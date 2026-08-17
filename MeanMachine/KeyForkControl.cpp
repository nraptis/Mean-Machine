#include "KeyForkControl.hpp"

#include "ControlValueFile.hpp"
#include "FileIO.hpp"
#include "Random.hpp"
#include "TwistWorkSpace.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Candidate = KeyForkControl::Candidate;
using BlockPick = KeyForkControl::BlockPick;

constexpr std::uint64_t kMuDistanceWeight = 4ULL;
constexpr std::uint64_t kLelDistanceWeight = 8ULL;
constexpr std::uint64_t kGozDistanceWeight = 12ULL;
constexpr std::size_t kValuesPerPick = 2U;
constexpr std::size_t kMuValueCount =
    KeyForkControl::kForkCount * KeyForkControl::kOutputLaneCount *
    KeyForkControl::kStageLaneCount * KeyForkControl::kMuBlockCount *
    KeyForkControl::kInputCount * kValuesPerPick;
constexpr std::size_t kLelValueCount =
    KeyForkControl::kForkCount * KeyForkControl::kOutputLaneCount *
    KeyForkControl::kStageLaneCount * KeyForkControl::kLelBlockCount *
    KeyForkControl::kInputCount * kValuesPerPick;
constexpr std::size_t kGozValueCount =
    KeyForkControl::kForkCount * KeyForkControl::kOutputLaneCount *
    KeyForkControl::kStageLaneCount * KeyForkControl::kGozBlockCount *
    KeyForkControl::kInputCount * kValuesPerPick;
constexpr std::size_t kCandidateValueCount =
    kMuValueCount + kLelValueCount + kGozValueCount;
constexpr std::size_t kSourceQuarterBlockCount =
    KeyForkControl::kSourceBlockCount / 4U;
static_assert(kSourceQuarterBlockCount == 8U,
              "Key-fork logical source quarter changed.");
constexpr BlockPick kFinalPairs[4U][2U] = {
    {{0U, 0U}, {1U, 0U}},
    {{2U, 0U}, {3U, 0U}},
    {{0U, 1U}, {2U, 1U}},
    {{1U, 1U}, {3U, 1U}},
};

struct Score {
    std::uint64_t mMinimum = 0ULL;
    std::uint64_t mTotal = 0ULL;
};

template <std::size_t LaneCount, std::size_t BlockCount>
struct BlockState {
    std::array<std::array<bool, BlockCount>, LaneCount> mUsed{};
    std::array<std::vector<std::uint8_t>, LaneCount> mChosen{};
};

template <std::size_t LaneCount>
using TierUsage =
    std::array<std::array<std::size_t, LaneCount>,
               KeyForkControl::kStageLaneCount>;

std::vector<Candidate> sCandidates;
bool sDidReset = false;

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

bool HasMinimumDistance(
    const std::uint8_t pCandidate,
    const std::vector<std::uint8_t> &pExisting,
    const std::size_t pMinimumDistance) {
    for (const std::uint8_t aExisting : pExisting) {
        const std::size_t aDistance = pCandidate > aExisting
            ? static_cast<std::size_t>(pCandidate - aExisting)
            : static_cast<std::size_t>(aExisting - pCandidate);
        if (aDistance < pMinimumDistance) {
            return false;
        }
    }
    return true;
}

template <typename T, std::size_t Count>
void ShuffleArray(std::array<T, Count> *pItems) {
    for (std::size_t aIndex = 1U; aIndex < Count; ++aIndex) {
        const std::size_t aSwapIndex = static_cast<std::size_t>(
            Random::Get(static_cast<int>(aIndex + 1U)));
        std::swap((*pItems)[aIndex], (*pItems)[aSwapIndex]);
    }
}

template <std::size_t LaneCount, std::size_t BlockCount>
std::uint8_t ChooseUnusedBlock(
    const std::size_t pLane,
    BlockState<LaneCount, BlockCount> *pState) {
    for (std::size_t aMinimumDistance = 6U;
         aMinimumDistance > 0U;
         --aMinimumDistance) {
        std::vector<std::uint8_t> aChoices;
        for (std::size_t aBlock = 0U; aBlock < BlockCount; ++aBlock) {
            if (!pState->mUsed[pLane][aBlock] &&
                HasMinimumDistance(
                    static_cast<std::uint8_t>(aBlock),
                    pState->mChosen[pLane],
                    aMinimumDistance)) {
                aChoices.push_back(static_cast<std::uint8_t>(aBlock));
            }
        }
        if (!aChoices.empty()) {
            const std::uint8_t aBlock =
                aChoices[static_cast<std::size_t>(
                    Random::Get(static_cast<int>(aChoices.size())))];
            pState->mUsed[pLane][aBlock] = true;
            pState->mChosen[pLane].push_back(aBlock);
            return aBlock;
        }
    }

    std::vector<std::uint8_t> aChoices;
    for (std::size_t aBlock = 0U; aBlock < BlockCount; ++aBlock) {
        if (!pState->mUsed[pLane][aBlock]) {
            aChoices.push_back(static_cast<std::uint8_t>(aBlock));
        }
    }
    if (aChoices.empty()) {
        return static_cast<std::uint8_t>(BlockCount);
    }
    const std::uint8_t aBlock =
        aChoices[static_cast<std::size_t>(
            Random::Get(static_cast<int>(aChoices.size())))];
    pState->mUsed[pLane][aBlock] = true;
    pState->mChosen[pLane].push_back(aBlock);
    return aBlock;
}

constexpr std::size_t kMuNodeCount =
    KeyForkControl::kStageLaneCount * KeyForkControl::kMuBlockCount;
constexpr std::size_t kLelNodeCount =
    KeyForkControl::kStageLaneCount * KeyForkControl::kLelBlockCount;
constexpr std::size_t kGozNodeCount =
    KeyForkControl::kStageLaneCount * KeyForkControl::kGozBlockCount;
constexpr std::uint8_t kUnassignedBlock = 0xFFU;

using SourcePair = std::array<std::uint8_t, 2U>;
using MembershipSchedule =
    std::array<std::array<SourcePair,
                          KeyForkControl::kStageLaneCount>,
               KeyForkControl::kStageLaneCount>;

struct MuNode {
    SourcePair mSources{};
    SourcePair mSourceBlocks = {{kUnassignedBlock, kUnassignedBlock}};
    std::uint8_t mLane = 0U;
    std::uint8_t mBlock = kUnassignedBlock;
};

