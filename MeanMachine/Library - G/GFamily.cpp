//
//  GBoxFamily.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/2/26.
//

#include "GFamily.hpp"

void GBoxFamily::Build(std::vector<GSymbol> pList, int pCount) {
    
    if (pList.empty()) {
        return;
    }
    
    if (pCount <= 0) {
        return;
    }
    
    if (pCount > FAMILY_DEPTH) {
        pCount = FAMILY_DEPTH;
    }
    
    std::vector<GSymbol> aList;
    aList.insert(aList.begin(), pList.begin(), pList.end());
    
    Random::Shuffle(&aList);
    
    int aCandidateCount = static_cast<int>(aList.size());
    
    if (aCandidateCount > FAMILY_MAX_CANDIDATE_COUNT) {
        aCandidateCount = FAMILY_MAX_CANDIDATE_COUNT;
    }
    
    for (int i=0; i<FAMILY_SIZE; i++) {
        for (int n=0; n<FAMILY_DEPTH; n++) {
            mChosen[i][n] = -1;
            mBox[i][n].Invalidate();
        }
    }
    
    for (int i=0; i<FAMILY_MAX_CANDIDATE_COUNT; i++) {
        mReserved[i] = 0;
    }
    
    int aFamilyUse[FAMILY_SIZE][FAMILY_MAX_CANDIDATE_COUNT];
    
    for (int i=0; i<FAMILY_SIZE; i++) {
        for (int n=0; n<FAMILY_MAX_CANDIDATE_COUNT; n++) {
            aFamilyUse[i][n] = 0;
        }
    }
    
    for (int aOuter=0; aOuter<FAMILY_SIZE; aOuter++) {
        for (int aSlot=0; aSlot<pCount; aSlot++) {
            int aBestIndex = 0;
            int aBestScore = std::numeric_limits<int>::max();
            
            for (int aIndex=0; aIndex<aCandidateCount; aIndex++) {
                int aSameSlotCollisions = 0;
                int aFamilyOverlap = 0;
                
                for (int aInner=0; aInner<aOuter; aInner++) {
                    
                    if (mChosen[aInner][aSlot] == aIndex) {
                        aSameSlotCollisions++;
                    }
                    
                    for (int aOtherSlot=0; aOtherSlot<pCount; aOtherSlot++) {
                        if (mChosen[aInner][aOtherSlot] == aIndex) {
                            aFamilyOverlap++;
                        }
                    }
                }
                
                const int aScore =
                (aSameSlotCollisions * 1000000) +
                (aFamilyOverlap * 50000) +
                (aFamilyUse[aOuter][aIndex] * 10000) +
                (mReserved[aIndex] * 100) +
                ((aIndex + aOuter + aSlot) % aCandidateCount);
                
                if (aScore < aBestScore) {
                    aBestScore = aScore;
                    aBestIndex = aIndex;
                }
            }
            
            mBox[aOuter][aSlot] = aList[aBestIndex];
            mChosen[aOuter][aSlot] = aBestIndex;
            
            aFamilyUse[aOuter][aBestIndex]++;
            mReserved[aBestIndex]++;
        }
    }
    
    
    for (int i=FAMILY_SIZE - 1; i>0; i--) {
        int j = Random::Get(i + 1);
        
        if (j != i) {
            for (int n=0; n<FAMILY_DEPTH; n++) {
                GSymbol aHold = mBox[i][n];
                mBox[i][n] = mBox[j][n];
                mBox[j][n] = aHold;
            }
        }
    }
    
}

std::vector<int> GRotationFamily::GetListLow() {
    return {
        3, 5, 7
    };
}

std::vector<int> GRotationFamily::GetListMedium() {
    return {
        11, 13, 17, 19, 21, 27, 29
    };
}

std::vector<int> GRotationFamily::GetListHigh() {
    return {
        31, 35, 37, 43, 45, 51, 53
    };
}

