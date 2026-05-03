//
//  TwistWorkSpace.cpp
//  Gorgon
//

#include "TwistWorkSpace.hpp"
#include "TwistExpander.hpp"
#include <cstring>

TwistWorkSpace::TwistWorkSpace() {
    std::memset(this, 0, sizeof(*this));
}

void TwistWorkSpace::ShiftKeyBoxA(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox + (H_KEY_A - 1) * W_KEY_A;
    std::uint8_t *aSource = aDest - W_KEY_A;
    for (int i = 0; i < (H_KEY_A - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_A);
        aDest = aSource;
        aSource = aDest - W_KEY_A;
    }
}

void TwistWorkSpace::ShiftKeyBoxB(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = pBox + W_KEY_B;
    for (int i = 0; i < (H_KEY_B - 1); i++) {
        std::memcpy(aDest, aSource, W_KEY_B);
        aDest = aSource;
        aSource = aDest + W_KEY_B;
    }
}

void TwistWorkSpace::ShiftMaskBoxA(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = pBox + W_MASK_A;
    for (int i = 0; i < (H_MASK_A - 1); i++) {
        std::memcpy(aDest, aSource, W_MASK_A);
        aDest = aSource;
        aSource = aDest + W_MASK_A;
    }
}

void TwistWorkSpace::ShiftMaskBoxB(std::uint8_t *pBox) {
    std::uint8_t *aDest = pBox;
    std::uint8_t *aSource = pBox + W_MASK_B;
    for (int i = 0; i < (H_MASK_B - 1); i++) {
        std::memcpy(aDest, aSource, W_MASK_B);
        aDest = aSource;
        aSource = aDest + W_MASK_B;
    }
}

