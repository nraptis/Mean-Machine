//
//  LoopHeadFarmer.cpp
//  MeanMachine
//

#include "LoopHeadFarmer.hpp"

#include "FileIO.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdio>
#include <filesystem>
#include <limits>
#include <numeric>
#include <vector>

namespace {

constexpr std::array<std::uint32_t, 12U> kFactorials = {
    1U,
    1U,
    2U,
    6U,
    24U,
    120U,
    720U,
    5'040U,
    40'320U,
    362'880U,
    3'628'800U,
    39'916'800U,
};

constexpr std::array<std::uint8_t, 8U> kFileMagic = {
    'M', 'M', 'H', 'E', 'A', 'D', '1', '1',
};
constexpr std::uint32_t kFileVersion = 1U;
constexpr std::size_t kFileHeaderByteCount = 32U;
constexpr std::size_t kFilePatternByteCount = 20U;
std::string ResolvedPath(const std::string &pPath) {
    const std::filesystem::path aPath(pPath);
    return aPath.is_absolute()
        ? aPath.lexically_normal().generic_string()
        : FileIO::ProjectRoot(pPath);
}

std::uint64_t Mix64(std::uint64_t pValue) {
    pValue ^= pValue >> 30U;
    pValue *= 0xBF58476D1CE4E5B9ULL;
    pValue ^= pValue >> 27U;
    pValue *= 0x94D049BB133111EBULL;
    return pValue ^ (pValue >> 31U);
}

std::uint8_t KeyDistance(const std::uint64_t pA,
                         const std::uint64_t pB) {
    std::uint64_t aDifference = pA ^ pB;
    aDifference |= aDifference >> 1U;
    aDifference |= aDifference >> 2U;
    aDifference &= 0x11111111111ULL;
    return static_cast<std::uint8_t>(
        __builtin_popcountll(aDifference));
}

std::uint32_t RankUnchecked(const LoopHeadPattern11 &pPattern) {
    std::uint32_t aRank = 0U;
    std::uint16_t aUsed = 0U;
    for (std::size_t i = 0U;
         i < LoopHeadFarmer::kRoleCount;
         ++i) {
        const std::uint8_t aValue =
            pPattern.mWandererForOrbiter[i];
        const std::uint16_t aSmallerMask =
            static_cast<std::uint16_t>((1U << aValue) - 1U);
        const std::uint32_t aSmallerUnused =
            static_cast<std::uint32_t>(__builtin_popcount(
                static_cast<unsigned int>(aSmallerMask & ~aUsed)));
        aRank += aSmallerUnused *
            kFactorials[LoopHeadFarmer::kRoleCount - 1U - i];
        aUsed = static_cast<std::uint16_t>(aUsed | (1U << aValue));
    }
    return aRank;
}

void SetError(std::string *pErrorMessage,
              const std::string &pText) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pText;
    }
}

void PrintPattern(const LoopHeadPattern11 &pPattern,
                  const std::uint32_t pRank) {
    std::printf("Loop head rank %u: { ", pRank);
    for (std::size_t i = 0U;
         i < pPattern.mWandererForOrbiter.size();
         ++i) {
        std::printf("%c<-%c%s",
                    static_cast<char>('A' + i),
                    static_cast<char>(
                        'A' + pPattern.mWandererForOrbiter[i]),
                    (i + 1U) == pPattern.mWandererForOrbiter.size()
                        ? ""
                        : ", ");
    }
    std::printf(" }\n");
}

} // namespace

LoopHeadPattern11 LoopHeadFarmer::Identity() {
    LoopHeadPattern11 aPattern;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aPattern.mWandererForOrbiter[i] =
            static_cast<std::uint8_t>(i);
    }
    aPattern.mPermutationRank = 0U;
    return aPattern;
}

bool LoopHeadFarmer::IsValid(const LoopHeadPattern11 &pPattern) {
    std::array<bool, kRoleCount> aSeen{};
    for (const std::uint8_t aWanderer :
         pPattern.mWandererForOrbiter) {
        if ((aWanderer >= kRoleCount) || aSeen[aWanderer]) {
            return false;
        }
        aSeen[aWanderer] = true;
    }
    return true;
}

