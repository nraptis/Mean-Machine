//
//  TwistExpander.hpp
//  MeanMachine
//

#ifndef TwistExpander_hpp
#define TwistExpander_hpp

#include "TwistWorkSpace.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include "M88.hpp"

#define MUTABLE_PARAMS \
    std::uint64_t *pPrevious, \
    std::uint64_t *pIngress, \
    std::uint64_t *pCarry, \
    std::uint64_t *pWandererA, \
    std::uint64_t *pWandererB, \
    std::uint64_t *pWandererC, \
    std::uint64_t *pWandererD, \
    std::uint64_t *pWandererE, \
    std::uint64_t *pWandererF, \
    std::uint64_t *pWandererG, \
    std::uint64_t *pWandererH, \
    std::uint64_t *pWandererI, \
    std::uint64_t *pWandererJ, \
    std::uint64_t *pWandererK

#define READ_IN_MUTABLE_PARAMS \
    std::uint64_t aPrevious = *pPrevious; \
    std::uint64_t aIngress = *pIngress; \
    std::uint64_t aCarry = *pCarry; \
    std::uint64_t aWandererA = *pWandererA; \
    std::uint64_t aWandererB = *pWandererB; \
    std::uint64_t aWandererC = *pWandererC; \
    std::uint64_t aWandererD = *pWandererD; \
    std::uint64_t aWandererE = *pWandererE; \
    std::uint64_t aWandererF = *pWandererF; \
    std::uint64_t aWandererG = *pWandererG; \
    std::uint64_t aWandererH = *pWandererH; \
    std::uint64_t aWandererI = *pWandererI; \
    std::uint64_t aWandererJ = *pWandererJ; \
    std::uint64_t aWandererK = *pWandererK

#define WRITE_OUT_MUTABLE_PARAMS \
    *pPrevious = aPrevious; \
    *pIngress = aIngress; \
    *pCarry = aCarry; \
    *pWandererA = aWandererA; \
    *pWandererB = aWandererB; \
    *pWandererC = aWandererC; \
    *pWandererD = aWandererD; \
    *pWandererE = aWandererE; \
    *pWandererF = aWandererF; \
    *pWandererG = aWandererG; \
    *pWandererH = aWandererH; \
    *pWandererI = aWandererI; \
    *pWandererJ = aWandererJ; \
    *pWandererK = aWandererK



class TwistFarmSalt;

class TwistExpander {
public:
    
    TwistExpander();
    
    virtual ~TwistExpander();
    
    static void                             UnrollPasswordToSource(std::uint8_t *pSource,
                                                                   std::uint8_t *pPassword,
                                                                   std::size_t pPasswordByteLength);
    static void                             UnrollPasswordToSource(std::uint8_t *pSource,
                                                                   std::uint8_t *pPassword,
                                                                   std::size_t pPasswordByteLength,
                                                                   std::size_t pSourceByteLength);
    
    virtual void                            KDF(std::uint64_t pNonce,
                                                TwistDomainConstants *pDomainConstants,
                                                TwistDomainSaltSet *pDomainSaltSet);
    
    virtual void                            KDF_A(TwistWorkSpace *pWorkSpace,
                                                  std::uint64_t pNonce,
                                                  TwistDomainConstants *pDomainConstants,
                                                  TwistDomainSaltSet *pDomainSaltSet,
                                                  std::uint8_t *pSnowLaneA,
                                                  std::uint8_t *pSnowLaneB,
                                                  std::uint8_t *pSnowLaneC,
                                                  MUTABLE_PARAMS);
    
    virtual void                            KDF_B(TwistWorkSpace *pWorkSpace,
                                                  std::uint64_t pNonce,
                                                  TwistDomainConstants *pDomainConstants,
                                                  TwistDomainSaltSet *pDomainSaltSet,
                                                  std::uint8_t *pSnowLaneA,
                                                  std::uint8_t *pSnowLaneB,
                                                  std::uint8_t *pSnowLaneC,
                                                  MUTABLE_PARAMS);

    virtual void                            KDF_C(TwistWorkSpace *pWorkSpace,
                                                  std::uint64_t pNonce,
                                                  TwistDomainConstants *pDomainConstants,
                                                  TwistDomainSaltSet *pDomainSaltSet,
                                                  std::uint8_t *pSnowLaneA,
                                                  std::uint8_t *pSnowLaneB,
                                                  std::uint8_t *pSnowLaneC,
                                                  MUTABLE_PARAMS);

