#pragma once

#include "TwistExpander.hpp"

class TwistExpander_Carbon : public TwistExpander {
public:
    TwistExpander_Carbon();
    ~TwistExpander_Carbon() override = default;

    void KDF(std::uint64_t pNonce,
             std::uint8_t *pInput,
             std::uint8_t *pOutput,
             TwistDomainConstants *pConstants,
             TwistDomainSaltSet *pDomainSaltSet,
             TwistDomainSBoxSet *pDomainSBoxSet) override;
    void Seed(TwistWorkSpace *pWorkspace,
              TwistFarmSBox *pFarmSBox,
              TwistFarmSalt *pFarmSalt,
              std::uint64_t pNonce,
              std::uint8_t *pSourceInput,
              std::uint8_t *pPassword,
              unsigned int pPasswordByteLength) override;
    void TwistBlock(TwistWorkSpace *pWorkspace,
                    std::uint64_t pNonce,
                    std::uint8_t *pSourceInput,
                    std::uint8_t *pDestinationOutput) override;

private:
    static const std::uint8_t kSBoxA[S_SBOX];
    static const std::uint8_t kSBoxB[S_SBOX];
    static const std::uint8_t kSBoxC[S_SBOX];
    static const std::uint8_t kSBoxD[S_SBOX];
    static const std::uint8_t kSBoxE[S_SBOX];
    static const std::uint8_t kSBoxF[S_SBOX];
    static const std::uint8_t kSBoxG[S_SBOX];
    static const std::uint8_t kSBoxH[S_SBOX];
};
