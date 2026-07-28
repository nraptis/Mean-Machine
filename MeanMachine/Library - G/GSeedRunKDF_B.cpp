//
//  GSeedRunKDF_B.cpp
//  MeanMachine
//

#include "GSeedRunKDF_B.hpp"
#include "GPassFactory.hpp"
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
    aConfig.mHasDomainMix = true;
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
    pBranch.AddLine("// [kdf-b]");
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

}


// [poi-a] x 3, [poi-b] x 3, [poi-c] x 2, [poi-d] x 2
// [ear-a] x 2, [ear-b] x 2, [ear-c] x 2, [ear-d] x 2
// [fir-a] x 1, [fir-b] x 1, [fir-c] x 1, [fir-d] x 1
// [win-a] x 0, [win-b] x 0, [win-c] x 0, [win-d] x 0

} // namespace

namespace GSeedRunKDF_BConfig {

KDFStageConfigs MakeKDF_BConfig(ResidualBucket &pResidualBucket) {
    using Slot = TwistWorkSpaceSlot;

    KDFStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    //
    // KDF B — Stage A
    //
    const GPassFactory::SlotArray4 aPrimarySourcesA = {
        Slot::kHeartLaneA,
        Slot::kHeartLaneB,
        Slot::kHeartLaneC,
        Slot::kHeartLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsA = {
        Slot::kSoilLaneA,
        Slot::kSoilLaneB,
        Slot::kSoilLaneC,
        Slot::kSoilLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsA));

    printf("at KDF B — Stage A, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF B — Stage A", 14);

    const GPassFactory::SlotArray16 aResidualsA = {
        Slot::kSource, Slot::kParamSnow,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
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
    const GPassFactory::SlotArray4 aPrimarySourcesB = {
        Slot::kSoilLaneA,
        Slot::kSoilLaneB,
        Slot::kSoilLaneC,
        Slot::kSoilLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsB = {
        Slot::kLightningLaneA,
        Slot::kLightningLaneB,
        Slot::kLightningLaneC,
        Slot::kLightningLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesB));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsB));

    printf("at KDF B — Stage B, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF B — Stage B", 14);

    const GPassFactory::SlotArray16 aResidualsB = {
        Slot::kSource, Slot::kParamSnow,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
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
    const GPassFactory::SlotArray4 aPrimarySourcesC = {
        Slot::kLightningLaneA,
        Slot::kLightningLaneB,
        Slot::kLightningLaneC,
        Slot::kLightningLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA,
        Slot::kFuseLaneB,
        Slot::kFuseLaneC,
        Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesC));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsC));

    printf("at KDF B — Stage C, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF B — Stage C", 14);

    const GPassFactory::SlotArray16 aResidualsC = {
        Slot::kSource, Slot::kParamSnow,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
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
    const GPassFactory::SlotArray4 aPrimarySourcesD = {
        Slot::kIceLaneA,
        Slot::kIceLaneB,
        Slot::kIceLaneC,
        Slot::kIceLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsD = {
        Slot::kWoodLaneA,
        Slot::kWoodLaneB,
        Slot::kWoodLaneC,
        Slot::kWoodLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesD));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsD));

    printf("at KDF B — Stage D, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF B — Stage D", 14);

    const GPassFactory::SlotArray16 aResidualsD = {
        Slot::kSource, Slot::kParamSnow,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
    };

    pResidualBucket.AddResiduals("KDF B — Stage D", {
        Slot::kIceLaneA,
        Slot::kIceLaneB,
        Slot::kIceLaneC,
        Slot::kIceLaneD,
    });

    //
    // Build and validate KDF B — Stage A
    //
    GSeedRunStageConfig aConfigA = BaseConfig("GSeedRunKDF_B_A",
                                              "kdf_b_loop_a",
                                              GAXSFormat::kN9);
    aConfigA.mSlices =
        GPassFactory::FourPassSixteenResidualSlices(aPrimarySourcesA,
                                                    aResidualsA,
                                                    aDestinationsA);
    aConfigA.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsA.size());
    aConfigA.mHotPackCount =
        static_cast<int>(aDestinationsA.size());

    std::string aErrorMessageA;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigA,
            GPassFactory::ToVector(aPrimarySourcesA),
            GPassFactory::ToVector(aResidualsA),
            GPassFactory::ToVector(aDestinationsA),
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
                                              GAXSFormat::kN7);
    aConfigB.mSlices =
        GPassFactory::FourPassSixteenResidualSlices(aPrimarySourcesB,
                                                    aResidualsB,
                                                    aDestinationsB);
    aConfigB.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsB.size());
    aConfigB.mHotPackCount =
        static_cast<int>(aDestinationsB.size());

    std::string aErrorMessageB;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigB,
            GPassFactory::ToVector(aPrimarySourcesB),
            GPassFactory::ToVector(aResidualsB),
            GPassFactory::ToVector(aDestinationsB),
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
        GPassFactory::FourPassSixteenResidualSlices(aPrimarySourcesC,
                                                    aResidualsC,
                                                    aDestinationsC);
    aConfigC.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsC.size());
    aConfigC.mHotPackCount =
        static_cast<int>(aDestinationsC.size());

    std::string aErrorMessageC;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigC,
            GPassFactory::ToVector(aPrimarySourcesC),
            GPassFactory::ToVector(aResidualsC),
            GPassFactory::ToVector(aDestinationsC),
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
    GSeedRunStageConfig aConfigD = BaseConfig("GSeedRunKDF_B_D",
                                              "kdf_b_loop_d",
                                              GAXSFormat::kN9);
    aConfigD.mSlices =
        GPassFactory::FourPassSixteenResidualSlices(aPrimarySourcesD,
                                                    aResidualsD,
                                                    aDestinationsD);
    aConfigD.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsD.size());
    aConfigD.mHotPackCount =
        static_cast<int>(aDestinationsD.size());

    std::string aErrorMessageD;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigD,
            GPassFactory::ToVector(aPrimarySourcesD),
            GPassFactory::ToVector(aResidualsD),
            GPassFactory::ToVector(aDestinationsD),
            &aErrorMessageD)) {
        printf("MakeKDF_BConfig stage D was not valid with ValidateMidstage");
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
