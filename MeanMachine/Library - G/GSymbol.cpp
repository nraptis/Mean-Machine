//
//  GSymbol.cpp
//  Superfox
//
//  Created by Dope on 4/20/26.
//

#include "GSymbol.hpp"

#include <cstdlib>

namespace {

bool BufferKeysEqual(const TwistBufferKey &pLHS,
                     const TwistBufferKey &pRHS) {
    return (pLHS.mKind == pRHS.mKind) &&
           (pLHS.mDirect == pRHS.mDirect) &&
           (pLHS.mDomain == pRHS.mDomain) &&
           (pLHS.mSaltOwner == pRHS.mSaltOwner) &&
           (pLHS.mSBoxOwner == pRHS.mSBoxOwner) &&
           (pLHS.mSaltPhase == pRHS.mSaltPhase) &&
           (pLHS.mSaltLane == pRHS.mSaltLane) &&
           (pLHS.mSBoxLane == pRHS.mSBoxLane);
}

TwistBufferKey ResolveBufferKeyFromSlot(const TwistWorkSpaceSlot pSlot) {
    TwistBufferKey aKey;
    if (TwistWorkSpace::TryLegacySlotToBufferKey(pSlot, &aKey)) {
        return aKey;
    }
    return TwistBufferKey();
}

TwistWorkSpaceSlot ResolveSlotFromBufferKey(const TwistBufferKey pKey) {
    if (!pKey.IsValid()) {
        return TwistWorkSpaceSlot::kInvalid;
    }
    for (int aValue = 0; aValue <= 255; ++aValue) {
        const TwistWorkSpaceSlot aCandidate = static_cast<TwistWorkSpaceSlot>(aValue);
        TwistBufferKey aMapped;
        if (!TwistWorkSpace::TryLegacySlotToBufferKey(aCandidate, &aMapped)) {
            continue;
        }
        if (BufferKeysEqual(aMapped, pKey)) {
            return aCandidate;
        }
    }
    return TwistWorkSpaceSlot::kInvalid;
}

TwistBufferKey ResolveBufferKeyFromSymbol(const GSymbol &pSymbol) {
    if (pSymbol.mKey.IsValid()) {
        return pSymbol.mKey;
    }
    return ResolveBufferKeyFromSlot(pSymbol.mSlot);
}

bool ParseTokenInt(const std::string &pText,
                   int *pValueOut) {
    if (pValueOut == nullptr) {
        return false;
    }
    if (pText.empty()) {
        return false;
    }
    char *aEnd = nullptr;
    const long aParsed = std::strtol(pText.c_str(), &aEnd, 10);
    if ((aEnd == nullptr) || (*aEnd != '\0')) {
        return false;
    }
    *pValueOut = static_cast<int>(aParsed);
    return true;
}

} // namespace

GSymbol::GSymbol() {
    Invalidate();
}

GSymbol GSymbol::Var(const std::string &pName) {
    GSymbol aSymbol;
    aSymbol.mType = GSymbolType::kVar;
    aSymbol.mName = pName;
    aSymbol.mSlot = TwistWorkSpaceSlot::kInvalid;
    aSymbol.mKey = TwistBufferKey();
    return aSymbol;
}

