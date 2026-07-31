//
//  TwistFarm.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "TwistFarm.hpp"

#include "TwistFarmSalt.hpp"
#include "TwistMix32.hpp"
#include "TwistMix64.hpp"

static_assert(S_BLOCK == 32768,
              "TwistFarm::Farm requires S_BLOCK to be exactly 32768 bytes.");

void TwistFarm::Farm(TwistFarmSalt *pFarmSalt,
                     const std::uint8_t *pSaltLaneA,
                     const std::uint8_t *pSaltLaneB,
                     const std::uint8_t *pSaltLaneC,
                     const std::uint8_t *pConstantLane,
                     std::uint8_t *pFoldLaneA,
                     std::uint8_t *pFoldLaneB,
                     std::uint8_t *pFoldLaneC,
                     TwistDomainSaltSet *pSaltSet,
                     TwistDomainConstants *pConstants) {
    if ((pFarmSalt == nullptr) ||
        (pSaltLaneA == nullptr) ||
        (pSaltLaneB == nullptr) ||
        (pSaltLaneC == nullptr) ||
        (pConstantLane == nullptr) ||
        (pFoldLaneA == nullptr) ||
        (pFoldLaneB == nullptr) ||
        (pFoldLaneC == nullptr) ||
        (pSaltSet == nullptr) ||
        (pConstants == nullptr)) {
        return;
    }

    FarmSalts(pFarmSalt,
              pSaltLaneA,
              pSaltLaneB,
              pSaltLaneC,
              pSaltSet);
    FarmConstants(pConstantLane,
                  pFoldLaneA,
                  pFoldLaneB,
                  pFoldLaneC,
                  pConstants);
}

void TwistFarm::FarmSalts(TwistFarmSalt *pFarmSalt,
                          const std::uint8_t *pSourceLaneA,
                          const std::uint8_t *pSourceLaneB,
                          const std::uint8_t *pSourceLaneC,
                          TwistDomainSaltSet *pSaltSet) {
    if ((pFarmSalt == nullptr) ||
        (pSourceLaneA == nullptr) ||
        (pSourceLaneB == nullptr) ||
        (pSourceLaneC == nullptr) ||
        (pSaltSet == nullptr)) {
        return;
    }

    pFarmSalt->Derive(pSourceLaneA,
                      &(pSaltSet->mOrbiterAssign));
    pFarmSalt->Derive(pSourceLaneB,
                      &(pSaltSet->mOrbiterUpdate));
    pFarmSalt->Derive(pSourceLaneC,
                      &(pSaltSet->mWandererUpdate));
}

