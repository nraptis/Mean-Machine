//
//  TwistWorkSpace.cpp
//  Gorgon
//

#include "TwistWorkSpace.hpp"
#include "TwistExpander.hpp"
#include <cstring>

inline TwistBufferKey TwistBufferKey::Salt(TwistSaltOwner pOwner,
                                           TwistDomain pDomain,
                                           TwistWorkSpaceSlot pSlot) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kSalt;
    aKey.mSaltOwner = pOwner;
    aKey.mDomain = pDomain;
    aKey.mSlot = static_cast<std::uint16_t>(pSlot);
    return aKey;
}

inline TwistBufferKey TwistBufferKey::SBox(TwistSBoxOwner pOwner,
                                           TwistDomain pDomain,
                                           TwistSBoxLane pLane) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kSBox;
    aKey.mSBoxOwner = pOwner;
    aKey.mDomain = pDomain;
    aKey.mSBoxLane = pLane;
    return aKey;
}

inline TwistBufferKey TwistBufferKey::Constants(TwistSaltOwner pOwner,
                                                TwistDomain pDomain) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kConstants;
    aKey.mSaltOwner = pOwner;
    aKey.mDomain = pDomain;
    return aKey;
}

inline bool TwistBufferKey::IsValid() const {
    return mKind != TwistBufferKind::kInvalid;
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

TwistDomainBundle *GetSaltDomainBundle(TwistExpander *pExpander,
                                       TwistSaltOwner pOwner) {
    switch (pOwner) {
        case TwistSaltOwner::kInbuilt:
            return pExpander ? &pExpander->mDomainBundleInbuilt : nullptr;
        case TwistSaltOwner::kEphemeral:
            return pExpander ? &pExpander->mDomainBundleEphemeral : nullptr;
        default:
            return nullptr;
    }
}

TwistDomainBundle *GetSBoxDomainBundle(TwistExpander *pExpander,
                                       TwistSBoxOwner pOwner) {
    switch (pOwner) {
        case TwistSBoxOwner::kInbuilt:
            return pExpander ? &pExpander->mDomainBundleInbuilt : nullptr;
        case TwistSBoxOwner::kEphemeral:
            return pExpander ? &pExpander->mDomainBundleEphemeral : nullptr;
        default:
            return nullptr;
    }
}

TwistDomainSaltSet *GetSaltSet(TwistDomainBundle *pBundle,
                               TwistDomain pDomain) {
    if (pBundle == nullptr) {
        return nullptr;
    }
    switch (pDomain) {
        case TwistDomain::kPhaseA: return &pBundle->mPhaseASalts;
        case TwistDomain::kPhaseB: return &pBundle->mPhaseBSalts;
        case TwistDomain::kPhaseC: return &pBundle->mPhaseCSalts;
        default: return nullptr;
    }
}

TwistDomainConstants *GetDomainConstants(TwistDomainBundle *pBundle,
                                         TwistDomain pDomain) {
    if (pBundle == nullptr) {
        return nullptr;
    }
    switch (pDomain) {
        case TwistDomain::kPhaseA: return &pBundle->mPhaseAConstants;
        case TwistDomain::kPhaseB: return &pBundle->mPhaseBConstants;
        case TwistDomain::kPhaseC: return &pBundle->mPhaseCConstants;
        default: return nullptr;
    }
}

TwistDomainSBoxSet *GetSBoxSet(TwistDomainBundle *pBundle,
                               TwistDomain pDomain) {
    if (pBundle == nullptr) {
        return nullptr;
    }
    switch (pDomain) {
        case TwistDomain::kPhaseA: return &pBundle->mPhaseASBoxes;
        case TwistDomain::kPhaseB: return &pBundle->mPhaseBSBoxes;
        case TwistDomain::kPhaseC: return &pBundle->mPhaseCSBoxes;
        default: return nullptr;
    }
}

std::uint64_t *GetSaltLane(TwistDomainSeedRoundMaterial *pMaterial,
                           int pLane) {
    if (pMaterial == nullptr) {
        return nullptr;
    }
    switch (pLane) {
        case 0: return pMaterial->mSaltA;
        case 1: return pMaterial->mSaltB;
        case 2: return pMaterial->mSaltC;
        case 3: return pMaterial->mSaltD;
        case 4: return pMaterial->mSaltE;
        case 5: return pMaterial->mSaltF;
        default: return nullptr;
    }
}

std::uint64_t *GetSaltSlot(TwistDomainSaltSet *pSet,
                           TwistWorkSpaceSlot pSlot) {
    if (pSet == nullptr) {
        return nullptr;
    }
    switch (pSlot) {
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxA:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxC:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxE:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxA:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxC:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxE:
            return GetSaltLane(&pSet->mOrbiterAssign, 0);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxB:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxD:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxB:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxD:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxF:
            return GetSaltLane(&pSet->mOrbiterAssign, 1);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC:
            return GetSaltLane(&pSet->mOrbiterAssign, 2);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD:
            return GetSaltLane(&pSet->mOrbiterAssign, 3);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE:
            return GetSaltLane(&pSet->mOrbiterAssign, 4);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF:
            return GetSaltLane(&pSet->mOrbiterAssign, 5);

        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateA:
        case TwistWorkSpaceSlot::kDomainSaltPrismA:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA:
            return GetSaltLane(&pSet->mOrbiterUpdate, 0);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateB:
        case TwistWorkSpaceSlot::kDomainSaltPrismB:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB:
            return GetSaltLane(&pSet->mOrbiterUpdate, 1);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateC:
        case TwistWorkSpaceSlot::kDomainSaltPrismC:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC:
            return GetSaltLane(&pSet->mOrbiterUpdate, 2);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateD:
        case TwistWorkSpaceSlot::kDomainSaltPrismD:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD:
            return GetSaltLane(&pSet->mOrbiterUpdate, 3);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateE:
        case TwistWorkSpaceSlot::kDomainSaltPrismE:
            return GetSaltLane(&pSet->mOrbiterUpdate, 4);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateF:
        case TwistWorkSpaceSlot::kDomainSaltPrismF:
            return GetSaltLane(&pSet->mOrbiterUpdate, 5);

        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateA:
        case TwistWorkSpaceSlot::kDerivedSaltWandererA:
            return GetSaltLane(&pSet->mWandererUpdate, 0);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateB:
        case TwistWorkSpaceSlot::kDerivedSaltWandererB:
            return GetSaltLane(&pSet->mWandererUpdate, 1);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateC:
        case TwistWorkSpaceSlot::kDerivedSaltWandererC:
            return GetSaltLane(&pSet->mWandererUpdate, 2);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateD:
        case TwistWorkSpaceSlot::kDerivedSaltWandererD:
            return GetSaltLane(&pSet->mWandererUpdate, 3);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateE:
            return GetSaltLane(&pSet->mWandererUpdate, 4);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateF:
            return GetSaltLane(&pSet->mWandererUpdate, 5);

        default:
            return nullptr;
    }
}

bool IsParamSaltSlot(TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF:
            return true;
        default:
            return false;
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
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxB:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxA:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxB:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateA:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateB:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateC:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateD:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateE:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateF:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateA:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateB:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateC:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateD:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateE:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateF:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt, TwistDomain::kPhaseA, pSlot);
            return true;

        case TwistWorkSpaceSlot::kDomainSaltKeyBoxC:
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxD:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxC:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxD:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxE:
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxF:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt, TwistDomain::kPhaseB, pSlot);
            return true;

        case TwistWorkSpaceSlot::kDomainSaltKeyBoxE:
        case TwistWorkSpaceSlot::kDomainSaltPrismA:
        case TwistWorkSpaceSlot::kDomainSaltPrismB:
        case TwistWorkSpaceSlot::kDomainSaltPrismC:
        case TwistWorkSpaceSlot::kDomainSaltPrismD:
        case TwistWorkSpaceSlot::kDomainSaltPrismE:
        case TwistWorkSpaceSlot::kDomainSaltPrismF:
            *pKeyOut = TwistBufferKey::Salt(TwistSaltOwner::kInbuilt, TwistDomain::kPhaseC, pSlot);
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

    return TryMapLegacySaltSlotToKey(pSlot, pKeyOut);
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
        if (IsParamSaltSlot(pSlot)) {
            return nullptr;
        }
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
            case TwistWorkSpaceSlot::kDomainSaltWandererUpdateA:
            case TwistWorkSpaceSlot::kDomainSaltWandererUpdateB:
            case TwistWorkSpaceSlot::kDomainSaltWandererUpdateC:
            case TwistWorkSpaceSlot::kDomainSaltWandererUpdateD:
            case TwistWorkSpaceSlot::kDomainSaltWandererUpdateE:
            case TwistWorkSpaceSlot::kDomainSaltWandererUpdateF:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateA:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateB:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateC:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateD:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateE:
            case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateF:
            case TwistWorkSpaceSlot::kDomainSaltPrismA:
            case TwistWorkSpaceSlot::kDomainSaltPrismB:
            case TwistWorkSpaceSlot::kDomainSaltPrismC:
            case TwistWorkSpaceSlot::kDomainSaltPrismD:
            case TwistWorkSpaceSlot::kDomainSaltPrismE:
            case TwistWorkSpaceSlot::kDomainSaltPrismF:
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
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD:
        case TwistWorkSpaceSlot::kDerivedSaltWandererA:
        case TwistWorkSpaceSlot::kDerivedSaltWandererB:
        case TwistWorkSpaceSlot::kDerivedSaltWandererC:
        case TwistWorkSpaceSlot::kDerivedSaltWandererD:
            return reinterpret_cast<std::uint8_t *>(
                GetSaltSlot(&pWorkspace->mDomainBundle.mPhaseASalts, pSlot)
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
        case TwistWorkSpaceSlot::kDerivedSBoxA: return pWorkspace->mDomainBundle.mPhaseASBoxes.mSBoxA;
        case TwistWorkSpaceSlot::kDerivedSBoxB: return pWorkspace->mDomainBundle.mPhaseASBoxes.mSBoxB;
        case TwistWorkSpaceSlot::kDerivedSBoxC: return pWorkspace->mDomainBundle.mPhaseASBoxes.mSBoxC;
        case TwistWorkSpaceSlot::kDerivedSBoxD: return pWorkspace->mDomainBundle.mPhaseASBoxes.mSBoxD;
        case TwistWorkSpaceSlot::kDerivedSBoxE: return pWorkspace->mDomainBundle.mPhaseASBoxes.mSBoxE;
        case TwistWorkSpaceSlot::kDerivedSBoxF: return pWorkspace->mDomainBundle.mPhaseASBoxes.mSBoxF;
        case TwistWorkSpaceSlot::kDerivedSBoxG: return pWorkspace->mDomainBundle.mPhaseASBoxes.mSBoxG;
        case TwistWorkSpaceSlot::kDerivedSBoxH: return pWorkspace->mDomainBundle.mPhaseASBoxes.mSBoxH;
        case TwistWorkSpaceSlot::kExpansionLaneA: return pWorkspace->mListExpansionLaneA;
        case TwistWorkSpaceSlot::kExpansionLaneB: return pWorkspace->mListExpansionLaneB;
        case TwistWorkSpaceSlot::kExpansionLaneC: return pWorkspace->mListExpansionLaneC;
        case TwistWorkSpaceSlot::kExpansionLaneD: return pWorkspace->mListExpansionLaneD;
        case TwistWorkSpaceSlot::kExpansionLaneE: return pWorkspace->mListExpansionLaneE;
        case TwistWorkSpaceSlot::kExpansionLaneF: return pWorkspace->mListExpansionLaneF;
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
        case TwistWorkSpaceSlot::kSnowLaneA: return pWorkspace->mSnowLaneA;
        case TwistWorkSpaceSlot::kSnowLaneB: return pWorkspace->mSnowLaneB;
        case TwistWorkSpaceSlot::kSnowLaneC: return pWorkspace->mSnowLaneC;
        case TwistWorkSpaceSlot::kSnowLaneD: return pWorkspace->mSnowLaneD;
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
            break;
    }

    if (IsParamSaltSlot(pSlot)) {
        return reinterpret_cast<std::uint8_t *>(
            GetSaltSlot(pExpander->mActiveSaltSet, pSlot)
        );
    }

    return pWorkspace->mWorkLaneA;
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

    if (pKey.IsSalt()) {
        TwistDomainBundle *aBundle = GetSaltDomainBundle(pExpander, pKey.mSaltOwner);
        TwistDomainSaltSet *aSet = GetSaltSet(aBundle, pKey.mDomain);
        std::uint64_t *aLane = GetSaltSlot(aSet, static_cast<TwistWorkSpaceSlot>(pKey.mSlot));
        return reinterpret_cast<std::uint8_t *>(aLane);
    }

    if (pKey.IsSBox()) {
        TwistDomainBundle *aBundle = GetSBoxDomainBundle(pExpander, pKey.mSBoxOwner);
        TwistDomainSBoxSet *aSet = GetSBoxSet(aBundle, pKey.mDomain);
        return GetSBoxLane(aSet, pKey.mSBoxLane);
    }

    if (pKey.IsConstants()) {
        TwistDomainBundle *aBundle = GetSaltDomainBundle(pExpander, pKey.mSaltOwner);
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

    if (IsParamSaltSlot(pSlot)) {
        return S_SALT;
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
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateA:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateB:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateC:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateD:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateE:
        case TwistWorkSpaceSlot::kDomainSaltWandererUpdateF:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateA:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateB:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateC:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateD:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateE:
        case TwistWorkSpaceSlot::kDomainSaltOrbiterUpdateF:
        case TwistWorkSpaceSlot::kDomainSaltPrismA:
        case TwistWorkSpaceSlot::kDomainSaltPrismB:
        case TwistWorkSpaceSlot::kDomainSaltPrismC:
        case TwistWorkSpaceSlot::kDomainSaltPrismD:
        case TwistWorkSpaceSlot::kDomainSaltPrismE:
        case TwistWorkSpaceSlot::kDomainSaltPrismF:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD:
        case TwistWorkSpaceSlot::kDerivedSaltWandererA:
        case TwistWorkSpaceSlot::kDerivedSaltWandererB:
        case TwistWorkSpaceSlot::kDerivedSaltWandererC:
        case TwistWorkSpaceSlot::kDerivedSaltWandererD:
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
        case TwistWorkSpaceSlot::kDerivedSBoxA:
        case TwistWorkSpaceSlot::kDerivedSBoxB:
        case TwistWorkSpaceSlot::kDerivedSBoxC:
        case TwistWorkSpaceSlot::kDerivedSBoxD:
        case TwistWorkSpaceSlot::kDerivedSBoxE:
        case TwistWorkSpaceSlot::kDerivedSBoxF:
        case TwistWorkSpaceSlot::kDerivedSBoxG:
        case TwistWorkSpaceSlot::kDerivedSBoxH:
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
    if (IsParamSaltSlot(pSlot)) {
        return true;
    }
    switch (pSlot) {
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC:
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD:
        case TwistWorkSpaceSlot::kDerivedSaltWandererA:
        case TwistWorkSpaceSlot::kDerivedSaltWandererB:
        case TwistWorkSpaceSlot::kDerivedSaltWandererC:
        case TwistWorkSpaceSlot::kDerivedSaltWandererD:
            return true;
        default:
            return false;
    }
}

bool TwistWorkSpace::IsSalt(TwistBufferKey pKey) {
    return pKey.mKind == TwistBufferKind::kSalt;
}
