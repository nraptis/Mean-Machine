//
//  GWideDoubleBoxAction.hpp
//  MeanMachine
//
//  Created by Dragon on 4/28/26.
//

#ifndef GWideDoubleBoxAction_hpp
#define GWideDoubleBoxAction_hpp

#include "GSymbol.hpp"

enum class GWideBoxByte : std::uint8_t {
    kLow8 = 0,
    kHigh8 = 1,
    kWhole16 = 2
};

class GWideBoxAction {
    
    GSymbol                     mSBoxA;
    GSymbol                     mOracleIndexA;
    GWideBoxByte                mOracleByteA;
    int                         mOracleOffsetA;
    GWideBoxByte                mDestinationByteA;
    
    
    GSymbol                     mSBoxB;
    GSymbol                     mOracleIndexB;
    GWideBoxByte                mOracleByteB;
    int                         mOracleOffsetB;
    GWideBoxByte                mDestinationByteB;
    
    
    
    //
    /*
    mValue = aSBoxA[(mValue >> 8) & 0xFF] ^ RotL8(mValue, 3)
     (mSBoxB[aLoopIndex % 0xFF] << 8)
     
    */
    
    
};

#endif /* GWideDoubleBoxAction_hpp */
