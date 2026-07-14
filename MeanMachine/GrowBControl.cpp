#include "GrowBControl.hpp"

#include "FileIO.hpp"
#include "Library - Twist/TwistWorkSpace.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <limits>
#include <sstream>
#include <vector>

namespace {

constexpr std::size_t kWidth = 4U;
constexpr std::size_t kCandidateCount = 33U;
constexpr std::size_t kQuarterOffsetCount = 16U;
constexpr std::size_t kKeyOffsetCount = 20U;
constexpr std::size_t kRoutedFoldCount = 8U;
constexpr std::uint64_t kBaseDistanceWeight = 7ULL;
constexpr std::uint64_t kShiftDistanceWeight = 6ULL;
constexpr std::uint64_t kOffsetDistanceWeight = 4ULL;
constexpr std::uint64_t kDiffuseDistanceWeight = 10ULL;
constexpr std::uint64_t kMaximumPairDistance =
    (static_cast<std::uint64_t>(kRoutedFoldCount) *
     ((static_cast<std::uint64_t>(kWidth) *
       (kBaseDistanceWeight + kShiftDistanceWeight +
        kOffsetDistanceWeight)) +
      kDiffuseDistanceWeight)) +
    (static_cast<std::uint64_t>(kWidth) *
     (kShiftDistanceWeight + kOffsetDistanceWeight)) +
    kDiffuseDistanceWeight;
static_assert(kMaximumPairDistance == 674ULL,
              "GrowB diversity denominator must match its effective fields.");

constexpr std::array<const char *, kCandidateCount> kNames = {
    "Achernar", "Alcor", "Aldebaran", "Alioth", "Alkaid", "Alnitak",
    "Altair", "Ankaa", "Antares", "Arcturus", "Athebyne", "Bellatrix",
    "Betelgeuse", "Canopus", "Capella", "Castor", "Mebsuta", "Menkent",
    "Mimosa", "Miram", "Mirfak", "Mothallah", "Naos", "Polaris",
    "Pollux", "Procyon", "Regulus", "Gemma", "Rigel", "Saiph",
    "Sirius", "Suhail", "Vega"
};

using Order4 = std::array<std::uint8_t, kWidth>;

struct Candidate {
    // The outer index is the fixed destination lane and the inner index is
    // the fixed source lane. Each source column is a permutation, so every
    // source quarter/chunk reaches exactly one destination.
    std::array<Order4, 4U> mQuarterBases{};
    std::array<Order4, 4U> mQuarterShifts{};
    std::array<std::array<std::uint16_t, 4U>, 4U> mQuarterOffsets{};
    std::array<std::uint8_t, 4U> mQuarterDiffuse{};

    std::array<Order4, 4U> mKeyBases{};
    std::array<Order4, 4U> mKeyShifts{};
    std::array<std::array<std::uint16_t, 4U>, 4U> mKeyOffsets{};
    std::array<std::uint8_t, 4U> mKeyDiffuse{};

