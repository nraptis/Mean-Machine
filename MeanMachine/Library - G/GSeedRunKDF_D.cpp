//
//  GSeedRunKDF_D.cpp
//  MeanMachine
//

#include "GSeedRunKDF_D.hpp"
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

void AddKDF_DPrologue(TwistProgramBranch &pBranch) {
    pBranch.AddLine("// [kdf-d]");
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

namespace GSeedRunKDF_DConfig {

KDFStageConfigs MakeKDF_DConfig(ResidualBucket &pResidualBucket) {
    using Slot = TwistWorkSpaceSlot;

    KDFStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    //
    // KDF D — Stage A
    //
    const GPassFactory::SlotArray4 aPrimarySourcesA = {
        Slot::kCrystalLaneA,
        Slot::kCrystalLaneB,
        Slot::kCrystalLaneC,
        Slot::kCrystalLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsA = {
        Slot::kAetherLaneA,
        Slot::kAetherLaneB,
        Slot::kAetherLaneC,
        Slot::kAetherLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsA));

    printf("at KDF D — Stage A, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF D — Stage A", 14);

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

    pResidualBucket.AddResiduals("KDF D — Stage A", {
        Slot::kCrystalLaneA,
        Slot::kCrystalLaneB,
        Slot::kCrystalLaneC,
        Slot::kCrystalLaneD,
    });

    //
    // KDF D — Stage B
    //
    const GPassFactory::SlotArray4 aPrimarySourcesB = {
        Slot::kAetherLaneA,
        Slot::kAetherLaneB,
        Slot::kAetherLaneC,
        Slot::kAetherLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsB = {
        Slot::kCelestialLaneA,
        Slot::kCelestialLaneB,
        Slot::kCelestialLaneC,
        Slot::kCelestialLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesB));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsB));

    printf("at KDF D — Stage B, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF D — Stage B", 14);

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

    pResidualBucket.AddResiduals("KDF D — Stage B", {
        Slot::kAetherLaneA,
        Slot::kAetherLaneB,
        Slot::kAetherLaneC,
        Slot::kAetherLaneD,
    });

    //
    // KDF D — Stage C
    //
    const GPassFactory::SlotArray4 aPrimarySourcesC = {
        Slot::kCelestialLaneA,
        Slot::kCelestialLaneB,
        Slot::kCelestialLaneC,
        Slot::kCelestialLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA,
        Slot::kFuseLaneB,
        Slot::kFuseLaneC,
        Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesC));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsC));

    printf("at KDF D — Stage C, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF D — Stage C", 14);

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

    pResidualBucket.AddResiduals("KDF D — Stage C", {
        Slot::kCelestialLaneA,
        Slot::kCelestialLaneB,
        Slot::kCelestialLaneC,
        Slot::kCelestialLaneD,
    });

    /*
    TwistDiffuse::DiffuseWithDomainWords(
                aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
                aVaporLaneA, aVaporLaneB, aVaporLaneC, aVaporLaneD, // output lanes
                aAetherLaneC, aAetherLaneD, aCelestialLaneC, aCelestialLaneD, // index shuffle seeds
                aCelestialLaneA, aCelestialLaneB); // operation seeds
    */

    //
    // KDF D — Stage D
    //
    const GPassFactory::SlotArray4 aPrimarySourcesD = {
        Slot::kVaporLaneA,
        Slot::kVaporLaneB,
        Slot::kVaporLaneC,
        Slot::kVaporLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsD = {
        Slot::kPoisonLaneA,
        Slot::kPoisonLaneB,
        Slot::kPoisonLaneC,
        Slot::kPoisonLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesD));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsD));

    printf("at KDF D — Stage D, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF D — Stage D", 14);

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

    pResidualBucket.AddResiduals("KDF D — Stage D", {
        Slot::kVaporLaneA,
        Slot::kVaporLaneB,
        Slot::kVaporLaneC,
        Slot::kVaporLaneD,
    });

    //
    // Build and validate KDF D — Stage A
    //
    GSeedRunStageConfig aConfigA = BaseConfig("GSeedRunKDF_D_A",
                                              "kdf_d_loop_a",
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
        printf("MakeKDF_DConfig stage A was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigs[0] = aConfigA;

    //
    // Build and validate KDF D — Stage B
    //
    GSeedRunStageConfig aConfigB = BaseConfig("GSeedRunKDF_D_B",
                                              "kdf_d_loop_b",
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
        printf("MakeKDF_DConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigs[1] = aConfigB;

    //
    // Build and validate KDF D — Stage C
    //
    GSeedRunStageConfig aConfigC = BaseConfig("GSeedRunKDF_D_C",
                                              "kdf_d_loop_c",
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
        printf("MakeKDF_DConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;

    //
    // Build and validate KDF D — Stage D
    //
    GSeedRunStageConfig aConfigD = BaseConfig("GSeedRunKDF_D_D",
                                              "kdf_d_loop_d",
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
        printf("MakeKDF_DConfig stage D was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigs[3] = aConfigD;

    return aConfigs;
}

} // namespace GSeedRunKDF_DConfig

GSeedRunKDF_D::GSeedRunKDF_D(
    const GSeedRunStageConfig &pConfig,
    const bool pEmitPrologue)
: mStage(pConfig),
  mEmitPrologue(pEmitPrologue) {
}

bool GSeedRunKDF_D::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_D::Build(TwistProgramBranch &pBranch,
                          std::string *pErrorMessage) {
    if (mEmitPrologue) {
        AddKDF_DPrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
