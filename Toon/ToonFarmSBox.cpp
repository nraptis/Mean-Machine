//
//  ToonFarmSBox.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/5/26.
//

#include "ToonFarmSBox.hpp"
#include <cstring>
#include <algorithm>

ToonFarmSBox::ToonFarmSBox() {
    mExponents[0] = 11;
    mExponents[1] = 13;
    mExponents[2] = 19;
    mExponents[3] = 23;
    mExponents[4] = 254;
    mTablesBuilt = false;
    
}

std::uint8_t ToonFarmSBox::ApplyMatrix8(const std::uint8_t *pMatrix,
                                        std::uint8_t pValue) {
    std::uint8_t aOut = 0;
    for (int aRow = 0; aRow < 8; aRow++) {
        std::uint8_t aMask = static_cast<std::uint8_t>(pMatrix[aRow] & pValue);
        std::uint8_t aParity = static_cast<std::uint8_t>(__builtin_popcount(aMask) & 1U);
        aOut |= static_cast<std::uint8_t>(aParity << aRow);
    }
    return aOut;
}

void ToonFarmSBox::Derive(const std::uint8_t *pSource,
                           std::uint8_t *pSBoxA,
                           std::uint8_t *pSBoxB,
                           std::uint8_t *pSBoxC,
                           std::uint8_t *pSBoxD,
                           std::uint8_t *pSBoxE,
                           std::uint8_t *pSBoxF,
                           std::uint8_t *pSBoxG,
                           std::uint8_t *pSBoxH) {
    
    if (mTablesBuilt == false) {
        int aX = 1;
        for (int i=0; i<255; i++) {
            mExp[i] = aX;
            mExp[i + 255] = aX;
            mLog[aX] = i;
            int aNext = aX ^ (aX << 1);
            if (aNext & 0x100) { aNext ^= 0x11B; }
            aX = aNext;
        }
        mLog[0] = 0;
        mTablesBuilt = true;
    }

    int aFillListSize = 0;
    int aFillListCount = 0;
    if (pSBoxA != nullptr) { mFillSBox[aFillListSize++] = pSBoxA; }
    if (pSBoxB != nullptr) { mFillSBox[aFillListSize++] = pSBoxB; }
    if (pSBoxC != nullptr) { mFillSBox[aFillListSize++] = pSBoxC; }
    if (pSBoxD != nullptr) { mFillSBox[aFillListSize++] = pSBoxD; }
    if (pSBoxE != nullptr) { mFillSBox[aFillListSize++] = pSBoxE; }
    if (pSBoxF != nullptr) { mFillSBox[aFillListSize++] = pSBoxF; }
    if (pSBoxG != nullptr) { mFillSBox[aFillListSize++] = pSBoxG; }
    if (pSBoxH != nullptr) { mFillSBox[aFillListSize++] = pSBoxH; }
    
    std::uint8_t *aCandidateSBoxFlatReference = mCandidateSBoxFlat;
    for (int i=0; i<SBOX_CANDIDATE_COUNT; i++) {
        mCandidateSBox[i] = aCandidateSBoxFlatReference;
        aCandidateSBoxFlatReference = &(aCandidateSBoxFlatReference[S_SBOX]);
    }

    memcpy(mCandidateSBoxFlat, pSource, S_BLOCK);

    int aPermutationCount = 0;
    for (int aLoop = 0; aLoop < SBOX_CANDIDATE_COUNT; aLoop++) {

        std::uint8_t *aSBox = mCandidateSBox[aPermutationCount];

        const int aStart = aLoop * 18;

        for (int i = 0; i < 8; i++) {
            mInputMatrix[i] = pSource[aStart + i];
            mInputMatrix[i] |= static_cast<std::uint8_t>(1U << i);
        }

        for (int i = 0; i < 8; i++) {
            mOutputMatrix[i] = pSource[aStart + 8 + i];
            mOutputMatrix[i] |= static_cast<std::uint8_t>(1U << i);
        }

        const std::uint8_t aSeed = pSource[aStart + 16];
        const std::uint8_t aConstant = pSource[aStart + 17];

        for (int i = 0; i < 256; i++) {
            std::uint8_t aX = static_cast<std::uint8_t>(i);

            aX = ApplyMatrix8(mInputMatrix, aX);
            aX = static_cast<std::uint8_t>(aX ^ aSeed);

            std::uint8_t aY;
            if (aX == 0) {
                aY = 0;
            } else {
                int aLog = mLog[aX];
                aY = mExp[(255 - aLog) % 255];
            }

            std::uint8_t aOut = ApplyMatrix8(mOutputMatrix, aY);
            aOut = static_cast<std::uint8_t>(aOut ^ aConstant);

            aSBox[i] = aOut;
        }
        
        if (mAnalyzer.ComputeIsPermutation_SBox(aSBox)) {
            aPermutationCount++;
        }
    }

    int aPow1 = 0;
    int aPow2 = 0;
    int aTake2 = 0;
    while (aPermutationCount < SBOX_CANDIDATE_MINIMUM_PERMUTATION_COUNT) {
        for (int i=0;i<8;i++) {
            mInputMatrix[i] = (1 << aPow1) | (1 << i);
        }
        for (int i=0;i<8;i++) {
            mOutputMatrix[i] = (1 << aPow2) | (1 << i);
        }
        std::uint8_t *aSBox = mCandidateSBox[aPermutationCount];
        const std::uint8_t aSeed = aPow1 ^ aPermutationCount;
        const std::uint8_t aConstant = aPow2 ^ aPermutationCount;
        for (int i = 0; i < 256; i++) {
            std::uint8_t aX = static_cast<std::uint8_t>(i);
            aX = ApplyMatrix8(mInputMatrix, aX);
            aX = static_cast<std::uint8_t>(aX ^ aSeed);
            std::uint8_t aY;
            if (aX == 0) {
                aY = 0;
            } else {
                int aLog = mLog[aX];
                aY = mExp[(255 - aLog) % 255];
            }
            std::uint8_t aOut = ApplyMatrix8(mOutputMatrix, aY);
            aOut = static_cast<std::uint8_t>(aOut ^ aConstant);
            aSBox[i] = aOut;
        }

        aTake2++;
        aPow1++;
        if (aPow1 >= 8) {
            aPow2++;
            aPow1 = 0;
        }
        aPermutationCount++;
    }
    
    for (int i=0; i<aPermutationCount; i++) {
        mCandidateScore[i] = mAnalyzer.ComputeCombinedSBoxGrade(mCandidateSBox[i]);
        printf("candidate score [%d] = %d\n", i, mCandidateScore[i]);
    }
    
    
    for (int i = 0; i < aPermutationCount - 1; i++) {
        int aBestIndex = i;
        
        for (int j = i + 1; j < aPermutationCount; j++) {
            if (mCandidateScore[j] > mCandidateScore[aBestIndex]) {
                aBestIndex = j;
            }
        }
        
        if (aBestIndex != i) {
            std::swap(mCandidateScore[i], mCandidateScore[aBestIndex]);
            std::swap(mCandidateSBox[i], mCandidateSBox[aBestIndex]);
        }
    }
    
    printf("\n========================================\n");
    printf("ToonFarmSBox::Derive sorted candidate scores\n");
    printf("SBOX_CANDIDATE_COUNT = %d\n", SBOX_CANDIDATE_COUNT);
    
    printf("========================================\n");
    printf("rank,grade,bit_balance,byte_spread,xor_drift,adjacency_penalty\n");
    
    for (int i = 0; i < aPermutationCount; i++) {
        const std::uint8_t *aCandidate = mCandidateSBox[i];
        
        const int aScore = mAnalyzer.ComputeCombinedSBoxGrade(aCandidate);
        
        printf("%d | %d | %d\n",
               i,
               mCandidateScore[i],
               aScore);
    }
    
    std::memset(mCandidateClaimed, 0, sizeof(mCandidateClaimed));

    std::memcpy(mFillSBox[0], mCandidateSBox[0], S_SBOX);
    mCandidateClaimed[0] = 1;
    aFillListCount = 1;
    
    
    const int aBattleCount = std::min<int>(24, SBOX_CANDIDATE_COUNT);
    
    while (aFillListCount < aFillListSize) {
        int aBestIndex = -1;
        int aBestMaxSameCount = std::numeric_limits<int>::max();

        for (int i=0; i<aBattleCount; i++) {
            if (mCandidateClaimed[i] != 0) {
                continue;
            }

            int aMaxSameCount = 0;

            for (int j = 0; j < aFillListCount; j++) {
                int aSameCount = mAnalyzer.ComputeSameFunctionCount_SBox(mCandidateSBox[i], mFillSBox[j]);
                aMaxSameCount = std::max(aMaxSameCount, aSameCount);
            }

            if (aMaxSameCount < aBestMaxSameCount) {
                aBestMaxSameCount = aMaxSameCount;
                aBestIndex = i;
            }
        }

        if (aBestIndex == -1) {
            printf("fatal: we did not have enough s-boxes?\n");
            break;
        }

        std::memcpy(mFillSBox[aFillListCount],
                    mCandidateSBox[aBestIndex],
                    S_SBOX);

        mCandidateClaimed[aBestIndex] = 1;

        printf("we took box rank %d grade %d max_same %d\n",
               aBestIndex,
               mCandidateScore[aBestIndex],
               aBestMaxSameCount);

        aFillListCount++;
    }
    
    
}

void ToonFarmSBox::Derive(const std::uint8_t *pSource,
                          ToonDomainSBoxSet *pRoundMaterial) {
    if (pRoundMaterial == nullptr) {
        return;
    }
    Derive(pSource,
           pRoundMaterial->mSBoxA,
           pRoundMaterial->mSBoxB,
           pRoundMaterial->mSBoxC,
           pRoundMaterial->mSBoxD,
           pRoundMaterial->mSBoxE,
           pRoundMaterial->mSBoxF,
           pRoundMaterial->mSBoxG,
           pRoundMaterial->mSBoxH);
}

