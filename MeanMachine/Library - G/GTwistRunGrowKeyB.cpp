//
//  GTwistRunGrowKeyB.cpp
//  MeanMachine
//

#include "GTwistRunGrowKeyB.hpp"
#include "ArrangementFour.hpp"
#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryStarter.hpp"
#include "GPassFactoryTrunk.hpp"
#include "GSeedRunStageConfigValidator.hpp"
#include "GFlowPlans.hpp"
#include "ResidualBucket.hpp"

#include <algorithm>

namespace {

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

std::vector<TwistWorkSpaceSlot> PhaseSalts(const TwistDomain pDomain,
                                           const TwistWorkSpaceSlot pBaseSlot,
                                           const int pLaneCount) {
    const int aBase = static_cast<int>(pBaseSlot);
    const int aOffset = PhaseIndex(pDomain) * 24;

    std::vector<TwistWorkSpaceSlot> aResult;
    aResult.reserve(static_cast<std::size_t>(pLaneCount));
    for (int i = 0; i < pLaneCount; ++i) {
        aResult.push_back(static_cast<TwistWorkSpaceSlot>(aBase + aOffset + i));
    }
    return aResult;
}

GSeedRunStageConfig BaseConfig(const std::string &pStageName,
                               const std::string &pLoopName) {
    using Slot = TwistWorkSpaceSlot;
    constexpr TwistDomain kDomain = TwistDomain::kKeyRotateB;

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pLoopName;
    aConfig.mStartLine = "// " + pStageName + " " + pLoopName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + pLoopName + " (end)";

    aConfig.mIgnoreNonces = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = kDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = W_KEY;
    aConfig.mLoopEndText = "W_KEY";
    aConfig.mAutoRangeAdjust = false;
    aConfig.mSourceOffsetRangeLo = 0;
    aConfig.mSourceOffsetRangeHi = W_KEY1;
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterAssignA, 8);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterUpdateA, 8);
    aConfig.mSaltsWandererUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltWandererUpdateA, 8);
    return aConfig;
}

bool ApplyLaneSplit(GSeedRunStageConfig *pConfig,
                    const std::uint8_t pLaneSplit,
                    std::string *pErrorMessage) {
    if (pConfig == nullptr) {
        return false;
    }

    for (GSeedRunStageSliceSpec &aSlice : pConfig->mSlices) {
        std::vector<TwistWorkSpaceSlot> aSources =
            aSlice.IngressSources();
        const std::vector<TwistWorkSpaceSlot> aCrossSources =
            aSlice.CrossSources();
        aSources.insert(aSources.end(),
                        aCrossSources.begin(),
                        aCrossSources.end());

        for (const TwistWorkSpaceSlot aSource : aSources) {
            if (TwistWorkSpace::GetBufferLength(aSource) != S_BLOCK) {
                continue;
            }
            if (!aSlice.SetSourceLaneSplit(aSource,
                                           pLaneSplit,
                                           pErrorMessage)) {
                return false;
            }
        }

        if ((TwistWorkSpace::GetBufferLength(aSlice.mDest) == S_BLOCK) &&
            !aSlice.SetDestinationLaneSplit(pLaneSplit,
                                            pErrorMessage)) {
            return false;
        }
    }
    return true;
}

} // namespace

