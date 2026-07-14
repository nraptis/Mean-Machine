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
        aSquash *= 0x85ebca6bU;
        aSquash ^= aSquash >> 13U;
        aSquash *= 0xc2b2ae35U;
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
        aSquash *= 0x21f0aaadU;
        aSquash ^= aSquash >> 15U;
        aSquash *= 0x735a2d97U;
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
        aSquash *= 0x7feb352dU;
        aSquash ^= aSquash >> 15U;
        aSquash *= 0x846ca68bU;
        aSquash ^= aSquash >> 16U;
        pOutputLane[aIndex] = static_cast<std::uint8_t>(aSquash);
    }
}
