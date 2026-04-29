//
//  TwistCryptoGenerator.cpp
//  MeanMachine
//
//  Created by Dragon on 4/28/26.
//

#include "TwistCryptoGenerator.hpp"
#include <cstring>
#include <algorithm>
#include <inttypes.h>

TwistCryptoGenerator::TwistCryptoGenerator() {
    mExponents[0] = 11;
    mExponents[1] = 13;
    mExponents[2] = 19;
    mExponents[3] = 23;
    mExponents[4] = 254;
    mTablesBuilt = false;
}

void TwistCryptoGenerator::BuildGFTables() {
    
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

std::uint8_t TwistCryptoGenerator::ReadSeed(const std::uint8_t *pSource, int pIndex) {
    return pSource[pIndex & (S_BLOCK - 1)];
}

void TwistCryptoGenerator::BuildMatrix(const std::uint8_t *pSource,
                                int aIndex,
                                std::uint8_t *pMatrix) {
    
    for (int aRow = 0; aRow < 8; aRow++) {
        std::uint8_t aValue = ReadSeed(pSource, aIndex + aRow);
        aValue ^= static_cast<std::uint8_t>((aValue << 1U) | (aValue >> 7U));
        aValue |= (1 << aRow);
        pMatrix[aRow] = aValue;
    }
    for (int aIter = 0; aIter < 16; aIter++) {
        int aA = ReadSeed(pSource, aIndex + aIter) & 7;
        int aB = ReadSeed(pSource, aIndex + aIter + 37) & 7;
        
        if (aA != aB) {
            pMatrix[aA] ^= pMatrix[aB];
        }
    }
    for (int i = 0; i < 8; i++) {
        if (pMatrix[i] == 0) {
            pMatrix[i] = static_cast<std::uint8_t>(1 << i);
        }
    }
}

void TwistCryptoGenerator::ApplyMatrix(const std::uint8_t *pMatrix,
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

void TwistCryptoGenerator::GenerateCandidate(const std::uint8_t *pSource,
                                             const std::uint8_t *pFeedBack,
                                      int aIndex,
                                      std::uint8_t *pOutput) {
    
    std::uint8_t aMatrix[8];
    BuildMatrix(pSource, aIndex, aMatrix);
    
    std::uint8_t aBase[256];
    for (int aI = 0; aI < 256; aI++) {
        
        std::uint8_t aSeed = ReadSeed(pSource, aIndex);
        
        if (pFeedBack != NULL) {
            aSeed = pFeedBack[aSeed];
        }
        
        std::uint8_t aX = static_cast<std::uint8_t>(aI ^ aSeed);
        
        std::uint8_t aY;

        
        if (aX == 0) {
            aY = 0;
        } else {
            int aLog = mLog[aX];
            aY = mExp[(255 - aLog) % 255];
        }
        
        aBase[aI] = aY;
    }
    
    ApplyMatrix(aMatrix, aBase, pOutput);
    
    std::uint8_t aConstant = ReadSeed(pSource, aIndex + 511);
    
    for (int aI = 0; aI < 256; aI++) {
        pOutput[aI] ^= aConstant;
    }
}

int TwistCryptoGenerator::ScoreCandidate(const std::uint8_t *pBox) {
    
    int aScore = 110000;
    
    if (mAnalyzer.ComputeIsPermutation_256(pBox, 256) == false) { aScore -= 60000; }
    
    int aDDT = mAnalyzer.ComputeDifferenceDistributionTableMax_256(pBox, 256);
    if (aDDT > 6) { aScore -= 20000; }
    else if (aDDT > 5) { aScore -= 10000; }
    else if (aDDT > 4) { aScore -= 2500; }
    
    int aWalsh = mAnalyzer.ComputeLinearCorrelationMax_256(pBox, 256);
    if (aWalsh > 46) { aScore -= 10000; }
    else if (aWalsh > 40) { aScore -= 5000; }
    else if (aWalsh > 34) { aScore -= 625; }
    
    float aSacAvg = mAnalyzer.ComputeSacAverageBias_256(pBox, 256);
    if (aSacAvg > 7.0) { aScore -= 4000; }
    else if (aSacAvg > 6.75) { aScore -= 2000; }
    else if (aSacAvg > 6.5) { aScore -= 250; }
    else if (aSacAvg > 6.4) { aScore -= 250; }
    else if (aSacAvg > 6.3) { aScore -= 200; }
    else if (aSacAvg > 6.2) { aScore -= 150; }
    else if (aSacAvg > 6.1) { aScore -= 100; }
    else if (aSacAvg > 6.0) { aScore -= 50; }
    
    int aSacMax = mAnalyzer.ComputeSacMaxBias_256(pBox, 256);
    if (aSacMax > 22) { aScore -= 6000; }
    else if (aSacMax > 18) { aScore -= 3000; }
    else if (aSacMax > 16) { aScore -= 1000; }
    else if (aSacMax > 14) { aScore -= 10; }
    
    
    float aBicAvg = mAnalyzer.ComputeBicAverageBias_256(pBox, 256);
    if (aBicAvg > 7.5) { aScore -= 2000; }
    else if (aBicAvg > 7.25) { aScore -= 1000; }
    else if (aBicAvg > 7.0) { aScore -= 150; }
    else if (aBicAvg > 6.9) { aScore -= 125; }
    else if (aBicAvg > 6.7) { aScore -= 100; }
    else if (aBicAvg > 6.6) { aScore -= 75; }
    else if (aBicAvg > 6.5) { aScore -= 50; }
    else if (aBicAvg > 6.4) { aScore -= 25; }
    
    int aBicMax = mAnalyzer.ComputeBicMaxBias_256(pBox, 256);
    if (aBicMax > 22) { aScore -= 5000; }
    else if (aBicMax > 18) { aScore -= 2500; }
    else if (aBicMax > 16) { aScore -= 800; }
    else if (aBicMax > 14) { aScore -= 5; }
    
    return aScore;
}

void TwistCryptoGenerator::Make(const std::uint8_t *pSource,
                                     std::uint8_t *pSBoxA,
                                     std::uint8_t *pSBoxB,
                                     std::uint8_t *pSBoxC,
                                std::uint8_t *pSBoxD) {
    Make(pSource,
         pSBoxA,
         pSBoxB,
         pSBoxC,
         pSBoxD,
         NULL,
         NULL,
         NULL,
         NULL);
}

void TwistCryptoGenerator::Make(const std::uint8_t *pSource,
                                std::uint8_t *pSBoxA,
                                std::uint8_t *pSBoxB,
                                std::uint8_t *pSBoxC,
                                std::uint8_t *pSBoxD,
                                std::uint8_t *pExistingSBoxA,
                                std::uint8_t *pExistingSBoxB,
                                std::uint8_t *pExistingSBoxC,
                                std::uint8_t *pExistingSBoxD) {
    
    if (!mTablesBuilt) {
        BuildGFTables();
    }
    
    int aBestIndex[16];
    int aBestScore[16];
    
    for (int aI = 0; aI < 16; aI++) {
        aBestIndex[aI] = -1;
        aBestScore[aI] = -1;
    }
    
    for (int aIteration=0;aIteration<CRYPTO_GENERATOR_ITERATIONS;aIteration++) {
        
        
        
        for (int aIndex = 0; aIndex < 256; aIndex++) {
            
            
            
            int aGlobalIndex = aIteration * 256 + aIndex;
            std::uint8_t *aCandidate = mCandidates[aGlobalIndex];
            
            std::uint8_t *aFeedback = NULL;
            if (aIteration > 0) {
                aFeedback = mCandidates[aGlobalIndex - 256];
            }
            
            GenerateCandidate(pSource, aFeedback, aIndex, aCandidate);
            
            int aScore = ScoreCandidate(aCandidate);
            
            mScores[aGlobalIndex] = aScore;
            
            //TODO: If already exists, print out that at index xyz, already exists, and do not take this.
            
            for (int aSlot = 0; aSlot < 16; aSlot++) {
                if (aScore > aBestScore[aSlot]) {
                    for (int aShift = 15; aShift > aSlot; aShift--) {
                        aBestScore[aShift] = aBestScore[aShift - 1];
                        aBestIndex[aShift] = aBestIndex[aShift - 1];
                    }
                    
                    aBestScore[aSlot] = aScore;
                    aBestIndex[aSlot] = aGlobalIndex;
                    break;
                }
            }
        }
    }
    
    ProceedWithTopSixteen(aBestIndex,
                          pSBoxA,
                          pSBoxB,
                          pSBoxC,
                          pSBoxD,
                          pExistingSBoxA,
                          pExistingSBoxB,
                          pExistingSBoxC,
                          pExistingSBoxD);
    
}

void TwistCryptoGenerator::ProceedWithTopSixteen(int *aBestIndex,
                                                 std::uint8_t *pSBoxA,
                                                 std::uint8_t *pSBoxB,
                                                 std::uint8_t *pSBoxC,
                                                 std::uint8_t *pSBoxD,
                                                 std::uint8_t *pExistingSBoxA,
                                                 std::uint8_t *pExistingSBoxB,
                                                 std::uint8_t *pExistingSBoxC,
                                                 std::uint8_t *pExistingSBoxD) {
    
    const int aMaxCandidates = CRYPTO_GENERATOR_ITERATIONS * 256;
    
    int aSelectedIndex[4];
    int aSelectedCount = 0;
    bool aInvalid = false;
    
    for (int aI = 0; aI < 4; aI++) {
        int aIdx = aBestIndex[aI];
        if (aIdx < 0 || aIdx >= aMaxCandidates) {
            aInvalid = true;
            break;
        }
    }

    if (aInvalid) {
        printf("ERROR: Invalid best indices, zeroing S-box outputs\n");
        std::memset(pSBoxA, 0, 256);
        std::memset(pSBoxB, 0, 256);
        std::memset(pSBoxC, 0, 256);
        std::memset(pSBoxD, 0, 256);
        return;
    }
    
    for (int aI = 0; aI < 4; aI++) {
        aSelectedIndex[aI] = aBestIndex[aI];
    }
    
    std::uint8_t *aExistingList[4];
    int aExistingCount = 0;
    
    if (pExistingSBoxA != NULL) {
        aExistingList[aExistingCount++] = pExistingSBoxA;
    }
    
    if (pExistingSBoxB != NULL) {
        aExistingList[aExistingCount++] = pExistingSBoxB;
    }
    
    if (pExistingSBoxC != NULL) {
        aExistingList[aExistingCount++] = pExistingSBoxC;
    }
    
    if (pExistingSBoxD != NULL) {
        aExistingList[aExistingCount++] = pExistingSBoxD;
    }
    
    // Always take best
    aSelectedIndex[0] = aBestIndex[0];
    aSelectedCount = 1;
    
    while (aSelectedCount < 4) {
        
        int aBestCandidateIndex = -1;
        int aBestSimilarity = 2000000;
        
        for (int aCandidateSlot = 1; aCandidateSlot < 16; aCandidateSlot++) {
            
            int aCandidateIndex = aBestIndex[aCandidateSlot];
            std::uint8_t *aCandidate = mCandidates[aCandidateIndex];
            
            bool aIsDuplicate = false;
            
            for (int aCheckDupeIndex = 0; aCheckDupeIndex < aExistingCount; aCheckDupeIndex++) {
                if (mAnalyzer.Equal_256(aCandidate, aExistingList[aCheckDupeIndex])) {
                    aIsDuplicate = true;
                    break;
                }
            }
            
            // --- Reject duplicates vs already selected ---
            for (int aSel = 0; aSel < aSelectedCount; aSel++) {
                if (mAnalyzer.Equal_256(aCandidate, mCandidates[aSelectedIndex[aSel]])) {
                    aIsDuplicate = true;
                    break;
                }
            }
            
            if (aIsDuplicate) {
                continue;
            }
            
            int aWorstSimilarity = 0;
            
            for (int aSel = 0; aSel < aSelectedCount; aSel++) {
                
                std::uint8_t *aSelected = mCandidates[aSelectedIndex[aSel]];
                
                int aXor = mAnalyzer.ComputeXorDistributionMax_256(aSelected, aCandidate, 256);
                int aDS  = mAnalyzer.ComputeDifferentialSimilarityMax_256(aSelected, aCandidate, 256);
                
                int aSimilarityScore = (aXor * 256) + aDS;
                
                if (aSimilarityScore > aWorstSimilarity) {
                    aWorstSimilarity = aSimilarityScore;
                }
            }
            
            for (int aE = 0; aE < aExistingCount; aE++) {
                
                std::uint8_t *aExisting = aExistingList[aE];
                
                int aXor = mAnalyzer.ComputeXorDistributionMax_256(aExisting, aCandidate, 256);
                int aDS  = mAnalyzer.ComputeDifferentialSimilarityMax_256(aExisting, aCandidate, 256);
                
                int aSimilarityScore = (aXor * 256) + aDS;
                
                if (aSimilarityScore > aWorstSimilarity) {
                    aWorstSimilarity = aSimilarityScore;
                }
            }
            

            bool aTakeCandidate = false;

            // Case 1: strictly better similarity
            if (aWorstSimilarity < aBestSimilarity) {
                aTakeCandidate = true;
            } else if (aWorstSimilarity == aBestSimilarity) {
                
                // No current best yet
                if (aBestCandidateIndex == -1) {
                    aTakeCandidate = true;
                } else if (mScores[aCandidateIndex] > mScores[aBestCandidateIndex]) {
                    aTakeCandidate = true;
                }
            }

            if (aTakeCandidate) {
                aBestSimilarity = aWorstSimilarity;
                aBestCandidateIndex = aCandidateIndex;
            }

        }
        
        if (aBestCandidateIndex == -1) {
            printf("WARNING: No candidate found for slot %d\n", aSelectedCount);
            break;
        }
        
        aSelectedIndex[aSelectedCount] = aBestCandidateIndex;
        aSelectedCount++;
    }

    if (aSelectedCount > 0) {
        std::memcpy(pSBoxA, mCandidates[aSelectedIndex[0]], 256);
    }

    if (aSelectedCount > 1) {
        std::memcpy(pSBoxB, mCandidates[aSelectedIndex[1]], 256);
    }

    if (aSelectedCount > 2) {
        std::memcpy(pSBoxC, mCandidates[aSelectedIndex[2]], 256);
    }

    if (aSelectedCount > 3) {
        std::memcpy(pSBoxD, mCandidates[aSelectedIndex[3]], 256);
    }
    
    printf("\n==== S-BOX SCORE TABLE ====\n");
    
    for (int aIndex=0; aIndex<aMaxCandidates; aIndex++) {
        
        bool aIsTop16 = false;
        bool aIsSelected = false;
        
        // Check if in top 16
        for (int aI = 0; aI<16; aI++) {
            if (aBestIndex[aI] == aIndex) {
                aIsTop16 = true;
                break;
            }
        }
        
        // Check if in final selected set (top 4)
        for (int aI = 0; aI < 4; aI++) {
            if (aSelectedIndex[aI] == aIndex) {
                aIsSelected = true;
                break;
            }
        }
        
        if (aIsTop16) {

            // Print line
            printf("[%3d] score=%6d", aIndex, mScores[aIndex]);
            
            if (aIsSelected) {
                printf("  *");        // final chosen
            } else if (aIsTop16) {
                printf("  +");        // in top 16 pool
            }
            printf("\n");
            
            
            printf("\n================ FINAL TOP 16 S-BOXES ================\n");
            printf("Idx   Score    DDT  Walsh   SACavg  SACmax  BICavg  BICmax   Flag\n");
            printf("-----------------------------------------------------------------\n");

            if (aIsTop16) {
                
                std::uint8_t *aBox = mCandidates[aIndex];
                
                int aDDT   = mAnalyzer.ComputeDifferenceDistributionTableMax_256(aBox, 256);
                int aWalsh = mAnalyzer.ComputeLinearCorrelationMax_256(aBox, 256);
                
                float aSacAvg = mAnalyzer.ComputeSacAverageBias_256(aBox, 256);
                int   aSacMax = mAnalyzer.ComputeSacMaxBias_256(aBox, 256);
                
                float aBicAvg = mAnalyzer.ComputeBicAverageBias_256(aBox, 256);
                int   aBicMax = mAnalyzer.ComputeBicMaxBias_256(aBox, 256);
                
                char aFlag = ' ';
                if (aIsSelected) {
                    aFlag = '*';   // final chosen
                } else {
                    aFlag = '+';   // top 16 pool
                }
                
                printf("%3d | %6d | %3d | %5d | %6.2f | %6d | %6.2f | %6d |  %c\n",
                       aIndex,
                       mScores[aIndex],
                       aDDT,
                       aWalsh,
                       aSacAvg,
                       aSacMax,
                       aBicAvg,
                       aBicMax,
                       aFlag);
            }

            printf("=======================================================\n\n");
            
            
        }
        
        
    }
    
    printf("==== END TABLE ====\n\n");
    
    
    printf("\n=========== FINAL 4 VS TOP 16 SIMILARITY ===========\n");
    printf("SelIdx | WorstSim | WorstAgainstIdx\n");
    printf("---------------------------------------------------\n");

    for (int aSel = 0; aSel < 4; aSel++) {
        
        int aSelIndex = aSelectedIndex[aSel];
        std::uint8_t *aSelected = mCandidates[aSelIndex];
        
        int aWorstSimilarity = 0;
        int aWorstAgainstIndex = -1;
        
        for (int aPool = 0; aPool < 16; aPool++) {
            
            int aCandidateIndex = aBestIndex[aPool];
            
            // skip self
            if (aCandidateIndex == aSelIndex) {
                continue;
            }
            
            std::uint8_t *aCandidate = mCandidates[aCandidateIndex];
            
            int aXor = mAnalyzer.ComputeXorDistributionMax_256(aSelected, aCandidate, 256);
            int aDS  = mAnalyzer.ComputeDifferentialSimilarityMax_256(aSelected, aCandidate, 256);
            
            int aSimilarityScore = (aXor * 256) + aDS;
            
            if (aSimilarityScore > aWorstSimilarity) {
                aWorstSimilarity = aSimilarityScore;
                aWorstAgainstIndex = aCandidateIndex;
            }
        }
        
        printf("%6d | %9d | %16d\n",
               aSelIndex,
               aWorstSimilarity,
               aWorstAgainstIndex);
    }

    printf("===================================================\n\n");
    
}

void TwistCryptoGenerator::Salt(const std::uint8_t *pSource,
                                std::uint8_t *pSaltA,
                                std::uint8_t *pSaltB,
                                std::uint8_t *pSaltC,
                                std::uint8_t *pSaltD,
                                std::uint8_t *pSBoxA,
                                std::uint8_t *pSBoxB,
                                std::uint8_t *pSBoxC,
                                std::uint8_t *pSBoxD) {
    
    Salt(pSource,
         pSaltA,
         pSaltB,
         pSaltC,
         pSaltD,
         NULL,
         NULL,
         NULL,
         NULL,
         pSBoxA,
         pSBoxB,
         pSBoxC,
         pSBoxD,
         NULL,
         NULL,
         NULL,
         NULL);
}

void TwistCryptoGenerator::Salt(const std::uint8_t *pSource,
                                         std::uint8_t *pSaltA,
                                         std::uint8_t *pSaltB,
                                         std::uint8_t *pSaltC,
                                         std::uint8_t *pSaltD,
                                         std::uint8_t *pExistingSaltA,
                                         std::uint8_t *pExistingSaltB,
                                         std::uint8_t *pExistingSaltC,
                                         std::uint8_t *pExistingSaltD,
                                         std::uint8_t *pSBoxA,
                                         std::uint8_t *pSBoxB,
                                         std::uint8_t *pSBoxC,
                                         std::uint8_t *pSBoxD,
                                         std::uint8_t *pSBoxE,
                                         std::uint8_t *pSBoxF,
                                         std::uint8_t *pSBoxG,
                                std::uint8_t *pSBoxH) {
    
    for (int i = 0; i < CRYPTO_GENERATOR_SALT_COUNT; i++) {
        mSalts[i] = const_cast<std::uint8_t*>(pSource + (i * CRYPTO_GENERATOR_SALT_HOP));
    }
    
    for (int i = 0; i < CRYPTO_GENERATOR_SALT_COUNT; i++) {
        
        const std::uint8_t *aSalt = mSalts[i];
        
        int aBitBalance = mAnalyzer.ComputeSaltBitBalance_128(aSalt);
        int aByteSpread = mAnalyzer.ComputeSaltByteSpread_128(aSalt);
        int aAdjacency  = mAnalyzer.ComputeSaltAdjacencyPenalty_128(aSalt);
        int aXorDrift   = mAnalyzer.ComputeSaltXorDrift_128(aSalt);
        
        int aScore =
        (aBitBalance * 4) +
        (aByteSpread * 3) +
        (aXorDrift * 4) -
        (aAdjacency * 5);
        
        mSaltScores[i] = aScore;
        
        printf("salt at %d score is %d\n", i, aScore);
    }
    
    
    int aBestIndex[12];
    int aBestScore[12];
    
    for (int i = 0; i < 12; i++) {
        aBestIndex[i] = -1;
        aBestScore[i] = -1;
    }
    
    const std::uint8_t *aExistingSaltList[4];
    
    aExistingSaltList[0] = pExistingSaltA;
    aExistingSaltList[1] = pExistingSaltB;
    aExistingSaltList[2] = pExistingSaltC;
    aExistingSaltList[3] = pExistingSaltD;
    
    for (int i = 0; i < CRYPTO_GENERATOR_SALT_COUNT; i++) {
        
        int aScore = mSaltScores[i];
        
        const std::uint8_t *aCandidate = mSalts[i];
        
        // --- Reject overlap ---
        bool aTooClose = false;
        for (int aCheck = 0; aCheck < 12; aCheck++) {
            if (aBestIndex[aCheck] < 0) {
                continue;
            }
            
            int aDistance = std::abs(i - aBestIndex[aCheck]);
            if (aDistance < CRYPTO_GENERATOR_SALT_MIN_DISTANCE) {
                aTooClose = true;
                break;
            }
        }
        
        if (aTooClose) { continue; }
        
        // --- Reject duplicates vs already selected best list ---
        bool aIsDuplicate = false;
        for (int aCheck=0; aCheck<12; aCheck++) {
            if (aBestIndex[aCheck] < 0) { continue; }
            const std::uint8_t *aExisting = mSalts[aBestIndex[aCheck]];
            
            if (mAnalyzer.Equal_128(aCandidate, aExisting)) {
                aIsDuplicate = true;
                break;
            }
        }
        
        if (aIsDuplicate) { continue; }
        
        for (int aExistingSaltIndex = 0; aExistingSaltIndex < 4; aExistingSaltIndex++) {
            
            if (aExistingSaltList[aExistingSaltIndex] == NULL) { continue; }
            
            if (mAnalyzer.Equal_128(aCandidate, aExistingSaltList[aExistingSaltIndex])) {
                aIsDuplicate = true;
                break;
            }
        }
        
        if (aIsDuplicate) { continue; }
        
        // --- Insert into ranked list ---
        for (int aSlot=0; aSlot<12; aSlot++) {
            
            if (aScore > aBestScore[aSlot]) {
                
                for (int aShift = (12 - 1); aShift>aSlot; aShift--) {
                    aBestScore[aShift] = aBestScore[aShift - 1];
                    aBestIndex[aShift] = aBestIndex[aShift - 1];
                }
                
                aBestScore[aSlot] = aScore;
                aBestIndex[aSlot] = i;
                break;
            }
        }
    }
    
    printf("\n=========== TOP SALTS ===========\n");
    
    for (int i = 0; i < 12; i++) {
        
        int idx = aBestIndex[i];
        
        if (idx < 0) {
            printf("[%02d] idx=  -1 score=    -1  empty\n", i);
            continue;
        }
        
        const std::uint8_t *aSalt = mSalts[idx];
        
        printf("[%02d] idx=%4d score=%6d  ",
               i,
               idx,
               aBestScore[i]);
        
        // print first 8 bytes
        for (int b = 0; b < 8; b++) {
            printf("%02X ", aSalt[b]);
        }
        
        printf("\n");
    }
    
    printf("=================================\n\n");
    
    ProceedWithTopTwelve(aBestIndex,
                            pSaltA,
                            pSaltB,
                            pSaltC,
                            pSaltD,
                            pExistingSaltA,
                            pExistingSaltB,
                            pExistingSaltC,
                            pExistingSaltD,
                            pSBoxA,
                            pSBoxB,
                            pSBoxC,
                            pSBoxD,
                            pSBoxE,
                            pSBoxF,
                            pSBoxG,
                            pSBoxH);
    
}


void TwistCryptoGenerator::ProceedWithTopTwelve(int *aBestIndex,
                                                   std::uint8_t *pSaltA,
                                                   std::uint8_t *pSaltB,
                                                   std::uint8_t *pSaltC,
                                                   std::uint8_t *pSaltD,
                                                   std::uint8_t *pExistingSaltA,
                                                   std::uint8_t *pExistingSaltB,
                                                   std::uint8_t *pExistingSaltC,
                                                   std::uint8_t *pExistingSaltD,
                                                   std::uint8_t *pSBoxA,
                                                   std::uint8_t *pSBoxB,
                                                   std::uint8_t *pSBoxC,
                                                   std::uint8_t *pSBoxD,
                                                   std::uint8_t *pSBoxE,
                                                   std::uint8_t *pSBoxF,
                                                   std::uint8_t *pSBoxG,
                                                   std::uint8_t *pSBoxH) {
    
    const int aPoolCount = 12;
    
    int aSelectedIndex[4];
    int aSelectedCount = 0;
    
    const std::uint8_t *aExistingSaltList[4];
    aExistingSaltList[0] = pExistingSaltA;
    aExistingSaltList[1] = pExistingSaltB;
    aExistingSaltList[2] = pExistingSaltC;
    aExistingSaltList[3] = pExistingSaltD;
    
    while (aSelectedCount < 4) {
        
        int aBestCandidateIndex = -1;
        std::uint64_t aBestCandidateScore = -1;
        
        for (int aSlot = 0; aSlot < aPoolCount; aSlot++) {
            
            int aIndex = aBestIndex[aSlot];
            
            if (aIndex < 0) {
                continue;
            }
            
            const std::uint8_t *aCandidate = mSalts[aIndex];
            
            // --- Reject duplicate vs existing salts ---
            bool aIsDuplicate = false;
            
            for (int aExistingIndex = 0; aExistingIndex < 4; aExistingIndex++) {
                
                if (aExistingSaltList[aExistingIndex] == NULL) {
                    continue;
                }
                
                if (mAnalyzer.Equal_128(aCandidate, aExistingSaltList[aExistingIndex])) {
                    aIsDuplicate = true;
                    break;
                }
            }
            
            if (aIsDuplicate) {
                continue;
            }
            
            // --- Reject duplicate vs already selected ---
            for (int aSel = 0; aSel < aSelectedCount; aSel++) {
                
                const std::uint8_t *aSelectedSalt = mSalts[aSelectedIndex[aSel]];
                
                if (mAnalyzer.Equal_128(aCandidate, aSelectedSalt)) {
                    aIsDuplicate = true;
                    break;
                }
            }
            
            if (aIsDuplicate) {
                continue;
            }
            
            
            std::uint64_t aCandidateScore =
                mAnalyzer.ComputeSaltComprehensiveAgainstSBoxFamilt(
                    aCandidate,
                    pSBoxA,
                    pSBoxB,
                    pSBoxC,
                    pSBoxD,
                    pSBoxE,
                    pSBoxF,
                    pSBoxG,
                    pSBoxH
                );

            bool aTakeCandidate = false;

            // Case 1: no current best yet
            if (aBestCandidateIndex == -1) {
                aTakeCandidate = true;
            }
            // Case 2: better score
            else if (aCandidateScore > aBestCandidateScore) {
                aTakeCandidate = true;
            }

            if (aTakeCandidate) {
                aBestCandidateScore = aCandidateScore;
                aBestCandidateIndex = aIndex;
            }
        }
        
        if (aBestCandidateIndex < 0) {
            printf("WARNING: could not find enough valid salts\n");
            break;
        }
        
        printf("Selected salt index %d with score %" PRIu64 "\n",
               aBestCandidateIndex,
               aBestCandidateScore);
        
        aSelectedIndex[aSelectedCount] = aBestCandidateIndex;
        aSelectedCount++;
    }
    
    // --- Copy out ---
    if (aSelectedCount > 0) std::memcpy(pSaltA, mSalts[aSelectedIndex[0]], 128);
    if (aSelectedCount > 1) std::memcpy(pSaltB, mSalts[aSelectedIndex[1]], 128);
    if (aSelectedCount > 2) std::memcpy(pSaltC, mSalts[aSelectedIndex[2]], 128);
    if (aSelectedCount > 3) std::memcpy(pSaltD, mSalts[aSelectedIndex[3]], 128);
    
    
    printf("\n====== TOP 12 SALT FULL SCORES ======\n");

    for (int aSlot = 0; aSlot < 12; aSlot++) {
        
        int aIndex = aBestIndex[aSlot];
        
        if (aIndex < 0) {
            printf("[%02d] idx=  -1  empty\n", aSlot);
            continue;
        }
        
        const std::uint8_t *aSalt = mSalts[aIndex];
        
        std::uint64_t aFullScore =
            mAnalyzer.ComputeSaltComprehensiveAgainstSBoxFamilt(
                aSalt,
                pSBoxA,
                pSBoxB,
                pSBoxC,
                pSBoxD,
                pSBoxE,
                pSBoxF,
                pSBoxG,
                pSBoxH
            );
        
        printf("[%02d] idx=%4d  base=%6d  full=%12llu  ",
               aSlot,
               aIndex,
               mSaltScores[aIndex],
               aFullScore);
        
        // print first 8 bytes
        for (int b = 0; b < 8; b++) {
            printf("%02X ", aSalt[b]);
        }
        
        printf("\n");
    }

    printf("=====================================\n\n");
    
}
