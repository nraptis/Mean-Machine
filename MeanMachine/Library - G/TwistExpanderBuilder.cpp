//
//  TwistExpanderBuilder.cpp
//  MeanMachine
//

#include "GTwistExpander.hpp"

#include "FileIO.hpp"
#include "GSeedRunStage.hpp"
#include "GJson.hpp"
#include "Random.hpp"

#include <array>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
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

const std::array<const char *, 3> kNonceDiffuseNames = {
    "DiffuseA",
    "DiffuseB",
    "DiffuseC",
};

std::string UInt64Literal(const std::uint64_t pValue) {
    std::ostringstream aStream;
    aStream << "0x" << std::uppercase << std::hex << pValue << "ULL";
    return aStream.str();
}

const char *RandomNonceDiffuseName() {
    return kNonceDiffuseNames[static_cast<std::size_t>(Random::Get(static_cast<int>(kNonceDiffuseNames.size())))];
}

std::string NonceDeclareLine(const GSymbol &pNonceSymbol,
                             const int pIndex) {
    (void)pIndex;
    const std::uint64_t aMultiplyWord = Random::Get64HighOdd();
    const std::uint64_t aAddWord = Random::Get64High();
    const char *aDiffuseName = RandomNonceDiffuseName();

    std::ostringstream aLine;
    aLine << "std::uint64_t " << pNonceSymbol.mName << " = TwistMix64::"
          << aDiffuseName
          << "(pNonce * "
          << UInt64Literal(aMultiplyWord)
          << " + "
          << UInt64Literal(aAddWord) << ");";
    return aLine.str();
}

const char *InvestLaneAliasName(const int pIndex) {
    static const char *kNames[8] = {
        "aInvestLaneA",
        "aInvestLaneB",
        "aInvestLaneC",
        "aInvestLaneD",
        "aInvestLaneE",
        "aInvestLaneF",
        "aInvestLaneG",
        "aInvestLaneH"
    };
    if ((pIndex < 0) || (pIndex >= 8)) {
        return "aInvestLaneA";
    }
    return kNames[pIndex];
}

const char *FragmentAliasName(const int pIndex) {
    static const char *kNames[8] = {
        "aFragmentA",
        "aFragmentB",
        "aFragmentC",
        "aFragmentD",
        "aFragmentE",
        "aFragmentF",
        "aFragmentG",
        "aFragmentH"
    };
    if ((pIndex < 0) || (pIndex >= 8)) {
        return "aFragmentA";
    }
    return kNames[pIndex];
}

std::string RandomDiffuse64Name() {
    switch (Random::Get(3)) {
        case 0: return "DiffuseA";
        case 1: return "DiffuseB";
        default: return "DiffuseC";
    }
}

std::vector<int> ShuffledInvestOffsetOrder() {
    const int aOffsetCount = S_BLOCK / W_KEY;
    std::vector<int> aOffsets;
    aOffsets.reserve(static_cast<std::size_t>(aOffsetCount));
    for (int aIndex = 0; aIndex < aOffsetCount; ++aIndex) {
        aOffsets.push_back(aIndex);
    }
    Random::Shuffle(&aOffsets);
    return aOffsets;
}

std::string BuildSquashInvestToKeyBoxesMethod(const std::string &pClassName) {
    constexpr int kLaneCount = 8;
    constexpr int kFragmentCount = 16;

    std::array<std::vector<int>, kLaneCount> aOffsetOrders;
    for (int aLane = 0; aLane < kLaneCount; ++aLane) {
        aOffsetOrders[static_cast<std::size_t>(aLane)] = ShuffledInvestOffsetOrder();
    }

    std::ostringstream aStream;
    aStream << "void " << pClassName << "::SquashInvestToKeyBoxes() {\n"
    << "    TwistWorkSpace *pWorkSpace = mWorkspace;\n"
    << "    if (pWorkSpace == nullptr) { return; }\n"
    << "    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;\n"
    << "    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;\n"
    << "    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;\n"
    << "    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;\n"
    << "    [[maybe_unused]] std::uint8_t *aInvestLaneE = pWorkSpace->mInvestLaneE;\n"
    << "    [[maybe_unused]] std::uint8_t *aInvestLaneF = pWorkSpace->mInvestLaneF;\n"
    << "    [[maybe_unused]] std::uint8_t *aInvestLaneG = pWorkSpace->mInvestLaneG;\n"
    << "    [[maybe_unused]] std::uint8_t *aInvestLaneH = pWorkSpace->mInvestLaneH;\n"
    << "\n";

    for (int aFragmentIndex = 0; aFragmentIndex < kFragmentCount; ++aFragmentIndex) {
        const bool aUseKeyBoxA = (aFragmentIndex < H_KEY);
        const int aRowIndex = aUseKeyBoxA ? aFragmentIndex : (aFragmentIndex - H_KEY);
        const char *aKeyBoxName = aUseKeyBoxA ? "mKeyBoxA" : "mKeyBoxB";
        const char *aKeyBoxComment = aUseKeyBoxA ? "key_box_a" : "key_box_b";
        std::vector<int> aShifts = { 0, 8, 16, 24, 32, 40, 48, 56 };
        Random::Shuffle(&aShifts);
        const std::string aDiffuseName = RandomDiffuse64Name();

        aStream << "    // " << aKeyBoxComment << " row " << aRowIndex << "\n"
        << "    {\n";
        for (int aLane = 0; aLane < kLaneCount; aLane += 2) {
            const std::vector<int> &aOffsetsA = aOffsetOrders[static_cast<std::size_t>(aLane)];
            const std::vector<int> &aOffsetsB = aOffsetOrders[static_cast<std::size_t>(aLane + 1)];
            const int aOffsetA = aOffsetsA[static_cast<std::size_t>(aFragmentIndex % static_cast<int>(aOffsetsA.size()))];
            const int aOffsetB = aOffsetsB[static_cast<std::size_t>(aFragmentIndex % static_cast<int>(aOffsetsB.size()))];
            aStream << "        std::uint8_t *" << FragmentAliasName(aLane)
            << " = " << InvestLaneAliasName(aLane)
            << " + (W_KEY * " << aOffsetA << "U), *"
            << FragmentAliasName(aLane + 1)
            << " = " << InvestLaneAliasName(aLane + 1)
            << " + (W_KEY * " << aOffsetB << "U);\n";
        }
        aStream << "        std::uint8_t *aKeyRow = &(pWorkSpace->" << aKeyBoxName
        << "[" << aRowIndex << "][0]);\n"
        << "        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {\n"
        << "            std::uint64_t aSquash =\n";
        for (int aLane = 0; aLane < kLaneCount; aLane += 2) {
            aStream << "                (static_cast<std::uint64_t>(" << FragmentAliasName(aLane)
            << "[aIndex]) << " << aShifts[static_cast<std::size_t>(aLane)] << "U) | "
            << "(static_cast<std::uint64_t>(" << FragmentAliasName(aLane + 1)
            << "[aIndex]) << " << aShifts[static_cast<std::size_t>(aLane + 1)] << "U)";
            if (aLane == (kLaneCount - 2)) {
                aStream << ";\n";
            } else {
                aStream << " |\n";
            }
        }
        aStream << "            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::"
        << aDiffuseName << "(aSquash));\n"
        << "        }\n"
        << "    }\n";
        if (aFragmentIndex != (kFragmentCount - 1)) {
            aStream << "\n";
        }
    }

    aStream << "}\n";
    return aStream.str();
}

[[maybe_unused]] std::string ResolveJsonOutputPath(const std::string &pRootPath,
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

bool IsFixedRandomArxStateScalarName(const std::string &pName) {
    return (pName == "aPrevious") ||
           (pName == "aIngress") ||
           (pName == "aCarry") ||
           (LetterIndexFromSuffix(pName, "aWanderer") >= 0);
}

std::string ScalarInitialValueForName(const std::string &pName) {
    if (IsFixedRandomArxStateScalarName(pName)) {
        return UInt64Literal(Random::Get64High());
    }
    return "0";
}

std::string ScalarDeclarationText(const std::string &pName) {
    return ScalarCppTypeForName(pName) + " " + pName + " = " + ScalarInitialValueForName(pName) + ";";
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

bool RawLinesContainText(const std::vector<std::string> &pLines,
                         const std::string &pText) {
    for (const std::string &aLine : pLines) {
        if (aLine.find(pText) != std::string::npos) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> CollectReferencedWorkspaceDomainWords(const std::vector<std::string> &pScalarVariables,
                                                               const std::vector<std::string> &pRawLines,
                                                               const std::vector<std::string> &pDeclaredNames) {
    std::vector<std::string> aResult;
    for (const std::string &aName : WorkspaceDomainWordAliasOrder()) {
        if (ContainsText(pDeclaredNames, aName)) {
            continue;
        }
        if (ContainsText(pScalarVariables, aName) || RawLinesContainText(pRawLines, aName)) {
            aResult.push_back(aName);
        }
    }
    return aResult;
}

std::string WorkspaceDomainWordDeclaration(const std::string &pName) {
    TwistDomain aDomain = TwistDomain::kInvalid;
    TwistConstants aConstant = TwistConstants::kInvalid;
    if (!WorkspaceDomainWordAliasInfo(pName, &aDomain, &aConstant)) {
        return "";
    }

    const std::string aAccess = WorkspaceDomainWordAccessText(aDomain, aConstant);
    if (aAccess.empty()) {
        return "";
    }
    return "const std::uint64_t &" + pName + " = " + aAccess + ";";
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

bool DecodePhaseSaltWorkspaceSlot(const TwistWorkSpaceSlot pSlot,
                                  int *pPhaseOut,
                                  int *pRoleOut,
                                  int *pLaneOut) {
    const int aValue = static_cast<int>(pSlot);
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kPhaseASaltOrbiterAssignA);
    const int aCountPerPhase = 18;
    const int aPhaseCount = 8;
    if ((aValue < aBase) || (aValue >= (aBase + aCountPerPhase * aPhaseCount))) {
        return false;
    }

    const int aOffset = aValue - aBase;
    const int aRoleLaneOffset = aOffset % aCountPerPhase;
    if (pPhaseOut != nullptr) {
        *pPhaseOut = aOffset / aCountPerPhase;
    }
    if (pRoleOut != nullptr) {
        *pRoleOut = aRoleLaneOffset / 6;
    }
    if (pLaneOut != nullptr) {
        *pLaneOut = aRoleLaneOffset % 6;
    }
    return true;
}

void AppendPhaseSaltWorkspaceSlots(std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pSlots == nullptr) {
        return;
    }
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kPhaseASaltOrbiterAssignA);
    const int aCount = 18 * 8;
    for (int aOffset = 0; aOffset < aCount; ++aOffset) {
        pSlots->push_back(static_cast<TwistWorkSpaceSlot>(aBase + aOffset));
    }
}

std::string PhaseSaltWorkspaceDeclaration(const TwistWorkSpaceSlot pSlot) {
    int aPhase = 0;
    int aRole = 0;
    int aLane = 0;
    if (!DecodePhaseSaltWorkspaceSlot(pSlot, &aPhase, &aRole, &aLane)) {
        return "";
    }

    static const char *kPhaseMembers[] = {
        "mPhaseASalts",
        "mPhaseBSalts",
        "mPhaseCSalts",
        "mPhaseDSalts",
        "mPhaseESalts",
        "mPhaseFSalts",
        "mPhaseGSalts",
        "mPhaseHSalts"
    };
    static const char *kRoleMembers[] = {
        "mOrbiterAssign",
        "mOrbiterUpdate",
        "mWandererUpdate"
    };
    static const char *kLaneMembers[] = {
        "mSaltA",
        "mSaltB",
        "mSaltC",
        "mSaltD",
        "mSaltE",
        "mSaltF"
    };

    return "[[maybe_unused]] std::uint64_t *" + BufAliasName(pSlot) +
           " = pWorkSpace->mDomainBundle." + kPhaseMembers[aPhase] +
           "." + kRoleMembers[aRole] + "." + kLaneMembers[aLane] + ";";
}

std::vector<TwistWorkSpaceSlot> FixedWorkspaceSlotOrder() {
    std::vector<TwistWorkSpaceSlot> aSlots = {
        TwistWorkSpaceSlot::kSource,

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
        TwistWorkSpaceSlot::kKeyRowWriteB
    };
    AppendPhaseSaltWorkspaceSlots(&aSlots);
    return aSlots;
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

bool IsKDFExcludedWorkspaceSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA:
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB:
        case TwistWorkSpaceSlot::kKeyRowReadA:
        case TwistWorkSpaceSlot::kKeyRowReadB:
        case TwistWorkSpaceSlot::kKeyRowWriteA:
        case TwistWorkSpaceSlot::kKeyRowWriteB:
        case TwistWorkSpaceSlot::kSnowLaneA:
        case TwistWorkSpaceSlot::kSnowLaneB:
        case TwistWorkSpaceSlot::kSnowLaneC:
        case TwistWorkSpaceSlot::kSnowLaneD:
            return true;
        default:
            return false;
    }
}

bool IsImplicitPointerWorkspaceSlot(const TwistWorkSpaceSlot pSlot) {
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

std::string WorkspaceAliasDeclaration(const TwistWorkSpaceSlot pSlot,
                                      const bool pUseKDFParameterAliases) {
    const std::string aPhaseSaltDeclaration = PhaseSaltWorkspaceDeclaration(pSlot);
    if (!aPhaseSaltDeclaration.empty()) {
        return aPhaseSaltDeclaration;
    }

    const std::string aAlias = BufAliasName(pSlot);
    if ((pSlot == TwistWorkSpaceSlot::kIndexList256A) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256B) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256C) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256D)) {
        return "[[maybe_unused]] std::size_t *" + aAlias + " = mIndexList256" +
               aAlias.substr(aAlias.size() - 1U) + ";";
    }
    const std::string aPrefix = "[[maybe_unused]] std::uint8_t *" + aAlias + " = ";
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource:
            if (pUseKDFParameterAliases) {
                return aPrefix + "mSource;";
            }
            return aPrefix +
                   "TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(" +
                   std::to_string(static_cast<int>(pSlot)) + "));";
        case TwistWorkSpaceSlot::kParamDestination:
            if (pUseKDFParameterAliases) {
                return aPrefix + "pDestination;";
            }
            return aPrefix +
                   "TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(" +
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

        case TwistWorkSpaceSlot::kExpansionLaneA: return aPrefix + "pWorkSpace->mExpansionLaneA;";
        case TwistWorkSpaceSlot::kExpansionLaneB: return aPrefix + "pWorkSpace->mExpansionLaneB;";
        case TwistWorkSpaceSlot::kExpansionLaneC: return aPrefix + "pWorkSpace->mExpansionLaneC;";
        case TwistWorkSpaceSlot::kExpansionLaneD: return aPrefix + "pWorkSpace->mExpansionLaneD;";

        case TwistWorkSpaceSlot::kWorkLaneA: return aPrefix + "pWorkSpace->mWorkLaneA;";
        case TwistWorkSpaceSlot::kWorkLaneB: return aPrefix + "pWorkSpace->mWorkLaneB;";
        case TwistWorkSpaceSlot::kWorkLaneC: return aPrefix + "pWorkSpace->mWorkLaneC;";
        case TwistWorkSpaceSlot::kWorkLaneD: return aPrefix + "pWorkSpace->mWorkLaneD;";

        case TwistWorkSpaceSlot::kOperationLaneA: return aPrefix + "pWorkSpace->mOperationLaneA;";
        case TwistWorkSpaceSlot::kOperationLaneB: return aPrefix + "pWorkSpace->mOperationLaneB;";
        case TwistWorkSpaceSlot::kOperationLaneC: return aPrefix + "pWorkSpace->mOperationLaneC;";
        case TwistWorkSpaceSlot::kOperationLaneD: return aPrefix + "pWorkSpace->mOperationLaneD;";

        case TwistWorkSpaceSlot::kSnowLaneA: return aPrefix + "pWorkSpace->mSnowLaneA;";
        case TwistWorkSpaceSlot::kSnowLaneB: return aPrefix + "pWorkSpace->mSnowLaneB;";
        case TwistWorkSpaceSlot::kSnowLaneC: return aPrefix + "pWorkSpace->mSnowLaneC;";
        case TwistWorkSpaceSlot::kSnowLaneD: return aPrefix + "pWorkSpace->mSnowLaneD;";
        case TwistWorkSpaceSlot::kFireLaneA: return aPrefix + "pWorkSpace->mFireLaneA;";
        case TwistWorkSpaceSlot::kFireLaneB: return aPrefix + "pWorkSpace->mFireLaneB;";
        case TwistWorkSpaceSlot::kFireLaneC: return aPrefix + "pWorkSpace->mFireLaneC;";
        case TwistWorkSpaceSlot::kFireLaneD: return aPrefix + "pWorkSpace->mFireLaneD;";
        case TwistWorkSpaceSlot::kParamSnow: return aPrefix + "pSnow;";

        case TwistWorkSpaceSlot::kInvestA: return aPrefix + "pWorkSpace->mInvestLaneA;";
        case TwistWorkSpaceSlot::kInvestB: return aPrefix + "pWorkSpace->mInvestLaneB;";
        case TwistWorkSpaceSlot::kInvestC: return aPrefix + "pWorkSpace->mInvestLaneC;";
        case TwistWorkSpaceSlot::kInvestD: return aPrefix + "pWorkSpace->mInvestLaneD;";
        case TwistWorkSpaceSlot::kInvestE: return aPrefix + "pWorkSpace->mInvestLaneE;";
        case TwistWorkSpaceSlot::kInvestF: return aPrefix + "pWorkSpace->mInvestLaneF;";
        case TwistWorkSpaceSlot::kInvestG: return aPrefix + "pWorkSpace->mInvestLaneG;";
        case TwistWorkSpaceSlot::kInvestH: return aPrefix + "pWorkSpace->mInvestLaneH;";

        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return aPrefix + "&(pWorkSpace->mKeyBoxA[0][0]);";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return aPrefix + "&(pWorkSpace->mKeyBoxB[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowReadA: return aPrefix + "&(pWorkSpace->mKeyBoxA[H_KEY - 1][0]);";
        case TwistWorkSpaceSlot::kKeyRowReadB: return aPrefix + "&(pWorkSpace->mKeyBoxB[H_KEY - 1][0]);";
        case TwistWorkSpaceSlot::kKeyRowWriteA: return aPrefix + "&(pWorkSpace->mKeyBoxA[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowWriteB: return aPrefix + "&(pWorkSpace->mKeyBoxB[0][0]);";

        default:
            return aPrefix +
                   "TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(" +
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

