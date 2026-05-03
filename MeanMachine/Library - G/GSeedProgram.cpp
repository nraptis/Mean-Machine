//
//  GSeedProgram.cpp
//  MeanMachine
//

#include "GSeedProgram.hpp"

#include "GJson.hpp"
#include "TwistExpander.hpp"
#include "TwistFastMatrix.hpp"
#include "TwistFunctional.hpp"
#include "TwistMasking.hpp"
#include "TwistMix64.hpp"
#include "TwistSnow.hpp"
#include "TwistMemory.hpp"

#include <algorithm>
#include <cctype>
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

std::string ScopeExprKey(const GExpr &pExpr) {
    return "expr:" + GExprKey(pExpr);
}

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != NULL) {
        *pErrorMessage = pMessage;
    }
}

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

bool IsIdentifierChar(const char pChar) {
    return (std::isalnum(static_cast<unsigned char>(pChar)) != 0) || (pChar == '_');
}

bool ContainsIdentifierToken(const std::string &pText,
                             const std::string &pToken) {
    if (pToken.empty()) {
        return false;
    }

    std::size_t aSearchPos = 0U;
    while (true) {
        const std::size_t aMatchPos = pText.find(pToken, aSearchPos);
        if (aMatchPos == std::string::npos) {
            return false;
        }

        const bool aLeftOk = (aMatchPos == 0U) || !IsIdentifierChar(pText[aMatchPos - 1U]);
        const std::size_t aAfterPos = aMatchPos + pToken.size();
        const bool aRightOk = (aAfterPos >= pText.size()) || !IsIdentifierChar(pText[aAfterPos]);
        if (aLeftOk && aRightOk) {
            return true;
        }
        aSearchPos = aMatchPos + 1U;
    }
}

const std::vector<TwistWorkSpaceSlot> &WorkspaceAliasSlotsForRawLine() {
    static const std::vector<TwistWorkSpaceSlot> kSlots = {
        TwistWorkSpaceSlot::kSource,
        TwistWorkSpaceSlot::kDest,
        TwistWorkSpaceSlot::kSaltA,
        TwistWorkSpaceSlot::kSaltB,
        TwistWorkSpaceSlot::kSaltC,
        TwistWorkSpaceSlot::kSaltD,
        TwistWorkSpaceSlot::kScratchSaltA,
        TwistWorkSpaceSlot::kScratchSaltB,
        TwistWorkSpaceSlot::kScratchSaltC,
        TwistWorkSpaceSlot::kScratchSaltD,
        TwistWorkSpaceSlot::kDerivedSaltA,
        TwistWorkSpaceSlot::kDerivedSaltB,
        TwistWorkSpaceSlot::kDerivedSaltC,
        TwistWorkSpaceSlot::kDerivedSaltD,
        TwistWorkSpaceSlot::kDerivedSaltE,
        TwistWorkSpaceSlot::kDerivedSaltF,
        TwistWorkSpaceSlot::kDerivedSaltG,
        TwistWorkSpaceSlot::kDerivedSaltH,
        TwistWorkSpaceSlot::kSBoxA,
        TwistWorkSpaceSlot::kSBoxB,
        TwistWorkSpaceSlot::kSBoxC,
        TwistWorkSpaceSlot::kSBoxD,
        TwistWorkSpaceSlot::kDerivedSBoxA,
        TwistWorkSpaceSlot::kDerivedSBoxB,
        TwistWorkSpaceSlot::kDerivedSBoxC,
        TwistWorkSpaceSlot::kDerivedSBoxD,
        TwistWorkSpaceSlot::kDerivedSBoxE,
        TwistWorkSpaceSlot::kDerivedSBoxF,
        TwistWorkSpaceSlot::kDerivedSBoxG,
        TwistWorkSpaceSlot::kDerivedSBoxH,
        TwistWorkSpaceSlot::kSeedExpansionLaneA,
        TwistWorkSpaceSlot::kSeedExpansionLaneB,
        TwistWorkSpaceSlot::kSeedExpansionLaneC,
        TwistWorkSpaceSlot::kSeedExpansionLaneD,
        TwistWorkSpaceSlot::kWorkLaneA,
        TwistWorkSpaceSlot::kWorkLaneB,
        TwistWorkSpaceSlot::kWorkLaneC,
        TwistWorkSpaceSlot::kWorkLaneD,
        TwistWorkSpaceSlot::kOperationLaneA,
        TwistWorkSpaceSlot::kOperationLaneB,
        TwistWorkSpaceSlot::kMaskLaneA,
        TwistWorkSpaceSlot::kMaskLaneB,
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
        TwistWorkSpaceSlot::kMaskRowWriteB
    };
    return kSlots;
}

void CollectSlotsFromRawLine(const std::string &pRawLine,
                             std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pSlots == nullptr) {
        return;
    }

    for (const TwistWorkSpaceSlot aSlot : WorkspaceAliasSlotsForRawLine()) {
        const std::string aAlias = BufAliasName(aSlot);
        if (!aAlias.empty() && (aAlias != "invalid") && ContainsIdentifierToken(pRawLine, aAlias)) {
            AppendUnique(pSlots, aSlot);
        }
    }
}

std::string SlotToken(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return "source";
        case TwistWorkSpaceSlot::kDest: return "dest";
        case TwistWorkSpaceSlot::kSaltA: return "salt_a";
        case TwistWorkSpaceSlot::kSaltB: return "salt_b";
        case TwistWorkSpaceSlot::kSaltC: return "salt_c";
        case TwistWorkSpaceSlot::kSaltD: return "salt_d";
        case TwistWorkSpaceSlot::kScratchSaltA: return "scratch_salt_a";
        case TwistWorkSpaceSlot::kScratchSaltB: return "scratch_salt_b";
        case TwistWorkSpaceSlot::kScratchSaltC: return "scratch_salt_c";
        case TwistWorkSpaceSlot::kScratchSaltD: return "scratch_salt_d";
        case TwistWorkSpaceSlot::kDerivedSaltA: return "derived_salt_a";
        case TwistWorkSpaceSlot::kDerivedSaltB: return "derived_salt_b";
        case TwistWorkSpaceSlot::kDerivedSaltC: return "derived_salt_c";
        case TwistWorkSpaceSlot::kDerivedSaltD: return "derived_salt_d";
        case TwistWorkSpaceSlot::kDerivedSaltE: return "derived_salt_e";
        case TwistWorkSpaceSlot::kDerivedSaltF: return "derived_salt_f";
        case TwistWorkSpaceSlot::kDerivedSaltG: return "derived_salt_g";
        case TwistWorkSpaceSlot::kDerivedSaltH: return "derived_salt_h";
        case TwistWorkSpaceSlot::kSBoxA: return "sbox_a";
        case TwistWorkSpaceSlot::kSBoxB: return "sbox_b";
        case TwistWorkSpaceSlot::kSBoxC: return "sbox_c";
        case TwistWorkSpaceSlot::kSBoxD: return "sbox_d";
        case TwistWorkSpaceSlot::kDerivedSBoxA: return "derived_sbox_a";
        case TwistWorkSpaceSlot::kDerivedSBoxB: return "derived_sbox_b";
        case TwistWorkSpaceSlot::kDerivedSBoxC: return "derived_sbox_c";
        case TwistWorkSpaceSlot::kDerivedSBoxD: return "derived_sbox_d";
        case TwistWorkSpaceSlot::kDerivedSBoxE: return "derived_sbox_e";
        case TwistWorkSpaceSlot::kDerivedSBoxF: return "derived_sbox_f";
        case TwistWorkSpaceSlot::kDerivedSBoxG: return "derived_sbox_g";
        case TwistWorkSpaceSlot::kDerivedSBoxH: return "derived_sbox_h";
        case TwistWorkSpaceSlot::kSeedExpansionLaneA: return "seed_lane_a";
        case TwistWorkSpaceSlot::kSeedExpansionLaneB: return "seed_lane_b";
        case TwistWorkSpaceSlot::kSeedExpansionLaneC: return "seed_lane_c";
        case TwistWorkSpaceSlot::kSeedExpansionLaneD: return "seed_lane_d";
        case TwistWorkSpaceSlot::kWorkLaneA: return "work_lane_a";
        case TwistWorkSpaceSlot::kWorkLaneB: return "work_lane_b";
        case TwistWorkSpaceSlot::kWorkLaneC: return "work_lane_c";
        case TwistWorkSpaceSlot::kWorkLaneD: return "work_lane_d";
        case TwistWorkSpaceSlot::kOperationLaneA: return "operation_lane_a";
        case TwistWorkSpaceSlot::kOperationLaneB: return "operation_lane_b";
        case TwistWorkSpaceSlot::kMaskLaneA: return "mask_lane_a";
        case TwistWorkSpaceSlot::kMaskLaneB: return "mask_lane_b";
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
        default: return "invalid";
    }
}

[[maybe_unused]] std::string SlotEnumName(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource: return "kSource";
        case TwistWorkSpaceSlot::kDest: return "kDest";
        case TwistWorkSpaceSlot::kSaltA: return "kSaltA";
        case TwistWorkSpaceSlot::kSaltB: return "kSaltB";
        case TwistWorkSpaceSlot::kSaltC: return "kSaltC";
        case TwistWorkSpaceSlot::kSaltD: return "kSaltD";
        case TwistWorkSpaceSlot::kScratchSaltA: return "kScratchSaltA";
        case TwistWorkSpaceSlot::kScratchSaltB: return "kScratchSaltB";
        case TwistWorkSpaceSlot::kScratchSaltC: return "kScratchSaltC";
        case TwistWorkSpaceSlot::kScratchSaltD: return "kScratchSaltD";
        case TwistWorkSpaceSlot::kDerivedSaltA: return "kDerivedSaltA";
        case TwistWorkSpaceSlot::kDerivedSaltB: return "kDerivedSaltB";
        case TwistWorkSpaceSlot::kDerivedSaltC: return "kDerivedSaltC";
        case TwistWorkSpaceSlot::kDerivedSaltD: return "kDerivedSaltD";
        case TwistWorkSpaceSlot::kDerivedSaltE: return "kDerivedSaltE";
        case TwistWorkSpaceSlot::kDerivedSaltF: return "kDerivedSaltF";
        case TwistWorkSpaceSlot::kDerivedSaltG: return "kDerivedSaltG";
        case TwistWorkSpaceSlot::kDerivedSaltH: return "kDerivedSaltH";
        case TwistWorkSpaceSlot::kSBoxA: return "kSBoxA";
        case TwistWorkSpaceSlot::kSBoxB: return "kSBoxB";
        case TwistWorkSpaceSlot::kSBoxC: return "kSBoxC";
        case TwistWorkSpaceSlot::kSBoxD: return "kSBoxD";
        case TwistWorkSpaceSlot::kDerivedSBoxA: return "kDerivedSBoxA";
        case TwistWorkSpaceSlot::kDerivedSBoxB: return "kDerivedSBoxB";
        case TwistWorkSpaceSlot::kDerivedSBoxC: return "kDerivedSBoxC";
        case TwistWorkSpaceSlot::kDerivedSBoxD: return "kDerivedSBoxD";
        case TwistWorkSpaceSlot::kDerivedSBoxE: return "kDerivedSBoxE";
        case TwistWorkSpaceSlot::kDerivedSBoxF: return "kDerivedSBoxF";
        case TwistWorkSpaceSlot::kDerivedSBoxG: return "kDerivedSBoxG";
        case TwistWorkSpaceSlot::kDerivedSBoxH: return "kDerivedSBoxH";
        case TwistWorkSpaceSlot::kSeedExpansionLaneA: return "kSeedExpansionLaneA";
        case TwistWorkSpaceSlot::kSeedExpansionLaneB: return "kSeedExpansionLaneB";
        case TwistWorkSpaceSlot::kSeedExpansionLaneC: return "kSeedExpansionLaneC";
        case TwistWorkSpaceSlot::kSeedExpansionLaneD: return "kSeedExpansionLaneD";
        case TwistWorkSpaceSlot::kWorkLaneA: return "kWorkLaneA";
        case TwistWorkSpaceSlot::kWorkLaneB: return "kWorkLaneB";
        case TwistWorkSpaceSlot::kWorkLaneC: return "kWorkLaneC";
        case TwistWorkSpaceSlot::kWorkLaneD: return "kWorkLaneD";
        case TwistWorkSpaceSlot::kOperationLaneA: return "kOperationLaneA";
        case TwistWorkSpaceSlot::kOperationLaneB: return "kOperationLaneB";
        case TwistWorkSpaceSlot::kMaskLaneA: return "kMaskLaneA";
        case TwistWorkSpaceSlot::kMaskLaneB: return "kMaskLaneB";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return "kKeyBoxUnrolledA";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return "kKeyBoxUnrolledB";
        case TwistWorkSpaceSlot::kKeyRowReadA: return "kKeyRowReadA";
        case TwistWorkSpaceSlot::kKeyRowReadB: return "kKeyRowReadB";
        case TwistWorkSpaceSlot::kKeyRowWriteA: return "kKeyRowWriteA";
        case TwistWorkSpaceSlot::kKeyRowWriteB: return "kKeyRowWriteB";
        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return "kMaskBoxUnrolledA";
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return "kMaskBoxUnrolledB";
        case TwistWorkSpaceSlot::kMaskRowReadA: return "kMaskRowReadA";
        case TwistWorkSpaceSlot::kMaskRowReadB: return "kMaskRowReadB";
        case TwistWorkSpaceSlot::kMaskRowWriteA: return "kMaskRowWriteA";
        case TwistWorkSpaceSlot::kMaskRowWriteB: return "kMaskRowWriteB";
        default: return "kInvalid";
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
        TwistWorkSpaceSlot::kSaltA,
        TwistWorkSpaceSlot::kSaltB,
        TwistWorkSpaceSlot::kSaltC,
        TwistWorkSpaceSlot::kSaltD,
        TwistWorkSpaceSlot::kScratchSaltA,
        TwistWorkSpaceSlot::kScratchSaltB,
        TwistWorkSpaceSlot::kScratchSaltC,
        TwistWorkSpaceSlot::kScratchSaltD,
        TwistWorkSpaceSlot::kDerivedSaltA,
        TwistWorkSpaceSlot::kDerivedSaltB,
        TwistWorkSpaceSlot::kDerivedSaltC,
        TwistWorkSpaceSlot::kDerivedSaltD,
        TwistWorkSpaceSlot::kDerivedSaltE,
        TwistWorkSpaceSlot::kDerivedSaltF,
        TwistWorkSpaceSlot::kDerivedSaltG,
        TwistWorkSpaceSlot::kDerivedSaltH,
        TwistWorkSpaceSlot::kSBoxA,
        TwistWorkSpaceSlot::kSBoxB,
        TwistWorkSpaceSlot::kSBoxC,
        TwistWorkSpaceSlot::kSBoxD,
        TwistWorkSpaceSlot::kDerivedSBoxA,
        TwistWorkSpaceSlot::kDerivedSBoxB,
        TwistWorkSpaceSlot::kDerivedSBoxC,
        TwistWorkSpaceSlot::kDerivedSBoxD,
        TwistWorkSpaceSlot::kDerivedSBoxE,
        TwistWorkSpaceSlot::kDerivedSBoxF,
        TwistWorkSpaceSlot::kDerivedSBoxG,
        TwistWorkSpaceSlot::kDerivedSBoxH,
        TwistWorkSpaceSlot::kSeedExpansionLaneA,
        TwistWorkSpaceSlot::kSeedExpansionLaneB,
        TwistWorkSpaceSlot::kSeedExpansionLaneC,
        TwistWorkSpaceSlot::kSeedExpansionLaneD,
        TwistWorkSpaceSlot::kWorkLaneA,
        TwistWorkSpaceSlot::kWorkLaneB,
        TwistWorkSpaceSlot::kWorkLaneC,
        TwistWorkSpaceSlot::kWorkLaneD,
        TwistWorkSpaceSlot::kOperationLaneA,
        TwistWorkSpaceSlot::kOperationLaneB,
        TwistWorkSpaceSlot::kMaskLaneA,
        TwistWorkSpaceSlot::kMaskLaneB,
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
    return false;
}

std::string ExprTypeToken(const GExprType pType) {
    switch (pType) {
        case GExprType::kSymbol: return "symbol";
        case GExprType::kConst: return "const";
        case GExprType::kRead: return "read";
        case GExprType::kAdd: return "add";
        case GExprType::kSub: return "sub";
        case GExprType::kMul: return "mul";
        case GExprType::kXor: return "xor";
        case GExprType::kAnd: return "and";
        case GExprType::kRotL8: return "rotl8";
        case GExprType::kRotL32: return "rotl32";
        case GExprType::kShiftL: return "shiftl";
        case GExprType::kShiftR: return "shiftr";
        case GExprType::kOr: return "or";
        case GExprType::kMix64_1: return "mix64_1";
        case GExprType::kMix64_4: return "mix64_4";
        case GExprType::kMix64_8: return "mix64_8";
        case GExprType::kRotL64: return "rotl64";
        case GExprType::kDiffuse64: return "diffuse64";
        default: return "invalid";
    }
}

bool ExprTypeFromToken(const std::string &pToken,
                       GExprType *pType) {
    if (pType == NULL) {
        return false;
    }
    if (pToken == "symbol") { *pType = GExprType::kSymbol; return true; }
    if (pToken == "const") { *pType = GExprType::kConst; return true; }
    if (pToken == "read") { *pType = GExprType::kRead; return true; }
    if (pToken == "add") { *pType = GExprType::kAdd; return true; }
    if (pToken == "sub") { *pType = GExprType::kSub; return true; }
    if (pToken == "mul") { *pType = GExprType::kMul; return true; }
    if (pToken == "xor") { *pType = GExprType::kXor; return true; }
    if (pToken == "and") { *pType = GExprType::kAnd; return true; }
    if (pToken == "rotl8") { *pType = GExprType::kRotL8; return true; }
    if (pToken == "rotl32") { *pType = GExprType::kRotL32; return true; }
    if (pToken == "shiftl") { *pType = GExprType::kShiftL; return true; }
    if (pToken == "shiftr") { *pType = GExprType::kShiftR; return true; }
    if (pToken == "or") { *pType = GExprType::kOr; return true; }
    if (pToken == "mix64_1") { *pType = GExprType::kMix64_1; return true; }
    if (pToken == "mix64_4") { *pType = GExprType::kMix64_4; return true; }
    if (pToken == "mix64_8") { *pType = GExprType::kMix64_8; return true; }
    if (pToken == "rotl64") { *pType = GExprType::kRotL64; return true; }
    if (pToken == "diffuse64") { *pType = GExprType::kDiffuse64; return true; }
    return false;
}

