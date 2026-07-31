//
//  GSeedRunSeed.cpp
//  MeanMachine
//

#include "GSeedRunSeed.hpp"
#include "ArrangementFour.hpp"
#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryStarter.hpp"
#include "GPassFactoryTrunk.hpp"
#include "Random.hpp"
#include "ResidualBucket.hpp"
#include "GSeedRunStageConfigValidator.hpp"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>

namespace {

const std::array<const char *, 16> kNonceVariableNames = {
    "aNonceWordA",
    "aNonceWordB",
    "aNonceWordC",
    "aNonceWordD",
    "aNonceWordE",
    "aNonceWordF",
    "aNonceWordG",
    "aNonceWordH",
    "aNonceWordI",
    "aNonceWordJ",
    "aNonceWordK",
    "aNonceWordL",
    "aNonceWordM",
    "aNonceWordN",
    "aNonceWordO",
    "aNonceWordP",
};

const std::array<const char *, 3> kNonceDiffuseNames = {
    "DiffuseA",
    "DiffuseB",
    "DiffuseC",
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

std::string SeedLoopName(const std::string &pStageName) {
    std::string aResult = "seed_loop";
    if (!pStageName.empty()) {
        const char aStageLetter = pStageName.back();
        if ((aStageLetter >= 'A') && (aStageLetter <= 'N')) {
            aResult.push_back('_');
            aResult.push_back(static_cast<char>('a' + (aStageLetter - 'A')));
        }
    }
    return aResult;
}

std::string UInt64Literal(const std::uint64_t pValue) {
    std::ostringstream aStream;
    aStream << "0x" << std::uppercase << std::hex << pValue << "ULL";
    return aStream.str();
}

const char *RandomNonceDiffuseName() {
    return kNonceDiffuseNames[static_cast<std::size_t>(Random::Get(static_cast<int>(kNonceDiffuseNames.size())))];
}

std::string NonceDeclareLine(const GSymbol &pNonceSymbol) {
    const std::uint64_t aMultiplyWord = Random::Get64HighOdd();
    const std::uint64_t aAddWord = Random::Get64High();
    const char *aDiffuseName = RandomNonceDiffuseName();

    std::ostringstream aLine;
    aLine << "[[maybe_unused]] const std::uint64_t " << pNonceSymbol.mName << " = TwistMix64::"
    << aDiffuseName
    << "(pNonce * "
    << UInt64Literal(aMultiplyWord)
    << " + "
    << UInt64Literal(aAddWord) << ");";
    return aLine.str();
}

void AddSeedNoncePrologue(TwistProgramBranch &pBranch) {
    for (std::size_t i = 0U; i < kNonceVariableNames.size(); ++i) {
        pBranch.AddLine(NonceDeclareLine(GSymbol::Var(kNonceVariableNames[i])));
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
                               const bool pUseNonces,
                               const GAXSFormat pFormat) {
    using Slot = TwistWorkSpaceSlot;
    constexpr TwistDomain kDomain = TwistDomain::kSeed;

    const std::string aLoopName = SeedLoopName(pStageName);

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = aLoopName;
    aConfig.mStartLine = "// " + pStageName + " " + aLoopName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + aLoopName + " (end)";
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = !pUseNonces;
    aConfig.mDomain = kDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterAssignA, 8);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterUpdateA, 8);
    aConfig.mSaltsWandererUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltWandererUpdateA, 8);
    return aConfig;
}

} // namespace

