//
//  SmartSquashControl.cpp
//  MeanMachine
//
//  Created by icarus black on 7/10/26.
//

#include "SmartSquashControl.hpp"
#include "FileIO.hpp"
#include "Library - Twist/TwistWorkSpace.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <limits>
#include <sstream>
#include <vector>

namespace {

constexpr std::size_t kRows = 16U;
constexpr std::size_t kLanes = 8U;
constexpr std::size_t kOffsetsPerCandidate = kRows * kLanes;
constexpr std::uint64_t kChunkDistanceWeight = 6ULL;
constexpr std::uint64_t kShiftDistanceWeight = 5ULL;
constexpr std::uint64_t kOffsetDistanceWeight = 3ULL;
constexpr std::uint64_t kDiffuseDistanceWeight = 12ULL;
constexpr std::uint64_t kMaximumPairDistance =
    static_cast<std::uint64_t>(kRows) *
    ((static_cast<std::uint64_t>(kLanes) *
      (kChunkDistanceWeight + kShiftDistanceWeight + kOffsetDistanceWeight)) +
     kDiffuseDistanceWeight);

constexpr std::array<const char *, 33U> kCandidateNames = {
    "Achernar", "Alcor", "Aldebaran", "Alioth", "Alkaid", "Alnitak",
    "Altair", "Ankaa", "Antares", "Arcturus", "Athebyne", "Bellatrix",
    "Betelgeuse", "Canopus", "Capella", "Castor", "Mebsuta", "Menkent",
    "Mimosa", "Miram", "Mirfak", "Mothallah", "Naos", "Polaris",
    "Pollux", "Procyon", "Regulus", "Gemma", "Rigel", "Saiph",
    "Sirius", "Suhail", "Vega"
};

using Order8 = std::array<std::uint8_t, kLanes>;
using Order16 = std::array<std::uint8_t, kRows>;

struct Candidate {
    // Lane identity is implicit: element 0...7 always means invest lane A...H.
    std::array<Order16, kLanes> mChunkOrder{};
    std::array<Order8, kRows> mShiftOrder{};
    std::array<std::array<std::uint16_t, kLanes>, kRows> mOffsetResidue{};
    std::array<std::uint8_t, kRows> mDiffuse{};
};

struct Score {
    std::uint64_t mMinimumDistance = 0ULL;
    std::uint64_t mTotalDistance = 0ULL;
};

std::vector<Candidate> gCandidates;
std::vector<std::string> gRenderedCandidates;
std::uint64_t gRandomState = 0x534D415254535153ULL;
bool gDidReset = false;
std::vector<std::uint16_t> gOffsetPool;

std::uint64_t NextRandom() {
    gRandomState += 0x9E3779B97F4A7C15ULL;
    std::uint64_t aValue = gRandomState;
    aValue = (aValue ^ (aValue >> 30U)) * 0xBF58476D1CE4E5B9ULL;
    aValue = (aValue ^ (aValue >> 27U)) * 0x94D049BB133111EBULL;
    return aValue ^ (aValue >> 31U);
}

std::size_t RandomIndex(const std::size_t pLimit) {
    return (pLimit == 0U) ? 0U : static_cast<std::size_t>(NextRandom() % pLimit);
}

template <typename T, std::size_t Count>
void Shuffle(std::array<T, Count> *pValues) {
    for (std::size_t i = Count; i > 1U; --i) {
        std::swap((*pValues)[i - 1U], (*pValues)[RandomIndex(i)]);
    }
}

template <typename T>
void Shuffle(std::vector<T> *pValues) {
    for (std::size_t i = pValues->size(); i > 1U; --i) {
        std::swap((*pValues)[i - 1U], (*pValues)[RandomIndex(i)]);
    }
}

template <std::size_t Count>
std::array<std::uint8_t, Count> IdentityOrder() {
    std::array<std::uint8_t, Count> aResult{};
    for (std::size_t i = 0U; i < Count; ++i) {
        aResult[i] = static_cast<std::uint8_t>(i);
    }
    return aResult;
}

Candidate MakeRandomCandidate() {
    Candidate aCandidate;

    for (Order16 &aOrder : aCandidate.mChunkOrder) {
        aOrder = IdentityOrder<kRows>();
        Shuffle(&aOrder);
    }
    for (Order8 &aOrder : aCandidate.mShiftOrder) {
        aOrder = IdentityOrder<kLanes>();
        Shuffle(&aOrder);
    }

    if (gOffsetPool.size() < kOffsetsPerCandidate) {
        std::fprintf(stderr, "fatal: SmartSquashControl exhausted its index-offset pool\n");
        std::abort();
    }
    // The emitted lookup masks with W_KEY1, so retain only effective residues.
    std::vector<std::uint16_t> aOffsetChoices = gOffsetPool;
    Shuffle(&aOffsetChoices);
    std::array<std::uint16_t, kOffsetsPerCandidate> aOffsets{};
    for (std::size_t i = 0U; i < aOffsets.size(); ++i) {
        aOffsets[i] = aOffsetChoices[i];
    }
    std::size_t aOffsetIndex = 0U;
    for (auto &aRow : aCandidate.mOffsetResidue) {
        for (std::uint16_t &aOffset : aRow) {
            aOffset = aOffsets[aOffsetIndex++];
        }
    }

    // Across 16 rows this gives a balanced 6/5/5 use of A/B/C.
    for (std::size_t i = 0U; i < kRows; ++i) {
        aCandidate.mDiffuse[i] = static_cast<std::uint8_t>(i % 3U);
    }
    Shuffle(&aCandidate.mDiffuse);
    return aCandidate;
}

std::uint64_t Distance(const Candidate &pLeft,
                       const Candidate &pRight) {
    std::uint64_t aDistance = 0ULL;
    for (std::size_t aRow = 0U; aRow < kRows; ++aRow) {
        // Compare the operation assigned to the same fixed lane on both sides.
        for (std::size_t aLane = 0U; aLane < kLanes; ++aLane) {
            aDistance += (pLeft.mChunkOrder[aLane][aRow] !=
                          pRight.mChunkOrder[aLane][aRow]) ? kChunkDistanceWeight : 0ULL;
            aDistance += (pLeft.mShiftOrder[aRow][aLane] !=
                          pRight.mShiftOrder[aRow][aLane]) ? kShiftDistanceWeight : 0ULL;
            aDistance += (pLeft.mOffsetResidue[aRow][aLane] !=
                          pRight.mOffsetResidue[aRow][aLane]) ? kOffsetDistanceWeight : 0ULL;
        }
        aDistance += (pLeft.mDiffuse[aRow] != pRight.mDiffuse[aRow])
                         ? kDiffuseDistanceWeight
                         : 0ULL;
    }
    return aDistance;
}

Score FamilyScore(const Candidate &pCandidate) {
    if (gCandidates.empty()) {
        return {std::numeric_limits<std::uint64_t>::max(), 0ULL};
    }

    Score aScore{std::numeric_limits<std::uint64_t>::max(), 0ULL};
    for (const Candidate &aExisting : gCandidates) {
        const std::uint64_t aDistance = Distance(pCandidate, aExisting);
        aScore.mMinimumDistance = std::min(aScore.mMinimumDistance, aDistance);
        aScore.mTotalDistance += aDistance;
    }
    return aScore;
}

bool IsBetter(const Score &pLeft, const Score &pRight) {
    return (pLeft.mMinimumDistance > pRight.mMinimumDistance) ||
           ((pLeft.mMinimumDistance == pRight.mMinimumDistance) &&
            (pLeft.mTotalDistance > pRight.mTotalDistance));
}

void Mutate(Candidate *pCandidate) {
    const std::size_t aKind = RandomIndex(5U);
    const std::size_t aRow = RandomIndex(kRows);
    const std::size_t aA = RandomIndex(kLanes);
    std::size_t aB = RandomIndex(kLanes - 1U);
    if (aB >= aA) { ++aB; }

    if (aKind == 0U) {
        const std::size_t aLane = RandomIndex(kLanes);
        std::size_t aOtherRow = RandomIndex(kRows - 1U);
        if (aOtherRow >= aRow) { ++aOtherRow; }
        std::swap(pCandidate->mChunkOrder[aLane][aRow],
                  pCandidate->mChunkOrder[aLane][aOtherRow]);
    } else if (aKind == 1U) {
        std::swap(pCandidate->mShiftOrder[aRow][aA], pCandidate->mShiftOrder[aRow][aB]);
    } else if (aKind == 2U) {
        std::swap(pCandidate->mOffsetResidue[aRow][aA],
                  pCandidate->mOffsetResidue[aRow][aB]);
    } else if (aKind == 3U) {
        const std::size_t aOtherRow = RandomIndex(kRows);
        const std::size_t aOtherFragment = RandomIndex(kLanes);
        std::swap(pCandidate->mOffsetResidue[aRow][aA],
                  pCandidate->mOffsetResidue[aOtherRow][aOtherFragment]);
    } else {
        std::size_t aOtherRow = RandomIndex(kRows - 1U);
        if (aOtherRow >= aRow) { ++aOtherRow; }
        std::swap(pCandidate->mDiffuse[aRow], pCandidate->mDiffuse[aOtherRow]);
    }
}

Candidate Explore(const std::uint64_t pCases) {
    Candidate aBest = MakeRandomCandidate();
    Score aBestScore = FamilyScore(aBest);

    for (std::uint64_t aCase = 1ULL; aCase < pCases; ++aCase) {
        Candidate aTrial;
        if ((aCase & 0x0FFFULL) == 0ULL) {
            aTrial = MakeRandomCandidate();
        } else {
            aTrial = aBest;
            Mutate(&aTrial);
        }
        const Score aTrialScore = FamilyScore(aTrial);
        if (IsBetter(aTrialScore, aBestScore)) {
            aBest = aTrial;
            aBestScore = aTrialScore;
        }
    }
    return aBest;
}

char FragmentName(const std::size_t pFragment) {
    return static_cast<char>('A' + pFragment);
}

std::uint32_t OffsetLiteral(const Candidate &pCandidate,
                            const std::size_t pRow,
                            const std::size_t pFragment) {
    return pCandidate.mOffsetResidue[pRow][pFragment];
}

std::string Render(const Candidate &pCandidate,
                   const std::size_t pCandidateIndex,
                   const Score &pScore,
                   const std::uint64_t pExplorationCases) {
    static const char *kDiffuseNames[3] = {"DiffuseA", "DiffuseB", "DiffuseC"};
    std::ostringstream aStream;
    aStream << "// SmartSquash candidate " << (pCandidateIndex + 1U) << " of 33\n"
            << "// Exploration cases: " << pExplorationCases << "\n";
    if (pCandidateIndex == 0U) {
        aStream << "// Diversity score: baseline candidate (no earlier family member)\n";
    } else {
        const double aPercentage =
            (100.0 * static_cast<double>(pScore.mMinimumDistance)) /
            static_cast<double>(kMaximumPairDistance);
        aStream << "// Nearest-family diversity: " << pScore.mMinimumDistance
                << " / " << kMaximumPairDistance << " ("
                << std::fixed << std::setprecision(2) << aPercentage << "%)\n"
                << "// Total distance from earlier candidates: " << pScore.mTotalDistance << "\n";
    }
    aStream << "void TwistExpander_" << kCandidateNames[pCandidateIndex]
            << "::SquashInvestToKeyBoxes() {\n"
            << "    static_assert((S_BLOCK / W_KEY) == 16, \"SquashInvestToKeyBoxes expects 16 invest fragments.\");\n"
            << "    static_assert(H_KEY == 8, \"SquashInvestToKeyBoxes expects 8 key rows per box.\");\n"
            << "    if (mWorkspace == nullptr) { return; }\n"
            << "    std::uint8_t *aInvestLaneA = mWorkspace->mInvestLaneA;\n"
            << "    std::uint8_t *aInvestLaneB = mWorkspace->mInvestLaneB;\n"
            << "    std::uint8_t *aInvestLaneC = mWorkspace->mInvestLaneC;\n"
            << "    std::uint8_t *aInvestLaneD = mWorkspace->mInvestLaneD;\n"
            << "    std::uint8_t *aInvestLaneE = mWorkspace->mInvestLaneE;\n"
            << "    std::uint8_t *aInvestLaneF = mWorkspace->mInvestLaneF;\n"
            << "    std::uint8_t *aInvestLaneG = mWorkspace->mInvestLaneG;\n"
            << "    std::uint8_t *aInvestLaneH = mWorkspace->mInvestLaneH;\n";

    for (std::size_t aRow = 0U; aRow < kRows; ++aRow) {
        const char aBox = (aRow < 8U) ? 'A' : 'B';
        const std::size_t aBoxRow = aRow & 7U;
        aStream << "\n    {\n";
        for (std::size_t aFragment = 0U; aFragment < kLanes; aFragment += 2U) {
            aStream << "        std::uint8_t *aFragment" << FragmentName(aFragment)
                    << " = aInvestLane" << FragmentName(aFragment)
                    << " + (W_KEY * " << static_cast<unsigned>(pCandidate.mChunkOrder[aFragment][aRow]) << "U), *aFragment"
                    << FragmentName(aFragment + 1U) << " = aInvestLane" << FragmentName(aFragment + 1U)
                    << " + (W_KEY * " << static_cast<unsigned>(pCandidate.mChunkOrder[aFragment + 1U][aRow]) << "U);\n";
        }
        aStream << "        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBox" << aBox
                << "[" << aBoxRow << "][0]);\n"
                << "        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {\n"
                << "            std::uint64_t aSquash =\n";
        for (std::size_t aFragment = 0U; aFragment < kLanes; aFragment += 2U) {
            const std::uint32_t aOffsetA = OffsetLiteral(pCandidate, aRow, aFragment);
            const std::uint32_t aOffsetB = OffsetLiteral(pCandidate, aRow, aFragment + 1U);
            aStream << "                (static_cast<std::uint64_t>(aFragment" << FragmentName(aFragment)
                    << "[((aIndex + " << aOffsetA << "U) & W_KEY1)]) << "
                    << (static_cast<unsigned>(pCandidate.mShiftOrder[aRow][aFragment]) * 8U) << "U) | "
                    << "(static_cast<std::uint64_t>(aFragment" << FragmentName(aFragment + 1U)
                    << "[((aIndex + " << aOffsetB << "U) & W_KEY1)]) << "
                    << (static_cast<unsigned>(pCandidate.mShiftOrder[aRow][aFragment + 1U]) * 8U) << "U)"
                    << ((aFragment == 6U) ? ";\n" : " |\n");
        }
        aStream << "            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::"
                << kDiffuseNames[pCandidate.mDiffuse[aRow]] << "(aSquash));\n"
                << "        }\n"
                << "    }\n";
    }
    aStream << "}\n";
    return aStream.str();
}

} // namespace

