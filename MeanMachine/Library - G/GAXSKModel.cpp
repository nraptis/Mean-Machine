//
//  GSKModel.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/21/26.
//

#include "GAX.hpp"

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

GAXSKModelStatement GAXSKModel::SetStatement(
    GAXSKVariable pTarget,
    const std::vector<GAXSKModelTerm> &pTerms) {
    GAXSKModelStatement aStatement;
    aStatement.mOperation = GAXSKModelOperation::kSet;
    aStatement.mTarget = pTarget;
    aStatement.mTerms = pTerms;
    return aStatement;
}

GAXSKModelStatement GAXSKModel::AddStatement(
    GAXSKVariable pTarget,
    const std::vector<GAXSKModelTerm> &pTerms) {
    GAXSKModelStatement aStatement;
    aStatement.mOperation = GAXSKModelOperation::kAdd;
    aStatement.mTarget = pTarget;
    aStatement.mTerms = pTerms;
    return aStatement;
}

GAXSKModelStatement GAXSKModel::XorStatement(
    GAXSKVariable pTarget,
    const std::vector<GAXSKModelTerm> &pTerms) {
    GAXSKModelStatement aStatement;
    aStatement.mOperation = GAXSKModelOperation::kXor;
    aStatement.mTarget = pTarget;
    aStatement.mTerms = pTerms;
    return aStatement;
}

GAXSKModelStatement GAXSKModel::MulRotateStatement(
    GAXSKVariable pTarget,
    int pHotIndex) {
    GAXSKModelStatement aStatement;
    aStatement.mOperation = GAXSKModelOperation::kMulRotate;
    aStatement.mTarget = pTarget;
    aStatement.mTerms.push_back(VarTerm(pTarget));
    aStatement.mTerms.push_back(HotMulTerm(pHotIndex));
    aStatement.mNeedsRotation = true;
    return aStatement;
}

void GAXSKModel::AppendOrbiterAssignStatements(
    std::span<const GAXSKModelOrbiterAssignment> pAssignments,
    int pHotIndexBase,
    std::vector<GAXSKModelStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }

    for (std::size_t i = 0U; i < pAssignments.size(); ++i) {
        const GAXSKModelOrbiterAssignment &aAssignment =
            pAssignments[i];
        std::vector<GAXSKModelTerm> aTerms;
        aTerms.push_back(VarTerm(aAssignment.mWanderer));
        aTerms.push_back(RotVarTerm(aAssignment.mContext));
        if (aAssignment.mUseCarry) {
            aTerms.push_back(RotVarTerm(GAXSKVariable::kCarry));
        }
        aTerms.push_back(HotAddTerm(
            pHotIndexBase + static_cast<int>(i)));
        pStatements->push_back(
            SetStatement(aAssignment.mTarget, aTerms));
    }
}

void GAXSKModel::AppendWandererUpdateStatements(
    std::span<const GAXSKModelWandererUpdate> pUpdates,
    std::vector<GAXSKModelStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }

    for (const GAXSKModelWandererUpdate &aUpdate : pUpdates) {
        std::vector<GAXSKModelTerm> aTerms;
        aTerms.push_back(VarTerm(aUpdate.mTarget));
        aTerms.push_back(RotVarTerm(aUpdate.mContext));
        if (aUpdate.mRotateFirst) {
            aTerms.push_back(RotVarTerm(aUpdate.mOrbiterA));
            aTerms.push_back(VarTerm(aUpdate.mOrbiterB));
        } else {
            aTerms.push_back(VarTerm(aUpdate.mOrbiterA));
            aTerms.push_back(RotVarTerm(aUpdate.mOrbiterB));
        }
        if (aUpdate.mUseCarry) {
            aTerms.push_back(RotVarTerm(GAXSKVariable::kCarry));
        }
        if (aUpdate.mUseXor) {
            pStatements->push_back(
                XorStatement(aUpdate.mTarget, aTerms));
        } else {
            pStatements->push_back(
                AddStatement(aUpdate.mTarget, aTerms));
        }
    }
}

void GAXSKModel::AppendOrbiterRoundStatements(
    const GAXSKModelOrbiterRound &pRound,
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

GAXSKModel GAXSKModel::MakeOrbiterPlan(
    std::span<const GAXSKModelOrbiterRound> pRounds,
    std::span<const GAXSKModelOrbiterAssignment> pAssignments,
    std::span<const GAXSKModelWandererUpdate> pUpdates) {
    GAXSKModel aResult;
    if ((pRounds.size() != 11U) ||
        (pAssignments.size() != 11U) ||
        (pUpdates.size() != 11U)) {
        return aResult;
    }

    aResult.mOrbiters = {
        GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB,
        GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD,
        GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitF,
        GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitH,
        GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitJ,
        GAXSKVariable::kOrbitK,
    };
    aResult.mWanderers = {
        GAXSKVariable::kWandererA, GAXSKVariable::kWandererB,
        GAXSKVariable::kWandererC, GAXSKVariable::kWandererD,
        GAXSKVariable::kWandererE, GAXSKVariable::kWandererF,
        GAXSKVariable::kWandererG, GAXSKVariable::kWandererH,
        GAXSKVariable::kWandererI, GAXSKVariable::kWandererJ,
        GAXSKVariable::kWandererK,
    };

    AppendOrbiterAssignStatements(pAssignments,
                                  0,
                                  &aResult.mStatements);

    int aHotIndex = static_cast<int>(aResult.mOrbiters.size());
    for (const GAXSKModelOrbiterRound &aRound : pRounds) {
        AppendOrbiterRoundStatements(aRound,
                                     aHotIndex,
                                     &aResult.mStatements);
        aHotIndex += 2;
    }

    AppendWandererUpdateStatements(pUpdates,
                                   &aResult.mStatements);
    return aResult;
}
