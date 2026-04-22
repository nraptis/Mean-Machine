//
//  CryptoAnalyzer.cpp
//  Gorgon
//
//  Created by Sonic The Hedge Whore on 4/10/26.
//

#include "CryptoAnalyzer.hpp"
#include <algorithm>
#include <bit>
#include <cstring>

namespace {

constexpr std::int32_t kAvalancheScorePerfect = 1000000;

std::int32_t ClampAvalancheScore(std::int64_t pScore) {
    if (pScore <= 0) { return 0; }
    if (pScore >= kAvalancheScorePerfect) { return kAvalancheScorePerfect; }
    return static_cast<std::int32_t>(pScore);
}

std::int32_t ScoreTowardsHalf(std::int32_t pObserved, std::int32_t pIdealDenominator) {
    if (pIdealDenominator <= 0) { return 0; }
    const std::int64_t aDeviation = std::llabs(static_cast<std::int64_t>(pObserved) * 2LL -
                                               static_cast<std::int64_t>(pIdealDenominator));
    const std::int64_t aPenalty = (aDeviation * static_cast<std::int64_t>(kAvalancheScorePerfect)) /
    static_cast<std::int64_t>(pIdealDenominator);
    return ClampAvalancheScore(static_cast<std::int64_t>(kAvalancheScorePerfect) - aPenalty);
}



}

CryptoAnalyzer::CryptoAnalyzer() {
    mDynamic = NULL;
    mDynamicWidth = 0;
    mDynamicHeight = 0;
    
    mScratch256 = NULL;
}

CryptoAnalyzer::~CryptoAnalyzer() {
    for (int aIndexY=0; aIndexY<mDynamicHeight; aIndexY++) {
        delete [] mDynamic[aIndexY];
    }
    delete [] mDynamic;
    mDynamic = NULL;
    mDynamicWidth = 0;
    mDynamicHeight = 0;
    
    delete [] mScratch256;
    mScratch256 = NULL;
}

ByteString CryptoAnalyzer::LongestCommonSubsequence(const ByteString &pStringA, const ByteString &pStringB) {
    const int aLengthA = pStringA.mLength;
    const int aLengthB = pStringB.mLength;

    if (aLengthA <= 0 || aLengthB <= 0 || pStringA.mData == nullptr || pStringB.mData == nullptr) {
        return ByteString();
    }

    EnsureDynamicSize(static_cast<std::int16_t>(aLengthB + 1), static_cast<std::int16_t>(aLengthA + 1));

    for (int aIndexY = 0; aIndexY <= aLengthA; aIndexY++) {
        mDynamic[aIndexY][0] = 0;
    }
    for (int aIndexX = 0; aIndexX <= aLengthB; aIndexX++) {
        mDynamic[0][aIndexX] = 0;
    }

    for (int aIndexY = 1; aIndexY <= aLengthA; aIndexY++) {
        for (int aIndexX = 1; aIndexX <= aLengthB; aIndexX++) {
            if (pStringA.mData[aIndexY - 1] == pStringB.mData[aIndexX - 1]) {
                mDynamic[aIndexY][aIndexX] = mDynamic[aIndexY - 1][aIndexX - 1] + 1;
            } else {
                mDynamic[aIndexY][aIndexX] = std::max(mDynamic[aIndexY - 1][aIndexX], mDynamic[aIndexY][aIndexX - 1]);
            }
        }
    }

    const int aResultLength = mDynamic[aLengthA][aLengthB];
    if (aResultLength <= 0) {
        return ByteString();
    }

    ByteString aResult;
    aResult.Size(aResultLength);
    aResult.mLength = aResultLength;

    int aIndexY = aLengthA;
    int aIndexX = aLengthB;
    int writeIndex = aResultLength - 1;

    while (aIndexY > 0 && aIndexX > 0) {
        if (pStringA.mData[aIndexY - 1] == pStringB.mData[aIndexX - 1]) {
            aResult.mData[writeIndex--] = pStringA.mData[aIndexY - 1];
            aIndexY--;
            aIndexX--;
        } else if (mDynamic[aIndexY - 1][aIndexX] >= mDynamic[aIndexY][aIndexX - 1]) {
            aIndexY--;
        } else {
            aIndexX--;
        }
    }

    return aResult;
}