enum class ArxCallKind {
    kKDF,
    kSeed,
    kTwist,
    kGrow,
};

struct ArxCallExport {
    ArxCallKind mKind = ArxCallKind::kKDF;
    bool mUsesSnow = false;
    bool mUsesNonce = true;
    std::string mBatchName;
    std::string mStartLine;
    std::string mEndLine;
    std::string mClassName;
    std::string mMethodName;
    std::string mTitle;
    std::string mReadFrom;
    std::string mTempStorage;
    std::string mWriteTo;
};

const ArxCallExport *FindArxCallForBatch(const std::vector<const ArxCallExport *> &pArxCalls,
                                         const std::string &pBatchName) {
    for (const ArxCallExport *aArxCall : pArxCalls) {
        if ((aArxCall != nullptr) && (aArxCall->mBatchName == pBatchName)) {
            return aArxCall;
        }
    }
    return nullptr;
}

bool IsExternalArxBatch(const std::vector<const ArxCallExport *> &pArxCalls,
                        const GBatch &pBatch) {
    return FindArxCallForBatch(pArxCalls, pBatch.mName) != nullptr;
}

bool ShouldSkipExternalArxLine(const std::vector<const ArxCallExport *> &pArxCalls,
                               const std::string &pLine) {
    for (const ArxCallExport *pArxCall : pArxCalls) {
        if (pArxCall == nullptr) {
            continue;
        }
        if ((pLine == pArxCall->mStartLine) ||
            (pLine == pArxCall->mEndLine)) {
            return true;
        }
    }
    return false;
}

bool IsArxOnlyKDFDomainWord(const std::string &pName) {
    return (pName == "aDomainWordIngress") ||
           (pName == "aDomainWordScatter") ||
           (pName == "aDomainWordCross");
}

bool IsArxOnlyDomainWordAssignmentLine(const std::string &pLine,
                                       const std::vector<std::string> &pReferencedScalarVariables) {
    for (const char *aName : {"aDomainWordIngress", "aDomainWordScatter", "aDomainWordCross"}) {
        if (ContainsText(pReferencedScalarVariables, std::string(aName))) {
            continue;
        }

        const std::string aDeclarePrefix = std::string("std::uint64_t ") + aName + " = ";
        const std::string aAssignPrefix = std::string(aName) + " = ";
        if ((pLine.rfind(aDeclarePrefix, 0U) == 0U) ||
            (pLine.rfind(aAssignPrefix, 0U) == 0U)) {
            return true;
        }
    }
    return false;
}

bool ShouldSkipUnusedExternalArxDeclarationLine(const std::vector<const ArxCallExport *> &pArxCalls,
                                                const std::vector<std::string> &pReferencedScalarVariables,
                                                const std::string &pLine) {
    if (pArxCalls.empty()) {
        return false;
    }

    if (IsArxOnlyDomainWordAssignmentLine(pLine, pReferencedScalarVariables)) {
        return true;
    }

    const std::string aDeclaredName = DeclaredIdentifierFromLine(pLine);
    if (!IsArxOnlyKDFDomainWord(aDeclaredName)) {
        return false;
    }

    return !ContainsText(pReferencedScalarVariables, aDeclaredName);
}

const std::array<const char *, 14> kExternalArxStateVariables = {
    "aPrevious",
    "aIngress",
    "aCarry",
    "aWandererA",
    "aWandererB",
    "aWandererC",
    "aWandererD",
    "aWandererE",
    "aWandererF",
    "aWandererG",
    "aWandererH",
    "aWandererI",
    "aWandererJ",
    "aWandererK",
};

bool IsExternalArxStateVariableName(const std::string &pName) {
    for (const char *aName : kExternalArxStateVariables) {
        if (pName == aName) {
            return true;
        }
    }
    return false;
}

bool UsesArxCallKind(const std::vector<const ArxCallExport *> &pArxCalls,
                     const ArxCallKind pKind) {
    for (const ArxCallExport *aArxCall : pArxCalls) {
        if ((aArxCall != nullptr) && (aArxCall->mKind == pKind)) {
            return true;
        }
    }
    return false;
}

std::string SeedArxStateInitializerLine(const std::string &pName) {
    return "std::uint64_t " + pName + " = " + UInt64Literal(Random::Get64High()) + ";";
}

void AppendSeedArxStateInitializerLines(std::vector<std::string> *pDeclaredNames,
                                        std::ostringstream *pStream) {
    if ((pDeclaredNames == nullptr) || (pStream == nullptr)) {
        return;
    }

    const std::array<const char *, 3> aCoreNames = {
        "aPrevious",
        "aIngress",
        "aCarry",
    };
    bool aWroteCore = false;
    for (const char *aName : aCoreNames) {
        if (ContainsText(*pDeclaredNames, std::string(aName))) {
            continue;
        }
        *pStream << "    " << SeedArxStateInitializerLine(aName) << '\n';
        AppendUniqueValue(pDeclaredNames, std::string(aName));
        aWroteCore = true;
    }

    bool aHasWandererToWrite = false;
    for (const char *aName : kExternalArxStateVariables) {
        if (LetterIndexFromSuffix(aName, "aWanderer") < 0) {
            continue;
        }
        if (!ContainsText(*pDeclaredNames, std::string(aName))) {
            aHasWandererToWrite = true;
            break;
        }
    }
    if (aWroteCore && aHasWandererToWrite) {
        *pStream << '\n';
    }

    for (const char *aName : kExternalArxStateVariables) {
        if (LetterIndexFromSuffix(aName, "aWanderer") < 0) {
            continue;
        }
        if (ContainsText(*pDeclaredNames, std::string(aName))) {
            continue;
        }
        *pStream << "    " << SeedArxStateInitializerLine(aName) << '\n';
        AppendUniqueValue(pDeclaredNames, std::string(aName));
    }
}

void AppendExternalArxStateVariables(std::vector<std::string> *pScalarVariables) {
    if (pScalarVariables == nullptr) {
        return;
    }

    for (const char *aName : kExternalArxStateVariables) {
        AppendUniqueValue(pScalarVariables, std::string(aName));
    }
}

void AppendArxCall(const ArxCallExport &pArxCall,
                   std::ostringstream *pStream) {
    if (pStream == nullptr) {
        return;
    }

    *pStream
    << "    //\n"
    << "    // ---------------------------------------------------\n"
    << "    // " << pArxCall.mTitle << ":\n"
    << "    // ---------------------------------------------------\n"
    << "    // read from: " << pArxCall.mReadFrom << "\n";
    if (!pArxCall.mTempStorage.empty()) {
        *pStream << "    // temp storage: " << pArxCall.mTempStorage << "\n";
    }
    *pStream
    << "    // ---------------------------------------------------\n"
    << "    // write to: " << pArxCall.mWriteTo << "\n"
    << "    // ---------------------------------------------------\n"
    << "    //\n";
    if ((pArxCall.mKind == ArxCallKind::kSeed) ||
        (pArxCall.mKind == ArxCallKind::kTwist) ||
        (pArxCall.mKind == ArxCallKind::kGrow)) {
        *pStream
        << "    " << pArxCall.mClassName << "::" << pArxCall.mMethodName << "(pWorkSpace,\n";
        if (pArxCall.mUsesNonce) {
            *pStream << "                 pNonce,\n";
        }
        if (pArxCall.mKind == ArxCallKind::kTwist) {
            *pStream << "                 pSource,\n";
        }
        *pStream
        << "                 &aPrevious,\n"
        << "                 &aIngress,\n"
        << "                 &aCarry,\n"
        << "                 &aWandererA,\n"
        << "                 &aWandererB,\n"
        << "                 &aWandererC,\n"
        << "                 &aWandererD,\n"
        << "                 &aWandererE,\n"
        << "                 &aWandererF,\n"
        << "                 &aWandererG,\n"
        << "                 &aWandererH,\n"
        << "                 &aWandererI,\n"
        << "                 &aWandererJ,\n"
        << "                 &aWandererK);\n"
        << "\n";
        return;
    }

    *pStream
    << "    " << pArxCall.mClassName << "::" << pArxCall.mMethodName << "(pWorkSpace,\n"
    << "                 pNonce,\n"
    << "                 pConstants,\n"
    << "                 pDomainSaltSet,\n";
    if (pArxCall.mUsesSnow) {
        *pStream << "                 pSnow,\n";
    }
    *pStream
    << "                 &aPrevious,\n"
    << "                 &aIngress,\n"
    << "                 &aCarry,\n"
    << "                 &aWandererA,\n"
    << "                 &aWandererB,\n"
    << "                 &aWandererC,\n"
    << "                 &aWandererD,\n"
    << "                 &aWandererE,\n"
    << "                 &aWandererF,\n"
    << "                 &aWandererG,\n"
    << "                 &aWandererH,\n"
    << "                 &aWandererI,\n"
    << "                 &aWandererJ,\n"
    << "                 &aWandererK);\n"
    << "\n";
}

void AppendSnapShotStart(const std::string &pFunctionName,
                         const char *pGuardExpression,
                         std::ostringstream *pStream) {
    if ((pStream == nullptr) || pFunctionName.empty()) {
        return;
    }

    if ((pGuardExpression != nullptr) && (pGuardExpression[0] != '\0')) {
        *pStream << "    if (" << pGuardExpression << ") {\n"
                 << "        SnapShotter::" << pFunctionName << "(pWorkSpace, this);\n"
                 << "    }\n"
                 << "\n";
        return;
    }

    *pStream << "    SnapShotter::" << pFunctionName << "(pWorkSpace, this);\n"
             << "\n";
}

void AppendSnapShotUpdate(const std::string &pFunctionName,
                          const char *pGuardExpression,
                          const std::string &pName,
                          std::ostringstream *pStream) {
    if ((pStream == nullptr) || pFunctionName.empty() || pName.empty()) {
        return;
    }

    if ((pGuardExpression != nullptr) && (pGuardExpression[0] != '\0')) {
        *pStream << "    if (" << pGuardExpression << ") {\n"
                 << "        SnapShotter::" << pFunctionName << "(pWorkSpace, this, \"" << pName << "\");\n"
                 << "    }\n"
                 << "\n";
        return;
    }

    *pStream << "    SnapShotter::" << pFunctionName << "(pWorkSpace, this, \"" << pName << "\");\n"
             << "\n";
}

void AppendSeedSnapShotScratchZero(std::ostringstream *pStream) {
    if (pStream == nullptr) {
        return;
    }

    *pStream
    << "    std::memset(pWorkSpace->mOperationLaneA, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mOperationLaneB, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mOperationLaneC, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mOperationLaneD, 0, S_BLOCK);\n"
    << "\n"
    << "    std::memset(pWorkSpace->mWorkLaneA, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mWorkLaneB, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mWorkLaneC, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mWorkLaneD, 0, S_BLOCK);\n"
    << "\n"
    << "    std::memset(pWorkSpace->mExpansionLaneA, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mExpansionLaneB, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mExpansionLaneC, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mExpansionLaneD, 0, S_BLOCK);\n"
    << "\n"
    << "    std::memset(pWorkSpace->mFireLaneA, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mFireLaneB, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mFireLaneC, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mFireLaneD, 0, S_BLOCK);\n"
    << "\n"
    << "    std::memset(pWorkSpace->mSnowLaneA, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mSnowLaneB, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mSnowLaneC, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mSnowLaneD, 0, S_BLOCK);\n"
    << "\n";
}

void AppendSeedSnapShotInvestZero(std::ostringstream *pStream) {
    if (pStream == nullptr) {
        return;
    }

    *pStream
    << "    std::memset(pWorkSpace->mInvestLaneA, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mInvestLaneB, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mInvestLaneC, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mInvestLaneD, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mInvestLaneE, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mInvestLaneF, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mInvestLaneG, 0, S_BLOCK);\n"
    << "    std::memset(pWorkSpace->mInvestLaneH, 0, S_BLOCK);\n"
    << "\n";
}

std::string SnapShotDiffuseName(const std::string &pPrefix,
                                const std::size_t pIndex) {
    if (pPrefix.empty()) {
        return "";
    }
    if (((pPrefix == "KDF_A_DIFFUSE") ||
         (pPrefix == "KDF_B_DIFFUSE") ||
         (pPrefix == "TWIST_DIFFUSE")) &&
        (pIndex == 0U)) {
        return pPrefix;
    }
    const char aSuffix = static_cast<char>('A' + static_cast<int>(pIndex % 26U));
    return pPrefix + "_" + std::string(1U, aSuffix);
}

