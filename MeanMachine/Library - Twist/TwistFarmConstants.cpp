//
//  TwistRipConstants.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "TwistFarmConstants.hpp"

TwistFarmConstants::TwistFarmConstants() {

}

std::uint64_t TwistFarmConstants::ReadU64(const std::uint8_t *pSource,
                                          int *pIndex) {
    if ((pSource == nullptr) || (pIndex == nullptr)) {
        return 0ULL;
    }

    const int aIndex = *pIndex;

    std::uint64_t aResult = 0ULL;
    aResult |= static_cast<std::uint64_t>(pSource[aIndex + 0]) << 0U;
    aResult |= static_cast<std::uint64_t>(pSource[aIndex + 1]) << 8U;
    aResult |= static_cast<std::uint64_t>(pSource[aIndex + 2]) << 16U;
    aResult |= static_cast<std::uint64_t>(pSource[aIndex + 3]) << 24U;
    aResult |= static_cast<std::uint64_t>(pSource[aIndex + 4]) << 32U;
    aResult |= static_cast<std::uint64_t>(pSource[aIndex + 5]) << 40U;
    aResult |= static_cast<std::uint64_t>(pSource[aIndex + 6]) << 48U;
    aResult |= static_cast<std::uint64_t>(pSource[aIndex + 7]) << 56U;

    *pIndex += 8;

    return aResult;
}

std::uint8_t TwistFarmConstants::ReadU8(const std::uint8_t *pSource,
                                        int *pIndex) {
    if ((pSource == nullptr) || (pIndex == nullptr)) {
        return 0U;
    }

    const std::uint8_t aResult = pSource[*pIndex];
    *pIndex += 1;

    return aResult;
}

void TwistFarmConstants::Derive(const std::uint8_t *pSource,
                                TwistDomainConstants *pConstants) {
    if ((pSource == nullptr) || (pConstants == nullptr)) {
        return;
    }

    int aIndex = 0;

    pConstants->mIngress = ReadU64(pSource, &aIndex);
    pConstants->mScatter = ReadU64(pSource, &aIndex);
    pConstants->mCross = ReadU64(pSource, &aIndex);

    pConstants->mDomainConstantPublicIngress = ReadU64(pSource, &aIndex);
    pConstants->mDomainConstantPrivateIngress = ReadU64(pSource, &aIndex);
    pConstants->mDomainConstantCrossIngress = ReadU64(pSource, &aIndex);

    pConstants->mMatrixSelectA = ReadU64(pSource, &aIndex);
    pConstants->mMatrixSelectB = ReadU64(pSource, &aIndex);

    pConstants->mMatrixUnrollA = ReadU8(pSource, &aIndex);
    pConstants->mMatrixUnrollB = ReadU8(pSource, &aIndex);

    pConstants->mMatrixArgA = ReadU8(pSource, &aIndex);
    pConstants->mMatrixArgB = ReadU8(pSource, &aIndex);
    pConstants->mMatrixArgC = ReadU8(pSource, &aIndex);
    pConstants->mMatrixArgD = ReadU8(pSource, &aIndex);

    pConstants->mMaskMutateA = ReadU8(pSource, &aIndex);
    pConstants->mMaskMutateB = ReadU8(pSource, &aIndex);
}
