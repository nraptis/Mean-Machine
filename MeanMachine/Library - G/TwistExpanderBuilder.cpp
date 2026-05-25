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

void SetError(std::string *pError,
              const std::string &pMessage) {
    if (pError != nullptr) {
        *pError = pMessage;
    }
}

bool SaveTextFile(const std::string &pPath,
                  const std::string &pText,
                  std::string *pError) {
    const std::vector<std::uint8_t> aData(pText.begin(), pText.end());
    if (!FileIO::Save(pPath, aData)) {
        SetError(pError, "Failed to save file: " + pPath);
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

std::string IndentBlock(const std::string &pText,
                        const int pIndentLevel) {
    const std::string aIndent(static_cast<std::size_t>(pIndentLevel * 4), ' ');

    std::istringstream aSource(pText);
    std::ostringstream aResult;
    std::string aLine;
    bool aFirstLine = true;

    while (std::getline(aSource, aLine)) {
        if (!aFirstLine) {
            aResult << '\n';
        }
        aFirstLine = false;
        aResult << aIndent << aLine;
    }

    return aResult.str();
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
    if (pName == "aCross") { return 2; }
    if (pName == "aScatter") { return 3; }
    if (pName == "aCarry") { return 4; }
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

std::string ScalarDeclarationText(const std::string &pName) {
    return ScalarCppTypeForName(pName) + " " + pName + " = 0;";
}

void AppendScalarDeclarationLines(const std::vector<std::string> &pNames,
                                  const std::string &pIndent,
                                  std::ostringstream *pStream) {
    if ((pStream == nullptr) || pNames.empty()) {
        return;
    }

    constexpr std::size_t kDeclarationsPerLine = 4U;
    std::size_t aIndex = 0U;
    int aPreviousGroup = -1;
    while (aIndex < pNames.size()) {
        const int aGroup = ScalarDeclarationGroup(pNames[aIndex]);
        const std::string aType = ScalarCppTypeForName(pNames[aIndex]);
        if ((aPreviousGroup >= 0) && (aGroup != aPreviousGroup)) {
            *pStream << '\n';
        }

        *pStream << pIndent;
        std::size_t aLineCount = 0U;
        while ((aIndex < pNames.size()) &&
               (aLineCount < kDeclarationsPerLine) &&
               (ScalarDeclarationGroup(pNames[aIndex]) == aGroup) &&
               (ScalarCppTypeForName(pNames[aIndex]) == aType)) {
            if (aLineCount > 0U) {
                *pStream << ' ';
            }
            *pStream << ScalarDeclarationText(pNames[aIndex]);
            ++aLineCount;
            ++aIndex;
        }
        *pStream << '\n';
        aPreviousGroup = aGroup;
    }
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

std::string SanitizeSingleLineComment(const std::string &pText) {
    std::string aText = pText;
    for (char &aChar : aText) {
        if ((aChar == '\n') || (aChar == '\r') || (aChar == '\t')) {
            aChar = ' ';
        }
    }
    while (true) {
        const std::size_t aPos = aText.find("//");
        if (aPos == std::string::npos) {
            break;
        }
        aText.replace(aPos, 2U, "/ /");
    }
    return aText;
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

    return aLine;
}

std::vector<TwistWorkSpaceSlot> FixedWorkspaceSlotOrder() {
    return {
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

        TwistWorkSpaceSlot::kMaskLaneA,
        TwistWorkSpaceSlot::kMaskLaneB,

        TwistWorkSpaceSlot::kIndexList256A,
        TwistWorkSpaceSlot::kIndexList256B,
        TwistWorkSpaceSlot::kIndexList256C,
        TwistWorkSpaceSlot::kIndexList256D,
        TwistWorkSpaceSlot::kIndexList256E,
        TwistWorkSpaceSlot::kIndexList256F,

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

bool IsParamDomainSaltWorkspaceSlot(const TwistWorkSpaceSlot pSlot) {
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

std::string WorkspaceAliasDeclaration(const TwistWorkSpaceSlot pSlot,
                                      const bool pUseKDFParameterAliases) {
    const std::string aAlias = BufAliasName(pSlot);
    if ((pSlot == TwistWorkSpaceSlot::kIndexList256A) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256B) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256C) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256D) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256E) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256F)) {
        return "[[maybe_unused]] std::size_t *" + aAlias + " = reinterpret_cast<std::size_t *>(" +
               "TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(" +
               std::to_string(static_cast<int>(pSlot)) + ")));";
    }
    const std::string aPrefix = "[[maybe_unused]] std::uint8_t *" + aAlias + " = ";
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource:
            if (pUseKDFParameterAliases) {
                return aPrefix + "mSource;";
            }
            return aPrefix +
                   "TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(" +
                   std::to_string(static_cast<int>(pSlot)) + "));";
        case TwistWorkSpaceSlot::kDest:
            if (pUseKDFParameterAliases) {
                return aPrefix + "mDest;";
            }
            return aPrefix +
                   "TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(" +
                   std::to_string(static_cast<int>(pSlot)) + "));";

        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA:
            return "[[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB:
            return "[[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC:
            return "[[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD:
            return "[[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE:
            return "[[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF:
            return "[[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA:
            return "[[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB:
            return "[[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC:
            return "[[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD:
            return "[[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE:
            return "[[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF:
            return "[[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA:
            return "[[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB:
            return "[[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC:
            return "[[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD:
            return "[[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE:
            return "[[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF:
            return "[[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;";

        case TwistWorkSpaceSlot::kParamDomainSBoxA:
        case TwistWorkSpaceSlot::kParamDomainSBoxB:
        case TwistWorkSpaceSlot::kParamDomainSBoxC:
        case TwistWorkSpaceSlot::kParamDomainSBoxD:
        case TwistWorkSpaceSlot::kParamDomainSBoxE:
        case TwistWorkSpaceSlot::kParamDomainSBoxF:
        case TwistWorkSpaceSlot::kParamDomainSBoxG:
        case TwistWorkSpaceSlot::kParamDomainSBoxH:
            return aPrefix +
                   "TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(" +
                   std::to_string(static_cast<int>(pSlot)) + "));";

        case TwistWorkSpaceSlot::kExpansionLaneA: return aPrefix + "pWorkspace->mExpansionLaneA;";
        case TwistWorkSpaceSlot::kExpansionLaneB: return aPrefix + "pWorkspace->mExpansionLaneB;";
        case TwistWorkSpaceSlot::kExpansionLaneC: return aPrefix + "pWorkspace->mExpansionLaneC;";
        case TwistWorkSpaceSlot::kExpansionLaneD: return aPrefix + "pWorkspace->mExpansionLaneD;";
        case TwistWorkSpaceSlot::kExpansionLaneE: return aPrefix + "pWorkspace->mExpansionLaneE;";
        case TwistWorkSpaceSlot::kExpansionLaneF: return aPrefix + "pWorkspace->mExpansionLaneF;";

        case TwistWorkSpaceSlot::kWorkLaneA: return aPrefix + "pWorkspace->mWorkLaneA;";
        case TwistWorkSpaceSlot::kWorkLaneB: return aPrefix + "pWorkspace->mWorkLaneB;";
        case TwistWorkSpaceSlot::kWorkLaneC: return aPrefix + "pWorkspace->mWorkLaneC;";
        case TwistWorkSpaceSlot::kWorkLaneD: return aPrefix + "pWorkspace->mWorkLaneD;";
        case TwistWorkSpaceSlot::kWorkLaneE: return aPrefix + "pWorkspace->mWorkLaneE;";
        case TwistWorkSpaceSlot::kWorkLaneF: return aPrefix + "pWorkspace->mWorkLaneF;";

        case TwistWorkSpaceSlot::kOperationLaneA: return aPrefix + "pWorkspace->mOperationLaneA;";
        case TwistWorkSpaceSlot::kOperationLaneB: return aPrefix + "pWorkspace->mOperationLaneB;";
        case TwistWorkSpaceSlot::kOperationLaneC: return aPrefix + "pWorkspace->mOperationLaneC;";
        case TwistWorkSpaceSlot::kOperationLaneD: return aPrefix + "pWorkspace->mOperationLaneD;";
        case TwistWorkSpaceSlot::kOperationLaneE: return aPrefix + "pWorkspace->mOperationLaneE;";
        case TwistWorkSpaceSlot::kOperationLaneF: return aPrefix + "pWorkspace->mOperationLaneF;";

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
                   "TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(" +
                   std::to_string(static_cast<int>(pSlot)) + "));";
    }
}

bool ParseBatchJson(const std::string &pBatchJson,
                    GBatch *pBatch,
                    std::string *pError) {
    if (pBatch == nullptr) {
        SetError(pError, "Batch output was null.");
        return false;
    }

    if (!GBatch::FromJson(pBatchJson, pBatch, pError)) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Failed to parse branch batch JSON.";
        }
        return false;
    }

    return true;
}

