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
#include "TwistWorkSpace.hpp"

class GAXSKPool;
struct GAXSKModelStatement;
class GAXSKModel;
enum class GAssignType : std::uint8_t;

enum class GAXSKUpdateRotationParityMode : std::uint8_t {
    kAllowEven = 0,
    kSuppressEven
};

enum class GAXSKModelOperation: std::uint8_t {
    kInvalid = 0,
    kSet,
    kAdd,
    kXor,
    kMulRotate
};

enum class GAXSKModelTermKind: std::uint8_t {
    kInvalid = 0,
    kVariable,
    kHotAdd,
    kHotMul
};

enum class GAXSFormat : std::uint8_t {
    kInvalid = 0,
    kN5,
    kN7,
    kN9,
    kN11
};

enum class GAXSKDiffuseKind : std::uint8_t {
    kInvalid = 0,
    kDiffuseA,
    kDiffuseB,
    kDiffuseC
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
    kSourceE,
    kSourceF,
    kSourceG,
    kSourceH,
    kSourceI,
    kSourceJ
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
    kNonceI,
    kNonceJ,
    kNonceK,
    kNonceL,
    kNonceM,
    kNonceN,
    kNonceO,
    kNonceP,
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
    
    kComment,

    kPreviousAssign,

    kContextWordAssign,
    kScatterMix,

    kOrbiterAssign,
    kOrbiterAdd,
    kOrbiterXor,
    kOrbiterMulRotate,

    kIngressCrush,
    
    kWandererAdd,
    kWandererXor,
    kWandererMulRotate,
    
    kCarryCrush
};

struct GAXSKInputSlot {
    GAXSKInputSlotKind mKind = GAXSKInputSlotKind::kInvalid;
    GAXSKSourceKind mSource = GAXSKSourceKind::kInvalid;
    GAXSKNonceByteKind mNonceByte = GAXSKNonceByteKind::kInvalid;
    //int mOffset = 0;
    
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

enum class GAXSKScatterMixOp : std::uint8_t {
    kInvalid = 0,
    kAdd = 1,
    kXor = 2
};

struct GAXSKScatterMixPair {
    GAXSKVariableTerm mLeft;
    GAXSKVariableTerm mRight;
    GAXSKScatterMixOp mOp = GAXSKScatterMixOp::kInvalid;
};

struct GAXSKScatterMixPlan {
    GAXSKVariable mTarget = GAXSKVariable::kScatter;
    GAXSKScatterMixPair mLeftPair;
    GAXSKScatterMixPair mRightPair;
    GAXSKScatterMixOp mOuterOp = GAXSKScatterMixOp::kInvalid;
    bool mHasDomainMix = true;
    GAXSKDiffuseKind mDiffuse = GAXSKDiffuseKind::kInvalid;
};

struct GAXSKUpdateTerm {
    GAXSKModelTermKind mKind = GAXSKModelTermKind::kInvalid;
    GAXSKVariable mVariable = GAXSKVariable::kInvalid;
    int mHotIndex = -1;
    bool mHasRotation = false;
    int mRotation = 32;
};

struct GAXSKUpdateRotationSlot {
    GAXSKUpdateTerm *mTerm = nullptr;
    int *mStatementRotation = nullptr;
};

struct GAXSKUpdatePlan {
    GAXSKVariable mTarget = GAXSKVariable::kInvalid;
    std::vector<GAXSKUpdateTerm> mTerms;

    bool mHasRotation = false;
    int mRotation = 32;
};

struct GAXSKCrushPairPlan {
    GAXSKVariable mA = GAXSKVariable::kInvalid;
    GAXSKVariable mB = GAXSKVariable::kInvalid;

    bool mRotateA = false;
    int mRotation = -1;

    GAXSKOpKind mOp = GAXSKOpKind::kInvalid; // add or xor
};

struct GAXSKCrushOddPlan {
    GAXSKVariable mVariable = GAXSKVariable::kInvalid;

    bool mHasRotation = false;
    int mRotation = -1;
};

struct GAXSKCrushPlan {
    GAXSKVariable mTarget = GAXSKVariable::kInvalid;

    std::vector<GAXSKCrushPairPlan> mPairs;

    bool mHasOdd = false;
    GAXSKCrushOddPlan mOdd;

    bool mHasFinalTerm = false;
    GAXSKVariableTerm mFinalTerm;

    GAXSKOpKind mOuterOp = GAXSKOpKind::kInvalid;
    bool mHasDiffuse = true;
    GAXSKDiffuseKind mDiffuse = GAXSKDiffuseKind::kInvalid;
};

enum class GAXSKSaltRole : std::uint8_t {
    kInvalid = 0,
    kOrbiterAssign,
    kOrbiterUpdate,
    kWandererUpdate
};

struct WandererUpdateRowPlan {
    int                         mIndex = -1;
    GAXSKVariable               mTarget = GAXSKVariable::kInvalid;
    GAXSKVariable               mStream = GAXSKVariable::kInvalid;
    GAXSKVariable               mOrbiterA = GAXSKVariable::kInvalid;
    GAXSKVariable               mOrbiterB = GAXSKVariable::kInvalid;
    bool                        mUseXor = false;
    bool                        mUseCarry = false;
};

struct GAXSKStatement {
    GAXSKStatementKind          mKind = GAXSKStatementKind::kInvalid;
    GAXSKVariable               mTarget = GAXSKVariable::kInvalid;
    GAXSKVariable               mSource = GAXSKVariable::kInvalid;
    GAXSKContextWordPlan        mContextWord;
    GAXSKScatterMixPlan         mScatterMix;
    GAXSKUpdatePlan             mUpdate;
    GAXSKCrushPlan              mCrush;
    GAXSKCrushPlan              mCarry;
};

struct GAXSKSkeleton {
    GAXSKSkeleton();
    bool HasNonceSlots() const;

