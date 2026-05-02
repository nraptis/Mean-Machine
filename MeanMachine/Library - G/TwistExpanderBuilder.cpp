//
//  TwistExpanderBuilder.cpp
//  MeanMachine
//

#include "GTwistExpander.hpp"

#include "FileIO.hpp"
#include "GJson.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

using MeanMachine_json::JsonValue;

namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

bool SaveTextFile(const std::string &pPath,
                  const std::string &pText,
                  std::string *pErrorMessage) {
    const std::vector<std::uint8_t> aData(pText.begin(), pText.end());
    if (!FileIO::Save(pPath, aData)) {
        SetError(pErrorMessage, "Failed to save file: " + pPath);
        return false;
    }
    return true;
}

std::string SanitizeIdentifier(const std::string &pText,
                               const std::string &pFallback) {
    std::string aResult;
    aResult.reserve(pText.size());

    for (const char aChar : pText) {
        if (std::isalnum(static_cast<unsigned char>(aChar)) != 0) {
            aResult.push_back(aChar);
        } else {
            aResult.push_back('_');
        }
    }

    while (!aResult.empty() && aResult.front() == '_') {
        aResult.erase(aResult.begin());
    }

    if (aResult.empty()) {
        aResult = pFallback;
    }

    if (!aResult.empty() && std::isdigit(static_cast<unsigned char>(aResult.front())) != 0) {
        aResult.insert(aResult.begin(), '_');
    }

    return aResult;
}

bool HasJsonExtension(const std::string &pPath) {
    std::string aExtension = std::filesystem::path(pPath).extension().string();
    std::transform(aExtension.begin(), aExtension.end(), aExtension.begin(),
                   [](const unsigned char pChar) {
                       return static_cast<char>(std::tolower(pChar));
                   });
    return aExtension == ".json";
}

std::string ResolveOutputPathFromProjectRoot(const std::string &pPath) {
    if (pPath.empty()) {
        return FileIO::ProjectRoot();
    }

    const std::filesystem::path aInputPath(pPath);
    if (aInputPath.is_absolute()) {
        return aInputPath.lexically_normal().generic_string();
    }

    const std::filesystem::path aProjectRoot(FileIO::ProjectRoot());
    return (aProjectRoot / aInputPath).lexically_normal().generic_string();
}

std::string ResolveJsonOutputPath(const std::string &pRootPath,
                                  const std::string &pNameBase) {
    if (HasJsonExtension(pRootPath)) {
        return ResolveOutputPathFromProjectRoot(pRootPath);
    }

    const std::string aFileName = pNameBase + ".json";
    return ResolveOutputPathFromProjectRoot(FileIO::Join(pRootPath, aFileName));
}

template <typename T>
void AppendUniqueValue(std::vector<T> *pList,
                       const T &pValue) {
    if (pList == nullptr) {
        return;
    }
    for (const T &aValue : *pList) {
        if (aValue == pValue) {
            return;
        }
    }
    pList->push_back(pValue);
}

