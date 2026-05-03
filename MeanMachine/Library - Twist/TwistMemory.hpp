//
//  TwistMemory.hpp
//  MeanMachine
//
//  Created by Dragon on 5/2/26.
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
    
    static void                 Grow(std::uint64_t *pDest,
                                     const std::uint8_t *pSource,
                                     std::uint32_t pLength) {
        if ((pDest == nullptr) || (pSource == nullptr) || (pLength == 0U)) {
            return;
        }

        std::uint64_t aCarry = 0x9E3779B97F4A7C15ULL;
        for (std::uint32_t i = 0U; i < pLength; ++i) {
            const std::uint64_t aByte = static_cast<std::uint64_t>(pSource[i]);
            aCarry = (aCarry << 7U) | (aCarry >> 57U);
            aCarry ^= (aByte + (static_cast<std::uint64_t>(i) * 0x100000001B3ULL));
            aCarry *= 0x9E3779B185EBCA87ULL;
            pDest[i] = aCarry ^ (aByte << ((i & 7U) * 8U));
        }
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