bool AppendBranchBody(const TwistProgramBranch &pBranch,
                      const bool pIncludeKDFParameterAliases,
                      std::ostringstream *pStream,
                      std::string *pError) {
    if (pStream == nullptr) {
        SetError(pError, "Branch output stream was null.");
        return false;
    }

    struct ParsedBatch {
        bool mValid = false;
        std::size_t mIndex = 0U;
        GBatch mBatch;
        std::string mError;
    };

    std::vector<ParsedBatch> aParsedBatches;
    std::size_t aBatchIndex = 0U;
    for (const std::string &aBatchJson : pBranch.GetBatchJsonText()) {
        ParsedBatch aParsed;
        aParsed.mIndex = aBatchIndex++;
        GBatch aBatch;
        std::string aBatchError;
        if (!ParseBatchJson(aBatchJson, &aBatch, &aBatchError)) {
            aParsed.mValid = false;
            aParsed.mError = aBatchError.empty() ? "unknown parse error" : aBatchError;
            std::printf("warn: AppendBranchBody skipping batch %zu due to parse failure: %s\n",
                        aParsed.mIndex,
                        aParsed.mError.c_str());
        } else {
            aParsed.mValid = true;
            aParsed.mBatch = aBatch;
        }
        aParsedBatches.push_back(aParsed);
    }

    std::vector<std::string> aDeclaredNames;
    for (const std::string &aLine : pBranch.GetStringLines()) {
        const std::string aNormalizedLine = NormalizeLegacyByteTypeLine(aLine);
        const std::string aDeclaredName = DeclaredIdentifierFromLine(aNormalizedLine);
        if (!aDeclaredName.empty()) {
            AppendUniqueValue(&aDeclaredNames, aDeclaredName);
        }
    }

    std::vector<std::string> aLoopVariables;
    std::vector<std::string> aScalarVariables;
    for (const ParsedBatch &aParsed : aParsedBatches) {
        if (!aParsed.mValid) {
            continue;
        }
        const GBatch &aBatch = aParsed.mBatch;
        for (const GLoop &aLoop : aBatch.mLoops) {
            if (!aLoop.mLoopVariableName.empty()) {
                AppendUniqueValue(&aLoopVariables, aLoop.mLoopVariableName);
            }
        }
        for (const std::string &aName : aBatch.CollectVariableNames()) {
            AppendUniqueValue(&aScalarVariables, aName);
        }
    }

    aScalarVariables.erase(
        std::remove_if(aScalarVariables.begin(),
                       aScalarVariables.end(),
                       [&aLoopVariables, &aDeclaredNames](const std::string &pName) {
                           return ContainsText(aLoopVariables, pName) || ContainsText(aDeclaredNames, pName);
                       }),
        aScalarVariables.end());
    SortScalarDeclarationNames(&aScalarVariables);

    bool aWroteDeclaration = false;
    const std::vector<TwistWorkSpaceSlot> aAllSlots = FixedWorkspaceSlotOrder();
    for (TwistWorkSpaceSlot aSlot : aAllSlots) {
        if (!pIncludeKDFParameterAliases && IsParamDomainSaltWorkspaceSlot(aSlot)) {
            continue;
        }
        const std::string aAliasName = BufAliasName(aSlot);
        if (ContainsText(aDeclaredNames, aAliasName)) {
            continue;
        }
        *pStream << "    " << WorkspaceAliasDeclaration(aSlot, pIncludeKDFParameterAliases) << '\n';
        AppendUniqueValue(&aDeclaredNames, aAliasName);
        aWroteDeclaration = true;
    }

    if (!aScalarVariables.empty()) {
        AppendScalarDeclarationLines(aScalarVariables, "    ", pStream);
        aWroteDeclaration = true;
    }

    if (aWroteDeclaration) {
        *pStream << '\n';
    }

    for (const std::string &aLine : pBranch.GetStringLines()) {
        *pStream << "    " << NormalizeLegacyByteTypeLine(aLine) << '\n';
    }
    if (!pBranch.GetStringLines().empty()) {
        *pStream << '\n';
    }

    for (const ParsedBatch &aParsed : aParsedBatches) {
        if (!aParsed.mValid) {
            *pStream << "    // export warning: skipped batch #" << aParsed.mIndex
                     << " (" << SanitizeSingleLineComment(aParsed.mError) << ")\n";
            continue;
        }

        std::string aScopeError;
        const std::string aScopeBlock = aParsed.mBatch.BuildCppScopeBlock(&aScopeError, false);
        if (aScopeBlock.empty()) {
            if (aScopeError.empty()) {
                aScopeError = "Batch scope-block export returned empty text.";
            }
            std::printf("warn: AppendBranchBody skipping batch %zu due to scope-build failure: %s\n",
                        aParsed.mIndex,
                        aScopeError.c_str());
            *pStream << "    // export warning: skipped batch #" << aParsed.mIndex
                     << " (" << SanitizeSingleLineComment(aScopeError) << ")\n";
            continue;
        }

        *pStream << IndentBlock(aScopeBlock, 1) << '\n';
    }

    return true;
}