GSymbol GSymbol::Var(TwistVariable pVariable) {
    switch (pVariable) {
        case TwistVariable::kIndex: return Var("aIndex");
        case TwistVariable::kCarry: return Var("aCarry");

        case TwistVariable::kPublicIngress: return Var("aPublicIngress");
        case TwistVariable::kPublicPrevious: return Var("aPublicPrevious");
        case TwistVariable::kPublicScatter: return Var("aPublicScatter");

        case TwistVariable::kPrivateIngress: return Var("aPrivateIngress");
        case TwistVariable::kPrivatePrevious: return Var("aPrivatePrevious");
        case TwistVariable::kPrivateScatter: return Var("aPrivateScatter");
        case TwistVariable::kPrivateWrite: return Var("aPrivateWrite");

        case TwistVariable::kCrossIngress: return Var("aCrossIngress");

        case TwistVariable::kUnwindA: return Var("aUnwindA");
        case TwistVariable::kUnwindB: return Var("aUnwindB");
        case TwistVariable::kUnwindC: return Var("aUnwindC");
        case TwistVariable::kUnwindD: return Var("aUnwindD");
        case TwistVariable::kUnwindE: return Var("aUnwindE");
        case TwistVariable::kUnwindF: return Var("aUnwindF");

        case TwistVariable::kOrbiterA: return Var("aOrbitA");
        case TwistVariable::kOrbiterB: return Var("aOrbitB");
        case TwistVariable::kOrbiterC: return Var("aOrbitC");
        case TwistVariable::kOrbiterD: return Var("aOrbitD");
        case TwistVariable::kOrbiterE: return Var("aOrbitE");
        case TwistVariable::kOrbiterF: return Var("aOrbitF");

        case TwistVariable::kPlugKeyA: return Var("aPlugKeyA");
        case TwistVariable::kPlugKeyB: return Var("aPlugKeyB");
        case TwistVariable::kPlugKeyC: return Var("aPlugKeyC");
        case TwistVariable::kPlugKeyD: return Var("aPlugKeyD");
        case TwistVariable::kPlugKeyE: return Var("aPlugKeyE");
        case TwistVariable::kPlugKeyF: return Var("aPlugKeyF");

        case TwistVariable::kPublicIngressDomainWord: return Var("aPublicIngressDomainWord");
        case TwistVariable::kPrivateIngressDomainWord: return Var("aPrivateIngressDomainWord");
        case TwistVariable::kCrossIngressDomainWord: return Var("aCrossIngressDomainWord");
        default:
            return Var("aInvalidVariable");
    }
}

GSymbol GSymbol::Var(TwistDomain pDomain,
                     TwistConstants pConstant) {
    const char *aConstantSuffix = nullptr;
    switch (pConstant) {
        case TwistConstants::kPublicIngress:
            aConstantSuffix = "PublicIngress";
            break;
        case TwistConstants::kPrivateIngress:
            aConstantSuffix = "PrivateIngress";
            break;
        case TwistConstants::kCrossIngress:
            aConstantSuffix = "CrossIngress";
            break;
        default:
            return Var("mDomainConstantPublicIngress");
    }
    
    const char *aFamilyPrefix = nullptr;
    switch (pDomain) {
            
        case TwistDomain::kSaltsKeyAUnwind:
        case TwistDomain::kSaltsKeyAOrbiter:
        case TwistDomain::kSaltsKeyAOrbiterInit:
        case TwistDomain::kSBoxesKeyA:
            aFamilyPrefix = "mDomainBundleInbuilt.mKeyAConstants";
            break;
            
            
        case TwistDomain::kSaltsKeyBUnwind:
        case TwistDomain::kSaltsKeyBOrbiter:
        case TwistDomain::kSaltsKeyBOrbiterInit:
        case TwistDomain::kSBoxesKeyB:
            aFamilyPrefix = "mDomainBundleInbuilt.mKeyBConstants";
            break;
            
            
        case TwistDomain::kSaltsMaskAUnwind:
        case TwistDomain::kSaltsMaskAOrbiter:
        case TwistDomain::kSaltsMaskAOrbiterInit:
        case TwistDomain::kSBoxesMaskA:
            aFamilyPrefix = "mDomainBundleInbuilt.mMaskAConstants";
            break;
            
            
        case TwistDomain::kSaltsMaskBUnwind:
        case TwistDomain::kSaltsMaskBOrbiter:
        case TwistDomain::kSaltsMaskBOrbiterInit:
        case TwistDomain::kSBoxesMaskB:
            aFamilyPrefix = "mDomainBundleInbuilt.mMaskBConstants";
            break;
            
        case TwistDomain::kSaltsMaskLaneUnwind:
        case TwistDomain::kSaltsMaskLaneOrbiter:
        case TwistDomain::kSaltsMaskLaneOrbiterInit:
        case TwistDomain::kSBoxesMaskLane:
            aFamilyPrefix = "mDomainBundleInbuilt.mMaskLaneConstants";
            break;
            
        case TwistDomain::kSaltsOperationLaneUnwind:
        case TwistDomain::kSaltsOperationLaneOrbiter:
        case TwistDomain::kSaltsOperationLaneOrbiterInit:
        case TwistDomain::kSBoxesOperationLane:
            aFamilyPrefix = "mDomainBundleInbuilt.mOperationLaneConstants";
            break;
            
        case TwistDomain::kInv:
        case TwistDomain::kSaltsWorkLaneUnwind:
        case TwistDomain::kSaltsWorkLaneOrbiter:
        case TwistDomain::kSaltsWorkLaneOrbiterInit:
        case TwistDomain::kSBoxesWorkLane:
        default:
            aFamilyPrefix = "mDomainBundleInbuilt.mWorkLaneConstants";
            break;
    }
    
    return Var(std::string(aFamilyPrefix) + ".mDomainConstant" + aConstantSuffix);
}

