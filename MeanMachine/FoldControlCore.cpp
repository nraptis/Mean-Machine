#include "FoldControlCore.hpp"

#include "ControlOffsetPool.hpp"
#include "FileIO.hpp"
#include "Library - Twist/TwistWorkSpace.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <vector>

namespace {

constexpr std::size_t kCandidateCount = 33U;
constexpr std::size_t kLaneCount = 4U;
constexpr std::size_t kChunkCount = 16U;
constexpr std::size_t kOffsetCount = kLaneCount * kChunkCount;
constexpr std::size_t kCandidateValueCount =
    kOffsetCount + kOffsetCount + kOffsetCount + kChunkCount;
constexpr std::uint64_t kChunkDistanceWeight = 7ULL;
constexpr std::uint64_t kShiftDistanceWeight = 6ULL;
constexpr std::uint64_t kOffsetDistanceWeight = 4ULL;
constexpr std::uint64_t kDiffuseDistanceWeight = 10ULL;
constexpr std::uint64_t kMaximumPairDistance =
    (kOffsetCount * (kChunkDistanceWeight +
                     kShiftDistanceWeight +
                     kOffsetDistanceWeight)) +
    (kChunkCount * kDiffuseDistanceWeight);

static_assert((S_BLOCK / W_KEY) == kChunkCount,
              "Fold controls require sixteen key-width chunks per lane.");
static_assert(kCandidateValueCount == 208U,
              "Fold control value count must remain explicit.");
static_assert(kMaximumPairDistance == 1248ULL,
              "Fold control diversity denominator changed.");

constexpr std::array<const char *, kCandidateCount> kCandidateNames = {
    "Achernar", "Alcor", "Aldebaran", "Alioth", "Alkaid", "Alnitak",
    "Altair", "Ankaa", "Antares", "Arcturus", "Athebyne", "Bellatrix",
    "Betelgeuse", "Canopus", "Capella", "Castor", "Mebsuta", "Menkent",
    "Mimosa", "Miram", "Mirfak", "Mothallah", "Naos", "Polaris",
    "Pollux", "Procyon", "Regulus", "Gemma", "Rigel", "Saiph",
    "Sirius", "Suhail", "Vega",
};

using Flavor = FoldControlCore::Flavor;
using Order4 = std::array<std::uint8_t, kLaneCount>;
using Order16 = std::array<std::uint8_t, kChunkCount>;

struct Candidate {
    std::array<Order4, kChunkCount> mChunks{};
    std::array<std::array<std::uint16_t, kLaneCount>, kChunkCount> mOffsets{};
    std::array<Order4, kChunkCount> mShifts{};
    std::array<std::uint8_t, kChunkCount> mDiffusers{};
};

struct Score {
    std::uint64_t mMinimum = 0ULL;
    std::uint64_t mTotal = 0ULL;
};

struct State {
    std::vector<Candidate> mCandidates;
    std::vector<std::string> mRendered;
    std::vector<std::uint64_t> mExplorationCases;
    std::array<std::uint16_t, kOffsetCount> mOffsetPool{};
    std::uint64_t mRandomState = 0ULL;
    bool mDidReset = false;
};

State gSeedState;
State gTwistState;

State &StateFor(const Flavor pFlavor) {
    return pFlavor == Flavor::kSeed ? gSeedState : gTwistState;
}

const char *MethodName(const Flavor pFlavor) {
    return pFlavor == Flavor::kSeed ? "FoldSeed" : "FoldTwist";
}

const char *ControlName(const Flavor pFlavor) {
    return pFlavor == Flavor::kSeed ? "FoldSeedControl" : "FoldTwistControl";
}

const char *FilePrefix(const Flavor pFlavor) {
    return pFlavor == Flavor::kSeed ? "FoldSeed" : "FoldTwist";
}

ControlValueFile::Kind FileKind(const Flavor pFlavor) {
    return pFlavor == Flavor::kSeed
        ? ControlValueFile::Kind::kFoldSeed
        : ControlValueFile::Kind::kFoldTwist;
}

std::uint64_t NextRandom(State *pState) {
    pState->mRandomState += 0x9E3779B97F4A7C15ULL;
    std::uint64_t aValue = pState->mRandomState;
    aValue = (aValue ^ (aValue >> 30U)) * 0xBF58476D1CE4E5B9ULL;
    aValue = (aValue ^ (aValue >> 27U)) * 0x94D049BB133111EBULL;
    return aValue ^ (aValue >> 31U);
}

std::size_t RandomIndex(State *pState,
                        const std::size_t pLimit) {
    return pLimit == 0U
        ? 0U
        : static_cast<std::size_t>(NextRandom(pState) % pLimit);
}

template <typename T, std::size_t Count>
void Shuffle(State *pState,
             std::array<T, Count> *pValues) {
    for (std::size_t i = Count; i > 1U; --i) {
        std::swap((*pValues)[i - 1U],
                  (*pValues)[RandomIndex(pState, i)]);
    }
}

Order4 RandomOrder4(State *pState) {
    Order4 aOrder = {0U, 1U, 2U, 3U};
    Shuffle(pState, &aOrder);
    return aOrder;
}

Order16 RandomOrder16(State *pState) {
    Order16 aOrder{};
    for (std::size_t i = 0U; i < aOrder.size(); ++i) {
        aOrder[i] = static_cast<std::uint8_t>(i);
    }
    Shuffle(pState, &aOrder);
    return aOrder;
}

void BuildOffsetPool(State *pState,
                     const Flavor pFlavor) {
    pState->mOffsetPool = ControlOffsetPool::Build<kOffsetCount>(
        pFlavor == Flavor::kSeed
            ? ControlOffsetPool::kFoldSeedKeyStart
            : ControlOffsetPool::kFoldTwistKeyStart,
        static_cast<std::size_t>(W_KEY)
    );
}

Candidate MakeCandidate(State *pState) {
    Candidate aCandidate;

    for (std::size_t aLane = 0U; aLane < kLaneCount; ++aLane) {
        const Order16 aChunks = RandomOrder16(pState);
        for (std::size_t aLoop = 0U; aLoop < kChunkCount; ++aLoop) {
            aCandidate.mChunks[aLoop][aLane] = aChunks[aLoop];
        }
    }

    std::array<std::uint16_t, kOffsetCount> aOffsets =
        pState->mOffsetPool;
    Shuffle(pState, &aOffsets);
    for (std::size_t aLoop = 0U; aLoop < kChunkCount; ++aLoop) {
        for (std::size_t aLane = 0U; aLane < kLaneCount; ++aLane) {
            aCandidate.mOffsets[aLoop][aLane] =
                aOffsets[(aLoop * kLaneCount) + aLane];
        }
        aCandidate.mShifts[aLoop] = RandomOrder4(pState);
        aCandidate.mDiffusers[aLoop] =
            static_cast<std::uint8_t>(RandomIndex(pState, 3U));
    }

    return aCandidate;
}

std::vector<std::uint64_t> CandidateValues(const Candidate &pCandidate) {
    std::vector<std::uint64_t> aValues;
    aValues.reserve(kCandidateValueCount);
    for (const Order4 &aChunks : pCandidate.mChunks) {
        for (const std::uint8_t aValue : aChunks) {
            aValues.push_back(aValue);
        }
    }
    for (const auto &aOffsets : pCandidate.mOffsets) {
        for (const std::uint16_t aValue : aOffsets) {
            aValues.push_back(aValue);
        }
    }
    for (const Order4 &aShifts : pCandidate.mShifts) {
        for (const std::uint8_t aValue : aShifts) {
            aValues.push_back(aValue);
        }
    }
    for (const std::uint8_t aValue : pCandidate.mDiffusers) {
        aValues.push_back(aValue);
    }
    return aValues;
}

Candidate CandidateFromValues(const std::vector<std::uint64_t> &pValues,
                              const Flavor pFlavor,
                              std::string *pWarningMessage) {
    Candidate aCandidate;
    std::size_t aIndex = 0U;
    std::size_t aInvalidCount = 0U;
    auto Next = [&](const std::uint64_t pLimit) {
        const std::uint64_t aRaw =
            aIndex < pValues.size() ? pValues[aIndex] : 0ULL;
        ++aIndex;
        if (aRaw >= pLimit) {
            ++aInvalidCount;
            return 0ULL;
        }
        return aRaw;
    };

    for (Order4 &aChunks : aCandidate.mChunks) {
        for (std::uint8_t &aValue : aChunks) {
            aValue = static_cast<std::uint8_t>(Next(kChunkCount));
        }
    }
    for (auto &aOffsets : aCandidate.mOffsets) {
        for (std::uint16_t &aValue : aOffsets) {
            aValue = static_cast<std::uint16_t>(Next(W_KEY));
        }
    }
    for (Order4 &aShifts : aCandidate.mShifts) {
        for (std::uint8_t &aValue : aShifts) {
            aValue = static_cast<std::uint8_t>(Next(kLaneCount));
        }
    }
    for (std::uint8_t &aValue : aCandidate.mDiffusers) {
        aValue = static_cast<std::uint8_t>(Next(3U));
    }

    if ((pWarningMessage != nullptr) && (aInvalidCount != 0U)) {
        *pWarningMessage =
            std::string(ControlName(pFlavor)) + " contained " +
            std::to_string(aInvalidCount) +
            " out-of-range value(s).";
    }
    return aCandidate;
}

std::uint64_t Distance(const Candidate &pLeft,
                       const Candidate &pRight) {
    std::uint64_t aDistance = 0ULL;
    for (std::size_t aLoop = 0U; aLoop < kChunkCount; ++aLoop) {
        for (std::size_t aLane = 0U; aLane < kLaneCount; ++aLane) {
            aDistance +=
                pLeft.mChunks[aLoop][aLane] != pRight.mChunks[aLoop][aLane]
                    ? kChunkDistanceWeight
                    : 0ULL;
            aDistance +=
                pLeft.mOffsets[aLoop][aLane] != pRight.mOffsets[aLoop][aLane]
                    ? kOffsetDistanceWeight
                    : 0ULL;
            aDistance +=
                pLeft.mShifts[aLoop][aLane] != pRight.mShifts[aLoop][aLane]
                    ? kShiftDistanceWeight
                    : 0ULL;
        }
        aDistance +=
            pLeft.mDiffusers[aLoop] != pRight.mDiffusers[aLoop]
                ? kDiffuseDistanceWeight
                : 0ULL;
    }
    return aDistance;
}

Score FamilyScore(const State &pState,
                  const Candidate &pCandidate) {
    if (pState.mCandidates.empty()) {
        return {std::numeric_limits<std::uint64_t>::max(), 0ULL};
    }
    Score aScore{std::numeric_limits<std::uint64_t>::max(), 0ULL};
    for (const Candidate &aExisting : pState.mCandidates) {
        const std::uint64_t aDistance =
            Distance(pCandidate, aExisting);
        aScore.mMinimum = std::min(aScore.mMinimum, aDistance);
        aScore.mTotal += aDistance;
    }
    return aScore;
}

bool Better(const Score &pLeft,
            const Score &pRight) {
    return (pLeft.mMinimum > pRight.mMinimum) ||
           ((pLeft.mMinimum == pRight.mMinimum) &&
            (pLeft.mTotal > pRight.mTotal));
}

Candidate Explore(State *pState,
                  const std::uint64_t pCases,
                  Score *pScore) {
    Candidate aBest = MakeCandidate(pState);
    Score aBestScore = FamilyScore(*pState, aBest);
    for (std::uint64_t i = 1ULL; i < pCases; ++i) {
        Candidate aTrial = MakeCandidate(pState);
        const Score aTrialScore = FamilyScore(*pState, aTrial);
        if (Better(aTrialScore, aBestScore)) {
            aBest = aTrial;
            aBestScore = aTrialScore;
        }
    }
    if (pScore != nullptr) {
        *pScore = aBestScore;
    }
    return aBest;
}

const char *DiffuseName(const std::uint8_t pIndex) {
    static const char *kNames[] = {
        "DiffuseA",
        "DiffuseB",
        "DiffuseC",
    };
    return kNames[pIndex % 3U];
}

char Letter(const std::size_t pIndex) {
    return static_cast<char>('A' + static_cast<int>(pIndex));
}

std::string Render(const Candidate &pCandidate,
                   const Flavor pFlavor,
                   const std::size_t pCandidateIndex,
                   const std::string &pClassName,
                   const Score &pScore,
                   const std::uint64_t pCases) {
    std::ostringstream aStream;
    aStream
        << "// " << ControlName(pFlavor) << " candidate "
        << (pCandidateIndex + 1U) << " of " << kCandidateCount << "\n";
    if (pCases == 0ULL) {
        aStream << "// Exploration cases: persisted candidate\n";
    } else {
        aStream << "// Exploration cases: " << pCases << "\n";
    }
    if (pCandidateIndex == 0U) {
        aStream
            << "// Structural distance: initial random-shuffle baseline\n";
    } else {
        aStream
            << "// Structural distance from earlier candidates: nearest "
            << pScore.mMinimum << " / " << kMaximumPairDistance
            << "; total " << pScore.mTotal << "\n";
    }
    aStream
        << "void " << pClassName << "::" << MethodName(pFlavor)
        << "(TwistWorkSpace *pWorkSpace,\n"
        << "                                      std::uint8_t *pDestination) {\n"
        << "    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }\n"
        << "\n"
        << "    std::uint8_t *aPoisonLaneA = pWorkSpace->mPoisonLaneA;\n"
        << "    std::uint8_t *aPoisonLaneB = pWorkSpace->mPoisonLaneB;\n"
        << "    std::uint8_t *aPoisonLaneC = pWorkSpace->mPoisonLaneC;\n"
        << "    std::uint8_t *aPoisonLaneD = pWorkSpace->mPoisonLaneD;\n"
        << "\n";
    for (std::size_t aChunk = 0U;
         aChunk < kChunkCount;
         ++aChunk) {
        aStream
            << "    std::uint8_t *aDestinationLane"
            << Letter(aChunk)
            << " = pDestination + (" << aChunk
            << "U * W_KEY);\n";
    }
    aStream
        << "\n"
        << "    static_assert((S_BLOCK / W_KEY) == 16,\n"
        << "                  \"" << MethodName(pFlavor)
        << " expects sixteen key-width chunks per lane.\");\n";

    for (std::size_t aLoop = 0U; aLoop < kChunkCount; ++aLoop) {
        aStream
            << "\n"
            << "    //\n"
            << "    // " << MethodName(pFlavor) << " — Chunk "
            << Letter(aLoop) << "\n"
            << "    //\n"
            << "    {\n";
        for (std::size_t aLane = 0U; aLane < kLaneCount; ++aLane) {
            aStream
                << "        const std::size_t aFoldBase" << Letter(aLane)
            << " = " << static_cast<unsigned>(
                    pCandidate.mChunks[aLoop][aLane]
                ) << "U * W_KEY;\n";
        }
        aStream
            << "        for (std::size_t aIndex = 0U;\n"
            << "             aIndex < static_cast<std::size_t>(W_KEY);\n"
            << "             aIndex += 1U) {\n";
        for (std::size_t aLane = 0U; aLane < kLaneCount; ++aLane) {
            aStream
                << "            const std::size_t aFoldIndex"
                << Letter(aLane) << " = aFoldBase" << Letter(aLane)
                << " + ((aIndex + "
                << pCandidate.mOffsets[aLoop][aLane]
                << "U) & W_KEY1);\n";
        }
        aStream
            << "            std::uint32_t aFoldWord =\n"
            << "                (static_cast<std::uint32_t>(aPoisonLaneA[aFoldIndexA]) << "
            << (static_cast<unsigned>(pCandidate.mShifts[aLoop][0]) * 8U)
            << "U) |\n"
            << "                (static_cast<std::uint32_t>(aPoisonLaneB[aFoldIndexB]) << "
            << (static_cast<unsigned>(pCandidate.mShifts[aLoop][1]) * 8U)
            << "U) |\n"
            << "                (static_cast<std::uint32_t>(aPoisonLaneC[aFoldIndexC]) << "
            << (static_cast<unsigned>(pCandidate.mShifts[aLoop][2]) * 8U)
            << "U) |\n"
            << "                (static_cast<std::uint32_t>(aPoisonLaneD[aFoldIndexD]) << "
            << (static_cast<unsigned>(pCandidate.mShifts[aLoop][3]) * 8U)
            << "U);\n"
            << "            aFoldWord = TwistMix32::"
            << DiffuseName(pCandidate.mDiffusers[aLoop])
            << "(aFoldWord);\n"
            << "            aDestinationLane" << Letter(aLoop)
            << "[aIndex] =\n"
            << "                static_cast<std::uint8_t>(aFoldWord);\n"
            << "        }\n"
            << "    }\n";
    }
    aStream << "}\n";
    return aStream.str();
}

bool IsPermutation4(const Order4 &pValues) {
    Order4 aSorted = pValues;
    std::sort(aSorted.begin(), aSorted.end());
    return aSorted == Order4{0U, 1U, 2U, 3U};
}

bool Validate(const Candidate &pCandidate,
              std::string *pErrorMessage) {
    for (std::size_t aLane = 0U; aLane < kLaneCount; ++aLane) {
        Order16 aChunks{};
        for (std::size_t aLoop = 0U; aLoop < kChunkCount; ++aLoop) {
            aChunks[aLoop] = pCandidate.mChunks[aLoop][aLane];
        }
        std::sort(aChunks.begin(), aChunks.end());
        for (std::size_t i = 0U; i < aChunks.size(); ++i) {
            if (aChunks[i] != i) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage =
                        "Source lane chunk routes were not a permutation of A-P.";
                }
                return false;
            }
        }
    }

    std::array<std::uint16_t, kOffsetCount> aOffsets{};
    std::size_t aOffsetIndex = 0U;
    for (std::size_t aLoop = 0U; aLoop < kChunkCount; ++aLoop) {
        if (!IsPermutation4(pCandidate.mShifts[aLoop])) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Fold byte shifts were not a permutation of 0, 8, 16, 24.";
            }
            return false;
        }
        if (pCandidate.mDiffusers[aLoop] >= 3U) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Fold diffuser index was out of range.";
            }
            return false;
        }
        for (const std::uint16_t aOffset : pCandidate.mOffsets[aLoop]) {
            if (aOffset >= W_KEY) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "Fold offset was outside W_KEY.";
                }
                return false;
            }
            aOffsets[aOffsetIndex++] = aOffset;
        }
    }
    std::sort(aOffsets.begin(), aOffsets.end());
    if (std::adjacent_find(aOffsets.begin(), aOffsets.end()) !=
        aOffsets.end()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Fold offsets were not unique.";
        }
        return false;
    }

    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    return true;
}

