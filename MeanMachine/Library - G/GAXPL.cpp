//
//  GAXPL.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#include "GAXPL.hpp"
#include "TwistArray.hpp"
#include "GAXPLQuick.hpp"

namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

}

void GAXPL::Reset() {
    mSkeleton = nullptr;
    mLoop = nullptr;

    mSaltsOrbiterAssign.clear();
    mSaltsOrbiterUpdate.clear();
    mSaltsWandererUpdate.clear();

    mNonceBytes.clear();
    mSources.clear();
    mOrbiters.clear();
    mWanderers.clear();

    mSourceMap.clear();
    mNonceMap.clear();
    mOrbiterMap.clear();
    mWandererMap.clear();
}

bool GAXPL::Configure(const GAXSKSkeleton *pSkeleton,
                 const GAXPLSaltBag &pSaltBag,
                 const std::vector<GSymbol> &pNonceBytes,
                 const std::vector<GSymbol> &pSources,
                 const std::vector<GSymbol> &pOrbiters,
                 const std::vector<GSymbol> &pWanderers,
                 GLoop *pLoop,
                 std::string *pErrorMessage) {
    
    Reset();
    
    if (pSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::Configure received null skeleton");
        return false;
    }

    if (pLoop == nullptr) {
        SetError(pErrorMessage, "GAXPL::Configure received null loop");
        return false;
    }
    
    mSkeleton = pSkeleton;
    mLoop = pLoop;
    
    TwistArray::Replace(&mSaltsOrbiterAssign, &(pSaltBag.mOrbiterAssign));
    TwistArray::Replace(&mSaltsOrbiterUpdate, &(pSaltBag.mOrbiterUpdate));
    TwistArray::Replace(&mSaltsWandererUpdate, &(pSaltBag.mWandererUpdate));
    TwistArray::Replace(&mNonceBytes, &(pNonceBytes));
    TwistArray::Replace(&mSources, &(pSources));
    TwistArray::Replace(&mOrbiters, &(pOrbiters));
    TwistArray::Replace(&mWanderers, &(pWanderers));
    
    if (!BuildSourceMap(pErrorMessage)) { return false; }
    if (!BuildNonceMap(pErrorMessage)) { return false; }
    if (!BuildOrbiterMap(pErrorMessage)) { return false; }
    if (!BuildWandererMap(pErrorMessage)) { return false; }
    
    return true;
}


bool GAXPL::Bake(const GAXSKSkeleton *pSkeleton,
                 const GAXPLSaltBag &pSaltBag,
                 const std::vector<GSymbol> &pNonceBytes,
                 const std::vector<GSymbol> &pSources,
                 const std::vector<GSymbol> &pOrbiters,
                 const std::vector<GSymbol> &pWanderers,
                 GLoop *pLoop,
                 std::string *pErrorMessage) {
    if (!Configure(pSkeleton, pSaltBag, pNonceBytes, pSources,
                   pOrbiters, pWanderers, pLoop, pErrorMessage)) {
        return false;
    }
    
    if (!GenerateStatements(pErrorMessage)) { return false; }
    
    return true;
}

int GAXPL::GetOrbiterIndex(GAXSKVariable pVariable) const {
    switch (pVariable) {
        case GAXSKVariable::kOrbitA: return 0;
        case GAXSKVariable::kOrbitB: return 1;
        case GAXSKVariable::kOrbitC: return 2;
        case GAXSKVariable::kOrbitD: return 3;
        case GAXSKVariable::kOrbitE: return 4;
        case GAXSKVariable::kOrbitF: return 5;
        case GAXSKVariable::kOrbitG: return 6;
        case GAXSKVariable::kOrbitH: return 7;
        case GAXSKVariable::kOrbitI: return 8;
        case GAXSKVariable::kOrbitJ: return 9;
        case GAXSKVariable::kOrbitK: return 10;
        default: return -1;
    }
}

