//
//  TwistIndexShuffle.hpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#ifndef TwistIndexShuffle_hpp
#define TwistIndexShuffle_hpp

#include <cstdint>
#include <vector>

class TwistIndexShuffle {
    
public:
    
    static void                         Execute256(std::size_t *pIndexList256,
                                                   const std::uint8_t *pBlockSizedEntropySource);
    static void                         Execute256(std::size_t *pIndexList256,
                                                   const std::size_t *pIndexEntropySource);
    
};

#endif /* TwistIndexShuffle_hpp */