bool ValidateOffsetPool(const State &pState,
                        const Candidate &pCandidate,
                        std::string *pErrorMessage) {
    std::array<std::uint16_t, kOffsetCount> aActualOffsets{};
    std::size_t aIndex = 0U;
    for (const auto &aLoopOffsets : pCandidate.mOffsets) {
        for (const std::uint16_t aOffset : aLoopOffsets) {
            aActualOffsets[aIndex++] = aOffset;
        }
    }
    std::array<std::uint16_t, kOffsetCount> aExpectedOffsets =
        pState.mOffsetPool;
    std::sort(aActualOffsets.begin(), aActualOffsets.end());
    std::sort(aExpectedOffsets.begin(), aExpectedOffsets.end());
    if (aActualOffsets != aExpectedOffsets) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Fold candidate did not use its complete preplanned "
                "offset pool.";
        }
        return false;
    }
    return true;
}

} // namespace

void FoldControlCore::Reset(const Flavor pFlavor,
                            const std::uint64_t pSeed) {
    State &aState = StateFor(pFlavor);
    aState = State{};
    aState.mRandomState = pSeed == 0ULL
        ? (pFlavor == Flavor::kSeed
               ? 0x464F4C4453454544ULL
               : 0x464F4C4454574953ULL)
        : pSeed;
    if ((static_cast<std::size_t>(W_KEY) < kOffsetCount) ||
        (static_cast<std::uint64_t>(W_KEY) >
         static_cast<std::uint64_t>(
             std::numeric_limits<std::uint16_t>::max()
         ) + 1ULL)) {
        std::abort();
    }
    static_assert(
        ControlOffsetPool::kKeyAllocationCount <=
            static_cast<std::size_t>(W_KEY),
        "Preplanned key-offset families exceed W_KEY."
    );
    BuildOffsetPool(&aState, pFlavor);
    aState.mDidReset = true;
}

