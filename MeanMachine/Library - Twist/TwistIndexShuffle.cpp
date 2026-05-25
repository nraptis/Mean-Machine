//
//  TwistIndexShuffle.cpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#include "TwistIndexShuffle.hpp"
#include "TwistWorkSpace.hpp"

void TwistIndexShuffle::ExecuteA(std::size_t *pIndexList256,
                                 const std::uint8_t *pBlockSizedEntropySource) {
    if ((pIndexList256 == nullptr) || (pBlockSizedEntropySource == nullptr)) {
        return;
    }
    
    std::size_t *aWrite = pIndexList256;
    for (std::size_t aValue = 0; aValue < 256; ++aValue) {
        *aWrite = aValue;
        ++aWrite;
    }
    
    const std::uint8_t *aEntropy = pBlockSizedEntropySource;
    const std::uint8_t * const aEntropyEnd = pBlockSizedEntropySource + static_cast<std::size_t>(S_BLOCK);
    
    std::size_t *aBase = pIndexList256;
    
    for (std::size_t aRemaining = 256; aRemaining > 1; --aRemaining) {
        
        const std::size_t aLimit = 256 - (256 % aRemaining);
        std::uint8_t aSample = 0;
        
        do {
            if (aEntropy >= aEntropyEnd) {
                return;
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

void TwistIndexShuffle::ExecuteB(std::size_t *pIndexList256,
                                 const std::uint8_t *pBlockSizedEntropySource) {
    if ((pIndexList256 == nullptr) || (pBlockSizedEntropySource == nullptr)) {
        return;
    }
    
    std::size_t *aWrite = pIndexList256;
    for (std::size_t aValue = 0; aValue < 256; ++aValue) {
        *aWrite = aValue;
        ++aWrite;
    }
    
    const std::uint8_t * const aEntropyBegin = pBlockSizedEntropySource;
    const std::uint8_t *aEntropy = pBlockSizedEntropySource + static_cast<std::size_t>(S_BLOCK);
    
    std::size_t *aBase = pIndexList256;
    
    for (std::size_t aRemaining = 256; aRemaining > 1; --aRemaining) {
        
        const std::size_t aLimit = 256 - (256 % aRemaining);
        std::uint8_t aSample = 0;
        
        do {
            if (aEntropy <= aEntropyBegin) {
                return;
            }
            
            --aEntropy;
            aSample = *aEntropy;
            
        } while (static_cast<std::size_t>(aSample) >= aLimit);
        
        std::size_t *aSwapA = aBase;
        std::size_t *aSwapB = aBase + (static_cast<std::size_t>(aSample) % aRemaining);
        
        const std::size_t aHold = *aSwapA;
        *aSwapA = *aSwapB;
        *aSwapB = aHold;
        
        ++aBase;
    }
}