std::uint8_t *TwistWorkSpace::GetBuffer(TwistWorkSpace *pWorkspace,
                                        TwistExpander *pExpander,
                                        TwistWorkSpaceSlot pSlot) {
    if (pWorkspace == nullptr) {
        return nullptr;
    }
    if (pExpander == nullptr) {
        switch (pSlot) {
            case TwistWorkSpaceSlot::kSource:
            case TwistWorkSpaceSlot::kDest:
            case TwistWorkSpaceSlot::kSaltA:
            case TwistWorkSpaceSlot::kSaltB:
            case TwistWorkSpaceSlot::kSaltC:
            case TwistWorkSpaceSlot::kSaltD:
            case TwistWorkSpaceSlot::kScratchSaltA:
            case TwistWorkSpaceSlot::kScratchSaltB:
            case TwistWorkSpaceSlot::kScratchSaltC:
            case TwistWorkSpaceSlot::kScratchSaltD:
            case TwistWorkSpaceSlot::kSBoxA:
            case TwistWorkSpaceSlot::kSBoxB:
            case TwistWorkSpaceSlot::kSBoxC:
            case TwistWorkSpaceSlot::kSBoxD:
                return nullptr;
            default:
                break;
        }
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return pExpander->mSource;
        case TwistWorkSpaceSlot::kDest: return pExpander->mDest;
        case TwistWorkSpaceSlot::kSaltA: return pExpander->mSaltA;
        case TwistWorkSpaceSlot::kSaltB: return pExpander->mSaltB;
        case TwistWorkSpaceSlot::kSaltC: return pExpander->mSaltC;
        case TwistWorkSpaceSlot::kSaltD: return pExpander->mSaltD;
        case TwistWorkSpaceSlot::kScratchSaltA: return reinterpret_cast<std::uint8_t *>(pExpander->mScratchSaltA);
        case TwistWorkSpaceSlot::kScratchSaltB: return reinterpret_cast<std::uint8_t *>(pExpander->mScratchSaltB);
        case TwistWorkSpaceSlot::kScratchSaltC: return reinterpret_cast<std::uint8_t *>(pExpander->mScratchSaltC);
        case TwistWorkSpaceSlot::kScratchSaltD: return reinterpret_cast<std::uint8_t *>(pExpander->mScratchSaltD);
        case TwistWorkSpaceSlot::kDerivedSaltA: return pWorkspace->mDerivedSaltA;
        case TwistWorkSpaceSlot::kDerivedSaltB: return pWorkspace->mDerivedSaltB;
        case TwistWorkSpaceSlot::kDerivedSaltC: return pWorkspace->mDerivedSaltC;
        case TwistWorkSpaceSlot::kDerivedSaltD: return pWorkspace->mDerivedSaltD;
        case TwistWorkSpaceSlot::kDerivedSaltE: return pWorkspace->mDerivedSaltE;
        case TwistWorkSpaceSlot::kDerivedSaltF: return pWorkspace->mDerivedSaltF;
        case TwistWorkSpaceSlot::kDerivedSaltG: return pWorkspace->mDerivedSaltG;
        case TwistWorkSpaceSlot::kDerivedSaltH: return pWorkspace->mDerivedSaltH;
        case TwistWorkSpaceSlot::kSBoxA: return pExpander->mSBoxA;
        case TwistWorkSpaceSlot::kSBoxB: return pExpander->mSBoxB;
        case TwistWorkSpaceSlot::kSBoxC: return pExpander->mSBoxC;
        case TwistWorkSpaceSlot::kSBoxD: return pExpander->mSBoxD;
        case TwistWorkSpaceSlot::kDerivedSBoxA: return pWorkspace->mDerivedSBoxA;
        case TwistWorkSpaceSlot::kDerivedSBoxB: return pWorkspace->mDerivedSBoxB;
        case TwistWorkSpaceSlot::kDerivedSBoxC: return pWorkspace->mDerivedSBoxC;
        case TwistWorkSpaceSlot::kDerivedSBoxD: return pWorkspace->mDerivedSBoxD;
        case TwistWorkSpaceSlot::kDerivedSBoxE: return pWorkspace->mDerivedSBoxE;
        case TwistWorkSpaceSlot::kDerivedSBoxF: return pWorkspace->mDerivedSBoxF;
        case TwistWorkSpaceSlot::kDerivedSBoxG: return pWorkspace->mDerivedSBoxG;
        case TwistWorkSpaceSlot::kDerivedSBoxH: return pWorkspace->mDerivedSBoxH;
        case TwistWorkSpaceSlot::kSeedExpansionLaneA: return pWorkspace->mExpandLaneA;
        case TwistWorkSpaceSlot::kSeedExpansionLaneB: return pWorkspace->mExpandLaneB;
        case TwistWorkSpaceSlot::kSeedExpansionLaneC: return pWorkspace->mExpandLaneC;
        case TwistWorkSpaceSlot::kSeedExpansionLaneD: return pWorkspace->mExpandLaneD;
        case TwistWorkSpaceSlot::kWorkLaneA: return pWorkspace->mWorkLaneA;
        case TwistWorkSpaceSlot::kWorkLaneB: return pWorkspace->mWorkLaneB;
        case TwistWorkSpaceSlot::kWorkLaneC: return pWorkspace->mWorkLaneC;
        case TwistWorkSpaceSlot::kWorkLaneD: return pWorkspace->mWorkLaneD;
        case TwistWorkSpaceSlot::kOperationLaneA: return pWorkspace->mOperationLaneA;
        case TwistWorkSpaceSlot::kOperationLaneB: return pWorkspace->mOperationLaneB;
        case TwistWorkSpaceSlot::kMaskLaneA: return pWorkspace->mMaskLaneA;
        case TwistWorkSpaceSlot::kMaskLaneB: return pWorkspace->mMaskLaneB;
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
            
        default:
            return pWorkspace->mWorkLaneA;
    }
}

