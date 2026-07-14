//
//  TwistWorkSpace.hpp
//  Gorgon
//

#ifndef TwistWorkSpace_hpp
#define TwistWorkSpace_hpp

#include <cstdint>
#include <vector>

#define S_BLOCK 32768 // 4,096 // 2,048
#define S_BLOCK1 (S_BLOCK - 1U)

#define S_QUARTER (S_BLOCK >> 2U)
#define S_QUARTER1 (S_QUARTER - 1U)

#define S_SALT 32
#define S_SALT_DIVIDE_BITSHIFT 5


#define S_SBOX1 255
#define S_SALT1 31

#define W_KEY 2048
#define W_KEY1 2047
#define H_KEY 8
#define S_KEY (W_KEY * H_KEY)

class TwistExpander;

enum class TwistDomain : std::uint8_t {
    kInvalid = 0,
    kPhaseA,
    kPhaseB,
    kPhaseC,
    kPhaseD,
    kPhaseE,
    kPhaseF,
    kPhaseG,
    kPhaseH,
};

enum class TwistWorkSpaceSlot : std::uint16_t;

enum class TwistBufferKind : std::uint8_t {
    kInvalid = 0,
    kSalt = 2,
    kSBox = 3,
    kConstants = 4
};

enum class TwistSBoxLane : std::uint16_t {
    kInvalid = 0,
    kA = 1,
    kB = 2,
    kC = 3,
    kD = 4,
    kE = 5,
    kF = 6,
    kG = 7,
    kH = 8
};

enum class TwistSaltOwner : std::uint16_t {
    kInvalid = 0,
    kInbuilt = 2,
    kEphemeral = 3
};

enum class TwistSBoxOwner : std::uint16_t {
    kInvalid = 0,
    kInbuilt = 2,
    kEphemeral = 3
};

struct TwistBufferKey {
    TwistBufferKind                          mKind = TwistBufferKind::kInvalid;
    TwistDomain                              mDomain = TwistDomain::kInvalid;
    std::uint16_t                            mSlot = 255U;
    
    TwistSaltOwner                           mSaltOwner = TwistSaltOwner::kInvalid;
    TwistSBoxOwner                           mSBoxOwner = TwistSBoxOwner::kInvalid;
    TwistSBoxLane                            mSBoxLane = TwistSBoxLane::kInvalid;

    static TwistBufferKey                    Salt(TwistSaltOwner pOwner,
                                                  TwistDomain pDomain,
                                                  TwistWorkSpaceSlot pSlot);
    
    static TwistBufferKey                    Constants(TwistSaltOwner pOwner,
                                                       TwistDomain pDomain);

    bool                                     IsValid() const;
    bool                                     IsSalt() const;
    bool                                     IsConstants() const;
};

enum class TwistWorkSpaceSlot : std::uint16_t {
    
    kInvalid=255,
    
    kSource=0, // workspace-owned source block
    kParamSource=2,
    kParamDestination=3,
    kParamSnow=4,
    
    kExpansionLaneA=80,
    kExpansionLaneB=81,
    kExpansionLaneC=82,
    kExpansionLaneD=83,

    kWorkLaneA=90,
    kWorkLaneB=91,
    kWorkLaneC=92,
    kWorkLaneD=93,

    kOperationLaneA=100,
    kOperationLaneB=101,
    kOperationLaneC=102,
    kOperationLaneD=103,

    kSnowLaneA=106,
    kSnowLaneB=107,
    kSnowLaneC=108,
    kSnowLaneD=109,

    kFireLaneA=110,
    kFireLaneB=111,
    kFireLaneC=112,
    kFireLaneD=113,

    kWaterLaneA=114,
    kWaterLaneB=115,
    kWaterLaneC=116,
    kWaterLaneD=117,

    kEarthLaneA=140,
    kEarthLaneB=141,
    kEarthLaneC=142,
    kEarthLaneD=143,

