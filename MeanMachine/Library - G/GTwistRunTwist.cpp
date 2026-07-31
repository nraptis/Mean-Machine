//
//  GTwistRunTwist.cpp
//  MeanMachine
//

#include "GTwistRunTwist.hpp"
#include "ArrangementFour.hpp"
#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryStarter.hpp"
#include "GPassFactoryTrunk.hpp"
#include "GQuick.hpp"
#include "Random.hpp"
#include "ResidualBucket.hpp"
#include "GSeedRunStageConfigValidator.hpp"
#include <array>
#include <cstdio>
#include <cstdlib>

namespace {

const std::array<TwistVariable, 13> kInitialRandomVariables = {
    TwistVariable::kIngress,
    TwistVariable::kCarry,
    TwistVariable::kWandererA,
    TwistVariable::kWandererB,
    TwistVariable::kWandererC,
    TwistVariable::kWandererD,
    TwistVariable::kWandererE,
    TwistVariable::kWandererF,
    TwistVariable::kWandererG,
    TwistVariable::kWandererH,
    TwistVariable::kWandererI,
    TwistVariable::kWandererJ,
    TwistVariable::kWandererK,
};

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
                               const std::string &pLoopName,
                               const GAXSFormat pFormat) {
    using Slot = TwistWorkSpaceSlot;
    constexpr TwistDomain kDomain = TwistDomain::kTwist;

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pLoopName;
    aConfig.mStartLine = "// " + pStageName + " " + pLoopName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + pLoopName + " (end)";
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = true;
    aConfig.mDomain = kDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterAssignA, 8);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterUpdateA, 8);
    aConfig.mSaltsWandererUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltWandererUpdateA, 8);
    return aConfig;
}

void AddTwistPrologue(TwistProgramBranch &pBranch) {
    GBatch aInitBatch;
    aInitBatch.mName = "init varz";
    aInitBatch.mExportsAsBlock = false;

    std::vector<GStatement> aInitStatements;
    for (TwistVariable aVariable : kInitialRandomVariables) {
        aInitStatements.push_back(
                                  GQuick::MakeAssignVariableStatement(GSymbol::Var(aVariable),
                                                                      GExpr::Const64Hex(Random::Get64High())));
    }
    aInitBatch.CommitStatements(&aInitStatements);
    pBranch.AddBatch(aInitBatch);
    pBranch.AddLine("");
}

} // namespace