ByteString CryptoAnalyzer::LongestCommonSubstring(const ByteString &pStringA, const ByteString &pStringB) {
    const int aLengthA = pStringA.mLength;
    const int aLengthB = pStringB.mLength;

    if (aLengthA <= 0 || aLengthB <= 0 || pStringA.mData == nullptr || pStringB.mData == nullptr) {
        return ByteString();
    }

    EnsureDynamicSize(static_cast<std::int16_t>(aLengthB + 1), static_cast<std::int16_t>(aLengthA + 1));

    for (int aIndexY = 0; aIndexY <= aLengthA; aIndexY++) {
        mDynamic[aIndexY][0] = 0;
    }
    for (int aIndexX = 0; aIndexX <= aLengthB; aIndexX++) {
        mDynamic[0][aIndexX] = 0;
    }

    int aBestLength = 0;
    int bestEndIndexA = 0;

    for (int aIndexY = 1; aIndexY <= aLengthA; aIndexY++) {
        for (int aIndexX = 1; aIndexX <= aLengthB; aIndexX++) {
            if (pStringA.mData[aIndexY - 1] == pStringB.mData[aIndexX - 1]) {
                mDynamic[aIndexY][aIndexX] = mDynamic[aIndexY - 1][aIndexX - 1] + 1;
                if (mDynamic[aIndexY][aIndexX] > aBestLength) {
                    aBestLength = mDynamic[aIndexY][aIndexX];
                    bestEndIndexA = aIndexY;
                }
            } else {
                mDynamic[aIndexY][aIndexX] = 0;
            }
        }
    }

    if (aBestLength <= 0) {
        return ByteString();
    }

    ByteString aResult;
    aResult.Size(aBestLength);
    aResult.mLength = aBestLength;
    std::memcpy(aResult.mData,
                pStringA.mData + (bestEndIndexA - aBestLength),
                static_cast<std::size_t>(aBestLength));
    return aResult;
}

std::int32_t CryptoAnalyzer::LongestCommonSubsequenceLength(const ByteString &pStringA, const ByteString &pStringB) {
    const int aLengthA = pStringA.mLength;
    const int aLengthB = pStringB.mLength;

    if (aLengthA <= 0 || aLengthB <= 0 || pStringA.mData == nullptr || pStringB.mData == nullptr) {
        return 0;
    }

    EnsureDynamicSize(static_cast<std::int16_t>(aLengthB + 1), static_cast<std::int16_t>(aLengthA + 1));

    for (int aIndexY = 0; aIndexY <= aLengthA; aIndexY++) {
        mDynamic[aIndexY][0] = 0;
    }
    for (int aIndexX = 0; aIndexX <= aLengthB; aIndexX++) {
        mDynamic[0][aIndexX] = 0;
    }

    for (int aIndexY = 1; aIndexY <= aLengthA; aIndexY++) {
        for (int aIndexX = 1; aIndexX <= aLengthB; aIndexX++) {
            if (pStringA.mData[aIndexY - 1] == pStringB.mData[aIndexX - 1]) {
                mDynamic[aIndexY][aIndexX] = mDynamic[aIndexY - 1][aIndexX - 1] + 1;
            } else {
                mDynamic[aIndexY][aIndexX] = std::max(mDynamic[aIndexY - 1][aIndexX], mDynamic[aIndexY][aIndexX - 1]);
            }
        }
    }

    return mDynamic[aLengthA][aLengthB];
}