struct LelNode {
    std::array<std::uint8_t, 2U> mMuNodes{};
    std::uint8_t mLane = 0U;
    std::uint8_t mBlock = kUnassignedBlock;
};

struct GozNode {
    std::array<std::uint8_t, 2U> mLelNodes{};
    std::uint8_t mLane = 0U;
    std::uint8_t mBlock = 0U;
};

struct OutputTopology {
    std::array<MuNode, kMuNodeCount> mMu{};
    std::array<LelNode, kLelNodeCount> mLel{};
    std::array<GozNode, kGozNodeCount> mGoz{};
};

const std::vector<std::array<std::uint8_t, 4U>> &PermutationsFour() {
    static const std::vector<std::array<std::uint8_t, 4U>> kValues = [] {
        std::vector<std::array<std::uint8_t, 4U>> aValues;
        std::array<std::uint8_t, 4U> aValue = {{0U, 1U, 2U, 3U}};
        do {
            aValues.push_back(aValue);
        } while (std::next_permutation(aValue.begin(), aValue.end()));
        return aValues;
    }();
    return kValues;
}

std::uint32_t MatchingKey(
    const std::array<SourcePair, 4U> &pPairs) {
    std::array<std::uint8_t, 4U> aEdges{};
    for (std::size_t aIndex = 0U; aIndex < 4U; ++aIndex) {
        const std::uint8_t aLow =
            std::min(pPairs[aIndex][0U], pPairs[aIndex][1U]);
        const std::uint8_t aHigh =
            std::max(pPairs[aIndex][0U], pPairs[aIndex][1U]);
        aEdges[aIndex] = static_cast<std::uint8_t>((aLow << 3U) | aHigh);
    }
    std::sort(aEdges.begin(), aEdges.end());
    std::uint32_t aKey = 0U;
    for (const std::uint8_t aEdge : aEdges) {
        aKey = (aKey << 6U) | aEdge;
    }
    return aKey;
}

bool AssignMembershipSchedule(
    const std::size_t pSource,
    std::array<std::array<std::size_t, 4U>, 4U> *pCounts,
    std::array<std::array<std::uint8_t, 4U>, 8U> *pColors,
    const std::vector<std::uint32_t> &pUsedMatchingKeys,
    MembershipSchedule *pSchedule,
    std::array<std::uint32_t, 4U> *pMatchingKeys) {
    if (pSource == KeyForkControl::kSourceLaneCount) {
        for (std::size_t aRow = 0U; aRow < 4U; ++aRow) {
            std::array<SourcePair, 4U> aPairs{};
            std::array<std::size_t, 4U> aPairCounts{};
            for (std::size_t aSource = 0U; aSource < 8U; ++aSource) {
                const std::size_t aLane = (*pColors)[aSource][aRow];
                aPairs[aLane][aPairCounts[aLane]++] =
                    static_cast<std::uint8_t>(aSource);
            }
            for (const std::size_t aCount : aPairCounts) {
                if (aCount != 2U) {
                    return false;
                }
            }
            const std::uint32_t aKey = MatchingKey(aPairs);
            if ((std::find(pUsedMatchingKeys.begin(),
                           pUsedMatchingKeys.end(),
                           aKey) != pUsedMatchingKeys.end()) ||
                (std::find(pMatchingKeys->begin(),
                           pMatchingKeys->begin() + aRow,
                           aKey) != pMatchingKeys->begin() + aRow)) {
                return false;
            }
            (*pSchedule)[aRow] = aPairs;
            (*pMatchingKeys)[aRow] = aKey;
        }
        return true;
    }

    std::vector<std::array<std::uint8_t, 4U>> aPermutations =
        PermutationsFour();
    Random::Shuffle(&aPermutations);
    for (const auto &aPermutation : aPermutations) {
        bool aFits = true;
        for (std::size_t aRow = 0U; aRow < 4U; ++aRow) {
            if ((*pCounts)[aRow][aPermutation[aRow]] >= 2U) {
                aFits = false;
                break;
            }
        }
        if (!aFits) {
            continue;
        }
        for (std::size_t aRow = 0U; aRow < 4U; ++aRow) {
            (*pColors)[pSource][aRow] = aPermutation[aRow];
            ++(*pCounts)[aRow][aPermutation[aRow]];
        }
        if (AssignMembershipSchedule(
                pSource + 1U,
                pCounts,
                pColors,
                pUsedMatchingKeys,
                pSchedule,
                pMatchingKeys)) {
            return true;
        }
        for (std::size_t aRow = 0U; aRow < 4U; ++aRow) {
            --(*pCounts)[aRow][aPermutation[aRow]];
        }
    }
    return false;
}

bool BuildMuTopology(OutputTopology *pTopology) {
    std::vector<std::uint32_t> aUsedMatchingKeys;
    for (std::size_t aGroup = 0U;
         aGroup < KeyForkControl::kGozBlockCount;
         ++aGroup) {
        std::array<std::array<std::size_t, 4U>, 4U> aCounts{};
        std::array<std::array<std::uint8_t, 4U>, 8U> aColors{};
        MembershipSchedule aSchedule{};
        std::array<std::uint32_t, 4U> aMatchingKeys{};
        if (!AssignMembershipSchedule(
                0U,
                &aCounts,
                &aColors,
                aUsedMatchingKeys,
                &aSchedule,
                &aMatchingKeys)) {
            return false;
        }
        aUsedMatchingKeys.insert(aUsedMatchingKeys.end(),
                                 aMatchingKeys.begin(),
                                 aMatchingKeys.end());
        for (std::size_t aRow = 0U; aRow < 4U; ++aRow) {
            const std::size_t aGoz = (aGroup * 4U) + aRow;
            for (std::size_t aMuLane = 0U; aMuLane < 4U; ++aMuLane) {
                MuNode &aNode = pTopology->mMu[(aGoz * 4U) + aMuLane];
                aNode.mLane = static_cast<std::uint8_t>(aMuLane);
                aNode.mSources = aSchedule[aRow][aMuLane];
                if (Random::Bool()) {
                    std::swap(aNode.mSources[0U], aNode.mSources[1U]);
                }
            }
            GozNode &aGozNode = pTopology->mGoz[aGoz];
            aGozNode.mLane = static_cast<std::uint8_t>(
                aGoz / KeyForkControl::kGozBlockCount);
            aGozNode.mBlock = static_cast<std::uint8_t>(
                aGoz % KeyForkControl::kGozBlockCount);
            aGozNode.mLelNodes = {{
                static_cast<std::uint8_t>(aGoz * 2U),
                static_cast<std::uint8_t>((aGoz * 2U) + 1U),
            }};
        }
    }
    return true;
}