bool ContainsText(const std::vector<std::string> &pList,
                  const std::string &pValue) {
    for (const std::string &aValue : pList) {
        if (aValue == pValue) {
            return true;
        }
    }
    return false;
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

bool IsKeyScalarName(const std::string &pName) {
    return pName.find("Key") != std::string::npos;
}

bool IsWideStateScalarName(const std::string &pName) {
    if (pName.find("Nibble") != std::string::npos) {
        return false;
    }
    return StartsWithText(pName, "aValue") ||
           StartsWithText(pName, "aState") ||
           StartsWithText(pName, "aCarry") ||
           StartsWithText(pName, "aPermute") ||
           StartsWithText(pName, "aHoldPermute");
}

std::string ScalarCppTypeForName(const std::string &pName) {
    if (StartsWithText(pName, "aOracle")) {
        return "std::uint64_t";
    }
    if (IsKeyScalarName(pName)) {
        return "std::size_t";
    }
    if (IsWideStateScalarName(pName)) {
        return "std::uint64_t";
    }
    return "std::uint8_t";
}

std::string TrimText(const std::string &pText) {
    if (pText.empty()) {
        return "";
    }

    std::size_t aBegin = 0U;
    while ((aBegin < pText.size()) && std::isspace(static_cast<unsigned char>(pText[aBegin])) != 0) {
        ++aBegin;
    }

    std::size_t aEnd = pText.size();
    while ((aEnd > aBegin) && std::isspace(static_cast<unsigned char>(pText[aEnd - 1U])) != 0) {
        --aEnd;
    }

    return pText.substr(aBegin, aEnd - aBegin);
}

std::string DeclaredIdentifierFromLine(const std::string &pLine) {
    std::string aText = TrimText(pLine);
    if (aText.empty()) {
        return "";
    }
    if (aText.back() == ';') {
        aText.pop_back();
    }

    const std::size_t aEquals = aText.find('=');
    if (aEquals == std::string::npos) {
        return "";
    }

    const std::string aLeft = TrimText(aText.substr(0U, aEquals));
    if (aLeft.empty()) {
        return "";
    }
    if ((aLeft.find(' ') == std::string::npos) && (aLeft.find('\t') == std::string::npos)) {
        return "";
    }
    if ((aLeft.find('(') != std::string::npos) || (aLeft.find(')') != std::string::npos)) {
        return "";
    }

    std::size_t aEnd = aLeft.size();
    while ((aEnd > 0U) && std::isspace(static_cast<unsigned char>(aLeft[aEnd - 1U])) != 0) {
        --aEnd;
    }

    std::size_t aStart = aEnd;
    while ((aStart > 0U) &&
           ((std::isalnum(static_cast<unsigned char>(aLeft[aStart - 1U])) != 0) ||
            (aLeft[aStart - 1U] == '_'))) {
        --aStart;
    }

    if (aStart == aEnd) {
        return "";
    }
    return aLeft.substr(aStart, aEnd - aStart);
}

std::string NormalizeLegacyByteTypeLine(const std::string &pLine) {
    std::string aLine = pLine;

    auto ReplaceAll = [&aLine](const std::string &pFrom, const std::string &pTo) {
        std::size_t aPos = 0U;
        while ((aPos = aLine.find(pFrom, aPos)) != std::string::npos) {
            aLine.replace(aPos, pFrom.size(), pTo);
            aPos += pTo.size();
        }
    };

    ReplaceAll("unsigned char *", "std::uint8_t *");
    ReplaceAll("unsigned char*", "std::uint8_t*");
    ReplaceAll("unsigned char ", "std::uint8_t ");

    const std::size_t aEquals = aLine.find('=');
    if (aEquals == std::string::npos) {
        return aLine;
    }

    const std::string aName = DeclaredIdentifierFromLine(aLine);
    if (aName.empty()) {
        return aLine;
    }

    const std::string aDesiredType = ScalarCppTypeForName(aName);
    if (aDesiredType == "std::uint8_t") {
        return aLine;
    }

    std::size_t aTypePos = aLine.find("std::uint8_t ");
    if (aTypePos != std::string::npos) {
        const std::size_t aStarPos = aLine.find('*', aTypePos);
        if ((aStarPos == std::string::npos) || (aStarPos > aEquals)) {
            aLine.replace(aTypePos, std::string("std::uint8_t").size(), aDesiredType);
        }
    }

    return aLine;
}

std::vector<TwistWorkSpaceSlot> FixedWorkspaceSlotOrder() {
    return {
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
}

std::string WorkspaceAliasDeclaration(const TwistWorkSpaceSlot pSlot) {
    const std::string aAlias = BufAliasName(pSlot);
    const std::string aPrefix = "[[maybe_unused]] std::uint8_t *" + aAlias + " = ";
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource:
            return "std::uint8_t *" + aAlias + " = pSource;";
        case TwistWorkSpaceSlot::kDest:
            return "std::uint8_t *" + aAlias + " = pDestination;";

        case TwistWorkSpaceSlot::kSaltA: return "";
        case TwistWorkSpaceSlot::kSaltB: return "";
        case TwistWorkSpaceSlot::kSaltC: return "";
        case TwistWorkSpaceSlot::kSaltD: return "";
        case TwistWorkSpaceSlot::kDerivedSaltA: return aPrefix + "pWorkspace->mDerivedSaltA;";
        case TwistWorkSpaceSlot::kDerivedSaltB: return aPrefix + "pWorkspace->mDerivedSaltB;";
        case TwistWorkSpaceSlot::kDerivedSaltC: return aPrefix + "pWorkspace->mDerivedSaltC;";
        case TwistWorkSpaceSlot::kDerivedSaltD: return aPrefix + "pWorkspace->mDerivedSaltD;";
        case TwistWorkSpaceSlot::kDerivedSaltE: return aPrefix + "pWorkspace->mDerivedSaltE;";
        case TwistWorkSpaceSlot::kDerivedSaltF: return aPrefix + "pWorkspace->mDerivedSaltF;";
        case TwistWorkSpaceSlot::kDerivedSaltG: return aPrefix + "pWorkspace->mDerivedSaltG;";
        case TwistWorkSpaceSlot::kDerivedSaltH: return aPrefix + "pWorkspace->mDerivedSaltH;";

        case TwistWorkSpaceSlot::kSBoxA: return "";
        case TwistWorkSpaceSlot::kSBoxB: return "";
        case TwistWorkSpaceSlot::kSBoxC: return "";
        case TwistWorkSpaceSlot::kSBoxD: return "";
        case TwistWorkSpaceSlot::kDerivedSBoxA: return aPrefix + "pWorkspace->mDerivedSBoxA;";
        case TwistWorkSpaceSlot::kDerivedSBoxB: return aPrefix + "pWorkspace->mDerivedSBoxB;";
        case TwistWorkSpaceSlot::kDerivedSBoxC: return aPrefix + "pWorkspace->mDerivedSBoxC;";
        case TwistWorkSpaceSlot::kDerivedSBoxD: return aPrefix + "pWorkspace->mDerivedSBoxD;";
        case TwistWorkSpaceSlot::kDerivedSBoxE: return aPrefix + "pWorkspace->mDerivedSBoxE;";
        case TwistWorkSpaceSlot::kDerivedSBoxF: return aPrefix + "pWorkspace->mDerivedSBoxF;";
        case TwistWorkSpaceSlot::kDerivedSBoxG: return aPrefix + "pWorkspace->mDerivedSBoxG;";
        case TwistWorkSpaceSlot::kDerivedSBoxH: return aPrefix + "pWorkspace->mDerivedSBoxH;";

        case TwistWorkSpaceSlot::kSeedExpansionLaneA: return aPrefix + "pWorkspace->mExpandLaneA;";
        case TwistWorkSpaceSlot::kSeedExpansionLaneB: return aPrefix + "pWorkspace->mExpandLaneB;";
        case TwistWorkSpaceSlot::kSeedExpansionLaneC: return aPrefix + "pWorkspace->mExpandLaneC;";
        case TwistWorkSpaceSlot::kSeedExpansionLaneD: return aPrefix + "pWorkspace->mExpandLaneD;";

        case TwistWorkSpaceSlot::kWorkLaneA: return aPrefix + "pWorkspace->mWorkLaneA;";
        case TwistWorkSpaceSlot::kWorkLaneB: return aPrefix + "pWorkspace->mWorkLaneB;";
        case TwistWorkSpaceSlot::kWorkLaneC: return aPrefix + "pWorkspace->mWorkLaneC;";
        case TwistWorkSpaceSlot::kWorkLaneD: return aPrefix + "pWorkspace->mWorkLaneD;";

        case TwistWorkSpaceSlot::kOperationLaneA: return aPrefix + "pWorkspace->mOperationLaneA;";
        case TwistWorkSpaceSlot::kOperationLaneB: return aPrefix + "pWorkspace->mOperationLaneB;";

        case TwistWorkSpaceSlot::kMaskLaneA: return aPrefix + "pWorkspace->mMaskLaneA;";
        case TwistWorkSpaceSlot::kMaskLaneB: return aPrefix + "pWorkspace->mMaskLaneB;";

        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return aPrefix + "&(pWorkspace->mKeyBoxA[0][0]);";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return aPrefix + "&(pWorkspace->mKeyBoxB[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowReadA: return aPrefix + "&(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]);";
        case TwistWorkSpaceSlot::kKeyRowReadB: return aPrefix + "&(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]);";
        case TwistWorkSpaceSlot::kKeyRowWriteA: return aPrefix + "&(pWorkspace->mKeyBoxA[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowWriteB: return aPrefix + "&(pWorkspace->mKeyBoxB[0][0]);";

        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return aPrefix + "&(pWorkspace->mMaskBoxA[0][0]);";
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return aPrefix + "&(pWorkspace->mMaskBoxB[0][0]);";
        case TwistWorkSpaceSlot::kMaskRowReadA: return aPrefix + "&(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]);";
        case TwistWorkSpaceSlot::kMaskRowReadB: return aPrefix + "&(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]);";
        case TwistWorkSpaceSlot::kMaskRowWriteA: return aPrefix + "&(pWorkspace->mMaskBoxA[0][0]);";
        case TwistWorkSpaceSlot::kMaskRowWriteB: return aPrefix + "&(pWorkspace->mMaskBoxB[0][0]);";

        default:
            return aPrefix +
                   "TwistWorkSpace::GetBuffer(pWorkspace, static_cast<TwistWorkSpaceSlot>(" +
                   std::to_string(static_cast<int>(pSlot)) + "));";
    }
}

