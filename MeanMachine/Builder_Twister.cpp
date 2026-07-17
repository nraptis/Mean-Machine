//
//  Builder_Twister.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Twister.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunTwist.hpp"
#include "GDomainSchedule.hpp"
#include "GRunMatrixDiffusion.hpp"

#include "GSquash.hpp"

#include <vector>

namespace {

const char *PhaseConstantsMemberName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB: return "mPhaseBConstants";
        case TwistDomain::kPhaseC: return "mPhaseCConstants";
        case TwistDomain::kPhaseD: return "mPhaseDConstants";
        case TwistDomain::kPhaseE: return "mPhaseEConstants";
        case TwistDomain::kPhaseF: return "mPhaseFConstants";
        case TwistDomain::kPhaseG: return "mPhaseGConstants";
        case TwistDomain::kPhaseH: return "mPhaseHConstants";
        case TwistDomain::kPhaseA:
        default:
            return "mPhaseAConstants";
    }
}

void AddTwistMatrixDomainWordLines(TwistProgramBranch &pBranch,
                                   const TwistDomain pDomain) {
    const std::string aConstants =
        std::string("pWorkSpace->mDomainBundle.") +
        PhaseConstantsMemberName(pDomain);

    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectA = " + aConstants + ".mMatrixSelectA;");
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectB = " + aConstants + ".mMatrixSelectB;");
    pBranch.AddLine("");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollA = " + aConstants + ".mMatrixUnrollA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollB = " + aConstants + ".mMatrixUnrollB;");
    pBranch.AddLine("");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgA = " + aConstants + ".mMatrixArgA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgB = " + aConstants + ".mMatrixArgB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgC = " + aConstants + ".mMatrixArgC;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgD = " + aConstants + ".mMatrixArgD;");
}

} // namespace

