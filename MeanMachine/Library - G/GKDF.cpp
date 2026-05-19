//
//  GKDF.cpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#include "GKDF.hpp"

#include <cstdio>

namespace {

struct RoundMaterialSet {
    const char *mConstants;
    const char *mSalts;
    const char *mSBoxes;
};

RoundMaterialSet DomainRoundMaterialSet(TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB:
            return {"mDomainBundleInbuilt.mPhaseBConstants", "mDomainBundle.mPhaseBSalts", "mDomainBundle.mPhaseBSBoxes"};
        case TwistDomain::kPhaseC:
            return {"mDomainBundleInbuilt.mPhaseCConstants", "mDomainBundle.mPhaseCSalts", "mDomainBundle.mPhaseCSBoxes"};
        case TwistDomain::kInvalid:
        case TwistDomain::kPhaseA:
        default:
            return {"mDomainBundleInbuilt.mPhaseAConstants", "mDomainBundle.mPhaseASalts", "mDomainBundle.mPhaseASBoxes"};
    }
}

} // namespace

bool GKDF::Bake(TwistDomain pDomain,
                GSymbol pSourceBuffer,
                GSymbol pKDFBuffer,
                std::vector<GStatement> *pStatements,
                std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    
    if (pStatements == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GKDF::Bake requires statement output.";
        }
        return false;
    }
    
    if (!pKDFBuffer.IsBuf()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GKDF::Bake requires a buffer symbol target.";
        }
        return false;
    }
    
    if (!pSourceBuffer.IsBuf()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GKDF::Bake requires a buffer symbol source.";
        }
        return false;
    }
    
    const std::string aBufferAlias = BufAliasName(pKDFBuffer);
    if (aBufferAlias.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GKDF::Bake target buffer alias was empty.";
        }
        return false;
    }
    
    const std::string aSourceAlias = BufAliasName(pSourceBuffer);
    if (aSourceAlias.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GKDF::Bake source alias was empty.";
        }
        return false;
    }
    
    const RoundMaterialSet aSet = DomainRoundMaterialSet(pDomain);
    pStatements->push_back(GStatement::RawLine(
        "KDF(pNonce, " + aSourceAlias + ", " + aBufferAlias + ", "
        "&(" + std::string(aSet.mConstants) + "), "
        "&(pWorkspace->" + std::string(aSet.mSalts) + "), "
        "&(pWorkspace->" + std::string(aSet.mSBoxes) + "));"));
    return true;
}
