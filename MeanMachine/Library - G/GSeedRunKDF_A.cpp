//
//  GSeedRunKDF_A.cpp
//  MeanMachine
//

#include "GSeedRunKDF_A.hpp"
#include "GPassFactory.hpp"
#include "GQuick.hpp"
#include "GSeedRunStageConfigValidator.hpp"
#include "Random.hpp"

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

void AddKDF_APrologue(TwistProgramBranch &pBranch) {
    pBranch.AddLine("// [kdf-a]");
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

GSeedRunStageConfig BuildKDF_A_AConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray2 aPrimarySources = {
        Slot::kSource, Slot::kParamSnow,
    };
    const GPassFactory::SlotArray2 aWarmUpLanes = {
        Slot::kScrapLaneA, Slot::kScrapLaneB,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kEarthLaneA, Slot::kEarthLaneB, Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactory::SlotArray6 aExpectedDestinations = GPassFactory::Concat(aWarmUpLanes,
                                                                                aDestinations);

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_A_A",
                                             "kdf_a_loop_a",
                                             GAXSFormat::kN11);
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mSlices = GPassFactory::KDF_A_AStarterSlices(aPrimarySources,
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
        printf("MakeKDF_A_AConfig was not valid with ValidateStarter");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

GSeedRunStageConfig BuildKDF_A_BConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kEarthLaneA, Slot::kEarthLaneB, Slot::kEarthLaneC, Slot::kEarthLaneD,
    };
    const GPassFactory::SlotArray4 aResidualSources = {
        Slot::kSource, Slot::kParamSnow,
        Slot::kScrapLaneA, Slot::kScrapLaneB,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
    };
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_A_B",
                                             "kdf_a_loop_b",
                                             GAXSFormat::kN9);
    
    
    aConfig.mSlices = GPassFactory::FourPassFourResidualSlices(aPrimarySources,
                                                               aResidualSources,
                                                               aDestinations);
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    
    {
        const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
        const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
        const std::vector<Slot> aOutputs = GPassFactory::ToVector(aDestinations);
        
        std::string aErrorMessage;
        if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                            aInputs,
                                                            aResiduals,
                                                            aOutputs,
                                                            &aErrorMessage)) {
            printf("MakeKDF_A_BConfig was not valid with ValidateMidstage");
            printf("%s\n", aErrorMessage.c_str());
            exit(0);
        }
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildKDF_A_CConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
    };
    const GPassFactory::SlotArray8 aResidualSources = {
        Slot::kSource, Slot::kParamSnow,
        Slot::kEarthLaneA, Slot::kEarthLaneB, Slot::kEarthLaneC, Slot::kEarthLaneD,
        Slot::kScrapLaneA, Slot::kScrapLaneB,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD,
    };

    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_A_C",
                                             "kdf_a_loop_c",
                                             GAXSFormat::kN7);
    
    aConfig.mSlices = GPassFactory::FourPassEightResidualSlices(aPrimarySources,
                                                               aResidualSources,
                                                               aDestinations);
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    const std::vector<Slot> aOutputs = GPassFactory::ToVector(aDestinations);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("MakeKDF_A_CConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

GSeedRunStageConfig BuildKDF_A_DConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD,
    };
    const GPassFactory::SlotArray12 aResidualSources = {
        Slot::kSource, Slot::kParamSnow,
        Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kEarthLaneA, Slot::kEarthLaneB, Slot::kEarthLaneC, Slot::kEarthLaneD,
        Slot::kScrapLaneA, Slot::kScrapLaneB,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kFuseLaneA, Slot::kFuseLaneB, Slot::kFuseLaneC, Slot::kFuseLaneD,
    };
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_A_D",
                                             "kdf_a_loop_d",
                                             GAXSFormat::kN9);
    
    aConfig.mSlices = GPassFactory::FourPassTwelveResidualSlices(aPrimarySources,
                                                                 aResidualSources,
                                                                 aDestinations);
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    const std::vector<Slot> aOutputs = GPassFactory::ToVector(aDestinations);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("MakeKDF_A_DConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    
    return aConfig;
}

// Here we diffuse [fuse] to [wind]