bool Builder_Twister::Build(GTwistExpander *pExpander,
                            std::string *pErrorMessage) {
    
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build received null expander";
        }
        return false;
    }

    std::vector<GSeedRunStageConfig> aStageConfigs = {
        GTwistRunTwistConfig::MakeTwist_AConfig(),
        GTwistRunTwistConfig::MakeTwist_BConfig(),
        GTwistRunTwistConfig::MakeTwist_CConfig(),
        GTwistRunTwistConfig::MakeTwist_DConfig(),
        GTwistRunTwistConfig::MakeTwist_EConfig(),
        GTwistRunTwistConfig::MakeTwist_FConfig(),
        GTwistRunTwistConfig::MakeTwist_GConfig(),
    };

    std::vector<TwistDomain> aExtraDomains;
    if (!GDomainSchedule::AssignShuffledRoundRobin(&aStageConfigs,
                                                   1U,
                                                   &aExtraDomains)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister failed to assign its domain schedule";
        }
        return false;
    }
    const TwistDomain aMatrixDomain = aExtraDomains[0];

    pExpander->mTwistStageConfigs = aStageConfigs;
    pExpander->mTwistMatrixDomain = aMatrixDomain;
    
    pExpander->mTwister.AddLine("// [seed]");
    
    
    std::vector<GSymbol> aWorkLanes;
    aWorkLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneA));
    aWorkLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneB));
    aWorkLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneC));
    aWorkLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneD));

    std::vector<GSymbol> aFuseLanes;
    aFuseLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneA));
    aFuseLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneB));
    aFuseLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneC));
    aFuseLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneD));

    std::vector<GSymbol> aFireLanes;
    aFireLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFireLaneA));
    aFireLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFireLaneB));
    aFireLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFireLaneC));
    aFireLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFireLaneD));

    std::vector<GSymbol> aOperationLanes;
    aOperationLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneA));
    aOperationLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneB));
    aOperationLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneC));
    aOperationLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneD));
    
    std::vector<GStatement> aStatementsSeed6;
    GTwistRunTwist_A aRunnerTwistA(aStageConfigs[0]);
    
    if (!aRunnerTwistA.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GTwistRunTwist_A.Plan for ") + "twist-a" + "\n" + *pErrorMessage;
        }
        return false;
    }
    
    if (!aRunnerTwistA.Build(pExpander->mTwister, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build failed to bake GTwistRunTwist_A:\n" + *pErrorMessage;
        }
        return false;
    }
    for (const GStatement &aStatement : aStatementsSeed6) {
        if (!aStatement.IsRawLine()) {
            continue;
        }
        pExpander->mTwister.AddLine(aStatement.mRawLine);
    }
    
    std::vector<GStatement> aStatementsHate16;
    GTwistRunTwist_B aRunnerTwistB(aStageConfigs[1]);
    
    if (!aRunnerTwistB.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GTwistRunTwist_B.Plan for ") + "twist-b" + "\n" + *pErrorMessage;
        }
        return false;
    }
    
    if (!aRunnerTwistB.Build(pExpander->mTwister, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build failed to bake GTwistRunTwist_B:\n" + *pErrorMessage;
        }
        return false;
    }
    for (const GStatement &aStatement : aStatementsHate16) {
        if (!aStatement.IsRawLine()) {
            continue;
        }
        pExpander->mTwister.AddLine(aStatement.mRawLine);
    }
    
    std::vector<GStatement> aStatementsSeed8;
    GTwistRunTwist_C aRunnerTwistC(aStageConfigs[2]);
    
    if (!aRunnerTwistC.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GTwistRunTwist_C.Plan for ") + "twist-c" + "\n" + *pErrorMessage;
        }
        return false;
    }
    
    if (!aRunnerTwistC.Build(pExpander->mTwister, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build failed to bake GTwistRunTwist_C:\n" + *pErrorMessage;
        }
        return false;
    }
    for (const GStatement &aStatement : aStatementsSeed8) {
        if (!aStatement.IsRawLine()) {
            continue;
        }
        pExpander->mTwister.AddLine(aStatement.mRawLine);
    }

    std::vector<GStatement> aStatementsTwistD;
    GTwistRunTwist_D aRunnerTwistD(aStageConfigs[3]);
    
    if (!aRunnerTwistD.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GTwistRunTwist_D.Plan for ") + "twist-d" + "\n" + *pErrorMessage;
        }
        return false;
    }
    
    if (!aRunnerTwistD.Build(pExpander->mTwister, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build failed to bake GTwistRunTwist_D:\n" + *pErrorMessage;
        }
        return false;
    }
    for (const GStatement &aStatement : aStatementsTwistD) {
        if (!aStatement.IsRawLine()) {
            continue;
        }
        pExpander->mTwister.AddLine(aStatement.mRawLine);
    }

    
    
    std::vector<GStatement> aStatementsTwistE;
    GTwistRunTwist_E aRunnerTwistE(aStageConfigs[4]);
    
    if (!aRunnerTwistE.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GTwistRunTwist_E.Plan for ") + "twist-e" + "\n" + *pErrorMessage;
        }
        return false;
    }
    
    if (!aRunnerTwistE.Build(pExpander->mTwister, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build failed to bake GTwistRunTwist_E:\n" + *pErrorMessage;
        }
        return false;
    }
    for (const GStatement &aStatement : aStatementsTwistE) {
        if (!aStatement.IsRawLine()) {
            continue;
        }
        pExpander->mTwister.AddLine(aStatement.mRawLine);
    }

    AddTwistMatrixDomainWordLines(pExpander->mTwister,
                                  aMatrixDomain);

    for (int i=0;i<4;i+=2) {
        GRunMatrixDiffusionConfig aDiffusion;
        aDiffusion.mInputA = aFuseLanes[i];
        aDiffusion.mInputB = aFuseLanes[i + 1];
        aDiffusion.mOutputA = aFireLanes[i];
        aDiffusion.mOutputB = aFireLanes[i + 1];

        aDiffusion.mShuffleEntropyA = aOperationLanes[(i + 2) % 4];
        aDiffusion.mShuffleEntropyB = aOperationLanes[(i + 3) % 4];
        aDiffusion.mOperationSourceA = aOperationLanes[(i + 0) % 4];
        aDiffusion.mOperationSourceB = aOperationLanes[(i + 1) % 4];
        aDiffusion.mUseDomainWords = true;

        GBatch aBatchDiffusion;
        aBatchDiffusion.mExportsAsBlock = false;

        if (!GRunMatrixDiffusion::Bake(aDiffusion, &aBatchDiffusion, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("error on matrix diffusion for twist: ") + *pErrorMessage;
            }
            return false;
        }
        pExpander->mTwister.AddBatch(aBatchDiffusion);
    }

    GTwistRunTwist_F aRunnerTwistF(aStageConfigs[5]);

    if (!aRunnerTwistF.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GTwistRunTwist_F.Plan for ") + "twist-f" + "\n" + *pErrorMessage;
        }
        return false;
    }

    if (!aRunnerTwistF.Build(pExpander->mTwister, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build failed to bake GTwistRunTwist_F:\n" + *pErrorMessage;
        }
        return false;
    }
    
    GTwistRunTwist_G aRunnerTwistG(aStageConfigs[6]);

    if (!aRunnerTwistG.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GTwistRunTwist_G.Plan for ") + "twist-g" + "\n" + *pErrorMessage;
        }
        return false;
    }

    if (!aRunnerTwistG.Build(pExpander->mTwister, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build failed to bake GTwistRunTwist_G:\n" + *pErrorMessage;
        }
        return false;
    }
    pExpander->mTwister.AddLine("//");
    std::vector<GStatement> aStatementsSquash;
    GSymbol aIndex = GSymbol::Var(TwistVariable::kIndex);
    GSquash aSquash;
    if (!aSquash.Bake(GSymbol::Var(TwistVariable::kParamOutput),
                      aWorkLanes[0],
                      aWorkLanes[1],
                      aWorkLanes[2],
                      aWorkLanes[3],
                      
                      aIndex,
                      
                      &aStatementsSquash,
                      pErrorMessage)) {
        return false;
    }
    
    GBatch aFinishBatch;
    aFinishBatch.mExportsAsBlock = false;
    aFinishBatch.CommitStatements(&aStatementsSquash);
    pExpander->mTwister.AddBatch(aFinishBatch);
    return true;
    
}
