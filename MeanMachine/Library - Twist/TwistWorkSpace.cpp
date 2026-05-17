//
//  TwistWorkSpace.cpp
//  Gorgon
//

#include "TwistWorkSpace.hpp"
#include "TwistExpander.hpp"
#include <cstring>

inline TwistBufferKey TwistBufferKey::Direct(TwistDirectBuffer pBuffer) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kDirect;
    aKey.mDirect = pBuffer;
    return aKey;
}

inline TwistBufferKey TwistBufferKey::Salt(TwistSaltOwner pOwner,
                                           TwistDomainFamily pDomain,
                                           TwistSaltPhase pPhase,
                                           TwistSaltLane pLane) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kSalt;
    aKey.mSaltOwner = pOwner;
    aKey.mDomain = pDomain;
    aKey.mSaltPhase = pPhase;
    aKey.mSaltLane = pLane;
    return aKey;
}

inline TwistBufferKey TwistBufferKey::SBox(TwistSBoxOwner pOwner,
                                           TwistDomainFamily pDomain,
                                           TwistSBoxLane pLane) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kSBox;
    aKey.mSBoxOwner = pOwner;
    aKey.mDomain = pDomain;
    aKey.mSBoxLane = pLane;
    return aKey;
}

inline TwistBufferKey TwistBufferKey::Constants(TwistSaltOwner pOwner,
                                                TwistDomainFamily pDomain) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kConstants;
    aKey.mSaltOwner = pOwner;
    aKey.mDomain = pDomain;
    return aKey;
}

inline bool TwistBufferKey::IsValid() const {
    return mKind != TwistBufferKind::kInvalid;
}

inline bool TwistBufferKey::IsDirect() const {
    return mKind == TwistBufferKind::kDirect;
}

inline bool TwistBufferKey::IsSalt() const {
    return mKind == TwistBufferKind::kSalt;
}

inline bool TwistBufferKey::IsSBox() const {
    return mKind == TwistBufferKind::kSBox;
}

inline bool TwistBufferKey::IsConstants() const {
    return mKind == TwistBufferKind::kConstants;
}