std::int32_t CryptoAnalyzer::LongestCommonSubstringLength(const ByteString &pStringA, const ByteString &pStringB) {
    const int aLengthA = pStringA.mLength;
    const int aLengthB = pStringB.mLength;

    if (aLengthA <= 0 || aLengthB <= 0 || pStringA.mData == nullptr || pStringB.mData == nullptr) {
        return 0;
    }

    EnsureDynamicSize(static_cast<std::int16_t>(aLengthB + 1), static_cast<std::int16_t>(aLengthA + 1));

    for (int aIndexY = 0; aIndexY <= aLengthA; aIndexY++) {
        mDynamic[aIndexY][0] = 0;
    }
    for (int aIndexX = 0; aIndexX <= aLengthB; aIndexX++) {
        mDynamic[0][aIndexX] = 0;
    }

    int aBestLength = 0;
    for (int aIndexY = 1; aIndexY <= aLengthA; aIndexY++) {
        for (int aIndexX = 1; aIndexX <= aLengthB; aIndexX++) {
            if (pStringA.mData[aIndexY - 1] == pStringB.mData[aIndexX - 1]) {
                mDynamic[aIndexY][aIndexX] = mDynamic[aIndexY - 1][aIndexX - 1] + 1;
                if (mDynamic[aIndexY][aIndexX] > aBestLength) {
                    aBestLength = mDynamic[aIndexY][aIndexX];
                }
            } else {
                mDynamic[aIndexY][aIndexX] = 0;
            }
        }
    }

    return aBestLength;
}

std::int32_t CryptoAnalyzer::LevenshteinDistance(const ByteString &pStringA, const ByteString &pStringB) {
    const int aLengthA = pStringA.mLength;
    const int aLengthB = pStringB.mLength;

    if (aLengthA <= 0) { return aLengthB; }
    if (aLengthB <= 0) { return aLengthA; }
    if (pStringA.mData == nullptr) { return aLengthB; }
    if (pStringB.mData == nullptr) { return aLengthA; }

    EnsureDynamicSize(static_cast<std::int16_t>(aLengthB + 1), static_cast<std::int16_t>(aLengthA + 1));

    for (int aIndexY = 0; aIndexY <= aLengthA; aIndexY++) {
        mDynamic[aIndexY][0] = aIndexY;
    }
    for (int aIndexX = 0; aIndexX <= aLengthB; aIndexX++) {
        mDynamic[0][aIndexX] = aIndexX;
    }

    for (int aIndexY = 1; aIndexY <= aLengthA; aIndexY++) {
        for (int aIndexX = 1; aIndexX <= aLengthB; aIndexX++) {
            
            int aCostChange = 0;
            if (pStringA.mData[aIndexY - 1] != pStringB.mData[aIndexX - 1]) {
                aCostChange = 1;
            }
            
            const int aCostDelete = mDynamic[aIndexY - 1][aIndexX] + 1;
            const int aCostInsert = mDynamic[aIndexY][aIndexX - 1] + 1;
            const int aCostSubstitute = mDynamic[aIndexY - 1][aIndexX - 1] + aCostChange;
            if (aCostDelete < aCostInsert) {
                if (aCostSubstitute < aCostDelete) {
                    mDynamic[aIndexY][aIndexX] = aCostSubstitute;
                } else {
                    mDynamic[aIndexY][aIndexX] = aCostDelete;
                }
            } else {
                if (aCostSubstitute < aCostInsert) {
                    mDynamic[aIndexY][aIndexX] = aCostSubstitute;
                } else {
                    mDynamic[aIndexY][aIndexX] = aCostInsert;
                }
            }
        }
    }

    return mDynamic[aLengthA][aLengthB];
}

std::int32_t CryptoAnalyzer::LongestCommonSubsequenceLength_WithRotation(const ByteString &pStringA, const ByteString &pStringB) {
    int aResult = 0;
    ByteString aRotatedA;
    aRotatedA.Set(pStringA.mData, pStringA.mLength);
    for (int aRotationA=0; aRotationA<pStringA.mLength; aRotationA++) {
        int aLongestCommonSubsequenceLength = LongestCommonSubsequenceLength(aRotatedA, pStringB);
        if (aLongestCommonSubsequenceLength > aResult) {
            aResult = aLongestCommonSubsequenceLength;
        }
        aRotatedA.Rotate(1);
    }
    return aResult;
}

