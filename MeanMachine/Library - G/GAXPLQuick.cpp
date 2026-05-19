//
//  GAXPLQuick.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#include "GAXPLQuick.hpp"


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

GExpr GAXPLQuick::Diffuse(const GExpr &pExpr, GAXSKDiffuseKind pDiffuse) {
    if (pExpr.IsInvalid()) {
        return GExpr();
    }

    switch (pDiffuse) {
        case GAXSKDiffuseKind::kDiffuseA:
            return GExpr::DiffuseA(pExpr);

        case GAXSKDiffuseKind::kDiffuseB:
            return GExpr::DiffuseB(pExpr);

        case GAXSKDiffuseKind::kDiffuseC:
            return GExpr::DiffuseC(pExpr);

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

        *pExpr = Rotate(GExpr::Symbol(aIterator->second), pSlot.mRotation);

        if (pExpr->IsInvalid()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GAXPLQuick::BakeInputSlotWord failed to rotate nonce byte";
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

        GExpr aRead = GQuick::MakeReadBufferOffsetExpressionDirected(
            aIterator->second,
            aLoopIndex,
            pSlot.mReverse,
            static_cast<std::uint32_t>(pSlot.mOffset)
        );

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

bool GAXPLQuick::InputsRequireAddSources(const std::vector<GAXSKInputSlot> &pInputs) {
    for (const GAXSKInputSlot &aInput : pInputs) {
        if (aInput.mKind == GAXSKInputSlotKind::kSource) {
            return true;
        }
    }
    return false;
}

bool GAXPLQuick::InputsRequireXorSources(const std::vector<GAXSKInputSlot> &pInputs) {
    for (const GAXSKInputSlot &aInput : pInputs) {
        if (aInput.mKind == GAXSKInputSlotKind::kSource) {
            return true;
        }
    }
    return false;
}

bool GAXPLQuick::InputsRequireAddNonces(const std::vector<GAXSKInputSlot> &pInputs) {
    for (const GAXSKInputSlot &aInput : pInputs) {
        if (aInput.mKind == GAXSKInputSlotKind::kNonceByte) {
            return true;
        }
    }
    return false;
}

bool GAXPLQuick::InputsRequireXorNonces(const std::vector<GAXSKInputSlot> &pInputs) {
    for (const GAXSKInputSlot &aInput : pInputs) {
        if (aInput.mKind == GAXSKInputSlotKind::kNonceByte) {
            return true;
        }
    }
    return false;
}

bool GAXPLQuick::BakeInputSlotWordsAddSources(
    const std::vector<GAXSKInputSlot> &pInputs,
    const std::unordered_map<GAXSKSourceKind, GSymbol> &pSourceMap,
    const std::unordered_map<GAXSKNonceByteKind, GSymbol> &pNonceMap,
    
    GExpr *pExpr,
    std::string *pErrorMessage) {

    if (pExpr == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWordsAddSources received null expression";
        }
        return false;
    }

    std::vector<GExpr> aTerms;

    for (const GAXSKInputSlot &aSlot : pInputs) {
        if (aSlot.mKind != GAXSKInputSlotKind::kSource) {
            continue;
        }

        GExpr aWord;
        if (!BakeInputSlotWord(aSlot,
                               pSourceMap,
                               pNonceMap,
                               &aWord,
                               pErrorMessage)) {
            return false;
        }

        aTerms.push_back(aWord);
    }

    if (aTerms.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWordsAddSources found no source terms";
        }
        return false;
    }

    *pExpr = GQuick::AddChain(aTerms);
    return !pExpr->IsInvalid();
}

bool GAXPLQuick::BakeInputSlotWordsXorSources(
    const std::vector<GAXSKInputSlot> &pInputs,
    const std::unordered_map<GAXSKSourceKind, GSymbol> &pSourceMap,
    const std::unordered_map<GAXSKNonceByteKind, GSymbol> &pNonceMap,
    
    GExpr *pExpr,
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
        if (!BakeInputSlotWord(aSlot, pSourceMap, pNonceMap, &aWord, pErrorMessage)) {
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

bool GAXPLQuick::BakeInputSlotWordsAddNonces(
    const std::vector<GAXSKInputSlot> &pInputs,
    const std::unordered_map<GAXSKSourceKind, GSymbol> &pSourceMap,
    const std::unordered_map<GAXSKNonceByteKind, GSymbol> &pNonceMap,
    GExpr *pExpr,
    std::string *pErrorMessage) {

    if (pExpr == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWordsAddNonces received null expression";
        }
        return false;
    }

    std::vector<GExpr> aTerms;

    for (const GAXSKInputSlot &aSlot : pInputs) {
        if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
            continue;
        }

        GExpr aWord;
        if (!BakeInputSlotWord(aSlot, pSourceMap, pNonceMap, &aWord, pErrorMessage)) {
            return false;
        }

        aTerms.push_back(aWord);
    }

    if (aTerms.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWordsAddNonces found no nonce terms";
        }
        return false;
    }

    *pExpr = GQuick::AddChain(aTerms);
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

    std::vector<GExpr> aTerms;

    for (const GAXSKInputSlot &aSlot : pInputs) {
        if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
            continue;
        }

        GExpr aWord;
        if (!BakeInputSlotWord(aSlot, pSourceMap, pNonceMap, &aWord, pErrorMessage)) {
            return false;
        }

        aTerms.push_back(aWord);
    }

    if (aTerms.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPLQuick::BakeInputSlotWordsXorNonces found no nonce terms";
        }
        return false;
    }

    *pExpr = GQuick::XorChain(aTerms);
    return !pExpr->IsInvalid();
}
