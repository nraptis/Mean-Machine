//
//  TwistIndexShuffle.cpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#include "TwistIndexShuffle.hpp"
#include "TwistWorkSpace.hpp"

namespace {

void Execute256WithEntropyBytes(std::size_t *pIndexList256,
                                const std::uint8_t *pEntropySource,
                                std::size_t pEntropyBytes) {
    if ((pIndexList256 == nullptr) || (pEntropySource == nullptr) || (pEntropyBytes == 0U)) {
        return;
    }

    std::size_t *aWrite = pIndexList256;
    for (std::size_t aValue = 0; aValue < 256; ++aValue) {
        *aWrite = aValue;
        ++aWrite;
    }
    
    const std::uint8_t *aEntropy = pEntropySource;
    const std::uint8_t * const aEntropyEnd = pEntropySource + pEntropyBytes;

    std::size_t *aBase = pIndexList256;

    for (std::size_t aRemaining = 256; aRemaining > 1; --aRemaining) {
        
        const std::size_t aLimit = 256 - (256 % aRemaining);
        std::uint8_t aSample = 0;

        do {
            if (aEntropy >= aEntropyEnd) {
                return; // Leaves partially shuffled but still valid.
            }

            aSample = *aEntropy;
            ++aEntropy;

        } while (static_cast<std::size_t>(aSample) >= aLimit);

        std::size_t *aSwapA = aBase;
        std::size_t *aSwapB = aBase + (static_cast<std::size_t>(aSample) % aRemaining);

        const std::size_t aHold = *aSwapA;
        *aSwapA = *aSwapB;
        *aSwapB = aHold;

        ++aBase;
    }

}

} // namespace

void TwistIndexShuffle::Execute256(std::size_t *pIndexList256,
                                   const std::uint8_t *pBlockSizedEntropySource) {
    Execute256WithEntropyBytes(pIndexList256,
                               pBlockSizedEntropySource,
                               static_cast<std::size_t>(S_BLOCK));
}

void TwistIndexShuffle::Execute256(std::size_t *pIndexList256,
                                   const std::size_t *pIndexEntropySource) {
    Execute256WithEntropyBytes(pIndexList256,
                               reinterpret_cast<const std::uint8_t *>(pIndexEntropySource),
                               static_cast<std::size_t>(256U * sizeof(std::size_t)));
}
