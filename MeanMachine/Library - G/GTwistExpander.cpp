//
//  GTwistExpander.cpp
//  MeanMachine
//

#include "GTwistExpander.hpp"

#include "FileIO.hpp"
#include "GJson.hpp"
#include "Random.hpp"
#include "SBoxTables.hpp"
#include "SaltTables.hpp"
#include "TwistCryptoGenerator.hpp"
#include "TwistFarmSBox.hpp"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <filesystem>

using MeanMachine_json::JsonValue;

namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

std::string ResolveInputPath(const std::string &pPath) {
    if (pPath.empty()) {
        return "";
    }

    const std::filesystem::path aInputPath(pPath);
    if (aInputPath.is_absolute()) {
        return aInputPath.lexically_normal().generic_string();
    }

    const std::filesystem::path aProjectRoot(FileIO::ProjectRoot());
    return (aProjectRoot / aInputPath).lexically_normal().generic_string();
}

bool LoadTextFile(const std::string &pPath,
                  std::string *pText,
                  std::string *pErrorMessage) {
    if (pText == nullptr) {
        SetError(pErrorMessage, "output text pointer was null.");
        return false;
    }

    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes)) {
        SetError(pErrorMessage, "failed to read JSON file: " + pPath);
        return false;
    }

    pText->assign(aBytes.begin(), aBytes.end());
    return true;
}

template <typename T>
void EnsureTableSize(std::vector<T> *pTable,
                     const int pLength,
                     const bool pIdentityFallback) {
    if (pTable == nullptr) {
        return;
    }

    if (pTable->size() > static_cast<std::size_t>(pLength)) {
        pTable->resize(static_cast<std::size_t>(pLength));
    }

    while (pTable->size() < static_cast<std::size_t>(pLength)) {
        T aValue = static_cast<T>(0);
        if (pIdentityFallback) {
            aValue = static_cast<T>(pTable->size() & 0xFFU);
        }
        pTable->push_back(aValue);
    }
}

bool ParseByteArray(const JsonValue *pArrayValue,
                    std::vector<std::uint8_t> *pOut,
                    std::string *pErrorMessage) {
    if (pOut == nullptr) {
        SetError(pErrorMessage, "byte-array output argument was null.");
        return false;
    }
    if (pArrayValue == nullptr) {
        pOut->clear();
        return true;
    }
    if (!pArrayValue->is_array()) {
        SetError(pErrorMessage, "expected byte table to be an array.");
        return false;
    }

    std::vector<std::uint8_t> aOut;
    aOut.reserve(pArrayValue->as_array().size());
    for (const JsonValue &aValue : pArrayValue->as_array()) {
        int aByte = -1;
        if (aValue.is_number()) {
            aByte = static_cast<int>(aValue.as_number());
        } else if (aValue.is_string()) {
            try {
                aByte = std::stoi(aValue.as_string());
            } catch (...) {
                SetError(pErrorMessage, "byte table had invalid string value.");
                return false;
            }
        } else {
            SetError(pErrorMessage, "byte table had non-numeric entry.");
            return false;
        }

        if ((aByte < 0) || (aByte > 255)) {
            SetError(pErrorMessage, "byte table entry outside [0,255].");
            return false;
        }
        aOut.push_back(static_cast<std::uint8_t>(aByte));
    }

    *pOut = std::move(aOut);
    return true;
}

bool ParseUInt64Array(const JsonValue *pArrayValue,
                      std::vector<std::uint64_t> *pOut,
                      std::string *pErrorMessage) {
    if (pOut == nullptr) {
        SetError(pErrorMessage, "uint64-array output argument was null.");
        return false;
    }
    if (pArrayValue == nullptr) {
        pOut->clear();
        return true;
    }
    if (!pArrayValue->is_array()) {
        SetError(pErrorMessage, "expected uint64 table to be an array.");
        return false;
    }

    std::vector<std::uint64_t> aOut;
    aOut.reserve(pArrayValue->as_array().size());
    for (const JsonValue &aValue : pArrayValue->as_array()) {
        std::uint64_t aWideValue = 0ULL;
        if (aValue.is_number()) {
            const double aNumber = aValue.as_number();
            if (aNumber < 0.0) {
                SetError(pErrorMessage, "uint64 table had a negative numeric entry.");
                return false;
            }
            aWideValue = static_cast<std::uint64_t>(aNumber);
        } else if (aValue.is_string()) {
            const std::string aText = aValue.as_string();
            char *aEnd = nullptr;
            const unsigned long long aParsed = std::strtoull(aText.c_str(), &aEnd, 0);
            if ((aEnd == nullptr) || (*aEnd != '\0')) {
                SetError(pErrorMessage, "uint64 table had invalid string value.");
                return false;
            }
            aWideValue = static_cast<std::uint64_t>(aParsed);
        } else {
            SetError(pErrorMessage, "uint64 table had non-numeric entry.");
            return false;
        }
        aOut.push_back(aWideValue);
    }

    *pOut = std::move(aOut);
    return true;
}

bool ParseBranch(const JsonValue &pRoot,
                 const std::string &pBranchName,
                 TwistProgramBranch *pBranch,
                 std::string *pErrorMessage) {
    if (pBranch == nullptr) {
        SetError(pErrorMessage, "branch output was null.");
        return false;
    }

    const JsonValue *aBranchValue = pRoot.find(pBranchName);
    if ((aBranchValue == nullptr) || !aBranchValue->is_object()) {
        return false;
    }

    pBranch->Clear();

    std::vector<GBatch> aParsedBatches;
    const JsonValue *aBatchesValue = aBranchValue->find("batches");
    if ((aBatchesValue != nullptr) && aBatchesValue->is_array()) {
        for (const JsonValue &aBatchValue : aBatchesValue->as_array()) {
            if (!aBatchValue.is_object()) {
                SetError(pErrorMessage, "branch '" + pBranchName + "' has non-object batch entry.");
                return false;
            }

            GBatch aBatch;
            std::string aBatchError;
            if (!GBatch::FromJson(aBatchValue.Serialize(), &aBatch, &aBatchError)) {
                SetError(pErrorMessage, "failed to parse branch batch JSON: " + aBatchError);
                return false;
            }
            aParsedBatches.push_back(aBatch);
        }
    }

    std::vector<std::string> aParsedLines;
    const JsonValue *aStringLinesValue = aBranchValue->find("string_lines");
    if ((aStringLinesValue != nullptr) && aStringLinesValue->is_array()) {
        for (const JsonValue &aLineValue : aStringLinesValue->as_array()) {
            if (!aLineValue.is_string()) {
                SetError(pErrorMessage, "branch '" + pBranchName + "' has non-string line entry.");
                return false;
            }
            aParsedLines.push_back(aLineValue.as_string());
        }
    }

    const JsonValue *aSequenceValue = aBranchValue->find("sequence");
    if ((aSequenceValue != nullptr) && aSequenceValue->is_array()) {
        for (const JsonValue &aStepValue : aSequenceValue->as_array()) {
            if (!aStepValue.is_object()) {
                SetError(pErrorMessage, "branch '" + pBranchName + "' has non-object sequence step.");
                return false;
            }

            const JsonValue *aTypeValue = aStepValue.find("type");
            const JsonValue *aIndexValue = aStepValue.find("index");
            if ((aTypeValue == nullptr) || (aIndexValue == nullptr) ||
                !aTypeValue->is_string() || !aIndexValue->is_number()) {
                SetError(pErrorMessage, "branch '" + pBranchName + "' has malformed sequence step.");
                return false;
            }

            const std::string aType = aTypeValue->as_string();
            const std::size_t aIndex = static_cast<std::size_t>(aIndexValue->as_number());
            if (aType == "line") {
                if (aIndex >= aParsedLines.size()) {
                    SetError(pErrorMessage, "branch '" + pBranchName + "' line sequence index out of range.");
                    return false;
                }
                pBranch->AddLine(aParsedLines[aIndex]);
            } else if (aType == "batch") {
                if (aIndex >= aParsedBatches.size()) {
                    SetError(pErrorMessage, "branch '" + pBranchName + "' batch sequence index out of range.");
                    return false;
                }
                pBranch->AddBatch(aParsedBatches[aIndex]);
            } else {
                SetError(pErrorMessage, "branch '" + pBranchName + "' has unknown sequence step type.");
                return false;
            }
        }
        return true;
    }

    // Legacy branch JSON used separate arrays with implicit order: lines, then batches.
    for (const std::string &aLine : aParsedLines) {
        pBranch->AddLine(aLine);
    }
    for (const GBatch &aBatch : aParsedBatches) {
        pBranch->AddBatch(aBatch);
    }

    return true;
}