int GAXPL::GetWandererIndex(GAXSKVariable pVariable) const {
    switch (pVariable) {
        case GAXSKVariable::kWandererA: return 0;
        case GAXSKVariable::kWandererB: return 1;
        case GAXSKVariable::kWandererC: return 2;
        case GAXSKVariable::kWandererD: return 3;
        case GAXSKVariable::kWandererE: return 4;
        case GAXSKVariable::kWandererF: return 5;
        case GAXSKVariable::kWandererG: return 6;
        case GAXSKVariable::kWandererH: return 7;
        case GAXSKVariable::kWandererI: return 8;
        case GAXSKVariable::kWandererJ: return 9;
        case GAXSKVariable::kWandererK: return 10;
        default: return -1;
    }
}

int GAXPL::GetNonceByteIndex(GAXSKNonceByteKind pNonce) const {
    switch (pNonce) {
        case GAXSKNonceByteKind::kNonceA: return 0;
        case GAXSKNonceByteKind::kNonceB: return 1;
        case GAXSKNonceByteKind::kNonceC: return 2;
        case GAXSKNonceByteKind::kNonceD: return 3;
        case GAXSKNonceByteKind::kNonceE: return 4;
        case GAXSKNonceByteKind::kNonceF: return 5;
        case GAXSKNonceByteKind::kNonceG: return 6;
        case GAXSKNonceByteKind::kNonceH: return 7;
        default: return -1;
    }
}

int GAXPL::GetSourceIndex(GAXSKSourceKind pSource) const {
    switch (pSource) {
        case GAXSKSourceKind::kSourceA: return 0;
        case GAXSKSourceKind::kSourceB: return 1;
        case GAXSKSourceKind::kSourceC: return 2;
        case GAXSKSourceKind::kSourceD: return 3;
        default: return -1;
    }
}

GAXSKVariable GAXPL::GetOrbiterVariableForIndex(int pIndex) const {
    switch (pIndex) {
        case 0: return GAXSKVariable::kOrbitA;
        case 1: return GAXSKVariable::kOrbitB;
        case 2: return GAXSKVariable::kOrbitC;
        case 3: return GAXSKVariable::kOrbitD;
        case 4: return GAXSKVariable::kOrbitE;
        case 5: return GAXSKVariable::kOrbitF;
        case 6: return GAXSKVariable::kOrbitG;
        case 7: return GAXSKVariable::kOrbitH;
        case 8: return GAXSKVariable::kOrbitI;
        case 9: return GAXSKVariable::kOrbitJ;
        case 10: return GAXSKVariable::kOrbitK;
        default: return GAXSKVariable::kInvalid;
    }
}

GAXSKVariable GAXPL::GetWandererVariableForIndex(int pIndex) const {
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

bool GAXPL::BuildSourceMap(std::string *pErrorMessage) {
    mSourceMap.clear();

    if (mSkeleton == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPL::BuildSourceMap has null skeleton";
        }
        return false;
    }

    for (const GAXSKStatement &aStatement : mSkeleton->mStatements) {
        if (aStatement.mKind != GAXSKStatementKind::kContextWordAssign) {
            continue;
        }

        const GAXSKContextWordPlan &aPlan = aStatement.mContextWord;

        for (const GAXSKInputSlot &aSlot : aPlan.mSlots) {
            if (aSlot.mKind != GAXSKInputSlotKind::kSource) {
                continue;
            }

            const int aSourceIndex = GetSourceIndex(aSlot.mSource);
            if (aSourceIndex < 0) {
                SetError(pErrorMessage, "GAXPL::BuildSourceMap found invalid source kind");
                return false;
            }

            if (static_cast<std::size_t>(aSourceIndex) >= mSources.size()) {
                SetError(pErrorMessage, "GAXPL::BuildSourceMap could not bind skeleton source");
                return false;
            }

            if (mSources[static_cast<std::size_t>(aSourceIndex)].IsInvalid()) {
                SetError(pErrorMessage, "GAXPL::BuildSourceMap source symbol is invalid");
                return false;
            }

            mSourceMap[aSlot.mSource] = mSources[static_cast<std::size_t>(aSourceIndex)];
        }
    }

    return true;
}

