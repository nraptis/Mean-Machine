//
//  GTwistRunGrowKeyB.cpp
//  MeanMachine
//

#include "GTwistRunGrowKeyB.hpp"
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
    constexpr TwistDomain kDomain = TwistDomain::kKeyRotateB;

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

namespace GTwistRunGrowKeyBConfig {

GrowStageConfigs MakeGrowBConfig(ResidualBucket &pResidualBucket) {
    using Slot = TwistWorkSpaceSlot;

    GrowStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    //
    // Grow B — Stage A
    //
    const GPassFactory::SlotArray4 aInputsA = {
        Slot::kAetherLaneA, Slot::kAetherLaneB,
        Slot::kAetherLaneC, Slot::kAetherLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesA = {
        Slot::kKineticLaneA, Slot::kKineticLaneB,
    };
    const GPassFactory::SlotArray4 aDestinationsA = {
        Slot::kSpiritLaneA, Slot::kSpiritLaneB,
        Slot::kSpiritLaneC, Slot::kSpiritLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsA =
        GPassFactory::Concat(aWarmUpLanesA,
                             aDestinationsA);

    pResidualBucket.Remove(GPassFactory::ToVector(aInputsA));
    pResidualBucket.Remove(
        GPassFactory::ToVector(aExpectedDestinationsA));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage A", 24 - 2);

    const GPassFactory::SlotArray24 aResidualsA = {
        Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14], aResidualsPool[15],
        aResidualsPool[16], aResidualsPool[17],
        aResidualsPool[18], aResidualsPool[19],
        aResidualsPool[20], aResidualsPool[21],
    };

    pResidualBucket.AddResiduals("Grow B — Stage A", {
        Slot::kAetherLaneA, Slot::kAetherLaneB,
        Slot::kAetherLaneC, Slot::kAetherLaneD,
        Slot::kKineticLaneA, Slot::kKineticLaneB,
    });

    GSeedRunStageConfig aConfigA = BaseConfig("GROW_B_A",
                                              "grow_b_loop_a");
    aConfigA.mFormat = GAXSFormat::kN9;
    aConfigA.mSlices =
        GPassFactory::SixPassTwentyFourResidualSlices(
            aInputsA,
            aResidualsA,
            aExpectedDestinationsA);
    aConfigA.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsA.size());
    aConfigA.mHotPackCount =
        static_cast<int>(aExpectedDestinationsA.size());

    std::string aErrorMessageA;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigA,
            GPassFactory::ToVector(aInputsA),
            GPassFactory::ToVector(aResidualsA),
            GPassFactory::ToVector(aExpectedDestinationsA),
            &aErrorMessageA)) {
        printf("MakeGrowBConfig stage A was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigs[0] = aConfigA;

    //
    // Grow B — Stage B
    //
    const GPassFactory::SlotArray4 aInputsB = {
        Slot::kSpiritLaneA, Slot::kSpiritLaneB,
        Slot::kSpiritLaneC, Slot::kSpiritLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesB = {
        Slot::kKineticLaneC, Slot::kKineticLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsB = {
        Slot::kCelestialLaneA, Slot::kCelestialLaneB,
        Slot::kCelestialLaneC, Slot::kCelestialLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsB =
        GPassFactory::Concat(aWarmUpLanesB,
                             aDestinationsB);

    pResidualBucket.Remove(GPassFactory::ToVector(aInputsB));
    pResidualBucket.Remove(
        GPassFactory::ToVector(aExpectedDestinationsB));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage B", 24 - 2);

    const GPassFactory::SlotArray24 aResidualsB = {
        Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14], aResidualsPool[15],
        aResidualsPool[16], aResidualsPool[17],
        aResidualsPool[18], aResidualsPool[19],
        aResidualsPool[20], aResidualsPool[21],
    };

    pResidualBucket.AddResiduals("Grow B — Stage B", {
        Slot::kSpiritLaneA, Slot::kSpiritLaneB,
        Slot::kSpiritLaneC, Slot::kSpiritLaneD,
        Slot::kKineticLaneC, Slot::kKineticLaneD,
    });

    GSeedRunStageConfig aConfigB = BaseConfig("GROW_B_B",
                                              "grow_b_loop_b");
    aConfigB.mFormat = GAXSFormat::kN7;
    aConfigB.mSlices =
        GPassFactory::SixPassTwentyFourResidualSlices(
            aInputsB,
            aResidualsB,
            aExpectedDestinationsB);
    aConfigB.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsB.size());
    aConfigB.mHotPackCount =
        static_cast<int>(aExpectedDestinationsB.size());

    std::string aErrorMessageB;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigB,
            GPassFactory::ToVector(aInputsB),
            GPassFactory::ToVector(aResidualsB),
            GPassFactory::ToVector(aExpectedDestinationsB),
            &aErrorMessageB)) {
        printf("MakeGrowBConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigs[1] = aConfigB;

    //
    // Grow B — Stage C
    //
    const GPassFactory::SlotArray4 aInputsC = {
        Slot::kCelestialLaneA, Slot::kCelestialLaneB,
        Slot::kCelestialLaneC, Slot::kCelestialLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aInputsC));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsC));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage C", 16);

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

    pResidualBucket.AddResiduals("Grow B — Stage C", {
        Slot::kCelestialLaneA, Slot::kCelestialLaneB,
        Slot::kCelestialLaneC, Slot::kCelestialLaneD,
    });

    GSeedRunStageConfig aConfigC = BaseConfig("GROW_B_C",
                                              "grow_b_loop_c");
    aConfigC.mFormat = GAXSFormat::kN9;
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
        printf("MakeGrowBConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;

    // Matrix diffusion:
    //   Fuse A-D -> Chance A-D
    // Previous six:
    //   Kinetic C, Kinetic D, Celestial A-D

    //
    // Grow B — Stage D
    //
    const GPassFactory::SlotArray4 aInputsD = {
        Slot::kChanceLaneA, Slot::kChanceLaneB,
        Slot::kChanceLaneC, Slot::kChanceLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsD = {
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aInputsD));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsD));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage D", 16);

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

    pResidualBucket.AddResiduals("Grow B — Stage D", {
        Slot::kChanceLaneA, Slot::kChanceLaneB,
        Slot::kChanceLaneC, Slot::kChanceLaneD,
    });

    pResidualBucket.Print("Grow B — Final");

    GSeedRunStageConfig aConfigD = BaseConfig("GROW_B_D",
                                              "grow_b_loop_d");
    aConfigD.mFormat = GAXSFormat::kN11;
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
        printf("MakeGrowBConfig stage D was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigs[3] = aConfigD;

    return aConfigs;
}

} // namespace GTwistRunGrowKeyBConfig

GTwistRunGrowKeyB::GTwistRunGrowKeyB(ResidualBucket &pResidualBucket)
: mStage(GTwistRunGrowKeyBConfig::MakeGrowBConfig(pResidualBucket)[0]) {
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