bool AppendBranchBody(const TwistProgramBranch &pBranch,
                      const bool pIncludeKDFParameterAliases,
                      std::ostringstream *pStream,
                      std::string *pError,
                      const ArxCallExport *pArxCallA = nullptr,
                      const ArxCallExport *pArxCallB = nullptr,
                      const ArxCallExport *pArxCallC = nullptr,
                      const ArxCallExport *pArxCallD = nullptr,
                      const ArxCallExport *pArxCallE = nullptr,
                      const ArxCallExport *pArxCallF = nullptr,
                      const ArxCallExport *pArxCallG = nullptr,
                      const char *pSnapShotUpdateFunction = nullptr,
                      const char *pSnapShotGuardExpression = nullptr,
                      const char *pDiffuseSnapShotPrefix = nullptr,
                      const bool pSnapShotSeedCrunch = false) {
    if (pStream == nullptr) {
        SetError(pError, "Branch output stream was null.");
        return false;
    }

    std::vector<const ArxCallExport *> aArxCalls;
    if (pArxCallA != nullptr) {
        aArxCalls.push_back(pArxCallA);
    }
    if (pArxCallB != nullptr) {
        aArxCalls.push_back(pArxCallB);
    }
    if (pArxCallC != nullptr) {
        aArxCalls.push_back(pArxCallC);
    }
    if (pArxCallD != nullptr) {
        aArxCalls.push_back(pArxCallD);
    }
    if (pArxCallE != nullptr) {
        aArxCalls.push_back(pArxCallE);
    }
    if (pArxCallF != nullptr) {
        aArxCalls.push_back(pArxCallF);
    }
    if (pArxCallG != nullptr) {
        aArxCalls.push_back(pArxCallG);
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
    std::vector<TwistWorkSpaceSlot> aReferencedSlots;
    for (const ParsedBatch &aParsed : aParsedBatches) {
        if (!aParsed.mValid) {
            continue;
        }
        const GBatch &aBatch = aParsed.mBatch;
        if (IsExternalArxBatch(aArxCalls, aBatch)) {
            continue;
        }
        for (const GLoop &aLoop : aBatch.mLoops) {
            if (!aLoop.mLoopVariableName.empty()) {
                AppendUniqueValue(&aLoopVariables, aLoop.mLoopVariableName);
            }
        }
        for (const std::string &aName : aBatch.CollectVariableNames()) {
            AppendUniqueValue(&aScalarVariables, aName);
        }
        for (TwistWorkSpaceSlot aSlot : aBatch.CollectReferencedSlots()) {
            AppendUniqueValue(&aReferencedSlots, aSlot);
        }
    }
    const std::vector<std::string> aReferencedScalarVariables = aScalarVariables;
    if (!aArxCalls.empty()) {
        AppendExternalArxStateVariables(&aScalarVariables);
    }

    const std::vector<TwistWorkSpaceSlot> aAllSlots = FixedWorkspaceSlotOrder();
    for (const std::string &aLine : pBranch.GetStringLines()) {
        for (TwistWorkSpaceSlot aSlot : aAllSlots) {
            const std::string aAliasName = BufAliasName(aSlot);
            if (!aAliasName.empty() && (aLine.find(aAliasName) != std::string::npos)) {
                AppendUniqueValue(&aReferencedSlots, aSlot);
            }
        }
    }

    const std::vector<std::string> aWorkspaceDomainWords =
        CollectReferencedWorkspaceDomainWords(aScalarVariables,
                                              pBranch.GetStringLines(),
                                              aDeclaredNames);

    aScalarVariables.erase(
        std::remove_if(aScalarVariables.begin(),
                       aScalarVariables.end(),
                       [&aLoopVariables, &aDeclaredNames](const std::string &pName) {
                           return ContainsText(aLoopVariables, pName) ||
                                  ContainsText(aDeclaredNames, pName) ||
                                  WorkspaceDomainWordAliasInfo(pName, nullptr, nullptr);
                       }),
        aScalarVariables.end());
    const bool aUsesSeedArxState = UsesArxCallKind(aArxCalls, ArxCallKind::kSeed);
    if (aUsesSeedArxState) {
        aScalarVariables.erase(
            std::remove_if(aScalarVariables.begin(),
                           aScalarVariables.end(),
                           [](const std::string &pName) {
                               return IsExternalArxStateVariableName(pName);
                           }),
            aScalarVariables.end());
    }
    SortScalarDeclarationNames(&aScalarVariables);

    bool aWroteDeclaration = false;
    for (TwistWorkSpaceSlot aSlot : aAllSlots) {
        if (std::find(aReferencedSlots.begin(), aReferencedSlots.end(), aSlot) == aReferencedSlots.end()) {
            continue;
        }
        if (IsImplicitPointerWorkspaceSlot(aSlot)) {
            continue;
        }
        if (pIncludeKDFParameterAliases &&
            ((aSlot == TwistWorkSpaceSlot::kParamDestination) || IsKDFExcludedWorkspaceSlot(aSlot))) {
            continue;
        }
        if (pIncludeKDFParameterAliases && DecodePhaseSaltWorkspaceSlot(aSlot, nullptr, nullptr, nullptr)) {
            continue;
        }
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

    for (const std::string &aDomainWordName : aWorkspaceDomainWords) {
        const std::string aDeclaration = WorkspaceDomainWordDeclaration(aDomainWordName);
        if (aDeclaration.empty()) {
            continue;
        }
        *pStream << "    " << aDeclaration << '\n';
        AppendUniqueValue(&aDeclaredNames, aDomainWordName);
        aWroteDeclaration = true;
    }

    if (aUsesSeedArxState) {
        AppendSeedArxStateInitializerLines(&aDeclaredNames, pStream);
        aWroteDeclaration = true;
    }

    if (!aScalarVariables.empty()) {
        AppendScalarDeclarationLines(aScalarVariables, "    ", pStream);
        aWroteDeclaration = true;
    }

    if (aWroteDeclaration) {
        *pStream << '\n';
    }

    std::vector<bool> aConsumedArxCalls(aArxCalls.size(), false);
    auto FindNextArxCallForBatch = [&](const std::string &pBatchName) -> const ArxCallExport * {
        for (std::size_t aIndex = 0U; aIndex < aArxCalls.size(); ++aIndex) {
            const ArxCallExport *aArxCall = aArxCalls[aIndex];
            if ((aArxCall == nullptr) || aConsumedArxCalls[aIndex]) {
                continue;
            }
            if (aArxCall->mBatchName == pBatchName) {
                aConsumedArxCalls[aIndex] = true;
                return aArxCall;
            }
        }
        return nullptr;
    };

    auto AppendLineByIndex = [&](const std::size_t pIndex) -> bool {
        if (pIndex >= pBranch.GetStringLines().size()) {
            SetError(pError, "Branch line step index was out of range during export.");
            return false;
        }
        const std::string aLine = NormalizeLegacyByteTypeLine(pBranch.GetStringLines()[pIndex]);
        if (ShouldSkipExternalArxLine(aArxCalls, aLine)) {
            return true;
        }
        if (ShouldSkipUnusedExternalArxDeclarationLine(aArxCalls, aReferencedScalarVariables, aLine)) {
            return true;
        }
        if (pSnapShotSeedCrunch && (TrimText(aLine) == "SquashInvestToKeyBoxes();")) {
            AppendSeedSnapShotScratchZero(pStream);
            AppendSnapShotStart("SnapStart_SEED", nullptr, pStream);
            *pStream << IndentBlock(aLine, 1) << '\n'
                     << "\n";
            AppendSnapShotUpdate("SnapUpdate_SEED", nullptr, "INVEST_KEY_BOX", pStream);
            AppendSeedSnapShotInvestZero(pStream);
            AppendSnapShotUpdate("SnapUpdate_SEED", nullptr, "ZERO_INVEST", pStream);
            return true;
        }
        *pStream << IndentBlock(aLine, 1) << '\n';
        return true;
    };

    std::size_t aDiffuseBatchCount = 0U;
    std::size_t aDiffuseSnapShotIndex = 0U;
    auto AppendBatchByIndex = [&](const std::size_t pIndex) -> bool {
        if (pIndex >= aParsedBatches.size()) {
            SetError(pError, "Branch batch step index was out of range during export.");
            return false;
        }
        const ParsedBatch &aParsed = aParsedBatches[pIndex];
        if (!aParsed.mValid) {
            *pStream << "    // export warning: skipped batch #" << aParsed.mIndex
                     << " (" << SanitizeSingleLineComment(aParsed.mError) << ")\n";
            return true;
        }

        if (const ArxCallExport *aArxCall = FindNextArxCallForBatch(aParsed.mBatch.mName)) {
            AppendArxCall(*aArxCall, pStream);
            if (pSnapShotUpdateFunction != nullptr) {
                AppendSnapShotUpdate(pSnapShotUpdateFunction,
                                     pSnapShotGuardExpression,
                                     aArxCall->mMethodName,
                                     pStream);
            }
            return true;
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
            return true;
        }

        *pStream << IndentBlock(aScopeBlock, 1) << '\n';
        if ((pSnapShotUpdateFunction != nullptr) &&
            (aScopeBlock.find("TwistDiffuse::") != std::string::npos)) {
            ++aDiffuseBatchCount;
            if ((aDiffuseBatchCount % 2U) == 0U) {
                AppendSnapShotUpdate(pSnapShotUpdateFunction,
                                     pSnapShotGuardExpression,
                                     SnapShotDiffuseName((pDiffuseSnapShotPrefix == nullptr) ? "" : pDiffuseSnapShotPrefix,
                                                         aDiffuseSnapShotIndex++),
                                     pStream);
            }
        }
        return true;
    };

    const std::vector<TwistProgramBranchStep> &aSteps = pBranch.GetSteps();
    if (aSteps.empty()) {
        for (std::size_t aLineIndex = 0U; aLineIndex < pBranch.GetStringLines().size(); ++aLineIndex) {
            if (!AppendLineByIndex(aLineIndex)) {
                return false;
            }
        }
        if (!pBranch.GetStringLines().empty()) {
            *pStream << '\n';
        }

        for (std::size_t aBatchIndex = 0U; aBatchIndex < aParsedBatches.size(); ++aBatchIndex) {
            if (!AppendBatchByIndex(aBatchIndex)) {
                return false;
            }
        }
        return true;
    }

    for (const TwistProgramBranchStep &aStep : aSteps) {
        if (aStep.mType == TwistProgramBranchStepType::kLine) {
            if (!AppendLineByIndex(aStep.mIndex)) {
                return false;
            }
            continue;
        }
        if (aStep.mType == TwistProgramBranchStepType::kBatch) {
            if (!AppendBatchByIndex(aStep.mIndex)) {
                return false;
            }
            continue;
        }
        SetError(pError, "Branch step type was invalid during export.");
        return false;
    }

    return true;
}

std::vector<TwistWorkSpaceSlot> ParamOrbiterAssignSalts() {
    using Slot = TwistWorkSpaceSlot;
    return {
        Slot::kParamDomainSaltOrbiterAssignA,
        Slot::kParamDomainSaltOrbiterAssignB,
        Slot::kParamDomainSaltOrbiterAssignC,
        Slot::kParamDomainSaltOrbiterAssignD,
        Slot::kParamDomainSaltOrbiterAssignE,
        Slot::kParamDomainSaltOrbiterAssignF,
    };
}

std::vector<TwistWorkSpaceSlot> ParamOrbiterUpdateSalts() {
    using Slot = TwistWorkSpaceSlot;
    return {
        Slot::kParamDomainSaltOrbiterUpdateA,
        Slot::kParamDomainSaltOrbiterUpdateB,
        Slot::kParamDomainSaltOrbiterUpdateC,
        Slot::kParamDomainSaltOrbiterUpdateD,
        Slot::kParamDomainSaltOrbiterUpdateE,
        Slot::kParamDomainSaltOrbiterUpdateF,
    };
}

std::vector<TwistWorkSpaceSlot> ParamWandererUpdateSalts() {
    using Slot = TwistWorkSpaceSlot;
    return {
        Slot::kParamDomainSaltWandererUpdateA,
        Slot::kParamDomainSaltWandererUpdateB,
        Slot::kParamDomainSaltWandererUpdateC,
        Slot::kParamDomainSaltWandererUpdateD,
        Slot::kParamDomainSaltWandererUpdateE,
        Slot::kParamDomainSaltWandererUpdateF,
    };
}

std::vector<GSeedRunStageSliceSpec> ExportStarterKeySourceWideSlices() {
    using Slot = TwistWorkSpaceSlot;
    return {
        {{Slot::kKeyRowReadA, Slot::kKeyRowReadB},
         {Slot::kKeyRowReadA, Slot::kSource},
         Slot::kWorkLaneA,
         false},

        {{Slot::kWorkLaneA, Slot::kKeyRowReadA},
         {Slot::kKeyRowReadB, Slot::kSource},
         Slot::kWorkLaneB,
         true},

        {{Slot::kWorkLaneB, Slot::kKeyRowReadB},
         {Slot::kKeyRowReadA, Slot::kSource, Slot::kWorkLaneA},
         Slot::kInvestA,
         false},

        {{Slot::kInvestA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneA},
         {Slot::kKeyRowReadA, Slot::kWorkLaneB},
         Slot::kInvestB,
         true},

        {{Slot::kInvestB, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneB},
         {Slot::kWorkLaneA, Slot::kInvestA},
         Slot::kFireLaneA,
         false},

        {{Slot::kFireLaneA, Slot::kInvestA},
         {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneB, Slot::kWorkLaneA},
         Slot::kFireLaneB,
         true},

        {{Slot::kFireLaneB, Slot::kKeyRowReadA, Slot::kSource, Slot::kWorkLaneA},
         {Slot::kKeyRowReadB, Slot::kInvestB, Slot::kFireLaneA},
         Slot::kFireLaneC,
         false},

        {{Slot::kFireLaneC, Slot::kSource, Slot::kFireLaneA, Slot::kWorkLaneA},
         {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kFireLaneB, Slot::kWorkLaneB},
         Slot::kFireLaneD,
         true},

        {{Slot::kFireLaneD, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kFireLaneC},
         {Slot::kSource, Slot::kFireLaneA, Slot::kInvestA, Slot::kInvestB},
         Slot::kExpansionLaneA,
         false},

        {{Slot::kExpansionLaneA, Slot::kKeyRowReadA, Slot::kFireLaneD, Slot::kFireLaneB},
         {Slot::kKeyRowReadB, Slot::kSource, Slot::kFireLaneC, Slot::kInvestB},
         Slot::kExpansionLaneB,
         true},

        {{Slot::kExpansionLaneB, Slot::kFireLaneD, Slot::kKeyRowReadB, Slot::kFireLaneC},
         {Slot::kKeyRowReadA, Slot::kSource, Slot::kExpansionLaneA, Slot::kFireLaneB},
         Slot::kExpansionLaneC,
         false},

        {{Slot::kExpansionLaneC, Slot::kKeyRowReadA},
         {Slot::kFireLaneD, Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kKeyRowReadB},
         Slot::kExpansionLaneD,
         true},
    };
}

std::vector<GSeedRunStageSliceSpec> ExportFourPassSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                         const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                         const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    std::vector<TwistWorkSpaceSlot> aResiduals = pResiduals;
    Random::Shuffle(&aResiduals);

    return {
        {{pPrimary[0], pPrimary[1], aResiduals[0]},
         {pPrimary[2], pPrimary[3], aResiduals[1]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], pPrimary[3], aResiduals[2]},
         {pPrimary[0], pPrimary[1], aResiduals[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[0], pPrimary[1], aResiduals[4]},
         {pDestinations[0], pPrimary[2], aResiduals[5]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], pPrimary[3], aResiduals[6]},
         {pDestinations[1], pPrimary[1], aResiduals[7]},
         pDestinations[3],
         true},
    };
}

std::vector<GSeedRunStageSliceSpec> ExportFourPassNoResidualSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                                   const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    return {
        {{pPrimary[0], pPrimary[1]},
         {pPrimary[2], pPrimary[3]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[1], pPrimary[2]},
         {pPrimary[0], pPrimary[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[3], pPrimary[0]},
         {pDestinations[0], pPrimary[1], pPrimary[2]},
         pDestinations[2],
         false},

        {{pDestinations[2], pPrimary[2], pDestinations[0]},
         {pDestinations[1], pPrimary[3], pPrimary[0]},
         pDestinations[3],
         true},
    };
}

std::vector<GSeedRunStageSliceSpec> ExportFourPassFourResidualSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                                     const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                                     const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    std::vector<TwistWorkSpaceSlot> aResiduals = pResiduals;
    Random::Shuffle(&aResiduals);

    return {
        {{pPrimary[0], pPrimary[1], aResiduals[0]},
         {pPrimary[2], pPrimary[3]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], aResiduals[1]},
         {pPrimary[0], pPrimary[3], pPrimary[1]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[3], aResiduals[2]},
         {pDestinations[0], pPrimary[1], pPrimary[2]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], aResiduals[3]},
         {pDestinations[1], pPrimary[2], pPrimary[3], pPrimary[0]},
         pDestinations[3],
         true},
    };
}

std::vector<GSeedRunStageSliceSpec> ExportFourPassEightResidualSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                                      const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                                      const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    std::vector<TwistWorkSpaceSlot> aResiduals = pResiduals;
    Random::Shuffle(&aResiduals);

    return {
        {{pPrimary[0], pPrimary[1], aResiduals[0]},
         {pPrimary[2], pPrimary[3], aResiduals[1]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], aResiduals[2]},
         {pPrimary[0], pPrimary[3], aResiduals[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[3], aResiduals[4]},
         {pDestinations[0], pPrimary[1], aResiduals[5]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], aResiduals[6]},
         {pDestinations[1], pPrimary[2], aResiduals[7]},
         pDestinations[3],
         true},
    };
}

std::vector<GSeedRunStageSliceSpec> ExportSixPassSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                        const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                        const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    std::vector<TwistWorkSpaceSlot> aResiduals = pResiduals;
    Random::Shuffle(&aResiduals);

    return {
        {{pPrimary[0], pPrimary[1], aResiduals[0]},
         {pPrimary[2], pPrimary[3], aResiduals[1]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], pPrimary[3], aResiduals[2]},
         {pPrimary[0], pPrimary[1], aResiduals[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[0], aResiduals[4]},
         {pDestinations[0], pPrimary[2]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], aResiduals[5]},
         {pDestinations[1], pPrimary[3]},
         pDestinations[3],
         true},

        {{pDestinations[3], pDestinations[1], aResiduals[6]},
         {pDestinations[2], pDestinations[0]},
         pDestinations[4],
         false},

        {{pDestinations[4], pDestinations[2], aResiduals[7]},
         {pDestinations[3], pPrimary[1]},
         pDestinations[5],
         true},
    };
}

std::vector<GSeedRunStageSliceSpec> ExportSixPassRecentResidualSlices(const std::vector<TwistWorkSpaceSlot> &pPrimary,
                                                                      const std::vector<TwistWorkSpaceSlot> &pResiduals,
                                                                      const std::vector<TwistWorkSpaceSlot> &pDestinations) {
    std::vector<TwistWorkSpaceSlot> aResiduals = pResiduals;
    Random::Shuffle(&aResiduals);

    return {
        {{pPrimary[0], pPrimary[1], aResiduals[0]},
         {pPrimary[2], pPrimary[3]},
         pDestinations[0],
         false},

        {{pDestinations[0], pPrimary[2], aResiduals[1]},
         {pPrimary[0], pPrimary[3]},
         pDestinations[1],
         true},

        {{pDestinations[1], pPrimary[3], aResiduals[2]},
         {pDestinations[0], pPrimary[1], pPrimary[0]},
         pDestinations[2],
         false},

        {{pDestinations[2], pDestinations[0], aResiduals[3]},
         {pDestinations[1], pPrimary[3], pPrimary[2]},
         pDestinations[3],
         true},

        {{pDestinations[3], pDestinations[2], pPrimary[1]},
         {pPrimary[2], pDestinations[0], pDestinations[1]},
         pDestinations[4],
         false},

        {{pDestinations[4], pPrimary[0], pPrimary[1]},
         {pDestinations[3], pDestinations[2], pDestinations[1]},
         pDestinations[5],
         true},
    };
}

GSeedRunStageConfig MakeExportArxKDF_A_AConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "KDF_A_A";
    aConfig.mBatchName = "kdf_a_loop_a";
    aConfig.mStartLine = "// KDF_A_A kdf_a_loop_a (start)";
    aConfig.mEndLine = "// KDF_A_A kdf_a_loop_a (end)";
    aConfig.mFormat = GAXSFormat::kN11;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mWarmupDestinationCount = 2;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    aConfig.mSlices = {
        {{Slot::kSource, Slot::kParamSnow},
         {Slot::kParamSnow, Slot::kSource},
         Slot::kWorkLaneA,
         false},

        {{Slot::kWorkLaneA, Slot::kSource},
         {Slot::kWorkLaneA, Slot::kParamSnow},
         Slot::kWorkLaneB,
         true},

        {{Slot::kWorkLaneB, Slot::kSource},
         {Slot::kParamSnow, Slot::kWorkLaneA},
         Slot::kFireLaneA,
         false},

        {{Slot::kFireLaneA, Slot::kWorkLaneA},
         {Slot::kSource, Slot::kParamSnow, Slot::kWorkLaneB},
         Slot::kFireLaneB,
         true},

        {{Slot::kFireLaneB, Slot::kSource, Slot::kParamSnow, Slot::kWorkLaneA},
         {Slot::kFireLaneA, Slot::kWorkLaneB},
         Slot::kFireLaneC,
         false},

        {{Slot::kFireLaneC, Slot::kParamSnow, Slot::kFireLaneA},
         {Slot::kFireLaneB, Slot::kSource, Slot::kWorkLaneB},
         Slot::kFireLaneD,
         true},
    };
    return aConfig;
}

