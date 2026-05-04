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

std::int32_t TwistCryptoScoring::ComputeDifferenceDistributionTableMax_256(const std::uint8_t *pData, const int pLength) {
    
    std::int32_t aCounts[256];
    std::int32_t aResult = 0;
    for (int aInputDifference = 1; aInputDifference < 256; ++aInputDifference) {
        std::memset(aCounts, 0, sizeof(std::int32_t) * 256);
        for (int aInput = 0; aInput < 256; ++aInput) {
            const int aPairedInput = aInput ^ aInputDifference;
            const std::uint8_t aOutputDifference = pData[aInput] ^ pData[aPairedInput];
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

std::int32_t TwistCryptoScoring::ComputeLinearCorrelationMax_256(const std::uint8_t *pData, const int pLength) {
    
    std::int32_t aSpectrum[256];
    std::int32_t aResult = 0;

    // Loop over all non-zero output masks
    for (int aOutputMask = 1; aOutputMask < 256; ++aOutputMask) {

        // Step 1: Build +/-1 signal based on parity of masked output
        for (int aInput = 0; aInput < 256; ++aInput) {
            
            const std::uint8_t aValue = pData[aInput];

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

std::int32_t TwistCryptoScoring::ComputeMinimumComponentAlgebraicDegree_256(const std::uint8_t *pData, const int pLength) {
    int aMinComponentDegree = 8;
    
    std::uint8_t aAnf[256];
    memset(aAnf, 0, 256);
    
    for (int aOutBit = 0; aOutBit < 8; ++aOutBit) {
        for (int aX = 0; aX < 256; ++aX) {
            aAnf[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>((pData[static_cast<std::size_t>(aX)] >> aOutBit) & 1U);
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

std::int32_t TwistCryptoScoring::ComputeMaximumComponentAlgebraicDegree_256(const std::uint8_t *pData, const int pLength) {
    int aMaxComponentDegree = 0;
    
    std::uint8_t aAnf[256];
    memset(aAnf, 0, 256);
    for (int aOutBit = 0; aOutBit < 8; ++aOutBit) {
        for (int aX = 0; aX < 256; ++aX) {
            aAnf[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>((pData[static_cast<std::size_t>(aX)] >> aOutBit) & 1U);
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


std::int32_t TwistCryptoScoring::ComputeSacMaxBias_256(const std::uint8_t *pData, const int pLength) {
    int aSacMaxBias = 0;

    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aOutputBit = 0; aOutputBit < 8; ++aOutputBit) {
            int aChanged = 0;
            for (int aX = 0; aX < 256; ++aX) {
                const std::uint8_t aDelta =
                static_cast<std::uint8_t>(pData[static_cast<std::size_t>(aX)] ^
                                          pData[static_cast<std::size_t>(aX ^ aDX)]);
                aChanged += (aDelta >> aOutputBit) & 1U;
            }
            const int aBias = std::abs(aChanged - 128);
            aSacMaxBias = std::max(aSacMaxBias, aBias);
        }
    }
    return aSacMaxBias;
}

float TwistCryptoScoring::ComputeSacAverageBias_256(const std::uint8_t *pData, const int pLength) {
    float aSacBiasTotal = 0.0;
    int aSacCount = 0;
    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aOutputBit = 0; aOutputBit < 8; ++aOutputBit) {
            int aChanged = 0;
            for (int aX = 0; aX < 256; ++aX) {
                const std::uint8_t aDelta =
                static_cast<std::uint8_t>(pData[static_cast<std::size_t>(aX)] ^
                                          pData[static_cast<std::size_t>(aX ^ aDX)]);
                aChanged += (aDelta >> aOutputBit) & 1U;
            }
            const int aBias = std::abs(aChanged - 128);
            aSacBiasTotal += static_cast<float>(aBias);
            ++aSacCount;
        }
    }
    float aSacAverageBias = (aSacCount == 0) ? 0.0 : (aSacBiasTotal / static_cast<float>(aSacCount));
    return aSacAverageBias;
}

std::int32_t TwistCryptoScoring::ComputeBicMaxBias_256(const std::uint8_t *pData, const int pLength) {
    int aBicMaxBias = 0;
    std::uint8_t aDeltaValues[256];
    memset(aDeltaValues, 0, 256);
    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aX = 0; aX < 256; ++aX) {
            aDeltaValues[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>(pData[static_cast<std::size_t>(aX)] ^ pData[static_cast<std::size_t>(aX ^ aDX)]);
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

float TwistCryptoScoring::ComputeBicAverageBias_256(const std::uint8_t *pData, const int pLength) {
    
    float aBicBiasTotal = 0.0;
    int aBicCount = 0;
    
    std::uint8_t aDeltaValues[256];
    memset(aDeltaValues, 0, 256);
    
    for (int aInputBit = 0; aInputBit < 8; ++aInputBit) {
        const int aDX = 1 << aInputBit;
        for (int aX = 0; aX < 256; ++aX) {
            aDeltaValues[static_cast<std::size_t>(aX)] =
            static_cast<std::uint8_t>(pData[static_cast<std::size_t>(aX)] ^ pData[static_cast<std::size_t>(aX ^ aDX)]);
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
                aBicBiasTotal += static_cast<float>(aBias);
                ++aBicCount;
            }
        }
    }
    float aBicAverageBias = (aBicCount == 0) ? 0.0 : (aBicBiasTotal / static_cast<float>(aBicCount));
    return aBicAverageBias;
}

std::int32_t TwistCryptoScoring::ComputeDifferentialSimilarityMax_256(const std::uint8_t *pDataA,
                                                                      const std::uint8_t *pDataB,
                                                                      const int pLength) {
    
    std::int32_t aMaximumSameCount = 0;
    
    for (std::int32_t aInputDifference = 1; aInputDifference < 256; aInputDifference++) {
        
        std::int32_t aSameCount = 0;
        
        for (std::int32_t aInputValue = 0; aInputValue < 256; aInputValue++) {
            
            std::uint8_t aOutputDifferenceA =
                pDataA[aInputValue] ^ pDataA[aInputValue ^ aInputDifference];
            
            std::uint8_t aOutputDifferenceB =
                pDataB[aInputValue] ^ pDataB[aInputValue ^ aInputDifference];
            
            if (aOutputDifferenceA == aOutputDifferenceB) {
                aSameCount += 1;
            }
        }
        
        if (aSameCount > aMaximumSameCount) {
            aMaximumSameCount = aSameCount;
        }
    }
    
    return aMaximumSameCount;
}

std::int32_t TwistCryptoScoring::ComputeXorDistributionMax_256(const std::uint8_t *pDataA,
                                                               const std::uint8_t *pDataB,
                                                               const int pLength) {
    
    std::int32_t aHistogram[256] = {};
    
    for (std::int32_t aIndex = 0; aIndex < 256; aIndex++) {
        std::uint8_t aDifference = pDataA[aIndex] ^ pDataB[aIndex];
        aHistogram[aDifference] += 1;
    }
    
    std::int32_t aMaximumBucket = 0;
    
    for (std::int32_t aIndex = 0; aIndex < 256; aIndex++) {
        if (aHistogram[aIndex] > aMaximumBucket) {
            aMaximumBucket = aHistogram[aIndex];
        }
    }
    
    return aMaximumBucket;
}

bool TwistCryptoScoring::Equal_256(const std::uint8_t *pDataA,
                                              const std::uint8_t *pDataB) {
    return (std::memcmp(pDataA, pDataB, 256) == 0);
}

bool TwistCryptoScoring::Equal_128(const std::uint8_t *pDataA,
                                   const std::uint8_t *pDataB) {
    
    for (int aIndex = 0; aIndex < 128; aIndex++) {
        
        if (pDataA[aIndex] != pDataB[aIndex]) {
            return false;
        }
    }
    
    return true;
}
bool TwistCryptoScoring::ComputeIsPermutation_256(const std::uint8_t *pData,
                                                  const int pLength) {
    
    std::uint8_t aSeen[256];
    std::memset(aSeen, 0, 256);
    
    for (int aIndex = 0; aIndex < 256; aIndex++) {
        
        std::uint8_t aValue = pData[aIndex];
        
        if (aSeen[aValue] != 0) {
            return false; // duplicate output → not a permutation
        }
        
        aSeen[aValue] = 1;
    }
    
    return true;
}


void TwistCryptoScoring::PrintBox_256(const char *pName, const std::uint8_t *pData) {
    
    printf("\n%s\n", pName);
    printf("--------------------------------------------------\n");
    
    for (int aRow = 0; aRow < 16; aRow++) {
        
        printf("[%02X] ", aRow << 4);
        
        for (int aCol = 0; aCol < 16; aCol++) {
            int aIndex = (aRow << 4) | aCol;
            printf("%02X ", pData[aIndex]);
        }
        
        printf("\n");
    }
}






/*
int TwistCryptoScoring::ComputeSaltMixResponse_128(const std::uint8_t *pData) {
    
    int aScore = 0;
    
    std::uint16_t aValue = 0x1234;
    
    for (int i = 0; i < 64; i++) {
        
        std::uint8_t aSalt = pData[i & 127];
        
        std::uint16_t aBefore = aValue;
        
        aValue ^= aSalt;
        aValue = TwistMix16::Mix161(
            static_cast<Mix161Type>((i % 11) + 1),
            aValue,
            pData // treat salt as S-box-like input
        );
        
        std::uint16_t aDiff = aBefore ^ aValue;
        
        // count changed bits
        int aBits = __builtin_popcount(aDiff);
        
        aScore += aBits;
    }
    
    return aScore;
}
*/

int TwistCryptoScoring::ComputeSaltBitBalance_128(const std::uint8_t *pData) {
    
    int aBitCount[8] = {0};
    
    for (int i = 0; i < 128; i++) {
        std::uint8_t v = pData[i];
        
        for (int b = 0; b < 8; b++) {
            if (v & (1U << b)) {
                aBitCount[b]++;
            }
        }
    }
    
    int aScore = 0;
    
    for (int b = 0; b < 8; b++) {
        int aDiff = std::abs(aBitCount[b] - 64); // ideal = 64
        
        // smaller diff = better → invert into score
        aScore += (64 - aDiff);
    }
    
    return aScore; // max = 512
}

int TwistCryptoScoring::ComputeSaltByteSpread_128(const std::uint8_t *pData) {
    
    bool aSeen[256] = {false};
    
    int aUnique = 0;
    
    for (int i = 0; i < 128; i++) {
        std::uint8_t v = pData[i];
        
        if (!aSeen[v]) {
            aSeen[v] = true;
            aUnique++;
        }
    }
    
    return aUnique; // max = 128
}

int TwistCryptoScoring::ComputeSaltAdjacencyPenalty_128(const std::uint8_t *pData) {
    int aPenalty = 0;
    for (int i=1; i<128; i++) {
        std::uint8_t aValueA = pData[i];
        std::uint8_t aValueB = pData[i - 1];
        if (aValueA == aValueB) {
            aPenalty += 4;
        }
        else if ((aValueA ^ aValueB) < 4) {
            aPenalty += 2;
        }
    }
    return aPenalty;
}


int TwistCryptoScoring::ComputeSaltXorDrift_128(const std::uint8_t *pData) {
    
    int aScore = 0;
    
    for (int i=1; i<128; i++) {
        
        std::uint8_t aValueA = pData[i];
        std::uint8_t aValueB = pData[i - 1];
        
        std::uint8_t aXor = aValueA ^ aValueB;
        
        // count changed bits
        int aBits = __builtin_popcount(aXor);
        
        aScore += aBits;
    }
    
    return aScore; // max = 127 * 8 = 1016
}


std::uint64_t TwistCryptoScoring::ComputeSaltComprehensiveAgainstSBoxFamily(const std::uint8_t *pSalt,
                                                                            std::uint8_t *pSBoxA,
                                                                            std::uint8_t *pSBoxB,
                                                                            std::uint8_t *pSBoxC,
                                                                            std::uint8_t *pSBoxD,
                                                                            std::uint8_t *pSBoxE,
                                                                            std::uint8_t *pSBoxF,
                                                                            std::uint8_t *pSBoxG,
                                                                            std::uint8_t *pSBoxH) {
    
    std::uint8_t *aList[8];
    int aListCount = 0;
    
    if (pSBoxA) { aList[aListCount++] = pSBoxA; }
    if (pSBoxB) { aList[aListCount++] = pSBoxB; }
    if (pSBoxC) { aList[aListCount++] = pSBoxC; }
    if (pSBoxD) { aList[aListCount++] = pSBoxD; }
    if (pSBoxE) { aList[aListCount++] = pSBoxE; }
    if (pSBoxF) { aList[aListCount++] = pSBoxF; }
    if (pSBoxG) { aList[aListCount++] = pSBoxG; }
    if (pSBoxH) { aList[aListCount++] = pSBoxH; }
    
    std::uint64_t aScore = 0;
    std::uint64_t aBaseValue = 0;
    std::uint64_t aBefore = 0;
    std::uint64_t aValue = aBaseValue;
    
    int aRotations[16] = {
        1, 3, 5, 7,
        11, 13, 19, 21,
        27, 29, 35, 37,
        43, 45, 51, 53
    };
    
    for (int aSBoxIndexA = 0; aSBoxIndexA < aListCount; aSBoxIndexA++) {
        
        std::uint8_t *aBox = aList[aSBoxIndexA];
        
        aValue = aBaseValue;
        for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
            aBefore = aValue;
            aValue = TwistMix64::GatePrism_1_8(aValue ^ pSalt[aSaltIndex], aBox);
            aScore += __builtin_popcountll(aBefore ^ aValue);
        }
        
        for (int aRotationIndex=0; aRotationIndex<16; aRotationIndex++) {
            
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRoll_1_1(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBox);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRoll_1_4(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBox);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRoll_1_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBox);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurn_1_1(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBox);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurn_1_4(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBox);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurn_1_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBox);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
        }
    }
    
    for (int aStartIndex = 0; aStartIndex < aListCount; aStartIndex++) {
        
        std::uint8_t *aBoxA = aList[((aStartIndex + 0) % aListCount)];
        std::uint8_t *aBoxB = aList[((aStartIndex + 1) % aListCount)];
        std::uint8_t *aBoxC = aList[((aStartIndex + 2) % aListCount)];
        std::uint8_t *aBoxD = aList[((aStartIndex + 3) % aListCount)];
        
        aValue = aBaseValue;
        for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
            aBefore = aValue;
            aValue = TwistMix64::GatePrismA_4_8(aValue ^ pSalt[aSaltIndex], aBoxA, aBoxB, aBoxC, aBoxD);
            aScore += __builtin_popcountll(aBefore ^ aValue);
        }
        
        aValue = aBaseValue;
        for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
            aBefore = aValue;
            aValue = TwistMix64::GatePrismB_4_8(aValue ^ pSalt[aSaltIndex], aBoxA, aBoxB, aBoxC, aBoxD);
            aScore += __builtin_popcountll(aBefore ^ aValue);
        }
        
        aValue = aBaseValue;
        for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
            aBefore = aValue;
            aValue = TwistMix64::GatePrismC_4_8(aValue ^ pSalt[aSaltIndex], aBoxA, aBoxB, aBoxC, aBoxD);
            aScore += __builtin_popcountll(aBefore ^ aValue);
        }
        
        for (int aRotationIndex=0; aRotationIndex<16; aRotationIndex++) {
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRoll_4_4(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRollA_4_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRollB_4_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRollC_4_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurn_4_4(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurnA_4_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurnB_4_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurnC_4_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
        }
    }
    
    for (int aStartIndex = 0; aStartIndex < aListCount; aStartIndex++) {
        
        std::uint8_t *aBoxA = aList[((aStartIndex + 0) % aListCount)];
        std::uint8_t *aBoxB = aList[((aStartIndex + 1) % aListCount)];
        std::uint8_t *aBoxC = aList[((aStartIndex + 2) % aListCount)];
        std::uint8_t *aBoxD = aList[((aStartIndex + 3) % aListCount)];
        std::uint8_t *aBoxE = aList[((aStartIndex + 4) % aListCount)];
        std::uint8_t *aBoxF = aList[((aStartIndex + 5) % aListCount)];
        std::uint8_t *aBoxG = aList[((aStartIndex + 6) % aListCount)];
        std::uint8_t *aBoxH = aList[((aStartIndex + 7) % aListCount)];
        
        aValue = aBaseValue;
        for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
            aBefore = aValue;
            aValue = TwistMix64::GatePrism_8_8(aValue ^ pSalt[aSaltIndex], aBoxA, aBoxB, aBoxC, aBoxD, aBoxE, aBoxF, aBoxG, aBoxH);
            aScore += __builtin_popcountll(aBefore ^ aValue);
        }
        
        aValue = aBaseValue;
        for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
            aBefore = aValue;
            aValue = TwistMix64::GatePrism_8_8(aValue ^ pSalt[aSaltIndex], aBoxH, aBoxB, aBoxF, aBoxD, aBoxE, aBoxC, aBoxG, aBoxA);
            aScore += __builtin_popcountll(aBefore ^ aValue);
        }
        
        aValue = aBaseValue;
        for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
            aBefore = aValue;
            aValue = TwistMix64::GatePrism_8_8(aValue ^ pSalt[aSaltIndex], aBoxA, aBoxG, aBoxC, aBoxE, aBoxD, aBoxF, aBoxB, aBoxH);
            aScore += __builtin_popcountll(aBefore ^ aValue);
        }
        
        
        for (int aRotationIndex=0; aRotationIndex<16; aRotationIndex++) {

            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRoll_8_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD, aBoxE, aBoxF, aBoxG, aBoxH);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRoll_8_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxH, aBoxB, aBoxF, aBoxD, aBoxE, aBoxC, aBoxG, aBoxA);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateRoll_8_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxG, aBoxC, aBoxE, aBoxD, aBoxF, aBoxB, aBoxH);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurn_8_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxB, aBoxC, aBoxD, aBoxE, aBoxF, aBoxG, aBoxH);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurn_8_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxH, aBoxB, aBoxF, aBoxD, aBoxE, aBoxC, aBoxG, aBoxA);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
            
            aValue = aBaseValue;
            for (int aSaltIndex = 0; aSaltIndex < S_SALT; aSaltIndex++) {
                aBefore = aValue;
                aValue = TwistMix64::GateTurn_8_8(aValue ^ pSalt[aSaltIndex], aRotations[aRotationIndex], aBoxA, aBoxG, aBoxC, aBoxE, aBoxD, aBoxF, aBoxB, aBoxH);
                aScore += __builtin_popcountll(aBefore ^ aValue);
            }
        }
    }
    return aScore;
}

