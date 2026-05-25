//
//  GSKModel.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/21/26.
//

#include "GAXSKModel.hpp"
#include "Random.hpp"
#include <unordered_map>
#include <unordered_set>

static int OrbiterPairKey(GAXSKVariable pOrbiterA,
                          GAXSKVariable pOrbiterB) {
    int aIndexA = GAXSK::GetIndexForOrbiter(pOrbiterA);
    int aIndexB = GAXSK::GetIndexForOrbiter(pOrbiterB);

    if ((aIndexA < 0) || (aIndexB < 0)) {
        return -1;
    }

    if (aIndexA > aIndexB) {
        std::swap(aIndexA, aIndexB);
    }

    return aIndexA * 100 + aIndexB;
}

static bool SameVariableDistanceClash(const std::vector<GAXSKVariable> &pList,
                                      int pMinimumDistance) {
    if (pMinimumDistance <= 0) {
        return false;
    }

    for (std::size_t aIndexA = 0U; aIndexA < pList.size(); aIndexA++) {
        for (std::size_t aIndexB = aIndexA + 1U; aIndexB < pList.size(); aIndexB++) {
            if (pList[aIndexA] != pList[aIndexB]) {
                continue;
            }

            const int aDistance = static_cast<int>(aIndexB - aIndexA);
            if (aDistance < pMinimumDistance) {
                return true;
            }
        }
    }

    return false;
}

static std::vector<GAXSKVariable> MakeContextSchedule(int pTargetCount) {
    std::vector<GAXSKVariable> aBase = {
        GAXSKVariable::kIngress,
        GAXSKVariable::kScatter,
        GAXSKVariable::kPrevious,
        GAXSKVariable::kCross
    };
    
    std::vector<GAXSKVariable> aResult;
    
    if (pTargetCount <= 0) {
        return aResult;
    }
    
    int aTryCount = 0;
    
    do {
        aResult.clear();
        
        for (int aGroupIndex = 0; aGroupIndex < 3; aGroupIndex++) {
            std::vector<GAXSKVariable> aGroup = aBase;
            Random::Shuffle(&aGroup);
            
            for (const GAXSKVariable aVariable : aGroup) {
                aResult.push_back(aVariable);
            }
        }
        
        aTryCount++;
        
        if (aTryCount > 10000) {
            std::printf("warning: MakeContextSchedule hit retry limit, target_count=%d\n",
                        pTargetCount);
            break;
        }
        
    } while (SameVariableDistanceClash(aResult, 2));
    
    if (static_cast<int>(aResult.size()) > pTargetCount) {
        aResult.resize(static_cast<std::size_t>(pTargetCount));
    }
    
    return aResult;
}

GAXSKModelTerm GAXSKModel::VarTerm(GAXSKVariable pVariable) {
    GAXSKModelTerm aTerm;
    aTerm.mKind = GAXSKModelTermKind::kVariable;
    aTerm.mVariable = pVariable;
    aTerm.mNeedsRotation = false;
    return aTerm;
}

GAXSKModelTerm GAXSKModel::RotVarTerm(GAXSKVariable pVariable) {
    GAXSKModelTerm aTerm = VarTerm(pVariable);
    aTerm.mNeedsRotation = true;
    return aTerm;
}

GAXSKModelTerm GAXSKModel::HotAddTerm(int pHotIndex) {
    GAXSKModelTerm aTerm;

    aTerm.mKind = GAXSKModelTermKind::kHotAdd;
    aTerm.mHotIndex = pHotIndex;

    return aTerm;
}

GAXSKModelTerm GAXSKModel::HotMulTerm(int pHotIndex) {
    GAXSKModelTerm aTerm;

    aTerm.mKind = GAXSKModelTermKind::kHotMul;
    aTerm.mHotIndex = pHotIndex;

    return aTerm;
}