    kWindLaneA=144,
    kWindLaneB=145,
    kWindLaneC=146,
    kWindLaneD=147,

    kFuseLaneA=148,
    kFuseLaneB=149,
    kFuseLaneC=150,
    kFuseLaneD=151,

    kScrapLaneA=152,
    kScrapLaneB=153,
    kScrapLaneC=154,
    kScrapLaneD=155,

    kMergeLaneA=156,
    kMergeLaneB=157,
    kMergeLaneC=158,
    kMergeLaneD=159,

    kInvestA=130,
    kInvestB=131,
    kInvestC=132,
    kInvestD=133,
    kInvestE=134,
    kInvestF=135,
    kInvestG=136,
    kInvestH=137,
    
    
    // These are confusing.
    // 1.) We "seed" into entire box, e.g. "kKeyBoxUnrolledA" or "kKeyBoxUnrolledB"
    // 2.) We "read", in a twist, from "kKeyRowReadA" or "kKeyRowReadB", which is the 'last row'.
    // 3.) Before writing, we Shift, evicting last row and duplicating first row
    // 4.) We "write", after a twist, from "kKeyRowWriteA" or "kKeyRowWriteB", which is the 'first row'.
    
    kKeyBoxUnrolledA=120, // size is S_KEY
    kKeyBoxUnrolledB=121, // size is S_KEY
    kKeyRowReadA=122, // size is W_KEY
    kKeyRowReadB=123, // size is W_KEY
    kKeyRowWriteA=124, // size is W_KEY
    kKeyRowWriteB=125, // size is W_KEY

    kParamDomainSaltOrbiterAssignA=170,
    kParamDomainSaltOrbiterAssignB=171,
    kParamDomainSaltOrbiterAssignC=172,
    kParamDomainSaltOrbiterAssignD=173,
    kParamDomainSaltOrbiterAssignE=174,
    kParamDomainSaltOrbiterAssignF=175,

    kParamDomainSaltOrbiterUpdateA=176,
    kParamDomainSaltOrbiterUpdateB=177,
    kParamDomainSaltOrbiterUpdateC=178,
    kParamDomainSaltOrbiterUpdateD=179,
    kParamDomainSaltOrbiterUpdateE=180,
    kParamDomainSaltOrbiterUpdateF=181,

    kParamDomainSaltWandererUpdateA=182,
    kParamDomainSaltWandererUpdateB=183,
    kParamDomainSaltWandererUpdateC=184,
    kParamDomainSaltWandererUpdateD=185,
    kParamDomainSaltWandererUpdateE=186,
    kParamDomainSaltWandererUpdateF=187,

    kIndexList256A=190,
    kIndexList256B=191,
    kIndexList256C=192,
    kIndexList256D=193,

    kPhaseASaltOrbiterAssignA=300,
    kPhaseASaltOrbiterAssignB,
    kPhaseASaltOrbiterAssignC,
    kPhaseASaltOrbiterAssignD,
    kPhaseASaltOrbiterAssignE,
    kPhaseASaltOrbiterAssignF,
    kPhaseASaltOrbiterUpdateA,
    kPhaseASaltOrbiterUpdateB,
    kPhaseASaltOrbiterUpdateC,
    kPhaseASaltOrbiterUpdateD,
    kPhaseASaltOrbiterUpdateE,
    kPhaseASaltOrbiterUpdateF,
    kPhaseASaltWandererUpdateA,
    kPhaseASaltWandererUpdateB,
    kPhaseASaltWandererUpdateC,
    kPhaseASaltWandererUpdateD,
    kPhaseASaltWandererUpdateE,
    kPhaseASaltWandererUpdateF,