void SmartSquashControl::Reset(const std::uint64_t pSeed) {
    gCandidates.clear();
    gRenderedCandidates.clear();
    gRandomState = (pSeed == 0ULL) ? 0x534D415254535153ULL : pSeed;
    gOffsetPool.clear();
    const std::uint64_t aResidueCount = static_cast<std::uint64_t>(W_KEY);
    const std::uint64_t aMaximumResidueCount =
        static_cast<std::uint64_t>(std::numeric_limits<std::uint16_t>::max()) + 1ULL;
    if ((aResidueCount < kOffsetsPerCandidate) ||
        (aResidueCount > aMaximumResidueCount)) {
        std::fprintf(stderr, "fatal: SmartSquashControl cannot represent W_KEY residues\n");
        std::abort();
    }
    for (std::uint64_t aResidue = 0ULL; aResidue < aResidueCount; ++aResidue) {
        gOffsetPool.push_back(static_cast<std::uint16_t>(aResidue));
    }
    gDidReset = true;
}

std::string SmartSquashControl::GenerateSquashInvestToKeyBoxes(
    const std::uint64_t pExplorationCases) {
    if (!gDidReset) {
        std::fprintf(stderr, "fatal: SmartSquashControl::Reset must be called first\n");
        std::abort();
    }
    if (gCandidates.size() >= kCandidateCount) {
        std::fprintf(stderr, "fatal: SmartSquashControl exceeded 33 candidates\n");
        std::abort();
    }

    Candidate aCandidate = Explore(std::max<std::uint64_t>(1ULL, pExplorationCases));
    const std::size_t aCandidateIndex = gCandidates.size();
    const Score aScore = FamilyScore(aCandidate);
    gCandidates.push_back(aCandidate);
    gRenderedCandidates.push_back(Render(aCandidate,
                                         aCandidateIndex,
                                         aScore,
                                         std::max<std::uint64_t>(1ULL, pExplorationCases)));
    return gRenderedCandidates.back();
}

