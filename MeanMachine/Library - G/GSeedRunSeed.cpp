//
//  GSeedRunSeed.cpp
//  MeanMachine
//

#include "GSeedRunSeed.hpp"
#include "ArrangementFour.hpp"
#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryStarter.hpp"
#include "GPassFactoryTrunk.hpp"
#include "GFlowPlans.hpp"
#include "Random.hpp"
#include "ResidualBucket.hpp"
#include "GSeedRunStageConfigValidator.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Slot = TwistWorkSpaceSlot;
using SlotArray4 = GPassFactoryMidstage::SlotArray4;

const std::array<const char *, 16> kNonceVariableNames = {
    "aNonceWordA", "aNonceWordB", "aNonceWordC", "aNonceWordD",
    "aNonceWordE", "aNonceWordF", "aNonceWordG", "aNonceWordH",
    "aNonceWordI", "aNonceWordJ", "aNonceWordK", "aNonceWordL",
    "aNonceWordM", "aNonceWordN", "aNonceWordO", "aNonceWordP",
};

const std::array<const char *, 3> kNonceDiffuseNames = {
    "DiffuseA", "DiffuseB", "DiffuseC",
};

int PhaseIndex(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kKeySpawnA: return 1;
        case TwistDomain::kSeed: return 2;
        case TwistDomain::kTwist: return 3;
        case TwistDomain::kKeyRotateB: return 4;
        case TwistDomain::kKeySpawnB: return 5;
        case TwistDomain::kKeyRotateA:
        default:
            return 0;
    }
}

std::string SeedStageName(const char pStageLetter) {
    return "GSeedRunSeed_" + std::string(1U, pStageLetter);
}

std::string SeedStageTitle(const char pStageLetter) {
    return "Seed — Stage " + std::string(1U, pStageLetter);
}

std::string SeedLoopName(const std::string &pStageName) {
    std::string aResult = "seed_loop";
    if (!pStageName.empty()) {
        const char aStageLetter = pStageName.back();
        if ((aStageLetter >= 'A') && (aStageLetter <= 'Q')) {
            aResult.push_back('_');
            aResult.push_back(
                static_cast<char>('a' + (aStageLetter - 'A')));
        }
    }
    return aResult;
}

std::string UInt64Literal(const std::uint64_t pValue) {
    std::ostringstream aStream;
    aStream << "0x" << std::uppercase << std::hex << pValue << "ULL";
    return aStream.str();
}

const char *RandomNonceDiffuseName() {
    return kNonceDiffuseNames[static_cast<std::size_t>(
        Random::Get(static_cast<int>(kNonceDiffuseNames.size())))];
}

std::string NonceDeclareLine(const GSymbol &pNonceSymbol) {
    const std::uint64_t aMultiplyWord = Random::Get64HighOdd();
    const std::uint64_t aAddWord = Random::Get64High();

    std::ostringstream aLine;
    aLine << "const std::uint64_t " << pNonceSymbol.mName
          << " = TwistMix64::" << RandomNonceDiffuseName()
          << "(pNonce * " << UInt64Literal(aMultiplyWord)
          << " + " << UInt64Literal(aAddWord) << ");";
    return aLine.str();
}

void AddSeedNoncePrologue(TwistProgramBranch &pBranch) {
    for (const char *aNonceVariableName : kNonceVariableNames) {
        pBranch.AddLine(
            NonceDeclareLine(GSymbol::Var(aNonceVariableName)));
    }
}

std::vector<Slot> PhaseSalts(const TwistDomain pDomain,
                             const Slot pBaseSlot,
                             const int pLaneCount) {
    const int aBase = static_cast<int>(pBaseSlot);
    const int aOffset = PhaseIndex(pDomain) * 24;

    std::vector<Slot> aResult;
    aResult.reserve(static_cast<std::size_t>(pLaneCount));
    for (int i = 0; i < pLaneCount; ++i) {
        aResult.push_back(static_cast<Slot>(aBase + aOffset + i));
    }
    return aResult;
}

