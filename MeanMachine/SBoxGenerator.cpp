//
//  SBoxGenerator.cpp
//  MeanMachine
//
//  Created by Dragon on 4/28/26.
//

#include "SBoxGenerator.hpp"
#include <cstring>
#include <algorithm>

SBoxGenerator::SBoxGenerator() {
    mExponents[0] = 11;
    mExponents[1] = 13;
    mExponents[2] = 19;
    mExponents[3] = 23;
    mExponents[4] = 254;
    mTablesBuilt = false;
}

SBoxGenerator::~SBoxGenerator() {
    // nothing
}

void SBoxGenerator::BuildGFTables() {
    
    int aX = 1;
    
    for (int aI = 0; aI < 255; aI++) {
        mExp[aI] = aX;
        mExp[aI + 255] = aX;
        mLog[aX] = aI;
        
        int aNext = aX ^ (aX << 1);
        if (aNext & 0x100) aNext ^= 0x11B;
        
        aX = aNext;
    }
    
    mLog[0] = 0;
    mTablesBuilt = true;
}

std::uint8_t SBoxGenerator::ReadSeed(const std::uint8_t *pSource, int pIndex) {
    return pSource[pIndex & (S_BLOCK - 1)];
}

void SBoxGenerator::BuildMatrix(const std::uint8_t *pSource,
                                int aIndex,
                                std::uint8_t *pMatrix) {
    
    for (int aRow = 0; aRow < 8; aRow++) {
        std::uint8_t aValue = ReadSeed(pSource, aIndex + aRow);
        //std::uint8_t aValue = pSource[aIndex + aRow];
        
        
        // spread bits + ensure diagonal presence
        aValue ^= static_cast<std::uint8_t>((aValue << 1U) | (aValue >> 7U));
        aValue |= (1 << aRow);
        
        pMatrix[aRow] = aValue;
    }
    
    // deterministic mixing to ensure invertibility-ish
    for (int aIter = 0; aIter < 16; aIter++) {
        int aA = ReadSeed(pSource, aIndex + aIter) & 7;
        int aB = ReadSeed(pSource, aIndex + aIter + 37) & 7;
        
        if (aA != aB) {
            pMatrix[aA] ^= pMatrix[aB];
        }
    }
    
    // ensure rows are not identical / degenerate
    for (int i = 0; i < 8; i++) {
        if (pMatrix[i] == 0) {
            pMatrix[i] = static_cast<std::uint8_t>(1 << i);
        }
    }
}

void SBoxGenerator::ApplyMatrix(const std::uint8_t *pMatrix,
                                const std::uint8_t *pInput,
                                std::uint8_t *pOutput) {
    
    for (int aIndex = 0; aIndex < 256; aIndex++) {
        
        std::uint8_t aX = pInput[aIndex];
        std::uint8_t aY = 0;
        
        for (int aBit = 0; aBit < 8; aBit++) {
            std::uint8_t aMask = pMatrix[aBit] & aX;
            std::uint8_t aParity = static_cast<std::uint8_t>(__builtin_popcount(aMask) & 1U);
            aY |= static_cast<std::uint8_t>(aParity << aBit);
        }
        
        pOutput[aIndex] = aY;
    }
}

void SBoxGenerator::GenerateCandidate(const std::uint8_t *pSource,
                                      int aIndex,
                                      std::uint8_t *pOutput) {
    
    std::uint8_t *aMatrix = mMatrices[aIndex];
    
    BuildMatrix(pSource, aIndex, aMatrix);
    
    std::uint8_t aBase[256]; // small, acceptable stack (256 bytes)
    
    for (int aI = 0; aI < 256; aI++) {
        
        std::uint8_t aSeed = ReadSeed(pSource, aIndex);
        std::uint8_t aX = static_cast<std::uint8_t>(aI ^ aSeed);
        
        std::uint8_t aY;

        
        if (aX == 0) {
            aY = 0;
        } else {
            int aLog = mLog[aX];
            aY = mExp[(255 - aLog) % 255];  // inverse
        }
        
        aBase[aI] = aY;
    }
    
    ApplyMatrix(aMatrix, aBase, pOutput);
    
    std::uint8_t aConstant = ReadSeed(pSource, aIndex + 511);
    
    for (int aI = 0; aI < 256; aI++) {
        pOutput[aI] ^= aConstant;
    }
}

int SBoxGenerator::ScoreCandidate(const std::uint8_t *pBox) {
    
    int aScore = 32000;
    
    int aDDT = mAnalyzer.ComputeDifferenceDistributionTableMax_256(pBox, 256);
    if (aDDT > 6) { aScore -= 20000; }
    else if (aDDT > 5) { aScore -= 10000; }
    else if (aDDT > 4) { aScore -= 2500; }
    
    int aWalsh = mAnalyzer.ComputeLinearCorrelationMax_256(pBox, 256);
    if (aWalsh > 46) { aScore -= 10000; }
    else if (aWalsh > 40) { aScore -= 5000; }
    else if (aWalsh > 34) { aScore -= 625; }
    
    double aSacAvg = mAnalyzer.ComputeSacAverageBias_256(pBox, 256);
    if (aSacAvg > 7.0) { aScore -= 4000; }
    else if (aSacAvg > 6.75) { aScore -= 2000; }
    else if (aSacAvg > 6.5) { aScore -= 250; }
    
    double aBicAvg = mAnalyzer.ComputeBicAverageBias_256(pBox, 256);
    if (aBicAvg > 7.5) { aScore -= 2000; }
    else if (aBicAvg > 7.25) { aScore -= 1000; }
    else if (aBicAvg > 7.0) { aScore -= 150; }
    
    return aScore;
}

void SBoxGenerator::Make(const std::uint8_t *pSource,
                         std::uint8_t *pSBoxA,
                         std::uint8_t *pSBoxB,
                         std::uint8_t *pSBoxC,
                         std::uint8_t *pSBoxD) {
    
    if (!mTablesBuilt) {
        BuildGFTables();
    }
    
    int aBestIndex[4] = { -1, -1, -1, -1 };
    int aBestScore[4] = { -1, -1, -1, -1 };
    
    for (int aIndex = 0; aIndex < 256; aIndex++) {
        std::uint8_t *aCandidate = mCandidates[aIndex];
        GenerateCandidate(pSource, aIndex, aCandidate);
        int aScore = ScoreCandidate(aCandidate);
        mScores[aIndex] = aScore;
        
        for (int aSlot = 0; aSlot < 4; aSlot++) {
            if (aScore > aBestScore[aSlot]) {
                
                for (int aShift = 3; aShift > aSlot; aShift--) {
                    aBestScore[aShift] = aBestScore[aShift - 1];
                    aBestIndex[aShift] = aBestIndex[aShift - 1];
                }
                
                aBestScore[aSlot] = aScore;
                aBestIndex[aSlot] = aIndex;
                break;
            }
        }
    }
    
    std::memcpy(pSBoxA, mCandidates[aBestIndex[0]], 256);
    std::memcpy(pSBoxB, mCandidates[aBestIndex[1]], 256);
    std::memcpy(pSBoxC, mCandidates[aBestIndex[2]], 256);
    std::memcpy(pSBoxD, mCandidates[aBestIndex[3]], 256);
}
