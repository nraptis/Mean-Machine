//
//  GSeedRunKDF.cpp
//  MeanMachine
//
//  Created by Codex on 5/10/26.
//

#include "GSeedRunKDF.hpp"
#include "GARXPlan.hpp"
#include <cstdio>

GSeedRunKDF::GSeedRunKDF() {
    Reset();
}

GSeedRunKDF::~GSeedRunKDF() {
}

void GSeedRunKDF::Reset() {
    mLoopIndex = VarSymbol("aIndex");
    mSource = BufSymbol(TwistWorkSpaceSlot::kSource);
    
    
    mStreamCurrent = VarSymbol("aPublicIngress");
    mStreamPrevious = VarSymbol("aPublicPrevious");
    mStreamScatter = VarSymbol("aPublicScatter");
    
    
    mSecretCurrent = VarSymbol("aPrivateIngress");
    mSecretPrevious = VarSymbol("aPrivatePrevious");
    mSecretScatter = VarSymbol("aPrivateScatter");
    mSecretWrite = VarSymbol("aPrivateWrite");
    
    mStreamCross = VarSymbol("aCrossIngress");
    mCarry = VarSymbol("aCarry");

    mWandererA = VarSymbol("aWandererA");
    mWandererB = VarSymbol("aWandererB");
    mWandererC = VarSymbol("aWandererC");
    mWandererD = VarSymbol("aWandererD");
    mWandererE = VarSymbol("aWandererE");
    mWandererF = VarSymbol("aWandererF");

    mOrbiterA = VarSymbol("aOrbitA");
    mOrbiterB = VarSymbol("aOrbitB");
    mOrbiterC = VarSymbol("aOrbitC");
    mOrbiterD = VarSymbol("aOrbitD");
    mOrbiterE = VarSymbol("aOrbitE");
    mOrbiterF = VarSymbol("aOrbitF");

    mPlugKeyA = VarSymbol("aPlugKeyA");
    mPlugKeyB = VarSymbol("aPlugKeyB");

    mDomainSaltA = BufSymbol(TwistWorkSpaceSlot::kDomainSaltSourceA);
    mDomainSaltB = BufSymbol(TwistWorkSpaceSlot::kDomainSaltSourceB);
    mDomainSaltC = BufSymbol(TwistWorkSpaceSlot::kDomainSaltSourceC);
    mDomainSaltD = BufSymbol(TwistWorkSpaceSlot::kDomainSaltSourceD);
    mDomainSaltE = BufSymbol(TwistWorkSpaceSlot::kDomainSaltSourceE);
    mDomainSaltF = BufSymbol(TwistWorkSpaceSlot::kDomainSaltSourceF);
    
    mPublicIngressDomainWord = VarSymbol("aPublicIngressDomainWord");
    mPrivateIngressDomainWord = VarSymbol("aPrivateIngressDomainWord");
    mCrossIngressDomainWord = VarSymbol("aCrossIngressDomainWord");
    
    

    mListSBoxes.clear();
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxA));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxB));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxC));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxD));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxE));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxF));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxG));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxH));

    mListWorldSalts.clear();
    mListWorldSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltA));
    mListWorldSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltB));
    mListWorldSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltC));
    mListWorldSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltD));
    mListWorldSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltE));
    mListWorldSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltF));
    mListWorldSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltG));
    mListWorldSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltH));

    mListWorkers.clear();
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneA));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneB));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneC));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneD));
    
    mListOpLanes.clear();
    mListOpLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneA));
    mListOpLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneB));
    
    const std::vector<GHotPack> aHotPacks = GMagicNumbers::GetHotPacks(1);
    if (!aHotPacks.empty()) {
        mHotPack = aHotPacks[0];
    } else {
        mHotPack = GHotPack();
    }
}

bool GSeedRunKDF::Plan(std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    Reset();
    return true;
}

