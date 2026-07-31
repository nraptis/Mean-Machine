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

#define S_HALF (S_BLOCK >> 1U)
#define S_HALF1 (S_HALF - 1U)

#define S_QUARTER (S_BLOCK >> 2U)
#define S_QUARTER1 (S_QUARTER - 1U)

#define S_EIGHTH (S_BLOCK >> 3U)
#define S_EIGHTH1 (S_EIGHTH - 1U)

#define S_SALT 512
#define S_SALT_DIVIDE_BITSHIFT 9

#define S_SALT1 511

static_assert((1U << S_SALT_DIVIDE_BITSHIFT) == S_SALT,
              "S_SALT_DIVIDE_BITSHIFT must describe S_SALT.");
static_assert((S_SALT & S_SALT1) == 0U,
              "S_SALT must be a power of two for masked salt indexing.");
static_assert(S_SALT1 == (S_SALT - 1U),
              "S_SALT1 must be the mask for S_SALT.");

#define W_KEY 2048
#define W_KEY1 2047
#define H_KEY 8
#define S_KEY (W_KEY * H_KEY)

class TwistExpander;

enum class TwistDomain : std::uint8_t {
    kInvalid = 0,
    // Keep the original serialized values stable for existing control assets.
    kKeyRotateA = 1,
    kKeySpawnA = 2,
    kSeed = 3,
    kTwist = 4,
    kKeyRotateB = 5,
    kKeySpawnB = 6,
};

enum class TwistWorkSpaceSlot : std::uint16_t;

enum class TwistBufferKind : std::uint8_t {
    kInvalid = 0,
    kSalt = 2,
    kSBox = 3,
    kConstants = 4,
    kLaneSplit = 5
};

enum class TwistSaltOwner : std::uint16_t {
    kInvalid = 0,
    kInbuilt = 2,
    kEphemeral = 3
};

struct TwistBufferKey {
    TwistBufferKind                          mKind = TwistBufferKind::kInvalid;
    TwistDomain                              mDomain = TwistDomain::kInvalid;
    std::uint16_t                            mSlot = 255U;
    std::uint8_t                             mLaneSplit = 255U;

    TwistSaltOwner                           mSaltOwner = TwistSaltOwner::kInvalid;

    static TwistBufferKey                    Salt(TwistSaltOwner pOwner,
                                                  TwistDomain pDomain,
                                                  TwistWorkSpaceSlot pSlot);

    static TwistBufferKey                    Constants(TwistSaltOwner pOwner,
                                                       TwistDomain pDomain);

    static TwistBufferKey                    LaneSplit(TwistWorkSpaceSlot pSlot,
                                                       std::uint8_t pLaneSplit);

    bool                                     IsValid() const;
    bool                                     IsSalt() const;
    bool                                     IsConstants() const;
    bool                                     IsLaneSplit() const;
};

enum class TwistWorkSpaceSlot : std::uint16_t {

    kInvalid=255,

    kSourceLane=0, // workspace-owned source lane
    kNonceLane=1,
    kParamSource=2,
    kParamDestination=3,

    kParamCrossA=8,
    kParamCrossB=9,
    kParamCrossC=10,
    kParamCrossD=11,
    
    
    kEarthLaneA=140,
    kEarthLaneB=141,
    kEarthLaneC=142,
    kEarthLaneD=143,
    
    kFireLaneA=110,
    kFireLaneB=111,
    kFireLaneC=112,
    kFireLaneD=113,

    kWindLaneA=144,
    kWindLaneB=145,
    kWindLaneC=146,
    kWindLaneD=147,
    
    kWaterLaneA=114,
    kWaterLaneB=115,
    kWaterLaneC=116,
    kWaterLaneD=117,

    kHeartLaneA=80,
    kHeartLaneB=81,
    kHeartLaneC=82,
    kHeartLaneD=83,

    kSoilLaneA=208,
    kSoilLaneB=209,
    kSoilLaneC=210,
    kSoilLaneD=211,
    
    kLightningLaneA=200,
    kLightningLaneB=201,
    kLightningLaneC=202,
    kLightningLaneD=203,
    
    kIceLaneA=130,
    kIceLaneB=131,
    kIceLaneC=132,
    kIceLaneD=133,
    
    kWoodLaneA=152,
    kWoodLaneB=153,
    kWoodLaneC=154,
    kWoodLaneD=155,

    kMagmaLaneA=204,
    kMagmaLaneB=205,
    kMagmaLaneC=206,
    kMagmaLaneD=207,

