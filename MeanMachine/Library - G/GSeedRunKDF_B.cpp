//
//  GSeedRunKDF_B.cpp
//  MeanMachine
//

#include "GSeedRunKDF_B.hpp"
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

std::vector<TwistWorkSpaceSlot> ParamOrbiterAssignSalts() {
    using Slot = TwistWorkSpaceSlot;
    return {
        Slot::kParamDomainSaltOrbiterAssignA,
        Slot::kParamDomainSaltOrbiterAssignB,
        Slot::kParamDomainSaltOrbiterAssignC,
        Slot::kParamDomainSaltOrbiterAssignD,
        Slot::kParamDomainSaltOrbiterAssignE,
        Slot::kParamDomainSaltOrbiterAssignF,
    };
}

std::vector<TwistWorkSpaceSlot> ParamOrbiterUpdateSalts() {
    using Slot = TwistWorkSpaceSlot;
    return {
        Slot::kParamDomainSaltOrbiterUpdateA,
        Slot::kParamDomainSaltOrbiterUpdateB,
        Slot::kParamDomainSaltOrbiterUpdateC,
        Slot::kParamDomainSaltOrbiterUpdateD,
        Slot::kParamDomainSaltOrbiterUpdateE,
        Slot::kParamDomainSaltOrbiterUpdateF,
    };
}

std::vector<TwistWorkSpaceSlot> ParamWandererUpdateSalts() {
    using Slot = TwistWorkSpaceSlot;
    return {
        Slot::kParamDomainSaltWandererUpdateA,
        Slot::kParamDomainSaltWandererUpdateB,
        Slot::kParamDomainSaltWandererUpdateC,
        Slot::kParamDomainSaltWandererUpdateD,
        Slot::kParamDomainSaltWandererUpdateE,
        Slot::kParamDomainSaltWandererUpdateF,
    };
}

GSeedRunStageConfig BaseConfig(const std::string &pStageName,
                               const std::string &pBatchName,
                               GAXSFormat pFormat) {
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pBatchName;
    aConfig.mStartLine = "// " + pStageName + " " + pBatchName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + pBatchName + " (end)";
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    return aConfig;
}

std::vector<GSeedRunStageSliceSpec> FourPassEightResidualSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                                const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                                const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    std::vector<TwistWorkSpaceSlot> aResiduals = pResiduals;
    Random::Shuffle(&aResiduals);

    return {
        {{pPrimary[0], pPrimary[1], aResiduals[0]},
         {pPrimary[2], pPrimary[3], aResiduals[1]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], aResiduals[2]},
         {pPrimary[0], pPrimary[3], aResiduals[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[3], aResiduals[4]},
         {pDestinations[0], pPrimary[1], aResiduals[5]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], aResiduals[6]},
         {pDestinations[1], pPrimary[2], aResiduals[7]},
         pDestinations[3],
         true},
    };
}

void AddKDF_BPrologue(TwistProgramBranch &pBranch) {
    pBranch.AddLine("// [kdf-b]");
    pBranch.AddLine("std::uint64_t aDomainWordIngress = pConstants->mIngress;");
    pBranch.AddLine("std::uint64_t aDomainWordScatter = pConstants->mScatter;");
    pBranch.AddLine("std::uint64_t aDomainWordCross = pConstants->mCross;");
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;");
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;");
    
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

GSeedRunStageConfig MakeKDF_B_AConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_B_A",
                                             "kdf_b_loop_a",
                                             GAXSFormat::kN7);
    aConfig.mSlices = FourPassEightResidualSlices({Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
                                                  {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD,
                                                   Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                                  {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD };

    std::vector<Slot> aResiduals;
    aResiduals = { Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD,
        Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD};

    std::vector<Slot> aOutputs;
    aOutputs = { Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD };
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("MakeKDF_B_AConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

GSeedRunStageConfig MakeKDF_B_BConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_B_B",
                                             "kdf_b_loop_b",
                                             GAXSFormat::kN11);
    
    //aConfig.mIgnoreNonces = true;
    //aConfig.mHasDomainMix = false;
    
    aConfig.mSlices = FourPassEightResidualSlices({Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                                  {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                                   Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
                                                  {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD };

    std::vector<Slot> aResiduals;
    aResiduals = { Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                   Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD };

    std::vector<Slot> aOutputs;
    aOutputs = { Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD };
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("MakeKDF_B_BConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

GSeedRunStageConfig MakeKDF_B_CConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_B_C",
                                             "kdf_b_loop_c",
                                             GAXSFormat::kN9);
    //aConfig.mIgnoreNonces = true;
    //aConfig.mHasDomainMix = false;
    
    aConfig.mSlices = FourPassEightResidualSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                                  {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                                   Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
                                                  {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD };

    std::vector<Slot> aResiduals;
    aResiduals = { Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                   Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD };

    std::vector<Slot> aOutputs;
    aOutputs = { Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD };
    
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("MakeKDF_B_CConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

GSeedRunStageConfig MakeKDF_B_DConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_B_D",
                                             "kdf_b_loop_d",
                                             GAXSFormat::kN7);
    //aConfig.mIgnoreNonces = true;
    //aConfig.mHasDomainMix = false;
    
    aConfig.mSlices = FourPassEightResidualSlices({Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
                                                  {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                                   Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                                  {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    
    
    std::vector<Slot> aInputs;
    aInputs = { Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD };

    std::vector<Slot> aResiduals;
    aResiduals = { Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                   Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD };

    std::vector<Slot> aOutputs;
    aOutputs = { Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD };
    
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("MakeKDF_B_DConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

} // namespace

GSeedRunKDF_B_A::GSeedRunKDF_B_A()
: mStage(MakeKDF_B_AConfig()) {
}

GSeedRunKDF_B_A::~GSeedRunKDF_B_A() {
}

void GSeedRunKDF_B_A::Reset() {
    mStage.Reset();
}

bool GSeedRunKDF_B_A::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_B_A::Build(TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    AddKDF_BPrologue(pBranch);
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunKDF_B_B::GSeedRunKDF_B_B()
: mStage(MakeKDF_B_BConfig()) {
}

GSeedRunKDF_B_B::~GSeedRunKDF_B_B() {
}

void GSeedRunKDF_B_B::Reset() {
    mStage.Reset();
}

bool GSeedRunKDF_B_B::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_B_B::Build(TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunKDF_B_C::GSeedRunKDF_B_C()
: mStage(MakeKDF_B_CConfig()) {
}

GSeedRunKDF_B_C::~GSeedRunKDF_B_C() {
}

void GSeedRunKDF_B_C::Reset() {
    mStage.Reset();
}

bool GSeedRunKDF_B_C::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_B_C::Build(TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunKDF_B_D::GSeedRunKDF_B_D()
: mStage(MakeKDF_B_DConfig()) {
}

GSeedRunKDF_B_D::~GSeedRunKDF_B_D() {
}

void GSeedRunKDF_B_D::Reset() {
    mStage.Reset();
}

bool GSeedRunKDF_B_D::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_B_D::Build(TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}