namespace GTwistRunTwistConfig {

TwistStageConfigs MakeTwistConfig(ResidualBucket &pResidualBucket,
                                  const std::size_t pCandidateIndex) {
    using Slot = TwistWorkSpaceSlot;

    std::vector<Slot> aResidualsPool;

    std::vector<Slot> aRandomCross = {
        Slot::kParamCrossA, Slot::kParamCrossB,
        Slot::kParamCrossC, Slot::kParamCrossD,
    };
    Random::Shuffle(&aRandomCross);

    TwistStageConfigs aConfigs;

    // Lane Plan

    //
    // Twist — Stage A
    //
    const GPassFactoryMidstage::SlotArray3 aPrimarySourcesA = {
        Slot::kSourceLane, Slot::kKeyRowReadA, Slot::kKeyRowReadB,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesA = {
        Slot::kFireLaneA, Slot::kFireLaneB,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsA = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsA =
        GPassFactoryMidstage::Concat(aWarmUpLanesA,
                             aDestinationsA);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsA));

    const GPassFactoryMidstage::SlotArray4 aResidualsA = {
        Slot::kParamCrossA, Slot::kParamCrossB,
        Slot::kParamCrossC, Slot::kParamCrossD,
    };

    pResidualBucket.AddResiduals("Twist — Stage A", {
        Slot::kFireLaneA, Slot::kFireLaneB,
    });

    //
    // Twist — Stage B
    //
    const GPassFactoryMidstage::SlotArray4 aInputsB = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aDestinationsB = {
        Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsB));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsB));

    aResidualsPool = pResidualBucket.Withdraw("Twist — Stage B", 9 - 7); // we are using 7 fixed ones.

    const GPassFactoryMidstage::SlotArray9 aResidualsB = {
        Slot::kParamCrossA, Slot::kParamCrossB,
        Slot::kParamCrossC, Slot::kParamCrossD,
        Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
    };

    pResidualBucket.AddResiduals("Twist — Stage B", {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
        Slot::kFireLaneC, Slot::kFireLaneD,
    });

    //
    // Twist — Stage C
    //
    const GPassFactoryMidstage::SlotArray4 aInputsC = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsC));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsC));

    aResidualsPool = pResidualBucket.Withdraw("Twist — Stage C", 14 - 6); // we are using 6 fixed ones.

    const GPassFactoryMidstage::SlotArray14 aResidualsC = {
        Slot::kParamCrossA, Slot::kParamCrossB,
        Slot::kParamCrossC, Slot::kParamCrossD,
        Slot::kKeyRowReadA, Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
    };

    pResidualBucket.AddResiduals("Twist — Stage C", {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    });
    
    /*
    TwistDiffuse::DiffuseWithDomainWords(
                aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
                aHeartLaneA, aHeartLaneB, aHeartLaneC, aHeartLaneD, // output lanes
                aFireLaneC, aFireLaneD, aWaterLaneC, aWaterLaneD, // index shuffle seeds
                aWaterLaneA, aWaterLaneB); // operation seeds
    */
    
    //
    // Twist — Stage D
    //
    const GPassFactoryMidstage::SlotArray4 aInputsD = {
        Slot::kHeartLaneA, Slot::kHeartLaneB,
        Slot::kHeartLaneC, Slot::kHeartLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aDestinationsD = {
        Slot::kLightningLaneA, Slot::kLightningLaneB,
        Slot::kSoilLaneA, Slot::kSoilLaneB,
        Slot::kSoilLaneC, Slot::kSoilLaneD,
    };
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsD));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsD));

    aResidualsPool = pResidualBucket.Withdraw("Twist — Stage D", 16 - 6); // we are using 6 fixed ones.

    const GPassFactoryMidstage::SlotArray16 aResidualsD = {
        Slot::kParamCrossA, Slot::kParamCrossB,
        Slot::kParamCrossC, Slot::kParamCrossD,
        Slot::kKeyRowReadB, Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
    };



    pResidualBucket.AddResiduals("Twist — Stage D", {
        Slot::kHeartLaneA, Slot::kHeartLaneB,
        Slot::kHeartLaneC, Slot::kHeartLaneD,
        Slot::kLightningLaneA, Slot::kLightningLaneB,
    });

    //
    // Twist — Stage E
    //
    const GPassFactoryMidstage::SlotArray4 aInputsE = {
        Slot::kSoilLaneA, Slot::kSoilLaneB,
        Slot::kSoilLaneC, Slot::kSoilLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aDestinationsE = {
        Slot::kLightningLaneC, Slot::kLightningLaneD,
        Slot::kIceLaneA, Slot::kIceLaneB,
        Slot::kIceLaneC, Slot::kIceLaneD,
    };
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aInputsE));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsE));

    aResidualsPool = pResidualBucket.Withdraw("Twist — Stage E", 16 - 3); // we are using 3 fixed ones.

    const GPassFactoryMidstage::SlotArray16 aResidualsE = {
        aRandomCross[0], Slot::kKeyRowReadA, Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1], aResidualsPool[2],
        aResidualsPool[3], aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7], aResidualsPool[8],
        aResidualsPool[9], aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12],
    };

    pResidualBucket.AddResiduals("Twist — Stage E", {
        Slot::kSoilLaneA, Slot::kSoilLaneB,
        Slot::kSoilLaneC, Slot::kSoilLaneD,
        Slot::kLightningLaneC, Slot::kLightningLaneD,
    });

    //
    // Twist — Stage F
    //

    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesF = {
        Slot::kIceLaneA, Slot::kIceLaneB,
        Slot::kIceLaneC, Slot::kIceLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsF = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesF));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsF));

    aResidualsPool = pResidualBucket.Withdraw("Twist — Stage F", 16 - 3); // we are using 3 fixed ones.

    const GPassFactoryMidstage::SlotArray16 aResidualsF = {
        aRandomCross[1], Slot::kKeyRowReadB, Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1], aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5], aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9], aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12],
    };

    pResidualBucket.AddResiduals("Twist — Stage F", {
        Slot::kIceLaneA, Slot::kIceLaneB,
        Slot::kIceLaneC, Slot::kIceLaneD,
    });
    
    /*
    TwistDiffuse::DiffuseWithDomainWords(
            aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
            aWoodLaneA, aWoodLaneB, aWoodLaneC, aWoodLaneD, // output lanes
            aLightningLaneC, aLightningLaneD, aIceLaneC, aIceLaneD, // index shuffle seeds
            aIceLaneA, aIceLaneB); // operation seeds
    */

    //
    // Twist — Stage G
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesG = {
        Slot::kWoodLaneA, Slot::kWoodLaneB,
        Slot::kWoodLaneC, Slot::kWoodLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesG = {
        Slot::kPlasmaLaneA, Slot::kPlasmaLaneB,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsG = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsG =
        GPassFactoryMidstage::Concat(aWarmUpLanesG,
                             aDestinationsG);
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesG));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsG));

    aResidualsPool = pResidualBucket.Withdraw("Twist — Stage G", 16 - 3); // we are using 3 fixed ones.

    const GPassFactoryMidstage::SlotArray16 aResidualsG = {
        aRandomCross[2], Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        aResidualsPool[0], aResidualsPool[1], aResidualsPool[2],
        aResidualsPool[3], aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7], aResidualsPool[8],
        aResidualsPool[9], aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12],
    };



    pResidualBucket.AddResiduals("Twist — Stage G", {
        Slot::kWoodLaneA, Slot::kWoodLaneB,
        Slot::kWoodLaneC, Slot::kWoodLaneD,
        Slot::kPlasmaLaneA, Slot::kPlasmaLaneB,
    });

    //
    // Twist — Stage H
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesH = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesH = {
        Slot::kPlasmaLaneC, Slot::kPlasmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsH = {
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsH =
        GPassFactoryMidstage::Concat(aWarmUpLanesH,
                             aDestinationsH);
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesH));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsH));

    aResidualsPool = pResidualBucket.Withdraw("Twist — Stage H", 16 - 1); // we are using 1 fixed one.

    const GPassFactoryMidstage::SlotArray16 aResidualsH = {
        aRandomCross[3],
        aResidualsPool[0], aResidualsPool[1], aResidualsPool[2],
        aResidualsPool[3], aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7], aResidualsPool[8],
        aResidualsPool[9], aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13], aResidualsPool[14],
    };

    pResidualBucket.AddResiduals("Twist — Stage H", {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
        Slot::kPlasmaLaneC, Slot::kPlasmaLaneD,
    });

    pResidualBucket.Print("Twist — Final");
    
    // Stage Construction
    
    GSeedRunStageConfig aConfigA = BaseConfig("GTwistRunTwist_A",
                                             "twist_loop_a",
                                             GAXSFormat::kN11);
    aConfigA.mMaxContextSourceCount = 4;
    aConfigA.mMaxBoundSourceCount = 8;
    aConfigA.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesA.size());
    aConfigA.mBindDuplicateSourceSlots = false;
    aConfigA.mUsesSpecialSixPassTwistStarterGraph = true;
    aConfigA.mSlices =
        GPassFactoryStarter::Twist_AStarterSlices(
            aPrimarySourcesA,
            aResidualsA,
            aWarmUpLanesA,
            aDestinationsA,
            pCandidateIndex);
    aConfigA.mExpectedSkeletonCount = 6;
    aConfigA.mHotPackCount = 6;

    std::string aErrorMessageA;
    if (!GSeedRunStageConfigValidator::ValidateStarterWithResiduals(
            aConfigA,
            GPassFactoryMidstage::ToVector(aPrimarySourcesA),
            GPassFactoryMidstage::ToVector(aResidualsA),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsA),
            &aErrorMessageA)) {
        printf("MakeTwistConfig stage A was not valid with ValidateStarterWithResiduals");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigs[0] = aConfigA;
    
    // --------------------------
    
    GSeedRunStageConfig aConfigB = BaseConfig("GTwistRunTwist_B",
                                             "twist_loop_b",
                                             GAXSFormat::kN9);
    aConfigB.mSlices = GPassFactoryMidstage::SixPassNineResidualSlices(aInputsB,
                                                               aResidualsB,
                                                               aDestinationsB);
    aConfigB.mWarmupDestinationCount = 2;
    aConfigB.mExpectedSkeletonCount = 6;
    aConfigB.mHotPackCount = 6;

    std::string aErrorMessageB;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfigB,
                                                        GPassFactoryMidstage::ToVector(aInputsB),
                                                        GPassFactoryMidstage::ToVector(aResidualsB),
                                                        GPassFactoryMidstage::ToVector(aDestinationsB),
                                                        &aErrorMessageB)) {
        printf("MakeTwistConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigs[1] = aConfigB;
    
    // --------------------------
    
    GSeedRunStageConfig aConfigC = BaseConfig("GTwistRunTwist_C",
                                             "twist_loop_c",
                                             GAXSFormat::kN7);
    aConfigC.mSlices = GPassFactoryMidstage::FourPassFourteenResidualSlices(aInputsC,
                                                                    aResidualsC,
                                                                    aDestinationsC);
    aConfigC.mExpectedSkeletonCount = 4;
    aConfigC.mHotPackCount = 4;

    std::string aErrorMessageC;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfigC,
                                                        GPassFactoryMidstage::ToVector(aInputsC),
                                                        GPassFactoryMidstage::ToVector(aResidualsC),
                                                        GPassFactoryMidstage::ToVector(aDestinationsC),
                                                        &aErrorMessageC)) {
        printf("MakeTwistConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;
    
    // --------------------------
    
    const ArrangementFour::SlotArray4 aArrangedInputsD =
        ArrangementFour::Arrange(aInputsD,
                                 static_cast<int>(pCandidateIndex),
                                 11);

    GSeedRunStageConfig aConfigD = BaseConfig("GTwistRunTwist_D",
                                             "twist_loop_d",
                                             GAXSFormat::kN9);
    aConfigD.mSlices = GPassFactoryTrunk::SixPassTrunkSlices(aArrangedInputsD,
                                                        aResidualsD,
                                                        aDestinationsD);
    aConfigD.mWarmupDestinationCount = 2;
    aConfigD.mExpectedSkeletonCount = 6;
    aConfigD.mHotPackCount = 6;

    std::string aErrorMessageD;
    if (!GSeedRunStageConfigValidator::ValidateTrunk(aConfigD,
                                                     GPassFactoryMidstage::ToVector(aArrangedInputsD),
                                                     GPassFactoryMidstage::ToVector(aResidualsD),
                                                     GPassFactoryMidstage::ToVector(aDestinationsD),
                                                     &aErrorMessageD)) {
        printf("MakeTwistConfig stage D was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigs[3] = aConfigD;
    
    // --------------------------
    
    GSeedRunStageConfig aConfigE = BaseConfig("GTwistRunTwist_E",
                                             "twist_loop_e",
                                             GAXSFormat::kN11);
    aConfigE.mSlices = GPassFactoryMidstage::SixPassSixteenResidualSlices(aInputsE,
                                                                  aResidualsE,
                                                                  aDestinationsE);
    aConfigE.mWarmupDestinationCount = 2;
    aConfigE.mExpectedSkeletonCount = 6;
    aConfigE.mHotPackCount = 6;

    std::string aErrorMessageE;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfigE,
                                                        GPassFactoryMidstage::ToVector(aInputsE),
                                                        GPassFactoryMidstage::ToVector(aResidualsE),
                                                        GPassFactoryMidstage::ToVector(aDestinationsE),
                                                        &aErrorMessageE)) {
        printf("MakeTwistConfig stage E was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageE.c_str());
        exit(0);
    }
    aConfigs[4] = aConfigE;
    
    // --------------------------
    
    GSeedRunStageConfig aConfigF = BaseConfig("GTwistRunTwist_F",
                                              "twist_loop_f",
                                              GAXSFormat::kN9);
    aConfigF.mSlices = GPassFactoryMidstage::FourPassSixteenResidualSlices(aPrimarySourcesF,
                                                                   aResidualsF,
                                                                   aDestinationsF);
    aConfigF.mExpectedSkeletonCount = 4;
    aConfigF.mHotPackCount = 4;

    std::string aErrorMessageF;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfigF,
                                                        GPassFactoryMidstage::ToVector(aPrimarySourcesF),
                                                        GPassFactoryMidstage::ToVector(aResidualsF),
                                                        GPassFactoryMidstage::ToVector(aDestinationsF),
                                                        &aErrorMessageF)) {
        printf("MakeTwistConfig stage F was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageF.c_str());
        exit(0);
    }
    aConfigs[5] = aConfigF;
    
    // --------------------------
    
    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesG =
        ArrangementFour::Arrange(aPrimarySourcesG,
                                 static_cast<int>(pCandidateIndex),
                                 9);

    GSeedRunStageConfig aConfigG = BaseConfig("GTwistRunTwist_G",
                                              "twist_loop_g",
                                              GAXSFormat::kN7);
    aConfigG.mSlices = GPassFactoryTrunk::SixPassTrunkSlices(aArrangedPrimarySourcesG,
                                                        aResidualsG,
                                                        aExpectedDestinationsG);
    aConfigG.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesG.size());
    aConfigG.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsG.size());
    aConfigG.mHotPackCount =
        static_cast<int>(aExpectedDestinationsG.size());

    std::string aErrorMessageG;
    if (!GSeedRunStageConfigValidator::ValidateTrunk(
            aConfigG,
            GPassFactoryMidstage::ToVector(aArrangedPrimarySourcesG),
            GPassFactoryMidstage::ToVector(aResidualsG),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsG),
            &aErrorMessageG)) {
        printf("MakeTwistConfig stage G was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageG.c_str());
        exit(0);
    }
    aConfigs[6] = aConfigG;
    
    // --------------------------
    
    GSeedRunStageConfig aConfigH = BaseConfig("GTwistRunTwist_H",
                                              "twist_loop_h",
                                              GAXSFormat::kN9);
    aConfigH.mSlices = GPassFactoryMidstage::SixPassSixteenResidualSlices(aPrimarySourcesH,
                                                                  aResidualsH,
                                                                  aExpectedDestinationsH);
    aConfigH.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesH.size());
    aConfigH.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsH.size());
    aConfigH.mHotPackCount =
        static_cast<int>(aExpectedDestinationsH.size());

    std::string aErrorMessageH;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigH,
            GPassFactoryMidstage::ToVector(aPrimarySourcesH),
            GPassFactoryMidstage::ToVector(aResidualsH),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsH),
            &aErrorMessageH)) {
        printf("MakeTwistConfig stage H was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageH.c_str());
        exit(0);
    }
    aConfigs[7] = aConfigH;
    
    return aConfigs;
    
}

} // namespace GTwistRunTwistConfig

GTwistRunTwist::GTwistRunTwist(const GSeedRunStageConfig &pConfig,
                               const bool pEmitPrologue)
: mStage(pConfig),
  mEmitPrologue(pEmitPrologue) {
}

bool GTwistRunTwist::Plan(std::string *pErrorMessage) {
    mStage.Reset();
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunTwist::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mEmitPrologue) {
        AddTwistPrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