GAXSKVariable GAXSKModel::WandererForIndex(int pIndex) {
    switch (pIndex) {
        case 0: return GAXSKVariable::kWandererA;
        case 1: return GAXSKVariable::kWandererB;
        case 2: return GAXSKVariable::kWandererC;
        case 3: return GAXSKVariable::kWandererD;
        case 4: return GAXSKVariable::kWandererE;
        case 5: return GAXSKVariable::kWandererF;
        case 6: return GAXSKVariable::kWandererG;
        case 7: return GAXSKVariable::kWandererH;
        case 8: return GAXSKVariable::kWandererI;
        case 9: return GAXSKVariable::kWandererJ;
        case 10: return GAXSKVariable::kWandererK;
        default: return GAXSKVariable::kInvalid;
    }
}

GAXSKModelStatement GAXSKModel::SetStatement(GAXSKVariable pTarget,
                                             const std::vector<GAXSKModelTerm> &pTerms) {
    GAXSKModelStatement aStatement;
    aStatement.mOperation = GAXSKModelOperation::kSet;
    aStatement.mTarget = pTarget;
    aStatement.mTerms = pTerms;
    return aStatement;
}

GAXSKModelStatement GAXSKModel::AddStatement(GAXSKVariable pTarget,
                                             const std::vector<GAXSKModelTerm> &pTerms) {
    GAXSKModelStatement aStatement;
    aStatement.mOperation = GAXSKModelOperation::kAdd;
    aStatement.mTarget = pTarget;
    aStatement.mTerms = pTerms;
    return aStatement;
}

GAXSKModelStatement GAXSKModel::XorStatement(GAXSKVariable pTarget,
                                             const std::vector<GAXSKModelTerm> &pTerms) {
    GAXSKModelStatement aStatement;
    aStatement.mOperation = GAXSKModelOperation::kXor;
    aStatement.mTarget = pTarget;
    aStatement.mTerms = pTerms;
    return aStatement;
}

GAXSKModelStatement GAXSKModel::MulRotateStatement(GAXSKVariable pTarget,
                                                   int pHotIndex) {
    GAXSKModelStatement aStatement;
    aStatement.mOperation = GAXSKModelOperation::kMulRotate;
    aStatement.mTarget = pTarget;
    aStatement.mTerms.push_back(VarTerm(pTarget));
    aStatement.mTerms.push_back(HotMulTerm(pHotIndex));
    aStatement.mNeedsRotation = true;
    return aStatement;
}

