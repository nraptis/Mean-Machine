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

enum class GARXType : std::uint8_t {
    kInv = 0,

    kStreamCurrent = 1,
    kStreamPrevious = 2,
    kStreamScatter = 3,
    kStreamCross = 4,

    kSecretCurrent = 5,
    kSecretPrevious = 6,
    kSecretScatter = 7,
    kCarry = 8,

    kStateA = 10,
    kStateB = 11,
    kStateC = 12,
    kStateD = 13,
    kStateE = 14,
    kStateF = 15,
    kStateG = 16,
    kStateH = 17,

    kRoundA = 20,
    kRoundB = 21,
    kRoundC = 22,
    kRoundD = 23,
    kRoundE = 24,
    kRoundF = 25,
    kRoundG = 26,
    kRoundH = 27
};

enum class GARXSaltDomain : std::uint8_t {
    kInv = 0,

    kInitA = 1,
    kInitB = 2,

    kPlugA = 3,
    kPlugB = 4,

    kUnwindA = 5,
    kUnwindB = 6
};

struct GARXTypePair {
    GARXType mTypeA;
    GARXType mTypeB;
};

struct GARXTypeHash {
    std::size_t operator()(GARXType pType) const { return static_cast<std::size_t>(pType); }
};

enum class GARXDatumKind : std::uint8_t {
    kInv = 0,
    kType = 1,
    kLoopKey = 2,
    kPlugKey = 3,
    kHotAdd = 4,
    kHotMul = 5
};

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
    kCurrentPreviousRound = 1,
    kCurrentCrossRound = 2,
    kRoundPair = 3
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

    static const char *GetSaltDomainName(GARXSaltDomain pDomain);
    
};

#endif /* GARXSkeleton_hpp */