GSymbol GSymbol::Buf(const TwistWorkSpaceSlot pSlot) {
    GSymbol aSymbol;
    aSymbol.mType = GSymbolType::kBuf;
    aSymbol.mSlot = pSlot;
    aSymbol.mKey = ResolveBufferKeyFromSlot(pSlot);
    aSymbol.mName = BufName(aSymbol);
    return aSymbol;
}

GSymbol GSymbol::Buf(const TwistBufferKey pKey) {
    GSymbol aSymbol;
    aSymbol.mType = GSymbolType::kBuf;
    aSymbol.mKey = pKey;
    aSymbol.mSlot = ResolveSlotFromBufferKey(pKey);
    aSymbol.mName = BufName(aSymbol);
    return aSymbol;
}

void GSymbol::Set(const GSymbol &pOther) {
    mName = pOther.mName;
    mType = pOther.mType;
    mSlot = pOther.mSlot;
    mKey = pOther.mKey;
}

void GSymbol::Invalidate() {
    mName = "";
    mType = GSymbolType::kInv;
    mSlot = TwistWorkSpaceSlot::kInvalid;
    mKey = TwistBufferKey();
}

bool GSymbol::IsInvalid() const {
    switch (mType) {
        case GSymbolType::kVar:
            return mName.empty();
        case GSymbolType::kBuf:
            return !mKey.IsValid() && (mSlot == TwistWorkSpaceSlot::kInvalid);
        default:
            return true;
    }
}

bool GSymbol::IsVar() const { return (mType == GSymbolType::kVar); }
bool GSymbol::IsBuf() const { return (mType == GSymbolType::kBuf); }

bool operator == (const GSymbol &pSymbolLHS, const GSymbol &pSymbolRHS) {
    if (pSymbolLHS.mType != pSymbolRHS.mType) {
        return false;
    }

    switch (pSymbolLHS.mType) {
        case GSymbolType::kInv:
            return true;
        case GSymbolType::kVar:
            return pSymbolLHS.mName == pSymbolRHS.mName;
        case GSymbolType::kBuf: {
            const TwistBufferKey aLHSKey = ResolveBufferKeyFromSymbol(pSymbolLHS);
            const TwistBufferKey aRHSKey = ResolveBufferKeyFromSymbol(pSymbolRHS);
            if (aLHSKey.IsValid() || aRHSKey.IsValid()) {
                return BufferKeysEqual(aLHSKey, aRHSKey);
            }
            return pSymbolLHS.mSlot == pSymbolRHS.mSlot;
        }
        default:
            return false;
    }
}

bool operator != (const GSymbol &pSymbolLHS, const GSymbol &pSymbolRHS) {
    return !(pSymbolLHS == pSymbolRHS);
}


