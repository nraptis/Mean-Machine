//
//  GTwistRunGrowKeyA.cpp
//  MeanMachine
//

#include "GTwistRunGrowKeyA.hpp"

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
    aConfig.mFormat = GAXSFormat::kN5;
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

GSeedRunStageConfig MakeGrowAConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = BaseConfig("GROW_A",
                                             "grow_key_a",
                                             TwistDomain::kPhaseG);
    aConfig.mSlices = {
        {{Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC},
         {Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
         Slot::kExpansionLaneA,
         false},

        {{Slot::kExpansionLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC},
         {Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
         Slot::kExpansionLaneB,
         true},

        {{Slot::kExpansionLaneB, Slot::kExpansionLaneA, Slot::kWorkLaneD},
         {Slot::kExpansionLaneA, Slot::kWorkLaneD, Slot::kWorkLaneC},
         Slot::kExpansionLaneC,
         false},

        {{Slot::kExpansionLaneC, Slot::kExpansionLaneB, Slot::kExpansionLaneA},
         {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC},
         Slot::kExpansionLaneD,
         true},
    };
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

GSeedRunStageConfig MakeGrowBConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = BaseConfig("GROW_B",
                                             "grow_key_b",
                                             TwistDomain::kPhaseH);
    aConfig.mSlices = {
        {{Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC},
         {Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
         Slot::kWorkLaneA,
         false},

        {{Slot::kWorkLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC},
         {Slot::kExpansionLaneC, Slot::kExpansionLaneD, Slot::kWorkLaneA},
         Slot::kWorkLaneB,
         true},

        {{Slot::kWorkLaneB, Slot::kWorkLaneA, Slot::kExpansionLaneD},
         {Slot::kWorkLaneA, Slot::kExpansionLaneD, Slot::kExpansionLaneC},
         Slot::kWorkLaneC,
         false},

        {{Slot::kWorkLaneC, Slot::kWorkLaneB, Slot::kWorkLaneA},
         {Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC},
         Slot::kWorkLaneD,
         true},
    };
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

} // namespace

GTwistRunGrowKeyA::GTwistRunGrowKeyA()
: mStage(MakeGrowAConfig()) {
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
: mStage(MakeGrowBConfig()) {
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
