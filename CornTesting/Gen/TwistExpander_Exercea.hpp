#pragma once

#include "TwistExpander.hpp"
#include "TwistExpander_Exercea_Arx.hpp"

class TwistExpander_Exercea : public TwistExpander {
public:
    TwistExpander_Exercea();
    ~TwistExpander_Exercea() override = default;

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
              unsigned int pPasswordByteLength,
              std::uint8_t *pDestination) override;
    void TwistBlock(TwistWorkSpace *pWorkSpace,
                    std::uint64_t pNonce,
                    std::uint8_t *pSource,
                    std::size_t pBlockIndex,
                    std::size_t pBlockCount,
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
