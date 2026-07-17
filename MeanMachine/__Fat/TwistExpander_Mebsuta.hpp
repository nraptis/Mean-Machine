#pragma once

#include "TwistExpander.hpp"
#include "TwistExpander_Mebsuta_Arx.hpp"

class TwistExpander_Mebsuta : public TwistExpander {
public:
    TwistExpander_Mebsuta();
    ~TwistExpander_Mebsuta() override = default;

    void KDF_A(std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               std::uint8_t *pSnow,
               int pIndexKDF) override;
    void KDF_B(std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               int pIndexKDF) override;
    void Seed(TwistWorkSpace *pWorkSpace,
              TwistFarmSalt *pFarmSalt,
              std::uint64_t pNonce,
              std::uint8_t *pPassword,
              std::size_t pPasswordByteLength,
              std::uint8_t *pDestination) override;
    void TwistBlock(TwistWorkSpace *pWorkSpace,
                    std::uint8_t *pSource,
                    std::uint8_t *pDestination) override;
    void SquashInvestToKeyBoxes() override;
    void GrowKeyA(TwistWorkSpace *pWorkSpace) override;
    void GrowKeyB(TwistWorkSpace *pWorkSpace) override;

private:
    static const TwistDomainSaltSet kPhaseASalts;
    static const TwistDomainConstants kPhaseAConstants;
    static const TwistDomainSaltSet kPhaseBSalts;
    static const TwistDomainConstants kPhaseBConstants;
    static const TwistDomainSaltSet kPhaseCSalts;
    static const TwistDomainConstants kPhaseCConstants;
    static const TwistDomainSaltSet kPhaseDSalts;
    static const TwistDomainConstants kPhaseDConstants;
    static const TwistDomainSaltSet kPhaseESalts;
    static const TwistDomainConstants kPhaseEConstants;
    static const TwistDomainSaltSet kPhaseFSalts;
    static const TwistDomainConstants kPhaseFConstants;
    static const TwistDomainSaltSet kPhaseGSalts;
    static const TwistDomainConstants kPhaseGConstants;
    static const TwistDomainSaltSet kPhaseHSalts;
    static const TwistDomainConstants kPhaseHConstants;
};