JsonValue BranchToJsonValue(const TwistProgramBranch &pBranch,
                            std::string *pError) {
    JsonValue::Array aLines;
    for (const std::string &aLine : pBranch.GetStringLines()) {
        aLines.push_back(JsonValue::String(NormalizeLegacyByteTypeLine(aLine)));
    }

    JsonValue::Array aBatches;
    std::size_t aBatchIndex = 0U;
    for (const std::string &aBatchJson : pBranch.GetBatchJsonText()) {
        auto aParsed = JsonValue::Parse(aBatchJson, pError);
        if (!aParsed.has_value() || !aParsed->is_object()) {
            std::string aParseError = (pError != nullptr) ? *pError : std::string();
            if (aParseError.empty()) {
                aParseError = "unknown JSON parse error";
            }
            std::printf("warn: BranchToJsonValue skipping batch %zu due to parse failure: %s\n",
                        aBatchIndex,
                        aParseError.c_str());
            if (pError != nullptr) {
                pError->clear();
            }
            ++aBatchIndex;
            continue;
        }
        aBatches.push_back(*aParsed);
        ++aBatchIndex;
    }

    JsonValue::Object aObject;
    aObject["string_lines"] = JsonValue::ArrayValue(std::move(aLines));
    aObject["batches"] = JsonValue::ArrayValue(std::move(aBatches));
    return JsonValue::ObjectValue(std::move(aObject));
}

bool BranchIsEmpty(const TwistProgramBranch &pBranch) {
    return pBranch.GetSteps().empty() &&
           pBranch.GetBatchJsonText().empty() &&
           pBranch.GetStringLines().empty();
}

JsonValue::Array BytesToJsonArray(const std::vector<std::uint8_t> &pBytes) {
    JsonValue::Array aOut;
    aOut.reserve(pBytes.size());
    for (std::uint8_t aByte : pBytes) {
        aOut.push_back(JsonValue::Number(static_cast<double>(aByte)));
    }
    return aOut;
}

JsonValue UInt64ToJsonValue(const std::uint64_t pValue) {
    return JsonValue::String(std::to_string(static_cast<unsigned long long>(pValue)));
}

