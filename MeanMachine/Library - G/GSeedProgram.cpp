//
//  GSeedProgram.cpp
//  MeanMachine
//

#include "GSeedProgram.hpp"

#include "GJson.hpp"
#include "Random.hpp"
#include "TwistExpander.hpp"
#include "TwistDiffuse.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMemory.hpp"
#include "TwistMix32.hpp"
#include "TwistShiftBox.hpp"
#include "TwistSnow.hpp"
#include "TwistSquash.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <unordered_map>

using MeanMachine_json::JsonValue;

namespace {

void SetError(std::string *pError,
              const std::string &pMessage) {
    if (pError != NULL) {
        *pError = pMessage;
    }
}

bool ParseInt32(const JsonValue &pValue,
                int *pResult);

bool StartsWithText(const std::string &pText,
                    const std::string &pPrefix);

bool IsIndexListSlot(TwistWorkSpaceSlot pSlot);

template <typename T>
void AppendUnique(std::vector<T> *pValues,
                  const T &pValue) {
    if (pValues == NULL) {
        return;
    }
    for (const T &aExisting : *pValues) {
        if (aExisting == pValue) {
            return;
        }
    }
    pValues->push_back(pValue);
}

bool IsDeclarableScalarName(const std::string &pName) {
    if (pName.empty()) {
        return false;
    }
    const unsigned char aFirst = static_cast<unsigned char>(pName[0]);
    if ((std::isalpha(aFirst) == 0) && (pName[0] != '_')) {
        return false;
    }
    for (const char aChar : pName) {
        const unsigned char aByte = static_cast<unsigned char>(aChar);
        if ((std::isalnum(aByte) == 0) && (aChar != '_')) {
            return false;
        }
    }
    return true;
}

bool IsParameterVariableName(const std::string &pName) {
    return (pName == "pNonce") ||
           (pName == "pSnow") ||
           (pName == "pSource") ||
           (pName == "pDestination") ||
           (pName == "pInput") ||
           (pName == "pOutput");
}

bool IsParameterBufferSymbol(const GSymbol &pSymbol) {
    return pSymbol.IsVar() &&
           ((pSymbol.mName == "pSource") ||
            (pSymbol.mName == "pDestination") ||
            (pSymbol.mName == "pInput") ||
            (pSymbol.mName == "pOutput"));
}

bool IsImplicitPointerSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource:
        case TwistWorkSpaceSlot::kParamSource:
        case TwistWorkSpaceSlot::kParamDestination:
        case TwistWorkSpaceSlot::kParamSnow:
            return true;
        default:
            return false;
    }
}

std::string CppBufferAlias(const GSymbol &pSymbol) {
    if (IsParameterBufferSymbol(pSymbol)) {
        if (pSymbol.mName == "pInput") {
            return BufAliasName(TwistWorkSpaceSlot::kParamSource);
        }
        if (pSymbol.mName == "pSource") {
            return BufAliasName(TwistWorkSpaceSlot::kParamSource);
        }
        if ((pSymbol.mName == "pOutput") || (pSymbol.mName == "pDestination")) {
            return BufAliasName(TwistWorkSpaceSlot::kParamDestination);
        }
        return pSymbol.mName;
    }
    return BufAliasName(pSymbol.mSlot);
}

void AppendUniqueVariableName(std::vector<std::string> *pNames,
                              const std::string &pName) {
    if (IsParameterVariableName(pName)) {
        return;
    }
    if (IsDeclarableScalarName(pName)) {
        AppendUnique(pNames, pName);
    }
}

bool IsPhaseSaltSlot(const TwistWorkSpaceSlot pSlot) {
    const int aValue = static_cast<int>(pSlot);
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kPhaseASaltOrbiterAssignA);
    const int aCount = 18 * 8;
    return (aValue >= aBase) && (aValue < (aBase + aCount));
}

void AppendPhaseSaltSlots(std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pSlots == nullptr) {
        return;
    }
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kPhaseASaltOrbiterAssignA);
    const int aCount = 18 * 8;
    for (int aOffset = 0; aOffset < aCount; ++aOffset) {
        pSlots->push_back(static_cast<TwistWorkSpaceSlot>(aBase + aOffset));
    }
}

std::vector<TwistWorkSpaceSlot> BuildKnownWorkspaceSlots() {
    std::vector<TwistWorkSpaceSlot> aSlots = {
        TwistWorkSpaceSlot::kSource,
        TwistWorkSpaceSlot::kParamSource,
        TwistWorkSpaceSlot::kParamDestination,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF,
        TwistWorkSpaceSlot::kExpansionLaneA,
        TwistWorkSpaceSlot::kExpansionLaneB,
        TwistWorkSpaceSlot::kExpansionLaneC,
        TwistWorkSpaceSlot::kExpansionLaneD,
        TwistWorkSpaceSlot::kWorkLaneA,
        TwistWorkSpaceSlot::kWorkLaneB,
        TwistWorkSpaceSlot::kWorkLaneC,
        TwistWorkSpaceSlot::kWorkLaneD,
        TwistWorkSpaceSlot::kOperationLaneA,
        TwistWorkSpaceSlot::kOperationLaneB,
        TwistWorkSpaceSlot::kOperationLaneC,
        TwistWorkSpaceSlot::kOperationLaneD,
        TwistWorkSpaceSlot::kSnowLaneA,
        TwistWorkSpaceSlot::kSnowLaneB,
        TwistWorkSpaceSlot::kSnowLaneC,
        TwistWorkSpaceSlot::kSnowLaneD,
        TwistWorkSpaceSlot::kFireLaneA,
        TwistWorkSpaceSlot::kFireLaneB,
        TwistWorkSpaceSlot::kFireLaneC,
        TwistWorkSpaceSlot::kFireLaneD,
        TwistWorkSpaceSlot::kWaterLaneA,
        TwistWorkSpaceSlot::kWaterLaneB,
        TwistWorkSpaceSlot::kWaterLaneC,
        TwistWorkSpaceSlot::kWaterLaneD,
        TwistWorkSpaceSlot::kEarthLaneA,
        TwistWorkSpaceSlot::kEarthLaneB,
        TwistWorkSpaceSlot::kEarthLaneC,
        TwistWorkSpaceSlot::kEarthLaneD,
        TwistWorkSpaceSlot::kWindLaneA,
        TwistWorkSpaceSlot::kWindLaneB,
        TwistWorkSpaceSlot::kWindLaneC,
        TwistWorkSpaceSlot::kWindLaneD,
        TwistWorkSpaceSlot::kFuseLaneA,
        TwistWorkSpaceSlot::kFuseLaneB,
        TwistWorkSpaceSlot::kFuseLaneC,
        TwistWorkSpaceSlot::kFuseLaneD,
        TwistWorkSpaceSlot::kScrapLaneA,
        TwistWorkSpaceSlot::kScrapLaneB,
        TwistWorkSpaceSlot::kScrapLaneC,
        TwistWorkSpaceSlot::kScrapLaneD,
        TwistWorkSpaceSlot::kMergeLaneA,
        TwistWorkSpaceSlot::kMergeLaneB,
        TwistWorkSpaceSlot::kMergeLaneC,
        TwistWorkSpaceSlot::kMergeLaneD,
        TwistWorkSpaceSlot::kInvestA,
        TwistWorkSpaceSlot::kInvestB,
        TwistWorkSpaceSlot::kInvestC,
        TwistWorkSpaceSlot::kInvestD,
        TwistWorkSpaceSlot::kInvestE,
        TwistWorkSpaceSlot::kInvestF,
        TwistWorkSpaceSlot::kInvestG,
        TwistWorkSpaceSlot::kInvestH,
        TwistWorkSpaceSlot::kIndexList256A,
        TwistWorkSpaceSlot::kIndexList256B,
        TwistWorkSpaceSlot::kIndexList256C,
        TwistWorkSpaceSlot::kIndexList256D,
        TwistWorkSpaceSlot::kKeyBoxUnrolledA,
        TwistWorkSpaceSlot::kKeyBoxUnrolledB,
        TwistWorkSpaceSlot::kKeyRowReadA,
        TwistWorkSpaceSlot::kKeyRowReadB,
        TwistWorkSpaceSlot::kKeyRowWriteA,
        TwistWorkSpaceSlot::kKeyRowWriteB,
        TwistWorkSpaceSlot::kParamSnow,
    };
    AppendPhaseSaltSlots(&aSlots);
    return aSlots;
}

const std::vector<TwistWorkSpaceSlot> &KnownWorkspaceSlots() {
    static const std::vector<TwistWorkSpaceSlot> kSlots = BuildKnownWorkspaceSlots();
    return kSlots;
}

std::string SlotToken(const TwistWorkSpaceSlot pSlot) {
    if (IsPhaseSaltSlot(pSlot)) {
        return BufName(pSlot);
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return "source";
        case TwistWorkSpaceSlot::kParamSource: return "param_source";
        case TwistWorkSpaceSlot::kParamDestination: return "param_destination";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA: return "param_domain_salt_orbiter_init_a";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB: return "param_domain_salt_orbiter_init_b";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC: return "param_domain_salt_orbiter_init_c";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD: return "param_domain_salt_orbiter_init_d";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE: return "param_domain_salt_orbiter_init_e";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF: return "param_domain_salt_orbiter_init_f";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA: return "param_domain_salt_orbiter_a";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB: return "param_domain_salt_orbiter_b";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC: return "param_domain_salt_orbiter_c";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD: return "param_domain_salt_orbiter_d";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE: return "param_domain_salt_orbiter_e";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF: return "param_domain_salt_orbiter_f";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA: return "param_domain_salt_Wanderer_a";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB: return "param_domain_salt_Wanderer_b";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC: return "param_domain_salt_Wanderer_c";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD: return "param_domain_salt_Wanderer_d";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE: return "param_domain_salt_Wanderer_e";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF: return "param_domain_salt_Wanderer_f";
        case TwistWorkSpaceSlot::kExpansionLaneA: return "seed_lane_a";
        case TwistWorkSpaceSlot::kExpansionLaneB: return "seed_lane_b";
        case TwistWorkSpaceSlot::kExpansionLaneC: return "seed_lane_c";
        case TwistWorkSpaceSlot::kExpansionLaneD: return "seed_lane_d";
        case TwistWorkSpaceSlot::kWorkLaneA: return "work_lane_a";
        case TwistWorkSpaceSlot::kWorkLaneB: return "work_lane_b";
        case TwistWorkSpaceSlot::kWorkLaneC: return "work_lane_c";
        case TwistWorkSpaceSlot::kWorkLaneD: return "work_lane_d";
        case TwistWorkSpaceSlot::kOperationLaneA: return "operation_lane_a";
        case TwistWorkSpaceSlot::kOperationLaneB: return "operation_lane_b";
        case TwistWorkSpaceSlot::kOperationLaneC: return "operation_lane_c";
        case TwistWorkSpaceSlot::kOperationLaneD: return "operation_lane_d";
        case TwistWorkSpaceSlot::kSnowLaneA: return "snow_lane_a";
        case TwistWorkSpaceSlot::kSnowLaneB: return "snow_lane_b";
        case TwistWorkSpaceSlot::kSnowLaneC: return "snow_lane_c";
        case TwistWorkSpaceSlot::kSnowLaneD: return "snow_lane_d";
        case TwistWorkSpaceSlot::kFireLaneA: return "fire_lane_a";
        case TwistWorkSpaceSlot::kFireLaneB: return "fire_lane_b";
        case TwistWorkSpaceSlot::kFireLaneC: return "fire_lane_c";
        case TwistWorkSpaceSlot::kFireLaneD: return "fire_lane_d";
        case TwistWorkSpaceSlot::kWaterLaneA: return "water_lane_a";
        case TwistWorkSpaceSlot::kWaterLaneB: return "water_lane_b";
        case TwistWorkSpaceSlot::kWaterLaneC: return "water_lane_c";
        case TwistWorkSpaceSlot::kWaterLaneD: return "water_lane_d";
        case TwistWorkSpaceSlot::kEarthLaneA: return "earth_lane_a";
        case TwistWorkSpaceSlot::kEarthLaneB: return "earth_lane_b";
        case TwistWorkSpaceSlot::kEarthLaneC: return "earth_lane_c";
        case TwistWorkSpaceSlot::kEarthLaneD: return "earth_lane_d";
        case TwistWorkSpaceSlot::kWindLaneA: return "wind_lane_a";
        case TwistWorkSpaceSlot::kWindLaneB: return "wind_lane_b";
        case TwistWorkSpaceSlot::kWindLaneC: return "wind_lane_c";
        case TwistWorkSpaceSlot::kWindLaneD: return "wind_lane_d";
        case TwistWorkSpaceSlot::kFuseLaneA: return "fuse_lane_a";
        case TwistWorkSpaceSlot::kFuseLaneB: return "fuse_lane_b";
        case TwistWorkSpaceSlot::kFuseLaneC: return "fuse_lane_c";
        case TwistWorkSpaceSlot::kFuseLaneD: return "fuse_lane_d";
        case TwistWorkSpaceSlot::kScrapLaneA: return "scrap_lane_a";
        case TwistWorkSpaceSlot::kScrapLaneB: return "scrap_lane_b";
        case TwistWorkSpaceSlot::kScrapLaneC: return "scrap_lane_c";
        case TwistWorkSpaceSlot::kScrapLaneD: return "scrap_lane_d";
        case TwistWorkSpaceSlot::kMergeLaneA: return "merge_lane_a";
        case TwistWorkSpaceSlot::kMergeLaneB: return "merge_lane_b";
        case TwistWorkSpaceSlot::kMergeLaneC: return "merge_lane_c";
        case TwistWorkSpaceSlot::kMergeLaneD: return "merge_lane_d";
        case TwistWorkSpaceSlot::kParamSnow: return "param_snow";
        case TwistWorkSpaceSlot::kInvestA: return "invest_lane_a";
        case TwistWorkSpaceSlot::kInvestB: return "invest_lane_b";
        case TwistWorkSpaceSlot::kInvestC: return "invest_lane_c";
        case TwistWorkSpaceSlot::kInvestD: return "invest_lane_d";
        case TwistWorkSpaceSlot::kInvestE: return "invest_lane_e";
        case TwistWorkSpaceSlot::kInvestF: return "invest_lane_f";
        case TwistWorkSpaceSlot::kInvestG: return "invest_lane_g";
        case TwistWorkSpaceSlot::kInvestH: return "invest_lane_h";
        case TwistWorkSpaceSlot::kIndexList256A: return "index_list_256_a";
        case TwistWorkSpaceSlot::kIndexList256B: return "index_list_256_b";
        case TwistWorkSpaceSlot::kIndexList256C: return "index_list_256_c";
        case TwistWorkSpaceSlot::kIndexList256D: return "index_list_256_d";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return "key_box_unrolled_a";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return "key_box_unrolled_b";
        case TwistWorkSpaceSlot::kKeyRowReadA: return "key_row_read_a";
        case TwistWorkSpaceSlot::kKeyRowReadB: return "key_row_read_b";
        case TwistWorkSpaceSlot::kKeyRowWriteA: return "key_row_write_a";
        case TwistWorkSpaceSlot::kKeyRowWriteB: return "key_row_write_b";
        default:
            return "slot_" + std::to_string(static_cast<int>(pSlot));
    }
}

bool SlotFromToken(const std::string &pToken,
                   TwistWorkSpaceSlot *pSlot) {
    if (pSlot == NULL) {
        return false;
    }

    if ((pToken == "param_input_source") || (pToken == "param_source")) {
        *pSlot = TwistWorkSpaceSlot::kParamSource;
        return true;
    }
    if ((pToken == "param_output_destination") || (pToken == "param_destination")) {
        *pSlot = TwistWorkSpaceSlot::kParamDestination;
        return true;
    }
    if ((pToken == "dest") || (pToken == "dst")) {
        *pSlot = TwistWorkSpaceSlot::kParamDestination;
        return true;
    }
    if ((pToken == "snow") || (pToken == "param_snow")) {
        *pSlot = TwistWorkSpaceSlot::kParamSnow;
        return true;
    }

    const std::vector<TwistWorkSpaceSlot> &kSlots = KnownWorkspaceSlots();

    for (TwistWorkSpaceSlot aSlot : kSlots) {
        if (SlotToken(aSlot) == pToken) {
            *pSlot = aSlot;
            return true;
        }
    }
    if (StartsWithText(pToken, "slot_")) {
        const std::string aNumeric = pToken.substr(5U);
        int aSlotValue = 0;
        if (ParseInt32(JsonValue::String(aNumeric), &aSlotValue)) {
            *pSlot = static_cast<TwistWorkSpaceSlot>(aSlotValue);
            return true;
        }
    }
    return false;
}

std::string ExprTypeToken(const GExprType pType) {
    switch (pType) {
        case GExprType::kInv: return "inv";
        case GExprType::kSymbol: return "symbol";
        case GExprType::kConst: return "const";
        case GExprType::kRead: return "read";
        case GExprType::kAdd: return "add";
        case GExprType::kSub: return "sub";
        case GExprType::kMul: return "mul";
        case GExprType::kXor: return "xor";
        case GExprType::kAnd: return "and";
        case GExprType::kOr: return "or";
        case GExprType::kRotL8: return "rotl8";
        case GExprType::kRotL32: return "rotl32";
        case GExprType::kRotL64: return "rotl64";
        case GExprType::kShiftL: return "shl";
        case GExprType::kShiftR: return "shr";
        case GExprType::kDiffuse64A: return "diffuse64_a";
        case GExprType::kDiffuse64B: return "diffuse64_b";
        case GExprType::kDiffuse64C: return "diffuse64_c";
        case GExprType::kDiffuse32A: return "diffuse32_a";
        case GExprType::kDiffuse32B: return "diffuse32_b";
        case GExprType::kDiffuse32C: return "diffuse32_c";
        case GExprType::kCast32: return "cast32";
        default: return "inv";
    }
}

bool ExprTypeFromToken(const std::string &pToken,
                       GExprType *pType) {
    if (pType == NULL) {
        return false;
    }
    if ((pToken == "inv") || (pToken == "kInv") || (pToken == "invalid") || (pToken == "kInvalid")) {
        *pType = GExprType::kInv;
        return true;
    }
    if (pToken == "symbol") { *pType = GExprType::kSymbol; return true; }
    if (pToken == "const") { *pType = GExprType::kConst; return true; }
    if (pToken == "read") { *pType = GExprType::kRead; return true; }
    if (pToken == "add") { *pType = GExprType::kAdd; return true; }
    if (pToken == "sub") { *pType = GExprType::kSub; return true; }
    if (pToken == "mul") { *pType = GExprType::kMul; return true; }
    if (pToken == "xor") { *pType = GExprType::kXor; return true; }
    if (pToken == "and") { *pType = GExprType::kAnd; return true; }
    if (pToken == "or") { *pType = GExprType::kOr; return true; }
    if (pToken == "rotl8") { *pType = GExprType::kRotL8; return true; }
    if (pToken == "rotl32") { *pType = GExprType::kRotL32; return true; }
    if (pToken == "rotl64") { *pType = GExprType::kRotL64; return true; }
    if (pToken == "shl") { *pType = GExprType::kShiftL; return true; }
    if (pToken == "shr") { *pType = GExprType::kShiftR; return true; }
    if ((pToken == "diffuse64_a") || (pToken == "diffuse_a64")) { *pType = GExprType::kDiffuse64A; return true; }
    if ((pToken == "diffuse64_b") || (pToken == "diffuse_b64")) { *pType = GExprType::kDiffuse64B; return true; }
    if ((pToken == "diffuse64_c") || (pToken == "diffuse_c64")) { *pType = GExprType::kDiffuse64C; return true; }
    if (pToken == "diffuse32_a") { *pType = GExprType::kDiffuse32A; return true; }
    if (pToken == "diffuse32_b") { *pType = GExprType::kDiffuse32B; return true; }
    if (pToken == "diffuse32_c") { *pType = GExprType::kDiffuse32C; return true; }
    if (pToken == "cast32") { *pType = GExprType::kCast32; return true; }
    return false;
}

std::string ReadWrapTypeToken(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kNone: return "none";
        case GReadWrapType::kBlock: return "block";
        case GReadWrapType::kSBox: return "sbox";
        case GReadWrapType::kSalt: return "salt";
        case GReadWrapType::kKeyA: return "key_a";
        case GReadWrapType::kKeyB: return "key_b";
        default: return "none";
    }
}

bool ReadWrapTypeFromToken(const std::string &pToken,
                           GReadWrapType *pType) {
    if (pType == NULL) {
        return false;
    }
    if ((pToken == "none") || (pToken == "kNone")) { *pType = GReadWrapType::kNone; return true; }
    if ((pToken == "block") || (pToken == "kBlock")) { *pType = GReadWrapType::kBlock; return true; }
    if ((pToken == "sbox") || (pToken == "kSBox")) { *pType = GReadWrapType::kSBox; return true; }
    if ((pToken == "salt") || (pToken == "kSalt")) { *pType = GReadWrapType::kSalt; return true; }
    if ((pToken == "key_a") || (pToken == "kKeyA")) { *pType = GReadWrapType::kKeyA; return true; }
    if ((pToken == "key_b") || (pToken == "kKeyB")) { *pType = GReadWrapType::kKeyB; return true; }
    return false;
}

std::string AssignTypeToken(const GAssignType pType) {
    switch (pType) {
        case GAssignType::kSet: return "set";
        case GAssignType::kAddAssign: return "add_assign";
        case GAssignType::kXorAssign: return "xor_assign";
        case GAssignType::kOrAssign: return "or_assign";
        default: return "invalid";
    }
}

bool AssignTypeFromToken(const std::string &pToken,
                         GAssignType *pType) {
    if (pType == NULL) {
        return false;
    }
    if ((pToken == "invalid") || (pToken == "kInvalid")) { *pType = GAssignType::kInvalid; return true; }
    if (pToken == "set") { *pType = GAssignType::kSet; return true; }
    if (pToken == "add_assign") { *pType = GAssignType::kAddAssign; return true; }
    if (pToken == "xor_assign") { *pType = GAssignType::kXorAssign; return true; }
    if (pToken == "or_assign") { *pType = GAssignType::kOrAssign; return true; }
    
    return false;
}

bool ParseInt64(const JsonValue &pValue,
                std::int64_t *pResult) {
    if (pResult == NULL) {
        return false;
    }
    if (pValue.is_string()) {
        try {
            *pResult = static_cast<std::int64_t>(std::stoll(pValue.as_string()));
            return true;
        } catch (...) {
            return false;
        }
    }
    if (pValue.is_number()) {
        const double aValue = pValue.as_number();
        if ((aValue < static_cast<double>(std::numeric_limits<std::int64_t>::min())) ||
            (aValue > static_cast<double>(std::numeric_limits<std::int64_t>::max()))) {
            return false;
        }
        *pResult = static_cast<std::int64_t>(aValue);
        return true;
    }
    return false;
}

bool ParseUInt64(const JsonValue &pValue,
                 std::uint64_t *pResult) {
    if (pResult == NULL) {
        return false;
    }
    if (pValue.is_string()) {
        try {
            *pResult = static_cast<std::uint64_t>(std::stoull(pValue.as_string()));
            return true;
        } catch (...) {
            return false;
        }
    }
    if (pValue.is_number()) {
        const double aValue = pValue.as_number();
        if ((aValue < 0.0) ||
            (aValue > static_cast<double>(std::numeric_limits<std::uint64_t>::max()))) {
            return false;
        }
        *pResult = static_cast<std::uint64_t>(aValue);
        return true;
    }
    return false;
}