    kPlasmaLaneA=212,
    kPlasmaLaneB=213,
    kPlasmaLaneC=214,
    kPlasmaLaneD=215,

    kShadowLaneA=40,
    kShadowLaneB=41,
    kShadowLaneC=42,
    kShadowLaneD=43,

    kCrystalLaneA=44,
    kCrystalLaneB=45,
    kCrystalLaneC=46,
    kCrystalLaneD=47,

    kAetherLaneA=48,
    kAetherLaneB=49,
    kAetherLaneC=50,
    kAetherLaneD=51,

    kCelestialLaneA=52,
    kCelestialLaneB=53,
    kCelestialLaneC=54,
    kCelestialLaneD=55,

    kKineticLaneA=56,
    kKineticLaneB=57,
    kKineticLaneC=58,
    kKineticLaneD=59,

    kVaporLaneA=60,
    kVaporLaneB=61,
    kVaporLaneC=62,
    kVaporLaneD=63,

    kSpiritLaneA=100,
    kSpiritLaneB=101,
    kSpiritLaneC=102,
    kSpiritLaneD=103,
    
    kFuseLaneA=148,
    kFuseLaneB=149,
    kFuseLaneC=150,
    kFuseLaneD=151,

    


    // Rolling key-box views used by Seed, Twist, and Grow:
    // 1.) Seed addresses the entire box through kKeyBoxUnrolledA/B.
    // 2.) Twist and Grow read the oldest row through kKeyRowReadA/B.
    // 3.) Grow shifts the box, evicting the oldest row.
    // 4.) Grow writes the new first row through kKeyRowWriteA/B.

    kKeyBoxUnrolledA=120, // size is S_KEY
    kKeyBoxUnrolledB=121, // size is S_KEY
    kKeyRowReadA=122, // size is W_KEY
    kKeyRowReadB=123, // size is W_KEY
    kKeyRowWriteA=124, // size is W_KEY
    kKeyRowWriteB=125, // size is W_KEY

    // Direct row views used by full key-box transforms.
    kKeyRowA0=216, // size is W_KEY
    kKeyRowA1,
    kKeyRowA2,
    kKeyRowA3,
    kKeyRowA4,
    kKeyRowA5,
    kKeyRowA6,
    kKeyRowA7,

    kKeyRowB0=224, // size is W_KEY
    kKeyRowB1,
    kKeyRowB2,
    kKeyRowB3,
    kKeyRowB4,
    kKeyRowB5,
    kKeyRowB6,
    kKeyRowB7,

    kParamDomainSaltOrbiterAssignA=170,
    kParamDomainSaltOrbiterAssignB=171,
    kParamDomainSaltOrbiterAssignC=172,
    kParamDomainSaltOrbiterAssignD=173,
    kParamDomainSaltOrbiterAssignE=174,
    kParamDomainSaltOrbiterAssignF=175,
    kParamDomainSaltOrbiterAssignG=176,
    kParamDomainSaltOrbiterAssignH=177,

    kParamDomainSaltOrbiterUpdateA=178,
    kParamDomainSaltOrbiterUpdateB=179,
    kParamDomainSaltOrbiterUpdateC=180,
    kParamDomainSaltOrbiterUpdateD=181,
    kParamDomainSaltOrbiterUpdateE=182,
    kParamDomainSaltOrbiterUpdateF=183,
    kParamDomainSaltOrbiterUpdateG=184,
    kParamDomainSaltOrbiterUpdateH=185,

    kParamDomainSaltWandererUpdateA=186,
    kParamDomainSaltWandererUpdateB=187,
    kParamDomainSaltWandererUpdateC=188,
    kParamDomainSaltWandererUpdateD=189,
    kParamDomainSaltWandererUpdateE=190,
    kParamDomainSaltWandererUpdateF=191,
    kParamDomainSaltWandererUpdateG=192,
    kParamDomainSaltWandererUpdateH=193,

    kIndexList256A=194,
    kIndexList256B=195,
    kIndexList256C=196,
    kIndexList256D=197,

