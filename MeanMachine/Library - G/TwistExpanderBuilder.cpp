//
//  TwistExpanderBuilder.cpp
//  MeanMachine
//

#include "GTwistExpander.hpp"

#include "FileIO.hpp"
#include "GSeedRunKDF_A.hpp"
#include "GSeedRunKDF_B.hpp"
#include "GSeedRunSeed.hpp"
#include "GSeedRunStage.hpp"
#include "GTwistRunGrowKeyA.hpp"
#include "GTwistRunTwist.hpp"
#include "GJson.hpp"
#include "Random.hpp"
#include "stdafx.hpp"

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

std::string SizeLiteral(const int pValue) {
    return std::to_string(pValue) + "U";
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

std::string BuildRandomSquashInvestToKeyBoxesMethod(const std::string &pClassName) {
    constexpr int kLaneCount = 8;
    constexpr int kFragmentCount = 16;

    std::array<std::vector<int>, kLaneCount> aOffsetOrders;
    for (int aLane = 0; aLane < kLaneCount; ++aLane) {
        aOffsetOrders[static_cast<std::size_t>(aLane)] = ShuffledInvestOffsetOrder();
    }

    std::ostringstream aStream;
    aStream << "void " << pClassName << "::SquashInvestToKeyBoxes() {\n"
    << "    static_assert((S_BLOCK / W_KEY) == 16, \"SquashInvestToKeyBoxes expects 16 invest fragments.\");\n"
    << "    static_assert(H_KEY == 8, \"SquashInvestToKeyBoxes expects 8 key rows per box.\");\n"
    << "    TwistWorkSpace *pWorkSpace = mWorkspace;\n"
    << "    if (pWorkSpace == nullptr) { return; }\n"
    << "    std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;\n"
    << "    std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;\n"
    << "    std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;\n"
    << "    std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;\n"
    << "    std::uint8_t *aInvestLaneE = pWorkSpace->mInvestLaneE;\n"
    << "    std::uint8_t *aInvestLaneF = pWorkSpace->mInvestLaneF;\n"
    << "    std::uint8_t *aInvestLaneG = pWorkSpace->mInvestLaneG;\n"
    << "    std::uint8_t *aInvestLaneH = pWorkSpace->mInvestLaneH;\n"
    << "\n";

    for (int aFragmentIndex = 0; aFragmentIndex < kFragmentCount; ++aFragmentIndex) {
        const bool aUseKeyBoxA = (aFragmentIndex < H_KEY);
        const int aRowIndex = aUseKeyBoxA ? aFragmentIndex : (aFragmentIndex - H_KEY);
        const char *aKeyBoxName = aUseKeyBoxA ? "mKeyBoxA" : "mKeyBoxB";
        const char *aKeyBoxComment = aUseKeyBoxA ? "key_box_a" : "key_box_b";
        std::vector<int> aLaneOrder = { 0, 1, 2, 3, 4, 5, 6, 7 };
        std::vector<int> aShifts = { 0, 8, 16, 24, 32, 40, 48, 56 };
        std::vector<int> aIndexOffsets;
        aIndexOffsets.reserve(kLaneCount);
        for (int aLane = 0; aLane < kLaneCount; ++aLane) {
            aIndexOffsets.push_back(Random::Get(W_KEY));
        }
        Random::Shuffle(&aLaneOrder);
        Random::Shuffle(&aShifts);
        const std::string aDiffuseName = RandomDiffuse64Name();

        aStream << "    // " << aKeyBoxComment << " row " << aRowIndex << "\n"
        << "    // read chunks:";
        for (int aFragment = 0; aFragment < kLaneCount; ++aFragment) {
            const int aLane = aLaneOrder[static_cast<std::size_t>(aFragment)];
            const std::vector<int> &aOffsets = aOffsetOrders[static_cast<std::size_t>(aLane)];
            const int aOffset = aOffsets[static_cast<std::size_t>(aFragmentIndex % static_cast<int>(aOffsets.size()))];
            aStream << (aFragment == 0 ? " " : ", ")
            << InvestLaneAliasName(aLane) << "[" << aOffset << "]";
        }
        aStream << "\n"
        << "    // index offsets: ";
        for (int aFragment = 0; aFragment < kLaneCount; ++aFragment) {
            if (aFragment > 0) {
                aStream << ", ";
            }
            aStream << SizeLiteral(aIndexOffsets[static_cast<std::size_t>(aFragment)]);
        }
        aStream << "\n"
        << "    {\n";
        for (int aFragment = 0; aFragment < kLaneCount; aFragment += 2) {
            const int aLaneA = aLaneOrder[static_cast<std::size_t>(aFragment)];
            const int aLaneB = aLaneOrder[static_cast<std::size_t>(aFragment + 1)];
            const std::vector<int> &aOffsetsA = aOffsetOrders[static_cast<std::size_t>(aLaneA)];
            const std::vector<int> &aOffsetsB = aOffsetOrders[static_cast<std::size_t>(aLaneB)];
            const int aOffsetA = aOffsetsA[static_cast<std::size_t>(aFragmentIndex % static_cast<int>(aOffsetsA.size()))];
            const int aOffsetB = aOffsetsB[static_cast<std::size_t>(aFragmentIndex % static_cast<int>(aOffsetsB.size()))];
            aStream << "        std::uint8_t *" << FragmentAliasName(aFragment)
            << " = " << InvestLaneAliasName(aLaneA)
            << " + (W_KEY * " << aOffsetA << "U), *"
            << FragmentAliasName(aFragment + 1)
            << " = " << InvestLaneAliasName(aLaneB)
            << " + (W_KEY * " << aOffsetB << "U);\n";
        }
        aStream << "        std::uint8_t *aKeyRow = &(pWorkSpace->" << aKeyBoxName
        << "[" << aRowIndex << "][0]);\n"
        << "        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {\n"
        << "            std::uint64_t aSquash =\n";
        for (int aLane = 0; aLane < kLaneCount; aLane += 2) {
            aStream << "                (static_cast<std::uint64_t>(" << FragmentAliasName(aLane)
            << "[((aIndex + " << SizeLiteral(aIndexOffsets[static_cast<std::size_t>(aLane)])
            << ") & W_KEY1)]) << " << aShifts[static_cast<std::size_t>(aLane)] << "U) | "
            << "(static_cast<std::uint64_t>(" << FragmentAliasName(aLane + 1)
            << "[((aIndex + " << SizeLiteral(aIndexOffsets[static_cast<std::size_t>(aLane + 1)])
            << ") & W_KEY1)]) << " << aShifts[static_cast<std::size_t>(aLane + 1)] << "U)";
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

// The legacy random builder remains available by switching this off.
constexpr bool kUsePreplannedSquashInvestToKeyBoxes = true;
constexpr std::size_t kPreplannedSquashCandidateCount = 33U;

bool BuildSquashInvestToKeyBoxesMethod(const std::string &pClassName,
                                       std::string *pMethod,
                                       std::string *pError) {
    if (pMethod == nullptr) {
        SetError(pError, "SquashInvestToKeyBoxes method output was null.");
        return false;
    }

    if (!kUsePreplannedSquashInvestToKeyBoxes) {
        *pMethod = BuildRandomSquashInvestToKeyBoxesMethod(pClassName);
        return true;
    }

    if ((gCandidateIndex < 0) ||
        (static_cast<std::size_t>(gCandidateIndex) >= kPreplannedSquashCandidateCount)) {
        SetError(pError,
                 "Exhausted all 33 preplanned SquashInvestToKeyBoxes candidates.");
        return false;
    }
    const std::size_t aCandidateIndex = static_cast<std::size_t>(gCandidateIndex);
    char aFileName[64];
    std::snprintf(aFileName,
                  sizeof(aFileName),
                  "SquashInvestToKeyBoxes_Candidate%02zu.cpp",
                  aCandidateIndex + 1U);
    const std::string aRelativePath = FileIO::Join("Assets/squash_pre_planned", aFileName);
    const std::string aSourcePath = FileIO::ProjectRoot(aRelativePath);

    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(aSourcePath, aBytes)) {
        SetError(pError, "Failed to load preplanned squash candidate: " + aSourcePath);
        return false;
    }

    std::string aMethod(aBytes.begin(), aBytes.end());
    const std::string aExpectedSignature =
        "void " + pClassName + "::SquashInvestToKeyBoxes()";
    const std::size_t aSignatureIndex = aMethod.find(aExpectedSignature);
    if (aSignatureIndex == std::string::npos) {
        // Exporters outside the named 33-member family keep the legacy path.
        *pMethod = BuildRandomSquashInvestToKeyBoxesMethod(pClassName);
        return true;
    }
    if (aMethod.find(aExpectedSignature,
                     aSignatureIndex + aExpectedSignature.size()) != std::string::npos) {
        SetError(pError,
                 "Preplanned squash candidate had multiple matching method signatures: " +
                 aSourcePath);
        return false;
    }
    *pMethod = std::move(aMethod);
    std::printf("Loaded preplanned SquashInvestToKeyBoxes file: %s for %s\n",
                aSourcePath.c_str(),
                pClassName.c_str());
    return true;
}

bool LoadPreplannedGrowKeyAMethod(const std::string &pClassName,
                                  std::string *pMethod,
                                  bool *pDidLoad,
                                  std::string *pError) {
    if ((pMethod == nullptr) || (pDidLoad == nullptr)) {
        SetError(pError, "GrowKeyA preplanned loader received null output.");
        return false;
    }
    *pDidLoad = false;

    if ((gCandidateIndex < 0) ||
        (static_cast<std::size_t>(gCandidateIndex) >= kPreplannedSquashCandidateCount)) {
        SetError(pError, "GrowKeyA candidate index was outside 0...32.");
        return false;
    }

    char aFileName[48];
    std::snprintf(aFileName,
                  sizeof(aFileName),
                  "GrowKeyA_Candidate%02d.cpp",
                  gCandidateIndex + 1);
    const std::string aRelativePath = FileIO::Join("Assets/grow_a_pre_planned", aFileName);
    const std::string aSourcePath = FileIO::ProjectRoot(aRelativePath);

    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(aSourcePath, aBytes)) {
        SetError(pError, "Failed to load preplanned GrowKeyA candidate: " + aSourcePath);
        return false;
    }

    std::string aMethod(aBytes.begin(), aBytes.end());
    const std::string aExpectedSignature =
        "void " + pClassName + "::GrowKeyA(TwistWorkSpace *pWorkSpace)";
    const std::size_t aSignatureIndex = aMethod.find(aExpectedSignature);
    if (aSignatureIndex == std::string::npos) {
        // Non-family exporters retain the existing generated GrowKeyA path.
        return true;
    }
    if (aMethod.find(aExpectedSignature,
                     aSignatureIndex + aExpectedSignature.size()) != std::string::npos) {
        SetError(pError,
                 "Preplanned GrowKeyA candidate had multiple matching signatures: " +
                 aSourcePath);
        return false;
    }

    *pMethod = std::move(aMethod);
    *pDidLoad = true;
    std::printf("Loaded preplanned GrowKeyA file: %s for %s\n",
                aSourcePath.c_str(),
                pClassName.c_str());
    return true;
}

bool LoadPreplannedGrowKeyBMethod(const std::string &pClassName,
                                  std::string *pMethod,
                                  bool *pDidLoad,
                                  std::string *pError) {
    if ((pMethod == nullptr) || (pDidLoad == nullptr)) {
        SetError(pError, "GrowKeyB preplanned loader received null output.");
        return false;
    }
    *pDidLoad = false;

    if ((gCandidateIndex < 0) ||
        (static_cast<std::size_t>(gCandidateIndex) >= kPreplannedSquashCandidateCount)) {
        SetError(pError, "GrowKeyB candidate index was outside 0...32.");
        return false;
    }

    char aFileName[48];
    std::snprintf(aFileName,
                  sizeof(aFileName),
                  "GrowKeyB_Candidate%02d.cpp",
                  gCandidateIndex + 1);
    const std::string aRelativePath = FileIO::Join("Assets/grow_b_pre_planned", aFileName);
    const std::string aSourcePath = FileIO::ProjectRoot(aRelativePath);

    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(aSourcePath, aBytes)) {
        SetError(pError, "Failed to load preplanned GrowKeyB candidate: " + aSourcePath);
        return false;
    }

    std::string aMethod(aBytes.begin(), aBytes.end());
    const std::string aExpectedSignature =
        "void " + pClassName + "::GrowKeyB(TwistWorkSpace *pWorkSpace)";
    const std::size_t aSignatureIndex = aMethod.find(aExpectedSignature);
    if (aSignatureIndex == std::string::npos) {
        return true;
    }
    if (aMethod.find(aExpectedSignature,
                     aSignatureIndex + aExpectedSignature.size()) != std::string::npos) {
        SetError(pError,
                 "Preplanned GrowKeyB candidate had multiple matching signatures: " +
                 aSourcePath);
        return false;
    }

    *pMethod = std::move(aMethod);
    *pDidLoad = true;
    std::printf("Loaded preplanned GrowKeyB file: %s for %s\n",
                aSourcePath.c_str(),
                pClassName.c_str());
    return true;
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

    return "std::uint64_t *" + BufAliasName(pSlot) +
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
        return "std::size_t *" + aAlias + " = mIndexList256" +
               aAlias.substr(aAlias.size() - 1U) + ";";
    }
    const std::string aPrefix = "std::uint8_t *" + aAlias + " = ";
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource:
            return "std::uint8_t *" + aAlias + " = pWorkSpace->mSource;";
        case TwistWorkSpaceSlot::kParamSource:
            return "std::uint8_t *" + aAlias + " = pSource;";
        case TwistWorkSpaceSlot::kParamDestination:
            if (pUseKDFParameterAliases) {
                return aPrefix + "pDestination;";
            }
            return aPrefix +
                   "TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(" +
                   std::to_string(static_cast<int>(pSlot)) + "));";

        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA:
            return "std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB:
            return "std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC:
            return "std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD:
            return "std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE:
            return "std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF:
            return "std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA:
            return "std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB:
            return "std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC:
            return "std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD:
            return "std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE:
            return "std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF:
            return "std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA:
            return "std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB:
            return "std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC:
            return "std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD:
            return "std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE:
            return "std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF:
            return "std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;";

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
        case TwistWorkSpaceSlot::kWaterLaneA: return aPrefix + "pWorkSpace->mWaterLaneA;";
        case TwistWorkSpaceSlot::kWaterLaneB: return aPrefix + "pWorkSpace->mWaterLaneB;";
        case TwistWorkSpaceSlot::kWaterLaneC: return aPrefix + "pWorkSpace->mWaterLaneC;";
        case TwistWorkSpaceSlot::kWaterLaneD: return aPrefix + "pWorkSpace->mWaterLaneD;";
        case TwistWorkSpaceSlot::kEarthLaneA: return aPrefix + "pWorkSpace->mEarthLaneA;";
        case TwistWorkSpaceSlot::kEarthLaneB: return aPrefix + "pWorkSpace->mEarthLaneB;";
        case TwistWorkSpaceSlot::kEarthLaneC: return aPrefix + "pWorkSpace->mEarthLaneC;";
        case TwistWorkSpaceSlot::kEarthLaneD: return aPrefix + "pWorkSpace->mEarthLaneD;";
        case TwistWorkSpaceSlot::kWindLaneA: return aPrefix + "pWorkSpace->mWindLaneA;";
        case TwistWorkSpaceSlot::kWindLaneB: return aPrefix + "pWorkSpace->mWindLaneB;";
        case TwistWorkSpaceSlot::kWindLaneC: return aPrefix + "pWorkSpace->mWindLaneC;";
        case TwistWorkSpaceSlot::kWindLaneD: return aPrefix + "pWorkSpace->mWindLaneD;";
        case TwistWorkSpaceSlot::kFuseLaneA: return aPrefix + "pWorkSpace->mFuseLaneA;";
        case TwistWorkSpaceSlot::kFuseLaneB: return aPrefix + "pWorkSpace->mFuseLaneB;";
        case TwistWorkSpaceSlot::kFuseLaneC: return aPrefix + "pWorkSpace->mFuseLaneC;";
        case TwistWorkSpaceSlot::kFuseLaneD: return aPrefix + "pWorkSpace->mFuseLaneD;";
        case TwistWorkSpaceSlot::kScrapLaneA: return aPrefix + "pWorkSpace->mScrapLaneA;";
        case TwistWorkSpaceSlot::kScrapLaneB: return aPrefix + "pWorkSpace->mScrapLaneB;";
        case TwistWorkSpaceSlot::kScrapLaneC: return aPrefix + "pWorkSpace->mScrapLaneC;";
        case TwistWorkSpaceSlot::kScrapLaneD: return aPrefix + "pWorkSpace->mScrapLaneD;";
        case TwistWorkSpaceSlot::kMergeLaneA: return aPrefix + "pWorkSpace->mMergeLaneA;";
        case TwistWorkSpaceSlot::kMergeLaneB: return aPrefix + "pWorkSpace->mMergeLaneB;";
        case TwistWorkSpaceSlot::kMergeLaneC: return aPrefix + "pWorkSpace->mMergeLaneC;";
        case TwistWorkSpaceSlot::kMergeLaneD: return aPrefix + "pWorkSpace->mMergeLaneD;";
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

void AppendWorkspaceMemsetLines(std::ostringstream *pStream,
                                const std::vector<const char *> &pFieldNames,
                                const char *pByteCountText = "S_BLOCK") {
    if (pStream == nullptr) {
        return;
    }

    for (const char *aFieldName : pFieldNames) {
        *pStream << "    std::memset(pWorkSpace->" << aFieldName << ", 0, " << pByteCountText << ");\n";
    }
    *pStream << "\n";
}

void AppendSeedSnapShotScratchZero(std::ostringstream *pStream) {
    AppendWorkspaceMemsetLines(pStream, {
        "mOperationLaneA", "mOperationLaneB", "mOperationLaneC", "mOperationLaneD",
        "mWorkLaneA", "mWorkLaneB", "mWorkLaneC", "mWorkLaneD",
        "mExpansionLaneA", "mExpansionLaneB", "mExpansionLaneC", "mExpansionLaneD",
        "mFireLaneA", "mFireLaneB", "mFireLaneC", "mFireLaneD",
        "mWaterLaneA", "mWaterLaneB", "mWaterLaneC", "mWaterLaneD",
        "mEarthLaneA", "mEarthLaneB", "mEarthLaneC", "mEarthLaneD",
        "mWindLaneA", "mWindLaneB", "mWindLaneC", "mWindLaneD",
        "mFuseLaneA", "mFuseLaneB", "mFuseLaneC", "mFuseLaneD",
        "mScrapLaneA", "mScrapLaneB", "mScrapLaneC", "mScrapLaneD",
        "mSnowLaneA", "mSnowLaneB", "mSnowLaneC", "mSnowLaneD",
    });
    AppendWorkspaceMemsetLines(pStream, {
        "mMergeLaneA", "mMergeLaneB", "mMergeLaneC", "mMergeLaneD",
    }, "S_QUARTER");
}

void AppendSeedSnapShotInvestZero(std::ostringstream *pStream) {
    AppendWorkspaceMemsetLines(pStream, {
        "mInvestLaneA", "mInvestLaneB", "mInvestLaneC", "mInvestLaneD",
        "mInvestLaneE", "mInvestLaneF", "mInvestLaneG", "mInvestLaneH",
    });
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

bool IsTwistDiffuseBatch(const GBatch &pBatch) {
    std::string aError;
    const std::string aScopeBlock = pBatch.BuildCppScopeBlock(&aError, false);
    return aScopeBlock.find("TwistDiffuse::") != std::string::npos;
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
                      const bool pSnapShotSeedCrunch = false,
                      const ArxCallExport *pArxCallH = nullptr,
                      const ArxCallExport *pArxCallI = nullptr,
                      const bool pForceWorkspaceSourceAlias = false,
                      const bool pSkipTwistDiffuseBatches = false) {
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
    if (pArxCallH != nullptr) {
        aArxCalls.push_back(pArxCallH);
    }
    if (pArxCallI != nullptr) {
        aArxCalls.push_back(pArxCallI);
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
        if (pSkipTwistDiffuseBatches && IsTwistDiffuseBatch(aBatch)) {
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
    if (pForceWorkspaceSourceAlias) {
        AppendUniqueValue(&aReferencedSlots, TwistWorkSpaceSlot::kSource);
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
        if (pSkipTwistDiffuseBatches && IsTwistDiffuseBatch(aParsed.mBatch)) {
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

bool ResolveSeedStageConfigs(const std::vector<GSeedRunStageConfig> &pConfigs,
                             std::vector<GSeedRunStageConfig> *pResolved,
                             std::string *pError) {
    if (pResolved == nullptr) {
        SetError(pError, "Seed ARX stage config destination was null.");
        return false;
    }

    *pResolved = pConfigs;
    if (pResolved->empty()) {
        *pResolved = {
            GSeedRunSeedConfig::MakeSeed_AConfig(true),
            GSeedRunSeedConfig::MakeSeed_BConfig(true),
            GSeedRunSeedConfig::MakeSeed_CConfig(true),
            GSeedRunSeedConfig::MakeSeed_DConfig(true),
            GSeedRunSeedConfig::MakeSeed_EConfig(true),
            GSeedRunSeedConfig::MakeSeed_FConfig(true),
            GSeedRunSeedConfig::MakeSeed_GConfig(true),
            GSeedRunSeedConfig::MakeSeed_HConfig(true),
            GSeedRunSeedConfig::MakeSeed_IConfig(true),
        };
    }
    if (pResolved->size() != 9U) {
        SetError(pError, "Seed ARX export expected exactly nine stage configs.");
        return false;
    }

    static const std::array<const char *, 9> kStageNames = {
        "GSeedRunSeed_A", "GSeedRunSeed_B", "GSeedRunSeed_C",
        "GSeedRunSeed_D", "GSeedRunSeed_E", "GSeedRunSeed_F",
        "GSeedRunSeed_G", "GSeedRunSeed_H", "GSeedRunSeed_I",
    };
    for (std::size_t i = 0U; i < pResolved->size(); ++i) {
        if ((*pResolved)[i].mStageName != kStageNames[i]) {
            SetError(pError, "Seed ARX stage config order did not match A through I.");
            return false;
        }
    }
    return true;
}

bool ResolveTwistStageConfigs(const std::vector<GSeedRunStageConfig> &pConfigs,
                              std::vector<GSeedRunStageConfig> *pResolved,
                              std::string *pError) {
    if (pResolved == nullptr) {
        SetError(pError, "Twist ARX stage config destination was null.");
        return false;
    }

    *pResolved = pConfigs;
    if (pResolved->empty()) {
        *pResolved = {
            GTwistRunTwistConfig::MakeTwist_AConfig(),
            GTwistRunTwistConfig::MakeTwist_BConfig(),
            GTwistRunTwistConfig::MakeTwist_CConfig(),
            GTwistRunTwistConfig::MakeTwist_DConfig(),
            GTwistRunTwistConfig::MakeTwist_EConfig(),
            GTwistRunTwistConfig::MakeTwist_FConfig(),
            GTwistRunTwistConfig::MakeTwist_GConfig(),
        };
    }
    if (pResolved->size() != 7U) {
        SetError(pError, "Twist ARX export expected exactly seven stage configs.");
        return false;
    }

    static const std::array<const char *, 7> kStageNames = {
        "GTwistRunTwist_A", "GTwistRunTwist_B", "GTwistRunTwist_C",
        "GTwistRunTwist_D", "GTwistRunTwist_E", "GTwistRunTwist_F",
        "GTwistRunTwist_G",
    };
    for (std::size_t i = 0U; i < pResolved->size(); ++i) {
        if ((*pResolved)[i].mStageName != kStageNames[i]) {
            SetError(pError, "Twist ARX stage config order did not match A through G.");
            return false;
        }
    }
    return true;
}

bool StageConfigReferencesSlot(const GSeedRunStageConfig &pConfig,
                               const TwistWorkSpaceSlot pSlot) {
    for (const GSeedRunStageSliceSpec &aSlice : pConfig.mSlices) {
        for (TwistWorkSpaceSlot aSlot : aSlice.IngressSources()) {
            if (aSlot == pSlot) {
                return true;
            }
        }
        for (TwistWorkSpaceSlot aSlot : aSlice.CrossSources()) {
            if (aSlot == pSlot) {
                return true;
            }
        }
        if (aSlice.mDest == pSlot) {
            return true;
        }
    }
    return false;
}

void AddExportArxKDFPrologue(TwistProgramBranch *pBranch,
                             const bool pUsesSource) {
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
    if (pUsesSource) {
        pBranch->AddLine("std::uint8_t *aSource = pWorkSpace->mSource;");
    }
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

void AddExportArxSeedPrologue(TwistProgramBranch *pBranch,
                              const bool pUsesSource) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("// [seed arx]");
    if (pUsesSource) {
        pBranch->AddLine("std::uint8_t *aSource = pWorkSpace->mSource;");
    }
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

void AddExportArxTwistPrologue(TwistProgramBranch *pBranch,
                               const bool pUsesSource) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("// [twist arx]");
    if (pUsesSource) {
        pBranch->AddLine("std::uint8_t *aSource = pSource;");
    }
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
                             std::string *pError) {
    if (pBranch == nullptr) {
        SetError(pError, "ARX branch output was null.");
        return false;
    }

    pBranch->Clear();
    AddExportArxKDFPrologue(pBranch,
                            StageConfigReferencesSlot(pConfig, TwistWorkSpaceSlot::kSource));

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
    AddExportArxSeedPrologue(pBranch,
                             StageConfigReferencesSlot(pConfig, TwistWorkSpaceSlot::kSource));
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
    AddExportArxTwistPrologue(pBranch,
                              StageConfigReferencesSlot(pConfig, TwistWorkSpaceSlot::kSource));

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

bool BuildExportArxGrow_ABranch(TwistProgramBranch *pBranch,
                                 std::string *pError) {
    return BuildExportArxGrowBranch(pBranch,
                                    GTwistRunGrowKeyConfig::MakeGrowAConfig(),
                                    "GROW_A",
                                    pError);
}

bool BuildExportArxGrow_BBranch(TwistProgramBranch *pBranch,
                                std::string *pError) {
    return BuildExportArxGrowBranch(pBranch,
                                    GTwistRunGrowKeyConfig::MakeGrowBConfig(),
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
                             const std::vector<GSeedRunStageConfig> &pSeedStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pTwistStageConfigs,
                             std::string *pError) {
    const std::string aArxClassName = pClassName + "_Arx";
    const std::string aHeaderPath = FileIO::Join(pRoot, aArxClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(pRoot, aArxClassName + ".cpp");

    using KDFConfigFactory = GSeedRunStageConfig (*)();
    static const std::array<KDFConfigFactory, 5> kKDFAConfigFactories = {
        &GSeedRunKDF_AConfig::MakeKDF_A_AConfig,
        &GSeedRunKDF_AConfig::MakeKDF_A_BConfig,
        &GSeedRunKDF_AConfig::MakeKDF_A_CConfig,
        &GSeedRunKDF_AConfig::MakeKDF_A_DConfig,
        &GSeedRunKDF_AConfig::MakeKDF_A_EConfig,
    };
    static const std::array<const char *, 5> kKDFAMethodNames = {
        "KDF_A_A", "KDF_A_B", "KDF_A_C", "KDF_A_D", "KDF_A_E",
    };
    std::array<TwistProgramBranch, 5> aBranchesKDFA;
    for (std::size_t i = 0U; i < aBranchesKDFA.size(); ++i) {
        if (!BuildExportArxKDFBranch(&aBranchesKDFA[i],
                                     kKDFAConfigFactories[i](),
                                     kKDFAMethodNames[i],
                                     pError)) {
            return false;
        }
    }

    static const std::array<KDFConfigFactory, 4> kKDFBConfigFactories = {
        &GSeedRunKDF_BConfig::MakeKDF_B_AConfig,
        &GSeedRunKDF_BConfig::MakeKDF_B_BConfig,
        &GSeedRunKDF_BConfig::MakeKDF_B_CConfig,
        &GSeedRunKDF_BConfig::MakeKDF_B_DConfig,
    };
    static const std::array<const char *, 4> kKDFBMethodNames = {
        "KDF_B_A", "KDF_B_B", "KDF_B_C", "KDF_B_D",
    };
    std::array<TwistProgramBranch, 4> aBranchesKDFB;
    for (std::size_t i = 0U; i < aBranchesKDFB.size(); ++i) {
        if (!BuildExportArxKDFBranch(&aBranchesKDFB[i],
                                     kKDFBConfigFactories[i](),
                                     kKDFBMethodNames[i],
                                     pError)) {
            return false;
        }
    }
    std::vector<GSeedRunStageConfig> aSeedStageConfigs;
    if (!ResolveSeedStageConfigs(pSeedStageConfigs, &aSeedStageConfigs, pError)) {
        return false;
    }
    static const std::array<const char *, 9> kSeedMethodNames = {
        "Seed_A", "Seed_B", "Seed_C", "Seed_D", "Seed_E",
        "Seed_F", "Seed_G", "Seed_H", "Seed_I",
    };
    std::array<TwistProgramBranch, 9> aBranchesSeed;
    for (std::size_t i = 0U; i < aBranchesSeed.size(); ++i) {
        if (!BuildExportArxSeedBranch(&aBranchesSeed[i],
                                      aSeedStageConfigs[i],
                                      kSeedMethodNames[i],
                                      pError)) {
            return false;
        }
    }

    std::vector<GSeedRunStageConfig> aTwistStageConfigs;
    if (!ResolveTwistStageConfigs(pTwistStageConfigs, &aTwistStageConfigs, pError)) {
        return false;
    }
    static const std::array<const char *, 7> kTwistMethodNames = {
        "Twist_A", "Twist_B", "Twist_C", "Twist_D",
        "Twist_E", "Twist_F", "Twist_G",
    };
    std::array<TwistProgramBranch, 7> aBranchesTwist;
    for (std::size_t i = 0U; i < aBranchesTwist.size(); ++i) {
        if (!BuildExportArxTwistBranch(&aBranchesTwist[i],
                                       aTwistStageConfigs[i],
                                       kTwistMethodNames[i],
                                       pError)) {
            return false;
        }
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
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_B", false, true);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_C", false, true);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_D", false, true);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_E", false, true);
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
    AppendArxSeedSignature(&aHeader, aArxClassName, "Seed_H", false);
    AppendArxSeedSignature(&aHeader, aArxClassName, "Seed_I", false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_A", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_B", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_C", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_D", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_E", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_F", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "Twist_G", false, false);
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
    if (!AppendBranchBody(aBranchesKDFA[0], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n"
    << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_B", true, true);
    if (!AppendBranchBody(aBranchesKDFA[1], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_C", true, true);
    if (!AppendBranchBody(aBranchesKDFA[2], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_D", true, true);
    if (!AppendBranchBody(aBranchesKDFA[3], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_E", true, true);
    if (!AppendBranchBody(aBranchesKDFA[4], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_A", true, false);
    if (!AppendBranchBody(aBranchesKDFB[0], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_B", true, false);
    if (!AppendBranchBody(aBranchesKDFB[1], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_C", true, false);
    if (!AppendBranchBody(aBranchesKDFB[2], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_D", true, false);
    if (!AppendBranchBody(aBranchesKDFB[3], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_A", true);
    if (!AppendBranchBody(aBranchesSeed[0], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_B", true);
    if (!AppendBranchBody(aBranchesSeed[1], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_C", true);
    if (!AppendBranchBody(aBranchesSeed[2], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_D", true);
    if (!AppendBranchBody(aBranchesSeed[3], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_E", true);
    if (!AppendBranchBody(aBranchesSeed[4], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_F", true);
    if (!AppendBranchBody(aBranchesSeed[5], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_G", true);
    if (!AppendBranchBody(aBranchesSeed[6], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_H", true);
    if (!AppendBranchBody(aBranchesSeed[7], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "Seed_I", true);
    if (!AppendBranchBody(aBranchesSeed[8], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_A", true, false);
    if (!AppendBranchBody(aBranchesTwist[0], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_B", true, false);
    if (!AppendBranchBody(aBranchesTwist[1], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_C", true, false);
    if (!AppendBranchBody(aBranchesTwist[2], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_D", true, false);
    if (!AppendBranchBody(aBranchesTwist[3], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_E", true, false);
    if (!AppendBranchBody(aBranchesTwist[4], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_F", true, false);
    if (!AppendBranchBody(aBranchesTwist[5], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "Twist_G", true, false);
    if (!AppendBranchBody(aBranchesTwist[6], false, &aCpp, pError)) {
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
              const std::vector<GSeedRunStageConfig> &pSeedStageConfigs,
              const std::vector<GSeedRunStageConfig> &pTwistStageConfigs,
              std::string *pError) {
        std::vector<GSeedRunStageConfig> aSeedStageConfigs;
        if (!ResolveSeedStageConfigs(pSeedStageConfigs, &aSeedStageConfigs, pError)) {
            return false;
        }
        std::vector<GSeedRunStageConfig> aTwistStageConfigs;
        if (!ResolveTwistStageConfigs(pTwistStageConfigs, &aTwistStageConfigs, pError)) {
            return false;
        }

        mArxClassName = pClassName + "_Arx";
        const std::array<ArxCallExport *, 5> aKDFACalls = {
            &mKDF_A_A, &mKDF_A_B, &mKDF_A_C, &mKDF_A_D, &mKDF_A_E,
        };
        static const std::array<const char *, 5> kKDFAMethodNames = {
            "KDF_A_A", "KDF_A_B", "KDF_A_C", "KDF_A_D", "KDF_A_E",
        };
        static const std::array<const char *, 5> kKDFAStageNames = {
            "GSeedRunKDF_A_A", "GSeedRunKDF_A_B", "GSeedRunKDF_A_C",
            "GSeedRunKDF_A_D", "GSeedRunKDF_A_E",
        };
        static const std::array<const char *, 5> kKDFABatchNames = {
            "kdf_a_loop_a", "kdf_a_loop_b", "kdf_a_loop_c",
            "kdf_a_loop_d", "kdf_a_loop_e",
        };
        for (std::size_t i = 0U; i < aKDFACalls.size(); ++i) {
            ArxCallExport &aCall = *aKDFACalls[i];
            aCall.mKind = ArxCallKind::kKDF;
            aCall.mUsesSnow = true;
            aCall.mBatchName = kKDFABatchNames[i];
            aCall.mStartLine = std::string("// ") + kKDFAStageNames[i] + " " +
                kKDFABatchNames[i] + " (start)";
            aCall.mEndLine = std::string("// ") + kKDFAStageNames[i] + " " +
                kKDFABatchNames[i] + " (end)";
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kKDFAMethodNames[i];
        }

        const std::array<ArxCallExport *, 4> aKDFBCalls = {
            &mKDF_B_A, &mKDF_B_B, &mKDF_B_C, &mKDF_B_D,
        };
        static const std::array<const char *, 4> kKDFBMethodNames = {
            "KDF_B_A", "KDF_B_B", "KDF_B_C", "KDF_B_D",
        };
        static const std::array<const char *, 4> kKDFBStageNames = {
            "GSeedRunKDF_B_A", "GSeedRunKDF_B_B",
            "GSeedRunKDF_B_C", "GSeedRunKDF_B_D",
        };
        static const std::array<const char *, 4> kKDFBBatchNames = {
            "kdf_b_loop_a", "kdf_b_loop_b", "kdf_b_loop_c", "kdf_b_loop_d",
        };
        for (std::size_t i = 0U; i < aKDFBCalls.size(); ++i) {
            ArxCallExport &aCall = *aKDFBCalls[i];
            aCall.mKind = ArxCallKind::kKDF;
            aCall.mUsesSnow = false;
            aCall.mBatchName = kKDFBBatchNames[i];
            aCall.mStartLine = std::string("// ") + kKDFBStageNames[i] + " " +
                kKDFBBatchNames[i] + " (start)";
            aCall.mEndLine = std::string("// ") + kKDFBStageNames[i] + " " +
                kKDFBBatchNames[i] + " (end)";
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kKDFBMethodNames[i];
        }

        const std::array<ArxCallExport *, 9> aSeedCalls = {
            &mSeed_A, &mSeed_B, &mSeed_C, &mSeed_D, &mSeed_E,
            &mSeed_F, &mSeed_G, &mSeed_H, &mSeed_I,
        };
        static const std::array<const char *, 9> kSeedMethodNames = {
            "Seed_A", "Seed_B", "Seed_C", "Seed_D", "Seed_E",
            "Seed_F", "Seed_G", "Seed_H", "Seed_I",
        };
        for (std::size_t i = 0U; i < aSeedCalls.size(); ++i) {
            ArxCallExport &aCall = *aSeedCalls[i];
            const GSeedRunStageConfig &aConfig = aSeedStageConfigs[i];
            aCall.mKind = ArxCallKind::kSeed;
            aCall.mUsesNonce = true;
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kSeedMethodNames[i];
        }

        const std::array<ArxCallExport *, 7> aTwistCalls = {
            &mTwist_A, &mTwist_B, &mTwist_C, &mTwist_D,
            &mTwist_E, &mTwist_F, &mTwist_G,
        };
        static const std::array<const char *, 7> kTwistMethodNames = {
            "Twist_A", "Twist_B", "Twist_C", "Twist_D",
            "Twist_E", "Twist_F", "Twist_G",
        };
        for (std::size_t i = 0U; i < aTwistCalls.size(); ++i) {
            ArxCallExport &aCall = *aTwistCalls[i];
            const GSeedRunStageConfig &aConfig = aTwistStageConfigs[i];
            aCall.mKind = ArxCallKind::kTwist;
            aCall.mUsesNonce = false;
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kTwistMethodNames[i];
        }

        mGrow_A.mKind = ArxCallKind::kGrow;
        mGrow_A.mUsesNonce = false;
        mGrow_A.mBatchName = "grow_key_a";
        mGrow_A.mStartLine = "// GROW_A grow_key_a (start)";
        mGrow_A.mEndLine = "// GROW_A grow_key_a (end)";
        mGrow_A.mClassName = mArxClassName;
        mGrow_A.mMethodName = "GROW_A";

        mGrow_B.mKind = ArxCallKind::kGrow;
        mGrow_B.mUsesNonce = false;
        mGrow_B.mBatchName = "grow_key_b";
        mGrow_B.mStartLine = "// GROW_B grow_key_b (start)";
        mGrow_B.mEndLine = "// GROW_B grow_key_b (end)";
        mGrow_B.mClassName = mArxClassName;
        mGrow_B.mMethodName = "GROW_B";

        return ExportArxCompanionFiles(pRoot,
                                       pClassName,
                                       aSeedStageConfigs,
                                       aTwistStageConfigs,
                                       pError);
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

    const ArxCallExport* KDF_A_E() const {
        return &mKDF_A_E;
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

    const ArxCallExport* Seed_H() const {
        return &mSeed_H;
    }

    const ArxCallExport* Seed_I() const {
        return &mSeed_I;
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

    const ArxCallExport* Twist_D() const {
        return &mTwist_D;
    }

    const ArxCallExport* Twist_E() const {
        return &mTwist_E;
    }

    const ArxCallExport* Twist_F() const {
        return &mTwist_F;
    }

    const ArxCallExport* Twist_G() const {
        return &mTwist_G;
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
    ArxCallExport mKDF_A_E;
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
    ArxCallExport mSeed_H;
    ArxCallExport mSeed_I;
    ArxCallExport mTwist_A;
    ArxCallExport mTwist_B;
    ArxCallExport mTwist_C;
    ArxCallExport mTwist_D;
    ArxCallExport mTwist_E;
    ArxCallExport mTwist_F;
    ArxCallExport mTwist_G;
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

    std::string aSquashInvestToKeyBoxesMethod;
    if (!BuildSquashInvestToKeyBoxesMethod(aClassName,
                                            &aSquashInvestToKeyBoxesMethod,
                                            pError)) {
        return false;
    }
    
    const std::string aRootInput = pRootPath.empty() ? "generated/cpp" : pRootPath;
    const std::string aRoot = ResolveOutputPathFromProjectRoot(aRootInput);
    
    const std::string aHeaderPath = FileIO::Join(aRoot, aClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(aRoot, aClassName + ".cpp");
    GArx aArx;
    if (!aArx.Bake(aRoot,
                   aClassName,
                   mSeedStageConfigs,
                   mTwistStageConfigs,
                   pError)) {
        return false;
    }
    
    GTwistExpander aSnapshot = *this;
    aSnapshot.RefreshTablePointers();
    const TwistProgramBranch &aKDF_ABranch = aSnapshot.mKDF_A;
    const TwistProgramBranch &aKDF_BBranch = aSnapshot.mKDF_B;

    std::ostringstream aLegacyGrowKeyA;
    aLegacyGrowKeyA << "void " << aClassName << "::GrowKeyA(TwistWorkSpace *pWorkSpace) {\n"
                    << "    TwistExpander::GrowKeyA(pWorkSpace);\n"
                    << "    if (pWorkSpace == nullptr) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mGrowKeyA, false, &aLegacyGrowKeyA, pError)) {
        return false;
    }
    aLegacyGrowKeyA << "}\n";

    std::string aGrowKeyAMethod;
    bool aDidLoadPreplannedGrowKeyA = false;
    if (!LoadPreplannedGrowKeyAMethod(aClassName,
                                      &aGrowKeyAMethod,
                                      &aDidLoadPreplannedGrowKeyA,
                                      pError)) {
        return false;
    }
    if (!aDidLoadPreplannedGrowKeyA) {
        aGrowKeyAMethod = aLegacyGrowKeyA.str();
    }

    std::ostringstream aLegacyGrowKeyB;
    aLegacyGrowKeyB << "void " << aClassName << "::GrowKeyB(TwistWorkSpace *pWorkSpace) {\n"
                    << "    TwistExpander::GrowKeyB(pWorkSpace);\n"
                    << "    if (pWorkSpace == nullptr) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mGrowKeyB, false, &aLegacyGrowKeyB, pError)) {
        return false;
    }
    aLegacyGrowKeyB << "}\n";

    std::string aGrowKeyBMethod;
    bool aDidLoadPreplannedGrowKeyB = false;
    if (!LoadPreplannedGrowKeyBMethod(aClassName,
                                      &aGrowKeyBMethod,
                                      &aDidLoadPreplannedGrowKeyB,
                                      pError)) {
        return false;
    }
    if (!aDidLoadPreplannedGrowKeyB) {
        aGrowKeyBMethod = aLegacyGrowKeyB.str();
    }
    
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
    << "              std::size_t pPasswordByteLength,\n"
    << "              std::uint8_t *pDestination) override;\n"
    << "    void TwistBlock(TwistWorkSpace *pWorkSpace,\n"
    << "                    std::uint8_t *pSource,\n"
    << "                    std::uint8_t *pDestination) override;\n"
    << "    void SquashInvestToKeyBoxes() override;\n"
    << "    void GrowKeyA(TwistWorkSpace *pWorkSpace) override;\n"
    << "    void GrowKeyB(TwistWorkSpace *pWorkSpace) override;\n"
    << "\n"
    << "private:\n";
    if (pUseSnapShotter) {
        aHeader << "    std::size_t mTwistBlockCounter;\n";
    }
    aHeader
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
    << ": TwistExpander() {\n";
    if (pUseSnapShotter) {
        aCpp << "    mTwistBlockCounter = 0U;\n";
    }
    aCpp
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
    << "    mDomainBundleEphemeral.Zero();\n"
    << "}\n"
    << "\n"
    << "void " << aClassName << "::KDF_A(std::uint64_t pNonce,\n"
    << "                                  TwistDomainConstants *pConstants,\n"
    << "                                  TwistDomainSaltSet *pDomainSaltSet,\n"
    << "                                  std::uint8_t *pSnow,\n"
    << "                                  int pIndexKDF) {\n"
    << "    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pSnow, pIndexKDF);\n"
    << "    TwistWorkSpace *pWorkSpace = mWorkspace;\n"
    << "    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||\n"
    << "        (pDomainSaltSet == nullptr) || (pSnow == nullptr)) { return; }\n";
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
                          aArx.KDF_A_E(),
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
    << "    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||\n"
    << "        (pDomainSaltSet == nullptr)) { return; }\n";
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
    << "                                 std::size_t pPasswordByteLength,\n"
    << "                                 std::uint8_t *pDestination) {\n"
    << "    TwistExpander::Seed(pWorkSpace, pFarmSalt, pNonce, pPassword, pPasswordByteLength, pDestination);\n"
    << "    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr)) { return; }\n";
    if (pUseSnapShotter) {
        aCpp << "    mTwistBlockCounter = 0U;\n";
    }
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
                          pUseSnapShotter,
                          aArx.Seed_H(),
                          aArx.Seed_I(),
                          true)) {
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
    << aSquashInvestToKeyBoxesMethod
    << "\n"
    << "void " << aClassName << "::TwistBlock(TwistWorkSpace *pWorkSpace,\n"
    << "                                       std::uint8_t *pSource,\n"
    << "                                       std::uint8_t *pDestination) {\n"
    << "    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);\n"
    << "    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }\n";
    if (pUseSnapShotter) {
        AppendSnapShotStart("SnapStart_TWIST", "mTwistBlockCounter == 0U", &aCpp);
    }
    if (!AppendBranchBody(aSnapshot.mTwister,
                          false,
                          &aCpp,
                          pError,
                          aArx.Twist_A(),
                          aArx.Twist_B(),
                          aArx.Twist_C(),
                          aArx.Twist_D(),
                          aArx.Twist_E(),
                          aArx.Twist_F(),
                          aArx.Twist_G(),
                          pUseSnapShotter ? "SnapUpdate_TWIST" : nullptr,
                          nullptr,
                          "TWIST_DIFFUSE",
                          false,
                          nullptr,
                          nullptr,
                          false,
                          /* pSkipTwistDiffuseBatches = */ false)) {
        return false;
    }
    AppendArxCall(*aArx.Grow_A(), &aCpp);
    aCpp << "    GrowKeyA(pWorkSpace);\n";
    if (pUseSnapShotter) {
        AppendSnapShotUpdate("SnapUpdate_TWIST", nullptr, "GROW_A", &aCpp);
    }
    AppendArxCall(*aArx.Grow_B(), &aCpp);
    aCpp << "    GrowKeyB(pWorkSpace);\n";
    if (pUseSnapShotter) {
        AppendSnapShotUpdate("SnapUpdate_TWIST", nullptr, "GROW_B", &aCpp);
        aCpp << "    mTwistBlockCounter += 1U;\n";
    }
    aCpp << "}\n"
    << "\n"
    << aGrowKeyAMethod
    << "\n"
    << aGrowKeyBMethod
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