std::int32_t CryptoAnalyzer::LongestCommonSubstringLength_WithRotation(const ByteString &pStringA, const ByteString &pStringB) {
    int aResult = 0;
    ByteString aRotatedA;
    aRotatedA.Set(pStringA.mData, pStringA.mLength);
    for (int aRotationA=0; aRotationA<pStringA.mLength; aRotationA++) {
        
        int aLongestCommonSubstringLength = LongestCommonSubstringLength(aRotatedA, pStringB);
        if (aLongestCommonSubstringLength > aResult) {
            aResult = aLongestCommonSubstringLength;
        }
        aRotatedA.Rotate(1);
    }
    return aResult;
}

std::int32_t CryptoAnalyzer::LevenshteinDistance_WithRotation(const ByteString &pStringA, const ByteString &pStringB) {
    int aResult = std::max(pStringA.mLength, pStringB.mLength);
    const int aMinimum = std::abs(pStringA.mLength - pStringB.mLength);
    ByteString aRotatedA;
    aRotatedA.Set(pStringA.mData, pStringA.mLength);
    for (int aRotationA = 0; aRotationA < pStringA.mLength; aRotationA++) {
        
        int aLevenshteinDistance = LevenshteinDistance(aRotatedA, pStringB);
        if (aLevenshteinDistance < aResult) {
            aResult = aLevenshteinDistance;
            if (aResult <= aMinimum) { break; }
        }
        aRotatedA.Rotate(1);
    }
    return aResult;
}

std::int32_t CryptoAnalyzer::ComputeDifferenceDistributionTableMax_256(const ByteString &pString) {
    if (pString.mLength != 256) { return 0; }
    EnsureScratch256();
    std::int32_t *aCounts = mScratch256;
    std::int32_t aResult = 0;
    for (int aInputDifference = 1; aInputDifference < 256; ++aInputDifference) {
        std::memset(aCounts, 0, sizeof(std::int32_t) * 256);
        for (int aInput = 0; aInput < 256; ++aInput) {
            const int aPairedInput = aInput ^ aInputDifference;
            const std::uint8_t aOutputDifference = pString.mData[aInput] ^ pString.mData[aPairedInput];
            ++aCounts[aOutputDifference];
        }
        
        // Find the largest count for this input difference
        for (int aOutputDifference = 0; aOutputDifference < 256; ++aOutputDifference) {
            if (aCounts[aOutputDifference] > aResult) {
                aResult = aCounts[aOutputDifference];
            }
        }
    }
    return aResult;
}

std::int32_t CryptoAnalyzer::ComputeLinearCorrelationMax_256(const ByteString &pString) {
    
    if (pString.mLength != 256 || pString.mData == nullptr) {
        return 0;
    }

    EnsureScratch256();
    std::int32_t *aSpectrum = mScratch256;
    std::int32_t aResult = 0;

    // Loop over all non-zero output masks
    for (int aOutputMask = 1; aOutputMask < 256; ++aOutputMask) {

        // Step 1: Build +/-1 signal based on parity of masked output
        for (int aInput = 0; aInput < 256; ++aInput) {
            
            const std::uint8_t aValue = pString.mData[aInput];

            // Count parity of bits selected by mask
            const int aParity = std::popcount(static_cast<unsigned int>(aValue & aOutputMask)) & 1;
            aSpectrum[aInput] = (aParity == 0) ? 1 : -1;
        }

        // Step 2: Fast Walsh-Hadamard Transform
        for (int aStep = 1; aStep < 256; aStep <<= 1) {
            for (int aIndex = 0; aIndex < 256; aIndex += (aStep << 1)) {
                for (int aOffset = 0; aOffset < aStep; ++aOffset) {
                    const int aLeft = aSpectrum[aIndex + aOffset];
                    const int aRight = aSpectrum[aIndex + aOffset + aStep];
                    aSpectrum[aIndex + aOffset] = aLeft + aRight;
                    aSpectrum[aIndex + aOffset + aStep] = aLeft - aRight;
                }
            }
        }

        // Step 3: Track maximum absolute correlation
        for (int aInputMask = 0; aInputMask < 256; ++aInputMask) {
            const int aValue = std::abs(aSpectrum[aInputMask]);
            if (aValue > aResult) {
                aResult = aValue;
            }
        }
    }

    return aResult;
}

