//
//  FrodoShireA.hpp
//  MeanMachine
//
//  Created by Dragon on 5/4/26.
//

#ifndef FrodoShireA_hpp
#define FrodoShireA_hpp

#include "TwistExpander.hpp"

class FrodoShireA : public TwistExpander {
public:
    FrodoShireA();
    ~FrodoShireA() override = default;

    void Seed(TwistWorkSpace *pWorkspace,
              TwistCryptoGenerator *pCryptoGenerator,
              std::uint8_t *pSource,
              std::uint8_t *pPassword,
              unsigned int pPasswordByteLength) override;
    void TwistBlock(TwistWorkSpace *pWorkspace,
                    std::uint8_t *pSource,
                    std::uint8_t *pDestination) override;

private:
    static const std::uint8_t kSBoxA[S_SBOX];
    static const std::uint8_t kSBoxB[S_SBOX];
    static const std::uint8_t kSBoxC[S_SBOX];
    static const std::uint8_t kSBoxD[S_SBOX];
    static const std::uint8_t kSaltA[S_SALT];
    static const std::uint8_t kSaltB[S_SALT];
    static const std::uint8_t kSaltC[S_SALT];
    static const std::uint8_t kSaltD[S_SALT];
};


#endif /* FrodoShireA_hpp */