bool GAXPL::BuildNonceMap(std::string *pErrorMessage) {
    mNonceMap.clear();

    if (mSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::BuildNonceMap has null skeleton");
        return false;
    }

    for (const GAXSKStatement &aStatement : mSkeleton->mStatements) {
        if (aStatement.mKind != GAXSKStatementKind::kContextWordAssign) {
            continue;
        }

        const GAXSKContextWordPlan &aPlan = aStatement.mContextWord;

        for (const GAXSKInputSlot &aSlot : aPlan.mSlots) {
            if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
                continue;
            }

            const int aNonceIndex = GetNonceByteIndex(aSlot.mNonceByte);
            if (aNonceIndex < 0) {
                SetError(pErrorMessage, "GAXPL::BuildNonceMap found invalid nonce byte kind");
                return false;
            }

            if (static_cast<std::size_t>(aNonceIndex) >= mNonceBytes.size()) {
                SetError(pErrorMessage, "GAXPL::BuildNonceMap could not bind skeleton nonce byte");
                return false;
            }

            if (mNonceBytes[static_cast<std::size_t>(aNonceIndex)].IsInvalid()) {
                SetError(pErrorMessage, "GAXPL::BuildNonceMap nonce byte symbol is invalid");
                return false;
            }

            mNonceMap[aSlot.mNonceByte] = mNonceBytes[static_cast<std::size_t>(aNonceIndex)];
        }
    }

    return true;
}

bool GAXPL::BuildOrbiterMap(std::string *pErrorMessage) {
    mOrbiterMap.clear();

    for (std::size_t aIndex = 0; aIndex < mOrbiters.size(); ++aIndex) {
        const GAXSKVariable aVariable = GetOrbiterVariableForIndex(static_cast<int>(aIndex));
        if (aVariable == GAXSKVariable::kInvalid) {
            SetError(pErrorMessage, "GAXPL::BuildOrbiterMap received too many orbiters");
            return false;
        }

        if (mOrbiters[aIndex].IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildOrbiterMap orbiter symbol is invalid");
            return false;
        }

        mOrbiterMap[aVariable] = mOrbiters[aIndex];
    }

    return true;
}

bool GAXPL::BuildWandererMap(std::string *pErrorMessage) {
    mWandererMap.clear();

    for (std::size_t aIndex = 0; aIndex < mWanderers.size(); ++aIndex) {
        const GAXSKVariable aVariable = GetWandererVariableForIndex(static_cast<int>(aIndex));
        if (aVariable == GAXSKVariable::kInvalid) {
            SetError(pErrorMessage, "GAXPL::BuildWandererMap received too many wanderers");
            return false;
        }

        if (mWanderers[aIndex].IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildWandererMap wanderer symbol is invalid");
            return false;
        }

        mWandererMap[aVariable] = mWanderers[aIndex];
    }

    return true;
}

