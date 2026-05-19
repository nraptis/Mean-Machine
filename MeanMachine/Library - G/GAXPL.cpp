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
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPL::Bake received null skeleton";
        }
        return false;
    }
    
    if (pLoop == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPL::Bake received null loop";
        }
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
    
    
    if (!GenerateIngressStatements(pErrorMessage)) { return false; }
    
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
    
    if (!Configure(pSkeleton,
                   pSaltBag,
                   pNonceBytes,
                   pSources,
                   pOrbiters,
                   pWanderers,
                   pLoop,
                   pErrorMessage)) {
        return false;
    }
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

        default:
            return -1;
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

        default:
            return -1;
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

        default:
            return -1;
    }
}

int GAXPL::GetSourceIndex(GAXSKSourceKind pSource) const {
    switch (pSource) {
        case GAXSKSourceKind::kSourceA: return 0;
        case GAXSKSourceKind::kSourceB: return 1;
        case GAXSKSourceKind::kSourceC: return 2;
        case GAXSKSourceKind::kSourceD: return 3;

        default:
            return -1;
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

        for (const GAXSKInputSlot &aSlot : aPlan.mXorSlots) {
            if (aSlot.mKind != GAXSKInputSlotKind::kSource) {
                continue;
            }

            const int aSourceIndex = GetSourceIndex(aSlot.mSource);
            if (aSourceIndex < 0) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildSourceMap found invalid source kind";
                }
                return false;
            }

            if (static_cast<std::size_t>(aSourceIndex) >= mSources.size()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildSourceMap could not bind skeleton source";
                }
                return false;
            }

            if (mSources[static_cast<std::size_t>(aSourceIndex)].IsInvalid()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildSourceMap source symbol is invalid";
                }
                return false;
            }

            mSourceMap[aSlot.mSource] = mSources[static_cast<std::size_t>(aSourceIndex)];
        }

        for (const GAXSKInputSlot &aSlot : aPlan.mAddXorSlots) {
            if (aSlot.mKind != GAXSKInputSlotKind::kSource) {
                continue;
            }

            const int aSourceIndex = GetSourceIndex(aSlot.mSource);
            if (aSourceIndex < 0) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildSourceMap found invalid source kind";
                }
                return false;
            }

            if (static_cast<std::size_t>(aSourceIndex) >= mSources.size()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildSourceMap could not bind skeleton source";
                }
                return false;
            }

            if (mSources[static_cast<std::size_t>(aSourceIndex)].IsInvalid()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildSourceMap source symbol is invalid";
                }
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
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPL::BuildNonceMap has null skeleton";
        }
        return false;
    }

    for (const GAXSKStatement &aStatement : mSkeleton->mStatements) {
        if (aStatement.mKind != GAXSKStatementKind::kContextWordAssign) {
            continue;
        }

        const GAXSKContextWordPlan &aPlan = aStatement.mContextWord;

        for (const GAXSKInputSlot &aSlot : aPlan.mXorSlots) {
            if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
                continue;
            }

            const int aNonceIndex = GetNonceByteIndex(aSlot.mNonceByte);
            if (aNonceIndex < 0) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildNonceMap found invalid nonce byte kind";
                }
                return false;
            }

            if (static_cast<std::size_t>(aNonceIndex) >= mNonceBytes.size()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildNonceMap could not bind skeleton nonce byte";
                }
                return false;
            }

            if (mNonceBytes[static_cast<std::size_t>(aNonceIndex)].IsInvalid()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildNonceMap nonce byte symbol is invalid";
                }
                return false;
            }

            mNonceMap[aSlot.mNonceByte] = mNonceBytes[static_cast<std::size_t>(aNonceIndex)];
        }

        for (const GAXSKInputSlot &aSlot : aPlan.mAddXorSlots) {
            if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
                continue;
            }

            const int aNonceIndex = GetNonceByteIndex(aSlot.mNonceByte);
            if (aNonceIndex < 0) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildNonceMap found invalid nonce byte kind";
                }
                return false;
            }

            if (static_cast<std::size_t>(aNonceIndex) >= mNonceBytes.size()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildNonceMap could not bind skeleton nonce byte";
                }
                return false;
            }

            if (mNonceBytes[static_cast<std::size_t>(aNonceIndex)].IsInvalid()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GAXPL::BuildNonceMap nonce byte symbol is invalid";
                }
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

