//
//  GSeedRunKDF_C.cpp
//  MeanMachine
//

#include "GSeedRunKDF_C.hpp"
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

void AddKDF_CPrologue(TwistProgramBranch &pBranch) {
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

namespace GSeedRunKDF_CConfig {

KDFStageConfigs MakeKDF_CConfig(ResidualBucket &pResidualBucket,
                                const std::size_t pCandidateIndex) {
    using Slot = TwistWorkSpaceSlot;

    KDFStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    // Lane Plan

    //
    // KDF C — Stage A
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesA = {
        Slot::kWoodLaneA,
        Slot::kWoodLaneB,
        Slot::kWoodLaneC,
        Slot::kWoodLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsA = {
        Slot::kMagmaLaneA,
        Slot::kMagmaLaneB,
        Slot::kMagmaLaneC,
        Slot::kMagmaLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsA));

    printf("at KDF C — Stage A, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF C — Stage A", 15);

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

    pResidualBucket.AddResiduals("KDF C — Stage A", {
        Slot::kWoodLaneA,
        Slot::kWoodLaneB,
        Slot::kWoodLaneC,
        Slot::kWoodLaneD,
    });

    //
    // KDF C — Stage B
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesB = {
        Slot::kMagmaLaneA,
        Slot::kMagmaLaneB,
        Slot::kMagmaLaneC,
        Slot::kMagmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsB = {
        Slot::kPlasmaLaneA,
        Slot::kPlasmaLaneB,
        Slot::kPlasmaLaneC,
        Slot::kPlasmaLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesB));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsB));

    printf("at KDF C — Stage B, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF C — Stage B", 15);

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

    pResidualBucket.AddResiduals("KDF C — Stage B", {
        Slot::kMagmaLaneA,
        Slot::kMagmaLaneB,
        Slot::kMagmaLaneC,
        Slot::kMagmaLaneD,
    });

    //
    // KDF C — Stage C
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesC = {
        Slot::kPlasmaLaneA,
        Slot::kPlasmaLaneB,
        Slot::kPlasmaLaneC,
        Slot::kPlasmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA,
        Slot::kFuseLaneB,
        Slot::kFuseLaneC,
        Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesC));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsC));

    printf("at KDF C — Stage C, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF C — Stage C", 15);

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

    pResidualBucket.AddResiduals("KDF C — Stage C", {
        Slot::kPlasmaLaneA,
        Slot::kPlasmaLaneB,
        Slot::kPlasmaLaneC,
        Slot::kPlasmaLaneD,
    });

    /*
    TwistDiffuse::DiffuseWithDomainWords(
                    aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
                    aShadowLaneA, aShadowLaneB, aShadowLaneC, aShadowLaneD, // output lanes
                    aMagmaLaneC, aMagmaLaneD, aPlasmaLaneC, aPlasmaLaneD, // index shuffle seeds
                    aPlasmaLaneA, aPlasmaLaneB);  // operation seeds
    */
    
    //
    // KDF C — Stage D
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesD = {
        Slot::kShadowLaneA,
        Slot::kShadowLaneB,
        Slot::kShadowLaneC,
        Slot::kShadowLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsD = {
        Slot::kCrystalLaneA,
        Slot::kCrystalLaneB,
        Slot::kCrystalLaneC,
        Slot::kCrystalLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesD));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsD));

    printf("at KDF C — Stage D, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF C — Stage D", 15);

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

    pResidualBucket.AddResiduals("KDF C — Stage D", {
        Slot::kShadowLaneA,
        Slot::kShadowLaneB,
        Slot::kShadowLaneC,
        Slot::kShadowLaneD,
    });

    // Stage Construction

    //
    // Build and validate KDF C — Stage A
    //
    GSeedRunStageConfig aConfigA = BaseConfig("GSeedRunKDF_C_A",
                                              "kdf_c_loop_a",
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
        printf("MakeKDF_CConfig stage A was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigs[0] = aConfigA;

    //
    // Build and validate KDF C — Stage B
    //
    GSeedRunStageConfig aConfigB = BaseConfig("GSeedRunKDF_C_B",
                                              "kdf_c_loop_b",
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
        printf("MakeKDF_CConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigs[1] = aConfigB;

    //
    // Build and validate KDF C — Stage C
    //
    GSeedRunStageConfig aConfigC = BaseConfig("GSeedRunKDF_C_C",
                                              "kdf_c_loop_c",
                                              GAXSFormat::kN9);
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
        printf("MakeKDF_CConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;

    //
    // Build and validate KDF C — Stage D
    //
    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesD =
        ArrangementFour::Arrange(aPrimarySourcesD,
                                 static_cast<int>(pCandidateIndex),
                                 12);

    GSeedRunStageConfig aConfigD = BaseConfig("GSeedRunKDF_C_D",
                                              "kdf_c_loop_d",
                                              GAXSFormat::kN11);
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
        printf("MakeKDF_CConfig stage D was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigs[3] = aConfigD;

    return aConfigs;
}

} // namespace GSeedRunKDF_CConfig

GSeedRunKDF_C::GSeedRunKDF_C(
    const GSeedRunStageConfig &pConfig,
    const bool pEmitPrologue)
: mStage(pConfig),
  mEmitPrologue(pEmitPrologue) {
}

bool GSeedRunKDF_C::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_C::Build(TwistProgramBranch &pBranch,
                          std::string *pErrorMessage) {
    if (mEmitPrologue) {
        AddKDF_CPrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