void GAXSKModel::AppendOrbiterAssignStatements(const std::vector<GAXSKVariable> &pOrbiters,
                                               const std::vector<GAXSKVariable> &pWanderers,
                                               int pHotIndexBase,
                                               std::vector<GAXSKModelStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }

    if (pOrbiters.empty()) {
        return;
    }

    if (pWanderers.empty()) {
        return;
    }

    struct OrbiterAssignRowPlan {
        int mIndex = -1;
        GAXSKVariable mOrbiter = GAXSKVariable::kInvalid;
        GAXSKVariable mWanderer = GAXSKVariable::kInvalid;
        GAXSKVariable mContext = GAXSKVariable::kInvalid;
        bool mUseCarry = false;
    };

    std::vector<GAXSKVariable> aContextSchedule =
        MakeContextSchedule(static_cast<int>(pOrbiters.size()));

    std::unordered_map<GAXSKVariable, int> aWandererUsage;
    for (const GAXSKVariable aWanderer : pWanderers) {
        aWandererUsage[aWanderer] = 0;
    }

    auto PopRandomLowestUsageWanderer = [&]() -> GAXSKVariable {
        int aLowestUsage = 0;
        bool aFoundAny = false;

        for (const GAXSKVariable aWanderer : pWanderers) {
            const int aUsage = aWandererUsage[aWanderer];
            if (!aFoundAny || (aUsage < aLowestUsage)) {
                aLowestUsage = aUsage;
                aFoundAny = true;
            }
        }

        std::vector<GAXSKVariable> aCandidates;

        for (const GAXSKVariable aWanderer : pWanderers) {
            if (aWandererUsage[aWanderer] == aLowestUsage) {
                aCandidates.push_back(aWanderer);
            }
        }

        GAXSKVariable aResult = Random::Choice(aCandidates);
        aWandererUsage[aResult] += 1;
        return aResult;
    };

    std::vector<OrbiterAssignRowPlan> aRows;

    for (std::size_t aIndex = 0U; aIndex < pOrbiters.size(); aIndex++) {
        const GAXSKVariable aOrbiter = pOrbiters[aIndex];

        if (aOrbiter == GAXSKVariable::kInvalid) {
            continue;
        }

        GAXSKVariable aContext = GAXSKVariable::kIngress;
        if (aIndex < aContextSchedule.size()) {
            aContext = aContextSchedule[aIndex];
        }

        OrbiterAssignRowPlan aRow;
        aRow.mIndex = static_cast<int>(aIndex);
        aRow.mOrbiter = aOrbiter;
        aRow.mWanderer = PopRandomLowestUsageWanderer();
        aRow.mContext = aContext;

        aRows.push_back(aRow);
    }

    //
    // Pick 1 or 2 carry rows, grouped by context type.
    //
    // This avoids carrying on two rows with the same context flavor, without
    // needing retry helpers or SelectedIndexesHaveUniqueContext.
    //
    //const int aCarryCount = Random::Bool() ? 1 : 2;
    const int aCarryCount = 3;
    

    std::vector<GAXSKVariable> aContextKinds = {
        GAXSKVariable::kIngress,
        GAXSKVariable::kScatter,
        GAXSKVariable::kPrevious,
        GAXSKVariable::kCross
    };

    Random::Shuffle(&aContextKinds);

    int aCarryAssignedCount = 0;

    for (const GAXSKVariable aContextKind : aContextKinds) {
        std::vector<int> aCandidateRowIndexes;

        for (int aRowIndex = 0; aRowIndex < static_cast<int>(aRows.size()); aRowIndex++) {
            const OrbiterAssignRowPlan &aRow =
                aRows[static_cast<std::size_t>(aRowIndex)];

            if (aRow.mContext == aContextKind) {
                aCandidateRowIndexes.push_back(aRowIndex);
            }
        }

        if (aCandidateRowIndexes.empty()) {
            continue;
        }

        const int aChosenRowIndex = Random::Choice(aCandidateRowIndexes);
        aRows[static_cast<std::size_t>(aChosenRowIndex)].mUseCarry = true;

        aCarryAssignedCount++;
        if (aCarryAssignedCount >= aCarryCount) {
            break;
        }
    }

    if (aCarryAssignedCount != aCarryCount) {
        std::printf("warning: AppendOrbiterAssignStatements assigned carry_count=%d requested=%d rows=%zu\n",
                    aCarryAssignedCount,
                    aCarryCount,
                    aRows.size());
    }

    for (const OrbiterAssignRowPlan &aRow : aRows) {
        std::vector<GAXSKModelTerm> aTerms;

        aTerms.push_back(VarTerm(aRow.mWanderer));
        aTerms.push_back(RotVarTerm(aRow.mContext));

        if (aRow.mUseCarry) {
            aTerms.push_back(RotVarTerm(GAXSKVariable::kCarry));
        }

        aTerms.push_back(HotAddTerm(pHotIndexBase + aRow.mIndex));

        pStatements->push_back(SetStatement(aRow.mOrbiter, aTerms));
    }
}