std::int32_t TwistCryptoScoring::ComputeMinimumCycle_256(const std::uint8_t *pData,
                                                         const int pLength) {
    
    if ((pData == nullptr) || (pLength < 256)) {
        return 0;
    }
    
    std::int32_t aResult = 256;
    
    for (int aStart = 0; aStart < 256; aStart++) {
        
        std::int32_t aSeen[256];
        std::memset(aSeen, 0xFF, sizeof(std::int32_t) * 256);
        
        std::uint8_t aValue = static_cast<std::uint8_t>(aStart);
        std::int32_t aStep = 0;
        
        while (aSeen[aValue] < 0) {
            
            aSeen[aValue] = aStep;
            aValue = pData[aValue];
            aStep += 1;
        }
        
        const std::int32_t aCycleLength = aStep - aSeen[aValue];
        
        if (aCycleLength < aResult) {
            aResult = aCycleLength;
        }
    }
    
    return aResult;
}

std::int32_t TwistCryptoScoring::ComputeMinimumCycleRotL3AfterGate_256(const std::uint8_t *pData,
                                                                       const int pLength) {
    
    if ((pData == nullptr) || (pLength < 256)) {
        return 0;
    }
    
    std::int32_t aResult = 256;
    for (int aStart = 0; aStart < 256; aStart++) {
        std::int32_t aSeen[256];
        std::memset(aSeen, 0xFF, sizeof(std::int32_t) * 256);
        std::uint8_t aValue = static_cast<std::uint8_t>(aStart);
        std::int32_t aStep = 0;
        while (aSeen[aValue] < 0) {
            aSeen[aValue] = aStep;
            aValue = pData[aValue];
            aValue = static_cast<std::uint8_t>((aValue << 3U) | (aValue >> 5U));
            aStep += 1;
        }
        const std::int32_t aCycleLength = aStep - aSeen[aValue];
        if (aCycleLength < aResult) {
            aResult = aCycleLength;
        }
    }
    return aResult;
}

std::int32_t TwistCryptoScoring::ComputeMinimumCycleRotL5AfterGate_256(const std::uint8_t *pData,
                                                                       const int pLength) {
    
    if ((pData == nullptr) || (pLength < 256)) {
        return 0;
    }
    
    std::int32_t aResult = 256;
    for (int aStart = 0; aStart < 256; aStart++) {
        std::int32_t aSeen[256];
        std::memset(aSeen, 0xFF, sizeof(std::int32_t) * 256);
        std::uint8_t aValue = static_cast<std::uint8_t>(aStart);
        std::int32_t aStep = 0;
        while (aSeen[aValue] < 0) {
            aSeen[aValue] = aStep;
            aValue = pData[aValue];
            aValue = static_cast<std::uint8_t>((aValue << 5U) | (aValue >> 3U));
            aStep += 1;
        }
        const std::int32_t aCycleLength = aStep - aSeen[aValue];
        if (aCycleLength < aResult) {
            aResult = aCycleLength;
        }
    }
    return aResult;
}