std::vector<int> GRotationFamily::GetListAll() {
    return {
        1, 3, 5, 7,
        11, 13, 19, 21, 27, 29,
        35, 37, 43, 45, 51, 53
    };
}

void GRotationFamily::Build(int pCount) {
    
    if (pCount <= 0) {
        return;
    }
    
    if (pCount > FAMILY_DEPTH) {
        pCount = FAMILY_DEPTH;
    }
    
    std::vector<int> aLow = GRotationFamily::GetListLow();
    std::vector<int> aMedium = GRotationFamily::GetListMedium();
    std::vector<int> aHigh = GRotationFamily::GetListHigh();
    std::vector<int> aHealthy = GRotationFamily::GetListAll();
    
    Random::Shuffle(&aLow);
    Random::Shuffle(&aMedium);
    Random::Shuffle(&aHigh);
    Random::Shuffle(&aHealthy);
    
    BuildGroup(mLow, aLow, pCount, false);
    BuildGroup(mMedium, aMedium, pCount, false);
    BuildGroup(mHigh, aHigh, pCount, false);
    
    // Healthy is built last so it can avoid Low/Medium/High.
    BuildGroup(mHealthy, aHealthy, pCount, true);
    
    ShuffleFamilies();
}

int GRotationFamily::GetExistingCollisionScore(int pFamily,
                                               int pSlot,
                                               int pValue) {
    
    int aScore = 0;
    
    // Exact same family + same slot is the worst.
    if (mLow[pFamily][pSlot] == pValue) {
        aScore += 1000000;
    }
    
    if (mMedium[pFamily][pSlot] == pValue) {
        aScore += 1000000;
    }
    
    if (mHigh[pFamily][pSlot] == pValue) {
        aScore += 1000000;
    }
    
    // Same family, different slot is still undesirable.
    for (int aSlot=0; aSlot<FAMILY_DEPTH; aSlot++) {
        if (mLow[pFamily][aSlot] == pValue) {
            aScore += 50000;
        }
        
        if (mMedium[pFamily][aSlot] == pValue) {
            aScore += 50000;
        }
        
        if (mHigh[pFamily][aSlot] == pValue) {
            aScore += 50000;
        }
    }
    
    // Same slot, different family is also undesirable.
    for (int aFamily=0; aFamily<FAMILY_SIZE; aFamily++) {
        if (mLow[aFamily][pSlot] == pValue) {
            aScore += 25000;
        }
        
        if (mMedium[aFamily][pSlot] == pValue) {
            aScore += 25000;
        }
        
        if (mHigh[aFamily][pSlot] == pValue) {
            aScore += 25000;
        }
    }
    
    return aScore;
}

