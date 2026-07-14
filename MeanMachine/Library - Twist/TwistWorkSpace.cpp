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
        case TwistDomain::kPhaseD: return &pBundle->mPhaseDSalts;
        case TwistDomain::kPhaseE: return &pBundle->mPhaseESalts;
        case TwistDomain::kPhaseF: return &pBundle->mPhaseFSalts;
        case TwistDomain::kPhaseG: return &pBundle->mPhaseGSalts;
        case TwistDomain::kPhaseH: return &pBundle->mPhaseHSalts;
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
        case TwistDomain::kPhaseD: return &pBundle->mPhaseDConstants;
        case TwistDomain::kPhaseE: return &pBundle->mPhaseEConstants;
        case TwistDomain::kPhaseF: return &pBundle->mPhaseFConstants;
        case TwistDomain::kPhaseG: return &pBundle->mPhaseGConstants;
        case TwistDomain::kPhaseH: return &pBundle->mPhaseHConstants;
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

TwistDomainSeedRoundMaterial *GetSaltMaterial(TwistDomainSaltSet *pSet,
                                              int pRole) {
    if (pSet == nullptr) {
        return nullptr;
    }
    switch (pRole) {
        case 0: return &pSet->mOrbiterAssign;
        case 1: return &pSet->mOrbiterUpdate;
        case 2: return &pSet->mWandererUpdate;
        default: return nullptr;
    }
}

bool DecodeParamSaltSlot(TwistWorkSpaceSlot pSlot,
                         int *pRoleOut,
                         int *pLaneOut) {
    const int aValue = static_cast<int>(pSlot);
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA);
    const int aCount = 18;
    if ((aValue < aBase) || (aValue >= (aBase + aCount))) {
        return false;
    }
    const int aOffset = aValue - aBase;
    if (pRoleOut != nullptr) {
        *pRoleOut = aOffset / 6;
    }
    if (pLaneOut != nullptr) {
        *pLaneOut = aOffset % 6;
    }
    return true;
}

bool DecodePhaseSaltSlot(TwistWorkSpaceSlot pSlot,
                         TwistDomain *pDomainOut,
                         int *pRoleOut,
                         int *pLaneOut) {
    const int aValue = static_cast<int>(pSlot);
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kPhaseASaltOrbiterAssignA);
    const int aCountPerPhase = 18;
    const int aPhaseCount = 8;
    if ((aValue < aBase) || (aValue >= (aBase + aCountPerPhase * aPhaseCount))) {
        return false;
    }

    const int aOffset = aValue - aBase;
    const int aPhaseIndex = aOffset / aCountPerPhase;
    const int aRoleLaneOffset = aOffset % aCountPerPhase;
    if (pDomainOut != nullptr) {
        *pDomainOut = static_cast<TwistDomain>(static_cast<int>(TwistDomain::kPhaseA) + aPhaseIndex);
    }
    if (pRoleOut != nullptr) {
        *pRoleOut = aRoleLaneOffset / 6;
    }
    if (pLaneOut != nullptr) {
        *pLaneOut = aRoleLaneOffset % 6;
    }
    return true;
}

std::uint64_t *GetSaltSlot(TwistDomainSaltSet *pSet,
                           int pRole,
                           int pLane) {
    return GetSaltLane(GetSaltMaterial(pSet, pRole), pLane);
}

std::uint64_t *GetParamSaltSlot(TwistDomainSaltSet *pSet,
                                TwistWorkSpaceSlot pSlot) {
    int aRole = 0;
    int aLane = 0;
    if (!DecodeParamSaltSlot(pSlot, &aRole, &aLane)) {
        return nullptr;
    }
    return GetSaltSlot(pSet, aRole, aLane);
}

std::uint64_t *GetPhaseSaltSlot(TwistWorkSpace *pWorkSpace,
                                TwistWorkSpaceSlot pSlot) {
    if (pWorkSpace == nullptr) {
        return nullptr;
    }
    TwistDomain aDomain = TwistDomain::kInvalid;
    int aRole = 0;
    int aLane = 0;
    if (!DecodePhaseSaltSlot(pSlot, &aDomain, &aRole, &aLane)) {
        return nullptr;
    }
    return GetSaltSlot(GetSaltSet(&pWorkSpace->mDomainBundle, aDomain), aRole, aLane);
}

} // namespace

TwistWorkSpace::TwistWorkSpace() {
    std::memset(this, 0, sizeof(*this));
}

