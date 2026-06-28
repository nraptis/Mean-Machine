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
    
    static void                 ZeroKeyBoxA(std::uint8_t *pSource) {
        Zero(pSource, S_KEY);
    }

    static void                 ZeroKeyBoxB(std::uint8_t *pSource) {
        Zero(pSource, S_KEY);
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