namespace GSeedRunSeedConfig {

SeedStageConfigs MakeSeedConfig(const bool pUseNonces,
                                ResidualBucket &pResidualBucket,
                                const std::size_t pCandidateIndex) {
    using Slot = TwistWorkSpaceSlot;

    SeedStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    // Lane Plan

    //
    // Seed — Stage A
    //
    const GPassFactoryStarter::SlotArray2 aPrimarySourcesA = {
        Slot::kSourceLane,
        Slot::kNonceLane,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesA = {
        Slot::kSpiritLaneA, Slot::kSpiritLaneB,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsA = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsA =
        GPassFactoryMidstage::Concat(aWarmUpLanesA,
                             aDestinationsA);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsA));

    pResidualBucket.Withdraw("Seed — Stage A", 0);

    pResidualBucket.AddResiduals("Seed — Stage A", {
        Slot::kSpiritLaneA, Slot::kSpiritLaneB,
    });

    //
    // Seed — Stage B
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesB = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesB = {
        Slot::kSpiritLaneC, Slot::kSpiritLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsB = {
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsB =
        GPassFactoryMidstage::Concat(aWarmUpLanesB,
                             aDestinationsB);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesB));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsB));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage B", 2);

    const GPassFactoryMidstage::SlotArray3 aResidualsB = {
        Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
    };

    pResidualBucket.AddResiduals("Seed — Stage B", {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
        Slot::kSpiritLaneC, Slot::kSpiritLaneD,
    });

    //
    // Seed — Stage C
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesC = {
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesC));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsC));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage C", 8);

    const GPassFactoryMidstage::SlotArray9 aResidualsC = {
        Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
    };

    pResidualBucket.AddResiduals("Seed — Stage C", {
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    });

    /*
    TwistDiffuse::DiffuseWithDomainWords(
                aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
                aWindLaneA, aWindLaneB, aWindLaneC, aWindLaneD, // output lanes
                aPlasmaLaneC, aPlasmaLaneD, aCrystalLaneC, aCrystalLaneD, // index shuffle seeds
                aCrystalLaneA, aCrystalLaneB); // operation seeds
    */
                                           
    //
    // Seed — Stage D
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesD = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesD = {
        Slot::kVaporLaneA, Slot::kVaporLaneB,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsD = {
        Slot::kShadowLaneA, Slot::kShadowLaneB,
        Slot::kShadowLaneC, Slot::kShadowLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsD =
        GPassFactoryMidstage::Concat(aWarmUpLanesD,
                             aDestinationsD);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesD));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsD));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage D", 12);

    const GPassFactoryMidstage::SlotArray13 aResidualsD = {
        Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
    };

    pResidualBucket.AddResiduals("Seed — Stage D", {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
        Slot::kVaporLaneA, Slot::kVaporLaneB,
    });

    //
    // Seed — Stage E
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesE = {
        Slot::kShadowLaneA, Slot::kShadowLaneB,
        Slot::kShadowLaneC, Slot::kShadowLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesE = {
        Slot::kVaporLaneC, Slot::kVaporLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsE = {
        Slot::kKineticLaneA, Slot::kKineticLaneB,
        Slot::kKineticLaneC, Slot::kKineticLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsE =
        GPassFactoryMidstage::Concat(aWarmUpLanesE,
                             aDestinationsE);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesE));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsE));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage E", 18);

    const GPassFactoryMidstage::SlotArray19 aResidualsE = {
        Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14], aResidualsPool[15],
        aResidualsPool[16], aResidualsPool[17],
    };

    pResidualBucket.AddResiduals("Seed — Stage E", {
        Slot::kShadowLaneA, Slot::kShadowLaneB,
        Slot::kShadowLaneC, Slot::kShadowLaneD,
        Slot::kVaporLaneC, Slot::kVaporLaneD,
    });

    //
    // Seed — Stage F
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesF = {
        Slot::kKineticLaneA, Slot::kKineticLaneB,
        Slot::kKineticLaneC, Slot::kKineticLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsF = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesF));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsF));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage F", 15);

    const GPassFactoryMidstage::SlotArray16 aResidualsF = {
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

    pResidualBucket.AddResiduals("Seed — Stage F", {
        Slot::kKineticLaneA, Slot::kKineticLaneB,
        Slot::kKineticLaneC, Slot::kKineticLaneD,
    });

    /*
    TwistDiffuse::DiffuseWithDomainWords(
            aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
            aAetherLaneA, aAetherLaneB, aAetherLaneC, aAetherLaneD, // output lanes
            aVaporLaneC, aVaporLaneD, aKineticLaneC, aKineticLaneD, // index shuffle seeds
            aKineticLaneA, aKineticLaneB); // operation seeds
    */

    //
    // Seed — Stage G
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesG = {
        Slot::kAetherLaneA, Slot::kAetherLaneB,
        Slot::kAetherLaneC, Slot::kAetherLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesG = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsG = {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsG =
        GPassFactoryMidstage::Concat(aWarmUpLanesG,
                             aDestinationsG);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesG));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsG));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage G", 24);

    const GPassFactoryMidstage::SlotArray24 aResidualsG = {
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
        aResidualsPool[22], aResidualsPool[23],
    };

    pResidualBucket.AddResiduals("Seed — Stage G", {
        Slot::kAetherLaneA, Slot::kAetherLaneB,
        Slot::kAetherLaneC, Slot::kAetherLaneD,
        Slot::kEarthLaneA, Slot::kEarthLaneB,
    });

    //
    // Seed — Stage H
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesH = {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesH = {
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsH = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsH =
        GPassFactoryMidstage::Concat(aWarmUpLanesH,
                             aDestinationsH);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesH));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsH));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage H", 24);

    const GPassFactoryMidstage::SlotArray24 aResidualsH = {
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
        aResidualsPool[22], aResidualsPool[23],
    };

    pResidualBucket.AddResiduals("Seed — Stage H", {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    });

    //
    // Seed — Stage I
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesI = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsI = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesI));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsI));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage I", 15);

    const GPassFactoryMidstage::SlotArray16 aResidualsI = {
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

    pResidualBucket.AddResiduals("Seed — Stage I", {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    });

    /*
    TwistDiffuse::DiffuseWithDomainWords(
            aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
            aHeartLaneA, aHeartLaneB, aHeartLaneC, aHeartLaneD, // output lanes
            aEarthLaneC, aEarthLaneD, aWaterLaneC, aWaterLaneD, // index shuffle seeds
            aWaterLaneA, aWaterLaneB); // operation seeds
    */

    //
    // Seed — Stage J
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesJ = {
        Slot::kHeartLaneA, Slot::kHeartLaneB,
        Slot::kHeartLaneC, Slot::kHeartLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesJ = {
        Slot::kLightningLaneA, Slot::kLightningLaneB,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsJ = {
        Slot::kSoilLaneA, Slot::kSoilLaneB,
        Slot::kSoilLaneC, Slot::kSoilLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsJ =
        GPassFactoryMidstage::Concat(aWarmUpLanesJ,
                             aDestinationsJ);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesJ));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsJ));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage J", 23);

    const GPassFactoryMidstage::SlotArray24 aResidualsJ = {
        Slot::kSourceLane,
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
        aResidualsPool[22],
    };

    pResidualBucket.AddResiduals("Seed — Stage J", {
        Slot::kHeartLaneA, Slot::kHeartLaneB,
        Slot::kHeartLaneC, Slot::kHeartLaneD,
        Slot::kLightningLaneA, Slot::kLightningLaneB,
    });

    //
    // Seed — Stage K
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesK = {
        Slot::kSoilLaneA, Slot::kSoilLaneB,
        Slot::kSoilLaneC, Slot::kSoilLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesK = {
        Slot::kLightningLaneC, Slot::kLightningLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsK = {
        Slot::kIceLaneA, Slot::kIceLaneB,
        Slot::kIceLaneC, Slot::kIceLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsK =
        GPassFactoryMidstage::Concat(aWarmUpLanesK,
                             aDestinationsK);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesK));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsK));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage K", 23);

    const GPassFactoryMidstage::SlotArray24 aResidualsK = {
        Slot::kSourceLane,
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
        aResidualsPool[22],
    };

    pResidualBucket.AddResiduals("Seed — Stage K", {
        Slot::kSoilLaneA, Slot::kSoilLaneB,
        Slot::kSoilLaneC, Slot::kSoilLaneD,
        Slot::kLightningLaneC, Slot::kLightningLaneD,
    });

    //
    // Seed — Stage L
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesL = {
        Slot::kIceLaneA, Slot::kIceLaneB,
        Slot::kIceLaneC, Slot::kIceLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsL = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesL));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aDestinationsL));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage L", 15);

    const GPassFactoryMidstage::SlotArray16 aResidualsL = {
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

    pResidualBucket.AddResiduals("Seed — Stage L", {
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
    // Seed — Stage M
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesM = {
        Slot::kWoodLaneA, Slot::kWoodLaneB,
        Slot::kWoodLaneC, Slot::kWoodLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesM = {
        Slot::kPlasmaLaneA, Slot::kPlasmaLaneB,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsM = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsM =
        GPassFactoryMidstage::Concat(aWarmUpLanesM,
                             aDestinationsM);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesM));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsM));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage M", 24 - 1);

    const GPassFactoryMidstage::SlotArray24 aResidualsM = {
        Slot::kSourceLane,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
        aResidualsPool[14],
        aResidualsPool[15], aResidualsPool[16],
        aResidualsPool[17], aResidualsPool[18],
        aResidualsPool[19], aResidualsPool[20],
        aResidualsPool[21], aResidualsPool[22],
    };

    pResidualBucket.AddResiduals("Seed — Stage M", {
        Slot::kWoodLaneA, Slot::kWoodLaneB,
        Slot::kWoodLaneC, Slot::kWoodLaneD,
        Slot::kPlasmaLaneA, Slot::kPlasmaLaneB,
    });

    //
    // Seed — Stage N
    //
    const GPassFactoryMidstage::SlotArray4 aPrimarySourcesN = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray2 aWarmUpLanesN = {
        Slot::kPlasmaLaneC, Slot::kPlasmaLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinationsN = {
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aExpectedDestinationsN =
        GPassFactoryMidstage::Concat(aWarmUpLanesN,
                             aDestinationsN);

    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aPrimarySourcesN));
    pResidualBucket.Remove(GPassFactoryMidstage::ToVector(aExpectedDestinationsN));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage N", 24);

    const GPassFactoryMidstage::SlotArray24 aResidualsN = {
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
        aResidualsPool[22], aResidualsPool[23],
    };

    // Crystal is the Grow starting family, so it deliberately stays out of
    // the residual bucket.
    pResidualBucket.AddResiduals("Seed — Stage N", {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
        Slot::kPlasmaLaneC, Slot::kPlasmaLaneD,
    });

    pResidualBucket.Print("Seed — Final");

    // Stage Construction

    GSeedRunStageConfig aConfigA = BaseConfig("GSeedRunSeed_A",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigA.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesA.size());
    aConfigA.mUsesSpecialSixPassStarterGraph = true;
    aConfigA.mSlices =
        GPassFactoryStarter::Seed_AStarterSlices(
            aPrimarySourcesA,
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
        printf("MakeSeedConfig stage A was not valid with ValidateStarter");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigs[0] = aConfigA;

    // --------------------------

    GSeedRunStageConfig aConfigB = BaseConfig("GSeedRunSeed_B",
                                              pUseNonces,
                                              GAXSFormat::kN9);
    aConfigB.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesB.size());
    aConfigB.mSlices =
        GPassFactoryMidstage::SixPassThreeResidualSlices(
            aPrimarySourcesB,
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
        printf("MakeSeedConfig stage B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageB.c_str());
        exit(0);
    }
    aConfigs[1] = aConfigB;

    // --------------------------

    GSeedRunStageConfig aConfigC = BaseConfig("GSeedRunSeed_C",
                                              pUseNonces,
                                              GAXSFormat::kN7);
    aConfigC.mSlices =
        GPassFactoryMidstage::FourPassNineResidualSlices(
            aPrimarySourcesC,
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
        printf("MakeSeedConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;

    // --------------------------

    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesD =
        ArrangementFour::Arrange(aPrimarySourcesD,
                                 static_cast<int>(pCandidateIndex),
                                 9);

    GSeedRunStageConfig aConfigD = BaseConfig("GSeedRunSeed_D",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigD.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesD.size());
    aConfigD.mSlices =
        GPassFactoryTrunk::SixPassTrunkSlices(
            aArrangedPrimarySourcesD,
            aResidualsD,
            aExpectedDestinationsD);
    aConfigD.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsD.size());
    aConfigD.mHotPackCount =
        static_cast<int>(aExpectedDestinationsD.size());

    std::string aErrorMessageD;
    if (!GSeedRunStageConfigValidator::ValidateTrunk(
            aConfigD,
            GPassFactoryMidstage::ToVector(aArrangedPrimarySourcesD),
            GPassFactoryMidstage::ToVector(aResidualsD),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsD),
            &aErrorMessageD)) {
        printf("MakeSeedConfig stage D was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageD.c_str());
        exit(0);
    }
    aConfigs[3] = aConfigD;

    // --------------------------

    GSeedRunStageConfig aConfigE = BaseConfig("GSeedRunSeed_E",
                                              pUseNonces,
                                              GAXSFormat::kN9);
    aConfigE.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesE.size());
    aConfigE.mSlices =
        GPassFactoryMidstage::SixPassNineteenResidualSlices(
            aPrimarySourcesE,
            aResidualsE,
            aExpectedDestinationsE);
    aConfigE.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsE.size());
    aConfigE.mHotPackCount =
        static_cast<int>(aExpectedDestinationsE.size());

    std::string aErrorMessageE;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigE,
            GPassFactoryMidstage::ToVector(aPrimarySourcesE),
            GPassFactoryMidstage::ToVector(aResidualsE),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsE),
            &aErrorMessageE)) {
        printf("MakeSeedConfig stage E was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageE.c_str());
        exit(0);
    }
    aConfigs[4] = aConfigE;

    // --------------------------

    GSeedRunStageConfig aConfigF = BaseConfig("GSeedRunSeed_F",
                                              pUseNonces,
                                              GAXSFormat::kN7);
    aConfigF.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(
            aPrimarySourcesF,
            aResidualsF,
            aDestinationsF);
    aConfigF.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsF.size());
    aConfigF.mHotPackCount =
        static_cast<int>(aDestinationsF.size());

    std::string aErrorMessageF;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigF,
            GPassFactoryMidstage::ToVector(aPrimarySourcesF),
            GPassFactoryMidstage::ToVector(aResidualsF),
            GPassFactoryMidstage::ToVector(aDestinationsF),
            &aErrorMessageF)) {
        printf("MakeSeedConfig stage F was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageF.c_str());
        exit(0);
    }
    aConfigs[5] = aConfigF;

    // --------------------------

    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesG =
        ArrangementFour::Arrange(aPrimarySourcesG,
                                 static_cast<int>(pCandidateIndex),
                                 13);

    GSeedRunStageConfig aConfigG = BaseConfig("GSeedRunSeed_G",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigG.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesG.size());
    aConfigG.mSlices =
        GPassFactoryTrunk::SixPassTrunkSlices(
            aArrangedPrimarySourcesG,
            aResidualsG,
            aExpectedDestinationsG);
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
        printf("MakeSeedConfig stage G was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageG.c_str());
        exit(0);
    }
    aConfigs[6] = aConfigG;

    // --------------------------

    GSeedRunStageConfig aConfigH = BaseConfig("GSeedRunSeed_H",
                                              pUseNonces,
                                              GAXSFormat::kN9);
    aConfigH.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesH.size());
    aConfigH.mSlices =
        GPassFactoryMidstage::SixPassTwentyFourResidualSlices(
            aPrimarySourcesH,
            aResidualsH,
            aExpectedDestinationsH);
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
        printf("MakeSeedConfig stage H was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageH.c_str());
        exit(0);
    }
    aConfigs[7] = aConfigH;

    // --------------------------

    GSeedRunStageConfig aConfigI = BaseConfig("GSeedRunSeed_I",
                                              pUseNonces,
                                              GAXSFormat::kN7);
    aConfigI.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(
            aPrimarySourcesI,
            aResidualsI,
            aDestinationsI);
    aConfigI.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsI.size());
    aConfigI.mHotPackCount =
        static_cast<int>(aDestinationsI.size());

    std::string aErrorMessageI;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigI,
            GPassFactoryMidstage::ToVector(aPrimarySourcesI),
            GPassFactoryMidstage::ToVector(aResidualsI),
            GPassFactoryMidstage::ToVector(aDestinationsI),
            &aErrorMessageI)) {
        printf("MakeSeedConfig stage I was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageI.c_str());
        exit(0);
    }
    aConfigs[8] = aConfigI;

    // --------------------------

    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesJ =
        ArrangementFour::Arrange(aPrimarySourcesJ,
                                 static_cast<int>(pCandidateIndex),
                                 2);

    GSeedRunStageConfig aConfigJ = BaseConfig("GSeedRunSeed_J",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigJ.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesJ.size());
    aConfigJ.mSlices =
        GPassFactoryTrunk::SixPassTrunkSlices(
            aArrangedPrimarySourcesJ,
            aResidualsJ,
            aExpectedDestinationsJ);
    aConfigJ.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsJ.size());
    aConfigJ.mHotPackCount =
        static_cast<int>(aExpectedDestinationsJ.size());

    std::string aErrorMessageJ;
    if (!GSeedRunStageConfigValidator::ValidateTrunk(
            aConfigJ,
            GPassFactoryMidstage::ToVector(aArrangedPrimarySourcesJ),
            GPassFactoryMidstage::ToVector(aResidualsJ),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsJ),
            &aErrorMessageJ)) {
        printf("MakeSeedConfig stage J was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageJ.c_str());
        exit(0);
    }
    aConfigs[9] = aConfigJ;

    // --------------------------

    GSeedRunStageConfig aConfigK = BaseConfig("GSeedRunSeed_K",
                                              pUseNonces,
                                              GAXSFormat::kN9);
    aConfigK.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesK.size());
    aConfigK.mSlices =
        GPassFactoryMidstage::SixPassTwentyFourResidualSlices(
            aPrimarySourcesK,
            aResidualsK,
            aExpectedDestinationsK);
    aConfigK.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsK.size());
    aConfigK.mHotPackCount =
        static_cast<int>(aExpectedDestinationsK.size());

    std::string aErrorMessageK;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigK,
            GPassFactoryMidstage::ToVector(aPrimarySourcesK),
            GPassFactoryMidstage::ToVector(aResidualsK),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsK),
            &aErrorMessageK)) {
        printf("MakeSeedConfig stage K was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageK.c_str());
        exit(0);
    }
    aConfigs[10] = aConfigK;

    // --------------------------

    GSeedRunStageConfig aConfigL = BaseConfig("GSeedRunSeed_L",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigL.mSlices =
        GPassFactoryMidstage::FourPassSixteenResidualSlices(
            aPrimarySourcesL,
            aResidualsL,
            aDestinationsL);
    aConfigL.mExpectedSkeletonCount =
        static_cast<int>(aDestinationsL.size());
    aConfigL.mHotPackCount =
        static_cast<int>(aDestinationsL.size());

    std::string aErrorMessageL;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigL,
            GPassFactoryMidstage::ToVector(aPrimarySourcesL),
            GPassFactoryMidstage::ToVector(aResidualsL),
            GPassFactoryMidstage::ToVector(aDestinationsL),
            &aErrorMessageL)) {
        printf("MakeSeedConfig stage L was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageL.c_str());
        exit(0);
    }
    aConfigs[11] = aConfigL;

    // --------------------------

    const ArrangementFour::SlotArray4 aArrangedPrimarySourcesM =
        ArrangementFour::Arrange(aPrimarySourcesM,
                                 static_cast<int>(pCandidateIndex),
                                 6);

    GSeedRunStageConfig aConfigM = BaseConfig("GSeedRunSeed_M",
                                              pUseNonces,
                                              GAXSFormat::kN9);
    aConfigM.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesM.size());
    aConfigM.mSlices =
        GPassFactoryTrunk::SixPassTrunkSlices(
            aArrangedPrimarySourcesM,
            aResidualsM,
            aExpectedDestinationsM);
    aConfigM.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsM.size());
    aConfigM.mHotPackCount =
        static_cast<int>(aExpectedDestinationsM.size());

    std::string aErrorMessageM;
    if (!GSeedRunStageConfigValidator::ValidateTrunk(
            aConfigM,
            GPassFactoryMidstage::ToVector(aArrangedPrimarySourcesM),
            GPassFactoryMidstage::ToVector(aResidualsM),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsM),
            &aErrorMessageM)) {
        printf("MakeSeedConfig stage M was not valid with ValidateTrunk");
        printf("%s\n", aErrorMessageM.c_str());
        exit(0);
    }
    aConfigs[12] = aConfigM;

    // --------------------------

    GSeedRunStageConfig aConfigN = BaseConfig("GSeedRunSeed_N",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigN.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesN.size());
    aConfigN.mSlices =
        GPassFactoryMidstage::SixPassTwentyFourResidualSlices(
            aPrimarySourcesN,
            aResidualsN,
            aExpectedDestinationsN);
    aConfigN.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsN.size());
    aConfigN.mHotPackCount =
        static_cast<int>(aExpectedDestinationsN.size());

    std::string aErrorMessageN;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigN,
            GPassFactoryMidstage::ToVector(aPrimarySourcesN),
            GPassFactoryMidstage::ToVector(aResidualsN),
            GPassFactoryMidstage::ToVector(aExpectedDestinationsN),
            &aErrorMessageN)) {
        printf("MakeSeedConfig stage N was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageN.c_str());
        exit(0);
    }
    aConfigs[13] = aConfigN;

    return aConfigs;
}

} // namespace GSeedRunSeedConfig

GSeedRunSeed::GSeedRunSeed(const GSeedRunStageConfig &pConfig,
                           const bool pUseNonces,
                           const bool pEmitNoncePrologue)
: mStage(pConfig),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

bool GSeedRunSeed::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed::Build(TwistProgramBranch &pBranch,
                         std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
