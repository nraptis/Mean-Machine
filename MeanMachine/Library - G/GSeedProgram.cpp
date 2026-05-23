//
//  GSeedProgram.cpp
//  MeanMachine
//

#include "GSeedProgram.hpp"

#include "GJson.hpp"
#include "TwistFunctional.hpp"

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

std::string ScopeSymbolKey(const GSymbol &pSymbol) {
    if (pSymbol.IsVar()) {
        return "var:" + pSymbol.mName;
    }
    if (pSymbol.IsBuf()) {
        return "buf:" + std::to_string(static_cast<int>(pSymbol.mSlot));
    }
    return "invalid";
}

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
           (pName == "pInput") ||
           (pName == "pOutput");
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

std::string SlotToken(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return "source";
        case TwistWorkSpaceSlot::kDest: return "dest";
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
        case TwistWorkSpaceSlot::kParamDomainSBoxA: return "sbox_a";
        case TwistWorkSpaceSlot::kParamDomainSBoxB: return "sbox_b";
        case TwistWorkSpaceSlot::kParamDomainSBoxC: return "sbox_c";
        case TwistWorkSpaceSlot::kParamDomainSBoxD: return "sbox_d";
        case TwistWorkSpaceSlot::kParamDomainSBoxE: return "sbox_e";
        case TwistWorkSpaceSlot::kParamDomainSBoxF: return "sbox_f";
        case TwistWorkSpaceSlot::kParamDomainSBoxG: return "sbox_g";
        case TwistWorkSpaceSlot::kParamDomainSBoxH: return "sbox_h";
        case TwistWorkSpaceSlot::kExpansionLaneA: return "seed_lane_a";
        case TwistWorkSpaceSlot::kExpansionLaneB: return "seed_lane_b";
        case TwistWorkSpaceSlot::kExpansionLaneC: return "seed_lane_c";
        case TwistWorkSpaceSlot::kExpansionLaneD: return "seed_lane_d";
        case TwistWorkSpaceSlot::kExpansionLaneE: return "seed_lane_e";
        case TwistWorkSpaceSlot::kExpansionLaneF: return "seed_lane_f";
        case TwistWorkSpaceSlot::kWorkLaneA: return "work_lane_a";
        case TwistWorkSpaceSlot::kWorkLaneB: return "work_lane_b";
        case TwistWorkSpaceSlot::kWorkLaneC: return "work_lane_c";
        case TwistWorkSpaceSlot::kWorkLaneD: return "work_lane_d";
        case TwistWorkSpaceSlot::kWorkLaneE: return "work_lane_e";
        case TwistWorkSpaceSlot::kWorkLaneF: return "work_lane_f";
        case TwistWorkSpaceSlot::kOperationLaneA: return "operation_lane_a";
        case TwistWorkSpaceSlot::kOperationLaneB: return "operation_lane_b";
        case TwistWorkSpaceSlot::kOperationLaneC: return "operation_lane_c";
        case TwistWorkSpaceSlot::kOperationLaneD: return "operation_lane_d";
        case TwistWorkSpaceSlot::kOperationLaneE: return "operation_lane_e";
        case TwistWorkSpaceSlot::kOperationLaneF: return "operation_lane_f";
        case TwistWorkSpaceSlot::kSnowLaneA: return "snow_lane_a";
        case TwistWorkSpaceSlot::kSnowLaneB: return "snow_lane_b";
        case TwistWorkSpaceSlot::kSnowLaneC: return "snow_lane_c";
        case TwistWorkSpaceSlot::kSnowLaneD: return "snow_lane_d";
        case TwistWorkSpaceSlot::kMaskLaneA: return "mask_lane_a";
        case TwistWorkSpaceSlot::kMaskLaneB: return "mask_lane_b";
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
        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return "mask_box_unrolled_a";
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return "mask_box_unrolled_b";
        case TwistWorkSpaceSlot::kMaskRowReadA: return "mask_row_read_a";
        case TwistWorkSpaceSlot::kMaskRowReadB: return "mask_row_read_b";
        case TwistWorkSpaceSlot::kMaskRowWriteA: return "mask_row_write_a";
        case TwistWorkSpaceSlot::kMaskRowWriteB: return "mask_row_write_b";
        default:
            return "slot_" + std::to_string(static_cast<int>(pSlot));
    }
}