    Order4 mFinalShifts{};
    std::array<std::uint16_t, 4U> mFinalOffsets{};
    std::uint8_t mFinalDiffuse = 0U;
};

struct Score {
    std::uint64_t mMinimum = 0ULL;
    std::uint64_t mTotal = 0ULL;
};

struct FrequencyTable {
    std::array<std::array<std::uint8_t, 4U>, 32U> mBases{};
    std::array<std::array<std::uint8_t, 4U>, 36U> mShifts{};
    std::array<std::vector<std::uint8_t>, kQuarterOffsetCount> mQuarterOffsets{};
    std::array<std::vector<std::uint8_t>, kKeyOffsetCount> mKeyOffsets{};
    std::array<std::array<std::uint8_t, 3U>, 9U> mDiffusers{};
    std::size_t mCandidateCount = 0U;
};

std::vector<Candidate> gCandidates;
std::vector<std::string> gRendered;
FrequencyTable gFrequencies;
std::uint64_t gRandomState = 0ULL;
bool gDidReset = false;

std::uint64_t NextRandom() {
    gRandomState += 0x9E3779B97F4A7C15ULL;
    std::uint64_t aValue = gRandomState;
    aValue = (aValue ^ (aValue >> 30U)) * 0xBF58476D1CE4E5B9ULL;
    aValue = (aValue ^ (aValue >> 27U)) * 0x94D049BB133111EBULL;
    return aValue ^ (aValue >> 31U);
}

std::size_t RandomIndex(const std::size_t pLimit) {
    return pLimit == 0U ? 0U : static_cast<std::size_t>(NextRandom() % pLimit);
}

template <typename T, std::size_t Count>
void Shuffle(std::array<T, Count> *pValues) {
    for (std::size_t i = Count; i > 1U; --i) {
        std::swap((*pValues)[i - 1U], (*pValues)[RandomIndex(i)]);
    }
}

Order4 RandomOrder() {
    Order4 aOrder = {0U, 1U, 2U, 3U};
    Shuffle(&aOrder);
    return aOrder;
}

bool HasAtLeastThreeDistinct(const Order4 &pOrder) {
    std::array<bool, kWidth> aSeen{};
    std::size_t aDistinctCount = 0U;
    for (const std::uint8_t aValue : pOrder) {
        if (!aSeen[aValue]) {
            aSeen[aValue] = true;
            ++aDistinctCount;
        }
    }
    return aDistinctCount >= 3U;
}

std::array<Order4, 4U> RandomRoutes() {
    std::array<Order4, 4U> aRoutes{};
    bool aValid = false;
    while (!aValid) {
        for (std::size_t aSourceLane = 0U; aSourceLane < 4U; ++aSourceLane) {
            const Order4 aSourceRoute = RandomOrder();
            for (std::size_t aDestinationLane = 0U;
                 aDestinationLane < 4U;
                 ++aDestinationLane) {
                aRoutes[aDestinationLane][aSourceLane] =
                    aSourceRoute[aDestinationLane];
            }
        }
        aValid = std::all_of(
            aRoutes.begin(),
            aRoutes.end(),
            [](const Order4 &pRoute) {
                return HasAtLeastThreeDistinct(pRoute);
            });
    }
    return aRoutes;
}

template <std::size_t Count>
std::array<std::uint16_t, Count> RandomDistinctResidues(
    const std::size_t pResidueCount) {
    std::array<std::uint16_t, Count> aResidues{};
    for (std::size_t i = 0U; i < Count; ++i) {
        std::uint16_t aResidue = 0U;
        do {
            aResidue = static_cast<std::uint16_t>(RandomIndex(pResidueCount));
        } while (std::find(aResidues.begin(), aResidues.begin() + i, aResidue) !=
                 (aResidues.begin() + i));
        aResidues[i] = aResidue;
    }
    return aResidues;
}

Candidate MakeCandidate() {
    Candidate aCandidate;
    const std::array<std::uint16_t, kQuarterOffsetCount> aQuarterOffsets =
        RandomDistinctResidues<kQuarterOffsetCount>(S_QUARTER);
    const std::array<std::uint16_t, kKeyOffsetCount> aKeyOffsets =
        RandomDistinctResidues<kKeyOffsetCount>(W_KEY);

    aCandidate.mQuarterBases = RandomRoutes();
    aCandidate.mKeyBases = RandomRoutes();

    for (std::size_t aLoop = 0U; aLoop < 4U; ++aLoop) {
        aCandidate.mQuarterShifts[aLoop] = RandomOrder();
        aCandidate.mQuarterDiffuse[aLoop] = static_cast<std::uint8_t>(RandomIndex(3U));
        aCandidate.mKeyShifts[aLoop] = RandomOrder();
        aCandidate.mKeyDiffuse[aLoop] = static_cast<std::uint8_t>(RandomIndex(3U));
        for (std::size_t i = 0U; i < 4U; ++i) {
            aCandidate.mQuarterOffsets[aLoop][i] =
                aQuarterOffsets[(aLoop * 4U) + i];
            aCandidate.mKeyOffsets[aLoop][i] =
                aKeyOffsets[(aLoop * 4U) + i];
        }
    }

    aCandidate.mFinalShifts = RandomOrder();
    aCandidate.mFinalDiffuse = static_cast<std::uint8_t>(RandomIndex(3U));
    for (std::size_t i = 0U; i < 4U; ++i) {
        aCandidate.mFinalOffsets[i] = aKeyOffsets[16U + i];
    }
    return aCandidate;
}

std::uint64_t Distance(const Candidate &a, const Candidate &b) {
    std::uint64_t d = 0ULL;
    auto CompareRoutedFold = [&](const Order4 &pLeftBases,
                                 const Order4 &pLeftShifts,
                                 const std::array<std::uint16_t, 4U> &pLeftOffsets,
                                 const Order4 &pRightBases,
                                 const Order4 &pRightShifts,
                                 const std::array<std::uint16_t, 4U> &pRightOffsets) {
        for (std::size_t i = 0U; i < kWidth; ++i) {
            d += (pLeftBases[i] != pRightBases[i])
                     ? kBaseDistanceWeight
                     : 0ULL;
            d += (pLeftShifts[i] != pRightShifts[i])
                     ? kShiftDistanceWeight
                     : 0ULL;
            d += (pLeftOffsets[i] != pRightOffsets[i])
                     ? kOffsetDistanceWeight
                     : 0ULL;
        }
    };
    for (std::size_t loop = 0U; loop < 4U; ++loop) {
        CompareRoutedFold(a.mQuarterBases[loop],
                          a.mQuarterShifts[loop],
                          a.mQuarterOffsets[loop],
                          b.mQuarterBases[loop],
                          b.mQuarterShifts[loop],
                          b.mQuarterOffsets[loop]);
        CompareRoutedFold(a.mKeyBases[loop],
                          a.mKeyShifts[loop],
                          a.mKeyOffsets[loop],
                          b.mKeyBases[loop],
                          b.mKeyShifts[loop],
                          b.mKeyOffsets[loop]);
        d += (a.mQuarterDiffuse[loop] != b.mQuarterDiffuse[loop])
                 ? kDiffuseDistanceWeight
                 : 0ULL;
        d += (a.mKeyDiffuse[loop] != b.mKeyDiffuse[loop])
                 ? kDiffuseDistanceWeight
                 : 0ULL;
    }
    for (std::size_t i = 0U; i < kWidth; ++i) {
        d += (a.mFinalShifts[i] != b.mFinalShifts[i])
                 ? kShiftDistanceWeight
                 : 0ULL;
        d += (a.mFinalOffsets[i] != b.mFinalOffsets[i])
                 ? kOffsetDistanceWeight
                 : 0ULL;
    }
    d += (a.mFinalDiffuse != b.mFinalDiffuse) ? kDiffuseDistanceWeight : 0ULL;
    return d;
}

std::uint64_t TotalDistance(const Candidate &pCandidate) {
    const std::uint64_t aCandidateCount =
        static_cast<std::uint64_t>(gFrequencies.mCandidateCount);
    std::uint64_t aTotal = 0ULL;
    auto AddDistance = [&](const std::uint8_t pMatchingCount,
                           const std::uint64_t pWeight) {
        aTotal +=
            (aCandidateCount - static_cast<std::uint64_t>(pMatchingCount)) *
            pWeight;
    };

    for (std::size_t aLoop = 0U; aLoop < 4U; ++aLoop) {
        for (std::size_t i = 0U; i < 4U; ++i) {
            const std::size_t aQuarterField = (aLoop * 4U) + i;
            const std::size_t aKeyField = 16U + aQuarterField;
            AddDistance(
                gFrequencies.mBases[aQuarterField]
                                   [pCandidate.mQuarterBases[aLoop][i]],
                kBaseDistanceWeight);
            AddDistance(
                gFrequencies.mBases[aKeyField]
                                   [pCandidate.mKeyBases[aLoop][i]],
                kBaseDistanceWeight);
            AddDistance(
                gFrequencies.mShifts[aQuarterField]
                                    [pCandidate.mQuarterShifts[aLoop][i]],
                kShiftDistanceWeight);
            AddDistance(
                gFrequencies.mShifts[aKeyField]
                                    [pCandidate.mKeyShifts[aLoop][i]],
                kShiftDistanceWeight);
            AddDistance(
                gFrequencies.mQuarterOffsets[aQuarterField]
                                            [pCandidate.mQuarterOffsets[aLoop][i]],
                kOffsetDistanceWeight);
            AddDistance(
                gFrequencies.mKeyOffsets[aQuarterField]
                                        [pCandidate.mKeyOffsets[aLoop][i]],
                kOffsetDistanceWeight);
        }
        AddDistance(
            gFrequencies.mDiffusers[aLoop][pCandidate.mQuarterDiffuse[aLoop]],
            kDiffuseDistanceWeight);
        AddDistance(
            gFrequencies.mDiffusers[4U + aLoop][pCandidate.mKeyDiffuse[aLoop]],
            kDiffuseDistanceWeight);
    }
    for (std::size_t i = 0U; i < 4U; ++i) {
        AddDistance(gFrequencies.mShifts[32U + i][pCandidate.mFinalShifts[i]],
                    kShiftDistanceWeight);
        AddDistance(gFrequencies.mKeyOffsets[16U + i]
                                            [pCandidate.mFinalOffsets[i]],
                    kOffsetDistanceWeight);
    }
    AddDistance(gFrequencies.mDiffusers[8U][pCandidate.mFinalDiffuse],
                kDiffuseDistanceWeight);
    return aTotal;
}

std::uint64_t MinimumDistance(const Candidate &pCandidate) {
    if (gCandidates.empty()) {
        return std::numeric_limits<std::uint64_t>::max();
    }
    std::uint64_t aMinimum = std::numeric_limits<std::uint64_t>::max();
    for (const Candidate &aExisting : gCandidates) {
        aMinimum = std::min(aMinimum, Distance(pCandidate, aExisting));
    }
    return aMinimum;
}

Score FamilyScore(const Candidate &pCandidate) {
    return {MinimumDistance(pCandidate), TotalDistance(pCandidate)};
}

Score DirectFamilyScore(const Candidate &pCandidate) {
    if (gCandidates.empty()) {
        return {std::numeric_limits<std::uint64_t>::max(), 0ULL};
    }
    Score aScore{std::numeric_limits<std::uint64_t>::max(), 0ULL};
    for (const Candidate &aExisting : gCandidates) {
        const std::uint64_t aDistance = Distance(pCandidate, aExisting);
        aScore.mMinimum = std::min(aScore.mMinimum, aDistance);
        aScore.mTotal += aDistance;
    }
    return aScore;
}

void AddToFrequencies(const Candidate &pCandidate) {
    for (std::size_t aLoop = 0U; aLoop < 4U; ++aLoop) {
        for (std::size_t i = 0U; i < 4U; ++i) {
            const std::size_t aQuarterField = (aLoop * 4U) + i;
            const std::size_t aKeyField = 16U + aQuarterField;
            ++gFrequencies.mBases[aQuarterField]
                                 [pCandidate.mQuarterBases[aLoop][i]];
            ++gFrequencies.mBases[aKeyField]
                                 [pCandidate.mKeyBases[aLoop][i]];
            ++gFrequencies.mShifts[aQuarterField]
                                  [pCandidate.mQuarterShifts[aLoop][i]];
            ++gFrequencies.mShifts[aKeyField]
                                  [pCandidate.mKeyShifts[aLoop][i]];
            ++gFrequencies.mQuarterOffsets[aQuarterField]
                                          [pCandidate.mQuarterOffsets[aLoop][i]];
            ++gFrequencies.mKeyOffsets[aQuarterField]
                                      [pCandidate.mKeyOffsets[aLoop][i]];
        }
        ++gFrequencies.mDiffusers[aLoop][pCandidate.mQuarterDiffuse[aLoop]];
        ++gFrequencies.mDiffusers[4U + aLoop][pCandidate.mKeyDiffuse[aLoop]];
    }
    for (std::size_t i = 0U; i < 4U; ++i) {
        ++gFrequencies.mShifts[32U + i][pCandidate.mFinalShifts[i]];
        ++gFrequencies.mKeyOffsets[16U + i][pCandidate.mFinalOffsets[i]];
    }
    ++gFrequencies.mDiffusers[8U][pCandidate.mFinalDiffuse];
    ++gFrequencies.mCandidateCount;
}

bool Better(const Score &a, const Score &b) {
    return (a.mTotal > b.mTotal) ||
           ((a.mTotal == b.mTotal) && (a.mMinimum > b.mMinimum));
}

Candidate Explore(std::uint64_t pCases, Score *pScore) {
    Candidate aBest = MakeCandidate();
    Score aBestScore = FamilyScore(aBest);
    for (std::uint64_t i = 1ULL; i < pCases; ++i) {
        Candidate aTrial = MakeCandidate();
        const std::uint64_t aTrialTotal = TotalDistance(aTrial);
        if (aTrialTotal < aBestScore.mTotal) { continue; }
        const Score aTrialScore = {MinimumDistance(aTrial), aTrialTotal};
        if (Better(aTrialScore, aBestScore)) {
            aBest = aTrial;
            aBestScore = aTrialScore;
        }
    }
    if (pScore != nullptr) { *pScore = aBestScore; }
    return aBest;
}

const char *Diffuse(std::uint8_t pIndex) {
    static const char *kNames[] = {"DiffuseA", "DiffuseB", "DiffuseC"};
    return kNames[pIndex % 3U];
}

char Letter(std::size_t pIndex) { return static_cast<char>('A' + pIndex); }

void RenderLaneFold(std::ostringstream &s,
                    const char *pSourcePrefix,
                    const char *pDest,
                    const char *pMask,
                    const char *pLength,
                    const Order4 &pBases,
                    const Order4 &pShifts,
                    const std::array<std::uint16_t, 4U> &pOffsets,
                    std::uint8_t pDiffuse) {
    s << "    {\n";
    for (std::size_t i = 0U; i < 4U; ++i) {
        s << "        const std::size_t aFoldBase" << Letter(i) << " = "
          << static_cast<unsigned>(pBases[i]) << "U * " << pLength << ";\n";
    }
    s << "        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(" << pLength << "); aIndex += 1U) {\n";
    for (std::size_t i = 0U; i < 4U; ++i) {
        s << "            const std::size_t aFoldIndex" << Letter(i) << " = aFoldBase" << Letter(i)
          << " + ((aIndex + " << pOffsets[i] << "U) & " << pMask << ");\n";
    }
    s << "            std::uint32_t aFoldWord =\n";
    for (std::size_t i = 0U; i < 4U; i += 2U) {
        s << "                (static_cast<std::uint32_t>(" << pSourcePrefix
          << Letter(i) << "[aFoldIndex" << Letter(i) << "]) << "
          << (static_cast<unsigned>(pShifts[i]) * 8U)
          << "U) | (static_cast<std::uint32_t>(" << pSourcePrefix
          << Letter(i + 1U) << "[aFoldIndex" << Letter(i + 1U) << "]) << "
          << (static_cast<unsigned>(pShifts[i + 1U]) * 8U) << "U)"
          << (i == 2U ? ";\n" : " |\n");
    }
    s << "            aFoldWord = TwistMix32::" << Diffuse(pDiffuse) << "(aFoldWord);\n"
      << "            " << pDest << "[aIndex] = aFoldWord;\n"
      << "        }\n    }\n";
}

std::string Render(const Candidate &c, std::size_t pIndex, const Score &pScore, std::uint64_t pCases) {
    std::ostringstream s;
    s << "// GrowB candidate " << (pIndex + 1U) << " of 33\n"
      << "// Exploration cases: " << pCases << "\n";
    if (pIndex == 0U) s << "// Total structural distance: baseline candidate\n";
    else s << "// Total structural distance from earlier candidates: "
           << pScore.mTotal << "; nearest pair: " << pScore.mMinimum
           << " / " << kMaximumPairDistance << "\n";
    s << "void TwistExpander_" << kNames[pIndex] << "::GrowKeyB(TwistWorkSpace *pWorkSpace) {\n"
      << "    if (pWorkSpace == nullptr) { return; }\n"
      << "    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;\n"
      << "    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;\n"
      << "    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;\n"
      << "    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;\n"
      << "    std::uint8_t *aScrapLaneA = pWorkSpace->mScrapLaneA;\n"
      << "    std::uint8_t *aScrapLaneB = pWorkSpace->mScrapLaneB;\n"
      << "    std::uint8_t *aScrapLaneC = pWorkSpace->mScrapLaneC;\n"
      << "    std::uint8_t *aScrapLaneD = pWorkSpace->mScrapLaneD;\n"
      << "    std::uint8_t *aMergeLaneA = pWorkSpace->mMergeLaneA;\n"
      << "    std::uint8_t *aMergeLaneB = pWorkSpace->mMergeLaneB;\n"
      << "    std::uint8_t *aMergeLaneC = pWorkSpace->mMergeLaneC;\n"
      << "    std::uint8_t *aMergeLaneD = pWorkSpace->mMergeLaneD;\n"
      << "    std::uint8_t *aKeyRowWriteB = &(pWorkSpace->mKeyBoxB[0][0]);\n"
      << "    static_assert((S_BLOCK / S_QUARTER) == 4, \"GrowKeyB expects four work-lane quarters.\");\n"
      << "    static_assert((S_QUARTER / W_KEY) == 4, \"GrowKeyB expects four key chunks per quarter.\");\n"
      << "    TwistShiftBox::ShiftKeyBoxB(pWorkSpace);\n";

    for (std::size_t loop = 0U; loop < 4U; ++loop) {
        const std::string aDestination =
            std::string("aScrapLane") + Letter(loop);
        RenderLaneFold(s,
                       "aWorkLane",
                       aDestination.c_str(),
                       "S_QUARTER1",
                       "S_QUARTER",
                       c.mQuarterBases[loop],
                       c.mQuarterShifts[loop],
                       c.mQuarterOffsets[loop],
                       c.mQuarterDiffuse[loop]);
    }
    for (std::size_t loop = 0U; loop < 4U; ++loop) {
        const std::string aDestination =
            std::string("aMergeLane") + Letter(loop);
        RenderLaneFold(s,
                       "aScrapLane",
                       aDestination.c_str(),
                       "W_KEY1",
                       "W_KEY",
                       c.mKeyBases[loop],
                       c.mKeyShifts[loop],
                       c.mKeyOffsets[loop],
                       c.mKeyDiffuse[loop]);
    }

    s << "    {\n        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {\n";
    for (std::size_t i = 0U; i < 4U; ++i) {
        s << "            const std::size_t aFoldIndex" << Letter(i) << " = (aIndex + "
          << c.mFinalOffsets[i] << "U) & W_KEY1;\n";
    }
    s << "            std::uint32_t aFoldWord =\n";
    for (std::size_t i = 0U; i < 4U; i += 2U) {
        s << "                (static_cast<std::uint32_t>(aMergeLane" << Letter(i)
          << "[aFoldIndex" << Letter(i) << "]) << " << (static_cast<unsigned>(c.mFinalShifts[i]) * 8U) << "U) | "
          << "(static_cast<std::uint32_t>(aMergeLane" << Letter(i + 1U)
          << "[aFoldIndex" << Letter(i + 1U) << "]) << " << (static_cast<unsigned>(c.mFinalShifts[i + 1U]) * 8U) << "U)"
          << (i == 2U ? ";\n" : " |\n");
    }
    s << "            aFoldWord = TwistMix32::" << Diffuse(c.mFinalDiffuse) << "(aFoldWord);\n"
      << "            aKeyRowWriteB[aIndex] = aFoldWord;\n        }\n    }\n}\n";
    return s.str();
}

} // namespace