std::string ReadWrapTypeToken(const GReadWrapType pType) {
    switch (pType) {
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
    if (pToken == "none") { *pType = GReadWrapType::kNone; return true; }
    if (pToken == "block") { *pType = GReadWrapType::kBlock; return true; }
    if (pToken == "sbox") { *pType = GReadWrapType::kSBox; return true; }
    if (pToken == "salt") { *pType = GReadWrapType::kSalt; return true; }
    if (pToken == "mask_a") { *pType = GReadWrapType::kMaskA; return true; }
    if (pToken == "mask_b") { *pType = GReadWrapType::kMaskB; return true; }
    if (pToken == "key_a") { *pType = GReadWrapType::kKeyA; return true; }
    if (pToken == "key_b") { *pType = GReadWrapType::kKeyB; return true; }
    return false;
}

std::string AssignTypeToken(const GAssignType pType) {
    switch (pType) {
        case GAssignType::kSet: return "set";
        default: return "invalid";
    }
}

bool AssignTypeFromToken(const std::string &pToken,
                         GAssignType *pType) {
    if (pType == NULL) {
        return false;
    }
    if (pToken == "set") { *pType = GAssignType::kSet; return true; }
    return false;
}

std::string Mix64Type1Token(const Mix64Type_1 pType) {
    switch (pType) {
        case Mix64Type_1::kGatePrism_1_8: return "kGatePrism_1_8";
        case Mix64Type_1::kGateRoll_1_1: return "kGateRoll_1_1";
        case Mix64Type_1::kGateRoll_1_4: return "kGateRoll_1_4";
        case Mix64Type_1::kGateRoll_1_8: return "kGateRoll_1_8";
        case Mix64Type_1::kGateTurn_1_1: return "kGateTurn_1_1";
        case Mix64Type_1::kGateTurn_1_4: return "kGateTurn_1_4";
        case Mix64Type_1::kGateTurn_1_8: return "kGateTurn_1_8";
        default: return "kInv";
    }
}

std::string Mix64Type4Token(const Mix64Type_4 pType) {
    switch (pType) {
        case Mix64Type_4::kGatePrismA_4_8: return "kGatePrismA_4_8";
        case Mix64Type_4::kGatePrismB_4_8: return "kGatePrismB_4_8";
        case Mix64Type_4::kGatePrismC_4_8: return "kGatePrismC_4_8";
        case Mix64Type_4::kGateRoll_4_4: return "kGateRoll_4_4";
        case Mix64Type_4::kGateRollA_4_8: return "kGateRollA_4_8";
        case Mix64Type_4::kGateRollB_4_8: return "kGateRollB_4_8";
        case Mix64Type_4::kGateRollC_4_8: return "kGateRollC_4_8";
        case Mix64Type_4::kGateTurn_4_4: return "kGateTurn_4_4";
        case Mix64Type_4::kGateTurnA_4_8: return "kGateTurnA_4_8";
        case Mix64Type_4::kGateTurnB_4_8: return "kGateTurnB_4_8";
        case Mix64Type_4::kGateTurnC_4_8: return "kGateTurnC_4_8";
        default: return "kInv";
    }
}

std::string Mix64Type8Token(const Mix64Type_8 pType) {
    switch (pType) {
        case Mix64Type_8::kGatePrism_8_8: return "kGatePrism_8_8";
        case Mix64Type_8::kGateRoll_8_8: return "kGateRoll_8_8";
        case Mix64Type_8::kGateTurn_8_8: return "kGateTurn_8_8";
        default: return "kInv";
    }
}

bool Mix64Type1FromToken(const std::string &pToken,
                         Mix64Type_1 *pType) {
    if (pType == NULL) {
        return false;
    }
    if (pToken == "kGatePrism_1_8") { *pType = Mix64Type_1::kGatePrism_1_8; return true; }
    if (pToken == "kGateRoll_1_1") { *pType = Mix64Type_1::kGateRoll_1_1; return true; }
    if (pToken == "kGateRoll_1_4") { *pType = Mix64Type_1::kGateRoll_1_4; return true; }
    if (pToken == "kGateRoll_1_8") { *pType = Mix64Type_1::kGateRoll_1_8; return true; }
    if (pToken == "kGateTurn_1_1") { *pType = Mix64Type_1::kGateTurn_1_1; return true; }
    if (pToken == "kGateTurn_1_4") { *pType = Mix64Type_1::kGateTurn_1_4; return true; }
    if (pToken == "kGateTurn_1_8") { *pType = Mix64Type_1::kGateTurn_1_8; return true; }
    return false;
}

bool Mix64Type4FromToken(const std::string &pToken,
                         Mix64Type_4 *pType) {
    if (pType == NULL) {
        return false;
    }
    if (pToken == "kGatePrismA_4_8") { *pType = Mix64Type_4::kGatePrismA_4_8; return true; }
    if (pToken == "kGatePrismB_4_8") { *pType = Mix64Type_4::kGatePrismB_4_8; return true; }
    if (pToken == "kGatePrismC_4_8") { *pType = Mix64Type_4::kGatePrismC_4_8; return true; }
    if (pToken == "kGateRoll_4_4") { *pType = Mix64Type_4::kGateRoll_4_4; return true; }
    if (pToken == "kGateRollA_4_8") { *pType = Mix64Type_4::kGateRollA_4_8; return true; }
    if (pToken == "kGateRollB_4_8") { *pType = Mix64Type_4::kGateRollB_4_8; return true; }
    if (pToken == "kGateRollC_4_8") { *pType = Mix64Type_4::kGateRollC_4_8; return true; }
    if (pToken == "kGateTurn_4_4") { *pType = Mix64Type_4::kGateTurn_4_4; return true; }
    if (pToken == "kGateTurnA_4_8") { *pType = Mix64Type_4::kGateTurnA_4_8; return true; }
    if (pToken == "kGateTurnB_4_8") { *pType = Mix64Type_4::kGateTurnB_4_8; return true; }
    if (pToken == "kGateTurnC_4_8") { *pType = Mix64Type_4::kGateTurnC_4_8; return true; }
    return false;
}

bool Mix64Type8FromToken(const std::string &pToken,
                         Mix64Type_8 *pType) {
    if (pType == NULL) {
        return false;
    }
    if (pToken == "kGatePrism_8_8") { *pType = Mix64Type_8::kGatePrism_8_8; return true; }
    if (pToken == "kGateRoll_8_8") { *pType = Mix64Type_8::kGateRoll_8_8; return true; }
    if (pToken == "kGateTurn_8_8") { *pType = Mix64Type_8::kGateTurn_8_8; return true; }
    return false;
}

std::string Mix64Type1CallToken(const Mix64Type_1 pType) {
    switch (pType) {
        case Mix64Type_1::kGatePrism_1_8: return "TwistMix64::GatePrism_1_8";
        case Mix64Type_1::kGateRoll_1_1: return "TwistMix64::GateRoll_1_1";
        case Mix64Type_1::kGateRoll_1_4: return "TwistMix64::GateRoll_1_4";
        case Mix64Type_1::kGateRoll_1_8: return "TwistMix64::GateRoll_1_8";
        case Mix64Type_1::kGateTurn_1_1: return "TwistMix64::GateTurn_1_1";
        case Mix64Type_1::kGateTurn_1_4: return "TwistMix64::GateTurn_1_4";
        case Mix64Type_1::kGateTurn_1_8: return "TwistMix64::GateTurn_1_8";
        default: return "";
    }
}

std::string Mix64Type4CallToken(const Mix64Type_4 pType) {
    switch (pType) {
        case Mix64Type_4::kGatePrismA_4_8: return "TwistMix64::GatePrismA_4_8";
        case Mix64Type_4::kGatePrismB_4_8: return "TwistMix64::GatePrismB_4_8";
        case Mix64Type_4::kGatePrismC_4_8: return "TwistMix64::GatePrismC_4_8";
        case Mix64Type_4::kGateRoll_4_4: return "TwistMix64::GateRoll_4_4";
        case Mix64Type_4::kGateRollA_4_8: return "TwistMix64::GateRollA_4_8";
        case Mix64Type_4::kGateRollB_4_8: return "TwistMix64::GateRollB_4_8";
        case Mix64Type_4::kGateRollC_4_8: return "TwistMix64::GateRollC_4_8";
        case Mix64Type_4::kGateTurn_4_4: return "TwistMix64::GateTurn_4_4";
        case Mix64Type_4::kGateTurnA_4_8: return "TwistMix64::GateTurnA_4_8";
        case Mix64Type_4::kGateTurnB_4_8: return "TwistMix64::GateTurnB_4_8";
        case Mix64Type_4::kGateTurnC_4_8: return "TwistMix64::GateTurnC_4_8";
        default: return "";
    }
}

std::string Mix64Type8CallToken(const Mix64Type_8 pType) {
    switch (pType) {
        case Mix64Type_8::kGatePrism_8_8: return "TwistMix64::GatePrism_8_8";
        case Mix64Type_8::kGateRoll_8_8: return "TwistMix64::GateRoll_8_8";
        case Mix64Type_8::kGateTurn_8_8: return "TwistMix64::GateTurn_8_8";
        default: return "";
    }
}

bool Mix64Type1NeedsAmount(const Mix64Type_1 pType) {
    switch (pType) {
        case Mix64Type_1::kGatePrism_1_8:
            return false;
        case Mix64Type_1::kGateRoll_1_1:
        case Mix64Type_1::kGateRoll_1_4:
        case Mix64Type_1::kGateRoll_1_8:
        case Mix64Type_1::kGateTurn_1_1:
        case Mix64Type_1::kGateTurn_1_4:
        case Mix64Type_1::kGateTurn_1_8:
            return true;
        default:
            return false;
    }
}

bool Mix64Type4NeedsAmount(const Mix64Type_4 pType) {
    switch (pType) {
        case Mix64Type_4::kGatePrismA_4_8:
        case Mix64Type_4::kGatePrismB_4_8:
        case Mix64Type_4::kGatePrismC_4_8:
            return false;
        case Mix64Type_4::kGateRoll_4_4:
        case Mix64Type_4::kGateRollA_4_8:
        case Mix64Type_4::kGateRollB_4_8:
        case Mix64Type_4::kGateRollC_4_8:
        case Mix64Type_4::kGateTurn_4_4:
        case Mix64Type_4::kGateTurnA_4_8:
        case Mix64Type_4::kGateTurnB_4_8:
        case Mix64Type_4::kGateTurnC_4_8:
            return true;
        default:
            return false;
    }
}

bool Mix64Type8NeedsAmount(const Mix64Type_8 pType) {
    switch (pType) {
        case Mix64Type_8::kGatePrism_8_8:
            return false;
        case Mix64Type_8::kGateRoll_8_8:
        case Mix64Type_8::kGateTurn_8_8:
            return true;
        default:
            return false;
    }
}

std::uint64_t EvaluateMix64Type1Local(const Mix64Type_1 pType,
                                      const std::uint64_t pValue,
                                      const std::uint64_t pAmount,
                                      const std::uint8_t *pSBoxA) {
    if (pSBoxA == NULL) {
        return pValue;
    }

    switch (pType) {
        case Mix64Type_1::kGatePrism_1_8:
            return TwistMix64::GatePrism_1_8(pValue, pSBoxA);
        case Mix64Type_1::kGateRoll_1_1:
            return TwistMix64::GateRoll_1_1(pValue, pAmount, pSBoxA);
        case Mix64Type_1::kGateRoll_1_4:
            return TwistMix64::GateRoll_1_4(pValue, pAmount, pSBoxA);
        case Mix64Type_1::kGateRoll_1_8:
            return TwistMix64::GateRoll_1_8(pValue, pAmount, pSBoxA);
        case Mix64Type_1::kGateTurn_1_1:
            return TwistMix64::GateTurn_1_1(pValue, pAmount, pSBoxA);
        case Mix64Type_1::kGateTurn_1_4:
            return TwistMix64::GateTurn_1_4(pValue, pAmount, pSBoxA);
        case Mix64Type_1::kGateTurn_1_8:
            return TwistMix64::GateTurn_1_8(pValue, pAmount, pSBoxA);
        default:
            return pValue;
    }
}

std::uint64_t EvaluateMix64Type4Local(const Mix64Type_4 pType,
                                      const std::uint64_t pValue,
                                      const std::uint64_t pAmount,
                                      const std::uint8_t *pSBoxA,
                                      const std::uint8_t *pSBoxB,
                                      const std::uint8_t *pSBoxC,
                                      const std::uint8_t *pSBoxD) {
    if ((pSBoxA == NULL) || (pSBoxB == NULL) || (pSBoxC == NULL) || (pSBoxD == NULL)) {
        return pValue;
    }

    switch (pType) {
        case Mix64Type_4::kGatePrismA_4_8:
            return TwistMix64::GatePrismA_4_8(pValue, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGatePrismB_4_8:
            return TwistMix64::GatePrismB_4_8(pValue, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGatePrismC_4_8:
            return TwistMix64::GatePrismC_4_8(pValue, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGateRoll_4_4:
            return TwistMix64::GateRoll_4_4(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGateRollA_4_8:
            return TwistMix64::GateRollA_4_8(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGateRollB_4_8:
            return TwistMix64::GateRollB_4_8(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGateRollC_4_8:
            return TwistMix64::GateRollC_4_8(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGateTurn_4_4:
            return TwistMix64::GateTurn_4_4(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGateTurnA_4_8:
            return TwistMix64::GateTurnA_4_8(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGateTurnB_4_8:
            return TwistMix64::GateTurnB_4_8(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        case Mix64Type_4::kGateTurnC_4_8:
            return TwistMix64::GateTurnC_4_8(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD);
        default:
            return pValue;
    }
}

std::uint64_t EvaluateMix64Type8Local(const Mix64Type_8 pType,
                                      const std::uint64_t pValue,
                                      const std::uint64_t pAmount,
                                      const std::uint8_t *pSBoxA,
                                      const std::uint8_t *pSBoxB,
                                      const std::uint8_t *pSBoxC,
                                      const std::uint8_t *pSBoxD,
                                      const std::uint8_t *pSBoxE,
                                      const std::uint8_t *pSBoxF,
                                      const std::uint8_t *pSBoxG,
                                      const std::uint8_t *pSBoxH) {
    if ((pSBoxA == NULL) || (pSBoxB == NULL) || (pSBoxC == NULL) || (pSBoxD == NULL) ||
        (pSBoxE == NULL) || (pSBoxF == NULL) || (pSBoxG == NULL) || (pSBoxH == NULL)) {
        return pValue;
    }

    switch (pType) {
        case Mix64Type_8::kGatePrism_8_8:
            return TwistMix64::GatePrism_8_8(pValue, pSBoxA, pSBoxB, pSBoxC, pSBoxD, pSBoxE, pSBoxF, pSBoxG, pSBoxH);
        case Mix64Type_8::kGateRoll_8_8:
            return TwistMix64::GateRoll_8_8(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD, pSBoxE, pSBoxF, pSBoxG, pSBoxH);
        case Mix64Type_8::kGateTurn_8_8:
            return TwistMix64::GateTurn_8_8(pValue, pAmount, pSBoxA, pSBoxB, pSBoxC, pSBoxD, pSBoxE, pSBoxF, pSBoxG, pSBoxH);
        default:
            return pValue;
    }
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

void CollectVariablesFromExpr(const GExpr &pExpr,
                              std::vector<std::string> *pNames) {
    if (pExpr.mType == GExprType::kSymbol && pExpr.mSymbol.IsVar()) {
        AppendUnique(pNames, pExpr.mSymbol.mName);
        return;
    }
    if (pExpr.mType == GExprType::kRead) {
        if (pExpr.mSymbol.IsVar()) {
            AppendUnique(pNames, pExpr.mSymbol.mName);
        }
        if (pExpr.mIndex != nullptr) {
            CollectVariablesFromExpr(*pExpr.mIndex, pNames);
        }
        return;
    }
    if (pExpr.mType == GExprType::kMix64_1 ||
        pExpr.mType == GExprType::kMix64_4 ||
        pExpr.mType == GExprType::kMix64_8) {
        if (pExpr.mA != nullptr) {
            CollectVariablesFromExpr(*pExpr.mA, pNames);
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
    if (pExpr.mType == GExprType::kMix64_1) {
        if (pExpr.mMix64SBoxA.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxA.mSlot);
        }
        if (pExpr.mA != nullptr) {
            CollectSlotsFromExpr(*pExpr.mA, pSlots);
        }
        return;
    }
    if (pExpr.mType == GExprType::kMix64_4) {
        if (pExpr.mMix64SBoxA.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxA.mSlot);
        }
        if (pExpr.mMix64SBoxB.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxB.mSlot);
        }
        if (pExpr.mMix64SBoxC.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxC.mSlot);
        }
        if (pExpr.mMix64SBoxD.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxD.mSlot);
        }
        if (pExpr.mA != nullptr) {
            CollectSlotsFromExpr(*pExpr.mA, pSlots);
        }
        return;
    }
    if (pExpr.mType == GExprType::kMix64_8) {
        if (pExpr.mMix64SBoxA.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxA.mSlot);
        }
        if (pExpr.mMix64SBoxB.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxB.mSlot);
        }
        if (pExpr.mMix64SBoxC.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxC.mSlot);
        }
        if (pExpr.mMix64SBoxD.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxD.mSlot);
        }
        if (pExpr.mMix64SBoxE.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxE.mSlot);
        }
        if (pExpr.mMix64SBoxF.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxF.mSlot);
        }
        if (pExpr.mMix64SBoxG.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxG.mSlot);
        }
        if (pExpr.mMix64SBoxH.IsBuf()) {
            AppendUnique(pSlots, pExpr.mMix64SBoxH.mSlot);
        }
        if (pExpr.mA != nullptr) {
            CollectSlotsFromExpr(*pExpr.mA, pSlots);
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
    if ((pExpr.mType == GExprType::kMix64_1) &&
        pExpr.mMix64SBoxA.IsBuf() &&
        (pExpr.mMix64SBoxA.mSlot == pSlot)) {
        ++aCount;
    }
    if ((pExpr.mType == GExprType::kMix64_4) &&
        ((pExpr.mMix64SBoxA.IsBuf() && (pExpr.mMix64SBoxA.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxB.IsBuf() && (pExpr.mMix64SBoxB.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxC.IsBuf() && (pExpr.mMix64SBoxC.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxD.IsBuf() && (pExpr.mMix64SBoxD.mSlot == pSlot)))) {
        ++aCount;
    }
    if ((pExpr.mType == GExprType::kMix64_8) &&
        ((pExpr.mMix64SBoxA.IsBuf() && (pExpr.mMix64SBoxA.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxB.IsBuf() && (pExpr.mMix64SBoxB.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxC.IsBuf() && (pExpr.mMix64SBoxC.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxD.IsBuf() && (pExpr.mMix64SBoxD.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxE.IsBuf() && (pExpr.mMix64SBoxE.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxF.IsBuf() && (pExpr.mMix64SBoxF.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxG.IsBuf() && (pExpr.mMix64SBoxG.mSlot == pSlot)) ||
         (pExpr.mMix64SBoxH.IsBuf() && (pExpr.mMix64SBoxH.mSlot == pSlot)))) {
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

void CollectReadSymbolsFromStatement(const GStatement &pStatement,
                                     std::vector<GSymbol> *pSymbols) {
    if (pStatement.mTarget.mIndex != nullptr) {
        const std::vector<GSymbol> aTargetSymbols = pStatement.mTarget.mIndex->GetSymbols();
        pSymbols->insert(pSymbols->end(), aTargetSymbols.begin(), aTargetSymbols.end());
    }

    const std::vector<GSymbol> aExprSymbols = pStatement.mExpression.GetSymbols();
    pSymbols->insert(pSymbols->end(), aExprSymbols.begin(), aExprSymbols.end());
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
        case GExprType::kShiftL: return "<<";
        case GExprType::kShiftR: return ">>";
        default: return "";
    }
}

std::string AssignOperatorText(const GAssignType pType) {
    switch (pType) {
        case GAssignType::kSet: return "=";
        default: return "?=";
    }
}

[[maybe_unused]] bool EndsWithText(const std::string &pText,
                                   const std::string &pSuffix) {
    if (pSuffix.size() > pText.size()) {
        return false;
    }
    return pText.compare(pText.size() - pSuffix.size(), pSuffix.size(), pSuffix) == 0;
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
        return "std::uint64_t";
    }
    if (IsKeyScalarName(pName)) {
        return "std::size_t";
    }
    return "std::uint64_t";
}

GRuntimeScalar NormalizeScalarValueForName(const std::string &pName,
                                           const GRuntimeScalar pValue) {
    if (IsKeyScalarName(pName)) {
        return pValue;
    }
    return pValue;
}

bool LoopUsesUint32(const GLoop &pLoop) {
    return (pLoop.mLoopBegin >= 0) && (pLoop.mLoopStep > 0);
}

bool IsSBoxSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSBoxA:
        case TwistWorkSpaceSlot::kSBoxB:
        case TwistWorkSpaceSlot::kSBoxC:
        case TwistWorkSpaceSlot::kSBoxD:
        case TwistWorkSpaceSlot::kDerivedSBoxA:
        case TwistWorkSpaceSlot::kDerivedSBoxB:
        case TwistWorkSpaceSlot::kDerivedSBoxC:
        case TwistWorkSpaceSlot::kDerivedSBoxD:
        case TwistWorkSpaceSlot::kDerivedSBoxE:
        case TwistWorkSpaceSlot::kDerivedSBoxF:
        case TwistWorkSpaceSlot::kDerivedSBoxG:
        case TwistWorkSpaceSlot::kDerivedSBoxH:
            return true;
        default:
            return false;
    }
}

bool IsSaltSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSaltA:
        case TwistWorkSpaceSlot::kSaltB:
        case TwistWorkSpaceSlot::kSaltC:
        case TwistWorkSpaceSlot::kSaltD:
        case TwistWorkSpaceSlot::kScratchSaltA:
        case TwistWorkSpaceSlot::kScratchSaltB:
        case TwistWorkSpaceSlot::kScratchSaltC:
        case TwistWorkSpaceSlot::kScratchSaltD:
        case TwistWorkSpaceSlot::kDerivedSaltA:
        case TwistWorkSpaceSlot::kDerivedSaltB:
        case TwistWorkSpaceSlot::kDerivedSaltC:
        case TwistWorkSpaceSlot::kDerivedSaltD:
        case TwistWorkSpaceSlot::kDerivedSaltE:
        case TwistWorkSpaceSlot::kDerivedSaltF:
        case TwistWorkSpaceSlot::kDerivedSaltG:
        case TwistWorkSpaceSlot::kDerivedSaltH:
            return true;
        default:
            return false;
    }
}

std::size_t RuntimeIndexForSlot(const TwistWorkSpaceSlot pSlot,
                                const GRuntimeScalar pIndexValue) {
    if (IsSaltSlot(pSlot)) {
        return static_cast<std::size_t>(pIndexValue & 0x7FULL);
    }
    if (IsSBoxSlot(pSlot)) {
        return static_cast<std::size_t>(pIndexValue & 0xFFULL);
    }
    return static_cast<std::size_t>(pIndexValue);
}

bool IsWideScratchSaltSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kScratchSaltA:
        case TwistWorkSpaceSlot::kScratchSaltB:
        case TwistWorkSpaceSlot::kScratchSaltC:
        case TwistWorkSpaceSlot::kScratchSaltD:
            return true;
        default:
            return false;
    }
}

GRuntimeScalar ReadRuntimeBufferValue(const TwistWorkSpaceSlot pSlot,
                                      const std::uint8_t *pBuffer,
                                      const std::size_t pIndex) {
    if (IsWideScratchSaltSlot(pSlot)) {
        const std::uint64_t *aWideBuffer = reinterpret_cast<const std::uint64_t *>(pBuffer);
        return static_cast<GRuntimeScalar>(aWideBuffer[pIndex]);
    }
    return static_cast<GRuntimeScalar>(pBuffer[pIndex]);
}

void WriteRuntimeBufferValue(const TwistWorkSpaceSlot pSlot,
                             std::uint8_t *pBuffer,
                             const std::size_t pIndex,
                             const GRuntimeScalar pValue) {
    if (IsWideScratchSaltSlot(pSlot)) {
        std::uint64_t *aWideBuffer = reinterpret_cast<std::uint64_t *>(pBuffer);
        aWideBuffer[pIndex] = static_cast<std::uint64_t>(pValue);
        return;
    }
    pBuffer[pIndex] = static_cast<std::uint8_t>(pValue);
}

unsigned int ReadWrapTrimMaskForType(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kBlock: return 0x1FFFU;
        case GReadWrapType::kSBox: return 0xFFU;
        case GReadWrapType::kSalt: return 0x7FU;
        case GReadWrapType::kMaskA: return static_cast<unsigned int>(S_MASK_A - 1U);
        case GReadWrapType::kMaskB: return static_cast<unsigned int>(S_MASK_B - 1U);
        case GReadWrapType::kKeyA: return static_cast<unsigned int>(S_KEY_A - 1U);
        case GReadWrapType::kKeyB: return static_cast<unsigned int>(S_KEY_B - 1U);
        default: return 0U;
    }
}

int ResolveLengthText(const std::string &pText) {
    if (pText == "S_BLOCK") { return S_BLOCK; }
    if (pText == "S_SBOX") { return S_SBOX; }
    if (pText == "S_SALT") { return S_SALT; }
    if (pText == "S_BLOCK1") { return S_BLOCK1; }
    if (pText == "S_SBOX1") { return S_SBOX1; }
    if (pText == "S_SALT1") { return S_SALT1; }
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
                         std::string *pErrorMessage) {
    if (pSymbol == NULL) {
        SetError(pErrorMessage, "Symbol output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pErrorMessage, "Symbol JSON was not an object.");
        return false;
    }

    const JsonValue *aKind = pValue.find("kind");
    const JsonValue *aName = pValue.find("name");
    if ((aKind == NULL) || !aKind->is_string() || (aName == NULL) || !aName->is_string()) {
        SetError(pErrorMessage, "Symbol JSON was incomplete.");
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
            SetError(pErrorMessage, "Buffer symbol was missing a slot.");
            return false;
        }
        TwistWorkSpaceSlot aParsedSlot = TwistWorkSpaceSlot::kInvalid;
        if (!SlotFromToken(aSlot->as_string(), &aParsedSlot)) {
            SetError(pErrorMessage, "Buffer symbol slot token was unknown.");
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
        aObject["read_wrap_offset"] = JsonValue::Number(static_cast<double>(pExpr.mReadWrapOffset));
    }
    if (pExpr.mType == GExprType::kMix64_1) {
        aObject["mix64_1_type"] = JsonValue::String(Mix64Type1Token(pExpr.mMix64Type1));
        aObject["mix64_use_amount"] = JsonValue::Bool(pExpr.mMix64UseAmount);
        aObject["mix64_amount"] = JsonValue::String(std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)));
        aObject["mix64_sbox_a_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxA);
    }
    if (pExpr.mType == GExprType::kMix64_4) {
        aObject["mix64_4_type"] = JsonValue::String(Mix64Type4Token(pExpr.mMix64Type4));
        aObject["mix64_use_amount"] = JsonValue::Bool(pExpr.mMix64UseAmount);
        aObject["mix64_amount"] = JsonValue::String(std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)));
        aObject["mix64_sbox_a_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxA);
        aObject["mix64_sbox_b_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxB);
        aObject["mix64_sbox_c_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxC);
        aObject["mix64_sbox_d_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxD);
    }
    if (pExpr.mType == GExprType::kMix64_8) {
        aObject["mix64_8_type"] = JsonValue::String(Mix64Type8Token(pExpr.mMix64Type8));
        aObject["mix64_use_amount"] = JsonValue::Bool(pExpr.mMix64UseAmount);
        aObject["mix64_amount"] = JsonValue::String(std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)));
        aObject["mix64_sbox_a_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxA);
        aObject["mix64_sbox_b_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxB);
        aObject["mix64_sbox_c_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxC);
        aObject["mix64_sbox_d_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxD);
        aObject["mix64_sbox_e_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxE);
        aObject["mix64_sbox_f_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxF);
        aObject["mix64_sbox_g_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxG);
        aObject["mix64_sbox_h_symbol"] = SymbolToJsonValue(pExpr.mMix64SBoxH);
    }
    return JsonValue::ObjectValue(std::move(aObject));
}

bool ExprFromJsonValue(const JsonValue &pValue,
                       GExpr *pExpr,
                       std::string *pErrorMessage) {
    if (pExpr == NULL) {
        SetError(pErrorMessage, "Expression output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pErrorMessage, "Expression JSON was not an object.");
        return false;
    }

    const JsonValue *aType = pValue.find("type");
    if ((aType == NULL) || !aType->is_string()) {
        SetError(pErrorMessage, "Expression JSON was missing a type.");
        return false;
    }

    GExprType aTypeValue = GExprType::kInv;
    if (!ExprTypeFromToken(aType->as_string(), &aTypeValue)) {
        SetError(pErrorMessage, "Expression type token was unknown.");
        return false;
    }

    GExpr aExpr;
    switch (aTypeValue) {
        case GExprType::kSymbol: {
            const JsonValue *aSymbol = pValue.find("symbol");
            if (aSymbol == NULL) {
                SetError(pErrorMessage, "Symbol expression was missing a symbol.");
                return false;
            }
            GSymbol aParsedSymbol;
            if (!SymbolFromJsonValue(*aSymbol, &aParsedSymbol, pErrorMessage)) {
                return false;
            }
            aExpr = GExpr::Symbol(aParsedSymbol);
            break;
        }
        case GExprType::kConst: {
            const JsonValue *aValue = pValue.find("value");
            std::uint64_t aNumber = 0U;
            if ((aValue == NULL) || !ParseUInt64(*aValue, &aNumber)) {
                SetError(pErrorMessage, "Constant expression value was invalid.");
                return false;
            }
            aExpr.mType = GExprType::kConst;
            aExpr.mConstVal = aNumber;
            break;
        }
        case GExprType::kRead: {
            const JsonValue *aSymbol = pValue.find("symbol");
            const JsonValue *aIndex = pValue.find("index");
            if ((aSymbol == NULL) || (aIndex == NULL)) {
                SetError(pErrorMessage, "Read expression was incomplete.");
                return false;
            }
            GSymbol aParsedSymbol;
            GExpr aIndexExpr;
            if (!SymbolFromJsonValue(*aSymbol, &aParsedSymbol, pErrorMessage) ||
                !ExprFromJsonValue(*aIndex, &aIndexExpr, pErrorMessage)) {
                return false;
            }
            aExpr = GExpr::Read(aParsedSymbol, aIndexExpr);

            if (const JsonValue *aWrapType = pValue.find("read_wrap_type");
                (aWrapType != NULL) && aWrapType->is_string()) {
                GReadWrapType aWrapTypeValue = GReadWrapType::kNone;
                if (!ReadWrapTypeFromToken(aWrapType->as_string(), &aWrapTypeValue)) {
                    SetError(pErrorMessage, "Read wrap type token was unknown.");
                    return false;
                }

                if (aWrapTypeValue != GReadWrapType::kNone) {
                    const JsonValue *aWrapIndexSymbol = pValue.find("read_wrap_index_symbol");
                    const JsonValue *aWrapOracleSymbol = pValue.find("read_wrap_oracle_symbol");
                    const JsonValue *aWrapOffset = pValue.find("read_wrap_offset");
                    if ((aWrapIndexSymbol == NULL) || (aWrapOracleSymbol == NULL) || (aWrapOffset == NULL)) {
                        SetError(pErrorMessage, "Read wrap metadata was incomplete.");
                        return false;
                    }

                    GSymbol aWrapIndexParsed;
                    GSymbol aWrapOracleParsed;
                    int aWrapOffsetParsed = 0;
                    if (!SymbolFromJsonValue(*aWrapIndexSymbol, &aWrapIndexParsed, pErrorMessage) ||
                        !SymbolFromJsonValue(*aWrapOracleSymbol, &aWrapOracleParsed, pErrorMessage) ||
                        !ParseInt32(*aWrapOffset, &aWrapOffsetParsed)) {
                        SetError(pErrorMessage, "Read wrap metadata was invalid.");
                        return false;
                    }

                    aExpr.mReadWrapType = aWrapTypeValue;
                    aExpr.mReadWrapIndexSymbol = aWrapIndexParsed;
                    aExpr.mReadWrapOracleSymbol = aWrapOracleParsed;
                    aExpr.mReadWrapOffset = aWrapOffsetParsed;
                }
            }
            break;
        }
        case GExprType::kDiffuse64: {
            const JsonValue *aValue = pValue.find("a");
            if (aValue == NULL) {
                SetError(pErrorMessage, "Diffuse64 expression was incomplete.");
                return false;
            }
            GExpr aInput;
            if (!ExprFromJsonValue(*aValue, &aInput, pErrorMessage)) {
                return false;
            }
            aExpr = GExpr::Diffuse(aInput);
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
                SetError(pErrorMessage, "Binary expression was incomplete.");
                return false;
            }
            GExpr aLeft;
            GExpr aRight;
            if (!ExprFromJsonValue(*aA, &aLeft, pErrorMessage) ||
                !ExprFromJsonValue(*aB, &aRight, pErrorMessage)) {
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
        case GExprType::kMix64_1: {
            const JsonValue *aValue = pValue.find("a");
            const JsonValue *aMixType = pValue.find("mix64_1_type");
            const JsonValue *aSBoxA = pValue.find("mix64_sbox_a_symbol");
            if ((aValue == NULL) || (aMixType == NULL) || !aMixType->is_string() || (aSBoxA == NULL)) {
                SetError(pErrorMessage, "Mix64_1 expression was incomplete.");
                return false;
            }

            GExpr aValueExpr;
            if (!ExprFromJsonValue(*aValue, &aValueExpr, pErrorMessage)) {
                return false;
            }

            Mix64Type_1 aParsedMixType = Mix64Type_1::kInv;
            if (!Mix64Type1FromToken(aMixType->as_string(), &aParsedMixType)) {
                SetError(pErrorMessage, "Mix64_1 type token was invalid.");
                return false;
            }

            GSymbol aParsedSBoxA;
            if (!SymbolFromJsonValue(*aSBoxA, &aParsedSBoxA, pErrorMessage)) {
                return false;
            }

            const JsonValue *aUseAmount = pValue.find("mix64_use_amount");
            const JsonValue *aAmount = pValue.find("mix64_amount");
            const bool aHasAmount = (aUseAmount != NULL) && aUseAmount->as_bool(false);
            if (aHasAmount && (aAmount != NULL)) {
                std::uint64_t aParsedAmount = 0U;
                if (!ParseUInt64(*aAmount, &aParsedAmount)) {
                    SetError(pErrorMessage, "Mix64_1 amount token was invalid.");
                    return false;
                }
                aExpr = GExpr::Mix64_1(aValueExpr, aParsedMixType, aParsedAmount, aParsedSBoxA);
            } else {
                aExpr = GExpr::Mix64_1(aValueExpr, aParsedMixType, aParsedSBoxA);
            }
            break;
        }
        case GExprType::kMix64_4: {
            const JsonValue *aValue = pValue.find("a");
            const JsonValue *aMixType = pValue.find("mix64_4_type");
            const JsonValue *aSBoxA = pValue.find("mix64_sbox_a_symbol");
            const JsonValue *aSBoxB = pValue.find("mix64_sbox_b_symbol");
            const JsonValue *aSBoxC = pValue.find("mix64_sbox_c_symbol");
            const JsonValue *aSBoxD = pValue.find("mix64_sbox_d_symbol");
            if ((aValue == NULL) || (aMixType == NULL) || !aMixType->is_string() ||
                (aSBoxA == NULL) || (aSBoxB == NULL) || (aSBoxC == NULL) || (aSBoxD == NULL)) {
                SetError(pErrorMessage, "Mix64_4 expression was incomplete.");
                return false;
            }

            GExpr aValueExpr;
            if (!ExprFromJsonValue(*aValue, &aValueExpr, pErrorMessage)) {
                return false;
            }

            Mix64Type_4 aParsedMixType = Mix64Type_4::kInv;
            if (!Mix64Type4FromToken(aMixType->as_string(), &aParsedMixType)) {
                SetError(pErrorMessage, "Mix64_4 type token was invalid.");
                return false;
            }

            GSymbol aParsedSBoxA;
            GSymbol aParsedSBoxB;
            GSymbol aParsedSBoxC;
            GSymbol aParsedSBoxD;
            if (!SymbolFromJsonValue(*aSBoxA, &aParsedSBoxA, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxB, &aParsedSBoxB, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxC, &aParsedSBoxC, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxD, &aParsedSBoxD, pErrorMessage)) {
                return false;
            }

            const JsonValue *aUseAmount = pValue.find("mix64_use_amount");
            const JsonValue *aAmount = pValue.find("mix64_amount");
            const bool aHasAmount = (aUseAmount != NULL) && aUseAmount->as_bool(false);
            if (aHasAmount && (aAmount != NULL)) {
                std::uint64_t aParsedAmount = 0U;
                if (!ParseUInt64(*aAmount, &aParsedAmount)) {
                    SetError(pErrorMessage, "Mix64_4 amount token was invalid.");
                    return false;
                }
                aExpr = GExpr::Mix64_4(aValueExpr,
                                       aParsedMixType,
                                       aParsedAmount,
                                       aParsedSBoxA,
                                       aParsedSBoxB,
                                       aParsedSBoxC,
                                       aParsedSBoxD);
            } else {
                aExpr = GExpr::Mix64_4(aValueExpr,
                                       aParsedMixType,
                                       aParsedSBoxA,
                                       aParsedSBoxB,
                                       aParsedSBoxC,
                                       aParsedSBoxD);
            }
            break;
        }
        case GExprType::kMix64_8: {
            const JsonValue *aValue = pValue.find("a");
            const JsonValue *aMixType = pValue.find("mix64_8_type");
            const JsonValue *aSBoxA = pValue.find("mix64_sbox_a_symbol");
            const JsonValue *aSBoxB = pValue.find("mix64_sbox_b_symbol");
            const JsonValue *aSBoxC = pValue.find("mix64_sbox_c_symbol");
            const JsonValue *aSBoxD = pValue.find("mix64_sbox_d_symbol");
            const JsonValue *aSBoxE = pValue.find("mix64_sbox_e_symbol");
            const JsonValue *aSBoxF = pValue.find("mix64_sbox_f_symbol");
            const JsonValue *aSBoxG = pValue.find("mix64_sbox_g_symbol");
            const JsonValue *aSBoxH = pValue.find("mix64_sbox_h_symbol");
            if ((aValue == NULL) || (aMixType == NULL) || !aMixType->is_string() ||
                (aSBoxA == NULL) || (aSBoxB == NULL) || (aSBoxC == NULL) || (aSBoxD == NULL) ||
                (aSBoxE == NULL) || (aSBoxF == NULL) || (aSBoxG == NULL) || (aSBoxH == NULL)) {
                SetError(pErrorMessage, "Mix64_8 expression was incomplete.");
                return false;
            }

            GExpr aValueExpr;
            if (!ExprFromJsonValue(*aValue, &aValueExpr, pErrorMessage)) {
                return false;
            }

            Mix64Type_8 aParsedMixType = Mix64Type_8::kInv;
            if (!Mix64Type8FromToken(aMixType->as_string(), &aParsedMixType)) {
                SetError(pErrorMessage, "Mix64_8 type token was invalid.");
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
            if (!SymbolFromJsonValue(*aSBoxA, &aParsedSBoxA, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxB, &aParsedSBoxB, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxC, &aParsedSBoxC, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxD, &aParsedSBoxD, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxE, &aParsedSBoxE, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxF, &aParsedSBoxF, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxG, &aParsedSBoxG, pErrorMessage) ||
                !SymbolFromJsonValue(*aSBoxH, &aParsedSBoxH, pErrorMessage)) {
                return false;
            }

            const JsonValue *aUseAmount = pValue.find("mix64_use_amount");
            const JsonValue *aAmount = pValue.find("mix64_amount");
            const bool aHasAmount = (aUseAmount != NULL) && aUseAmount->as_bool(false);
            if (aHasAmount && (aAmount != NULL)) {
                std::uint64_t aParsedAmount = 0U;
                if (!ParseUInt64(*aAmount, &aParsedAmount)) {
                    SetError(pErrorMessage, "Mix64_8 amount token was invalid.");
                    return false;
                }
                aExpr = GExpr::Mix64_8(aValueExpr,
                                       aParsedMixType,
                                       aParsedAmount,
                                       aParsedSBoxA,
                                       aParsedSBoxB,
                                       aParsedSBoxC,
                                       aParsedSBoxD,
                                       aParsedSBoxE,
                                       aParsedSBoxF,
                                       aParsedSBoxG,
                                       aParsedSBoxH);
            } else {
                aExpr = GExpr::Mix64_8(aValueExpr,
                                       aParsedMixType,
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
                         std::string *pErrorMessage) {
    if (pTarget == NULL) {
        SetError(pErrorMessage, "Target output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pErrorMessage, "Target JSON was not an object.");
        return false;
    }

    const JsonValue *aSymbol = pValue.find("symbol");
    if (aSymbol == NULL) {
        SetError(pErrorMessage, "Target symbol was missing.");
        return false;
    }

    GSymbol aParsedSymbol;
    if (!SymbolFromJsonValue(*aSymbol, &aParsedSymbol, pErrorMessage)) {
        return false;
    }

    const JsonValue *aIndex = pValue.find("index");
    if ((aIndex == NULL) || aIndex->is_null()) {
        *pTarget = GTarget::Symbol(aParsedSymbol);
        return true;
    }

    GExpr aIndexExpr;
    if (!ExprFromJsonValue(*aIndex, &aIndexExpr, pErrorMessage)) {
        return false;
    }
    *pTarget = GTarget::Write(aParsedSymbol, aIndexExpr);
    return true;
}

JsonValue StatementToJsonValue(const GStatement &pStatement) {
    if (pStatement.IsRawLine()) {
        JsonValue::Object aObject;
        aObject["kind"] = JsonValue::String("raw_line");
        aObject["line"] = JsonValue::String(pStatement.mRawLine);
        if (!pStatement.mOutputPrefix.empty()) {
            aObject["output_prefix"] = JsonValue::String(pStatement.mOutputPrefix);
        }
        return JsonValue::ObjectValue(std::move(aObject));
    }

    JsonValue::Object aObject;
    aObject["kind"] = JsonValue::String("assign");
    aObject["target"] = TargetToJsonValue(pStatement.mTarget);
    aObject["assign"] = JsonValue::String(AssignTypeToken(pStatement.mAssignType));
    aObject["expression"] = ExprToJsonValue(pStatement.mExpression);
    if (!pStatement.mOutputPrefix.empty()) {
        aObject["output_prefix"] = JsonValue::String(pStatement.mOutputPrefix);
    }
    return JsonValue::ObjectValue(std::move(aObject));
}

bool StatementFromJsonValue(const JsonValue &pValue,
                            GStatement *pStatement,
                            std::string *pErrorMessage) {
    if (pStatement == NULL) {
        SetError(pErrorMessage, "Statement output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pErrorMessage, "Statement JSON was not an object.");
        return false;
    }

    const JsonValue *aKind = pValue.find("kind");
    if ((aKind != NULL) && aKind->is_string() && (aKind->as_string() == "raw_line")) {
        const JsonValue *aLine = pValue.find("line");
        if ((aLine == NULL) || !aLine->is_string()) {
            SetError(pErrorMessage, "Raw-line statement JSON was incomplete.");
            return false;
        }
        GStatement aStatement = GStatement::RawLine(aLine->as_string());
        const JsonValue *aOutputPrefix = pValue.find("output_prefix");
        if ((aOutputPrefix != NULL) && aOutputPrefix->is_string()) {
            aStatement.mOutputPrefix = aOutputPrefix->as_string();
        }
        *pStatement = aStatement;
        return true;
    }

    const JsonValue *aTarget = pValue.find("target");
    const JsonValue *aAssign = pValue.find("assign");
    const JsonValue *aExpr = pValue.find("expression");
    if ((aTarget == NULL) || (aAssign == NULL) || !aAssign->is_string() || (aExpr == NULL)) {
        SetError(pErrorMessage, "Statement JSON was incomplete.");
        return false;
    }

    GStatement aStatement;
    if (!TargetFromJsonValue(*aTarget, &aStatement.mTarget, pErrorMessage) ||
        !ExprFromJsonValue(*aExpr, &aStatement.mExpression, pErrorMessage) ||
        !AssignTypeFromToken(aAssign->as_string(), &aStatement.mAssignType)) {
        if ((aStatement.mAssignType == GAssignType::kInvalid) && (pErrorMessage != NULL) && pErrorMessage->empty()) {
            *pErrorMessage = "Statement assign token was invalid.";
        }
        return false;
    }
    aStatement.mType = GStatementType::kAssign;
    aStatement.mRawLine.clear();
    const JsonValue *aOutputPrefix = pValue.find("output_prefix");
    if ((aOutputPrefix != NULL) && aOutputPrefix->is_string()) {
        aStatement.mOutputPrefix = aOutputPrefix->as_string();
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

    JsonValue::Array aBodyDecorations;
    for (const GLoop::BodyDecoration &aDecoration : pLoop.mBodyDecorations) {
        JsonValue::Object aDecorationObject;
        if (aDecoration.mType == GLoop::BodyDecoration::Type::kEmptyLine) {
            aDecorationObject["kind"] = JsonValue::String("empty_line");
        } else {
            aDecorationObject["kind"] = JsonValue::String("comment");
            aDecorationObject["text"] = JsonValue::String(aDecoration.mText);
        }
        aDecorationObject["statement_index"] = JsonValue::Number(static_cast<double>(aDecoration.mStatementIndex));
        aBodyDecorations.push_back(JsonValue::ObjectValue(std::move(aDecorationObject)));
    }

    JsonValue::Object aObject;
    aObject["loop_variable"] = JsonValue::String(pLoop.mLoopVariableName);
    aObject["loop_begin"] = JsonValue::Number(static_cast<double>(pLoop.mLoopBegin));
    aObject["loop_end_text"] = JsonValue::String(pLoop.mLoopEndText);
    aObject["loop_step"] = JsonValue::Number(static_cast<double>(pLoop.mLoopStep));
    aObject["init"] = JsonValue::ArrayValue(std::move(aInit));
    aObject["body"] = JsonValue::ArrayValue(std::move(aBody));
    aObject["body_decorations"] = JsonValue::ArrayValue(std::move(aBodyDecorations));
    return JsonValue::ObjectValue(std::move(aObject));
}

bool LoopFromJsonValue(const JsonValue &pValue,
                       GLoop *pLoop,
                       std::string *pErrorMessage) {
    if (pLoop == NULL) {
        SetError(pErrorMessage, "Loop output was null.");
        return false;
    }
    if (!pValue.is_object()) {
        SetError(pErrorMessage, "Loop JSON was not an object.");
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
        SetError(pErrorMessage, "Loop JSON was incomplete.");
        return false;
    }

    GLoop aLoop;
    if (!ParseInt32(*aBegin, &aLoop.mLoopBegin) ||
        !ParseInt32(*aStep, &aLoop.mLoopStep)) {
        SetError(pErrorMessage, "Loop numeric fields were invalid.");
        return false;
    }

    aLoop.mLoopVariableName = aVariable->as_string();
    aLoop.mLoopVariable = GSymbol::Var(aLoop.mLoopVariableName);
    aLoop.mLoopEndText = aEnd->as_string();

    for (const JsonValue &aValue : aInit->as_array()) {
        GStatement aStatement;
        if (!StatementFromJsonValue(aValue, &aStatement, pErrorMessage)) {
            return false;
        }
        aLoop.mInitializationStatements.push_back(aStatement);
    }

    for (const JsonValue &aValue : aBody->as_array()) {
        GStatement aStatement;
        if (!StatementFromJsonValue(aValue, &aStatement, pErrorMessage)) {
            return false;
        }
        aLoop.mBodyStatements.push_back(aStatement);
    }

    if (const JsonValue *aBodyDecorations = pValue.find("body_decorations");
        (aBodyDecorations != NULL) && aBodyDecorations->is_array()) {
        for (const JsonValue &aDecorationValue : aBodyDecorations->as_array()) {
            if (!aDecorationValue.is_object()) {
                SetError(pErrorMessage, "Loop body decoration JSON entry was not an object.");
                return false;
            }

            const JsonValue *aKind = aDecorationValue.find("kind");
            const JsonValue *aStatementIndex = aDecorationValue.find("statement_index");
            if ((aKind == NULL) || !aKind->is_string() ||
                (aStatementIndex == NULL) || !aStatementIndex->is_number()) {
                SetError(pErrorMessage, "Loop body decoration JSON was incomplete.");
                return false;
            }

            GLoop::BodyDecoration aDecoration;
            if (aKind->as_string() == "empty_line") {
                aDecoration.mType = GLoop::BodyDecoration::Type::kEmptyLine;
                aDecoration.mText.clear();
            } else if (aKind->as_string() == "comment") {
                aDecoration.mType = GLoop::BodyDecoration::Type::kComment;
                const JsonValue *aText = aDecorationValue.find("text");
                aDecoration.mText = ((aText != NULL) && aText->is_string()) ? aText->as_string() : "";
            } else {
                SetError(pErrorMessage, "Loop body decoration kind was invalid.");
                return false;
            }

            std::uint64_t aParsedStatementIndex = 0U;
            if (!ParseUInt64(*aStatementIndex, &aParsedStatementIndex)) {
                SetError(pErrorMessage, "Loop body decoration statement index was invalid.");
                return false;
            }
            aDecoration.mStatementIndex = static_cast<std::size_t>(aParsedStatementIndex);
            aLoop.mBodyDecorations.push_back(std::move(aDecoration));
        }
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
        case GExprType::kOr:
        case GExprType::kShiftL:
        case GExprType::kShiftR:
            return "(" + PrettyExpr(*pExpr.mA) + " " + ScalarOperatorText(pExpr.mType) +
                   " " + PrettyExpr(*pExpr.mB) + ")";
        case GExprType::kRotL8:
            return "rotl8(" + PrettyExpr(*pExpr.mA) + ", " + PrettyExpr(*pExpr.mB) + ")";
        case GExprType::kRotL32:
            return "rotl32(" + PrettyExpr(*pExpr.mA) + ", " + PrettyExpr(*pExpr.mB) + ")";
        case GExprType::kRotL64:
            return "rotl64(" + PrettyExpr(*pExpr.mA) + ", " + PrettyExpr(*pExpr.mB) + ")";
        case GExprType::kDiffuse64:
            return "diffuse64(" + PrettyExpr(*pExpr.mA) + ")";
        case GExprType::kMix64_1: {
            const std::string aCall = Mix64Type1CallToken(pExpr.mMix64Type1);
            if (Mix64Type1NeedsAmount(pExpr.mMix64Type1)) {
                return aCall + "(" + PrettyExpr(*pExpr.mA) + ", " +
                       std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)) + ", " +
                       pExpr.mMix64SBoxA.mName + ")";
            }
            return aCall + "(" + PrettyExpr(*pExpr.mA) + ", " + pExpr.mMix64SBoxA.mName + ")";
        }
        case GExprType::kMix64_4: {
            const std::string aCall = Mix64Type4CallToken(pExpr.mMix64Type4);
            const std::string aSBoxes = pExpr.mMix64SBoxA.mName + ", " + pExpr.mMix64SBoxB.mName +
                                        ", " + pExpr.mMix64SBoxC.mName + ", " + pExpr.mMix64SBoxD.mName;
            if (Mix64Type4NeedsAmount(pExpr.mMix64Type4)) {
                return aCall + "(" + PrettyExpr(*pExpr.mA) + ", " +
                       std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)) + ", " +
                       aSBoxes + ")";
            }
            return aCall + "(" + PrettyExpr(*pExpr.mA) + ", " + aSBoxes + ")";
        }
        case GExprType::kMix64_8: {
            const std::string aCall = Mix64Type8CallToken(pExpr.mMix64Type8);
            const std::string aSBoxes = pExpr.mMix64SBoxA.mName + ", " + pExpr.mMix64SBoxB.mName +
                                        ", " + pExpr.mMix64SBoxC.mName + ", " + pExpr.mMix64SBoxD.mName +
                                        ", " + pExpr.mMix64SBoxE.mName + ", " + pExpr.mMix64SBoxF.mName +
                                        ", " + pExpr.mMix64SBoxG.mName + ", " + pExpr.mMix64SBoxH.mName;
            if (Mix64Type8NeedsAmount(pExpr.mMix64Type8)) {
                return aCall + "(" + PrettyExpr(*pExpr.mA) + ", " +
                       std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)) + ", " +
                       aSBoxes + ")";
            }
            return aCall + "(" + PrettyExpr(*pExpr.mA) + ", " + aSBoxes + ")";
        }
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

std::string NormalizeCommentLine(const std::string &pComment) {
    if (pComment.empty()) {
        return "//";
    }
    if (pComment.rfind("//", 0U) == 0U) {
        return pComment;
    }
    return "// " + pComment;
}

void AppendBodyDecorations(const GLoop &pLoop,
                           std::size_t pStatementIndex,
                           int pIndentDepth,
                           std::vector<std::string> *pLines) {
    if (pLines == NULL) {
        return;
    }

    for (const GLoop::BodyDecoration &aDecoration : pLoop.mBodyDecorations) {
        if (aDecoration.mStatementIndex != pStatementIndex) {
            continue;
        }

        if (aDecoration.mType == GLoop::BodyDecoration::Type::kEmptyLine) {
            pLines->push_back("");
            continue;
        }

        pLines->push_back(Indent(pIndentDepth) + NormalizeCommentLine(aDecoration.mText));
    }
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
    for (std::size_t aStatementIndex = 0U; aStatementIndex < pLoop.mBodyStatements.size(); ++aStatementIndex) {
        AppendBodyDecorations(pLoop, aStatementIndex, 1, pLines);
        const GStatement &aStatement = pLoop.mBodyStatements[aStatementIndex];
        pLines->push_back(Indent(1) + PrettyStatement(aStatement));
    }
    AppendBodyDecorations(pLoop, pLoop.mBodyStatements.size(), 1, pLines);
    pLines->push_back("}");
}

std::string CppIndexForSlot(const TwistWorkSpaceSlot pSlot,
                            const GExpr *pIndexExpr,
                            const std::string &pIndexText,
                            const bool pIsRead) {
    auto HasEquivalentOrNarrowerAndMask = [](const GExpr *pExpr,
                                             const std::uint64_t pSlotMask,
                                             const auto &pSelf) -> bool {
        if ((pExpr == nullptr) || (pExpr->mType != GExprType::kAnd)) {
            return false;
        }

        auto IsMatchingMaskConst = [pSlotMask](const GExpr *pCandidate) -> bool {
            if ((pCandidate == nullptr) || (pCandidate->mType != GExprType::kConst)) {
                return false;
            }
            const std::uint64_t aMask = pCandidate->mConstVal;
            return (aMask & pSlotMask) == aMask;
        };

        if (IsMatchingMaskConst(pExpr->mA.get()) || IsMatchingMaskConst(pExpr->mB.get())) {
            return true;
        }

        return pSelf(pExpr->mA.get(), pSlotMask, pSelf) ||
               pSelf(pExpr->mB.get(), pSlotMask, pSelf);
    };

    auto StripTrivialZeroOffset = [](const GExpr *pExpr) -> const GExpr * {
        const GExpr *aCurrent = pExpr;
        while (aCurrent != nullptr) {
            if ((aCurrent->mType == GExprType::kAdd) &&
                (aCurrent->mA != nullptr) &&
                (aCurrent->mB != nullptr)) {
                const bool aLeftIsZero = (aCurrent->mA->mType == GExprType::kConst) &&
                                         (aCurrent->mA->mConstVal == 0ULL);
                const bool aRightIsZero = (aCurrent->mB->mType == GExprType::kConst) &&
                                          (aCurrent->mB->mConstVal == 0ULL);
                if (aLeftIsZero) {
                    aCurrent = aCurrent->mB.get();
                    continue;
                }
                if (aRightIsZero) {
                    aCurrent = aCurrent->mA.get();
                    continue;
                }
            } else if ((aCurrent->mType == GExprType::kSub) &&
                       (aCurrent->mA != nullptr) &&
                       (aCurrent->mB != nullptr) &&
                       (aCurrent->mB->mType == GExprType::kConst) &&
                       (aCurrent->mB->mConstVal == 0ULL)) {
                aCurrent = aCurrent->mA.get();
                continue;
            }
            break;
        }
        return aCurrent;
    };

    std::string aIndexText = pIndexText;
    bool aMaskedIndex = false;
    if (IsSaltSlot(pSlot)) {
        const bool aHasExplicitMask = HasEquivalentOrNarrowerAndMask(pIndexExpr, 0x7FULL, HasEquivalentOrNarrowerAndMask);
        if (!aHasExplicitMask) {
            aIndexText = "((" + aIndexText + ") & 0x7FU)";
        }
        aMaskedIndex = true;
    } else if (IsSBoxSlot(pSlot)) {
        const bool aHasExplicitMask = HasEquivalentOrNarrowerAndMask(pIndexExpr, 0xFFULL, HasEquivalentOrNarrowerAndMask);
        if (!aHasExplicitMask) {
            aIndexText = "((" + aIndexText + ") & 0xFFU)";
        }
        aMaskedIndex = true;
    }

    const bool aIsBlockSized = TwistWorkSpace::GetBufferLength(pSlot) == S_BLOCK;
    if (aIsBlockSized && (pIndexExpr != nullptr)) {
        const GExpr *aNormalizedIndexExpr = StripTrivialZeroOffset(pIndexExpr);
        if (aNormalizedIndexExpr != nullptr) {
            const bool aIsExactAIndex =
                (aNormalizedIndexExpr->mType == GExprType::kSymbol) &&
                aNormalizedIndexExpr->mSymbol.IsVar() &&
                (aNormalizedIndexExpr->mSymbol.mName == "aIndex");

            const GExpr *aInverseRightExpr = nullptr;
            if ((aNormalizedIndexExpr->mType == GExprType::kSub) &&
                (aNormalizedIndexExpr->mA != nullptr) &&
                (aNormalizedIndexExpr->mB != nullptr)) {
                aInverseRightExpr = StripTrivialZeroOffset(aNormalizedIndexExpr->mB.get());
            }
            const bool aIsExactSBlockInverseAIndex =
                (aNormalizedIndexExpr->mType == GExprType::kSub) &&
                (aNormalizedIndexExpr->mA != nullptr) &&
                (aNormalizedIndexExpr->mA->mType == GExprType::kConst) &&
                (aNormalizedIndexExpr->mA->mConstVal == static_cast<std::uint64_t>(S_BLOCK1)) &&
                (aInverseRightExpr != nullptr) &&
                (aInverseRightExpr->mType == GExprType::kSymbol) &&
                aInverseRightExpr->mSymbol.IsVar() &&
                (aInverseRightExpr->mSymbol.mName == "aIndex");
            if (aIsExactAIndex) {
                return "aIndex";
            }
            if (aIsExactSBlockInverseAIndex) {
                return "S_BLOCK1 - aIndex";
            }
        }
    }

    if (!pIsRead) {
        return aIndexText;
    }

    if (aMaskedIndex) {
        return aIndexText;
    }
    return "(" + aIndexText + ")";
}

enum class CppExprGroup : std::uint8_t {
    kNone = 0,
    kAddSub = 1,
    kMul = 2,
    kXor = 3,
    kAnd = 4,
    kOr = 5
};

CppExprGroup CppExprGroupForType(const GExprType pType) {
    switch (pType) {
        case GExprType::kAdd:
        case GExprType::kSub:
            return CppExprGroup::kAddSub;
        case GExprType::kMul:
            return CppExprGroup::kMul;
        case GExprType::kXor:
            return CppExprGroup::kXor;
        case GExprType::kAnd:
            return CppExprGroup::kAnd;
        case GExprType::kOr:
            return CppExprGroup::kOr;
        default:
            return CppExprGroup::kNone;
    }
}

std::string CppExprWithParent(const GExpr &pExpr,
                              CppExprGroup pParentGroup);

std::string CppUnsignedLiteral(const std::uint64_t pValue) {
    const std::string aValueText = std::to_string(static_cast<unsigned long long>(pValue));
    if (pValue > static_cast<std::uint64_t>(std::numeric_limits<std::int32_t>::max())) {
        return aValueText + "ULL";
    }
    return aValueText + "U";
}

std::string WrapForParentGroup(const GExpr &pExpr,
                               const CppExprGroup pParentGroup,
                               const std::string &pText) {
    if (pParentGroup == CppExprGroup::kNone) {
        return pText;
    }

    const CppExprGroup aExprGroup = CppExprGroupForType(pExpr.mType);
    if ((aExprGroup == CppExprGroup::kNone) || (aExprGroup == pParentGroup)) {
        return pText;
    }
    return "(" + pText + ")";
}

bool TryRenderInverseLoopIndexSub(const GExpr &pExpr,
                                  std::string *pText) {
    if ((pText == nullptr) ||
        (pExpr.mType != GExprType::kSub) ||
        (pExpr.mA == nullptr) ||
        (pExpr.mB == nullptr) ||
        (pExpr.mA->mType != GExprType::kConst) ||
        (pExpr.mB->mType != GExprType::kSymbol) ||
        !pExpr.mB->mSymbol.IsVar()) {
        return false;
    }

    const std::string &aName = pExpr.mB->mSymbol.mName;
    if ((aName != "i") && (aName.find("LoopIndex") == std::string::npos)) {
        return false;
    }

    if (pExpr.mA->mConstVal == S_BLOCK1) {
        *pText = "S_BLOCK1 - " + CppExprWithParent(*pExpr.mB, CppExprGroup::kAddSub);
        return true;
    }
    if (pExpr.mA->mConstVal == S_SALT1) {
        *pText = "S_SALT1 - " + CppExprWithParent(*pExpr.mB, CppExprGroup::kAddSub);
        return true;
    }
    if (pExpr.mA->mConstVal == S_SBOX1) {
        *pText = "S_SBOX1 - " + CppExprWithParent(*pExpr.mB, CppExprGroup::kAddSub);
        return true;
    }

    return false;
}

struct CppAddSubTerm {
    const GExpr                           *mExpr = nullptr;
    bool                                  mIsNegative = false;
};

void CollectAddSubTerms(const GExpr &pExpr,
                        const bool pIsNegative,
                        std::vector<CppAddSubTerm> *pTerms) {
    if (pTerms == nullptr) {
        return;
    }

    if (pExpr.mType == GExprType::kAdd) {
        if (pExpr.mA != nullptr) {
            CollectAddSubTerms(*pExpr.mA, pIsNegative, pTerms);
        }
        if (pExpr.mB != nullptr) {
            CollectAddSubTerms(*pExpr.mB, pIsNegative, pTerms);
        }
        return;
    }

    if (pExpr.mType == GExprType::kSub) {
        std::string aInverseText;
        if (TryRenderInverseLoopIndexSub(pExpr, &aInverseText)) {
            CppAddSubTerm aTerm;
            aTerm.mExpr = &pExpr;
            aTerm.mIsNegative = pIsNegative;
            pTerms->push_back(aTerm);
            return;
        }
        if (pExpr.mA != nullptr) {
            CollectAddSubTerms(*pExpr.mA, pIsNegative, pTerms);
        }
        if (pExpr.mB != nullptr) {
            CollectAddSubTerms(*pExpr.mB, !pIsNegative, pTerms);
        }
        return;
    }

    CppAddSubTerm aTerm;
    aTerm.mExpr = &pExpr;
    aTerm.mIsNegative = pIsNegative;
    pTerms->push_back(aTerm);
}

void CollectFlatTerms(const GExpr &pExpr,
                      const GExprType pType,
                      std::vector<const GExpr *> *pTerms) {
    if (pTerms == nullptr) {
        return;
    }

    if ((pExpr.mType == pType) &&
        (pExpr.mA != nullptr) &&
        (pExpr.mB != nullptr)) {
        CollectFlatTerms(*pExpr.mA, pType, pTerms);
        CollectFlatTerms(*pExpr.mB, pType, pTerms);
        return;
    }

    pTerms->push_back(&pExpr);
}

std::string RenderFlatExpr(const GExpr &pExpr,
                           const GExprType pType,
                           const CppExprGroup pCurrentGroup,
                           const CppExprGroup pParentGroup) {
    std::vector<const GExpr *> aTerms;
    CollectFlatTerms(pExpr, pType, &aTerms);
    if (aTerms.empty()) {
        return "0";
    }

    std::string aText;
    const std::string aOperator = " " + ScalarOperatorText(pType) + " ";

    // Preserve a small left-associated xor grouping shape used by MixBrew tests:
    // (x ^ y) ^ z
    if ((pType == GExprType::kXor) &&
        (aTerms.size() == 3U) &&
        (pExpr.mA != nullptr) &&
        (pExpr.mA->mType == GExprType::kXor) &&
        (pExpr.mB != nullptr) &&
        (pExpr.mB->mType != GExprType::kXor) &&
        (CppExprGroupForType(pExpr.mB->mType) != CppExprGroup::kNone) &&
        (aTerms[0] != nullptr) &&
        (aTerms[1] != nullptr) &&
        (aTerms[2] != nullptr)) {
        const std::string aLHS = CppExprWithParent(*aTerms[0], pCurrentGroup) +
                                 aOperator +
                                 CppExprWithParent(*aTerms[1], pCurrentGroup);
        aText = "(" + aLHS + ")" + aOperator + CppExprWithParent(*aTerms[2], pCurrentGroup);
    } else {
        for (std::size_t i = 0U; i < aTerms.size(); ++i) {
            if (aTerms[i] == nullptr) {
                continue;
            }
            if (!aText.empty()) {
                aText += aOperator;
            }
            aText += CppExprWithParent(*aTerms[i], pCurrentGroup);
        }
    }

    if (aText.empty()) {
        aText = "0";
    }
    return WrapForParentGroup(pExpr, pParentGroup, aText);
}

std::string RenderAddSubExpr(const GExpr &pExpr,
                             const CppExprGroup pParentGroup) {
    std::string aInverseText;
    if (TryRenderInverseLoopIndexSub(pExpr, &aInverseText)) {
        return WrapForParentGroup(pExpr, pParentGroup, aInverseText);
    }

    std::vector<CppAddSubTerm> aTerms;
    CollectAddSubTerms(pExpr, false, &aTerms);
    if (aTerms.empty()) {
        return "0";
    }

    std::size_t aNonZeroTermCount = 0U;
    for (const CppAddSubTerm &aTerm : aTerms) {
        if ((aTerm.mExpr == nullptr) ||
            ((aTerm.mExpr->mType == GExprType::kConst) && (aTerm.mExpr->mConstVal == 0ULL))) {
            continue;
        }
        aNonZeroTermCount += 1U;
    }
    if (aNonZeroTermCount == 0U) {
        return "0";
    }

    std::string aText;
    bool aHasOutputTerm = false;
    for (const CppAddSubTerm &aTerm : aTerms) {
        if (aTerm.mExpr == nullptr) {
            continue;
        }
        if ((aTerm.mExpr->mType == GExprType::kConst) && (aTerm.mExpr->mConstVal == 0ULL)) {
            continue;
        }

        const std::string aTermText = CppExprWithParent(*aTerm.mExpr, CppExprGroup::kAddSub);
        if (!aHasOutputTerm) {
            aText = aTerm.mIsNegative ? ("-" + aTermText) : aTermText;
            aHasOutputTerm = true;
            continue;
        }
        aText += aTerm.mIsNegative ? " - " : " + ";
        aText += aTermText;
    }
    if (aText.empty()) {
        aText = "0";
    }

    return WrapForParentGroup(pExpr, pParentGroup, aText);
}

std::string CppExprWithParent(const GExpr &pExpr,
                              const CppExprGroup pParentGroup) {
    const CppExprGroup aExprGroup = CppExprGroupForType(pExpr.mType);
    if (aExprGroup == CppExprGroup::kAddSub) {
        return RenderAddSubExpr(pExpr, pParentGroup);
    }
    if (aExprGroup == CppExprGroup::kMul) {
        return RenderFlatExpr(pExpr, GExprType::kMul, aExprGroup, pParentGroup);
    }
    if (aExprGroup == CppExprGroup::kXor) {
        return RenderFlatExpr(pExpr, GExprType::kXor, aExprGroup, pParentGroup);
    }
    if (aExprGroup == CppExprGroup::kAnd) {
        return RenderFlatExpr(pExpr, GExprType::kAnd, aExprGroup, pParentGroup);
    }
    if (aExprGroup == CppExprGroup::kOr) {
        return RenderFlatExpr(pExpr, GExprType::kOr, aExprGroup, pParentGroup);
    }

    switch (pExpr.mType) {
        case GExprType::kSymbol:
            if (pExpr.mSymbol.IsBuf()) {
                return BufAliasName(pExpr.mSymbol.mSlot) + "[0]";
            }
            return pExpr.mSymbol.mName;
        case GExprType::kConst:
            return CppUnsignedLiteral(pExpr.mConstVal);
        case GExprType::kRead: {
            const std::string aIndexText = (pExpr.mIndex != nullptr)
                                           ? CppExprWithParent(*pExpr.mIndex, CppExprGroup::kNone)
                                           : std::string("0");
            return BufAliasName(pExpr.mSymbol.mSlot) + "[" +
                   CppIndexForSlot(pExpr.mSymbol.mSlot, pExpr.mIndex.get(), aIndexText, true) + "]";
        }
        case GExprType::kShiftL:
            return "ShiftL64(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " +
                   CppExprWithParent(*pExpr.mB, CppExprGroup::kNone) + ")";
        case GExprType::kShiftR:
            return "ShiftR64(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " +
                   CppExprWithParent(*pExpr.mB, CppExprGroup::kNone) + ")";
        case GExprType::kRotL8:
            return "RotL8(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " +
                   CppExprWithParent(*pExpr.mB, CppExprGroup::kNone) + ")";
        case GExprType::kRotL32:
            return "RotL32(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " +
                   CppExprWithParent(*pExpr.mB, CppExprGroup::kNone) + ")";
        case GExprType::kRotL64:
            return "RotL64(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " +
                   CppExprWithParent(*pExpr.mB, CppExprGroup::kNone) + ")";
        case GExprType::kDiffuse64:
            return "TwistMix64::Diffuse(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ")";
        case GExprType::kMix64_1: {
            const std::string aCall = Mix64Type1CallToken(pExpr.mMix64Type1);
            if (aCall.empty() || !pExpr.mMix64SBoxA.IsBuf()) {
                return "0";
            }
            if (Mix64Type1NeedsAmount(pExpr.mMix64Type1)) {
                if (!pExpr.mMix64UseAmount) {
                    return "0";
                }
                return aCall + "(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " +
                       std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)) + "ULL, " +
                       BufAliasName(pExpr.mMix64SBoxA.mSlot) + ")";
            }
            return aCall + "(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " +
                   BufAliasName(pExpr.mMix64SBoxA.mSlot) + ")";
        }
        case GExprType::kMix64_4: {
            const std::string aCall = Mix64Type4CallToken(pExpr.mMix64Type4);
            if (aCall.empty() ||
                !pExpr.mMix64SBoxA.IsBuf() ||
                !pExpr.mMix64SBoxB.IsBuf() ||
                !pExpr.mMix64SBoxC.IsBuf() ||
                !pExpr.mMix64SBoxD.IsBuf()) {
                return "0";
            }
            const std::string aSBoxes = BufAliasName(pExpr.mMix64SBoxA.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxB.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxC.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxD.mSlot);
            if (Mix64Type4NeedsAmount(pExpr.mMix64Type4)) {
                if (!pExpr.mMix64UseAmount) {
                    return "0";
                }
                return aCall + "(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " +
                       std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)) + "ULL, " +
                       aSBoxes + ")";
            }
            return aCall + "(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " + aSBoxes + ")";
        }
        case GExprType::kMix64_8: {
            const std::string aCall = Mix64Type8CallToken(pExpr.mMix64Type8);
            if (aCall.empty() ||
                !pExpr.mMix64SBoxA.IsBuf() ||
                !pExpr.mMix64SBoxB.IsBuf() ||
                !pExpr.mMix64SBoxC.IsBuf() ||
                !pExpr.mMix64SBoxD.IsBuf() ||
                !pExpr.mMix64SBoxE.IsBuf() ||
                !pExpr.mMix64SBoxF.IsBuf() ||
                !pExpr.mMix64SBoxG.IsBuf() ||
                !pExpr.mMix64SBoxH.IsBuf()) {
                return "0";
            }
            const std::string aSBoxes = BufAliasName(pExpr.mMix64SBoxA.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxB.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxC.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxD.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxE.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxF.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxG.mSlot) + ", " +
                                        BufAliasName(pExpr.mMix64SBoxH.mSlot);
            if (Mix64Type8NeedsAmount(pExpr.mMix64Type8)) {
                if (!pExpr.mMix64UseAmount) {
                    return "0";
                }
                return aCall + "(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " +
                       std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)) + "ULL, " +
                       aSBoxes + ")";
            }
            return aCall + "(" + CppExprWithParent(*pExpr.mA, CppExprGroup::kNone) + ", " + aSBoxes + ")";
        }
        default:
            return "0";
    }
}

std::string CppExpr(const GExpr &pExpr) {
    return CppExprWithParent(pExpr, CppExprGroup::kNone);
}

std::string CppTarget(const GTarget &pTarget) {
    if (!pTarget.HasIndex()) {
        if (pTarget.IsBuf()) {
            return BufAliasName(pTarget.mSymbol.mSlot) + "[0]";
        }
        return pTarget.mSymbol.mName;
    }
    return BufAliasName(pTarget.mSymbol.mSlot) + "[" +
           CppIndexForSlot(pTarget.mSymbol.mSlot, pTarget.mIndex.get(), CppExpr(*pTarget.mIndex), false) + "]";
}

struct CppReadWrapMetadata {
    GReadWrapType                        mType = GReadWrapType::kNone;
    GSymbol                              mIndexSymbol;
    GSymbol                              mOracleSymbol;
    int                                  mOffset = 0;
};

bool CppWrapMetadataEqual(const CppReadWrapMetadata &pLeft,
                          const CppReadWrapMetadata &pRight) {
    return (pLeft.mType == pRight.mType) &&
           (pLeft.mIndexSymbol == pRight.mIndexSymbol) &&
           (pLeft.mOracleSymbol == pRight.mOracleSymbol) &&
           (pLeft.mOffset == pRight.mOffset);
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
            aMetadata.mOffset = pExpr.mReadWrapOffset;
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

std::string CppReadWrapTrimMaskToken(const GReadWrapType pType) {
    switch (pType) {
        case GReadWrapType::kBlock: return "0x1FFFU";
        case GReadWrapType::kSBox: return "0xFFU";
        case GReadWrapType::kSalt: return "0x7FU";
        case GReadWrapType::kMaskA: return "(S_MASK_A - 1U)";
        case GReadWrapType::kMaskB: return "(S_MASK_B - 1U)";
        case GReadWrapType::kKeyA: return "(S_KEY_A - 1U)";
        case GReadWrapType::kKeyB: return "(S_KEY_B - 1U)";
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
        const std::string aTrimMaskToken = CppReadWrapTrimMaskToken(aWrap.mType);
        const int aOffsetMagnitude = (aWrap.mOffset < 0) ? -aWrap.mOffset : aWrap.mOffset;
        const std::string aOffsetOp = (aWrap.mOffset < 0) ? " - " : " + ";

        aLines.push_back(aOracleName + " = " + aIndexName +
                         aOffsetOp + std::to_string(aOffsetMagnitude) + "U;");
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

bool SplitTopLevelOr(const std::string &pText,
                     std::string *pLeft,
                     std::string *pRight) {
    if ((pLeft == nullptr) || (pRight == nullptr)) {
        return false;
    }

    int aDepth = 0;
    for (std::size_t i = 0U; (i + 2U) <= pText.size(); ++i) {
        const char aChar = pText[i];
        if (aChar == '(') {
            aDepth += 1;
            continue;
        }
        if (aChar == ')') {
            aDepth -= 1;
            continue;
        }

        if ((aDepth == 0) &&
            (pText[i] == ' ') &&
            (i + 2U < pText.size()) &&
            (pText[i + 1U] == '|') &&
            (pText[i + 2U] == ' ')) {
            *pLeft = pText.substr(0U, i);
            *pRight = pText.substr(i + 3U);
            return true;
        }
    }

    return false;
}

void FlattenTopLevelOrTerms(const std::string &pText,
                            std::vector<std::string> *pTerms) {
    if (pTerms == nullptr) {
        return;
    }

    std::string aLeft;
    std::string aRight;
    const std::string aCandidate = StripOuterParens(pText);
    if (SplitTopLevelOr(aCandidate, &aLeft, &aRight)) {
        FlattenTopLevelOrTerms(aLeft, pTerms);
        FlattenTopLevelOrTerms(aRight, pTerms);
        return;
    }

    pTerms->push_back(aCandidate);
}

std::string FormatExpressionForCppStatement(const std::string &pExpressionText) {
    std::string aText = pExpressionText;

    // Keep packed nibble rebuild statements readable in generated C++.
    // Render as one OR term per line.
    if ((aText.find("NibbleA") != std::string::npos) &&
        (aText.find("NibbleB") != std::string::npos) &&
        (aText.find("NibbleC") != std::string::npos) &&
        (aText.find("NibbleD") != std::string::npos) &&
        (aText.find("<< 24U") != std::string::npos)) {
        std::vector<std::string> aTerms;
        FlattenTopLevelOrTerms(aText, &aTerms);
        if (aTerms.size() == 4U) {
            aText = StripOuterParens(aTerms[0]) +
                    " |\n\t\t" + StripOuterParens(aTerms[1]) +
                    " |\n\t\t" + StripOuterParens(aTerms[2]) +
                    " |\n\t\t" + StripOuterParens(aTerms[3]);
        }
    }

    return aText;
}

std::string CppStatement(const GStatement &pStatement) {
    const std::string aTargetText = CppTarget(pStatement.mTarget);
    const std::string aExpressionText =
        FormatExpressionForCppStatement(StripOuterParens(CppExpr(pStatement.mExpression)));
    return aTargetText + " = " + aExpressionText + ";";
}

std::vector<std::string> CppStatementLines(const GStatement &pStatement) {
    if (pStatement.IsRawLine()) {
        std::vector<std::string> aLines{pStatement.mRawLine};
        if (!pStatement.mOutputPrefix.empty()) {
            aLines[0] = pStatement.mOutputPrefix + aLines[0];
        }
        return aLines;
    }
    std::vector<std::string> aLines = CppReadWrapPreludeLines(pStatement);
    aLines.push_back(CppStatement(pStatement));
    if (!pStatement.mOutputPrefix.empty()) {
        for (std::string &aLine : aLines) {
            aLine = pStatement.mOutputPrefix + aLine;
        }
    }
    return aLines;
}

bool EvaluateExpr(const GExpr &pExpr,
                  TwistWorkSpace *pWorkspace,
                  TwistExpander *pExpander,
                  std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                  GRuntimeScalar *pValue,
                  std::string *pErrorMessage) {
    if ((pVariables == NULL) || (pValue == NULL)) {
        SetError(pErrorMessage, "Expression evaluation output was null.");
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
                    SetError(pErrorMessage, "Workspace was null during buffer read.");
                    return false;
                }
                std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mSymbol.mSlot);
                if (aBuffer == NULL) {
                    SetError(pErrorMessage, "Buffer symbol resolved to null.");
                    return false;
                }
                *pValue = static_cast<GRuntimeScalar>(aBuffer[0]);
                return true;
            }
            break;

        case GExprType::kConst:
            *pValue = static_cast<GRuntimeScalar>(pExpr.mConstVal);
            return true;

        case GExprType::kRead: {
            if (pWorkspace == NULL) {
                SetError(pErrorMessage, "Workspace was null during read.");
                return false;
            }
            GRuntimeScalar aIndexValue = 0ULL;
            if (pExpr.mReadWrapType != GReadWrapType::kNone) {
                GRuntimeScalar aBaseIndexValue = 0ULL;
                if (pExpr.mReadWrapIndexSymbol.IsVar()) {
                    const auto aBaseIterator = pVariables->find(pExpr.mReadWrapIndexSymbol.mName);
                    aBaseIndexValue = (aBaseIterator == pVariables->end()) ? 0ULL : aBaseIterator->second;
                } else if (pExpr.mReadWrapIndexSymbol.IsBuf()) {
                    std::uint8_t *aBaseBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mReadWrapIndexSymbol.mSlot);
                    if (aBaseBuffer == NULL) {
                        SetError(pErrorMessage, "Read wrap index buffer was null.");
                        return false;
                    }
                    aBaseIndexValue = static_cast<GRuntimeScalar>(aBaseBuffer[0]);
                } else {
                    SetError(pErrorMessage, "Read wrap index symbol was invalid.");
                    return false;
                }

                const std::int64_t aOracleSigned = static_cast<std::int64_t>(aBaseIndexValue) +
                                                   static_cast<std::int64_t>(pExpr.mReadWrapOffset);
                GRuntimeScalar aOracleValue = static_cast<GRuntimeScalar>(aOracleSigned);
                const unsigned int aWrapTrimMask = ReadWrapTrimMaskForType(pExpr.mReadWrapType);
                if (aWrapTrimMask != 0U) {
                    aOracleValue = static_cast<GRuntimeScalar>(aOracleValue & static_cast<GRuntimeScalar>(aWrapTrimMask));
                }
                aIndexValue = aOracleValue;

                if (pExpr.mReadWrapOracleSymbol.IsVar()) {
                    (*pVariables)[pExpr.mReadWrapOracleSymbol.mName] = aOracleValue;
                }
            } else {
                if ((pExpr.mIndex == NULL) ||
                    !EvaluateExpr(*pExpr.mIndex, pWorkspace, pExpander, pVariables, &aIndexValue, pErrorMessage)) {
                    SetError(pErrorMessage, "Read expression index was invalid.");
                    return false;
                }
            }
            std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mSymbol.mSlot);
            if (aBuffer == NULL) {
                SetError(pErrorMessage, "Read expression buffer was null.");
                return false;
            }
            const std::size_t aIndex = RuntimeIndexForSlot(pExpr.mSymbol.mSlot, aIndexValue);
            *pValue = ReadRuntimeBufferValue(pExpr.mSymbol.mSlot, aBuffer, aIndex);
            return true;
        }
        case GExprType::kDiffuse64: {
            if (pExpr.mA == NULL) {
                SetError(pErrorMessage, "Diffuse64 expression was missing an input child.");
                return false;
            }
            GRuntimeScalar aInputValue = 0ULL;
            if (!EvaluateExpr(*pExpr.mA, pWorkspace, pExpander, pVariables, &aInputValue, pErrorMessage)) {
                SetError(pErrorMessage, "Diffuse64 input expression was invalid.");
                return false;
            }
            *pValue = static_cast<GRuntimeScalar>(
                TwistMix64::Diffuse(static_cast<std::uint64_t>(aInputValue)));
            return true;
        }
        case GExprType::kMix64_1: {
            if ((pExpr.mA == NULL) || !pExpr.mMix64SBoxA.IsBuf()) {
                SetError(pErrorMessage, "Mix64_1 expression metadata was invalid.");
                return false;
            }

            if (Mix64Type1NeedsAmount(pExpr.mMix64Type1) && !pExpr.mMix64UseAmount) {
                SetError(pErrorMessage, "Mix64_1 amount was required but missing.");
                return false;
            }

            GRuntimeScalar aInputValue = 0ULL;
            if (!EvaluateExpr(*pExpr.mA, pWorkspace, pExpander, pVariables, &aInputValue, pErrorMessage)) {
                SetError(pErrorMessage, "Mix64_1 input expression was invalid.");
                return false;
            }

            std::uint8_t *aSBoxA = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxA.mSlot);
            if (aSBoxA == NULL) {
                SetError(pErrorMessage, "Mix64_1 S-box buffer resolved to null.");
                return false;
            }

            const std::uint64_t aResult = EvaluateMix64Type1Local(
                pExpr.mMix64Type1,
                static_cast<std::uint64_t>(aInputValue),
                pExpr.mMix64Amount,
                aSBoxA);
            *pValue = static_cast<GRuntimeScalar>(aResult);
            return true;
        }
        case GExprType::kMix64_4: {
            if ((pExpr.mA == NULL) ||
                !pExpr.mMix64SBoxA.IsBuf() ||
                !pExpr.mMix64SBoxB.IsBuf() ||
                !pExpr.mMix64SBoxC.IsBuf() ||
                !pExpr.mMix64SBoxD.IsBuf()) {
                SetError(pErrorMessage, "Mix64_4 expression metadata was invalid.");
                return false;
            }

            if (Mix64Type4NeedsAmount(pExpr.mMix64Type4) && !pExpr.mMix64UseAmount) {
                SetError(pErrorMessage, "Mix64_4 amount was required but missing.");
                return false;
            }

            GRuntimeScalar aInputValue = 0ULL;
            if (!EvaluateExpr(*pExpr.mA, pWorkspace, pExpander, pVariables, &aInputValue, pErrorMessage)) {
                SetError(pErrorMessage, "Mix64_4 input expression was invalid.");
                return false;
            }

            std::uint8_t *aSBoxA = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxA.mSlot);
            std::uint8_t *aSBoxB = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxB.mSlot);
            std::uint8_t *aSBoxC = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxC.mSlot);
            std::uint8_t *aSBoxD = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxD.mSlot);
            if ((aSBoxA == NULL) || (aSBoxB == NULL) || (aSBoxC == NULL) || (aSBoxD == NULL)) {
                SetError(pErrorMessage, "Mix64_4 S-box buffer resolved to null.");
                return false;
            }

            const std::uint64_t aResult = EvaluateMix64Type4Local(
                pExpr.mMix64Type4,
                static_cast<std::uint64_t>(aInputValue),
                pExpr.mMix64Amount,
                aSBoxA,
                aSBoxB,
                aSBoxC,
                aSBoxD);
            *pValue = static_cast<GRuntimeScalar>(aResult);
            return true;
        }
        case GExprType::kMix64_8: {
            if ((pExpr.mA == NULL) ||
                !pExpr.mMix64SBoxA.IsBuf() ||
                !pExpr.mMix64SBoxB.IsBuf() ||
                !pExpr.mMix64SBoxC.IsBuf() ||
                !pExpr.mMix64SBoxD.IsBuf() ||
                !pExpr.mMix64SBoxE.IsBuf() ||
                !pExpr.mMix64SBoxF.IsBuf() ||
                !pExpr.mMix64SBoxG.IsBuf() ||
                !pExpr.mMix64SBoxH.IsBuf()) {
                SetError(pErrorMessage, "Mix64_8 expression metadata was invalid.");
                return false;
            }

            if (Mix64Type8NeedsAmount(pExpr.mMix64Type8) && !pExpr.mMix64UseAmount) {
                SetError(pErrorMessage, "Mix64_8 amount was required but missing.");
                return false;
            }

            GRuntimeScalar aInputValue = 0ULL;
            if (!EvaluateExpr(*pExpr.mA, pWorkspace, pExpander, pVariables, &aInputValue, pErrorMessage)) {
                SetError(pErrorMessage, "Mix64_8 input expression was invalid.");
                return false;
            }

            std::uint8_t *aSBoxA = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxA.mSlot);
            std::uint8_t *aSBoxB = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxB.mSlot);
            std::uint8_t *aSBoxC = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxC.mSlot);
            std::uint8_t *aSBoxD = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxD.mSlot);
            std::uint8_t *aSBoxE = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxE.mSlot);
            std::uint8_t *aSBoxF = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxF.mSlot);
            std::uint8_t *aSBoxG = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxG.mSlot);
            std::uint8_t *aSBoxH = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pExpr.mMix64SBoxH.mSlot);
            if ((aSBoxA == NULL) || (aSBoxB == NULL) || (aSBoxC == NULL) || (aSBoxD == NULL) ||
                (aSBoxE == NULL) || (aSBoxF == NULL) || (aSBoxG == NULL) || (aSBoxH == NULL)) {
                SetError(pErrorMessage, "Mix64_8 S-box buffer resolved to null.");
                return false;
            }

            const std::uint64_t aResult = EvaluateMix64Type8Local(
                pExpr.mMix64Type8,
                static_cast<std::uint64_t>(aInputValue),
                pExpr.mMix64Amount,
                aSBoxA,
                aSBoxB,
                aSBoxC,
                aSBoxD,
                aSBoxE,
                aSBoxF,
                aSBoxG,
                aSBoxH);
            *pValue = static_cast<GRuntimeScalar>(aResult);
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
                !EvaluateExpr(*pExpr.mA, pWorkspace, pExpander, pVariables, &aLeft, pErrorMessage) ||
                !EvaluateExpr(*pExpr.mB, pWorkspace, pExpander, pVariables, &aRight, pErrorMessage)) {
                SetError(pErrorMessage, "Binary expression child was invalid.");
                return false;
            }
            switch (pExpr.mType) {
                case GExprType::kAdd: *pValue = aLeft + aRight; return true;
                case GExprType::kSub: *pValue = aLeft - aRight; return true;
                case GExprType::kMul: *pValue = aLeft * aRight; return true;
                case GExprType::kXor: *pValue = aLeft ^ aRight; return true;
                case GExprType::kAnd: *pValue = aLeft & aRight; return true;
                case GExprType::kOr: *pValue = aLeft | aRight; return true;
                case GExprType::kRotL8:
                    *pValue = static_cast<GRuntimeScalar>(
                        RotL8(static_cast<std::uint8_t>(aLeft),
                              static_cast<std::uint8_t>(aRight)));
                    return true;
                case GExprType::kRotL32:
                    *pValue = static_cast<GRuntimeScalar>(
                        RotL32(static_cast<std::uint32_t>(aLeft),
                               static_cast<std::uint32_t>(aRight)));
                    return true;
                case GExprType::kRotL64:
                    *pValue = static_cast<GRuntimeScalar>(
                        RotL64(static_cast<std::uint64_t>(aLeft),
                               static_cast<std::uint64_t>(aRight)));
                    return true;
                case GExprType::kShiftL:
                    *pValue = static_cast<GRuntimeScalar>(
                        ShiftL64(static_cast<std::uint64_t>(aLeft),
                                 static_cast<std::uint64_t>(aRight)));
                    return true;
                case GExprType::kShiftR:
                    *pValue = static_cast<GRuntimeScalar>(
                        ShiftR64(static_cast<std::uint64_t>(aLeft),
                                 static_cast<std::uint64_t>(aRight)));
                    return true;
                default: break;
            }
            break;
        }

        default:
            break;
    }

    SetError(pErrorMessage, "Expression type could not be evaluated.");
    return false;
}

