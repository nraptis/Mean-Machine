//
//  GSeedRunKeyBox.cpp
//  MeanMachine
//

#include "GSeedRunKeyBox.hpp"

#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryStarter.hpp"
#include "GFlowPlans.hpp"
#include "KeyLaneAssignments.hpp"
#include "ResidualBucket.hpp"

#include <algorithm>
#include <array>
#include <utility>
#include <vector>

namespace {

using Slot = TwistWorkSpaceSlot;

constexpr std::size_t kKeyFlowCount = GFlowPlans::kKeyFlowCount;
constexpr std::size_t kKeyBoxAFlowCount =
    GFlowPlans::kKeyBoxFlowCount;
constexpr std::size_t kPhaseAConfigOffset = 0U;
constexpr std::size_t kPhaseBConfigOffset = 1U * kKeyFlowCount;
constexpr std::size_t kPhaseCConfigOffset = 2U * kKeyFlowCount;
constexpr std::size_t kPhaseDConfigOffset = 3U * kKeyFlowCount;
constexpr std::size_t kPhaseEConfigOffset = 4U * kKeyFlowCount;

std::string KeyStageName(const std::size_t pLogicalIndex,
                         const char pPhase) {
    const char aKeyBox = (pLogicalIndex < kKeyBoxAFlowCount) ? 'A' : 'B';
    const char aKeyRow = static_cast<char>(
        'A' + (pLogicalIndex % kKeyBoxAFlowCount));
    return std::string("GSeedRunKEY_") + aKeyBox + "_" +
        aKeyRow + "_" + pPhase;
}

std::string KeyBatchName(const std::size_t pLogicalIndex,
                         const char pPhase) {
    const char aKeyBox = (pLogicalIndex < kKeyBoxAFlowCount) ? 'a' : 'b';
    const char aKeyRow = static_cast<char>(
        'a' + (pLogicalIndex % kKeyBoxAFlowCount));
    const char aPhase = static_cast<char>(pPhase - 'A' + 'a');
    return std::string("key_") + aKeyBox + "_loop_" +
        aKeyRow + "_" + aPhase;
}

std::vector<Slot> PhaseSalts(const TwistDomain pDomain,
                             const Slot pBaseSlot,
                             const int pLaneCount) {
    int aPhaseIndex = 0;
    switch (pDomain) {
        case TwistDomain::kKeySpawnA: aPhaseIndex = 1; break;
        case TwistDomain::kSeed: aPhaseIndex = 2; break;
        case TwistDomain::kTwist: aPhaseIndex = 3; break;
        case TwistDomain::kKeyRotateB: aPhaseIndex = 4; break;
        case TwistDomain::kKeySpawnB: aPhaseIndex = 5; break;
        case TwistDomain::kKeyRotateA:
        default:
            aPhaseIndex = 0;
            break;
    }

    std::vector<Slot> aResult;
    aResult.reserve(static_cast<std::size_t>(pLaneCount));
    const int aBase = static_cast<int>(pBaseSlot);
    const int aOffset = aPhaseIndex * 24;
    for (int i = 0; i < pLaneCount; ++i) {
        aResult.push_back(
            static_cast<Slot>(aBase + aOffset + i)
        );
    }
    return aResult;
}

GSeedRunStageConfig BaseConfig(const std::string &pStageName,
                               const std::string &pBatchName,
                               const TwistDomain pDomain,
                               const GAXSFormat pFormat) {
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pBatchName;
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = false;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = pDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 1;
    aConfig.mHotPackCount = 1;
    aConfig.mMaxContextSourceCount = 4;
    aConfig.mMaxBoundSourceCount = 8;
    aConfig.mBindDuplicateSourceSlots = false;
    aConfig.mFixedDiffuse = GAXSKDiffuseKind::kDiffuseA;
    aConfig.mAutoRangeAdjust = false;
    aConfig.mSourceOffsetRangeLo = 0;
    aConfig.mSourceOffsetRangeHi = W_KEY1;
    aConfig.mEmitLaneFlowComments = true;
    aConfig.mSaltsOrbiterAssign =
        PhaseSalts(pDomain,
                   Slot::kKeyRotateASaltOrbiterAssignA,
                   8);
    aConfig.mSaltsOrbiterUpdate =
        PhaseSalts(pDomain,
                   Slot::kKeyRotateASaltOrbiterUpdateA,
                   8);
    aConfig.mSaltsWandererUpdate =
        PhaseSalts(pDomain,
                   Slot::kKeyRotateASaltWandererUpdateA,
                   8);
    return aConfig;
}

template <std::size_t N>
std::array<Slot, N> WithdrawFlowResiduals(
    ResidualBucket &pResidualBucket,
    const std::string &pStageName) {
    const std::vector<Slot> aWithdrawn =
        pResidualBucket.Withdraw(pStageName, static_cast<int>(N));
    std::array<Slot, N> aResult = {};
    for (std::size_t i = 0U; i < N; ++i) {
        aResult[i] = aWithdrawn[i];
    }
    return aResult;
}

void AppendUniqueSlots(std::vector<Slot> *pDestination,
                       const std::vector<Slot> &pSource) {
    for (const Slot aSlot : pSource) {
        if (std::find(pDestination->begin(),
                      pDestination->end(),
                      aSlot) == pDestination->end()) {
            pDestination->push_back(aSlot);
        }
    }
}

std::uint8_t KeyLaneSplit(
    const Slot pSlot,
    const std::size_t pLogicalKeyIndex,
    const std::size_t pCandidateIndex) {
    return KeyLaneAssignments::Split(pSlot,
                                     pLogicalKeyIndex,
                                     pCandidateIndex);
}

bool ApplyKeyLaneSplits(
    GSeedRunStageConfig *pConfig,
    const std::size_t pLogicalKeyIndex,
    const std::size_t pCandidateIndex,
    std::string *pErrorMessage) {
    if (pConfig == nullptr) {
        return false;
    }

    for (GSeedRunStageSliceSpec &aSlice : pConfig->mSlices) {
        std::vector<Slot> aSources = aSlice.IngressSources();
        const std::vector<Slot> aCrossSources = aSlice.CrossSources();
        aSources.insert(aSources.end(),
                        aCrossSources.begin(),
                        aCrossSources.end());
        for (const Slot aSource : aSources) {
            if (TwistWorkSpace::GetBufferLength(aSource) != S_BLOCK) {
                continue;
            }
            if (!KeyLaneAssignments::HasLane(aSource)) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage =
                        "Key flow used a full lane without a mandatory "
                        "KeyLaneAssignments entry";
                }
                return false;
            }
            if (!aSlice.SetSourceLaneSplit(
                    aSource,
                    KeyLaneSplit(aSource,
                                 pLogicalKeyIndex,
                                 pCandidateIndex),
                    pErrorMessage)) {
                return false;
            }
        }

