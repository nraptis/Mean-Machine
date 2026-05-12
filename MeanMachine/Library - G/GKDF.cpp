//
//  GKDF.cpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#include "GKDF.hpp"

#include <cstdio>

namespace {

std::string DomainToken(TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kInv: return "TwistDomain::kInv";
        case TwistDomain::kSalts:
            return "TwistDomain::kSalts";
        case TwistDomain::kSBoxes:
            return "TwistDomain::kSBoxes";
        case TwistDomain::kKeyBoxA:
            return "TwistDomain::kKeyBoxA";
        case TwistDomain::kKeyBoxB:
            return "TwistDomain::kKeyBoxB";
        case TwistDomain::kMaskBoxA:
            return "TwistDomain::kMaskBoxA";
        case TwistDomain::kMaskBoxB:
            return "TwistDomain::kMaskBoxB";
        case TwistDomain::kSaltsKeyAWanderer: return "TwistDomain::kSaltsKeyAWanderer";
        case TwistDomain::kSaltsKeyAOrbiter: return "TwistDomain::kSaltsKeyAOrbiter";
        case TwistDomain::kSaltsKeyASeeder: return "TwistDomain::kSaltsKeyASeeder";
        case TwistDomain::kSaltsKeyBWanderer: return "TwistDomain::kSaltsKeyBWanderer";
        case TwistDomain::kSaltsKeyBOrbiter: return "TwistDomain::kSaltsKeyBOrbiter";
        case TwistDomain::kSaltsKeyBSeeder: return "TwistDomain::kSaltsKeyBSeeder";
        case TwistDomain::kSaltsMaskAWanderer: return "TwistDomain::kSaltsMaskAWanderer";
        case TwistDomain::kSaltsMaskAOrbiter: return "TwistDomain::kSaltsMaskAOrbiter";
        case TwistDomain::kSaltsMaskASeeder: return "TwistDomain::kSaltsMaskASeeder";
        case TwistDomain::kSaltsMaskBWanderer: return "TwistDomain::kSaltsMaskBWanderer";
        case TwistDomain::kSaltsMaskBOrbiter: return "TwistDomain::kSaltsMaskBOrbiter";
        case TwistDomain::kSaltsMaskBSeeder: return "TwistDomain::kSaltsMaskBSeeder";
        case TwistDomain::kSaltsWorkLaneWanderer: return "TwistDomain::kSaltsWorkLaneWanderer";
        case TwistDomain::kSaltsWorkLaneOrbiter: return "TwistDomain::kSaltsWorkLaneOrbiter";
        case TwistDomain::kSaltsWorkLaneSeeder: return "TwistDomain::kSaltsWorkLaneSeeder";
        case TwistDomain::kSaltsMaskLaneWanderer: return "TwistDomain::kSaltsMaskLaneWanderer";
        case TwistDomain::kSaltsMaskLaneOrbiter: return "TwistDomain::kSaltsMaskLaneOrbiter";
        case TwistDomain::kSaltsMaskLaneSeeder: return "TwistDomain::kSaltsMaskLaneSeeder";
        case TwistDomain::kSaltsOperationLaneWanderer: return "TwistDomain::kSaltsOperationLaneWanderer";
        case TwistDomain::kSaltsOperationLaneOrbiter: return "TwistDomain::kSaltsOperationLaneOrbiter";
        case TwistDomain::kSaltsOperationLaneSeeder: return "TwistDomain::kSaltsOperationLaneSeeder";
        case TwistDomain::kSBoxesKeyA: return "TwistDomain::kSBoxesKeyA";
        case TwistDomain::kSBoxesKeyB: return "TwistDomain::kSBoxesKeyB";
        case TwistDomain::kSBoxesMaskA: return "TwistDomain::kSBoxesMaskA";
        case TwistDomain::kSBoxesMaskB: return "TwistDomain::kSBoxesMaskB";
        case TwistDomain::kSBoxesWorkLane: return "TwistDomain::kSBoxesWorkLane";
        case TwistDomain::kSBoxesMaskLane: return "TwistDomain::kSBoxesMaskLane";
        case TwistDomain::kSBoxesOperationLane: return "TwistDomain::kSBoxesOperationLane";
        default:
            break;
    }

    return "TwistDomain::kInv";
}

} // namespace

bool GKDF::Bake(TwistDomain pDomain,
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

    const std::string aBufferAlias = BufAliasName(pKDFBuffer.mSlot);
    if (aBufferAlias.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GKDF::Bake target buffer alias was empty.";
        }
        return false;
    }

    const std::string aDomain = DomainToken(pDomain);
    const std::string aLaneA = aBufferAlias;
    const std::string aLaneB = BufAliasName(TwistWorkSpaceSlot::kDerivedSaltA);
    const std::string aLaneC = BufAliasName(TwistWorkSpaceSlot::kDerivedSaltB);
    const std::string aLaneD = BufAliasName(TwistWorkSpaceSlot::kDerivedSaltC);
    const std::string aLaneE = BufAliasName(TwistWorkSpaceSlot::kDerivedSaltD);
    const std::string aLaneF = BufAliasName(TwistWorkSpaceSlot::kDerivedSaltE);
    if (aLaneB.empty() || aLaneC.empty() || aLaneD.empty() || aLaneE.empty() || aLaneF.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GKDF::Bake required derived-salt aliases were empty.";
        }
        return false;
    }

    pStatements->push_back(GStatement::RawLine(
        "KDF(" + aDomain + ", "
        "mDomainConstantPublicIngress, "
        "mDomainConstantPrivateIngress, "
        "mDomainConstantCrossIngress, "
        + aLaneA + ", " + aLaneB + ", " + aLaneC + ", " + aLaneD + ", " + aLaneE + ", " + aLaneF + ");"));
    return true;
}