    kPhaseBSaltOrbiterAssignA=318,
    kPhaseBSaltOrbiterAssignB,
    kPhaseBSaltOrbiterAssignC,
    kPhaseBSaltOrbiterAssignD,
    kPhaseBSaltOrbiterAssignE,
    kPhaseBSaltOrbiterAssignF,
    kPhaseBSaltOrbiterUpdateA,
    kPhaseBSaltOrbiterUpdateB,
    kPhaseBSaltOrbiterUpdateC,
    kPhaseBSaltOrbiterUpdateD,
    kPhaseBSaltOrbiterUpdateE,
    kPhaseBSaltOrbiterUpdateF,
    kPhaseBSaltWandererUpdateA,
    kPhaseBSaltWandererUpdateB,
    kPhaseBSaltWandererUpdateC,
    kPhaseBSaltWandererUpdateD,
    kPhaseBSaltWandererUpdateE,
    kPhaseBSaltWandererUpdateF,

    kPhaseCSaltOrbiterAssignA=336,
    kPhaseCSaltOrbiterAssignB,
    kPhaseCSaltOrbiterAssignC,
    kPhaseCSaltOrbiterAssignD,
    kPhaseCSaltOrbiterAssignE,
    kPhaseCSaltOrbiterAssignF,
    kPhaseCSaltOrbiterUpdateA,
    kPhaseCSaltOrbiterUpdateB,
    kPhaseCSaltOrbiterUpdateC,
    kPhaseCSaltOrbiterUpdateD,
    kPhaseCSaltOrbiterUpdateE,
    kPhaseCSaltOrbiterUpdateF,
    kPhaseCSaltWandererUpdateA,
    kPhaseCSaltWandererUpdateB,
    kPhaseCSaltWandererUpdateC,
    kPhaseCSaltWandererUpdateD,
    kPhaseCSaltWandererUpdateE,
    kPhaseCSaltWandererUpdateF,

    kPhaseDSaltOrbiterAssignA=354,
    kPhaseDSaltOrbiterAssignB,
    kPhaseDSaltOrbiterAssignC,
    kPhaseDSaltOrbiterAssignD,
    kPhaseDSaltOrbiterAssignE,
    kPhaseDSaltOrbiterAssignF,
    kPhaseDSaltOrbiterUpdateA,
    kPhaseDSaltOrbiterUpdateB,
    kPhaseDSaltOrbiterUpdateC,
    kPhaseDSaltOrbiterUpdateD,
    kPhaseDSaltOrbiterUpdateE,
    kPhaseDSaltOrbiterUpdateF,
    kPhaseDSaltWandererUpdateA,
    kPhaseDSaltWandererUpdateB,
    kPhaseDSaltWandererUpdateC,
    kPhaseDSaltWandererUpdateD,
    kPhaseDSaltWandererUpdateE,
    kPhaseDSaltWandererUpdateF,

    kPhaseESaltOrbiterAssignA=372,
    kPhaseESaltOrbiterAssignB,
    kPhaseESaltOrbiterAssignC,
    kPhaseESaltOrbiterAssignD,
    kPhaseESaltOrbiterAssignE,
    kPhaseESaltOrbiterAssignF,
    kPhaseESaltOrbiterUpdateA,
    kPhaseESaltOrbiterUpdateB,
    kPhaseESaltOrbiterUpdateC,
    kPhaseESaltOrbiterUpdateD,
    kPhaseESaltOrbiterUpdateE,
    kPhaseESaltOrbiterUpdateF,
    kPhaseESaltWandererUpdateA,
    kPhaseESaltWandererUpdateB,
    kPhaseESaltWandererUpdateC,
    kPhaseESaltWandererUpdateD,
    kPhaseESaltWandererUpdateE,
    kPhaseESaltWandererUpdateF,

    kPhaseFSaltOrbiterAssignA=390,
    kPhaseFSaltOrbiterAssignB,
    kPhaseFSaltOrbiterAssignC,
    kPhaseFSaltOrbiterAssignD,
    kPhaseFSaltOrbiterAssignE,
    kPhaseFSaltOrbiterAssignF,
    kPhaseFSaltOrbiterUpdateA,
    kPhaseFSaltOrbiterUpdateB,
    kPhaseFSaltOrbiterUpdateC,
    kPhaseFSaltOrbiterUpdateD,
    kPhaseFSaltOrbiterUpdateE,
    kPhaseFSaltOrbiterUpdateF,
    kPhaseFSaltWandererUpdateA,
    kPhaseFSaltWandererUpdateB,
    kPhaseFSaltWandererUpdateC,
    kPhaseFSaltWandererUpdateD,
    kPhaseFSaltWandererUpdateE,
    kPhaseFSaltWandererUpdateF,