bool ExecuteStatement(const GStatement &pStatement,
                      TwistWorkSpace *pWorkspace,
                      TwistExpander *pExpander,
                      std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                      std::string *pErrorMessage) {
    if (pStatement.IsRawLine()) {
        return true;
    }

    GRuntimeScalar aExpressionValue = 0ULL;
    if (!EvaluateExpr(pStatement.mExpression, pWorkspace, pExpander, pVariables, &aExpressionValue, pErrorMessage)) {
        return false;
    }

    if (pStatement.mTarget.IsVar()) {
        GRuntimeScalar &aTargetValue = (*pVariables)[pStatement.mTarget.mSymbol.mName];
        switch (pStatement.mAssignType) {
            case GAssignType::kSet:
                aTargetValue = NormalizeScalarValueForName(pStatement.mTarget.mSymbol.mName, aExpressionValue);
                return true;
            default:
                SetError(pErrorMessage, "Variable assignment type was invalid.");
                return false;
        }
    }

    if (pStatement.mTarget.IsBuf()) {
        if (pWorkspace == NULL) {
            SetError(pErrorMessage, "Workspace was null during write.");
            return false;
        }
        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pStatement.mTarget.mSymbol.mSlot);
        if (aBuffer == NULL) {
            SetError(pErrorMessage, "Write buffer was null.");
            return false;
        }
        GRuntimeScalar aIndexValue = 0ULL;
        if (pStatement.mTarget.mIndex != nullptr &&
            !EvaluateExpr(*pStatement.mTarget.mIndex, pWorkspace, pExpander, pVariables, &aIndexValue, pErrorMessage)) {
            return false;
        }

        const std::size_t aIndex = RuntimeIndexForSlot(pStatement.mTarget.mSymbol.mSlot, aIndexValue);

        switch (pStatement.mAssignType) {
            case GAssignType::kSet:
                WriteRuntimeBufferValue(pStatement.mTarget.mSymbol.mSlot,
                                        aBuffer,
                                        aIndex,
                                        aExpressionValue);
                return true;
            default:
                SetError(pErrorMessage, "Buffer assignment type was invalid.");
                return false;
        }
    }

    SetError(pErrorMessage, "Statement target was invalid.");
    return false;
}