void GAXSKModel::AppendWandererUpdateStatements(const std::vector<GAXSKVariable> &pOrbiters,
                                                int pWandererCount,
                                                std::vector<GAXSKModelStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }

    if (pOrbiters.empty()) {
        return;
    }

    if (pWandererCount <= 0) {
        return;
    }

    struct WandererUpdateRowPlan {
        int mIndex = -1;
        GAXSKVariable mTarget = GAXSKVariable::kInvalid;
        GAXSKVariable mStream = GAXSKVariable::kInvalid;
        GAXSKVariable mOrbiterA = GAXSKVariable::kInvalid;
        GAXSKVariable mOrbiterB = GAXSKVariable::kInvalid;
        bool mUseXor = false;
        bool mUseCarry = false;
    };

    std::vector<GAXSKVariable> aContextSchedule = MakeContextSchedule(pWandererCount);

    std::unordered_map<GAXSKVariable, int> aOrbiterUsageLHS;
    for (const GAXSKVariable aOrbiter : pOrbiters) {
        aOrbiterUsageLHS[aOrbiter] = 0;
    }

    std::unordered_set<int> aUsedOrbiterPairs;


    auto PopRandomLowestUsageOrbiter = [&]() -> GAXSKVariable {
        int aLowestUsage = 0;
        bool aFoundAny = false;

        for (const GAXSKVariable aOrbiter : pOrbiters) {
            const int aUsage = aOrbiterUsageLHS[aOrbiter];
            if (!aFoundAny || (aUsage < aLowestUsage)) {
                aLowestUsage = aUsage;
                aFoundAny = true;
            }
        }

        std::vector<GAXSKVariable> aCandidates;

        for (const GAXSKVariable aOrbiter : pOrbiters) {
            if (aOrbiterUsageLHS[aOrbiter] == aLowestUsage) {
                aCandidates.push_back(aOrbiter);
            }
        }

        GAXSKVariable aResult = Random::Choice(aCandidates);
        aOrbiterUsageLHS[aResult] += 1;
        return aResult;
    };

    auto PopRandomNonAdjacentOrbiterUnsafe = [&](GAXSKVariable pLeft) -> GAXSKVariable {
        std::vector<GAXSKVariable> aCandidates;

        // Tier 1: non-adjacent and unused pair.
        for (const GAXSKVariable aOrbiter : pOrbiters) {
            if (aOrbiter == pLeft) { continue; }
            if (GAXSK::AreOrbitersAdjacent(pLeft, aOrbiter)) { continue; }

            const int aPairKey = OrbiterPairKey(pLeft, aOrbiter);
            if ((aPairKey >= 0) && (aUsedOrbiterPairs.find(aPairKey) != aUsedOrbiterPairs.end())) {
                continue;
            }

            aCandidates.push_back(aOrbiter);
        }

        if (!aCandidates.empty()) {
            return Random::Choice(aCandidates);
        }

        // Tier 2: unused pair, adjacent allowed.
        for (const GAXSKVariable aOrbiter : pOrbiters) {
            if (aOrbiter == pLeft) { continue; }

            const int aPairKey = OrbiterPairKey(pLeft, aOrbiter);
            if ((aPairKey >= 0) && (aUsedOrbiterPairs.find(aPairKey) != aUsedOrbiterPairs.end())) {
                continue;
            }

            aCandidates.push_back(aOrbiter);
        }

        if (!aCandidates.empty()) {
            return Random::Choice(aCandidates);
        }

        // Tier 3: non-adjacent, reused pair allowed.
        for (const GAXSKVariable aOrbiter : pOrbiters) {
            if (aOrbiter == pLeft) { continue; }
            if (GAXSK::AreOrbitersAdjacent(pLeft, aOrbiter)) { continue; }

            aCandidates.push_back(aOrbiter);
        }

        if (!aCandidates.empty()) {
            return Random::Choice(aCandidates);
        }

        // Tier 4: anything except self.
        for (const GAXSKVariable aOrbiter : pOrbiters) {
            if (aOrbiter != pLeft) {
                aCandidates.push_back(aOrbiter);
            }
        }

        if (!aCandidates.empty()) {
            return Random::Choice(aCandidates);
        }

        return Random::Choice(pOrbiters);
    };

    const bool aFlipXorAndAdd = Random::Bool();

    std::vector<WandererUpdateRowPlan> aRows;

    for (int aIndex = 0; aIndex < pWandererCount; aIndex++) {
        GAXSKVariable aTarget = WandererForIndex(aIndex);
        if (aTarget == GAXSKVariable::kInvalid) {
            continue;
        }

        GAXSKVariable aStream = aContextSchedule[static_cast<std::size_t>(aIndex)];

        GAXSKVariable aOrbiterA = PopRandomLowestUsageOrbiter();
        GAXSKVariable aOrbiterB = PopRandomNonAdjacentOrbiterUnsafe(aOrbiterA);
        if (Random::Bool()) {
            std::swap(aOrbiterA, aOrbiterB);
        }

        const int aPairKey = OrbiterPairKey(aOrbiterA, aOrbiterB);
        if (aPairKey >= 0) {
            aUsedOrbiterPairs.insert(aPairKey);
        }

        bool aUseXor = ((aIndex & 1) == 1);
        if (aFlipXorAndAdd) {
            aUseXor = !aUseXor;
        }

        WandererUpdateRowPlan aRow;
        aRow.mIndex = aIndex;
        aRow.mTarget = aTarget;
        aRow.mStream = aStream;
        aRow.mOrbiterA = aOrbiterA;
        aRow.mOrbiterB = aOrbiterB;
        aRow.mUseXor = aUseXor;

        aRows.push_back(aRow);
    }

    auto CarryRowsAreValid =
        [&](const std::vector<int> &pSelectedRowIndexes) -> bool {

        std::unordered_set<GAXSKVariable> aUsedContext;
        std::unordered_set<int> aUsedOrbiterPairs;

        int aRepeatedOrbiterCount = 0;
        std::unordered_set<GAXSKVariable> aUsedOrbiters;

        for (int aRowIndex : pSelectedRowIndexes) {
            if (aRowIndex < 0 || aRowIndex >= static_cast<int>(aRows.size())) {
                return false;
            }

            const WandererUpdateRowPlan &aRow =
                aRows[static_cast<std::size_t>(aRowIndex)];

            // Carry only on add rows.
            if (aRow.mUseXor) {
                return false;
            }

            // Context must be unique.
            if (aUsedContext.find(aRow.mStream) != aUsedContext.end()) {
                return false;
            }
            aUsedContext.insert(aRow.mStream);

            if (aRow.mOrbiterA == GAXSKVariable::kInvalid ||
                aRow.mOrbiterB == GAXSKVariable::kInvalid ||
                aRow.mOrbiterA == aRow.mOrbiterB) {
                return false;
            }

            // The unordered orbiter pair itself must not repeat.
            const int aPairKey = OrbiterPairKey(aRow.mOrbiterA, aRow.mOrbiterB);
            if (aPairKey < 0) {
                return false;
            }

            if (aUsedOrbiterPairs.find(aPairKey) != aUsedOrbiterPairs.end()) {
                return false;
            }
            aUsedOrbiterPairs.insert(aPairKey);

            // Across all carry rows, allow at most one repeated orbiter.
            if (aUsedOrbiters.find(aRow.mOrbiterA) != aUsedOrbiters.end()) {
                aRepeatedOrbiterCount++;
            } else {
                aUsedOrbiters.insert(aRow.mOrbiterA);
            }

            if (aUsedOrbiters.find(aRow.mOrbiterB) != aUsedOrbiters.end()) {
                aRepeatedOrbiterCount++;
            } else {
                aUsedOrbiters.insert(aRow.mOrbiterB);
            }

            if (aRepeatedOrbiterCount > 1) {
                return false;
            }
        }

        return true;
    };
    
    std::vector<int> aCarryRowIndexes;

    //const int aCarryCount = Random::Bool() ? 1 : 2;
    const int aCarryCount = 2;

    int aCarryTryCount = 0;
    do {
        aCarryRowIndexes.clear();

        std::vector<int> aCandidateRowIndexes;
        for (int i = 0; i < static_cast<int>(aRows.size()); i++) {
            aCandidateRowIndexes.push_back(i);
        }

        Random::Shuffle(&aCandidateRowIndexes);

        for (int i = 0;
             i < aCarryCount && i < static_cast<int>(aCandidateRowIndexes.size());
             i++) {
            aCarryRowIndexes.push_back(aCandidateRowIndexes[static_cast<std::size_t>(i)]);
        }

        aCarryTryCount++;
        if (aCarryTryCount > 10000) {
            std::printf("warning: AppendWandererUpdateStatements hit carry retry limit, rows=%zu carry_count=%d\n",
                        aRows.size(),
                        aCarryCount);
            aCarryRowIndexes.clear();
            break;
        }

    } while (!CarryRowsAreValid(aCarryRowIndexes));

    for (int aRowIndex : aCarryRowIndexes) {
        if (aRowIndex >= 0 && aRowIndex < static_cast<int>(aRows.size())) {
            aRows[static_cast<std::size_t>(aRowIndex)].mUseCarry = true;
        }
    }

    for (const WandererUpdateRowPlan &aRow : aRows) {
        std::vector<GAXSKModelTerm> aTerms;
        aTerms.push_back(VarTerm(aRow.mTarget));
        aTerms.push_back(RotVarTerm(aRow.mStream));

        if (Random::Bool()) {
            aTerms.push_back(RotVarTerm(aRow.mOrbiterA));
            aTerms.push_back(VarTerm(aRow.mOrbiterB));
        } else {
            aTerms.push_back(VarTerm(aRow.mOrbiterA));
            aTerms.push_back(RotVarTerm(aRow.mOrbiterB));
        }

        if (aRow.mUseCarry) {
            aTerms.push_back(RotVarTerm(GAXSKVariable::kCarry));
        }

        if (aRow.mUseXor) {
            pStatements->push_back(XorStatement(aRow.mTarget, aTerms));
        } else {
            pStatements->push_back(AddStatement(aRow.mTarget, aTerms));
        }
    }
}