bool ParseBatchJson(const std::string &pBatchJson,
                    GBatch *pBatch,
                    std::string *pErrorMessage) {
    if (pBatch == nullptr) {
        SetError(pErrorMessage, "Batch output was null.");
        return false;
    }

    if (!GBatch::FromJson(pBatchJson, pBatch, pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "Failed to parse branch batch JSON.";
        }
        return false;
    }

    return true;
}

bool ScopeBlockToFlatBody(const std::string &pScopeBlock,
                          std::string *pBody,
                          std::string *pErrorMessage) {
    if (pBody == nullptr) {
        SetError(pErrorMessage, "Batch scope-block body output was null.");
        return false;
    }

    std::vector<std::string> aLines;
    std::istringstream aStream(pScopeBlock);
    std::string aLine;
    while (std::getline(aStream, aLine)) {
        aLines.push_back(aLine);
    }

    std::size_t aFirst = 0U;
    while ((aFirst < aLines.size()) && TrimText(aLines[aFirst]).empty()) {
        ++aFirst;
    }

    std::size_t aLast = aLines.size();
    while ((aLast > aFirst) && TrimText(aLines[aLast - 1U]).empty()) {
        --aLast;
    }

    if ((aFirst >= aLast) ||
        (TrimText(aLines[aFirst]) != "{") ||
        (TrimText(aLines[aLast - 1U]) != "}")) {
        SetError(pErrorMessage, "Batch scope-block had unexpected format.");
        return false;
    }

    std::ostringstream aBody;
    bool aFirstLine = true;
    for (std::size_t aIndex = aFirst + 1U; aIndex + 1U < aLast; ++aIndex) {
        std::string aBodyLine = aLines[aIndex];
        if (StartsWithText(aBodyLine, "    ")) {
            aBodyLine.erase(0U, 4U);
        } else if (!aBodyLine.empty() && (aBodyLine.front() == '\t')) {
            aBodyLine.erase(aBodyLine.begin());
        }

        if (!aFirstLine) {
            aBody << '\n';
        }
        aFirstLine = false;
        aBody << aBodyLine;
    }

    *pBody = aBody.str();
    return true;
}