void TwistFarm::FarmConstants(const std::uint8_t *pSource,
                              std::uint8_t *pFoldLaneA,
                              std::uint8_t *pFoldLaneB,
                              std::uint8_t *pFoldLaneC,
                              TwistDomainConstants *pConstants) {
    if ((pSource == nullptr) ||
        (pFoldLaneA == nullptr) ||
        (pFoldLaneB == nullptr) ||
        (pFoldLaneC == nullptr) ||
        (pConstants == nullptr)) {
        return;
    }
    if ((pSource == pFoldLaneA) ||
        (pSource == pFoldLaneB) ||
        (pSource == pFoldLaneC) ||
        (pFoldLaneA == pFoldLaneB) ||
        (pFoldLaneA == pFoldLaneC) ||
        (pFoldLaneB == pFoldLaneC)) {
        return;
    }

    if ((reinterpret_cast<std::uintptr_t>(pSource) & 7U) != 0U) {
        return;
    }
    if ((reinterpret_cast<std::uintptr_t>(pFoldLaneA) & 7U) != 0U) {
        return;
    }
    if ((reinterpret_cast<std::uintptr_t>(pFoldLaneB) & 7U) != 0U) {
        return;
    }
    if ((reinterpret_cast<std::uintptr_t>(pFoldLaneC) & 7U) != 0U) {
        return;
    }

    const std::uint64_t *aSource =
        reinterpret_cast<const std::uint64_t *>(pSource);
    std::uint64_t *aFoldLaneA =
        reinterpret_cast<std::uint64_t *>(pFoldLaneA);
    std::uint64_t *aFoldLaneB =
        reinterpret_cast<std::uint64_t *>(pFoldLaneB);
    std::uint64_t *aFoldLaneC =
        reinterpret_cast<std::uint64_t *>(pFoldLaneC);

    //
    // Fold eight 4,096-byte pieces into 512 64-bit words.
    //
    for (std::size_t aIndex = 0U; aIndex < 512U; aIndex += 1U) {
        std::uint64_t aFold = 0ULL;
        aFold = TwistMix64::DiffuseA(aFold ^ aSource[aIndex + 0U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aSource[aIndex + 512U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aSource[aIndex + 1024U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aSource[aIndex + 1536U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aSource[aIndex + 2048U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aSource[aIndex + 2560U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aSource[aIndex + 3072U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aSource[aIndex + 3584U]);
        aFoldLaneA[aIndex] = aFold;
    }

    //
    // Fold eight 512-byte pieces into 64 64-bit words.
    //
    for (std::size_t aIndex = 0U; aIndex < 64U; aIndex += 1U) {
        std::uint64_t aFold = 0ULL;
        aFold = TwistMix64::DiffuseA(aFold ^ aFoldLaneA[aIndex + 0U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aFoldLaneA[aIndex + 64U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aFoldLaneA[aIndex + 128U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aFoldLaneA[aIndex + 192U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aFoldLaneA[aIndex + 256U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aFoldLaneA[aIndex + 320U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aFoldLaneA[aIndex + 384U]);
        aFold = TwistMix64::DiffuseA(aFold ^ aFoldLaneA[aIndex + 448U]);
        aFoldLaneB[aIndex] = aFold;
    }

    //
    // Fold four 128-byte pieces into 16 64-bit words.
    //
    // The low and high halves are folded independently with TwistMix32.
    //
    for (std::size_t aIndex = 0U; aIndex < 16U; aIndex += 1U) {
        std::uint64_t aPieceA = aFoldLaneB[aIndex + 0U];
        std::uint64_t aPieceB = aFoldLaneB[aIndex + 16U];
        std::uint64_t aPieceC = aFoldLaneB[aIndex + 32U];
        std::uint64_t aPieceD = aFoldLaneB[aIndex + 48U];

        std::uint32_t aFoldLow = 0U;
        aFoldLow = TwistMix32::DiffuseA(
            aFoldLow ^ static_cast<std::uint32_t>(aPieceA));
        aFoldLow = TwistMix32::DiffuseA(
            aFoldLow ^ static_cast<std::uint32_t>(aPieceB));
        aFoldLow = TwistMix32::DiffuseA(
            aFoldLow ^ static_cast<std::uint32_t>(aPieceC));
        aFoldLow = TwistMix32::DiffuseA(
            aFoldLow ^ static_cast<std::uint32_t>(aPieceD));

        std::uint32_t aFoldHigh = 0U;
        aFoldHigh = TwistMix32::DiffuseA(
            aFoldHigh ^ static_cast<std::uint32_t>(aPieceA >> 32U));
        aFoldHigh = TwistMix32::DiffuseA(
            aFoldHigh ^ static_cast<std::uint32_t>(aPieceB >> 32U));
        aFoldHigh = TwistMix32::DiffuseA(
            aFoldHigh ^ static_cast<std::uint32_t>(aPieceC >> 32U));
        aFoldHigh = TwistMix32::DiffuseA(
            aFoldHigh ^ static_cast<std::uint32_t>(aPieceD >> 32U));

        std::uint64_t aFold = static_cast<std::uint64_t>(aFoldLow);
        aFold |= static_cast<std::uint64_t>(aFoldHigh) << 32U;
        aFoldLaneC[aIndex] = aFold;
    }

    //
    // The final lane contains sixteen 64-bit words. Use the first eleven.
    //
    std::uint64_t aIngress = aFoldLaneC[0U];
    std::uint64_t aScatter = aFoldLaneC[1U];
    std::uint64_t aCross = aFoldLaneC[2U];
    std::uint64_t aMatrixSelectA = aFoldLaneC[3U];
    std::uint64_t aMatrixSelectB = aFoldLaneC[4U];
    std::uint64_t aMatrixUnrollA = aFoldLaneC[5U];
    std::uint64_t aMatrixUnrollB = aFoldLaneC[6U];
    std::uint64_t aMatrixArgA = aFoldLaneC[7U];
    std::uint64_t aMatrixArgB = aFoldLaneC[8U];
    std::uint64_t aMatrixArgC = aFoldLaneC[9U];
    std::uint64_t aMatrixArgD = aFoldLaneC[10U];

    //
    // Fold each 64-bit small constant down to eight bits.
    //
    aMatrixUnrollA = TwistMix64::DiffuseA(aMatrixUnrollA);
    aMatrixUnrollA ^= aMatrixUnrollA >> 32U;
    aMatrixUnrollA ^= aMatrixUnrollA >> 16U;
    aMatrixUnrollA ^= aMatrixUnrollA >> 8U;

    aMatrixUnrollB = TwistMix64::DiffuseA(aMatrixUnrollB);
    aMatrixUnrollB ^= aMatrixUnrollB >> 32U;
    aMatrixUnrollB ^= aMatrixUnrollB >> 16U;
    aMatrixUnrollB ^= aMatrixUnrollB >> 8U;

    aMatrixArgA = TwistMix64::DiffuseA(aMatrixArgA);
    aMatrixArgA ^= aMatrixArgA >> 32U;
    aMatrixArgA ^= aMatrixArgA >> 16U;
    aMatrixArgA ^= aMatrixArgA >> 8U;

    aMatrixArgB = TwistMix64::DiffuseA(aMatrixArgB);
    aMatrixArgB ^= aMatrixArgB >> 32U;
    aMatrixArgB ^= aMatrixArgB >> 16U;
    aMatrixArgB ^= aMatrixArgB >> 8U;

    aMatrixArgC = TwistMix64::DiffuseA(aMatrixArgC);
    aMatrixArgC ^= aMatrixArgC >> 32U;
    aMatrixArgC ^= aMatrixArgC >> 16U;
    aMatrixArgC ^= aMatrixArgC >> 8U;

    aMatrixArgD = TwistMix64::DiffuseA(aMatrixArgD);
    aMatrixArgD ^= aMatrixArgD >> 32U;
    aMatrixArgD ^= aMatrixArgD >> 16U;
    aMatrixArgD ^= aMatrixArgD >> 8U;

    pConstants->mIngress = aIngress;
    pConstants->mScatter = aScatter;
    pConstants->mCross = aCross;
    pConstants->mMatrixSelectA = aMatrixSelectA;
    pConstants->mMatrixSelectB = aMatrixSelectB;
    pConstants->mMatrixUnrollA =
        static_cast<std::uint8_t>(aMatrixUnrollA);
    pConstants->mMatrixUnrollB =
        static_cast<std::uint8_t>(aMatrixUnrollB);
    pConstants->mMatrixArgA =
        static_cast<std::uint8_t>(aMatrixArgA);
    pConstants->mMatrixArgB =
        static_cast<std::uint8_t>(aMatrixArgB);
    pConstants->mMatrixArgC =
        static_cast<std::uint8_t>(aMatrixArgC);
    pConstants->mMatrixArgD =
        static_cast<std::uint8_t>(aMatrixArgD);
}
