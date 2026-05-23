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
           (pLHS.mDomain == pRHS.mDomain) &&
           (pLHS.mSlot == pRHS.mSlot) &&
           (pLHS.mSaltOwner == pRHS.mSaltOwner) &&
           (pLHS.mSBoxOwner == pRHS.mSBoxOwner) &&
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

const char *ConstantMemberName(TwistConstants pConstant) {
    switch (pConstant) {
        case TwistConstants::kPublicIngress: return "mIngress";
        case TwistConstants::kScatter: return "mScatter";
        case TwistConstants::kCrossIngress: return "mCross";

        case TwistConstants::kDomainConstantPublicIngress: return "mDomainConstantPublicIngress";
        case TwistConstants::kDomainConstantPrivateIngress: return "mDomainConstantPrivateIngress";
        case TwistConstants::kDomainConstantCrossIngress: return "mDomainConstantCrossIngress";

        case TwistConstants::kMatrixSelectA: return "mMatrixSelectA";
        case TwistConstants::kMatrixSelectB: return "mMatrixSelectB";

        case TwistConstants::kMatrixUnrollA: return "mMatrixUnrollA";
        case TwistConstants::kMatrixUnrollB: return "mMatrixUnrollB";

        case TwistConstants::kMatrixSchemeA: return "mMatrixSchemeA";
        case TwistConstants::kMatrixSchemeB: return "mMatrixSchemeB";

        case TwistConstants::kMatrixArgAA: return "mMatrixArgAA";
        case TwistConstants::kMatrixArgAB: return "mMatrixArgAB";
        case TwistConstants::kMatrixArgBA: return "mMatrixArgBA";
        case TwistConstants::kMatrixArgBB: return "mMatrixArgBB";

        case TwistConstants::kMaskMutateA: return "mMaskMutateA";
        case TwistConstants::kMaskMutateB: return "mMaskMutateB";

        case TwistConstants::kInvalid:
        default:
            return nullptr;
    }
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
        case TwistVariable::kNonce: return Var("aNonce");
        case TwistVariable::kParamNonce: return Var("pNonce");
        case TwistVariable::kParamInput: return Var("pInput");
        case TwistVariable::kParamOutput: return Var("pOutput");
        case TwistVariable::kDomainWordIngress: return Var("aDomainWordIngress");
        case TwistVariable::kDomainWordScatter: return Var("aDomainWordScatter");
        case TwistVariable::kDomainWordCross: return Var("aDomainWordCross");
        case TwistVariable::kCarry: return Var("aCarry");

        case TwistVariable::kIngress: return Var("aIngress");
        case TwistVariable::kPrevious: return Var("aPrevious");
        case TwistVariable::kCross: return Var("aCross");
        case TwistVariable::kScatter: return Var("aScatter");

        case TwistVariable::kWandererA: return Var("aWandererA");
        case TwistVariable::kWandererB: return Var("aWandererB");
        case TwistVariable::kWandererC: return Var("aWandererC");
        case TwistVariable::kWandererD: return Var("aWandererD");
        case TwistVariable::kWandererE: return Var("aWandererE");
        case TwistVariable::kWandererF: return Var("aWandererF");
        case TwistVariable::kWandererG: return Var("aWandererG");
        case TwistVariable::kWandererH: return Var("aWandererH");
        case TwistVariable::kWandererI: return Var("aWandererI");
        case TwistVariable::kWandererJ: return Var("aWandererJ");
        case TwistVariable::kWandererK: return Var("aWandererK");

        case TwistVariable::kOrbiterA: return Var("aOrbitA");
        case TwistVariable::kOrbiterB: return Var("aOrbitB");
        case TwistVariable::kOrbiterC: return Var("aOrbitC");
        case TwistVariable::kOrbiterD: return Var("aOrbitD");
        case TwistVariable::kOrbiterE: return Var("aOrbitE");
        case TwistVariable::kOrbiterF: return Var("aOrbitF");
        case TwistVariable::kOrbiterG: return Var("aOrbitG");
        case TwistVariable::kOrbiterH: return Var("aOrbitH");
        case TwistVariable::kOrbiterI: return Var("aOrbitI");
        case TwistVariable::kOrbiterJ: return Var("aOrbitJ");
        case TwistVariable::kOrbiterK: return Var("aOrbitK");

        case TwistVariable::kSelect: return Var("aSelect");
        case TwistVariable::kMatrixUnrollA: return Var("mMatrixUnrollA");
        case TwistVariable::kMatrixUnrollB: return Var("mMatrixUnrollB");
        case TwistVariable::kMatrixSchemeA: return Var("mMatrixSchemeA");
        case TwistVariable::kMatrixSchemeB: return Var("mMatrixSchemeB");
        case TwistVariable::kMatrixArgAA: return Var("mMatrixArgAA");
        case TwistVariable::kMatrixArgAB: return Var("mMatrixArgAB");
        case TwistVariable::kMatrixArgBA: return Var("mMatrixArgBA");
        case TwistVariable::kMatrixArgBB: return Var("mMatrixArgBB");
        case TwistVariable::kMaskMutateA: return Var("mMaskMutateA");
        case TwistVariable::kMaskMutateB: return Var("mMaskMutateB");

        case TwistVariable::kInvalid:
        default:
            return GSymbol();
    }
}

