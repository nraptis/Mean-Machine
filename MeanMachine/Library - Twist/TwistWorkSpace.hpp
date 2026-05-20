//
//  TwistWorkSpace.hpp
//  Gorgon
//

#ifndef TwistWorkSpace_hpp
#define TwistWorkSpace_hpp

#include <cstdint>
#include <vector>

#define S_BLOCK 16384 // 4,096 // 2,048

#define S_SBOX 256

#define S_SALT 32
#define S_SALT_DIVIDE_BITSHIFT 5

#define S_BLOCK1 16383
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
};

enum class TwistWorkSpaceSlot : std::uint16_t;

enum class TwistBufferKind : std::uint8_t {
    kInvalid = 0,
    kDirect,
    kSalt,
    kSBox,
    kConstants
};

enum class TwistDirectBuffer : std::uint16_t {
    kInvalid = 0,

    kSource,
    kDest,

    kIndexList256A,
    kIndexList256B,
    kIndexList256C,
    kIndexList256D,

    kExpansionLaneA,
    kExpansionLaneB,
    kExpansionLaneC,
    kExpansionLaneD,
    kExpansionLaneE,
    kExpansionLaneF,

    kWorkLaneA,
    kWorkLaneB,
    kWorkLaneC,
    kWorkLaneD,
    kWorkLaneE,
    kWorkLaneF,

    kOperationLaneA,
    kOperationLaneB,
    kOperationLaneC,
    kOperationLaneD,
    kOperationLaneE,
    kOperationLaneF,

    kSnowLaneA,
    kSnowLaneB,
    kSnowLaneC,
    kSnowLaneD,

    kMaskLaneA,
    kMaskLaneB,

    kKeyBoxUnrolledA,
    kKeyBoxUnrolledB,
    kKeyRowReadA,
    kKeyRowReadB,
    kKeyRowWriteA,
    kKeyRowWriteB,

    kMaskBoxUnrolledA,
    kMaskBoxUnrolledB,
    kMaskRowReadA,
    kMaskRowReadB,
    kMaskRowWriteA,
    kMaskRowWriteB
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
    kLocal = 1,
    kInbuilt = 2,
    kEphemeral = 3
};

enum class TwistSBoxOwner : std::uint16_t {
    kInvalid = 0,
    kLocal = 1,
    kInbuilt = 2
};

struct TwistBufferKey {
    TwistBufferKind                          mKind = TwistBufferKind::kInvalid;
    TwistDirectBuffer                        mDirect = TwistDirectBuffer::kInvalid;
    TwistDomain                              mDomain = TwistDomain::kInvalid;
    std::uint16_t                            mSlot = 255U;
    
    TwistSaltOwner                           mSaltOwner = TwistSaltOwner::kInvalid;
    TwistSBoxOwner                           mSBoxOwner = TwistSBoxOwner::kInvalid;
    TwistSBoxLane                            mSBoxLane = TwistSBoxLane::kInvalid;

    static TwistBufferKey                    Direct(TwistDirectBuffer pBuffer);
    static TwistBufferKey                    Salt(TwistSaltOwner pOwner,
                                                  TwistDomain pDomain,
                                                  TwistWorkSpaceSlot pSlot);
    static TwistBufferKey                    SBox(TwistSBoxOwner pOwner,
                                                  TwistDomain pDomain,
                                                  TwistSBoxLane pLane);
    static TwistBufferKey                    Constants(TwistSaltOwner pOwner,
                                                       TwistDomain pDomain);

    bool                                     IsValid() const;
    bool                                     IsDirect() const;
    bool                                     IsSalt() const;
    bool                                     IsSBox() const;
    bool                                     IsConstants() const;
};

enum class TwistWorkSpaceSlot : std::uint16_t {
    
    kInvalid=255,
    
    kSource=0, // size is N * S_BLOCK. To fetch from here is different, because it includes an offset. So we wrap into [offset...offset+S_BLOCK)
    kDest=1, // size is N * S_BLOCK To write to here is different, because it includes an offset. So we wrap into [offset...offset+S_BLOCK)
    
