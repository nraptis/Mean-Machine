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
    
    mSaltA = BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA);
    mSaltB = BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB);
    mSaltC = BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC);
    mSaltD = BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD);
    
    mWorkLaneA = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
    mWorkLaneB = BufSymbol(TwistWorkSpaceSlot::kWorkLaneB);
    mWorkLaneC = BufSymbol(TwistWorkSpaceSlot::kWorkLaneC);
    mWorkLaneD = BufSymbol(TwistWorkSpaceSlot::kWorkLaneD);
    
    
    
    mKeyReadA = BufSymbol(TwistWorkSpaceSlot::kKeyRowReadA);
    mKeyReadB = BufSymbol(TwistWorkSpaceSlot::kKeyRowReadB);
    
    mKeyWriteA = BufSymbol(TwistWorkSpaceSlot::kKeyRowWriteA);
    mKeyWriteB = BufSymbol(TwistWorkSpaceSlot::kKeyRowWriteB);
    
}