    kPhaseGSaltOrbiterAssignA=408,
    kPhaseGSaltOrbiterAssignB,
    kPhaseGSaltOrbiterAssignC,
    kPhaseGSaltOrbiterAssignD,
    kPhaseGSaltOrbiterAssignE,
    kPhaseGSaltOrbiterAssignF,
    kPhaseGSaltOrbiterUpdateA,
    kPhaseGSaltOrbiterUpdateB,
    kPhaseGSaltOrbiterUpdateC,
    kPhaseGSaltOrbiterUpdateD,
    kPhaseGSaltOrbiterUpdateE,
    kPhaseGSaltOrbiterUpdateF,
    kPhaseGSaltWandererUpdateA,
    kPhaseGSaltWandererUpdateB,
    kPhaseGSaltWandererUpdateC,
    kPhaseGSaltWandererUpdateD,
    kPhaseGSaltWandererUpdateE,
    kPhaseGSaltWandererUpdateF,

    kPhaseHSaltOrbiterAssignA=426,
    kPhaseHSaltOrbiterAssignB,
    kPhaseHSaltOrbiterAssignC,
    kPhaseHSaltOrbiterAssignD,
    kPhaseHSaltOrbiterAssignE,
    kPhaseHSaltOrbiterAssignF,
    kPhaseHSaltOrbiterUpdateA,
    kPhaseHSaltOrbiterUpdateB,
    kPhaseHSaltOrbiterUpdateC,
    kPhaseHSaltOrbiterUpdateD,
    kPhaseHSaltOrbiterUpdateE,
    kPhaseHSaltOrbiterUpdateF,
    kPhaseHSaltWandererUpdateA,
    kPhaseHSaltWandererUpdateB,
    kPhaseHSaltWandererUpdateC,
    kPhaseHSaltWandererUpdateD,
    kPhaseHSaltWandererUpdateE,
    kPhaseHSaltWandererUpdateF,
    
};

struct TwistDomainConstants {
public:
    
    std::uint64_t                           mIngress;
    std::uint64_t                           mScatter;
    std::uint64_t                           mCross;

    std::uint64_t                           mDomainConstantPublicIngress;
    std::uint64_t                           mDomainConstantPrivateIngress;
    std::uint64_t                           mDomainConstantCrossIngress;
    
    std::uint64_t                           mMatrixSelectA;
    std::uint64_t                           mMatrixSelectB;
    
    std::uint8_t                            mMatrixUnrollA;
    std::uint8_t                            mMatrixUnrollB;
    
    std::uint8_t                            mMatrixArgA;
    std::uint8_t                            mMatrixArgB;
    std::uint8_t                            mMatrixArgC;
    std::uint8_t                            mMatrixArgD;
    
    std::uint8_t                            mMaskMutateA;
    std::uint8_t                            mMaskMutateB;
    
    void                                    Zero() {
        mIngress = 0; mScatter = 0; mCross = 0;
        mDomainConstantPublicIngress = 0; mDomainConstantPrivateIngress = 0; mDomainConstantCrossIngress = 0;
        mMatrixSelectA = 0; mMatrixSelectB = 0;
        mMatrixUnrollA = 0; mMatrixUnrollB = 0;
        mMatrixArgA = 0; mMatrixArgB = 0; mMatrixArgC = 0; mMatrixArgD = 0;
        mMaskMutateA = 0; mMaskMutateB = 0;
    }
    
};