bool ParseTables(const JsonValue &pRoot,
                 GTwistExpander *pExpander,
                 std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        SetError(pErrorMessage, "expander output was null.");
        return false;
    }

    const JsonValue *aTables = pRoot.find("tables");
    if ((aTables == nullptr) || !aTables->is_object()) {
        return true;
    }

    if (!ParseByteArray(aTables->find("sbox_a"), &pExpander->_mSBoxA, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("sbox_b"), &pExpander->_mSBoxB, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("sbox_c"), &pExpander->_mSBoxC, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("sbox_d"), &pExpander->_mSBoxD, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("sbox_e"), &pExpander->_mSBoxE, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("sbox_f"), &pExpander->_mSBoxF, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("sbox_g"), &pExpander->_mSBoxG, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("sbox_h"), &pExpander->_mSBoxH, pErrorMessage)) { return false; }

    auto ParseSaltWithLegacyFallback = [&](const char *pKey,
                                           std::vector<std::uint64_t> *pSaltOut) -> bool {
        const JsonValue *aSaltValue = aTables->find(pKey);
        if (!ParseUInt64Array(aSaltValue, pSaltOut, pErrorMessage)) {
            return false;
        }
        if (!pSaltOut->empty()) {
            return true;
        }

        std::vector<std::uint8_t> aLegacyBytes;
        if (!ParseByteArray(aSaltValue, &aLegacyBytes, pErrorMessage)) {
            return false;
        }
        pSaltOut->reserve(aLegacyBytes.size());
        for (std::uint8_t aByte : aLegacyBytes) {
            pSaltOut->push_back(static_cast<std::uint64_t>(aByte));
        }
        return true;
    };

    if (!ParseSaltWithLegacyFallback("salt_a", &pExpander->_mSaltA)) { return false; }
    if (!ParseSaltWithLegacyFallback("salt_b", &pExpander->_mSaltB)) { return false; }
    if (!ParseSaltWithLegacyFallback("salt_c", &pExpander->_mSaltC)) { return false; }
    if (!ParseSaltWithLegacyFallback("salt_d", &pExpander->_mSaltD)) { return false; }
    if (!ParseSaltWithLegacyFallback("salt_e", &pExpander->_mSaltE)) { return false; }
    if (!ParseSaltWithLegacyFallback("salt_f", &pExpander->_mSaltF)) { return false; }
    if (!ParseSaltWithLegacyFallback("salt_g", &pExpander->_mSaltG)) { return false; }
    if (!ParseSaltWithLegacyFallback("salt_h", &pExpander->_mSaltH)) { return false; }

    auto ParseDomainConstantOptional = [&](const char *pKey,
                                           std::uint64_t *pDest) -> bool {
        if ((pKey == nullptr) || (pDest == nullptr)) {
            return true;
        }

        const JsonValue *aValue = aTables->find(pKey);
        if (aValue == nullptr) {
            return true;
        }

        if (aValue->is_number()) {
            const double aNumber = aValue->as_number();
            if (aNumber < 0.0) {
                SetError(pErrorMessage, "domain constant was negative: " + std::string(pKey));
                return false;
            }
            *pDest = static_cast<std::uint64_t>(aNumber);
            return true;
        }

        if (aValue->is_string()) {
            const std::string aText = aValue->as_string();
            char *aEnd = nullptr;
            const unsigned long long aParsed = std::strtoull(aText.c_str(), &aEnd, 0);
            if ((aEnd == nullptr) || (*aEnd != '\0')) {
                SetError(pErrorMessage, "domain constant had invalid string value: " + std::string(pKey));
                return false;
            }
            *pDest = static_cast<std::uint64_t>(aParsed);
            return true;
        }

        SetError(pErrorMessage, "domain constant had invalid type: " + std::string(pKey));
        return false;
    };

    if (!ParseDomainConstantOptional("domain_constant_public_ingress", &pExpander->mDomainConstantPublicIngress)) { return false; }
    if (!ParseDomainConstantOptional("domain_constant_private_ingress", &pExpander->mDomainConstantPrivateIngress)) { return false; }
    if (!ParseDomainConstantOptional("domain_constant_cross_ingress", &pExpander->mDomainConstantCrossIngress)) { return false; }

    auto ParseDomainSaltOptional = [&](const char *pKey,
                                       std::uint64_t *pDest) -> bool {
        if ((pKey == nullptr) || (pDest == nullptr)) {
            return true;
        }

        const JsonValue *aDomainValue = aTables->find(pKey);
        if (aDomainValue == nullptr) {
            return true;
        }

        std::vector<std::uint64_t> aWideSalt;
        if (!ParseUInt64Array(aDomainValue, &aWideSalt, pErrorMessage)) {
            return false;
        }

        if (aWideSalt.empty()) {
            std::vector<std::uint8_t> aLegacyBytes;
            if (!ParseByteArray(aDomainValue, &aLegacyBytes, pErrorMessage)) {
                return false;
            }
            for (const std::uint8_t aByte : aLegacyBytes) {
                aWideSalt.push_back(static_cast<std::uint64_t>(aByte));
            }
        }

        if (aWideSalt.empty()) {
            return true;
        }

        if (aWideSalt.size() < static_cast<std::size_t>(S_SALT)) {
            aWideSalt.resize(static_cast<std::size_t>(S_SALT), 0ULL);
        }
        if (aWideSalt.size() > static_cast<std::size_t>(S_SALT)) {
            aWideSalt.resize(static_cast<std::size_t>(S_SALT));
        }

        std::memcpy(pDest,
                    aWideSalt.data(),
                    sizeof(std::uint64_t) * static_cast<std::size_t>(S_SALT));
        return true;
    };

    if (!ParseDomainSaltOptional("domain_salt_keybox_a", pExpander->mDomainSaltKeyBoxA)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_b", pExpander->mDomainSaltKeyBoxB)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_c", pExpander->mDomainSaltKeyBoxC)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_d", pExpander->mDomainSaltKeyBoxD)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_e", pExpander->mDomainSaltKeyBoxE)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_f", pExpander->mDomainSaltKeyBoxF)) { return false; }

    if (!ParseDomainSaltOptional("domain_salt_maskbox_a", pExpander->mDomainSaltMaskBoxA)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_maskbox_b", pExpander->mDomainSaltMaskBoxB)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_maskbox_c", pExpander->mDomainSaltMaskBoxC)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_maskbox_d", pExpander->mDomainSaltMaskBoxD)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_maskbox_e", pExpander->mDomainSaltMaskBoxE)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_maskbox_f", pExpander->mDomainSaltMaskBoxF)) { return false; }

    if (!ParseDomainSaltOptional("domain_salt_wanderer_a", pExpander->mDomainSaltWandererA)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_wanderer_b", pExpander->mDomainSaltWandererB)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_wanderer_c", pExpander->mDomainSaltWandererC)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_wanderer_d", pExpander->mDomainSaltWandererD)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_wanderer_e", pExpander->mDomainSaltWandererE)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_wanderer_f", pExpander->mDomainSaltWandererF)) { return false; }

    if (!ParseDomainSaltOptional("domain_salt_orbiter_a", pExpander->mDomainSaltOrbiterA)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_orbiter_b", pExpander->mDomainSaltOrbiterB)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_orbiter_c", pExpander->mDomainSaltOrbiterC)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_orbiter_d", pExpander->mDomainSaltOrbiterD)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_orbiter_e", pExpander->mDomainSaltOrbiterE)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_orbiter_f", pExpander->mDomainSaltOrbiterF)) { return false; }

    if (!ParseDomainSaltOptional("domain_salt_prism_a", pExpander->mDomainSaltPrismA)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_prism_b", pExpander->mDomainSaltPrismB)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_prism_c", pExpander->mDomainSaltPrismC)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_prism_d", pExpander->mDomainSaltPrismD)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_prism_e", pExpander->mDomainSaltPrismE)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_prism_f", pExpander->mDomainSaltPrismF)) { return false; }

    if (!ParseDomainSaltOptional("domain_salt_source_a", pExpander->mDomainSaltSourceA)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_b", pExpander->mDomainSaltSourceB)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_c", pExpander->mDomainSaltSourceC)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_d", pExpander->mDomainSaltSourceD)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_e", pExpander->mDomainSaltSourceE)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_f", pExpander->mDomainSaltSourceF)) { return false; }

    return true;
}

