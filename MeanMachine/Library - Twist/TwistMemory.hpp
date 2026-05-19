//
//  TwistMemory.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/2/26.
//

#ifndef TwistMemory_hpp
#define TwistMemory_hpp

#include "TwistWorkSpace.hpp"
#include <cstring>
#include <vector>

class TwistMemory {
public:
    
    static void                 Zero(std::uint8_t *pSource,
                                     std::uint32_t pLength) {
        std::memset(pSource, 0, pLength);
    }
    
    static void                 Copy(std::uint8_t *pDest,
                                     std::uint8_t *pSource,
                                     std::uint32_t pLength) {
        memcpy(pDest, pSource, pLength);
    }
    
    static void                 GrowA(std::uint64_t *pDest,
                                      const std::uint8_t *pSource,
                                      std::uint32_t pLength) {
        if ((pDest == nullptr) || (pSource == nullptr) || (pLength == 0U)) {
            return;
        }

        auto RotL64 = [](const std::uint64_t pValue, const std::uint32_t pShift) -> std::uint64_t {
            const std::uint32_t aShift = (pShift & 63U);
            if (aShift == 0U) {
                return pValue;
            }
            return (pValue << aShift) | (pValue >> (64U - aShift));
        };

        std::uint64_t aDigestA = 0x9E3779B97F4A7C15ULL;
        std::uint64_t aDigestB = 0xD6E8FEB86659FD93ULL;
        for (std::uint32_t i = 0U; i < pLength; ++i) {
            const std::uint64_t aByte = static_cast<std::uint64_t>(pSource[i]);
            aDigestA ^= (aByte + (static_cast<std::uint64_t>(i) * 0x100000001B3ULL));
            aDigestA = RotL64(aDigestA, 27U);
            aDigestA *= 0x94D049BB133111EBULL;

            aDigestB += ((aByte + 0xA5ULL) * 0x9E3779B185EBCA87ULL);
            aDigestB ^= RotL64(aDigestA, 17U) + (static_cast<std::uint64_t>(i) * 0xA24BAED4963EE407ULL);
            aDigestB = RotL64(aDigestB, 31U);
            aDigestB *= 0xC2B2AE3D27D4EB4FULL;
        }

        std::uint64_t aState = aDigestA ^ RotL64(aDigestB, 23U) ^
                               (static_cast<std::uint64_t>(pLength) * 0x165667B19E3779F9ULL);

        for (std::uint32_t i = 0U; i < S_SALT; ++i) {
            const std::uint32_t aIndexA = (i % pLength);
            const std::uint32_t aIndexB = ((i * 17U + 13U) % pLength);
            const std::uint32_t aIndexC = ((i * 31U + 7U) % pLength);
            const std::uint32_t aIndexD = ((i * 47U + 19U) % pLength);

            const std::uint64_t aByteA = static_cast<std::uint64_t>(pSource[aIndexA]);
            const std::uint64_t aByteB = static_cast<std::uint64_t>(pSource[aIndexB]);
            const std::uint64_t aByteC = static_cast<std::uint64_t>(pSource[aIndexC]);
            const std::uint64_t aByteD = static_cast<std::uint64_t>(pSource[aIndexD]);

            const std::uint64_t aPack = aByteA |
                                         (aByteB << 16U) |
                                         (aByteC << 32U) |
                                         (aByteD << 48U);

            aState ^= aPack + (static_cast<std::uint64_t>(i + 1U) * 0x9E3779B185EBCA87ULL);
            aState = RotL64(aState, static_cast<std::uint32_t>((i & 31U) + 11U));
            aState *= 0xD6E8FEB86659FD93ULL;
            aState ^= (aState >> 29U);

            pDest[i] = aState ^
                       RotL64(aDigestA, (i & 63U)) ^
                       RotL64(aDigestB, ((i * 3U) & 63U)) ^
                       (aPack * 0x94D049BB133111EBULL);
        }
    }

    static void                 GrowA(std::uint64_t *pDest,
                                      const std::uint64_t *pSource,
                                      std::uint32_t pLength) {
        GrowA(pDest,
              reinterpret_cast<const std::uint8_t *>(pSource),
              pLength);
    }

