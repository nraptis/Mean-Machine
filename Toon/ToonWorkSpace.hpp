//
//  ToonWorkSpace.hpp
//  Valhalla
//
//  Created by Dragon on 5/16/26.
//

#ifndef ToonWorkSpace_hpp
#define ToonWorkSpace_hpp

#include "ToonDomain.hpp"

class ToonExpander;

struct ToonDomainConstants {
public:
    
    std::uint64_t                           mPublicIngress;
    std::uint64_t                           mPrivateIngress;
    std::uint64_t                           mCrossIngress;
    
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

struct ToonDomainRoundMaterial {
public:
    std::uint64_t                           mSaltA[S_SALT];
    std::uint64_t                           mSaltB[S_SALT];
    std::uint64_t                           mSaltC[S_SALT];
    std::uint64_t                           mSaltD[S_SALT];
    std::uint64_t                           mSaltE[S_SALT];
    std::uint64_t                           mSaltF[S_SALT];
};

class ToonDomainSaltSet {
public:
    ToonDomainRoundMaterial mUnwind;
    ToonDomainRoundMaterial mOrbiter;
    ToonDomainRoundMaterial mOrbiterInit;
};

class ToonDomainSBoxSet {
public:
    std::uint8_t mSBoxA[S_SBOX];
    std::uint8_t mSBoxB[S_SBOX];
    std::uint8_t mSBoxC[S_SBOX];
    std::uint8_t mSBoxD[S_SBOX];
    std::uint8_t mSBoxE[S_SBOX];
    std::uint8_t mSBoxF[S_SBOX];
    std::uint8_t mSBoxG[S_SBOX];
    std::uint8_t mSBoxH[S_SBOX];
};

enum class ToonBufferKind : std::uint8_t {
    kInvalid = 0,

    kDirect,
    kSalt,
    kSBox,
    kConstants
};

enum class ToonDirectBuffer : std::uint16_t {
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
    kKeyBoxUnrolledC,
    kKeyBoxUnrolledD,

    kKeyRowReadA,
    kKeyRowReadB,
    kKeyRowReadC,
    kKeyRowReadD,
    
    kKeyRowWriteA,
    kKeyRowWriteB,
    kKeyRowWriteC,
    kKeyRowWriteD
    
};

struct ToonBufferKey {
    ToonBufferKind mKind = ToonBufferKind::kInvalid;

    ToonDirectBuffer mDirect = ToonDirectBuffer::kInvalid;

    ToonDomain mDomain = ToonDomain::kInvalid;

    ToonSaltOwner mSaltOwner = ToonSaltOwner::kInvalid;
    ToonSBoxOwner mSBoxOwner = ToonSBoxOwner::kInvalid;

    ToonSaltPhase mSaltPhase = ToonSaltPhase::kInvalid;
    ToonSaltLane mSaltLane = ToonSaltLane::kInvalid;
    ToonSBoxLane mSBoxLane = ToonSBoxLane::kInvalid;

    static ToonBufferKey Direct(ToonDirectBuffer buffer);
    static ToonBufferKey Salt(ToonSaltOwner owner, ToonDomain domain, ToonSaltPhase phase, ToonSaltLane lane);
    static ToonBufferKey SBox(ToonSBoxOwner owner, ToonDomain domain, ToonSBoxLane lane);
    static ToonBufferKey Constants(ToonSaltOwner owner, ToonDomain domain);

    bool IsValid() const;
    bool IsDirect() const;
    bool IsSalt() const;
    bool IsSBox() const;
    bool IsConstants() const;
};

class ToonDomainBundle {
public:
    //
    // Salts + constants.
    //
    ToonDomainSaltSet      mKeyASalts;
    ToonDomainConstants    mKeyAConstants;

    ToonDomainSaltSet      mKeyBSalts;
    ToonDomainConstants    mKeyBConstants;

    ToonDomainSaltSet      mKeyCSalts;
    ToonDomainConstants    mKeyCConstants;

    ToonDomainSaltSet      mKeyDSalts;
    ToonDomainConstants    mKeyDConstants;

    ToonDomainSaltSet      mWorkLaneSalts;
    ToonDomainConstants    mWorkLaneConstants;

    ToonDomainSaltSet      mOperationLaneSalts;
    ToonDomainConstants    mOperationLaneConstants;

    ToonDomainSaltSet      mExpansionLaneSalts;
    ToonDomainConstants    mExpansionLaneConstants;

    //
    // SBoxes.
    // These are domain-scoped, not phase-scoped.
    //
    ToonDomainSBoxSet      mKeyASBoxes;
    ToonDomainSBoxSet      mKeyBSBoxes;
    ToonDomainSBoxSet      mKeyCSBoxes;
    ToonDomainSBoxSet      mKeyDSBoxes;

    ToonDomainSBoxSet      mWorkLaneSBoxes;
    ToonDomainSBoxSet      mOperationLaneSBoxes;
    ToonDomainSBoxSet      mExpansionLaneSBoxes;
};

class ToonWorkSpace {
    
public:
    ToonWorkSpace();
    
    std::size_t                             mIndexList256A[256];
    std::size_t                             mIndexList256B[256];
    std::size_t                             mIndexList256C[256];
    std::size_t                             mIndexList256D[256];
    
    uint8_t                                 mKeyBoxA[H_KEY_A][W_KEY_A];
    uint8_t                                 mKeyBoxB[H_KEY_B][W_KEY_B];
    uint8_t                                 mKeyBoxC[H_KEY_A][W_KEY_A];
    uint8_t                                 mKeyBoxD[H_KEY_B][W_KEY_B];
    
    std::uint8_t                            mExpandLaneA[S_BLOCK];
    std::uint8_t                            mExpandLaneB[S_BLOCK];
    std::uint8_t                            mExpandLaneC[S_BLOCK];
    std::uint8_t                            mExpandLaneD[S_BLOCK];
    
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
    
    ToonDomainBundle                        mDomainBundle;
    
    // Rotate stays byte-wide across the workspace helpers.
    static void                             ShiftKeyBoxA(std::uint8_t *pBox); //
    static void                             ShiftKeyBoxB(std::uint8_t *pBox); //
    static void                             ShiftKeyBoxC(std::uint8_t *pBox); //
    static void                             ShiftKeyBoxD(std::uint8_t *pBox); //
    
    static std::uint8_t                     *GetBuffer(ToonWorkSpace *pWorkspace,
                                                       ToonExpander *pExpander,
                                                       ToonBufferKey pKey);
    
    static int                              GetBufferLength(ToonBufferKey pKey);
    
    static bool                             IsSBox(ToonBufferKey pKey);
    static bool                             IsSalt(ToonBufferKey pKey);
    
};

#endif /* ToonWorkSpace_hpp */