bool ExecuteBatchJsonText(const std::vector<std::string> &pBatchJsonText,
                          TwistWorkSpace *pWorkspace,
                          TwistExpander *pExpander,
                          std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                          std::string *pErrorMessage) {
    if (pVariables == nullptr) {
        SetError(pErrorMessage, "batch variable map was null.");
        return false;
    }

    for (const std::string &aBatchJson : pBatchJsonText) {
        GBatch aBatch;
        if (!GBatch::FromJson(aBatchJson, &aBatch, pErrorMessage)) {
            if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
                *pErrorMessage = "failed to parse batch JSON.";
            }
            return false;
        }

        if (!aBatch.ExecuteWithVariables(pWorkspace, pExpander, pVariables, pErrorMessage)) {
            if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
                *pErrorMessage = "batch execution failed.";
            }
            return false;
        }
    }
    return true;
}

std::string TrimCopy(const std::string &pText) {
    std::size_t aStart = 0U;
    while ((aStart < pText.size()) && std::isspace(static_cast<unsigned char>(pText[aStart]))) {
        aStart += 1U;
    }

    std::size_t aEnd = pText.size();
    while ((aEnd > aStart) && std::isspace(static_cast<unsigned char>(pText[aEnd - 1U]))) {
        aEnd -= 1U;
    }
    return pText.substr(aStart, aEnd - aStart);
}

bool IsIdentifier(const std::string &pName) {
    if (pName.empty()) {
        return false;
    }
    const unsigned char aFirst = static_cast<unsigned char>(pName[0]);
    if (!(std::isalpha(aFirst) || (aFirst == '_'))) {
        return false;
    }
    for (const unsigned char aCh : pName) {
        if (!(std::isalnum(aCh) || (aCh == '_'))) {
            return false;
        }
    }
    return true;
}

void StripOuterParens(std::string *pText) {
    if (pText == nullptr) {
        return;
    }
    while (pText->size() >= 2U && pText->front() == '(' && pText->back() == ')') {
        *pText = TrimCopy(pText->substr(1U, pText->size() - 2U));
    }
}

bool ParseIntLiteral(std::string pValueText,
                     int *pValueOut) {
    if (pValueOut == nullptr) {
        return false;
    }

    pValueText = TrimCopy(pValueText);
    if (pValueText.empty()) {
        return false;
    }

    StripOuterParens(&pValueText);

    while (!pValueText.empty()) {
        const char aLast = pValueText.back();
        if (aLast == 'u' || aLast == 'U' || aLast == 'l' || aLast == 'L') {
            pValueText.pop_back();
            pValueText = TrimCopy(pValueText);
            continue;
        }
        break;
    }

    if (pValueText.empty()) {
        return false;
    }

    const char *aStart = pValueText.c_str();
    char *aEnd = nullptr;
    const long aValue = std::strtol(aStart, &aEnd, 0);
    if ((aEnd == nullptr) || (*aEnd != '\0')) {
        return false;
    }
    *pValueOut = static_cast<int>(aValue);
    return true;
}

