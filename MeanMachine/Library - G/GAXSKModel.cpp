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

GAXSKModelStatement GAXSKModel::MulRotateStatement(GAXSKVariable pTarget) {
    GAXSKModelStatement aStatement;
    aStatement.mOperation = GAXSKModelOperation::kMulRotate;
    aStatement.mTarget = pTarget;
    aStatement.mTerms.push_back(VarTerm(pTarget));
    aStatement.mTerms.push_back(HotMulTerm());
    aStatement.mNeedsRotation = true;
    return aStatement;
}

void GAXSKModel::AppendOrbiterAssignStatements(const std::vector<GAXSKVariable> &pOrbiters,
                                               const std::vector<GAXSKVariable> &pWanderers,
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

    std::vector<GAXSKVariable> aContextSchedule = MakeContextSchedule((int)pOrbiters.size());

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

    for (std::size_t aIndex = 0U; aIndex < pOrbiters.size(); aIndex++) {
        GAXSKVariable aOrbiter = pOrbiters[aIndex];

        if (aOrbiter == GAXSKVariable::kInvalid) {
            continue;
        }

        GAXSKVariable aContext = GAXSKVariable::kIngress;
        if (aIndex < aContextSchedule.size()) {
            aContext = aContextSchedule[aIndex];
        }

        GAXSKVariable aWanderer = PopRandomLowestUsageWanderer();

        std::vector<GAXSKModelTerm> aTerms;
        aTerms.push_back(VarTerm(aWanderer));
        aTerms.push_back(RotVarTerm(aContext));

        if (aIndex < 2U) {
            aTerms.push_back(RotVarTerm(GAXSKVariable::kCarry));
        }

        pStatements->push_back(SetStatement(aOrbiter, aTerms));
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
    
    std::vector<GAXSKVariable> aContextSchedule = MakeContextSchedule(pWandererCount);
    
    std::unordered_map<GAXSKVariable, int> aOrbiterUsageLHS;
    for (const GAXSKVariable aOrbiter : pOrbiters) {
        aOrbiterUsageLHS[aOrbiter] = 0;
    }
    
    std::unordered_set<int> aUsedOrbiterPairs;
    auto OrbiterPairKey = [](GAXSKVariable pOrbiterA,
                             GAXSKVariable pOrbiterB) -> int {
        int aIndexA = GAXSK::GetIndexForOrbiter(pOrbiterA);
        int aIndexB = GAXSK::GetIndexForOrbiter(pOrbiterB);

        if ((aIndexA < 0) || (aIndexB < 0)) {
            return -1;
        }

        if (aIndexA > aIndexB) {
            std::swap(aIndexA, aIndexB);
        }

        return aIndexA * 100 + aIndexB;
    };
    
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
    
    for (int aIndex = 0; aIndex < pWandererCount; aIndex++) {
        GAXSKVariable aTarget = WandererForIndex(aIndex);
        if (aTarget == GAXSKVariable::kInvalid) {
            continue;
        }
        
        GAXSKVariable aStream = aContextSchedule[aIndex];
        
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
        const bool aUseCarry = (aIndex >= (pWandererCount - 2));
        
        std::vector<GAXSKModelTerm> aTerms;
        aTerms.push_back(VarTerm(aTarget));
        aTerms.push_back(RotVarTerm(aStream));
        
        if (Random::Bool()) {
            aTerms.push_back(RotVarTerm(aOrbiterA));
            aTerms.push_back(VarTerm(aOrbiterB));
        } else {
            aTerms.push_back(VarTerm(aOrbiterA));
            aTerms.push_back(RotVarTerm(aOrbiterB));
        }

        if (aUseCarry) {
            aTerms.push_back(RotVarTerm(GAXSKVariable::kCarry));
        }

        if (aUseXor) {
            pStatements->push_back(XorStatement(aTarget, aTerms));
        } else {
            pStatements->push_back(AddStatement(aTarget, aTerms));
        }
    }
}

void GAXSKModel::AppendOrbiterRoundStatements(const GAXSKModelOrbiterRound &pRound,
                                              std::vector<GAXSKModelStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }

    pStatements->push_back(
        AddStatement(
            pRound.mLead,
            {
                VarTerm(pRound.mLead),
                VarTerm(pRound.mSource)
            }
        )
    );

    pStatements->push_back(
        XorStatement(
            pRound.mFeedback,
            {
                VarTerm(pRound.mFeedback),
                VarTerm(pRound.mLead)
            }
        )
    );

    pStatements->push_back(
        MulRotateStatement(pRound.mFeedback)
    );
}

GAXSKModel GAXSKModel::MakeOrbiterPlan4x4() {
    GAXSKModel aModel;
    
    aModel.mName = "GAXSKModelOrbiter4x4";
    
    aModel.mOrbiters = { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD };
    aModel.mUnwind = {
        GAXSKVariable::kWandererA,
        GAXSKVariable::kWandererB,
        GAXSKVariable::kWandererC,
        GAXSKVariable::kWandererD,
        GAXSKVariable::kWandererE,
        
        GAXSKVariable::kWandererF,
        GAXSKVariable::kWandererG,
        GAXSKVariable::kWandererH,
        GAXSKVariable::kWandererI,
        GAXSKVariable::kWandererJ,
        
        GAXSKVariable::kWandererK
    };
    
    AppendOrbiterAssignStatements(aModel.mOrbiters, aModel.mUnwind, &aModel.mStatements);
    
    const std::vector<GAXSKModelOrbiterRound> aRounds = {
        { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitD },
        { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitA },
        { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB },
        { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC }
    };
    
    for (const GAXSKModelOrbiterRound &aRound : aRounds) {
        AppendOrbiterRoundStatements(aRound, &aModel.mStatements);
    }
    
    AppendWandererUpdateStatements(aModel.mOrbiters,
                                   static_cast<int>(aModel.mUnwind.size()),
                                   &aModel.mStatements);
    
    return aModel;
}
