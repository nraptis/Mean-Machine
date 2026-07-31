//
//  TwistExpanderBuilder.cpp
//  MeanMachine
//

#include "GTwistExpander.hpp"

#include "FileIO.hpp"
#include "GrowAControl.hpp"
#include "GrowBControl.hpp"
#include "GSeedRunKDF_A.hpp"
#include "GSeedRunKDF_B.hpp"
#include "GSeedRunKDF_C.hpp"
#include "GSeedRunKDF_D.hpp"
#include "GSeedRunStage.hpp"
#include "ResidualBucket.hpp"
#include "GJson.hpp"
#include "Random.hpp"
#include "stdafx.hpp"

#include <array>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <string>
#include <utility>
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

bool EnsureControlValues(std::string *pError) {
    auto LoadGrowA = [&]() {
        if (GrowAControl::GeneratedCount() ==
            GrowAControl::kCandidateCount) {
            return true;
        }
        if (GrowAControl::GeneratedCount() != 0U) {
            SetError(pError,
                     "GrowAControl had a partial candidate family.");
            return false;
        }
        GrowAControl::Reset();
        return GrowAControl::LoadValues("Assets/grow_a_pre_planned",
                                        pError);
    };

    auto LoadGrowB = [&]() {
        if (GrowBControl::GeneratedCount() ==
            GrowBControl::kCandidateCount) {
            return true;
        }
        if (GrowBControl::GeneratedCount() != 0U) {
            SetError(pError,
                     "GrowBControl had a partial candidate family.");
            return false;
        }
        GrowBControl::Reset();
        return GrowBControl::LoadValues("Assets/grow_b_pre_planned",
                                        pError);
    };

    return LoadGrowA() &&
           LoadGrowB();
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

std::string RandomDestinationSquashLine() {
    static constexpr std::array<const char *, 3> kMethods = {
        "SquashA", "SquashB", "SquashC",
    };
    const char *aMethod =
        kMethods[static_cast<std::size_t>(Random::Get(
            static_cast<int>(kMethods.size())
        ))];

    return std::string("    TwistSquash::") + aMethod +
        "(pWorkSpace->mCrystalLaneA, pWorkSpace->mCrystalLaneB, "
        "pWorkSpace->mCrystalLaneC, pWorkSpace->mCrystalLaneD, "
        "pDestination);\n";
}

struct FlowLoopExport {
    std::string                             mId;
    std::string                             mSectionId;
    std::string                             mFamilyId;
    std::string                             mFunctionId;
    std::string                             mLoopLetter;
    std::vector<TwistWorkSpaceSlot>         mInputs;
    TwistWorkSpaceSlot                      mDestination =
        TwistWorkSpaceSlot::kInvalid;
};

struct FlowLaneFamily {
    TwistWorkSpaceSlot                      mFirst;
    const char                              *mName;
};

std::string FlowSlotName(const TwistWorkSpaceSlot pSlot) {
    static constexpr std::array<FlowLaneFamily, 20> kLaneFamilies = {{
        {TwistWorkSpaceSlot::kEarthLaneA, "earth"},
        {TwistWorkSpaceSlot::kFireLaneA, "fire"},
        {TwistWorkSpaceSlot::kWindLaneA, "wind"},
        {TwistWorkSpaceSlot::kWaterLaneA, "water"},
        {TwistWorkSpaceSlot::kHeartLaneA, "heart"},
        {TwistWorkSpaceSlot::kSoilLaneA, "soil"},
        {TwistWorkSpaceSlot::kLightningLaneA, "lightning"},
        {TwistWorkSpaceSlot::kIceLaneA, "ice"},
        {TwistWorkSpaceSlot::kWoodLaneA, "wood"},
        {TwistWorkSpaceSlot::kMagmaLaneA, "magma"},
        {TwistWorkSpaceSlot::kPlasmaLaneA, "plasma"},
        {TwistWorkSpaceSlot::kShadowLaneA, "shadow"},
        {TwistWorkSpaceSlot::kCrystalLaneA, "crystal"},
        {TwistWorkSpaceSlot::kAetherLaneA, "aether"},
        {TwistWorkSpaceSlot::kCelestialLaneA, "celestial"},
        {TwistWorkSpaceSlot::kKineticLaneA, "kinetic"},
        {TwistWorkSpaceSlot::kVaporLaneA, "vapor"},
        {TwistWorkSpaceSlot::kSpiritLaneA, "spirit"},
        {TwistWorkSpaceSlot::kFuseLaneA, "fuse"},
        {TwistWorkSpaceSlot::kParamCrossA, "cross"},
    }};

    const int aSlotValue = static_cast<int>(pSlot);
    for (const FlowLaneFamily &aFamily : kLaneFamilies) {
        const int aOffset =
            aSlotValue - static_cast<int>(aFamily.mFirst);
        if ((aOffset >= 0) && (aOffset < 4)) {
            std::string aName = aFamily.mName;
            aName += "_";
            aName.push_back(static_cast<char>('a' + aOffset));
            return aName;
        }
    }

    const int aKeyRowAOffset =
        aSlotValue - static_cast<int>(TwistWorkSpaceSlot::kKeyRowA0);
    if ((aKeyRowAOffset >= 0) && (aKeyRowAOffset < 8)) {
        return "key_row_a_" + std::to_string(aKeyRowAOffset);
    }
    const int aKeyRowBOffset =
        aSlotValue - static_cast<int>(TwistWorkSpaceSlot::kKeyRowB0);
    if ((aKeyRowBOffset >= 0) && (aKeyRowBOffset < 8)) {
        return "key_row_b_" + std::to_string(aKeyRowBOffset);
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kSourceLane: return "source";
        case TwistWorkSpaceSlot::kNonceLane: return "nonce";
        case TwistWorkSpaceSlot::kParamSource: return "source";
        case TwistWorkSpaceSlot::kParamDestination: return "destination";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return "key_box_a";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return "key_box_b";
        case TwistWorkSpaceSlot::kKeyRowReadA: return "key_a";
        case TwistWorkSpaceSlot::kKeyRowReadB: return "key_b";
        case TwistWorkSpaceSlot::kKeyRowWriteA: return "key_write_a";
        case TwistWorkSpaceSlot::kKeyRowWriteB: return "key_write_b";
        default:
            return "slot_" + std::to_string(aSlotValue);
    }
}

void AppendFlowLoops(
    std::vector<FlowLoopExport> *pLoops,
    const std::string &pSectionId,
    const std::string &pFamilyId,
    const std::string &pFunctionId,
    const GSeedRunStageConfig &pConfig) {
    if (pLoops == nullptr) {
        return;
    }

    for (std::size_t i = 0U; i < pConfig.mSlices.size(); ++i) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[i];
        FlowLoopExport aLoop;
        aLoop.mSectionId = pSectionId;
        aLoop.mFamilyId = pFamilyId;
        aLoop.mFunctionId = pFunctionId;
        aLoop.mLoopLetter =
            std::string(1U, static_cast<char>('A' + i));
        aLoop.mId =
            pFunctionId + "_LOOP_" + aLoop.mLoopLetter;
        aLoop.mInputs = aSlice.IngressSources();
        const std::vector<TwistWorkSpaceSlot> aCrossInputs =
            aSlice.CrossSources();
        aLoop.mInputs.insert(aLoop.mInputs.end(),
                             aCrossInputs.begin(),
                             aCrossInputs.end());
        aLoop.mDestination = aSlice.mDest;
        pLoops->push_back(std::move(aLoop));
    }
}

std::string JsonString(const std::string &pValue) {
    return JsonValue::String(pValue).Serialize();
}

bool SaveFlowJSON(
    const std::string &pRoot,
    const std::string &pClassName,
    const std::string &pExpanderName,
    const std::size_t pCandidateIndex,
    const std::vector<FlowLoopExport> &pLoops,
    std::string *pError) {
    std::ostringstream aJSON;
    aJSON
        << "{\n"
        << "  \"expander\": {\n"
        << "    \"name\": " << JsonString(pExpanderName) << ",\n"
        << "    \"candidate_index\": " << pCandidateIndex << "\n"
        << "  },\n"
        << "  \"loops\": [\n";

    for (std::size_t i = 0U; i < pLoops.size(); ++i) {
        const FlowLoopExport &aLoop = pLoops[i];
        aJSON
            << "    {\n"
            << "      \"id\": " << JsonString(aLoop.mId) << ",\n"
            << "      \"section_id\": "
            << JsonString(aLoop.mSectionId) << ",\n"
            << "      \"family_id\": "
            << JsonString(aLoop.mFamilyId) << ",\n"
            << "      \"function_id\": "
            << JsonString(aLoop.mFunctionId) << ",\n"
            << "      \"loop_letter\": "
            << JsonString(aLoop.mLoopLetter) << ",\n"
            << "      \"inputs\": [";
        for (std::size_t j = 0U; j < aLoop.mInputs.size(); ++j) {
            if (j > 0U) {
                aJSON << ", ";
            }
            aJSON << JsonString(FlowSlotName(aLoop.mInputs[j]));
        }
        aJSON
            << "],\n"
            << "      \"destination\": "
            << JsonString(FlowSlotName(aLoop.mDestination)) << "\n"
            << "    }";
        if ((i + 1U) < pLoops.size()) {
            aJSON << ",";
        }
        aJSON << "\n";
    }

    aJSON
        << "  ]\n"
        << "}\n";

    const std::string aFlowPath =
        FileIO::Join(pRoot, pClassName + "_Flow.json");
    return SaveTextFile(aFlowPath, aJSON.str(), pError);
}

const char *RandomNonceDiffuseName() {
    return kNonceDiffuseNames[static_cast<std::size_t>(Random::Get(static_cast<int>(kNonceDiffuseNames.size())))];
}

const char *NonceDiffuseName(const GAXSKDiffuseKind pFixedDiffuse) {
    switch (pFixedDiffuse) {
        case GAXSKDiffuseKind::kDiffuseA: return "DiffuseA";
        case GAXSKDiffuseKind::kDiffuseB: return "DiffuseB";
        case GAXSKDiffuseKind::kDiffuseC: return "DiffuseC";
        case GAXSKDiffuseKind::kInvalid:
        default:
            return RandomNonceDiffuseName();
    }
}

std::string NonceDeclareLine(
    const GSymbol &pNonceSymbol,
    const GAXSKDiffuseKind pFixedDiffuse = GAXSKDiffuseKind::kInvalid) {
    const std::uint64_t aMultiplyWord = Random::Get64HighOdd();
    const std::uint64_t aAddWord = Random::Get64High();
    const char *aDiffuseName = NonceDiffuseName(pFixedDiffuse);

    std::ostringstream aLine;
    aLine << "[[maybe_unused]] const std::uint64_t " << pNonceSymbol.mName << " = TwistMix64::"
          << aDiffuseName
          << "(pNonce * "
          << UInt64Literal(aMultiplyWord)
          << " + "
          << UInt64Literal(aAddWord) << ");";
    return aLine.str();
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
    return (pName == "aIngress") ||
           (pName == "aCarry") ||
           (LetterIndexFromSuffix(pName, "aWanderer") >= 0);
}

std::string ScalarInitialValueForName(const std::string &pName) {
    if (IsFixedRandomArxStateScalarName(pName)) {
        return "0U";
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
        TwistDomain::kKeyRotateA,
        TwistDomain::kKeyRotateB,
        TwistDomain::kKeySpawnA,
        TwistDomain::kKeySpawnB,
        TwistDomain::kSeed,
        TwistDomain::kTwist
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

std::string CollapseLocalArxStateArguments(std::string pLine) {
    static const std::string kExpandedArguments =
        "&aPrevious, &aIngress, &aCarry"
        ", &aWandererA, &aWandererB, &aWandererC, &aWandererD"
        ", &aWandererE, &aWandererF, &aWandererG, &aWandererH"
        ", &aWandererI, &aWandererJ, &aWandererK";

    const std::size_t aOffset = pLine.find(kExpandedArguments);
    if (aOffset != std::string::npos) {
        pLine.replace(aOffset,
                      kExpandedArguments.size(),
                      "ARX_STATE_VARS");
    }
    return pLine;
}

bool DecodePhaseSaltWorkspaceSlot(const TwistWorkSpaceSlot pSlot,
                                  int *pPhaseOut,
                                  int *pRoleOut,
                                  int *pLaneOut) {
    const int aValue = static_cast<int>(pSlot);
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kKeyRotateASaltOrbiterAssignA);
    const int aCountPerPhase = 24;
    const int aPhaseCount = 6;
    if ((aValue < aBase) || (aValue >= (aBase + aCountPerPhase * aPhaseCount))) {
        return false;
    }

    const int aOffset = aValue - aBase;
    const int aRoleLaneOffset = aOffset % aCountPerPhase;
    if (pPhaseOut != nullptr) {
        *pPhaseOut = aOffset / aCountPerPhase;
    }
    if (pRoleOut != nullptr) {
        *pRoleOut = aRoleLaneOffset / 8;
    }
    if (pLaneOut != nullptr) {
        *pLaneOut = aRoleLaneOffset % 8;
    }
    return true;
}

void AppendPhaseSaltWorkspaceSlots(std::vector<TwistWorkSpaceSlot> *pSlots) {
    if (pSlots == nullptr) {
        return;
    }
    const int aBase = static_cast<int>(TwistWorkSpaceSlot::kKeyRotateASaltOrbiterAssignA);
    const int aCount = 24 * 6;
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
        "mKeyRotateASalts",
        "mKeySpawnASalts",
        "mSeedSalts",
        "mTwistSalts",
        "mKeyRotateBSalts",
        "mKeySpawnBSalts"
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
        "mSaltF",
        "mSaltG",
        "mSaltH"
    };

    return "std::uint64_t *" + BufAliasName(pSlot) +
           " = pWorkSpace->mDomainBundle." + kPhaseMembers[aPhase] +
           "." + kRoleMembers[aRole] + "." + kLaneMembers[aLane] + ";";
}