GSymbol GSymbol::Var(TwistDomain pDomain,
                     TwistConstants pConstant) {
    const char *aMemberName = ConstantMemberName(pConstant);
    if (aMemberName == nullptr) {
        return GSymbol();
    }
    
    const char *aFamilyPrefix = nullptr;
    switch (pDomain) {
        case TwistDomain::kPhaseB:
            aFamilyPrefix = "mDomainBundleInbuilt.mPhaseBConstants";
            break;
        case TwistDomain::kPhaseC:
            aFamilyPrefix = "mDomainBundleInbuilt.mPhaseCConstants";
            break;
        case TwistDomain::kInvalid:
        case TwistDomain::kPhaseA:
        default:
            aFamilyPrefix = "mDomainBundleInbuilt.mPhaseAConstants";
            break;
    }
    
    return Var(std::string(aFamilyPrefix) + "." + aMemberName);
}

GSymbol GSymbol::Constant(TwistConstants pConstant) {
    const char *aMemberName = ConstantMemberName(pConstant);
    if (aMemberName == nullptr) {
        return GSymbol();
    }
    return Var(std::string("pConstants->") + aMemberName);
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

        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA: return "domain_orbiter_init_a";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB: return "domain_orbiter_init_b";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC: return "domain_orbiter_init_c";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD: return "domain_orbiter_init_d";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE: return "domain_orbiter_init_e";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF: return "domain_orbiter_init_f";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA: return "domain_orbiter_a";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB: return "domain_orbiter_b";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC: return "domain_orbiter_c";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD: return "domain_orbiter_d";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE: return "domain_orbiter_e";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF: return "domain_orbiter_f";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA: return "domain_Wanderer_a";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB: return "domain_Wanderer_b";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC: return "domain_Wanderer_c";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD: return "domain_Wanderer_d";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE: return "domain_Wanderer_e";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF: return "domain_Wanderer_f";
        case TwistWorkSpaceSlot::kParamDomainSBoxA: return "sbox_a";
        case TwistWorkSpaceSlot::kParamDomainSBoxB: return "sbox_b";
        case TwistWorkSpaceSlot::kParamDomainSBoxC: return "sbox_c";
        case TwistWorkSpaceSlot::kParamDomainSBoxD: return "sbox_d";
        case TwistWorkSpaceSlot::kParamDomainSBoxE: return "sbox_e";
        case TwistWorkSpaceSlot::kParamDomainSBoxF: return "sbox_f";
        case TwistWorkSpaceSlot::kParamDomainSBoxG: return "sbox_g";
        case TwistWorkSpaceSlot::kParamDomainSBoxH: return "sbox_h";
        case TwistWorkSpaceSlot::kExpansionLaneA: return "seed_a";
        case TwistWorkSpaceSlot::kExpansionLaneB: return "seed_b";
        case TwistWorkSpaceSlot::kExpansionLaneC: return "seed_c";
        case TwistWorkSpaceSlot::kExpansionLaneD: return "seed_d";
        case TwistWorkSpaceSlot::kExpansionLaneE: return "seed_e";
        case TwistWorkSpaceSlot::kExpansionLaneF: return "seed_f";

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

        case TwistWorkSpaceSlot::kSnowLaneA: return "snow_a";
        case TwistWorkSpaceSlot::kSnowLaneB: return "snow_b";
        case TwistWorkSpaceSlot::kSnowLaneC: return "snow_c";
        case TwistWorkSpaceSlot::kSnowLaneD: return "snow_d";

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

        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA: return "aOrbiterAssignSaltA";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB: return "aOrbiterAssignSaltB";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC: return "aOrbiterAssignSaltC";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD: return "aOrbiterAssignSaltD";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE: return "aOrbiterAssignSaltE";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF: return "aOrbiterAssignSaltF";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA: return "aOrbiterUpdateSaltA";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB: return "aOrbiterUpdateSaltB";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC: return "aOrbiterUpdateSaltC";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD: return "aOrbiterUpdateSaltD";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE: return "aOrbiterUpdateSaltE";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF: return "aOrbiterUpdateSaltF";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA: return "aWandererUpdateSaltA";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB: return "aWandererUpdateSaltB";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC: return "aWandererUpdateSaltC";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD: return "aWandererUpdateSaltD";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE: return "aWandererUpdateSaltE";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF: return "aWandererUpdateSaltF";
        case TwistWorkSpaceSlot::kParamDomainSBoxA: return "mSBoxA";
        case TwistWorkSpaceSlot::kParamDomainSBoxB: return "mSBoxB";
        case TwistWorkSpaceSlot::kParamDomainSBoxC: return "mSBoxC";
        case TwistWorkSpaceSlot::kParamDomainSBoxD: return "mSBoxD";
        case TwistWorkSpaceSlot::kParamDomainSBoxE: return "mSBoxE";
        case TwistWorkSpaceSlot::kParamDomainSBoxF: return "mSBoxF";
        case TwistWorkSpaceSlot::kParamDomainSBoxG: return "mSBoxG";
        case TwistWorkSpaceSlot::kParamDomainSBoxH: return "mSBoxH";
        case TwistWorkSpaceSlot::kExpansionLaneA: return "aExpandLaneA";
        case TwistWorkSpaceSlot::kExpansionLaneB: return "aExpandLaneB";
        case TwistWorkSpaceSlot::kExpansionLaneC: return "aExpandLaneC";
        case TwistWorkSpaceSlot::kExpansionLaneD: return "aExpandLaneD";
        case TwistWorkSpaceSlot::kExpansionLaneE: return "aExpandLaneE";
        case TwistWorkSpaceSlot::kExpansionLaneF: return "aExpandLaneF";

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

        case TwistWorkSpaceSlot::kSnowLaneA: return "aSnowLaneA";
        case TwistWorkSpaceSlot::kSnowLaneB: return "aSnowLaneB";
        case TwistWorkSpaceSlot::kSnowLaneC: return "aSnowLaneC";
        case TwistWorkSpaceSlot::kSnowLaneD: return "aSnowLaneD";

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
           std::to_string(static_cast<int>(pKey.mDomain)) + ":" +
           std::to_string(static_cast<int>(pKey.mSaltOwner)) + ":" +
           std::to_string(static_cast<int>(pKey.mSBoxOwner)) + ":" +
           std::to_string(static_cast<int>(pKey.mSlot)) + ":" +
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
    int aValues[7] = {0};
    int aValueCount = 0;
    std::size_t aCursor = 0U;
    while (aCursor <= aRemainder.size()) {
        const std::size_t aColon = aRemainder.find(':', aCursor);
        const std::string aPart = (aColon == std::string::npos)
            ? aRemainder.substr(aCursor)
            : aRemainder.substr(aCursor, aColon - aCursor);
        if ((aValueCount >= 7) || !ParseTokenInt(aPart, &aValues[aValueCount])) {
            return false;
        }
        ++aValueCount;
        if (aColon == std::string::npos) {
            break;
        }
        aCursor = aColon + 1U;
    }
    if ((aValueCount != 6) && (aValueCount != 7)) {
        return false;
    }

    const int aKind = aValues[0];
    if ((aKind != static_cast<int>(TwistBufferKind::kSalt)) &&
        (aKind != static_cast<int>(TwistBufferKind::kSBox)) &&
        (aKind != static_cast<int>(TwistBufferKind::kConstants))) {
        return false;
    }

    const int aOffset = (aValueCount == 7) ? 1 : 0;
    TwistBufferKey aKey;
    aKey.mKind = static_cast<TwistBufferKind>(aValues[0]);
    aKey.mDomain = static_cast<TwistDomain>(aValues[1 + aOffset]);
    aKey.mSaltOwner = static_cast<TwistSaltOwner>(aValues[2 + aOffset]);
    aKey.mSBoxOwner = static_cast<TwistSBoxOwner>(aValues[3 + aOffset]);
    aKey.mSlot = static_cast<std::uint16_t>(aValues[4 + aOffset]);
    aKey.mSBoxLane = static_cast<TwistSBoxLane>(aValues[5 + aOffset]);

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

GSymbol BufParamSymbolDomainSalt(TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF:
            return BufSymbol(pSlot);
        default:
            return GSymbol();
    }
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
