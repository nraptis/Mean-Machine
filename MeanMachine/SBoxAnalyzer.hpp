//
//  CryptoAnalyzer.hpp
//  Gorgon
//
//  Created by Sonic The Hedge Whore on 4/10/26.
//

#ifndef CryptoAnalyzer_hpp
#define CryptoAnalyzer_hpp

#include "ByteString.hpp"
#include <vector>

class SBoxAnalyzer {
public:
    
    SBoxAnalyzer();
    ~SBoxAnalyzer();

    std::int32_t                                ComputeLinearCorrelationMax_256(const std::uint8_t *pData, const int pLength);
    std::int32_t                                ComputeDifferenceDistributionTableMax_256(const std::uint8_t *pData, const int pLength);
    std::int32_t                                ComputeMinimumComponentAlgebraicDegree_256(const std::uint8_t *pData, const int pLength);
    std::int32_t                                ComputeMaximumComponentAlgebraicDegree_256(const std::uint8_t *pData, const int pLength);
    
    std::int32_t                                ComputeSacMaxBias_256(const std::uint8_t *pData, const int pLength);
    double                                      ComputeSacAverageBias_256(const std::uint8_t *pData, const int pLength);

    std::int32_t                                ComputeBicMaxBias_256(const std::uint8_t *pData, const int pLength);
    double                                      ComputeBicAverageBias_256(const std::uint8_t *pData, const int pLength);
    
private:
    
    void                                        EnsureScratch256();
    std::int32_t                                *mScratch256;
    
};

#endif /* CryptoAnalyzer_hpp */