JsonValue::Array UInt64ToJsonArray(const std::uint64_t *pValues,
                                   const std::size_t pCount) {
    JsonValue::Array aOut;
    if (pValues == nullptr) {
        return aOut;
    }
    aOut.reserve(pCount);
    for (std::size_t i = 0U; i < pCount; ++i) {
        aOut.push_back(UInt64ToJsonValue(pValues[i]));
    }
    return aOut;
}

JsonValue::Array BytesToJsonArray(const std::uint8_t *pValues,
                                  const std::size_t pCount) {
    JsonValue::Array aOut;
    if (pValues == nullptr) {
        return aOut;
    }
    aOut.reserve(pCount);
    for (std::size_t i = 0U; i < pCount; ++i) {
        aOut.push_back(JsonValue::Number(static_cast<double>(pValues[i])));
    }
    return aOut;
}

JsonValue SeedRoundMaterialToJsonValue(const TwistDomainSeedRoundMaterial &pMaterial) {
    JsonValue::Object aObject;
    aObject["salt_a"] = JsonValue::ArrayValue(UInt64ToJsonArray(pMaterial.mSaltA, S_SALT));
    aObject["salt_b"] = JsonValue::ArrayValue(UInt64ToJsonArray(pMaterial.mSaltB, S_SALT));
    aObject["salt_c"] = JsonValue::ArrayValue(UInt64ToJsonArray(pMaterial.mSaltC, S_SALT));
    aObject["salt_d"] = JsonValue::ArrayValue(UInt64ToJsonArray(pMaterial.mSaltD, S_SALT));
    aObject["salt_e"] = JsonValue::ArrayValue(UInt64ToJsonArray(pMaterial.mSaltE, S_SALT));
    aObject["salt_f"] = JsonValue::ArrayValue(UInt64ToJsonArray(pMaterial.mSaltF, S_SALT));
    return JsonValue::ObjectValue(std::move(aObject));
}

JsonValue ConstantsToJsonValue(const TwistDomainConstants &pConstants) {
    JsonValue::Object aObject;
    aObject["ingress"] = UInt64ToJsonValue(pConstants.mIngress);
    aObject["scatter"] = UInt64ToJsonValue(pConstants.mScatter);
    aObject["cross"] = UInt64ToJsonValue(pConstants.mCross);
    aObject["public_ingress"] = UInt64ToJsonValue(pConstants.mDomainConstantPublicIngress);
    aObject["private_ingress"] = UInt64ToJsonValue(pConstants.mDomainConstantPrivateIngress);
    aObject["cross_ingress"] = UInt64ToJsonValue(pConstants.mDomainConstantCrossIngress);
    aObject["matrix_select_a"] = UInt64ToJsonValue(pConstants.mMatrixSelectA);
    aObject["matrix_select_b"] = UInt64ToJsonValue(pConstants.mMatrixSelectB);
    aObject["matrix_unroll_a"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixUnrollA));
    aObject["matrix_unroll_b"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixUnrollB));
    aObject["matrix_scheme_a"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixSchemeA));
    aObject["matrix_scheme_b"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixSchemeB));
    aObject["matrix_arg_aa"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgA));
    aObject["matrix_arg_ab"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgB));
    aObject["matrix_arg_ba"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgC));
    aObject["matrix_arg_bb"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgD));
    aObject["mask_mutate_a"] = JsonValue::Number(static_cast<double>(pConstants.mMaskMutateA));
    aObject["mask_mutate_b"] = JsonValue::Number(static_cast<double>(pConstants.mMaskMutateB));
    return JsonValue::ObjectValue(std::move(aObject));
}

JsonValue SBoxSetToJsonValue(const TwistDomainSBoxSet &pSBoxSet) {
    JsonValue::Object aObject;
    aObject["sbox_a"] = JsonValue::ArrayValue(BytesToJsonArray(pSBoxSet.mSBoxA, S_SBOX));
    aObject["sbox_b"] = JsonValue::ArrayValue(BytesToJsonArray(pSBoxSet.mSBoxB, S_SBOX));
    aObject["sbox_c"] = JsonValue::ArrayValue(BytesToJsonArray(pSBoxSet.mSBoxC, S_SBOX));
    aObject["sbox_d"] = JsonValue::ArrayValue(BytesToJsonArray(pSBoxSet.mSBoxD, S_SBOX));
    aObject["sbox_e"] = JsonValue::ArrayValue(BytesToJsonArray(pSBoxSet.mSBoxE, S_SBOX));
    aObject["sbox_f"] = JsonValue::ArrayValue(BytesToJsonArray(pSBoxSet.mSBoxF, S_SBOX));
    aObject["sbox_g"] = JsonValue::ArrayValue(BytesToJsonArray(pSBoxSet.mSBoxG, S_SBOX));
    aObject["sbox_h"] = JsonValue::ArrayValue(BytesToJsonArray(pSBoxSet.mSBoxH, S_SBOX));
    return JsonValue::ObjectValue(std::move(aObject));
}

