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
    
    virtual void                            KDF(std::uint8_t *pSource,
                                                std::uint8_t *pDest,
                                                TwistDomainConstants *pDomainConstants,
                                                TwistDomainSaltSet *pDomainSaltSet,
                                                TwistDomainSBoxSet *pDomainSBoxSet);
    
    virtual void                            Seed(TwistWorkSpace *pWorkspace,
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
    
    std::size_t                             mIndexList256A[256];
    std::size_t                             mIndexList256B[256];
    std::size_t                             mIndexList256C[256];
    std::size_t                             mIndexList256D[256];
    
    std::uint8_t                            mSBoxA[S_SBOX];
    std::uint8_t                            mSBoxB[S_SBOX];
    std::uint8_t                            mSBoxC[S_SBOX];
    std::uint8_t                            mSBoxD[S_SBOX];
    std::uint8_t                            mSBoxE[S_SBOX];
    std::uint8_t                            mSBoxF[S_SBOX];
    std::uint8_t                            mSBoxG[S_SBOX];
    std::uint8_t                            mSBoxH[S_SBOX];
    
    TwistDomainConstants                    *mActiveConstants;
    TwistDomainSaltSet                      *mActiveSaltSet;
    TwistDomainSBoxSet                      *mActiveSBoxSet;
    
    std::uint8_t                            *mSource;
    std::uint8_t                            *mDest;
    
    TwistFastMatrix                         mMatrixA;
    TwistFastMatrix                         mMatrixB;

    TwistFarmSBox                           *GetFarmSBox() const;
    TwistFarmSalt                           *GetFarmSalt() const;

    void                                    SyncDomainBundleInbuiltFromLegacy();
    void                                    SyncLegacyFromDomainBundleInbuilt();

    TwistDomainBundle                       mDomainBundleInbuilt;
    TwistDomainBundle                       mDomainBundleEphemeral;
    
protected:
    
    TwistWorkSpace                          *mWorkspace;
    TwistFarmSBox                           *mFarmSBox;
    TwistFarmSalt                           *mFarmSalt;
    std::uint64_t                           mKDFCallCounter;
    std::uint64_t                           mKDFSessionNonce;
    
};

#endif /* TwistExpander_hpp */