bool SlotFromToken(const std::string &pToken,
                   TwistWorkSpaceSlot *pSlot) {
    if (pSlot == NULL) {
        return false;
    }

    static const std::vector<TwistWorkSpaceSlot> kSlots = {
        TwistWorkSpaceSlot::kSource,
        TwistWorkSpaceSlot::kDest,
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
        TwistWorkSpaceSlot::kParamDomainSBoxA,
        TwistWorkSpaceSlot::kParamDomainSBoxB,
        TwistWorkSpaceSlot::kParamDomainSBoxC,
        TwistWorkSpaceSlot::kParamDomainSBoxD,
        TwistWorkSpaceSlot::kParamDomainSBoxE,
        TwistWorkSpaceSlot::kParamDomainSBoxF,
        TwistWorkSpaceSlot::kParamDomainSBoxG,
        TwistWorkSpaceSlot::kParamDomainSBoxH,
        TwistWorkSpaceSlot::kExpansionLaneA,
        TwistWorkSpaceSlot::kExpansionLaneB,
        TwistWorkSpaceSlot::kExpansionLaneC,
        TwistWorkSpaceSlot::kExpansionLaneD,
        TwistWorkSpaceSlot::kExpansionLaneE,
        TwistWorkSpaceSlot::kExpansionLaneF,
        TwistWorkSpaceSlot::kWorkLaneA,
        TwistWorkSpaceSlot::kWorkLaneB,
        TwistWorkSpaceSlot::kWorkLaneC,
        TwistWorkSpaceSlot::kWorkLaneD,
        TwistWorkSpaceSlot::kWorkLaneE,
        TwistWorkSpaceSlot::kWorkLaneF,
        TwistWorkSpaceSlot::kOperationLaneA,
        TwistWorkSpaceSlot::kOperationLaneB,
        TwistWorkSpaceSlot::kOperationLaneC,
        TwistWorkSpaceSlot::kOperationLaneD,
        TwistWorkSpaceSlot::kOperationLaneE,
        TwistWorkSpaceSlot::kOperationLaneF,
        TwistWorkSpaceSlot::kSnowLaneA,
        TwistWorkSpaceSlot::kSnowLaneB,
        TwistWorkSpaceSlot::kSnowLaneC,
        TwistWorkSpaceSlot::kSnowLaneD,
        TwistWorkSpaceSlot::kMaskLaneA,
        TwistWorkSpaceSlot::kMaskLaneB,
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
        TwistWorkSpaceSlot::kMaskBoxUnrolledA,
        TwistWorkSpaceSlot::kMaskBoxUnrolledB,
        TwistWorkSpaceSlot::kMaskRowReadA,
        TwistWorkSpaceSlot::kMaskRowReadB,
        TwistWorkSpaceSlot::kMaskRowWriteA,
        TwistWorkSpaceSlot::kMaskRowWriteB,
    };

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
        case GExprType::kMix64_8: return "mix64_8";
        case GExprType::kDiffuseA64: return "diffuse_a64";
        case GExprType::kDiffuseB64: return "diffuse_b64";
        case GExprType::kDiffuseC64: return "diffuse_c64";
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
    if (pToken == "mix64_8") { *pType = GExprType::kMix64_8; return true; }
    if (pToken == "diffuse_a64") { *pType = GExprType::kDiffuseA64; return true; }
    if (pToken == "diffuse_b64") { *pType = GExprType::kDiffuseB64; return true; }
    if (pToken == "diffuse_c64") { *pType = GExprType::kDiffuseC64; return true; }
    return false;
}

std::string ReadWrapTypeToken(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kNone: return "none";
        case GReadWrapType::kBlock: return "block";
        case GReadWrapType::kSBox: return "sbox";
        case GReadWrapType::kSalt: return "salt";
        case GReadWrapType::kMaskA: return "mask_a";
        case GReadWrapType::kMaskB: return "mask_b";
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
    if ((pToken == "mask_a") || (pToken == "kMaskA")) { *pType = GReadWrapType::kMaskA; return true; }
    if ((pToken == "mask_b") || (pToken == "kMaskB")) { *pType = GReadWrapType::kMaskB; return true; }
    if ((pToken == "key_a") || (pToken == "kKeyA")) { *pType = GReadWrapType::kKeyA; return true; }
    if ((pToken == "key_b") || (pToken == "kKeyB")) { *pType = GReadWrapType::kKeyB; return true; }
    return false;
}

std::string AssignTypeToken(const GAssignType pType) {
    switch (pType) {
        case GAssignType::kSet: return "set";
        case GAssignType::kAddAssign: return "add_assign";
        case GAssignType::kXorAssign: return "xor_assign";
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

std::string Mix64Type8Token(const Mix64Type_8 pType) {
    switch (pType) {
        case Mix64Type_8::kGatePrism_8_8: return "gate_prism_8_8";
        case Mix64Type_8::kGateRoll_8_8: return "gate_roll_8_8";
        case Mix64Type_8::kGateTurn_8_8: return "gate_turn_8_8";
        case Mix64Type_8::kInv:
        default:
            return "inv";
    }
}

bool Mix64Type8FromToken(const std::string &pToken,
                         Mix64Type_8 *pType) {
    if (pType == NULL) {
        return false;
    }

    if ((pToken == "inv") || (pToken == "kInv") || (pToken == "0")) {
        *pType = Mix64Type_8::kInv;
        return true;
    }
    if ((pToken == "gate_prism_8_8") || (pToken == "kGatePrism_8_8") || (pToken == "1")) {
        *pType = Mix64Type_8::kGatePrism_8_8;
        return true;
    }
    if ((pToken == "gate_roll_8_8") || (pToken == "kGateRoll_8_8") || (pToken == "2")) {
        *pType = Mix64Type_8::kGateRoll_8_8;
        return true;
    }
    if ((pToken == "gate_turn_8_8") || (pToken == "kGateTurn_8_8") || (pToken == "3")) {
        *pType = Mix64Type_8::kGateTurn_8_8;
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

bool ExprReadsSlot(const GExpr &pExpr,
                   const TwistWorkSpaceSlot pSlot) {
    return CountExprReads(pExpr, pSlot) > 0U;
}

int CountTargetWrites(const GTarget &pTarget,
                                const TwistWorkSpaceSlot pSlot) {
    return (pTarget.IsBuf() && pTarget.mSymbol.mSlot == pSlot) ? 1U : 0U;
}

bool TargetWritesSlot(const GTarget &pTarget,
                      const TwistWorkSpaceSlot pSlot) {
    return CountTargetWrites(pTarget, pSlot) > 0U;
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
    if (IsKeyScalarName(pName)) {
        return "std::size_t";
    }
    return "std::uint64_t";
}

int NormalizeScalarValueForName(const std::string &pName,
                                const int pValue) {
    if (StartsWithText(pName, "aOracle")) {
        return pValue;
    }
    if (IsKeyScalarName(pName)) {
        return static_cast<int>(static_cast<std::uint32_t>(pValue));
    }
    return pValue;
}

bool LoopUsesSizeT(const GLoop &pLoop) {
    return (pLoop.mLoopBegin >= 0) && (pLoop.mLoopStep > 0);
}

bool IsSBoxSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kParamDomainSBoxA:
        case TwistWorkSpaceSlot::kParamDomainSBoxB:
        case TwistWorkSpaceSlot::kParamDomainSBoxC:
        case TwistWorkSpaceSlot::kParamDomainSBoxD:
        case TwistWorkSpaceSlot::kParamDomainSBoxE:
        case TwistWorkSpaceSlot::kParamDomainSBoxF:
        case TwistWorkSpaceSlot::kParamDomainSBoxG:
        case TwistWorkSpaceSlot::kParamDomainSBoxH:
            return true;
        default:
            return false;
    }
}

bool IsSaltSlot(const TwistWorkSpaceSlot pSlot) {
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
            return true;
        default:
            return false;
    }
}

std::size_t RuntimeIndexForSlot(const TwistWorkSpaceSlot pSlot,
                                const int pIndexValue) {
    if (IsSaltSlot(pSlot)) {
        return static_cast<std::size_t>(static_cast<unsigned int>(pIndexValue) &
                                        static_cast<unsigned int>(S_SALT1));
    }
    if (IsSBoxSlot(pSlot)) {
        return static_cast<std::size_t>(static_cast<unsigned int>(pIndexValue) &
                                        static_cast<unsigned int>(S_SBOX1));
    }
    return static_cast<std::size_t>(pIndexValue);
}

unsigned int ReadWrapTrimMaskForType(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kSBox: return static_cast<unsigned int>(S_SBOX1);
        case GReadWrapType::kSalt: return static_cast<unsigned int>(S_SALT1);
        default: return 0U;
    }
}

