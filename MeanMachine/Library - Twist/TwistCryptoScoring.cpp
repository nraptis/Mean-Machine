//
//  TwistCryptoScoring.cpp
//  Gorgon
//
//  Created by Sonic The Hedge Whore on 4/10/26.
//

#include "TwistCryptoScoring.hpp"
#include "TwistWorkSpace.hpp"
#include "TwistMix64.hpp"
#include <algorithm>
#include <bit>
#include <cstring>



TwistCryptoScoring::TwistCryptoScoring() {
    
}

TwistCryptoScoring::~TwistCryptoScoring() {
    
}


std::int32_t TwistCryptoScoring::ComputeDDTMax_SBox(const std::uint8_t *pData) {
    std::int32_t aResult = 0;
    for (int aInputDifference = 1; aInputDifference < S_SBOX; ++aInputDifference) {
        std::memset(mHistogram, 0, sizeof(mHistogram));
        for (int aInput = 0; aInput < S_SBOX; ++aInput) {
            const int aPairedInput = aInput ^ aInputDifference;
            const std::uint8_t aOutputDifference = pData[aInput] ^ pData[aPairedInput];
            ++mHistogram[aOutputDifference];
        }
        for (int aOutputDifference = 0; aOutputDifference < S_SBOX; ++aOutputDifference) {
            if (mHistogram[aOutputDifference] > aResult) {
                aResult = mHistogram[aOutputDifference];
            }
        }
    }
    return aResult;
}

std::int32_t TwistCryptoScoring::ComputeWalsh_SBox(const std::uint8_t *pData) {
    std::int32_t aResult = 0;
    for (int aOutputMask = 1; aOutputMask < S_SBOX; ++aOutputMask) {
        for (int aInput = 0; aInput < S_SBOX; ++aInput) {
            const std::uint8_t aValue = pData[aInput];
            const int aParity = std::popcount(static_cast<unsigned int>(aValue & aOutputMask)) & 1;
            mSpectrum[aInput] = (aParity == 0) ? 1 : -1;
        }

        // Step 2: Fast Walsh-Hadamard Transform
        for (int aStep = 1; aStep < S_SBOX; aStep <<= 1) {
            for (int aIndex = 0; aIndex < S_SBOX; aIndex += (aStep << 1)) {
                for (int aOffset = 0; aOffset < aStep; ++aOffset) {
                    const int aLeft = mSpectrum[aIndex + aOffset];
                    const int aRight = mSpectrum[aIndex + aOffset + aStep];
                    mSpectrum[aIndex + aOffset] = aLeft + aRight;
                    mSpectrum[aIndex + aOffset + aStep] = aLeft - aRight;
                }
            }
        }

        // Step 3: Track maximum absolute correlation
        for (int aInputMask = 0; aInputMask < S_SBOX; ++aInputMask) {
            const int aValue = std::abs(mSpectrum[aInputMask]);
            if (aValue > aResult) {
                aResult = aValue;
            }
        }
    }

    return aResult;
}

TwistCryptoMinMaxResponse TwistCryptoScoring::ComputeComponentAlgebraicDegrees_SBox(const std::uint8_t *pData) {
    int aMaxComponentDegree = 0;
    int aMinComponentDegree = 8;
    
    memset(mBlock, 0, sizeof(mBlock));
    for (int aOutBit = 0; aOutBit < 8; ++aOutBit) {
        for (int aX = 0; aX < S_SBOX; ++aX) {
            mBlock[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>((pData[static_cast<std::size_t>(aX)] >> aOutBit) & 1U);
        }
        
        for (int aBit = 0; aBit < 8; ++aBit) {
            for (int aMask = 0; aMask < S_SBOX; ++aMask) {
                if ((aMask & (1 << aBit)) != 0) {
                    mBlock[static_cast<std::size_t>(aMask)] ^=
                    mBlock[static_cast<std::size_t>(aMask ^ (1 << aBit))];
                }
            }
        }
        
        int aDegree = 0;
        for (int aMask = 1; aMask < S_SBOX; ++aMask) {
            if (mBlock[static_cast<std::size_t>(aMask)] != 0U) {
                aDegree = std::max(aDegree, std::popcount(static_cast<unsigned int>(aMask)));
            }
        }
        aMaxComponentDegree = std::max(aMaxComponentDegree, aDegree);
        aMinComponentDegree = std::min(aMinComponentDegree, aDegree);
    }
    
    TwistCryptoMinMaxResponse aResult;
    aResult.mMin = aMinComponentDegree;
    aResult.mMax = aMaxComponentDegree;
    return aResult;
}

TwistCryptoMaxAverageResponse TwistCryptoScoring::ComputeSacBias_SBox(const std::uint8_t *pData) {
    int aSacMaxBias = 0;
    float aSacBiasTotal = 0.0;
    int aSacCount = 0;
    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aOutputBit = 0; aOutputBit < 8; ++aOutputBit) {
            int aChanged = 0;
            for (int aX = 0; aX < S_SBOX; ++aX) {
                const std::uint8_t aDelta =
                static_cast<std::uint8_t>(pData[static_cast<std::size_t>(aX)] ^
                                          pData[static_cast<std::size_t>(aX ^ aDX)]);
                aChanged += (aDelta >> aOutputBit) & 1U;
            }
            const int aBias = std::abs(aChanged - 128);
            aSacBiasTotal += static_cast<float>(aBias);
            if (aBias > aSacMaxBias) {
                aSacMaxBias = aBias;
            }
            ++aSacCount;
        }
    }
    TwistCryptoMaxAverageResponse aResult;
    aResult.mMax = aSacMaxBias;
    aResult.mAverage = 0.0f;
    if (aSacCount != 0) {
        aResult.mAverage = (aSacBiasTotal / static_cast<float>(aSacCount));
    }
    return aResult;
    
}