    std::vector<GAXSKStatement>             mStatements;
    GAssignType                             mAssignType;
};

struct GAXSKSourceLayout {
    std::vector<GAXSKSourceKind>             mIngress;
    std::vector<GAXSKSourceKind>             mCross;
};

class GAXSK {
public:
    
    GAXSK(const GAXSK &) = delete;
    GAXSK();
    ~GAXSK();
    
    GAXSK &operator=(const GAXSK &) = delete;
    
    static bool                             RotationsClash_64_N(int pRotationA,
                                                                int pRotationB,
                                                                int pMinimumDistance);
    static bool                             RotationsClash_64_N(const std::vector<int> &pRotations,
                                                                int pMinimumDistance);
    
    static bool                             RotationsClash_64_2(int pRotationA, int pRotationB);
    static bool                             RotationsClash_64_2(const std::vector<int> &pRotations);
    
    static bool                             RotationsClash_64_8(int pRotationA, int pRotationB);
    static bool                             RotationsClash_64_8(const std::vector<int> &pRotations);
    
    static bool                             RotationsClash_64_12(int pRotationA, int pRotationB);
    static bool                             RotationsClash_64_12(const std::vector<int> &pRotations);
    
    
    static bool                             ChooseUpdateRotations(int pCount,
                                                                  int pMinimumDistance,
                                                                  bool pAllowEvenRotation,
                                                                  std::vector<int> *pResult,
                                                                  std::string *pErrorMessage);
    
    
    void                                    Reset();
    bool                                    Bake(GAXSFormat pFormat,
                                                 bool pIgnoreNonces,
                                                 std::vector<int> pLaneCounts,
                                                 std::vector<GAXSKSourceLayout> pSourceLayouts,
                                                 bool pHasDomainMix,
                                                 GAssignType pAssignType,
                                                 std::vector<GAXSKSkeleton> *pResult,
                                                 std::string *pErrorMessage);

    bool                                    Bake(GAXSFormat pFormat,
                                                 bool pIgnoreNonces,
                                                 std::vector<int> pLaneCounts,
                                                 bool pHasDomainMix,
                                                 GAssignType pAssignType,
                                                 std::vector<GAXSKSkeleton> *pResult,
                                                 std::string *pErrorMessage);
    
    bool                                    GetPassCount(int *pResult, std::string *pErrorMessage) const;
    bool                                    GetOrbiterCount(int *pResult, std::string *pErrorMessage) const;
    bool                                    GetWandererCount(int *pResult, std::string *pErrorMessage) const;
    
    static int                              GetIndexForOrbiter(GAXSKVariable pOrbiter);
    static bool                             AreOrbitersAdjacent(GAXSKVariable pOrbiterA,
                                                                GAXSKVariable pOrbiterB);
    
    
    bool                                    GetLaneCountForPass(int pPassIndex,
                                                                int *pResult,
                                                                std::string *pErrorMessage) const;
    
    bool                                    MakeIngressCrushStatement(GAXSKVariable pTarget,
                                                                      const std::vector<GAXSKVariable> &pOrbiters,
                                                                      GAXSKStatement *pResult,
                                                                      std::string *pErrorMessage);
    
    bool                                    MakeCarryMixStatement(const std::vector<GAXSKVariable> &pWanderers,
                                                                  GAXSKStatement *pResult,
                                                                  std::string *pErrorMessage);
    
    
    
    GAXSKStatement                          MakePreviousAssignStatement();
    
    GAXSKStatement                          MakeCommentStatement();
    
    GAXSKModel                              MakeModelForFormatPass(GAXSFormat pFormat,
                                                                   int pPassIndex);
    
    GAXSKStatement                          MakeContextWordStatement(GAXSKVariable pTarget,
                                                                     GAXSKDiffuseKind pDiffuse,
                                                                     bool pIsIngress);
    
    bool                                    MakeScatterMixStatement(GAXSKStatement *pResult,
                                                                    std::string *pErrorMessage);
    
    bool                                    MakeModelUpdateStatement(const GAXSKModelStatement &pModelStatement,
                                                                     GAXSKStatement *pResult,
                                                                     std::string *pErrorMessage);
    
    
    bool                                    InfuseUpdateRotationSlots(std::vector<GAXSKUpdateRotationSlot> *pSlots,
                                                                      GAXSKUpdateRotationParityMode pParityMode,
                                                                      std::string *pErrorMessage);
    
    
    bool                                    BuildSkeletonForLaneCount(int pPassIndex,
                                                                      int pLaneCount,
                                                                      GAXSKSkeleton *pSkeleton,
                                                                      std::string *pErrorMessage);
    
    
    bool                                    FinishModelStatements(const GAXSKModel &pModel,
                                                                  std::vector<GAXSKStatement> *pStatements,
                                                                  std::string *pErrorMessage);
    
    
    GAXSFormat                              mFormat = GAXSFormat::kInvalid;
    bool                                    mHasDomainMix = false;
    std::vector<GAXSKPool *>                mPools;
    std::vector<int>                        mLaneCounts;
    
};

#endif /* GAXSK_hpp */
