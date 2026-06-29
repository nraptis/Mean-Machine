//
//  GTwistExpander.cpp
//  MeanMachine
//

#include "GTwistExpander.hpp"

#include "FileIO.hpp"
#include "GJson.hpp"
#include "Random.hpp"
#include "SaltTables.hpp"
#include "TwistFarmConstants.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistSnow.hpp"

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

[[maybe_unused]] std::string ResolveInputPath(const std::string &pPath) {
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

[[maybe_unused]] bool LoadTextFile(const std::string &pPath,
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

[[maybe_unused]] bool ParseBranch(const JsonValue &pRoot,
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

    // Legacy seed JSON used separate arrays before branch steps existed. Seed
    // setup batches must run before the KDF call lines.
    if (pBranchName == "seed") {
        for (const GBatch &aBatch : aParsedBatches) {
            pBranch->AddBatch(aBatch);
        }
        for (const std::string &aLine : aParsedLines) {
            pBranch->AddLine(aLine);
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

[[maybe_unused]] bool ParseTables(const JsonValue &pRoot,
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
    const JsonValue *aDomainBundleInbuilt = aTables->find("domain_bundle_inbuilt");

    auto ResolveTableValue = [&](const char *pKey) -> const JsonValue * {
        if (pKey == nullptr) {
            return nullptr;
        }
        if ((aDomainBundleInbuilt != nullptr) && aDomainBundleInbuilt->is_object()) {
            const JsonValue *aValue = aDomainBundleInbuilt->find(pKey);
            if (aValue != nullptr) {
                return aValue;
            }
        }
        return aTables->find(pKey);
    };

    auto ParseSaltWithLegacyFallback = [&](const char *pKey,
                                           std::vector<std::uint64_t> *pSaltOut) -> bool {
        const JsonValue *aSaltValue = ResolveTableValue(pKey);
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

    auto ParseLegacySaltOnly = [&](const char *pKey) -> bool {
        std::vector<std::uint64_t> aDiscardedSalt;
        return ParseSaltWithLegacyFallback(pKey, &aDiscardedSalt);
    };

    if (!ParseLegacySaltOnly("salt_a")) { return false; }
    if (!ParseLegacySaltOnly("salt_b")) { return false; }
    if (!ParseLegacySaltOnly("salt_c")) { return false; }
    if (!ParseLegacySaltOnly("salt_d")) { return false; }
    if (!ParseLegacySaltOnly("salt_e")) { return false; }
    if (!ParseLegacySaltOnly("salt_f")) { return false; }
    if (!ParseLegacySaltOnly("salt_g")) { return false; }
    if (!ParseLegacySaltOnly("salt_h")) { return false; }

    auto ParseMaterialObject = [&](const char *pKey,
                                   TwistDomainSeedRoundMaterial *pDest) -> bool {
        if ((pKey == nullptr) || (pDest == nullptr)) {
            return true;
        }
        const JsonValue *aObject = ResolveTableValue(pKey);
        if (aObject == nullptr) {
            return true;
        }
        if (!aObject->is_object()) {
            SetError(pErrorMessage, "domain material entry was not an object: " + std::string(pKey));
            return false;
        }

        auto ParseLane = [&](const char *pLaneKey, std::uint64_t *pLaneDest) -> bool {
            if ((pLaneKey == nullptr) || (pLaneDest == nullptr)) {
                return true;
            }
            std::vector<std::uint64_t> aWide;
            if (!ParseUInt64Array(aObject->find(pLaneKey), &aWide, pErrorMessage)) {
                return false;
            }
            if (aWide.empty()) {
                std::vector<std::uint8_t> aLegacyBytes;
                if (!ParseByteArray(aObject->find(pLaneKey), &aLegacyBytes, pErrorMessage)) {
                    return false;
                }
                for (std::uint8_t aByte : aLegacyBytes) {
                    aWide.push_back(static_cast<std::uint64_t>(aByte));
                }
            }
            if (aWide.empty()) {
                return true;
            }
            if (aWide.size() < static_cast<std::size_t>(S_SALT)) {
                aWide.resize(static_cast<std::size_t>(S_SALT), 0ULL);
            }
            if (aWide.size() > static_cast<std::size_t>(S_SALT)) {
                aWide.resize(static_cast<std::size_t>(S_SALT));
            }
            std::memcpy(pLaneDest,
                        aWide.data(),
                        sizeof(std::uint64_t) * static_cast<std::size_t>(S_SALT));
            return true;
        };

        if (!ParseLane("salt_a", pDest->mSaltA)) { return false; }
        if (!ParseLane("salt_b", pDest->mSaltB)) { return false; }
        if (!ParseLane("salt_c", pDest->mSaltC)) { return false; }
        if (!ParseLane("salt_d", pDest->mSaltD)) { return false; }
        if (!ParseLane("salt_e", pDest->mSaltE)) { return false; }
        if (!ParseLane("salt_f", pDest->mSaltF)) { return false; }
        return true;
    };

    if (!ParseMaterialObject("mats_phase_a_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseASalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_a_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseASalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_a_seeder", &pExpander->mDomainBundleInbuilt.mPhaseASalts.mOrbiterAssign)) { return false; }
    if (!ParseMaterialObject("mats_phase_b_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseBSalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_b_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseBSalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_b_seeder", &pExpander->mDomainBundleInbuilt.mPhaseBSalts.mOrbiterAssign)) { return false; }
    if (!ParseMaterialObject("mats_phase_c_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseCSalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_c_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseCSalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_c_seeder", &pExpander->mDomainBundleInbuilt.mPhaseCSalts.mOrbiterAssign)) { return false; }
    if (!ParseMaterialObject("mats_phase_d_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseDSalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_d_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseDSalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_d_seeder", &pExpander->mDomainBundleInbuilt.mPhaseDSalts.mOrbiterAssign)) { return false; }
    if (!ParseMaterialObject("mats_phase_e_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseESalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_e_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseESalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_e_seeder", &pExpander->mDomainBundleInbuilt.mPhaseESalts.mOrbiterAssign)) { return false; }
    if (!ParseMaterialObject("mats_phase_f_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseFSalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_f_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseFSalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_f_seeder", &pExpander->mDomainBundleInbuilt.mPhaseFSalts.mOrbiterAssign)) { return false; }
    if (!ParseMaterialObject("mats_phase_g_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseGSalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_g_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseGSalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_g_seeder", &pExpander->mDomainBundleInbuilt.mPhaseGSalts.mOrbiterAssign)) { return false; }
    if (!ParseMaterialObject("mats_phase_h_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseHSalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_h_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseHSalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_phase_h_seeder", &pExpander->mDomainBundleInbuilt.mPhaseHSalts.mOrbiterAssign)) { return false; }

    if (!ParseMaterialObject("mats_key_a_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseASalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_key_a_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseASalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_key_a_seeder", &pExpander->mDomainBundleInbuilt.mPhaseASalts.mOrbiterAssign)) { return false; }
    if (!ParseMaterialObject("mats_key_b_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseBSalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_key_b_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseBSalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_key_b_seeder", &pExpander->mDomainBundleInbuilt.mPhaseBSalts.mOrbiterAssign)) { return false; }
    if (!ParseMaterialObject("mats_operation_lane_wanderer", &pExpander->mDomainBundleInbuilt.mPhaseCSalts.mWandererUpdate)) { return false; }
    if (!ParseMaterialObject("mats_operation_lane_orbiter", &pExpander->mDomainBundleInbuilt.mPhaseCSalts.mOrbiterUpdate)) { return false; }
    if (!ParseMaterialObject("mats_operation_lane_seeder", &pExpander->mDomainBundleInbuilt.mPhaseCSalts.mOrbiterAssign)) { return false; }

    auto ParseDomainConstantOptional = [&](const char *pKey,
                                           std::uint64_t *pDest) -> bool {
        if ((pKey == nullptr) || (pDest == nullptr)) {
            return true;
        }

        const JsonValue *aValue = ResolveTableValue(pKey);
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

    std::uint64_t aDiscardedDomainConstant = 0ULL;
    if (!ParseDomainConstantOptional("domain_constant_public_ingress", &aDiscardedDomainConstant)) { return false; }
    if (!ParseDomainConstantOptional("domain_constant_private_ingress", &aDiscardedDomainConstant)) { return false; }
    if (!ParseDomainConstantOptional("domain_constant_cross_ingress", &aDiscardedDomainConstant)) { return false; }
    
    auto ParseDomainConstantFromObject = [&](const JsonValue *pObject,
                                             const char *pFieldKey,
                                             std::uint64_t *pDest) -> bool {
        if ((pObject == nullptr) || (pFieldKey == nullptr) || (pDest == nullptr)) {
            return true;
        }
        const JsonValue *aField = pObject->find(pFieldKey);
        if (aField == nullptr) {
            return true;
        }
        if (aField->is_number()) {
            const double aNumber = aField->as_number();
            if (aNumber < 0.0) {
                SetError(pErrorMessage, "domain constant field was negative: " + std::string(pFieldKey));
                return false;
            }
            *pDest = static_cast<std::uint64_t>(aNumber);
            return true;
        }
        if (aField->is_string()) {
            const std::string aText = aField->as_string();
            char *aEnd = nullptr;
            const unsigned long long aParsed = std::strtoull(aText.c_str(), &aEnd, 0);
            if ((aEnd == nullptr) || (*aEnd != '\0')) {
                SetError(pErrorMessage, "domain constant field had invalid string value: " + std::string(pFieldKey));
                return false;
            }
            *pDest = static_cast<std::uint64_t>(aParsed);
            return true;
        }
        SetError(pErrorMessage, "domain constant field had invalid type: " + std::string(pFieldKey));
        return false;
    };
    
    auto ParseDomainConstantsObject = [&](const char *pKey,
                                          TwistDomainConstants *pDest) -> bool {
        if ((pKey == nullptr) || (pDest == nullptr)) {
            return true;
        }
        
        const JsonValue *aObject = ResolveTableValue(pKey);
        if (aObject == nullptr) {
            return true;
        }
        if (!aObject->is_object()) {
            SetError(pErrorMessage, "domain constants entry was not an object: " + std::string(pKey));
            return false;
        }
        auto ParseDomainConstantByteFromObject = [&](const char *pFieldKey,
                                                     std::uint8_t *pByteDest) -> bool {
            if ((pFieldKey == nullptr) || (pByteDest == nullptr)) {
                return true;
            }
            std::uint64_t aParsed = static_cast<std::uint64_t>(*pByteDest);
            if (!ParseDomainConstantFromObject(aObject, pFieldKey, &aParsed)) {
                return false;
            }
            if (aParsed > 255ULL) {
                SetError(pErrorMessage, "domain constant byte field was outside [0,255]: " + std::string(pFieldKey));
                return false;
            }
            *pByteDest = static_cast<std::uint8_t>(aParsed);
            return true;
        };

        if (!ParseDomainConstantFromObject(aObject, "ingress", &pDest->mIngress)) { return false; }
        if (!ParseDomainConstantFromObject(aObject, "scatter", &pDest->mScatter)) { return false; }
        if (!ParseDomainConstantFromObject(aObject, "cross", &pDest->mCross)) { return false; }
        if (!ParseDomainConstantFromObject(aObject, "public_ingress", &pDest->mDomainConstantPublicIngress)) { return false; }
        if (!ParseDomainConstantFromObject(aObject, "private_ingress", &pDest->mDomainConstantPrivateIngress)) { return false; }
        if (!ParseDomainConstantFromObject(aObject, "cross_ingress", &pDest->mDomainConstantCrossIngress)) { return false; }
        if (!ParseDomainConstantFromObject(aObject, "matrix_select_a", &pDest->mMatrixSelectA)) { return false; }
        if (!ParseDomainConstantFromObject(aObject, "matrix_select_b", &pDest->mMatrixSelectB)) { return false; }
        if (!ParseDomainConstantByteFromObject("matrix_unroll_a", &pDest->mMatrixUnrollA)) { return false; }
        if (!ParseDomainConstantByteFromObject("matrix_unroll_b", &pDest->mMatrixUnrollB)) { return false; }
        if (!ParseDomainConstantByteFromObject("matrix_arg_aa", &pDest->mMatrixArgA)) { return false; }
        if (!ParseDomainConstantByteFromObject("matrix_arg_ab", &pDest->mMatrixArgB)) { return false; }
        if (!ParseDomainConstantByteFromObject("matrix_arg_ba", &pDest->mMatrixArgC)) { return false; }
        if (!ParseDomainConstantByteFromObject("matrix_arg_bb", &pDest->mMatrixArgD)) { return false; }
        if (!ParseDomainConstantByteFromObject("mask_mutate_a", &pDest->mMaskMutateA)) { return false; }
        if (!ParseDomainConstantByteFromObject("mask_mutate_b", &pDest->mMaskMutateB)) { return false; }
        return true;
    };
    
    if (!ParseDomainConstantsObject("constants_phase_a", &pExpander->mDomainBundleInbuilt.mPhaseAConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_phase_b", &pExpander->mDomainBundleInbuilt.mPhaseBConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_phase_c", &pExpander->mDomainBundleInbuilt.mPhaseCConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_phase_d", &pExpander->mDomainBundleInbuilt.mPhaseDConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_phase_e", &pExpander->mDomainBundleInbuilt.mPhaseEConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_phase_f", &pExpander->mDomainBundleInbuilt.mPhaseFConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_phase_g", &pExpander->mDomainBundleInbuilt.mPhaseGConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_phase_h", &pExpander->mDomainBundleInbuilt.mPhaseHConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_key_a", &pExpander->mDomainBundleInbuilt.mPhaseAConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_key_b", &pExpander->mDomainBundleInbuilt.mPhaseBConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_work_lane", &pExpander->mDomainBundleInbuilt.mPhaseAConstants)) { return false; }
    if (!ParseDomainConstantsObject("constants_operation_lane", &pExpander->mDomainBundleInbuilt.mPhaseCConstants)) { return false; }
    
    auto ParseDomainSaltOptional = [&](const char *pKey,
                                       std::uint64_t *pDest) -> bool {
        if ((pKey == nullptr) || (pDest == nullptr)) {
            return true;
        }

        const JsonValue *aDomainValue = ResolveTableValue(pKey);
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

    std::uint64_t aDiscardedSalt[S_SALT];
    std::memset(aDiscardedSalt, 0, sizeof(aDiscardedSalt));
    if (!ParseDomainSaltOptional("domain_salt_keybox_a", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_b", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_c", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_d", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_e", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_keybox_f", aDiscardedSalt)) { return false; }

    if (!ParseDomainSaltOptional("domain_salt_source_a", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_b", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_c", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_d", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_e", aDiscardedSalt)) { return false; }
    if (!ParseDomainSaltOptional("domain_salt_source_f", aDiscardedSalt)) { return false; }

    return true;
}

bool ExecuteBatchJsonText(const std::vector<std::string> &pBatchJsonText,
                          TwistWorkSpace *pWorkSpace,
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

        if (!aBatch.ExecuteWithVariables(pWorkSpace, pExpander, pVariables, pErrorMessage)) {
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

const TwistDomainConstants *WorkspaceDomainConstantsForMember(TwistWorkSpace *pWorkSpace,
                                                              const std::string &pMemberName) {
    if (pWorkSpace == nullptr) {
        return nullptr;
    }
    if (pMemberName == "mPhaseBConstants") {
        return &pWorkSpace->mDomainBundle.mPhaseBConstants;
    }
    if (pMemberName == "mPhaseCConstants") {
        return &pWorkSpace->mDomainBundle.mPhaseCConstants;
    }
    if (pMemberName == "mPhaseDConstants") {
        return &pWorkSpace->mDomainBundle.mPhaseDConstants;
    }
    if (pMemberName == "mPhaseEConstants") {
        return &pWorkSpace->mDomainBundle.mPhaseEConstants;
    }
    if (pMemberName == "mPhaseFConstants") {
        return &pWorkSpace->mDomainBundle.mPhaseFConstants;
    }
    if (pMemberName == "mPhaseGConstants") {
        return &pWorkSpace->mDomainBundle.mPhaseGConstants;
    }
    if (pMemberName == "mPhaseHConstants") {
        return &pWorkSpace->mDomainBundle.mPhaseHConstants;
    }
    if (pMemberName == "mPhaseAConstants") {
        return &pWorkSpace->mDomainBundle.mPhaseAConstants;
    }
    return nullptr;
}

bool DomainConstantMemberValue(const TwistDomainConstants *pConstants,
                               const std::string &pMemberName,
                               GRuntimeScalar *pValueOut) {
    if ((pConstants == nullptr) || (pValueOut == nullptr)) {
        return false;
    }

    if (pMemberName == "mIngress") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mIngress); return true; }
    if (pMemberName == "mScatter") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mScatter); return true; }
    if (pMemberName == "mCross") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mCross); return true; }
    if (pMemberName == "mMatrixSelectA") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixSelectA); return true; }
    if (pMemberName == "mMatrixSelectB") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixSelectB); return true; }
    if (pMemberName == "mMatrixUnrollA") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixUnrollA); return true; }
    if (pMemberName == "mMatrixUnrollB") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixUnrollB); return true; }
    if (pMemberName == "mMatrixArgA") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixArgA); return true; }
    if (pMemberName == "mMatrixArgB") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixArgB); return true; }
    if (pMemberName == "mMatrixArgC") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixArgC); return true; }
    if (pMemberName == "mMatrixArgD") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixArgD); return true; }
    if (pMemberName == "mMaskMutateA") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMaskMutateA); return true; }
    if (pMemberName == "mMaskMutateB") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMaskMutateB); return true; }

    return false;
}

