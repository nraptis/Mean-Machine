//
//  TwistExpanderBuilder.cpp
//  MeanMachine
//

#include "GTwistExpander.hpp"

#include "FileIO.hpp"
#include "GFlowPlans.hpp"
#include "GSeedRunStage.hpp"
#include "GJson.hpp"
#include "KeyForkControl.hpp"
#include "KeyLaneAssignments.hpp"
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
    auto LoadKeyFork = [&]() {
        if (KeyForkControl::GeneratedCount() ==
            KeyForkControl::kCandidateCount) {
            return true;
        }
        if (KeyForkControl::GeneratedCount() != 0U) {
            SetError(pError,
                     "KeyForkControl had a partial candidate family.");
            return false;
        }
        KeyForkControl::Reset();
        return KeyForkControl::LoadValues(
            "Assets/key_fork_pre_planned",
            pError);
    };

    return LoadKeyFork();
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

std::string UppercaseIdentifier(std::string pText) {
    std::transform(pText.begin(), pText.end(), pText.begin(),
                   [](const unsigned char pChar) {
                       return static_cast<char>(std::toupper(pChar));
                   });
    return pText;
}

std::string KeyFlowName(const std::size_t pLogicalKeyIndex) {
    const char aKeyBoxName =
        (pLogicalKeyIndex < 8U) ? 'A' : 'B';
    const char aKeyRowName =
        static_cast<char>('A' + (pLogicalKeyIndex % 8U));
    return std::string("KEY_") + aKeyBoxName + "_" + aKeyRowName;
}

std::string KeyLaneMacroPrefix(const std::string &pExpanderName) {
    return UppercaseIdentifier(
        SanitizeIdentifier(pExpanderName, "GENERATED")
    ) + "_";
}

std::string KeyLaneName(const TwistWorkSpaceSlot pSlot) {
    const std::string aAlias = BufAliasName(pSlot);
    if ((aAlias.size() < 2U) || (aAlias.front() != 'a') ||
        (aAlias == "aInvalidBuffer")) {
        return "";
    }
    return aAlias.substr(1U);
}

bool IsKeyLaneMacroSlot(const TwistWorkSpaceSlot pSlot) {
    if (!KeyLaneAssignments::HasLane(pSlot) ||
        (TwistWorkSpace::GetBufferLength(pSlot) != S_BLOCK)) {
        return false;
    }

    switch (pSlot) {
        case TwistWorkSpaceSlot::kSourceLane:
        case TwistWorkSpaceSlot::kNonceLane:
        case TwistWorkSpaceSlot::kParamSource:
        case TwistWorkSpaceSlot::kParamDestination:
        case TwistWorkSpaceSlot::kParamCrossA:
        case TwistWorkSpaceSlot::kParamCrossB:
        case TwistWorkSpaceSlot::kParamCrossC:
        case TwistWorkSpaceSlot::kParamCrossD:
            return false;
        default:
            return !KeyLaneName(pSlot).empty();
    }
}

std::string KeyLaneMacroName(const std::string &pMacroPrefix,
                             const std::size_t pLogicalKeyIndex,
                             const TwistWorkSpaceSlot pSlot) {
    const std::string aLaneName = KeyLaneName(pSlot);
    if (aLaneName.empty()) {
        return "";
    }
    return pMacroPrefix + KeyFlowName(pLogicalKeyIndex) + "_" + aLaneName;
}

