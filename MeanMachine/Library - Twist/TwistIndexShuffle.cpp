//
//  TwistIndexShuffle.cpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#include "TwistIndexShuffle.hpp"
#include "TwistWorkSpace.hpp"

namespace {

void ShuffleBackward(std::size_t *pIndexList256,
                     const std::uint8_t *pEntropyBegin,
                     const std::uint8_t *pEntropyEnd) {
    constexpr std::size_t kIndexCount = 256U;
    constexpr std::size_t kEntropyValueCount = 256U;

    const std::uint8_t *aEntropyCursor = pEntropyEnd;

    for (std::size_t aDestinationIndex = 0U;
         aDestinationIndex < (kIndexCount - 1U);
         ++aDestinationIndex) {
        //
        // Determine how many entries remain, including the destination.
        //
        const std::size_t aRemaining =
            kIndexCount - aDestinationIndex;

        //
        // Reject the uneven tail of the byte range. This keeps the modulo
        // operation below unbiased for every possible remaining count.
        //
        const std::size_t aAcceptedSampleLimit =
            kEntropyValueCount - (kEntropyValueCount % aRemaining);

        std::size_t aAcceptedSample = 0U;
        for (;;) {
            //
            // Entropy is consumed from the end of the supplied range toward
            // the beginning.
            //
            if (aEntropyCursor <= pEntropyBegin) {
                return;
            }
            --aEntropyCursor;

            const std::size_t aSample =
                static_cast<std::size_t>(*aEntropyCursor);
            if (aSample < aAcceptedSampleLimit) {
                aAcceptedSample = aSample;
                break;
            }
        }

        //
        // Select one entry from the unplaced suffix.
        //
        const std::size_t aSwapOffset =
            aAcceptedSample % aRemaining;
        const std::size_t aSwapIndex =
            aDestinationIndex + aSwapOffset;

        //
        // Place the selected entry at the current destination.
        //
        const std::size_t aHold =
            pIndexList256[aDestinationIndex];
        pIndexList256[aDestinationIndex] =
            pIndexList256[aSwapIndex];
        pIndexList256[aSwapIndex] =
            aHold;
    }
}

} // namespace

void TwistIndexShuffle::Execute(std::size_t *pIndexList256,
                                const std::uint8_t *pBlockSizedEntropySource) {
    if ((pIndexList256 == nullptr) || (pBlockSizedEntropySource == nullptr)) {
        return;
    }

    for (std::size_t aValue = 0U; aValue < 256U; ++aValue) {
        pIndexList256[aValue] = aValue;
    }

    ShuffleBackward(pIndexList256,
                    pBlockSizedEntropySource,
                    pBlockSizedEntropySource + static_cast<std::size_t>(S_HALF));
    ShuffleBackward(pIndexList256,
                    pBlockSizedEntropySource,
                    pBlockSizedEntropySource + static_cast<std::size_t>(S_BLOCK));
}