std::string TrimCopy(const std::string &pText) {
    std::size_t aBegin = 0U;
    while (aBegin < pText.size() && std::isspace(static_cast<unsigned char>(pText[aBegin]))) {
        ++aBegin;
    }

    std::size_t aEnd = pText.size();
    while (aEnd > aBegin && std::isspace(static_cast<unsigned char>(pText[aEnd - 1U]))) {
        --aEnd;
    }

    return pText.substr(aBegin, aEnd - aBegin);
}

bool IsIdentifierToken(const std::string &pText) {
    if (pText.empty()) {
        return false;
    }

    const unsigned char aHead = static_cast<unsigned char>(pText[0]);
    if (!(std::isalpha(aHead) || pText[0] == '_')) {
        return false;
    }

    for (char aChar : pText) {
        const unsigned char aValue = static_cast<unsigned char>(aChar);
        if (!(std::isalnum(aValue) || (aChar == '_'))) {
            return false;
        }
    }
    return true;
}

bool ParseIntLiteralToken(const std::string &pText,
                          int *pValue) {
    if (pValue == NULL) {
        return false;
    }

    std::string aToken = TrimCopy(pText);
    if (aToken.empty()) {
        return false;
    }

    while (!aToken.empty() && ((aToken.back() == 'U') || (aToken.back() == 'u') ||
                               (aToken.back() == 'L') || (aToken.back() == 'l'))) {
        aToken.pop_back();
    }
    if (aToken.empty()) {
        return false;
    }

    char *aEnd = NULL;
    const long aValue = std::strtol(aToken.c_str(), &aEnd, 0);
    if ((aEnd == aToken.c_str()) || (*aEnd != '\0')) {
        return false;
    }
    if ((aValue < std::numeric_limits<int>::min()) ||
        (aValue > std::numeric_limits<int>::max())) {
        return false;
    }

    *pValue = static_cast<int>(aValue);
    return true;
}

