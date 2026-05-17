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
        case TwistDomain::kSaltsKeyAUnwind:
        case TwistDomain::kSaltsKeyAOrbiter:
        case TwistDomain::kSaltsKeyAOrbiterInit:
        case TwistDomain::kSBoxesKeyA:
            return {"mDomainBundleInbuilt.mKeyAConstants", "mDomainBundle.mKeyASalts", "mDomainBundle.mKeyASBoxes"};
            
        case TwistDomain::kSaltsKeyBUnwind:
        case TwistDomain::kSaltsKeyBOrbiter:
        case TwistDomain::kSaltsKeyBOrbiterInit:
        case TwistDomain::kSBoxesKeyB:
            return {"mDomainBundleInbuilt.mKeyBConstants", "mDomainBundle.mKeyBSalts", "mDomainBundle.mKeyBSBoxes"};
            
        case TwistDomain::kSaltsMaskAUnwind:
        case TwistDomain::kSaltsMaskAOrbiter:
        case TwistDomain::kSaltsMaskAOrbiterInit:
        case TwistDomain::kSBoxesMaskA:
            return {"mDomainBundleInbuilt.mMaskAConstants", "mDomainBundle.mMaskASalts", "mDomainBundle.mMaskASBoxes"};
            
            
        case TwistDomain::kSaltsMaskBUnwind:
        case TwistDomain::kSaltsMaskBOrbiter:
        case TwistDomain::kSaltsMaskBOrbiterInit:
        case TwistDomain::kSBoxesMaskB:
            return {"mDomainBundleInbuilt.mMaskBConstants", "mDomainBundle.mMaskBSalts", "mDomainBundle.mMaskBSBoxes"};
            
        case TwistDomain::kSaltsMaskLaneUnwind:
        case TwistDomain::kSaltsMaskLaneOrbiter:
        case TwistDomain::kSaltsMaskLaneOrbiterInit:
        case TwistDomain::kSBoxesMaskLane:
            return {"mDomainBundleInbuilt.mMaskLaneConstants", "mDomainBundle.mMaskLaneSalts", "mDomainBundle.mMaskLaneSBoxes"};
            
        case TwistDomain::kSaltsOperationLaneUnwind:
        case TwistDomain::kSaltsOperationLaneOrbiter:
        case TwistDomain::kSaltsOperationLaneOrbiterInit:
        case TwistDomain::kSBoxesOperationLane:
            return {"mDomainBundleInbuilt.mOperationLaneConstants", "mDomainBundle.mOperationLaneSalts", "mDomainBundle.mOperationLaneSBoxes"};
            
        case TwistDomain::kInv:
        case TwistDomain::kSaltsWorkLaneUnwind:
        case TwistDomain::kSaltsWorkLaneOrbiter:
        case TwistDomain::kSaltsWorkLaneOrbiterInit:
        case TwistDomain::kSBoxesWorkLane:
        default:
            return {"mDomainBundleInbuilt.mWorkLaneConstants", "mDomainBundle.mWorkLaneSalts", "mDomainBundle.mWorkLaneSBoxes"};
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
        "KDF(" + aSourceAlias + ", " + aBufferAlias + ", "
        "&(" + std::string(aSet.mConstants) + "), "
        "&(pWorkspace->" + std::string(aSet.mSalts) + "), "
        "&(pWorkspace->" + std::string(aSet.mSBoxes) + "));"));
    return true;
}