struct LelAssignmentOption {
    std::uint8_t mPartition = 0U;
    std::uint8_t mLaneA = 0U;
    std::uint8_t mLaneB = 1U;
};

constexpr std::uint8_t kMuPartitions[3U][2U][2U] = {
    {{0U, 1U}, {2U, 3U}},
    {{0U, 2U}, {1U, 3U}},
    {{0U, 3U}, {1U, 2U}},
};

bool AssignLelTopology(
    const std::size_t pGoz,
    OutputTopology *pTopology,
    std::array<std::array<std::size_t, 4U>, 4U> *pLelMuUsage,
    std::array<std::size_t, 4U> *pLelBlockUsage,
    std::array<std::array<std::size_t, 4U>, 4U> *pGozLelUsage) {
    if (pGoz == kGozNodeCount) {
        return true;
    }

    std::vector<LelAssignmentOption> aOptions;
    for (std::size_t aPartition = 0U; aPartition < 3U; ++aPartition) {
        for (std::size_t aLaneA = 0U; aLaneA < 4U; ++aLaneA) {
            for (std::size_t aLaneB = 0U; aLaneB < 4U; ++aLaneB) {
                if (aLaneA != aLaneB) {
                    aOptions.push_back({
                        static_cast<std::uint8_t>(aPartition),
                        static_cast<std::uint8_t>(aLaneA),
                        static_cast<std::uint8_t>(aLaneB),
                    });
                }
            }
        }
    }
    Random::Shuffle(&aOptions);

    const std::size_t aGozLane =
        pGoz / KeyForkControl::kGozBlockCount;
    constexpr std::size_t kMuUsesPerLelLane =
        (KeyForkControl::kLelBlockCount * KeyForkControl::kInputCount) /
        KeyForkControl::kStageLaneCount;
    constexpr std::size_t kLelUsesPerGozLane =
        (KeyForkControl::kGozBlockCount * KeyForkControl::kInputCount) /
        KeyForkControl::kStageLaneCount;
    for (const LelAssignmentOption &aOption : aOptions) {
        const std::size_t aLaneA = aOption.mLaneA;
        const std::size_t aLaneB = aOption.mLaneB;
        if (((*pLelBlockUsage)[aLaneA] >=
             KeyForkControl::kLelBlockCount) ||
            ((*pLelBlockUsage)[aLaneB] >=
             KeyForkControl::kLelBlockCount) ||
            ((*pGozLelUsage)[aGozLane][aLaneA] >=
             kLelUsesPerGozLane) ||
            ((*pGozLelUsage)[aGozLane][aLaneB] >=
             kLelUsesPerGozLane)) {
            continue;
        }

        const auto &aHalfA = kMuPartitions[aOption.mPartition][0U];
        const auto &aHalfB = kMuPartitions[aOption.mPartition][1U];
        if (((*pLelMuUsage)[aLaneA][aHalfA[0U]] >=
             kMuUsesPerLelLane) ||
            ((*pLelMuUsage)[aLaneA][aHalfA[1U]] >=
             kMuUsesPerLelLane) ||
            ((*pLelMuUsage)[aLaneB][aHalfB[0U]] >=
             kMuUsesPerLelLane) ||
            ((*pLelMuUsage)[aLaneB][aHalfB[1U]] >=
             kMuUsesPerLelLane)) {
            continue;
        }

        LelNode &aNodeA = pTopology->mLel[pGoz * 2U];
        LelNode &aNodeB = pTopology->mLel[(pGoz * 2U) + 1U];
        aNodeA.mLane = static_cast<std::uint8_t>(aLaneA);
        aNodeB.mLane = static_cast<std::uint8_t>(aLaneB);
        aNodeA.mMuNodes = {{
            static_cast<std::uint8_t>((pGoz * 4U) + aHalfA[0U]),
            static_cast<std::uint8_t>((pGoz * 4U) + aHalfA[1U]),
        }};
        aNodeB.mMuNodes = {{
            static_cast<std::uint8_t>((pGoz * 4U) + aHalfB[0U]),
            static_cast<std::uint8_t>((pGoz * 4U) + aHalfB[1U]),
        }};
        if (Random::Bool()) {
            std::swap(aNodeA.mMuNodes[0U], aNodeA.mMuNodes[1U]);
        }
        if (Random::Bool()) {
            std::swap(aNodeB.mMuNodes[0U], aNodeB.mMuNodes[1U]);
        }

        ++(*pLelBlockUsage)[aLaneA];
        ++(*pLelBlockUsage)[aLaneB];
        ++(*pGozLelUsage)[aGozLane][aLaneA];
        ++(*pGozLelUsage)[aGozLane][aLaneB];
        ++(*pLelMuUsage)[aLaneA][aHalfA[0U]];
        ++(*pLelMuUsage)[aLaneA][aHalfA[1U]];
        ++(*pLelMuUsage)[aLaneB][aHalfB[0U]];
        ++(*pLelMuUsage)[aLaneB][aHalfB[1U]];

        if (AssignLelTopology(
                pGoz + 1U,
                pTopology,
                pLelMuUsage,
                pLelBlockUsage,
                pGozLelUsage)) {
            if (Random::Bool()) {
                std::swap(pTopology->mGoz[pGoz].mLelNodes[0U],
                          pTopology->mGoz[pGoz].mLelNodes[1U]);
            }
            return true;
        }

        --(*pLelBlockUsage)[aLaneA];
        --(*pLelBlockUsage)[aLaneB];
        --(*pGozLelUsage)[aGozLane][aLaneA];
        --(*pGozLelUsage)[aGozLane][aLaneB];
        --(*pLelMuUsage)[aLaneA][aHalfA[0U]];
        --(*pLelMuUsage)[aLaneA][aHalfA[1U]];
        --(*pLelMuUsage)[aLaneB][aHalfB[0U]];
        --(*pLelMuUsage)[aLaneB][aHalfB[1U]];
    }
    return false;
}

bool BuildOutputTopology(OutputTopology *pTopology) {
    if (!BuildMuTopology(pTopology)) {
        return false;
    }
    std::array<std::array<std::size_t, 4U>, 4U> aLelMuUsage{};
    std::array<std::size_t, 4U> aLelBlockUsage{};
    std::array<std::array<std::size_t, 4U>, 4U> aGozLelUsage{};
    return AssignLelTopology(
        0U,
        pTopology,
        &aLelMuUsage,
        &aLelBlockUsage,
        &aGozLelUsage);
}