int ReadWrapLimitForType(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kBlock: return S_BLOCK;
        case GReadWrapType::kSBox: return S_SBOX;
        case GReadWrapType::kSalt: return S_SALT;
        default: return 0;
    }
}

int ResolveLengthText(const std::string &pText) {
    if (pText == "S_BLOCK") { return S_BLOCK; }
    if (pText == "S_SBOX") { return S_SBOX; }
    if (pText == "S_SALT") { return S_SALT; }
    if (pText == "W_KEY_A") { return W_KEY_A; }
    if (pText == "W_KEY_B") { return W_KEY_B; }
    if (pText == "S_KEY_A") { return S_KEY_A; }
    if (pText == "S_KEY_B") { return S_KEY_B; }
    if (pText == "W_MASK_A") { return W_MASK_A; }
    if (pText == "W_MASK_B") { return W_MASK_B; }
    if (pText == "S_MASK_A") { return S_MASK_A; }
    if (pText == "S_MASK_B") { return S_MASK_B; }

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
        *pSymbol = GSymbol::Var(aName->as_string());
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
    if (pExpr.mType == GExprType::kMix64_8) {
        aObject["mix64_type_8"] = JsonValue::String(Mix64Type8Token(pExpr.mMix64Type8));
        aObject["mix64_use_amount"] = JsonValue::Bool(pExpr.mMix64UseAmount);
        aObject["mix64_amount"] = JsonValue::String(std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)));
        aObject["mix64_sbox_a"] = SymbolToJsonValue(pExpr.mMix64SBoxA);
        aObject["mix64_sbox_b"] = SymbolToJsonValue(pExpr.mMix64SBoxB);
        aObject["mix64_sbox_c"] = SymbolToJsonValue(pExpr.mMix64SBoxC);
        aObject["mix64_sbox_d"] = SymbolToJsonValue(pExpr.mMix64SBoxD);
        aObject["mix64_sbox_e"] = SymbolToJsonValue(pExpr.mMix64SBoxE);
        aObject["mix64_sbox_f"] = SymbolToJsonValue(pExpr.mMix64SBoxF);
        aObject["mix64_sbox_g"] = SymbolToJsonValue(pExpr.mMix64SBoxG);
        aObject["mix64_sbox_h"] = SymbolToJsonValue(pExpr.mMix64SBoxH);
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
            aExpr = GExpr::Const64(aNumber);
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
        case GExprType::kDiffuseA64:
        case GExprType::kDiffuseB64:
        case GExprType::kDiffuseC64: {
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
                case GExprType::kDiffuseA64: aExpr = GExpr::DiffuseA(aInner); break;
                case GExprType::kDiffuseB64: aExpr = GExpr::DiffuseB(aInner); break;
                case GExprType::kDiffuseC64: aExpr = GExpr::DiffuseC(aInner); break;
                default: break;
            }
            break;
        }
        case GExprType::kMix64_8: {
            const JsonValue *aA = pValue.find("a");
            const JsonValue *aMixType = pValue.find("mix64_type_8");
            const JsonValue *aUseAmount = pValue.find("mix64_use_amount");
            const JsonValue *aAmount = pValue.find("mix64_amount");
            const JsonValue *aSBoxA = pValue.find("mix64_sbox_a");
            const JsonValue *aSBoxB = pValue.find("mix64_sbox_b");
            const JsonValue *aSBoxC = pValue.find("mix64_sbox_c");
            const JsonValue *aSBoxD = pValue.find("mix64_sbox_d");
            const JsonValue *aSBoxE = pValue.find("mix64_sbox_e");
            const JsonValue *aSBoxF = pValue.find("mix64_sbox_f");
            const JsonValue *aSBoxG = pValue.find("mix64_sbox_g");
            const JsonValue *aSBoxH = pValue.find("mix64_sbox_h");
            if ((aA == NULL) || (aMixType == NULL) || !aMixType->is_string() ||
                (aSBoxA == NULL) || (aSBoxB == NULL) || (aSBoxC == NULL) || (aSBoxD == NULL) ||
                (aSBoxE == NULL) || (aSBoxF == NULL) || (aSBoxG == NULL) || (aSBoxH == NULL)) {
                SetError(pError, "Mix64_8 expression was incomplete.");
                return false;
            }

            GExpr aInner;
            if (!ExprFromJsonValue(*aA, &aInner, pError)) {
                return false;
            }

            Mix64Type_8 aMixTypeParsed = Mix64Type_8::kInv;
            if (!Mix64Type8FromToken(aMixType->as_string(), &aMixTypeParsed)) {
                SetError(pError, "Mix64_8 type token was unknown.");
                return false;
            }

            GSymbol aParsedSBoxA;
            GSymbol aParsedSBoxB;
            GSymbol aParsedSBoxC;
            GSymbol aParsedSBoxD;
            GSymbol aParsedSBoxE;
            GSymbol aParsedSBoxF;
            GSymbol aParsedSBoxG;
            GSymbol aParsedSBoxH;
            if (!SymbolFromJsonValue(*aSBoxA, &aParsedSBoxA, pError) ||
                !SymbolFromJsonValue(*aSBoxB, &aParsedSBoxB, pError) ||
                !SymbolFromJsonValue(*aSBoxC, &aParsedSBoxC, pError) ||
                !SymbolFromJsonValue(*aSBoxD, &aParsedSBoxD, pError) ||
                !SymbolFromJsonValue(*aSBoxE, &aParsedSBoxE, pError) ||
                !SymbolFromJsonValue(*aSBoxF, &aParsedSBoxF, pError) ||
                !SymbolFromJsonValue(*aSBoxG, &aParsedSBoxG, pError) ||
                !SymbolFromJsonValue(*aSBoxH, &aParsedSBoxH, pError)) {
                return false;
            }

            bool aUseAmountValue = false;
            if ((aUseAmount != NULL) && aUseAmount->is_bool()) {
                aUseAmountValue = aUseAmount->as_bool();
            } else if ((aUseAmount != NULL) && aUseAmount->is_number()) {
                aUseAmountValue = aUseAmount->as_number() != 0.0;
            }

            if (aUseAmountValue) {
                std::uint64_t aAmountValue = 0U;
                if ((aAmount == NULL) || !ParseUInt64(*aAmount, &aAmountValue)) {
                    SetError(pError, "Mix64_8 amount was invalid.");
                    return false;
                }
                aExpr = GExpr::Mix64_8(aInner,
                                       aMixTypeParsed,
                                       aAmountValue,
                                       aParsedSBoxA,
                                       aParsedSBoxB,
                                       aParsedSBoxC,
                                       aParsedSBoxD,
                                       aParsedSBoxE,
                                       aParsedSBoxF,
                                       aParsedSBoxG,
                                       aParsedSBoxH);
            } else {
                aExpr = GExpr::Mix64_8(aInner,
                                       aMixTypeParsed,
                                       aParsedSBoxA,
                                       aParsedSBoxB,
                                       aParsedSBoxC,
                                       aParsedSBoxD,
                                       aParsedSBoxE,
                                       aParsedSBoxF,
                                       aParsedSBoxG,
                                       aParsedSBoxH);
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
    for (const GStatement &aStatement : pLoop.mInitializationStatements) {
        pLines->push_back(PrettyStatement(aStatement));
    }
    pLines->push_back("for (int " + pLoop.mLoopVariableName + " = " +
                      std::to_string(pLoop.mLoopBegin) + "; " +
                      pLoop.mLoopVariableName + " < " + pLoop.mLoopEndText + "; " +
                      pLoop.mLoopVariableName + " += " + std::to_string(pLoop.mLoopStep) + ") {");
    for (const GStatement &aStatement : pLoop.mBodyStatements) {
        pLines->push_back(Indent(1) + PrettyStatement(aStatement));
    }
    pLines->push_back("}");
}

bool ShouldMaskSBoxIndex(const GExpr *pIndexExpr) {
    if (pIndexExpr == nullptr) {
        return true;
    }
    if (pIndexExpr->mType != GExprType::kSymbol || !pIndexExpr->mSymbol.IsVar()) {
        return true;
    }
    const std::string &aName = pIndexExpr->mSymbol.mName;
    if (aName == "i") {
        return true;
    }
    if (aName.find("Index") != std::string::npos) {
        return true;
    }
    if (aName.find("Key") != std::string::npos) {
        return true;
    }
    if (StartsWithText(aName, "aOracle")) {
        return true;
    }
    return false;
}

std::string CppIndexForSlot(const TwistWorkSpaceSlot pSlot,
                            const GExpr *pIndexExpr,
                            const std::string &pIndexText) {
    if (IsSaltSlot(pSlot)) {
        return "(" + pIndexText + ") & S_SALT1";
    }
    if (IsSBoxSlot(pSlot)) {
        if (!ShouldMaskSBoxIndex(pIndexExpr)) {
            return pIndexText;
        }
        return "(" + pIndexText + ") & S_SBOX1";
    }

    // For block-sized buffers, preserve the two canonical direct-index forms and
    // wrap all other offsets with S_BLOCK1.
    if ((pIndexText == "aIndex") || (pIndexText == "i") ||
        (pIndexText == "S_BLOCK1 - aIndex") || (pIndexText == "S_BLOCK1 - i")) {
        return pIndexText;
    }
    return "(" + pIndexText + ") & S_BLOCK1";
}

std::string CppExpr(const GExpr &pExpr) {
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
            return std::to_string(static_cast<unsigned long long>(pExpr.mConstVal)) + "U";
        case GExprType::kRead: {
            const std::string aIndexText = (pExpr.mIndex != nullptr) ? CppExpr(*pExpr.mIndex) : std::string("0");
            return BufAliasName(pExpr.mSymbol.mSlot) + "[" +
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
        case GExprType::kDiffuseA64:
            return "TwistMix64::DiffuseA(" + CppExpr(*pExpr.mA) + ")";
        case GExprType::kDiffuseB64:
            return "TwistMix64::DiffuseB(" + CppExpr(*pExpr.mA) + ")";
        case GExprType::kDiffuseC64:
            return "TwistMix64::DiffuseC(" + CppExpr(*pExpr.mA) + ")";
        case GExprType::kMix64_8: {
            const std::string aInput = CppExpr(*pExpr.mA);
            const std::string aSBoxA = BufAliasName(pExpr.mMix64SBoxA);
            const std::string aSBoxB = BufAliasName(pExpr.mMix64SBoxB);
            const std::string aSBoxC = BufAliasName(pExpr.mMix64SBoxC);
            const std::string aSBoxD = BufAliasName(pExpr.mMix64SBoxD);
            const std::string aSBoxE = BufAliasName(pExpr.mMix64SBoxE);
            const std::string aSBoxF = BufAliasName(pExpr.mMix64SBoxF);
            const std::string aSBoxG = BufAliasName(pExpr.mMix64SBoxG);
            const std::string aSBoxH = BufAliasName(pExpr.mMix64SBoxH);
            switch (pExpr.mMix64Type8) {
                case Mix64Type_8::kGatePrism_8_8:
                    return "TwistMix64::GatePrism_8_8(" + aInput +
                           ", " + aSBoxA + ", " + aSBoxB + ", " + aSBoxC + ", " + aSBoxD +
                           ", " + aSBoxE + ", " + aSBoxF + ", " + aSBoxG + ", " + aSBoxH + ")";
                case Mix64Type_8::kGateRoll_8_8:
                    return "TwistMix64::GateRoll_8_8(" + aInput +
                           ", " + std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)) + "ULL" +
                           ", " + aSBoxA + ", " + aSBoxB + ", " + aSBoxC + ", " + aSBoxD +
                           ", " + aSBoxE + ", " + aSBoxF + ", " + aSBoxG + ", " + aSBoxH + ")";
                case Mix64Type_8::kGateTurn_8_8:
                    return "TwistMix64::GateTurn_8_8(" + aInput +
                           ", " + std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)) + "ULL" +
                           ", " + aSBoxA + ", " + aSBoxB + ", " + aSBoxC + ", " + aSBoxD +
                           ", " + aSBoxE + ", " + aSBoxF + ", " + aSBoxG + ", " + aSBoxH + ")";
                default:
                    return "0ULL";
            }
        }
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
    return BufAliasName(pTarget.mSymbol.mSlot) + "[" +
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
        default: return "S_BLOCK";
    }
}