void ReplaceAllText(std::string *pText,
                    const std::string &pFrom,
                    const std::string &pTo) {
    if ((pText == nullptr) || pFrom.empty()) {
        return;
    }

    std::size_t aOffset = 0U;
    while ((aOffset = pText->find(pFrom, aOffset)) !=
           std::string::npos) {
        pText->replace(aOffset, pFrom.size(), pTo);
        aOffset += pTo.size();
    }
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

std::string RandomDestinationSquashLine(const char *pLaneFamily) {
    static constexpr std::array<const char *, 3> kMethods = {
        "SquashA", "SquashB", "SquashC",
    };
    const char *aMethod =
        kMethods[static_cast<std::size_t>(Random::Get(
            static_cast<int>(kMethods.size())
        ))];

    return std::string("    TwistSquash::") + aMethod +
        "(pWorkSpace->m" + pLaneFamily + "LaneA, pWorkSpace->m" +
        pLaneFamily + "LaneB, pWorkSpace->m" + pLaneFamily +
        "LaneC, pWorkSpace->m" + pLaneFamily + "LaneD, "
        "pDestination);\n";
}

std::string WorkspaceLaneExpression(const TwistWorkSpaceSlot pSlot) {
    const std::string aAlias = BufAliasName(pSlot);
    if ((aAlias.size() < 2U) || (aAlias[0] != 'a')) {
        return "";
    }
    return "pWorkSpace->m" + aAlias.substr(1U);
}

std::size_t RandomKeyFoldOffset() {
    return static_cast<std::size_t>(Random::Get(1, 511));
}

std::string RenderTwistForkKeyHalf(
    const std::string &pClassName,
    const std::array<TwistWorkSpaceSlot, 4U> &pEarthLanes,
    const std::array<TwistWorkSpaceSlot, 4U> &pCrystalLanes,
    const std::array<TwistWorkSpaceSlot, 4U> &pMuLanes,
    const std::array<TwistWorkSpaceSlot, 4U> &pLelLanes,
    const std::array<TwistWorkSpaceSlot, 4U> &pGozLanes,
    const std::array<TwistWorkSpaceSlot, 4U> &pFinalLanes,
    const KeyForkControl::Candidate &pCandidate,
    const bool pIsHalfB) {
    static_assert(S_BLOCK == 32768,
                  "Twist key forks require 32,768-byte source lanes.");
    static_assert(W_KEY == 2048,
                  "Twist key forks require 2,048-byte key pieces.");
    static constexpr std::size_t kBlockSize = 512U;
    static constexpr std::size_t kPhysicalBlocksPerQuarter =
        (S_BLOCK / 4U) / kBlockSize;
    static_assert(KeyForkControl::kSourceBlockCount * 2U * kBlockSize ==
                      S_BLOCK,
                  "Even and odd source blocks must cover one source lane.");
    static_assert(KeyForkControl::kMuBlockCount * kBlockSize == 4096U,
                  "Mu lane size changed.");
    static_assert(KeyForkControl::kLelBlockCount * kBlockSize == W_KEY,
                  "Lel lane size changed.");
    static_assert(KeyForkControl::kGozBlockCount * kBlockSize == 1024U,
                  "Goz lane size changed.");
    static constexpr std::array<
        std::array<KeyForkControl::BlockPick, 2U>, 4U> kFinalPairs = {{
            {{{0U, 0U}, {1U, 0U}}},
            {{{2U, 0U}, {3U, 0U}}},
            {{{0U, 1U}, {2U, 1U}}},
            {{{1U, 1U}, {3U, 1U}}},
        }};

    const std::size_t aForkIndex = pIsHalfB ? 1U : 0U;
    const char aForkLetter = pIsHalfB ? 'B' : 'A';

    std::ostringstream aOut;
    aOut << "void " << pClassName << "::TwistForkKeyHalf"
         << aForkLetter << "(TwistWorkSpace *pWorkSpace) {\n"
         << "    static_assert(S_BLOCK == 32768, \"Twist fork source size changed.\");\n"
         << "    static_assert(S_BLOCK / 64U == 512U, \"Twist fork block size changed.\");\n"
         << "    static_assert(W_KEY == 2048, \"Twist fork key size changed.\");\n\n";

    for (std::size_t aLane = 0U; aLane < 4U; ++aLane) {
        const std::string aExpression =
            WorkspaceLaneExpression(pEarthLanes[aLane]);
        if (aExpression.empty()) {
            return "";
        }
        aOut << "    std::uint8_t *aEarthLane"
             << static_cast<char>('A' + aLane)
             << " = " << aExpression << ";\n";
    }
    for (std::size_t aLane = 0U; aLane < 4U; ++aLane) {
        const std::string aExpression =
            WorkspaceLaneExpression(pCrystalLanes[aLane]);
        if (aExpression.empty()) {
            return "";
        }
        aOut << "    std::uint8_t *aCrystalLane"
             << static_cast<char>('A' + aLane)
             << " = " << aExpression << ";\n";
    }
    aOut << "\n";

    for (std::size_t aLane = 0U; aLane < 4U; ++aLane) {
        const std::string aMuExpression =
            WorkspaceLaneExpression(pMuLanes[aLane]);
        const std::string aLelExpression =
            WorkspaceLaneExpression(pLelLanes[aLane]);
        const std::string aGozExpression =
            WorkspaceLaneExpression(pGozLanes[aLane]);
        if (aMuExpression.empty() || aLelExpression.empty() ||
            aGozExpression.empty()) {
            return "";
        }
        aOut << "    std::uint8_t *aMuLane"
             << static_cast<char>('A' + aLane)
             << " = " << aMuExpression << ";\n"
             << "    std::uint8_t *aLelLane"
             << static_cast<char>('A' + aLane)
             << " = " << aLelExpression << ";\n"
             << "    std::uint8_t *aGozLane"
             << static_cast<char>('A' + aLane)
             << " = " << aGozExpression << ";\n";
    }
    aOut << "\n";
    for (std::size_t aLane = 0U; aLane < 4U; ++aLane) {
        const std::string aExpression =
            WorkspaceLaneExpression(pFinalLanes[aLane]);
        if (aExpression.empty()) {
            return "";
        }
        aOut << "    std::uint8_t *aFinalLane"
             << static_cast<char>('A' + aLane)
             << " = " << aExpression << ";\n";
    }

    static constexpr std::array<const char *, 8U> kSourceLaneNames = {{
        "aEarthLaneA", "aEarthLaneB", "aEarthLaneC", "aEarthLaneD",
        "aCrystalLaneA", "aCrystalLaneB",
        "aCrystalLaneC", "aCrystalLaneD",
    }};
    static constexpr std::array<const char *, 4U> kMuLaneNames = {{
        "aMuLaneA", "aMuLaneB", "aMuLaneC", "aMuLaneD",
    }};
    static constexpr std::array<const char *, 4U> kLelLaneNames = {{
        "aLelLaneA", "aLelLaneB", "aLelLaneC", "aLelLaneD",
    }};
    using SourceMembership =
        std::array<std::size_t, KeyForkControl::kSourceLaneCount>;
    using SourceBlocks =
        std::array<std::vector<std::size_t>,
                   KeyForkControl::kSourceLaneCount>;

    for (std::size_t aOutputLane = 0U;
         aOutputLane < KeyForkControl::kOutputLaneCount;
         ++aOutputLane) {
        std::array<std::array<SourceMembership,
                              KeyForkControl::kMuBlockCount>,
                   KeyForkControl::kStageLaneCount> aMuMemberships{};
        std::array<std::array<SourceMembership,
                              KeyForkControl::kLelBlockCount>,
                   KeyForkControl::kStageLaneCount> aLelMemberships{};
        std::array<std::array<SourceMembership,
                              KeyForkControl::kGozBlockCount>,
                   KeyForkControl::kStageLaneCount> aGozMemberships{};
        std::array<std::array<SourceBlocks,
                              KeyForkControl::kMuBlockCount>,
                   KeyForkControl::kStageLaneCount> aMuSourceBlocks{};
        std::array<std::array<SourceBlocks,
                              KeyForkControl::kLelBlockCount>,
                   KeyForkControl::kStageLaneCount> aLelSourceBlocks{};
        std::array<std::array<SourceBlocks,
                              KeyForkControl::kGozBlockCount>,
                   KeyForkControl::kStageLaneCount> aGozSourceBlocks{};
        const char aOutputLetter = static_cast<char>('A' + aOutputLane);
        aOut << "\n"
             << "    // Grow input " << aOutputLetter
             << " — balanced 512-byte fold graph.\n\n"
             << "    // Mu — eight 512-byte blocks per lane.\n\n";

        for (std::size_t aMu = 0U;
             aMu < KeyForkControl::kStageLaneCount;
             ++aMu) {
            for (std::size_t aBlock = 0U;
                 aBlock < KeyForkControl::kMuBlockCount;
                 ++aBlock) {
                const auto &aPair =
                    pCandidate.mMu[aForkIndex][aOutputLane][aMu][aBlock];
                const auto &aPickA = aPair[0U];
                const auto &aPickB = aPair[1U];
                const std::size_t aPhysicalBlockA =
                    KeyForkControl::PhysicalSourceBlock(
                        aForkIndex,
                        aPickA.mLane,
                        aPickA.mBlock);
                const std::size_t aPhysicalBlockB =
                    KeyForkControl::PhysicalSourceBlock(
                        aForkIndex,
                        aPickB.mLane,
                        aPickB.mBlock);
                ++aMuMemberships[aMu][aBlock][aPickA.mLane];
                ++aMuMemberships[aMu][aBlock][aPickB.mLane];
                aMuSourceBlocks[aMu][aBlock][aPickA.mLane]
                    .push_back(aPhysicalBlockA);
                aMuSourceBlocks[aMu][aBlock][aPickB.mLane]
                    .push_back(aPhysicalBlockB);
                aOut << "    // Mu " << static_cast<char>('A' + aMu)
                     << "[" << aBlock << "]: "
                     << kSourceLaneNames[aPickA.mLane] << "["
                     << aPhysicalBlockA << "] + "
                     << kSourceLaneNames[aPickB.mLane] << "["
                     << aPhysicalBlockB << "].\n"
                     << "    KEY_FOLD_BLOCK("
                     << kSourceLaneNames[aPickA.mLane] << ", "
                     << aPhysicalBlockA << "U, "
                     << RandomKeyFoldOffset() << "U, "
                     << kSourceLaneNames[aPickB.mLane] << ", "
                     << aPhysicalBlockB << "U, "
                     << RandomKeyFoldOffset() << "U, "
                     << "aMuLane" << static_cast<char>('A' + aMu) << ", "
                     << aBlock << "U);\n\n";
            }
        }

        aOut << "    // Lel — four 512-byte blocks per lane.\n\n";
        for (std::size_t aLel = 0U;
             aLel < KeyForkControl::kStageLaneCount;
             ++aLel) {
            for (std::size_t aBlock = 0U;
                 aBlock < KeyForkControl::kLelBlockCount;
                 ++aBlock) {
                const auto &aPair =
                    pCandidate.mLel[aForkIndex][aOutputLane][aLel][aBlock];
                const auto &aPickA = aPair[0U];
                const auto &aPickB = aPair[1U];
                for (std::size_t aSource = 0U;
                     aSource < KeyForkControl::kSourceLaneCount;
                     ++aSource) {
                    aLelMemberships[aLel][aBlock][aSource] =
                        aMuMemberships[aPickA.mLane]
                                      [aPickA.mBlock][aSource] +
                        aMuMemberships[aPickB.mLane]
                                      [aPickB.mBlock][aSource];
                    const auto &aBlocksA =
                        aMuSourceBlocks[aPickA.mLane]
                                       [aPickA.mBlock][aSource];
                    const auto &aBlocksB =
                        aMuSourceBlocks[aPickB.mLane]
                                       [aPickB.mBlock][aSource];
                    auto &aBlocks = aLelSourceBlocks[aLel][aBlock][aSource];
                    aBlocks.insert(aBlocks.end(),
                                   aBlocksA.begin(), aBlocksA.end());
                    aBlocks.insert(aBlocks.end(),
                                   aBlocksB.begin(), aBlocksB.end());
                }
                aOut << "    // Lel " << static_cast<char>('A' + aLel)
                     << "[" << aBlock << "]: "
                     << kMuLaneNames[aPickA.mLane] << "["
                     << static_cast<std::size_t>(aPickA.mBlock) << "] + "
                     << kMuLaneNames[aPickB.mLane] << "["
                     << static_cast<std::size_t>(aPickB.mBlock) << "].\n"
                     << "    KEY_FOLD_BLOCK("
                     << kMuLaneNames[aPickA.mLane] << ", "
                     << static_cast<std::size_t>(aPickA.mBlock) << "U, "
                     << RandomKeyFoldOffset() << "U, "
                     << kMuLaneNames[aPickB.mLane] << ", "
                     << static_cast<std::size_t>(aPickB.mBlock) << "U, "
                     << RandomKeyFoldOffset() << "U, "
                     << "aLelLane" << static_cast<char>('A' + aLel) << ", "
                     << aBlock << "U);\n\n";
            }
        }

        aOut << "    // Goz — two 512-byte blocks per lane.\n\n";
        for (std::size_t aGoz = 0U;
             aGoz < KeyForkControl::kStageLaneCount;
             ++aGoz) {
            for (std::size_t aBlock = 0U;
                 aBlock < KeyForkControl::kGozBlockCount;
                 ++aBlock) {
                const auto &aPair =
                    pCandidate.mGoz[aForkIndex][aOutputLane][aGoz][aBlock];
                const auto &aPickA = aPair[0U];
                const auto &aPickB = aPair[1U];
                for (std::size_t aSource = 0U;
                     aSource < KeyForkControl::kSourceLaneCount;
                     ++aSource) {
                    aGozMemberships[aGoz][aBlock][aSource] =
                        aLelMemberships[aPickA.mLane]
                                       [aPickA.mBlock][aSource] +
                        aLelMemberships[aPickB.mLane]
                                       [aPickB.mBlock][aSource];
                    const auto &aBlocksA =
                        aLelSourceBlocks[aPickA.mLane]
                                        [aPickA.mBlock][aSource];
                    const auto &aBlocksB =
                        aLelSourceBlocks[aPickB.mLane]
                                        [aPickB.mBlock][aSource];
                    auto &aBlocks = aGozSourceBlocks[aGoz][aBlock][aSource];
                    aBlocks.insert(aBlocks.end(),
                                   aBlocksA.begin(), aBlocksA.end());
                    aBlocks.insert(aBlocks.end(),
                                   aBlocksB.begin(), aBlocksB.end());
                }
                aOut << "    // Goz " << static_cast<char>('A' + aGoz)
                     << "[" << aBlock << "]: "
                     << kLelLaneNames[aPickA.mLane] << "["
                     << static_cast<std::size_t>(aPickA.mBlock) << "] + "
                     << kLelLaneNames[aPickB.mLane] << "["
                     << static_cast<std::size_t>(aPickB.mBlock) << "].\n"
                     << "    KEY_FOLD_BLOCK("
                     << kLelLaneNames[aPickA.mLane] << ", "
                     << static_cast<std::size_t>(aPickA.mBlock) << "U, "
                     << RandomKeyFoldOffset() << "U, "
                     << kLelLaneNames[aPickB.mLane] << ", "
                     << static_cast<std::size_t>(aPickB.mBlock) << "U, "
                     << RandomKeyFoldOffset() << "U, "
                     << "aGozLane" << static_cast<char>('A' + aGoz) << ", "
                     << aBlock << "U);\n\n";
            }
        }

        std::array<SourceMembership, 4U> aKeyMemberships{};
        std::array<SourceBlocks, 4U> aKeySourceBlocks{};
        for (std::size_t aKeyBlock = 0U; aKeyBlock < 4U; ++aKeyBlock) {
            const auto &aLeft = kFinalPairs[aKeyBlock][0U];
            const auto &aRight = kFinalPairs[aKeyBlock][1U];
            for (std::size_t aSource = 0U;
                 aSource < KeyForkControl::kSourceLaneCount;
                 ++aSource) {
                aKeyMemberships[aKeyBlock][aSource] =
                    aGozMemberships[aLeft.mLane][aLeft.mBlock][aSource] +
                    aGozMemberships[aRight.mLane][aRight.mBlock][aSource];
                const auto &aBlocksA =
                    aGozSourceBlocks[aLeft.mLane]
                                    [aLeft.mBlock][aSource];
                const auto &aBlocksB =
                    aGozSourceBlocks[aRight.mLane]
                                    [aRight.mBlock][aSource];
                auto &aBlocks = aKeySourceBlocks[aKeyBlock][aSource];
                aBlocks.insert(aBlocks.end(),
                               aBlocksA.begin(), aBlocksA.end());
                aBlocks.insert(aBlocks.end(),
                               aBlocksB.begin(), aBlocksB.end());
            }
        }

        aOut << "    // Key source memberships.\n";
        for (std::size_t aKeyBlock = 0U; aKeyBlock < 4U; ++aKeyBlock) {
            aOut << "    // Block " << aKeyBlock
                 << ": Earth={A:" << aKeyMemberships[aKeyBlock][0U]
                 << ", B:" << aKeyMemberships[aKeyBlock][1U]
                 << ", C:" << aKeyMemberships[aKeyBlock][2U]
                 << ", D:" << aKeyMemberships[aKeyBlock][3U]
                 << "} Crystal={A:" << aKeyMemberships[aKeyBlock][4U]
                 << ", B:" << aKeyMemberships[aKeyBlock][5U]
                 << ", C:" << aKeyMemberships[aKeyBlock][6U]
                 << ", D:" << aKeyMemberships[aKeyBlock][7U]
                 << "}.\n";
            aOut << "    // Quarters: Earth={A:"
                 << (aKeySourceBlocks[aKeyBlock][0U][0U] /
                     kPhysicalBlocksPerQuarter) << "/"
                 << (aKeySourceBlocks[aKeyBlock][0U][1U] /
                     kPhysicalBlocksPerQuarter)
                 << ", B:"
                 << (aKeySourceBlocks[aKeyBlock][1U][0U] /
                     kPhysicalBlocksPerQuarter) << "/"
                 << (aKeySourceBlocks[aKeyBlock][1U][1U] /
                     kPhysicalBlocksPerQuarter)
                 << ", C:"
                 << (aKeySourceBlocks[aKeyBlock][2U][0U] /
                     kPhysicalBlocksPerQuarter) << "/"
                 << (aKeySourceBlocks[aKeyBlock][2U][1U] /
                     kPhysicalBlocksPerQuarter)
                 << ", D:"
                 << (aKeySourceBlocks[aKeyBlock][3U][0U] /
                     kPhysicalBlocksPerQuarter) << "/"
                 << (aKeySourceBlocks[aKeyBlock][3U][1U] /
                     kPhysicalBlocksPerQuarter)
                 << "} Crystal={A:"
                 << (aKeySourceBlocks[aKeyBlock][4U][0U] /
                     kPhysicalBlocksPerQuarter) << "/"
                 << (aKeySourceBlocks[aKeyBlock][4U][1U] /
                     kPhysicalBlocksPerQuarter)
                 << ", B:"
                 << (aKeySourceBlocks[aKeyBlock][5U][0U] /
                     kPhysicalBlocksPerQuarter) << "/"
                 << (aKeySourceBlocks[aKeyBlock][5U][1U] /
                     kPhysicalBlocksPerQuarter)
                 << ", C:"
                 << (aKeySourceBlocks[aKeyBlock][6U][0U] /
                     kPhysicalBlocksPerQuarter) << "/"
                 << (aKeySourceBlocks[aKeyBlock][6U][1U] /
                     kPhysicalBlocksPerQuarter)
                 << ", D:"
                 << (aKeySourceBlocks[aKeyBlock][7U][0U] /
                     kPhysicalBlocksPerQuarter) << "/"
                 << (aKeySourceBlocks[aKeyBlock][7U][1U] /
                     kPhysicalBlocksPerQuarter)
                 << "}.\n";
        }
        aOut << "\n"
             << "    // Key — fixed two-input Goz fold.\n\n";
        for (std::size_t aKeyBlock = 0U; aKeyBlock < 4U; ++aKeyBlock) {
            const auto &aLeft = kFinalPairs[aKeyBlock][0U];
            const auto &aRight = kFinalPairs[aKeyBlock][1U];
            const char aLeftLane = static_cast<char>('A' + aLeft.mLane);
            const char aRightLane = static_cast<char>('A' + aRight.mLane);
            aOut << "    KEY_FOLD_BLOCK(aGozLane" << aLeftLane << ", "
                 << static_cast<std::size_t>(aLeft.mBlock) << "U, "
                 << RandomKeyFoldOffset() << "U, "
                 << "aGozLane" << aRightLane << ", "
                 << static_cast<std::size_t>(aRight.mBlock) << "U, "
                 << RandomKeyFoldOffset() << "U, "
                 << "aFinalLane" << aOutputLetter;
            if (pIsHalfB) {
                aOut << " + W_KEY";
            }
            aOut << ", " << aKeyBlock << "U);\n\n";
        }
    }
    aOut << "}\n";
    return aOut.str();
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
    static constexpr std::array<FlowLaneFamily, 31> kLaneFamilies = {{
        {TwistWorkSpaceSlot::kEarthLaneA, "earth"},
        {TwistWorkSpaceSlot::kFireLaneA, "fire"},
        {TwistWorkSpaceSlot::kWindLaneA, "wind"},
        {TwistWorkSpaceSlot::kWaterLaneA, "water"},
        {TwistWorkSpaceSlot::kRainbowLaneA, "rainbow"},
        {TwistWorkSpaceSlot::kLightningLaneA, "lightning"},
        {TwistWorkSpaceSlot::kIceLaneA, "ice"},
        {TwistWorkSpaceSlot::kPlasmaLaneA, "plasma"},
        {TwistWorkSpaceSlot::kShadowLaneA, "shadow"},
        {TwistWorkSpaceSlot::kCrystalLaneA, "crystal"},
        {TwistWorkSpaceSlot::kAetherLaneA, "aether"},
        {TwistWorkSpaceSlot::kCelestialLaneA, "celestial"},
        {TwistWorkSpaceSlot::kVaporLaneA, "vapor"},
        {TwistWorkSpaceSlot::kKineticLaneA, "kinetic"},
        {TwistWorkSpaceSlot::kSonicLaneA, "sonic"},
        {TwistWorkSpaceSlot::kPlanarLaneA, "planar"},
        {TwistWorkSpaceSlot::kFrostLaneA, "frost"},
        {TwistWorkSpaceSlot::kArcaneLaneA, "arcane"},
        {TwistWorkSpaceSlot::kLunarLaneA, "lunar"},
        {TwistWorkSpaceSlot::kRunicLaneA, "runic"},
        {TwistWorkSpaceSlot::kGloomLaneA, "gloom"},
        {TwistWorkSpaceSlot::kAbjurationLaneA, "abjuration"},
        {TwistWorkSpaceSlot::kDivinationLaneA, "divination"},
        {TwistWorkSpaceSlot::kEvocationLaneA, "evocation"},
        {TwistWorkSpaceSlot::kStasisLaneA, "stasis"},
        {TwistWorkSpaceSlot::kAlchemyLaneA, "alchemy"},
        {TwistWorkSpaceSlot::kAuguryLaneA, "augury"},
        {TwistWorkSpaceSlot::kPsychicLaneA, "psychic"},
        {TwistWorkSpaceSlot::kVoodooLaneA, "voodoo"},
        {TwistWorkSpaceSlot::kSpiritLaneA, "spirit"},
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

std::string CompactFlowSlotName(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kKeyRowReadA: return "key_read_a";
        case TwistWorkSpaceSlot::kKeyRowReadB: return "key_read_b";
        default: return FlowSlotName(pSlot);
    }
}

std::string CompactFlowList(
    const std::vector<TwistWorkSpaceSlot> &pSlots) {
    std::vector<TwistWorkSpaceSlot> aSlots;
    for (const TwistWorkSpaceSlot aSlot : pSlots) {
        if (std::find(aSlots.begin(), aSlots.end(), aSlot) ==
            aSlots.end()) {
            aSlots.push_back(aSlot);
        }
    }

    std::vector<bool> aConsumed(aSlots.size(), false);
    std::vector<std::string> aNames;
    for (std::size_t i = 0U; i < aSlots.size(); ++i) {
        if (aConsumed[i]) {
            continue;
        }

        const std::string aName = CompactFlowSlotName(aSlots[i]);
        std::string aFamilyName;
        if ((aName.size() > 2U) &&
            (aName[aName.size() - 2U] == '_') &&
            (aName.back() >= 'a') && (aName.back() <= 'd')) {
            aFamilyName = aName.substr(0U, aName.size() - 2U);
        }

        std::array<std::size_t, 4U> aFamilyIndices = {
            aSlots.size(), aSlots.size(), aSlots.size(), aSlots.size(),
        };
        if (!aFamilyName.empty()) {
            for (std::size_t j = 0U; j < aSlots.size(); ++j) {
                const std::string aCandidateName =
                    CompactFlowSlotName(aSlots[j]);
                if ((aCandidateName.size() == aFamilyName.size() + 2U) &&
                    (aCandidateName.compare(0U,
                                            aFamilyName.size(),
                                            aFamilyName) == 0) &&
                    (aCandidateName[aFamilyName.size()] == '_') &&
                    (aCandidateName.back() >= 'a') &&
                    (aCandidateName.back() <= 'd')) {
                    aFamilyIndices[static_cast<std::size_t>(
                        aCandidateName.back() - 'a')] = j;
                }
            }
        }

        const bool aHasWholeFamily =
            std::all_of(aFamilyIndices.begin(),
                        aFamilyIndices.end(),
                        [&aSlots](const std::size_t pIndex) {
                            return pIndex < aSlots.size();
                        });
        if (aHasWholeFamily) {
            aNames.push_back("$" + aFamilyName);
            for (const std::size_t aFamilyIndex : aFamilyIndices) {
                aConsumed[aFamilyIndex] = true;
            }
        } else {
            aNames.push_back(aName);
            aConsumed[i] = true;
        }
    }

    std::ostringstream aStream;
    aStream << '[';
    for (std::size_t i = 0U; i < aNames.size(); ++i) {
        if (i > 0U) {
            aStream << ", ";
        }
        aStream << aNames[i];
    }
    aStream << ']';
    return aStream.str();
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
    aLine << "const std::uint64_t " << pNonceSymbol.mName << " = TwistMix64::"
          << aDiffuseName
          << "(pNonce * "
          << UInt64Literal(aMultiplyWord)
          << " + "
          << UInt64Literal(aAddWord) << ");";
    return aLine.str();
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

        TwistWorkSpaceSlot::kRainbowLaneA,
        TwistWorkSpaceSlot::kRainbowLaneB,
        TwistWorkSpaceSlot::kRainbowLaneC,
        TwistWorkSpaceSlot::kRainbowLaneD,

        TwistWorkSpaceSlot::kEarthLaneA,
        TwistWorkSpaceSlot::kEarthLaneB,
        TwistWorkSpaceSlot::kEarthLaneC,
        TwistWorkSpaceSlot::kEarthLaneD,

        TwistWorkSpaceSlot::kWindLaneA,
        TwistWorkSpaceSlot::kWindLaneB,
        TwistWorkSpaceSlot::kWindLaneC,
        TwistWorkSpaceSlot::kWindLaneD,

        TwistWorkSpaceSlot::kLightningLaneA,
        TwistWorkSpaceSlot::kLightningLaneB,
        TwistWorkSpaceSlot::kLightningLaneC,
        TwistWorkSpaceSlot::kLightningLaneD,

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

        TwistWorkSpaceSlot::kVaporLaneA,
        TwistWorkSpaceSlot::kVaporLaneB,
        TwistWorkSpaceSlot::kVaporLaneC,
        TwistWorkSpaceSlot::kVaporLaneD,

        TwistWorkSpaceSlot::kKineticLaneA,
        TwistWorkSpaceSlot::kKineticLaneB,
        TwistWorkSpaceSlot::kKineticLaneC,
        TwistWorkSpaceSlot::kKineticLaneD,
        TwistWorkSpaceSlot::kSonicLaneA,
        TwistWorkSpaceSlot::kSonicLaneB,
        TwistWorkSpaceSlot::kSonicLaneC,
        TwistWorkSpaceSlot::kSonicLaneD,
        TwistWorkSpaceSlot::kPlanarLaneA,
        TwistWorkSpaceSlot::kPlanarLaneB,
        TwistWorkSpaceSlot::kPlanarLaneC,
        TwistWorkSpaceSlot::kPlanarLaneD,
        TwistWorkSpaceSlot::kFrostLaneA,
        TwistWorkSpaceSlot::kFrostLaneB,
        TwistWorkSpaceSlot::kFrostLaneC,
        TwistWorkSpaceSlot::kFrostLaneD,
        TwistWorkSpaceSlot::kArcaneLaneA,
        TwistWorkSpaceSlot::kArcaneLaneB,
        TwistWorkSpaceSlot::kArcaneLaneC,
        TwistWorkSpaceSlot::kArcaneLaneD,
        TwistWorkSpaceSlot::kLunarLaneA,
        TwistWorkSpaceSlot::kLunarLaneB,
        TwistWorkSpaceSlot::kLunarLaneC,
        TwistWorkSpaceSlot::kLunarLaneD,
        TwistWorkSpaceSlot::kRunicLaneA,
        TwistWorkSpaceSlot::kRunicLaneB,
        TwistWorkSpaceSlot::kRunicLaneC,
        TwistWorkSpaceSlot::kRunicLaneD,
        TwistWorkSpaceSlot::kGloomLaneA,
        TwistWorkSpaceSlot::kGloomLaneB,
        TwistWorkSpaceSlot::kGloomLaneC,
        TwistWorkSpaceSlot::kGloomLaneD,
        TwistWorkSpaceSlot::kAbjurationLaneA,
        TwistWorkSpaceSlot::kAbjurationLaneB,
        TwistWorkSpaceSlot::kAbjurationLaneC,
        TwistWorkSpaceSlot::kAbjurationLaneD,
        TwistWorkSpaceSlot::kDivinationLaneA,
        TwistWorkSpaceSlot::kDivinationLaneB,
        TwistWorkSpaceSlot::kDivinationLaneC,
        TwistWorkSpaceSlot::kDivinationLaneD,
        TwistWorkSpaceSlot::kEvocationLaneA,
        TwistWorkSpaceSlot::kEvocationLaneB,
        TwistWorkSpaceSlot::kEvocationLaneC,
        TwistWorkSpaceSlot::kEvocationLaneD,
        TwistWorkSpaceSlot::kPlasmaLaneA,
        TwistWorkSpaceSlot::kPlasmaLaneB,
        TwistWorkSpaceSlot::kPlasmaLaneC,
        TwistWorkSpaceSlot::kPlasmaLaneD,
        TwistWorkSpaceSlot::kRainbowLaneA,
        TwistWorkSpaceSlot::kRainbowLaneB,
        TwistWorkSpaceSlot::kRainbowLaneC,
        TwistWorkSpaceSlot::kRainbowLaneD,
        TwistWorkSpaceSlot::kStasisLaneA,
        TwistWorkSpaceSlot::kStasisLaneB,
        TwistWorkSpaceSlot::kStasisLaneC,
        TwistWorkSpaceSlot::kAlchemyLaneA,
        TwistWorkSpaceSlot::kAlchemyLaneB,
        TwistWorkSpaceSlot::kAlchemyLaneC,
        TwistWorkSpaceSlot::kAlchemyLaneD,
        TwistWorkSpaceSlot::kAuguryLaneA,
        TwistWorkSpaceSlot::kAuguryLaneB,
        TwistWorkSpaceSlot::kAuguryLaneC,
        TwistWorkSpaceSlot::kAuguryLaneD,
        TwistWorkSpaceSlot::kPsychicLaneA,
        TwistWorkSpaceSlot::kPsychicLaneB,
        TwistWorkSpaceSlot::kPsychicLaneC,
        TwistWorkSpaceSlot::kPsychicLaneD,
        TwistWorkSpaceSlot::kVoodooLaneA,
        TwistWorkSpaceSlot::kVoodooLaneB,
        TwistWorkSpaceSlot::kVoodooLaneC,
        TwistWorkSpaceSlot::kVoodooLaneD,

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
        case TwistWorkSpaceSlot::kRainbowLaneA: return aPrefix + "pWorkSpace->mRainbowLaneA;";
        case TwistWorkSpaceSlot::kRainbowLaneB: return aPrefix + "pWorkSpace->mRainbowLaneB;";
        case TwistWorkSpaceSlot::kRainbowLaneC: return aPrefix + "pWorkSpace->mRainbowLaneC;";
        case TwistWorkSpaceSlot::kRainbowLaneD: return aPrefix + "pWorkSpace->mRainbowLaneD;";
        case TwistWorkSpaceSlot::kEarthLaneA: return aPrefix + "pWorkSpace->mEarthLaneA;";
        case TwistWorkSpaceSlot::kEarthLaneB: return aPrefix + "pWorkSpace->mEarthLaneB;";
        case TwistWorkSpaceSlot::kEarthLaneC: return aPrefix + "pWorkSpace->mEarthLaneC;";
        case TwistWorkSpaceSlot::kEarthLaneD: return aPrefix + "pWorkSpace->mEarthLaneD;";
        case TwistWorkSpaceSlot::kWindLaneA: return aPrefix + "pWorkSpace->mWindLaneA;";
        case TwistWorkSpaceSlot::kWindLaneB: return aPrefix + "pWorkSpace->mWindLaneB;";
        case TwistWorkSpaceSlot::kWindLaneC: return aPrefix + "pWorkSpace->mWindLaneC;";
        case TwistWorkSpaceSlot::kWindLaneD: return aPrefix + "pWorkSpace->mWindLaneD;";
        case TwistWorkSpaceSlot::kLightningLaneA: return aPrefix + "pWorkSpace->mLightningLaneA;";
        case TwistWorkSpaceSlot::kLightningLaneB: return aPrefix + "pWorkSpace->mLightningLaneB;";
        case TwistWorkSpaceSlot::kLightningLaneC: return aPrefix + "pWorkSpace->mLightningLaneC;";
        case TwistWorkSpaceSlot::kLightningLaneD: return aPrefix + "pWorkSpace->mLightningLaneD;";
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
        case TwistWorkSpaceSlot::kVaporLaneA: return aPrefix + "pWorkSpace->mVaporLaneA;";
        case TwistWorkSpaceSlot::kVaporLaneB: return aPrefix + "pWorkSpace->mVaporLaneB;";
        case TwistWorkSpaceSlot::kVaporLaneC: return aPrefix + "pWorkSpace->mVaporLaneC;";
        case TwistWorkSpaceSlot::kVaporLaneD: return aPrefix + "pWorkSpace->mVaporLaneD;";
        case TwistWorkSpaceSlot::kKineticLaneA: return aPrefix + "pWorkSpace->mKineticLaneA;";
        case TwistWorkSpaceSlot::kKineticLaneB: return aPrefix + "pWorkSpace->mKineticLaneB;";
        case TwistWorkSpaceSlot::kKineticLaneC: return aPrefix + "pWorkSpace->mKineticLaneC;";
        case TwistWorkSpaceSlot::kKineticLaneD: return aPrefix + "pWorkSpace->mKineticLaneD;";
        case TwistWorkSpaceSlot::kSonicLaneA: return aPrefix + "pWorkSpace->mSonicLaneA;";
        case TwistWorkSpaceSlot::kSonicLaneB: return aPrefix + "pWorkSpace->mSonicLaneB;";
        case TwistWorkSpaceSlot::kSonicLaneC: return aPrefix + "pWorkSpace->mSonicLaneC;";
        case TwistWorkSpaceSlot::kSonicLaneD: return aPrefix + "pWorkSpace->mSonicLaneD;";
        case TwistWorkSpaceSlot::kPlanarLaneA: return aPrefix + "pWorkSpace->mPlanarLaneA;";
        case TwistWorkSpaceSlot::kPlanarLaneB: return aPrefix + "pWorkSpace->mPlanarLaneB;";
        case TwistWorkSpaceSlot::kPlanarLaneC: return aPrefix + "pWorkSpace->mPlanarLaneC;";
        case TwistWorkSpaceSlot::kPlanarLaneD: return aPrefix + "pWorkSpace->mPlanarLaneD;";
        case TwistWorkSpaceSlot::kFrostLaneA: return aPrefix + "pWorkSpace->mFrostLaneA;";
        case TwistWorkSpaceSlot::kFrostLaneB: return aPrefix + "pWorkSpace->mFrostLaneB;";
        case TwistWorkSpaceSlot::kFrostLaneC: return aPrefix + "pWorkSpace->mFrostLaneC;";
        case TwistWorkSpaceSlot::kFrostLaneD: return aPrefix + "pWorkSpace->mFrostLaneD;";
        case TwistWorkSpaceSlot::kArcaneLaneA: return aPrefix + "pWorkSpace->mArcaneLaneA;";
        case TwistWorkSpaceSlot::kArcaneLaneB: return aPrefix + "pWorkSpace->mArcaneLaneB;";
        case TwistWorkSpaceSlot::kArcaneLaneC: return aPrefix + "pWorkSpace->mArcaneLaneC;";
        case TwistWorkSpaceSlot::kArcaneLaneD: return aPrefix + "pWorkSpace->mArcaneLaneD;";
        case TwistWorkSpaceSlot::kLunarLaneA: return aPrefix + "pWorkSpace->mLunarLaneA;";
        case TwistWorkSpaceSlot::kLunarLaneB: return aPrefix + "pWorkSpace->mLunarLaneB;";
        case TwistWorkSpaceSlot::kLunarLaneC: return aPrefix + "pWorkSpace->mLunarLaneC;";
        case TwistWorkSpaceSlot::kLunarLaneD: return aPrefix + "pWorkSpace->mLunarLaneD;";
        case TwistWorkSpaceSlot::kRunicLaneA: return aPrefix + "pWorkSpace->mRunicLaneA;";
        case TwistWorkSpaceSlot::kRunicLaneB: return aPrefix + "pWorkSpace->mRunicLaneB;";
        case TwistWorkSpaceSlot::kRunicLaneC: return aPrefix + "pWorkSpace->mRunicLaneC;";
        case TwistWorkSpaceSlot::kRunicLaneD: return aPrefix + "pWorkSpace->mRunicLaneD;";
        case TwistWorkSpaceSlot::kGloomLaneA: return aPrefix + "pWorkSpace->mGloomLaneA;";
        case TwistWorkSpaceSlot::kGloomLaneB: return aPrefix + "pWorkSpace->mGloomLaneB;";
        case TwistWorkSpaceSlot::kGloomLaneC: return aPrefix + "pWorkSpace->mGloomLaneC;";
        case TwistWorkSpaceSlot::kGloomLaneD: return aPrefix + "pWorkSpace->mGloomLaneD;";
        case TwistWorkSpaceSlot::kAbjurationLaneA: return aPrefix + "pWorkSpace->mAbjurationLaneA;";
        case TwistWorkSpaceSlot::kAbjurationLaneB: return aPrefix + "pWorkSpace->mAbjurationLaneB;";
        case TwistWorkSpaceSlot::kAbjurationLaneC: return aPrefix + "pWorkSpace->mAbjurationLaneC;";
        case TwistWorkSpaceSlot::kAbjurationLaneD: return aPrefix + "pWorkSpace->mAbjurationLaneD;";
        case TwistWorkSpaceSlot::kDivinationLaneA: return aPrefix + "pWorkSpace->mDivinationLaneA;";
        case TwistWorkSpaceSlot::kDivinationLaneB: return aPrefix + "pWorkSpace->mDivinationLaneB;";
        case TwistWorkSpaceSlot::kDivinationLaneC: return aPrefix + "pWorkSpace->mDivinationLaneC;";
        case TwistWorkSpaceSlot::kDivinationLaneD: return aPrefix + "pWorkSpace->mDivinationLaneD;";
        case TwistWorkSpaceSlot::kEvocationLaneA: return aPrefix + "pWorkSpace->mEvocationLaneA;";
        case TwistWorkSpaceSlot::kEvocationLaneB: return aPrefix + "pWorkSpace->mEvocationLaneB;";
        case TwistWorkSpaceSlot::kEvocationLaneC: return aPrefix + "pWorkSpace->mEvocationLaneC;";
        case TwistWorkSpaceSlot::kEvocationLaneD: return aPrefix + "pWorkSpace->mEvocationLaneD;";
        case TwistWorkSpaceSlot::kStasisLaneA: return aPrefix + "pWorkSpace->mStasisLaneA;";
        case TwistWorkSpaceSlot::kStasisLaneB: return aPrefix + "pWorkSpace->mStasisLaneB;";
        case TwistWorkSpaceSlot::kStasisLaneC: return aPrefix + "pWorkSpace->mStasisLaneC;";
        case TwistWorkSpaceSlot::kAlchemyLaneA: return aPrefix + "pWorkSpace->mAlchemyLaneA;";
        case TwistWorkSpaceSlot::kAlchemyLaneB: return aPrefix + "pWorkSpace->mAlchemyLaneB;";
        case TwistWorkSpaceSlot::kAlchemyLaneC: return aPrefix + "pWorkSpace->mAlchemyLaneC;";
        case TwistWorkSpaceSlot::kAlchemyLaneD: return aPrefix + "pWorkSpace->mAlchemyLaneD;";
        case TwistWorkSpaceSlot::kAuguryLaneA: return aPrefix + "pWorkSpace->mAuguryLaneA;";
        case TwistWorkSpaceSlot::kAuguryLaneB: return aPrefix + "pWorkSpace->mAuguryLaneB;";
        case TwistWorkSpaceSlot::kAuguryLaneC: return aPrefix + "pWorkSpace->mAuguryLaneC;";
        case TwistWorkSpaceSlot::kAuguryLaneD: return aPrefix + "pWorkSpace->mAuguryLaneD;";
        case TwistWorkSpaceSlot::kPsychicLaneA: return aPrefix + "pWorkSpace->mPsychicLaneA;";
        case TwistWorkSpaceSlot::kPsychicLaneB: return aPrefix + "pWorkSpace->mPsychicLaneB;";
        case TwistWorkSpaceSlot::kPsychicLaneC: return aPrefix + "pWorkSpace->mPsychicLaneC;";
        case TwistWorkSpaceSlot::kPsychicLaneD: return aPrefix + "pWorkSpace->mPsychicLaneD;";
        case TwistWorkSpaceSlot::kVoodooLaneA: return aPrefix + "pWorkSpace->mVoodooLaneA;";
        case TwistWorkSpaceSlot::kVoodooLaneB: return aPrefix + "pWorkSpace->mVoodooLaneB;";
        case TwistWorkSpaceSlot::kVoodooLaneC: return aPrefix + "pWorkSpace->mVoodooLaneC;";
        case TwistWorkSpaceSlot::kVoodooLaneD: return aPrefix + "pWorkSpace->mVoodooLaneD;";
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
    std::string aBaseAlias = BufAliasName(aSlot);
    switch (aSlot) {
        case TwistWorkSpaceSlot::kSourceLane:
            aBaseAlias = "pWorkSpace->mSourceLane";
            break;
        case TwistWorkSpaceSlot::kNonceLane:
            aBaseAlias = "pWorkSpace->mNonceLane";
            break;
        case TwistWorkSpaceSlot::kParamSource:
            aBaseAlias = "pSource";
            break;
        case TwistWorkSpaceSlot::kParamDestination:
            aBaseAlias = "pDestination";
            break;
        case TwistWorkSpaceSlot::kParamCrossA:
            aBaseAlias = "pCrossLaneA";
            break;
        case TwistWorkSpaceSlot::kParamCrossB:
            aBaseAlias = "pCrossLaneB";
            break;
        case TwistWorkSpaceSlot::kParamCrossC:
            aBaseAlias = "pCrossLaneC";
            break;
        case TwistWorkSpaceSlot::kParamCrossD:
            aBaseAlias = "pCrossLaneD";
            break;
        default:
            break;
    }
    return "std::uint8_t *" + BufAliasName(pKey) + " = " +
           aBaseAlias + " + (W_KEY * " +
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
    std::vector<TwistWorkSpaceSlot> mFlowSources;
    std::vector<TwistWorkSpaceSlot> mFlowDestinations;
};

void SetArxCallLaneFlow(ArxCallExport *pCall,
                        const GSeedRunStageConfig &pConfig) {
    if (pCall == nullptr) {
        return;
    }
    pCall->mFlowSources = pConfig.mFlowSources;
    pCall->mFlowDestinations = pConfig.mFlowDestinations;
}

bool UsesGrowCrossLanes(const GSeedRunStageConfig &pConfig) {
    for (const GSeedRunStageSliceSpec &aSlice : pConfig.mSlices) {
        std::vector<TwistWorkSpaceSlot> aSources =
            aSlice.IngressSources();
        const std::vector<TwistWorkSpaceSlot> aCrossSources =
            aSlice.CrossSources();
        aSources.insert(aSources.end(),
                        aCrossSources.begin(),
                        aCrossSources.end());

        for (const TwistWorkSpaceSlot aSource : aSources) {
            if ((aSource == TwistWorkSpaceSlot::kParamCrossA) ||
                (aSource == TwistWorkSpaceSlot::kParamCrossB)) {
                return true;
            }
        }
    }
    return false;
}

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
        if ((!pArxCall->mStartLine.empty() &&
             (pLine == pArxCall->mStartLine)) ||
            (!pArxCall->mEndLine.empty() &&
             (pLine == pArxCall->mEndLine))) {
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

std::string MainArxStateWriteOutText(const std::string &pIndent) {
    std::ostringstream aStream;
    for (const char *aLocalName : kExternalArxStateVariables) {
        const std::string aName(aLocalName);
        aStream << pIndent << "*p" << aName.substr(1U)
                << " = " << aName << ";\n";
    }
    return aStream.str();
}

std::string MainArxStateRestoreText(const std::string &pIndent) {
    std::ostringstream aStream;
    for (const char *aLocalName : kExternalArxStateVariables) {
        const std::string aName(aLocalName);
        aStream << pIndent << aName << " = *p"
                << aName.substr(1U) << ";\n";
    }
    return aStream.str();
}

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

    if (!pArxCall.mFlowSources.empty() &&
        !pArxCall.mFlowDestinations.empty()) {
        *pStream
            << "    //\n"
            << "    // src: "
            << CompactFlowList(pArxCall.mFlowSources) << "\n"
            << "    // dst: "
            << CompactFlowList(pArxCall.mFlowDestinations) << "\n"
            << "    //\n";
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
            aParameterMacro = pArxCall.mUsesCrossLanes
                ? "PARAMS_GROW_CROSS"
                : "PARAMS_GROW";
        }

        if (aParameterMacro != nullptr) {
            const bool aEndsArxSection =
                (pArxCall.mMethodName == "SEED_Q") ||
                (pArxCall.mMethodName == "KEY_B_H_C") ||
                (pArxCall.mMethodName == "TWIST_C");
            *pStream
            << "    " << pArxCall.mClassName << "::"
            << pArxCall.mMethodName << "(" << aParameterMacro << ");\n";
            if (!aEndsArxSection) {
                *pStream << '\n';
            }
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
    const bool pUseCrossParameters,
    const char *pBodySectionTitle = nullptr,
    const char *pKeyLaneMacroPrefix = nullptr,
    const char *pKeyLaneMacroFlow = nullptr,
    const std::string *pSeedDestinationSquash = nullptr) {
    if (pStream == nullptr) {
        SetError(pError, "Branch output stream was null.");
        return false;
    }

    const std::vector<const ArxCallExport *> &aArxCalls = pArxCalls;
    const bool aUseKeyLaneMacros =
        (pKeyLaneMacroPrefix != nullptr) &&
        (pKeyLaneMacroFlow != nullptr);

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
                if (!aUseKeyLaneMacros) {
                    // A conventional split alias is rendered from its
                    // full-lane alias.
                    AppendUniqueValue(
                        &aReferencedSlots,
                        static_cast<TwistWorkSpaceSlot>(
                            aBuffer.mKey.mSlot)
                    );
                }
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
        if (aUseKeyLaneMacros &&
            std::any_of(
                aReferencedLaneSplits.begin(),
                aReferencedLaneSplits.end(),
                [aSlot](const GSymbol &pBuffer) {
                    return pBuffer.mKey.mSlot ==
                        static_cast<std::uint16_t>(aSlot);
                })) {
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
        const TwistWorkSpaceSlot aSlot =
            static_cast<TwistWorkSpaceSlot>(aBuffer.mKey.mSlot);
        const std::string aAliasName =
            aUseKeyLaneMacros
                ? BufAliasName(aSlot)
                : BufAliasName(aBuffer);
        if (ContainsText(aDeclaredNames, aAliasName)) {
            continue;
        }
        std::string aDeclaration;
        if (aUseKeyLaneMacros) {
            const std::string aLaneName = KeyLaneName(aSlot);
            if (aLaneName.empty()) {
                SetError(pError,
                         "Key lane macro had no lane name.");
                return false;
            }
            aDeclaration =
                "std::uint8_t *" + aAliasName + " = " +
                pKeyLaneMacroPrefix + pKeyLaneMacroFlow + "_" +
                aLaneName + ";";
        } else {
            aDeclaration = LaneSplitAliasDeclaration(
                aBuffer.mKey,
                pUseCrossParameters
            );
        }
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
    bool aWroteBodySectionTitle = false;
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
        if (aLine == "SEED_DESTINATION_SQUASH;") {
            if (pSeedDestinationSquash == nullptr) {
                SetError(pError,
                         "Seed destination squash placeholder had no rendered line.");
                return false;
            }
            *pStream << *pSeedDestinationSquash;
            return true;
        }
        if (aLine == "WRITE_OUT_MAIN_ARX_STATE;") {
            *pStream << MainArxStateWriteOutText("    ");
            return true;
        }
        if (aLine == "RESTORE_MAIN_ARX_STATE;") {
            *pStream << MainArxStateRestoreText("    ");
            return true;
        }
        aLine = CollapseLocalArxStateArguments(std::move(aLine));
        if (pKeyLaneMacroPrefix != nullptr) {
            ReplaceAllText(&aLine,
                           "KEY_LANE_",
                           pKeyLaneMacroPrefix);
        }
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
            if (!aWroteBodySectionTitle &&
                (pBodySectionTitle != nullptr)) {
                *pStream
                    << "    ////////////////////////////////////////////////////////\n"
                    << "    //\n"
                    << "    // " << pBodySectionTitle << "\n";
                aWroteBodySectionTitle = true;
            }
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

        if (aUseKeyLaneMacros) {
            for (const GSymbol &aBuffer : aReferencedLaneSplits) {
                const TwistWorkSpaceSlot aSlot =
                    static_cast<TwistWorkSpaceSlot>(
                        aBuffer.mKey.mSlot);
                ReplaceAllText(&aScopeBlock,
                               BufAliasName(aBuffer),
                               BufAliasName(aSlot));
            }
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
                      const ArxCallExport *pArxCallP = nullptr,
                      const char *pKeyLaneMacroPrefix = nullptr,
                      const char *pKeyLaneMacroFlow = nullptr) {
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
        pUseCrossParameters,
        nullptr,
        pKeyLaneMacroPrefix,
        pKeyLaneMacroFlow
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

constexpr std::size_t kSeedStageCount = 17U;
constexpr std::size_t kKeyFlowCount =
    GFlowPlans::kKeyFlowCount;
constexpr std::size_t kKeyConfigCount =
    GFlowPlans::kKeyStageConfigCount;

std::string SeedMethodName(const std::size_t pStageIndex) {
    return "SEED_" +
        std::string(1U, static_cast<char>('A' + pStageIndex));
}

std::string SeedConfigName(const std::size_t pStageIndex) {
    return "GSeedRunSeed_" +
        std::string(1U, static_cast<char>('A' + pStageIndex));
}

std::string KeyMethodName(const std::size_t pConfigIndex) {
    const std::size_t aPhaseIndex = pConfigIndex / kKeyFlowCount;
    const std::size_t aLogicalKeyIndex = pConfigIndex % kKeyFlowCount;
    return KeyFlowName(aLogicalKeyIndex) + "_" +
        std::string(1U, static_cast<char>('A' + aPhaseIndex));
}

std::string KeyConfigName(const std::size_t pConfigIndex) {
    return "GSeedRun" + KeyMethodName(pConfigIndex);
}

std::string KeyBatchName(const std::size_t pConfigIndex) {
    const std::size_t aPhaseIndex = pConfigIndex / kKeyFlowCount;
    const std::size_t aLogicalKeyIndex = pConfigIndex % kKeyFlowCount;
    const char aKeyBox =
        aLogicalKeyIndex < GFlowPlans::kKeyBoxFlowCount ? 'a' : 'b';
    const char aKeyRow = static_cast<char>(
        'a' + (aLogicalKeyIndex % GFlowPlans::kKeyBoxFlowCount));
    const char aPhase = static_cast<char>('a' + aPhaseIndex);
    return std::string("key_") + aKeyBox + "_loop_" + aKeyRow +
        "_" + aPhase;
}

bool ResolveSeedStageConfigs(const std::vector<GSeedRunStageConfig> &pConfigs,
                             std::vector<GSeedRunStageConfig> *pResolved,
                             std::string *pError) {
    if (pResolved == nullptr) {
        SetError(pError, "Seed ARX stage config destination was null.");
        return false;
    }

    *pResolved = pConfigs;
    if (pResolved->size() != kSeedStageCount) {
        SetError(pError,
                 "Seed ARX export requires exactly twenty-five supplied "
                 "stage configs.");
        return false;
    }

    for (std::size_t i = 0U; i < pResolved->size(); ++i) {
        if ((*pResolved)[i].mStageName != SeedConfigName(i)) {
            SetError(pError,
                     "Seed ARX stage config order did not match A through Y.");
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
    if (pResolved->size() != kKeyConfigCount) {
        SetError(pError,
                 "Seed key-box ARX export requires exactly eighty supplied "
                 "KEY stage configs.");
        return false;
    }
    for (std::size_t i = 0U; i < pResolved->size(); ++i) {
        if (((*pResolved)[i].mStageName != KeyConfigName(i)) ||
            ((*pResolved)[i].mBatchName != KeyBatchName(i))) {
            SetError(pError,
                     "Seed key-box ARX stage config order did not match "
                     "the five-phase KEY_A_A_A through KEY_B_H_E order.");
            return false;
        }
        if ((*pResolved)[i].mSlices.size() != 4U) {
            SetError(pError,
                     "Each seed key-box ARX stage must contain exactly four loops.");
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
    if (pResolved->size() != 3U) {
        SetError(pError,
                 "Twist ARX export requires exactly three supplied "
                 "stage configs.");
        return false;
    }

    static const std::array<const char *, 3> kStageNames = {
        "GTwistRunTwist_A", "GTwistRunTwist_B", "GTwistRunTwist_C",
    };
    for (std::size_t i = 0U; i < pResolved->size(); ++i) {
        if ((*pResolved)[i].mStageName != kStageNames[i]) {
            SetError(pError, "Twist ARX stage config order did not match A through C.");
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
                            const bool pUsesCrossLanes,
                            const bool pDefinition) {
    if (pStream == nullptr) {
        return;
    }

    const std::string aPrefix = pDefinition ?
        ("void " + pClassName + "::") :
        "    static void ";
    const std::string aSuffix = pDefinition ? " {\n" : ";\n";
    *pStream
    << aPrefix << pMethodName << "(TwistWorkSpace *pWorkSpace,\n";
    if (pUsesCrossLanes) {
        *pStream
        << "                     std::uint8_t *pCrossLaneA,\n"
        << "                     std::uint8_t *pCrossLaneB,\n";
    }
    *pStream << "                     MUTABLE_PARAMS)" << aSuffix;
}

void AppendKDFSignature(std::ostringstream *pStream,
                        const std::string &pClassName,
                        const std::string &pMethodName,
                        const bool pDefinition,
                        const bool pOverride = true) {
    if (pStream == nullptr) {
        return;
    }

    const std::string aPrefix = pDefinition
        ? ("void " + pClassName + "::")
        : "    void ";
    const std::string aSuffix = pDefinition
        ? " {\n"
        : (pOverride ? " override;\n" : ";\n");
    *pStream
    << aPrefix << pMethodName << "(TwistWorkSpace *pWorkSpace,\n"
    << "               std::uint64_t pNonce,\n"
    << "               TwistDomainConstants *pConstants,\n"
    << "               TwistDomainSaltSet *pDomainSaltSet,\n"
    << "               MUTABLE_PARAMS)" << aSuffix;
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
    << "                  std::uint8_t *pCrossLaneA,\n"
    << "                  std::uint8_t *pCrossLaneB,\n"
    << "                  MUTABLE_PARAMS)" << aSuffix;
}

constexpr std::size_t kKDFDomainCount = 6U;
constexpr std::size_t kKDFFamilyCount = 3U;
constexpr std::size_t kKDFStageCount = 3U;
constexpr std::size_t kKDFBranchCount =
    kKDFDomainCount * kKDFFamilyCount;
constexpr std::size_t kKDFConfigCount =
    kKDFBranchCount * kKDFStageCount;

std::size_t KDFBranchIndex(const std::size_t pDomain,
                           const std::size_t pFamily) {
    return (pDomain * kKDFFamilyCount) + pFamily;
}

std::size_t KDFConfigIndex(const std::size_t pDomain,
                           const std::size_t pFamily,
                           const std::size_t pStage) {
    return (KDFBranchIndex(pDomain, pFamily) * kKDFStageCount) + pStage;
}

std::string KDFWrapperMethodName(const std::size_t pFamily,
                                 const std::size_t pDomain) {
    return std::string("KDF_") + static_cast<char>('A' + pFamily) +
        "_" + static_cast<char>('A' + pDomain);
}

std::string KDFArxMethodName(const std::size_t pFamily,
                             const std::size_t pStage,
                             const std::size_t pDomain) {
    return std::string("KDF_") + static_cast<char>('A' + pFamily) +
        "_" + static_cast<char>('A' + pStage) +
        "_" + static_cast<char>('A' + pDomain);
}

bool ExportArxCompanionFiles(const std::string &pRoot,
                             const std::string &pClassName,
                             const std::string &pExpanderName,
                             const std::size_t pCandidateIndex,
                             const std::vector<GSeedRunStageConfig> &pKDFStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pSeedStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pSeedKeyBoxStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pTwistStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pGrowAStageConfigs,
                             const std::vector<GSeedRunStageConfig> &pGrowBStageConfigs,
    std::string *pError) {
    const std::string aArxClassName = pClassName + "_Arx";
    const std::string aKeyLaneMacroPrefix =
        KeyLaneMacroPrefix(pExpanderName);
    const std::string aHeaderPath = FileIO::Join(pRoot, aArxClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(pRoot, aArxClassName + ".cpp");

    if (pKDFStageConfigs.size() != kKDFConfigCount) {
        SetError(pError,
                 "ARX export expected 54 domain-specific KDF stage configs.");
        return false;
    }
    std::array<std::string, kKDFConfigCount> aKDFMethodNames;
    std::array<TwistProgramBranch, kKDFConfigCount> aBranchesKDF;
    for (std::size_t aDomain = 0U; aDomain < kKDFDomainCount; ++aDomain) {
        for (std::size_t aFamily = 0U; aFamily < kKDFFamilyCount; ++aFamily) {
            for (std::size_t aStage = 0U; aStage < kKDFStageCount; ++aStage) {
                const std::size_t aIndex =
                    KDFConfigIndex(aDomain, aFamily, aStage);
                aKDFMethodNames[aIndex] =
                    KDFArxMethodName(aFamily, aStage, aDomain);
                if (!BuildExportArxKDFBranch(&aBranchesKDF[aIndex],
                                             pKDFStageConfigs[aIndex],
                                             aKDFMethodNames[aIndex],
                                             pError)) {
                    return false;
                }
            }
        }
    }
    std::vector<GSeedRunStageConfig> aSeedStageConfigs;
    if (!ResolveSeedStageConfigs(pSeedStageConfigs, &aSeedStageConfigs, pError)) {
        return false;
    }
    std::array<std::string, kSeedStageCount> aSeedMethodNames;
    std::array<TwistProgramBranch, kSeedStageCount> aBranchesSeed;
    for (std::size_t i = 0U; i < aBranchesSeed.size(); ++i) {
        aSeedMethodNames[i] = SeedMethodName(i);
        if (!BuildExportArxSeedBranch(&aBranchesSeed[i],
                                      aSeedStageConfigs[i],
                                      aSeedMethodNames[i],
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
    std::array<std::string, kKeyConfigCount> aKeyMethodNames;
    for (std::size_t i = 0U; i < aKeyMethodNames.size(); ++i) {
        aKeyMethodNames[i] = KeyMethodName(i);
    }
    std::array<TwistProgramBranch, kKeyConfigCount> aBranchesKEY;
    for (std::size_t i = 0U; i < aBranchesKEY.size(); ++i) {
        if (!BuildExportArxSeedBranch(&aBranchesKEY[i],
                                      aSeedKeyBoxStageConfigs[i],
                                      aKeyMethodNames[i],
                                      pError,
                                      "key",
                                      (i < 64U) ||
                                      ((i != 71U) && (i != 79U)))) {
            return false;
        }
    }

    std::vector<GSeedRunStageConfig> aTwistStageConfigs;
    if (!ResolveTwistStageConfigs(pTwistStageConfigs, &aTwistStageConfigs, pError)) {
        return false;
    }
    static const std::array<const char *, 3> kTwistMethodNames = {
        "TWIST_A", "TWIST_B", "TWIST_C",
    };
    std::array<TwistProgramBranch, 3> aBranchesTwist;
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
    for (std::size_t aDomain = 0U; aDomain < kKDFDomainCount; ++aDomain) {
        for (std::size_t aFamily = 0U; aFamily < kKDFFamilyCount; ++aFamily) {
            for (std::size_t aStage = 0U; aStage < kKDFStageCount; ++aStage) {
                const std::size_t aIndex =
                    KDFConfigIndex(aDomain, aFamily, aStage);
                const std::string aFamilyName =
                    std::string("KDF_") + static_cast<char>('A' + aFamily);
                AppendFlowLoops(&aFlowLoops,
                                "KDF",
                                aFamilyName,
                                aKDFMethodNames[aIndex],
                                pKDFStageConfigs[aIndex]);
            }
        }
    }
    for (std::size_t i = 0U; i < aSeedStageConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "SEED",
                        "SEED",
                        aSeedMethodNames[i],
                        aSeedStageConfigs[i]);
    }
    for (std::size_t i = 0U; i < aSeedKeyBoxStageConfigs.size(); ++i) {
        AppendFlowLoops(&aFlowLoops,
                        "KEY",
                        ((i % 16U) < 8U) ? "KEY_A" : "KEY_B",
                        aKeyMethodNames[i],
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
    for (const std::string &aMethodName : aKDFMethodNames) {
        AppendArxKDFSignature(&aHeader,
                              aArxClassName,
                              aMethodName,
                              false);
    }
    for (const std::string &aMethodName : aSeedMethodNames) {
        AppendArxSeedSignature(&aHeader,
                               aArxClassName,
                               aMethodName,
                               false,
                               true);
    }
    for (const std::string &aMethodName : aKeyMethodNames) {
        AppendArxSeedSignature(&aHeader,
                               aArxClassName,
                               aMethodName,
                               false);
    }
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_A", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_B", false, false);
    AppendArxTwistSignature(&aHeader, aArxClassName, "TWIST_C", false, false);
    for (std::size_t i = 0U; i < kGrowAMethodNames.size(); ++i) {
        AppendArxGrowSignature(&aHeader,
                               aArxClassName,
                               kGrowAMethodNames[i],
                               UsesGrowCrossLanes(aGrowAStageConfigs[i]),
                               false);
    }
    for (std::size_t i = 0U; i < kGrowBMethodNames.size(); ++i) {
        AppendArxGrowSignature(&aHeader,
                               aArxClassName,
                               kGrowBMethodNames[i],
                               UsesGrowCrossLanes(aGrowBStageConfigs[i]),
                               false);
    }
    aHeader << "};\n"
            << "\n"
            << "//\n"
            << "// Key-lane assignments\n"
            << "//\n";
    for (std::size_t aLogicalKeyIndex = 0U;
         aLogicalKeyIndex < KeyLaneAssignments::kKeyFunctionCount;
         ++aLogicalKeyIndex) {
        aHeader << "\n// " << KeyFlowName(aLogicalKeyIndex) << "\n";
        for (const KeyLaneAssignments::Assignment &aAssignment :
             KeyLaneAssignments::kAssignments) {
            if (!IsKeyLaneMacroSlot(aAssignment.mLane)) {
                continue;
            }
            const std::string aLaneName =
                KeyLaneName(aAssignment.mLane);
            const std::uint8_t aSplit =
                KeyLaneAssignments::Split(
                    aAssignment.mLane,
                    aLogicalKeyIndex,
                    pCandidateIndex
                );
            aHeader
                << "#define "
                << KeyLaneMacroName(aKeyLaneMacroPrefix,
                                    aLogicalKeyIndex,
                                    aAssignment.mLane)
                << " (pWorkSpace->m" << aLaneName
                << " + (W_KEY * "
                << static_cast<unsigned int>(aSplit)
                << "U))\n";
        }
    }

    std::ostringstream aCpp;
    aCpp << "#include \"" << aArxClassName << ".hpp\"\n"
    << "#include \"TwistFunctional.hpp\"\n"
    << "#include \"TwistMix32.hpp\"\n"
    << "#include \"TwistMix64.hpp\"\n"
    << "\n"
    << "#include <cstdint>\n"
    << "\n";
    for (std::size_t aIndex = 0U;
         aIndex < aBranchesKDF.size();
         ++aIndex) {
        AppendArxKDFSignature(&aCpp,
                              aArxClassName,
                              aKDFMethodNames[aIndex],
                              true);
        if (!AppendBranchBody(aBranchesKDF[aIndex],
                              true,
                              &aCpp,
                              pError)) {
            return false;
        }
        aCpp << "}\n\n";
    }
    for (std::size_t i = 0U; i < aBranchesSeed.size(); ++i) {
        AppendArxSeedSignature(&aCpp,
                               aArxClassName,
                               aSeedMethodNames[i],
                               true,
                               true);
        if (!AppendBranchBody(aBranchesSeed[i], false, &aCpp, pError)) {
            return false;
        }
        aCpp << "}\n\n";
    }
    for (std::size_t i = 0U; i < aBranchesKEY.size(); ++i) {
        AppendArxSeedSignature(&aCpp,
                               aArxClassName,
                               aKeyMethodNames[i],
                               true);
        const std::string aKeyFlowName = KeyFlowName(i % 16U);
        const std::vector<const ArxCallExport *> aNoArxCalls;
        if (!AppendBranchBodyWithArxCalls(
                aBranchesKEY[i],
                false,
                &aCpp,
                pError,
                aNoArxCalls,
                /* pForceWorkspaceSourceAlias = */ false,
                /* pSkipTwistDiffuseBatches = */ false,
                /* pUseCrossParameters = */ false,
                /* pBodySectionTitle = */ nullptr,
                aKeyLaneMacroPrefix.c_str(),
                aKeyFlowName.c_str())) {
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
    for (std::size_t i = 0U; i < aBranchesGrowA.size(); ++i) {
        AppendArxGrowSignature(&aCpp,
                               aArxClassName,
                               kGrowAMethodNames[i],
                               UsesGrowCrossLanes(aGrowAStageConfigs[i]),
                               true);
        if (!AppendCrossParameterBranchBody(aBranchesGrowA[i],
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
                               UsesGrowCrossLanes(aGrowBStageConfigs[i]),
                               true);
        if (!AppendCrossParameterBranchBody(aBranchesGrowB[i],
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
              const std::vector<GSeedRunStageConfig> &pKDFStageConfigs,
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
        if (pKDFStageConfigs.size() != mKDFCalls.size()) {
            SetError(pError,
                     "GArx expected 54 domain-specific KDF stage configs.");
            return false;
        }
        for (std::size_t aDomain = 0U; aDomain < kKDFDomainCount; ++aDomain) {
            for (std::size_t aFamily = 0U; aFamily < kKDFFamilyCount; ++aFamily) {
                for (std::size_t aStage = 0U; aStage < kKDFStageCount; ++aStage) {
                    const std::size_t aIndex =
                        KDFConfigIndex(aDomain, aFamily, aStage);
                    const GSeedRunStageConfig &aConfig =
                        pKDFStageConfigs[aIndex];
                    ArxCallExport &aCall = mKDFCalls[aIndex];
                    aCall.mKind = ArxCallKind::kKDF;
                    aCall.mBatchName = aConfig.mBatchName;
                    aCall.mStartLine = aConfig.mStartLine;
                    aCall.mEndLine = aConfig.mEndLine;
                    aCall.mClassName = mArxClassName;
                    aCall.mMethodName =
                        KDFArxMethodName(aFamily, aStage, aDomain);
                    SetArxCallLaneFlow(&aCall, aConfig);
                }
            }
        }

        for (std::size_t i = 0U; i < mSeedCalls.size(); ++i) {
            ArxCallExport &aCall = mSeedCalls[i];
            const GSeedRunStageConfig &aConfig = aSeedStageConfigs[i];
            aCall.mKind = ArxCallKind::kSeed;
            aCall.mUsesNonce = true;
            aCall.mUsesCrossLanes = false;
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = SeedMethodName(i);
            SetArxCallLaneFlow(&aCall, aConfig);
        }

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
            aCall.mMethodName = KeyMethodName(i);
            SetArxCallLaneFlow(&aCall, aConfig);
        }

        const std::array<ArxCallExport *, 3> aTwistCalls = {
            &mTwist_A, &mTwist_B, &mTwist_C,
        };
        static const std::array<const char *, 3> kTwistMethodNames = {
            "TWIST_A", "TWIST_B", "TWIST_C",
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
            SetArxCallLaneFlow(&aCall, aConfig);
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
            aCall.mUsesCrossLanes = UsesGrowCrossLanes(aConfig);
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kGrowAMethodNames[i];
            SetArxCallLaneFlow(&aCall, aConfig);
        }
        for (std::size_t i = 0U; i < aGrowBCalls.size(); ++i) {
            ArxCallExport &aCall = *aGrowBCalls[i];
            const GSeedRunStageConfig &aConfig = aGrowBStageConfigs[i];
            aCall.mKind = ArxCallKind::kGrow;
            aCall.mUsesNonce = false;
            aCall.mUsesCrossLanes = UsesGrowCrossLanes(aConfig);
            aCall.mBatchName = aConfig.mBatchName;
            aCall.mStartLine = aConfig.mStartLine;
            aCall.mEndLine = aConfig.mEndLine;
            aCall.mClassName = mArxClassName;
            aCall.mMethodName = kGrowBMethodNames[i];
            SetArxCallLaneFlow(&aCall, aConfig);
        }

        return ExportArxCompanionFiles(pRoot,
                                       pClassName,
                                       pExpanderName,
                                       pCandidateIndex,
                                       pKDFStageConfigs,
                                       aSeedStageConfigs,
                                       aSeedKeyBoxStageConfigs,
                                       aTwistStageConfigs,
                                       aGrowAStageConfigs,
                                       aGrowBStageConfigs,
                                       pError);
    }

    const ArxCallExport* KDFCall(const std::size_t pDomain,
                                 const std::size_t pFamily,
                                 const std::size_t pStage) const {
        if ((pDomain >= kKDFDomainCount) ||
            (pFamily >= kKDFFamilyCount) ||
            (pStage >= kKDFStageCount)) {
            return nullptr;
        }
        return &mKDFCalls[KDFConfigIndex(pDomain, pFamily, pStage)];
    }

    const ArxCallExport* KDF_A_A() const {
        return KDFCall(0U, 0U, 0U);
    }

    const ArxCallExport* KDF_A_B() const {
        return KDFCall(0U, 0U, 1U);
    }

    const ArxCallExport* KDF_A_C() const {
        return KDFCall(0U, 0U, 2U);
    }

    const ArxCallExport* KDF_B_A() const {
        return KDFCall(0U, 1U, 0U);
    }

    const ArxCallExport* KDF_B_B() const {
        return KDFCall(0U, 1U, 1U);
    }

    const ArxCallExport* KDF_B_C() const {
        return KDFCall(0U, 1U, 2U);
    }

    const ArxCallExport* KDF_C_A() const {
        return KDFCall(0U, 2U, 0U);
    }

    const ArxCallExport* KDF_C_B() const {
        return KDFCall(0U, 2U, 1U);
    }

    const ArxCallExport* KDF_C_C() const {
        return KDFCall(0U, 2U, 2U);
    }

    std::vector<const ArxCallExport *> SeedCalls() const {
        std::vector<const ArxCallExport *> aCalls;
        aCalls.reserve(mSeedCalls.size());
        for (const ArxCallExport &aCall : mSeedCalls) {
            aCalls.push_back(&aCall);
        }
        return aCalls;
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
    std::array<ArxCallExport, kKDFConfigCount> mKDFCalls;
    std::array<ArxCallExport, kSeedStageCount> mSeedCalls;
    std::array<ArxCallExport, kKeyConfigCount> mKEYs;
    ArxCallExport mTwist_A;
    ArxCallExport mTwist_B;
    ArxCallExport mTwist_C;
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
    const std::string aKeyLaneMacroPrefix =
        KeyLaneMacroPrefix(aBaseName);

    if (!EnsureControlValues(pError)) {
        return false;
    }
    if (mControlCandidateIndex >= KeyForkControl::GeneratedCount()) {
        SetError(pError,
                 "Control candidate index was out of range.");
        return false;
    }
    const KeyForkControl::Candidate *aKeyForkCandidate =
        KeyForkControl::CandidateAt(mControlCandidateIndex);
    if (aKeyForkCandidate == nullptr) {
        SetError(pError,
                 "KeyForkControl failed to provide its selected candidate.");
        return false;
    }
    const std::string aSeedDestinationSquash =
        RandomDestinationSquashLine("Crystal");
    const std::string aTwistDestinationSquash =
        RandomDestinationSquashLine("Crystal");

    const std::string aRootInput = pRootPath.empty() ? "generated/cpp" : pRootPath;
    const std::string aRoot = ResolveOutputPathFromProjectRoot(aRootInput);

    const std::string aHeaderPath = FileIO::Join(aRoot, aClassName + ".hpp");
    const std::string aCppPath = FileIO::Join(aRoot, aClassName + ".cpp");
    GArx aArx;
    if (!aArx.Bake(aRoot,
                   aClassName,
                   aBaseName,
                   mControlCandidateIndex,
                   mKDFStageConfigs,
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
    std::ostringstream aLegacyGrowKeyA;
    AppendGrowKeySignature(&aLegacyGrowKeyA,
                           aClassName,
                           "GrowKeyA",
                           true);
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

    const std::string aTwistForkKeyHalfAMethod =
        RenderTwistForkKeyHalf(aClassName,
                               aSnapshot.mTwistForkEarthLanes,
                               aSnapshot.mTwistForkCrystalLanes,
                               aSnapshot.mTwistForkMuLanes,
                               aSnapshot.mTwistForkLelLanes,
                               aSnapshot.mTwistForkGozLanes,
                               aSnapshot.mTwistForkFinalALanes,
                               *aKeyForkCandidate,
                               false);
    const std::string aTwistForkKeyHalfBMethod =
        RenderTwistForkKeyHalf(aClassName,
                               aSnapshot.mTwistForkEarthLanes,
                               aSnapshot.mTwistForkCrystalLanes,
                               aSnapshot.mTwistForkMuLanes,
                               aSnapshot.mTwistForkLelLanes,
                               aSnapshot.mTwistForkGozLanes,
                               aSnapshot.mTwistForkFinalBLanes,
                               *aKeyForkCandidate,
                               true);
    if (aTwistForkKeyHalfAMethod.empty() ||
        aTwistForkKeyHalfBMethod.empty()) {
        SetError(pError,
                 "Twist fork source, scratch, or final lanes could not be rendered.");
        return false;
    }

    const auto RenderKeyDiffuseMethod = [&aClassName,
                                         &aKeyLaneMacroPrefix](
        const char *pMethodName,
        const std::size_t pLogicalKeyIndex,
        const std::array<TwistWorkSpaceSlot, 4U> &pInputs,
        const std::array<TwistWorkSpaceSlot, 4U> &pOutputs,
        const std::array<TwistWorkSpaceSlot, 4U> &pEntropy) {
        std::ostringstream aMethod;
        aMethod << "void " << aClassName << "::" << pMethodName
                << "(TwistWorkSpace *pWorkSpace) {\n";
        const char *aDomainName =
            pLogicalKeyIndex < 8U
                ? "mKeySpawnAConstants"
                : "mKeySpawnBConstants";
        const auto KeyLaneMacro = [&](const TwistWorkSpaceSlot pLane) {
            return KeyLaneMacroName(aKeyLaneMacroPrefix,
                                    pLogicalKeyIndex,
                                    pLane);
        };
        aMethod << "    TwistDiffuse::KeyDiffuseWithDomainWords(\n";
        aMethod
            << "        " << KeyLaneMacro(pEntropy[0U]) << ", "
            << KeyLaneMacro(pEntropy[1U]) << ", // entropy lanes\n"
            << "        " << KeyLaneMacro(pEntropy[2U]) << ", "
            << KeyLaneMacro(pEntropy[3U]) << ", // entropy lanes\n"
            << "        " << KeyLaneMacro(pInputs[0U]) << ", "
            << KeyLaneMacro(pInputs[1U]) << ", // input lanes\n"
            << "        " << KeyLaneMacro(pInputs[2U]) << ", "
            << KeyLaneMacro(pInputs[3U]) << ", // input lanes\n"
            << "        " << KeyLaneMacro(pOutputs[0U]) << ", "
            << KeyLaneMacro(pOutputs[1U]) << ", // output lanes\n"
            << "        " << KeyLaneMacro(pOutputs[2U]) << ", "
            << KeyLaneMacro(pOutputs[3U]) << ", // output lanes\n";
        aMethod
            << "        pWorkSpace->mIndexList256A, pWorkSpace->mIndexList256B, pWorkSpace->mIndexList256C, pWorkSpace->mIndexList256D,\n"
            << "        &mMatrix, pWorkSpace->mDomainBundle." << aDomainName << ".mMatrixSelectA, pWorkSpace->mDomainBundle." << aDomainName << ".mMatrixSelectB,\n"
            << "        pWorkSpace->mDomainBundle." << aDomainName << ".mMatrixUnrollA, pWorkSpace->mDomainBundle." << aDomainName << ".mMatrixUnrollB,\n"
            << "        pWorkSpace->mDomainBundle." << aDomainName << ".mMatrixArgA, pWorkSpace->mDomainBundle." << aDomainName << ".mMatrixArgB, pWorkSpace->mDomainBundle." << aDomainName << ".mMatrixArgC, pWorkSpace->mDomainBundle." << aDomainName << ".mMatrixArgD);\n";
        aMethod << "}\n";
        return aMethod.str();
    };

    const auto KeyDiffuseMethodName = [](
        const char pDiffuseStage,
        const std::size_t pLogicalKeyIndex) {
        const char aKeyBoxName =
            (pLogicalKeyIndex < 8U) ? 'A' : 'B';
        const char aKeyRowName = static_cast<char>(
            'A' + (pLogicalKeyIndex % 8U));
        return std::string("KeyDiffuse_") + pDiffuseStage + "_" +
            aKeyBoxName + "_" + aKeyRowName;
    };

    const std::array<TwistWorkSpaceSlot, 4U> aKeyDiffuseAInputs = {{
        TwistWorkSpaceSlot::kPlasmaLaneA,
        TwistWorkSpaceSlot::kPlasmaLaneB,
        TwistWorkSpaceSlot::kPlasmaLaneC,
        TwistWorkSpaceSlot::kPlasmaLaneD,
    }};
    const std::array<TwistWorkSpaceSlot, 4U> aKeyDiffuseAOutputs = {{
        TwistWorkSpaceSlot::kRainbowLaneA,
        TwistWorkSpaceSlot::kRainbowLaneB,
        TwistWorkSpaceSlot::kRainbowLaneC,
        TwistWorkSpaceSlot::kRainbowLaneD,
    }};
    const std::array<TwistWorkSpaceSlot, 4U> aKeyDiffuseAEntropy = {{
        TwistWorkSpaceSlot::kArcaneLaneA,
        TwistWorkSpaceSlot::kArcaneLaneB,
        TwistWorkSpaceSlot::kArcaneLaneC,
        TwistWorkSpaceSlot::kArcaneLaneD,
    }};
    const std::array<TwistWorkSpaceSlot, 4U> aKeyDiffuseBInputs = {{
        TwistWorkSpaceSlot::kVaporLaneA,
        TwistWorkSpaceSlot::kVaporLaneB,
        TwistWorkSpaceSlot::kVaporLaneC,
        TwistWorkSpaceSlot::kVaporLaneD,
    }};
    const std::array<TwistWorkSpaceSlot, 4U> aKeyDiffuseBOutputs = {{
        TwistWorkSpaceSlot::kFrostLaneA,
        TwistWorkSpaceSlot::kFrostLaneB,
        TwistWorkSpaceSlot::kFrostLaneC,
        TwistWorkSpaceSlot::kFrostLaneD,
    }};
    const std::array<TwistWorkSpaceSlot, 4U> aKeyDiffuseBEntropy = {{
        TwistWorkSpaceSlot::kWaterLaneA,
        TwistWorkSpaceSlot::kWaterLaneB,
        TwistWorkSpaceSlot::kWaterLaneC,
        TwistWorkSpaceSlot::kWaterLaneD,
    }};

    std::ostringstream aKeyDiffuseDeclarations;
    std::ostringstream aKeyDiffuseMethods;
    for (const char aDiffuseStage : {'A', 'B'}) {
        for (std::size_t aLogicalKeyIndex = 0U;
             aLogicalKeyIndex < 16U;
             ++aLogicalKeyIndex) {
            const std::string aMethodName =
                KeyDiffuseMethodName(aDiffuseStage, aLogicalKeyIndex);
            aKeyDiffuseDeclarations
                << "    void " << aMethodName
                << "(TwistWorkSpace *pWorkSpace);\n";
            aKeyDiffuseMethods
                << RenderKeyDiffuseMethod(
                    aMethodName.c_str(),
                    aLogicalKeyIndex,
                    (aDiffuseStage == 'A')
                        ? aKeyDiffuseAInputs
                        : aKeyDiffuseBInputs,
                    (aDiffuseStage == 'A')
                        ? aKeyDiffuseAOutputs
                        : aKeyDiffuseBOutputs,
                    (aDiffuseStage == 'A')
                        ? aKeyDiffuseAEntropy
                        : aKeyDiffuseBEntropy)
                << "\n";
        }
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
    << "\n";
    for (std::size_t aDomain = 0U; aDomain < kKDFDomainCount; ++aDomain) {
        for (std::size_t aFamily = 0U; aFamily < kKDFFamilyCount; ++aFamily) {
            AppendKDFSignature(&aHeader,
                               aClassName,
                               KDFWrapperMethodName(aFamily, aDomain),
                               false,
                               false);
        }
    }
    aHeader
    << "    void Seed(TwistWorkSpace *pWorkSpace,\n"
    << "              TwistFarmSalt *pFarmSalt,\n"
    << "              std::uint64_t pNonce,\n"
    << "              std::uint8_t *pPassword,\n"
    << "              std::size_t pPasswordByteLength,\n"
    << "              std::uint8_t *pDestination,\n"
    << "              MUTABLE_PARAMS) override;\n"
    << "    void TwistBlock(TwistWorkSpace *pWorkSpace,\n"
    << "                    std::uint8_t *pSource,\n"
    << "                    std::uint8_t *pCrossLaneA,\n"
    << "                    std::uint8_t *pCrossLaneB,\n"
    << "                    std::uint8_t *pCrossLaneC,\n"
    << "                    std::uint8_t *pCrossLaneD,\n"
    << "                    std::uint8_t *pDestination,\n"
    << "                    bool pStifleKey,\n"
    << "                    MUTABLE_PARAMS) override;\n";
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
    aHeader << "    void TwistForkKeyHalfA(TwistWorkSpace *pWorkSpace);\n"
            << "    void TwistForkKeyHalfB(TwistWorkSpace *pWorkSpace);\n"
            << aKeyDiffuseDeclarations.str();
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
    << "#include \"TwistMix16.hpp\"\n"
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
    << "    mDomainBundleEphemeralA.Zero();\n"
    << "    mDomainBundleEphemeralB.Zero();\n"
    << "}\n"
    << "\n";
    for (std::size_t aDomain = 0U; aDomain < kKDFDomainCount; ++aDomain) {
        for (std::size_t aFamily = 0U; aFamily < kKDFFamilyCount; ++aFamily) {
            AppendKDFSignature(&aCpp,
                               aClassName,
                               KDFWrapperMethodName(aFamily, aDomain),
                               true,
                               false);
            const TwistProgramBranch &aBranch =
                aSnapshot.mKDFDomainBranches[
                    KDFBranchIndex(aDomain, aFamily)];
            if (!AppendBranchBody(aBranch,
                                  true,
                                  &aCpp,
                                  pError,
                                  aArx.KDFCall(aDomain, aFamily, 0U),
                                  aArx.KDFCall(aDomain, aFamily, 1U),
                                  aArx.KDFCall(aDomain, aFamily, 2U))) {
                return false;
            }
            aCpp << "}\n\n";
        }
    }

    aCpp << "void " << aClassName << "::Seed(TwistWorkSpace *pWorkSpace,\n"
    << "                                 TwistFarmSalt *pFarmSalt,\n"
    << "                                 std::uint64_t pNonce,\n"
    << "                                 std::uint8_t *pPassword,\n"
    << "                                 std::size_t pPasswordByteLength,\n"
    << "                                 std::uint8_t *pDestination,\n"
    << "                                 MUTABLE_PARAMS) {\n"
    << "    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr) ||\n"
    << "        (pDestination == nullptr) || MUTABLE_PARAMS_ARE_NULL) { return; }\n"
    << "\n"
    << "    UnrollPassword(pWorkSpace->mSourceLane, pPassword, pPasswordByteLength);\n"
    << "    UnrollNonce(pWorkSpace->mNonceLane, pNonce);\n"
    << InbuiltDomainBundleAssignmentLines()
    << "    mDomainBundleEphemeralA.Zero();\n"
    << "    mDomainBundleEphemeralB.Zero();\n"
    << "    pWorkSpace->mDomainBundle.Zero();\n";
    std::vector<const ArxCallExport *> aSeedArxCalls =
        aArx.SeedCalls();
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
            /* pUseCrossParameters = */ false,
            /* pBodySectionTitle = */ nullptr,
            aKeyLaneMacroPrefix.c_str(),
            /* pKeyLaneMacroFlow = */ nullptr,
            &aSeedDestinationSquash)) {
        return false;
    }
    aCpp << "\n"
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
    << "                                       std::uint8_t *pDestination,\n"
    << "                                       bool pStifleKey,\n"
    << "                                       MUTABLE_PARAMS) {\n"
    << "    if ((pWorkSpace == nullptr) || (pSource == nullptr) ||\n"
    << "        (pCrossLaneA == nullptr) || (pCrossLaneB == nullptr) ||\n"
    << "        (pCrossLaneC == nullptr) || (pCrossLaneD == nullptr) ||\n"
    << "        (pDestination == nullptr) || MUTABLE_PARAMS_ARE_NULL) { return; }\n";
    const std::vector<const ArxCallExport *> aTwistArxCalls = {
        aArx.TWIST_A(), aArx.TWIST_B(), aArx.TWIST_C(),
    };
    if (!AppendBranchBodyWithArxCalls(
            aSnapshot.mTwister,
            false,
            &aCpp,
            pError,
            aTwistArxCalls,
            /* pForceWorkspaceSourceAlias = */ false,
            /* pSkipTwistDiffuseBatches = */ false,
            /* pUseCrossParameters = */ true,
            "Main twist loops")) {
        return false;
    }
    aCpp << "    //\n"
         << "    ////////////////////////////////////////////////////////\n"
         << "\n"
         << "    ////////////////////////////////////////////////////////\n"
         << "    //\n"
         << "    // Folding main twist loops into destination\n"
         << "    //\n"
         << aTwistDestinationSquash
         << "    //\n"
         << "    ////////////////////////////////////////////////////////\n"
         << "\n"
         << MainArxStateWriteOutText("    ")
         << "\n"
         << "    ////////////////////////////////////////////////////////\n"
         << "    //\n"
         << "    // Key box management\n"
         << "    //\n"
         << "    if (pStifleKey == true) {\n"
         << "        TwistShiftBox::ShiftKeyBoxA(pWorkSpace);\n"
         << "        TwistShiftBox::ShiftKeyBoxB(pWorkSpace);\n"
         << "    } else {\n"
         << "        TwistForkKeyHalfA(pWorkSpace);\n"
         << "        TwistForkKeyHalfB(pWorkSpace);\n"
         << "        \n"
         << "        GrowKeyA(pWorkSpace, pCrossLaneA, pCrossLaneC, ARX_STATE_VARS);\n"
         << "        \n"
         << MainArxStateRestoreText("        ")
         << "        \n"
         << "        GrowKeyB(pWorkSpace, pCrossLaneB, pCrossLaneD, ARX_STATE_VARS);\n"
         << "        \n"
         << "    }\n"
         << "    //\n"
         << "    ////////////////////////////////////////////////////////\n";
    aCpp << "}\n"
    << "\n"
    << aGrowKeyAMethod
    << "\n"
    << aGrowKeyBMethod
    << "\n"
    << aTwistForkKeyHalfAMethod
    << "\n"
    << aTwistForkKeyHalfBMethod
    << "\n"
    << aKeyDiffuseMethods.str()
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
}
