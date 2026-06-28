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
    (void)pSlot;
    return TwistBufferKey();
}

TwistWorkSpaceSlot ResolveSlotFromBufferKey(const TwistBufferKey pKey) {
    if (!pKey.IsValid()) {
        return TwistWorkSpaceSlot::kInvalid;
    }
    const TwistWorkSpaceSlot aKeySlot = static_cast<TwistWorkSpaceSlot>(pKey.mSlot);
    if (pKey.IsSalt() && TwistWorkSpace::IsSalt(aKeySlot)) {
        return aKeySlot;
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

bool DecodePhaseSaltSlot(const TwistWorkSpaceSlot pSlot,
                         int *pPhaseOut,
                         int *pRoleOut,
                         int *pLaneOut) {
    const int aValue = static_cast<int>(pSlot);
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kPhaseASaltOrbiterAssignA);
    const int aCountPerPhase = 18;
    const int aPhaseCount = 8;
    if ((aValue < aBase) || (aValue >= (aBase + aCountPerPhase * aPhaseCount))) {
        return false;
    }

    const int aOffset = aValue - aBase;
    const int aRoleLaneOffset = aOffset % aCountPerPhase;
    if (pPhaseOut != nullptr) {
        *pPhaseOut = aOffset / aCountPerPhase;
    }
    if (pRoleOut != nullptr) {
        *pRoleOut = aRoleLaneOffset / 6;
    }
    if (pLaneOut != nullptr) {
        *pLaneOut = aRoleLaneOffset % 6;
    }
    return true;
}

const char *PhaseNameLower(const int pPhase) {
    switch (pPhase) {
        case 0: return "phase_a";
        case 1: return "phase_b";
        case 2: return "phase_c";
        case 3: return "phase_d";
        case 4: return "phase_e";
        case 5: return "phase_f";
        case 6: return "phase_g";
        case 7: return "phase_h";
        default: return "phase_invalid";
    }
}

const char *PhaseNameUpper(const int pPhase) {
    switch (pPhase) {
        case 0: return "PhaseA";
        case 1: return "PhaseB";
        case 2: return "PhaseC";
        case 3: return "PhaseD";
        case 4: return "PhaseE";
        case 5: return "PhaseF";
        case 6: return "PhaseG";
        case 7: return "PhaseH";
        default: return "PhaseInvalid";
    }
}

const char *SaltRoleNameLower(const int pRole) {
    switch (pRole) {
        case 0: return "orbiter_assign";
        case 1: return "orbiter_update";
        case 2: return "wanderer_update";
        default: return "invalid";
    }
}

const char *SaltRoleNameUpper(const int pRole) {
    switch (pRole) {
        case 0: return "OrbiterAssign";
        case 1: return "OrbiterUpdate";
        case 2: return "WandererUpdate";
        default: return "Invalid";
    }
}

char SaltLaneNameLower(const int pLane) {
    return static_cast<char>('a' + pLane);
}

char SaltLaneNameUpper(const int pLane) {
    return static_cast<char>('A' + pLane);
}

const char *DomainPhaseNameUpper(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB: return "PhaseB";
        case TwistDomain::kPhaseC: return "PhaseC";
        case TwistDomain::kPhaseD: return "PhaseD";
        case TwistDomain::kPhaseE: return "PhaseE";
        case TwistDomain::kPhaseF: return "PhaseF";
        case TwistDomain::kPhaseG: return "PhaseG";
        case TwistDomain::kPhaseH: return "PhaseH";
        case TwistDomain::kInvalid:
        case TwistDomain::kPhaseA:
        default:
            return "PhaseA";
    }
}

