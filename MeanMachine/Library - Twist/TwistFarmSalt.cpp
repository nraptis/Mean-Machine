//
//  TwistFarmSalt.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/6/26.
//

#include "TwistFarmSalt.hpp"

namespace {

constexpr std::size_t kSaltByteCount =
    static_cast<std::size_t>(S_SALT) * sizeof(std::uint64_t);
constexpr std::size_t kSourceSliceCount =
    static_cast<std::size_t>(S_BLOCK) / kSaltByteCount;

static_assert(kSourceSliceCount == 8U,
              "TwistFarmSalt expects eight salt-sized source slices.");
static_assert((8U * kSaltByteCount) == S_BLOCK,
              "Eight salts must consume exactly one source lane.");

} // namespace

TwistFarmSalt::TwistFarmSalt() {
    
}

void TwistFarmSalt::Derive(const std::uint8_t *pSource,
                           std::uint64_t *pSaltA,
                           std::uint64_t *pSaltB,
                           std::uint64_t *pSaltC,
                           std::uint64_t *pSaltD,
                           std::uint64_t *pSaltE,
                           std::uint64_t *pSaltF,
                           std::uint64_t *pSaltG,
                           std::uint64_t *pSaltH) {
    if (pSource == nullptr) {
        return;
    }

    const std::uint8_t *aSaltSliceA =
        pSource + (0U * kSaltByteCount);
    const std::uint8_t *aSaltSliceB =
        pSource + (1U * kSaltByteCount);
    const std::uint8_t *aSaltSliceC =
        pSource + (2U * kSaltByteCount);
    const std::uint8_t *aSaltSliceD =
        pSource + (3U * kSaltByteCount);
    const std::uint8_t *aSaltSliceE =
        pSource + (4U * kSaltByteCount);
    const std::uint8_t *aSaltSliceF =
        pSource + (5U * kSaltByteCount);
    const std::uint8_t *aSaltSliceG =
        pSource + (6U * kSaltByteCount);
    const std::uint8_t *aSaltSliceH =
        pSource + (7U * kSaltByteCount);

    if (pSaltA != nullptr) {
        std::memcpy(pSaltA, aSaltSliceA, kSaltByteCount);
    }
    if (pSaltB != nullptr) {
        std::memcpy(pSaltB, aSaltSliceB, kSaltByteCount);
    }
    if (pSaltC != nullptr) {
        std::memcpy(pSaltC, aSaltSliceC, kSaltByteCount);
    }
    if (pSaltD != nullptr) {
        std::memcpy(pSaltD, aSaltSliceD, kSaltByteCount);
    }
    if (pSaltE != nullptr) {
        std::memcpy(pSaltE, aSaltSliceE, kSaltByteCount);
    }
    if (pSaltF != nullptr) {
        std::memcpy(pSaltF, aSaltSliceF, kSaltByteCount);
    }
    if (pSaltG != nullptr) {
        std::memcpy(pSaltG, aSaltSliceG, kSaltByteCount);
    }
    if (pSaltH != nullptr) {
        std::memcpy(pSaltH, aSaltSliceH, kSaltByteCount);
    }
}

void TwistFarmSalt::Derive(const std::uint8_t *pSource,
                           TwistDomainSeedRoundMaterial *pRoundMaterial) {
    if (pRoundMaterial == nullptr) {
        return;
    }
    Derive(pSource,
           pRoundMaterial->mSaltA,
           pRoundMaterial->mSaltB,
           pRoundMaterial->mSaltC,
           pRoundMaterial->mSaltD,
           pRoundMaterial->mSaltE,
           pRoundMaterial->mSaltF,
           pRoundMaterial->mSaltG,
           pRoundMaterial->mSaltH);
}

void TwistFarmSalt::Zero() {
    
}