enum class ControlLineType : std::uint8_t {
    kNone = 0,
    kIf = 1,
    kElse = 2,
    kEnd = 3
};

struct ParsedControlLine {
    ControlLineType                 mType = ControlLineType::kNone;
    std::string                     mCondition;
};

bool ParseControlLine(const std::string &pRawLine,
                      ParsedControlLine *pParsed) {
    if (pParsed == NULL) {
        return false;
    }

    ParsedControlLine aLine;
    const std::string aText = TrimCopy(pRawLine);
    if (aText.empty()) {
        *pParsed = aLine;
        return true;
    }

    if ((aText == "else {") || (aText == "} else {")) {
        aLine.mType = ControlLineType::kElse;
        *pParsed = aLine;
        return true;
    }

    if (aText == "}") {
        aLine.mType = ControlLineType::kEnd;
        *pParsed = aLine;
        return true;
    }

    if (aText.rfind("if", 0U) == 0U) {
        const std::size_t aOpenParen = aText.find('(');
        const std::size_t aCloseParen = aText.rfind(')');
        const std::size_t aOpenBrace = aText.rfind('{');
        if ((aOpenParen == std::string::npos) ||
            (aCloseParen == std::string::npos) ||
            (aOpenBrace == std::string::npos) ||
            (aCloseParen <= aOpenParen) ||
            (aOpenBrace <= aCloseParen)) {
            return false;
        }

        aLine.mType = ControlLineType::kIf;
        aLine.mCondition = TrimCopy(aText.substr(aOpenParen + 1U, aCloseParen - aOpenParen - 1U));
        *pParsed = aLine;
        return true;
    }

    *pParsed = aLine;
    return true;
}

bool EvaluateControlOperand(const std::string &pText,
                            std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                            int *pValue) {
    if ((pVariables == NULL) || (pValue == NULL)) {
        return false;
    }

    const std::string aToken = TrimCopy(pText);
    if (aToken.empty()) {
        return false;
    }

    int aLiteral = 0;
    if (ParseIntLiteralToken(aToken, &aLiteral)) {
        *pValue = aLiteral;
        return true;
    }

    if (!IsIdentifierToken(aToken)) {
        return false;
    }

    const auto aIterator = pVariables->find(aToken);
    *pValue = (aIterator == pVariables->end()) ? 0 : static_cast<int>(aIterator->second);
    return true;
}

bool ResolveAliasBufferSlot(const std::string &pAlias,
                            TwistWorkSpaceSlot *pSlot) {
    if (pSlot == nullptr) {
        return false;
    }

    static const TwistWorkSpaceSlot kSlots[] = {
        TwistWorkSpaceSlot::kSource,
        TwistWorkSpaceSlot::kDest,

        TwistWorkSpaceSlot::kSaltA,
        TwistWorkSpaceSlot::kSaltB,
        TwistWorkSpaceSlot::kSaltC,
        TwistWorkSpaceSlot::kSaltD,
        TwistWorkSpaceSlot::kScratchSaltA,
        TwistWorkSpaceSlot::kScratchSaltB,
        TwistWorkSpaceSlot::kScratchSaltC,
        TwistWorkSpaceSlot::kScratchSaltD,
        TwistWorkSpaceSlot::kDerivedSaltA,
        TwistWorkSpaceSlot::kDerivedSaltB,
        TwistWorkSpaceSlot::kDerivedSaltC,
        TwistWorkSpaceSlot::kDerivedSaltD,
        TwistWorkSpaceSlot::kDerivedSaltE,
        TwistWorkSpaceSlot::kDerivedSaltF,
        TwistWorkSpaceSlot::kDerivedSaltG,
        TwistWorkSpaceSlot::kDerivedSaltH,

        TwistWorkSpaceSlot::kSBoxA,
        TwistWorkSpaceSlot::kSBoxB,
        TwistWorkSpaceSlot::kSBoxC,
        TwistWorkSpaceSlot::kSBoxD,
        TwistWorkSpaceSlot::kDerivedSBoxA,
        TwistWorkSpaceSlot::kDerivedSBoxB,
        TwistWorkSpaceSlot::kDerivedSBoxC,
        TwistWorkSpaceSlot::kDerivedSBoxD,
        TwistWorkSpaceSlot::kDerivedSBoxE,
        TwistWorkSpaceSlot::kDerivedSBoxF,
        TwistWorkSpaceSlot::kDerivedSBoxG,
        TwistWorkSpaceSlot::kDerivedSBoxH,

        TwistWorkSpaceSlot::kSeedExpansionLaneA,
        TwistWorkSpaceSlot::kSeedExpansionLaneB,
        TwistWorkSpaceSlot::kSeedExpansionLaneC,
        TwistWorkSpaceSlot::kSeedExpansionLaneD,

        TwistWorkSpaceSlot::kWorkLaneA,
        TwistWorkSpaceSlot::kWorkLaneB,
        TwistWorkSpaceSlot::kWorkLaneC,
        TwistWorkSpaceSlot::kWorkLaneD,

        TwistWorkSpaceSlot::kOperationLaneA,
        TwistWorkSpaceSlot::kOperationLaneB,

        TwistWorkSpaceSlot::kMaskLaneA,
        TwistWorkSpaceSlot::kMaskLaneB,

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
        TwistWorkSpaceSlot::kMaskRowWriteB
    };

    for (TwistWorkSpaceSlot aSlot : kSlots) {
        if (BufAliasName(aSlot) == pAlias) {
            *pSlot = aSlot;
            return true;
        }
    }

    return false;
}

bool ParseMatrixBufferOffsetExpression(const std::string &pText,
                                       std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                       TwistWorkSpaceSlot *pSlot,
                                       int *pOffset,
                                       std::string *pErrorMessage) {
    if ((pSlot == nullptr) || (pOffset == nullptr)) {
        SetError(pErrorMessage, "Matrix buffer expression output was null.");
        return false;
    }
    if (pVariables == nullptr) {
        SetError(pErrorMessage, "Matrix buffer expression variable map was null.");
        return false;
    }

    const std::string aText = TrimCopy(pText);
    if (aText.empty()) {
        SetError(pErrorMessage, "Matrix buffer expression was empty.");
        return false;
    }

    const std::size_t aPlusPos = aText.find('+');
    const std::string aAlias = TrimCopy((aPlusPos == std::string::npos) ? aText : aText.substr(0U, aPlusPos));
    if (!ResolveAliasBufferSlot(aAlias, pSlot)) {
        SetError(pErrorMessage, "Unknown matrix buffer alias: " + aAlias);
        return false;
    }

    if (aPlusPos == std::string::npos) {
        *pOffset = 0;
        return true;
    }

    const std::string aOffsetText = TrimCopy(aText.substr(aPlusPos + 1U));
    int aOffset = 0;
    if (!EvaluateControlOperand(aOffsetText, pVariables, &aOffset)) {
        SetError(pErrorMessage, "Matrix buffer offset token was invalid: " + aOffsetText);
        return false;
    }
    if (aOffset < 0) {
        SetError(pErrorMessage, "Matrix buffer offset cannot be negative.");
        return false;
    }

    *pOffset = aOffset;
    return true;
}

std::vector<std::string> SplitCommaTokens(const std::string &pText) {
    std::vector<std::string> aResult;
    std::size_t aStart = 0U;
    while (aStart <= pText.size()) {
        const std::size_t aComma = pText.find(',', aStart);
        if (aComma == std::string::npos) {
            aResult.push_back(TrimCopy(pText.substr(aStart)));
            break;
        }
        aResult.push_back(TrimCopy(pText.substr(aStart, aComma - aStart)));
        aStart = aComma + 1U;
    }
    return aResult;
}

bool SplitBufferElementToken(const std::string &pText,
                             std::string *pAliasToken,
                             std::string *pIndexToken) {
    if ((pAliasToken == nullptr) || (pIndexToken == nullptr)) {
        return false;
    }

    const std::string aText = TrimCopy(pText);
    const std::size_t aOpenPos = aText.find('[');
    const std::size_t aClosePos = aText.rfind(']');
    if ((aOpenPos == std::string::npos) ||
        (aClosePos == std::string::npos) ||
        (aClosePos <= aOpenPos) ||
        (aClosePos + 1U != aText.size())) {
        return false;
    }

    const std::string aAlias = TrimCopy(aText.substr(0U, aOpenPos));
    const std::string aIndex = TrimCopy(aText.substr(aOpenPos + 1U, aClosePos - aOpenPos - 1U));
    if (aAlias.empty() || aIndex.empty()) {
        return false;
    }

    *pAliasToken = aAlias;
    *pIndexToken = aIndex;
    return true;
}

std::size_t FindTopLevelChar(const std::string &pText,
                             const char pChar) {
    int aParenDepth = 0;
    int aBracketDepth = 0;
    for (std::size_t i = 0U; i < pText.size(); ++i) {
        const char aChar = pText[i];
        if (aChar == '(') {
            aParenDepth += 1;
            continue;
        }
        if (aChar == ')') {
            aParenDepth -= 1;
            continue;
        }
        if (aChar == '[') {
            aBracketDepth += 1;
            continue;
        }
        if (aChar == ']') {
            aBracketDepth -= 1;
            continue;
        }
        if ((aParenDepth == 0) && (aBracketDepth == 0) && (aChar == pChar)) {
            return i;
        }
    }
    return std::string::npos;
}

bool StripOneOuterParenPair(std::string *pText) {
    if (pText == nullptr) {
        return false;
    }
    if (pText->size() < 2U) {
        return false;
    }
    if ((pText->front() != '(') || (pText->back() != ')')) {
        return false;
    }

    int aParenDepth = 0;
    int aBracketDepth = 0;
    for (std::size_t i = 0U; i < pText->size(); ++i) {
        const char aChar = (*pText)[i];
        if (aChar == '(') {
            aParenDepth += 1;
        } else if (aChar == ')') {
            aParenDepth -= 1;
            if (aParenDepth < 0) {
                return false;
            }
            if ((aParenDepth == 0) && (aBracketDepth == 0) && (i + 1U < pText->size())) {
                return false;
            }
        } else if (aChar == '[') {
            aBracketDepth += 1;
        } else if (aChar == ']') {
            aBracketDepth -= 1;
            if (aBracketDepth < 0) {
                return false;
            }
        }
    }
    if ((aParenDepth != 0) || (aBracketDepth != 0)) {
        return false;
    }
    *pText = TrimCopy(pText->substr(1U, pText->size() - 2U));
    return true;
}

bool IsUnarySignOperator(const std::string &pText,
                         const std::size_t pPos) {
    if (pPos >= pText.size()) {
        return false;
    }
    std::size_t aPrev = pPos;
    while ((aPrev > 0U) &&
           (std::isspace(static_cast<unsigned char>(pText[aPrev - 1U])) != 0)) {
        --aPrev;
    }
    if (aPrev == 0U) {
        return true;
    }
    const char aPrevChar = pText[aPrev - 1U];
    switch (aPrevChar) {
        case '(':
        case '[':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
        case '&':
        case '|':
        case '<':
        case '>':
        case '=':
        case '!':
        case '~':
        case '?':
        case ':':
            return true;
        default:
            return false;
    }
}

std::size_t FindTopLevelOperatorChar(const std::string &pText,
                                     const char pChar,
                                     const bool pTreatUnarySignAsNonOperator) {
    int aParenDepth = 0;
    int aBracketDepth = 0;
    std::size_t aFound = std::string::npos;
    for (std::size_t i = 0U; i < pText.size(); ++i) {
        const char aChar = pText[i];
        if (aChar == '(') {
            aParenDepth += 1;
            continue;
        }
        if (aChar == ')') {
            aParenDepth -= 1;
            continue;
        }
        if (aChar == '[') {
            aBracketDepth += 1;
            continue;
        }
        if (aChar == ']') {
            aBracketDepth -= 1;
            continue;
        }
        if ((aParenDepth != 0) || (aBracketDepth != 0) || (aChar != pChar)) {
            continue;
        }
        if (pTreatUnarySignAsNonOperator &&
            ((pChar == '+') || (pChar == '-')) &&
            IsUnarySignOperator(pText, i)) {
            continue;
        }
        aFound = i;
    }
    return aFound;
}

std::size_t FindTopLevelShiftOperator(const std::string &pText,
                                      bool *pIsRightShift) {
    if (pIsRightShift == nullptr) {
        return std::string::npos;
    }
    int aParenDepth = 0;
    int aBracketDepth = 0;
    std::size_t aFound = std::string::npos;
    bool aFoundRightShift = false;
    for (std::size_t i = 0U; i + 1U < pText.size(); ++i) {
        const char aChar = pText[i];
        if (aChar == '(') {
            aParenDepth += 1;
            continue;
        }
        if (aChar == ')') {
            aParenDepth -= 1;
            continue;
        }
        if (aChar == '[') {
            aBracketDepth += 1;
            continue;
        }
        if (aChar == ']') {
            aBracketDepth -= 1;
            continue;
        }
        if ((aParenDepth != 0) || (aBracketDepth != 0)) {
            continue;
        }
        if ((pText[i] == '<') && (pText[i + 1U] == '<')) {
            aFound = i;
            aFoundRightShift = false;
            ++i;
            continue;
        }
        if ((pText[i] == '>') && (pText[i + 1U] == '>')) {
            aFound = i;
            aFoundRightShift = true;
            ++i;
            continue;
        }
    }
    if (aFound != std::string::npos) {
        *pIsRightShift = aFoundRightShift;
    }
    return aFound;
}

bool FindTopLevelComparisonOperator(const std::string &pCondition,
                                    std::size_t *pOperatorPos,
                                    std::size_t *pOperatorLength,
                                    std::string *pOperatorText) {
    if ((pOperatorPos == nullptr) ||
        (pOperatorLength == nullptr) ||
        (pOperatorText == nullptr)) {
        return false;
    }

    int aParenDepth = 0;
    int aBracketDepth = 0;
    for (std::size_t i = 0U; i < pCondition.size(); ++i) {
        const char aChar = pCondition[i];
        if (aChar == '(') {
            aParenDepth += 1;
            continue;
        }
        if (aChar == ')') {
            aParenDepth -= 1;
            continue;
        }
        if (aChar == '[') {
            aBracketDepth += 1;
            continue;
        }
        if (aChar == ']') {
            aBracketDepth -= 1;
            continue;
        }
        if ((aParenDepth != 0) || (aBracketDepth != 0)) {
            continue;
        }

        if (i + 1U < pCondition.size()) {
            const char aNext = pCondition[i + 1U];
            if (((aChar == '>') || (aChar == '<') || (aChar == '=') || (aChar == '!')) && (aNext == '=')) {
                *pOperatorPos = i;
                *pOperatorLength = 2U;
                *pOperatorText = pCondition.substr(i, 2U);
                return true;
            }
            if (((aChar == '>') && (aNext == '>')) ||
                ((aChar == '<') && (aNext == '<'))) {
                ++i;
                continue;
            }
        }
        if ((aChar == '>') || (aChar == '<')) {
            *pOperatorPos = i;
            *pOperatorLength = 1U;
            *pOperatorText = pCondition.substr(i, 1U);
            return true;
        }
    }
    return false;
}

enum class GRawAssignType : std::uint8_t {
    kSet = 0,
    kAddAssign = 1,
    kXorAssign = 2
};

bool FindTopLevelAssignOperator(const std::string &pText,
                                std::size_t *pPos,
                                std::size_t *pLength,
                                GRawAssignType *pAssignType) {
    if ((pPos == nullptr) || (pLength == nullptr) || (pAssignType == nullptr)) {
        return false;
    }

    int aParenDepth = 0;
    int aBracketDepth = 0;
    for (std::size_t i = 0U; i < pText.size(); ++i) {
        const char aChar = pText[i];
        if (aChar == '(') {
            aParenDepth += 1;
            continue;
        }
        if (aChar == ')') {
            aParenDepth -= 1;
            continue;
        }
        if (aChar == '[') {
            aBracketDepth += 1;
            continue;
        }
        if (aChar == ']') {
            aBracketDepth -= 1;
            continue;
        }
        if ((aParenDepth != 0) || (aBracketDepth != 0)) {
            continue;
        }

        if ((i + 1U < pText.size()) && (pText[i] == '^') && (pText[i + 1U] == '=')) {
            *pPos = i;
            *pLength = 2U;
            *pAssignType = GRawAssignType::kXorAssign;
            return true;
        }
        if ((i + 1U < pText.size()) && (pText[i] == '+') && (pText[i + 1U] == '=')) {
            *pPos = i;
            *pLength = 2U;
            *pAssignType = GRawAssignType::kAddAssign;
            return true;
        }
        if (pText[i] == '=') {
            const char aPrev = (i > 0U) ? pText[i - 1U] : '\0';
            const char aNext = (i + 1U < pText.size()) ? pText[i + 1U] : '\0';
            if ((aPrev == '=') || (aPrev == '!') || (aPrev == '<') || (aPrev == '>') ||
                (aNext == '=')) {
                continue;
            }
            *pPos = i;
            *pLength = 1U;
            *pAssignType = GRawAssignType::kSet;
            return true;
        }
    }
    return false;
}

bool EvaluateGenericRawExpression(const std::string &pExpression,
                                  TwistWorkSpace *pWorkspace,
                                  TwistExpander *pExpander,
                                  std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                  GRuntimeScalar *pValue,
                                  std::string *pErrorMessage);

bool EvaluateGenericRawAtom(const std::string &pToken,
                            TwistWorkSpace *pWorkspace,
                            TwistExpander *pExpander,
                            std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                            GRuntimeScalar *pValue,
                            std::string *pErrorMessage) {
    if ((pVariables == nullptr) || (pValue == nullptr)) {
        SetError(pErrorMessage, "Generic raw-line atom output was null.");
        return false;
    }

    const std::string aToken = TrimCopy(pToken);
    if (aToken.empty()) {
        SetError(pErrorMessage, "Generic raw-line atom was empty.");
        return false;
    }

    const std::string kGateRollPrefix = "TwistMix64::GateRoll_1_1(";
    if ((aToken.rfind(kGateRollPrefix, 0U) == 0U) &&
        (aToken.size() > kGateRollPrefix.size()) &&
        (aToken.back() == ')')) {
        const std::string aArgsText = aToken.substr(kGateRollPrefix.size(),
                                                    aToken.size() - kGateRollPrefix.size() - 1U);
        const std::vector<std::string> aArgs = SplitCommaTokens(aArgsText);
        if (aArgs.size() != 3U) {
            SetError(pErrorMessage, "GateRoll_1_1 expected exactly 3 arguments.");
            return false;
        }

        GRuntimeScalar aInputValue = 0ULL;
        if (!EvaluateGenericRawExpression(aArgs[0], pWorkspace, pExpander, pVariables, &aInputValue, pErrorMessage)) {
            return false;
        }

        int aAmount = 0;
        if (!ParseIntLiteralToken(aArgs[1], &aAmount) || (aAmount < 0)) {
            SetError(pErrorMessage, "GateRoll_1_1 amount token was invalid: " + aArgs[1]);
            return false;
        }

        TwistWorkSpaceSlot aSBoxSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveAliasBufferSlot(TrimCopy(aArgs[2]), &aSBoxSlot)) {
            SetError(pErrorMessage, "GateRoll_1_1 S-box alias was invalid: " + aArgs[2]);
            return false;
        }
        std::uint8_t *aSBox = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSBoxSlot);
        if (aSBox == nullptr) {
            SetError(pErrorMessage, "GateRoll_1_1 S-box buffer resolved to null.");
            return false;
        }

        *pValue = static_cast<GRuntimeScalar>(
            TwistMix64::GateRoll_1_1(static_cast<std::uint64_t>(aInputValue),
                                     static_cast<std::uint64_t>(aAmount),
                                     aSBox));
        return true;
    }

    std::string aAliasToken;
    std::string aIndexToken;
    if (SplitBufferElementToken(aToken, &aAliasToken, &aIndexToken)) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveAliasBufferSlot(aAliasToken, &aSlot)) {
            SetError(pErrorMessage, "Generic raw-line buffer alias was invalid: " + aAliasToken);
            return false;
        }
        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSlot);
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "Generic raw-line buffer pointer was null.");
            return false;
        }
        GRuntimeScalar aIndexValue = 0ULL;
        if (!EvaluateGenericRawExpression(aIndexToken, pWorkspace, pExpander, pVariables, &aIndexValue, pErrorMessage)) {
            return false;
        }
        const std::size_t aIndex = RuntimeIndexForSlot(aSlot, aIndexValue);
        *pValue = ReadRuntimeBufferValue(aSlot, aBuffer, aIndex);
        return true;
    }

    int aLiteral = 0;
    if (ParseIntLiteralToken(aToken, &aLiteral)) {
        *pValue = static_cast<GRuntimeScalar>(static_cast<std::int64_t>(aLiteral));
        return true;
    }

    if (IsIdentifierToken(aToken)) {
        const auto aIterator = pVariables->find(aToken);
        *pValue = (aIterator == pVariables->end()) ? 0ULL : aIterator->second;
        return true;
    }

    SetError(pErrorMessage, "Generic raw-line atom was unsupported: " + aToken);
    return false;
}