bool ResolveAliasSlot(const std::string &pAlias,
                      TwistWorkSpaceSlot *pSlotOut) {
    if (pSlotOut == nullptr) {
        return false;
    }

    auto NormalizeAliasToken = [](const std::string &pToken) -> std::string {
        std::string aToken = TrimCopy(pToken);
        if (aToken.empty()) {
            return aToken;
        }

        while (!aToken.empty() && ((aToken[0] == '&') || (aToken[0] == '*'))) {
            aToken.erase(aToken.begin());
            aToken = TrimCopy(aToken);
        }

        const std::size_t aBracketPos = aToken.find('[');
        if (aBracketPos != std::string::npos) {
            aToken = TrimCopy(aToken.substr(0U, aBracketPos));
        }

        const std::size_t aArrowPos = aToken.rfind("->");
        const std::size_t aDotPos = aToken.rfind('.');
        std::size_t aMemberPos = std::string::npos;
        if (aArrowPos != std::string::npos) {
            aMemberPos = aArrowPos + 2U;
        }
        if (aDotPos != std::string::npos) {
            const std::size_t aDotMemberPos = aDotPos + 1U;
            if ((aMemberPos == std::string::npos) || (aDotMemberPos > aMemberPos)) {
                aMemberPos = aDotMemberPos;
            }
        }
        if ((aMemberPos != std::string::npos) && (aMemberPos < aToken.size())) {
            aToken = TrimCopy(aToken.substr(aMemberPos));
        }

        return aToken;
    };

    const std::string aAlias = NormalizeAliasToken(pAlias);

    static const TwistWorkSpaceSlot kKnownSlots[] = {
        TwistWorkSpaceSlot::kSource,
        TwistWorkSpaceSlot::kDest,

        TwistWorkSpaceSlot::kSaltA,
        TwistWorkSpaceSlot::kSaltB,
        TwistWorkSpaceSlot::kSaltC,
        TwistWorkSpaceSlot::kSaltD,
        TwistWorkSpaceSlot::kSaltE,
        TwistWorkSpaceSlot::kSaltF,
        TwistWorkSpaceSlot::kSaltG,
        TwistWorkSpaceSlot::kSaltH,
        TwistWorkSpaceSlot::kDomainSaltKeyBoxA,
        TwistWorkSpaceSlot::kDomainSaltKeyBoxB,
        TwistWorkSpaceSlot::kDomainSaltKeyBoxC,
        TwistWorkSpaceSlot::kDomainSaltKeyBoxD,
        TwistWorkSpaceSlot::kDomainSaltKeyBoxE,
        TwistWorkSpaceSlot::kDomainSaltKeyBoxF,
        TwistWorkSpaceSlot::kDomainSaltMaskBoxA,
        TwistWorkSpaceSlot::kDomainSaltMaskBoxB,
        TwistWorkSpaceSlot::kDomainSaltMaskBoxC,
        TwistWorkSpaceSlot::kDomainSaltMaskBoxD,
        TwistWorkSpaceSlot::kDomainSaltMaskBoxE,
        TwistWorkSpaceSlot::kDomainSaltMaskBoxF,
        TwistWorkSpaceSlot::kDomainSaltWandererA,
        TwistWorkSpaceSlot::kDomainSaltWandererB,
        TwistWorkSpaceSlot::kDomainSaltWandererC,
        TwistWorkSpaceSlot::kDomainSaltWandererD,
        TwistWorkSpaceSlot::kDomainSaltWandererE,
        TwistWorkSpaceSlot::kDomainSaltWandererF,
        TwistWorkSpaceSlot::kDomainSaltOrbiterA,
        TwistWorkSpaceSlot::kDomainSaltOrbiterB,
        TwistWorkSpaceSlot::kDomainSaltOrbiterC,
        TwistWorkSpaceSlot::kDomainSaltOrbiterD,
        TwistWorkSpaceSlot::kDomainSaltOrbiterE,
        TwistWorkSpaceSlot::kDomainSaltOrbiterF,
        TwistWorkSpaceSlot::kDomainSaltPrismA,
        TwistWorkSpaceSlot::kDomainSaltPrismB,
        TwistWorkSpaceSlot::kDomainSaltPrismC,
        TwistWorkSpaceSlot::kDomainSaltPrismD,
        TwistWorkSpaceSlot::kDomainSaltPrismE,
        TwistWorkSpaceSlot::kDomainSaltPrismF,
        TwistWorkSpaceSlot::kDomainSaltSourceA,
        TwistWorkSpaceSlot::kDomainSaltSourceB,
        TwistWorkSpaceSlot::kDomainSaltSourceC,
        TwistWorkSpaceSlot::kDomainSaltSourceD,
        TwistWorkSpaceSlot::kDomainSaltSourceE,
        TwistWorkSpaceSlot::kDomainSaltSourceF,
        TwistWorkSpaceSlot::kSaltA,
        TwistWorkSpaceSlot::kSaltB,
        TwistWorkSpaceSlot::kSaltC,
        TwistWorkSpaceSlot::kSaltD,
        TwistWorkSpaceSlot::kDerivedSaltA,
        TwistWorkSpaceSlot::kDerivedSaltB,
        TwistWorkSpaceSlot::kDerivedSaltC,
        TwistWorkSpaceSlot::kDerivedSaltD,
        TwistWorkSpaceSlot::kDerivedSaltE,
        TwistWorkSpaceSlot::kDerivedSaltF,
        TwistWorkSpaceSlot::kDerivedSaltG,
        TwistWorkSpaceSlot::kDerivedSaltH,
        TwistWorkSpaceSlot::kDerivedSaltOrbiterA,
        TwistWorkSpaceSlot::kDerivedSaltOrbiterB,
        TwistWorkSpaceSlot::kDerivedSaltOrbiterC,
        TwistWorkSpaceSlot::kDerivedSaltOrbiterD,
        TwistWorkSpaceSlot::kDerivedSaltWandererA,
        TwistWorkSpaceSlot::kDerivedSaltWandererB,
        TwistWorkSpaceSlot::kDerivedSaltWandererC,
        TwistWorkSpaceSlot::kDerivedSaltWandererD,

        TwistWorkSpaceSlot::kSBoxA,
        TwistWorkSpaceSlot::kSBoxB,
        TwistWorkSpaceSlot::kSBoxC,
        TwistWorkSpaceSlot::kSBoxD,
        TwistWorkSpaceSlot::kSBoxE,
        TwistWorkSpaceSlot::kSBoxF,
        TwistWorkSpaceSlot::kSBoxG,
        TwistWorkSpaceSlot::kSBoxH,
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

    for (TwistWorkSpaceSlot aSlot : kKnownSlots) {
        if (BufAliasName(aSlot) == aAlias) {
            *pSlotOut = aSlot;
            return true;
        }
    }

    struct AliasSlotPair {
        const char *mAlias;
        TwistWorkSpaceSlot mSlot;
    };

    static const AliasSlotPair kWorkspaceFieldAliases[] = {
        {"mSaltA", TwistWorkSpaceSlot::kSaltA},
        {"mSaltB", TwistWorkSpaceSlot::kSaltB},
        {"mSaltC", TwistWorkSpaceSlot::kSaltC},
        {"mSaltD", TwistWorkSpaceSlot::kSaltD},
        {"mSaltE", TwistWorkSpaceSlot::kSaltE},
        {"mSaltF", TwistWorkSpaceSlot::kSaltF},
        {"mSaltG", TwistWorkSpaceSlot::kSaltG},
        {"mSaltH", TwistWorkSpaceSlot::kSaltH},
        {"mDomainSaltKeyBoxA", TwistWorkSpaceSlot::kDomainSaltKeyBoxA},
        {"mDomainSaltKeyBoxB", TwistWorkSpaceSlot::kDomainSaltKeyBoxB},
        {"mDomainSaltKeyBoxC", TwistWorkSpaceSlot::kDomainSaltKeyBoxC},
        {"mDomainSaltKeyBoxD", TwistWorkSpaceSlot::kDomainSaltKeyBoxD},
        {"mDomainSaltKeyBoxE", TwistWorkSpaceSlot::kDomainSaltKeyBoxE},
        {"mDomainSaltKeyBoxF", TwistWorkSpaceSlot::kDomainSaltKeyBoxF},
        {"mDomainSaltMaskBoxA", TwistWorkSpaceSlot::kDomainSaltMaskBoxA},
        {"mDomainSaltMaskBoxB", TwistWorkSpaceSlot::kDomainSaltMaskBoxB},
        {"mDomainSaltMaskBoxC", TwistWorkSpaceSlot::kDomainSaltMaskBoxC},
        {"mDomainSaltMaskBoxD", TwistWorkSpaceSlot::kDomainSaltMaskBoxD},
        {"mDomainSaltMaskBoxE", TwistWorkSpaceSlot::kDomainSaltMaskBoxE},
        {"mDomainSaltMaskBoxF", TwistWorkSpaceSlot::kDomainSaltMaskBoxF},
        {"mDomainSaltWandererA", TwistWorkSpaceSlot::kDomainSaltWandererA},
        {"mDomainSaltWandererB", TwistWorkSpaceSlot::kDomainSaltWandererB},
        {"mDomainSaltWandererC", TwistWorkSpaceSlot::kDomainSaltWandererC},
        {"mDomainSaltWandererD", TwistWorkSpaceSlot::kDomainSaltWandererD},
        {"mDomainSaltWandererE", TwistWorkSpaceSlot::kDomainSaltWandererE},
        {"mDomainSaltWandererF", TwistWorkSpaceSlot::kDomainSaltWandererF},
        {"mDomainSaltOrbiterA", TwistWorkSpaceSlot::kDomainSaltOrbiterA},
        {"mDomainSaltOrbiterB", TwistWorkSpaceSlot::kDomainSaltOrbiterB},
        {"mDomainSaltOrbiterC", TwistWorkSpaceSlot::kDomainSaltOrbiterC},
        {"mDomainSaltOrbiterD", TwistWorkSpaceSlot::kDomainSaltOrbiterD},
        {"mDomainSaltOrbiterE", TwistWorkSpaceSlot::kDomainSaltOrbiterE},
        {"mDomainSaltOrbiterF", TwistWorkSpaceSlot::kDomainSaltOrbiterF},
        {"mDomainSaltPrismA", TwistWorkSpaceSlot::kDomainSaltPrismA},
        {"mDomainSaltPrismB", TwistWorkSpaceSlot::kDomainSaltPrismB},
        {"mDomainSaltPrismC", TwistWorkSpaceSlot::kDomainSaltPrismC},
        {"mDomainSaltPrismD", TwistWorkSpaceSlot::kDomainSaltPrismD},
        {"mDomainSaltPrismE", TwistWorkSpaceSlot::kDomainSaltPrismE},
        {"mDomainSaltPrismF", TwistWorkSpaceSlot::kDomainSaltPrismF},
        {"mDomainSaltSourceA", TwistWorkSpaceSlot::kDomainSaltSourceA},
        {"mDomainSaltSourceB", TwistWorkSpaceSlot::kDomainSaltSourceB},
        {"mDomainSaltSourceC", TwistWorkSpaceSlot::kDomainSaltSourceC},
        {"mDomainSaltSourceD", TwistWorkSpaceSlot::kDomainSaltSourceD},
        {"mDomainSaltSourceE", TwistWorkSpaceSlot::kDomainSaltSourceE},
        {"mDomainSaltSourceF", TwistWorkSpaceSlot::kDomainSaltSourceF},
        {"mDerivedSaltA", TwistWorkSpaceSlot::kDerivedSaltA},
        {"mDerivedSaltB", TwistWorkSpaceSlot::kDerivedSaltB},
        {"mDerivedSaltC", TwistWorkSpaceSlot::kDerivedSaltC},
        {"mDerivedSaltD", TwistWorkSpaceSlot::kDerivedSaltD},
        {"mDerivedSaltE", TwistWorkSpaceSlot::kDerivedSaltE},
        {"mDerivedSaltF", TwistWorkSpaceSlot::kDerivedSaltF},
        {"mDerivedSaltG", TwistWorkSpaceSlot::kDerivedSaltG},
        {"mDerivedSaltH", TwistWorkSpaceSlot::kDerivedSaltH},
        {"mDerivedSaltOrbiterA", TwistWorkSpaceSlot::kDerivedSaltOrbiterA},
        {"mDerivedSaltOrbiterB", TwistWorkSpaceSlot::kDerivedSaltOrbiterB},
        {"mDerivedSaltOrbiterC", TwistWorkSpaceSlot::kDerivedSaltOrbiterC},
        {"mDerivedSaltOrbiterD", TwistWorkSpaceSlot::kDerivedSaltOrbiterD},
        {"mDerivedSaltWandererA", TwistWorkSpaceSlot::kDerivedSaltWandererA},
        {"mDerivedSaltWandererB", TwistWorkSpaceSlot::kDerivedSaltWandererB},
        {"mDerivedSaltWandererC", TwistWorkSpaceSlot::kDerivedSaltWandererC},
        {"mDerivedSaltWandererD", TwistWorkSpaceSlot::kDerivedSaltWandererD},
        {"mSBoxA", TwistWorkSpaceSlot::kSBoxA},
        {"mSBoxB", TwistWorkSpaceSlot::kSBoxB},
        {"mSBoxC", TwistWorkSpaceSlot::kSBoxC},
        {"mSBoxD", TwistWorkSpaceSlot::kSBoxD},
        {"mSBoxE", TwistWorkSpaceSlot::kSBoxE},
        {"mSBoxF", TwistWorkSpaceSlot::kSBoxF},
        {"mSBoxG", TwistWorkSpaceSlot::kSBoxG},
        {"mSBoxH", TwistWorkSpaceSlot::kSBoxH},
        {"mDerivedSBoxA", TwistWorkSpaceSlot::kDerivedSBoxA},
        {"mDerivedSBoxB", TwistWorkSpaceSlot::kDerivedSBoxB},
        {"mDerivedSBoxC", TwistWorkSpaceSlot::kDerivedSBoxC},
        {"mDerivedSBoxD", TwistWorkSpaceSlot::kDerivedSBoxD},
        {"mDerivedSBoxE", TwistWorkSpaceSlot::kDerivedSBoxE},
        {"mDerivedSBoxF", TwistWorkSpaceSlot::kDerivedSBoxF},
        {"mDerivedSBoxG", TwistWorkSpaceSlot::kDerivedSBoxG},
        {"mDerivedSBoxH", TwistWorkSpaceSlot::kDerivedSBoxH},
        {"mExpandLaneA", TwistWorkSpaceSlot::kSeedExpansionLaneA},
        {"mExpandLaneB", TwistWorkSpaceSlot::kSeedExpansionLaneB},
        {"mExpandLaneC", TwistWorkSpaceSlot::kSeedExpansionLaneC},
        {"mExpandLaneD", TwistWorkSpaceSlot::kSeedExpansionLaneD},
        {"mWorkLaneA", TwistWorkSpaceSlot::kWorkLaneA},
        {"mWorkLaneB", TwistWorkSpaceSlot::kWorkLaneB},
        {"mWorkLaneC", TwistWorkSpaceSlot::kWorkLaneC},
        {"mWorkLaneD", TwistWorkSpaceSlot::kWorkLaneD},
        {"mOperationLaneA", TwistWorkSpaceSlot::kOperationLaneA},
        {"mOperationLaneB", TwistWorkSpaceSlot::kOperationLaneB},
        {"mMaskLaneA", TwistWorkSpaceSlot::kMaskLaneA},
        {"mMaskLaneB", TwistWorkSpaceSlot::kMaskLaneB}
    };

    for (const AliasSlotPair &aPair : kWorkspaceFieldAliases) {
        if (aAlias == aPair.mAlias) {
            *pSlotOut = aPair.mSlot;
            return true;
        }
    }

    return false;
}

bool ParseCryptoCallArguments(const std::string &pLine,
                              const std::string &pMethodName,
                              std::vector<std::string> *pArgsOut) {
    if (pArgsOut == nullptr) {
        return false;
    }

    std::string aLine = TrimCopy(pLine);
    if (aLine.empty()) {
        return false;
    }

    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimCopy(aLine);
    }

    const std::string aCallTokenDot = "." + pMethodName + "(";
    const std::string aCallTokenArrow = "->" + pMethodName + "(";
    const std::string aCallTokenPlain = pMethodName + "(";
    std::size_t aCallPos = aLine.find(aCallTokenDot);
    std::size_t aOpen = std::string::npos;
    if (aCallPos != std::string::npos) {
        aOpen = aCallPos + aCallTokenDot.size();
    } else {
        aCallPos = aLine.find(aCallTokenArrow);
        if (aCallPos != std::string::npos) {
            aOpen = aCallPos + aCallTokenArrow.size();
        } else if (aLine.rfind(aCallTokenPlain, 0U) == 0U) {
            aCallPos = 0U;
            aOpen = aCallTokenPlain.size();
        }
    }

    if ((aCallPos == std::string::npos) || (aOpen == std::string::npos)) {
        return false;
    }

    const std::size_t aClose = aLine.rfind(')');
    if ((aClose == std::string::npos) || (aClose < aOpen)) {
        return false;
    }

    const std::string aArgsText = aLine.substr(aOpen, aClose - aOpen);
    std::vector<std::string> aArgs;

    std::size_t aCursor = 0U;
    while (aCursor < aArgsText.size()) {
        const std::size_t aComma = aArgsText.find(',', aCursor);
        std::string aToken = (aComma == std::string::npos)
            ? aArgsText.substr(aCursor)
            : aArgsText.substr(aCursor, aComma - aCursor);
        aToken = TrimCopy(aToken);
        if (!aToken.empty()) {
            aArgs.push_back(aToken);
        }
        if (aComma == std::string::npos) {
            break;
        }
        aCursor = aComma + 1U;
    }

    if (aArgs.empty()) {
        return false;
    }

    *pArgsOut = std::move(aArgs);
    return true;
}