std::string FoldControlCore::Generate(
    const Flavor pFlavor,
    const std::uint64_t pExplorationCases) {
    State &aState = StateFor(pFlavor);
    if (!aState.mDidReset ||
        (aState.mCandidates.size() >= kCandidateCount)) {
        std::abort();
    }
    const std::uint64_t aCases =
        std::max<std::uint64_t>(1ULL, pExplorationCases);
    Score aScore;
    Candidate aCandidate;
    std::uint64_t aReportedCases = aCases;
    if (aState.mCandidates.empty()) {
        aCandidate = MakeCandidate(&aState);
        aScore = Score{
            std::numeric_limits<std::uint64_t>::max(),
            0ULL,
        };
        aReportedCases = 1ULL;
    } else {
        aCandidate = Explore(&aState, aCases, &aScore);
    }
    std::string aValidationError;
    if (!Validate(aCandidate, &aValidationError)) {
        std::abort();
    }
    const std::size_t aIndex = aState.mCandidates.size();
    aState.mCandidates.push_back(aCandidate);
    aState.mExplorationCases.push_back(aReportedCases);
    aState.mRendered.push_back(
        Render(aCandidate,
               pFlavor,
               aIndex,
               std::string("TwistExpander_") + kCandidateNames[aIndex],
               aScore,
               aReportedCases)
    );
    return aState.mRendered.back();
}

