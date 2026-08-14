//
//  GSeedRunKDF_B.cpp
//  MeanMachine
//

#include "GSeedRunKDF_B.hpp"
#include "ArrangementFour.hpp"
#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryTrunk.hpp"
#include "GSeedRunStageConfigValidator.hpp"
#include "GSeedRunKDFCommon.hpp"
#include "GFlowPlans.hpp"
#include "ResidualBucket.hpp"

namespace GSeedRunKDF_BConfig {

KDFStageConfigs MakeKDF_BConfig(ResidualBucket &pResidualBucket,
                                const std::size_t pCandidateIndex) {
    using Slot = TwistWorkSpaceSlot;

    KDFStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    // Lane Plan
    const std::vector<GFlowStep> aLanePlans =
        GFlowPlans::ARXSteps(GFlowPlans::KDFB());

    //
    // KDF B — Stage A
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesA =
        GFlowPlans::FamilySlots(aLanePlans[0].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsA =
        GFlowPlans::FamilySlots(aLanePlans[0].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsA));

    printf("at KDF B — Stage A, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF B — Stage A", 12);

    const GPassFactoryMidstage::SlotArray13 aResidualsA = {
        Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
    };

    pResidualBucket.AddResiduals(
        "KDF B — Stage A",
        GFlowPlans::FamilySlotVector(aLanePlans[0].mInputs[0]));

    //
    // KDF B — Stage B
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesB =
        GFlowPlans::FamilySlots(aLanePlans[1].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsB =
        GFlowPlans::FamilySlots(aLanePlans[1].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesB));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsB));

    printf("at KDF B — Stage B, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF B — Stage B", 15);

    const GPassFactoryMidstage::SlotArray16 aResidualsB = {
        Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14],
    };

    pResidualBucket.AddResiduals(
        "KDF B — Stage B",
        GFlowPlans::FamilySlotVector(aLanePlans[1].mInputs[0]));

    pResidualBucket.AddResiduals(
        "KDF B — After diffusion",
        GFlowPlans::FamilySlotVector(aLanePlans[1].mOutput));

    //
    // KDF B — Stage C
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesC =
        GFlowPlans::FamilySlots(aLanePlans[2].mInputs[0]);
    const GPassFactoryMidstage::SlotArray4 aDestinationsC =
        GFlowPlans::FamilySlots(aLanePlans[2].mOutput);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesC));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsC));

    printf("at KDF B — Stage C, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF B — Stage C", 15);

    const GPassFactoryMidstage::SlotArray16 aResidualsC = {
        Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14],
    };

    pResidualBucket.AddResiduals(
        "KDF B — Stage C",
        GFlowPlans::FamilySlotVector(aLanePlans[2].mInputs[0]));

    // Stage Construction

    //
    // Build and validate KDF B — Stage A
    //
    GSeedRunStageConfig aConfigA = GSeedRunKDFCommon::BaseConfig("GSeedRunKDF_B_A",
                                              "kdf_b_loop_a",
                                              GAXSFormat::kN11);
    aConfigA.mSlices =
        GPassFactoryMidstage::FourPassThirteenResidualSlices(aPrimarySourcesA,
                                                             aResidualsA,
                                                             aDestinationsA);
    aConfigA.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsA.size());
    aConfigA.mHotPackCount =
        static_cast<int>(aDestinationsA.size());

    std::string aErrorMessageA;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigA,
            GPassFactoryMidstage::ToVector(aPrimarySourcesA),
            GPassFactoryMidstage::ToVector(aResidualsA),
            GPassFactoryMidstage::ToVector(aDestinationsA),
            &aErrorMessageA)) {
        printf("MakeKDF_BConfig stage A was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigA.SetLaneFlow(aPrimarySourcesA, aDestinationsA);
    aConfigs[0] = aConfigA;

    //
    // Build and validate KDF B — Stage B
    //
    GSeedRunStageConfig aConfigB = GSeedRunKDFCommon::BaseConfig("GSeedRunKDF_B_B",
                                              "kdf_b_loop_b",
                                              GAXSFormat::kN11);
    aConfigB.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(aPrimarySourcesB,
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
        printf("MakeKDF_BConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigB.SetLaneFlow(aPrimarySourcesB, aDestinationsB);
    aConfigs[1] = aConfigB;

    //
    // Build and validate KDF B — Stage C
    //
    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesC =
        ArrangementFour::Arrange(aPrimarySourcesC,
                                 static_cast<int>(pCandidateIndex),
                                 aLanePlans[2].mArrangementOffset);

    GSeedRunStageConfig aConfigC = GSeedRunKDFCommon::BaseConfig("GSeedRunKDF_B_C",
                                              "kdf_b_loop_c",
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
        printf("MakeKDF_BConfig stage C was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigC.SetLaneFlow(aPrimarySourcesC, aDestinationsC);
    aConfigs[2] = aConfigC;

    return aConfigs;
}

} // namespace GSeedRunKDF_BConfig

GSeedRunKDF_B::GSeedRunKDF_B(
    const GSeedRunStageConfig &pConfig,
    const bool pEmitPrologue)
: mStage(pConfig),
  mEmitPrologue(pEmitPrologue) {
}

bool GSeedRunKDF_B::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_B::Build(TwistProgramBranch &pBranch,
                          std::string *pErrorMessage) {
    if (mEmitPrologue) {
        GSeedRunKDFCommon::AddPrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
