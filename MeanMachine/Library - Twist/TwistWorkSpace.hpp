//
//  TwistWorkSpace.hpp
//  Gorgon
//

#ifndef TwistWorkSpace_hpp
#define TwistWorkSpace_hpp

#include <cstdint>
#include <vector>
#include "TwistDomains.hpp"

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

enum class TwistDomainFamily : std::uint16_t {
    kInvalid = 0,
    kKeyA = 1,
    kKeyB = 2,
    kMaskA = 3,
    kMaskB = 4,
    kWorkLane = 5,
    kMaskLane = 6,
    kOperationLane = 7
};

enum class TwistSaltPhase : std::uint16_t {
    kInvalid = 0,
    kUnwind = 1,
    kOrbiter = 2,
    kOrbiterInit = 3
};

enum class TwistSaltLane : std::uint16_t {
    kInvalid = 0,
    kA = 1,
    kB = 2,
    kC = 3,
    kD = 4,
    kE = 5,
    kF = 6
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
    TwistDomainFamily                        mDomain = TwistDomainFamily::kInvalid;
    TwistSaltOwner                           mSaltOwner = TwistSaltOwner::kInvalid;
    TwistSBoxOwner                           mSBoxOwner = TwistSBoxOwner::kInvalid;
    TwistSaltPhase                           mSaltPhase = TwistSaltPhase::kInvalid;
    TwistSaltLane                            mSaltLane = TwistSaltLane::kInvalid;
    TwistSBoxLane                            mSBoxLane = TwistSBoxLane::kInvalid;

    static TwistBufferKey                    Direct(TwistDirectBuffer pBuffer);
    static TwistBufferKey                    Salt(TwistSaltOwner pOwner,
                                                  TwistDomainFamily pDomain,
                                                  TwistSaltPhase pPhase,
                                                  TwistSaltLane pLane);
    static TwistBufferKey                    SBox(TwistSBoxOwner pOwner,
                                                  TwistDomainFamily pDomain,
                                                  TwistSBoxLane pLane);
    static TwistBufferKey                    Constants(TwistSaltOwner pOwner,
                                                       TwistDomainFamily pDomain);

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

    kSBoxA=kParamDomainSBoxA,
    kSBoxB=kParamDomainSBoxB,
    kSBoxC=kParamDomainSBoxC,
    kSBoxD=kParamDomainSBoxD,
    kSBoxE=kParamDomainSBoxE,
    kSBoxF=kParamDomainSBoxF,
    kSBoxG=kParamDomainSBoxG,
    kSBoxH=kParamDomainSBoxH,
    
    kDerivedSBoxA=40,
    kDerivedSBoxB=41,
    kDerivedSBoxC=42,
    kDerivedSBoxD=43,
    kDerivedSBoxE=44,
    kDerivedSBoxF=45,
    kDerivedSBoxG=46,
    kDerivedSBoxH=47,
    
    
    kSeedExpansionLaneA=80,
    kSeedExpansionLaneB=81,
    kSeedExpansionLaneC=82,
    kSeedExpansionLaneD=83,
    kSeedExpansionLaneE=84,
    kSeedExpansionLaneF=85,

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
    
    kDomainSaltKeyBoxA=140,
    kDomainSaltKeyBoxB=141,
    kDomainSaltKeyBoxC=142,
    kDomainSaltKeyBoxD=143,
    kDomainSaltKeyBoxE=144,
    //kDomainSaltKeyBoxF=145,
    
    kDomainSaltMaskBoxA=146,
    kDomainSaltMaskBoxB=147,
    kDomainSaltMaskBoxC=148,
    kDomainSaltMaskBoxD=149,
    kDomainSaltMaskBoxE=150,
    kDomainSaltMaskBoxF=151,
    
    kDomainSaltUnwindA=152,
    kDomainSaltUnwindB=153,
    kDomainSaltUnwindC=154,
    kDomainSaltUnwindD=155,
    kDomainSaltUnwindE=156,
    kDomainSaltUnwindF=157,
    
    kDomainSaltOrbiterA=158,
    kDomainSaltOrbiterB=159,
    kDomainSaltOrbiterC=160,
    kDomainSaltOrbiterD=161,
    kDomainSaltOrbiterE=162,
    kDomainSaltOrbiterF=163,
    