bool ExecuteCryptoGeneratorCallLine(const std::string &pLine,
                                    TwistWorkSpace *pWorkspace,
                                    TwistExpander *pExpander,
                                    TwistCryptoGenerator *pCryptoGenerator,
                                    std::string *pErrorMessage) {
    enum class CryptoMethod : std::uint8_t {
        kStepA_MakeSBoxes = 0,
        kStepB_MakeSalts = 1,
        kStepC_MakeSBoxes = 2,
        kStepD_MakeSalts = 3
    };

    std::vector<std::string> aArgs;
    CryptoMethod aMethod = CryptoMethod::kStepA_MakeSBoxes;
    if (ParseCryptoCallArguments(pLine, "StepA_MakeSBoxes", &aArgs)) {
        aMethod = CryptoMethod::kStepA_MakeSBoxes;
    } else if (ParseCryptoCallArguments(pLine, "StepB_MakeSalts", &aArgs)) {
        aMethod = CryptoMethod::kStepB_MakeSalts;
    } else if (ParseCryptoCallArguments(pLine, "StepC_MakeSBoxes", &aArgs)) {
        aMethod = CryptoMethod::kStepC_MakeSBoxes;
    } else if (ParseCryptoCallArguments(pLine, "StepD_MakeSalts", &aArgs)) {
        aMethod = CryptoMethod::kStepD_MakeSalts;
    } else {
        return false;
    }

    const bool aValidCount =
        ((aMethod == CryptoMethod::kStepA_MakeSBoxes) && (aArgs.size() == 13U)) ||
        ((aMethod == CryptoMethod::kStepB_MakeSalts) && (aArgs.size() == 17U)) ||
        ((aMethod == CryptoMethod::kStepC_MakeSBoxes) && (aArgs.size() == 21U)) ||
        ((aMethod == CryptoMethod::kStepD_MakeSalts) && (aArgs.size() == 25U));
    if (!aValidCount) {
        if (aMethod == CryptoMethod::kStepA_MakeSBoxes) {
            SetError(pErrorMessage, "TwistCryptoGenerator::StepA_MakeSBoxes expects 13 arguments.");
        } else if (aMethod == CryptoMethod::kStepB_MakeSalts) {
            SetError(pErrorMessage, "TwistCryptoGenerator::StepB_MakeSalts expects 17 arguments.");
        } else if (aMethod == CryptoMethod::kStepC_MakeSBoxes) {
            SetError(pErrorMessage, "TwistCryptoGenerator::StepC_MakeSBoxes expects 21 arguments.");
        } else {
            SetError(pErrorMessage, "TwistCryptoGenerator::StepD_MakeSalts expects 25 arguments.");
        }
        return false;
    }

    if ((pWorkspace == nullptr) || (pExpander == nullptr) || (pCryptoGenerator == nullptr)) {
        SetError(pErrorMessage, "TwistCryptoGenerator call execution was missing required runtime inputs.");
        return false;
    }

    std::vector<std::uint8_t *> aBuffers;
    aBuffers.reserve(aArgs.size());
    for (const std::string &aAlias : aArgs) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveAliasSlot(aAlias, &aSlot)) {
            SetError(pErrorMessage, "Unknown buffer alias in TwistCryptoGenerator call: " + aAlias);
            return false;
        }

        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace,
                                                          pExpander,
                                                          aSlot);
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "Resolved null buffer for alias: " + aAlias);
            return false;
        }
        aBuffers.push_back(aBuffer);
    }

    if (aMethod == CryptoMethod::kStepA_MakeSBoxes) {
        /*
        pCryptoGenerator->StepA_MakeSBoxes(aBuffers[0],
                                           aBuffers[1], aBuffers[2], aBuffers[3], aBuffers[4],
                                           aBuffers[5], aBuffers[6], aBuffers[7], aBuffers[8],
                                           aBuffers[9], aBuffers[10], aBuffers[11], aBuffers[12]);
        */
        return true;
    }

    if (aMethod == CryptoMethod::kStepB_MakeSalts) {
        /*
        pCryptoGenerator->StepB_MakeSalts(aBuffers[0],
                                          aBuffers[1], aBuffers[2], aBuffers[3], aBuffers[4],
                                          aBuffers[5], aBuffers[6], aBuffers[7], aBuffers[8],
                                          aBuffers[9], aBuffers[10], aBuffers[11], aBuffers[12],
                                          aBuffers[13], aBuffers[14], aBuffers[15], aBuffers[16]);
        */
        return true;
    }

    if (aMethod == CryptoMethod::kStepC_MakeSBoxes) {
        /*
        pCryptoGenerator->StepC_MakeSBoxes(aBuffers[0],
                                           aBuffers[1], aBuffers[2], aBuffers[3], aBuffers[4],
                                           aBuffers[5], aBuffers[6], aBuffers[7], aBuffers[8],
                                           aBuffers[9], aBuffers[10], aBuffers[11], aBuffers[12],
                                           aBuffers[13], aBuffers[14], aBuffers[15], aBuffers[16],
                                           aBuffers[17], aBuffers[18], aBuffers[19], aBuffers[20]);
        */
        return true;
    }

    if (aMethod == CryptoMethod::kStepD_MakeSalts) {
        /*
        pCryptoGenerator->StepD_MakeSalts(aBuffers[0],
                                          aBuffers[1], aBuffers[2], aBuffers[3], aBuffers[4],
                                          aBuffers[5], aBuffers[6], aBuffers[7], aBuffers[8],
                                          aBuffers[9], aBuffers[10], aBuffers[11], aBuffers[12],
                                          aBuffers[13], aBuffers[14], aBuffers[15], aBuffers[16],
                                          aBuffers[17], aBuffers[18], aBuffers[19], aBuffers[20],
                                          aBuffers[21], aBuffers[22], aBuffers[23], aBuffers[24]);
        */
        return true;
    }
    SetError(pErrorMessage, "Unsupported TwistCryptoGenerator step call.");
    return false;
}

