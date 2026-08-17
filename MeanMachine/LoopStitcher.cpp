//
//  LoopStitcher.cpp
//  MeanMachine
//

#include "LoopStitcher.hpp"

#include "FileIO.hpp"
#include "LoopNexusHearts.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <limits>
#include <numeric>
#include <random>
#include <unordered_set>

namespace {

constexpr std::array<std::uint8_t, 8U> kLoopMagic = {
    'M', 'M', 'N', 'E', 'X', 'U', 'S', '1',
};
constexpr std::uint32_t kLoopVersion = 2U;
constexpr std::uint32_t kMetricCount =
    static_cast<std::uint32_t>(LOOP_RECIPE_METRIC_COUNT_11);
constexpr std::uint32_t kLoopByteCount = 414U;
constexpr std::size_t kIntegrityOffset = 92U;
constexpr std::size_t kCoreScoreCount = 12U;
constexpr std::uint32_t kHeadPermutationCount = 39'916'800U;
constexpr std::size_t kSavedPatternCount = 19'800U;

using HeartBuckets = std::array<std::vector<LoopRecipe11>,
                                LoopStitcher::kHeartCount>;

static_assert(LoopNexusHearts::kHeartCount ==
              LoopStitcher::kHeartCount);

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

std::string ResolvedPath(const std::string &pPath) {
    const std::filesystem::path aPath(pPath);
    return aPath.is_absolute()
        ? aPath.lexically_normal().generic_string()
        : FileIO::ProjectRoot(pPath);
}

std::string ProjectRelativePath(const std::string &pPath) {
    std::error_code aError;
    const std::filesystem::path aRelative =
        std::filesystem::relative(pPath, FileIO::ProjectRoot(), aError);
    if (!aError && !aRelative.empty()) {
        return aRelative.lexically_normal().generic_string();
    }
    return std::filesystem::path(pPath)
        .lexically_normal().generic_string();
}

std::uint32_t Read32(const std::vector<std::uint8_t> &pBytes,
                     std::size_t *pOffset) {
    std::uint32_t aValue = 0U;
    for (unsigned i = 0U; i < sizeof(aValue); ++i) {
        aValue |= static_cast<std::uint32_t>(pBytes[*pOffset + i])
                  << (i * 8U);
    }
    *pOffset += sizeof(aValue);
    return aValue;
}

std::uint64_t Read64(const std::vector<std::uint8_t> &pBytes,
                     std::size_t *pOffset) {
    std::uint64_t aValue = 0ULL;
    for (unsigned i = 0U; i < sizeof(aValue); ++i) {
        aValue |= static_cast<std::uint64_t>(pBytes[*pOffset + i])
                  << (i * 8U);
    }
    *pOffset += sizeof(aValue);
    return aValue;
}

std::uint64_t HashByte(const std::uint64_t pHash,
                       const std::uint8_t pByte) {
    return (pHash ^ static_cast<std::uint64_t>(pByte)) *
        0x100000001B3ULL;
}

std::uint64_t IntegrityHash(const std::vector<std::uint8_t> &pBytes) {
    std::uint64_t aHash = 0xCBF29CE484222325ULL;
    for (std::size_t i = 0U; i < pBytes.size(); ++i) {
        if ((i >= kIntegrityOffset) &&
            (i < (kIntegrityOffset + sizeof(std::uint64_t)))) {
            continue;
        }
        aHash = HashByte(aHash, pBytes[i]);
    }
    return aHash;
}

std::uint64_t HeartSignature(const LoopCorePattern11 &pHeart) {
    std::uint64_t aHash = 0xCBF29CE484222325ULL;
    for (const auto &aRound : pHeart.mRounds) {
        for (const std::uint8_t aRole : aRound) {
            aHash = HashByte(aHash, aRole);
        }
    }
    return aHash;
}

std::array<std::uint32_t, kCoreScoreCount> CoreScoreValues(
    const LoopCorePatternScore11 &pScore) {
    return {{
        pScore.mDirectedEdgeCount,
        pScore.mReciprocalEdgeCount,
        pScore.mStronglyConnected,
        pScore.mArticulationPointCount,
        pScore.mBridgeCount,
        pScore.mMinimumDestinationSources,
        pScore.mMinimumSourceReach,
        pScore.mMinimumDestinationCurveArea,
        pScore.mMinimumSourceCurveArea,
        pScore.mFinalInfluenceTotal,
        pScore.mInfluenceCurveArea,
        pScore.mDirectedDiameter,
    }};
}

bool IsPermutation(
    const std::array<std::uint8_t, LOOP_PATTERN_ROLE_COUNT_11> &pValues) {
    std::array<bool, LOOP_PATTERN_ROLE_COUNT_11> aSeen{};
    for (const std::uint8_t aValue : pValues) {
        if ((aValue >= LOOP_PATTERN_ROLE_COUNT_11) || aSeen[aValue]) {
            return false;
        }
        aSeen[aValue] = true;
    }
    return true;
}

std::uint32_t HeadRank(const LoopHeadPattern11 &pHead) {
    static constexpr std::array<std::uint32_t, 12U> kFactorials = {{
        1U, 1U, 2U, 6U, 24U, 120U, 720U, 5'040U,
        40'320U, 362'880U, 3'628'800U, 39'916'800U,
    }};
    std::uint32_t aRank = 0U;
    std::uint16_t aUsed = 0U;
    for (std::size_t i = 0U; i < LOOP_PATTERN_ROLE_COUNT_11; ++i) {
        const std::uint8_t aValue = pHead.mWandererForOrbiter[i];
        const std::uint16_t aSmallerMask =
            static_cast<std::uint16_t>((1U << aValue) - 1U);
        const std::uint32_t aSmallerUnused =
            static_cast<std::uint32_t>(__builtin_popcount(
                static_cast<unsigned int>(aSmallerMask & ~aUsed)));
        aRank += aSmallerUnused *
            kFactorials[LOOP_PATTERN_ROLE_COUNT_11 - 1U - i];
        aUsed = static_cast<std::uint16_t>(aUsed | (1U << aValue));
    }
    return aRank;
}

bool CoreIsValid(const LoopCorePattern11 &pCore) {
    for (std::size_t aColumn = 0U; aColumn < 3U; ++aColumn) {
        std::array<bool, LOOP_PATTERN_ROLE_COUNT_11> aSeen{};
        for (const auto &aRound : pCore.mRounds) {
            const std::uint8_t aRole = aRound[aColumn];
            if ((aRole >= LOOP_PATTERN_ROLE_COUNT_11) || aSeen[aRole]) {
                return false;
            }
            aSeen[aRole] = true;
        }
    }
    return true;
}

bool TailIsValid(const LoopTailPattern11 &pTail) {
    if (!IsPermutation(pTail.mOrbiterAForWanderer) ||
        !IsPermutation(pTail.mOrbiterBForWanderer)) {
        return false;
    }
    std::array<std::array<bool, LOOP_PATTERN_ROLE_COUNT_11>,
               LOOP_PATTERN_ROLE_COUNT_11> aSeenPairs{};
    for (std::size_t i = 0U; i < LOOP_PATTERN_ROLE_COUNT_11; ++i) {
        const std::size_t a = pTail.mOrbiterAForWanderer[i];
        const std::size_t b = pTail.mOrbiterBForWanderer[i];
        if (a == b) {
            return false;
        }
        const std::size_t aLow = std::min(a, b);
        const std::size_t aHigh = std::max(a, b);
        if (aSeenPairs[aLow][aHigh]) {
            return false;
        }
        aSeenPairs[aLow][aHigh] = true;
    }
    return true;
}

bool TailFitsHeartAndHead(const LoopTailPattern11 &pTail,
                          const LoopCorePattern11 &pHeart,
                          const LoopHeadPattern11 &pHead) {
    std::array<std::array<bool, LOOP_PATTERN_ROLE_COUNT_11>,
               LOOP_PATTERN_ROLE_COUNT_11> aHeartAdjacency{};
    for (const auto &aRound : pHeart.mRounds) {
        aHeartAdjacency[aRound[0]][aRound[1]] = true;
        aHeartAdjacency[aRound[1]][aRound[0]] = true;
        aHeartAdjacency[aRound[0]][aRound[2]] = true;
        aHeartAdjacency[aRound[2]][aRound[0]] = true;
    }
    for (std::size_t i = 0U; i < LOOP_PATTERN_ROLE_COUNT_11; ++i) {
        if (aHeartAdjacency[pTail.mOrbiterAForWanderer[i]]
                           [pTail.mOrbiterBForWanderer[i]]) {
            return false;
        }
    }

    std::array<std::uint8_t,
               LOOP_PATTERN_ROLE_COUNT_11> aOrbiterForWanderer{};
    for (std::size_t aOrbiter = 0U;
         aOrbiter < LOOP_PATTERN_ROLE_COUNT_11;
         ++aOrbiter) {
        aOrbiterForWanderer[
            pHead.mWandererForOrbiter[aOrbiter]] =
                static_cast<std::uint8_t>(aOrbiter);
    }
    std::array<std::array<bool, LOOP_PATTERN_ROLE_COUNT_11>,
               LOOP_PATTERN_ROLE_COUNT_11> aTransition{};
    for (std::size_t aWanderer = 0U;
         aWanderer < LOOP_PATTERN_ROLE_COUNT_11;
         ++aWanderer) {
        const std::size_t aDestination =
            aOrbiterForWanderer[aWanderer];
        aTransition[pTail.mOrbiterAForWanderer[aWanderer]]
                   [aDestination] = true;
        aTransition[pTail.mOrbiterBForWanderer[aWanderer]]
                   [aDestination] = true;
    }
    for (std::size_t aStart = 0U;
         aStart < LOOP_PATTERN_ROLE_COUNT_11;
         ++aStart) {
        std::array<bool, LOOP_PATTERN_ROLE_COUNT_11> aVisited{};
        std::array<std::uint8_t,
                   LOOP_PATTERN_ROLE_COUNT_11> aQueue{};
        std::size_t aRead = 0U;
        std::size_t aWrite = 0U;
        aVisited[aStart] = true;
        aQueue[aWrite++] = static_cast<std::uint8_t>(aStart);
        while (aRead < aWrite) {
            const std::size_t aNode = aQueue[aRead++];
            for (std::size_t aNext = 0U;
                 aNext < LOOP_PATTERN_ROLE_COUNT_11;
                 ++aNext) {
                if (aTransition[aNode][aNext] && !aVisited[aNext]) {
                    aVisited[aNext] = true;
                    aQueue[aWrite++] = static_cast<std::uint8_t>(aNext);
                }
            }
        }
        if (std::find(aVisited.begin(), aVisited.end(), false) !=
            aVisited.end()) {
            return false;
        }
    }
    return true;
}

bool ParseLoopIndex(const std::filesystem::path &pPath,
                    std::uint64_t *pLoopIndex) {
    if (pPath.extension() != ".bin") {
        return false;
    }
    const std::string aName = pPath.stem().generic_string();
    constexpr const char *kPrefix = "loop_";
    constexpr std::size_t kPrefixLength = 5U;
    if ((aName.rfind(kPrefix, 0U) != 0U) ||
        (aName.size() == kPrefixLength)) {
        return false;
    }
    std::uint64_t aValue = 0ULL;
    for (std::size_t i = kPrefixLength; i < aName.size(); ++i) {
        const char aCharacter = aName[i];
        if ((aCharacter < '0') || (aCharacter > '9')) {
            return false;
        }
        const std::uint64_t aDigit =
            static_cast<std::uint64_t>(aCharacter - '0');
        if (aValue > ((std::numeric_limits<std::uint64_t>::max() -
                       aDigit) / 10ULL)) {
            return false;
        }
        aValue = (aValue * 10ULL) + aDigit;
    }
    if (aValue == 0ULL) {
        return false;
    }
    *pLoopIndex = aValue;
    return true;
}

bool LoadRecord(const std::string &pPath,
                const std::size_t pExpectedHeartIndex,
                const std::uint64_t pExpectedLoopIndex,
                LoopRecipe11 *pRecipe,
                std::string *pReason) {
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes) ||
        (aBytes.size() != kLoopByteCount) ||
        !std::equal(kLoopMagic.begin(), kLoopMagic.end(), aBytes.begin())) {
        SetError(pReason, "invalid file header or size");
        return false;
    }

    std::size_t aOffset = kLoopMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    const std::uint32_t aRoleCount = Read32(aBytes, &aOffset);
    const std::uint32_t aMetricCount = Read32(aBytes, &aOffset);
    const std::uint32_t aByteCount = Read32(aBytes, &aOffset);
    const std::uint32_t aHeartIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aSourceHeartIndex = Read32(aBytes, &aOffset);
    const std::uint64_t aLoopIndex = Read64(aBytes, &aOffset);
    const std::uint32_t aPatternIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aHeadRank = Read32(aBytes, &aOffset);
    const std::int32_t aIntegerScore =
        static_cast<std::int32_t>(Read32(aBytes, &aOffset));
    const std::int32_t aMinimumScore =
        static_cast<std::int32_t>(Read32(aBytes, &aOffset));
    const std::uint32_t aMinimumHead = Read32(aBytes, &aOffset);
    const std::uint32_t aMinimumTailPartial = Read32(aBytes, &aOffset);
    const std::uint32_t aMinimumTailFull = Read32(aBytes, &aOffset);
    const std::uint64_t aRawAttempt = Read64(aBytes, &aOffset);
    const std::uint64_t aAcceptedOrdinal = Read64(aBytes, &aOffset);
    const std::uint64_t aHeartSignature = Read64(aBytes, &aOffset);
    const std::uint64_t aIntegrity = Read64(aBytes, &aOffset);

    const LoopCorePattern11 &aExpectedHeart =
        LoopNexusHearts::kNexuses[pExpectedHeartIndex];
    if ((aVersion != kLoopVersion) ||
        (aRoleCount != LOOP_PATTERN_ROLE_COUNT_11) ||
        (aMetricCount != kMetricCount) ||
        (aByteCount != kLoopByteCount) ||
        (aHeartIndex != pExpectedHeartIndex) ||
        (aSourceHeartIndex !=
         LoopNexusHearts::kSourceHeartIndices[pExpectedHeartIndex]) ||
        (aLoopIndex != pExpectedLoopIndex) ||
        (aPatternIndex >= kSavedPatternCount) ||
        (aHeadRank >= kHeadPermutationCount) ||
        (aIntegerScore < aMinimumScore) ||
        (aMinimumHead > LOOP_PATTERN_ROLE_COUNT_11) ||
        (aMinimumTailPartial > LOOP_PATTERN_ROLE_COUNT_11) ||
        (aMinimumTailFull > LOOP_PATTERN_ROLE_COUNT_11) ||
        (aHeartSignature != HeartSignature(aExpectedHeart)) ||
        (aIntegrity != IntegrityHash(aBytes))) {
        SetError(pReason, "record metadata or checksum did not validate");
        return false;
    }

    LoopRecipe11 aRecipe;
    aRecipe.mCore = aExpectedHeart;
    aRecipe.mMetadata.mNexusIndex = aHeartIndex;
    aRecipe.mMetadata.mSourceHeartIndex = aSourceHeartIndex;
    aRecipe.mMetadata.mFileIndex = aLoopIndex;
    aRecipe.mMetadata.mPatternIndex = aPatternIndex;
    aRecipe.mMetadata.mIntegerScore = aIntegerScore;
    aRecipe.mMetadata.mMinimumScore = aMinimumScore;
    aRecipe.mMetadata.mRawAttempt = aRawAttempt;
    aRecipe.mMetadata.mAcceptedOrdinal = aAcceptedOrdinal;
    aRecipe.mMetadata.mSourceFile = ProjectRelativePath(pPath);
    aRecipe.mHead.mPermutationRank = aHeadRank;
    for (std::uint8_t &aValue :
         aRecipe.mHead.mWandererForOrbiter) {
        aValue = aBytes[aOffset++];
    }
    LoopCorePattern11 aStoredCore;
    for (auto &aRound : aStoredCore.mRounds) {
        for (std::uint8_t &aValue : aRound) {
            aValue = aBytes[aOffset++];
        }
    }
    for (std::uint8_t &aValue :
         aRecipe.mTail.mOrbiterAForWanderer) {
        aValue = aBytes[aOffset++];
    }
    for (std::uint8_t &aValue :
         aRecipe.mTail.mOrbiterBForWanderer) {
        aValue = aBytes[aOffset++];
    }

    const auto aExpectedScores = CoreScoreValues(aExpectedHeart.mScore);
    for (std::size_t i = 0U; i < kCoreScoreCount; ++i) {
        if (Read32(aBytes, &aOffset) != aExpectedScores[i]) {
            SetError(pReason, "stored core score did not match its nexus");
            return false;
        }
    }
    for (std::int32_t &aMetric : aRecipe.mMetadata.mMetrics) {
        aMetric = static_cast<std::int32_t>(Read32(aBytes, &aOffset));
    }
    if ((aOffset != aBytes.size()) ||
        (aStoredCore.mRounds != aExpectedHeart.mRounds) ||
        !CoreIsValid(aRecipe.mCore) ||
        !IsPermutation(aRecipe.mHead.mWandererForOrbiter) ||
        (HeadRank(aRecipe.mHead) != aHeadRank) ||
        !TailIsValid(aRecipe.mTail) ||
        !TailFitsHeartAndHead(aRecipe.mTail,
                              aRecipe.mCore,
                              aRecipe.mHead)) {
        SetError(pReason, "record body did not validate");
        return false;
    }

    *pRecipe = std::move(aRecipe);
    return true;
}

