//
//  TwistShuffle.hpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#ifndef TwistShuffle_hpp
#define TwistShuffle_hpp

#include <cstddef>
#include <cstdint>

class TwistExpander;
class TwistWorkSpace;

class TwistShuffle {
public:
    template <typename T>
    static void                         MoveClaimedToEnd16(bool *pClaimed,
                                                           T *pArray) {
        if ((pClaimed == nullptr) || (pArray == nullptr)) {
            return;
        }

        std::size_t aFrontIndex = 0U;
        std::size_t aUnclaimedCount = 16U;

        while (aFrontIndex < aUnclaimedCount) {
            while ((aFrontIndex < aUnclaimedCount) && (!pClaimed[aFrontIndex])) {
                aFrontIndex++;
            }
            while ((aFrontIndex < aUnclaimedCount) && (pClaimed[aUnclaimedCount - 1U])) {
                aUnclaimedCount--;
            }

            if (aFrontIndex < aUnclaimedCount) {
                aUnclaimedCount--;

                T aHold = pArray[aFrontIndex];
                pArray[aFrontIndex] = pArray[aUnclaimedCount];
                pArray[aUnclaimedCount] = aHold;

                pClaimed[aFrontIndex] = false;
                pClaimed[aUnclaimedCount] = true;
                aFrontIndex++;
            }
        }
    }

    template <typename T>
    static void                         MoveClaimedToEnd32(bool *pClaimed,
                                                           T *pArray) {
        if ((pClaimed == nullptr) || (pArray == nullptr)) {
            return;
        }

        std::size_t aFrontIndex = 0U;
        std::size_t aUnclaimedCount = 32U;

        while (aFrontIndex < aUnclaimedCount) {
            while ((aFrontIndex < aUnclaimedCount) && (!pClaimed[aFrontIndex])) {
                aFrontIndex++;
            }
            while ((aFrontIndex < aUnclaimedCount) && (pClaimed[aUnclaimedCount - 1U])) {
                aUnclaimedCount--;
            }

            if (aFrontIndex < aUnclaimedCount) {
                aUnclaimedCount--;

                T aHold = pArray[aFrontIndex];
                pArray[aFrontIndex] = pArray[aUnclaimedCount];
                pArray[aUnclaimedCount] = aHold;

                pClaimed[aFrontIndex] = false;
                pClaimed[aUnclaimedCount] = true;
                aFrontIndex++;
            }
        }
    }

