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
    mStreamCross = GSymbol::Var(TwistVariable::kCrossIngress);
    
    
    mSecretCurrent = GSymbol::Var(TwistVariable::kPrivateIngress);
    mSecretPrevious = GSymbol::Var(TwistVariable::kPrivatePrevious);
    mSecretScatter = GSymbol::Var(TwistVariable::kPrivateScatter);
    mSecretWrite = GSymbol::Var(TwistVariable::kPrivateWrite);
    
    mCarry = GSymbol::Var(TwistVariable::kCarry);
    
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

    mListWorkLanes.clear();
    mListWorkLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneA)));
    mListWorkLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneB)));
    mListWorkLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneC)));
    mListWorkLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneD)));
    mListWorkLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneE)));
    mListWorkLanes.push_back(BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kWorkLaneF)));
    
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
        mListWorkLanes[0],
        mListWorkLanes[1]
    };
    
    std::vector<GSymbol> aCrossBuffers = {
        mSource,
        mListOpLanes[0],
        mListWorkLanes[0],
        mListWorkLanes[1]
    };
    
    std::vector<GSymbol> aDestBuffers = {
        mListWorkLanes[0],
        mListWorkLanes[1],
        mListWorkLanes[2],
        mListWorkLanes[3]
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

    GDomainSaltSet aDomainSaltSet;
    aDomainSaltSet.mOrbiter.mSaltA = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiter, TwistSaltLane::kA);
    aDomainSaltSet.mOrbiter.mSaltB = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiter, TwistSaltLane::kB);
    aDomainSaltSet.mOrbiter.mSaltC = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiter, TwistSaltLane::kC);
    aDomainSaltSet.mOrbiter.mSaltD = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiter, TwistSaltLane::kD);
    aDomainSaltSet.mOrbiter.mSaltE = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiter, TwistSaltLane::kE);
    aDomainSaltSet.mOrbiter.mSaltF = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiter, TwistSaltLane::kF);

    aDomainSaltSet.mUnwind.mSaltA = BufParamSymbolDomainSalt(TwistSaltPhase::kUnwind, TwistSaltLane::kA);
    aDomainSaltSet.mUnwind.mSaltB = BufParamSymbolDomainSalt(TwistSaltPhase::kUnwind, TwistSaltLane::kB);
    aDomainSaltSet.mUnwind.mSaltC = BufParamSymbolDomainSalt(TwistSaltPhase::kUnwind, TwistSaltLane::kC);
    aDomainSaltSet.mUnwind.mSaltD = BufParamSymbolDomainSalt(TwistSaltPhase::kUnwind, TwistSaltLane::kD);
    aDomainSaltSet.mUnwind.mSaltE = BufParamSymbolDomainSalt(TwistSaltPhase::kUnwind, TwistSaltLane::kE);
    aDomainSaltSet.mUnwind.mSaltF = BufParamSymbolDomainSalt(TwistSaltPhase::kUnwind, TwistSaltLane::kF);

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

                          //
                          // stream scatter components
                          //
                          mStreamCurrent,
                          mStreamPrevious,
                          mStreamCross,
                          mStreamCurrent,

                          //
                          // secret scatter components
                          //
                          mSecretCurrent,
                          mSecretPrevious,
                          mStreamCross,
                          mCarry,
                          
                          aDomainSaltSet,
                          
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
    aDiff.mInputA = mListWorkLanes[0];
    aDiff.mInputB = mListWorkLanes[1];
    
    aDiff.mOutputA = mListWorkLanes[0];
    aDiff.mOutputB = mListOpLanes[1];
    
    aDiff.mShuffleEntropyA = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256A));
    aDiff.mShuffleEntropyB = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256B));
    aDiff.mShuffleEntropyC = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256C));
    aDiff.mShuffleEntropyD = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256D));
    
    aDiff.mOperationSourceA = mListOpLanes[0];
    aDiff.mOperationSourceB = mListOpLanes[1];
    
    GRunMatrixDiffusion aFuss;
    if (!aFuss.Bake(aDiff, &aBatch, pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "GRunMatrixDiffusion::Bake failed during GSeedRunKDF::Build";
        }
        return false;
    }
    
    if (aBatch.IsInvalid()) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "GSeedRunKDF::Build produced an invalid (empty) KDF batch";
        }
        return false;
    }

    const std::size_t aBatchCountBefore = pBranch.GetBatchJsonText().size();
    pBranch.AddBatch(aBatch);
    if (pBranch.GetBatchJsonText().size() <= aBatchCountBefore) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "TwistProgramBranch::AddBatch failed while appending KDF batch";
        }
        return false;
    }
    return true;
}
