//
//  TwistExpander.hpp
//  MeanMachine
//

#ifndef TwistExpander_hpp
#define TwistExpander_hpp

#include "TwistWorkSpace.hpp"
#include "TwistDomains.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include "TwistFastMatrix.hpp"
#include "TwistCryptoGenerator.hpp"

class TwistFarmSBox;
class TwistFarmSalt;

class TwistExpander {
public:
    
    TwistExpander();
    
    virtual ~TwistExpander();

    static void                             UnrollPasswordToSource(std::uint8_t *pSource,
                                                                   std::uint8_t *pPassword,
                                                                   const unsigned int pPasswordByteLength);
    static void                             UnrollPasswordToSource(std::uint8_t *pSource,
                                                                   std::uint8_t *pPassword,
                                                                   const unsigned int pPasswordByteLength,
                                                                   const unsigned int pSourceByteLength);
    
    
    
    virtual void                            KDF(TwistDomain pDomain,
                                                std::uint64_t pDomainConstantPublicIngress,
                                                std::uint64_t pDomainConstantPrivateIngress,
                                                std::uint64_t pDomainConstantCrossIngress,
                                                std::uint64_t *pDomainSaltA,
                                                std::uint64_t *pDomainSaltB,
                                                std::uint64_t *pDomainSaltC,
                                                std::uint64_t *pDomainSaltD,
                                                std::uint64_t *pDomainSaltE,
                                                std::uint64_t *pDomainSaltF);

    virtual void                            KDF(std::uint64_t *pDomainSaltA,
                                                std::uint64_t *pDomainSaltB,
                                                std::uint64_t *pDomainSaltC,
                                                std::uint64_t *pDomainSaltD,
                                                std::uint64_t *pDomainSaltE,
                                                std::uint64_t *pDomainSaltF);
    
    virtual void                            Seed(TwistWorkSpace *pWorkspace,
                                                 TwistCryptoGenerator *pCryptoGenerator,
                                                 TwistFarmSBox *pFarmSBox,
                                                 TwistFarmSalt *pFarmSalt,
                                                 std::uint8_t *pSource,
                                                 std::uint8_t *pPassword,
                                                 unsigned int pPasswordByteLength);
    
    virtual void                            TwistBlock(TwistWorkSpace *pWorkspace,
                                                       std::uint8_t *pSource,
                                                       std::uint8_t *pDestination);
    
    // this is not virtual, it calls TwistBlock on every block
    void                                    Twist(TwistWorkSpace *pWorkspace,
                                                  std::uint8_t *pSource,
                                                  std::uint8_t *pDestination,
                                                  unsigned int pDestinationByteLength);
    
    std::uint64_t                           mSaltA[S_SALT];
    std::uint64_t                           mSaltB[S_SALT];
    std::uint64_t                           mSaltC[S_SALT];
    std::uint64_t                           mSaltD[S_SALT];
    std::uint64_t                           mSaltE[S_SALT];
    std::uint64_t                           mSaltF[S_SALT];
    std::uint64_t                           mSaltG[S_SALT];
    std::uint64_t                           mSaltH[S_SALT];

    std::uint64_t                           mDomainSaltKeyBoxA[S_SALT];
    std::uint64_t                           mDomainSaltKeyBoxB[S_SALT];
    std::uint64_t                           mDomainSaltKeyBoxC[S_SALT];
    std::uint64_t                           mDomainSaltKeyBoxD[S_SALT];
    std::uint64_t                           mDomainSaltKeyBoxE[S_SALT];
    std::uint64_t                           mDomainSaltKeyBoxF[S_SALT];

    std::uint64_t                           mDomainSaltMaskBoxA[S_SALT];
    std::uint64_t                           mDomainSaltMaskBoxB[S_SALT];
    std::uint64_t                           mDomainSaltMaskBoxC[S_SALT];
    std::uint64_t                           mDomainSaltMaskBoxD[S_SALT];
    std::uint64_t                           mDomainSaltMaskBoxE[S_SALT];
    std::uint64_t                           mDomainSaltMaskBoxF[S_SALT];

    std::uint64_t                           mDomainSaltWandererA[S_SALT];
    std::uint64_t                           mDomainSaltWandererB[S_SALT];
    std::uint64_t                           mDomainSaltWandererC[S_SALT];
    std::uint64_t                           mDomainSaltWandererD[S_SALT];
    std::uint64_t                           mDomainSaltWandererE[S_SALT];
    std::uint64_t                           mDomainSaltWandererF[S_SALT];

    std::uint64_t                           mDomainSaltOrbiterA[S_SALT];
    std::uint64_t                           mDomainSaltOrbiterB[S_SALT];
    std::uint64_t                           mDomainSaltOrbiterC[S_SALT];
    std::uint64_t                           mDomainSaltOrbiterD[S_SALT];
    std::uint64_t                           mDomainSaltOrbiterE[S_SALT];
    std::uint64_t                           mDomainSaltOrbiterF[S_SALT];

    std::uint64_t                           mDomainSaltPrismA[S_SALT];
    std::uint64_t                           mDomainSaltPrismB[S_SALT];
    std::uint64_t                           mDomainSaltPrismC[S_SALT];
    std::uint64_t                           mDomainSaltPrismD[S_SALT];
    std::uint64_t                           mDomainSaltPrismE[S_SALT];
    std::uint64_t                           mDomainSaltPrismF[S_SALT];

    std::uint64_t                           mDomainSaltSourceA[S_SALT];
    std::uint64_t                           mDomainSaltSourceB[S_SALT];
    std::uint64_t                           mDomainSaltSourceC[S_SALT];
    std::uint64_t                           mDomainSaltSourceD[S_SALT];
    std::uint64_t                           mDomainSaltSourceE[S_SALT];
    std::uint64_t                           mDomainSaltSourceF[S_SALT];
    
    std::uint8_t                            mSBoxA[S_SBOX];
    std::uint8_t                            mSBoxB[S_SBOX];
    std::uint8_t                            mSBoxC[S_SBOX];
    std::uint8_t                            mSBoxD[S_SBOX];
    std::uint8_t                            mSBoxE[S_SBOX];
    std::uint8_t                            mSBoxF[S_SBOX];
    std::uint8_t                            mSBoxG[S_SBOX];
    std::uint8_t                            mSBoxH[S_SBOX];

    std::uint64_t                           mDomainConstantPublicIngress;
    std::uint64_t                           mDomainConstantPrivateIngress;
    std::uint64_t                           mDomainConstantCrossIngress;
    
    std::uint8_t                            *mSource;
    std::uint8_t                            *mDest;
    
    TwistFastMatrix                         mMatrixA;
    TwistFastMatrix                         mMatrixB;

    TwistFarmSBox                           *GetFarmSBox() const;
    TwistFarmSalt                           *GetFarmSalt() const;
    
protected:
    
    TwistWorkSpace                          *mWorkspace;
    TwistFarmSBox                           *mFarmSBox;
    TwistFarmSalt                           *mFarmSalt;
    std::uint64_t                           mKDFCallCounter;
    std::uint64_t                           mKDFSessionNonce;
    
};

#endif /* TwistExpander_hpp */