bool AppendBatchBlock(const GBatch &pBatch,
                      std::ostringstream *pStream,
                      std::string *pErrorMessage,
                      int pBatchNumber,
                      bool pInsertLeadingBlankLine) {
    if (pStream == nullptr) {
        SetError(pErrorMessage, "Batch output stream was null.");
        return false;
    }

    const std::string aScopeBlock = pBatch.BuildCppScopeBlock(pErrorMessage, false);
    if (aScopeBlock.empty()) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "Batch scope-block export returned empty text.";
        }
        return false;
    }

    std::string aFlatBody;
    if (!ScopeBlockToFlatBody(aScopeBlock, &aFlatBody, pErrorMessage)) {
        return false;
    }

    if (pInsertLeadingBlankLine) {
        *pStream << '\n';
    }

    *pStream << "    //\n"
             << "    // Batch " << pBatchNumber << "\n"
             << "    //\n\n";

    if (!aFlatBody.empty()) {
        *pStream << aFlatBody << '\n';
    }

    *pStream << '\n';
    return true;
}

bool AppendBranchBody(const TwistProgramBranch &pBranch,
                      std::ostringstream *pStream,
                      std::string *pErrorMessage,
                      const bool pSkipDestinationAlias) {
    if (pStream == nullptr) {
        SetError(pErrorMessage, "Branch output stream was null.");
        return false;
    }

    std::vector<GBatch> aBatches;
    for (const std::string &aBatchJson : pBranch.GetBatchJsonText()) {
        GBatch aBatch;
        if (!ParseBatchJson(aBatchJson, &aBatch, pErrorMessage)) {
            return false;
        }
        aBatches.push_back(aBatch);
    }

    std::vector<std::string> aDeclaredNames;
    for (const std::string &aLine : pBranch.GetStringLines()) {
        const std::string aNormalizedLine = NormalizeLegacyByteTypeLine(aLine);
        const std::string aDeclaredName = DeclaredIdentifierFromLine(aNormalizedLine);
        if (!aDeclaredName.empty()) {
            AppendUniqueValue(&aDeclaredNames, aDeclaredName);
        }
    }
    // Function parameters are already declared by signature.
    AppendUniqueValue(&aDeclaredNames, std::string("pSource"));
    AppendUniqueValue(&aDeclaredNames, std::string("pDestination"));

    std::vector<std::string> aLoopVariables;
    std::vector<std::string> aScalarVariables;
    std::vector<TwistWorkSpaceSlot> aReferencedSlots;
    for (const GBatch &aBatch : aBatches) {
        for (const GLoop &aLoop : aBatch.mLoops) {
            if (!aLoop.mLoopVariableName.empty()) {
                AppendUniqueValue(&aLoopVariables, aLoop.mLoopVariableName);
            }
        }
        for (const std::string &aName : aBatch.CollectVariableNames()) {
            AppendUniqueValue(&aScalarVariables, aName);
        }
        for (const TwistWorkSpaceSlot aSlot : aBatch.CollectReferencedSlots()) {
            AppendUniqueValue(&aReferencedSlots, aSlot);
        }
    }

    aScalarVariables.erase(
        std::remove_if(aScalarVariables.begin(),
                       aScalarVariables.end(),
                       [&aLoopVariables, &aDeclaredNames](const std::string &pName) {
                           return ContainsText(aLoopVariables, pName) || ContainsText(aDeclaredNames, pName);
                       }),
        aScalarVariables.end());

    bool aWroteDeclaration = false;
    const std::vector<TwistWorkSpaceSlot> aAllSlots = FixedWorkspaceSlotOrder();
    for (TwistWorkSpaceSlot aSlot : aAllSlots) {
        if (pSkipDestinationAlias && (aSlot == TwistWorkSpaceSlot::kDest)) {
            continue;
        }
        const std::string aAliasName = BufAliasName(aSlot);
        if (ContainsText(aDeclaredNames, aAliasName)) {
            continue;
        }

        const bool aReferencedByBatch =
            (std::find(aReferencedSlots.begin(), aReferencedSlots.end(), aSlot) != aReferencedSlots.end());

        bool aReferencedByLine = false;
        if (!aReferencedByBatch) {
            for (const std::string &aLine : pBranch.GetStringLines()) {
                if (ContainsIdentifierToken(aLine, aAliasName)) {
                    aReferencedByLine = true;
                    break;
                }
            }
        }

        if (!aReferencedByBatch && !aReferencedByLine) {
            continue;
        }

        const std::string aDeclaration = WorkspaceAliasDeclaration(aSlot);
        if (aDeclaration.empty()) {
            continue;
        }
        *pStream << "    " << aDeclaration << '\n';
        aWroteDeclaration = true;
    }

    for (const std::string &aVariable : aScalarVariables) {
        *pStream << "    " << ScalarCppTypeForName(aVariable) << " " << aVariable << " = 0;\n";
        aWroteDeclaration = true;
    }

    if (aWroteDeclaration) {
        *pStream << '\n';
    }

    int aBatchNumber = 0;
    bool aEmittedBatch = false;

    const std::vector<TwistProgramBranchStep> &aSteps = pBranch.GetSteps();
    if (aSteps.empty()) {
        for (const GBatch &aBatch : aBatches) {
            ++aBatchNumber;
            const bool aInsertLeadingBlankLine = (!aEmittedBatch && !aWroteDeclaration);
            if (!AppendBatchBlock(aBatch,
                                  pStream,
                                  pErrorMessage,
                                  aBatchNumber,
                                  aInsertLeadingBlankLine)) {
                return false;
            }
            aEmittedBatch = true;
        }
        return true;
    }

    for (const TwistProgramBranchStep &aStep : aSteps) {
        if (aStep.mType == TwistProgramBranchStepType::kLine) {
            if (aStep.mIndex >= pBranch.GetStringLines().size()) {
                SetError(pErrorMessage, "Branch line step index was out of range.");
                return false;
            }
            *pStream << "    " << NormalizeLegacyByteTypeLine(pBranch.GetStringLines()[aStep.mIndex]) << '\n';
            continue;
        }

        if (aStep.mType == TwistProgramBranchStepType::kBatch) {
            if (aStep.mIndex >= aBatches.size()) {
                SetError(pErrorMessage, "Branch batch step index was out of range.");
                return false;
            }

            ++aBatchNumber;
            const bool aInsertLeadingBlankLine = (!aEmittedBatch && !aWroteDeclaration);
            if (!AppendBatchBlock(aBatches[aStep.mIndex],
                                  pStream,
                                  pErrorMessage,
                                  aBatchNumber,
                                  aInsertLeadingBlankLine)) {
                return false;
            }
            aEmittedBatch = true;
            continue;
        }

        SetError(pErrorMessage, "Branch step type was invalid.");
        return false;
    }

    return true;
}