namespace {

[[maybe_unused]] TwistWorkSpaceSlot DirectBufferToSlot(TwistDirectBuffer pBuffer) {
    switch (pBuffer) {
        case TwistDirectBuffer::kSource: return TwistWorkSpaceSlot::kSource;
        case TwistDirectBuffer::kDest: return TwistWorkSpaceSlot::kDest;
        case TwistDirectBuffer::kIndexList256A: return TwistWorkSpaceSlot::kIndexList256A;
        case TwistDirectBuffer::kIndexList256B: return TwistWorkSpaceSlot::kIndexList256B;
        case TwistDirectBuffer::kIndexList256C: return TwistWorkSpaceSlot::kIndexList256C;
        case TwistDirectBuffer::kIndexList256D: return TwistWorkSpaceSlot::kIndexList256D;
        case TwistDirectBuffer::kExpansionLaneA: return TwistWorkSpaceSlot::kSeedExpansionLaneA;
        case TwistDirectBuffer::kExpansionLaneB: return TwistWorkSpaceSlot::kSeedExpansionLaneB;
        case TwistDirectBuffer::kExpansionLaneC: return TwistWorkSpaceSlot::kSeedExpansionLaneC;
        case TwistDirectBuffer::kExpansionLaneD: return TwistWorkSpaceSlot::kSeedExpansionLaneD;
        case TwistDirectBuffer::kExpansionLaneE: return TwistWorkSpaceSlot::kSeedExpansionLaneE;
        case TwistDirectBuffer::kExpansionLaneF: return TwistWorkSpaceSlot::kSeedExpansionLaneF;
        case TwistDirectBuffer::kWorkLaneA: return TwistWorkSpaceSlot::kWorkLaneA;
        case TwistDirectBuffer::kWorkLaneB: return TwistWorkSpaceSlot::kWorkLaneB;
        case TwistDirectBuffer::kWorkLaneC: return TwistWorkSpaceSlot::kWorkLaneC;
        case TwistDirectBuffer::kWorkLaneD: return TwistWorkSpaceSlot::kWorkLaneD;
        case TwistDirectBuffer::kWorkLaneE: return TwistWorkSpaceSlot::kWorkLaneE;
        case TwistDirectBuffer::kWorkLaneF: return TwistWorkSpaceSlot::kWorkLaneF;
        case TwistDirectBuffer::kOperationLaneA: return TwistWorkSpaceSlot::kOperationLaneA;
        case TwistDirectBuffer::kOperationLaneB: return TwistWorkSpaceSlot::kOperationLaneB;
        case TwistDirectBuffer::kOperationLaneC: return TwistWorkSpaceSlot::kOperationLaneC;
        case TwistDirectBuffer::kOperationLaneD: return TwistWorkSpaceSlot::kOperationLaneD;
        case TwistDirectBuffer::kOperationLaneE: return TwistWorkSpaceSlot::kOperationLaneE;
        case TwistDirectBuffer::kOperationLaneF: return TwistWorkSpaceSlot::kOperationLaneF;
        case TwistDirectBuffer::kMaskLaneA: return TwistWorkSpaceSlot::kMaskLaneA;
        case TwistDirectBuffer::kMaskLaneB: return TwistWorkSpaceSlot::kMaskLaneB;
        case TwistDirectBuffer::kKeyBoxUnrolledA: return TwistWorkSpaceSlot::kKeyBoxUnrolledA;
        case TwistDirectBuffer::kKeyBoxUnrolledB: return TwistWorkSpaceSlot::kKeyBoxUnrolledB;
        case TwistDirectBuffer::kKeyRowReadA: return TwistWorkSpaceSlot::kKeyRowReadA;
        case TwistDirectBuffer::kKeyRowReadB: return TwistWorkSpaceSlot::kKeyRowReadB;
        case TwistDirectBuffer::kKeyRowWriteA: return TwistWorkSpaceSlot::kKeyRowWriteA;
        case TwistDirectBuffer::kKeyRowWriteB: return TwistWorkSpaceSlot::kKeyRowWriteB;
        case TwistDirectBuffer::kMaskBoxUnrolledA: return TwistWorkSpaceSlot::kMaskBoxUnrolledA;
        case TwistDirectBuffer::kMaskBoxUnrolledB: return TwistWorkSpaceSlot::kMaskBoxUnrolledB;
        case TwistDirectBuffer::kMaskRowReadA: return TwistWorkSpaceSlot::kMaskRowReadA;
        case TwistDirectBuffer::kMaskRowReadB: return TwistWorkSpaceSlot::kMaskRowReadB;
        case TwistDirectBuffer::kMaskRowWriteA: return TwistWorkSpaceSlot::kMaskRowWriteA;
        case TwistDirectBuffer::kMaskRowWriteB: return TwistWorkSpaceSlot::kMaskRowWriteB;
        default: return TwistWorkSpaceSlot::kInvalid;
    }
}

bool DirectBufferFromSlot(TwistWorkSpaceSlot pSlot,
                          TwistDirectBuffer *pBufferOut) {
    if (pBufferOut == nullptr) {
        return false;
    }
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource:
            *pBufferOut = TwistDirectBuffer::kSource;
            return true;
        case TwistWorkSpaceSlot::kDest:
            *pBufferOut = TwistDirectBuffer::kDest;
            return true;
        case TwistWorkSpaceSlot::kIndexList256A:
            *pBufferOut = TwistDirectBuffer::kIndexList256A;
            return true;
        case TwistWorkSpaceSlot::kIndexList256B:
            *pBufferOut = TwistDirectBuffer::kIndexList256B;
            return true;
        case TwistWorkSpaceSlot::kIndexList256C:
            *pBufferOut = TwistDirectBuffer::kIndexList256C;
            return true;
        case TwistWorkSpaceSlot::kIndexList256D:
            *pBufferOut = TwistDirectBuffer::kIndexList256D;
            return true;
        case TwistWorkSpaceSlot::kSeedExpansionLaneA:
            *pBufferOut = TwistDirectBuffer::kExpansionLaneA;
            return true;
        case TwistWorkSpaceSlot::kSeedExpansionLaneB:
            *pBufferOut = TwistDirectBuffer::kExpansionLaneB;
            return true;
        case TwistWorkSpaceSlot::kSeedExpansionLaneC:
            *pBufferOut = TwistDirectBuffer::kExpansionLaneC;
            return true;
        case TwistWorkSpaceSlot::kSeedExpansionLaneD:
            *pBufferOut = TwistDirectBuffer::kExpansionLaneD;
            return true;
        case TwistWorkSpaceSlot::kSeedExpansionLaneE:
            *pBufferOut = TwistDirectBuffer::kExpansionLaneE;
            return true;
        case TwistWorkSpaceSlot::kSeedExpansionLaneF:
            *pBufferOut = TwistDirectBuffer::kExpansionLaneF;
            return true;
        case TwistWorkSpaceSlot::kWorkLaneA:
            *pBufferOut = TwistDirectBuffer::kWorkLaneA;
            return true;
        case TwistWorkSpaceSlot::kWorkLaneB:
            *pBufferOut = TwistDirectBuffer::kWorkLaneB;
            return true;
        case TwistWorkSpaceSlot::kWorkLaneC:
            *pBufferOut = TwistDirectBuffer::kWorkLaneC;
            return true;
        case TwistWorkSpaceSlot::kWorkLaneD:
            *pBufferOut = TwistDirectBuffer::kWorkLaneD;
            return true;
        case TwistWorkSpaceSlot::kWorkLaneE:
            *pBufferOut = TwistDirectBuffer::kWorkLaneE;
            return true;
        case TwistWorkSpaceSlot::kWorkLaneF:
            *pBufferOut = TwistDirectBuffer::kWorkLaneF;
            return true;
        case TwistWorkSpaceSlot::kOperationLaneA:
            *pBufferOut = TwistDirectBuffer::kOperationLaneA;
            return true;
        case TwistWorkSpaceSlot::kOperationLaneB:
            *pBufferOut = TwistDirectBuffer::kOperationLaneB;
            return true;
        case TwistWorkSpaceSlot::kOperationLaneC:
            *pBufferOut = TwistDirectBuffer::kOperationLaneC;
            return true;
        case TwistWorkSpaceSlot::kOperationLaneD:
            *pBufferOut = TwistDirectBuffer::kOperationLaneD;
            return true;
        case TwistWorkSpaceSlot::kOperationLaneE:
            *pBufferOut = TwistDirectBuffer::kOperationLaneE;
            return true;
        case TwistWorkSpaceSlot::kOperationLaneF:
            *pBufferOut = TwistDirectBuffer::kOperationLaneF;
            return true;
        case TwistWorkSpaceSlot::kMaskLaneA:
            *pBufferOut = TwistDirectBuffer::kMaskLaneA;
            return true;
        case TwistWorkSpaceSlot::kMaskLaneB:
            *pBufferOut = TwistDirectBuffer::kMaskLaneB;
            return true;
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA:
            *pBufferOut = TwistDirectBuffer::kKeyBoxUnrolledA;
            return true;
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB:
            *pBufferOut = TwistDirectBuffer::kKeyBoxUnrolledB;
            return true;
        case TwistWorkSpaceSlot::kKeyRowReadA:
            *pBufferOut = TwistDirectBuffer::kKeyRowReadA;
            return true;
        case TwistWorkSpaceSlot::kKeyRowReadB:
            *pBufferOut = TwistDirectBuffer::kKeyRowReadB;
            return true;
        case TwistWorkSpaceSlot::kKeyRowWriteA:
            *pBufferOut = TwistDirectBuffer::kKeyRowWriteA;
            return true;
        case TwistWorkSpaceSlot::kKeyRowWriteB:
            *pBufferOut = TwistDirectBuffer::kKeyRowWriteB;
            return true;
        case TwistWorkSpaceSlot::kMaskBoxUnrolledA:
            *pBufferOut = TwistDirectBuffer::kMaskBoxUnrolledA;
            return true;
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB:
            *pBufferOut = TwistDirectBuffer::kMaskBoxUnrolledB;
            return true;
        case TwistWorkSpaceSlot::kMaskRowReadA:
            *pBufferOut = TwistDirectBuffer::kMaskRowReadA;
            return true;
        case TwistWorkSpaceSlot::kMaskRowReadB:
            *pBufferOut = TwistDirectBuffer::kMaskRowReadB;
            return true;
        case TwistWorkSpaceSlot::kMaskRowWriteA:
            *pBufferOut = TwistDirectBuffer::kMaskRowWriteA;
            return true;
        case TwistWorkSpaceSlot::kMaskRowWriteB:
            *pBufferOut = TwistDirectBuffer::kMaskRowWriteB;
            return true;
        default:
            return false;
    }
}

