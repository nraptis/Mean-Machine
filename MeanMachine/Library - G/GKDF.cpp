//
//  GKDF.cpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#include "GKDF.hpp"

#include <cstdio>

namespace {

struct RoundMaterialSuffixSet {
    const char *mConstants;
    const char *mSalts;
};

RoundMaterialSuffixSet DomainRoundMaterialSuffixSet(TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB:
            return {"mPhaseBConstants", "mPhaseBSalts"};
        case TwistDomain::kPhaseC:
            return {"mPhaseCConstants", "mPhaseCSalts"};
        case TwistDomain::kInvalid:
        case TwistDomain::kPhaseA:
        default:
            return {"mPhaseAConstants", "mPhaseASalts"};
    }
}

std::string BundlePrefix(const GKDFMaterialBundle pBundle) {
    switch (pBundle) {
        case GKDFMaterialBundle::kEphemeral:
            return "mDomainBundleEphemeral";
        case GKDFMaterialBundle::kWorkspace:
            return "pWorkSpace->mDomainBundle";
        case GKDFMaterialBundle::kInbuilt:
        default:
            return "mDomainBundleInbuilt";
    }
}

bool BakeKDFCall(const char *pFunctionName,
                 TwistDomain pDomain,
                 GKDFMaterialBundle pBundle,
                 const GSymbol *pSnow,
                 std::vector<GStatement> *pStatements,
                 std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    if (pStatements == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string(pFunctionName) + "::Bake requires statement output.";
        }
        return false;
    }

    const RoundMaterialSuffixSet aSet = DomainRoundMaterialSuffixSet(pDomain);
    const std::string aBundle = BundlePrefix(pBundle);
    if ((pSnow != nullptr) && pSnow->IsBuf()) {
        pStatements->push_back(GStatement::RawLine("mSnow = " + BufAliasName(*pSnow) + ";"));
    }
    pStatements->push_back(GStatement::RawLine(
        std::string(pFunctionName) + "(pNonce, "
        "&(" + aBundle + "." + std::string(aSet.mConstants) + "), "
        "&(" + aBundle + "." + std::string(aSet.mSalts) + "));"));
    return true;
}

} // namespace

bool GKDF_A::Bake(TwistDomain pDomain,
                  GKDFMaterialBundle pBundle,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) {
    return BakeKDFCall("KDF_A",
                       pDomain,
                       pBundle,
                       &mSnow,
                       pStatements,
                       pErrorMessage);
}

bool GKDF_B::Bake(TwistDomain pDomain,
                  GKDFMaterialBundle pBundle,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) {
    return BakeKDFCall("KDF_B",
                       pDomain,
                       pBundle,
                       nullptr,
                       pStatements,
                       pErrorMessage);
}