std::uint64_t LoopHeadFarmer::PackedKey(
    const LoopHeadPattern11 &pPattern) {
    std::uint64_t aKey = 0ULL;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aKey |= static_cast<std::uint64_t>(
                    pPattern.mWandererForOrbiter[i])
                << (i * 4U);
    }
    return aKey;
}

std::uint32_t LoopHeadFarmer::Rank(
    const LoopHeadPattern11 &pPattern) {
    if (!IsValid(pPattern)) {
        return std::numeric_limits<std::uint32_t>::max();
    }
    return RankUnchecked(pPattern);
}

LoopHeadPattern11 LoopHeadFarmer::PatternForRank(
    std::uint32_t pRank) {
    LoopHeadPattern11 aPattern;
    if (pRank >= kPermutationCount) {
        aPattern.mWandererForOrbiter.fill(0xFFU);
        return aPattern;
    }

    std::array<std::uint8_t, kRoleCount> aAvailable{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aAvailable[i] = static_cast<std::uint8_t>(i);
    }

    std::size_t aAvailableCount = kRoleCount;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::uint32_t aFactorial =
            kFactorials[kRoleCount - 1U - i];
        const std::size_t aDigit =
            static_cast<std::size_t>(pRank / aFactorial);
        pRank %= aFactorial;
        aPattern.mWandererForOrbiter[i] = aAvailable[aDigit];
        for (std::size_t j = aDigit; j + 1U < aAvailableCount; ++j) {
            aAvailable[j] = aAvailable[j + 1U];
        }
        --aAvailableCount;
    }
    aPattern.mPermutationRank =
        RankUnchecked(aPattern);
    return aPattern;
}

bool LoopHeadFarmer::Survey(const std::uint64_t pPermutationLimit,
                            std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    const std::uint64_t aLimit = pPermutationLimit == 0ULL
        ? static_cast<std::uint64_t>(kPermutationCount)
        : std::min<std::uint64_t>(pPermutationLimit,
                                  kPermutationCount);
    if (aLimit == 0ULL) {
        SetError(pErrorMessage,
                 "Loop head survey received an empty permutation limit");
        return false;
    }

    LoopHeadPattern11 aPattern = Identity();
    std::uint64_t aChecksum = 0xCBF29CE484222325ULL;
    const std::uint64_t aProgressInterval =
        std::max<std::uint64_t>(1ULL, aLimit / 20ULL);
    std::uint64_t aNextProgress = aProgressInterval;
    const auto aStart = std::chrono::steady_clock::now();

    std::printf("Loop head survey: walking %llu of %u permutations\n",
                static_cast<unsigned long long>(aLimit),
                kPermutationCount);
    for (std::uint64_t i = 0ULL; i < aLimit; ++i) {
        if (i < 5ULL) {
            PrintPattern(aPattern, static_cast<std::uint32_t>(i));
        }

        aChecksum ^= PackedKey(aPattern);
        aChecksum *= 0x100000001B3ULL;

        if ((i + 1ULL) >= aNextProgress) {
            const double aSeconds = std::chrono::duration<double>(
                std::chrono::steady_clock::now() - aStart).count();
            std::printf("loop head survey %llu/%llu rate=%.0f/s\n",
                        static_cast<unsigned long long>(i + 1ULL),
                        static_cast<unsigned long long>(aLimit),
                        static_cast<double>(i + 1ULL) /
                            std::max(0.001, aSeconds));
            aNextProgress += aProgressInterval;
        }

        if ((i + 1ULL) < aLimit &&
            !std::next_permutation(
                aPattern.mWandererForOrbiter.begin(),
                aPattern.mWandererForOrbiter.end())) {
            SetError(pErrorMessage,
                     "Loop head survey exhausted permutations early");
            return false;
        }
    }

    const LoopHeadPattern11 aLast =
        PatternForRank(static_cast<std::uint32_t>(aLimit - 1ULL));
    if (aLast.mWandererForOrbiter !=
        aPattern.mWandererForOrbiter) {
        SetError(pErrorMessage,
                 "Loop head rank/unrank did not match lexicographic "
                 "enumeration");
        return false;
    }

    const double aSeconds = std::chrono::duration<double>(
        std::chrono::steady_clock::now() - aStart).count();
    std::printf("Loop head survey complete: count=%llu elapsed=%.3fs "
                "checksum=%016llX\n",
                static_cast<unsigned long long>(aLimit),
                aSeconds,
                static_cast<unsigned long long>(aChecksum));
    return true;
}