bool ParseInt32(const JsonValue &pValue,
                int *pResult) {
    std::int64_t aValue = 0;
    if (!ParseInt64(pValue, &aValue)) {
        return false;
    }
    if ((aValue < static_cast<std::int64_t>(std::numeric_limits<int>::min())) ||
        (aValue > static_cast<std::int64_t>(std::numeric_limits<int>::max()))) {
        return false;
    }
    *pResult = static_cast<int>(aValue);
    return true;
}

std::string Indent(const std::size_t pCount) {
    return std::string(pCount * 4U, ' ');
}

std::string TrimRuntimeLine(const std::string &pText) {
    std::size_t aStart = 0U;
    while ((aStart < pText.size()) && (std::isspace(static_cast<unsigned char>(pText[aStart])) != 0)) {
        ++aStart;
    }
    std::size_t aEnd = pText.size();
    while ((aEnd > aStart) && (std::isspace(static_cast<unsigned char>(pText[aEnd - 1U])) != 0)) {
        --aEnd;
    }
    return pText.substr(aStart, aEnd - aStart);
}

std::string StripRuntimeLineComments(const std::string &pText) {
    std::ostringstream aStream;
    std::size_t aCursor = 0U;
    bool aNeedsNewline = false;

    while (aCursor <= pText.size()) {
        std::size_t aLineEnd = pText.find('\n', aCursor);
        if (aLineEnd == std::string::npos) {
            aLineEnd = pText.size();
        }

        std::string aLine = pText.substr(aCursor, aLineEnd - aCursor);
        const std::size_t aComment = aLine.find("//");
        if (aComment != std::string::npos) {
            aLine = aLine.substr(0U, aComment);
        }

        if (aNeedsNewline) {
            aStream << '\n';
        }
        aStream << aLine;
        aNeedsNewline = true;

        if (aLineEnd >= pText.size()) {
            break;
        }
        aCursor = aLineEnd + 1U;
    }

    return aStream.str();
}

bool ParseRuntimeIntToken(std::string pToken,
                          const std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                          int *pValueOut) {
    if ((pVariables == nullptr) || (pValueOut == nullptr)) {
        return false;
    }

    pToken = TrimRuntimeLine(pToken);
    if (pToken.empty()) {
        return false;
    }

    const std::string aStaticCastPrefix = "static_cast<";
    while (pToken.rfind(aStaticCastPrefix, 0U) == 0U) {
        const std::size_t aCastClose = pToken.find(">(");
        if ((aCastClose == std::string::npos) || pToken.empty() || (pToken.back() != ')')) {
            break;
        }
        pToken = TrimRuntimeLine(pToken.substr(aCastClose + 2U,
                                               pToken.size() - aCastClose - 3U));
        if (pToken.empty()) {
            return false;
        }
    }

    const auto aVariable = pVariables->find(pToken);
    if (aVariable != pVariables->end()) {
        *pValueOut = static_cast<int>(aVariable->second);
        return true;
    }

    while (!pToken.empty()) {
        const char aLast = pToken.back();
        if ((aLast == 'u') || (aLast == 'U') || (aLast == 'l') || (aLast == 'L')) {
            pToken.pop_back();
            pToken = TrimRuntimeLine(pToken);
            continue;
        }
        break;
    }

    if (pToken.empty()) {
        return false;
    }

    char *aEnd = nullptr;
    const long aValue = std::strtol(pToken.c_str(), &aEnd, 0);
    if ((aEnd == nullptr) || (*aEnd != '\0')) {
        return false;
    }

    *pValueOut = static_cast<int>(aValue);
    return true;
}

bool ParseRuntimeScalarToken(std::string pToken,
                             const std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                             GRuntimeScalar *pValueOut) {
    if ((pVariables == nullptr) || (pValueOut == nullptr)) {
        return false;
    }

    pToken = TrimRuntimeLine(pToken);
    if (pToken.empty()) {
        return false;
    }

    const std::string aStaticCastPrefix = "static_cast<";
    while (pToken.rfind(aStaticCastPrefix, 0U) == 0U) {
        const std::size_t aCastClose = pToken.find(">(");
        if ((aCastClose == std::string::npos) || pToken.empty() || (pToken.back() != ')')) {
            break;
        }
        pToken = TrimRuntimeLine(pToken.substr(aCastClose + 2U,
                                               pToken.size() - aCastClose - 3U));
        if (pToken.empty()) {
            return false;
        }
    }

    const auto aVariable = pVariables->find(pToken);
    if (aVariable != pVariables->end()) {
        *pValueOut = aVariable->second;
        return true;
    }

    while (!pToken.empty()) {
        const char aLast = pToken.back();
        if ((aLast == 'u') || (aLast == 'U') || (aLast == 'l') || (aLast == 'L')) {
            pToken.pop_back();
            pToken = TrimRuntimeLine(pToken);
            continue;
        }
        break;
    }

    if (pToken.empty()) {
        return false;
    }

    char *aEnd = nullptr;
    const unsigned long long aValue = std::strtoull(pToken.c_str(), &aEnd, 0);
    if ((aEnd == nullptr) || (*aEnd != '\0')) {
        return false;
    }

    *pValueOut = static_cast<GRuntimeScalar>(aValue);
    return true;
}

bool ParseRuntimeSizeToken(const std::string &pToken,
                           const std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                           std::size_t *pValueOut) {
    if (pValueOut == nullptr) {
        return false;
    }

    const std::string aToken = TrimRuntimeLine(pToken);
    if (aToken == "S_BLOCK") { *pValueOut = S_BLOCK; return true; }
    if (aToken == "W_KEY") { *pValueOut = W_KEY; return true; }

    int aValue = 0;
    if (!ParseRuntimeIntToken(aToken, pVariables, &aValue) || (aValue < 0)) {
        return false;
    }
    *pValueOut = static_cast<std::size_t>(aValue);
    return true;
}

bool ResolveRuntimeAliasSlot(const std::string &pAlias,
                             TwistWorkSpaceSlot *pSlotOut) {
    if (pSlotOut == nullptr) {
        return false;
    }

    const std::string aAlias = TrimRuntimeLine(pAlias);
    if ((aAlias == "aSource") || (aAlias == "mSource")) {
        *pSlotOut = TwistWorkSpaceSlot::kSource;
        return true;
    }
    if ((aAlias == "pSource") || (aAlias == "pSourceInput") || (aAlias == "pInput")) {
        *pSlotOut = TwistWorkSpaceSlot::kParamSource;
        return true;
    }
    if ((aAlias == "aDestination") || (aAlias == "mDest")) {
        *pSlotOut = TwistWorkSpaceSlot::kParamDestination;
        return true;
    }
    if ((aAlias == "pDestination") || (aAlias == "pOutput")) {
        *pSlotOut = TwistWorkSpaceSlot::kParamDestination;
        return true;
    }

    for (TwistWorkSpaceSlot aSlot : KnownWorkspaceSlots()) {
        if (BufAliasName(aSlot) == aAlias) {
            *pSlotOut = aSlot;
            return true;
        }
    }

    return false;
}

std::uint8_t *ResolveRuntimeBufferSlot(TwistWorkSpace *pWorkSpace,
                                       TwistExpander *pExpander,
                                       const TwistWorkSpaceSlot pSlot) {
    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        return nullptr;
    }

    return TwistWorkSpace::GetBuffer(pWorkSpace, pExpander, pSlot);
}

bool ResolveRuntimeBufferPointerExpression(const std::string &pExpression,
                                           TwistWorkSpace *pWorkSpace,
                                           TwistExpander *pExpander,
                                           const std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                           std::uint8_t **pPointerOut) {
    if (pPointerOut == nullptr) {
        return false;
    }

    std::string aExpression = TrimRuntimeLine(pExpression);
    std::size_t aPlus = aExpression.find('+');
    std::string aAlias = (aPlus == std::string::npos)
        ? aExpression
        : TrimRuntimeLine(aExpression.substr(0U, aPlus));
    std::string aOffsetText = (aPlus == std::string::npos)
        ? std::string()
        : TrimRuntimeLine(aExpression.substr(aPlus + 1U));

    TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
    if (!ResolveRuntimeAliasSlot(aAlias, &aSlot)) {
        return false;
    }

    std::uint8_t *aBase = ResolveRuntimeBufferSlot(pWorkSpace, pExpander, aSlot);
    if (aBase == nullptr) {
        return false;
    }

    int aOffset = 0;
    if (!aOffsetText.empty() && !ParseRuntimeIntToken(aOffsetText, pVariables, &aOffset)) {
        return false;
    }

    *pPointerOut = aBase + aOffset;
    return true;
}

bool SplitRuntimeCallArguments(const std::string &pArgsText,
                               std::vector<std::string> *pArgsOut) {
    if (pArgsOut == nullptr) {
        return false;
    }

    std::vector<std::string> aArgs;
    std::size_t aCursor = 0U;
    while (aCursor < pArgsText.size()) {
        const std::size_t aComma = pArgsText.find(',', aCursor);
        std::string aToken = (aComma == std::string::npos)
            ? pArgsText.substr(aCursor)
            : pArgsText.substr(aCursor, aComma - aCursor);
        aToken = TrimRuntimeLine(aToken);
        if (!aToken.empty()) {
            aArgs.push_back(aToken);
        }
        if (aComma == std::string::npos) {
            break;
        }
        aCursor = aComma + 1U;
    }

    *pArgsOut = std::move(aArgs);
    return true;
}

bool ParseRuntimeM88DispatchLine(const std::string &pRawLine,
                                 std::vector<std::string> *pArgsOut) {
    if (pArgsOut == nullptr) {
        return false;
    }

    std::string aLine = StripRuntimeLineComments(pRawLine);
    aLine = TrimRuntimeLine(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }

    const std::string aPrefix = "mMatrix.Dispatch";
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        return false;
    }

    std::size_t aOpen = aPrefix.size();
    while ((aOpen < aLine.size()) && (std::isspace(static_cast<unsigned char>(aLine[aOpen])) != 0)) {
        ++aOpen;
    }
    if ((aOpen >= aLine.size()) || (aLine[aOpen] != '(')) {
        return false;
    }
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        return false;
    }

    return SplitRuntimeCallArguments(aLine.substr(aOpen + 1U, aClose - aOpen - 1U), pArgsOut);
}

void CollectRuntimeM88DispatchSlots(const std::string &pRawLine,
                                    std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pSlots == nullptr) {
        return;
    }

    std::vector<std::string> aArgs;
    if (!ParseRuntimeM88DispatchLine(pRawLine, &aArgs) || (aArgs.size() != 11U)) {
        return;
    }

    const int aBufferArgIndexes[3] = { 0, 2, 4 };
    for (const int aArgIndex : aBufferArgIndexes) {
        std::string aAlias = TrimRuntimeLine(aArgs[static_cast<std::size_t>(aArgIndex)]);
        const std::size_t aPlus = aAlias.find('+');
        if (aPlus != std::string::npos) {
            aAlias = TrimRuntimeLine(aAlias.substr(0U, aPlus));
        }

        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (ResolveRuntimeAliasSlot(aAlias, &aSlot)) {
            AppendUnique(pSlots, aSlot);
        }
    }
}

void CollectRuntimeSquashSlots(const std::string &pRawLine,
                               std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pSlots == nullptr) {
        return;
    }

    std::string aLine = StripRuntimeLineComments(pRawLine);
    aLine = TrimRuntimeLine(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }

    const std::string aPrefix = "TwistSquash::";
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        return;
    }

    const std::size_t aOpen = aLine.find('(', aPrefix.size());
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        return;
    }

    std::vector<std::string> aArgs;
    if (!SplitRuntimeCallArguments(aLine.substr(aOpen + 1U, aClose - aOpen - 1U), &aArgs)) {
        return;
    }

    for (const std::string &aArg : aArgs) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (ResolveRuntimeAliasSlot(aArg, &aSlot)) {
            AppendUnique(pSlots, aSlot);
        }
    }
}

bool ParseRuntimeDiffuseLine(const std::string &pRawLine,
                             std::string *pMethodOut,
                             std::vector<std::string> *pArgsOut) {
    if (pArgsOut == nullptr) {
        return false;
    }

    std::string aLine = StripRuntimeLineComments(pRawLine);
    aLine = TrimRuntimeLine(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }

    const std::string aPrefix = "TwistDiffuse::";
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        return false;
    }

    const std::size_t aOpen = aLine.find('(', aPrefix.size());
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        return false;
    }

    if (pMethodOut != nullptr) {
        *pMethodOut = aLine.substr(aPrefix.size(), aOpen - aPrefix.size());
    }
    return SplitRuntimeCallArguments(aLine.substr(aOpen + 1U, aClose - aOpen - 1U), pArgsOut);
}

void CollectRuntimeDiffuseSlots(const std::string &pRawLine,
                                std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pSlots == nullptr) {
        return;
    }

    std::string aMethod;
    std::vector<std::string> aArgs;
    if (!ParseRuntimeDiffuseLine(pRawLine, &aMethod, &aArgs) ||
        ((aMethod != "Diffuse") && (aMethod != "DiffuseWithDomainWords")) ||
        (aArgs.size() < 12U)) {
        return;
    }

    for (std::size_t aArgumentIndex = 0U; aArgumentIndex < 12U; aArgumentIndex += 1U) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (ResolveRuntimeAliasSlot(aArgs[aArgumentIndex], &aSlot)) {
            AppendUnique(pSlots, aSlot);
        }
    }
}

void CollectRuntimeMemorySlots(const std::string &pRawLine,
                               std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pSlots == nullptr) {
        return;
    }
    
    std::string aLine = pRawLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimRuntimeLine(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }
    
    const std::string aPrefix = "TwistMemory::";
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        return;
    }
    
    const std::size_t aOpen = aLine.find('(', aPrefix.size());
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        return;
    }
    
    const std::string aMethod = aLine.substr(aPrefix.size(), aOpen - aPrefix.size());
    std::vector<std::string> aArgs;
    if (!SplitRuntimeCallArguments(aLine.substr(aOpen + 1U, aClose - aOpen - 1U), &aArgs)) {
        return;
    }
    
    std::size_t aBufferArgumentCount = 0U;
    if ((aMethod == "ZeroBlock") ||
        (aMethod == "ZeroKeyBoxA") ||
        (aMethod == "ZeroKeyBoxB")) {
        aBufferArgumentCount = 1U;
    } else if (aMethod == "Copy") {
        aBufferArgumentCount = 2U;
    }
    
    for (std::size_t aArgumentIndex = 0U; (aArgumentIndex < aBufferArgumentCount) && (aArgumentIndex < aArgs.size()); aArgumentIndex += 1U) {
        std::string aAlias = TrimRuntimeLine(aArgs[aArgumentIndex]);
        const std::size_t aPlus = aAlias.find('+');
        if (aPlus != std::string::npos) {
            aAlias = TrimRuntimeLine(aAlias.substr(0U, aPlus));
        }
        
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (ResolveRuntimeAliasSlot(aAlias, &aSlot)) {
            AppendUnique(pSlots, aSlot);
        }
    }
}

bool ExecuteRuntimeRawMatrixLine(const std::string &pRawLine,
                                 TwistWorkSpace *pWorkSpace,
                                 TwistExpander *pExpander,
                                 const std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                 bool *pExecuted,
                                 std::string *pError) {
    if (pExecuted != nullptr) {
        *pExecuted = false;
    }
    if ((pWorkSpace == nullptr) || (pExpander == nullptr) || (pVariables == nullptr)) {
        return true;
    }

    std::vector<std::string> aArgs;
    if (!ParseRuntimeM88DispatchLine(pRawLine, &aArgs)) {
        return true;
    }
    if (pExecuted != nullptr) {
        *pExecuted = true;
    }

    if (aArgs.size() != 11U) {
        SetError(pError, "M88 Dispatch expected 11 arguments.");
        return false;
    }

    std::uint8_t *aOperationData = nullptr;
    if (!ResolveRuntimeBufferPointerExpression(aArgs[0], pWorkSpace, pExpander, pVariables, &aOperationData)) {
        SetError(pError, "M88 Dispatch operation data was invalid: " + aArgs[0]);
        return false;
    }

    std::size_t aOperationIndex = 0U;
    if (!ParseRuntimeSizeToken(aArgs[1], pVariables, &aOperationIndex)) {
        SetError(pError, "M88 Dispatch operation index was invalid: " + aArgs[1]);
        return false;
    }

    std::uint8_t *aSource = nullptr;
    if (!ResolveRuntimeBufferPointerExpression(aArgs[2], pWorkSpace, pExpander, pVariables, &aSource)) {
        SetError(pError, "M88 Dispatch source was invalid: " + aArgs[2]);
        return false;
    }

    std::size_t aSourceIndex = 0U;
    if (!ParseRuntimeSizeToken(aArgs[3], pVariables, &aSourceIndex)) {
        SetError(pError, "M88 Dispatch source index was invalid: " + aArgs[3]);
        return false;
    }

    std::uint8_t *aDestination = nullptr;
    if (!ResolveRuntimeBufferPointerExpression(aArgs[4], pWorkSpace, pExpander, pVariables, &aDestination)) {
        SetError(pError, "M88 Dispatch destination was invalid: " + aArgs[4]);
        return false;
    }

    std::size_t aDestinationIndex = 0U;
    if (!ParseRuntimeSizeToken(aArgs[5], pVariables, &aDestinationIndex)) {
        SetError(pError, "M88 Dispatch destination index was invalid: " + aArgs[5]);
        return false;
    }

    int aUnrollDomainWord = 0;
    if (!ParseRuntimeIntToken(aArgs[6], pVariables, &aUnrollDomainWord)) {
        SetError(pError, "M88 Dispatch unroll domain word was invalid: " + aArgs[6]);
        return false;
    }

    int aArgADomainWord = 0;
    if (!ParseRuntimeIntToken(aArgs[7], pVariables, &aArgADomainWord)) {
        SetError(pError, "M88 Dispatch arg A domain word was invalid: " + aArgs[7]);
        return false;
    }

    int aArgBDomainWord = 0;
    if (!ParseRuntimeIntToken(aArgs[8], pVariables, &aArgBDomainWord)) {
        SetError(pError, "M88 Dispatch arg B domain word was invalid: " + aArgs[8]);
        return false;
    }

    int aArgCDomainWord = 0;
    if (!ParseRuntimeIntToken(aArgs[9], pVariables, &aArgCDomainWord)) {
        SetError(pError, "M88 Dispatch arg C domain word was invalid: " + aArgs[9]);
        return false;
    }

    int aArgDDomainWord = 0;
    if (!ParseRuntimeIntToken(aArgs[10], pVariables, &aArgDDomainWord)) {
        SetError(pError, "M88 Dispatch arg D domain word was invalid: " + aArgs[10]);
        return false;
    }

    pExpander->mMatrix.Dispatch(aOperationData,
                                aOperationIndex,
                                aSource,
                                aSourceIndex,
                                aDestination,
                                aDestinationIndex,
                                static_cast<std::uint8_t>(aUnrollDomainWord),
                                static_cast<std::uint8_t>(aArgADomainWord),
                                static_cast<std::uint8_t>(aArgBDomainWord),
                                static_cast<std::uint8_t>(aArgCDomainWord),
                                static_cast<std::uint8_t>(aArgDDomainWord));
    return true;
}

bool ExecuteRuntimeRawIndexShuffleLine(const std::string &pRawLine,
                                       TwistWorkSpace *pWorkSpace,
                                       TwistExpander *pExpander,
                                       bool *pExecuted,
                                       std::string *pError) {
    if (pExecuted != nullptr) {
        *pExecuted = false;
    }
    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        return true;
    }

    std::string aLine = pRawLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimRuntimeLine(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }

    std::string aPrefix = "TwistIndexShuffle::ExecuteA";
    bool aUseExecuteB = false;
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        aPrefix = "TwistIndexShuffle::ExecuteB";
        aUseExecuteB = true;
    }
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        aPrefix = "TwistIndexShuffle::Execute256";
        aUseExecuteB = false;
    }
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        return true;
    }
    if (pExecuted != nullptr) {
        *pExecuted = true;
    }

    const std::size_t aOpen = aLine.find('(', aPrefix.size());
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        SetError(pError, "Index shuffle call was malformed.");
        return false;
    }

    std::vector<std::string> aArgs;
    if (!SplitRuntimeCallArguments(aLine.substr(aOpen + 1U, aClose - aOpen - 1U), &aArgs) ||
        (aArgs.size() != 2U)) {
        SetError(pError, "Index shuffle expected 2 arguments.");
        return false;
    }

    TwistWorkSpaceSlot aDestSlot = TwistWorkSpaceSlot::kInvalid;
    if (!ResolveRuntimeAliasSlot(aArgs[0], &aDestSlot) || !IsIndexListSlot(aDestSlot)) {
        SetError(pError, "Index shuffle destination was invalid: " + aArgs[0]);
        return false;
    }
    std::uint8_t *aDestBytes = ResolveRuntimeBufferSlot(pWorkSpace, pExpander, aDestSlot);
    if (aDestBytes == nullptr) {
        SetError(pError, "Index shuffle destination resolved to null.");
        return false;
    }

    TwistWorkSpaceSlot aSourceSlot = TwistWorkSpaceSlot::kInvalid;
    if (!ResolveRuntimeAliasSlot(aArgs[1], &aSourceSlot)) {
        SetError(pError, "Index shuffle source was invalid: " + aArgs[1]);
        return false;
    }
    std::uint8_t *aSourceBytes = ResolveRuntimeBufferSlot(pWorkSpace, pExpander, aSourceSlot);
    if (aSourceBytes == nullptr) {
        SetError(pError, "Index shuffle source resolved to null.");
        return false;
    }

    std::size_t *aDest = reinterpret_cast<std::size_t *>(aDestBytes);
    if (aUseExecuteB) {
        TwistIndexShuffle::ExecuteB(aDest, aSourceBytes);
    } else {
        TwistIndexShuffle::ExecuteA(aDest, aSourceBytes);
    }
    return true;
}

