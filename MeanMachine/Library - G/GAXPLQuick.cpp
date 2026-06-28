//
//  GAXPLQuick.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#include "GAX.hpp"
#include "Random.hpp"

GExpr GAXPLQuick::Rotate(const GExpr &pExpr, int pRotation) {
    if (pExpr.IsInvalid()) {
        return GExpr();
    }

    if (pRotation < 0) {
        return pExpr;
    }

    if (pRotation > 63) {
        return GExpr();
    }

    return GQuick::RotL64(pExpr, pRotation);
}

GExpr GAXPLQuick::RotateSymbol(const GSymbol &pSymbol, int pRotation) {
    if (pSymbol.IsInvalid()) {
        return GExpr();
    }
    return Rotate(GExpr::Symbol(pSymbol), pRotation);
}

GExpr GAXPLQuick::Diffuse(const GExpr &pExpr, GAXSKDiffuseKind pDiffuse) {
    if (pExpr.IsInvalid()) {
        return GExpr();
    }

    switch (pDiffuse) {
        case GAXSKDiffuseKind::kDiffuseA:
            return GExpr::Diffuse64A(pExpr);

        case GAXSKDiffuseKind::kDiffuseB:
            return GExpr::Diffuse64B(pExpr);

        case GAXSKDiffuseKind::kDiffuseC:
            return GExpr::Diffuse64C(pExpr);

        default:
            return GExpr();
    }
}

GExpr GAXPLQuick::DiffuseAndXor(const GExpr &pExpr,
                                const GExpr &pXor,
                                GAXSKDiffuseKind pDiffuse) {
    if (pExpr.IsInvalid() || pXor.IsInvalid()) {
        return GExpr();
    }
    return Diffuse(GExpr::Xor(pExpr, pXor), pDiffuse);
}

GSymbol GAXPLQuick::DomainConstantIngress() {
    return GSymbol::Var(TwistVariable::kDomainWordIngress);
}

GSymbol GAXPLQuick::DomainConstantScatter() {
    return GSymbol::Var(TwistVariable::kDomainWordScatter);
}

GSymbol GAXPLQuick::DomainConstantCross() {
    return GSymbol::Var(TwistVariable::kDomainWordCross);
}

bool GAXPLQuick::BakeInputSlotWord(const GAXSKInputSlot &pSlot,
                                   const std::unordered_map<GAXSKSourceKind, GSymbol> &pSourceMap,
                                   const std::unordered_map<GAXSKNonceByteKind, GSymbol> &pNonceMap,
                                   GExpr *pExpr,
                                   int pOffsetRangeLo,
                                   int pOffsetRangeHi,
                                   std::string *pErrorMessage) {
    
    GSymbol aLoopIndex = GSymbol::Var(TwistVariable::kIndex);
    
    if (pExpr == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWord received null expression";
        }
        return false;
    }

    *pExpr = GExpr();

    if (pSlot.mRotation < 0 || pSlot.mRotation > 63) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWord received invalid rotation";
        }
        return false;
    }

    if (pSlot.mKind == GAXSKInputSlotKind::kNonceByte) {
        const auto aIterator = pNonceMap.find(pSlot.mNonceByte);

        if (aIterator == pNonceMap.end()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GAXPLQuick::BakeInputSlotWord could not bind nonce byte";
            }
            return false;
        }

        if (aIterator->second.IsInvalid()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GAXPLQuick::BakeInputSlotWord nonce byte symbol is invalid";
            }
            return false;
        }

        *pExpr = GExpr::Symbol(aIterator->second);

        if (pExpr->IsInvalid()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GAXPLQuick::BakeInputSlotWord failed to build nonce byte";
            }
            return false;
        }

        return true;
    }

    if (pSlot.mKind == GAXSKInputSlotKind::kSource) {
        const auto aIterator = pSourceMap.find(pSlot.mSource);

        if (aIterator == pSourceMap.end()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GAXPLQuick::BakeInputSlotWord could not bind source";
            }
            return false;
        }

        if (aIterator->second.IsInvalid()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GAXPLQuick::BakeInputSlotWord source symbol is invalid";
            }
            return false;
        }

        GExpr aRead = GQuick::MakeReadBufferOffsetExpressionDirected(aIterator->second, aLoopIndex, pSlot.mReverse, Random::Get(pOffsetRangeLo, pOffsetRangeHi));

        if (aRead.IsInvalid()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GAXPLQuick::BakeInputSlotWord failed to read source";
            }
            return false;
        }

        *pExpr = Rotate(aRead, pSlot.mRotation);

        if (pExpr->IsInvalid()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GAXPLQuick::BakeInputSlotWord failed to rotate source";
            }
            return false;
        }

        return true;
    }

    if (pErrorMessage != nullptr) {
        *pErrorMessage = "GAXPLQuick::BakeInputSlotWord received invalid input slot kind";
    }
    return false;
}

bool GAXPLQuick::BakeInputSlotWordsXorSources(const std::vector<GAXSKInputSlot> &pInputs,
                                              const std::unordered_map<GAXSKSourceKind, GSymbol> &pSourceMap,
                                              const std::unordered_map<GAXSKNonceByteKind, GSymbol> &pNonceMap,
                                              GExpr *pExpr,
                                              int pOffsetRangeLo,
                                              int pOffsetRangeHi,
    std::string *pErrorMessage) {

    if (pExpr == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWordsXorSources received null expression";
        }
        return false;
    }

    std::vector<GExpr> aTerms;

    for (const GAXSKInputSlot &aSlot : pInputs) {
        if (aSlot.mKind != GAXSKInputSlotKind::kSource) {
            continue;
        }

        GExpr aWord;
        if (!BakeInputSlotWord(aSlot, pSourceMap, pNonceMap, &aWord, pOffsetRangeLo, pOffsetRangeHi, pErrorMessage)) {
            return false;
        }

        aTerms.push_back(aWord);
    }

    if (aTerms.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWordsXorSources found no source terms";
        }
        return false;
    }

    *pExpr = GQuick::XorChain(aTerms);
    return !pExpr->IsInvalid();
}


bool GAXPLQuick::BakeInputSlotWordsXorNonces(
    const std::vector<GAXSKInputSlot> &pInputs,
    const std::unordered_map<GAXSKSourceKind, GSymbol> &pSourceMap,
    const std::unordered_map<GAXSKNonceByteKind, GSymbol> &pNonceMap,
    GExpr *pExpr,
    std::string *pErrorMessage) {

    if (pExpr == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWordsXorNonces received null expression";
        }
        return false;
    }

    std::vector<const GAXSKInputSlot *> aNonceSlots;

    for (const GAXSKInputSlot &aSlot : pInputs) {
        if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
            continue;
        }

        aNonceSlots.push_back(&aSlot);
    }

    if (aNonceSlots.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWordsXorNonces found no nonce terms";
        }
        return false;
    }

    const int aNonceIndex = Random::Get(static_cast<int>(aNonceSlots.size()));
    if (!BakeInputSlotWord(*aNonceSlots[static_cast<std::size_t>(aNonceIndex)],
                           pSourceMap,
                           pNonceMap,
                           pExpr,
                           0,
                           0,
                           pErrorMessage)) {
        return false;
    }

    return !pExpr->IsInvalid();
}