void AssignIntermediateBlocks(OutputTopology *pTopology) {
    BlockState<KeyForkControl::kStageLaneCount,
               KeyForkControl::kLelBlockCount> aLelState;
    for (const GozNode &aGoz : pTopology->mGoz) {
        for (const std::uint8_t aLelIndex : aGoz.mLelNodes) {
            LelNode &aLel = pTopology->mLel[aLelIndex];
            aLel.mBlock = ChooseUnusedBlock(aLel.mLane, &aLelState);
        }
    }

    BlockState<KeyForkControl::kStageLaneCount,
               KeyForkControl::kMuBlockCount> aMuState;
    std::vector<std::size_t> aLelOrder(kLelNodeCount);
    for (std::size_t aIndex = 0U; aIndex < kLelNodeCount; ++aIndex) {
        aLelOrder[aIndex] = aIndex;
    }
    std::sort(aLelOrder.begin(), aLelOrder.end(),
              [pTopology](const std::size_t pLeft,
                          const std::size_t pRight) {
        const LelNode &aLeft = pTopology->mLel[pLeft];
        const LelNode &aRight = pTopology->mLel[pRight];
        return std::pair(aLeft.mLane, aLeft.mBlock) <
            std::pair(aRight.mLane, aRight.mBlock);
    });
    for (const std::size_t aLelIndex : aLelOrder) {
        for (const std::uint8_t aMuIndex :
             pTopology->mLel[aLelIndex].mMuNodes) {
            MuNode &aMu = pTopology->mMu[aMuIndex];
            aMu.mBlock = ChooseUnusedBlock(aMu.mLane, &aMuState);
        }
    }
}

struct SourceLeaf {
    std::uint8_t mOutput = 0U;
    std::uint8_t mMuNode = 0U;
    std::uint8_t mInput = 0U;
};

using OutputTopologies =
    std::array<OutputTopology, KeyForkControl::kOutputLaneCount>;
using FinalSourceLeaves =
    std::array<std::array<SourceLeaf, 2U>,
               KeyForkControl::kSourceLaneCount>;

bool CollectFinalSourceLeaves(
    OutputTopologies *pTopologies,
    const std::size_t pOutput,
    const std::size_t pKeyBlock,
    FinalSourceLeaves *pLeaves) {
    std::array<std::size_t, KeyForkControl::kSourceLaneCount> aCounts{};
    OutputTopology &aTopology = (*pTopologies)[pOutput];

    for (const BlockPick &aGozPick : kFinalPairs[pKeyBlock]) {
        const std::size_t aGozIndex =
            (static_cast<std::size_t>(aGozPick.mLane) *
             KeyForkControl::kGozBlockCount) +
            static_cast<std::size_t>(aGozPick.mBlock);
        if (aGozIndex >= aTopology.mGoz.size()) {
            return false;
        }
        const GozNode &aGoz = aTopology.mGoz[aGozIndex];
        for (const std::uint8_t aLelIndex : aGoz.mLelNodes) {
            if (aLelIndex >= aTopology.mLel.size()) {
                return false;
            }
            const LelNode &aLel = aTopology.mLel[aLelIndex];
            for (const std::uint8_t aMuIndex : aLel.mMuNodes) {
                if (aMuIndex >= aTopology.mMu.size()) {
                    return false;
                }
                const MuNode &aMu = aTopology.mMu[aMuIndex];
                for (std::size_t aInput = 0U; aInput < 2U; ++aInput) {
                    const std::size_t aSource = aMu.mSources[aInput];
                    if ((aSource >= KeyForkControl::kSourceLaneCount) ||
                        (aCounts[aSource] >= 2U)) {
                        return false;
                    }
                    (*pLeaves)[aSource][aCounts[aSource]++] = {
                        static_cast<std::uint8_t>(pOutput),
                        aMuIndex,
                        static_cast<std::uint8_t>(aInput),
                    };
                }
            }
        }
    }

    for (const std::size_t aCount : aCounts) {
        if (aCount != 2U) {
            return false;
        }
    }
    return true;
}

bool AssignSourceBlocksForFork(OutputTopologies *pTopologies) {
    static constexpr std::size_t kFinalBlockCount =
        KeyForkControl::kOutputLaneCount * 4U;
    std::array<FinalSourceLeaves, kFinalBlockCount> aLeaves{};
    for (std::size_t aOutput = 0U;
         aOutput < KeyForkControl::kOutputLaneCount;
         ++aOutput) {
        for (std::size_t aKeyBlock = 0U; aKeyBlock < 4U; ++aKeyBlock) {
            const std::size_t aFinalBlock = (aOutput * 4U) + aKeyBlock;
            if (!CollectFinalSourceLeaves(
                    pTopologies,
                    aOutput,
                    aKeyBlock,
                    &aLeaves[aFinalBlock])) {
                return false;
            }
        }
    }

    for (std::size_t aSource = 0U;
         aSource < KeyForkControl::kSourceLaneCount;
         ++aSource) {
        std::array<std::uint8_t, kFinalBlockCount> aFinalOrder{};
        for (std::size_t aIndex = 0U; aIndex < kFinalBlockCount; ++aIndex) {
            aFinalOrder[aIndex] = static_cast<std::uint8_t>(aIndex);
        }
        ShuffleArray(&aFinalOrder);

        std::array<std::array<std::uint8_t,
                              kSourceQuarterBlockCount>, 4U>
            aQuarterBlocks{};
        for (std::size_t aQuarter = 0U; aQuarter < 4U; ++aQuarter) {
            for (std::size_t aIndex = 0U;
                 aIndex < kSourceQuarterBlockCount;
                 ++aIndex) {
                aQuarterBlocks[aQuarter][aIndex] =
                    static_cast<std::uint8_t>(
                        (aQuarter * kSourceQuarterBlockCount) + aIndex);
            }
            ShuffleArray(&aQuarterBlocks[aQuarter]);
        }

        std::array<std::size_t, 4U> aQuarterOffsets{};
        for (std::size_t aPosition = 0U;
             aPosition < kFinalBlockCount;
             ++aPosition) {
            const std::size_t aFinalBlock = aFinalOrder[aPosition];
            const std::size_t aQuarterA =
                aPosition < kSourceQuarterBlockCount ? 0U : 1U;
            const std::size_t aQuarterB = aQuarterA + 2U;
            std::uint8_t aBlockA =
                aQuarterBlocks[aQuarterA][aQuarterOffsets[aQuarterA]++];
            std::uint8_t aBlockB =
                aQuarterBlocks[aQuarterB][aQuarterOffsets[aQuarterB]++];
            if (Random::Bool()) {
                std::swap(aBlockA, aBlockB);
            }

            const SourceLeaf &aLeafA = aLeaves[aFinalBlock][aSource][0U];
            const SourceLeaf &aLeafB = aLeaves[aFinalBlock][aSource][1U];
            (*pTopologies)[aLeafA.mOutput]
                .mMu[aLeafA.mMuNode]
                .mSourceBlocks[aLeafA.mInput] = aBlockA;
            (*pTopologies)[aLeafB.mOutput]
                .mMu[aLeafB.mMuNode]
                .mSourceBlocks[aLeafB.mInput] = aBlockB;
        }
    }
    return true;
}

