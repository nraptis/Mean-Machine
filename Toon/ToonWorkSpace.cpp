//
//  ToonWorkSpace.cpp
//  Valhalla
//
//  Created by Dragon on 5/16/26.
//

#include "ToonWorkSpace.hpp"
#include "ToonExpander.hpp"
#include <cstring>

inline ToonBufferKey ToonBufferKey::Direct(ToonDirectBuffer buffer) {
    ToonBufferKey key;
    key.mKind = ToonBufferKind::kDirect;
    key.mDirect = buffer;
    return key;
}

inline ToonBufferKey ToonBufferKey::Salt(ToonSaltOwner owner,
                                         ToonDomain domain,
                                         ToonSaltPhase phase,
                                         ToonSaltLane lane) {
    ToonBufferKey key;
    key.mKind = ToonBufferKind::kSalt;
    key.mSaltOwner = owner;
    key.mDomain = domain;
    key.mSaltPhase = phase;
    key.mSaltLane = lane;
    return key;
}

inline ToonBufferKey ToonBufferKey::SBox(ToonSBoxOwner owner,
                                         ToonDomain domain,
                                         ToonSBoxLane lane) {
    ToonBufferKey key;
    key.mKind = ToonBufferKind::kSBox;
    key.mSBoxOwner = owner;
    key.mDomain = domain;
    key.mSBoxLane = lane;
    return key;
}

inline ToonBufferKey ToonBufferKey::Constants(ToonSaltOwner owner,
                                              ToonDomain domain) {
    ToonBufferKey key;
    key.mKind = ToonBufferKind::kConstants;
    key.mSaltOwner = owner;
    key.mDomain = domain;
    return key;
}

inline bool ToonBufferKey::IsValid() const {
    return mKind != ToonBufferKind::kInvalid;
}

inline bool ToonBufferKey::IsDirect() const {
    return mKind == ToonBufferKind::kDirect;
}

inline bool ToonBufferKey::IsSalt() const {
    return mKind == ToonBufferKind::kSalt;
}

inline bool ToonBufferKey::IsSBox() const {
    return mKind == ToonBufferKind::kSBox;
}

inline bool ToonBufferKey::IsConstants() const {
    return mKind == ToonBufferKind::kConstants;
}

ToonWorkSpace::ToonWorkSpace() {
    std::memset(this, 0, sizeof(*this));
}

void ToonWorkSpace::ShiftKeyBoxA(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox + (H_KEY_A - 1) * W_KEY_A;
    std::uint8_t *aSource = aDest - W_KEY_A;
    for (int i = 0; i < (H_KEY_A - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_A);
        aDest = aSource;
        aSource = aDest - W_KEY_A;
    }
}

void ToonWorkSpace::ShiftKeyBoxB(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = pBox + W_KEY_B;
    for (int i = 0; i < (H_KEY_B - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_B);
        aDest = aSource;
        aSource = aDest + W_KEY_B;
    }
}

void ToonWorkSpace::ShiftKeyBoxC(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox + (H_KEY_C - 1) * W_KEY_C;
    std::uint8_t *aSource = aDest - W_KEY_C;

    for (int i = 0; i < (H_KEY_C - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_C);
        aDest = aSource;
        aSource = aDest - W_KEY_C;
    }
}

void ToonWorkSpace::ShiftKeyBoxD(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = pBox + W_KEY_D;

    for (int i = 0; i < (H_KEY_D - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_D);
        aDest = aSource;
        aSource = aDest + W_KEY_D;
    }
}

static ToonDomainBundle *GetDomainBundle(ToonWorkSpace *pWorkspace,
                                         ToonExpander *pExpander,
                                         ToonSaltOwner owner) {
    switch (owner) {
        case ToonSaltOwner::kLocal:
            return pWorkspace ? &pWorkspace->mDomainBundle : nullptr;

        case ToonSaltOwner::kInbuilt:
            return pExpander ? &pExpander->mDomainBundleInbuilt : nullptr;

        case ToonSaltOwner::kEphemeral:
            return pExpander ? &pExpander->mDomainBundleEphemeral : nullptr;

        default:
            return nullptr;
    }
}

static ToonDomainBundle *GetSBoxDomainBundle(ToonWorkSpace *pWorkspace,
                                             ToonExpander *pExpander,
                                             ToonSBoxOwner owner) {
    switch (owner) {
        case ToonSBoxOwner::kLocal:
            return pWorkspace ? &pWorkspace->mDomainBundle : nullptr;

        case ToonSBoxOwner::kInbuilt:
            return pExpander ? &pExpander->mDomainBundleInbuilt : nullptr;

        default:
            return nullptr;
    }
}

int ToonWorkSpace::GetBufferLength(ToonBufferKey pKey) {
    switch (pKey.mKind) {
        case ToonBufferKind::kSalt:
            return S_SALT * static_cast<int>(sizeof(std::uint64_t));

        case ToonBufferKind::kSBox:
            return S_SBOX;

        case ToonBufferKind::kConstants:
            return static_cast<int>(sizeof(ToonDomainConstants));

        case ToonBufferKind::kDirect:
            switch (pKey.mDirect) {
                case ToonDirectBuffer::kIndexList256A:
                case ToonDirectBuffer::kIndexList256B:
                case ToonDirectBuffer::kIndexList256C:
                case ToonDirectBuffer::kIndexList256D:
                    return 256 * static_cast<int>(sizeof(std::size_t));

                case ToonDirectBuffer::kKeyBoxUnrolledA:
                    return S_KEY_A;

                case ToonDirectBuffer::kKeyBoxUnrolledB:
                    return S_KEY_B;

                case ToonDirectBuffer::kKeyBoxUnrolledC:
                    return S_KEY_C;

                case ToonDirectBuffer::kKeyBoxUnrolledD:
                    return S_KEY_D;

                case ToonDirectBuffer::kKeyRowReadA:
                case ToonDirectBuffer::kKeyRowWriteA:
                    return W_KEY_A;

                case ToonDirectBuffer::kKeyRowReadB:
                case ToonDirectBuffer::kKeyRowWriteB:
                    return W_KEY_B;

                case ToonDirectBuffer::kKeyRowReadC:
                case ToonDirectBuffer::kKeyRowWriteC:
                    return W_KEY_C;

                case ToonDirectBuffer::kKeyRowReadD:
                case ToonDirectBuffer::kKeyRowWriteD:
                    return W_KEY_D;

                default:
                    return S_BLOCK;
            }

        default:
            return 0;
    }
}

bool ToonWorkSpace::IsSBox(ToonBufferKey pKey) {
    return pKey.mKind == ToonBufferKind::kSBox;
}

bool ToonWorkSpace::IsSalt(ToonBufferKey pKey) {
    return pKey.mKind == ToonBufferKind::kSalt;
}