    virtual void                            KDF_D(TwistWorkSpace *pWorkSpace,
                                                  std::uint64_t pNonce,
                                                  TwistDomainConstants *pDomainConstants,
                                                  TwistDomainSaltSet *pDomainSaltSet,
                                                  std::uint8_t *pSnowLaneA,
                                                  std::uint8_t *pSnowLaneB,
                                                  std::uint8_t *pSnowLaneC,
                                                  MUTABLE_PARAMS);
    
    virtual void                            Seed(TwistWorkSpace *pWorkSpace,
                                                 TwistFarmSalt *pFarmSalt,
                                                 std::uint64_t pNonce,
                                                 std::uint8_t *pPassword,
                                                 std::size_t pPasswordByteLength,
                                                 std::uint8_t *pSnowLaneA,
                                                 std::uint8_t *pSnowLaneB,
                                                 std::uint8_t *pSnowLaneC,
                                                 std::uint8_t *pSnowLaneD,
                                                 std::uint8_t *pDestination);
    
    virtual void                            TwistBlock(TwistWorkSpace *pWorkSpace,
                                                       std::uint8_t *pSource,
                                                       std::uint8_t *pSnowLaneA,
                                                       std::uint8_t *pSnowLaneB,
                                                       std::uint8_t *pSnowLaneC,
                                                       std::uint8_t *pSnowLaneD,
                                                       std::uint8_t *pDestination);

    virtual void                            FoldSeed(TwistWorkSpace *pWorkSpace,
                                                     std::uint8_t *pDestination);
    virtual void                            FoldTwist(TwistWorkSpace *pWorkSpace,
                                                      std::uint8_t *pDestination);
    
    virtual void                            GrowKeyA(TwistWorkSpace *pWorkSpace,
                                                     MUTABLE_PARAMS);
    virtual void                            GrowKeyB(TwistWorkSpace *pWorkSpace,
                                                     MUTABLE_PARAMS);
    
    
    // this is not virtual, it calls TwistBlock on every block
    void                                    Twist(TwistWorkSpace *pWorkSpace,
                                                  std::uint8_t *pSource,
                                                  std::uint8_t *pSnowLaneA,
                                                  std::uint8_t *pSnowLaneB,
                                                  std::uint8_t *pSnowLaneC,
                                                  std::uint8_t *pSnowLaneD,
                                                  std::uint8_t *pDestination,
                                                  std::size_t pDestinationByteLength);
    
    void                                    AutoSeedThenTwist(TwistWorkSpace *pWorkSpace,
                                                              TwistFarmSalt *pFarmSalt,
                                                              std::uint64_t pNonce,
                                                              std::uint8_t *pPassword,
                                                              std::size_t pPasswordByteLength,
                                                              std::uint8_t *pSnowLaneA,
                                                              std::uint8_t *pSnowLaneB,
                                                              std::uint8_t *pSnowLaneC,
                                                              std::uint8_t *pSnowLaneD,
                                                              std::uint8_t *pDestination,
                                                              std::size_t pDestinationByteLength);
    
    // Assumes the work space is seeded...
    // Assumes pSource has at least S_BLOCK bytes...
    void                                    AutoTwist(TwistWorkSpace *pWorkSpace,
                                                      std::uint8_t *pSource,
                                                      std::uint8_t *pSnowLaneA,
                                                      std::uint8_t *pSnowLaneB,
                                                      std::uint8_t *pSnowLaneC,
                                                      std::uint8_t *pSnowLaneD,
                                                      std::uint8_t *pDestination,
                                                      std::size_t pDestinationByteLength);
    
    std::size_t                             mIndexList256A[256];
    std::size_t                             mIndexList256B[256];
    std::size_t                             mIndexList256C[256];
    std::size_t                             mIndexList256D[256];
    
    M88                                     mMatrix;
    
    TwistDomainBundle                       *GetDomainBundleInbuilt() {
        return &mDomainBundleInbuilt;
    }
    const TwistDomainBundle                 *GetDomainBundleInbuilt() const {
        return &mDomainBundleInbuilt;
    }
    TwistDomainBundle                       *GetDomainBundleEphemeral() {
        return &mDomainBundleEphemeral;
    }
    const TwistDomainBundle                 *GetDomainBundleEphemeral() const {
        return &mDomainBundleEphemeral;
    }
    
    void                                    Zero_PostSeed();
    
    void                                    Zero();
    
protected:
    
    TwistDomainBundle                       mDomainBundleInbuilt;
    TwistDomainBundle                       mDomainBundleEphemeral;
    
};


#endif /* TwistExpander_hpp */