std::string HeartFolder(const std::string &pRoot,
                        const std::size_t pHeartIndex) {
    char aName[32];
    std::snprintf(aName, sizeof(aName), "nexus_%02zu", pHeartIndex);
    return (std::filesystem::path(pRoot) / aName)
        .lexically_normal().generic_string();
}

} // namespace

bool LoopStitcher::Load(const std::string &pFolderPath,
                        ExpanderBuckets *pExpanderBuckets,
                        std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if (pExpanderBuckets == nullptr) {
        SetError(pErrorMessage,
                 "Loop stitcher destination was null");
        return false;
    }
    *pExpanderBuckets = {};

    const std::string aRoot = ResolvedPath(pFolderPath);
    HeartBuckets aHeartBuckets;
    std::size_t aIgnoredCount = 0U;
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < kHeartCount;
         ++aHeartIndex) {
        const std::string aFolder = HeartFolder(aRoot, aHeartIndex);
        std::error_code aDirectoryError;
        if (!std::filesystem::is_directory(aFolder, aDirectoryError) ||
            aDirectoryError) {
            SetError(pErrorMessage,
                     "Loop stitcher could not read heart bucket " +
                     aFolder);
            return false;
        }

        std::vector<std::pair<std::uint64_t,
                              std::filesystem::path>> aPaths;
        std::error_code aEnumerationError;
        std::filesystem::directory_iterator aIterator(
            aFolder, aEnumerationError);
        while (!aEnumerationError &&
               (aIterator != std::filesystem::directory_iterator())) {
            std::error_code aTypeError;
            if (aIterator->is_regular_file(aTypeError) && !aTypeError) {
                std::uint64_t aLoopIndex = 0ULL;
                if (ParseLoopIndex(aIterator->path(), &aLoopIndex)) {
                    aPaths.push_back({aLoopIndex, aIterator->path()});
                }
            }
            aIterator.increment(aEnumerationError);
        }
        if (aEnumerationError) {
            SetError(pErrorMessage,
                     "Loop stitcher could not enumerate " + aFolder +
                     ": " + aEnumerationError.message());
            return false;
        }
        std::sort(aPaths.begin(), aPaths.end(),
                  [](const auto &pA, const auto &pB) {
                      return pA.first < pB.first;
                  });

        std::unordered_set<std::uint64_t> aSeenIndices;
        for (const auto &aEntry : aPaths) {
            if (!aSeenIndices.insert(aEntry.first).second) {
                ++aIgnoredCount;
                std::printf("Loop stitcher ignored duplicate index %llu "
                            "in nexus_%02zu\n",
                            static_cast<unsigned long long>(aEntry.first),
                            aHeartIndex);
                continue;
            }
            LoopRecipe11 aRecipe;
            std::string aReason;
            const std::string aPath =
                aEntry.second.lexically_normal().generic_string();
            if (!LoadRecord(aPath,
                            aHeartIndex,
                            aEntry.first,
                            &aRecipe,
                            &aReason)) {
                ++aIgnoredCount;
                std::printf("Loop stitcher ignored %s: %s\n",
                            aPath.c_str(), aReason.c_str());
                continue;
            }
            aHeartBuckets[aHeartIndex].push_back(std::move(aRecipe));
        }
        if (aHeartBuckets[aHeartIndex].empty()) {
            SetError(pErrorMessage,
                     "Loop stitcher found no usable recipes in " +
                     aFolder);
            return false;
        }
    }

    std::mt19937_64 aGenerator(std::random_device{}());
    for (std::vector<LoopRecipe11> &aBucket : aHeartBuckets) {
        std::shuffle(aBucket.begin(), aBucket.end(), aGenerator);
    }
    std::array<std::size_t, kHeartCount> aHeartOrder{};
    std::iota(aHeartOrder.begin(), aHeartOrder.end(), 0U);
    std::shuffle(aHeartOrder.begin(), aHeartOrder.end(), aGenerator);

    std::array<std::array<std::size_t, kHeartCount>,
               kExpanderCount> aAssignmentCounts{};
    std::size_t aExpanderIndex = 0U;
    for (const std::size_t aHeartIndex : aHeartOrder) {
        for (LoopRecipe11 &aRecipe : aHeartBuckets[aHeartIndex]) {
            (*pExpanderBuckets)[aExpanderIndex].push_back(
                std::move(aRecipe));
            ++aAssignmentCounts[aExpanderIndex][aHeartIndex];
            aExpanderIndex = (aExpanderIndex + 1U) % kExpanderCount;
        }
    }
    for (std::size_t i = 0U; i < kExpanderCount; ++i) {
        std::vector<LoopRecipe11> &aBucket = (*pExpanderBuckets)[i];
        if (aBucket.size() < kRequiredRecipesPerExpander) {
            SetError(pErrorMessage,
                     "Loop stitcher assigned only " +
                     std::to_string(aBucket.size()) +
                     " unique recipes to expander_" +
                     (i < 10U ? "0" : "") + std::to_string(i) +
                     "; 656 are required");
            return false;
        }
        std::shuffle(aBucket.begin(), aBucket.end(), aGenerator);
    }

    std::printf("\nLOOP STITCHER — HEART BUCKETS\n");
    std::size_t aTotalCount = 0U;
    for (std::size_t i = 0U; i < kHeartCount; ++i) {
        std::printf("  nexus_%02zu: %zu\n",
                    i, aHeartBuckets[i].size());
        aTotalCount += aHeartBuckets[i].size();
    }
    std::printf("LOOP STITCHER — ASSIGNMENTS BY EXPANDER\n");
    std::printf("             ");
    for (std::size_t i = 0U; i < kHeartCount; ++i) {
        std::printf(" nx%02zu", i);
    }
    std::printf(" | total spare\n");
    for (std::size_t i = 0U; i < kExpanderCount; ++i) {
        std::printf("  expander_%02zu", i);
        for (std::size_t aHeartIndex = 0U;
             aHeartIndex < kHeartCount;
             ++aHeartIndex) {
            std::printf(" %4zu",
                        aAssignmentCounts[i][aHeartIndex]);
        }
        const std::size_t aCount = (*pExpanderBuckets)[i].size();
        std::printf(" | %5zu %5zu\n",
                    aCount,
                    aCount - kRequiredRecipesPerExpander);
    }
    std::printf("  total: %zu usable, %zu ignored\n\n",
                aTotalCount, aIgnoredCount);
    return true;
}
