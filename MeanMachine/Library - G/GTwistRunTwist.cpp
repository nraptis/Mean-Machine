//
//  GTwistRunTwist.cpp
//  MeanMachine
//

#include "GTwistRunTwist.hpp"
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

GSeedRunStageConfig MakeTwist_AConfig() {
    using Slot = TwistWorkSpaceSlot;
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_A",
                                             "twist_loop_a",
                                             TwistDomain::kPhaseD,
                                             GAXSFormat::kN9);
    aConfig.mMaxContextSourceCount = 5;
    aConfig.mMaxBoundSourceCount = 10;
    aConfig.mWarmupDestinationCount = 4;
    aConfig.mBindDuplicateSourceSlots = true;
    aConfig.mSliceDomains = {
        TwistDomain::kPhaseA, TwistDomain::kPhaseA, TwistDomain::kPhaseA,
        TwistDomain::kPhaseB, TwistDomain::kPhaseB, TwistDomain::kPhaseB,
        TwistDomain::kPhaseC, TwistDomain::kPhaseC, TwistDomain::kPhaseC,
        TwistDomain::kPhaseD, TwistDomain::kPhaseD, TwistDomain::kPhaseD,
    };
    aConfig.mSlices = {
        // source graph: 3 available sources, ingress [a, b], cross [a, c].
        {{Slot::kKeyRowReadA, Slot::kKeyRowReadB},
            {Slot::kKeyRowReadA, Slot::kSource},
            Slot::kWorkLaneA,
            false},
        
        // cover source forward, key rows backward.
        {{Slot::kWorkLaneA, Slot::kKeyRowReadA},
            {Slot::kKeyRowReadB, Slot::kSource},
            Slot::kWorkLaneB,
            true},
        
        // cover key_b forward, key_a/source backward.
        {{Slot::kWorkLaneB, Slot::kKeyRowReadB},
            {Slot::kKeyRowReadA, Slot::kSource, Slot::kWorkLaneA},
            Slot::kInvestA,
            false},
        
        // cover key_b/source forward, key_a backward.
        {{Slot::kInvestA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneA},
            {Slot::kKeyRowReadA, Slot::kWorkLaneB},
            Slot::kInvestB,
            true},
        
        // special five-wide ingress: cover key_a/key_b/source forward.
        {{Slot::kInvestB, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneB},
            {Slot::kWorkLaneA, Slot::kInvestA},
            Slot::kFireLaneA,
            false},
        
        // special five-wide cross: cover key_a/key_b/source backward.
        {{Slot::kFireLaneA, Slot::kInvestA},
            {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneB, Slot::kWorkLaneA},
            Slot::kFireLaneB,
            true},
        
        // cover key_a/source forward, key_b/snow_d backward.
        {{Slot::kFireLaneB, Slot::kKeyRowReadA, Slot::kSource, Slot::kWorkLaneA},
            {Slot::kKeyRowReadB, Slot::kInvestB, Slot::kFireLaneA},
            Slot::kFireLaneC,
            false},
        
        // cover source forward, key_a/key_b backward.
        {{Slot::kFireLaneC, Slot::kSource, Slot::kFireLaneA, Slot::kWorkLaneA},
            {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kFireLaneB, Slot::kWorkLaneB},
            Slot::kFireLaneD,
            true},
        
        // cover key_a/key_b forward, source/snow history backward.
        {{Slot::kFireLaneD, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kFireLaneC},
            {Slot::kSource, Slot::kFireLaneA, Slot::kInvestA, Slot::kInvestB},
            Slot::kExpansionLaneA,
            false},
        
        // cover key_a forward, key_b/source backward.
        {{Slot::kExpansionLaneA, Slot::kKeyRowReadA, Slot::kFireLaneD, Slot::kFireLaneB},
            {Slot::kKeyRowReadB, Slot::kSource, Slot::kFireLaneC, Slot::kInvestB},
            Slot::kExpansionLaneB,
            true},
        
        // cover key_b forward, key_a/source/work backward.
        {{Slot::kExpansionLaneB, Slot::kFireLaneD, Slot::kKeyRowReadB, Slot::kFireLaneC},
            {Slot::kKeyRowReadA, Slot::kSource, Slot::kExpansionLaneA, Slot::kFireLaneB},
            Slot::kExpansionLaneC,
            false},
        
        // final write, keep previous dest flowing forward.
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
        Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kInvestA, Slot::kInvestB,
        Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD};
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateStarter(aConfig,
                                                       aInputs, // primary inputs
                                                       aOutputs,
                                                       true,
                                                       &aErrorMessage)) {
        printf("MakeTwist_AConfig was not valid with ValidateStarter");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig MakeTwist_BConfig() {
    using Slot = TwistWorkSpaceSlot;
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_B",
                                             "twist_loop_b",
                                             TwistDomain::kPhaseE,
                                             GAXSFormat::kN7);
    aConfig.mSlices = SixPassRecentResidualSlices({Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                                  {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                                  {Slot::kInvestC, Slot::kInvestD,
                                                   Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD };

    std::vector<Slot> aResiduals;
    aResiduals = { Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD };

    std::vector<Slot> aOutputs;
    aOutputs = { Slot::kInvestC, Slot::kInvestD, Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD};
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("MakeTwist_BConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig MakeTwist_CConfig() {
    using Slot = TwistWorkSpaceSlot;
    
    GSeedRunStageConfig aConfig = BaseConfig("GTwistRunTwist_C",
                                             "twist_loop_c",
                                             TwistDomain::kPhaseF,
                                             GAXSFormat::kN11);
    aConfig.mSlices = SixPassDiverseSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                           {Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD,
                                            Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                           {Slot::kSnowLaneA, Slot::kSnowLaneB,
                                            Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    
    std::vector<Slot> aInputs;
    aInputs = {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD};

    std::vector<Slot> aResiduals;
    aResiduals = {Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD,
        Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD};

    std::vector<Slot> aOutputs;
    aOutputs = { Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD};
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("MakeTwist_CConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

void AddTwistPrologue(TwistProgramBranch &pBranch) {
    GBatch aInitBatch;
    aInitBatch.mName = "init varz";
    
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


GTwistRunTwist_A::GTwistRunTwist_A()
: mStage(MakeTwist_AConfig()) {
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
: mStage(MakeTwist_BConfig()) {
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
: mStage(MakeTwist_CConfig()) {
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
