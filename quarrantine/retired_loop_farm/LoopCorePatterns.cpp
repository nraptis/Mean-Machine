//
//  LoopCorePatterns.cpp
//  MeanMachine
//

#include "LoopCorePatterns.hpp"

#include "FileIO.hpp"

#include <algorithm>
#include <array>
#include <filesystem>
#include <limits>
#include <vector>

namespace {

constexpr std::size_t kRoleCount = 11U;
constexpr std::size_t kColumnCount = 3U;
constexpr std::array<std::uint8_t, 8U> kMagic = {
    'M', 'M', 'L', 'C', '1', '1', 'B', '1',
};
constexpr std::uint32_t kVersion = 2U;
constexpr std::size_t kScoreFieldCount = 12U;
constexpr std::size_t kScoreByteCount = kScoreFieldCount * 4U;
constexpr std::size_t kHeaderByteCount =
    8U + 4U + 4U + 8U + 8U + 8U + (4U * kScoreByteCount);
constexpr std::size_t kPatternByteCount =
    (kRoleCount * kColumnCount) + kScoreByteCount;

void SetError(std::string *pErrorMessage,
              const std::string &pText) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pText;
    }
}

std::string ResolvedPath(const std::string &pPath) {
    const std::filesystem::path aPath(pPath);
    return aPath.is_absolute()
        ? aPath.lexically_normal().generic_string()
        : FileIO::ProjectRoot(pPath);
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

bool Read64(const std::vector<std::uint8_t> &pBytes,
            std::size_t *pOffset,
            std::uint64_t *pValue) {
    if ((*pOffset + 8U) > pBytes.size()) {
        return false;
    }
    std::uint64_t aValue = 0ULL;
    for (unsigned i = 0U; i < 8U; ++i) {
        aValue |= static_cast<std::uint64_t>(pBytes[*pOffset + i])
                  << (i * 8U);
    }
    *pOffset += 8U;
    *pValue = aValue;
    return true;
}

bool ReadScore(const std::vector<std::uint8_t> &pBytes,
               std::size_t *pOffset,
               LoopCorePatternScore11 *pScore) {
    return Read32(pBytes, pOffset, &pScore->mDirectedEdgeCount) &&
           Read32(pBytes, pOffset, &pScore->mReciprocalEdgeCount) &&
           Read32(pBytes, pOffset, &pScore->mStronglyConnected) &&
           Read32(pBytes, pOffset, &pScore->mArticulationPointCount) &&
           Read32(pBytes, pOffset, &pScore->mBridgeCount) &&
           Read32(pBytes, pOffset, &pScore->mMinimumDestinationSources) &&
           Read32(pBytes, pOffset, &pScore->mMinimumSourceReach) &&
           Read32(pBytes, pOffset,
                  &pScore->mMinimumDestinationCurveArea) &&
           Read32(pBytes, pOffset,
                  &pScore->mMinimumSourceCurveArea) &&
           Read32(pBytes, pOffset, &pScore->mFinalInfluenceTotal) &&
           Read32(pBytes, pOffset, &pScore->mInfluenceCurveArea) &&
           Read32(pBytes, pOffset, &pScore->mDirectedDiameter);
}

bool PatternColumnsArePermutations(const LoopCorePattern11 &pPattern) {
    for (std::size_t aColumn = 0U;
         aColumn < kColumnCount;
         ++aColumn) {
        std::array<bool, kRoleCount> aSeen{};
        for (const auto &aRound : pPattern.mRounds) {
            const std::uint8_t aRole = aRound[aColumn];
            if ((aRole >= kRoleCount) || aSeen[aRole]) {
                return false;
            }
            aSeen[aRole] = true;
        }
    }
    return true;
}

} // namespace

bool LoopCorePatterns::Load(const std::string &pPath,
                            LoopCorePatternFile11 *pFile,
                            std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if (pFile == nullptr) {
        SetError(pErrorMessage,
                 "Loop core pattern load destination was null");
        return false;
    }
    *pFile = {};

    const std::string aPath = ResolvedPath(pPath);
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(aPath, aBytes)) {
        SetError(pErrorMessage,
                 "Loop core pattern file could not be loaded: " + aPath);
        return false;
    }
    if ((aBytes.size() < kHeaderByteCount) ||
        !std::equal(kMagic.begin(), kMagic.end(), aBytes.begin())) {
        SetError(pErrorMessage,
                 "Loop core pattern file had an invalid header: " + aPath);
        return false;
    }

    std::size_t aOffset = kMagic.size();
    std::uint32_t aVersion = 0U;
    std::uint32_t aRoleCount = 0U;
    std::uint64_t aPatternCount = 0ULL;
    if (!Read32(aBytes, &aOffset, &aVersion) ||
        !Read32(aBytes, &aOffset, &aRoleCount) ||
        !Read64(aBytes, &aOffset, &pFile->mEvaluatedCount) ||
        !Read64(aBytes, &aOffset, &pFile->mEligibleCount) ||
        !Read64(aBytes, &aOffset, &aPatternCount) ||
        !ReadScore(aBytes, &aOffset, &pFile->mWholeWorst) ||
        !ReadScore(aBytes, &aOffset, &pFile->mWholeBest) ||
        !ReadScore(aBytes, &aOffset, &pFile->mChosenWorst) ||
        !ReadScore(aBytes, &aOffset, &pFile->mChosenBest) ||
        (aVersion != kVersion) ||
        (aRoleCount != kRoleCount) ||
        (aPatternCount >
         static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max()))) {
        SetError(pErrorMessage,
                 "Loop core pattern file had an incompatible header: " +
                 aPath);
        return false;
    }

    const std::size_t aExpectedByteCount =
        kHeaderByteCount +
        (static_cast<std::size_t>(aPatternCount) * kPatternByteCount);
    if (aBytes.size() != aExpectedByteCount) {
        SetError(pErrorMessage,
                 "Loop core pattern file had an incorrect exact size: " +
                 aPath);
        return false;
    }

    pFile->mPatterns.resize(static_cast<std::size_t>(aPatternCount));
    for (LoopCorePattern11 &aPattern : pFile->mPatterns) {
        for (auto &aRound : aPattern.mRounds) {
            for (std::uint8_t &aRole : aRound) {
                aRole = aBytes[aOffset++];
            }
        }
        if (!ReadScore(aBytes, &aOffset, &aPattern.mScore) ||
            !PatternColumnsArePermutations(aPattern)) {
            SetError(pErrorMessage,
                     "Loop core pattern file contained an invalid pattern: " +
                     aPath);
            return false;
        }
    }
    return aOffset == aBytes.size();
}