namespace GTwistRunGrowKeyBConfig {

GrowStageConfigs MakeGrowBConfig(ResidualBucket &pResidualBucket,
                                 const std::size_t pCandidateIndex) {
    using Slot = TwistWorkSpaceSlot;

    GrowStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    // Lane Plan
    const std::vector<GFlowStep> aLanePlans =
        GFlowPlans::ARXSteps(GFlowPlans::GrowB());

    //
    // Grow B — Stage A
    //
    const std::vector<Slot> aInputsAVector =
        GFlowPlans::InputSlots(aLanePlans[0]);
    const GPassFactoryStarter::SlotArray6 aInputsA = {
        aInputsAVector[0], aInputsAVector[1], aInputsAVector[2],
        aInputsAVector[3], aInputsAVector[4], aInputsAVector[5],
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsA =
        GFlowPlans::FamilySlots(aLanePlans[0].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsA));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsA));

    const std::vector<Slot> aResidualsOne =
        pResidualBucket.Withdraw("Grow B — Stage A / residuals A-B", 2);
    const std::vector<Slot> aResidualsTwo =
        pResidualBucket.Withdraw("Grow B — Stage A / residuals C-F", 4);
    const std::vector<Slot> aResidualsThree =
        pResidualBucket.Withdraw("Grow B — Stage A / residuals G-L", 6);

    std::vector<Slot> aResidualsThreeOrdered;
    for (Slot aResidual : aResidualsThree) {
        if ((aResidual != aResidualsTwo[2]) &&
            (aResidual != aResidualsTwo[3]) &&
            (aResidualsThreeOrdered.size() < 2U)) {
            aResidualsThreeOrdered.push_back(aResidual);
        }
    }
    for (Slot aResidual : aResidualsThree) {
        if (std::find(aResidualsThreeOrdered.begin(),
                      aResidualsThreeOrdered.end(),
                      aResidual) == aResidualsThreeOrdered.end()) {
            aResidualsThreeOrdered.push_back(aResidual);
        }
    }

    const GPassFactoryStarter::SlotArray12 aResidualsA = {
        aResidualsOne[0], aResidualsOne[1],
        aResidualsTwo[0], aResidualsTwo[1],
        aResidualsTwo[2], aResidualsTwo[3],
        aResidualsThreeOrdered[0], aResidualsThreeOrdered[1],
        aResidualsThreeOrdered[2], aResidualsThreeOrdered[3],
        aResidualsThreeOrdered[4], aResidualsThreeOrdered[5],
    };

    pResidualBucket.AddResiduals(
        "Grow B — Stage A sources",
        GFlowPlans::FamilySlotVector(aLanePlans[0].mInputs[0]),
        3U);

    //
    // Grow B — Stage B
    //
    const GPassFactoryMidstage::SlotArray4 aInputsB =
        GFlowPlans::FamilySlots(aLanePlans[1].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsB =
        GFlowPlans::FamilySlots(aLanePlans[1].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsB));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsB));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage B", 4);

    const GPassFactoryMidstage::SlotArray4 aResidualsB = {
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
    };

    pResidualBucket.AddResiduals(
        "Grow B — Stage B material",
        GFlowPlans::FamilySlotVector({
            aLanePlans[0].mOutput,
            aLanePlans[1].mOutput,
        }),
        3U);

    //
    // Grow B — Stage C
    //
    const GPassFactoryMidstage::SlotArray4 aInputsC =
        GFlowPlans::FamilySlots(aLanePlans[2].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsC =
        GFlowPlans::FamilySlots(aLanePlans[2].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsC));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsC));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage C", 2);

    const GPassFactoryMidstage::SlotArray2 aResidualsC = {
        aResidualsPool[0], aResidualsPool[1],
    };

    pResidualBucket.AddResiduals(
        "Grow B — Stage C material",
        GFlowPlans::FamilySlotVector({
            aLanePlans[2].mInputs[0],
            aLanePlans[2].mOutput,
        }),
        3U);

    //
    // Grow B — Stage D
    //
    const GPassFactoryMidstage::SlotArray4 aInputsD =
        GFlowPlans::FamilySlots(aLanePlans[3].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsD =
        GFlowPlans::FamilySlots(aLanePlans[3].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsD));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsD));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage D", 4);

    const GPassFactoryMidstage::SlotArray4 aResidualsD = {
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
    };

    pResidualBucket.AddResiduals(
        "Grow B — Stage D material",
        GFlowPlans::FamilySlotVector({
            aLanePlans[3].mInputs[0],
            aLanePlans[3].mOutput,
        }),
        3U);

    //
    // Grow B — Stage E
    //
    const GPassFactoryMidstage::SlotArray4 aInputsE =
        GFlowPlans::FamilySlots(aLanePlans[4].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsE =
        GFlowPlans::FamilySlots(aLanePlans[4].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsE));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsE));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage E", 2);

    const GPassFactoryMidstage::SlotArray2 aResidualsE = {
        aResidualsPool[0], aResidualsPool[1],
    };

    pResidualBucket.Print("Grow B — Final");

    // Stage Construction

    GSeedRunStageConfig aConfigA = BaseConfig("GROW_B_A",
                                              "grow_b_loop_a");
    aConfigA.mFormat = GAXSFormat::kN11;
    aConfigA.mSlices =
        GPassFactoryStarter::WideFourPassSixInputTwelveResidualSlices(
            aInputsA,
            aResidualsA,
            aDestinationsA);
    aConfigA.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsA.size());
    aConfigA.mHotPackCount =
        static_cast<int>(aDestinationsA.size());

    std::string aErrorMessageA;
    if (!ApplyLaneSplit(&aConfigA, 1U, &aErrorMessageA)) {
        printf("MakeGrowBConfig stage A could not apply lane split");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    if (!GSeedRunStageConfigValidator::ValidateGrowSixInput(
            aConfigA,
            std::vector<Slot>(aInputsA.begin(), aInputsA.end()),
            std::vector<Slot>(aResidualsA.begin(), aResidualsA.end()),
            GPassFactoryMidstage::ToVector(aDestinationsA),
            &aErrorMessageA)) {
        printf("MakeGrowBConfig stage A was not valid with ValidateGrowSixInput");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigA.SetLaneFlow(aInputsA, aDestinationsA);
    aConfigs[0] = aConfigA;

    GSeedRunStageConfig aConfigB = BaseConfig("GROW_B_B",
                                              "grow_b_loop_b");
    aConfigB.mFormat = GAXSFormat::kN11;
    aConfigB.mSlices =
        GPassFactoryMidstage::FourPassFourResidualSlices(
            aInputsB,
            aResidualsB,
            aDestinationsB);
    aConfigB.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsB.size());
    aConfigB.mHotPackCount =
        static_cast<int>(aDestinationsB.size());

    std::string aErrorMessageB;
    if (!ApplyLaneSplit(&aConfigB, 1U, &aErrorMessageB)) {
        printf("MakeGrowBConfig stage B could not apply lane split");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigB,
            GPassFactoryMidstage::ToVector(aInputsB),
            GPassFactoryMidstage::ToVector(aResidualsB),
            GPassFactoryMidstage::ToVector(aDestinationsB),
            &aErrorMessageB)) {
        printf("MakeGrowBConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigB.SetLaneFlow(aInputsB, aDestinationsB);
    aConfigs[1] = aConfigB;

    const ArrangementFour::SlotArray4 aArrangedInputsC =
        ArrangementFour::Arrange(aInputsC,
                                 static_cast<int>(pCandidateIndex),
                                 aLanePlans[2].mArrangementOffset);

    GSeedRunStageConfig aConfigC = BaseConfig("GROW_B_C",
                                              "grow_b_loop_c");
    aConfigC.mFormat = GAXSFormat::kN11;
    aConfigC.mSlices =
        GPassFactoryTrunk::FourPassTrunkSlices(
            aArrangedInputsC,
            aResidualsC,
            aDestinationsC);
    aConfigC.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsC.size());
    aConfigC.mHotPackCount =
        static_cast<int>(aDestinationsC.size());

    std::string aErrorMessageC;
    if (!ApplyLaneSplit(&aConfigC, 1U, &aErrorMessageC)) {
        printf("MakeGrowBConfig stage C could not apply lane split");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    if (!GSeedRunStageConfigValidator::ValidateTrunk(
            aConfigC,
            GPassFactoryMidstage::ToVector(aArrangedInputsC),
            GPassFactoryMidstage::ToVector(aResidualsC),
            GPassFactoryMidstage::ToVector(aDestinationsC),
            &aErrorMessageC)) {
        printf("MakeGrowBConfig stage C was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigC.SetLaneFlow(aInputsC, aDestinationsC);
    aConfigs[2] = aConfigC;

    GSeedRunStageConfig aConfigD = BaseConfig("GROW_B_D",
                                              "grow_b_loop_d");
    aConfigD.mFormat = GAXSFormat::kN11;
    aConfigD.mSlices =
        GPassFactoryMidstage::FourPassFourResidualSlices(
            aInputsD,
            aResidualsD,
            aDestinationsD);
    aConfigD.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsD.size());
    aConfigD.mHotPackCount =
        static_cast<int>(aDestinationsD.size());

    std::string aErrorMessageD;
    if (!ApplyLaneSplit(&aConfigD, 1U, &aErrorMessageD)) {
        printf("MakeGrowBConfig stage D could not apply lane split");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigD,
            GPassFactoryMidstage::ToVector(aInputsD),
            GPassFactoryMidstage::ToVector(aResidualsD),
            GPassFactoryMidstage::ToVector(aDestinationsD),
            &aErrorMessageD)) {
        printf("MakeGrowBConfig stage D was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigD.SetLaneFlow(aInputsD, aDestinationsD);
    aConfigs[3] = aConfigD;

    const ArrangementFour::SlotArray4 aArrangedInputsE =
        ArrangementFour::Arrange(aInputsE,
                                 static_cast<int>(pCandidateIndex),
                                 aLanePlans[4].mArrangementOffset);

    GSeedRunStageConfig aConfigE = BaseConfig("GROW_B_E",
                                              "grow_b_loop_e");
    aConfigE.mFormat = GAXSFormat::kN11;
    aConfigE.mSlices =
        GPassFactoryTrunk::FourPassTrunkSlices(
            aArrangedInputsE,
            aResidualsE,
            aDestinationsE);
    aConfigE.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsE.size());
    aConfigE.mHotPackCount =
        static_cast<int>(aDestinationsE.size());

    std::string aErrorMessageE;
    if (!ApplyLaneSplit(&aConfigE, 1U, &aErrorMessageE)) {
        printf("MakeGrowBConfig stage E could not apply lane split");
        printf("%s\n", aErrorMessageE.c_str());
        exit(0);
    }
    if (!GSeedRunStageConfigValidator::ValidateTrunk(
            aConfigE,
            GPassFactoryMidstage::ToVector(aArrangedInputsE),
            GPassFactoryMidstage::ToVector(aResidualsE),
            GPassFactoryMidstage::ToVector(aDestinationsE),
            &aErrorMessageE)) {
        printf("MakeGrowBConfig stage E was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageE.c_str());
        exit(0);
    }
    aConfigE.SetLaneFlow(aInputsE, aDestinationsE);
    aConfigs[4] = aConfigE;

    return aConfigs;
}

} // namespace GTwistRunGrowKeyBConfig

GTwistRunGrowKeyB::GTwistRunGrowKeyB(ResidualBucket &pResidualBucket)
: mStage(GTwistRunGrowKeyBConfig::MakeGrowBConfig(pResidualBucket, 0U)[0]) {
}

GTwistRunGrowKeyB::GTwistRunGrowKeyB(const GSeedRunStageConfig &pConfig,
                                     ResidualBucket &pResidualBucket)
: mStage(pConfig) {
    (void)pResidualBucket;
}

GTwistRunGrowKeyB::~GTwistRunGrowKeyB() {
}

void GTwistRunGrowKeyB::Reset() {
    mStage.Reset();
}

bool GTwistRunGrowKeyB::Plan(std::string *pErrorMessage) {
    Reset();
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunGrowKeyB::Build(TwistProgramBranch &pBranch,
                              std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}