JsonValue DomainBundleToJsonValue(const TwistDomainBundle &pBundle) {
    JsonValue::Object aObject;
    aObject["mats_phase_a_seeder"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseASalts.mOrbiterAssign);
    aObject["mats_phase_a_orbiter"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseASalts.mOrbiterUpdate);
    aObject["mats_phase_a_wanderer"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseASalts.mWandererUpdate);
    aObject["mats_phase_b_seeder"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseBSalts.mOrbiterAssign);
    aObject["mats_phase_b_orbiter"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseBSalts.mOrbiterUpdate);
    aObject["mats_phase_b_wanderer"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseBSalts.mWandererUpdate);
    aObject["mats_phase_c_seeder"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseCSalts.mOrbiterAssign);
    aObject["mats_phase_c_orbiter"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseCSalts.mOrbiterUpdate);
    aObject["mats_phase_c_wanderer"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseCSalts.mWandererUpdate);
    aObject["constants_phase_a"] = ConstantsToJsonValue(pBundle.mPhaseAConstants);
    aObject["constants_phase_b"] = ConstantsToJsonValue(pBundle.mPhaseBConstants);
    aObject["constants_phase_c"] = ConstantsToJsonValue(pBundle.mPhaseCConstants);
    aObject["sboxes_phase_a"] = SBoxSetToJsonValue(pBundle.mPhaseASBoxes);
    aObject["sboxes_phase_b"] = SBoxSetToJsonValue(pBundle.mPhaseBSBoxes);
    aObject["sboxes_phase_c"] = SBoxSetToJsonValue(pBundle.mPhaseCSBoxes);
    return JsonValue::ObjectValue(std::move(aObject));
}

std::string IndentSpaces(const int pIndentLevel) {
    return std::string(static_cast<std::size_t>(pIndentLevel * 4), ' ');
}

std::string ByteCppLiteral(const std::uint8_t pValue) {
    char aHex[8];
    std::snprintf(aHex, sizeof(aHex), "0x%02X", pValue);
    return aHex;
}

std::string UInt64CppLiteral(const std::uint64_t pValue) {
    char aHex[32];
    std::snprintf(aHex,
                  sizeof(aHex),
                  "0x%016llXULL",
                  static_cast<unsigned long long>(pValue));
    return aHex;
}

void AppendByteArrayInitializer(std::ostringstream *pOut,
                                const std::uint8_t *pValues,
                                const std::size_t pCount,
                                const int pIndentLevel) {
    if ((pOut == nullptr) || (pValues == nullptr)) {
        return;
    }

    *pOut << IndentSpaces(pIndentLevel) << "{\n";
    for (std::size_t i = 0U; i < pCount; ++i) {
        if ((i % 16U) == 0U) {
            *pOut << IndentSpaces(pIndentLevel + 1);
        }

        *pOut << ByteCppLiteral(pValues[i]);
        if (i + 1U < pCount) {
            *pOut << ", ";
        }

        if (((i % 16U) == 15U) || (i + 1U == pCount)) {
            *pOut << '\n';
        }
    }
    *pOut << IndentSpaces(pIndentLevel) << "}";
}

void AppendUInt64ArrayInitializer(std::ostringstream *pOut,
                                  const std::uint64_t *pValues,
                                  const std::size_t pCount,
                                  const int pIndentLevel) {
    if ((pOut == nullptr) || (pValues == nullptr)) {
        return;
    }

    *pOut << IndentSpaces(pIndentLevel) << "{\n";
    for (std::size_t i = 0U; i < pCount; ++i) {
        if ((i % 4U) == 0U) {
            *pOut << IndentSpaces(pIndentLevel + 1);
        }

        *pOut << UInt64CppLiteral(pValues[i]);
        if (i + 1U < pCount) {
            *pOut << ", ";
        }

        if (((i % 4U) == 3U) || (i + 1U == pCount)) {
            *pOut << '\n';
        }
    }
    *pOut << IndentSpaces(pIndentLevel) << "}";
}

void AppendSeedRoundMaterialInitializer(std::ostringstream *pOut,
                                        const TwistDomainSeedRoundMaterial &pMaterial,
                                        const int pIndentLevel) {
    if (pOut == nullptr) {
        return;
    }

    *pOut << IndentSpaces(pIndentLevel) << "{\n";
    AppendUInt64ArrayInitializer(pOut, pMaterial.mSaltA, S_SALT, pIndentLevel + 1);
    *pOut << ",\n";
    AppendUInt64ArrayInitializer(pOut, pMaterial.mSaltB, S_SALT, pIndentLevel + 1);
    *pOut << ",\n";
    AppendUInt64ArrayInitializer(pOut, pMaterial.mSaltC, S_SALT, pIndentLevel + 1);
    *pOut << ",\n";
    AppendUInt64ArrayInitializer(pOut, pMaterial.mSaltD, S_SALT, pIndentLevel + 1);
    *pOut << ",\n";
    AppendUInt64ArrayInitializer(pOut, pMaterial.mSaltE, S_SALT, pIndentLevel + 1);
    *pOut << ",\n";
    AppendUInt64ArrayInitializer(pOut, pMaterial.mSaltF, S_SALT, pIndentLevel + 1);
    *pOut << "\n" << IndentSpaces(pIndentLevel) << "}";
}

void AppendSaltSetDefinition(std::ostringstream *pOut,
                             const std::string &pClassName,
                             const std::string &pMemberName,
                             const TwistDomainSaltSet &pSaltSet) {
    if (pOut == nullptr) {
        return;
    }

    *pOut << "const TwistDomainSaltSet " << pClassName << "::" << pMemberName << " = {\n";
    AppendSeedRoundMaterialInitializer(pOut, pSaltSet.mOrbiterAssign, 1);
    *pOut << ",\n";
    AppendSeedRoundMaterialInitializer(pOut, pSaltSet.mOrbiterUpdate, 1);
    *pOut << ",\n";
    AppendSeedRoundMaterialInitializer(pOut, pSaltSet.mWandererUpdate, 1);
    *pOut << "\n};\n";
}