bool GSeedRunKDF::Build(TwistProgramBranch &pBranch,
                        std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    GARXPlan aPlan;
    if (!GARXPlan::Bake(&aPlan)) {
        if (pErrorMessage != nullptr && pErrorMessage->empty()) {
            *pErrorMessage = "failed to bake GARX plan for KDF pass";
        }
        return false;
    }
    if (aPlan.mPassPlans.empty() || (aPlan.mPassPlans[0] == nullptr)) {
        if (pErrorMessage != nullptr && pErrorMessage->empty()) {
            *pErrorMessage = "GARX plan had no pass plan";
        }
        return false;
    }

    GBatch aBatch;
    
    std::vector<GSymbol> aInputBuffers = {
        mSource,
        mListOpLanes[0],
        mListWorkers[0],
        mListWorkers[1]
    };
    
    std::vector<GSymbol> aCrossBuffers = {
        mSource,
        mListOpLanes[0],
        mListWorkers[0],
        mListWorkers[1]
    };
    
    std::vector<GSymbol> aDestBuffers = {
        mListWorkers[0],
        mListWorkers[1],
        mListWorkers[2],
        mListWorkers[3]
    };
    
    auto MakeReadExpr = [&](const GSymbol pBuffer,
                            const bool pInverted,
                            const std::uint32_t pOffset) -> GExpr {
        return GQuick::MakeReadBufferOffsetExpressionDirected(pBuffer,
                                                              mLoopIndex,
                                                              pInverted,
                                                              pOffset);
    };
    
    for (std::size_t aPassIndex = 0; aPassIndex < 4U; aPassIndex++) {
        
        if (aPassIndex >= aPlan.mPassPlans.size() ||
            aPlan.mPassPlans[aPassIndex] == nullptr) {
            
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GARX plan missing pass plan";
            }
            return false;
        }
        
        GLoop aLoop;
        GStatement aStatement;
        std::vector<GStatement> aStatements;
        std::vector<GStatement> aDomainStatements;
        
        const GSymbol aInputBuffer = aInputBuffers[aPassIndex];
        const GSymbol aCrossBuffer = aCrossBuffers[aPassIndex];
        
        const GExpr aPublicIngressDomainWordRead = GQuick::MakeReadBufferReadExpression(
            mDomainSaltA,
            GExpr::Const32(static_cast<int>(aPassIndex))
        );
        const GExpr aPrivateIngressDomainWordRead = GQuick::MakeReadBufferReadExpression(
            mDomainSaltB,
            GExpr::Const32(static_cast<int>((aPassIndex * 3U) % static_cast<std::size_t>(S_SALT)))
        );
        const GExpr aCrossIngressDomainWordRead = GQuick::MakeReadBufferReadExpression(
            mDomainSaltC,
            GExpr::Const32(static_cast<int>((aPassIndex * 5U) % static_cast<std::size_t>(S_SALT)))
        );
        
        aDomainStatements.push_back(
            GQuick::MakeAssignVariableStatement(mPublicIngressDomainWord,
                                                aPublicIngressDomainWordRead)
        );
        aDomainStatements.push_back(
            GQuick::MakeAssignVariableStatement(mPrivateIngressDomainWord,
                                                aPrivateIngressDomainWordRead)
        );
        aDomainStatements.push_back(
            GQuick::MakeAssignVariableStatement(mCrossIngressDomainWord,
                                                aCrossIngressDomainWordRead)
        );
        aBatch.CommitStatements(&aDomainStatements);
        
        const GExpr aPublicIngressSourceA = MakeReadExpr(aInputBuffer, false, 0U);
        const GExpr aPublicIngressSourceB = MakeReadExpr(aInputBuffer, false, 1U);
        const GExpr aPublicIngressSourceC = MakeReadExpr(aInputBuffer, false, 17U);
        const GExpr aPublicIngressSourceD = MakeReadExpr(aInputBuffer, true, 0U);
        
        const GExpr aPrivateIngressSourceA = MakeReadExpr(aInputBuffer, false, 3U);
        const GExpr aPrivateIngressSourceB = MakeReadExpr(aInputBuffer, false, 29U);
        const GExpr aPrivateIngressSourceC = MakeReadExpr(aInputBuffer, true, 7U);
        const GExpr aPrivateIngressSourceD = MakeReadExpr(aInputBuffer, true, 23U);
        
        const GExpr aCrossIngressSourceA = MakeReadExpr(aCrossBuffer, true, 0U);
        const GExpr aCrossIngressSourceB = MakeReadExpr(aCrossBuffer, true, 1U);
        const GExpr aCrossIngressSourceC = MakeReadExpr(aCrossBuffer, false, 11U);
        const GExpr aCrossIngressSourceD = MakeReadExpr(aCrossBuffer, true, 31U);
        
        aLoop.mLoopVariable = mLoopIndex;
        aLoop.mLoopVariableName = mLoopIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 1;
        
        //
        // previous lanes
        //
        aStatement = GQuick::MakeAssignVariableStatement(mStreamPrevious,
                                                         mStreamCurrent);
        aLoop.AddBody(&aStatement);
        
        aStatement = GQuick::MakeAssignVariableStatement(mSecretPrevious,
                                                         mSecretCurrent);
        aLoop.AddBody(&aStatement);
        
        if (!CSPKDF::Bake(aPlan.mPassPlans[aPassIndex],
                          aDestBuffers[aPassIndex],
                          false,
                          mLoopIndex,
                          
                          aPublicIngressSourceA,
                          aPublicIngressSourceB,
                          aPublicIngressSourceC,
                          aPublicIngressSourceD,
                          aPrivateIngressSourceA,
                          aPrivateIngressSourceB,
                          aPrivateIngressSourceC,
                          aPrivateIngressSourceD,
                          aCrossIngressSourceA,
                          aCrossIngressSourceB,
                          aCrossIngressSourceC,
                          aCrossIngressSourceD,
                          GExpr::Symbol(mPublicIngressDomainWord),
                          GExpr::Symbol(mPrivateIngressDomainWord),
                          GExpr::Symbol(mCrossIngressDomainWord),
                          
                          mStreamCurrent,
                          mStreamPrevious,
                          mStreamScatter,
                          mStreamCross,
                          
                          //
                          // stream scatter components
                          //
                          mStreamCurrent,
                          mStreamPrevious,
                          mStreamCross,
                          mStreamCurrent,
                          
                          mSecretCurrent,
                          mSecretPrevious,
                          mSecretScatter,
                          mSecretWrite,
                          
                          //
                          // secret scatter components
                          //
                          mSecretCurrent,
                          mSecretPrevious,
                          mStreamCross,
                          mCarry,
                          
                          mCarry,
                          mWandererA,
                          mWandererB,
                          mWandererC,
                          mWandererD,
                          mWandererE,
                          mWandererF,
                          
                          mOrbiterA,
                          mOrbiterB,
                          mOrbiterC,
                          mOrbiterD,
                          mOrbiterE,
                          mOrbiterF,
                          
                          mDomainSaltA,
                          mDomainSaltB,
                          mDomainSaltC,
                          mDomainSaltD,
                          mDomainSaltE,
                          mDomainSaltF,
                          
                          mListWorldSalts[0],
                          mListWorldSalts[1],
                          mListWorldSalts[2],
                          mListWorldSalts[3],
                          mListWorldSalts[4],
                          mListWorldSalts[5],
                          mListWorldSalts[6],
                          mListWorldSalts[7],
                          
                          mPlugKeyA,
                          mPlugKeyB,
                          
                          mListSBoxes,
                          mHotPack,
                          
                          &aStatements,
                          pErrorMessage)) {
            
            if (pErrorMessage != nullptr && pErrorMessage->empty()) {
                *pErrorMessage = "CSPKDF::Bake failed";
            }
            return false;
        }
        
        aLoop.AddBody(&aStatements);
        aBatch.CommitLoop(&aLoop);
    }
    
    
    pBranch.AddBatch(aBatch);
    return true;
}