const char *DomainPhaseConstantsMemberName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB: return "mPhaseBConstants";
        case TwistDomain::kPhaseC: return "mPhaseCConstants";
        case TwistDomain::kPhaseD: return "mPhaseDConstants";
        case TwistDomain::kPhaseE: return "mPhaseEConstants";
        case TwistDomain::kPhaseF: return "mPhaseFConstants";
        case TwistDomain::kPhaseG: return "mPhaseGConstants";
        case TwistDomain::kPhaseH: return "mPhaseHConstants";
        case TwistDomain::kInvalid:
        case TwistDomain::kPhaseA:
        default:
            return "mPhaseAConstants";
    }
}

const char *DomainWordAliasConstantName(const TwistConstants pConstant) {
    switch (pConstant) {
        case TwistConstants::kIngress: return "Ingress";
        case TwistConstants::kScatter: return "Scatter";
        case TwistConstants::kCross: return "Cross";
        default:
            return nullptr;
    }
}

const char *DomainWordMemberName(const TwistConstants pConstant) {
    switch (pConstant) {
        case TwistConstants::kIngress: return "mIngress";
        case TwistConstants::kScatter: return "mScatter";
        case TwistConstants::kCross: return "mCross";
        default:
            return nullptr;
    }
}

std::string PhaseSaltBufName(const TwistWorkSpaceSlot pSlot) {
    int aPhase = 0;
    int aRole = 0;
    int aLane = 0;
    if (!DecodePhaseSaltSlot(pSlot, &aPhase, &aRole, &aLane)) {
        return "";
    }
    std::string aName = PhaseNameLower(aPhase);
    aName += "_salt_";
    aName += SaltRoleNameLower(aRole);
    aName += "_";
    aName.push_back(SaltLaneNameLower(aLane));
    return aName;
}

std::string PhaseSaltAliasName(const TwistWorkSpaceSlot pSlot) {
    int aPhase = 0;
    int aRole = 0;
    int aLane = 0;
    if (!DecodePhaseSaltSlot(pSlot, &aPhase, &aRole, &aLane)) {
        return "";
    }
    std::string aName = "a";
    aName += PhaseNameUpper(aPhase);
    aName += SaltRoleNameUpper(aRole);
    aName += "Salt";
    aName.push_back(SaltLaneNameUpper(aLane));
    return aName;
}

