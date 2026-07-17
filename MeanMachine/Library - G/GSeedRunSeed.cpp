//
//  GSeedRunSeed.cpp
//  MeanMachine
//

#include "GSeedRunSeed.hpp"
#include "GPassFactory.hpp"
#include "Random.hpp"
#include "GSeedRunStageConfigValidator.hpp"

#include <array>
#include <sstream>
#include <utility>

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
        case TwistDomain::kPhaseB: return 1;
        case TwistDomain::kPhaseC: return 2;
        case TwistDomain::kPhaseD: return 3;
        case TwistDomain::kPhaseE: return 4;
        case TwistDomain::kPhaseF: return 5;
        case TwistDomain::kPhaseG: return 6;
        case TwistDomain::kPhaseH: return 7;
        case TwistDomain::kPhaseA:
        default:
            return 0;
    }
}

char PhaseLetterLower(const TwistDomain pDomain) {
    return static_cast<char>('a' + PhaseIndex(pDomain));
}

std::string SeedLoopName(const TwistDomain pDomain) {
    std::string aResult = "seed_loop_";
    aResult.push_back(PhaseLetterLower(pDomain));
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

std::string NonceDeclareLine(const GSymbol &pNonceSymbol,
                             const int pIndex) {
    (void)pIndex;
    const std::uint64_t aMultiplyWord = Random::Get64HighOdd();
    const std::uint64_t aAddWord = Random::Get64High();
    const char *aDiffuseName = RandomNonceDiffuseName();
    
    std::ostringstream aLine;
    aLine << "std::uint64_t " << pNonceSymbol.mName << " = TwistMix64::"
    << aDiffuseName
    << "(pNonce * "
    << UInt64Literal(aMultiplyWord)
    << " + "
    << UInt64Literal(aAddWord) << ");";
    return aLine.str();
}

void AddSeedNoncePrologue(TwistProgramBranch &pBranch) {
    for (std::size_t i = 0U; i < kNonceVariableNames.size(); ++i) {
        pBranch.AddLine(NonceDeclareLine(GSymbol::Var(kNonceVariableNames[i]), static_cast<int>(i)));
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
                               const TwistDomain pDomain,
                               const bool pUseNonces,
                               const GAXSFormat pFormat) {
    using Slot = TwistWorkSpaceSlot;
    
    const std::string aLoopName = SeedLoopName(pDomain);
    
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = aLoopName;
    aConfig.mStartLine = "// " + pStageName + " " + aLoopName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + aLoopName + " (end)";
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = !pUseNonces;
    aConfig.mHasDomainMix = true;
    aConfig.mDomain = pDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 8;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(pDomain, Slot::kPhaseASaltOrbiterAssignA, 6);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(pDomain, Slot::kPhaseASaltOrbiterUpdateA, 6);
    aConfig.mSaltsWandererUpdate = PhaseSalts(pDomain, Slot::kPhaseASaltWandererUpdateA, 6);
    return aConfig;
}

GSeedRunStageConfig BuildSeed_AConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray3 aPrimarySources = {
        Slot::kSource, Slot::kKeyRowReadA, Slot::kKeyRowReadB,
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kWorkLaneA, Slot::kWorkLaneB,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_A",
                                             TwistDomain::kPhaseA,
                                             pUseNonces,
                                             GAXSFormat::kN9);
    
    aConfig.mMaxContextSourceCount = 4;
    aConfig.mMaxBoundSourceCount = 8;
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mBindDuplicateSourceSlots = false;
    aConfig.mSlices = GPassFactory::Seed_AStarterSlices(aPrimarySources,
                                                        aWarmUpLanes,
                                                        aDestinations);
   
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    const std::vector<Slot> aOutputs = GPassFactory::ToVector(aExpectedDestinations);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateStarter(aConfig,
                                                       aInputs, // primary inputs
                                                       aOutputs,
                                                       false,
                                                       &aErrorMessage)) {
        printf("MakeSeed_AConfig was not valid with ValidateStarter");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildSeed_BConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
    };
    const GPassFactory::SlotArray5 aResidualSources = {
        Slot::kSource, Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        Slot::kWorkLaneA, Slot::kWorkLaneB,
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kWorkLaneC, Slot::kWorkLaneD,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_B",
                                             TwistDomain::kPhaseE,
                                             pUseNonces,
                                             GAXSFormat::kN11);
    
    aConfig.mSlices = GPassFactory::SixPassFiveResidualSlices(aPrimarySources,
                                                             aResidualSources,
                                                             aExpectedDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    const std::vector<Slot> aOutputs = GPassFactory::ToVector(aExpectedDestinations);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_B was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

GSeedRunStageConfig BuildSeed_CConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactory::SlotArray9 aResidualSources = {
        Slot::kSource,
        Slot::kWorkLaneA, Slot::kWorkLaneB,
        Slot::kWorkLaneC, Slot::kWorkLaneD,
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
    };
    const GPassFactory::SlotArray2 aPrefixDestinations = {
        Slot::kScrapLaneA, Slot::kScrapLaneB,
    };
    const GPassFactory::SlotArray4 aBodyDestinations = {
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };
    
    const GPassFactory::SlotArray6 aDestinations = GPassFactory::Concat(aPrefixDestinations,
                                                                        aBodyDestinations);
    
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_C",
                                             TwistDomain::kPhaseD,
                                             pUseNonces,
                                             GAXSFormat::kN7);
    
    aConfig.mSlices = GPassFactory::SixPassNineResidualSlices(aPrimarySources,
                                                             aResidualSources,
                                                             aDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildSeed_DConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };
    const GPassFactory::SlotArray12 aResidualSources = {
        Slot::kKeyRowReadA,
        
        Slot::kWorkLaneD,
        Slot::kScrapLaneA, Slot::kScrapLaneB,
        
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
        
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
        
    };
    const GPassFactory::SlotArray2 aPrefixDestinations = {
        Slot::kScrapLaneC, Slot::kScrapLaneD,
    };
    const GPassFactory::SlotArray4 aBodyDestinations = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    
    const GPassFactory::SlotArray6 aDestinations = GPassFactory::Concat(aPrefixDestinations,
                                                                        aBodyDestinations);
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_D",
                                             TwistDomain::kPhaseC,
                                             pUseNonces,
                                             GAXSFormat::kN11);
    aConfig.mSlices = GPassFactory::SixPassTwelveResidualSlices(aPrimarySources,
                                                                aResidualSources,
                                                                aDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_D was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

// Here we diffuse [fuse] to [fire]

GSeedRunStageConfig BuildSeed_EConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactory::SlotArray14 aResidualSources = {
        Slot::kKeyRowReadB,
        
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
        
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
        
        Slot::kScrapLaneA, Slot::kScrapLaneB,
        Slot::kScrapLaneC, Slot::kScrapLaneD,
        
        Slot::kWorkLaneC,
    };
    const GPassFactory::SlotArray2 aPrefixDestinations = {
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    const GPassFactory::SlotArray4 aBodyDestinations = {
        Slot::kInvestA, Slot::kInvestB,
        Slot::kInvestC, Slot::kInvestD,
    };
    
    const GPassFactory::SlotArray6 aDestinations = GPassFactory::Concat(aPrefixDestinations,
                                                                        aBodyDestinations);

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_E",
                                             TwistDomain::kPhaseB,
                                             pUseNonces,
                                             GAXSFormat::kN9);
    aConfig.mSlices = GPassFactory::SixPassFourteenResidualSlices(aPrimarySources,
                                                                aResidualSources,
                                                                aDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_E was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildSeed_FConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kInvestA, Slot::kInvestB,
        Slot::kInvestC, Slot::kInvestD,
    };
    const GPassFactory::SlotArray16 aResidualSources = {
        Slot::kSource,
        
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
        
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
        
        Slot::kScrapLaneA, Slot::kScrapLaneB,
        Slot::kScrapLaneC, Slot::kScrapLaneD,
        
        Slot::kEarthLaneD
    };
    
    
    const GPassFactory::SlotArray2 aPrefixDestinations = {
        Slot::kSnowLaneC, Slot::kSnowLaneD,
    };
    const GPassFactory::SlotArray4 aBodyDestinations = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray6 aDestinations = GPassFactory::Concat(aPrefixDestinations,
                                                                        aBodyDestinations);

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_F",
                                             TwistDomain::kPhaseC,
                                             pUseNonces,
                                             GAXSFormat::kN11);
    aConfig.mSlices = GPassFactory::SixPassSixteenResidualSlices(aPrimarySources,
                                                                aResidualSources,
                                                                aDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_F was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

// kSnowLaneC[0] kSnowLaneD[0]

GSeedRunStageConfig BuildSeed_GConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray18 aResidualSources = {
        Slot::kKeyRowReadA,
        
        Slot::kEarthLaneA, Slot::kEarthLaneB, Slot::kEarthLaneC,
        
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        Slot::kScrapLaneC, Slot::kScrapLaneD,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
        
        Slot::kInvestA, Slot::kInvestB,
        Slot::kInvestC, Slot::kInvestD,
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    
    const GPassFactory::SlotArray2 aPrefixDestinations = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
    };
    const GPassFactory::SlotArray4 aBodyDestinations = {
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };
    const GPassFactory::SlotArray6 aDestinations = GPassFactory::Concat(aPrefixDestinations,
                                                                        aBodyDestinations);

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_G",
                                             TwistDomain::kPhaseD,
                                             pUseNonces,
                                             GAXSFormat::kN7);
    aConfig.mSlices = GPassFactory::SixPassEighteenResidualSlices(aPrimarySources,
                                                                aResidualSources,
                                                                aDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
        
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_G was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

// kSnowLaneC[1] kSnowLaneD[1]

GSeedRunStageConfig BuildSeed_HConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };
    const GPassFactory::SlotArray16 aResidualSources = {
        Slot::kKeyRowReadB,
        Slot::kExpansionLaneD,
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
        Slot::kInvestA, Slot::kInvestB,
        Slot::kInvestC, Slot::kInvestD,
        Slot::kFireLaneA, Slot::kFireLaneB,
    };
    
    const GPassFactory::SlotArray2 aPrefixDestinations = {
        Slot::kSnowLaneA, Slot::kSnowLaneB,
    };
    const GPassFactory::SlotArray4 aBodyDestinations = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    const GPassFactory::SlotArray6 aDestinations = GPassFactory::Concat(aPrefixDestinations,
                                                                        aBodyDestinations);

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_H",
                                             TwistDomain::kPhaseE,
                                             pUseNonces,
                                             GAXSFormat::kN9);
    aConfig.mSlices = GPassFactory::SixPassSixteenResidualSlices(aPrimarySources,
                                                                aResidualSources,
                                                                aDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
        
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_H was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

// Here we diffuse [fuse] to [invest_efgh]

GSeedRunStageConfig BuildSeed_IConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kInvestE, Slot::kInvestF,
        Slot::kInvestG, Slot::kInvestH,
    };
    const GPassFactory::SlotArray16 aResidualSources = {
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactory::SlotArray2 aPrefixDestinations = {
        Slot::kSnowLaneC, Slot::kSnowLaneD,
    };
    const GPassFactory::SlotArray4 aBodyDestinations = {
        Slot::kWorkLaneA, Slot::kWorkLaneB,
        Slot::kWorkLaneC, Slot::kWorkLaneD,
    };
    const GPassFactory::SlotArray6 aDestinations = GPassFactory::Concat(aPrefixDestinations,
                                                                        aBodyDestinations);

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_I",
                                             TwistDomain::kPhaseF,
                                             pUseNonces,
                                             GAXSFormat::kN7);
    aConfig.mSlices = GPassFactory::SixPassSixteenResidualSlices(aPrimarySources,
                                                                aResidualSources,
                                                                aDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
        
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_I was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

} // namespace

