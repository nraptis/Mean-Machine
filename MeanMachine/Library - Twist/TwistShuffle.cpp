//
//  TwistShuffle.cpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#include "TwistShuffle.hpp"
#include "TwistWorkSpace.hpp"

void TwistShuffle::Execute(
    std::size_t *pIndexList256,
    const std::uint8_t *pBlockSizedEntropySource) {
    std::size_t *aDestination = pIndexList256;
    std::size_t *const aDestinationEnd = pIndexList256 + 256U;
    std::size_t aValue = 0U;

    while (aDestination < aDestinationEnd) {
        *aDestination = aValue;
        ++aDestination;
        ++aValue;
    }

    ShuffleIndexList256(pIndexList256,
                        pBlockSizedEntropySource,
                        0U,
                        S_EIGHTH,
                        1U);
    ShuffleIndexList256(pIndexList256,
                        pBlockSizedEntropySource,
                        S_EIGHTH,
                        2U * S_EIGHTH,
                        1U);
    ShuffleIndexList256(pIndexList256,
                        pBlockSizedEntropySource,
                        2U * S_EIGHTH,
                        3U * S_EIGHTH,
                        1U);
    ShuffleIndexList256(pIndexList256,
                        pBlockSizedEntropySource,
                        3U * S_EIGHTH,
                        4U * S_EIGHTH,
                        1U);
    ShuffleIndexList256(pIndexList256,
                        pBlockSizedEntropySource,
                        4U * S_EIGHTH,
                        5U * S_EIGHTH,
                        1U);
    ShuffleIndexList256(pIndexList256,
                        pBlockSizedEntropySource,
                        5U * S_EIGHTH,
                        6U * S_EIGHTH,
                        1U);
    ShuffleIndexList256(pIndexList256,
                        pBlockSizedEntropySource,
                        6U * S_EIGHTH,
                        7U * S_EIGHTH,
                        1U);
    ShuffleIndexList256(pIndexList256,
                        pBlockSizedEntropySource,
                        7U * S_EIGHTH,
                        S_BLOCK,
                        1U);
}

void TwistShuffle::ShuffleIndexList256(std::size_t *pIndexList, const std::uint8_t *pEntropy,
                                       const std::size_t pStartIndex, const std::size_t pCeiling, const std::size_t pMaxIterations) {
    
    const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
    const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;
    
    for (std::size_t aIteration = 0U; aIteration < pMaxIterations; ++aIteration) {
        
        std::size_t *aDestination = pIndexList;
        std::size_t aRemaining = 256U;
        std::size_t aMask = 255U;

        while (aRemaining > 1U) {
            std::size_t aSwapOffset = 0U;

            for (;;) {
                if (aEntropyCursor <= aEntropyBegin) {
                    return;
                }

                --aEntropyCursor;
                aSwapOffset = static_cast<std::size_t>(*aEntropyCursor) & aMask;

                if (aSwapOffset < aRemaining) {
                    break;
                }
            }

            std::size_t *const aSwap = aDestination + aSwapOffset;
            const std::size_t aHold = *aDestination;
            *aDestination = *aSwap;
            *aSwap = aHold;

            ++aDestination;
            --aRemaining;

            if ((aRemaining & (aRemaining - 1U)) == 0U) {
                aMask = aRemaining - 1U;
            }
        }
    }
}

void TwistShuffle::ShufflePointerList2(void **pPointerList, const std::uint8_t *pEntropy,
                                       const std::size_t pStartIndex, const std::size_t pCeiling, const std::size_t pMaxIterations) {
    
    const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
    const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;
    
    for (std::size_t aIteration = 0U; aIteration < pMaxIterations; ++aIteration) {
        
        void **aDestination = pPointerList;
        std::size_t aRemaining = 2U;
        std::size_t aMask = 1U;

        while (aRemaining > 1U) {
            std::size_t aSwapOffset = 0U;

            for (;;) {
                if (aEntropyCursor <= aEntropyBegin) {
                    return;
                }

                --aEntropyCursor;
                aSwapOffset = static_cast<std::size_t>(*aEntropyCursor) & aMask;

                if (aSwapOffset < aRemaining) {
                    break;
                }
            }

            void **const aSwap = aDestination + aSwapOffset;
            void *const aHold = *aDestination;
            *aDestination = *aSwap;
            *aSwap = aHold;

            ++aDestination;
            --aRemaining;

            if ((aRemaining & (aRemaining - 1U)) == 0U) {
                aMask = aRemaining - 1U;
            }
        }
    }
}