std::int32_t CryptoAnalyzer::ComputeMinimumComponentAlgebraicDegree_256(const ByteString &pString) {
    int aMinComponentDegree = 8;
    
    std::uint8_t aAnf[256];
    memset(aAnf, 0, 256);
    
    for (int aOutBit = 0; aOutBit < 8; ++aOutBit) {
        for (int aX = 0; aX < 256; ++aX) {
            aAnf[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>((pString.mData[static_cast<std::size_t>(aX)] >> aOutBit) & 1U);
        }
        
        for (int aBit = 0; aBit < 8; ++aBit) {
            for (int aMask = 0; aMask < 256; ++aMask) {
                if ((aMask & (1 << aBit)) != 0) {
                    aAnf[static_cast<std::size_t>(aMask)] ^=
                    aAnf[static_cast<std::size_t>(aMask ^ (1 << aBit))];
                }
            }
        }
        
        int aDegree = 0;
        for (int aMask = 1; aMask < 256; ++aMask) {
            if (aAnf[static_cast<std::size_t>(aMask)] != 0U) {
                aDegree = std::max(aDegree, std::popcount(static_cast<unsigned int>(aMask)));
            }
        }
        aMinComponentDegree = std::min(aMinComponentDegree, aDegree);
    }
    return aMinComponentDegree;
}

std::int32_t CryptoAnalyzer::ComputeMaximumComponentAlgebraicDegree_256(const ByteString &pString) {
    int aMaxComponentDegree = 0;
    
    std::uint8_t aAnf[256];
    memset(aAnf, 0, 256);
    for (int aOutBit = 0; aOutBit < 8; ++aOutBit) {
        for (int aX = 0; aX < 256; ++aX) {
            aAnf[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>((pString.mData[static_cast<std::size_t>(aX)] >> aOutBit) & 1U);
        }
        
        for (int aBit = 0; aBit < 8; ++aBit) {
            for (int aMask = 0; aMask < 256; ++aMask) {
                if ((aMask & (1 << aBit)) != 0) {
                    aAnf[static_cast<std::size_t>(aMask)] ^=
                    aAnf[static_cast<std::size_t>(aMask ^ (1 << aBit))];
                }
            }
        }
        
        int aDegree = 0;
        for (int aMask = 1; aMask < 256; ++aMask) {
            if (aAnf[static_cast<std::size_t>(aMask)] != 0U) {
                aDegree = std::max(aDegree, std::popcount(static_cast<unsigned int>(aMask)));
            }
        }
        aMaxComponentDegree = std::max(aMaxComponentDegree, aDegree);
        
    }
    return aMaxComponentDegree;
}


std::int32_t CryptoAnalyzer::ComputeSacMaxBias_256(const ByteString &pString) {
    int aSacMaxBias = 0;

    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aOutputBit = 0; aOutputBit < 8; ++aOutputBit) {
            int aChanged = 0;
            for (int aX = 0; aX < 256; ++aX) {
                const std::uint8_t aDelta =
                static_cast<std::uint8_t>(pString.mData[static_cast<std::size_t>(aX)] ^
                                          pString.mData[static_cast<std::size_t>(aX ^ aDX)]);
                aChanged += (aDelta >> aOutputBit) & 1U;
            }
            const int aBias = std::abs(aChanged - 128);
            aSacMaxBias = std::max(aSacMaxBias, aBias);
        }
    }
    return aSacMaxBias;
}