bool ExecuteCryptoMakeLine(const std::string &pLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           TwistCryptoGenerator *pCryptoGenerator,
                           std::string *pErrorMessage) {
    return ExecuteCryptoGeneratorCallLine(pLine, pWorkspace, pExpander, pCryptoGenerator, pErrorMessage);
}

bool ExecuteCryptoSaltLine(const std::string &pLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           TwistCryptoGenerator *pCryptoGenerator,
                           std::string *pErrorMessage) {
    return ExecuteCryptoGeneratorCallLine(pLine, pWorkspace, pExpander, pCryptoGenerator, pErrorMessage);
}

bool ParseTwistDomainToken(const std::string &pToken,
                           TwistDomain *pDomainOut) {
    if (pDomainOut == nullptr) {
        return false;
    }

    const std::string aToken = TrimCopy(pToken);
    const std::string kPrefix = "TwistDomain::";
    if (aToken.rfind(kPrefix, 0U) == 0U) {
        const std::string aName = aToken.substr(kPrefix.size());
        if (aName == "kInv") { *pDomainOut = TwistDomain::kInv; return true; }
        if (aName == "kSalts") { *pDomainOut = TwistDomain::kSalts; return true; }
        if (aName == "kSBoxes") { *pDomainOut = TwistDomain::kSBoxes; return true; }
        if (aName == "kKeyBoxA") { *pDomainOut = TwistDomain::kKeyBoxA; return true; }
        if (aName == "kKeyBoxB") { *pDomainOut = TwistDomain::kKeyBoxB; return true; }
        if (aName == "kMaskBoxA") { *pDomainOut = TwistDomain::kMaskBoxA; return true; }
        if (aName == "kMaskBoxB") { *pDomainOut = TwistDomain::kMaskBoxB; return true; }
        if (aName == "kSaltsKeyAWanderer") { *pDomainOut = TwistDomain::kSaltsKeyAWanderer; return true; }
        if (aName == "kSaltsKeyAOrbiter") { *pDomainOut = TwistDomain::kSaltsKeyAOrbiter; return true; }
        if (aName == "kSaltsKeyASeeder") { *pDomainOut = TwistDomain::kSaltsKeyASeeder; return true; }
        if (aName == "kSaltsKeyBWanderer") { *pDomainOut = TwistDomain::kSaltsKeyBWanderer; return true; }
        if (aName == "kSaltsKeyBOrbiter") { *pDomainOut = TwistDomain::kSaltsKeyBOrbiter; return true; }
        if (aName == "kSaltsKeyBSeeder") { *pDomainOut = TwistDomain::kSaltsKeyBSeeder; return true; }
        if (aName == "kSaltsMaskAWanderer") { *pDomainOut = TwistDomain::kSaltsMaskAWanderer; return true; }
        if (aName == "kSaltsMaskAOrbiter") { *pDomainOut = TwistDomain::kSaltsMaskAOrbiter; return true; }
        if (aName == "kSaltsMaskASeeder") { *pDomainOut = TwistDomain::kSaltsMaskASeeder; return true; }
        if (aName == "kSaltsMaskBWanderer") { *pDomainOut = TwistDomain::kSaltsMaskBWanderer; return true; }
        if (aName == "kSaltsMaskBOrbiter") { *pDomainOut = TwistDomain::kSaltsMaskBOrbiter; return true; }
        if (aName == "kSaltsMaskBSeeder") { *pDomainOut = TwistDomain::kSaltsMaskBSeeder; return true; }
        if (aName == "kSaltsWorkLaneWanderer") { *pDomainOut = TwistDomain::kSaltsWorkLaneWanderer; return true; }
        if (aName == "kSaltsWorkLaneOrbiter") { *pDomainOut = TwistDomain::kSaltsWorkLaneOrbiter; return true; }
        if (aName == "kSaltsWorkLaneSeeder") { *pDomainOut = TwistDomain::kSaltsWorkLaneSeeder; return true; }
        if (aName == "kSaltsMaskLaneWanderer") { *pDomainOut = TwistDomain::kSaltsMaskLaneWanderer; return true; }
        if (aName == "kSaltsMaskLaneOrbiter") { *pDomainOut = TwistDomain::kSaltsMaskLaneOrbiter; return true; }
        if (aName == "kSaltsMaskLaneSeeder") { *pDomainOut = TwistDomain::kSaltsMaskLaneSeeder; return true; }
        if (aName == "kSaltsOperationLaneWanderer") { *pDomainOut = TwistDomain::kSaltsOperationLaneWanderer; return true; }
        if (aName == "kSaltsOperationLaneOrbiter") { *pDomainOut = TwistDomain::kSaltsOperationLaneOrbiter; return true; }
        if (aName == "kSaltsOperationLaneSeeder") { *pDomainOut = TwistDomain::kSaltsOperationLaneSeeder; return true; }
        if (aName == "kSBoxesKeyA") { *pDomainOut = TwistDomain::kSBoxesKeyA; return true; }
        if (aName == "kSBoxesKeyB") { *pDomainOut = TwistDomain::kSBoxesKeyB; return true; }
        if (aName == "kSBoxesMaskA") { *pDomainOut = TwistDomain::kSBoxesMaskA; return true; }
        if (aName == "kSBoxesMaskB") { *pDomainOut = TwistDomain::kSBoxesMaskB; return true; }
        if (aName == "kSBoxesWorkLane") { *pDomainOut = TwistDomain::kSBoxesWorkLane; return true; }
        if (aName == "kSBoxesMaskLane") { *pDomainOut = TwistDomain::kSBoxesMaskLane; return true; }
        if (aName == "kSBoxesOperationLane") { *pDomainOut = TwistDomain::kSBoxesOperationLane; return true; }
        return false;
    }

    char *aEnd = nullptr;
    const unsigned long long aParsed = std::strtoull(aToken.c_str(), &aEnd, 0);
    if ((aEnd == nullptr) || (*aEnd != '\0')) {
        return false;
    }
    *pDomainOut = static_cast<TwistDomain>(static_cast<std::uint8_t>(aParsed & 0xFFULL));
    return true;
}

