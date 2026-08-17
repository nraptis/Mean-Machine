//
//  TwistDiffuse.cpp
//  MeanMachine
//
//  Created by icarus black on 6/23/26.
//

#include "TwistDiffuse.hpp"
#include "TwistShuffle.hpp"

namespace {

constexpr std::size_t kDispatchCount = 256U;
constexpr std::size_t kDispatchEntropyByteCount =
    M88::kOperationByteCount;
constexpr std::size_t kDispatchOutputByteCount = 64U;
constexpr std::size_t kInputPairByteCount =
    2U * kDispatchOutputByteCount;
constexpr std::size_t kShuffleByteCount = 512U;
constexpr std::size_t kOperationSetByteCount =
    kDispatchCount * kDispatchEntropyByteCount;
constexpr std::size_t kFirstShuffleGroupStart = 0U;
constexpr std::size_t kOperationSetAStart =
    kFirstShuffleGroupStart + (4U * kShuffleByteCount);
constexpr std::size_t kSecondShuffleGroupStart =
    kOperationSetAStart + kOperationSetByteCount;
constexpr std::size_t kThirdShuffleGroupStart =
    kSecondShuffleGroupStart + (4U * kShuffleByteCount);
constexpr std::size_t kOperationSetBStart =
    kThirdShuffleGroupStart + (4U * kShuffleByteCount);
constexpr std::size_t kFourthShuffleGroupStart =
    kOperationSetBStart + kOperationSetByteCount;

constexpr std::size_t kKeyByteCount = 2048U;
constexpr std::size_t kKeyDispatchCount = 16U;
constexpr std::size_t kKeyShuffleByteCount = 256U;
constexpr std::size_t kKeyOperationSetStart = 256U;
constexpr std::size_t kKeyOperationSetByteCount = 1536U;
constexpr std::size_t kKeyFinalShuffleStart = 1792U;

static_assert(S_BLOCK == 32768U);
static_assert(kShuffleByteCount == 512U);
static_assert(kOperationSetByteCount == 12288U);
static_assert(kOperationSetAStart == 2048U);
static_assert(kSecondShuffleGroupStart == 14336U);
static_assert(kThirdShuffleGroupStart == 16384U);
static_assert(kOperationSetBStart == 18432U);
static_assert(kFourthShuffleGroupStart == 30720U);
static_assert(kFourthShuffleGroupStart +
              (4U * kShuffleByteCount) == S_BLOCK);
static_assert(kDispatchCount * 2U * kDispatchOutputByteCount ==
              S_BLOCK);
static_assert(W_KEY == kKeyByteCount);
static_assert(kKeyDispatchCount * kInputPairByteCount == kKeyByteCount);
static_assert(kKeyOperationSetByteCount ==
              2U * kKeyDispatchCount * kDispatchEntropyByteCount);
static_assert(kKeyOperationSetStart + kKeyOperationSetByteCount ==
              kKeyFinalShuffleStart);
static_assert(kKeyFinalShuffleStart + kKeyShuffleByteCount ==
              kKeyByteCount);

void DiffuseLaneWithDomainWords(std::uint8_t *pInputLaneA,
                                std::uint8_t *pInputLaneB,
                                std::uint8_t *pOutputLane,
                                std::uint8_t *pEntropyLane,
                                std::size_t *pIndexListLeft,
                                std::size_t *pIndexListRight,
                                M88 *pMatrix,
                                int pInputOffsetA,
                                int pInputOffsetB,
                                std::uint64_t pMatrixSelect,
                                std::uint8_t pMatrixUnroll,
                                std::uint8_t pMatrixArgA,
                                std::uint8_t pMatrixArgB,
                                std::uint8_t pMatrixArgC,
                                std::uint8_t pMatrixArgD) {
    std::size_t aDestinationIndex = 0U;
    
    for (std::size_t aMatrixDiffusionIndex = 0U;
         aMatrixDiffusionIndex < kDispatchCount;
         aMatrixDiffusionIndex += 1U) {
        const std::size_t aReadIndexA =
            (pIndexListLeft[aMatrixDiffusionIndex] * kInputPairByteCount) +
            static_cast<std::size_t>(pInputOffsetA);
        const std::size_t aReadIndexB =
            (pIndexListRight[aMatrixDiffusionIndex] * kInputPairByteCount) +
            static_cast<std::size_t>(pInputOffsetB);
        const std::size_t aOperationIndexA =
            kOperationSetAStart +
            (aMatrixDiffusionIndex * kDispatchEntropyByteCount);
        const std::size_t aOperationIndexB =
            kOperationSetBStart +
            (aMatrixDiffusionIndex * kDispatchEntropyByteCount);

        if (((pEntropyLane[aOperationIndexA] ^ pMatrixSelect) & 0x7E) > 62) {
            pMatrix->Dispatch(pEntropyLane,
                              aOperationIndexA,
                              pInputLaneA,
                              aReadIndexA,
                              pOutputLane + aDestinationIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
            aDestinationIndex += kDispatchOutputByteCount;
            pMatrix->Dispatch(pEntropyLane,
                              aOperationIndexB,
                              pInputLaneB,
                              aReadIndexB,
                              pOutputLane + aDestinationIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
        } else {
            pMatrix->Dispatch(pEntropyLane,
                              aOperationIndexA,
                              pInputLaneB,
                              aReadIndexB,
                              pOutputLane + aDestinationIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
            aDestinationIndex += kDispatchOutputByteCount;
            pMatrix->Dispatch(pEntropyLane,
                              aOperationIndexB,
                              pInputLaneA,
                              aReadIndexA,
                              pOutputLane + aDestinationIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
        }
        aDestinationIndex += kDispatchOutputByteCount;
    }
}

void KeyDiffuseLaneWithDomainWords(std::uint8_t *pInputLaneA,
                                   std::uint8_t *pInputLaneB,
                                   std::uint8_t *pOutputLane,
                                   std::uint8_t *pOperationEntropyLane,
                                   std::size_t *pIndexListLeft,
                                   std::size_t *pIndexListRight,
                                   M88 *pMatrix,
                                   const std::size_t pInputOffsetA,
                                   const std::size_t pInputOffsetB,
                                   const std::uint64_t pMatrixSelect,
                                   const std::uint8_t pMatrixUnroll,
                                   const std::uint8_t pMatrixArgA,
                                   const std::uint8_t pMatrixArgB,
                                   const std::uint8_t pMatrixArgC,
                                   const std::uint8_t pMatrixArgD) {
    std::size_t aDestinationIndex = 0U;

    for (std::size_t aMatrixDiffusionIndex = 0U;
         aMatrixDiffusionIndex < kKeyDispatchCount;
         aMatrixDiffusionIndex += 1U) {
        const std::size_t aReadIndexA =
            (pIndexListLeft[aMatrixDiffusionIndex] * kInputPairByteCount) +
            pInputOffsetA;
        const std::size_t aReadIndexB =
            (pIndexListRight[aMatrixDiffusionIndex] * kInputPairByteCount) +
            pInputOffsetB;
        const std::size_t aOperationIndexA =
            kKeyOperationSetStart +
            (aMatrixDiffusionIndex * kDispatchEntropyByteCount);
        const std::size_t aOperationIndexB =
            kKeyOperationSetStart +
            ((aMatrixDiffusionIndex + kKeyDispatchCount) *
             kDispatchEntropyByteCount);

        if (((pOperationEntropyLane[aOperationIndexA] ^ pMatrixSelect) &
             0x7EU) > 62U) {
            pMatrix->Dispatch(pOperationEntropyLane,
                              aOperationIndexA,
                              pInputLaneA,
                              aReadIndexA,
                              pOutputLane + aDestinationIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
            aDestinationIndex += kDispatchOutputByteCount;
            pMatrix->Dispatch(pOperationEntropyLane,
                              aOperationIndexB,
                              pInputLaneB,
                              aReadIndexB,
                              pOutputLane + aDestinationIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
        } else {
            pMatrix->Dispatch(pOperationEntropyLane,
                              aOperationIndexA,
                              pInputLaneB,
                              aReadIndexB,
                              pOutputLane + aDestinationIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
            aDestinationIndex += kDispatchOutputByteCount;
            pMatrix->Dispatch(pOperationEntropyLane,
                              aOperationIndexB,
                              pInputLaneA,
                              aReadIndexA,
                              pOutputLane + aDestinationIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
        }
        aDestinationIndex += kDispatchOutputByteCount;
    }
}

} // namespace

void TwistDiffuse::DiffuseWithDomainWords(std::uint8_t *pEntropyLaneA,
                                          std::uint8_t *pEntropyLaneB,
                                          std::uint8_t *pEntropyLaneC,
                                          std::uint8_t *pEntropyLaneD,
                                          std::uint8_t *pInputLaneA,
                                          std::uint8_t *pInputLaneB,
                                          std::uint8_t *pInputLaneC,
                                          std::uint8_t *pInputLaneD,
                                          std::uint8_t *pOutputLaneA,
                                          std::uint8_t *pOutputLaneB,
                                          std::uint8_t *pOutputLaneC,
                                          std::uint8_t *pOutputLaneD,
                                          std::size_t *pIndexList256A,
                                          std::size_t *pIndexList256B,
                                          std::size_t *pIndexList256C,
                                          std::size_t *pIndexList256D,
                                          M88 *pMatrix,
                                          std::uint64_t pMatrixSelectA,
                                          std::uint64_t pMatrixSelectB,
                                          std::uint8_t pMatrixUnrollA,
                                          std::uint8_t pMatrixUnrollB,
                                          std::uint8_t pMatrixArgA,
                                          std::uint8_t pMatrixArgB,
                                          std::uint8_t pMatrixArgC,
                                          std::uint8_t pMatrixArgD) {
    for (std::size_t aIndex = 0U; aIndex < kDispatchCount; aIndex += 1U) {
        pIndexList256A[aIndex] = aIndex;
        pIndexList256B[aIndex] = aIndex;
        pIndexList256C[aIndex] = aIndex;
        pIndexList256D[aIndex] = aIndex;
    }

    // Shuffles 1-4
    TwistShuffle::ShuffleList256(pIndexList256A, pEntropyLaneA,
                                 kFirstShuffleGroupStart + (0U * kShuffleByteCount),
                                 kFirstShuffleGroupStart + (1U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256B, pEntropyLaneB,
                                 kFirstShuffleGroupStart + (1U * kShuffleByteCount),
                                 kFirstShuffleGroupStart + (2U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256C, pEntropyLaneC,
                                 kFirstShuffleGroupStart + (2U * kShuffleByteCount),
                                 kFirstShuffleGroupStart + (3U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256D, pEntropyLaneD,
                                 kFirstShuffleGroupStart + (3U * kShuffleByteCount),
                                 kFirstShuffleGroupStart + (4U * kShuffleByteCount), 1U);

    // Shuffles 5-8
    TwistShuffle::ShuffleList256(pIndexList256A, pEntropyLaneA,
                                 kSecondShuffleGroupStart + (0U * kShuffleByteCount),
                                 kSecondShuffleGroupStart + (1U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256B, pEntropyLaneB,
                                 kSecondShuffleGroupStart + (1U * kShuffleByteCount),
                                 kSecondShuffleGroupStart + (2U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256C, pEntropyLaneC,
                                 kSecondShuffleGroupStart + (2U * kShuffleByteCount),
                                 kSecondShuffleGroupStart + (3U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256D, pEntropyLaneD,
                                 kSecondShuffleGroupStart + (3U * kShuffleByteCount),
                                 kSecondShuffleGroupStart + (4U * kShuffleByteCount), 1U);

    // Shuffles 9-12
    TwistShuffle::ShuffleList256(pIndexList256A, pEntropyLaneA,
                                 kThirdShuffleGroupStart + (0U * kShuffleByteCount),
                                 kThirdShuffleGroupStart + (1U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256B, pEntropyLaneB,
                                 kThirdShuffleGroupStart + (1U * kShuffleByteCount),
                                 kThirdShuffleGroupStart + (2U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256C, pEntropyLaneC,
                                 kThirdShuffleGroupStart + (2U * kShuffleByteCount),
                                 kThirdShuffleGroupStart + (3U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256D, pEntropyLaneD,
                                 kThirdShuffleGroupStart + (3U * kShuffleByteCount),
                                 kThirdShuffleGroupStart + (4U * kShuffleByteCount), 1U);

    // Shuffles 13-16
    TwistShuffle::ShuffleList256(pIndexList256A, pEntropyLaneA,
                                 kFourthShuffleGroupStart + (0U * kShuffleByteCount),
                                 kFourthShuffleGroupStart + (1U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256B, pEntropyLaneB,
                                 kFourthShuffleGroupStart + (1U * kShuffleByteCount),
                                 kFourthShuffleGroupStart + (2U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256C, pEntropyLaneC,
                                 kFourthShuffleGroupStart + (2U * kShuffleByteCount),
                                 kFourthShuffleGroupStart + (3U * kShuffleByteCount), 1U);
    TwistShuffle::ShuffleList256(pIndexList256D, pEntropyLaneD,
                                 kFourthShuffleGroupStart + (3U * kShuffleByteCount),
                                 kFourthShuffleGroupStart + (4U * kShuffleByteCount), 1U);
    
    // A @ 0, C @ 64
    DiffuseLaneWithDomainWords(pInputLaneA,
                               pInputLaneC,
                               pOutputLaneA,
                               pEntropyLaneA,
                               pIndexList256A,
                               pIndexList256B,
                               pMatrix,
                               0,
                               64,
                               pMatrixSelectA,
                               pMatrixUnrollA,
                               pMatrixArgA,
                               pMatrixArgB,
                               pMatrixArgC,
                               pMatrixArgD);
    
    // A @ 64, D @ 0
    DiffuseLaneWithDomainWords(pInputLaneA,
                               pInputLaneD,
                               pOutputLaneB,
                               pEntropyLaneB,
                               pIndexList256C,
                               pIndexList256D,
                               pMatrix,
                               64,
                               0,
                               pMatrixSelectB,
                               pMatrixUnrollB,
                               pMatrixArgA,
                               pMatrixArgB,
                               pMatrixArgC,
                               pMatrixArgD);

    // B @ 64, C @ 0
    DiffuseLaneWithDomainWords(pInputLaneB,
                               pInputLaneC,
                               pOutputLaneC,
                               pEntropyLaneC,
                               pIndexList256A,
                               pIndexList256B,
                               pMatrix,
                               64,
                               0,
                               pMatrixSelectA,
                               pMatrixUnrollA,
                               pMatrixArgA,
                               pMatrixArgB,
                               pMatrixArgC,
                               pMatrixArgD);

    // B @ 0, D @ 64
    DiffuseLaneWithDomainWords(pInputLaneB,
                               pInputLaneD,
                               pOutputLaneD,
                               pEntropyLaneD,
                               pIndexList256C,
                               pIndexList256D,
                               pMatrix,
                               0,
                               64,
                               pMatrixSelectB,
                               pMatrixUnrollB,
                               pMatrixArgA,
                               pMatrixArgB,
                               pMatrixArgC,
                               pMatrixArgD);
}

void TwistDiffuse::KeyDiffuseWithDomainWords(
    std::uint8_t *pEntropyLaneA,
    std::uint8_t *pEntropyLaneB,
    std::uint8_t *pEntropyLaneC,
    std::uint8_t *pEntropyLaneD,
    std::uint8_t *pInputLaneA,
    std::uint8_t *pInputLaneB,
    std::uint8_t *pInputLaneC,
    std::uint8_t *pInputLaneD,
    std::uint8_t *pOutputLaneA,
    std::uint8_t *pOutputLaneB,
    std::uint8_t *pOutputLaneC,
    std::uint8_t *pOutputLaneD,
    std::size_t *pIndexList16A,
    std::size_t *pIndexList16B,
    std::size_t *pIndexList16C,
    std::size_t *pIndexList16D,
    M88 *pMatrix,
    std::uint64_t pMatrixSelectA,
    std::uint64_t pMatrixSelectB,
    std::uint8_t pMatrixUnrollA,
    std::uint8_t pMatrixUnrollB,
    std::uint8_t pMatrixArgA,
    std::uint8_t pMatrixArgB,
    std::uint8_t pMatrixArgC,
    std::uint8_t pMatrixArgD) {
    for (std::size_t aIndex = 0U;
         aIndex < kKeyDispatchCount;
         aIndex += 1U) {
        pIndexList16A[aIndex] = aIndex;
        pIndexList16B[aIndex] = aIndex;
        pIndexList16C[aIndex] = aIndex;
        pIndexList16D[aIndex] = aIndex;
    }

    TwistShuffle::ShuffleList16(pIndexList16A,
                                pEntropyLaneA,
                                0U,
                                kKeyShuffleByteCount,
                                3U);
    TwistShuffle::ShuffleList16(pIndexList16B,
                                pEntropyLaneB,
                                0U,
                                kKeyShuffleByteCount,
                                3U);
    TwistShuffle::ShuffleList16(pIndexList16C,
                                pEntropyLaneC,
                                0U,
                                kKeyShuffleByteCount,
                                3U);
    TwistShuffle::ShuffleList16(pIndexList16D,
                                pEntropyLaneD,
                                0U,
                                kKeyShuffleByteCount,
                                3U);

    TwistShuffle::ShuffleList16(pIndexList16A,
                                pEntropyLaneA,
                                kKeyFinalShuffleStart,
                                kKeyByteCount,
                                3U);
    TwistShuffle::ShuffleList16(pIndexList16B,
                                pEntropyLaneB,
                                kKeyFinalShuffleStart,
                                kKeyByteCount,
                                3U);
    TwistShuffle::ShuffleList16(pIndexList16C,
                                pEntropyLaneC,
                                kKeyFinalShuffleStart,
                                kKeyByteCount,
                                3U);
    TwistShuffle::ShuffleList16(pIndexList16D,
                                pEntropyLaneD,
                                kKeyFinalShuffleStart,
                                kKeyByteCount,
                                3U);

    // A @ 0, C @ 64
    KeyDiffuseLaneWithDomainWords(pInputLaneA,
                                  pInputLaneC,
                                  pOutputLaneA,
                                  pEntropyLaneA,
                                  pIndexList16A,
                                  pIndexList16B,
                                  pMatrix,
                                  0U,
                                  64U,
                                  pMatrixSelectA,
                                  pMatrixUnrollA,
                                  pMatrixArgA,
                                  pMatrixArgB,
                                  pMatrixArgC,
                                  pMatrixArgD);

    // A @ 64, D @ 0
    KeyDiffuseLaneWithDomainWords(pInputLaneA,
                                  pInputLaneD,
                                  pOutputLaneB,
                                  pEntropyLaneB,
                                  pIndexList16C,
                                  pIndexList16D,
                                  pMatrix,
                                  64U,
                                  0U,
                                  pMatrixSelectB,
                                  pMatrixUnrollB,
                                  pMatrixArgA,
                                  pMatrixArgB,
                                  pMatrixArgC,
                                  pMatrixArgD);

    // B @ 64, C @ 0
    KeyDiffuseLaneWithDomainWords(pInputLaneB,
                                  pInputLaneC,
                                  pOutputLaneC,
                                  pEntropyLaneC,
                                  pIndexList16A,
                                  pIndexList16B,
                                  pMatrix,
                                  64U,
                                  0U,
                                  pMatrixSelectA,
                                  pMatrixUnrollA,
                                  pMatrixArgA,
                                  pMatrixArgB,
                                  pMatrixArgC,
                                  pMatrixArgD);

    // B @ 0, D @ 64
    KeyDiffuseLaneWithDomainWords(pInputLaneB,
                                  pInputLaneD,
                                  pOutputLaneD,
                                  pEntropyLaneD,
                                  pIndexList16C,
                                  pIndexList16D,
                                  pMatrix,
                                  0U,
                                  64U,
                                  pMatrixSelectB,
                                  pMatrixUnrollB,
                                  pMatrixArgA,
                                  pMatrixArgB,
                                  pMatrixArgC,
                                  pMatrixArgD);
}

void TwistDiffuse::KeyDiffuseWithDomainWordsA(
    std::uint8_t *pEntropyLaneA,
    std::uint8_t *pEntropyLaneB,
    std::uint8_t *pEntropyLaneC,
    std::uint8_t *pEntropyLaneD,
    std::uint8_t *pInputLaneA,
    std::uint8_t *pInputLaneB,
    std::uint8_t *pInputLaneC,
    std::uint8_t *pInputLaneD,
    std::uint8_t *pOutputLaneA,
    std::uint8_t *pOutputLaneB,
    std::uint8_t *pOutputLaneC,
    std::uint8_t *pOutputLaneD,
    std::size_t *pIndexList16A,
    std::size_t *pIndexList16B,
    std::size_t *pIndexList16C,
    std::size_t *pIndexList16D,
    M88 *pMatrix,
    std::uint64_t pMatrixSelectA,
    std::uint64_t pMatrixSelectB,
    std::uint8_t pMatrixUnrollA,
    std::uint8_t pMatrixUnrollB,
    std::uint8_t pMatrixArgA,
    std::uint8_t pMatrixArgB,
    std::uint8_t pMatrixArgC,
    std::uint8_t pMatrixArgD) {
    KeyDiffuseWithDomainWords(pEntropyLaneA, pEntropyLaneB,
                              pEntropyLaneC, pEntropyLaneD,
                              pInputLaneA, pInputLaneB,
                              pInputLaneC, pInputLaneD,
                              pOutputLaneA, pOutputLaneB,
                              pOutputLaneC, pOutputLaneD,
                              pIndexList16A, pIndexList16B,
                              pIndexList16C, pIndexList16D,
                              pMatrix,
                              pMatrixSelectA, pMatrixSelectB,
                              pMatrixUnrollA, pMatrixUnrollB,
                              pMatrixArgA, pMatrixArgB,
                              pMatrixArgC, pMatrixArgD);
}

void TwistDiffuse::KeyDiffuseWithDomainWordsB(
    std::uint8_t *pEntropyLaneA,
    std::uint8_t *pEntropyLaneB,
    std::uint8_t *pEntropyLaneC,
    std::uint8_t *pEntropyLaneD,
    std::uint8_t *pInputLaneA,
    std::uint8_t *pInputLaneB,
    std::uint8_t *pInputLaneC,
    std::uint8_t *pInputLaneD,
    std::uint8_t *pOutputLaneA,
    std::uint8_t *pOutputLaneB,
    std::uint8_t *pOutputLaneC,
    std::uint8_t *pOutputLaneD,
    std::size_t *pIndexList16A,
    std::size_t *pIndexList16B,
    std::size_t *pIndexList16C,
    std::size_t *pIndexList16D,
    M88 *pMatrix,
    std::uint64_t pMatrixSelectA,
    std::uint64_t pMatrixSelectB,
    std::uint8_t pMatrixUnrollA,
    std::uint8_t pMatrixUnrollB,
    std::uint8_t pMatrixArgA,
    std::uint8_t pMatrixArgB,
    std::uint8_t pMatrixArgC,
    std::uint8_t pMatrixArgD) {
    KeyDiffuseWithDomainWords(pEntropyLaneA + W_KEY,
                              pEntropyLaneB + W_KEY,
                              pEntropyLaneC + W_KEY,
                              pEntropyLaneD + W_KEY,
                              pInputLaneA + W_KEY,
                              pInputLaneB + W_KEY,
                              pInputLaneC + W_KEY,
                              pInputLaneD + W_KEY,
                              pOutputLaneA + W_KEY,
                              pOutputLaneB + W_KEY,
                              pOutputLaneC + W_KEY,
                              pOutputLaneD + W_KEY,
                              pIndexList16A, pIndexList16B,
                              pIndexList16C, pIndexList16D,
                              pMatrix,
                              pMatrixSelectA, pMatrixSelectB,
                              pMatrixUnrollA, pMatrixUnrollB,
                              pMatrixArgA, pMatrixArgB,
                              pMatrixArgC, pMatrixArgD);
}