TwistDomainBundle *GetSaltDomainBundle(TwistWorkSpace *pWorkspace,
                                       TwistExpander *pExpander,
                                       TwistSaltOwner pOwner) {
    switch (pOwner) {
        case TwistSaltOwner::kLocal:
            return pWorkspace ? &pWorkspace->mDomainBundle : nullptr;
        case TwistSaltOwner::kInbuilt:
            return pExpander ? &pExpander->mDomainBundleInbuilt : nullptr;
        case TwistSaltOwner::kEphemeral:
            return pExpander ? &pExpander->mDomainBundleEphemeral : nullptr;
        default:
            return nullptr;
    }
}

TwistDomainBundle *GetSBoxDomainBundle(TwistWorkSpace *pWorkspace,
                                       TwistExpander *pExpander,
                                       TwistSBoxOwner pOwner) {
    switch (pOwner) {
        case TwistSBoxOwner::kLocal:
            return pWorkspace ? &pWorkspace->mDomainBundle : nullptr;
        case TwistSBoxOwner::kInbuilt:
            return pExpander ? &pExpander->mDomainBundleInbuilt : nullptr;
        default:
            return nullptr;
    }
}

TwistDomainSaltSet *GetSaltSet(TwistDomainBundle *pBundle,
                               TwistDomainFamily pDomain) {
    if (pBundle == nullptr) {
        return nullptr;
    }
    switch (pDomain) {
        case TwistDomainFamily::kKeyA: return &pBundle->mKeyASalts;
        case TwistDomainFamily::kKeyB: return &pBundle->mKeyBSalts;
        case TwistDomainFamily::kMaskA: return &pBundle->mMaskASalts;
        case TwistDomainFamily::kMaskB: return &pBundle->mMaskBSalts;
        case TwistDomainFamily::kWorkLane: return &pBundle->mWorkLaneSalts;
        case TwistDomainFamily::kMaskLane: return &pBundle->mMaskLaneSalts;
        case TwistDomainFamily::kOperationLane: return &pBundle->mOperationLaneSalts;
        default: return nullptr;
    }
}

TwistDomainConstants *GetDomainConstants(TwistDomainBundle *pBundle,
                                         TwistDomainFamily pDomain) {
    if (pBundle == nullptr) {
        return nullptr;
    }
    switch (pDomain) {
        case TwistDomainFamily::kKeyA: return &pBundle->mKeyAConstants;
        case TwistDomainFamily::kKeyB: return &pBundle->mKeyBConstants;
        case TwistDomainFamily::kMaskA: return &pBundle->mMaskAConstants;
        case TwistDomainFamily::kMaskB: return &pBundle->mMaskBConstants;
        case TwistDomainFamily::kWorkLane: return &pBundle->mWorkLaneConstants;
        case TwistDomainFamily::kMaskLane: return &pBundle->mMaskLaneConstants;
        case TwistDomainFamily::kOperationLane: return &pBundle->mOperationLaneConstants;
        default: return nullptr;
    }
}

TwistDomainSBoxSet *GetSBoxSet(TwistDomainBundle *pBundle,
                               TwistDomainFamily pDomain) {
    if (pBundle == nullptr) {
        return nullptr;
    }
    switch (pDomain) {
        case TwistDomainFamily::kKeyA: return &pBundle->mKeyASBoxes;
        case TwistDomainFamily::kKeyB: return &pBundle->mKeyBSBoxes;
        case TwistDomainFamily::kMaskA: return &pBundle->mMaskASBoxes;
        case TwistDomainFamily::kMaskB: return &pBundle->mMaskBSBoxes;
        case TwistDomainFamily::kWorkLane: return &pBundle->mWorkLaneSBoxes;
        case TwistDomainFamily::kMaskLane: return &pBundle->mMaskLaneSBoxes;
        case TwistDomainFamily::kOperationLane: return &pBundle->mOperationLaneSBoxes;
        default: return nullptr;
    }
}

TwistDomainSeedRoundMaterial *GetPhaseMaterial(TwistDomainSaltSet *pSet,
                                               TwistSaltPhase pPhase) {
    if (pSet == nullptr) {
        return nullptr;
    }
    switch (pPhase) {
        case TwistSaltPhase::kUnwind: return &pSet->mUnwind;
        case TwistSaltPhase::kOrbiter: return &pSet->mOrbiter;
        case TwistSaltPhase::kOrbiterInit: return &pSet->mOrbiterInit;
        default: return nullptr;
    }
}

std::uint64_t *GetSaltLane(TwistDomainSeedRoundMaterial *pMaterial,
                           TwistSaltLane pLane) {
    if (pMaterial == nullptr) {
        return nullptr;
    }
    switch (pLane) {
        case TwistSaltLane::kA: return pMaterial->mSaltA;
        case TwistSaltLane::kB: return pMaterial->mSaltB;
        case TwistSaltLane::kC: return pMaterial->mSaltC;
        case TwistSaltLane::kD: return pMaterial->mSaltD;
        case TwistSaltLane::kE: return pMaterial->mSaltE;
        case TwistSaltLane::kF: return pMaterial->mSaltF;
        default: return nullptr;
    }
}

std::uint8_t *GetSBoxLane(TwistDomainSBoxSet *pSet,
                          TwistSBoxLane pLane) {
    if (pSet == nullptr) {
        return nullptr;
    }
    switch (pLane) {
        case TwistSBoxLane::kA: return pSet->mSBoxA;
        case TwistSBoxLane::kB: return pSet->mSBoxB;
        case TwistSBoxLane::kC: return pSet->mSBoxC;
        case TwistSBoxLane::kD: return pSet->mSBoxD;
        case TwistSBoxLane::kE: return pSet->mSBoxE;
        case TwistSBoxLane::kF: return pSet->mSBoxF;
        case TwistSBoxLane::kG: return pSet->mSBoxG;
        case TwistSBoxLane::kH: return pSet->mSBoxH;
        default: return nullptr;
    }
}