void GAXSKModel::AppendOrbiterRoundStatements(const GAXSKModelOrbiterRound &pRound,
                                              int pHotIndex,
                                              std::vector<GAXSKModelStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }

    const int aLeadHotIndex = pHotIndex;
    const int aFeedbackHotIndex = pHotIndex + 1;

    pStatements->push_back(
        AddStatement(
            pRound.mLead,
            {
                VarTerm(pRound.mLead),
                VarTerm(pRound.mSource),
                HotAddTerm(aLeadHotIndex)
            }
        )
    );

    pStatements->push_back(
        XorStatement(
            pRound.mFeedback,
            {
                VarTerm(pRound.mFeedback),
                VarTerm(pRound.mLead),
                HotAddTerm(aFeedbackHotIndex)
            }
        )
    );

    pStatements->push_back(
        MulRotateStatement(pRound.mFeedback, aFeedbackHotIndex)
    );
}

GAXSKModel GAXSKModel::MakeOrbiterPlan(std::span<const GAXSKModelOrbiterRound> pRounds) {
    GAXSKModel aResult;

    for (const GAXSKModelOrbiterRound &aRound : pRounds) {
        auto PushUnique = [&](GAXSKVariable pVariable) {
            if (std::find(aResult.mOrbiters.begin(),
                          aResult.mOrbiters.end(),
                          pVariable) == aResult.mOrbiters.end()) {
                aResult.mOrbiters.push_back(pVariable);
            }
        };

        PushUnique(aRound.mLead);
        PushUnique(aRound.mSource);
        PushUnique(aRound.mFeedback);
    }

    for (int i = 0; i < static_cast<int>(aResult.mOrbiters.size()); ++i) {
        aResult.mWanderers.push_back(WandererForIndex(i));
    }

    AppendOrbiterAssignStatements(aResult.mOrbiters,
                                  aResult.mWanderers,
                                  0,
                                  &aResult.mStatements);

    int aHotIndex = static_cast<int>(aResult.mOrbiters.size());

    for (const GAXSKModelOrbiterRound &aRound : pRounds) {
        AppendOrbiterRoundStatements(aRound,
                                     aHotIndex,
                                     &aResult.mStatements);
        aHotIndex += 2;
    }

    AppendWandererUpdateStatements(aResult.mOrbiters,
                                   static_cast<int>(aResult.mWanderers.size()),
                                   &aResult.mStatements);

    return aResult;
}
