//
//  TwistShiftBox.cpp
//  MeanMachine
//
//  Created by nicholas on 5/25/26.
//

#include "TwistShiftBox.hpp"

void TwistShiftBox::ShiftKeyBoxA(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) {
        return;
    }
    TwistWorkSpace::ShiftKeyBoxA(&(pWorkSpace->mKeyBoxA[0][0]));
}

void TwistShiftBox::ShiftKeyBoxB(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) {
        return;
    }
    TwistWorkSpace::ShiftKeyBoxB(&(pWorkSpace->mKeyBoxB[0][0]));
}

void TwistShiftBox::ShiftMaskBoxA(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) {
        return;
    }
    TwistWorkSpace::ShiftMaskBoxA(&(pWorkSpace->mMaskBoxA[0][0]));
}

void TwistShiftBox::ShiftMaskBoxB(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) {
        return;
    }
    TwistWorkSpace::ShiftMaskBoxB(&(pWorkSpace->mMaskBoxB[0][0]));
}