bool GAXPL::SymbolForVariable(GAXSKVariable pVariable,
                              GSymbol *pResult,
                              std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXPL::SymbolForVariable received null result");
        return false;
    }

    *pResult = GSymbol();

    switch (pVariable) {
        case GAXSKVariable::kIngress:
            *pResult = GSymbol::Var(TwistVariable::kIngress);
            break;
        case GAXSKVariable::kCross:
            *pResult = GSymbol::Var(TwistVariable::kCross);
            break;
        case GAXSKVariable::kPrevious:
            *pResult = GSymbol::Var(TwistVariable::kPrevious);
            break;
        case GAXSKVariable::kScatter:
            *pResult = GSymbol::Var(TwistVariable::kScatter);
            break;
        case GAXSKVariable::kCarry:
            *pResult = GSymbol::Var(TwistVariable::kCarry);
            break;
        default:
            if (GetOrbiterIndex(pVariable) >= 0) {
                const auto aIterator = mOrbiterMap.find(pVariable);
                if (aIterator == mOrbiterMap.end()) {
                    SetError(pErrorMessage, "GAXPL::SymbolForVariable could not bind orbiter");
                    return false;
                }
                *pResult = aIterator->second;
            } else if (GetWandererIndex(pVariable) >= 0) {
                const auto aIterator = mWandererMap.find(pVariable);
                if (aIterator == mWandererMap.end()) {
                    SetError(pErrorMessage, "GAXPL::SymbolForVariable could not bind wanderer");
                    return false;
                }
                *pResult = aIterator->second;
            } else {
                SetError(pErrorMessage, "GAXPL::SymbolForVariable received invalid variable");
                return false;
            }
            break;
    }

    if (pResult->IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::SymbolForVariable produced invalid symbol");
        return false;
    }

    return true;
}

bool GAXPL::GeneratePreviousAssignStatement(const GAXSKStatement &pStatement,
                                            std::vector<GStatement> *pStatements,
                                            std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GeneratePreviousAssignStatement received null statements");
        return false;
    }
    GSymbol aTarget;
    if (!SymbolForVariable(pStatement.mTarget, &aTarget, pErrorMessage)) {
        return false;
    }
    GSymbol aSource;
    if (!SymbolForVariable(pStatement.mSource, &aSource, pErrorMessage)) {
        return false;
    }
    pStatements->push_back(GStatement::Comment(""));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget), GExpr::Symbol(aSource)));
    return true;
}

bool GAXPL::GenerateContextWordStatement(const GAXSKStatement &pStatement,
                                         std::vector<GStatement> *pStatements,
                                         std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateContextWordStatement received null statements");
        return false;
    }
    
    const GAXSKContextWordPlan &aPlan = pStatement.mContextWord;
    
    GSymbol aTarget;
    if (!SymbolForVariable(aPlan.mTarget, &aTarget, pErrorMessage)) {
        return false;
    }
    
    pStatements->push_back(GStatement::Comment(""));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget), GExpr::Const(0)));
    
    {
        GExpr aExpr;
        if (!GAXPLQuick::BakeInputSlotWordsXorNonces(aPlan.mSlots,
                                                     mSourceMap,
                                                     mNonceMap,
                                                     &aExpr,
                                                     pErrorMessage)) {
            return false;
        }
        
        pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget),
                                                  GExpr::Xor(GExpr::Symbol(aTarget), aExpr)));
    }
    
    {
        GExpr aExpr;
        if (!GAXPLQuick::BakeInputSlotWordsXorSources(aPlan.mSlots,
                                                      mSourceMap,
                                                      mNonceMap,
                                                      &aExpr,
                                                      pErrorMessage)) {
            return false;
        }
        
        pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget),
                                                  GExpr::Xor(GExpr::Symbol(aTarget), aExpr)));
    }
    
    GExpr aDiffuse;
    
    if (aPlan.mHasDomainMix) {
        GSymbol aDomainWord;
        
        if (aPlan.mIsIngress == true) {
            aDomainWord = GAXPLQuick::DomainConstantIngress();
        } else {
            aDomainWord = GAXPLQuick::DomainConstantCross();
        }
        
        aDiffuse = GAXPLQuick::DiffuseAndXor(GExpr::Symbol(aTarget),
                                             GExpr::Symbol(aDomainWord),
                                             aPlan.mDiffuse);
    } else {
        aDiffuse = GAXPLQuick::Diffuse(GExpr::Symbol(aTarget),
                                       aPlan.mDiffuse);
    }
    
    if (aDiffuse.IsInvalid()) {
        SetError(pErrorMessage,
                 "GAXPL::GenerateContextWordStatement failed to diffuse context word");
        return false;
    }
    
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget),
                                              aDiffuse));
    
    return true;
}

