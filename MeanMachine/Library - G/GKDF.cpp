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
        case TwistDomain::kPhaseD:
            return {"mPhaseDConstants", "mPhaseDSalts"};
        case TwistDomain::kPhaseE:
            return {"mPhaseEConstants", "mPhaseESalts"};
        case TwistDomain::kPhaseF:
            return {"mPhaseFConstants", "mPhaseFSalts"};
        case TwistDomain::kPhaseG:
            return {"mPhaseGConstants", "mPhaseGSalts"};
        case TwistDomain::kPhaseH:
            return {"mPhaseHConstants", "mPhaseHSalts"};
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
    std::string aCall = std::string(pFunctionName) + "(pNonce, "
        "&(" + aBundle + "." + std::string(aSet.mConstants) + "), "
        "&(" + aBundle + "." + std::string(aSet.mSalts) + ")";
    if (pSnow != nullptr) {
        if (!pSnow->IsBuf()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string(pFunctionName) + "::Bake requires a snow buffer.";
            }
            return false;
        }
        aCall += ", " + BufAliasName(*pSnow);
    }
    aCall += ");";
    pStatements->push_back(GStatement::RawLine(aCall));
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
                       &mKDFSnow,
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
