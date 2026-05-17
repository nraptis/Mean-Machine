//
//  GARXSkeleton.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/8/26.
//

#include "GARXSkeleton.hpp"

static void AppendBackwardRoundSix(GARXSkeletonPass *pRound) {
    
    if (pRound == nullptr) {
        return;
    }
    
    if (pRound->mForward.size() < 6) {
        return;
    }
    
    const GARXSkeletonForwardRound &aForward0 = pRound->mForward[0];
    const GARXSkeletonForwardRound &aForward1 = pRound->mForward[1];
    const GARXSkeletonForwardRound &aForward2 = pRound->mForward[2];
    const GARXSkeletonForwardRound &aForward3 = pRound->mForward[3];
    const GARXSkeletonForwardRound &aForward4 = pRound->mForward[4];
    const GARXSkeletonForwardRound &aForward5 = pRound->mForward[5];
    
    GARXSkeletonBackwardRound aBackward0(
        GARXUnwindShape::kCurrentPreviousOrbiter,
        GARXType::kUnwindA,
                                         GARXType::kSecretCurrent,
                                         GARXType::kSecretPrevious,
        aForward0.mFeedback
    );
    
    GARXSkeletonBackwardRound aBackward1(
        GARXUnwindShape::kCurrentCrossOrbiter,
        GARXType::kUnwindB,
        GARXType::kSecretCurrent,
        GARXType::kSecretScatter,
        aForward1.mLead
    );
    
    GARXSkeletonBackwardRound aBackward2(
        GARXUnwindShape::kOrbiterPair,
        GARXType::kUnwindC,
        aForward2.mSource,
        aForward2.mFeedback,
        GARXType::kInv
    );
    
    GARXSkeletonBackwardRound aBackward3(
        GARXUnwindShape::kCurrentPreviousOrbiter,
        GARXType::kUnwindD,
        GARXType::kSecretCurrent,
        GARXType::kSecretPrevious,
        aForward3.mFeedback
    );
    
    GARXSkeletonBackwardRound aBackward4(
        GARXUnwindShape::kCurrentCrossOrbiter,
        GARXType::kUnwindE,
        GARXType::kSecretCurrent,
        GARXType::kSecretScatter,
        aForward4.mLead
    );
    
    GARXSkeletonBackwardRound aBackward5(
        GARXUnwindShape::kOrbiterPair,
        GARXType::kUnwindF,
        aForward5.mLead,
        aForward5.mSource,
        GARXType::kInv
    );
    
    pRound->mBackward.push_back(aBackward0);
    pRound->mBackward.push_back(aBackward1);
    pRound->mBackward.push_back(aBackward2);
    pRound->mBackward.push_back(aBackward3);
    pRound->mBackward.push_back(aBackward4);
    pRound->mBackward.push_back(aBackward5);
}

GARXSkeletonForwardRound::GARXSkeletonForwardRound() {
    mLead = GARXType::kInv;
    mSource = GARXType::kInv;
    mFeedback = GARXType::kInv;
}

GARXSkeletonForwardRound::GARXSkeletonForwardRound(GARXType pLead,
                                                   GARXType pSource,
                                                   GARXType pFeedback) {
    mLead = pLead;
    mSource = pSource;
    mFeedback = pFeedback;
}

GARXSkeletonBackwardRound::GARXSkeletonBackwardRound() {
    mShape = GARXUnwindShape::kInv;
    
    mTarget = GARXType::kInv;
    mInputA = GARXType::kInv;
    mInputB = GARXType::kInv;
    mInputC = GARXType::kInv;
}

GARXSkeletonBackwardRound::GARXSkeletonBackwardRound(GARXUnwindShape pShape,
                                                     GARXType pTarget,
                                                     GARXType pInputA,
                                                     GARXType pInputB,
                                                     GARXType pInputC) {
    mShape = pShape;
    mTarget = pTarget;
    mInputA = pInputA;
    mInputB = pInputB;
    mInputC = pInputC;
}

GARXSkeletonPass::GARXSkeletonPass() {
    mPattern = GARXSkeletonPattern::kInv;
}


GARXSkeleton::GARXSkeleton() {
    
    //
    // Pattern 0: ring-forward
    //
    {
        GARXSkeletonPass aRound;
        aRound.mPattern = GARXSkeletonPattern::kRingForward;
        
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterA, GARXType::kOrbiterB, GARXType::kOrbiterD));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterB, GARXType::kOrbiterC, GARXType::kOrbiterE));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterC, GARXType::kOrbiterD, GARXType::kOrbiterF));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterD, GARXType::kOrbiterE, GARXType::kOrbiterA));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterE, GARXType::kOrbiterF, GARXType::kOrbiterB));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterF, GARXType::kOrbiterA, GARXType::kOrbiterC));
        
        AppendBackwardRoundSix(&aRound);
        
        mPasses.push_back(aRound);
    }
    
    //
    // Pattern 1: stride-2 lead order
    //
    {
        GARXSkeletonPass aRound;
        aRound.mPattern = GARXSkeletonPattern::kStride2Lead;
        
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterA, GARXType::kOrbiterB, GARXType::kOrbiterD));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterC, GARXType::kOrbiterD, GARXType::kOrbiterF));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterE, GARXType::kOrbiterF, GARXType::kOrbiterB));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterB, GARXType::kOrbiterC, GARXType::kOrbiterE));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterD, GARXType::kOrbiterE, GARXType::kOrbiterA));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterF, GARXType::kOrbiterA, GARXType::kOrbiterC));
        
        AppendBackwardRoundSix(&aRound);
        
        mPasses.push_back(aRound);
    }
    
    //
    // Pattern 2: reverse ring
    //
    {
        GARXSkeletonPass aRound;
        aRound.mPattern = GARXSkeletonPattern::kReverseRing;
        
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterA, GARXType::kOrbiterF, GARXType::kOrbiterD));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterF, GARXType::kOrbiterE, GARXType::kOrbiterC));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterE, GARXType::kOrbiterD, GARXType::kOrbiterB));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterD, GARXType::kOrbiterC, GARXType::kOrbiterA));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterC, GARXType::kOrbiterB, GARXType::kOrbiterF));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterB, GARXType::kOrbiterA, GARXType::kOrbiterE));
        
        AppendBackwardRoundSix(&aRound);
        
        mPasses.push_back(aRound);
    }
    
    //
    // Pattern 3: long-cross
    //
    {
        GARXSkeletonPass aRound;
        aRound.mPattern = GARXSkeletonPattern::kLongCross;
        
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterA, GARXType::kOrbiterD, GARXType::kOrbiterF));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterB, GARXType::kOrbiterE, GARXType::kOrbiterA));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterC, GARXType::kOrbiterF, GARXType::kOrbiterB));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterD, GARXType::kOrbiterA, GARXType::kOrbiterC));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterE, GARXType::kOrbiterB, GARXType::kOrbiterD));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kOrbiterF, GARXType::kOrbiterC, GARXType::kOrbiterE));
        
        AppendBackwardRoundSix(&aRound);
        
        mPasses.push_back(aRound);
    }
}