bool TryMapLegacySaltSlotToKey(const TwistWorkSpaceSlot pSlot,
                               TwistBufferKey *pKeyOut) {
    if (pKeyOut == nullptr) {
        return false;
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxA:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kKeyA,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxB:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kKeyA,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxC:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kKeyB,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxD:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kKeyB,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxE:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxA:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kMaskA,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxB:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kMaskA,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxC:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kMaskB,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxD:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kMaskB,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxE:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kMaskLane,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxF:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kMaskLane,
                                            TwistSaltPhase::kOrbiterInit,
                                            TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltUnwindA:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kUnwind,
                                            TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltUnwindB:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kUnwind,
                                            TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltUnwindC:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kUnwind,
                                            TwistSaltLane::kC);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltUnwindD:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kUnwind,
                                            TwistSaltLane::kD);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltUnwindE:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kUnwind,
                                            TwistSaltLane::kE);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltUnwindF:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kUnwind,
                                            TwistSaltLane::kF);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltOrbiterA:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltOrbiterB:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltOrbiterC:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kC);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltOrbiterD:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kD);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltOrbiterE:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kE);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltOrbiterF:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kWorkLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kF);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltPrismA:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kOperationLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltPrismB:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kOperationLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltPrismC:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kOperationLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kC);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltPrismD:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kOperationLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kD);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltPrismE:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kOperationLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kE);
            return true;
        case TwistWorkSpaceSlot::kDomainSaltPrismF:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt,
                                            TwistDomainFamily::kOperationLane,
                                            TwistSaltPhase::kOrbiter,
                                            TwistSaltLane::kF);
            return true;
        default:
            return false;
    }
}

bool TryMapLegacySlotToKey(const TwistWorkSpaceSlot pSlot,
                           TwistBufferKey *pKeyOut) {
    if (pKeyOut == nullptr) {
        return false;
    }

    if (TryMapLegacySaltSlotToKey(pSlot, pKeyOut)) {
        return true;
    }

    TwistDirectBuffer aDirectBuffer = TwistDirectBuffer::kInvalid;
    if (DirectBufferFromSlot(pSlot, &aDirectBuffer)) {
        *pKeyOut = TwistBufferKey::Direct(aDirectBuffer);
        return true;
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSaltPhase::kOrbiter, TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSaltPhase::kOrbiter, TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSaltPhase::kOrbiter, TwistSaltLane::kC);
            return true;
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSaltPhase::kOrbiter, TwistSaltLane::kD);
            return true;
        case TwistWorkSpaceSlot::kDerivedSaltUnwindA:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSaltPhase::kUnwind, TwistSaltLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDerivedSaltUnwindB:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSaltPhase::kUnwind, TwistSaltLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDerivedSaltUnwindC:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSaltPhase::kUnwind, TwistSaltLane::kC);
            return true;
        case TwistWorkSpaceSlot::kDerivedSaltUnwindD:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSaltPhase::kUnwind, TwistSaltLane::kD);
            return true;

        case TwistWorkSpaceSlot::kDerivedSBoxA:
            *pKeyOut = TwistBufferKey::SBox(TwistSBoxOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSBoxLane::kA);
            return true;
        case TwistWorkSpaceSlot::kDerivedSBoxB:
            *pKeyOut = TwistBufferKey::SBox(TwistSBoxOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSBoxLane::kB);
            return true;
        case TwistWorkSpaceSlot::kDerivedSBoxC:
            *pKeyOut = TwistBufferKey::SBox(TwistSBoxOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSBoxLane::kC);
            return true;
        case TwistWorkSpaceSlot::kDerivedSBoxD:
            *pKeyOut = TwistBufferKey::SBox(TwistSBoxOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSBoxLane::kD);
            return true;
        case TwistWorkSpaceSlot::kDerivedSBoxE:
            *pKeyOut = TwistBufferKey::SBox(TwistSBoxOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSBoxLane::kE);
            return true;
        case TwistWorkSpaceSlot::kDerivedSBoxF:
            *pKeyOut = TwistBufferKey::SBox(TwistSBoxOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSBoxLane::kF);
            return true;
        case TwistWorkSpaceSlot::kDerivedSBoxG:
            *pKeyOut = TwistBufferKey::SBox(TwistSBoxOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSBoxLane::kG);
            return true;
        case TwistWorkSpaceSlot::kDerivedSBoxH:
            *pKeyOut = TwistBufferKey::SBox(TwistSBoxOwner::kLocal, TwistDomainFamily::kWorkLane, TwistSBoxLane::kH);
            return true;

        default:
            return false;
    }
}

} // namespace

TwistWorkSpace::TwistWorkSpace() {
    std::memset(this, 0, sizeof(*this));
}

void TwistWorkSpace::ShiftKeyBoxA(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox + (H_KEY_A - 1) * W_KEY_A;
    std::uint8_t *aSource = aDest - W_KEY_A;
    for (int i = 0; i < (H_KEY_A - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_A);
        aDest = aSource;
        aSource = aDest - W_KEY_A;
    }
}

void TwistWorkSpace::ShiftKeyBoxB(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = pBox + W_KEY_B;
    for (int i = 0; i < (H_KEY_B - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_B);
        aDest = aSource;
        aSource = aDest + W_KEY_B;
    }
}

void TwistWorkSpace::ShiftMaskBoxA(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = pBox + W_MASK_A;
    for (int i = 0; i < (H_MASK_A - 1); i++) {
        std::memcpy(aDest, aSource, W_MASK_A);
        aDest = aSource;
        aSource = aDest + W_MASK_A;
    }
}

