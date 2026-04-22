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

class CryptoAnalyzer {
public:
    
    struct BitInclusionStats {
        std::uint32_t                           mBitsSet;
        std::uint32_t                           mBitsCleared;
        std::uint32_t                           mBitCounts[8];
    };

    struct CharacterDistributionStats {
        std::int32_t                            mDistinctCharacterCount;
        std::int32_t                            mDuplicateCharacterCount;
        std::int32_t                            mExtraCharacterCount;
        std::int32_t                            mMaxCharacterCount;
        std::int32_t                            mCharacterCounts[256];
    };

    struct AvalancheStats {
        bool                                    mHasMatchingLength;
        std::int32_t                            mComparedBytes;
        std::int32_t                            mChangedBytes;
        std::int32_t                            mUnchangedBytes;
        std::int32_t                            mChangedBits;
        std::int32_t                            mUnchangedBits;
        std::int32_t                            mBitFlipCounts[8];
        std::int32_t                            mMinBitFlipCount;
        std::int32_t                            mMaxBitFlipCount;
        std::int32_t                            mTotalBitFlipScore;
        std::int32_t                            mPerBitFlipScore;
        std::int32_t                            mByteCoverageScore;
        std::int32_t                            mScore;
    };
    CryptoAnalyzer();
    ~CryptoAnalyzer();
    
    ByteString                                  LongestCommonSubsequence(const ByteString &pStringA, const ByteString &pStringB);
    ByteString                                  LongestCommonSubstring(const ByteString &pStringA, const ByteString &pStringB);
    
    std::int32_t                                LongestCommonSubsequenceLength(const ByteString &pStringA, const ByteString &pStringB);
    std::int32_t                                LongestCommonSubstringLength(const ByteString &pStringA, const ByteString &pStringB);
    std::int32_t                                LevenshteinDistance(const ByteString &pStringA, const ByteString &pStringB);
    
    std::int32_t                                LongestCommonSubsequenceLength_WithRotation(const ByteString &pStringA, const ByteString &pStringB);
    std::int32_t                                LongestCommonSubstringLength_WithRotation(const ByteString &pStringA, const ByteString &pStringB);
    std::int32_t                                LevenshteinDistance_WithRotation(const ByteString &pStringA, const ByteString &pStringB);
    
    std::int32_t                                ComputeLinearCorrelationMax_256(const ByteString &pString);
    std::int32_t                                ComputeDifferenceDistributionTableMax_256(const ByteString &pString);
    std::int32_t                                ComputeMinimumComponentAlgebraicDegree_256(const ByteString &pString);
    std::int32_t                                ComputeMaximumComponentAlgebraicDegree_256(const ByteString &pString);
    
    
    std::int32_t                                ComputeSacMaxBias_256(const ByteString &pString);
    double                                      ComputeSacAverageBias_256(const ByteString &pString);

    std::int32_t                                ComputeBicMaxBias_256(const ByteString &pString);
    double                                      ComputeBicAverageBias_256(const ByteString &pString);
    
    
    BitInclusionStats                           ComputeBitInclusion(const ByteString &pString);
    CharacterDistributionStats                  ComputeCharacterDistribution(const ByteString &pString);
    AvalancheStats                              ComputeAvalancheStats(const ByteString &pStringA, const ByteString &pStringB);
    std::int32_t                                ComputeAvalancheScore(const ByteString &pStringA, const ByteString &pStringB);
    
private:
    
    // We only ever increase mDynamicWidth and mDynamicHeight
    void                                        EnsureDynamicSize(std::int16_t pWidth, std::int16_t pHeight);
    std::int32_t                                **mDynamic;
    std::int16_t                                mDynamicWidth;
    std::int16_t                                mDynamicHeight;
    
    void                                        EnsureScratch256();
    std::int32_t                                *mScratch256;
    
};

#endif /* CryptoAnalyzer_hpp */