void GRotationFamily::BuildGroup(int pDest[FAMILY_SIZE][FAMILY_DEPTH],
                                 std::vector<int> pList,
                                 int pCount,
                                 bool pAvoidExisting) {
    
    if (pList.empty()) {
        return;
    }
    
    if (pCount <= 0) {
        return;
    }
    
    if (pCount > FAMILY_DEPTH) {
        pCount = FAMILY_DEPTH;
    }
    
    const int aCandidateCount = static_cast<int>(pList.size());
    
    int aChosen[FAMILY_SIZE][FAMILY_DEPTH];
    int aReserved[16];
    int aFamilyUse[FAMILY_SIZE][16];
    
    for (int i=0; i<FAMILY_SIZE; i++) {
        for (int n=0; n<FAMILY_DEPTH; n++) {
            aChosen[i][n] = -1;
            pDest[i][n] = 0;
        }
    }
    
    for (int i=0; i<16; i++) {
        aReserved[i] = 0;
    }
    
    for (int i=0; i<FAMILY_SIZE; i++) {
        for (int n=0; n<16; n++) {
            aFamilyUse[i][n] = 0;
        }
    }
    
    for (int aOuter=0; aOuter<FAMILY_SIZE; aOuter++) {
        for (int aSlot=0; aSlot<pCount; aSlot++) {
            int aBestIndex = 0;
            int aBestScore = std::numeric_limits<int>::max();
            
            for (int aIndex=0; aIndex<aCandidateCount; aIndex++) {
                int aSameSlotCollisions = 0;
                int aFamilyOverlap = 0;
                
                for (int aInner=0; aInner<aOuter; aInner++) {
                    
                    if (aChosen[aInner][aSlot] == aIndex) {
                        aSameSlotCollisions++;
                    }
                    
                    for (int aOtherSlot=0; aOtherSlot<pCount; aOtherSlot++) {
                        if (aChosen[aInner][aOtherSlot] == aIndex) {
                            aFamilyOverlap++;
                        }
                    }
                }
                
                const int aTargetIndex =
                    ((aOuter * pCount) + aSlot) % aCandidateCount;
                
                const int aTieBreak =
                    (aIndex - aTargetIndex + aCandidateCount) % aCandidateCount;
                
                const int aExistingCollisionScore =
                    pAvoidExisting ? GetExistingCollisionScore(aOuter, aSlot, pList[aIndex]) : 0;
                
                const int aScore =
                aExistingCollisionScore +
                (aSameSlotCollisions * 1000000) +
                (aFamilyOverlap * 50000) +
                (aFamilyUse[aOuter][aIndex] * 10000) +
                (aReserved[aIndex] * 100) +
                aTieBreak;
                
                if (aScore < aBestScore) {
                    aBestScore = aScore;
                    aBestIndex = aIndex;
                }
            }
            
            pDest[aOuter][aSlot] = pList[aBestIndex];
            
            aChosen[aOuter][aSlot] = aBestIndex;
            aFamilyUse[aOuter][aBestIndex]++;
            aReserved[aBestIndex]++;
        }
    }
}

void GRotationFamily::ShuffleFamilies() {
    
    for (int i=FAMILY_SIZE - 1; i>0; i--) {
        int j = Random::Get(i + 1);
        
        for (int n=0; n<FAMILY_DEPTH; n++) {
            
            int aTempLow = mLow[i][n];
            mLow[i][n] = mLow[j][n];
            mLow[j][n] = aTempLow;
            
            int aTempMedium = mMedium[i][n];
            mMedium[i][n] = mMedium[j][n];
            mMedium[j][n] = aTempMedium;
            
            int aTempHigh = mHigh[i][n];
            mHigh[i][n] = mHigh[j][n];
            mHigh[j][n] = aTempHigh;
            
            int aTempHealthy = mHealthy[i][n];
            mHealthy[i][n] = mHealthy[j][n];
            mHealthy[j][n] = aTempHealthy;
        }
    }
}

void GOperationFamily::Build(int pCount, std::vector<std::uint8_t> pOptions) {
    
    if (pOptions.empty()) {
        return;
    }
    
    if (pCount <= 0) {
        return;
    }
    
    if (pCount > FAMILY_DEPTH) {
        pCount = FAMILY_DEPTH;
    }
    
    std::vector<std::uint8_t> aList;
    aList.insert(aList.begin(), pOptions.begin(), pOptions.end());
    
    Random::Shuffle(&aList);
    
    if (static_cast<int>(aList.size()) > FAMILY_MAX_CANDIDATE_COUNT) {
        aList.resize(FAMILY_MAX_CANDIDATE_COUNT);
    }
    
    BuildGroup(mOperation, aList, pCount, false);
    
    ShuffleFamilies();
}

int GOperationFamily::GetExistingCollisionScore(int pFamily,
                                                int pSlot,
                                                std::uint8_t pValue) {
    
    int aScore = 0;
    
    for (int aSlot=0; aSlot<FAMILY_DEPTH; aSlot++) {
        if (mOperation[pFamily][aSlot] == pValue) {
            aScore += 50000;
        }
    }
    
    for (int aFamily=0; aFamily<FAMILY_SIZE; aFamily++) {
        if (mOperation[aFamily][pSlot] == pValue) {
            aScore += 25000;
        }
    }
    
    return aScore;
}

