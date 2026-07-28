//
//  GSeedRunSeed.cpp
//  MeanMachine
//

#include "GSeedRunSeed.hpp"
#include "GPassFactory.hpp"
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
    const int aOffset = PhaseIndex(pDomain) * 18;

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
    aConfig.mHasDomainMix = true;
    aConfig.mDomain = kDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterAssignA, 6);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltOrbiterUpdateA, 6);
    aConfig.mSaltsWandererUpdate = PhaseSalts(kDomain, Slot::kKeyRotateASaltWandererUpdateA, 6);
    return aConfig;
}

} // namespace

namespace GSeedRunSeedConfig {

SeedStageConfigs MakeSeedConfig(const bool pUseNonces,
                                ResidualBucket &pResidualBucket) {
    using Slot = TwistWorkSpaceSlot;

    SeedStageConfigs aConfigs;
    std::vector<Slot> aResidualsPool;

    std::vector<Slot> aRandomSnowA = {
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
    };
    Random::Shuffle(&aRandomSnowA);

    std::vector<Slot> aRandomSnowB = {
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
    };
    Random::Shuffle(&aRandomSnowB);

    //
    // Seed — Stage A
    //
    const GPassFactory::SlotArray1 aPrimarySourcesA = {
        Slot::kSource,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesA = {
        Slot::kPlasmaLaneA, Slot::kPlasmaLaneB,
    };
    const GPassFactory::SlotArray4 aDestinationsA = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsA =
        GPassFactory::Concat(aWarmUpLanesA,
                             aDestinationsA);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesA));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsA));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage A", 4 - 4);

    const GPassFactory::SlotArray4 aResidualsA = {
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
    };

    pResidualBucket.AddResiduals("Seed — Stage A", {
        Slot::kPlasmaLaneA, Slot::kPlasmaLaneB,
    });

    //
    // Seed — Stage B
    //
    const GPassFactory::SlotArray4 aPrimarySourcesB = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesB = {
        Slot::kPlasmaLaneC, Slot::kPlasmaLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsB = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsB =
        GPassFactory::Concat(aWarmUpLanesB,
                             aDestinationsB);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesB));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsB));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage B", 7 - 5);

    const GPassFactory::SlotArray7 aResidualsB = {
        Slot::kSource,
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
        aResidualsPool[0], aResidualsPool[1],
    };

    pResidualBucket.AddResiduals("Seed — Stage B", {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        Slot::kPlasmaLaneC, Slot::kPlasmaLaneD,
    });

    //
    // Seed — Stage C
    //
    const GPassFactory::SlotArray4 aPrimarySourcesC = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsC = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesC));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsC));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage C", 13 - 5);

    const GPassFactory::SlotArray13 aResidualsC = {
        Slot::kSource,
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
    };

    pResidualBucket.AddResiduals("Seed — Stage C", {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    });

    /*
    TwistDiffuse::DiffuseWithDomainWords(
                aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
                aHeartLaneA, aHeartLaneB, aHeartLaneC, aHeartLaneD, // output lanes
                aPlasmaLaneC, aPlasmaLaneD, aMagmaLaneC, aMagmaLaneD, // index shuffle seeds
                aMagmaLaneA, aMagmaLaneB); // operation seeds
    */
                                           
    //
    // Seed — Stage D
    //
    const GPassFactory::SlotArray4 aPrimarySourcesD = {
        Slot::kHeartLaneA, Slot::kHeartLaneB,
        Slot::kHeartLaneC, Slot::kHeartLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesD = {
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
    };
    const GPassFactory::SlotArray4 aDestinationsD = {
        Slot::kShadowLaneA, Slot::kShadowLaneB,
        Slot::kShadowLaneC, Slot::kShadowLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsD =
        GPassFactory::Concat(aWarmUpLanesD,
                             aDestinationsD);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesD));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsD));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage D", 17 - 5);

    const GPassFactory::SlotArray17 aResidualsD = {
        Slot::kSource,
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
    };

    pResidualBucket.AddResiduals("Seed — Stage D", {
        Slot::kHeartLaneA, Slot::kHeartLaneB,
        Slot::kHeartLaneC, Slot::kHeartLaneD,
        Slot::kCrystalLaneA, Slot::kCrystalLaneB,
    });

    //
    // Seed — Stage E
    //
    const GPassFactory::SlotArray4 aPrimarySourcesE = {
        Slot::kShadowLaneA, Slot::kShadowLaneB,
        Slot::kShadowLaneC, Slot::kShadowLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesE = {
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsE = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsE =
        GPassFactory::Concat(aWarmUpLanesE,
                             aDestinationsE);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesE));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsE));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage E", 21 - 3);

    const GPassFactory::SlotArray21 aResidualsE = {
        Slot::kSource, Slot::kSnowLaneA, Slot::kSnowLaneB,
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
        Slot::kCrystalLaneC, Slot::kCrystalLaneD,
    });

    //
    // Seed — Stage F
    //
    const GPassFactory::SlotArray4 aPrimarySourcesF = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsF = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    
    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesF));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsF));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage F", 16 - 3);

    const GPassFactory::SlotArray16 aResidualsF = {
        Slot::kSource, Slot::kSnowLaneC, Slot::kSnowLaneD,
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12],
    };

    pResidualBucket.AddResiduals("Seed — Stage F", {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    });

    /*
    TwistDiffuse::DiffuseWithDomainWords(
            aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
            aWindLaneA, aWindLaneB, aWindLaneC, aWindLaneD, // output lanes
            aCrystalLaneC, aCrystalLaneD, aEarthLaneC, aEarthLaneD, // index shuffle seeds
            aEarthLaneA, aEarthLaneB); // operation seeds
    */

    //
    // Seed — Stage G
    //
    const GPassFactory::SlotArray4 aPrimarySourcesG = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesG = {
        Slot::kAetherLaneA, Slot::kAetherLaneB,
    };
    const GPassFactory::SlotArray4 aDestinationsG = {
        Slot::kVaporLaneA, Slot::kVaporLaneB,
        Slot::kVaporLaneC, Slot::kVaporLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsG =
        GPassFactory::Concat(aWarmUpLanesG,
                             aDestinationsG);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesG));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsG));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage G", 24 - 2);

    const GPassFactory::SlotArray24 aResidualsG = {
        aRandomSnowA[0], aRandomSnowA[1],
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

    pResidualBucket.AddResiduals("Seed — Stage G", {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
        Slot::kAetherLaneA, Slot::kAetherLaneB,
    });

    //
    // Seed — Stage H
    //
    const GPassFactory::SlotArray4 aPrimarySourcesH = {
        Slot::kVaporLaneA, Slot::kVaporLaneB,
        Slot::kVaporLaneC, Slot::kVaporLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesH = {
        Slot::kAetherLaneC, Slot::kAetherLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsH = {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsH =
        GPassFactory::Concat(aWarmUpLanesH,
                             aDestinationsH);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesH));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsH));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage H", 24 - 2);

    const GPassFactory::SlotArray24 aResidualsH = {
        aRandomSnowA[2], aRandomSnowA[3],
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

    pResidualBucket.AddResiduals("Seed — Stage H", {
        Slot::kVaporLaneA, Slot::kVaporLaneB,
        Slot::kVaporLaneC, Slot::kVaporLaneD,
        Slot::kAetherLaneC, Slot::kAetherLaneD,
    });

    //
    // Seed — Stage I
    //
    const GPassFactory::SlotArray4 aPrimarySourcesI = {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsI = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    
    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesI));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsI));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage I", 16 - 2);

    const GPassFactory::SlotArray16 aResidualsI = {
        Slot::kSource, aRandomSnowB[0],
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
    };

    pResidualBucket.AddResiduals("Seed — Stage I", {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    });

    /*
    TwistDiffuse::DiffuseWithDomainWords(
            aFuseLaneA, aFuseLaneB, aFuseLaneC, aFuseLaneD,  // input lanes
            aCelestialLaneA, aCelestialLaneB, aCelestialLaneC, aCelestialLaneD, // output lanes
            aAetherLaneC, aAetherLaneD, aFireLaneC, aFireLaneD, // index shuffle seeds
            aFireLaneA, aFireLaneB); // operation seeds
    */

    //
    // Seed — Stage J
    //
    const GPassFactory::SlotArray4 aPrimarySourcesJ = {
        Slot::kCelestialLaneA, Slot::kCelestialLaneB,
        Slot::kCelestialLaneC, Slot::kCelestialLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesJ = {
        Slot::kLightningLaneA, Slot::kLightningLaneB,
    };
    const GPassFactory::SlotArray4 aDestinationsJ = {
        Slot::kSoilLaneA, Slot::kSoilLaneB,
        Slot::kSoilLaneC, Slot::kSoilLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsJ =
        GPassFactory::Concat(aWarmUpLanesJ,
                             aDestinationsJ);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesJ));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsJ));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage J", 24 - 2);

    const GPassFactory::SlotArray24 aResidualsJ = {
        Slot::kSource, aRandomSnowB[1],
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

    pResidualBucket.AddResiduals("Seed — Stage J", {
        Slot::kCelestialLaneA, Slot::kCelestialLaneB,
        Slot::kCelestialLaneC, Slot::kCelestialLaneD,
        Slot::kLightningLaneA, Slot::kLightningLaneB,
    });

    //
    // Seed — Stage K
    //
    const GPassFactory::SlotArray4 aPrimarySourcesK = {
        Slot::kSoilLaneA, Slot::kSoilLaneB,
        Slot::kSoilLaneC, Slot::kSoilLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesK = {
        Slot::kLightningLaneC, Slot::kLightningLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsK = {
        Slot::kIceLaneA, Slot::kIceLaneB,
        Slot::kIceLaneC, Slot::kIceLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsK =
        GPassFactory::Concat(aWarmUpLanesK,
                             aDestinationsK);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesK));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsK));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage K", 24 - 2);

    const GPassFactory::SlotArray24 aResidualsK = {
        Slot::kSource, aRandomSnowB[2],
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

    pResidualBucket.AddResiduals("Seed — Stage K", {
        Slot::kSoilLaneA, Slot::kSoilLaneB,
        Slot::kSoilLaneC, Slot::kSoilLaneD,
        Slot::kLightningLaneC, Slot::kLightningLaneD,
    });

    //
    // Seed — Stage L
    //
    const GPassFactory::SlotArray4 aPrimarySourcesL = {
        Slot::kIceLaneA, Slot::kIceLaneB,
        Slot::kIceLaneC, Slot::kIceLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsL = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesL));
    pResidualBucket.Remove(GPassFactory::ToVector(aDestinationsL));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage L", 16 - 2);

    const GPassFactory::SlotArray16 aResidualsL = {
        Slot::kSource, aRandomSnowB[3],
        aResidualsPool[0], aResidualsPool[1],
        aResidualsPool[2], aResidualsPool[3],
        aResidualsPool[4], aResidualsPool[5],
        aResidualsPool[6], aResidualsPool[7],
        aResidualsPool[8], aResidualsPool[9],
        aResidualsPool[10], aResidualsPool[11],
        aResidualsPool[12], aResidualsPool[13],
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
    const GPassFactory::SlotArray4 aPrimarySourcesM = {
        Slot::kWoodLaneA, Slot::kWoodLaneB,
        Slot::kWoodLaneC, Slot::kWoodLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesM = {
        Slot::kPlasmaLaneA, Slot::kPlasmaLaneB,
    };
    const GPassFactory::SlotArray4 aDestinationsM = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsM =
        GPassFactory::Concat(aWarmUpLanesM,
                             aDestinationsM);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesM));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsM));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage M", 24 - 1);

    const GPassFactory::SlotArray24 aResidualsM = {
        Slot::kSource,
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
    const GPassFactory::SlotArray4 aPrimarySourcesN = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanesN = {
        Slot::kPlasmaLaneC, Slot::kPlasmaLaneD,
    };
    const GPassFactory::SlotArray4 aDestinationsN = {
        Slot::kPoisonLaneA, Slot::kPoisonLaneB,
        Slot::kPoisonLaneC, Slot::kPoisonLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinationsN =
        GPassFactory::Concat(aWarmUpLanesN,
                             aDestinationsN);

    pResidualBucket.Remove(GPassFactory::ToVector(aPrimarySourcesN));
    pResidualBucket.Remove(GPassFactory::ToVector(aExpectedDestinationsN));

    aResidualsPool =
        pResidualBucket.Withdraw("Seed — Stage N", 24);

    const GPassFactory::SlotArray24 aResidualsN = {
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

    // Poison is the GrowA starting family, so it deliberately stays out of
    // the residual bucket.
    pResidualBucket.AddResiduals("Seed — Stage N", {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB,
        Slot::kMagmaLaneC, Slot::kMagmaLaneD,
        Slot::kPlasmaLaneC, Slot::kPlasmaLaneD,
    });

    pResidualBucket.Print("Seed — Final");

    // --------------------------
    // --------------------------
    // --------------------------

    GSeedRunStageConfig aConfigA = BaseConfig("GSeedRunSeed_A",
                                              pUseNonces,
                                              GAXSFormat::kN9);
    aConfigA.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesA.size());
    aConfigA.mBindDuplicateSourceSlots = true;
    aConfigA.mSlices =
        GPassFactory::SixPassOneInputFourResidualSlices(
            aPrimarySourcesA,
            aResidualsA,
            aWarmUpLanesA,
            aDestinationsA);
    aConfigA.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsA.size());
    aConfigA.mHotPackCount =
        static_cast<int>(aExpectedDestinationsA.size());

    std::string aErrorMessageA;
    if (!GSeedRunStageConfigValidator::ValidateStarterWithResiduals(
            aConfigA,
            GPassFactory::ToVector(aPrimarySourcesA),
            GPassFactory::ToVector(aResidualsA),
            GPassFactory::ToVector(aExpectedDestinationsA),
            &aErrorMessageA)) {
        printf("MakeSeedConfig stage A was not valid with ValidateStarterWithResiduals");
        printf("%s\n", aErrorMessageA.c_str());
        exit(0);
    }
    aConfigs[0] = aConfigA;

    // --------------------------

    GSeedRunStageConfig aConfigB = BaseConfig("GSeedRunSeed_B",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigB.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesB.size());
    aConfigB.mSlices =
        GPassFactory::SixPassSevenResidualSlices(
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
            GPassFactory::ToVector(aPrimarySourcesB),
            GPassFactory::ToVector(aResidualsB),
            GPassFactory::ToVector(aExpectedDestinationsB),
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
        GPassFactory::FourPassThirteenResidualSlices(
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
            GPassFactory::ToVector(aPrimarySourcesC),
            GPassFactory::ToVector(aResidualsC),
            GPassFactory::ToVector(aDestinationsC),
            &aErrorMessageC)) {
        printf("MakeSeedConfig stage C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageC.c_str());
        exit(0);
    }
    aConfigs[2] = aConfigC;

    // --------------------------

    GSeedRunStageConfig aConfigD = BaseConfig("GSeedRunSeed_D",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigD.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesD.size());
    aConfigD.mSlices =
        GPassFactory::SixPassSeventeenResidualSlices(
            aPrimarySourcesD,
            aResidualsD,
            aExpectedDestinationsD);
    aConfigD.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsD.size());
    aConfigD.mHotPackCount =
        static_cast<int>(aExpectedDestinationsD.size());

    std::string aErrorMessageD;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigD,
            GPassFactory::ToVector(aPrimarySourcesD),
            GPassFactory::ToVector(aResidualsD),
            GPassFactory::ToVector(aExpectedDestinationsD),
            &aErrorMessageD)) {
        printf("MakeSeedConfig stage D was not valid with ValidateMidstage");
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
        GPassFactory::SixPassTwentyOneResidualSlices(
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
            GPassFactory::ToVector(aPrimarySourcesE),
            GPassFactory::ToVector(aResidualsE),
            GPassFactory::ToVector(aExpectedDestinationsE),
            &aErrorMessageE)) {
        printf("MakeSeedConfig stage E was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageE.c_str());
        exit(0);
    }
    aConfigs[4] = aConfigE;

    // --------------------------

    GSeedRunStageConfig aConfigF = BaseConfig("GSeedRunSeed_F",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigF.mSlices =
        GPassFactory::FourPassSixteenResidualSlices(
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
            GPassFactory::ToVector(aPrimarySourcesF),
            GPassFactory::ToVector(aResidualsF),
            GPassFactory::ToVector(aDestinationsF),
            &aErrorMessageF)) {
        printf("MakeSeedConfig stage F was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageF.c_str());
        exit(0);
    }
    aConfigs[5] = aConfigF;

    // --------------------------

    GSeedRunStageConfig aConfigG = BaseConfig("GSeedRunSeed_G",
                                              pUseNonces,
                                              GAXSFormat::kN7);
    aConfigG.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesG.size());
    aConfigG.mSlices =
        GPassFactory::SixPassTwentyFourResidualSlices(
            aPrimarySourcesG,
            aResidualsG,
            aExpectedDestinationsG);
    aConfigG.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsG.size());
    aConfigG.mHotPackCount =
        static_cast<int>(aExpectedDestinationsG.size());

    std::string aErrorMessageG;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigG,
            GPassFactory::ToVector(aPrimarySourcesG),
            GPassFactory::ToVector(aResidualsG),
            GPassFactory::ToVector(aExpectedDestinationsG),
            &aErrorMessageG)) {
        printf("MakeSeedConfig stage G was not valid with ValidateMidstage");
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
        GPassFactory::SixPassTwentyFourResidualSlices(
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
            GPassFactory::ToVector(aPrimarySourcesH),
            GPassFactory::ToVector(aResidualsH),
            GPassFactory::ToVector(aExpectedDestinationsH),
            &aErrorMessageH)) {
        printf("MakeSeedConfig stage H was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageH.c_str());
        exit(0);
    }
    aConfigs[7] = aConfigH;

    // --------------------------

    GSeedRunStageConfig aConfigI = BaseConfig("GSeedRunSeed_I",
                                              pUseNonces,
                                              GAXSFormat::kN11);
    aConfigI.mSlices =
        GPassFactory::FourPassSixteenResidualSlices(
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
            GPassFactory::ToVector(aPrimarySourcesI),
            GPassFactory::ToVector(aResidualsI),
            GPassFactory::ToVector(aDestinationsI),
            &aErrorMessageI)) {
        printf("MakeSeedConfig stage I was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageI.c_str());
        exit(0);
    }
    aConfigs[8] = aConfigI;

    // --------------------------

    GSeedRunStageConfig aConfigJ = BaseConfig("GSeedRunSeed_J",
                                              pUseNonces,
                                              GAXSFormat::kN7);
    aConfigJ.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesJ.size());
    aConfigJ.mSlices =
        GPassFactory::SixPassTwentyFourResidualSlices(
            aPrimarySourcesJ,
            aResidualsJ,
            aExpectedDestinationsJ);
    aConfigJ.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsJ.size());
    aConfigJ.mHotPackCount =
        static_cast<int>(aExpectedDestinationsJ.size());

    std::string aErrorMessageJ;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigJ,
            GPassFactory::ToVector(aPrimarySourcesJ),
            GPassFactory::ToVector(aResidualsJ),
            GPassFactory::ToVector(aExpectedDestinationsJ),
            &aErrorMessageJ)) {
        printf("MakeSeedConfig stage J was not valid with ValidateMidstage");
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
        GPassFactory::SixPassTwentyFourResidualSlices(
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
            GPassFactory::ToVector(aPrimarySourcesK),
            GPassFactory::ToVector(aResidualsK),
            GPassFactory::ToVector(aExpectedDestinationsK),
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
        GPassFactory::FourPassSixteenResidualSlices(
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
            GPassFactory::ToVector(aPrimarySourcesL),
            GPassFactory::ToVector(aResidualsL),
            GPassFactory::ToVector(aDestinationsL),
            &aErrorMessageL)) {
        printf("MakeSeedConfig stage L was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageL.c_str());
        exit(0);
    }
    aConfigs[11] = aConfigL;

    // --------------------------

    GSeedRunStageConfig aConfigM = BaseConfig("GSeedRunSeed_M",
                                              pUseNonces,
                                              GAXSFormat::kN7);
    aConfigM.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesM.size());
    aConfigM.mSlices =
        GPassFactory::SixPassTwentyFourResidualSlices(
            aPrimarySourcesM,
            aResidualsM,
            aExpectedDestinationsM);
    aConfigM.mExpectedSkeletonCount =
        static_cast<int>(aExpectedDestinationsM.size());
    aConfigM.mHotPackCount =
        static_cast<int>(aExpectedDestinationsM.size());

    std::string aErrorMessageM;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(
            aConfigM,
            GPassFactory::ToVector(aPrimarySourcesM),
            GPassFactory::ToVector(aResidualsM),
            GPassFactory::ToVector(aExpectedDestinationsM),
            &aErrorMessageM)) {
        printf("MakeSeedConfig stage M was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessageM.c_str());
        exit(0);
    }
    aConfigs[12] = aConfigM;

    // --------------------------

    GSeedRunStageConfig aConfigN = BaseConfig("GSeedRunSeed_N",
                                              pUseNonces,
                                              GAXSFormat::kN9);
    aConfigN.mWarmupDestinationCount =
        static_cast<int>(aWarmUpLanesN.size());
    aConfigN.mSlices =
        GPassFactory::SixPassTwentyFourResidualSlices(
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
            GPassFactory::ToVector(aPrimarySourcesN),
            GPassFactory::ToVector(aResidualsN),
            GPassFactory::ToVector(aExpectedDestinationsN),
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