std::string CppReadWrapTrimMaskToken(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kSBox: return "S_SBOX1";
        case GReadWrapType::kSalt: return "S_SALT1";
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
    }

    return aTargetText + " " + AssignOperatorText(pStatement.mAssignType) + " " + aExpressionText + ";";
}

std::vector<std::string> CppStatementLines(const GStatement &pStatement) {
    if (pStatement.IsRawLine()) {
        return { pStatement.mOutputPrefix + pStatement.mRawLine };
    }

    std::vector<std::string> aLines = CppReadWrapPreludeLines(pStatement);
    for (std::string &aLine : aLines) {
        aLine = pStatement.mOutputPrefix + aLine;
    }
    aLines.push_back(pStatement.mOutputPrefix + CppStatement(pStatement));
    return aLines;
}

bool EvaluateExpr(const GExpr &pExpr,
                  TwistWorkSpace *pWorkspace,
                  TwistExpander *pExpander,
                  std::unordered_map<std::string, int> *pVariables,
                  int *pValue,
                  std::string *pError) {
    if ((pVariables == NULL) || (pValue == NULL)) {
        SetError(pError, "Expression evaluation output was null.");
        return false;
    }

    switch (pExpr.mType) {
        case GExprType::kSymbol:
            if (pExpr.mSymbol.IsVar()) {
                const auto aIterator = pVariables->find(pExpr.mSymbol.mName);
                *pValue = (aIterator == pVariables->end()) ? 0ULL : aIterator->second;
                return true;
            }
            if (pExpr.mSymbol.IsBuf()) {
                if (pWorkspace == NULL) {
                    SetError(pError, "Workspace was null during buffer read.");
                    return false;
                }
                std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mSymbol.mSlot);
                if (aBuffer == NULL) {
                    SetError(pError, "Buffer symbol resolved to null.");
                    return false;
                }
                *pValue = static_cast<int>(aBuffer[0]);
                return true;
            }
            break;

        case GExprType::kConst:
            *pValue = static_cast<int>(pExpr.mConstVal);
            return true;

        case GExprType::kRead: {
            if (pWorkspace == NULL) {
                SetError(pError, "Workspace was null during read.");
                return false;
            }
            int aIndexValue = 0ULL;
            if (pExpr.mReadWrapType != GReadWrapType::kNone) {
                int aBaseIndexValue = 0;
                if (pExpr.mReadWrapIndexSymbol.IsVar()) {
                    const auto aBaseIterator = pVariables->find(pExpr.mReadWrapIndexSymbol.mName);
                    aBaseIndexValue = (aBaseIterator == pVariables->end()) ? 0 : aBaseIterator->second;
                } else if (pExpr.mReadWrapIndexSymbol.IsBuf()) {
                    std::uint8_t *aBaseBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mReadWrapIndexSymbol.mSlot);
                    if (aBaseBuffer == NULL) {
                        SetError(pError, "Read wrap index buffer was null.");
                        return false;
                    }
                    aBaseIndexValue = static_cast<int>(aBaseBuffer[0]);
                } else {
                    SetError(pError, "Read wrap index symbol was invalid.");
                    return false;
                }

                int aOracleValue = aBaseIndexValue;
                const int aWrapLimit = ReadWrapLimitForType(pExpr.mReadWrapType);
                if ((aWrapLimit > 0) && (aOracleValue >= aWrapLimit)) {
                    aOracleValue -= aWrapLimit;
                }
                const unsigned int aWrapTrimMask = ReadWrapTrimMaskForType(pExpr.mReadWrapType);
                if (aWrapTrimMask != 0U) {
                    aOracleValue = static_cast<int>(static_cast<unsigned int>(aOracleValue) & aWrapTrimMask);
                }
                aIndexValue = aOracleValue;

                if (pExpr.mReadWrapOracleSymbol.IsVar()) {
                    (*pVariables)[pExpr.mReadWrapOracleSymbol.mName] = aOracleValue;
                }
            } else {
                if ((pExpr.mIndex == NULL) ||
                    !EvaluateExpr(*pExpr.mIndex, pWorkspace, pExpander, pVariables, &aIndexValue, pError)) {
                    SetError(pError, "Read expression index was invalid.");
                    return false;
                }
            }
            std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mSymbol.mSlot);
            if (aBuffer == NULL) {
                SetError(pError, "Read expression buffer was null.");
                return false;
            }
            const std::size_t aIndex = RuntimeIndexForSlot(pExpr.mSymbol.mSlot, aIndexValue);
            *pValue = static_cast<int>(aBuffer[aIndex]);
            return true;
        }

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kRotL8: {
            int aLeft = 0ULL;
            int aRight = 0ULL;
            if ((pExpr.mA == NULL) || (pExpr.mB == NULL) ||
                !EvaluateExpr(*pExpr.mA, pWorkspace, pExpander, pVariables, &aLeft, pError) ||
                !EvaluateExpr(*pExpr.mB, pWorkspace, pExpander, pVariables, &aRight, pError)) {
                SetError(pError, "Binary expression child was invalid.");
                return false;
            }
            switch (pExpr.mType) {
                case GExprType::kAdd: *pValue = aLeft + aRight; return true;
                case GExprType::kSub: *pValue = aLeft - aRight; return true;
                case GExprType::kMul: *pValue = aLeft * aRight; return true;
                case GExprType::kXor: *pValue = aLeft ^ aRight; return true;
                case GExprType::kAnd: *pValue = aLeft & aRight; return true;
                case GExprType::kRotL8: *pValue = RotL8(aLeft, aRight); return true;
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
                      TwistWorkSpace *pWorkspace,
                      TwistExpander *pExpander,
                      std::unordered_map<std::string, int> *pVariables,
                      std::string *pError) {
    if (pStatement.IsRawLine()) {
        return true;
    }

    int aExpressionValue = 0ULL;
    if (!EvaluateExpr(pStatement.mExpression, pWorkspace, pExpander, pVariables, &aExpressionValue, pError)) {
        return false;
    }

    if (pStatement.mTarget.IsVar()) {
        int &aTargetValue = (*pVariables)[pStatement.mTarget.mSymbol.mName];
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
            default:
                SetError(pError, "Variable assignment type was invalid.");
                return false;
        }
    }

    if (pStatement.mTarget.IsBuf()) {
        if (pWorkspace == NULL) {
            SetError(pError, "Workspace was null during write.");
            return false;
        }
        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pStatement.mTarget.mSymbol.mSlot);
        if (aBuffer == NULL) {
            SetError(pError, "Write buffer was null.");
            return false;
        }
        int aIndexValue = 0ULL;
        if (pStatement.mTarget.mIndex != nullptr &&
            !EvaluateExpr(*pStatement.mTarget.mIndex, pWorkspace, pExpander, pVariables, &aIndexValue, pError)) {
            return false;
        }

        const std::size_t aIndex = RuntimeIndexForSlot(pStatement.mTarget.mSymbol.mSlot, aIndexValue);

        switch (pStatement.mAssignType) {
            case GAssignType::kSet:
                aBuffer[aIndex] = static_cast<std::uint8_t>(aExpressionValue);
                return true;
            case GAssignType::kAddAssign:
                aBuffer[aIndex] = static_cast<std::uint8_t>(static_cast<int>(aBuffer[aIndex]) + aExpressionValue);
                return true;
            case GAssignType::kXorAssign:
                aBuffer[aIndex] = static_cast<std::uint8_t>(static_cast<int>(aBuffer[aIndex]) ^ aExpressionValue);
                return true;
            default:
                SetError(pError, "Buffer assignment type was invalid.");
                return false;
        }
    }

    SetError(pError, "Statement target was invalid.");
    return false;
}

} // namespace

