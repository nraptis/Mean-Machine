//
//  CryptoAnalyzer.hpp
//  Gorgon
//
//  Created by Sonic The Hedge Whore on 4/10/26.
//

#ifndef CryptoAnalyzer_hpp
#define CryptoAnalyzer_hpp

#include <vector>

class TwistCryptoScoring {
public:
    
    TwistCryptoScoring();
    ~TwistCryptoScoring();
    
    std::int32_t                                ComputeLinearCorrelationMax_256(const std::uint8_t *pData, const int pLength);
    std::int32_t                                ComputeDifferenceDistributionTableMax_256(const std::uint8_t *pData, const int pLength);
    std::int32_t                                ComputeMinimumComponentAlgebraicDegree_256(const std::uint8_t *pData, const int pLength);
    std::int32_t                                ComputeMaximumComponentAlgebraicDegree_256(const std::uint8_t *pData, const int pLength);
    
    std::int32_t                                ComputeSacMaxBias_256(const std::uint8_t *pData, const int pLength);
    float                                       ComputeSacAverageBias_256(const std::uint8_t *pData, const int pLength);
    
    std::int32_t                                ComputeBicMaxBias_256(const std::uint8_t *pData, const int pLength);
    float                                       ComputeBicAverageBias_256(const std::uint8_t *pData, const int pLength);
    
    std::int32_t                                ComputeDifferentialSimilarityMax_256(const std::uint8_t *pDataA,
                                                                                     const std::uint8_t *pDataB,
                                                                                     const int pLength);
    
    std::int32_t                                ComputeXorDistributionMax_256(const std::uint8_t *pDataA,
                                                                              const std::uint8_t *pDataB,
                                                                              const int pLength);
    
    bool                                        Equal_256(const std::uint8_t *pDataA,
                                                          const std::uint8_t *pDataB);
    
    bool                                        Equal_128(const std::uint8_t *pDataA,
                                                          const std::uint8_t *pDataB);
    
    
    bool                                        ComputeIsPermutation_256(const std::uint8_t *pData,
                                                                         const int pLength);
    
    
    int                                         ComputeSaltBitBalance_128(const std::uint8_t *pData);
    int                                         ComputeSaltByteSpread_128(const std::uint8_t *pData);
    int                                         ComputeSaltAdjacencyPenalty_128(const std::uint8_t *pData);
    int                                         ComputeSaltXorDrift_128(const std::uint8_t *pData);
    
    
    void                                        PrintBox_256(const char *pName,
                                                             const std::uint8_t *pData);
    
    std::uint64_t                                         ComputeSaltComprehensiveAgainstSBoxFamilt(const std::uint8_t *pSalt,
                                                                                                    std::uint8_t *pSBoxA,
                                                                                                    std::uint8_t *pSBoxB,
                                                                                                    std::uint8_t *pSBoxC,
                                                                                                    std::uint8_t *pSBoxD,
                                                                                                    
                                                                                                    std::uint8_t *pSBoxE,
                                                                                                    std::uint8_t *pSBoxF,
                                                                                                    std::uint8_t *pSBoxG,
                                                                                                    std::uint8_t *pSBoxH);
    
    
};

#endif /* CryptoAnalyzer_hpp */