TwistCryptoMaxAverageResponse TwistCryptoScoring::ComputeBicBias_SBox(const std::uint8_t *pData) {
    
    float aBicBiasTotal = 0.0;
    int aBicCount = 0;
    int aBicMaxBias = 0;
    
    memset(mBlock, 0, sizeof(mBlock));
    
    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aX = 0; aX < S_SBOX; ++aX) {
            mBlock[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>(pData[static_cast<std::size_t>(aX)] ^ pData[static_cast<std::size_t>(aX ^ aDX)]);
        }
        for (int aBitA = 0; aBitA < 8; ++aBitA) {
            for (int aBitB = aBitA + 1; aBitB < 8; ++aBitB) {
                int aXorOnes = 0;
                for (int aX = 0; aX < S_SBOX; ++aX) {
                    const std::uint8_t aDelta = mBlock[static_cast<std::size_t>(aX)];
                    const int aPair = (((aDelta >> aBitA) & 1U) ^ ((aDelta >> aBitB) & 1U));
                    aXorOnes += aPair;
                }
                const int aBias = std::abs(aXorOnes - 128);
                aBicBiasTotal += static_cast<float>(aBias);
                if (aBias > aBicMaxBias) {
                    aBicMaxBias = aBias;
                }
                ++aBicCount;
            }
        }
    }
    
    TwistCryptoMaxAverageResponse aResult;
    aResult.mMax = aBicMaxBias;
    aResult.mAverage = 0.0f;
    if (aBicCount != 0) {
        aResult.mAverage = (aBicBiasTotal / static_cast<float>(aBicCount));
    }
    return aResult;
}

std::int32_t TwistCryptoScoring::ComputeSameFunctionCount_SBox(const std::uint8_t *pDataA,
                                                               const std::uint8_t *pDataB) {
    std::int32_t aSameCount = 0;
    for (int i=0; i<S_SBOX; i++) {
        if (pDataA[i] == pDataB[i]) {
            aSameCount++;
        }
    }
    return aSameCount;
}

std::int32_t TwistCryptoScoring::ComputeDifferentialSimilarityMax_SBox(const std::uint8_t *pDataA,
                                                                      const std::uint8_t *pDataB) {
    std::int32_t aMaximumSameCount = 0;
    for (std::int32_t aInputDifference = 1; aInputDifference < S_SBOX; aInputDifference++) {
        std::int32_t aSameCount = 0;
        for (std::int32_t aInputValue = 0; aInputValue < S_SBOX; aInputValue++) {
            std::uint8_t aOutputDifferenceA = pDataA[aInputValue] ^ pDataA[aInputValue ^ aInputDifference];
            std::uint8_t aOutputDifferenceB = pDataB[aInputValue] ^ pDataB[aInputValue ^ aInputDifference];
            if (aOutputDifferenceA == aOutputDifferenceB) {
                aSameCount += 1;
            }
        }
        if (aSameCount > aMaximumSameCount) { aMaximumSameCount = aSameCount; }
    }
    return aMaximumSameCount;
}