bool ResolveDomainWordAssignmentValue(const std::string &pRight,
                                      TwistWorkSpace *pWorkSpace,
                                      TwistExpander *pExpander,
                                      const std::unordered_map<std::string, GRuntimeScalar> &pVariables,
                                      GRuntimeScalar *pValueOut) {
    if (pValueOut == nullptr) {
        return false;
    }

    if (IsIdentifier(pRight)) {
        const auto aIterator = pVariables.find(pRight);
        if (aIterator != pVariables.end()) {
            *pValueOut = aIterator->second;
            return true;
        }
        return false;
    }

    const std::string aConstantsPrefix = "pConstants->";
    if (pRight.rfind(aConstantsPrefix, 0U) == 0U) {
        const std::string aMemberName = pRight.substr(aConstantsPrefix.size());
        const TwistDomainConstants *aConstants = (pExpander == nullptr) ? nullptr : pExpander->mActiveConstants;
        return DomainConstantMemberValue(aConstants,
                                         aMemberName,
                                         pValueOut);
    }

    const std::string aWorkspacePrefix = "pWorkSpace->mDomainBundle.";
    if (pRight.rfind(aWorkspacePrefix, 0U) != 0U) {
        return false;
    }

    const std::string aTail = pRight.substr(aWorkspacePrefix.size());
    const std::size_t aDot = aTail.find('.');
    if (aDot == std::string::npos) {
        return false;
    }

    const std::string aConstantsMember = aTail.substr(0U, aDot);
    const std::string aDomainMember = aTail.substr(aDot + 1U);
    const TwistDomainConstants *aConstants = WorkspaceDomainConstantsForMember(pWorkSpace, aConstantsMember);
    return DomainConstantMemberValue(aConstants, aDomainMember, pValueOut);
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

        const std::size_t aMatsPos = aToken.find("mMats");
        if (aMatsPos != std::string::npos) {
            std::string aMatsToken = TrimCopy(aToken.substr(aMatsPos));
            while (!aMatsToken.empty()) {
                const char aLast = aMatsToken.back();
                if ((aLast == ';') || (aLast == ')')) {
                    aMatsToken.pop_back();
                    aMatsToken = TrimCopy(aMatsToken);
                    continue;
                }
                break;
            }
            return aMatsToken;
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
    std::string aKeyToken = aAlias;
    if (aKeyToken.rfind("bufkey:", 0U) == 0U) {
        aKeyToken = aKeyToken.substr(7U);
    }
    TwistBufferKey aParsedKey;
    if (BufferKeyFromToken(aKeyToken, &aParsedKey)) {
        const TwistWorkSpaceSlot aResolvedSlot = ResolveBufferSlot(GSymbol::Buf(aParsedKey));
        if (aResolvedSlot != TwistWorkSpaceSlot::kInvalid) {
            *pSlotOut = aResolvedSlot;
            return true;
        }
    }

    for (int aValue = 0; aValue <= 512; ++aValue) {
        const TwistWorkSpaceSlot aSlot = static_cast<TwistWorkSpaceSlot>(aValue);
        const std::string aSlotAlias = BufAliasName(aSlot);
        if ((aSlotAlias == "aInvalidBuffer") || (aSlotAlias == "invalid")) {
            continue;
        }
        if (aSlotAlias == aAlias) {
            *pSlotOut = aSlot;
            return true;
        }
    }

    struct AliasSlotPair {
        const char *mAlias;
        TwistWorkSpaceSlot mSlot;
    };

    static const AliasSlotPair kWorkspaceFieldAliases[] = {
        {"aSource", TwistWorkSpaceSlot::kSource},
        {"mSource", TwistWorkSpaceSlot::kSource},
        {"pSource", TwistWorkSpaceSlot::kParamSource},
        {"pSourceInput", TwistWorkSpaceSlot::kParamSource},
        {"aDestination", TwistWorkSpaceSlot::kParamDestination},
        {"mDest", TwistWorkSpaceSlot::kParamDestination},
        {"pInput", TwistWorkSpaceSlot::kParamSource},
        {"pDestination", TwistWorkSpaceSlot::kParamDestination},
        {"pOutput", TwistWorkSpaceSlot::kParamDestination},
        {"mSaltA", TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA},
        {"mSaltB", TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB},
        {"mSaltC", TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC},
        {"mSaltD", TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD},
        {"mSaltE", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE},
        {"mSaltF", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF},
        {"mMatsWorkLaneOrbiterInit.mSaltA", TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA},
        {"mMatsWorkLaneOrbiterInit.mSaltB", TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB},
        {"mMatsWorkLaneOrbiterInit.mSaltC", TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC},
        {"mMatsWorkLaneOrbiterInit.mSaltD", TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD},
        {"mMatsWorkLaneOrbiterInit.mSaltE", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE},
        {"mMatsWorkLaneOrbiterInit.mSaltF", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF},
        {"mMatsWorkLaneOrbiter.mSaltE", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE},
        {"mMatsWorkLaneOrbiter.mSaltF", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF},
        {"mExpansionLaneA", TwistWorkSpaceSlot::kExpansionLaneA},
        {"mExpansionLaneB", TwistWorkSpaceSlot::kExpansionLaneB},
        {"mExpansionLaneC", TwistWorkSpaceSlot::kExpansionLaneC},
        {"mExpansionLaneD", TwistWorkSpaceSlot::kExpansionLaneD},
        {"mWorkLaneA", TwistWorkSpaceSlot::kWorkLaneA},
        {"mWorkLaneB", TwistWorkSpaceSlot::kWorkLaneB},
        {"mWorkLaneC", TwistWorkSpaceSlot::kWorkLaneC},
        {"mWorkLaneD", TwistWorkSpaceSlot::kWorkLaneD},
        {"mOperationLaneA", TwistWorkSpaceSlot::kOperationLaneA},
        {"mOperationLaneB", TwistWorkSpaceSlot::kOperationLaneB},
        {"mOperationLaneC", TwistWorkSpaceSlot::kOperationLaneC},
        {"mOperationLaneD", TwistWorkSpaceSlot::kOperationLaneD},
        {"mKeyBoxUnrolledA", TwistWorkSpaceSlot::kKeyBoxUnrolledA},
        {"mKeyBoxUnrolledB", TwistWorkSpaceSlot::kKeyBoxUnrolledB},
        {"mKeyRowReadA", TwistWorkSpaceSlot::kKeyRowReadA},
        {"mKeyRowReadB", TwistWorkSpaceSlot::kKeyRowReadB},
        {"mKeyRowWriteA", TwistWorkSpaceSlot::kKeyRowWriteA},
        {"mKeyRowWriteB", TwistWorkSpaceSlot::kKeyRowWriteB},
        {"mIndexList256A", TwistWorkSpaceSlot::kIndexList256A},
        {"mIndexList256B", TwistWorkSpaceSlot::kIndexList256B},
        {"mIndexList256C", TwistWorkSpaceSlot::kIndexList256C},
        {"mIndexList256D", TwistWorkSpaceSlot::kIndexList256D}
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
    const std::string aCallTokenScope = "::" + pMethodName + "(";
    const std::string aCallTokenPlain = pMethodName + "(";
    std::size_t aCallPos = aLine.find(aCallTokenDot);
    std::size_t aOpen = std::string::npos;
    if (aCallPos != std::string::npos) {
        aOpen = aCallPos + aCallTokenDot.size();
    } else {
        aCallPos = aLine.find(aCallTokenArrow);
        if (aCallPos != std::string::npos) {
            aOpen = aCallPos + aCallTokenArrow.size();
        } else {
            aCallPos = aLine.find(aCallTokenScope);
            if (aCallPos != std::string::npos) {
                aOpen = aCallPos + aCallTokenScope.size();
            } else if (aLine.rfind(aCallTokenPlain, 0U) == 0U) {
                aCallPos = 0U;
                aOpen = aCallTokenPlain.size();
            }
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
                                    TwistWorkSpace *pWorkSpace,
                                    TwistExpander *pExpander,
                                    std::string *pErrorMessage) {
    enum class CryptoMethod : std::uint8_t {
        kStepB_MakeSalts = 1,
        kStepD_MakeSalts = 3
    };

    std::vector<std::string> aArgs;
    CryptoMethod aMethod = CryptoMethod::kStepB_MakeSalts;
    if (ParseCryptoCallArguments(pLine, "StepB_MakeSalts", &aArgs)) {
        aMethod = CryptoMethod::kStepB_MakeSalts;
    } else if (ParseCryptoCallArguments(pLine, "StepD_MakeSalts", &aArgs)) {
        aMethod = CryptoMethod::kStepD_MakeSalts;
    } else {
        return false;
    }

    const bool aValidCount =
        ((aMethod == CryptoMethod::kStepB_MakeSalts) && (aArgs.size() == 17U)) ||
        ((aMethod == CryptoMethod::kStepD_MakeSalts) && (aArgs.size() == 25U));
    if (!aValidCount) {
        if (aMethod == CryptoMethod::kStepB_MakeSalts) {
            SetError(pErrorMessage, "StepB_MakeSalts expects 17 arguments.");
        } else {
            SetError(pErrorMessage, "StepD_MakeSalts expects 25 arguments.");
        }
        return false;
    }

    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        SetError(pErrorMessage, "Legacy crypto-step call execution was missing required runtime inputs.");
        return false;
    }

    std::vector<std::uint8_t *> aBuffers;
    aBuffers.reserve(aArgs.size());
    for (const std::string &aAlias : aArgs) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveAliasSlot(aAlias, &aSlot)) {
            SetError(pErrorMessage, "Unknown buffer alias in legacy crypto-step call: " + aAlias);
            return false;
        }

        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkSpace, pExpander, aSlot);
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "Resolved null buffer for alias: " + aAlias);
            return false;
        }
        aBuffers.push_back(aBuffer);
    }

    if (aMethod == CryptoMethod::kStepB_MakeSalts) {
        return true;
    }

    if (aMethod == CryptoMethod::kStepD_MakeSalts) {
        return true;
    }
    SetError(pErrorMessage, "Unsupported legacy crypto-step call.");
    return false;
}

