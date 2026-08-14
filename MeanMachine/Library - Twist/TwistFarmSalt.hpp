//
//  TwistFarmSalt.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/6/26.
//

#ifndef TwistFarmSalt_hpp
#define TwistFarmSalt_hpp

#include <cstdint>
#include <cstring>
#include "TwistWorkSpace.hpp"

class TwistFarmSalt {
public:
    TwistFarmSalt();
    
    void                    Derive(const std::uint8_t *pSource,
                                   std::uint64_t *pSaltA, std::uint64_t *pSaltB, std::uint64_t *pSaltC, std::uint64_t *pSaltD,
                                   std::uint64_t *pSaltE, std::uint64_t *pSaltF, std::uint64_t *pSaltG, std::uint64_t *pSaltH);
    void                    Derive(const std::uint8_t *pSource, TwistDomainSeedRoundMaterial *pRoundMaterial);
    
};

#endif /* TwistFarmSalt_hpp */