void AppendConstantsDefinition(std::ostringstream *pOut,
                               const std::string &pClassName,
                               const std::string &pMemberName,
                               const TwistDomainConstants &pConstants) {
    if (pOut == nullptr) {
        return;
    }

    *pOut << "const TwistDomainConstants " << pClassName << "::" << pMemberName << " = {\n"
          << "    " << UInt64CppLiteral(pConstants.mIngress) << ",\n"
          << "    " << UInt64CppLiteral(pConstants.mScatter) << ",\n"
          << "    " << UInt64CppLiteral(pConstants.mCross) << ",\n"
          << "    " << UInt64CppLiteral(pConstants.mDomainConstantPublicIngress) << ",\n"
          << "    " << UInt64CppLiteral(pConstants.mDomainConstantPrivateIngress) << ",\n"
          << "    " << UInt64CppLiteral(pConstants.mDomainConstantCrossIngress) << ",\n"
          << "    " << UInt64CppLiteral(pConstants.mMatrixSelectA) << ",\n"
          << "    " << UInt64CppLiteral(pConstants.mMatrixSelectB) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixUnrollA) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixUnrollB) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixSchemeA) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixSchemeB) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgA) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgB) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgC) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgD) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMaskMutateA) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMaskMutateB) << "\n"
          << "};\n";
}

void AppendSBoxSetDefinition(std::ostringstream *pOut,
                             const std::string &pClassName,
                             const std::string &pMemberName,
                             const TwistDomainSBoxSet &pSBoxSet) {
    if (pOut == nullptr) {
        return;
    }

    *pOut << "const TwistDomainSBoxSet " << pClassName << "::" << pMemberName << " = {\n";
    AppendByteArrayInitializer(pOut, pSBoxSet.mSBoxA, S_SBOX, 1);
    *pOut << ",\n";
    AppendByteArrayInitializer(pOut, pSBoxSet.mSBoxB, S_SBOX, 1);
    *pOut << ",\n";
    AppendByteArrayInitializer(pOut, pSBoxSet.mSBoxC, S_SBOX, 1);
    *pOut << ",\n";
    AppendByteArrayInitializer(pOut, pSBoxSet.mSBoxD, S_SBOX, 1);
    *pOut << ",\n";
    AppendByteArrayInitializer(pOut, pSBoxSet.mSBoxE, S_SBOX, 1);
    *pOut << ",\n";
    AppendByteArrayInitializer(pOut, pSBoxSet.mSBoxF, S_SBOX, 1);
    *pOut << ",\n";
    AppendByteArrayInitializer(pOut, pSBoxSet.mSBoxG, S_SBOX, 1);
    *pOut << ",\n";
    AppendByteArrayInitializer(pOut, pSBoxSet.mSBoxH, S_SBOX, 1);
    *pOut << "\n};\n";
}