JsonValue BranchToJsonValue(const TwistProgramBranch &pBranch,
                            std::string *pErrorMessage) {
    JsonValue::Array aLines;
    for (const std::string &aLine : pBranch.GetStringLines()) {
        aLines.push_back(JsonValue::String(NormalizeLegacyByteTypeLine(aLine)));
    }

    JsonValue::Array aBatches;
    for (const std::string &aBatchJson : pBranch.GetBatchJsonText()) {
        auto aParsed = JsonValue::Parse(aBatchJson, pErrorMessage);
        if (!aParsed.has_value() || !aParsed->is_object()) {
            if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
                *pErrorMessage = "Failed to parse branch batch JSON for program export.";
            }
            return JsonValue::ObjectValue({});
        }
        aBatches.push_back(*aParsed);
    }

    JsonValue::Object aObject;
    aObject["string_lines"] = JsonValue::ArrayValue(std::move(aLines));
    aObject["batches"] = JsonValue::ArrayValue(std::move(aBatches));

    JsonValue::Array aSteps;
    for (const TwistProgramBranchStep &aStep : pBranch.GetSteps()) {
        JsonValue::Object aStepObject;
        aStepObject["type"] = JsonValue::String(
            (aStep.mType == TwistProgramBranchStepType::kLine) ? "line" : "batch");
        aStepObject["index"] = JsonValue::Number(static_cast<double>(aStep.mIndex));
        aSteps.push_back(JsonValue::ObjectValue(std::move(aStepObject)));
    }
    aObject["sequence"] = JsonValue::ArrayValue(std::move(aSteps));

    return JsonValue::ObjectValue(std::move(aObject));
}