double CryptoAnalyzer::ComputeSacAverageBias_256(const ByteString &pString) {
    double aSacBiasTotal = 0.0;
    int aSacCount = 0;
    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aOutputBit = 0; aOutputBit < 8; ++aOutputBit) {
            int aChanged = 0;
            for (int aX = 0; aX < 256; ++aX) {
                const std::uint8_t aDelta =
                static_cast<std::uint8_t>(pString.mData[static_cast<std::size_t>(aX)] ^
                                          pString.mData[static_cast<std::size_t>(aX ^ aDX)]);
                aChanged += (aDelta >> aOutputBit) & 1U;
            }
            const int aBias = std::abs(aChanged - 128);
            aSacBiasTotal += static_cast<double>(aBias);
            ++aSacCount;
        }
    }
    
    double aSacAverageBias = (aSacCount == 0) ? 0.0 : (aSacBiasTotal / static_cast<double>(aSacCount));
    return aSacAverageBias;
}

std::int32_t CryptoAnalyzer::ComputeBicMaxBias_256(const ByteString &pString) {
    int aBicMaxBias = 0;
    std::uint8_t aDeltaValues[256];
    memset(aDeltaValues, 0, 256);
    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aX = 0; aX < 256; ++aX) {
            aDeltaValues[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>(pString.mData[static_cast<std::size_t>(aX)] ^ pString.mData[static_cast<std::size_t>(aX ^ aDX)]);
        }
        for (int aBitA = 0; aBitA < 8; ++aBitA) {
            for (int aBitB = aBitA + 1; aBitB < 8; ++aBitB) {
                int aXorOnes = 0;
                for (int aX = 0; aX < 256; ++aX) {
                    const std::uint8_t aDelta = aDeltaValues[static_cast<std::size_t>(aX)];
                    const int aPair = (((aDelta >> aBitA) & 1U) ^ ((aDelta >> aBitB) & 1U));
                    aXorOnes += aPair;
                }
                const int aBias = std::abs(aXorOnes - 128);
                aBicMaxBias = std::max(aBicMaxBias, aBias);
            }
        }
    }
    
    return aBicMaxBias;
}

double CryptoAnalyzer::ComputeBicAverageBias_256(const ByteString &pString) {
    
    double aBicBiasTotal = 0.0;
    int aBicCount = 0;
    
    std::uint8_t aDeltaValues[256];
    memset(aDeltaValues, 0, 256);
    
    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aX = 0; aX < 256; ++aX) {
            aDeltaValues[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>(pString.mData[static_cast<std::size_t>(aX)] ^ pString.mData[static_cast<std::size_t>(aX ^ aDX)]);
        }
        
        for (int aBitA = 0; aBitA < 8; ++aBitA) {
            for (int aBitB = aBitA + 1; aBitB < 8; ++aBitB) {
                int aXorOnes = 0;
                for (int aX = 0; aX < 256; ++aX) {
                    const std::uint8_t aDelta = aDeltaValues[static_cast<std::size_t>(aX)];
                    const int aPair = (((aDelta >> aBitA) & 1U) ^ ((aDelta >> aBitB) & 1U));
                    aXorOnes += aPair;
                }
                const int aBias = std::abs(aXorOnes - 128);
                aBicBiasTotal += static_cast<double>(aBias);
                ++aBicCount;
            }
        }
    }
    double aBicAverageBias = (aBicCount == 0) ? 0.0 : (aBicBiasTotal / static_cast<double>(aBicCount));
    return aBicAverageBias;
}



