#pragma once

#include "TwistExpander.hpp"

class TwistExpander_Nine_0006 : public TwistExpander {
public:
    TwistExpander_Nine_0006();
    ~TwistExpander_Nine_0006() override = default;

    void KDF(std::uint64_t pNonce,
             TwistDomainConstants *pConstants,
             TwistDomainSaltSet *pDomainSaltSet,
             TwistDomainSBoxSet *pDomainSBoxSet) override;
    void KDF_A(std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               TwistDomainSBoxSet *pDomainSBoxSet) override;
    void KDF_B(std::uint64_t pNonce,
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