void PopulateOutputCandidate(
    Candidate *pCandidate,
    const std::size_t pFork,
    const std::size_t pOutput,
    const OutputTopology &pTopology) {
    std::vector<std::size_t> aMuOrder(kMuNodeCount);
    for (std::size_t aIndex = 0U; aIndex < kMuNodeCount; ++aIndex) {
        aMuOrder[aIndex] = aIndex;
    }
    std::sort(aMuOrder.begin(), aMuOrder.end(),
              [&pTopology](const std::size_t pLeft,
                           const std::size_t pRight) {
        const MuNode &aLeft = pTopology.mMu[pLeft];
        const MuNode &aRight = pTopology.mMu[pRight];
        return std::pair(aLeft.mLane, aLeft.mBlock) <
            std::pair(aRight.mLane, aRight.mBlock);
    });
    for (const std::size_t aMuIndex : aMuOrder) {
        const MuNode &aMu = pTopology.mMu[aMuIndex];
        auto &aPair =
            pCandidate->mMu[pFork][pOutput][aMu.mLane][aMu.mBlock];
        for (std::size_t aInput = 0U; aInput < 2U; ++aInput) {
            aPair[aInput].mLane = aMu.mSources[aInput];
            aPair[aInput].mBlock = aMu.mSourceBlocks[aInput];
        }
    }

    for (const LelNode &aLel : pTopology.mLel) {
        auto &aPair =
            pCandidate->mLel[pFork][pOutput][aLel.mLane][aLel.mBlock];
        for (std::size_t aInput = 0U; aInput < 2U; ++aInput) {
            const MuNode &aMu = pTopology.mMu[aLel.mMuNodes[aInput]];
            aPair[aInput] = {aMu.mLane, aMu.mBlock};
        }
    }

    for (const GozNode &aGoz : pTopology.mGoz) {
        auto &aPair =
            pCandidate->mGoz[pFork][pOutput][aGoz.mLane][aGoz.mBlock];
        for (std::size_t aInput = 0U; aInput < 2U; ++aInput) {
            const LelNode &aLel = pTopology.mLel[aGoz.mLelNodes[aInput]];
            aPair[aInput] = {aLel.mLane, aLel.mBlock};
        }
    }
}

bool GenerateCandidate(Candidate *pCandidate) {
    for (std::size_t aFork = 0U;
         aFork < KeyForkControl::kForkCount;
         ++aFork) {
        OutputTopologies aTopologies{};
        for (std::size_t aOutput = 0U;
             aOutput < KeyForkControl::kOutputLaneCount;
             ++aOutput) {
            bool aBuilt = false;
            for (std::size_t aAttempt = 0U;
                 (aAttempt < 64U) && !aBuilt;
                 ++aAttempt) {
                aTopologies[aOutput] = {};
                aBuilt = BuildOutputTopology(&aTopologies[aOutput]);
            }
            if (!aBuilt) {
                return false;
            }
            AssignIntermediateBlocks(&aTopologies[aOutput]);
        }
        if (!AssignSourceBlocksForFork(&aTopologies)) {
            return false;
        }
        for (std::size_t aOutput = 0U;
             aOutput < KeyForkControl::kOutputLaneCount;
             ++aOutput) {
            PopulateOutputCandidate(
                pCandidate,
                aFork,
                aOutput,
                aTopologies[aOutput]);
        }
    }
    return true;
}

Candidate RandomCandidate() {
    Candidate aCandidate;
    while (!GenerateCandidate(&aCandidate)) {
        aCandidate = {};
    }
    return aCandidate;
}

template <typename Plans>
std::uint64_t StageDistance(
    const Plans &pLeft,
    const Plans &pRight,
    const std::uint64_t pWeight) {
    std::uint64_t aDistance = 0ULL;
    for (std::size_t aFork = 0U; aFork < pLeft.size(); ++aFork) {
        for (std::size_t aOutput = 0U;
             aOutput < pLeft[aFork].size();
             ++aOutput) {
            for (std::size_t aLane = 0U;
                 aLane < pLeft[aFork][aOutput].size();
                 ++aLane) {
                for (std::size_t aBlock = 0U;
                     aBlock < pLeft[aFork][aOutput][aLane].size();
                     ++aBlock) {
                    for (std::size_t aInput = 0U;
                         aInput < KeyForkControl::kInputCount;
                         ++aInput) {
                        const BlockPick &aLeft =
                            pLeft[aFork][aOutput][aLane][aBlock][aInput];
                        const BlockPick &aRight =
                            pRight[aFork][aOutput][aLane][aBlock][aInput];
                        if (aLeft.mLane != aRight.mLane) {
                            aDistance += pWeight;
                        }
                        if (aLeft.mBlock != aRight.mBlock) {
                            aDistance += pWeight;
                        }
                    }
                }
            }
        }
    }
    return aDistance;
}

std::uint64_t Distance(
    const Candidate &pLeft,
    const Candidate &pRight) {
    return StageDistance(pLeft.mMu, pRight.mMu, kMuDistanceWeight) +
        StageDistance(pLeft.mLel, pRight.mLel, kLelDistanceWeight) +
        StageDistance(pLeft.mGoz, pRight.mGoz, kGozDistanceWeight);
}