void TwistShuffle::ShufflePointerList4(void **pPointerList, const std::uint8_t *pEntropy,
                                       const std::size_t pStartIndex, const std::size_t pCeiling, const std::size_t pMaxIterations) {
    
    const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
    const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;
    
    for (std::size_t aIteration = 0U; aIteration < pMaxIterations; ++aIteration) {
        
        void **aDestination = pPointerList;
        std::size_t aRemaining = 4U;
        std::size_t aMask = 3U;

        while (aRemaining > 1U) {
            std::size_t aSwapOffset = 0U;

            for (;;) {
                if (aEntropyCursor <= aEntropyBegin) {
                    return;
                }

                --aEntropyCursor;
                aSwapOffset = static_cast<std::size_t>(*aEntropyCursor) & aMask;

                if (aSwapOffset < aRemaining) {
                    break;
                }
            }

            void **const aSwap = aDestination + aSwapOffset;
            void *const aHold = *aDestination;
            *aDestination = *aSwap;
            *aSwap = aHold;

            ++aDestination;
            --aRemaining;

            if ((aRemaining & (aRemaining - 1U)) == 0U) {
                aMask = aRemaining - 1U;
            }
        }
    }
}

void TwistShuffle::ShufflePointerList8(void **pPointerList, const std::uint8_t *pEntropy,
                                       const std::size_t pStartIndex, const std::size_t pCeiling, const std::size_t pMaxIterations) {
    
    const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
    const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;
    
    for (std::size_t aIteration = 0U; aIteration < pMaxIterations; ++aIteration) {
        
        void **aDestination = pPointerList;
        std::size_t aRemaining = 8U;
        std::size_t aMask = 7U;

        while (aRemaining > 1U) {
            std::size_t aSwapOffset = 0U;

            for (;;) {
                if (aEntropyCursor <= aEntropyBegin) {
                    return;
                }

                --aEntropyCursor;
                aSwapOffset = static_cast<std::size_t>(*aEntropyCursor) & aMask;

                if (aSwapOffset < aRemaining) {
                    break;
                }
            }

            void **const aSwap = aDestination + aSwapOffset;
            void *const aHold = *aDestination;
            *aDestination = *aSwap;
            *aSwap = aHold;

            ++aDestination;
            --aRemaining;

            if ((aRemaining & (aRemaining - 1U)) == 0U) {
                aMask = aRemaining - 1U;
            }
        }
    }
}

void TwistShuffle::ShufflePointerList16(void **pPointerList, const std::uint8_t *pEntropy,
                                        const std::size_t pStartIndex, const std::size_t pCeiling, const std::size_t pMaxIterations) {
    
    const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
    const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;
    
    for (std::size_t aIteration = 0U; aIteration < pMaxIterations; ++aIteration) {
        
        void **aDestination = pPointerList;
        std::size_t aRemaining = 16U;
        std::size_t aMask = 15U;

        while (aRemaining > 1U) {
            std::size_t aSwapOffset = 0U;

            for (;;) {
                if (aEntropyCursor <= aEntropyBegin) {
                    return;
                }

                --aEntropyCursor;
                aSwapOffset = static_cast<std::size_t>(*aEntropyCursor) & aMask;

                if (aSwapOffset < aRemaining) {
                    break;
                }
            }

            void **const aSwap = aDestination + aSwapOffset;
            void *const aHold = *aDestination;
            *aDestination = *aSwap;
            *aSwap = aHold;

            ++aDestination;
            --aRemaining;

            if ((aRemaining & (aRemaining - 1U)) == 0U) {
                aMask = aRemaining - 1U;
            }
        }
    }
}