bool GAXPL::GenerateScatterMixStatement(const GAXSKStatement &pStatement,
                                        std::vector<GStatement> *pStatements,
                                        std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement received null statements");
        return false;
    }

    const GAXSKScatterMixPlan &aPlan = pStatement.mScatterMix;

    GSymbol aTarget;
    if (!SymbolForVariable(aPlan.mTarget, &aTarget, pErrorMessage)) {
        return false;
    }

    std::vector<GExpr> aXorTerms;
    for (const GAXSKVariableTerm &aTerm : aPlan.mXorTerms) {
        GSymbol aSymbol;
        if (!SymbolForVariable(aTerm.mVariable, &aSymbol, pErrorMessage)) {
            return false;
        }

        GExpr aExpr = GAXPLQuick::RotateSymbol(aSymbol, aTerm.mRotation);
        if (aExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement failed to build xor term");
            return false;
        }

        aXorTerms.push_back(aExpr);
    }

    std::vector<GExpr> aAddTerms;
    for (const GAXSKVariableTerm &aTerm : aPlan.mAddTerms) {
        GSymbol aSymbol;
        if (!SymbolForVariable(aTerm.mVariable, &aSymbol, pErrorMessage)) {
            return false;
        }

        GExpr aExpr = GAXPLQuick::RotateSymbol(aSymbol, aTerm.mRotation);
        if (aExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement failed to build add term");
            return false;
        }

        aAddTerms.push_back(aExpr);
    }

    if (aXorTerms.empty()) {
        SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement received no xor terms");
        return false;
    }

    if (aAddTerms.empty()) {
        SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement received no add terms");
        return false;
    }

    GExpr aExpr = GExpr::Add(GQuick::XorChain(aXorTerms),
                             GQuick::XorChain(aAddTerms));

    if (aPlan.mHasDomainMix) {
        GSymbol aDomainWord = GAXPLQuick::DomainConstantScatter();

        if (aDomainWord.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement produced invalid domain word");
            return false;
        }

        aExpr = GExpr::Xor(aExpr, GExpr::Symbol(aDomainWord));
    }

    aExpr = GAXPLQuick::Diffuse(aExpr, aPlan.mDiffuse);

    if (aExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement failed to diffuse scatter");
        return false;
    }

    pStatements->push_back(GStatement::Comment(""));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget), aExpr));

    return true;
}

bool GAXPL::GenerateStatements(std::string *pErrorMessage) {
    if (mLoop == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateStatements received null loop");
        return false;
    }

    if (mSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateStatements received null skeleton");
        return false;
    }

    std::vector<GStatement> aStatements;

    for (const GAXSKStatement &aSkeletonStatement : mSkeleton->mStatements) {
        if (aSkeletonStatement.mKind == GAXSKStatementKind::kPreviousAssign) {
            if (!GeneratePreviousAssignStatement(aSkeletonStatement,
                                                 &aStatements,
                                                 pErrorMessage)) {
                return false;
            }
            continue;
        }

        if (aSkeletonStatement.mKind == GAXSKStatementKind::kContextWordAssign) {
            if (!GenerateContextWordStatement(aSkeletonStatement,
                                              &aStatements,
                                              pErrorMessage)) {
                return false;
            }
            continue;
        }
        
        if (aSkeletonStatement.mKind == GAXSKStatementKind::kScatterMix) {
            if (!GenerateScatterMixStatement(aSkeletonStatement,
                                             &aStatements,
                                             pErrorMessage)) {
                return false;
            }
            continue;
        }
        
        SetError(pErrorMessage,
                 "GAXPL::GenerateStatements unsupported statement kind: " +
                 std::to_string(static_cast<int>(aSkeletonStatement.mKind)));
        return false;
    }

    mLoop->AddBody(&aStatements);
    return true;
}