bool ExecuteRuntimeRawMemoryLine(const std::string &pRawLine,
                                 TwistWorkSpace *pWorkSpace,
                                 TwistExpander *pExpander,
                                 bool *pExecuted,
                                 std::string *pError) {
    if (pExecuted != nullptr) {
        *pExecuted = false;
    }
    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        return true;
    }

    std::string aLine = pRawLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimRuntimeLine(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }

    const std::string aPrefix = "TwistMemory::";
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        return true;
    }
    if (pExecuted != nullptr) {
        *pExecuted = true;
    }

    const std::size_t aOpen = aLine.find('(', aPrefix.size());
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        SetError(pError, "Memory call was malformed.");
        return false;
    }

    const std::string aMethod = aLine.substr(aPrefix.size(), aOpen - aPrefix.size());
    std::vector<std::string> aArgs;
    if (!SplitRuntimeCallArguments(aLine.substr(aOpen + 1U, aClose - aOpen - 1U), &aArgs)) {
        SetError(pError, "Memory call arguments were malformed.");
        return false;
    }

    auto ResolveBufferArg = [&](const std::string &pArg, std::uint8_t **pBufferOut) -> bool {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveRuntimeAliasSlot(pArg, &aSlot)) {
            SetError(pError, "Memory buffer argument was invalid: " + pArg);
            return false;
        }
        *pBufferOut = ResolveRuntimeBufferSlot(pWorkSpace, pExpander, aSlot);
        if (*pBufferOut == nullptr) {
            SetError(pError, "Memory buffer argument resolved to null: " + pArg);
            return false;
        }
        return true;
    };

    if ((aMethod == "ZeroBlock") ||
        (aMethod == "ZeroKeyBoxA") ||
        (aMethod == "ZeroKeyBoxB")) {
        if (aArgs.size() != 1U) {
            SetError(pError, "Memory zero call expected 1 argument.");
            return false;
        }
        std::uint8_t *aBuffer = nullptr;
        if (!ResolveBufferArg(aArgs[0], &aBuffer)) {
            return false;
        }
        if (aMethod == "ZeroBlock") {
            TwistMemory::ZeroBlock(aBuffer);
        } else if (aMethod == "ZeroKeyBoxA") {
            TwistMemory::ZeroKeyBoxA(aBuffer);
        } else if (aMethod == "ZeroKeyBoxB") {
            TwistMemory::ZeroKeyBoxB(aBuffer);
        }
        return true;
    }

    if (aMethod == "Copy") {
        if (aArgs.size() != 3U) {
            SetError(pError, "Memory copy call expected 3 arguments.");
            return false;
        }
        std::uint8_t *aDest = nullptr;
        std::uint8_t *aSource = nullptr;
        if (!ResolveBufferArg(aArgs[0], &aDest) ||
            !ResolveBufferArg(aArgs[1], &aSource)) {
            return false;
        }
        std::string aLengthToken = TrimRuntimeLine(aArgs[2]);
        if (!aLengthToken.empty() && ((aLengthToken.back() == 'U') || (aLengthToken.back() == 'u'))) {
            aLengthToken.pop_back();
        }
        int aLength = 0;
        if (!ParseRuntimeIntToken(aLengthToken, nullptr, &aLength) || (aLength < 0)) {
            SetError(pError, "Memory copy length was invalid: " + aArgs[2]);
            return false;
        }
        TwistMemory::Copy(aDest, aSource, static_cast<std::uint32_t>(aLength));
        return true;
    }

    if (aMethod == "SwapBlock") {
        if (aArgs.size() != 3U) {
            SetError(pError, "Memory swap call expected 3 arguments.");
            return false;
        }
        std::uint8_t *aBufferA = nullptr;
        std::uint8_t *aBufferB = nullptr;
        std::uint8_t *aTemp = nullptr;
        if (!ResolveBufferArg(aArgs[0], &aBufferA) ||
            !ResolveBufferArg(aArgs[1], &aBufferB) ||
            !ResolveBufferArg(aArgs[2], &aTemp)) {
            return false;
        }
        TwistMemory::SwapBlock(aBufferA, aBufferB, aTemp);
        return true;
    }

    SetError(pError, "Memory call method was unsupported: " + aMethod);
    return false;
}

bool ExecuteRuntimeRawSquashLine(const std::string &pRawLine,
                                 TwistWorkSpace *pWorkSpace,
                                 TwistExpander *pExpander,
                                 bool *pExecuted,
                                 std::string *pError) {
    if (pExecuted != nullptr) {
        *pExecuted = false;
    }
    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        return true;
    }

    std::string aLine = pRawLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimRuntimeLine(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }

    const std::string aPrefix = "TwistSquash::";
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        return true;
    }
    if (pExecuted != nullptr) {
        *pExecuted = true;
    }

    const std::size_t aOpen = aLine.find('(', aPrefix.size());
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        SetError(pError, "Squash call was malformed.");
        return false;
    }

    const std::string aMethod = aLine.substr(aPrefix.size(), aOpen - aPrefix.size());
    std::vector<std::string> aArgs;
    if (!SplitRuntimeCallArguments(aLine.substr(aOpen + 1U, aClose - aOpen - 1U), &aArgs) ||
        (aArgs.size() != 5U)) {
        SetError(pError, "Squash call expected 5 arguments.");
        return false;
    }

    std::uint8_t *aBuffers[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
    for (std::size_t aIndex = 0U; aIndex < 5U; aIndex += 1U) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveRuntimeAliasSlot(aArgs[aIndex], &aSlot)) {
            SetError(pError, "Squash buffer argument was invalid: " + aArgs[aIndex]);
            return false;
        }
        aBuffers[aIndex] = ResolveRuntimeBufferSlot(pWorkSpace, pExpander, aSlot);
        if (aBuffers[aIndex] == nullptr) {
            SetError(pError, "Squash buffer argument resolved to null: " + aArgs[aIndex]);
            return false;
        }
    }

    if (aMethod == "SquashA") {
        TwistSquash::SquashA(aBuffers[0], aBuffers[1], aBuffers[2], aBuffers[3], aBuffers[4]);
    } else if (aMethod == "SquashB") {
        TwistSquash::SquashB(aBuffers[0], aBuffers[1], aBuffers[2], aBuffers[3], aBuffers[4]);
    } else if (aMethod == "SquashC") {
        TwistSquash::SquashC(aBuffers[0], aBuffers[1], aBuffers[2], aBuffers[3], aBuffers[4]);
    } else {
        SetError(pError, "Squash call method was unsupported: " + aMethod);
        return false;
    }

    return true;
}

bool ExecuteRuntimeRawDiffuseLine(const std::string &pRawLine,
                                  TwistWorkSpace *pWorkSpace,
                                  TwistExpander *pExpander,
                                  const std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                  bool *pExecuted,
                                  std::string *pError) {
    if (pExecuted != nullptr) {
        *pExecuted = false;
    }
    if ((pWorkSpace == nullptr) || (pExpander == nullptr) || (pVariables == nullptr)) {
        return true;
    }

    std::string aMethod;
    std::vector<std::string> aArgs;
    if (!ParseRuntimeDiffuseLine(pRawLine, &aMethod, &aArgs)) {
        return true;
    }
    if (pExecuted != nullptr) {
        *pExecuted = true;
    }

    const bool aUseDomainWords = (aMethod == "DiffuseWithDomainWords");
    if ((aMethod != "Diffuse") && !aUseDomainWords) {
        SetError(pError, "Diffuse call method was unsupported: " + aMethod);
        return false;
    }

    const std::size_t aExpectedCount = aUseDomainWords ? 21U : 13U;
    if (aArgs.size() != aExpectedCount) {
        SetError(pError, "Diffuse call expected " + std::to_string(aExpectedCount) + " arguments.");
        return false;
    }

    auto ResolveBufferArg = [&](const std::size_t pArgumentIndex,
                                const char *pLabel,
                                std::uint8_t **pBufferOut) -> bool {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveRuntimeAliasSlot(aArgs[pArgumentIndex], &aSlot)) {
            SetError(pError, std::string("Diffuse ") + pLabel + " was invalid: " + aArgs[pArgumentIndex]);
            return false;
        }
        *pBufferOut = ResolveRuntimeBufferSlot(pWorkSpace, pExpander, aSlot);
        if (*pBufferOut == nullptr) {
            SetError(pError, std::string("Diffuse ") + pLabel + " resolved to null: " + aArgs[pArgumentIndex]);
            return false;
        }
        return true;
    };

    auto ResolveIndexListArg = [&](const std::size_t pArgumentIndex,
                                   const char *pLabel,
                                   std::size_t **pIndexListOut) -> bool {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveRuntimeAliasSlot(aArgs[pArgumentIndex], &aSlot) || !IsIndexListSlot(aSlot)) {
            SetError(pError, std::string("Diffuse ") + pLabel + " was invalid: " + aArgs[pArgumentIndex]);
            return false;
        }
        std::uint8_t *aBuffer = ResolveRuntimeBufferSlot(pWorkSpace, pExpander, aSlot);
        if (aBuffer == nullptr) {
            SetError(pError, std::string("Diffuse ") + pLabel + " resolved to null: " + aArgs[pArgumentIndex]);
            return false;
        }
        *pIndexListOut = reinterpret_cast<std::size_t *>(aBuffer);
        return true;
    };

    std::uint8_t *aInputLaneA = nullptr;
    std::uint8_t *aInputLaneB = nullptr;
    std::uint8_t *aOutputLaneA = nullptr;
    std::uint8_t *aOutputLaneB = nullptr;
    std::uint8_t *aShuffleEntropyLaneA = nullptr;
    std::uint8_t *aShuffleEntropyLaneB = nullptr;
    std::uint8_t *aOperationSourceLaneA = nullptr;
    std::uint8_t *aOperationSourceLaneB = nullptr;
    std::size_t *aIndexList256A = nullptr;
    std::size_t *aIndexList256B = nullptr;
    std::size_t *aIndexList256C = nullptr;
    std::size_t *aIndexList256D = nullptr;

    if (!ResolveBufferArg(0U, "input lane A", &aInputLaneA) ||
        !ResolveBufferArg(1U, "input lane B", &aInputLaneB) ||
        !ResolveBufferArg(2U, "output lane A", &aOutputLaneA) ||
        !ResolveBufferArg(3U, "output lane B", &aOutputLaneB) ||
        !ResolveBufferArg(4U, "shuffle entropy lane A", &aShuffleEntropyLaneA) ||
        !ResolveBufferArg(5U, "shuffle entropy lane B", &aShuffleEntropyLaneB) ||
        !ResolveBufferArg(6U, "operation source lane A", &aOperationSourceLaneA) ||
        !ResolveBufferArg(7U, "operation source lane B", &aOperationSourceLaneB) ||
        !ResolveIndexListArg(8U, "index list 256 A", &aIndexList256A) ||
        !ResolveIndexListArg(9U, "index list 256 B", &aIndexList256B) ||
        !ResolveIndexListArg(10U, "index list 256 C", &aIndexList256C) ||
        !ResolveIndexListArg(11U, "index list 256 D", &aIndexList256D)) {
        return false;
    }

    if (TrimRuntimeLine(aArgs[12U]) != "&mMatrix") {
        SetError(pError, "Diffuse matrix argument was invalid: " + aArgs[12U]);
        return false;
    }

    if (!aUseDomainWords) {
        TwistDiffuse::Diffuse(aInputLaneA,
                              aInputLaneB,
                              aOutputLaneA,
                              aOutputLaneB,
                              aShuffleEntropyLaneA,
                              aShuffleEntropyLaneB,
                              aOperationSourceLaneA,
                              aOperationSourceLaneB,
                              aIndexList256A,
                              aIndexList256B,
                              aIndexList256C,
                              aIndexList256D,
                              &(pExpander->mMatrix));
        return true;
    }

    GRuntimeScalar aMatrixSelectA = 0ULL;
    GRuntimeScalar aMatrixSelectB = 0ULL;
    int aMatrixUnrollA = 0;
    int aMatrixUnrollB = 0;
    int aMatrixArgA = 0;
    int aMatrixArgB = 0;
    int aMatrixArgC = 0;
    int aMatrixArgD = 0;
    if (!ParseRuntimeScalarToken(aArgs[13U], pVariables, &aMatrixSelectA) ||
        !ParseRuntimeScalarToken(aArgs[14U], pVariables, &aMatrixSelectB) ||
        !ParseRuntimeIntToken(aArgs[15U], pVariables, &aMatrixUnrollA) ||
        !ParseRuntimeIntToken(aArgs[16U], pVariables, &aMatrixUnrollB) ||
        !ParseRuntimeIntToken(aArgs[17U], pVariables, &aMatrixArgA) ||
        !ParseRuntimeIntToken(aArgs[18U], pVariables, &aMatrixArgB) ||
        !ParseRuntimeIntToken(aArgs[19U], pVariables, &aMatrixArgC) ||
        !ParseRuntimeIntToken(aArgs[20U], pVariables, &aMatrixArgD)) {
        SetError(pError, "Diffuse domain word argument was invalid.");
        return false;
    }

    TwistDiffuse::DiffuseWithDomainWords(aInputLaneA,
                                         aInputLaneB,
                                         aOutputLaneA,
                                         aOutputLaneB,
                                         aShuffleEntropyLaneA,
                                         aShuffleEntropyLaneB,
                                         aOperationSourceLaneA,
                                         aOperationSourceLaneB,
                                         aIndexList256A,
                                         aIndexList256B,
                                         aIndexList256C,
                                         aIndexList256D,
                                         &(pExpander->mMatrix),
                                         static_cast<std::uint64_t>(aMatrixSelectA),
                                         static_cast<std::uint64_t>(aMatrixSelectB),
                                         static_cast<std::uint8_t>(aMatrixUnrollA),
                                         static_cast<std::uint8_t>(aMatrixUnrollB),
                                         static_cast<std::uint8_t>(aMatrixArgA),
                                         static_cast<std::uint8_t>(aMatrixArgB),
                                         static_cast<std::uint8_t>(aMatrixArgC),
                                         static_cast<std::uint8_t>(aMatrixArgD));
    return true;
}

bool ExecuteRuntimeRawShiftBoxLine(const std::string &pRawLine,
                                   TwistWorkSpace *pWorkSpace,
                                   bool *pExecuted,
                                   std::string *pError) {
    if (pExecuted != nullptr) {
        *pExecuted = false;
    }
    if (pWorkSpace == nullptr) {
        return true;
    }

    std::string aLine = pRawLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimRuntimeLine(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }

    const std::string aPrefix = "TwistShiftBox::";
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        return true;
    }
    if (pExecuted != nullptr) {
        *pExecuted = true;
    }

    const std::size_t aOpen = aLine.find('(', aPrefix.size());
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        SetError(pError, "ShiftBox call was malformed.");
        return false;
    }

    const std::string aMethod = aLine.substr(aPrefix.size(), aOpen - aPrefix.size());
    std::vector<std::string> aArgs;
    if (!SplitRuntimeCallArguments(aLine.substr(aOpen + 1U, aClose - aOpen - 1U), &aArgs) ||
        (aArgs.size() != 1U) ||
        (TrimRuntimeLine(aArgs[0]) != "pWorkSpace")) {
        SetError(pError, "ShiftBox call expected pWorkSpace.");
        return false;
    }

    if (aMethod == "ShiftKeyBoxA") {
        TwistShiftBox::ShiftKeyBoxA(pWorkSpace);
    } else if (aMethod == "ShiftKeyBoxB") {
        TwistShiftBox::ShiftKeyBoxB(pWorkSpace);
    } else {
        SetError(pError, "ShiftBox call method was unsupported: " + aMethod);
        return false;
    }

    return true;
}

bool ExecuteRuntimeRawSnowLine(const std::string &pRawLine,
                               TwistWorkSpace *pWorkSpace,
                               TwistExpander *pExpander,
                               bool *pExecuted,
                               std::string *pError) {
    if (pExecuted != nullptr) {
        *pExecuted = false;
    }
    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        return true;
    }

    std::string aLine = pRawLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimRuntimeLine(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }

    const std::string aPrefix = "TwistSnow::";
    if (aLine.rfind(aPrefix, 0U) != 0U) {
        return true;
    }
    if (pExecuted != nullptr) {
        *pExecuted = true;
    }

    const std::size_t aOpen = aLine.find('(', aPrefix.size());
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        SetError(pError, "Snow call was malformed.");
        return false;
    }

    const std::string aMethod = aLine.substr(aPrefix.size(), aOpen - aPrefix.size());
    std::vector<std::string> aArgs;
    if (!SplitRuntimeCallArguments(aLine.substr(aOpen + 1U, aClose - aOpen - 1U), &aArgs) ||
        (aArgs.size() != 2U)) {
        SetError(pError, "Snow counter call expected 2 arguments.");
        return false;
    }

    auto ResolveBufferArg = [&](const std::string &pArg, std::uint8_t **pBufferOut) -> bool {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveRuntimeAliasSlot(pArg, &aSlot)) {
            SetError(pError, "Snow buffer argument was invalid: " + pArg);
            return false;
        }
        *pBufferOut = ResolveRuntimeBufferSlot(pWorkSpace, pExpander, aSlot);
        if (*pBufferOut == nullptr) {
            SetError(pError, "Snow buffer argument resolved to null: " + pArg);
            return false;
        }
        return true;
    };

    std::uint8_t *aSource = nullptr;
    std::uint8_t *aDest = nullptr;
    if (!ResolveBufferArg(aArgs[0], &aSource) ||
        !ResolveBufferArg(aArgs[1], &aDest)) {
        return false;
    }

    if (aMethod == "AES256Counter") {
        TwistSnow::AES256Counter(aSource, aDest);
    } else if (aMethod == "ChaCha20Counter") {
        TwistSnow::ChaCha20Counter(aSource, aDest);
    } else if (aMethod == "Sha256Counter") {
        TwistSnow::Sha256Counter(aSource, aDest);
    } else if (aMethod == "Aria256Counter") {
        TwistSnow::Aria256Counter(aSource, aDest);
    } else {
        SetError(pError, "Snow call method was unsupported: " + aMethod);
        return false;
    }

    return true;
}

bool ParseRuntimeSwitchLine(const std::string &pRawLine,
                            const std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                            int *pSelectedCase,
                            int *pCaseCount) {
    if ((pVariables == nullptr) || (pSelectedCase == nullptr) || (pCaseCount == nullptr)) {
        return false;
    }

    std::string aLine = TrimRuntimeLine(pRawLine);
    if (aLine.rfind("switch (", 0U) != 0U) {
        return false;
    }

    const std::size_t aOpen = aLine.find('(');
    const std::size_t aClose = aLine.rfind(')');
    if ((aOpen == std::string::npos) || (aClose == std::string::npos) || (aClose < aOpen)) {
        return false;
    }

    const std::string aExpr = TrimRuntimeLine(aLine.substr(aOpen + 1U, aClose - aOpen - 1U));
    const std::size_t aPercent = aExpr.find('%');
    if (aPercent == std::string::npos) {
        return false;
    }

    int aSelect = 0;
    int aModulo = 0;
    if (!ParseRuntimeIntToken(aExpr.substr(0U, aPercent), pVariables, &aSelect) ||
        !ParseRuntimeIntToken(aExpr.substr(aPercent + 1U), pVariables, &aModulo) ||
        (aModulo <= 0)) {
        return false;
    }

    *pSelectedCase = aSelect % aModulo;
    if (*pSelectedCase < 0) {
        *pSelectedCase += aModulo;
    }
    *pCaseCount = aModulo;
    return true;
}

bool ParseRuntimeCaseLine(const std::string &pRawLine,
                          int *pCaseValue) {
    if (pCaseValue == nullptr) {
        return false;
    }

    std::string aLine = TrimRuntimeLine(pRawLine);
    if (aLine.rfind("case ", 0U) != 0U) {
        return false;
    }

    const std::size_t aStart = std::string("case ").size();
    const std::size_t aColon = aLine.find(':', aStart);
    if (aColon == std::string::npos) {
        return false;
    }

    std::unordered_map<std::string, GRuntimeScalar> aEmptyVariables;
    return ParseRuntimeIntToken(aLine.substr(aStart, aColon - aStart),
                                &aEmptyVariables,
                                pCaseValue);
}

bool IsRuntimeBreakLine(const std::string &pRawLine) {
    std::string aLine = TrimRuntimeLine(pRawLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }
    return aLine == "break";
}

std::string StripRuntimeParens(std::string pText) {
    pText = TrimRuntimeLine(pText);
    bool aChanged = true;
    while (aChanged && (pText.size() >= 2U) && (pText.front() == '(') && (pText.back() == ')')) {
        aChanged = false;
        int aDepth = 0;
        bool aWrapsWholeText = true;
        for (std::size_t i = 0U; i < pText.size(); ++i) {
            if (pText[i] == '(') {
                aDepth += 1;
            } else if (pText[i] == ')') {
                aDepth -= 1;
                if ((aDepth == 0) && ((i + 1U) < pText.size())) {
                    aWrapsWholeText = false;
                    break;
                }
            }
            if (aDepth < 0) {
                aWrapsWholeText = false;
                break;
            }
        }
        if (aWrapsWholeText && (aDepth == 0)) {
            pText = TrimRuntimeLine(pText.substr(1U, pText.size() - 2U));
            aChanged = true;
        }
    }
    return pText;
}

bool ParseRuntimeIfByteMaskGreaterLine(const std::string &pRawLine,
                                       TwistWorkSpace *pWorkSpace,
                                       TwistExpander *pExpander,
                                       const std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                       bool *pConditionOut) {
    if ((pWorkSpace == nullptr) || (pExpander == nullptr) || (pVariables == nullptr) || (pConditionOut == nullptr)) {
        return false;
    }

    std::string aLine = TrimRuntimeLine(pRawLine);
    if (aLine.rfind("if", 0U) != 0U) {
        return false;
    }
    if (!aLine.empty() && (aLine.back() == '{')) {
        aLine.pop_back();
        aLine = TrimRuntimeLine(aLine);
    }
    if (aLine.rfind("if", 0U) != 0U) {
        return false;
    }

    std::size_t aOpen = std::string("if").size();
    while ((aOpen < aLine.size()) && (std::isspace(static_cast<unsigned char>(aLine[aOpen])) != 0)) {
        ++aOpen;
    }
    if ((aOpen >= aLine.size()) || (aLine[aOpen] != '(')) {
        return false;
    }
    const std::size_t aClose = aLine.rfind(')');
    if ((aClose == std::string::npos) || (aClose <= aOpen)) {
        return false;
    }

    const std::string aExpr = StripRuntimeParens(aLine.substr(aOpen + 1U, aClose - aOpen - 1U));
    const std::size_t aGreater = aExpr.find('>');
    if (aGreater == std::string::npos) {
        return false;
    }

    std::string aLeft = StripRuntimeParens(aExpr.substr(0U, aGreater));
    const std::string aRight = aExpr.substr(aGreater + 1U);
    int aThreshold = 0;
    if (!ParseRuntimeIntToken(aRight, pVariables, &aThreshold)) {
        return false;
    }

    const std::size_t aAnd = aLeft.find('&');
    if (aAnd == std::string::npos) {
        return false;
    }
    std::string aRead = StripRuntimeParens(aLeft.substr(0U, aAnd));
    GRuntimeScalar aXorValue = 0ULL;
    const std::size_t aXor = aRead.find('^');
    if (aXor != std::string::npos) {
        const std::string aXorToken = aRead.substr(aXor + 1U);
        aRead = StripRuntimeParens(aRead.substr(0U, aXor));
        if (!ParseRuntimeScalarToken(aXorToken, pVariables, &aXorValue)) {
            return false;
        }
    }
    const std::string aMaskToken = aLeft.substr(aAnd + 1U);
    int aMask = 0;
    if (!ParseRuntimeIntToken(aMaskToken, pVariables, &aMask)) {
        return false;
    }

    const std::size_t aBracketOpen = aRead.find('[');
    const std::size_t aBracketClose = aRead.rfind(']');
    if ((aBracketOpen == std::string::npos) ||
        (aBracketClose == std::string::npos) ||
        (aBracketClose <= aBracketOpen)) {
        return false;
    }

    const std::string aAlias = aRead.substr(0U, aBracketOpen);
    const std::string aIndexToken = aRead.substr(aBracketOpen + 1U,
                                                 aBracketClose - aBracketOpen - 1U);
    TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
    if (!ResolveRuntimeAliasSlot(aAlias, &aSlot)) {
        return false;
    }
    std::uint8_t *aBuffer = ResolveRuntimeBufferSlot(pWorkSpace, pExpander, aSlot);
    if (aBuffer == nullptr) {
        return false;
    }
    std::size_t aIndex = 0U;
    if (!ParseRuntimeSizeToken(aIndexToken, pVariables, &aIndex)) {
        return false;
    }

    const GRuntimeScalar aSelectedValue =
        static_cast<GRuntimeScalar>(aBuffer[aIndex & static_cast<std::size_t>(S_BLOCK1)]) ^ aXorValue;
    const int aMaskedValue = static_cast<int>(aSelectedValue & static_cast<GRuntimeScalar>(aMask));
    *pConditionOut = aMaskedValue > aThreshold;
    return true;
}

