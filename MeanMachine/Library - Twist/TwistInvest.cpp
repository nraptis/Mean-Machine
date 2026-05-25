//
//  TwistInvest.cpp
//  MeanMachine
//
//  Created by nicholas on 5/25/26.
//

#include "TwistInvest.hpp"

void TwistInvest::InvestBlockKeyBoxA(std::uint8_t *pSource,
                                     TwistWorkSpace *pWorkSpace) {
    if ((pSource == nullptr) || (pWorkSpace == nullptr)) {
        return;
    }
    
    std::uint8_t *aKeyBoxUnrolledA = &(pWorkSpace->mKeyBoxA[0][0]);
    
    std::size_t aSourceIndex = 0;
    std::size_t aKeyIndex = 0;
    while (aSourceIndex < S_BLOCK) {
        aKeyBoxUnrolledA[aKeyIndex] += pSource[aSourceIndex];
        aSourceIndex++;
        aKeyIndex++;
        if (aKeyIndex == S_KEY_A) {
            aKeyIndex = 0;
        }
    }
}

void TwistInvest::InvestBlockKeyBoxB(std::uint8_t *pSource,
                                     TwistWorkSpace *pWorkSpace) {
    if ((pSource == nullptr) || (pWorkSpace == nullptr)) {
        return;
    }
    
    std::uint8_t *aKeyBoxUnrolledB = &(pWorkSpace->mKeyBoxB[0][0]);
    
    std::size_t aSourceIndex = 0;
    std::size_t aKeyIndex = 0;
    while (aSourceIndex < S_BLOCK) {
        aKeyBoxUnrolledB[aKeyIndex] += pSource[aSourceIndex];
        aSourceIndex++;
        aKeyIndex++;
        if (aKeyIndex == S_KEY_B) {
            aKeyIndex = 0;
        }
    }
}

void TwistInvest::InvestBlockMaskBoxA(std::uint8_t *pSource,
                                      TwistWorkSpace *pWorkSpace) {
    if ((pSource == nullptr) || (pWorkSpace == nullptr)) {
        return;
    }
    
    std::uint8_t *aMaskBoxUnrolledA = &(pWorkSpace->mMaskBoxA[0][0]);
    
    std::size_t aSourceIndex = 0;
    std::size_t aMaskIndex = 0;
    while (aSourceIndex < S_BLOCK) {
        aMaskBoxUnrolledA[aMaskIndex] += pSource[aSourceIndex];
        aSourceIndex++;
        aMaskIndex++;
        if (aMaskIndex == S_MASK_A) {
            aMaskIndex = 0;
        }
    }
}

void TwistInvest::InvestBlockMaskBoxB(std::uint8_t *pSource,
                                      TwistWorkSpace *pWorkSpace) {
    if ((pSource == nullptr) || (pWorkSpace == nullptr)) {
        return;
    }
    
    std::uint8_t *aMaskBoxUnrolledB = &(pWorkSpace->mMaskBoxB[0][0]);
    
    std::size_t aSourceIndex = 0;
    std::size_t aMaskIndex = 0;
    while (aSourceIndex < S_BLOCK) {
        aMaskBoxUnrolledB[aMaskIndex] += pSource[aSourceIndex];
        aSourceIndex++;
        aMaskIndex++;
        if (aMaskIndex == S_MASK_B) {
            aMaskIndex = 0;
        }
    }
}