struct TwistDomainSeedRoundMaterial {
public:
    std::uint64_t                           mSaltA[S_SALT];
    std::uint64_t                           mSaltB[S_SALT];
    std::uint64_t                           mSaltC[S_SALT];
    std::uint64_t                           mSaltD[S_SALT];
    std::uint64_t                           mSaltE[S_SALT];
    std::uint64_t                           mSaltF[S_SALT];
    
    void                                    Zero() {
        memset(mSaltA, 0, sizeof(mSaltA));
        memset(mSaltB, 0, sizeof(mSaltB));
        memset(mSaltC, 0, sizeof(mSaltC));
        memset(mSaltD, 0, sizeof(mSaltD));
        memset(mSaltE, 0, sizeof(mSaltE));
        memset(mSaltF, 0, sizeof(mSaltF));
    }
    
};

class TwistDomainSaltSet {
public:
    TwistDomainSeedRoundMaterial            mOrbiterAssign;
    TwistDomainSeedRoundMaterial            mOrbiterUpdate;
    TwistDomainSeedRoundMaterial            mWandererUpdate;
    
    void                                    Zero() {
        mOrbiterAssign.Zero();
        mOrbiterUpdate.Zero();
        mWandererUpdate.Zero();
    }
    
};

class TwistDomainBundle {
public:
    TwistDomainSaltSet                      mPhaseASalts;
    TwistDomainConstants                    mPhaseAConstants;

    TwistDomainSaltSet                      mPhaseBSalts;
    TwistDomainConstants                    mPhaseBConstants;

    TwistDomainSaltSet                      mPhaseCSalts;
    TwistDomainConstants                    mPhaseCConstants;

    TwistDomainSaltSet                      mPhaseDSalts;
    TwistDomainConstants                    mPhaseDConstants;

    TwistDomainSaltSet                      mPhaseESalts;
    TwistDomainConstants                    mPhaseEConstants;

    TwistDomainSaltSet                      mPhaseFSalts;
    TwistDomainConstants                    mPhaseFConstants;

    TwistDomainSaltSet                      mPhaseGSalts;
    TwistDomainConstants                    mPhaseGConstants;

    TwistDomainSaltSet                      mPhaseHSalts;
    TwistDomainConstants                    mPhaseHConstants;
    
    void                                    Zero() {
        mPhaseASalts.Zero();
        mPhaseAConstants.Zero();
        
        mPhaseBSalts.Zero();
        mPhaseBConstants.Zero();

        mPhaseCSalts.Zero();
        mPhaseCConstants.Zero();

        mPhaseDSalts.Zero();
        mPhaseDConstants.Zero();

        mPhaseESalts.Zero();
        mPhaseEConstants.Zero();

        mPhaseFSalts.Zero();
        mPhaseFConstants.Zero();

        mPhaseGSalts.Zero();
        mPhaseGConstants.Zero();

        mPhaseHSalts.Zero();
        mPhaseHConstants.Zero();
        
    }
    
};


class TwistWorkSpace {
    
public:
    TwistWorkSpace();

    uint8_t                                 mKeyBoxA[H_KEY][W_KEY];
    uint8_t                                 mKeyBoxB[H_KEY][W_KEY];

    std::uint8_t                            mSource[S_BLOCK];

    std::uint8_t                            mExpansionLaneA[S_BLOCK];
    std::uint8_t                            mExpansionLaneB[S_BLOCK];
    std::uint8_t                            mExpansionLaneC[S_BLOCK];
    std::uint8_t                            mExpansionLaneD[S_BLOCK];

    std::uint8_t                            mWorkLaneA[S_BLOCK];
    std::uint8_t                            mWorkLaneB[S_BLOCK];
    std::uint8_t                            mWorkLaneC[S_BLOCK];
    std::uint8_t                            mWorkLaneD[S_BLOCK];

    std::uint8_t                            mOperationLaneA[S_BLOCK];
    std::uint8_t                            mOperationLaneB[S_BLOCK];
    std::uint8_t                            mOperationLaneC[S_BLOCK];
    std::uint8_t                            mOperationLaneD[S_BLOCK];

