//
//  TwistFarmSBox.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/5/26.
//

#include "TwistFarmSBox.hpp"
#include <cstring>
#include <algorithm>

TwistFarmSBox::TwistFarmSBox() {
    mExponents[0] = 11;
    mExponents[1] = 13;
    mExponents[2] = 19;
    mExponents[3] = 23;
    mExponents[4] = 254;
    mTablesBuilt = false;
    mCount = 0;
}

void TwistFarmSBox::Reset() {
    mCount = 0;
}

std::uint8_t TwistFarmSBox::ApplyMatrix8(const std::uint8_t *pMatrix,
                                        std::uint8_t pValue) {
    std::uint8_t aOut = 0;
    for (int aRow = 0; aRow < 8; aRow++) {
        std::uint8_t aMask = static_cast<std::uint8_t>(pMatrix[aRow] & pValue);
        std::uint8_t aParity = static_cast<std::uint8_t>(__builtin_popcount(aMask) & 1U);
        aOut |= static_cast<std::uint8_t>(aParity << aRow);
    }
    return aOut;
}

void TwistFarmSBox::Derive(const std::uint8_t *pSource,
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
    printf("TwistFarmSBox::Derive sorted candidate scores\n");
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

bool TwistFarmSBox::TillBytes(const std::uint8_t *pSource,
                              const std::uint8_t *pSnow,
                              std::uint64_t pTargetCount) {
    
    
    
    if (mTablesBuilt == false) {
        int aX = 1;
        for (int i=0; i<255; i++) {
            mExp[i] = aX;
            mExp[i + 255] = aX;
            mLog[aX] = i;
            int aNext = aX ^ (aX << 1);
            if (aNext & 0x100) {
                aNext ^= 0x11B;
            }
            aX = aNext;
        }
        
        mLog[0] = 0;
        mTablesBuilt = true;
    }
    
    static constexpr int kBytesPerCandidate = 53;
    static constexpr int kSourceBytes = 8192;
    static constexpr int kCandidateCount = 512;
    
    
    
    int aKeepCount = 0;
    
    int aRejectNotPermutation = 0;
    int aRejectDDT = 0;
    int aRejectWalsh = 0;
    int aRejectNoConstantCycleGate = 0;
    int aRejectComponentDegree = 0;
    int aRejectSacAverage = 0;
    int aRejectSacMax = 0;
    int aRejectBicAverage = 0;
    int aRejectBicMax = 0;
    
    auto PrintSummary = [&]() {
        printf("SBox Farm Summary:\n");
        printf("  keep: %d\n", aKeepCount);
        printf("  reject not permutation: %d\n", aRejectNotPermutation);
        printf("  reject DDT: %d\n", aRejectDDT);
        printf("  reject Walsh: %d\n", aRejectWalsh);
        printf("  reject no constant passed cycle gate: %d\n", aRejectNoConstantCycleGate);
        printf("  reject component degree: %d\n", aRejectComponentDegree);
        printf("  reject SAC average: %d\n", aRejectSacAverage);
        printf("  reject SAC max: %d\n", aRejectSacMax);
        printf("  reject BIC average: %d\n", aRejectBicAverage);
        printf("  reject BIC max: %d\n", aRejectBicMax);
    };
    
    for (int aBoxIndex=0; aBoxIndex<kCandidateCount; aBoxIndex++) {
        
        // Security Issue:
        // The destructuring of this s-box can reveal
        // a portion of the stream, so we need to ensure
        // that we do not leak a contiguous sequence.
        //
        int aObscureIndex = 0;
        int aSeedSlot = (aBoxIndex * 3251) & S_BLOCK1;
        int aSnowSlot = (aBoxIndex * 4933) & S_BLOCK1;
        while (aObscureIndex < 53) {
            int aOldSnowSlot = aSnowSlot;
            int aOldSeedSlot = aSeedSlot;
            aSnowSlot = (aOldSeedSlot * 1427 + pSource[aOldSnowSlot] + aBoxIndex) & S_BLOCK1;
            aSeedSlot = (aOldSnowSlot * 5741 + pSnow[aOldSeedSlot] + aBoxIndex) & S_BLOCK1;
            mObscure[aObscureIndex] = static_cast<std::uint8_t>(pSource[aSeedSlot] ^ pSnow[aSnowSlot]);
            aObscureIndex++;
        }
        
        std::uint8_t *aSBox = mSBox[mCount];

        //
        // Build matrix from mObscure[0..52]
        //
        for (int aRow = 0; aRow < 8; aRow++) {
            std::uint8_t aValue = mObscure[aRow];
            aValue ^= static_cast<std::uint8_t>((aValue << 1U) | (aValue >> 7U));
            aValue |= static_cast<std::uint8_t>(1U << aRow);
            mMatrix[aRow] = aValue;
        }

        for (int aIter = 0; aIter < 16; aIter++) {
            int aA = mObscure[aIter] & 7;
            int aB = mObscure[aIter + 37] & 7;
            if (aA != aB) {
                mMatrix[aA] ^= mMatrix[aB];
            }
        }

        for (int i = 0; i < 8; i++) {
            if (mMatrix[i] == 0) {
                mMatrix[i] = static_cast<std::uint8_t>(1U << i);
            }
        }

        //
        // Generate inverse-based candidate, then apply matrix directly.
        //
        
        const std::uint8_t aSeed = mObscure[0];
        for (int i=0; i<256; i++) {
            std::uint8_t aX = static_cast<std::uint8_t>(i ^ aSeed);
            std::uint8_t aY;

            if (aX == 0) {
                aY = 0;
            } else {
                int aLog = mLog[aX];
                aY = mExp[(255 - aLog) % 255];
            }

            std::uint8_t aOut = 0;
            for (int aBit = 0; aBit < 8; aBit++) {
                std::uint8_t aMask = static_cast<std::uint8_t>(mMatrix[aBit] & aY);
                std::uint8_t aParity = static_cast<std::uint8_t>(__builtin_popcount(aMask) & 1U);
                aOut |= static_cast<std::uint8_t>(aParity << aBit);
            }

            aSBox[i] = aOut;
        }
        
        if (mAnalyzer.ComputeIsPermutation_SBox(aSBox) == false) {
            aRejectNotPermutation++;
            continue;
        }
        
        /*
        int aDDT = mAnalyzer.ComputeDDTMax_SBox(aSBox);
        if (aDDT != 4) {
            aRejectDDT++;
            continue;
        }
        
        int aWalsh = mAnalyzer.ComputeWalsh_SBox(aSBox);
        if (aWalsh != 32) {
            aRejectWalsh++;
            continue;
        }
        */
        
        bool aFoundConstant = false;

        memcpy(mSBoxBase, aSBox, 256);
        for (int aConstantTry = 0; aConstantTry < 256; aConstantTry++) {

            std::uint8_t aConstant =
                static_cast<std::uint8_t>(aConstantTry + mObscure[52]);

            for (int i = 0; i < 256; i++) {
                aSBox[i] = static_cast<std::uint8_t>(mSBoxBase[i] ^ aConstant);
            }

            int aCycle0 = mAnalyzer.ComputeMinimumCycleRotL0AfterGate_SBox(aSBox);
            if (aCycle0 < 2) {
                continue;
            }

            int aCycle1 = mAnalyzer.ComputeMinimumCycleRotL1AfterGate_SBox(aSBox);
            if (aCycle1 < 2) {
                continue;
            }

            int aCycle3 = mAnalyzer.ComputeMinimumCycleRotL3AfterGate_SBox(aSBox);
            if (aCycle3 < 2) {
                continue;
            }

            int aCycle5 = mAnalyzer.ComputeMinimumCycleRotL5AfterGate_SBox(aSBox);
            if (aCycle5 < 2) {
                continue;
            }

            int aCycle7 = mAnalyzer.ComputeMinimumCycleRotL7AfterGate_SBox(aSBox);
            if (aCycle7 < 2) {
                continue;
            }

            aFoundConstant = true;
            break;
        }

        if (!aFoundConstant) {
            aRejectNoConstantCycleGate++;
            continue;
        }
        
        /*
        TwistCryptoMinMaxResponse aComponentDegrees = mAnalyzer.ComputeComponentAlgebraicDegrees_SBox(aSBox);
        if ((aComponentDegrees.mMin != 7) || (aComponentDegrees.mMax != 7)) {
            aRejectComponentDegree++;
            continue;
        }
        */
        
        TwistCryptoMaxAverageResponse aSacBias = mAnalyzer.ComputeSacBias_SBox(aSBox);
        if (aSacBias.mAverage >= 7.0f) {
            aRejectSacAverage++;
            continue;
        }
        
        if (aSacBias.mMax > 18) {
            aRejectSacMax++;
            continue;
        }
        
        TwistCryptoMaxAverageResponse aBicBias = mAnalyzer.ComputeBicBias_SBox(aSBox);
        if (aBicBias.mAverage >= 7.0f) {
            aRejectBicAverage++;
            continue;
        }
        
        if (aBicBias.mMax > 18) {
            aRejectBicMax++;
            continue;
        }
        
        aKeepCount++;
        mCount++;
        
        if (mCount >= pTargetCount) {
            PrintSummary();
            return true;
        }
    }

    PrintSummary();
    return false;
}
