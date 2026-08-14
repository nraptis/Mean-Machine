//
//  GSeedRunKDF_A.cpp
//  MeanMachine
//

#include "GSeedRunKDF_A.hpp"
#include "ArrangementFour.hpp"
#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryStarter.hpp"
#include "GPassFactoryTrunk.hpp"
#include "GSeedRunStageConfigValidator.hpp"
#include "GSeedRunKDFCommon.hpp"
#include "GFlowPlans.hpp"
#include "ResidualBucket.hpp"

#include <array>

namespace GSeedRunKDF_AConfig {

KDFStageConfigs MakeKDF_AConfig(ResidualBucket &pResidualBucket,
                                const std::size_t pCandidateIndex) {
    using Slot = TwistWorkSpaceSlot;
    KDFStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    // Lane Plan
    const std::vector<GFlowStep> aLanePlans =
        GFlowPlans::ARXSteps(GFlowPlans::KDFA());

    //
    // KDF A — Stage A
    //
    const std::vector<Slot> aPrimarySourcesAVector =
        GFlowPlans::InputSlots(aLanePlans[0]);
    const GPassFactoryStarter::SlotArray2 aPrimarySourcesA = {
        aPrimarySourcesAVector[0], aPrimarySourcesAVector[1],
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsA =
        GFlowPlans::FamilySlots(aLanePlans[0].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsA));

    printf("at KDF A — Stage A, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    //
    // KDF A — Stage B
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesB =
        GFlowPlans::FamilySlots(aLanePlans[1].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsB =
        GFlowPlans::FamilySlots(aLanePlans[1].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesB));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsB));

    printf("at KDF A — Stage B, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    const GPassFactoryMidstage::SlotArray2 aResidualsB = {
        Slot::kSourceLane,
        Slot::kNonceLane,
    };

    pResidualBucket.AddResiduals(
        "KDF A — Stage B",
        GFlowPlans::FamilySlotVector(aLanePlans[1].mInputs[0]));

    pResidualBucket.AddResiduals(
        "KDF A — After diffusion",
        GFlowPlans::FamilySlotVector(aLanePlans[1].mOutput));

    //
    // KDF A — Stage C
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesC =
        GFlowPlans::FamilySlots(aLanePlans[2].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsC =
        GFlowPlans::FamilySlots(aLanePlans[2].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesC));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsC));

    printf("at KDF A — Stage C, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF A — Stage C", 8);

    const GPassFactoryMidstage::SlotArray10 aResidualsC = {
        Slot::kSourceLane,
        Slot::kNonceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
    };

    pResidualBucket.AddResiduals(
        "KDF A — Stage C",
        GFlowPlans::FamilySlotVector(aLanePlans[2].mInputs[0]));

    // Stage Construction

    //
    // Build KDF A — Stage A
    //
    GSeedRunStageConfig aConfigA = GSeedRunKDFCommon::BaseConfig("GSeedRunKDF_A_A",
                                              "kdf_a_loop_a",
                                              GAXSFormat::kN11);
    aConfigA.mSlices =
        GPassFactoryStarter::KDF_A_AStarterSlices(aPrimarySourcesA,
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
        printf("MakeKDF_AConfig stage A was not valid with ValidateStarter");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigA.SetLaneFlow(aPrimarySourcesA, aDestinationsA);
    aConfigs[0] = aConfigA;

    //
    // Build and validate KDF A — Stage B
    //
    GSeedRunStageConfig aConfigB = GSeedRunKDFCommon::BaseConfig("GSeedRunKDF_A_B",
                                              "kdf_a_loop_b",
                                              GAXSFormat::kN11);
    aConfigB.mSlices =
        GPassFactoryMidstage::FourPassTwoResidualSlices(aPrimarySourcesB,
                                                        aResidualsB,
                                                        aDestinationsB);
    aConfigB.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsB.size());
    aConfigB.mHotPackCount =
        static_cast<int>(aDestinationsB.size());

    std::string aErrorMessageB;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigB,
            GPassFactoryMidstage::ToVector(aPrimarySourcesB),
            GPassFactoryMidstage::ToVector(aResidualsB),
            GPassFactoryMidstage::ToVector(aDestinationsB),
            &aErrorMessageB)) {
        printf("MakeKDF_AConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigB.SetLaneFlow(aPrimarySourcesB, aDestinationsB);
    aConfigs[1] = aConfigB;

    //
    // Build and validate KDF A — Stage C
    //
    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesC =
        ArrangementFour::Arrange(aPrimarySourcesC,
                                 static_cast<int>(pCandidateIndex),
                                 aLanePlans[2].mArrangementOffset);

    GSeedRunStageConfig aConfigC = GSeedRunKDFCommon::BaseConfig("GSeedRunKDF_A_C",
                                              "kdf_a_loop_c",
                                              GAXSFormat::kN11);
    aConfigC.mSlices =
        GPassFactoryTrunk::FourPassTrunkSlices(aArrangedPrimarySourcesC,
                                               aResidualsC,
                                               aDestinationsC);
    aConfigC.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsC.size());
    aConfigC.mHotPackCount =
        static_cast<int>(aDestinationsC.size());

    std::string aErrorMessageC;
    if (!GSeedRunStageConfigValidator::ValidateTrunk(
            aConfigC,
            GPassFactoryMidstage::ToVector(aArrangedPrimarySourcesC),
            GPassFactoryMidstage::ToVector(aResidualsC),
            GPassFactoryMidstage::ToVector(aDestinationsC),
            &aErrorMessageC)) {
        printf("MakeKDF_AConfig stage C was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigC.SetLaneFlow(aPrimarySourcesC, aDestinationsC);
    aConfigs[2] = aConfigC;

    return aConfigs;
}

} // namespace GSeedRunKDF_AConfig

GSeedRunKDF_A::GSeedRunKDF_A(const GSeedRunStageConfig &pConfig,
                             const bool pEmitPrologue)
: mStage(pConfig),
  mEmitPrologue(pEmitPrologue) {
}

bool GSeedRunKDF_A::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_A::Build(TwistProgramBranch &pBranch,
                          std::string *pErrorMessage) {
    if (mEmitPrologue) {
        GSeedRunKDFCommon::AddPrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