namespace GSeedRunSeedConfig {

GSeedRunStageConfig MakeSeed_AConfig(const bool pUseNonces) {
    return BuildSeed_AConfig(pUseNonces);
}

GSeedRunStageConfig MakeSeed_BConfig(const bool pUseNonces) {
    return BuildSeed_BConfig(pUseNonces);
}

GSeedRunStageConfig MakeSeed_CConfig(const bool pUseNonces) {
    return BuildSeed_CConfig(pUseNonces);
}

GSeedRunStageConfig MakeSeed_DConfig(const bool pUseNonces) {
    return BuildSeed_DConfig(pUseNonces);
}

GSeedRunStageConfig MakeSeed_EConfig(const bool pUseNonces) {
    return BuildSeed_EConfig(pUseNonces);
}

GSeedRunStageConfig MakeSeed_FConfig(const bool pUseNonces) {
    return BuildSeed_FConfig(pUseNonces);
}

GSeedRunStageConfig MakeSeed_GConfig(const bool pUseNonces) {
    return BuildSeed_GConfig(pUseNonces);
}

GSeedRunStageConfig MakeSeed_HConfig(const bool pUseNonces) {
    return BuildSeed_HConfig(pUseNonces);
}

GSeedRunStageConfig MakeSeed_IConfig(const bool pUseNonces) {
    return BuildSeed_IConfig(pUseNonces);
}

}