    //
    // Each supported size intentionally owns a complete loop body. Keep these
    // separate: their constant bounds let the optimizer specialize each hot
    // path independently.
    //
    template <typename T>
    static void                         ShuffleList2(T *pList,
                                                       const std::uint8_t *pEntropy,
                                                       std::size_t pStartIndex,
                                                       std::size_t pCeiling,
                                                       std::size_t pMaxIterations) {
        if ((pList == nullptr) ||
            (pEntropy == nullptr) ||
            (pStartIndex > pCeiling)) {
            return;
        }

        const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
        const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;

        for (std::size_t aIteration = 0U;
             aIteration < pMaxIterations;
             ++aIteration) {
            T *aDestination = pList;
            std::size_t aRemaining = 2U;
            std::size_t aMask = 1U;

            while (aRemaining > 1U) {
                std::size_t aSwapOffset = 0U;

                for (;;) {
                    if (aEntropyCursor <= aEntropyBegin) {
                        return;
                    }

                    --aEntropyCursor;
                    aSwapOffset =
                        static_cast<std::size_t>(*aEntropyCursor) & aMask;

                    if (aSwapOffset < aRemaining) {
                        break;
                    }
                }

                T *const aSwap = aDestination + aSwapOffset;
                T aHold = *aDestination;
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

    template <typename T>
    static void                         ShuffleList4(T *pList,
                                                       const std::uint8_t *pEntropy,
                                                       std::size_t pStartIndex,
                                                       std::size_t pCeiling,
                                                       std::size_t pMaxIterations) {
        if ((pList == nullptr) ||
            (pEntropy == nullptr) ||
            (pStartIndex > pCeiling)) {
            return;
        }

        const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
        const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;

        for (std::size_t aIteration = 0U;
             aIteration < pMaxIterations;
             ++aIteration) {
            T *aDestination = pList;
            std::size_t aRemaining = 4U;
            std::size_t aMask = 3U;

            while (aRemaining > 1U) {
                std::size_t aSwapOffset = 0U;

                for (;;) {
                    if (aEntropyCursor <= aEntropyBegin) {
                        return;
                    }

                    --aEntropyCursor;
                    aSwapOffset =
                        static_cast<std::size_t>(*aEntropyCursor) & aMask;

                    if (aSwapOffset < aRemaining) {
                        break;
                    }
                }

                T *const aSwap = aDestination + aSwapOffset;
                T aHold = *aDestination;
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

    template <typename T>
    static void                         ShuffleList8(T *pList,
                                                       const std::uint8_t *pEntropy,
                                                       std::size_t pStartIndex,
                                                       std::size_t pCeiling,
                                                       std::size_t pMaxIterations) {
        if ((pList == nullptr) ||
            (pEntropy == nullptr) ||
            (pStartIndex > pCeiling)) {
            return;
        }

        const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
        const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;

        for (std::size_t aIteration = 0U;
             aIteration < pMaxIterations;
             ++aIteration) {
            T *aDestination = pList;
            std::size_t aRemaining = 8U;
            std::size_t aMask = 7U;

            while (aRemaining > 1U) {
                std::size_t aSwapOffset = 0U;

                for (;;) {
                    if (aEntropyCursor <= aEntropyBegin) {
                        return;
                    }

                    --aEntropyCursor;
                    aSwapOffset =
                        static_cast<std::size_t>(*aEntropyCursor) & aMask;

                    if (aSwapOffset < aRemaining) {
                        break;
                    }
                }

                T *const aSwap = aDestination + aSwapOffset;
                T aHold = *aDestination;
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

    template <typename T>
    static void                         ShuffleList16(T *pList,
                                                       const std::uint8_t *pEntropy,
                                                       std::size_t pStartIndex,
                                                       std::size_t pCeiling,
                                                       std::size_t pMaxIterations) {
        if ((pList == nullptr) ||
            (pEntropy == nullptr) ||
            (pStartIndex > pCeiling)) {
            return;
        }

        const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
        const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;

        for (std::size_t aIteration = 0U;
             aIteration < pMaxIterations;
             ++aIteration) {
            T *aDestination = pList;
            std::size_t aRemaining = 16U;
            std::size_t aMask = 15U;

            while (aRemaining > 1U) {
                std::size_t aSwapOffset = 0U;

                for (;;) {
                    if (aEntropyCursor <= aEntropyBegin) {
                        return;
                    }

                    --aEntropyCursor;
                    aSwapOffset =
                        static_cast<std::size_t>(*aEntropyCursor) & aMask;

                    if (aSwapOffset < aRemaining) {
                        break;
                    }
                }

                T *const aSwap = aDestination + aSwapOffset;
                T aHold = *aDestination;
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

    template <typename T>
    static void                         ShuffleList32(T *pList,
                                                       const std::uint8_t *pEntropy,
                                                       std::size_t pStartIndex,
                                                       std::size_t pCeiling,
                                                       std::size_t pMaxIterations) {
        if ((pList == nullptr) ||
            (pEntropy == nullptr) ||
            (pStartIndex > pCeiling)) {
            return;
        }

        const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
        const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;

        for (std::size_t aIteration = 0U;
             aIteration < pMaxIterations;
             ++aIteration) {
            T *aDestination = pList;
            std::size_t aRemaining = 32U;
            std::size_t aMask = 31U;

            while (aRemaining > 1U) {
                std::size_t aSwapOffset = 0U;

                for (;;) {
                    if (aEntropyCursor <= aEntropyBegin) {
                        return;
                    }

                    --aEntropyCursor;
                    aSwapOffset =
                        static_cast<std::size_t>(*aEntropyCursor) & aMask;

                    if (aSwapOffset < aRemaining) {
                        break;
                    }
                }

                T *const aSwap = aDestination + aSwapOffset;
                T aHold = *aDestination;
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

    template <typename T>
    static void                         ShuffleList64(T *pList,
                                                       const std::uint8_t *pEntropy,
                                                       std::size_t pStartIndex,
                                                       std::size_t pCeiling,
                                                       std::size_t pMaxIterations) {
        if ((pList == nullptr) ||
            (pEntropy == nullptr) ||
            (pStartIndex > pCeiling)) {
            return;
        }

        const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
        const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;

        for (std::size_t aIteration = 0U;
             aIteration < pMaxIterations;
             ++aIteration) {
            T *aDestination = pList;
            std::size_t aRemaining = 64U;
            std::size_t aMask = 63U;

            while (aRemaining > 1U) {
                std::size_t aSwapOffset = 0U;

                for (;;) {
                    if (aEntropyCursor <= aEntropyBegin) {
                        return;
                    }

                    --aEntropyCursor;
                    aSwapOffset =
                        static_cast<std::size_t>(*aEntropyCursor) & aMask;

                    if (aSwapOffset < aRemaining) {
                        break;
                    }
                }

                T *const aSwap = aDestination + aSwapOffset;
                T aHold = *aDestination;
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

    template <typename T>
    static void                         ShuffleList128(T *pList,
                                                       const std::uint8_t *pEntropy,
                                                       std::size_t pStartIndex,
                                                       std::size_t pCeiling,
                                                       std::size_t pMaxIterations) {
        if ((pList == nullptr) ||
            (pEntropy == nullptr) ||
            (pStartIndex > pCeiling)) {
            return;
        }

        const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
        const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;

        for (std::size_t aIteration = 0U;
             aIteration < pMaxIterations;
             ++aIteration) {
            T *aDestination = pList;
            std::size_t aRemaining = 128U;
            std::size_t aMask = 127U;

            while (aRemaining > 1U) {
                std::size_t aSwapOffset = 0U;

                for (;;) {
                    if (aEntropyCursor <= aEntropyBegin) {
                        return;
                    }

                    --aEntropyCursor;
                    aSwapOffset =
                        static_cast<std::size_t>(*aEntropyCursor) & aMask;

                    if (aSwapOffset < aRemaining) {
                        break;
                    }
                }

                T *const aSwap = aDestination + aSwapOffset;
                T aHold = *aDestination;
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

    template <typename T>
    static void                         ShuffleList256(T *pList,
                                                       const std::uint8_t *pEntropy,
                                                       std::size_t pStartIndex,
                                                       std::size_t pCeiling,
                                                       std::size_t pMaxIterations) {
        if ((pList == nullptr) ||
            (pEntropy == nullptr) ||
            (pStartIndex > pCeiling)) {
            return;
        }

        const std::uint8_t *const aEntropyBegin = pEntropy + pStartIndex;
        const std::uint8_t *aEntropyCursor = pEntropy + pCeiling;

        for (std::size_t aIteration = 0U;
             aIteration < pMaxIterations;
             ++aIteration) {
            T *aDestination = pList;
            std::size_t aRemaining = 256U;
            std::size_t aMask = 255U;

            while (aRemaining > 1U) {
                std::size_t aSwapOffset = 0U;

                for (;;) {
                    if (aEntropyCursor <= aEntropyBegin) {
                        return;
                    }

                    --aEntropyCursor;
                    aSwapOffset =
                        static_cast<std::size_t>(*aEntropyCursor) & aMask;

                    if (aSwapOffset < aRemaining) {
                        break;
                    }
                }

                T *const aSwap = aDestination + aSwapOffset;
                T aHold = *aDestination;
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
    
};

#endif /* TwistShuffle_hpp */