std::int32_t TwistCryptoScoring::ComputeXorDistributionMax_SBox(const std::uint8_t *pDataA,
                                                               const std::uint8_t *pDataB) {
    
    memset(mHistogram, 0, sizeof(mHistogram));
    
    for (std::int32_t aIndex = 0; aIndex < S_SBOX; aIndex++) {
        std::uint8_t aDifference = pDataA[aIndex] ^ pDataB[aIndex];
        mHistogram[aDifference] += 1;
    }
    
    std::int32_t aMaximumBucket = 0;
    
    for (std::int32_t aIndex = 0; aIndex < S_SBOX; aIndex++) {
        if (mHistogram[aIndex] > aMaximumBucket) {
            aMaximumBucket = mHistogram[aIndex];
        }
    }
    
    return aMaximumBucket;
}

std::int32_t TwistCryptoScoring::ComputeSBoxSimilarityScore_SBox(const std::uint8_t *pDataA,
                                                                const std::uint8_t *pDataB) {
    const int aXor = ComputeXorDistributionMax_SBox(pDataA, pDataB);
    const int aDifferential = ComputeDifferentialSimilarityMax_SBox(pDataA, pDataB);
    return (aXor * 256) + aDifferential;
}

std::int32_t TwistCryptoScoring::ComputeSaltHammingDistance_Salt(const std::uint64_t *pDataA,
                                                                 const std::uint64_t *pDataB) {
    
    std::int32_t aDistance = 0;
    for (int aIndex = 0; aIndex < S_SALT; ++aIndex) {
        aDistance += static_cast<std::int32_t>(
            __builtin_popcountll(pDataA[aIndex] ^ pDataB[aIndex])
        );
    }
    return aDistance;
}

bool TwistCryptoScoring::ComputeIsPermutation_SBox(const std::uint8_t *pData) {
    std::memset(mBlock, 0, S_SBOX);
    for (int aIndex = 0; aIndex < S_SBOX; aIndex++) {
        std::uint8_t aValue = pData[aIndex];
        if (mBlock[aValue] != 0) {
            return false;
        }
        mBlock[aValue] = 1;
    }
    return true;
}

int TwistCryptoScoring::ComputeBitBalance_Salt(const std::uint64_t *pData) {
    
    std::memset(mHistogram, 0, sizeof(mHistogram));
    
    for (int i = 0; i < S_SALT; i++) {
        std::uint64_t v = pData[i];
        
        for (int b = 0; b < 64; b++) {
            if (v & (1ULL << b)) {
                mHistogram[b]++;
            }
        }
    }
    
    int aScore = 0;
    const int aIdeal = S_SALT / 2;
    
    for (int b = 0; b < 64; b++) {
        const int aDiff = std::abs(static_cast<int>(mHistogram[b]) - aIdeal);
        aScore += (aIdeal - aDiff);
    }
    
    return aScore;
}

int TwistCryptoScoring::ComputeByteSpread_Salt(const std::uint64_t *pData) {

    std::memset(mHistogram, 0, sizeof(mHistogram));

    int aUnique = 0;
    const std::uint8_t *aBytes = reinterpret_cast<const std::uint8_t *>(pData);

    for (int i = 0; i < S_SALT * static_cast<int>(sizeof(std::uint64_t)); i++) {
        const std::uint8_t v = aBytes[i];
        if (mHistogram[v] == 0) {
            mHistogram[v] = 1;
            aUnique++;
        }
    }

    return aUnique;
}

int TwistCryptoScoring::ComputeAdjacencyPenalty_Salt(const std::uint64_t *pData) {

    int aPenalty = 0;

    for (int i = 1; i < S_SALT; i++) {
        const std::uint64_t aValueA = pData[i];
        const std::uint64_t aValueB = pData[i - 1];
        const int aDistance = static_cast<int>(__builtin_popcountll(aValueA ^ aValueB));

        if (aValueA == aValueB) {
            aPenalty += 64;
        } else if (aDistance < 8) {
            aPenalty += 16;
        } else if (aDistance < 16) {
            aPenalty += 4;
        }
    }

    return aPenalty;
}


