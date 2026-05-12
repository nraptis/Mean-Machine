//
//  GSymbol.cpp
//  Superfox
//
//  Created by Dope on 4/20/26.
//

#include "GSymbol.hpp"

GSymbol::GSymbol() {
    Invalidate();
}

GSymbol GSymbol::Var(const std::string &pName) {
    GSymbol aSymbol;
    aSymbol.mType = GSymbolType::kVar;
    aSymbol.mName = pName;
    aSymbol.mSlot = TwistWorkSpaceSlot::kInvalid;
    return aSymbol;
}

GSymbol GSymbol::Buf(const TwistWorkSpaceSlot pSlot) {
    GSymbol aSymbol;
    aSymbol.mType = GSymbolType::kBuf;
    aSymbol.mSlot = pSlot;
    aSymbol.mName = BufName(pSlot);
    return aSymbol;
}

void GSymbol::Set(const GSymbol &pOther) {
    mName = pOther.mName;
    mType = pOther.mType;
    mSlot = pOther.mSlot;
}

void GSymbol::Invalidate() {
    mName = "";
    mType = GSymbolType::kInv;
    mSlot = TwistWorkSpaceSlot::kInvalid;
}

bool GSymbol::IsInvalid() const {
    switch (mType) {
        case GSymbolType::kVar:
            return mName.empty();
        case GSymbolType::kBuf:
            return (mSlot == TwistWorkSpaceSlot::kInvalid);
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
        case GSymbolType::kBuf:
            return pSymbolLHS.mSlot == pSymbolRHS.mSlot;
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

        case TwistWorkSpaceSlot::kSaltA: return "salt_a";
        case TwistWorkSpaceSlot::kSaltB: return "salt_b";
        case TwistWorkSpaceSlot::kSaltC: return "salt_c";
        case TwistWorkSpaceSlot::kSaltD: return "salt_d";
        case TwistWorkSpaceSlot::kSaltE: return "salt_e";
        case TwistWorkSpaceSlot::kSaltF: return "salt_f";
        case TwistWorkSpaceSlot::kSaltG: return "salt_g";
        case TwistWorkSpaceSlot::kSaltH: return "salt_h";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxA: return "domain_keybox_a";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxB: return "domain_keybox_b";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxC: return "domain_keybox_c";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxD: return "domain_keybox_d";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxE: return "domain_keybox_e";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxF: return "domain_keybox_f";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxA: return "domain_maskbox_a";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxB: return "domain_maskbox_b";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxC: return "domain_maskbox_c";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxD: return "domain_maskbox_d";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxE: return "domain_maskbox_e";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxF: return "domain_maskbox_f";
        case TwistWorkSpaceSlot::kDomainSaltWandererA: return "domain_wanderer_a";
        case TwistWorkSpaceSlot::kDomainSaltWandererB: return "domain_wanderer_b";
        case TwistWorkSpaceSlot::kDomainSaltWandererC: return "domain_wanderer_c";
        case TwistWorkSpaceSlot::kDomainSaltWandererD: return "domain_wanderer_d";
        case TwistWorkSpaceSlot::kDomainSaltWandererE: return "domain_wanderer_e";
        case TwistWorkSpaceSlot::kDomainSaltWandererF: return "domain_wanderer_f";
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
        case TwistWorkSpaceSlot::kDomainSaltSourceA: return "domain_source_a";
        case TwistWorkSpaceSlot::kDomainSaltSourceB: return "domain_source_b";
        case TwistWorkSpaceSlot::kDomainSaltSourceC: return "domain_source_c";
        case TwistWorkSpaceSlot::kDomainSaltSourceD: return "domain_source_d";
        case TwistWorkSpaceSlot::kDomainSaltSourceE: return "domain_source_e";
        case TwistWorkSpaceSlot::kDomainSaltSourceF: return "domain_source_f";
        case TwistWorkSpaceSlot::kDerivedSaltA: return "derived_salt_a";
        case TwistWorkSpaceSlot::kDerivedSaltB: return "derived_salt_b";
        case TwistWorkSpaceSlot::kDerivedSaltC: return "derived_salt_c";
        case TwistWorkSpaceSlot::kDerivedSaltD: return "derived_salt_d";
        case TwistWorkSpaceSlot::kDerivedSaltE: return "derived_salt_e";
        case TwistWorkSpaceSlot::kDerivedSaltF: return "derived_salt_f";
        case TwistWorkSpaceSlot::kDerivedSaltG: return "derived_salt_g";
        case TwistWorkSpaceSlot::kDerivedSaltH: return "derived_salt_h";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA: return "derived_salt_orbiter_a";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB: return "derived_salt_orbiter_b";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC: return "derived_salt_orbiter_c";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD: return "derived_salt_orbiter_d";
        case TwistWorkSpaceSlot::kDerivedSaltWandererA: return "derived_salt_wanderer_a";
        case TwistWorkSpaceSlot::kDerivedSaltWandererB: return "derived_salt_wanderer_b";
        case TwistWorkSpaceSlot::kDerivedSaltWandererC: return "derived_salt_wanderer_c";
        case TwistWorkSpaceSlot::kDerivedSaltWandererD: return "derived_salt_wanderer_d";

        case TwistWorkSpaceSlot::kSBoxA: return "sbox_a";
        case TwistWorkSpaceSlot::kSBoxB: return "sbox_b";
        case TwistWorkSpaceSlot::kSBoxC: return "sbox_c";
        case TwistWorkSpaceSlot::kSBoxD: return "sbox_d";
        case TwistWorkSpaceSlot::kSBoxE: return "sbox_e";
        case TwistWorkSpaceSlot::kSBoxF: return "sbox_f";
        case TwistWorkSpaceSlot::kSBoxG: return "sbox_g";
        case TwistWorkSpaceSlot::kSBoxH: return "sbox_h";
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

        case TwistWorkSpaceSlot::kWorkLaneA: return "work_a";
        case TwistWorkSpaceSlot::kWorkLaneB: return "work_b";
        case TwistWorkSpaceSlot::kWorkLaneC: return "work_c";
        case TwistWorkSpaceSlot::kWorkLaneD: return "work_d";

        case TwistWorkSpaceSlot::kOperationLaneA: return "op_a";
        case TwistWorkSpaceSlot::kOperationLaneB: return "op_b";

        case TwistWorkSpaceSlot::kMaskLaneA: return "mask_a";
        case TwistWorkSpaceSlot::kMaskLaneB: return "mask_b";

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

std::string BufAliasName(TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return "pSource";
        case TwistWorkSpaceSlot::kDest: return "pDestination";

        case TwistWorkSpaceSlot::kSaltA: return "mSaltA";
        case TwistWorkSpaceSlot::kSaltB: return "mSaltB";
        case TwistWorkSpaceSlot::kSaltC: return "mSaltC";
        case TwistWorkSpaceSlot::kSaltD: return "mSaltD";
        case TwistWorkSpaceSlot::kSaltE: return "mSaltE";
        case TwistWorkSpaceSlot::kSaltF: return "mSaltF";
        case TwistWorkSpaceSlot::kSaltG: return "mSaltG";
        case TwistWorkSpaceSlot::kSaltH: return "mSaltH";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxA: return "mDomainSaltKeyBoxA";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxB: return "mDomainSaltKeyBoxB";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxC: return "mDomainSaltKeyBoxC";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxD: return "mDomainSaltKeyBoxD";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxE: return "mDomainSaltKeyBoxE";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxF: return "mDomainSaltKeyBoxF";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxA: return "mDomainSaltMaskBoxA";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxB: return "mDomainSaltMaskBoxB";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxC: return "mDomainSaltMaskBoxC";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxD: return "mDomainSaltMaskBoxD";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxE: return "mDomainSaltMaskBoxE";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxF: return "mDomainSaltMaskBoxF";
        case TwistWorkSpaceSlot::kDomainSaltWandererA: return "mDomainSaltWandererA";
        case TwistWorkSpaceSlot::kDomainSaltWandererB: return "mDomainSaltWandererB";
        case TwistWorkSpaceSlot::kDomainSaltWandererC: return "mDomainSaltWandererC";
        case TwistWorkSpaceSlot::kDomainSaltWandererD: return "mDomainSaltWandererD";
        case TwistWorkSpaceSlot::kDomainSaltWandererE: return "mDomainSaltWandererE";
        case TwistWorkSpaceSlot::kDomainSaltWandererF: return "mDomainSaltWandererF";
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
        case TwistWorkSpaceSlot::kDomainSaltSourceA: return "mDomainSaltSourceA";
        case TwistWorkSpaceSlot::kDomainSaltSourceB: return "mDomainSaltSourceB";
        case TwistWorkSpaceSlot::kDomainSaltSourceC: return "mDomainSaltSourceC";
        case TwistWorkSpaceSlot::kDomainSaltSourceD: return "mDomainSaltSourceD";
        case TwistWorkSpaceSlot::kDomainSaltSourceE: return "mDomainSaltSourceE";
        case TwistWorkSpaceSlot::kDomainSaltSourceF: return "mDomainSaltSourceF";
        case TwistWorkSpaceSlot::kDerivedSaltA: return "aDerivedSaltA";
        case TwistWorkSpaceSlot::kDerivedSaltB: return "aDerivedSaltB";
        case TwistWorkSpaceSlot::kDerivedSaltC: return "aDerivedSaltC";
        case TwistWorkSpaceSlot::kDerivedSaltD: return "aDerivedSaltD";
        case TwistWorkSpaceSlot::kDerivedSaltE: return "aDerivedSaltE";
        case TwistWorkSpaceSlot::kDerivedSaltF: return "aDerivedSaltF";
        case TwistWorkSpaceSlot::kDerivedSaltG: return "aDerivedSaltG";
        case TwistWorkSpaceSlot::kDerivedSaltH: return "aDerivedSaltH";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterA: return "aDerivedSaltOrbiterA";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterB: return "aDerivedSaltOrbiterB";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterC: return "aDerivedSaltOrbiterC";
        case TwistWorkSpaceSlot::kDerivedSaltOrbiterD: return "aDerivedSaltOrbiterD";
        case TwistWorkSpaceSlot::kDerivedSaltWandererA: return "aDerivedSaltWandererA";
        case TwistWorkSpaceSlot::kDerivedSaltWandererB: return "aDerivedSaltWandererB";
        case TwistWorkSpaceSlot::kDerivedSaltWandererC: return "aDerivedSaltWandererC";
        case TwistWorkSpaceSlot::kDerivedSaltWandererD: return "aDerivedSaltWandererD";

        case TwistWorkSpaceSlot::kSBoxA: return "mSBoxA";
        case TwistWorkSpaceSlot::kSBoxB: return "mSBoxB";
        case TwistWorkSpaceSlot::kSBoxC: return "mSBoxC";
        case TwistWorkSpaceSlot::kSBoxD: return "mSBoxD";
        case TwistWorkSpaceSlot::kSBoxE: return "mSBoxE";
        case TwistWorkSpaceSlot::kSBoxF: return "mSBoxF";
        case TwistWorkSpaceSlot::kSBoxG: return "mSBoxG";
        case TwistWorkSpaceSlot::kSBoxH: return "mSBoxH";
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

        case TwistWorkSpaceSlot::kWorkLaneA: return "aWorkLaneA";
        case TwistWorkSpaceSlot::kWorkLaneB: return "aWorkLaneB";
        case TwistWorkSpaceSlot::kWorkLaneC: return "aWorkLaneC";
        case TwistWorkSpaceSlot::kWorkLaneD: return "aWorkLaneD";

        case TwistWorkSpaceSlot::kOperationLaneA: return "aOperationLaneA";
        case TwistWorkSpaceSlot::kOperationLaneB: return "aOperationLaneB";

        case TwistWorkSpaceSlot::kMaskLaneA: return "aMaskLaneA";
        case TwistWorkSpaceSlot::kMaskLaneB: return "aMaskLaneB";

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

GSymbol VarSymbol(const std::string &pName) {
    return GSymbol::Var(pName);
}

GSymbol BufSymbol(const TwistWorkSpaceSlot pSlot) {
    return GSymbol::Buf(pSlot);
}