std::string BufName(TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return "src";
        case TwistWorkSpaceSlot::kDest:   return "dst";

        case TwistWorkSpaceSlot::kDomainSaltKeyBoxA: return "domain_keybox_a";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxB: return "domain_keybox_b";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxC: return "domain_keybox_c";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxD: return "domain_keybox_d";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxE: return "domain_keybox_e";
        
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxA: return "domain_maskbox_a";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxB: return "domain_maskbox_b";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxC: return "domain_maskbox_c";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxD: return "domain_maskbox_d";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxE: return "domain_maskbox_e";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxF: return "domain_maskbox_f";
        case TwistWorkSpaceSlot::kDomainSaltUnwindA: return "domain_wanderer_a";
        case TwistWorkSpaceSlot::kDomainSaltUnwindB: return "domain_wanderer_b";
        case TwistWorkSpaceSlot::kDomainSaltUnwindC: return "domain_wanderer_c";
        case TwistWorkSpaceSlot::kDomainSaltUnwindD: return "domain_wanderer_d";
        case TwistWorkSpaceSlot::kDomainSaltUnwindE: return "domain_wanderer_e";
        case TwistWorkSpaceSlot::kDomainSaltUnwindF: return "domain_wanderer_f";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterA: return "domain_orbiter_a";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterB: return "domain_orbiter_b";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterC: return "domain_orbiter_c";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterD: return "domain_orbiter_d";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterE: return "domain_orbiter_e";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterF: return "domain_orbiter_f";
        case TwistWorkSpaceSlot::kDomainSaltPrismA: return "domain_prism_a";
        case TwistWorkSpaceSlot::kDomainSaltPrismB: return "domain_prism_b";
        case TwistWorkSpaceSlot::kDomainSaltPrismC: return "domain_prism_c";
        case TwistWorkSpaceSlot::kDomainSaltPrismD: return "domain_prism_d";
        case TwistWorkSpaceSlot::kDomainSaltPrismE: return "domain_prism_e";
        case TwistWorkSpaceSlot::kDomainSaltPrismF: return "domain_prism_f";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitA: return "domain_source_a";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitB: return "domain_source_b";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterC: return "domain_source_c";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterD: return "domain_source_d";
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindE: return "domain_source_e";
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindF: return "domain_source_f";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA: return "derived_salt_orbiter_a";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB: return "derived_salt_orbiter_b";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC: return "derived_salt_orbiter_c";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD: return "derived_salt_orbiter_d";
        case TwistWorkSpaceSlot::kDerivedSaltUnwindA: return "derived_salt_wanderer_a";
        case TwistWorkSpaceSlot::kDerivedSaltUnwindB: return "derived_salt_wanderer_b";
        case TwistWorkSpaceSlot::kDerivedSaltUnwindC: return "derived_salt_wanderer_c";
        case TwistWorkSpaceSlot::kDerivedSaltUnwindD: return "derived_salt_wanderer_d";

        case TwistWorkSpaceSlot::kParamDomainSBoxA: return "sbox_a";
        case TwistWorkSpaceSlot::kParamDomainSBoxB: return "sbox_b";
        case TwistWorkSpaceSlot::kParamDomainSBoxC: return "sbox_c";
        case TwistWorkSpaceSlot::kParamDomainSBoxD: return "sbox_d";
        case TwistWorkSpaceSlot::kParamDomainSBoxE: return "sbox_e";
        case TwistWorkSpaceSlot::kParamDomainSBoxF: return "sbox_f";
        case TwistWorkSpaceSlot::kParamDomainSBoxG: return "sbox_g";
        case TwistWorkSpaceSlot::kParamDomainSBoxH: return "sbox_h";
        case TwistWorkSpaceSlot::kDerivedSBoxA: return "derived_sbox_a";
        case TwistWorkSpaceSlot::kDerivedSBoxB: return "derived_sbox_b";
        case TwistWorkSpaceSlot::kDerivedSBoxC: return "derived_sbox_c";
        case TwistWorkSpaceSlot::kDerivedSBoxD: return "derived_sbox_d";
        case TwistWorkSpaceSlot::kDerivedSBoxE: return "derived_sbox_e";
        case TwistWorkSpaceSlot::kDerivedSBoxF: return "derived_sbox_f";
        case TwistWorkSpaceSlot::kDerivedSBoxG: return "derived_sbox_g";
        case TwistWorkSpaceSlot::kDerivedSBoxH: return "derived_sbox_h";

        case TwistWorkSpaceSlot::kSeedExpansionLaneA: return "seed_a";
        case TwistWorkSpaceSlot::kSeedExpansionLaneB: return "seed_b";
        case TwistWorkSpaceSlot::kSeedExpansionLaneC: return "seed_c";
        case TwistWorkSpaceSlot::kSeedExpansionLaneD: return "seed_d";
        case TwistWorkSpaceSlot::kSeedExpansionLaneE: return "seed_e";
        case TwistWorkSpaceSlot::kSeedExpansionLaneF: return "seed_f";

        case TwistWorkSpaceSlot::kWorkLaneA: return "work_a";
        case TwistWorkSpaceSlot::kWorkLaneB: return "work_b";
        case TwistWorkSpaceSlot::kWorkLaneC: return "work_c";
        case TwistWorkSpaceSlot::kWorkLaneD: return "work_d";
        case TwistWorkSpaceSlot::kWorkLaneE: return "work_e";
        case TwistWorkSpaceSlot::kWorkLaneF: return "work_f";

        case TwistWorkSpaceSlot::kOperationLaneA: return "op_a";
        case TwistWorkSpaceSlot::kOperationLaneB: return "op_b";
        case TwistWorkSpaceSlot::kOperationLaneC: return "op_c";
        case TwistWorkSpaceSlot::kOperationLaneD: return "op_d";
        case TwistWorkSpaceSlot::kOperationLaneE: return "op_e";
        case TwistWorkSpaceSlot::kOperationLaneF: return "op_f";

        case TwistWorkSpaceSlot::kMaskLaneA: return "mask_a";
        case TwistWorkSpaceSlot::kMaskLaneB: return "mask_b";

        case TwistWorkSpaceSlot::kIndexList256A: return "index_list_256_a";
        case TwistWorkSpaceSlot::kIndexList256B: return "index_list_256_b";
        case TwistWorkSpaceSlot::kIndexList256C: return "index_list_256_c";
        case TwistWorkSpaceSlot::kIndexList256D: return "index_list_256_d";

        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return "key_u_a";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return "key_u_b";
        case TwistWorkSpaceSlot::kKeyRowReadA:     return "key_r_a";
        case TwistWorkSpaceSlot::kKeyRowReadB:     return "key_r_b";
        case TwistWorkSpaceSlot::kKeyRowWriteA:    return "key_w_a";
        case TwistWorkSpaceSlot::kKeyRowWriteB:    return "key_w_b";

        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return "mask_u_a";
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return "mask_u_b";
        case TwistWorkSpaceSlot::kMaskRowReadA:     return "mask_r_a";
        case TwistWorkSpaceSlot::kMaskRowReadB:     return "mask_r_b";
        case TwistWorkSpaceSlot::kMaskRowWriteA:    return "mask_w_a";
        case TwistWorkSpaceSlot::kMaskRowWriteB:    return "mask_w_b";

        default: return "inv";
    }
}

