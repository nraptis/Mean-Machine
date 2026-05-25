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
#include "TwistFarmConstants.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmSalt.hpp"

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
        if (!ParseDomainConstantByteFromObject("matrix_scheme_a", &pDest->mMatrixSchemeA)) { return false; }
        if (!ParseDomainConstantByteFromObject("matrix_scheme_b", &pDest->mMatrixSchemeB)) { return false; }
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

    pExpander->SyncDomainBundleInbuiltFromLegacy();

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

    for (int aValue = 0; aValue <= 255; ++aValue) {
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
        {"pSource", TwistWorkSpaceSlot::kSource},
        {"aSource", TwistWorkSpaceSlot::kSource},
        {"pInput", TwistWorkSpaceSlot::kSource},
        {"pDestination", TwistWorkSpaceSlot::kDest},
        {"aDestination", TwistWorkSpaceSlot::kDest},
        {"pOutput", TwistWorkSpaceSlot::kDest},
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
        {"mSBoxA", TwistWorkSpaceSlot::kParamDomainSBoxA},
        {"mSBoxB", TwistWorkSpaceSlot::kParamDomainSBoxB},
        {"mSBoxC", TwistWorkSpaceSlot::kParamDomainSBoxC},
        {"mSBoxD", TwistWorkSpaceSlot::kParamDomainSBoxD},
        {"mSBoxE", TwistWorkSpaceSlot::kParamDomainSBoxE},
        {"mSBoxF", TwistWorkSpaceSlot::kParamDomainSBoxF},
        {"mSBoxG", TwistWorkSpaceSlot::kParamDomainSBoxG},
        {"mSBoxH", TwistWorkSpaceSlot::kParamDomainSBoxH},
        {"mExpansionLaneA", TwistWorkSpaceSlot::kExpansionLaneA},
        {"mExpansionLaneB", TwistWorkSpaceSlot::kExpansionLaneB},
        {"mExpansionLaneC", TwistWorkSpaceSlot::kExpansionLaneC},
        {"mExpansionLaneD", TwistWorkSpaceSlot::kExpansionLaneD},
        {"mExpansionLaneE", TwistWorkSpaceSlot::kExpansionLaneE},
        {"mExpansionLaneF", TwistWorkSpaceSlot::kExpansionLaneF},
        {"mWorkLaneA", TwistWorkSpaceSlot::kWorkLaneA},
        {"mWorkLaneB", TwistWorkSpaceSlot::kWorkLaneB},
        {"mWorkLaneC", TwistWorkSpaceSlot::kWorkLaneC},
        {"mWorkLaneD", TwistWorkSpaceSlot::kWorkLaneD},
        {"mWorkLaneE", TwistWorkSpaceSlot::kWorkLaneE},
        {"mWorkLaneF", TwistWorkSpaceSlot::kWorkLaneF},
        {"mOperationLaneA", TwistWorkSpaceSlot::kOperationLaneA},
        {"mOperationLaneB", TwistWorkSpaceSlot::kOperationLaneB},
        {"mOperationLaneC", TwistWorkSpaceSlot::kOperationLaneC},
        {"mOperationLaneD", TwistWorkSpaceSlot::kOperationLaneD},
        {"mOperationLaneE", TwistWorkSpaceSlot::kOperationLaneE},
        {"mOperationLaneF", TwistWorkSpaceSlot::kOperationLaneF},
        {"mMaskLaneA", TwistWorkSpaceSlot::kMaskLaneA},
        {"mMaskLaneB", TwistWorkSpaceSlot::kMaskLaneB},
        {"mKeyBoxUnrolledA", TwistWorkSpaceSlot::kKeyBoxUnrolledA},
        {"mKeyBoxUnrolledB", TwistWorkSpaceSlot::kKeyBoxUnrolledB},
        {"mKeyBoxUnrolledC", TwistWorkSpaceSlot::kMaskBoxUnrolledA},
        {"mKeyBoxUnrolledD", TwistWorkSpaceSlot::kMaskBoxUnrolledB},
        {"aKeyBoxUnrolledC", TwistWorkSpaceSlot::kMaskBoxUnrolledA},
        {"aKeyBoxUnrolledD", TwistWorkSpaceSlot::kMaskBoxUnrolledB},
        {"mKeyRowReadA", TwistWorkSpaceSlot::kKeyRowReadA},
        {"mKeyRowReadB", TwistWorkSpaceSlot::kKeyRowReadB},
        {"mKeyRowReadC", TwistWorkSpaceSlot::kMaskRowReadA},
        {"mKeyRowReadD", TwistWorkSpaceSlot::kMaskRowReadB},
        {"aKeyRowReadC", TwistWorkSpaceSlot::kMaskRowReadA},
        {"aKeyRowReadD", TwistWorkSpaceSlot::kMaskRowReadB},
        {"mKeyRowWriteA", TwistWorkSpaceSlot::kKeyRowWriteA},
        {"mKeyRowWriteB", TwistWorkSpaceSlot::kKeyRowWriteB},
        {"mKeyRowWriteC", TwistWorkSpaceSlot::kMaskRowWriteA},
        {"mKeyRowWriteD", TwistWorkSpaceSlot::kMaskRowWriteB},
        {"aKeyRowWriteC", TwistWorkSpaceSlot::kMaskRowWriteA},
        {"aKeyRowWriteD", TwistWorkSpaceSlot::kMaskRowWriteB},
        {"mMaskBoxUnrolledA", TwistWorkSpaceSlot::kMaskBoxUnrolledA},
        {"mMaskBoxUnrolledB", TwistWorkSpaceSlot::kMaskBoxUnrolledB},
        {"mMaskRowReadA", TwistWorkSpaceSlot::kMaskRowReadA},
        {"mMaskRowReadB", TwistWorkSpaceSlot::kMaskRowReadB},
        {"mMaskRowWriteA", TwistWorkSpaceSlot::kMaskRowWriteA},
        {"mMaskRowWriteB", TwistWorkSpaceSlot::kMaskRowWriteB},
        {"mIndexList256A", TwistWorkSpaceSlot::kIndexList256A},
        {"mIndexList256B", TwistWorkSpaceSlot::kIndexList256B},
        {"mIndexList256C", TwistWorkSpaceSlot::kIndexList256C},
        {"mIndexList256D", TwistWorkSpaceSlot::kIndexList256D},
        {"mIndexList256E", TwistWorkSpaceSlot::kIndexList256E},
        {"mIndexList256F", TwistWorkSpaceSlot::kIndexList256F}
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
                                    TwistWorkSpace *pWorkspace,
                                    TwistExpander *pExpander,
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
            SetError(pErrorMessage, "StepA_MakeSBoxes expects 13 arguments.");
        } else if (aMethod == CryptoMethod::kStepB_MakeSalts) {
            SetError(pErrorMessage, "StepB_MakeSalts expects 17 arguments.");
        } else if (aMethod == CryptoMethod::kStepC_MakeSBoxes) {
            SetError(pErrorMessage, "StepC_MakeSBoxes expects 21 arguments.");
        } else {
            SetError(pErrorMessage, "StepD_MakeSalts expects 25 arguments.");
        }
        return false;
    }

    if ((pWorkspace == nullptr) || (pExpander == nullptr)) {
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

        TwistBufferKey aMappedKey;
        std::uint8_t *aBuffer = nullptr;
        if (TwistWorkSpace::TryLegacySlotToBufferKey(aSlot, &aMappedKey)) {
            aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aMappedKey);
        } else {
            aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSlot);
        }
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "Resolved null buffer for alias: " + aAlias);
            return false;
        }
        aBuffers.push_back(aBuffer);
    }

    if (aMethod == CryptoMethod::kStepA_MakeSBoxes) {
        (void)aBuffers;
        return true;
    }

    if (aMethod == CryptoMethod::kStepB_MakeSalts) {
        return true;
    }

    if (aMethod == CryptoMethod::kStepC_MakeSBoxes) {
        return true;
    }

    if (aMethod == CryptoMethod::kStepD_MakeSalts) {
        return true;
    }
    SetError(pErrorMessage, "Unsupported legacy crypto-step call.");
    return false;
}