GSeedRunStageConfig BaseConfig(const std::string &pStageName,
                               const bool pUseNonces,
                               const GAXSFormat pFormat) {
    constexpr TwistDomain kDomain = TwistDomain::kSeed;
    const std::string aLoopName = SeedLoopName(pStageName);

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = aLoopName;
    aConfig.mStartLine =
        "// " + pStageName + " " + aLoopName + " (start)";
    aConfig.mEndLine =
        "// " + pStageName + " " + aLoopName + " (end)";
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = !pUseNonces;
    aConfig.mDomain = kDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(
        kDomain, Slot::kKeyRotateASaltOrbiterAssignA, 8);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(
        kDomain, Slot::kKeyRotateASaltOrbiterUpdateA, 8);
    aConfig.mSaltsWandererUpdate = PhaseSalts(
        kDomain, Slot::kKeyRotateASaltWandererUpdateA, 8);
    return aConfig;
}

std::vector<Slot> WithdrawSeedResiduals(
    ResidualBucket &pResidualBucket,
    const GFlowStep &pStep,
    const std::string &pStageName) {
    constexpr std::size_t kMaximumResidualCount = 16U;
    std::vector<Slot> aResiduals =
        GFlowPlans::ForcedResidualSlots(pStep);
    if (aResiduals.size() > kMaximumResidualCount) {
        return {};
    }

    const std::size_t aPoolCount =
        std::min(kMaximumResidualCount - aResiduals.size(),
                 pResidualBucket.CountValidResiduals());
    std::vector<Slot> aWithdrawnResiduals =
        pResidualBucket.Withdraw(pStageName,
                                 static_cast<int>(aPoolCount));
    aResiduals.insert(aResiduals.end(),
                      aWithdrawnResiduals.begin(),
                      aWithdrawnResiduals.end());
    return aResiduals;
}

void AddCompletedStageLanes(ResidualBucket &pResidualBucket,
                            const GFlowStep &pStep) {
    std::vector<Slot> aResiduals = GFlowPlans::InputSlots(pStep);
    const GFlowPlans::SlotArray4 aDestinationSlots =
        GFlowPlans::FamilySlots(pStep.mOutput);
    const std::vector<Slot> aOutputs(aDestinationSlots.begin(),
                                     aDestinationSlots.end());
    aResiduals.insert(aResiduals.end(),
                      aOutputs.begin(),
                      aOutputs.end());
    pResidualBucket.AddResiduals(
        SeedStageTitle(pStep.mLetter),
        std::move(aResiduals));
}

} // namespace