const char *ConstantMemberName(TwistConstants pConstant) {
    switch (pConstant) {
        case TwistConstants::kPublicIngress: return "aIngress";
        case TwistConstants::kScatter: return "aScatter";
        case TwistConstants::kCrossIngress: return "aCross";

        case TwistConstants::kDomainConstantPublicIngress: return "mDomainConstantPublicIngress";
        case TwistConstants::kDomainConstantPrivateIngress: return "mDomainConstantPrivateIngress";
        case TwistConstants::kDomainConstantCrossIngress: return "mDomainConstantCrossIngress";

        case TwistConstants::kMatrixSelectA: return "mMatrixSelectA";
        case TwistConstants::kMatrixSelectB: return "mMatrixSelectB";

        case TwistConstants::kMatrixUnrollA: return "mMatrixUnrollA";
        case TwistConstants::kMatrixUnrollB: return "mMatrixUnrollB";

        case TwistConstants::kMatrixArgA: return "mMatrixArgA";
        case TwistConstants::kMatrixArgB: return "mMatrixArgB";
        case TwistConstants::kMatrixArgC: return "mMatrixArgC";
        case TwistConstants::kMatrixArgD: return "mMatrixArgD";

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
        case TwistVariable::kParamInput: return Buf(TwistWorkSpaceSlot::kParamSource);
        case TwistVariable::kParamOutput: return Buf(TwistWorkSpaceSlot::kParamDestination);
        case TwistVariable::kParamSnow: return Var("pSnow");
            
        case TwistVariable::kDomainWordIngress: return Var("aDomainWordIngress");
        case TwistVariable::kDomainWordScatter: return Var("aDomainWordScatter");
        case TwistVariable::kDomainWordCross: return Var("aDomainWordCross");
            
        case TwistVariable::kDomainWordMatrixSelectA: return Var("aDomainWordMatrixSelectA");
        case TwistVariable::kDomainWordMatrixSelectB: return Var("aDomainWordMatrixSelectB");
            
        case TwistVariable::kDomainWordMatrixUnrollA: return Var("aDomainWordMatrixUnrollA");
        case TwistVariable::kDomainWordMatrixUnrollB: return Var("aDomainWordMatrixUnrollB");
            
        case TwistVariable::kDomainWordMatrixArgA: return Var("aDomainWordMatrixArgA");
        case TwistVariable::kDomainWordMatrixArgB: return Var("aDomainWordMatrixArgB");
            
        case TwistVariable::kDomainWordMatrixArgC: return Var("aDomainWordMatrixArgC");
        case TwistVariable::kDomainWordMatrixArgD: return Var("aDomainWordMatrixArgD");

        case TwistVariable::kDomainWordMaskMutateA: return Var("aDomainWordMaskMutateA");
        case TwistVariable::kDomainWordMaskMutateB: return Var("aDomainWordMaskMutateB");
            
            
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

        case TwistVariable::kOrbiterA: return Var("aOrbiterA");
        case TwistVariable::kOrbiterB: return Var("aOrbiterB");
        case TwistVariable::kOrbiterC: return Var("aOrbiterC");
        case TwistVariable::kOrbiterD: return Var("aOrbiterD");
        case TwistVariable::kOrbiterE: return Var("aOrbiterE");
        case TwistVariable::kOrbiterF: return Var("aOrbiterF");
        case TwistVariable::kOrbiterG: return Var("aOrbiterG");
        case TwistVariable::kOrbiterH: return Var("aOrbiterH");
        case TwistVariable::kOrbiterI: return Var("aOrbiterI");
        case TwistVariable::kOrbiterJ: return Var("aOrbiterJ");
        case TwistVariable::kOrbiterK: return Var("aOrbiterK");

        case TwistVariable::kSelect: return Var("aSelect");
        case TwistVariable::kMatrixUnrollA: return Var("aMatrixUnrollA");
        case TwistVariable::kMatrixUnrollB: return Var("aMatrixUnrollB");
        case TwistVariable::kMatrixArgA: return Var("aMatrixArgA");
        case TwistVariable::kMatrixArgB: return Var("aMatrixArgB");
        case TwistVariable::kMatrixArgC: return Var("aMatrixArgC");
        case TwistVariable::kMatrixArgD: return Var("aMatrixArgD");
        case TwistVariable::kMaskMutateA: return Var("aMaskMutateA");
        case TwistVariable::kMaskMutateB: return Var("aMaskMutateB");

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
        case TwistDomain::kPhaseD:
            aFamilyPrefix = "mDomainBundleInbuilt.mPhaseDConstants";
            break;
        case TwistDomain::kPhaseE:
            aFamilyPrefix = "mDomainBundleInbuilt.mPhaseEConstants";
            break;
        case TwistDomain::kPhaseF:
            aFamilyPrefix = "mDomainBundleInbuilt.mPhaseFConstants";
            break;
        case TwistDomain::kPhaseG:
            aFamilyPrefix = "mDomainBundleInbuilt.mPhaseGConstants";
            break;
        case TwistDomain::kPhaseH:
            aFamilyPrefix = "mDomainBundleInbuilt.mPhaseHConstants";
            break;
        case TwistDomain::kInvalid:
        case TwistDomain::kPhaseA:
        default:
            aFamilyPrefix = "mDomainBundleInbuilt.mPhaseAConstants";
            break;
    }
    
    return Var(std::string(aFamilyPrefix) + "." + aMemberName);
}