bool GARXSkeleton::IsRoundType(GARXType pType) {
    return (pType >= GARXType::kOrbiterA) && (pType <= GARXType::kOrbiterK);
}

bool GARXSkeleton::IsStateType(GARXType pType) {
    return (pType >= GARXType::kUnwindA) && (pType <= GARXType::kUnwindK);
}

bool GARXSkeleton::IsPlugVisibleType(GARXType pType) {
    switch (pType) {
        case GARXType::kStreamCurrent:
        case GARXType::kStreamPrevious:
        case GARXType::kStreamScatter:
        case GARXType::kStreamCross:
            return true;
        default:
            return false;
    }
}
bool GARXSkeleton::IsSecretContextType(GARXType pType) {
    switch (pType) {
        case GARXType::kSecretCurrent:
        case GARXType::kSecretPrevious:
        case GARXType::kSecretScatter:
        case GARXType::kCarry:
            return true;
        default:
            return false;
    }
}

bool GARXSkeleton::IsScatterInputType(GARXType pType) {
    switch (pType) {
        case GARXType::kStreamCurrent:
        case GARXType::kStreamPrevious:
        case GARXType::kStreamCross:
        case GARXType::kCarry:
            return true;
        default:
            return false;
    }
}

const char *GARXSkeleton::GetTypeName(GARXType pType) {
    switch (pType) {
        case GARXType::kStreamCurrent: return "stream_current";
        case GARXType::kStreamPrevious: return "stream_previous";
        case GARXType::kStreamScatter: return "stream_scatter";
        case GARXType::kStreamCross: return "stream_cross";
            
        case GARXType::kSecretCurrent: return "secret_current";
        case GARXType::kSecretPrevious: return "secret_previous";
        case GARXType::kSecretScatter: return "secret_scatter";
        case GARXType::kCarry: return "carry";
            
        case GARXType::kUnwindA: return "wanderer_a";
        case GARXType::kUnwindB: return "wanderer_b";
        case GARXType::kUnwindC: return "wanderer_c";
        case GARXType::kUnwindD: return "wanderer_d";
        case GARXType::kUnwindE: return "wanderer_e";
        case GARXType::kUnwindF: return "wanderer_f";
        case GARXType::kUnwindG: return "wanderer_g";
        case GARXType::kUnwindH: return "wanderer_h";
        case GARXType::kUnwindI: return "wanderer_i";
        case GARXType::kUnwindJ: return "wanderer_j";
        case GARXType::kUnwindK: return "wanderer_k";

        case GARXType::kOrbiterA: return "orbiter_a";
        case GARXType::kOrbiterB: return "orbiter_b";
        case GARXType::kOrbiterC: return "orbiter_c";
        case GARXType::kOrbiterD: return "orbiter_d";
        case GARXType::kOrbiterE: return "orbiter_e";
        case GARXType::kOrbiterF: return "orbiter_f";
        case GARXType::kOrbiterG: return "orbiter_g";
        case GARXType::kOrbiterH: return "orbiter_h";
        case GARXType::kOrbiterI: return "orbiter_i";
        case GARXType::kOrbiterJ: return "orbiter_j";
        case GARXType::kOrbiterK: return "orbiter_k";
            
        default:
            return "invalid";
    }
}

const char *GARXSkeleton::GetStatementKindName(GARXStatementType pKind) {
    switch (pKind) {
        case GARXStatementType::kRoundSeed: return "seed";
        case GARXStatementType::kForwardLead: return "forward_lead";
        case GARXStatementType::kForwardFeedback: return "forward_feedback";
        case GARXStatementType::kForwardRotate: return "forward_rotate";
        case GARXStatementType::kUnwind: return "unwind";
        case GARXStatementType::kCrush: return "crush";
        case GARXStatementType::kCarry: return "carry";
        default: return "invalid";
    }
}

const char *GARXSkeleton::GetDatumKindName(GARXDatumKind pKind) {
    switch (pKind) {
        case GARXDatumKind::kType: return "type";
        case GARXDatumKind::kLoopKey: return "loop_key";
        case GARXDatumKind::kPlugKey: return "plug_key";
        case GARXDatumKind::kHotAdd: return "hot_add";
        case GARXDatumKind::kHotMul: return "hot_mul";
        default:
            return "invalid";
    }
}
