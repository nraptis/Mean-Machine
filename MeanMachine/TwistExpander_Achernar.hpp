#pragma once

#include "TwistExpander.hpp"
#include "TwistExpander_Achernar_Arx.hpp"

class TwistExpander_Achernar : public TwistExpander {
public:
    TwistExpander_Achernar();
    ~TwistExpander_Achernar() override = default;

    void KDF_A(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               std::uint8_t *pSnowLaneA,
               std::uint8_t *pSnowLaneB,
               std::uint8_t *pSnowLaneC,
               MUTABLE_PARAMS) override;
    void KDF_B(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               std::uint8_t *pSnowLaneA,
               std::uint8_t *pSnowLaneB,
               std::uint8_t *pSnowLaneC,
               MUTABLE_PARAMS) override;
    void KDF_C(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               std::uint8_t *pSnowLaneA,
               std::uint8_t *pSnowLaneB,
               std::uint8_t *pSnowLaneC,
               MUTABLE_PARAMS) override;
    void KDF_D(TwistWorkSpace *pWorkSpace,
               std::uint64_t pNonce,
               TwistDomainConstants *pConstants,
               TwistDomainSaltSet *pDomainSaltSet,
               std::uint8_t *pSnowLaneA,
               std::uint8_t *pSnowLaneB,
               std::uint8_t *pSnowLaneC,
               MUTABLE_PARAMS) override;
    void Seed(TwistWorkSpace *pWorkSpace,
              TwistFarmSalt *pFarmSalt,
              std::uint64_t pNonce,
              std::uint8_t *pPassword,
              std::size_t pPasswordByteLength,
              std::uint8_t *pSnowLaneA,
              std::uint8_t *pSnowLaneB,
              std::uint8_t *pSnowLaneC,
              std::uint8_t *pSnowLaneD,
              std::uint8_t *pDestination) override;
    void TwistBlock(TwistWorkSpace *pWorkSpace,
                    std::uint8_t *pSource,
                    std::uint8_t *pSnowLaneA,
                    std::uint8_t *pSnowLaneB,
                    std::uint8_t *pSnowLaneC,
                    std::uint8_t *pSnowLaneD,
                    std::uint8_t *pDestination) override;
    void FoldSeed(TwistWorkSpace *pWorkSpace,
                  std::uint8_t *pDestination) override;
    void FoldTwist(TwistWorkSpace *pWorkSpace,
                   std::uint8_t *pDestination) override;
    void GrowKeyA(TwistWorkSpace *pWorkSpace,
                  MUTABLE_PARAMS) override;
    void GrowKeyB(TwistWorkSpace *pWorkSpace,
                  MUTABLE_PARAMS) override;

private:
    void FoldKeyRows(TwistWorkSpace *pWorkSpace);
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