std::string BytesToCppArray(const std::vector<std::uint8_t> &pBytes,
                            const std::string &pName,
                            const std::string &pLenToken) {
    std::ostringstream aOut;
    aOut << "const std::uint8_t " << pName << "[" << pLenToken << "] = {\n";

    for (std::size_t i = 0; i < pBytes.size(); ++i) {
        if ((i % 16U) == 0U) {
            aOut << "    ";
        }

        char aHex[8];
        std::snprintf(aHex, sizeof(aHex), "0x%02X", pBytes[i]);
        aOut << aHex;

        if (i + 1U < pBytes.size()) {
            aOut << ", ";
        }

        if ((i % 16U) == 15U || (i + 1U == pBytes.size())) {
            aOut << '\n';
        }
    }

    aOut << "};\n";
    return aOut.str();
}

JsonValue::Array BytesToJsonArray(const std::vector<std::uint8_t> &pBytes) {
    JsonValue::Array aOut;
    aOut.reserve(pBytes.size());
    for (std::uint8_t aByte : pBytes) {
        aOut.push_back(JsonValue::Number(static_cast<double>(aByte)));
    }
    return aOut;
}

} // namespace

void TwistProgramBranch::AddBatch(const GBatch &pBatch) {
    std::string aError;
    const std::string aBatchJson = pBatch.ToJson(&aError);
    if (aBatchJson.empty()) {
        std::printf("fatal: TwistProgramBranch::AddBatch failed: %s\n", aError.c_str());
        return;
    }

    mBatchJsonText.push_back(aBatchJson);
    TwistProgramBranchStep aStep;
    aStep.mType = TwistProgramBranchStepType::kBatch;
    aStep.mIndex = mBatchJsonText.size() - 1U;
    mSteps.push_back(aStep);
}

void TwistProgramBranch::AddLine(const std::string &pLine) {
    if (pLine.empty()) {
        return;
    }
    mStringLines.push_back(pLine);
    TwistProgramBranchStep aStep;
    aStep.mType = TwistProgramBranchStepType::kLine;
    aStep.mIndex = mStringLines.size() - 1U;
    mSteps.push_back(aStep);
}