int TwistWorkSpace::GetBufferLength(TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return S_KEY_A;
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return S_KEY_B;
        case TwistWorkSpaceSlot::kKeyRowReadA:
        case TwistWorkSpaceSlot::kKeyRowWriteA: return W_KEY_A;
        case TwistWorkSpaceSlot::kKeyRowReadB:
        case TwistWorkSpaceSlot::kKeyRowWriteB: return W_KEY_B;
        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return S_MASK_A;
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return S_MASK_B;
        case TwistWorkSpaceSlot::kMaskRowReadA:
        case TwistWorkSpaceSlot::kMaskRowWriteA: return W_MASK_A;
        case TwistWorkSpaceSlot::kMaskRowReadB:
        case TwistWorkSpaceSlot::kMaskRowWriteB: return W_MASK_B;

        case TwistWorkSpaceSlot::kSBoxA:
        case TwistWorkSpaceSlot::kSBoxB:
        case TwistWorkSpaceSlot::kSBoxC:
        case TwistWorkSpaceSlot::kSBoxD:
        case TwistWorkSpaceSlot::kDerivedSBoxA:
        case TwistWorkSpaceSlot::kDerivedSBoxB:
        case TwistWorkSpaceSlot::kDerivedSBoxC:
        case TwistWorkSpaceSlot::kDerivedSBoxD:
        case TwistWorkSpaceSlot::kDerivedSBoxE:
        case TwistWorkSpaceSlot::kDerivedSBoxF:
        case TwistWorkSpaceSlot::kDerivedSBoxG:
        case TwistWorkSpaceSlot::kDerivedSBoxH:
            return S_SBOX;

        case TwistWorkSpaceSlot::kSaltA:
        case TwistWorkSpaceSlot::kSaltB:
        case TwistWorkSpaceSlot::kSaltC:
        case TwistWorkSpaceSlot::kSaltD:
        case TwistWorkSpaceSlot::kScratchSaltA:
        case TwistWorkSpaceSlot::kScratchSaltB:
        case TwistWorkSpaceSlot::kScratchSaltC:
        case TwistWorkSpaceSlot::kScratchSaltD:
        case TwistWorkSpaceSlot::kDerivedSaltA:
        case TwistWorkSpaceSlot::kDerivedSaltB:
        case TwistWorkSpaceSlot::kDerivedSaltC:
        case TwistWorkSpaceSlot::kDerivedSaltD:
        case TwistWorkSpaceSlot::kDerivedSaltE:
        case TwistWorkSpaceSlot::kDerivedSaltF:
        case TwistWorkSpaceSlot::kDerivedSaltG:
        case TwistWorkSpaceSlot::kDerivedSaltH:
            return S_SALT;

        default:
            return S_BLOCK;
    }
}

bool TwistWorkSpace::IsSBox(TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSBoxA:
        case TwistWorkSpaceSlot::kSBoxB:
        case TwistWorkSpaceSlot::kSBoxC:
        case TwistWorkSpaceSlot::kSBoxD:
        case TwistWorkSpaceSlot::kDerivedSBoxA:
        case TwistWorkSpaceSlot::kDerivedSBoxB:
        case TwistWorkSpaceSlot::kDerivedSBoxC:
        case TwistWorkSpaceSlot::kDerivedSBoxD:
        case TwistWorkSpaceSlot::kDerivedSBoxE:
        case TwistWorkSpaceSlot::kDerivedSBoxF:
        case TwistWorkSpaceSlot::kDerivedSBoxG:
        case TwistWorkSpaceSlot::kDerivedSBoxH:
            return true;
        default:
            return false;
    }
}

bool TwistWorkSpace::IsSalt(TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSaltA:
        case TwistWorkSpaceSlot::kSaltB:
        case TwistWorkSpaceSlot::kSaltC:
        case TwistWorkSpaceSlot::kSaltD:
        case TwistWorkSpaceSlot::kScratchSaltA:
        case TwistWorkSpaceSlot::kScratchSaltB:
        case TwistWorkSpaceSlot::kScratchSaltC:
        case TwistWorkSpaceSlot::kScratchSaltD:
        case TwistWorkSpaceSlot::kDerivedSaltA:
        case TwistWorkSpaceSlot::kDerivedSaltB:
        case TwistWorkSpaceSlot::kDerivedSaltC:
        case TwistWorkSpaceSlot::kDerivedSaltD:
        case TwistWorkSpaceSlot::kDerivedSaltE:
        case TwistWorkSpaceSlot::kDerivedSaltF:
        case TwistWorkSpaceSlot::kDerivedSaltG:
        case TwistWorkSpaceSlot::kDerivedSaltH:
            return true;
        default:
            return false;
    }
}
