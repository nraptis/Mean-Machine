//
//  TwistExpander.hpp
//  MeanMachine
//

#ifndef TwistExpander_hpp
#define TwistExpander_hpp

#include "TwistWorkSpace.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include "TwistFastMatrix.hpp"

class TwistExpander {
public:
    
    TwistExpander();
    
    virtual ~TwistExpander();

    static void                             UnrollPasswordToSource(std::uint8_t *pSource,
                                                                   std::uint8_t *pPassword,
                                                                   const unsigned int pPasswordByteLength);
    
    virtual void                            Seed(TwistWorkSpace *pWorkspace,
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
    
    
    std::uint8_t                            mSaltA[S_SALT];
    std::uint8_t                            mSaltB[S_SALT];
    std::uint8_t                            mSaltC[S_SALT];
    std::uint8_t                            mSaltD[S_SALT];
    
    std::uint64_t                           mScratchSaltA[S_SALT];
    std::uint64_t                           mScratchSaltB[S_SALT];
    std::uint64_t                           mScratchSaltC[S_SALT];
    std::uint64_t                           mScratchSaltD[S_SALT];
    
    std::uint8_t                            mSBoxA[S_SBOX];
    std::uint8_t                            mSBoxB[S_SBOX];
    std::uint8_t                            mSBoxC[S_SBOX];
    std::uint8_t                            mSBoxD[S_SBOX];
    
    std::uint8_t                            *mSource;
    std::uint8_t                            *mDest;
    
    TwistFastMatrix                         mMatrixA;
    TwistFastMatrix                         mMatrixB;
    
protected:
    
    TwistWorkSpace                          *mWorkspace;
    
};

#endif /* TwistExpander_hpp */