std::string FoldControlCore::RenderCandidate(
    const Flavor pFlavor,
    const std::size_t pCandidateIndex,
    const std::string &pClassName) {
    const State &aState = StateFor(pFlavor);
    if ((pCandidateIndex >= aState.mCandidates.size()) ||
        pClassName.empty()) {
        return "";
    }
    const Score aScore =
        pCandidateIndex == 0U
            ? Score{std::numeric_limits<std::uint64_t>::max(), 0ULL}
            : [&]() {
                  State aPriorState;
                  aPriorState.mCandidates.assign(
                      aState.mCandidates.begin(),
                      aState.mCandidates.begin() + pCandidateIndex
                  );
                  return FamilyScore(aPriorState,
                                     aState.mCandidates[pCandidateIndex]);
              }();
    return Render(aState.mCandidates[pCandidateIndex],
                  pFlavor,
                  pCandidateIndex,
                  pClassName,
                  aScore,
                  pCandidateIndex < aState.mExplorationCases.size()
                      ? aState.mExplorationCases[pCandidateIndex]
                      : 0ULL);
}

void FoldControlCore::Print(const Flavor pFlavor) {
    for (const std::string &aText : StateFor(pFlavor).mRendered) {
        std::printf("%s\n", aText.c_str());
    }
}