void TwistWorkSpace::ShiftMaskBoxB(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = pBox + W_MASK_B;
    for (int i = 0; i < (H_MASK_B - 1); i++) {
        std::memcpy(aDest, aSource, W_MASK_B);
        aDest = aSource;
        aSource = aDest + W_MASK_B;
    }
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkspace,
                                        TwistExpander *pExpander,
                                        TwistWorkSpaceSlot pSlot) {
    if (pWorkspace == nullptr) {
        return nullptr;
    }

    TwistBufferKey aMappedKey;
    if (TryLegacySlotToBufferKey(pSlot, &aMappedKey)) {
        return GetBuffer(pWorkspace, pExpander, aMappedKey);
    }

    if (pExpander == nullptr) {
        switch (pSlot) {
            case TwistWorkSpaceSlot::kSource:
            case TwistWorkSpaceSlot::kDest:
            case TwistWorkSpaceSlot::kDomainSaltKeyBoxA:
            case TwistWorkSpaceSlot::kDomainSaltKeyBoxB:
            case TwistWorkSpaceSlot::kDomainSaltKeyBoxC:
            case TwistWorkSpaceSlot::kDomainSaltKeyBoxD:
            case TwistWorkSpaceSlot::kDomainSaltKeyBoxE:
            
            case TwistWorkSpaceSlot::kDomainSaltMaskBoxA:
            case TwistWorkSpaceSlot::kDomainSaltMaskBoxB:
            case TwistWorkSpaceSlot::kDomainSaltMaskBoxC:
            case TwistWorkSpaceSlot::kDomainSaltMaskBoxD:
            case TwistWorkSpaceSlot::kDomainSaltMaskBoxE:
            case TwistWorkSpaceSlot::kDomainSaltMaskBoxF:
            case TwistWorkSpaceSlot::kDomainSaltUnwindA:
            case TwistWorkSpaceSlot::kDomainSaltUnwindB:
            case TwistWorkSpaceSlot::kDomainSaltUnwindC:
            case TwistWorkSpaceSlot::kDomainSaltUnwindD:
            case TwistWorkSpaceSlot::kDomainSaltUnwindE:
            case TwistWorkSpaceSlot::kDomainSaltUnwindF:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterA:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterB:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterC:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterD:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterE:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterF:
            case TwistWorkSpaceSlot::kDomainSaltPrismA:
            case TwistWorkSpaceSlot::kDomainSaltPrismB:
            case TwistWorkSpaceSlot::kDomainSaltPrismC:
            case TwistWorkSpaceSlot::kDomainSaltPrismD:
            case TwistWorkSpaceSlot::kDomainSaltPrismE:
            case TwistWorkSpaceSlot::kDomainSaltPrismF:
            case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitA:
            case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitB:
            case TwistWorkSpaceSlot::kParamDomainSaltOrbiterC:
            case TwistWorkSpaceSlot::kParamDomainSaltOrbiterD:
            case TwistWorkSpaceSlot::kParamDomainSaltUnwindE:
            case TwistWorkSpaceSlot::kParamDomainSaltUnwindF:
            case TwistWorkSpaceSlot::kParamDomainSBoxA:
            case TwistWorkSpaceSlot::kParamDomainSBoxB:
            case TwistWorkSpaceSlot::kParamDomainSBoxC:
            case TwistWorkSpaceSlot::kParamDomainSBoxD:
            case TwistWorkSpaceSlot::kParamDomainSBoxE:
            case TwistWorkSpaceSlot::kParamDomainSBoxF:
            case TwistWorkSpaceSlot::kParamDomainSBoxG:
            case TwistWorkSpaceSlot::kParamDomainSBoxH:
            case TwistWorkSpaceSlot::kIndexList256A:
            case TwistWorkSpaceSlot::kIndexList256B:
            case TwistWorkSpaceSlot::kIndexList256C:
            case TwistWorkSpaceSlot::kIndexList256D:
                return nullptr;
            default:
                break;
        }
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return pExpander->mSource;
        case TwistWorkSpaceSlot::kDest: return pExpander->mDest;
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitA:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(pExpander->mActiveSaltSet, TwistSaltPhase::kOrbiterInit),
                            TwistSaltLane::kA)
            );
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitB:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(pExpander->mActiveSaltSet, TwistSaltPhase::kOrbiterInit),
                            TwistSaltLane::kB)
            );
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterC:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(pExpander->mActiveSaltSet, TwistSaltPhase::kOrbiter),
                            TwistSaltLane::kC)
            );
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterD:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(pExpander->mActiveSaltSet, TwistSaltPhase::kOrbiter),
                            TwistSaltLane::kD)
            );
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindE:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(pExpander->mActiveSaltSet, TwistSaltPhase::kUnwind),
                            TwistSaltLane::kE)
            );
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindF:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(pExpander->mActiveSaltSet, TwistSaltPhase::kUnwind),
                            TwistSaltLane::kF)
            );
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(&pWorkspace->mDomainBundle.mWorkLaneSalts, TwistSaltPhase::kOrbiter),
                            TwistSaltLane::kA)
            );
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(&pWorkspace->mDomainBundle.mWorkLaneSalts, TwistSaltPhase::kOrbiter),
                            TwistSaltLane::kB)
            );
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(&pWorkspace->mDomainBundle.mWorkLaneSalts, TwistSaltPhase::kOrbiter),
                            TwistSaltLane::kC)
            );
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(&pWorkspace->mDomainBundle.mWorkLaneSalts, TwistSaltPhase::kOrbiter),
                            TwistSaltLane::kD)
            );
        case TwistWorkSpaceSlot::kDerivedSaltUnwindA:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(&pWorkspace->mDomainBundle.mWorkLaneSalts, TwistSaltPhase::kUnwind),
                            TwistSaltLane::kA)
            );
        case TwistWorkSpaceSlot::kDerivedSaltUnwindB:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(&pWorkspace->mDomainBundle.mWorkLaneSalts, TwistSaltPhase::kUnwind),
                            TwistSaltLane::kB)
            );
        case TwistWorkSpaceSlot::kDerivedSaltUnwindC:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(&pWorkspace->mDomainBundle.mWorkLaneSalts, TwistSaltPhase::kUnwind),
                            TwistSaltLane::kC)
            );
        case TwistWorkSpaceSlot::kDerivedSaltUnwindD:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltLane(GetPhaseMaterial(&pWorkspace->mDomainBundle.mWorkLaneSalts, TwistSaltPhase::kUnwind),
                            TwistSaltLane::kD)
            );
        case TwistWorkSpaceSlot::kParamDomainSBoxA:
            return (pExpander->mActiveSBoxSet != nullptr) ? pExpander->mActiveSBoxSet->mSBoxA : pExpander->mSBoxA;
        case TwistWorkSpaceSlot::kParamDomainSBoxB:
            return (pExpander->mActiveSBoxSet != nullptr) ? pExpander->mActiveSBoxSet->mSBoxB : pExpander->mSBoxB;
        case TwistWorkSpaceSlot::kParamDomainSBoxC:
            return (pExpander->mActiveSBoxSet != nullptr) ? pExpander->mActiveSBoxSet->mSBoxC : pExpander->mSBoxC;
        case TwistWorkSpaceSlot::kParamDomainSBoxD:
            return (pExpander->mActiveSBoxSet != nullptr) ? pExpander->mActiveSBoxSet->mSBoxD : pExpander->mSBoxD;
        case TwistWorkSpaceSlot::kParamDomainSBoxE:
            return (pExpander->mActiveSBoxSet != nullptr) ? pExpander->mActiveSBoxSet->mSBoxE : pExpander->mSBoxE;
        case TwistWorkSpaceSlot::kParamDomainSBoxF:
            return (pExpander->mActiveSBoxSet != nullptr) ? pExpander->mActiveSBoxSet->mSBoxF : pExpander->mSBoxF;
        case TwistWorkSpaceSlot::kParamDomainSBoxG:
            return (pExpander->mActiveSBoxSet != nullptr) ? pExpander->mActiveSBoxSet->mSBoxG : pExpander->mSBoxG;
        case TwistWorkSpaceSlot::kParamDomainSBoxH:
            return (pExpander->mActiveSBoxSet != nullptr) ? pExpander->mActiveSBoxSet->mSBoxH : pExpander->mSBoxH;
        case TwistWorkSpaceSlot::kDerivedSBoxA: return pWorkspace->mDomainBundle.mWorkLaneSBoxes.mSBoxA;
        case TwistWorkSpaceSlot::kDerivedSBoxB: return pWorkspace->mDomainBundle.mWorkLaneSBoxes.mSBoxB;
        case TwistWorkSpaceSlot::kDerivedSBoxC: return pWorkspace->mDomainBundle.mWorkLaneSBoxes.mSBoxC;
        case TwistWorkSpaceSlot::kDerivedSBoxD: return pWorkspace->mDomainBundle.mWorkLaneSBoxes.mSBoxD;
        case TwistWorkSpaceSlot::kDerivedSBoxE: return pWorkspace->mDomainBundle.mWorkLaneSBoxes.mSBoxE;
        case TwistWorkSpaceSlot::kDerivedSBoxF: return pWorkspace->mDomainBundle.mWorkLaneSBoxes.mSBoxF;
        case TwistWorkSpaceSlot::kDerivedSBoxG: return pWorkspace->mDomainBundle.mWorkLaneSBoxes.mSBoxG;
        case TwistWorkSpaceSlot::kDerivedSBoxH: return pWorkspace->mDomainBundle.mWorkLaneSBoxes.mSBoxH;
        case TwistWorkSpaceSlot::kSeedExpansionLaneA: return pWorkspace->mExpandLaneA;
        case TwistWorkSpaceSlot::kSeedExpansionLaneB: return pWorkspace->mExpandLaneB;
        case TwistWorkSpaceSlot::kSeedExpansionLaneC: return pWorkspace->mExpandLaneC;
        case TwistWorkSpaceSlot::kSeedExpansionLaneD: return pWorkspace->mExpandLaneD;
        case TwistWorkSpaceSlot::kSeedExpansionLaneE: return pWorkspace->mExpandLaneE;
        case TwistWorkSpaceSlot::kSeedExpansionLaneF: return pWorkspace->mExpandLaneF;
        case TwistWorkSpaceSlot::kWorkLaneA: return pWorkspace->mWorkLaneA;
        case TwistWorkSpaceSlot::kWorkLaneB: return pWorkspace->mWorkLaneB;
        case TwistWorkSpaceSlot::kWorkLaneC: return pWorkspace->mWorkLaneC;
        case TwistWorkSpaceSlot::kWorkLaneD: return pWorkspace->mWorkLaneD;
        case TwistWorkSpaceSlot::kWorkLaneE: return pWorkspace->mWorkLaneE;
        case TwistWorkSpaceSlot::kWorkLaneF: return pWorkspace->mWorkLaneF;
        case TwistWorkSpaceSlot::kOperationLaneA: return pWorkspace->mOperationLaneA;
        case TwistWorkSpaceSlot::kOperationLaneB: return pWorkspace->mOperationLaneB;
        case TwistWorkSpaceSlot::kOperationLaneC: return pWorkspace->mOperationLaneC;
        case TwistWorkSpaceSlot::kOperationLaneD: return pWorkspace->mOperationLaneD;
        case TwistWorkSpaceSlot::kOperationLaneE: return pWorkspace->mOperationLaneE;
        case TwistWorkSpaceSlot::kOperationLaneF: return pWorkspace->mOperationLaneF;
        case TwistWorkSpaceSlot::kMaskLaneA: return pWorkspace->mMaskLaneA;
        case TwistWorkSpaceSlot::kMaskLaneB: return pWorkspace->mMaskLaneB;
        case TwistWorkSpaceSlot::kIndexList256A: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256A);
        case TwistWorkSpaceSlot::kIndexList256B: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256B);
        case TwistWorkSpaceSlot::kIndexList256C: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256C);
        case TwistWorkSpaceSlot::kIndexList256D: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256D);
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return &(pWorkspace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return &(pWorkspace->mKeyBoxB[0][0]);
        case TwistWorkSpaceSlot::kKeyRowReadA: return &(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowReadB: return &(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteA: return &(pWorkspace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteB: return &(pWorkspace->mKeyBoxB[0][0]);
        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return &(pWorkspace->mMaskBoxA[0][0]);
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return &(pWorkspace->mMaskBoxB[0][0]);
        case TwistWorkSpaceSlot::kMaskRowReadA: return &(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]);
        case TwistWorkSpaceSlot::kMaskRowReadB: return &(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]);
        case TwistWorkSpaceSlot::kMaskRowWriteA: return &(pWorkspace->mMaskBoxA[0][0]);
        case TwistWorkSpaceSlot::kMaskRowWriteB: return &(pWorkspace->mMaskBoxB[0][0]);
            
        default:
            return pWorkspace->mWorkLaneA;
    }
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkspace,
                                        TwistWorkSpaceSlot pSlot) {
    return GetBuffer(pWorkspace, nullptr, pSlot);
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkspace,
                                        TwistExpander *pExpander,
                                        TwistBufferKey pKey) {
    if (!pKey.IsValid()) {
        return nullptr;
    }

    if (pKey.IsDirect()) {
        switch (pKey.mDirect) {
            case TwistDirectBuffer::kSource:
                return pExpander ? pExpander->mSource : nullptr;
            case TwistDirectBuffer::kDest:
                return pExpander ? pExpander->mDest : nullptr;
            case TwistDirectBuffer::kIndexList256A:
                return pExpander ? reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256A) : nullptr;
            case TwistDirectBuffer::kIndexList256B:
                return pExpander ? reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256B) : nullptr;
            case TwistDirectBuffer::kIndexList256C:
                return pExpander ? reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256C) : nullptr;
            case TwistDirectBuffer::kIndexList256D:
                return pExpander ? reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256D) : nullptr;
            case TwistDirectBuffer::kExpansionLaneA:
                return pWorkspace ? pWorkspace->mExpandLaneA : nullptr;
            case TwistDirectBuffer::kExpansionLaneB:
                return pWorkspace ? pWorkspace->mExpandLaneB : nullptr;
            case TwistDirectBuffer::kExpansionLaneC:
                return pWorkspace ? pWorkspace->mExpandLaneC : nullptr;
            case TwistDirectBuffer::kExpansionLaneD:
                return pWorkspace ? pWorkspace->mExpandLaneD : nullptr;
            case TwistDirectBuffer::kExpansionLaneE:
                return pWorkspace ? pWorkspace->mExpandLaneE : nullptr;
            case TwistDirectBuffer::kExpansionLaneF:
                return pWorkspace ? pWorkspace->mExpandLaneF : nullptr;
            case TwistDirectBuffer::kWorkLaneA:
                return pWorkspace ? pWorkspace->mWorkLaneA : nullptr;
            case TwistDirectBuffer::kWorkLaneB:
                return pWorkspace ? pWorkspace->mWorkLaneB : nullptr;
            case TwistDirectBuffer::kWorkLaneC:
                return pWorkspace ? pWorkspace->mWorkLaneC : nullptr;
            case TwistDirectBuffer::kWorkLaneD:
                return pWorkspace ? pWorkspace->mWorkLaneD : nullptr;
            case TwistDirectBuffer::kWorkLaneE:
                return pWorkspace ? pWorkspace->mWorkLaneE : nullptr;
            case TwistDirectBuffer::kWorkLaneF:
                return pWorkspace ? pWorkspace->mWorkLaneF : nullptr;
            case TwistDirectBuffer::kOperationLaneA:
                return pWorkspace ? pWorkspace->mOperationLaneA : nullptr;
            case TwistDirectBuffer::kOperationLaneB:
                return pWorkspace ? pWorkspace->mOperationLaneB : nullptr;
            case TwistDirectBuffer::kOperationLaneC:
                return pWorkspace ? pWorkspace->mOperationLaneC : nullptr;
            case TwistDirectBuffer::kOperationLaneD:
                return pWorkspace ? pWorkspace->mOperationLaneD : nullptr;
            case TwistDirectBuffer::kOperationLaneE:
                return pWorkspace ? pWorkspace->mOperationLaneE : nullptr;
            case TwistDirectBuffer::kOperationLaneF:
                return pWorkspace ? pWorkspace->mOperationLaneF : nullptr;
            case TwistDirectBuffer::kMaskLaneA:
                return pWorkspace ? pWorkspace->mMaskLaneA : nullptr;
            case TwistDirectBuffer::kMaskLaneB:
                return pWorkspace ? pWorkspace->mMaskLaneB : nullptr;
            case TwistDirectBuffer::kKeyBoxUnrolledA:
                return pWorkspace ? &(pWorkspace->mKeyBoxA[0][0]) : nullptr;
            case TwistDirectBuffer::kKeyBoxUnrolledB:
                return pWorkspace ? &(pWorkspace->mKeyBoxB[0][0]) : nullptr;
            case TwistDirectBuffer::kKeyRowReadA:
                return pWorkspace ? &(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]) : nullptr;
            case TwistDirectBuffer::kKeyRowReadB:
                return pWorkspace ? &(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]) : nullptr;
            case TwistDirectBuffer::kKeyRowWriteA:
                return pWorkspace ? &(pWorkspace->mKeyBoxA[0][0]) : nullptr;
            case TwistDirectBuffer::kKeyRowWriteB:
                return pWorkspace ? &(pWorkspace->mKeyBoxB[0][0]) : nullptr;
            case TwistDirectBuffer::kMaskBoxUnrolledA:
                return pWorkspace ? &(pWorkspace->mMaskBoxA[0][0]) : nullptr;
            case TwistDirectBuffer::kMaskBoxUnrolledB:
                return pWorkspace ? &(pWorkspace->mMaskBoxB[0][0]) : nullptr;
            case TwistDirectBuffer::kMaskRowReadA:
                return pWorkspace ? &(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]) : nullptr;
            case TwistDirectBuffer::kMaskRowReadB:
                return pWorkspace ? &(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]) : nullptr;
            case TwistDirectBuffer::kMaskRowWriteA:
                return pWorkspace ? &(pWorkspace->mMaskBoxA[0][0]) : nullptr;
            case TwistDirectBuffer::kMaskRowWriteB:
                return pWorkspace ? &(pWorkspace->mMaskBoxB[0][0]) : nullptr;
            default:
                return nullptr;
        }
    }

    if (pKey.IsSalt()) {
        TwistDomainBundle *aBundle = GetSaltDomainBundle(pWorkspace, pExpander, pKey.mSaltOwner);
        TwistDomainSaltSet *aSet = GetSaltSet(aBundle, pKey.mDomain);
        TwistDomainSeedRoundMaterial *aMaterial = GetPhaseMaterial(aSet, pKey.mSaltPhase);
        std::uint64_t *aLane = GetSaltLane(aMaterial, pKey.mSaltLane);
        return reinterpret_cast<std::uint8_t *>(aLane);
    }

    if (pKey.IsSBox()) {
        TwistDomainBundle *aBundle = GetSBoxDomainBundle(pWorkspace, pExpander, pKey.mSBoxOwner);
        TwistDomainSBoxSet *aSet = GetSBoxSet(aBundle, pKey.mDomain);
        return GetSBoxLane(aSet, pKey.mSBoxLane);
    }

    if (pKey.IsConstants()) {
        TwistDomainBundle *aBundle = GetSaltDomainBundle(pWorkspace, pExpander, pKey.mSaltOwner);
        TwistDomainConstants *aConstants = GetDomainConstants(aBundle, pKey.mDomain);
        return reinterpret_cast<std::uint8_t *>(aConstants);
    }

    return nullptr;
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkspace,
                                        TwistBufferKey pKey) {
    return GetBuffer(pWorkspace, nullptr, pKey);
}

