//
//  GSeedRunKDF_B.cpp
//  MeanMachine
//

#include "GSeedRunKDF_B.hpp"
#include "ArrangementFour.hpp"
#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryTrunk.hpp"
#include "GSeedRunStageConfigValidator.hpp"
#include "ResidualBucket.hpp"

namespace {

std::vector<TwistWorkSpaceSlot> ParamOrbiterAssignSalts() {
    using Slot = TwistWorkSpaceSlot;
    return {
        Slot::kParamDomainSaltOrbiterAssignA,
        Slot::kParamDomainSaltOrbiterAssignB,
        Slot::kParamDomainSaltOrbiterAssignC,
        Slot::kParamDomainSaltOrbiterAssignD,
        Slot::kParamDomainSaltOrbiterAssignE,
        Slot::kParamDomainSaltOrbiterAssignF,
        Slot::kParamDomainSaltOrbiterAssignG,
        Slot::kParamDomainSaltOrbiterAssignH,
    };
}

std::vector<TwistWorkSpaceSlot> ParamOrbiterUpdateSalts() {
    using Slot = TwistWorkSpaceSlot;
    return {
        Slot::kParamDomainSaltOrbiterUpdateA,
        Slot::kParamDomainSaltOrbiterUpdateB,
        Slot::kParamDomainSaltOrbiterUpdateC,
        Slot::kParamDomainSaltOrbiterUpdateD,
        Slot::kParamDomainSaltOrbiterUpdateE,
        Slot::kParamDomainSaltOrbiterUpdateF,
        Slot::kParamDomainSaltOrbiterUpdateG,
        Slot::kParamDomainSaltOrbiterUpdateH,
    };
}

std::vector<TwistWorkSpaceSlot> ParamWandererUpdateSalts() {
    using Slot = TwistWorkSpaceSlot;
    return {
        Slot::kParamDomainSaltWandererUpdateA,
        Slot::kParamDomainSaltWandererUpdateB,
        Slot::kParamDomainSaltWandererUpdateC,
        Slot::kParamDomainSaltWandererUpdateD,
        Slot::kParamDomainSaltWandererUpdateE,
        Slot::kParamDomainSaltWandererUpdateF,
        Slot::kParamDomainSaltWandererUpdateG,
        Slot::kParamDomainSaltWandererUpdateH,
    };
}

GSeedRunStageConfig BaseConfig(const std::string &pStageName,
                               const std::string &pBatchName,
                               GAXSFormat pFormat) {
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pBatchName;
    aConfig.mStartLine = "// " + pStageName + " " + pBatchName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + pBatchName + " (end)";
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = false;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    return aConfig;
}

void AddKDF_BPrologue(TwistProgramBranch &pBranch) {
    pBranch.AddLine("std::uint64_t aDomainWordIngress = pConstants->mIngress;");
    pBranch.AddLine("std::uint64_t aDomainWordScatter = pConstants->mScatter;");
    pBranch.AddLine("std::uint64_t aDomainWordCross = pConstants->mCross;");
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;");
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;");
    pBranch.AddLine("");
}

} // namespace