int TwistCryptoScoring::ScorePercentileWeighted(int pValue,
                                                int p01,
                                                int p10,
                                                int p20,
                                                int p40,
                                                int p60,
                                                int p80,
                                                int p90,
                                                int p99,
                                                int pWeight,
                                                int *pRedFlagPoints) {
    
    if (pRedFlagPoints == nullptr) {
        return 0;
    }
    
    double aPercent = 0.0;
    
    // Outside p01..p99 is the actual red-flag zone.
    if (pValue < p01) {
        *pRedFlagPoints += 1;
        return 5;
    } else if (pValue > p99) {
        *pRedFlagPoints += 1;
        return 5;
    } else if (pValue < p10) {
        const double t = static_cast<double>(pValue - p01) / static_cast<double>(p10 - p01);
        aPercent = 5.0 + t * 15.0;
        return static_cast<int>(((static_cast<double>(pWeight) * aPercent) / 100.0) + 0.5);
    } else if (pValue < p20) {
        const double t = static_cast<double>(pValue - p10) / static_cast<double>(p20 - p10);
        aPercent = 20.0 + t * 40.0;
        return static_cast<int>(((static_cast<double>(pWeight) * aPercent) / 100.0) + 0.5);
    } else if (pValue < p40) {
        const double t = static_cast<double>(pValue - p20) / static_cast<double>(p40 - p20);
        aPercent = 60.0 + t * 40.0;
        return static_cast<int>(((static_cast<double>(pWeight) * aPercent) / 100.0) + 0.5);
    } else if (pValue <= p60) {
        return pWeight;
    } else if (pValue <= p80) {
        const double t = static_cast<double>(pValue - p60) / static_cast<double>(p80 - p60);
        aPercent = 100.0 - t * 40.0;
        return static_cast<int>(((static_cast<double>(pWeight) * aPercent) / 100.0) + 0.5);
    } else if (pValue <= p90) {
        const double t = static_cast<double>(pValue - p80) / static_cast<double>(p90 - p80);
        aPercent = 60.0 - t * 40.0;
        return static_cast<int>(((static_cast<double>(pWeight) * aPercent) / 100.0) + 0.5);
    } else {
        const double t = static_cast<double>(pValue - p90) / static_cast<double>(p99 - p90);
        aPercent = 20.0 - t * 15.0;
        return static_cast<int>(((static_cast<double>(pWeight) * aPercent) / 100.0) + 0.5);
    }
}

int TwistCryptoScoring::ScoreLowerIsBetterCurve(float pValue,
                                   float pBest,
                                   float pWorst,
                                                int pMaxPoints) {
    float aPercent = (pValue - pBest) / (pWorst - pBest);
    float aKeep = 1.0f - aPercent;
    float aPointsf = static_cast<float>(pMaxPoints) * aKeep * aKeep;
    int aPoints = static_cast<int>(aPointsf + 0.5f);
    if (aPoints > pMaxPoints) { aPoints = pMaxPoints; }
    if (aPoints < 0) { aPoints = 0; }
    return aPoints;
}

void TwistCryptoScoring::ComputeCombinedSaltGrade_Component_BitBalance(int pBitBalance,
                                                                       int *pScore,
                                                                       int *pRedFlagPoints) {
    
    if ((pScore == nullptr) || (pRedFlagPoints == nullptr)) {
        return;
    }
    
    *pScore += ScorePercentileWeighted(pBitBalance,
                                       847,
                                       863,
                                       869,
                                       877,
                                       884,
                                       892,
                                       898,
                                       912,
                                       30,
                                       pRedFlagPoints);
}

void TwistCryptoScoring::ComputeCombinedSaltGrade_Component_ByteSpread(int pByteSpread,
                                                                       int *pScore,
                                                                       int *pRedFlagPoints) {
    
    if ((pScore == nullptr) || (pRedFlagPoints == nullptr)) {
        return;
    }
    
    *pScore += ScorePercentileWeighted(pByteSpread,
                                       150,
                                       156,
                                       158,
                                       161,
                                       163,
                                       166,
                                       168,
                                       174,
                                       35,
                                       pRedFlagPoints);
}

void TwistCryptoScoring::ComputeCombinedSaltGrade_Component_XorDrift(int pXorDrift,
                                                                     int *pScore,
                                                                     int *pRedFlagPoints) {
    
    if ((pScore == nullptr) || (pRedFlagPoints == nullptr)) {
        return;
    }
    
    *pScore += ScorePercentileWeighted(pXorDrift,
                                       972,
                                       996,
                                       1004,
                                       1018,
                                       1030,
                                       1044,
                                       1052,
                                       1076,
                                       30,
                                       pRedFlagPoints);
}

