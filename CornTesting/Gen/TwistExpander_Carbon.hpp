#pragma once

#include "TwistExpander.hpp"

class TwistExpander_Carbon : public TwistExpander {
public:
    TwistExpander_Carbon();
    ~TwistExpander_Carbon() override = default;

    void KDF(TwistDomain pDomain,
             std::uint64_t pDomainConstantPublicIngress,
             std::uint64_t pDomainConstantPrivateIngress,
             std::uint64_t pDomainConstantCrossIngress,
             std::uint64_t *pDomainSaltA,
             std::uint64_t *pDomainSaltB,
             std::uint64_t *pDomainSaltC,
             std::uint64_t *pDomainSaltD,
             std::uint64_t *pDomainSaltE,
             std::uint64_t *pDomainSaltF) override;
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
    static const std::uint64_t kDomainConstantPublicIngress;
    static const std::uint64_t kDomainConstantPrivateIngress;
    static const std::uint64_t kDomainConstantCrossIngress;
    static const std::uint64_t kDomainSaltKeyBoxA[S_SALT];
    static const std::uint64_t kDomainSaltKeyBoxB[S_SALT];
    static const std::uint64_t kDomainSaltKeyBoxC[S_SALT];
    static const std::uint64_t kDomainSaltKeyBoxD[S_SALT];
    static const std::uint64_t kDomainSaltKeyBoxE[S_SALT];
    static const std::uint64_t kDomainSaltKeyBoxF[S_SALT];
    static const std::uint64_t kDomainSaltMaskBoxA[S_SALT];
    static const std::uint64_t kDomainSaltMaskBoxB[S_SALT];
    static const std::uint64_t kDomainSaltMaskBoxC[S_SALT];
    static const std::uint64_t kDomainSaltMaskBoxD[S_SALT];
    static const std::uint64_t kDomainSaltMaskBoxE[S_SALT];
    static const std::uint64_t kDomainSaltMaskBoxF[S_SALT];
    static const std::uint64_t kDomainSaltWandererA[S_SALT];
    static const std::uint64_t kDomainSaltWandererB[S_SALT];
    static const std::uint64_t kDomainSaltWandererC[S_SALT];
    static const std::uint64_t kDomainSaltWandererD[S_SALT];
    static const std::uint64_t kDomainSaltWandererE[S_SALT];
    static const std::uint64_t kDomainSaltWandererF[S_SALT];
    static const std::uint64_t kDomainSaltOrbiterA[S_SALT];
    static const std::uint64_t kDomainSaltOrbiterB[S_SALT];
    static const std::uint64_t kDomainSaltOrbiterC[S_SALT];
    static const std::uint64_t kDomainSaltOrbiterD[S_SALT];
    static const std::uint64_t kDomainSaltOrbiterE[S_SALT];
    static const std::uint64_t kDomainSaltOrbiterF[S_SALT];
    static const std::uint64_t kDomainSaltPrismA[S_SALT];
    static const std::uint64_t kDomainSaltPrismB[S_SALT];
    static const std::uint64_t kDomainSaltPrismC[S_SALT];
    static const std::uint64_t kDomainSaltPrismD[S_SALT];
    static const std::uint64_t kDomainSaltPrismE[S_SALT];
    static const std::uint64_t kDomainSaltPrismF[S_SALT];
    static const std::uint64_t kDomainSaltSourceA[S_SALT];
    static const std::uint64_t kDomainSaltSourceB[S_SALT];
    static const std::uint64_t kDomainSaltSourceC[S_SALT];
    static const std::uint64_t kDomainSaltSourceD[S_SALT];
    static const std::uint64_t kDomainSaltSourceE[S_SALT];
    static const std::uint64_t kDomainSaltSourceF[S_SALT];
};
