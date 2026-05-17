//
//  ToonExpander.hpp
//  Valhalla
//
//  Created by Dragon on 5/16/26.
//

#ifndef ToonExpander_hpp
#define ToonExpander_hpp


#include <cstdint>
#include <string>
#include <vector>
#include "ToonFastMatrix.hpp"
#include "ToonWorkSpace.hpp"

class ToonFarmSBox;
class ToonFarmSalt;

class ToonExpander {
public:
    
    ToonExpander();
    
    virtual ~ToonExpander();

    static void                             UnrollPasswordToSource(std::uint8_t *pSource,
                                                                   std::uint8_t *pPassword,
                                                                   const unsigned int pPasswordByteLength);
    static void                             UnrollPasswordToSource(std::uint8_t *pSource,
                                                                   std::uint8_t *pPassword,
                                                                   const unsigned int pPasswordByteLength,
                                                                   const unsigned int pSourceByteLength);
    
    virtual void                            KDF(std::uint8_t *pSource,
                                                std::uint8_t *pDest,
                                                ToonDomainConstants *pConstants,
                                                ToonDomainRoundMaterial *pRoundMaterialOrbiterInit,
                                                ToonDomainRoundMaterial *pRoundMaterialOrbiter,
                                                ToonDomainRoundMaterial *pRoundMaterialUnwind);
    
    virtual void                            Seed(ToonWorkSpace *pWorkspace,
                                                 ToonFarmSBox *pFarmSBox,
                                                 ToonFarmSalt *pFarmSalt,
                                                 std::uint8_t *pSource,
                                                 std::uint8_t *pPassword,
                                                 unsigned int pPasswordByteLength);
    
    virtual void                            ToonBlock(ToonWorkSpace *pWorkspace,
                                                       std::uint8_t *pSource,
                                                       std::uint8_t *pDestination);
    
    // this is not virtual, it calls ToonBlock on every block
    void                                    Toon(ToonWorkSpace *pWorkspace,
                                                  std::uint8_t *pSource,
                                                  std::uint8_t *pDestination,
                                                  unsigned int pDestinationByteLength);
    
    ToonFastMatrix                          mMatrixA;
    ToonFastMatrix                          mMatrixB;

    ToonFarmSBox                            *GetFarmSBox() const;
    ToonFarmSalt                            *GetFarmSalt() const;

    ToonDomainBundle                        mDomainBundleInbuilt;
    ToonDomainBundle                        mDomainBundleEphemeral;
    
protected:
    
    ToonWorkSpace                           *mWorkspace;
    ToonFarmSBox                            *mFarmSBox;
    ToonFarmSalt                            *mFarmSalt;
    std::uint64_t                           mKDFCallCounter;
    std::uint64_t                           mKDFSessionNonce;
    
};

#endif /* ToonExpander_hpp */