std::string BufName(TwistBufferKey pKey) {
    const TwistWorkSpaceSlot aSlot = ResolveSlotFromBufferKey(pKey);
    if (aSlot != TwistWorkSpaceSlot::kInvalid) {
        return BufName(aSlot);
    }
    return "inv";
}

std::string BufName(const GSymbol &pSymbol) {
    if (!pSymbol.IsBuf()) {
        return "inv";
    }
    const TwistBufferKey aKey = ResolveBufferKeyFromSymbol(pSymbol);
    if (aKey.IsValid()) {
        return BufName(aKey);
    }
    return BufName(pSymbol.mSlot);
}

std::string BufAliasName(TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return "pSource";
        case TwistWorkSpaceSlot::kDest: return "pDestination";

        case TwistWorkSpaceSlot::kDomainSaltKeyBoxA: return "mDomainSaltKeyBoxA";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxB: return "mDomainSaltKeyBoxB";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxC: return "mDomainSaltKeyBoxC";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxD: return "mDomainSaltKeyBoxD";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxE: return "mDomainSaltKeyBoxE";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxA: return "mDomainSaltMaskBoxA";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxB: return "mDomainSaltMaskBoxB";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxC: return "mDomainSaltMaskBoxC";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxD: return "mDomainSaltMaskBoxD";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxE: return "mDomainSaltMaskBoxE";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxF: return "mDomainSaltMaskBoxF";
        case TwistWorkSpaceSlot::kDomainSaltUnwindA: return "mDomainSaltUnwindA";
        case TwistWorkSpaceSlot::kDomainSaltUnwindB: return "mDomainSaltUnwindB";
        case TwistWorkSpaceSlot::kDomainSaltUnwindC: return "mDomainSaltUnwindC";
        case TwistWorkSpaceSlot::kDomainSaltUnwindD: return "mDomainSaltUnwindD";
        case TwistWorkSpaceSlot::kDomainSaltUnwindE: return "mDomainSaltUnwindE";
        case TwistWorkSpaceSlot::kDomainSaltUnwindF: return "mDomainSaltUnwindF";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterA: return "mDomainSaltOrbiterA";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterB: return "mDomainSaltOrbiterB";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterC: return "mDomainSaltOrbiterC";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterD: return "mDomainSaltOrbiterD";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterE: return "mDomainSaltOrbiterE";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterF: return "mDomainSaltOrbiterF";
        case TwistWorkSpaceSlot::kDomainSaltPrismA: return "mDomainSaltPrismA";
        case TwistWorkSpaceSlot::kDomainSaltPrismB: return "mDomainSaltPrismB";
        case TwistWorkSpaceSlot::kDomainSaltPrismC: return "mDomainSaltPrismC";
        case TwistWorkSpaceSlot::kDomainSaltPrismD: return "mDomainSaltPrismD";
        case TwistWorkSpaceSlot::kDomainSaltPrismE: return "mDomainSaltPrismE";
        case TwistWorkSpaceSlot::kDomainSaltPrismF: return "mDomainSaltPrismF";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitA: return "mDomainSaltSourceA";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitB: return "mDomainSaltSourceB";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterC: return "mDomainSaltSourceC";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterD: return "mDomainSaltSourceD";
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindE: return "mDomainSaltSourceE";
        case TwistWorkSpaceSlot::kParamDomainSaltUnwindF: return "mDomainSaltSourceF";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA: return "aDerivedSaltOrbiterA";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB: return "aDerivedSaltOrbiterB";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC: return "aDerivedSaltOrbiterC";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD: return "aDerivedSaltOrbiterD";
        case TwistWorkSpaceSlot::kDerivedSaltUnwindA: return "aDerivedSaltUnwindA";
        case TwistWorkSpaceSlot::kDerivedSaltUnwindB: return "aDerivedSaltUnwindB";
        case TwistWorkSpaceSlot::kDerivedSaltUnwindC: return "aDerivedSaltUnwindC";
        case TwistWorkSpaceSlot::kDerivedSaltUnwindD: return "aDerivedSaltUnwindD";

        case TwistWorkSpaceSlot::kParamDomainSBoxA: return "mSBoxA";
        case TwistWorkSpaceSlot::kParamDomainSBoxB: return "mSBoxB";
        case TwistWorkSpaceSlot::kParamDomainSBoxC: return "mSBoxC";
        case TwistWorkSpaceSlot::kParamDomainSBoxD: return "mSBoxD";
        case TwistWorkSpaceSlot::kParamDomainSBoxE: return "mSBoxE";
        case TwistWorkSpaceSlot::kParamDomainSBoxF: return "mSBoxF";
        case TwistWorkSpaceSlot::kParamDomainSBoxG: return "mSBoxG";
        case TwistWorkSpaceSlot::kParamDomainSBoxH: return "mSBoxH";
        case TwistWorkSpaceSlot::kDerivedSBoxA: return "aDerivedSBoxA";
        case TwistWorkSpaceSlot::kDerivedSBoxB: return "aDerivedSBoxB";
        case TwistWorkSpaceSlot::kDerivedSBoxC: return "aDerivedSBoxC";
        case TwistWorkSpaceSlot::kDerivedSBoxD: return "aDerivedSBoxD";
        case TwistWorkSpaceSlot::kDerivedSBoxE: return "aDerivedSBoxE";
        case TwistWorkSpaceSlot::kDerivedSBoxF: return "aDerivedSBoxF";
        case TwistWorkSpaceSlot::kDerivedSBoxG: return "aDerivedSBoxG";
        case TwistWorkSpaceSlot::kDerivedSBoxH: return "aDerivedSBoxH";

        case TwistWorkSpaceSlot::kSeedExpansionLaneA: return "aExpandLaneA";
        case TwistWorkSpaceSlot::kSeedExpansionLaneB: return "aExpandLaneB";
        case TwistWorkSpaceSlot::kSeedExpansionLaneC: return "aExpandLaneC";
        case TwistWorkSpaceSlot::kSeedExpansionLaneD: return "aExpandLaneD";
        case TwistWorkSpaceSlot::kSeedExpansionLaneE: return "aExpandLaneE";
        case TwistWorkSpaceSlot::kSeedExpansionLaneF: return "aExpandLaneF";

        case TwistWorkSpaceSlot::kWorkLaneA: return "aWorkLaneA";
        case TwistWorkSpaceSlot::kWorkLaneB: return "aWorkLaneB";
        case TwistWorkSpaceSlot::kWorkLaneC: return "aWorkLaneC";
        case TwistWorkSpaceSlot::kWorkLaneD: return "aWorkLaneD";
        case TwistWorkSpaceSlot::kWorkLaneE: return "aWorkLaneE";
        case TwistWorkSpaceSlot::kWorkLaneF: return "aWorkLaneF";

        case TwistWorkSpaceSlot::kOperationLaneA: return "aOperationLaneA";
        case TwistWorkSpaceSlot::kOperationLaneB: return "aOperationLaneB";
        case TwistWorkSpaceSlot::kOperationLaneC: return "aOperationLaneC";
        case TwistWorkSpaceSlot::kOperationLaneD: return "aOperationLaneD";
        case TwistWorkSpaceSlot::kOperationLaneE: return "aOperationLaneE";
        case TwistWorkSpaceSlot::kOperationLaneF: return "aOperationLaneF";

        case TwistWorkSpaceSlot::kMaskLaneA: return "aMaskLaneA";
        case TwistWorkSpaceSlot::kMaskLaneB: return "aMaskLaneB";

        case TwistWorkSpaceSlot::kIndexList256A: return "aIndexList256A";
        case TwistWorkSpaceSlot::kIndexList256B: return "aIndexList256B";
        case TwistWorkSpaceSlot::kIndexList256C: return "aIndexList256C";
        case TwistWorkSpaceSlot::kIndexList256D: return "aIndexList256D";

        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return "aKeyBoxUnrolledA";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return "aKeyBoxUnrolledB";
        case TwistWorkSpaceSlot::kKeyRowReadA: return "aKeyRowReadA";
        case TwistWorkSpaceSlot::kKeyRowReadB: return "aKeyRowReadB";
        case TwistWorkSpaceSlot::kKeyRowWriteA: return "aKeyRowWriteA";
        case TwistWorkSpaceSlot::kKeyRowWriteB: return "aKeyRowWriteB";

        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return "aMaskBoxUnrolledA";
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return "aMaskBoxUnrolledB";
        case TwistWorkSpaceSlot::kMaskRowReadA: return "aMaskRowReadA";
        case TwistWorkSpaceSlot::kMaskRowReadB: return "aMaskRowReadB";
        case TwistWorkSpaceSlot::kMaskRowWriteA: return "aMaskRowWriteA";
        case TwistWorkSpaceSlot::kMaskRowWriteB: return "aMaskRowWriteB";

        default: return "aInvalidBuffer";
    }
}

