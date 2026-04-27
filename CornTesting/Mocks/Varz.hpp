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
    GSymbol         mCarry;
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
    
    
};

#endif /* Varz_hpp */