bool EvaluateGenericRawExpression(const std::string &pExpression,
                                  TwistWorkSpace *pWorkspace,
                                  TwistExpander *pExpander,
                                  std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                  GRuntimeScalar *pValue,
                                  std::string *pErrorMessage) {
    if ((pVariables == nullptr) || (pValue == nullptr)) {
        SetError(pErrorMessage, "Generic raw-line expression output was null.");
        return false;
    }

    const std::string aExpression = TrimCopy(pExpression);
    if (aExpression.empty()) {
        SetError(pErrorMessage, "Generic raw-line expression was empty.");
        return false;
    }

    std::string aParsed = aExpression;
    while (StripOneOuterParenPair(&aParsed)) {
    }

    const std::size_t aOrPos = FindTopLevelOperatorChar(aParsed, '|', false);
    if (aOrPos != std::string::npos) {
        GRuntimeScalar aLeft = 0ULL;
        GRuntimeScalar aRight = 0ULL;
        if (!EvaluateGenericRawExpression(aParsed.substr(0U, aOrPos),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aLeft,
                                          pErrorMessage) ||
            !EvaluateGenericRawExpression(aParsed.substr(aOrPos + 1U),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aRight,
                                          pErrorMessage)) {
            return false;
        }
        *pValue = aLeft | aRight;
        return true;
    }

    const std::size_t aXorPos = FindTopLevelOperatorChar(aParsed, '^', false);
    if (aXorPos != std::string::npos) {
        GRuntimeScalar aLeft = 0ULL;
        GRuntimeScalar aRight = 0ULL;
        if (!EvaluateGenericRawExpression(aParsed.substr(0U, aXorPos),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aLeft,
                                          pErrorMessage) ||
            !EvaluateGenericRawExpression(aParsed.substr(aXorPos + 1U),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aRight,
                                          pErrorMessage)) {
            return false;
        }
        *pValue = aLeft ^ aRight;
        return true;
    }

    const std::size_t aAndPos = FindTopLevelOperatorChar(aParsed, '&', false);
    if (aAndPos != std::string::npos) {
        GRuntimeScalar aLeft = 0ULL;
        GRuntimeScalar aRight = 0ULL;
        if (!EvaluateGenericRawExpression(aParsed.substr(0U, aAndPos),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aLeft,
                                          pErrorMessage) ||
            !EvaluateGenericRawExpression(aParsed.substr(aAndPos + 1U),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aRight,
                                          pErrorMessage)) {
            return false;
        }
        *pValue = aLeft & aRight;
        return true;
    }

    bool aIsRightShift = false;
    const std::size_t aShiftPos = FindTopLevelShiftOperator(aParsed, &aIsRightShift);
    if (aShiftPos != std::string::npos) {
        GRuntimeScalar aLeft = 0ULL;
        GRuntimeScalar aRight = 0ULL;
        if (!EvaluateGenericRawExpression(aParsed.substr(0U, aShiftPos),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aLeft,
                                          pErrorMessage) ||
            !EvaluateGenericRawExpression(aParsed.substr(aShiftPos + 2U),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aRight,
                                          pErrorMessage)) {
            return false;
        }
        const unsigned int aAmount = static_cast<unsigned int>(aRight & 63ULL);
        *pValue = aIsRightShift ? (aLeft >> aAmount) : (aLeft << aAmount);
        return true;
    }

    const std::size_t aPlusPos = FindTopLevelOperatorChar(aParsed, '+', true);
    if (aPlusPos != std::string::npos) {
        GRuntimeScalar aLeft = 0ULL;
        GRuntimeScalar aRight = 0ULL;
        if (!EvaluateGenericRawExpression(aParsed.substr(0U, aPlusPos),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aLeft,
                                          pErrorMessage) ||
            !EvaluateGenericRawExpression(aParsed.substr(aPlusPos + 1U),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aRight,
                                          pErrorMessage)) {
            return false;
        }
        *pValue = aLeft + aRight;
        return true;
    }

    const std::size_t aMinusPos = FindTopLevelOperatorChar(aParsed, '-', true);
    if (aMinusPos != std::string::npos) {
        GRuntimeScalar aLeft = 0ULL;
        GRuntimeScalar aRight = 0ULL;
        if (!EvaluateGenericRawExpression(aParsed.substr(0U, aMinusPos),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aLeft,
                                          pErrorMessage) ||
            !EvaluateGenericRawExpression(aParsed.substr(aMinusPos + 1U),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aRight,
                                          pErrorMessage)) {
            return false;
        }
        *pValue = aLeft - aRight;
        return true;
    }

    const std::size_t aMulPos = FindTopLevelOperatorChar(aParsed, '*', false);
    if (aMulPos != std::string::npos) {
        GRuntimeScalar aLeft = 0ULL;
        GRuntimeScalar aRight = 0ULL;
        if (!EvaluateGenericRawExpression(aParsed.substr(0U, aMulPos),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aLeft,
                                          pErrorMessage) ||
            !EvaluateGenericRawExpression(aParsed.substr(aMulPos + 1U),
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aRight,
                                          pErrorMessage)) {
            return false;
        }
        *pValue = aLeft * aRight;
        return true;
    }

    return EvaluateGenericRawAtom(aParsed, pWorkspace, pExpander, pVariables, pValue, pErrorMessage);
}

bool ExecuteGenericRawLine(const std::string &pRawLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                           bool *pHandled,
                           std::string *pErrorMessage) {
    if ((pHandled == nullptr) || (pVariables == nullptr)) {
        SetError(pErrorMessage, "Generic raw-line handler output was null.");
        return false;
    }
    *pHandled = false;

    const std::string aText = TrimCopy(pRawLine);
    if (aText.empty() || (aText.rfind("//", 0U) == 0U)) {
        *pHandled = true;
        return true;
    }
    if (aText.back() != ';') {
        return true;
    }

    const std::string aBody = TrimCopy(aText.substr(0U, aText.size() - 1U));
    std::size_t aAssignPos = std::string::npos;
    std::size_t aAssignLen = 0U;
    GRawAssignType aAssignType = GRawAssignType::kSet;
    if (!FindTopLevelAssignOperator(aBody, &aAssignPos, &aAssignLen, &aAssignType)) {
        return true;
    }

    const std::string aLeft = TrimCopy(aBody.substr(0U, aAssignPos));
    const std::string aRight = TrimCopy(aBody.substr(aAssignPos + aAssignLen));
    if (aLeft.empty() || aRight.empty()) {
        return true;
    }

    std::string aTargetAliasToken;
    std::string aTargetIndexToken;
    const bool aIsBufferTarget = SplitBufferElementToken(aLeft, &aTargetAliasToken, &aTargetIndexToken);
    const bool aIsVarTarget = IsIdentifierToken(aLeft);
    if (!aIsBufferTarget && !aIsVarTarget) {
        return true;
    }
    *pHandled = true;

    GRuntimeScalar aRightValue = 0ULL;
    if (!EvaluateGenericRawExpression(aRight, pWorkspace, pExpander, pVariables, &aRightValue, pErrorMessage)) {
        return false;
    }

    if (aIsVarTarget) {
        GRuntimeScalar &aTargetValue = (*pVariables)[aLeft];
        switch (aAssignType) {
            case GRawAssignType::kSet:
                aTargetValue = NormalizeScalarValueForName(aLeft, aRightValue);
                return true;
            case GRawAssignType::kAddAssign:
                aTargetValue = NormalizeScalarValueForName(aLeft, aTargetValue + aRightValue);
                return true;
            case GRawAssignType::kXorAssign:
                aTargetValue = NormalizeScalarValueForName(aLeft, aTargetValue ^ aRightValue);
                return true;
            default:
                SetError(pErrorMessage, "Generic raw-line variable assignment type was invalid.");
                return false;
        }
    }

    TwistWorkSpaceSlot aTargetSlot = TwistWorkSpaceSlot::kInvalid;
    if (!ResolveAliasBufferSlot(aTargetAliasToken, &aTargetSlot)) {
        SetError(pErrorMessage, "Generic raw-line target alias was invalid: " + aTargetAliasToken);
        return false;
    }
    std::uint8_t *aTargetBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aTargetSlot);
    if (aTargetBuffer == nullptr) {
        SetError(pErrorMessage, "Generic raw-line target buffer resolved to null.");
        return false;
    }

    GRuntimeScalar aTargetIndexValue = 0ULL;
    if (!EvaluateGenericRawExpression(aTargetIndexToken,
                                      pWorkspace,
                                      pExpander,
                                      pVariables,
                                      &aTargetIndexValue,
                                      pErrorMessage)) {
        return false;
    }
    const std::size_t aTargetIndex = RuntimeIndexForSlot(aTargetSlot, aTargetIndexValue);

    switch (aAssignType) {
        case GRawAssignType::kSet:
            WriteRuntimeBufferValue(aTargetSlot,
                                    aTargetBuffer,
                                    aTargetIndex,
                                    aRightValue);
            return true;
        case GRawAssignType::kAddAssign: {
            const GRuntimeScalar aCurrentValue = ReadRuntimeBufferValue(aTargetSlot,
                                                                        aTargetBuffer,
                                                                        aTargetIndex);
            WriteRuntimeBufferValue(aTargetSlot,
                                    aTargetBuffer,
                                    aTargetIndex,
                                    aCurrentValue + aRightValue);
            return true;
        }
        case GRawAssignType::kXorAssign: {
            const GRuntimeScalar aCurrentValue = ReadRuntimeBufferValue(aTargetSlot,
                                                                        aTargetBuffer,
                                                                        aTargetIndex);
            WriteRuntimeBufferValue(aTargetSlot,
                                    aTargetBuffer,
                                    aTargetIndex,
                                    aCurrentValue ^ aRightValue);
            return true;
        }
        default:
            SetError(pErrorMessage, "Generic raw-line buffer assignment type was invalid.");
            return false;
    }
}

bool ExecuteSnowRawLine(const std::string &pRawLine,
                        TwistWorkSpace *pWorkspace,
                        TwistExpander *pExpander,
                        std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                        bool *pHandled,
                        std::string *pErrorMessage) {
    if (pHandled == nullptr) {
        SetError(pErrorMessage, "Snow raw-line handled output was null.");
        return false;
    }
    *pHandled = false;

    const std::string aText = TrimCopy(pRawLine);
    if (aText.empty()) {
        return true;
    }
    if (aText.rfind("//", 0U) == 0U) {
        return true;
    }

    const std::string kSnowPrefix = "TwistSnow::";
    if (aText.rfind(kSnowPrefix, 0U) != 0U) {
        return true;
    }
    *pHandled = true;

    if ((pWorkspace == nullptr) || (pExpander == nullptr) || (pVariables == nullptr)) {
        SetError(pErrorMessage, "Snow statement execution was missing required runtime inputs.");
        return false;
    }
    if (aText.back() != ';') {
        SetError(pErrorMessage, "Snow statement was missing a trailing semicolon.");
        return false;
    }

    const std::size_t aOpenPos = aText.find('(', kSnowPrefix.size());
    const std::size_t aClosePos = aText.rfind(')');
    if ((aOpenPos == std::string::npos) ||
        (aClosePos == std::string::npos) ||
        (aClosePos <= aOpenPos)) {
        SetError(pErrorMessage, "Snow statement call syntax was invalid.");
        return false;
    }

    const std::string aMethod = aText.substr(kSnowPrefix.size(), aOpenPos - kSnowPrefix.size());
    const std::string aArgsText = aText.substr(aOpenPos + 1U, aClosePos - (aOpenPos + 1U));
    const std::vector<std::string> aArgs = SplitCommaTokens(aArgsText);
    if (aArgs.size() != 2U) {
        SetError(pErrorMessage, "Snow call expected exactly 2 arguments.");
        return false;
    }

    TwistWorkSpaceSlot aSourceSlot = TwistWorkSpaceSlot::kInvalid;
    TwistWorkSpaceSlot aDestSlot = TwistWorkSpaceSlot::kInvalid;
    int aSourceOffset = 0;
    int aDestOffset = 0;
    if (!ParseMatrixBufferOffsetExpression(aArgs[0], pVariables, &aSourceSlot, &aSourceOffset, pErrorMessage)) {
        return false;
    }
    if (!ParseMatrixBufferOffsetExpression(aArgs[1], pVariables, &aDestSlot, &aDestOffset, pErrorMessage)) {
        return false;
    }

    std::uint8_t *aSource = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSourceSlot);
    std::uint8_t *aDest = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aDestSlot);
    if ((aSource == nullptr) || (aDest == nullptr)) {
        SetError(pErrorMessage, "Snow source/destination pointer was null.");
        return false;
    }
    aSource += static_cast<std::size_t>(aSourceOffset);
    aDest += static_cast<std::size_t>(aDestOffset);

    if (aMethod == "AES256Counter") {
        TwistSnow::AES256Counter(aSource, aDest);
        return true;
    }
    if (aMethod == "ChaCha20Counter") {
        TwistSnow::ChaCha20Counter(aSource, aDest);
        return true;
    }
    if (aMethod == "Sha256Counter") {
        TwistSnow::Sha256Counter(aSource, aDest);
        return true;
    }
    if (aMethod == "Aria256Counter") {
        TwistSnow::Aria256Counter(aSource, aDest);
        return true;
    }

    SetError(pErrorMessage, "Unsupported snow statement method: " + aMethod);
    return false;
}

bool ExecuteMemoryRawLine(const std::string &pRawLine,
                          TwistWorkSpace *pWorkspace,
                          TwistExpander *pExpander,
                          std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                          bool *pHandled,
                          std::string *pErrorMessage) {
    if (pHandled == nullptr) {
        SetError(pErrorMessage, "Memory raw-line handled output was null.");
        return false;
    }
    *pHandled = false;

    const std::string aText = TrimCopy(pRawLine);
    if (aText.empty()) {
        return true;
    }
    if (aText.rfind("//", 0U) == 0U) {
        return true;
    }

    const std::string kMemoryPrefix = "TwistMemory::";
    if (aText.rfind(kMemoryPrefix, 0U) != 0U) {
        return true;
    }
    *pHandled = true;

    if ((pWorkspace == nullptr) || (pExpander == nullptr) || (pVariables == nullptr)) {
        SetError(pErrorMessage, "Memory statement execution was missing required runtime inputs.");
        return false;
    }
    if (aText.back() != ';') {
        SetError(pErrorMessage, "Memory statement was missing a trailing semicolon.");
        return false;
    }

    const std::size_t aOpenPos = aText.find('(', kMemoryPrefix.size());
    const std::size_t aClosePos = aText.rfind(')');
    if ((aOpenPos == std::string::npos) ||
        (aClosePos == std::string::npos) ||
        (aClosePos <= aOpenPos)) {
        SetError(pErrorMessage, "Memory statement call syntax was invalid.");
        return false;
    }

    const std::string aMethod = aText.substr(kMemoryPrefix.size(), aOpenPos - kMemoryPrefix.size());
    const std::string aArgsText = aText.substr(aOpenPos + 1U, aClosePos - (aOpenPos + 1U));
    const std::vector<std::string> aArgs = SplitCommaTokens(aArgsText);

    auto IsScratchSaltSlot = [](const TwistWorkSpaceSlot pSlot) -> bool {
        switch (pSlot) {
            case TwistWorkSpaceSlot::kScratchSaltA:
            case TwistWorkSpaceSlot::kScratchSaltB:
            case TwistWorkSpaceSlot::kScratchSaltC:
            case TwistWorkSpaceSlot::kScratchSaltD:
                return true;
            default:
                return false;
        }
    };

    auto ParseLength = [&](const std::string &pToken,
                           std::size_t *pLength) -> bool {
        if (pLength == nullptr) {
            SetError(pErrorMessage, "Grow length output pointer was null.");
            return false;
        }

        int aLength = ResolveLengthText(TrimCopy(pToken));
        if (aLength <= 0) {
            if (!EvaluateControlOperand(pToken, pVariables, &aLength)) {
                SetError(pErrorMessage, "Grow length token was invalid: " + pToken);
                return false;
            }
        }
        if (aLength <= 0) {
            SetError(pErrorMessage, "Grow length must be > 0.");
            return false;
        }
        *pLength = static_cast<std::size_t>(aLength);
        return true;
    };

    if (aMethod == "ZeroBlock") {
        if (aArgs.size() != 1U) {
            SetError(pErrorMessage, "ZeroBlock expected exactly 1 argument.");
            return false;
        }

        TwistWorkSpaceSlot aSourceSlot = TwistWorkSpaceSlot::kInvalid;
        int aSourceOffset = 0;
        if (!ParseMatrixBufferOffsetExpression(aArgs[0], pVariables, &aSourceSlot, &aSourceOffset, pErrorMessage)) {
            return false;
        }

        std::uint8_t *aSource = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSourceSlot);
        if (aSource == nullptr) {
            SetError(pErrorMessage, "ZeroBlock source pointer was null.");
            return false;
        }
        aSource += static_cast<std::size_t>(aSourceOffset);
        TwistMemory::ZeroBlock(aSource);
        return true;
    }

    if (aMethod == "CopyBlock") {
        if (aArgs.size() != 2U) {
            SetError(pErrorMessage, "CopyBlock expected exactly 2 arguments.");
            return false;
        }

        TwistWorkSpaceSlot aDestSlot = TwistWorkSpaceSlot::kInvalid;
        TwistWorkSpaceSlot aSourceSlot = TwistWorkSpaceSlot::kInvalid;
        int aDestOffset = 0;
        int aSourceOffset = 0;
        if (!ParseMatrixBufferOffsetExpression(aArgs[0], pVariables, &aDestSlot, &aDestOffset, pErrorMessage)) {
            return false;
        }
        if (!ParseMatrixBufferOffsetExpression(aArgs[1], pVariables, &aSourceSlot, &aSourceOffset, pErrorMessage)) {
            return false;
        }

        std::uint8_t *aDest = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aDestSlot);
        std::uint8_t *aSource = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSourceSlot);
        if ((aDest == nullptr) || (aSource == nullptr)) {
            SetError(pErrorMessage, "CopyBlock source/destination pointer was null.");
            return false;
        }
        aDest += static_cast<std::size_t>(aDestOffset);
        aSource += static_cast<std::size_t>(aSourceOffset);
        TwistMemory::CopyBlock(aDest, aSource);
        return true;
    }

    if (aMethod == "Grow") {
        if (aArgs.size() != 3U) {
            SetError(pErrorMessage, "Grow expected exactly 3 arguments.");
            return false;
        }

        TwistWorkSpaceSlot aDestSlot = TwistWorkSpaceSlot::kInvalid;
        TwistWorkSpaceSlot aSourceSlot = TwistWorkSpaceSlot::kInvalid;
        int aDestOffset = 0;
        int aSourceOffset = 0;
        if (!ParseMatrixBufferOffsetExpression(aArgs[0], pVariables, &aDestSlot, &aDestOffset, pErrorMessage)) {
            return false;
        }
        if (!ParseMatrixBufferOffsetExpression(aArgs[1], pVariables, &aSourceSlot, &aSourceOffset, pErrorMessage)) {
            return false;
        }
        if (!IsScratchSaltSlot(aDestSlot)) {
            SetError(pErrorMessage, "Grow destination must be a scratch-salt buffer.");
            return false;
        }

        std::size_t aLength = 0U;
        if (!ParseLength(aArgs[2], &aLength)) {
            return false;
        }

        std::uint8_t *aDestBytes = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aDestSlot);
        std::uint8_t *aSourceBytes = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSourceSlot);
        if ((aDestBytes == nullptr) || (aSourceBytes == nullptr)) {
            SetError(pErrorMessage, "Grow source/destination pointer was null.");
            return false;
        }

        aDestBytes += static_cast<std::size_t>(aDestOffset);
        aSourceBytes += static_cast<std::size_t>(aSourceOffset);
        TwistMemory::Grow(reinterpret_cast<std::uint64_t *>(aDestBytes),
                          aSourceBytes,
                          static_cast<std::uint32_t>(aLength));
        return true;
    }

    if (aMethod == "SwapBlock") {
        if (aArgs.size() != 3U) {
            SetError(pErrorMessage, "SwapBlock expected exactly 3 arguments.");
            return false;
        }

        TwistWorkSpaceSlot aBufferASlot = TwistWorkSpaceSlot::kInvalid;
        TwistWorkSpaceSlot aBufferBSlot = TwistWorkSpaceSlot::kInvalid;
        TwistWorkSpaceSlot aTempSlot = TwistWorkSpaceSlot::kInvalid;
        int aBufferAOffset = 0;
        int aBufferBOffset = 0;
        int aTempOffset = 0;
        if (!ParseMatrixBufferOffsetExpression(aArgs[0], pVariables, &aBufferASlot, &aBufferAOffset, pErrorMessage)) {
            return false;
        }
        if (!ParseMatrixBufferOffsetExpression(aArgs[1], pVariables, &aBufferBSlot, &aBufferBOffset, pErrorMessage)) {
            return false;
        }
        if (!ParseMatrixBufferOffsetExpression(aArgs[2], pVariables, &aTempSlot, &aTempOffset, pErrorMessage)) {
            return false;
        }

        std::uint8_t *aBufferA = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aBufferASlot);
        std::uint8_t *aBufferB = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aBufferBSlot);
        std::uint8_t *aTemp = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aTempSlot);
        if ((aBufferA == nullptr) || (aBufferB == nullptr) || (aTemp == nullptr)) {
            SetError(pErrorMessage, "SwapBlock buffer pointer was null.");
            return false;
        }
        aBufferA += static_cast<std::size_t>(aBufferAOffset);
        aBufferB += static_cast<std::size_t>(aBufferBOffset);
        aTemp += static_cast<std::size_t>(aTempOffset);
        TwistMemory::SwapBlock(aBufferA, aBufferB, aTemp);
        return true;
    }

    SetError(pErrorMessage, "Unsupported memory statement method: " + aMethod);
    return false;
}

bool ParseMaskBraidTypeToken(const std::string &pText,
                             TwistMaskBraidType *pType) {
    if (pType == nullptr) {
        return false;
    }
    std::string aToken = TrimCopy(pText);
    if (aToken.rfind("TwistMaskBraidType::", 0U) == 0U) {
        aToken = aToken.substr(20U);
    }
    if (aToken == "kA") {
        *pType = TwistMaskBraidType::kA;
        return true;
    }
    if (aToken == "kB") {
        *pType = TwistMaskBraidType::kB;
        return true;
    }
    if (aToken == "kC") {
        *pType = TwistMaskBraidType::kC;
        return true;
    }
    return false;
}

bool ParseMaskWeaveTypeToken(const std::string &pText,
                             TwistMaskWeaveType *pType) {
    if (pType == nullptr) {
        return false;
    }
    std::string aToken = TrimCopy(pText);
    if (aToken.rfind("TwistMaskWeaveType::", 0U) == 0U) {
        aToken = aToken.substr(20U);
    }
    if (aToken == "kA") {
        *pType = TwistMaskWeaveType::kA;
        return true;
    }
    if (aToken == "kB") {
        *pType = TwistMaskWeaveType::kB;
        return true;
    }
    if (aToken == "kC") {
        *pType = TwistMaskWeaveType::kC;
        return true;
    }
    if (aToken == "kD") {
        *pType = TwistMaskWeaveType::kD;
        return true;
    }
    return false;
}

