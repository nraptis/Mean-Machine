#pragma once

#include "TwistExpander.hpp"

class TwistExpander_Gollum : public TwistExpander {
public:
    TwistExpander_Gollum();
    ~TwistExpander_Gollum() override = default;

    void Seed(TwistWorkSpace *pWorkspace,
              TwistCryptoGenerator *pCryptoGenerator,
              TwistFarmSBox *pFarmSBox,
              TwistFarmSalt *pFarmSalt,
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
    static const std::uint8_t kSBoxE[S_SBOX];
    static const std::uint8_t kSBoxF[S_SBOX];
    static const std::uint8_t kSBoxG[S_SBOX];
    static const std::uint8_t kSBoxH[S_SBOX];
    static const std::uint64_t kSaltA[S_SALT];
    static const std::uint64_t kSaltB[S_SALT];
    static const std::uint64_t kSaltC[S_SALT];
    static const std::uint64_t kSaltD[S_SALT];
    static const std::uint64_t kSaltE[S_SALT];
    static const std::uint64_t kSaltF[S_SALT];
    static const std::uint64_t kSaltG[S_SALT];
    static const std::uint64_t kSaltH[S_SALT];
};
