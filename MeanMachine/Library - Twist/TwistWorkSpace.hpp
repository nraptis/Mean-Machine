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
#define S_SALT1 (S_SALT - 1)

#define CRYPTO_MAX_DEPTH 16
#define CRYPTO_MAX_DEPTH1 16

#define W_KEY_A 128
#define W_KEY_A1 127
#define H_KEY_A 13
#define S_KEY_A (W_KEY_A * H_KEY_A)

#define W_KEY_B 256
#define W_KEY_1 255
#define H_KEY_B 11
#define S_KEY_B (W_KEY_B * H_KEY_B)

#define W_MASK_A 128
#define W_MASK_A1 127
#define H_MASK_A 15
#define S_MASK_A (W_MASK_A * H_MASK_A)

#define W_MASK_B 256
#define W_MASK_B1 255
#define H_MASK_B 9
#define S_MASK_B (W_MASK_B * H_MASK_B)

class TwistExpander;

enum class TwistWorkSpaceSlot : std::uint8_t {
    
    kInvalid=255,
    
    kSource=0, // size is N * S_BLOCK. To fetch from here is different, because it includes an offset. So we wrap into [offset...offset+S_BLOCK)
    kDest=1, // size is N * S_BLOCK To write to here is different, because it includes an offset. So we wrap into [offset...offset+S_BLOCK)
    
    kSaltA=10,
    kSaltB=11,
    kSaltC=12,
    kSaltD=13,
    kSaltE=18,
    kSaltF=19,
    kSaltG=28,
    kSaltH=29,
    
    kDerivedSaltA=20,
    kDerivedSaltB=21,
    kDerivedSaltC=22,
    kDerivedSaltD=23,
    kDerivedSaltE=24,
    kDerivedSaltF=25,
    kDerivedSaltG=26,
    kDerivedSaltH=27,
    
    kSBoxA=30,
    kSBoxB=31,
    kSBoxC=32,
    kSBoxD=33,
    kSBoxE=34,
    kSBoxF=35,
    kSBoxG=36,
    kSBoxH=37,
    
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

    kWorkLaneA=90,
    kWorkLaneB=91,
    kWorkLaneC=92,
    kWorkLaneD=93,

    kOperationLaneA=100,
    kOperationLaneB=101,

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
    kDomainSaltKeyBoxF=145,
    
    kDomainSaltMaskBoxA=146,
    kDomainSaltMaskBoxB=147,
    kDomainSaltMaskBoxC=148,
    kDomainSaltMaskBoxD=149,
    kDomainSaltMaskBoxE=150,
    kDomainSaltMaskBoxF=151,
    
    kDomainSaltWandererA=152,
    kDomainSaltWandererB=153,
    kDomainSaltWandererC=154,
    kDomainSaltWandererD=155,
    kDomainSaltWandererE=156,
    kDomainSaltWandererF=157,
    
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
    
    kDomainSaltSourceA=170,
    kDomainSaltSourceB=171,
    kDomainSaltSourceC=172,
    kDomainSaltSourceD=173,
    kDomainSaltSourceE=174,
    kDomainSaltSourceF=175,

    kDerivedSaltOrbiterA=176,
    kDerivedSaltOrbiterB=177,
    kDerivedSaltOrbiterC=178,
    kDerivedSaltOrbiterD=179,

    kDerivedSaltWandererA=180,
    kDerivedSaltWandererB=181,
    kDerivedSaltWandererC=182,
    kDerivedSaltWandererD=183,
};


class TwistWorkSpace {
    
public:
    TwistWorkSpace();
    
    // We stop storing source here.
    // std::uint8_t                            *mSource;
    
    // We stop storing dest here.
    //std::uint8_t                            *mDest;
    
    std::uint64_t                           mDerivedSaltA[S_SALT];
    std::uint64_t                           mDerivedSaltB[S_SALT];
    std::uint64_t                           mDerivedSaltC[S_SALT];
    std::uint64_t                           mDerivedSaltD[S_SALT];
    std::uint64_t                           mDerivedSaltE[S_SALT];
    std::uint64_t                           mDerivedSaltF[S_SALT];
    std::uint64_t                           mDerivedSaltG[S_SALT];
    std::uint64_t                           mDerivedSaltH[S_SALT];

    std::uint64_t                           mDerivedSaltOrbiterA[S_SALT];
    std::uint64_t                           mDerivedSaltOrbiterB[S_SALT];
    std::uint64_t                           mDerivedSaltOrbiterC[S_SALT];
    std::uint64_t                           mDerivedSaltOrbiterD[S_SALT];

    std::uint64_t                           mDerivedSaltWandererA[S_SALT];
    std::uint64_t                           mDerivedSaltWandererB[S_SALT];
    std::uint64_t                           mDerivedSaltWandererC[S_SALT];
    std::uint64_t                           mDerivedSaltWandererD[S_SALT];
    
    std::uint8_t                            mDerivedSBoxA[S_SBOX];
    std::uint8_t                            mDerivedSBoxB[S_SBOX];
    std::uint8_t                            mDerivedSBoxC[S_SBOX];
    std::uint8_t                            mDerivedSBoxD[S_SBOX];
    std::uint8_t                            mDerivedSBoxE[S_SBOX];
    std::uint8_t                            mDerivedSBoxF[S_SBOX];
    std::uint8_t                            mDerivedSBoxG[S_SBOX];
    std::uint8_t                            mDerivedSBoxH[S_SBOX];
    
    uint8_t                                 mKeyBoxA[CRYPTO_MAX_DEPTH][W_KEY_A];
    uint8_t                                 mKeyBoxB[CRYPTO_MAX_DEPTH][W_KEY_B];
    uint8_t                                 mMaskBoxA[CRYPTO_MAX_DEPTH][W_MASK_A];
    uint8_t                                 mMaskBoxB[CRYPTO_MAX_DEPTH][W_MASK_B];
    
    std::uint8_t                            mExpandLaneA[S_BLOCK];
    std::uint8_t                            mExpandLaneB[S_BLOCK];
    std::uint8_t                            mExpandLaneC[S_BLOCK];
    std::uint8_t                            mExpandLaneD[S_BLOCK];
    
    std::uint8_t                            mWorkLaneA[S_BLOCK];
    std::uint8_t                            mWorkLaneB[S_BLOCK];
    std::uint8_t                            mWorkLaneC[S_BLOCK];
    std::uint8_t                            mWorkLaneD[S_BLOCK];
    
    std::uint8_t                            mOperationLaneA[S_BLOCK];
    std::uint8_t                            mOperationLaneB[S_BLOCK];
    
    std::uint8_t                            mMaskLaneA[S_BLOCK];
    std::uint8_t                            mMaskLaneB[S_BLOCK];
    
    // Rotate stays byte-wide across the workspace helpers.
    static void                             ShiftKeyBoxA(std::uint8_t *pBox); //
    static void                             ShiftKeyBoxB(std::uint8_t *pBox); //
    static void                             ShiftMaskBoxA(std::uint8_t *pBox); //
    static void                             ShiftMaskBoxB(std::uint8_t *pBox); //
    
    static std::uint8_t                     *GetBuffer(TwistWorkSpace *pWorkspace,
                                                       TwistExpander *pExpander,
                                                       TwistWorkSpaceSlot pSlot);
    
    static int                              GetBufferLength(TwistWorkSpaceSlot pSlot); //
    
    static bool                             IsSBox(TwistWorkSpaceSlot pSlot);
    static bool                             IsSalt(TwistWorkSpaceSlot pSlot);
    
    
};

#endif /* TwistWorkSpace_hpp */