GSeedRunSeed_A::GSeedRunSeed_A(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: GSeedRunSeed_A(GSeedRunSeedConfig::MakeSeed_AConfig(pUseNonces),
                 pUseNonces,
                 pEmitNoncePrologue) {
}

GSeedRunSeed_A::GSeedRunSeed_A(GSeedRunStageConfig pConfig,
                               const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(std::move(pConfig)),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

GSeedRunSeed_A::~GSeedRunSeed_A() {
}

void GSeedRunSeed_A::Reset() {
    mStage.Reset();
}

bool GSeedRunSeed_A::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed_A::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunSeed_B::GSeedRunSeed_B(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: GSeedRunSeed_B(GSeedRunSeedConfig::MakeSeed_BConfig(pUseNonces),
                 pUseNonces,
                 pEmitNoncePrologue) {
}

GSeedRunSeed_B::GSeedRunSeed_B(GSeedRunStageConfig pConfig,
                               const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(std::move(pConfig)),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

GSeedRunSeed_B::~GSeedRunSeed_B() {
}

void GSeedRunSeed_B::Reset() {
    mStage.Reset();
}

bool GSeedRunSeed_B::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed_B::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunSeed_C::GSeedRunSeed_C(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: GSeedRunSeed_C(GSeedRunSeedConfig::MakeSeed_CConfig(pUseNonces),
                 pUseNonces,
                 pEmitNoncePrologue) {
}

GSeedRunSeed_C::GSeedRunSeed_C(GSeedRunStageConfig pConfig,
                               const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(std::move(pConfig)),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

GSeedRunSeed_C::~GSeedRunSeed_C() {
}

void GSeedRunSeed_C::Reset() {
    mStage.Reset();
}

bool GSeedRunSeed_C::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed_C::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunSeed_D::GSeedRunSeed_D(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: GSeedRunSeed_D(GSeedRunSeedConfig::MakeSeed_DConfig(pUseNonces),
                 pUseNonces,
                 pEmitNoncePrologue) {
}

GSeedRunSeed_D::GSeedRunSeed_D(GSeedRunStageConfig pConfig,
                               const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(std::move(pConfig)),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

GSeedRunSeed_D::~GSeedRunSeed_D() {
}

void GSeedRunSeed_D::Reset() {
    mStage.Reset();
}

bool GSeedRunSeed_D::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed_D::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunSeed_E::GSeedRunSeed_E(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: GSeedRunSeed_E(GSeedRunSeedConfig::MakeSeed_EConfig(pUseNonces),
                 pUseNonces,
                 pEmitNoncePrologue) {
}

GSeedRunSeed_E::GSeedRunSeed_E(GSeedRunStageConfig pConfig,
                               const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(std::move(pConfig)),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

GSeedRunSeed_E::~GSeedRunSeed_E() {
}

void GSeedRunSeed_E::Reset() {
    mStage.Reset();
}

bool GSeedRunSeed_E::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed_E::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunSeed_F::GSeedRunSeed_F(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: GSeedRunSeed_F(GSeedRunSeedConfig::MakeSeed_FConfig(pUseNonces),
                 pUseNonces,
                 pEmitNoncePrologue) {
}

GSeedRunSeed_F::GSeedRunSeed_F(GSeedRunStageConfig pConfig,
                               const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(std::move(pConfig)),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

GSeedRunSeed_F::~GSeedRunSeed_F() {
}

void GSeedRunSeed_F::Reset() {
    mStage.Reset();
}

bool GSeedRunSeed_F::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed_F::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunSeed_G::GSeedRunSeed_G(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: GSeedRunSeed_G(GSeedRunSeedConfig::MakeSeed_GConfig(pUseNonces),
                 pUseNonces,
                 pEmitNoncePrologue) {
}

GSeedRunSeed_G::GSeedRunSeed_G(GSeedRunStageConfig pConfig,
                               const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(std::move(pConfig)),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

GSeedRunSeed_G::~GSeedRunSeed_G() {
}

void GSeedRunSeed_G::Reset() {
    mStage.Reset();
}

bool GSeedRunSeed_G::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed_G::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunSeed_H::GSeedRunSeed_H(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: GSeedRunSeed_H(GSeedRunSeedConfig::MakeSeed_HConfig(pUseNonces),
                 pUseNonces,
                 pEmitNoncePrologue) {
}

GSeedRunSeed_H::GSeedRunSeed_H(GSeedRunStageConfig pConfig,
                               const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(std::move(pConfig)),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

GSeedRunSeed_H::~GSeedRunSeed_H() {
}

void GSeedRunSeed_H::Reset() {
    mStage.Reset();
}

bool GSeedRunSeed_H::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed_H::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunSeed_I::GSeedRunSeed_I(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: GSeedRunSeed_I(GSeedRunSeedConfig::MakeSeed_IConfig(pUseNonces),
                 pUseNonces,
                 pEmitNoncePrologue) {
}

GSeedRunSeed_I::GSeedRunSeed_I(GSeedRunStageConfig pConfig,
                               const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(std::move(pConfig)),
  mUseNonces(pUseNonces),
  mEmitNoncePrologue(pEmitNoncePrologue) {
}

GSeedRunSeed_I::~GSeedRunSeed_I() {
}

void GSeedRunSeed_I::Reset() {
    mStage.Reset();
}

bool GSeedRunSeed_I::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunSeed_I::Build(TwistProgramBranch &pBranch,
                           std::string *pErrorMessage) {
    if (mUseNonces && mEmitNoncePrologue) {
        AddSeedNoncePrologue(pBranch);
    }
    return mStage.Build(pBranch, pErrorMessage);
}
