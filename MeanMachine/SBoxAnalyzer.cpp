//
//  SBoxAnalyzer.cpp
//  Gorgon
//
//  Created by Sonic The Hedge Whore on 4/10/26.
//

#include "SBoxAnalyzer.hpp"
#include <algorithm>
#include <bit>
#include <cstring>


SBoxAnalyzer::SBoxAnalyzer() {
    mScratch256 = NULL;
}

SBoxAnalyzer::~SBoxAnalyzer() {

    delete [] mScratch256;
    mScratch256 = NULL;
}


std::int32_t SBoxAnalyzer::ComputeDifferenceDistributionTableMax_256(const std::uint8_t *pData, const int pLength) {
    
    EnsureScratch256();
    std::int32_t *aCounts = mScratch256;
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

std::int32_t SBoxAnalyzer::ComputeLinearCorrelationMax_256(const std::uint8_t *pData, const int pLength) {
    
    EnsureScratch256();
    std::int32_t *aSpectrum = mScratch256;
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

std::int32_t SBoxAnalyzer::ComputeMinimumComponentAlgebraicDegree_256(const std::uint8_t *pData, const int pLength) {
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

std::int32_t SBoxAnalyzer::ComputeMaximumComponentAlgebraicDegree_256(const std::uint8_t *pData, const int pLength) {
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


std::int32_t SBoxAnalyzer::ComputeSacMaxBias_256(const std::uint8_t *pData, const int pLength) {
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

double SBoxAnalyzer::ComputeSacAverageBias_256(const std::uint8_t *pData, const int pLength) {
    double aSacBiasTotal = 0.0;
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
            aSacBiasTotal += static_cast<double>(aBias);
            ++aSacCount;
        }
    }
    
    double aSacAverageBias = (aSacCount == 0) ? 0.0 : (aSacBiasTotal / static_cast<double>(aSacCount));
    return aSacAverageBias;
}

std::int32_t SBoxAnalyzer::ComputeBicMaxBias_256(const std::uint8_t *pData, const int pLength) {
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

double SBoxAnalyzer::ComputeBicAverageBias_256(const std::uint8_t *pData, const int pLength) {
    
    double aBicBiasTotal = 0.0;
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
                aBicBiasTotal += static_cast<double>(aBias);
                ++aBicCount;
            }
        }
    }
    double aBicAverageBias = (aBicCount == 0) ? 0.0 : (aBicBiasTotal / static_cast<double>(aBicCount));
    return aBicAverageBias;
}

void SBoxAnalyzer::EnsureScratch256() {
    if (mScratch256 == nullptr) {
        mScratch256 = new std::int32_t[256];
    }
}