    kKeyRotateASaltOrbiterAssignA=300,
    kKeyRotateASaltOrbiterAssignB,
    kKeyRotateASaltOrbiterAssignC,
    kKeyRotateASaltOrbiterAssignD,
    kKeyRotateASaltOrbiterAssignE,
    kKeyRotateASaltOrbiterAssignF,
    kKeyRotateASaltOrbiterAssignG,
    kKeyRotateASaltOrbiterAssignH,
    kKeyRotateASaltOrbiterUpdateA,
    kKeyRotateASaltOrbiterUpdateB,
    kKeyRotateASaltOrbiterUpdateC,
    kKeyRotateASaltOrbiterUpdateD,
    kKeyRotateASaltOrbiterUpdateE,
    kKeyRotateASaltOrbiterUpdateF,
    kKeyRotateASaltOrbiterUpdateG,
    kKeyRotateASaltOrbiterUpdateH,
    kKeyRotateASaltWandererUpdateA,
    kKeyRotateASaltWandererUpdateB,
    kKeyRotateASaltWandererUpdateC,
    kKeyRotateASaltWandererUpdateD,
    kKeyRotateASaltWandererUpdateE,
    kKeyRotateASaltWandererUpdateF,
    kKeyRotateASaltWandererUpdateG,
    kKeyRotateASaltWandererUpdateH,

    kKeySpawnASaltOrbiterAssignA=324,
    kKeySpawnASaltOrbiterAssignB,
    kKeySpawnASaltOrbiterAssignC,
    kKeySpawnASaltOrbiterAssignD,
    kKeySpawnASaltOrbiterAssignE,
    kKeySpawnASaltOrbiterAssignF,
    kKeySpawnASaltOrbiterAssignG,
    kKeySpawnASaltOrbiterAssignH,
    kKeySpawnASaltOrbiterUpdateA,
    kKeySpawnASaltOrbiterUpdateB,
    kKeySpawnASaltOrbiterUpdateC,
    kKeySpawnASaltOrbiterUpdateD,
    kKeySpawnASaltOrbiterUpdateE,
    kKeySpawnASaltOrbiterUpdateF,
    kKeySpawnASaltOrbiterUpdateG,
    kKeySpawnASaltOrbiterUpdateH,
    kKeySpawnASaltWandererUpdateA,
    kKeySpawnASaltWandererUpdateB,
    kKeySpawnASaltWandererUpdateC,
    kKeySpawnASaltWandererUpdateD,
    kKeySpawnASaltWandererUpdateE,
    kKeySpawnASaltWandererUpdateF,
    kKeySpawnASaltWandererUpdateG,
    kKeySpawnASaltWandererUpdateH,

    kSeedSaltOrbiterAssignA=348,
    kSeedSaltOrbiterAssignB,
    kSeedSaltOrbiterAssignC,
    kSeedSaltOrbiterAssignD,
    kSeedSaltOrbiterAssignE,
    kSeedSaltOrbiterAssignF,
    kSeedSaltOrbiterAssignG,
    kSeedSaltOrbiterAssignH,
    kSeedSaltOrbiterUpdateA,
    kSeedSaltOrbiterUpdateB,
    kSeedSaltOrbiterUpdateC,
    kSeedSaltOrbiterUpdateD,
    kSeedSaltOrbiterUpdateE,
    kSeedSaltOrbiterUpdateF,
    kSeedSaltOrbiterUpdateG,
    kSeedSaltOrbiterUpdateH,
    kSeedSaltWandererUpdateA,
    kSeedSaltWandererUpdateB,
    kSeedSaltWandererUpdateC,
    kSeedSaltWandererUpdateD,
    kSeedSaltWandererUpdateE,
    kSeedSaltWandererUpdateF,
    kSeedSaltWandererUpdateG,
    kSeedSaltWandererUpdateH,

    kTwistSaltOrbiterAssignA=372,
    kTwistSaltOrbiterAssignB,
    kTwistSaltOrbiterAssignC,
    kTwistSaltOrbiterAssignD,
    kTwistSaltOrbiterAssignE,
    kTwistSaltOrbiterAssignF,
    kTwistSaltOrbiterAssignG,
    kTwistSaltOrbiterAssignH,
    kTwistSaltOrbiterUpdateA,
    kTwistSaltOrbiterUpdateB,
    kTwistSaltOrbiterUpdateC,
    kTwistSaltOrbiterUpdateD,
    kTwistSaltOrbiterUpdateE,
    kTwistSaltOrbiterUpdateF,
    kTwistSaltOrbiterUpdateG,
    kTwistSaltOrbiterUpdateH,
    kTwistSaltWandererUpdateA,
    kTwistSaltWandererUpdateB,
    kTwistSaltWandererUpdateC,
    kTwistSaltWandererUpdateD,
    kTwistSaltWandererUpdateE,
    kTwistSaltWandererUpdateF,
    kTwistSaltWandererUpdateG,
    kTwistSaltWandererUpdateH,

