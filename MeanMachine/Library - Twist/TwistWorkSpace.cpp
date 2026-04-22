//
//  TwistWorkSpace.cpp
//  Gorgon
//
//  Created by Sonic The Hedge Whore on 4/8/26.
//

#include "TwistWorkSpace.hpp"
#include <cstring>

TwistWorkSpace::TwistWorkSpace() {
    mSource = NULL;
    mDest = NULL;
}

void TwistWorkSpace::ShiftKeyBoxA(std::uint8_t *pBox) {
    std::uint8_t* aDest   = pBox + (H_KEY_A - 1) * W_KEY_A;
    std::uint8_t* aSource = aDest - W_KEY_A;
    for (std::uint32_t i = 0; i < (H_KEY_A - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_A);
        aDest   = aSource;
        aSource = aDest - W_KEY_A;
    }
}

void TwistWorkSpace::ShiftKeyBoxB(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = (pBox + W_KEY_B);
    for (std::uint32_t i=0; i < (H_KEY_B - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_B);
        aDest = aSource;
        aSource = aDest + W_KEY_B;
    }
}

void TwistWorkSpace::ShiftMaskBoxA(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = (pBox + W_MASK_A);
    for (std::uint32_t i = 0; i < (H_MASK_A - 1); i++) {
        std::memcpy(aDest, aSource, W_MASK_A);
        aDest = aSource;
        aSource = aDest + W_MASK_A;
    }
}

void TwistWorkSpace::ShiftMaskBoxB(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = (pBox + W_MASK_B);
    for (std::uint32_t i = 0; i < (H_MASK_B - 1); i++) {
        std::memcpy(aDest, aSource, W_MASK_B);
        aDest = aSource;
        aSource = aDest + W_MASK_B;
    }
}

std::uint8_t *TwistWorkSpace::GetBufer(TwistWorkSpace *pWorkspace, TwistWorkSpaceSlot pSlot) {
    return GetBuffer(pWorkspace, pSlot);
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkspace, TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
            
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return &(pWorkspace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return &(pWorkspace->mKeyBoxB[0][0]);
        case TwistWorkSpaceSlot::kKeyRowReadA: return &(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowReadB: return &(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteA: return &(pWorkspace->mKeyBoxA[0][0]);
        case TwistWorkSpaceSlot::kKeyRowWriteB: return &(pWorkspace->mKeyBoxB[0][0]);
        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return &(pWorkspace->mMaskBoxA[0][0]);
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return &(pWorkspace->mMaskBoxB[0][0]);
        case TwistWorkSpaceSlot::kMaskRowReadA: return &(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]);
        case TwistWorkSpaceSlot::kMaskRowReadB: return &(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]);
        case TwistWorkSpaceSlot::kMaskRowWriteA: return &(pWorkspace->mMaskBoxA[0][0]);
        case TwistWorkSpaceSlot::kMaskRowWriteB: return &(pWorkspace->mMaskBoxB[0][0]);
            
            
            
        case TwistWorkSpaceSlot::kSBoxA: return pWorkspace->mSBoxA;
        case TwistWorkSpaceSlot::kSBoxB: return pWorkspace->mSBoxB;
        case TwistWorkSpaceSlot::kSBoxC: return pWorkspace->mSBoxC;
        case TwistWorkSpaceSlot::kSBoxD: return pWorkspace->mSBoxD;
            
            
        case TwistWorkSpaceSlot::kSaltA: return pWorkspace->mSaltA;
        case TwistWorkSpaceSlot::kSaltB: return pWorkspace->mSaltB;
        case TwistWorkSpaceSlot::kSaltC: return pWorkspace->mSaltC;
        case TwistWorkSpaceSlot::kSaltD: return pWorkspace->mSaltD;
               
            
        case TwistWorkSpaceSlot::kDest: return pWorkspace->mDest;
        case TwistWorkSpaceSlot::kSource: return pWorkspace->mSource;
        case TwistWorkSpaceSlot::kSeedExpansionLaneA: return pWorkspace->mExpandLaneA;
        case TwistWorkSpaceSlot::kSeedExpansionLaneB: return pWorkspace->mExpandLaneB;
        case TwistWorkSpaceSlot::kSeedExpansionLaneC: return pWorkspace->mExpandLaneC;
        case TwistWorkSpaceSlot::kSeedExpansionLaneD: return pWorkspace->mExpandLaneD;
            
        case TwistWorkSpaceSlot::kWorkLaneA: return pWorkspace->mWorkLaneA;
        case TwistWorkSpaceSlot::kWorkLaneB: return pWorkspace->mWorkLaneB;
        case TwistWorkSpaceSlot::kWorkLaneC: return pWorkspace->mWorkLaneC;
        case TwistWorkSpaceSlot::kWorkLaneD: return pWorkspace->mWorkLaneD;
        case TwistWorkSpaceSlot::kWorkLaneE: return pWorkspace->mWorkLaneE;
        case TwistWorkSpaceSlot::kWorkLaneF: return pWorkspace->mWorkLaneF;
        case TwistWorkSpaceSlot::kWorkLaneG: return pWorkspace->mWorkLaneG;
        case TwistWorkSpaceSlot::kWorkLaneH: return pWorkspace->mWorkLaneH;
        case TwistWorkSpaceSlot::kOperationLaneA: return pWorkspace->mOperationLaneA;
        case TwistWorkSpaceSlot::kOperationLaneB: return pWorkspace->mOperationLaneB;
        case TwistWorkSpaceSlot::kMaskLaneA: return pWorkspace->mMaskLaneA;
        case TwistWorkSpaceSlot::kMaskLaneB: return pWorkspace->mMaskLaneB;
        default: return pWorkspace->mSource;
    }
}

std::uint32_t TwistWorkSpace::GetBuferLength(TwistWorkSpaceSlot pSlot) {
    return GetBufferLength(pSlot);
}

std::uint32_t TwistWorkSpace::GetBufferLength(TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
            
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return S_KEY_A;
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return S_KEY_B;
            
        case TwistWorkSpaceSlot::kKeyRowReadA: return W_KEY_A;
        case TwistWorkSpaceSlot::kKeyRowReadB: return W_KEY_B;
            
        case TwistWorkSpaceSlot::kKeyRowWriteA: return W_KEY_A;
        case TwistWorkSpaceSlot::kKeyRowWriteB: return W_KEY_B;
            
        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return S_MASK_A;
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return S_MASK_B;
                    
        case TwistWorkSpaceSlot::kMaskRowReadA: return W_MASK_A;
        case TwistWorkSpaceSlot::kMaskRowReadB: return W_MASK_B;
                    
        case TwistWorkSpaceSlot::kMaskRowWriteA: return W_MASK_A;
        case TwistWorkSpaceSlot::kMaskRowWriteB: return W_MASK_B;
            
        case TwistWorkSpaceSlot::kSBoxA: return S_SBOX;
        case TwistWorkSpaceSlot::kSBoxB: return S_SBOX;
        case TwistWorkSpaceSlot::kSBoxC: return S_SBOX;
        case TwistWorkSpaceSlot::kSBoxD: return S_SBOX;

        case TwistWorkSpaceSlot::kSaltA: return S_SALT;
        case TwistWorkSpaceSlot::kSaltB: return S_SALT;
        case TwistWorkSpaceSlot::kSaltC: return S_SALT;
        case TwistWorkSpaceSlot::kSaltD: return S_SALT;
            
        default: return S_BLOCK;
    }
}