namespace {

class RankBitSet {
public:
    RankBitSet()
        : mWords((LoopHeadFarmer::kPermutationCount + 63U) / 64U,
                 0ULL) {
    }

    bool Contains(const std::uint32_t pRank) const {
        return (mWords[pRank >> 6U] &
                (1ULL << (pRank & 63U))) != 0ULL;
    }

    void Add(const std::uint32_t pRank) {
        mWords[pRank >> 6U] |= 1ULL << (pRank & 63U);
    }

private:
    std::vector<std::uint64_t> mWords;
};

void MarkForbiddenNeighborhood(const LoopHeadPattern11 &pPattern,
                               RankBitSet *pForbidden) {
    pForbidden->Add(RankUnchecked(pPattern));

    // Exact Hamming distance 2: one transposition.
    for (std::size_t a = 0U; a < LoopHeadFarmer::kRoleCount; ++a) {
        for (std::size_t b = a + 1U;
             b < LoopHeadFarmer::kRoleCount;
             ++b) {
            LoopHeadPattern11 aNeighbor = pPattern;
            std::swap(aNeighbor.mWandererForOrbiter[a],
                      aNeighbor.mWandererForOrbiter[b]);
            pForbidden->Add(RankUnchecked(aNeighbor));
        }
    }

    // Exact Hamming distance 3: the two orientations of a 3-cycle.
    for (std::size_t a = 0U; a < LoopHeadFarmer::kRoleCount; ++a) {
        for (std::size_t b = a + 1U;
             b < LoopHeadFarmer::kRoleCount;
             ++b) {
            for (std::size_t c = b + 1U;
                 c < LoopHeadFarmer::kRoleCount;
                 ++c) {
                LoopHeadPattern11 aForward = pPattern;
                aForward.mWandererForOrbiter[a] =
                    pPattern.mWandererForOrbiter[b];
                aForward.mWandererForOrbiter[b] =
                    pPattern.mWandererForOrbiter[c];
                aForward.mWandererForOrbiter[c] =
                    pPattern.mWandererForOrbiter[a];
                pForbidden->Add(RankUnchecked(aForward));

                LoopHeadPattern11 aBackward = pPattern;
                aBackward.mWandererForOrbiter[a] =
                    pPattern.mWandererForOrbiter[c];
                aBackward.mWandererForOrbiter[b] =
                    pPattern.mWandererForOrbiter[a];
                aBackward.mWandererForOrbiter[c] =
                    pPattern.mWandererForOrbiter[b];
                pForbidden->Add(RankUnchecked(aBackward));
            }
        }
    }

    // Exact Hamming distance 4: all nine derangements of four positions.
    static constexpr std::uint8_t kDerangements4[9U][4U] = {
        {1U, 0U, 3U, 2U}, {1U, 2U, 3U, 0U},
        {1U, 3U, 0U, 2U}, {2U, 0U, 3U, 1U},
        {2U, 3U, 0U, 1U}, {2U, 3U, 1U, 0U},
        {3U, 0U, 1U, 2U}, {3U, 2U, 0U, 1U},
        {3U, 2U, 1U, 0U},
    };
    for (std::size_t a = 0U; a < LoopHeadFarmer::kRoleCount; ++a) {
        for (std::size_t b = a + 1U;
             b < LoopHeadFarmer::kRoleCount;
             ++b) {
            for (std::size_t c = b + 1U;
                 c < LoopHeadFarmer::kRoleCount;
                 ++c) {
                for (std::size_t d = c + 1U;
                     d < LoopHeadFarmer::kRoleCount;
                     ++d) {
                    const std::size_t aPositions[4U] = {a, b, c, d};
                    for (const auto &aDerangement : kDerangements4) {
                        LoopHeadPattern11 aNeighbor = pPattern;
                        for (std::size_t i = 0U; i < 4U; ++i) {
                            aNeighbor.mWandererForOrbiter[aPositions[i]] =
                                pPattern.mWandererForOrbiter[
                                    aPositions[aDerangement[i]]];
                        }
                        pForbidden->Add(RankUnchecked(aNeighbor));
                    }
                }
            }
        }
    }
}

struct PreCandidate {
    std::uint64_t mHash = 0ULL;
    std::uint32_t mRank = 0U;
};

bool PatternScoreIsBetter(const LoopHeadPattern11 &pA,
                          const LoopHeadPattern11 &pB) {
    if (pA.mWorstDistance != pB.mWorstDistance) {
        return pA.mWorstDistance > pB.mWorstDistance;
    }
    if (pA.mDistanceTotal != pB.mDistanceTotal) {
        return pA.mDistanceTotal > pB.mDistanceTotal;
    }
    return pA.mPermutationRank < pB.mPermutationRank;
}

void Append32(std::vector<std::uint8_t> *pBytes,
              const std::uint32_t pValue) {
    for (unsigned i = 0U; i < 4U; ++i) {
        pBytes->push_back(static_cast<std::uint8_t>(
            (pValue >> (i * 8U)) & 0xFFU));
    }
}

bool Read32(const std::vector<std::uint8_t> &pBytes,
            std::size_t *pOffset,
            std::uint32_t *pValue) {
    if ((*pOffset + 4U) > pBytes.size()) {
        return false;
    }
    std::uint32_t aValue = 0U;
    for (unsigned i = 0U; i < 4U; ++i) {
        aValue |= static_cast<std::uint32_t>(pBytes[*pOffset + i])
                  << (i * 8U);
    }
    *pOffset += 4U;
    *pValue = aValue;
    return true;
}

bool SaveHeadPatterns(const std::string &pPath,
                      const std::vector<LoopHeadPattern11> &pPatterns,
                      std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kFileHeaderByteCount +
                   (pPatterns.size() * kFilePatternByteCount));
    aBytes.insert(aBytes.end(), kFileMagic.begin(), kFileMagic.end());
    Append32(&aBytes, kFileVersion);
    Append32(&aBytes,
             static_cast<std::uint32_t>(LoopHeadFarmer::kRoleCount));
    Append32(&aBytes,
             static_cast<std::uint32_t>(LoopHeadFarmer::kCoreCount));
    Append32(&aBytes,
             static_cast<std::uint32_t>(
                 LoopHeadFarmer::kPatternsPerCore));
    Append32(&aBytes, LoopHeadFarmer::kPermutationCount);
    Append32(&aBytes,
             static_cast<std::uint32_t>(pPatterns.size()));