    kKeyRotateBSaltOrbiterAssignA=396,
    kKeyRotateBSaltOrbiterAssignB,
    kKeyRotateBSaltOrbiterAssignC,
    kKeyRotateBSaltOrbiterAssignD,
    kKeyRotateBSaltOrbiterAssignE,
    kKeyRotateBSaltOrbiterAssignF,
    kKeyRotateBSaltOrbiterAssignG,
    kKeyRotateBSaltOrbiterAssignH,
    kKeyRotateBSaltOrbiterUpdateA,
    kKeyRotateBSaltOrbiterUpdateB,
    kKeyRotateBSaltOrbiterUpdateC,
    kKeyRotateBSaltOrbiterUpdateD,
    kKeyRotateBSaltOrbiterUpdateE,
    kKeyRotateBSaltOrbiterUpdateF,
    kKeyRotateBSaltOrbiterUpdateG,
    kKeyRotateBSaltOrbiterUpdateH,
    kKeyRotateBSaltWandererUpdateA,
    kKeyRotateBSaltWandererUpdateB,
    kKeyRotateBSaltWandererUpdateC,
    kKeyRotateBSaltWandererUpdateD,
    kKeyRotateBSaltWandererUpdateE,
    kKeyRotateBSaltWandererUpdateF,
    kKeyRotateBSaltWandererUpdateG,
    kKeyRotateBSaltWandererUpdateH,

    kKeySpawnBSaltOrbiterAssignA=420,
    kKeySpawnBSaltOrbiterAssignB,
    kKeySpawnBSaltOrbiterAssignC,
    kKeySpawnBSaltOrbiterAssignD,
    kKeySpawnBSaltOrbiterAssignE,
    kKeySpawnBSaltOrbiterAssignF,
    kKeySpawnBSaltOrbiterAssignG,
    kKeySpawnBSaltOrbiterAssignH,
    kKeySpawnBSaltOrbiterUpdateA,
    kKeySpawnBSaltOrbiterUpdateB,
    kKeySpawnBSaltOrbiterUpdateC,
    kKeySpawnBSaltOrbiterUpdateD,
    kKeySpawnBSaltOrbiterUpdateE,
    kKeySpawnBSaltOrbiterUpdateF,
    kKeySpawnBSaltOrbiterUpdateG,
    kKeySpawnBSaltOrbiterUpdateH,
    kKeySpawnBSaltWandererUpdateA,
    kKeySpawnBSaltWandererUpdateB,
    kKeySpawnBSaltWandererUpdateC,
    kKeySpawnBSaltWandererUpdateD,
    kKeySpawnBSaltWandererUpdateE,
    kKeySpawnBSaltWandererUpdateF,
    kKeySpawnBSaltWandererUpdateG,
    kKeySpawnBSaltWandererUpdateH,

};

struct TwistDomainConstants {
public:

    std::uint64_t                           mIngress;
    std::uint64_t                           mScatter;
    std::uint64_t                           mCross;

    std::uint64_t                           mMatrixSelectA;
    std::uint64_t                           mMatrixSelectB;

    std::uint8_t                            mMatrixUnrollA;
    std::uint8_t                            mMatrixUnrollB;

    std::uint8_t                            mMatrixArgA;
    std::uint8_t                            mMatrixArgB;
    std::uint8_t                            mMatrixArgC;
    std::uint8_t                            mMatrixArgD;

