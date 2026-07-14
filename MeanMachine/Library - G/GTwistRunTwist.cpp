//
//  GTwistRunTwist.cpp
//  MeanMachine
//

#include "GTwistRunTwist.hpp"
#include "GPassFactory.hpp"
#include "GQuick.hpp"
#include "Random.hpp"
#include "GSeedRunStageConfigValidator.hpp"
#include <array>

namespace {

const std::array<TwistVariable, 13> kInitialRandomVariables = {
    TwistVariable::kPrevious,
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
                               const std::string &pLoopName,
                               const TwistDomain pDomain,
                               const GAXSFormat pFormat) {
    using Slot = TwistWorkSpaceSlot;
    
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pLoopName;
    aConfig.mStartLine = "// " + pStageName + " " + pLoopName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + pLoopName + " (end)";
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = true;
    aConfig.mHasDomainMix = false;
    aConfig.mDomain = pDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(pDomain, Slot::kPhaseASaltOrbiterAssignA, 6);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(pDomain, Slot::kPhaseASaltOrbiterUpdateA, 6);
    aConfig.mSaltsWandererUpdate = PhaseSalts(pDomain, Slot::kPhaseASaltWandererUpdateA, 6);
    return aConfig;
}

GSeedRunStageConfig BuildTwist_AConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray3 aPrimarySources = {
        Slot::kSource, Slot::kKeyRowReadA, Slot::kKeyRowReadB,
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kScrapLaneA, Slot::kScrapLaneB,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_A",
                                             "twist_loop_a",
                                             TwistDomain::kPhaseA,
                                             GAXSFormat::kN9);
    aConfig.mMaxContextSourceCount = 4;
    aConfig.mMaxBoundSourceCount = 8;
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mBindDuplicateSourceSlots = false;
    aConfig.mSliceDomains = {
        TwistDomain::kPhaseA, TwistDomain::kPhaseA,
        TwistDomain::kPhaseA, TwistDomain::kPhaseA,
        TwistDomain::kPhaseA, TwistDomain::kPhaseA,
    };
    aConfig.mSlices = GPassFactory::Seed_AStarterSlices(aPrimarySources,
                                                        aWarmUpLanes,
                                                        aDestinations);
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateStarter(aConfig,
                                                       aInputs, // primary inputs
                                                       GPassFactory::ToVector(aExpectedDestinations),
                                                       false,
                                                       &aErrorMessage)) {
        printf("MakeTwist_AConfig was not valid with ValidateStarter");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildTwist_BConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray2 aResiduals = {
        Slot::kScrapLaneA, Slot::kScrapLaneB,
    };
    const GPassFactory::SlotArray6 aDestinations = {
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
    };
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_B",
                                             "twist_loop_b",
                                             TwistDomain::kPhaseB,
                                             GAXSFormat::kN7);
    aConfig.mSliceDomains = {
        TwistDomain::kPhaseB, TwistDomain::kPhaseB,
        TwistDomain::kPhaseB, TwistDomain::kPhaseB,
        TwistDomain::kPhaseB, TwistDomain::kPhaseB,
    };
    aConfig.mSlices = GPassFactory::SixPassTwoResidualSlices(aInputs,
                                                             aResiduals,
                                                             aDestinations);
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("MakeTwist_BConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildTwist_CConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
    };
    const GPassFactory::SlotArray6 aResiduals = {
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray6 aDestinations = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_C",
                                             "twist_loop_c",
                                             TwistDomain::kPhaseC,
                                             GAXSFormat::kN7);
    aConfig.mSliceDomains = {
        TwistDomain::kPhaseC, TwistDomain::kPhaseC,
        TwistDomain::kPhaseC, TwistDomain::kPhaseC,
        TwistDomain::kPhaseC, TwistDomain::kPhaseC,
    };
    aConfig.mSlices = GPassFactory::SixPassSixResidualSlices(aInputs,
                                                             aResiduals,
                                                             aDestinations);
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("MakeTwist_CConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildTwist_DConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactory::SlotArray12 aResiduals = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
    };
    const GPassFactory::SlotArray8 aOutputs = {
        Slot::kInvestA, Slot::kInvestB,
        Slot::kInvestC, Slot::kInvestD,
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_D",
                                             "twist_loop_d",
                                             TwistDomain::kPhaseD,
                                             GAXSFormat::kN11);
    aConfig.mSliceDomains = {
        TwistDomain::kPhaseD, TwistDomain::kPhaseD,
        TwistDomain::kPhaseD, TwistDomain::kPhaseD,
        TwistDomain::kPhaseE, TwistDomain::kPhaseE,
        TwistDomain::kPhaseE, TwistDomain::kPhaseE,
    };
    aConfig.mSlices = GPassFactory::EightPassTwelveResidualSlices(aInputs,
                                                                 aResiduals,
                                                                 aOutputs);
    aConfig.mExpectedSkeletonCount = 8;
    aConfig.mHotPackCount = 8;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aOutputs),
                                                        &aErrorMessage)) {
        printf("MakeTwist_DConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildTwist_EConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactory::SlotArray12 aResiduals = {
        Slot::kInvestA, Slot::kInvestB,
        Slot::kInvestC, Slot::kInvestD,
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactory::SlotArray8 aDestinations = {
        Slot::kInvestE, Slot::kInvestF,
        Slot::kInvestG, Slot::kInvestH,
        Slot::kWorkLaneA, Slot::kWorkLaneB,
        Slot::kWorkLaneC, Slot::kWorkLaneD,
    };
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_E",
                                             "twist_loop_e",
                                             TwistDomain::kPhaseE,
                                             GAXSFormat::kN9);
    aConfig.mSliceDomains = {
        TwistDomain::kPhaseE, TwistDomain::kPhaseE,
        TwistDomain::kPhaseF, TwistDomain::kPhaseF,
        TwistDomain::kPhaseF, TwistDomain::kPhaseF,
        TwistDomain::kPhaseF, TwistDomain::kPhaseF,
    };
    aConfig.mSlices = GPassFactory::EightPassTwelveResidualSlices(aInputs,
                                                                  aResiduals,
                                                                  aDestinations);
    aConfig.mExpectedSkeletonCount = 8;
    aConfig.mHotPackCount = 8;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aDestinations),
                                                        &aErrorMessage)) {
        printf("MakeTwist_EConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
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
                                                                      GExpr::Const(Random::Get64High())));
    }
    aInitBatch.CommitStatements(&aInitStatements);
    pBranch.AddBatch(aInitBatch);
}

} // namespace

