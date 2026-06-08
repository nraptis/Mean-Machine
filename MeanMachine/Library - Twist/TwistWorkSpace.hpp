//
//  TwistWorkSpace.hpp
//  Gorgon
//

#ifndef TwistWorkSpace_hpp
#define TwistWorkSpace_hpp

#include <cstdint>
#include <vector>

#define S_BLOCK 32768 // 4,096 // 2,048

#define S_SBOX 256

#define S_SALT 32
#define S_SALT_DIVIDE_BITSHIFT 5

#define S_BLOCK1 32767
#define S_SBOX1 255
#define S_SALT1 31

#define W_KEY_A 512
#define W_KEY_A1 511
#define H_KEY_A 8
#define S_KEY_A (W_KEY_A * H_KEY_A)

#define W_KEY_B 1024
#define W_KEY_1 1023
#define H_KEY_B 4
#define S_KEY_B (W_KEY_B * H_KEY_B)

#define W_MASK_A 512
#define W_MASK_A1 511
#define H_MASK_A 8
#define S_MASK_A (W_MASK_A * H_MASK_A)

#define W_MASK_B 512
#define W_MASK_B1 511
#define H_MASK_B 8
#define S_MASK_B (W_MASK_B * H_MASK_B)

class TwistExpander;

enum class TwistDomain : std::uint8_t {
    kInvalid = 0,
    kPhaseA,
    kPhaseB,
    kPhaseC,
    kPhaseD,
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
    
    kSource=0, // size is N * S_BLOCK. To fetch from here is different, because it includes an offset. So we wrap into [offset...offset+S_BLOCK)
    kDest=1, // size is N * S_BLOCK To write to here is different, because it includes an offset. So we wrap into [offset...offset+S_BLOCK)
    
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

    kSnow=112,
    
    
    // These are confusing.
    // 1.) We "seed" into entire box, e.g. "kKeyBoxUnrolledA" or "kKeyBoxUnrolledB"
    // 2.) We "read", in a twist, from "kKeyRowReadA" or "kKeyRowReadB", which is the 'last row'.
    // 3.) Before writing, we Shift, evicting last row and duplicating first row
    // 4.) We "write", after a twist, from "kKeyRowWriteA" or "kKeyRowWriteB", which is the 'first row'.
    
    kKeyBoxUnrolledA=120, // size is S_KEY_A
    kKeyBoxUnrolledB=121, // size is S_KEY_B
    kKeyRowReadA=122, // size is W_KEY_A
    kKeyRowReadB=123, // size is W_KEY_B
    kKeyRowWriteA=124, // size is S_KEY_A
    kKeyRowWriteB=125, // size is S_KEY_B

    kMaskBoxUnrolledA=130, // size is S_MASK_A
    kMaskBoxUnrolledB=131, // size is S_MASK_B
    kMaskRowReadA=132, // size is W_MASK_A
    kMaskRowReadB=133, // size is W_MASK_B
    kMaskRowWriteA=134, // size is S_MASK_A
    kMaskRowWriteB=135, // size is S_MASK_B
    
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
    
};

struct TwistDomainSeedRoundMaterial {
public:
    std::uint64_t                           mSaltA[S_SALT];
    std::uint64_t                           mSaltB[S_SALT];
    std::uint64_t                           mSaltC[S_SALT];
    std::uint64_t                           mSaltD[S_SALT];
    std::uint64_t                           mSaltE[S_SALT];
    std::uint64_t                           mSaltF[S_SALT];
    
};

class TwistDomainSaltSet {
public:
    TwistDomainSeedRoundMaterial            mOrbiterAssign;
    TwistDomainSeedRoundMaterial            mOrbiterUpdate;
    TwistDomainSeedRoundMaterial            mWandererUpdate;
    
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
};


class TwistWorkSpace {
    
public:
    TwistWorkSpace();

    uint8_t                                 mKeyBoxA[H_KEY_A][W_KEY_A];
    uint8_t                                 mKeyBoxB[H_KEY_B][W_KEY_B];
    uint8_t                                 mMaskBoxA[H_MASK_A][W_MASK_A];
    uint8_t                                 mMaskBoxB[H_MASK_B][W_MASK_B];

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

    TwistDomainBundle                       mDomainBundle;
    
    // Rotate stays byte-wide across the workspace helpers.
    static void                             ShiftKeyBoxA(std::uint8_t *pBox); //
    static void                             ShiftKeyBoxB(std::uint8_t *pBox); //
    static void                             ShiftMaskBoxA(std::uint8_t *pBox); //
    static void                             ShiftMaskBoxB(std::uint8_t *pBox); //
    
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
    static bool                             TryLegacySlotToBufferKey(TwistWorkSpaceSlot pSlot,
                                                                     TwistBufferKey *pKeyOut);
    
    static int                              GetBufferLength(TwistWorkSpaceSlot pSlot); //
    static int                              GetBufferLength(TwistBufferKey pKey);
    
    static bool                             IsSalt(TwistWorkSpaceSlot pSlot);
    static bool                             IsSalt(TwistBufferKey pKey);
    
};

#endif /* TwistWorkSpace_hpp */