    kParamDomainSBoxA=30,
    kParamDomainSBoxB=31,
    kParamDomainSBoxC=32,
    kParamDomainSBoxD=33,
    kParamDomainSBoxE=34,
    kParamDomainSBoxF=35,
    kParamDomainSBoxG=36,
    kParamDomainSBoxH=37,

    kSBoxA=kParamDomainSBoxA, // try to remove
    kSBoxB=kParamDomainSBoxB, // try to remove
    kSBoxC=kParamDomainSBoxC, // try to remove
    kSBoxD=kParamDomainSBoxD, // try to remove
    kSBoxE=kParamDomainSBoxE, // try to remove
    kSBoxF=kParamDomainSBoxF, // try to remove
    kSBoxG=kParamDomainSBoxG, // try to remove
    kSBoxH=kParamDomainSBoxH, // try to remove
    
    
    kDerivedSBoxA=40, // try to remove
    kDerivedSBoxB=41, // try to remove
    kDerivedSBoxC=42, // try to remove
    kDerivedSBoxD=43, // try to remove
    kDerivedSBoxE=44, // try to remove
    kDerivedSBoxF=45, // try to remove
    kDerivedSBoxG=46, // try to remove
    kDerivedSBoxH=47, // try to remove
    
    kExpansionLaneA=80,
    kExpansionLaneB=81,
    kExpansionLaneC=82,
    kExpansionLaneD=83,
    kExpansionLaneE=84,
    kExpansionLaneF=85,

    kWorkLaneA=90,
    kWorkLaneB=91,
    kWorkLaneC=92,
    kWorkLaneD=93,
    kWorkLaneE=94,
    kWorkLaneF=95,

    kOperationLaneA=100,
    kOperationLaneB=101,
    kOperationLaneC=102,
    kOperationLaneD=103,
    kOperationLaneE=104,
    kOperationLaneF=105,

    kSnowLaneA=106,
    kSnowLaneB=107,
    kSnowLaneC=108,
    kSnowLaneD=109,

    kMaskLaneA=110,
    kMaskLaneB=111,
    
    
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
    
    kDomainSaltKeyBoxA=140, // try to remove
    kDomainSaltKeyBoxB=141, // try to remove
    kDomainSaltKeyBoxC=142, // try to remove
    kDomainSaltKeyBoxD=143, // try to remove
    kDomainSaltKeyBoxE=144, // try to remove
    //kDomainSaltKeyBoxF=145,
    
    kDomainSaltMaskBoxA=146, // try to remove
    kDomainSaltMaskBoxB=147, // try to remove
    kDomainSaltMaskBoxC=148, // try to remove
    kDomainSaltMaskBoxD=149, // try to remove
    kDomainSaltMaskBoxE=150, // try to remove
    kDomainSaltMaskBoxF=151, // try to remove
    
    kDomainSaltWandererUpdateA=152, // try to remove
    kDomainSaltWandererUpdateB=153, // try to remove
    kDomainSaltWandererUpdateC=154, // try to remove
    kDomainSaltWandererUpdateD=155, // try to remove
    kDomainSaltWandererUpdateE=156, // try to remove
    kDomainSaltWandererUpdateF=157, // try to remove
    
    kDomainSaltOrbiterUpdateA=158, // try to remove
    kDomainSaltOrbiterUpdateB=159, // try to remove
    kDomainSaltOrbiterUpdateC=160, // try to remove
    kDomainSaltOrbiterUpdateD=161, // try to remove
    kDomainSaltOrbiterUpdateE=162, // try to remove
    kDomainSaltOrbiterUpdateF=163, // try to remove
    
    kDomainSaltPrismA=164, // try to remove
    kDomainSaltPrismB=165, // try to remove
    kDomainSaltPrismC=166, // try to remove
    kDomainSaltPrismD=167, // try to remove
    kDomainSaltPrismE=168, // try to remove
    kDomainSaltPrismF=169, // try to remove
    
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