void SmartSquashControl::Print() {
    for (const std::string &aCandidate : gRenderedCandidates) {
        std::printf("%s\n", aCandidate.c_str());
    }
}

bool SmartSquashControl::SavePreview(const std::string &pPath,
                                     std::string *pErrorMessage) {
    const std::string aOutputPath = FileIO::ProjectRoot(pPath);
    std::ostringstream aCombined;
    aCombined << "// Preview only. Generated by SmartSquashControl.\n"
              << "// Complete SquashInvestToKeyBoxes replacement for each candidate.\n"
              << "// Each numbered file is a clean replacement; this combined file contains duplicates for comparison.\n"
              << "// Candidates: " << gRenderedCandidates.size() << " / 33\n\n";
    for (const std::string &aCandidate : gRenderedCandidates) {
        aCombined << aCandidate << '\n';
    }

    const std::string aCombinedText = aCombined.str();
    if (!FileIO::Save(aOutputPath,
                      std::vector<std::uint8_t>(aCombinedText.begin(), aCombinedText.end()))) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "SmartSquashControl failed to save " + aOutputPath;
        }
        return false;
    }

    const std::filesystem::path aCombinedPath(aOutputPath);
    const std::string aCandidateFolder = aCombinedPath.parent_path().generic_string();
    for (std::size_t i = 0U; i < gRenderedCandidates.size(); ++i) {
        std::ostringstream aFileName;
        aFileName << "SquashInvestToKeyBoxes_Candidate"
                  << (i < 9U ? "0" : "") << (i + 1U) << ".cpp";
        const std::string aCandidatePath = FileIO::Join(aCandidateFolder, aFileName.str());
        const std::string &aCandidateText = gRenderedCandidates[i];
        if (!FileIO::Save(aCandidatePath,
                          std::vector<std::uint8_t>(aCandidateText.begin(), aCandidateText.end()))) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "SmartSquashControl failed to save " + aCandidatePath;
            }
            return false;
        }
    }
    return true;
}

std::size_t SmartSquashControl::GeneratedCount() {
    return gCandidates.size();
}