bool IsRuntimeElseLine(const std::string &pRawLine) {
    std::string aLine = TrimRuntimeLine(pRawLine);
    return (aLine == "} else {") || (aLine == "else {");
}

bool IsRuntimeCloseBraceLine(const std::string &pRawLine) {
    return TrimRuntimeLine(pRawLine) == "}";
}

void CollectVariablesFromExpr(const GExpr &pExpr,
                              std::vector<std::string> *pNames) {
    if (pExpr.mType == GExprType::kSymbol && pExpr.mSymbol.IsVar()) {
        AppendUniqueVariableName(pNames, pExpr.mSymbol.mName);
        return;
    }
    if (pExpr.mType == GExprType::kRead) {
        if (pExpr.mSymbol.IsVar()) {
            AppendUniqueVariableName(pNames, pExpr.mSymbol.mName);
        }
        if (pExpr.mIndex != nullptr) {
            CollectVariablesFromExpr(*pExpr.mIndex, pNames);
        }
        return;
    }
    if (pExpr.mA != nullptr) {
        CollectVariablesFromExpr(*pExpr.mA, pNames);
    }
    if (pExpr.mB != nullptr) {
        CollectVariablesFromExpr(*pExpr.mB, pNames);
    }
}

void CollectSlotsFromExpr(const GExpr &pExpr,
                          std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pExpr.mType == GExprType::kSymbol && pExpr.mSymbol.IsBuf()) {
        AppendUnique(pSlots, pExpr.mSymbol.mSlot);
        return;
    }
    if (pExpr.mType == GExprType::kRead) {
        if (pExpr.mSymbol.IsBuf()) {
            AppendUnique(pSlots, pExpr.mSymbol.mSlot);
        }
        if (pExpr.mIndex != nullptr) {
            CollectSlotsFromExpr(*pExpr.mIndex, pSlots);
        }
        return;
    }
    if (pExpr.mA != nullptr) {
        CollectSlotsFromExpr(*pExpr.mA, pSlots);
    }
    if (pExpr.mB != nullptr) {
        CollectSlotsFromExpr(*pExpr.mB, pSlots);
    }
}

int CountExprReads(const GExpr &pExpr,
                             const TwistWorkSpaceSlot pSlot) {
    int aCount = 0U;
    if ((pExpr.mType == GExprType::kSymbol || pExpr.mType == GExprType::kRead) &&
        pExpr.mSymbol.IsBuf() &&
        pExpr.mSymbol.mSlot == pSlot) {
        ++aCount;
    }
    if (pExpr.mIndex != nullptr) {
        aCount += CountExprReads(*pExpr.mIndex, pSlot);
    }
    if (pExpr.mA != nullptr) {
        aCount += CountExprReads(*pExpr.mA, pSlot);
    }
    if (pExpr.mB != nullptr) {
        aCount += CountExprReads(*pExpr.mB, pSlot);
    }
    return aCount;
}

int CountTargetWrites(const GTarget &pTarget,
                                const TwistWorkSpaceSlot pSlot) {
    return (pTarget.IsBuf() && pTarget.mSymbol.mSlot == pSlot) ? 1U : 0U;
}

std::string ScalarOperatorText(const GExprType pType) {
    switch (pType) {
        case GExprType::kAdd: return "+";
        case GExprType::kSub: return "-";
        case GExprType::kMul: return "*";
        case GExprType::kXor: return "^";
        case GExprType::kAnd: return "&";
        case GExprType::kOr: return "|";
        default: return "";
    }
}

std::string AssignOperatorText(const GAssignType pType) {
    switch (pType) {
        case GAssignType::kSet: return "=";
        case GAssignType::kAddAssign: return "+=";
        case GAssignType::kXorAssign: return "^=";
        case GAssignType::kOrAssign: return "|=";
        
        default: return "?=";
    }
}

bool StartsWithText(const std::string &pText,
                    const std::string &pPrefix) {
    if (pPrefix.size() > pText.size()) {
        return false;
    }
    return pText.compare(0U, pPrefix.size(), pPrefix) == 0;
}

bool IsKeyScalarName(const std::string &pName) {
    return pName.find("Key") != std::string::npos;
}

std::string ScalarCppTypeForName(const std::string &pName) {
    if (StartsWithText(pName, "aOracle")) {
        return "std::size_t";
    }
    if (pName == "aSquash") {
        return "std::uint32_t";
    }
    if (IsKeyScalarName(pName)) {
        return "std::size_t";
    }
    return "std::uint64_t";
}

int LetterIndexFromSuffix(const std::string &pName,
                          const std::string &pPrefix) {
    if (pName.size() != (pPrefix.size() + 1U)) {
        return -1;
    }
    if (pName.compare(0U, pPrefix.size(), pPrefix) != 0) {
        return -1;
    }
    const char aSuffix = pName[pPrefix.size()];
    if ((aSuffix < 'A') || (aSuffix > 'K')) {
        return -1;
    }
    return static_cast<int>(aSuffix - 'A');
}

int CoreScalarOrder(const std::string &pName) {
    if (pName == "aPrevious") { return 0; }
    if (pName == "aIngress") { return 1; }
    if (pName == "aCarry") { return 2; }
    if (pName == "aCross") { return 3; }
    if (pName == "aScatter") { return 4; }
    return -1;
}

int ScalarDeclarationGroup(const std::string &pName) {
    if (CoreScalarOrder(pName) >= 0) {
        return 0;
    }
    if (LetterIndexFromSuffix(pName, "aOrbiter") >= 0) {
        return 1;
    }
    if (LetterIndexFromSuffix(pName, "aWanderer") >= 0) {
        return 2;
    }
    return 3;
}

int ScalarDeclarationOrder(const std::string &pName) {
    const int aCoreOrder = CoreScalarOrder(pName);
    if (aCoreOrder >= 0) {
        return aCoreOrder;
    }
    const int aOrbitOrder = LetterIndexFromSuffix(pName, "aOrbiter");
    if (aOrbitOrder >= 0) {
        return aOrbitOrder;
    }
    const int aWandererOrder = LetterIndexFromSuffix(pName, "aWanderer");
    if (aWandererOrder >= 0) {
        return aWandererOrder;
    }
    return 0;
}

bool IsFixedRandomArxStateScalarName(const std::string &pName) {
    return (pName == "aPrevious") ||
           (pName == "aIngress") ||
           (pName == "aCarry") ||
           (LetterIndexFromSuffix(pName, "aWanderer") >= 0);
}

std::string UInt64ScalarLiteral(const std::uint64_t pValue) {
    std::ostringstream aStream;
    aStream << "0x" << std::uppercase << std::hex << pValue << "ULL";
    return aStream.str();
}

std::string ScalarInitialValueForName(const std::string &pName) {
    if (IsFixedRandomArxStateScalarName(pName)) {
        return UInt64ScalarLiteral(Random::Get64High());
    }
    return "0";
}

void SortScalarDeclarationNames(std::vector<std::string> *pNames) {
    if (pNames == nullptr) {
        return;
    }
    std::stable_sort(pNames->begin(),
                     pNames->end(),
                     [](const std::string &pLHS, const std::string &pRHS) {
                         const int aGroupLHS = ScalarDeclarationGroup(pLHS);
                         const int aGroupRHS = ScalarDeclarationGroup(pRHS);
                         if (aGroupLHS != aGroupRHS) {
                             return aGroupLHS < aGroupRHS;
                         }
                         const int aOrderLHS = ScalarDeclarationOrder(pLHS);
                         const int aOrderRHS = ScalarDeclarationOrder(pRHS);
                         if (aOrderLHS != aOrderRHS) {
                             return aOrderLHS < aOrderRHS;
                         }
                         return false;
                     });
}

std::vector<std::string> ScalarDeclarationLines(const std::vector<std::string> &pNames,
                                                const int pIndentLevel) {
    std::vector<std::string> aLines;
    if (pNames.empty()) {
        return aLines;
    }

    constexpr std::size_t kDeclarationsPerLine = 4U;
    const std::string aIndent = Indent(pIndentLevel);
    std::size_t aIndex = 0U;
    int aPreviousGroup = -1;
    while (aIndex < pNames.size()) {
        const int aGroup = ScalarDeclarationGroup(pNames[aIndex]);
        const std::string aType = ScalarCppTypeForName(pNames[aIndex]);
        if ((aPreviousGroup >= 0) && (aGroup != aPreviousGroup)) {
            aLines.push_back("");
        }

        std::ostringstream aLine;
        aLine << aIndent;
        std::size_t aLineCount = 0U;
        while ((aIndex < pNames.size()) &&
               (aLineCount < kDeclarationsPerLine) &&
               (ScalarDeclarationGroup(pNames[aIndex]) == aGroup) &&
               (ScalarCppTypeForName(pNames[aIndex]) == aType)) {
            if (aLineCount > 0U) {
                aLine << ' ';
            }
            aLine << ScalarCppTypeForName(pNames[aIndex]) << ' ' << pNames[aIndex]
                  << " = " << ScalarInitialValueForName(pNames[aIndex]) << ";";
            ++aLineCount;
            ++aIndex;
        }
        aLines.push_back(aLine.str());
        aPreviousGroup = aGroup;
    }

    return aLines;
}

std::vector<std::string> WorkspaceDomainWordAliasOrder() {
    std::vector<std::string> aResult;
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
            const std::string aName = WorkspaceDomainWordAliasName(aDomain, aConstant);
            if (!aName.empty()) {
                aResult.push_back(aName);
            }
        }
    }
    return aResult;
}

std::vector<std::string> ExtractWorkspaceDomainWordNames(std::vector<std::string> *pScalarVariables) {
    std::vector<std::string> aResult;
    if (pScalarVariables == nullptr) {
        return aResult;
    }

    for (const std::string &aName : WorkspaceDomainWordAliasOrder()) {
        if (std::find(pScalarVariables->begin(), pScalarVariables->end(), aName) != pScalarVariables->end()) {
            aResult.push_back(aName);
        }
    }

    pScalarVariables->erase(
        std::remove_if(pScalarVariables->begin(),
                       pScalarVariables->end(),
                       [](const std::string &pName) {
                           return WorkspaceDomainWordAliasInfo(pName, nullptr, nullptr);
                       }),
        pScalarVariables->end());

    return aResult;
}

std::vector<std::string> WorkspaceDomainWordDeclarationLines(const std::vector<std::string> &pNames,
                                                             const int pIndentLevel) {
    std::vector<std::string> aLines;
    const std::string aIndent = Indent(pIndentLevel);
    for (const std::string &aName : pNames) {
        TwistDomain aDomain = TwistDomain::kInvalid;
        TwistConstants aConstant = TwistConstants::kInvalid;
        if (!WorkspaceDomainWordAliasInfo(aName, &aDomain, &aConstant)) {
            continue;
        }

        const std::string aAccess = WorkspaceDomainWordAccessText(aDomain, aConstant);
        if (aAccess.empty()) {
            continue;
        }
        aLines.push_back(aIndent + "const std::uint64_t &" + aName + " = " + aAccess + ";");
    }
    return aLines;
}

GRuntimeScalar NormalizeScalarValueForName(const std::string &pName,
                                           const GRuntimeScalar pValue) {
    if (StartsWithText(pName, "aOracle")) {
        return pValue;
    }
    if (pName == "aSquash") {
        return static_cast<GRuntimeScalar>(static_cast<std::uint32_t>(pValue));
    }
    if (IsKeyScalarName(pName)) {
        return static_cast<GRuntimeScalar>(static_cast<std::uint32_t>(pValue));
    }
    return pValue;
}

bool LoopUsesSizeT(const GLoop &pLoop) {
    return (pLoop.mLoopBegin >= 0) && (pLoop.mLoopStep > 0);
}

bool IsSaltSlot(const TwistWorkSpaceSlot pSlot) {
    return TwistWorkSpace::IsSalt(pSlot);
}

bool IsIndexListSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kIndexList256A:
        case TwistWorkSpaceSlot::kIndexList256B:
        case TwistWorkSpaceSlot::kIndexList256C:
        case TwistWorkSpaceSlot::kIndexList256D:
            return true;
        default:
            return false;
    }
}

TwistDomainConstants *WorkspaceConstantsForDomain(TwistWorkSpace *pWorkSpace,
                                                  const TwistDomain pDomain) {
    if (pWorkSpace == nullptr) {
        return nullptr;
    }

    switch (pDomain) {
        case TwistDomain::kPhaseB: return &pWorkSpace->mDomainBundle.mPhaseBConstants;
        case TwistDomain::kPhaseC: return &pWorkSpace->mDomainBundle.mPhaseCConstants;
        case TwistDomain::kPhaseD: return &pWorkSpace->mDomainBundle.mPhaseDConstants;
        case TwistDomain::kPhaseE: return &pWorkSpace->mDomainBundle.mPhaseEConstants;
        case TwistDomain::kPhaseF: return &pWorkSpace->mDomainBundle.mPhaseFConstants;
        case TwistDomain::kPhaseG: return &pWorkSpace->mDomainBundle.mPhaseGConstants;
        case TwistDomain::kPhaseH: return &pWorkSpace->mDomainBundle.mPhaseHConstants;
        case TwistDomain::kInvalid:
        case TwistDomain::kPhaseA:
        default:
            return &pWorkSpace->mDomainBundle.mPhaseAConstants;
    }
}

bool WorkspaceConstantValue(const TwistDomainConstants *pConstants,
                            const TwistConstants pConstant,
                            GRuntimeScalar *pValue,
                            std::string *pError) {
    if ((pConstants == nullptr) || (pValue == nullptr)) {
        SetError(pError, "Workspace domain constant value input was null.");
        return false;
    }

    switch (pConstant) {
        case TwistConstants::kIngress:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mIngress);
            return true;
        case TwistConstants::kScatter:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mScatter);
            return true;
        case TwistConstants::kCross:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mCross);
            return true;
        case TwistConstants::kMatrixSelectA:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMatrixSelectA);
            return true;
        case TwistConstants::kMatrixSelectB:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMatrixSelectB);
            return true;
        case TwistConstants::kMatrixUnrollA:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMatrixUnrollA);
            return true;
        case TwistConstants::kMatrixUnrollB:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMatrixUnrollB);
            return true;
        case TwistConstants::kMatrixArgA:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMatrixArgA);
            return true;
        case TwistConstants::kMatrixArgB:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMatrixArgB);
            return true;
        case TwistConstants::kMatrixArgC:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMatrixArgC);
            return true;
        case TwistConstants::kMatrixArgD:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMatrixArgD);
            return true;
        case TwistConstants::kMaskMutateA:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMaskMutateA);
            return true;
        case TwistConstants::kMaskMutateB:
            *pValue = static_cast<GRuntimeScalar>(pConstants->mMaskMutateB);
            return true;
        default:
            SetError(pError, "Workspace domain word used an unsupported constant.");
            return false;
    }
}

bool LegacyDomainWordConstantInfo(const std::string &pName,
                                  TwistConstants *pConstantOut) {
    TwistConstants aConstant = TwistConstants::kInvalid;
    if (pName == "aDomainWordIngress") {
        aConstant = TwistConstants::kIngress;
    } else if (pName == "aDomainWordScatter") {
        aConstant = TwistConstants::kScatter;
    } else if (pName == "aDomainWordCross") {
        aConstant = TwistConstants::kCross;
    } else if (pName == "aDomainWordMatrixSelectA") {
        aConstant = TwistConstants::kMatrixSelectA;
    } else if (pName == "aDomainWordMatrixSelectB") {
        aConstant = TwistConstants::kMatrixSelectB;
    } else if (pName == "aDomainWordMatrixUnrollA") {
        aConstant = TwistConstants::kMatrixUnrollA;
    } else if (pName == "aDomainWordMatrixUnrollB") {
        aConstant = TwistConstants::kMatrixUnrollB;
    } else if (pName == "aDomainWordMatrixArgA") {
        aConstant = TwistConstants::kMatrixArgA;
    } else if (pName == "aDomainWordMatrixArgB") {
        aConstant = TwistConstants::kMatrixArgB;
    } else if (pName == "aDomainWordMatrixArgC") {
        aConstant = TwistConstants::kMatrixArgC;
    } else if (pName == "aDomainWordMatrixArgD") {
        aConstant = TwistConstants::kMatrixArgD;
    } else if (pName == "aDomainWordMaskMutateA") {
        aConstant = TwistConstants::kMaskMutateA;
    } else if (pName == "aDomainWordMaskMutateB") {
        aConstant = TwistConstants::kMaskMutateB;
    }

    if (aConstant == TwistConstants::kInvalid) {
        return false;
    }
    if (pConstantOut != nullptr) {
        *pConstantOut = aConstant;
    }
    return true;
}

bool IsWorkspaceResolvedDomainWordName(const std::string &pName) {
    return WorkspaceDomainWordAliasInfo(pName, nullptr, nullptr) ||
           LegacyDomainWordConstantInfo(pName, nullptr);
}

bool ResolveWorkspaceDomainWordValue(const std::string &pName,
                                     TwistWorkSpace *pWorkSpace,
                                     GRuntimeScalar *pValue,
                                     bool *pWasDomainWord,
                                     std::string *pError) {
    if (pWasDomainWord != nullptr) {
        *pWasDomainWord = false;
    }

    TwistDomain aDomain = TwistDomain::kInvalid;
    TwistConstants aConstant = TwistConstants::kInvalid;
    if (!WorkspaceDomainWordAliasInfo(pName, &aDomain, &aConstant)) {
        return true;
    }

    if (pWasDomainWord != nullptr) {
        *pWasDomainWord = true;
    }
    if (pValue == nullptr) {
        SetError(pError, "Workspace domain word output was null.");
        return false;
    }

    TwistDomainConstants *aConstants = WorkspaceConstantsForDomain(pWorkSpace, aDomain);
    if (aConstants == nullptr) {
        SetError(pError, "Workspace was null during domain word read.");
        return false;
    }

    return WorkspaceConstantValue(aConstants, aConstant, pValue, pError);
}

bool ResolveLegacyWorkspaceDomainWordValue(const std::string &pName,
                                           TwistWorkSpace *pWorkSpace,
                                           GRuntimeScalar *pValue,
                                           bool *pWasDomainWord,
                                           std::string *pError) {
    if (pWasDomainWord != nullptr) {
        *pWasDomainWord = false;
    }

    TwistConstants aConstant = TwistConstants::kInvalid;
    if (!LegacyDomainWordConstantInfo(pName, &aConstant)) {
        return true;
    }

    if (pWasDomainWord != nullptr) {
        *pWasDomainWord = true;
    }

    TwistDomainConstants *aConstants = WorkspaceConstantsForDomain(pWorkSpace, TwistDomain::kPhaseA);
    if (aConstants == nullptr) {
        SetError(pError, "Workspace was null during legacy domain word read.");
        return false;
    }
    return WorkspaceConstantValue(aConstants, aConstant, pValue, pError);
}

std::size_t RuntimeIndexForSlot(const TwistWorkSpaceSlot pSlot,
                                const GRuntimeScalar pIndexValue) {
    if (IsSaltSlot(pSlot)) {
        return static_cast<std::size_t>(pIndexValue & static_cast<GRuntimeScalar>(S_SALT1));
    }
    if (IsIndexListSlot(pSlot)) {
        return static_cast<std::size_t>(pIndexValue & static_cast<GRuntimeScalar>(S_SBOX1));
    }

    const int aElementCount = TwistWorkSpace::GetBufferLength(pSlot);
    if (aElementCount <= 0) {
        return static_cast<std::size_t>(pIndexValue);
    }
    if ((aElementCount & (aElementCount - 1)) == 0) {
        return static_cast<std::size_t>(pIndexValue & static_cast<GRuntimeScalar>(aElementCount - 1));
    }
    return static_cast<std::size_t>(pIndexValue % static_cast<GRuntimeScalar>(aElementCount));
}

unsigned int ReadWrapTrimMaskForType(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kSBox: return static_cast<unsigned int>(S_SBOX1);
        case GReadWrapType::kSalt: return static_cast<unsigned int>(S_SALT1);
        case GReadWrapType::kKeyA: return static_cast<unsigned int>(S_KEY - 1);
        case GReadWrapType::kKeyB: return static_cast<unsigned int>(S_KEY - 1);
        default: return 0U;
    }
}

int ReadWrapLimitForType(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kBlock: return S_BLOCK;
        case GReadWrapType::kSalt: return S_SALT;
        case GReadWrapType::kKeyA: return S_KEY;
        case GReadWrapType::kKeyB: return S_KEY;
        default: return 0;
    }
}

int ResolveLengthText(const std::string &pText) {
    if (pText == "S_BLOCK") { return S_BLOCK; }
    if (pText == "S_SALT") { return S_SALT; }
    if (pText == "W_KEY") { return W_KEY; }
    if (pText == "S_KEY") { return S_KEY; }

    if (pText.empty()) {
        return 0;
    }

    const char *aStart = pText.c_str();
    char *aEnd = NULL;
    const long aValue = std::strtol(aStart, &aEnd, 10);
    if ((aEnd != NULL) && (*aEnd == '\0')) {
        return static_cast<int>(aValue);
    }
    return 0;
}

JsonValue SymbolToJsonValue(const GSymbol &pSymbol) {
    JsonValue::Object aObject;
    aObject["name"] = JsonValue::String(pSymbol.mName);
    switch (pSymbol.mType) {
        case GSymbolType::kVar:
            aObject["kind"] = JsonValue::String("var");
            break;
        case GSymbolType::kBuf:
            aObject["kind"] = JsonValue::String("buf");
            aObject["slot"] = JsonValue::String(SlotToken(pSymbol.mSlot));
            break;
        default:
            aObject["kind"] = JsonValue::String("invalid");
            break;
    }
    return JsonValue::ObjectValue(std::move(aObject));
}

