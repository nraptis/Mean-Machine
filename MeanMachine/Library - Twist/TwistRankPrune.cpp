//
//  TwistRankPrune.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/4/26.
//

#include "TwistRankPrune.hpp"

int TwistRankPrune::Execute(std::uint8_t **pMainList,
                            int pItemCount,
                            std::uint32_t *pRanks,
                            int pMinimumTake) {
    
    std::uint32_t aSortedRanks[32];
    int aSortedRankCount = 0;

    for (int i=0; i<pItemCount; i++) {
        std::uint32_t aRank = pRanks[i];
        bool aAlreadyExists = false;
        for (int n = 0; n < aSortedRankCount; n++) {
            if (aSortedRanks[n] == aRank) {
                aAlreadyExists = true;
                break;
            }
        }
        if (aAlreadyExists == false) {
            aSortedRanks[aSortedRankCount] = aRank;
            aSortedRankCount++;
        }
    }

    for (int i=0; i<aSortedRankCount; i++) {
        
        int aBestIndex = i;
        
        for (int n=i+1; n<aSortedRankCount; n++) {
            if (aSortedRanks[n] > aSortedRanks[aBestIndex]) {
                aBestIndex = n;
            }
        }
        
        if (aBestIndex != i) {
            std::uint32_t aTemp = aSortedRanks[i];
            aSortedRanks[i] = aSortedRanks[aBestIndex];
            aSortedRanks[aBestIndex] = aTemp;
        }
    }
    
    int aFront = 0;

    for (int aSortedRankIndex = 0; aSortedRankIndex < aSortedRankCount; aSortedRankIndex++) {
        
        std::uint32_t aCurrentRank = aSortedRanks[aSortedRankIndex];
        
        int aLeft = aFront;
        int aRight = pItemCount - 1;
        
        while (aLeft <= aRight) {
            
            while ((aLeft <= aRight) && (pRanks[aLeft] == aCurrentRank)) {
                aLeft++;
            }
            
            while ((aLeft <= aRight) && (pRanks[aRight] != aCurrentRank)) {
                aRight--;
            }
            
            if (aLeft < aRight) {
                uint8_t *aHoldItem = pMainList[aLeft];
                pMainList[aLeft] = pMainList[aRight];
                pMainList[aRight] = aHoldItem;
                
                std::uint32_t aHoldRank = pRanks[aLeft];
                pRanks[aLeft] = pRanks[aRight];
                pRanks[aRight] = aHoldRank;
                
                aLeft++;
                aRight--;
            }
        }
        
        aFront = aLeft;
        
        if (aFront >= pMinimumTake) {
            return aFront;
        }
    }

    return aFront;
}