namespace GSeedRunSeedConfig {

SeedStageConfigs MakeSeedConfig(const bool pUseNonces,
                                ResidualBucket &pResidualBucket,
                                const std::size_t pCandidateIndex) {
    SeedStageConfigs aConfigs;

    // Lane Plan
    const std::vector<GFlowStep> aLanePlans =
        GFlowPlans::ARXSteps(GFlowPlans::Seed());
    const std::vector<Slot> aPrimarySourcesAVector =
        GFlowPlans::InputSlots(aLanePlans[0]);
    const GPassFactoryStarter::SlotArray2 aPrimarySourcesA = {
        aPrimarySourcesAVector[0], aPrimarySourcesAVector[1],
    };
    const SlotArray4 aDestinationsA =
        GFlowPlans::FamilySlots(aLanePlans[0].mOutput);

    // Stage Construction

    pResidualBucket.Remove(
        GPassFactoryMidstage::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(
        GPassFactoryMidstage::ToVector(aDestinationsA));
    pResidualBucket.Withdraw("Seed — Stage A", 0);

    GSeedRunStageConfig aConfigA = BaseConfig(
        "GSeedRunSeed_A", pUseNonces, GAXSFormat::kN11);
    aConfigA.mSlices = GPassFactoryStarter::KDF_A_AStarterSlices(
        aPrimarySourcesA,
        aDestinationsA,
        pCandidateIndex);
    aConfigA.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsA.size());
    aConfigA.mHotPackCount =
        static_cast<int>(aDestinationsA.size());

    std::string aErrorMessageA;
    if (!GSeedRunStageConfigValidator::ValidateStarter(
            aConfigA,
            GPassFactoryMidstage::ToVector(aPrimarySourcesA),
            GPassFactoryMidstage::ToVector(aDestinationsA),
            &aErrorMessageA)) {
        printf("MakeSeedConfig stage A was not valid with ValidateStarter");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigA.SetLaneFlow(aPrimarySourcesA, aDestinationsA);
    aConfigs[0] = aConfigA;
    pResidualBucket.AddResiduals(
        "Seed — Stage A",
        GPassFactoryMidstage::ToVector(aDestinationsA));

    for (std::size_t aPlanIndex = 1U;
         aPlanIndex < aLanePlans.size();
         ++aPlanIndex) {
        const GFlowStep &aPlan = aLanePlans[aPlanIndex];
        const std::size_t aConfigIndex = aPlanIndex;
        const std::string aStageName = SeedStageName(aPlan.mLetter);
        const std::string aStageTitle = SeedStageTitle(aPlan.mLetter);
        const SlotArray4 aPrimarySources =
            GFlowPlans::FamilySlots(aPlan.mInputs[0]);
        const SlotArray4 aDestinations =
            GFlowPlans::FamilySlots(aPlan.mOutput);
        const std::vector<Slot> aOutputs(aDestinations.begin(),
                                         aDestinations.end());

        pResidualBucket.Remove(
            GPassFactoryMidstage::ToVector(aPrimarySources));
        pResidualBucket.Remove(aOutputs);

        GSeedRunStageConfig aConfig = BaseConfig(
            aStageName, pUseNonces, GAXSFormat::kN11);
        std::string aErrorMessage;
        const std::vector<Slot> aResiduals =
            WithdrawSeedResiduals(pResidualBucket,
                                  aPlan,
                                  aStageTitle);
        aConfig.mExpectedSkeletonCount =
            static_cast<int>(aDestinations.size());
        aConfig.mHotPackCount =
            static_cast<int>(aDestinations.size());

        if (aPlan.mARXShape == GFlowARXShape::kTrunk) {
            const ArrangementFour::SlotArray4 aArrangedPrimarySources =
                ArrangementFour::Arrange(
                    aPrimarySources,
                    static_cast<int>(pCandidateIndex),
                    aPlan.mArrangementOffset);
            aConfig.mSlices = GPassFactoryTrunk::FourPassVariableResidualSlices(
                aArrangedPrimarySources,
                aResiduals,
                aDestinations);
            if (!GSeedRunStageConfigValidator::ValidateTrunk(
                    aConfig,
                    GPassFactoryMidstage::ToVector(aArrangedPrimarySources),
                    aResiduals,
                    GPassFactoryMidstage::ToVector(aDestinations),
                    &aErrorMessage)) {
                printf("MakeSeedConfig stage %c was not valid with ValidateTrunk",
                       aPlan.mLetter);
                printf("%s\n", aErrorMessage.c_str());
                exit(0);
            }
        } else {
            aConfig.mSlices =
                GPassFactoryMidstage::FourPassVariableResidualSlices(
                    aPrimarySources,
                    aResiduals,
                    aDestinations);
            if (!GSeedRunStageConfigValidator::ValidateMidstage(
                    aConfig,
                    GPassFactoryMidstage::ToVector(aPrimarySources),
                    aResiduals,
                    GPassFactoryMidstage::ToVector(aDestinations),
                    &aErrorMessage)) {
                printf("MakeSeedConfig stage %c was not valid with ValidateMidstage",
                       aPlan.mLetter);
                printf("%s\n", aErrorMessage.c_str());
                exit(0);
            }
        }

        aConfig.SetLaneFlow(aPrimarySources,
                            aDestinations);
        aConfigs[aConfigIndex] = aConfig;
        AddCompletedStageLanes(pResidualBucket, aPlan);
    }
    
    return aConfigs;
}

} // namespace GSeedRunSeedConfig

GSeedRunSeed::GSeedRunSeed(const GSeedRunStageConfig &pConfig,
                           const bool pUseNonces,
                           const bool pEmitNoncePrologue)
: mStage(pConfig),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

bool GSeedRunSeed::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed::Build(TwistProgramBranch &pBranch,
                         std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
