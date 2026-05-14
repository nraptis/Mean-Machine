//
//  TwistFarmSalt.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/6/26.
//

#include "TwistFarmSalt.hpp"

TwistFarmSalt::TwistFarmSalt() {
    mCount = 0ULL;
    std::memset(mSalt, 0, sizeof(mSalt));
    std::memset(mScore, 0, sizeof(mScore));
    //std::memset(mCandidate, 0, sizeof(mCandidate));
    
}

void TwistFarmSalt::Derive(const std::uint8_t *pSource,
                           std::uint64_t *pSaltA,
                           std::uint64_t *pSaltB,
                           std::uint64_t *pSaltC,
                           std::uint64_t *pSaltD,
                           std::uint64_t *pSaltE,
                           std::uint64_t *pSaltF) {
    
    static_assert((SALT_CANDIDATE_COUNT * S_SALT * sizeof(std::uint64_t)) == S_BLOCK,
                  "SALT_CANDIDATE_COUNT must exactly cover S_BLOCK.");
    
    int aFillListSize = 0;
    int aFillListCount = 0;
    if (pSaltA != nullptr) { mFillSalt[aFillListSize++] = pSaltA; }
    if (pSaltB != nullptr) { mFillSalt[aFillListSize++] = pSaltB; }
    if (pSaltC != nullptr) { mFillSalt[aFillListSize++] = pSaltC; }
    if (pSaltD != nullptr) { mFillSalt[aFillListSize++] = pSaltD; }
    if (pSaltE != nullptr) { mFillSalt[aFillListSize++] = pSaltE; }
    if (pSaltF != nullptr) { mFillSalt[aFillListSize++] = pSaltF; }
    
    std::uint64_t *aCandidateSaltFlatReference = mCandidateSaltFlat;
    for (int i=0; i<SALT_CANDIDATE_COUNT; i++) {
        mCandidateSalt[i] = aCandidateSaltFlatReference;
        aCandidateSaltFlatReference = &(aCandidateSaltFlatReference[S_SALT]);
    }
    
    memcpy(mCandidateSaltFlat, pSource, S_BLOCK);
    
    // Score every candidate.
    for (int i = 0; i < SALT_CANDIDATE_COUNT; i++) {
        const std::uint64_t *aCandidate = mCandidateSalt[i];
        mCandidateScore[i] = mAnalyzer.ComputeCombinedSaltGrade(aCandidate);
    }
    
    for (int i = 0; i < SALT_CANDIDATE_COUNT - 1; i++) {
        int aBestIndex = i;
        
        for (int j = i + 1; j < SALT_CANDIDATE_COUNT; j++) {
            if (mCandidateScore[j] > mCandidateScore[aBestIndex]) {
                aBestIndex = j;
            }
        }
        
        if (aBestIndex != i) {
            std::swap(mCandidateScore[i], mCandidateScore[aBestIndex]);
            std::swap(mCandidateSalt[i], mCandidateSalt[aBestIndex]);
        }
    }
    
    printf("\n========================================\n");
    printf("TwistFarmSalt::Derive sorted candidate scores\n");
    printf("SALT_CANDIDATE_COUNT = %d\n", SALT_CANDIDATE_COUNT);
    
    printf("========================================\n");
    printf("rank,grade,bit_balance,byte_spread,xor_drift,adjacency_penalty\n");
    
    for (int i = 0; i < SALT_CANDIDATE_COUNT; i++) {
        const std::uint64_t *aCandidate = mCandidateSalt[i];
        
        const int aScore = mAnalyzer.ComputeCombinedSaltGrade(aCandidate);
        
        
        printf("%d | %d | %d\n",
               i,
               mCandidateScore[i],
               aScore);
    }
    
    std::memset(mCandidateClaimed, 0, sizeof(mCandidateClaimed));

    std::memcpy(mFillSalt[0], mCandidateSalt[0], S_SALT * sizeof(std::uint64_t));
    mCandidateClaimed[0] = 1;
    aFillListCount = 1;
    
    const int aBattleCount = std::min<int>(24, SALT_CANDIDATE_COUNT);
    while (aFillListCount<aFillListSize) {
        int aBestIndex = -1;
        int aBestMinHammingDistance = -1;
        
        for (int i=0; i<aBattleCount; i++) {
            
            if (mCandidateClaimed[i] != 0) {
                continue;
            }
            
            int aMinHammingDistance = std::numeric_limits<int>::max();
            
            for (int j=0; j<aFillListCount; j++) {
                const int aDistance =
                    mAnalyzer.ComputeSaltHammingDistance_Salt(mFillSalt[j],
                                                              mCandidateSalt[i]);
                
                if (aDistance < aMinHammingDistance) {
                    aMinHammingDistance = aDistance;
                }
            }
            
            if (aMinHammingDistance > aBestMinHammingDistance) {
                aBestMinHammingDistance = aMinHammingDistance;
                aBestIndex = i;
            }
        }
        
        if (aBestIndex == -1) {
            printf("fatal: we did not have enough salts?\n");
            break;
        }
        
        std::memcpy(mFillSalt[aFillListCount],
                    mCandidateSalt[aBestIndex],
                    S_SALT * sizeof(std::uint64_t));
        
        mCandidateClaimed[aBestIndex] = 1;
        
        printf("we took salt rank %d grade %d min_hamming %d\n",
               aBestIndex,
               mCandidateScore[aBestIndex],
               aBestMinHammingDistance);
        
        aFillListCount++;
    }
}

