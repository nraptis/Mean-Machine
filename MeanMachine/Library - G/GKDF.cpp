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
    const char *mSBoxes;
};

RoundMaterialSuffixSet DomainRoundMaterialSuffixSet(TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB:
            return {"mPhaseBConstants", "mPhaseBSalts", "mPhaseBSBoxes"};
        case TwistDomain::kPhaseC:
            return {"mPhaseCConstants", "mPhaseCSalts", "mPhaseCSBoxes"};
        case TwistDomain::kInvalid:
        case TwistDomain::kPhaseA:
        default:
            return {"mPhaseAConstants", "mPhaseASalts", "mPhaseASBoxes"};
    }
}

std::string BundlePrefix(const GKDFMaterialBundle pBundle) {
    switch (pBundle) {
        case GKDFMaterialBundle::kEphemeral:
            return "mDomainBundleEphemeral";
        case GKDFMaterialBundle::kWorkspace:
            return "pWorkspace->mDomainBundle";
        case GKDFMaterialBundle::kInbuilt:
        default:
            return "mDomainBundleInbuilt";
    }
}

bool BakeKDFCall(const char *pFunctionName,
                 TwistDomain pDomain,
                 const std::string &pSource,
                 const std::string &pDest,
                 GKDFMaterialBundle pBundle,
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
    if (pSource.empty() || pDest.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string(pFunctionName) + "::Bake requires source and destination expressions.";
        }
        return false;
    }

    const RoundMaterialSuffixSet aSet = DomainRoundMaterialSuffixSet(pDomain);
    const std::string aBundle = BundlePrefix(pBundle);
    pStatements->push_back(GStatement::RawLine("mSource = " + pSource + ";"));
    pStatements->push_back(GStatement::RawLine("mDest = " + pDest + ";"));
    pStatements->push_back(GStatement::RawLine(
        std::string(pFunctionName) + "(pNonce, "
        "&(" + aBundle + "." + std::string(aSet.mConstants) + "), "
        "&(" + aBundle + "." + std::string(aSet.mSalts) + "), "
        "&(" + aBundle + "." + std::string(aSet.mSBoxes) + "));"));
    return true;
}

} // namespace

bool GKDF_A::Bake(TwistDomain pDomain,
                  const std::string &pSource,
                  const std::string &pDest,
                  GKDFMaterialBundle pBundle,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) {
    return BakeKDFCall("KDF_A",
                       pDomain,
                       pSource,
                       pDest,
                       pBundle,
                       pStatements,
                       pErrorMessage);
}

bool GKDF_B::Bake(TwistDomain pDomain,
                  const std::string &pSource,
                  const std::string &pDest,
                  GKDFMaterialBundle pBundle,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) {
    return BakeKDFCall("KDF_B",
                       pDomain,
                       pSource,
                       pDest,
                       pBundle,
                       pStatements,
                       pErrorMessage);
}