bool SymbolFromJsonValue(const JsonValue &pValue,
                         GSymbol *pSymbol,
                         std::string *pError) {
    if (pSymbol == NULL) {
        SetError(pError, "Symbol output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pError, "Symbol JSON was not an object.");
        return false;
    }

    const JsonValue *aKind = pValue.find("kind");
    const JsonValue *aName = pValue.find("name");
    if ((aKind == NULL) || !aKind->is_string() || (aName == NULL) || !aName->is_string()) {
        SetError(pError, "Symbol JSON was incomplete.");
        return false;
    }

    const std::string aKindText = aKind->as_string();
    if (aKindText == "var") {
        const std::string aNameText = aName->as_string();
        if ((aNameText == "pInput") || (aNameText == "pSource")) {
            *pSymbol = GSymbol::Buf(TwistWorkSpaceSlot::kParamSource);
            return true;
        }
        if ((aNameText == "pOutput") || (aNameText == "pDestination")) {
            *pSymbol = GSymbol::Buf(TwistWorkSpaceSlot::kParamDestination);
            return true;
        }
        *pSymbol = GSymbol::Var(aNameText);
        return true;
    }
    if (aKindText == "buf") {
        const JsonValue *aSlot = pValue.find("slot");
        if ((aSlot == NULL) || !aSlot->is_string()) {
            SetError(pError, "Buffer symbol was missing a slot.");
            return false;
        }
        TwistWorkSpaceSlot aParsedSlot = TwistWorkSpaceSlot::kInvalid;
        if (!SlotFromToken(aSlot->as_string(), &aParsedSlot)) {
            SetError(pError, "Buffer symbol slot token was unknown.");
            return false;
        }
        *pSymbol = GSymbol::Buf(aParsedSlot);
        if (!aName->as_string().empty()) {
            pSymbol->mName = aName->as_string();
        }
        return true;
    }

    pSymbol->Invalidate();
    return true;
}

JsonValue ExprToJsonValue(const GExpr &pExpr) {
    JsonValue::Object aObject;
    aObject["type"] = JsonValue::String(ExprTypeToken(pExpr.mType));

    if (pExpr.mType == GExprType::kSymbol || pExpr.mType == GExprType::kRead) {
        aObject["symbol"] = SymbolToJsonValue(pExpr.mSymbol);
    }
    if (pExpr.mType == GExprType::kConst) {
        aObject["value"] = JsonValue::String(std::to_string(static_cast<unsigned long long>(pExpr.mConstVal)));
        if (pExpr.mConstPreferHex) {
            aObject["prefer_hex"] = JsonValue::Bool(true);
        }
    }
    if (pExpr.mIndex != nullptr) {
        aObject["index"] = ExprToJsonValue(*pExpr.mIndex);
    }
    if (pExpr.mA != nullptr) {
        aObject["a"] = ExprToJsonValue(*pExpr.mA);
    }
    if (pExpr.mB != nullptr) {
        aObject["b"] = ExprToJsonValue(*pExpr.mB);
    }
    if ((pExpr.mType == GExprType::kRead) && (pExpr.mReadWrapType != GReadWrapType::kNone)) {
        aObject["read_wrap_type"] = JsonValue::String(ReadWrapTypeToken(pExpr.mReadWrapType));
        aObject["read_wrap_index_symbol"] = SymbolToJsonValue(pExpr.mReadWrapIndexSymbol);
        aObject["read_wrap_oracle_symbol"] = SymbolToJsonValue(pExpr.mReadWrapOracleSymbol);
    }
    return JsonValue::ObjectValue(std::move(aObject));
}

bool ExprFromJsonValue(const JsonValue &pValue,
                       GExpr *pExpr,
                       std::string *pError) {
    if (pExpr == NULL) {
        SetError(pError, "Expression output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pError, "Expression JSON was not an object.");
        return false;
    }

    const JsonValue *aType = pValue.find("type");
    if ((aType == NULL) || !aType->is_string()) {
        SetError(pError, "Expression JSON was missing a type.");
        return false;
    }

    GExprType aTypeValue = GExprType::kInv;
    if (!ExprTypeFromToken(aType->as_string(), &aTypeValue)) {
        std::printf("warn: ExprFromJsonValue unknown expression type token '%s'; defaulting to invalid expression.\n",
                    aType->as_string().c_str());
        aTypeValue = GExprType::kInv;
    }

    GExpr aExpr;
    switch (aTypeValue) {
        case GExprType::kSymbol: {
            const JsonValue *aSymbol = pValue.find("symbol");
            if (aSymbol == NULL) {
                SetError(pError, "Symbol expression was missing a symbol.");
                return false;
            }
            GSymbol aParsedSymbol;
            if (!SymbolFromJsonValue(*aSymbol, &aParsedSymbol, pError)) {
                return false;
            }
            aExpr = GExpr::Symbol(aParsedSymbol);
            break;
        }
        case GExprType::kConst: {
            const JsonValue *aValue = pValue.find("value");
            std::uint64_t aNumber = 0U;
            if ((aValue == NULL) || !ParseUInt64(*aValue, &aNumber)) {
                SetError(pError, "Constant expression value was invalid.");
                return false;
            }
            bool aPreferHex = false;
            if (const JsonValue *aPreferHexValue = pValue.find("prefer_hex");
                aPreferHexValue != NULL) {
                if (!aPreferHexValue->is_bool()) {
                    SetError(pError, "Constant expression prefer_hex value was invalid.");
                    return false;
                }
                aPreferHex = aPreferHexValue->as_bool();
            }
            aExpr = aPreferHex ? GExpr::Const64Hex(aNumber)
                               : GExpr::Const64(aNumber);
            break;
        }
        case GExprType::kRead: {
            const JsonValue *aSymbol = pValue.find("symbol");
            const JsonValue *aIndex = pValue.find("index");
            if ((aSymbol == NULL) || (aIndex == NULL)) {
                SetError(pError, "Read expression was incomplete.");
                return false;
            }
            GSymbol aParsedSymbol;
            GExpr aIndexExpr;
            if (!SymbolFromJsonValue(*aSymbol, &aParsedSymbol, pError) ||
                !ExprFromJsonValue(*aIndex, &aIndexExpr, pError)) {
                return false;
            }
            aExpr = GExpr::Read(aParsedSymbol, aIndexExpr);

            if (const JsonValue *aWrapType = pValue.find("read_wrap_type");
                (aWrapType != NULL) && aWrapType->is_string()) {
                GReadWrapType aWrapTypeValue = GReadWrapType::kNone;
                if (!ReadWrapTypeFromToken(aWrapType->as_string(), &aWrapTypeValue)) {
                    SetError(pError, "Read wrap type token was unknown.");
                    return false;
                }

                if (aWrapTypeValue != GReadWrapType::kNone) {
                    const JsonValue *aWrapIndexSymbol = pValue.find("read_wrap_index_symbol");
                    const JsonValue *aWrapOracleSymbol = pValue.find("read_wrap_oracle_symbol");
                    if ((aWrapIndexSymbol == NULL) || (aWrapOracleSymbol == NULL)) {
                        SetError(pError, "Read wrap metadata was incomplete.");
                        return false;
                    }

                    GSymbol aWrapIndexParsed;
                    GSymbol aWrapOracleParsed;
                    if (!SymbolFromJsonValue(*aWrapIndexSymbol, &aWrapIndexParsed, pError) ||
                        !SymbolFromJsonValue(*aWrapOracleSymbol, &aWrapOracleParsed, pError)) {
                        SetError(pError, "Read wrap metadata was invalid.");
                        return false;
                    }

                    aExpr.mReadWrapType = aWrapTypeValue;
                    aExpr.mReadWrapIndexSymbol = aWrapIndexParsed;
                    aExpr.mReadWrapOracleSymbol = aWrapOracleParsed;
                }
            }
            break;
        }
        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kOr:
        case GExprType::kRotL8:
        case GExprType::kRotL32:
        case GExprType::kRotL64:
        case GExprType::kShiftL:
        case GExprType::kShiftR: {
            const JsonValue *aA = pValue.find("a");
            const JsonValue *aB = pValue.find("b");
            if ((aA == NULL) || (aB == NULL)) {
                SetError(pError, "Binary expression was incomplete.");
                return false;
            }
            GExpr aLeft;
            GExpr aRight;
            if (!ExprFromJsonValue(*aA, &aLeft, pError) ||
                !ExprFromJsonValue(*aB, &aRight, pError)) {
                return false;
            }
            switch (aTypeValue) {
                case GExprType::kAdd: aExpr = GExpr::Add(aLeft, aRight); break;
                case GExprType::kSub: aExpr = GExpr::Sub(aLeft, aRight); break;
                case GExprType::kMul: aExpr = GExpr::Mul(aLeft, aRight); break;
                case GExprType::kXor: aExpr = GExpr::Xor(aLeft, aRight); break;
                case GExprType::kAnd: aExpr = GExpr::And(aLeft, aRight); break;
                case GExprType::kOr: aExpr = GExpr::Or(aLeft, aRight); break;
                case GExprType::kRotL8: aExpr = GExpr::RotL8(aLeft, aRight); break;
                case GExprType::kRotL32: aExpr = GExpr::RotL32(aLeft, aRight); break;
                case GExprType::kRotL64: aExpr = GExpr::RotL64(aLeft, aRight); break;
                case GExprType::kShiftL: aExpr = GExpr::ShiftL(aLeft, aRight); break;
                case GExprType::kShiftR: aExpr = GExpr::ShiftR(aLeft, aRight); break;
                default: break;
            }
            break;
        }
        case GExprType::kDiffuse64A:
        case GExprType::kDiffuse64B:
        case GExprType::kDiffuse64C:
        case GExprType::kDiffuse32A:
        case GExprType::kDiffuse32B:
        case GExprType::kDiffuse32C:
        case GExprType::kCast32: {
            const JsonValue *aA = pValue.find("a");
            if (aA == NULL) {
                SetError(pError, "Unary expression was incomplete.");
                return false;
            }

            GExpr aInner;
            if (!ExprFromJsonValue(*aA, &aInner, pError)) {
                return false;
            }

            switch (aTypeValue) {
                case GExprType::kDiffuse64A: aExpr = GExpr::Diffuse64A(aInner); break;
                case GExprType::kDiffuse64B: aExpr = GExpr::Diffuse64B(aInner); break;
                case GExprType::kDiffuse64C: aExpr = GExpr::Diffuse64C(aInner); break;
                case GExprType::kDiffuse32A: aExpr = GExpr::Diffuse32A(aInner); break;
                case GExprType::kDiffuse32B: aExpr = GExpr::Diffuse32B(aInner); break;
                case GExprType::kDiffuse32C: aExpr = GExpr::Diffuse32C(aInner); break;
                case GExprType::kCast32: aExpr = GExpr::Cast32(aInner); break;
                default: break;
            }
            break;
        }
        case GExprType::kInv: {
            aExpr.Invalidate();
            break;
        }
        default:
            aExpr.Invalidate();
            break;
    }

    *pExpr = aExpr;
    return true;
}

JsonValue TargetToJsonValue(const GTarget &pTarget) {
    JsonValue::Object aObject;
    aObject["symbol"] = SymbolToJsonValue(pTarget.mSymbol);
    if (pTarget.mIndex != nullptr) {
        aObject["index"] = ExprToJsonValue(*pTarget.mIndex);
    } else {
        aObject["index"] = JsonValue::Null();
    }
    return JsonValue::ObjectValue(std::move(aObject));
}

bool TargetFromJsonValue(const JsonValue &pValue,
                         GTarget *pTarget,
                         std::string *pError) {
    if (pTarget == NULL) {
        SetError(pError, "Target output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pError, "Target JSON was not an object.");
        return false;
    }

    const JsonValue *aSymbol = pValue.find("symbol");
    if (aSymbol == NULL) {
        SetError(pError, "Target symbol was missing.");
        return false;
    }

    GSymbol aParsedSymbol;
    if (!SymbolFromJsonValue(*aSymbol, &aParsedSymbol, pError)) {
        return false;
    }

    const JsonValue *aIndex = pValue.find("index");
    if ((aIndex == NULL) || aIndex->is_null()) {
        *pTarget = GTarget::Symbol(aParsedSymbol);
        return true;
    }

    GExpr aIndexExpr;
    if (!ExprFromJsonValue(*aIndex, &aIndexExpr, pError)) {
        return false;
    }
    *pTarget = GTarget::Write(aParsedSymbol, aIndexExpr);
    return true;
}

JsonValue StatementToJsonValue(const GStatement &pStatement) {
    JsonValue::Object aObject;
    if (pStatement.IsRawLine()) {
        aObject["statement_type"] = JsonValue::String("raw_line");
        aObject["line"] = JsonValue::String(pStatement.mRawLine);
        aObject["output_prefix"] = JsonValue::String(pStatement.mOutputPrefix);
        return JsonValue::ObjectValue(std::move(aObject));
    }
    if (pStatement.IsInvalid()) {
        std::printf("warn: StatementToJsonValue encountered invalid assign statement; preserving as raw warning line.\n");
        aObject["statement_type"] = JsonValue::String("raw_line");
        aObject["line"] = JsonValue::String("// export warning: invalid assign statement was dropped");
        aObject["output_prefix"] = JsonValue::String("");
        return JsonValue::ObjectValue(std::move(aObject));
    }

    aObject["statement_type"] = JsonValue::String("assign");
    aObject["target"] = TargetToJsonValue(pStatement.mTarget);
    aObject["assign"] = JsonValue::String(AssignTypeToken(pStatement.mAssignType));
    aObject["expression"] = ExprToJsonValue(pStatement.mExpression);
    aObject["output_prefix"] = JsonValue::String(pStatement.mOutputPrefix);
    return JsonValue::ObjectValue(std::move(aObject));
}

bool StatementFromJsonValue(const JsonValue &pValue,
                            GStatement *pStatement,
                            std::string *pError) {
    if (pStatement == NULL) {
        SetError(pError, "Statement output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pError, "Statement JSON was not an object.");
        return false;
    }

    const JsonValue *aStatementType = pValue.find("statement_type");
    const JsonValue *aOutputPrefix = pValue.find("output_prefix");
    if ((aStatementType != NULL) && aStatementType->is_string() &&
        (aStatementType->as_string() == "raw_line")) {
        const JsonValue *aLine = pValue.find("line");
        if ((aLine == NULL) || !aLine->is_string()) {
            SetError(pError, "Raw-line statement JSON was incomplete.");
            return false;
        }
        GStatement aRaw = GStatement::RawLine(aLine->as_string());
        if ((aOutputPrefix != NULL) && aOutputPrefix->is_string()) {
            aRaw.mOutputPrefix = aOutputPrefix->as_string();
        }
        *pStatement = aRaw;
        return true;
    }

    const JsonValue *aTarget = pValue.find("target");
    const JsonValue *aAssign = pValue.find("assign");
    const JsonValue *aExpr = pValue.find("expression");
    if ((aTarget == NULL) || (aAssign == NULL) || !aAssign->is_string() || (aExpr == NULL)) {
        SetError(pError, "Statement JSON was incomplete.");
        return false;
    }

    GStatement aStatement;
    if (!TargetFromJsonValue(*aTarget, &aStatement.mTarget, pError) ||
        !ExprFromJsonValue(*aExpr, &aStatement.mExpression, pError) ||
        !AssignTypeFromToken(aAssign->as_string(), &aStatement.mAssignType)) {
        if ((aStatement.mAssignType == GAssignType::kInvalid) && (pError != NULL) && pError->empty()) {
            *pError = "Statement assign token was invalid.";
        }
        return false;
    }

    aStatement.mType = GStatementType::kAssign;
    if ((aOutputPrefix != NULL) && aOutputPrefix->is_string()) {
        aStatement.mOutputPrefix = aOutputPrefix->as_string();
    }
    if (aStatement.IsInvalid()) {
        SetError(pError, "Statement JSON produced an invalid assign statement.");
        return false;
    }
    *pStatement = aStatement;
    return true;
}

JsonValue LoopToJsonValue(const GLoop &pLoop) {
    JsonValue::Array aInit;
    for (const GStatement &aStatement : pLoop.mInitializationStatements) {
        aInit.push_back(StatementToJsonValue(aStatement));
    }

    JsonValue::Array aBody;
    for (const GStatement &aStatement : pLoop.mBodyStatements) {
        aBody.push_back(StatementToJsonValue(aStatement));
    }

    JsonValue::Object aObject;
    aObject["loop_variable"] = JsonValue::String(pLoop.mLoopVariableName);
    aObject["loop_begin"] = JsonValue::Number(static_cast<double>(pLoop.mLoopBegin));
    aObject["loop_begin_text"] = JsonValue::String(pLoop.mLoopBeginText);
    aObject["loop_end_text"] = JsonValue::String(pLoop.mLoopEndText);
    aObject["loop_step"] = JsonValue::Number(static_cast<double>(pLoop.mLoopStep));
    aObject["init"] = JsonValue::ArrayValue(std::move(aInit));
    aObject["body"] = JsonValue::ArrayValue(std::move(aBody));
    return JsonValue::ObjectValue(std::move(aObject));
}

bool LoopFromJsonValue(const JsonValue &pValue,
                       GLoop *pLoop,
                       std::string *pError) {
    if (pLoop == NULL) {
        SetError(pError, "Loop output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pError, "Loop JSON was not an object.");
        return false;
    }

    const JsonValue *aVariable = pValue.find("loop_variable");
    const JsonValue *aBegin = pValue.find("loop_begin");
    const JsonValue *aBeginText = pValue.find("loop_begin_text");
    const JsonValue *aEnd = pValue.find("loop_end_text");
    const JsonValue *aStep = pValue.find("loop_step");
    const JsonValue *aInit = pValue.find("init");
    const JsonValue *aBody = pValue.find("body");
    if ((aVariable == NULL) || !aVariable->is_string() ||
        (aBegin == NULL) ||
        (aEnd == NULL) || !aEnd->is_string() ||
        (aStep == NULL) ||
        (aInit == NULL) || !aInit->is_array() ||
        (aBody == NULL) || !aBody->is_array()) {
        SetError(pError, "Loop JSON was incomplete.");
        return false;
    }

    GLoop aLoop;
    if (!ParseInt32(*aBegin, &aLoop.mLoopBegin) ||
        !ParseInt32(*aStep, &aLoop.mLoopStep)) {
        SetError(pError, "Loop numeric fields were invalid.");
        return false;
    }

    aLoop.mLoopVariableName = aVariable->as_string();
    aLoop.mLoopVariable = GSymbol::Var(aLoop.mLoopVariableName);
    if ((aBeginText != NULL) && aBeginText->is_string()) {
        aLoop.mLoopBeginText = aBeginText->as_string();
    }
    aLoop.mLoopEndText = aEnd->as_string();

    for (const JsonValue &aValue : aInit->as_array()) {
        GStatement aStatement;
        if (!StatementFromJsonValue(aValue, &aStatement, pError)) {
            return false;
        }
        aLoop.mInitializationStatements.push_back(aStatement);
    }

    for (const JsonValue &aValue : aBody->as_array()) {
        GStatement aStatement;
        if (!StatementFromJsonValue(aValue, &aStatement, pError)) {
            return false;
        }
        aLoop.mBodyStatements.push_back(aStatement);
    }

    *pLoop = aLoop;
    return true;
}

std::string PrettyExpr(const GExpr &pExpr);

std::string PrettyTarget(const GTarget &pTarget) {
    if (pTarget.IsInvalid()) {
        return "invalid_target";
    }
    if (!pTarget.HasIndex()) {
        return pTarget.mSymbol.mName;
    }
    return pTarget.mSymbol.mName + "[" + PrettyExpr(*pTarget.mIndex) + "]";
}

std::string PrettyExpr(const GExpr &pExpr) {
    switch (pExpr.mType) {
        case GExprType::kSymbol:
            return pExpr.mSymbol.mName;
        case GExprType::kConst:
            return std::to_string(static_cast<unsigned long long>(pExpr.mConstVal));
        case GExprType::kRead:
            return pExpr.mSymbol.mName + "[" +
                   ((pExpr.mIndex != nullptr) ? PrettyExpr(*pExpr.mIndex) : std::string("0")) + "]";
        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
            return "(" + PrettyExpr(*pExpr.mA) + " " + ScalarOperatorText(pExpr.mType) +
                   " " + PrettyExpr(*pExpr.mB) + ")";
        case GExprType::kRotL8:
            return "rotl8(" + PrettyExpr(*pExpr.mA) + ", " + PrettyExpr(*pExpr.mB) + ")";
        default:
            return "invalid_expr";
    }
}

std::string PrettyStatement(const GStatement &pStatement) {
    if (pStatement.IsRawLine()) {
        return pStatement.mRawLine;
    }
    return PrettyTarget(pStatement.mTarget) + " " +
           AssignOperatorText(pStatement.mAssignType) + " " +
           PrettyExpr(pStatement.mExpression) + ";";
}

void AppendPrettyLoopLines(const GLoop &pLoop,
                           std::vector<std::string> *pLines) {
    const std::string aLoopBeginText = pLoop.mLoopBeginText.empty() ?
        std::to_string(pLoop.mLoopBegin) :
        pLoop.mLoopBeginText;
    for (const GStatement &aStatement : pLoop.mInitializationStatements) {
        pLines->push_back(PrettyStatement(aStatement));
    }
    pLines->push_back("for (int " + pLoop.mLoopVariableName + " = " +
                      aLoopBeginText + "; " +
                      pLoop.mLoopVariableName + " < " + pLoop.mLoopEndText + "; " +
                      pLoop.mLoopVariableName + " += " + std::to_string(pLoop.mLoopStep) + ") {");
    for (const GStatement &aStatement : pLoop.mBodyStatements) {
        pLines->push_back(Indent(1) + PrettyStatement(aStatement));
    }
    pLines->push_back("}");
}

std::string CppIndexForSlot(const TwistWorkSpaceSlot pSlot,
                            const GExpr *pIndexExpr,
                            const std::string &pIndexText) {
    (void)pIndexExpr;

    const int aElementCount = [&]() -> int {
        if (IsSaltSlot(pSlot)) {
            return S_SALT;
        }
        if (IsIndexListSlot(pSlot)) {
            return 256;
        }
        return TwistWorkSpace::GetBufferLength(pSlot);
    }();

    const bool aIsBlockSized = (aElementCount == S_BLOCK);
    if (aIsBlockSized &&
        ((pIndexText == "aIndex") || (pIndexText == "i") ||
         (pIndexText == "S_BLOCK1 - aIndex") || (pIndexText == "S_BLOCK1 - i"))) {
        return pIndexText;
    }

    std::string aMaskToken;
    switch (pSlot) {
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: aMaskToken = "(S_KEY - 1)"; break;
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: aMaskToken = "(S_KEY - 1)"; break;
        case TwistWorkSpaceSlot::kKeyRowReadA:
        case TwistWorkSpaceSlot::kKeyRowWriteA: aMaskToken = "W_KEY1"; break;
        case TwistWorkSpaceSlot::kKeyRowReadB:
        case TwistWorkSpaceSlot::kKeyRowWriteB: aMaskToken = "W_KEY1"; break;
        default:
            if (IsSaltSlot(pSlot)) {
                aMaskToken = "S_SALT1";
            } else if (IsIndexListSlot(pSlot)) {
                aMaskToken = "S_SBOX1";
            } else if (aElementCount == S_QUARTER) {
                aMaskToken = "S_QUARTER1";
            } else if (aElementCount == S_BLOCK) {
                aMaskToken = "S_BLOCK1";
            } else if ((aElementCount > 0) && ((aElementCount & (aElementCount - 1)) == 0)) {
                aMaskToken = std::to_string(aElementCount - 1) + "U";
            }
            break;
    }
    if (!aMaskToken.empty()) {
        return "(" + pIndexText + ") & " + aMaskToken;
    }
    if (aElementCount > 0) {
        return "(" + pIndexText + ") % " + std::to_string(aElementCount) + "U";
    }
    return pIndexText;
}

std::string CppExpr(const GExpr &pExpr) {
    const auto Diffuse32ArgumentText = [](const GExpr &pInput) -> std::string {
        if ((pInput.mType == GExprType::kSymbol) &&
            pInput.mSymbol.IsVar() &&
            (pInput.mSymbol.mName == "aSquash")) {
            return CppExpr(pInput);
        }
        if (pInput.mType == GExprType::kCast32) {
            return CppExpr(pInput);
        }
        return "static_cast<std::uint32_t>(" + CppExpr(pInput) + ")";
    };
    
    switch (pExpr.mType) {
        case GExprType::kSymbol:
            if (pExpr.mSymbol.IsBuf()) {
                return BufAliasName(pExpr.mSymbol.mSlot) + "[0]";
            }
            return pExpr.mSymbol.mName;
        case GExprType::kConst:
            if (pExpr.mConstVal == static_cast<std::uint64_t>(S_BLOCK1)) {
                return "S_BLOCK1";
            }
            if (pExpr.mConstPreferHex) {
                char aHexLiteral[24];
                std::snprintf(aHexLiteral,
                              sizeof(aHexLiteral),
                              "0x%016llXULL",
                              static_cast<unsigned long long>(pExpr.mConstVal));
                return aHexLiteral;
            }
            return std::to_string(static_cast<unsigned long long>(pExpr.mConstVal)) + "U";
        case GExprType::kRead: {
            const std::string aIndexText = (pExpr.mIndex != nullptr) ? CppExpr(*pExpr.mIndex) : std::string("0");
            return CppBufferAlias(pExpr.mSymbol) + "[" +
                   CppIndexForSlot(pExpr.mSymbol.mSlot, pExpr.mIndex.get(), aIndexText) + "]";
        }
        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kOr:
            if ((pExpr.mType == GExprType::kAdd) &&
                (pExpr.mB != nullptr) &&
                (pExpr.mB->mType == GExprType::kConst) &&
                (pExpr.mB->mConstVal == 0ULL)) {
                return CppExpr(*pExpr.mA);
            }
            if ((pExpr.mType == GExprType::kAdd) &&
                (pExpr.mA != nullptr) &&
                (pExpr.mA->mType == GExprType::kConst) &&
                (pExpr.mA->mConstVal == 0ULL)) {
                return CppExpr(*pExpr.mB);
            }
            if ((pExpr.mType == GExprType::kSub) &&
                (pExpr.mB != nullptr) &&
                (pExpr.mB->mType == GExprType::kConst) &&
                (pExpr.mB->mConstVal == 0ULL)) {
                return CppExpr(*pExpr.mA);
            }
            if ((pExpr.mType == GExprType::kSub) &&
                (pExpr.mA != nullptr) &&
                (pExpr.mA->mType == GExprType::kConst) &&
                (pExpr.mA->mConstVal == static_cast<std::uint64_t>(S_BLOCK1)) &&
                (pExpr.mB != nullptr) &&
                (pExpr.mB->mType == GExprType::kSymbol)) {
                return "S_BLOCK1 - " + CppExpr(*pExpr.mB);
            }
            return "(" + CppExpr(*pExpr.mA) + " " + ScalarOperatorText(pExpr.mType) +
                   " " + CppExpr(*pExpr.mB) + ")";
        case GExprType::kRotL8:
            return "RotL8(" + CppExpr(*pExpr.mA) + ", " + CppExpr(*pExpr.mB) + ")";
        case GExprType::kRotL32:
            return "RotL32(" + CppExpr(*pExpr.mA) + ", " + CppExpr(*pExpr.mB) + ")";
        case GExprType::kRotL64:
            return "RotL64(" + CppExpr(*pExpr.mA) + ", " + CppExpr(*pExpr.mB) + ")";
        case GExprType::kShiftL:
            return "(" + CppExpr(*pExpr.mA) + " << " + CppExpr(*pExpr.mB) + ")";
        case GExprType::kShiftR:
            return "(" + CppExpr(*pExpr.mA) + " >> " + CppExpr(*pExpr.mB) + ")";
        case GExprType::kDiffuse64A:
            return "TwistMix64::DiffuseA(" + CppExpr(*pExpr.mA) + ")";
        case GExprType::kDiffuse64B:
            return "TwistMix64::DiffuseB(" + CppExpr(*pExpr.mA) + ")";
        case GExprType::kDiffuse64C:
            return "TwistMix64::DiffuseC(" + CppExpr(*pExpr.mA) + ")";
        case GExprType::kDiffuse32A:
            return "TwistMix32::DiffuseA(" + Diffuse32ArgumentText(*pExpr.mA) + ")";
        case GExprType::kDiffuse32B:
            return "TwistMix32::DiffuseB(" + Diffuse32ArgumentText(*pExpr.mA) + ")";
        case GExprType::kDiffuse32C:
            return "TwistMix32::DiffuseC(" + Diffuse32ArgumentText(*pExpr.mA) + ")";
        case GExprType::kCast32:
            return "static_cast<std::uint32_t>(" + CppExpr(*pExpr.mA) + ")";
        default:
            return "0";
    }
}

std::string CppTarget(const GTarget &pTarget) {
    if (!pTarget.HasIndex()) {
        if (pTarget.IsBuf()) {
            return BufAliasName(pTarget.mSymbol.mSlot) + "[0]";
        }
        return pTarget.mSymbol.mName;
    }
    return CppBufferAlias(pTarget.mSymbol) + "[" +
           CppIndexForSlot(pTarget.mSymbol.mSlot, pTarget.mIndex.get(), CppExpr(*pTarget.mIndex)) + "]";
}

struct CppReadWrapMetadata {
    GReadWrapType                        mType = GReadWrapType::kNone;
    GSymbol                              mIndexSymbol;
    GSymbol                              mOracleSymbol;
};

bool CppWrapMetadataEqual(const CppReadWrapMetadata &pLeft,
                          const CppReadWrapMetadata &pRight) {
    return (pLeft.mType == pRight.mType) &&
           (pLeft.mIndexSymbol == pRight.mIndexSymbol) &&
           (pLeft.mOracleSymbol == pRight.mOracleSymbol);
}

void AppendUniqueWrapMetadata(std::vector<CppReadWrapMetadata> *pList,
                              const CppReadWrapMetadata &pMetadata) {
    if (pList == NULL) {
        return;
    }
    for (const CppReadWrapMetadata &aExisting : *pList) {
        if (CppWrapMetadataEqual(aExisting, pMetadata)) {
            return;
        }
    }
    pList->push_back(pMetadata);
}

void CollectReadWrapMetadataFromExpr(const GExpr &pExpr,
                                     std::vector<CppReadWrapMetadata> *pList) {
    if (pExpr.mType == GExprType::kRead) {
        if ((pExpr.mReadWrapType != GReadWrapType::kNone) &&
            !pExpr.mReadWrapIndexSymbol.IsInvalid() &&
            !pExpr.mReadWrapOracleSymbol.IsInvalid()) {
            CppReadWrapMetadata aMetadata;
            aMetadata.mType = pExpr.mReadWrapType;
            aMetadata.mIndexSymbol = pExpr.mReadWrapIndexSymbol;
            aMetadata.mOracleSymbol = pExpr.mReadWrapOracleSymbol;
            AppendUniqueWrapMetadata(pList, aMetadata);
        }
        if (pExpr.mIndex != nullptr) {
            CollectReadWrapMetadataFromExpr(*pExpr.mIndex, pList);
        }
        return;
    }

    if (pExpr.mA != nullptr) {
        CollectReadWrapMetadataFromExpr(*pExpr.mA, pList);
    }
    if (pExpr.mB != nullptr) {
        CollectReadWrapMetadataFromExpr(*pExpr.mB, pList);
    }
}

std::string CppSymbolText(const GSymbol &pSymbol) {
    if (pSymbol.IsBuf()) {
        return BufAliasName(pSymbol.mSlot);
    }
    return pSymbol.mName;
}

std::string CppReadWrapLimitToken(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kBlock: return "S_BLOCK";
        case GReadWrapType::kSBox: return "S_SBOX";
        case GReadWrapType::kSalt: return "S_SALT";
        case GReadWrapType::kKeyA: return "S_KEY";
        case GReadWrapType::kKeyB: return "S_KEY";
        default: return "S_BLOCK";
    }
}

std::string CppReadWrapTrimMaskToken(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kSBox: return "S_SBOX1";
        case GReadWrapType::kSalt: return "S_SALT1";
        case GReadWrapType::kKeyA: return "(S_KEY - 1)";
        case GReadWrapType::kKeyB: return "(S_KEY - 1)";
        default: return "";
    }
}

std::vector<std::string> CppReadWrapPreludeLines(const GStatement &pStatement) {
    std::vector<CppReadWrapMetadata> aMetadata;
    CollectReadWrapMetadataFromExpr(pStatement.mExpression, &aMetadata);

    std::vector<std::string> aLines;
    for (const CppReadWrapMetadata &aWrap : aMetadata) {
        const std::string aOracleName = CppSymbolText(aWrap.mOracleSymbol);
        const std::string aIndexName = CppSymbolText(aWrap.mIndexSymbol);
        const std::string aLimitToken = CppReadWrapLimitToken(aWrap.mType);
        const std::string aTrimMaskToken = CppReadWrapTrimMaskToken(aWrap.mType);

        aLines.push_back(aOracleName + " = " + aIndexName + ";");
        aLines.push_back("if (" + aOracleName + " >= " + aLimitToken + ") { " +
                         aOracleName + " -= " + aLimitToken + "; }");
        if (!aTrimMaskToken.empty()) {
            aLines.push_back(aOracleName + " &= " + aTrimMaskToken + ";");
        }
    }
    return aLines;
}

bool CanStripOuterParens(const std::string &pText) {
    if (pText.size() < 2U || pText.front() != '(' || pText.back() != ')') {
        return false;
    }
    int aDepth = 0;
    for (std::size_t aIndex = 0U; aIndex < pText.size(); ++aIndex) {
        const char aChar = pText[aIndex];
        if (aChar == '(') {
            aDepth += 1;
        } else if (aChar == ')') {
            aDepth -= 1;
            if (aDepth < 0) {
                return false;
            }
        }
        if ((aDepth == 0) && (aIndex + 1U < pText.size())) {
            return false;
        }
    }
    return aDepth == 0;
}

std::string StripOuterParens(const std::string &pText) {
    if (!CanStripOuterParens(pText)) {
        return pText;
    }
    return pText.substr(1U, pText.size() - 2U);
}

std::string CppStatement(const GStatement &pStatement) {
    if (pStatement.IsRawLine()) {
        return pStatement.mRawLine;
    }

    const std::string aTargetText = CppTarget(pStatement.mTarget);
    const std::string aExpressionText = StripOuterParens(CppExpr(pStatement.mExpression));

    if (pStatement.mTarget.IsBuf()) {
        if (pStatement.mAssignType == GAssignType::kSet) {
            return aTargetText + " = " + aExpressionText + ";";
        }
        if (pStatement.mAssignType == GAssignType::kAddAssign) {
            return aTargetText + " += " + aExpressionText + ";";
        }
        if (pStatement.mAssignType == GAssignType::kXorAssign) {
            return aTargetText + " ^= " + aExpressionText + ";";
        }
        if (pStatement.mAssignType == GAssignType::kOrAssign) {
            return aTargetText + " |= " + aExpressionText + ";";
        }
        
    }

    if (pStatement.mTarget.IsVar()) {
        if (pStatement.mAssignType == GAssignType::kSet) {
            return aTargetText + " = " + aExpressionText + ";";
        }
        if (pStatement.mAssignType == GAssignType::kAddAssign) {
            return aTargetText + " += " + aExpressionText + ";";
        }
        if (pStatement.mAssignType == GAssignType::kXorAssign) {
            return aTargetText + " ^= " + aExpressionText + ";";
        }
        if (pStatement.mAssignType == GAssignType::kOrAssign) {
            return aTargetText + " |= " + aExpressionText + ";";
        }
    }

    return aTargetText + " " + AssignOperatorText(pStatement.mAssignType) + " " + aExpressionText + ";";
}

void CollectXorTerms(const GExpr &pExpr,
                     std::vector<const GExpr *> *pTerms) {
    if (pTerms == nullptr) {
        return;
    }
    
    if ((pExpr.mType == GExprType::kXor) &&
        (pExpr.mA != nullptr) &&
        (pExpr.mB != nullptr)) {
        CollectXorTerms(*pExpr.mA, pTerms);
        CollectXorTerms(*pExpr.mB, pTerms);
        return;
    }
    
    pTerms->push_back(&pExpr);
}

bool IsWrappedContextWordAssignment(const GStatement &pStatement) {
    if (pStatement.IsRawLine() ||
        !pStatement.mTarget.IsVar() ||
        (pStatement.mAssignType != GAssignType::kSet)) {
        return false;
    }
    
    const std::string &aName = pStatement.mTarget.mSymbol.mName;
    return (aName == "aIngress") || (aName == "aCross");
}

bool AppendWrappedXorAssignmentLines(const GStatement &pStatement,
                                     std::vector<std::string> *pLines) {
    if ((pLines == nullptr) || !IsWrappedContextWordAssignment(pStatement)) {
        return false;
    }
    
    std::vector<const GExpr *> aTerms;
    CollectXorTerms(pStatement.mExpression, &aTerms);
    if (aTerms.size() <= 2U) {
        return false;
    }
    
    const std::string aTargetText = CppTarget(pStatement.mTarget);
    
    for (std::size_t aIndex = 0U; aIndex < aTerms.size(); aIndex += 2U) {
        const bool aHasSecond = ((aIndex + 1U) < aTerms.size());
        const bool aIsFirst = (aIndex == 0U);
        
        std::string aExpressionText;
        if (aHasSecond) {
            aExpressionText = "(" + StripOuterParens(CppExpr(*aTerms[aIndex])) + " ^ " +
                StripOuterParens(CppExpr(*aTerms[aIndex + 1U])) + ")";
        } else {
            aExpressionText = StripOuterParens(CppExpr(*aTerms[aIndex]));
        }
        
        const std::string aAssignText = aIsFirst ? " = " : " ^= ";
        pLines->push_back(pStatement.mOutputPrefix + aTargetText + aAssignText + aExpressionText + ";");
    }
    
    return true;
}

std::vector<std::string> CppStatementLines(const GStatement &pStatement) {
    if (pStatement.IsRawLine()) {
        return { pStatement.mOutputPrefix + pStatement.mRawLine };
    }

    std::vector<std::string> aLines = CppReadWrapPreludeLines(pStatement);
    for (std::string &aLine : aLines) {
        aLine = pStatement.mOutputPrefix + aLine;
    }
    if (AppendWrappedXorAssignmentLines(pStatement, &aLines)) {
        return aLines;
    }
    aLines.push_back(pStatement.mOutputPrefix + CppStatement(pStatement));
    return aLines;
}

bool EvaluateExpr(const GExpr &pExpr,
                  TwistWorkSpace *pWorkSpace,
                  TwistExpander *pExpander,
                  std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                  GRuntimeScalar *pValue,
                  std::string *pError) {
    if ((pVariables == NULL) || (pValue == NULL)) {
        SetError(pError, "Expression evaluation output was null.");
        return false;
    }

    switch (pExpr.mType) {
        case GExprType::kSymbol:
            if (pExpr.mSymbol.IsVar()) {
                bool aWasWorkspaceDomainWord = false;
                if (!ResolveWorkspaceDomainWordValue(pExpr.mSymbol.mName,
                                                     pWorkSpace,
                                                     pValue,
                                                     &aWasWorkspaceDomainWord,
                                                     pError)) {
                    return false;
                }
                if (aWasWorkspaceDomainWord) {
                    return true;
                }

                const auto aIterator = pVariables->find(pExpr.mSymbol.mName);
                if (aIterator != pVariables->end()) {
                    *pValue = aIterator->second;
                    return true;
                }

                bool aWasLegacyDomainWord = false;
                if (!ResolveLegacyWorkspaceDomainWordValue(pExpr.mSymbol.mName,
                                                           pWorkSpace,
                                                           pValue,
                                                           &aWasLegacyDomainWord,
                                                           pError)) {
                    return false;
                }
                if (aWasLegacyDomainWord) {
                    return true;
                }

                *pValue = 0ULL;
                return true;
            }
            if (pExpr.mSymbol.IsBuf()) {
                if (pWorkSpace == NULL) {
                    SetError(pError, "Workspace was null during buffer read.");
                    return false;
                }
                std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkSpace, pExpander, pExpr.mSymbol.mSlot);
                if (aBuffer == NULL) {
                    SetError(pError, "Buffer symbol resolved to null.");
                    return false;
                }
                if (IsSaltSlot(pExpr.mSymbol.mSlot)) {
                    *pValue = reinterpret_cast<std::uint64_t *>(aBuffer)[0];
                } else if (IsIndexListSlot(pExpr.mSymbol.mSlot)) {
                    *pValue = static_cast<GRuntimeScalar>(reinterpret_cast<std::size_t *>(aBuffer)[0]);
                } else {
                    *pValue = static_cast<GRuntimeScalar>(aBuffer[0]);
                }
                return true;
            }
            break;

        case GExprType::kConst:
            *pValue = pExpr.mConstVal;
            return true;

        case GExprType::kRead: {
            if (pWorkSpace == NULL) {
                SetError(pError, "Workspace was null during read.");
                return false;
            }
            GRuntimeScalar aIndexValue = 0ULL;
            if (pExpr.mReadWrapType != GReadWrapType::kNone) {
                GRuntimeScalar aBaseIndexValue = 0ULL;
                if (pExpr.mReadWrapIndexSymbol.IsVar()) {
                    const auto aBaseIterator = pVariables->find(pExpr.mReadWrapIndexSymbol.mName);
                    aBaseIndexValue = (aBaseIterator == pVariables->end()) ? 0ULL : aBaseIterator->second;
                } else if (pExpr.mReadWrapIndexSymbol.IsBuf()) {
                    std::uint8_t *aBaseBuffer = TwistWorkSpace::GetBuffer(pWorkSpace, pExpander, pExpr.mReadWrapIndexSymbol.mSlot);
                    if (aBaseBuffer == NULL) {
                        SetError(pError, "Read wrap index buffer was null.");
                        return false;
                    }
                    if (IsSaltSlot(pExpr.mReadWrapIndexSymbol.mSlot)) {
                        aBaseIndexValue = reinterpret_cast<std::uint64_t *>(aBaseBuffer)[0];
                    } else if (IsIndexListSlot(pExpr.mReadWrapIndexSymbol.mSlot)) {
                        aBaseIndexValue = static_cast<GRuntimeScalar>(reinterpret_cast<std::size_t *>(aBaseBuffer)[0]);
                    } else {
                        aBaseIndexValue = static_cast<GRuntimeScalar>(aBaseBuffer[0]);
                    }
                } else {
                    SetError(pError, "Read wrap index symbol was invalid.");
                    return false;
                }

                GRuntimeScalar aOracleValue = aBaseIndexValue;
                const int aWrapLimit = ReadWrapLimitForType(pExpr.mReadWrapType);
                if ((aWrapLimit > 0) && (aOracleValue >= static_cast<GRuntimeScalar>(aWrapLimit))) {
                    aOracleValue -= static_cast<GRuntimeScalar>(aWrapLimit);
                }
                const unsigned int aWrapTrimMask = ReadWrapTrimMaskForType(pExpr.mReadWrapType);
                if (aWrapTrimMask != 0U) {
                    aOracleValue = aOracleValue & static_cast<GRuntimeScalar>(aWrapTrimMask);
                }
                aIndexValue = aOracleValue;

                if (pExpr.mReadWrapOracleSymbol.IsVar()) {
                    (*pVariables)[pExpr.mReadWrapOracleSymbol.mName] = aOracleValue;
                }
            } else {
                if ((pExpr.mIndex == NULL) ||
                    !EvaluateExpr(*pExpr.mIndex, pWorkSpace, pExpander, pVariables, &aIndexValue, pError)) {
                    SetError(pError, "Read expression index was invalid.");
                    return false;
                }
            }
            std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkSpace, pExpander, pExpr.mSymbol.mSlot);
            if (aBuffer == NULL) {
                SetError(pError, "Read expression buffer was null.");
                return false;
            }
            const std::size_t aIndex = RuntimeIndexForSlot(pExpr.mSymbol.mSlot, aIndexValue);
            if (IsSaltSlot(pExpr.mSymbol.mSlot)) {
                *pValue = reinterpret_cast<std::uint64_t *>(aBuffer)[aIndex];
            } else if (IsIndexListSlot(pExpr.mSymbol.mSlot)) {
                *pValue = static_cast<GRuntimeScalar>(reinterpret_cast<std::size_t *>(aBuffer)[aIndex]);
            } else {
                *pValue = static_cast<GRuntimeScalar>(aBuffer[aIndex]);
            }
            return true;
        }

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kOr:
        case GExprType::kRotL8:
        case GExprType::kRotL32:
        case GExprType::kRotL64:
        case GExprType::kShiftL:
        case GExprType::kShiftR: {
            GRuntimeScalar aLeft = 0ULL;
            GRuntimeScalar aRight = 0ULL;
            if ((pExpr.mA == NULL) || (pExpr.mB == NULL) ||
                !EvaluateExpr(*pExpr.mA, pWorkSpace, pExpander, pVariables, &aLeft, pError) ||
                !EvaluateExpr(*pExpr.mB, pWorkSpace, pExpander, pVariables, &aRight, pError)) {
                SetError(pError, "Binary expression child was invalid.");
                return false;
            }
            switch (pExpr.mType) {
                case GExprType::kAdd: *pValue = aLeft + aRight; return true;
                case GExprType::kSub: *pValue = aLeft - aRight; return true;
                case GExprType::kMul: *pValue = aLeft * aRight; return true;
                case GExprType::kXor: *pValue = aLeft ^ aRight; return true;
                case GExprType::kAnd: *pValue = aLeft & aRight; return true;
                case GExprType::kOr: *pValue = aLeft | aRight; return true;
                case GExprType::kRotL8: *pValue = RotL8(static_cast<std::uint8_t>(aLeft), static_cast<std::uint8_t>(aRight)); return true;
                case GExprType::kRotL32: *pValue = RotL32(static_cast<std::uint32_t>(aLeft), static_cast<std::uint32_t>(aRight)); return true;
                case GExprType::kRotL64: *pValue = RotL64(aLeft, aRight); return true;
                case GExprType::kShiftL: *pValue = ShiftL64(aLeft, aRight); return true;
                case GExprType::kShiftR: *pValue = ShiftR64(aLeft, aRight); return true;
                default: break;
            }
            break;
        }

        case GExprType::kDiffuse64A:
        case GExprType::kDiffuse64B:
        case GExprType::kDiffuse64C:
        case GExprType::kDiffuse32A:
        case GExprType::kDiffuse32B:
        case GExprType::kDiffuse32C:
        case GExprType::kCast32: {
            GRuntimeScalar aValue = 0ULL;
            if ((pExpr.mA == NULL) ||
                !EvaluateExpr(*pExpr.mA, pWorkSpace, pExpander, pVariables, &aValue, pError)) {
                SetError(pError, "Diffuse expression child was invalid.");
                return false;
            }
            switch (pExpr.mType) {
                case GExprType::kDiffuse64A: *pValue = TwistMix64::DiffuseA(aValue); return true;
                case GExprType::kDiffuse64B: *pValue = TwistMix64::DiffuseB(aValue); return true;
                case GExprType::kDiffuse64C: *pValue = TwistMix64::DiffuseC(aValue); return true;
                case GExprType::kDiffuse32A: *pValue = static_cast<GRuntimeScalar>(TwistMix32::DiffuseA(static_cast<std::uint32_t>(aValue))); return true;
                case GExprType::kDiffuse32B: *pValue = static_cast<GRuntimeScalar>(TwistMix32::DiffuseB(static_cast<std::uint32_t>(aValue))); return true;
                case GExprType::kDiffuse32C: *pValue = static_cast<GRuntimeScalar>(TwistMix32::DiffuseC(static_cast<std::uint32_t>(aValue))); return true;
                case GExprType::kCast32: *pValue = static_cast<GRuntimeScalar>(static_cast<std::uint32_t>(aValue)); return true;
                default: break;
            }
            break;
        }

        default:
            break;
    }

    SetError(pError, "Expression type could not be evaluated.");
    return false;
}

bool ExecuteStatement(const GStatement &pStatement,
                      TwistWorkSpace *pWorkSpace,
                      TwistExpander *pExpander,
                      std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                      std::string *pError) {
    if (pStatement.IsRawLine()) {
        bool aExecutedRawLine = false;
        if (!ExecuteRuntimeRawIndexShuffleLine(pStatement.mRawLine,
                                               pWorkSpace,
                                               pExpander,
                                               &aExecutedRawLine,
                                               pError)) {
            return false;
        }
        if (aExecutedRawLine) {
            return true;
        }

        if (!ExecuteRuntimeRawMemoryLine(pStatement.mRawLine,
                                         pWorkSpace,
                                         pExpander,
                                         &aExecutedRawLine,
                                         pError)) {
            return false;
        }
        if (aExecutedRawLine) {
            return true;
        }

        if (!ExecuteRuntimeRawSquashLine(pStatement.mRawLine,
                                         pWorkSpace,
                                         pExpander,
                                         &aExecutedRawLine,
                                         pError)) {
            return false;
        }
        if (aExecutedRawLine) {
            return true;
        }

        if (!ExecuteRuntimeRawDiffuseLine(pStatement.mRawLine,
                                          pWorkSpace,
                                          pExpander,
                                          pVariables,
                                          &aExecutedRawLine,
                                          pError)) {
            return false;
        }
        if (aExecutedRawLine) {
            return true;
        }

        if (!ExecuteRuntimeRawShiftBoxLine(pStatement.mRawLine,
                                           pWorkSpace,
                                           &aExecutedRawLine,
                                           pError)) {
            return false;
        }
        if (aExecutedRawLine) {
            return true;
        }

        if (!ExecuteRuntimeRawSnowLine(pStatement.mRawLine,
                                       pWorkSpace,
                                       pExpander,
                                       &aExecutedRawLine,
                                       pError)) {
            return false;
        }
        if (aExecutedRawLine) {
            return true;
        }

        if (!ExecuteRuntimeRawMatrixLine(pStatement.mRawLine,
                                         pWorkSpace,
                                         pExpander,
                                         pVariables,
                                         &aExecutedRawLine,
                                         pError)) {
            return false;
        }
        return true;
    }

    GRuntimeScalar aExpressionValue = 0ULL;
    if (!EvaluateExpr(pStatement.mExpression, pWorkSpace, pExpander, pVariables, &aExpressionValue, pError)) {
        return false;
    }

    if (pStatement.mTarget.IsVar()) {
        GRuntimeScalar &aTargetValue = (*pVariables)[pStatement.mTarget.mSymbol.mName];
        switch (pStatement.mAssignType) {
            case GAssignType::kSet:
                aTargetValue = NormalizeScalarValueForName(pStatement.mTarget.mSymbol.mName, aExpressionValue);
                return true;
            case GAssignType::kAddAssign:
                aTargetValue = NormalizeScalarValueForName(
                    pStatement.mTarget.mSymbol.mName,
                    aTargetValue + aExpressionValue);
                return true;
            case GAssignType::kXorAssign:
                aTargetValue = NormalizeScalarValueForName(
                    pStatement.mTarget.mSymbol.mName,
                    aTargetValue ^ aExpressionValue);
                return true;
            case GAssignType::kOrAssign:
                aTargetValue = NormalizeScalarValueForName(
                    pStatement.mTarget.mSymbol.mName,
                    aTargetValue | aExpressionValue);
                return true;
            default:
                SetError(pError, "Variable assignment type was invalid.");
                return false;
        }
    }

    if (pStatement.mTarget.IsBuf()) {
        if (pWorkSpace == NULL) {
            SetError(pError, "Workspace was null during write.");
            return false;
        }
        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkSpace, pExpander, pStatement.mTarget.mSymbol.mSlot);
        if (aBuffer == NULL) {
            SetError(pError, "Write buffer was null.");
            return false;
        }
        GRuntimeScalar aIndexValue = 0ULL;
        if (pStatement.mTarget.mIndex != nullptr &&
            !EvaluateExpr(*pStatement.mTarget.mIndex, pWorkSpace, pExpander, pVariables, &aIndexValue, pError)) {
            return false;
        }

        const std::size_t aIndex = RuntimeIndexForSlot(pStatement.mTarget.mSymbol.mSlot, aIndexValue);
        if (IsSaltSlot(pStatement.mTarget.mSymbol.mSlot)) {
            std::uint64_t *aSaltLane = reinterpret_cast<std::uint64_t *>(aBuffer);
            switch (pStatement.mAssignType) {
                case GAssignType::kSet:
                    aSaltLane[aIndex] = aExpressionValue;
                    return true;
                case GAssignType::kAddAssign:
                    aSaltLane[aIndex] = aSaltLane[aIndex] + aExpressionValue;
                    return true;
                case GAssignType::kXorAssign:
                    aSaltLane[aIndex] = aSaltLane[aIndex] ^ aExpressionValue;
                    return true;
                case GAssignType::kOrAssign:
                    aSaltLane[aIndex] = aSaltLane[aIndex] | aExpressionValue;
                    return true;
                default:
                    SetError(pError, "Buffer assignment type was invalid.");
                    return false;
            }
        }
        if (IsIndexListSlot(pStatement.mTarget.mSymbol.mSlot)) {
            std::size_t *aIndexList = reinterpret_cast<std::size_t *>(aBuffer);
            switch (pStatement.mAssignType) {
                case GAssignType::kSet:
                    aIndexList[aIndex] = static_cast<std::size_t>(aExpressionValue);
                    return true;
                case GAssignType::kAddAssign:
                    aIndexList[aIndex] = static_cast<std::size_t>(aIndexList[aIndex] + aExpressionValue);
                    return true;
                case GAssignType::kXorAssign:
                    aIndexList[aIndex] = static_cast<std::size_t>(
                        static_cast<GRuntimeScalar>(aIndexList[aIndex]) ^ aExpressionValue);
                    return true;
                case GAssignType::kOrAssign:
                    aIndexList[aIndex] = static_cast<std::size_t>(
                        static_cast<GRuntimeScalar>(aIndexList[aIndex]) | aExpressionValue);
                    return true;
                default:
                    SetError(pError, "Buffer assignment type was invalid.");
                    return false;
            }
        }

        switch (pStatement.mAssignType) {
            case GAssignType::kSet:
                aBuffer[aIndex] = static_cast<std::uint8_t>(aExpressionValue);
                return true;
            case GAssignType::kAddAssign:
                aBuffer[aIndex] = static_cast<std::uint8_t>(static_cast<GRuntimeScalar>(aBuffer[aIndex]) + aExpressionValue);
                return true;
            case GAssignType::kXorAssign:
                aBuffer[aIndex] = static_cast<std::uint8_t>(static_cast<GRuntimeScalar>(aBuffer[aIndex]) ^ aExpressionValue);
                return true;
            case GAssignType::kOrAssign:
                aBuffer[aIndex] = static_cast<std::uint8_t>(static_cast<GRuntimeScalar>(aBuffer[aIndex]) | aExpressionValue);
                return true;
            default:
                SetError(pError, "Buffer assignment type was invalid.");
                return false;
        }
    }

    SetError(pError, "Statement target was invalid.");
    return false;
}