    kDomainSaltPrismA=164,
    kDomainSaltPrismB=165,
    kDomainSaltPrismC=166,
    kDomainSaltPrismD=167,
    kDomainSaltPrismE=168,
    kDomainSaltPrismF=169,
    
    kParamDomainSaltOrbiterInitA=170,
    kParamDomainSaltOrbiterInitB=171,
    kParamDomainSaltOrbiterC=172,
    kParamDomainSaltOrbiterD=173,
    kParamDomainSaltUnwindE=174,
    kParamDomainSaltUnwindF=175,

    kDomainSaltSourceA=kParamDomainSaltOrbiterInitA,
    kDomainSaltSourceB=kParamDomainSaltOrbiterInitB,
    kDomainSaltSourceC=kParamDomainSaltOrbiterC,
    kDomainSaltSourceD=kParamDomainSaltOrbiterD,
    kDomainSaltSourceE=kParamDomainSaltUnwindE,
    kDomainSaltSourceF=kParamDomainSaltUnwindF,

    kDerivedSaltOrbiterA=176,
    kDerivedSaltOrbiterB=177,
    kDerivedSaltOrbiterC=178,
    kDerivedSaltOrbiterD=179,

    kDerivedSaltUnwindA=180,
    kDerivedSaltUnwindB=181,
    kDerivedSaltUnwindC=182,
    kDerivedSaltUnwindD=183,
    
    
    kIndexList256A=190,
    kIndexList256B=191,
    kIndexList256C=192,
    kIndexList256D=193,
    
};

struct TwistDomainConstants {
public:
    
    std::uint64_t                           mDomainConstantPublicIngress;
    std::uint64_t                           mDomainConstantPrivateIngress;
    std::uint64_t                           mDomainConstantCrossIngress;
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
    TwistDomainSeedRoundMaterial            mUnwind;
    TwistDomainSeedRoundMaterial            mOrbiter;
    TwistDomainSeedRoundMaterial            mOrbiterInit;
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
    TwistDomainSaltSet                      mKeyASalts;
    TwistDomainConstants                    mKeyAConstants;

    TwistDomainSaltSet                      mKeyBSalts;
    TwistDomainConstants                    mKeyBConstants;

    TwistDomainSaltSet                      mMaskASalts;
    TwistDomainConstants                    mMaskAConstants;

    TwistDomainSaltSet                      mMaskBSalts;
    TwistDomainConstants                    mMaskBConstants;

    TwistDomainSaltSet                      mWorkLaneSalts;
    TwistDomainConstants                    mWorkLaneConstants;

    TwistDomainSaltSet                      mMaskLaneSalts;
    TwistDomainConstants                    mMaskLaneConstants;

    TwistDomainSaltSet                      mOperationLaneSalts;
    TwistDomainConstants                    mOperationLaneConstants;

    TwistDomainSBoxSet                      mKeyASBoxes;
    TwistDomainSBoxSet                      mKeyBSBoxes;
    TwistDomainSBoxSet                      mMaskASBoxes;
    TwistDomainSBoxSet                      mMaskBSBoxes;
    TwistDomainSBoxSet                      mWorkLaneSBoxes;
    TwistDomainSBoxSet                      mMaskLaneSBoxes;
    TwistDomainSBoxSet                      mOperationLaneSBoxes;
};


class TwistWorkSpace {
    
public:
    TwistWorkSpace();

    uint8_t                                 mKeyBoxA[H_KEY_A][W_KEY_A];
    uint8_t                                 mKeyBoxB[H_KEY_B][W_KEY_B];
    uint8_t                                 mMaskBoxA[H_MASK_A][W_MASK_A];
    uint8_t                                 mMaskBoxB[H_MASK_B][W_MASK_B];

    std::uint8_t                            mExpandLaneA[S_BLOCK];
    std::uint8_t                            mExpandLaneB[S_BLOCK];
    std::uint8_t                            mExpandLaneC[S_BLOCK];
    std::uint8_t                            mExpandLaneD[S_BLOCK];
    std::uint8_t                            mExpandLaneE[S_BLOCK];
    std::uint8_t                            mExpandLaneF[S_BLOCK];

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
