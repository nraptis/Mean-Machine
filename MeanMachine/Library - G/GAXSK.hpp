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

class GAXSKPool;

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
    std::vector<GAXSKInputSlot> mSlots;
    bool mHasDomainMix = true;
    bool mIsIngress = false;
    GAXSKDiffuseKind mDiffuse = GAXSKDiffuseKind::kInvalid;
};

struct GAXSKVariableTerm {
    GAXSKVariable mVariable = GAXSKVariable::kInvalid;
    int mRotation = -1;
};

struct GAXSKScatterMixPlan {
    GAXSKVariable mTarget = GAXSKVariable::kScatter;

    std::vector<GAXSKVariableTerm> mXorTerms;
    std::vector<GAXSKVariableTerm> mAddTerms;

    bool mHasDomainMix = true;
    GAXSKDiffuseKind mDiffuse = GAXSKDiffuseKind::kInvalid;
};


struct GAXSKStatement {
    GAXSKStatementKind mKind = GAXSKStatementKind::kInvalid;
    GAXSKVariable mTarget = GAXSKVariable::kInvalid;
    GAXSKVariable mSource = GAXSKVariable::kInvalid;
    GAXSKContextWordPlan mContextWord;
    GAXSKScatterMixPlan mScatterMix;
};



struct GAXSKSkeleton {
    std::vector<GAXSKStatement> mStatements;
};

class GAXSK {
public:
    
    GAXSK(const GAXSK &) = delete;
    GAXSK();
    ~GAXSK();
    
    GAXSK &operator=(const GAXSK &) = delete;
    
    static bool                             RotationsClash_64_8(int pRotationA, int pRotationB);
    static bool                             RotationsClash_64_8(std::vector<int> pRotations);
    
    
    void                                    Reset();
    bool                                    Bake(GAXSFormat pFormat,
                                                 std::vector<int> pLaneCounts,
                                                 bool pHasDomainMix,
                                                 std::vector<GAXSKSkeleton> *pResult,
                                                 std::string *pErrorMessage);
    
    bool                                    GetPassCount(int *pResult, std::string *pErrorMessage) const;
    bool                                    GetOrbiterCount(int *pResult, std::string *pErrorMessage) const;
    bool                                    GetWandererCount(int *pResult, std::string *pErrorMessage) const;
    
    
    bool                                    GetLaneCountForPass(int pPassIndex,
                                                                int *pResult,
                                                                std::string *pErrorMessage) const;
    
    GAXSKSourceKind                         SourceForIndex(int pIndex);
    GAXSKNonceByteKind                      NonceForIndex(int pIndex);
    
    GAXSKInputSlot                          MakeSourceSlot(GAXSKSourceKind pSource,
                                                           int pOffset,
                                                           bool pReverse,
                                                           int pRotation);
    
    GAXSKInputSlot                          MakeNonceSlot(GAXSKNonceByteKind pNonceByte,
                                                          int pRotation);
    
    GAXSKStatement                          MakePreviousAssignStatement();
    
    GAXSKStatement                          MakeContextWordStatement(GAXSKVariable pTarget,
                                                                     GAXSKDiffuseKind pDiffuse,
                                                                     bool pIsIngress);
    
    bool                                    MakeScatterMixStatement(GAXSKStatement *pResult,
                                                                    std::string *pErrorMessage);
    
    bool                                    BuildSkeletonForLaneCount(int pPassIndex,
                                                                      int pLaneCount,
                                                                      GAXSKSkeleton *pSkeleton,
                                                                      std::string *pErrorMessage);
    
    bool                                    BuildTinySkeletonForLaneCount(int pLaneCount,
                                                                          GAXSKSkeleton *pSkeleton,
                                                                          std::string *pErrorMessage);
    
    GAXSFormat                              mFormat = GAXSFormat::kInvalid;
    bool                                    mHasDomainMix = false;
    std::vector<GAXSKPool *>                mPools;
    std::vector<int>                        mLaneCounts;
    
};


#endif /* GAXSK_hpp */