void TwistCryptoScoring::ComputeCombinedSaltGrade_Component_AdjacencyPenalty(int pAdjacencyPenalty,
                                                                             int *pScore,
                                                                             int *pRedFlagPoints) {
    
    if ((pScore == nullptr) || (pRedFlagPoints == nullptr)) {
        *pScore += 5;
        return;
    }
    
    if (pAdjacencyPenalty == 0) {
        return;
    }
    
    if (pAdjacencyPenalty <= 8) {
        *pRedFlagPoints += 1;
    } else {
        *pRedFlagPoints += 2;
    }
}

int TwistCryptoScoring::ComputeCombinedSaltGrade(const std::uint64_t *pData) {
    
    const int aAdjacencyPenalty = ComputeAdjacencyPenalty_Salt(pData);
    const int aBitBalance = ComputeBitBalance_Salt(pData);
    const int aByteSpread = ComputeByteSpread_Salt(pData);
    const int aXorDrift = ComputeXorDrift_Salt(pData);
    
    int aHealthyScore = 0;
    int aRedFlagPoints = 0;
    
    ComputeCombinedSaltGrade_Component_BitBalance(aBitBalance, &aHealthyScore, &aRedFlagPoints);
    ComputeCombinedSaltGrade_Component_ByteSpread(aByteSpread, &aHealthyScore, &aRedFlagPoints);
    ComputeCombinedSaltGrade_Component_XorDrift(aXorDrift, &aHealthyScore, &aRedFlagPoints);
    ComputeCombinedSaltGrade_Component_AdjacencyPenalty(aAdjacencyPenalty, &aHealthyScore, &aRedFlagPoints);
    
    if (aRedFlagPoints > 0) {
        // max aRedFlagPoints is [2 + 1 + 1 + 1] = 5
        return (aHealthyScore / 4) // [0 - 25]
        - aRedFlagPoints * 5;
    } else {
        return aHealthyScore;
    }
}

int TwistCryptoScoring::ComputeXorDrift_Salt(const std::uint64_t *pData) {
    int aScore = 0;
    
    for (int i = 0, j = S_SALT - 1; i < S_SALT; j = i++) {
        aScore += static_cast<int>(__builtin_popcountll(pData[i] ^ pData[j]));
    }
    
    return aScore;
}

std::int32_t TwistCryptoScoring::ComputeMinimumCycleRotL0AfterGate_SBox(const std::uint8_t *pData) {
    std::int32_t aResult = S_SBOX;

    for (int aStart = 0; aStart < S_SBOX; aStart++) {
        std::memset(mCycleBlock, 0xFF, sizeof(mCycleBlock));

        std::uint8_t aValue = static_cast<std::uint8_t>(aStart);
        std::int32_t aStep = 0;

        while (mCycleBlock[aValue] == -1) {
            mCycleBlock[aValue] = aStep;
            aValue = pData[aValue];
            aStep += 1;
        }

        const std::int32_t aCycleLength = aStep - mCycleBlock[aValue];
        if (aCycleLength < aResult) {
            aResult = aCycleLength;
        }
    }

    return aResult;
}

std::int32_t TwistCryptoScoring::ComputeMinimumCycleRotL1AfterGate_SBox(const std::uint8_t *pData) {
    std::int32_t aResult = S_SBOX;

    for (int aStart = 0; aStart < S_SBOX; aStart++) {
        std::memset(mCycleBlock, 0xFF, sizeof(mCycleBlock));

        std::uint8_t aValue = static_cast<std::uint8_t>(aStart);
        std::int32_t aStep = 0;

        while (mCycleBlock[aValue] == -1) {
            mCycleBlock[aValue] = aStep;
            aValue = pData[aValue];
            aValue = static_cast<std::uint8_t>((aValue << 1U) | (aValue >> 7U));
            aStep += 1;
        }

        const std::int32_t aCycleLength = aStep - mCycleBlock[aValue];
        if (aCycleLength < aResult) {
            aResult = aCycleLength;
        }
    }

    return aResult;
}

std::int32_t TwistCryptoScoring::ComputeMinimumCycleRotL3AfterGate_SBox(const std::uint8_t *pData) {
    std::int32_t aResult = S_SBOX;

    for (int aStart = 0; aStart < S_SBOX; aStart++) {
        std::memset(mCycleBlock, 0xFF, sizeof(mCycleBlock));

        std::uint8_t aValue = static_cast<std::uint8_t>(aStart);
        std::int32_t aStep = 0;

        while (mCycleBlock[aValue] == -1) {
            mCycleBlock[aValue] = aStep;
            aValue = pData[aValue];
            aValue = static_cast<std::uint8_t>((aValue << 3U) | (aValue >> 5U));
            aStep += 1;
        }

        const std::int32_t aCycleLength = aStep - mCycleBlock[aValue];
        if (aCycleLength < aResult) {
            aResult = aCycleLength;
        }
    }

    return aResult;
}