void TwistShuffle::ShufflePointerList32(void **pPointerList, const std::uint8_t *pEntropy,
                                        const std::size_t pStartIndex, const std::size_t pCeiling, const std::size_t pMaxIterations) {
    
    const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
    const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;
    
    for (std::size_t aIteration = 0U; aIteration < pMaxIterations; ++aIteration) {
        
        void **aDestination = pPointerList;
        std::size_t aRemaining = 32U;
        std::size_t aMask = 31U;

        while (aRemaining > 1U) {
            std::size_t aSwapOffset = 0U;

            for (;;) {
                if (aEntropyCursor <= aEntropyBegin) {
                    return;
                }

                --aEntropyCursor;
                aSwapOffset = static_cast<std::size_t>(*aEntropyCursor) & aMask;

                if (aSwapOffset < aRemaining) {
                    break;
                }
            }

            void **const aSwap = aDestination + aSwapOffset;
            void *const aHold = *aDestination;
            *aDestination = *aSwap;
            *aSwap = aHold;

            ++aDestination;
            --aRemaining;

            if ((aRemaining & (aRemaining - 1U)) == 0U) {
                aMask = aRemaining - 1U;
            }
        }
    }
}

void TwistShuffle::ShufflePointerList64(void **pPointerList, const std::uint8_t *pEntropy,
                                        const std::size_t pStartIndex, const std::size_t pCeiling, const std::size_t pMaxIterations) {
    
    const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
    const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;
    
    for (std::size_t aIteration = 0U; aIteration < pMaxIterations; ++aIteration) {
        
        void **aDestination = pPointerList;
        std::size_t aRemaining = 64U;
        std::size_t aMask = 63U;

        while (aRemaining > 1U) {
            std::size_t aSwapOffset = 0U;

            for (;;) {
                if (aEntropyCursor <= aEntropyBegin) {
                    return;
                }

                --aEntropyCursor;
                aSwapOffset = static_cast<std::size_t>(*aEntropyCursor) & aMask;

                if (aSwapOffset < aRemaining) {
                    break;
                }
            }

            void **const aSwap = aDestination + aSwapOffset;
            void *const aHold = *aDestination;
            *aDestination = *aSwap;
            *aSwap = aHold;

            ++aDestination;
            --aRemaining;

            if ((aRemaining & (aRemaining - 1U)) == 0U) {
                aMask = aRemaining - 1U;
            }
        }
    }
}

void TwistShuffle::ShufflePointerList128(void **pPointerList, const std::uint8_t *pEntropy,
                                         const std::size_t pStartIndex, const std::size_t pCeiling, const std::size_t pMaxIterations) {
    
    const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
    const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;
    
    for (std::size_t aIteration = 0U; aIteration < pMaxIterations; ++aIteration) {
        
        void **aDestination = pPointerList;
        std::size_t aRemaining = 128U;
        std::size_t aMask = 127U;

        while (aRemaining > 1U) {
            std::size_t aSwapOffset = 0U;

            for (;;) {
                if (aEntropyCursor <= aEntropyBegin) {
                    return;
                }

                --aEntropyCursor;
                aSwapOffset = static_cast<std::size_t>(*aEntropyCursor) & aMask;

                if (aSwapOffset < aRemaining) {
                    break;
                }
            }

            void **const aSwap = aDestination + aSwapOffset;
            void *const aHold = *aDestination;
            *aDestination = *aSwap;
            *aSwap = aHold;

            ++aDestination;
            --aRemaining;

            if ((aRemaining & (aRemaining - 1U)) == 0U) {
                aMask = aRemaining - 1U;
            }
        }
    }
}