void TwistFarmSalt::Reset() {
    mCount = 0ULL;
}

    // We try to get to pTargetCount passing salt grading.
    // if we failed, we return false.
    bool TwistFarmSalt::TillBytes(const std::uint8_t *pSource,
                                  const std::uint8_t *pSnow,
                                  std::uint64_t pTargetCount) {
        
        /*
        if ((pSource == nullptr) || (pSnow == nullptr)) {
            return false;
        }
        if (pTargetCount == 0ULL) {
            return true;
        }
        
        if (pTargetCount > kCapacity) {
            pTargetCount = kCapacity;
        }
        
        static constexpr int kCandidateCountPerPass = 512;
        static constexpr int kMaxAcceptPerPass = 12;
        
        int aAcceptedThisPass = 0;
        bool aHaveFallback = false;
        std::uint64_t aFallbackSalt[S_SALT];
        std::uint64_t aFallbackScore = 0ULL;
        
        for (int aCandidateIndex = 0; aCandidateIndex < kCandidateCountPerPass; ++aCandidateIndex) {
            BuildCandidate(pSource, pSnow, static_cast<std::uint32_t>(aCandidateIndex));
            
            const int aBitBalance = mAnalyzer.ComputeBitBalance_Salt(mCandidate);
            const int aByteSpread = mAnalyzer.ComputeByteSpread_Salt(mCandidate);
            const int aXorDrift = mAnalyzer.ComputeXorDrift_Salt(mCandidate);
            const int aAdjacencyPenalty = mAnalyzer.ComputeAdjacencyPenalty_Salt(mCandidate);
            const int aMinDistance = ComputeNearestDistance(mCandidate);
            
            std::int64_t aScoreSigned =
            static_cast<std::int64_t>(aBitBalance * 8 + aByteSpread * 16 + aXorDrift * 4)
            - static_cast<std::int64_t>(aAdjacencyPenalty * 6)
            + static_cast<std::int64_t>(std::max(aMinDistance, 0) * 2);
            if (aScoreSigned < 0) {
                aScoreSigned = 0;
            }
            const std::uint64_t aScore = static_cast<std::uint64_t>(aScoreSigned);
            
            if ((!aHaveFallback) || (aScore > aFallbackScore)) {
                std::memcpy(aFallbackSalt, mCandidate, sizeof(aFallbackSalt));
                aFallbackScore = aScore;
                aHaveFallback = true;
            }
            
            const bool aPassThreshold =
            (aBitBalance >= 640) &&
            (aByteSpread >= 96) &&
            (aXorDrift >= 704) &&
            (aAdjacencyPenalty <= 320) &&
            (aMinDistance >= 640);
            if (!aPassThreshold) {
                continue;
            }
            
            if (!AppendAccepted(mCandidate, aScore)) {
                break;
            }
            
            ++aAcceptedThisPass;
            if ((mCount >= pTargetCount) || (aAcceptedThisPass >= kMaxAcceptPerPass)) {
                break;
            }
        }
        
        if ((aAcceptedThisPass == 0) && aHaveFallback && (mCount < pTargetCount)) {
            (void)AppendAccepted(aFallbackSalt, aFallbackScore);
        }
        
        return (mCount >= pTargetCount);
        */
        return 1;
    }