void GrowBControl::Reset(std::uint64_t pSeed) {
    gCandidates.clear(); gRendered.clear();
    gFrequencies = FrequencyTable{};
    gRandomState = pSeed == 0ULL ? 0x47524F57425F3333ULL : pSeed;
    const std::uint64_t aMaximumResidueCount =
        static_cast<std::uint64_t>(std::numeric_limits<std::uint16_t>::max()) + 1ULL;
    if ((static_cast<std::uint64_t>(S_QUARTER) > aMaximumResidueCount) ||
        (static_cast<std::uint64_t>(W_KEY) > aMaximumResidueCount) ||
        (static_cast<std::size_t>(S_QUARTER) < kQuarterOffsetCount) ||
        (static_cast<std::size_t>(W_KEY) < kKeyOffsetCount)) {
        std::abort();
    }
    for (std::vector<std::uint8_t> &aCounts :
         gFrequencies.mQuarterOffsets) {
        aCounts.assign(static_cast<std::size_t>(S_QUARTER), 0U);
    }
    for (std::vector<std::uint8_t> &aCounts : gFrequencies.mKeyOffsets) {
        aCounts.assign(static_cast<std::size_t>(W_KEY), 0U);
    }
    gDidReset = true;
}

std::string GrowBControl::Generate(std::uint64_t pExplorationCases) {
    if (!gDidReset || gCandidates.size() >= kCandidateCount) std::abort();
    const std::uint64_t aCases =
        std::max<std::uint64_t>(1ULL, pExplorationCases);
    Score aScore;
    Candidate aCandidate = Explore(aCases, &aScore);
    const Score aDirectScore = DirectFamilyScore(aCandidate);
    if ((aScore.mMinimum != aDirectScore.mMinimum) ||
        (aScore.mTotal != aDirectScore.mTotal)) {
        std::abort();
    }
    const std::size_t aIndex = gCandidates.size();
    AddToFrequencies(aCandidate);
    gCandidates.push_back(aCandidate);
    gRendered.push_back(Render(aCandidate, aIndex, aScore, aCases));
    return gRendered.back();
}

void GrowBControl::Print() {
    for (const std::string &aText : gRendered) std::printf("%s\n", aText.c_str());
}

bool GrowBControl::SavePreview(const std::string &pPath, std::string *pErrorMessage) {
    const std::string aPath = FileIO::ProjectRoot(pPath);
    std::ostringstream combined;
    for (const std::string &text : gRendered) combined << text << '\n';
    const std::string all = combined.str();
    if (!FileIO::Save(aPath, std::vector<std::uint8_t>(all.begin(), all.end()))) {
        if (pErrorMessage) *pErrorMessage = "GrowBControl failed to save " + aPath;
        return false;
    }
    const std::string folder = std::filesystem::path(aPath).parent_path().generic_string();
    for (std::size_t i = 0U; i < gRendered.size(); ++i) {
        char name[48]; std::snprintf(name, sizeof(name), "GrowKeyB_Candidate%02zu.cpp", i + 1U);
        const std::string path = FileIO::Join(folder, name);
        const std::string &text = gRendered[i];
        if (!FileIO::Save(path, std::vector<std::uint8_t>(text.begin(), text.end()))) return false;
    }
    return true;
}
