//
//  GSeedRunSeed.cpp
//  MeanMachine
//

#include "GSeedRunSeed.hpp"
#include "Random.hpp"
#include "GSeedRunStageConfigValidator.hpp"

#include <array>
#include <sstream>

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
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(pDomain, Slot::kPhaseASaltOrbiterAssignA, 6);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(pDomain, Slot::kPhaseASaltOrbiterUpdateA, 6);
    aConfig.mSaltsWandererUpdate = PhaseSalts(pDomain, Slot::kPhaseASaltWandererUpdateA, 6);
    return aConfig;
}

std::vector<GSeedRunStageSliceSpec> FourPassDiverseSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                          const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                          const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    std::vector<TwistWorkSpaceSlot> aResiduals = pResiduals;
    Random::Shuffle(&aResiduals);

    return {
        {{pPrimary[0], pPrimary[1], aResiduals[0]},
         {pPrimary[2], pPrimary[3], aResiduals[1]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], pPrimary[3], aResiduals[2]},
         {pPrimary[0], pPrimary[1], aResiduals[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[0], pPrimary[1], aResiduals[4]},
         {pDestinations[0], pPrimary[2], aResiduals[5]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], pPrimary[3], aResiduals[6]},
         {pDestinations[1], pPrimary[1], aResiduals[7]},
         pDestinations[3],
         true},
    };
}

std::vector<GSeedRunStageSliceSpec> SixPassDiverseSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                         const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                         const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    std::vector<TwistWorkSpaceSlot> aResiduals = pResiduals;
    Random::Shuffle(&aResiduals);

    return {
        {{pPrimary[0], pPrimary[1], aResiduals[0]},
         {pPrimary[2], pPrimary[3], aResiduals[1]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], pPrimary[3], aResiduals[2]},
         {pPrimary[0], pPrimary[1], aResiduals[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[0], aResiduals[4]},
         {pDestinations[0], pPrimary[2]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], aResiduals[5]},
         {pDestinations[1], pPrimary[3]},
         pDestinations[3],
         true},

        {{pDestinations[3], pDestinations[1], aResiduals[6]},
         {pDestinations[2], pDestinations[0]},
         pDestinations[4],
         false},

        {{pDestinations[4], pDestinations[2], aResiduals[7]},
         {pDestinations[3], pPrimary[1]},
         pDestinations[5],
         true},
    };
}

std::vector<GSeedRunStageSliceSpec> SixPassRecentResidualSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                                const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                                const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    std::vector<TwistWorkSpaceSlot> aResiduals = pResiduals;
    Random::Shuffle(&aResiduals);

    return {
        {{pPrimary[0], pPrimary[1], aResiduals[0]},
         {pPrimary[2], pPrimary[3]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], aResiduals[1]},
         {pPrimary[0], pPrimary[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[3], aResiduals[2]},
         {pDestinations[0], pPrimary[1], pPrimary[0]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], aResiduals[3]},
         {pDestinations[1], pPrimary[3], pPrimary[2]},
         pDestinations[3],
         true},

        {{pDestinations[3], pDestinations[2], pPrimary[1]},
         {pPrimary[2], pDestinations[0], pDestinations[1]},
         pDestinations[4],
         false},

        {{pDestinations[4], pPrimary[0], pPrimary[1]},
         {pDestinations[3], pDestinations[2], pDestinations[1]},
         pDestinations[5],
         true},
    };
}