        if ((TwistWorkSpace::GetBufferLength(aSlice.mDest) == S_BLOCK) &&
            !KeyLaneAssignments::HasLane(aSlice.mDest)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Key flow wrote a full lane without a mandatory "
                    "KeyLaneAssignments entry";
            }
            return false;
        }
        if ((TwistWorkSpace::GetBufferLength(aSlice.mDest) == S_BLOCK) &&
            !aSlice.SetDestinationLaneSplit(
                KeyLaneSplit(aSlice.mDest,
                             pLogicalKeyIndex,
                             pCandidateIndex),
                pErrorMessage)) {
            return false;
        }
    }
    return true;
}

GSeedRunStageConfig FinishFourLoopConfig(
    GSeedRunStageConfig pConfig,
    const std::size_t pLogicalKeyIndex,
    const std::size_t pCandidateIndex,
    const TwistDomain pDomain,
    std::string *pErrorMessage) {
    pConfig.mExpectedSkeletonCount = 4;
    pConfig.mHotPackCount = 4;
    pConfig.mLoopBegin = 0;
    pConfig.mLoopBeginText.clear();
    pConfig.mLoopCeiling = W_KEY;
    pConfig.mLoopEndText = "W_KEY";
    pConfig.mSliceDomains.assign(4U, pDomain);
    if (!ApplyKeyLaneSplits(&pConfig,
                            pLogicalKeyIndex,
                            pCandidateIndex,
                            pErrorMessage)) {
        return GSeedRunStageConfig();
    }
    return pConfig;
}

} // namespace

