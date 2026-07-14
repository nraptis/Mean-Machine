//
//  GTwistRunGrowKeyA.cpp
//  MeanMachine
//

#include "GTwistRunGrowKeyA.hpp"
#include "GPassFactory.hpp"
#include "GSeedRunStageConfigValidator.hpp"

namespace {

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
                               const TwistDomain pDomain) {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pLoopName;
    aConfig.mStartLine = "// " + pStageName + " " + pLoopName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + pLoopName + " (end)";
    
    aConfig.mIgnoreNonces = true;
    aConfig.mHasDomainMix = false;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = pDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = PhaseSalts(pDomain, Slot::kPhaseASaltOrbiterAssignA, 6);
    aConfig.mSaltsOrbiterUpdate = PhaseSalts(pDomain, Slot::kPhaseASaltOrbiterUpdateA, 6);
    aConfig.mSaltsWandererUpdate = PhaseSalts(pDomain, Slot::kPhaseASaltWandererUpdateA, 6);
    aConfig.mEmitGroupLaneFlowComments = false;
    return aConfig;
}

GSeedRunStageConfig BuildGrowAConfig() {
    
    //TODO:
    // This doesn't work. The generated code uses operation lanes, which are not listed here.
    
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kWorkLaneA, Slot::kWorkLaneB,
        Slot::kWorkLaneC, Slot::kWorkLaneD,
    };
    const GPassFactory::SlotArray12 aResiduals = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        Slot::kInvestA, Slot::kInvestB,
        Slot::kInvestC, Slot::kInvestD,
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kOperationLaneA, Slot::kOperationLaneB,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);

    GSeedRunStageConfig aConfig = BaseConfig("GROW_A",
                                             "grow_key_a",
                                             TwistDomain::kPhaseG);
    aConfig.mSlices = GPassFactory::SixPassTwelveResidualSlices(aInputs,
                                                                aResiduals,
                                                                aExpectedDestinations);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mFormat = GAXSFormat::kN7;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aExpectedDestinations),
                                                        &aErrorMessage)) {
        printf("MakeGrowAConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildGrowBConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
    };
    const GPassFactory::SlotArray12 aResiduals = {
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
        Slot::kInvestE, Slot::kInvestF,
        Slot::kInvestG, Slot::kInvestH,
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kWorkLaneA, Slot::kWorkLaneB,
        Slot::kWorkLaneC, Slot::kWorkLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);

    GSeedRunStageConfig aConfig = BaseConfig("GROW_B",
                                             "grow_key_b",
                                             TwistDomain::kPhaseH);
    aConfig.mFormat = GAXSFormat::kN9;
    
    aConfig.mSlices = GPassFactory::SixPassTwelveResidualSlices(aInputs,
                                                                aResiduals,
                                                                aExpectedDestinations);
    aConfig.mWarmupDestinationCount = 2;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aExpectedDestinations),
                                                        &aErrorMessage)) {
        printf("MakeGrowBConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

} // namespace

namespace GTwistRunGrowKeyConfig {

GSeedRunStageConfig MakeGrowAConfig() {
    return BuildGrowAConfig();
}

GSeedRunStageConfig MakeGrowBConfig() {
    return BuildGrowBConfig();
}

}

GTwistRunGrowKeyA::GTwistRunGrowKeyA()
: mStage(GTwistRunGrowKeyConfig::MakeGrowAConfig()) {
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

GTwistRunGrowKeyB::GTwistRunGrowKeyB()
: mStage(GTwistRunGrowKeyConfig::MakeGrowBConfig()) {
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