GTarget::GTarget() {
    Invalidate();
}

void GScopeRules::SetReadPreferredMinimum(GSymbol pSymbol, int pCount) {
    if (!pSymbol.IsInvalid()) {
        mReadPreferredMinimum[ScopeSymbolKey(pSymbol)] = pCount;
    }
}

void GScopeRules::SetReadPreferredMaximum(GSymbol pSymbol, int pCount) {
    if (!pSymbol.IsInvalid()) {
        mReadPreferredMaximum[ScopeSymbolKey(pSymbol)] = pCount;
    }
}

int GScopeRules::GetReadPreferredMinimum(GSymbol pSymbol) const {
    const auto aIterator = mReadPreferredMinimum.find(ScopeSymbolKey(pSymbol));
    return (aIterator == mReadPreferredMinimum.end()) ? 0 : aIterator->second;
}

int GScopeRules::GetReadPreferredMaximum(GSymbol pSymbol) const {
    const auto aIterator = mReadPreferredMaximum.find(ScopeSymbolKey(pSymbol));
    return (aIterator == mReadPreferredMaximum.end()) ? 0 : aIterator->second;
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
}

void GBatch::CommitLoop(const GLoop &pLoop) {
    mLoops.push_back(pLoop);
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
    GLoop aLoop;
    for (const GStatement &aStatement : *pStatements) {
        aLoop.AddBody(aStatement);
    }
    CommitLoop(aLoop);
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

bool GBatch::IsInvalid() const {
    if (mLoops.empty()) {
        return true;
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
    for (const GLoop &aLoop : mLoops) {
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            aCount += CountExprReads(aStatement.mExpression, pSlot);
            if (aStatement.mTarget.mIndex != nullptr) {
                aCount += CountExprReads(*aStatement.mTarget.mIndex, pSlot);
            }
        }
        for (const GStatement &aStatement : aLoop.mBodyStatements) {
            aCount += CountExprReads(aStatement.mExpression, pSlot);
            if (aStatement.mTarget.mIndex != nullptr) {
                aCount += CountExprReads(*aStatement.mTarget.mIndex, pSlot);
            }
        }
    }
    return aCount;
}

int GBatch::CountWrites(TwistWorkSpaceSlot pSlot) const {
    int aCount = 0U;
    for (const GLoop &aLoop : mLoops) {
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            aCount += CountTargetWrites(aStatement.mTarget, pSlot);
        }
        for (const GStatement &aStatement : aLoop.mBodyStatements) {
            aCount += CountTargetWrites(aStatement.mTarget, pSlot);
        }
    }
    return aCount;
}

