//
//  Builder_Twister.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Twister.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunTwist.hpp"
#include "GRunMatrixDiffusion.hpp"

#include "GSquash.hpp"

bool Builder_Twister::Build(GTwistExpander *pExpander,
                            std::string *pErrorMessage) {
    
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build received null expander";
        }
        return false;
    }
    
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
    GTwistRunTwist_A aRunnerTwistA;
    
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
    GTwistRunTwist_B aRunnerTwistB;
    
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
    GTwistRunTwist_C aRunnerTwistC;
    
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
    GTwistRunTwist_D aRunnerTwistD;
    
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

    for (int i=0;i<4;i+=2) {
        
        GRunMatrixDiffusionConfig aDiffusion;
        aDiffusion.mInputA = aFuseLanes[i];
        aDiffusion.mInputB = aFuseLanes[i + 1];
        aDiffusion.mOutputA = aFireLanes[i];
        aDiffusion.mOutputB =  aFireLanes[i + 1];
        
        aDiffusion.mShuffleEntropyA = aOperationLanes[(i + 2) % 4];
        aDiffusion.mShuffleEntropyB = aOperationLanes[(i + 3) % 4];
        aDiffusion.mOperationSourceA = aOperationLanes[(i + 0) % 4];
        aDiffusion.mOperationSourceB = aOperationLanes[(i + 1) % 4];
        aDiffusion.mUseDomainWords = false;
        
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
    
    std::vector<GStatement> aStatementsTwistE;
    GTwistRunTwist_E aRunnerTwistE;
    
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
