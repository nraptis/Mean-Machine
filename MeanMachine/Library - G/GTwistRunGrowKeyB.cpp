//
//  GTwistRunGrowKeyB.cpp
//  MeanMachine
//

#include "GTwistRunGrowKeyB.hpp"
#include "ArrangementFour.hpp"
#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryTrunk.hpp"
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
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterAssignA, 8);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterUpdateA, 8);
    aConfig.mSaltsWandererUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltWandererUpdateA, 8);
    return aConfig;
}

} // namespace

namespace GTwistRunGrowKeyBConfig {

GrowStageConfigs MakeGrowBConfig(ResidualBucket &pResidualBucket,
                                 const std::size_t pCandidateIndex) {
    using Slot = TwistWorkSpaceSlot;

    GrowStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    // Lane Plan

    //
    // Grow B — Stage A
    //
    const GPassFactoryMidstage::SlotArray4 aInputsA = {
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsA = {
        Slot::kAetherLaneA, Slot::kAetherLaneB,
        Slot::kAetherLaneC, Slot::kAetherLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsA));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsA));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage A", 15); // plus the opposite key row

    const GPassFactoryMidstage::SlotArray16 aResidualsA = {
        Slot::kKeyRowReadA,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14],
    };

    pResidualBucket.AddResiduals("Grow B — Stage A", {
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    });

    //
    // Grow B — Stage B
    //
    const GPassFactoryMidstage::SlotArray4 aInputsB = {
        Slot::kAetherLaneA, Slot::kAetherLaneB,
        Slot::kAetherLaneC, Slot::kAetherLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsB = {
        Slot::kKineticLaneA, Slot::kKineticLaneB,
        Slot::kKineticLaneC, Slot::kKineticLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsB));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsB));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage B", 15); // plus the opposite key row

    const GPassFactoryMidstage::SlotArray16 aResidualsB = {
        Slot::kKeyRowReadA,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14],
    };

    pResidualBucket.AddResiduals("Grow B — Stage B", {
        Slot::kAetherLaneA, Slot::kAetherLaneB,
        Slot::kAetherLaneC, Slot::kAetherLaneD,
    });

    //
    // Grow B — Stage C
    //
    const GPassFactoryMidstage::SlotArray4 aInputsC = {
        Slot::kKineticLaneA, Slot::kKineticLaneB,
        Slot::kKineticLaneC, Slot::kKineticLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsC));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsC));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage C", 15); // plus the opposite key row

    const GPassFactoryMidstage::SlotArray16 aResidualsC = {
        Slot::kKeyRowReadA,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14],
    };

    pResidualBucket.AddResiduals("Grow B — Stage C", {
        Slot::kKineticLaneA, Slot::kKineticLaneB,
        Slot::kKineticLaneC, Slot::kKineticLaneD,
    });

    // Matrix diffusion:
    //   Fuse A-D -> Vapor A-D
    // Previous six:
    //   Aether C, Aether D, Kinetic A-D

    //
    // Grow B — Stage D
    //
    const GPassFactoryMidstage::SlotArray4 aInputsD = {
        Slot::kVaporLaneA, Slot::kVaporLaneB,
        Slot::kVaporLaneC, Slot::kVaporLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsD = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsD));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsD));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage D", 15); // plus the opposite key row

    const GPassFactoryMidstage::SlotArray16 aResidualsD = {
        Slot::kKeyRowReadA,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14],
    };

    pResidualBucket.AddResiduals("Grow B — Stage D", {
        Slot::kVaporLaneA, Slot::kVaporLaneB,
        Slot::kVaporLaneC, Slot::kVaporLaneD,
    });

    const ArrangementFour::SlotArray4 aArrangedInputsD =
        ArrangementFour::Arrange(aInputsD,
                                 static_cast<int>(pCandidateIndex),
                                 3);

    //
    // Grow B — Stage E
    //
    const GPassFactoryMidstage::SlotArray4 aInputsE = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsE = {
        Slot::kShadowLaneA, Slot::kShadowLaneB,
        Slot::kShadowLaneC, Slot::kShadowLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsE));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsE));

    aResidualsPool =
        pResidualBucket.Withdraw("Grow B — Stage E", 15); // plus the opposite key row

    const GPassFactoryMidstage::SlotArray16 aResidualsE = {
        Slot::kKeyRowReadA,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14],
    };

    pResidualBucket.AddResiduals("Grow B — Stage E", {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    });

    pResidualBucket.Print("Grow B — Final");

    // Stage Construction

    GSeedRunStageConfig aConfigA = BaseConfig("GROW_B_A",
                                              "grow_b_loop_a");
    aConfigA.mFormat = GAXSFormat::kN7;
    aConfigA.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(
            aInputsA,
            aResidualsA,
            aDestinationsA);
    aConfigA.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsA.size());
    aConfigA.mHotPackCount =
        static_cast<int>(aDestinationsA.size());

    std::string aErrorMessageA;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigA,
            GPassFactoryMidstage::ToVector(aInputsA),
            GPassFactoryMidstage::ToVector(aResidualsA),
            GPassFactoryMidstage::ToVector(aDestinationsA),
            &aErrorMessageA)) {
        printf("MakeGrowBConfig stage A was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigs[0] = aConfigA;

    GSeedRunStageConfig aConfigB = BaseConfig("GROW_B_B",
                                              "grow_b_loop_b");
    aConfigB.mFormat = GAXSFormat::kN9;
    aConfigB.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(
            aInputsB,
            aResidualsB,
            aDestinationsB);
    aConfigB.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsB.size());
    aConfigB.mHotPackCount =
        static_cast<int>(aDestinationsB.size());

    std::string aErrorMessageB;
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
    aConfigs[1] = aConfigB;

    GSeedRunStageConfig aConfigC = BaseConfig("GROW_B_C",
                                              "grow_b_loop_c");
    aConfigC.mFormat = GAXSFormat::kN11;
    aConfigC.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(
            aInputsC,
            aResidualsC,
            aDestinationsC);
    aConfigC.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsC.size());
    aConfigC.mHotPackCount =
        static_cast<int>(aDestinationsC.size());

    std::string aErrorMessageC;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigC,
            GPassFactoryMidstage::ToVector(aInputsC),
            GPassFactoryMidstage::ToVector(aResidualsC),
            GPassFactoryMidstage::ToVector(aDestinationsC),
            &aErrorMessageC)) {
        printf("MakeGrowBConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;

    GSeedRunStageConfig aConfigD = BaseConfig("GROW_B_D",
                                              "grow_b_loop_d");
    aConfigD.mFormat = GAXSFormat::kN7;
    aConfigD.mSlices =
        GPassFactoryTrunk::FourPassTrunkSlices(
            aArrangedInputsD,
            aResidualsD,
            aDestinationsD);
    aConfigD.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsD.size());
    aConfigD.mHotPackCount =
        static_cast<int>(aDestinationsD.size());

    std::string aErrorMessageD;
    if (!GSeedRunStageConfigValidator::ValidateTrunk(
            aConfigD,
            GPassFactoryMidstage::ToVector(aArrangedInputsD),
            GPassFactoryMidstage::ToVector(aResidualsD),
            GPassFactoryMidstage::ToVector(aDestinationsD),
            &aErrorMessageD)) {
        printf("MakeGrowBConfig stage D was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigs[3] = aConfigD;

    GSeedRunStageConfig aConfigE = BaseConfig("GROW_B_E",
                                              "grow_b_loop_e");
    aConfigE.mFormat = GAXSFormat::kN11;
    aConfigE.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(aInputsE,
                                                     aResidualsE,
                                                     aDestinationsE);
    aConfigE.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsE.size());
    aConfigE.mHotPackCount =
        static_cast<int>(aDestinationsE.size());

    std::string aErrorMessageE;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigE,
            GPassFactoryMidstage::ToVector(aInputsE),
            GPassFactoryMidstage::ToVector(aResidualsE),
            GPassFactoryMidstage::ToVector(aDestinationsE),
            &aErrorMessageE)) {
        printf("MakeGrowBConfig stage E was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageE.c_str());
        exit(0);
    }
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
