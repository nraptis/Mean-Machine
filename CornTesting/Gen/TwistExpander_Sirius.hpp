#pragma once

#include "TwistExpander.hpp"
#include "TwistExpander_Sirius_Arx.hpp"

class TwistExpander_Sirius : public TwistExpander {
public:
    TwistExpander_Sirius();
    ~TwistExpander_Sirius() override = default;

    void KDF_A(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               MUTABLE_PARAMS) override;
    void KDF_B(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               MUTABLE_PARAMS) override;
    void KDF_C(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               MUTABLE_PARAMS) override;
    void KDF_D(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               MUTABLE_PARAMS) override;
    void Seed(TwistWorkSpace *pWorkSpace,
              TwistFarmSalt *pFarmSalt,
              std::uint64_t pNonce,
              std::uint8_t *pPassword,
              std::size_t pPasswordByteLength,
              std::uint8_t *pDestination) override;
    void TwistBlock(TwistWorkSpace *pWorkSpace,
                    std::uint8_t *pSource,
                    std::uint8_t *pCrossLaneA,
                    std::uint8_t *pCrossLaneB,
                    std::uint8_t *pCrossLaneC,
                    std::uint8_t *pCrossLaneD,
                    std::uint8_t *pDestination) override;
    void GrowKeyA(TwistWorkSpace *pWorkSpace,
                  MUTABLE_PARAMS) override;
    void GrowKeyB(TwistWorkSpace *pWorkSpace,
                  MUTABLE_PARAMS) override;

private:
    void FoldKeyRowA(TwistWorkSpace *pWorkSpace);
    void FoldKeyRowB(TwistWorkSpace *pWorkSpace);
    static const TwistDomainSaltSet kKeyRotateASalts;
    static const TwistDomainConstants kKeyRotateAConstants;
    static const TwistDomainSaltSet kKeyRotateBSalts;
    static const TwistDomainConstants kKeyRotateBConstants;
    static const TwistDomainSaltSet kKeySpawnASalts;
    static const TwistDomainConstants kKeySpawnAConstants;
    static const TwistDomainSaltSet kKeySpawnBSalts;
    static const TwistDomainConstants kKeySpawnBConstants;
    static const TwistDomainSaltSet kSeedSalts;
    static const TwistDomainConstants kSeedConstants;
    static const TwistDomainSaltSet kTwistSalts;
    static const TwistDomainConstants kTwistConstants;
};
