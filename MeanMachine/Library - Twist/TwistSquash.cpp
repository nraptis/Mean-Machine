//
//  TwistSquash.cpp
//  MeanMachine
//
//  Created by icarus black on 6/23/26.
//

#include "TwistSquash.hpp"

void TwistSquash::SquashA(std::uint8_t *pInputLaneA,
                          std::uint8_t *pInputLaneB,
                          std::uint8_t *pInputLaneC,
                          std::uint8_t *pInputLaneD,
                          std::uint8_t *pOutputLane) {
    for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
        std::uint32_t aSquash = static_cast<std::uint32_t>(pInputLaneA[aIndex]);
        aSquash |= static_cast<std::uint32_t>(pInputLaneB[aIndex]) << 8U;
        aSquash |= static_cast<std::uint32_t>(pInputLaneC[aIndex]) << 16U;
        aSquash |= static_cast<std::uint32_t>(pInputLaneD[aIndex]) << 24U;
        aSquash ^= aSquash >> 16U;
        aSquash *= 0x85EBCA6BU;
        aSquash ^= aSquash >> 13U;
        aSquash *= 0xC2B2AE35U;
        aSquash ^= aSquash >> 16U;
        pOutputLane[aIndex] = static_cast<std::uint8_t>(aSquash);
    }
}

void TwistSquash::SquashB(std::uint8_t *pInputLaneA,
                          std::uint8_t *pInputLaneB,
                          std::uint8_t *pInputLaneC,
                          std::uint8_t *pInputLaneD,
                          std::uint8_t *pOutputLane) {
    for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
        std::uint32_t aSquash = static_cast<std::uint32_t>(pInputLaneA[aIndex]);
        aSquash |= static_cast<std::uint32_t>(pInputLaneB[aIndex]) << 8U;
        aSquash |= static_cast<std::uint32_t>(pInputLaneC[aIndex]) << 16U;
        aSquash |= static_cast<std::uint32_t>(pInputLaneD[aIndex]) << 24U;
        aSquash ^= aSquash >> 16U;
        aSquash *= 0x21F0AAADU;
        aSquash ^= aSquash >> 15U;
        aSquash *= 0x735A2D97U;
        aSquash ^= aSquash >> 15U;
        pOutputLane[aIndex] = static_cast<std::uint8_t>(aSquash);
    }
}

void TwistSquash::SquashC(std::uint8_t *pInputLaneA,
                          std::uint8_t *pInputLaneB,
                          std::uint8_t *pInputLaneC,
                          std::uint8_t *pInputLaneD,
                          std::uint8_t *pOutputLane) {
    for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
        std::uint32_t aSquash = static_cast<std::uint32_t>(pInputLaneA[aIndex]);
        aSquash |= static_cast<std::uint32_t>(pInputLaneB[aIndex]) << 8U;
        aSquash |= static_cast<std::uint32_t>(pInputLaneC[aIndex]) << 16U;
        aSquash |= static_cast<std::uint32_t>(pInputLaneD[aIndex]) << 24U;
        aSquash ^= aSquash >> 16U;
        aSquash *= 0x7FEB352DU;
        aSquash ^= aSquash >> 15U;
        aSquash *= 0x846CA68BU;
        aSquash ^= aSquash >> 16U;
        pOutputLane[aIndex] = static_cast<std::uint8_t>(aSquash);
    }
}

void TwistSquash::FoldQuarterA(std::uint8_t *pInputLaneA,
                               std::uint8_t *pInputLaneB,
                               std::uint8_t *pInputLaneC,
                               std::uint8_t *pInputLaneD,
                               std::uint8_t *pOutputLaneA,
                               std::uint8_t *pOutputLaneB,
                               std::uint8_t *pOutputLaneC,
                               std::uint8_t *pOutputLaneD) {
    static_assert(S_BLOCK == (S_QUARTER * 4U),
                  "FoldQuarterA requires four equal input quarters.");

    for (std::size_t aIndex = 0U;
         aIndex < static_cast<std::size_t>(S_QUARTER);
         aIndex += 1U) {
        const std::size_t aInputIndexA = aIndex;
        const std::size_t aInputIndexB = S_QUARTER + aIndex;
        const std::size_t aInputIndexC = (S_QUARTER * 2U) + aIndex;
        const std::size_t aInputIndexD = (S_QUARTER * 3U) + aIndex;

        std::uint32_t aFoldA =
            static_cast<std::uint32_t>(pInputLaneA[aInputIndexA]);
        aFoldA |=
            static_cast<std::uint32_t>(pInputLaneB[aInputIndexA]) << 8U;
        aFoldA |=
            static_cast<std::uint32_t>(pInputLaneC[aInputIndexA]) << 16U;
        aFoldA |=
            static_cast<std::uint32_t>(pInputLaneD[aInputIndexA]) << 24U;
        aFoldA ^= aFoldA >> 16U;
        aFoldA *= 0x85EBCA6BU;
        aFoldA ^= aFoldA >> 13U;
        aFoldA *= 0xC2B2AE35U;
        aFoldA ^= aFoldA >> 16U;
        pOutputLaneA[aIndex] = static_cast<std::uint8_t>(aFoldA);

        std::uint32_t aFoldB =
            static_cast<std::uint32_t>(pInputLaneA[aInputIndexB]);
        aFoldB |=
            static_cast<std::uint32_t>(pInputLaneB[aInputIndexB]) << 8U;
        aFoldB |=
            static_cast<std::uint32_t>(pInputLaneC[aInputIndexB]) << 16U;
        aFoldB |=
            static_cast<std::uint32_t>(pInputLaneD[aInputIndexB]) << 24U;
        aFoldB ^= aFoldB >> 16U;
        aFoldB *= 0x85EBCA6BU;
        aFoldB ^= aFoldB >> 13U;
        aFoldB *= 0xC2B2AE35U;
        aFoldB ^= aFoldB >> 16U;
        pOutputLaneB[aIndex] = static_cast<std::uint8_t>(aFoldB);

        std::uint32_t aFoldC =
            static_cast<std::uint32_t>(pInputLaneA[aInputIndexC]);
        aFoldC |=
            static_cast<std::uint32_t>(pInputLaneB[aInputIndexC]) << 8U;
        aFoldC |=
            static_cast<std::uint32_t>(pInputLaneC[aInputIndexC]) << 16U;
        aFoldC |=
            static_cast<std::uint32_t>(pInputLaneD[aInputIndexC]) << 24U;
        aFoldC ^= aFoldC >> 16U;
        aFoldC *= 0x85EBCA6BU;
        aFoldC ^= aFoldC >> 13U;
        aFoldC *= 0xC2B2AE35U;
        aFoldC ^= aFoldC >> 16U;
        pOutputLaneC[aIndex] = static_cast<std::uint8_t>(aFoldC);

        std::uint32_t aFoldD =
            static_cast<std::uint32_t>(pInputLaneA[aInputIndexD]);
        aFoldD |=
            static_cast<std::uint32_t>(pInputLaneB[aInputIndexD]) << 8U;
        aFoldD |=
            static_cast<std::uint32_t>(pInputLaneC[aInputIndexD]) << 16U;
        aFoldD |=
            static_cast<std::uint32_t>(pInputLaneD[aInputIndexD]) << 24U;
        aFoldD ^= aFoldD >> 16U;
        aFoldD *= 0x85EBCA6BU;
        aFoldD ^= aFoldD >> 13U;
        aFoldD *= 0xC2B2AE35U;
        aFoldD ^= aFoldD >> 16U;
        pOutputLaneD[aIndex] = static_cast<std::uint8_t>(aFoldD);
    }
}