GSymbol GAXPL::SymbolForVariable(GAXSKVariable pVariable,
                                  std::string *pErrorMessage) const {
    switch (pVariable) {
        case GAXSKVariable::kIngress: return GSymbol::Var("aIngress");
        case GAXSKVariable::kCross: return GSymbol::Var("aCross");
        case GAXSKVariable::kPrevious: return GSymbol::Var("aPrevious");
        case GAXSKVariable::kScatter: return GSymbol::Var("aScatter");
        case GAXSKVariable::kCarry: return GSymbol::Var("aCarry");
        default:
            break;
    }

    const int aOrbiterIndex = GetOrbiterIndex(pVariable);
    if (aOrbiterIndex >= 0) {
        const auto aIterator = mOrbiterMap.find(pVariable);
        if (aIterator != mOrbiterMap.end() && !aIterator->second.IsInvalid()) {
            return aIterator->second;
        }
        SetError(pErrorMessage, "GAXPL::SymbolForVariable could not bind orbiter");
        return GSymbol();
    }

    const int aWandererIndex = GetWandererIndex(pVariable);
    if (aWandererIndex >= 0) {
        const auto aIterator = mWandererMap.find(pVariable);
        if (aIterator != mWandererMap.end() && !aIterator->second.IsInvalid()) {
            return aIterator->second;
        }
        SetError(pErrorMessage, "GAXPL::SymbolForVariable could not bind wanderer");
        return GSymbol();
    }

    SetError(pErrorMessage, "GAXPL::SymbolForVariable received invalid variable");
    return GSymbol();
}

