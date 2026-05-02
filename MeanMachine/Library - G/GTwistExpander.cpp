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

void EnsureTableSize(std::vector<std::uint8_t> *pTable,
                     const int pLength,
                     const bool pIdentityFallback) {
    if (pTable == nullptr) {
        return;
    }

    if (pTable->size() > static_cast<std::size_t>(pLength)) {
        pTable->resize(static_cast<std::size_t>(pLength));
    }

    while (pTable->size() < static_cast<std::size_t>(pLength)) {
        std::uint8_t aValue = 0U;
        if (pIdentityFallback) {
            aValue = static_cast<std::uint8_t>(pTable->size() & 0xFFU);
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

    if (!ParseByteArray(aTables->find("salt_a"), &pExpander->_mSaltA, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("salt_b"), &pExpander->_mSaltB, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("salt_c"), &pExpander->_mSaltC, pErrorMessage)) { return false; }
    if (!ParseByteArray(aTables->find("salt_d"), &pExpander->_mSaltD, pErrorMessage)) { return false; }

    return true;
}

bool ExecuteBatchJsonText(const std::vector<std::string> &pBatchJsonText,
                          TwistWorkSpace *pWorkspace,
                          TwistExpander *pExpander,
                          std::unordered_map<std::string, int> *pVariables,
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

    static const TwistWorkSpaceSlot kKnownSlots[] = {
        TwistWorkSpaceSlot::kSource,
        TwistWorkSpaceSlot::kDest,

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

    for (TwistWorkSpaceSlot aSlot : kKnownSlots) {
        if (BufAliasName(aSlot) == pAlias) {
            *pSlotOut = aSlot;
            return true;
        }
    }
    return false;
}

bool ParseCryptoMakeArguments(const std::string &pLine,
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

    const std::size_t aCallPos = aLine.find(".Make(");
    if (aCallPos == std::string::npos) {
        return false;
    }

    const std::size_t aOpen = aCallPos + 6U;
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

bool ExecuteCryptoMakeLine(const std::string &pLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           std::string *pErrorMessage) {
    std::vector<std::string> aArgs;
    if (!ParseCryptoMakeArguments(pLine, &aArgs)) {
        return false;
    }

    if ((aArgs.size() != 5U) && (aArgs.size() != 9U)) {
        SetError(pErrorMessage, "TwistCryptoGenerator::Make expects 5 or 9 arguments.");
        return false;
    }

    std::vector<std::uint8_t *> aBuffers;
    aBuffers.reserve(aArgs.size());
    for (const std::string &aAlias : aArgs) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveAliasSlot(aAlias, &aSlot)) {
            SetError(pErrorMessage, "Unknown buffer alias in TwistCryptoGenerator::Make call: " + aAlias);
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

    TwistCryptoGenerator aGenerator;
    if (aBuffers.size() == 5U) {
        aGenerator.Make(aBuffers[0],
                        aBuffers[1],
                        aBuffers[2],
                        aBuffers[3],
                        aBuffers[4]);
    } else {
        aGenerator.Make(aBuffers[0],
                        aBuffers[1],
                        aBuffers[2],
                        aBuffers[3],
                        aBuffers[4],
                        aBuffers[5],
                        aBuffers[6],
                        aBuffers[7],
                        aBuffers[8]);
    }

    return true;
}

bool ApplyBranchStringLine(const std::string &pRawLine,
                           TwistWorkSpace *pWorkspace,
                           TwistExpander *pExpander,
                           std::unordered_map<std::string, int> *pVariables,
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

    (*pVariables)[aName] = aValue;
    return true;
}

bool ApplyBranchStringLines(const std::vector<std::string> &pLines,
                            TwistWorkSpace *pWorkspace,
                            TwistExpander *pExpander,
                            std::unordered_map<std::string, int> *pVariables,
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
                             std::unordered_map<std::string, int> *pVariables,
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
                   std::string *pErrorMessage) {
    if (pWorkspace == nullptr) {
        SetError(pErrorMessage, "Branch execution received a null workspace.");
        return false;
    }

    std::unordered_map<std::string, int> aVariables;
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

    SBoxTables::InjectRandomFour(this);
    SaltTables::InjectRandomFour(this);
    RefreshTablePointers();
}

GTwistExpander::~GTwistExpander() {
    
}

void GTwistExpander::RefreshTablePointers() {
    EnsureTableSize(&_mSBoxA, S_SBOX, true);
    EnsureTableSize(&_mSBoxB, S_SBOX, true);
    EnsureTableSize(&_mSBoxC, S_SBOX, true);
    EnsureTableSize(&_mSBoxD, S_SBOX, true);

    EnsureTableSize(&_mSaltA, S_SALT, false);
    EnsureTableSize(&_mSaltB, S_SALT, false);
    EnsureTableSize(&_mSaltC, S_SALT, false);
    EnsureTableSize(&_mSaltD, S_SALT, false);

    memcpy(mSBoxA, _mSBoxA.data(), S_SBOX);
    memcpy(mSBoxB, _mSBoxB.data(), S_SBOX);
    memcpy(mSBoxC, _mSBoxC.data(), S_SBOX);
    memcpy(mSBoxD, _mSBoxD.data(), S_SBOX);
    
    memcpy(mSaltA, _mSaltA.data(), S_SALT);
    memcpy(mSaltB, _mSaltB.data(), S_SALT);
    memcpy(mSaltC, _mSaltC.data(), S_SALT);
    memcpy(mSaltD, _mSaltD.data(), S_SALT);
    
}

void GTwistExpander::Seed(TwistWorkSpace *pWorkspace,
                          std::uint8_t *pSource,
                          std::uint8_t *pPassword,
                          unsigned int pPasswordByteLength) {
    RefreshTablePointers();
    TwistExpander::Seed(pWorkspace, pSource, pPassword, pPasswordByteLength);

    if (pWorkspace == nullptr) {
        return;
    }

    std::string aError;
    if (!ExecuteBranch(mSeeder, pWorkspace, this, &aError)) {
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

    bool aDidParseSeed = ParseBranch(*aRoot, "seed", &mSeeder, pErrorMessage);
    bool aDidParseTwist = ParseBranch(*aRoot, "twist", &mTwister, pErrorMessage);

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
