//
//  TwistFarmSBox.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/5/26.
//

#ifndef TwistFarmSBox_hpp
#define TwistFarmSBox_hpp

#include <cstdint>
#include "TwistCryptoScoring.hpp"
#include "TwistWorkSpace.hpp"

class TwistFarmSBox {
public:
    
    TwistFarmSBox();
    
    void                                Reset();

    // We try to get to pTargetCount passing s-boxes.
    // if we failed, we return false.
    bool                                TillBytes(const std::uint8_t *pSource,
                                                  const std::uint8_t *pSnow,
                                                  std::uint64_t pTargetCount);

    std::uint8_t                        mSBox[1024][256];
    std::uint8_t                        mSBoxBase[256];
    
    std::uint64_t                       mCount;
    
private:
    TwistCryptoScoring                  mAnalyzer;
    std::uint8_t                        mExp[512];
    std::uint8_t                        mLog[256];
    int                                 mExponents[5];
    bool                                mTablesBuilt;
    std::uint8_t                        mMatrix[8];
    
    std::uint8_t                        mObscure[53];
    
    
    
};

#endif /* TwistFarmSBox_hpp */