    for (const LoopHeadPattern11 &aPattern : pPatterns) {
        aBytes.insert(aBytes.end(),
                      aPattern.mWandererForOrbiter.begin(),
                      aPattern.mWandererForOrbiter.end());
        Append32(&aBytes, aPattern.mPermutationRank);
        aBytes.push_back(aPattern.mWorstDistance);
        Append32(&aBytes, aPattern.mDistanceTotal);
    }

    const std::string aPath = ResolvedPath(pPath);
    if (!FileIO::Save(aPath, aBytes)) {
        SetError(pErrorMessage,
                 "Loop head farmer could not save " + aPath);
        return false;
    }
    std::printf("Loop head farmer wrote %s (%zu bytes)\n",
                aPath.c_str(),
                aBytes.size());
    return true;
}

} // namespace

bool LoopHeadFarmer::Farm(const std::string &pPath,
                          std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    const auto aStart = std::chrono::steady_clock::now();

    // A deterministic 1/32 sample is large enough to support the strict
    // distance floor while keeping the expensive greedy phase compact.
    std::vector<PreCandidate> aPreCandidates;
    aPreCandidates.reserve((kPermutationCount / 32U) + 4096U);
    LoopHeadPattern11 aPattern = Identity();
    for (std::uint32_t aRank = 0U;
         aRank < kPermutationCount;
         ++aRank) {
        const std::uint64_t aHash = Mix64(
            PackedKey(aPattern) ^ 0xD68F5A72C914E30BULL);
        if ((aRank == 0U) || ((aHash & 31ULL) == 0ULL)) {
            aPreCandidates.push_back({aHash, aRank});
        }
        if ((aRank + 1U) < kPermutationCount) {
            std::next_permutation(
                aPattern.mWandererForOrbiter.begin(),
                aPattern.mWandererForOrbiter.end());
        }
    }
    std::sort(aPreCandidates.begin(),
              aPreCandidates.end(),
              [](const PreCandidate &pA, const PreCandidate &pB) {
                  if (pA.mHash != pB.mHash) {
                      return pA.mHash < pB.mHash;
                  }
                  return pA.mRank < pB.mRank;
              });

    RankBitSet aForbidden;
    std::vector<LoopHeadPattern11> aSelected;
    aSelected.reserve(kRetainedPatternCount);
    const LoopHeadPattern11 aIdentity = Identity();
    aSelected.push_back(aIdentity);
    MarkForbiddenNeighborhood(aIdentity, &aForbidden);

    for (const PreCandidate &aCandidate : aPreCandidates) {
        if ((aCandidate.mRank == 0U) ||
            aForbidden.Contains(aCandidate.mRank)) {
            continue;
        }
        LoopHeadPattern11 aSelectedPattern =
            PatternForRank(aCandidate.mRank);
        aSelected.push_back(aSelectedPattern);
        MarkForbiddenNeighborhood(aSelectedPattern, &aForbidden);
        if (aSelected.size() == kRetainedPatternCount) {
            break;
        }
    }
    if (aSelected.size() != kRetainedPatternCount) {
        SetError(pErrorMessage,
                 "Loop head preselection retained only " +
                 std::to_string(aSelected.size()) +
                 " patterns at minimum distance five");
        return false;
    }

    std::printf("Loop head preselection: candidates=%zu retained=%zu "
                "minimum_distance>=5\n",
                aPreCandidates.size(),
                aSelected.size());

    std::vector<std::uint64_t> aKeys(aSelected.size());
    for (std::size_t i = 0U; i < aSelected.size(); ++i) {
        aKeys[i] = PackedKey(aSelected[i]);
        aSelected[i].mWorstDistance =
            static_cast<std::uint8_t>(kRoleCount);
        aSelected[i].mDistanceTotal = 0U;
    }
    for (std::size_t i = 0U; i < aSelected.size(); ++i) {
        for (std::size_t j = i + 1U; j < aSelected.size(); ++j) {
            const std::uint8_t aDistance =
                KeyDistance(aKeys[i], aKeys[j]);
            aSelected[i].mWorstDistance = std::min(
                aSelected[i].mWorstDistance,
                aDistance);
            aSelected[j].mWorstDistance = std::min(
                aSelected[j].mWorstDistance,
                aDistance);
            aSelected[i].mDistanceTotal += aDistance;
            aSelected[j].mDistanceTotal += aDistance;
        }
    }
    std::sort(aSelected.begin(),
              aSelected.end(),
              PatternScoreIsBetter);

    const double aBestAverage =
        static_cast<double>(aSelected.front().mDistanceTotal) /
        static_cast<double>(aSelected.size() - 1U);
    const double aWorstAverage =
        static_cast<double>(aSelected.back().mDistanceTotal) /
        static_cast<double>(aSelected.size() - 1U);
    std::printf("Loop head exact rescore: pairs=196010100 "
                "best={worst:%u average:%.4f} "
                "last={worst:%u average:%.4f}\n",
                aSelected.front().mWorstDistance,
                aBestAverage,
                aSelected.back().mWorstDistance,
                aWorstAverage);
    std::printf("Round-robin layout: 180 cores x 110 heads; "
                "index=(head * 180) + core\n");

    if (!SaveHeadPatterns(pPath, aSelected, pErrorMessage)) {
        return false;
    }
    const double aSeconds = std::chrono::duration<double>(
        std::chrono::steady_clock::now() - aStart).count();
    std::printf("Loop head farming complete in %.3f seconds\n", aSeconds);
    return true;
}