void TwistFarmSalt::BuildCandidate(const std::uint8_t *pSource,
                        const std::uint8_t *pSnow,
                                   std::uint32_t pCandidateIndex) {
    /*
    std::uint32_t aSourceSlot = (pCandidateIndex * 3251U) & S_BLOCK1;
    std::uint32_t aSnowSlot = (pCandidateIndex * 4933U) & S_BLOCK1;
    std::uint64_t aCarry = 0x9E3779B97F4A7C15ULL ^
    (static_cast<std::uint64_t>(pCandidateIndex) * 0xD6E8FEB86659FD93ULL);
    
    for (std::uint32_t aWordIndex = 0U; aWordIndex < S_SALT; ++aWordIndex) {
        std::uint64_t aWord = 0ULL;
        
        for (std::uint32_t aByteIndex = 0U; aByteIndex < 8U; ++aByteIndex) {
            const std::uint8_t aSourceByte = pSource[aSourceSlot];
            const std::uint8_t aSnowByte = pSnow[aSnowSlot];
            const std::uint8_t aMixedByte = static_cast<std::uint8_t>(
                                                                      aSourceByte ^
                                                                      aSnowByte ^
                                                                      static_cast<std::uint8_t>((pCandidateIndex + aWordIndex + aByteIndex) * 17U));
            
            aWord |= (static_cast<std::uint64_t>(aMixedByte) << (aByteIndex * 8U));
            
            aSourceSlot = (aSourceSlot * 1427U + aSnowByte + aWordIndex + aByteIndex + pCandidateIndex) & S_BLOCK1;
            aSnowSlot = (aSnowSlot * 5741U + aSourceByte + aWordIndex + aByteIndex + pCandidateIndex) & S_BLOCK1;
        }
        
        aCarry ^= aWord + (static_cast<std::uint64_t>(aWordIndex) * 0x100000001B3ULL);
        aCarry = RotL64(aCarry, 11U + (aWordIndex * 7U));
        aCarry *= 0x9E3779B185EBCA87ULL;
        
        std::uint64_t aOut = aCarry ^ RotL64(aWord, aWordIndex * 13U + pCandidateIndex);
        aOut ^= (static_cast<std::uint64_t>(aSourceSlot) << 32U);
        aOut ^= static_cast<std::uint64_t>(aSnowSlot);
        
        mCandidate[aWordIndex] = aOut;
    }
    */
}

int TwistFarmSalt::ComputeNearestDistance(const std::uint64_t *pCandidate) {
    if (mCount == 0ULL) {
        return S_SALT * 64;
    }
    
    int aBest = std::numeric_limits<int>::max();
    const std::uint64_t aEnd = std::min<std::uint64_t>(mCount, kCapacity);
    for (std::uint64_t i = 0ULL; i < aEnd; ++i) {
        const int aDistance = mAnalyzer.ComputeSaltHammingDistance_Salt(pCandidate, mSalt[i]);
        if (aDistance < aBest) {
            aBest = aDistance;
        }
    }
    return aBest;
}

    
bool TwistFarmSalt::AppendAccepted(const std::uint64_t *pCandidate,
                                   std::uint64_t pScore) {
    if (mCount >= kCapacity) {
        return false;
    }
    
    std::memcpy(mSalt[mCount], pCandidate, sizeof(mSalt[mCount]));
    mScore[mCount] = pScore;
    ++mCount;
    return true;
}