std::string BufAliasName(TwistBufferKey pKey) {
    const TwistWorkSpaceSlot aSlot = ResolveSlotFromBufferKey(pKey);
    if (aSlot != TwistWorkSpaceSlot::kInvalid) {
        return BufAliasName(aSlot);
    }
    return "aInvalidBuffer";
}

std::string BufAliasName(const GSymbol &pSymbol) {
    if (!pSymbol.IsBuf()) {
        return "aInvalidBuffer";
    }
    const TwistBufferKey aKey = ResolveBufferKeyFromSymbol(pSymbol);
    if (aKey.IsValid()) {
        return BufAliasName(aKey);
    }
    return BufAliasName(pSymbol.mSlot);
}

std::string BufferKeyToken(TwistBufferKey pKey) {
    return "k:" +
           std::to_string(static_cast<int>(pKey.mKind)) + ":" +
           std::to_string(static_cast<int>(pKey.mDirect)) + ":" +
           std::to_string(static_cast<int>(pKey.mDomain)) + ":" +
           std::to_string(static_cast<int>(pKey.mSaltOwner)) + ":" +
           std::to_string(static_cast<int>(pKey.mSBoxOwner)) + ":" +
           std::to_string(static_cast<int>(pKey.mSaltPhase)) + ":" +
           std::to_string(static_cast<int>(pKey.mSaltLane)) + ":" +
           std::to_string(static_cast<int>(pKey.mSBoxLane));
}