bool FoldControlCore::SaveValues(const Flavor pFlavor,
                                 const std::string &pFolder,
                                 std::string *pErrorMessage) {
    const State &aState = StateFor(pFlavor);
    if (aState.mCandidates.size() != kCandidateCount) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                std::string(ControlName(pFlavor)) +
                " needs all 33 candidates before saving values.";
        }
        return false;
    }
    const std::string aFolder = FileIO::ProjectRoot(pFolder);
    for (std::size_t i = 0U; i < aState.mCandidates.size(); ++i) {
        char aName[48];
        std::snprintf(aName,
                      sizeof(aName),
                      "%s_Candidate%02zu.bin",
                      FilePrefix(pFlavor),
                      i + 1U);
        if (!ControlValueFile::Save(
                FileIO::Join(aFolder, aName),
                FileKind(pFlavor),
                CandidateValues(aState.mCandidates[i]),
                pErrorMessage)) {
            return false;
        }
    }
    return true;
}

bool FoldControlCore::LoadValues(
    const Flavor pFlavor,
    const std::string &pFolder,
    std::string *pErrorMessage) {
    State &aState = StateFor(pFlavor);
    if (!aState.mDidReset || !aState.mCandidates.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                std::string(ControlName(pFlavor)) +
                "::Reset must precede value loading.";
        }
        return false;
    }
    const std::string aFolder = FileIO::ProjectRoot(pFolder);
    for (std::size_t i = 0U; i < kCandidateCount; ++i) {
        char aName[48];
        std::snprintf(aName,
                      sizeof(aName),
                      "%s_Candidate%02zu.bin",
                      FilePrefix(pFlavor),
                      i + 1U);
        std::vector<std::uint64_t> aValues;
        std::string aLoadWarning;
        if (!ControlValueFile::Load(
                FileIO::Join(aFolder, aName),
                FileKind(pFlavor),
                kCandidateValueCount,
                &aValues,
                &aLoadWarning)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = aLoadWarning;
            }
            return false;
        }
        std::string aValueWarning;
        Candidate aCandidate =
            CandidateFromValues(aValues, pFlavor, &aValueWarning);
        if (!aValueWarning.empty()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = aValueWarning;
            }
            return false;
        }
        std::string aValidationError;
        if (!Validate(aCandidate, &aValidationError) ||
            !ValidateOffsetPool(aState,
                                aCandidate,
                                &aValidationError)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    std::string(ControlName(pFlavor)) +
                    " candidate " + std::to_string(i + 1U) +
                    " was invalid: " + aValidationError;
            }
            return false;
        }
        const Score aScore = FamilyScore(aState, aCandidate);
        aState.mCandidates.push_back(aCandidate);
        aState.mExplorationCases.push_back(0ULL);
        aState.mRendered.push_back(
            Render(aCandidate,
                   pFlavor,
                   i,
                   std::string("TwistExpander_") + kCandidateNames[i],
                   aScore,
                   0ULL)
        );
    }
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    return true;
}

bool FoldControlCore::ValidateCandidate(
    const Flavor pFlavor,
    const std::size_t pCandidateIndex,
    std::string *pErrorMessage) {
    const State &aState = StateFor(pFlavor);
    if (pCandidateIndex >= aState.mCandidates.size()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Fold candidate index was out of range.";
        }
        return false;
    }
    const Candidate &aCandidate =
        aState.mCandidates[pCandidateIndex];
    if (!Validate(aCandidate, pErrorMessage)) {
        return false;
    }

    if (!ValidateOffsetPool(aState, aCandidate, pErrorMessage)) {
        return false;
    }
    return true;
}

std::size_t FoldControlCore::GeneratedCount(const Flavor pFlavor) {
    return StateFor(pFlavor).mCandidates.size();
}