bool ExecuteMaskingRawLine(const std::string &pRawLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                           bool *pHandled,
                           std::string *pErrorMessage) {
    if (pHandled == nullptr) {
        SetError(pErrorMessage, "Masking raw-line handled output was null.");
        return false;
    }
    *pHandled = false;

    const std::string aText = TrimCopy(pRawLine);
    if (aText.empty()) {
        return true;
    }
    if (aText.rfind("//", 0U) == 0U) {
        return true;
    }

    const std::string kMaskingPrefix = "TwistMasking::";
    if (aText.rfind(kMaskingPrefix, 0U) != 0U) {
        return true;
    }
    *pHandled = true;

    if ((pWorkspace == nullptr) || (pExpander == nullptr) || (pVariables == nullptr)) {
        SetError(pErrorMessage, "Masking statement execution was missing required runtime inputs.");
        return false;
    }
    if (aText.back() != ';') {
        SetError(pErrorMessage, "Masking statement was missing a trailing semicolon.");
        return false;
    }

    const std::size_t aOpenPos = aText.find('(', kMaskingPrefix.size());
    const std::size_t aClosePos = aText.rfind(')');
    if ((aOpenPos == std::string::npos) ||
        (aClosePos == std::string::npos) ||
        (aClosePos <= aOpenPos)) {
        SetError(pErrorMessage, "Masking statement call syntax was invalid.");
        return false;
    }

    const std::string aMethod = aText.substr(kMaskingPrefix.size(), aOpenPos - kMaskingPrefix.size());
    const std::string aArgsText = aText.substr(aOpenPos + 1U, aClosePos - (aOpenPos + 1U));
    const std::vector<std::string> aArgs = SplitCommaTokens(aArgsText);

    auto ParseLen = [&](const std::string &pText, std::size_t *pLen, const std::string &pWhich) -> bool {
        int aLen = ResolveLengthText(TrimCopy(pText));
        if (aLen <= 0) {
            if (!EvaluateControlOperand(pText, pVariables, &aLen)) {
                SetError(pErrorMessage, "Masking " + pWhich + " token was invalid: " + pText);
                return false;
            }
        }
        if (aLen <= 0) {
            SetError(pErrorMessage, "Masking " + pWhich + " must be > 0.");
            return false;
        }
        *pLen = static_cast<std::size_t>(aLen);
        return true;
    };

    auto ParsePtr = [&](const std::string &pText, std::uint8_t **pPtr, const std::string &pWhich) -> bool {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        int aOffset = 0;
        if (!ParseMatrixBufferOffsetExpression(pText, pVariables, &aSlot, &aOffset, pErrorMessage)) {
            return false;
        }
        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSlot);
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "Masking " + pWhich + " pointer was null.");
            return false;
        }
        *pPtr = aBuffer + static_cast<std::size_t>(aOffset);
        return true;
    };

    if (aMethod == "MaskBraid") {
        if (aArgs.size() != 6U) {
            SetError(pErrorMessage, "MaskBraid expected exactly 6 arguments.");
            return false;
        }
        TwistMaskBraidType aType = TwistMaskBraidType::kA;
        if (!ParseMaskBraidTypeToken(aArgs[0], &aType)) {
            SetError(pErrorMessage, "MaskBraid type token was invalid: " + aArgs[0]);
            return false;
        }

        std::uint8_t *aSourceA = nullptr;
        std::uint8_t *aSourceB = nullptr;
        std::uint8_t *aMask = nullptr;
        std::size_t aBufferLength = 0U;
        std::size_t aMaskLength = 0U;
        if (!ParsePtr(aArgs[1], &aSourceA, "source A") ||
            !ParsePtr(aArgs[2], &aSourceB, "source B") ||
            !ParseLen(aArgs[3], &aBufferLength, "buffer length") ||
            !ParsePtr(aArgs[4], &aMask, "mask") ||
            !ParseLen(aArgs[5], &aMaskLength, "mask length")) {
            return false;
        }
        TwistMasking::MaskBraid(aType, aSourceA, aSourceB, aBufferLength, aMask, aMaskLength);
        return true;
    }

    if ((aMethod == "MaskBraidA") || (aMethod == "MaskBraidB") || (aMethod == "MaskBraidC")) {
        if (aArgs.size() != 5U) {
            SetError(pErrorMessage, aMethod + " expected exactly 5 arguments.");
            return false;
        }
        std::uint8_t *aSourceA = nullptr;
        std::uint8_t *aSourceB = nullptr;
        std::uint8_t *aMask = nullptr;
        std::size_t aBufferLength = 0U;
        std::size_t aMaskLength = 0U;
        if (!ParsePtr(aArgs[0], &aSourceA, "source A") ||
            !ParsePtr(aArgs[1], &aSourceB, "source B") ||
            !ParseLen(aArgs[2], &aBufferLength, "buffer length") ||
            !ParsePtr(aArgs[3], &aMask, "mask") ||
            !ParseLen(aArgs[4], &aMaskLength, "mask length")) {
            return false;
        }
        if (aMethod == "MaskBraidA") {
            TwistMasking::MaskBraidA(aSourceA, aSourceB, aBufferLength, aMask, aMaskLength);
            return true;
        }
        if (aMethod == "MaskBraidB") {
            TwistMasking::MaskBraidB(aSourceA, aSourceB, aBufferLength, aMask, aMaskLength);
            return true;
        }
        TwistMasking::MaskBraidC(aSourceA, aSourceB, aBufferLength, aMask, aMaskLength);
        return true;
    }

    if (aMethod == "MaskWeave") {
        if (aArgs.size() != 7U) {
            SetError(pErrorMessage, "MaskWeave expected exactly 7 arguments.");
            return false;
        }
        TwistMaskWeaveType aType = TwistMaskWeaveType::kA;
        if (!ParseMaskWeaveTypeToken(aArgs[0], &aType)) {
            SetError(pErrorMessage, "MaskWeave type token was invalid: " + aArgs[0]);
            return false;
        }

        std::uint8_t *aSourceA = nullptr;
        std::uint8_t *aSourceB = nullptr;
        std::uint8_t *aDest = nullptr;
        std::uint8_t *aMask = nullptr;
        std::size_t aBufferLength = 0U;
        std::size_t aMaskLength = 0U;
        if (!ParsePtr(aArgs[1], &aSourceA, "source A") ||
            !ParsePtr(aArgs[2], &aSourceB, "source B") ||
            !ParsePtr(aArgs[3], &aDest, "dest") ||
            !ParseLen(aArgs[4], &aBufferLength, "buffer length") ||
            !ParsePtr(aArgs[5], &aMask, "mask") ||
            !ParseLen(aArgs[6], &aMaskLength, "mask length")) {
            return false;
        }
        TwistMasking::MaskWeave(aType, aSourceA, aSourceB, aDest, aBufferLength, aMask, aMaskLength);
        return true;
    }

    if ((aMethod == "MaskWeaveA") || (aMethod == "MaskWeaveB") || (aMethod == "MaskWeaveC") || (aMethod == "MaskWeaveD")) {
        if (aArgs.size() != 6U) {
            SetError(pErrorMessage, aMethod + " expected exactly 6 arguments.");
            return false;
        }
        std::uint8_t *aSourceA = nullptr;
        std::uint8_t *aSourceB = nullptr;
        std::uint8_t *aDest = nullptr;
        std::uint8_t *aMask = nullptr;
        std::size_t aBufferLength = 0U;
        std::size_t aMaskLength = 0U;
        if (!ParsePtr(aArgs[0], &aSourceA, "source A") ||
            !ParsePtr(aArgs[1], &aSourceB, "source B") ||
            !ParsePtr(aArgs[2], &aDest, "dest") ||
            !ParseLen(aArgs[3], &aBufferLength, "buffer length") ||
            !ParsePtr(aArgs[4], &aMask, "mask") ||
            !ParseLen(aArgs[5], &aMaskLength, "mask length")) {
            return false;
        }
        if (aMethod == "MaskWeaveA") {
            TwistMasking::MaskWeaveA(aSourceA, aSourceB, aDest, aBufferLength, aMask, aMaskLength);
            return true;
        }
        if (aMethod == "MaskWeaveB") {
            TwistMasking::MaskWeaveB(aSourceA, aSourceB, aDest, aBufferLength, aMask, aMaskLength);
            return true;
        }
        if (aMethod == "MaskWeaveC") {
            TwistMasking::MaskWeaveC(aSourceA, aSourceB, aDest, aBufferLength, aMask, aMaskLength);
            return true;
        }
        TwistMasking::MaskWeaveD(aSourceA, aSourceB, aDest, aBufferLength, aMask, aMaskLength);
        return true;
    }

    SetError(pErrorMessage, "Unsupported masking statement method: " + aMethod);
    return false;
}

bool ExecuteMatrixRawLine(const std::string &pRawLine,
                          TwistWorkSpace *pWorkspace,
                          TwistExpander *pExpander,
                          std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                          bool *pHandled,
                          std::string *pErrorMessage) {
    if (pHandled == nullptr) {
        SetError(pErrorMessage, "Matrix raw-line handled output was null.");
        return false;
    }
    *pHandled = false;

    const std::string aText = TrimCopy(pRawLine);
    if (aText.empty()) {
        return true;
    }
    if (aText.rfind("//", 0U) == 0U) {
        return true;
    }

    TwistFastMatrix *aMatrix = nullptr;
    const std::string kMatrixA = "mMatrixA.";
    const std::string kMatrixB = "mMatrixB.";
    if (aText.rfind(kMatrixA, 0U) == 0U) {
        *pHandled = true;
        if (pExpander != nullptr) {
            aMatrix = &pExpander->mMatrixA;
        }
    } else if (aText.rfind(kMatrixB, 0U) == 0U) {
        *pHandled = true;
        if (pExpander != nullptr) {
            aMatrix = &pExpander->mMatrixB;
        }
    } else {
        return true;
    }

    if ((aMatrix == nullptr) || (pWorkspace == nullptr) || (pExpander == nullptr) || (pVariables == nullptr)) {
        SetError(pErrorMessage, "Matrix statement execution was missing required runtime inputs.");
        return false;
    }

    if (aText.back() != ';') {
        SetError(pErrorMessage, "Matrix statement was missing a trailing semicolon.");
        return false;
    }

    const std::size_t aDotPos = aText.find('.');
    const std::size_t aOpenPos = aText.find('(', aDotPos + 1U);
    const std::size_t aClosePos = aText.rfind(')');
    if ((aDotPos == std::string::npos) ||
        (aOpenPos == std::string::npos) ||
        (aClosePos == std::string::npos) ||
        (aClosePos <= aOpenPos)) {
        SetError(pErrorMessage, "Matrix statement call syntax was invalid.");
        return false;
    }

    const std::string aMethod = aText.substr(aDotPos + 1U, aOpenPos - (aDotPos + 1U));
    const std::string aArgsText = aText.substr(aOpenPos + 1U, aClosePos - (aOpenPos + 1U));

    if (aMethod == "LoadAndReset") {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        int aOffset = 0;
        if (!ParseMatrixBufferOffsetExpression(aArgsText, pVariables, &aSlot, &aOffset, pErrorMessage)) {
            return false;
        }
        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSlot);
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "Matrix load buffer pointer was null.");
            return false;
        }
        aMatrix->LoadAndReset(aBuffer + static_cast<std::size_t>(aOffset));
        return true;
    }

    if (aMethod == "ExecuteOp") {
        const std::vector<std::string> aArgs = SplitCommaTokens(aArgsText);
        if (aArgs.size() != 3U) {
            SetError(pErrorMessage, "Matrix ExecuteOp expected 3 arguments.");
            return false;
        }

        TwistFastMatrixOp aOp = TwistFastMatrixOp::kInv;
        if (!TwistFastMatrix::OpFromToken(aArgs[0], &aOp) || (aOp == TwistFastMatrixOp::kInv)) {
            SetError(pErrorMessage, "Matrix ExecuteOp had an invalid op token: " + aArgs[0]);
            return false;
        }

        int aArg1 = 0;
        int aArg2 = 0;
        if (!EvaluateControlOperand(aArgs[1], pVariables, &aArg1) ||
            !EvaluateControlOperand(aArgs[2], pVariables, &aArg2)) {
            SetError(pErrorMessage, "Matrix ExecuteOp argument token was invalid.");
            return false;
        }

        aMatrix->ExecuteOp(aOp, static_cast<std::uint8_t>(aArg1), static_cast<std::uint8_t>(aArg2));
        return true;
    }

    TwistFastMatrixOp aMethodOp = TwistFastMatrixOp::kInv;
    if (TwistFastMatrix::OpFromFunctionName(aMethod, &aMethodOp) &&
        (aMethodOp != TwistFastMatrixOp::kInv)) {
        const std::vector<std::string> aArgs = SplitCommaTokens(aArgsText);
        if (aArgs.size() > 2U) {
            SetError(pErrorMessage, "Matrix op method expected 0-2 arguments.");
            return false;
        }

        int aArg1 = 0;
        int aArg2 = 0;
        if ((aArgs.size() >= 1U) &&
            !aArgs[0].empty() &&
            !EvaluateControlOperand(aArgs[0], pVariables, &aArg1)) {
            SetError(pErrorMessage, "Matrix op method argument 1 token was invalid.");
            return false;
        }
        if ((aArgs.size() >= 2U) &&
            !aArgs[1].empty() &&
            !EvaluateControlOperand(aArgs[1], pVariables, &aArg2)) {
            SetError(pErrorMessage, "Matrix op method argument 2 token was invalid.");
            return false;
        }

        aMatrix->ExecuteOp(aMethodOp, static_cast<std::uint8_t>(aArg1), static_cast<std::uint8_t>(aArg2));
        return true;
    }

    if (aMethod == "Store") {
        const std::vector<std::string> aArgs = SplitCommaTokens(aArgsText);
        if (aArgs.size() != 3U) {
            SetError(pErrorMessage, "Matrix Store expected 3 arguments.");
            return false;
        }

        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        int aOffset = 0;
        if (!ParseMatrixBufferOffsetExpression(aArgs[0], pVariables, &aSlot, &aOffset, pErrorMessage)) {
            return false;
        }

        TwistFastMatrixUnrollScheme aScheme = TwistFastMatrixUnrollScheme::kA;
        if (!TwistFastMatrix::UnrollSchemeFromToken(aArgs[1], &aScheme)) {
            SetError(pErrorMessage, "Matrix Store unroll scheme token was invalid: " + aArgs[1]);
            return false;
        }

        int aByte = 0;
        if (!EvaluateControlOperand(aArgs[2], pVariables, &aByte)) {
            SetError(pErrorMessage, "Matrix Store unroll byte token was invalid.");
            return false;
        }

        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSlot);
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "Matrix store buffer pointer was null.");
            return false;
        }
        aMatrix->Store(aBuffer + static_cast<std::size_t>(aOffset),
                       aScheme,
                       static_cast<std::uint8_t>(aByte));
        return true;
    }

    SetError(pErrorMessage, "Unsupported matrix statement method: " + aMethod);
    return false;
}

bool EvaluateControlCondition(const std::string &pCondition,
                              std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                              bool *pResult,
                              std::string *pErrorMessage) {
    if ((pVariables == NULL) || (pResult == NULL)) {
        SetError(pErrorMessage, "Control condition inputs were null.");
        return false;
    }

    const std::string aCondition = TrimCopy(pCondition);
    if (aCondition.empty()) {
        SetError(pErrorMessage, "Control condition was empty.");
        return false;
    }

    std::size_t aOperatorPos = std::string::npos;
    std::size_t aOperatorLength = 0U;
    std::string aOperatorText;
    if (FindTopLevelComparisonOperator(aCondition,
                                       &aOperatorPos,
                                       &aOperatorLength,
                                       &aOperatorText)) {
        const std::string aLeftText = TrimCopy(aCondition.substr(0U, aOperatorPos));
        const std::string aRightText = TrimCopy(aCondition.substr(aOperatorPos + aOperatorLength));
        GRuntimeScalar aLeftValue = 0ULL;
        GRuntimeScalar aRightValue = 0ULL;
        if (!EvaluateGenericRawExpression(aLeftText, nullptr, nullptr, pVariables, &aLeftValue, pErrorMessage) ||
            !EvaluateGenericRawExpression(aRightText, nullptr, nullptr, pVariables, &aRightValue, pErrorMessage)) {
            SetError(pErrorMessage, "Control condition operand could not be evaluated.");
            return false;
        }

        if (aOperatorText == ">=") { *pResult = aLeftValue >= aRightValue; return true; }
        if (aOperatorText == "<=") { *pResult = aLeftValue <= aRightValue; return true; }
        if (aOperatorText == "==") { *pResult = aLeftValue == aRightValue; return true; }
        if (aOperatorText == "!=") { *pResult = aLeftValue != aRightValue; return true; }
        if (aOperatorText == ">") { *pResult = aLeftValue > aRightValue; return true; }
        if (aOperatorText == "<") { *pResult = aLeftValue < aRightValue; return true; }
    }

    GRuntimeScalar aTruthValue = 0ULL;
    if (!EvaluateGenericRawExpression(aCondition, nullptr, nullptr, pVariables, &aTruthValue, pErrorMessage)) {
        SetError(pErrorMessage, "Control condition could not be evaluated.");
        return false;
    }
    *pResult = (aTruthValue != 0);
    return true;
}

struct ControlFrame {
    bool                            mParentActive = false;
    bool                            mCondition = false;
    bool                            mBranchActive = false;
    bool                            mElseSeen = false;
};

bool AllBranchesActive(const std::vector<ControlFrame> &pStack) {
    for (const ControlFrame &aFrame : pStack) {
        if (!aFrame.mBranchActive) {
            return false;
        }
    }
    return true;
}

bool ExecuteStatementSequence(const std::vector<GStatement> *pStatements,
                              TwistWorkSpace *pWorkspace,
                              TwistExpander *pExpander,
                              std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                              std::string *pErrorMessage) {
    if ((pVariables == NULL) || (pStatements == NULL)) {
        SetError(pErrorMessage, "Statement execution variable map was null.");
        return false;
    }

    std::vector<ControlFrame> aControlStack;
    for (const GStatement &aStatement : *pStatements) {
        if (aStatement.IsRawLine()) {
            ParsedControlLine aControlLine;
            if (!ParseControlLine(aStatement.mRawLine, &aControlLine)) {
                SetError(pErrorMessage, "Failed to parse control statement line: " + aStatement.mRawLine);
                return false;
            }

            if (aControlLine.mType == ControlLineType::kNone) {
                bool aDidHandleSnowLine = false;
                if (!ExecuteSnowRawLine(aStatement.mRawLine,
                                        pWorkspace,
                                        pExpander,
                                        pVariables,
                                        &aDidHandleSnowLine,
                                        pErrorMessage)) {
                    return false;
                }
                if (aDidHandleSnowLine) {
                    continue;
                }

                bool aDidHandleMemoryLine = false;
                if (!ExecuteMemoryRawLine(aStatement.mRawLine,
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aDidHandleMemoryLine,
                                          pErrorMessage)) {
                    return false;
                }
                if (aDidHandleMemoryLine) {
                    continue;
                }

                bool aDidHandleMaskingLine = false;
                if (!ExecuteMaskingRawLine(aStatement.mRawLine,
                                           pWorkspace,
                                           pExpander,
                                           pVariables,
                                           &aDidHandleMaskingLine,
                                           pErrorMessage)) {
                    return false;
                }
                if (aDidHandleMaskingLine) {
                    continue;
                }

                bool aDidHandleMatrixLine = false;
                if (!ExecuteMatrixRawLine(aStatement.mRawLine,
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          &aDidHandleMatrixLine,
                                          pErrorMessage)) {
                    return false;
                }
                if (aDidHandleMatrixLine) {
                    continue;
                }

                bool aDidHandleGenericLine = false;
                if (!ExecuteGenericRawLine(aStatement.mRawLine,
                                           pWorkspace,
                                           pExpander,
                                           pVariables,
                                           &aDidHandleGenericLine,
                                           pErrorMessage)) {
                    return false;
                }
                (void)aDidHandleGenericLine;
                continue;
            }

            if (aControlLine.mType == ControlLineType::kIf) {
                ControlFrame aFrame;
                aFrame.mParentActive = AllBranchesActive(aControlStack);
                if (aFrame.mParentActive) {
                    if (!EvaluateControlCondition(aControlLine.mCondition,
                                                  pVariables,
                                                  &aFrame.mCondition,
                                                  pErrorMessage)) {
                        return false;
                    }
                } else {
                    aFrame.mCondition = false;
                }
                aFrame.mBranchActive = aFrame.mParentActive && aFrame.mCondition;
                aControlStack.push_back(aFrame);
                continue;
            }

            if (aControlLine.mType == ControlLineType::kElse) {
                if (aControlStack.empty()) {
                    SetError(pErrorMessage, "Encountered else without matching if.");
                    return false;
                }
                ControlFrame &aFrame = aControlStack.back();
                if (aFrame.mElseSeen) {
                    SetError(pErrorMessage, "Encountered repeated else for one if block.");
                    return false;
                }
                aFrame.mElseSeen = true;
                aFrame.mBranchActive = aFrame.mParentActive && !aFrame.mCondition;
                continue;
            }

            if (aControlLine.mType == ControlLineType::kEnd) {
                if (aControlStack.empty()) {
                    SetError(pErrorMessage, "Encountered closing brace without matching if.");
                    return false;
                }
                aControlStack.pop_back();
                continue;
            }
        }

        if (!AllBranchesActive(aControlStack)) {
            continue;
        }
        if (!ExecuteStatement(aStatement, pWorkspace, pExpander, pVariables, pErrorMessage)) {
            return false;
        }
    }

    if (!aControlStack.empty()) {
        SetError(pErrorMessage, "Control statement block ended with an open if.");
        return false;
    }

    return true;
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

void GScopeState::Clear() {
    mReadCounts.clear();
}

void GScopeState::Consume(GScopeState pScopeState) {
    for (const auto &aPair : pScopeState.mReadCounts) {
        mReadCounts[aPair.first] += aPair.second;
    }
}

void GScopeState::Consume(GLoop pLoop) {
    for (const GStatement &aStatement : pLoop.mInitializationStatements) {
        Consume(aStatement);
    }
    for (const GStatement &aStatement : pLoop.mBodyStatements) {
        Consume(aStatement);
    }
}

void GScopeState::Consume(GStatement pStatement) {
    std::vector<GSymbol> aSymbols;
    CollectReadSymbolsFromStatement(pStatement, &aSymbols);
    for (const GSymbol &aSymbol : aSymbols) {
        RegisterRead(aSymbol);
    }
    RegisterRead(pStatement.mExpression);
}

void GScopeState::Consume(GSymbol pSymbol) {
    RegisterRead(pSymbol);
}

void GScopeState::Consume(GExpr pExpr) {
    RegisterRead(pExpr);
    const std::vector<GSymbol> aSymbols = pExpr.GetSymbols();
    for (const GSymbol &aSymbol : aSymbols) {
        RegisterRead(aSymbol);
    }
}

void GScopeState::RegisterRead(GSymbol pSymbol) {
    if (!pSymbol.IsInvalid()) {
        mReadCounts[ScopeSymbolKey(pSymbol)] += 1;
    }
}

void GScopeState::RegisterRead(GExpr pExpr) {
    if (!pExpr.IsInvalid()) {
        mReadCounts[ScopeExprKey(pExpr)] += 1;
    }
}

int GScopeState::GetReadCount(GSymbol pSymbol, int pCount) const {
    if (pSymbol.IsInvalid()) {
        return pCount;
    }
    const auto aIterator = mReadCounts.find(ScopeSymbolKey(pSymbol));
    return (aIterator == mReadCounts.end()) ? pCount : aIterator->second;
}

int GScopeState::GetReadCount(GExpr pExpr, int pCount) const {
    if (pExpr.IsInvalid()) {
        return pCount;
    }
    const auto aIterator = mReadCounts.find(ScopeExprKey(pExpr));
    return (aIterator == mReadCounts.end()) ? pCount : aIterator->second;
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
    aStatement.mRawLine.clear();
    aStatement.mOutputPrefix.clear();
    return aStatement;
}

GStatement GStatement::RawLine(const std::string &pRawLine) {
    GStatement aStatement;
    aStatement.mType = GStatementType::kRawLine;
    aStatement.mRawLine = pRawLine;
    aStatement.mOutputPrefix.clear();
    return aStatement;
}

GStatement GStatement::Comment(const std::string &pComment) {
    if (pComment.empty()) {
        return RawLine("//");
    }
    if (pComment.rfind("//", 0U) == 0U) {
        return RawLine(pComment);
    }
    return RawLine("// " + pComment);
}

GStatement GStatement::EmptyLine() {
    return RawLine(" ");
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
        return mRawLine.empty();
    }
    return (mAssignType == GAssignType::kInvalid) ||
           mTarget.IsInvalid() ||
           mExpression.IsInvalid();
}

bool GStatement::IsRawLine() const {
    return mType == GStatementType::kRawLine;
}

GSymbol GStatement::GetAssignSymbol(int pIndex) const {
    if (IsRawLine()) {
        return GSymbol();
    }
    if (pIndex == 0 && !mTarget.mSymbol.IsInvalid()) {
        return mTarget.mSymbol;
    }
    return GSymbol();
}

bool GStatement::HasAssignSymbol(int pIndex) const {
    return !GetAssignSymbol(pIndex).IsInvalid();
}

GOperType GStatement::GetAssignOper(int pIndex) const {
    if (IsRawLine()) {
        return GOperType::kInv;
    }
    (void)pIndex;
    return GOperType::kInv;
}

bool GStatement::HasAssignOper(int pIndex) const {
    return GetAssignOper(pIndex) != GOperType::kInv;
}

GSymbol GStatement::GetExprSymbol(int pIndex) const {
    if (IsRawLine()) {
        return GSymbol();
    }
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
    if (IsRawLine()) {
        return GOperType::kInv;
    }
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
    if (IsRawLine()) {
        return false;
    }
    return mTarget.mSymbol == pSymbol;
}

bool GStatement::HasAssignOper(GOperType pOper) const {
    return GetAssignOper(0) == pOper;
}

bool GStatement::HasExprSymbol(GSymbol pSymbol) const {
    if (IsRawLine()) {
        return false;
    }
    for (const GSymbol &aSymbol : mExpression.GetSymbols()) {
        if (aSymbol == pSymbol) {
            return true;
        }
    }
    return false;
}

bool GStatement::HasExprOper(GOperType pOper) const {
    if (IsRawLine()) {
        return false;
    }
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
    if (IsRawLine()) {
        return mRawLine;
    }
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

void GLoop::AddBodyComment(std::string pComment) {
    BodyDecoration aDecoration;
    aDecoration.mType = BodyDecoration::Type::kComment;
    aDecoration.mText = std::move(pComment);
    aDecoration.mStatementIndex = mBodyStatements.size();
    mBodyDecorations.push_back(std::move(aDecoration));
}

void GLoop::AddBodyEmptyLine() {
    BodyDecoration aDecoration;
    aDecoration.mType = BodyDecoration::Type::kEmptyLine;
    aDecoration.mStatementIndex = mBodyStatements.size();
    mBodyDecorations.push_back(std::move(aDecoration));
}

void GLoop::AddBody(GStatement *pStatement) {
    if (pStatement == nullptr) {
        return;
    }
    mBodyStatements.push_back(*pStatement);
    pStatement->Invalidate();
}

void GLoop::AddBody(GStatement pStatement) {
    mBodyStatements.push_back(pStatement);
}

void GLoop::AddBody(std::vector<GStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }
    for (int aIndex=0; aIndex<pStatements->size(); aIndex++) {
        mBodyStatements.push_back((*pStatements)[aIndex]);
    }
    pStatements->clear();
}

void GLoop::AddInitialization(GStatement *pStatement) {
    if (pStatement == nullptr) {
        return;
    }
    mInitializationStatements.push_back(*pStatement);
    pStatement->Invalidate();
}

GBatchWorkItem::GBatchWorkItem() {
    mType = GBatchWorkItemType::kLoop;
    mComment.clear();
}

GBatchWorkItem GBatchWorkItem::Loop(const GLoop &pLoop) {
    GBatchWorkItem aItem;
    aItem.mType = GBatchWorkItemType::kLoop;
    aItem.mLoop = pLoop;
    aItem.mStatements.clear();
    aItem.mComment.clear();
    return aItem;
}

GBatchWorkItem GBatchWorkItem::Statements(std::vector<GStatement> *pStatements) {
    GBatchWorkItem aItem;
    aItem.mType = GBatchWorkItemType::kStatements;
    aItem.mLoop = GLoop();
    if (pStatements != nullptr) {
        aItem.mStatements = std::move(*pStatements);
        pStatements->clear();
    }
    aItem.mComment.clear();
    return aItem;
}

GBatchWorkItem GBatchWorkItem::Comment(std::string pComment) {
    GBatchWorkItem aItem;
    aItem.mType = GBatchWorkItemType::kComment;
    aItem.mLoop = GLoop();
    aItem.mStatements.clear();
    aItem.mComment = std::move(pComment);
    return aItem;
}

GBatchWorkItem GBatchWorkItem::EmptyLine() {
    GBatchWorkItem aItem;
    aItem.mType = GBatchWorkItemType::kEmptyLine;
    aItem.mLoop = GLoop();
    aItem.mStatements.clear();
    aItem.mComment.clear();
    return aItem;
}

bool GBatchWorkItem::IsLoop() const {
    return mType == GBatchWorkItemType::kLoop;
}

bool GBatchWorkItem::IsStatements() const {
    return mType == GBatchWorkItemType::kStatements;
}

bool GBatchWorkItem::IsComment() const {
    return mType == GBatchWorkItemType::kComment;
}

bool GBatchWorkItem::IsEmptyLine() const {
    return mType == GBatchWorkItemType::kEmptyLine;
}

bool GBatchWorkItem::IsInvalid() const {
    if (IsLoop()) {
        return mLoop.IsInvalid();
    }
    if (IsStatements()) {
        for (const GStatement &aStatement : mStatements) {
            if (aStatement.IsInvalid()) {
                return true;
            }
        }
        return false;
    }
    if (IsComment() || IsEmptyLine()) {
        return false;
    }
    return true;
}