int GBatch::CountLoopsReading(TwistWorkSpaceSlot pSlot) const {
    int aCount = 0U;
    for (const GLoop &aLoop : mLoops) {
        bool aReads = false;
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            if (ExprReadsSlot(aStatement.mExpression, pSlot) ||
                ((aStatement.mTarget.mIndex != nullptr) && ExprReadsSlot(*aStatement.mTarget.mIndex, pSlot))) {
                aReads = true;
                break;
            }
        }
        if (!aReads) {
            for (const GStatement &aStatement : aLoop.mBodyStatements) {
                if (ExprReadsSlot(aStatement.mExpression, pSlot) ||
                    ((aStatement.mTarget.mIndex != nullptr) && ExprReadsSlot(*aStatement.mTarget.mIndex, pSlot))) {
                    aReads = true;
                    break;
                }
            }
        }
        if (aReads) {
            ++aCount;
        }
    }
    return aCount;
}

int GBatch::CountLoopsWriting(TwistWorkSpaceSlot pSlot) const {
    int aCount = 0U;
    for (const GLoop &aLoop : mLoops) {
        bool aWrites = false;
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            if (TargetWritesSlot(aStatement.mTarget, pSlot)) {
                aWrites = true;
                break;
            }
        }
        if (!aWrites) {
            for (const GStatement &aStatement : aLoop.mBodyStatements) {
                if (TargetWritesSlot(aStatement.mTarget, pSlot)) {
                    aWrites = true;
                    break;
                }
            }
        }
        if (aWrites) {
            ++aCount;
        }
    }
    return aCount;
}