GSeedRunStageConfig MakeExportArxKDF_A_BConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "KDF_A_B";
    aConfig.mBatchName = "kdf_a_loop_b";
    aConfig.mStartLine = "// KDF_A_B kdf_a_loop_b (start)";
    aConfig.mEndLine = "// KDF_A_B kdf_a_loop_b (end)";
    aConfig.mFormat = GAXSFormat::kN9;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    aConfig.mSlices = ExportFourPassNoResidualSlices({Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                                     {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxKDF_A_CConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "KDF_A_C";
    aConfig.mBatchName = "kdf_a_loop_c";
    aConfig.mStartLine = "// KDF_A_C kdf_a_loop_c (start)";
    aConfig.mEndLine = "// KDF_A_C kdf_a_loop_c (end)";
    aConfig.mFormat = GAXSFormat::kN5;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    aConfig.mSlices = ExportFourPassFourResidualSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                                       {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                                       {Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxKDF_A_DConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "KDF_A_D";
    aConfig.mBatchName = "kdf_a_loop_d";
    aConfig.mStartLine = "// KDF_A_D kdf_a_loop_d (start)";
    aConfig.mEndLine = "// KDF_A_D kdf_a_loop_d (end)";
    aConfig.mFormat = GAXSFormat::kN7;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    aConfig.mSlices = ExportFourPassEightResidualSlices({Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                                       {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                                        Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                                       {Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxKDF_B_AConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "KDF_B_A";
    aConfig.mBatchName = "kdf_b_loop_a";
    aConfig.mStartLine = "// KDF_B_A kdf_b_loop_a (start)";
    aConfig.mEndLine = "// KDF_B_A kdf_b_loop_a (end)";
    aConfig.mFormat = GAXSFormat::kN7;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    aConfig.mSlices = ExportFourPassEightResidualSlices({Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
                                                        {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD,
                                                         Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                                        {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    return aConfig;
}

GSeedRunStageConfig MakeExportArxKDF_B_BConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "KDF_B_B";
    aConfig.mBatchName = "kdf_b_loop_b";
    aConfig.mStartLine = "// KDF_B_B kdf_b_loop_b (start)";
    aConfig.mEndLine = "// KDF_B_B kdf_b_loop_b (end)";
    aConfig.mFormat = GAXSFormat::kN11;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    aConfig.mSlices = ExportFourPassEightResidualSlices({Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                                        {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                                         Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
                                                        {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxKDF_B_CConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "KDF_B_C";
    aConfig.mBatchName = "kdf_b_loop_c";
    aConfig.mStartLine = "// KDF_B_C kdf_b_loop_c (start)";
    aConfig.mEndLine = "// KDF_B_C kdf_b_loop_c (end)";
    aConfig.mFormat = GAXSFormat::kN9;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    aConfig.mSlices = ExportFourPassEightResidualSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                                        {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                                         Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
                                                        {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxKDF_B_DConfig() {
    using Slot = TwistWorkSpaceSlot;
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "KDF_B_D";
    aConfig.mBatchName = "kdf_b_loop_d";
    aConfig.mStartLine = "// KDF_B_D kdf_b_loop_d (start)";
    aConfig.mEndLine = "// KDF_B_D kdf_b_loop_d (end)";
    aConfig.mFormat = GAXSFormat::kN7;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kInvalid;
    aConfig.mIsNonKDF = false;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ParamOrbiterAssignSalts();
    aConfig.mSaltsOrbiterUpdate = ParamOrbiterUpdateSalts();
    aConfig.mSaltsWandererUpdate = ParamWandererUpdateSalts();
    aConfig.mSlices = ExportFourPassEightResidualSlices({Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD},
                                                        {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                                         Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                                        {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

int ExportArxPhaseIndex(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB: return 1;
        case TwistDomain::kPhaseC: return 2;
        case TwistDomain::kPhaseD: return 3;
        case TwistDomain::kPhaseE: return 4;
        case TwistDomain::kPhaseF: return 5;
        case TwistDomain::kPhaseG: return 6;
        case TwistDomain::kPhaseH: return 7;
        case TwistDomain::kPhaseA:
        default:
            return 0;
    }
}

std::string ExportArxSeedLoopName(const TwistDomain pDomain) {
    std::string aResult = "seed_loop_";
    aResult.push_back(static_cast<char>('a' + ExportArxPhaseIndex(pDomain)));
    return aResult;
}

std::vector<TwistWorkSpaceSlot> ExportArxPhaseSalts(const TwistDomain pDomain,
                                                    const TwistWorkSpaceSlot pBaseSlot,
                                                    const int pLaneCount) {
    const int aBase = static_cast<int>(pBaseSlot);
    const int aOffset = ExportArxPhaseIndex(pDomain) * 18;

    std::vector<TwistWorkSpaceSlot> aResult;
    aResult.reserve(static_cast<std::size_t>(pLaneCount));
    for (int i = 0; i < pLaneCount; ++i) {
        aResult.push_back(static_cast<TwistWorkSpaceSlot>(aBase + aOffset + i));
    }
    return aResult;
}

GSeedRunStageConfig MakeExportArxSeedBaseConfig(const std::string &pStageName,
                                                const TwistDomain pDomain,
                                                const bool pUseNonces,
                                                const GAXSFormat pFormat) {
    using Slot = TwistWorkSpaceSlot;

    const std::string aLoopName = ExportArxSeedLoopName(pDomain);
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = aLoopName;
    aConfig.mStartLine = "// " + pStageName + " " + aLoopName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + aLoopName + " (end)";
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = !pUseNonces;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = pDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ExportArxPhaseSalts(pDomain, Slot::kPhaseASaltOrbiterAssignA, 6);
    aConfig.mSaltsOrbiterUpdate = ExportArxPhaseSalts(pDomain, Slot::kPhaseASaltOrbiterUpdateA, 6);
    aConfig.mSaltsWandererUpdate = ExportArxPhaseSalts(pDomain, Slot::kPhaseASaltWandererUpdateA, 6);
    return aConfig;
}

GSeedRunStageConfig MakeExportArxSeed_AConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = MakeExportArxSeedBaseConfig("GSeedRunSeed_A",
                                                              TwistDomain::kPhaseA,
                                                              true,
                                                              GAXSFormat::kN7);
    aConfig.mMaxContextSourceCount = 5;
    aConfig.mMaxBoundSourceCount = 10;
    aConfig.mWarmupDestinationCount = 4;
    aConfig.mBindDuplicateSourceSlots = true;
    aConfig.mSliceDomains = {
        TwistDomain::kPhaseE, TwistDomain::kPhaseE, TwistDomain::kPhaseE,
        TwistDomain::kPhaseF, TwistDomain::kPhaseF, TwistDomain::kPhaseF,
        TwistDomain::kPhaseG, TwistDomain::kPhaseG, TwistDomain::kPhaseG,
        TwistDomain::kPhaseH, TwistDomain::kPhaseH, TwistDomain::kPhaseH,
    };
    aConfig.mSlices = {
        {{Slot::kKeyRowReadA, Slot::kKeyRowReadB},
         {Slot::kKeyRowReadA, Slot::kSource},
         Slot::kWorkLaneA,
         false},

        {{Slot::kWorkLaneA, Slot::kKeyRowReadA},
         {Slot::kKeyRowReadB, Slot::kSource},
         Slot::kWorkLaneB,
         true},

        {{Slot::kWorkLaneB, Slot::kKeyRowReadB},
         {Slot::kKeyRowReadA, Slot::kSource, Slot::kWorkLaneA},
         Slot::kWorkLaneC,
         false},

        {{Slot::kWorkLaneC, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneA},
         {Slot::kKeyRowReadA, Slot::kWorkLaneB},
         Slot::kWorkLaneD,
         true},

        {{Slot::kWorkLaneD, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneB},
         {Slot::kWorkLaneA, Slot::kWorkLaneC},
         Slot::kFireLaneA,
         false},

        {{Slot::kFireLaneA, Slot::kWorkLaneC},
         {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kSource, Slot::kWorkLaneB, Slot::kWorkLaneA},
         Slot::kFireLaneB,
         true},

        {{Slot::kFireLaneB, Slot::kKeyRowReadA, Slot::kSource, Slot::kWorkLaneA},
         {Slot::kKeyRowReadB, Slot::kWorkLaneD, Slot::kFireLaneA},
         Slot::kFireLaneC,
         false},

        {{Slot::kFireLaneC, Slot::kSource, Slot::kFireLaneA, Slot::kWorkLaneA},
         {Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kFireLaneB, Slot::kWorkLaneB},
         Slot::kFireLaneD,
         true},

        {{Slot::kFireLaneD, Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kFireLaneC},
         {Slot::kSource, Slot::kFireLaneA, Slot::kWorkLaneC, Slot::kWorkLaneD},
         Slot::kExpansionLaneA,
         false},

        {{Slot::kExpansionLaneA, Slot::kKeyRowReadA, Slot::kFireLaneD, Slot::kFireLaneB},
         {Slot::kKeyRowReadB, Slot::kSource, Slot::kFireLaneC, Slot::kWorkLaneD},
         Slot::kExpansionLaneB,
         true},

        {{Slot::kExpansionLaneB, Slot::kFireLaneD, Slot::kKeyRowReadB, Slot::kFireLaneC},
         {Slot::kKeyRowReadA, Slot::kSource, Slot::kExpansionLaneA, Slot::kFireLaneB},
         Slot::kExpansionLaneC,
         false},

        {{Slot::kExpansionLaneC, Slot::kKeyRowReadA},
         {Slot::kFireLaneD, Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kKeyRowReadB},
         Slot::kExpansionLaneD,
         true},
    };
    aConfig.mExpectedSkeletonCount = 12;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxSeed_BConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = MakeExportArxSeedBaseConfig("GSeedRunSeed_B",
                                                              TwistDomain::kPhaseA,
                                                              true,
                                                              GAXSFormat::kN5);
    aConfig.mSlices = ExportSixPassRecentResidualSlices({Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                                        {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                                        {Slot::kInvestA, Slot::kInvestB,
                                                         Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxSeed_CConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = MakeExportArxSeedBaseConfig("GSeedRunSeed_C",
                                                              TwistDomain::kPhaseB,
                                                              true,
                                                              GAXSFormat::kN9);
    aConfig.mSlices = ExportSixPassSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                          {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
                                           Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                          {Slot::kInvestC, Slot::kInvestD,
                                           Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxSeed_DConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = MakeExportArxSeedBaseConfig("GSeedRunSeed_D",
                                                              TwistDomain::kPhaseD,
                                                              true,
                                                              GAXSFormat::kN7);
    aConfig.mSlices = {
        {{Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kInvestA},
         {Slot::kExpansionLaneC, Slot::kExpansionLaneD, Slot::kInvestB},
         Slot::kSnowLaneA,
         false},

        {{Slot::kSnowLaneA, Slot::kExpansionLaneC, Slot::kExpansionLaneD, Slot::kInvestC},
         {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kInvestD},
         Slot::kSnowLaneB,
         true},

        {{Slot::kSnowLaneB, Slot::kExpansionLaneA, Slot::kFireLaneA},
         {Slot::kSnowLaneA, Slot::kExpansionLaneC},
         Slot::kInvestA,
         false},

        {{Slot::kInvestA, Slot::kSnowLaneA, Slot::kFireLaneB},
         {Slot::kSnowLaneB, Slot::kExpansionLaneD},
         Slot::kInvestB,
         true},

        {{Slot::kInvestB, Slot::kSnowLaneB, Slot::kFireLaneC},
         {Slot::kInvestA, Slot::kSnowLaneA},
         Slot::kInvestC,
         false},

        {{Slot::kInvestC, Slot::kInvestA, Slot::kFireLaneD},
         {Slot::kInvestB, Slot::kExpansionLaneB},
         Slot::kInvestD,
         true},
    };
    aConfig.mExpectedSkeletonCount = 6;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxSeed_EConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = MakeExportArxSeedBaseConfig("GSeedRunSeed_E",
                                                              TwistDomain::kPhaseE,
                                                              true,
                                                              GAXSFormat::kN11);
    aConfig.mSlices = {
        {{Slot::kInvestA, Slot::kInvestB, Slot::kFireLaneA},
         {Slot::kInvestC, Slot::kInvestD, Slot::kFireLaneB},
         Slot::kFireLaneA,
         false},

        {{Slot::kFireLaneA, Slot::kInvestC, Slot::kInvestD, Slot::kWorkLaneA},
         {Slot::kInvestA, Slot::kInvestB, Slot::kWorkLaneB},
         Slot::kFireLaneB,
         true},

        {{Slot::kFireLaneB, Slot::kInvestA, Slot::kWorkLaneC},
         {Slot::kFireLaneA, Slot::kInvestC},
         Slot::kOperationLaneA,
         false},

        {{Slot::kOperationLaneA, Slot::kFireLaneA, Slot::kWorkLaneD},
         {Slot::kFireLaneB, Slot::kInvestD},
         Slot::kOperationLaneB,
         true},

        {{Slot::kOperationLaneB, Slot::kFireLaneB, Slot::kFireLaneC},
         {Slot::kOperationLaneA, Slot::kFireLaneA, Slot::kInvestA},
         Slot::kOperationLaneC,
         false},

        {{Slot::kOperationLaneC, Slot::kOperationLaneA, Slot::kFireLaneD},
         {Slot::kOperationLaneB, Slot::kInvestB},
         Slot::kOperationLaneD,
         true},
    };
    aConfig.mExpectedSkeletonCount = 6;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxSeed_FConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = MakeExportArxSeedBaseConfig("GSeedRunSeed_F",
                                                              TwistDomain::kPhaseF,
                                                              true,
                                                              GAXSFormat::kN9);
    aConfig.mSlices = ExportSixPassSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                          {Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD,
                                           Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD},
                                          {Slot::kSnowLaneC, Slot::kSnowLaneD,
                                           Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxSeed_GConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = MakeExportArxSeedBaseConfig("GSeedRunSeed_G",
                                                              TwistDomain::kPhaseH,
                                                              true,
                                                              GAXSFormat::kN7);
    aConfig.mSlices = ExportSixPassSlices({Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kSnowLaneC, Slot::kSnowLaneD},
                                          {Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD,
                                           Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                          {Slot::kWorkLaneA, Slot::kWorkLaneB,
                                           Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxTwist_AConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "GTwistRunTwist_A";
    aConfig.mBatchName = "twist_loop_a";
    aConfig.mStartLine = "// GTwistRunTwist_A twist_loop_a (start)";
    aConfig.mEndLine = "// GTwistRunTwist_A twist_loop_a (end)";
    aConfig.mFormat = GAXSFormat::kN9;
    aConfig.mIgnoreNonces = true;
    aConfig.mHasDomainMix = false;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kPhaseD;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 12;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mMaxContextSourceCount = 5;
    aConfig.mMaxBoundSourceCount = 10;
    aConfig.mWarmupDestinationCount = 4;
    aConfig.mBindDuplicateSourceSlots = true;
    aConfig.mSliceDomains = {
        TwistDomain::kPhaseA, TwistDomain::kPhaseA, TwistDomain::kPhaseA,
        TwistDomain::kPhaseB, TwistDomain::kPhaseB, TwistDomain::kPhaseB,
        TwistDomain::kPhaseC, TwistDomain::kPhaseC, TwistDomain::kPhaseC,
        TwistDomain::kPhaseD, TwistDomain::kPhaseD, TwistDomain::kPhaseD,
    };
    aConfig.mSaltsOrbiterAssign = ExportArxPhaseSalts(TwistDomain::kPhaseD,
                                                       Slot::kPhaseASaltOrbiterAssignA,
                                                       6);
    aConfig.mSaltsOrbiterUpdate = ExportArxPhaseSalts(TwistDomain::kPhaseD,
                                                      Slot::kPhaseASaltOrbiterUpdateA,
                                                      6);
    aConfig.mSaltsWandererUpdate = ExportArxPhaseSalts(TwistDomain::kPhaseD,
                                                        Slot::kPhaseASaltWandererUpdateA,
                                                        6);
    aConfig.mSlices = ExportStarterKeySourceWideSlices();
    aConfig.mExpectedSkeletonCount = 12;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxTwist_BConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "GTwistRunTwist_B";
    aConfig.mBatchName = "twist_loop_b";
    aConfig.mStartLine = "// GTwistRunTwist_B twist_loop_b (start)";
    aConfig.mEndLine = "// GTwistRunTwist_B twist_loop_b (end)";
    aConfig.mFormat = GAXSFormat::kN7;
    aConfig.mIgnoreNonces = true;
    aConfig.mHasDomainMix = false;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kPhaseE;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ExportArxPhaseSalts(TwistDomain::kPhaseE,
                                                       Slot::kPhaseASaltOrbiterAssignA,
                                                       6);
    aConfig.mSaltsOrbiterUpdate = ExportArxPhaseSalts(TwistDomain::kPhaseE,
                                                      Slot::kPhaseASaltOrbiterUpdateA,
                                                      6);
    aConfig.mSaltsWandererUpdate = ExportArxPhaseSalts(TwistDomain::kPhaseE,
                                                        Slot::kPhaseASaltWandererUpdateA,
                                                        6);
    aConfig.mSlices = ExportSixPassRecentResidualSlices({Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                                        {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD},
                                                        {Slot::kInvestC, Slot::kInvestD,
                                                         Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxTwist_CConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "GTwistRunTwist_C";
    aConfig.mBatchName = "twist_loop_c";
    aConfig.mStartLine = "// GTwistRunTwist_C twist_loop_c (start)";
    aConfig.mEndLine = "// GTwistRunTwist_C twist_loop_c (end)";
    aConfig.mFormat = GAXSFormat::kN11;
    aConfig.mIgnoreNonces = true;
    aConfig.mHasDomainMix = false;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = TwistDomain::kPhaseF;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ExportArxPhaseSalts(TwistDomain::kPhaseF,
                                                       Slot::kPhaseASaltOrbiterAssignA,
                                                       6);
    aConfig.mSaltsOrbiterUpdate = ExportArxPhaseSalts(TwistDomain::kPhaseF,
                                                      Slot::kPhaseASaltOrbiterUpdateA,
                                                      6);
    aConfig.mSaltsWandererUpdate = ExportArxPhaseSalts(TwistDomain::kPhaseF,
                                                        Slot::kPhaseASaltWandererUpdateA,
                                                        6);
    aConfig.mSlices = ExportSixPassSlices({Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD},
                                          {Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD,
                                           Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD},
                                          {Slot::kSnowLaneA, Slot::kSnowLaneB,
                                           Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD});
    aConfig.mExpectedSkeletonCount = 6;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxGrowBaseConfig(const std::string &pStageName,
                                                const std::string &pLoopName,
                                                const TwistDomain pDomain) {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pLoopName;
    aConfig.mStartLine = "// " + pStageName + " " + pLoopName + " (start)";
    aConfig.mEndLine = "// " + pStageName + " " + pLoopName + " (end)";
    aConfig.mFormat = GAXSFormat::kN5;
    aConfig.mIgnoreNonces = true;
    aConfig.mHasDomainMix = false;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = pDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mLoopCeiling = S_BLOCK;
    aConfig.mLoopEndText = "S_BLOCK";
    aConfig.mHotPackCount = 12;
    aConfig.mSaltsOrbiterAssign = ExportArxPhaseSalts(pDomain,
                                                       Slot::kPhaseASaltOrbiterAssignA,
                                                       6);
    aConfig.mSaltsOrbiterUpdate = ExportArxPhaseSalts(pDomain,
                                                       Slot::kPhaseASaltOrbiterUpdateA,
                                                       6);
    aConfig.mSaltsWandererUpdate = ExportArxPhaseSalts(pDomain,
                                                        Slot::kPhaseASaltWandererUpdateA,
                                                        6);
    aConfig.mEmitGroupLaneFlowComments = false;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxGrow_AConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = MakeExportArxGrowBaseConfig("GROW_A",
                                                              "grow_key_a",
                                                              TwistDomain::kPhaseG);
    aConfig.mSlices = {
        {{Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kInvestA},
         {Slot::kWorkLaneC, Slot::kWorkLaneD, Slot::kOperationLaneA},
         Slot::kExpansionLaneA,
         false},

        {{Slot::kExpansionLaneA, Slot::kWorkLaneC, Slot::kInvestB},
         {Slot::kWorkLaneA, Slot::kWorkLaneD, Slot::kOperationLaneB},
         Slot::kExpansionLaneB,
         true},

        {{Slot::kExpansionLaneB, Slot::kWorkLaneD, Slot::kInvestC},
         {Slot::kExpansionLaneA, Slot::kWorkLaneB, Slot::kOperationLaneC},
         Slot::kExpansionLaneC,
         false},

        {{Slot::kExpansionLaneC, Slot::kExpansionLaneA, Slot::kInvestD},
         {Slot::kExpansionLaneB, Slot::kWorkLaneA, Slot::kOperationLaneD},
         Slot::kExpansionLaneD,
         true},
    };
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

GSeedRunStageConfig MakeExportArxGrow_BConfig() {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = MakeExportArxGrowBaseConfig("GROW_B",
                                                              "grow_key_b",
                                                              TwistDomain::kPhaseH);
    aConfig.mSlices = {
        {{Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kInvestA},
         {Slot::kExpansionLaneC, Slot::kExpansionLaneD, Slot::kOperationLaneA},
         Slot::kWorkLaneA,
         false},

        {{Slot::kWorkLaneA, Slot::kExpansionLaneC, Slot::kInvestB},
         {Slot::kExpansionLaneA, Slot::kExpansionLaneD, Slot::kOperationLaneB},
         Slot::kWorkLaneB,
         true},

        {{Slot::kWorkLaneB, Slot::kExpansionLaneD, Slot::kInvestC},
         {Slot::kWorkLaneA, Slot::kExpansionLaneB, Slot::kOperationLaneC},
         Slot::kWorkLaneC,
         false},

        {{Slot::kWorkLaneC, Slot::kWorkLaneA, Slot::kInvestD},
         {Slot::kWorkLaneB, Slot::kExpansionLaneC, Slot::kOperationLaneD},
         Slot::kWorkLaneD,
         true},
    };
    aConfig.mExpectedSkeletonCount = 4;
    return aConfig;
}

void AddExportArxKDFPrologue(TwistProgramBranch *pBranch,
                             const bool pUsesSnow) {
    if (pBranch == nullptr) {
        return;
    }

    static const std::array<const char *, 16> kNonceVariableNames = {
        "aNonceWordA",
        "aNonceWordB",
        "aNonceWordC",
        "aNonceWordD",
        "aNonceWordE",
        "aNonceWordF",
        "aNonceWordG",
        "aNonceWordH",
        "aNonceWordI",
        "aNonceWordJ",
        "aNonceWordK",
        "aNonceWordL",
        "aNonceWordM",
        "aNonceWordN",
        "aNonceWordO",
        "aNonceWordP",
    };

    pBranch->AddLine("// [kdf-a arx]");
    for (std::size_t i = 0U; i < kNonceVariableNames.size(); ++i) {
        pBranch->AddLine(NonceDeclareLine(GSymbol::Var(kNonceVariableNames[i]), static_cast<int>(i)));
    }
    pBranch->AddLine("std::uint64_t aDomainWordIngress = pConstants->mIngress;");
    pBranch->AddLine("std::uint64_t aDomainWordScatter = pConstants->mScatter;");
    pBranch->AddLine("std::uint64_t aDomainWordCross = pConstants->mCross;");
    pBranch->AddLine("[[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;");
    pBranch->AddLine("std::uint64_t aPrevious = *pPrevious;");
    pBranch->AddLine("std::uint64_t aIngress = *pIngress;");
    pBranch->AddLine("std::uint64_t aCarry = *pCarry;");
    pBranch->AddLine("std::uint64_t aWandererA = *pWandererA;");
    pBranch->AddLine("std::uint64_t aWandererB = *pWandererB;");
    pBranch->AddLine("std::uint64_t aWandererC = *pWandererC;");
    pBranch->AddLine("std::uint64_t aWandererD = *pWandererD;");
    pBranch->AddLine("std::uint64_t aWandererE = *pWandererE;");
    pBranch->AddLine("std::uint64_t aWandererF = *pWandererF;");
    pBranch->AddLine("std::uint64_t aWandererG = *pWandererG;");
    pBranch->AddLine("std::uint64_t aWandererH = *pWandererH;");
    pBranch->AddLine("std::uint64_t aWandererI = *pWandererI;");
    pBranch->AddLine("std::uint64_t aWandererJ = *pWandererJ;");
    pBranch->AddLine("std::uint64_t aWandererK = *pWandererK;");
}

void AddExportArxKDF_A_AEpilogue(TwistProgramBranch *pBranch) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("*pPrevious = aPrevious;");
    pBranch->AddLine("*pIngress = aIngress;");
    pBranch->AddLine("*pCarry = aCarry;");
    pBranch->AddLine("*pWandererA = aWandererA;");
    pBranch->AddLine("*pWandererB = aWandererB;");
    pBranch->AddLine("*pWandererC = aWandererC;");
    pBranch->AddLine("*pWandererD = aWandererD;");
    pBranch->AddLine("*pWandererE = aWandererE;");
    pBranch->AddLine("*pWandererF = aWandererF;");
    pBranch->AddLine("*pWandererG = aWandererG;");
    pBranch->AddLine("*pWandererH = aWandererH;");
    pBranch->AddLine("*pWandererI = aWandererI;");
    pBranch->AddLine("*pWandererJ = aWandererJ;");
    pBranch->AddLine("*pWandererK = aWandererK;");
}

void AddExportArxSeedNonceLines(TwistProgramBranch *pBranch) {
    if (pBranch == nullptr) {
        return;
    }

    static const std::array<const char *, 16> kNonceVariableNames = {
        "aNonceWordA",
        "aNonceWordB",
        "aNonceWordC",
        "aNonceWordD",
        "aNonceWordE",
        "aNonceWordF",
        "aNonceWordG",
        "aNonceWordH",
        "aNonceWordI",
        "aNonceWordJ",
        "aNonceWordK",
        "aNonceWordL",
        "aNonceWordM",
        "aNonceWordN",
        "aNonceWordO",
        "aNonceWordP",
    };

    for (std::size_t i = 0U; i < kNonceVariableNames.size(); ++i) {
        pBranch->AddLine(NonceDeclareLine(GSymbol::Var(kNonceVariableNames[i]), static_cast<int>(i)));
    }
}

void AddExportArxSeedPrologue(TwistProgramBranch *pBranch) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("// [seed arx]");
    pBranch->AddLine("[[maybe_unused]] std::uint8_t *mSource = pWorkSpace->mSource;");
    pBranch->AddLine("std::uint64_t aPrevious = *pPrevious;");
    pBranch->AddLine("std::uint64_t aIngress = *pIngress;");
    pBranch->AddLine("std::uint64_t aCarry = *pCarry;");
    pBranch->AddLine("std::uint64_t aWandererA = *pWandererA;");
    pBranch->AddLine("std::uint64_t aWandererB = *pWandererB;");
    pBranch->AddLine("std::uint64_t aWandererC = *pWandererC;");
    pBranch->AddLine("std::uint64_t aWandererD = *pWandererD;");
    pBranch->AddLine("std::uint64_t aWandererE = *pWandererE;");
    pBranch->AddLine("std::uint64_t aWandererF = *pWandererF;");
    pBranch->AddLine("std::uint64_t aWandererG = *pWandererG;");
    pBranch->AddLine("std::uint64_t aWandererH = *pWandererH;");
    pBranch->AddLine("std::uint64_t aWandererI = *pWandererI;");
    pBranch->AddLine("std::uint64_t aWandererJ = *pWandererJ;");
    pBranch->AddLine("std::uint64_t aWandererK = *pWandererK;");
}

void AddExportArxSeedEpilogue(TwistProgramBranch *pBranch) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("*pPrevious = aPrevious;");
    pBranch->AddLine("*pIngress = aIngress;");
    pBranch->AddLine("*pCarry = aCarry;");
    pBranch->AddLine("*pWandererA = aWandererA;");
    pBranch->AddLine("*pWandererB = aWandererB;");
    pBranch->AddLine("*pWandererC = aWandererC;");
    pBranch->AddLine("*pWandererD = aWandererD;");
    pBranch->AddLine("*pWandererE = aWandererE;");
    pBranch->AddLine("*pWandererF = aWandererF;");
    pBranch->AddLine("*pWandererG = aWandererG;");
    pBranch->AddLine("*pWandererH = aWandererH;");
    pBranch->AddLine("*pWandererI = aWandererI;");
    pBranch->AddLine("*pWandererJ = aWandererJ;");
    pBranch->AddLine("*pWandererK = aWandererK;");
}

void AddExportArxTwistPrologue(TwistProgramBranch *pBranch) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("// [twist arx]");
    pBranch->AddLine("[[maybe_unused]] std::uint8_t *mSource = pSource;");
    pBranch->AddLine("std::uint64_t aPrevious = *pPrevious;");
    pBranch->AddLine("std::uint64_t aIngress = *pIngress;");
    pBranch->AddLine("std::uint64_t aCarry = *pCarry;");
    pBranch->AddLine("std::uint64_t aWandererA = *pWandererA;");
    pBranch->AddLine("std::uint64_t aWandererB = *pWandererB;");
    pBranch->AddLine("std::uint64_t aWandererC = *pWandererC;");
    pBranch->AddLine("std::uint64_t aWandererD = *pWandererD;");
    pBranch->AddLine("std::uint64_t aWandererE = *pWandererE;");
    pBranch->AddLine("std::uint64_t aWandererF = *pWandererF;");
    pBranch->AddLine("std::uint64_t aWandererG = *pWandererG;");
    pBranch->AddLine("std::uint64_t aWandererH = *pWandererH;");
    pBranch->AddLine("std::uint64_t aWandererI = *pWandererI;");
    pBranch->AddLine("std::uint64_t aWandererJ = *pWandererJ;");
    pBranch->AddLine("std::uint64_t aWandererK = *pWandererK;");
}

void AddExportArxGrowPrologue(TwistProgramBranch *pBranch) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("// [grow arx]");
    pBranch->AddLine("std::uint64_t aPrevious = *pPrevious;");
    pBranch->AddLine("std::uint64_t aIngress = *pIngress;");
    pBranch->AddLine("std::uint64_t aCarry = *pCarry;");
    pBranch->AddLine("std::uint64_t aWandererA = *pWandererA;");
    pBranch->AddLine("std::uint64_t aWandererB = *pWandererB;");
    pBranch->AddLine("std::uint64_t aWandererC = *pWandererC;");
    pBranch->AddLine("std::uint64_t aWandererD = *pWandererD;");
    pBranch->AddLine("std::uint64_t aWandererE = *pWandererE;");
    pBranch->AddLine("std::uint64_t aWandererF = *pWandererF;");
    pBranch->AddLine("std::uint64_t aWandererG = *pWandererG;");
    pBranch->AddLine("std::uint64_t aWandererH = *pWandererH;");
    pBranch->AddLine("std::uint64_t aWandererI = *pWandererI;");
    pBranch->AddLine("std::uint64_t aWandererJ = *pWandererJ;");
    pBranch->AddLine("std::uint64_t aWandererK = *pWandererK;");
}

bool BuildExportArxKDFBranch(TwistProgramBranch *pBranch,
                             const GSeedRunStageConfig &pConfig,
                             const std::string &pStageName,
                             const bool pUsesSnow,
                             std::string *pError) {
    if (pBranch == nullptr) {
        SetError(pError, "ARX branch output was null.");
        return false;
    }

    pBranch->Clear();
    AddExportArxKDFPrologue(pBranch, pUsesSnow);

    GSeedRunStage aStage(pConfig);
    if (!aStage.Plan(pError)) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Failed to plan exported ARX " + pStageName + ".";
        }
        return false;
    }
    if (!aStage.Build(*pBranch, pError)) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Failed to build exported ARX " + pStageName + ".";
        }
        return false;
    }

    AddExportArxKDF_A_AEpilogue(pBranch);
    return true;
}

bool BuildExportArxSeedBranch(TwistProgramBranch *pBranch,
                              const GSeedRunStageConfig &pConfig,
                              const std::string &pStageName,
                              std::string *pError) {
    if (pBranch == nullptr) {
        SetError(pError, "Seed ARX branch output was null.");
        return false;
    }

    pBranch->Clear();
    AddExportArxSeedPrologue(pBranch);
    if (!pConfig.mIgnoreNonces) {
        AddExportArxSeedNonceLines(pBranch);
    }

    GSeedRunStage aStage(pConfig);
    if (!aStage.Plan(pError)) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Failed to plan exported ARX " + pStageName + ".";
        }
        return false;
    }
    if (!aStage.Build(*pBranch, pError)) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Failed to build exported ARX " + pStageName + ".";
        }
        return false;
    }

    AddExportArxSeedEpilogue(pBranch);
    return true;
}

bool BuildExportArxTwistBranch(TwistProgramBranch *pBranch,
                               const GSeedRunStageConfig &pConfig,
                               const std::string &pStageName,
                               std::string *pError) {
    if (pBranch == nullptr) {
        SetError(pError, "Twist ARX branch output was null.");
        return false;
    }

    pBranch->Clear();
    AddExportArxTwistPrologue(pBranch);

    GSeedRunStage aStage(pConfig);
    if (!aStage.Plan(pError)) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Failed to plan exported ARX " + pStageName + ".";
        }
        return false;
    }
    if (!aStage.Build(*pBranch, pError)) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Failed to build exported ARX " + pStageName + ".";
        }
        return false;
    }

    AddExportArxSeedEpilogue(pBranch);
    return true;
}

bool BuildExportArxGrowBranch(TwistProgramBranch *pBranch,
                              const GSeedRunStageConfig &pConfig,
                              const std::string &pStageName,
                              std::string *pError) {
    if (pBranch == nullptr) {
        SetError(pError, "Grow ARX branch output was null.");
        return false;
    }

    pBranch->Clear();
    AddExportArxGrowPrologue(pBranch);

    GSeedRunStage aStage(pConfig);
    if (!aStage.Plan(pError)) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Failed to plan exported ARX " + pStageName + ".";
        }
        return false;
    }
    if (!aStage.Build(*pBranch, pError)) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Failed to build exported ARX " + pStageName + ".";
        }
        return false;
    }

    AddExportArxSeedEpilogue(pBranch);
    return true;
}

bool BuildExportArxKDF_A_ABranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxKDFBranch(pBranch,
                                   MakeExportArxKDF_A_AConfig(),
                                   "KDF_A_A",
                                   true,
                                   pError);
}

bool BuildExportArxKDF_A_BBranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxKDFBranch(pBranch,
                                   MakeExportArxKDF_A_BConfig(),
                                   "KDF_A_B",
                                   false,
                                   pError);
}

bool BuildExportArxKDF_A_CBranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxKDFBranch(pBranch,
                                   MakeExportArxKDF_A_CConfig(),
                                   "KDF_A_C",
                                   false,
                                   pError);
}

bool BuildExportArxKDF_A_DBranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxKDFBranch(pBranch,
                                   MakeExportArxKDF_A_DConfig(),
                                   "KDF_A_D",
                                   false,
                                   pError);
}

bool BuildExportArxKDF_B_ABranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxKDFBranch(pBranch,
                                   MakeExportArxKDF_B_AConfig(),
                                   "KDF_B_A",
                                   false,
                                   pError);
}

bool BuildExportArxKDF_B_BBranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxKDFBranch(pBranch,
                                   MakeExportArxKDF_B_BConfig(),
                                   "KDF_B_B",
                                   false,
                                   pError);
}

bool BuildExportArxKDF_B_CBranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxKDFBranch(pBranch,
                                   MakeExportArxKDF_B_CConfig(),
                                   "KDF_B_C",
                                   false,
                                   pError);
}

bool BuildExportArxKDF_B_DBranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxKDFBranch(pBranch,
                                   MakeExportArxKDF_B_DConfig(),
                                   "KDF_B_D",
                                   false,
                                   pError);
}

bool BuildExportArxSeed_ABranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxSeedBranch(pBranch,
                                    MakeExportArxSeed_AConfig(),
                                    "Seed_A",
                                    pError);
}

bool BuildExportArxSeed_BBranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxSeedBranch(pBranch,
                                    MakeExportArxSeed_BConfig(),
                                    "Seed_B",
                                    pError);
}

bool BuildExportArxSeed_CBranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxSeedBranch(pBranch,
                                    MakeExportArxSeed_CConfig(),
                                    "Seed_C",
                                    pError);
}

bool BuildExportArxSeed_DBranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxSeedBranch(pBranch,
                                    MakeExportArxSeed_DConfig(),
                                    "Seed_D",
                                    pError);
}

bool BuildExportArxSeed_EBranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxSeedBranch(pBranch,
                                    MakeExportArxSeed_EConfig(),
                                    "Seed_E",
                                    pError);
}

bool BuildExportArxSeed_FBranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxSeedBranch(pBranch,
                                    MakeExportArxSeed_FConfig(),
                                    "Seed_F",
                                    pError);
}

