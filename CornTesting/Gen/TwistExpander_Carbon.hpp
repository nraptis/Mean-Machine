#pragma once

#include "TwistExpander.hpp"

class TwistExpander_Carbon : public TwistExpander {
public:
    TwistExpander_Carbon();
    ~TwistExpander_Carbon() override = default;

    void Seed(TwistWorkSpace *pWorkspace,
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
};
