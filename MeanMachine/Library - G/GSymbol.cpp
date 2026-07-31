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
           (pLHS.mLaneSplit == pRHS.mLaneSplit) &&
           (pLHS.mSaltOwner == pRHS.mSaltOwner);
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
    if (pKey.IsLaneSplit() &&
        (TwistWorkSpace::GetBufferLength(aKeySlot) == S_BLOCK)) {
        return aKeySlot;
    }
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
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kKeyRotateASaltOrbiterAssignA);
    const int aCountPerPhase = 24;
    const int aPhaseCount = 6;
    if ((aValue < aBase) || (aValue >= (aBase + aCountPerPhase * aPhaseCount))) {
        return false;
    }

    const int aOffset = aValue - aBase;
    const int aRoleLaneOffset = aOffset % aCountPerPhase;
    if (pPhaseOut != nullptr) {
        *pPhaseOut = aOffset / aCountPerPhase;
    }
    if (pRoleOut != nullptr) {
        *pRoleOut = aRoleLaneOffset / 8;
    }
    if (pLaneOut != nullptr) {
        *pLaneOut = aRoleLaneOffset % 8;
    }
    return true;
}

const char *PhaseNameLower(const int pPhase) {
    switch (pPhase) {
        case 0: return "key_rotate_a";
        case 1: return "key_spawn_a";
        case 2: return "seed";
        case 3: return "twist";
        case 4: return "key_rotate_b";
        case 5: return "key_spawn_b";
        default: return "domain_invalid";
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

const char *SaltRoleAlias(const int pRole) {
    switch (pRole) {
        case 0: return "OA";
        case 1: return "OU";
        case 2: return "WU";
        default: return "";
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
        case TwistDomain::kKeyRotateA: return "KeyRotateA";
        case TwistDomain::kKeyRotateB: return "KeyRotateB";
        case TwistDomain::kKeySpawnA: return "KeySpawnA";
        case TwistDomain::kKeySpawnB: return "KeySpawnB";
        case TwistDomain::kSeed: return "Seed";
        case TwistDomain::kTwist: return "Twist";
        case TwistDomain::kInvalid:
        default:
            return "Invalid";
    }
}

const char *DomainPhaseConstantsMemberName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kKeyRotateA: return "mKeyRotateAConstants";
        case TwistDomain::kKeyRotateB: return "mKeyRotateBConstants";
        case TwistDomain::kKeySpawnA: return "mKeySpawnAConstants";
        case TwistDomain::kKeySpawnB: return "mKeySpawnBConstants";
        case TwistDomain::kSeed: return "mSeedConstants";
        case TwistDomain::kTwist: return "mTwistConstants";
        case TwistDomain::kInvalid:
        default:
            return "";
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
    int aRole = 0;
    int aLane = 0;
    if (!DecodePhaseSaltSlot(pSlot, nullptr, &aRole, &aLane)) {
        return "";
    }
    std::string aName = "a";
    aName += SaltRoleAlias(aRole);
    aName += "Salt";
    aName.push_back(SaltLaneNameUpper(aLane));
    return aName;
}

const char *ConstantMemberName(TwistConstants pConstant) {
    switch (pConstant) {
        case TwistConstants::kPublicIngress: return "aIngress";
        case TwistConstants::kScatter: return "aScatter";
        case TwistConstants::kCrossIngress: return "aCross";

        case TwistConstants::kMatrixSelectA: return "mMatrixSelectA";
        case TwistConstants::kMatrixSelectB: return "mMatrixSelectB";

        case TwistConstants::kMatrixUnrollA: return "mMatrixUnrollA";
        case TwistConstants::kMatrixUnrollB: return "mMatrixUnrollB";

        case TwistConstants::kMatrixArgA: return "mMatrixArgA";
        case TwistConstants::kMatrixArgB: return "mMatrixArgB";
        case TwistConstants::kMatrixArgC: return "mMatrixArgC";
        case TwistConstants::kMatrixArgD: return "mMatrixArgD";

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
        case TwistDomain::kKeyRotateA:
            aFamilyPrefix = "mDomainBundleInbuilt.mKeyRotateAConstants";
            break;
        case TwistDomain::kKeyRotateB:
            aFamilyPrefix = "mDomainBundleInbuilt.mKeyRotateBConstants";
            break;
        case TwistDomain::kKeySpawnA:
            aFamilyPrefix = "mDomainBundleInbuilt.mKeySpawnAConstants";
            break;
        case TwistDomain::kKeySpawnB:
            aFamilyPrefix = "mDomainBundleInbuilt.mKeySpawnBConstants";
            break;
        case TwistDomain::kSeed:
            aFamilyPrefix = "mDomainBundleInbuilt.mSeedConstants";
            break;
        case TwistDomain::kTwist:
            aFamilyPrefix = "mDomainBundleInbuilt.mTwistConstants";
            break;
        case TwistDomain::kInvalid:
        default:
            return GSymbol();
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
        case TwistWorkSpaceSlot::kSourceLane: return "src";
        case TwistWorkSpaceSlot::kNonceLane: return "nonce";
        case TwistWorkSpaceSlot::kParamSource: return "param_source";
        case TwistWorkSpaceSlot::kParamDestination: return "param_destination";

        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA: return "domain_orbiter_init_a";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB: return "domain_orbiter_init_b";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC: return "domain_orbiter_init_c";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD: return "domain_orbiter_init_d";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE: return "domain_orbiter_init_e";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF: return "domain_orbiter_init_f";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignG: return "domain_orbiter_init_g";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignH: return "domain_orbiter_init_h";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA: return "domain_orbiter_a";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB: return "domain_orbiter_b";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC: return "domain_orbiter_c";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD: return "domain_orbiter_d";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE: return "domain_orbiter_e";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF: return "domain_orbiter_f";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateG: return "domain_orbiter_g";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateH: return "domain_orbiter_h";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA: return "domain_Wanderer_a";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB: return "domain_Wanderer_b";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC: return "domain_Wanderer_c";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD: return "domain_Wanderer_d";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE: return "domain_Wanderer_e";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF: return "domain_Wanderer_f";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateG: return "domain_Wanderer_g";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateH: return "domain_Wanderer_h";
        case TwistWorkSpaceSlot::kHeartLaneA: return "seed_a";
        case TwistWorkSpaceSlot::kHeartLaneB: return "seed_b";
        case TwistWorkSpaceSlot::kHeartLaneC: return "seed_c";
        case TwistWorkSpaceSlot::kHeartLaneD: return "seed_d";

        case TwistWorkSpaceSlot::kSpiritLaneA: return "op_a";
        case TwistWorkSpaceSlot::kSpiritLaneB: return "op_b";
        case TwistWorkSpaceSlot::kSpiritLaneC: return "op_c";
        case TwistWorkSpaceSlot::kSpiritLaneD: return "op_d";

        case TwistWorkSpaceSlot::kParamCrossA: return "param_cross_a";
        case TwistWorkSpaceSlot::kParamCrossB: return "param_cross_b";
        case TwistWorkSpaceSlot::kParamCrossC: return "param_cross_c";
        case TwistWorkSpaceSlot::kParamCrossD: return "param_cross_d";
        case TwistWorkSpaceSlot::kFireLaneA: return "fire_a";
        case TwistWorkSpaceSlot::kFireLaneB: return "fire_b";
        case TwistWorkSpaceSlot::kFireLaneC: return "fire_c";
        case TwistWorkSpaceSlot::kFireLaneD: return "fire_d";
        case TwistWorkSpaceSlot::kWaterLaneA: return "water_a";
        case TwistWorkSpaceSlot::kWaterLaneB: return "water_b";
        case TwistWorkSpaceSlot::kWaterLaneC: return "water_c";
        case TwistWorkSpaceSlot::kWaterLaneD: return "water_d";
        case TwistWorkSpaceSlot::kEarthLaneA: return "earth_a";
        case TwistWorkSpaceSlot::kEarthLaneB: return "earth_b";
        case TwistWorkSpaceSlot::kEarthLaneC: return "earth_c";
        case TwistWorkSpaceSlot::kEarthLaneD: return "earth_d";
        case TwistWorkSpaceSlot::kWindLaneA: return "wind_a";
        case TwistWorkSpaceSlot::kWindLaneB: return "wind_b";
        case TwistWorkSpaceSlot::kWindLaneC: return "wind_c";
        case TwistWorkSpaceSlot::kWindLaneD: return "wind_d";
        case TwistWorkSpaceSlot::kFuseLaneA: return "fuse_a";
        case TwistWorkSpaceSlot::kFuseLaneB: return "fuse_b";
        case TwistWorkSpaceSlot::kFuseLaneC: return "fuse_c";
        case TwistWorkSpaceSlot::kFuseLaneD: return "fuse_d";
        case TwistWorkSpaceSlot::kWoodLaneA: return "scrap_a";
        case TwistWorkSpaceSlot::kWoodLaneB: return "scrap_b";
        case TwistWorkSpaceSlot::kWoodLaneC: return "scrap_c";
        case TwistWorkSpaceSlot::kWoodLaneD: return "scrap_d";
        case TwistWorkSpaceSlot::kLightningLaneA: return "lightning_a";
        case TwistWorkSpaceSlot::kLightningLaneB: return "lightning_b";
        case TwistWorkSpaceSlot::kLightningLaneC: return "lightning_c";
        case TwistWorkSpaceSlot::kLightningLaneD: return "lightning_d";
        case TwistWorkSpaceSlot::kMagmaLaneA: return "magma_a";
        case TwistWorkSpaceSlot::kMagmaLaneB: return "magma_b";
        case TwistWorkSpaceSlot::kMagmaLaneC: return "magma_c";
        case TwistWorkSpaceSlot::kMagmaLaneD: return "magma_d";
        case TwistWorkSpaceSlot::kSoilLaneA: return "soil_a";
        case TwistWorkSpaceSlot::kSoilLaneB: return "soil_b";
        case TwistWorkSpaceSlot::kSoilLaneC: return "soil_c";
        case TwistWorkSpaceSlot::kSoilLaneD: return "soil_d";
        case TwistWorkSpaceSlot::kPlasmaLaneA: return "plasma_a";
        case TwistWorkSpaceSlot::kPlasmaLaneB: return "plasma_b";
        case TwistWorkSpaceSlot::kPlasmaLaneC: return "plasma_c";
        case TwistWorkSpaceSlot::kPlasmaLaneD: return "plasma_d";
        case TwistWorkSpaceSlot::kShadowLaneA: return "shadow_a";
        case TwistWorkSpaceSlot::kShadowLaneB: return "shadow_b";
        case TwistWorkSpaceSlot::kShadowLaneC: return "shadow_c";
        case TwistWorkSpaceSlot::kShadowLaneD: return "shadow_d";
        case TwistWorkSpaceSlot::kCrystalLaneA: return "crystal_a";
        case TwistWorkSpaceSlot::kCrystalLaneB: return "crystal_b";
        case TwistWorkSpaceSlot::kCrystalLaneC: return "crystal_c";
        case TwistWorkSpaceSlot::kCrystalLaneD: return "crystal_d";
        case TwistWorkSpaceSlot::kAetherLaneA: return "aether_a";
        case TwistWorkSpaceSlot::kAetherLaneB: return "aether_b";
        case TwistWorkSpaceSlot::kAetherLaneC: return "aether_c";
        case TwistWorkSpaceSlot::kAetherLaneD: return "aether_d";
        case TwistWorkSpaceSlot::kCelestialLaneA: return "celestial_a";
        case TwistWorkSpaceSlot::kCelestialLaneB: return "celestial_b";
        case TwistWorkSpaceSlot::kCelestialLaneC: return "celestial_c";
        case TwistWorkSpaceSlot::kCelestialLaneD: return "celestial_d";
        case TwistWorkSpaceSlot::kKineticLaneA: return "kinetic_a";
        case TwistWorkSpaceSlot::kKineticLaneB: return "kinetic_b";
        case TwistWorkSpaceSlot::kKineticLaneC: return "kinetic_c";
        case TwistWorkSpaceSlot::kKineticLaneD: return "kinetic_d";
        case TwistWorkSpaceSlot::kVaporLaneA: return "vapor_a";
        case TwistWorkSpaceSlot::kVaporLaneB: return "vapor_b";
        case TwistWorkSpaceSlot::kVaporLaneC: return "vapor_c";
        case TwistWorkSpaceSlot::kVaporLaneD: return "vapor_d";
        case TwistWorkSpaceSlot::kIceLaneA: return "invest_a";
        case TwistWorkSpaceSlot::kIceLaneB: return "invest_b";
        case TwistWorkSpaceSlot::kIceLaneC: return "invest_c";
        case TwistWorkSpaceSlot::kIceLaneD: return "invest_d";

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

        case TwistWorkSpaceSlot::kKeyRowA0: return "key_row_a_0";
        case TwistWorkSpaceSlot::kKeyRowA1: return "key_row_a_1";
        case TwistWorkSpaceSlot::kKeyRowA2: return "key_row_a_2";
        case TwistWorkSpaceSlot::kKeyRowA3: return "key_row_a_3";
        case TwistWorkSpaceSlot::kKeyRowA4: return "key_row_a_4";
        case TwistWorkSpaceSlot::kKeyRowA5: return "key_row_a_5";
        case TwistWorkSpaceSlot::kKeyRowA6: return "key_row_a_6";
        case TwistWorkSpaceSlot::kKeyRowA7: return "key_row_a_7";

        case TwistWorkSpaceSlot::kKeyRowB0: return "key_row_b_0";
        case TwistWorkSpaceSlot::kKeyRowB1: return "key_row_b_1";
        case TwistWorkSpaceSlot::kKeyRowB2: return "key_row_b_2";
        case TwistWorkSpaceSlot::kKeyRowB3: return "key_row_b_3";
        case TwistWorkSpaceSlot::kKeyRowB4: return "key_row_b_4";
        case TwistWorkSpaceSlot::kKeyRowB5: return "key_row_b_5";
        case TwistWorkSpaceSlot::kKeyRowB6: return "key_row_b_6";
        case TwistWorkSpaceSlot::kKeyRowB7: return "key_row_b_7";

        default: return "inv";
    }
}

std::string BufName(TwistBufferKey pKey) {
    const TwistWorkSpaceSlot aSlot = ResolveSlotFromBufferKey(pKey);
    if (aSlot != TwistWorkSpaceSlot::kInvalid) {
        std::string aName = BufName(aSlot);
        if (pKey.IsLaneSplit()) {
            aName += "_split_";
            aName.push_back(static_cast<char>('a' + pKey.mLaneSplit));
        }
        return aName;
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
        case TwistWorkSpaceSlot::kSourceLane: return "aSource";
        case TwistWorkSpaceSlot::kNonceLane: return "aNonceLane";
        case TwistWorkSpaceSlot::kParamSource: return "pSource";
        case TwistWorkSpaceSlot::kParamDestination: return "pDestination";

        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA: return "aOASaltA";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB: return "aOASaltB";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC: return "aOASaltC";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD: return "aOASaltD";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE: return "aOASaltE";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF: return "aOASaltF";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignG: return "aOASaltG";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignH: return "aOASaltH";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA: return "aOUSaltA";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB: return "aOUSaltB";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC: return "aOUSaltC";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD: return "aOUSaltD";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE: return "aOUSaltE";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF: return "aOUSaltF";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateG: return "aOUSaltG";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateH: return "aOUSaltH";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA: return "aWUSaltA";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB: return "aWUSaltB";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC: return "aWUSaltC";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD: return "aWUSaltD";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE: return "aWUSaltE";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF: return "aWUSaltF";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateG: return "aWUSaltG";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateH: return "aWUSaltH";

        case TwistWorkSpaceSlot::kHeartLaneA: return "aHeartLaneA";
        case TwistWorkSpaceSlot::kHeartLaneB: return "aHeartLaneB";
        case TwistWorkSpaceSlot::kHeartLaneC: return "aHeartLaneC";
        case TwistWorkSpaceSlot::kHeartLaneD: return "aHeartLaneD";

        case TwistWorkSpaceSlot::kSpiritLaneA: return "aSpiritLaneA";
        case TwistWorkSpaceSlot::kSpiritLaneB: return "aSpiritLaneB";
        case TwistWorkSpaceSlot::kSpiritLaneC: return "aSpiritLaneC";
        case TwistWorkSpaceSlot::kSpiritLaneD: return "aSpiritLaneD";

        case TwistWorkSpaceSlot::kParamCrossA: return "pCrossLaneA";
        case TwistWorkSpaceSlot::kParamCrossB: return "pCrossLaneB";
        case TwistWorkSpaceSlot::kParamCrossC: return "pCrossLaneC";
        case TwistWorkSpaceSlot::kParamCrossD: return "pCrossLaneD";

        case TwistWorkSpaceSlot::kFireLaneA: return "aFireLaneA";
        case TwistWorkSpaceSlot::kFireLaneB: return "aFireLaneB";
        case TwistWorkSpaceSlot::kFireLaneC: return "aFireLaneC";
        case TwistWorkSpaceSlot::kFireLaneD: return "aFireLaneD";
        case TwistWorkSpaceSlot::kWaterLaneA: return "aWaterLaneA";
        case TwistWorkSpaceSlot::kWaterLaneB: return "aWaterLaneB";
        case TwistWorkSpaceSlot::kWaterLaneC: return "aWaterLaneC";
        case TwistWorkSpaceSlot::kWaterLaneD: return "aWaterLaneD";
        case TwistWorkSpaceSlot::kEarthLaneA: return "aEarthLaneA";
        case TwistWorkSpaceSlot::kEarthLaneB: return "aEarthLaneB";
        case TwistWorkSpaceSlot::kEarthLaneC: return "aEarthLaneC";
        case TwistWorkSpaceSlot::kEarthLaneD: return "aEarthLaneD";
        case TwistWorkSpaceSlot::kWindLaneA: return "aWindLaneA";
        case TwistWorkSpaceSlot::kWindLaneB: return "aWindLaneB";
        case TwistWorkSpaceSlot::kWindLaneC: return "aWindLaneC";
        case TwistWorkSpaceSlot::kWindLaneD: return "aWindLaneD";
        case TwistWorkSpaceSlot::kFuseLaneA: return "aFuseLaneA";
        case TwistWorkSpaceSlot::kFuseLaneB: return "aFuseLaneB";
        case TwistWorkSpaceSlot::kFuseLaneC: return "aFuseLaneC";
        case TwistWorkSpaceSlot::kFuseLaneD: return "aFuseLaneD";
        case TwistWorkSpaceSlot::kWoodLaneA: return "aWoodLaneA";
        case TwistWorkSpaceSlot::kWoodLaneB: return "aWoodLaneB";
        case TwistWorkSpaceSlot::kWoodLaneC: return "aWoodLaneC";
        case TwistWorkSpaceSlot::kWoodLaneD: return "aWoodLaneD";
        case TwistWorkSpaceSlot::kLightningLaneA: return "aLightningLaneA";
        case TwistWorkSpaceSlot::kLightningLaneB: return "aLightningLaneB";
        case TwistWorkSpaceSlot::kLightningLaneC: return "aLightningLaneC";
        case TwistWorkSpaceSlot::kLightningLaneD: return "aLightningLaneD";
        case TwistWorkSpaceSlot::kMagmaLaneA: return "aMagmaLaneA";
        case TwistWorkSpaceSlot::kMagmaLaneB: return "aMagmaLaneB";
        case TwistWorkSpaceSlot::kMagmaLaneC: return "aMagmaLaneC";
        case TwistWorkSpaceSlot::kMagmaLaneD: return "aMagmaLaneD";
        case TwistWorkSpaceSlot::kSoilLaneA: return "aSoilLaneA";
        case TwistWorkSpaceSlot::kSoilLaneB: return "aSoilLaneB";
        case TwistWorkSpaceSlot::kSoilLaneC: return "aSoilLaneC";
        case TwistWorkSpaceSlot::kSoilLaneD: return "aSoilLaneD";
        case TwistWorkSpaceSlot::kPlasmaLaneA: return "aPlasmaLaneA";
        case TwistWorkSpaceSlot::kPlasmaLaneB: return "aPlasmaLaneB";
        case TwistWorkSpaceSlot::kPlasmaLaneC: return "aPlasmaLaneC";
        case TwistWorkSpaceSlot::kPlasmaLaneD: return "aPlasmaLaneD";
        case TwistWorkSpaceSlot::kShadowLaneA: return "aShadowLaneA";
        case TwistWorkSpaceSlot::kShadowLaneB: return "aShadowLaneB";
        case TwistWorkSpaceSlot::kShadowLaneC: return "aShadowLaneC";
        case TwistWorkSpaceSlot::kShadowLaneD: return "aShadowLaneD";
        case TwistWorkSpaceSlot::kCrystalLaneA: return "aCrystalLaneA";
        case TwistWorkSpaceSlot::kCrystalLaneB: return "aCrystalLaneB";
        case TwistWorkSpaceSlot::kCrystalLaneC: return "aCrystalLaneC";
        case TwistWorkSpaceSlot::kCrystalLaneD: return "aCrystalLaneD";
        case TwistWorkSpaceSlot::kAetherLaneA: return "aAetherLaneA";
        case TwistWorkSpaceSlot::kAetherLaneB: return "aAetherLaneB";
        case TwistWorkSpaceSlot::kAetherLaneC: return "aAetherLaneC";
        case TwistWorkSpaceSlot::kAetherLaneD: return "aAetherLaneD";
        case TwistWorkSpaceSlot::kCelestialLaneA: return "aCelestialLaneA";
        case TwistWorkSpaceSlot::kCelestialLaneB: return "aCelestialLaneB";
        case TwistWorkSpaceSlot::kCelestialLaneC: return "aCelestialLaneC";
        case TwistWorkSpaceSlot::kCelestialLaneD: return "aCelestialLaneD";
        case TwistWorkSpaceSlot::kKineticLaneA: return "aKineticLaneA";
        case TwistWorkSpaceSlot::kKineticLaneB: return "aKineticLaneB";
        case TwistWorkSpaceSlot::kKineticLaneC: return "aKineticLaneC";
        case TwistWorkSpaceSlot::kKineticLaneD: return "aKineticLaneD";
        case TwistWorkSpaceSlot::kVaporLaneA: return "aVaporLaneA";
        case TwistWorkSpaceSlot::kVaporLaneB: return "aVaporLaneB";
        case TwistWorkSpaceSlot::kVaporLaneC: return "aVaporLaneC";
        case TwistWorkSpaceSlot::kVaporLaneD: return "aVaporLaneD";
        case TwistWorkSpaceSlot::kIceLaneA: return "aIceLaneA";
        case TwistWorkSpaceSlot::kIceLaneB: return "aIceLaneB";
        case TwistWorkSpaceSlot::kIceLaneC: return "aIceLaneC";
        case TwistWorkSpaceSlot::kIceLaneD: return "aIceLaneD";

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

        case TwistWorkSpaceSlot::kKeyRowA0: return "aKeyRowA0";
        case TwistWorkSpaceSlot::kKeyRowA1: return "aKeyRowA1";
        case TwistWorkSpaceSlot::kKeyRowA2: return "aKeyRowA2";
        case TwistWorkSpaceSlot::kKeyRowA3: return "aKeyRowA3";
        case TwistWorkSpaceSlot::kKeyRowA4: return "aKeyRowA4";
        case TwistWorkSpaceSlot::kKeyRowA5: return "aKeyRowA5";
        case TwistWorkSpaceSlot::kKeyRowA6: return "aKeyRowA6";
        case TwistWorkSpaceSlot::kKeyRowA7: return "aKeyRowA7";

        case TwistWorkSpaceSlot::kKeyRowB0: return "aKeyRowB0";
        case TwistWorkSpaceSlot::kKeyRowB1: return "aKeyRowB1";
        case TwistWorkSpaceSlot::kKeyRowB2: return "aKeyRowB2";
        case TwistWorkSpaceSlot::kKeyRowB3: return "aKeyRowB3";
        case TwistWorkSpaceSlot::kKeyRowB4: return "aKeyRowB4";
        case TwistWorkSpaceSlot::kKeyRowB5: return "aKeyRowB5";
        case TwistWorkSpaceSlot::kKeyRowB6: return "aKeyRowB6";
        case TwistWorkSpaceSlot::kKeyRowB7: return "aKeyRowB7";

        default: return "aInvalidBuffer";
    }
}

std::string BufAliasName(TwistBufferKey pKey) {
    const TwistWorkSpaceSlot aSlot = ResolveSlotFromBufferKey(pKey);
    if (aSlot != TwistWorkSpaceSlot::kInvalid) {
        std::string aName = BufAliasName(aSlot);
        if (pKey.IsLaneSplit()) {
            aName += "_";
            aName.push_back(static_cast<char>('A' + pKey.mLaneSplit));
        }
        return aName;
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
    std::string aToken =
        "k:" +
        std::to_string(static_cast<int>(pKey.mKind)) + ":" +
        std::to_string(static_cast<int>(pKey.mDomain)) + ":" +
        std::to_string(static_cast<int>(pKey.mSaltOwner)) + ":" +
        std::to_string(static_cast<int>(pKey.mSlot));
    if (pKey.IsLaneSplit()) {
        aToken += ":" +
                  std::to_string(
                      static_cast<int>(pKey.mLaneSplit)
                  );
    }
    return aToken;
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
    if ((aValueCount != 4) && (aValueCount != 5) &&
        (aValueCount != 6) && (aValueCount != 7)) {
        return false;
    }

    const int aKind = aValues[0];
    if ((aKind != static_cast<int>(TwistBufferKind::kSalt)) &&
        (aKind != static_cast<int>(TwistBufferKind::kSBox)) &&
        (aKind != static_cast<int>(TwistBufferKind::kConstants)) &&
        (aKind != static_cast<int>(TwistBufferKind::kLaneSplit))) {
        return false;
    }

    TwistBufferKey aKey;
    if ((aValueCount == 4) || (aValueCount == 5)) {
        const bool aIsLaneSplit =
            aKind == static_cast<int>(
                TwistBufferKind::kLaneSplit
            );
        if (aIsLaneSplit != (aValueCount == 5)) {
            return false;
        }
        if (aIsLaneSplit &&
            ((aValues[4] < 0) || (aValues[4] >= 16))) {
            return false;
        }
        aKey.mKind = static_cast<TwistBufferKind>(aValues[0]);
        aKey.mDomain = static_cast<TwistDomain>(aValues[1]);
        aKey.mSaltOwner = static_cast<TwistSaltOwner>(aValues[2]);
        aKey.mSlot = static_cast<std::uint16_t>(aValues[3]);
        if (aValueCount == 5) {
            aKey.mLaneSplit = static_cast<std::uint8_t>(aValues[4]);
        }
    } else {
        const int aOffset = (aValueCount == 7) ? 1 : 0;
        aKey.mKind = static_cast<TwistBufferKind>(aValues[0]);
        aKey.mDomain = static_cast<TwistDomain>(aValues[1 + aOffset]);
        aKey.mSaltOwner = static_cast<TwistSaltOwner>(aValues[2 + aOffset]);
        aKey.mSlot = static_cast<std::uint16_t>(aValues[4 + aOffset]);
    }
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
        TwistDomain::kKeyRotateA,
        TwistDomain::kKeyRotateB,
        TwistDomain::kKeySpawnA,
        TwistDomain::kKeySpawnB,
        TwistDomain::kSeed,
        TwistDomain::kTwist
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
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignG:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignH:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateG:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateH:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateG:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateH:
            return BufSymbol(pSlot);
        default:
            return GSymbol();
    }
}