bool BuildExportArxSeed_GBranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxSeedBranch(pBranch,
                                    MakeExportArxSeed_GConfig(),
                                    "Seed_G",
                                    pError);
}

bool BuildExportArxTwist_ABranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxTwistBranch(pBranch,
                                     MakeExportArxTwist_AConfig(),
                                     "Twist_A",
                                     pError);
}

bool BuildExportArxTwist_BBranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxTwistBranch(pBranch,
                                     MakeExportArxTwist_BConfig(),
                                     "Twist_B",
                                     pError);
}

bool BuildExportArxTwist_CBranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxTwistBranch(pBranch,
                                     MakeExportArxTwist_CConfig(),
                                     "Twist_C",
                                     pError);
}

bool BuildExportArxGrow_ABranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxGrowBranch(pBranch,
                                    MakeExportArxGrow_AConfig(),
                                    "GROW_A",
                                    pError);
}

bool BuildExportArxGrow_BBranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxGrowBranch(pBranch,
                                    MakeExportArxGrow_BConfig(),
                                    "GROW_B",
                                    pError);
}

void AppendArxKDFSignature(std::ostringstream *pStream,
                           const std::string &pClassName,
                           const std::string &pMethodName,
                           const bool pDefinition,
                           const bool pUsesSnow) {
    if (pStream == nullptr) {
        return;
    }

    const std::string aPrefix = pDefinition ?
        ("void " + pClassName + "::") :
        "    static void ";
    const std::string aSuffix = pDefinition ? " {\n" : ";\n";
    *pStream
    << aPrefix << pMethodName << "(TwistWorkSpace *pWorkSpace,\n"
    << "                     std::uint64_t pNonce,\n"
    << "                     TwistDomainConstants *pConstants,\n"
    << "                     TwistDomainSaltSet *pDomainSaltSet,\n";
    if (pUsesSnow) {
        *pStream << "                     std::uint8_t *pSnow,\n";
    }
    *pStream
    << "                     std::uint64_t *pPrevious,\n"
    << "                     std::uint64_t *pIngress,\n"
    << "                     std::uint64_t *pCarry,\n"
    << "                     std::uint64_t *pWandererA,\n"
    << "                     std::uint64_t *pWandererB,\n"
    << "                     std::uint64_t *pWandererC,\n"
    << "                     std::uint64_t *pWandererD,\n"
    << "                     std::uint64_t *pWandererE,\n"
    << "                     std::uint64_t *pWandererF,\n"
    << "                     std::uint64_t *pWandererG,\n"
    << "                     std::uint64_t *pWandererH,\n"
    << "                     std::uint64_t *pWandererI,\n"
    << "                     std::uint64_t *pWandererJ,\n"
    << "                     std::uint64_t *pWandererK)" << aSuffix;
}

