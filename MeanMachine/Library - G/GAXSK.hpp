//
//  GAXSK.hpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/18/26.
//

#ifndef GAXSK_hpp
#define GAXSK_hpp

#include <cstdint>
#include <vector>
#include <string>


enum class GAXSFormat : std::uint8_t {
    kInvalid = 0,
    kSixSix
};

enum class GAXSKDiffuseKind : std::uint8_t {
    kInvalid = 0,
    kDiffuseA,
    kDiffuseB,
    kDiffuseC
};

enum class GAXSKSaltRole : std::uint8_t {
    kInvalid = 0,
    kOrbiterAssign,
    kOrbiterUpdate,
    kWandererAssign,
};

enum class GAXSKInputSlotKind : std::uint8_t {
    kInvalid = 0,
    kSource,
    kNonceByte
};

enum class GAXSKSourceKind : std::uint8_t {
    kInvalid = 0,
    kSourceA,
    kSourceB,
    kSourceC,
    kSourceD,
};

enum class GAXSKNonceByteKind : std::uint8_t {
    kInvalid = 0,
    kNonceA,
    kNonceB,
    kNonceC,
    kNonceD,
    kNonceE,
    kNonceF,
    kNonceG,
    kNonceH,
};

enum class GAXSKOpKind : std::uint8_t {
    kInvalid = 0,
    kAdd,
    kXor
};

enum class GAXSKVariable : std::uint8_t {
    kInvalid = 0,

    kIngress,
    kCross,
    kPrevious,
    kScatter,

    kCarry,

    kOrbitA,
    kOrbitB,
    kOrbitC,
    kOrbitD,
    kOrbitE,
    kOrbitF,
    kOrbitG,
    kOrbitH,
    kOrbitI,
    kOrbitJ,
    kOrbitK,

    kWandererA,
    kWandererB,
    kWandererC,
    kWandererD,
    kWandererE,
    kWandererF,
    kWandererG,
    kWandererH,
    kWandererI,
    kWandererJ,
    kWandererK,
};

enum class GAXSKStatementKind : std::uint8_t {
    kInvalid = 0,

    kPreviousAssign,

    kContextWordAssign,
    kContextWordDomainMix,
    kContextWordDiffuse,

    kScatterMix,

    kOrbiterAssign,
    kOrbiterAdd,
    kOrbiterXor,
    kOrbiterMulRotate,

    kWandererAdd,
    kWandererXor,
    kWandererMulRotate,

    kCarryMix,
    kCarryMulRotate,
    kCarryFinalXor
};

struct GAXSKInputSlot {
    GAXSKInputSlotKind mKind = GAXSKInputSlotKind::kInvalid;

    GAXSKSourceKind mSource = GAXSKSourceKind::kInvalid;
    GAXSKNonceByteKind mNonceByte = GAXSKNonceByteKind::kInvalid;

    int mOffset = 0;
    bool mReverse = false;

    int mRotation = -1;
};

struct GAXSKContextWordPlan {
    GAXSKVariable mTarget = GAXSKVariable::kInvalid;
    
    std::vector<GAXSKInputSlot> mXorSlots;
    std::vector<GAXSKInputSlot> mAddXorSlots;

    bool mHasDomainMix = true;
    bool mIsIngress = false;

    GAXSKDiffuseKind mDiffuse = GAXSKDiffuseKind::kInvalid;
};

struct GAXSKStatement {
    
    // ingress =
    //
    // source a, reversed, offset 17, rotated 3
    // source b, non-reversed, offset 11, rotated 11
    // source c, non-reversed, offset 0, rotated 23
    // nonce byte a, rotated 51
    // nonce byte b, rotated 43
    // nonce byte c, rotated 35
    
    GAXSKStatementKind mKind = GAXSKStatementKind::kInvalid;
    GAXSKVariable mTarget = GAXSKVariable::kInvalid;

    GAXSKVariable mSource = GAXSKVariable::kInvalid;

    GAXSKContextWordPlan mContextWord;
};

struct GAXSKSkeleton {
    std::vector<GAXSKStatement> mStatements;
};

class GAXSK {
public:
    // new plan: we want to minimize the number of source reads.
    // so, if there's 2, we should do 1 read ingress < source_a, and one cross < source_b
    // if there's 1, we still have to do 2
    // if there's 3, we add 1 more to ingress
    // if there's 4, we do 2 and 2
    // then that's it, if it's not [1, 2, 3, 4], it's an error
    static bool                                 Bake(GAXSFormat pFormat,
                                                     std::vector<int> pLaneCounts,
                                                     bool pHasDomainMix,
                                                     std::vector<GAXSKSkeleton> *pResult,
                                                     std::string *pErrorMessage);
    
    static GAXSKSourceKind                      SourceForIndex(int pIndex);
    static GAXSKNonceByteKind                   NonceForIndex(int pIndex);
    
    static GAXSKInputSlot                       MakeSourceSlot(GAXSKSourceKind pSource,
                                                               int pOffset,
                                                               bool pReverse,
                                                               int pRotation);
    
    static GAXSKInputSlot                       MakeNonceSlot(GAXSKNonceByteKind pNonceByte,
                                                              int pRotation);
    
    static GAXSKStatement                       MakePreviousAssignStatement();
    
    static GAXSKStatement                       MakeContextWordStatement(GAXSKVariable pTarget,
                                                                         GAXSKDiffuseKind pDiffuse,
                                                                         bool pIsIngress,
                                                                         bool pHasDomainMix);
    
    static bool                                 BuildTinySkeletonForLaneCount(int pLaneCount,
                                                                              GAXSKSkeleton *pSkeleton,
                                                                              std::string *pErrorMessage);
    
    static void                                 SetError(std::string *pErrorMessage,
                                                         const std::string &pMessage);
};


#endif /* GAXSK_hpp */