bool ExecuteStatementSequence(const std::vector<GStatement> &pStatements,
                              TwistWorkSpace *pWorkSpace,
                              TwistExpander *pExpander,
                              std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                              std::string *pError) {
    bool aInSwitch = false;
    bool aCaseActive = true;
    bool aWaitingForSwitchClose = false;
    int aSelectedCase = 0;
    int aCaseCount = 0;
    int aCasesSeen = 0;
    bool aInIf = false;
    bool aIfCondition = false;
    bool aIfActive = true;

    for (const GStatement &aStatement : pStatements) {
        if (aStatement.IsRawLine()) {
            int aParsedSelectedCase = 0;
            int aParsedCaseCount = 0;
            if (!aInIf &&
                !aInSwitch &&
                ParseRuntimeSwitchLine(aStatement.mRawLine,
                                       pVariables,
                                       &aParsedSelectedCase,
                                       &aParsedCaseCount)) {
                aInSwitch = true;
                aCaseActive = false;
                aWaitingForSwitchClose = false;
                aSelectedCase = aParsedSelectedCase;
                aCaseCount = aParsedCaseCount;
                aCasesSeen = 0;
                continue;
            }

            if (aInSwitch) {
                int aCaseValue = 0;
                if (ParseRuntimeCaseLine(aStatement.mRawLine, &aCaseValue)) {
                    aCasesSeen += 1;
                    aCaseActive = (aCaseValue == aSelectedCase);
                    aWaitingForSwitchClose = false;
                    continue;
                }

                if (IsRuntimeBreakLine(aStatement.mRawLine)) {
                    if (aCaseActive) {
                        aCaseActive = false;
                    }
                    continue;
                }

                if (IsRuntimeCloseBraceLine(aStatement.mRawLine)) {
                    if (aCasesSeen >= aCaseCount) {
                        if (aWaitingForSwitchClose) {
                            aInSwitch = false;
                            aCaseActive = true;
                            aWaitingForSwitchClose = false;
                        } else {
                            aWaitingForSwitchClose = true;
                        }
                    }
                    continue;
                }

                if (!aCaseActive) {
                    continue;
                }
            } else {
                bool aParsedIfCondition = false;
                if (!aInIf &&
                    ParseRuntimeIfByteMaskGreaterLine(aStatement.mRawLine,
                                                      pWorkSpace,
                                                      pExpander,
                                                      pVariables,
                                                      &aParsedIfCondition)) {
                    aInIf = true;
                    aIfCondition = aParsedIfCondition;
                    aIfActive = aParsedIfCondition;
                    continue;
                }

                if (aInIf) {
                    if (IsRuntimeElseLine(aStatement.mRawLine)) {
                        aIfActive = !aIfCondition;
                        continue;
                    }

                    if (IsRuntimeCloseBraceLine(aStatement.mRawLine)) {
                        aInIf = false;
                        aIfCondition = false;
                        aIfActive = true;
                        continue;
                    }

                    if (!aIfActive) {
                        continue;
                    }
                }
            }
        } else if ((aInSwitch && !aCaseActive) || (aInIf && !aIfActive)) {
            continue;
        }

        if (!ExecuteStatement(aStatement, pWorkSpace, pExpander, pVariables, pError)) {
            return false;
        }
    }

    return true;
}

} // namespace