    std::uint8_t                            mSnowLaneA[S_BLOCK];
    std::uint8_t                            mSnowLaneB[S_BLOCK];
    std::uint8_t                            mSnowLaneC[S_BLOCK];
    std::uint8_t                            mSnowLaneD[S_BLOCK];

    std::uint8_t                            mFireLaneA[S_BLOCK];
    std::uint8_t                            mFireLaneB[S_BLOCK];
    std::uint8_t                            mFireLaneC[S_BLOCK];
    std::uint8_t                            mFireLaneD[S_BLOCK];
    
    std::uint8_t                            mWaterLaneA[S_BLOCK];
    std::uint8_t                            mWaterLaneB[S_BLOCK];
    std::uint8_t                            mWaterLaneC[S_BLOCK];
    std::uint8_t                            mWaterLaneD[S_BLOCK];
    
    std::uint8_t                            mEarthLaneA[S_BLOCK];
    std::uint8_t                            mEarthLaneB[S_BLOCK];
    std::uint8_t                            mEarthLaneC[S_BLOCK];
    std::uint8_t                            mEarthLaneD[S_BLOCK];
    
    std::uint8_t                            mWindLaneA[S_BLOCK];
    std::uint8_t                            mWindLaneB[S_BLOCK];
    std::uint8_t                            mWindLaneC[S_BLOCK];
    std::uint8_t                            mWindLaneD[S_BLOCK];

    std::uint8_t                            mFuseLaneA[S_BLOCK];
    std::uint8_t                            mFuseLaneB[S_BLOCK];
    std::uint8_t                            mFuseLaneC[S_BLOCK];
    std::uint8_t                            mFuseLaneD[S_BLOCK];

    std::uint8_t                            mScrapLaneA[S_BLOCK];
    std::uint8_t                            mScrapLaneB[S_BLOCK];
    std::uint8_t                            mScrapLaneC[S_BLOCK];
    std::uint8_t                            mScrapLaneD[S_BLOCK];

    std::uint8_t                            mMergeLaneA[S_QUARTER];
    std::uint8_t                            mMergeLaneB[S_QUARTER];
    std::uint8_t                            mMergeLaneC[S_QUARTER];
    std::uint8_t                            mMergeLaneD[S_QUARTER];
    
    std::uint8_t                            mInvestLaneA[S_BLOCK];
    std::uint8_t                            mInvestLaneB[S_BLOCK];
    std::uint8_t                            mInvestLaneC[S_BLOCK];
    std::uint8_t                            mInvestLaneD[S_BLOCK];

    std::uint8_t                            mInvestLaneE[S_BLOCK];
    std::uint8_t                            mInvestLaneF[S_BLOCK];
    std::uint8_t                            mInvestLaneG[S_BLOCK];
    std::uint8_t                            mInvestLaneH[S_BLOCK];


    TwistDomainBundle                       mDomainBundle;
    
    // Rotate stays byte-wide across the workspace helpers.
    static void                             ShiftKeyBoxA(std::uint8_t *pBox); //
    static void                             ShiftKeyBoxB(std::uint8_t *pBox); //
    
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkSpace,
                                                       TwistExpander *pExpander,
                                                       TwistWorkSpaceSlot pSlot);
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkSpace,
                                                       TwistWorkSpaceSlot pSlot);
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkSpace,
                                                       TwistExpander *pExpander,
                                                       TwistBufferKey pKey);
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkSpace,
                                                       TwistBufferKey pKey);
    
    static int                              GetBufferLength(TwistWorkSpaceSlot pSlot); //
    static int                              GetBufferLength(TwistBufferKey pKey);
    
    static bool                             IsSalt(TwistWorkSpaceSlot pSlot);
    static bool                             IsSalt(TwistBufferKey pKey);
    
    void                                    Zero_PostSeed();
    void                                    Zero();
    
};

#endif /* TwistWorkSpace_hpp */