std::vector<TwistWorkSpaceSlot> FixedWorkspaceSlotOrder() {
    std::vector<TwistWorkSpaceSlot> aSlots = {
        TwistWorkSpaceSlot::kSourceLane,
        TwistWorkSpaceSlot::kNonceLane,
        TwistWorkSpaceSlot::kParamSource,
        TwistWorkSpaceSlot::kParamDestination,
        TwistWorkSpaceSlot::kParamCrossA,
        TwistWorkSpaceSlot::kParamCrossB,
        TwistWorkSpaceSlot::kParamCrossC,
        TwistWorkSpaceSlot::kParamCrossD,

        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignG,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignH,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateG,
        TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateH,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateG,
        TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateH,

        TwistWorkSpaceSlot::kHeartLaneA,
        TwistWorkSpaceSlot::kHeartLaneB,
        TwistWorkSpaceSlot::kHeartLaneC,
        TwistWorkSpaceSlot::kHeartLaneD,

        TwistWorkSpaceSlot::kSpiritLaneA,
        TwistWorkSpaceSlot::kSpiritLaneB,
        TwistWorkSpaceSlot::kSpiritLaneC,
        TwistWorkSpaceSlot::kSpiritLaneD,

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

        TwistWorkSpaceSlot::kWoodLaneA,
        TwistWorkSpaceSlot::kWoodLaneB,
        TwistWorkSpaceSlot::kWoodLaneC,
        TwistWorkSpaceSlot::kWoodLaneD,

        TwistWorkSpaceSlot::kLightningLaneA,
        TwistWorkSpaceSlot::kLightningLaneB,
        TwistWorkSpaceSlot::kLightningLaneC,
        TwistWorkSpaceSlot::kLightningLaneD,

        TwistWorkSpaceSlot::kMagmaLaneA,
        TwistWorkSpaceSlot::kMagmaLaneB,
        TwistWorkSpaceSlot::kMagmaLaneC,
        TwistWorkSpaceSlot::kMagmaLaneD,

        TwistWorkSpaceSlot::kSoilLaneA,
        TwistWorkSpaceSlot::kSoilLaneB,
        TwistWorkSpaceSlot::kSoilLaneC,
        TwistWorkSpaceSlot::kSoilLaneD,

        TwistWorkSpaceSlot::kPlasmaLaneA,
        TwistWorkSpaceSlot::kPlasmaLaneB,
        TwistWorkSpaceSlot::kPlasmaLaneC,
        TwistWorkSpaceSlot::kPlasmaLaneD,

        TwistWorkSpaceSlot::kShadowLaneA,
        TwistWorkSpaceSlot::kShadowLaneB,
        TwistWorkSpaceSlot::kShadowLaneC,
        TwistWorkSpaceSlot::kShadowLaneD,

        TwistWorkSpaceSlot::kCrystalLaneA,
        TwistWorkSpaceSlot::kCrystalLaneB,
        TwistWorkSpaceSlot::kCrystalLaneC,
        TwistWorkSpaceSlot::kCrystalLaneD,

        TwistWorkSpaceSlot::kAetherLaneA,
        TwistWorkSpaceSlot::kAetherLaneB,
        TwistWorkSpaceSlot::kAetherLaneC,
        TwistWorkSpaceSlot::kAetherLaneD,

        TwistWorkSpaceSlot::kCelestialLaneA,
        TwistWorkSpaceSlot::kCelestialLaneB,
        TwistWorkSpaceSlot::kCelestialLaneC,
        TwistWorkSpaceSlot::kCelestialLaneD,

        TwistWorkSpaceSlot::kKineticLaneA,
        TwistWorkSpaceSlot::kKineticLaneB,
        TwistWorkSpaceSlot::kKineticLaneC,
        TwistWorkSpaceSlot::kKineticLaneD,

        TwistWorkSpaceSlot::kVaporLaneA,
        TwistWorkSpaceSlot::kVaporLaneB,
        TwistWorkSpaceSlot::kVaporLaneC,
        TwistWorkSpaceSlot::kVaporLaneD,

        TwistWorkSpaceSlot::kIceLaneA,
        TwistWorkSpaceSlot::kIceLaneB,
        TwistWorkSpaceSlot::kIceLaneC,
        TwistWorkSpaceSlot::kIceLaneD,

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

        TwistWorkSpaceSlot::kKeyRowA0,
        TwistWorkSpaceSlot::kKeyRowA1,
        TwistWorkSpaceSlot::kKeyRowA2,
        TwistWorkSpaceSlot::kKeyRowA3,
        TwistWorkSpaceSlot::kKeyRowA4,
        TwistWorkSpaceSlot::kKeyRowA5,
        TwistWorkSpaceSlot::kKeyRowA6,
        TwistWorkSpaceSlot::kKeyRowA7,

        TwistWorkSpaceSlot::kKeyRowB0,
        TwistWorkSpaceSlot::kKeyRowB1,
        TwistWorkSpaceSlot::kKeyRowB2,
        TwistWorkSpaceSlot::kKeyRowB3,
        TwistWorkSpaceSlot::kKeyRowB4,
        TwistWorkSpaceSlot::kKeyRowB5,
        TwistWorkSpaceSlot::kKeyRowB6,
        TwistWorkSpaceSlot::kKeyRowB7
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
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignG:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignH:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateG:
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateH:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateG:
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateH:
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
        case TwistWorkSpaceSlot::kKeyRowA0:
        case TwistWorkSpaceSlot::kKeyRowA1:
        case TwistWorkSpaceSlot::kKeyRowA2:
        case TwistWorkSpaceSlot::kKeyRowA3:
        case TwistWorkSpaceSlot::kKeyRowA4:
        case TwistWorkSpaceSlot::kKeyRowA5:
        case TwistWorkSpaceSlot::kKeyRowA6:
        case TwistWorkSpaceSlot::kKeyRowA7:
        case TwistWorkSpaceSlot::kKeyRowB0:
        case TwistWorkSpaceSlot::kKeyRowB1:
        case TwistWorkSpaceSlot::kKeyRowB2:
        case TwistWorkSpaceSlot::kKeyRowB3:
        case TwistWorkSpaceSlot::kKeyRowB4:
        case TwistWorkSpaceSlot::kKeyRowB5:
        case TwistWorkSpaceSlot::kKeyRowB6:
        case TwistWorkSpaceSlot::kKeyRowB7:
        case TwistWorkSpaceSlot::kParamCrossA:
        case TwistWorkSpaceSlot::kParamCrossB:
        case TwistWorkSpaceSlot::kParamCrossC:
        case TwistWorkSpaceSlot::kParamCrossD:
            return true;
        default:
            return false;
    }
}

bool IsImplicitPointerWorkspaceSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kParamSource:
        case TwistWorkSpaceSlot::kParamDestination:
        case TwistWorkSpaceSlot::kParamCrossA:
        case TwistWorkSpaceSlot::kParamCrossB:
        case TwistWorkSpaceSlot::kParamCrossC:
        case TwistWorkSpaceSlot::kParamCrossD:
            return true;
        default:
            return false;
    }
}

std::string WorkspaceAliasDeclaration(const TwistWorkSpaceSlot pSlot,
                                      const bool pUseKDFParameterAliases,
                                      const bool pUseCrossParameters) {
    (void)pUseCrossParameters;
    const std::string aPhaseSaltDeclaration = PhaseSaltWorkspaceDeclaration(pSlot);
    if (!aPhaseSaltDeclaration.empty()) {
        return aPhaseSaltDeclaration;
    }

    const std::string aAlias = BufAliasName(pSlot);
    if ((pSlot == TwistWorkSpaceSlot::kIndexList256A) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256B) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256C) ||
        (pSlot == TwistWorkSpaceSlot::kIndexList256D)) {
        return "std::size_t *" + aAlias + " = pWorkSpace->mIndexList256" +
               aAlias.substr(aAlias.size() - 1U) + ";";
    }
    const std::string aPrefix = "std::uint8_t *" + aAlias + " = ";
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSourceLane:
            return "std::uint8_t *" + aAlias + " = pWorkSpace->mSourceLane;";
        case TwistWorkSpaceSlot::kNonceLane:
            return "std::uint8_t *" + aAlias + " = pWorkSpace->mNonceLane;";
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
            return "std::uint64_t *aOASaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB:
            return "std::uint64_t *aOASaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignC:
            return "std::uint64_t *aOASaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignD:
            return "std::uint64_t *aOASaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignE:
            return "std::uint64_t *aOASaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignF:
            return "std::uint64_t *aOASaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignG:
            return "std::uint64_t *aOASaltG = pDomainSaltSet->mOrbiterAssign.mSaltG;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignH:
            return "std::uint64_t *aOASaltH = pDomainSaltSet->mOrbiterAssign.mSaltH;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateA:
            return "std::uint64_t *aOUSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateB:
            return "std::uint64_t *aOUSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC:
            return "std::uint64_t *aOUSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD:
            return "std::uint64_t *aOUSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateE:
            return "std::uint64_t *aOUSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateF:
            return "std::uint64_t *aOUSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateG:
            return "std::uint64_t *aOUSaltG = pDomainSaltSet->mOrbiterUpdate.mSaltG;";
        case TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateH:
            return "std::uint64_t *aOUSaltH = pDomainSaltSet->mOrbiterUpdate.mSaltH;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateA:
            return "std::uint64_t *aWUSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateB:
            return "std::uint64_t *aWUSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateC:
            return "std::uint64_t *aWUSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateD:
            return "std::uint64_t *aWUSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE:
            return "std::uint64_t *aWUSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF:
            return "std::uint64_t *aWUSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateG:
            return "std::uint64_t *aWUSaltG = pDomainSaltSet->mWandererUpdate.mSaltG;";
        case TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateH:
            return "std::uint64_t *aWUSaltH = pDomainSaltSet->mWandererUpdate.mSaltH;";

        case TwistWorkSpaceSlot::kHeartLaneA: return aPrefix + "pWorkSpace->mHeartLaneA;";
        case TwistWorkSpaceSlot::kHeartLaneB: return aPrefix + "pWorkSpace->mHeartLaneB;";
        case TwistWorkSpaceSlot::kHeartLaneC: return aPrefix + "pWorkSpace->mHeartLaneC;";
        case TwistWorkSpaceSlot::kHeartLaneD: return aPrefix + "pWorkSpace->mHeartLaneD;";

        case TwistWorkSpaceSlot::kSpiritLaneA: return aPrefix + "pWorkSpace->mSpiritLaneA;";
        case TwistWorkSpaceSlot::kSpiritLaneB: return aPrefix + "pWorkSpace->mSpiritLaneB;";
        case TwistWorkSpaceSlot::kSpiritLaneC: return aPrefix + "pWorkSpace->mSpiritLaneC;";
        case TwistWorkSpaceSlot::kSpiritLaneD: return aPrefix + "pWorkSpace->mSpiritLaneD;";

        case TwistWorkSpaceSlot::kParamCrossA: return aPrefix + "pCrossLaneA;";
        case TwistWorkSpaceSlot::kParamCrossB: return aPrefix + "pCrossLaneB;";
        case TwistWorkSpaceSlot::kParamCrossC: return aPrefix + "pCrossLaneC;";
        case TwistWorkSpaceSlot::kParamCrossD: return aPrefix + "pCrossLaneD;";
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
        case TwistWorkSpaceSlot::kWoodLaneA: return aPrefix + "pWorkSpace->mWoodLaneA;";
        case TwistWorkSpaceSlot::kWoodLaneB: return aPrefix + "pWorkSpace->mWoodLaneB;";
        case TwistWorkSpaceSlot::kWoodLaneC: return aPrefix + "pWorkSpace->mWoodLaneC;";
        case TwistWorkSpaceSlot::kWoodLaneD: return aPrefix + "pWorkSpace->mWoodLaneD;";
        case TwistWorkSpaceSlot::kLightningLaneA: return aPrefix + "pWorkSpace->mLightningLaneA;";
        case TwistWorkSpaceSlot::kLightningLaneB: return aPrefix + "pWorkSpace->mLightningLaneB;";
        case TwistWorkSpaceSlot::kLightningLaneC: return aPrefix + "pWorkSpace->mLightningLaneC;";
        case TwistWorkSpaceSlot::kLightningLaneD: return aPrefix + "pWorkSpace->mLightningLaneD;";
        case TwistWorkSpaceSlot::kMagmaLaneA: return aPrefix + "pWorkSpace->mMagmaLaneA;";
        case TwistWorkSpaceSlot::kMagmaLaneB: return aPrefix + "pWorkSpace->mMagmaLaneB;";
        case TwistWorkSpaceSlot::kMagmaLaneC: return aPrefix + "pWorkSpace->mMagmaLaneC;";
        case TwistWorkSpaceSlot::kMagmaLaneD: return aPrefix + "pWorkSpace->mMagmaLaneD;";
        case TwistWorkSpaceSlot::kSoilLaneA: return aPrefix + "pWorkSpace->mSoilLaneA;";
        case TwistWorkSpaceSlot::kSoilLaneB: return aPrefix + "pWorkSpace->mSoilLaneB;";
        case TwistWorkSpaceSlot::kSoilLaneC: return aPrefix + "pWorkSpace->mSoilLaneC;";
        case TwistWorkSpaceSlot::kSoilLaneD: return aPrefix + "pWorkSpace->mSoilLaneD;";
        case TwistWorkSpaceSlot::kPlasmaLaneA: return aPrefix + "pWorkSpace->mPlasmaLaneA;";
        case TwistWorkSpaceSlot::kPlasmaLaneB: return aPrefix + "pWorkSpace->mPlasmaLaneB;";
        case TwistWorkSpaceSlot::kPlasmaLaneC: return aPrefix + "pWorkSpace->mPlasmaLaneC;";
        case TwistWorkSpaceSlot::kPlasmaLaneD: return aPrefix + "pWorkSpace->mPlasmaLaneD;";
        case TwistWorkSpaceSlot::kShadowLaneA: return aPrefix + "pWorkSpace->mShadowLaneA;";
        case TwistWorkSpaceSlot::kShadowLaneB: return aPrefix + "pWorkSpace->mShadowLaneB;";
        case TwistWorkSpaceSlot::kShadowLaneC: return aPrefix + "pWorkSpace->mShadowLaneC;";
        case TwistWorkSpaceSlot::kShadowLaneD: return aPrefix + "pWorkSpace->mShadowLaneD;";
        case TwistWorkSpaceSlot::kCrystalLaneA: return aPrefix + "pWorkSpace->mCrystalLaneA;";
        case TwistWorkSpaceSlot::kCrystalLaneB: return aPrefix + "pWorkSpace->mCrystalLaneB;";
        case TwistWorkSpaceSlot::kCrystalLaneC: return aPrefix + "pWorkSpace->mCrystalLaneC;";
        case TwistWorkSpaceSlot::kCrystalLaneD: return aPrefix + "pWorkSpace->mCrystalLaneD;";
        case TwistWorkSpaceSlot::kAetherLaneA: return aPrefix + "pWorkSpace->mAetherLaneA;";
        case TwistWorkSpaceSlot::kAetherLaneB: return aPrefix + "pWorkSpace->mAetherLaneB;";
        case TwistWorkSpaceSlot::kAetherLaneC: return aPrefix + "pWorkSpace->mAetherLaneC;";
        case TwistWorkSpaceSlot::kAetherLaneD: return aPrefix + "pWorkSpace->mAetherLaneD;";
        case TwistWorkSpaceSlot::kCelestialLaneA: return aPrefix + "pWorkSpace->mCelestialLaneA;";
        case TwistWorkSpaceSlot::kCelestialLaneB: return aPrefix + "pWorkSpace->mCelestialLaneB;";
        case TwistWorkSpaceSlot::kCelestialLaneC: return aPrefix + "pWorkSpace->mCelestialLaneC;";
        case TwistWorkSpaceSlot::kCelestialLaneD: return aPrefix + "pWorkSpace->mCelestialLaneD;";
        case TwistWorkSpaceSlot::kKineticLaneA: return aPrefix + "pWorkSpace->mKineticLaneA;";
        case TwistWorkSpaceSlot::kKineticLaneB: return aPrefix + "pWorkSpace->mKineticLaneB;";
        case TwistWorkSpaceSlot::kKineticLaneC: return aPrefix + "pWorkSpace->mKineticLaneC;";
        case TwistWorkSpaceSlot::kKineticLaneD: return aPrefix + "pWorkSpace->mKineticLaneD;";
        case TwistWorkSpaceSlot::kVaporLaneA: return aPrefix + "pWorkSpace->mVaporLaneA;";
        case TwistWorkSpaceSlot::kVaporLaneB: return aPrefix + "pWorkSpace->mVaporLaneB;";
        case TwistWorkSpaceSlot::kVaporLaneC: return aPrefix + "pWorkSpace->mVaporLaneC;";
        case TwistWorkSpaceSlot::kVaporLaneD: return aPrefix + "pWorkSpace->mVaporLaneD;";
        case TwistWorkSpaceSlot::kIceLaneA: return aPrefix + "pWorkSpace->mIceLaneA;";
        case TwistWorkSpaceSlot::kIceLaneB: return aPrefix + "pWorkSpace->mIceLaneB;";
        case TwistWorkSpaceSlot::kIceLaneC: return aPrefix + "pWorkSpace->mIceLaneC;";
        case TwistWorkSpaceSlot::kIceLaneD: return aPrefix + "pWorkSpace->mIceLaneD;";

        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return aPrefix + "&(pWorkSpace->mKeyBoxA[0][0]);";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return aPrefix + "&(pWorkSpace->mKeyBoxB[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowReadA: return aPrefix + "&(pWorkSpace->mKeyBoxA[H_KEY - 1][0]);";
        case TwistWorkSpaceSlot::kKeyRowReadB: return aPrefix + "&(pWorkSpace->mKeyBoxB[H_KEY - 1][0]);";
        case TwistWorkSpaceSlot::kKeyRowWriteA: return aPrefix + "&(pWorkSpace->mKeyBoxA[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowWriteB: return aPrefix + "&(pWorkSpace->mKeyBoxB[0][0]);";

        case TwistWorkSpaceSlot::kKeyRowA0: return aPrefix + "&(pWorkSpace->mKeyBoxA[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowA1: return aPrefix + "&(pWorkSpace->mKeyBoxA[1][0]);";
        case TwistWorkSpaceSlot::kKeyRowA2: return aPrefix + "&(pWorkSpace->mKeyBoxA[2][0]);";
        case TwistWorkSpaceSlot::kKeyRowA3: return aPrefix + "&(pWorkSpace->mKeyBoxA[3][0]);";
        case TwistWorkSpaceSlot::kKeyRowA4: return aPrefix + "&(pWorkSpace->mKeyBoxA[4][0]);";
        case TwistWorkSpaceSlot::kKeyRowA5: return aPrefix + "&(pWorkSpace->mKeyBoxA[5][0]);";
        case TwistWorkSpaceSlot::kKeyRowA6: return aPrefix + "&(pWorkSpace->mKeyBoxA[6][0]);";
        case TwistWorkSpaceSlot::kKeyRowA7: return aPrefix + "&(pWorkSpace->mKeyBoxA[7][0]);";

        case TwistWorkSpaceSlot::kKeyRowB0: return aPrefix + "&(pWorkSpace->mKeyBoxB[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowB1: return aPrefix + "&(pWorkSpace->mKeyBoxB[1][0]);";
        case TwistWorkSpaceSlot::kKeyRowB2: return aPrefix + "&(pWorkSpace->mKeyBoxB[2][0]);";
        case TwistWorkSpaceSlot::kKeyRowB3: return aPrefix + "&(pWorkSpace->mKeyBoxB[3][0]);";
        case TwistWorkSpaceSlot::kKeyRowB4: return aPrefix + "&(pWorkSpace->mKeyBoxB[4][0]);";
        case TwistWorkSpaceSlot::kKeyRowB5: return aPrefix + "&(pWorkSpace->mKeyBoxB[5][0]);";
        case TwistWorkSpaceSlot::kKeyRowB6: return aPrefix + "&(pWorkSpace->mKeyBoxB[6][0]);";
        case TwistWorkSpaceSlot::kKeyRowB7: return aPrefix + "&(pWorkSpace->mKeyBoxB[7][0]);";

        default:
            return aPrefix +
                   "TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(" +
                   std::to_string(static_cast<int>(pSlot)) + "));";
    }
}