std::int32_t TwistCryptoScoring::ComputeMinimumCycleRotL5AfterGate_SBox(const std::uint8_t *pData) {
    std::int32_t aResult = S_SBOX;

    for (int aStart = 0; aStart < S_SBOX; aStart++) {
        std::memset(mCycleBlock, 0xFF, sizeof(mCycleBlock));

        std::uint8_t aValue = static_cast<std::uint8_t>(aStart);
        std::int32_t aStep = 0;

        while (mCycleBlock[aValue] == -1) {
            mCycleBlock[aValue] = aStep;
            aValue = pData[aValue];
            aValue = static_cast<std::uint8_t>((aValue << 5U) | (aValue >> 3U));
            aStep += 1;
        }

        const std::int32_t aCycleLength = aStep - mCycleBlock[aValue];
        if (aCycleLength < aResult) {
            aResult = aCycleLength;
        }
    }

    return aResult;
}

std::int32_t TwistCryptoScoring::ComputeMinimumCycleRotL7AfterGate_SBox(const std::uint8_t *pData) {
    std::int32_t aResult = S_SBOX;

    for (int aStart = 0; aStart < S_SBOX; aStart++) {
        std::memset(mCycleBlock, 0xFF, sizeof(mCycleBlock));

        std::uint8_t aValue = static_cast<std::uint8_t>(aStart);
        std::int32_t aStep = 0;

        while (mCycleBlock[aValue] == -1) {
            mCycleBlock[aValue] = aStep;
            aValue = pData[aValue];
            aValue = static_cast<std::uint8_t>((aValue << 7U) | (aValue >> 1U));
            aStep += 1;
        }

        const std::int32_t aCycleLength = aStep - mCycleBlock[aValue];
        if (aCycleLength < aResult) {
            aResult = aCycleLength;
        }
    }

    return aResult;
}

void TwistCryptoScoring::ComputeCombinedSBoxGrade_Component_SacMax(int pSacMax, int *pScore, int *pRedFlagPoints) {
    if (pSacMax <= 12) {
        *pScore += 10;
    } else {
        *pScore += 5;
    }
}

void TwistCryptoScoring::ComputeCombinedSBoxGrade_Component_SacAverage(float pSacAverage,
                                                                       int *pScore,
                                                                       int *pRedFlagPoints) {
    if (pSacAverage < 8.0f) {
        *pScore += ScoreLowerIsBetterCurve(pSacAverage, 5.50f, 8.00f, 50);
    }
    
    if (pSacAverage > 8.00f) {
        *pRedFlagPoints += 2;
    } else if (pSacAverage > 7.75f) {
        *pRedFlagPoints += 1;
    }
}

void TwistCryptoScoring::ComputeCombinedSBoxGrade_Component_BicAverage(float pBicAverage,
                                                                       int *pScore,
                                                                       int *pRedFlagPoints) {
    if (pBicAverage < 7.5f) {
        *pScore += ScoreLowerIsBetterCurve(pBicAverage, 6.25f, 7.5f, 40);
    }
    if (pBicAverage > 7.50f) {
        *pRedFlagPoints += 2;
    } else if (pBicAverage > 7.25f) {
        *pRedFlagPoints += 1;
    }
}

int TwistCryptoScoring::ComputeCombinedSBoxGrade(const std::uint8_t *pData) {
    TwistCryptoMaxAverageResponse aSacBias = ComputeSacBias_SBox(pData);
    TwistCryptoMaxAverageResponse aBicBias = ComputeBicBias_SBox(pData);
    int aHealthyScore = 0;
    int aRedFlagPoints = 0;
    ComputeCombinedSBoxGrade_Component_SacAverage(aSacBias.mAverage,
                                                  &aHealthyScore,
                                                  &aRedFlagPoints);
    ComputeCombinedSBoxGrade_Component_SacMax(static_cast<int>(aSacBias.mMax),
                                              &aHealthyScore,
                                              &aRedFlagPoints);
    ComputeCombinedSBoxGrade_Component_BicAverage(aBicBias.mAverage,
                                                  &aHealthyScore,
                                                  &aRedFlagPoints);
    if (aRedFlagPoints > 0) {
        // max red flag points is 4
        return (aHealthyScore / 5) - (aRedFlagPoints * 5);
    }
    return aHealthyScore;
}