void TwistProgramBranch::AddWorkspaceAliasLine(const std::string &pAliasName,
                                               const std::string &pWorkspaceFieldName) {
    if (pAliasName.empty() || pWorkspaceFieldName.empty()) {
        return;
    }

    const bool aInternalExpanderTable = StartsWithText(pWorkspaceFieldName, "mSalt") ||
                                        StartsWithText(pWorkspaceFieldName, "mSBox");
    if (aInternalExpanderTable) {
        AddLine("std::uint8_t *" + pAliasName + " = " + pWorkspaceFieldName + ";");
    } else {
        AddLine("std::uint8_t *" + pAliasName + " = pWorkspace->" + pWorkspaceFieldName + ";");
    }
}

void TwistProgramBranch::AddAssignByteLine(const std::string &pName,
                                           std::uint8_t pValue) {
    if (pName.empty()) {
        return;
    }

    char aHex[8];
    std::snprintf(aHex, sizeof(aHex), "0x%02X", pValue);
    AddLine(ScalarCppTypeForName(pName) + " " + pName + " = " + std::string(aHex) + ";");
}

void TwistProgramBranch::Clear() {
    mBatchJsonText.clear();
    mStringLines.clear();
    mSteps.clear();
}

const std::vector<std::string>& TwistProgramBranch::GetBatchJsonText() const {
    return mBatchJsonText;
}

const std::vector<std::string>& TwistProgramBranch::GetStringLines() const {
    return mStringLines;
}

const std::vector<TwistProgramBranchStep>& TwistProgramBranch::GetSteps() const {
    return mSteps;
}

bool GTwistExpander::ExportCPPProjectRoot(const std::string &pRootPath,
                                          std::string *pErrorMessage) const {
    const std::string aBaseInput = mNameBase.empty() ? "Generated" : mNameBase;
    const std::string aBaseName = SanitizeIdentifier(aBaseInput, "Generated");
    const std::string aClassName = "TwistExpander_" + aBaseName;

    const std::string aRootInput = pRootPath.empty() ? "generated/cpp" : pRootPath;
    const std::string aRoot = ResolveOutputPathFromProjectRoot(aRootInput);

    const std::string aHeaderPath = FileIO::Join(aRoot, aClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(aRoot, aClassName + ".cpp");

    GTwistExpander aSnapshot = *this;
    aSnapshot.RefreshTablePointers();

    std::ostringstream aHeader;
    aHeader << "#pragma once\n"
            << "\n"
            << "#include \"TwistExpander.hpp\"\n"
            << "\n"
            << "class " << aClassName << " : public TwistExpander {\n"
            << "public:\n"
            << "    " << aClassName << "();\n"
            << "    ~" << aClassName << "() override = default;\n"
            << "\n"
            << "    void Seed(TwistWorkSpace *pWorkspace,\n"
            << "              std::uint8_t *pSource,\n"
            << "              std::uint8_t *pPassword,\n"
            << "              unsigned int pPasswordByteLength) override;\n"
            << "    void TwistBlock(TwistWorkSpace *pWorkspace,\n"
            << "                    std::uint8_t *pSource,\n"
            << "                    std::uint8_t *pDestination) override;\n"
            << "\n"
            << "private:\n"
            << "    static const std::uint8_t kSBoxA[S_SBOX];\n"
            << "    static const std::uint8_t kSBoxB[S_SBOX];\n"
            << "    static const std::uint8_t kSBoxC[S_SBOX];\n"
            << "    static const std::uint8_t kSBoxD[S_SBOX];\n"
            << "    static const std::uint8_t kSaltA[S_SALT];\n"
            << "    static const std::uint8_t kSaltB[S_SALT];\n"
            << "    static const std::uint8_t kSaltC[S_SALT];\n"
            << "    static const std::uint8_t kSaltD[S_SALT];\n"
            << "};\n";

    std::ostringstream aCpp;
    aCpp << "#include \"" << aClassName << ".hpp\"\n"
         << "#include \"TwistFunctional.hpp\"\n"
         << "#include \"TwistMasking.hpp\"\n"
         << "#include \"TwistMix64.hpp\"\n"
         << "#include \"TwistSnow.hpp\"\n"
         << "#include \"TwistCryptoGenerator.hpp\"\n"
         << "\n"
         << "#include <cstring>\n"
         << "\n"
         << BytesToCppArray(aSnapshot._mSBoxA, aClassName + "::kSBoxA", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxB, aClassName + "::kSBoxB", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxC, aClassName + "::kSBoxC", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxD, aClassName + "::kSBoxD", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSaltA, aClassName + "::kSaltA", "S_SALT")
         << '\n'
         << BytesToCppArray(aSnapshot._mSaltB, aClassName + "::kSaltB", "S_SALT")
         << '\n'
         << BytesToCppArray(aSnapshot._mSaltC, aClassName + "::kSaltC", "S_SALT")
         << '\n'
         << BytesToCppArray(aSnapshot._mSaltD, aClassName + "::kSaltD", "S_SALT")
         << '\n'
         << aClassName << "::" << aClassName << "()\n"
         << ": TwistExpander() {\n"
         << "    std::memcpy(mSBoxA, kSBoxA, sizeof(mSBoxA));\n"
         << "    std::memcpy(mSBoxB, kSBoxB, sizeof(mSBoxB));\n"
         << "    std::memcpy(mSBoxC, kSBoxC, sizeof(mSBoxC));\n"
         << "    std::memcpy(mSBoxD, kSBoxD, sizeof(mSBoxD));\n"
         << "    std::memcpy(mSaltA, kSaltA, sizeof(mSaltA));\n"
         << "    std::memcpy(mSaltB, kSaltB, sizeof(mSaltB));\n"
         << "    std::memcpy(mSaltC, kSaltC, sizeof(mSaltC));\n"
         << "    std::memcpy(mSaltD, kSaltD, sizeof(mSaltD));\n"
         << "}\n"
         << "\n"
         << "void " << aClassName << "::Seed(TwistWorkSpace *pWorkspace,\n"
         << "                                 std::uint8_t *pSource,\n"
         << "                                 std::uint8_t *pPassword,\n"
         << "                                 unsigned int pPasswordByteLength) {\n"
         << "    TwistExpander::Seed(pWorkspace, pSource, pPassword, pPasswordByteLength);\n"
         << "    if (pWorkspace == nullptr) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mSeeder, &aCpp, pErrorMessage, true)) {
        return false;
    }
    aCpp << "}\n"
         << "\n"
         << "void " << aClassName << "::TwistBlock(TwistWorkSpace *pWorkspace,\n"
         << "                                       std::uint8_t *pSource,\n"
         << "                                       std::uint8_t *pDestination) {\n"
         << "    TwistExpander::TwistBlock(pWorkspace, pSource, pDestination);\n"
         << "    if ((pWorkspace == nullptr) || (pDestination == nullptr)) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mTwister, &aCpp, pErrorMessage, false)) {
        return false;
    }
    aCpp << "    std::memcpy(pDestination, pWorkspace->mWorkLaneD, S_BLOCK);\n"
         << "}\n";

    if (!SaveTextFile(aHeaderPath, aHeader.str(), pErrorMessage)) {
        return false;
    }
    if (!SaveTextFile(aCppPath, aCpp.str(), pErrorMessage)) {
        return false;
    }

    return true;
}