void GOperationFamily::BuildGroup(std::uint8_t pDest[FAMILY_SIZE][FAMILY_DEPTH],
                                  std::vector<std::uint8_t> pList,
                                  int pCount,
                                  bool pAvoidExisting) {
    
    if (pList.empty()) {
        return;
    }
    
    if (pCount <= 0) {
        return;
    }
    
    if (pCount > FAMILY_DEPTH) {
        pCount = FAMILY_DEPTH;
    }
    
    int aCandidateCount = static_cast<int>(pList.size());
    
    if (aCandidateCount > FAMILY_MAX_CANDIDATE_COUNT) {
        aCandidateCount = FAMILY_MAX_CANDIDATE_COUNT;
    }
    
    int aChosen[FAMILY_SIZE][FAMILY_DEPTH];
    int aReserved[FAMILY_MAX_CANDIDATE_COUNT];
    int aFamilyUse[FAMILY_SIZE][FAMILY_MAX_CANDIDATE_COUNT];
    
    for (int i=0; i<FAMILY_SIZE; i++) {
        for (int n=0; n<FAMILY_DEPTH; n++) {
            aChosen[i][n] = -1;
            pDest[i][n] = 0;
        }
    }
    
    for (int i=0; i<FAMILY_MAX_CANDIDATE_COUNT; i++) {
        aReserved[i] = 0;
    }
    
    for (int i=0; i<FAMILY_SIZE; i++) {
        for (int n=0; n<FAMILY_MAX_CANDIDATE_COUNT; n++) {
            aFamilyUse[i][n] = 0;
        }
    }
    
    for (int aOuter=0; aOuter<FAMILY_SIZE; aOuter++) {
        for (int aSlot=0; aSlot<pCount; aSlot++) {
            int aBestIndex = 0;
            int aBestScore = std::numeric_limits<int>::max();
            
            for (int aIndex=0; aIndex<aCandidateCount; aIndex++) {
                int aSameSlotCollisions = 0;
                int aFamilyOverlap = 0;
                
                for (int aInner=0; aInner<aOuter; aInner++) {
                    
                    if (aChosen[aInner][aSlot] == aIndex) {
                        aSameSlotCollisions++;
                    }
                    
                    for (int aOtherSlot=0; aOtherSlot<pCount; aOtherSlot++) {
                        if (aChosen[aInner][aOtherSlot] == aIndex) {
                            aFamilyOverlap++;
                        }
                    }
                }
                
                const int aTargetIndex =
                    ((aOuter * pCount) + aSlot) % aCandidateCount;
                
                const int aTieBreak =
                    (aIndex - aTargetIndex + aCandidateCount) % aCandidateCount;
                
                const int aExistingCollisionScore =
                    pAvoidExisting ? GetExistingCollisionScore(aOuter, aSlot, pList[aIndex]) : 0;
                
                const int aScore =
                aExistingCollisionScore +
                (aSameSlotCollisions * 1000000) +
                (aFamilyOverlap * 50000) +
                (aFamilyUse[aOuter][aIndex] * 10000) +
                (aReserved[aIndex] * 100) +
                aTieBreak;
                
                if (aScore < aBestScore) {
                    aBestScore = aScore;
                    aBestIndex = aIndex;
                }
            }
            
            pDest[aOuter][aSlot] = pList[aBestIndex];
            
            aChosen[aOuter][aSlot] = aBestIndex;
            aFamilyUse[aOuter][aBestIndex]++;
            aReserved[aBestIndex]++;
        }
    }
}


void GOperationFamily::ShuffleFamilies() {
    
    for (int i=FAMILY_SIZE - 1; i>0; i--) {
        int j = Random::Get(i + 1);
        
        if (j != i) {
            for (int n=0; n<FAMILY_DEPTH; n++) {
                std::uint8_t aHold = mOperation[i][n];
                mOperation[i][n] = mOperation[j][n];
                mOperation[j][n] = aHold;
            }
        }
    }
}