    static void                 GrowB(std::uint64_t *pDest,
                                      const std::uint8_t *pSource,
                                      std::uint32_t pLength) {
        if ((pDest == nullptr) || (pSource == nullptr) || (pLength == 0U)) {
            return;
        }

        auto RotL64 = [](const std::uint64_t pValue, const std::uint32_t pShift) -> std::uint64_t {
            const std::uint32_t aShift = (pShift & 63U);
            if (aShift == 0U) {
                return pValue;
            }
            return (pValue << aShift) | (pValue >> (64U - aShift));
        };

        std::uint64_t aDigestA = 0xA24BAED4963EE407ULL;
        std::uint64_t aDigestB = 0x9E3779B185EBCA87ULL;
        for (std::uint32_t n = 0U; n < pLength; ++n) {
            const std::uint32_t i = pLength - 1U - n;
            const std::uint64_t aByte = static_cast<std::uint64_t>(pSource[i]);
            aDigestA += aByte ^ (static_cast<std::uint64_t>(i + 1U) * 0xD6E8FEB86659FD93ULL);
            aDigestA = RotL64(aDigestA, 19U);
            aDigestA *= 0x9E3779B97F4A7C15ULL;

            aDigestB ^= aDigestA + (aByte * 0x94D049BB133111EBULL);
            aDigestB = RotL64(aDigestB, 37U);
            aDigestB *= 0xC2B2AE3D27D4EB4FULL;
        }

        std::uint64_t aState = aDigestA ^ RotL64(aDigestB, 13U) ^
                               (static_cast<std::uint64_t>(pLength) * 0xBF58476D1CE4E5B9ULL);

        for (std::uint32_t i = 0U; i < S_SALT; ++i) {
            const std::uint32_t aIndexA = ((i * 11U + 5U) % pLength);
            const std::uint32_t aIndexB = (pLength - 1U - (i % pLength));
            const std::uint32_t aIndexC = ((i * 29U + (pLength >> 1U)) % pLength);
            const std::uint32_t aIndexD = ((i * 7U + 3U) % pLength);

            const std::uint64_t aByteA = static_cast<std::uint64_t>(pSource[aIndexA]);
            const std::uint64_t aByteB = static_cast<std::uint64_t>(pSource[aIndexB]);
            const std::uint64_t aByteC = static_cast<std::uint64_t>(pSource[aIndexC]);
            const std::uint64_t aByteD = static_cast<std::uint64_t>(pSource[aIndexD]);

            const std::uint64_t aPack = aByteA |
                                         (aByteB << 8U) |
                                         (aByteC << 24U) |
                                         (aByteD << 40U) |
                                         ((aByteA ^ aByteC) << 56U);

            aState += aPack ^ (static_cast<std::uint64_t>(i + 1U) * 0xA24BAED4963EE407ULL);
            aState = RotL64(aState, static_cast<std::uint32_t>(((i * 9U) & 63U) + 1U));
            aState ^= RotL64(aDigestB, ((i + 17U) & 63U));
            aState *= 0x94D049BB133111EBULL;
            aState ^= (aState >> 33U);

            pDest[i] = aState ^
                       RotL64(aDigestA, ((i * 5U) & 63U)) ^
                       (aPack * 0x9E3779B185EBCA87ULL);
        }
    }

    static void                 GrowB(std::uint64_t *pDest,
                                      const std::uint64_t *pSource,
                                      std::uint32_t pLength) {
        GrowB(pDest,
              reinterpret_cast<const std::uint8_t *>(pSource),
              pLength);
    }

    static void                 Swap(std::uint8_t *pBufferA,
                                     std::uint8_t *pBufferB,
                                     std::uint8_t *pTemp,
                                     std::uint32_t pLength) {
        memcpy(pTemp, pBufferA, pLength);
        memcpy(pBufferA, pBufferB, pLength);
        memcpy(pBufferB, pTemp, pLength);
    }
    
    static void                 ZeroBlock(std::uint8_t *pSource) {
        Zero(pSource, S_BLOCK);
    }
    
    static void                 CopyBlock(std::uint8_t *pDest,
                                          std::uint8_t *pSource) {
        Copy(pDest, pSource, S_BLOCK);
    }
    
    static void                 SwapBlock(std::uint8_t *pBufferA,
                                          std::uint8_t *pBufferB,
                                          std::uint8_t *pTemp) {
        Swap(pBufferA, pBufferB, pTemp, S_BLOCK);
    }
    
    
};

#endif /* TwistMemory_hpp */