GTarget::GTarget() {
    Invalidate();
}

GTarget GTarget::Symbol(const GSymbol &pSymbol) {
    GTarget aTarget;
    aTarget.mSymbol = pSymbol;
    return aTarget;
}

GTarget GTarget::Write(const GSymbol &pSymbol,
                       const GExpr &pIndex) {
    GTarget aTarget;
    aTarget.mSymbol = pSymbol;
    aTarget.mIndex = std::make_shared<GExpr>(pIndex);
    return aTarget;
}

void GTarget::Set(const GTarget &pOther) {
    mSymbol = pOther.mSymbol;
    mIndex = pOther.mIndex;
}

void GTarget::Invalidate() {
    mSymbol.Invalidate();
    mIndex.reset();
}

bool GTarget::IsInvalid() const {
    return mSymbol.IsInvalid() || ((mIndex != nullptr) && mIndex->IsInvalid());
}

bool GTarget::HasIndex() const {
    return mIndex != nullptr;
}

bool GTarget::IsVar() const {
    return mSymbol.IsVar();
}

bool GTarget::IsBuf() const {
    return mSymbol.IsBuf();
}

bool GTarget::HasSymbol(GSymbol pSymbol) const {
    if (mSymbol == pSymbol) {
        return true;
    }
    if (mIndex == nullptr) {
        return false;
    }
    for (const GSymbol &aSymbol : mIndex->GetSymbols()) {
        if (aSymbol == pSymbol) {
            return true;
        }
    }
    return false;
}

bool GTarget::HasOper(GOperType pOper) const {
    if (mIndex == nullptr) {
        return false;
    }
    for (GOperType aOper : mIndex->GetOps()) {
        if (aOper == pOper) {
            return true;
        }
    }
    return false;
}

GStatement::GStatement() {
    Invalidate();
}

GStatement GStatement::Assign(const GTarget &pTarget,
                              const GExpr &pExpression) {
    GStatement aStatement;
    aStatement.mType = GStatementType::kAssign;
    aStatement.mTarget = pTarget;
    aStatement.mAssignType = GAssignType::kSet;
    aStatement.mExpression = pExpression;
    return aStatement;
}

GStatement GStatement::AddAssign(const GTarget &pTarget,
                                 const GExpr &pExpression) {
    GStatement aStatement;
    aStatement.mType = GStatementType::kAssign;
    aStatement.mTarget = pTarget;
    aStatement.mAssignType = GAssignType::kAddAssign;
    aStatement.mExpression = pExpression;
    return aStatement;
}

GStatement GStatement::XorAssign(const GTarget &pTarget,
                                 const GExpr &pExpression) {
    GStatement aStatement;
    aStatement.mType = GStatementType::kAssign;
    aStatement.mTarget = pTarget;
    aStatement.mAssignType = GAssignType::kXorAssign;
    aStatement.mExpression = pExpression;
    return aStatement;
}

GStatement GStatement::OrAssign(const GTarget &pTarget,
                                 const GExpr &pExpression) {
    GStatement aStatement;
    aStatement.mType = GStatementType::kAssign;
    aStatement.mTarget = pTarget;
    aStatement.mAssignType = GAssignType::kOrAssign;
    aStatement.mExpression = pExpression;
    return aStatement;
}

GStatement GStatement::RawLine(const std::string &pRawLine) {
    GStatement aStatement;
    aStatement.mType = GStatementType::kRawLine;
    aStatement.mRawLine = pRawLine;
    aStatement.mAssignType = GAssignType::kSet;
    return aStatement;
}

GStatement GStatement::Comment(const std::string &pComment) {
    if (pComment.empty()) {
        return RawLine("//");
    }
    return RawLine("// " + pComment);
}

GStatement GStatement::EmptyLine() {
    return RawLine("");
}

void GStatement::Set(const GStatement &pOther) {
    mType = pOther.mType;
    mTarget = pOther.mTarget;
    mAssignType = pOther.mAssignType;
    mExpression = pOther.mExpression;
    mRawLine = pOther.mRawLine;
    mOutputPrefix = pOther.mOutputPrefix;
}

void GStatement::Invalidate() {
    mType = GStatementType::kAssign;
    mTarget.Invalidate();
    mAssignType = GAssignType::kInvalid;
    mExpression.Invalidate();
    mRawLine.clear();
    mOutputPrefix.clear();
}

bool GStatement::IsInvalid() const {
    if (mType == GStatementType::kRawLine) {
        return false;
    }
    return (mAssignType == GAssignType::kInvalid) ||
           mTarget.IsInvalid() ||
           mExpression.IsInvalid();
}

bool GStatement::IsRawLine() const {
    return mType == GStatementType::kRawLine;
}

GSymbol GStatement::GetAssignSymbol(int pIndex) const {
    if (pIndex == 0 && !mTarget.mSymbol.IsInvalid()) {
        return mTarget.mSymbol;
    }
    return GSymbol();
}

bool GStatement::HasAssignSymbol(int pIndex) const {
    return !GetAssignSymbol(pIndex).IsInvalid();
}

GOperType GStatement::GetAssignOper(int pIndex) const {
    (void)pIndex;
    return GOperType::kInv;
}

bool GStatement::HasAssignOper(int pIndex) const {
    return GetAssignOper(pIndex) != GOperType::kInv;
}

GSymbol GStatement::GetExprSymbol(int pIndex) const {
    const std::vector<GSymbol> aSymbols = mExpression.GetSymbols();
    if (pIndex < 0 || static_cast<std::size_t>(pIndex) >= aSymbols.size()) {
        return GSymbol();
    }
    return aSymbols[static_cast<std::size_t>(pIndex)];
}

bool GStatement::HasExprSymbol(int pIndex) const {
    return !GetExprSymbol(pIndex).IsInvalid();
}

GOperType GStatement::GetExprOper(int pIndex) const {
    const std::vector<GOperType> aOps = mExpression.GetOps();
    if (pIndex < 0 || static_cast<std::size_t>(pIndex) >= aOps.size()) {
        return GOperType::kInv;
    }
    return aOps[static_cast<std::size_t>(pIndex)];
}

bool GStatement::HasExprOper(int pIndex) const {
    return GetExprOper(pIndex) != GOperType::kInv;
}

bool GStatement::HasAssignSymbol(GSymbol pSymbol) const {
    return mTarget.mSymbol == pSymbol;
}

bool GStatement::HasAssignOper(GOperType pOper) const {
    return GetAssignOper(0) == pOper;
}

bool GStatement::HasExprSymbol(GSymbol pSymbol) const {
    for (const GSymbol &aSymbol : mExpression.GetSymbols()) {
        if (aSymbol == pSymbol) {
            return true;
        }
    }
    return false;
}

bool GStatement::HasExprOper(GOperType pOper) const {
    for (GOperType aOper : mExpression.GetOps()) {
        if (aOper == pOper) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> GStatement::ToCPPStatements() const {
    if (IsInvalid()) {
        return std::vector<std::string>();
    }
    return CppStatementLines(*this);
}

std::string GStatement::ToPretty() const {
    if (IsInvalid()) {
        return "invalid_statement;";
    }
    return PrettyStatement(*this);
}

GLoop::GLoop() {
    mLoopVariable = GSymbol::Var("i");
    mLoopVariableName = "i";
    mLoopBegin = 0;
    mLoopBeginText = "";
    mLoopEndText = "S_BLOCK";
    mLoopStep = 1;
}

bool GLoop::IsInvalid() const {
    if (mLoopVariableName.empty() || mLoopEndText.empty() || (mLoopStep == 0)) {
        return true;
    }
    for (const GStatement &aStatement : mInitializationStatements) {
        if (aStatement.IsInvalid()) {
            return true;
        }
    }
    for (const GStatement &aStatement : mBodyStatements) {
        if (aStatement.IsInvalid()) {
            return true;
        }
    }
    return false;
}

void GLoop::AddBody(GStatement &pStatemet) {
    mBodyStatements.push_back(pStatemet);
}

void GLoop::AddBody(GStatement *pStatement) {
    if (pStatement != nullptr) {
        mBodyStatements.push_back(*pStatement);
    }
}

void GLoop::AddBody(GStatement pStatement) {
    mBodyStatements.push_back(pStatement);
}

void GLoop::AddBody(std::vector<GStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }
    for (const GStatement &aStatement : *pStatements) {
        mBodyStatements.push_back(aStatement);
    }
}

void GLoop::AddInitialization(GStatement &pStatemet) {
    mInitializationStatements.push_back(pStatemet);
}

void GLoop::AddInitialization(GStatement *pStatement) {
    if (pStatement != nullptr) {
        mInitializationStatements.push_back(*pStatement);
    }
}

GBatch::GBatch() {
    mName = "twist_seed_batch";
    mExportsAsBlock = true;
}

GBatchChunk GBatchChunk::Loop(const GLoop &pLoop) {
    GBatchChunk aChunk;
    aChunk.mType = GBatchChunkType::kLoop;
    aChunk.mLoop = pLoop;
    return aChunk;
}

GBatchChunk GBatchChunk::Statements(const std::vector<GStatement> &pStatements) {
    GBatchChunk aChunk;
    aChunk.mType = GBatchChunkType::kStatements;
    aChunk.mStatements = pStatements;
    return aChunk;
}

bool GBatchChunk::IsInvalid() const {
    switch (mType) {
        case GBatchChunkType::kLoop:
            return mLoop.IsInvalid();
        case GBatchChunkType::kStatements:
            if (mStatements.empty()) {
                return true;
            }
            for (const GStatement &aStatement : mStatements) {
                if (aStatement.IsInvalid()) {
                    return true;
                }
            }
            return false;
        case GBatchChunkType::kInvalid:
        default:
            return true;
    }
}

void GBatch::CommitLoop(const GLoop &pLoop) {
    mLoops.push_back(pLoop);
    mChunks.push_back(GBatchChunk::Loop(pLoop));
}

void GBatch::CommitLoop(GLoop *pLoop) {
    if (pLoop != nullptr) {
        CommitLoop(*pLoop);
    }
}

void GBatch::CommitStatements(std::vector<GStatement> *pStatements) {
    if ((pStatements == nullptr) || pStatements->empty()) {
        return;
    }
    mChunks.push_back(GBatchChunk::Statements(*pStatements));
}

void GBatch::AddComment(std::string pComment) {
    std::vector<GStatement> aStatements;
    aStatements.push_back(GStatement::Comment(pComment));
    CommitStatements(&aStatements);
}

void GBatch::AddEmptyLine() {
    std::vector<GStatement> aStatements;
    aStatements.push_back(GStatement::EmptyLine());
    CommitStatements(&aStatements);
}

static int CountStatementReads(const GStatement &pStatement,
                               TwistWorkSpaceSlot pSlot) {
    int aCount = CountExprReads(pStatement.mExpression, pSlot);
    if (pStatement.mTarget.mIndex != nullptr) {
        aCount += CountExprReads(*pStatement.mTarget.mIndex, pSlot);
    }
    return aCount;
}

static int CountLoopReads(const GLoop &pLoop,
                          TwistWorkSpaceSlot pSlot) {
    int aCount = 0;
    for (const GStatement &aStatement : pLoop.mInitializationStatements) {
        aCount += CountStatementReads(aStatement, pSlot);
    }
    for (const GStatement &aStatement : pLoop.mBodyStatements) {
        aCount += CountStatementReads(aStatement, pSlot);
    }
    return aCount;
}

static int CountStatementWrites(const GStatement &pStatement,
                                TwistWorkSpaceSlot pSlot) {
    return CountTargetWrites(pStatement.mTarget, pSlot);
}

static int CountLoopWrites(const GLoop &pLoop,
                           TwistWorkSpaceSlot pSlot) {
    int aCount = 0;
    for (const GStatement &aStatement : pLoop.mInitializationStatements) {
        aCount += CountStatementWrites(aStatement, pSlot);
    }
    for (const GStatement &aStatement : pLoop.mBodyStatements) {
        aCount += CountStatementWrites(aStatement, pSlot);
    }
    return aCount;
}

static bool LoopReadsSlot(const GLoop &pLoop,
                          TwistWorkSpaceSlot pSlot) {
    return (CountLoopReads(pLoop, pSlot) > 0);
}

static bool LoopWritesSlot(const GLoop &pLoop,
                           TwistWorkSpaceSlot pSlot) {
    return (CountLoopWrites(pLoop, pSlot) > 0);
}

static void CollectVariablesFromStatement(const GStatement &pStatement,
                                          std::vector<std::string> *pNames) {
    if (pStatement.mTarget.IsVar()) {
        AppendUniqueVariableName(pNames, pStatement.mTarget.mSymbol.mName);
    }
    if (pStatement.mTarget.mIndex != nullptr) {
        CollectVariablesFromExpr(*pStatement.mTarget.mIndex, pNames);
    }
    CollectVariablesFromExpr(pStatement.mExpression, pNames);
}

static void CollectVariablesFromLoop(const GLoop &pLoop,
                                     std::vector<std::string> *pNames) {
    AppendUniqueVariableName(pNames, pLoop.mLoopVariableName);
    for (const GStatement &aStatement : pLoop.mInitializationStatements) {
        CollectVariablesFromStatement(aStatement, pNames);
    }
    for (const GStatement &aStatement : pLoop.mBodyStatements) {
        CollectVariablesFromStatement(aStatement, pNames);
    }
}

static void CollectSlotsFromStatement(const GStatement &pStatement,
                                      std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pStatement.IsRawLine()) {
        CollectRuntimeM88DispatchSlots(pStatement.mRawLine, pSlots);
        CollectRuntimeSquashSlots(pStatement.mRawLine, pSlots);
        CollectRuntimeMemorySlots(pStatement.mRawLine, pSlots);
        CollectRuntimeDiffuseSlots(pStatement.mRawLine, pSlots);
        return;
    }
    if (pStatement.mTarget.IsBuf()) {
        AppendUnique(pSlots, pStatement.mTarget.mSymbol.mSlot);
    }
    if (pStatement.mTarget.mIndex != nullptr) {
        CollectSlotsFromExpr(*pStatement.mTarget.mIndex, pSlots);
    }
    CollectSlotsFromExpr(pStatement.mExpression, pSlots);
}

