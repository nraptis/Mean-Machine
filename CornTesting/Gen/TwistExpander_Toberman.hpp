#pragma once

#include "TwistExpander.hpp"

class TwistExpander_Toberman : public TwistExpander {
public:
    TwistExpander_Toberman();
    ~TwistExpander_Toberman() override = default;

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
    static const TwistDomainSaltSet kPhaseASalts;
    static const TwistDomainConstants kPhaseAConstants;
    static const TwistDomainSaltSet kPhaseBSalts;
    static const TwistDomainConstants kPhaseBConstants;
    static const TwistDomainSaltSet kPhaseCSalts;
    static const TwistDomainConstants kPhaseCConstants;
    static const TwistDomainSBoxSet kPhaseASBoxes;
    static const TwistDomainSBoxSet kPhaseBSBoxes;
    static const TwistDomainSBoxSet kPhaseCSBoxes;
};