bool ExecuteCryptoMakeLine(const std::string &pLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           std::string *pErrorMessage) {
    return ExecuteCryptoGeneratorCallLine(pLine, pWorkspace, pExpander, pErrorMessage);
}

bool ExecuteCryptoSaltLine(const std::string &pLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           std::string *pErrorMessage) {
    return ExecuteCryptoGeneratorCallLine(pLine, pWorkspace, pExpander, pErrorMessage);
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
        "pWorkspace->",
        "mWorkspace->",
        "(*pWorkspace).",
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
        "pWorkspace->",
        "mWorkspace->",
        "(*pWorkspace).",
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
                           TwistWorkSpace *pWorkspace,
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
        if ((pWorkspace == nullptr) || (pConstants == nullptr) || (aToken != pName)) {
            return false;
        }
        *pConstantsResolved = pConstants;
        return true;
    };

    if (TryWorkspaceConstants("mDomainBundle.mPhaseAConstants", &pWorkspace->mDomainBundle.mPhaseAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mPhaseBConstants", &pWorkspace->mDomainBundle.mPhaseBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mPhaseCConstants", &pWorkspace->mDomainBundle.mPhaseCConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mKeyAConstants", &pWorkspace->mDomainBundle.mPhaseAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mKeyBConstants", &pWorkspace->mDomainBundle.mPhaseBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mMaskAConstants", &pWorkspace->mDomainBundle.mPhaseAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mMaskBConstants", &pWorkspace->mDomainBundle.mPhaseBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mWorkLaneConstants", &pWorkspace->mDomainBundle.mPhaseAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mMaskLaneConstants", &pWorkspace->mDomainBundle.mPhaseBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mOperationLaneConstants", &pWorkspace->mDomainBundle.mPhaseCConstants)) { return true; }

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
    return false;
}

bool ResolveSaltSetToken(const std::string &pToken,
                         TwistWorkSpace *pWorkspace,
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
        if ((pWorkspace == nullptr) || (pSet == nullptr)) {
            return false;
        }
        if (aToken != pName) {
            return false;
        }
        *pSaltSetResolved = pSet;
        return true;
    };

    if (TryWorkspaceSet("mDomainBundle.mPhaseASalts", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseBSalts", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseCSalts", &pWorkspace->mDomainBundle.mPhaseCSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeyASalts", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeyBSalts", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskASalts", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskBSalts", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mWorkLaneSalts", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskLaneSalts", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mOperationLaneSalts", &pWorkspace->mDomainBundle.mPhaseCSalts)) { return true; }

    // Legacy compatibility tokens.
    if (TryWorkspaceSet("mMatsKeyAOrbiterInit", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyAOrbiter", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyAWanderer", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyBOrbiterInit", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyBOrbiter", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyBWanderer", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskAOrbiterInit", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskAOrbiter", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskAWanderer", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskBOrbiterInit", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskBOrbiter", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskBWanderer", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsWorkLaneOrbiterInit", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsWorkLaneOrbiter", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsWorkLaneWanderer", &pWorkspace->mDomainBundle.mPhaseASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskLaneOrbiterInit", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskLaneOrbiter", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskLaneWanderer", &pWorkspace->mDomainBundle.mPhaseBSalts)) { return true; }
    if (TryWorkspaceSet("mMatsOperationLaneOrbiterInit", &pWorkspace->mDomainBundle.mPhaseCSalts)) { return true; }
    if (TryWorkspaceSet("mMatsOperationLaneOrbiter", &pWorkspace->mDomainBundle.mPhaseCSalts)) { return true; }
    if (TryWorkspaceSet("mMatsOperationLaneWanderer", &pWorkspace->mDomainBundle.mPhaseCSalts)) { return true; }

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
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseASalts", &pExpander->mDomainBundleEphemeral.mPhaseASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseBSalts", &pExpander->mDomainBundleEphemeral.mPhaseBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseCSalts", &pExpander->mDomainBundleEphemeral.mPhaseCSalts)) { return true; }
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

bool ResolveSBoxSetToken(const std::string &pToken,
                         TwistWorkSpace *pWorkspace,
                         TwistExpander *pExpander,
                         TwistDomainSBoxSet **pSBoxSetResolved) {
    if (pSBoxSetResolved == nullptr) {
        return false;
    }

    const std::string aToken = NormalizeRoundMaterialToken(pToken);
    if (aToken.empty()) {
        return false;
    }

    auto TryWorkspaceSet = [&](const std::string &pName,
                               TwistDomainSBoxSet *pSet) -> bool {
        if ((pWorkspace == nullptr) || (pSet == nullptr)) {
            return false;
        }
        if (aToken != pName) {
            return false;
        }
        *pSBoxSetResolved = pSet;
        return true;
    };

    if (TryWorkspaceSet("mDomainBundle.mPhaseASBoxes", &pWorkspace->mDomainBundle.mPhaseASBoxes)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseBSBoxes", &pWorkspace->mDomainBundle.mPhaseBSBoxes)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mPhaseCSBoxes", &pWorkspace->mDomainBundle.mPhaseCSBoxes)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeyASBoxes", &pWorkspace->mDomainBundle.mPhaseASBoxes)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeyBSBoxes", &pWorkspace->mDomainBundle.mPhaseBSBoxes)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskASBoxes", &pWorkspace->mDomainBundle.mPhaseASBoxes)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskBSBoxes", &pWorkspace->mDomainBundle.mPhaseBSBoxes)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mWorkLaneSBoxes", &pWorkspace->mDomainBundle.mPhaseASBoxes)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskLaneSBoxes", &pWorkspace->mDomainBundle.mPhaseBSBoxes)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mOperationLaneSBoxes", &pWorkspace->mDomainBundle.mPhaseCSBoxes)) { return true; }

    if (pExpander != nullptr) {
        auto TryExpanderSet = [&](const std::string &pName,
                                  TwistDomainSBoxSet *pSet) -> bool {
            if (pSet == nullptr) {
                return false;
            }
            if (aToken != pName) {
                return false;
            }
            *pSBoxSetResolved = pSet;
            return true;
        };

        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseASBoxes", &pExpander->mDomainBundleInbuilt.mPhaseASBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseBSBoxes", &pExpander->mDomainBundleInbuilt.mPhaseBSBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mPhaseCSBoxes", &pExpander->mDomainBundleInbuilt.mPhaseCSBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseASBoxes", &pExpander->mDomainBundleEphemeral.mPhaseASBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseBSBoxes", &pExpander->mDomainBundleEphemeral.mPhaseBSBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mPhaseCSBoxes", &pExpander->mDomainBundleEphemeral.mPhaseCSBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mKeyASBoxes", &pExpander->mDomainBundleInbuilt.mPhaseASBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mKeyBSBoxes", &pExpander->mDomainBundleInbuilt.mPhaseBSBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mMaskASBoxes", &pExpander->mDomainBundleInbuilt.mPhaseASBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mMaskBSBoxes", &pExpander->mDomainBundleInbuilt.mPhaseBSBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mWorkLaneSBoxes", &pExpander->mDomainBundleInbuilt.mPhaseASBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mMaskLaneSBoxes", &pExpander->mDomainBundleInbuilt.mPhaseBSBoxes)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mOperationLaneSBoxes", &pExpander->mDomainBundleInbuilt.mPhaseCSBoxes)) { return true; }
    }

    return false;
}

bool ResolveBufferPointerToken(const std::string &pToken,
                               TwistWorkSpace *pWorkspace,
                               TwistExpander *pExpander,
                               std::uint8_t **pBufferResolved) {
    if ((pWorkspace == nullptr) || (pExpander == nullptr) || (pBufferResolved == nullptr)) {
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

    TwistBufferKey aKey;
    if (TwistWorkSpace::TryLegacySlotToBufferKey(aSlot, &aKey)) {
        *pBufferResolved = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aKey);
    } else {
        *pBufferResolved = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, aSlot);
    }
    return *pBufferResolved != nullptr;
}

