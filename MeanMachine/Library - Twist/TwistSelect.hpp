//
//  TwistSelect.hpp
//  MeanMachine
//
//  Created by Dragon on 4/30/26.
//

#ifndef TwistSelect_hpp
#define TwistSelect_hpp

#include <cstdint>
#include <vector>

struct TwistSelectRange {
public:
    TwistSelectRange();
    
    int                         mLo;
    int                         mHi;
};

struct TwistSelectResult4 {
public:
    TwistSelectResult4();
    
    std::uint8_t                mMask;
    TwistSelectRange            mRangeA;
    TwistSelectRange            mRangeB;
    TwistSelectRange            mRangeC;
};

struct TwistSelectResult2 {
public:
    std::uint8_t                mMask;
    TwistSelectRange            mRangeA;
    TwistSelectResult2();
};

class TwistSelect {
public:
    static std::vector<TwistSelectResult2>          GetAll2();
    static std::vector<TwistSelectResult4>          GetAll4();
};

#endif /* TwistSelect_hpp */