void AppendArxSeedSignature(std::ostringstream *pStream,
                            const std::string &pClassName,
                            const std::string &pMethodName,
                            const bool pDefinition,
                            const bool pUsesNonce = true) {
    if (pStream == nullptr) {
        return;
    }

    const std::string aPrefix = pDefinition ?
        ("void " + pClassName + "::") :
        "    static void ";
    const std::string aSuffix = pDefinition ? " {\n" : ";\n";
    *pStream
    << aPrefix << pMethodName << "(TwistWorkSpace *pWorkSpace,\n";
    if (pUsesNonce) {
        *pStream << "                     std::uint64_t pNonce,\n";
    }
    *pStream
    << "                     std::uint64_t *pPrevious,\n"
    << "                     std::uint64_t *pIngress,\n"
    << "                     std::uint64_t *pCarry,\n"
    << "                     std::uint64_t *pWandererA,\n"
    << "                     std::uint64_t *pWandererB,\n"
    << "                     std::uint64_t *pWandererC,\n"
    << "                     std::uint64_t *pWandererD,\n"
    << "                     std::uint64_t *pWandererE,\n"
    << "                     std::uint64_t *pWandererF,\n"
    << "                     std::uint64_t *pWandererG,\n"
    << "                     std::uint64_t *pWandererH,\n"
    << "                     std::uint64_t *pWandererI,\n"
    << "                     std::uint64_t *pWandererJ,\n"
    << "                     std::uint64_t *pWandererK)" << aSuffix;
}

void AppendArxTwistSignature(std::ostringstream *pStream,
                             const std::string &pClassName,
                             const std::string &pMethodName,
                             const bool pDefinition,
                             const bool pUsesNonce) {
    if (pStream == nullptr) {
        return;
    }

    const std::string aPrefix = pDefinition ?
        ("void " + pClassName + "::") :
        "    static void ";
    const std::string aSuffix = pDefinition ? " {\n" : ";\n";
    *pStream
    << aPrefix << pMethodName << "(TwistWorkSpace *pWorkSpace,\n";
    if (pUsesNonce) {
        *pStream << "                     std::uint64_t pNonce,\n";
    }
    *pStream
    << "                     std::uint8_t *pSource,\n"
    << "                     std::uint64_t *pPrevious,\n"
    << "                     std::uint64_t *pIngress,\n"
    << "                     std::uint64_t *pCarry,\n"
    << "                     std::uint64_t *pWandererA,\n"
    << "                     std::uint64_t *pWandererB,\n"
    << "                     std::uint64_t *pWandererC,\n"
    << "                     std::uint64_t *pWandererD,\n"
    << "                     std::uint64_t *pWandererE,\n"
    << "                     std::uint64_t *pWandererF,\n"
    << "                     std::uint64_t *pWandererG,\n"
    << "                     std::uint64_t *pWandererH,\n"
    << "                     std::uint64_t *pWandererI,\n"
    << "                     std::uint64_t *pWandererJ,\n"
    << "                     std::uint64_t *pWandererK)" << aSuffix;
}

void AppendArxGrowSignature(std::ostringstream *pStream,
                            const std::string &pClassName,
                            const std::string &pMethodName,
                            const bool pDefinition) {
    if (pStream == nullptr) {
        return;
    }

    const std::string aPrefix = pDefinition ?
        ("void " + pClassName + "::") :
        "    static void ";
    const std::string aSuffix = pDefinition ? " {\n" : ";\n";
    *pStream
    << aPrefix << pMethodName << "(TwistWorkSpace *pWorkSpace,\n"
    << "                     std::uint64_t *pPrevious,\n"
    << "                     std::uint64_t *pIngress,\n"
    << "                     std::uint64_t *pCarry,\n"
    << "                     std::uint64_t *pWandererA,\n"
    << "                     std::uint64_t *pWandererB,\n"
    << "                     std::uint64_t *pWandererC,\n"
    << "                     std::uint64_t *pWandererD,\n"
    << "                     std::uint64_t *pWandererE,\n"
    << "                     std::uint64_t *pWandererF,\n"
    << "                     std::uint64_t *pWandererG,\n"
    << "                     std::uint64_t *pWandererH,\n"
    << "                     std::uint64_t *pWandererI,\n"
    << "                     std::uint64_t *pWandererJ,\n"
    << "                     std::uint64_t *pWandererK)" << aSuffix;
}