namespace GSeedRunKDF_BConfig {

KDFStageConfigs MakeKDF_BConfig(ResidualBucket &pResidualBucket,
                                const std::size_t pCandidateIndex) {
    using Slot = TwistWorkSpaceSlot;

    KDFStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    // Lane Plan

    //
    // KDF B — Stage A
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesA = {
        Slot::kHeartLaneA,
        Slot::kHeartLaneB,
        Slot::kHeartLaneC,
        Slot::kHeartLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsA = {
        Slot::kSoilLaneA,
        Slot::kSoilLaneB,
        Slot::kSoilLaneC,
        Slot::kSoilLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsA));

    printf("at KDF B — Stage A, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF B — Stage A", 15);

    const GPassFactoryMidstage::SlotArray16 aResidualsA = {
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

    pResidualBucket.AddResiduals("KDF B — Stage A", {
        Slot::kHeartLaneA,
        Slot::kHeartLaneB,
        Slot::kHeartLaneC,
        Slot::kHeartLaneD,
    });

    //
    // KDF B — Stage B
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesB = {
        Slot::kSoilLaneA,
        Slot::kSoilLaneB,
        Slot::kSoilLaneC,
        Slot::kSoilLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsB = {
        Slot::kLightningLaneA,
        Slot::kLightningLaneB,
        Slot::kLightningLaneC,
        Slot::kLightningLaneD,
    };

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

    pResidualBucket.AddResiduals("KDF B — Stage B", {
        Slot::kSoilLaneA,
        Slot::kSoilLaneB,
        Slot::kSoilLaneC,
        Slot::kSoilLaneD,
    });

    //
    // KDF B — Stage C
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesC = {
        Slot::kLightningLaneA,
        Slot::kLightningLaneB,
        Slot::kLightningLaneC,
        Slot::kLightningLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA,
        Slot::kFuseLaneB,
        Slot::kFuseLaneC,
        Slot::kFuseLaneD,
    };

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

    pResidualBucket.AddResiduals("KDF B — Stage C", {
        Slot::kLightningLaneA,
        Slot::kLightningLaneB,
        Slot::kLightningLaneC,
        Slot::kLightningLaneD,
    });

    //
    // Matrix diffusion: Fuse lanes -> Ice lanes
    //

    //
    // KDF B — Stage D
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesD = {
        Slot::kIceLaneA,
        Slot::kIceLaneB,
        Slot::kIceLaneC,
        Slot::kIceLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsD = {
        Slot::kWoodLaneA,
        Slot::kWoodLaneB,
        Slot::kWoodLaneC,
        Slot::kWoodLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesD));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsD));

    printf("at KDF B — Stage D, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF B — Stage D", 15);

    const GPassFactoryMidstage::SlotArray16 aResidualsD = {
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

    pResidualBucket.AddResiduals("KDF B — Stage D", {
        Slot::kIceLaneA,
        Slot::kIceLaneB,
        Slot::kIceLaneC,
        Slot::kIceLaneD,
    });

    // Stage Construction

    //
    // Build and validate KDF B — Stage A
    //
    GSeedRunStageConfig aConfigA = BaseConfig("GSeedRunKDF_B_A",
                                              "kdf_b_loop_a",
                                              GAXSFormat::kN7);
    aConfigA.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(aPrimarySourcesA,
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
    aConfigs[0] = aConfigA;

    //
    // Build and validate KDF B — Stage B
    //
    GSeedRunStageConfig aConfigB = BaseConfig("GSeedRunKDF_B_B",
                                              "kdf_b_loop_b",
                                              GAXSFormat::kN9);
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
    aConfigs[1] = aConfigB;

    //
    // Build and validate KDF B — Stage C
    //
    GSeedRunStageConfig aConfigC = BaseConfig("GSeedRunKDF_B_C",
                                              "kdf_b_loop_c",
                                              GAXSFormat::kN11);
    aConfigC.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(aPrimarySourcesC,
                                                    aResidualsC,
                                                    aDestinationsC);
    aConfigC.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsC.size());
    aConfigC.mHotPackCount =
        static_cast<int>(aDestinationsC.size());

    std::string aErrorMessageC;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigC,
            GPassFactoryMidstage::ToVector(aPrimarySourcesC),
            GPassFactoryMidstage::ToVector(aResidualsC),
            GPassFactoryMidstage::ToVector(aDestinationsC),
            &aErrorMessageC)) {
        printf("MakeKDF_BConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;
    
    /*
    TwistDiffuse::DiffuseWithDomainWords(
                aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
                aIceLaneA, aIceLaneB, aIceLaneC, aIceLaneD, // output lanes
                aSoilLaneC, aSoilLaneD, aLightningLaneC, aLightningLaneD, // index shuffle seeds
                aLightningLaneA, aLightningLaneB); // operation seeds
    */
     
    //
    // Build and validate KDF B — Stage D
    //
    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesD =
        ArrangementFour::Arrange(aPrimarySourcesD,
                                 static_cast<int>(pCandidateIndex),
                                 1);

    GSeedRunStageConfig aConfigD = BaseConfig("GSeedRunKDF_B_D",
                                              "kdf_b_loop_d",
                                              GAXSFormat::kN7);
    aConfigD.mSlices =
        GPassFactoryTrunk::FourPassTrunkSlices(aArrangedPrimarySourcesD,
                                          aResidualsD,
                                          aDestinationsD);
    aConfigD.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsD.size());
    aConfigD.mHotPackCount =
        static_cast<int>(aDestinationsD.size());

    std::string aErrorMessageD;
    if (!GSeedRunStageConfigValidator::ValidateTrunk(
            aConfigD,
            GPassFactoryMidstage::ToVector(aArrangedPrimarySourcesD),
            GPassFactoryMidstage::ToVector(aResidualsD),
            GPassFactoryMidstage::ToVector(aDestinationsD),
            &aErrorMessageD)) {
        printf("MakeKDF_BConfig stage D was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigs[3] = aConfigD;

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
        AddKDF_BPrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