bool LoopHeadFarmer::Load(
    const std::string &pPath,
    std::array<LoopHeadPattern11, kRetainedPatternCount> *pPatterns,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if (pPatterns == nullptr) {
        SetError(pErrorMessage,
                 "Loop head load destination was null");
        return false;
    }

    const std::string aPath = ResolvedPath(pPath);
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(aPath, aBytes) ||
        (aBytes.size() !=
         (kFileHeaderByteCount +
          (kRetainedPatternCount * kFilePatternByteCount))) ||
        !std::equal(kFileMagic.begin(), kFileMagic.end(), aBytes.begin())) {
        SetError(pErrorMessage,
                 "Loop head pattern file had an invalid size or header: " +
                 aPath);
        return false;
    }

    std::size_t aOffset = kFileMagic.size();
    std::uint32_t aVersion = 0U;
    std::uint32_t aRoleCount = 0U;
    std::uint32_t aCoreCount = 0U;
    std::uint32_t aPatternsPerCore = 0U;
    std::uint32_t aPermutationCount = 0U;
    std::uint32_t aPatternCount = 0U;
    if (!Read32(aBytes, &aOffset, &aVersion) ||
        !Read32(aBytes, &aOffset, &aRoleCount) ||
        !Read32(aBytes, &aOffset, &aCoreCount) ||
        !Read32(aBytes, &aOffset, &aPatternsPerCore) ||
        !Read32(aBytes, &aOffset, &aPermutationCount) ||
        !Read32(aBytes, &aOffset, &aPatternCount) ||
        (aVersion != kFileVersion) ||
        (aRoleCount != kRoleCount) ||
        (aCoreCount != kCoreCount) ||
        (aPatternsPerCore != kPatternsPerCore) ||
        (aPermutationCount != kPermutationCount) ||
        (aPatternCount != kRetainedPatternCount)) {
        SetError(pErrorMessage,
                 "Loop head pattern file had incompatible metadata: " +
                 aPath);
        return false;
    }

    RankBitSet aSeen;
    for (LoopHeadPattern11 &aPattern : *pPatterns) {
        for (std::uint8_t &aValue : aPattern.mWandererForOrbiter) {
            aValue = aBytes[aOffset++];
        }
        if (!Read32(aBytes, &aOffset, &aPattern.mPermutationRank)) {
            SetError(pErrorMessage,
                     "Loop head pattern file was truncated: " + aPath);
            return false;
        }
        aPattern.mWorstDistance = aBytes[aOffset++];
        if (!Read32(aBytes, &aOffset, &aPattern.mDistanceTotal) ||
            !IsValid(aPattern) ||
            (Rank(aPattern) != aPattern.mPermutationRank) ||
            (aPattern.mWorstDistance > kRoleCount) ||
            aSeen.Contains(aPattern.mPermutationRank)) {
            SetError(pErrorMessage,
                     "Loop head pattern file contained an invalid record: " +
                     aPath);
            return false;
        }
        aSeen.Add(aPattern.mPermutationRank);
    }
    for (std::size_t i = 1U; i < pPatterns->size(); ++i) {
        if (PatternScoreIsBetter((*pPatterns)[i],
                                 (*pPatterns)[i - 1U])) {
            SetError(pErrorMessage,
                     "Loop head patterns were not in final score order: " +
                     aPath);
            return false;
        }
    }

    std::printf("Loaded %zu loop head patterns from %s\n",
                pPatterns->size(),
                aPath.c_str());
    std::printf("First 5 loop head patterns in final score order:\n");
    for (std::size_t i = 0U; i < 5U; ++i) {
        const LoopHeadPattern11 &aPattern = (*pPatterns)[i];
        std::printf("ranked %zu -> core %zu, head %zu, "
                    "worst=%u average=%.4f\n",
                    i,
                    i % kCoreCount,
                    i / kCoreCount,
                    aPattern.mWorstDistance,
                    static_cast<double>(aPattern.mDistanceTotal) /
                        static_cast<double>(pPatterns->size() - 1U));
        PrintPattern(aPattern, aPattern.mPermutationRank);
    }
    return true;
}