    /*
    kDomainSaltSourceA=kParamDomainSaltOrbiterAssignA,
    kDomainSaltSourceB=kParamDomainSaltOrbiterAssignB,
    kDomainSaltSourceC=kParamDomainSaltOrbiterUpdateC,
    kDomainSaltSourceD=kParamDomainSaltOrbiterUpdateD,
    kDomainSaltSourceE=kParamDomainSaltWandererUpdateE,
    kDomainSaltSourceF=kParamDomainSaltWandererUpdateF,
    */
    
    kIndexList256A=190,
    kIndexList256B=191,
    kIndexList256C=192,
    kIndexList256D=193,

    kDerivedSaltOrbiterA=194, // try to remove
    kDerivedSaltOrbiterB=195, // try to remove
    kDerivedSaltOrbiterC=196, // try to remove
    kDerivedSaltOrbiterD=197, // try to remove

    kDerivedSaltWandererA=198, // try to remove
    kDerivedSaltWandererB=199, // try to remove
    kDerivedSaltWandererC=200, // try to remove
    kDerivedSaltWandererD=201, // try to remove
    
};

struct TwistDomainConstants {
public:
    
    std::uint64_t                           mIngress;
    std::uint64_t                           mPrevious;
    std::uint64_t                           mCross;

    std::uint64_t                           mDomainConstantPublicIngress;
    std::uint64_t                           mDomainConstantPrivateIngress;
    std::uint64_t                           mDomainConstantCrossIngress;
    
    std::uint64_t                           mMatrixSelectA;
    std::uint64_t                           mMatrixSelectB;
    
    std::uint8_t                            mMatrixUnrollA;
    std::uint8_t                            mMatrixUnrollB;
    
    std::uint8_t                            mMatrixSchemeA;
    std::uint8_t                            mMatrixSchemeB;
    
    std::uint8_t                            mMatrixArgAA;
    std::uint8_t                            mMatrixArgAB;
    std::uint8_t                            mMatrixArgBA;
    std::uint8_t                            mMatrixArgBB;
    
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

struct TwistDomainRoundMaterial : public TwistDomainSeedRoundMaterial {
public:
    std::uint8_t                            mSBoxA[S_SBOX];
    std::uint8_t                            mSBoxB[S_SBOX];
    std::uint8_t                            mSBoxC[S_SBOX];
    std::uint8_t                            mSBoxD[S_SBOX];
    std::uint8_t                            mSBoxE[S_SBOX];
    std::uint8_t                            mSBoxF[S_SBOX];
    std::uint8_t                            mSBoxG[S_SBOX];
    std::uint8_t                            mSBoxH[S_SBOX];
    
};

class TwistDomainSaltSet {
public:
    TwistDomainSeedRoundMaterial            mOrbiterAssign;
    TwistDomainSeedRoundMaterial            mOrbiterUpdate;
    TwistDomainSeedRoundMaterial            mWandererUpdate;
    
};

class TwistDomainSBoxSet {
public:
    std::uint8_t                            mSBoxA[S_SBOX];
    std::uint8_t                            mSBoxB[S_SBOX];
    std::uint8_t                            mSBoxC[S_SBOX];
    std::uint8_t                            mSBoxD[S_SBOX];
    std::uint8_t                            mSBoxE[S_SBOX];
    std::uint8_t                            mSBoxF[S_SBOX];
    std::uint8_t                            mSBoxG[S_SBOX];
    std::uint8_t                            mSBoxH[S_SBOX];
    
};

class TwistDomainBundle {
public:
    TwistDomainSaltSet                      mPhaseASalts;
    TwistDomainConstants                    mPhaseAConstants;

    TwistDomainSaltSet                      mPhaseBSalts;
    TwistDomainConstants                    mPhaseBConstants;