bool GAXPL::GeneratePreviousAssignStatement(const GAXSKStatement &pStatement,
                                            std::vector<GStatement> *pStatements,
                                            std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GeneratePreviousAssignStatement received null statements");
        return false;
    }

    const GSymbol aTarget = SymbolForVariable(pStatement.mTarget, pErrorMessage);
    const GSymbol aSource = SymbolForVariable(pStatement.mSource, pErrorMessage);

    if (aTarget.IsInvalid() || aSource.IsInvalid()) {
        return false;
    }

    pStatements->push_back(
        GStatement::Assign(GTarget::Symbol(aTarget),
                           GExpr::Symbol(aSource))
    );

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
    
    const GSymbol aTarget = SymbolForVariable(aPlan.mTarget, pErrorMessage);
    if (aTarget.IsInvalid()) {
        return false;
    }
    
    if (aPlan.mTarget == GAXSKVariable::kIngress) {
        pStatements->push_back(GStatement::Comment("ingress word"));
    } else if (aPlan.mTarget == GAXSKVariable::kCross) {
        pStatements->push_back(GStatement::Comment("cross word"));
    } else {
        pStatements->push_back(GStatement::Comment("context word"));
    }
    
    pStatements->push_back(
                           GStatement::Assign(GTarget::Symbol(aTarget),
                                              GExpr::Const(0))
                           );
    
    if (GAXPLQuick::InputsRequireXorNonces(aPlan.mXorSlots)) {
        GExpr aExpr;
        if (!GAXPLQuick::BakeInputSlotWordsXorNonces(aPlan.mXorSlots,
                                                     mSourceMap,
                                                     mNonceMap,
                                                     &aExpr,
                                                     pErrorMessage)) {
            return false;
        }
        
        pStatements->push_back(
                               GStatement::Assign(
                                                  GTarget::Symbol(aTarget),
                                                  GExpr::Xor(GExpr::Symbol(aTarget), aExpr)
                                                  )
                               );
    }
    
    if (GAXPLQuick::InputsRequireXorSources(aPlan.mXorSlots)) {
        GExpr aExpr;
        if (!GAXPLQuick::BakeInputSlotWordsXorSources(aPlan.mXorSlots,
                                                      mSourceMap,
                                                      mNonceMap,
                                                      &aExpr,
                                                      pErrorMessage)) {
            return false;
        }
        
        pStatements->push_back(
                               GStatement::Assign(
                                                  GTarget::Symbol(aTarget),
                                                  GExpr::Xor(GExpr::Symbol(aTarget), aExpr)
                                                  )
                               );
    }
    
    if (GAXPLQuick::InputsRequireAddNonces(aPlan.mAddXorSlots)) {
        GExpr aExpr;
        if (!GAXPLQuick::BakeInputSlotWordsAddNonces(aPlan.mAddXorSlots,
                                                     mSourceMap,
                                                     mNonceMap,
                                                     &aExpr,
                                                     pErrorMessage)) {
            return false;
        }
        
        pStatements->push_back(
                               GStatement::Assign(
                                                  GTarget::Symbol(aTarget),
                                                  GExpr::Add(GExpr::Symbol(aTarget), aExpr)
                                                  )
                               );
    }
    
    if (GAXPLQuick::InputsRequireAddSources(aPlan.mAddXorSlots)) {
        GExpr aExpr;
        if (!GAXPLQuick::BakeInputSlotWordsAddSources(aPlan.mAddXorSlots,
                                                      mSourceMap,
                                                      mNonceMap,
                                                      &aExpr,
                                                      pErrorMessage)) {
            return false;
        }
        
        pStatements->push_back(
                               GStatement::Assign(
                                                  GTarget::Symbol(aTarget),
                                                  GExpr::Add(GExpr::Symbol(aTarget), aExpr)
                                                  )
                               );
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
    
    pStatements->push_back(
                           GStatement::Assign(GTarget::Symbol(aTarget),
                                              aDiffuse)
                           );
    
    return true;
}

bool GAXPL::GenerateIngressStatements(std::string *pErrorMessage) {
    if (mLoop == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateIngressStatements received null loop");
        return false;
    }

    if (mSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateIngressStatements received null skeleton");
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
    }

    mLoop->AddBody(&aStatements);
    return true;
}

/*
bool GAXPL::GenerateIngressStatements(std::string *pErrorMessage) {
    if (mLoop == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateIngressStatements received null loop");
        return false;
    }

    if (mSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateIngressStatements received null skeleton");
        return false;
    }

    std::vector<GStatement> aStatements;

    for (const GAXSKStatement &aSkeletonStatement : mSkeleton->mStatements) {
        if (aSkeletonStatement.mKind == GAXSKStatementKind::kPreviousAssign) {
            const GSymbol aTarget = SymbolForVariable(aSkeletonStatement.mTarget,
                                                      pErrorMessage);
            const GSymbol aSource = SymbolForVariable(aSkeletonStatement.mSource,
                                                      pErrorMessage);
            if (aTarget.IsInvalid() || aSource.IsInvalid()) {
                return false;
            }

            aStatements.push_back(
                GStatement::Assign(GTarget::Symbol(aTarget),
                                   GExpr::Symbol(aSource))
            );
            continue;
        }

        if (aSkeletonStatement.mKind == GAXSKStatementKind::kContextWordAssign) {
            const GSymbol aTarget = SymbolForVariable(aSkeletonStatement.mTarget,
                                                      pErrorMessage);
            if (aTarget.IsInvalid()) {
                return false;
            }

            const GExpr aExpr = BuildContextExpr(aSkeletonStatement.mContextWord,
                                                 pErrorMessage);
            if (aExpr.IsInvalid()) {
                return false;
            }

            aStatements.push_back(
                GStatement::Assign(GTarget::Symbol(aTarget), aExpr)
            );
        }
    }

    mLoop->AddBody(&aStatements);
    return true;
}
*/
