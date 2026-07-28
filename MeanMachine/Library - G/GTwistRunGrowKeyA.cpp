//
//  GTwistRunGrowKeyA.cpp
//  MeanMachine
//

#include "GTwistRunGrowKeyA.hpp"
#include "GPassFactory.hpp"
#include "GSeedRunStageConfigValidator.hpp"
#include "ResidualBucket.hpp"

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
    const int aOffset = PhaseIndex(pDomain) * 18;

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
    constexpr TwistDomain kDomain = TwistDomain::kKeyRotateA;

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pLoopName;
    aConfig.mStartLine = "// " + pStageName + " " + pLoopName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + pLoopName + " (end)";
    
    aConfig.mIgnoreNonces = true;
    aConfig.mHasDomainMix = false;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = kDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterAssignA, 6);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterUpdateA, 6);
    aConfig.mSaltsWandererUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltWandererUpdateA, 6);
    return aConfig;
}

} // namespace

namespace GTwistRunGrowKeyAConfig {

GrowStageConfigs MakeGrowAConfig(ResidualBucket &pResidualBucket) {
    using Slot = TwistWorkSpaceSlot;

    GrowStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    //
    // Grow A — Stage A
    //
    const GPassFactory::SlotArray4 aInputsA = {
        Slot::kPoisonLaneA, Slot::kPoisonLaneB,
        Slot::kPoisonLaneC, Slot::kPoisonLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsA = {
        Slot::kShadowLaneA, Slot::kShadowLaneB,
        Slot::kShadowLaneC, Slot::kShadowLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aInputsA));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsA));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow A — Stage A", 16); // plus two fixed key rows

    const GPassFactory::SlotArray18 aResidualsA = {
        Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14], aResidualsPool[15],
    };

    pResidualBucket.AddResiduals("Grow A — Stage A", {
        Slot::kPoisonLaneA, Slot::kPoisonLaneB,
        Slot::kPoisonLaneC, Slot::kPoisonLaneD,
    });

    GSeedRunStageConfig aConfigA = BaseConfig("GROW_A_A",
                                              "grow_a_loop_a");
    aConfigA.mFormat = GAXSFormat::kN7;
    aConfigA.mSlices =
        GPassFactory::FourPassEighteenResidualSlices(aInputsA,
                                                     aResidualsA,
                                                     aDestinationsA);
    aConfigA.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsA.size());
    aConfigA.mHotPackCount =
        static_cast<int>(aDestinationsA.size());

    std::string aErrorMessageA;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigA,
            GPassFactory::ToVector(aInputsA),
            GPassFactory::ToVector(aResidualsA),
            GPassFactory::ToVector(aDestinationsA),
            &aErrorMessageA)) {
        printf("MakeGrowAConfig stage A was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigs[0] = aConfigA;

    //
    // Grow A — Stage B
    //
    const GPassFactory::SlotArray4 aInputsB = {
        Slot::kShadowLaneA, Slot::kShadowLaneB,
        Slot::kShadowLaneC, Slot::kShadowLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsB = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aInputsB));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsB));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow A — Stage B", 16); // plus two fixed key rows

    const GPassFactory::SlotArray18 aResidualsB = {
        Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14], aResidualsPool[15],
    };

    pResidualBucket.AddResiduals("Grow A — Stage B", {
        Slot::kShadowLaneA, Slot::kShadowLaneB,
        Slot::kShadowLaneC, Slot::kShadowLaneD,
    });

    GSeedRunStageConfig aConfigB = BaseConfig("GROW_A_B",
                                              "grow_a_loop_b");
    aConfigB.mFormat = GAXSFormat::kN9;
    aConfigB.mSlices =
        GPassFactory::FourPassEighteenResidualSlices(aInputsB,
                                                     aResidualsB,
                                                     aDestinationsB);
    aConfigB.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsB.size());
    aConfigB.mHotPackCount =
        static_cast<int>(aDestinationsB.size());

    std::string aErrorMessageB;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigB,
            GPassFactory::ToVector(aInputsB),
            GPassFactory::ToVector(aResidualsB),
            GPassFactory::ToVector(aDestinationsB),
            &aErrorMessageB)) {
        printf("MakeGrowAConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigs[1] = aConfigB;

    //
    // Grow A — Stage C
    //
    const GPassFactory::SlotArray4 aInputsC = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aInputsC));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsC));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow A — Stage C", 16); // plus two fixed key rows

    const GPassFactory::SlotArray18 aResidualsC = {
        Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14], aResidualsPool[15],
    };

    pResidualBucket.AddResiduals("Grow A — Stage C", {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    });

    GSeedRunStageConfig aConfigC = BaseConfig("GROW_A_C",
                                              "grow_a_loop_c");
    aConfigC.mFormat = GAXSFormat::kN11;
    aConfigC.mSlices =
        GPassFactory::FourPassEighteenResidualSlices(aInputsC,
                                                     aResidualsC,
                                                     aDestinationsC);
    aConfigC.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsC.size());
    aConfigC.mHotPackCount =
        static_cast<int>(aDestinationsC.size());

    std::string aErrorMessageC;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigC,
            GPassFactory::ToVector(aInputsC),
            GPassFactory::ToVector(aResidualsC),
            GPassFactory::ToVector(aDestinationsC),
            &aErrorMessageC)) {
        printf("MakeGrowAConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;

    // Matrix diffusion:
    //   Fuse A-D -> Vapor A-D
    // Previous six:
    //   Shadow C, Shadow D, Wind A-D

    //
    // Grow A — Stage D
    //
    const GPassFactory::SlotArray4 aInputsD = {
        Slot::kVaporLaneA, Slot::kVaporLaneB,
        Slot::kVaporLaneC, Slot::kVaporLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsD = {
        Slot::kAetherLaneA, Slot::kAetherLaneB,
        Slot::kAetherLaneC, Slot::kAetherLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aInputsD));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsD));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow A — Stage D", 16); // plus two fixed key rows

    const GPassFactory::SlotArray18 aResidualsD = {
        Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14], aResidualsPool[15],
    };

    pResidualBucket.AddResiduals("Grow A — Stage D", {
        Slot::kVaporLaneA, Slot::kVaporLaneB,
        Slot::kVaporLaneC, Slot::kVaporLaneD,
    });

    pResidualBucket.Print("Grow A — Final");

    GSeedRunStageConfig aConfigD = BaseConfig("GROW_A_D",
                                              "grow_a_loop_d");
    aConfigD.mFormat = GAXSFormat::kN7;
    aConfigD.mSlices =
        GPassFactory::FourPassEighteenResidualSlices(aInputsD,
                                                     aResidualsD,
                                                     aDestinationsD);
    aConfigD.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsD.size());
    aConfigD.mHotPackCount =
        static_cast<int>(aDestinationsD.size());

    std::string aErrorMessageD;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigD,
            GPassFactory::ToVector(aInputsD),
            GPassFactory::ToVector(aResidualsD),
            GPassFactory::ToVector(aDestinationsD),
            &aErrorMessageD)) {
        printf("MakeGrowAConfig stage D was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigs[3] = aConfigD;

    return aConfigs;
}

} // namespace GTwistRunGrowKeyAConfig

GTwistRunGrowKeyA::GTwistRunGrowKeyA(ResidualBucket &pResidualBucket)
: mStage(GTwistRunGrowKeyAConfig::MakeGrowAConfig(pResidualBucket)[0]) {
}

GTwistRunGrowKeyA::GTwistRunGrowKeyA(const GSeedRunStageConfig &pConfig,
                                     ResidualBucket &pResidualBucket)
: mStage(pConfig) {
    (void)pResidualBucket;
}

GTwistRunGrowKeyA::~GTwistRunGrowKeyA() {
}

void GTwistRunGrowKeyA::Reset() {
    mStage.Reset();
}

bool GTwistRunGrowKeyA::Plan(std::string *pErrorMessage) {
    Reset();
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunGrowKeyA::Build(TwistProgramBranch &pBranch,
                              std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}