std::vector<std::string> GBatch::CollectVariableNames() const {
    std::vector<std::string> aNames;
    for (const GLoop &aLoop : mLoops) {
        AppendUniqueVariableName(&aNames, aLoop.mLoopVariableName);
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            if (aStatement.mTarget.IsVar()) {
                AppendUniqueVariableName(&aNames, aStatement.mTarget.mSymbol.mName);
            }
            if (aStatement.mTarget.mIndex != nullptr) {
                CollectVariablesFromExpr(*aStatement.mTarget.mIndex, &aNames);
            }
            CollectVariablesFromExpr(aStatement.mExpression, &aNames);
        }
        for (const GStatement &aStatement : aLoop.mBodyStatements) {
            if (aStatement.mTarget.IsVar()) {
                AppendUniqueVariableName(&aNames, aStatement.mTarget.mSymbol.mName);
            }
            if (aStatement.mTarget.mIndex != nullptr) {
                CollectVariablesFromExpr(*aStatement.mTarget.mIndex, &aNames);
            }
            CollectVariablesFromExpr(aStatement.mExpression, &aNames);
        }
    }
    return aNames;
}

std::vector<TwistWorkSpaceSlot> GBatch::CollectReferencedSlots() const {
    std::vector<TwistWorkSpaceSlot> aSlots;
    for (const GLoop &aLoop : mLoops) {
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            if (aStatement.mTarget.IsBuf()) {
                AppendUnique(&aSlots, aStatement.mTarget.mSymbol.mSlot);
            }
            if (aStatement.mTarget.mIndex != nullptr) {
                CollectSlotsFromExpr(*aStatement.mTarget.mIndex, &aSlots);
            }
            CollectSlotsFromExpr(aStatement.mExpression, &aSlots);
        }
        for (const GStatement &aStatement : aLoop.mBodyStatements) {
            if (aStatement.mTarget.IsBuf()) {
                AppendUnique(&aSlots, aStatement.mTarget.mSymbol.mSlot);
            }
            if (aStatement.mTarget.mIndex != nullptr) {
                CollectSlotsFromExpr(*aStatement.mTarget.mIndex, &aSlots);
            }
            CollectSlotsFromExpr(aStatement.mExpression, &aSlots);
        }
    }
    return aSlots;
}