static void CollectSlotsFromLoop(const GLoop &pLoop,
                                 std::vector<TwistWorkSpaceSlot> *pSlots) {
    for (const GStatement &aStatement : pLoop.mInitializationStatements) {
        CollectSlotsFromStatement(aStatement, pSlots);
    }
    for (const GStatement &aStatement : pLoop.mBodyStatements) {
        CollectSlotsFromStatement(aStatement, pSlots);
    }
}

bool GBatch::IsInvalid() const {
    if (mChunks.empty() && mLoops.empty()) {
        return true;
    }
    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if (aChunk.IsInvalid()) {
                return true;
            }
        }
        return false;
    }
    for (const GLoop &aLoop : mLoops) {
        if (aLoop.IsInvalid()) {
            return true;
        }
    }
    return false;
}

int GBatch::CountReads(TwistWorkSpaceSlot pSlot) const {
    int aCount = 0U;
    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if (aChunk.mType == GBatchChunkType::kLoop) {
                aCount += CountLoopReads(aChunk.mLoop, pSlot);
            } else if (aChunk.mType == GBatchChunkType::kStatements) {
                for (const GStatement &aStatement : aChunk.mStatements) {
                    aCount += CountStatementReads(aStatement, pSlot);
                }
            }
        }
        return aCount;
    }
    for (const GLoop &aLoop : mLoops) {
        aCount += CountLoopReads(aLoop, pSlot);
    }
    return aCount;
}

int GBatch::CountWrites(TwistWorkSpaceSlot pSlot) const {
    int aCount = 0U;
    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if (aChunk.mType == GBatchChunkType::kLoop) {
                aCount += CountLoopWrites(aChunk.mLoop, pSlot);
            } else if (aChunk.mType == GBatchChunkType::kStatements) {
                for (const GStatement &aStatement : aChunk.mStatements) {
                    aCount += CountStatementWrites(aStatement, pSlot);
                }
            }
        }
        return aCount;
    }
    for (const GLoop &aLoop : mLoops) {
        aCount += CountLoopWrites(aLoop, pSlot);
    }
    return aCount;
}

int GBatch::CountLoopsReading(TwistWorkSpaceSlot pSlot) const {
    int aCount = 0U;
    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if ((aChunk.mType == GBatchChunkType::kLoop) && LoopReadsSlot(aChunk.mLoop, pSlot)) {
                ++aCount;
            }
        }
        return aCount;
    }
    for (const GLoop &aLoop : mLoops) {
        if (LoopReadsSlot(aLoop, pSlot)) {
            ++aCount;
        }
    }
    return aCount;
}

int GBatch::CountLoopsWriting(TwistWorkSpaceSlot pSlot) const {
    int aCount = 0U;
    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if ((aChunk.mType == GBatchChunkType::kLoop) && LoopWritesSlot(aChunk.mLoop, pSlot)) {
                ++aCount;
            }
        }
        return aCount;
    }
    for (const GLoop &aLoop : mLoops) {
        if (LoopWritesSlot(aLoop, pSlot)) {
            ++aCount;
        }
    }
    return aCount;
}

std::vector<std::string> GBatch::CollectVariableNames() const {
    std::vector<std::string> aNames;
    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if (aChunk.mType == GBatchChunkType::kLoop) {
                CollectVariablesFromLoop(aChunk.mLoop, &aNames);
            } else if (aChunk.mType == GBatchChunkType::kStatements) {
                for (const GStatement &aStatement : aChunk.mStatements) {
                    CollectVariablesFromStatement(aStatement, &aNames);
                }
            }
        }
        return aNames;
    }
    for (const GLoop &aLoop : mLoops) {
        CollectVariablesFromLoop(aLoop, &aNames);
    }
    return aNames;
}

std::vector<TwistWorkSpaceSlot> GBatch::CollectReferencedSlots() const {
    std::vector<TwistWorkSpaceSlot> aSlots;
    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if (aChunk.mType == GBatchChunkType::kLoop) {
                CollectSlotsFromLoop(aChunk.mLoop, &aSlots);
            } else if (aChunk.mType == GBatchChunkType::kStatements) {
                for (const GStatement &aStatement : aChunk.mStatements) {
                    CollectSlotsFromStatement(aStatement, &aSlots);
                }
            }
        }
        return aSlots;
    }
    for (const GLoop &aLoop : mLoops) {
        CollectSlotsFromLoop(aLoop, &aSlots);
    }
    return aSlots;
}

std::string GBatch::ToPrettyString() const {
    std::vector<std::string> aLines;
    if (!mChunks.empty()) {
        for (std::size_t aIndex = 0U; aIndex < mChunks.size(); ++aIndex) {
            if (aIndex > 0U) {
                aLines.push_back("");
            }
            const GBatchChunk &aChunk = mChunks[aIndex];
            if (aChunk.mType == GBatchChunkType::kLoop) {
                AppendPrettyLoopLines(aChunk.mLoop, &aLines);
            } else if (aChunk.mType == GBatchChunkType::kStatements) {
                for (const GStatement &aStatement : aChunk.mStatements) {
                    aLines.push_back(aStatement.ToPretty());
                }
            }
        }
        std::ostringstream aStream;
        for (std::size_t aIndex = 0U; aIndex < aLines.size(); ++aIndex) {
            aStream << aLines[aIndex];
            if ((aIndex + 1U) < aLines.size()) {
                aStream << '\n';
            }
        }
        return aStream.str();
    }
    for (std::size_t aIndex = 0U; aIndex < mLoops.size(); ++aIndex) {
        if (aIndex > 0U) {
            aLines.push_back("");
        }
        AppendPrettyLoopLines(mLoops[aIndex], &aLines);
    }

    std::ostringstream aStream;
    for (std::size_t aIndex = 0U; aIndex < aLines.size(); ++aIndex) {
        aStream << aLines[aIndex];
        if ((aIndex + 1U) < aLines.size()) {
            aStream << '\n';
        }
    }
    return aStream.str();
}

std::string GBatch::ToJson(std::string *pError) const {
    JsonValue::Array aLoops;
    JsonValue::Array aChunks;

    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if (aChunk.IsInvalid()) {
                SetError(pError, "Batch could not be serialized because it had an invalid chunk.");
                return "";
            }

            JsonValue::Object aChunkObject;
            if (aChunk.mType == GBatchChunkType::kLoop) {
                aChunkObject["type"] = JsonValue::String("loop");
                aChunkObject["loop"] = LoopToJsonValue(aChunk.mLoop);
                aLoops.push_back(LoopToJsonValue(aChunk.mLoop));
            } else if (aChunk.mType == GBatchChunkType::kStatements) {
                JsonValue::Array aStatements;
                for (const GStatement &aStatement : aChunk.mStatements) {
                    aStatements.push_back(StatementToJsonValue(aStatement));
                }
                aChunkObject["type"] = JsonValue::String("statements");
                aChunkObject["statements"] = JsonValue::ArrayValue(std::move(aStatements));
            } else {
                SetError(pError, "Batch could not be serialized because it had an unknown chunk type.");
                return "";
            }
            aChunks.push_back(JsonValue::ObjectValue(std::move(aChunkObject)));
        }

        JsonValue::Object aObject;
        aObject["name"] = JsonValue::String(mName);
        aObject["exports_as_block"] = JsonValue::Bool(mExportsAsBlock);
        aObject["chunks"] = JsonValue::ArrayValue(std::move(aChunks));
        aObject["loops"] = JsonValue::ArrayValue(std::move(aLoops));
        return JsonValue::ObjectValue(std::move(aObject)).Serialize();
    }

    std::size_t aSkippedInvalidLoops = 0U;
    for (const GLoop &aLoop : mLoops) {
        // Allow statement-level sanitization in LoopToJsonValue/StatementToJsonValue.
        // We only skip loops whose control metadata is unusable.
        if (aLoop.mLoopVariableName.empty() ||
            aLoop.mLoopEndText.empty() ||
            (aLoop.mLoopStep == 0)) {
            ++aSkippedInvalidLoops;
            std::printf("warn: GBatch::ToJson skipped invalid loop metadata (var='%s', end='%s', step=%d)\n",
                        aLoop.mLoopVariableName.c_str(),
                        aLoop.mLoopEndText.c_str(),
                        aLoop.mLoopStep);
            continue;
        }
        aLoops.push_back(LoopToJsonValue(aLoop));
    }

    if (aLoops.empty()) {
        if (mLoops.empty()) {
            SetError(pError, "Batch could not be serialized because it had no loops.");
        } else {
            SetError(pError, "Batch could not be serialized because every loop had invalid metadata.");
        }
        return "";
    }
    if (aSkippedInvalidLoops > 0U) {
        std::printf("warn: GBatch::ToJson emitted %zu loops and skipped %zu invalid loops.\n",
                    aLoops.size(),
                    aSkippedInvalidLoops);
    }

    JsonValue::Object aObject;
    aObject["name"] = JsonValue::String(mName);
    aObject["exports_as_block"] = JsonValue::Bool(mExportsAsBlock);
    aObject["loops"] = JsonValue::ArrayValue(std::move(aLoops));
    return JsonValue::ObjectValue(std::move(aObject)).Serialize();
}

bool GBatch::FromJson(const std::string &pJsonText,
                      GBatch *pBatch,
                      std::string *pError) {
    if (pBatch == NULL) {
        SetError(pError, "Batch output was null.");
        return false;
    }

    auto aRoot = JsonValue::Parse(pJsonText, pError);
    if (!aRoot.has_value() || !aRoot->is_object()) {
        if ((pError != NULL) && pError->empty()) {
            *pError = "Batch JSON root was invalid.";
        }
        return false;
    }

    const JsonValue *aName = aRoot->find("name");
    const JsonValue *aExportsAsBlock = aRoot->find("exports_as_block");
    const JsonValue *aLoops = aRoot->find("loops");
    const JsonValue *aChunks = aRoot->find("chunks");
    if ((aName == NULL) || !aName->is_string()) {
        SetError(pError, "Batch JSON was incomplete.");
        return false;
    }

    GBatch aBatch;
    aBatch.mName = aName->as_string();
    if ((aExportsAsBlock != NULL) && aExportsAsBlock->is_bool()) {
        aBatch.mExportsAsBlock = aExportsAsBlock->as_bool();
    }
    if ((aChunks != NULL) && aChunks->is_array()) {
        for (const JsonValue &aChunkValue : aChunks->as_array()) {
            if (!aChunkValue.is_object()) {
                SetError(pError, "Batch chunk JSON was not an object.");
                return false;
            }

            const JsonValue *aType = aChunkValue.find("type");
            if ((aType == NULL) || !aType->is_string()) {
                SetError(pError, "Batch chunk JSON was missing a type.");
                return false;
            }

            const std::string aTypeText = aType->as_string();
            if (aTypeText == "loop") {
                const JsonValue *aLoopValue = aChunkValue.find("loop");
                if (aLoopValue == NULL) {
                    SetError(pError, "Batch loop chunk was missing loop data.");
                    return false;
                }
                GLoop aLoop;
                if (!LoopFromJsonValue(*aLoopValue, &aLoop, pError)) {
                    return false;
                }
                aBatch.CommitLoop(aLoop);
            } else if (aTypeText == "statements") {
                const JsonValue *aStatementsValue = aChunkValue.find("statements");
                if ((aStatementsValue == NULL) || !aStatementsValue->is_array()) {
                    SetError(pError, "Batch statements chunk was missing statement data.");
                    return false;
                }
                std::vector<GStatement> aStatements;
                for (const JsonValue &aStatementValue : aStatementsValue->as_array()) {
                    GStatement aStatement;
                    if (!StatementFromJsonValue(aStatementValue, &aStatement, pError)) {
                        return false;
                    }
                    aStatements.push_back(aStatement);
                }
                aBatch.CommitStatements(&aStatements);
            } else {
                SetError(pError, "Batch chunk type was unknown: " + aTypeText);
                return false;
            }
        }
        *pBatch = aBatch;
        return true;
    }

    if ((aLoops == NULL) || !aLoops->is_array()) {
        SetError(pError, "Batch JSON was incomplete.");
        return false;
    }

    for (const JsonValue &aLoopValue : aLoops->as_array()) {
        GLoop aLoop;
        if (!LoopFromJsonValue(aLoopValue, &aLoop, pError)) {
            return false;
        }
        aBatch.CommitLoop(aLoop);
    }

    *pBatch = aBatch;
    return true;
}

std::string GBatch::BuildCpp(const std::string &pFunctionName,
                             std::string *pError,
                             bool pEmitDeclarations) const {
    if (IsInvalid()) {
        SetError(pError, "Batch was invalid and could not be emitted as C++.");
        return "";
    }

    std::vector<std::string> aLines;
    aLines.push_back("static void " + pFunctionName + "(TwistWorkSpace *pWorkSpace) {");

    std::vector<std::string> aLoopVariables;
    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if ((aChunk.mType == GBatchChunkType::kLoop) && !aChunk.mLoop.mLoopVariableName.empty()) {
                AppendUnique(&aLoopVariables, aChunk.mLoop.mLoopVariableName);
            }
        }
    } else {
        for (const GLoop &aLoop : mLoops) {
            AppendUnique(&aLoopVariables, aLoop.mLoopVariableName);
        }
    }

    std::vector<std::string> aScalarVariables = CollectVariableNames();
    aScalarVariables.erase(
        std::remove_if(aScalarVariables.begin(),
                       aScalarVariables.end(),
                       [&aLoopVariables](const std::string &pName) {
                           for (const std::string &aLoopVar : aLoopVariables) {
                               if (aLoopVar == pName) {
                                   return true;
                               }
                           }
                           return false;
                       }),
        aScalarVariables.end()
    );
    const std::vector<std::string> aWorkspaceDomainWords =
        ExtractWorkspaceDomainWordNames(&aScalarVariables);
    SortScalarDeclarationNames(&aScalarVariables);

    if (pEmitDeclarations) {
        std::vector<TwistWorkSpaceSlot> aSlots = CollectReferencedSlots();
        for (TwistWorkSpaceSlot aSlot : aSlots) {
            if (IsImplicitPointerSlot(aSlot)) {
                continue;
            }
            if (IsSaltSlot(aSlot)) {
                aLines.push_back(Indent(1) + "std::uint64_t *" + BufAliasName(aSlot) +
                                 " = reinterpret_cast<std::uint64_t *>(TwistWorkSpace::GetBuffer(pWorkSpace, static_cast<TwistWorkSpaceSlot>(" +
                                 std::to_string(static_cast<int>(aSlot)) + ")));");
            } else {
                aLines.push_back(Indent(1) + "std::uint8_t *" + BufAliasName(aSlot) +
                                 " = TwistWorkSpace::GetBuffer(pWorkSpace, static_cast<TwistWorkSpaceSlot>(" +
                                 std::to_string(static_cast<int>(aSlot)) + "));");
            }
        }

        const std::vector<std::string> aWorkspaceDomainWordLines =
            WorkspaceDomainWordDeclarationLines(aWorkspaceDomainWords, 1);
        if (!aSlots.empty() &&
            (!aWorkspaceDomainWordLines.empty() || !aScalarVariables.empty())) {
            aLines.push_back("");
        }

        for (const std::string &aLine : aWorkspaceDomainWordLines) {
            aLines.push_back(aLine);
        }

        if (!aWorkspaceDomainWordLines.empty() && !aScalarVariables.empty()) {
            aLines.push_back("");
        }

        const std::vector<std::string> aDeclarationLines = ScalarDeclarationLines(aScalarVariables, 1);
        for (const std::string &aLine : aDeclarationLines) {
            aLines.push_back(aLine);
        }
    }

    auto AppendStatementLines = [&](const GStatement &pStatement, int pIndentLevel) {
        const std::vector<std::string> aStatementLines = CppStatementLines(pStatement);
        for (const std::string &aStatementLine : aStatementLines) {
            aLines.push_back(Indent(pIndentLevel) + aStatementLine);
        }
    };

    auto AppendLoopLines = [&](const GLoop &pLoop) {
        const std::string aLoopBeginText = pLoop.mLoopBeginText.empty() ?
            std::to_string(pLoop.mLoopBegin) :
            pLoop.mLoopBeginText;
        for (const GStatement &aStatement : pLoop.mInitializationStatements) {
            AppendStatementLines(aStatement, 1);
        }
        if (LoopUsesSizeT(pLoop)) {
            const std::string aSizeTLoopBeginText = pLoop.mLoopBeginText.empty() ?
                std::to_string(pLoop.mLoopBegin) + "U" :
                "static_cast<std::size_t>(" + pLoop.mLoopBeginText + ")";
            aLines.push_back(Indent(1) + "for (std::size_t " + pLoop.mLoopVariableName + " = " +
                             aSizeTLoopBeginText + "; " +
                             pLoop.mLoopVariableName + " < static_cast<std::size_t>(" + pLoop.mLoopEndText + "); " +
                             pLoop.mLoopVariableName + " += " + std::to_string(pLoop.mLoopStep) + "U) {");
        } else {
            aLines.push_back(Indent(1) + "for (int " + pLoop.mLoopVariableName + " = " +
                             aLoopBeginText + "; " +
                             pLoop.mLoopVariableName + " < " + pLoop.mLoopEndText + "; " +
                             pLoop.mLoopVariableName + " += " + std::to_string(pLoop.mLoopStep) + ") {");
        }
        for (const GStatement &aStatement : pLoop.mBodyStatements) {
            AppendStatementLines(aStatement, 2);
        }
        aLines.push_back(Indent(1) + "}");
    };

    if (!mChunks.empty()) {
        for (std::size_t aChunkIndex = 0U; aChunkIndex < mChunks.size(); ++aChunkIndex) {
            const GBatchChunk &aChunk = mChunks[aChunkIndex];
            if (pEmitDeclarations || (aChunkIndex > 0U)) {
                aLines.push_back("");
            }
            if (aChunk.mType == GBatchChunkType::kLoop) {
                AppendLoopLines(aChunk.mLoop);
            } else if (aChunk.mType == GBatchChunkType::kStatements) {
                for (const GStatement &aStatement : aChunk.mStatements) {
                    AppendStatementLines(aStatement, 1);
                }
            }
        }
    } else {
        for (std::size_t aLoopIndex = 0U; aLoopIndex < mLoops.size(); ++aLoopIndex) {
            const GLoop &aLoop = mLoops[aLoopIndex];
            if (pEmitDeclarations || (aLoopIndex > 0U)) {
                aLines.push_back("");
            }
            AppendLoopLines(aLoop);
        }
    }

    aLines.push_back("}");

    std::ostringstream aStream;
    for (std::size_t aIndex = 0U; aIndex < aLines.size(); ++aIndex) {
        aStream << aLines[aIndex];
        if ((aIndex + 1U) < aLines.size()) {
            aStream << '\n';
        }
    }
    return aStream.str();
}

std::string GBatch::BuildCppScopeBlock(std::string *pError,
                                       bool pEmitDeclarations) const {
    const std::string aFunctionText = BuildCpp("__GeneratedScopeBlock", pError, pEmitDeclarations);
    if (aFunctionText.empty()) {
        return "";
    }

    const std::size_t aBodyStart = aFunctionText.find('{');
    const std::size_t aBodyEnd = aFunctionText.rfind('}');
    if ((aBodyStart == std::string::npos) ||
        (aBodyEnd == std::string::npos) ||
        (aBodyEnd <= aBodyStart)) {
        SetError(pError, "Failed to convert batch function text into scope block.");
        return "";
    }

    std::string aBody = aFunctionText.substr(aBodyStart + 1U, aBodyEnd - aBodyStart - 1U);
    while (!aBody.empty() && (aBody.front() == '\n' || aBody.front() == '\r')) {
        aBody.erase(aBody.begin());
    }
    while (!aBody.empty() && (aBody.back() == '\n' || aBody.back() == '\r')) {
        aBody.pop_back();
    }

    std::ostringstream aStream;
    if (mExportsAsBlock) {
        aStream << "{\n";
    }
    if (!aBody.empty()) {
        std::istringstream aBodyStream(aBody);
        std::string aLine;
        bool aIsFirstLine = true;
        while (std::getline(aBodyStream, aLine)) {
            if (!aIsFirstLine) {
                aStream << '\n';
            }
            aIsFirstLine = false;
            aStream << aLine;
        }
        if (mExportsAsBlock) {
            aStream << '\n';
        }
    }
    if (mExportsAsBlock) {
        aStream << "}";
    }
    return aStream.str();
}

bool GBatch::Execute(TwistWorkSpace *pWorkSpace,
                     TwistExpander *pExpander,
                     std::string *pError) const {
    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    return ExecuteWithVariables(pWorkSpace, pExpander, &aVariables, pError);
}

bool GBatch::ExecuteWithVariables(TwistWorkSpace *pWorkSpace,
                                  TwistExpander *pExpander,
                                  std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                  std::string *pError) const {
    if (IsInvalid()) {
        SetError(pError, "Batch was invalid and could not be executed.");
        return false;
    }
    if (pVariables == nullptr) {
        SetError(pError, "Batch variable map was null.");
        return false;
    }

    std::unordered_map<std::string, GRuntimeScalar> aLocalVariables;
    for (const auto &aPair : *pVariables) {
        aLocalVariables[aPair.first] = aPair.second;
    }

    for (const std::string &aName : CollectVariableNames()) {
        if (IsWorkspaceResolvedDomainWordName(aName)) {
            continue;
        }
        if (aLocalVariables.find(aName) == aLocalVariables.end()) {
            aLocalVariables[aName] = 0ULL;
        }
    }

    auto ExecuteLoop = [&](const GLoop &pLoop) -> bool {
        for (const GStatement &aStatement : pLoop.mInitializationStatements) {
            if (!ExecuteStatement(aStatement, pWorkSpace, pExpander, &aLocalVariables, pError)) {
                return false;
            }
        }

        const int aLoopEnd = ResolveLengthText(pLoop.mLoopEndText);
        for (int aLoopValue = pLoop.mLoopBegin;
             (pLoop.mLoopStep > 0) ? (aLoopValue < aLoopEnd) : (aLoopValue > aLoopEnd);
             aLoopValue += pLoop.mLoopStep) {
            aLocalVariables[pLoop.mLoopVariableName] = static_cast<GRuntimeScalar>(aLoopValue);
            if (!ExecuteStatementSequence(pLoop.mBodyStatements,
                                          pWorkSpace,
                                          pExpander,
                                          &aLocalVariables,
                                          pError)) {
                return false;
            }
        }
        return true;
    };

    if (!mChunks.empty()) {
        for (const GBatchChunk &aChunk : mChunks) {
            if (aChunk.mType == GBatchChunkType::kLoop) {
                if (!ExecuteLoop(aChunk.mLoop)) {
                    return false;
                }
            } else if (aChunk.mType == GBatchChunkType::kStatements) {
                if (!ExecuteStatementSequence(aChunk.mStatements,
                                              pWorkSpace,
                                              pExpander,
                                              &aLocalVariables,
                                              pError)) {
                    return false;
                }
            }
        }

        for (const auto &aPair : aLocalVariables) {
            (*pVariables)[aPair.first] = aPair.second;
        }
        return true;
    }

    for (const GLoop &aLoop : mLoops) {
        if (!ExecuteLoop(aLoop)) {
            return false;
        }
    }

    for (const auto &aPair : aLocalVariables) {
        (*pVariables)[aPair.first] = aPair.second;
    }

    return true;
}