bool ParseDomainConstantToken(const std::string &pToken,
                              const TwistExpander *pExpander,
                              std::uint64_t *pValueOut) {
    if ((pExpander == nullptr) || (pValueOut == nullptr)) {
        return false;
    }

    const std::string aToken = TrimCopy(pToken);
    if (aToken == "mDomainConstantPublicIngress" || aToken == "pDomainConstantPublicIngress") {
        *pValueOut = pExpander->mDomainConstantPublicIngress;
        return true;
    }
    if (aToken == "mDomainConstantPrivateIngress" || aToken == "pDomainConstantPrivateIngress") {
        *pValueOut = pExpander->mDomainConstantPrivateIngress;
        return true;
    }
    if (aToken == "mDomainConstantCrossIngress" || aToken == "pDomainConstantCrossIngress") {
        *pValueOut = pExpander->mDomainConstantCrossIngress;
        return true;
    }

    char *aEnd = nullptr;
    const unsigned long long aParsed = std::strtoull(aToken.c_str(), &aEnd, 0);
    if ((aEnd == nullptr) || (*aEnd != '\0')) {
        return false;
    }
    *pValueOut = static_cast<std::uint64_t>(aParsed);
    return true;
}

bool ExecuteKDFLine(const std::string &pLine,
                    TwistWorkSpace *pWorkspace,
                    TwistExpander *pExpander,
                    std::string *pErrorMessage) {
    std::vector<std::string> aArgs;
    if (!ParseCryptoCallArguments(pLine, "KDF", &aArgs)) {
        return false;
    }

    if ((pWorkspace == nullptr) || (pExpander == nullptr)) {
        SetError(pErrorMessage, "KDF call execution was missing required runtime inputs.");
        return false;
    }

    if (aArgs.size() != 10U) {
        SetError(pErrorMessage, "KDF call expects exactly 10 arguments.");
        return false;
    }

    TwistDomain aDomain = TwistDomain::kInv;
    if (!ParseTwistDomainToken(aArgs[0], &aDomain)) {
        SetError(pErrorMessage, "KDF call domain token was invalid: " + aArgs[0]);
        return false;
    }

    std::uint64_t aDomainPublic = 0ULL;
    std::uint64_t aDomainPrivate = 0ULL;
    std::uint64_t aDomainCross = 0ULL;
    if (!ParseDomainConstantToken(aArgs[1], pExpander, &aDomainPublic)) {
        SetError(pErrorMessage, "KDF public domain constant token was invalid: " + aArgs[1]);
        return false;
    }
    if (!ParseDomainConstantToken(aArgs[2], pExpander, &aDomainPrivate)) {
        SetError(pErrorMessage, "KDF private domain constant token was invalid: " + aArgs[2]);
        return false;
    }
    if (!ParseDomainConstantToken(aArgs[3], pExpander, &aDomainCross)) {
        SetError(pErrorMessage, "KDF cross domain constant token was invalid: " + aArgs[3]);
        return false;
    }

    std::uint64_t *aOutputBuffers[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    for (std::size_t i = 0U; i < 6U; ++i) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveAliasSlot(aArgs[4U + i], &aSlot)) {
            SetError(pErrorMessage, "KDF output alias was invalid: " + aArgs[4U + i]);
            return false;
        }

        std::uint8_t *aBytes = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSlot);
        if (aBytes == nullptr) {
            SetError(pErrorMessage, "KDF output alias resolved to null: " + aArgs[4U + i]);
            return false;
        }
        aOutputBuffers[i] = reinterpret_cast<std::uint64_t *>(aBytes);
    }

    pExpander->KDF(aDomain,
                   aDomainPublic,
                   aDomainPrivate,
                   aDomainCross,
                   aOutputBuffers[0],
                   aOutputBuffers[1],
                   aOutputBuffers[2],
                   aOutputBuffers[3],
                   aOutputBuffers[4],
                   aOutputBuffers[5]);
    return true;
}

bool ApplyBranchStringLine(const std::string &pRawLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           TwistCryptoGenerator *pCryptoGenerator,
                           std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                           std::string *pErrorMessage) {
    if ((pWorkspace == nullptr) || (pVariables == nullptr)) {
        SetError(pErrorMessage, "Branch string-line execution had null inputs.");
        return false;
    }

    std::string aLineError;
    const bool aExecutedCrypto = ExecuteCryptoMakeLine(pRawLine, pWorkspace, pExpander, pCryptoGenerator, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedCrypto) {
        return true;
    }

    const bool aExecutedCryptoSalt = ExecuteCryptoSaltLine(pRawLine, pWorkspace, pExpander, pCryptoGenerator, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedCryptoSalt) {
        return true;
    }

    const bool aExecutedKDF = ExecuteKDFLine(pRawLine, pWorkspace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedKDF) {
        return true;
    }

    std::string aLine = pRawLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimCopy(aLine);
    if (aLine.empty()) {
        return true;
    }

    if (!aLine.empty() && aLine.back() == ';') {
        aLine.pop_back();
        aLine = TrimCopy(aLine);
    }
    if (aLine.empty()) {
        return true;
    }

    const std::size_t aEqual = aLine.find('=');
    if (aEqual == std::string::npos) {
        return true;
    }

    std::string aLeft = TrimCopy(aLine.substr(0U, aEqual));
    std::string aRight = TrimCopy(aLine.substr(aEqual + 1U));
    if (aLeft.empty() || aRight.empty()) {
        return true;
    }

    if ((aLeft.find('*') != std::string::npos) ||
        (aLeft.find('[') != std::string::npos) ||
        (aLeft.find('(') != std::string::npos) ||
        (aLeft.find(')') != std::string::npos)) {
        return true;
    }

    const std::size_t aLastSpace = aLeft.find_last_of(" \t");
    const std::string aName = (aLastSpace == std::string::npos)
        ? aLeft
        : TrimCopy(aLeft.substr(aLastSpace + 1U));
    if (!IsIdentifier(aName)) {
        return true;
    }

    int aValue = 0;
    if (!ParseIntLiteral(aRight, &aValue)) {
        return true;
    }

    (*pVariables)[aName] = static_cast<GRuntimeScalar>(aValue);
    return true;
}

bool ApplyBranchStringLines(const std::vector<std::string> &pLines,
                            TwistWorkSpace *pWorkspace,
                            TwistExpander *pExpander,
                            TwistCryptoGenerator *pCryptoGenerator,
                            std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                            std::string *pErrorMessage) {
    for (const std::string &aRawLine : pLines) {
        if (!ApplyBranchStringLine(aRawLine, pWorkspace, pExpander, pCryptoGenerator, pVariables, pErrorMessage)) {
            return false;
        }
    }
    return true;
}

bool ExecuteBatchJsonByIndex(const TwistProgramBranch &pBranch,
                             std::size_t pBatchIndex,
                             TwistWorkSpace *pWorkspace,
                             TwistExpander *pExpander,
                             std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                             std::string *pErrorMessage) {
    if (pBatchIndex >= pBranch.GetBatchJsonText().size()) {
        SetError(pErrorMessage, "Branch batch step index was out of range during execution.");
        return false;
    }

    GBatch aBatch;
    if (!GBatch::FromJson(pBranch.GetBatchJsonText()[pBatchIndex], &aBatch, pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "Failed to parse branch batch JSON.";
        }
        return false;
    }

    if (!aBatch.ExecuteWithVariables(pWorkspace, pExpander, pVariables, pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "Branch batch execution failed.";
        }
        return false;
    }

    return true;
}