    void                                    Zero() {
        mIngress = 0; mScatter = 0; mCross = 0;
        mMatrixSelectA = 0; mMatrixSelectB = 0;
        mMatrixUnrollA = 0; mMatrixUnrollB = 0;
        mMatrixArgA = 0; mMatrixArgB = 0; mMatrixArgC = 0; mMatrixArgD = 0;
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
    std::uint64_t                           mSaltG[S_SALT];
    std::uint64_t                           mSaltH[S_SALT];

    void                                    Zero() {
        memset(mSaltA, 0, sizeof(mSaltA));
        memset(mSaltB, 0, sizeof(mSaltB));
        memset(mSaltC, 0, sizeof(mSaltC));
        memset(mSaltD, 0, sizeof(mSaltD));
        memset(mSaltE, 0, sizeof(mSaltE));
        memset(mSaltF, 0, sizeof(mSaltF));
        memset(mSaltG, 0, sizeof(mSaltG));
        memset(mSaltH, 0, sizeof(mSaltH));
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
    TwistDomainSaltSet                      mKeyRotateASalts;
    TwistDomainConstants                    mKeyRotateAConstants;

    TwistDomainSaltSet                      mKeyRotateBSalts;
    TwistDomainConstants                    mKeyRotateBConstants;

    TwistDomainSaltSet                      mKeySpawnASalts;
    TwistDomainConstants                    mKeySpawnAConstants;

    TwistDomainSaltSet                      mKeySpawnBSalts;
    TwistDomainConstants                    mKeySpawnBConstants;

    TwistDomainSaltSet                      mSeedSalts;
    TwistDomainConstants                    mSeedConstants;

    TwistDomainSaltSet                      mTwistSalts;
    TwistDomainConstants                    mTwistConstants;

    void                                    Zero() {
        mKeyRotateASalts.Zero();
        mKeyRotateAConstants.Zero();

        mKeyRotateBSalts.Zero();
        mKeyRotateBConstants.Zero();

        mKeySpawnASalts.Zero();
        mKeySpawnAConstants.Zero();

        mKeySpawnBSalts.Zero();
        mKeySpawnBConstants.Zero();

        mSeedSalts.Zero();
        mSeedConstants.Zero();

        mTwistSalts.Zero();
        mTwistConstants.Zero();

    }

};


class TwistWorkSpace {

public:
    TwistWorkSpace();

    alignas(std::uint32_t) uint8_t          mKeyBoxA[H_KEY][W_KEY];
    alignas(std::uint32_t) uint8_t          mKeyBoxB[H_KEY][W_KEY];

    std::uint8_t                            mSourceLane[S_BLOCK];
    std::uint8_t                            mNonceLane[S_BLOCK];

    std::size_t                             mIndexList256A[256];
    std::size_t                             mIndexList256B[256];
    std::size_t                             mIndexList256C[256];
    std::size_t                             mIndexList256D[256];

    std::uint8_t                            mEarthLaneA[S_BLOCK];
    std::uint8_t                            mEarthLaneB[S_BLOCK];
    std::uint8_t                            mEarthLaneC[S_BLOCK];
    std::uint8_t                            mEarthLaneD[S_BLOCK];
    
    std::uint8_t                            mFireLaneA[S_BLOCK];
    std::uint8_t                            mFireLaneB[S_BLOCK];
    std::uint8_t                            mFireLaneC[S_BLOCK];
    std::uint8_t                            mFireLaneD[S_BLOCK];

    std::uint8_t                            mWindLaneA[S_BLOCK];
    std::uint8_t                            mWindLaneB[S_BLOCK];
    std::uint8_t                            mWindLaneC[S_BLOCK];
    std::uint8_t                            mWindLaneD[S_BLOCK];
    
    std::uint8_t                            mWaterLaneA[S_BLOCK];
    std::uint8_t                            mWaterLaneB[S_BLOCK];
    std::uint8_t                            mWaterLaneC[S_BLOCK];
    std::uint8_t                            mWaterLaneD[S_BLOCK];
    
    std::uint8_t                            mHeartLaneA[S_BLOCK];
    std::uint8_t                            mHeartLaneB[S_BLOCK];
    std::uint8_t                            mHeartLaneC[S_BLOCK];
    std::uint8_t                            mHeartLaneD[S_BLOCK];

    std::uint8_t                            mSoilLaneA[S_BLOCK];
    std::uint8_t                            mSoilLaneB[S_BLOCK];
    std::uint8_t                            mSoilLaneC[S_BLOCK];
    std::uint8_t                            mSoilLaneD[S_BLOCK];
    
    std::uint8_t                            mLightningLaneA[S_BLOCK];
    std::uint8_t                            mLightningLaneB[S_BLOCK];
    std::uint8_t                            mLightningLaneC[S_BLOCK];
    std::uint8_t                            mLightningLaneD[S_BLOCK];
    
    std::uint8_t                            mIceLaneA[S_BLOCK];
    std::uint8_t                            mIceLaneB[S_BLOCK];
    std::uint8_t                            mIceLaneC[S_BLOCK];
    std::uint8_t                            mIceLaneD[S_BLOCK];
    
    std::uint8_t                            mWoodLaneA[S_BLOCK];
    std::uint8_t                            mWoodLaneB[S_BLOCK];
    std::uint8_t                            mWoodLaneC[S_BLOCK];
    std::uint8_t                            mWoodLaneD[S_BLOCK];
    
    std::uint8_t                            mMagmaLaneA[S_BLOCK];
    std::uint8_t                            mMagmaLaneB[S_BLOCK];
    std::uint8_t                            mMagmaLaneC[S_BLOCK];
    std::uint8_t                            mMagmaLaneD[S_BLOCK];
    
    std::uint8_t                            mPlasmaLaneA[S_BLOCK];
    std::uint8_t                            mPlasmaLaneB[S_BLOCK];
    std::uint8_t                            mPlasmaLaneC[S_BLOCK];
    std::uint8_t                            mPlasmaLaneD[S_BLOCK];

    alignas(std::uint32_t) std::uint8_t     mShadowLaneA[S_BLOCK];
    alignas(std::uint32_t) std::uint8_t     mShadowLaneB[S_BLOCK];
    alignas(std::uint32_t) std::uint8_t     mShadowLaneC[S_BLOCK];
    alignas(std::uint32_t) std::uint8_t     mShadowLaneD[S_BLOCK];

    std::uint8_t                            mCrystalLaneA[S_BLOCK];
    std::uint8_t                            mCrystalLaneB[S_BLOCK];
    std::uint8_t                            mCrystalLaneC[S_BLOCK];
    std::uint8_t                            mCrystalLaneD[S_BLOCK];

    std::uint8_t                            mAetherLaneA[S_BLOCK];
    std::uint8_t                            mAetherLaneB[S_BLOCK];
    std::uint8_t                            mAetherLaneC[S_BLOCK];
    std::uint8_t                            mAetherLaneD[S_BLOCK];

    std::uint8_t                            mCelestialLaneA[S_BLOCK];
    std::uint8_t                            mCelestialLaneB[S_BLOCK];
    std::uint8_t                            mCelestialLaneC[S_BLOCK];
    std::uint8_t                            mCelestialLaneD[S_BLOCK];

    alignas(std::uint32_t) std::uint8_t     mKineticLaneA[S_BLOCK];
    alignas(std::uint32_t) std::uint8_t     mKineticLaneB[S_BLOCK];
    alignas(std::uint32_t) std::uint8_t     mKineticLaneC[S_BLOCK];
    alignas(std::uint32_t) std::uint8_t     mKineticLaneD[S_BLOCK];

    alignas(std::uint32_t) std::uint8_t     mVaporLaneA[S_BLOCK];
    alignas(std::uint32_t) std::uint8_t     mVaporLaneB[S_BLOCK];
    alignas(std::uint32_t) std::uint8_t     mVaporLaneC[S_BLOCK];
    alignas(std::uint32_t) std::uint8_t     mVaporLaneD[S_BLOCK];

    std::uint8_t                            mSpiritLaneA[S_BLOCK];
    std::uint8_t                            mSpiritLaneB[S_BLOCK];
    std::uint8_t                            mSpiritLaneC[S_BLOCK];
    std::uint8_t                            mSpiritLaneD[S_BLOCK];

    std::uint8_t                            mFuseLaneA[S_BLOCK];
    std::uint8_t                            mFuseLaneB[S_BLOCK];
    std::uint8_t                            mFuseLaneC[S_BLOCK];
    std::uint8_t                            mFuseLaneD[S_BLOCK];

    TwistDomainBundle                       mDomainBundle;

    // Rotate stays byte-wide across the workspace helpers.
    static void                             ShiftKeyBoxA(std::uint8_t *pBox); //
    static void                             ShiftKeyBoxB(std::uint8_t *pBox); //

    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkSpace,
                                                       TwistExpander *pExpander,
                                                       TwistWorkSpaceSlot pSlot);
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkSpace,
                                                       TwistExpander *pExpander,
                                                       TwistWorkSpaceSlot pSlot,
                                                       std::uint8_t *pParamSource,
                                                       std::uint8_t *pParamDestination);
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkSpace,
                                                       TwistExpander *pExpander,
                                                       TwistWorkSpaceSlot pSlot,
                                                       std::uint8_t *pParamSource,
                                                       std::uint8_t *pParamDestination,
                                                       TwistDomainSaltSet *pParamSaltSet);
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

private:
    static TwistDomainBundle                *GetSaltDomainBundle(TwistExpander *pExpander,
                                                                 TwistSaltOwner pOwner);

};

#endif /* TwistWorkSpace_hpp */