bool ExecuteCryptoMakeLine(const std::string &pLine,
                           TwistWorkSpace *pWorkSpace,
                           TwistExpander *pExpander,
                           std::string *pErrorMessage) {
    return ExecuteCryptoGeneratorCallLine(pLine, pWorkSpace, pExpander, pErrorMessage);
}

bool ExecuteCryptoSaltLine(const std::string &pLine,
                           TwistWorkSpace *pWorkSpace,
                           TwistExpander *pExpander,
                           std::string *pErrorMessage) {
    return ExecuteCryptoGeneratorCallLine(pLine, pWorkSpace, pExpander, pErrorMessage);
}

std::string NormalizeRoundMaterialToken(const std::string &pToken) {
    std::string aToken = TrimCopy(pToken);
    while (!aToken.empty() && (aToken.front() == '&')) {
        aToken.erase(aToken.begin());
        aToken = TrimCopy(aToken);
    }
    while ((aToken.size() >= 2U) && (aToken.front() == '(') && (aToken.back() == ')')) {
        aToken = TrimCopy(aToken.substr(1U, aToken.size() - 2U));
    }

    const char *kPrefixes[] = {
        "pWorkSpace->",
        "mWorkspace->",
        "(*pWorkSpace).",
        "(*mWorkspace).",
        "this->",
        "pExpander->",
        "(*pExpander)."
    };
    for (const char *aPrefix : kPrefixes) {
        const std::string aPrefixText(aPrefix);
        if (aToken.rfind(aPrefixText, 0U) == 0U) {
            aToken = TrimCopy(aToken.substr(aPrefixText.size()));
            break;
        }
    }
    return aToken;
}