namespace GSeedRunKeyBoxConfig {

bool MakeKeyBoxConfigs(const std::size_t pCandidateIndex,
                       const ResidualBucket &pSeedResidualBucket,
                       KeyBoxStageConfigs *pConfigs,
                       std::string *pErrorMessage) {
    if (pConfigs == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Key-box config output was null";
        }
        return false;
    }
    // Lane Plan
    const std::vector<GFlowStep> aLanePlans =
        GFlowPlans::ARXSteps(GFlowPlans::Key());
    if (aLanePlans.size() != GFlowPlans::kKeyARXStageCount) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Key stage configuration count did not match its flow plan";
        }
        return false;
    }

    //
    // KEY — Phase A
    // Eight inherited residual lanes are consumed.
    //
    const std::vector<Slot> aPrimarySourcesAVector =
        GFlowPlans::InputSlots(aLanePlans[0]);
    const GPassFactoryStarter::SlotArray8 aPrimarySourcesA = {
        aPrimarySourcesAVector[0], aPrimarySourcesAVector[1],
        aPrimarySourcesAVector[2], aPrimarySourcesAVector[3],
        aPrimarySourcesAVector[4], aPrimarySourcesAVector[5],
        aPrimarySourcesAVector[6], aPrimarySourcesAVector[7],
    };
    const GPassFactoryStarter::SlotArray4 aDestinationsA =
        GFlowPlans::FamilySlots(aLanePlans[0].mOutput);

    //
    // KEY — Phase B
    // Thirteen inherited residual lanes are consumed.
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesB =
        GFlowPlans::FamilySlots(aLanePlans[1].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsB =
        GFlowPlans::FamilySlots(aLanePlans[1].mOutput);

    //
    // KEY — Phase C
    // Thirteen inherited residual lanes are consumed.
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesC =
        GFlowPlans::FamilySlots(aLanePlans[2].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsC =
        GFlowPlans::FamilySlots(aLanePlans[2].mOutput);

    //
    // KEY — Phase D
    // Thirteen inherited residual lanes are consumed.
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesD =
        GFlowPlans::FamilySlots(aLanePlans[3].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsD =
        GFlowPlans::FamilySlots(aLanePlans[3].mOutput);

    //
    // KEY — Phase E
    // This overwrites only the current logical key flow's Ice sixteenths;
    // every other flow owns a different KeyLaneAssignments split.
    // Thirteen inherited residual lanes are consumed.
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesE =
        GFlowPlans::FamilySlots(aLanePlans[4].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsE =
        GFlowPlans::FamilySlots(aLanePlans[4].mOutput);

    // These lanes have fixed jobs in the five phases. Source and Nonce are
    // deliberately excluded from key construction. No phase adds its output
    // lanes back; each independent flow drains this inherited bucket.
    std::vector<Slot> aUnavailableResiduals = {
        Slot::kSourceLane,
        Slot::kNonceLane,
    };
    for (const GFlowStep &aPlan : aLanePlans) {
        AppendUniqueSlots(&aUnavailableResiduals,
                          GFlowPlans::InputSlots(aPlan));
        AppendUniqueSlots(
            &aUnavailableResiduals,
            GFlowPlans::FamilySlotVector(aPlan.mOutput));
    }

    // Stage Construction

    for (std::size_t aLogicalIndex = 0U;
         aLogicalIndex < kKeyFlowCount;
         ++aLogicalIndex) {
        const TwistDomain aDomain =
            (aLogicalIndex < kKeyBoxAFlowCount)
                ? TwistDomain::kKeySpawnA
                : TwistDomain::kKeySpawnB;
        const std::string aFlowName =
            std::string("KEY flow ") +
            std::to_string(aLogicalIndex);

        // Each logical key flow gets an independent value-copy of the final
        // Seed residual state. Its withdrawals never affect another key flow
        // or the caller's bucket. Flattening the surviving lanes to three
        // makes every withdrawal terminal: a selected lane advances to four
        // and cannot be selected again within this key flow.
        ResidualBucket aFlowResidualBucket = pSeedResidualBucket;
        aFlowResidualBucket.Remove(aUnavailableResiduals);
        aFlowResidualBucket.FlattenUsageCounts(3U);

        const GPassFactoryStarter::SlotArray8 aResidualsA =
            WithdrawFlowResiduals<8U>(
                aFlowResidualBucket,
                aFlowName + " — Phase A");

        const GPassFactoryMidstage::SlotArray13 aResidualsB =
            WithdrawFlowResiduals<13U>(
                aFlowResidualBucket,
                aFlowName + " — Phase B");

        const GPassFactoryMidstage::SlotArray13 aResidualsC =
            WithdrawFlowResiduals<13U>(
                aFlowResidualBucket,
                aFlowName + " — Phase C");

        const GPassFactoryMidstage::SlotArray13 aResidualsD =
            WithdrawFlowResiduals<13U>(
                aFlowResidualBucket,
                aFlowName + " — Phase D");

        const GPassFactoryMidstage::SlotArray13 aResidualsE =
            WithdrawFlowResiduals<13U>(
                aFlowResidualBucket,
                aFlowName + " — Phase E");

        constexpr std::size_t kExpectedResidualSurplus = 16U;
        const std::size_t aResidualSurplus =
            aFlowResidualBucket.CountValidResiduals();
        if (aResidualSurplus != kExpectedResidualSurplus) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    aFlowName + " ended with " +
                    std::to_string(aResidualSurplus) +
                    " residual lanes; expected " +
                    std::to_string(kExpectedResidualSurplus);
            }
            return false;
        }

        //
        // Build KEY — Phase A
        //
        GSeedRunStageConfig aConfigA = BaseConfig(
            KeyStageName(aLogicalIndex, 'A'),
            KeyBatchName(aLogicalIndex, 'A'),
            aDomain,
            GAXSFormat::kN11);
        aConfigA.mSlices =
            GPassFactoryStarter::WideFourPassTenResidualSlices(
                aPrimarySourcesA,
                aResidualsA,
                aDestinationsA);
        aConfigA.SetLaneFlow(aPrimarySourcesA, aDestinationsA);
        aConfigA = FinishFourLoopConfig(std::move(aConfigA),
                                        aLogicalIndex,
                                        pCandidateIndex,
                                        aDomain,
                                        pErrorMessage);
        if (aConfigA.mStageName.empty()) {
            return false;
        }
        (*pConfigs)[kPhaseAConfigOffset + aLogicalIndex] =
            std::move(aConfigA);

        //
        // Build KEY — Phase B
        //
        GSeedRunStageConfig aConfigB = BaseConfig(
            KeyStageName(aLogicalIndex, 'B'),
            KeyBatchName(aLogicalIndex, 'B'),
            aDomain,
            GAXSFormat::kN11);
        aConfigB.mSlices =
            GPassFactoryMidstage::FourPassThirteenResidualSlices(
                aPrimarySourcesB,
                aResidualsB,
                aDestinationsB);
        aConfigB.SetLaneFlow(aPrimarySourcesB, aDestinationsB);
        aConfigB = FinishFourLoopConfig(std::move(aConfigB),
                                        aLogicalIndex,
                                        pCandidateIndex,
                                        aDomain,
                                        pErrorMessage);
        if (aConfigB.mStageName.empty()) {
            return false;
        }
        (*pConfigs)[kPhaseBConfigOffset + aLogicalIndex] =
            std::move(aConfigB);

        //
        // Build KEY — Phase C
        //
        GSeedRunStageConfig aConfigC = BaseConfig(
            KeyStageName(aLogicalIndex, 'C'),
            KeyBatchName(aLogicalIndex, 'C'),
            aDomain,
            GAXSFormat::kN11);
        aConfigC.mSlices =
            GPassFactoryMidstage::FourPassThirteenResidualSlices(
                aPrimarySourcesC,
                aResidualsC,
                aDestinationsC);
        aConfigC.SetLaneFlow(aPrimarySourcesC, aDestinationsC);
        aConfigC = FinishFourLoopConfig(std::move(aConfigC),
                                        aLogicalIndex,
                                        pCandidateIndex,
                                        aDomain,
                                        pErrorMessage);
        if (aConfigC.mStageName.empty()) {
            return false;
        }
        (*pConfigs)[kPhaseCConfigOffset + aLogicalIndex] =
            std::move(aConfigC);

        //
        // Build KEY — Phase D
        //
        GSeedRunStageConfig aConfigD = BaseConfig(
            KeyStageName(aLogicalIndex, 'D'),
            KeyBatchName(aLogicalIndex, 'D'),
            aDomain,
            GAXSFormat::kN11);
        aConfigD.mSlices =
            GPassFactoryMidstage::FourPassThirteenResidualSlices(
                aPrimarySourcesD,
                aResidualsD,
                aDestinationsD);
        aConfigD.SetLaneFlow(aPrimarySourcesD, aDestinationsD);
        aConfigD = FinishFourLoopConfig(std::move(aConfigD),
                                        aLogicalIndex,
                                        pCandidateIndex,
                                        aDomain,
                                        pErrorMessage);
        if (aConfigD.mStageName.empty()) {
            return false;
        }
        (*pConfigs)[kPhaseDConfigOffset + aLogicalIndex] =
            std::move(aConfigD);

        //
        // Build KEY — Phase E
        //
        GSeedRunStageConfig aConfigE = BaseConfig(
            KeyStageName(aLogicalIndex, 'E'),
            KeyBatchName(aLogicalIndex, 'E'),
            aDomain,
            GAXSFormat::kN11);
        aConfigE.mSlices =
            GPassFactoryMidstage::FourPassThirteenResidualSlices(
                aPrimarySourcesE,
                aResidualsE,
                aDestinationsE);
        aConfigE.SetLaneFlow(aPrimarySourcesE, aDestinationsE);
        aConfigE = FinishFourLoopConfig(std::move(aConfigE),
                                        aLogicalIndex,
                                        pCandidateIndex,
                                        aDomain,
                                        pErrorMessage);
        if (aConfigE.mStageName.empty()) {
            return false;
        }
        (*pConfigs)[kPhaseEConfigOffset + aLogicalIndex] =
            std::move(aConfigE);
    }
    return true;
}

} // namespace GSeedRunKeyBoxConfig

GSeedRunKEY::GSeedRunKEY(
    const GSeedRunStageConfig &pConfig)
: mStage(pConfig) {
}

bool GSeedRunKEY::Plan(
    std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKEY::Build(
    TwistProgramBranch &pBranch,
    std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}
