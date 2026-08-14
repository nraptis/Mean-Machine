//
//  LoopNewFarmer.cpp
//  MeanMachine
//

#include "LoopNewFarmer.hpp"

#include "FileIO.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <filesystem>
#include <unordered_set>
#include <vector>

namespace {

constexpr std::array<std::uint8_t, 8U> kTailFileMagic = {
    'M', 'M', 'T', 'A', 'I', 'L', '1', '1',
};
constexpr std::uint32_t kTailFileVersion = 1U;
constexpr std::size_t kTailFileHeaderByteCount = 32U;
constexpr std::size_t kTailPatternByteCount =
    LoopHeadFarmer::kRoleCount * 2U;

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

bool Read32(const std::vector<std::uint8_t> &pBytes,
            std::size_t *pOffset,
            std::uint32_t *pValue) {
    if ((*pOffset + 4U) > pBytes.size()) {
        return false;
    }
    std::uint32_t aValue = 0U;
    for (unsigned i = 0U; i < 4U; ++i) {
        aValue |= static_cast<std::uint32_t>(
                      pBytes[*pOffset + i]) << (i * 8U);
    }
    *pOffset += 4U;
    *pValue = aValue;
    return true;
}

bool TailIsValid(const LoopTailPattern11 &pTail) {
    std::array<bool, LoopHeadFarmer::kRoleCount> aSeenA{};
    std::array<bool, LoopHeadFarmer::kRoleCount> aSeenB{};
    std::array<std::array<bool, LoopHeadFarmer::kRoleCount>,
               LoopHeadFarmer::kRoleCount> aSeenPairs{};
    for (std::size_t i = 0U;
         i < LoopHeadFarmer::kRoleCount;
         ++i) {
        const std::size_t a = pTail.mOrbiterAForWanderer[i];
        const std::size_t b = pTail.mOrbiterBForWanderer[i];
        if ((a >= LoopHeadFarmer::kRoleCount) ||
            (b >= LoopHeadFarmer::kRoleCount) ||
            (a == b) || aSeenA[a] || aSeenB[b]) {
            return false;
        }
        aSeenA[a] = true;
        aSeenB[b] = true;
        const std::size_t aLo = std::min(a, b);
        const std::size_t aHi = std::max(a, b);
        if (aSeenPairs[aLo][aHi]) {
            return false;
        }
        aSeenPairs[aLo][aHi] = true;
    }
    return true;
}

bool TailFitsHeartAndHead(const LoopTailPattern11 &pTail,
                          const LoopCorePattern11 &pHeart,
                          const LoopHeadPattern11 &pHead) {
    std::array<std::array<bool, LoopHeadFarmer::kRoleCount>,
               LoopHeadFarmer::kRoleCount> aHeartAdjacency{};
    for (const auto &aRound : pHeart.mRounds) {
        aHeartAdjacency[aRound[0]][aRound[1]] = true;
        aHeartAdjacency[aRound[1]][aRound[0]] = true;
        aHeartAdjacency[aRound[0]][aRound[2]] = true;
        aHeartAdjacency[aRound[2]][aRound[0]] = true;
    }
    for (std::size_t i = 0U;
         i < LoopHeadFarmer::kRoleCount;
         ++i) {
        const std::size_t a = pTail.mOrbiterAForWanderer[i];
        const std::size_t b = pTail.mOrbiterBForWanderer[i];
        if (aHeartAdjacency[a][b]) {
            return false;
        }
    }

    std::array<std::uint8_t,
               LoopHeadFarmer::kRoleCount> aOrbiterForWanderer{};
    for (std::size_t aOrbiter = 0U;
         aOrbiter < LoopHeadFarmer::kRoleCount;
         ++aOrbiter) {
        aOrbiterForWanderer[
            pHead.mWandererForOrbiter[aOrbiter]] =
                static_cast<std::uint8_t>(aOrbiter);
    }
    std::array<std::array<bool, LoopHeadFarmer::kRoleCount>,
               LoopHeadFarmer::kRoleCount> aTransition{};
    for (std::size_t aWanderer = 0U;
         aWanderer < LoopHeadFarmer::kRoleCount;
         ++aWanderer) {
        const std::size_t aDestination =
            aOrbiterForWanderer[aWanderer];
        aTransition[pTail.mOrbiterAForWanderer[aWanderer]]
                   [aDestination] = true;
        aTransition[pTail.mOrbiterBForWanderer[aWanderer]]
                   [aDestination] = true;
    }
    for (std::size_t aStart = 0U;
         aStart < LoopHeadFarmer::kRoleCount;
         ++aStart) {
        std::array<bool, LoopHeadFarmer::kRoleCount> aVisited{};
        std::array<std::uint8_t,
                   LoopHeadFarmer::kRoleCount> aQueue{};
        std::size_t aRead = 0U;
        std::size_t aWrite = 0U;
        aVisited[aStart] = true;
        aQueue[aWrite++] = static_cast<std::uint8_t>(aStart);
        while (aRead < aWrite) {
            const std::size_t aNode = aQueue[aRead++];
            for (std::size_t aNext = 0U;
                 aNext < LoopHeadFarmer::kRoleCount;
                 ++aNext) {
                if (aTransition[aNode][aNext] &&
                    !aVisited[aNext]) {
                    aVisited[aNext] = true;
                    aQueue[aWrite++] =
                        static_cast<std::uint8_t>(aNext);
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

std::string TailKey(const LoopTailPattern11 &pTail) {
    std::string aKey;
    aKey.reserve(LoopHeadFarmer::kRoleCount * 2U);
    for (const std::uint8_t aValue :
         pTail.mOrbiterAForWanderer) {
        aKey.push_back(static_cast<char>(aValue));
    }
    for (const std::uint8_t aValue :
         pTail.mOrbiterBForWanderer) {
        aKey.push_back(static_cast<char>(aValue));
    }
    return aKey;
}

}

bool LoopNewFarmer::RecipeIsValid(
    const LoopCorePattern11 &pCore,
    const LoopHeadPattern11 &pHead,
    const LoopTailPattern11 &pTail) {
    for (std::size_t aColumn = 0U; aColumn < 3U; ++aColumn) {
        std::array<bool, LoopHeadFarmer::kRoleCount> aSeen{};
        for (const auto &aRound : pCore.mRounds) {
            const std::size_t aRole = aRound[aColumn];
            if ((aRole >= LoopHeadFarmer::kRoleCount) || aSeen[aRole]) {
                return false;
            }
            aSeen[aRole] = true;
        }
    }
    return LoopHeadFarmer::IsValid(pHead) &&
           TailIsValid(pTail) &&
           TailFitsHeartAndHead(pTail, pCore, pHead);
}

bool LoopNewFarmer::Load(const std::string &pHeartPatternPath,
                         const std::string &pHeadPatternPath,
                         LoopNewPatternFile11 *pFile,
                         std::string *pErrorMessage) {
    static_assert(LoopHeadFarmer::kRetainedPatternCount ==
                  (LoopHeadFarmer::kCoreCount *
                   LoopHeadFarmer::kPatternsPerCore));

    SetError(pErrorMessage, "");
    if (pFile == nullptr) {
        SetError(pErrorMessage,
                 "Loop-new load destination was null");
        return false;
    }

    LoopCorePatternFile11 aHeartFile;
    std::string aLoadError;
    if (!LoopCorePatterns::Load(pHeartPatternPath,
                                &aHeartFile,
                                &aLoadError)) {
        SetError(pErrorMessage,
                 "Loop-new heart loading failed: " + aLoadError);
        return false;
    }
    if (aHeartFile.mPatterns.size() !=
        LoopHeadFarmer::kCoreCount) {
        SetError(pErrorMessage,
                 "Loop-new heart file did not contain exactly 180 hearts");
        return false;
    }

    std::array<LoopHeadPattern11,
               LoopHeadFarmer::kRetainedPatternCount> aHeads;
    if (!LoopHeadFarmer::Load(pHeadPatternPath,
                              &aHeads,
                              &aLoadError)) {
        SetError(pErrorMessage,
                 "Loop-new head loading failed: " + aLoadError);
        return false;
    }

    std::array<std::size_t,
               LoopHeadFarmer::kCoreCount> aHeadCounts{};
    std::array<bool,
               LoopHeadFarmer::kRetainedPatternCount> aUsedHeads{};
    std::size_t aTotalHeadCount = 0U;

    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < LoopHeadFarmer::kCoreCount;
         ++aHeartIndex) {
        LoopNewHeart11 &aHeart = pFile->mHearts[aHeartIndex];
        aHeart.mHeart = aHeartFile.mPatterns[aHeartIndex];

        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(aHeartIndex,
                                             aHeadIndex);
            if ((aPatternIndex >= aHeads.size()) ||
                aUsedHeads[aPatternIndex]) {
                SetError(pErrorMessage,
                         "Loop-new round-robin head mapping was invalid");
                return false;
            }

            aHeart.mHeads[aHeadIndex].mHead = aHeads[aPatternIndex];
            aUsedHeads[aPatternIndex] = true;
            ++aHeadCounts[aHeartIndex];
            ++aTotalHeadCount;
        }
    }

    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < aHeadCounts.size();
         ++aHeartIndex) {
        if (aHeadCounts[aHeartIndex] !=
            LoopHeadFarmer::kPatternsPerCore) {
            SetError(pErrorMessage,
                     "Loop-new heart did not receive exactly 110 heads");
            return false;
        }
    }
    for (const bool aWasUsed : aUsedHeads) {
        if (!aWasUsed) {
            SetError(pErrorMessage,
                     "Loop-new head was not assigned to a heart");
            return false;
        }
    }
    if (aTotalHeadCount !=
        LoopHeadFarmer::kRetainedPatternCount) {
        SetError(pErrorMessage,
                 "Loop-new joined head count was not exactly 19,800");
        return false;
    }

    std::printf("Loaded loop-new patterns: %zu hearts x %zu heads "
                "= %zu joined patterns\n",
                pFile->mHearts.size(),
                pFile->mHearts.front().mHeads.size(),
                aTotalHeadCount);
    return true;
}

bool LoopNewFarmer::Load(const std::string &pHeartPatternPath,
                         const std::string &pHeadPatternPath,
                         const std::string &pTailPatternPath,
                         LoopNewPatternFile11 *pFile,
                         std::string *pErrorMessage) {
    if (!Load(pHeartPatternPath,
              pHeadPatternPath,
              pFile,
              pErrorMessage)) {
        return false;
    }
    return LoadTailPatterns(pTailPatternPath,
                            pFile,
                            pErrorMessage);
}

bool LoopNewFarmer::LoadTailPatterns(
    const std::string &pTailPatternPath,
    LoopNewPatternFile11 *pFile,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if (pFile == nullptr) {
        SetError(pErrorMessage,
                 "Loop-new tail load destination was null");
        return false;
    }

    const std::string aPath = ResolvedPath(pTailPatternPath);
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(aPath, aBytes) ||
        (aBytes.size() !=
         (kTailFileHeaderByteCount +
          (LoopHeadFarmer::kRetainedPatternCount *
           kTailPatternByteCount))) ||
        !std::equal(kTailFileMagic.begin(),
                    kTailFileMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Loop-new tail file had an invalid size or header: " +
                 aPath);
        return false;
    }

    std::size_t aOffset = kTailFileMagic.size();
    std::uint32_t aVersion = 0U;
    std::uint32_t aRoleCount = 0U;
    std::uint32_t aHeartCount = 0U;
    std::uint32_t aHeadsPerHeart = 0U;
    std::uint32_t aPatternCount = 0U;
    std::uint32_t aPatternByteCount = 0U;
    if (!Read32(aBytes, &aOffset, &aVersion) ||
        !Read32(aBytes, &aOffset, &aRoleCount) ||
        !Read32(aBytes, &aOffset, &aHeartCount) ||
        !Read32(aBytes, &aOffset, &aHeadsPerHeart) ||
        !Read32(aBytes, &aOffset, &aPatternCount) ||
        !Read32(aBytes, &aOffset, &aPatternByteCount) ||
        (aVersion != kTailFileVersion) ||
        (aRoleCount != LoopHeadFarmer::kRoleCount) ||
        (aHeartCount != LoopHeadFarmer::kCoreCount) ||
        (aHeadsPerHeart != LoopHeadFarmer::kPatternsPerCore) ||
        (aPatternCount != LoopHeadFarmer::kRetainedPatternCount) ||
        (aPatternByteCount != kTailPatternByteCount)) {
        SetError(pErrorMessage,
                 "Loop-new tail file had incompatible metadata: " +
                 aPath);
        return false;
    }

    std::size_t aLoadedPatternCount = 0U;
    std::unordered_set<std::string> aTailKeys;
    aTailKeys.reserve(LoopHeadFarmer::kRetainedPatternCount * 2U);
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < LoopHeadFarmer::kCoreCount;
         ++aHeartIndex) {
        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            LoopTailPattern11 &aTail =
                pFile->mHearts[aHeartIndex]
                    .mHeads[aHeadIndex]
                    .mTail;
            for (std::uint8_t &aOrbiter :
                 aTail.mOrbiterAForWanderer) {
                aOrbiter = aBytes[aOffset++];
            }
            for (std::uint8_t &aOrbiter :
                 aTail.mOrbiterBForWanderer) {
                aOrbiter = aBytes[aOffset++];
            }
            if (!TailIsValid(aTail) ||
                !TailFitsHeartAndHead(
                    aTail,
                    pFile->mHearts[aHeartIndex].mHeart,
                    pFile->mHearts[aHeartIndex]
                        .mHeads[aHeadIndex].mHead)) {
                SetError(pErrorMessage,
                         "Loop-new tail file contained an invalid record: " +
                         aPath);
                return false;
            }
            if (!aTailKeys.insert(TailKey(aTail)).second) {
                SetError(pErrorMessage,
                         "Loop-new tail file contained duplicate records: " +
                         aPath);
                return false;
            }
            ++aLoadedPatternCount;
        }
    }

    if ((aOffset != aBytes.size()) ||
        (aLoadedPatternCount !=
         LoopHeadFarmer::kRetainedPatternCount)) {
        SetError(pErrorMessage,
                 "Loop-new tail file did not load exactly 19,800 records");
        return false;
    }

    std::printf("Loaded loop-new tails: %zu hearts x %zu heads "
                "= %zu tail patterns\n",
                pFile->mHearts.size(),
                pFile->mHearts.front().mHeads.size(),
                aLoadedPatternCount);
    return true;
}