bool BufferKeyFromToken(const std::string &pToken,
                        TwistBufferKey *pKeyOut) {
    if (pKeyOut == nullptr) {
        return false;
    }
    if (pToken.rfind("k:", 0U) != 0U) {
        return false;
    }

    std::string aRemainder = pToken.substr(2U);
    int aValues[8] = {0};
    int aValueCount = 0;
    std::size_t aCursor = 0U;
    while (aCursor <= aRemainder.size()) {
        const std::size_t aColon = aRemainder.find(':', aCursor);
        const std::string aPart = (aColon == std::string::npos)
            ? aRemainder.substr(aCursor)
            : aRemainder.substr(aCursor, aColon - aCursor);
        if ((aValueCount >= 8) || !ParseTokenInt(aPart, &aValues[aValueCount])) {
            return false;
        }
        ++aValueCount;
        if (aColon == std::string::npos) {
            break;
        }
        aCursor = aColon + 1U;
    }
    if (aValueCount != 8) {
        return false;
    }

    TwistBufferKey aKey;
    aKey.mKind = static_cast<TwistBufferKind>(aValues[0]);
    aKey.mDirect = static_cast<TwistDirectBuffer>(aValues[1]);
    aKey.mDomain = static_cast<TwistDomainFamily>(aValues[2]);
    aKey.mSaltOwner = static_cast<TwistSaltOwner>(aValues[3]);
    aKey.mSBoxOwner = static_cast<TwistSBoxOwner>(aValues[4]);
    aKey.mSaltPhase = static_cast<TwistSaltPhase>(aValues[5]);
    aKey.mSaltLane = static_cast<TwistSaltLane>(aValues[6]);
    aKey.mSBoxLane = static_cast<TwistSBoxLane>(aValues[7]);

    *pKeyOut = aKey;
    return aKey.IsValid();
}