std::string NormalizeConstantsToken(const std::string &pToken) {
    std::string aToken = TrimCopy(pToken);
    while (!aToken.empty() && (aToken.front() == '&')) {
        aToken.erase(aToken.begin());
        aToken = TrimCopy(aToken);
    }
    while ((aToken.size() >= 2U) && (aToken.front() == '(') && (aToken.back() == ')')) {
        aToken = TrimCopy(aToken.substr(1U, aToken.size() - 2U));
    }

    const char *kPrefixes[] = {
        "pWorkSpace->",
        "mWorkspace->",
        "(*pWorkSpace).",
        "(*mWorkspace).",
        "this->",
        "pExpander->",
        "(*pExpander)."
    };
    for (const char *aPrefix : kPrefixes) {
        const std::string aPrefixText(aPrefix);
        if (aToken.rfind(aPrefixText, 0U) == 0U) {
            aToken = TrimCopy(aToken.substr(aPrefixText.size()));
            break;
        }
    }
    return aToken;
}

bool ResolveConstantsToken(const std::string &pToken,
                           TwistWorkSpace *pWorkSpace,
                           TwistExpander *pExpander,
                           TwistDomainConstants **pConstantsResolved) {
    if (pConstantsResolved == nullptr) {
        return false;
    }

    const std::string aToken = NormalizeConstantsToken(pToken);
    if (aToken.empty()) {
        return false;
    }

    auto TryWorkspaceConstants = [&](const std::string &pName,
                                     TwistDomainConstants *pConstants) -> bool {
        if ((pWorkSpace == nullptr) || (pConstants == nullptr) || (aToken != pName)) {
            return false;
        }
        *pConstantsResolved = pConstants;
        return true;
    };

    if (TryWorkspaceConstants("mDomainBundle.mPhaseAConstants", &pWorkSpace->mDomainBundle.mPhaseAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mPhaseBConstants", &pWorkSpace->mDomainBundle.mPhaseBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mPhaseCConstants", &pWorkSpace->mDomainBundle.mPhaseCConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mPhaseDConstants", &pWorkSpace->mDomainBundle.mPhaseDConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mPhaseEConstants", &pWorkSpace->mDomainBundle.mPhaseEConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mPhaseFConstants", &pWorkSpace->mDomainBundle.mPhaseFConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mPhaseGConstants", &pWorkSpace->mDomainBundle.mPhaseGConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mPhaseHConstants", &pWorkSpace->mDomainBundle.mPhaseHConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mKeyAConstants", &pWorkSpace->mDomainBundle.mPhaseAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mKeyBConstants", &pWorkSpace->mDomainBundle.mPhaseBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mMaskAConstants", &pWorkSpace->mDomainBundle.mPhaseAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mMaskBConstants", &pWorkSpace->mDomainBundle.mPhaseBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mWorkLaneConstants", &pWorkSpace->mDomainBundle.mPhaseAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mMaskLaneConstants", &pWorkSpace->mDomainBundle.mPhaseBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mOperationLaneConstants", &pWorkSpace->mDomainBundle.mPhaseCConstants)) { return true; }

    if (pExpander == nullptr) {
        return false;
    }

    if (aToken == "mDomainBundleEphemeral.mPhaseAConstants") {
        *pConstantsResolved = &(pExpander->mDomainBundleEphemeral.mPhaseAConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mPhaseBConstants") {
        *pConstantsResolved = &(pExpander->mDomainBundleEphemeral.mPhaseBConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mPhaseCConstants") {
        *pConstantsResolved = &(pExpander->mDomainBundleEphemeral.mPhaseCConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mPhaseDConstants") {
        *pConstantsResolved = &(pExpander->mDomainBundleEphemeral.mPhaseDConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mPhaseEConstants") {
        *pConstantsResolved = &(pExpander->mDomainBundleEphemeral.mPhaseEConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mPhaseFConstants") {
        *pConstantsResolved = &(pExpander->mDomainBundleEphemeral.mPhaseFConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mPhaseGConstants") {
        *pConstantsResolved = &(pExpander->mDomainBundleEphemeral.mPhaseGConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mPhaseHConstants") {
        *pConstantsResolved = &(pExpander->mDomainBundleEphemeral.mPhaseHConstants);
        return true;
    }

    if ((aToken == "mConstantsPhaseA") ||
        (aToken == "mConstantsKeyA") ||
        (aToken == "mConstantsMaskA") ||
        (aToken == "mConstantsWorkLane") ||
        (aToken == "mDomainBundleInbuilt.mPhaseAConstants") ||
        (aToken == "mDomainBundleInbuilt.mKeyAConstants") ||
        (aToken == "mDomainBundleInbuilt.mMaskAConstants") ||
        (aToken == "mDomainBundleInbuilt.mWorkLaneConstants")) {
        *pConstantsResolved = &(pExpander->mDomainBundleInbuilt.mPhaseAConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseB") ||
        (aToken == "mConstantsKeyB") ||
        (aToken == "mConstantsMaskB") ||
        (aToken == "mConstantsMaskLane") ||
        (aToken == "mDomainBundleInbuilt.mPhaseBConstants") ||
        (aToken == "mDomainBundleInbuilt.mKeyBConstants") ||
        (aToken == "mDomainBundleInbuilt.mMaskBConstants") ||
        (aToken == "mDomainBundleInbuilt.mMaskLaneConstants")) {
        *pConstantsResolved = &(pExpander->mDomainBundleInbuilt.mPhaseBConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseC") ||
        (aToken == "mConstantsOperationLane") ||
        (aToken == "mDomainBundleInbuilt.mPhaseCConstants") ||
        (aToken == "mDomainBundleInbuilt.mOperationLaneConstants")) {
        *pConstantsResolved = &(pExpander->mDomainBundleInbuilt.mPhaseCConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseD") ||
        (aToken == "mDomainBundleInbuilt.mPhaseDConstants")) {
        *pConstantsResolved = &(pExpander->mDomainBundleInbuilt.mPhaseDConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseE") ||
        (aToken == "mDomainBundleInbuilt.mPhaseEConstants")) {
        *pConstantsResolved = &(pExpander->mDomainBundleInbuilt.mPhaseEConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseF") ||
        (aToken == "mDomainBundleInbuilt.mPhaseFConstants")) {
        *pConstantsResolved = &(pExpander->mDomainBundleInbuilt.mPhaseFConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseG") ||
        (aToken == "mDomainBundleInbuilt.mPhaseGConstants")) {
        *pConstantsResolved = &(pExpander->mDomainBundleInbuilt.mPhaseGConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseH") ||
        (aToken == "mDomainBundleInbuilt.mPhaseHConstants")) {
        *pConstantsResolved = &(pExpander->mDomainBundleInbuilt.mPhaseHConstants);
        return true;
    }
    return false;
}

bool ResolveSaltSetToken(const std::string &pToken,
                         TwistWorkSpace *pWorkSpace,
                         TwistExpander *pExpander,
                         TwistDomainSaltSet **pSaltSetResolved) {
    if (pSaltSetResolved == nullptr) {
        return false;
    }

    const std::string aToken = NormalizeRoundMaterialToken(pToken);
    if (aToken.empty()) {
        return false;
    }

    auto TryWorkspaceSet = [&](const std::string &pName,
                               TwistDomainSaltSet *pSet) -> bool {
        if ((pWorkSpace == nullptr) || (pSet == nullptr)) {
            return false;
        }
        if (aToken != pName) {
            return false;
        }
        *pSaltSetResolved = pSet;
        return true;
    };

    if (TryWorkspaceSet("mDomainBundle.mPhaseASalts", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseBSalts", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseCSalts", &pWorkSpace->mDomainBundle.mPhaseCSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseDSalts", &pWorkSpace->mDomainBundle.mPhaseDSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseESalts", &pWorkSpace->mDomainBundle.mPhaseESalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseFSalts", &pWorkSpace->mDomainBundle.mPhaseFSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseGSalts", &pWorkSpace->mDomainBundle.mPhaseGSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseHSalts", &pWorkSpace->mDomainBundle.mPhaseHSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeyASalts", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeyBSalts", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskASalts", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskBSalts", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mWorkLaneSalts", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskLaneSalts", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mOperationLaneSalts", &pWorkSpace->mDomainBundle.mPhaseCSalts)) { return true; }

    // Legacy compatibility tokens.
    if (TryWorkspaceSet("mMatsKeyAOrbiterInit", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyAOrbiter", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyAWanderer", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyBOrbiterInit", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyBOrbiter", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyBWanderer", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskAOrbiterInit", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskAOrbiter", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskAWanderer", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskBOrbiterInit", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskBOrbiter", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskBWanderer", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsWorkLaneOrbiterInit", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsWorkLaneOrbiter", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsWorkLaneWanderer", &pWorkSpace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskLaneOrbiterInit", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskLaneOrbiter", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskLaneWanderer", &pWorkSpace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsOperationLaneOrbiterInit", &pWorkSpace->mDomainBundle.mPhaseCSalts)) { return true; }
    if (TryWorkspaceSet("mMatsOperationLaneOrbiter", &pWorkSpace->mDomainBundle.mPhaseCSalts)) { return true; }
    if (TryWorkspaceSet("mMatsOperationLaneWanderer", &pWorkSpace->mDomainBundle.mPhaseCSalts)) { return true; }

    if (pExpander != nullptr) {
        auto TryExpanderSet = [&](const std::string &pName,
                                  TwistDomainSaltSet *pSet) -> bool {
            if (pSet == nullptr) {
                return false;
            }
            if (aToken != pName) {
                return false;
            }
            *pSaltSetResolved = pSet;
            return true;
        };

        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseASalts", &pExpander->mDomainBundleInbuilt.mPhaseASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseBSalts", &pExpander->mDomainBundleInbuilt.mPhaseBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseCSalts", &pExpander->mDomainBundleInbuilt.mPhaseCSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseDSalts", &pExpander->mDomainBundleInbuilt.mPhaseDSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseESalts", &pExpander->mDomainBundleInbuilt.mPhaseESalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseFSalts", &pExpander->mDomainBundleInbuilt.mPhaseFSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseGSalts", &pExpander->mDomainBundleInbuilt.mPhaseGSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseHSalts", &pExpander->mDomainBundleInbuilt.mPhaseHSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseASalts", &pExpander->mDomainBundleEphemeral.mPhaseASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseBSalts", &pExpander->mDomainBundleEphemeral.mPhaseBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseCSalts", &pExpander->mDomainBundleEphemeral.mPhaseCSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseDSalts", &pExpander->mDomainBundleEphemeral.mPhaseDSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseESalts", &pExpander->mDomainBundleEphemeral.mPhaseESalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseFSalts", &pExpander->mDomainBundleEphemeral.mPhaseFSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseGSalts", &pExpander->mDomainBundleEphemeral.mPhaseGSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseHSalts", &pExpander->mDomainBundleEphemeral.mPhaseHSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mKeyASalts", &pExpander->mDomainBundleInbuilt.mPhaseASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mKeyBSalts", &pExpander->mDomainBundleInbuilt.mPhaseBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mMaskASalts", &pExpander->mDomainBundleInbuilt.mPhaseASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mMaskBSalts", &pExpander->mDomainBundleInbuilt.mPhaseBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mWorkLaneSalts", &pExpander->mDomainBundleInbuilt.mPhaseASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mMaskLaneSalts", &pExpander->mDomainBundleInbuilt.mPhaseBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mOperationLaneSalts", &pExpander->mDomainBundleInbuilt.mPhaseCSalts)) { return true; }
    }

    return false;
}

bool ResolveBufferPointerToken(const std::string &pToken,
                               TwistWorkSpace *pWorkSpace,
                               TwistExpander *pExpander,
                               std::uint8_t **pBufferResolved) {
    if ((pWorkSpace == nullptr) || (pExpander == nullptr) || (pBufferResolved == nullptr)) {
        return false;
    }

    std::string aToken = TrimCopy(pToken);
    if (!aToken.empty() && (aToken.back() == ';')) {
        aToken.pop_back();
        aToken = TrimCopy(aToken);
    }
    while (!aToken.empty() && ((aToken.front() == '&') || (aToken.front() == '*'))) {
        aToken.erase(aToken.begin());
        aToken = TrimCopy(aToken);
    }
    StripOuterParens(&aToken);

    if ((aToken == "mSource") || (aToken == "this->mSource") || (aToken == "pExpander->mSource")) {
        *pBufferResolved = pExpander->mSource;
        return *pBufferResolved != nullptr;
    }
    if ((aToken == "mDest") || (aToken == "this->mDest") || (aToken == "pExpander->mDest")) {
        *pBufferResolved = pExpander->mDest;
        return *pBufferResolved != nullptr;
    }
    TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
    if (!ResolveAliasSlot(aToken, &aSlot)) {
        return false;
    }

    *pBufferResolved = TwistWorkSpace::GetBuffer(pWorkSpace, pExpander, aSlot);
    return *pBufferResolved != nullptr;
}

bool ResolveSeedRoundMaterialToken(const std::string &pToken,
                                   TwistWorkSpace *pWorkSpace,
                                   TwistExpander *pExpander,
                                   TwistDomainSeedRoundMaterial **pMaterialResolved) {
    if (pMaterialResolved == nullptr) {
        return false;
    }

    const std::string aToken = NormalizeRoundMaterialToken(pToken);
    const std::size_t aRoundPos = aToken.rfind('.');
    if (aRoundPos == std::string::npos) {
        return false;
    }

    const std::string aSetToken = aToken.substr(0U, aRoundPos);
    const std::string aRoundToken = aToken.substr(aRoundPos + 1U);
    TwistDomainSaltSet *aSaltSet = nullptr;
    if (!ResolveSaltSetToken(aSetToken, pWorkSpace, pExpander, &aSaltSet) || (aSaltSet == nullptr)) {
        return false;
    }

    if (aRoundToken == "mOrbiterAssign") {
        *pMaterialResolved = &aSaltSet->mOrbiterAssign;
        return true;
    }
    if (aRoundToken == "mOrbiterUpdate") {
        *pMaterialResolved = &aSaltSet->mOrbiterUpdate;
        return true;
    }
    if (aRoundToken == "mWandererUpdate") {
        *pMaterialResolved = &aSaltSet->mWandererUpdate;
        return true;
    }
    return false;
}

bool ResolveSaltLaneToken(const std::string &pToken,
                          TwistWorkSpace *pWorkSpace,
                          TwistExpander *pExpander,
                          std::uint64_t **pSaltResolved) {
    if (pSaltResolved == nullptr) {
        return false;
    }

    const std::string aToken = NormalizeRoundMaterialToken(pToken);
    static const char *kSaltNames[] = {
        ".mSaltA",
        ".mSaltB",
        ".mSaltC",
        ".mSaltD",
        ".mSaltE",
        ".mSaltF"
    };

    for (int i = 0; i < 6; ++i) {
        const std::string aSuffix(kSaltNames[i]);
        if ((aToken.size() <= aSuffix.size()) ||
            (aToken.compare(aToken.size() - aSuffix.size(), aSuffix.size(), aSuffix) != 0)) {
            continue;
        }

        TwistDomainSeedRoundMaterial *aMaterial = nullptr;
        if (!ResolveSeedRoundMaterialToken(aToken.substr(0U, aToken.size() - aSuffix.size()),
                                           pWorkSpace,
                                           pExpander,
                                           &aMaterial) ||
            (aMaterial == nullptr)) {
            return false;
        }

        switch (i) {
            case 0: *pSaltResolved = aMaterial->mSaltA; return true;
            case 1: *pSaltResolved = aMaterial->mSaltB; return true;
            case 2: *pSaltResolved = aMaterial->mSaltC; return true;
            case 3: *pSaltResolved = aMaterial->mSaltD; return true;
            case 4: *pSaltResolved = aMaterial->mSaltE; return true;
            case 5: *pSaltResolved = aMaterial->mSaltF; return true;
            default: break;
        }
    }

    return false;
}

bool ExecuteKDFBufferAssignmentLine(const std::string &pLine,
                                    TwistWorkSpace *pWorkSpace,
                                    TwistExpander *pExpander,
                                    std::string *pErrorMessage) {
    std::string aLine = pLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimCopy(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimCopy(aLine);
    }
    const std::size_t aEqual = aLine.find('=');
    if (aEqual == std::string::npos) {
        return false;
    }

    const std::string aLeft = NormalizeRoundMaterialToken(aLine.substr(0U, aEqual));
    const std::string aRight = TrimCopy(aLine.substr(aEqual + 1U));
    if ((aLeft != "mSource") && (aLeft != "mDest")) {
        return false;
    }

    std::uint8_t *aBuffer = nullptr;
    if (!ResolveBufferPointerToken(aRight, pWorkSpace, pExpander, &aBuffer)) {
        SetError(pErrorMessage, "KDF buffer assignment resolved null or unknown source: " + aRight);
        return false;
    }

    if (aLeft == "mSource") {
        pExpander->mSource = aBuffer;
    } else {
        pExpander->mDest = aBuffer;
    }
    return true;
}

bool ExecuteSnowLine(const std::string &pLine,
                     TwistWorkSpace *pWorkSpace,
                     TwistExpander *pExpander,
                     std::string *pErrorMessage) {
    enum class SnowMethod : std::uint8_t {
        kAES256 = 0,
        kChaCha20 = 1,
        kSha256 = 2,
        kAria256 = 3
    };

    std::vector<std::string> aArgs;
    SnowMethod aMethod = SnowMethod::kAES256;
    if (ParseCryptoCallArguments(pLine, "AES256Counter", &aArgs)) {
        aMethod = SnowMethod::kAES256;
    } else if (ParseCryptoCallArguments(pLine, "ChaCha20Counter", &aArgs)) {
        aMethod = SnowMethod::kChaCha20;
    } else if (ParseCryptoCallArguments(pLine, "Sha256Counter", &aArgs)) {
        aMethod = SnowMethod::kSha256;
    } else if (ParseCryptoCallArguments(pLine, "Aria256Counter", &aArgs)) {
        aMethod = SnowMethod::kAria256;
    } else {
        return false;
    }

    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        SetError(pErrorMessage, "Snow call execution was missing required runtime inputs.");
        return false;
    }
    if (aArgs.size() != 2U) {
        SetError(pErrorMessage, "Snow counter call expects exactly 2 arguments.");
        return false;
    }

    std::uint8_t *aSource = nullptr;
    std::uint8_t *aDest = nullptr;
    if (!ResolveBufferPointerToken(aArgs[0], pWorkSpace, pExpander, &aSource)) {
        SetError(pErrorMessage, "Snow source alias resolved to null or unknown: " + aArgs[0]);
        return false;
    }
    if (!ResolveBufferPointerToken(aArgs[1], pWorkSpace, pExpander, &aDest)) {
        SetError(pErrorMessage, "Snow destination alias resolved to null or unknown: " + aArgs[1]);
        return false;
    }

    switch (aMethod) {
        case SnowMethod::kAES256:
            TwistSnow::AES256Counter(aSource, aDest);
            break;
        case SnowMethod::kChaCha20:
            TwistSnow::ChaCha20Counter(aSource, aDest);
            break;
        case SnowMethod::kSha256:
            TwistSnow::Sha256Counter(aSource, aDest);
            break;
        case SnowMethod::kAria256:
            TwistSnow::Aria256Counter(aSource, aDest);
            break;
        default:
            SetError(pErrorMessage, "Snow call method was unsupported.");
            return false;
    }

    return true;
}

bool ExecuteFarmSaltLine(const std::string &pLine,
                         TwistWorkSpace *pWorkSpace,
                         TwistExpander *pExpander,
                         std::string *pErrorMessage) {
    if (pLine.find("pFarmSalt") == std::string::npos) {
        return false;
    }

    std::vector<std::string> aArgs;
    if (!ParseCryptoCallArguments(pLine, "Derive", &aArgs)) {
        return false;
    }
    if (aArgs.size() != 7U) {
        SetError(pErrorMessage, "pFarmSalt->Derive expects exactly 7 arguments.");
        return false;
    }

    TwistFarmSalt *aFarmSalt = (pExpander != nullptr) ? pExpander->GetFarmSalt() : nullptr;
    if (aFarmSalt == nullptr) {
        SetError(pErrorMessage, "pFarmSalt->Derive execution had no active farm.");
        return false;
    }

    std::uint8_t *aSource = nullptr;
    if (!ResolveBufferPointerToken(aArgs[0], pWorkSpace, pExpander, &aSource)) {
        SetError(pErrorMessage, "pFarmSalt->Derive source alias was invalid: " + aArgs[0]);
        return false;
    }

    std::uint64_t *aSalt[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    for (int i = 0; i < 6; ++i) {
        if (!ResolveSaltLaneToken(aArgs[static_cast<std::size_t>(i + 1)],
                                  pWorkSpace,
                                  pExpander,
                                  &aSalt[i])) {
            SetError(pErrorMessage,
                     "pFarmSalt->Derive salt token was invalid: " + aArgs[static_cast<std::size_t>(i + 1)]);
            return false;
        }
    }

    aFarmSalt->Derive(aSource, aSalt[0], aSalt[1], aSalt[2], aSalt[3], aSalt[4], aSalt[5]);
    return true;
}

bool ExecuteFarmConstantsLine(const std::string &pLine,
                              TwistWorkSpace *pWorkSpace,
                              TwistExpander *pExpander,
                              std::string *pErrorMessage) {
    if (pLine.find("TwistFarmConstants") == std::string::npos) {
        return false;
    }

    std::vector<std::string> aArgs;
    if (!ParseCryptoCallArguments(pLine, "Derive", &aArgs)) {
        return false;
    }
    if (aArgs.size() != 2U) {
        SetError(pErrorMessage, "TwistFarmConstants::Derive expects exactly 2 arguments.");
        return false;
    }

    std::uint8_t *aSource = nullptr;
    if (!ResolveBufferPointerToken(aArgs[0], pWorkSpace, pExpander, &aSource)) {
        SetError(pErrorMessage, "TwistFarmConstants::Derive source alias was invalid: " + aArgs[0]);
        return false;
    }

    TwistDomainConstants *aConstants = nullptr;
    if (!ResolveConstantsToken(aArgs[1], pWorkSpace, pExpander, &aConstants)) {
        SetError(pErrorMessage, "TwistFarmConstants::Derive constants token was invalid: " + aArgs[1]);
        return false;
    }

    TwistFarmConstants::Derive(aSource, aConstants);
    return true;
}

bool ExecuteKDFLine(const std::string &pLine,
                    TwistWorkSpace *pWorkSpace,
                    TwistExpander *pExpander,
                    const std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                    std::string *pErrorMessage) {
    std::vector<std::string> aArgs;
    std::string aFunctionName;
    if (ParseCryptoCallArguments(pLine, "KDF_A", &aArgs)) {
        aFunctionName = "KDF_A";
    } else if (ParseCryptoCallArguments(pLine, "KDF_B", &aArgs)) {
        aFunctionName = "KDF_B";
    } else if (ParseCryptoCallArguments(pLine, "KDF", &aArgs)) {
        aFunctionName = "KDF";
    } else {
        return false;
    }

    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        SetError(pErrorMessage, "KDF call execution was missing required runtime inputs.");
        return false;
    }

    if ((aArgs.size() != 2U) && (aArgs.size() != 3U) &&
        (aArgs.size() != 4U) && (aArgs.size() != 5U)) {
        SetError(pErrorMessage, "KDF call expects exactly 2, 3, 4, or 5 arguments.");
        return false;
    }

    auto ResolveNonceToken = [&](const std::string &pToken,
                                 std::uint64_t *pNonceOut) -> bool {
        if (pNonceOut == nullptr) {
            return false;
        }
        const std::string aNonceToken = TrimCopy(pToken);
        if (aNonceToken == "pNonce") {
            if (pVariables != nullptr) {
                const auto aIterator = pVariables->find("pNonce");
                *pNonceOut = (aIterator == pVariables->end())
                    ? pExpander->GetSessionNonce()
                    : static_cast<std::uint64_t>(aIterator->second);
            } else {
                *pNonceOut = pExpander->GetSessionNonce();
            }
            return true;
        }
        if (aNonceToken == "mKDFSessionNonce") {
            *pNonceOut = pExpander->GetSessionNonce();
            return true;
        }
        if (pVariables != nullptr) {
            const auto aIterator = pVariables->find(aNonceToken);
            if (aIterator != pVariables->end()) {
                *pNonceOut = static_cast<std::uint64_t>(aIterator->second);
                return true;
            }
        }

        char *aEnd = nullptr;
        const unsigned long long aParsed = std::strtoull(aNonceToken.c_str(), &aEnd, 0);
        if ((aEnd == nullptr) || (*aEnd != '\0')) {
            return false;
        }
        *pNonceOut = static_cast<std::uint64_t>(aParsed);
        return true;
    };

    auto ResolveIndexToken = [&](const std::string &pToken,
                                 int *pIndexOut) -> bool {
        if (pIndexOut == nullptr) {
            return false;
        }
        const std::string aIndexToken = TrimCopy(pToken);
        if (pVariables != nullptr) {
            const auto aIterator = pVariables->find(aIndexToken);
            if (aIterator != pVariables->end()) {
                *pIndexOut = static_cast<int>(aIterator->second);
                return true;
            }
        }

        char *aEnd = nullptr;
        const long aParsed = std::strtol(aIndexToken.c_str(), &aEnd, 0);
        if ((aEnd == nullptr) || (*aEnd != '\0')) {
            return false;
        }
        *pIndexOut = static_cast<int>(aParsed);
        return true;
    };

    auto LooksLikeNonceToken = [&](const std::string &pToken) -> bool {
        std::uint64_t aUnused = 0U;
        return ResolveNonceToken(pToken, &aUnused);
    };

    bool aUsesKDF_ASnowArgument = false;
    bool aUsesExplicitBuffers = false;
    bool aHasExplicitNonce = false;
    bool aHasKDFIndex = false;

    if (aFunctionName == "KDF_A") {
        if ((aArgs.size() < 3U) || (aArgs.size() > 5U)) {
            SetError(pErrorMessage, "KDF_A call expects constants, salts, snow, optional nonce, and optional index.");
            return false;
        }
        aUsesKDF_ASnowArgument = true;
        aHasExplicitNonce = (aArgs.size() >= 4U);
        aHasKDFIndex = (aArgs.size() == 5U);
    } else if (aFunctionName == "KDF_B") {
        if ((aArgs.size() < 2U) || (aArgs.size() > 5U)) {
            SetError(pErrorMessage, "KDF_B call expects constants, salts, optional nonce, optional index, or explicit buffers.");
            return false;
        }
        if ((aArgs.size() == 4U) && LooksLikeNonceToken(aArgs[0])) {
            aHasExplicitNonce = true;
            aHasKDFIndex = true;
        } else {
            aUsesExplicitBuffers = (aArgs.size() == 4U) || (aArgs.size() == 5U);
            aHasExplicitNonce = (aArgs.size() == 3U) || (aArgs.size() == 5U);
        }
    } else {
        aUsesExplicitBuffers = (aArgs.size() == 4U) || (aArgs.size() == 5U);
        aHasExplicitNonce = (aArgs.size() == 3U) || (aArgs.size() == 5U);
    }

    std::uint64_t aNonce = pExpander->GetSessionNonce();
    int aIndexKDF = 0;
    std::size_t aOffset = 0U;
    if (aHasExplicitNonce) {
        aOffset = 1U;
        if (!ResolveNonceToken(aArgs[0], &aNonce)) {
            SetError(pErrorMessage, "KDF nonce token was invalid: " + aArgs[0]);
            return false;
        }
    }
    if (aHasKDFIndex && !ResolveIndexToken(aArgs.back(), &aIndexKDF)) {
        SetError(pErrorMessage, "KDF index token was invalid: " + aArgs.back());
        return false;
    }

    if (aUsesExplicitBuffers) {
        std::uint8_t *aSource = nullptr;
        if (!ResolveBufferPointerToken(aArgs[aOffset + 0U], pWorkSpace, pExpander, &aSource)) {
            SetError(pErrorMessage, "KDF source alias resolved to null or unknown: " + aArgs[aOffset + 0U]);
            return false;
        }
        std::uint8_t *aDest = nullptr;
        if (!ResolveBufferPointerToken(aArgs[aOffset + 1U], pWorkSpace, pExpander, &aDest)) {
            SetError(pErrorMessage, "KDF destination alias resolved to null or unknown: " + aArgs[aOffset + 1U]);
            return false;
        }
        pExpander->mSource = aSource;
        pExpander->mDest = aDest;
        aOffset += 2U;
    }

    TwistDomainConstants *aConstants = nullptr;
    if (!ResolveConstantsToken(aArgs[aOffset + 0U], pWorkSpace, pExpander, &aConstants)) {
        SetError(pErrorMessage, "KDF constants token was invalid: " + aArgs[aOffset + 0U]);
        return false;
    }
    TwistDomainSaltSet *aSaltSet = nullptr;
    if (!ResolveSaltSetToken(aArgs[aOffset + 1U], pWorkSpace, pExpander, &aSaltSet)) {
        SetError(pErrorMessage, "KDF salt-set token was invalid: " + aArgs[aOffset + 1U]);
        return false;
    }

    if (aFunctionName == "KDF_A") {
        if (!aUsesKDF_ASnowArgument) {
            SetError(pErrorMessage, "KDF_A call expects a snow argument.");
            return false;
        }
        std::uint8_t *aSnow = nullptr;
        if (!ResolveBufferPointerToken(aArgs[aOffset + 2U], pWorkSpace, pExpander, &aSnow)) {
            SetError(pErrorMessage, "KDF_A snow alias resolved to null or unknown: " + aArgs[aOffset + 2U]);
            return false;
        }
        pExpander->KDF_A(aNonce,
                         aConstants,
                         aSaltSet,
                         aSnow,
                         aIndexKDF);
    } else if (aFunctionName == "KDF_B") {
        pExpander->KDF_B(aNonce,
                         aConstants,
                         aSaltSet,
                         aIndexKDF);
    } else {
        pExpander->KDF(aNonce,
                       aConstants,
                       aSaltSet);
    }
    return true;
}

bool ApplyBranchStringLine(const std::string &pRawLine,
                           TwistWorkSpace *pWorkSpace,
                           TwistExpander *pExpander,
                           std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                           std::string *pErrorMessage) {
    if ((pWorkSpace == nullptr) || (pVariables == nullptr)) {
        SetError(pErrorMessage, "Branch string-line execution had null inputs.");
        return false;
    }

    std::string aLineError;
    const bool aExecutedCrypto = ExecuteCryptoMakeLine(pRawLine, pWorkSpace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedCrypto) {
        return true;
    }

    const bool aExecutedCryptoSalt = ExecuteCryptoSaltLine(pRawLine, pWorkSpace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedCryptoSalt) {
        return true;
    }

    const bool aExecutedKDFBufferAssignment = ExecuteKDFBufferAssignmentLine(pRawLine, pWorkSpace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedKDFBufferAssignment) {
        return true;
    }

    const bool aExecutedSnow = ExecuteSnowLine(pRawLine, pWorkSpace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedSnow) {
        return true;
    }

    const bool aExecutedKDF = ExecuteKDFLine(pRawLine, pWorkSpace, pExpander, pVariables, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedKDF) {
        return true;
    }

    const bool aExecutedFarmSalt = ExecuteFarmSaltLine(pRawLine, pWorkSpace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedFarmSalt) {
        return true;
    }

    const bool aExecutedFarmConstants = ExecuteFarmConstantsLine(pRawLine, pWorkSpace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedFarmConstants) {
        return true;
    }

    std::string aHookLine = pRawLine;
    const std::size_t aHookComment = aHookLine.find("//");
    if (aHookComment != std::string::npos) {
        aHookLine = aHookLine.substr(0U, aHookComment);
    }
    aHookLine = TrimCopy(aHookLine);
    if (!aHookLine.empty() && aHookLine.back() == ';') {
        aHookLine.pop_back();
        aHookLine = TrimCopy(aHookLine);
    }
    if (aHookLine == "SquashInvestToKeyBoxes()") {
        if (pExpander != nullptr) {
            pExpander->SquashInvestToKeyBoxes();
        }
        return true;
    }

    std::string aRuntimeRawLine = pRawLine;
    const std::size_t aRuntimeComment = aRuntimeRawLine.find("//");
    if (aRuntimeComment != std::string::npos) {
        aRuntimeRawLine = aRuntimeRawLine.substr(0U, aRuntimeComment);
    }
    aRuntimeRawLine = TrimCopy(aRuntimeRawLine);
    if (!aRuntimeRawLine.empty() && aRuntimeRawLine.back() == ';') {
        aRuntimeRawLine.pop_back();
        aRuntimeRawLine = TrimCopy(aRuntimeRawLine);
    }
    if ((aRuntimeRawLine.rfind("TwistMemory::", 0U) == 0U) ||
        (aRuntimeRawLine.rfind("TwistSquash::", 0U) == 0U) ||
        (aRuntimeRawLine.rfind("TwistDiffuse::", 0U) == 0U) ||
        (aRuntimeRawLine.rfind("TwistShiftBox::", 0U) == 0U) ||
        (aRuntimeRawLine.rfind("TwistIndexShuffle::", 0U) == 0U) ||
        (aRuntimeRawLine.rfind("mMatrix.", 0U) == 0U)) {
        std::vector<GStatement> aRuntimeStatements;
        aRuntimeStatements.push_back(GStatement::RawLine(pRawLine));
        GBatch aRuntimeBatch;
        aRuntimeBatch.CommitStatements(&aRuntimeStatements);
        if (!aRuntimeBatch.ExecuteWithVariables(pWorkSpace, pExpander, pVariables, &aLineError)) {
            if (!aLineError.empty()) {
                SetError(pErrorMessage, aLineError);
            }
            return false;
        }
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

    GRuntimeScalar aDomainAssignmentValue = 0ULL;
    if (ResolveDomainWordAssignmentValue(aRight,
                                         pWorkSpace,
                                         pExpander,
                                         *pVariables,
                                         &aDomainAssignmentValue)) {
        (*pVariables)[aName] = aDomainAssignmentValue;
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
                            TwistWorkSpace *pWorkSpace,
                            TwistExpander *pExpander,
                            std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                            std::string *pErrorMessage) {
    for (const std::string &aRawLine : pLines) {
        if (!ApplyBranchStringLine(aRawLine, pWorkSpace, pExpander, pVariables, pErrorMessage)) {
            return false;
        }
    }
    return true;
}

bool ExecuteBatchJsonByIndex(const TwistProgramBranch &pBranch,
                             std::size_t pBatchIndex,
                             TwistWorkSpace *pWorkSpace,
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

    if (!aBatch.ExecuteWithVariables(pWorkSpace, pExpander, pVariables, pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "Branch batch execution failed.";
        }
        return false;
    }

    return true;
}

[[maybe_unused]] bool ExecuteBranch(const TwistProgramBranch &pBranch,
                                    TwistWorkSpace *pWorkSpace,
                                    TwistExpander *pExpander,
                                    const std::unordered_map<std::string, GRuntimeScalar> *pInitialVariables,
                                    std::string *pErrorMessage) {
    if (pWorkSpace == nullptr) {
        SetError(pErrorMessage, "Branch execution received a null workspace.");
        return false;
    }

    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    if (pInitialVariables != nullptr) {
        aVariables = *pInitialVariables;
    }
    const std::vector<TwistProgramBranchStep> &aSteps = pBranch.GetSteps();
    if (aSteps.empty()) {
        if (!ApplyBranchStringLines(pBranch.GetStringLines(), pWorkSpace, pExpander, &aVariables, pErrorMessage)) {
            return false;
        }
        return ExecuteBatchJsonText(pBranch.GetBatchJsonText(), pWorkSpace, pExpander, &aVariables, pErrorMessage);
    }

    for (const TwistProgramBranchStep &aStep : aSteps) {
        if (aStep.mType == TwistProgramBranchStepType::kLine) {
            if (aStep.mIndex >= pBranch.GetStringLines().size()) {
                SetError(pErrorMessage, "Branch line step index was out of range during execution.");
                return false;
            }
            if (!ApplyBranchStringLine(pBranch.GetStringLines()[aStep.mIndex],
                                       pWorkSpace,
                                       pExpander,
                                       &aVariables,
                                       pErrorMessage)) {
                return false;
            }
            continue;
        }

        if (aStep.mType == TwistProgramBranchStepType::kBatch) {
            if (!ExecuteBatchJsonByIndex(pBranch,
                                         aStep.mIndex,
                                         pWorkSpace,
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

    SaltTables::InjectRandomEight(this);
    RefreshTablePointers();
}

GTwistExpander::~GTwistExpander() {
    
}

void GTwistExpander::RefreshTablePointers() {
}

void GTwistExpander::KDF(std::uint64_t pNonce,
                         TwistDomainConstants *pDomainConstants,
                         TwistDomainSaltSet *pDomainSaltSet) {
    TwistExpander::KDF(pNonce,
                       pDomainConstants,
                       pDomainSaltSet);
}

void GTwistExpander::KDF_A(std::uint64_t pNonce,
                           TwistDomainConstants *pDomainConstants,
                           TwistDomainSaltSet *pDomainSaltSet,
                           std::uint8_t *pSnow,
                           int pIndexKDF) {
    TwistExpander::KDF_A(pNonce,
                         pDomainConstants,
                         pDomainSaltSet,
                         pSnow,
                         pIndexKDF);
}

void GTwistExpander::KDF_B(std::uint64_t pNonce,
                           TwistDomainConstants *pDomainConstants,
                           TwistDomainSaltSet *pDomainSaltSet,
                           int pIndexKDF) {
    TwistExpander::KDF_B(pNonce,
                         pDomainConstants,
                         pDomainSaltSet,
                         pIndexKDF);
}

void GTwistExpander::Seed(TwistWorkSpace *pWorkSpace,
                          TwistFarmSalt *pFarmSalt,
                          std::uint64_t pNonce,
                          std::uint8_t *pPassword,
                          unsigned int pPasswordByteLength,
                          std::uint8_t *pDestination) {
    RefreshTablePointers();
    TwistExpander::Seed(pWorkSpace,
                        pFarmSalt,
                        pNonce,
                        pPassword,
                        pPasswordByteLength,
                        pDestination);

}

void GTwistExpander::TwistBlock(TwistWorkSpace *pWorkSpace,
                                std::uint64_t pNonce,
                                std::uint8_t *pSource,
                                std::size_t pBlockIndex,
                                std::size_t pBlockCount,
                                std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace,
                              pNonce,
                              pSource,
                              pBlockIndex,
                              pBlockCount,
                              pDestination);
}

void GTwistExpander::SquashInvestToKeyBoxes() {
    TwistExpander::SquashInvestToKeyBoxes();
}

void GTwistExpander::GrowKeyA(TwistWorkSpace *pWorkSpace) {
    TwistExpander::GrowKeyA(pWorkSpace);
}

void GTwistExpander::GrowKeyB(TwistWorkSpace *pWorkSpace) {
    TwistExpander::GrowKeyB(pWorkSpace);
}

bool GTwistExpander::LoadJSONProjectRoot(const std::string &pJsonPath,
                                         std::string *pErrorMessage) {
    (void)pJsonPath;
    SetError(pErrorMessage, "GTwistExpander JSON loading has been removed; export and use generated C++ instead.");
    return false;
#if 0
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

    mKDF_A.Clear();
    mKDF_B.Clear();
    mSeed.Clear();
    mTwister.Clear();
    mGrowKeyA.Clear();
    mGrowKeyB.Clear();
    (void)ParseBranch(*aRoot, "kdf_a", &mKDF_A, pErrorMessage);
    (void)ParseBranch(*aRoot, "kdf_b", &mKDF_B, pErrorMessage);
    (void)ParseBranch(*aRoot, "seed", &mSeed, pErrorMessage);
    (void)ParseBranch(*aRoot, "twist", &mTwister, pErrorMessage);
    (void)ParseBranch(*aRoot, "grow_key_a", &mGrowKeyA, pErrorMessage);
    (void)ParseBranch(*aRoot, "grow_key_b", &mGrowKeyB, pErrorMessage);
    
    if (!ParseTables(*aRoot, this, pErrorMessage)) {
        return false;
    }

    RefreshTablePointers();
    return true;
#endif
}
