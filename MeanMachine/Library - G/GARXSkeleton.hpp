//
//  GARXSkeleton.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/8/26.
//

#ifndef GARXSkeleton_hpp
#define GARXSkeleton_hpp

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_set>
#include "GARXTypes.hpp"

enum class GARXStatementType : std::uint8_t {
    kInv = 0,
    kRoundSeed = 1,
    kForwardLead = 2,
    kForwardFeedback = 3,
    kForwardRotate = 4,
    kUnwind = 5,
    kCrush = 6,
    kCarry = 7
};

enum class GARXSkeletonPattern : std::uint8_t {
    kInv = 0,
    kRingForward = 1,
    kStride2Lead = 2,
    kReverseRing = 3,
    kLongCross = 4
};


class GARXSkeletonForwardRound {
public:
    GARXSkeletonForwardRound();
    GARXSkeletonForwardRound(GARXType pLead, GARXType pSource, GARXType pFeedback);
    
    GARXType                                mLead;
    GARXType                                mSource;
    GARXType                                mFeedback;
};

enum class GARXUnwindShape : std::uint8_t {
    kInv = 0,
    kCurrentPreviousOrbiter = 1,
    kCurrentCrossOrbiter = 2,
    kOrbiterPair = 3
};

class GARXSkeletonBackwardRound {
public:
    GARXSkeletonBackwardRound();
    GARXSkeletonBackwardRound(GARXUnwindShape pShape,
                              GARXType pTarget,
                              GARXType pInputA,
                              GARXType pInputB,
                              GARXType pInputC);
    
    GARXUnwindShape mShape;
    
    GARXType mTarget;
    GARXType mInputA;
    GARXType mInputB;
    GARXType mInputC;
};

class GARXSkeletonPass {
public:
    GARXSkeletonPass();

    GARXSkeletonPattern                         mPattern;
    std::vector<GARXSkeletonForwardRound>       mForward;
    std::vector<GARXSkeletonBackwardRound>      mBackward;
    
};

class GARXSkeleton {
public:
    GARXSkeleton();

    std::vector<GARXSkeletonPass>          mPasses;
    
    static bool IsRoundType(GARXType pType);
    static bool IsStateType(GARXType pType);
    
    static bool IsPlugVisibleType(GARXType pType);
    static bool IsSecretContextType(GARXType pType);
    static bool IsScatterInputType(GARXType pType);

    static const char *GetTypeName(GARXType pType);
    static const char *GetStatementKindName(GARXStatementType pKind);
    static const char *GetDatumKindName(GARXDatumKind pKind);
    
};

#endif /* GARXSkeleton_hpp */
