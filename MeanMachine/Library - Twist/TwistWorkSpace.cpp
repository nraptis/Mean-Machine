//
//  TwistWorkSpace.cpp
//  Gorgon
//

#include "TwistWorkSpace.hpp"
#include "TwistExpander.hpp"
#include <cstring>

TwistBufferKey TwistBufferKey::Salt(TwistSaltOwner pOwner,
                                    TwistDomain pDomain,
                                    TwistWorkSpaceSlot pSlot) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kSalt;
    aKey.mSaltOwner = pOwner;
    aKey.mDomain = pDomain;
    aKey.mSlot = static_cast<std::uint16_t>(pSlot);
    return aKey;
}

TwistBufferKey TwistBufferKey::Constants(TwistSaltOwner pOwner,
                                         TwistDomain pDomain) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kConstants;
    aKey.mSaltOwner = pOwner;
    aKey.mDomain = pDomain;
    return aKey;
}

bool TwistBufferKey::IsValid() const {
    return mKind != TwistBufferKind::kInvalid;
}

bool TwistBufferKey::IsSalt() const {
    return mKind == TwistBufferKind::kSalt;
}

bool TwistBufferKey::IsConstants() const {
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
            return GetSaltLane(&pSet->mOrbiterAssign, 0);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB:
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
            return GetSaltLane(&pSet->mOrbiterUpdate, 0);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB:
            return GetSaltLane(&pSet->mOrbiterUpdate, 1);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC:
            return GetSaltLane(&pSet->mOrbiterUpdate, 2);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD:
            return GetSaltLane(&pSet->mOrbiterUpdate, 3);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE:
            return GetSaltLane(&pSet->mOrbiterUpdate, 4);
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF:
            return GetSaltLane(&pSet->mOrbiterUpdate, 5);

        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA:
            return GetSaltLane(&pSet->mWandererUpdate, 0);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB:
            return GetSaltLane(&pSet->mWandererUpdate, 1);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC:
            return GetSaltLane(&pSet->mWandererUpdate, 2);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD:
            return GetSaltLane(&pSet->mWandererUpdate, 3);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE:
            return GetSaltLane(&pSet->mWandererUpdate, 4);
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF:
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

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkSpace,
                                        TwistExpander *pExpander,
                                        TwistWorkSpaceSlot pSlot) {
    if (pWorkSpace == nullptr) {
        return nullptr;
    }

    TwistBufferKey aMappedKey;
    if (TryLegacySlotToBufferKey(pSlot, &aMappedKey)) {
        return GetBuffer(pWorkSpace, pExpander, aMappedKey);
    }

    if (pExpander == nullptr) {
        if (IsParamSaltSlot(pSlot)) {
            return nullptr;
        }
        switch (pSlot) {
            case TwistWorkSpaceSlot::kSource:
            case TwistWorkSpaceSlot::kDest:
            case TwistWorkSpaceSlot::kSnow:
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
        case TwistWorkSpaceSlot::kSnow: return pExpander->mSnow;
        case TwistWorkSpaceSlot::kExpansionLaneA: return pWorkSpace->mExpansionLaneA;
        case TwistWorkSpaceSlot::kExpansionLaneB: return pWorkSpace->mExpansionLaneB;
        case TwistWorkSpaceSlot::kExpansionLaneC: return pWorkSpace->mExpansionLaneC;
        case TwistWorkSpaceSlot::kExpansionLaneD: return pWorkSpace->mExpansionLaneD;
        case TwistWorkSpaceSlot::kWorkLaneA: return pWorkSpace->mWorkLaneA;
        case TwistWorkSpaceSlot::kWorkLaneB: return pWorkSpace->mWorkLaneB;
        case TwistWorkSpaceSlot::kWorkLaneC: return pWorkSpace->mWorkLaneC;
        case TwistWorkSpaceSlot::kWorkLaneD: return pWorkSpace->mWorkLaneD;
        case TwistWorkSpaceSlot::kOperationLaneA: return pWorkSpace->mOperationLaneA;
        case TwistWorkSpaceSlot::kOperationLaneB: return pWorkSpace->mOperationLaneB;
        case TwistWorkSpaceSlot::kOperationLaneC: return pWorkSpace->mOperationLaneC;
        case TwistWorkSpaceSlot::kOperationLaneD: return pWorkSpace->mOperationLaneD;
        case TwistWorkSpaceSlot::kSnowLaneA: return pWorkSpace->mSnowLaneA;
        case TwistWorkSpaceSlot::kSnowLaneB: return pWorkSpace->mSnowLaneB;
        case TwistWorkSpaceSlot::kSnowLaneC: return pWorkSpace->mSnowLaneC;
        case TwistWorkSpaceSlot::kSnowLaneD: return pWorkSpace->mSnowLaneD;
        case TwistWorkSpaceSlot::kIndexList256A: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256A);
        case TwistWorkSpaceSlot::kIndexList256B: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256B);
        case TwistWorkSpaceSlot::kIndexList256C: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256C);
        case TwistWorkSpaceSlot::kIndexList256D: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256D);
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return &(pWorkSpace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return &(pWorkSpace->mKeyBoxB[0][0]);
        case TwistWorkSpaceSlot::kKeyRowReadA: return &(pWorkSpace->mKeyBoxA[H_KEY_A - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowReadB: return &(pWorkSpace->mKeyBoxB[H_KEY_B - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteA: return &(pWorkSpace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteB: return &(pWorkSpace->mKeyBoxB[0][0]);
        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return &(pWorkSpace->mMaskBoxA[0][0]);
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return &(pWorkSpace->mMaskBoxB[0][0]);
        case TwistWorkSpaceSlot::kMaskRowReadA: return &(pWorkSpace->mMaskBoxA[H_MASK_A - 1][0]);
        case TwistWorkSpaceSlot::kMaskRowReadB: return &(pWorkSpace->mMaskBoxB[H_MASK_B - 1][0]);
        case TwistWorkSpaceSlot::kMaskRowWriteA: return &(pWorkSpace->mMaskBoxA[0][0]);
        case TwistWorkSpaceSlot::kMaskRowWriteB: return &(pWorkSpace->mMaskBoxB[0][0]);
            
        default:
            break;
    }

    if (IsParamSaltSlot(pSlot)) {
        return reinterpret_cast<std::uint8_t *>(
            GetSaltSlot(pExpander->mActiveSaltSet, pSlot)
        );
    }

    return pWorkSpace->mWorkLaneA;
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkSpace,
                                        TwistWorkSpaceSlot pSlot) {
    return GetBuffer(pWorkSpace, nullptr, pSlot);
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkSpace,
                                        TwistExpander *pExpander,
                                        TwistBufferKey pKey) {
    (void)pWorkSpace;
    if (!pKey.IsValid()) {
        return nullptr;
    }

    if (pKey.IsSalt()) {
        TwistDomainBundle *aBundle = GetSaltDomainBundle(pExpander, pKey.mSaltOwner);
        TwistDomainSaltSet *aSet = GetSaltSet(aBundle, pKey.mDomain);
        std::uint64_t *aLane = GetSaltSlot(aSet, static_cast<TwistWorkSpaceSlot>(pKey.mSlot));
        return reinterpret_cast<std::uint8_t *>(aLane);
    }

    if (pKey.IsConstants()) {
        TwistDomainBundle *aBundle = GetSaltDomainBundle(pExpander, pKey.mSaltOwner);
        TwistDomainConstants *aConstants = GetDomainConstants(aBundle, pKey.mDomain);
        return reinterpret_cast<std::uint8_t *>(aConstants);
    }

    return nullptr;
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkSpace,
                                        TwistBufferKey pKey) {
    return GetBuffer(pWorkSpace, nullptr, pKey);
}

bool TwistWorkSpace::TryLegacySlotToBufferKey(TwistWorkSpaceSlot pSlot,
                                              TwistBufferKey *pKeyOut) {
    (void)pSlot;
    (void)pKeyOut;
    return false;
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

        case TwistBufferKind::kConstants:
            return static_cast<int>(sizeof(TwistDomainConstants));

        default:
            return 0;
    }
}

bool TwistWorkSpace::IsSalt(TwistWorkSpaceSlot pSlot) {
    TwistBufferKey aMappedKey;
    if (TryLegacySlotToBufferKey(pSlot, &aMappedKey)) {
        return IsSalt(aMappedKey);
    }
    if (IsParamSaltSlot(pSlot)) {
        return true;
    }
    return false;
}

bool TwistWorkSpace::IsSalt(TwistBufferKey pKey) {
    return pKey.mKind == TwistBufferKind::kSalt;
}
