//
//  TwistInvest.hpp
//  MeanMachine
//
//  Created by nicholas on 5/25/26.
//

#ifndef TwistInvest_hpp
#define TwistInvest_hpp

#include <cstdint>
#include "TwistWorkSpace.hpp"

class TwistInvest {
    
public:
    
    static void             InvestBlockKeyBoxA(std::uint8_t *pSource, TwistWorkSpace *pWorkSpace);
    static void             InvestBlockKeyBoxB(std::uint8_t *pSource, TwistWorkSpace *pWorkSpace);
    
    static void             InvestBlockMaskBoxA(std::uint8_t *pSource, TwistWorkSpace *pWorkSpace);
    static void             InvestBlockMaskBoxB(std::uint8_t *pSource, TwistWorkSpace *pWorkSpace);
    
};

#endif /* TwistInvest_hpp */
