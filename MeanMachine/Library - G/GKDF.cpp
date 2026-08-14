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
        case TwistDomain::kKeyRotateA:
            return {"mKeyRotateAConstants", "mKeyRotateASalts"};
        case TwistDomain::kKeyRotateB:
            return {"mKeyRotateBConstants", "mKeyRotateBSalts"};
        case TwistDomain::kKeySpawnA:
            return {"mKeySpawnAConstants", "mKeySpawnASalts"};
        case TwistDomain::kKeySpawnB:
            return {"mKeySpawnBConstants", "mKeySpawnBSalts"};
        case TwistDomain::kSeed:
            return {"mSeedConstants", "mSeedSalts"};
        case TwistDomain::kTwist:
            return {"mTwistConstants", "mTwistSalts"};
        case TwistDomain::kInvalid:
        default:
            return {"", ""};
    }
}

std::string BundlePrefix(const GKDFMaterialBundle pBundle) {
    switch (pBundle) {
        case GKDFMaterialBundle::kEphemeralA:
            return "mDomainBundleEphemeralA";
        case GKDFMaterialBundle::kEphemeralB:
            return "mDomainBundleEphemeralB";
        case GKDFMaterialBundle::kWorkspace:
            return "pWorkSpace->mDomainBundle";
        case GKDFMaterialBundle::kInbuilt:
        default:
            return "mDomainBundleInbuilt";
    }
}

char DomainFunctionSuffix(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kKeyRotateA: return 'A';
        case TwistDomain::kKeyRotateB: return 'B';
        case TwistDomain::kKeySpawnA: return 'C';
        case TwistDomain::kKeySpawnB: return 'D';
        case TwistDomain::kTwist: return 'E';
        case TwistDomain::kSeed: return 'F';
        case TwistDomain::kInvalid:
        default: return 'A';
    }
}

bool BakeKDFCall(const char *pFunctionName,
                 TwistDomain pDomain,
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

    const RoundMaterialSuffixSet aSet = DomainRoundMaterialSuffixSet(pDomain);
    const std::string aBundle = BundlePrefix(pBundle);
    std::string aCall = std::string(pFunctionName) + "_" +
        DomainFunctionSuffix(pDomain) + "(pWorkSpace, pNonce, "
        "&(" + aBundle + "." + std::string(aSet.mConstants) + "), "
        "&(" + aBundle + "." + std::string(aSet.mSalts) + ")";
    aCall +=
        ", &aPrevious, &aIngress, &aCarry"
        ", &aWandererA, &aWandererB, &aWandererC, &aWandererD"
        ", &aWandererE, &aWandererF, &aWandererG, &aWandererH"
        ", &aWandererI, &aWandererJ, &aWandererK";
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
                       pStatements,
                       pErrorMessage);
}

bool GKDF_C::Bake(TwistDomain pDomain,
                  GKDFMaterialBundle pBundle,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) {
    return BakeKDFCall("KDF_C",
                       pDomain,
                       pBundle,
                       pStatements,
                       pErrorMessage);
}
