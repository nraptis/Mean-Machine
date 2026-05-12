//
//  TwistCryptoScoring.hpp
//  Gorgon
//

#ifndef TwistCryptoScoring_hpp
#define TwistCryptoScoring_hpp

#include <cstdint>

struct TwistCryptoMaxAverageResponse {
    std::uint32_t mMax;
    float         mAverage;
};

struct TwistCryptoMinMaxResponse {
    std::uint32_t mMin;
    std::uint32_t mMax;
};

class TwistCryptoScoring {
public:
    
    static constexpr int kRotations[16] = {
        1, 3, 5, 7,
        11, 13, 19, 21,
        27, 29, 35, 37,
        43, 45, 51, 53
    };
    
    TwistCryptoScoring();
    ~TwistCryptoScoring();
    
    // ---------------------------------------------------------------------
    // S-box scoring
    // ---------------------------------------------------------------------
    
    bool ComputeIsPermutation_SBox(const std::uint8_t *pData);
    
    std::int32_t ComputeDDTMax_SBox(const std::uint8_t *pData);
    std::int32_t ComputeWalsh_SBox(const std::uint8_t *pData);
    
    TwistCryptoMinMaxResponse ComputeComponentAlgebraicDegrees_SBox(const std::uint8_t *pData);
    
    TwistCryptoMaxAverageResponse ComputeSacBias_SBox(const std::uint8_t *pData);
    TwistCryptoMaxAverageResponse ComputeBicBias_SBox(const std::uint8_t *pData);
    
    std::int32_t ComputeMinimumCycleRotL0AfterGate_SBox(const std::uint8_t *pData);
    std::int32_t ComputeMinimumCycleRotL1AfterGate_SBox(const std::uint8_t *pData);
    std::int32_t ComputeMinimumCycleRotL3AfterGate_SBox(const std::uint8_t *pData);
    std::int32_t ComputeMinimumCycleRotL5AfterGate_SBox(const std::uint8_t *pData);
    std::int32_t ComputeMinimumCycleRotL7AfterGate_SBox(const std::uint8_t *pData);
    
    std::int32_t ComputeDifferentialSimilarityMax_SBox(const std::uint8_t *pDataA,
                                                       const std::uint8_t *pDataB);
    
    std::int32_t ComputeXorDistributionMax_SBox(const std::uint8_t *pDataA,
                                                const std::uint8_t *pDataB);
    
    std::int32_t ComputeSBoxSimilarityScore_SBox(const std::uint8_t *pDataA,
                                                 const std::uint8_t *pDataB);
    
    
    // ---------------------------------------------------------------------
    // Salt scoring
    // ---------------------------------------------------------------------
    
    std::int32_t ComputeSaltHammingDistance_Salt(const std::uint64_t *pDataA,
                                                 const std::uint64_t *pDataB);
    
    // Range for S_SALT=32: 0..1024.
    // Typical random values from testing: ~850..910, centered near 881.
    // 0 means every bit column is completely one-sided, such as all 0 or all 1.
    // 1024 means every bit column is perfectly balanced: exactly 16 of 32 words set.
    // That can happen with artificial small cycles, so max is suspicious, not best.
    int ComputeBitBalance_Salt(const std::uint64_t *pData);

    // Range for S_SALT=32: 1..256.
    // Typical random values from testing: ~150..174, centered near 162.
    // All 0 / all 1 gives 1.
    // Small repeating patterns give very low values.
    // Sequential bytes 0..255 gives 256, which is "too perfect" / structured,
    // not healthier than random.
    int ComputeByteSpread_Salt(const std::uint64_t *pData);

    // Range for S_SALT=32: 0..1984.
    // Typical random value is 0.
    // This is mostly a catastrophic local-similarity detector, not a ranking score.
    // 1984 means all 31 adjacent word pairs are identical.
    int ComputeAdjacencyPenalty_Salt(const std::uint64_t *pData);

    // Range for S_SALT=32: 0..2048.
    // Typical random values from testing: ~972..1078, centered near 1024.
    // All 0 / all 1 gives 0.
    // Alternating complement words can give 2048, which is catastrophic structure,
    // not good drift.
    int ComputeXorDrift_Salt(const std::uint64_t *pData);
    
    
    int ScorePercentileWeighted(int pValue,
                                                    int p01,
                                                    int p10,
                                                    int p20,
                                                    int p40,
                                                    int p60,
                                                    int p80,
                                                    int p90,
                                                    int p99,
                                                    int pWeight,
                                                    int *pRedFlagPoints);
        
    void ComputeCombinedSaltGrade_Component_BitBalance(int pBitBalance, int *pScore, int *pRedFlagPoints);
    void ComputeCombinedSaltGrade_Component_ByteSpread(int pByteSpread, int *pScore, int *pRedFlagPoints);
    void ComputeCombinedSaltGrade_Component_AdjacencyPenalty(int pAdjacencyPenalty, int *pScore, int *pRedFlagPoints);
    void ComputeCombinedSaltGrade_Component_XorDrift(int pXorDrift, int *pScore, int *pRedFlagPoints);
    
    int ComputeCombinedSaltGrade(const std::uint64_t *pData); // [0 - 100], [0 - 10 usually means red flag detected]
    
private:
    
    std::uint32_t mHistogram[256];
    std::int32_t  mSpectrum[256];
    std::uint8_t  mBlock[256];
    
    // Needed if the cycle functions keep using int32 visit depths.
    std::int32_t  mCycleBlock[256];
};

#endif
