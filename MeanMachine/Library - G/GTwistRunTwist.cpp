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

std::vector<GSeedRunStageSliceSpec> FourPassDiverseSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                          const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                          const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    return {
        {{pPrimary[0], pPrimary[1], pResiduals[0]},
         {pPrimary[2], pPrimary[3], pResiduals[1]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], pPrimary[3], pResiduals[2]},
         {pPrimary[0], pPrimary[1], pResiduals[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[0], pPrimary[1], pResiduals[4]},
         {pDestinations[0], pPrimary[2], pResiduals[5]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], pPrimary[3], pResiduals[6]},
         {pDestinations[1], pPrimary[1], pResiduals[7]},
         pDestinations[3],
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
            Slot::kFireLaneA,
            false},
        
        // cover source forward, key rows backward.
        {{Slot::kFireLaneA, Slot::kKeyRowReadA},
            {Slot::kKeyRowReadB, Slot::kSource},
            Slot::kFireLaneB,
            true},
        
        // cover key_b forward, key_a/source backward.
        {{Slot::kFireLaneB, Slot::kKeyRowReadB},
            {Slot::kKeyRowReadA, Slot::kSource, Slot::kFireLaneA},
            Slot::kFireLaneC,
            false},
        
        // cover key_b/source forward, key_a backward.
        {{Slot::kFireLaneC, Slot::kKeyRowReadB, Slot::kSource, Slot::kFireLaneA},
            {Slot::kKeyRowReadA, Slot::kFireLaneB},
            Slot::kFireLaneD,
            true},
        
        // special five-wide ingress: cover key_a/key_b/source forward.
        {{Slot::kFireLaneD, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kFireLaneB},
            {Slot::kFireLaneA, Slot::kFireLaneC},
            Slot::kWorkLaneA,
            false},
        
        // special five-wide cross: cover key_a/key_b/source backward.
        {{Slot::kWorkLaneA, Slot::kFireLaneC},
            {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kFireLaneB, Slot::kFireLaneA},
            Slot::kWorkLaneB,
            true},
        
        // cover key_a/source forward, key_b/snow_d backward.
        {{Slot::kWorkLaneB, Slot::kKeyRowReadA, Slot::kSource, Slot::kFireLaneA},
            {Slot::kKeyRowReadB, Slot::kFireLaneD, Slot::kWorkLaneA},
            Slot::kWorkLaneC,
            false},
        
        // cover source forward, key_a/key_b backward.
        {{Slot::kWorkLaneC, Slot::kSource, Slot::kWorkLaneA, Slot::kFireLaneA},
            {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kWorkLaneB, Slot::kFireLaneB},
            Slot::kWorkLaneD,
            true},
        
        // cover key_a/key_b forward, source/snow history backward.
        {{Slot::kWorkLaneD, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kWorkLaneC},
            {Slot::kSource, Slot::kWorkLaneA, Slot::kFireLaneC, Slot::kFireLaneD},
            Slot::kExpansionLaneA,
            false},
        
        // cover key_a forward, key_b/source backward.
        {{Slot::kExpansionLaneA, Slot::kKeyRowReadA, Slot::kWorkLaneD, Slot::kWorkLaneB},
            {Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneC, Slot::kFireLaneD},
            Slot::kExpansionLaneB,
            true},
        
        // cover key_b forward, key_a/source/work backward.
        {{Slot::kExpansionLaneB, Slot::kWorkLaneD, Slot::kKeyRowReadB, Slot::kWorkLaneC},
            {Slot::kKeyRowReadA, Slot::kSource, Slot::kExpansionLaneA, Slot::kWorkLaneB},
            Slot::kExpansionLaneC,
            false},
        
        // final write, keep previous dest flowing forward.
        {{Slot::kExpansionLaneC, Slot::kKeyRowReadA},
            {Slot::kWorkLaneD, Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kKeyRowReadB},
            Slot::kExpansionLaneD,
            true},
    };
    aConfig.mExpectedSkeletonCount = 12;
    
    std::vector<Slot> aInputs;
    aInputs = {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource};

    std::vector<Slot> aOutputs;
    aOutputs = {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD,
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
    aConfig.mSlices = FourPassDiverseSlices({Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                            {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                             Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
                                            {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    
    std::vector<Slot> aInputs;
    aInputs = {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD};

    std::vector<Slot> aResiduals;
    aResiduals = {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD};

    std::vector<Slot> aOutputs;
    aOutputs = {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD};
    
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
    aConfig.mSlices = FourPassDiverseSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                            {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                             Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                            {Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    
    std::vector<Slot> aInputs;
    aInputs = {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD};

    std::vector<Slot> aResiduals;
    aResiduals = {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD};

    std::vector<Slot> aOutputs;
    aOutputs = {Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD};
    
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