Score CandidateScore(const Candidate &pCandidate) {
    if (sCandidates.empty()) {
        return {std::numeric_limits<std::uint64_t>::max(), 0ULL};
    }
    Score aScore{std::numeric_limits<std::uint64_t>::max(), 0ULL};
    for (const Candidate &aExisting : sCandidates) {
        const std::uint64_t aDistance = Distance(pCandidate, aExisting);
        aScore.mMinimum = std::min(aScore.mMinimum, aDistance);
        aScore.mTotal += aDistance;
    }
    return aScore;
}

bool Better(const Score &pLeft,
            const Score &pRight) {
    if (pLeft.mMinimum != pRight.mMinimum) {
        return pLeft.mMinimum > pRight.mMinimum;
    }
    return pLeft.mTotal > pRight.mTotal;
}

template <std::size_t InputLaneCount,
          std::size_t InputBlockCount,
          typename Plans>
bool ValidateStage(
    const Plans &pPlans,
    const bool pShareBlocksAcrossOutputs,
    const char *pStageName,
    std::string *pErrorMessage) {
    for (std::size_t aFork = 0U;
         aFork < KeyForkControl::kForkCount;
         ++aFork) {
        std::array<std::array<bool, InputBlockCount>, InputLaneCount>
            aSharedUsed{};
        for (std::size_t aOutput = 0U;
             aOutput < KeyForkControl::kOutputLaneCount;
             ++aOutput) {
            std::array<std::array<bool, InputBlockCount>, InputLaneCount>
                aLocalUsed{};
            auto &aUsed = pShareBlocksAcrossOutputs
                ? aSharedUsed
                : aLocalUsed;
            TierUsage<InputLaneCount> aUsage{};
            for (std::size_t aDestinationLane = 0U;
                 aDestinationLane < KeyForkControl::kStageLaneCount;
                 ++aDestinationLane) {
                for (const auto &aPair :
                     pPlans[aFork][aOutput][aDestinationLane]) {
                    if (aPair[0U].mLane == aPair[1U].mLane) {
                        SetError(pErrorMessage,
                                 std::string("KeyForkControl ") +
                                 pStageName +
                                 " pair reused one source lane");
                        return false;
                    }
                    for (const BlockPick &aPick : aPair) {
                        if ((aPick.mLane >= InputLaneCount) ||
                            (aPick.mBlock >= InputBlockCount) ||
                            aUsed[aPick.mLane][aPick.mBlock]) {
                            SetError(pErrorMessage,
                                     std::string("KeyForkControl ") +
                                     pStageName +
                                     " contained an invalid or reused block");
                            return false;
                        }
                        aUsed[aPick.mLane][aPick.mBlock] = true;
                        ++aUsage[aDestinationLane][aPick.mLane];
                    }
                }
            }

            const std::size_t aExpectedUsesPerLane =
                (pPlans[aFork][aOutput][0U].size() *
                 KeyForkControl::kInputCount) /
                InputLaneCount;
            for (std::size_t aDestinationLane = 0U;
                 aDestinationLane < KeyForkControl::kStageLaneCount;
                 ++aDestinationLane) {
                for (std::size_t aSourceLane = 0U;
                     aSourceLane < InputLaneCount;
                     ++aSourceLane) {
                    if (aUsage[aDestinationLane][aSourceLane] !=
                        aExpectedUsesPerLane) {
                        SetError(pErrorMessage,
                                 std::string("KeyForkControl ") +
                                 pStageName +
                                 " lane membership was not balanced");
                        return false;
                    }
                }
            }
        }

        if (pShareBlocksAcrossOutputs) {
            for (const auto &aLane : aSharedUsed) {
                for (const bool aUsed : aLane) {
                    if (!aUsed) {
                        SetError(pErrorMessage,
                                 std::string("KeyForkControl ") +
                                 pStageName +
                                 " did not consume every source block");
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

using SourceMembership =
    std::array<std::uint8_t, KeyForkControl::kSourceLaneCount>;

SourceMembership MergeMemberships(
    const SourceMembership &pLeft,
    const SourceMembership &pRight) {
    SourceMembership aResult{};
    for (std::size_t aSource = 0U;
         aSource < KeyForkControl::kSourceLaneCount;
         ++aSource) {
        aResult[aSource] = static_cast<std::uint8_t>(
            pLeft[aSource] + pRight[aSource]);
    }
    return aResult;
}

using FinalSourceBlocks =
    std::array<std::array<std::uint8_t, 2U>,
               KeyForkControl::kSourceLaneCount>;

bool CollectFinalSourceBlocks(
    const Candidate &pCandidate,
    const std::size_t pFork,
    const std::size_t pOutput,
    const std::size_t pKeyBlock,
    FinalSourceBlocks *pBlocks) {
    std::array<std::size_t, KeyForkControl::kSourceLaneCount> aCounts{};
    for (const BlockPick &aGozPick : kFinalPairs[pKeyBlock]) {
        const auto &aGozPair =
            pCandidate.mGoz[pFork][pOutput]
                           [aGozPick.mLane][aGozPick.mBlock];
        for (const BlockPick &aLelPick : aGozPair) {
            const auto &aLelPair =
                pCandidate.mLel[pFork][pOutput]
                               [aLelPick.mLane][aLelPick.mBlock];
            for (const BlockPick &aMuPick : aLelPair) {
                const auto &aMuPair =
                    pCandidate.mMu[pFork][pOutput]
                                  [aMuPick.mLane][aMuPick.mBlock];
                for (const BlockPick &aSourcePick : aMuPair) {
                    const std::size_t aSource = aSourcePick.mLane;
                    if ((aSource >= KeyForkControl::kSourceLaneCount) ||
                        (aCounts[aSource] >= 2U)) {
                        return false;
                    }
                    (*pBlocks)[aSource][aCounts[aSource]++] =
                        aSourcePick.mBlock;
                }
            }
        }
    }
    for (const std::size_t aCount : aCounts) {
        if (aCount != 2U) {
            return false;
        }
    }
    return true;
}

bool ValidatePerfectAncestry(
    const Candidate &pCandidate,
    std::string *pErrorMessage) {
    for (std::size_t aFork = 0U;
         aFork < KeyForkControl::kForkCount;
         ++aFork) {
        for (std::size_t aOutput = 0U;
             aOutput < KeyForkControl::kOutputLaneCount;
             ++aOutput) {
            std::array<std::array<SourceMembership,
                                  KeyForkControl::kMuBlockCount>,
                       KeyForkControl::kStageLaneCount> aMu{};
            std::array<std::array<SourceMembership,
                                  KeyForkControl::kLelBlockCount>,
                       KeyForkControl::kStageLaneCount> aLel{};
            std::array<std::array<SourceMembership,
                                  KeyForkControl::kGozBlockCount>,
                       KeyForkControl::kStageLaneCount> aGoz{};

            for (std::size_t aLane = 0U; aLane < 4U; ++aLane) {
                for (std::size_t aBlock = 0U;
                     aBlock < KeyForkControl::kMuBlockCount;
                     ++aBlock) {
                    const auto &aPair =
                        pCandidate.mMu[aFork][aOutput][aLane][aBlock];
                    ++aMu[aLane][aBlock][aPair[0U].mLane];
                    ++aMu[aLane][aBlock][aPair[1U].mLane];
                    for (const std::uint8_t aCount : aMu[aLane][aBlock]) {
                        if (aCount > 1U) {
                            SetError(pErrorMessage,
                                     "KeyForkControl Mu ancestry repeated "
                                     "an original source lane");
                            return false;
                        }
                    }
                }
            }

            for (std::size_t aLane = 0U; aLane < 4U; ++aLane) {
                for (std::size_t aBlock = 0U;
                     aBlock < KeyForkControl::kLelBlockCount;
                     ++aBlock) {
                    const auto &aPair =
                        pCandidate.mLel[aFork][aOutput][aLane][aBlock];
                    aLel[aLane][aBlock] = MergeMemberships(
                        aMu[aPair[0U].mLane][aPair[0U].mBlock],
                        aMu[aPair[1U].mLane][aPair[1U].mBlock]);
                    for (const std::uint8_t aCount : aLel[aLane][aBlock]) {
                        if (aCount > 1U) {
                            SetError(pErrorMessage,
                                     "KeyForkControl Lel ancestry did not "
                                     "contain four distinct source lanes");
                            return false;
                        }
                    }
                }
            }

            for (std::size_t aLane = 0U; aLane < 4U; ++aLane) {
                for (std::size_t aBlock = 0U;
                     aBlock < KeyForkControl::kGozBlockCount;
                     ++aBlock) {
                    const auto &aPair =
                        pCandidate.mGoz[aFork][aOutput][aLane][aBlock];
                    aGoz[aLane][aBlock] = MergeMemberships(
                        aLel[aPair[0U].mLane][aPair[0U].mBlock],
                        aLel[aPair[1U].mLane][aPair[1U].mBlock]);
                    for (const std::uint8_t aCount : aGoz[aLane][aBlock]) {
                        if (aCount != 1U) {
                            SetError(pErrorMessage,
                                     "KeyForkControl Goz ancestry did not "
                                     "contain all eight source lanes once");
                            return false;
                        }
                    }
                }
            }

            for (std::size_t aKeyBlock = 0U;
                 aKeyBlock < 4U;
                 ++aKeyBlock) {
                const BlockPick &aLeft = kFinalPairs[aKeyBlock][0U];
                const BlockPick &aRight = kFinalPairs[aKeyBlock][1U];
                const SourceMembership aKey = MergeMemberships(
                    aGoz[aLeft.mLane][aLeft.mBlock],
                    aGoz[aRight.mLane][aRight.mBlock]);
                for (const std::uint8_t aCount : aKey) {
                    if (aCount != 2U) {
                        SetError(pErrorMessage,
                                 "KeyForkControl final key ancestry was not "
                                 "perfectly balanced");
                        return false;
                    }
                }

                FinalSourceBlocks aSourceBlocks{};
                if (!CollectFinalSourceBlocks(
                        pCandidate,
                        aFork,
                        aOutput,
                        aKeyBlock,
                        &aSourceBlocks)) {
                    SetError(pErrorMessage,
                             "KeyForkControl could not trace final source "
                             "blocks");
                    return false;
                }
                for (const auto &aBlocks : aSourceBlocks) {
                    const std::size_t aQuarterA =
                        aBlocks[0U] / kSourceQuarterBlockCount;
                    const std::size_t aQuarterB =
                        aBlocks[1U] / kSourceQuarterBlockCount;
                    if ((aQuarterA ^ aQuarterB) != 2U) {
                        SetError(pErrorMessage,
                                 "KeyForkControl final source blocks were "
                                 "not separated by two quarters");
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Validate(const Candidate &pCandidate,
              std::string *pErrorMessage) {
    if (!ValidateStage<KeyForkControl::kSourceLaneCount,
                       KeyForkControl::kSourceBlockCount>(
            pCandidate.mMu, true, "Mu-stage", pErrorMessage) ||
        !ValidateStage<KeyForkControl::kStageLaneCount,
                       KeyForkControl::kMuBlockCount>(
            pCandidate.mLel, false, "Lel-stage", pErrorMessage) ||
        !ValidateStage<KeyForkControl::kStageLaneCount,
                       KeyForkControl::kLelBlockCount>(
            pCandidate.mGoz, false, "Goz-stage", pErrorMessage) ||
        !ValidatePerfectAncestry(pCandidate, pErrorMessage)) {
        return false;
    }
    SetError(pErrorMessage, "");
    return true;
}

template <typename Plans>
void AppendStageValues(
    const Plans &pPlans,
    std::vector<std::uint64_t> *pValues) {
    for (const auto &aFork : pPlans) {
        for (const auto &aOutput : aFork) {
            for (const auto &aLane : aOutput) {
                for (const auto &aPair : aLane) {
                    for (const BlockPick &aPick : aPair) {
                        pValues->push_back(aPick.mLane);
                        pValues->push_back(aPick.mBlock);
                    }
                }
            }
        }
    }
}

std::vector<std::uint64_t> CandidateValues(
    const Candidate &pCandidate) {
    std::vector<std::uint64_t> aValues;
    aValues.reserve(kCandidateValueCount);
    AppendStageValues(pCandidate.mMu, &aValues);
    AppendStageValues(pCandidate.mLel, &aValues);
    AppendStageValues(pCandidate.mGoz, &aValues);
    return aValues;
}

template <typename Plans, typename Next>
void LoadStageValues(
    Plans *pPlans,
    const std::uint64_t pLaneLimit,
    const std::uint64_t pBlockLimit,
    Next &&pNext) {
    for (auto &aFork : *pPlans) {
        for (auto &aOutput : aFork) {
            for (auto &aLane : aOutput) {
                for (auto &aPair : aLane) {
                    for (BlockPick &aPick : aPair) {
                        aPick.mLane = static_cast<std::uint8_t>(
                            pNext(pLaneLimit));
                        aPick.mBlock = static_cast<std::uint8_t>(
                            pNext(pBlockLimit));
                    }
                }
            }
        }
    }
}

Candidate CandidateFromValues(
    const std::vector<std::uint64_t> &pValues,
    std::string *pErrorMessage) {
    Candidate aCandidate;
    std::size_t aIndex = 0U;
    std::size_t aInvalidCount = 0U;
    auto Next = [&](const std::uint64_t pLimit) {
        const std::uint64_t aValue =
            aIndex < pValues.size() ? pValues[aIndex] : pLimit;
        ++aIndex;
        if (aValue >= pLimit) {
            ++aInvalidCount;
            return 0ULL;
        }
        return aValue;
    };
    LoadStageValues(&aCandidate.mMu,
                    KeyForkControl::kSourceLaneCount,
                    KeyForkControl::kSourceBlockCount,
                    Next);
    LoadStageValues(&aCandidate.mLel,
                    KeyForkControl::kStageLaneCount,
                    KeyForkControl::kMuBlockCount,
                    Next);
    LoadStageValues(&aCandidate.mGoz,
                    KeyForkControl::kStageLaneCount,
                    KeyForkControl::kLelBlockCount,
                    Next);
    if ((aIndex != pValues.size()) || (aInvalidCount != 0U)) {
        SetError(pErrorMessage,
                 "KeyForkControl contained out-of-range or trailing values");
    } else {
        SetError(pErrorMessage, "");
    }
    return aCandidate;
}

void CandidateFileName(
    const std::size_t pCandidateIndex,
    char *pName,
    const std::size_t pNameSize) {
    std::snprintf(pName, pNameSize,
                  "KeyFork_Candidate%02zu.bin",
                  pCandidateIndex + 1U);
}

} // namespace

void KeyForkControl::Reset(const std::uint64_t pSeed) {
    static_assert(S_BLOCK == 32768,
                  "KeyForkControl requires 32,768-byte source lanes.");
    static_assert(W_KEY == 2048,
                  "KeyForkControl requires 2,048-byte key inputs.");
    static_assert(kCandidateValueCount == 1792U,
                  "KeyForkControl binary format changed.");
    sCandidates.clear();
    Random::Seed(static_cast<int>(pSeed ^ (pSeed >> 32U)));
    sDidReset = true;
}

std::string KeyForkControl::Generate(
    const std::uint64_t pExplorationCases) {
    if (!sDidReset || (sCandidates.size() >= kCandidateCount)) {
        return "";
    }

    const std::uint64_t aCases =
        std::max<std::uint64_t>(1ULL, pExplorationCases);
    Candidate aBest{};
    Score aBestScore{};
    bool aHasBest = false;
    for (std::uint64_t aCase = 0ULL; aCase < aCases; ++aCase) {
        const Candidate aCandidate = RandomCandidate();
        const Score aScore = CandidateScore(aCandidate);
        if (!aHasBest || Better(aScore, aBestScore)) {
            aBest = aCandidate;
            aBestScore = aScore;
            aHasBest = true;
        }
    }

    std::string aError;
    if (!aHasBest || !Validate(aBest, &aError)) {
        return "";
    }
    sCandidates.push_back(aBest);

    std::ostringstream aText;
    aText << "KeyForkControl candidate " << sCandidates.size()
          << "/" << kCandidateCount << " cases=" << aCases;
    if (sCandidates.size() == 1U) {
        aText << " distance=first";
    } else {
        aText << " distance={minimum:" << aBestScore.mMinimum
              << ", total:" << aBestScore.mTotal << "}";
    }
    aText << " weights={Mu:4, Lel:8, Goz:12}";
    return aText.str();
}

bool KeyForkControl::SaveValues(
    const std::string &pFolder,
    std::string *pErrorMessage) {
    if (sCandidates.size() != kCandidateCount) {
        SetError(pErrorMessage,
                 "KeyForkControl requires all 17 candidates before saving");
        return false;
    }
    const std::string aFolder = FileIO::ProjectRoot(pFolder);
    for (std::size_t i = 0U; i < sCandidates.size(); ++i) {
        std::string aError;
        if (!Validate(sCandidates[i], &aError)) {
            SetError(pErrorMessage, aError);
            return false;
        }
        char aName[48];
        CandidateFileName(i, aName, sizeof(aName));
        if (!ControlValueFile::Save(
                FileIO::Join(aFolder, aName),
                ControlValueFile::Kind::kKeyFork,
                CandidateValues(sCandidates[i]),
                pErrorMessage)) {
            return false;
        }
    }
    return true;
}

bool KeyForkControl::LoadValues(
    const std::string &pFolder,
    std::string *pErrorMessage) {
    if (!sDidReset || !sCandidates.empty()) {
        SetError(pErrorMessage,
                 "KeyForkControl::Reset must precede value loading");
        return false;
    }
    const std::string aFolder = FileIO::ProjectRoot(pFolder);
    for (std::size_t i = 0U; i < kCandidateCount; ++i) {
        char aName[48];
        CandidateFileName(i, aName, sizeof(aName));
        std::vector<std::uint64_t> aValues;
        if (!ControlValueFile::Load(
                FileIO::Join(aFolder, aName),
                ControlValueFile::Kind::kKeyFork,
                kCandidateValueCount,
                &aValues,
                pErrorMessage)) {
            return false;
        }
        std::string aError;
        Candidate aCandidate = CandidateFromValues(aValues, &aError);
        if (!aError.empty() || !Validate(aCandidate, &aError)) {
            SetError(pErrorMessage,
                     "KeyForkControl candidate " +
                     std::to_string(i + 1U) +
                     " was invalid: " + aError);
            return false;
        }
        sCandidates.push_back(aCandidate);
    }
    SetError(pErrorMessage, "");
    return true;
}

bool KeyForkControl::ValidateCandidate(
    const std::size_t pCandidateIndex,
    std::string *pErrorMessage) {
    if (pCandidateIndex >= sCandidates.size()) {
        SetError(pErrorMessage,
                 "KeyForkControl candidate index was out of range");
        return false;
    }
    return Validate(sCandidates[pCandidateIndex], pErrorMessage);
}

const KeyForkControl::Candidate *KeyForkControl::CandidateAt(
    const std::size_t pCandidateIndex) {
    return pCandidateIndex < sCandidates.size()
        ? &sCandidates[pCandidateIndex]
        : nullptr;
}

std::size_t KeyForkControl::GeneratedCount() {
    return sCandidates.size();
}
