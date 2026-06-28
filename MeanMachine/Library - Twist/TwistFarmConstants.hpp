//
//  TwistRipConstants.hpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#ifndef TwistFarmConstants_hpp
#define TwistFarmConstants_hpp

#include <cstdint>
#include "TwistWorkSpace.hpp"

class TwistFarmConstants {
public:
    TwistFarmConstants();
    
    static void                 Derive(const std::uint8_t *pSource, TwistDomainConstants *pConstants);
    
private:
    static std::uint64_t        ReadU64(const std::uint8_t *pSource, int *pIndex);
    static std::uint8_t         ReadU8(const std::uint8_t *pSource, int *pIndex);
};

#endif /* TwistFarmConstants_hpp */