std::string LaneSplitAliasDeclaration(
    const TwistBufferKey pKey,
    const bool pUseCrossParameters) {
    (void)pUseCrossParameters;
    if (!pKey.IsLaneSplit()) {
        return "";
    }
    const TwistWorkSpaceSlot aSlot =
        static_cast<TwistWorkSpaceSlot>(pKey.mSlot);
    return "std::uint8_t *" + BufAliasName(pKey) + " = " +
           BufAliasName(aSlot) + " + (W_KEY * " +
           std::to_string(static_cast<unsigned int>(pKey.mLaneSplit)) +
           "U);";
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
    bool mUsesCrossLanes = false;
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

const std::array<const char *, 13> kExternalArxStateVariables = {
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
    return "std::uint64_t " + pName + " = 0U;";
}

void AppendSeedArxStateInitializerLines(std::vector<std::string> *pDeclaredNames,
                                        std::ostringstream *pStream) {
    if ((pDeclaredNames == nullptr) || (pStream == nullptr)) {
        return;
    }

    const std::array<const char *, 2> aCoreNames = {
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
                   std::ostringstream *pStream,
                   const bool pForwardArxStateParameters = false) {
    if (pStream == nullptr) {
        return;
    }

    if ((pArxCall.mKind == ArxCallKind::kSeed) ||
        (pArxCall.mKind == ArxCallKind::kTwist) ||
        (pArxCall.mKind == ArxCallKind::kGrow)) {
        const char *aParameterMacro = nullptr;
        if ((pArxCall.mKind == ArxCallKind::kSeed) &&
            !pForwardArxStateParameters) {
            aParameterMacro = "PARAMS_SEED";
        } else if ((pArxCall.mKind == ArxCallKind::kTwist) &&
                   !pForwardArxStateParameters) {
            aParameterMacro = "PARAMS_TWIST";
        } else if ((pArxCall.mKind == ArxCallKind::kGrow) &&
                   pForwardArxStateParameters) {
            aParameterMacro = "PARAMS_GROW";
        }

        if (aParameterMacro != nullptr) {
            *pStream
            << "    " << pArxCall.mClassName << "::"
            << pArxCall.mMethodName << "(" << aParameterMacro << ");\n\n";
            return;
        }

        *pStream
        << "    " << pArxCall.mClassName << "::" << pArxCall.mMethodName
        << "(pWorkSpace,\n";
        if (pArxCall.mUsesNonce) {
            *pStream << "                 pNonce,\n";
        }
        if (pArxCall.mKind == ArxCallKind::kTwist) {
            *pStream << "                 pSource,\n";
        }
        if (pArxCall.mUsesCrossLanes) {
            *pStream
            << "                 pCrossLaneA,\n"
            << "                 pCrossLaneB,\n"
            << "                 pCrossLaneC,\n"
            << "                 pCrossLaneD,\n";
        }
        *pStream << (pForwardArxStateParameters ?
                     "                 MUTABLE_PARAMS_PASSED);\n\n" :
                     "                 ARX_STATE_VARS);\n\n");
        return;
    }

    if (pForwardArxStateParameters) {
        *pStream
        << "    " << pArxCall.mClassName << "::" << pArxCall.mMethodName
        << "(PARAMS_KDF);\n\n";
    } else {
        *pStream
        << "    " << pArxCall.mClassName << "::" << pArxCall.mMethodName
        << "(pWorkSpace,\n"
        << "                 pNonce,\n"
        << "                 pConstants,\n"
        << "                 pDomainSaltSet,\n"
        << "                 ARX_STATE_VARS);\n\n";
    }
}

bool IsTwistDiffuseBatch(const GBatch &pBatch) {
    std::string aError;
    const std::string aScopeBlock = pBatch.BuildCppScopeBlock(&aError, false);
    return aScopeBlock.find("TwistDiffuse::") != std::string::npos;
}

bool AppendBranchBodyWithArxCalls(
    const TwistProgramBranch &pBranch,
    const bool pIncludeKDFParameterAliases,
    std::ostringstream *pStream,
    std::string *pError,
    const std::vector<const ArxCallExport *> &pArxCalls,
    const bool pForceWorkspaceSourceAlias,
    const bool pSkipTwistDiffuseBatches,
    const bool pUseCrossParameters) {
    if (pStream == nullptr) {
        SetError(pError, "Branch output stream was null.");
        return false;
    }

    const std::vector<const ArxCallExport *> &aArxCalls = pArxCalls;

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
        if (aNormalizedLine == "READ_IN_MUTABLE_PARAMS;") {
            AppendUniqueValue(&aDeclaredNames, std::string("aPrevious"));
            for (const char *aName : kExternalArxStateVariables) {
                AppendUniqueValue(&aDeclaredNames, std::string(aName));
            }
            continue;
        }
        const std::string aDeclaredName = DeclaredIdentifierFromLine(aNormalizedLine);
        if (!aDeclaredName.empty()) {
            AppendUniqueValue(&aDeclaredNames, aDeclaredName);
        }
    }
    std::vector<std::string> aLoopVariables;
    std::vector<std::string> aScalarVariables;
    std::vector<TwistWorkSpaceSlot> aReferencedSlots;
    std::vector<GSymbol> aReferencedLaneSplits;
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
        for (const GSymbol &aBuffer : aBatch.CollectReferencedBuffers()) {
            if (aBuffer.mKey.IsLaneSplit() &&
                (std::find(aReferencedLaneSplits.begin(),
                           aReferencedLaneSplits.end(),
                           aBuffer) == aReferencedLaneSplits.end())) {
                aReferencedLaneSplits.push_back(aBuffer);
            }
        }
    }
    const std::vector<std::string> aReferencedScalarVariables = aScalarVariables;
    const bool aForwardsArxStateParameters =
        UsesArxCallKind(aArxCalls, ArxCallKind::kGrow) ||
        UsesArxCallKind(aArxCalls, ArxCallKind::kKDF);
    if (!aArxCalls.empty() && !aForwardsArxStateParameters) {
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
        AppendUniqueValue(&aReferencedSlots, TwistWorkSpaceSlot::kSourceLane);
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
    if (aUsesSeedArxState || aForwardsArxStateParameters) {
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
        *pStream << "    " << WorkspaceAliasDeclaration(aSlot,
                                                         pIncludeKDFParameterAliases,
                                                         pUseCrossParameters) << '\n';
        AppendUniqueValue(&aDeclaredNames, aAliasName);
        aWroteDeclaration = true;
    }

    std::sort(aReferencedLaneSplits.begin(),
              aReferencedLaneSplits.end(),
              [](const GSymbol &pLeft, const GSymbol &pRight) {
                  if (pLeft.mKey.mSlot != pRight.mKey.mSlot) {
                      return pLeft.mKey.mSlot < pRight.mKey.mSlot;
                  }
                  return pLeft.mKey.mLaneSplit < pRight.mKey.mLaneSplit;
              });
    for (const GSymbol &aBuffer : aReferencedLaneSplits) {
        const std::string aAliasName = BufAliasName(aBuffer);
        if (ContainsText(aDeclaredNames, aAliasName)) {
            continue;
        }
        const std::string aDeclaration =
            LaneSplitAliasDeclaration(
                aBuffer.mKey,
                pUseCrossParameters
            );
        if (aDeclaration.empty()) {
            continue;
        }
        *pStream << "    " << aDeclaration << '\n';
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
        std::string aLine = NormalizeLegacyByteTypeLine(pBranch.GetStringLines()[pIndex]);
        aLine = CollapseLocalArxStateArguments(std::move(aLine));
        if (ShouldSkipExternalArxLine(aArxCalls, aLine)) {
            return true;
        }
        if (ShouldSkipUnusedExternalArxDeclarationLine(aArxCalls, aReferencedScalarVariables, aLine)) {
            return true;
        }
        *pStream << IndentBlock(aLine, 1) << '\n';
        if (aLine.rfind("aWandererK = ", 0U) == 0U) {
            *pStream << '\n';
        }
        return true;
    };

    auto EnsureBlankLine = [&]() {
        const std::string aCurrentText = pStream->str();
        if ((aCurrentText.size() < 2U) ||
            (aCurrentText.compare(aCurrentText.size() - 2U,
                                  2U,
                                  "\n\n") != 0)) {
            *pStream << '\n';
        }
    };

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
            AppendArxCall(*aArxCall,
                          pStream,
                          aForwardsArxStateParameters);
            return true;
        }
        const bool aIsTwistDiffuseBatch =
            IsTwistDiffuseBatch(aParsed.mBatch);
        if (pSkipTwistDiffuseBatches && aIsTwistDiffuseBatch) {
            return true;
        }
        if (aIsTwistDiffuseBatch) {
            EnsureBlankLine();
        }

        std::string aScopeError;
        std::string aScopeBlock = aParsed.mBatch.BuildCppScopeBlock(&aScopeError, false);
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
        if (aIsTwistDiffuseBatch) {
            *pStream << '\n';
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
                      const ArxCallExport *pArxCallH = nullptr,
                      const ArxCallExport *pArxCallI = nullptr,
                      const bool pForceWorkspaceSourceAlias = false,
                      const bool pSkipTwistDiffuseBatches = false,
                      const bool pUseCrossParameters = false,
                      const ArxCallExport *pArxCallJ = nullptr,
                      const ArxCallExport *pArxCallK = nullptr,
                      const ArxCallExport *pArxCallL = nullptr,
                      const ArxCallExport *pArxCallM = nullptr,
                      const ArxCallExport *pArxCallN = nullptr,
                      const ArxCallExport *pArxCallO = nullptr,
                      const ArxCallExport *pArxCallP = nullptr) {
    const std::array<const ArxCallExport *, 16> aCandidates = {
        pArxCallA, pArxCallB, pArxCallC, pArxCallD,
        pArxCallE, pArxCallF, pArxCallG, pArxCallH,
        pArxCallI, pArxCallJ, pArxCallK, pArxCallL,
        pArxCallM, pArxCallN, pArxCallO, pArxCallP,
    };
    std::vector<const ArxCallExport *> aArxCalls;
    for (const ArxCallExport *aCandidate : aCandidates) {
        if (aCandidate != nullptr) {
            aArxCalls.push_back(aCandidate);
        }
    }

    return AppendBranchBodyWithArxCalls(
        pBranch,
        pIncludeKDFParameterAliases,
        pStream,
        pError,
        aArxCalls,
        pForceWorkspaceSourceAlias,
        pSkipTwistDiffuseBatches,
        pUseCrossParameters
    );
}

bool AppendCrossParameterBranchBody(
    const TwistProgramBranch &pBranch,
    std::ostringstream *pStream,
    std::string *pError) {
    return AppendBranchBody(
        pBranch,
        false,
        pStream,
        pError,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        false,
        false,
        true
    );
}

bool ResolveSeedStageConfigs(const std::vector<GSeedRunStageConfig> &pConfigs,
                             std::vector<GSeedRunStageConfig> *pResolved,
                             std::string *pError) {
    if (pResolved == nullptr) {
        SetError(pError, "Seed ARX stage config destination was null.");
        return false;
    }

    *pResolved = pConfigs;
    if (pResolved->size() != 14U) {
        SetError(pError,
                 "Seed ARX export requires exactly fourteen supplied "
                 "stage configs.");
        return false;
    }

    static const std::array<const char *, 14> kStageNames = {
        "GSeedRunSeed_A", "GSeedRunSeed_B", "GSeedRunSeed_C",
        "GSeedRunSeed_D", "GSeedRunSeed_E", "GSeedRunSeed_F",
        "GSeedRunSeed_G", "GSeedRunSeed_H", "GSeedRunSeed_I",
        "GSeedRunSeed_J", "GSeedRunSeed_K", "GSeedRunSeed_L",
        "GSeedRunSeed_M", "GSeedRunSeed_N",
    };
    for (std::size_t i = 0U; i < pResolved->size(); ++i) {
        if ((*pResolved)[i].mStageName != kStageNames[i]) {
            SetError(pError, "Seed ARX stage config order did not match A through N.");
            return false;
        }
    }
    return true;
}

bool ResolveSeedKeyBoxStageConfigs(
    const std::vector<GSeedRunStageConfig> &pConfigs,
    std::vector<GSeedRunStageConfig> *pResolved,
    std::string *pError) {
    if (pResolved == nullptr) {
        SetError(pError,
                 "Seed key-box ARX stage config destination was null.");
        return false;
    }

    *pResolved = pConfigs;
    if (pResolved->size() != 16U) {
        SetError(pError,
                 "Seed key-box ARX export requires exactly sixteen supplied "
                 "KEY stage configs.");
        return false;
    }

    static const std::array<const char *, 16> kStageNames = {
        "GSeedRunKEY_A_A", "GSeedRunKEY_A_B",
        "GSeedRunKEY_A_C", "GSeedRunKEY_A_D",
        "GSeedRunKEY_A_E", "GSeedRunKEY_A_F",
        "GSeedRunKEY_A_G", "GSeedRunKEY_A_H",
        "GSeedRunKEY_B_A", "GSeedRunKEY_B_B",
        "GSeedRunKEY_B_C", "GSeedRunKEY_B_D",
        "GSeedRunKEY_B_E", "GSeedRunKEY_B_F",
        "GSeedRunKEY_B_G", "GSeedRunKEY_B_H",
    };
    static const std::array<const char *, 16> kBatchNames = {
        "key_a_loop_a", "key_a_loop_b",
        "key_a_loop_c", "key_a_loop_d",
        "key_a_loop_e", "key_a_loop_f",
        "key_a_loop_g", "key_a_loop_h",
        "key_b_loop_a", "key_b_loop_b",
        "key_b_loop_c", "key_b_loop_d",
        "key_b_loop_e", "key_b_loop_f",
        "key_b_loop_g", "key_b_loop_h",
    };
    for (std::size_t i = 0U; i < pResolved->size(); ++i) {
        if (((*pResolved)[i].mStageName != kStageNames[i]) ||
            ((*pResolved)[i].mBatchName != kBatchNames[i])) {
            SetError(pError,
                     "Seed key-box ARX stage config order did not match "
                     "KEY_A_A through KEY_B_H.");
            return false;
        }
        if ((*pResolved)[i].mSlices.size() != 1U) {
            SetError(pError,
                     "Each seed key-box ARX stage must contain exactly one loop.");
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
    if (pResolved->size() != 8U) {
        SetError(pError,
                 "Twist ARX export requires exactly eight supplied "
                 "stage configs.");
        return false;
    }

    static const std::array<const char *, 8> kStageNames = {
        "GTwistRunTwist_A", "GTwistRunTwist_B", "GTwistRunTwist_C",
        "GTwistRunTwist_D", "GTwistRunTwist_E", "GTwistRunTwist_F",
        "GTwistRunTwist_G", "GTwistRunTwist_H",
    };
    for (std::size_t i = 0U; i < pResolved->size(); ++i) {
        if ((*pResolved)[i].mStageName != kStageNames[i]) {
            SetError(pError, "Twist ARX stage config order did not match A through H.");
            return false;
        }
    }
    return true;
}

bool ResolveGrowStageConfig(const GSeedRunStageConfig &pConfig,
                            const std::string &pExpectedStageName,
                            GSeedRunStageConfig *pResolved,
                            std::string *pError) {
    if (pResolved == nullptr) {
        SetError(pError, "Grow ARX stage config destination was null.");
        return false;
    }

    *pResolved = pConfig;
    if (pResolved->mStageName != pExpectedStageName) {
        SetError(pError, "Grow ARX stage config name did not match " +
                         pExpectedStageName + ".");
        return false;
    }
    if (!pResolved->mSliceDomains.empty() &&
        (pResolved->mSliceDomains.size() != pResolved->mSlices.size())) {
        SetError(pError, pExpectedStageName +
                         " must retain exactly one domain per slice.");
        return false;
    }

    auto IsActiveDomain = [](const TwistDomain pDomain) {
        return (pDomain == TwistDomain::kKeyRotateA) ||
               (pDomain == TwistDomain::kKeyRotateB) ||
               (pDomain == TwistDomain::kKeySpawnA) ||
               (pDomain == TwistDomain::kKeySpawnB) ||
               (pDomain == TwistDomain::kSeed) ||
               (pDomain == TwistDomain::kTwist);
    };
    if (!IsActiveDomain(pResolved->mDomain)) {
        SetError(pError, pExpectedStageName +
                         " domain must be one of the six active domains.");
        return false;
    }
    for (TwistDomain aDomain : pResolved->mSliceDomains) {
        if (!IsActiveDomain(aDomain)) {
            SetError(pError, pExpectedStageName +
                             " scheduled a retired domain.");
            return false;
        }
    }
    return true;
}

bool ResolveGrowStageConfigs(
    const std::vector<GSeedRunStageConfig> &pConfigs,
    const bool pGrowA,
    std::vector<GSeedRunStageConfig> *pResolved,
    std::string *pError) {
    if (pResolved == nullptr) {
        SetError(pError, "Grow ARX stage config destination was null.");
        return false;
    }

    const std::array<const char *, 5> aExpectedNames = pGrowA ?
        std::array<const char *, 5>{
            "GROW_A_A", "GROW_A_B", "GROW_A_C", "GROW_A_D", "GROW_A_E",
        } :
        std::array<const char *, 5>{
            "GROW_B_A", "GROW_B_B", "GROW_B_C", "GROW_B_D", "GROW_B_E",
        };

    *pResolved = pConfigs;
    if (pResolved->size() != 5U) {
        SetError(pError, pGrowA ?
            "Grow A ARX export requires exactly five supplied stage configs." :
            "Grow B ARX export requires exactly five supplied stage configs.");
        return false;
    }

    for (std::size_t i = 0U; i < pResolved->size(); ++i) {
        GSeedRunStageConfig aValidated;
        if (!ResolveGrowStageConfig((*pResolved)[i],
                                    aExpectedNames[i],
                                    &aValidated,
                                    pError)) {
            return false;
        }
        (*pResolved)[i] = std::move(aValidated);
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
        pBranch->AddLine(NonceDeclareLine(GSymbol::Var(kNonceVariableNames[i])));
    }
    pBranch->AddLine("std::uint64_t aDomainWordIngress = pConstants->mIngress;");
    pBranch->AddLine("std::uint64_t aDomainWordScatter = pConstants->mScatter;");
    pBranch->AddLine("std::uint64_t aDomainWordCross = pConstants->mCross;");
    if (pUsesSource) {
        pBranch->AddLine("std::uint8_t *aSource = pWorkSpace->mSourceLane;");
    }
    pBranch->AddLine("READ_IN_MUTABLE_PARAMS;");
}

void AddExportArxKDF_A_AEpilogue(TwistProgramBranch *pBranch) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("WRITE_OUT_MUTABLE_PARAMS;");
}

void AddExportArxSeedNonceLines(
    TwistProgramBranch *pBranch,
    const GAXSKDiffuseKind pFixedDiffuse) {
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
        pBranch->AddLine(
            NonceDeclareLine(
                GSymbol::Var(kNonceVariableNames[i]),
                pFixedDiffuse
            )
        );
    }
}

void AddExportArxSeedPrologue(TwistProgramBranch *pBranch,
                              const bool pUsesSource,
                              const char *pArxKind) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine(
        std::string("// [") +
        ((pArxKind != nullptr) ? pArxKind : "seed") +
        " arx]"
    );
    if (pUsesSource) {
        pBranch->AddLine("std::uint8_t *aSource = pWorkSpace->mSourceLane;");
    }
    pBranch->AddLine("READ_IN_MUTABLE_PARAMS;");
}