bool TwistWorkSpace::TryLegacySlotToBufferKey(TwistWorkSpaceSlot pSlot,
                                              TwistBufferKey *pKeyOut) {
    return TryMapLegacySlotToKey(pSlot, pKeyOut);
}

int TwistWorkSpace::GetBufferLength(TwistWorkSpaceSlot pSlot) {
    TwistBufferKey aMappedKey;
    if (TryLegacySlotToBufferKey(pSlot, &aMappedKey)) {
        return GetBufferLength(aMappedKey);
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return S_KEY_A;
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return S_KEY_B;
        case TwistWorkSpaceSlot::kKeyRowReadA:
        case TwistWorkSpaceSlot::kKeyRowWriteA: return W_KEY_A;
        case TwistWorkSpaceSlot::kKeyRowReadB:
        case TwistWorkSpaceSlot::kKeyRowWriteB: return W_KEY_B;
        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return S_MASK_A;
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return S_MASK_B;
        case TwistWorkSpaceSlot::kMaskRowReadA:
        case TwistWorkSpaceSlot::kMaskRowWriteA: return W_MASK_A;
        case TwistWorkSpaceSlot::kMaskRowReadB:
        case TwistWorkSpaceSlot::kMaskRowWriteB: return W_MASK_B;

        case TwistWorkSpaceSlot::kParamDomainSBoxA:
        case TwistWorkSpaceSlot::kParamDomainSBoxB:
        case TwistWorkSpaceSlot::kParamDomainSBoxC:
        case TwistWorkSpaceSlot::kParamDomainSBoxD:
        case TwistWorkSpaceSlot::kParamDomainSBoxE:
        case TwistWorkSpaceSlot::kParamDomainSBoxF:
        case TwistWorkSpaceSlot::kParamDomainSBoxG:
        case TwistWorkSpaceSlot::kParamDomainSBoxH:
        case TwistWorkSpaceSlot::kDerivedSBoxA:
        case TwistWorkSpaceSlot::kDerivedSBoxB:
        case TwistWorkSpaceSlot::kDerivedSBoxC:
        case TwistWorkSpaceSlot::kDerivedSBoxD:
        case TwistWorkSpaceSlot::kDerivedSBoxE:
        case TwistWorkSpaceSlot::kDerivedSBoxF:
        case TwistWorkSpaceSlot::kDerivedSBoxG:
        case TwistWorkSpaceSlot::kDerivedSBoxH:
            return S_SBOX;

        case TwistWorkSpaceSlot::kDomainSaltKeyBoxA:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxB:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxC:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxD:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxE:
        
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxA:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxB:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxC:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxD:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxE:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxF:
        case TwistWorkSpaceSlot::kDomainSaltUnwindA:
        case TwistWorkSpaceSlot::kDomainSaltUnwindB:
        case TwistWorkSpaceSlot::kDomainSaltUnwindC:
        case TwistWorkSpaceSlot::kDomainSaltUnwindD:
        case TwistWorkSpaceSlot::kDomainSaltUnwindE:
        case TwistWorkSpaceSlot::kDomainSaltUnwindF:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterA:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterB:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterC:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterD:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterE:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterF:
        case TwistWorkSpaceSlot::kDomainSaltPrismA:
        case TwistWorkSpaceSlot::kDomainSaltPrismB:
        case TwistWorkSpaceSlot::kDomainSaltPrismC:
        case TwistWorkSpaceSlot::kDomainSaltPrismD:
        case TwistWorkSpaceSlot::kDomainSaltPrismE:
        case TwistWorkSpaceSlot::kDomainSaltPrismF:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitA:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitB:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterC:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterD:
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindE:
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindF:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD:
        case TwistWorkSpaceSlot::kDerivedSaltUnwindA:
        case TwistWorkSpaceSlot::kDerivedSaltUnwindB:
        case TwistWorkSpaceSlot::kDerivedSaltUnwindC:
        case TwistWorkSpaceSlot::kDerivedSaltUnwindD:
            return S_SALT;
        case TwistWorkSpaceSlot::kIndexList256A:
        case TwistWorkSpaceSlot::kIndexList256B:
        case TwistWorkSpaceSlot::kIndexList256C:
        case TwistWorkSpaceSlot::kIndexList256D:
            return static_cast<int>(256U * sizeof(std::size_t));

        default:
            return S_BLOCK;
    }
}

