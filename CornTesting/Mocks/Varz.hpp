//
//  Varz.hpp
//  CornTesting
//
//  Created by Trombone on 4/26/26.
//

#ifndef Varz_hpp
#define Varz_hpp

#include "TwistWorkSpace.hpp"
#include "GSymbol.hpp"

class Varz {
    
public:
    Varz();
    
    GSymbol         mLoopIndex;
    
    GSymbol         mValue;
    GSymbol         mValueMix;
    
    GSymbol         mCarry;
    GSymbol         mCarryMix;
    
    GSymbol         mPermute;
    GSymbol         mMutate;
    GSymbol         mSelect;
    
    
    GSymbol         mSBoxA;
    GSymbol         mSBoxB;
    GSymbol         mSBoxC;
    GSymbol         mSBoxD;
    
    GSymbol         mSaltA;
    GSymbol         mSaltB;
    GSymbol         mSaltC;
    GSymbol         mSaltD;
    
    GSymbol         mWorkerA;
    GSymbol         mWorkerB;
    GSymbol         mWorkerC;
    GSymbol         mWorkerD;
    
    GSymbol         mKeyReadA;
    GSymbol         mKeyReadB;
    GSymbol         mMaskReadA;
    GSymbol         mMaskReadB;
    
    
    GSymbol         mKeyWriteA;
    GSymbol         mKeyWriteB;
    GSymbol         mMaskWriteA;
    GSymbol         mMaskWriteB;
    
    
    
    GSymbol         a;
    GSymbol         b;
    GSymbol         c;
    GSymbol         d;
    GSymbol         e;
    GSymbol         f;
    
    
};

#endif /* Varz_hpp */