CryptoAnalyzer::BitInclusionStats CryptoAnalyzer::ComputeBitInclusion(const ByteString &pString) {
    CryptoAnalyzer::BitInclusionStats aStats;
    aStats.mBitsSet = 0;
    aStats.mBitsCleared = 0;
    for (int aBit = 0; aBit < 8; ++aBit) { aStats.mBitCounts[aBit] = 0; }
    if (pString.mLength <= 0) { return aStats; }
    const std::int32_t aLength = pString.mLength;
    for (std::int32_t aIndex = 0; aIndex < aLength; ++aIndex) {
        const std::uint8_t aValue = pString.mData[aIndex];
        for (int aBit = 0; aBit < 8; ++aBit) {
            if ((aValue >> aBit) & 1U) {
                aStats.mBitCounts[aBit]++;
            }
        }
    }
    
    for (int aBit = 0; aBit < 8; ++aBit) {
        const std::uint32_t aCount = aStats.mBitCounts[aBit];
        if (aCount > 0) { ++aStats.mBitsSet; }
        if (aCount < static_cast<std::uint32_t>(aLength)) { ++aStats.mBitsCleared; }
    }
    return aStats;
}

CryptoAnalyzer::CharacterDistributionStats CryptoAnalyzer::ComputeCharacterDistribution(const ByteString &pString) {
    CryptoAnalyzer::CharacterDistributionStats aStats;
    aStats.mDistinctCharacterCount = 0;
    aStats.mDuplicateCharacterCount = 0;
    aStats.mExtraCharacterCount = 0;
    aStats.mMaxCharacterCount = 0;
    for (int aIndex = 0; aIndex < 256; ++aIndex) {
        aStats.mCharacterCounts[aIndex] = 0;
    }

    if (pString.mLength <= 0 || pString.mData == nullptr) {
        return aStats;
    }

    for (int aIndex = 0; aIndex < pString.mLength; ++aIndex) {
        const int aValue = static_cast<int>(pString.mData[aIndex]);
        ++aStats.mCharacterCounts[aValue];
    }

    for (int aValue = 0; aValue < 256; ++aValue) {
        const int aCount = aStats.mCharacterCounts[aValue];
        if (aCount <= 0) {
            continue;
        }

        ++aStats.mDistinctCharacterCount;
        if (aCount > 1) {
            ++aStats.mDuplicateCharacterCount;
            aStats.mExtraCharacterCount += (aCount - 1);
        }
        if (aCount > aStats.mMaxCharacterCount) {
            aStats.mMaxCharacterCount = aCount;
        }
    }

    return aStats;
}