int TwistWorkSpace::GetBufferLength(TwistBufferKey pKey) {
    switch (pKey.mKind) {
        case TwistBufferKind::kSalt:
            return static_cast<int>(S_SALT * sizeof(std::uint64_t));

        case TwistBufferKind::kSBox:
            return S_SBOX;

        case TwistBufferKind::kConstants:
            return static_cast<int>(sizeof(TwistDomainConstants));

        case TwistBufferKind::kDirect: {
            switch (pKey.mDirect) {
                case TwistDirectBuffer::kIndexList256A:
                case TwistDirectBuffer::kIndexList256B:
                case TwistDirectBuffer::kIndexList256C:
                case TwistDirectBuffer::kIndexList256D:
                    return static_cast<int>(256U * sizeof(std::size_t));

                case TwistDirectBuffer::kKeyBoxUnrolledA:
                    return S_KEY_A;
                case TwistDirectBuffer::kKeyBoxUnrolledB:
                    return S_KEY_B;
                case TwistDirectBuffer::kKeyRowReadA:
                case TwistDirectBuffer::kKeyRowWriteA:
                    return W_KEY_A;
                case TwistDirectBuffer::kKeyRowReadB:
                case TwistDirectBuffer::kKeyRowWriteB:
                    return W_KEY_B;

                case TwistDirectBuffer::kMaskBoxUnrolledA:
                    return S_MASK_A;
                case TwistDirectBuffer::kMaskBoxUnrolledB:
                    return S_MASK_B;
                case TwistDirectBuffer::kMaskRowReadA:
                case TwistDirectBuffer::kMaskRowWriteA:
                    return W_MASK_A;
                case TwistDirectBuffer::kMaskRowReadB:
                case TwistDirectBuffer::kMaskRowWriteB:
                    return W_MASK_B;

                default:
                    return S_BLOCK;
            }
        }

        default:
            return 0;
    }
}

