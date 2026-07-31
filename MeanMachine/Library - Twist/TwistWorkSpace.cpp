//
//  TwistWorkSpace.cpp
//  Gorgon
//

#include "TwistWorkSpace.hpp"
#include "TwistExpander.hpp"
#include <cstring>

static_assert(H_KEY == 8,
              "The individual key-row workspace slots require exactly eight rows.");
static_assert(S_BLOCK == (W_KEY * 16),
              "Lane splits require exactly sixteen W_KEY fragments per full lane.");
static_assert(
    (static_cast<int>(TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateH) -
     static_cast<int>(TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA) + 1) == 24,
    "Parameterized domain salts require three contiguous groups of eight.");
static_assert(
    (static_cast<int>(TwistWorkSpaceSlot::kKeySpawnBSaltWandererUpdateH) -
     static_cast<int>(TwistWorkSpaceSlot::kKeyRotateASaltOrbiterAssignA) + 1) == 144,
    "Workspace domain salts require six contiguous groups of twenty-four.");

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

TwistBufferKey TwistBufferKey::LaneSplit(TwistWorkSpaceSlot pSlot,
                                         std::uint8_t pLaneSplit) {
    TwistBufferKey aKey;
    aKey.mKind = TwistBufferKind::kLaneSplit;
    aKey.mSlot = static_cast<std::uint16_t>(pSlot);
    aKey.mLaneSplit = pLaneSplit;
    return aKey;
}

bool TwistBufferKey::IsValid() const {
    if (mKind == TwistBufferKind::kLaneSplit) {
        return (mLaneSplit < 16U) &&
               (mSlot != static_cast<std::uint16_t>(
                    TwistWorkSpaceSlot::kInvalid
                ));
    }
    return mKind != TwistBufferKind::kInvalid;
}

bool TwistBufferKey::IsSalt() const {
    return mKind == TwistBufferKind::kSalt;
}

bool TwistBufferKey::IsConstants() const {
    return mKind == TwistBufferKind::kConstants;
}

bool TwistBufferKey::IsLaneSplit() const {
    return mKind == TwistBufferKind::kLaneSplit;
}

TwistDomainBundle *TwistWorkSpace::GetSaltDomainBundle(TwistExpander *pExpander,
                                                        TwistSaltOwner pOwner) {
    switch (pOwner) {
        case TwistSaltOwner::kInbuilt:
            return pExpander ? pExpander->GetDomainBundleInbuilt() : nullptr;
        case TwistSaltOwner::kEphemeral:
            return pExpander ? pExpander->GetDomainBundleEphemeral() : nullptr;
        default:
            return nullptr;
    }
}