CryptoAnalyzer::AvalancheStats CryptoAnalyzer::ComputeAvalancheStats(const ByteString &pStringA, const ByteString &pStringB) {

    CryptoAnalyzer::AvalancheStats aStats;
    aStats.mHasMatchingLength = false;
    aStats.mComparedBytes = 0;
    aStats.mChangedBytes = 0;
    aStats.mUnchangedBytes = 0;
    aStats.mChangedBits = 0;
    aStats.mUnchangedBits = 0;
    aStats.mMinBitFlipCount = 0;
    aStats.mMaxBitFlipCount = 0;
    aStats.mTotalBitFlipScore = 0;
    aStats.mPerBitFlipScore = 0;
    aStats.mByteCoverageScore = 0;
    aStats.mScore = 0;
    for (int aBit = 0; aBit < 8; ++aBit) {
        aStats.mBitFlipCounts[aBit] = 0;
    }

    if (pStringA.mData == nullptr || pStringB.mData == nullptr) {
        return aStats;
    }

    if (pStringA.mLength <= 0 || pStringB.mLength <= 0) {
        return aStats;
    }

    if (pStringA.mLength != pStringB.mLength) {
        return aStats;
    }

    const std::int32_t aLength = pStringA.mLength;
    aStats.mHasMatchingLength = true;
    aStats.mComparedBytes = aLength;
    aStats.mMinBitFlipCount = aLength;

    for (std::int32_t aIndex = 0; aIndex < aLength; ++aIndex) {

        const std::uint8_t aDelta = static_cast<std::uint8_t>(pStringA.mData[aIndex] ^ pStringB.mData[aIndex]);

        if (aDelta != 0U) {
            ++aStats.mChangedBytes;
        }

        const std::int32_t aChangedBitsInByte = static_cast<std::int32_t>(std::popcount(static_cast<unsigned int>(aDelta)));
        aStats.mChangedBits += aChangedBitsInByte;

        for (int aBit = 0; aBit < 8; ++aBit) {
            if (((aDelta >> aBit) & 1U) != 0U) {
                ++aStats.mBitFlipCounts[aBit];
            }
        }
    }

    aStats.mUnchangedBytes = aLength - aStats.mChangedBytes;
    aStats.mUnchangedBits = (aLength * 8) - aStats.mChangedBits;

    std::int64_t aPerBitScoreTotal = 0;
    for (int aBit = 0; aBit < 8; ++aBit) {
        const std::int32_t aCount = aStats.mBitFlipCounts[aBit];
        if (aCount < aStats.mMinBitFlipCount) {
            aStats.mMinBitFlipCount = aCount;
        }
        if (aCount > aStats.mMaxBitFlipCount) {
            aStats.mMaxBitFlipCount = aCount;
        }
        aPerBitScoreTotal += static_cast<std::int64_t>(ScoreTowardsHalf(aCount, aLength));
    }

    aStats.mTotalBitFlipScore = ScoreTowardsHalf(aStats.mChangedBits, aLength * 8);
    aStats.mPerBitFlipScore = static_cast<std::int32_t>(aPerBitScoreTotal / 8LL);
    aStats.mByteCoverageScore = static_cast<std::int32_t>(
        (static_cast<std::int64_t>(aStats.mChangedBytes) * static_cast<std::int64_t>(kAvalancheScorePerfect)) /
        static_cast<std::int64_t>(aLength));

    aStats.mScore = static_cast<std::int32_t>(
        (static_cast<std::int64_t>(aStats.mTotalBitFlipScore) * 4LL +
         static_cast<std::int64_t>(aStats.mPerBitFlipScore) * 4LL +
         static_cast<std::int64_t>(aStats.mByteCoverageScore) * 2LL) / 10LL);

    return aStats;
}

std::int32_t CryptoAnalyzer::ComputeAvalancheScore(const ByteString &pStringA, const ByteString &pStringB) {
    return ComputeAvalancheStats(pStringA, pStringB).mScore;
}

// We only ever increase mDynamicWidth and mDynamicHeight
// We only ever increase mDynamicWidth and mDynamicHeight
void CryptoAnalyzer::EnsureDynamicSize(std::int16_t pWidth, std::int16_t pHeight) {
    if (pWidth <= 0 || pHeight <= 0) {
        return;
    }

    if (pWidth <= mDynamicWidth && pHeight <= mDynamicHeight) {
        return;
    }

    const int aNewWidth = std::max<int>(mDynamicWidth, pWidth);
    const int aNewHeight = std::max<int>(mDynamicHeight, pHeight);

    int **aNewDynamic = new int *[aNewHeight];
    for (int aIndexY = 0; aIndexY < aNewHeight; aIndexY++) {
        aNewDynamic[aIndexY] = new int[aNewWidth];
        for (int aIndexX = 0; aIndexX < aNewWidth; aIndexX++) {
            aNewDynamic[aIndexY][aIndexX] = 0;
        }
    }

    for (int aIndexY = 0; aIndexY < mDynamicHeight; aIndexY++) {
        for (int aIndexX = 0; aIndexX < mDynamicWidth; aIndexX++) {
            aNewDynamic[aIndexY][aIndexX] = mDynamic[aIndexY][aIndexX];
        }
    }

    for (int aIndexY = 0; aIndexY < mDynamicHeight; aIndexY++) {
        delete [] mDynamic[aIndexY];
    }
    delete [] mDynamic;

    mDynamic = aNewDynamic;
    mDynamicWidth = aNewWidth;
    mDynamicHeight = aNewHeight;
}

void CryptoAnalyzer::EnsureScratch256() {
    if (mScratch256 == nullptr) {
        mScratch256 = new std::int32_t[256];
    }
}