GSeedRunStageConfig BuildKDF_A_EConfig() {
    using Slot = TwistWorkSpaceSlot;
    const GPassFactory::SlotArray4 aPrimarySources = {
        Slot::kWindLaneA, Slot::kWindLaneB, Slot::kWindLaneC, Slot::kWindLaneD,
    };
    const GPassFactory::SlotArray14 aResidualSources = {
        Slot::kSource, Slot::kParamSnow,
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kOperationLaneA, Slot::kOperationLaneB,
        Slot::kOperationLaneC, Slot::kOperationLaneD,
    };
    const GPassFactory::SlotArray4 aDestinations = {
        Slot::kWaterLaneA, Slot::kWaterLaneB, Slot::kWaterLaneC, Slot::kWaterLaneD,
    };
    
    GSeedRunStageConfig aConfig = BaseConfig("GSeedRunKDF_A_E",
                                             "kdf_a_loop_e",
                                             GAXSFormat::kN11);
    
    aConfig.mSlices = GPassFactory::FourPassFourteenResidualSlices(aPrimarySources,
                                                                 aResidualSources,
                                                                 aDestinations);
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    
    const std::vector<Slot> aInputs = GPassFactory::ToVector(aPrimarySources);
    const std::vector<Slot> aResiduals = GPassFactory::ToVector(aResidualSources);
    const std::vector<Slot> aOutputs = GPassFactory::ToVector(aDestinations);
    
    std::string aErrorMessage;
    if (!GSeedRunStageConfigValidator::ValidateMidstage(aConfig,
                                                        aInputs,
                                                        aResiduals,
                                                        aOutputs,
                                                        &aErrorMessage)) {
        printf("MakeKDF_A_EConfig was not valid with ValidateMidstage");
        printf("%s\n", aErrorMessage.c_str());
        exit(0);
    }
    
    return aConfig;
}

// available residuals
// kScrapLaneA[3] kScrapLaneB[3]
// kEarthLaneA[3] kEarthLaneB[3]
// kEarthLaneC[3] kEarthLaneD[3]
// kFireLaneA[2] kFireLaneB[2]
// kFireLaneC[2] kFireLaneD[2]
// kOperationLaneA[1] kOperationLaneB[1]
// kOperationLaneC[1] kOperationLaneD[1]
// kWindLaneA[0] kWindLaneB[0]
// kWindLaneC[0] kWindLaneD[0]

} // namespace

namespace GSeedRunKDF_AConfig {

GSeedRunStageConfig MakeKDF_A_AConfig() {
    return BuildKDF_A_AConfig();
}

GSeedRunStageConfig MakeKDF_A_BConfig() {
    return BuildKDF_A_BConfig();
}

GSeedRunStageConfig MakeKDF_A_CConfig() {
    return BuildKDF_A_CConfig();
}

GSeedRunStageConfig MakeKDF_A_DConfig() {
    return BuildKDF_A_DConfig();
}

GSeedRunStageConfig MakeKDF_A_EConfig() {
    return BuildKDF_A_EConfig();
}

}

GSeedRunKDF_A_A::GSeedRunKDF_A_A()
: mStage(GSeedRunKDF_AConfig::MakeKDF_A_AConfig()) {
}

GSeedRunKDF_A_A::~GSeedRunKDF_A_A() {
}

bool GSeedRunKDF_A_A::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_A_A::Build(TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    AddKDF_APrologue(pBranch);
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunKDF_A_B::GSeedRunKDF_A_B()
: mStage(GSeedRunKDF_AConfig::MakeKDF_A_BConfig()) {
}

GSeedRunKDF_A_B::~GSeedRunKDF_A_B() {
}

bool GSeedRunKDF_A_B::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_A_B::Build(TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunKDF_A_C::GSeedRunKDF_A_C()
: mStage(GSeedRunKDF_AConfig::MakeKDF_A_CConfig()) {
}

GSeedRunKDF_A_C::~GSeedRunKDF_A_C() {
}

bool GSeedRunKDF_A_C::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_A_C::Build(TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunKDF_A_D::GSeedRunKDF_A_D()
: mStage(GSeedRunKDF_AConfig::MakeKDF_A_DConfig()) {
}

GSeedRunKDF_A_D::~GSeedRunKDF_A_D() {
}

bool GSeedRunKDF_A_D::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_A_D::Build(TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}

GSeedRunKDF_A_E::GSeedRunKDF_A_E()
: mStage(GSeedRunKDF_AConfig::MakeKDF_A_EConfig()) {
}

GSeedRunKDF_A_E::~GSeedRunKDF_A_E() {
}

bool GSeedRunKDF_A_E::Plan(std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKDF_A_E::Build(TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}
