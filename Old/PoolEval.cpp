//
//  PoolEval.cpp
//  CornTesting
//
//  Created by Magneto on 4/21/26.
//

#include "PoolEval.hpp"

namespace {

void ResetAchieveVector(std::vector<bool> &pAchieve) {
    for (int aIndex = 0; aIndex < pAchieve.size(); aIndex++) {
        pAchieve[aIndex] = false;
    }
    while (pAchieve.size() < 8) {
        pAchieve.push_back(false);
    }
}

bool ValidateAchieveRange(const std::vector<bool> &pAchieve,
                          const int pMinimum,
                          const int pMaximum) {
    for (int aIndex = pMinimum; aIndex <= pMaximum; aIndex++) {
        if (pAchieve[aIndex] == false) {
            return false;
        }
    }

    for (int aIndex = 0; aIndex < pMinimum; aIndex++) {
        if (pAchieve[aIndex] == true) {
            return false;
        }
    }

    for (int aIndex = pMaximum + 1; aIndex < pAchieve.size(); aIndex++) {
        if (pAchieve[aIndex] == true) {
            return false;
        }
    }

    return true;
}

bool ValidateCount(const int pCount,
                   const int pMinimum,
                   const int pMaximum,
                   const char *pName,
                   bool &pHardFailure) {
    if (pCount < pMinimum) {
        printf("underflow count %s\n", pName);
        pHardFailure = true;
        return false;
    }

    if (pCount > pMaximum) {
        printf("overflow count %s\n", pName);
        pHardFailure = true;
        return false;
    }

    return true;
}

} // namespace


int PoolEval::Count(const std::vector<GStatementSlot> &pSlots, const GSymbol pSymbol) {
    int aCount = 0;
    for (int aIndex=0; aIndex<pSlots.size(); aIndex++) {
        switch(pSlots[aIndex].mType) {
            case GStatementSlotType::kInv:
                break;
            case GStatementSlotType::kSymbol:
                if (pSlots[aIndex].mSymbol == pSymbol) {
                    aCount += 1;
                }
                break;
            case GStatementSlotType::kExpr:
                break;
        }
    }
    return aCount;
}

int PoolEval::Count(const std::vector<GStatementSlot> &pSlots, const GExpr pExpr) {
    int aCount = 0;
    for (int aIndex=0; aIndex<pSlots.size(); aIndex++) {
        switch(pSlots[aIndex].mType) {
            case GStatementSlotType::kInv:
                break;
            case GStatementSlotType::kSymbol:
                break;
            case GStatementSlotType::kExpr:
                if (pSlots[aIndex].mExpr == pExpr) {
                    aCount += 1;
                }
                break;
        }
    }
    return aCount;
}


void PoolEval::ResetTwo(std::vector<bool> &pAchieveA,
                        std::vector<bool> &pAchieveB) {
    ResetAchieveVector(pAchieveA);
    ResetAchieveVector(pAchieveB);
}

bool PoolEval::UpdateTwo(int pMinA,
                         int pMaxA,
                         int pCountA,
                         int pMinB,
                         int pMaxB,
                         int pCountB,
                         std::vector<bool> &pAchieveA,
                         std::vector<bool> &pAchieveB,
                         int pTotalMin,
                         int pTotalMax,
                         bool &pHardFailure) {
    pHardFailure = false;

    if (!ValidateCount(pCountA, pMinA, pMaxA, "a", pHardFailure)) {
        return false;
    }

    if (!ValidateCount(pCountB, pMinB, pMaxB, "b", pHardFailure)) {
        return false;
    }
    
    if ((pCountA + pCountB) < pTotalMin) {
        printf("underflow count total\n");
        pHardFailure = true;
        return false;
    }
    
    if ((pCountA + pCountB) > pTotalMax) {
        printf("overflow count total\n");
        pHardFailure = true;
        return false;
    }
    
    pAchieveA[pCountA] = true;
    pAchieveB[pCountB] = true;
    
    return ValidateAchieveRange(pAchieveA, pMinA, pMaxA) &&
           ValidateAchieveRange(pAchieveB, pMinB, pMaxB);
}

void PoolEval::ResetThree(std::vector<bool> &pAchieveA,
                          std::vector<bool> &pAchieveB,
                          std::vector<bool> &pAchieveC) {
    ResetAchieveVector(pAchieveA);
    ResetAchieveVector(pAchieveB);
    ResetAchieveVector(pAchieveC);
}

bool PoolEval::UpdateThree(int pMinA,
                           int pMaxA,
                           int pCountA,
                           int pMinB,
                           int pMaxB,
                           int pCountB,
                           int pMinC,
                           int pMaxC,
                           int pCountC,
                           std::vector<bool> &pAchieveA,
                           std::vector<bool> &pAchieveB,
                           std::vector<bool> &pAchieveC,
                           int pTotalMin,
                           int pTotalMax,
                           bool &pHardFailure) {
    pHardFailure = false;

    if (!ValidateCount(pCountA, pMinA, pMaxA, "a", pHardFailure)) {
        return false;
    }

    if (!ValidateCount(pCountB, pMinB, pMaxB, "b", pHardFailure)) {
        return false;
    }

    if (!ValidateCount(pCountC, pMinC, pMaxC, "c", pHardFailure)) {
        return false;
    }

    if ((pCountA + pCountB + pCountC) < pTotalMin) {
        printf("underflow count total\n");
        pHardFailure = true;
        return false;
    }

    if ((pCountA + pCountB + pCountC) > pTotalMax) {
        printf("overflow count total\n");
        pHardFailure = true;
        return false;
    }

    pAchieveA[pCountA] = true;
    pAchieveB[pCountB] = true;
    pAchieveC[pCountC] = true;

    return ValidateAchieveRange(pAchieveA, pMinA, pMaxA) &&
           ValidateAchieveRange(pAchieveB, pMinB, pMaxB) &&
           ValidateAchieveRange(pAchieveC, pMinC, pMaxC);
}