void AddExportArxSeedEpilogue(TwistProgramBranch *pBranch) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("WRITE_OUT_MUTABLE_PARAMS;");
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
    pBranch->AddLine("READ_IN_MUTABLE_PARAMS;");
}

void AddExportArxGrowPrologue(TwistProgramBranch *pBranch) {
    if (pBranch == nullptr) {
        return;
    }

    pBranch->AddLine("// [grow arx]");
    pBranch->AddLine("READ_IN_MUTABLE_PARAMS;");
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
                            StageConfigReferencesSlot(pConfig, TwistWorkSpaceSlot::kSourceLane));

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
                              std::string *pError,
                              const char *pArxKind = "seed",
                              const bool pWriteOutMutableParams = true) {
    if (pBranch == nullptr) {
        SetError(pError, "Seed ARX branch output was null.");
        return false;
    }

    pBranch->Clear();
    AddExportArxSeedPrologue(pBranch,
                             StageConfigReferencesSlot(
                                 pConfig,
                                 TwistWorkSpaceSlot::kSourceLane),
                             pArxKind);
    if (!pConfig.mIgnoreNonces) {
        AddExportArxSeedNonceLines(pBranch,
                                   pConfig.mFixedDiffuse);
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

    if (pWriteOutMutableParams) {
        AddExportArxSeedEpilogue(pBranch);
    }
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
                              StageConfigReferencesSlot(pConfig, TwistWorkSpaceSlot::kSourceLane));

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

[[maybe_unused]] bool BuildExportArxGrow_ABranch(TwistProgramBranch *pBranch,
                                 const GSeedRunStageConfig &pConfig,
                                 std::string *pError) {
    return BuildExportArxGrowBranch(pBranch,
                                    pConfig,
                                    "GROW_A",
                                    pError);
}

[[maybe_unused]] bool BuildExportArxGrow_BBranch(TwistProgramBranch *pBranch,
                                const GSeedRunStageConfig &pConfig,
                                std::string *pError) {
    return BuildExportArxGrowBranch(pBranch,
                                    pConfig,
                                    "GROW_B",
                                    pError);
}

void AppendArxKDFSignature(std::ostringstream *pStream,
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
    << "                     std::uint64_t pNonce,\n"
    << "                     TwistDomainConstants *pConstants,\n"
    << "                     TwistDomainSaltSet *pDomainSaltSet,\n"
    << "                     MUTABLE_PARAMS)" << aSuffix;
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
    *pStream << "                     MUTABLE_PARAMS)" << aSuffix;
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
    << "                     std::uint8_t *pCrossLaneA,\n"
    << "                     std::uint8_t *pCrossLaneB,\n"
    << "                     std::uint8_t *pCrossLaneC,\n"
    << "                     std::uint8_t *pCrossLaneD,\n"
    << "                     MUTABLE_PARAMS)" << aSuffix;
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
    << "                     MUTABLE_PARAMS)" << aSuffix;
}

void AppendKDFSignature(std::ostringstream *pStream,
                        const std::string &pClassName,
                        const std::string &pMethodName,
                        const bool pDefinition) {
    if (pStream == nullptr) {
        return;
    }

    const std::string aPrefix = pDefinition
        ? ("void " + pClassName + "::")
        : "    void ";
    const std::string aSuffix = pDefinition ? " {\n" : " override;\n";
    *pStream
    << aPrefix << pMethodName << "(TwistWorkSpace *pWorkSpace,\n"
    << "               std::uint64_t pNonce,\n"
    << "               TwistDomainConstants *pConstants,\n"
    << "               TwistDomainSaltSet *pDomainSaltSet,\n"
    << "               MUTABLE_PARAMS)" << aSuffix;
}

void AppendKDFMethodPrologue(std::ostringstream *pStream) {
    if (pStream == nullptr) {
        return;
    }

    *pStream
    << "    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||\n"
    << "        (pDomainSaltSet == nullptr) ||\n"
    << "        (pIngress == nullptr) || (pCarry == nullptr) ||\n"
    << "        (pWandererA == nullptr) || (pWandererB == nullptr) ||\n"
    << "        (pWandererC == nullptr) || (pWandererD == nullptr) ||\n"
    << "        (pWandererE == nullptr) || (pWandererF == nullptr) ||\n"
    << "        (pWandererG == nullptr) || (pWandererH == nullptr) ||\n"
    << "        (pWandererI == nullptr) || (pWandererJ == nullptr) ||\n"
    << "        (pWandererK == nullptr)) { return; }\n";
}

void AppendGrowKeySignature(std::ostringstream *pStream,
                            const std::string &pClassName,
                            const std::string &pMethodName,
                            const bool pDefinition) {
    if (pStream == nullptr) {
        return;
    }

    const std::string aPrefix = pDefinition ?
        ("void " + pClassName + "::") :
        "    void ";
    const std::string aSuffix = pDefinition ? " {\n" : " override;\n";
    *pStream
    << aPrefix << pMethodName << "(TwistWorkSpace *pWorkSpace,\n"
    << "                  MUTABLE_PARAMS)" << aSuffix;
}

void AppendGrowKeyCall(std::ostringstream *pStream,
                       const std::string &pMethodName,
                       const bool pForwardParameters) {
    if (pStream == nullptr) {
        return;
    }

    *pStream << "    " << pMethodName << "(pWorkSpace, ";
    if (!pForwardParameters) {
        *pStream << "ARX_STATE_VARS);\n";
    } else {
        *pStream << "MUTABLE_PARAMS_PASSED);\n";
    }
}

bool ExportArxCompanionFiles(const std::string &pRoot,
                             const std::string &pClassName,
                             const std::string &pExpanderName,
                             const std::size_t pCandidateIndex,
                             const std::vector<GSeedRunStageConfig> &pSeedStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pSeedKeyBoxStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pTwistStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pGrowAStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pGrowBStageConfigs,
                             std::string *pError) {
    const std::string aArxClassName = pClassName + "_Arx";
    const std::string aHeaderPath = FileIO::Join(pRoot, aArxClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(pRoot, aArxClassName + ".cpp");

    static const std::array<const char *, 4> kKDFAMethodNames = {
        "KDF_A_A", "KDF_A_B", "KDF_A_C", "KDF_A_D",
    };
    ResidualBucket aKDFResidualBucket;

    const GSeedRunKDF_AConfig::KDFStageConfigs aKDFAConfigs =
        GSeedRunKDF_AConfig::MakeKDF_AConfig(aKDFResidualBucket,
                                             pCandidateIndex);
    std::array<TwistProgramBranch, 4> aBranchesKDFA;
    for (std::size_t i = 0U; i < aBranchesKDFA.size(); ++i) {
        if (!BuildExportArxKDFBranch(&aBranchesKDFA[i],
                                     aKDFAConfigs[i],
                                     kKDFAMethodNames[i],
                                     pError)) {
            return false;
        }
    }

    static const std::array<const char *, 4> kKDFBMethodNames = {
        "KDF_B_A", "KDF_B_B", "KDF_B_C", "KDF_B_D",
    };
    const GSeedRunKDF_BConfig::KDFStageConfigs aKDFBConfigs =
        GSeedRunKDF_BConfig::MakeKDF_BConfig(aKDFResidualBucket,
                                             pCandidateIndex);
    std::array<TwistProgramBranch, 4> aBranchesKDFB;
    for (std::size_t i = 0U; i < aBranchesKDFB.size(); ++i) {
        if (!BuildExportArxKDFBranch(&aBranchesKDFB[i],
                                     aKDFBConfigs[i],
                                     kKDFBMethodNames[i],
                                     pError)) {
            return false;
        }
    }
    static const std::array<const char *, 4> kKDFCMethodNames = {
        "KDF_C_A", "KDF_C_B", "KDF_C_C", "KDF_C_D",
    };
    const GSeedRunKDF_CConfig::KDFStageConfigs aKDFCConfigs =
        GSeedRunKDF_CConfig::MakeKDF_CConfig(aKDFResidualBucket,
                                             pCandidateIndex);
    std::array<TwistProgramBranch, 4> aBranchesKDFC;
    for (std::size_t i = 0U; i < aBranchesKDFC.size(); ++i) {
        if (!BuildExportArxKDFBranch(&aBranchesKDFC[i],
                                     aKDFCConfigs[i],
                                     kKDFCMethodNames[i],
                                     pError)) {
            return false;
        }
    }
    static const std::array<const char *, 4> kKDFDMethodNames = {
        "KDF_D_A", "KDF_D_B", "KDF_D_C", "KDF_D_D",
    };
    const GSeedRunKDF_DConfig::KDFStageConfigs aKDFDConfigs =
        GSeedRunKDF_DConfig::MakeKDF_DConfig(aKDFResidualBucket,
                                             pCandidateIndex);
    std::array<TwistProgramBranch, 4> aBranchesKDFD;
    for (std::size_t i = 0U; i < aBranchesKDFD.size(); ++i) {
        if (!BuildExportArxKDFBranch(&aBranchesKDFD[i],
                                     aKDFDConfigs[i],
                                     kKDFDMethodNames[i],
                                     pError)) {
            return false;
        }
    }
    std::vector<GSeedRunStageConfig> aSeedStageConfigs;
    if (!ResolveSeedStageConfigs(pSeedStageConfigs, &aSeedStageConfigs, pError)) {
        return false;
    }
    static const std::array<const char *, 14> kSeedMethodNames = {
        "SEED_A", "SEED_B", "SEED_C", "SEED_D", "SEED_E",
        "SEED_F", "SEED_G", "SEED_H", "SEED_I", "SEED_J",
        "SEED_K", "SEED_L", "SEED_M", "SEED_N",
    };
    std::array<TwistProgramBranch, 14> aBranchesSeed;
    for (std::size_t i = 0U; i < aBranchesSeed.size(); ++i) {
        if (!BuildExportArxSeedBranch(&aBranchesSeed[i],
                                      aSeedStageConfigs[i],
                                      kSeedMethodNames[i],
                                      pError)) {
            return false;
        }
    }

    std::vector<GSeedRunStageConfig> aSeedKeyBoxStageConfigs;
    if (!ResolveSeedKeyBoxStageConfigs(pSeedKeyBoxStageConfigs,
                                       &aSeedKeyBoxStageConfigs,
                                       pError)) {
        return false;
    }
    static const std::array<const char *, 16> kKeyMethodNames = {
        "KEY_A_A", "KEY_A_B", "KEY_A_C", "KEY_A_D",
        "KEY_A_E", "KEY_A_F", "KEY_A_G", "KEY_A_H",
        "KEY_B_A", "KEY_B_B", "KEY_B_C", "KEY_B_D",
        "KEY_B_E", "KEY_B_F", "KEY_B_G", "KEY_B_H",
    };
    std::array<TwistProgramBranch, 16> aBranchesKEY;
    for (std::size_t i = 0U; i < aBranchesKEY.size(); ++i) {
        if (!BuildExportArxSeedBranch(&aBranchesKEY[i],
                                      aSeedKeyBoxStageConfigs[i],
                                      kKeyMethodNames[i],
                                      pError,
                                      "key",
                                      (i != 7U) && (i != 15U))) {
            return false;
        }
    }

    std::vector<GSeedRunStageConfig> aTwistStageConfigs;
    if (!ResolveTwistStageConfigs(pTwistStageConfigs, &aTwistStageConfigs, pError)) {
        return false;
    }
    static const std::array<const char *, 8> kTwistMethodNames = {
        "TWIST_A", "TWIST_B", "TWIST_C", "TWIST_D",
        "TWIST_E", "TWIST_F", "TWIST_G", "TWIST_H",
    };
    std::array<TwistProgramBranch, 8> aBranchesTwist;
    for (std::size_t i = 0U; i < aBranchesTwist.size(); ++i) {
        if (!BuildExportArxTwistBranch(&aBranchesTwist[i],
                                       aTwistStageConfigs[i],
                                       kTwistMethodNames[i],
                                       pError)) {
            return false;
        }
    }
    std::vector<GSeedRunStageConfig> aGrowAStageConfigs;
    if (!ResolveGrowStageConfigs(pGrowAStageConfigs,
                                 true,
                                 &aGrowAStageConfigs,
                                 pError)) {
        return false;
    }
    static const std::array<const char *, 5> kGrowAMethodNames = {
        "GROW_A_A", "GROW_A_B", "GROW_A_C", "GROW_A_D", "GROW_A_E",
    };
    std::array<TwistProgramBranch, 5> aBranchesGrowA;
    for (std::size_t i = 0U; i < aBranchesGrowA.size(); ++i) {
        if (!BuildExportArxGrowBranch(&aBranchesGrowA[i],
                                      aGrowAStageConfigs[i],
                                      kGrowAMethodNames[i],
                                      pError)) {
            return false;
        }
    }
    std::vector<GSeedRunStageConfig> aGrowBStageConfigs;
    if (!ResolveGrowStageConfigs(pGrowBStageConfigs,
                                 false,
                                 &aGrowBStageConfigs,
                                 pError)) {
        return false;
    }
    static const std::array<const char *, 5> kGrowBMethodNames = {
        "GROW_B_A", "GROW_B_B", "GROW_B_C", "GROW_B_D", "GROW_B_E",
    };
    std::array<TwistProgramBranch, 5> aBranchesGrowB;
    for (std::size_t i = 0U; i < aBranchesGrowB.size(); ++i) {
        if (!BuildExportArxGrowBranch(&aBranchesGrowB[i],
                                      aGrowBStageConfigs[i],
                                      kGrowBMethodNames[i],
                                      pError)) {
            return false;
        }
    }

    std::vector<FlowLoopExport> aFlowLoops;
    for (std::size_t i = 0U; i < aKDFAConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "KDF",
                        "KDF_A",
                        kKDFAMethodNames[i],
                        aKDFAConfigs[i]);
    }
    for (std::size_t i = 0U; i < aKDFBConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "KDF",
                        "KDF_B",
                        kKDFBMethodNames[i],
                        aKDFBConfigs[i]);
    }
    for (std::size_t i = 0U; i < aKDFCConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "KDF",
                        "KDF_C",
                        kKDFCMethodNames[i],
                        aKDFCConfigs[i]);
    }
    for (std::size_t i = 0U; i < aKDFDConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "KDF",
                        "KDF_D",
                        kKDFDMethodNames[i],
                        aKDFDConfigs[i]);
    }
    for (std::size_t i = 0U; i < aSeedStageConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "SEED",
                        "SEED",
                        kSeedMethodNames[i],
                        aSeedStageConfigs[i]);
    }
    for (std::size_t i = 0U; i < aSeedKeyBoxStageConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "KEY",
                        (i < 8U) ? "KEY_A" : "KEY_B",
                        kKeyMethodNames[i],
                        aSeedKeyBoxStageConfigs[i]);
    }
    for (std::size_t i = 0U; i < aTwistStageConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "TWIST",
                        "TWIST",
                        kTwistMethodNames[i],
                        aTwistStageConfigs[i]);
    }
    for (std::size_t i = 0U; i < aGrowAStageConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "GROW",
                        "GROW_A",
                        kGrowAMethodNames[i],
                        aGrowAStageConfigs[i]);
    }
    for (std::size_t i = 0U; i < aGrowBStageConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "GROW",
                        "GROW_B",
                        kGrowBMethodNames[i],
                        aGrowBStageConfigs[i]);
    }

    std::ostringstream aHeader;
    aHeader << "#pragma once\n"
    << "\n"
    << "#include \"TwistExpander.hpp\"\n"
    << "\n"
    << "class " << aArxClassName << " {\n"
    << "public:\n";
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_A", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_B", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_C", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_A_D", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_B_A", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_B_B", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_B_C", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_B_D", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_C_A", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_C_B", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_C_C", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_C_D", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_D_A", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_D_B", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_D_C", false);
    AppendArxKDFSignature(&aHeader, aArxClassName, "KDF_D_D", false);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_A", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_B", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_C", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_D", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_E", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_F", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_G", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_H", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_I", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_J", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_K", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_L", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_M", false, true);
    AppendArxSeedSignature(&aHeader, aArxClassName, "SEED_N", false, true);
    for (const char *aMethodName : kKeyMethodNames) {
        AppendArxSeedSignature(&aHeader,
                               aArxClassName,
                               aMethodName,
                               false);
    }
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_A", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_B", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_C", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_D", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_E", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_F", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_G", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_H", false, false);
    for (const char *aMethodName : kGrowAMethodNames) {
        AppendArxGrowSignature(&aHeader, aArxClassName, aMethodName, false);
    }
    for (const char *aMethodName : kGrowBMethodNames) {
        AppendArxGrowSignature(&aHeader, aArxClassName, aMethodName, false);
    }
    aHeader << "};\n";

    std::ostringstream aCpp;
    aCpp << "#include \"" << aArxClassName << ".hpp\"\n"
    << "#include \"TwistFunctional.hpp\"\n"
    << "#include \"TwistMix32.hpp\"\n"
    << "#include \"TwistMix64.hpp\"\n"
    << "\n"
    << "#include <cstdint>\n"
    << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_A", true);
    if (!AppendBranchBody(aBranchesKDFA[0], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n"
    << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_B", true);
    if (!AppendBranchBody(aBranchesKDFA[1], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_C", true);
    if (!AppendBranchBody(aBranchesKDFA[2], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_A_D", true);
    if (!AppendBranchBody(aBranchesKDFA[3], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_A", true);
    if (!AppendBranchBody(aBranchesKDFB[0], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_B", true);
    if (!AppendBranchBody(aBranchesKDFB[1], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_C", true);
    if (!AppendBranchBody(aBranchesKDFB[2], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_B_D", true);
    if (!AppendBranchBody(aBranchesKDFB[3], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_C_A", true);
    if (!AppendBranchBody(aBranchesKDFC[0], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_C_B", true);
    if (!AppendBranchBody(aBranchesKDFC[1], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_C_C", true);
    if (!AppendBranchBody(aBranchesKDFC[2], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_C_D", true);
    if (!AppendBranchBody(aBranchesKDFC[3], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_D_A", true);
    if (!AppendBranchBody(aBranchesKDFD[0], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_D_B", true);
    if (!AppendBranchBody(aBranchesKDFD[1], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_D_C", true);
    if (!AppendBranchBody(aBranchesKDFD[2], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxKDFSignature(&aCpp, aArxClassName, "KDF_D_D", true);
    if (!AppendBranchBody(aBranchesKDFD[3], true, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_A", true, true);
    if (!AppendBranchBody(aBranchesSeed[0], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_B", true, true);
    if (!AppendBranchBody(aBranchesSeed[1], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_C", true, true);
    if (!AppendBranchBody(aBranchesSeed[2], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_D", true, true);
    if (!AppendBranchBody(aBranchesSeed[3], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_E", true, true);
    if (!AppendBranchBody(aBranchesSeed[4], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_F", true, true);
    if (!AppendBranchBody(aBranchesSeed[5], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_G", true, true);
    if (!AppendBranchBody(aBranchesSeed[6], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_H", true, true);
    if (!AppendBranchBody(aBranchesSeed[7], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_I", true, true);
    if (!AppendBranchBody(aBranchesSeed[8], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_J", true, true);
    if (!AppendBranchBody(aBranchesSeed[9], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_K", true, true);
    if (!AppendBranchBody(aBranchesSeed[10], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_L", true, true);
    if (!AppendBranchBody(aBranchesSeed[11], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_M", true, true);
    if (!AppendBranchBody(aBranchesSeed[12], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxSeedSignature(&aCpp, aArxClassName, "SEED_N", true, true);
    if (!AppendBranchBody(aBranchesSeed[13], false, &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    for (std::size_t i = 0U; i < aBranchesKEY.size(); ++i) {
        AppendArxSeedSignature(&aCpp,
                               aArxClassName,
                               kKeyMethodNames[i],
                               true);
        if (!AppendBranchBody(aBranchesKEY[i],
                              false,
                              &aCpp,
                              pError)) {
            return false;
        }
        aCpp << "}\n";
        aCpp << "\n";
    }
    AppendArxTwistSignature(&aCpp, aArxClassName, "TWIST_A", true, false);
    if (!AppendCrossParameterBranchBody(aBranchesTwist[0], &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "TWIST_B", true, false);
    if (!AppendCrossParameterBranchBody(aBranchesTwist[1], &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "TWIST_C", true, false);
    if (!AppendCrossParameterBranchBody(aBranchesTwist[2], &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "TWIST_D", true, false);
    if (!AppendCrossParameterBranchBody(aBranchesTwist[3], &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "TWIST_E", true, false);
    if (!AppendCrossParameterBranchBody(aBranchesTwist[4], &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "TWIST_F", true, false);
    if (!AppendCrossParameterBranchBody(aBranchesTwist[5], &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "TWIST_G", true, false);
    if (!AppendCrossParameterBranchBody(aBranchesTwist[6], &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    AppendArxTwistSignature(&aCpp, aArxClassName, "TWIST_H", true, false);
    if (!AppendCrossParameterBranchBody(aBranchesTwist[7], &aCpp, pError)) {
        return false;
    }
    aCpp << "}\n";
    aCpp << "\n";
    for (std::size_t i = 0U; i < aBranchesGrowA.size(); ++i) {
        AppendArxGrowSignature(&aCpp,
                               aArxClassName,
                               kGrowAMethodNames[i],
                               true);
        if (!AppendBranchBody(aBranchesGrowA[i],
                              false,
                              &aCpp,
                              pError)) {
            return false;
        }
        aCpp << "}\n\n";
    }
    for (std::size_t i = 0U; i < aBranchesGrowB.size(); ++i) {
        AppendArxGrowSignature(&aCpp,
                               aArxClassName,
                               kGrowBMethodNames[i],
                               true);
        if (!AppendBranchBody(aBranchesGrowB[i],
                              false,
                              &aCpp,
                              pError)) {
            return false;
        }
        aCpp << "}\n";
        if ((i + 1U) != aBranchesGrowB.size()) {
            aCpp << "\n";
        }
    }

    if (!SaveTextFile(aHeaderPath, aHeader.str(), pError)) {
        return false;
    }
    if (!SaveTextFile(aCppPath, aCpp.str(), pError)) {
        return false;
    }
    return SaveFlowJSON(pRoot,
                        pClassName,
                        pExpanderName,
                        pCandidateIndex,
                        aFlowLoops,
                        pError);
}

class GArx {
public:
    bool Bake(const std::string &pRoot,
              const std::string &pClassName,
              const std::string &pExpanderName,
              const std::size_t pCandidateIndex,
              const std::vector<GSeedRunStageConfig> &pSeedStageConfigs,
              const std::vector<GSeedRunStageConfig> &pSeedKeyBoxStageConfigs,
              const std::vector<GSeedRunStageConfig> &pTwistStageConfigs,
              const std::vector<GSeedRunStageConfig> &pGrowAStageConfigs,
              const std::vector<GSeedRunStageConfig> &pGrowBStageConfigs,
              std::string *pError) {
        std::vector<GSeedRunStageConfig> aSeedStageConfigs;
        if (!ResolveSeedStageConfigs(pSeedStageConfigs, &aSeedStageConfigs, pError)) {
            return false;
        }
        std::vector<GSeedRunStageConfig> aSeedKeyBoxStageConfigs;
        if (!ResolveSeedKeyBoxStageConfigs(pSeedKeyBoxStageConfigs,
                                           &aSeedKeyBoxStageConfigs,
                                           pError)) {
            return false;
        }
        std::vector<GSeedRunStageConfig> aTwistStageConfigs;
        if (!ResolveTwistStageConfigs(pTwistStageConfigs, &aTwistStageConfigs, pError)) {
            return false;
        }
        std::vector<GSeedRunStageConfig> aGrowAStageConfigs;
        if (!ResolveGrowStageConfigs(pGrowAStageConfigs,
                                     true,
                                     &aGrowAStageConfigs,
                                     pError)) {
            return false;
        }
        std::vector<GSeedRunStageConfig> aGrowBStageConfigs;
        if (!ResolveGrowStageConfigs(pGrowBStageConfigs,
                                     false,
                                     &aGrowBStageConfigs,
                                     pError)) {
            return false;
        }

        mArxClassName = pClassName + "_Arx";
        const std::array<ArxCallExport *, 4> aKDFACalls = {
            &mKDF_A_A, &mKDF_A_B, &mKDF_A_C, &mKDF_A_D,
        };
        static const std::array<const char *, 4> kKDFAMethodNames = {
            "KDF_A_A", "KDF_A_B", "KDF_A_C", "KDF_A_D",
        };
        static const std::array<const char *, 4> kKDFAStageNames = {
            "GSeedRunKDF_A_A", "GSeedRunKDF_A_B", "GSeedRunKDF_A_C",
            "GSeedRunKDF_A_D",
        };
        static const std::array<const char *, 4> kKDFABatchNames = {
            "kdf_a_loop_a", "kdf_a_loop_b", "kdf_a_loop_c",
            "kdf_a_loop_d",
        };
        for (std::size_t i = 0U; i < aKDFACalls.size(); ++i) {
            ArxCallExport &aCall = *aKDFACalls[i];
            aCall.mKind = ArxCallKind::kKDF;
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
            aCall.mBatchName = kKDFBBatchNames[i];
            aCall.mStartLine = std::string("// ") + kKDFBStageNames[i] + " " +
                kKDFBBatchNames[i] + " (start)";
            aCall.mEndLine = std::string("// ") + kKDFBStageNames[i] + " " +
                kKDFBBatchNames[i] + " (end)";
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kKDFBMethodNames[i];
        }

        const std::array<ArxCallExport *, 4> aKDFCCalls = {
            &mKDF_C_A, &mKDF_C_B, &mKDF_C_C, &mKDF_C_D,
        };
        static const std::array<const char *, 4> kKDFCMethodNames = {
            "KDF_C_A", "KDF_C_B", "KDF_C_C", "KDF_C_D",
        };
        static const std::array<const char *, 4> kKDFCStageNames = {
            "GSeedRunKDF_C_A", "GSeedRunKDF_C_B",
            "GSeedRunKDF_C_C", "GSeedRunKDF_C_D",
        };
        static const std::array<const char *, 4> kKDFCBatchNames = {
            "kdf_c_loop_a", "kdf_c_loop_b", "kdf_c_loop_c", "kdf_c_loop_d",
        };
        for (std::size_t i = 0U; i < aKDFCCalls.size(); ++i) {
            ArxCallExport &aCall = *aKDFCCalls[i];
            aCall.mKind = ArxCallKind::kKDF;
            aCall.mBatchName = kKDFCBatchNames[i];
            aCall.mStartLine = std::string("// ") + kKDFCStageNames[i] + " " +
                kKDFCBatchNames[i] + " (start)";
            aCall.mEndLine = std::string("// ") + kKDFCStageNames[i] + " " +
                kKDFCBatchNames[i] + " (end)";
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kKDFCMethodNames[i];
        }

        const std::array<ArxCallExport *, 4> aKDFDCalls = {
            &mKDF_D_A, &mKDF_D_B, &mKDF_D_C, &mKDF_D_D,
        };
        static const std::array<const char *, 4> kKDFDMethodNames = {
            "KDF_D_A", "KDF_D_B", "KDF_D_C", "KDF_D_D",
        };
        static const std::array<const char *, 4> kKDFDStageNames = {
            "GSeedRunKDF_D_A", "GSeedRunKDF_D_B",
            "GSeedRunKDF_D_C", "GSeedRunKDF_D_D",
        };
        static const std::array<const char *, 4> kKDFDBatchNames = {
            "kdf_d_loop_a", "kdf_d_loop_b", "kdf_d_loop_c", "kdf_d_loop_d",
        };
        for (std::size_t i = 0U; i < aKDFDCalls.size(); ++i) {
            ArxCallExport &aCall = *aKDFDCalls[i];
            aCall.mKind = ArxCallKind::kKDF;
            aCall.mBatchName = kKDFDBatchNames[i];
            aCall.mStartLine = std::string("// ") + kKDFDStageNames[i] + " " +
                kKDFDBatchNames[i] + " (start)";
            aCall.mEndLine = std::string("// ") + kKDFDStageNames[i] + " " +
                kKDFDBatchNames[i] + " (end)";
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kKDFDMethodNames[i];
        }

        const std::array<ArxCallExport *, 14> aSeedCalls = {
            &mSeed_A, &mSeed_B, &mSeed_C, &mSeed_D, &mSeed_E,
            &mSeed_F, &mSeed_G, &mSeed_H, &mSeed_I, &mSeed_J,
            &mSeed_K, &mSeed_L, &mSeed_M, &mSeed_N,
        };
        static const std::array<const char *, 14> kSeedMethodNames = {
            "SEED_A", "SEED_B", "SEED_C", "SEED_D", "SEED_E",
            "SEED_F", "SEED_G", "SEED_H", "SEED_I", "SEED_J",
            "SEED_K", "SEED_L", "SEED_M", "SEED_N",
        };
        for (std::size_t i = 0U; i < aSeedCalls.size(); ++i) {
            ArxCallExport &aCall = *aSeedCalls[i];
            const GSeedRunStageConfig &aConfig = aSeedStageConfigs[i];
            aCall.mKind = ArxCallKind::kSeed;
            aCall.mUsesNonce = true;
            aCall.mUsesCrossLanes = false;
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kSeedMethodNames[i];
        }

        static const std::array<const char *, 16> kKeyMethodNames = {
            "KEY_A_A", "KEY_A_B", "KEY_A_C", "KEY_A_D",
            "KEY_A_E", "KEY_A_F", "KEY_A_G", "KEY_A_H",
            "KEY_B_A", "KEY_B_B", "KEY_B_C", "KEY_B_D",
            "KEY_B_E", "KEY_B_F", "KEY_B_G", "KEY_B_H",
        };
        for (std::size_t i = 0U; i < mKEYs.size(); ++i) {
            ArxCallExport &aCall = mKEYs[i];
            const GSeedRunStageConfig &aConfig =
                aSeedKeyBoxStageConfigs[i];
            aCall.mKind = ArxCallKind::kSeed;
            aCall.mUsesNonce = true;
            aCall.mUsesCrossLanes = false;
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kKeyMethodNames[i];
        }

        const std::array<ArxCallExport *, 8> aTwistCalls = {
            &mTwist_A, &mTwist_B, &mTwist_C, &mTwist_D,
            &mTwist_E, &mTwist_F, &mTwist_G, &mTwist_H,
        };
        static const std::array<const char *, 8> kTwistMethodNames = {
            "TWIST_A", "TWIST_B", "TWIST_C", "TWIST_D",
            "TWIST_E", "TWIST_F", "TWIST_G", "TWIST_H",
        };
        for (std::size_t i = 0U; i < aTwistCalls.size(); ++i) {
            ArxCallExport &aCall = *aTwistCalls[i];
            const GSeedRunStageConfig &aConfig = aTwistStageConfigs[i];
            aCall.mKind = ArxCallKind::kTwist;
            aCall.mUsesNonce = false;
            aCall.mUsesCrossLanes = true;
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kTwistMethodNames[i];
        }

        const std::array<ArxCallExport *, 5> aGrowACalls = {
            &mGrow_A_A, &mGrow_A_B, &mGrow_A_C, &mGrow_A_D, &mGrow_A_E,
        };
        static const std::array<const char *, 5> kGrowAMethodNames = {
            "GROW_A_A", "GROW_A_B", "GROW_A_C", "GROW_A_D", "GROW_A_E",
        };
        const std::array<ArxCallExport *, 5> aGrowBCalls = {
            &mGrow_B_A, &mGrow_B_B, &mGrow_B_C, &mGrow_B_D, &mGrow_B_E,
        };
        static const std::array<const char *, 5> kGrowBMethodNames = {
            "GROW_B_A", "GROW_B_B", "GROW_B_C", "GROW_B_D", "GROW_B_E",
        };
        for (std::size_t i = 0U; i < aGrowACalls.size(); ++i) {
            ArxCallExport &aCall = *aGrowACalls[i];
            const GSeedRunStageConfig &aConfig = aGrowAStageConfigs[i];
            aCall.mKind = ArxCallKind::kGrow;
            aCall.mUsesNonce = false;
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kGrowAMethodNames[i];
        }
        for (std::size_t i = 0U; i < aGrowBCalls.size(); ++i) {
            ArxCallExport &aCall = *aGrowBCalls[i];
            const GSeedRunStageConfig &aConfig = aGrowBStageConfigs[i];
            aCall.mKind = ArxCallKind::kGrow;
            aCall.mUsesNonce = false;
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kGrowBMethodNames[i];
        }

        return ExportArxCompanionFiles(pRoot,
                                       pClassName,
                                       pExpanderName,
                                       pCandidateIndex,
                                       aSeedStageConfigs,
                                       aSeedKeyBoxStageConfigs,
                                       aTwistStageConfigs,
                                       aGrowAStageConfigs,
                                       aGrowBStageConfigs,
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

    const ArxCallExport* KDF_C_A() const {
        return &mKDF_C_A;
    }

    const ArxCallExport* KDF_C_B() const {
        return &mKDF_C_B;
    }

    const ArxCallExport* KDF_C_C() const {
        return &mKDF_C_C;
    }

    const ArxCallExport* KDF_C_D() const {
        return &mKDF_C_D;
    }

    const ArxCallExport* KDF_D_A() const {
        return &mKDF_D_A;
    }

    const ArxCallExport* KDF_D_B() const {
        return &mKDF_D_B;
    }

    const ArxCallExport* KDF_D_C() const {
        return &mKDF_D_C;
    }

    const ArxCallExport* KDF_D_D() const {
        return &mKDF_D_D;
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

    const ArxCallExport* Seed_J() const {
        return &mSeed_J;
    }

    const ArxCallExport* Seed_K() const {
        return &mSeed_K;
    }

    const ArxCallExport* Seed_L() const {
        return &mSeed_L;
    }

    const ArxCallExport* Seed_M() const {
        return &mSeed_M;
    }

    const ArxCallExport* Seed_N() const {
        return &mSeed_N;
    }

    std::vector<const ArxCallExport *> KeyCalls() const {
        std::vector<const ArxCallExport *> aCalls;
        aCalls.reserve(mKEYs.size());
        for (const ArxCallExport &aCall : mKEYs) {
            aCalls.push_back(&aCall);
        }
        return aCalls;
    }

    const ArxCallExport* TWIST_A() const {
        return &mTwist_A;
    }

    const ArxCallExport* TWIST_B() const {
        return &mTwist_B;
    }

    const ArxCallExport* TWIST_C() const {
        return &mTwist_C;
    }

    const ArxCallExport* TWIST_D() const {
        return &mTwist_D;
    }

    const ArxCallExport* TWIST_E() const {
        return &mTwist_E;
    }

    const ArxCallExport* TWIST_F() const {
        return &mTwist_F;
    }

    const ArxCallExport* TWIST_G() const {
        return &mTwist_G;
    }

    const ArxCallExport* TWIST_H() const {
        return &mTwist_H;
    }

    const ArxCallExport* Grow_A_A() const {
        return &mGrow_A_A;
    }

    const ArxCallExport* Grow_A_B() const {
        return &mGrow_A_B;
    }

    const ArxCallExport* Grow_A_C() const {
        return &mGrow_A_C;
    }

    const ArxCallExport* Grow_A_D() const {
        return &mGrow_A_D;
    }

    const ArxCallExport* Grow_A_E() const {
        return &mGrow_A_E;
    }

    const ArxCallExport* Grow_B_A() const {
        return &mGrow_B_A;
    }

    const ArxCallExport* Grow_B_B() const {
        return &mGrow_B_B;
    }

    const ArxCallExport* Grow_B_C() const {
        return &mGrow_B_C;
    }

    const ArxCallExport* Grow_B_D() const {
        return &mGrow_B_D;
    }

    const ArxCallExport* Grow_B_E() const {
        return &mGrow_B_E;
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
    ArxCallExport mKDF_C_A;
    ArxCallExport mKDF_C_B;
    ArxCallExport mKDF_C_C;
    ArxCallExport mKDF_C_D;
    ArxCallExport mKDF_D_A;
    ArxCallExport mKDF_D_B;
    ArxCallExport mKDF_D_C;
    ArxCallExport mKDF_D_D;
    ArxCallExport mSeed_A;
    ArxCallExport mSeed_B;
    ArxCallExport mSeed_C;
    ArxCallExport mSeed_D;
    ArxCallExport mSeed_E;
    ArxCallExport mSeed_F;
    ArxCallExport mSeed_G;
    ArxCallExport mSeed_H;
    ArxCallExport mSeed_I;
    ArxCallExport mSeed_J;
    ArxCallExport mSeed_K;
    ArxCallExport mSeed_L;
    ArxCallExport mSeed_M;
    ArxCallExport mSeed_N;
    std::array<ArxCallExport, 16> mKEYs;
    ArxCallExport mTwist_A;
    ArxCallExport mTwist_B;
    ArxCallExport mTwist_C;
    ArxCallExport mTwist_D;
    ArxCallExport mTwist_E;
    ArxCallExport mTwist_F;
    ArxCallExport mTwist_G;
    ArxCallExport mTwist_H;
    ArxCallExport mGrow_A_A;
    ArxCallExport mGrow_A_B;
    ArxCallExport mGrow_A_C;
    ArxCallExport mGrow_A_D;
    ArxCallExport mGrow_A_E;
    ArxCallExport mGrow_B_A;
    ArxCallExport mGrow_B_B;
    ArxCallExport mGrow_B_C;
    ArxCallExport mGrow_B_D;
    ArxCallExport mGrow_B_E;
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
    aObject["salt_g"] = JsonValue::ArrayValue(UInt64ToJsonArray(pMaterial.mSaltG, S_SALT));
    aObject["salt_h"] = JsonValue::ArrayValue(UInt64ToJsonArray(pMaterial.mSaltH, S_SALT));
    return JsonValue::ObjectValue(std::move(aObject));
}

JsonValue ConstantsToJsonValue(const TwistDomainConstants &pConstants) {
    JsonValue::Object aObject;
    aObject["ingress"] = UInt64ToJsonValue(pConstants.mIngress);
    aObject["scatter"] = UInt64ToJsonValue(pConstants.mScatter);
    aObject["cross"] = UInt64ToJsonValue(pConstants.mCross);
    aObject["matrix_select_a"] = UInt64ToJsonValue(pConstants.mMatrixSelectA);
    aObject["matrix_select_b"] = UInt64ToJsonValue(pConstants.mMatrixSelectB);
    aObject["matrix_unroll_a"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixUnrollA));
    aObject["matrix_unroll_b"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixUnrollB));
    aObject["matrix_arg_aa"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgA));
    aObject["matrix_arg_ab"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgB));
    aObject["matrix_arg_ba"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgC));
    aObject["matrix_arg_bb"] = JsonValue::Number(static_cast<double>(pConstants.mMatrixArgD));
    return JsonValue::ObjectValue(std::move(aObject));
}

[[maybe_unused]] JsonValue DomainBundleToJsonValue(const TwistDomainBundle &pBundle) {
    JsonValue::Object aObject;
    aObject["mats_key_rotate_a_orbiter_assign"] = SeedRoundMaterialToJsonValue(pBundle.mKeyRotateASalts.mOrbiterAssign);
    aObject["mats_key_rotate_a_orbiter_update"] = SeedRoundMaterialToJsonValue(pBundle.mKeyRotateASalts.mOrbiterUpdate);
    aObject["mats_key_rotate_a_wanderer_update"] = SeedRoundMaterialToJsonValue(pBundle.mKeyRotateASalts.mWandererUpdate);
    aObject["mats_key_rotate_b_orbiter_assign"] = SeedRoundMaterialToJsonValue(pBundle.mKeyRotateBSalts.mOrbiterAssign);
    aObject["mats_key_rotate_b_orbiter_update"] = SeedRoundMaterialToJsonValue(pBundle.mKeyRotateBSalts.mOrbiterUpdate);
    aObject["mats_key_rotate_b_wanderer_update"] = SeedRoundMaterialToJsonValue(pBundle.mKeyRotateBSalts.mWandererUpdate);
    aObject["mats_key_spawn_a_orbiter_assign"] = SeedRoundMaterialToJsonValue(pBundle.mKeySpawnASalts.mOrbiterAssign);
    aObject["mats_key_spawn_a_orbiter_update"] = SeedRoundMaterialToJsonValue(pBundle.mKeySpawnASalts.mOrbiterUpdate);
    aObject["mats_key_spawn_a_wanderer_update"] = SeedRoundMaterialToJsonValue(pBundle.mKeySpawnASalts.mWandererUpdate);
    aObject["mats_key_spawn_b_orbiter_assign"] = SeedRoundMaterialToJsonValue(pBundle.mKeySpawnBSalts.mOrbiterAssign);
    aObject["mats_key_spawn_b_orbiter_update"] = SeedRoundMaterialToJsonValue(pBundle.mKeySpawnBSalts.mOrbiterUpdate);
    aObject["mats_key_spawn_b_wanderer_update"] = SeedRoundMaterialToJsonValue(pBundle.mKeySpawnBSalts.mWandererUpdate);
    aObject["mats_seed_orbiter_assign"] = SeedRoundMaterialToJsonValue(pBundle.mSeedSalts.mOrbiterAssign);
    aObject["mats_seed_orbiter_update"] = SeedRoundMaterialToJsonValue(pBundle.mSeedSalts.mOrbiterUpdate);
    aObject["mats_seed_wanderer_update"] = SeedRoundMaterialToJsonValue(pBundle.mSeedSalts.mWandererUpdate);
    aObject["mats_twist_orbiter_assign"] = SeedRoundMaterialToJsonValue(pBundle.mTwistSalts.mOrbiterAssign);
    aObject["mats_twist_orbiter_update"] = SeedRoundMaterialToJsonValue(pBundle.mTwistSalts.mOrbiterUpdate);
    aObject["mats_twist_wanderer_update"] = SeedRoundMaterialToJsonValue(pBundle.mTwistSalts.mWandererUpdate);
    aObject["constants_key_rotate_a"] = ConstantsToJsonValue(pBundle.mKeyRotateAConstants);
    aObject["constants_key_rotate_b"] = ConstantsToJsonValue(pBundle.mKeyRotateBConstants);
    aObject["constants_key_spawn_a"] = ConstantsToJsonValue(pBundle.mKeySpawnAConstants);
    aObject["constants_key_spawn_b"] = ConstantsToJsonValue(pBundle.mKeySpawnBConstants);
    aObject["constants_seed"] = ConstantsToJsonValue(pBundle.mSeedConstants);
    aObject["constants_twist"] = ConstantsToJsonValue(pBundle.mTwistConstants);
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
    *pOut << ",\n";
    AppendUInt64ArrayInitializer(pOut, pMaterial.mSaltG, S_SALT, pIndentLevel + 1);
    *pOut << ",\n";
    AppendUInt64ArrayInitializer(pOut, pMaterial.mSaltH, S_SALT, pIndentLevel + 1);
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
          << "    " << UInt64CppLiteral(pConstants.mMatrixSelectA) << ",\n"
          << "    " << UInt64CppLiteral(pConstants.mMatrixSelectB) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixUnrollA) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixUnrollB) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgA) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgB) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgC) << ",\n"
          << "    " << ByteCppLiteral(pConstants.mMatrixArgD) << "\n"
          << "};\n";
}

std::string DomainBundleStaticDefinitions(const std::string &pClassName,
                                          const TwistDomainBundle &pBundle) {
    std::ostringstream aOut;

    AppendSaltSetDefinition(&aOut, pClassName, "kKeyRotateASalts", pBundle.mKeyRotateASalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kKeyRotateAConstants", pBundle.mKeyRotateAConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kKeyRotateBSalts", pBundle.mKeyRotateBSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kKeyRotateBConstants", pBundle.mKeyRotateBConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kKeySpawnASalts", pBundle.mKeySpawnASalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kKeySpawnAConstants", pBundle.mKeySpawnAConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kKeySpawnBSalts", pBundle.mKeySpawnBSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kKeySpawnBConstants", pBundle.mKeySpawnBConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kSeedSalts", pBundle.mSeedSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kSeedConstants", pBundle.mSeedConstants);
    aOut << '\n';
    AppendSaltSetDefinition(&aOut, pClassName, "kTwistSalts", pBundle.mTwistSalts);
    aOut << '\n';
    AppendConstantsDefinition(&aOut, pClassName, "kTwistConstants", pBundle.mTwistConstants);

    return aOut.str();
}

std::string InbuiltDomainBundleAssignmentLines() {
    std::ostringstream aOut;
    aOut
    << "    mDomainBundleInbuilt.mKeyRotateASalts = kKeyRotateASalts;\n"
    << "    mDomainBundleInbuilt.mKeyRotateAConstants = kKeyRotateAConstants;\n"
    << "    mDomainBundleInbuilt.mKeyRotateBSalts = kKeyRotateBSalts;\n"
    << "    mDomainBundleInbuilt.mKeyRotateBConstants = kKeyRotateBConstants;\n"
    << "    mDomainBundleInbuilt.mKeySpawnASalts = kKeySpawnASalts;\n"
    << "    mDomainBundleInbuilt.mKeySpawnAConstants = kKeySpawnAConstants;\n"
    << "    mDomainBundleInbuilt.mKeySpawnBSalts = kKeySpawnBSalts;\n"
    << "    mDomainBundleInbuilt.mKeySpawnBConstants = kKeySpawnBConstants;\n"
    << "    mDomainBundleInbuilt.mSeedSalts = kSeedSalts;\n"
    << "    mDomainBundleInbuilt.mSeedConstants = kSeedConstants;\n"
    << "    mDomainBundleInbuilt.mTwistSalts = kTwistSalts;\n"
    << "    mDomainBundleInbuilt.mTwistConstants = kTwistConstants;\n";
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
    const std::string aBaseInput = mNameBase.empty() ? "Generated" : mNameBase;
    const std::string aBaseName = SanitizeIdentifier(aBaseInput, "Generated");
    const std::string aClassName = "TwistExpander_" + aBaseName;

    if (!EnsureControlValues(pError)) {
        return false;
    }
    if ((mControlCandidateIndex >= GrowAControl::GeneratedCount()) ||
        (mControlCandidateIndex >= GrowBControl::GeneratedCount())) {
        SetError(pError,
                 "Control candidate index was out of range.");
        return false;
    }
    const std::string aGrowAKeyFold =
        GrowAControl::RenderCandidate(mControlCandidateIndex);
    const std::string aGrowBKeyFold =
        GrowBControl::RenderCandidate(mControlCandidateIndex);
    if (aGrowAKeyFold.empty() ||
        aGrowBKeyFold.empty()) {
        SetError(pError,
                 "Controls failed to render their selected candidate.");
        return false;
    }
    const std::string aSeedDestinationSquash =
        RandomDestinationSquashLine();
    const std::string aTwistDestinationSquash =
        RandomDestinationSquashLine();

    const std::string aRootInput = pRootPath.empty() ? "generated/cpp" : pRootPath;
    const std::string aRoot = ResolveOutputPathFromProjectRoot(aRootInput);

    const std::string aHeaderPath = FileIO::Join(aRoot, aClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(aRoot, aClassName + ".cpp");
    GArx aArx;
    if (!aArx.Bake(aRoot,
                   aClassName,
                   aBaseName,
                   mControlCandidateIndex,
                   mSeedStageConfigs,
                   mSeedKeyBoxStageConfigs,
                   mTwistStageConfigs,
                   mGrowAStageConfigs,
                   mGrowBStageConfigs,
                   pError)) {
        return false;
    }

    GTwistExpander aSnapshot = *this;
    aSnapshot.RefreshTablePointers();
    const TwistProgramBranch &aKDF_ABranch = aSnapshot.mKDF_A;
    const TwistProgramBranch &aKDF_BBranch = aSnapshot.mKDF_B;
    const TwistProgramBranch &aKDF_CBranch = aSnapshot.mKDF_C;
    const TwistProgramBranch &aKDF_DBranch = aSnapshot.mKDF_D;

    std::ostringstream aLegacyGrowKeyA;
    AppendGrowKeySignature(&aLegacyGrowKeyA,
                           aClassName,
                           "GrowKeyA",
                           true);
    aLegacyGrowKeyA
        << "    if ((pWorkSpace == nullptr) || (pIngress == nullptr) ||\n"
        << "        (pCarry == nullptr) ||\n"
        << "        (pWandererA == nullptr) || (pWandererB == nullptr) ||\n"
        << "        (pWandererC == nullptr) || (pWandererD == nullptr) ||\n"
        << "        (pWandererE == nullptr) || (pWandererF == nullptr) ||\n"
        << "        (pWandererG == nullptr) || (pWandererH == nullptr) ||\n"
        << "        (pWandererI == nullptr) || (pWandererJ == nullptr) ||\n"
        << "        (pWandererK == nullptr)) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mGrowKeyA,
                          false,
                          &aLegacyGrowKeyA,
                          pError,
                          aArx.Grow_A_A(),
                          aArx.Grow_A_B(),
                          aArx.Grow_A_C(),
                          aArx.Grow_A_D(),
                          aArx.Grow_A_E())) {
        return false;
    }
    aLegacyGrowKeyA << "}\n";

    const std::string aGrowKeyAMethod = aLegacyGrowKeyA.str();

    std::ostringstream aLegacyGrowKeyB;
    AppendGrowKeySignature(&aLegacyGrowKeyB,
                           aClassName,
                           "GrowKeyB",
                           true);
    aLegacyGrowKeyB
        << "    if ((pWorkSpace == nullptr) || (pIngress == nullptr) ||\n"
        << "        (pCarry == nullptr) ||\n"
        << "        (pWandererA == nullptr) || (pWandererB == nullptr) ||\n"
        << "        (pWandererC == nullptr) || (pWandererD == nullptr) ||\n"
        << "        (pWandererE == nullptr) || (pWandererF == nullptr) ||\n"
        << "        (pWandererG == nullptr) || (pWandererH == nullptr) ||\n"
        << "        (pWandererI == nullptr) || (pWandererJ == nullptr) ||\n"
        << "        (pWandererK == nullptr)) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mGrowKeyB,
                          false,
                          &aLegacyGrowKeyB,
                          pError,
                          aArx.Grow_B_A(),
                          aArx.Grow_B_B(),
                          aArx.Grow_B_C(),
                          aArx.Grow_B_D(),
                          aArx.Grow_B_E())) {
        return false;
    }
    aLegacyGrowKeyB << "}\n";

    const std::string aGrowKeyBMethod = aLegacyGrowKeyB.str();

    std::ostringstream aFoldKeyRowA;
    aFoldKeyRowA << "void " << aClassName << "::FoldKeyRowA(TwistWorkSpace *pWorkSpace) {\n"
                 << "    if (pWorkSpace == nullptr) { return; }\n"
                 << aGrowAKeyFold
                 << "}\n";
    const std::string aFoldKeyRowAMethod = aFoldKeyRowA.str();

    std::ostringstream aFoldKeyRowB;
    aFoldKeyRowB << "void " << aClassName << "::FoldKeyRowB(TwistWorkSpace *pWorkSpace) {\n"
                 << "    if (pWorkSpace == nullptr) { return; }\n"
                 << aGrowBKeyFold
                 << "}\n";
    const std::string aFoldKeyRowBMethod = aFoldKeyRowB.str();

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
    << "\n";
    AppendKDFSignature(&aHeader, aClassName, "KDF_A", false);
    AppendKDFSignature(&aHeader, aClassName, "KDF_B", false);
    AppendKDFSignature(&aHeader, aClassName, "KDF_C", false);
    AppendKDFSignature(&aHeader, aClassName, "KDF_D", false);
    aHeader
    << "    void Seed(TwistWorkSpace *pWorkSpace,\n"
    << "              TwistFarmSalt *pFarmSalt,\n"
    << "              std::uint64_t pNonce,\n"
    << "              std::uint8_t *pPassword,\n"
    << "              std::size_t pPasswordByteLength,\n"
    << "              std::uint8_t *pDestination) override;\n"
    << "    void TwistBlock(TwistWorkSpace *pWorkSpace,\n"
    << "                    std::uint8_t *pSource,\n"
    << "                    std::uint8_t *pCrossLaneA,\n"
    << "                    std::uint8_t *pCrossLaneB,\n"
    << "                    std::uint8_t *pCrossLaneC,\n"
    << "                    std::uint8_t *pCrossLaneD,\n"
    << "                    std::uint8_t *pDestination) override;\n";
    AppendGrowKeySignature(&aHeader,
                           aClassName,
                           "GrowKeyA",
                           false);
    AppendGrowKeySignature(&aHeader,
                           aClassName,
                           "GrowKeyB",
                           false);
    aHeader << "\n"
            << "private:\n";
    aHeader << "    void FoldKeyRowA(TwistWorkSpace *pWorkSpace);\n"
            << "    void FoldKeyRowB(TwistWorkSpace *pWorkSpace);\n";
    aHeader
    << "    static const TwistDomainSaltSet kKeyRotateASalts;\n"
    << "    static const TwistDomainConstants kKeyRotateAConstants;\n"
    << "    static const TwistDomainSaltSet kKeyRotateBSalts;\n"
    << "    static const TwistDomainConstants kKeyRotateBConstants;\n"
    << "    static const TwistDomainSaltSet kKeySpawnASalts;\n"
    << "    static const TwistDomainConstants kKeySpawnAConstants;\n"
    << "    static const TwistDomainSaltSet kKeySpawnBSalts;\n"
    << "    static const TwistDomainConstants kKeySpawnBConstants;\n"
    << "    static const TwistDomainSaltSet kSeedSalts;\n"
    << "    static const TwistDomainConstants kSeedConstants;\n"
    << "    static const TwistDomainSaltSet kTwistSalts;\n"
    << "    static const TwistDomainConstants kTwistConstants;\n"
    << "};\n";

    std::ostringstream aCpp;
    aCpp << "#include \"" << aClassName << ".hpp\"\n"
    << "#include \"TwistDiffuse.hpp\"\n"
    << "#include \"TwistFunctional.hpp\"\n"
    << "#include \"TwistShuffle.hpp\"\n"
    << "#include \"TwistMix32.hpp\"\n"
    << "#include \"TwistMix64.hpp\"\n"
    << "#include \"TwistFarmSalt.hpp\"\n"
    << "#include \"TwistFarm.hpp\"\n"
    << "#include \"TwistSquash.hpp\"\n"
    << "#include \"TwistShiftBox.hpp\"\n"
    << "\n"
    << "#include <cstdint>\n"
    << "#include <cstring>\n"
    << "\n"
    << aClassName << "::" << aClassName << "()\n"
    << ": TwistExpander() {\n";
    aCpp
    << InbuiltDomainBundleAssignmentLines()
    << "    mDomainBundleEphemeral.Zero();\n"
    << "}\n"
    << "\n";
    AppendKDFSignature(&aCpp, aClassName, "KDF_A", true);
    AppendKDFMethodPrologue(&aCpp);
    if (!AppendBranchBody(aKDF_ABranch,
                          true,
                          &aCpp,
                          pError,
                          aArx.KDF_A_A(),
                          aArx.KDF_A_B(),
                          aArx.KDF_A_C(),
                          aArx.KDF_A_D())) {
        return false;
    }
    aCpp << "}\n"
         << "\n";
    AppendKDFSignature(&aCpp, aClassName, "KDF_B", true);
    AppendKDFMethodPrologue(&aCpp);
    if (!AppendBranchBody(aKDF_BBranch,
                          true,
                          &aCpp,
                          pError,
                          aArx.KDF_B_A(),
                          aArx.KDF_B_B(),
                          aArx.KDF_B_C(),
                          aArx.KDF_B_D())) {
        return false;
    }
    aCpp << "}\n"
         << "\n";
    AppendKDFSignature(&aCpp, aClassName, "KDF_C", true);
    AppendKDFMethodPrologue(&aCpp);
    if (!AppendBranchBody(aKDF_CBranch,
                          true,
                          &aCpp,
                          pError,
                          aArx.KDF_C_A(),
                          aArx.KDF_C_B(),
                          aArx.KDF_C_C(),
                          aArx.KDF_C_D())) {
        return false;
    }
    aCpp << "}\n"
         << "\n";
    AppendKDFSignature(&aCpp, aClassName, "KDF_D", true);
    AppendKDFMethodPrologue(&aCpp);
    if (!AppendBranchBody(aKDF_DBranch,
                          true,
                          &aCpp,
                          pError,
                          aArx.KDF_D_A(),
                          aArx.KDF_D_B(),
                          aArx.KDF_D_C(),
                          aArx.KDF_D_D())) {
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
    << "    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr) ||\n"
    << "        (pDestination == nullptr)) { return; }\n"
    << "\n"
    << "    UnrollPassword(pWorkSpace->mSourceLane, pPassword, pPasswordByteLength);\n"
    << "    UnrollNonce(pWorkSpace->mNonceLane, pNonce);\n"
    << InbuiltDomainBundleAssignmentLines()
    << "    mDomainBundleEphemeral.Zero();\n"
    << "    pWorkSpace->mDomainBundle.Zero();\n";
    std::vector<const ArxCallExport *> aSeedArxCalls = {
        aArx.Seed_A(), aArx.Seed_B(), aArx.Seed_C(), aArx.Seed_D(),
        aArx.Seed_E(), aArx.Seed_F(), aArx.Seed_G(), aArx.Seed_H(),
        aArx.Seed_I(), aArx.Seed_J(), aArx.Seed_K(), aArx.Seed_L(),
        aArx.Seed_M(), aArx.Seed_N(),
    };
    const std::vector<const ArxCallExport *> aKeyArxCalls =
        aArx.KeyCalls();
    aSeedArxCalls.insert(aSeedArxCalls.end(),
                         aKeyArxCalls.begin(),
                         aKeyArxCalls.end());
    if (!AppendBranchBodyWithArxCalls(
            aSnapshot.mSeed,
            false,
            &aCpp,
            pError,
            aSeedArxCalls,
            /* pForceWorkspaceSourceAlias = */ false,
            /* pSkipTwistDiffuseBatches = */ false,
            /* pUseCrossParameters = */ false)) {
        return false;
    }
    aCpp << aSeedDestinationSquash
         << "\n";
    AppendGrowKeyCall(&aCpp, "GrowKeyA", false);
    aCpp << "\n"
         << "    FoldKeyRowA(pWorkSpace);\n"
         << "\n";
    AppendGrowKeyCall(&aCpp, "GrowKeyB", false);
    aCpp << "\n"
         << "    FoldKeyRowB(pWorkSpace);\n"
         << "\n"
         << "    pWorkSpace->Zero_PostSeed();\n"
         << "\n"
         << "    Zero_PostSeed();\n"
    << "}\n"
    << "\n"
    << "void " << aClassName << "::TwistBlock(TwistWorkSpace *pWorkSpace,\n"
    << "                                       std::uint8_t *pSource,\n"
    << "                                       std::uint8_t *pCrossLaneA,\n"
    << "                                       std::uint8_t *pCrossLaneB,\n"
    << "                                       std::uint8_t *pCrossLaneC,\n"
    << "                                       std::uint8_t *pCrossLaneD,\n"
    << "                                       std::uint8_t *pDestination) {\n"
    << "    if ((pWorkSpace == nullptr) || (pSource == nullptr) ||\n"
    << "        (pCrossLaneA == nullptr) || (pCrossLaneB == nullptr) ||\n"
    << "        (pCrossLaneC == nullptr) || (pCrossLaneD == nullptr) ||\n"
    << "        (pDestination == nullptr)) { return; }\n";
    if (!AppendBranchBody(aSnapshot.mTwister,
                          false,
                          &aCpp,
                          pError,
                          aArx.TWIST_A(),
                          aArx.TWIST_B(),
                          aArx.TWIST_C(),
                          aArx.TWIST_D(),
                          aArx.TWIST_E(),
                          aArx.TWIST_F(),
                          aArx.TWIST_G(),
                          aArx.TWIST_H(),
                          nullptr,
                          false,
                          /* pSkipTwistDiffuseBatches = */ false,
                          /* pUseCrossParameters = */ true)) {
        return false;
    }
    aCpp << aTwistDestinationSquash
         << "\n";
    AppendGrowKeyCall(&aCpp, "GrowKeyA", false);
    aCpp << "\n"
         << "    FoldKeyRowA(pWorkSpace);\n"
         << "\n";
    AppendGrowKeyCall(&aCpp, "GrowKeyB", false);
    aCpp << "\n"
         << "    FoldKeyRowB(pWorkSpace);\n";
    aCpp << "}\n"
    << "\n"
    << aGrowKeyAMethod
    << "\n"
    << aGrowKeyBMethod
    << "\n"
    << aFoldKeyRowAMethod
    << "\n"
    << aFoldKeyRowBMethod
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

    aRootObject["kdf_c"] = BranchToJsonValue(aSnapshot.mKDF_C, pError);
    if ((pError != nullptr) && !pError->empty()) {
        return false;
    }

    aRootObject["kdf_d"] = BranchToJsonValue(aSnapshot.mKDF_D, pError);
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
