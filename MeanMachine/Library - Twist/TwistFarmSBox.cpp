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