TwistBufferKey ResolveBufferKey(const GSymbol &pSymbol) {
    if (!pSymbol.IsBuf()) {
        return TwistBufferKey();
    }
    return ResolveBufferKeyFromSymbol(pSymbol);
}

TwistWorkSpaceSlot ResolveBufferSlot(const GSymbol &pSymbol) {
    if (!pSymbol.IsBuf()) {
        return TwistWorkSpaceSlot::kInvalid;
    }
    if (pSymbol.mSlot != TwistWorkSpaceSlot::kInvalid) {
        return pSymbol.mSlot;
    }
    return ResolveSlotFromBufferKey(ResolveBufferKeyFromSymbol(pSymbol));
}

GSymbol VarSymbol(const std::string &pName) {
    return GSymbol::Var(pName);
}

GSymbol BufSymbol(const TwistWorkSpaceSlot pSlot) {
    return GSymbol::Buf(pSlot);
}

GSymbol BufSymbol(const TwistBufferKey pKey) {
    return GSymbol::Buf(pKey);
}

GSymbol BufParamSymbolDomainSalt(const TwistSaltPhase pPhase, const TwistSaltLane pLane) {
    if ((pPhase == TwistSaltPhase::kOrbiterInit) && (pLane == TwistSaltLane::kA)) {
        return BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitA);
    }
    if ((pPhase == TwistSaltPhase::kOrbiterInit) && (pLane == TwistSaltLane::kB)) {
        return BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltOrbiterInitB);
    }
    if ((pPhase == TwistSaltPhase::kOrbiter) && (pLane == TwistSaltLane::kC)) {
        return BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltOrbiterC);
    }
    if ((pPhase == TwistSaltPhase::kOrbiter) && (pLane == TwistSaltLane::kD)) {
        return BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltOrbiterD);
    }
    if ((pPhase == TwistSaltPhase::kUnwind) && (pLane == TwistSaltLane::kE)) {
        return BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltUnwindE);
    }
    if ((pPhase == TwistSaltPhase::kUnwind) && (pLane == TwistSaltLane::kF)) {
        return BufSymbol(TwistWorkSpaceSlot::kParamDomainSaltUnwindF);
    }
    return GSymbol();
}

GSymbol BufParamSymbolDomainSBox(const TwistSBoxLane pLane) {
    switch (pLane) {
        case TwistSBoxLane::kA: return BufSymbol(TwistWorkSpaceSlot::kParamDomainSBoxA);
        case TwistSBoxLane::kB: return BufSymbol(TwistWorkSpaceSlot::kParamDomainSBoxB);
        case TwistSBoxLane::kC: return BufSymbol(TwistWorkSpaceSlot::kParamDomainSBoxC);
        case TwistSBoxLane::kD: return BufSymbol(TwistWorkSpaceSlot::kParamDomainSBoxD);
        case TwistSBoxLane::kE: return BufSymbol(TwistWorkSpaceSlot::kParamDomainSBoxE);
        case TwistSBoxLane::kF: return BufSymbol(TwistWorkSpaceSlot::kParamDomainSBoxF);
        case TwistSBoxLane::kG: return BufSymbol(TwistWorkSpaceSlot::kParamDomainSBoxG);
        case TwistSBoxLane::kH: return BufSymbol(TwistWorkSpaceSlot::kParamDomainSBoxH);
        default: return GSymbol();
    }
}
