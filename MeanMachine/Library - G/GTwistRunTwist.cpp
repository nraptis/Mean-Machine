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
#include <utility>

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

    const GPassFactory::SlotArray5 aResiduals = {
        Slot::kSource, Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        Slot::kScrapLaneA, Slot::kScrapLaneB,
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kWorkLaneA, Slot::kWorkLaneB,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_B",
                                             "twist_loop_b",
                                             TwistDomain::kPhaseB,
                                             GAXSFormat::kN7);
    aConfig.mSlices = GPassFactory::SixPassFiveResidualSlices(aInputs,
                                                              aResiduals,
                                                              aExpectedDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aExpectedDestinations),
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

    const GPassFactory::SlotArray9 aResiduals = {
        Slot::kSource,
        
        Slot::kScrapLaneA, Slot::kScrapLaneB,
        Slot::kWorkLaneA, Slot::kWorkLaneB,
        
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kInvestA, Slot::kInvestB,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_C",
                                             "twist_loop_c",
                                             TwistDomain::kPhaseC,
                                             GAXSFormat::kN7);
    aConfig.mSlices = GPassFactory::SixPassNineResidualSlices(aInputs,
                                                              aResiduals,
                                                              aExpectedDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aExpectedDestinations),
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
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };

    const GPassFactory::SlotArray11 aResiduals = {
        Slot::kKeyRowReadA,
        
        Slot::kInvestA, Slot::kInvestB,
        
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
        
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
        
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kScrapLaneC, Slot::kScrapLaneD,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_D",
                                             "twist_loop_d",
                                             TwistDomain::kPhaseD,
                                             GAXSFormat::kN11);
    aConfig.mSlices = GPassFactory::SixPassElevenResidualSlices(aInputs,
                                                                aResiduals,
                                                                aExpectedDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aExpectedDestinations),
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
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };

    const GPassFactory::SlotArray12 aResiduals = {
        Slot::kKeyRowReadB,
        
        Slot::kScrapLaneC, Slot::kScrapLaneD,
        
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
        
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kSnowLaneC, Slot::kSnowLaneD,
        
        Slot::kInvestA,
    };
    
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kInvestC, Slot::kInvestD,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_E",
                                             "twist_loop_e",
                                             TwistDomain::kPhaseE,
                                             GAXSFormat::kN9);
    aConfig.mSlices = GPassFactory::SixPassTwelveResidualSlices(aInputs,
                                                             aResiduals,
                                                             aExpectedDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aExpectedDestinations),
                                                        &aErrorMessage)) {
        printf("MakeTwist_EConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

// Here we diffuse [fuse] to [fire]

GSeedRunStageConfig BuildTwist_FConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };

    const GPassFactory::SlotArray18 aResiduals = {
        Slot::kSource,
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        Slot::kInvestC, Slot::kInvestD,
        Slot::kInvestB,
        Slot::kSnowLaneA, Slot::kSnowLaneB,
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
        Slot::kScrapLaneC, Slot::kScrapLaneD,
        Slot::kScrapLaneA, Slot::kScrapLaneB,
    };
    
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kInvestE, Slot::kInvestF,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);

    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_F",
                                             "twist_loop_f",
                                             TwistDomain::kPhaseF,
                                             GAXSFormat::kN9);
    aConfig.mSlices = GPassFactory::SixPassEighteenResidualSlices(aInputs,
                                                                aResiduals,
                                                                aExpectedDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;

    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aExpectedDestinations),
                                                        &aErrorMessage)) {
        printf("MakeTwist_FConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }

    return aConfig;
}

GSeedRunStageConfig BuildTwist_GConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactory::SlotArray18 aResiduals = {
        Slot::kKeyRowReadA, Slot::kKeyRowReadB,
        
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
        
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        
        Slot::kSnowLaneC, Slot::kSnowLaneD,
        
        Slot::kInvestA, Slot::kInvestB,
        Slot::kInvestC, Slot::kInvestD,
        Slot::kInvestE, Slot::kInvestF,
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kInvestG, Slot::kInvestH,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kWorkLaneA, Slot::kWorkLaneB,
        Slot::kWorkLaneC, Slot::kWorkLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);

    // Twist domains wrap after F; phases G and H are reserved for Grow.
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_G",
                                             "twist_loop_g",
                                             TwistDomain::kPhaseA,
                                             GAXSFormat::kN9);
    aConfig.mSlices = GPassFactory::SixPassEighteenResidualSlices(aInputs,
                                                                aResiduals,
                                                                aExpectedDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;

    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aExpectedDestinations),
                                                        &aErrorMessage)) {
        printf("MakeTwist_GConfig was not valid with ValidateMidstage");
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

GSeedRunStageConfig MakeTwist_FConfig() {
    return BuildTwist_FConfig();
}

GSeedRunStageConfig MakeTwist_GConfig() {
    return BuildTwist_GConfig();
}

}


GTwistRunTwist_A::GTwistRunTwist_A()
: GTwistRunTwist_A(GTwistRunTwistConfig::MakeTwist_AConfig()) {
}

GTwistRunTwist_A::GTwistRunTwist_A(GSeedRunStageConfig pConfig)
: mStage(std::move(pConfig)) {
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
: GTwistRunTwist_B(GTwistRunTwistConfig::MakeTwist_BConfig()) {
}

GTwistRunTwist_B::GTwistRunTwist_B(GSeedRunStageConfig pConfig)
: mStage(std::move(pConfig)) {
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
: GTwistRunTwist_C(GTwistRunTwistConfig::MakeTwist_CConfig()) {
}

GTwistRunTwist_C::GTwistRunTwist_C(GSeedRunStageConfig pConfig)
: mStage(std::move(pConfig)) {
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
: GTwistRunTwist_D(GTwistRunTwistConfig::MakeTwist_DConfig()) {
}

GTwistRunTwist_D::GTwistRunTwist_D(GSeedRunStageConfig pConfig)
: mStage(std::move(pConfig)) {
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
: GTwistRunTwist_E(GTwistRunTwistConfig::MakeTwist_EConfig()) {
}

GTwistRunTwist_E::GTwistRunTwist_E(GSeedRunStageConfig pConfig)
: mStage(std::move(pConfig)) {
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

GTwistRunTwist_F::GTwistRunTwist_F()
: GTwistRunTwist_F(GTwistRunTwistConfig::MakeTwist_FConfig()) {
}

GTwistRunTwist_F::GTwistRunTwist_F(GSeedRunStageConfig pConfig)
: mStage(std::move(pConfig)) {
}

GTwistRunTwist_F::~GTwistRunTwist_F() {
}

void GTwistRunTwist_F::Reset() {
    mStage.Reset();
}

bool GTwistRunTwist_F::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunTwist_F::Build(TwistProgramBranch &pBranch,
                             std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}

GTwistRunTwist_G::GTwistRunTwist_G()
: GTwistRunTwist_G(GTwistRunTwistConfig::MakeTwist_GConfig()) {
}

GTwistRunTwist_G::GTwistRunTwist_G(GSeedRunStageConfig pConfig)
: mStage(std::move(pConfig)) {
}

GTwistRunTwist_G::~GTwistRunTwist_G() {
}

void GTwistRunTwist_G::Reset() {
    mStage.Reset();
}

bool GTwistRunTwist_G::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GTwistRunTwist_G::Build(TwistProgramBranch &pBranch,
                             std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}