GSeedRunStageConfig MakeSeed_AConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_A",
                                             TwistDomain::kPhaseA,
                                             pUseNonces,
                                             GAXSFormat::kN11);
    
    aConfig.mMaxContextSourceCount = 5;
    aConfig.mMaxBoundSourceCount = 10;
    aConfig.mWarmupDestinationCount = 4;
    aConfig.mBindDuplicateSourceSlots = true;
    aConfig.mSliceDomains = {
        TwistDomain::kPhaseE, TwistDomain::kPhaseE, TwistDomain::kPhaseE,
        TwistDomain::kPhaseF, TwistDomain::kPhaseF, TwistDomain::kPhaseF,
        TwistDomain::kPhaseG, TwistDomain::kPhaseG, TwistDomain::kPhaseG,
        TwistDomain::kPhaseH, TwistDomain::kPhaseH, TwistDomain::kPhaseH,
    };
    
    aConfig.mSlices = {
        {{Slot::kKeyRowReadA, Slot::kKeyRowReadB},
         {Slot::kKeyRowReadA, Slot::kSource},
            Slot::kWorkLaneA,
            false},
        
        {{Slot::kWorkLaneA, Slot::kKeyRowReadA},
         {Slot::kKeyRowReadB, Slot::kSource},
            Slot::kWorkLaneB,
            true},
        
        {{Slot::kWorkLaneB, Slot::kKeyRowReadB},
         {Slot::kKeyRowReadA, Slot::kSource, Slot::kWorkLaneA},
            Slot::kWorkLaneC,
            false},
        
        {{Slot::kWorkLaneC, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneA},
         {Slot::kKeyRowReadA, Slot::kWorkLaneB},
            Slot::kWorkLaneD,
            true},
        
        {{Slot::kWorkLaneD, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneB},
         {Slot::kWorkLaneA, Slot::kWorkLaneC},
            Slot::kFireLaneA,
            false},
        
        {{Slot::kFireLaneA, Slot::kWorkLaneC},
         {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneB, Slot::kWorkLaneA},
            Slot::kFireLaneB,
            true},
        
        {{Slot::kFireLaneB, Slot::kKeyRowReadA, Slot::kSource, Slot::kWorkLaneA},
         {Slot::kKeyRowReadB, Slot::kWorkLaneD, Slot::kFireLaneA},
            Slot::kFireLaneC,
            false},
        
        {{Slot::kFireLaneC, Slot::kSource, Slot::kFireLaneA, Slot::kWorkLaneA},
         {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kFireLaneB, Slot::kWorkLaneB},
            Slot::kFireLaneD,
            true},
        
        {{Slot::kFireLaneD, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kFireLaneC},
         {Slot::kSource, Slot::kFireLaneA, Slot::kWorkLaneC, Slot::kWorkLaneD},
            Slot::kExpansionLaneA,
            false},
        
        {{Slot::kExpansionLaneA, Slot::kKeyRowReadA, Slot::kFireLaneD, Slot::kFireLaneB},
         {Slot::kKeyRowReadB, Slot::kSource, Slot::kFireLaneC, Slot::kWorkLaneD},
            Slot::kExpansionLaneB,
            true},
        
        {{Slot::kExpansionLaneB, Slot::kFireLaneD, Slot::kKeyRowReadB, Slot::kFireLaneC},
         {Slot::kKeyRowReadA, Slot::kSource, Slot::kExpansionLaneA, Slot::kFireLaneB},
            Slot::kExpansionLaneC,
            false},
        
        {{Slot::kExpansionLaneC, Slot::kKeyRowReadA},
         {Slot::kFireLaneD, Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kKeyRowReadB},
            Slot::kExpansionLaneD,
            true},
        
    };
   
    aConfig.mExpectedSkeletonCount = 12;
    
    std::vector<Slot> aInputs;
    aInputs = {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource};

    std::vector<Slot> aOutputs;
    aOutputs = {
        Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD,
        Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD};
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateStarter(aConfig,
                                                       aInputs, // primary inputs
                                                       aOutputs,
                                                       true,
                                                       &aErrorMessage)) {
        printf("MakeSeed_AConfig was not valid with ValidateStarter");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig MakeSeed_BConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_B",
                                             TwistDomain::kPhaseA,
                                             pUseNonces,
                                             GAXSFormat::kN5);
    
    aConfig.mSlices = SixPassRecentResidualSlices({Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                                  {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                                  {Slot::kInvestA, Slot::kInvestB,
                                                   Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD };

    std::vector<Slot> aResiduals;
    aResiduals = { Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD };

    std::vector<Slot> aOutputs;
    aOutputs = { Slot::kInvestA, Slot::kInvestB, Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD };
    
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

GSeedRunStageConfig MakeSeed_CConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_C",
                                             TwistDomain::kPhaseB,
                                             pUseNonces,
                                             GAXSFormat::kN9);
    
    aConfig.mSlices = SixPassDiverseSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                           {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                            Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                           {Slot::kInvestC, Slot::kInvestD,
                                            Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD };

    std::vector<Slot> aResiduals;
    aResiduals = { Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD};

    std::vector<Slot> aOutputs;
    aOutputs = { Slot::kInvestC, Slot::kInvestD, Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD };
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_C was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

/*
 Now matrix diffuses [work] -> [expansion]
 */

GSeedRunStageConfig MakeSeed_DConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_D",
                                             TwistDomain::kPhaseD,
                                             pUseNonces,
                                             GAXSFormat::kN7);
    aConfig.mSlices = {
        {{Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kInvestA},
         {Slot::kExpansionLaneC, Slot::kExpansionLaneD, Slot::kInvestB},
         Slot::kSnowLaneA,
         false},

        {{Slot::kSnowLaneA, Slot::kExpansionLaneC, Slot::kExpansionLaneD, Slot::kInvestC},
         {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kInvestD},
         Slot::kSnowLaneB,
         true},

        {{Slot::kSnowLaneB, Slot::kExpansionLaneA, Slot::kFireLaneA},
         {Slot::kSnowLaneA, Slot::kExpansionLaneC},
         Slot::kInvestA,
         false},

        {{Slot::kInvestA, Slot::kSnowLaneA, Slot::kFireLaneB},
         {Slot::kSnowLaneB, Slot::kExpansionLaneD},
         Slot::kInvestB,
         true},

        {{Slot::kInvestB, Slot::kSnowLaneB, Slot::kFireLaneC},
         {Slot::kInvestA, Slot::kSnowLaneA},
         Slot::kInvestC,
         false},

        {{Slot::kInvestC, Slot::kInvestA, Slot::kFireLaneD},
         {Slot::kInvestB, Slot::kExpansionLaneB},
         Slot::kInvestD,
         true},
    };
    aConfig.mExpectedSkeletonCount = 6;
    
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD };

    std::vector<Slot> aResiduals;
    aResiduals = {
        Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD
    };

    std::vector<Slot> aOutputs;
    aOutputs = {Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD };
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_D was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

GSeedRunStageConfig MakeSeed_EConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_E",
                                             TwistDomain::kPhaseE,
                                             pUseNonces,
                                             GAXSFormat::kN11);
    aConfig.mSlices = {
        {{Slot::kInvestA, Slot::kInvestB, Slot::kFireLaneA},
         {Slot::kInvestC, Slot::kInvestD, Slot::kFireLaneB},
         Slot::kFireLaneA,
         false},

        {{Slot::kFireLaneA, Slot::kInvestC, Slot::kInvestD, Slot::kWorkLaneA},
         {Slot::kInvestA, Slot::kInvestB, Slot::kWorkLaneB},
         Slot::kFireLaneB,
         true},

        {{Slot::kFireLaneB, Slot::kInvestA, Slot::kWorkLaneC},
         {Slot::kFireLaneA, Slot::kInvestC},
         Slot::kOperationLaneA,
         false},

        {{Slot::kOperationLaneA, Slot::kFireLaneA, Slot::kWorkLaneD},
         {Slot::kFireLaneB, Slot::kInvestD},
         Slot::kOperationLaneB,
         true},

        {{Slot::kOperationLaneB, Slot::kFireLaneB, Slot::kFireLaneC},
         {Slot::kOperationLaneA, Slot::kFireLaneA, Slot::kInvestA},
         Slot::kOperationLaneC,
         false},

        {{Slot::kOperationLaneC, Slot::kOperationLaneA, Slot::kFireLaneD},
         {Slot::kOperationLaneB, Slot::kInvestB},
         Slot::kOperationLaneD,
         true},
    };
    aConfig.mExpectedSkeletonCount = 6;
    
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD };

    std::vector<Slot> aResiduals;
    aResiduals = { Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD,
                    Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD };

    std::vector<Slot> aOutputs;
    aOutputs = {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD };
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_E was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig MakeSeed_FConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_F",
                                             TwistDomain::kPhaseF,
                                             pUseNonces,
                                             GAXSFormat::kN9);
    aConfig.mSlices = SixPassDiverseSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                           {Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD,
                                            Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD},
                                           {Slot::kSnowLaneC, Slot::kSnowLaneD,
                                            Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD };

    std::vector<Slot> aResiduals;
    aResiduals = {
        Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD,
        Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD,
    };

    std::vector<Slot> aOutputs;
    aOutputs = {Slot::kSnowLaneC, Slot::kSnowLaneD, Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD };
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_F was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig MakeSeed_GConfig(const bool pUseNonces) {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunSeed_G",
                                             TwistDomain::kPhaseH,
                                             pUseNonces,
                                             GAXSFormat::kN7);
    aConfig.mSlices = SixPassDiverseSlices({Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kSnowLaneC, Slot::kSnowLaneD},
                                           {Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD,
                                            Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                           {Slot::kWorkLaneA, Slot::kWorkLaneB,
                                            Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    
    
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kSnowLaneC, Slot::kSnowLaneD };
        
    std::vector<Slot> aResiduals;
    aResiduals = {
        Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD,
        Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD
    };

    std::vector<Slot> aOutputs;
    aOutputs = { Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD };
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("GSeedRunSeed_G was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

} // namespace

GSeedRunSeed_A::GSeedRunSeed_A(const bool pUseNonces,
                               const bool pEmitNoncePrologue)
: mStage(MakeSeed_AConfig(pUseNonces)),
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
: mStage(MakeSeed_BConfig(pUseNonces)),
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
: mStage(MakeSeed_CConfig(pUseNonces)),
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
: mStage(MakeSeed_DConfig(pUseNonces)),
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
: mStage(MakeSeed_EConfig(pUseNonces)),
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
: mStage(MakeSeed_FConfig(pUseNonces)),
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
: mStage(MakeSeed_GConfig(pUseNonces)),
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