bool GTwistExpander::ExportJSONProjectRoot(const std::string &pRootPath,
                                           std::string *pErrorMessage) const {
    GTwistExpander aSnapshot = *this;
    aSnapshot.RefreshTablePointers();

    const std::string aBaseInput = aSnapshot.mNameBase.empty() ? "Generated" : aSnapshot.mNameBase;
    const std::string aBaseName = SanitizeIdentifier(aBaseInput, "Generated");

    JsonValue::Object aRootObject;
    aRootObject["name_base"] = JsonValue::String(aBaseInput);
    aRootObject["seed"] = BranchToJsonValue(aSnapshot.mSeeder, pErrorMessage);
    if ((pErrorMessage != nullptr) && !pErrorMessage->empty()) {
        return false;
    }

    aRootObject["twist"] = BranchToJsonValue(aSnapshot.mTwister, pErrorMessage);
    if ((pErrorMessage != nullptr) && !pErrorMessage->empty()) {
        return false;
    }

    JsonValue::Object aTables;
    aTables["sbox_a"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxA));
    aTables["sbox_b"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxB));
    aTables["sbox_c"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxC));
    aTables["sbox_d"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxD));
    aTables["salt_a"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSaltA));
    aTables["salt_b"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSaltB));
    aTables["salt_c"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSaltC));
    aTables["salt_d"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSaltD));
    aRootObject["tables"] = JsonValue::ObjectValue(std::move(aTables));

    const std::string aJsonText = JsonValue::ObjectValue(std::move(aRootObject)).Serialize();
    const std::string aRoot = pRootPath.empty() ? "generated/json" : pRootPath;
    const std::string aOutputPath = ResolveJsonOutputPath(aRoot, aBaseName);

    return SaveTextFile(aOutputPath, aJsonText, pErrorMessage);
}
