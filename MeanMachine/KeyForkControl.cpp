#include "KeyForkControl.hpp"

#include "ControlValueFile.hpp"
#include "FileIO.hpp"
#include "TwistWorkSpace.hpp"

#include <algorithm>
#include <cstdio>
#include <limits>
#include <sstream>
#include <type_traits>
#include <vector>

namespace {

using Candidate = KeyForkControl::Candidate;

constexpr std::uint64_t kStageOneDistanceWeight = 3ULL;
constexpr std::uint64_t kStageTwoDistanceWeight = 1ULL;
constexpr std::size_t kFoldBlockSize = 2048U;
constexpr std::size_t kStageOneCellCount =
    KeyForkControl::kForkCount * KeyForkControl::kLaneCount *
    KeyForkControl::kStageOneBlockCount *
    KeyForkControl::kStageOneInputCount;
constexpr std::size_t kStageOneOutputCount =
    KeyForkControl::kForkCount * KeyForkControl::kLaneCount *
    KeyForkControl::kStageOneBlockCount;
constexpr std::size_t kStageTwoCellCount =
    KeyForkControl::kForkCount * KeyForkControl::kStageTwoOutputCount *
    KeyForkControl::kLaneCount;
constexpr std::size_t kStageTwoOutputCount =
    KeyForkControl::kForkCount * KeyForkControl::kStageTwoOutputCount;
constexpr std::size_t kCandidateValueCount =
    (KeyForkControl::kForkCount * KeyForkControl::kLaneCount) +
    (kStageOneCellCount * 4U) + kStageOneOutputCount +
    (kStageTwoCellCount * 3U) + kStageTwoOutputCount;

struct Score {
    std::uint64_t mMinimum = 0ULL;
    std::uint64_t mTotal = 0ULL;
};

std::vector<Candidate> sCandidates;
bool sDidReset = false;

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

constexpr std::array<std::array<std::uint8_t,
                                KeyForkControl::kLaneCount>,
                     KeyForkControl::kCandidateCount> kForkAHalfPlans = {{
    // Candidates 0-15 are balanced at every lane coordinate: each physical
    // half appears eight times. Candidate 16 is the valid unused spare.
    {{0U, 0U, 1U, 1U}}, {{0U, 1U, 0U, 1U}},
    {{0U, 1U, 1U, 0U}}, {{1U, 0U, 0U, 1U}},
    {{1U, 0U, 1U, 0U}}, {{1U, 1U, 0U, 0U}},
    {{0U, 0U, 1U, 1U}}, {{0U, 1U, 0U, 1U}},
    {{0U, 1U, 1U, 0U}}, {{1U, 0U, 0U, 1U}},
    {{1U, 0U, 1U, 0U}}, {{1U, 1U, 0U, 0U}},
    {{0U, 0U, 1U, 1U}}, {{1U, 1U, 0U, 0U}},
    {{0U, 1U, 0U, 1U}}, {{1U, 0U, 1U, 0U}},
    // Candidate 17 is a valid spare; the first 16 form the balanced family.
    {{0U, 1U, 1U, 0U}},
}};

constexpr std::array<std::array<std::uint8_t, 4U>, 24U>
kPermutationsFour = {{
    {{0U, 1U, 2U, 3U}}, {{0U, 1U, 3U, 2U}},
    {{0U, 2U, 1U, 3U}}, {{0U, 2U, 3U, 1U}},
    {{0U, 3U, 1U, 2U}}, {{0U, 3U, 2U, 1U}},
    {{1U, 0U, 2U, 3U}}, {{1U, 0U, 3U, 2U}},
    {{1U, 2U, 0U, 3U}}, {{1U, 2U, 3U, 0U}},
    {{1U, 3U, 0U, 2U}}, {{1U, 3U, 2U, 0U}},
    {{2U, 0U, 1U, 3U}}, {{2U, 0U, 3U, 1U}},
    {{2U, 1U, 0U, 3U}}, {{2U, 1U, 3U, 0U}},
    {{2U, 3U, 0U, 1U}}, {{2U, 3U, 1U, 0U}},
    {{3U, 0U, 1U, 2U}}, {{3U, 0U, 2U, 1U}},
    {{3U, 1U, 0U, 2U}}, {{3U, 1U, 2U, 0U}},
    {{3U, 2U, 0U, 1U}}, {{3U, 2U, 1U, 0U}},
}};

std::uint8_t Parity(std::size_t pValue) {
    pValue ^= pValue >> 2U;
    pValue ^= pValue >> 1U;
    return static_cast<std::uint8_t>(pValue & 1U);
}

std::uint16_t CoordinateOffset(const std::size_t pCandidateIndex,
                               const std::size_t pCoordinate,
                               const std::size_t pStageSalt) {
    // The odd candidate stride has period W_KEY. Therefore every offset at a
    // fixed coordinate differs across all 16 active candidates.
    return static_cast<std::uint16_t>(
        ((pCoordinate * 4051U) + pStageSalt +
         (pCandidateIndex * 127U)) & (kFoldBlockSize - 1U)
    );
}

Candidate MakeCandidate(const std::size_t pCandidateIndex) {
    Candidate aCandidate;

    for (std::size_t aLane = 0U;
         aLane < KeyForkControl::kLaneCount;
         ++aLane) {
        const std::uint8_t aHalf =
            kForkAHalfPlans[pCandidateIndex][aLane];
        aCandidate.mStageOne.mSourceHalves[0U][aLane] = aHalf;
        aCandidate.mStageOne.mSourceHalves[1U][aLane] =
            static_cast<std::uint8_t>(aHalf ^ 1U);
    }

    std::size_t aCoordinate = 0U;
    for (std::size_t aFork = 0U;
         aFork < KeyForkControl::kForkCount;
         ++aFork) {
        std::array<std::size_t,
                   KeyForkControl::kLaneCount> aSourceBlockIndices{};
        for (std::size_t aDestination = 0U;
             aDestination < KeyForkControl::kLaneCount;
             ++aDestination) {
            const std::array<std::uint8_t, 4U> &aLanePermutation =
                kPermutationsFour[
                    (pCandidateIndex + (aDestination * 5U) +
                     (aFork * 11U)) % kPermutationsFour.size()
                ];
            for (std::size_t aBlock = 0U;
                 aBlock < KeyForkControl::kStageOneBlockCount;
                 ++aBlock) {
                const std::uint8_t aBaseLane =
                    static_cast<std::uint8_t>(
                        (aBlock + aDestination + aFork) & 3U
                    );
                const std::uint8_t aPartnerLane =
                    static_cast<std::uint8_t>(
                        (aBaseLane +
                         ((((pCandidateIndex >> 2U) + aDestination + aFork) & 1U)
                              == 0U ? 1U : 3U)) & 3U
                    );
                const std::uint8_t aSourceLaneA =
                    aLanePermutation[aBaseLane];
                const std::uint8_t aSourceLaneB =
                    aLanePermutation[aPartnerLane];
                const std::array<std::uint8_t, 2U> aSourceLanes = {{
                    aSourceLaneA, aSourceLaneB,
                }};
                const std::size_t aLinearMask = 1U +
                    (((aFork * 16U) + (aDestination * 4U) + aBlock) % 15U);
                const bool aSwapBytes =
                    Parity(pCandidateIndex & aLinearMask) != 0U;
                for (std::size_t aInput = 0U;
                     aInput < KeyForkControl::kStageOneInputCount;
                     ++aInput) {
                    const std::uint8_t aSourceLane =
                        aSourceLanes[aInput];
                    const std::size_t aBlockIndex =
                        aSourceBlockIndices[aSourceLane]++;
                    aCandidate.mStageOne
                        .mSourceLanes[aFork][aDestination][aBlock][aInput] =
                        aSourceLane;
                    aCandidate.mStageOne
                        .mSourceBlocks[aFork][aDestination][aBlock][aInput] =
                        static_cast<std::uint8_t>(
                            (((1U + (2U * ((pCandidateIndex >> 3U) +
                                           aFork))) & 7U) *
                             aBlockIndex + (pCandidateIndex & 7U) +
                             (aSourceLane * 3U) + aFork) & 7U
                        );
                    aCandidate.mStageOne
                        .mSourceOffsets[aFork][aDestination][aBlock][aInput] =
                        CoordinateOffset(pCandidateIndex, aCoordinate++, 137U);
                    aCandidate.mStageOne
                        .mWordShifts[aFork][aDestination][aBlock][aInput] =
                        static_cast<std::uint8_t>(
                            aSwapBytes ? (1U - aInput) : aInput
                        );
                }
                aCandidate.mStageOne
                    .mOutputShifts[aFork][aDestination][aBlock] =
                    static_cast<std::uint8_t>(
                        kPermutationsFour[
                            (pCandidateIndex + (aDestination * 7U) +
                             (aFork * 13U)) % kPermutationsFour.size()
                        ][aBlock] >> 1U
                    );
            }
        }
    }

    aCoordinate = 0U;
    for (std::size_t aFork = 0U;
         aFork < KeyForkControl::kForkCount;
         ++aFork) {
        const std::array<std::uint8_t, 4U> &aOutputShifts =
            kPermutationsFour[
                ((pCandidateIndex * 7U) + (aFork * 11U)) %
                kPermutationsFour.size()
            ];
        for (std::size_t aOutput = 0U;
             aOutput < KeyForkControl::kStageTwoOutputCount;
             ++aOutput) {
            aCandidate.mStageTwo.mOutputShifts[aFork][aOutput] =
                aOutputShifts[aOutput];
            for (std::size_t aLane = 0U;
                 aLane < KeyForkControl::kLaneCount;
                 ++aLane) {
                aCandidate.mStageTwo.mSourceBlocks[aFork][aOutput][aLane] =
                    kPermutationsFour[
                        (pCandidateIndex + (aLane * 5U) +
                         (aFork * 7U)) % kPermutationsFour.size()
                    ][aOutput];
                aCandidate.mStageTwo.mSourceOffsets[aFork][aOutput][aLane] =
                    CoordinateOffset(pCandidateIndex, aCoordinate++, 911U);
                aCandidate.mStageTwo.mWordShifts[aFork][aOutput][aLane] =
                    kPermutationsFour[
                        ((pCandidateIndex * 5U) + (aOutput * 7U) +
                         (aFork * 11U)) % kPermutationsFour.size()
                    ][aLane];
            }
        }
    }
    return aCandidate;
}

template <typename Value>
std::uint64_t Different(const Value pLeft,
                        const Value pRight,
                        const std::uint64_t pWeight) {
    return pLeft == pRight ? 0ULL : pWeight;
}

std::uint64_t Distance(const Candidate &pLeft,
                       const Candidate &pRight) {
    std::uint64_t aDistance = 0ULL;
    for (std::size_t aFork = 0U;
         aFork < KeyForkControl::kForkCount;
         ++aFork) {
        for (std::size_t aLane = 0U;
             aLane < KeyForkControl::kLaneCount;
             ++aLane) {
            aDistance += Different(
                pLeft.mStageOne.mSourceHalves[aFork][aLane],
                pRight.mStageOne.mSourceHalves[aFork][aLane],
                kStageOneDistanceWeight);
        }
        for (std::size_t aDestination = 0U;
             aDestination < KeyForkControl::kLaneCount;
             ++aDestination) {
            for (std::size_t aBlock = 0U;
                 aBlock < KeyForkControl::kStageOneBlockCount;
                 ++aBlock) {
                aDistance += Different(
                    pLeft.mStageOne.mOutputShifts[aFork][aDestination][aBlock],
                    pRight.mStageOne.mOutputShifts[aFork][aDestination][aBlock],
                    kStageOneDistanceWeight);
                for (std::size_t aInput = 0U;
                     aInput < KeyForkControl::kStageOneInputCount;
                     ++aInput) {
                    aDistance += Different(
                        pLeft.mStageOne.mSourceLanes[aFork][aDestination][aBlock][aInput],
                        pRight.mStageOne.mSourceLanes[aFork][aDestination][aBlock][aInput],
                        kStageOneDistanceWeight);
                    aDistance += Different(
                        pLeft.mStageOne.mSourceBlocks[aFork][aDestination][aBlock][aInput],
                        pRight.mStageOne.mSourceBlocks[aFork][aDestination][aBlock][aInput],
                        kStageOneDistanceWeight);
                    aDistance += Different(
                        pLeft.mStageOne.mSourceOffsets[aFork][aDestination][aBlock][aInput],
                        pRight.mStageOne.mSourceOffsets[aFork][aDestination][aBlock][aInput],
                        kStageOneDistanceWeight);
                    aDistance += Different(
                        pLeft.mStageOne.mWordShifts[aFork][aDestination][aBlock][aInput],
                        pRight.mStageOne.mWordShifts[aFork][aDestination][aBlock][aInput],
                        kStageOneDistanceWeight);
                }
            }
        }
    }

    for (std::size_t aFork = 0U;
         aFork < KeyForkControl::kForkCount;
         ++aFork) {
        for (std::size_t aOutput = 0U;
             aOutput < KeyForkControl::kStageTwoOutputCount;
             ++aOutput) {
            aDistance += Different(
                pLeft.mStageTwo.mOutputShifts[aFork][aOutput],
                pRight.mStageTwo.mOutputShifts[aFork][aOutput],
                kStageTwoDistanceWeight);
            for (std::size_t aLane = 0U;
                 aLane < KeyForkControl::kLaneCount;
                 ++aLane) {
                aDistance += Different(
                    pLeft.mStageTwo.mSourceBlocks[aFork][aOutput][aLane],
                    pRight.mStageTwo.mSourceBlocks[aFork][aOutput][aLane],
                    kStageTwoDistanceWeight);
                aDistance += Different(
                    pLeft.mStageTwo.mSourceOffsets[aFork][aOutput][aLane],
                    pRight.mStageTwo.mSourceOffsets[aFork][aOutput][aLane],
                    kStageTwoDistanceWeight);
                aDistance += Different(
                    pLeft.mStageTwo.mWordShifts[aFork][aOutput][aLane],
                    pRight.mStageTwo.mWordShifts[aFork][aOutput][aLane],
                    kStageTwoDistanceWeight);
            }
        }
    }
    return aDistance;
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

template <std::size_t Count>
bool IsPermutation(const std::array<std::uint8_t, Count> &pValues) {
    std::array<std::uint8_t, Count> aSorted = pValues;
    std::sort(aSorted.begin(), aSorted.end());
    for (std::size_t i = 0U; i < Count; ++i) {
        if (aSorted[i] != i) {
            return false;
        }
    }
    return true;
}

bool Validate(const Candidate &pCandidate,
              std::string *pErrorMessage) {
    std::size_t aForkAUpperHalfCount = 0U;
    for (std::size_t aLane = 0U;
         aLane < KeyForkControl::kLaneCount;
         ++aLane) {
        const std::uint8_t aHalfA =
            pCandidate.mStageOne.mSourceHalves[0U][aLane];
        const std::uint8_t aHalfB =
            pCandidate.mStageOne.mSourceHalves[1U][aLane];
        if ((aHalfA >= 2U) || (aHalfB >= 2U) ||
            ((aHalfA ^ aHalfB) != 1U)) {
            SetError(pErrorMessage,
                     "KeyForkControl source halves were not complementary");
            return false;
        }
        aForkAUpperHalfCount += aHalfA;
    }
    if (aForkAUpperHalfCount != 2U) {
        SetError(pErrorMessage,
                 "KeyForkControl did not mix both physical halves into each fork");
        return false;
    }

    for (std::size_t aFork = 0U;
         aFork < KeyForkControl::kForkCount;
         ++aFork) {
        std::array<std::array<bool,
                              KeyForkControl::kSourceHalfBlockCount>,
                   KeyForkControl::kLaneCount> aUsedSourceBlocks{};
        for (std::size_t aDestination = 0U;
             aDestination < KeyForkControl::kLaneCount;
             ++aDestination) {
            std::array<std::size_t,
                       KeyForkControl::kLaneCount> aSourceUseCounts{};
            std::array<std::size_t, 2U> aOutputShiftCounts{};
            for (std::size_t aBlock = 0U;
                 aBlock < KeyForkControl::kStageOneBlockCount;
                 ++aBlock) {
                const std::uint8_t aOutputShift =
                    pCandidate.mStageOne
                        .mOutputShifts[aFork][aDestination][aBlock];
                if (aOutputShift >= 2U) {
                    SetError(pErrorMessage,
                             "KeyForkControl had invalid Stage-I output shift");
                    return false;
                }
                ++aOutputShiftCounts[aOutputShift];

                const std::uint8_t aSourceLaneA =
                    pCandidate.mStageOne
                        .mSourceLanes[aFork][aDestination][aBlock][0U];
                const std::uint8_t aSourceLaneB =
                    pCandidate.mStageOne
                        .mSourceLanes[aFork][aDestination][aBlock][1U];
                if ((aSourceLaneA >= KeyForkControl::kLaneCount) ||
                    (aSourceLaneB >= KeyForkControl::kLaneCount) ||
                    (aSourceLaneA == aSourceLaneB)) {
                    SetError(pErrorMessage,
                             "KeyForkControl Stage-I pair did not use two distinct lanes");
                    return false;
                }

                std::array<bool, 2U> aWordShiftSeen{};
                for (std::size_t aInput = 0U;
                     aInput < KeyForkControl::kStageOneInputCount;
                     ++aInput) {
                    const std::uint8_t aSourceLane =
                        pCandidate.mStageOne
                            .mSourceLanes[aFork][aDestination][aBlock][aInput];
                    const std::uint8_t aSourceBlock =
                        pCandidate.mStageOne
                            .mSourceBlocks[aFork][aDestination][aBlock][aInput];
                    const std::uint16_t aSourceOffset =
                        pCandidate.mStageOne
                            .mSourceOffsets[aFork][aDestination][aBlock][aInput];
                    const std::uint8_t aWordShift =
                        pCandidate.mStageOne
                            .mWordShifts[aFork][aDestination][aBlock][aInput];
                    if ((aSourceBlock >= KeyForkControl::kSourceHalfBlockCount) ||
                        aUsedSourceBlocks[aSourceLane][aSourceBlock] ||
                        (aSourceOffset >= kFoldBlockSize) ||
                        (aWordShift >= 2U) ||
                        aWordShiftSeen[aWordShift]) {
                        SetError(pErrorMessage,
                                 "KeyForkControl had invalid Stage-I source data");
                        return false;
                    }
                    aUsedSourceBlocks[aSourceLane][aSourceBlock] = true;
                    aWordShiftSeen[aWordShift] = true;
                    ++aSourceUseCounts[aSourceLane];
                }
            }
            for (const std::size_t aCount : aSourceUseCounts) {
                if (aCount != 2U) {
                    SetError(pErrorMessage,
                             "KeyForkControl Stage-I destination was not evenly sourced");
                    return false;
                }
            }
            if ((aOutputShiftCounts[0U] != 2U) ||
                (aOutputShiftCounts[1U] != 2U)) {
                SetError(pErrorMessage,
                         "KeyForkControl Stage-I output bytes were not balanced");
                return false;
            }
        }
        for (const auto &aLaneBlocks : aUsedSourceBlocks) {
            for (const bool aWasUsed : aLaneBlocks) {
                if (!aWasUsed) {
                    SetError(pErrorMessage,
                             "KeyForkControl Stage-I did not consume every source block");
                    return false;
                }
            }
        }

        if (!IsPermutation(pCandidate.mStageTwo.mOutputShifts[aFork])) {
            SetError(pErrorMessage,
                     "KeyForkControl Stage-II output shifts were not a permutation");
            return false;
        }
        for (std::size_t aLane = 0U;
             aLane < KeyForkControl::kLaneCount;
             ++aLane) {
            std::array<std::uint8_t,
                       KeyForkControl::kStageTwoSourceBlockCount> aRoute{};
            for (std::size_t aOutput = 0U;
                 aOutput < KeyForkControl::kStageTwoOutputCount;
                 ++aOutput) {
                aRoute[aOutput] = pCandidate.mStageTwo
                    .mSourceBlocks[aFork][aOutput][aLane];
            }
            if (!IsPermutation(aRoute)) {
                SetError(pErrorMessage,
                         "KeyForkControl Stage-II did not consume every source block");
                return false;
            }
        }
        for (std::size_t aOutput = 0U;
             aOutput < KeyForkControl::kStageTwoOutputCount;
             ++aOutput) {
            std::array<bool,
                       KeyForkControl::kLaneCount> aWordShiftSeen{};
            for (std::size_t aLane = 0U;
                 aLane < KeyForkControl::kLaneCount;
                 ++aLane) {
                const std::uint8_t aSourceBlock =
                    pCandidate.mStageTwo
                        .mSourceBlocks[aFork][aOutput][aLane];
                const std::uint16_t aSourceOffset =
                    pCandidate.mStageTwo
                        .mSourceOffsets[aFork][aOutput][aLane];
                const std::uint8_t aWordShift =
                    pCandidate.mStageTwo
                        .mWordShifts[aFork][aOutput][aLane];
                if ((aSourceBlock >= KeyForkControl::kStageTwoSourceBlockCount) ||
                    (aSourceOffset >= kFoldBlockSize) ||
                    (aWordShift >= KeyForkControl::kLaneCount) ||
                    aWordShiftSeen[aWordShift]) {
                    SetError(pErrorMessage,
                             "KeyForkControl had invalid Stage-II source data");
                    return false;
                }
                aWordShiftSeen[aWordShift] = true;
            }
        }
    }
    SetError(pErrorMessage, "");
    return true;
}

template <typename Value>
void AppendValue(const Value pValue,
                 std::vector<std::uint64_t> *pValues) {
    pValues->push_back(static_cast<std::uint64_t>(pValue));
}

template <typename Container>
void AppendNestedValues(const Container &pContainer,
                        std::vector<std::uint64_t> *pValues) {
    for (const auto &aValue : pContainer) {
        if constexpr (std::is_arithmetic_v<std::decay_t<decltype(aValue)>>) {
            AppendValue(aValue, pValues);
        } else {
            AppendNestedValues(aValue, pValues);
        }
    }
}

std::vector<std::uint64_t> CandidateValues(
    const Candidate &pCandidate) {
    std::vector<std::uint64_t> aValues;
    aValues.reserve(kCandidateValueCount);
    AppendNestedValues(pCandidate.mStageOne.mSourceHalves, &aValues);
    AppendNestedValues(pCandidate.mStageOne.mSourceLanes, &aValues);
    AppendNestedValues(pCandidate.mStageOne.mSourceBlocks, &aValues);
    AppendNestedValues(pCandidate.mStageOne.mSourceOffsets, &aValues);
    AppendNestedValues(pCandidate.mStageOne.mWordShifts, &aValues);
    AppendNestedValues(pCandidate.mStageOne.mOutputShifts, &aValues);
    AppendNestedValues(pCandidate.mStageTwo.mSourceBlocks, &aValues);
    AppendNestedValues(pCandidate.mStageTwo.mSourceOffsets, &aValues);
    AppendNestedValues(pCandidate.mStageTwo.mWordShifts, &aValues);
    AppendNestedValues(pCandidate.mStageTwo.mOutputShifts, &aValues);
    return aValues;
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
    auto Load = [&](auto &pContainer,
                    const std::uint64_t pLimit,
                    auto &&pLoad) -> void {
        for (auto &aValue : pContainer) {
            if constexpr (std::is_arithmetic_v<std::decay_t<decltype(aValue)>>) {
                aValue = static_cast<std::decay_t<decltype(aValue)>>(Next(pLimit));
            } else {
                pLoad(aValue, pLimit, pLoad);
            }
        }
    };
    Load(aCandidate.mStageOne.mSourceHalves, 2U, Load);
    Load(aCandidate.mStageOne.mSourceLanes, KeyForkControl::kLaneCount, Load);
    Load(aCandidate.mStageOne.mSourceBlocks,
         KeyForkControl::kSourceHalfBlockCount, Load);
    Load(aCandidate.mStageOne.mSourceOffsets, kFoldBlockSize, Load);
    Load(aCandidate.mStageOne.mWordShifts, 2U, Load);
    Load(aCandidate.mStageOne.mOutputShifts, 2U, Load);
    Load(aCandidate.mStageTwo.mSourceBlocks,
         KeyForkControl::kStageTwoSourceBlockCount, Load);
    Load(aCandidate.mStageTwo.mSourceOffsets, kFoldBlockSize, Load);
    Load(aCandidate.mStageTwo.mWordShifts, KeyForkControl::kLaneCount, Load);
    Load(aCandidate.mStageTwo.mOutputShifts,
         KeyForkControl::kStageTwoOutputCount, Load);
    if ((aIndex != pValues.size()) || (aInvalidCount != 0U)) {
        SetError(pErrorMessage,
                 "KeyForkControl contained out-of-range or trailing values");
    } else {
        SetError(pErrorMessage, "");
    }
    return aCandidate;
}

void CandidateFileName(const std::size_t pCandidateIndex,
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
    static_assert(S_HALF == 16384,
                  "KeyForkControl requires 16,384-byte source halves.");
    static_assert(W_KEY == 2048,
                  "KeyForkControl requires 2,048-byte outputs.");
    static_assert(kFoldBlockSize == W_KEY,
                  "KeyForkControl fold block size changed.");
    static_assert((S_HALF / kFoldBlockSize) == kSourceHalfBlockCount,
                  "KeyForkControl source-half block count changed.");
    static_assert(kCandidateValueCount == 400U,
                  "KeyForkControl binary format changed.");
    sCandidates.clear();
    (void)pSeed;
    sDidReset = true;
}

std::string KeyForkControl::Generate(
    const std::uint64_t pExplorationCases) {
    if (!sDidReset || (sCandidates.size() >= kCandidateCount)) {
        return "";
    }
    (void)pExplorationCases;
    Candidate aBest = MakeCandidate(sCandidates.size());
    const Score aBestScore = CandidateScore(aBest);
    std::string aError;
    if (!Validate(aBest, &aError)) {
        return "";
    }
    sCandidates.push_back(aBest);

    std::ostringstream aText;
    aText << "KeyForkControl candidate " << sCandidates.size()
          << ": minimum=";
    if (aBestScore.mMinimum ==
        std::numeric_limits<std::uint64_t>::max()) {
        aText << "first";
    } else {
        aText << aBestScore.mMinimum;
    }
    aText << " total=" << aBestScore.mTotal
          << " stage-weights={I:3, II:1}"
          << " construction=balanced";
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
                     std::to_string(i + 1U) + " was invalid: " + aError);
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