bool ResolveSeedRoundMaterialToken(const std::string &pToken,
                                   TwistWorkSpace *pWorkspace,
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
    if (!ResolveSaltSetToken(aSetToken, pWorkspace, pExpander, &aSaltSet) || (aSaltSet == nullptr)) {
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
                          TwistWorkSpace *pWorkspace,
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
                                           pWorkspace,
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

bool ResolveSBoxLaneToken(const std::string &pToken,
                          TwistWorkSpace *pWorkspace,
                          TwistExpander *pExpander,
                          std::uint8_t **pSBoxResolved) {
    if (pSBoxResolved == nullptr) {
        return false;
    }

    const std::string aToken = NormalizeRoundMaterialToken(pToken);
    static const char *kSBoxNames[] = {
        ".mSBoxA",
        ".mSBoxB",
        ".mSBoxC",
        ".mSBoxD",
        ".mSBoxE",
        ".mSBoxF",
        ".mSBoxG",
        ".mSBoxH"
    };

    for (int i = 0; i < 8; ++i) {
        const std::string aSuffix(kSBoxNames[i]);
        if ((aToken.size() <= aSuffix.size()) ||
            (aToken.compare(aToken.size() - aSuffix.size(), aSuffix.size(), aSuffix) != 0)) {
            continue;
        }

        TwistDomainSBoxSet *aSBoxSet = nullptr;
        if (!ResolveSBoxSetToken(aToken.substr(0U, aToken.size() - aSuffix.size()),
                                 pWorkspace,
                                 pExpander,
                                 &aSBoxSet) ||
            (aSBoxSet == nullptr)) {
            return false;
        }

        switch (i) {
            case 0: *pSBoxResolved = aSBoxSet->mSBoxA; return true;
            case 1: *pSBoxResolved = aSBoxSet->mSBoxB; return true;
            case 2: *pSBoxResolved = aSBoxSet->mSBoxC; return true;
            case 3: *pSBoxResolved = aSBoxSet->mSBoxD; return true;
            case 4: *pSBoxResolved = aSBoxSet->mSBoxE; return true;
            case 5: *pSBoxResolved = aSBoxSet->mSBoxF; return true;
            case 6: *pSBoxResolved = aSBoxSet->mSBoxG; return true;
            case 7: *pSBoxResolved = aSBoxSet->mSBoxH; return true;
            default: break;
        }
    }

    return false;
}

bool ExecuteKDFBufferAssignmentLine(const std::string &pLine,
                                    TwistWorkSpace *pWorkspace,
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
    if (!ResolveBufferPointerToken(aRight, pWorkspace, pExpander, &aBuffer)) {
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

bool ExecuteFarmSaltLine(const std::string &pLine,
                         TwistWorkSpace *pWorkspace,
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
    if (!ResolveBufferPointerToken(aArgs[0], pWorkspace, pExpander, &aSource)) {
        SetError(pErrorMessage, "pFarmSalt->Derive source alias was invalid: " + aArgs[0]);
        return false;
    }

    std::uint64_t *aSalt[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    for (int i = 0; i < 6; ++i) {
        if (!ResolveSaltLaneToken(aArgs[static_cast<std::size_t>(i + 1)],
                                  pWorkspace,
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

bool ExecuteFarmSBoxLine(const std::string &pLine,
                         TwistWorkSpace *pWorkspace,
                         TwistExpander *pExpander,
                         std::string *pErrorMessage) {
    if (pLine.find("pFarmSBox") == std::string::npos) {
        return false;
    }

    std::vector<std::string> aArgs;
    if (!ParseCryptoCallArguments(pLine, "Derive", &aArgs)) {
        return false;
    }
    if (aArgs.size() != 9U) {
        SetError(pErrorMessage, "pFarmSBox->Derive expects exactly 9 arguments.");
        return false;
    }

    TwistFarmSBox *aFarmSBox = (pExpander != nullptr) ? pExpander->GetFarmSBox() : nullptr;
    if (aFarmSBox == nullptr) {
        SetError(pErrorMessage, "pFarmSBox->Derive execution had no active farm.");
        return false;
    }

    std::uint8_t *aSource = nullptr;
    if (!ResolveBufferPointerToken(aArgs[0], pWorkspace, pExpander, &aSource)) {
        SetError(pErrorMessage, "pFarmSBox->Derive source alias was invalid: " + aArgs[0]);
        return false;
    }

    std::uint8_t *aSBox[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    for (int i = 0; i < 8; ++i) {
        if (!ResolveSBoxLaneToken(aArgs[static_cast<std::size_t>(i + 1)],
                                  pWorkspace,
                                  pExpander,
                                  &aSBox[i])) {
            SetError(pErrorMessage,
                     "pFarmSBox->Derive sbox token was invalid: " + aArgs[static_cast<std::size_t>(i + 1)]);
            return false;
        }
    }

    aFarmSBox->Derive(aSource,
                      aSBox[0],
                      aSBox[1],
                      aSBox[2],
                      aSBox[3],
                      aSBox[4],
                      aSBox[5],
                      aSBox[6],
                      aSBox[7]);
    return true;
}

bool ExecuteFarmConstantsLine(const std::string &pLine,
                              TwistWorkSpace *pWorkspace,
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
    if (!ResolveBufferPointerToken(aArgs[0], pWorkspace, pExpander, &aSource)) {
        SetError(pErrorMessage, "TwistFarmConstants::Derive source alias was invalid: " + aArgs[0]);
        return false;
    }

    TwistDomainConstants *aConstants = nullptr;
    if (!ResolveConstantsToken(aArgs[1], pWorkspace, pExpander, &aConstants)) {
        SetError(pErrorMessage, "TwistFarmConstants::Derive constants token was invalid: " + aArgs[1]);
        return false;
    }

    TwistFarmConstants::Derive(aSource, aConstants);
    return true;
}

bool ExecuteKDFLine(const std::string &pLine,
                    TwistWorkSpace *pWorkspace,
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

    if ((pWorkspace == nullptr) || (pExpander == nullptr)) {
        SetError(pErrorMessage, "KDF call execution was missing required runtime inputs.");
        return false;
    }

    if ((aArgs.size() != 3U) && (aArgs.size() != 4U) &&
        (aArgs.size() != 5U) && (aArgs.size() != 6U)) {
        SetError(pErrorMessage, "KDF call expects exactly 3, 4, 5, or 6 arguments.");
        return false;
    }

    const bool aUsesExplicitBuffers = ((aArgs.size() == 5U) || (aArgs.size() == 6U));
    const bool aHasExplicitNonce = ((aArgs.size() == 4U) || (aArgs.size() == 6U));
    std::uint64_t aNonce = pExpander->GetSessionNonce();
    std::size_t aOffset = 0U;
    if (aHasExplicitNonce) {
        aOffset = 1U;
        const std::string aNonceToken = TrimCopy(aArgs[0]);
        if (aNonceToken == "pNonce") {
            if (pVariables != nullptr) {
                const auto aIterator = pVariables->find("pNonce");
                aNonce = (aIterator == pVariables->end())
                    ? pExpander->GetSessionNonce()
                    : static_cast<std::uint64_t>(aIterator->second);
            } else {
                aNonce = pExpander->GetSessionNonce();
            }
        } else if (aNonceToken == "mKDFSessionNonce") {
            aNonce = pExpander->GetSessionNonce();
        } else if (pVariables != nullptr) {
            const auto aIterator = pVariables->find(aNonceToken);
            if (aIterator != pVariables->end()) {
                aNonce = static_cast<std::uint64_t>(aIterator->second);
            } else {
                char *aEnd = nullptr;
                const unsigned long long aParsed = std::strtoull(aNonceToken.c_str(), &aEnd, 0);
                if ((aEnd == nullptr) || (*aEnd != '\0')) {
                    SetError(pErrorMessage, "KDF nonce token was invalid: " + aArgs[0]);
                    return false;
                }
                aNonce = static_cast<std::uint64_t>(aParsed);
            }
        } else {
            char *aEnd = nullptr;
            const unsigned long long aParsed = std::strtoull(aNonceToken.c_str(), &aEnd, 0);
            if ((aEnd == nullptr) || (*aEnd != '\0')) {
                SetError(pErrorMessage, "KDF nonce token was invalid: " + aArgs[0]);
                return false;
            }
            aNonce = static_cast<std::uint64_t>(aParsed);
        }
    }

    if (aUsesExplicitBuffers) {
        std::uint8_t *aSource = nullptr;
        if (!ResolveBufferPointerToken(aArgs[aOffset + 0U], pWorkspace, pExpander, &aSource)) {
            SetError(pErrorMessage, "KDF source alias resolved to null or unknown: " + aArgs[aOffset + 0U]);
            return false;
        }
        std::uint8_t *aDest = nullptr;
        if (!ResolveBufferPointerToken(aArgs[aOffset + 1U], pWorkspace, pExpander, &aDest)) {
            SetError(pErrorMessage, "KDF destination alias resolved to null or unknown: " + aArgs[aOffset + 1U]);
            return false;
        }
        pExpander->mSource = aSource;
        pExpander->mDest = aDest;
        aOffset += 2U;
    }

    TwistDomainConstants *aConstants = nullptr;
    if (!ResolveConstantsToken(aArgs[aOffset + 0U], pWorkspace, pExpander, &aConstants)) {
        SetError(pErrorMessage, "KDF constants token was invalid: " + aArgs[aOffset + 0U]);
        return false;
    }
    TwistDomainSaltSet *aSaltSet = nullptr;
    if (!ResolveSaltSetToken(aArgs[aOffset + 1U], pWorkspace, pExpander, &aSaltSet)) {
        SetError(pErrorMessage, "KDF salt-set token was invalid: " + aArgs[aOffset + 1U]);
        return false;
    }
    TwistDomainSBoxSet *aSBoxSet = nullptr;
    if (!ResolveSBoxSetToken(aArgs[aOffset + 2U], pWorkspace, pExpander, &aSBoxSet)) {
        SetError(pErrorMessage, "KDF sbox-set token was invalid: " + aArgs[aOffset + 2U]);
        return false;
    }

    if (aFunctionName == "KDF_A") {
        pExpander->KDF_A(aNonce,
                         aConstants,
                         aSaltSet,
                         aSBoxSet);
    } else if (aFunctionName == "KDF_B") {
        pExpander->KDF_B(aNonce,
                         aConstants,
                         aSaltSet,
                         aSBoxSet);
    } else {
        pExpander->KDF(aNonce,
                       aConstants,
                       aSaltSet,
                       aSBoxSet);
    }
    return true;
}

bool ApplyBranchStringLine(const std::string &pRawLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                           std::string *pErrorMessage) {
    if ((pWorkspace == nullptr) || (pVariables == nullptr)) {
        SetError(pErrorMessage, "Branch string-line execution had null inputs.");
        return false;
    }

    std::string aLineError;
    const bool aExecutedCrypto = ExecuteCryptoMakeLine(pRawLine, pWorkspace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedCrypto) {
        return true;
    }

    const bool aExecutedCryptoSalt = ExecuteCryptoSaltLine(pRawLine, pWorkspace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedCryptoSalt) {
        return true;
    }

    const bool aExecutedKDFBufferAssignment = ExecuteKDFBufferAssignmentLine(pRawLine, pWorkspace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedKDFBufferAssignment) {
        return true;
    }

    const bool aExecutedKDF = ExecuteKDFLine(pRawLine, pWorkspace, pExpander, pVariables, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedKDF) {
        return true;
    }

    const bool aExecutedFarmSalt = ExecuteFarmSaltLine(pRawLine, pWorkspace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedFarmSalt) {
        return true;
    }

    const bool aExecutedFarmSBox = ExecuteFarmSBoxLine(pRawLine, pWorkspace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedFarmSBox) {
        return true;
    }

    const bool aExecutedFarmConstants = ExecuteFarmConstantsLine(pRawLine, pWorkspace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedFarmConstants) {
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
                            std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                            std::string *pErrorMessage) {
    for (const std::string &aRawLine : pLines) {
        if (!ApplyBranchStringLine(aRawLine, pWorkspace, pExpander, pVariables, pErrorMessage)) {
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
                   const std::unordered_map<std::string, GRuntimeScalar> *pInitialVariables,
                   std::string *pErrorMessage) {
    if (pWorkspace == nullptr) {
        SetError(pErrorMessage, "Branch execution received a null workspace.");
        return false;
    }

    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    if (pInitialVariables != nullptr) {
        aVariables = *pInitialVariables;
    }
    const std::vector<TwistProgramBranchStep> &aSteps = pBranch.GetSteps();
    if (aSteps.empty()) {
        if (!ApplyBranchStringLines(pBranch.GetStringLines(), pWorkspace, pExpander, &aVariables, pErrorMessage)) {
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

    memcpy(mSBoxA, _mSBoxA.data(), S_SBOX);
    memcpy(mSBoxB, _mSBoxB.data(), S_SBOX);
    memcpy(mSBoxC, _mSBoxC.data(), S_SBOX);
    memcpy(mSBoxD, _mSBoxD.data(), S_SBOX);
    memcpy(mSBoxE, _mSBoxE.data(), S_SBOX);
    memcpy(mSBoxF, _mSBoxF.data(), S_SBOX);
    memcpy(mSBoxG, _mSBoxG.data(), S_SBOX);
    memcpy(mSBoxH, _mSBoxH.data(), S_SBOX);

    SyncDomainBundleInbuiltFromLegacy();
}

void GTwistExpander::KDF(std::uint64_t pNonce,
                         TwistDomainConstants *pDomainConstants,
                         TwistDomainSaltSet *pDomainSaltSet,
                         TwistDomainSBoxSet *pDomainSBoxSet) {
    KDF_A(pNonce,
          pDomainConstants,
          pDomainSaltSet,
          pDomainSBoxSet);
}

void GTwistExpander::KDF_A(std::uint64_t pNonce,
                           TwistDomainConstants *pDomainConstants,
                           TwistDomainSaltSet *pDomainSaltSet,
                           TwistDomainSBoxSet *pDomainSBoxSet) {
    TwistExpander::KDF_A(pNonce,
                         pDomainConstants,
                         pDomainSaltSet,
                         pDomainSBoxSet);

    const TwistProgramBranch &aBranch = mKDF_A.GetSteps().empty() &&
                                        mKDF_A.GetBatchJsonText().empty() &&
                                        mKDF_A.GetStringLines().empty()
        ? mKDF
        : mKDF_A;
    ExecuteKDFBranch(aBranch,
                     "KDF_A",
                     pNonce,
                     pDomainConstants,
                     pDomainSaltSet,
                     pDomainSBoxSet);
}

void GTwistExpander::KDF_B(std::uint64_t pNonce,
                           TwistDomainConstants *pDomainConstants,
                           TwistDomainSaltSet *pDomainSaltSet,
                           TwistDomainSBoxSet *pDomainSBoxSet) {
    TwistExpander::KDF_B(pNonce,
                         pDomainConstants,
                         pDomainSaltSet,
                         pDomainSBoxSet);

    ExecuteKDFBranch(mKDF_B,
                     "KDF_B",
                     pNonce,
                     pDomainConstants,
                     pDomainSaltSet,
                     pDomainSBoxSet);
}

void GTwistExpander::ExecuteKDFBranch(const TwistProgramBranch &pBranch,
                                      const char *pBranchName,
                                      std::uint64_t pNonce,
                                      TwistDomainConstants *pDomainConstants,
                                      TwistDomainSaltSet *pDomainSaltSet,
                                      TwistDomainSBoxSet *pDomainSBoxSet) {
    if ((mWorkspace == nullptr) || (mSource == nullptr) || (mDest == nullptr) ||
        (pDomainConstants == nullptr) ||
        (pDomainSaltSet == nullptr) ||
        (pDomainSBoxSet == nullptr)) {
        return;
    }

    std::string aError;
    std::unordered_map<std::string, GRuntimeScalar> aInitialVariables;
    const char *aNonceNames[8] = {
        "aNonceByteA",
        "aNonceByteB",
        "aNonceByteC",
        "aNonceByteD",
        "aNonceByteE",
        "aNonceByteF",
        "aNonceByteG",
        "aNonceByteH",
    };
    for (int i = 0; i < 8; ++i) {
        aInitialVariables[aNonceNames[i]] = static_cast<GRuntimeScalar>((pNonce >> (i * 8)) & 0xFFULL);
    }
    aInitialVariables["pNonce"] = static_cast<GRuntimeScalar>(pNonce);
    aInitialVariables["aDomainWordIngress"] = static_cast<GRuntimeScalar>(pDomainConstants->mIngress);
    aInitialVariables["aDomainWordScatter"] = static_cast<GRuntimeScalar>(pDomainConstants->mScatter);
    aInitialVariables["aDomainWordCross"] = static_cast<GRuntimeScalar>(pDomainConstants->mCross);
    aInitialVariables["aDomainWordMatrixSelectA"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixSelectA);
    aInitialVariables["aDomainWordMatrixSelectB"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixSelectB);
    aInitialVariables["aDomainWordMatrixUnrollA"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixUnrollA);
    aInitialVariables["aDomainWordMatrixUnrollB"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixUnrollB);
    aInitialVariables["aDomainWordMatrixSchemeA"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixSchemeA);
    aInitialVariables["aDomainWordMatrixSchemeB"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixSchemeB);
    aInitialVariables["aDomainWordMatrixArgA"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixArgA);
    aInitialVariables["aDomainWordMatrixArgB"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixArgB);
    aInitialVariables["aDomainWordMatrixArgC"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixArgC);
    aInitialVariables["aDomainWordMatrixArgD"] = static_cast<GRuntimeScalar>(pDomainConstants->mMatrixArgD);

    if (!ExecuteBranch(pBranch, mWorkspace, this, &aInitialVariables, &aError)) {
        std::printf("fatal: GTwistExpander::%s failed: %s\n", pBranchName, aError.c_str());
    }
}

void GTwistExpander::Seed(TwistWorkSpace *pWorkspace,
                          TwistFarmSBox *pFarmSBox,
                          TwistFarmSalt *pFarmSalt,
                          std::uint64_t pNonce,
                          std::uint8_t *pSource,
                          std::uint8_t *pPassword,
                          unsigned int pPasswordByteLength) {
    RefreshTablePointers();
    TwistExpander::Seed(pWorkspace,
                        pFarmSBox,
                        pFarmSalt,
                        pNonce,
                        pSource,
                        pPassword,
                        pPasswordByteLength);

    if ((pWorkspace == nullptr) || (pFarmSBox == nullptr) ||
        (pFarmSalt == nullptr) || (pSource == nullptr)) {
        return;
    }

    std::string aError;
    std::unordered_map<std::string, GRuntimeScalar> aInitialVariables;
    aInitialVariables["pNonce"] = static_cast<GRuntimeScalar>(pNonce);
    if (!ExecuteBranch(mSeed, pWorkspace, this, &aInitialVariables, &aError)) {
        std::printf("fatal: GTwistExpander::Seed failed: %s\n", aError.c_str());
    }
}

void GTwistExpander::TwistBlock(TwistWorkSpace *pWorkspace,
                                std::uint64_t pNonce,
                                std::uint8_t *pSource,
                                std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkspace, pNonce, pSource, pDestination);
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

    mKDF_A.Clear();
    mKDF_B.Clear();
    mKDF.Clear();
    const bool aParsedKDF_A = ParseBranch(*aRoot, "kdf_a", &mKDF_A, pErrorMessage);
    (void)ParseBranch(*aRoot, "kdf_b", &mKDF_B, pErrorMessage);
    if (!aParsedKDF_A) {
        (void)ParseBranch(*aRoot, "kdf", &mKDF_A, pErrorMessage);
        mKDF = mKDF_A;
    } else {
        mKDF = mKDF_A;
    }
    (void)ParseBranch(*aRoot, "seed", &mSeed, pErrorMessage);
    (void)ParseBranch(*aRoot, "twist", &mTwister, pErrorMessage);
    
    if (!ParseTables(*aRoot, this, pErrorMessage)) {
        return false;
    }

    RefreshTablePointers();
    return true;
}
