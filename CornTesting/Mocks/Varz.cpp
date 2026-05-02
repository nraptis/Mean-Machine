//
//  Varz.cpp
//  CornTesting
//
//  Created by Trombone on 4/26/26.
//

#include "Varz.hpp"

Varz::Varz() {
    
    mLoopIndex = VarSymbol("i");
    
    mValue = VarSymbol("aValue");
    mValueMix = VarSymbol("aValueMix");
    
    mCarry = VarSymbol("aCarry");
    mCarryMix = VarSymbol("aCarryMix");
    
    
    mPermute = VarSymbol("aPermute");
    mMutate = VarSymbol("aMutate");
    mSelect = VarSymbol("aSelect");
    
    a = VarSymbol("a");
    b = VarSymbol("b");
    c = VarSymbol("c");
    d = VarSymbol("d");
    e = VarSymbol("e");
    f = VarSymbol("f");
    
    mSBoxA = BufSymbol(TwistWorkSpaceSlot::kSBoxA);
    mSBoxB = BufSymbol(TwistWorkSpaceSlot::kSBoxB);
    mSBoxC = BufSymbol(TwistWorkSpaceSlot::kSBoxC);
    mSBoxD = BufSymbol(TwistWorkSpaceSlot::kSBoxD);
    
    mSaltA = BufSymbol(TwistWorkSpaceSlot::kSaltA);
    mSaltB = BufSymbol(TwistWorkSpaceSlot::kSaltB);
    mSaltC = BufSymbol(TwistWorkSpaceSlot::kSaltC);
    mSaltD = BufSymbol(TwistWorkSpaceSlot::kSaltD);
    
    mWorkerA = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
    mWorkerB = BufSymbol(TwistWorkSpaceSlot::kWorkLaneB);
    mWorkerC = BufSymbol(TwistWorkSpaceSlot::kWorkLaneC);
    mWorkerD = BufSymbol(TwistWorkSpaceSlot::kWorkLaneD);
}