bool TwistWorkSpace::IsSBox(TwistWorkSpaceSlot pSlot) {
    TwistBufferKey aMappedKey;
    if (TryLegacySlotToBufferKey(pSlot, &aMappedKey)) {
        return IsSBox(aMappedKey);
    }
    switch (pSlot) {
        case TwistWorkSpaceSlot::kParamDomainSBoxA:
        case TwistWorkSpaceSlot::kParamDomainSBoxB:
        case TwistWorkSpaceSlot::kParamDomainSBoxC:
        case TwistWorkSpaceSlot::kParamDomainSBoxD:
        case TwistWorkSpaceSlot::kParamDomainSBoxE:
        case TwistWorkSpaceSlot::kParamDomainSBoxF:
        case TwistWorkSpaceSlot::kParamDomainSBoxG:
        case TwistWorkSpaceSlot::kParamDomainSBoxH:
            return true;
        default:
            return false;
    }
}

bool TwistWorkSpace::IsSBox(TwistBufferKey pKey) {
    return pKey.mKind == TwistBufferKind::kSBox;
}

bool TwistWorkSpace::IsSalt(TwistWorkSpaceSlot pSlot) {
    TwistBufferKey aMappedKey;
    if (TryLegacySlotToBufferKey(pSlot, &aMappedKey)) {
        return IsSalt(aMappedKey);
    }
    switch (pSlot) {
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitA:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitB:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterC:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterD:
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindE:
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindF:
            return true;
        default:
            return false;
    }
}

bool TwistWorkSpace::IsSalt(TwistBufferKey pKey) {
    return pKey.mKind == TwistBufferKind::kSalt;
}
