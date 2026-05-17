//
//  TwistCryptoGenerator.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 4/28/26.
//

#ifndef TwistCryptoGenerator_hpp
#define TwistCryptoGenerator_hpp

#include <cstdint>
#include "TwistCryptoScoring.hpp"
#include "TwistWorkSpace.hpp"


#define CRYPTO_GENERATOR_ITERATIONS 32
#define CRYPTO_GENERATOR_SALT_HOP 64
#define CRYPTO_GENERATOR_SALT_COUNT (((S_BLOCK - S_SALT) / CRYPTO_GENERATOR_SALT_HOP) + 1)
#define CRYPTO_GENERATOR_SALT_MIN_DISTANCE 8


class TwistCryptoGenerator {
public:
    
    TwistCryptoGenerator();

    TwistCryptoScoring                  mAnalyzer;

};

#endif
