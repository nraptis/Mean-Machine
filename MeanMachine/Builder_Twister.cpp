//
//  Builder_Twister.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Twister.hpp"
#include "GTwistExpander.hpp"
#include "GKeyFoldA.hpp"
#include "GTwistRunTwist.hpp"

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
    
    
    
    
    pExpander->mGrowKeyA.AddLine("// [grow key a]");
    GKeyFoldA aKeyFold;
    if (!aKeyFold.BakeGrowKeyA(pExpander->mGrowKeyA, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build failed to bake GKeyFoldA grow key A:\n" + *pErrorMessage;
        }
        return false;
    }
    
    pExpander->mGrowKeyB.AddLine("// [grow key b]");
    if (!aKeyFold.BakeGrowKeyB(pExpander->mGrowKeyB, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build failed to bake GKeyFoldA grow key B:\n" + *pErrorMessage;
        }
        return false;
    }
    
    return true;
    
}