void TwistWorkSpace::ShiftKeyBoxA(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox + (H_KEY - 1) * W_KEY;
    std::uint8_t *aSource = aDest - W_KEY;
    for (int i = 0; i < (H_KEY - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY);
        aDest = aSource;
        aSource = aDest - W_KEY;
    }
}

void TwistWorkSpace::ShiftKeyBoxB(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox + (H_KEY - 1) * W_KEY;
    std::uint8_t *aSource = aDest - W_KEY;
    for (int i = 0; i < (H_KEY - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY);
        aDest = aSource;
        aSource = aDest - W_KEY;
    }
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkSpace,
                                        TwistExpander *pExpander,
                                        TwistWorkSpaceSlot pSlot) {
    if (pWorkSpace == nullptr) {
        return nullptr;
    }

    if (pExpander == nullptr) {
        if (DecodeParamSaltSlot(pSlot, nullptr, nullptr)) {
            return nullptr;
        }
        switch (pSlot) {
            case TwistWorkSpaceSlot::kParamSource:
            case TwistWorkSpaceSlot::kParamDestination:
            case TwistWorkSpaceSlot::kParamSnow:
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
        case TwistWorkSpaceSlot::kSource: return pWorkSpace->mSource;
        case TwistWorkSpaceSlot::kParamSource: return pExpander->mSource;
        case TwistWorkSpaceSlot::kParamDestination: return pExpander->mDest;
        case TwistWorkSpaceSlot::kParamSnow: return nullptr;
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
        case TwistWorkSpaceSlot::kFireLaneA: return pWorkSpace->mFireLaneA;
        case TwistWorkSpaceSlot::kFireLaneB: return pWorkSpace->mFireLaneB;
        case TwistWorkSpaceSlot::kFireLaneC: return pWorkSpace->mFireLaneC;
        case TwistWorkSpaceSlot::kFireLaneD: return pWorkSpace->mFireLaneD;
        case TwistWorkSpaceSlot::kWaterLaneA: return pWorkSpace->mWaterLaneA;
        case TwistWorkSpaceSlot::kWaterLaneB: return pWorkSpace->mWaterLaneB;
        case TwistWorkSpaceSlot::kWaterLaneC: return pWorkSpace->mWaterLaneC;
        case TwistWorkSpaceSlot::kWaterLaneD: return pWorkSpace->mWaterLaneD;
        case TwistWorkSpaceSlot::kEarthLaneA: return pWorkSpace->mEarthLaneA;
        case TwistWorkSpaceSlot::kEarthLaneB: return pWorkSpace->mEarthLaneB;
        case TwistWorkSpaceSlot::kEarthLaneC: return pWorkSpace->mEarthLaneC;
        case TwistWorkSpaceSlot::kEarthLaneD: return pWorkSpace->mEarthLaneD;
        case TwistWorkSpaceSlot::kWindLaneA: return pWorkSpace->mWindLaneA;
        case TwistWorkSpaceSlot::kWindLaneB: return pWorkSpace->mWindLaneB;
        case TwistWorkSpaceSlot::kWindLaneC: return pWorkSpace->mWindLaneC;
        case TwistWorkSpaceSlot::kWindLaneD: return pWorkSpace->mWindLaneD;
        case TwistWorkSpaceSlot::kFuseLaneA: return pWorkSpace->mFuseLaneA;
        case TwistWorkSpaceSlot::kFuseLaneB: return pWorkSpace->mFuseLaneB;
        case TwistWorkSpaceSlot::kFuseLaneC: return pWorkSpace->mFuseLaneC;
        case TwistWorkSpaceSlot::kFuseLaneD: return pWorkSpace->mFuseLaneD;
        case TwistWorkSpaceSlot::kScrapLaneA: return pWorkSpace->mScrapLaneA;
        case TwistWorkSpaceSlot::kScrapLaneB: return pWorkSpace->mScrapLaneB;
        case TwistWorkSpaceSlot::kScrapLaneC: return pWorkSpace->mScrapLaneC;
        case TwistWorkSpaceSlot::kScrapLaneD: return pWorkSpace->mScrapLaneD;
        case TwistWorkSpaceSlot::kMergeLaneA: return pWorkSpace->mMergeLaneA;
        case TwistWorkSpaceSlot::kMergeLaneB: return pWorkSpace->mMergeLaneB;
        case TwistWorkSpaceSlot::kMergeLaneC: return pWorkSpace->mMergeLaneC;
        case TwistWorkSpaceSlot::kMergeLaneD: return pWorkSpace->mMergeLaneD;
        case TwistWorkSpaceSlot::kInvestA: return pWorkSpace->mInvestLaneA;
        case TwistWorkSpaceSlot::kInvestB: return pWorkSpace->mInvestLaneB;
        case TwistWorkSpaceSlot::kInvestC: return pWorkSpace->mInvestLaneC;
        case TwistWorkSpaceSlot::kInvestD: return pWorkSpace->mInvestLaneD;
        case TwistWorkSpaceSlot::kInvestE: return pWorkSpace->mInvestLaneE;
        case TwistWorkSpaceSlot::kInvestF: return pWorkSpace->mInvestLaneF;
        case TwistWorkSpaceSlot::kInvestG: return pWorkSpace->mInvestLaneG;
        case TwistWorkSpaceSlot::kInvestH: return pWorkSpace->mInvestLaneH;
        case TwistWorkSpaceSlot::kIndexList256A: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256A);
        case TwistWorkSpaceSlot::kIndexList256B: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256B);
        case TwistWorkSpaceSlot::kIndexList256C: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256C);
        case TwistWorkSpaceSlot::kIndexList256D: return reinterpret_cast<std::uint8_t *>(pExpander->mIndexList256D);
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return &(pWorkSpace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return &(pWorkSpace->mKeyBoxB[0][0]);
        case TwistWorkSpaceSlot::kKeyRowReadA: return &(pWorkSpace->mKeyBoxA[H_KEY - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowReadB: return &(pWorkSpace->mKeyBoxB[H_KEY - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteA: return &(pWorkSpace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteB: return &(pWorkSpace->mKeyBoxB[0][0]);
            
        default:
            break;
    }

    if (DecodeParamSaltSlot(pSlot, nullptr, nullptr)) {
        return reinterpret_cast<std::uint8_t *>(
            GetParamSaltSlot(pExpander->mActiveSaltSet, pSlot)
        );
    }

    if (DecodePhaseSaltSlot(pSlot, nullptr, nullptr, nullptr)) {
        return reinterpret_cast<std::uint8_t *>(GetPhaseSaltSlot(pWorkSpace, pSlot));
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
        const TwistWorkSpaceSlot aSlot = static_cast<TwistWorkSpaceSlot>(pKey.mSlot);
        std::uint64_t *aLane = GetParamSaltSlot(aSet, aSlot);
        if (aLane == nullptr) {
            int aRole = 0;
            int aLaneIndex = 0;
            if (DecodePhaseSaltSlot(aSlot, nullptr, &aRole, &aLaneIndex)) {
                aLane = GetSaltSlot(aSet, aRole, aLaneIndex);
            }
        }
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

int TwistWorkSpace::GetBufferLength(TwistWorkSpaceSlot pSlot) {
    if (DecodeParamSaltSlot(pSlot, nullptr, nullptr) ||
        DecodePhaseSaltSlot(pSlot, nullptr, nullptr, nullptr)) {
        return S_SALT;
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return S_KEY;
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return S_KEY;
        case TwistWorkSpaceSlot::kKeyRowReadA:
        case TwistWorkSpaceSlot::kKeyRowWriteA: return W_KEY;
        case TwistWorkSpaceSlot::kKeyRowReadB:
        case TwistWorkSpaceSlot::kKeyRowWriteB: return W_KEY;

        case TwistWorkSpaceSlot::kIndexList256A:
        case TwistWorkSpaceSlot::kIndexList256B:
        case TwistWorkSpaceSlot::kIndexList256C:
        case TwistWorkSpaceSlot::kIndexList256D:
            return static_cast<int>(256U * sizeof(std::size_t));

        case TwistWorkSpaceSlot::kMergeLaneA:
        case TwistWorkSpaceSlot::kMergeLaneB:
        case TwistWorkSpaceSlot::kMergeLaneC:
        case TwistWorkSpaceSlot::kMergeLaneD:
            return S_QUARTER;

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
    if (DecodeParamSaltSlot(pSlot, nullptr, nullptr) ||
        DecodePhaseSaltSlot(pSlot, nullptr, nullptr, nullptr)) {
        return true;
    }
    return false;
}

bool TwistWorkSpace::IsSalt(TwistBufferKey pKey) {
    return pKey.mKind == TwistBufferKind::kSalt;
}

void TwistWorkSpace::Zero() {
    Zero_PostSeed();
    mDomainBundle.Zero();
}

void TwistWorkSpace::Zero_PostSeed() {
 
    memset(mSource, 0, sizeof(mSource));

    memset(mExpansionLaneA, 0, sizeof(mExpansionLaneA));
    memset(mExpansionLaneB, 0, sizeof(mExpansionLaneB));
    memset(mExpansionLaneC, 0, sizeof(mExpansionLaneC));
    memset(mExpansionLaneD, 0, sizeof(mExpansionLaneD));
    
    memset(mWorkLaneA, 0, sizeof(mWorkLaneA));
    memset(mWorkLaneB, 0, sizeof(mWorkLaneB));
    memset(mWorkLaneC, 0, sizeof(mWorkLaneC));
    memset(mWorkLaneD, 0, sizeof(mWorkLaneD));
    
    memset(mOperationLaneA, 0, sizeof(mOperationLaneA));
    memset(mOperationLaneB, 0, sizeof(mOperationLaneB));
    memset(mOperationLaneC, 0, sizeof(mOperationLaneC));
    memset(mOperationLaneD, 0, sizeof(mOperationLaneD));
    
    memset(mSnowLaneA, 0, sizeof(mSnowLaneA));
    memset(mSnowLaneB, 0, sizeof(mSnowLaneB));
    memset(mSnowLaneC, 0, sizeof(mSnowLaneC));
    memset(mSnowLaneD, 0, sizeof(mSnowLaneD));

    memset(mFireLaneA, 0, sizeof(mFireLaneA));
    memset(mFireLaneB, 0, sizeof(mFireLaneB));
    memset(mFireLaneC, 0, sizeof(mFireLaneC));
    memset(mFireLaneD, 0, sizeof(mFireLaneD));

    memset(mWaterLaneA, 0, sizeof(mWaterLaneA));
    memset(mWaterLaneB, 0, sizeof(mWaterLaneB));
    memset(mWaterLaneC, 0, sizeof(mWaterLaneC));
    memset(mWaterLaneD, 0, sizeof(mWaterLaneD));

    memset(mEarthLaneA, 0, sizeof(mEarthLaneA));
    memset(mEarthLaneB, 0, sizeof(mEarthLaneB));
    memset(mEarthLaneC, 0, sizeof(mEarthLaneC));
    memset(mEarthLaneD, 0, sizeof(mEarthLaneD));

    memset(mWindLaneA, 0, sizeof(mWindLaneA));
    memset(mWindLaneB, 0, sizeof(mWindLaneB));
    memset(mWindLaneC, 0, sizeof(mWindLaneC));
    memset(mWindLaneD, 0, sizeof(mWindLaneD));

    memset(mFuseLaneA, 0, sizeof(mFuseLaneA));
    memset(mFuseLaneB, 0, sizeof(mFuseLaneB));
    memset(mFuseLaneC, 0, sizeof(mFuseLaneC));
    memset(mFuseLaneD, 0, sizeof(mFuseLaneD));

    memset(mScrapLaneA, 0, sizeof(mScrapLaneA));
    memset(mScrapLaneB, 0, sizeof(mScrapLaneB));
    memset(mScrapLaneC, 0, sizeof(mScrapLaneC));
    memset(mScrapLaneD, 0, sizeof(mScrapLaneD));

    memset(mMergeLaneA, 0, sizeof(mMergeLaneA));
    memset(mMergeLaneB, 0, sizeof(mMergeLaneB));
    memset(mMergeLaneC, 0, sizeof(mMergeLaneC));
    memset(mMergeLaneD, 0, sizeof(mMergeLaneD));
    
    memset(mInvestLaneA, 0, sizeof(mInvestLaneA));
    memset(mInvestLaneB, 0, sizeof(mInvestLaneB));
    memset(mInvestLaneC, 0, sizeof(mInvestLaneC));
    memset(mInvestLaneD, 0, sizeof(mInvestLaneD));
    
    memset(mInvestLaneE, 0, sizeof(mInvestLaneE));
    memset(mInvestLaneF, 0, sizeof(mInvestLaneF));
    memset(mInvestLaneG, 0, sizeof(mInvestLaneG));
    memset(mInvestLaneH, 0, sizeof(mInvestLaneH));
    
}