GBatch::GBatch() {
    mName = "twist_seed_batch";
}

void GBatch::CommitLoop(GLoop *pLoop) {
    if (pLoop == nullptr) {
        return;
    }
    mLoops.push_back(*pLoop);
    mWorkItems.push_back(GBatchWorkItem::Loop(*pLoop));
    mScopeStateGlobal.Consume(mScopeStateLocal);
    mScopeStateLocal.Clear();
    *pLoop = GLoop();
}

void GBatch::CommitStatements(std::vector<GStatement> *pStatements) {
    if ((pStatements == nullptr) || pStatements->empty()) {
        return;
    }
    mWorkItems.push_back(GBatchWorkItem::Statements(pStatements));
    for (const GStatement &aStatement : mWorkItems.back().mStatements) {
        mScopeStateLocal.Consume(aStatement);
    }
    mScopeStateGlobal.Consume(mScopeStateLocal);
    mScopeStateLocal.Clear();
}

void GBatch::AddComment(std::string pComment) {
    mWorkItems.push_back(GBatchWorkItem::Comment(std::move(pComment)));
    mScopeStateGlobal.Consume(mScopeStateLocal);
    mScopeStateLocal.Clear();
}

void GBatch::AddEmptyLine() {
    mWorkItems.push_back(GBatchWorkItem::EmptyLine());
    mScopeStateGlobal.Consume(mScopeStateLocal);
    mScopeStateLocal.Clear();
}

bool GBatch::IsInvalid() const {
    if (!mWorkItems.empty()) {
        for (const GBatchWorkItem &aItem : mWorkItems) {
            if (aItem.IsInvalid()) {
                return true;
            }
        }
        return false;
    }
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
    if (!mWorkItems.empty()) {
        for (const GBatchWorkItem &aItem : mWorkItems) {
            if (aItem.IsLoop()) {
                for (const GStatement &aStatement : aItem.mLoop.mInitializationStatements) {
                    aCount += CountExprReads(aStatement.mExpression, pSlot);
                    if (aStatement.mTarget.mIndex != nullptr) {
                        aCount += CountExprReads(*aStatement.mTarget.mIndex, pSlot);
                    }
                }
                for (const GStatement &aStatement : aItem.mLoop.mBodyStatements) {
                    aCount += CountExprReads(aStatement.mExpression, pSlot);
                    if (aStatement.mTarget.mIndex != nullptr) {
                        aCount += CountExprReads(*aStatement.mTarget.mIndex, pSlot);
                    }
                }
                continue;
            }
            for (const GStatement &aStatement : aItem.mStatements) {
                aCount += CountExprReads(aStatement.mExpression, pSlot);
                if (aStatement.mTarget.mIndex != nullptr) {
                    aCount += CountExprReads(*aStatement.mTarget.mIndex, pSlot);
                }
            }
        }
        return aCount;
    }

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
    if (!mWorkItems.empty()) {
        for (const GBatchWorkItem &aItem : mWorkItems) {
            if (aItem.IsLoop()) {
                for (const GStatement &aStatement : aItem.mLoop.mInitializationStatements) {
                    aCount += CountTargetWrites(aStatement.mTarget, pSlot);
                }
                for (const GStatement &aStatement : aItem.mLoop.mBodyStatements) {
                    aCount += CountTargetWrites(aStatement.mTarget, pSlot);
                }
                continue;
            }
            for (const GStatement &aStatement : aItem.mStatements) {
                aCount += CountTargetWrites(aStatement.mTarget, pSlot);
            }
        }
        return aCount;
    }

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
    if (!mWorkItems.empty()) {
        for (const GBatchWorkItem &aItem : mWorkItems) {
            if (!aItem.IsLoop()) {
                continue;
            }
            const GLoop &aLoop = aItem.mLoop;
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
    if (!mWorkItems.empty()) {
        for (const GBatchWorkItem &aItem : mWorkItems) {
            if (!aItem.IsLoop()) {
                continue;
            }
            const GLoop &aLoop = aItem.mLoop;
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
    if (!mWorkItems.empty()) {
        for (const GBatchWorkItem &aItem : mWorkItems) {
            if (aItem.IsLoop()) {
                const GLoop &aLoop = aItem.mLoop;
                AppendUnique(&aNames, aLoop.mLoopVariableName);
                for (const GStatement &aStatement : aLoop.mInitializationStatements) {
                    if (aStatement.mTarget.IsVar()) {
                        AppendUnique(&aNames, aStatement.mTarget.mSymbol.mName);
                    }
                    if (aStatement.mTarget.mIndex != nullptr) {
                        CollectVariablesFromExpr(*aStatement.mTarget.mIndex, &aNames);
                    }
                    CollectVariablesFromExpr(aStatement.mExpression, &aNames);
                }
                for (const GStatement &aStatement : aLoop.mBodyStatements) {
                    if (aStatement.mTarget.IsVar()) {
                        AppendUnique(&aNames, aStatement.mTarget.mSymbol.mName);
                    }
                    if (aStatement.mTarget.mIndex != nullptr) {
                        CollectVariablesFromExpr(*aStatement.mTarget.mIndex, &aNames);
                    }
                    CollectVariablesFromExpr(aStatement.mExpression, &aNames);
                }
                continue;
            }
            for (const GStatement &aStatement : aItem.mStatements) {
                if (aStatement.mTarget.IsVar()) {
                    AppendUnique(&aNames, aStatement.mTarget.mSymbol.mName);
                }
                if (aStatement.mTarget.mIndex != nullptr) {
                    CollectVariablesFromExpr(*aStatement.mTarget.mIndex, &aNames);
                }
                CollectVariablesFromExpr(aStatement.mExpression, &aNames);
            }
        }
        return aNames;
    }

    for (const GLoop &aLoop : mLoops) {
        AppendUnique(&aNames, aLoop.mLoopVariableName);
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            if (aStatement.mTarget.IsVar()) {
                AppendUnique(&aNames, aStatement.mTarget.mSymbol.mName);
            }
            if (aStatement.mTarget.mIndex != nullptr) {
                CollectVariablesFromExpr(*aStatement.mTarget.mIndex, &aNames);
            }
            CollectVariablesFromExpr(aStatement.mExpression, &aNames);
        }
        for (const GStatement &aStatement : aLoop.mBodyStatements) {
            if (aStatement.mTarget.IsVar()) {
                AppendUnique(&aNames, aStatement.mTarget.mSymbol.mName);
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
    if (!mWorkItems.empty()) {
        for (const GBatchWorkItem &aItem : mWorkItems) {
            if (aItem.IsLoop()) {
                const GLoop &aLoop = aItem.mLoop;
                for (const GStatement &aStatement : aLoop.mInitializationStatements) {
                    if (aStatement.IsRawLine()) {
                        CollectSlotsFromRawLine(aStatement.mRawLine, &aSlots);
                        continue;
                    }
                    if (aStatement.mTarget.IsBuf()) {
                        AppendUnique(&aSlots, aStatement.mTarget.mSymbol.mSlot);
                    }
                    if (aStatement.mTarget.mIndex != nullptr) {
                        CollectSlotsFromExpr(*aStatement.mTarget.mIndex, &aSlots);
                    }
                    CollectSlotsFromExpr(aStatement.mExpression, &aSlots);
                }
                for (const GStatement &aStatement : aLoop.mBodyStatements) {
                    if (aStatement.IsRawLine()) {
                        CollectSlotsFromRawLine(aStatement.mRawLine, &aSlots);
                        continue;
                    }
                    if (aStatement.mTarget.IsBuf()) {
                        AppendUnique(&aSlots, aStatement.mTarget.mSymbol.mSlot);
                    }
                    if (aStatement.mTarget.mIndex != nullptr) {
                        CollectSlotsFromExpr(*aStatement.mTarget.mIndex, &aSlots);
                    }
                    CollectSlotsFromExpr(aStatement.mExpression, &aSlots);
                }
                continue;
            }
            for (const GStatement &aStatement : aItem.mStatements) {
                if (aStatement.IsRawLine()) {
                    CollectSlotsFromRawLine(aStatement.mRawLine, &aSlots);
                    continue;
                }
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

    for (const GLoop &aLoop : mLoops) {
        for (const GStatement &aStatement : aLoop.mInitializationStatements) {
            if (aStatement.IsRawLine()) {
                CollectSlotsFromRawLine(aStatement.mRawLine, &aSlots);
                continue;
            }
            if (aStatement.mTarget.IsBuf()) {
                AppendUnique(&aSlots, aStatement.mTarget.mSymbol.mSlot);
            }
            if (aStatement.mTarget.mIndex != nullptr) {
                CollectSlotsFromExpr(*aStatement.mTarget.mIndex, &aSlots);
            }
            CollectSlotsFromExpr(aStatement.mExpression, &aSlots);
        }
        for (const GStatement &aStatement : aLoop.mBodyStatements) {
            if (aStatement.IsRawLine()) {
                CollectSlotsFromRawLine(aStatement.mRawLine, &aSlots);
                continue;
            }
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
    if (!mWorkItems.empty()) {
        for (std::size_t aIndex = 0U; aIndex < mWorkItems.size(); ++aIndex) {
            const GBatchWorkItem &aItem = mWorkItems[aIndex];
            if (aIndex > 0U) {
                aLines.push_back("");
            }
            if (aItem.IsComment()) {
                aLines.push_back(NormalizeCommentLine(aItem.mComment));
                continue;
            }
            if (aItem.IsEmptyLine()) {
                aLines.push_back("");
                continue;
            }
            if (aItem.IsLoop()) {
                AppendPrettyLoopLines(aItem.mLoop, &aLines);
                continue;
            }
            for (const GStatement &aStatement : aItem.mStatements) {
                aLines.push_back(PrettyStatement(aStatement));
            }
        }
    } else {
        for (std::size_t aIndex = 0U; aIndex < mLoops.size(); ++aIndex) {
            if (aIndex > 0U) {
                aLines.push_back("");
            }
            AppendPrettyLoopLines(mLoops[aIndex], &aLines);
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

std::string GBatch::ToJson(std::string *pErrorMessage) const {
    if (IsInvalid()) {
        SetError(pErrorMessage, "Batch was invalid and could not be serialized.");
        return "";
    }

    std::vector<GBatchWorkItem> aOrderedItems;
    if (!mWorkItems.empty()) {
        aOrderedItems = mWorkItems;
    } else {
        for (const GLoop &aLoop : mLoops) {
            aOrderedItems.push_back(GBatchWorkItem::Loop(aLoop));
        }
    }

    JsonValue::Array aLoops;
    JsonValue::Array aWorkItems;
    for (const GBatchWorkItem &aItem : aOrderedItems) {
        if (aItem.IsLoop()) {
            aLoops.push_back(LoopToJsonValue(aItem.mLoop));
            JsonValue::Object aItemObject;
            aItemObject["kind"] = JsonValue::String("loop");
            aItemObject["loop"] = LoopToJsonValue(aItem.mLoop);
            aWorkItems.push_back(JsonValue::ObjectValue(std::move(aItemObject)));
            continue;
        }
        if (aItem.IsStatements()) {
            JsonValue::Array aStatements;
            for (const GStatement &aStatement : aItem.mStatements) {
                aStatements.push_back(StatementToJsonValue(aStatement));
            }
            JsonValue::Object aItemObject;
            aItemObject["kind"] = JsonValue::String("statements");
            aItemObject["statements"] = JsonValue::ArrayValue(std::move(aStatements));
            aWorkItems.push_back(JsonValue::ObjectValue(std::move(aItemObject)));
            continue;
        }
        if (aItem.IsComment()) {
            JsonValue::Object aItemObject;
            aItemObject["kind"] = JsonValue::String("comment");
            aItemObject["text"] = JsonValue::String(aItem.mComment);
            aWorkItems.push_back(JsonValue::ObjectValue(std::move(aItemObject)));
            continue;
        }
        if (aItem.IsEmptyLine()) {
            JsonValue::Object aItemObject;
            aItemObject["kind"] = JsonValue::String("empty_line");
            aWorkItems.push_back(JsonValue::ObjectValue(std::move(aItemObject)));
            continue;
        }
        SetError(pErrorMessage, "Batch work-item type was invalid and could not be serialized.");
        return "";
    }

    JsonValue::Object aObject;
    aObject["name"] = JsonValue::String(mName);
    aObject["loops"] = JsonValue::ArrayValue(std::move(aLoops));
    aObject["work_items"] = JsonValue::ArrayValue(std::move(aWorkItems));
    return JsonValue::ObjectValue(std::move(aObject)).Serialize();
}

bool GBatch::FromJson(const std::string &pJsonText,
                      GBatch *pBatch,
                      std::string *pErrorMessage) {
    if (pBatch == NULL) {
        SetError(pErrorMessage, "Batch output was null.");
        return false;
    }

    auto aRoot = JsonValue::Parse(pJsonText, pErrorMessage);
    if (!aRoot.has_value() || !aRoot->is_object()) {
        if ((pErrorMessage != NULL) && pErrorMessage->empty()) {
            *pErrorMessage = "Batch JSON root was invalid.";
        }
        return false;
    }

    const JsonValue *aName = aRoot->find("name");
    if ((aName == NULL) || !aName->is_string()) {
        SetError(pErrorMessage, "Batch JSON was incomplete.");
        return false;
    }

    GBatch aBatch;
    aBatch.mName = aName->as_string();

    const JsonValue *aWorkItems = aRoot->find("work_items");
    if ((aWorkItems != NULL) && aWorkItems->is_array()) {
        for (const JsonValue &aItemValue : aWorkItems->as_array()) {
            if (!aItemValue.is_object()) {
                SetError(pErrorMessage, "Batch work-item JSON entry was not an object.");
                return false;
            }
            const JsonValue *aKind = aItemValue.find("kind");
            if ((aKind == NULL) || !aKind->is_string()) {
                SetError(pErrorMessage, "Batch work-item JSON kind was missing.");
                return false;
            }
            if (aKind->as_string() == "loop") {
                const JsonValue *aLoopJson = aItemValue.find("loop");
                if (aLoopJson == NULL) {
                    SetError(pErrorMessage, "Batch loop work-item JSON was incomplete.");
                    return false;
                }
                GLoop aLoop;
                if (!LoopFromJsonValue(*aLoopJson, &aLoop, pErrorMessage)) {
                    return false;
                }
                aBatch.mLoops.push_back(aLoop);
                aBatch.mWorkItems.push_back(GBatchWorkItem::Loop(aLoop));
                continue;
            }
            if (aKind->as_string() == "statements") {
                const JsonValue *aStatementsJson = aItemValue.find("statements");
                if ((aStatementsJson == NULL) || !aStatementsJson->is_array()) {
                    SetError(pErrorMessage, "Batch statements work-item JSON was incomplete.");
                    return false;
                }
                std::vector<GStatement> aStatements;
                for (const JsonValue &aStatementValue : aStatementsJson->as_array()) {
                    GStatement aStatement;
                    if (!StatementFromJsonValue(aStatementValue, &aStatement, pErrorMessage)) {
                        return false;
                    }
                    aStatements.push_back(aStatement);
                }
                aBatch.mWorkItems.push_back(GBatchWorkItem::Statements(&aStatements));
                continue;
            }
            if (aKind->as_string() == "comment") {
                const JsonValue *aText = aItemValue.find("text");
                const std::string aCommentText = ((aText != NULL) && aText->is_string()) ? aText->as_string() : "";
                aBatch.mWorkItems.push_back(GBatchWorkItem::Comment(aCommentText));
                continue;
            }
            if (aKind->as_string() == "empty_line") {
                aBatch.mWorkItems.push_back(GBatchWorkItem::EmptyLine());
                continue;
            }
            SetError(pErrorMessage, "Batch work-item JSON kind was invalid.");
            return false;
        }
    } else {
        const JsonValue *aLoops = aRoot->find("loops");
        if ((aLoops == NULL) || !aLoops->is_array()) {
            SetError(pErrorMessage, "Batch JSON was incomplete.");
            return false;
        }

        for (const JsonValue &aLoopValue : aLoops->as_array()) {
            GLoop aLoop;
            if (!LoopFromJsonValue(aLoopValue, &aLoop, pErrorMessage)) {
                return false;
            }
            aBatch.mLoops.push_back(aLoop);
            aBatch.mWorkItems.push_back(GBatchWorkItem::Loop(aLoop));
        }
    }

    *pBatch = aBatch;
    return true;
}

std::string GBatch::BuildCpp(const std::string &pFunctionName,
                             std::string *pErrorMessage,
                             bool pEmitDeclarations) const {
    if (IsInvalid()) {
        SetError(pErrorMessage, "Batch was invalid and could not be emitted as C++.");
        return "";
    }

    std::vector<std::string> aLines;
    aLines.push_back("static void " + pFunctionName + "(TwistWorkSpace *pWorkspace) {");

    std::vector<std::string> aLoopVariables;
    if (!mWorkItems.empty()) {
        for (const GBatchWorkItem &aItem : mWorkItems) {
            if (aItem.IsLoop()) {
                AppendUnique(&aLoopVariables, aItem.mLoop.mLoopVariableName);
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

    if (pEmitDeclarations) {
        std::vector<TwistWorkSpaceSlot> aSlots = CollectReferencedSlots();
        auto aSkipSlotAliasDeclaration = [](const TwistWorkSpaceSlot pSlot) -> bool {
            switch (pSlot) {
                case TwistWorkSpaceSlot::kSource:
                case TwistWorkSpaceSlot::kDest:
                case TwistWorkSpaceSlot::kSaltA:
                case TwistWorkSpaceSlot::kSaltB:
                case TwistWorkSpaceSlot::kSaltC:
                case TwistWorkSpaceSlot::kSaltD:
                case TwistWorkSpaceSlot::kScratchSaltA:
                case TwistWorkSpaceSlot::kScratchSaltB:
                case TwistWorkSpaceSlot::kScratchSaltC:
                case TwistWorkSpaceSlot::kScratchSaltD:
                case TwistWorkSpaceSlot::kSBoxA:
                case TwistWorkSpaceSlot::kSBoxB:
                case TwistWorkSpaceSlot::kSBoxC:
                case TwistWorkSpaceSlot::kSBoxD:
                    return true;
                default:
                    return false;
            }
        };
        for (TwistWorkSpaceSlot aSlot : aSlots) {
            if (aSkipSlotAliasDeclaration(aSlot)) {
                continue;
            }
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

    if (!mWorkItems.empty()) {
        for (std::size_t aIndex = 0U; aIndex < mWorkItems.size(); ++aIndex) {
            const GBatchWorkItem &aItem = mWorkItems[aIndex];
            if ((pEmitDeclarations || (aIndex > 0U)) && !aItem.IsEmptyLine()) {
                aLines.push_back("");
            }
            if (aItem.IsComment()) {
                aLines.push_back(Indent(1) + NormalizeCommentLine(aItem.mComment));
                continue;
            }
            if (aItem.IsEmptyLine()) {
                aLines.push_back("");
                continue;
            }
            if (aItem.IsLoop()) {
                const GLoop &aLoop = aItem.mLoop;
                for (const GStatement &aStatement : aLoop.mInitializationStatements) {
                    const std::vector<std::string> aStatementLines = CppStatementLines(aStatement);
                    for (const std::string &aStatementLine : aStatementLines) {
                        aLines.push_back(Indent(1) + aStatementLine);
                    }
                }
                if (LoopUsesUint32(aLoop)) {
                    aLines.push_back(Indent(1) + "for (std::uint16_t " + aLoop.mLoopVariableName + " = " +
                                     std::to_string(aLoop.mLoopBegin) + "U; " +
                                     aLoop.mLoopVariableName + " < " + aLoop.mLoopEndText + "; " +
                                     aLoop.mLoopVariableName + " += " + std::to_string(aLoop.mLoopStep) + "U) {");
                } else {
                    aLines.push_back(Indent(1) + "for (int " + aLoop.mLoopVariableName + " = " +
                                     std::to_string(aLoop.mLoopBegin) + "; " +
                                     aLoop.mLoopVariableName + " < " + aLoop.mLoopEndText + "; " +
                                     aLoop.mLoopVariableName + " += " + std::to_string(aLoop.mLoopStep) + ") {");
                }
                for (std::size_t aStatementIndex = 0U; aStatementIndex < aLoop.mBodyStatements.size(); ++aStatementIndex) {
                    AppendBodyDecorations(aLoop, aStatementIndex, 2, &aLines);
                    const GStatement &aStatement = aLoop.mBodyStatements[aStatementIndex];
                    const std::vector<std::string> aStatementLines = CppStatementLines(aStatement);
                    for (const std::string &aStatementLine : aStatementLines) {
                        aLines.push_back(Indent(2) + aStatementLine);
                    }
                }
                AppendBodyDecorations(aLoop, aLoop.mBodyStatements.size(), 2, &aLines);
                aLines.push_back(Indent(1) + "}");
                continue;
            }
            for (const GStatement &aStatement : aItem.mStatements) {
                const std::vector<std::string> aStatementLines = CppStatementLines(aStatement);
                for (const std::string &aStatementLine : aStatementLines) {
                    aLines.push_back(Indent(1) + aStatementLine);
                }
            }
        }
    } else {
        for (std::size_t aIndex = 0U; aIndex < mLoops.size(); ++aIndex) {
            const GLoop &aLoop = mLoops[aIndex];
            if (pEmitDeclarations || (aIndex > 0U)) {
                aLines.push_back("");
            }
            for (const GStatement &aStatement : aLoop.mInitializationStatements) {
                const std::vector<std::string> aStatementLines = CppStatementLines(aStatement);
                for (const std::string &aStatementLine : aStatementLines) {
                    aLines.push_back(Indent(1) + aStatementLine);
                }
            }
            if (LoopUsesUint32(aLoop)) {
                aLines.push_back(Indent(1) + "for (std::uint16_t " + aLoop.mLoopVariableName + " = " +
                                 std::to_string(aLoop.mLoopBegin) + "U; " +
                                 aLoop.mLoopVariableName + " < " + aLoop.mLoopEndText + "; " +
                                 aLoop.mLoopVariableName + " += " + std::to_string(aLoop.mLoopStep) + "U) {");
            } else {
                aLines.push_back(Indent(1) + "for (int " + aLoop.mLoopVariableName + " = " +
                                 std::to_string(aLoop.mLoopBegin) + "; " +
                                 aLoop.mLoopVariableName + " < " + aLoop.mLoopEndText + "; " +
                                 aLoop.mLoopVariableName + " += " + std::to_string(aLoop.mLoopStep) + ") {");
            }
            for (std::size_t aStatementIndex = 0U; aStatementIndex < aLoop.mBodyStatements.size(); ++aStatementIndex) {
                AppendBodyDecorations(aLoop, aStatementIndex, 2, &aLines);
                const GStatement &aStatement = aLoop.mBodyStatements[aStatementIndex];
                const std::vector<std::string> aStatementLines = CppStatementLines(aStatement);
                for (const std::string &aStatementLine : aStatementLines) {
                    aLines.push_back(Indent(2) + aStatementLine);
                }
            }
            AppendBodyDecorations(aLoop, aLoop.mBodyStatements.size(), 2, &aLines);
            aLines.push_back(Indent(1) + "}");
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

std::string GBatch::BuildCppScopeBlock(std::string *pErrorMessage,
                                       bool pEmitDeclarations) const {
    const std::string aFunctionText = BuildCpp("__GeneratedScopeBlock", pErrorMessage, pEmitDeclarations);
    if (aFunctionText.empty()) {
        return "";
    }

    const std::size_t aBodyStart = aFunctionText.find('{');
    const std::size_t aBodyEnd = aFunctionText.rfind('}');
    if ((aBodyStart == std::string::npos) ||
        (aBodyEnd == std::string::npos) ||
        (aBodyEnd <= aBodyStart)) {
        SetError(pErrorMessage, "Failed to convert batch function text into scope block.");
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
                     std::string *pErrorMessage) const {
    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    return ExecuteWithVariables(pWorkspace, pExpander, &aVariables, pErrorMessage);
}

bool GBatch::ExecuteWithVariables(TwistWorkSpace *pWorkspace,
                                  TwistExpander *pExpander,
                                  std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                                  std::string *pErrorMessage) const {
    if (IsInvalid()) {
        SetError(pErrorMessage, "Batch was invalid and could not be executed.");
        return false;
    }
    if (pVariables == nullptr) {
        SetError(pErrorMessage, "Batch variable map was null.");
        return false;
    }

    for (const std::string &aName : CollectVariableNames()) {
        if (pVariables->find(aName) == pVariables->end()) {
            (*pVariables)[aName] = 0ULL;
        }
    }

    if (!mWorkItems.empty()) {
        for (const GBatchWorkItem &aItem : mWorkItems) {
            if (aItem.IsLoop()) {
                const GLoop &aLoop = aItem.mLoop;
                if (!ExecuteStatementSequence(&aLoop.mInitializationStatements,
                                              pWorkspace,
                                              pExpander,
                                              pVariables,
                                              pErrorMessage)) {
                    return false;
                }

                const int aLoopEnd = ResolveLengthText(aLoop.mLoopEndText);
                for (int aLoopValue = aLoop.mLoopBegin;
                     (aLoop.mLoopStep > 0) ? (aLoopValue < aLoopEnd) : (aLoopValue > aLoopEnd);
                     aLoopValue += aLoop.mLoopStep) {
                    (*pVariables)[aLoop.mLoopVariableName] = static_cast<GRuntimeScalar>(aLoopValue);
                    if (!ExecuteStatementSequence(&aLoop.mBodyStatements,
                                                  pWorkspace,
                                                  pExpander,
                                                  pVariables,
                                                  pErrorMessage)) {
                        return false;
                    }
                }
                continue;
            }
            if (!ExecuteStatementSequence(&aItem.mStatements,
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          pErrorMessage)) {
                return false;
            }
        }
    } else {
        for (const GLoop &aLoop : mLoops) {
            if (!ExecuteStatementSequence(&aLoop.mInitializationStatements,
                                          pWorkspace,
                                          pExpander,
                                          pVariables,
                                          pErrorMessage)) {
                return false;
            }

            const int aLoopEnd = ResolveLengthText(aLoop.mLoopEndText);
            for (int aLoopValue = aLoop.mLoopBegin;
                 (aLoop.mLoopStep > 0) ? (aLoopValue < aLoopEnd) : (aLoopValue > aLoopEnd);
                 aLoopValue += aLoop.mLoopStep) {
                (*pVariables)[aLoop.mLoopVariableName] = static_cast<GRuntimeScalar>(aLoopValue);
                if (!ExecuteStatementSequence(&aLoop.mBodyStatements,
                                              pWorkspace,
                                              pExpander,
                                              pVariables,
                                              pErrorMessage)) {
                    return false;
                }
            }
        }
    }

    return true;
}