    TwistDomainSaltSet                      mPhaseCSalts;
    TwistDomainConstants                    mPhaseCConstants;

    TwistDomainSBoxSet                      mPhaseASBoxes;
    TwistDomainSBoxSet                      mPhaseBSBoxes;
    TwistDomainSBoxSet                      mPhaseCSBoxes;
    
};


class TwistWorkSpace {
    
public:
    TwistWorkSpace();

    uint8_t                                 mKeyBoxA[H_KEY_A][W_KEY_A];
    uint8_t                                 mKeyBoxB[H_KEY_B][W_KEY_B];
    uint8_t                                 mMaskBoxA[H_MASK_A][W_MASK_A];
    uint8_t                                 mMaskBoxB[H_MASK_B][W_MASK_B];

    std::uint8_t                            mListExpansionLaneA[S_BLOCK];
    std::uint8_t                            mListExpansionLaneB[S_BLOCK];
    std::uint8_t                            mListExpansionLaneC[S_BLOCK];
    std::uint8_t                            mListExpansionLaneD[S_BLOCK];
    std::uint8_t                            mListExpansionLaneE[S_BLOCK];
    std::uint8_t                            mListExpansionLaneF[S_BLOCK];

    std::uint8_t                            mWorkLaneA[S_BLOCK];
    std::uint8_t                            mWorkLaneB[S_BLOCK];
    std::uint8_t                            mWorkLaneC[S_BLOCK];
    std::uint8_t                            mWorkLaneD[S_BLOCK];
    std::uint8_t                            mWorkLaneE[S_BLOCK];
    std::uint8_t                            mWorkLaneF[S_BLOCK];
    
    std::uint8_t                            mOperationLaneA[S_BLOCK];
    std::uint8_t                            mOperationLaneB[S_BLOCK];
    std::uint8_t                            mOperationLaneC[S_BLOCK];
    std::uint8_t                            mOperationLaneD[S_BLOCK];
    std::uint8_t                            mOperationLaneE[S_BLOCK];
    std::uint8_t                            mOperationLaneF[S_BLOCK];

    std::uint8_t                            mSnowLaneA[S_BLOCK];
    std::uint8_t                            mSnowLaneB[S_BLOCK];
    std::uint8_t                            mSnowLaneC[S_BLOCK];
    std::uint8_t                            mSnowLaneD[S_BLOCK];
    
    std::uint8_t                            mMaskLaneA[S_BLOCK];
    std::uint8_t                            mMaskLaneB[S_BLOCK];

    TwistDomainBundle                       mDomainBundle;
    
    // Rotate stays byte-wide across the workspace helpers.
    static void                             ShiftKeyBoxA(std::uint8_t *pBox); //
    static void                             ShiftKeyBoxB(std::uint8_t *pBox); //
    static void                             ShiftMaskBoxA(std::uint8_t *pBox); //
    static void                             ShiftMaskBoxB(std::uint8_t *pBox); //
    
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkspace,
                                                       TwistExpander *pExpander,
                                                       TwistWorkSpaceSlot pSlot);
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkspace,
                                                       TwistWorkSpaceSlot pSlot);
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkspace,
                                                       TwistExpander *pExpander,
                                                       TwistBufferKey pKey);
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkspace,
                                                       TwistBufferKey pKey);
    static bool                             TryLegacySlotToBufferKey(TwistWorkSpaceSlot pSlot,
                                                                     TwistBufferKey *pKeyOut);
    
    static int                              GetBufferLength(TwistWorkSpaceSlot pSlot); //
    static int                              GetBufferLength(TwistBufferKey pKey);
    
    static bool                             IsSBox(TwistWorkSpaceSlot pSlot);
    static bool                             IsSalt(TwistWorkSpaceSlot pSlot);
    static bool                             IsSBox(TwistBufferKey pKey);
    static bool                             IsSalt(TwistBufferKey pKey);
    
};

#endif /* TwistWorkSpace_hpp */
