//
//  Random.hpp
//  HomeGrownTests
//
//  Created by Lucky Squirrel on 4/3/26.
//

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include "ByteString.hpp"

class Random {
public:
    
    static void                         Seed(uint32_t pSeed);
    
    static uint64_t                     Get();
    static uint64_t                     Get(uint64_t pMax);
    static uint64_t                     Get(uint64_t pMin, uint64_t pMax);
    
    static float                        GetFloat();
    static float                        GetFloat(float pMax);
    
    static float                        GetFloat(float pMin, float pMax);
    
    static bool                         Bool();
    
    static ByteString                   GetByteString(int pLength);
    
};

#endif /* Random_hpp */