std::string DomainBundleStaticDefinitions(const std::string &pClassName,
                                          const TwistDomainBundle &pBundle) {
    std::ostringstream aOut;

    AppendSaltSetDefinition(&aOut, pClassName, "kPhaseASalts", pBundle.mPhaseASalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kPhaseAConstants", pBundle.mPhaseAConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kPhaseBSalts", pBundle.mPhaseBSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kPhaseBConstants", pBundle.mPhaseBConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kPhaseCSalts", pBundle.mPhaseCSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kPhaseCConstants", pBundle.mPhaseCConstants);
    aOut << '\n';
    AppendSBoxSetDefinition(&aOut, pClassName, "kPhaseASBoxes", pBundle.mPhaseASBoxes);
    aOut << '\n';
    AppendSBoxSetDefinition(&aOut, pClassName, "kPhaseBSBoxes", pBundle.mPhaseBSBoxes);
    aOut << '\n';
    AppendSBoxSetDefinition(&aOut, pClassName, "kPhaseCSBoxes", pBundle.mPhaseCSBoxes);

    return aOut.str();
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

    AddLine("std::uint8_t *" + pAliasName + " = pWorkspace->" + pWorkspaceFieldName + ";");
}

void TwistProgramBranch::AddAssignByteLine(const std::string &pName,
                                           std::uint8_t pValue) {
    if (pName.empty()) {
        return;
    }

    char aHex[8];
    std::snprintf(aHex, sizeof(aHex), "0x%02X", pValue);
    AddLine("std::uint8_t " + pName + " = " + std::string(aHex) + ";");
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
                                          std::string *pError) const {
    const std::string aBaseInput = mNameBase.empty() ? "Generated" : mNameBase;
    const std::string aBaseName = SanitizeIdentifier(aBaseInput, "Generated");
    const std::string aClassName = "TwistExpander_" + aBaseName;

    const std::string aRootInput = pRootPath.empty() ? "generated/cpp" : pRootPath;
    const std::string aRoot = ResolveOutputPathFromProjectRoot(aRootInput);

    const std::string aHeaderPath = FileIO::Join(aRoot, aClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(aRoot, aClassName + ".cpp");

    GTwistExpander aSnapshot = *this;
    aSnapshot.RefreshTablePointers();
    const TwistProgramBranch &aKDF_ABranch = BranchIsEmpty(aSnapshot.mKDF_A)
        ? aSnapshot.mKDF
        : aSnapshot.mKDF_A;
    const TwistProgramBranch &aKDF_BBranch = aSnapshot.mKDF_B;

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
            << "    void KDF(std::uint64_t pNonce,\n"
            << "             TwistDomainConstants *pConstants,\n"
            << "             TwistDomainSaltSet *pDomainSaltSet,\n"
            << "             TwistDomainSBoxSet *pDomainSBoxSet) override;\n"
            << "    void KDF_A(std::uint64_t pNonce,\n"
            << "               TwistDomainConstants *pConstants,\n"
            << "               TwistDomainSaltSet *pDomainSaltSet,\n"
            << "               TwistDomainSBoxSet *pDomainSBoxSet) override;\n"
            << "    void KDF_B(std::uint64_t pNonce,\n"
            << "               TwistDomainConstants *pConstants,\n"
            << "               TwistDomainSaltSet *pDomainSaltSet,\n"
            << "               TwistDomainSBoxSet *pDomainSBoxSet) override;\n"
            << "    void Seed(TwistWorkSpace *pWorkspace,\n"
            << "              TwistFarmSBox *pFarmSBox,\n"
            << "              TwistFarmSalt *pFarmSalt,\n"
            << "              std::uint64_t pNonce,\n"
            << "              std::uint8_t *pSourceInput,\n"
            << "              std::uint8_t *pPassword,\n"
            << "              unsigned int pPasswordByteLength) override;\n"
            << "    void TwistBlock(TwistWorkSpace *pWorkspace,\n"
            << "                    std::uint64_t pNonce,\n"
            << "                    std::uint8_t *pSourceInput,\n"
            << "                    std::uint8_t *pDestinationOutput) override;\n"
            << "\n"
            << "private:\n"
            << "    static const TwistDomainSaltSet kPhaseASalts;\n"
            << "    static const TwistDomainConstants kPhaseAConstants;\n"
            << "    static const TwistDomainSaltSet kPhaseBSalts;\n"
            << "    static const TwistDomainConstants kPhaseBConstants;\n"
            << "    static const TwistDomainSaltSet kPhaseCSalts;\n"
            << "    static const TwistDomainConstants kPhaseCConstants;\n"
            << "    static const TwistDomainSBoxSet kPhaseASBoxes;\n"
            << "    static const TwistDomainSBoxSet kPhaseBSBoxes;\n"
            << "    static const TwistDomainSBoxSet kPhaseCSBoxes;\n"
            << "};\n";

    std::ostringstream aCpp;
    aCpp << "#include \"" << aClassName << ".hpp\"\n"
         << "#include \"TwistFunctional.hpp\"\n"
         << "#include \"TwistIndexShuffle.hpp\"\n"
         << "#include \"TwistMix64.hpp\"\n"
         << "#include \"TwistFarmSalt.hpp\"\n"
         << "#include \"TwistFarmSBox.hpp\"\n"
         << "#include \"TwistFarmConstants.hpp\"\n"
         << "\n"
         << "#include <cstring>\n"
         << "\n"
         << aClassName << "::" << aClassName << "()\n"
         << ": TwistExpander() {\n"
         << "    mDomainBundleInbuilt.mPhaseASalts = kPhaseASalts;\n"
         << "    mDomainBundleInbuilt.mPhaseAConstants = kPhaseAConstants;\n"
         << "    mDomainBundleInbuilt.mPhaseBSalts = kPhaseBSalts;\n"
         << "    mDomainBundleInbuilt.mPhaseBConstants = kPhaseBConstants;\n"
         << "    mDomainBundleInbuilt.mPhaseCSalts = kPhaseCSalts;\n"
         << "    mDomainBundleInbuilt.mPhaseCConstants = kPhaseCConstants;\n"
         << "    mDomainBundleInbuilt.mPhaseASBoxes = kPhaseASBoxes;\n"
         << "    mDomainBundleInbuilt.mPhaseBSBoxes = kPhaseBSBoxes;\n"
         << "    mDomainBundleInbuilt.mPhaseCSBoxes = kPhaseCSBoxes;\n"
         << "    SyncLegacyFromDomainBundleInbuilt();\n"
         << "    std::memcpy(&mDomainBundleEphemeral, &mDomainBundleInbuilt, sizeof(mDomainBundleEphemeral));\n"
         << "}\n"
         << "\n"
         << "void " << aClassName << "::KDF(std::uint64_t pNonce,\n"
         << "                                TwistDomainConstants *pConstants,\n"
         << "                                TwistDomainSaltSet *pDomainSaltSet,\n"
         << "                                TwistDomainSBoxSet *pDomainSBoxSet) {\n"
         << "    KDF_A(pNonce, pConstants, pDomainSaltSet, pDomainSBoxSet);\n"
         << "}\n"
         << "\n"
         << "void " << aClassName << "::KDF_A(std::uint64_t pNonce,\n"
         << "                                  TwistDomainConstants *pConstants,\n"
         << "                                  TwistDomainSaltSet *pDomainSaltSet,\n"
         << "                                  TwistDomainSBoxSet *pDomainSBoxSet) {\n"
         << "    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pDomainSBoxSet);\n"
         << "    TwistWorkSpace *pWorkspace = mWorkspace;\n"
         << "    if ((pWorkspace == nullptr) || (mSource == nullptr) || (mDest == nullptr) ||\n"
         << "        (pConstants == nullptr) || (pDomainSaltSet == nullptr) || (pDomainSBoxSet == nullptr)) { return; }\n";
    if (!AppendBranchBody(aKDF_ABranch, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n"
         << "\n"
         << "void " << aClassName << "::KDF_B(std::uint64_t pNonce,\n"
         << "                                  TwistDomainConstants *pConstants,\n"
         << "                                  TwistDomainSaltSet *pDomainSaltSet,\n"
         << "                                  TwistDomainSBoxSet *pDomainSBoxSet) {\n"
         << "    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet, pDomainSBoxSet);\n"
         << "    TwistWorkSpace *pWorkspace = mWorkspace;\n"
         << "    if ((pWorkspace == nullptr) || (mSource == nullptr) || (mDest == nullptr) ||\n"
         << "        (pConstants == nullptr) || (pDomainSaltSet == nullptr) || (pDomainSBoxSet == nullptr)) { return; }\n";
    if (!AppendBranchBody(aKDF_BBranch, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n"
         << "\n"
         << "void " << aClassName << "::Seed(TwistWorkSpace *pWorkspace,\n"
         << "                                 TwistFarmSBox *pFarmSBox,\n"
         << "                                 TwistFarmSalt *pFarmSalt,\n"
         << "                                 std::uint64_t pNonce,\n"
         << "                                 std::uint8_t *pSourceInput,\n"
         << "                                 std::uint8_t *pPassword,\n"
         << "                                 unsigned int pPasswordByteLength) {\n"
         << "    TwistExpander::Seed(pWorkspace, pFarmSBox, pFarmSalt, pNonce, pSourceInput, pPassword, pPasswordByteLength);\n"
         << "    if ((pWorkspace == nullptr) || (pFarmSBox == nullptr) ||\n"
         << "        (pFarmSalt == nullptr) || (pSourceInput == nullptr)) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mSeed, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n"
         << "\n"
         << "void " << aClassName << "::TwistBlock(TwistWorkSpace *pWorkspace,\n"
         << "                                       std::uint64_t pNonce,\n"
         << "                                       std::uint8_t *pSourceInput,\n"
         << "                                       std::uint8_t *pDestinationOutput) {\n"
         << "    TwistExpander::TwistBlock(pWorkspace, pNonce, pSourceInput, pDestinationOutput);\n"
         << "    if ((pWorkspace == nullptr) || (pDestinationOutput == nullptr)) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mTwister, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "    std::memcpy(pDestinationOutput, pWorkspace->mWorkLaneD, S_BLOCK);\n"
         << "}\n"
         << "\n"
         << DomainBundleStaticDefinitions(aClassName, aSnapshot.mDomainBundleInbuilt)
         << "\n";

    if (!SaveTextFile(aHeaderPath, aHeader.str(), pError)) {
        return false;
    }
    if (!SaveTextFile(aCppPath, aCpp.str(), pError)) {
        return false;
    }

    return true;
}

bool GTwistExpander::ExportJSONProjectRoot(const std::string &pRootPath,
                                           std::string *pError) const {
    GTwistExpander aSnapshot = *this;
    aSnapshot.RefreshTablePointers();

    const std::string aBaseInput = aSnapshot.mNameBase.empty() ? "Generated" : aSnapshot.mNameBase;
    const std::string aBaseName = SanitizeIdentifier(aBaseInput, "Generated");

    JsonValue::Object aRootObject;
    aRootObject["name_base"] = JsonValue::String(aBaseInput);
    const TwistProgramBranch &aKDF_ABranch = BranchIsEmpty(aSnapshot.mKDF_A)
        ? aSnapshot.mKDF
        : aSnapshot.mKDF_A;
    aRootObject["kdf_a"] = BranchToJsonValue(aKDF_ABranch, pError);
    if ((pError != nullptr) && !pError->empty()) {
        return false;
    }

    aRootObject["kdf_b"] = BranchToJsonValue(aSnapshot.mKDF_B, pError);
    if ((pError != nullptr) && !pError->empty()) {
        return false;
    }

    aRootObject["kdf"] = BranchToJsonValue(aKDF_ABranch, pError);
    if ((pError != nullptr) && !pError->empty()) {
        return false;
    }

    aRootObject["seed"] = BranchToJsonValue(aSnapshot.mSeed, pError);
    if ((pError != nullptr) && !pError->empty()) {
        return false;
    }

    aRootObject["twist"] = BranchToJsonValue(aSnapshot.mTwister, pError);
    if ((pError != nullptr) && !pError->empty()) {
        return false;
    }

    JsonValue::Object aTables;
    aTables["sbox_a"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxA));
    aTables["sbox_b"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxB));
    aTables["sbox_c"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxC));
    aTables["sbox_d"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxD));
    aTables["sbox_e"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxE));
    aTables["sbox_f"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxF));
    aTables["sbox_g"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxG));
    aTables["sbox_h"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxH));
    aTables["domain_bundle_inbuilt"] = DomainBundleToJsonValue(aSnapshot.mDomainBundleInbuilt);
    aRootObject["tables"] = JsonValue::ObjectValue(std::move(aTables));

    const std::string aJsonText = JsonValue::ObjectValue(std::move(aRootObject)).Serialize();
    const std::string aRoot = pRootPath.empty() ? "generated/json" : pRootPath;
    const std::string aOutputPath = ResolveJsonOutputPath(aRoot, aBaseName);

    return SaveTextFile(aOutputPath, aJsonText, pError);
}