namespace {

TwistDomainSaltSet *GetSaltSet(TwistDomainBundle *pBundle,
                               TwistDomain pDomain) {
    if (pBundle == nullptr) {
        return nullptr;
    }
    switch (pDomain) {
        case TwistDomain::kKeyRotateA: return &pBundle->mKeyRotateASalts;
        case TwistDomain::kKeyRotateB: return &pBundle->mKeyRotateBSalts;
        case TwistDomain::kKeySpawnA: return &pBundle->mKeySpawnASalts;
        case TwistDomain::kKeySpawnB: return &pBundle->mKeySpawnBSalts;
        case TwistDomain::kSeed: return &pBundle->mSeedSalts;
        case TwistDomain::kTwist: return &pBundle->mTwistSalts;
        default: return nullptr;
    }
}

TwistDomainConstants *GetDomainConstants(TwistDomainBundle *pBundle,
                                         TwistDomain pDomain) {
    if (pBundle == nullptr) {
        return nullptr;
    }
    switch (pDomain) {
        case TwistDomain::kKeyRotateA: return &pBundle->mKeyRotateAConstants;
        case TwistDomain::kKeyRotateB: return &pBundle->mKeyRotateBConstants;
        case TwistDomain::kKeySpawnA: return &pBundle->mKeySpawnAConstants;
        case TwistDomain::kKeySpawnB: return &pBundle->mKeySpawnBConstants;
        case TwistDomain::kSeed: return &pBundle->mSeedConstants;
        case TwistDomain::kTwist: return &pBundle->mTwistConstants;
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
        case 6: return pMaterial->mSaltG;
        case 7: return pMaterial->mSaltH;
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
    const int aCount = 24;
    if ((aValue < aBase) || (aValue >= (aBase + aCount))) {
        return false;
    }
    const int aOffset = aValue - aBase;
    if (pRoleOut != nullptr) {
        *pRoleOut = aOffset / 8;
    }
    if (pLaneOut != nullptr) {
        *pLaneOut = aOffset % 8;
    }
    return true;
}

bool DecodePhaseSaltSlot(TwistWorkSpaceSlot pSlot,
                         TwistDomain *pDomainOut,
                         int *pRoleOut,
                         int *pLaneOut) {
    const int aValue = static_cast<int>(pSlot);
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kKeyRotateASaltOrbiterAssignA);
    const int aCountPerPhase = 24;
    constexpr int kPhaseCount = 6;
    constexpr TwistDomain kDomains[kPhaseCount] = {
        TwistDomain::kKeyRotateA,
        TwistDomain::kKeySpawnA,
        TwistDomain::kSeed,
        TwistDomain::kTwist,
        TwistDomain::kKeyRotateB,
        TwistDomain::kKeySpawnB,
    };
    if ((aValue < aBase) || (aValue >= (aBase + aCountPerPhase * kPhaseCount))) {
        return false;
    }

    const int aOffset = aValue - aBase;
    const int aPhaseIndex = aOffset / aCountPerPhase;
    const int aRoleLaneOffset = aOffset % aCountPerPhase;
    if (pDomainOut != nullptr) {
        *pDomainOut = kDomains[aPhaseIndex];
    }
    if (pRoleOut != nullptr) {
        *pRoleOut = aRoleLaneOffset / 8;
    }
    if (pLaneOut != nullptr) {
        *pLaneOut = aRoleLaneOffset % 8;
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
    return GetBuffer(pWorkSpace,
                     pExpander,
                     pSlot,
                     nullptr,
                     nullptr);
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkSpace,
                                        TwistExpander *pExpander,
                                        TwistWorkSpaceSlot pSlot,
                                        std::uint8_t *pParamSource,
                                        std::uint8_t *pParamDestination) {
    return GetBuffer(pWorkSpace,
                     pExpander,
                     pSlot,
                     pParamSource,
                     pParamDestination,
                     nullptr);
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkSpace,
                                        TwistExpander *pExpander,
                                        TwistWorkSpaceSlot pSlot,
                                        std::uint8_t *pParamSource,
                                        std::uint8_t *pParamDestination,
                                        TwistDomainSaltSet *pParamSaltSet) {
    if (pWorkSpace == nullptr) {
        return nullptr;
    }

    if (pExpander == nullptr) {
        if (DecodeParamSaltSlot(pSlot, nullptr, nullptr) &&
            (pParamSaltSet == nullptr)) {
            return nullptr;
        }
        switch (pSlot) {
            case TwistWorkSpaceSlot::kParamCrossA:
            case TwistWorkSpaceSlot::kParamCrossB:
            case TwistWorkSpaceSlot::kParamCrossC:
            case TwistWorkSpaceSlot::kParamCrossD:
                return nullptr;
            default:
                break;
        }
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kSourceLane: return pWorkSpace->mSourceLane;
        case TwistWorkSpaceSlot::kNonceLane: return pWorkSpace->mNonceLane;
        case TwistWorkSpaceSlot::kParamSource: return pParamSource;
        case TwistWorkSpaceSlot::kParamDestination: return pParamDestination;
        case TwistWorkSpaceSlot::kParamCrossA: return nullptr;
        case TwistWorkSpaceSlot::kParamCrossB: return nullptr;
        case TwistWorkSpaceSlot::kParamCrossC: return nullptr;
        case TwistWorkSpaceSlot::kParamCrossD: return nullptr;
        case TwistWorkSpaceSlot::kHeartLaneA: return pWorkSpace->mHeartLaneA;
        case TwistWorkSpaceSlot::kHeartLaneB: return pWorkSpace->mHeartLaneB;
        case TwistWorkSpaceSlot::kHeartLaneC: return pWorkSpace->mHeartLaneC;
        case TwistWorkSpaceSlot::kHeartLaneD: return pWorkSpace->mHeartLaneD;
        case TwistWorkSpaceSlot::kSpiritLaneA: return pWorkSpace->mSpiritLaneA;
        case TwistWorkSpaceSlot::kSpiritLaneB: return pWorkSpace->mSpiritLaneB;
        case TwistWorkSpaceSlot::kSpiritLaneC: return pWorkSpace->mSpiritLaneC;
        case TwistWorkSpaceSlot::kSpiritLaneD: return pWorkSpace->mSpiritLaneD;
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
        case TwistWorkSpaceSlot::kWoodLaneA: return pWorkSpace->mWoodLaneA;
        case TwistWorkSpaceSlot::kWoodLaneB: return pWorkSpace->mWoodLaneB;
        case TwistWorkSpaceSlot::kWoodLaneC: return pWorkSpace->mWoodLaneC;
        case TwistWorkSpaceSlot::kWoodLaneD: return pWorkSpace->mWoodLaneD;
        case TwistWorkSpaceSlot::kLightningLaneA: return pWorkSpace->mLightningLaneA;
        case TwistWorkSpaceSlot::kLightningLaneB: return pWorkSpace->mLightningLaneB;
        case TwistWorkSpaceSlot::kLightningLaneC: return pWorkSpace->mLightningLaneC;
        case TwistWorkSpaceSlot::kLightningLaneD: return pWorkSpace->mLightningLaneD;
        case TwistWorkSpaceSlot::kMagmaLaneA: return pWorkSpace->mMagmaLaneA;
        case TwistWorkSpaceSlot::kMagmaLaneB: return pWorkSpace->mMagmaLaneB;
        case TwistWorkSpaceSlot::kMagmaLaneC: return pWorkSpace->mMagmaLaneC;
        case TwistWorkSpaceSlot::kMagmaLaneD: return pWorkSpace->mMagmaLaneD;
        case TwistWorkSpaceSlot::kSoilLaneA: return pWorkSpace->mSoilLaneA;
        case TwistWorkSpaceSlot::kSoilLaneB: return pWorkSpace->mSoilLaneB;
        case TwistWorkSpaceSlot::kSoilLaneC: return pWorkSpace->mSoilLaneC;
        case TwistWorkSpaceSlot::kSoilLaneD: return pWorkSpace->mSoilLaneD;
        case TwistWorkSpaceSlot::kPlasmaLaneA: return pWorkSpace->mPlasmaLaneA;
        case TwistWorkSpaceSlot::kPlasmaLaneB: return pWorkSpace->mPlasmaLaneB;
        case TwistWorkSpaceSlot::kPlasmaLaneC: return pWorkSpace->mPlasmaLaneC;
        case TwistWorkSpaceSlot::kPlasmaLaneD: return pWorkSpace->mPlasmaLaneD;
        case TwistWorkSpaceSlot::kShadowLaneA: return pWorkSpace->mShadowLaneA;
        case TwistWorkSpaceSlot::kShadowLaneB: return pWorkSpace->mShadowLaneB;
        case TwistWorkSpaceSlot::kShadowLaneC: return pWorkSpace->mShadowLaneC;
        case TwistWorkSpaceSlot::kShadowLaneD: return pWorkSpace->mShadowLaneD;
        case TwistWorkSpaceSlot::kCrystalLaneA: return pWorkSpace->mCrystalLaneA;
        case TwistWorkSpaceSlot::kCrystalLaneB: return pWorkSpace->mCrystalLaneB;
        case TwistWorkSpaceSlot::kCrystalLaneC: return pWorkSpace->mCrystalLaneC;
        case TwistWorkSpaceSlot::kCrystalLaneD: return pWorkSpace->mCrystalLaneD;
        case TwistWorkSpaceSlot::kAetherLaneA: return pWorkSpace->mAetherLaneA;
        case TwistWorkSpaceSlot::kAetherLaneB: return pWorkSpace->mAetherLaneB;
        case TwistWorkSpaceSlot::kAetherLaneC: return pWorkSpace->mAetherLaneC;
        case TwistWorkSpaceSlot::kAetherLaneD: return pWorkSpace->mAetherLaneD;
        case TwistWorkSpaceSlot::kCelestialLaneA: return pWorkSpace->mCelestialLaneA;
        case TwistWorkSpaceSlot::kCelestialLaneB: return pWorkSpace->mCelestialLaneB;
        case TwistWorkSpaceSlot::kCelestialLaneC: return pWorkSpace->mCelestialLaneC;
        case TwistWorkSpaceSlot::kCelestialLaneD: return pWorkSpace->mCelestialLaneD;
        case TwistWorkSpaceSlot::kKineticLaneA: return pWorkSpace->mKineticLaneA;
        case TwistWorkSpaceSlot::kKineticLaneB: return pWorkSpace->mKineticLaneB;
        case TwistWorkSpaceSlot::kKineticLaneC: return pWorkSpace->mKineticLaneC;
        case TwistWorkSpaceSlot::kKineticLaneD: return pWorkSpace->mKineticLaneD;
        case TwistWorkSpaceSlot::kVaporLaneA: return pWorkSpace->mVaporLaneA;
        case TwistWorkSpaceSlot::kVaporLaneB: return pWorkSpace->mVaporLaneB;
        case TwistWorkSpaceSlot::kVaporLaneC: return pWorkSpace->mVaporLaneC;
        case TwistWorkSpaceSlot::kVaporLaneD: return pWorkSpace->mVaporLaneD;
        case TwistWorkSpaceSlot::kIceLaneA: return pWorkSpace->mIceLaneA;
        case TwistWorkSpaceSlot::kIceLaneB: return pWorkSpace->mIceLaneB;
        case TwistWorkSpaceSlot::kIceLaneC: return pWorkSpace->mIceLaneC;
        case TwistWorkSpaceSlot::kIceLaneD: return pWorkSpace->mIceLaneD;
        case TwistWorkSpaceSlot::kIndexList256A: return reinterpret_cast<std::uint8_t *>(pWorkSpace->mIndexList256A);
        case TwistWorkSpaceSlot::kIndexList256B: return reinterpret_cast<std::uint8_t *>(pWorkSpace->mIndexList256B);
        case TwistWorkSpaceSlot::kIndexList256C: return reinterpret_cast<std::uint8_t *>(pWorkSpace->mIndexList256C);
        case TwistWorkSpaceSlot::kIndexList256D: return reinterpret_cast<std::uint8_t *>(pWorkSpace->mIndexList256D);
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return &(pWorkSpace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return &(pWorkSpace->mKeyBoxB[0][0]);
        case TwistWorkSpaceSlot::kKeyRowReadA: return &(pWorkSpace->mKeyBoxA[H_KEY - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowReadB: return &(pWorkSpace->mKeyBoxB[H_KEY - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteA: return &(pWorkSpace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteB: return &(pWorkSpace->mKeyBoxB[0][0]);

        case TwistWorkSpaceSlot::kKeyRowA0: return &(pWorkSpace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyRowA1: return &(pWorkSpace->mKeyBoxA[1][0]);
        case TwistWorkSpaceSlot::kKeyRowA2: return &(pWorkSpace->mKeyBoxA[2][0]);
        case TwistWorkSpaceSlot::kKeyRowA3: return &(pWorkSpace->mKeyBoxA[3][0]);
        case TwistWorkSpaceSlot::kKeyRowA4: return &(pWorkSpace->mKeyBoxA[4][0]);
        case TwistWorkSpaceSlot::kKeyRowA5: return &(pWorkSpace->mKeyBoxA[5][0]);
        case TwistWorkSpaceSlot::kKeyRowA6: return &(pWorkSpace->mKeyBoxA[6][0]);
        case TwistWorkSpaceSlot::kKeyRowA7: return &(pWorkSpace->mKeyBoxA[7][0]);

        case TwistWorkSpaceSlot::kKeyRowB0: return &(pWorkSpace->mKeyBoxB[0][0]);
        case TwistWorkSpaceSlot::kKeyRowB1: return &(pWorkSpace->mKeyBoxB[1][0]);
        case TwistWorkSpaceSlot::kKeyRowB2: return &(pWorkSpace->mKeyBoxB[2][0]);
        case TwistWorkSpaceSlot::kKeyRowB3: return &(pWorkSpace->mKeyBoxB[3][0]);
        case TwistWorkSpaceSlot::kKeyRowB4: return &(pWorkSpace->mKeyBoxB[4][0]);
        case TwistWorkSpaceSlot::kKeyRowB5: return &(pWorkSpace->mKeyBoxB[5][0]);
        case TwistWorkSpaceSlot::kKeyRowB6: return &(pWorkSpace->mKeyBoxB[6][0]);
        case TwistWorkSpaceSlot::kKeyRowB7: return &(pWorkSpace->mKeyBoxB[7][0]);

        default:
            break;
    }

    if (DecodeParamSaltSlot(pSlot, nullptr, nullptr)) {
        return reinterpret_cast<std::uint8_t *>(
            GetParamSaltSlot(pParamSaltSet, pSlot)
        );
    }

    if (DecodePhaseSaltSlot(pSlot, nullptr, nullptr, nullptr)) {
        return reinterpret_cast<std::uint8_t *>(GetPhaseSaltSlot(pWorkSpace, pSlot));
    }

    return nullptr;
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkSpace,
                                        TwistWorkSpaceSlot pSlot) {
    return GetBuffer(pWorkSpace, nullptr, pSlot);
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkSpace,
                                        TwistExpander *pExpander,
                                        TwistBufferKey pKey) {
    if (!pKey.IsValid()) {
        return nullptr;
    }

    if (pKey.IsLaneSplit()) {
        const TwistWorkSpaceSlot aSlot =
            static_cast<TwistWorkSpaceSlot>(pKey.mSlot);
        if (GetBufferLength(aSlot) != S_BLOCK) {
            return nullptr;
        }
        std::uint8_t *aLane = GetBuffer(pWorkSpace, pExpander, aSlot);
        return aLane == nullptr
            ? nullptr
            : aLane + (static_cast<std::size_t>(pKey.mLaneSplit) *
                       static_cast<std::size_t>(W_KEY));
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

        case TwistWorkSpaceSlot::kKeyRowA0:
        case TwistWorkSpaceSlot::kKeyRowA1:
        case TwistWorkSpaceSlot::kKeyRowA2:
        case TwistWorkSpaceSlot::kKeyRowA3:
        case TwistWorkSpaceSlot::kKeyRowA4:
        case TwistWorkSpaceSlot::kKeyRowA5:
        case TwistWorkSpaceSlot::kKeyRowA6:
        case TwistWorkSpaceSlot::kKeyRowA7:
        case TwistWorkSpaceSlot::kKeyRowB0:
        case TwistWorkSpaceSlot::kKeyRowB1:
        case TwistWorkSpaceSlot::kKeyRowB2:
        case TwistWorkSpaceSlot::kKeyRowB3:
        case TwistWorkSpaceSlot::kKeyRowB4:
        case TwistWorkSpaceSlot::kKeyRowB5:
        case TwistWorkSpaceSlot::kKeyRowB6:
        case TwistWorkSpaceSlot::kKeyRowB7:
            return W_KEY;

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

        case TwistBufferKind::kLaneSplit:
            return pKey.IsValid() &&
                   (GetBufferLength(
                        static_cast<TwistWorkSpaceSlot>(pKey.mSlot)
                    ) == S_BLOCK)
                ? W_KEY
                : 0;

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

    memset(mSourceLane, 0, sizeof(mSourceLane));
    memset(mNonceLane, 0, sizeof(mNonceLane));

    memset(mIndexList256A, 0, sizeof(mIndexList256A));
    memset(mIndexList256B, 0, sizeof(mIndexList256B));
    memset(mIndexList256C, 0, sizeof(mIndexList256C));
    memset(mIndexList256D, 0, sizeof(mIndexList256D));

    memset(mHeartLaneA, 0, sizeof(mHeartLaneA));
    memset(mHeartLaneB, 0, sizeof(mHeartLaneB));
    memset(mHeartLaneC, 0, sizeof(mHeartLaneC));
    memset(mHeartLaneD, 0, sizeof(mHeartLaneD));

    memset(mSpiritLaneA, 0, sizeof(mSpiritLaneA));
    memset(mSpiritLaneB, 0, sizeof(mSpiritLaneB));
    memset(mSpiritLaneC, 0, sizeof(mSpiritLaneC));
    memset(mSpiritLaneD, 0, sizeof(mSpiritLaneD));

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

    memset(mWoodLaneA, 0, sizeof(mWoodLaneA));
    memset(mWoodLaneB, 0, sizeof(mWoodLaneB));
    memset(mWoodLaneC, 0, sizeof(mWoodLaneC));
    memset(mWoodLaneD, 0, sizeof(mWoodLaneD));

    memset(mLightningLaneA, 0, sizeof(mLightningLaneA));
    memset(mLightningLaneB, 0, sizeof(mLightningLaneB));
    memset(mLightningLaneC, 0, sizeof(mLightningLaneC));
    memset(mLightningLaneD, 0, sizeof(mLightningLaneD));

    memset(mMagmaLaneA, 0, sizeof(mMagmaLaneA));
    memset(mMagmaLaneB, 0, sizeof(mMagmaLaneB));
    memset(mMagmaLaneC, 0, sizeof(mMagmaLaneC));
    memset(mMagmaLaneD, 0, sizeof(mMagmaLaneD));

    memset(mSoilLaneA, 0, sizeof(mSoilLaneA));
    memset(mSoilLaneB, 0, sizeof(mSoilLaneB));
    memset(mSoilLaneC, 0, sizeof(mSoilLaneC));
    memset(mSoilLaneD, 0, sizeof(mSoilLaneD));

    memset(mPlasmaLaneA, 0, sizeof(mPlasmaLaneA));
    memset(mPlasmaLaneB, 0, sizeof(mPlasmaLaneB));
    memset(mPlasmaLaneC, 0, sizeof(mPlasmaLaneC));
    memset(mPlasmaLaneD, 0, sizeof(mPlasmaLaneD));

    memset(mShadowLaneA, 0, sizeof(mShadowLaneA));
    memset(mShadowLaneB, 0, sizeof(mShadowLaneB));
    memset(mShadowLaneC, 0, sizeof(mShadowLaneC));
    memset(mShadowLaneD, 0, sizeof(mShadowLaneD));

    memset(mCrystalLaneA, 0, sizeof(mCrystalLaneA));
    memset(mCrystalLaneB, 0, sizeof(mCrystalLaneB));
    memset(mCrystalLaneC, 0, sizeof(mCrystalLaneC));
    memset(mCrystalLaneD, 0, sizeof(mCrystalLaneD));

    memset(mAetherLaneA, 0, sizeof(mAetherLaneA));
    memset(mAetherLaneB, 0, sizeof(mAetherLaneB));
    memset(mAetherLaneC, 0, sizeof(mAetherLaneC));
    memset(mAetherLaneD, 0, sizeof(mAetherLaneD));

    memset(mCelestialLaneA, 0, sizeof(mCelestialLaneA));
    memset(mCelestialLaneB, 0, sizeof(mCelestialLaneB));
    memset(mCelestialLaneC, 0, sizeof(mCelestialLaneC));
    memset(mCelestialLaneD, 0, sizeof(mCelestialLaneD));

    memset(mKineticLaneA, 0, sizeof(mKineticLaneA));
    memset(mKineticLaneB, 0, sizeof(mKineticLaneB));
    memset(mKineticLaneC, 0, sizeof(mKineticLaneC));
    memset(mKineticLaneD, 0, sizeof(mKineticLaneD));

    memset(mVaporLaneA, 0, sizeof(mVaporLaneA));
    memset(mVaporLaneB, 0, sizeof(mVaporLaneB));
    memset(mVaporLaneC, 0, sizeof(mVaporLaneC));
    memset(mVaporLaneD, 0, sizeof(mVaporLaneD));

    memset(mIceLaneA, 0, sizeof(mIceLaneA));
    memset(mIceLaneB, 0, sizeof(mIceLaneB));
    memset(mIceLaneC, 0, sizeof(mIceLaneC));
    memset(mIceLaneD, 0, sizeof(mIceLaneD));

}