bool ExportArxCompanionFiles(const std::string &pRoot,
                             const std::string &pClassName,
                             std::string *pError) {
    const std::string aArxClassName = pClassName + "_Arx";
    const std::string aHeaderPath = FileIO::Join(pRoot, aArxClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(pRoot, aArxClassName + ".cpp");

    TwistProgramBranch aBranchKDF_A_A;
    if (!BuildExportArxKDF_A_ABranch(&aBranchKDF_A_A, pError)) {
        return false;
    }
    TwistProgramBranch aBranchKDF_A_B;
    if (!BuildExportArxKDF_A_BBranch(&aBranchKDF_A_B, pError)) {
        return false;
    }
    TwistProgramBranch aBranchKDF_A_C;
    if (!BuildExportArxKDF_A_CBranch(&aBranchKDF_A_C, pError)) {
        return false;
    }
    TwistProgramBranch aBranchKDF_A_D;
    if (!BuildExportArxKDF_A_DBranch(&aBranchKDF_A_D, pError)) {
        return false;
    }
    TwistProgramBranch aBranchKDF_B_A;
    if (!BuildExportArxKDF_B_ABranch(&aBranchKDF_B_A, pError)) {
        return false;
    }
    TwistProgramBranch aBranchKDF_B_B;
    if (!BuildExportArxKDF_B_BBranch(&aBranchKDF_B_B, pError)) {
        return false;
    }
    TwistProgramBranch aBranchKDF_B_C;
    if (!BuildExportArxKDF_B_CBranch(&aBranchKDF_B_C, pError)) {
        return false;
    }
    TwistProgramBranch aBranchKDF_B_D;
    if (!BuildExportArxKDF_B_DBranch(&aBranchKDF_B_D, pError)) {
        return false;
    }
    TwistProgramBranch aBranchSeed_A;
    if (!BuildExportArxSeed_ABranch(&aBranchSeed_A, pError)) {
        return false;
    }
    TwistProgramBranch aBranchSeed_B;
    if (!BuildExportArxSeed_BBranch(&aBranchSeed_B, pError)) {
        return false;
    }
    TwistProgramBranch aBranchSeed_C;
    if (!BuildExportArxSeed_CBranch(&aBranchSeed_C, pError)) {
        return false;
    }
    TwistProgramBranch aBranchSeed_D;
    if (!BuildExportArxSeed_DBranch(&aBranchSeed_D, pError)) {
        return false;
    }
    TwistProgramBranch aBranchSeed_E;
    if (!BuildExportArxSeed_EBranch(&aBranchSeed_E, pError)) {
        return false;
    }
    TwistProgramBranch aBranchSeed_F;
    if (!BuildExportArxSeed_FBranch(&aBranchSeed_F, pError)) {
        return false;
    }
    TwistProgramBranch aBranchSeed_G;
    if (!BuildExportArxSeed_GBranch(&aBranchSeed_G, pError)) {
        return false;
    }
    TwistProgramBranch aBranchTwist_A;
    if (!BuildExportArxTwist_ABranch(&aBranchTwist_A, pError)) {
        return false;
    }
    TwistProgramBranch aBranchTwist_B;
    if (!BuildExportArxTwist_BBranch(&aBranchTwist_B, pError)) {
        return false;
    }
    TwistProgramBranch aBranchTwist_C;
    if (!BuildExportArxTwist_CBranch(&aBranchTwist_C, pError)) {
        return false;
    }
    TwistProgramBranch aBranchGrow_A;
    if (!BuildExportArxGrow_ABranch(&aBranchGrow_A, pError)) {
        return false;
    }
    TwistProgramBranch aBranchGrow_B;
    if (!BuildExportArxGrow_BBranch(&aBranchGrow_B, pError)) {
        return false;
    }

    std::ostringstream aHeader;
    aHeader << "#pragma once\n"
    << "\n"
    << "#include \"TwistExpander.hpp\"\n"
    << "\n"
    << "class " << aArxClassName << " {\n"
    << "public:\n";
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_A", false, true);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_B", false, false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_C", false, false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_D", false, false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_B_A", false, false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_B_B", false, false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_B_C", false, false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_B_D", false, false);
    AppendArxSeedSignature(&aHeader, aArxClassName, "Seed_A", false);
    AppendArxSeedSignature(&aHeader, aArxClassName, "Seed_B", false);
    AppendArxSeedSignature(&aHeader, aArxClassName, "Seed_C", false);
    AppendArxSeedSignature(&aHeader, aArxClassName, "Seed_D", false);
    AppendArxSeedSignature(&aHeader, aArxClassName, "Seed_E", false);
    AppendArxSeedSignature(&aHeader, aArxClassName, "Seed_F", false);
    AppendArxSeedSignature(&aHeader, aArxClassName, "Seed_G", false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_A", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_B", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_C", false, false);
    AppendArxGrowSignature(&aHeader, aArxClassName, "GROW_A", false);
    AppendArxGrowSignature(&aHeader, aArxClassName, "GROW_B", false);
    aHeader << "};\n";

    std::ostringstream aCpp;
    aCpp << "#include \"" << aArxClassName << ".hpp\"\n"
    << "#include \"TwistFunctional.hpp\"\n"
    << "#include \"TwistMix32.hpp\"\n"
    << "#include \"TwistMix64.hpp\"\n"
    << "\n"
    << "#include <cstdint>\n"
    << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_A", true, true);
    if (!AppendBranchBody(aBranchKDF_A_A, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n"
    << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_B", true, false);
    if (!AppendBranchBody(aBranchKDF_A_B, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_C", true, false);
    if (!AppendBranchBody(aBranchKDF_A_C, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_D", true, false);
    if (!AppendBranchBody(aBranchKDF_A_D, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_A", true, false);
    if (!AppendBranchBody(aBranchKDF_B_A, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_B", true, false);
    if (!AppendBranchBody(aBranchKDF_B_B, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_C", true, false);
    if (!AppendBranchBody(aBranchKDF_B_C, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_D", true, false);
    if (!AppendBranchBody(aBranchKDF_B_D, true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_A", true);
    if (!AppendBranchBody(aBranchSeed_A, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_B", true);
    if (!AppendBranchBody(aBranchSeed_B, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_C", true);
    if (!AppendBranchBody(aBranchSeed_C, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_D", true);
    if (!AppendBranchBody(aBranchSeed_D, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_E", true);
    if (!AppendBranchBody(aBranchSeed_E, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_F", true);
    if (!AppendBranchBody(aBranchSeed_F, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_G", true);
    if (!AppendBranchBody(aBranchSeed_G, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_A", true, false);
    if (!AppendBranchBody(aBranchTwist_A, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_B", true, false);
    if (!AppendBranchBody(aBranchTwist_B, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_C", true, false);
    if (!AppendBranchBody(aBranchTwist_C, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxGrowSignature(&aCpp, aArxClassName, "GROW_A", true);
    if (!AppendBranchBody(aBranchGrow_A, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxGrowSignature(&aCpp, aArxClassName, "GROW_B", true);
    if (!AppendBranchBody(aBranchGrow_B, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";

    if (!SaveTextFile(aHeaderPath, aHeader.str(), pError)) {
        return false;
    }
    if (!SaveTextFile(aCppPath, aCpp.str(), pError)) {
        return false;
    }
    return true;
}

class GArx {
public:
    bool Bake(const std::string &pRoot,
              const std::string &pClassName,
              std::string *pError) {
        mArxClassName = pClassName + "_Arx";
        mKDF_A_A.mBatchName = "kdf_a_loop_a";
        mKDF_A_A.mStartLine = "// GSeedRunKDF_A_A kdf_a_loop_a (start)";
        mKDF_A_A.mEndLine = "// GSeedRunKDF_A_A kdf_a_loop_a (end)";
        mKDF_A_A.mClassName = mArxClassName;
        mKDF_A_A.mUsesSnow = true;
        mKDF_A_A.mMethodName = "KDF_A_A";
        mKDF_A_A.mTitle = "KDF_A_A kdf_a_loop_a";
        mKDF_A_A.mReadFrom = "source, snow";
        mKDF_A_A.mTempStorage = "work_a, work_b";
        mKDF_A_A.mWriteTo = "work_a, work_b, fire_a, fire_b, fire_c, fire_d";

        mKDF_A_B.mBatchName = "kdf_a_loop_b";
        mKDF_A_B.mStartLine = "// GSeedRunKDF_A_B kdf_a_loop_b (start)";
        mKDF_A_B.mEndLine = "// GSeedRunKDF_A_B kdf_a_loop_b (end)";
        mKDF_A_B.mClassName = mArxClassName;
        mKDF_A_B.mMethodName = "KDF_A_B";
        mKDF_A_B.mTitle = "KDF_A_B kdf_a_loop_b";
        mKDF_A_B.mReadFrom = "fire_a, fire_b, fire_c, fire_d";
        mKDF_A_B.mWriteTo = "operation_a, operation_b, operation_c, operation_d";

        mKDF_A_C.mBatchName = "kdf_a_loop_c";
        mKDF_A_C.mStartLine = "// GSeedRunKDF_A_C kdf_a_loop_c (start)";
        mKDF_A_C.mEndLine = "// GSeedRunKDF_A_C kdf_a_loop_c (end)";
        mKDF_A_C.mClassName = mArxClassName;
        mKDF_A_C.mMethodName = "KDF_A_C";
        mKDF_A_C.mTitle = "KDF_A_C kdf_a_loop_c";
        mKDF_A_C.mReadFrom = "operation_a, operation_b, operation_c, operation_d";
        mKDF_A_C.mWriteTo = "work_a, work_b, work_c, work_d";

        mKDF_A_D.mBatchName = "kdf_a_loop_d";
        mKDF_A_D.mStartLine = "// GSeedRunKDF_A_D kdf_a_loop_d (start)";
        mKDF_A_D.mEndLine = "// GSeedRunKDF_A_D kdf_a_loop_d (end)";
        mKDF_A_D.mClassName = mArxClassName;
        mKDF_A_D.mMethodName = "KDF_A_D";
        mKDF_A_D.mTitle = "KDF_A_D kdf_a_loop_d";
        mKDF_A_D.mReadFrom = "expand_a, expand_b, expand_c, expand_d";
        mKDF_A_D.mWriteTo = "work_a, work_b, work_c, work_d";

        mKDF_B_A.mBatchName = "kdf_b_loop_a";
        mKDF_B_A.mStartLine = "// GSeedRunKDF_B_A kdf_b_loop_a (start)";
        mKDF_B_A.mEndLine = "// GSeedRunKDF_B_A kdf_b_loop_a (end)";
        mKDF_B_A.mClassName = mArxClassName;
        mKDF_B_A.mMethodName = "KDF_B_A";
        mKDF_B_A.mTitle = "KDF_B_A kdf_b_loop_a";
        mKDF_B_A.mReadFrom = "work_a, work_b, work_c, work_d";
        mKDF_B_A.mTempStorage = "operation_a, operation_b, operation_c, operation_d, fire_a, fire_b, fire_c, fire_d";
        mKDF_B_A.mWriteTo = "expand_a, expand_b, expand_c, expand_d";

        mKDF_B_B.mBatchName = "kdf_b_loop_b";
        mKDF_B_B.mStartLine = "// GSeedRunKDF_B_B kdf_b_loop_b (start)";
        mKDF_B_B.mEndLine = "// GSeedRunKDF_B_B kdf_b_loop_b (end)";
        mKDF_B_B.mClassName = mArxClassName;
        mKDF_B_B.mMethodName = "KDF_B_B";
        mKDF_B_B.mTitle = "KDF_B_B kdf_b_loop_b";
        mKDF_B_B.mReadFrom = "expand_a, expand_b, expand_c, expand_d";
        mKDF_B_B.mTempStorage = "fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d";
        mKDF_B_B.mWriteTo = "operation_a, operation_b, operation_c, operation_d";

        mKDF_B_C.mBatchName = "kdf_b_loop_c";
        mKDF_B_C.mStartLine = "// GSeedRunKDF_B_C kdf_b_loop_c (start)";
        mKDF_B_C.mEndLine = "// GSeedRunKDF_B_C kdf_b_loop_c (end)";
        mKDF_B_C.mClassName = mArxClassName;
        mKDF_B_C.mMethodName = "KDF_B_C";
        mKDF_B_C.mTitle = "KDF_B_C kdf_b_loop_c";
        mKDF_B_C.mReadFrom = "operation_a, operation_b, operation_c, operation_d";
        mKDF_B_C.mTempStorage = "fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d";
        mKDF_B_C.mWriteTo = "expand_a, expand_b, expand_c, expand_d";

        mKDF_B_D.mBatchName = "kdf_b_loop_d";
        mKDF_B_D.mStartLine = "// GSeedRunKDF_B_D kdf_b_loop_d (start)";
        mKDF_B_D.mEndLine = "// GSeedRunKDF_B_D kdf_b_loop_d (end)";
        mKDF_B_D.mClassName = mArxClassName;
        mKDF_B_D.mMethodName = "KDF_B_D";
        mKDF_B_D.mTitle = "KDF_B_D kdf_b_loop_d";
        mKDF_B_D.mReadFrom = "work_a, work_b, work_c, work_d";
        mKDF_B_D.mTempStorage = "fire_a, fire_b, fire_c, fire_d, operation_a, operation_b, operation_c, operation_d";
        mKDF_B_D.mWriteTo = "expand_a, expand_b, expand_c, expand_d";

        mSeed_A.mKind = ArxCallKind::kSeed;
        mSeed_A.mBatchName = "seed_loop_a";
        mSeed_A.mStartLine = "// GSeedRunSeed_A seed_loop_a (start)";
        mSeed_A.mEndLine = "// GSeedRunSeed_A seed_loop_a (end)";
        mSeed_A.mClassName = mArxClassName;
        mSeed_A.mMethodName = "Seed_A";
        mSeed_A.mTitle = "GSeedRunSeed_A seed_loop_a";
        mSeed_A.mReadFrom = "source, key_row_read_a, key_row_read_b";
        mSeed_A.mTempStorage = "work_a, work_b, work_c, work_d, fire_a, fire_b, fire_c, fire_d";
        mSeed_A.mWriteTo = "work_a, work_b, work_c, work_d, fire_a, fire_b, fire_c, fire_d, expand_a, expand_b, expand_c, expand_d";

        mSeed_B.mKind = ArxCallKind::kSeed;
        mSeed_B.mBatchName = "seed_loop_a";
        mSeed_B.mStartLine = "// GSeedRunSeed_B seed_loop_a (start)";
        mSeed_B.mEndLine = "// GSeedRunSeed_B seed_loop_a (end)";
        mSeed_B.mClassName = mArxClassName;
        mSeed_B.mMethodName = "Seed_B";
        mSeed_B.mTitle = "GSeedRunSeed_B seed_loop_a";
        mSeed_B.mReadFrom = "expand_a, expand_b, expand_c, expand_d";
        mSeed_B.mTempStorage = "fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d";
        mSeed_B.mWriteTo = "invest_a, invest_b, operation_a, operation_b, operation_c, operation_d";

        mSeed_C.mKind = ArxCallKind::kSeed;
        mSeed_C.mBatchName = "seed_loop_b";
        mSeed_C.mStartLine = "// GSeedRunSeed_C seed_loop_b (start)";
        mSeed_C.mEndLine = "// GSeedRunSeed_C seed_loop_b (end)";
        mSeed_C.mClassName = mArxClassName;
        mSeed_C.mMethodName = "Seed_C";
        mSeed_C.mTitle = "GSeedRunSeed_C seed_loop_b";
        mSeed_C.mReadFrom = "operation_a, operation_b, operation_c, operation_d";
        mSeed_C.mTempStorage = "fire_a, fire_b, fire_c, fire_d, expand_a, expand_b, expand_c, expand_d";
        mSeed_C.mWriteTo = "invest_c, invest_d, work_a, work_b, work_c, work_d";

        mSeed_D.mKind = ArxCallKind::kSeed;
        mSeed_D.mBatchName = "seed_loop_d";
        mSeed_D.mStartLine = "// GSeedRunSeed_D seed_loop_d (start)";
        mSeed_D.mEndLine = "// GSeedRunSeed_D seed_loop_d (end)";
        mSeed_D.mClassName = mArxClassName;
        mSeed_D.mMethodName = "Seed_D";
        mSeed_D.mTitle = "GSeedRunSeed_D seed_loop_d";
        mSeed_D.mReadFrom = "expand_a, expand_b, expand_c, expand_d";
        mSeed_D.mTempStorage = "fire_a, fire_b, fire_c, fire_d, invest_a, invest_b, invest_c, invest_d";
        mSeed_D.mWriteTo = "snow_a, snow_b, invest_a, invest_b, invest_c, invest_d";

        mSeed_E.mKind = ArxCallKind::kSeed;
        mSeed_E.mBatchName = "seed_loop_e";
        mSeed_E.mStartLine = "// GSeedRunSeed_E seed_loop_e (start)";
        mSeed_E.mEndLine = "// GSeedRunSeed_E seed_loop_e (end)";
        mSeed_E.mClassName = mArxClassName;
        mSeed_E.mMethodName = "Seed_E";
        mSeed_E.mTitle = "GSeedRunSeed_E seed_loop_e";
        mSeed_E.mReadFrom = "invest_a, invest_b, invest_c, invest_d";
        mSeed_E.mTempStorage = "fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d";
        mSeed_E.mWriteTo = "fire_a, fire_b, operation_a, operation_b, operation_c, operation_d";

        mSeed_F.mKind = ArxCallKind::kSeed;
        mSeed_F.mBatchName = "seed_loop_f";
        mSeed_F.mStartLine = "// GSeedRunSeed_F seed_loop_f (start)";
        mSeed_F.mEndLine = "// GSeedRunSeed_F seed_loop_f (end)";
        mSeed_F.mClassName = mArxClassName;
        mSeed_F.mMethodName = "Seed_F";
        mSeed_F.mTitle = "GSeedRunSeed_F seed_loop_f";
        mSeed_F.mReadFrom = "operation_a, operation_b, operation_c, operation_d";
        mSeed_F.mTempStorage = "snow_a, snow_b, work_c, work_d, invest_a, invest_b, invest_c, invest_d";
        mSeed_F.mWriteTo = "snow_c, snow_d, expand_a, expand_b, expand_c, expand_d";

        mSeed_G.mKind = ArxCallKind::kSeed;
        mSeed_G.mBatchName = "seed_loop_h";
        mSeed_G.mStartLine = "// GSeedRunSeed_G seed_loop_h (start)";
        mSeed_G.mEndLine = "// GSeedRunSeed_G seed_loop_h (end)";
        mSeed_G.mClassName = mArxClassName;
        mSeed_G.mMethodName = "Seed_G";
        mSeed_G.mTitle = "GSeedRunSeed_G seed_loop_h";
        mSeed_G.mReadFrom = "snow_a, snow_b, snow_c, snow_d";
        mSeed_G.mTempStorage = "invest_a, invest_b, invest_c, invest_d, fire_a, fire_b, fire_c, fire_d";
        mSeed_G.mWriteTo = "work_a, work_b, expand_a, expand_b, expand_c, expand_d";

        mTwist_A.mKind = ArxCallKind::kTwist;
        mTwist_A.mUsesNonce = false;
        mTwist_A.mBatchName = "twist_loop_a";
        mTwist_A.mStartLine = "// GTwistRunTwist_A twist_loop_a (start)";
        mTwist_A.mEndLine = "// GTwistRunTwist_A twist_loop_a (end)";
        mTwist_A.mClassName = mArxClassName;
        mTwist_A.mMethodName = "Twist_A";
        mTwist_A.mTitle = "GTwistRunTwist_A twist_loop_a";
        mTwist_A.mReadFrom = "source, key_row_read_a, key_row_read_b";
        mTwist_A.mTempStorage = "fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d";
        mTwist_A.mWriteTo = "fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d, expand_a, expand_b, expand_c, expand_d";

        mTwist_B.mKind = ArxCallKind::kTwist;
        mTwist_B.mUsesNonce = false;
        mTwist_B.mBatchName = "twist_loop_b";
        mTwist_B.mStartLine = "// GTwistRunTwist_B twist_loop_b (start)";
        mTwist_B.mEndLine = "// GTwistRunTwist_B twist_loop_b (end)";
        mTwist_B.mClassName = mArxClassName;
        mTwist_B.mMethodName = "Twist_B";
        mTwist_B.mTitle = "GTwistRunTwist_B twist_loop_b";
        mTwist_B.mReadFrom = "expand_a, expand_b, expand_c, expand_d";
        mTwist_B.mTempStorage = "fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d";
        mTwist_B.mWriteTo = "operation_a, operation_b, operation_c, operation_d";

        mTwist_C.mKind = ArxCallKind::kTwist;
        mTwist_C.mUsesNonce = false;
        mTwist_C.mBatchName = "twist_loop_c";
        mTwist_C.mStartLine = "// GTwistRunTwist_C twist_loop_c (start)";
        mTwist_C.mEndLine = "// GTwistRunTwist_C twist_loop_c (end)";
        mTwist_C.mClassName = mArxClassName;
        mTwist_C.mMethodName = "Twist_C";
        mTwist_C.mTitle = "GTwistRunTwist_C twist_loop_c";
        mTwist_C.mReadFrom = "operation_a, operation_b, operation_c, operation_d";
        mTwist_C.mTempStorage = "fire_a, fire_b, fire_c, fire_d, expand_a, expand_b, expand_c, expand_d";
        mTwist_C.mWriteTo = "work_a, work_b, work_c, work_d";

        mGrow_A.mKind = ArxCallKind::kGrow;
        mGrow_A.mUsesNonce = false;
        mGrow_A.mBatchName = "grow_key_a";
        mGrow_A.mStartLine = "// GROW_A grow_key_a (start)";
        mGrow_A.mEndLine = "// GROW_A grow_key_a (end)";
        mGrow_A.mClassName = mArxClassName;
        mGrow_A.mMethodName = "GROW_A";
        mGrow_A.mTitle = "GROW_A grow_key_a";
        mGrow_A.mReadFrom = "work_a, work_b, work_c, work_d";
        mGrow_A.mTempStorage.clear();
        mGrow_A.mWriteTo = "expand_a, expand_b, expand_c, expand_d";

        mGrow_B.mKind = ArxCallKind::kGrow;
        mGrow_B.mUsesNonce = false;
        mGrow_B.mBatchName = "grow_key_b";
        mGrow_B.mStartLine = "// GROW_B grow_key_b (start)";
        mGrow_B.mEndLine = "// GROW_B grow_key_b (end)";
        mGrow_B.mClassName = mArxClassName;
        mGrow_B.mMethodName = "GROW_B";
        mGrow_B.mTitle = "GROW_B grow_key_b";
        mGrow_B.mReadFrom = "expand_a, expand_b, expand_c, expand_d";
        mGrow_B.mTempStorage.clear();
        mGrow_B.mWriteTo = "work_a, work_b, work_c, work_d";

        return ExportArxCompanionFiles(pRoot, pClassName, pError);
    }

    const ArxCallExport* KDF_A_A() const {
        return &mKDF_A_A;
    }

    const ArxCallExport* KDF_A_B() const {
        return &mKDF_A_B;
    }

    const ArxCallExport* KDF_A_C() const {
        return &mKDF_A_C;
    }

    const ArxCallExport* KDF_A_D() const {
        return &mKDF_A_D;
    }

    const ArxCallExport* KDF_B_A() const {
        return &mKDF_B_A;
    }

    const ArxCallExport* KDF_B_B() const {
        return &mKDF_B_B;
    }

    const ArxCallExport* KDF_B_C() const {
        return &mKDF_B_C;
    }

    const ArxCallExport* KDF_B_D() const {
        return &mKDF_B_D;
    }

    const ArxCallExport* Seed_A() const {
        return &mSeed_A;
    }

    const ArxCallExport* Seed_B() const {
        return &mSeed_B;
    }

    const ArxCallExport* Seed_C() const {
        return &mSeed_C;
    }

    const ArxCallExport* Seed_D() const {
        return &mSeed_D;
    }

    const ArxCallExport* Seed_E() const {
        return &mSeed_E;
    }

    const ArxCallExport* Seed_F() const {
        return &mSeed_F;
    }

    const ArxCallExport* Seed_G() const {
        return &mSeed_G;
    }

    const ArxCallExport* Twist_A() const {
        return &mTwist_A;
    }

    const ArxCallExport* Twist_B() const {
        return &mTwist_B;
    }

    const ArxCallExport* Twist_C() const {
        return &mTwist_C;
    }

    const ArxCallExport* Grow_A() const {
        return &mGrow_A;
    }

    const ArxCallExport* Grow_B() const {
        return &mGrow_B;
    }

    const std::string& ClassName() const {
        return mArxClassName;
    }

private:
    std::string mArxClassName;
    ArxCallExport mKDF_A_A;
    ArxCallExport mKDF_A_B;
    ArxCallExport mKDF_A_C;
    ArxCallExport mKDF_A_D;
    ArxCallExport mKDF_B_A;
    ArxCallExport mKDF_B_B;
    ArxCallExport mKDF_B_C;
    ArxCallExport mKDF_B_D;
    ArxCallExport mSeed_A;
    ArxCallExport mSeed_B;
    ArxCallExport mSeed_C;
    ArxCallExport mSeed_D;
    ArxCallExport mSeed_E;
    ArxCallExport mSeed_F;
    ArxCallExport mSeed_G;
    ArxCallExport mTwist_A;
    ArxCallExport mTwist_B;
    ArxCallExport mTwist_C;
    ArxCallExport mGrow_A;
    ArxCallExport mGrow_B;
};

[[maybe_unused]] JsonValue BranchToJsonValue(const TwistProgramBranch &pBranch,
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

    JsonValue::Array aSequence;
    for (const TwistProgramBranchStep &aStep : pBranch.GetSteps()) {
        JsonValue::Object aStepObject;
        switch (aStep.mType) {
            case TwistProgramBranchStepType::kLine:
                aStepObject["type"] = JsonValue::String("line");
                break;
            case TwistProgramBranchStepType::kBatch:
                aStepObject["type"] = JsonValue::String("batch");
                break;
            default:
                SetError(pError, "Branch had invalid sequence step type.");
                return JsonValue::ObjectValue(JsonValue::Object{});
        }
        aStepObject["index"] = JsonValue::Number(static_cast<double>(aStep.mIndex));
        aSequence.push_back(JsonValue::ObjectValue(std::move(aStepObject)));
    }

    JsonValue::Object aObject;
    aObject["string_lines"] = JsonValue::ArrayValue(std::move(aLines));
    aObject["batches"] = JsonValue::ArrayValue(std::move(aBatches));
    aObject["sequence"] = JsonValue::ArrayValue(std::move(aSequence));
    return JsonValue::ObjectValue(std::move(aObject));
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
    aObject["matrix_arg_aa"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgA));
    aObject["matrix_arg_ab"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgB));
    aObject["matrix_arg_ba"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgC));
    aObject["matrix_arg_bb"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgD));
    aObject["mask_mutate_a"] = JsonValue::Number(static_cast<double>(pConstants.mMaskMutateA));
    aObject["mask_mutate_b"] = JsonValue::Number(static_cast<double>(pConstants.mMaskMutateB));
    return JsonValue::ObjectValue(std::move(aObject));
}

[[maybe_unused]] JsonValue DomainBundleToJsonValue(const TwistDomainBundle &pBundle) {
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
    aObject["mats_phase_d_seeder"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseDSalts.mOrbiterAssign);
    aObject["mats_phase_d_orbiter"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseDSalts.mOrbiterUpdate);
    aObject["mats_phase_d_wanderer"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseDSalts.mWandererUpdate);
    aObject["mats_phase_e_seeder"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseESalts.mOrbiterAssign);
    aObject["mats_phase_e_orbiter"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseESalts.mOrbiterUpdate);
    aObject["mats_phase_e_wanderer"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseESalts.mWandererUpdate);
    aObject["mats_phase_f_seeder"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseFSalts.mOrbiterAssign);
    aObject["mats_phase_f_orbiter"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseFSalts.mOrbiterUpdate);
    aObject["mats_phase_f_wanderer"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseFSalts.mWandererUpdate);
    aObject["mats_phase_g_seeder"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseGSalts.mOrbiterAssign);
    aObject["mats_phase_g_orbiter"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseGSalts.mOrbiterUpdate);
    aObject["mats_phase_g_wanderer"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseGSalts.mWandererUpdate);
    aObject["mats_phase_h_seeder"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseHSalts.mOrbiterAssign);
    aObject["mats_phase_h_orbiter"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseHSalts.mOrbiterUpdate);
    aObject["mats_phase_h_wanderer"] = SeedRoundMaterialToJsonValue(pBundle.mPhaseHSalts.mWandererUpdate);
    aObject["constants_phase_a"] = ConstantsToJsonValue(pBundle.mPhaseAConstants);
    aObject["constants_phase_b"] = ConstantsToJsonValue(pBundle.mPhaseBConstants);
    aObject["constants_phase_c"] = ConstantsToJsonValue(pBundle.mPhaseCConstants);
    aObject["constants_phase_d"] = ConstantsToJsonValue(pBundle.mPhaseDConstants);
    aObject["constants_phase_e"] = ConstantsToJsonValue(pBundle.mPhaseEConstants);
    aObject["constants_phase_f"] = ConstantsToJsonValue(pBundle.mPhaseFConstants);
    aObject["constants_phase_g"] = ConstantsToJsonValue(pBundle.mPhaseGConstants);
    aObject["constants_phase_h"] = ConstantsToJsonValue(pBundle.mPhaseHConstants);
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
          << "    " << ByteCppLiteral(pConstants.mMatrixArgA) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgB) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgC) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgD) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMaskMutateA) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMaskMutateB) << "\n"
          << "};\n";
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
    AppendSaltSetDefinition(&aOut, pClassName, "kPhaseDSalts", pBundle.mPhaseDSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kPhaseDConstants", pBundle.mPhaseDConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kPhaseESalts", pBundle.mPhaseESalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kPhaseEConstants", pBundle.mPhaseEConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kPhaseFSalts", pBundle.mPhaseFSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kPhaseFConstants", pBundle.mPhaseFConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kPhaseGSalts", pBundle.mPhaseGSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kPhaseGConstants", pBundle.mPhaseGConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kPhaseHSalts", pBundle.mPhaseHSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kPhaseHConstants", pBundle.mPhaseHConstants);

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
                                               const std::string &pWorkSpaceFieldName) {
    if (pAliasName.empty() || pWorkSpaceFieldName.empty()) {
        return;
    }

    AddLine("std::uint8_t *" + pAliasName + " = pWorkSpace->" + pWorkSpaceFieldName + ";");
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
    return ExportCPPProjectRoot(pRootPath, false, pError);
}

bool GTwistExpander::ExportCPPProjectRoot(const std::string &pRootPath,
                                          const bool pUseSnapShotter,
                                          std::string *pError) const {
    const std::string aBaseInput = mNameBase.empty() ? "Generated" : mNameBase;
    const std::string aBaseName = SanitizeIdentifier(aBaseInput, "Generated");
    const std::string aClassName = "TwistExpander_" + aBaseName;
    
    const std::string aRootInput = pRootPath.empty() ? "generated/cpp" : pRootPath;
    const std::string aRoot = ResolveOutputPathFromProjectRoot(aRootInput);
    
    const std::string aHeaderPath = FileIO::Join(aRoot, aClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(aRoot, aClassName + ".cpp");
    GArx aArx;
    if (!aArx.Bake(aRoot, aClassName, pError)) {
        return false;
    }
    
    GTwistExpander aSnapshot = *this;
    aSnapshot.RefreshTablePointers();
    const TwistProgramBranch &aKDF_ABranch = aSnapshot.mKDF_A;
    const TwistProgramBranch &aKDF_BBranch = aSnapshot.mKDF_B;
    
    std::ostringstream aHeader;
    aHeader << "#pragma once\n"
    << "\n"
    << "#include \"TwistExpander.hpp\"\n"
    << "#include \"" << aArx.ClassName() << ".hpp\"\n"
    << "\n"
    << "class " << aClassName << " : public TwistExpander {\n"
    << "public:\n"
    << "    " << aClassName << "();\n"
    << "    ~" << aClassName << "() override = default;\n"
    << "\n"
    << "    void KDF_A(std::uint64_t pNonce,\n"
    << "               TwistDomainConstants *pConstants,\n"
    << "               TwistDomainSaltSet *pDomainSaltSet,\n"
    << "               std::uint8_t *pSnow,\n"
    << "               int pIndexKDF) override;\n"
    << "    void KDF_B(std::uint64_t pNonce,\n"
    << "               TwistDomainConstants *pConstants,\n"
    << "               TwistDomainSaltSet *pDomainSaltSet,\n"
    << "               int pIndexKDF) override;\n"
    << "    void Seed(TwistWorkSpace *pWorkSpace,\n"
    << "              TwistFarmSalt *pFarmSalt,\n"
    << "              std::uint64_t pNonce,\n"
    << "              std::uint8_t *pPassword,\n"
    << "              unsigned int pPasswordByteLength,\n"
    << "              std::uint8_t *pDestination) override;\n"
    << "    void TwistBlock(TwistWorkSpace *pWorkSpace,\n"
    << "                    std::uint64_t pNonce,\n"
    << "                    std::uint8_t *pSource,\n"
    << "                    std::size_t pBlockIndex,\n"
    << "                    std::size_t pBlockCount,\n"
    << "                    std::uint8_t *pDestination) override;\n"
    << "    void SquashInvestToKeyBoxes() override;\n"
    << "    void GrowKeyA(TwistWorkSpace *pWorkSpace) override;\n"
    << "    void GrowKeyB(TwistWorkSpace *pWorkSpace) override;\n"
    << "\n"
    << "private:\n"
    << "    static const TwistDomainSaltSet kPhaseASalts;\n"
    << "    static const TwistDomainConstants kPhaseAConstants;\n"
    << "    static const TwistDomainSaltSet kPhaseBSalts;\n"
    << "    static const TwistDomainConstants kPhaseBConstants;\n"
    << "    static const TwistDomainSaltSet kPhaseCSalts;\n"
    << "    static const TwistDomainConstants kPhaseCConstants;\n"
    << "    static const TwistDomainSaltSet kPhaseDSalts;\n"
    << "    static const TwistDomainConstants kPhaseDConstants;\n"
    << "    static const TwistDomainSaltSet kPhaseESalts;\n"
    << "    static const TwistDomainConstants kPhaseEConstants;\n"
    << "    static const TwistDomainSaltSet kPhaseFSalts;\n"
    << "    static const TwistDomainConstants kPhaseFConstants;\n"
    << "    static const TwistDomainSaltSet kPhaseGSalts;\n"
    << "    static const TwistDomainConstants kPhaseGConstants;\n"
    << "    static const TwistDomainSaltSet kPhaseHSalts;\n"
    << "    static const TwistDomainConstants kPhaseHConstants;\n"
    << "};\n";
    
    std::ostringstream aCpp;
    aCpp << "#include \"" << aClassName << ".hpp\"\n"
    << "#include \"TwistDiffuse.hpp\"\n"
    << "#include \"TwistFunctional.hpp\"\n"
    << "#include \"TwistIndexShuffle.hpp\"\n"
    << "#include \"TwistMix32.hpp\"\n"
    << "#include \"TwistMix64.hpp\"\n"
    << "#include \"TwistFarmSalt.hpp\"\n"
    << "#include \"TwistFarmConstants.hpp\"\n"
    << "#include \"TwistMemory.hpp\"\n"
    << "#include \"TwistShiftBox.hpp\"\n"
    << "#include \"TwistSnow.hpp\"\n"
    << "#include \"TwistSquash.hpp\"\n";
    if (pUseSnapShotter) {
        aCpp << "#include \"SnapShotter.hpp\"\n";
    }
    aCpp << "\n"
    << "#include <cstdint>\n"
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
    << "    mDomainBundleInbuilt.mPhaseDSalts = kPhaseDSalts;\n"
    << "    mDomainBundleInbuilt.mPhaseDConstants = kPhaseDConstants;\n"
    << "    mDomainBundleInbuilt.mPhaseESalts = kPhaseESalts;\n"
    << "    mDomainBundleInbuilt.mPhaseEConstants = kPhaseEConstants;\n"
    << "    mDomainBundleInbuilt.mPhaseFSalts = kPhaseFSalts;\n"
    << "    mDomainBundleInbuilt.mPhaseFConstants = kPhaseFConstants;\n"
    << "    mDomainBundleInbuilt.mPhaseGSalts = kPhaseGSalts;\n"
    << "    mDomainBundleInbuilt.mPhaseGConstants = kPhaseGConstants;\n"
    << "    mDomainBundleInbuilt.mPhaseHSalts = kPhaseHSalts;\n"
    << "    mDomainBundleInbuilt.mPhaseHConstants = kPhaseHConstants;\n"
    << "    std::memcpy(&mDomainBundleEphemeral, &mDomainBundleInbuilt, sizeof(mDomainBundleEphemeral));\n"
    << "}\n"
    << "\n"
    << "void " << aClassName << "::KDF_A(std::uint64_t pNonce,\n"
    << "                                  TwistDomainConstants *pConstants,\n"
    << "                                  TwistDomainSaltSet *pDomainSaltSet,\n"
    << "                                  std::uint8_t *pSnow,\n"
    << "                                  int pIndexKDF) {\n"
    << "    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pSnow, pIndexKDF);\n"
    << "    TwistWorkSpace *pWorkSpace = mWorkspace;\n"
    << "    if ((pWorkSpace == nullptr) || (mSource == nullptr) ||\n"
    << "        (pConstants == nullptr) || (pDomainSaltSet == nullptr) || (pSnow == nullptr)) { return; }\n";
    if (pUseSnapShotter) {
        AppendSnapShotStart("SnapStart_KDFA", "pIndexKDF == 0", &aCpp);
    }
    if (!AppendBranchBody(aKDF_ABranch,
                          true,
                          &aCpp,
                          pError,
                          aArx.KDF_A_A(),
                          aArx.KDF_A_B(),
                          aArx.KDF_A_C(),
                          aArx.KDF_A_D(),
                          nullptr,
                          nullptr,
                          nullptr,
                          pUseSnapShotter ? "SnapUpdate_KDFA" : nullptr,
                          "pIndexKDF == 0",
                          "KDF_A_DIFFUSE")) {
        return false;
    }
    aCpp << "}\n"
    << "\n"
    << "void " << aClassName << "::KDF_B(std::uint64_t pNonce,\n"
    << "                                  TwistDomainConstants *pConstants,\n"
    << "                                  TwistDomainSaltSet *pDomainSaltSet,\n"
    << "                                  int pIndexKDF) {\n"
    << "    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet, pIndexKDF);\n"
    << "    TwistWorkSpace *pWorkSpace = mWorkspace;\n"
    << "    if ((pWorkSpace == nullptr) || (mSource == nullptr) ||\n"
    << "        (pConstants == nullptr) || (pDomainSaltSet == nullptr)) { return; }\n";
    if (pUseSnapShotter) {
        AppendSnapShotStart("SnapStart_KDFB", "pIndexKDF == 0", &aCpp);
    }
    if (!AppendBranchBody(aKDF_BBranch,
                          true,
                          &aCpp,
                          pError,
                          aArx.KDF_B_A(),
                          aArx.KDF_B_B(),
                          aArx.KDF_B_C(),
                          aArx.KDF_B_D(),
                          nullptr,
                          nullptr,
                          nullptr,
                          pUseSnapShotter ? "SnapUpdate_KDFB" : nullptr,
                          "pIndexKDF == 0",
                          "KDF_B_DIFFUSE")) {
        return false;
    }
    aCpp << "}\n"
    << "\n"
    << "void " << aClassName << "::Seed(TwistWorkSpace *pWorkSpace,\n"
    << "                                 TwistFarmSalt *pFarmSalt,\n"
    << "                                 std::uint64_t pNonce,\n"
    << "                                 std::uint8_t *pPassword,\n"
    << "                                 unsigned int pPasswordByteLength,\n"
    << "                                 std::uint8_t *pDestination) {\n"
    << "    TwistExpander::Seed(pWorkSpace, pFarmSalt, pNonce, pPassword, pPasswordByteLength, pDestination);\n"
    << "    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr)) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mSeed,
                          false,
                          &aCpp,
                          pError,
                          aArx.Seed_A(),
                          aArx.Seed_B(),
                          aArx.Seed_C(),
                          aArx.Seed_D(),
                          aArx.Seed_E(),
                          aArx.Seed_F(),
                          aArx.Seed_G(),
                          pUseSnapShotter ? "SnapUpdate_SEED" : nullptr,
                          nullptr,
                          "SEED_DIFFUSE",
                          pUseSnapShotter)) {
        return false;
    }
    AppendArxCall(*aArx.Grow_A(), &aCpp);
    aCpp << "    GrowKeyA(pWorkSpace);\n";
    if (pUseSnapShotter) {
        AppendSnapShotUpdate("SnapUpdate_SEED", nullptr, "GROW_A", &aCpp);
    }
    AppendArxCall(*aArx.Grow_B(), &aCpp);
    aCpp << "    GrowKeyB(pWorkSpace);\n";
    if (pUseSnapShotter) {
        AppendSnapShotUpdate("SnapUpdate_SEED", nullptr, "GROW_B", &aCpp);
    }
    aCpp << "    Zero_PostSeed();\n"
    << "}\n"
    << "\n"
    << BuildSquashInvestToKeyBoxesMethod(aClassName)
    << "\n"
    << "void " << aClassName << "::TwistBlock(TwistWorkSpace *pWorkSpace,\n"
    << "                                       std::uint64_t pNonce,\n"
    << "                                       std::uint8_t *pSource,\n"
    << "                                       std::size_t pBlockIndex,\n"
    << "                                       std::size_t pBlockCount,\n"
    << "                                       std::uint8_t *pDestination) {\n"
    << "    TwistExpander::TwistBlock(pWorkSpace, pNonce, pSource, pBlockIndex, pBlockCount, pDestination);\n"
    << "    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }\n";
    if (pUseSnapShotter) {
        AppendSnapShotStart("SnapStart_TWIST", "pBlockIndex == 0U", &aCpp);
    }
    if (!AppendBranchBody(aSnapshot.mTwister,
                          false,
                          &aCpp,
                          pError,
                          aArx.Twist_A(),
                          aArx.Twist_B(),
                          aArx.Twist_C(),
                          nullptr,
                          nullptr,
                          nullptr,
                          nullptr,
                          pUseSnapShotter ? "SnapUpdate_TWIST" : nullptr,
                          nullptr,
                          "TWIST_DIFFUSE")) {
        return false;
    }
    aCpp << "    if ((pBlockCount - pBlockIndex) > static_cast<std::size_t>(H_KEY)) {\n";
    {
        std::ostringstream aGrowCall;
        AppendArxCall(*aArx.Grow_A(), &aGrowCall);
        aCpp << IndentBlock(aGrowCall.str(), 1) << '\n';
    }
    aCpp << "        GrowKeyA(pWorkSpace);\n";
    if (pUseSnapShotter) {
        std::ostringstream aSnapShotUpdate;
        AppendSnapShotUpdate("SnapUpdate_TWIST", nullptr, "GROW_A", &aSnapShotUpdate);
        aCpp << IndentBlock(aSnapShotUpdate.str(), 1);
    }
    aCpp << "    } else {\n"
         << "        TwistShiftBox::ShiftKeyBoxA(pWorkSpace);\n"
         << "    }\n"
         << "    if ((pBlockCount - pBlockIndex) > static_cast<std::size_t>(H_KEY)) {\n";
    {
        std::ostringstream aGrowCall;
        AppendArxCall(*aArx.Grow_B(), &aGrowCall);
        aCpp << IndentBlock(aGrowCall.str(), 1) << '\n';
    }
    aCpp << "        GrowKeyB(pWorkSpace);\n";
    if (pUseSnapShotter) {
        std::ostringstream aSnapShotUpdate;
        AppendSnapShotUpdate("SnapUpdate_TWIST", nullptr, "GROW_B", &aSnapShotUpdate);
        aCpp << IndentBlock(aSnapShotUpdate.str(), 1);
    }
    aCpp << "    } else {\n"
         << "        TwistShiftBox::ShiftKeyBoxB(pWorkSpace);\n"
         << "    }\n"
         << "}\n"
         << "\n"
         << "void " << aClassName << "::GrowKeyA(TwistWorkSpace *pWorkSpace) {\n"
         << "    TwistExpander::GrowKeyA(pWorkSpace);\n"
         << "    if (pWorkSpace == nullptr) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mGrowKeyA, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n"
    << "\n"
    << "void " << aClassName << "::GrowKeyB(TwistWorkSpace *pWorkSpace) {\n"
    << "    TwistExpander::GrowKeyB(pWorkSpace);\n"
    << "    if (pWorkSpace == nullptr) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mGrowKeyB, false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n"
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
    (void)pRootPath;
    SetError(pError, "GTwistExpander JSON export has been removed; use ExportCPPProjectRoot.");
    return false;
#if 0
    GTwistExpander aSnapshot = *this;
    aSnapshot.RefreshTablePointers();
    
    const std::string aBaseInput = aSnapshot.mNameBase.empty() ? "Generated" : aSnapshot.mNameBase;
    const std::string aBaseName = SanitizeIdentifier(aBaseInput, "Generated");
    
    JsonValue::Object aRootObject;
    aRootObject["name_base"] = JsonValue::String(aBaseInput);
    const TwistProgramBranch &aKDF_ABranch = aSnapshot.mKDF_A;
    aRootObject["kdf_a"] = BranchToJsonValue(aKDF_ABranch, pError);
    if ((pError != nullptr) && !pError->empty()) {
        return false;
    }
    
    aRootObject["kdf_b"] = BranchToJsonValue(aSnapshot.mKDF_B, pError);
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

    aRootObject["grow_key_a"] = BranchToJsonValue(aSnapshot.mGrowKeyA, pError);
    if ((pError != nullptr) && !pError->empty()) {
        return false;
    }

    aRootObject["grow_key_b"] = BranchToJsonValue(aSnapshot.mGrowKeyB, pError);
    if ((pError != nullptr) && !pError->empty()) {
        return false;
    }
    
    JsonValue::Object aTables;
    aTables["domain_bundle_inbuilt"] = DomainBundleToJsonValue(aSnapshot.mDomainBundleInbuilt);
    aRootObject["tables"] = JsonValue::ObjectValue(std::move(aTables));
    
    const std::string aJsonText = JsonValue::ObjectValue(std::move(aRootObject)).Serialize();
    const std::string aRoot = pRootPath.empty() ? "generated/json" : pRootPath;
    const std::string aOutputPath = ResolveJsonOutputPath(aRoot, aBaseName);
    
    return SaveTextFile(aOutputPath, aJsonText, pError);
#endif
}
