//
//  GSeedRunKDF.cpp
//  MeanMachine
//
//  Created by Codex on 5/10/26.
//

#include "GSeedRunKDF.hpp"
#include "GIndexShuffle.hpp"
#include "GRunMatrixDiffusion.hpp"

#include <cstdio>

GSeedRunKDF::GSeedRunKDF() {
    Reset();
}

GSeedRunKDF::~GSeedRunKDF() {
}

void GSeedRunKDF::Reset() {
    mLoopIndex = GSymbol::Var(TwistVariable::kIndex);
    mSource = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kSource));
    
    
    mStreamCurrent = GSymbol::Var(TwistVariable::kPublicIngress);
    mStreamPrevious = GSymbol::Var(TwistVariable::kPublicPrevious);
    mStreamScatter = GSymbol::Var(TwistVariable::kPublicScatter);
    
    
    mSecretCurrent = GSymbol::Var(TwistVariable::kPrivateIngress);
    mSecretPrevious = GSymbol::Var(TwistVariable::kPrivatePrevious);
    mSecretScatter = GSymbol::Var(TwistVariable::kPrivateScatter);
    mSecretWrite = GSymbol::Var(TwistVariable::kPrivateWrite);
    
    mStreamCross = GSymbol::Var(TwistVariable::kCrossIngress);
    mCarry = GSymbol::Var(TwistVariable::kCarry);

    mUnwindA = GSymbol::Var(TwistVariable::kUnwindA);
    mUnwindB = GSymbol::Var(TwistVariable::kUnwindB);
    mUnwindC = GSymbol::Var(TwistVariable::kUnwindC);
    mUnwindD = GSymbol::Var(TwistVariable::kUnwindD);
    mUnwindE = GSymbol::Var(TwistVariable::kUnwindE);
    mUnwindF = GSymbol::Var(TwistVariable::kUnwindF);

    mOrbiterA = GSymbol::Var(TwistVariable::kOrbiterA);
    mOrbiterB = GSymbol::Var(TwistVariable::kOrbiterB);
    mOrbiterC = GSymbol::Var(TwistVariable::kOrbiterC);
    mOrbiterD = GSymbol::Var(TwistVariable::kOrbiterD);
    mOrbiterE = GSymbol::Var(TwistVariable::kOrbiterE);
    mOrbiterF = GSymbol::Var(TwistVariable::kOrbiterF);

    mPlugKeyA = GSymbol::Var(TwistVariable::kPlugKeyA);
    mPlugKeyB = GSymbol::Var(TwistVariable::kPlugKeyB);
    mPlugKeyC = GSymbol::Var(TwistVariable::kPlugKeyC);
    mPlugKeyD = GSymbol::Var(TwistVariable::kPlugKeyD);
    mPlugKeyE = GSymbol::Var(TwistVariable::kPlugKeyE);
    mPlugKeyF = GSymbol::Var(TwistVariable::kPlugKeyF);

    mPublicIngressDomainWord = GSymbol::Var(TwistVariable::kPublicIngressDomainWord);
    mPrivateIngressDomainWord = GSymbol::Var(TwistVariable::kPrivateIngressDomainWord);
    mCrossIngressDomainWord = GSymbol::Var(TwistVariable::kCrossIngressDomainWord);
    
    

    mListSBoxes.clear();
    mListSBoxes.push_back(BufSymbol(TwistBufferKey::SBox(TwistSBoxOwner::kInbuilt, TwistDomainFamily::kWorkLane, TwistSBoxLane::kA)));
    mListSBoxes.push_back(BufSymbol(TwistBufferKey::SBox(TwistSBoxOwner::kInbuilt, TwistDomainFamily::kWorkLane, TwistSBoxLane::kB)));
    mListSBoxes.push_back(BufSymbol(TwistBufferKey::SBox(TwistSBoxOwner::kInbuilt, TwistDomainFamily::kWorkLane, TwistSBoxLane::kC)));
    mListSBoxes.push_back(BufSymbol(TwistBufferKey::SBox(TwistSBoxOwner::kInbuilt, TwistDomainFamily::kWorkLane, TwistSBoxLane::kD)));
    mListSBoxes.push_back(BufSymbol(TwistBufferKey::SBox(TwistSBoxOwner::kInbuilt, TwistDomainFamily::kWorkLane, TwistSBoxLane::kE)));
    mListSBoxes.push_back(BufSymbol(TwistBufferKey::SBox(TwistSBoxOwner::kInbuilt, TwistDomainFamily::kWorkLane, TwistSBoxLane::kF)));
    mListSBoxes.push_back(BufSymbol(TwistBufferKey::SBox(TwistSBoxOwner::kInbuilt, TwistDomainFamily::kWorkLane, TwistSBoxLane::kG)));
    mListSBoxes.push_back(BufSymbol(TwistBufferKey::SBox(TwistSBoxOwner::kInbuilt, TwistDomainFamily::kWorkLane, TwistSBoxLane::kH)));

    mListWorkers.clear();
    mListWorkers.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneA)));
    mListWorkers.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneB)));
    mListWorkers.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneC)));
    mListWorkers.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneD)));
    mListWorkers.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneE)));
    mListWorkers.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneF)));
    
    mListOpLanes.clear();
    mListOpLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kOperationLaneA)));
    mListOpLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kOperationLaneB)));
    mListOpLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kOperationLaneC)));
    mListOpLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kOperationLaneD)));
    mListOpLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kOperationLaneE)));
    mListOpLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kOperationLaneF)));
    
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
            *pErrorMessage = "failed to bake GARXPlan plan for KDF pass";
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

    std::vector<GStatement> aPrepStatements;
    if (!GIndexShuffle::BakeExecute256(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256A)),
                                       mListOpLanes[2],
                                       &aPrepStatements,
                                       pErrorMessage)) {
        return false;
    }
    aBatch.CommitStatements(&aPrepStatements);
    if (!GIndexShuffle::BakeExecute256(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256B)),
                                       mListOpLanes[3],
                                       &aPrepStatements,
                                       pErrorMessage)) {
        return false;
    }
    aBatch.CommitStatements(&aPrepStatements);
    
    for (std::size_t aPassIndex = 0; aPassIndex < 4U; aPassIndex++) {
        
        if (aPassIndex >= aPlan.mPasses.size() ||
            aPlan.mPasses[aPassIndex] == nullptr) {
            
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GMox plan missing pass plan";
            }
            return false;
        }
        
        GLoop aLoop;
        GStatement aStatement;
        std::vector<GStatement> aStatements;
        std::vector<GStatement> aDomainStatements;
        
        const GSymbol aInputBuffer = aInputBuffers[aPassIndex];
        const GSymbol aCrossBuffer = aCrossBuffers[aPassIndex];
        
        aDomainStatements.push_back(
            GStatement::RawLine(mPublicIngressDomainWord.mName + " = pConstants->mDomainConstantPublicIngress;")
        );
        aDomainStatements.push_back(
            GStatement::RawLine(mPrivateIngressDomainWord.mName + " = pConstants->mDomainConstantPrivateIngress;")
        );
        aDomainStatements.push_back(
            GStatement::RawLine(mCrossIngressDomainWord.mName + " = pConstants->mDomainConstantCrossIngress;")
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
        
        if (!CSPKDF::Bake(aPlan.mPasses[aPassIndex],
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
                          mUnwindA,
                          mUnwindB,
                          mUnwindC,
                          mUnwindD,
                          mUnwindE,
                          mUnwindF,
                          
                          mOrbiterA,
                          mOrbiterB,
                          mOrbiterC,
                          mOrbiterD,
                          mOrbiterE,
                          mOrbiterF,

                          nullptr,
                          nullptr,
                          nullptr,
                          
                          mPlugKeyA,
                          mPlugKeyB,
                          mPlugKeyC,
                          mPlugKeyD,
                          mPlugKeyE,
                          mPlugKeyF,
                          
                          mListSBoxes,
                          mHotPack,
                          
                          &aStatements,
                          pErrorMessage)) {
            
            if (pErrorMessage != nullptr && pErrorMessage->empty()) {
                *pErrorMessage = "CSPKDF2::Bake failed";
            }
            return false;
        }
        
        aLoop.AddBody(&aStatements);
        aBatch.CommitLoop(&aLoop);
    }
    
    
    GRunMatrixDiffusionConfig aDiff;
    aDiff.mSelect = GSymbol::Var(TwistVariable::kOrbiterE);
    aDiff.mInputA = mListWorkers[0];
    aDiff.mInputB = mListWorkers[1];
    
    aDiff.mOutputA = mListWorkers[0];
    aDiff.mOutputB = mListOpLanes[1];
    
    aDiff.mShuffleEntropyA = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256A));
    aDiff.mShuffleEntropyB = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256B));
    aDiff.mShuffleEntropyC = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256C));
    aDiff.mShuffleEntropyD = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256D));
    
    aDiff.mOperationSourceA = mListOpLanes[0];
    aDiff.mOperationSourceB = mListOpLanes[1];
    
    GRunMatrixDiffusion aFuss;
    if (!aFuss.Bake(aDiff, &aBatch, pErrorMessage)) {
        printf("cain saw WA^\n");
    }
    
    pBranch.AddBatch(aBatch);
    return true;
}
