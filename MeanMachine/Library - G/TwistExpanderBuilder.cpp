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

std::string NormalizeScalarName(const std::string &pName) {
    std::size_t aBegin = 0U;
    while ((aBegin < pName.size()) &&
           (std::isspace(static_cast<unsigned char>(pName[aBegin])) != 0)) {
        ++aBegin;
    }

    std::size_t aEnd = pName.size();
    while ((aEnd > aBegin) &&
           (std::isspace(static_cast<unsigned char>(pName[aEnd - 1U])) != 0)) {
        --aEnd;
    }
    if (aBegin >= aEnd) {
        return "";
    }

    std::string aTrimmed = pName.substr(aBegin, aEnd - aBegin);
    while (!aTrimmed.empty() && !IsIdentifierChar(aTrimmed.front())) {
        aTrimmed.erase(aTrimmed.begin());
    }
    while (!aTrimmed.empty() && !IsIdentifierChar(aTrimmed.back())) {
        aTrimmed.pop_back();
    }
    if (aTrimmed.empty()) {
        return "";
    }

    std::size_t aTokenEnd = 0U;
    while ((aTokenEnd < aTrimmed.size()) && IsIdentifierChar(aTrimmed[aTokenEnd])) {
        ++aTokenEnd;
    }
    if (aTokenEnd == 0U) {
        return "";
    }
    return aTrimmed.substr(0U, aTokenEnd);
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

bool TryParseTrailingNumber(const std::string &pText,
                            std::string *pPrefix,
                            std::uint32_t *pNumber) {
    if ((pPrefix == nullptr) || (pNumber == nullptr) || pText.empty()) {
        return false;
    }

    std::size_t aSplit = pText.size();
    while ((aSplit > 0U) &&
           (std::isdigit(static_cast<unsigned char>(pText[aSplit - 1U])) != 0)) {
        --aSplit;
    }
    if ((aSplit == pText.size()) || (aSplit == 0U)) {
        return false;
    }

    std::uint32_t aValue = 0U;
    for (std::size_t i = aSplit; i < pText.size(); ++i) {
        const char aChar = pText[i];
        if ((aChar < '0') || (aChar > '9')) {
            return false;
        }
        aValue = (aValue * 10U) + static_cast<std::uint32_t>(aChar - '0');
    }

    *pPrefix = pText.substr(0U, aSplit);
    *pNumber = aValue;
    return true;
}

bool NaturalScalarNameLess(const std::string &pLeft,
                           const std::string &pRight) {
    std::string aLeftPrefix;
    std::string aRightPrefix;
    std::uint32_t aLeftNumber = 0U;
    std::uint32_t aRightNumber = 0U;

    const bool aLeftHasNumber = TryParseTrailingNumber(pLeft, &aLeftPrefix, &aLeftNumber);
    const bool aRightHasNumber = TryParseTrailingNumber(pRight, &aRightPrefix, &aRightNumber);
    if (aLeftHasNumber && aRightHasNumber && (aLeftPrefix == aRightPrefix)) {
        if (aLeftNumber != aRightNumber) {
            return aLeftNumber < aRightNumber;
        }
    }
    return pLeft < pRight;
}

std::string ScalarFamilyKey(const std::string &pName) {
    if (StartsWithText(pName, "aOrbit")) { return "orbit"; }
    if (StartsWithText(pName, "aWanderer")) { return "wanderer"; }
    if (StartsWithText(pName, "aPlugSalt")) { return "plug_salt"; }
    if (StartsWithText(pName, "aPlugKey")) { return "plug_key"; }
    if (StartsWithText(pName, "aPublic")) { return "public"; }
    if (StartsWithText(pName, "aPrivate")) { return "private"; }
    if (StartsWithText(pName, "aCross")) { return "cross"; }
    if (StartsWithText(pName, "aArg")) { return "arg"; }
    if (StartsWithText(pName, "aKind")) { return "kind"; }
    if (StartsWithText(pName, "aDomain")) { return "domain"; }
    if (StartsWithText(pName, "aHot")) { return "hot"; }
    if (pName == "aCarry") { return "carry"; }
    if (pName == "aPrism") { return "prism"; }
    if (pName == "aWalker") { return "walker"; }
    if (pName == "aReloop") { return "reloop"; }
    return "solo:" + pName;
}

std::vector<std::string> BuildScalarDeclarationLines(const std::vector<std::string> &pScalarVariables) {
    struct ScalarDeclGroup {
        std::string                     mType;
        std::string                     mFamilyKey;
        std::vector<std::string>        mNames;
    };

    std::vector<ScalarDeclGroup> aGroups;
    for (const std::string &aRawName : pScalarVariables) {
        const std::string aName = NormalizeScalarName(aRawName);
        if (aName.empty()) {
            continue;
        }

        const std::string aType = ScalarCppTypeForName(aName);
        const std::string aFamilyKey = ScalarFamilyKey(aName);

        ScalarDeclGroup *aGroup = nullptr;
        for (ScalarDeclGroup &aCandidate : aGroups) {
            if ((aCandidate.mType == aType) && (aCandidate.mFamilyKey == aFamilyKey)) {
                aGroup = &aCandidate;
                break;
            }
        }

        if (aGroup == nullptr) {
            ScalarDeclGroup aNewGroup;
            aNewGroup.mType = aType;
            aNewGroup.mFamilyKey = aFamilyKey;
            aGroups.push_back(std::move(aNewGroup));
            aGroup = &aGroups.back();
        }

        if (std::find(aGroup->mNames.begin(), aGroup->mNames.end(), aName) == aGroup->mNames.end()) {
            aGroup->mNames.push_back(aName);
        }
    }

    std::vector<std::string> aLines;
    for (ScalarDeclGroup &aGroup : aGroups) {
        std::sort(aGroup.mNames.begin(), aGroup.mNames.end(), NaturalScalarNameLess);

        static const std::size_t kMaxNamesPerLine = 6U;
        for (std::size_t aStart = 0U; aStart < aGroup.mNames.size(); aStart += kMaxNamesPerLine) {
            const std::size_t aEnd = std::min(aGroup.mNames.size(), aStart + kMaxNamesPerLine);
            std::string aLine = aGroup.mType + " " + aGroup.mNames[aStart] + " = 0";
            for (std::size_t i = aStart + 1U; i < aEnd; ++i) {
                aLine += ", " + aGroup.mNames[i] + " = 0";
            }
            aLine += ";";
            aLines.push_back(std::move(aLine));
        }
    }

    return aLines;
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

std::string TrailingIdentifierToken(const std::string &pText) {
    const std::string aTrimmed = TrimText(pText);
    if (aTrimmed.empty()) {
        return "";
    }

    std::size_t aEnd = aTrimmed.size();
    while ((aEnd > 0U) && !IsIdentifierChar(aTrimmed[aEnd - 1U])) {
        --aEnd;
    }
    if (aEnd == 0U) {
        return "";
    }

    std::size_t aStart = aEnd;
    while ((aStart > 0U) && IsIdentifierChar(aTrimmed[aStart - 1U])) {
        --aStart;
    }
    if (aStart == aEnd) {
        return "";
    }

    return aTrimmed.substr(aStart, aEnd - aStart);
}

void CollectDeclaredIdentifiersFromLine(const std::string &pLine,
                                        std::vector<std::string> *pDeclaredNames) {
    if (pDeclaredNames == nullptr) {
        return;
    }

    std::string aText = TrimText(pLine);
    if (aText.empty()) {
        return;
    }
    if (aText.back() == ';') {
        aText.pop_back();
    }

    if (aText.find('=') == std::string::npos) {
        return;
    }

    int aDepth = 0;
    std::size_t aSegmentStart = 0U;
    for (std::size_t i = 0U; i <= aText.size(); ++i) {
        const bool aAtEnd = (i == aText.size());
        const char aChar = aAtEnd ? '\0' : aText[i];
        if (!aAtEnd) {
            if (aChar == '(') {
                aDepth += 1;
            } else if ((aChar == ')') && (aDepth > 0)) {
                aDepth -= 1;
            }
        }

        if (!aAtEnd && ((aChar != ',') || (aDepth != 0))) {
            continue;
        }

        const std::string aSegment = aText.substr(aSegmentStart, i - aSegmentStart);
        const std::size_t aEquals = aSegment.find('=');
        if (aEquals != std::string::npos) {
            const std::string aName = NormalizeScalarName(TrailingIdentifierToken(aSegment.substr(0U, aEquals)));
            if (!aName.empty()) {
                AppendUniqueValue(pDeclaredNames, aName);
            }
        }

        aSegmentStart = i + 1U;
    }
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
}

std::string WorkspaceAliasDeclaration(const TwistWorkSpaceSlot pSlot) {
    const std::string aAlias = BufAliasName(pSlot);
    const std::string aPrefixBytes = "[[maybe_unused]] std::uint8_t *" + aAlias + " = ";
    const std::string aPrefixWide = "[[maybe_unused]] std::uint64_t *" + aAlias + " = ";
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSource:
            return "std::uint8_t *" + aAlias + " = pSource;";
        case TwistWorkSpaceSlot::kDest:
            return "std::uint8_t *" + aAlias + " = pDestination;";

        case TwistWorkSpaceSlot::kSaltA: return "";
        case TwistWorkSpaceSlot::kSaltB: return "";
        case TwistWorkSpaceSlot::kSaltC: return "";
        case TwistWorkSpaceSlot::kSaltD: return "";
        case TwistWorkSpaceSlot::kSaltE: return "";
        case TwistWorkSpaceSlot::kSaltF: return "";
        case TwistWorkSpaceSlot::kSaltG: return "";
        case TwistWorkSpaceSlot::kSaltH: return "";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxA: return "";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxB: return "";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxC: return "";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxD: return "";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxE: return "";
        case TwistWorkSpaceSlot::kDomainSaltKeyBoxF: return "";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxA: return "";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxB: return "";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxC: return "";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxD: return "";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxE: return "";
        case TwistWorkSpaceSlot::kDomainSaltMaskBoxF: return "";
        case TwistWorkSpaceSlot::kDomainSaltWandererA: return "";
        case TwistWorkSpaceSlot::kDomainSaltWandererB: return "";
        case TwistWorkSpaceSlot::kDomainSaltWandererC: return "";
        case TwistWorkSpaceSlot::kDomainSaltWandererD: return "";
        case TwistWorkSpaceSlot::kDomainSaltWandererE: return "";
        case TwistWorkSpaceSlot::kDomainSaltWandererF: return "";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterA: return "";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterB: return "";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterC: return "";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterD: return "";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterE: return "";
        case TwistWorkSpaceSlot::kDomainSaltOrbiterF: return "";
        case TwistWorkSpaceSlot::kDomainSaltPrismA: return "";
        case TwistWorkSpaceSlot::kDomainSaltPrismB: return "";
        case TwistWorkSpaceSlot::kDomainSaltPrismC: return "";
        case TwistWorkSpaceSlot::kDomainSaltPrismD: return "";
        case TwistWorkSpaceSlot::kDomainSaltPrismE: return "";
        case TwistWorkSpaceSlot::kDomainSaltPrismF: return "";
        case TwistWorkSpaceSlot::kDomainSaltSourceA: return "";
        case TwistWorkSpaceSlot::kDomainSaltSourceB: return "";
        case TwistWorkSpaceSlot::kDomainSaltSourceC: return "";
        case TwistWorkSpaceSlot::kDomainSaltSourceD: return "";
        case TwistWorkSpaceSlot::kDomainSaltSourceE: return "";
        case TwistWorkSpaceSlot::kDomainSaltSourceF: return "";
        case TwistWorkSpaceSlot::kDerivedSaltA: return aPrefixWide + "pWorkspace->mDerivedSaltA;";
        case TwistWorkSpaceSlot::kDerivedSaltB: return aPrefixWide + "pWorkspace->mDerivedSaltB;";
        case TwistWorkSpaceSlot::kDerivedSaltC: return aPrefixWide + "pWorkspace->mDerivedSaltC;";
        case TwistWorkSpaceSlot::kDerivedSaltD: return aPrefixWide + "pWorkspace->mDerivedSaltD;";
        case TwistWorkSpaceSlot::kDerivedSaltE: return aPrefixWide + "pWorkspace->mDerivedSaltE;";
        case TwistWorkSpaceSlot::kDerivedSaltF: return aPrefixWide + "pWorkspace->mDerivedSaltF;";
        case TwistWorkSpaceSlot::kDerivedSaltG: return aPrefixWide + "pWorkspace->mDerivedSaltG;";
        case TwistWorkSpaceSlot::kDerivedSaltH: return aPrefixWide + "pWorkspace->mDerivedSaltH;";

        case TwistWorkSpaceSlot::kSBoxA: return "";
        case TwistWorkSpaceSlot::kSBoxB: return "";
        case TwistWorkSpaceSlot::kSBoxC: return "";
        case TwistWorkSpaceSlot::kSBoxD: return "";
        case TwistWorkSpaceSlot::kSBoxE: return "";
        case TwistWorkSpaceSlot::kSBoxF: return "";
        case TwistWorkSpaceSlot::kSBoxG: return "";
        case TwistWorkSpaceSlot::kSBoxH: return "";
        case TwistWorkSpaceSlot::kDerivedSBoxA: return aPrefixBytes + "pWorkspace->mDerivedSBoxA;";
        case TwistWorkSpaceSlot::kDerivedSBoxB: return aPrefixBytes + "pWorkspace->mDerivedSBoxB;";
        case TwistWorkSpaceSlot::kDerivedSBoxC: return aPrefixBytes + "pWorkspace->mDerivedSBoxC;";
        case TwistWorkSpaceSlot::kDerivedSBoxD: return aPrefixBytes + "pWorkspace->mDerivedSBoxD;";
        case TwistWorkSpaceSlot::kDerivedSBoxE: return aPrefixBytes + "pWorkspace->mDerivedSBoxE;";
        case TwistWorkSpaceSlot::kDerivedSBoxF: return aPrefixBytes + "pWorkspace->mDerivedSBoxF;";
        case TwistWorkSpaceSlot::kDerivedSBoxG: return aPrefixBytes + "pWorkspace->mDerivedSBoxG;";
        case TwistWorkSpaceSlot::kDerivedSBoxH: return aPrefixBytes + "pWorkspace->mDerivedSBoxH;";

        case TwistWorkSpaceSlot::kSeedExpansionLaneA: return aPrefixBytes + "pWorkspace->mExpandLaneA;";
        case TwistWorkSpaceSlot::kSeedExpansionLaneB: return aPrefixBytes + "pWorkspace->mExpandLaneB;";
        case TwistWorkSpaceSlot::kSeedExpansionLaneC: return aPrefixBytes + "pWorkspace->mExpandLaneC;";
        case TwistWorkSpaceSlot::kSeedExpansionLaneD: return aPrefixBytes + "pWorkspace->mExpandLaneD;";

        case TwistWorkSpaceSlot::kWorkLaneA: return aPrefixBytes + "pWorkspace->mWorkLaneA;";
        case TwistWorkSpaceSlot::kWorkLaneB: return aPrefixBytes + "pWorkspace->mWorkLaneB;";
        case TwistWorkSpaceSlot::kWorkLaneC: return aPrefixBytes + "pWorkspace->mWorkLaneC;";
        case TwistWorkSpaceSlot::kWorkLaneD: return aPrefixBytes + "pWorkspace->mWorkLaneD;";

        case TwistWorkSpaceSlot::kOperationLaneA: return aPrefixBytes + "pWorkspace->mOperationLaneA;";
        case TwistWorkSpaceSlot::kOperationLaneB: return aPrefixBytes + "pWorkspace->mOperationLaneB;";

        case TwistWorkSpaceSlot::kMaskLaneA: return aPrefixBytes + "pWorkspace->mMaskLaneA;";
        case TwistWorkSpaceSlot::kMaskLaneB: return aPrefixBytes + "pWorkspace->mMaskLaneB;";

        case TwistWorkSpaceSlot::kKeyBoxUnrolledA: return aPrefixBytes + "&(pWorkspace->mKeyBoxA[0][0]);";
        case TwistWorkSpaceSlot::kKeyBoxUnrolledB: return aPrefixBytes + "&(pWorkspace->mKeyBoxB[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowReadA: return aPrefixBytes + "&(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]);";
        case TwistWorkSpaceSlot::kKeyRowReadB: return aPrefixBytes + "&(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]);";
        case TwistWorkSpaceSlot::kKeyRowWriteA: return aPrefixBytes + "&(pWorkspace->mKeyBoxA[0][0]);";
        case TwistWorkSpaceSlot::kKeyRowWriteB: return aPrefixBytes + "&(pWorkspace->mKeyBoxB[0][0]);";

        case TwistWorkSpaceSlot::kMaskBoxUnrolledA: return aPrefixBytes + "&(pWorkspace->mMaskBoxA[0][0]);";
        case TwistWorkSpaceSlot::kMaskBoxUnrolledB: return aPrefixBytes + "&(pWorkspace->mMaskBoxB[0][0]);";
        case TwistWorkSpaceSlot::kMaskRowReadA: return aPrefixBytes + "&(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]);";
        case TwistWorkSpaceSlot::kMaskRowReadB: return aPrefixBytes + "&(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]);";
        case TwistWorkSpaceSlot::kMaskRowWriteA: return aPrefixBytes + "&(pWorkspace->mMaskBoxA[0][0]);";
        case TwistWorkSpaceSlot::kMaskRowWriteB: return aPrefixBytes + "&(pWorkspace->mMaskBoxB[0][0]);";

        default:
            return aPrefixBytes +
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
        CollectDeclaredIdentifiersFromLine(aNormalizedLine, &aDeclaredNames);
    }
    // Function parameters are already declared by signature.
    AppendUniqueValue(&aDeclaredNames, std::string("pSource"));
    AppendUniqueValue(&aDeclaredNames, std::string("pDestination"));

    std::vector<std::string> aLoopVariables;
    std::vector<std::string> aScalarVariables;
    std::vector<TwistWorkSpaceSlot> aReferencedSlots;
    for (const GBatch &aBatch : aBatches) {
        if (!aBatch.mWorkItems.empty()) {
            for (const GBatchWorkItem &aItem : aBatch.mWorkItems) {
                if (aItem.IsLoop()) {
                    if (!aItem.mLoop.mLoopVariableName.empty()) {
                        const std::string aLoopName = NormalizeScalarName(aItem.mLoop.mLoopVariableName);
                        if (!aLoopName.empty()) {
                            AppendUniqueValue(&aLoopVariables, aLoopName);
                        }
                    }
                    continue;
                }
                if (aItem.IsWhile()) {
                    for (const GWhileWorkItem &aWhileItem : aItem.mWhile.mWorkItems) {
                        if (aWhileItem.IsLoop() && !aWhileItem.mLoop.mLoopVariableName.empty()) {
                            const std::string aLoopName = NormalizeScalarName(aWhileItem.mLoop.mLoopVariableName);
                            if (!aLoopName.empty()) {
                                AppendUniqueValue(&aLoopVariables, aLoopName);
                            }
                        }
                    }
                }
            }
        } else {
            for (const GLoop &aLoop : aBatch.mLoops) {
                if (!aLoop.mLoopVariableName.empty()) {
                    const std::string aLoopName = NormalizeScalarName(aLoop.mLoopVariableName);
                    if (!aLoopName.empty()) {
                        AppendUniqueValue(&aLoopVariables, aLoopName);
                    }
                }
            }
        }
        for (const std::string &aRawName : aBatch.CollectVariableNames()) {
            const std::string aName = NormalizeScalarName(aRawName);
            if (!aName.empty()) {
                AppendUniqueValue(&aScalarVariables, aName);
            }
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

    const std::vector<std::string> aScalarDeclarationLines = BuildScalarDeclarationLines(aScalarVariables);
    for (const std::string &aDeclarationLine : aScalarDeclarationLines) {
        *pStream << "    " << aDeclarationLine << '\n';
        aWroteDeclaration = true;
    }

    if (aWroteDeclaration) {
        *pStream << '\n';
    }

    bool aEmittedBatch = false;

    const std::vector<TwistProgramBranchStep> &aSteps = pBranch.GetSteps();
    if (aSteps.empty()) {
        for (const GBatch &aBatch : aBatches) {
            const bool aInsertLeadingBlankLine = (!aEmittedBatch && !aWroteDeclaration);
            if (!AppendBatchBlock(aBatch,
                                  pStream,
                                  pErrorMessage,
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

            const bool aInsertLeadingBlankLine = (!aEmittedBatch && !aWroteDeclaration);
            if (!AppendBatchBlock(aBatches[aStep.mIndex],
                                  pStream,
                                  pErrorMessage,
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
    aOut << "const std::uint8_t " << pName;
    if (!pLenToken.empty()) {
        aOut << "[" << pLenToken << "]";
    }
    aOut << " = {\n";

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

std::string UInt64ToCppArray(const std::vector<std::uint64_t> &pValues,
                             const std::string &pName,
                             const std::string &pLenToken) {
    std::ostringstream aOut;
    aOut << "const std::uint64_t " << pName;
    if (!pLenToken.empty()) {
        aOut << "[" << pLenToken << "]";
    }
    aOut << " = {\n";

    for (std::size_t i = 0; i < pValues.size(); ++i) {
        if ((i % 4U) == 0U) {
            aOut << "    ";
        }

        char aHex[32];
        std::snprintf(aHex, sizeof(aHex), "0x%016llXULL",
                      static_cast<unsigned long long>(pValues[i]));
        aOut << aHex;

        if (i + 1U < pValues.size()) {
            aOut << ", ";
        }

        if ((i % 4U) == 3U || (i + 1U == pValues.size())) {
            aOut << '\n';
        }
    }

    aOut << "};\n";
    return aOut.str();
}

std::string UInt64Literal(const std::uint64_t pValue) {
    char aHex[32];
    std::snprintf(aHex, sizeof(aHex), "0x%016llXULL",
                  static_cast<unsigned long long>(pValue));
    return std::string(aHex);
}

JsonValue::Array BytesToJsonArray(const std::vector<std::uint8_t> &pBytes) {
    JsonValue::Array aOut;
    aOut.reserve(pBytes.size());
    for (std::uint8_t aByte : pBytes) {
        aOut.push_back(JsonValue::Number(static_cast<double>(aByte)));
    }
    return aOut;
}

JsonValue::Array UInt64ToJsonArray(const std::vector<std::uint64_t> &pValues) {
    JsonValue::Array aOut;
    aOut.reserve(pValues.size());
    for (std::uint64_t aValue : pValues) {
        aOut.push_back(JsonValue::String(std::to_string(aValue)));
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
    const bool aInternalWideSaltField = StartsWithText(pWorkspaceFieldName, "mSalt");
    const bool aWideSaltField = pWorkspaceFieldName.find("DerivedSalt") != std::string::npos;
    const std::string aType = aWideSaltField ? "std::uint64_t *" : "std::uint8_t *";
    if (aInternalExpanderTable) {
        AddLine(std::string(aInternalWideSaltField ? "std::uint64_t *" : "std::uint8_t *") +
                pAliasName + " = " + pWorkspaceFieldName + ";");
    } else {
        AddLine(aType + pAliasName + " = pWorkspace->" + pWorkspaceFieldName + ";");
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

    struct DomainSaltExportEntry {
        const char *mSuffix;
        const std::uint64_t *mValues;
    };

    const DomainSaltExportEntry aDomainSaltEntries[] = {
        {"KeyBoxA", aSnapshot.mDomainSaltKeyBoxA},
        {"KeyBoxB", aSnapshot.mDomainSaltKeyBoxB},
        {"KeyBoxC", aSnapshot.mDomainSaltKeyBoxC},
        {"KeyBoxD", aSnapshot.mDomainSaltKeyBoxD},
        {"KeyBoxE", aSnapshot.mDomainSaltKeyBoxE},
        {"KeyBoxF", aSnapshot.mDomainSaltKeyBoxF},

        {"MaskBoxA", aSnapshot.mDomainSaltMaskBoxA},
        {"MaskBoxB", aSnapshot.mDomainSaltMaskBoxB},
        {"MaskBoxC", aSnapshot.mDomainSaltMaskBoxC},
        {"MaskBoxD", aSnapshot.mDomainSaltMaskBoxD},
        {"MaskBoxE", aSnapshot.mDomainSaltMaskBoxE},
        {"MaskBoxF", aSnapshot.mDomainSaltMaskBoxF},

        {"WandererA", aSnapshot.mDomainSaltWandererA},
        {"WandererB", aSnapshot.mDomainSaltWandererB},
        {"WandererC", aSnapshot.mDomainSaltWandererC},
        {"WandererD", aSnapshot.mDomainSaltWandererD},
        {"WandererE", aSnapshot.mDomainSaltWandererE},
        {"WandererF", aSnapshot.mDomainSaltWandererF},

        {"OrbiterA", aSnapshot.mDomainSaltOrbiterA},
        {"OrbiterB", aSnapshot.mDomainSaltOrbiterB},
        {"OrbiterC", aSnapshot.mDomainSaltOrbiterC},
        {"OrbiterD", aSnapshot.mDomainSaltOrbiterD},
        {"OrbiterE", aSnapshot.mDomainSaltOrbiterE},
        {"OrbiterF", aSnapshot.mDomainSaltOrbiterF},

        {"PrismA", aSnapshot.mDomainSaltPrismA},
        {"PrismB", aSnapshot.mDomainSaltPrismB},
        {"PrismC", aSnapshot.mDomainSaltPrismC},
        {"PrismD", aSnapshot.mDomainSaltPrismD},
        {"PrismE", aSnapshot.mDomainSaltPrismE},
        {"PrismF", aSnapshot.mDomainSaltPrismF},

        {"SourceA", aSnapshot.mDomainSaltSourceA},
        {"SourceB", aSnapshot.mDomainSaltSourceB},
        {"SourceC", aSnapshot.mDomainSaltSourceC},
        {"SourceD", aSnapshot.mDomainSaltSourceD},
        {"SourceE", aSnapshot.mDomainSaltSourceE},
        {"SourceF", aSnapshot.mDomainSaltSourceF}
    };

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
            << "    void KDF(TwistDomain pDomain,\n"
            << "             std::uint64_t pDomainConstantPublicIngress,\n"
            << "             std::uint64_t pDomainConstantPrivateIngress,\n"
            << "             std::uint64_t pDomainConstantCrossIngress,\n"
            << "             std::uint64_t *pDomainSaltA,\n"
            << "             std::uint64_t *pDomainSaltB,\n"
            << "             std::uint64_t *pDomainSaltC,\n"
            << "             std::uint64_t *pDomainSaltD,\n"
            << "             std::uint64_t *pDomainSaltE,\n"
            << "             std::uint64_t *pDomainSaltF) override;\n"
            << "    void Seed(TwistWorkSpace *pWorkspace,\n"
            << "              TwistCryptoGenerator *pCryptoGenerator,\n"
            << "              TwistFarmSBox *pFarmSBox,\n"
            << "              TwistFarmSalt *pFarmSalt,\n"
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
            << "    static const std::uint8_t kSBoxE[S_SBOX];\n"
            << "    static const std::uint8_t kSBoxF[S_SBOX];\n"
            << "    static const std::uint8_t kSBoxG[S_SBOX];\n"
            << "    static const std::uint8_t kSBoxH[S_SBOX];\n"
            << "    static const std::uint64_t kSaltA[S_SALT];\n"
            << "    static const std::uint64_t kSaltB[S_SALT];\n"
            << "    static const std::uint64_t kSaltC[S_SALT];\n"
            << "    static const std::uint64_t kSaltD[S_SALT];\n"
            << "    static const std::uint64_t kSaltE[S_SALT];\n"
            << "    static const std::uint64_t kSaltF[S_SALT];\n"
            << "    static const std::uint64_t kSaltG[S_SALT];\n"
            << "    static const std::uint64_t kSaltH[S_SALT];\n"
            << "    static const std::uint64_t kDomainConstantPublicIngress;\n"
            << "    static const std::uint64_t kDomainConstantPrivateIngress;\n"
            << "    static const std::uint64_t kDomainConstantCrossIngress;\n";
    for (const DomainSaltExportEntry &aDomainSaltEntry : aDomainSaltEntries) {
        aHeader << "    static const std::uint64_t kDomainSalt" << aDomainSaltEntry.mSuffix << "[S_SALT];\n";
    }
    aHeader << "};\n";

    std::ostringstream aCpp;
    aCpp << "#include \"" << aClassName << ".hpp\"\n"
         << "#include \"TwistFunctional.hpp\"\n"
         << "#include \"TwistMasking.hpp\"\n"
         << "#include \"TwistMix64.hpp\"\n"
         << "#include \"TwistSnow.hpp\"\n"
         << "#include \"TwistMemory.hpp\"\n"
         << "#include \"TwistCryptoGenerator.hpp\"\n"
         << "#include \"TwistFarmSBox.hpp\"\n"
         << "#include \"TwistFarmSalt.hpp\"\n"
         << "\n"
         << "#include <cstring>\n"
         << '\n'
         << aClassName << "::" << aClassName << "()\n"
         << ": TwistExpander() {\n"
         << "    std::memcpy(mSBoxA, kSBoxA, sizeof(mSBoxA));\n"
         << "    std::memcpy(mSBoxB, kSBoxB, sizeof(mSBoxB));\n"
         << "    std::memcpy(mSBoxC, kSBoxC, sizeof(mSBoxC));\n"
         << "    std::memcpy(mSBoxD, kSBoxD, sizeof(mSBoxD));\n"
         << "    std::memcpy(mSBoxE, kSBoxE, sizeof(mSBoxE));\n"
         << "    std::memcpy(mSBoxF, kSBoxF, sizeof(mSBoxF));\n"
         << "    std::memcpy(mSBoxG, kSBoxG, sizeof(mSBoxG));\n"
         << "    std::memcpy(mSBoxH, kSBoxH, sizeof(mSBoxH));\n"
         << "    std::memcpy(mSaltA, kSaltA, sizeof(mSaltA));\n"
         << "    std::memcpy(mSaltB, kSaltB, sizeof(mSaltB));\n"
         << "    std::memcpy(mSaltC, kSaltC, sizeof(mSaltC));\n"
         << "    std::memcpy(mSaltD, kSaltD, sizeof(mSaltD));\n"
         << "    std::memcpy(mSaltE, kSaltE, sizeof(mSaltE));\n"
         << "    std::memcpy(mSaltF, kSaltF, sizeof(mSaltF));\n"
         << "    std::memcpy(mSaltG, kSaltG, sizeof(mSaltG));\n"
         << "    std::memcpy(mSaltH, kSaltH, sizeof(mSaltH));\n"
         << "    mDomainConstantPublicIngress = kDomainConstantPublicIngress;\n"
         << "    mDomainConstantPrivateIngress = kDomainConstantPrivateIngress;\n"
         << "    mDomainConstantCrossIngress = kDomainConstantCrossIngress;\n";
    for (const DomainSaltExportEntry &aDomainSaltEntry : aDomainSaltEntries) {
        aCpp << "    std::memcpy(mDomainSalt" << aDomainSaltEntry.mSuffix
             << ", kDomainSalt" << aDomainSaltEntry.mSuffix
             << ", sizeof(mDomainSalt" << aDomainSaltEntry.mSuffix << "));\n";
    }
    aCpp << "}\n"
         << "\n"
         << "void " << aClassName << "::KDF(TwistDomain pDomain,\n"
         << "                                std::uint64_t pDomainConstantPublicIngress,\n"
         << "                                std::uint64_t pDomainConstantPrivateIngress,\n"
         << "                                std::uint64_t pDomainConstantCrossIngress,\n"
         << "                                std::uint64_t *pDomainSaltA,\n"
         << "                                std::uint64_t *pDomainSaltB,\n"
         << "                                std::uint64_t *pDomainSaltC,\n"
         << "                                std::uint64_t *pDomainSaltD,\n"
         << "                                std::uint64_t *pDomainSaltE,\n"
         << "                                std::uint64_t *pDomainSaltF) {\n"
         << "    TwistExpander::KDF(pDomain, pDomainConstantPublicIngress, pDomainConstantPrivateIngress, pDomainConstantCrossIngress, pDomainSaltA, pDomainSaltB, pDomainSaltC, pDomainSaltD, pDomainSaltE, pDomainSaltF);\n"
         << "    TwistWorkSpace *pWorkspace = mWorkspace;\n"
         << "    std::uint8_t *pSource = mSource;\n"
         << "    if ((pWorkspace == nullptr) || (pSource == nullptr)) { return; }\n"
         << "    (void)pDomain;\n"
         << "    (void)pDomainSaltA;\n"
         << "    (void)pDomainSaltB;\n"
         << "    (void)pDomainSaltC;\n"
         << "    (void)pDomainSaltD;\n"
         << "    (void)pDomainSaltE;\n"
         << "    (void)pDomainSaltF;\n"
         << "    (void)pDomainConstantPublicIngress;\n"
         << "    (void)pDomainConstantPrivateIngress;\n"
         << "    (void)pDomainConstantCrossIngress;\n";
    aCpp << "\n"
         << "    {\n";
    if (!AppendBranchBody(aSnapshot.mKDF, &aCpp, pErrorMessage, true)) {
        return false;
    }
    aCpp << "    }\n"
         << "}\n"
         << "\n"
         << "void " << aClassName << "::Seed(TwistWorkSpace *pWorkspace,\n"
         << "                                 TwistCryptoGenerator *pCryptoGenerator,\n"
         << "                                 TwistFarmSBox *pFarmSBox,\n"
         << "                                 TwistFarmSalt *pFarmSalt,\n"
         << "                                 std::uint8_t *pSource,\n"
         << "                                 std::uint8_t *pPassword,\n"
         << "                                 unsigned int pPasswordByteLength) {\n"
         << "    TwistExpander::Seed(pWorkspace, pCryptoGenerator, pFarmSBox, pFarmSalt, pSource, pPassword, pPasswordByteLength);\n"
         << "    if ((pWorkspace == nullptr) || (pCryptoGenerator == nullptr) || (pFarmSBox == nullptr) || (pFarmSalt == nullptr)) { return; }\n";
    aCpp << "\n"
         << "    {\n";
    if (!AppendBranchBody(aSnapshot.mSeeder, &aCpp, pErrorMessage, true)) {
        return false;
    }
    aCpp << "    }\n"
         << "}\n"
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
         << "}\n"
         << "\n"
         << BytesToCppArray(aSnapshot._mSBoxA, aClassName + "::kSBoxA", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxB, aClassName + "::kSBoxB", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxC, aClassName + "::kSBoxC", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxD, aClassName + "::kSBoxD", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxE, aClassName + "::kSBoxE", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxF, aClassName + "::kSBoxF", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxG, aClassName + "::kSBoxG", "S_SBOX")
         << '\n'
         << BytesToCppArray(aSnapshot._mSBoxH, aClassName + "::kSBoxH", "S_SBOX")
         << '\n'
         << UInt64ToCppArray(aSnapshot._mSaltA, aClassName + "::kSaltA", "S_SALT")
         << '\n'
         << UInt64ToCppArray(aSnapshot._mSaltB, aClassName + "::kSaltB", "S_SALT")
         << '\n'
         << UInt64ToCppArray(aSnapshot._mSaltC, aClassName + "::kSaltC", "S_SALT")
         << '\n'
         << UInt64ToCppArray(aSnapshot._mSaltD, aClassName + "::kSaltD", "S_SALT")
         << '\n'
         << UInt64ToCppArray(aSnapshot._mSaltE, aClassName + "::kSaltE", "S_SALT")
         << '\n'
         << UInt64ToCppArray(aSnapshot._mSaltF, aClassName + "::kSaltF", "S_SALT")
         << '\n'
         << UInt64ToCppArray(aSnapshot._mSaltG, aClassName + "::kSaltG", "S_SALT")
         << '\n'
         << UInt64ToCppArray(aSnapshot._mSaltH, aClassName + "::kSaltH", "S_SALT");
    for (const DomainSaltExportEntry &aDomainSaltEntry : aDomainSaltEntries) {
        std::vector<std::uint64_t> aValues(aDomainSaltEntry.mValues,
                                           aDomainSaltEntry.mValues + static_cast<std::size_t>(S_SALT));
        aCpp << '\n'
             << UInt64ToCppArray(aValues,
                                 aClassName + "::kDomainSalt" + aDomainSaltEntry.mSuffix,
                                 "S_SALT");
    }
    aCpp << "\n"
         << "const std::uint64_t " << aClassName << "::kDomainConstantPublicIngress = "
         << UInt64Literal(aSnapshot.mDomainConstantPublicIngress) << ";\n"
         << "const std::uint64_t " << aClassName << "::kDomainConstantPrivateIngress = "
         << UInt64Literal(aSnapshot.mDomainConstantPrivateIngress) << ";\n"
         << "const std::uint64_t " << aClassName << "::kDomainConstantCrossIngress = "
         << UInt64Literal(aSnapshot.mDomainConstantCrossIngress) << ";\n";

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

    struct DomainSaltJsonEntry {
        const char *mJsonKey;
        const std::uint64_t *mValues;
    };

    const DomainSaltJsonEntry aDomainSaltEntries[] = {
        {"domain_salt_keybox_a", aSnapshot.mDomainSaltKeyBoxA},
        {"domain_salt_keybox_b", aSnapshot.mDomainSaltKeyBoxB},
        {"domain_salt_keybox_c", aSnapshot.mDomainSaltKeyBoxC},
        {"domain_salt_keybox_d", aSnapshot.mDomainSaltKeyBoxD},
        {"domain_salt_keybox_e", aSnapshot.mDomainSaltKeyBoxE},
        {"domain_salt_keybox_f", aSnapshot.mDomainSaltKeyBoxF},

        {"domain_salt_maskbox_a", aSnapshot.mDomainSaltMaskBoxA},
        {"domain_salt_maskbox_b", aSnapshot.mDomainSaltMaskBoxB},
        {"domain_salt_maskbox_c", aSnapshot.mDomainSaltMaskBoxC},
        {"domain_salt_maskbox_d", aSnapshot.mDomainSaltMaskBoxD},
        {"domain_salt_maskbox_e", aSnapshot.mDomainSaltMaskBoxE},
        {"domain_salt_maskbox_f", aSnapshot.mDomainSaltMaskBoxF},

        {"domain_salt_wanderer_a", aSnapshot.mDomainSaltWandererA},
        {"domain_salt_wanderer_b", aSnapshot.mDomainSaltWandererB},
        {"domain_salt_wanderer_c", aSnapshot.mDomainSaltWandererC},
        {"domain_salt_wanderer_d", aSnapshot.mDomainSaltWandererD},
        {"domain_salt_wanderer_e", aSnapshot.mDomainSaltWandererE},
        {"domain_salt_wanderer_f", aSnapshot.mDomainSaltWandererF},

        {"domain_salt_orbiter_a", aSnapshot.mDomainSaltOrbiterA},
        {"domain_salt_orbiter_b", aSnapshot.mDomainSaltOrbiterB},
        {"domain_salt_orbiter_c", aSnapshot.mDomainSaltOrbiterC},
        {"domain_salt_orbiter_d", aSnapshot.mDomainSaltOrbiterD},
        {"domain_salt_orbiter_e", aSnapshot.mDomainSaltOrbiterE},
        {"domain_salt_orbiter_f", aSnapshot.mDomainSaltOrbiterF},

        {"domain_salt_prism_a", aSnapshot.mDomainSaltPrismA},
        {"domain_salt_prism_b", aSnapshot.mDomainSaltPrismB},
        {"domain_salt_prism_c", aSnapshot.mDomainSaltPrismC},
        {"domain_salt_prism_d", aSnapshot.mDomainSaltPrismD},
        {"domain_salt_prism_e", aSnapshot.mDomainSaltPrismE},
        {"domain_salt_prism_f", aSnapshot.mDomainSaltPrismF},

        {"domain_salt_source_a", aSnapshot.mDomainSaltSourceA},
        {"domain_salt_source_b", aSnapshot.mDomainSaltSourceB},
        {"domain_salt_source_c", aSnapshot.mDomainSaltSourceC},
        {"domain_salt_source_d", aSnapshot.mDomainSaltSourceD},
        {"domain_salt_source_e", aSnapshot.mDomainSaltSourceE},
        {"domain_salt_source_f", aSnapshot.mDomainSaltSourceF}
    };

    const std::string aBaseInput = aSnapshot.mNameBase.empty() ? "Generated" : aSnapshot.mNameBase;
    const std::string aBaseName = SanitizeIdentifier(aBaseInput, "Generated");

    JsonValue::Object aRootObject;
    aRootObject["name_base"] = JsonValue::String(aBaseInput);
    aRootObject["kdf"] = BranchToJsonValue(aSnapshot.mKDF, pErrorMessage);
    if ((pErrorMessage != nullptr) && !pErrorMessage->empty()) {
        return false;
    }

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
    aTables["sbox_e"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxE));
    aTables["sbox_f"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxF));
    aTables["sbox_g"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxG));
    aTables["sbox_h"] = JsonValue::ArrayValue(BytesToJsonArray(aSnapshot._mSBoxH));
    aTables["salt_a"] = JsonValue::ArrayValue(UInt64ToJsonArray(aSnapshot._mSaltA));
    aTables["salt_b"] = JsonValue::ArrayValue(UInt64ToJsonArray(aSnapshot._mSaltB));
    aTables["salt_c"] = JsonValue::ArrayValue(UInt64ToJsonArray(aSnapshot._mSaltC));
    aTables["salt_d"] = JsonValue::ArrayValue(UInt64ToJsonArray(aSnapshot._mSaltD));
    aTables["salt_e"] = JsonValue::ArrayValue(UInt64ToJsonArray(aSnapshot._mSaltE));
    aTables["salt_f"] = JsonValue::ArrayValue(UInt64ToJsonArray(aSnapshot._mSaltF));
    aTables["salt_g"] = JsonValue::ArrayValue(UInt64ToJsonArray(aSnapshot._mSaltG));
    aTables["salt_h"] = JsonValue::ArrayValue(UInt64ToJsonArray(aSnapshot._mSaltH));
    aTables["domain_constant_public_ingress"] = JsonValue::String(std::to_string(aSnapshot.mDomainConstantPublicIngress));
    aTables["domain_constant_private_ingress"] = JsonValue::String(std::to_string(aSnapshot.mDomainConstantPrivateIngress));
    aTables["domain_constant_cross_ingress"] = JsonValue::String(std::to_string(aSnapshot.mDomainConstantCrossIngress));
    for (const DomainSaltJsonEntry &aEntry : aDomainSaltEntries) {
        std::vector<std::uint64_t> aValues(aEntry.mValues,
                                           aEntry.mValues + static_cast<std::size_t>(S_SALT));
        aTables[aEntry.mJsonKey] = JsonValue::ArrayValue(UInt64ToJsonArray(aValues));
    }
    aRootObject["tables"] = JsonValue::ObjectValue(std::move(aTables));

    const std::string aJsonText = JsonValue::ObjectValue(std::move(aRootObject)).Serialize();
    const std::string aRoot = pRootPath.empty() ? "generated/json" : pRootPath;
    const std::string aOutputPath = ResolveJsonOutputPath(aRoot, aBaseName);

    return SaveTextFile(aOutputPath, aJsonText, pErrorMessage);
}