bool ExecuteBranch(const TwistProgramBranch &pBranch,
                   TwistWorkSpace *pWorkspace,
                   TwistExpander *pExpander,
                   TwistCryptoGenerator *pCryptoGenerator,
                   std::string *pErrorMessage) {
    if (pWorkspace == nullptr) {
        SetError(pErrorMessage, "Branch execution received a null workspace.");
        return false;
    }

    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    const std::vector<TwistProgramBranchStep> &aSteps = pBranch.GetSteps();
    if (aSteps.empty()) {
        if (!ApplyBranchStringLines(pBranch.GetStringLines(), pWorkspace, pExpander, pCryptoGenerator, &aVariables, pErrorMessage)) {
            return false;
        }
        return ExecuteBatchJsonText(pBranch.GetBatchJsonText(), pWorkspace, pExpander, &aVariables, pErrorMessage);
    }

    for (const TwistProgramBranchStep &aStep : aSteps) {
        if (aStep.mType == TwistProgramBranchStepType::kLine) {
            if (aStep.mIndex >= pBranch.GetStringLines().size()) {
                SetError(pErrorMessage, "Branch line step index was out of range during execution.");
                return false;
            }
            if (!ApplyBranchStringLine(pBranch.GetStringLines()[aStep.mIndex],
                                       pWorkspace,
                                       pExpander,
                                       pCryptoGenerator,
                                       &aVariables,
                                       pErrorMessage)) {
                return false;
            }
            continue;
        }

        if (aStep.mType == TwistProgramBranchStepType::kBatch) {
            if (!ExecuteBatchJsonByIndex(pBranch,
                                         aStep.mIndex,
                                         pWorkspace,
                                         pExpander,
                                         &aVariables,
                                         pErrorMessage)) {
                return false;
            }
            continue;
        }

        SetError(pErrorMessage, "Branch step type was invalid during execution.");
        return false;
    }

    return true;
}

} // namespace

GTwistExpander::GTwistExpander()
: TwistExpander() {
    mNameBase = "Generated";

    mInitialValue_Carry = static_cast<unsigned char>(Random::Get(256));
    mInitialValue_Value = static_cast<unsigned char>(Random::Get(256));
    mInitialValue_Permute = static_cast<unsigned char>(Random::Get(256));

    SBoxTables::InjectRandomEight(this);
    SaltTables::InjectRandomEight(this);
    RefreshTablePointers();
}

GTwistExpander::~GTwistExpander() {
    
}

void GTwistExpander::RefreshTablePointers() {
    EnsureTableSize(&_mSBoxA, S_SBOX, true);
    EnsureTableSize(&_mSBoxB, S_SBOX, true);
    EnsureTableSize(&_mSBoxC, S_SBOX, true);
    EnsureTableSize(&_mSBoxD, S_SBOX, true);
    EnsureTableSize(&_mSBoxE, S_SBOX, true);
    EnsureTableSize(&_mSBoxF, S_SBOX, true);
    EnsureTableSize(&_mSBoxG, S_SBOX, true);
    EnsureTableSize(&_mSBoxH, S_SBOX, true);

    EnsureTableSize(&_mSaltA, S_SALT, false);
    EnsureTableSize(&_mSaltB, S_SALT, false);
    EnsureTableSize(&_mSaltC, S_SALT, false);
    EnsureTableSize(&_mSaltD, S_SALT, false);
    EnsureTableSize(&_mSaltE, S_SALT, false);
    EnsureTableSize(&_mSaltF, S_SALT, false);
    EnsureTableSize(&_mSaltG, S_SALT, false);
    EnsureTableSize(&_mSaltH, S_SALT, false);

    memcpy(mSBoxA, _mSBoxA.data(), S_SBOX);
    memcpy(mSBoxB, _mSBoxB.data(), S_SBOX);
    memcpy(mSBoxC, _mSBoxC.data(), S_SBOX);
    memcpy(mSBoxD, _mSBoxD.data(), S_SBOX);
    memcpy(mSBoxE, _mSBoxE.data(), S_SBOX);
    memcpy(mSBoxF, _mSBoxF.data(), S_SBOX);
    memcpy(mSBoxG, _mSBoxG.data(), S_SBOX);
    memcpy(mSBoxH, _mSBoxH.data(), S_SBOX);
    
    memcpy(mSaltA, _mSaltA.data(), sizeof(mSaltA));
    memcpy(mSaltB, _mSaltB.data(), sizeof(mSaltB));
    memcpy(mSaltC, _mSaltC.data(), sizeof(mSaltC));
    memcpy(mSaltD, _mSaltD.data(), sizeof(mSaltD));
    memcpy(mSaltE, _mSaltE.data(), sizeof(mSaltE));
    memcpy(mSaltF, _mSaltF.data(), sizeof(mSaltF));
    memcpy(mSaltG, _mSaltG.data(), sizeof(mSaltG));
    memcpy(mSaltH, _mSaltH.data(), sizeof(mSaltH));
    
}

void GTwistExpander::KDF(TwistDomain pDomain,
                         std::uint64_t pDomainConstantPublicIngress,
                         std::uint64_t pDomainConstantPrivateIngress,
                         std::uint64_t pDomainConstantCrossIngress,
                         std::uint64_t *pDomainSaltA,
                         std::uint64_t *pDomainSaltB,
                         std::uint64_t *pDomainSaltC,
                         std::uint64_t *pDomainSaltD,
                         std::uint64_t *pDomainSaltE,
                         std::uint64_t *pDomainSaltF) {
    TwistExpander::KDF(pDomain,
                       pDomainConstantPublicIngress,
                       pDomainConstantPrivateIngress,
                       pDomainConstantCrossIngress,
                       pDomainSaltA,
                       pDomainSaltB,
                       pDomainSaltC,
                       pDomainSaltD,
                       pDomainSaltE,
                       pDomainSaltF);
}

void GTwistExpander::Seed(TwistWorkSpace *pWorkspace,
                          TwistCryptoGenerator *pCryptoGenerator,
                          TwistFarmSBox *pFarmSBox,
                          TwistFarmSalt *pFarmSalt,
                          std::uint8_t *pSource,
                          std::uint8_t *pPassword,
                          unsigned int pPasswordByteLength) {
    RefreshTablePointers();
    TwistExpander::Seed(pWorkspace, pCryptoGenerator, pFarmSBox, pFarmSalt, pSource, pPassword, pPasswordByteLength);

    if ((pWorkspace == nullptr) || (pCryptoGenerator == nullptr) || (pFarmSBox == nullptr) || (pFarmSalt == nullptr)) {
        return;
    }

    std::string aError;
    if (!ExecuteBranch(mKDF, pWorkspace, this, pCryptoGenerator, &aError)) {
        std::printf("fatal: GTwistExpander::Seed KDF failed: %s\n", aError.c_str());
    }

    if (!ExecuteBranch(mSeeder, pWorkspace, this, pCryptoGenerator, &aError)) {
        std::printf("fatal: GTwistExpander::Seed failed: %s\n", aError.c_str());
    }
}

void GTwistExpander::TwistBlock(TwistWorkSpace *pWorkspace,
                                std::uint8_t *pSource,
                                std::uint8_t *pDestination) {
    
}

bool GTwistExpander::LoadJSONProjectRoot(const std::string &pJsonPath,
                                         std::string *pErrorMessage) {
    const std::string aResolvedPath = ResolveInputPath(pJsonPath);
    if (aResolvedPath.empty()) {
        SetError(pErrorMessage, "JSON path was empty.");
        return false;
    }

    std::string aJsonText;
    if (!LoadTextFile(aResolvedPath, &aJsonText, pErrorMessage)) {
        return false;
    }

    auto aRoot = JsonValue::Parse(aJsonText, pErrorMessage);
    if (!aRoot.has_value() || !aRoot->is_object()) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "program JSON root was invalid.";
        }
        return false;
    }

    if (const JsonValue *aNameBase = aRoot->find("name_base"); (aNameBase != nullptr) && aNameBase->is_string()) {
        mNameBase = aNameBase->as_string();
    }

    mKDF.Clear();
    bool aDidParseKDF = ParseBranch(*aRoot, "kdf", &mKDF, pErrorMessage);
    bool aDidParseSeed = ParseBranch(*aRoot, "seed", &mSeeder, pErrorMessage);
    bool aDidParseTwist = ParseBranch(*aRoot, "twist", &mTwister, pErrorMessage);

    if (!aDidParseKDF) {
        (void)ParseBranch(*aRoot, "kdf_branch", &mKDF, pErrorMessage);
    }
    if (!aDidParseSeed) {
        (void)ParseBranch(*aRoot, "seeder", &mSeeder, pErrorMessage);
    }
    if (!aDidParseTwist) {
        (void)ParseBranch(*aRoot, "twister", &mTwister, pErrorMessage);
    }

    if (!ParseTables(*aRoot, this, pErrorMessage)) {
        return false;
    }

    RefreshTablePointers();
    return true;
}
