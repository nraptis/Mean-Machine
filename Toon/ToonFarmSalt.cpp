//
//  ToonFarmSalt.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/6/26.
//

#include "ToonFarmSalt.hpp"

ToonFarmSalt::ToonFarmSalt() {
    
}

void ToonFarmSalt::Derive(const std::uint8_t *pSource,
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
    printf("ToonFarmSalt::Derive sorted candidate scores\n");
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

void ToonFarmSalt::Derive(const std::uint8_t *pSource,
                          ToonDomainRoundMaterial *pRoundMaterial) {
    if (pRoundMaterial == nullptr) {
        return;
    }
    Derive(pSource,
           pRoundMaterial->mSaltA,
           pRoundMaterial->mSaltB,
           pRoundMaterial->mSaltC,
           pRoundMaterial->mSaltD,
           pRoundMaterial->mSaltE,
           pRoundMaterial->mSaltF);
}

