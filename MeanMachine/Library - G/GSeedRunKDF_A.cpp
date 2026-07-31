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
#include "ResidualBucket.hpp"

#include <array>

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

void AddKDF_APrologue(TwistProgramBranch &pBranch) {
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

namespace GSeedRunKDF_AConfig {

KDFStageConfigs MakeKDF_AConfig(ResidualBucket &pResidualBucket,
                                const std::size_t pCandidateIndex) {
    using Slot = TwistWorkSpaceSlot;
    KDFStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    // Lane Plan

    //
    // KDF A — Stage A
    //
    const GPassFactoryStarter::SlotArray2 aPrimarySourcesA = {
        Slot::kSourceLane,
        Slot::kNonceLane,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesA = {
        Slot::kFireLaneA, Slot::kFireLaneB,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsA = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsA =
        GPassFactoryMidstage::Concat(aWarmUpLanesA, aDestinationsA);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsA));

    printf("at KDF A — Stage A, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    pResidualBucket.Withdraw("KDF A — Stage A", 0);

    pResidualBucket.AddResiduals("KDF A — Stage A", {
        Slot::kFireLaneA, Slot::kFireLaneB,
    });

    //
    // KDF A — Stage B
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesB = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesB = {
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsB = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsB =
        GPassFactoryMidstage::Concat(aWarmUpLanesB, aDestinationsB);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesB));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsB));

    printf("at KDF A — Stage B, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF A — Stage B", 2);

    const GPassFactoryMidstage::SlotArray4 aResidualsB = {
        Slot::kSourceLane,
        Slot::kNonceLane,
        aResidualsPool[0], aResidualsPool[1],
    };

    pResidualBucket.AddResiduals("KDF A — Stage B", {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
        Slot::kFireLaneC, Slot::kFireLaneD,
    });

    //
    // KDF A — Stage C
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesC = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };

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

    pResidualBucket.AddResiduals("KDF A — Stage C", {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    });

    /*
    TwistDiffuse::DiffuseWithDomainWords(
                    aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
                    aSpiritLaneA, aSpiritLaneB, aSpiritLaneC, aSpiritLaneD, // output lanes
                    aFireLaneC, aFireLaneD, aWindLaneC, aWindLaneD, // index shuffle seeds
                    aWindLaneA, aWindLaneB); // operation seeds
    */

    //
    // KDF A — Stage D
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesD = {
        Slot::kSpiritLaneA, Slot::kSpiritLaneB,
        Slot::kSpiritLaneC, Slot::kSpiritLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsD = {
        Slot::kHeartLaneA, Slot::kHeartLaneB,
        Slot::kHeartLaneC, Slot::kHeartLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesD));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsD));

    printf("at KDF A — Stage D, there were %zu residuals available\n",
           pResidualBucket.CountValidResiduals());

    aResidualsPool = pResidualBucket.Withdraw("KDF A — Stage D", 12);

    const GPassFactoryMidstage::SlotArray14 aResidualsD = {
        Slot::kSourceLane,
        Slot::kNonceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
    };

    pResidualBucket.AddResiduals("KDF A — Stage D", {
        Slot::kSpiritLaneA, Slot::kSpiritLaneB,
        Slot::kSpiritLaneC, Slot::kSpiritLaneD,
    });

    // Stage Construction

    //
    // Build KDF A — Stage A
    //
    GSeedRunStageConfig aConfigA = BaseConfig("GSeedRunKDF_A_A",
                                              "kdf_a_loop_a",
                                              GAXSFormat::kN11);
    aConfigA.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesA.size());
    aConfigA.mUsesSpecialSixPassStarterGraph = true;
    aConfigA.mSlices =
        GPassFactoryStarter::KDF_A_AStarterSlices(aPrimarySourcesA,
                                                  aWarmUpLanesA,
                                                  aDestinationsA,
                                                  pCandidateIndex);
    aConfigA.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsA.size());
    aConfigA.mHotPackCount =
        static_cast<int>(aExpectedDestinationsA.size());

    std::string aErrorMessageA;
    if (!GSeedRunStageConfigValidator::ValidateStarter(
            aConfigA,
            GPassFactoryMidstage::ToVector(aPrimarySourcesA),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsA),
            &aErrorMessageA)) {
        printf("MakeKDF_AConfig stage A was not valid with ValidateStarter");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigs[0] = aConfigA;

    //
    // Build and validate KDF A — Stage B
    //
    GSeedRunStageConfig aConfigB = BaseConfig("GSeedRunKDF_A_B",
                                              "kdf_a_loop_b",
                                              GAXSFormat::kN9);
    aConfigB.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesB.size());
    aConfigB.mSlices =
        GPassFactoryMidstage::SixPassFourResidualSlices(aPrimarySourcesB,
                                                 aResidualsB,
                                                 aExpectedDestinationsB);
    aConfigB.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsB.size());
    aConfigB.mHotPackCount =
        static_cast<int>(aExpectedDestinationsB.size());

    std::string aErrorMessageB;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigB,
            GPassFactoryMidstage::ToVector(aPrimarySourcesB),
            GPassFactoryMidstage::ToVector(aResidualsB),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsB),
            &aErrorMessageB)) {
        printf("MakeKDF_AConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigs[1] = aConfigB;

    //
    // Build and validate KDF A — Stage C
    //
    GSeedRunStageConfig aConfigC = BaseConfig("GSeedRunKDF_A_C",
                                              "kdf_a_loop_c",
                                              GAXSFormat::kN7);
    aConfigC.mSlices =
        GPassFactoryMidstage::FourPassTenResidualSlices(aPrimarySourcesC,
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
        printf("MakeKDF_AConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;

    //
    // Build and validate KDF A — Stage D
    //
    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesD =
        ArrangementFour::Arrange(aPrimarySourcesD,
                                 static_cast<int>(pCandidateIndex),
                                 7);

    GSeedRunStageConfig aConfigD = BaseConfig("GSeedRunKDF_A_D",
                                              "kdf_a_loop_d",
                                              GAXSFormat::kN9);
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
        printf("MakeKDF_AConfig stage D was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigs[3] = aConfigD;

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
        AddKDF_APrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
