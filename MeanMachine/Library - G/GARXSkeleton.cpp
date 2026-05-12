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
        GARXUnwindShape::kCurrentPreviousRound,
        GARXType::kStateA,
                                         GARXType::kSecretCurrent,
                                         GARXType::kSecretPrevious,
        aForward0.mFeedback
    );
    
    GARXSkeletonBackwardRound aBackward1(
        GARXUnwindShape::kCurrentCrossRound,
        GARXType::kStateB,
        GARXType::kSecretCurrent,
        GARXType::kSecretScatter,
        aForward1.mLead
    );
    
    GARXSkeletonBackwardRound aBackward2(
        GARXUnwindShape::kRoundPair,
        GARXType::kStateC,
        aForward2.mSource,
        aForward2.mFeedback,
        GARXType::kInv
    );
    
    GARXSkeletonBackwardRound aBackward3(
        GARXUnwindShape::kCurrentPreviousRound,
        GARXType::kStateD,
        GARXType::kSecretCurrent,
        GARXType::kSecretPrevious,
        aForward3.mFeedback
    );
    
    GARXSkeletonBackwardRound aBackward4(
        GARXUnwindShape::kCurrentCrossRound,
        GARXType::kStateE,
        GARXType::kSecretCurrent,
        GARXType::kSecretScatter,
        aForward4.mLead
    );
    
    GARXSkeletonBackwardRound aBackward5(
        GARXUnwindShape::kRoundPair,
        GARXType::kStateF,
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
        
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundA, GARXType::kRoundB, GARXType::kRoundD));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundB, GARXType::kRoundC, GARXType::kRoundE));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundC, GARXType::kRoundD, GARXType::kRoundF));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundD, GARXType::kRoundE, GARXType::kRoundA));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundE, GARXType::kRoundF, GARXType::kRoundB));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundF, GARXType::kRoundA, GARXType::kRoundC));
        
        AppendBackwardRoundSix(&aRound);
        
        mPasses.push_back(aRound);
    }
    
    //
    // Pattern 1: stride-2 lead order
    //
    {
        GARXSkeletonPass aRound;
        aRound.mPattern = GARXSkeletonPattern::kStride2Lead;
        
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundA, GARXType::kRoundB, GARXType::kRoundD));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundC, GARXType::kRoundD, GARXType::kRoundF));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundE, GARXType::kRoundF, GARXType::kRoundB));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundB, GARXType::kRoundC, GARXType::kRoundE));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundD, GARXType::kRoundE, GARXType::kRoundA));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundF, GARXType::kRoundA, GARXType::kRoundC));
        
        AppendBackwardRoundSix(&aRound);
        
        mPasses.push_back(aRound);
    }
    
    //
    // Pattern 2: reverse ring
    //
    {
        GARXSkeletonPass aRound;
        aRound.mPattern = GARXSkeletonPattern::kReverseRing;
        
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundA, GARXType::kRoundF, GARXType::kRoundD));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundF, GARXType::kRoundE, GARXType::kRoundC));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundE, GARXType::kRoundD, GARXType::kRoundB));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundD, GARXType::kRoundC, GARXType::kRoundA));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundC, GARXType::kRoundB, GARXType::kRoundF));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundB, GARXType::kRoundA, GARXType::kRoundE));
        
        AppendBackwardRoundSix(&aRound);
        
        mPasses.push_back(aRound);
    }
    
    //
    // Pattern 3: long-cross
    //
    {
        GARXSkeletonPass aRound;
        aRound.mPattern = GARXSkeletonPattern::kLongCross;
        
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundA, GARXType::kRoundD, GARXType::kRoundF));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundB, GARXType::kRoundE, GARXType::kRoundA));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundC, GARXType::kRoundF, GARXType::kRoundB));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundD, GARXType::kRoundA, GARXType::kRoundC));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundE, GARXType::kRoundB, GARXType::kRoundD));
        aRound.mForward.push_back(GARXSkeletonForwardRound(GARXType::kRoundF, GARXType::kRoundC, GARXType::kRoundE));
        
        AppendBackwardRoundSix(&aRound);
        
        mPasses.push_back(aRound);
    }
}

bool GARXSkeleton::IsRoundType(GARXType pType) {
    return (pType >= GARXType::kRoundA) && (pType <= GARXType::kRoundH);
}

bool GARXSkeleton::IsStateType(GARXType pType) {
    return (pType >= GARXType::kStateA) && (pType <= GARXType::kStateH);
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
            
        case GARXType::kStateA: return "wanderer_a";
        case GARXType::kStateB: return "wanderer_b";
        case GARXType::kStateC: return "wanderer_c";
        case GARXType::kStateD: return "wanderer_d";
        case GARXType::kStateE: return "wanderer_e";
        case GARXType::kStateF: return "wanderer_f";
        case GARXType::kStateG: return "wanderer_g";
        case GARXType::kStateH: return "wanderer_h";

        case GARXType::kRoundA: return "orbiter_a";
        case GARXType::kRoundB: return "orbiter_b";
        case GARXType::kRoundC: return "orbiter_c";
        case GARXType::kRoundD: return "orbiter_d";
        case GARXType::kRoundE: return "orbiter_e";
        case GARXType::kRoundF: return "orbiter_f";
        case GARXType::kRoundG: return "orbiter_g";
        case GARXType::kRoundH: return "orbiter_h";
            
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

const char *GARXSkeleton::GetSaltDomainName(GARXSaltDomain pDomain) {
    switch (pDomain) {
        case GARXSaltDomain::kInitA: return "init_a";
        case GARXSaltDomain::kInitB: return "init_b";
        case GARXSaltDomain::kPlugA: return "plug_a";
        case GARXSaltDomain::kPlugB: return "plug_b";
        case GARXSaltDomain::kUnwindA: return "unwind_a";
        case GARXSaltDomain::kUnwindB: return "unwind_b";
        default: return "invalid";
    }
}