std::string GBatch::ToPrettyString() const {
    std::vector<std::string> aLines;
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
    const JsonValue *aLoops = aRoot->find("loops");
    if ((aName == NULL) || !aName->is_string() ||
        (aLoops == NULL) || !aLoops->is_array()) {
        SetError(pError, "Batch JSON was incomplete.");
        return false;
    }

    GBatch aBatch;
    aBatch.mName = aName->as_string();
    for (const JsonValue &aLoopValue : aLoops->as_array()) {
        GLoop aLoop;
        if (!LoopFromJsonValue(aLoopValue, &aLoop, pError)) {
            return false;
        }
        aBatch.mLoops.push_back(aLoop);
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
    aLines.push_back("static void " + pFunctionName + "(TwistWorkSpace *pWorkspace) {");

    std::vector<std::string> aLoopVariables;
    for (const GLoop &aLoop : mLoops) {
        AppendUnique(&aLoopVariables, aLoop.mLoopVariableName);
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

    if (pEmitDeclarations) {
        std::vector<TwistWorkSpaceSlot> aSlots = CollectReferencedSlots();
        for (TwistWorkSpaceSlot aSlot : aSlots) {
            aLines.push_back(Indent(1) + "std::uint8_t *" + BufAliasName(aSlot) +
                             " = TwistWorkSpace::GetBuffer(pWorkspace, static_cast<TwistWorkSpaceSlot>(" +
                             std::to_string(static_cast<int>(aSlot)) + "));");
        }

        if (!aSlots.empty() && !aScalarVariables.empty()) {
            aLines.push_back("");
        }

        for (const std::string &aVariable : aScalarVariables) {
            aLines.push_back(Indent(1) + ScalarCppTypeForName(aVariable) + " " + aVariable + " = 0;");
        }
    }

    for (std::size_t aLoopIndex = 0U; aLoopIndex < mLoops.size(); ++aLoopIndex) {
        const GLoop &aLoop = mLoops[aLoopIndex];
        if (pEmitDeclarations || (aLoopIndex > 0U)) {
            aLines.push_back("");
        }
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            const std::vector<std::string> aStatementLines = CppStatementLines(aStatement);
            for (const std::string &aStatementLine : aStatementLines) {
                aLines.push_back(Indent(1) + aStatementLine);
            }
        }
        if (LoopUsesSizeT(aLoop)) {
            aLines.push_back(Indent(1) + "for (std::size_t " + aLoop.mLoopVariableName + " = " +
                             std::to_string(aLoop.mLoopBegin) + "U; " +
                             aLoop.mLoopVariableName + " < static_cast<std::size_t>(" + aLoop.mLoopEndText + "); " +
                             aLoop.mLoopVariableName + " += " + std::to_string(aLoop.mLoopStep) + "U) {");
        } else {
            aLines.push_back(Indent(1) + "for (int " + aLoop.mLoopVariableName + " = " +
                             std::to_string(aLoop.mLoopBegin) + "; " +
                             aLoop.mLoopVariableName + " < " + aLoop.mLoopEndText + "; " +
                             aLoop.mLoopVariableName + " += " + std::to_string(aLoop.mLoopStep) + ") {");
        }
        for (const GStatement &aStatement : aLoop.mBodyStatements) {
            const std::vector<std::string> aStatementLines = CppStatementLines(aStatement);
            for (const std::string &aStatementLine : aStatementLines) {
                aLines.push_back(Indent(2) + aStatementLine);
            }
        }
        aLines.push_back(Indent(1) + "}");
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
    aStream << "{\n";
    if (!aBody.empty()) {
        std::istringstream aBodyStream(aBody);
        std::string aLine;
        bool aIsFirstLine = true;
        while (std::getline(aBodyStream, aLine)) {
            if (!aIsFirstLine) {
                aStream << '\n';
            }
            aIsFirstLine = false;
            aStream << "    " << aLine;
        }
        aStream << '\n';
    }
    aStream << "}";
    return aStream.str();
}

bool GBatch::Execute(TwistWorkSpace *pWorkspace,
                     TwistExpander *pExpander,
                     std::string *pError) const {
    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    return ExecuteWithVariables(pWorkspace, pExpander, &aVariables, pError);
}

bool GBatch::ExecuteWithVariables(TwistWorkSpace *pWorkspace,
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

    std::unordered_map<std::string, int> aLocalVariables;
    for (const auto &aPair : *pVariables) {
        aLocalVariables[aPair.first] = static_cast<int>(aPair.second);
    }

    for (const std::string &aName : CollectVariableNames()) {
        if (aLocalVariables.find(aName) == aLocalVariables.end()) {
            aLocalVariables[aName] = 0;
        }
    }

    for (const GLoop &aLoop : mLoops) {
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            if (!ExecuteStatement(aStatement, pWorkspace, pExpander, &aLocalVariables, pError)) {
                return false;
            }
        }

        const int aLoopEnd = ResolveLengthText(aLoop.mLoopEndText);
        for (int aLoopValue = aLoop.mLoopBegin;
             (aLoop.mLoopStep > 0) ? (aLoopValue < aLoopEnd) : (aLoopValue > aLoopEnd);
             aLoopValue += aLoop.mLoopStep) {
            aLocalVariables[aLoop.mLoopVariableName] = static_cast<int>(aLoopValue);
            for (const GStatement &aStatement : aLoop.mBodyStatements) {
                if (!ExecuteStatement(aStatement, pWorkspace, pExpander, &aLocalVariables, pError)) {
                    return false;
                }
            }
        }
    }

    for (const auto &aPair : aLocalVariables) {
        (*pVariables)[aPair.first] = static_cast<GRuntimeScalar>(aPair.second);
    }

    return true;
}