namespace GTwistRunTwistConfig {

GSeedRunStageConfig MakeTwist_AConfig() {
    return BuildTwist_AConfig();
}

GSeedRunStageConfig MakeTwist_BConfig() {
    return BuildTwist_BConfig();
}

GSeedRunStageConfig MakeTwist_CConfig() {
    return BuildTwist_CConfig();
}

GSeedRunStageConfig MakeTwist_DConfig() {
    return BuildTwist_DConfig();
}

GSeedRunStageConfig MakeTwist_EConfig() {
    return BuildTwist_EConfig();
}

}


GTwistRunTwist_A::GTwistRunTwist_A()
: mStage(GTwistRunTwistConfig::MakeTwist_AConfig()) {
}

GTwistRunTwist_A::~GTwistRunTwist_A() {
}

void GTwistRunTwist_A::Reset() {
    mStage.Reset();
}

bool GTwistRunTwist_A::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunTwist_A::Build(TwistProgramBranch &pBranch,
                             std::string *pErrorMessage) {
    AddTwistPrologue(pBranch);
    return mStage.Build(pBranch, pErrorMessage);
}

GTwistRunTwist_B::GTwistRunTwist_B()
: mStage(GTwistRunTwistConfig::MakeTwist_BConfig()) {
}

GTwistRunTwist_B::~GTwistRunTwist_B() {
}

void GTwistRunTwist_B::Reset() {
    mStage.Reset();
}

bool GTwistRunTwist_B::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunTwist_B::Build(TwistProgramBranch &pBranch,
                             std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}

GTwistRunTwist_C::GTwistRunTwist_C()
: mStage(GTwistRunTwistConfig::MakeTwist_CConfig()) {
}

GTwistRunTwist_C::~GTwistRunTwist_C() {
}

void GTwistRunTwist_C::Reset() {
    mStage.Reset();
}

bool GTwistRunTwist_C::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunTwist_C::Build(TwistProgramBranch &pBranch,
                             std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}

GTwistRunTwist_D::GTwistRunTwist_D()
: mStage(GTwistRunTwistConfig::MakeTwist_DConfig()) {
}

GTwistRunTwist_D::~GTwistRunTwist_D() {
}

void GTwistRunTwist_D::Reset() {
    mStage.Reset();
}

bool GTwistRunTwist_D::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunTwist_D::Build(TwistProgramBranch &pBranch,
                             std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}

GTwistRunTwist_E::GTwistRunTwist_E()
: mStage(GTwistRunTwistConfig::MakeTwist_EConfig()) {
}

GTwistRunTwist_E::~GTwistRunTwist_E() {
}

void GTwistRunTwist_E::Reset() {
    mStage.Reset();
}

bool GTwistRunTwist_E::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunTwist_E::Build(TwistProgramBranch &pBranch,
                             std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}