GSymbol GSymbol::WorkspaceDomainWord(TwistDomain pDomain,
                                     TwistConstants pConstant) {
    const std::string aName = WorkspaceDomainWordAliasName(pDomain, pConstant);
    if (aName.empty()) {
        return GSymbol();
    }
    return Var(aName);
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
    const std::string aPhaseSaltName = PhaseSaltBufName(pSlot);
    if (!aPhaseSaltName.empty()) {
        return aPhaseSaltName;
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return "src";
        case TwistWorkSpaceSlot::kParamSource: return "param_source";
        case TwistWorkSpaceSlot::kParamDestination: return "param_destination";

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
        case TwistWorkSpaceSlot::kExpansionLaneA: return "seed_a";
        case TwistWorkSpaceSlot::kExpansionLaneB: return "seed_b";
        case TwistWorkSpaceSlot::kExpansionLaneC: return "seed_c";
        case TwistWorkSpaceSlot::kExpansionLaneD: return "seed_d";

        case TwistWorkSpaceSlot::kWorkLaneA: return "work_a";
        case TwistWorkSpaceSlot::kWorkLaneB: return "work_b";
        case TwistWorkSpaceSlot::kWorkLaneC: return "work_c";
        case TwistWorkSpaceSlot::kWorkLaneD: return "work_d";

        case TwistWorkSpaceSlot::kOperationLaneA: return "op_a";
        case TwistWorkSpaceSlot::kOperationLaneB: return "op_b";
        case TwistWorkSpaceSlot::kOperationLaneC: return "op_c";
        case TwistWorkSpaceSlot::kOperationLaneD: return "op_d";

        case TwistWorkSpaceSlot::kSnowLaneA: return "snow_lane_a";
        case TwistWorkSpaceSlot::kSnowLaneB: return "snow_lane_b";
        case TwistWorkSpaceSlot::kSnowLaneC: return "snow_lane_c";
        case TwistWorkSpaceSlot::kSnowLaneD: return "snow_lane_d";
        case TwistWorkSpaceSlot::kFireLaneA: return "fire_a";
        case TwistWorkSpaceSlot::kFireLaneB: return "fire_b";
        case TwistWorkSpaceSlot::kFireLaneC: return "fire_c";
        case TwistWorkSpaceSlot::kFireLaneD: return "fire_d";
        case TwistWorkSpaceSlot::kParamSnow: return "param_snow";
        case TwistWorkSpaceSlot::kInvestA: return "invest_a";
        case TwistWorkSpaceSlot::kInvestB: return "invest_b";
        case TwistWorkSpaceSlot::kInvestC: return "invest_c";
        case TwistWorkSpaceSlot::kInvestD: return "invest_d";
        case TwistWorkSpaceSlot::kInvestE: return "invest_e";
        case TwistWorkSpaceSlot::kInvestF: return "invest_f";
        case TwistWorkSpaceSlot::kInvestG: return "invest_g";
        case TwistWorkSpaceSlot::kInvestH: return "invest_h";

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
    const std::string aPhaseSaltName = PhaseSaltAliasName(pSlot);
    if (!aPhaseSaltName.empty()) {
        return aPhaseSaltName;
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return "mSource";
        case TwistWorkSpaceSlot::kParamSource: return "pSource";
        case TwistWorkSpaceSlot::kParamDestination: return "pDestination";

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
        case TwistWorkSpaceSlot::kExpansionLaneA: return "aExpandLaneA";
        case TwistWorkSpaceSlot::kExpansionLaneB: return "aExpandLaneB";
        case TwistWorkSpaceSlot::kExpansionLaneC: return "aExpandLaneC";
        case TwistWorkSpaceSlot::kExpansionLaneD: return "aExpandLaneD";

        case TwistWorkSpaceSlot::kWorkLaneA: return "aWorkLaneA";
        case TwistWorkSpaceSlot::kWorkLaneB: return "aWorkLaneB";
        case TwistWorkSpaceSlot::kWorkLaneC: return "aWorkLaneC";
        case TwistWorkSpaceSlot::kWorkLaneD: return "aWorkLaneD";

        case TwistWorkSpaceSlot::kOperationLaneA: return "aOperationLaneA";
        case TwistWorkSpaceSlot::kOperationLaneB: return "aOperationLaneB";
        case TwistWorkSpaceSlot::kOperationLaneC: return "aOperationLaneC";
        case TwistWorkSpaceSlot::kOperationLaneD: return "aOperationLaneD";

        case TwistWorkSpaceSlot::kSnowLaneA: return "aSnowLaneA";
        case TwistWorkSpaceSlot::kSnowLaneB: return "aSnowLaneB";
        case TwistWorkSpaceSlot::kSnowLaneC: return "aSnowLaneC";
        case TwistWorkSpaceSlot::kSnowLaneD: return "aSnowLaneD";
        case TwistWorkSpaceSlot::kFireLaneA: return "aFireLaneA";
        case TwistWorkSpaceSlot::kFireLaneB: return "aFireLaneB";
        case TwistWorkSpaceSlot::kFireLaneC: return "aFireLaneC";
        case TwistWorkSpaceSlot::kFireLaneD: return "aFireLaneD";
        case TwistWorkSpaceSlot::kParamSnow: return "pSnow";
        case TwistWorkSpaceSlot::kInvestA: return "aInvestLaneA";
        case TwistWorkSpaceSlot::kInvestB: return "aInvestLaneB";
        case TwistWorkSpaceSlot::kInvestC: return "aInvestLaneC";
        case TwistWorkSpaceSlot::kInvestD: return "aInvestLaneD";
        case TwistWorkSpaceSlot::kInvestE: return "aInvestLaneE";
        case TwistWorkSpaceSlot::kInvestF: return "aInvestLaneF";
        case TwistWorkSpaceSlot::kInvestG: return "aInvestLaneG";
        case TwistWorkSpaceSlot::kInvestH: return "aInvestLaneH";

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

std::string WorkspaceDomainWordAliasName(const TwistDomain domain,
                                         const TwistConstants constant) {
    const char *aConstantName = DomainWordAliasConstantName(constant);
    if (aConstantName == nullptr) {
        return "";
    }
    return std::string("a") + DomainPhaseNameUpper(domain) + "DomainWord" + aConstantName;
}

std::string WorkspaceDomainWordAccessText(const TwistDomain domain,
                                          const TwistConstants constant) {
    const char *aMemberName = DomainWordMemberName(constant);
    if (aMemberName == nullptr) {
        return "";
    }
    return std::string("pWorkSpace->mDomainBundle.") +
           DomainPhaseConstantsMemberName(domain) + "." + aMemberName;
}

bool WorkspaceDomainWordAliasInfo(const std::string &name,
                                  TwistDomain *domainOut,
                                  TwistConstants *constantOut) {
    const TwistDomain aDomains[] = {
        TwistDomain::kPhaseA,
        TwistDomain::kPhaseB,
        TwistDomain::kPhaseC,
        TwistDomain::kPhaseD,
        TwistDomain::kPhaseE,
        TwistDomain::kPhaseF,
        TwistDomain::kPhaseG,
        TwistDomain::kPhaseH
    };
    const TwistConstants aConstants[] = {
        TwistConstants::kIngress,
        TwistConstants::kScatter,
        TwistConstants::kCross
    };

    for (TwistDomain aDomain : aDomains) {
        for (TwistConstants aConstant : aConstants) {
            if (name == WorkspaceDomainWordAliasName(aDomain, aConstant)) {
                if (domainOut != nullptr) {
                    *domainOut = aDomain;
                }
                if (constantOut != nullptr) {
                    *constantOut = aConstant;
                }
                return true;
            }
        }
    }
    return false;
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
    const std::string aPhaseSaltName = PhaseSaltAliasName(pSlot);
    if (!aPhaseSaltName.empty()) {
        return BufSymbol(pSlot);
    }

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
