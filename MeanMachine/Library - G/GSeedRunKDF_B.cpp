//
//  GSeedRunKDF_B.cpp
//  MeanMachine
//

#include "GSeedRunKDF_B.hpp"
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

GSeedRunStageConfig BuildKDF_B_AConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    const GPassFactory::SlotArray8 aResiduals = {
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kSource,
    };
    const GPassFactory::SlotArray4 aOutputs = {
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
    };

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_B_A",
                                             "kdf_b_loop_a",
                                             GAXSFormat::kN9);
    aConfig.mSlices = GPassFactory::FourPassEightResidualSlices(aInputs,
                                                                aResiduals,
                                                                aOutputs);
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aOutputs),
                                                        &aErrorMessage)) {
        printf("MakeKDF_B_AConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildKDF_B_BConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
    };
    const GPassFactory::SlotArray8 aResiduals = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        Slot::kSource, Slot::kWindLaneA,
        Slot::kWindLaneB, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray4 aOutputs = {
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_B_B",
                                             "kdf_b_loop_b",
                                             GAXSFormat::kN7);
    
    aConfig.mSlices = GPassFactory::FourPassEightResidualSlices(aInputs,
                                                                aResiduals,
                                                                aOutputs);
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aOutputs),
                                                        &aErrorMessage)) {
        printf("MakeKDF_B_BConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildKDF_B_CConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };
    const GPassFactory::SlotArray8 aResiduals = {
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
        Slot::kEarthLaneD, Slot::kFireLaneD,
        Slot::kWaterLaneD, Slot::kSource,
    };
    const GPassFactory::SlotArray4 aOutputs = {
        Slot::kFuseLaneA, Slot::kFuseLaneB,
        Slot::kFuseLaneC, Slot::kFuseLaneD,
    };

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_B_C",
                                             "kdf_b_loop_c",
                                             GAXSFormat::kN11);
    
    aConfig.mSlices = GPassFactory::FourPassTerminalEightResidualSlices(aInputs,
                                                                        aResiduals,
                                                                        aOutputs);
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateTerminalMidstage(aConfig,
                                                                GPassFactory::ToVector(aInputs),
                                                                GPassFactory::ToVector(aResiduals),
                                                                GPassFactory::ToVector(aOutputs),
                                                                &aErrorMessage)) {
        printf("MakeKDF_B_CConfig was not valid with ValidateTerminalMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

// Here we diffuse [fuse] to [worker]

GSeedRunStageConfig BuildKDF_B_DConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aInputs = {
        Slot::kWorkLaneA, Slot::kWorkLaneB,
        Slot::kWorkLaneC, Slot::kWorkLaneD,
    };
    const GPassFactory::SlotArray8 aResiduals = {
        Slot::kWaterLaneA, Slot::kWaterLaneB,
        Slot::kWaterLaneC, Slot::kWaterLaneD,
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kWindLaneC,
    };
    const GPassFactory::SlotArray4 aOutputs = {
        Slot::kExpansionLaneA, Slot::kExpansionLaneB,
        Slot::kExpansionLaneC, Slot::kExpansionLaneD,
    };

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_B_D",
                                             "kdf_b_loop_d",
                                             GAXSFormat::kN9);
    
    aConfig.mSlices = GPassFactory::FourPassEightResidualSlices(aInputs,
                                                                aResiduals,
                                                                aOutputs);
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        GPassFactory::ToVector(aInputs),
                                                        GPassFactory::ToVector(aResiduals),
                                                        GPassFactory::ToVector(aOutputs),
                                                        &aErrorMessage)) {
        printf("MakeKDF_B_DConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

// Here we squash [expand]

} // namespace

namespace GSeedRunKDF_BConfig {

GSeedRunStageConfig MakeKDF_B_AConfig() {
    return BuildKDF_B_AConfig();
}

GSeedRunStageConfig MakeKDF_B_BConfig() {
    return BuildKDF_B_BConfig();
}

GSeedRunStageConfig MakeKDF_B_CConfig() {
    return BuildKDF_B_CConfig();
}

GSeedRunStageConfig MakeKDF_B_DConfig() {
    return BuildKDF_B_DConfig();
}

}

GSeedRunKDF_B_A::GSeedRunKDF_B_A()
: mStage(GSeedRunKDF_BConfig::MakeKDF_B_AConfig()) {
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
: mStage(GSeedRunKDF_BConfig::MakeKDF_B_BConfig()) {
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
: mStage(GSeedRunKDF_BConfig::MakeKDF_B_CConfig()) {
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
: mStage(GSeedRunKDF_BConfig::MakeKDF_B_DConfig()) {
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
