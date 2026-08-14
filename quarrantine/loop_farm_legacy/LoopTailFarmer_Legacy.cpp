//
//  LoopTailFarmer.cpp
//  MeanMachine
//

#include "LoopTailFarmer.hpp"

#include "FileIO.hpp"
#include "LoopCorePatternFarmer.hpp"
#include "LoopExtremeMeasures.hpp"
#include "LoopFinalFarmHearts.hpp"
#include "LoopFinalFarmThreholds.hpp"
#include "LoopHeadTailDifference.hpp"
#include "LoopPlanMinimums.hpp"
#include "LoopNewFarmer.hpp"
#include "LoopScorer.hpp"
#include "LoopWeights.hpp"

#include <algorithm>
#include <array>
#include <cerrno>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <limits>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

namespace {

constexpr std::size_t kRoleCount = LoopHeadFarmer::kRoleCount;
constexpr std::size_t kSourceCount = 17U;
constexpr std::size_t kFirstIterationSourceCount = 15U;
constexpr std::size_t kScoreFieldCount = 50U;

constexpr bool ShouldMeasureMetric(const bool pWeightedOnly,
                                   const std::size_t pMetric) {
    return !pWeightedOnly || LoopWeights::IsEnabled(pMetric);
}

constexpr std::size_t kInitialIngressSource = 11U;
constexpr std::size_t kInitialCarrySource = 12U;
constexpr std::size_t kFirstFreshIngressSource = 13U;
constexpr std::size_t kFirstFreshCrossSource = 14U;
constexpr std::size_t kSecondFreshIngressSource = 15U;
constexpr std::size_t kSecondFreshCrossSource = 16U;
constexpr int kFlowStepsPerIteration = 25;

constexpr std::array<std::uint8_t, 8U> kFileMagic = {
    'M', 'M', 'T', 'A', 'I', 'L', '1', '1',
};
constexpr std::uint32_t kFileVersion = 1U;
constexpr std::size_t kFileHeaderByteCount = 32U;
constexpr std::size_t kPatternByteCount = kRoleCount * 2U;

constexpr std::array<std::uint8_t, 8U> kPoolFileMagic = {
    'M', 'M', 'T', 'P', 'O', 'O', 'L', 'A',
};
constexpr std::uint32_t kPoolFileVersion = 10U;
constexpr std::size_t kPoolFileHeaderByteCount = 56U;
constexpr std::size_t kPoolRecordByteCount =
    kPatternByteCount + (kScoreFieldCount * sizeof(std::uint32_t));

enum class PoolPhase : std::uint32_t {
    kExploration = 1U,
    kSafe = 2U,
};

struct PoolMetadata {
    PoolPhase mPhase = PoolPhase::kExploration;
    std::uint64_t mExplorationCasesPerPair = 0ULL;
    std::size_t mParentRetainedPerPair = 0U;
    std::size_t mRetainedPerPair = 0U;
};

enum : std::uint8_t {
    kContextIngress = 0U,
    kContextScatter = 1U,
    kContextPrevious = 2U,
    kContextCross = 3U,
};

using Influence = std::uint32_t;
using InfluenceSet = std::array<Influence, kRoleCount>;
using DistanceMatrix = std::array<
    std::array<int, kRoleCount>, kRoleCount>;
using ArrivalMatrix = std::array<
    std::array<int, kSourceCount>, kRoleCount>;

constexpr int kUnreachableDistance =
    static_cast<int>(kRoleCount) + 1;

class Generator {
public:
    explicit Generator(const std::uint64_t pSeed)
    : mState(pSeed) {
    }

    std::uint64_t Next() {
        mState += 0x9E3779B97F4A7C15ULL;
        std::uint64_t aValue = mState;
        aValue = (aValue ^ (aValue >> 30U)) *
            0xBF58476D1CE4E5B9ULL;
        aValue = (aValue ^ (aValue >> 27U)) *
            0x94D049BB133111EBULL;
        return aValue ^ (aValue >> 31U);
    }

    std::size_t Below(const std::size_t pCeiling) {
        if (pCeiling <= 1U) {
            return 0U;
        }
        const std::uint64_t aCeiling =
            static_cast<std::uint64_t>(pCeiling);
        const std::uint64_t aLimit =
            std::numeric_limits<std::uint64_t>::max() -
            (std::numeric_limits<std::uint64_t>::max() % aCeiling);
        std::uint64_t aValue = 0ULL;
        do {
            aValue = Next();
        } while (aValue >= aLimit);
        return static_cast<std::size_t>(aValue % aCeiling);
    }

    bool Bool() {
        return (Next() & 1ULL) != 0ULL;
    }

private:
    std::uint64_t mState = 0ULL;
};

std::uint64_t GeneratorSeedForPattern(const std::size_t pPatternIndex) {
    std::uint64_t aValue =
        0xD1B54A32D192ED03ULL +
        (static_cast<std::uint64_t>(pPatternIndex) *
         0x9E3779B97F4A7C15ULL);
    aValue = (aValue ^ (aValue >> 30U)) *
        0xBF58476D1CE4E5B9ULL;
    aValue = (aValue ^ (aValue >> 27U)) *
        0x94D049BB133111EBULL;
    return aValue ^ (aValue >> 31U);
}

template <std::size_t N>
void Shuffle(std::array<std::uint8_t, N> *pValues,
             Generator *pGenerator) {
    for (std::size_t i = N; i > 1U; --i) {
        const std::size_t aSwap = pGenerator->Below(i);
        std::swap((*pValues)[i - 1U], (*pValues)[aSwap]);
    }
}

std::array<std::uint8_t, kRoleCount> IdentityRoles() {
    std::array<std::uint8_t, kRoleCount> aResult{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aResult[i] = static_cast<std::uint8_t>(i);
    }
    return aResult;
}

std::string ResolvedPath(const std::string &pPath) {
    const std::filesystem::path aPath(pPath);
    return aPath.is_absolute()
        ? aPath.lexically_normal().generic_string()
        : FileIO::ProjectRoot(pPath);
}

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

void Append32(std::vector<std::uint8_t> *pBytes,
              const std::uint32_t pValue) {
    for (unsigned i = 0U; i < 4U; ++i) {
        pBytes->push_back(static_cast<std::uint8_t>(
            pValue >> (i * 8U)));
    }
}

void Append64(std::vector<std::uint8_t> *pBytes,
              const std::uint64_t pValue) {
    for (unsigned i = 0U; i < 8U; ++i) {
        pBytes->push_back(static_cast<std::uint8_t>(
            pValue >> (i * 8U)));
    }
}

std::uint32_t Read32(const std::vector<std::uint8_t> &pBytes,
                     std::size_t *pOffset) {
    std::uint32_t aValue = 0U;
    for (unsigned i = 0U; i < 4U; ++i) {
        aValue |= static_cast<std::uint32_t>(pBytes[*pOffset + i]) <<
            (i * 8U);
    }
    *pOffset += 4U;
    return aValue;
}

std::uint64_t Read64(const std::vector<std::uint8_t> &pBytes,
                     std::size_t *pOffset) {
    std::uint64_t aValue = 0ULL;
    for (unsigned i = 0U; i < 8U; ++i) {
        aValue |= static_cast<std::uint64_t>(pBytes[*pOffset + i]) <<
            (i * 8U);
    }
    *pOffset += 8U;
    return aValue;
}

std::string PoolFilePath(const std::string &pFolderPath,
                         const std::size_t pHeartIndex) {
    char aName[64];
    std::snprintf(aName, sizeof(aName),
                  "loop_tail_core_%03zu.bin", pHeartIndex);
    return (std::filesystem::path(ResolvedPath(pFolderPath)) / aName)
        .lexically_normal().generic_string();
}

int PopCount(const Influence pValue) {
    return __builtin_popcount(static_cast<unsigned int>(pValue));
}

Influence SourceInfluence(const std::size_t pSource) {
    return static_cast<Influence>(1U << pSource);
}

Influence ContextInfluence(const std::uint8_t pContext,
                           const Influence pIngress,
                           const Influence pScatter,
                           const Influence pPrevious,
                           const Influence pCross) {
    switch (pContext) {
        case kContextIngress: return pIngress;
        case kContextScatter: return pScatter;
        case kContextPrevious: return pPrevious;
        case kContextCross: return pCross;
        default: return 0U;
    }
}

DistanceMatrix HeartTemporalDistances(
    const LoopCorePattern11 &pHeart) {
    DistanceMatrix aDistances{};
    for (std::size_t aSource = 0U;
         aSource < kRoleCount;
         ++aSource) {
        aDistances[aSource].fill(kUnreachableDistance);
        aDistances[aSource][aSource] = 0;
    }

    for (const auto &aRound : pHeart.mRounds) {
        const std::size_t aLead = aRound[0];
        const std::size_t aSource = aRound[1];
        const std::size_t aFeedback = aRound[2];
        for (std::size_t aOrigin = 0U;
             aOrigin < kRoleCount;
             ++aOrigin) {
            if (aDistances[aOrigin][aSource] <
                kUnreachableDistance) {
                aDistances[aOrigin][aLead] = std::min(
                    aDistances[aOrigin][aLead],
                    aDistances[aOrigin][aSource] + 1);
            }
            if (aDistances[aOrigin][aLead] <
                kUnreachableDistance) {
                aDistances[aOrigin][aFeedback] = std::min(
                    aDistances[aOrigin][aFeedback],
                    aDistances[aOrigin][aLead] + 1);
            }
        }
    }
    return aDistances;
}

int HeartPairSeparation(const DistanceMatrix &pDistances,
                        const std::size_t pA,
                        const std::size_t pB) {
    return std::min(pDistances[pA][pB],
                    pDistances[pB][pA]);
}

struct IterationResult {
    InfluenceSet mOrbiters{};
    int mFlowArea = 0;
};

void RecordArrivals(const Influence pInfluence,
                    const std::size_t pWanderer,
                    const int pStep,
                    ArrivalMatrix *pArrivals) {
    for (std::size_t aSource = 0U;
         aSource < kSourceCount;
         ++aSource) {
        int &aArrival = (*pArrivals)[pWanderer][aSource];
        if ((aArrival < 0) &&
            ((pInfluence & SourceInfluence(aSource)) != 0U)) {
            aArrival = pStep;
        }
    }
}

IterationResult PropagateIteration(
    const LoopCorePattern11 &pHeart,
    const LoopHeadPattern11 &pHead,
    const LoopTailPattern11 &pTail,
    const std::size_t pPatternIndex,
    const std::size_t pFreshIngressSource,
    const std::size_t pFreshCrossSource,
    const int pBaseStep,
    InfluenceSet *pWanderers,
    Influence *pIngress,
    Influence *pCarry,
    ArrivalMatrix *pArrivals) {
    IterationResult aResult;
    const Influence aPrevious = *pIngress;
    const Influence aFreshIngress =
        SourceInfluence(pFreshIngressSource);
    const Influence aCross = SourceInfluence(pFreshCrossSource);
    const Influence aScatter =
        aPrevious | aFreshIngress | aCross | *pCarry;

    const std::size_t aAssignmentCarryBase =
        pPatternIndex % kRoleCount;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::uint8_t aContext =
            static_cast<std::uint8_t>(
                (i + (pPatternIndex & 3U)) & 3U);
        Influence aInfluence =
            (*pWanderers)[pHead.mWandererForOrbiter[i]] |
            ContextInfluence(aContext,
                             aFreshIngress,
                             aScatter,
                             aPrevious,
                             aCross);
        if ((i == aAssignmentCarryBase) ||
            (i == ((aAssignmentCarryBase + 4U) % kRoleCount)) ||
            (i == ((aAssignmentCarryBase + 8U) % kRoleCount))) {
            aInfluence |= *pCarry;
        }
        aResult.mOrbiters[i] = aInfluence;
    }

    for (const Influence aInfluence : aResult.mOrbiters) {
        aResult.mFlowArea += PopCount(aInfluence);
    }
    for (const auto &aRound : pHeart.mRounds) {
        aResult.mOrbiters[aRound[0]] |=
            aResult.mOrbiters[aRound[1]];
        aResult.mOrbiters[aRound[2]] |=
            aResult.mOrbiters[aRound[0]];
        int aCurrentTotal = 0;
        for (const Influence aInfluence : aResult.mOrbiters) {
            aCurrentTotal += PopCount(aInfluence);
        }
        aResult.mFlowArea += aCurrentTotal;
    }

    Influence aCrushedIngress = aScatter;
    for (const Influence aOrbiter : aResult.mOrbiters) {
        aCrushedIngress |= aOrbiter;
    }

    const InfluenceSet aPreviousWanderers = *pWanderers;
    InfluenceSet aUpdatedWanderers = aPreviousWanderers;
    const std::size_t aUpdateCarryBase =
        (pPatternIndex * 3U) % kRoleCount;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::uint8_t aContext =
            static_cast<std::uint8_t>(
                (i + 1U + ((pPatternIndex >> 2U) & 3U)) & 3U);
        Influence aInfluence = aPreviousWanderers[i] |
            aResult.mOrbiters[pTail.mOrbiterAForWanderer[i]] |
            aResult.mOrbiters[pTail.mOrbiterBForWanderer[i]] |
            ContextInfluence(aContext,
                             aCrushedIngress,
                             aScatter,
                             aPrevious,
                             aCross);
        if ((i == aUpdateCarryBase) ||
            (i == ((aUpdateCarryBase + 5U) % kRoleCount))) {
            aInfluence |= *pCarry;
        }
        aUpdatedWanderers[i] = aInfluence;
        if (pArrivals != nullptr) {
            RecordArrivals(aInfluence,
                           i,
                           pBaseStep + 14 + static_cast<int>(i),
                           pArrivals);
        }

        int aCurrentTotal = 0;
        for (const Influence aValue : aUpdatedWanderers) {
            aCurrentTotal += PopCount(aValue);
        }
        aResult.mFlowArea += aCurrentTotal;
    }

    Influence aNextCarry = *pCarry | aCrushedIngress;
    for (const Influence aWanderer : aUpdatedWanderers) {
        aNextCarry |= aWanderer;
    }
    *pWanderers = aUpdatedWanderers;
    *pIngress = aCrushedIngress;
    *pCarry = aNextCarry;
    return aResult;
}

struct PairInfo {
    bool mAllowed = false;
    int mUnion = 0;
    int mOverlap = 0;
    int mUniqueSide = 0;
    int mComplement = 0;
    int mHeartSeparation = 0;
};

using PairInfoMatrix = std::array<
    std::array<PairInfo, kRoleCount>, kRoleCount>;

PairInfoMatrix MeasurePairs(const InfluenceSet &pOrbiters,
                            const DistanceMatrix &pDistances) {
    PairInfoMatrix aResult{};
    for (std::size_t a = 0U; a < kRoleCount; ++a) {
        for (std::size_t b = a + 1U; b < kRoleCount; ++b) {
            PairInfo aInfo;
            aInfo.mUnion = PopCount(pOrbiters[a] | pOrbiters[b]);
            aInfo.mOverlap = PopCount(pOrbiters[a] & pOrbiters[b]);
            aInfo.mUniqueSide = std::min(
                PopCount(pOrbiters[a] & ~pOrbiters[b]),
                PopCount(pOrbiters[b] & ~pOrbiters[a]));
            aInfo.mComplement = PopCount(
                pOrbiters[a] ^ pOrbiters[b]);
            aInfo.mHeartSeparation = HeartPairSeparation(
                pDistances, a, b);
            // Equality and a direct causal heart edge are structural tail
            // violations. Dependency overlap, complement, and union depend
            // on the independently fixed head, so they are ranked below
            // instead of making some heart/head pairs unsatisfiable.
            aInfo.mAllowed = aInfo.mHeartSeparation > 1;
            aResult[a][b] = aInfo;
            aResult[b][a] = aInfo;
        }
    }
    return aResult;
}

bool GenerateTail(const PairInfoMatrix &pPairs,
                  Generator *pGenerator,
                  LoopTailPattern11 *pTail) {
    // Normalize the first permutation to A...K, then solve the second as a
    // constrained perfect matching. A later target permutation restores the
    // full row-order space. This is equivalent to shuffling both sides, but
    // it does not waste almost every trial when the allowed graph is sparse.
    std::array<std::uint8_t, kRoleCount> aRoleOrder = IdentityRoles();
    Shuffle(&aRoleOrder, pGenerator);
    std::stable_sort(
        aRoleOrder.begin(), aRoleOrder.end(),
        [&pPairs](const std::uint8_t pA,
                  const std::uint8_t pB) {
            int aDegreeA = 0;
            int aDegreeB = 0;
            for (std::size_t i = 0U; i < kRoleCount; ++i) {
                aDegreeA += pPairs[pA][i].mAllowed;
                aDegreeB += pPairs[pB][i].mAllowed;
            }
            return aDegreeA < aDegreeB;
        });

    std::array<std::uint8_t, kRoleCount> aMatch{};
    aMatch.fill(0xFFU);
    std::array<bool, kRoleCount> aUsedB{};
    const std::function<bool(std::size_t)> Match =
        [&](const std::size_t pDepth) -> bool {
            if (pDepth == kRoleCount) {
                for (std::size_t a = 0U; a < kRoleCount; ++a) {
                    const std::size_t b = aMatch[a];
                    if ((b < kRoleCount) && (aMatch[b] == a)) {
                        return false;
                    }
                }
                return true;
            }

            const std::size_t a = aRoleOrder[pDepth];
            std::array<std::uint8_t, kRoleCount> aChoices =
                IdentityRoles();
            Shuffle(&aChoices, pGenerator);
            for (const std::uint8_t b : aChoices) {
                if (aUsedB[b] || !pPairs[a][b].mAllowed) {
                    continue;
                }
                // A reciprocal edge would repeat the same unordered pair.
                if ((aMatch[b] != 0xFFU) && (aMatch[b] == a)) {
                    continue;
                }
                aMatch[a] = b;
                aUsedB[b] = true;
                if (Match(pDepth + 1U)) {
                    return true;
                }
                aUsedB[b] = false;
                aMatch[a] = 0xFFU;
            }
            return false;
        };
    if (!Match(0U)) {
        return false;
    }

    std::array<std::uint8_t, kRoleCount> aTargets = IdentityRoles();
    Shuffle(&aTargets, pGenerator);
    const bool aReverse = pGenerator->Bool();
    for (std::size_t a = 0U; a < kRoleCount; ++a) {
        const std::size_t aTarget = aTargets[a];
        pTail->mOrbiterAForWanderer[aTarget] =
            aReverse ? aMatch[a] : static_cast<std::uint8_t>(a);
        pTail->mOrbiterBForWanderer[aTarget] =
            aReverse ? static_cast<std::uint8_t>(a) : aMatch[a];
    }
    return true;
}

int PairComponentCount(const LoopTailPattern11 &pTail) {
    std::array<std::array<bool, kRoleCount>, kRoleCount> aAdjacency{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::size_t a = pTail.mOrbiterAForWanderer[i];
        const std::size_t b = pTail.mOrbiterBForWanderer[i];
        aAdjacency[a][b] = true;
        aAdjacency[b][a] = true;
    }
    std::array<bool, kRoleCount> aVisited{};
    int aComponents = 0;
    for (std::size_t aStart = 0U;
         aStart < kRoleCount;
         ++aStart) {
        if (aVisited[aStart]) {
            continue;
        }
        ++aComponents;
        std::array<std::uint8_t, kRoleCount> aQueue{};
        std::size_t aRead = 0U;
        std::size_t aWrite = 0U;
        aVisited[aStart] = true;
        aQueue[aWrite++] = static_cast<std::uint8_t>(aStart);
        while (aRead < aWrite) {
            const std::size_t aNode = aQueue[aRead++];
            for (std::size_t aNext = 0U;
                 aNext < kRoleCount;
                 ++aNext) {
                if (aAdjacency[aNode][aNext] &&
                    !aVisited[aNext]) {
                    aVisited[aNext] = true;
                    aQueue[aWrite++] =
                        static_cast<std::uint8_t>(aNext);
                }
            }
        }
    }
    return aComponents;
}

std::string TailKey(const LoopTailPattern11 &pTail) {
    std::string aKey;
    aKey.reserve(kPatternByteCount);
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

bool IsTailPermutation(const LoopTailPattern11 &pTail) {
    std::array<bool, kRoleCount> aSeenA{};
    std::array<bool, kRoleCount> aSeenB{};
    std::array<bool, kRoleCount * kRoleCount> aSeenPairs{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::size_t a = pTail.mOrbiterAForWanderer[i];
        const std::size_t b = pTail.mOrbiterBForWanderer[i];
        if ((a >= kRoleCount) || (b >= kRoleCount) ||
            aSeenA[a] || aSeenB[b] || (a == b)) {
            return false;
        }
        aSeenA[a] = true;
        aSeenB[b] = true;
        const std::size_t aLow = std::min(a, b);
        const std::size_t aHigh = std::max(a, b);
        const std::size_t aPairIndex = (aLow * kRoleCount) + aHigh;
        if (aSeenPairs[aPairIndex]) {
            return false;
        }
        aSeenPairs[aPairIndex] = true;
    }
    return true;
}

struct TransitionMetrics {
    bool mStronglyConnected = false;
    int mDirectedDiameter = 0;
    int mMinimumExpansion = 0;
    int mExpansionTotal = 0;
};

using TransitionMatrix = std::array<
    std::array<std::uint8_t, kRoleCount>, kRoleCount>;

TransitionMatrix MakeTransitionMatrix(
    const LoopHeadPattern11 &pHead,
    const LoopTailPattern11 &pTail) {
    // This is explicitly a wanderer-to-wanderer graph. The head tells us
    // which wanderer feeds each orbiter. The tail tells us which two
    // orbiters feed each destination wanderer. Following both mappings gives
    // one directed edge from a source wanderer, through an orbiter, to a
    // destination wanderer.
    TransitionMatrix aResult{};
    for (std::size_t aDestinationWanderer = 0U;
         aDestinationWanderer < kRoleCount;
         ++aDestinationWanderer) {
        const std::size_t aOrbiterA =
            pTail.mOrbiterAForWanderer[aDestinationWanderer];
        const std::size_t aOrbiterB =
            pTail.mOrbiterBForWanderer[aDestinationWanderer];
        const std::size_t aSourceWandererA =
            pHead.mWandererForOrbiter[aOrbiterA];
        const std::size_t aSourceWandererB =
            pHead.mWandererForOrbiter[aOrbiterB];
        ++aResult[aSourceWandererA][aDestinationWanderer];
        ++aResult[aSourceWandererB][aDestinationWanderer];
    }
    return aResult;
}

TransitionMetrics MeasureTransition(
    const TransitionMatrix &pTransition,
    const bool pMeasureExpansion,
    const bool pMeasureOptionalMetrics = true) {
    TransitionMetrics aResult;
    aResult.mStronglyConnected = true;
    for (std::size_t aStart = 0U;
         aStart < kRoleCount;
         ++aStart) {
        std::array<int, kRoleCount> aDistance{};
        aDistance.fill(-1);
        std::array<std::uint8_t, kRoleCount> aQueue{};
        std::size_t aRead = 0U;
        std::size_t aWrite = 0U;
        aDistance[aStart] = 0;
        aQueue[aWrite++] = static_cast<std::uint8_t>(aStart);
        while (aRead < aWrite) {
            const std::size_t aNode = aQueue[aRead++];
            for (std::size_t aNext = 0U;
                 aNext < kRoleCount;
                 ++aNext) {
                if ((pTransition[aNode][aNext] > 0U) &&
                    (aDistance[aNext] < 0)) {
                    aDistance[aNext] = aDistance[aNode] + 1;
                    aQueue[aWrite++] =
                        static_cast<std::uint8_t>(aNext);
                }
            }
        }
        for (std::size_t aDestination = 0U;
             aDestination < kRoleCount;
             ++aDestination) {
            const int aValue = aDistance[aDestination];
            if (aValue < 0) {
                aResult.mStronglyConnected = false;
                return aResult;
            }
            if (pMeasureOptionalMetrics) {
                aResult.mDirectedDiameter = std::max(
                    aResult.mDirectedDiameter, aValue);
            }
        }
    }

    if (!pMeasureExpansion) {
        return aResult;
    }

    aResult.mMinimumExpansion = std::numeric_limits<int>::max();
    const std::uint32_t aAll =
        (1U << static_cast<unsigned>(kRoleCount)) - 1U;
    for (std::uint32_t aMask = 1U; aMask < aAll; ++aMask) {
        const int aSize = __builtin_popcount(aMask);
        if (aSize > static_cast<int>(kRoleCount / 2U)) {
            continue;
        }
        int aBoundary = 0;
        for (std::size_t aSource = 0U;
             aSource < kRoleCount;
             ++aSource) {
            if ((aMask & (1U << aSource)) == 0U) {
                continue;
            }
            for (std::size_t aDestination = 0U;
                 aDestination < kRoleCount;
                 ++aDestination) {
                if ((aMask & (1U << aDestination)) == 0U) {
                    aBoundary += pTransition[aSource][aDestination];
                }
            }
        }
        const int aExpansion =
            (aBoundary * 1024) / (2 * aSize);
        aResult.mMinimumExpansion = std::min(
            aResult.mMinimumExpansion, aExpansion);
        if (pMeasureOptionalMetrics) {
            aResult.mExpansionTotal += aExpansion;
        }
    }
    return aResult;
}

constexpr std::size_t kWandererNodeCount = kRoleCount;
constexpr std::size_t kOrbiterNodeBase = kWandererNodeCount;
constexpr std::size_t kFlowNodeCount =
    kWandererNodeCount + kRoleCount;
constexpr int kEarlySpreadHopLimit = 4;

using WandererOrbiterGraph = std::array<
    std::array<bool, kFlowNodeCount>, kFlowNodeCount>;

struct WandererPathMetrics {
    int mMinimumInfluencedWanderers = 0;
    int mMinimumEarlyReach = 0;
    int mMeanEarlyReachTimes1000 = 0;
    int mMeanShortestPathTimes1000 = 0;
    int mWorstMeanShortestPathTimes1000 = 0;
    int mRedundantRouteFractionTimes1000 = 0;
    int mMaximumOrbiterPathLoadTimes1000 = 0;
};

WandererOrbiterGraph MakeWandererOrbiterGraph(
    const LoopCorePattern11 &pHeart,
    const LoopHeadPattern11 &pHead,
    const LoopTailPattern11 &pTail) {
    WandererOrbiterGraph aGraph{};

    // Head: each source wanderer initializes one orbiter.
    for (std::size_t aOrbiter = 0U;
         aOrbiter < kRoleCount;
         ++aOrbiter) {
        const std::size_t aSourceWanderer =
            pHead.mWandererForOrbiter[aOrbiter];
        aGraph[aSourceWanderer][kOrbiterNodeBase + aOrbiter] = true;
    }

    // Heart: each core round is source -> lead -> feedback.
    for (const auto &aRound : pHeart.mRounds) {
        const std::size_t aLead = kOrbiterNodeBase + aRound[0];
        const std::size_t aSource = kOrbiterNodeBase + aRound[1];
        const std::size_t aFeedback = kOrbiterNodeBase + aRound[2];
        aGraph[aSource][aLead] = true;
        aGraph[aLead][aFeedback] = true;
    }

    // Tail: two final orbiters update each destination wanderer.
    for (std::size_t aDestinationWanderer = 0U;
         aDestinationWanderer < kRoleCount;
         ++aDestinationWanderer) {
        const std::size_t aOrbiterA = kOrbiterNodeBase +
            pTail.mOrbiterAForWanderer[aDestinationWanderer];
        const std::size_t aOrbiterB = kOrbiterNodeBase +
            pTail.mOrbiterBForWanderer[aDestinationWanderer];
        aGraph[aOrbiterA][aDestinationWanderer] = true;
        aGraph[aOrbiterB][aDestinationWanderer] = true;
    }
    return aGraph;
}

std::array<int, kFlowNodeCount> FlowDistances(
    const WandererOrbiterGraph &pGraph,
    const std::size_t pSource) {
    std::array<int, kFlowNodeCount> aDistances{};
    aDistances.fill(-1);
    std::array<std::size_t, kFlowNodeCount> aQueue{};
    std::size_t aRead = 0U;
    std::size_t aWrite = 0U;
    aDistances[pSource] = 0;
    aQueue[aWrite++] = pSource;
    while (aRead < aWrite) {
        const std::size_t aNode = aQueue[aRead++];
        for (std::size_t aNext = 0U;
             aNext < kFlowNodeCount;
             ++aNext) {
            if (pGraph[aNode][aNext] && (aDistances[aNext] < 0)) {
                aDistances[aNext] = aDistances[aNode] + 1;
                aQueue[aWrite++] = aNext;
            }
        }
    }
    return aDistances;
}

std::array<std::uint64_t, kFlowNodeCount> FlowShortestPathCounts(
    const WandererOrbiterGraph &pGraph,
    const std::size_t pSource,
    const std::array<int, kFlowNodeCount> &pDistances) {
    std::array<std::uint64_t, kFlowNodeCount> aCounts{};
    aCounts[pSource] = 1ULL;
    for (int aDistance = 0;
         aDistance < static_cast<int>(kFlowNodeCount);
         ++aDistance) {
        for (std::size_t aNode = 0U;
             aNode < kFlowNodeCount;
             ++aNode) {
            if (pDistances[aNode] != aDistance) {
                continue;
            }
            for (std::size_t aNext = 0U;
                 aNext < kFlowNodeCount;
                 ++aNext) {
                if (pGraph[aNode][aNext] &&
                    (pDistances[aNext] == (aDistance + 1))) {
                    aCounts[aNext] += aCounts[aNode];
                }
            }
        }
    }
    return aCounts;
}

WandererPathMetrics MeasureWandererPaths(
    const LoopCorePattern11 &pHeart,
    const LoopHeadPattern11 &pHead,
    const LoopTailPattern11 &pTail,
    const bool pWeightedOnly = false) {
    const WandererOrbiterGraph aGraph =
        MakeWandererOrbiterGraph(pHeart, pHead, pTail);
    std::array<std::array<int, kFlowNodeCount>,
               kFlowNodeCount> aAllDistances{};
    std::array<std::array<std::uint64_t, kFlowNodeCount>,
               kFlowNodeCount> aAllPathCounts{};
    for (std::size_t aSource = 0U;
         aSource < kFlowNodeCount;
         ++aSource) {
        aAllDistances[aSource] = FlowDistances(aGraph, aSource);
        aAllPathCounts[aSource] = FlowShortestPathCounts(
            aGraph, aSource, aAllDistances[aSource]);
    }
    WandererPathMetrics aResult;
    aResult.mMinimumInfluencedWanderers =
        static_cast<int>(kRoleCount - 1U);
    aResult.mMinimumEarlyReach =
        static_cast<int>(kRoleCount - 1U);
    int aEarlyReachTotal = 0;
    int aShortestPathTotal = 0;
    int aRedundantRouteCount = 0;
    std::array<double, kRoleCount> aOrbiterPathLoads{};

    std::array<std::size_t, kRoleCount> aOrbiterForWanderer{};
    for (std::size_t aOrbiter = 0U;
         aOrbiter < kRoleCount;
         ++aOrbiter) {
        aOrbiterForWanderer[
            pHead.mWandererForOrbiter[aOrbiter]] = aOrbiter;
    }

    for (std::size_t aSourceWanderer = 0U;
         aSourceWanderer < kRoleCount;
         ++aSourceWanderer) {
        const auto &aDistances = aAllDistances[aSourceWanderer];
        int aInfluenced = 0;
        int aEarlyReach = 0;
        int aSourceShortestPathTotal = 0;
        const std::size_t aSourceOrbiter = kOrbiterNodeBase +
            aOrbiterForWanderer[aSourceWanderer];
        for (std::size_t aDestinationWanderer = 0U;
             aDestinationWanderer < kRoleCount;
             ++aDestinationWanderer) {
            if (aDestinationWanderer == aSourceWanderer) {
                continue;
            }
            const int aDistance = aDistances[aDestinationWanderer];
            if (aDistance >= 0) {
                ++aInfluenced;
                aShortestPathTotal += aDistance;
                aSourceShortestPathTotal += aDistance;
                aEarlyReach += aDistance <= kEarlySpreadHopLimit;
            }
            int aReachingBranches = 0;
            for (std::size_t aBranch = 0U;
                 aBranch < kFlowNodeCount;
                 ++aBranch) {
                const int aBranchDistance =
                    aAllDistances[aBranch][aDestinationWanderer];
                if (aGraph[aSourceOrbiter][aBranch] &&
                    (aBranchDistance >= 0) &&
                    (aBranchDistance <= (kEarlySpreadHopLimit - 2))) {
                    ++aReachingBranches;
                }
            }
            aRedundantRouteCount += aReachingBranches >= 2;

            const std::uint64_t aShortestPathCount =
                aAllPathCounts[aSourceWanderer][aDestinationWanderer];
            if (aShortestPathCount == 0ULL) {
                continue;
            }
            for (std::size_t aOrbiter = 0U;
                 aOrbiter < kRoleCount;
                 ++aOrbiter) {
                const std::size_t aOrbiterNode =
                    kOrbiterNodeBase + aOrbiter;
                const int aToOrbiter =
                    aAllDistances[aSourceWanderer][aOrbiterNode];
                const int aFromOrbiter =
                    aAllDistances[aOrbiterNode][aDestinationWanderer];
                if ((aToOrbiter < 0) || (aFromOrbiter < 0) ||
                    ((aToOrbiter + aFromOrbiter) != aDistance)) {
                    continue;
                }
                const double aPathsThrough =
                    static_cast<double>(
                        aAllPathCounts[aSourceWanderer][aOrbiterNode]) *
                    static_cast<double>(
                        aAllPathCounts[aOrbiterNode][aDestinationWanderer]);
                aOrbiterPathLoads[aOrbiter] +=
                    aPathsThrough /
                    static_cast<double>(aShortestPathCount);
            }
        }
        if (ShouldMeasureMetric(pWeightedOnly, 16U)) {
            aResult.mMinimumInfluencedWanderers = std::min(
                aResult.mMinimumInfluencedWanderers, aInfluenced);
        }
        aResult.mMinimumEarlyReach = std::min(
            aResult.mMinimumEarlyReach, aEarlyReach);
        if (ShouldMeasureMetric(pWeightedOnly, 18U)) {
            aEarlyReachTotal += aEarlyReach;
        }
        if (aInfluenced == static_cast<int>(kRoleCount - 1U)) {
            aResult.mWorstMeanShortestPathTimes1000 = std::max(
                aResult.mWorstMeanShortestPathTimes1000,
                (aSourceShortestPathTotal * 1000) /
                    static_cast<int>(kRoleCount - 1U));
        }
    }

    const int aPairCount =
        static_cast<int>(kRoleCount * (kRoleCount - 1U));
    if (ShouldMeasureMetric(pWeightedOnly, 18U)) {
        aResult.mMeanEarlyReachTimes1000 =
            (aEarlyReachTotal * 1000) /
            static_cast<int>(kRoleCount);
    }
    aResult.mMeanShortestPathTimes1000 =
        (aShortestPathTotal * 1000) / aPairCount;
    aResult.mRedundantRouteFractionTimes1000 =
        (aRedundantRouteCount * 1000) / aPairCount;
    aResult.mMaximumOrbiterPathLoadTimes1000 =
        static_cast<int>((
            *std::max_element(aOrbiterPathLoads.begin(),
                              aOrbiterPathLoads.end()) *
            1000.0 / static_cast<double>(aPairCount)) + 0.5);
    return aResult;
}

struct OrderedJourneyMetrics {
    int mMinimumOneRoundFanout = 0;
    int mMeanOneRoundFanoutTimes1000 = 0;
    int mMinimumSourceOrbiterArea = 0;
    int mMinimumDualTailReach = 0;
    int mMeanDualTailReachTimes1000 = 0;
    int mMaximumSourceOrphanArea = 0;
    int mMeanSourceOrphanAreaTimes1000 = 0;
    int mMaximumLastOrphanLatency = 0;
    int mMaximumStragglerGap = 0;
    int mMaximumMidpointSourceOrphans = 0;
    int mMaximumMidpointDestinationOrphanLoad = 0;
    int mMaximumMidpointCoOrphanLoad = 0;
    int mMaximumMeetingOrphans = 0;
    int mMaximumSourceMeetingArea = 0;
    int mMeanPairMeetingLatencyTimes1000 = 0;
    int mMaximumRobustOrphans = 0;
    int mMeanRobustOrphansTimes1000 = 0;
    int mMaximumDestinationOrphanArea = 0;
    int mMaximumDualTailOrphanArea = 0;
    int mMeanDualTailOrphanAreaTimes1000 = 0;
    int mMaximumRobustDestinationOrphans = 0;
    int mMaximumSingleOrbiterDamage = 0;
    int mMeanSingleOrbiterDamageTimes1000 = 0;
    int mMinimumSurvivingFanout = 0;
    int mMaximumDualTailArrivalSkew = 0;
};

OrderedJourneyMetrics MeasureOrderedJourney(
    const LoopCorePattern11 &pHeart,
    const LoopHeadPattern11 &pHead,
    const LoopTailPattern11 &pTail,
    const bool pWeightedOnly = false) {
    constexpr int kUnreachedRound =
        static_cast<int>(kRoleCount) + 1;
    constexpr int kHeartOperationCount =
        static_cast<int>(kRoleCount * 2U);
    constexpr int kUnmetOperation = kHeartOperationCount + 1;
    constexpr int kMidpointRound =
        static_cast<int>(kRoleCount / 2U);

    InfluenceSet aOrbiters{};
    std::array<std::size_t, kRoleCount> aOrbiterForWanderer{};
    for (std::size_t aOrbiter = 0U;
         aOrbiter < kRoleCount;
         ++aOrbiter) {
        const std::size_t aSource =
            pHead.mWandererForOrbiter[aOrbiter];
        aOrbiters[aOrbiter] = SourceInfluence(aSource);
        aOrbiterForWanderer[aSource] = aOrbiter;
    }

    std::array<std::array<int, kRoleCount>, kRoleCount>
        aDestinationArrivals{};
    std::array<std::array<int, kRoleCount>, kRoleCount>
        aTailAArrivals{};
    std::array<std::array<int, kRoleCount>, kRoleCount>
        aTailBArrivals{};
    std::array<std::array<int, kRoleCount>, kRoleCount>
        aMeetingArrivals{};
    for (std::size_t aSource = 0U;
         aSource < kRoleCount;
         ++aSource) {
        aDestinationArrivals[aSource].fill(kUnreachedRound);
        aTailAArrivals[aSource].fill(kUnreachedRound);
        aTailBArrivals[aSource].fill(kUnreachedRound);
        aMeetingArrivals[aSource].fill(kUnmetOperation);
        aDestinationArrivals[aSource][aSource] = 0;
        aTailAArrivals[aSource][aSource] = 0;
        aTailBArrivals[aSource][aSource] = 0;
        aMeetingArrivals[aSource][aSource] = 0;
    }

    const auto RecordDestinationArrivals = [
        &aOrbiters,
        &aDestinationArrivals,
        &aTailAArrivals,
        &aTailBArrivals,
        &pTail](const int pRound) {
        for (std::size_t aDestination = 0U;
             aDestination < kRoleCount;
             ++aDestination) {
            const Influence aTailAInfluence =
                aOrbiters[pTail.mOrbiterAForWanderer[aDestination]];
            const Influence aTailBInfluence =
                aOrbiters[pTail.mOrbiterBForWanderer[aDestination]];
            const Influence aInfluence =
                aTailAInfluence | aTailBInfluence;
            for (std::size_t aSource = 0U;
                 aSource < kRoleCount;
                 ++aSource) {
                const Influence aSourceInfluence =
                    SourceInfluence(aSource);
                if ((aSource != aDestination) &&
                    (aDestinationArrivals[aSource][aDestination] ==
                        kUnreachedRound) &&
                    ((aInfluence & aSourceInfluence) != 0U)) {
                    aDestinationArrivals[aSource][aDestination] =
                        pRound;
                }
                if ((aSource != aDestination) &&
                    (aTailAArrivals[aSource][aDestination] ==
                        kUnreachedRound) &&
                    ((aTailAInfluence & aSourceInfluence) != 0U)) {
                    aTailAArrivals[aSource][aDestination] = pRound;
                }
                if ((aSource != aDestination) &&
                    (aTailBArrivals[aSource][aDestination] ==
                        kUnreachedRound) &&
                    ((aTailBInfluence & aSourceInfluence) != 0U)) {
                    aTailBArrivals[aSource][aDestination] = pRound;
                }
            }
        }
    };

    const auto RecordMeetings = [
        &aOrbiters,
        &aMeetingArrivals](const int pOperation) {
        for (const Influence aOrbiter : aOrbiters) {
            for (std::size_t a = 0U; a < kRoleCount; ++a) {
                if ((aOrbiter & SourceInfluence(a)) == 0U) {
                    continue;
                }
                for (std::size_t b = a + 1U;
                     b < kRoleCount;
                     ++b) {
                    if ((aOrbiter & SourceInfluence(b)) == 0U) {
                        continue;
                    }
                    aMeetingArrivals[a][b] = std::min(
                        aMeetingArrivals[a][b], pOperation);
                    aMeetingArrivals[b][a] = std::min(
                        aMeetingArrivals[b][a], pOperation);
                }
            }
        }
    };

    std::array<int, kRoleCount> aSourceOrbiterArea{};
    const auto RecordOrbiterCopies = [
        &aOrbiters,
        &aSourceOrbiterArea]() {
        for (std::size_t aSource = 0U;
             aSource < kRoleCount;
             ++aSource) {
            const Influence aSourceBit = SourceInfluence(aSource);
            for (const Influence aOrbiter : aOrbiters) {
                aSourceOrbiterArea[aSource] +=
                    (aOrbiter & aSourceBit) != 0U;
            }
        }
    };

    // Preserve the real ordered ARX heart. Destination arrivals are sampled
    // after every complete heart round; source-pair meetings are sampled
    // after each of the two individual data-flow operations.
    RecordOrbiterCopies();
    RecordDestinationArrivals(0);
    RecordMeetings(0);
    int aOperation = 0;
    int aRoundIndex = 0;
    for (const auto &aHeartRound : pHeart.mRounds) {
        aOrbiters[aHeartRound[0]] |= aOrbiters[aHeartRound[1]];
        RecordMeetings(++aOperation);
        aOrbiters[aHeartRound[2]] |= aOrbiters[aHeartRound[0]];
        RecordMeetings(++aOperation);
        RecordOrbiterCopies();
        RecordDestinationArrivals(++aRoundIndex);
    }

    InfluenceSet aDestinationInfluence{};
    InfluenceSet aDualTailInfluence{};
    const bool aMeasureOneRoundFanout =
        ShouldMeasureMetric(pWeightedOnly, 24U) ||
        ShouldMeasureMetric(pWeightedOnly, 25U);
    for (std::size_t aDestination = 0U;
         aDestination < kRoleCount;
         ++aDestination) {
        const Influence aTailA = aOrbiters[
            pTail.mOrbiterAForWanderer[aDestination]];
        const Influence aTailB = aOrbiters[
            pTail.mOrbiterBForWanderer[aDestination]];
        if (aMeasureOneRoundFanout) {
            aDestinationInfluence[aDestination] =
                SourceInfluence(aDestination) | aTailA | aTailB;
        }
        aDualTailInfluence[aDestination] = aTailA & aTailB;
    }

    OrderedJourneyMetrics aResult;
    if (aMeasureOneRoundFanout) {
        aResult.mMinimumOneRoundFanout =
            static_cast<int>(kRoleCount - 1U);
    }
    aResult.mMinimumSourceOrbiterArea =
        std::numeric_limits<int>::max();
    aResult.mMinimumDualTailReach =
        static_cast<int>(kRoleCount - 1U);
    int aFanoutTotal = 0;
    int aDualTailTotal = 0;
    for (std::size_t aSource = 0U;
         aSource < kRoleCount;
         ++aSource) {
        const Influence aSourceBit = SourceInfluence(aSource);
        int aFanout = 0;
        int aDualTailReach = 0;
        for (std::size_t aDestination = 0U;
             aDestination < kRoleCount;
             ++aDestination) {
            if (aDestination == aSource) {
                continue;
            }
            if (aMeasureOneRoundFanout) {
                aFanout +=
                    (aDestinationInfluence[aDestination] & aSourceBit) !=
                    0U;
            }
            aDualTailReach +=
                (aDualTailInfluence[aDestination] & aSourceBit) != 0U;
        }
        if (ShouldMeasureMetric(pWeightedOnly, 24U)) {
            aResult.mMinimumOneRoundFanout = std::min(
                aResult.mMinimumOneRoundFanout, aFanout);
        }
        aResult.mMinimumSourceOrbiterArea = std::min(
            aResult.mMinimumSourceOrbiterArea,
            aSourceOrbiterArea[aSource]);
        aResult.mMinimumDualTailReach = std::min(
            aResult.mMinimumDualTailReach, aDualTailReach);
        if (ShouldMeasureMetric(pWeightedOnly, 25U)) {
            aFanoutTotal += aFanout;
        }
        if (ShouldMeasureMetric(pWeightedOnly, 28U)) {
            aDualTailTotal += aDualTailReach;
        }
    }
    const int aOrderedPairCount =
        static_cast<int>(kRoleCount * (kRoleCount - 1U));
    if (ShouldMeasureMetric(pWeightedOnly, 25U)) {
        aResult.mMeanOneRoundFanoutTimes1000 =
            (aFanoutTotal * 1000) / aOrderedPairCount;
    }
    if (ShouldMeasureMetric(pWeightedOnly, 28U)) {
        aResult.mMeanDualTailReachTimes1000 =
            (aDualTailTotal * 1000) / aOrderedPairCount;
    }

    int aSourceOrphanAreaTotal = 0;
    int aDualTailOrphanAreaTotal = 0;
    std::array<int, kRoleCount> aMidpointDestinationOrphans{};
    std::array<int, kRoleCount> aDestinationOrphanAreas{};
    for (std::size_t aSource = 0U;
         aSource < kRoleCount;
         ++aSource) {
        std::array<int, kRoleCount - 1U> aArrivalList{};
        std::size_t aArrivalIndex = 0U;
        int aSourceOrphanArea = 0;
        int aDualTailOrphanArea = 0;
        int aMidpointSourceOrphans = 0;
        for (std::size_t aDestination = 0U;
             aDestination < kRoleCount;
             ++aDestination) {
            if (aDestination == aSource) {
                continue;
            }
            const int aArrival =
                aDestinationArrivals[aSource][aDestination];
            aArrivalList[aArrivalIndex++] = aArrival;
            aSourceOrphanArea += aArrival;
            aDestinationOrphanAreas[aDestination] += aArrival;
            aDualTailOrphanArea += std::max(
                aTailAArrivals[aSource][aDestination],
                aTailBArrivals[aSource][aDestination]);
            if (ShouldMeasureMetric(pWeightedOnly, 49U) &&
                (aTailAArrivals[aSource][aDestination] <
                    kUnreachedRound) &&
                (aTailBArrivals[aSource][aDestination] <
                    kUnreachedRound)) {
                const int aDualTailArrivalSkew = std::abs(
                    aTailAArrivals[aSource][aDestination] -
                    aTailBArrivals[aSource][aDestination]);
                aResult.mMaximumDualTailArrivalSkew = std::max(
                    aResult.mMaximumDualTailArrivalSkew,
                    aDualTailArrivalSkew);
            }
            if (aArrival > kMidpointRound) {
                ++aMidpointSourceOrphans;
                ++aMidpointDestinationOrphans[aDestination];
            }
        }
        std::sort(aArrivalList.begin(), aArrivalList.end());
        aResult.mMaximumSourceOrphanArea = std::max(
            aResult.mMaximumSourceOrphanArea,
            aSourceOrphanArea);
        if (ShouldMeasureMetric(pWeightedOnly, 32U)) {
            aResult.mMaximumLastOrphanLatency = std::max(
                aResult.mMaximumLastOrphanLatency,
                aArrivalList.back());
        }
        aResult.mMaximumStragglerGap = std::max(
            aResult.mMaximumStragglerGap,
            aArrivalList.back() -
                aArrivalList[aArrivalList.size() - 2U]);
        aResult.mMaximumMidpointSourceOrphans = std::max(
            aResult.mMaximumMidpointSourceOrphans,
            aMidpointSourceOrphans);
        aResult.mMaximumDualTailOrphanArea = std::max(
            aResult.mMaximumDualTailOrphanArea,
            aDualTailOrphanArea);
        if (ShouldMeasureMetric(pWeightedOnly, 31U)) {
            aSourceOrphanAreaTotal += aSourceOrphanArea;
        }
        if (ShouldMeasureMetric(pWeightedOnly, 44U)) {
            aDualTailOrphanAreaTotal += aDualTailOrphanArea;
        }
    }
    if (ShouldMeasureMetric(pWeightedOnly, 31U)) {
        aResult.mMeanSourceOrphanAreaTimes1000 =
            (aSourceOrphanAreaTotal * 1000) /
            static_cast<int>(kRoleCount);
    }
    aResult.mMaximumDestinationOrphanArea =
        *std::max_element(aDestinationOrphanAreas.begin(),
                          aDestinationOrphanAreas.end());
    if (ShouldMeasureMetric(pWeightedOnly, 44U)) {
        aResult.mMeanDualTailOrphanAreaTimes1000 =
            (aDualTailOrphanAreaTotal * 1000) /
            static_cast<int>(kRoleCount);
    }
    aResult.mMaximumMidpointDestinationOrphanLoad =
        *std::max_element(aMidpointDestinationOrphans.begin(),
                          aMidpointDestinationOrphans.end());

    for (std::size_t a = 0U; a < kRoleCount; ++a) {
        for (std::size_t b = a + 1U; b < kRoleCount; ++b) {
            int aCoOrphanLoad = 0;
            for (std::size_t aSource = 0U;
                 aSource < kRoleCount;
                 ++aSource) {
                if ((aSource == a) || (aSource == b)) {
                    continue;
                }
                aCoOrphanLoad +=
                    (aDestinationArrivals[aSource][a] >
                        kMidpointRound) &&
                    (aDestinationArrivals[aSource][b] >
                        kMidpointRound);
            }
            aResult.mMaximumMidpointCoOrphanLoad = std::max(
                aResult.mMaximumMidpointCoOrphanLoad,
                aCoOrphanLoad);
        }
    }

    int aMeetingLatencyTotal = 0;
    for (std::size_t aSource = 0U;
         aSource < kRoleCount;
         ++aSource) {
        int aMeetingOrphans = 0;
        int aSourceMeetingArea = 0;
        for (std::size_t aPartner = 0U;
             aPartner < kRoleCount;
             ++aPartner) {
            if (aPartner == aSource) {
                continue;
            }
            const int aMeeting =
                aMeetingArrivals[aSource][aPartner];
            if (ShouldMeasureMetric(pWeightedOnly, 37U)) {
                aMeetingOrphans += aMeeting == kUnmetOperation;
            }
            aSourceMeetingArea += aMeeting;
            aMeetingLatencyTotal += aMeeting;
        }
        if (ShouldMeasureMetric(pWeightedOnly, 37U)) {
            aResult.mMaximumMeetingOrphans = std::max(
                aResult.mMaximumMeetingOrphans,
                aMeetingOrphans);
        }
        aResult.mMaximumSourceMeetingArea = std::max(
            aResult.mMaximumSourceMeetingArea,
            aSourceMeetingArea);
    }
    aResult.mMeanPairMeetingLatencyTimes1000 =
        (aMeetingLatencyTotal * 1000) / aOrderedPairCount;

    int aRobustOrphanTotal = 0;
    std::array<int, kRoleCount> aRobustDestinationOrphans{};
    std::array<int, kRoleCount> aDamageByRemovedOrbiter{};
    aResult.mMinimumSurvivingFanout =
        static_cast<int>(kRoleCount - 1U);
    for (std::size_t aSource = 0U;
         aSource < kRoleCount;
         ++aSource) {
        const std::size_t aRootOrbiter =
            aOrbiterForWanderer[aSource];
        std::array<bool, kRoleCount> aRelationshipIsRobust{};
        aRelationshipIsRobust.fill(true);
        for (std::size_t aRemoved = 0U;
             aRemoved < kRoleCount;
             ++aRemoved) {
            if (aRemoved == aRootOrbiter) {
                continue;
            }
            std::array<bool, kRoleCount> aReach{};
            aReach[aRootOrbiter] = true;
            for (const auto &aHeartRound : pHeart.mRounds) {
                const std::size_t aLead = aHeartRound[0];
                const std::size_t aHeartSource = aHeartRound[1];
                const std::size_t aFeedback = aHeartRound[2];
                if ((aLead != aRemoved) &&
                    (aHeartSource != aRemoved)) {
                    aReach[aLead] =
                        aReach[aLead] || aReach[aHeartSource];
                }
                if ((aFeedback != aRemoved) &&
                    (aLead != aRemoved)) {
                    aReach[aFeedback] =
                        aReach[aFeedback] || aReach[aLead];
                }
                aReach[aRemoved] = false;
            }

            int aSurvivingFanout = 0;
            for (std::size_t aDestination = 0U;
                 aDestination < kRoleCount;
                 ++aDestination) {
                if (aDestination == aSource) {
                    continue;
                }
                const std::size_t aTailA =
                    pTail.mOrbiterAForWanderer[aDestination];
                const std::size_t aTailB =
                    pTail.mOrbiterBForWanderer[aDestination];
                const bool aReached =
                    ((aTailA != aRemoved) && aReach[aTailA]) ||
                    ((aTailB != aRemoved) && aReach[aTailB]);
                aSurvivingFanout += aReached;
                if (!aReached) {
                    aRelationshipIsRobust[aDestination] = false;
                    ++aDamageByRemovedOrbiter[aRemoved];
                }
            }
            aResult.mMinimumSurvivingFanout = std::min(
                aResult.mMinimumSurvivingFanout,
                aSurvivingFanout);
        }

        int aRobustOrphans = 0;
        for (std::size_t aDestination = 0U;
             aDestination < kRoleCount;
             ++aDestination) {
            if (aDestination == aSource) {
                continue;
            }
            const bool aRobust =
                aRelationshipIsRobust[aDestination];
            aRobustOrphans += !aRobust;
            aRobustDestinationOrphans[aDestination] += !aRobust;
        }
        aResult.mMaximumRobustOrphans = std::max(
            aResult.mMaximumRobustOrphans,
            aRobustOrphans);
        if (ShouldMeasureMetric(pWeightedOnly, 41U)) {
            aRobustOrphanTotal += aRobustOrphans;
        }
    }
    if (ShouldMeasureMetric(pWeightedOnly, 41U)) {
        aResult.mMeanRobustOrphansTimes1000 =
            (aRobustOrphanTotal * 1000) /
            static_cast<int>(kRoleCount);
    }
    aResult.mMaximumRobustDestinationOrphans =
        *std::max_element(aRobustDestinationOrphans.begin(),
                          aRobustDestinationOrphans.end());
    aResult.mMaximumSingleOrbiterDamage =
        *std::max_element(aDamageByRemovedOrbiter.begin(),
                          aDamageByRemovedOrbiter.end());
    if (ShouldMeasureMetric(pWeightedOnly, 47U)) {
        const int aSingleOrbiterDamageTotal = std::accumulate(
            aDamageByRemovedOrbiter.begin(),
            aDamageByRemovedOrbiter.end(),
            0);
        aResult.mMeanSingleOrbiterDamageTimes1000 =
            (aSingleOrbiterDamageTotal * 1000) /
            static_cast<int>(kRoleCount);
    }
    return aResult;
}

struct TailScore {
    int mFirstMinimumWandererInfluence = 0;
    int mFirstMinimumInputCoverage = 0;
    int mSecondMinimumWandererInfluence = 0;
    int mSecondMinimumInputCoverage = 0;
    int mMinimumPairUnion = 0;
    int mMinimumExpansion = 0;
    int mDirectedDiameter = 0;
    int mMeanShortestPathTimes1000 = 0;
    int mWorstMeanShortestPathTimes1000 = 0;
    int mMinimumInfluencedWanderers = 0;
    int mMinimumEarlyReach = 0;
    int mMeanEarlyReachTimes1000 = 0;
    int mRedundantRouteFractionTimes1000 = 0;
    int mPairComponentCount = 0;
    int mMinimumHeartSeparation = 0;
    int mHeartSeparationTotal = 0;
    int mMinimumPairBalance = 0;
    int mMinimumComplement = 0;
    int mDominatedPairCount = 0;
    int mFlowArea = 0;
    int mArrivalTotal = 0;
    int mMaximumArrivalSkew = 0;
    int mExpansionTotal = 0;
    // Preserves the established 50-field binary score layout. No spectral
    // calculation is performed; new records always serialize zero here.
    int mReservedLegacySpectralGap = 0;
    int mMinimumOneRoundFanout = 0;
    int mMeanOneRoundFanoutTimes1000 = 0;
    int mMinimumSourceOrbiterArea = 0;
    int mMinimumDualTailReach = 0;
    int mMeanDualTailReachTimes1000 = 0;
    int mMaximumOrbiterPathLoadTimes1000 = 0;
    int mMaximumSourceOrphanArea = 0;
    int mMeanSourceOrphanAreaTimes1000 = 0;
    int mMaximumLastOrphanLatency = 0;
    int mMaximumStragglerGap = 0;
    int mMaximumMidpointSourceOrphans = 0;
    int mMaximumMidpointDestinationOrphanLoad = 0;
    int mMaximumMidpointCoOrphanLoad = 0;
    int mMaximumMeetingOrphans = 0;
    int mMaximumSourceMeetingArea = 0;
    int mMeanPairMeetingLatencyTimes1000 = 0;
    int mMaximumRobustOrphans = 0;
    int mMeanRobustOrphansTimes1000 = 0;
    int mMaximumDestinationOrphanArea = 0;
    int mMaximumDualTailOrphanArea = 0;
    int mMeanDualTailOrphanAreaTimes1000 = 0;
    int mMaximumRobustDestinationOrphans = 0;
    int mMaximumSingleOrbiterDamage = 0;
    int mMeanSingleOrbiterDamageTimes1000 = 0;
    int mMinimumSurvivingFanout = 0;
    int mMaximumDualTailArrivalSkew = 0;
};

constexpr std::array<const char *, kScoreFieldCount> kRankingMetricNames = {
    "first minimum wanderer influence",
    "first minimum input coverage",
    "second minimum wanderer influence",
    "second minimum input coverage",
    "minimum pair union",
    "minimum heart separation",
    "total heart separation",
    "minimum pair balance",
    "minimum complement",
    "dominated pair count",
    "flow area",
    "arrival total",
    "maximum arrival skew",
    "directed diameter",
    "mean wanderer shortest path x1000",
    "worst wanderer mean shortest path x1000",
    "minimum influenced wanderers",
    "minimum wanderers reached within four edges",
    "mean four-edge wanderer reach x1000",
    "redundant early-branch fraction x1000",
    "pair component count",
    "minimum subset expansion",
    "total subset expansion",
    "reserved legacy spectral gap",
    "minimum one-round wanderer fanout",
    "mean one-round wanderer fanout x1000",
    "minimum source orbiter journey area",
    "minimum dual-tail wanderer reach",
    "mean dual-tail wanderer reach x1000",
    "maximum orbiter shortest-path load x1000",
    "maximum ordered source orphan area",
    "mean ordered source orphan area x1000",
    "maximum last-orphan latency",
    "maximum orphan straggler gap",
    "maximum midpoint source orphans",
    "maximum midpoint destination orphan load",
    "maximum midpoint co-orphan load",
    "maximum source meeting orphans",
    "maximum source meeting area",
    "mean source-pair meeting latency x1000",
    "maximum robust orphans",
    "mean robust orphans x1000",
    "maximum ordered destination orphan area",
    "maximum dual-tail source orphan area",
    "mean dual-tail source orphan area x1000",
    "maximum robust destination orphans",
    "maximum single-orbiter ordered-pair damage",
    "mean single-orbiter ordered-pair damage x1000",
    "minimum surviving fanout after one orbiter removal",
    "maximum dual-tail arrival skew",
};

constexpr std::array<bool, kScoreFieldCount> kRankingHigherIsBetter = {
    true, true, true, true, true, true, true, true, true,
    false, true, false, false, false, false, false,
    true, true, true, true, false, true, true, true,
    true, true, true, true, true, false,
    false, false, false, false, false, false,
    false, false, false, false, false, false,
    false, false, false, false,
    false, false, true, false,
};

struct MetricGate {
    std::size_t mMetric = 0U;
    int mThreshold = 0;
};

// The direction comes from kRankingHigherIsBetter. These are the proposed
// universal gates under investigation; this experiment does not yet promote
// them into the live Ascendency tier policy.
constexpr std::array<MetricGate, 32U> kProposedMustHaveGates = {{
    {33U, 4},     // maximum orphan straggler gap
    {20U, 3},     // pair component count
    {40U, 9},     // maximum robust orphans
    {45U, 9},     // maximum robust destination orphans
    {42U, 69},    // maximum ordered destination orphan area
    {35U, 9},     // maximum midpoint destination orphan load
    {17U, 9},     // minimum wanderers reached within four edges
    {10U, 6280},  // flow area
    {32U, 11},    // maximum last-orphan latency
    {27U, 5},     // minimum dual-tail wanderer reach
    {28U, 863},   // mean dual-tail wanderer reach x1000
    {34U, 9},     // maximum midpoint source orphans
    {48U, 4},     // minimum surviving fanout after one orbiter removal
    {49U, 11},    // maximum dual-tail arrival skew
    {23U, 0},     // reserved legacy spectral gap
    {24U, 10},    // minimum one-round wanderer fanout
    {25U, 1000},  // mean one-round wanderer fanout x1000
    {26U, 29},    // minimum source orbiter journey area
    {0U, 15},     // first minimum wanderer influence
    {1U, 11},     // first minimum input coverage
    {2U, 17},     // second minimum wanderer influence
    {3U, 11},     // second minimum input coverage
    {4U, 15},     // minimum pair union
    {7U, 0},      // minimum pair balance
    {8U, 0},      // minimum complement
    {9U, 11},     // dominated pair count
    {11U, 3894},  // arrival total
    {12U, 24},    // maximum arrival skew
    {16U, 10},    // minimum influenced wanderers
    {37U, 0},     // maximum source meeting orphans
    {38U, 120},   // maximum source meeting area
    {39U, 9545},  // mean source-pair meeting latency x1000
}};

bool PassesMetricThreshold(const int pValue,
                           const std::size_t pMetric,
                           const int pThreshold) {
    return kRankingHigherIsBetter[pMetric]
        ? pValue >= pThreshold
        : pValue <= pThreshold;
}

int MinimumWandererInfluence(const InfluenceSet &pWanderers,
                             const std::size_t pSourceCount) {
    int aResult = static_cast<int>(pSourceCount);
    for (const Influence aInfluence : pWanderers) {
        aResult = std::min(aResult, PopCount(aInfluence));
    }
    return aResult;
}

int MinimumInputCoverage(const InfluenceSet &pWanderers,
                         const std::size_t pSourceCount) {
    int aResult = static_cast<int>(kRoleCount);
    for (std::size_t aSource = 0U;
         aSource < pSourceCount;
         ++aSource) {
        int aCoverage = 0;
        for (const Influence aInfluence : pWanderers) {
            aCoverage +=
                (aInfluence & SourceInfluence(aSource)) != 0U;
        }
        aResult = std::min(aResult, aCoverage);
    }
    return aResult;
}

TailScore ScoreTail(const LoopCorePattern11 &pHeart,
                    const LoopHeadPattern11 &pHead,
                    const LoopTailPattern11 &pTail,
                    const std::size_t pPatternIndex,
                    const PairInfoMatrix &pPairs,
                    const TransitionMetrics &pTransition,
                    const bool pWeightedOnly = false) {
    TailScore aScore;
    aScore.mMinimumPairUnion =
        static_cast<int>(kFirstIterationSourceCount);
    aScore.mMinimumHeartSeparation = kUnreachableDistance;
    aScore.mMinimumPairBalance =
        static_cast<int>(kFirstIterationSourceCount);
    aScore.mMinimumComplement =
        static_cast<int>(kFirstIterationSourceCount);
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const PairInfo &aPair = pPairs[
            pTail.mOrbiterAForWanderer[i]]
            [pTail.mOrbiterBForWanderer[i]];
        if (ShouldMeasureMetric(pWeightedOnly, 4U)) {
            aScore.mMinimumPairUnion = std::min(
                aScore.mMinimumPairUnion, aPair.mUnion);
        }
        if (ShouldMeasureMetric(pWeightedOnly, 5U)) {
            aScore.mMinimumHeartSeparation = std::min(
                aScore.mMinimumHeartSeparation,
                aPair.mHeartSeparation);
        }
        if (ShouldMeasureMetric(pWeightedOnly, 6U)) {
            aScore.mHeartSeparationTotal += aPair.mHeartSeparation;
        }
        if (ShouldMeasureMetric(pWeightedOnly, 7U)) {
            aScore.mMinimumPairBalance = std::min(
                aScore.mMinimumPairBalance,
                std::min(aPair.mOverlap, aPair.mUniqueSide));
        }
        if (ShouldMeasureMetric(pWeightedOnly, 8U)) {
            aScore.mMinimumComplement = std::min(
                aScore.mMinimumComplement, aPair.mComplement);
        }
        if (ShouldMeasureMetric(pWeightedOnly, 9U)) {
            aScore.mDominatedPairCount += aPair.mUniqueSide == 0;
        }
    }

    InfluenceSet aWanderers{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aWanderers[i] = SourceInfluence(i);
    }
    Influence aIngress = SourceInfluence(kInitialIngressSource);
    Influence aCarry = SourceInfluence(kInitialCarrySource);
    ArrivalMatrix aArrivals{};
    const bool aMeasureArrivals =
        ShouldMeasureMetric(pWeightedOnly, 11U) ||
        ShouldMeasureMetric(pWeightedOnly, 12U);
    if (aMeasureArrivals) {
        for (auto &aRow : aArrivals) {
            aRow.fill(-1);
        }
        for (std::size_t i = 0U; i < kRoleCount; ++i) {
            aArrivals[i][i] = 0;
        }
    }

    const IterationResult aFirst = PropagateIteration(
        pHeart, pHead, pTail, pPatternIndex,
        kFirstFreshIngressSource, kFirstFreshCrossSource, 0,
        &aWanderers, &aIngress, &aCarry,
        aMeasureArrivals ? &aArrivals : nullptr);
    if (ShouldMeasureMetric(pWeightedOnly, 0U)) {
        aScore.mFirstMinimumWandererInfluence =
            MinimumWandererInfluence(
                aWanderers, kFirstIterationSourceCount);
    }
    if (ShouldMeasureMetric(pWeightedOnly, 1U)) {
        aScore.mFirstMinimumInputCoverage =
            MinimumInputCoverage(
                aWanderers, kFirstIterationSourceCount);
    }

    const IterationResult aSecond = PropagateIteration(
        pHeart, pHead, pTail, pPatternIndex,
        kSecondFreshIngressSource, kSecondFreshCrossSource,
        kFlowStepsPerIteration,
        &aWanderers, &aIngress, &aCarry,
        aMeasureArrivals ? &aArrivals : nullptr);
    if (ShouldMeasureMetric(pWeightedOnly, 2U)) {
        aScore.mSecondMinimumWandererInfluence =
            MinimumWandererInfluence(aWanderers, kSourceCount);
    }
    if (ShouldMeasureMetric(pWeightedOnly, 3U)) {
        aScore.mSecondMinimumInputCoverage =
            MinimumInputCoverage(aWanderers, kSourceCount);
    }
    aScore.mFlowArea = aFirst.mFlowArea + aSecond.mFlowArea;

    constexpr int kMissingArrival =
        (2 * kFlowStepsPerIteration) + 1;
    if (aMeasureArrivals) {
        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            int aMinimum = kMissingArrival;
            int aMaximum = 0;
            for (std::size_t aWanderer = 0U;
                 aWanderer < kRoleCount;
                 ++aWanderer) {
                const int aArrival =
                    aArrivals[aWanderer][aSource] >= 0
                        ? aArrivals[aWanderer][aSource]
                        : kMissingArrival;
                aMinimum = std::min(aMinimum, aArrival);
                aMaximum = std::max(aMaximum, aArrival);
                if (ShouldMeasureMetric(pWeightedOnly, 11U)) {
                    aScore.mArrivalTotal += aArrival;
                }
            }
            if (ShouldMeasureMetric(pWeightedOnly, 12U)) {
                aScore.mMaximumArrivalSkew = std::max(
                    aScore.mMaximumArrivalSkew,
                    aMaximum - aMinimum);
            }
        }
    }

    if (ShouldMeasureMetric(pWeightedOnly, 21U)) {
        aScore.mMinimumExpansion = pTransition.mMinimumExpansion;
    }
    if (ShouldMeasureMetric(pWeightedOnly, 13U)) {
        aScore.mDirectedDiameter = pTransition.mDirectedDiameter;
    }
    const WandererPathMetrics aPaths = MeasureWandererPaths(
        pHeart, pHead, pTail, pWeightedOnly);
    aScore.mMeanShortestPathTimes1000 =
        aPaths.mMeanShortestPathTimes1000;
    aScore.mWorstMeanShortestPathTimes1000 =
        aPaths.mWorstMeanShortestPathTimes1000;
    aScore.mMinimumInfluencedWanderers =
        aPaths.mMinimumInfluencedWanderers;
    aScore.mMinimumEarlyReach = aPaths.mMinimumEarlyReach;
    aScore.mMeanEarlyReachTimes1000 =
        aPaths.mMeanEarlyReachTimes1000;
    aScore.mRedundantRouteFractionTimes1000 =
        aPaths.mRedundantRouteFractionTimes1000;
    aScore.mMaximumOrbiterPathLoadTimes1000 =
        aPaths.mMaximumOrbiterPathLoadTimes1000;
    const OrderedJourneyMetrics aJourney = MeasureOrderedJourney(
        pHeart, pHead, pTail, pWeightedOnly);
    aScore.mMinimumOneRoundFanout =
        aJourney.mMinimumOneRoundFanout;
    aScore.mMeanOneRoundFanoutTimes1000 =
        aJourney.mMeanOneRoundFanoutTimes1000;
    aScore.mMinimumSourceOrbiterArea =
        aJourney.mMinimumSourceOrbiterArea;
    aScore.mMinimumDualTailReach =
        aJourney.mMinimumDualTailReach;
    aScore.mMeanDualTailReachTimes1000 =
        aJourney.mMeanDualTailReachTimes1000;
    aScore.mMaximumSourceOrphanArea =
        aJourney.mMaximumSourceOrphanArea;
    aScore.mMeanSourceOrphanAreaTimes1000 =
        aJourney.mMeanSourceOrphanAreaTimes1000;
    aScore.mMaximumLastOrphanLatency =
        aJourney.mMaximumLastOrphanLatency;
    aScore.mMaximumStragglerGap =
        aJourney.mMaximumStragglerGap;
    aScore.mMaximumMidpointSourceOrphans =
        aJourney.mMaximumMidpointSourceOrphans;
    aScore.mMaximumMidpointDestinationOrphanLoad =
        aJourney.mMaximumMidpointDestinationOrphanLoad;
    aScore.mMaximumMidpointCoOrphanLoad =
        aJourney.mMaximumMidpointCoOrphanLoad;
    aScore.mMaximumMeetingOrphans =
        aJourney.mMaximumMeetingOrphans;
    aScore.mMaximumSourceMeetingArea =
        aJourney.mMaximumSourceMeetingArea;
    aScore.mMeanPairMeetingLatencyTimes1000 =
        aJourney.mMeanPairMeetingLatencyTimes1000;
    aScore.mMaximumRobustOrphans =
        aJourney.mMaximumRobustOrphans;
    aScore.mMeanRobustOrphansTimes1000 =
        aJourney.mMeanRobustOrphansTimes1000;
    aScore.mMaximumDestinationOrphanArea =
        aJourney.mMaximumDestinationOrphanArea;
    aScore.mMaximumDualTailOrphanArea =
        aJourney.mMaximumDualTailOrphanArea;
    aScore.mMeanDualTailOrphanAreaTimes1000 =
        aJourney.mMeanDualTailOrphanAreaTimes1000;
    aScore.mMaximumRobustDestinationOrphans =
        aJourney.mMaximumRobustDestinationOrphans;
    aScore.mMaximumSingleOrbiterDamage =
        aJourney.mMaximumSingleOrbiterDamage;
    aScore.mMeanSingleOrbiterDamageTimes1000 =
        aJourney.mMeanSingleOrbiterDamageTimes1000;
    aScore.mMinimumSurvivingFanout =
        aJourney.mMinimumSurvivingFanout;
    aScore.mMaximumDualTailArrivalSkew =
        aJourney.mMaximumDualTailArrivalSkew;
    if (ShouldMeasureMetric(pWeightedOnly, 20U)) {
        aScore.mPairComponentCount = PairComponentCount(pTail);
    }
    if (ShouldMeasureMetric(pWeightedOnly, 22U)) {
        aScore.mExpansionTotal = pTransition.mExpansionTotal;
    }
    return aScore;
}

constexpr std::size_t kExplorationRankingMetricCount = 5U;
constexpr std::size_t kSafeRankingMetricCount = 4U;

constexpr std::array<const char *, kExplorationRankingMetricCount>
kExplorationRankingMetricNames = {
    "minimum pair union",
    "minimum dual-tail wanderer reach",
    "minimum wanderers reached within four edges",
    "minimum complement",
    "dominated pair count",
};

constexpr std::array<bool, kExplorationRankingMetricCount>
kExplorationRankingHigherIsBetter = {
    true, true, true, true, false,
};

constexpr std::array<const char *, kSafeRankingMetricCount>
kSafeRankingMetricNames = {
    "maximum single-orbiter ordered-pair damage",
    "minimum surviving fanout after one orbiter removal",
    "minimum dual-tail wanderer reach",
    "maximum ordered source orphan area",
};

constexpr std::array<bool, kSafeRankingMetricCount>
kSafeRankingHigherIsBetter = {
    false, true, true, false,
};

std::array<int, kExplorationRankingMetricCount>
ExplorationRankingValues(const TailScore &pScore) {
    return {
        pScore.mMinimumPairUnion,
        pScore.mMinimumDualTailReach,
        pScore.mMinimumEarlyReach,
        pScore.mMinimumComplement,
        -pScore.mDominatedPairCount,
    };
}

std::array<int, kSafeRankingMetricCount>
SafeRankingValues(const TailScore &pScore) {
    return {
        -pScore.mMaximumSingleOrbiterDamage,
        pScore.mMinimumSurvivingFanout,
        pScore.mMinimumDualTailReach,
        -pScore.mMaximumSourceOrphanArea,
    };
}

std::array<int, kSafeRankingMetricCount>
SafeRankingDisplayValues(const TailScore &pScore) {
    return {
        pScore.mMaximumSingleOrbiterDamage,
        pScore.mMinimumSurvivingFanout,
        pScore.mMinimumDualTailReach,
        pScore.mMaximumSourceOrphanArea,
    };
}

bool ExplorationScoreIsBetter(const TailScore &pA,
                              const TailScore &pB) {
    return ExplorationRankingValues(pA) > ExplorationRankingValues(pB);
}

bool SafeScoreIsBetter(const TailScore &pA,
                       const TailScore &pB) {
    return SafeRankingValues(pA) > SafeRankingValues(pB);
}

struct Candidate {
    LoopTailPattern11 mTail;
    TailScore mScore;
    std::string mKey;
};

bool CandidateIsBetterForPhase(const Candidate &pA,
                               const Candidate &pB,
                               const PoolPhase pPhase) {
    const bool aIsBetter = pPhase == PoolPhase::kExploration
        ? ExplorationScoreIsBetter(pA.mScore, pB.mScore)
        : SafeScoreIsBetter(pA.mScore, pB.mScore);
    const bool bIsBetter = pPhase == PoolPhase::kExploration
        ? ExplorationScoreIsBetter(pB.mScore, pA.mScore)
        : SafeScoreIsBetter(pB.mScore, pA.mScore);
    if (aIsBetter) {
        return true;
    }
    if (bIsBetter) {
        return false;
    }
    return pA.mKey < pB.mKey;
}

bool ExplorationCandidateIsBetter(const Candidate &pA,
                                  const Candidate &pB) {
    return CandidateIsBetterForPhase(
        pA, pB, PoolPhase::kExploration);
}

bool SafeCandidateIsBetter(const Candidate &pA,
                           const Candidate &pB) {
    return CandidateIsBetterForPhase(pA, pB, PoolPhase::kSafe);
}

struct BetterExplorationCandidateComparator {
    bool operator()(const Candidate &pA,
                    const Candidate &pB) const {
        // A "better" comparator makes priority_queue::top() the worst
        // retained candidate, which is the one replaced by a stronger tail.
        return ExplorationCandidateIsBetter(pA, pB);
    }
};

std::array<int, kScoreFieldCount> ScoreValues(
    const TailScore &pScore) {
    return {
        pScore.mFirstMinimumWandererInfluence,
        pScore.mFirstMinimumInputCoverage,
        pScore.mSecondMinimumWandererInfluence,
        pScore.mSecondMinimumInputCoverage,
        pScore.mMinimumPairUnion,
        pScore.mMinimumExpansion,
        pScore.mDirectedDiameter,
        pScore.mPairComponentCount,
        pScore.mMinimumHeartSeparation,
        pScore.mHeartSeparationTotal,
        pScore.mMinimumPairBalance,
        pScore.mMinimumComplement,
        pScore.mDominatedPairCount,
        pScore.mFlowArea,
        pScore.mArrivalTotal,
        pScore.mMaximumArrivalSkew,
        pScore.mExpansionTotal,
        pScore.mReservedLegacySpectralGap,
        pScore.mMeanShortestPathTimes1000,
        pScore.mWorstMeanShortestPathTimes1000,
        pScore.mMinimumInfluencedWanderers,
        pScore.mMinimumEarlyReach,
        pScore.mMeanEarlyReachTimes1000,
        pScore.mRedundantRouteFractionTimes1000,
        pScore.mMinimumOneRoundFanout,
        pScore.mMeanOneRoundFanoutTimes1000,
        pScore.mMinimumSourceOrbiterArea,
        pScore.mMinimumDualTailReach,
        pScore.mMeanDualTailReachTimes1000,
        pScore.mMaximumOrbiterPathLoadTimes1000,
        pScore.mMaximumSourceOrphanArea,
        pScore.mMeanSourceOrphanAreaTimes1000,
        pScore.mMaximumLastOrphanLatency,
        pScore.mMaximumStragglerGap,
        pScore.mMaximumMidpointSourceOrphans,
        pScore.mMaximumMidpointDestinationOrphanLoad,
        pScore.mMaximumMidpointCoOrphanLoad,
        pScore.mMaximumMeetingOrphans,
        pScore.mMaximumSourceMeetingArea,
        pScore.mMeanPairMeetingLatencyTimes1000,
        pScore.mMaximumRobustOrphans,
        pScore.mMeanRobustOrphansTimes1000,
        pScore.mMaximumDestinationOrphanArea,
        pScore.mMaximumDualTailOrphanArea,
        pScore.mMeanDualTailOrphanAreaTimes1000,
        pScore.mMaximumRobustDestinationOrphans,
        pScore.mMaximumSingleOrbiterDamage,
        pScore.mMeanSingleOrbiterDamageTimes1000,
        pScore.mMinimumSurvivingFanout,
        pScore.mMaximumDualTailArrivalSkew,
    };
}

void AppendScore(std::vector<std::uint8_t> *pBytes,
                 const TailScore &pScore) {
    for (const int aValue : ScoreValues(pScore)) {
        Append32(pBytes, static_cast<std::uint32_t>(aValue));
    }
}

TailScore ReadScore(const std::vector<std::uint8_t> &pBytes,
                    std::size_t *pOffset) {
    std::array<int, kScoreFieldCount> aValues{};
    for (int &aValue : aValues) {
        aValue = static_cast<int>(Read32(pBytes, pOffset));
    }
    TailScore aScore;
    aScore.mFirstMinimumWandererInfluence = aValues[0];
    aScore.mFirstMinimumInputCoverage = aValues[1];
    aScore.mSecondMinimumWandererInfluence = aValues[2];
    aScore.mSecondMinimumInputCoverage = aValues[3];
    aScore.mMinimumPairUnion = aValues[4];
    aScore.mMinimumExpansion = aValues[5];
    aScore.mDirectedDiameter = aValues[6];
    aScore.mPairComponentCount = aValues[7];
    aScore.mMinimumHeartSeparation = aValues[8];
    aScore.mHeartSeparationTotal = aValues[9];
    aScore.mMinimumPairBalance = aValues[10];
    aScore.mMinimumComplement = aValues[11];
    aScore.mDominatedPairCount = aValues[12];
    aScore.mFlowArea = aValues[13];
    aScore.mArrivalTotal = aValues[14];
    aScore.mMaximumArrivalSkew = aValues[15];
    aScore.mExpansionTotal = aValues[16];
    aScore.mReservedLegacySpectralGap = aValues[17];
    aScore.mMeanShortestPathTimes1000 = aValues[18];
    aScore.mWorstMeanShortestPathTimes1000 = aValues[19];
    aScore.mMinimumInfluencedWanderers = aValues[20];
    aScore.mMinimumEarlyReach = aValues[21];
    aScore.mMeanEarlyReachTimes1000 = aValues[22];
    aScore.mRedundantRouteFractionTimes1000 = aValues[23];
    aScore.mMinimumOneRoundFanout = aValues[24];
    aScore.mMeanOneRoundFanoutTimes1000 = aValues[25];
    aScore.mMinimumSourceOrbiterArea = aValues[26];
    aScore.mMinimumDualTailReach = aValues[27];
    aScore.mMeanDualTailReachTimes1000 = aValues[28];
    aScore.mMaximumOrbiterPathLoadTimes1000 = aValues[29];
    aScore.mMaximumSourceOrphanArea = aValues[30];
    aScore.mMeanSourceOrphanAreaTimes1000 = aValues[31];
    aScore.mMaximumLastOrphanLatency = aValues[32];
    aScore.mMaximumStragglerGap = aValues[33];
    aScore.mMaximumMidpointSourceOrphans = aValues[34];
    aScore.mMaximumMidpointDestinationOrphanLoad = aValues[35];
    aScore.mMaximumMidpointCoOrphanLoad = aValues[36];
    aScore.mMaximumMeetingOrphans = aValues[37];
    aScore.mMaximumSourceMeetingArea = aValues[38];
    aScore.mMeanPairMeetingLatencyTimes1000 = aValues[39];
    aScore.mMaximumRobustOrphans = aValues[40];
    aScore.mMeanRobustOrphansTimes1000 = aValues[41];
    aScore.mMaximumDestinationOrphanArea = aValues[42];
    aScore.mMaximumDualTailOrphanArea = aValues[43];
    aScore.mMeanDualTailOrphanAreaTimes1000 = aValues[44];
    aScore.mMaximumRobustDestinationOrphans = aValues[45];
    aScore.mMaximumSingleOrbiterDamage = aValues[46];
    aScore.mMeanSingleOrbiterDamageTimes1000 = aValues[47];
    aScore.mMinimumSurvivingFanout = aValues[48];
    aScore.mMaximumDualTailArrivalSkew = aValues[49];
    return aScore;
}

using TailPools = std::vector<std::vector<Candidate>>;

bool SaveCorePool(const std::string &pPoolFolderPath,
                  const std::size_t pHeartIndex,
                  const PoolMetadata &pMetadata,
                  const TailPools &pPools,
                  std::string *pErrorMessage) {
    if (pPools.size() != LoopHeadFarmer::kPatternsPerCore) {
        SetError(pErrorMessage,
                 "Loop tail pool did not contain exactly 110 heads");
        return false;
    }
    for (const auto &aPool : pPools) {
        if (aPool.size() != pMetadata.mRetainedPerPair) {
            SetError(pErrorMessage,
                     "Loop tail pool had an incomplete retained set");
            return false;
        }
    }

    const std::size_t aRecordCount =
        LoopHeadFarmer::kPatternsPerCore * pMetadata.mRetainedPerPair;
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kPoolFileHeaderByteCount +
                   (aRecordCount * kPoolRecordByteCount));
    aBytes.insert(aBytes.end(),
                  kPoolFileMagic.begin(), kPoolFileMagic.end());
    Append32(&aBytes, kPoolFileVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(kRoleCount));
    Append32(&aBytes, static_cast<std::uint32_t>(pMetadata.mPhase));
    Append32(&aBytes, static_cast<std::uint32_t>(pHeartIndex));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopHeadFarmer::kPatternsPerCore));
    Append32(&aBytes, static_cast<std::uint32_t>(
        pMetadata.mRetainedPerPair));
    Append32(&aBytes, static_cast<std::uint32_t>(aRecordCount));
    Append32(&aBytes, static_cast<std::uint32_t>(kScoreFieldCount));
    Append32(&aBytes, static_cast<std::uint32_t>(kPoolRecordByteCount));
    Append64(&aBytes, pMetadata.mExplorationCasesPerPair);
    Append32(&aBytes, static_cast<std::uint32_t>(
        pMetadata.mParentRetainedPerPair));

    for (const auto &aPool : pPools) {
        for (const Candidate &aCandidate : aPool) {
            aBytes.insert(aBytes.end(),
                          aCandidate.mTail.mOrbiterAForWanderer.begin(),
                          aCandidate.mTail.mOrbiterAForWanderer.end());
            aBytes.insert(aBytes.end(),
                          aCandidate.mTail.mOrbiterBForWanderer.begin(),
                          aCandidate.mTail.mOrbiterBForWanderer.end());
            AppendScore(&aBytes, aCandidate.mScore);
        }
    }

    const std::string aPath = PoolFilePath(
        pPoolFolderPath, pHeartIndex);
    if (!FileIO::Save(aPath, aBytes)) {
        SetError(pErrorMessage,
                 "Loop tail farmer could not save " + aPath);
        return false;
    }
    return true;
}

bool LoadCorePool(const std::string &pPoolFolderPath,
                  const std::size_t pExpectedHeartIndex,
                  const PoolMetadata &pExpectedMetadata,
                  TailPools *pPools,
                  std::string *pErrorMessage) {
    const std::string aPath = PoolFilePath(
        pPoolFolderPath, pExpectedHeartIndex);
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(aPath, aBytes) ||
        (aBytes.size() < kPoolFileHeaderByteCount) ||
        !std::equal(kPoolFileMagic.begin(), kPoolFileMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Loop tail farmer could not load pool " + aPath);
        return false;
    }

    std::size_t aOffset = kPoolFileMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    const std::uint32_t aRoleCount = Read32(aBytes, &aOffset);
    const std::uint32_t aPhase = Read32(aBytes, &aOffset);
    const std::uint32_t aHeartIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aHeadCount = Read32(aBytes, &aOffset);
    const std::uint32_t aRetainedCount = Read32(aBytes, &aOffset);
    const std::uint32_t aRecordCount = Read32(aBytes, &aOffset);
    const std::uint32_t aScoreFieldCount = Read32(aBytes, &aOffset);
    const std::uint32_t aRecordByteCount = Read32(aBytes, &aOffset);
    const std::uint64_t aExplorationCases = Read64(aBytes, &aOffset);
    const std::uint32_t aParentRetainedCount =
        Read32(aBytes, &aOffset);
    const std::size_t aExpectedRecordCount =
        LoopHeadFarmer::kPatternsPerCore *
        pExpectedMetadata.mRetainedPerPair;
    const std::size_t aExpectedByteCount =
        kPoolFileHeaderByteCount +
        (aExpectedRecordCount * kPoolRecordByteCount);
    if ((aVersion != kPoolFileVersion) ||
        (aRoleCount != kRoleCount) ||
        (aPhase != static_cast<std::uint32_t>(pExpectedMetadata.mPhase)) ||
        (aHeartIndex != pExpectedHeartIndex) ||
        (aHeadCount != LoopHeadFarmer::kPatternsPerCore) ||
        (aRetainedCount != pExpectedMetadata.mRetainedPerPair) ||
        (aRecordCount != aExpectedRecordCount) ||
        (aScoreFieldCount != kScoreFieldCount) ||
        (aRecordByteCount != kPoolRecordByteCount) ||
        (aExplorationCases !=
         pExpectedMetadata.mExplorationCasesPerPair) ||
        (aParentRetainedCount !=
         pExpectedMetadata.mParentRetainedPerPair) ||
        (aBytes.size() != aExpectedByteCount)) {
        SetError(pErrorMessage,
                 "Loop tail pool metadata did not match the current farm");
        return false;
    }

    pPools->assign(LoopHeadFarmer::kPatternsPerCore, {});
    for (auto &aPool : *pPools) {
        aPool.reserve(pExpectedMetadata.mRetainedPerPair);
        for (std::size_t i = 0U;
             i < pExpectedMetadata.mRetainedPerPair;
             ++i) {
            Candidate aCandidate;
            for (std::uint8_t &aValue :
                 aCandidate.mTail.mOrbiterAForWanderer) {
                aValue = aBytes[aOffset++];
            }
            for (std::uint8_t &aValue :
                 aCandidate.mTail.mOrbiterBForWanderer) {
                aValue = aBytes[aOffset++];
            }
            aCandidate.mScore = ReadScore(aBytes, &aOffset);
            aCandidate.mKey = TailKey(aCandidate.mTail);
            if (!IsTailPermutation(aCandidate.mTail)) {
                SetError(pErrorMessage,
                         "Loop tail pool contained an invalid tail record");
                return false;
            }
            if (!aPool.empty() &&
                CandidateIsBetterForPhase(
                    aCandidate,
                    aPool.back(),
                    pExpectedMetadata.mPhase)) {
                SetError(pErrorMessage,
                         "Loop tail pool records were not in score order");
                return false;
            }
            aPool.push_back(std::move(aCandidate));
        }
    }
    return true;
}

bool Save(const std::string &pPath,
          const std::vector<LoopTailPattern11> &pTails,
          std::string *pErrorMessage) {
    if (pTails.size() != LoopHeadFarmer::kRetainedPatternCount) {
        SetError(pErrorMessage,
                 "Loop tail farmer did not produce exactly 19,800 tails");
        return false;
    }

    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kFileHeaderByteCount +
                   (pTails.size() * kPatternByteCount));
    aBytes.insert(aBytes.end(),
                  kFileMagic.begin(), kFileMagic.end());
    Append32(&aBytes, kFileVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(kRoleCount));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopHeadFarmer::kCoreCount));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopHeadFarmer::kPatternsPerCore));
    Append32(&aBytes, static_cast<std::uint32_t>(pTails.size()));
    Append32(&aBytes, static_cast<std::uint32_t>(kPatternByteCount));
    for (const LoopTailPattern11 &aTail : pTails) {
        aBytes.insert(aBytes.end(),
                      aTail.mOrbiterAForWanderer.begin(),
                      aTail.mOrbiterAForWanderer.end());
        aBytes.insert(aBytes.end(),
                      aTail.mOrbiterBForWanderer.begin(),
                      aTail.mOrbiterBForWanderer.end());
    }

    const std::string aPath = ResolvedPath(pPath);
    if (!FileIO::Save(aPath, aBytes)) {
        SetError(pErrorMessage,
                 "Loop tail farmer could not save " + aPath);
        return false;
    }
    std::printf("Loop tail farmer wrote %zu tails to %s (%zu bytes)\n",
                pTails.size(), aPath.c_str(), aBytes.size());
    return true;
}

struct PackedTail {
    std::uint64_t mLow = 0ULL;
    std::uint64_t mHigh = 0ULL;
};

PackedTail PackTail(const LoopTailPattern11 &pTail) {
    PackedTail aPacked;
    std::size_t aPosition = 0U;
    const auto PackValue = [&aPacked, &aPosition](
        const std::uint8_t pValue) {
        std::uint64_t &aWord = aPosition < 16U
            ? aPacked.mLow : aPacked.mHigh;
        const std::size_t aWordPosition = aPosition & 15U;
        aWord |= static_cast<std::uint64_t>(pValue) <<
            (aWordPosition * 4U);
        ++aPosition;
    };
    for (const std::uint8_t aValue :
         pTail.mOrbiterAForWanderer) {
        PackValue(aValue);
    }
    for (const std::uint8_t aValue :
         pTail.mOrbiterBForWanderer) {
        PackValue(aValue);
    }
    return aPacked;
}

int NonZeroNibbleCount(std::uint64_t pValue) {
    pValue |= pValue >> 1U;
    pValue |= pValue >> 2U;
    return __builtin_popcountll(pValue & 0x1111111111111111ULL);
}

int TailDistance(const PackedTail &pA,
                 const PackedTail &pB) {
    return NonZeroNibbleCount(pA.mLow ^ pB.mLow) +
           NonZeroNibbleCount(pA.mHigh ^ pB.mHigh);
}

bool SelectDiverseTails(
    const std::string &pPoolFolderPath,
    const std::string &pTailPatternPath,
    const PoolMetadata &pMetadata,
    std::string *pErrorMessage) {
    std::vector<LoopTailPattern11> aSelectedTails;
    aSelectedTails.reserve(LoopHeadFarmer::kRetainedPatternCount);
    std::vector<PackedTail> aSelectedPacked;
    aSelectedPacked.reserve(LoopHeadFarmer::kRetainedPatternCount);
    std::unordered_set<std::string> aSelectedKeys;
    aSelectedKeys.reserve(LoopHeadFarmer::kRetainedPatternCount * 2U);

    int aMinimumSelectedDistance = static_cast<int>(kPatternByteCount);
    int aMaximumSelectedDistance = 0;
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < LoopHeadFarmer::kCoreCount;
         ++aHeartIndex) {
        TailPools aPools;
        if (!LoadCorePool(pPoolFolderPath,
                          aHeartIndex,
                          pMetadata,
                          &aPools,
                          pErrorMessage)) {
            return false;
        }

        for (const auto &aPool : aPools) {
            std::size_t aBestIndex = 0U;
            int aBestMinimumDistance = -1;
            std::uint64_t aBestTotalDistance = 0ULL;
            for (std::size_t aCandidateIndex = 0U;
                 aCandidateIndex < aPool.size();
                 ++aCandidateIndex) {
                const Candidate &aCandidate = aPool[aCandidateIndex];
                const PackedTail aPacked = PackTail(aCandidate.mTail);
                int aMinimumDistance = static_cast<int>(kPatternByteCount);
                std::uint64_t aTotalDistance = 0ULL;
                bool aCannotWin = false;
                for (const PackedTail &aPrevious : aSelectedPacked) {
                    const int aDistance = TailDistance(aPacked, aPrevious);
                    aMinimumDistance = std::min(
                        aMinimumDistance, aDistance);
                    if (aMinimumDistance < aBestMinimumDistance) {
                        aCannotWin = true;
                        break;
                    }
                    aTotalDistance += static_cast<std::uint64_t>(aDistance);
                }
                if (aCannotWin) {
                    continue;
                }

                const bool aBetterDistance =
                    aMinimumDistance > aBestMinimumDistance;
                const bool aBetterTotal =
                    (aMinimumDistance == aBestMinimumDistance) &&
                    (aTotalDistance > aBestTotalDistance);
                const bool aBetterFlow =
                    (aMinimumDistance == aBestMinimumDistance) &&
                    (aTotalDistance == aBestTotalDistance) &&
                    SafeCandidateIsBetter(
                        aCandidate, aPool[aBestIndex]);
                if (aBetterDistance || aBetterTotal || aBetterFlow) {
                    aBestIndex = aCandidateIndex;
                    aBestMinimumDistance = aMinimumDistance;
                    aBestTotalDistance = aTotalDistance;
                }
            }

            const Candidate &aChosen = aPool[aBestIndex];
            if (!aSelectedKeys.insert(aChosen.mKey).second) {
                SetError(pErrorMessage,
                         "Tail diversity selection exhausted a pool without a unique tail");
                return false;
            }
            aSelectedTails.push_back(aChosen.mTail);
            aSelectedPacked.push_back(PackTail(aChosen.mTail));
            if (aSelectedTails.size() > 1U) {
                aMinimumSelectedDistance = std::min(
                    aMinimumSelectedDistance, aBestMinimumDistance);
                aMaximumSelectedDistance = std::max(
                    aMaximumSelectedDistance, aBestMinimumDistance);
            }
        }
        std::printf("Final processed heart %zu/%zu; selected=%zu/%zu\n",
                    aHeartIndex + 1U,
                    LoopHeadFarmer::kCoreCount,
                    aSelectedTails.size(),
                    LoopHeadFarmer::kRetainedPatternCount);
    }

    if (!Save(pTailPatternPath, aSelectedTails, pErrorMessage)) {
        return false;
    }
    std::printf("Final tail diversity: canonical minimum-distance range="
                "%d..%d across %zu selected tails\n",
                aMinimumSelectedDistance,
                aMaximumSelectedDistance,
                aSelectedTails.size());
    return true;
}

void PrintTail(const char *pLabel,
               const Candidate &pCandidate) {
    std::printf("  %s A={", pLabel);
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        std::printf("%c%s",
                    static_cast<char>('A' +
                        pCandidate.mTail.mOrbiterAForWanderer[i]),
                    (i + 1U) == kRoleCount ? "" : ",");
    }
    std::printf("} B={");
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        std::printf("%c%s",
                    static_cast<char>('A' +
                        pCandidate.mTail.mOrbiterBForWanderer[i]),
                    (i + 1U) == kRoleCount ? "" : ",");
    }
    std::printf("}\n");
    std::printf("       flow: first=%d/%d second=%d/%d union=%d "
                "arrival=%d skew=%d\n",
                pCandidate.mScore.mFirstMinimumWandererInfluence,
                pCandidate.mScore.mFirstMinimumInputCoverage,
                pCandidate.mScore.mSecondMinimumWandererInfluence,
                pCandidate.mScore.mSecondMinimumInputCoverage,
                pCandidate.mScore.mMinimumPairUnion,
                pCandidate.mScore.mArrivalTotal,
                pCandidate.mScore.mMaximumArrivalSkew);
    std::printf("       graph: expansion=%d total=%d diameter=%d "
                "mean_path=%d.%03d worst_mean_path=%d.%03d "
                "influenced=%d early=%d/%d.%03d redundant=%d.%03d "
                "components=%d\n"
                "       journey: one_round=%d/%d.%03d "
                "orbiter_area=%d dual_tail=%d/%d.%03d "
                "max_path_load=%d.%03d\n",
                pCandidate.mScore.mMinimumExpansion,
                pCandidate.mScore.mExpansionTotal,
                pCandidate.mScore.mDirectedDiameter,
                pCandidate.mScore.mMeanShortestPathTimes1000 / 1000,
                pCandidate.mScore.mMeanShortestPathTimes1000 % 1000,
                pCandidate.mScore.mWorstMeanShortestPathTimes1000 / 1000,
                pCandidate.mScore.mWorstMeanShortestPathTimes1000 % 1000,
                pCandidate.mScore.mMinimumInfluencedWanderers,
                pCandidate.mScore.mMinimumEarlyReach,
                pCandidate.mScore.mMeanEarlyReachTimes1000 / 1000,
                pCandidate.mScore.mMeanEarlyReachTimes1000 % 1000,
                pCandidate.mScore.mRedundantRouteFractionTimes1000 / 1000,
                pCandidate.mScore.mRedundantRouteFractionTimes1000 % 1000,
                pCandidate.mScore.mPairComponentCount,
                pCandidate.mScore.mMinimumOneRoundFanout,
                pCandidate.mScore.mMeanOneRoundFanoutTimes1000 / 1000,
                pCandidate.mScore.mMeanOneRoundFanoutTimes1000 % 1000,
                pCandidate.mScore.mMinimumSourceOrbiterArea,
                pCandidate.mScore.mMinimumDualTailReach,
                pCandidate.mScore.mMeanDualTailReachTimes1000 / 1000,
                pCandidate.mScore.mMeanDualTailReachTimes1000 % 1000,
                pCandidate.mScore.mMaximumOrbiterPathLoadTimes1000 / 1000,
                pCandidate.mScore.mMaximumOrbiterPathLoadTimes1000 % 1000);
    std::printf("       orphan: source_area=%d/%d.%03d last=%d "
                "straggler=%d midpoint=%d/%d co=%d\n"
                "       meeting: orphans=%d area=%d mean=%d.%03d "
                "robust_orphans=%d/%d.%03d\n"
                "       relation: destination_area=%d "
                "dual_tail_area=%d/%d.%03d robust_destination=%d\n"
                "       cut: maximum_damage=%d mean_damage=%d.%03d "
                "minimum_fanout=%d dual_tail_skew=%d\n",
                pCandidate.mScore.mMaximumSourceOrphanArea,
                pCandidate.mScore.mMeanSourceOrphanAreaTimes1000 / 1000,
                pCandidate.mScore.mMeanSourceOrphanAreaTimes1000 % 1000,
                pCandidate.mScore.mMaximumLastOrphanLatency,
                pCandidate.mScore.mMaximumStragglerGap,
                pCandidate.mScore.mMaximumMidpointSourceOrphans,
                pCandidate.mScore.mMaximumMidpointDestinationOrphanLoad,
                pCandidate.mScore.mMaximumMidpointCoOrphanLoad,
                pCandidate.mScore.mMaximumMeetingOrphans,
                pCandidate.mScore.mMaximumSourceMeetingArea,
                pCandidate.mScore.mMeanPairMeetingLatencyTimes1000 / 1000,
                pCandidate.mScore.mMeanPairMeetingLatencyTimes1000 % 1000,
                pCandidate.mScore.mMaximumRobustOrphans,
                pCandidate.mScore.mMeanRobustOrphansTimes1000 / 1000,
                pCandidate.mScore.mMeanRobustOrphansTimes1000 % 1000,
                pCandidate.mScore.mMaximumDestinationOrphanArea,
                pCandidate.mScore.mMaximumDualTailOrphanArea,
                pCandidate.mScore.mMeanDualTailOrphanAreaTimes1000 / 1000,
                pCandidate.mScore.mMeanDualTailOrphanAreaTimes1000 % 1000,
                pCandidate.mScore.mMaximumRobustDestinationOrphans,
                pCandidate.mScore.mMaximumSingleOrbiterDamage,
                pCandidate.mScore.mMeanSingleOrbiterDamageTimes1000 / 1000,
                pCandidate.mScore.mMeanSingleOrbiterDamageTimes1000 % 1000,
                pCandidate.mScore.mMinimumSurvivingFanout,
                pCandidate.mScore.mMaximumDualTailArrivalSkew);
}

std::array<int, kScoreFieldCount> RankingDisplayValues(
    const TailScore &pScore) {
    return {
        pScore.mFirstMinimumWandererInfluence,
        pScore.mFirstMinimumInputCoverage,
        pScore.mSecondMinimumWandererInfluence,
        pScore.mSecondMinimumInputCoverage,
        pScore.mMinimumPairUnion,
        pScore.mMinimumHeartSeparation,
        pScore.mHeartSeparationTotal,
        pScore.mMinimumPairBalance,
        pScore.mMinimumComplement,
        pScore.mDominatedPairCount,
        pScore.mFlowArea,
        pScore.mArrivalTotal,
        pScore.mMaximumArrivalSkew,
        pScore.mDirectedDiameter,
        pScore.mMeanShortestPathTimes1000,
        pScore.mWorstMeanShortestPathTimes1000,
        pScore.mMinimumInfluencedWanderers,
        pScore.mMinimumEarlyReach,
        pScore.mMeanEarlyReachTimes1000,
        pScore.mRedundantRouteFractionTimes1000,
        pScore.mPairComponentCount,
        pScore.mMinimumExpansion,
        pScore.mExpansionTotal,
        pScore.mReservedLegacySpectralGap,
        pScore.mMinimumOneRoundFanout,
        pScore.mMeanOneRoundFanoutTimes1000,
        pScore.mMinimumSourceOrbiterArea,
        pScore.mMinimumDualTailReach,
        pScore.mMeanDualTailReachTimes1000,
        pScore.mMaximumOrbiterPathLoadTimes1000,
        pScore.mMaximumSourceOrphanArea,
        pScore.mMeanSourceOrphanAreaTimes1000,
        pScore.mMaximumLastOrphanLatency,
        pScore.mMaximumStragglerGap,
        pScore.mMaximumMidpointSourceOrphans,
        pScore.mMaximumMidpointDestinationOrphanLoad,
        pScore.mMaximumMidpointCoOrphanLoad,
        pScore.mMaximumMeetingOrphans,
        pScore.mMaximumSourceMeetingArea,
        pScore.mMeanPairMeetingLatencyTimes1000,
        pScore.mMaximumRobustOrphans,
        pScore.mMeanRobustOrphansTimes1000,
        pScore.mMaximumDestinationOrphanArea,
        pScore.mMaximumDualTailOrphanArea,
        pScore.mMeanDualTailOrphanAreaTimes1000,
        pScore.mMaximumRobustDestinationOrphans,
        pScore.mMaximumSingleOrbiterDamage,
        pScore.mMeanSingleOrbiterDamageTimes1000,
        pScore.mMinimumSurvivingFanout,
        pScore.mMaximumDualTailArrivalSkew,
    };
}

void PrintDetailedScore(const char *pLabel,
                        const Candidate &pCandidate) {
    PrintTail(pLabel, pCandidate);
    const TailScore &aScore = pCandidate.mScore;
    std::printf("       pair: heart_separation=%d/%d balance=%d "
                "complement=%d dominated=%d\n",
                aScore.mMinimumHeartSeparation,
                aScore.mHeartSeparationTotal,
                aScore.mMinimumPairBalance,
                aScore.mMinimumComplement,
                aScore.mDominatedPairCount);
    std::printf("       journey: flow_area=%d arrival_total=%d "
                "maximum_skew=%d\n",
                aScore.mFlowArea,
                aScore.mArrivalTotal,
                aScore.mMaximumArrivalSkew);
}

void PrintScoreExplanation(const Candidate &pBest,
                           const Candidate &pWorst) {
    const auto aBestValues = SafeRankingDisplayValues(pBest.mScore);
    const auto aWorstValues = SafeRankingDisplayValues(pWorst.mScore);

    std::printf("\nHOW THE SCORES ARE READ\n");
    std::printf("  Safe ranking is lexicographic in the order below: the "
                "first different score decides.\n");
    for (std::size_t i = 0U; i < kSafeRankingMetricNames.size(); ++i) {
        std::printf("  %2zu. %-35s best=%7d worst=%7d  %s\n",
                    i + 1U,
                    kSafeRankingMetricNames[i],
                    aBestValues[i],
                    aWorstValues[i],
                    kSafeRankingHigherIsBetter[i] ? "higher" : "lower");
    }

    for (std::size_t i = 0U; i < kSafeRankingMetricNames.size(); ++i) {
        if (aBestValues[i] != aWorstValues[i]) {
            std::printf("\n  Deciding score: %s. The best has %d and the "
                        "worst has %d; %s is preferred.\n",
                        kSafeRankingMetricNames[i],
                        aBestValues[i],
                        aWorstValues[i],
                        kSafeRankingHigherIsBetter[i]
                            ? "higher" : "lower");
            break;
        }
    }
    std::printf("  Exact expansion cannot rescue weak early causal flow, "
                "but it now decides among candidates that clear those "
                "causal floors.\n");
}

PairInfoMatrix MakePairInfo(const LoopCorePattern11 &pHeart,
                            const LoopHeadPattern11 &pHead,
                            const std::size_t pPatternIndex,
                            const DistanceMatrix &pDistances) {
    LoopTailPattern11 aProbeTail;
    aProbeTail.mOrbiterAForWanderer.fill(0U);
    aProbeTail.mOrbiterBForWanderer.fill(1U);
    InfluenceSet aProbeWanderers{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aProbeWanderers[i] = SourceInfluence(i);
    }
    Influence aProbeIngress = SourceInfluence(kInitialIngressSource);
    Influence aProbeCarry = SourceInfluence(kInitialCarrySource);
    const IterationResult aProbe = PropagateIteration(
        pHeart, pHead, aProbeTail, pPatternIndex,
        kFirstFreshIngressSource, kFirstFreshCrossSource, 0,
        &aProbeWanderers, &aProbeIngress, &aProbeCarry,
        nullptr);
    return MeasurePairs(aProbe.mOrbiters, pDistances);
}

bool TailUsesAllowedPairs(const LoopTailPattern11 &pTail,
                          const PairInfoMatrix &pPairs) {
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        if (!pPairs[pTail.mOrbiterAForWanderer[i]]
                   [pTail.mOrbiterBForWanderer[i]].mAllowed) {
            return false;
        }
    }
    return true;
}

struct PairScoreSample {
    Candidate mExplorationBest;
    Candidate mExplorationWorst;
    Candidate mSafeBest;
    Candidate mSafeWorst;
    std::array<int, kScoreFieldCount> mMinimumValues{};
    std::array<int, kScoreFieldCount> mMaximumValues{};
    std::array<std::size_t, kScoreFieldCount> mDistinctValueCounts{};
    std::array<std::size_t, kExplorationRankingMetricCount>
        mExplorationDistinctValueCounts{};
    std::array<std::size_t, kSafeRankingMetricCount>
        mSafeDistinctValueCounts{};
    std::array<std::size_t, kExplorationRankingMetricCount>
        mExplorationSurvivorsAfterMetric{};
    std::array<std::size_t, kSafeRankingMetricCount>
        mSafeSurvivorsAfterMetric{};
    std::size_t mSafeBestExplorationRank = 0U;
    std::size_t mSafeTop100InExplorationTop500 = 0U;
    std::size_t mExplorationTop500Count = 0U;
    std::size_t mSafeTop100Count = 0U;
    std::uint64_t mAttempts = 0ULL;
    std::uint64_t mRejectedSchedules = 0ULL;
    std::uint64_t mRejectedTransitions = 0ULL;
    std::uint64_t mRejectedDuplicates = 0ULL;
    std::size_t mFirstInfluenceEqualsPairUnionCount = 0U;
};

template <std::size_t N>
std::array<std::size_t, N> SurvivorsAfterEachMetric(
    const std::vector<Candidate> &pCandidates,
    std::array<int, N> (*pRankingValues)(const TailScore &)) {
    std::vector<std::size_t> aSurvivors(pCandidates.size());
    for (std::size_t i = 0U; i < aSurvivors.size(); ++i) {
        aSurvivors[i] = i;
    }
    std::array<std::size_t, N> aCounts{};
    for (std::size_t aMetric = 0U;
         aMetric < aCounts.size();
         ++aMetric) {
        int aBestValue = std::numeric_limits<int>::min();
        for (const std::size_t aIndex : aSurvivors) {
            aBestValue = std::max(
                aBestValue,
                pRankingValues(pCandidates[aIndex].mScore)[aMetric]);
        }
        aSurvivors.erase(
            std::remove_if(
                aSurvivors.begin(),
                aSurvivors.end(),
                [&pCandidates, pRankingValues, aMetric, aBestValue](
                    const std::size_t pIndex) {
                    return pRankingValues(
                        pCandidates[pIndex].mScore)[aMetric] !=
                        aBestValue;
                }),
            aSurvivors.end());
        aCounts[aMetric] = aSurvivors.size();
    }
    return aCounts;
}

bool MakePairScoreSample(const LoopNewPatternFile11 &pPatterns,
                         const std::size_t pHeartIndex,
                         const std::size_t pHeadIndex,
                         const std::uint64_t pCandidateCount,
                         PairScoreSample *pSample,
                         std::string *pErrorMessage) {
    const LoopNewHeart11 &aHeart = pPatterns.mHearts[pHeartIndex];
    const LoopHeadPattern11 &aHead =
        aHeart.mHeads[pHeadIndex].mHead;
    const std::size_t aPatternIndex =
        LoopHeadFarmer::PatternIndex(pHeartIndex, pHeadIndex);
    const DistanceMatrix aDistances =
        HeartTemporalDistances(aHeart.mHeart);
    const PairInfoMatrix aPairs = MakePairInfo(
        aHeart.mHeart, aHead, aPatternIndex, aDistances);
    Generator aGenerator(GeneratorSeedForPattern(aPatternIndex));

    std::unordered_set<std::string> aKeys;
    const std::uint64_t aReserveCount =
        pCandidateCount >
            (std::numeric_limits<std::uint64_t>::max() / 2ULL)
            ? std::numeric_limits<std::uint64_t>::max()
            : pCandidateCount * 2ULL;
    aKeys.reserve(static_cast<std::size_t>(
        std::min<std::uint64_t>(
            aReserveCount,
            std::numeric_limits<std::size_t>::max())));
    std::vector<Candidate> aSafeCandidates;
    std::vector<Candidate> aExplorationCandidates;
    aSafeCandidates.reserve(static_cast<std::size_t>(pCandidateCount));
    aExplorationCandidates.reserve(
        static_cast<std::size_t>(pCandidateCount));
    std::array<std::unordered_set<int>, kScoreFieldCount> aDistinctValues;
    std::array<std::unordered_set<int>, kExplorationRankingMetricCount>
        aExplorationDistinctValues;
    std::array<std::unordered_set<int>, kSafeRankingMetricCount>
        aSafeDistinctValues;
    pSample->mMinimumValues.fill(std::numeric_limits<int>::max());
    pSample->mMaximumValues.fill(std::numeric_limits<int>::min());

    std::uint64_t aValidCases = 0ULL;
    const std::uint64_t aMaximumAttempts =
        pCandidateCount >
            ((std::numeric_limits<std::uint64_t>::max() - 4096ULL) /
             64ULL)
            ? std::numeric_limits<std::uint64_t>::max()
            : (pCandidateCount * 64ULL) + 4096ULL;
    while ((aValidCases < pCandidateCount) &&
           (pSample->mAttempts < aMaximumAttempts)) {
        ++pSample->mAttempts;
        LoopTailPattern11 aTail;
        if (!GenerateTail(aPairs, &aGenerator, &aTail)) {
            ++pSample->mRejectedSchedules;
            continue;
        }
        const std::string aKey = TailKey(aTail);
        if (!aKeys.insert(aKey).second) {
            ++pSample->mRejectedDuplicates;
            continue;
        }

        const TransitionMatrix aTransition =
            MakeTransitionMatrix(aHead, aTail);
        const TransitionMetrics aTransitionMetrics =
            MeasureTransition(aTransition, true);
        if (!aTransitionMetrics.mStronglyConnected) {
            ++pSample->mRejectedTransitions;
            continue;
        }

        Candidate aCandidate;
        aCandidate.mTail = aTail;
        aCandidate.mKey = aKey;
        aCandidate.mScore = ScoreTail(
            aHeart.mHeart,
            aHead,
            aTail,
            aPatternIndex,
            aPairs,
            aTransitionMetrics);
        const std::array<int, kScoreFieldCount> aValues =
            RankingDisplayValues(aCandidate.mScore);
        for (std::size_t i = 0U; i < aValues.size(); ++i) {
            pSample->mMinimumValues[i] = std::min(
                pSample->mMinimumValues[i], aValues[i]);
            pSample->mMaximumValues[i] = std::max(
                pSample->mMaximumValues[i], aValues[i]);
            aDistinctValues[i].insert(aValues[i]);
        }
        const auto aExplorationValues =
            ExplorationRankingValues(aCandidate.mScore);
        for (std::size_t i = 0U; i < aExplorationValues.size(); ++i) {
            aExplorationDistinctValues[i].insert(aExplorationValues[i]);
        }
        const auto aSafeValues = SafeRankingValues(aCandidate.mScore);
        for (std::size_t i = 0U; i < aSafeValues.size(); ++i) {
            aSafeDistinctValues[i].insert(aSafeValues[i]);
        }
        pSample->mFirstInfluenceEqualsPairUnionCount +=
            aCandidate.mScore.mFirstMinimumWandererInfluence ==
            aCandidate.mScore.mMinimumPairUnion;
        aSafeCandidates.push_back(aCandidate);
        aExplorationCandidates.push_back(aCandidate);
        ++aValidCases;
    }

    if (aValidCases != pCandidateCount) {
        SetError(pErrorMessage,
                 "Loop tail score analysis could not fill its valid candidate budget");
        return false;
    }

    for (std::size_t i = 0U; i < aDistinctValues.size(); ++i) {
        pSample->mDistinctValueCounts[i] = aDistinctValues[i].size();
    }
    for (std::size_t i = 0U;
         i < aExplorationDistinctValues.size();
         ++i) {
        pSample->mExplorationDistinctValueCounts[i] =
            aExplorationDistinctValues[i].size();
    }
    for (std::size_t i = 0U; i < aSafeDistinctValues.size(); ++i) {
        pSample->mSafeDistinctValueCounts[i] =
            aSafeDistinctValues[i].size();
    }
    pSample->mSafeSurvivorsAfterMetric =
        SurvivorsAfterEachMetric(
            aSafeCandidates, SafeRankingValues);
    pSample->mExplorationSurvivorsAfterMetric =
        SurvivorsAfterEachMetric(
            aExplorationCandidates, ExplorationRankingValues);
    std::sort(aSafeCandidates.begin(),
              aSafeCandidates.end(), SafeCandidateIsBetter);
    std::sort(aExplorationCandidates.begin(),
              aExplorationCandidates.end(),
              ExplorationCandidateIsBetter);
    pSample->mSafeBest = aSafeCandidates.front();
    pSample->mSafeWorst = aSafeCandidates.back();
    pSample->mExplorationBest = aExplorationCandidates.front();
    pSample->mExplorationWorst = aExplorationCandidates.back();

    for (std::size_t i = 0U; i < aExplorationCandidates.size(); ++i) {
        if (aExplorationCandidates[i].mKey == pSample->mSafeBest.mKey) {
            pSample->mSafeBestExplorationRank = i + 1U;
            break;
        }
    }
    pSample->mExplorationTop500Count = std::min<std::size_t>(
        500U, aExplorationCandidates.size());
    pSample->mSafeTop100Count = std::min<std::size_t>(
        100U, aSafeCandidates.size());
    std::unordered_set<std::string> aExplorationTopKeys;
    aExplorationTopKeys.reserve(
        pSample->mExplorationTop500Count * 2U);
    for (std::size_t i = 0U;
         i < pSample->mExplorationTop500Count;
         ++i) {
        aExplorationTopKeys.insert(aExplorationCandidates[i].mKey);
    }
    for (std::size_t i = 0U; i < pSample->mSafeTop100Count; ++i) {
        pSample->mSafeTop100InExplorationTop500 +=
            aExplorationTopKeys.contains(aSafeCandidates[i].mKey);
    }
    return true;
}

void AppendTail(std::ostringstream *pOutput,
                const char *pLabel,
                const Candidate &pCandidate) {
    *pOutput << pLabel << " A={";
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        *pOutput << static_cast<char>(
            'A' + pCandidate.mTail.mOrbiterAForWanderer[i]);
        *pOutput << ((i + 1U) == kRoleCount ? "" : ",");
    }
    *pOutput << "} B={";
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        *pOutput << static_cast<char>(
            'A' + pCandidate.mTail.mOrbiterBForWanderer[i]);
        *pOutput << ((i + 1U) == kRoleCount ? "" : ",");
    }
    *pOutput << "}\n";
    const std::array<int, kScoreFieldCount> aValues =
        RankingDisplayValues(pCandidate.mScore);
    for (std::size_t i = 0U; i < aValues.size(); ++i) {
        *pOutput << "    " << (i + 1U) << ". "
                 << kRankingMetricNames[i] << " = "
                 << aValues[i] << "\n";
    }
}

struct DistributionSummary {
    int mMinimum = 0;
    int mP25 = 0;
    int mMedian = 0;
    int mP75 = 0;
    int mMaximum = 0;
    double mMean = 0.0;
};

DistributionSummary SummarizeValues(std::vector<int> pValues) {
    DistributionSummary aResult;
    if (pValues.empty()) {
        return aResult;
    }
    std::sort(pValues.begin(), pValues.end());
    const auto Quantile = [&pValues](const std::size_t pNumerator) {
        const std::size_t aIndex =
            ((pValues.size() - 1U) * pNumerator) / 4U;
        return pValues[aIndex];
    };
    std::int64_t aTotal = 0;
    for (const int aValue : pValues) {
        aTotal += aValue;
    }
    aResult.mMinimum = pValues.front();
    aResult.mP25 = Quantile(1U);
    aResult.mMedian = Quantile(2U);
    aResult.mP75 = Quantile(3U);
    aResult.mMaximum = pValues.back();
    aResult.mMean = static_cast<double>(aTotal) /
        static_cast<double>(pValues.size());
    return aResult;
}

int PercentileValue(std::vector<int> pValues,
                    const std::size_t pPercentile) {
    if (pValues.empty()) {
        return 0;
    }
    std::sort(pValues.begin(), pValues.end());
    const std::size_t aClippedPercentile =
        std::min<std::size_t>(pPercentile, 100U);
    const std::size_t aIndex =
        ((pValues.size() - 1U) * aClippedPercentile) / 100U;
    return pValues[aIndex];
}

std::vector<double> AverageRanks(const std::vector<int> &pValues) {
    std::vector<std::size_t> aOrder(pValues.size());
    std::iota(aOrder.begin(), aOrder.end(), 0U);
    std::sort(aOrder.begin(), aOrder.end(),
              [&pValues](const std::size_t pA,
                         const std::size_t pB) {
                  if (pValues[pA] != pValues[pB]) {
                      return pValues[pA] < pValues[pB];
                  }
                  return pA < pB;
              });
    std::vector<double> aRanks(pValues.size());
    std::size_t aBegin = 0U;
    while (aBegin < aOrder.size()) {
        std::size_t aEnd = aBegin + 1U;
        while ((aEnd < aOrder.size()) &&
               (pValues[aOrder[aEnd]] == pValues[aOrder[aBegin]])) {
            ++aEnd;
        }
        const double aAverageRank =
            (static_cast<double>(aBegin) +
             static_cast<double>(aEnd - 1U)) * 0.5;
        for (std::size_t i = aBegin; i < aEnd; ++i) {
            aRanks[aOrder[i]] = aAverageRank;
        }
        aBegin = aEnd;
    }
    return aRanks;
}

double PearsonCorrelation(const std::vector<double> &pA,
                          const std::vector<double> &pB) {
    if (pA.empty() || (pA.size() != pB.size())) {
        return 0.0;
    }
    double aMeanA = 0.0;
    double aMeanB = 0.0;
    for (std::size_t i = 0U; i < pA.size(); ++i) {
        aMeanA += pA[i];
        aMeanB += pB[i];
    }
    aMeanA /= static_cast<double>(pA.size());
    aMeanB /= static_cast<double>(pB.size());
    double aCovariance = 0.0;
    double aVarianceA = 0.0;
    double aVarianceB = 0.0;
    for (std::size_t i = 0U; i < pA.size(); ++i) {
        const double aDeltaA = pA[i] - aMeanA;
        const double aDeltaB = pB[i] - aMeanB;
        aCovariance += aDeltaA * aDeltaB;
        aVarianceA += aDeltaA * aDeltaA;
        aVarianceB += aDeltaB * aDeltaB;
    }
    if ((aVarianceA <= 0.0) || (aVarianceB <= 0.0)) {
        return 0.0;
    }
    return aCovariance / std::sqrt(aVarianceA * aVarianceB);
}

void AppendDistributionRow(std::ostringstream *pReport,
                           const char *pName,
                           const bool pHigherIsBetter,
                           const DistributionSummary &pSummary) {
    *pReport << "  " << std::left << std::setw(46) << pName
             << std::right << std::setw(7) << pSummary.mMinimum
             << std::setw(7) << pSummary.mP25
             << std::setw(7) << pSummary.mMedian
             << std::setw(7) << pSummary.mP75
             << std::setw(7) << pSummary.mMaximum
             << std::setw(12) << std::fixed << std::setprecision(2)
             << pSummary.mMean
             << "  " << (pHigherIsBetter ? "higher" : "lower")
             << "\n";
}

template <std::size_t N>
std::uint64_t HistogramCount(
    const std::array<std::uint64_t, N> &pHistogram) {
    std::uint64_t aCount = 0ULL;
    for (const std::uint64_t aValue : pHistogram) {
        aCount += aValue;
    }
    return aCount;
}

template <std::size_t N>
int HistogramQuantile(const std::array<std::uint64_t, N> &pHistogram,
                      const std::size_t pNumerator) {
    const std::uint64_t aCount = HistogramCount(pHistogram);
    if (aCount == 0ULL) {
        return 0;
    }
    const std::uint64_t aTarget =
        ((aCount - 1ULL) * pNumerator) / 4ULL;
    std::uint64_t aSeen = 0ULL;
    for (std::size_t i = 0U; i < N; ++i) {
        aSeen += pHistogram[i];
        if (aSeen > aTarget) {
            return static_cast<int>(i);
        }
    }
    return static_cast<int>(N - 1U);
}

template <std::size_t N>
void AppendDistanceHistogram(
    std::ostringstream *pReport,
    const char *pTitle,
    const std::array<std::uint64_t, N> &pHistogram) {
    const std::uint64_t aCount = HistogramCount(pHistogram);
    std::uint64_t aWeightedTotal = 0ULL;
    for (std::size_t i = 0U; i < N; ++i) {
        aWeightedTotal += static_cast<std::uint64_t>(i) * pHistogram[i];
    }
    const int aMinimum = HistogramQuantile(pHistogram, 0U);
    int aMaximum = 0;
    for (std::size_t i = 0U; i < N; ++i) {
        if (pHistogram[i] != 0ULL) {
            aMaximum = static_cast<int>(i);
        }
    }
    *pReport << pTitle << "\n"
             << "  pairs=" << aCount
             << " min=" << aMinimum
             << " p25=" << HistogramQuantile(pHistogram, 1U)
             << " median=" << HistogramQuantile(pHistogram, 2U)
             << " p75=" << HistogramQuantile(pHistogram, 3U)
             << " max=" << aMaximum
             << " average=" << std::fixed << std::setprecision(4)
             << (aCount == 0ULL
                    ? 0.0
                    : static_cast<double>(aWeightedTotal) /
                        static_cast<double>(aCount))
             << "\n  histogram:";
    for (std::size_t i = 0U; i < N; ++i) {
        if (pHistogram[i] != 0ULL) {
            *pReport << " " << i << "=" << pHistogram[i];
        }
    }
    *pReport << "\n\n";
}

int HeartSlotDistance(const LoopCorePattern11 &pA,
                      const LoopCorePattern11 &pB) {
    int aDistance = 0;
    for (std::size_t aRound = 0U; aRound < kRoleCount; ++aRound) {
        for (std::size_t aColumn = 0U; aColumn < 3U; ++aColumn) {
            aDistance +=
                pA.mRounds[aRound][aColumn] !=
                pB.mRounds[aRound][aColumn];
        }
    }
    return aDistance;
}

//
// Ascendency farm
//


constexpr std::array<std::uint8_t, 8U> kAscendencyFileMagic = {
    'M', 'M', 'L', 'O', 'O', 'P', '1', '1',
};
constexpr std::uint32_t kAscendencyFileVersion = 1U;
constexpr std::size_t kAscendencyFileByteCount =
    44U + kPatternByteCount +
    (kScoreFieldCount * sizeof(std::uint32_t));
constexpr int kAscendencyTierZero = 0;
constexpr int kAscendencyTierOne = 1;
constexpr int kAscendencyTierTwo = 2;
constexpr int kAscendencyWorkingTier = 3;

constexpr std::array<const char *, 4U> kAscendencyTierFolderNames = {
    "tier_0", "tier_1", "tier_2", "working",
};

struct AscendencyRecord {
    Candidate mCandidate;
    std::uint64_t mAttempts = 0ULL;
    int mTier = kAscendencyWorkingTier;
};

// These four tail-sensitive integer measurements cover normal ordered flow
// and failure behavior. Static path-load and spectral estimates are omitted.
constexpr std::array<std::size_t, 4U> kAscendencyHeadlineMetrics = {
    27U, 30U, 46U, 48U,
};

struct AscendencyTierPolicy {
    // First index is tier 0, 1, or 2. Second index selects one of the four
    // headline metrics above.
    std::array<std::array<int, 4U>, 3U> mThresholds{};
};

bool ScorePassesAscendencyTier(
    const std::array<int, kScoreFieldCount> &pValues,
    const AscendencyTierPolicy &pPolicy,
    const int pTier) {
    for (std::size_t i = 0U;
         i < kAscendencyHeadlineMetrics.size();
         ++i) {
        const std::size_t aMetric = kAscendencyHeadlineMetrics[i];
        const int aThreshold =
            pPolicy.mThresholds[static_cast<std::size_t>(pTier)][i];
        const bool aPasses = kRankingHigherIsBetter[aMetric]
            ? pValues[aMetric] >= aThreshold
            : pValues[aMetric] <= aThreshold;
        if (!aPasses) {
            return false;
        }
    }
    return true;
}

int AscendencyTier(const TailScore &pScore,
                   const AscendencyTierPolicy &pPolicy) {
    const auto aValues = RankingDisplayValues(pScore);
    if (ScorePassesAscendencyTier(
            aValues, pPolicy, kAscendencyTierZero)) {
        return kAscendencyTierZero;
    }
    if (ScorePassesAscendencyTier(
            aValues, pPolicy, kAscendencyTierOne)) {
        return kAscendencyTierOne;
    }
    if (ScorePassesAscendencyTier(
            aValues, pPolicy, kAscendencyTierTwo)) {
        return kAscendencyTierTwo;
    }
    return kAscendencyWorkingTier;
}

bool AscendencyRecordIsBetter(const AscendencyRecord &pA,
                              const AscendencyRecord &pB) {
    if (pA.mTier != pB.mTier) {
        return pA.mTier < pB.mTier;
    }
    return SafeCandidateIsBetter(pA.mCandidate, pB.mCandidate);
}

std::string AscendencyRecordPath(const std::string &pFarmFolderPath,
                                 const std::size_t pHeartIndex,
                                 const std::size_t pHeadIndex,
                                 const int pTier) {
    char aHeartName[32];
    char aLoopName[32];
    std::snprintf(aHeartName, sizeof(aHeartName),
                  "heart_%02zu", pHeartIndex);
    std::snprintf(aLoopName, sizeof(aLoopName),
                  "loop_%03zu.bin", pHeadIndex + 1U);
    return (std::filesystem::path(ResolvedPath(pFarmFolderPath)) /
            aHeartName /
            kAscendencyTierFolderNames[static_cast<std::size_t>(pTier)] /
            aLoopName).lexically_normal().generic_string();
}

bool SaveAscendencyRecord(const std::string &pFarmFolderPath,
                          const std::size_t pHeartIndex,
                          const std::size_t pHeadIndex,
                          const AscendencyRecord &pRecord,
                          std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kAscendencyFileByteCount);
    aBytes.insert(aBytes.end(),
                  kAscendencyFileMagic.begin(),
                  kAscendencyFileMagic.end());
    Append32(&aBytes, kAscendencyFileVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(kRoleCount));
    Append32(&aBytes, static_cast<std::uint32_t>(kScoreFieldCount));
    Append32(&aBytes, static_cast<std::uint32_t>(pHeartIndex));
    Append32(&aBytes, static_cast<std::uint32_t>(pHeadIndex));
    Append32(&aBytes, static_cast<std::uint32_t>(pRecord.mTier));
    Append32(&aBytes, static_cast<std::uint32_t>(
        kAscendencyFileByteCount));
    Append64(&aBytes, pRecord.mAttempts);
    aBytes.insert(aBytes.end(),
                  pRecord.mCandidate.mTail.mOrbiterAForWanderer.begin(),
                  pRecord.mCandidate.mTail.mOrbiterAForWanderer.end());
    aBytes.insert(aBytes.end(),
                  pRecord.mCandidate.mTail.mOrbiterBForWanderer.begin(),
                  pRecord.mCandidate.mTail.mOrbiterBForWanderer.end());
    AppendScore(&aBytes, pRecord.mCandidate.mScore);
    if (aBytes.size() != kAscendencyFileByteCount) {
        SetError(pErrorMessage,
                 "Ascendency loop record had an internal size mismatch");
        return false;
    }

    const std::string aPath = AscendencyRecordPath(
        pFarmFolderPath, pHeartIndex, pHeadIndex, pRecord.mTier);
    const std::string aTemporaryPath = aPath + ".tmp";
    if (!FileIO::Save(aTemporaryPath, aBytes)) {
        SetError(pErrorMessage,
                 "Ascendency farm could not checkpoint " + aPath);
        return false;
    }
    if (std::rename(aTemporaryPath.c_str(), aPath.c_str()) != 0) {
        const std::string aReason = std::strerror(errno);
        std::error_code aCleanupError;
        std::filesystem::remove(aTemporaryPath, aCleanupError);
        SetError(pErrorMessage,
                 "Ascendency farm could not install checkpoint " +
                 aPath + ": " + aReason);
        return false;
    }

    // A task has one canonical record. Removal happens only after the new
    // checkpoint is fully installed, so a crash cannot erase the last result.
    for (int aTier = kAscendencyTierZero;
         aTier <= kAscendencyWorkingTier;
         ++aTier) {
        if (aTier == pRecord.mTier) {
            continue;
        }
        std::error_code aRemoveError;
        std::filesystem::remove(
            AscendencyRecordPath(pFarmFolderPath,
                                 pHeartIndex,
                                 pHeadIndex,
                                 aTier),
            aRemoveError);
    }
    return true;
}

bool LoadOneAscendencyRecord(const std::string &pPath,
                             const std::size_t pExpectedHeartIndex,
                             const std::size_t pExpectedHeadIndex,
                             const int pExpectedTier,
                             AscendencyRecord *pRecord,
                             std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes) ||
        (aBytes.size() != kAscendencyFileByteCount) ||
        !std::equal(kAscendencyFileMagic.begin(),
                    kAscendencyFileMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Ascendency farm could not load record " + pPath);
        return false;
    }
    std::size_t aOffset = kAscendencyFileMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    const std::uint32_t aRoleCount = Read32(aBytes, &aOffset);
    const std::uint32_t aScoreFieldCount = Read32(aBytes, &aOffset);
    const std::uint32_t aHeartIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aHeadIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aTier = Read32(aBytes, &aOffset);
    const std::uint32_t aByteCount = Read32(aBytes, &aOffset);
    const std::uint64_t aAttempts = Read64(aBytes, &aOffset);
    if ((aVersion != kAscendencyFileVersion) ||
        (aRoleCount != kRoleCount) ||
        (aScoreFieldCount != kScoreFieldCount) ||
        (aHeartIndex != pExpectedHeartIndex) ||
        (aHeadIndex != pExpectedHeadIndex) ||
        (aTier != static_cast<std::uint32_t>(pExpectedTier)) ||
        (aByteCount != kAscendencyFileByteCount)) {
        SetError(pErrorMessage,
                 "Ascendency record metadata did not match " + pPath);
        return false;
    }

    AscendencyRecord aRecord;
    aRecord.mAttempts = aAttempts;
    aRecord.mTier = pExpectedTier;
    for (std::uint8_t &aValue :
         aRecord.mCandidate.mTail.mOrbiterAForWanderer) {
        aValue = aBytes[aOffset++];
    }
    for (std::uint8_t &aValue :
         aRecord.mCandidate.mTail.mOrbiterBForWanderer) {
        aValue = aBytes[aOffset++];
    }
    aRecord.mCandidate.mScore = ReadScore(aBytes, &aOffset);
    aRecord.mCandidate.mKey = TailKey(aRecord.mCandidate.mTail);
    if ((aOffset != aBytes.size()) ||
        !IsTailPermutation(aRecord.mCandidate.mTail)) {
        SetError(pErrorMessage,
                 "Ascendency record contained an invalid tail " + pPath);
        return false;
    }
    *pRecord = std::move(aRecord);
    return true;
}

bool LoadAscendencyRecord(const std::string &pFarmFolderPath,
                          const std::size_t pHeartIndex,
                          const std::size_t pHeadIndex,
                          bool *pFound,
                          AscendencyRecord *pRecord,
                          std::string *pErrorMessage) {
    *pFound = false;
    std::uint64_t aMaximumAttempts = 0ULL;
    for (int aTier = kAscendencyTierZero;
         aTier <= kAscendencyWorkingTier;
         ++aTier) {
        const std::string aPath = AscendencyRecordPath(
            pFarmFolderPath, pHeartIndex, pHeadIndex, aTier);
        std::error_code aExistsError;
        if (!std::filesystem::exists(aPath, aExistsError)) {
            continue;
        }
        AscendencyRecord aLoaded;
        if (!LoadOneAscendencyRecord(aPath,
                                     pHeartIndex,
                                     pHeadIndex,
                                     aTier,
                                     &aLoaded,
                                     pErrorMessage)) {
            return false;
        }
        aMaximumAttempts = std::max(aMaximumAttempts,
                                    aLoaded.mAttempts);
        if (!*pFound || AscendencyRecordIsBetter(aLoaded, *pRecord)) {
            *pRecord = std::move(aLoaded);
            *pFound = true;
        }
    }
    if (*pFound) {
        pRecord->mAttempts = aMaximumAttempts;
    }
    return true;
}

bool ParseHeartIndex(const std::string &pText,
                     std::size_t *pHeartIndex) {
    if (pText.empty()) {
        return false;
    }
    std::size_t aValue = 0U;
    for (const char aCharacter : pText) {
        if ((aCharacter < '0') || (aCharacter > '9')) {
            return false;
        }
        const std::size_t aDigit =
            static_cast<std::size_t>(aCharacter - '0');
        if (aValue > ((std::numeric_limits<std::size_t>::max() -
                       aDigit) / 10U)) {
            return false;
        }
        aValue = (aValue * 10U) + aDigit;
    }
    if (aValue >= LoopHeadFarmer::kCoreCount) {
        return false;
    }
    *pHeartIndex = aValue;
    return true;
}

bool ParseHeartSelection(const std::string &pSelection,
                         std::vector<std::size_t> *pHeartIndices,
                         std::string *pErrorMessage) {
    pHeartIndices->clear();
    if (pSelection == "all") {
        for (std::size_t i = 0U;
             i < LoopHeadFarmer::kCoreCount;
             ++i) {
            pHeartIndices->push_back(i);
        }
        return true;
    }

    std::array<bool, LoopHeadFarmer::kCoreCount> aSelected{};
    std::size_t aBegin = 0U;
    while (aBegin < pSelection.size()) {
        const std::size_t aEnd = pSelection.find(',', aBegin);
        const std::string aPart = pSelection.substr(
            aBegin,
            aEnd == std::string::npos
                ? std::string::npos : aEnd - aBegin);
        const std::size_t aDash = aPart.find('-');
        std::size_t aFirst = 0U;
        std::size_t aLast = 0U;
        if (aDash == std::string::npos) {
            if (!ParseHeartIndex(aPart, &aFirst)) {
                SetError(pErrorMessage,
                         "Invalid heart selection: " + pSelection);
                return false;
            }
            aLast = aFirst;
        } else {
            if ((aPart.find('-', aDash + 1U) != std::string::npos) ||
                !ParseHeartIndex(aPart.substr(0U, aDash), &aFirst) ||
                !ParseHeartIndex(aPart.substr(aDash + 1U), &aLast) ||
                (aFirst > aLast)) {
                SetError(pErrorMessage,
                         "Invalid heart selection: " + pSelection);
                return false;
            }
        }
        for (std::size_t i = aFirst; i <= aLast; ++i) {
            aSelected[i] = true;
        }
        if (aEnd == std::string::npos) {
            break;
        }
        aBegin = aEnd + 1U;
    }
    for (std::size_t i = 0U; i < aSelected.size(); ++i) {
        if (aSelected[i]) {
            pHeartIndices->push_back(i);
        }
    }
    if (pHeartIndices->empty()) {
        SetError(pErrorMessage,
                 "Heart selection did not contain a heart");
        return false;
    }
    return true;
}

bool EvaluateAscendencyCandidate(
    const LoopNewHeart11 &pHeart,
    const LoopHeadPattern11 &pHead,
    const std::size_t pPatternIndex,
    const PairInfoMatrix &pPairs,
    const LoopTailPattern11 &pTail,
    Candidate *pCandidate,
    const bool pWeightedOnly = false) {
    if (!IsTailPermutation(pTail) ||
        !TailUsesAllowedPairs(pTail, pPairs)) {
        return false;
    }
    const TransitionMatrix aTransition =
        MakeTransitionMatrix(pHead, pTail);
    const TransitionMetrics aTransitionMetrics =
        MeasureTransition(aTransition, true, !pWeightedOnly);
    if (!aTransitionMetrics.mStronglyConnected) {
        return false;
    }
    pCandidate->mTail = pTail;
    pCandidate->mKey = TailKey(pTail);
    pCandidate->mScore = ScoreTail(
        pHeart.mHeart,
        pHead,
        pTail,
        pPatternIndex,
        pPairs,
        aTransitionMetrics,
        pWeightedOnly);
    return true;
}

bool MakeAscendencyTierPolicy(
    const LoopNewHeart11 &pHeart,
    const std::size_t pHeartIndex,
    const DistanceMatrix &pDistances,
    AscendencyTierPolicy *pPolicy,
    std::string *pErrorMessage) {
    std::array<std::vector<int>, 4U> aHeadlineValues;
    for (auto &aValues : aHeadlineValues) {
        aValues.reserve(LoopHeadFarmer::kPatternsPerCore);
    }
    for (std::size_t aHeadIndex = 0U;
         aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
         ++aHeadIndex) {
        const LoopHeadPattern11 &aHead =
            pHeart.mHeads[aHeadIndex].mHead;
        const std::size_t aPatternIndex =
            LoopHeadFarmer::PatternIndex(pHeartIndex, aHeadIndex);
        const PairInfoMatrix aPairs = MakePairInfo(
            pHeart.mHeart, aHead, aPatternIndex, pDistances);
        Candidate aCandidate;
        if (!EvaluateAscendencyCandidate(
                pHeart,
                aHead,
                aPatternIndex,
                aPairs,
                pHeart.mHeads[aHeadIndex].mTail,
                &aCandidate)) {
            SetError(pErrorMessage,
                     "Current loop asset could not establish the Ascendency policy for heart " +
                     std::to_string(pHeartIndex) + " head " +
                     std::to_string(aHeadIndex));
            return false;
        }
        const auto aValues = RankingDisplayValues(aCandidate.mScore);
        for (std::size_t i = 0U;
             i < kAscendencyHeadlineMetrics.size();
             ++i) {
            aHeadlineValues[i].push_back(
                aValues[kAscendencyHeadlineMetrics[i]]);
        }
    }

    // Tier 0 is the best 5% side of all four heart-local distributions.
    // Tier 1 is the best 20%; Tier 2 is the better half. Inclusive ties make
    // the thresholds deterministic even when a metric has few distinct values.
    constexpr std::array<std::size_t, 3U> kBestPercentiles = {
        95U, 80U, 50U,
    };
    for (std::size_t aTier = 0U; aTier < 3U; ++aTier) {
        for (std::size_t i = 0U;
             i < kAscendencyHeadlineMetrics.size();
             ++i) {
            const std::size_t aMetric = kAscendencyHeadlineMetrics[i];
            const std::size_t aPercentile =
                kRankingHigherIsBetter[aMetric]
                    ? kBestPercentiles[aTier]
                    : 100U - kBestPercentiles[aTier];
            pPolicy->mThresholds[aTier][i] = PercentileValue(
                aHeadlineValues[i], aPercentile);
        }
    }
    return true;
}

void PrintAscendencyTierPolicy(
    const std::size_t pHeartIndex,
    const AscendencyTierPolicy &pPolicy) {
    std::printf("heart %zu tier gates "
                "(dual reach >=, source area <=, damage <=, fanout >=):\n",
                pHeartIndex);
    for (int aTier = kAscendencyTierZero;
         aTier <= kAscendencyTierTwo;
         ++aTier) {
        const auto &aThresholds =
            pPolicy.mThresholds[static_cast<std::size_t>(aTier)];
        std::printf("  tier_%d: %d, %d, %d, %d\n",
                    aTier,
                    aThresholds[0],
                    aThresholds[1],
                    aThresholds[2],
                    aThresholds[3]);
    }
}

std::uint64_t MixFarmSeed(std::uint64_t pValue) {
    pValue = (pValue ^ (pValue >> 30U)) *
        0xBF58476D1CE4E5B9ULL;
    pValue = (pValue ^ (pValue >> 27U)) *
        0x94D049BB133111EBULL;
    return pValue ^ (pValue >> 31U);
}

std::uint64_t AscendencyGeneratorSeed(
    const std::size_t pPatternIndex,
    const std::uint64_t pCompletedAttempts) {
    return MixFarmSeed(
        GeneratorSeedForPattern(pPatternIndex) ^
        (pCompletedAttempts * 0xD1342543DE82EF95ULL) ^
        0x415343454E443131ULL);
}

using MetricValues = std::array<int, kScoreFieldCount>;

static_assert(LoopExtremeMeasures::kMetricCount == kScoreFieldCount,
              "Loop extrema must match the scoring metric count");
static_assert(LoopScorer::kMetricCount == kScoreFieldCount,
              "Loop scorer must match the scoring metric count");
static_assert(LoopScorer::kMaximumScore ==
                  static_cast<int>(LoopWeights::WeightTotal()),
              "Loop scorer maximum must match the metric weights");

constexpr bool LoopScorerMatchesWeights() {
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        if ((LoopScorer::kMeasures[i].mHigherIsBetter !=
             LoopWeights::kMetrics[i].mHigherIsBetter) ||
            (LoopScorer::kMeasures[i].mWeight !=
             static_cast<float>(LoopWeights::kMetrics[i].mWeight))) {
            return false;
        }
    }
    return true;
}

static_assert(LoopScorerMatchesWeights(),
              "Loop scorer directions and weights must match LoopWeights");

constexpr std::array<std::uint8_t, 8U> kMetricSliceFileMagic = {
    'M', 'M', 'S', 'L', 'I', 'C', 'E', '1',
};
constexpr std::uint32_t kMetricSliceFileVersion = 1U;

struct MetricSliceHeadSummary {
    std::uint64_t mValidTrials = 0ULL;
    std::uint64_t mRawAttempts = 0ULL;
    MetricValues mMinimumValues{};
    MetricValues mMaximumValues{};
    MetricValues mOnePercentThresholds{};
    std::array<std::uint64_t, kScoreFieldCount> mMinimumCounts{};
    std::array<std::uint64_t, kScoreFieldCount> mMaximumCounts{};
    std::array<std::uint64_t, kScoreFieldCount> mOnePercentPassCounts{};
    std::array<std::uint64_t, kProposedMustHaveGates.size()>
        mProposedGatePassCounts{};
    std::uint64_t mDirectionalBestJointCount = 0ULL;
    std::uint64_t mOnePercentJointCount = 0ULL;
    std::uint64_t mProposedGateJointCount = 0ULL;
};

struct MetricSliceHeartSummary {
    MetricValues mMinimumValues{};
    MetricValues mMaximumValues{};
    MetricValues mDirectionalBestValues{};
    MetricValues mWeakestHeadOnePercentThresholds{};
    std::array<std::uint64_t, kScoreFieldCount> mMinimumCounts{};
    std::array<std::uint64_t, kScoreFieldCount> mMaximumCounts{};
    std::array<std::uint64_t, kProposedMustHaveGates.size()>
        mProposedGatePassCounts{};
    std::uint64_t mValidTrials = 0ULL;
    std::uint64_t mRawAttempts = 0ULL;
    std::uint64_t mDirectionalBestJointCount = 0ULL;
    std::uint64_t mOnePercentJointCount = 0ULL;
    std::uint64_t mProposedGateJointCount = 0ULL;
};

std::string MetricSliceHeadPath(const std::string &pFolderPath,
                                const std::uint64_t pTrialsPerHead,
                                const std::size_t pHeartIndex,
                                const std::size_t pHeadIndex) {
    char aTrialFolder[48];
    char aHeartFolder[32];
    char aHeadFile[32];
    std::snprintf(aTrialFolder, sizeof(aTrialFolder),
                  "trials_%llu",
                  static_cast<unsigned long long>(pTrialsPerHead));
    std::snprintf(aHeartFolder, sizeof(aHeartFolder),
                  "heart_%03zu", pHeartIndex);
    std::snprintf(aHeadFile, sizeof(aHeadFile),
                  "head_%03zu.bin", pHeadIndex);
    return (std::filesystem::path(ResolvedPath(pFolderPath)) /
            aTrialFolder / aHeartFolder / aHeadFile)
        .lexically_normal().generic_string();
}

void AppendMetricValues(std::vector<std::uint8_t> *pBytes,
                        const MetricValues &pValues) {
    for (const int aValue : pValues) {
        Append32(pBytes, static_cast<std::uint32_t>(aValue));
    }
}

void AppendMetricCounts(
    std::vector<std::uint8_t> *pBytes,
    const std::array<std::uint64_t, kScoreFieldCount> &pValues) {
    for (const std::uint64_t aValue : pValues) {
        Append64(pBytes, aValue);
    }
}

MetricValues ReadMetricValues(const std::vector<std::uint8_t> &pBytes,
                              std::size_t *pOffset) {
    MetricValues aValues{};
    for (int &aValue : aValues) {
        aValue = static_cast<int>(Read32(pBytes, pOffset));
    }
    return aValues;
}

std::array<std::uint64_t, kScoreFieldCount> ReadMetricCounts(
    const std::vector<std::uint8_t> &pBytes,
    std::size_t *pOffset) {
    std::array<std::uint64_t, kScoreFieldCount> aValues{};
    for (std::uint64_t &aValue : aValues) {
        aValue = Read64(pBytes, pOffset);
    }
    return aValues;
}

bool SaveMetricSliceHeadSummary(
    const std::string &pFolderPath,
    const std::size_t pHeartIndex,
    const std::size_t pHeadIndex,
    const MetricSliceHeadSummary &pSummary,
    std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    aBytes.insert(aBytes.end(),
                  kMetricSliceFileMagic.begin(),
                  kMetricSliceFileMagic.end());
    Append32(&aBytes, kMetricSliceFileVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(kScoreFieldCount));
    Append32(&aBytes, static_cast<std::uint32_t>(
        kProposedMustHaveGates.size()));
    Append32(&aBytes, static_cast<std::uint32_t>(pHeartIndex));
    Append32(&aBytes, static_cast<std::uint32_t>(pHeadIndex));
    Append64(&aBytes, pSummary.mValidTrials);
    Append64(&aBytes, pSummary.mRawAttempts);
    AppendMetricValues(&aBytes, pSummary.mMinimumValues);
    AppendMetricValues(&aBytes, pSummary.mMaximumValues);
    AppendMetricValues(&aBytes, pSummary.mOnePercentThresholds);
    AppendMetricCounts(&aBytes, pSummary.mMinimumCounts);
    AppendMetricCounts(&aBytes, pSummary.mMaximumCounts);
    AppendMetricCounts(&aBytes, pSummary.mOnePercentPassCounts);
    for (const std::uint64_t aCount :
         pSummary.mProposedGatePassCounts) {
        Append64(&aBytes, aCount);
    }
    Append64(&aBytes, pSummary.mDirectionalBestJointCount);
    Append64(&aBytes, pSummary.mOnePercentJointCount);
    Append64(&aBytes, pSummary.mProposedGateJointCount);

    const std::string aPath = MetricSliceHeadPath(
        pFolderPath, pSummary.mValidTrials, pHeartIndex, pHeadIndex);
    const std::string aTemporaryPath = aPath + ".tmp";
    if (!FileIO::Save(aTemporaryPath, aBytes)) {
        SetError(pErrorMessage,
                 "Metric slice explorer could not save " + aPath);
        return false;
    }
    if (std::rename(aTemporaryPath.c_str(), aPath.c_str()) != 0) {
        const std::string aReason = std::strerror(errno);
        std::error_code aCleanupError;
        std::filesystem::remove(aTemporaryPath, aCleanupError);
        SetError(pErrorMessage,
                 "Metric slice explorer could not install " + aPath +
                 ": " + aReason);
        return false;
    }
    return true;
}

bool LoadMetricSliceHeadSummary(
    const std::string &pFolderPath,
    const std::uint64_t pExpectedTrials,
    const std::size_t pHeartIndex,
    const std::size_t pHeadIndex,
    bool *pFound,
    MetricSliceHeadSummary *pSummary,
    std::string *pErrorMessage) {
    *pFound = false;
    const std::string aPath = MetricSliceHeadPath(
        pFolderPath, pExpectedTrials, pHeartIndex, pHeadIndex);
    std::error_code aExistsError;
    if (!std::filesystem::exists(aPath, aExistsError)) {
        return true;
    }
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(aPath, aBytes) ||
        (aBytes.size() < kMetricSliceFileMagic.size()) ||
        !std::equal(kMetricSliceFileMagic.begin(),
                    kMetricSliceFileMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Metric slice explorer could not load " + aPath);
        return false;
    }
    std::size_t aOffset = kMetricSliceFileMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    const std::uint32_t aMetricCount = Read32(aBytes, &aOffset);
    const std::uint32_t aGateCount = Read32(aBytes, &aOffset);
    const std::uint32_t aHeartIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aHeadIndex = Read32(aBytes, &aOffset);
    MetricSliceHeadSummary aSummary;
    aSummary.mValidTrials = Read64(aBytes, &aOffset);
    aSummary.mRawAttempts = Read64(aBytes, &aOffset);
    if ((aVersion != kMetricSliceFileVersion) ||
        (aMetricCount != kScoreFieldCount) ||
        (aGateCount != kProposedMustHaveGates.size()) ||
        (aHeartIndex != pHeartIndex) ||
        (aHeadIndex != pHeadIndex) ||
        (aSummary.mValidTrials != pExpectedTrials)) {
        SetError(pErrorMessage,
                 "Metric slice checkpoint metadata did not match " +
                 aPath);
        return false;
    }
    const std::size_t aExpectedRemaining =
        (3U * kScoreFieldCount * sizeof(std::uint32_t)) +
        (3U * kScoreFieldCount * sizeof(std::uint64_t)) +
        (kProposedMustHaveGates.size() * sizeof(std::uint64_t)) +
        (3U * sizeof(std::uint64_t));
    if ((aOffset + aExpectedRemaining) != aBytes.size()) {
        SetError(pErrorMessage,
                 "Metric slice checkpoint size did not match " + aPath);
        return false;
    }
    aSummary.mMinimumValues = ReadMetricValues(aBytes, &aOffset);
    aSummary.mMaximumValues = ReadMetricValues(aBytes, &aOffset);
    aSummary.mOnePercentThresholds = ReadMetricValues(aBytes, &aOffset);
    aSummary.mMinimumCounts = ReadMetricCounts(aBytes, &aOffset);
    aSummary.mMaximumCounts = ReadMetricCounts(aBytes, &aOffset);
    aSummary.mOnePercentPassCounts = ReadMetricCounts(aBytes, &aOffset);
    for (std::uint64_t &aCount : aSummary.mProposedGatePassCounts) {
        aCount = Read64(aBytes, &aOffset);
    }
    aSummary.mDirectionalBestJointCount = Read64(aBytes, &aOffset);
    aSummary.mOnePercentJointCount = Read64(aBytes, &aOffset);
    aSummary.mProposedGateJointCount = Read64(aBytes, &aOffset);
    if (aOffset != aBytes.size()) {
        SetError(pErrorMessage,
                 "Metric slice checkpoint ended incorrectly " + aPath);
        return false;
    }
    *pSummary = std::move(aSummary);
    *pFound = true;
    return true;
}

void SummarizeMetricSliceRows(
    const std::vector<MetricValues> &pRows,
    MetricSliceHeadSummary *pSummary) {
    pSummary->mMinimumValues.fill(std::numeric_limits<int>::max());
    pSummary->mMaximumValues.fill(std::numeric_limits<int>::min());
    for (const MetricValues &aValues : pRows) {
        for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
            pSummary->mMinimumValues[i] = std::min(
                pSummary->mMinimumValues[i], aValues[i]);
            pSummary->mMaximumValues[i] = std::max(
                pSummary->mMaximumValues[i], aValues[i]);
        }
    }

    const std::size_t aOnePercentCount = std::max<std::size_t>(
        1U, (pRows.size() + 99U) / 100U);
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        std::vector<int> aColumn;
        aColumn.reserve(pRows.size());
        for (const MetricValues &aValues : pRows) {
            aColumn.push_back(aValues[i]);
            pSummary->mMinimumCounts[i] +=
                aValues[i] == pSummary->mMinimumValues[i];
            pSummary->mMaximumCounts[i] +=
                aValues[i] == pSummary->mMaximumValues[i];
        }
        std::sort(aColumn.begin(), aColumn.end());
        pSummary->mOnePercentThresholds[i] =
            kRankingHigherIsBetter[i]
                ? aColumn[aColumn.size() - aOnePercentCount]
                : aColumn[aOnePercentCount - 1U];
        for (const int aValue : aColumn) {
            pSummary->mOnePercentPassCounts[i] +=
                PassesMetricThreshold(
                    aValue, i,
                    pSummary->mOnePercentThresholds[i]);
        }
    }

    for (const MetricValues &aValues : pRows) {
        bool aPassesDirectionalBest = true;
        bool aPassesOnePercent = true;
        bool aPassesProposedJoint = true;
        for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
            const int aDirectionalBest = kRankingHigherIsBetter[i]
                ? pSummary->mMaximumValues[i]
                : pSummary->mMinimumValues[i];
            aPassesDirectionalBest = aPassesDirectionalBest &&
                (aValues[i] == aDirectionalBest);
            aPassesOnePercent = aPassesOnePercent &&
                PassesMetricThreshold(
                    aValues[i], i,
                    pSummary->mOnePercentThresholds[i]);
        }
        for (std::size_t i = 0U;
             i < kProposedMustHaveGates.size();
             ++i) {
            const MetricGate &aGate = kProposedMustHaveGates[i];
            const bool aPasses = PassesMetricThreshold(
                aValues[aGate.mMetric],
                aGate.mMetric,
                aGate.mThreshold);
            pSummary->mProposedGatePassCounts[i] += aPasses;
            aPassesProposedJoint = aPassesProposedJoint && aPasses;
        }
        pSummary->mDirectionalBestJointCount +=
            aPassesDirectionalBest;
        pSummary->mOnePercentJointCount += aPassesOnePercent;
        pSummary->mProposedGateJointCount += aPassesProposedJoint;
    }
}

MetricSliceHeartSummary AggregateMetricSliceHeart(
    const std::vector<MetricSliceHeadSummary> &pHeads) {
    MetricSliceHeartSummary aHeart;
    aHeart.mMinimumValues.fill(std::numeric_limits<int>::max());
    aHeart.mMaximumValues.fill(std::numeric_limits<int>::min());
    for (const MetricSliceHeadSummary &aHead : pHeads) {
        aHeart.mValidTrials += aHead.mValidTrials;
        aHeart.mRawAttempts += aHead.mRawAttempts;
        aHeart.mDirectionalBestJointCount +=
            aHead.mDirectionalBestJointCount;
        aHeart.mOnePercentJointCount += aHead.mOnePercentJointCount;
        aHeart.mProposedGateJointCount +=
            aHead.mProposedGateJointCount;
        for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
            aHeart.mMinimumValues[i] = std::min(
                aHeart.mMinimumValues[i], aHead.mMinimumValues[i]);
            aHeart.mMaximumValues[i] = std::max(
                aHeart.mMaximumValues[i], aHead.mMaximumValues[i]);
        }
        for (std::size_t i = 0U;
             i < kProposedMustHaveGates.size();
             ++i) {
            aHeart.mProposedGatePassCounts[i] +=
                aHead.mProposedGatePassCounts[i];
        }
    }
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        aHeart.mDirectionalBestValues[i] = kRankingHigherIsBetter[i]
            ? aHeart.mMaximumValues[i]
            : aHeart.mMinimumValues[i];
        aHeart.mWeakestHeadOnePercentThresholds[i] =
            pHeads.front().mOnePercentThresholds[i];
        for (const MetricSliceHeadSummary &aHead : pHeads) {
            if (aHead.mMinimumValues[i] == aHeart.mMinimumValues[i]) {
                aHeart.mMinimumCounts[i] += aHead.mMinimumCounts[i];
            }
            if (aHead.mMaximumValues[i] == aHeart.mMaximumValues[i]) {
                aHeart.mMaximumCounts[i] += aHead.mMaximumCounts[i];
            }
            if (kRankingHigherIsBetter[i]) {
                aHeart.mWeakestHeadOnePercentThresholds[i] = std::min(
                    aHeart.mWeakestHeadOnePercentThresholds[i],
                    aHead.mOnePercentThresholds[i]);
            } else {
                aHeart.mWeakestHeadOnePercentThresholds[i] = std::max(
                    aHeart.mWeakestHeadOnePercentThresholds[i],
                    aHead.mOnePercentThresholds[i]);
            }
        }
    }
    return aHeart;
}

std::string MetricSliceReport(
    const std::vector<MetricSliceHeartSummary> &pHearts,
    const std::size_t pFirstHeartIndex,
    const std::size_t pRequestedHeartCount,
    const std::uint64_t pTrialsPerHead) {
    std::ostringstream aReport;
    std::uint64_t aTotalValid = 0ULL;
    std::uint64_t aTotalRaw = 0ULL;
    std::uint64_t aDirectionalBestJoint = 0ULL;
    std::uint64_t aOnePercentJoint = 0ULL;
    std::uint64_t aProposedJoint = 0ULL;
    for (const MetricSliceHeartSummary &aHeart : pHearts) {
        aTotalValid += aHeart.mValidTrials;
        aTotalRaw += aHeart.mRawAttempts;
        aDirectionalBestJoint += aHeart.mDirectionalBestJointCount;
        aOnePercentJoint += aHeart.mOnePercentJointCount;
        aProposedJoint += aHeart.mProposedGateJointCount;
    }

    aReport << "LONG METRIC SLICE EXPLORE\n"
            << "=========================\n\n"
            << "trials_per_head=" << pTrialsPerHead << "\n"
            << "heads_per_heart="
            << LoopHeadFarmer::kPatternsPerCore << "\n"
            << "first_heart=" << pFirstHeartIndex << "\n"
            << "requested_hearts=" << pRequestedHeartCount << "\n"
            << "completed_hearts=" << pHearts.size() << "\n"
            << "valid_loops=" << aTotalValid << "\n"
            << "raw_attempts=" << aTotalRaw << "\n\n"
            << "Directional best means maximum for higher-is-better and "
               "minimum for lower-is-better. The one-percent clamp is the "
               "weakest head-local top-one-percent threshold in each heart."
               "\n\n";

    aReport << "GLOBAL INVARIANTS (NO OBSERVED VARIATION)\n";
    std::size_t aInvariantCount = 0U;
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        int aMinimum = std::numeric_limits<int>::max();
        int aMaximum = std::numeric_limits<int>::min();
        for (const MetricSliceHeartSummary &aHeart : pHearts) {
            aMinimum = std::min(aMinimum, aHeart.mMinimumValues[i]);
            aMaximum = std::max(aMaximum, aHeart.mMaximumValues[i]);
        }
        if (aMinimum == aMaximum) {
            ++aInvariantCount;
            aReport << "  " << (i + 1U) << ". "
                    << kRankingMetricNames[i] << " = " << aMinimum << "\n";
        }
    }
    aReport << "  count=" << aInvariantCount << "\n\n";

    aReport << "PROPOSED GATES PASSED BY EVERY OBSERVED LOOP\n";
    std::size_t aUniversalGateCount = 0U;
    for (std::size_t i = 0U;
         i < kProposedMustHaveGates.size();
         ++i) {
        std::uint64_t aPasses = 0ULL;
        for (const MetricSliceHeartSummary &aHeart : pHearts) {
            aPasses += aHeart.mProposedGatePassCounts[i];
        }
        if (aPasses == aTotalValid) {
            ++aUniversalGateCount;
            const MetricGate &aGate = kProposedMustHaveGates[i];
            aReport << "  " << (aGate.mMetric + 1U) << ". "
                    << kRankingMetricNames[aGate.mMetric]
                    << (kRankingHigherIsBetter[aGate.mMetric]
                            ? " >= " : " <= ")
                    << aGate.mThreshold << "\n";
        }
    }
    aReport << "  count=" << aUniversalGateCount << "/"
            << kProposedMustHaveGates.size() << "\n\n";

    aReport << "PROPOSED GATE SURVIVAL\n";
    for (std::size_t i = 0U;
         i < kProposedMustHaveGates.size();
         ++i) {
        std::uint64_t aPasses = 0ULL;
        for (const MetricSliceHeartSummary &aHeart : pHearts) {
            aPasses += aHeart.mProposedGatePassCounts[i];
        }
        const MetricGate &aGate = kProposedMustHaveGates[i];
        const double aRate = aTotalValid == 0ULL
            ? 0.0
            : (static_cast<double>(aPasses) * 100.0) /
                static_cast<double>(aTotalValid);
        aReport << "  " << std::setw(2) << (aGate.mMetric + 1U)
                << ". " << std::left << std::setw(48)
                << kRankingMetricNames[aGate.mMetric] << std::right
                << (kRankingHigherIsBetter[aGate.mMetric]
                        ? " >= " : " <= ")
                << std::setw(6) << aGate.mThreshold
                << "  " << std::setw(12) << aPasses << "/"
                << aTotalValid << "  " << std::fixed
                << std::setprecision(4) << aRate << "%\n";
    }
    aReport << "\n";

    aReport << "SAME RAW MAXIMUM IN EVERY COMPLETED HEART\n";
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        bool aSame = !pHearts.empty();
        const int aValue = pHearts.empty()
            ? 0 : pHearts.front().mMaximumValues[i];
        for (const MetricSliceHeartSummary &aHeart : pHearts) {
            aSame = aSame && (aHeart.mMaximumValues[i] == aValue);
        }
        if (aSame) {
            std::uint64_t aMinimumCount =
                std::numeric_limits<std::uint64_t>::max();
            std::uint64_t aMaximumCount = 0ULL;
            for (const MetricSliceHeartSummary &aHeart : pHearts) {
                aMinimumCount = std::min(
                    aMinimumCount, aHeart.mMaximumCounts[i]);
                aMaximumCount = std::max(
                    aMaximumCount, aHeart.mMaximumCounts[i]);
            }
            aReport << "  " << (i + 1U) << ". "
                    << kRankingMetricNames[i] << " = " << aValue
                    << "  heart tie counts=" << aMinimumCount << ".."
                    << aMaximumCount << "\n";
        }
    }
    aReport << "\nSAME DIRECTIONAL BEST IN EVERY COMPLETED HEART\n";
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        bool aSame = !pHearts.empty();
        const int aValue = pHearts.empty()
            ? 0 : pHearts.front().mDirectionalBestValues[i];
        for (const MetricSliceHeartSummary &aHeart : pHearts) {
            aSame = aSame &&
                (aHeart.mDirectionalBestValues[i] == aValue);
        }
        if (aSame) {
            std::uint64_t aMinimumCount =
                std::numeric_limits<std::uint64_t>::max();
            std::uint64_t aMaximumCount = 0ULL;
            for (const MetricSliceHeartSummary &aHeart : pHearts) {
                const std::uint64_t aCount =
                    kRankingHigherIsBetter[i]
                        ? aHeart.mMaximumCounts[i]
                        : aHeart.mMinimumCounts[i];
                aMinimumCount = std::min(aMinimumCount, aCount);
                aMaximumCount = std::max(aMaximumCount, aCount);
            }
            aReport << "  " << (i + 1U) << ". "
                    << kRankingMetricNames[i] << " = " << aValue
                    << "  heart tie counts=" << aMinimumCount << ".."
                    << aMaximumCount << "\n";
        }
    }

    aReport << "\nJOINT ATTAINABILITY\n"
            << "  all head-local directional bests simultaneously: "
            << aDirectionalBestJoint << "/" << aTotalValid << "\n"
            << "  all head-local one-percent clamps simultaneously: "
            << aOnePercentJoint << "/" << aTotalValid << "\n"
            << "  all proposed universal gates simultaneously: "
            << aProposedJoint << "/" << aTotalValid << "\n\n";

    aReport << "PER-METRIC SLICES\n"
            << " # | DIR | GLOBAL RANGE | HEART MAX RANGE | HEART BEST RANGE "
               "| 1% CLAMP RANGE\n"
            << "---+-----+--------------+-----------------+------------------"
               "+----------------\n";
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        int aGlobalMinimum = std::numeric_limits<int>::max();
        int aGlobalMaximum = std::numeric_limits<int>::min();
        int aHeartMaximumMinimum = std::numeric_limits<int>::max();
        int aHeartMaximumMaximum = std::numeric_limits<int>::min();
        int aHeartBestMinimum = std::numeric_limits<int>::max();
        int aHeartBestMaximum = std::numeric_limits<int>::min();
        int aClampMinimum = std::numeric_limits<int>::max();
        int aClampMaximum = std::numeric_limits<int>::min();
        for (const MetricSliceHeartSummary &aHeart : pHearts) {
            aGlobalMinimum = std::min(
                aGlobalMinimum, aHeart.mMinimumValues[i]);
            aGlobalMaximum = std::max(
                aGlobalMaximum, aHeart.mMaximumValues[i]);
            aHeartMaximumMinimum = std::min(
                aHeartMaximumMinimum, aHeart.mMaximumValues[i]);
            aHeartMaximumMaximum = std::max(
                aHeartMaximumMaximum, aHeart.mMaximumValues[i]);
            aHeartBestMinimum = std::min(
                aHeartBestMinimum, aHeart.mDirectionalBestValues[i]);
            aHeartBestMaximum = std::max(
                aHeartBestMaximum, aHeart.mDirectionalBestValues[i]);
            aClampMinimum = std::min(
                aClampMinimum,
                aHeart.mWeakestHeadOnePercentThresholds[i]);
            aClampMaximum = std::max(
                aClampMaximum,
                aHeart.mWeakestHeadOnePercentThresholds[i]);
        }
        aReport << std::setw(2) << (i + 1U) << " | "
                << (kRankingHigherIsBetter[i] ? "HI " : "LO ") << " | "
                << std::setw(6) << aGlobalMinimum << ".."
                << std::setw(6) << aGlobalMaximum << " | "
                << std::setw(6) << aHeartMaximumMinimum << ".."
                << std::setw(6) << aHeartMaximumMaximum << " | "
                << std::setw(6) << aHeartBestMinimum << ".."
                << std::setw(6) << aHeartBestMaximum << " | "
                << std::setw(6) << aClampMinimum << ".."
                << std::setw(6) << aClampMaximum << "  "
                << kRankingMetricNames[i] << "\n";
    }

    aReport << "\nPER-HEART JOINT SURVIVAL\n"
            << "heart | valid      | exact best | all 1% clamps | proposed\n"
            << "------+------------+------------+---------------+------------\n";
    for (std::size_t i = 0U; i < pHearts.size(); ++i) {
        const MetricSliceHeartSummary &aHeart = pHearts[i];
        aReport << std::setw(5) << (pFirstHeartIndex + i) << " | "
                << std::setw(10) << aHeart.mValidTrials << " | "
                << std::setw(10) << aHeart.mDirectionalBestJointCount
                << " | " << std::setw(13) << aHeart.mOnePercentJointCount
                << " | " << std::setw(10)
                << aHeart.mProposedGateJointCount << "\n";
    }
    return aReport.str();
}

std::string CsvMetricName(const char *pName) {
    std::string aResult;
    bool aLastWasUnderscore = false;
    for (const unsigned char aCharacter : std::string(pName)) {
        if (((aCharacter >= 'a') && (aCharacter <= 'z')) ||
            ((aCharacter >= '0') && (aCharacter <= '9'))) {
            aResult.push_back(static_cast<char>(aCharacter));
            aLastWasUnderscore = false;
        } else if ((aCharacter >= 'A') && (aCharacter <= 'Z')) {
            aResult.push_back(static_cast<char>(
                aCharacter - 'A' + 'a'));
            aLastWasUnderscore = false;
        } else if (!aResult.empty() && !aLastWasUnderscore) {
            aResult.push_back('_');
            aLastWasUnderscore = true;
        }
    }
    if (!aResult.empty() && (aResult.back() == '_')) {
        aResult.pop_back();
    }
    return aResult;
}

std::string MetricTableHeader(const bool pOmitAssumedMetrics = false) {
    std::ostringstream aHeader;
    aHeader << "heart_index,head_index,trial_index,pattern_index,"
               "raw_attempt";
    for (char aSide = 'a'; aSide <= 'b'; ++aSide) {
        for (char aRole = 'a'; aRole <= 'k'; ++aRole) {
            aHeader << ",tail_" << aSide << "_" << aRole;
        }
    }
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        if (pOmitAssumedMetrics &&
            !LoopPlanMinimums::ShouldRecordMetric(i)) {
            continue;
        }
        aHeader << "," << CsvMetricName(kRankingMetricNames[i]);
    }
    aHeader << "\n";
    return aHeader.str();
}

std::string RandomMetricTableHeader() {
    std::ostringstream aHeader;
    aHeader << "heart_index,trial_index,pattern_index,head_rank,raw_attempt";
    for (char aRole = 'a'; aRole <= 'k'; ++aRole) {
        aHeader << ",head_" << aRole;
    }
    for (char aSide = 'a'; aSide <= 'b'; ++aSide) {
        for (char aRole = 'a'; aRole <= 'k'; ++aRole) {
            aHeader << ",tail_" << aSide << "_" << aRole;
        }
    }
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        if (LoopPlanMinimums::ShouldRecordMetric(i)) {
            aHeader << "," << CsvMetricName(kRankingMetricNames[i]);
        }
    }
    aHeader << "\n";
    return aHeader.str();
}

std::string MetricTableShardPath(const std::string &pFolderPath,
                                 const std::uint64_t pTrialsPerHeart,
                                 const std::size_t pHeartIndex) {
    char aTrialFolder[48];
    char aHeartFile[32];
    std::snprintf(aTrialFolder, sizeof(aTrialFolder),
                  "runs_%llu",
                  static_cast<unsigned long long>(pTrialsPerHeart));
    std::snprintf(aHeartFile, sizeof(aHeartFile),
                  "heart_%03zu.csv", pHeartIndex);
    return (std::filesystem::path(ResolvedPath(pFolderPath)) /
            aTrialFolder / aHeartFile)
        .lexically_normal().generic_string();
}

bool LoadValidMetricTableShard(const std::string &pPath,
                               const std::string &pHeader,
                               const std::uint64_t pTrialsPerHeart,
                               bool *pFound,
                               std::vector<std::uint8_t> *pBytes,
                               std::string *pErrorMessage) {
    *pFound = false;
    std::error_code aExistsError;
    if (!std::filesystem::exists(pPath, aExistsError)) {
        return true;
    }
    if (!FileIO::Load(pPath, *pBytes) ||
        (pBytes->size() < pHeader.size()) ||
        !std::equal(pHeader.begin(), pHeader.end(), pBytes->begin()) ||
        (pBytes->back() != '\n')) {
        SetError(pErrorMessage,
                 "Metric table shard was incomplete or invalid: " + pPath);
        return false;
    }
    const std::uint64_t aLineCount = static_cast<std::uint64_t>(
        std::count(pBytes->begin(), pBytes->end(),
                   static_cast<std::uint8_t>('\n')));
    if (aLineCount != (pTrialsPerHeart + 1ULL)) {
        SetError(pErrorMessage,
                 "Metric table shard had the wrong row count: " + pPath);
        return false;
    }
    *pFound = true;
    return true;
}

bool LoadValidFilteredMetricTableShard(
    const std::string &pPath,
    const std::string &pHeader,
    const std::uint64_t pSpinsPerHeart,
    bool *pFound,
    std::uint64_t *pPassingRows,
    std::vector<std::uint8_t> *pBytes,
    std::string *pErrorMessage) {
    *pFound = false;
    *pPassingRows = 0ULL;
    std::error_code aExistsError;
    if (!std::filesystem::exists(pPath, aExistsError)) {
        return true;
    }
    if (!FileIO::Load(pPath, *pBytes) ||
        (pBytes->size() < pHeader.size()) ||
        !std::equal(pHeader.begin(), pHeader.end(), pBytes->begin()) ||
        (pBytes->back() != '\n')) {
        SetError(pErrorMessage,
                 "Filtered metric table shard was incomplete or invalid: " +
                 pPath);
        return false;
    }
    const std::uint64_t aLineCount = static_cast<std::uint64_t>(
        std::count(pBytes->begin(), pBytes->end(),
                   static_cast<std::uint8_t>('\n')));
    if ((aLineCount == 0ULL) ||
        (aLineCount > (pSpinsPerHeart + 1ULL))) {
        SetError(pErrorMessage,
                 "Filtered metric table shard had an invalid row count: " +
                 pPath);
        return false;
    }
    *pPassingRows = aLineCount - 1ULL;
    *pFound = true;
    return true;
}

bool SaveMetricTableShard(const std::string &pPath,
                          const std::vector<std::uint8_t> &pBytes,
                          std::string *pErrorMessage) {
    const std::string aTemporaryPath = pPath + ".tmp";
    if (!FileIO::Save(aTemporaryPath, pBytes)) {
        SetError(pErrorMessage,
                 "Metric table exporter could not save " + pPath);
        return false;
    }
    if (std::rename(aTemporaryPath.c_str(), pPath.c_str()) != 0) {
        const std::string aReason = std::strerror(errno);
        std::error_code aCleanupError;
        std::filesystem::remove(aTemporaryPath, aCleanupError);
        SetError(pErrorMessage,
                 "Metric table exporter could not install " + pPath +
                 ": " + aReason);
        return false;
    }
    return true;
}

std::string MetricTableSchema(const bool pOmitAssumedMetrics = false) {
    std::ostringstream aSchema;
    aSchema << "column_index,column_name,direction,proposed_gate,"
               "proposed_threshold\n";
    std::size_t aColumn = 1U;
    constexpr std::array<const char *, 5U> kIdentityColumns = {
        "heart_index", "head_index", "trial_index", "pattern_index",
        "raw_attempt",
    };
    for (const char *aName : kIdentityColumns) {
        aSchema << aColumn++ << "," << aName << ",identity,no,\n";
    }
    for (char aSide = 'a'; aSide <= 'b'; ++aSide) {
        for (char aRole = 'a'; aRole <= 'k'; ++aRole) {
            aSchema << aColumn++ << ",tail_" << aSide << "_" << aRole
                    << ",recipe,no,\n";
        }
    }
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        if (pOmitAssumedMetrics &&
            !LoopPlanMinimums::ShouldRecordMetric(i)) {
            continue;
        }
        bool aHasGate = false;
        int aThreshold = 0;
        for (const MetricGate &aGate : kProposedMustHaveGates) {
            if (aGate.mMetric == i) {
                aHasGate = true;
                aThreshold = aGate.mThreshold;
                break;
            }
        }
        aSchema << aColumn++ << "," << CsvMetricName(
            kRankingMetricNames[i]) << ","
                << (kRankingHigherIsBetter[i] ? "higher" : "lower")
                << "," << (aHasGate ? "yes" : "no") << ",";
        if (aHasGate) {
            aSchema << aThreshold;
        }
        aSchema << "\n";
    }
    return aSchema.str();
}

std::string RandomMetricTableSchema() {
    std::ostringstream aSchema;
    aSchema << "column_index,column_name,direction,proposed_gate,"
               "proposed_threshold\n";
    std::size_t aColumn = 1U;
    constexpr std::array<const char *, 5U> kIdentityColumns = {
        "heart_index", "trial_index", "pattern_index", "head_rank",
        "raw_attempt",
    };
    for (const char *aName : kIdentityColumns) {
        aSchema << aColumn++ << "," << aName << ",identity,no,\n";
    }
    for (char aRole = 'a'; aRole <= 'k'; ++aRole) {
        aSchema << aColumn++ << ",head_" << aRole
                << ",recipe,no,\n";
    }
    for (char aSide = 'a'; aSide <= 'b'; ++aSide) {
        for (char aRole = 'a'; aRole <= 'k'; ++aRole) {
            aSchema << aColumn++ << ",tail_" << aSide << "_" << aRole
                    << ",recipe,no,\n";
        }
    }
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        if (!LoopPlanMinimums::ShouldRecordMetric(i)) {
            continue;
        }
        bool aHasGate = false;
        int aThreshold = 0;
        for (const MetricGate &aGate : kProposedMustHaveGates) {
            if (aGate.mMetric == i) {
                aHasGate = true;
                aThreshold = aGate.mThreshold;
                break;
            }
        }
        aSchema << aColumn++ << "," << CsvMetricName(
            kRankingMetricNames[i]) << ","
                << (kRankingHigherIsBetter[i] ? "higher" : "lower")
                << "," << (aHasGate ? "yes" : "no") << ",";
        if (aHasGate) {
            aSchema << aThreshold;
        }
        aSchema << "\n";
    }
    return aSchema.str();
}

//
// Per-heart gold-rate search
//

constexpr std::array<std::uint8_t, 8U> kGoldStatsFileMagic = {
    'M', 'M', 'G', 'O', 'L', 'D', '1', '1',
};
// Version 2 records are scored against one range shared by the complete
// heart set. Version 1 was normalized independently for each heart.
constexpr std::uint32_t kGoldStatsFileVersion = 2U;
constexpr std::uint32_t kGoldStatsLegacyFileVersion = 1U;
constexpr std::size_t kGoldCandidateCount = 3U;
constexpr std::size_t kGoldSelectedHeartCount = 24U;
constexpr std::uint32_t kGoldPercentScale = 1'000'000U;
constexpr std::size_t kGoldStatsHeaderByteCount = 64U;
constexpr std::size_t kGoldCandidateByteCount =
    (3U * sizeof(std::uint32_t)) +
    (3U * kRoleCount) +
    (kScoreFieldCount * sizeof(std::uint32_t));
constexpr std::size_t kGoldStatsFileByteCount =
    kGoldStatsHeaderByteCount +
    (3U * kScoreFieldCount * sizeof(std::uint32_t)) +
    (kGoldCandidateCount * kGoldCandidateByteCount);

struct GoldSearchCandidate {
    LoopHeadPattern11 mHead;
    LoopTailPattern11 mTail;
    MetricValues mValues{};
    std::size_t mPatternIndex = 0U;
};

struct RankedGoldCandidate {
    std::size_t mCandidateIndex = 0U;
    double mScore = 0.0;
};

std::uint64_t GoldHashByte(std::uint64_t pHash,
                           const std::uint8_t pByte) {
    return (pHash ^ static_cast<std::uint64_t>(pByte)) *
        0x100000001B3ULL;
}

std::uint64_t GoldHeartSignature(const LoopCorePattern11 &pHeart) {
    std::uint64_t aHash = 0xCBF29CE484222325ULL;
    for (const auto &aRound : pHeart.mRounds) {
        for (const std::uint8_t aRole : aRound) {
            aHash = GoldHashByte(aHash, aRole);
        }
    }
    return aHash;
}

std::uint64_t GoldWeightSignature() {
    std::uint64_t aHash = 0xCBF29CE484222325ULL;
    for (const LoopWeights::MetricWeight &aMetric :
         LoopWeights::kMetrics) {
        for (const char *aCharacter = aMetric.mName;
             *aCharacter != '\0';
             ++aCharacter) {
            aHash = GoldHashByte(
                aHash, static_cast<std::uint8_t>(*aCharacter));
        }
        aHash = GoldHashByte(aHash, 0U);
        aHash = GoldHashByte(
            aHash, aMetric.mHigherIsBetter ? 1U : 0U);
        for (unsigned i = 0U; i < sizeof(aMetric.mWeight); ++i) {
            aHash = GoldHashByte(
                aHash,
                static_cast<std::uint8_t>(
                    aMetric.mWeight >> (i * 8U)));
        }
    }
    return aHash;
}

std::uint64_t Top40ScoringSignature() {
    std::uint64_t aHash = GoldWeightSignature();
    // Version the per-metric integer-rounding score itself, not only the
    // weight table used to construct it.
    aHash = GoldHashByte(aHash, 1U);
    for (const LoopScorer::Measure &aMeasure : LoopScorer::kMeasures) {
        aHash = GoldHashByte(
            aHash, aMeasure.mHigherIsBetter ? 1U : 0U);
        std::uint32_t aWeightBits = 0U;
        static_assert(sizeof(aWeightBits) == sizeof(aMeasure.mWeight));
        std::memcpy(&aWeightBits, &aMeasure.mWeight, sizeof(aWeightBits));
        for (unsigned aByte = 0U; aByte < sizeof(aWeightBits); ++aByte) {
            aHash = GoldHashByte(
                aHash,
                static_cast<std::uint8_t>(aWeightBits >> (aByte * 8U)));
        }
        const std::array<std::uint32_t, 2U> aLimits = {
            static_cast<std::uint32_t>(aMeasure.mMinimum),
            static_cast<std::uint32_t>(aMeasure.mMaximum),
        };
        for (const std::uint32_t aLimit : aLimits) {
            for (unsigned aByte = 0U; aByte < sizeof(aLimit); ++aByte) {
                aHash = GoldHashByte(
                    aHash,
                    static_cast<std::uint8_t>(aLimit >> (aByte * 8U)));
            }
        }
    }
    return aHash;
}

constexpr std::size_t kTop40CandidateCount = 40U;

struct Top40RetainedCandidate {
    GoldSearchCandidate mCandidate;
    int mScore = 0;
};

struct Top40HeartSummary {
    std::size_t mHeartIndex = 0U;
    std::uint64_t mTrials = 0ULL;
    std::uint64_t mRawAttempts = 0ULL;
    std::uint64_t mScoreSum = 0ULL;
    int mBestScore = 0;
    int mWorstScore = 0;
    std::string mPath;
};

bool Top40CandidateIsBetter(const Top40RetainedCandidate &pA,
                            const Top40RetainedCandidate &pB) {
    if (pA.mScore != pB.mScore) {
        return pA.mScore > pB.mScore;
    }
    if (pA.mCandidate.mHead.mPermutationRank !=
        pB.mCandidate.mHead.mPermutationRank) {
        return pA.mCandidate.mHead.mPermutationRank <
            pB.mCandidate.mHead.mPermutationRank;
    }
    if (pA.mCandidate.mPatternIndex != pB.mCandidate.mPatternIndex) {
        return pA.mCandidate.mPatternIndex <
            pB.mCandidate.mPatternIndex;
    }
    if (pA.mCandidate.mTail.mOrbiterAForWanderer !=
        pB.mCandidate.mTail.mOrbiterAForWanderer) {
        return pA.mCandidate.mTail.mOrbiterAForWanderer <
            pB.mCandidate.mTail.mOrbiterAForWanderer;
    }
    return pA.mCandidate.mTail.mOrbiterBForWanderer <
        pB.mCandidate.mTail.mOrbiterBForWanderer;
}

bool Top40CandidateIsDuplicate(
    const Top40RetainedCandidate &pCandidate,
    const std::vector<Top40RetainedCandidate> &pRetained) {
    for (const Top40RetainedCandidate &aExisting : pRetained) {
        if ((aExisting.mCandidate.mHead.mPermutationRank ==
             pCandidate.mCandidate.mHead.mPermutationRank) &&
            (aExisting.mCandidate.mPatternIndex ==
             pCandidate.mCandidate.mPatternIndex) &&
            (aExisting.mCandidate.mTail.mOrbiterAForWanderer ==
             pCandidate.mCandidate.mTail.mOrbiterAForWanderer) &&
            (aExisting.mCandidate.mTail.mOrbiterBForWanderer ==
             pCandidate.mCandidate.mTail.mOrbiterBForWanderer)) {
            return true;
        }
    }
    return false;
}

std::string Top40CsvHeader() {
    std::ostringstream aHeader;
    aHeader << "heart_index,trials_per_heart,raw_attempts,heart_signature,"
               "scoring_signature,rank,integer_score,score_percent,"
               "head_permutation_rank,head_pattern_index,"
               "head_wanderer_for_orbiter,tail_orbiter_a_for_wanderer,"
               "tail_orbiter_b_for_wanderer";
    for (const LoopWeights::MetricWeight &aMetric : LoopWeights::kMetrics) {
        aHeader << "," << aMetric.mName;
    }
    aHeader << "\n";
    return aHeader.str();
}

std::string Top40RoleList(
    const std::array<std::uint8_t, kRoleCount> &pRoles) {
    std::string aList;
    aList.reserve((2U * kRoleCount) - 1U);
    for (std::size_t i = 0U; i < pRoles.size(); ++i) {
        if (i != 0U) {
            aList.push_back(' ');
        }
        aList.push_back(static_cast<char>('A' + pRoles[i]));
    }
    return aList;
}

bool SaveTop40TextAtomically(const std::string &pPath,
                             const std::string &pText,
                             std::string *pErrorMessage) {
    const std::vector<std::uint8_t> aBytes(pText.begin(), pText.end());
    const std::string aTemporaryPath = pPath + ".tmp";
    if (!FileIO::Save(aTemporaryPath, aBytes)) {
        SetError(pErrorMessage,
                 "Top-40 search could not save " + aTemporaryPath);
        return false;
    }
    if (std::rename(aTemporaryPath.c_str(), pPath.c_str()) != 0) {
        SetError(pErrorMessage,
                 "Top-40 search could not commit " + pPath + ": " +
                 std::strerror(errno));
        return false;
    }
    return true;
}

std::string Top40HeartPath(const std::string &pFolderPath,
                           const std::size_t pHeartIndex) {
    char aFileName[64];
    std::snprintf(aFileName, sizeof(aFileName),
                  "heart_%03zu_top_40.csv", pHeartIndex);
    return (std::filesystem::path(ResolvedPath(pFolderPath)) / aFileName)
        .lexically_normal().generic_string();
}

bool ParseUnsigned(const std::string &pText, std::uint64_t *pValue) {
    try {
        std::size_t aConsumed = 0U;
        const std::uint64_t aValue = std::stoull(pText, &aConsumed, 10);
        if (aConsumed != pText.size()) {
            return false;
        }
        *pValue = aValue;
        return true;
    } catch (...) {
        return false;
    }
}

bool LoadTop40HeartSummary(const std::string &pPath,
                           const std::size_t pExpectedHeartIndex,
                           const std::uint64_t pExpectedTrials,
                           const std::uint64_t pExpectedHeartSignature,
                           const std::uint64_t pExpectedScoringSignature,
                           Top40HeartSummary *pSummary) {
    std::ifstream aInput(pPath);
    if (!aInput.is_open()) {
        return false;
    }
    std::string aLine;
    if (!std::getline(aInput, aLine) ||
        ((aLine + "\n") != Top40CsvHeader())) {
        return false;
    }

    Top40HeartSummary aSummary;
    aSummary.mHeartIndex = pExpectedHeartIndex;
    aSummary.mTrials = pExpectedTrials;
    aSummary.mPath = pPath;
    for (std::size_t aRow = 0U; aRow < kTop40CandidateCount; ++aRow) {
        if (!std::getline(aInput, aLine)) {
            return false;
        }
        std::istringstream aRowStream(aLine);
        std::array<std::uint64_t, 7U> aLeading{};
        for (std::size_t i = 0U; i < aLeading.size(); ++i) {
            std::string aField;
            if (!std::getline(aRowStream, aField, ',') ||
                !ParseUnsigned(aField, &aLeading[i])) {
                return false;
            }
        }
        if ((aLeading[0] != pExpectedHeartIndex) ||
            (aLeading[1] != pExpectedTrials) ||
            (aLeading[3] != pExpectedHeartSignature) ||
            (aLeading[4] != pExpectedScoringSignature) ||
            (aLeading[5] != (aRow + 1U)) ||
            (aLeading[6] >
             static_cast<std::uint64_t>(LoopScorer::kMaximumScore))) {
            return false;
        }
        if (aRow == 0U) {
            aSummary.mRawAttempts = aLeading[2];
            aSummary.mBestScore = static_cast<int>(aLeading[6]);
        } else if (aLeading[2] != aSummary.mRawAttempts) {
            return false;
        }
        aSummary.mWorstScore = static_cast<int>(aLeading[6]);
        aSummary.mScoreSum += aLeading[6];
    }
    while (std::getline(aInput, aLine)) {
        if (!aLine.empty()) {
            return false;
        }
    }
    *pSummary = aSummary;
    return true;
}

bool SaveTop40Heart(
    const std::string &pPath,
    const std::size_t pHeartIndex,
    const std::uint64_t pTrials,
    const std::uint64_t pRawAttempts,
    const std::uint64_t pHeartSignature,
    const std::uint64_t pScoringSignature,
    const std::vector<Top40RetainedCandidate> &pRetained,
    std::string *pErrorMessage) {
    std::ostringstream aCsv;
    aCsv << Top40CsvHeader();
    aCsv << std::fixed << std::setprecision(6);
    for (std::size_t i = 0U; i < pRetained.size(); ++i) {
        const Top40RetainedCandidate &aRetained = pRetained[i];
        const GoldSearchCandidate &aCandidate = aRetained.mCandidate;
        aCsv << pHeartIndex << "," << pTrials << "," << pRawAttempts
             << "," << pHeartSignature << "," << pScoringSignature
             << "," << (i + 1U) << "," << aRetained.mScore << ","
             << (100.0 * static_cast<double>(aRetained.mScore) /
                 static_cast<double>(LoopScorer::kMaximumScore))
             << "," << aCandidate.mHead.mPermutationRank
             << "," << aCandidate.mPatternIndex
             << "," << Top40RoleList(
                    aCandidate.mHead.mWandererForOrbiter)
             << "," << Top40RoleList(
                    aCandidate.mTail.mOrbiterAForWanderer)
             << "," << Top40RoleList(
                    aCandidate.mTail.mOrbiterBForWanderer);
        for (const int aValue : aCandidate.mValues) {
            aCsv << "," << aValue;
        }
        aCsv << "\n";
    }
    return SaveTop40TextAtomically(pPath, aCsv.str(), pErrorMessage);
}

std::string GoldStatsPath(const std::string &pFolderPath,
                          const std::size_t pHeartIndex,
                          const std::string &pHeartName = "") {
    std::string aFileName;
    if (pHeartName.empty()) {
        char aIndexedName[64];
        std::snprintf(aIndexedName, sizeof(aIndexedName),
                      "heart_%03zu_gold_stats.bin", pHeartIndex);
        aFileName = aIndexedName;
    } else {
        aFileName = pHeartName + "_gold_stats.bin";
    }
    return (std::filesystem::path(ResolvedPath(pFolderPath)) /
            aFileName).lexically_normal().generic_string();
}

std::string GoldRecipeKey(const LoopHeadPattern11 &pHead,
                          const std::size_t pPatternIndex,
                          const LoopTailPattern11 &pTail) {
    std::string aKey;
    aKey.reserve(8U + (2U * kRoleCount));
    const std::uint32_t aHeadRank = pHead.mPermutationRank;
    const std::uint32_t aPattern =
        static_cast<std::uint32_t>(pPatternIndex);
    for (unsigned i = 0U; i < 4U; ++i) {
        aKey.push_back(static_cast<char>(aHeadRank >> (i * 8U)));
    }
    for (unsigned i = 0U; i < 4U; ++i) {
        aKey.push_back(static_cast<char>(aPattern >> (i * 8U)));
    }
    for (const std::uint8_t aRole : pTail.mOrbiterAForWanderer) {
        aKey.push_back(static_cast<char>(aRole));
    }
    for (const std::uint8_t aRole : pTail.mOrbiterBForWanderer) {
        aKey.push_back(static_cast<char>(aRole));
    }
    return aKey;
}

bool GoldCandidateIsBetter(
    const RankedGoldCandidate &pA,
    const RankedGoldCandidate &pB,
    const std::vector<GoldSearchCandidate> &pCandidates) {
    if (pA.mScore != pB.mScore) {
        return pA.mScore > pB.mScore;
    }
    const GoldSearchCandidate &a = pCandidates[pA.mCandidateIndex];
    const GoldSearchCandidate &b = pCandidates[pB.mCandidateIndex];
    if (a.mHead.mPermutationRank != b.mHead.mPermutationRank) {
        return a.mHead.mPermutationRank < b.mHead.mPermutationRank;
    }
    if (a.mPatternIndex != b.mPatternIndex) {
        return a.mPatternIndex < b.mPatternIndex;
    }
    if (a.mTail.mOrbiterAForWanderer !=
        b.mTail.mOrbiterAForWanderer) {
        return a.mTail.mOrbiterAForWanderer <
            b.mTail.mOrbiterAForWanderer;
    }
    return a.mTail.mOrbiterBForWanderer <
        b.mTail.mOrbiterBForWanderer;
}

std::uint32_t GoldPercentFixed(const double pPercent) {
    const double aClamped = pPercent < 0.0
        ? 0.0
        : (pPercent > 1.0 ? 1.0 : pPercent);
    return static_cast<std::uint32_t>(std::llround(
        aClamped * static_cast<double>(kGoldPercentScale)));
}

template <typename CandidateConsumer>
bool StreamCoreGoldCandidates(
    const LoopCorePattern11 &pCore,
    const std::size_t pHeartIndex,
    const std::uint64_t pTrials,
    const std::uint64_t pProgressInterval,
    const char *pPhaseName,
    CandidateConsumer pConsume,
    std::uint64_t *pRawAttempts,
    std::string *pErrorMessage) {
    LoopNewHeart11 aHeart;
    aHeart.mHeart = pCore;
    const DistanceMatrix aDistances =
        HeartTemporalDistances(aHeart.mHeart);
    const std::uint64_t aHeartSignature =
        GoldHeartSignature(aHeart.mHeart);
    Generator aGenerator(MixFarmSeed(
        0x434F5245474F4C44ULL ^
        aHeartSignature ^
        ((static_cast<std::uint64_t>(pHeartIndex) + 1ULL) *
         0xD1342543DE82EF95ULL) ^
        pTrials));

    std::uint64_t aValidTrials = 0ULL;
    std::uint64_t aRawAttempts = 0ULL;
    const std::uint64_t aMaximumAttempts = pTrials >
        ((std::numeric_limits<std::uint64_t>::max() - 4096ULL) /
         256ULL)
            ? std::numeric_limits<std::uint64_t>::max()
            : (pTrials * 256ULL) + 4096ULL;
    while ((aValidTrials < pTrials) &&
           (aRawAttempts < aMaximumAttempts)) {
        ++aRawAttempts;
        LoopHeadPattern11 aHead;
        aHead.mWandererForOrbiter = IdentityRoles();
        Shuffle(&aHead.mWandererForOrbiter, &aGenerator);
        aHead.mPermutationRank = LoopHeadFarmer::Rank(aHead);
        if (!LoopHeadFarmer::IsValid(aHead)) {
            SetError(pErrorMessage,
                     "Core gold search generated an invalid head");
            return false;
        }

        const std::size_t aPatternIndex = aGenerator.Below(
            LoopHeadFarmer::kRetainedPatternCount);
        const PairInfoMatrix aPairs = MakePairInfo(
            aHeart.mHeart,
            aHead,
            aPatternIndex,
            aDistances);
        LoopTailPattern11 aTail;
        if (!GenerateTail(aPairs, &aGenerator, &aTail)) {
            continue;
        }
        Candidate aEvaluated;
        if (!EvaluateAscendencyCandidate(
                aHeart,
                aHead,
                aPatternIndex,
                aPairs,
                aTail,
                &aEvaluated,
                true)) {
            continue;
        }

        GoldSearchCandidate aCandidate;
        aCandidate.mHead = aHead;
        aCandidate.mTail = aTail;
        aCandidate.mPatternIndex = aPatternIndex;
        aCandidate.mValues = RankingDisplayValues(aEvaluated.mScore);
        pConsume(aCandidate);
        ++aValidTrials;

        if ((pProgressInterval != 0ULL) &&
            ((aValidTrials % pProgressInterval) == 0ULL)) {
            std::printf("%s heart %03zu: valid=%llu/%llu raw=%llu\n",
                        pPhaseName,
                        pHeartIndex,
                        static_cast<unsigned long long>(aValidTrials),
                        static_cast<unsigned long long>(pTrials),
                        static_cast<unsigned long long>(aRawAttempts));
        }
    }
    if (aValidTrials != pTrials) {
        SetError(pErrorMessage,
                 "Core gold search exhausted its attempt budget for heart " +
                 std::to_string(pHeartIndex));
        return false;
    }
    *pRawAttempts = aRawAttempts;
    return true;
}

bool GoldStatsFileMatches(
    const std::string &pPath,
    const std::size_t pExpectedHeartIndex,
    const std::uint64_t pExpectedTrials,
    const std::uint64_t pExpectedHeartSignature,
    const std::uint64_t pExpectedWeightSignature,
    std::array<std::uint32_t, kGoldCandidateCount> *pCandidateScores =
        nullptr,
    std::array<std::uint32_t, kScoreFieldCount> *pGoldPercents =
        nullptr) {
    std::error_code aExistsError;
    if (!std::filesystem::exists(pPath, aExistsError)) {
        return false;
    }
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes) ||
        (aBytes.size() != kGoldStatsFileByteCount) ||
        !std::equal(kGoldStatsFileMagic.begin(),
                    kGoldStatsFileMagic.end(),
                    aBytes.begin())) {
        return false;
    }
    std::size_t aOffset = kGoldStatsFileMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    const std::uint32_t aHeartIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aRoleCount = Read32(aBytes, &aOffset);
    const std::uint32_t aMetricCount = Read32(aBytes, &aOffset);
    const std::uint32_t aCandidateCount = Read32(aBytes, &aOffset);
    const std::uint32_t aPercentScale = Read32(aBytes, &aOffset);
    const std::uint64_t aTrials = Read64(aBytes, &aOffset);
    (void)Read64(aBytes, &aOffset); // Raw attempts are informational.
    const std::uint64_t aHeartSignature = Read64(aBytes, &aOffset);
    const std::uint64_t aWeightSignature = Read64(aBytes, &aOffset);
    const bool aMatches = (aVersion == kGoldStatsFileVersion) &&
        (aHeartIndex == pExpectedHeartIndex) &&
        (aRoleCount == kRoleCount) &&
        (aMetricCount == kScoreFieldCount) &&
        (aCandidateCount == kGoldCandidateCount) &&
        (aPercentScale == kGoldPercentScale) &&
        (aTrials == pExpectedTrials) &&
        (aHeartSignature == pExpectedHeartSignature) &&
        (aWeightSignature == pExpectedWeightSignature);
    if (!aMatches) {
        return false;
    }

    if (pGoldPercents != nullptr) {
        aOffset = kGoldStatsHeaderByteCount +
            (2U * kScoreFieldCount * sizeof(std::uint32_t));
        for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
            (*pGoldPercents)[i] = Read32(aBytes, &aOffset);
        }
    }

    if (pCandidateScores != nullptr) {
        aOffset = kGoldStatsHeaderByteCount +
            (3U * kScoreFieldCount * sizeof(std::uint32_t));
        for (std::size_t i = 0U; i < kGoldCandidateCount; ++i) {
            (*pCandidateScores)[i] = Read32(aBytes, &aOffset);
            aOffset += kGoldCandidateByteCount - sizeof(std::uint32_t);
        }
    }
    return true;
}

bool LoadGoldRangeForUniversalNormalization(
    const std::string &pPath,
    const std::uint64_t pExpectedTrials,
    const std::uint64_t pExpectedHeartSignature,
    const std::uint64_t pExpectedWeightSignature,
    MetricValues *pMinimums,
    MetricValues *pMaximums,
    std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes) ||
        (aBytes.size() != kGoldStatsFileByteCount) ||
        !std::equal(kGoldStatsFileMagic.begin(),
                    kGoldStatsFileMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Universal gold normalization could not load " + pPath);
        return false;
    }

    std::size_t aOffset = kGoldStatsFileMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    (void)Read32(aBytes, &aOffset); // Source-heart index.
    const std::uint32_t aRoleCount = Read32(aBytes, &aOffset);
    const std::uint32_t aMetricCount = Read32(aBytes, &aOffset);
    const std::uint32_t aCandidateCount = Read32(aBytes, &aOffset);
    const std::uint32_t aPercentScale = Read32(aBytes, &aOffset);
    const std::uint64_t aTrials = Read64(aBytes, &aOffset);
    (void)Read64(aBytes, &aOffset); // Raw attempts.
    const std::uint64_t aHeartSignature = Read64(aBytes, &aOffset);
    const std::uint64_t aWeightSignature = Read64(aBytes, &aOffset);
    if (((aVersion != kGoldStatsLegacyFileVersion) &&
         (aVersion != kGoldStatsFileVersion)) ||
        (aRoleCount != kRoleCount) ||
        (aMetricCount != kScoreFieldCount) ||
        (aCandidateCount != kGoldCandidateCount) ||
        (aPercentScale != kGoldPercentScale) ||
        (aTrials != pExpectedTrials) ||
        (aHeartSignature != pExpectedHeartSignature) ||
        (aWeightSignature != pExpectedWeightSignature)) {
        SetError(pErrorMessage,
                 "Universal gold normalization metadata did not match " +
                 pPath);
        return false;
    }

    *pMinimums = ReadMetricValues(aBytes, &aOffset);
    *pMaximums = ReadMetricValues(aBytes, &aOffset);
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        if ((*pMinimums)[i] > (*pMaximums)[i]) {
            SetError(pErrorMessage,
                     "Universal gold normalization found an inverted "
                     "range in " + pPath);
            return false;
        }
    }
    return true;
}

bool SaveGoldStats(
    const std::string &pPath,
    const std::size_t pHeartIndex,
    const std::uint64_t pTrials,
    const std::uint64_t pRawAttempts,
    const std::uint64_t pHeartSignature,
    const std::uint64_t pWeightSignature,
    const MetricValues &pMinimums,
    const MetricValues &pMaximums,
    const std::array<std::uint32_t, kScoreFieldCount> &pGoldPercents,
    const std::array<RankedGoldCandidate, kGoldCandidateCount> &pTop,
    const std::vector<GoldSearchCandidate> &pCandidates,
    std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kGoldStatsFileByteCount);
    aBytes.insert(aBytes.end(),
                  kGoldStatsFileMagic.begin(),
                  kGoldStatsFileMagic.end());
    Append32(&aBytes, kGoldStatsFileVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(pHeartIndex));
    Append32(&aBytes, static_cast<std::uint32_t>(kRoleCount));
    Append32(&aBytes, static_cast<std::uint32_t>(kScoreFieldCount));
    Append32(&aBytes, static_cast<std::uint32_t>(kGoldCandidateCount));
    Append32(&aBytes, kGoldPercentScale);
    Append64(&aBytes, pTrials);
    Append64(&aBytes, pRawAttempts);
    Append64(&aBytes, pHeartSignature);
    Append64(&aBytes, pWeightSignature);
    AppendMetricValues(&aBytes, pMinimums);
    AppendMetricValues(&aBytes, pMaximums);
    for (const std::uint32_t aPercent : pGoldPercents) {
        Append32(&aBytes, aPercent);
    }
    for (const RankedGoldCandidate &aRanked : pTop) {
        const GoldSearchCandidate &aCandidate =
            pCandidates[aRanked.mCandidateIndex];
        Append32(&aBytes, GoldPercentFixed(
            aRanked.mScore /
            static_cast<double>(LoopWeights::WeightTotal())));
        Append32(&aBytes, static_cast<std::uint32_t>(
            aCandidate.mPatternIndex));
        Append32(&aBytes, aCandidate.mHead.mPermutationRank);
        aBytes.insert(aBytes.end(),
                      aCandidate.mHead.mWandererForOrbiter.begin(),
                      aCandidate.mHead.mWandererForOrbiter.end());
        aBytes.insert(aBytes.end(),
                      aCandidate.mTail.mOrbiterAForWanderer.begin(),
                      aCandidate.mTail.mOrbiterAForWanderer.end());
        aBytes.insert(aBytes.end(),
                      aCandidate.mTail.mOrbiterBForWanderer.begin(),
                      aCandidate.mTail.mOrbiterBForWanderer.end());
        AppendMetricValues(&aBytes, aCandidate.mValues);
    }
    if (aBytes.size() != kGoldStatsFileByteCount) {
        SetError(pErrorMessage,
                 "Gold-rate search built an invalid file size");
        return false;
    }
    const std::string aTemporaryPath = pPath + ".tmp";
    if (!FileIO::Save(aTemporaryPath, aBytes)) {
        SetError(pErrorMessage,
                 "Gold-rate search could not save " + aTemporaryPath);
        return false;
    }
    if (std::rename(aTemporaryPath.c_str(), pPath.c_str()) != 0) {
        const std::string aReason = std::strerror(errno);
        std::error_code aCleanupError;
        std::filesystem::remove(aTemporaryPath, aCleanupError);
        SetError(pErrorMessage,
                 "Gold-rate search could not install " + pPath +
                 ": " + aReason);
        return false;
    }
    return true;
}

struct GoldHeartQuality {
    std::size_t mHeartIndex = 0U;
    std::string mHeartName;
    std::array<std::uint32_t, kGoldCandidateCount> mCandidateScores{};
    std::array<std::uint32_t, kScoreFieldCount> mGoldPercents{};
    std::uint32_t mFloorScore = 0U;
    std::uint64_t mScoreSum = 0ULL;
};

std::uint32_t GoldFloorScore(
    const std::array<std::uint32_t, kScoreFieldCount> &pGoldPercents) {
    std::uint64_t aWeightedSum = 0ULL;
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        aWeightedSum +=
            static_cast<std::uint64_t>(LoopWeights::kMetrics[i].mWeight) *
            static_cast<std::uint64_t>(pGoldPercents[i]);
    }
    const std::uint64_t aWeightTotal = LoopWeights::WeightTotal();
    return static_cast<std::uint32_t>(
        (aWeightedSum + (aWeightTotal / 2ULL)) / aWeightTotal);
}

bool SaveGoldHeartQualitySummary(
    const std::string &pOutputFolderPath,
    const LoopCorePatternFile11 &pHeartPatterns,
    const std::vector<std::string> &pHeartNames,
    const std::uint64_t pTrialsPerHeart,
    const std::uint64_t pWeightSignature,
    const char *pNormalizationScope,
    const bool pPrintRanking,
    std::string *pErrorMessage) {
    if (pHeartNames.size() != pHeartPatterns.mPatterns.size()) {
        SetError(pErrorMessage,
                 "Gold-rate heart names did not match the loaded hearts");
        return false;
    }
    std::vector<GoldHeartQuality> aQualities;
    aQualities.reserve(pHeartPatterns.mPatterns.size());
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < pHeartPatterns.mPatterns.size();
         ++aHeartIndex) {
        GoldHeartQuality aQuality;
        aQuality.mHeartIndex = aHeartIndex;
        aQuality.mHeartName = pHeartNames[aHeartIndex];
        if (!GoldStatsFileMatches(
                GoldStatsPath(pOutputFolderPath,
                              aHeartIndex,
                              aQuality.mHeartName),
                aHeartIndex,
                pTrialsPerHeart,
                GoldHeartSignature(
                    pHeartPatterns.mPatterns[aHeartIndex]),
                pWeightSignature,
                &aQuality.mCandidateScores,
                &aQuality.mGoldPercents)) {
            continue;
        }
        aQuality.mFloorScore = GoldFloorScore(aQuality.mGoldPercents);
        aQuality.mScoreSum = std::accumulate(
            aQuality.mCandidateScores.begin(),
            aQuality.mCandidateScores.end(),
            0ULL);
        aQualities.push_back(aQuality);
    }

    std::sort(aQualities.begin(), aQualities.end(),
              [](const GoldHeartQuality &pA,
                 const GoldHeartQuality &pB) {
        if (pA.mFloorScore != pB.mFloorScore) {
            return pA.mFloorScore > pB.mFloorScore;
        }
        if (pA.mScoreSum != pB.mScoreSum) {
            return pA.mScoreSum > pB.mScoreSum;
        }
        return pA.mHeartIndex < pB.mHeartIndex;
    });

    const double aFixedToPercent =
        100.0 / static_cast<double>(kGoldPercentScale);
    std::ostringstream aCsv;
    aCsv << "rank,selected_top_24,heart_index,heart_name,"
            "gold_floor_score_0_to_100,"
            "relative_heart_score_0_to_300,"
            "relative_top_1_0_to_100,relative_top_2_0_to_100,"
            "relative_top_3_0_to_100,normalization_scope\n";
    aCsv << std::fixed << std::setprecision(6);
    for (std::size_t i = 0U; i < aQualities.size(); ++i) {
        const GoldHeartQuality &aQuality = aQualities[i];
        aCsv << (i + 1U) << ","
             << (i < kGoldSelectedHeartCount ? "yes" : "no") << ","
             << aQuality.mHeartIndex << ","
             << aQuality.mHeartName << ","
             << (static_cast<double>(aQuality.mFloorScore) *
                 aFixedToPercent) << ","
             << (static_cast<double>(aQuality.mScoreSum) *
                 aFixedToPercent) << ","
             << (static_cast<double>(aQuality.mCandidateScores[0]) *
                 aFixedToPercent) << ","
             << (static_cast<double>(aQuality.mCandidateScores[1]) *
                 aFixedToPercent) << ","
             << (static_cast<double>(aQuality.mCandidateScores[2]) *
                 aFixedToPercent)
             << "," << pNormalizationScope << "\n";
    }

    const std::string aOutputPath = (
        std::filesystem::path(ResolvedPath(pOutputFolderPath)) /
        "heart_quality.csv").lexically_normal().generic_string();
    const std::string aText = aCsv.str();
    const std::vector<std::uint8_t> aBytes(aText.begin(), aText.end());
    const std::string aTemporaryPath = aOutputPath + ".tmp";
    if (!FileIO::Save(aTemporaryPath, aBytes)) {
        SetError(pErrorMessage,
                 "Gold-rate search could not save " + aTemporaryPath);
        return false;
    }
    if (std::rename(aTemporaryPath.c_str(), aOutputPath.c_str()) != 0) {
        const std::string aReason = std::strerror(errno);
        std::error_code aCleanupError;
        std::filesystem::remove(aTemporaryPath, aCleanupError);
        SetError(pErrorMessage,
                 "Gold-rate search could not install " + aOutputPath +
                 ": " + aReason);
        return false;
    }

    std::ostringstream aRanking;
    aRanking << "GOLD HEART FLOOR RANKING\n"
             << "rank | heart | name            | floor score | top 24\n"
             << "-----+-------+-----------------+-------------+-------\n";
    aRanking << std::fixed << std::setprecision(6);
    for (std::size_t i = 0U; i < aQualities.size(); ++i) {
        aRanking << std::setw(4) << (i + 1U) << " | "
                 << std::setfill('0') << std::setw(3)
                 << aQualities[i].mHeartIndex << std::setfill(' ')
                 << "   | " << std::left << std::setw(15)
                 << aQualities[i].mHeartName << std::right
                 << " | " << std::setw(11)
                 << (static_cast<double>(aQualities[i].mFloorScore) *
                     aFixedToPercent)
                 << " | "
                 << (i < kGoldSelectedHeartCount ? "yes" : "")
                 << "\n";
    }
    const std::string aRankingPath = (
        std::filesystem::path(ResolvedPath(pOutputFolderPath)) /
        "heart_quality_sorted.txt").lexically_normal().generic_string();
    const std::string aRankingText = aRanking.str();
    const std::vector<std::uint8_t> aRankingBytes(
        aRankingText.begin(), aRankingText.end());
    if (!FileIO::Save(aRankingPath, aRankingBytes)) {
        SetError(pErrorMessage,
                 "Gold-rate search could not save " + aRankingPath);
        return false;
    }

    if (pPrintRanking) {
        std::printf("\n%s", aRankingText.c_str());
    }

    if (aQualities.empty()) {
        std::printf("gold global heart-quality summary: completed=0/%zu\n",
                    pHeartPatterns.mPatterns.size());
    } else {
        const GoldHeartQuality &aBest = aQualities.front();
        const GoldHeartQuality &aWorst = aQualities.back();
        std::printf(
            "gold global heart-quality summary: completed=%zu/%zu "
            "global_best=%03zu(%.6f) global_worst=%03zu(%.6f) "
            "saved=%s ranking=%s\n",
            aQualities.size(),
            pHeartPatterns.mPatterns.size(),
            aBest.mHeartIndex,
            static_cast<double>(aBest.mFloorScore) * aFixedToPercent,
            aWorst.mHeartIndex,
            static_cast<double>(aWorst.mFloorScore) * aFixedToPercent,
            aOutputPath.c_str(),
            aRankingPath.c_str());
    }
    return true;
}

//
// Final alien-loop farm
//

constexpr std::size_t kAlienHeartCount = 4U;
constexpr std::array<std::uint8_t, 8U> kAlienLoopMagic = {
    'M', 'M', 'A', 'L', 'I', 'E', 'N', '1',
};
constexpr std::array<std::uint8_t, 8U> kAlienStateMagic = {
    'M', 'M', 'A', 'L', 'S', 'T', 'A', '1',
};
constexpr std::uint32_t kAlienLoopVersion = 1U;
constexpr std::uint32_t kAlienStateVersion = 1U;
constexpr std::size_t kAlienCoreScoreCount = 12U;
constexpr std::size_t kAlienLoopHeaderByteCount = 92U;
constexpr std::size_t kAlienLoopByteCount =
    kAlienLoopHeaderByteCount +
    (4U * kRoleCount) +
    (2U * kRoleCount) +
    (kAlienCoreScoreCount * sizeof(std::uint32_t)) +
    (3U * kScoreFieldCount * sizeof(std::uint32_t));
constexpr std::size_t kAlienStateByteCount = 48U;

struct AlienNormalization {
    MetricValues mMinimums{};
    MetricValues mMaximums{};
};

struct AlienLoopRecord {
    std::size_t mHeartIndex = 0U;
    std::uint64_t mLocalIndex = 0ULL;
    std::size_t mPatternIndex = 0U;
    LoopHeadPattern11 mHead;
    LoopCorePattern11 mHeart;
    LoopTailPattern11 mTail;
    MetricValues mValues{};
    AlienNormalization mNormalization;
    std::uint32_t mScoreFixed = 0U;
    std::uint64_t mRawAttempt = 0ULL;
    std::uint64_t mAcceptedOrdinal = 0ULL;
};

std::array<std::uint32_t, kAlienCoreScoreCount>
AlienCoreScoreValues(const LoopCorePatternScore11 &pScore) {
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

std::string AlienHeartPath(const std::string &pFolderPath,
                           const std::size_t pHeartIndex) {
    char aName[64];
    std::snprintf(aName, sizeof(aName),
                  "alien_heart_%02zu.bin", pHeartIndex + 1U);
    return (std::filesystem::path(ResolvedPath(pFolderPath)) / aName)
        .lexically_normal().generic_string();
}

std::string AlienNormalizationPath(const std::string &pFolderPath,
                                   const std::size_t pHeartIndex) {
    char aName[80];
    std::snprintf(aName, sizeof(aName),
                  "alien_heart_%02zu_gold_stats.bin",
                  pHeartIndex + 1U);
    return (std::filesystem::path(ResolvedPath(pFolderPath)) / aName)
        .lexically_normal().generic_string();
}

std::string AlienLoopFolderPath(const std::string &pFolderPath,
                                const std::size_t pHeartIndex) {
    char aName[64];
    std::snprintf(aName, sizeof(aName),
                  "alien_loop_%02zu", pHeartIndex);
    return (std::filesystem::path(ResolvedPath(pFolderPath)) / aName)
        .lexically_normal().generic_string();
}

std::string AlienLoopPath(const std::string &pFolderPath,
                          const std::size_t pHeartIndex,
                          const std::uint64_t pLocalIndex) {
    char aName[64];
    std::snprintf(aName, sizeof(aName),
                  "loop_%04llu.bin",
                  static_cast<unsigned long long>(pLocalIndex));
    return (std::filesystem::path(
                AlienLoopFolderPath(pFolderPath, pHeartIndex)) / aName)
        .lexically_normal().generic_string();
}

std::string AlienStatePath(const std::string &pFolderPath) {
    return (std::filesystem::path(ResolvedPath(pFolderPath)) /
            "alien_farm_state.bin")
        .lexically_normal().generic_string();
}

bool SaveAlienBytesAtomically(const std::string &pPath,
                              const std::vector<std::uint8_t> &pBytes,
                              std::string *pErrorMessage) {
    const std::string aTemporaryPath = pPath + ".tmp";
    if (!FileIO::Save(aTemporaryPath, pBytes)) {
        SetError(pErrorMessage,
                 "Alien loop farm could not save " + aTemporaryPath);
        return false;
    }
    if (std::rename(aTemporaryPath.c_str(), pPath.c_str()) != 0) {
        const std::string aReason = std::strerror(errno);
        std::error_code aCleanupError;
        std::filesystem::remove(aTemporaryPath, aCleanupError);
        SetError(pErrorMessage,
                 "Alien loop farm could not install " + pPath +
                 ": " + aReason);
        return false;
    }
    return true;
}

bool LoadAlienNormalization(
    const std::string &pPath,
    const LoopCorePattern11 &pHeart,
    AlienNormalization *pNormalization,
    std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes) ||
        (aBytes.size() != kGoldStatsFileByteCount) ||
        !std::equal(kGoldStatsFileMagic.begin(),
                    kGoldStatsFileMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Alien loop farm could not load gold-stat ranges from " +
                 pPath);
        return false;
    }

    std::size_t aOffset = kGoldStatsFileMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    (void)Read32(aBytes, &aOffset); // Original source-heart index.
    const std::uint32_t aRoleCount = Read32(aBytes, &aOffset);
    const std::uint32_t aMetricCount = Read32(aBytes, &aOffset);
    const std::uint32_t aCandidateCount = Read32(aBytes, &aOffset);
    const std::uint32_t aPercentScale = Read32(aBytes, &aOffset);
    (void)Read64(aBytes, &aOffset); // Reference trial count.
    (void)Read64(aBytes, &aOffset); // Reference raw-attempt count.
    const std::uint64_t aHeartSignature = Read64(aBytes, &aOffset);
    const std::uint64_t aWeightSignature = Read64(aBytes, &aOffset);
    if ((aVersion != kGoldStatsFileVersion) ||
        (aRoleCount != kRoleCount) ||
        (aMetricCount != kScoreFieldCount) ||
        (aCandidateCount != kGoldCandidateCount) ||
        (aPercentScale != kGoldPercentScale) ||
        (aHeartSignature != GoldHeartSignature(pHeart)) ||
        (aWeightSignature != GoldWeightSignature())) {
        SetError(pErrorMessage,
                 "Alien loop farm gold-stat metadata did not match " +
                 pPath);
        return false;
    }

    pNormalization->mMinimums = ReadMetricValues(aBytes, &aOffset);
    pNormalization->mMaximums = ReadMetricValues(aBytes, &aOffset);
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        if (pNormalization->mMinimums[i] >
            pNormalization->mMaximums[i]) {
            SetError(pErrorMessage,
                     "Alien loop farm found an inverted gold-stat range in " +
                     pPath);
            return false;
        }
    }
    return true;
}

std::uint32_t AlienScoreFixed(
    const MetricValues &pValues,
    const AlienNormalization &pNormalization) {
    const double aWeightedScore = LoopWeights::Score(
        pValues,
        pNormalization.mMinimums,
        pNormalization.mMaximums);
    return GoldPercentFixed(
        aWeightedScore /
        static_cast<double>(LoopWeights::WeightTotal()));
}

std::size_t AlienHeadExactMatches(const LoopHeadPattern11 &pA,
                                  const LoopHeadPattern11 &pB) {
    std::size_t aMatches = 0U;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aMatches += pA.mWandererForOrbiter[i] ==
            pB.mWandererForOrbiter[i];
    }
    return aMatches;
}

bool AlienTailPairIsExact(const LoopTailPattern11 &pA,
                          const LoopTailPattern11 &pB,
                          const std::size_t pDestination) {
    const std::uint8_t aA =
        pA.mOrbiterAForWanderer[pDestination];
    const std::uint8_t aB =
        pA.mOrbiterBForWanderer[pDestination];
    const std::uint8_t bA =
        pB.mOrbiterAForWanderer[pDestination];
    const std::uint8_t bB =
        pB.mOrbiterBForWanderer[pDestination];
    return ((aA == bA) && (aB == bB)) ||
           ((aA == bB) && (aB == bA));
}

std::size_t AlienTailExactMatches(const LoopTailPattern11 &pA,
                                  const LoopTailPattern11 &pB) {
    std::size_t aMatches = 0U;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aMatches += AlienTailPairIsExact(pA, pB, i);
    }
    return aMatches;
}

std::size_t AlienTailPartialMatches(const LoopTailPattern11 &pA,
                                    const LoopTailPattern11 &pB) {
    std::size_t aMatches = 0U;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::uint8_t aA =
            pA.mOrbiterAForWanderer[i];
        const std::uint8_t aB =
            pA.mOrbiterBForWanderer[i];
        const std::uint8_t bA =
            pB.mOrbiterAForWanderer[i];
        const std::uint8_t bB =
            pB.mOrbiterBForWanderer[i];
        aMatches += (aA == bA) || (aA == bB);
        aMatches += (aB == bA) || (aB == bB);
    }
    return aMatches;
}

bool AlienIsDifferentFromPool(
    const LoopHeadPattern11 &pHead,
    const LoopTailPattern11 &pTail,
    const std::vector<AlienLoopRecord> &pSaved,
    const std::size_t pMaximumHeadExactMatches,
    const std::size_t pMaximumTailExactMatches,
    const std::size_t pMaximumTailPartialMatches,
    std::size_t *pWorstHeadExactMatches = nullptr,
    std::size_t *pWorstTailExactMatches = nullptr,
    std::size_t *pWorstTailPartialMatches = nullptr) {
    std::size_t aWorstHead = 0U;
    std::size_t aWorstTailExact = 0U;
    std::size_t aWorstTailPartial = 0U;
    for (const AlienLoopRecord &aSaved : pSaved) {
        const std::size_t aHead = AlienHeadExactMatches(
            pHead, aSaved.mHead);
        const std::size_t aTailExact = AlienTailExactMatches(
            pTail, aSaved.mTail);
        const std::size_t aTailPartial = AlienTailPartialMatches(
            pTail, aSaved.mTail);
        aWorstHead = std::max(aWorstHead, aHead);
        aWorstTailExact = std::max(aWorstTailExact, aTailExact);
        aWorstTailPartial = std::max(aWorstTailPartial, aTailPartial);
        if ((aHead > pMaximumHeadExactMatches) ||
            (aTailExact > pMaximumTailExactMatches) ||
            (aTailPartial > pMaximumTailPartialMatches)) {
            return false;
        }
    }
    if (pWorstHeadExactMatches != nullptr) {
        *pWorstHeadExactMatches = aWorstHead;
    }
    if (pWorstTailExactMatches != nullptr) {
        *pWorstTailExactMatches = aWorstTailExact;
    }
    if (pWorstTailPartialMatches != nullptr) {
        *pWorstTailPartialMatches = aWorstTailPartial;
    }
    return true;
}

bool SaveAlienLoopRecord(
    const std::string &pPath,
    const AlienLoopRecord &pRecord,
    const std::uint32_t pMinimumScoreFixed,
    const std::size_t pMaximumHeadExactMatches,
    const std::size_t pMaximumTailExactMatches,
    const std::size_t pMaximumTailPartialMatches,
    std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kAlienLoopByteCount);
    aBytes.insert(aBytes.end(),
                  kAlienLoopMagic.begin(), kAlienLoopMagic.end());
    Append32(&aBytes, kAlienLoopVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(kRoleCount));
    Append32(&aBytes, static_cast<std::uint32_t>(kScoreFieldCount));
    Append32(&aBytes, static_cast<std::uint32_t>(kAlienLoopByteCount));
    Append32(&aBytes, static_cast<std::uint32_t>(pRecord.mHeartIndex));
    Append32(&aBytes, static_cast<std::uint32_t>(pRecord.mLocalIndex));
    Append32(&aBytes, static_cast<std::uint32_t>(pRecord.mPatternIndex));
    Append32(&aBytes, pRecord.mHead.mPermutationRank);
    Append32(&aBytes, pRecord.mScoreFixed);
    Append32(&aBytes, pMinimumScoreFixed);
    Append32(&aBytes, static_cast<std::uint32_t>(
        pMaximumHeadExactMatches));
    Append32(&aBytes, static_cast<std::uint32_t>(
        pMaximumTailExactMatches));
    Append32(&aBytes, static_cast<std::uint32_t>(
        pMaximumTailPartialMatches));
    Append64(&aBytes, pRecord.mRawAttempt);
    Append64(&aBytes, pRecord.mAcceptedOrdinal);
    Append64(&aBytes, GoldHeartSignature(pRecord.mHeart));
    Append64(&aBytes, GoldWeightSignature());

    aBytes.insert(aBytes.end(),
                  pRecord.mHead.mWandererForOrbiter.begin(),
                  pRecord.mHead.mWandererForOrbiter.end());
    for (const auto &aRound : pRecord.mHeart.mRounds) {
        aBytes.insert(aBytes.end(), aRound.begin(), aRound.end());
    }
    aBytes.insert(aBytes.end(),
                  pRecord.mTail.mOrbiterAForWanderer.begin(),
                  pRecord.mTail.mOrbiterAForWanderer.end());
    aBytes.insert(aBytes.end(),
                  pRecord.mTail.mOrbiterBForWanderer.begin(),
                  pRecord.mTail.mOrbiterBForWanderer.end());
    for (const std::uint32_t aValue :
         AlienCoreScoreValues(pRecord.mHeart.mScore)) {
        Append32(&aBytes, aValue);
    }
    AppendMetricValues(&aBytes, pRecord.mValues);
    AppendMetricValues(&aBytes, pRecord.mNormalization.mMinimums);
    AppendMetricValues(&aBytes, pRecord.mNormalization.mMaximums);
    if (aBytes.size() != kAlienLoopByteCount) {
        SetError(pErrorMessage,
                 "Alien loop farm built an invalid record size");
        return false;
    }
    return SaveAlienBytesAtomically(pPath, aBytes, pErrorMessage);
}

bool LoadAlienLoopRecord(
    const std::string &pPath,
    const std::size_t pExpectedHeartIndex,
    const std::uint64_t pExpectedLocalIndex,
    const LoopCorePattern11 &pExpectedHeart,
    const AlienNormalization &pExpectedNormalization,
    const std::uint32_t pExpectedMinimumScoreFixed,
    const std::size_t pMaximumHeadExactMatches,
    const std::size_t pMaximumTailExactMatches,
    const std::size_t pMaximumTailPartialMatches,
    AlienLoopRecord *pRecord,
    std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes) ||
        (aBytes.size() != kAlienLoopByteCount) ||
        !std::equal(kAlienLoopMagic.begin(), kAlienLoopMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Alien loop farm could not read " + pPath);
        return false;
    }
    std::size_t aOffset = kAlienLoopMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    const std::uint32_t aRoleCount = Read32(aBytes, &aOffset);
    const std::uint32_t aMetricCount = Read32(aBytes, &aOffset);
    const std::uint32_t aByteCount = Read32(aBytes, &aOffset);
    const std::uint32_t aHeartIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aLocalIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aPatternIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aHeadRank = Read32(aBytes, &aOffset);
    const std::uint32_t aScoreFixed = Read32(aBytes, &aOffset);
    const std::uint32_t aMinimumScoreFixed = Read32(aBytes, &aOffset);
    const std::uint32_t aHeadLimit = Read32(aBytes, &aOffset);
    const std::uint32_t aTailExactLimit = Read32(aBytes, &aOffset);
    const std::uint32_t aTailPartialLimit = Read32(aBytes, &aOffset);
    const std::uint64_t aRawAttempt = Read64(aBytes, &aOffset);
    const std::uint64_t aAcceptedOrdinal = Read64(aBytes, &aOffset);
    const std::uint64_t aHeartSignature = Read64(aBytes, &aOffset);
    const std::uint64_t aWeightSignature = Read64(aBytes, &aOffset);
    if ((aVersion != kAlienLoopVersion) ||
        (aRoleCount != kRoleCount) ||
        (aMetricCount != kScoreFieldCount) ||
        (aByteCount != kAlienLoopByteCount) ||
        (aHeartIndex != pExpectedHeartIndex) ||
        (aLocalIndex != pExpectedLocalIndex) ||
        (aPatternIndex >= LoopHeadFarmer::kRetainedPatternCount) ||
        (aMinimumScoreFixed > kGoldPercentScale) ||
        (aHeadLimit != pMaximumHeadExactMatches) ||
        (aTailExactLimit != pMaximumTailExactMatches) ||
        (aTailPartialLimit != pMaximumTailPartialMatches) ||
        (aHeartSignature != GoldHeartSignature(pExpectedHeart)) ||
        (aWeightSignature != GoldWeightSignature()) ||
        (aScoreFixed <= pExpectedMinimumScoreFixed)) {
        SetError(pErrorMessage,
                 "Alien loop farm record metadata did not match " + pPath);
        return false;
    }

    AlienLoopRecord aRecord;
    aRecord.mHeartIndex = aHeartIndex;
    aRecord.mLocalIndex = aLocalIndex;
    aRecord.mPatternIndex = aPatternIndex;
    aRecord.mHead.mPermutationRank = aHeadRank;
    aRecord.mScoreFixed = aScoreFixed;
    aRecord.mRawAttempt = aRawAttempt;
    aRecord.mAcceptedOrdinal = aAcceptedOrdinal;
    for (std::uint8_t &aValue :
         aRecord.mHead.mWandererForOrbiter) {
        aValue = aBytes[aOffset++];
    }
    for (auto &aRound : aRecord.mHeart.mRounds) {
        for (std::uint8_t &aValue : aRound) {
            aValue = aBytes[aOffset++];
        }
    }
    for (std::uint8_t &aValue :
         aRecord.mTail.mOrbiterAForWanderer) {
        aValue = aBytes[aOffset++];
    }
    for (std::uint8_t &aValue :
         aRecord.mTail.mOrbiterBForWanderer) {
        aValue = aBytes[aOffset++];
    }
    const auto aExpectedCoreScore =
        AlienCoreScoreValues(pExpectedHeart.mScore);
    for (std::size_t i = 0U; i < kAlienCoreScoreCount; ++i) {
        if (Read32(aBytes, &aOffset) != aExpectedCoreScore[i]) {
            SetError(pErrorMessage,
                     "Alien loop farm core score did not match " + pPath);
            return false;
        }
    }
    aRecord.mValues = ReadMetricValues(aBytes, &aOffset);
    aRecord.mNormalization.mMinimums =
        ReadMetricValues(aBytes, &aOffset);
    aRecord.mNormalization.mMaximums =
        ReadMetricValues(aBytes, &aOffset);
    if ((aOffset != aBytes.size()) ||
        (aRecord.mHeart.mRounds != pExpectedHeart.mRounds) ||
        (aRecord.mNormalization.mMinimums !=
         pExpectedNormalization.mMinimums) ||
        (aRecord.mNormalization.mMaximums !=
         pExpectedNormalization.mMaximums) ||
        !LoopHeadFarmer::IsValid(aRecord.mHead) ||
        (LoopHeadFarmer::Rank(aRecord.mHead) != aHeadRank)) {
        SetError(pErrorMessage,
                 "Alien loop farm record body did not validate " + pPath);
        return false;
    }
    aRecord.mHeart.mScore = pExpectedHeart.mScore;

    LoopNewHeart11 aHeart;
    aHeart.mHeart = pExpectedHeart;
    const DistanceMatrix aDistances =
        HeartTemporalDistances(pExpectedHeart);
    const PairInfoMatrix aPairs = MakePairInfo(
        pExpectedHeart,
        aRecord.mHead,
        aRecord.mPatternIndex,
        aDistances);
    Candidate aEvaluated;
    if (!EvaluateAscendencyCandidate(
            aHeart,
            aRecord.mHead,
            aRecord.mPatternIndex,
            aPairs,
            aRecord.mTail,
            &aEvaluated) ||
        (RankingDisplayValues(aEvaluated.mScore) != aRecord.mValues) ||
        (AlienScoreFixed(aRecord.mValues,
                         aRecord.mNormalization) != aScoreFixed)) {
        SetError(pErrorMessage,
                 "Alien loop farm could not reproduce " + pPath);
        return false;
    }
    *pRecord = std::move(aRecord);
    return true;
}

bool ParseAlienLoopLocalIndex(const std::filesystem::path &pPath,
                              std::uint64_t *pIndex) {
    const std::string aName = pPath.stem().generic_string();
    constexpr const char *kPrefix = "loop_";
    if (aName.rfind(kPrefix, 0U) != 0U ||
        (aName.size() == std::strlen(kPrefix))) {
        return false;
    }
    std::uint64_t aValue = 0ULL;
    for (std::size_t i = std::strlen(kPrefix); i < aName.size(); ++i) {
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
    *pIndex = aValue;
    return true;
}

bool SaveAlienFarmState(
    const std::string &pPath,
    const std::uint32_t pMinimumScoreFixed,
    const std::size_t pMaximumHeadExactMatches,
    const std::size_t pMaximumTailExactMatches,
    const std::size_t pMaximumTailPartialMatches,
    const std::uint64_t pRawAttempts,
    const std::uint64_t pAcceptedCount,
    std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kAlienStateByteCount);
    aBytes.insert(aBytes.end(),
                  kAlienStateMagic.begin(), kAlienStateMagic.end());
    Append32(&aBytes, kAlienStateVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(kAlienHeartCount));
    Append32(&aBytes, pMinimumScoreFixed);
    Append32(&aBytes, static_cast<std::uint32_t>(
        pMaximumHeadExactMatches));
    Append32(&aBytes, static_cast<std::uint32_t>(
        pMaximumTailExactMatches));
    Append32(&aBytes, static_cast<std::uint32_t>(
        pMaximumTailPartialMatches));
    Append64(&aBytes, pRawAttempts);
    Append64(&aBytes, pAcceptedCount);
    if (aBytes.size() != kAlienStateByteCount) {
        SetError(pErrorMessage,
                 "Alien loop farm built an invalid state size");
        return false;
    }
    return SaveAlienBytesAtomically(pPath, aBytes, pErrorMessage);
}

bool LoadAlienFarmState(
    const std::string &pPath,
    const std::uint32_t pMinimumScoreFixed,
    const std::size_t pMaximumHeadExactMatches,
    const std::size_t pMaximumTailExactMatches,
    const std::size_t pMaximumTailPartialMatches,
    bool *pFound,
    std::uint64_t *pRawAttempts,
    std::uint64_t *pAcceptedCount,
    std::string *pErrorMessage) {
    *pFound = false;
    std::error_code aExistsError;
    if (!std::filesystem::exists(pPath, aExistsError)) {
        return !aExistsError;
    }
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes) ||
        (aBytes.size() != kAlienStateByteCount) ||
        !std::equal(kAlienStateMagic.begin(), kAlienStateMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Alien loop farm could not read its state file");
        return false;
    }
    std::size_t aOffset = kAlienStateMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    const std::uint32_t aHeartCount = Read32(aBytes, &aOffset);
    const std::uint32_t aMinimumScoreFixed = Read32(aBytes, &aOffset);
    const std::uint32_t aHeadLimit = Read32(aBytes, &aOffset);
    const std::uint32_t aTailExactLimit = Read32(aBytes, &aOffset);
    const std::uint32_t aTailPartialLimit = Read32(aBytes, &aOffset);
    const std::uint64_t aRawAttempts = Read64(aBytes, &aOffset);
    const std::uint64_t aAcceptedCount = Read64(aBytes, &aOffset);
    if ((aVersion != kAlienStateVersion) ||
        ((aHeartCount != kAlienHeartCount) && (aHeartCount != 12U)) ||
        (aMinimumScoreFixed > kGoldPercentScale) ||
        (aHeadLimit != pMaximumHeadExactMatches) ||
        (aTailExactLimit != pMaximumTailExactMatches) ||
        (aTailPartialLimit != pMaximumTailPartialMatches)) {
        SetError(pErrorMessage,
                 "Alien loop farm state used different scoring or "
                 "difference settings");
        return false;
    }
    *pFound = true;
    *pRawAttempts = aRawAttempts;
    *pAcceptedCount = aAcceptedCount;
    return true;
}

bool PrintAscendencyInventoryForHearts(
    const std::string &pFarmFolderPath,
    const std::vector<std::size_t> &pHeartIndices,
    std::string *pErrorMessage) {
    std::array<std::size_t, 4U> aGrandCounts{};
    std::size_t aGrandMissing = 0U;
    std::uint64_t aGrandAttempts = 0ULL;
    std::printf("\nASCENDENCY LOOP FARM INVENTORY\n");
    std::printf("heart | tier_0 tier_1 tier_2 working missing | attempts\n");
    std::printf("------+----------------------------------------+----------------\n");
    for (const std::size_t aHeartIndex : pHeartIndices) {
        std::array<std::size_t, 4U> aCounts{};
        std::size_t aMissing = 0U;
        std::uint64_t aAttempts = 0ULL;
        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            bool aFound = false;
            AscendencyRecord aRecord;
            if (!LoadAscendencyRecord(pFarmFolderPath,
                                      aHeartIndex,
                                      aHeadIndex,
                                      &aFound,
                                      &aRecord,
                                      pErrorMessage)) {
                return false;
            }
            if (!aFound) {
                ++aMissing;
                continue;
            }
            ++aCounts[static_cast<std::size_t>(aRecord.mTier)];
            aAttempts += aRecord.mAttempts;
        }
        for (std::size_t i = 0U; i < aCounts.size(); ++i) {
            aGrandCounts[i] += aCounts[i];
        }
        aGrandMissing += aMissing;
        aGrandAttempts += aAttempts;
        std::printf("%5zu | %6zu %6zu %6zu %7zu %7zu | %llu\n",
                    aHeartIndex,
                    aCounts[0], aCounts[1], aCounts[2], aCounts[3],
                    aMissing,
                    static_cast<unsigned long long>(aAttempts));
    }
    std::printf("------+----------------------------------------+----------------\n");
    std::printf("total | %6zu %6zu %6zu %7zu %7zu | %llu\n\n",
                aGrandCounts[0], aGrandCounts[1],
                aGrandCounts[2], aGrandCounts[3],
                aGrandMissing,
                static_cast<unsigned long long>(aGrandAttempts));
    return true;
}

} // namespace

bool LoopTailFarmer::FarmAlienLoops(
    const std::string &pHeartPatternFolderPath,
    const std::string &pNormalizationFolderPath,
    const std::string &pOutputFolderPath,
    const std::uint64_t pNewLoopTarget,
    const std::uint64_t pMaximumAttempts,
    const std::uint64_t pProgressInterval,
    const double pMinimumScore,
    const std::size_t pMaximumHeadExactMatches,
    const std::size_t pMaximumTailExactMatches,
    const std::size_t pMaximumTailPartialMatches,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pNewLoopTarget == 0ULL) ||
        (pMaximumAttempts == 0ULL) ||
        (pProgressInterval == 0ULL) ||
        !std::isfinite(pMinimumScore) ||
        (pMinimumScore < 0.0) ||
        (pMinimumScore > 100.0) ||
        (pMaximumHeadExactMatches > kRoleCount) ||
        (pMaximumTailExactMatches > kRoleCount) ||
        (pMaximumTailPartialMatches > (2U * kRoleCount))) {
        SetError(pErrorMessage,
                 "Alien loop farm settings were invalid");
        return false;
    }
    const std::uint32_t aMinimumScoreFixed = GoldPercentFixed(
        pMinimumScore / 100.0);

    std::array<LoopCorePattern11, kAlienHeartCount> aHearts;
    std::array<AlienNormalization, kAlienHeartCount> aNormalizations;
    for (std::size_t i = 0U; i < kAlienHeartCount; ++i) {
        LoopCorePatternFile11 aLoaded;
        const std::string aHeartPath = AlienHeartPath(
            pHeartPatternFolderPath, i);
        if (!LoopCorePatternFarmer::Load(
                aHeartPath, &aLoaded, pErrorMessage)) {
            return false;
        }
        if (aLoaded.mPatterns.size() != 1U) {
            SetError(pErrorMessage,
                     "Alien heart file did not contain exactly one heart: " +
                     aHeartPath);
            return false;
        }
        aHearts[i] = aLoaded.mPatterns.front();
        if (!LoadAlienNormalization(
                AlienNormalizationPath(pNormalizationFolderPath, i),
                aHearts[i],
                &aNormalizations[i],
                pErrorMessage)) {
            return false;
        }
    }

    const std::string aOutputRoot = ResolvedPath(pOutputFolderPath);
    std::error_code aDirectoryError;
    std::filesystem::create_directories(aOutputRoot, aDirectoryError);
    if (aDirectoryError) {
        SetError(pErrorMessage,
                 "Alien loop farm could not create its output folder: " +
                 aDirectoryError.message());
        return false;
    }
    for (std::size_t i = 0U; i < kAlienHeartCount; ++i) {
        std::filesystem::create_directories(
            AlienLoopFolderPath(pOutputFolderPath, i),
            aDirectoryError);
        if (aDirectoryError) {
            SetError(pErrorMessage,
                     "Alien loop farm could not create heart folder " +
                     std::to_string(i) + ": " +
                     aDirectoryError.message());
            return false;
        }
    }

    std::vector<AlienLoopRecord> aSaved;
    std::array<std::uint64_t, kAlienHeartCount> aHeartCounts{};
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < kAlienHeartCount;
         ++aHeartIndex) {
        const std::filesystem::path aFolder(
            AlienLoopFolderPath(pOutputFolderPath, aHeartIndex));
        std::vector<std::pair<std::uint64_t, std::filesystem::path>>
            aPaths;
        std::error_code aEnumerateError;
        std::filesystem::directory_iterator aIterator(
            aFolder,
            std::filesystem::directory_options::skip_permission_denied,
            aEnumerateError);
        const std::filesystem::directory_iterator aEnd;
        while (!aEnumerateError && (aIterator != aEnd)) {
            const std::filesystem::directory_entry aEntry = *aIterator;
            std::error_code aEntryError;
            if (aEntry.is_regular_file(aEntryError) && !aEntryError &&
                (aEntry.path().extension() == ".bin")) {
                std::uint64_t aLocalIndex = 0ULL;
                if (!ParseAlienLoopLocalIndex(
                        aEntry.path(), &aLocalIndex)) {
                    SetError(pErrorMessage,
                             "Alien loop farm found an unexpected .bin "
                             "file: " + aEntry.path().generic_string());
                    return false;
                }
                aPaths.push_back({aLocalIndex, aEntry.path()});
            }
            aIterator.increment(aEnumerateError);
        }
        if (aEnumerateError) {
            SetError(pErrorMessage,
                     "Alien loop farm could not enumerate " +
                     aFolder.generic_string() + ": " +
                     aEnumerateError.message());
            return false;
        }
        std::sort(aPaths.begin(), aPaths.end(),
                  [](const auto &pA, const auto &pB) {
            return pA.first < pB.first;
        });
        for (std::size_t i = 0U; i < aPaths.size(); ++i) {
            const std::uint64_t aExpectedLocalIndex = i + 1ULL;
            if (aPaths[i].first != aExpectedLocalIndex) {
                SetError(pErrorMessage,
                         "Alien loop farm found a duplicate or gap in " +
                         aFolder.generic_string());
                return false;
            }
            AlienLoopRecord aRecord;
            if (!LoadAlienLoopRecord(
                    aPaths[i].second.generic_string(),
                    aHeartIndex,
                    aExpectedLocalIndex,
                    aHearts[aHeartIndex],
                    aNormalizations[aHeartIndex],
                    aMinimumScoreFixed,
                    pMaximumHeadExactMatches,
                    pMaximumTailExactMatches,
                    pMaximumTailPartialMatches,
                    &aRecord,
                    pErrorMessage)) {
                return false;
            }
            aSaved.push_back(std::move(aRecord));
        }
        aHeartCounts[aHeartIndex] = aPaths.size();
    }

    std::sort(aSaved.begin(), aSaved.end(),
              [](const AlienLoopRecord &pA,
                 const AlienLoopRecord &pB) {
        return pA.mAcceptedOrdinal < pB.mAcceptedOrdinal;
    });
    std::uint64_t aMaximumRecordAttempt = 0ULL;
    for (std::size_t i = 0U; i < aSaved.size(); ++i) {
        const std::uint64_t aExpectedOrdinal = i + 1ULL;
        const std::size_t aExpectedHeart = i % kAlienHeartCount;
        const std::uint64_t aExpectedLocal =
            (i / kAlienHeartCount) + 1ULL;
        if ((aSaved[i].mAcceptedOrdinal != aExpectedOrdinal) ||
            (aSaved[i].mHeartIndex != aExpectedHeart) ||
            (aSaved[i].mLocalIndex != aExpectedLocal)) {
            SetError(pErrorMessage,
                     "Alien loop farm records did not form one complete "
                     "round-robin sequence");
            return false;
        }
        aMaximumRecordAttempt = std::max(
            aMaximumRecordAttempt, aSaved[i].mRawAttempt);
    }
    for (std::size_t i = 0U; i < aSaved.size(); ++i) {
        for (std::size_t j = 0U; j < i; ++j) {
            if ((AlienHeadExactMatches(
                     aSaved[i].mHead,
                     aSaved[j].mHead) >
                 pMaximumHeadExactMatches) ||
                (AlienTailExactMatches(
                     aSaved[i].mTail,
                     aSaved[j].mTail) >
                 pMaximumTailExactMatches) ||
                (AlienTailPartialMatches(
                     aSaved[i].mTail,
                     aSaved[j].mTail) >
                 pMaximumTailPartialMatches)) {
                SetError(pErrorMessage,
                         "Alien loop farm loaded two recipes that violate "
                         "the universal difference limits");
                return false;
            }
        }
    }

    const std::string aStatePath = AlienStatePath(pOutputFolderPath);
    bool aFoundState = false;
    std::uint64_t aTotalRawAttempts = 0ULL;
    std::uint64_t aStateAcceptedCount = 0ULL;
    if (!LoadAlienFarmState(
            aStatePath,
            aMinimumScoreFixed,
            pMaximumHeadExactMatches,
            pMaximumTailExactMatches,
            pMaximumTailPartialMatches,
            &aFoundState,
            &aTotalRawAttempts,
            &aStateAcceptedCount,
            pErrorMessage)) {
        return false;
    }
    if (aFoundState && (aStateAcceptedCount > aSaved.size())) {
        SetError(pErrorMessage,
                 "Alien loop farm state refers to missing loop files");
        return false;
    }
    aTotalRawAttempts = std::max(
        aTotalRawAttempts, aMaximumRecordAttempt);
    if (!SaveAlienFarmState(
            aStatePath,
            aMinimumScoreFixed,
            pMaximumHeadExactMatches,
            pMaximumTailExactMatches,
            pMaximumTailPartialMatches,
            aTotalRawAttempts,
            aSaved.size(),
            pErrorMessage)) {
        return false;
    }

    std::printf("\nALIEN LOOP FARM\n");
    std::printf("loaded=%zu attempts=%llu next-heart=%02zu "
                "score>%.4f head<=%zu tail-exact<=%zu "
                "tail-partial<=%zu\n",
                aSaved.size(),
                static_cast<unsigned long long>(aTotalRawAttempts),
                aSaved.size() % kAlienHeartCount,
                pMinimumScore,
                pMaximumHeadExactMatches,
                pMaximumTailExactMatches,
                pMaximumTailPartialMatches);
    std::printf("heart | saved\n------+-------\n");
    for (std::size_t i = 0U; i < kAlienHeartCount; ++i) {
        std::printf("%5zu | %llu\n", i,
                    static_cast<unsigned long long>(aHeartCounts[i]));
    }
    std::printf("\n");

    std::uint64_t aRunAttempts = 0ULL;
    std::uint64_t aRunValid = 0ULL;
    std::uint64_t aRunScorePassed = 0ULL;
    std::uint64_t aRunDifferenceRejected = 0ULL;
    std::uint64_t aRunAccepted = 0ULL;
    while ((aRunAccepted < pNewLoopTarget) &&
           (aRunAttempts < pMaximumAttempts)) {
        ++aRunAttempts;
        ++aTotalRawAttempts;
        if ((aRunAttempts % pProgressInterval) == 0ULL) {
            // This checkpoint is written before the current candidate is
            // evaluated. Persist the preceding attempt so a sudden exit
            // retries, rather than silently skips, this exact candidate.
            if (!SaveAlienFarmState(
                    aStatePath,
                    aMinimumScoreFixed,
                    pMaximumHeadExactMatches,
                    pMaximumTailExactMatches,
                    pMaximumTailPartialMatches,
                    aTotalRawAttempts - 1ULL,
                    aSaved.size(),
                    pErrorMessage)) {
                return false;
            }
            std::printf("alien progress: tried=%llu valid=%llu "
                        "score-pass=%llu difference-reject=%llu "
                        "saved=%llu/%llu\n",
                        static_cast<unsigned long long>(aRunAttempts),
                        static_cast<unsigned long long>(aRunValid),
                        static_cast<unsigned long long>(aRunScorePassed),
                        static_cast<unsigned long long>(
                            aRunDifferenceRejected),
                        static_cast<unsigned long long>(aRunAccepted),
                        static_cast<unsigned long long>(pNewLoopTarget));
        }
        const std::size_t aHeartIndex =
            aSaved.size() % kAlienHeartCount;
        const LoopCorePattern11 &aCore = aHearts[aHeartIndex];
        const AlienNormalization &aNormalization =
            aNormalizations[aHeartIndex];
        LoopNewHeart11 aHeart;
        aHeart.mHeart = aCore;

        Generator aGenerator(MixFarmSeed(
            0x414C49454E4C4F4FULL ^
            GoldHeartSignature(aCore) ^
            (aTotalRawAttempts * 0xD1342543DE82EF95ULL)));
        LoopHeadPattern11 aHead;
        aHead.mWandererForOrbiter = IdentityRoles();
        Shuffle(&aHead.mWandererForOrbiter, &aGenerator);
        aHead.mPermutationRank = LoopHeadFarmer::Rank(aHead);
        if (!LoopHeadFarmer::IsValid(aHead)) {
            SetError(pErrorMessage,
                     "Alien loop farm generated an invalid head");
            return false;
        }
        const std::size_t aPatternIndex = aGenerator.Below(
            LoopHeadFarmer::kRetainedPatternCount);
        const DistanceMatrix aDistances = HeartTemporalDistances(aCore);
        const PairInfoMatrix aPairs = MakePairInfo(
            aCore, aHead, aPatternIndex, aDistances);
        LoopTailPattern11 aTail;
        Candidate aEvaluated;
        if (!GenerateTail(aPairs, &aGenerator, &aTail) ||
            !EvaluateAscendencyCandidate(
                aHeart,
                aHead,
                aPatternIndex,
                aPairs,
                aTail,
                &aEvaluated)) {
            continue;
        }
        ++aRunValid;
        const MetricValues aValues =
            RankingDisplayValues(aEvaluated.mScore);
        const std::uint32_t aScoreFixed = AlienScoreFixed(
            aValues, aNormalization);
        if (aScoreFixed <= aMinimumScoreFixed) {
            continue;
        }
        ++aRunScorePassed;

        std::size_t aWorstHead = 0U;
        std::size_t aWorstTailExact = 0U;
        std::size_t aWorstTailPartial = 0U;
        if (!AlienIsDifferentFromPool(
                aHead,
                aTail,
                aSaved,
                pMaximumHeadExactMatches,
                pMaximumTailExactMatches,
                pMaximumTailPartialMatches,
                &aWorstHead,
                &aWorstTailExact,
                &aWorstTailPartial)) {
            ++aRunDifferenceRejected;
            continue;
        }

        AlienLoopRecord aRecord;
        aRecord.mHeartIndex = aHeartIndex;
        aRecord.mLocalIndex = aHeartCounts[aHeartIndex] + 1ULL;
        aRecord.mPatternIndex = aPatternIndex;
        aRecord.mHead = aHead;
        aRecord.mHeart = aCore;
        aRecord.mTail = aTail;
        aRecord.mValues = aValues;
        aRecord.mNormalization = aNormalization;
        aRecord.mScoreFixed = aScoreFixed;
        aRecord.mRawAttempt = aTotalRawAttempts;
        aRecord.mAcceptedOrdinal = aSaved.size() + 1ULL;
        const std::string aRecordPath = AlienLoopPath(
            pOutputFolderPath,
            aHeartIndex,
            aRecord.mLocalIndex);
        if (!SaveAlienLoopRecord(
                aRecordPath,
                aRecord,
                aMinimumScoreFixed,
                pMaximumHeadExactMatches,
                pMaximumTailExactMatches,
                pMaximumTailPartialMatches,
                pErrorMessage)) {
            return false;
        }
        aSaved.push_back(aRecord);
        ++aHeartCounts[aHeartIndex];
        ++aRunAccepted;
        if (!SaveAlienFarmState(
                aStatePath,
                aMinimumScoreFixed,
                pMaximumHeadExactMatches,
                pMaximumTailExactMatches,
                pMaximumTailPartialMatches,
                aTotalRawAttempts,
                aSaved.size(),
                pErrorMessage)) {
            return false;
        }
        std::printf("accepted %llu/%llu: heart=%02zu local=%04llu "
                    "score=%.6f closest={head:%zu tail:%zu partial:%zu} "
                    "%s\n",
                    static_cast<unsigned long long>(aRunAccepted),
                    static_cast<unsigned long long>(pNewLoopTarget),
                    aHeartIndex,
                    static_cast<unsigned long long>(aRecord.mLocalIndex),
                    static_cast<double>(aScoreFixed) / 10'000.0,
                    aWorstHead,
                    aWorstTailExact,
                    aWorstTailPartial,
                    aRecordPath.c_str());

        if (aRunAccepted == pNewLoopTarget) {
            break;
        }

    }

    if (!SaveAlienFarmState(
            aStatePath,
            aMinimumScoreFixed,
            pMaximumHeadExactMatches,
            pMaximumTailExactMatches,
            pMaximumTailPartialMatches,
            aTotalRawAttempts,
            aSaved.size(),
            pErrorMessage)) {
        return false;
    }
    std::printf("alien run complete: tried=%llu valid=%llu "
                "score-pass=%llu difference-reject=%llu saved=%llu/%llu\n\n",
                static_cast<unsigned long long>(aRunAttempts),
                static_cast<unsigned long long>(aRunValid),
                static_cast<unsigned long long>(aRunScorePassed),
                static_cast<unsigned long long>(aRunDifferenceRejected),
                static_cast<unsigned long long>(aRunAccepted),
                static_cast<unsigned long long>(pNewLoopTarget));
    return true;
}

bool LoopTailFarmer::PrintAscendencyInventory(
    const std::string &pFarmFolderPath,
    const std::string &pHeartSelection,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    std::vector<std::size_t> aHeartIndices;
    if (!ParseHeartSelection(pHeartSelection,
                             &aHeartIndices,
                             pErrorMessage)) {
        return false;
    }
    return PrintAscendencyInventoryForHearts(
        pFarmFolderPath, aHeartIndices, pErrorMessage);
}

bool LoopTailFarmer::FarmAscendency(
    const std::string &pHeartPatternPath,
    const std::string &pHeadPatternPath,
    const std::string &pCurrentTailPatternPath,
    const std::string &pFarmFolderPath,
    const std::string &pHeartSelection,
    const std::uint64_t pValidCandidatesPerTask,
    const std::uint64_t pCheckpointAttemptCount,
    const bool pSkipTierZero,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pValidCandidatesPerTask == 0ULL) ||
        (pCheckpointAttemptCount == 0ULL)) {
        SetError(pErrorMessage,
                 "Ascendency farm counts must both be non-zero");
        return false;
    }
    std::vector<std::size_t> aHeartIndices;
    if (!ParseHeartSelection(pHeartSelection,
                             &aHeartIndices,
                             pErrorMessage)) {
        return false;
    }

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pHeartPatternPath,
                             pHeadPatternPath,
                             pCurrentTailPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    std::printf("Ascendency farm: hearts=%s valid_candidates/task=%llu "
                "checkpoint_attempts=%llu skip_tier_0=%s output=%s\n",
                pHeartSelection.c_str(),
                static_cast<unsigned long long>(
                    pValidCandidatesPerTask),
                static_cast<unsigned long long>(
                    pCheckpointAttemptCount),
                pSkipTierZero ? "yes" : "no",
                ResolvedPath(pFarmFolderPath).c_str());
    if (!PrintAscendencyInventoryForHearts(
            pFarmFolderPath, aHeartIndices, pErrorMessage)) {
        return false;
    }

    std::uint64_t aTotalValidCandidates = 0ULL;
    std::uint64_t aTotalRawAttempts = 0ULL;
    std::size_t aTotalSkippedTierZero = 0U;
    for (const std::size_t aHeartIndex : aHeartIndices) {
        const LoopNewHeart11 &aHeart = aPatterns.mHearts[aHeartIndex];
        const DistanceMatrix aDistances =
            HeartTemporalDistances(aHeart.mHeart);
        AscendencyTierPolicy aTierPolicy;
        if (!MakeAscendencyTierPolicy(aHeart,
                                      aHeartIndex,
                                      aDistances,
                                      &aTierPolicy,
                                      pErrorMessage)) {
            return false;
        }
        PrintAscendencyTierPolicy(aHeartIndex, aTierPolicy);
        std::size_t aHeartPromotions = 0U;
        std::size_t aHeartSkippedTierZero = 0U;
        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            const LoopHeadPattern11 &aHead =
                aHeart.mHeads[aHeadIndex].mHead;
            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(aHeartIndex, aHeadIndex);
            const PairInfoMatrix aPairs = MakePairInfo(
                aHeart.mHeart, aHead, aPatternIndex, aDistances);

            bool aFound = false;
            AscendencyRecord aBest;
            if (!LoadAscendencyRecord(pFarmFolderPath,
                                      aHeartIndex,
                                      aHeadIndex,
                                      &aFound,
                                      &aBest,
                                      pErrorMessage)) {
                return false;
            }
            if (aFound) {
                const int aStoredTier = aBest.mTier;
                Candidate aRescored;
                if (!EvaluateAscendencyCandidate(
                        aHeart,
                        aHead,
                        aPatternIndex,
                        aPairs,
                        aBest.mCandidate.mTail,
                        &aRescored)) {
                    SetError(pErrorMessage,
                             "Saved Ascendency loop no longer validated for heart " +
                             std::to_string(aHeartIndex) + " head " +
                             std::to_string(aHeadIndex));
                    return false;
                }
                aBest.mCandidate = std::move(aRescored);
                aBest.mTier = AscendencyTier(
                    aBest.mCandidate.mScore, aTierPolicy);
                if ((aBest.mTier != aStoredTier) &&
                    !SaveAscendencyRecord(pFarmFolderPath,
                                          aHeartIndex,
                                          aHeadIndex,
                                          aBest,
                                          pErrorMessage)) {
                    return false;
                }
            } else {
                if (!EvaluateAscendencyCandidate(
                        aHeart,
                        aHead,
                        aPatternIndex,
                        aPairs,
                        aHeart.mHeads[aHeadIndex].mTail,
                        &aBest.mCandidate)) {
                    SetError(pErrorMessage,
                             "Current loop asset did not validate for Ascendency heart " +
                             std::to_string(aHeartIndex) + " head " +
                             std::to_string(aHeadIndex));
                    return false;
                }
                aBest.mTier = AscendencyTier(
                    aBest.mCandidate.mScore, aTierPolicy);
                if (!SaveAscendencyRecord(pFarmFolderPath,
                                          aHeartIndex,
                                          aHeadIndex,
                                          aBest,
                                          pErrorMessage)) {
                    return false;
                }
            }

            const int aStartingTier = aBest.mTier;
            if (pSkipTierZero &&
                (aBest.mTier == kAscendencyTierZero)) {
                ++aHeartSkippedTierZero;
                ++aTotalSkippedTierZero;
                continue;
            }

            Generator aGenerator(AscendencyGeneratorSeed(
                aPatternIndex, aBest.mAttempts));
            std::unordered_set<std::string> aKeys;
            const std::uint64_t aReserveCount =
                pValidCandidatesPerTask >= 999999ULL
                    ? 1000000ULL
                    : pValidCandidatesPerTask + 1ULL;
            aKeys.reserve(static_cast<std::size_t>(aReserveCount));
            aKeys.insert(aBest.mCandidate.mKey);
            std::uint64_t aValidCandidates = 0ULL;
            std::uint64_t aTaskAttempts = 0ULL;
            const std::uint64_t aMaximumAttempts =
                pValidCandidatesPerTask >
                    ((std::numeric_limits<std::uint64_t>::max() -
                      4096ULL) / 64ULL)
                    ? std::numeric_limits<std::uint64_t>::max()
                    : (pValidCandidatesPerTask * 64ULL) + 4096ULL;
            while ((aValidCandidates < pValidCandidatesPerTask) &&
                   (aTaskAttempts < aMaximumAttempts)) {
                ++aTaskAttempts;
                ++aBest.mAttempts;
                LoopTailPattern11 aTail;
                if (!GenerateTail(aPairs, &aGenerator, &aTail)) {
                    if ((aBest.mAttempts % pCheckpointAttemptCount) == 0ULL &&
                        !SaveAscendencyRecord(pFarmFolderPath,
                                              aHeartIndex,
                                              aHeadIndex,
                                              aBest,
                                              pErrorMessage)) {
                        return false;
                    }
                    continue;
                }
                const std::string aKey = TailKey(aTail);
                if (!aKeys.insert(aKey).second) {
                    if ((aBest.mAttempts % pCheckpointAttemptCount) == 0ULL &&
                        !SaveAscendencyRecord(pFarmFolderPath,
                                              aHeartIndex,
                                              aHeadIndex,
                                              aBest,
                                              pErrorMessage)) {
                        return false;
                    }
                    continue;
                }
                Candidate aCandidate;
                if (!EvaluateAscendencyCandidate(
                        aHeart,
                        aHead,
                        aPatternIndex,
                        aPairs,
                        aTail,
                        &aCandidate)) {
                    if ((aBest.mAttempts % pCheckpointAttemptCount) == 0ULL &&
                        !SaveAscendencyRecord(pFarmFolderPath,
                                              aHeartIndex,
                                              aHeadIndex,
                                              aBest,
                                              pErrorMessage)) {
                        return false;
                    }
                    continue;
                }
                ++aValidCandidates;
                ++aTotalValidCandidates;
                AscendencyRecord aCandidateRecord;
                aCandidateRecord.mCandidate = std::move(aCandidate);
                aCandidateRecord.mAttempts = aBest.mAttempts;
                aCandidateRecord.mTier = AscendencyTier(
                    aCandidateRecord.mCandidate.mScore,
                    aTierPolicy);
                if (AscendencyRecordIsBetter(aCandidateRecord, aBest)) {
                    aBest.mCandidate = std::move(
                        aCandidateRecord.mCandidate);
                    aBest.mTier = aCandidateRecord.mTier;
                }
                if ((aBest.mAttempts % pCheckpointAttemptCount) == 0ULL) {
                    if (!SaveAscendencyRecord(pFarmFolderPath,
                                              aHeartIndex,
                                              aHeadIndex,
                                              aBest,
                                              pErrorMessage)) {
                        return false;
                    }
                }
                if (pSkipTierZero &&
                    (aBest.mTier == kAscendencyTierZero)) {
                    break;
                }
            }
            aTotalRawAttempts += aTaskAttempts;
            if (!SaveAscendencyRecord(pFarmFolderPath,
                                      aHeartIndex,
                                      aHeadIndex,
                                      aBest,
                                      pErrorMessage)) {
                return false;
            }
            if (aBest.mTier < aStartingTier) {
                ++aHeartPromotions;
                std::printf("heart %zu loop %03zu promoted %s -> %s "
                            "after %llu total attempts\n",
                            aHeartIndex,
                            aHeadIndex + 1U,
                            kAscendencyTierFolderNames[
                                static_cast<std::size_t>(aStartingTier)],
                            kAscendencyTierFolderNames[
                                static_cast<std::size_t>(aBest.mTier)],
                            static_cast<unsigned long long>(
                                aBest.mAttempts));
            }
        }
        std::printf("Ascendency processed heart %zu: promotions=%zu "
                    "tier_0_skipped=%zu\n",
                    aHeartIndex,
                    aHeartPromotions,
                    aHeartSkippedTierZero);
        if (!PrintAscendencyInventoryForHearts(
                pFarmFolderPath,
                std::vector<std::size_t>{aHeartIndex},
                pErrorMessage)) {
            return false;
        }
    }
    std::printf("Ascendency farm summary: valid_candidates=%llu "
                "raw_attempts=%llu tier_0_tasks_skipped=%zu\n",
                static_cast<unsigned long long>(aTotalValidCandidates),
                static_cast<unsigned long long>(aTotalRawAttempts),
                aTotalSkippedTierZero);
    return PrintAscendencyInventoryForHearts(
        pFarmFolderPath, aHeartIndices, pErrorMessage);
}

bool LoopTailFarmer::ExplainScores(
    const std::string &pHeartPatternPath,
    const std::string &pHeadPatternPath,
    const std::size_t pHeartIndex,
    const std::size_t pHeadIndex,
    const std::uint64_t pCandidateCount,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pCandidateCount == 0ULL) ||
        (pHeartIndex >= LoopHeadFarmer::kCoreCount) ||
        (pHeadIndex >= LoopHeadFarmer::kPatternsPerCore)) {
        SetError(pErrorMessage,
                 "Loop tail score example had an invalid count, heart, or head index");
        return false;
    }

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pHeartPatternPath,
                             pHeadPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    const std::size_t aPatternIndex =
        LoopHeadFarmer::PatternIndex(pHeartIndex, pHeadIndex);
    PairScoreSample aSample;
    if (!MakePairScoreSample(aPatterns,
                             pHeartIndex,
                             pHeadIndex,
                             pCandidateCount,
                             &aSample,
                             pErrorMessage)) {
        return false;
    }

    std::printf("\n============================================================\n");
    std::printf("LOOP TAIL SCORE EXAMPLE\n");
    std::printf("heart=%zu head=%zu pattern=%zu valid_candidates=%llu "
                "attempts=%llu\n",
                pHeartIndex,
                pHeadIndex,
                aPatternIndex,
                static_cast<unsigned long long>(pCandidateCount),
                static_cast<unsigned long long>(aSample.mAttempts));
    std::printf("rejected: schedule=%llu transition=%llu duplicate=%llu\n",
                static_cast<unsigned long long>(
                    aSample.mRejectedSchedules),
                static_cast<unsigned long long>(
                    aSample.mRejectedTransitions),
                static_cast<unsigned long long>(
                    aSample.mRejectedDuplicates));
    std::printf("------------------------------------------------------------\n");
    PrintDetailedScore("BEST ", aSample.mSafeBest);
    std::printf("------------------------------------------------------------\n");
    PrintDetailedScore("WORST", aSample.mSafeWorst);
    PrintScoreExplanation(aSample.mSafeBest, aSample.mSafeWorst);
    std::printf("============================================================\n\n");
    return true;
}

bool LoopTailFarmer::AnalyzeScores(
    const std::string &pHeartPatternPath,
    const std::string &pHeadPatternPath,
    const std::string &pOutputPath,
    const std::size_t pFirstHeartIndex,
    const std::size_t pFirstHeadIndex,
    const std::size_t pPairCount,
    const std::uint64_t pCandidateCount,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pPairCount == 0U) || (pCandidateCount == 0ULL) ||
        (pCandidateCount >
         std::numeric_limits<std::size_t>::max()) ||
        (pFirstHeartIndex >= LoopHeadFarmer::kCoreCount) ||
        (pFirstHeadIndex >= LoopHeadFarmer::kPatternsPerCore) ||
        (pPairCount >
         (LoopHeadFarmer::kCoreCount - pFirstHeartIndex)) ||
        (pPairCount >
         (LoopHeadFarmer::kPatternsPerCore - pFirstHeadIndex))) {
        SetError(pErrorMessage,
                 "Loop tail batch analysis had an invalid range or candidate count");
        return false;
    }

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pHeartPatternPath,
                             pHeadPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    std::ostringstream aBody;
    std::array<std::size_t, kScoreFieldCount> aVariablePairCounts{};
    std::array<std::size_t, kExplorationRankingMetricCount>
        aExplorationVariablePairCounts{};
    std::array<std::size_t, kExplorationRankingMetricCount>
        aExplorationFirstDecisionCounts{};
    std::array<std::size_t, kExplorationRankingMetricCount>
        aExplorationReductionCounts{};
    std::array<std::uint64_t, kExplorationRankingMetricCount>
        aExplorationSurvivorTotals{};
    std::array<std::size_t, kSafeRankingMetricCount>
        aSafeVariablePairCounts{};
    std::array<std::size_t, kSafeRankingMetricCount>
        aSafeFirstDecisionCounts{};
    std::array<std::size_t, kSafeRankingMetricCount>
        aSafeReductionCounts{};
    std::array<std::uint64_t, kSafeRankingMetricCount>
        aSafeSurvivorTotals{};
    std::size_t aSameBestCount = 0U;
    std::size_t aMaximumSafeBestExplorationRank = 0U;
    std::uint64_t aSafeBestExplorationRankTotal = 0ULL;
    std::size_t aSafeTopSurvivorTotal = 0U;
    std::size_t aSafeTopCandidateTotal = 0U;
    std::uint64_t aFirstInfluenceEqualsPairUnionTotal = 0ULL;

    for (std::size_t aTrialIndex = 0U;
         aTrialIndex < pPairCount;
         ++aTrialIndex) {
        const std::size_t aHeartIndex =
            pFirstHeartIndex + aTrialIndex;
        const std::size_t aHeadIndex =
            pFirstHeadIndex + aTrialIndex;
        const std::size_t aPatternIndex =
            LoopHeadFarmer::PatternIndex(aHeartIndex, aHeadIndex);
        PairScoreSample aSample;
        if (!MakePairScoreSample(aPatterns,
                                 aHeartIndex,
                                 aHeadIndex,
                                 pCandidateCount,
                                 &aSample,
                                 pErrorMessage)) {
            return false;
        }

        aSameBestCount +=
            aSample.mExplorationBest.mKey == aSample.mSafeBest.mKey;
        aMaximumSafeBestExplorationRank = std::max(
            aMaximumSafeBestExplorationRank,
            aSample.mSafeBestExplorationRank);
        aSafeBestExplorationRankTotal +=
            aSample.mSafeBestExplorationRank;
        aSafeTopSurvivorTotal +=
            aSample.mSafeTop100InExplorationTop500;
        aSafeTopCandidateTotal += aSample.mSafeTop100Count;
        aFirstInfluenceEqualsPairUnionTotal +=
            aSample.mFirstInfluenceEqualsPairUnionCount;

        for (std::size_t i = 0U; i < kRankingMetricNames.size(); ++i) {
            aVariablePairCounts[i] +=
                aSample.mDistinctValueCounts[i] > 1U;
        }

        const auto aExplorationBestValues =
            ExplorationRankingValues(aSample.mExplorationBest.mScore);
        const auto aExplorationWorstValues =
            ExplorationRankingValues(aSample.mExplorationWorst.mScore);
        bool aFoundExplorationDecision = false;
        for (std::size_t i = 0U;
             i < kExplorationRankingMetricCount;
             ++i) {
            aExplorationVariablePairCounts[i] +=
                aSample.mExplorationDistinctValueCounts[i] > 1U;
            if (!aFoundExplorationDecision &&
                (aExplorationBestValues[i] !=
                 aExplorationWorstValues[i])) {
                ++aExplorationFirstDecisionCounts[i];
                aFoundExplorationDecision = true;
            }
            const std::size_t aPreviousExplorationCount =
                i == 0U
                    ? static_cast<std::size_t>(pCandidateCount)
                    : aSample.mExplorationSurvivorsAfterMetric[i - 1U];
            aExplorationReductionCounts[i] +=
                aSample.mExplorationSurvivorsAfterMetric[i] <
                aPreviousExplorationCount;
            aExplorationSurvivorTotals[i] +=
                aSample.mExplorationSurvivorsAfterMetric[i];
        }

        const auto aSafeBestValues =
            SafeRankingValues(aSample.mSafeBest.mScore);
        const auto aSafeWorstValues =
            SafeRankingValues(aSample.mSafeWorst.mScore);
        bool aFoundSafeDecision = false;
        for (std::size_t i = 0U; i < kSafeRankingMetricCount; ++i) {
            aSafeVariablePairCounts[i] +=
                aSample.mSafeDistinctValueCounts[i] > 1U;
            if (!aFoundSafeDecision &&
                (aSafeBestValues[i] != aSafeWorstValues[i])) {
                ++aSafeFirstDecisionCounts[i];
                aFoundSafeDecision = true;
            }
            const std::size_t aPreviousSafeCount =
                i == 0U
                    ? static_cast<std::size_t>(pCandidateCount)
                    : aSample.mSafeSurvivorsAfterMetric[i - 1U];
            aSafeReductionCounts[i] +=
                aSample.mSafeSurvivorsAfterMetric[i] <
                aPreviousSafeCount;
            aSafeSurvivorTotals[i] +=
                aSample.mSafeSurvivorsAfterMetric[i];
        }

        aBody << "\n============================================================\n";
        aBody << "TRIAL " << (aTrialIndex + 1U)
              << ": heart=" << aHeartIndex
              << " head=" << aHeadIndex
              << " pattern=" << aPatternIndex
              << " candidates=" << pCandidateCount
              << " attempts=" << aSample.mAttempts << "\n";
        aBody << "rejected: schedule=" << aSample.mRejectedSchedules
              << " transition=" << aSample.mRejectedTransitions
              << " duplicate=" << aSample.mRejectedDuplicates << "\n";
        aBody << "stage agreement: same_best="
              << (aSample.mExplorationBest.mKey ==
                  aSample.mSafeBest.mKey ? "yes" : "no")
              << " safe_best_exploration_rank="
              << aSample.mSafeBestExplorationRank
              << " safe_top_" << aSample.mSafeTop100Count
              << "_inside_exploration_top_"
              << aSample.mExplorationTop500Count << "="
              << aSample.mSafeTop100InExplorationTop500 << "\n";
        aBody << "\nMETRIC RANGE WITHIN THIS FIXED HEART/HEAD\n";
        for (std::size_t i = 0U; i < kRankingMetricNames.size(); ++i) {
            aBody << "  " << (i + 1U) << ". "
                  << kRankingMetricNames[i]
                  << ": min=" << aSample.mMinimumValues[i]
                  << " max=" << aSample.mMaximumValues[i]
                  << " distinct=" << aSample.mDistinctValueCounts[i]
                  << " preference="
                  << (kRankingHigherIsBetter[i] ? "higher" : "lower")
                  << "\n";
        }
        aBody << "\nEXPLORATION RANKING SURVIVORS\n";
        for (std::size_t i = 0U;
             i < kExplorationRankingMetricCount;
             ++i) {
            aBody << "  " << (i + 1U) << ". "
                  << kExplorationRankingMetricNames[i]
                  << ": survivors="
                  << aSample.mExplorationSurvivorsAfterMetric[i]
                  << "\n";
        }
        aBody << "\nSAFE RANKING SURVIVORS\n";
        for (std::size_t i = 0U; i < kSafeRankingMetricCount; ++i) {
            aBody << "  " << (i + 1U) << ". "
                  << kSafeRankingMetricNames[i]
                  << ": survivors="
                  << aSample.mSafeSurvivorsAfterMetric[i]
                  << "\n";
        }
        aBody << "\n";
        AppendTail(&aBody, "EXPLORATION BEST ",
                   aSample.mExplorationBest);
        AppendTail(&aBody, "EXPLORATION WORST", 
                   aSample.mExplorationWorst);
        AppendTail(&aBody, "SAFE BEST        ", aSample.mSafeBest);
        AppendTail(&aBody, "SAFE WORST       ", aSample.mSafeWorst);

        std::printf("Score analysis processed pair %zu/%zu: heart=%zu "
                    "head=%zu\n",
                    aTrialIndex + 1U,
                    pPairCount,
                    aHeartIndex,
                    aHeadIndex);
    }

    std::ostringstream aReport;
    aReport << "LOOP HEAD/TAIL SCORE ANALYSIS\n"
            << "pairs=" << pPairCount
            << " candidates_per_pair=" << pCandidateCount
            << " first_heart=" << pFirstHeartIndex
            << " first_head=" << pFirstHeadIndex << "\n\n";
    aReport << "Each phase is lexicographic. The first differing metric in "
               "that phase's listed order decides.\n\n";
    aReport << "EXPLORATION PRIORITY\n";
    for (std::size_t i = 0U;
         i < kExplorationRankingMetricCount;
         ++i) {
        aReport << "  " << (i + 1U) << ". "
                << kExplorationRankingMetricNames[i] << " ("
                << (kExplorationRankingHigherIsBetter[i]
                        ? "higher" : "lower")
                << ")\n";
    }
    aReport << "\nSAFE PRIORITY\n";
    for (std::size_t i = 0U; i < kSafeRankingMetricCount; ++i) {
        aReport << "  " << (i + 1U) << ". "
                << kSafeRankingMetricNames[i] << " ("
                << (kSafeRankingHigherIsBetter[i] ? "higher" : "lower")
                << ")\n";
    }
    aReport << "\n";
    aReport << "CROSS-TRIAL SUMMARY\n";
    aReport << "  Exploration and Safe chose the same best tail in "
            << aSameBestCount << "/" << pPairCount << " trials.\n";
    aReport << "  Safe-best Exploration rank: average="
            << (static_cast<double>(aSafeBestExplorationRankTotal) /
                static_cast<double>(pPairCount))
            << " maximum=" << aMaximumSafeBestExplorationRank << ".\n";
    aReport << "  Safe top candidates surviving Exploration top pools: "
            << aSafeTopSurvivorTotal << "/"
            << aSafeTopCandidateTotal << ".\n\n";
    aReport << "  First minimum influence equaled minimum pair union in "
            << aFirstInfluenceEqualsPairUnionTotal << "/"
            << (pCandidateCount * pPairCount)
            << " candidates.\n\n";
    aReport << "RAW METRIC VARIABILITY\n";
    for (std::size_t i = 0U; i < kRankingMetricNames.size(); ++i) {
        aReport << "  " << (i + 1U) << ". "
                << kRankingMetricNames[i]
                << ": variable_pairs=" << aVariablePairCounts[i]
                << "/" << pPairCount << "\n";
    }
    aReport << "\nEXPLORATION RANKING EFFECTIVENESS\n";
    for (std::size_t i = 0U;
         i < kExplorationRankingMetricCount;
         ++i) {
        aReport << "  " << (i + 1U) << ". "
                << kExplorationRankingMetricNames[i]
                << ": variable_pairs="
                << aExplorationVariablePairCounts[i]
                << "/" << pPairCount
                << " first_decisions="
                << aExplorationFirstDecisionCounts[i]
                << "/" << pPairCount
                << " reductions=" << aExplorationReductionCounts[i]
                << "/" << pPairCount
                << " average_survivors="
                << (static_cast<double>(aExplorationSurvivorTotals[i]) /
                    static_cast<double>(pPairCount))
                << "\n";
    }
    aReport << "\nSAFE RANKING EFFECTIVENESS\n";
    for (std::size_t i = 0U; i < kSafeRankingMetricCount; ++i) {
        aReport << "  " << (i + 1U) << ". "
                << kSafeRankingMetricNames[i]
                << ": variable_pairs=" << aSafeVariablePairCounts[i]
                << "/" << pPairCount
                << " first_decisions=" << aSafeFirstDecisionCounts[i]
                << "/" << pPairCount
                << " reductions=" << aSafeReductionCounts[i]
                << "/" << pPairCount
                << " average_survivors="
                << (static_cast<double>(aSafeSurvivorTotals[i]) /
                    static_cast<double>(pPairCount))
                << "\n";
    }
    aReport << aBody.str();

    const std::string aText = aReport.str();
    const std::vector<std::uint8_t> aBytes(
        aText.begin(), aText.end());
    const std::string aPath = ResolvedPath(pOutputPath);
    if (!FileIO::Save(aPath, aBytes)) {
        SetError(pErrorMessage,
                 "Loop tail batch analysis could not save " + aPath);
        return false;
    }
    std::printf("Saved loop tail score analysis to %s (%zu bytes)\n",
                aPath.c_str(), aBytes.size());
    return true;
}

bool LoopTailFarmer::ExplorePerHeartMaxima(
    const std::string &pHeartPatternPath,
    const std::string &pHeadPatternPath,
    const std::string &pOutputPath,
    const std::size_t pFirstHeartIndex,
    const std::size_t pHeartCount,
    const std::uint64_t pTrialsPerHeart,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pTrialsPerHeart == 0ULL) || (pHeartCount == 0U) ||
        (pFirstHeartIndex >= LoopHeadFarmer::kCoreCount) ||
        (pHeartCount >
            (LoopHeadFarmer::kCoreCount - pFirstHeartIndex))) {
        SetError(pErrorMessage,
                 "TenK trial exploration range or trial count was invalid");
        return false;
    }

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pHeartPatternPath,
                             pHeadPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    std::ostringstream aReport;
    aReport << "TEN K TRIAL EXPLORE\n"
            << "===================\n\n"
            << "valid_trials_per_heart=" << pTrialsPerHeart << "\n"
            << "first_heart=" << pFirstHeartIndex << "\n"
            << "heart_count=" << pHeartCount << "\n"
            << "head_schedule=round_robin_across_110_fixed_heads\n\n"
            << "MAXIMUM is the raw numeric maximum, even for a statistic "
               "where lower is preferred. COUNT is the number of valid "
               "trials tied at that maximum.\n\n";

    const std::size_t aLastHeart = pFirstHeartIndex + pHeartCount;
    for (std::size_t aHeartIndex = pFirstHeartIndex;
         aHeartIndex < aLastHeart;
         ++aHeartIndex) {
        const LoopNewHeart11 &aHeart = aPatterns.mHearts[aHeartIndex];
        const DistanceMatrix aDistances =
            HeartTemporalDistances(aHeart.mHeart);
        std::vector<PairInfoMatrix> aPairPlans;
        aPairPlans.reserve(LoopHeadFarmer::kPatternsPerCore);
        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(aHeartIndex, aHeadIndex);
            aPairPlans.push_back(MakePairInfo(
                aHeart.mHeart,
                aHeart.mHeads[aHeadIndex].mHead,
                aPatternIndex,
                aDistances));
        }

        std::array<int, kScoreFieldCount> aMaximumValues{};
        aMaximumValues.fill(std::numeric_limits<int>::min());
        std::array<std::uint64_t, kScoreFieldCount> aMaximumCounts{};

        const std::uint64_t aReserveCount = pTrialsPerHeart >= 999999ULL
            ? 1000000ULL
            : pTrialsPerHeart + 1ULL;
        std::unordered_set<std::string> aSeen;
        aSeen.reserve(static_cast<std::size_t>(aReserveCount));
        Generator aGenerator(MixFarmSeed(
            0x54454E4B54524941ULL ^
            static_cast<std::uint64_t>(aHeartIndex)));

        std::uint64_t aValidTrials = 0ULL;
        std::uint64_t aRawAttempts = 0ULL;
        std::uint64_t aRejectedSchedules = 0ULL;
        std::uint64_t aRejectedTransitions = 0ULL;
        std::uint64_t aRejectedDuplicates = 0ULL;
        const std::uint64_t aMaximumAttempts = pTrialsPerHeart >
            ((std::numeric_limits<std::uint64_t>::max() - 4096ULL) /
             128ULL)
                ? std::numeric_limits<std::uint64_t>::max()
                : (pTrialsPerHeart * 128ULL) + 4096ULL;

        while ((aValidTrials < pTrialsPerHeart) &&
               (aRawAttempts < aMaximumAttempts)) {
            ++aRawAttempts;
            const std::size_t aHeadIndex = static_cast<std::size_t>(
                aValidTrials % LoopHeadFarmer::kPatternsPerCore);
            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(aHeartIndex, aHeadIndex);
            const LoopHeadPattern11 &aHead =
                aHeart.mHeads[aHeadIndex].mHead;

            LoopTailPattern11 aTail;
            if (!GenerateTail(aPairPlans[aHeadIndex],
                              &aGenerator,
                              &aTail)) {
                ++aRejectedSchedules;
                continue;
            }
            std::string aKey = TailKey(aTail);
            aKey.insert(aKey.begin(), static_cast<char>(aHeadIndex));
            if (!aSeen.insert(aKey).second) {
                ++aRejectedDuplicates;
                continue;
            }

            Candidate aCandidate;
            if (!EvaluateAscendencyCandidate(
                    aHeart,
                    aHead,
                    aPatternIndex,
                    aPairPlans[aHeadIndex],
                    aTail,
                    &aCandidate)) {
                ++aRejectedTransitions;
                continue;
            }

            const auto aValues = RankingDisplayValues(aCandidate.mScore);
            for (std::size_t i = 0U; i < aValues.size(); ++i) {
                if (aValues[i] > aMaximumValues[i]) {
                    aMaximumValues[i] = aValues[i];
                    aMaximumCounts[i] = 1ULL;
                } else if (aValues[i] == aMaximumValues[i]) {
                    ++aMaximumCounts[i];
                }
            }
            ++aValidTrials;
        }

        if (aValidTrials != pTrialsPerHeart) {
            SetError(pErrorMessage,
                     "TenK trial exploration exhausted its attempt budget "
                     "for heart " + std::to_string(aHeartIndex));
            return false;
        }

        aReport << "============================================================\n"
                << "HEART " << std::setw(3) << std::setfill('0')
                << aHeartIndex << std::setfill(' ') << "\n"
                << "valid=" << aValidTrials
                << " raw_attempts=" << aRawAttempts
                << " rejected_schedule=" << aRejectedSchedules
                << " rejected_transition=" << aRejectedTransitions
                << " rejected_duplicate=" << aRejectedDuplicates
                << "\n\n"
                << " #  | STAT                                             "
                   "| PREF   | MAXIMUM    | COUNT      | RATE\n"
                << "----+--------------------------------------------------"
                   "+--------+------------+------------+-----------\n";
        for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
            const double aRate =
                (static_cast<double>(aMaximumCounts[i]) * 100.0) /
                static_cast<double>(pTrialsPerHeart);
            aReport << std::setw(3) << (i + 1U) << " | "
                    << std::left << std::setw(48)
                    << kRankingMetricNames[i] << std::right << " | "
                    << std::setw(6)
                    << (kRankingHigherIsBetter[i] ? "higher" : "lower")
                    << " | " << std::setw(10) << aMaximumValues[i]
                    << " | " << std::setw(10) << aMaximumCounts[i]
                    << " | " << std::fixed << std::setprecision(4)
                    << std::setw(8) << aRate << "%\n";
        }
        aReport << "\n";

        std::printf("TenK trial explore completed heart %zu (%zu/%zu): "
                    "valid=%llu raw=%llu\n",
                    aHeartIndex,
                    (aHeartIndex - pFirstHeartIndex) + 1U,
                    pHeartCount,
                    static_cast<unsigned long long>(aValidTrials),
                    static_cast<unsigned long long>(aRawAttempts));
    }

    const std::string aText = aReport.str();
    const std::vector<std::uint8_t> aBytes(aText.begin(), aText.end());
    const std::string aPath = ResolvedPath(pOutputPath);
    if (!FileIO::Save(aPath, aBytes)) {
        SetError(pErrorMessage,
                 "TenK trial exploration could not save " + aPath);
        return false;
    }
    std::printf("Saved TenK trial exploration to %s (%zu bytes)\n",
                aPath.c_str(), aBytes.size());
    return true;
}

bool LoopTailFarmer::ExploreMetricSlices(
    const std::string &pHeartPatternPath,
    const std::string &pHeadPatternPath,
    const std::string &pCheckpointFolderPath,
    const std::string &pOutputPath,
    const std::size_t pFirstHeartIndex,
    const std::size_t pHeartCount,
    const std::uint64_t pTrialsPerHead,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pTrialsPerHead == 0ULL) || (pHeartCount == 0U) ||
        (pFirstHeartIndex >= LoopHeadFarmer::kCoreCount) ||
        (pHeartCount >
            (LoopHeadFarmer::kCoreCount - pFirstHeartIndex))) {
        SetError(pErrorMessage,
                 "Metric slice exploration range or count was invalid");
        return false;
    }

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pHeartPatternPath,
                             pHeadPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    const std::uint64_t aExpectedTotal = pTrialsPerHead *
        static_cast<std::uint64_t>(
            LoopHeadFarmer::kPatternsPerCore) *
        static_cast<std::uint64_t>(pHeartCount);
    std::printf("Metric slice explore: %llu trials/head, %zu hearts, "
                "%llu total valid loops\n",
                static_cast<unsigned long long>(pTrialsPerHead),
                pHeartCount,
                static_cast<unsigned long long>(aExpectedTotal));
    std::printf("Checkpoints: %s\n",
                ResolvedPath(pCheckpointFolderPath).c_str());

    std::vector<MetricSliceHeartSummary> aHeartSummaries;
    aHeartSummaries.reserve(pHeartCount);
    const std::size_t aLastHeart = pFirstHeartIndex + pHeartCount;
    for (std::size_t aHeartIndex = pFirstHeartIndex;
         aHeartIndex < aLastHeart;
         ++aHeartIndex) {
        const LoopNewHeart11 &aHeart = aPatterns.mHearts[aHeartIndex];
        const DistanceMatrix aDistances =
            HeartTemporalDistances(aHeart.mHeart);
        std::vector<MetricSliceHeadSummary> aHeadSummaries;
        aHeadSummaries.reserve(LoopHeadFarmer::kPatternsPerCore);
        std::size_t aLoadedHeads = 0U;

        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            MetricSliceHeadSummary aSummary;
            bool aFound = false;
            if (!LoadMetricSliceHeadSummary(
                    pCheckpointFolderPath,
                    pTrialsPerHead,
                    aHeartIndex,
                    aHeadIndex,
                    &aFound,
                    &aSummary,
                    pErrorMessage)) {
                return false;
            }
            if (aFound) {
                ++aLoadedHeads;
                aHeadSummaries.push_back(std::move(aSummary));
                continue;
            }

            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(aHeartIndex, aHeadIndex);
            const LoopHeadPattern11 &aHead =
                aHeart.mHeads[aHeadIndex].mHead;
            const PairInfoMatrix aPairs = MakePairInfo(
                aHeart.mHeart, aHead, aPatternIndex, aDistances);
            Generator aGenerator(MixFarmSeed(
                0x4D4554524943534CULL ^
                static_cast<std::uint64_t>(aPatternIndex)));
            std::vector<MetricValues> aRows;
            aRows.reserve(static_cast<std::size_t>(pTrialsPerHead));
            std::unordered_set<std::string> aSeen;
            const std::uint64_t aReserveCount =
                pTrialsPerHead >= 999999ULL
                    ? 1000000ULL
                    : pTrialsPerHead + 1ULL;
            aSeen.reserve(static_cast<std::size_t>(aReserveCount));
            const std::uint64_t aMaximumAttempts = pTrialsPerHead >
                ((std::numeric_limits<std::uint64_t>::max() - 4096ULL) /
                 128ULL)
                    ? std::numeric_limits<std::uint64_t>::max()
                    : (pTrialsPerHead * 128ULL) + 4096ULL;

            while ((aRows.size() < pTrialsPerHead) &&
                   (aSummary.mRawAttempts < aMaximumAttempts)) {
                ++aSummary.mRawAttempts;
                LoopTailPattern11 aTail;
                if (!GenerateTail(aPairs, &aGenerator, &aTail)) {
                    continue;
                }
                const std::string aKey = TailKey(aTail);
                if (!aSeen.insert(aKey).second) {
                    continue;
                }
                Candidate aCandidate;
                if (!EvaluateAscendencyCandidate(
                        aHeart,
                        aHead,
                        aPatternIndex,
                        aPairs,
                        aTail,
                        &aCandidate)) {
                    continue;
                }
                aRows.push_back(
                    RankingDisplayValues(aCandidate.mScore));
            }
            if (aRows.size() != pTrialsPerHead) {
                SetError(pErrorMessage,
                         "Metric slice explorer exhausted its attempt budget "
                         "for heart " + std::to_string(aHeartIndex) +
                         " head " + std::to_string(aHeadIndex));
                return false;
            }
            aSummary.mValidTrials = pTrialsPerHead;
            SummarizeMetricSliceRows(aRows, &aSummary);
            if (!SaveMetricSliceHeadSummary(
                    pCheckpointFolderPath,
                    aHeartIndex,
                    aHeadIndex,
                    aSummary,
                    pErrorMessage)) {
                return false;
            }
            aHeadSummaries.push_back(std::move(aSummary));
            const MetricSliceHeadSummary &aSaved = aHeadSummaries.back();
            std::printf(
                "metric slice heart %03zu head %03zu/%03zu: "
                "valid=%llu raw=%llu exact_joint=%llu "
                "one_percent_joint=%llu proposed_joint=%llu\n",
                aHeartIndex,
                aHeadIndex + 1U,
                LoopHeadFarmer::kPatternsPerCore,
                static_cast<unsigned long long>(aSaved.mValidTrials),
                static_cast<unsigned long long>(aSaved.mRawAttempts),
                static_cast<unsigned long long>(
                    aSaved.mDirectionalBestJointCount),
                static_cast<unsigned long long>(
                    aSaved.mOnePercentJointCount),
                static_cast<unsigned long long>(
                    aSaved.mProposedGateJointCount));
        }

        aHeartSummaries.push_back(
            AggregateMetricSliceHeart(aHeadSummaries));
        const MetricSliceHeartSummary &aFinishedHeart =
            aHeartSummaries.back();
        std::printf(
            "metric slice completed heart %03zu (%zu/%zu): "
            "loaded_heads=%zu valid=%llu exact_joint=%llu "
            "one_percent_joint=%llu proposed_joint=%llu\n",
            aHeartIndex,
            (aHeartIndex - pFirstHeartIndex) + 1U,
            pHeartCount,
            aLoadedHeads,
            static_cast<unsigned long long>(
                aFinishedHeart.mValidTrials),
            static_cast<unsigned long long>(
                aFinishedHeart.mDirectionalBestJointCount),
            static_cast<unsigned long long>(
                aFinishedHeart.mOnePercentJointCount),
            static_cast<unsigned long long>(
                aFinishedHeart.mProposedGateJointCount));

        const std::string aText = MetricSliceReport(
            aHeartSummaries,
            pFirstHeartIndex,
            pHeartCount,
            pTrialsPerHead);
        const std::vector<std::uint8_t> aBytes(
            aText.begin(), aText.end());
        const std::string aPath = ResolvedPath(pOutputPath);
        if (!FileIO::Save(aPath, aBytes)) {
            SetError(pErrorMessage,
                     "Metric slice explorer could not save " + aPath);
            return false;
        }
    }

    std::printf("Metric slice exploration report saved to %s\n",
                ResolvedPath(pOutputPath).c_str());
    return true;
}

bool LoopTailFarmer::ExportMetricTable(
    const std::string &pHeartPatternPath,
    const std::string &pCheckpointFolderPath,
    const std::string &pOutputPath,
    const std::string &pSchemaPath,
    const std::size_t pFirstHeartIndex,
    const std::size_t pHeartCount,
    const std::uint64_t pTrialsPerHeart,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pTrialsPerHeart == 0ULL) || (pHeartCount == 0U) ||
        (pFirstHeartIndex >= LoopHeadFarmer::kCoreCount) ||
        (pHeartCount >
            (LoopHeadFarmer::kCoreCount - pFirstHeartIndex))) {
        SetError(pErrorMessage,
                 "Metric table export range or count was invalid");
        return false;
    }

    LoopCorePatternFile11 aHeartPatterns;
    if (!LoopCorePatternFarmer::Load(pHeartPatternPath,
                                     &aHeartPatterns,
                                     pErrorMessage)) {
        return false;
    }
    if (aHeartPatterns.mPatterns.size() < LoopHeadFarmer::kCoreCount) {
        SetError(pErrorMessage,
                 "Random metric table exporter did not load all 180 "
                 "heart patterns");
        return false;
    }

    const std::string aHeader = RandomMetricTableHeader();
    const std::size_t aLastHeart = pFirstHeartIndex + pHeartCount;
    std::printf("Random-head/random-tail metric table export: "
                "%llu rows/heart, %zu hearts, "
                "%llu total rows\n",
                static_cast<unsigned long long>(pTrialsPerHeart),
                pHeartCount,
                static_cast<unsigned long long>(
                    pTrialsPerHeart *
                    static_cast<std::uint64_t>(pHeartCount)));

    for (std::size_t aHeartIndex = pFirstHeartIndex;
         aHeartIndex < aLastHeart;
         ++aHeartIndex) {
        const std::string aShardPath = MetricTableShardPath(
            pCheckpointFolderPath, pTrialsPerHeart, aHeartIndex);
        bool aFound = false;
        std::vector<std::uint8_t> aExistingBytes;
        if (!LoadValidMetricTableShard(
                aShardPath,
                aHeader,
                pTrialsPerHeart,
                &aFound,
                &aExistingBytes,
                pErrorMessage)) {
            return false;
        }
        if (aFound) {
            std::printf("metric table heart %03zu/%03zu loaded "
                        "from checkpoint\n",
                        aHeartIndex,
                        aLastHeart - 1U);
            continue;
        }

        LoopNewHeart11 aHeart;
        aHeart.mHeart = aHeartPatterns.mPatterns[aHeartIndex];
        const DistanceMatrix aDistances =
            HeartTemporalDistances(aHeart.mHeart);

        Generator aGenerator(MixFarmSeed(
            0x52414E444F4D4D54ULL ^
            static_cast<std::uint64_t>(aHeartIndex)));

        std::ostringstream aShard;
        aShard << aHeader;
        std::uint64_t aValidTrials = 0ULL;
        std::uint64_t aRawAttempts = 0ULL;
        const std::uint64_t aMaximumAttempts = pTrialsPerHeart >
            ((std::numeric_limits<std::uint64_t>::max() - 4096ULL) /
             128ULL)
                ? std::numeric_limits<std::uint64_t>::max()
                : (pTrialsPerHeart * 128ULL) + 4096ULL;

        while ((aValidTrials < pTrialsPerHeart) &&
               (aRawAttempts < aMaximumAttempts)) {
            ++aRawAttempts;
            LoopHeadPattern11 aHead;
            aHead.mWandererForOrbiter = IdentityRoles();
            Shuffle(&aHead.mWandererForOrbiter, &aGenerator);
            aHead.mPermutationRank = LoopHeadFarmer::Rank(aHead);
            if (!LoopHeadFarmer::IsValid(aHead)) {
                SetError(pErrorMessage,
                         "Random metric table generated an invalid head");
                return false;
            }

            const std::size_t aPatternIndex = aGenerator.Below(
                LoopHeadFarmer::kRetainedPatternCount);
            const PairInfoMatrix aPairs = MakePairInfo(
                aHeart.mHeart,
                aHead,
                aPatternIndex,
                aDistances);
            LoopTailPattern11 aTail;
            if (!GenerateTail(aPairs, &aGenerator, &aTail)) {
                continue;
            }
            Candidate aCandidate;
            if (!EvaluateAscendencyCandidate(
                    aHeart,
                    aHead,
                    aPatternIndex,
                    aPairs,
                    aTail,
                    &aCandidate)) {
                continue;
            }

            aShard << aHeartIndex << "," << aValidTrials << ","
                   << aPatternIndex << "," << aHead.mPermutationRank
                   << "," << aRawAttempts;
            for (const std::uint8_t aRole :
                 aHead.mWandererForOrbiter) {
                aShard << "," << static_cast<unsigned>(aRole);
            }
            for (const std::uint8_t aRole :
                 aTail.mOrbiterAForWanderer) {
                aShard << "," << static_cast<unsigned>(aRole);
            }
            for (const std::uint8_t aRole :
                 aTail.mOrbiterBForWanderer) {
                aShard << "," << static_cast<unsigned>(aRole);
            }
            const MetricValues aValues =
                RankingDisplayValues(aCandidate.mScore);
            for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
                if (LoopPlanMinimums::ShouldRecordMetric(i)) {
                    aShard << "," << aValues[i];
                }
            }
            aShard << "\n";
            ++aValidTrials;
        }
        if (aValidTrials != pTrialsPerHeart) {
            SetError(pErrorMessage,
                     "Metric table exporter exhausted its attempt budget "
                     "for heart " + std::to_string(aHeartIndex));
            return false;
        }

        const std::string aText = aShard.str();
        const std::vector<std::uint8_t> aBytes(
            aText.begin(), aText.end());
        if (!SaveMetricTableShard(
                aShardPath, aBytes, pErrorMessage)) {
            return false;
        }
        std::printf("metric table completed heart %03zu/%03zu: "
                    "rows=%llu raw=%llu bytes=%zu\n",
                    aHeartIndex,
                    aLastHeart - 1U,
                    static_cast<unsigned long long>(aValidTrials),
                    static_cast<unsigned long long>(aRawAttempts),
                    aBytes.size());
    }

    const std::string aOutputPath = ResolvedPath(pOutputPath);
    const std::string aTemporaryOutputPath = aOutputPath + ".tmp";
    std::ofstream aOutput(aTemporaryOutputPath,
                          std::ios::binary | std::ios::trunc);
    if (!aOutput) {
        SetError(pErrorMessage,
                 "Metric table exporter could not open " +
                 aTemporaryOutputPath);
        return false;
    }
    aOutput.write(aHeader.data(),
                  static_cast<std::streamsize>(aHeader.size()));
    for (std::size_t aHeartIndex = pFirstHeartIndex;
         aHeartIndex < aLastHeart;
         ++aHeartIndex) {
        const std::string aShardPath = MetricTableShardPath(
            pCheckpointFolderPath, pTrialsPerHeart, aHeartIndex);
        bool aFound = false;
        std::vector<std::uint8_t> aBytes;
        if (!LoadValidMetricTableShard(
                aShardPath,
                aHeader,
                pTrialsPerHeart,
                &aFound,
                &aBytes,
                pErrorMessage) || !aFound) {
            if (pErrorMessage != nullptr && pErrorMessage->empty()) {
                *pErrorMessage =
                    "Metric table shard disappeared before joining: " +
                    aShardPath;
            }
            aOutput.close();
            return false;
        }
        const std::size_t aBodySize = aBytes.size() - aHeader.size();
        aOutput.write(
            reinterpret_cast<const char *>(
                aBytes.data() + aHeader.size()),
            static_cast<std::streamsize>(aBodySize));
        if (!aOutput) {
            SetError(pErrorMessage,
                     "Metric table exporter failed while joining " +
                     aShardPath);
            aOutput.close();
            return false;
        }
    }
    aOutput.close();
    if (!aOutput) {
        SetError(pErrorMessage,
                 "Metric table exporter could not finish " +
                 aTemporaryOutputPath);
        return false;
    }
    if (std::rename(aTemporaryOutputPath.c_str(),
                    aOutputPath.c_str()) != 0) {
        const std::string aReason = std::strerror(errno);
        SetError(pErrorMessage,
                 "Metric table exporter could not install " +
                 aOutputPath + ": " + aReason);
        return false;
    }

    const std::string aSchemaText = RandomMetricTableSchema();
    const std::vector<std::uint8_t> aSchemaBytes(
        aSchemaText.begin(), aSchemaText.end());
    if (!FileIO::Save(ResolvedPath(pSchemaPath), aSchemaBytes)) {
        SetError(pErrorMessage,
                 "Metric table exporter could not save schema " +
                 ResolvedPath(pSchemaPath));
        return false;
    }

    std::printf("Metric table saved %llu rows to %s\n",
                static_cast<unsigned long long>(
                    pTrialsPerHeart *
                    static_cast<std::uint64_t>(pHeartCount)),
                aOutputPath.c_str());
    return true;
}

bool LoopTailFarmer::SearchGoldRates(
    const std::string &pHeartPatternFolderPath,
    const std::string &pNormalizationFolderPath,
    const std::string &pOutputFolderPath,
    const std::uint64_t pTrialsPerHeart,
    const std::string &pHeartNameFilter,
    const std::size_t pRepeatCount,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pTrialsPerHeart < kGoldCandidateCount) ||
        (pTrialsPerHeart >
         static_cast<std::uint64_t>(
             std::numeric_limits<std::size_t>::max())) ||
        (pRepeatCount == 0U)) {
        SetError(pErrorMessage,
                 "Gold-rate search trial count was invalid");
        return false;
    }

    const std::filesystem::path aHeartFolder(
        ResolvedPath(pHeartPatternFolderPath));
    std::error_code aFolderError;
    if (!std::filesystem::is_directory(aHeartFolder, aFolderError) ||
        aFolderError) {
        SetError(pErrorMessage,
                 "Gold-rate heart folder was not readable: " +
                 aHeartFolder.generic_string());
        return false;
    }

    std::vector<std::filesystem::path> aAllHeartPaths;
    std::filesystem::directory_iterator aIterator(
        aHeartFolder,
        std::filesystem::directory_options::skip_permission_denied,
        aFolderError);
    const std::filesystem::directory_iterator aEnd;
    while (!aFolderError && (aIterator != aEnd)) {
        const std::filesystem::directory_entry aEntry = *aIterator;
        std::error_code aEntryError;
        if (aEntry.is_regular_file(aEntryError) && !aEntryError &&
            (aEntry.path().extension() == ".bin")) {
            aAllHeartPaths.push_back(aEntry.path());
        }
        aIterator.increment(aFolderError);
    }
    if (aFolderError) {
        SetError(pErrorMessage,
                 "Gold-rate heart folder enumeration failed: " +
                 aFolderError.message());
        return false;
    }
    std::sort(aAllHeartPaths.begin(), aAllHeartPaths.end(),
              [](const std::filesystem::path &pA,
                 const std::filesystem::path &pB) {
        const auto aGroup = [](const std::string &pName) {
            if (pName.rfind("gold_heart_", 0U) == 0U) {
                return 0;
            }
            if (pName.rfind("silver_heart_", 0U) == 0U) {
                return 1;
            }
            if (pName.rfind("old_heart_", 0U) == 0U) {
                return 2;
            }
            return 3;
        };
        const std::string aName = pA.stem().generic_string();
        const std::string bName = pB.stem().generic_string();
        const int aGroupIndex = aGroup(aName);
        const int bGroupIndex = aGroup(bName);
        return aGroupIndex != bGroupIndex
            ? aGroupIndex < bGroupIndex
            : aName < bName;
    });
    if (aAllHeartPaths.empty()) {
        SetError(pErrorMessage,
                 "Gold-rate heart folder contained no .bin files: " +
                 aHeartFolder.generic_string());
        return false;
    }

    std::vector<std::filesystem::path> aHeartPaths;
    for (const std::filesystem::path &aHeartPath : aAllHeartPaths) {
        if (pHeartNameFilter.empty() ||
            (aHeartPath.stem().generic_string() == pHeartNameFilter)) {
            aHeartPaths.push_back(aHeartPath);
        }
    }
    if (aHeartPaths.empty()) {
        SetError(pErrorMessage,
                 "Gold-rate heart folder did not contain " +
                 pHeartNameFilter + ".bin");
        return false;
    }

    LoopCorePatternFile11 aHeartPatterns;
    std::vector<std::string> aHeartNames;
    const std::size_t aEffectiveRepeatCount =
        pHeartNameFilter.empty() ? 1U : pRepeatCount;
    aHeartPatterns.mPatterns.reserve(
        aHeartPaths.size() * aEffectiveRepeatCount);
    aHeartNames.reserve(aHeartPaths.size() * aEffectiveRepeatCount);
    for (const std::filesystem::path &aHeartPath : aHeartPaths) {
        LoopCorePatternFile11 aLoaded;
        if (!LoopCorePatternFarmer::Load(
                aHeartPath.generic_string(), &aLoaded, pErrorMessage)) {
            return false;
        }
        if (aLoaded.mPatterns.size() != 1U) {
            SetError(pErrorMessage,
                     "Gold-rate heart file did not contain exactly one "
                     "heart: " + aHeartPath.generic_string());
            return false;
        }
        const std::string aHeartName =
            aHeartPath.stem().generic_string();
        for (std::size_t aRepeatIndex = 0U;
             aRepeatIndex < aEffectiveRepeatCount;
             ++aRepeatIndex) {
            aHeartPatterns.mPatterns.push_back(aLoaded.mPatterns.front());
            if (aEffectiveRepeatCount == 1U) {
                aHeartNames.push_back(aHeartName);
            } else {
                char aRepeatSuffix[32];
                std::snprintf(aRepeatSuffix, sizeof(aRepeatSuffix),
                              "_run_%02zu", aRepeatIndex + 1U);
                aHeartNames.push_back(aHeartName + aRepeatSuffix);
            }
        }
    }

    std::error_code aDirectoryError;
    std::filesystem::create_directories(
        ResolvedPath(pOutputFolderPath), aDirectoryError);
    if (aDirectoryError) {
        SetError(pErrorMessage,
                 "Gold-rate search could not create its output folder: " +
                 aDirectoryError.message());
        return false;
    }

    const std::uint64_t aWeightSignature = GoldWeightSignature();
    MetricValues aUniversalMinimums{};
    MetricValues aUniversalMaximums{};
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        if (LoopWeights::IsEnabled(i)) {
            aUniversalMinimums[i] = std::numeric_limits<int>::max();
            aUniversalMaximums[i] = std::numeric_limits<int>::min();
        }
    }
    for (const std::filesystem::path &aHeartPath : aAllHeartPaths) {
        LoopCorePatternFile11 aLoaded;
        if (!LoopCorePatternFarmer::Load(
                aHeartPath.generic_string(), &aLoaded, pErrorMessage)) {
            return false;
        }
        if (aLoaded.mPatterns.size() != 1U) {
            SetError(pErrorMessage,
                     "Universal normalization heart file did not contain "
                     "exactly one heart: " +
                     aHeartPath.generic_string());
            return false;
        }
        MetricValues aHeartMinimums{};
        MetricValues aHeartMaximums{};
        const std::string aRangePath = GoldStatsPath(
            pNormalizationFolderPath,
            0U,
            aHeartPath.stem().generic_string());
        if (!LoadGoldRangeForUniversalNormalization(
                aRangePath,
                pTrialsPerHeart,
                GoldHeartSignature(aLoaded.mPatterns.front()),
                aWeightSignature,
                &aHeartMinimums,
                &aHeartMaximums,
                pErrorMessage)) {
            return false;
        }
        for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
            if (!LoopWeights::IsEnabled(i)) {
                continue;
            }
            aUniversalMinimums[i] = std::min(
                aUniversalMinimums[i], aHeartMinimums[i]);
            aUniversalMaximums[i] = std::max(
                aUniversalMaximums[i], aHeartMaximums[i]);
        }
    }
    std::printf("\nLOOP GOLD-RATE SEARCH\n"
                "folder=%s filter=%s repeats=%zu hearts=%zu "
                "trials/heart=%llu "
                "top=%zu normalization=universal output=%s\n\n",
                aHeartFolder.generic_string().c_str(),
                pHeartNameFilter.empty()
                    ? "<all>"
                    : pHeartNameFilter.c_str(),
                aEffectiveRepeatCount,
                aHeartPatterns.mPatterns.size(),
                static_cast<unsigned long long>(pTrialsPerHeart),
                kGoldCandidateCount,
                ResolvedPath(pOutputFolderPath).c_str());

    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < aHeartPatterns.mPatterns.size();
         ++aHeartIndex) {
        const LoopCorePattern11 &aCore =
            aHeartPatterns.mPatterns[aHeartIndex];
        const std::uint64_t aHeartSignature =
            GoldHeartSignature(aCore);
        const std::string aOutputPath = GoldStatsPath(
            pOutputFolderPath,
            aHeartIndex,
            aHeartNames[aHeartIndex]);
        if (GoldStatsFileMatches(
                aOutputPath,
                aHeartIndex,
                pTrialsPerHeart,
                aHeartSignature,
                aWeightSignature)) {
            std::printf("gold heart %03zu (%s) loaded; already complete\n",
                        aHeartIndex,
                        aHeartNames[aHeartIndex].c_str());
            continue;
        }

        LoopNewHeart11 aHeart;
        aHeart.mHeart = aCore;
        const DistanceMatrix aDistances =
            HeartTemporalDistances(aHeart.mHeart);
        Generator aGenerator(MixFarmSeed(
            0x474F4C4452415445ULL ^
            aHeartSignature ^
            ((static_cast<std::uint64_t>(aHeartIndex) + 1ULL) *
             0xD1342543DE82EF95ULL) ^
            pTrialsPerHeart));

        std::vector<GoldSearchCandidate> aCandidates;
        aCandidates.reserve(static_cast<std::size_t>(pTrialsPerHeart));
        std::unordered_set<std::string> aSeenRecipes;
        aSeenRecipes.reserve(static_cast<std::size_t>(
            pTrialsPerHeart + (pTrialsPerHeart / 4ULL)));
        std::uint64_t aRawAttempts = 0ULL;
        const std::uint64_t aMaximumAttempts = pTrialsPerHeart >
            ((std::numeric_limits<std::uint64_t>::max() - 4096ULL) /
             256ULL)
                ? std::numeric_limits<std::uint64_t>::max()
                : (pTrialsPerHeart * 256ULL) + 4096ULL;

        while ((aCandidates.size() < pTrialsPerHeart) &&
               (aRawAttempts < aMaximumAttempts)) {
            ++aRawAttempts;
            LoopHeadPattern11 aHead;
            aHead.mWandererForOrbiter = IdentityRoles();
            Shuffle(&aHead.mWandererForOrbiter, &aGenerator);
            aHead.mPermutationRank = LoopHeadFarmer::Rank(aHead);
            if (!LoopHeadFarmer::IsValid(aHead)) {
                SetError(pErrorMessage,
                         "Gold-rate search generated an invalid head");
                return false;
            }

            const std::size_t aPatternIndex = aGenerator.Below(
                LoopHeadFarmer::kRetainedPatternCount);
            const PairInfoMatrix aPairs = MakePairInfo(
                aHeart.mHeart,
                aHead,
                aPatternIndex,
                aDistances);
            LoopTailPattern11 aTail;
            if (!GenerateTail(aPairs, &aGenerator, &aTail)) {
                continue;
            }
            Candidate aEvaluated;
            if (!EvaluateAscendencyCandidate(
                    aHeart,
                    aHead,
                    aPatternIndex,
                    aPairs,
                    aTail,
                    &aEvaluated,
                    true)) {
                continue;
            }

            std::string aRecipeKey = GoldRecipeKey(
                aHead, aPatternIndex, aTail);
            if (!aSeenRecipes.insert(std::move(aRecipeKey)).second) {
                continue;
            }

            GoldSearchCandidate aCandidate;
            aCandidate.mHead = aHead;
            aCandidate.mTail = aTail;
            aCandidate.mPatternIndex = aPatternIndex;
            aCandidate.mValues = RankingDisplayValues(
                aEvaluated.mScore);
            aCandidates.push_back(std::move(aCandidate));

            if ((aCandidates.size() % 10'000U) == 0U) {
                std::printf("gold heart %03zu: valid=%zu/%llu raw=%llu\n",
                            aHeartIndex,
                            aCandidates.size(),
                            static_cast<unsigned long long>(
                                pTrialsPerHeart),
                            static_cast<unsigned long long>(
                                aRawAttempts));
            }
        }
        if (aCandidates.size() != pTrialsPerHeart) {
            SetError(pErrorMessage,
                     "Gold-rate search exhausted its attempt budget for "
                     "heart " + std::to_string(aHeartIndex));
            return false;
        }

        std::array<RankedGoldCandidate, kGoldCandidateCount> aTop{};
        std::size_t aTopCount = 0U;
        for (std::size_t i = 0U; i < aCandidates.size(); ++i) {
            const RankedGoldCandidate aRanked = {
                i,
                LoopWeights::Score(
                    aCandidates[i].mValues,
                    aUniversalMinimums,
                    aUniversalMaximums),
            };
            std::size_t aInsertIndex = 0U;
            while ((aInsertIndex < aTopCount) &&
                   !GoldCandidateIsBetter(
                       aRanked, aTop[aInsertIndex], aCandidates)) {
                ++aInsertIndex;
            }
            if (aInsertIndex >= kGoldCandidateCount) {
                continue;
            }
            const std::size_t aShiftEnd = std::min(
                aTopCount, kGoldCandidateCount - 1U);
            for (std::size_t aShift = aShiftEnd;
                 aShift > aInsertIndex;
                 --aShift) {
                aTop[aShift] = aTop[aShift - 1U];
            }
            aTop[aInsertIndex] = aRanked;
            aTopCount = std::min(
                aTopCount + 1U, kGoldCandidateCount);
        }
        if (aTopCount != kGoldCandidateCount) {
            SetError(pErrorMessage,
                     "Gold-rate search did not select three candidates");
            return false;
        }

        std::array<std::uint32_t, kScoreFieldCount> aGoldPercents{};
        for (std::size_t aMetric = 0U;
             aMetric < kScoreFieldCount;
             ++aMetric) {
            if (!LoopWeights::IsEnabled(aMetric)) {
                continue;
            }
            double aGoldPercent = 1.0;
            for (const RankedGoldCandidate &aRanked : aTop) {
                aGoldPercent = std::min(
                    aGoldPercent,
                    LoopWeights::Percent(
                        aCandidates[aRanked.mCandidateIndex]
                            .mValues[aMetric],
                        aUniversalMinimums[aMetric],
                        aUniversalMaximums[aMetric],
                        LoopWeights::kMetrics[aMetric]
                            .mHigherIsBetter));
            }
            aGoldPercents[aMetric] = GoldPercentFixed(aGoldPercent);
        }

        if (!SaveGoldStats(
                aOutputPath,
                aHeartIndex,
                pTrialsPerHeart,
                aRawAttempts,
                aHeartSignature,
                aWeightSignature,
                aUniversalMinimums,
                aUniversalMaximums,
                aGoldPercents,
                aTop,
                aCandidates,
                pErrorMessage)) {
            return false;
        }
        if (!GoldStatsFileMatches(
                aOutputPath,
                aHeartIndex,
                pTrialsPerHeart,
                aHeartSignature,
                aWeightSignature)) {
            SetError(pErrorMessage,
                     "Gold-rate search could not verify " + aOutputPath);
            return false;
        }

        std::printf(
            "gold heart %03zu (%s) complete: raw=%llu "
            "scores={%.6f, %.6f, %.6f} score_sum=%.6f "
            "gold_floor_score=%.6f saved=%s\n",
            aHeartIndex,
            aHeartNames[aHeartIndex].c_str(),
            static_cast<unsigned long long>(aRawAttempts),
            (100.0 * aTop[0].mScore) /
                static_cast<double>(LoopWeights::WeightTotal()),
            (100.0 * aTop[1].mScore) /
                static_cast<double>(LoopWeights::WeightTotal()),
            (100.0 * aTop[2].mScore) /
                static_cast<double>(LoopWeights::WeightTotal()),
            (100.0 * (aTop[0].mScore + aTop[1].mScore +
                      aTop[2].mScore)) /
                static_cast<double>(LoopWeights::WeightTotal()),
            static_cast<double>(GoldFloorScore(aGoldPercents)) *
                (100.0 / static_cast<double>(kGoldPercentScale)),
            aOutputPath.c_str());

    }

    return SaveGoldHeartQualitySummary(
        pOutputFolderPath,
        aHeartPatterns,
        aHeartNames,
        pTrialsPerHeart,
        aWeightSignature,
        "loaded_universal_range",
        true,
        pErrorMessage);
}

bool LoopTailFarmer::SearchCoreGoldRates(
    const std::string &pHeartPatternPath,
    const std::string &pOutputFolderPath,
    const std::uint64_t pTrialsPerHeart,
    const std::uint64_t pProgressInterval,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if (pTrialsPerHeart < kGoldCandidateCount) {
        SetError(pErrorMessage,
                 "Core gold search trial count was invalid");
        return false;
    }

    LoopCorePatternFile11 aHeartPatterns;
    if (!LoopCorePatternFarmer::Load(
            pHeartPatternPath, &aHeartPatterns, pErrorMessage)) {
        return false;
    }
    if (aHeartPatterns.mPatterns.size() !=
        LoopHeadFarmer::kCoreCount) {
        SetError(pErrorMessage,
                 "Core gold search did not load exactly 180 hearts");
        return false;
    }

    std::error_code aDirectoryError;
    std::filesystem::create_directories(
        ResolvedPath(pOutputFolderPath), aDirectoryError);
    if (aDirectoryError) {
        SetError(pErrorMessage,
                 "Core gold search could not create its output folder: " +
                 aDirectoryError.message());
        return false;
    }

    const std::uint64_t aWeightSignature = GoldWeightSignature();
    MetricValues aScoringMinimums{};
    MetricValues aScoringMaximums{};
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        aScoringMinimums[i] = LoopScorer::kMeasures[i].mMinimum;
        aScoringMaximums[i] = LoopScorer::kMeasures[i].mMaximum;
    }

    std::ostringstream aRangeCsv;
    aRangeCsv << "metric_index,metric_name,direction,weight,"
                 "scoring_minimum,scoring_maximum\n";
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        const LoopScorer::Measure &aMeasure =
            LoopScorer::kMeasures[i];
        if (aMeasure.mWeight == 0.0F) {
            continue;
        }
        aRangeCsv << i << "," << LoopWeights::kMetrics[i].mName << ","
                  << (aMeasure.mHigherIsBetter
                          ? "higher"
                          : "lower")
                  << "," << aMeasure.mWeight << ","
                  << aScoringMinimums[i] << ","
                  << aScoringMaximums[i] << "\n";
    }
    const std::string aRangeOutputPath = (
        std::filesystem::path(ResolvedPath(pOutputFolderPath)) /
        "universal_metric_ranges.csv").lexically_normal().generic_string();
    const std::string aRangeText = aRangeCsv.str();
    const std::vector<std::uint8_t> aRangeBytes(
        aRangeText.begin(), aRangeText.end());
    if (!FileIO::Save(aRangeOutputPath, aRangeBytes)) {
        SetError(pErrorMessage,
                 "Core gold search could not save " + aRangeOutputPath);
        return false;
    }

    std::uint64_t aScoringSignature = aWeightSignature;
    for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
        for (unsigned aByte = 0U; aByte < sizeof(std::uint32_t);
             ++aByte) {
            aScoringSignature = GoldHashByte(
                aScoringSignature,
                static_cast<std::uint8_t>(
                    static_cast<std::uint32_t>(aScoringMinimums[i]) >>
                    (aByte * 8U)));
            aScoringSignature = GoldHashByte(
                aScoringSignature,
                static_cast<std::uint8_t>(
                    static_cast<std::uint32_t>(aScoringMaximums[i]) >>
                    (aByte * 8U)));
        }
    }

    struct RetainedCandidate {
        GoldSearchCandidate mCandidate;
        int mScore = 0;
    };
    const auto CandidateIsBetter = [](
        const RetainedCandidate &pA,
        const RetainedCandidate &pB) {
        if (pA.mScore != pB.mScore) {
            return pA.mScore > pB.mScore;
        }
        if (pA.mCandidate.mHead.mPermutationRank !=
            pB.mCandidate.mHead.mPermutationRank) {
            return pA.mCandidate.mHead.mPermutationRank <
                pB.mCandidate.mHead.mPermutationRank;
        }
        if (pA.mCandidate.mPatternIndex !=
            pB.mCandidate.mPatternIndex) {
            return pA.mCandidate.mPatternIndex <
                pB.mCandidate.mPatternIndex;
        }
        if (pA.mCandidate.mTail.mOrbiterAForWanderer !=
            pB.mCandidate.mTail.mOrbiterAForWanderer) {
            return pA.mCandidate.mTail.mOrbiterAForWanderer <
                pB.mCandidate.mTail.mOrbiterAForWanderer;
        }
        return pA.mCandidate.mTail.mOrbiterBForWanderer <
            pB.mCandidate.mTail.mOrbiterBForWanderer;
    };

    std::printf("\nCORE GOLD SEARCH\n"
                "hearts=%zu trials/heart=%llu total=%llu\n"
                "normalization=floor(min * 0.9), ceil(max * 1.25) from "
                "%zu hearts and %llu trials\n"
                "ranges=%s\n\n",
                aHeartPatterns.mPatterns.size(),
                static_cast<unsigned long long>(pTrialsPerHeart),
                static_cast<unsigned long long>(
                    pTrialsPerHeart *
                    static_cast<std::uint64_t>(
                        aHeartPatterns.mPatterns.size())),
                LoopExtremeMeasures::kSourceHeartCount,
                static_cast<unsigned long long>(
                    LoopExtremeMeasures::kTotalTrials),
                aRangeOutputPath.c_str());

    std::vector<std::string> aHeartNames;
    aHeartNames.reserve(aHeartPatterns.mPatterns.size());
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < aHeartPatterns.mPatterns.size();
         ++aHeartIndex) {
        char aHeartName[32];
        std::snprintf(aHeartName, sizeof(aHeartName),
                      "heart_%03zu", aHeartIndex);
        aHeartNames.emplace_back(aHeartName);

        const LoopCorePattern11 &aCore =
            aHeartPatterns.mPatterns[aHeartIndex];
        const std::uint64_t aHeartSignature =
            GoldHeartSignature(aCore);
        const std::string aOutputPath = GoldStatsPath(
            pOutputFolderPath, aHeartIndex);
        if (GoldStatsFileMatches(
                aOutputPath,
                aHeartIndex,
                pTrialsPerHeart,
                aHeartSignature,
                aScoringSignature)) {
            std::printf("score heart %03zu loaded; already complete\n",
                        aHeartIndex);
            continue;
        }

        std::vector<RetainedCandidate> aRetained;
        aRetained.reserve(kGoldCandidateCount + 1U);
        std::uint64_t aRawAttempts = 0ULL;
        if (!StreamCoreGoldCandidates(
                aCore,
                aHeartIndex,
                pTrialsPerHeart,
                pProgressInterval,
                "score",
                [&](const GoldSearchCandidate &pCandidate) {
                    const int aScore = LoopScorer::Score(
                        pCandidate.mValues);
                    if ((aRetained.size() == kGoldCandidateCount) &&
                        (aScore < aRetained.back().mScore)) {
                        return;
                    }
                    RetainedCandidate aCandidate;
                    aCandidate.mCandidate = pCandidate;
                    aCandidate.mScore = aScore;
                    for (const RetainedCandidate &aExisting : aRetained) {
                        if ((aExisting.mCandidate.mHead.mPermutationRank ==
                             aCandidate.mCandidate.mHead.mPermutationRank) &&
                            (aExisting.mCandidate.mPatternIndex ==
                             aCandidate.mCandidate.mPatternIndex) &&
                            (aExisting.mCandidate.mTail
                                 .mOrbiterAForWanderer ==
                             aCandidate.mCandidate.mTail
                                 .mOrbiterAForWanderer) &&
                            (aExisting.mCandidate.mTail
                                 .mOrbiterBForWanderer ==
                             aCandidate.mCandidate.mTail
                                 .mOrbiterBForWanderer)) {
                            return;
                        }
                    }
                    auto aInsert = aRetained.begin();
                    while ((aInsert != aRetained.end()) &&
                           !CandidateIsBetter(aCandidate, *aInsert)) {
                        ++aInsert;
                    }
                    aRetained.insert(aInsert, std::move(aCandidate));
                    if (aRetained.size() > kGoldCandidateCount) {
                        aRetained.pop_back();
                    }
                },
                &aRawAttempts,
                pErrorMessage)) {
            return false;
        }
        if (aRetained.size() != kGoldCandidateCount) {
            SetError(pErrorMessage,
                     "Core gold search did not retain three candidates for "
                     "heart " + std::to_string(aHeartIndex));
            return false;
        }

        std::vector<GoldSearchCandidate> aCandidates;
        aCandidates.reserve(kGoldCandidateCount);
        std::array<RankedGoldCandidate, kGoldCandidateCount> aTop{};
        for (std::size_t i = 0U; i < kGoldCandidateCount; ++i) {
            aCandidates.push_back(aRetained[i].mCandidate);
            aTop[i] = {
                i,
                static_cast<double>(aRetained[i].mScore),
            };
        }
        std::array<std::uint32_t, kScoreFieldCount> aGoldPercents{};
        for (std::size_t aMetric = 0U;
             aMetric < kScoreFieldCount;
             ++aMetric) {
            const LoopScorer::Measure &aMeasure =
                LoopScorer::kMeasures[aMetric];
            if (aMeasure.mWeight == 0.0F) {
                continue;
            }
            double aGoldPercent = 1.0;
            for (const RetainedCandidate &aCandidate : aRetained) {
                aGoldPercent = std::min(
                    aGoldPercent,
                    LoopWeights::Percent(
                        aCandidate.mCandidate.mValues[aMetric],
                        aScoringMinimums[aMetric],
                        aScoringMaximums[aMetric],
                        aMeasure.mHigherIsBetter));
            }
            aGoldPercents[aMetric] = GoldPercentFixed(aGoldPercent);
        }

        if (!SaveGoldStats(
                aOutputPath,
                aHeartIndex,
                pTrialsPerHeart,
                aRawAttempts,
                aHeartSignature,
                aScoringSignature,
                aScoringMinimums,
                aScoringMaximums,
                aGoldPercents,
                aTop,
                aCandidates,
                pErrorMessage)) {
            return false;
        }
        std::printf(
            "score heart %03zu complete: "
            "scores={%.6f, %.6f, %.6f} floor=%.6f saved=%s\n",
            aHeartIndex,
            (100.0 * aTop[0].mScore) /
                static_cast<double>(LoopScorer::kMaximumScore),
            (100.0 * aTop[1].mScore) /
                static_cast<double>(LoopScorer::kMaximumScore),
            (100.0 * aTop[2].mScore) /
                static_cast<double>(LoopScorer::kMaximumScore),
            static_cast<double>(GoldFloorScore(aGoldPercents)) *
                (100.0 / static_cast<double>(kGoldPercentScale)),
            aOutputPath.c_str());
    }

    return SaveGoldHeartQualitySummary(
        pOutputFolderPath,
        aHeartPatterns,
        aHeartNames,
        pTrialsPerHeart,
        aScoringSignature,
        "padded_20_heart_extrema",
        true,
        pErrorMessage);
}

bool LoopTailFarmer::SearchCoreTop40(
    const std::string &pHeartPatternPath,
    const std::string &pOutputFolderPath,
    const std::uint64_t pTrialsPerHeart,
    const std::uint64_t pProgressInterval,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if (pTrialsPerHeart < kTop40CandidateCount) {
        SetError(pErrorMessage,
                 "Top-40 search needs at least 40 trials per heart");
        return false;
    }

    LoopCorePatternFile11 aHeartPatterns;
    if (!LoopCorePatternFarmer::Load(
            pHeartPatternPath, &aHeartPatterns, pErrorMessage)) {
        return false;
    }
    if (aHeartPatterns.mPatterns.size() !=
        LoopHeadFarmer::kCoreCount) {
        SetError(pErrorMessage,
                 "Top-40 search did not load exactly 180 hearts");
        return false;
    }

    const std::string aOutputFolder = ResolvedPath(pOutputFolderPath);
    std::error_code aDirectoryError;
    std::filesystem::create_directories(aOutputFolder, aDirectoryError);
    if (aDirectoryError) {
        SetError(pErrorMessage,
                 "Top-40 search could not create its output folder: " +
                 aDirectoryError.message());
        return false;
    }

    const std::uint64_t aScoringSignature = Top40ScoringSignature();
    std::ostringstream aRanges;
    aRanges << "metric_index,metric_name,direction,weight,minimum,maximum\n";
    for (std::size_t i = 0U; i < LoopScorer::kMetricCount; ++i) {
        const LoopScorer::Measure &aMeasure = LoopScorer::kMeasures[i];
        aRanges << i << "," << LoopWeights::kMetrics[i].mName << ","
                << (aMeasure.mHigherIsBetter ? "higher" : "lower")
                << "," << aMeasure.mWeight << ","
                << aMeasure.mMinimum << "," << aMeasure.mMaximum << "\n";
    }
    const std::string aRangePath = (
        std::filesystem::path(aOutputFolder) / "scoring_ranges.csv")
        .lexically_normal().generic_string();
    if (!SaveTop40TextAtomically(
            aRangePath, aRanges.str(), pErrorMessage)) {
        return false;
    }

    std::printf("\nTOP-40 LITSUM\n"
                "hearts=%zu trials/heart=%llu total=%llu retain=%zu\n"
                "maximum recipe score=%d maximum heart score=%zu\n"
                "output=%s\n\n",
                aHeartPatterns.mPatterns.size(),
                static_cast<unsigned long long>(pTrialsPerHeart),
                static_cast<unsigned long long>(
                    pTrialsPerHeart *
                    static_cast<std::uint64_t>(
                        aHeartPatterns.mPatterns.size())),
                kTop40CandidateCount,
                LoopScorer::kMaximumScore,
                kTop40CandidateCount *
                    static_cast<std::size_t>(LoopScorer::kMaximumScore),
                aOutputFolder.c_str());

    std::vector<Top40HeartSummary> aSummaries;
    aSummaries.reserve(aHeartPatterns.mPatterns.size());
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < aHeartPatterns.mPatterns.size();
         ++aHeartIndex) {
        const LoopCorePattern11 &aCore =
            aHeartPatterns.mPatterns[aHeartIndex];
        const std::uint64_t aHeartSignature = GoldHeartSignature(aCore);
        const std::string aHeartPath = Top40HeartPath(
            pOutputFolderPath, aHeartIndex);

        Top40HeartSummary aSummary;
        if (LoadTop40HeartSummary(
                aHeartPath,
                aHeartIndex,
                pTrialsPerHeart,
                aHeartSignature,
                aScoringSignature,
                &aSummary)) {
            std::printf(
                "top40 heart %03zu loaded: sum=%llu best=%d floor=%d\n",
                aHeartIndex,
                static_cast<unsigned long long>(aSummary.mScoreSum),
                aSummary.mBestScore,
                aSummary.mWorstScore);
            aSummaries.push_back(std::move(aSummary));
            continue;
        }

        std::vector<Top40RetainedCandidate> aRetained;
        aRetained.reserve(kTop40CandidateCount + 1U);
        std::uint64_t aRawAttempts = 0ULL;
        if (!StreamCoreGoldCandidates(
                aCore,
                aHeartIndex,
                pTrialsPerHeart,
                pProgressInterval,
                "top40",
                [&](const GoldSearchCandidate &pCandidate) {
                    const int aScore = LoopScorer::Score(
                        pCandidate.mValues);
                    if ((aRetained.size() == kTop40CandidateCount) &&
                        (aScore < aRetained.back().mScore)) {
                        return;
                    }

                    Top40RetainedCandidate aCandidate;
                    aCandidate.mCandidate = pCandidate;
                    aCandidate.mScore = aScore;
                    if (Top40CandidateIsDuplicate(aCandidate, aRetained)) {
                        return;
                    }
                    auto aInsert = aRetained.begin();
                    while ((aInsert != aRetained.end()) &&
                           !Top40CandidateIsBetter(
                               aCandidate, *aInsert)) {
                        ++aInsert;
                    }
                    aRetained.insert(aInsert, std::move(aCandidate));
                    if (aRetained.size() > kTop40CandidateCount) {
                        aRetained.pop_back();
                    }
                },
                &aRawAttempts,
                pErrorMessage)) {
            return false;
        }
        if (aRetained.size() != kTop40CandidateCount) {
            SetError(pErrorMessage,
                     "Top-40 search did not retain 40 distinct candidates "
                     "for heart " + std::to_string(aHeartIndex));
            return false;
        }
        if (!SaveTop40Heart(
                aHeartPath,
                aHeartIndex,
                pTrialsPerHeart,
                aRawAttempts,
                aHeartSignature,
                aScoringSignature,
                aRetained,
                pErrorMessage)) {
            return false;
        }
        if (!LoadTop40HeartSummary(
                aHeartPath,
                aHeartIndex,
                pTrialsPerHeart,
                aHeartSignature,
                aScoringSignature,
                &aSummary)) {
            SetError(pErrorMessage,
                     "Top-40 search could not verify completed CSV " +
                     aHeartPath);
            return false;
        }
        std::printf(
            "top40 heart %03zu complete: sum=%llu best=%d floor=%d "
            "raw=%llu saved=%s\n",
            aHeartIndex,
            static_cast<unsigned long long>(aSummary.mScoreSum),
            aSummary.mBestScore,
            aSummary.mWorstScore,
            static_cast<unsigned long long>(aSummary.mRawAttempts),
            aHeartPath.c_str());
        aSummaries.push_back(std::move(aSummary));
    }

    std::sort(
        aSummaries.begin(),
        aSummaries.end(),
        [](const Top40HeartSummary &pA,
           const Top40HeartSummary &pB) {
            if (pA.mScoreSum != pB.mScoreSum) {
                return pA.mScoreSum > pB.mScoreSum;
            }
            if (pA.mWorstScore != pB.mWorstScore) {
                return pA.mWorstScore > pB.mWorstScore;
            }
            if (pA.mBestScore != pB.mBestScore) {
                return pA.mBestScore > pB.mBestScore;
            }
            return pA.mHeartIndex < pB.mHeartIndex;
        });

    std::ostringstream aSummaryCsv;
    aSummaryCsv << "rank,heart_index,top_40_sum,average_score,best_score,"
                   "worst_top_40_score,trials_per_heart,raw_attempts,"
                   "candidate_csv\n";
    aSummaryCsv << std::fixed << std::setprecision(6);
    for (std::size_t i = 0U; i < aSummaries.size(); ++i) {
        const Top40HeartSummary &aSummary = aSummaries[i];
        aSummaryCsv
            << (i + 1U) << "," << aSummary.mHeartIndex << ","
            << aSummary.mScoreSum << ","
            << (static_cast<double>(aSummary.mScoreSum) /
                static_cast<double>(kTop40CandidateCount))
            << "," << aSummary.mBestScore << ","
            << aSummary.mWorstScore << "," << aSummary.mTrials << ","
            << aSummary.mRawAttempts << ","
            << std::filesystem::path(aSummary.mPath).filename().string()
            << "\n";
    }
    const std::string aSummaryPath = (
        std::filesystem::path(aOutputFolder) / "heart_scores.csv")
        .lexically_normal().generic_string();
    if (!SaveTop40TextAtomically(
            aSummaryPath, aSummaryCsv.str(), pErrorMessage)) {
        return false;
    }

    std::printf("\nTOP-40 LITSUM COMPLETE\nsummary=%s\n",
                aSummaryPath.c_str());
    return true;
}

bool LoopTailFarmer::ExportMinimumFilteredMetricTable(
    const std::string &pHeartPatternPath,
    const std::string &pHeadPatternPath,
    const std::string &pCheckpointFolderPath,
    const std::string &pOutputPath,
    const std::string &pSchemaPath,
    const std::size_t pFirstHeartIndex,
    const std::size_t pHeartCount,
    const std::uint64_t pSpinsPerHeart,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pSpinsPerHeart == 0ULL) || (pHeartCount == 0U) ||
        (pFirstHeartIndex >= LoopHeadFarmer::kCoreCount) ||
        (pHeartCount >
            (LoopHeadFarmer::kCoreCount - pFirstHeartIndex))) {
        SetError(pErrorMessage,
                 "Loop plan minimum export range or count was invalid");
        return false;
    }

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pHeartPatternPath,
                             pHeadPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    const std::string aHeader = MetricTableHeader(true);
    const std::size_t aLastHeart = pFirstHeartIndex + pHeartCount;
    std::uint64_t aTotalPassing = 0ULL;
    std::printf("Loop plan minimum export: %llu spins/heart, %zu hearts, "
                "%llu total scored candidates\n",
                static_cast<unsigned long long>(pSpinsPerHeart),
                pHeartCount,
                static_cast<unsigned long long>(
                    pSpinsPerHeart *
                    static_cast<std::uint64_t>(pHeartCount)));

    for (std::size_t aHeartIndex = pFirstHeartIndex;
         aHeartIndex < aLastHeart;
         ++aHeartIndex) {
        const std::string aShardPath = MetricTableShardPath(
            pCheckpointFolderPath, pSpinsPerHeart, aHeartIndex);
        bool aFound = false;
        std::uint64_t aPassingRows = 0ULL;
        std::vector<std::uint8_t> aExistingBytes;
        if (!LoadValidFilteredMetricTableShard(
                aShardPath,
                aHeader,
                pSpinsPerHeart,
                &aFound,
                &aPassingRows,
                &aExistingBytes,
                pErrorMessage)) {
            return false;
        }
        if (aFound) {
            aTotalPassing += aPassingRows;
            const double aRate =
                (static_cast<double>(aPassingRows) * 100.0) /
                static_cast<double>(pSpinsPerHeart);
            std::printf("minimum filter heart %03zu/%03zu loaded: "
                        "passed=%llu/%llu (%.8f%%)\n",
                        aHeartIndex,
                        aLastHeart - 1U,
                        static_cast<unsigned long long>(aPassingRows),
                        static_cast<unsigned long long>(pSpinsPerHeart),
                        aRate);
            continue;
        }

        const LoopNewHeart11 &aHeart = aPatterns.mHearts[aHeartIndex];
        const DistanceMatrix aDistances =
            HeartTemporalDistances(aHeart.mHeart);
        std::vector<PairInfoMatrix> aPairPlans;
        aPairPlans.reserve(LoopHeadFarmer::kPatternsPerCore);
        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(aHeartIndex, aHeadIndex);
            aPairPlans.push_back(MakePairInfo(
                aHeart.mHeart,
                aHeart.mHeads[aHeadIndex].mHead,
                aPatternIndex,
                aDistances));
        }

        Generator aGenerator(MixFarmSeed(
            0x4D494E494D554D53ULL ^
            static_cast<std::uint64_t>(aHeartIndex)));
        std::vector<std::unordered_set<std::string>> aSeenByHead(
            LoopHeadFarmer::kPatternsPerCore);
        const std::size_t aExpectedRowsPerHead =
            static_cast<std::size_t>(
                (pSpinsPerHeart +
                 LoopHeadFarmer::kPatternsPerCore - 1ULL) /
                LoopHeadFarmer::kPatternsPerCore);
        for (auto &aSeen : aSeenByHead) {
            aSeen.reserve(aExpectedRowsPerHead + 1U);
        }

        std::ostringstream aShard;
        aShard << aHeader;
        std::uint64_t aTestedSpins = 0ULL;
        std::uint64_t aRawAttempts = 0ULL;
        aPassingRows = 0ULL;
        const std::uint64_t aMaximumAttempts = pSpinsPerHeart >
            ((std::numeric_limits<std::uint64_t>::max() - 4096ULL) /
             128ULL)
                ? std::numeric_limits<std::uint64_t>::max()
                : (pSpinsPerHeart * 128ULL) + 4096ULL;

        while ((aTestedSpins < pSpinsPerHeart) &&
               (aRawAttempts < aMaximumAttempts)) {
            ++aRawAttempts;
            const std::size_t aHeadIndex = static_cast<std::size_t>(
                aTestedSpins % LoopHeadFarmer::kPatternsPerCore);
            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(aHeartIndex, aHeadIndex);
            LoopTailPattern11 aTail;
            if (!GenerateTail(aPairPlans[aHeadIndex],
                              &aGenerator,
                              &aTail)) {
                continue;
            }
            const std::string aKey = TailKey(aTail);
            if (!aSeenByHead[aHeadIndex].insert(aKey).second) {
                continue;
            }
            Candidate aCandidate;
            if (!EvaluateAscendencyCandidate(
                    aHeart,
                    aHeart.mHeads[aHeadIndex].mHead,
                    aPatternIndex,
                    aPairPlans[aHeadIndex],
                    aTail,
                    &aCandidate)) {
                continue;
            }

            const MetricValues aValues =
                RankingDisplayValues(aCandidate.mScore);
            const std::uint64_t aTrialIndex = aTestedSpins;
            ++aTestedSpins;
            if (!LoopPlanMinimums::PassesUniversalMaxima(aValues)) {
                continue;
            }

            aShard << aHeartIndex << "," << aHeadIndex << ","
                   << aTrialIndex << "," << aPatternIndex << ","
                   << aRawAttempts;
            for (const std::uint8_t aRole :
                 aTail.mOrbiterAForWanderer) {
                aShard << "," << static_cast<unsigned>(aRole);
            }
            for (const std::uint8_t aRole :
                 aTail.mOrbiterBForWanderer) {
                aShard << "," << static_cast<unsigned>(aRole);
            }
            for (std::size_t i = 0U; i < kScoreFieldCount; ++i) {
                if (LoopPlanMinimums::ShouldRecordMetric(i)) {
                    aShard << "," << aValues[i];
                }
            }
            aShard << "\n";
            ++aPassingRows;
        }
        if (aTestedSpins != pSpinsPerHeart) {
            SetError(pErrorMessage,
                     "Loop plan minimum exporter exhausted its attempt "
                     "budget for heart " + std::to_string(aHeartIndex));
            return false;
        }

        const std::string aText = aShard.str();
        const std::vector<std::uint8_t> aBytes(
            aText.begin(), aText.end());
        if (!SaveMetricTableShard(
                aShardPath, aBytes, pErrorMessage)) {
            return false;
        }
        aTotalPassing += aPassingRows;
        const double aRate =
            (static_cast<double>(aPassingRows) * 100.0) /
            static_cast<double>(pSpinsPerHeart);
        std::printf("minimum filter heart %03zu/%03zu: "
                    "passed=%llu/%llu (%.8f%%) raw=%llu\n",
                    aHeartIndex,
                    aLastHeart - 1U,
                    static_cast<unsigned long long>(aPassingRows),
                    static_cast<unsigned long long>(pSpinsPerHeart),
                    aRate,
                    static_cast<unsigned long long>(aRawAttempts));
    }

    const std::string aOutputPath = ResolvedPath(pOutputPath);
    const std::string aTemporaryOutputPath = aOutputPath + ".tmp";
    std::ofstream aOutput(aTemporaryOutputPath,
                          std::ios::binary | std::ios::trunc);
    if (!aOutput) {
        SetError(pErrorMessage,
                 "Loop plan minimum exporter could not open " +
                 aTemporaryOutputPath);
        return false;
    }
    aOutput.write(aHeader.data(),
                  static_cast<std::streamsize>(aHeader.size()));
    for (std::size_t aHeartIndex = pFirstHeartIndex;
         aHeartIndex < aLastHeart;
         ++aHeartIndex) {
        const std::string aShardPath = MetricTableShardPath(
            pCheckpointFolderPath, pSpinsPerHeart, aHeartIndex);
        bool aFound = false;
        std::uint64_t aPassingRows = 0ULL;
        std::vector<std::uint8_t> aBytes;
        if (!LoadValidFilteredMetricTableShard(
                aShardPath,
                aHeader,
                pSpinsPerHeart,
                &aFound,
                &aPassingRows,
                &aBytes,
                pErrorMessage) || !aFound) {
            if (pErrorMessage != nullptr && pErrorMessage->empty()) {
                *pErrorMessage =
                    "Filtered metric table shard disappeared before "
                    "joining: " + aShardPath;
            }
            aOutput.close();
            return false;
        }
        aOutput.write(
            reinterpret_cast<const char *>(
                aBytes.data() + aHeader.size()),
            static_cast<std::streamsize>(
                aBytes.size() - aHeader.size()));
    }
    aOutput.close();
    if (!aOutput ||
        (std::rename(aTemporaryOutputPath.c_str(),
                     aOutputPath.c_str()) != 0)) {
        SetError(pErrorMessage,
                 "Loop plan minimum exporter could not install " +
                 aOutputPath);
        return false;
    }

    const std::string aSchemaText = MetricTableSchema(true);
    const std::vector<std::uint8_t> aSchemaBytes(
        aSchemaText.begin(), aSchemaText.end());
    if (!FileIO::Save(ResolvedPath(pSchemaPath), aSchemaBytes)) {
        SetError(pErrorMessage,
                 "Loop plan minimum exporter could not save schema " +
                 ResolvedPath(pSchemaPath));
        return false;
    }

    const std::uint64_t aTotalSpins = pSpinsPerHeart *
        static_cast<std::uint64_t>(pHeartCount);
    const double aTotalRate =
        (static_cast<double>(aTotalPassing) * 100.0) /
        static_cast<double>(aTotalSpins);
    std::printf("Loop plan minimum total: passed=%llu/%llu (%.10f%%) "
                "output=%s\n",
                static_cast<unsigned long long>(aTotalPassing),
                static_cast<unsigned long long>(aTotalSpins),
                aTotalRate,
                aOutputPath.c_str());
    return true;
}

bool LoopTailFarmer::AnalyzeCurrentRecipes(
    const std::string &pHeartPatternPath,
    const std::string &pHeadPatternPath,
    const std::string &pTailPatternPath,
    const std::string &pOutputPath,
    const bool pMeasureExactPairDistances,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pHeartPatternPath,
                             pHeadPatternPath,
                             pTailPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    constexpr std::size_t kMetricCount = kScoreFieldCount;
    constexpr std::size_t kRecipeCount =
        LoopHeadFarmer::kRetainedPatternCount;
    using MetricColumns =
        std::array<std::vector<int>, kMetricCount>;

    MetricColumns aGlobalValues;
    for (auto &aValues : aGlobalValues) {
        aValues.reserve(kRecipeCount);
    }
    std::array<MetricColumns, LoopHeadFarmer::kCoreCount>
        aPerHeartValues;

    std::vector<std::uint64_t> aPackedHeads;
    std::vector<PackedTail> aPackedTails;
    aPackedHeads.reserve(kRecipeCount);
    aPackedTails.reserve(kRecipeCount);

    std::size_t aRecipeIndex = 0U;
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < LoopHeadFarmer::kCoreCount;
         ++aHeartIndex) {
        const LoopNewHeart11 &aHeart =
            aPatterns.mHearts[aHeartIndex];
        const DistanceMatrix aDistances =
            HeartTemporalDistances(aHeart.mHeart);
        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            const LoopNewHead11 &aReady = aHeart.mHeads[aHeadIndex];
            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(
                    aHeartIndex, aHeadIndex);
            const PairInfoMatrix aPairs = MakePairInfo(
                aHeart.mHeart,
                aReady.mHead,
                aPatternIndex,
                aDistances);
            if (!TailUsesAllowedPairs(aReady.mTail, aPairs)) {
                SetError(pErrorMessage,
                         "Current loop recipe used a disallowed tail pair at recipe " +
                         std::to_string(aRecipeIndex));
                return false;
            }

            const TransitionMatrix aTransition =
                MakeTransitionMatrix(aReady.mHead, aReady.mTail);
            const TransitionMetrics aTransitionMetrics =
                MeasureTransition(aTransition, true);
            if (!aTransitionMetrics.mStronglyConnected) {
                SetError(pErrorMessage,
                         "Current loop recipe was not strongly connected at recipe " +
                         std::to_string(aRecipeIndex));
                return false;
            }

            TailScore aScore = ScoreTail(
                aHeart.mHeart,
                aReady.mHead,
                aReady.mTail,
                aPatternIndex,
                aPairs,
                aTransitionMetrics);
            const std::array<int, kMetricCount> aValues =
                RankingDisplayValues(aScore);
            for (std::size_t aMetric = 0U;
                 aMetric < kMetricCount;
                 ++aMetric) {
                aGlobalValues[aMetric].push_back(aValues[aMetric]);
                aPerHeartValues[aHeartIndex][aMetric].push_back(
                    aValues[aMetric]);
            }
            aPackedHeads.push_back(
                LoopHeadFarmer::PackedKey(aReady.mHead));
            aPackedTails.push_back(PackTail(aReady.mTail));
            ++aRecipeIndex;
        }
        std::printf("Current recipe audit scored heart %zu/%zu; "
                    "recipes=%zu/%zu\n",
                    aHeartIndex + 1U,
                    LoopHeadFarmer::kCoreCount,
                    aRecipeIndex,
                    kRecipeCount);
    }

    if (aRecipeIndex != kRecipeCount) {
        SetError(pErrorMessage,
                 "Current loop recipe audit did not measure exactly 19,800 recipes");
        return false;
    }

    std::array<DistributionSummary, kMetricCount> aGlobalSummary;
    for (std::size_t aMetric = 0U;
         aMetric < kMetricCount;
         ++aMetric) {
        aGlobalSummary[aMetric] =
            SummarizeValues(aGlobalValues[aMetric]);
    }

    std::ostringstream aReport;
    aReport << "CURRENT LOOP FLOW BASELINE\n"
            << "recipes=" << kRecipeCount
            << " hearts=" << LoopHeadFarmer::kCoreCount
            << " heads_per_heart="
            << LoopHeadFarmer::kPatternsPerCore << "\n"
            << "Quantiles use the sorted inclusive index "
               "floor((count - 1) * q).\n"
            << "This file measures the existing selected population; it "
               "does not yet declare final acceptance thresholds.\n\n";

    const auto AppendMetricHeader = [&aReport]() {
        aReport << "  " << std::left << std::setw(46) << "metric"
                << std::right << std::setw(7) << "min"
                << std::setw(7) << "p25"
                << std::setw(7) << "p50"
                << std::setw(7) << "p75"
                << std::setw(7) << "max"
                << std::setw(12) << "mean"
                << "  preference\n";
    };

    aReport << "GLOBAL METRIC QUARTILES\n";
    AppendMetricHeader();
    for (std::size_t aMetric = 0U;
         aMetric < kMetricCount;
         ++aMetric) {
        AppendDistributionRow(&aReport,
                              kRankingMetricNames[aMetric],
                              kRankingHigherIsBetter[aMetric],
                              aGlobalSummary[aMetric]);
    }

    std::array<std::size_t, kMetricCount> aDistinctCounts{};
    std::array<double, kMetricCount> aModeFractions{};
    std::array<double, kMetricCount> aEffectiveValueCounts{};
    std::array<int, kMetricCount> aMedianWithinHeartDistinct{};
    std::array<double, kMetricCount> aHeartVarianceFractions{};

    aReport << "\nGLOBAL METRIC CARDINALITY\n";
    for (std::size_t aMetric = 0U;
         aMetric < kMetricCount;
         ++aMetric) {
        std::vector<int> aSorted = aGlobalValues[aMetric];
        std::sort(aSorted.begin(), aSorted.end());
        std::size_t aDistinctCount = 0U;
        std::size_t aModeCount = 0U;
        double aEntropy = 0.0;
        std::size_t aBegin = 0U;
        while (aBegin < aSorted.size()) {
            std::size_t aEnd = aBegin + 1U;
            while ((aEnd < aSorted.size()) &&
                   (aSorted[aEnd] == aSorted[aBegin])) {
                ++aEnd;
            }
            const std::size_t aCount = aEnd - aBegin;
            const double aProbability = static_cast<double>(aCount) /
                static_cast<double>(aSorted.size());
            aEntropy -= aProbability * std::log(aProbability);
            aModeCount = std::max(aModeCount, aCount);
            ++aDistinctCount;
            aBegin = aEnd;
        }
        aDistinctCounts[aMetric] = aDistinctCount;
        aModeFractions[aMetric] = aSorted.empty()
            ? 1.0
            : static_cast<double>(aModeCount) /
                static_cast<double>(aSorted.size());
        aEffectiveValueCounts[aMetric] = std::exp(aEntropy);

        std::vector<int> aWithinHeartDistinct;
        aWithinHeartDistinct.reserve(LoopHeadFarmer::kCoreCount);
        double aBetweenHeartSquares = 0.0;
        for (std::size_t aHeart = 0U;
             aHeart < LoopHeadFarmer::kCoreCount;
             ++aHeart) {
            std::vector<int> aHeartValues =
                aPerHeartValues[aHeart][aMetric];
            std::sort(aHeartValues.begin(), aHeartValues.end());
            const auto aUniqueEnd = std::unique(
                aHeartValues.begin(), aHeartValues.end());
            aWithinHeartDistinct.push_back(static_cast<int>(
                std::distance(aHeartValues.begin(), aUniqueEnd)));

            const double aHeartTotal = std::accumulate(
                aPerHeartValues[aHeart][aMetric].begin(),
                aPerHeartValues[aHeart][aMetric].end(),
                0.0);
            const double aHeartMean = aHeartTotal /
                static_cast<double>(
                    aPerHeartValues[aHeart][aMetric].size());
            const double aDelta =
                aHeartMean - aGlobalSummary[aMetric].mMean;
            aBetweenHeartSquares += static_cast<double>(
                aPerHeartValues[aHeart][aMetric].size()) *
                aDelta * aDelta;
        }
        aMedianWithinHeartDistinct[aMetric] =
            SummarizeValues(aWithinHeartDistinct).mMedian;

        double aTotalSquares = 0.0;
        for (const int aValue : aGlobalValues[aMetric]) {
            const double aDelta = static_cast<double>(aValue) -
                aGlobalSummary[aMetric].mMean;
            aTotalSquares += aDelta * aDelta;
        }
        aHeartVarianceFractions[aMetric] = aTotalSquares > 0.0
            ? aBetweenHeartSquares / aTotalSquares
            : 0.0;

        aReport << "  " << std::left << std::setw(46)
                << kRankingMetricNames[aMetric]
                << std::right << aDistinctCounts[aMetric]
                << " distinct values\n";
    }

    struct CorrelationPair {
        std::size_t mA = 0U;
        std::size_t mB = 0U;
        double mCorrelation = 0.0;
    };
    std::array<std::vector<double>, kMetricCount> aMetricRanks;
    for (std::size_t aMetric = 0U;
         aMetric < kMetricCount;
         ++aMetric) {
        aMetricRanks[aMetric] = AverageRanks(aGlobalValues[aMetric]);
    }
    std::vector<CorrelationPair> aCorrelations;
    std::array<double, kMetricCount> aMaximumAbsoluteCorrelations{};
    for (std::size_t a = 0U; a < kMetricCount; ++a) {
        if (aGlobalSummary[a].mMinimum == aGlobalSummary[a].mMaximum) {
            continue;
        }
        for (std::size_t b = a + 1U; b < kMetricCount; ++b) {
            if (aGlobalSummary[b].mMinimum ==
                aGlobalSummary[b].mMaximum) {
                continue;
            }
            const double aCorrelation = PearsonCorrelation(
                aMetricRanks[a], aMetricRanks[b]);
            const double aAbsoluteCorrelation =
                std::fabs(aCorrelation);
            aMaximumAbsoluteCorrelations[a] = std::max(
                aMaximumAbsoluteCorrelations[a],
                aAbsoluteCorrelation);
            aMaximumAbsoluteCorrelations[b] = std::max(
                aMaximumAbsoluteCorrelations[b],
                aAbsoluteCorrelation);
            if (aAbsoluteCorrelation >= 0.75) {
                aCorrelations.push_back({a, b, aCorrelation});
            }
        }
    }
    std::sort(aCorrelations.begin(), aCorrelations.end(),
              [](const CorrelationPair &pA,
                 const CorrelationPair &pB) {
                  return std::fabs(pA.mCorrelation) >
                      std::fabs(pB.mCorrelation);
              });
    aReport << "\nSTRONG SPEARMAN CORRELATIONS (absolute rho >= 0.75)\n"
            << "High absolute correlation means the pair should normally "
               "not receive two independent hard thresholds.\n";
    if (aCorrelations.empty()) {
        aReport << "  none\n";
    }
    for (const CorrelationPair &aPair : aCorrelations) {
        aReport << "  " << std::left << std::setw(44)
                << kRankingMetricNames[aPair.mA]
                << " <-> " << std::setw(44)
                << kRankingMetricNames[aPair.mB]
                << std::right << " rho=" << std::fixed
                << std::setprecision(3) << aPair.mCorrelation << "\n";
    }

    aReport << "\nMETRIC UTILITY DIAGNOSTICS\n"
            << "These describe statistical usefulness, not cryptographic "
               "strength. Mode is the largest tie group; effective values "
               "is exp(Shannon entropy); within-heart is the median number "
               "of values among one heart's 110 recipes; heart share is "
               "the fraction of variance explained by heart identity.\n"
            << "  " << std::left << std::setw(46) << "metric"
            << std::right << std::setw(8) << "distinct"
            << std::setw(9) << "mode%"
            << std::setw(11) << "eff vals"
            << std::setw(11) << "within p50"
            << std::setw(12) << "heart share"
            << std::setw(11) << "max |rho|" << "\n";
    for (std::size_t aMetric = 0U;
         aMetric < kMetricCount;
         ++aMetric) {
        aReport << "  " << std::left << std::setw(46)
                << kRankingMetricNames[aMetric]
                << std::right << std::setw(8)
                << aDistinctCounts[aMetric]
                << std::setw(8) << std::fixed << std::setprecision(1)
                << (aModeFractions[aMetric] * 100.0) << "%"
                << std::setw(11) << std::setprecision(2)
                << aEffectiveValueCounts[aMetric]
                << std::setw(11)
                << aMedianWithinHeartDistinct[aMetric]
                << std::setw(12) << std::setprecision(3)
                << aHeartVarianceFractions[aMetric]
                << std::setw(11)
                << aMaximumAbsoluteCorrelations[aMetric]
                << "\n";
    }

    aReport << "\nPERCENTILE-RANK THRESHOLD VALUES\n"
            << "Top 80% means percentile rank 80 or better: raw p80 for "
               "higher-is-better metrics and raw p20 for lower-is-better "
               "metrics. The most-important metric uses percentile rank "
               "95 or better. Ties can retain more than the nominal share.\n"
            << "  " << std::left << std::setw(46) << "metric"
            << std::right << std::setw(12) << "rank"
            << std::setw(14) << "threshold"
            << "  comparison\n";
    constexpr std::size_t kMostImportantMetric = 29U;
    for (std::size_t aMetric = 0U;
         aMetric < kMetricCount;
         ++aMetric) {
        const std::size_t aRank =
            aMetric == kMostImportantMetric ? 95U : 80U;
        const std::size_t aRawPercentile =
            kRankingHigherIsBetter[aMetric]
                ? aRank
                : 100U - aRank;
        const int aThreshold = PercentileValue(
            aGlobalValues[aMetric], aRawPercentile);
        aReport << "  " << std::left << std::setw(46)
                << kRankingMetricNames[aMetric]
                << std::right << std::setw(11) << aRank << "%"
                << std::setw(14) << aThreshold
                << "  "
                << (kRankingHigherIsBetter[aMetric] ? ">=" : "<=")
                << "\n";
    }

    MetricColumns aHeartWorstValues;
    MetricColumns aHeartMedianValues;
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < LoopHeadFarmer::kCoreCount;
         ++aHeartIndex) {
        for (std::size_t aMetric = 0U;
             aMetric < kMetricCount;
             ++aMetric) {
            const DistributionSummary aSummary = SummarizeValues(
                aPerHeartValues[aHeartIndex][aMetric]);
            aHeartWorstValues[aMetric].push_back(
                kRankingHigherIsBetter[aMetric]
                    ? aSummary.mMinimum
                    : aSummary.mMaximum);
            aHeartMedianValues[aMetric].push_back(aSummary.mMedian);
        }
    }

    aReport << "\nDISTRIBUTION OF PER-HEART WORST VALUES\n"
            << "Each sample is the weakest of the 110 recipes assigned to "
               "one heart.\n";
    AppendMetricHeader();
    for (std::size_t aMetric = 0U;
         aMetric < kMetricCount;
         ++aMetric) {
        AppendDistributionRow(
            &aReport,
            kRankingMetricNames[aMetric],
            kRankingHigherIsBetter[aMetric],
            SummarizeValues(aHeartWorstValues[aMetric]));
    }

    aReport << "\nDISTRIBUTION OF PER-HEART MEDIANS\n"
            << "Each sample is the median of the 110 recipes assigned to "
               "one heart.\n";
    AppendMetricHeader();
    for (std::size_t aMetric = 0U;
         aMetric < kMetricCount;
         ++aMetric) {
        AppendDistributionRow(
            &aReport,
            kRankingMetricNames[aMetric],
            kRankingHigherIsBetter[aMetric],
            SummarizeValues(aHeartMedianValues[aMetric]));
    }

    const auto CountJointSurvivors = [
        &aGlobalValues,
        &aGlobalSummary](
            const std::vector<std::size_t> &pMetricIndices,
            const int pStrength,
            std::array<std::size_t,
                       LoopHeadFarmer::kCoreCount> *pPerHeart) {
        pPerHeart->fill(0U);
        std::size_t aSurvivors = 0U;
        for (std::size_t aRecipe = 0U;
             aRecipe < kRecipeCount;
             ++aRecipe) {
            bool aPasses = true;
            for (const std::size_t aMetric : pMetricIndices) {
                const DistributionSummary &aSummary =
                    aGlobalSummary[aMetric];
                int aThreshold = aSummary.mMedian;
                if (pStrength == 0) {
                    aThreshold = kRankingHigherIsBetter[aMetric]
                        ? aSummary.mP25 : aSummary.mP75;
                } else if (pStrength == 2) {
                    aThreshold = kRankingHigherIsBetter[aMetric]
                        ? aSummary.mP75 : aSummary.mP25;
                }
                const int aValue = aGlobalValues[aMetric][aRecipe];
                aPasses = kRankingHigherIsBetter[aMetric]
                    ? (aValue >= aThreshold)
                    : (aValue <= aThreshold);
                if (!aPasses) {
                    break;
                }
            }
            if (aPasses) {
                ++aSurvivors;
                ++(*pPerHeart)[
                    aRecipe / LoopHeadFarmer::kPatternsPerCore];
            }
        }
        return aSurvivors;
    };

    const std::vector<std::size_t> aSafeMetrics = {
        0U, 4U, 20U, 21U, 13U, 22U,
    };
    std::vector<std::size_t> aAllMetrics(kMetricCount);
    for (std::size_t i = 0U; i < kMetricCount; ++i) {
        aAllMetrics[i] = i;
    }

    const auto AppendJointSurvival = [
        &aReport,
        &CountJointSurvivors](
            const char *pLabel,
            const std::vector<std::size_t> &pMetrics) {
        aReport << "\n" << pLabel << "\n";
        constexpr std::array<const char *, 3U> kNames = {
            "inclusive quartile", "median", "strong quartile",
        };
        for (int aStrength = 0; aStrength < 3; ++aStrength) {
            std::array<std::size_t,
                       LoopHeadFarmer::kCoreCount> aPerHeart{};
            const std::size_t aSurvivors = CountJointSurvivors(
                pMetrics, aStrength, &aPerHeart);
            std::vector<int> aHeartCounts;
            aHeartCounts.reserve(aPerHeart.size());
            std::size_t aEmptyHearts = 0U;
            for (const std::size_t aCount : aPerHeart) {
                aHeartCounts.push_back(static_cast<int>(aCount));
                aEmptyHearts += aCount == 0U;
            }
            const DistributionSummary aHeartSummary =
                SummarizeValues(aHeartCounts);
            aReport << "  " << std::left << std::setw(20)
                    << kNames[static_cast<std::size_t>(aStrength)]
                    << std::right << " survivors=" << aSurvivors
                    << "/" << kRecipeCount
                    << " empty_hearts=" << aEmptyHearts
                    << " per_heart=" << aHeartSummary.mMinimum
                    << "/" << aHeartSummary.mP25
                    << "/" << aHeartSummary.mMedian
                    << "/" << aHeartSummary.mP75
                    << "/" << aHeartSummary.mMaximum
                    << " (min/p25/p50/p75/max)\n";
        }
    };

    aReport << "\nJOINT THRESHOLD SURVIVAL\n"
            << "Inclusive quartile keeps the better 75% side of each "
               "individual metric; strong quartile keeps the better 25% "
               "side. Joint survival is the intersection, not an expected "
               "fixed percentage.\n";
    AppendJointSurvival("CURRENT SIX-METRIC SAFE SET", aSafeMetrics);
    AppendJointSurvival("ALL METRICS", aAllMetrics);

    std::array<int, kMetricCount> aConfiguredThresholds{};
    for (std::size_t aMetric = 0U;
         aMetric < kMetricCount;
         ++aMetric) {
        const std::size_t aRank =
            aMetric == kMostImportantMetric ? 95U : 80U;
        const std::size_t aRawPercentile =
            kRankingHigherIsBetter[aMetric]
                ? aRank
                : 100U - aRank;
        aConfiguredThresholds[aMetric] = PercentileValue(
            aGlobalValues[aMetric], aRawPercentile);
    }
    std::array<std::size_t,
               LoopHeadFarmer::kCoreCount> aConfiguredPerHeart{};
    std::size_t aConfiguredSurvivors = 0U;
    for (std::size_t aRecipe = 0U;
         aRecipe < kRecipeCount;
         ++aRecipe) {
        bool aPasses = true;
        for (std::size_t aMetric = 0U;
             aMetric < kMetricCount;
             ++aMetric) {
            const int aValue = aGlobalValues[aMetric][aRecipe];
            aPasses = kRankingHigherIsBetter[aMetric]
                ? aValue >= aConfiguredThresholds[aMetric]
                : aValue <= aConfiguredThresholds[aMetric];
            if (!aPasses) {
                break;
            }
        }
        if (aPasses) {
            ++aConfiguredSurvivors;
            ++aConfiguredPerHeart[
                aRecipe / LoopHeadFarmer::kPatternsPerCore];
        }
    }
    std::vector<int> aConfiguredHeartCounts;
    std::size_t aConfiguredEmptyHearts = 0U;
    for (const std::size_t aCount : aConfiguredPerHeart) {
        aConfiguredHeartCounts.push_back(static_cast<int>(aCount));
        aConfiguredEmptyHearts += aCount == 0U;
    }
    const DistributionSummary aConfiguredHeartSummary =
        SummarizeValues(aConfiguredHeartCounts);
    aReport << "\nCONFIGURED 80/95 POLICY\n"
            << "  survivors=" << aConfiguredSurvivors
            << "/" << kRecipeCount
            << " empty_hearts=" << aConfiguredEmptyHearts
            << " per_heart=" << aConfiguredHeartSummary.mMinimum
            << "/" << aConfiguredHeartSummary.mP25
            << "/" << aConfiguredHeartSummary.mMedian
            << "/" << aConfiguredHeartSummary.mP75
            << "/" << aConfiguredHeartSummary.mMaximum
            << " (min/p25/p50/p75/max)\n";

    struct ThresholdRule {
        std::size_t mMetric = 0U;
        int mThreshold = 0;
    };
    const std::vector<ThresholdRule> aStructuralFloorPolicy = {
        {4U, 15},       // minimum pair union
        {6U, 33},       // total heart separation
        {8U, 1},        // minimum complement
        {9U, 8},        // dominated pair count
        {10U, 6142},    // flow area
        {14U, 3363},    // mean wanderer shortest path
        {15U, 3700},    // worst wanderer mean shortest path
        {17U, 8},       // minimum early reach
        {19U, 509},     // redundant early branches
        {21U, 307},     // minimum subset expansion
        {24U, 9},       // minimum one-round fanout
        {26U, 26},      // minimum source journey area
        {27U, 1},       // minimum dual-tail reach
        {28U, 572},     // mean dual-tail reach
        {29U, 224},     // maximum orbiter path load
        {30U, 75},      // maximum ordered source orphan area
        {33U, 3},       // maximum orphan straggler gap
        {34U, 8},       // maximum midpoint source orphans
        {35U, 7},       // maximum midpoint destination orphan load
        {36U, 6},       // maximum midpoint co-orphan load
        {37U, 0},       // maximum source meeting orphans
        {38U, 138},     // maximum source meeting area
        {39U, 11127},   // mean source-pair meeting latency
        {40U, 8},       // maximum robust orphans
        {41U, 5636},    // mean robust orphans
    };
    std::array<std::size_t,
               LoopHeadFarmer::kCoreCount> aFloorPerHeart{};
    std::vector<bool> aPassesStructuralFloors(kRecipeCount, false);
    std::size_t aFloorSurvivors = 0U;
    for (std::size_t aRecipe = 0U;
         aRecipe < kRecipeCount;
         ++aRecipe) {
        bool aPasses = true;
        for (const ThresholdRule &aRule : aStructuralFloorPolicy) {
            const int aValue =
                aGlobalValues[aRule.mMetric][aRecipe];
            aPasses = kRankingHigherIsBetter[aRule.mMetric]
                ? aValue >= aRule.mThreshold
                : aValue <= aRule.mThreshold;
            if (!aPasses) {
                break;
            }
        }
        if (aPasses) {
            aPassesStructuralFloors[aRecipe] = true;
            ++aFloorSurvivors;
            ++aFloorPerHeart[
                aRecipe / LoopHeadFarmer::kPatternsPerCore];
        }
    }
    std::vector<int> aFloorHeartCounts;
    std::size_t aFloorEmptyHearts = 0U;
    for (const std::size_t aCount : aFloorPerHeart) {
        aFloorHeartCounts.push_back(static_cast<int>(aCount));
        aFloorEmptyHearts += aCount == 0U;
    }
    const DistributionSummary aFloorHeartSummary =
        SummarizeValues(aFloorHeartCounts);
    aReport << "\nPROPOSED STRUCTURAL FLOOR POLICY\n"
            << "These are bottom-quality rejection floors, not a demand "
               "that every metric independently land in its top 20%. "
               "The weak one-round fanout floor is retained as an inverse-"
               "flow safety check, but it must not receive a second score "
               "weight beside minimum pair union.\n";
    for (const ThresholdRule &aRule : aStructuralFloorPolicy) {
        aReport << "  " << std::left << std::setw(46)
                << kRankingMetricNames[aRule.mMetric]
                << std::right
                << (kRankingHigherIsBetter[aRule.mMetric]
                        ? " >= " : " <= ")
                << aRule.mThreshold << "\n";
    }
    aReport << "  survivors=" << aFloorSurvivors
            << "/" << kRecipeCount
            << " empty_hearts=" << aFloorEmptyHearts
            << " per_heart=" << aFloorHeartSummary.mMinimum
            << "/" << aFloorHeartSummary.mP25
            << "/" << aFloorHeartSummary.mMedian
            << "/" << aFloorHeartSummary.mP75
            << "/" << aFloorHeartSummary.mMaximum
            << " (min/p25/p50/p75/max)\n";

    const std::vector<ThresholdRule> aPrimaryEvidencePolicy = {
        {19U, 554},     // redundant early-branch fraction, top 80%
        {29U, 209},     // maximum orbiter path load, top 95%
        {46U, 14},      // maximum single-orbiter damage, top 80%
    };
    std::size_t aPrimaryEvidenceSurvivors = 0U;
    std::size_t aPrimaryAndFloorSurvivors = 0U;
    std::array<std::size_t,
               LoopHeadFarmer::kCoreCount> aPrimaryPerHeart{};
    std::array<std::size_t,
               LoopHeadFarmer::kCoreCount> aPrimaryAndFloorPerHeart{};
    for (std::size_t aRecipe = 0U;
         aRecipe < kRecipeCount;
         ++aRecipe) {
        bool aPasses = true;
        for (const ThresholdRule &aRule : aPrimaryEvidencePolicy) {
            const int aValue =
                aGlobalValues[aRule.mMetric][aRecipe];
            aPasses = kRankingHigherIsBetter[aRule.mMetric]
                ? aValue >= aRule.mThreshold
                : aValue <= aRule.mThreshold;
            if (!aPasses) {
                break;
            }
        }
        if (!aPasses) {
            continue;
        }
        const std::size_t aHeart =
            aRecipe / LoopHeadFarmer::kPatternsPerCore;
        ++aPrimaryEvidenceSurvivors;
        ++aPrimaryPerHeart[aHeart];
        if (aPassesStructuralFloors[aRecipe]) {
            ++aPrimaryAndFloorSurvivors;
            ++aPrimaryAndFloorPerHeart[aHeart];
        }
    }
    const auto AppendPrimaryEvidenceSurvival = [
        &aReport,
        kRecipeCount](
            const char *pLabel,
            const std::size_t pSurvivors,
            const std::array<std::size_t,
                LoopHeadFarmer::kCoreCount> &pPerHeart) {
        std::vector<int> aHeartCounts;
        aHeartCounts.reserve(pPerHeart.size());
        std::size_t aEmptyHearts = 0U;
        for (const std::size_t aCount : pPerHeart) {
            aHeartCounts.push_back(static_cast<int>(aCount));
            aEmptyHearts += aCount == 0U;
        }
        const DistributionSummary aSummary =
            SummarizeValues(aHeartCounts);
        aReport << "  " << std::left << std::setw(32) << pLabel
                << std::right << " survivors=" << pSurvivors
                << "/" << kRecipeCount
                << " empty_hearts=" << aEmptyHearts
                << " per_heart=" << aSummary.mMinimum
                << "/" << aSummary.mP25
                << "/" << aSummary.mMedian
                << "/" << aSummary.mP75
                << "/" << aSummary.mMaximum
                << " (min/p25/p50/p75/max)\n";
    };
    aReport << "\nPRIMARY EVIDENCE SET SURVIVAL\n"
            << "Uses redundant early-branch fraction >=554, maximum "
               "orbiter shortest-path load <=209, and maximum single-"
               "orbiter ordered-pair damage <=14. These are two top-80% "
               "references plus the designated top-95% path-load "
               "reference.\n";
    AppendPrimaryEvidenceSurvival(
        "primary evidence only",
        aPrimaryEvidenceSurvivors,
        aPrimaryPerHeart);
    AppendPrimaryEvidenceSurvival(
        "primary plus structural floors",
        aPrimaryAndFloorSurvivors,
        aPrimaryAndFloorPerHeart);

    struct EvidencePoint {
        int mEarlyBranchFraction = 0;
        int mPathLoad = 0;
        int mSingleOrbiterDamage = 0;
        std::size_t mRecipeCount = 0U;
        std::size_t mExampleRecipeIndex = 0U;
    };
    std::vector<EvidencePoint> aEvidencePoints;
    aEvidencePoints.reserve(kRecipeCount);
    for (std::size_t aRecipe = 0U;
         aRecipe < kRecipeCount;
         ++aRecipe) {
        aEvidencePoints.push_back({
            aGlobalValues[19U][aRecipe],
            aGlobalValues[29U][aRecipe],
            aGlobalValues[46U][aRecipe],
            1U,
            aRecipe,
        });
    }
    std::sort(aEvidencePoints.begin(), aEvidencePoints.end(),
              [](const EvidencePoint &pA,
                 const EvidencePoint &pB) {
                  if (pA.mEarlyBranchFraction !=
                      pB.mEarlyBranchFraction) {
                      return pA.mEarlyBranchFraction >
                          pB.mEarlyBranchFraction;
                  }
                  if (pA.mPathLoad != pB.mPathLoad) {
                      return pA.mPathLoad < pB.mPathLoad;
                  }
                  return pA.mSingleOrbiterDamage <
                      pB.mSingleOrbiterDamage;
              });
    std::vector<EvidencePoint> aUniqueEvidencePoints;
    aUniqueEvidencePoints.reserve(aEvidencePoints.size());
    for (const EvidencePoint &aPoint : aEvidencePoints) {
        if (!aUniqueEvidencePoints.empty()) {
            EvidencePoint &aPrevious = aUniqueEvidencePoints.back();
            if ((aPrevious.mEarlyBranchFraction ==
                 aPoint.mEarlyBranchFraction) &&
                (aPrevious.mPathLoad == aPoint.mPathLoad) &&
                (aPrevious.mSingleOrbiterDamage ==
                 aPoint.mSingleOrbiterDamage)) {
                ++aPrevious.mRecipeCount;
                continue;
            }
        }
        aUniqueEvidencePoints.push_back(aPoint);
    }

    int aMaximumPathLoad = 0;
    for (const EvidencePoint &aPoint : aUniqueEvidencePoints) {
        aMaximumPathLoad = std::max(
            aMaximumPathLoad, aPoint.mPathLoad);
    }
    std::vector<int> aMinimumDamageByPath(
        static_cast<std::size_t>(aMaximumPathLoad + 1),
        std::numeric_limits<int>::max());
    std::size_t aParetoPointCount = 0U;
    std::size_t aParetoRecipeCount = 0U;
    std::vector<EvidencePoint> aParetoPoints;
    for (const EvidencePoint &aPoint : aUniqueEvidencePoints) {
        int aBestDamage = std::numeric_limits<int>::max();
        for (int aPath = 0; aPath <= aPoint.mPathLoad; ++aPath) {
            aBestDamage = std::min(
                aBestDamage,
                aMinimumDamageByPath[static_cast<std::size_t>(aPath)]);
        }
        if (aBestDamage > aPoint.mSingleOrbiterDamage) {
            ++aParetoPointCount;
            aParetoRecipeCount += aPoint.mRecipeCount;
            aParetoPoints.push_back(aPoint);
        }
        int &aStoredDamage = aMinimumDamageByPath[
            static_cast<std::size_t>(aPoint.mPathLoad)];
        aStoredDamage = std::min(
            aStoredDamage, aPoint.mSingleOrbiterDamage);
    }
    aReport << "  Pareto frontier                 recipes="
            << aParetoRecipeCount << "/" << kRecipeCount
            << " unique_metric_tuples=" << aParetoPointCount
            << "/" << aUniqueEvidencePoints.size() << "\n"
            << "  Pareto directions: maximize early-branch redundancy; "
               "minimize path load and single-orbiter damage.\n";
    for (const EvidencePoint &aPoint : aParetoPoints) {
        aReport << "    recipe=" << aPoint.mExampleRecipeIndex
                << " heart="
                << (aPoint.mExampleRecipeIndex /
                    LoopHeadFarmer::kPatternsPerCore)
                << " head="
                << (aPoint.mExampleRecipeIndex %
                    LoopHeadFarmer::kPatternsPerCore)
                << " branch=" << aPoint.mEarlyBranchFraction
                << " path_load=" << aPoint.mPathLoad
                << " cut_damage=" << aPoint.mSingleOrbiterDamage;
        if (aPoint.mRecipeCount > 1U) {
            aReport << " tied_recipes=" << aPoint.mRecipeCount;
        }
        aReport << "\n";
    }

    if (pMeasureExactPairDistances) {
        aReport << "\nEXACT STRUCTURAL DIFFERENCE BASELINE\n"
                << "Heart distance counts unequal canonical slots among "
                   "the 33 lead/source/feedback slots.\n"
                << "Head distance counts unequal orbiter-to-wanderer "
                   "assignments among 11 slots.\n"
                << "Tail distance counts unequal update-role assignments "
                   "among 22 slots.\n"
                << "Nearest-neighbor quartiles, rather than ordinary pair "
                   "quartiles, are the useful starting point for future "
                   "minimum-distance rejection thresholds.\n\n";

        std::array<std::uint64_t, 34U> aHeartHistogram{};
        std::array<int, LoopHeadFarmer::kCoreCount> aHeartNearest{};
        aHeartNearest.fill(33);
        for (std::size_t a = 0U;
             a < LoopHeadFarmer::kCoreCount;
             ++a) {
            for (std::size_t b = a + 1U;
                 b < LoopHeadFarmer::kCoreCount;
                 ++b) {
                const int aDistance = HeartSlotDistance(
                    aPatterns.mHearts[a].mHeart,
                    aPatterns.mHearts[b].mHeart);
                ++aHeartHistogram[static_cast<std::size_t>(aDistance)];
                aHeartNearest[a] = std::min(aHeartNearest[a], aDistance);
                aHeartNearest[b] = std::min(aHeartNearest[b], aDistance);
            }
        }
        AppendDistanceHistogram(&aReport,
                                "HEART ALL-PAIR DISTANCE",
                                aHeartHistogram);
        AppendDistributionRow(
            &aReport,
            "heart nearest-neighbor distance",
            true,
            SummarizeValues(std::vector<int>(
                aHeartNearest.begin(), aHeartNearest.end())));
        aReport << "\n";

        std::array<std::uint64_t, 12U> aHeadHistogram{};
        std::array<std::uint64_t, 23U> aTailHistogram{};
        std::vector<int> aHeadNearest(kRecipeCount, 11);
        std::vector<int> aTailNearest(kRecipeCount, 22);
        for (std::size_t a = 0U; a < kRecipeCount; ++a) {
            for (std::size_t b = a + 1U; b < kRecipeCount; ++b) {
                const int aHeadDistance = NonZeroNibbleCount(
                    aPackedHeads[a] ^ aPackedHeads[b]);
                const int aTailDistanceValue = TailDistance(
                    aPackedTails[a], aPackedTails[b]);
                ++aHeadHistogram[
                    static_cast<std::size_t>(aHeadDistance)];
                ++aTailHistogram[
                    static_cast<std::size_t>(aTailDistanceValue)];
                aHeadNearest[a] = std::min(
                    aHeadNearest[a], aHeadDistance);
                aHeadNearest[b] = std::min(
                    aHeadNearest[b], aHeadDistance);
                aTailNearest[a] = std::min(
                    aTailNearest[a], aTailDistanceValue);
                aTailNearest[b] = std::min(
                    aTailNearest[b], aTailDistanceValue);
            }
            if (((a + 1U) % 1000U) == 0U) {
                std::printf("Current recipe distance audit processed "
                            "%zu/%zu rows\n",
                            a + 1U, kRecipeCount);
            }
        }
        AppendDistanceHistogram(&aReport,
                                "HEAD ALL-PAIR DISTANCE",
                                aHeadHistogram);
        AppendDistributionRow(
            &aReport,
            "head nearest-neighbor distance",
            true,
            SummarizeValues(aHeadNearest));
        aReport << "\n";
        AppendDistanceHistogram(&aReport,
                                "TAIL ALL-PAIR DISTANCE",
                                aTailHistogram);
        AppendDistributionRow(
            &aReport,
            "tail nearest-neighbor distance",
            true,
            SummarizeValues(aTailNearest));
        aReport << "\n";
    } else {
        aReport << "\nEXACT STRUCTURAL DIFFERENCE BASELINE\n"
                << "Skipped. Re-run with exact pair distances enabled to "
                   "measure all-pair and nearest-neighbor heart/head/tail "
                   "distance distributions.\n";
    }

    aReport << "\nINTERPRETATION FOR THE NEXT FARMER\n"
            << "1. Treat hard validity (allowed tail pairs and strong "
               "connectivity) as immediate rejection, not as a score.\n"
            << "2. Select provisional flow floors from the global table, "
               "then inspect joint survival and empty-heart counts. "
               "Independent medians are not automatically a viable joint "
               "threshold.\n"
            << "3. Use nearest-neighbor heart/head distances to seed "
               "minimum structural-distance cutoffs. All-pair medians are "
               "too permissive for this purpose.\n"
            << "4. The replacement farmer should draw a random canonical "
               "heart and a random head, build valid tails, and accept only "
               "complete recipes that clear every chosen flow floor and "
               "the distance floors against the accepted set.\n";

    const std::string aText = aReport.str();
    const std::vector<std::uint8_t> aBytes(
        aText.begin(), aText.end());
    const std::string aPath = ResolvedPath(pOutputPath);
    if (!FileIO::Save(aPath, aBytes)) {
        SetError(pErrorMessage,
                 "Current loop recipe audit could not save " + aPath);
        return false;
    }
    std::printf("Saved current loop flow baseline to %s (%zu bytes)\n",
                aPath.c_str(), aBytes.size());
    return true;
}

bool LoopTailFarmer::Explore(
    const std::string &pHeartPatternPath,
    const std::string &pHeadPatternPath,
    const std::string &pExplorationPoolFolderPath,
    const std::uint64_t pExplorationCasesPerPair,
    const std::size_t pExplorationRetainedPerPair,
    const std::size_t pPrintEveryPairCount,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if (pExplorationCasesPerPair == 0ULL) {
        SetError(pErrorMessage,
                 "Loop tail farmer requires at least one exploration case per pair");
        return false;
    }
    if ((pExplorationRetainedPerPair == 0U) ||
        (pExplorationRetainedPerPair > pExplorationCasesPerPair)) {
        SetError(pErrorMessage,
                 "Loop tail exploration retention must be between one and the exploration count");
        return false;
    }
    if ((pExplorationCasesPerPair >
         std::numeric_limits<std::uint32_t>::max()) ||
        (pExplorationRetainedPerPair >
         std::numeric_limits<std::uint32_t>::max())) {
        SetError(pErrorMessage,
                 "Loop tail farmer configuration exceeded its binary format");
        return false;
    }

    std::error_code aDirectoryError;
    std::filesystem::create_directories(
        ResolvedPath(pExplorationPoolFolderPath), aDirectoryError);
    if (aDirectoryError) {
        SetError(pErrorMessage,
                 "Loop tail farmer could not create the pool folder: " +
                 aDirectoryError.message());
        return false;
    }

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pHeartPatternPath,
                             pHeadPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    const PoolMetadata aExplorationMetadata = {
        PoolPhase::kExploration,
        pExplorationCasesPerPair,
        0U,
        pExplorationRetainedPerPair,
    };
    std::printf("Loop tail Exploration phase: explore=%llu retain=%zu "
                "per heart/head pair; pools=%s\n",
                static_cast<unsigned long long>(
                    pExplorationCasesPerPair),
                pExplorationRetainedPerPair,
                ResolvedPath(pExplorationPoolFolderPath).c_str());

    std::uint64_t aRejectedSchedules = 0ULL;
    std::uint64_t aRejectedTransitions = 0ULL;
    std::uint64_t aRejectedDuplicates = 0ULL;
    std::uint64_t aEvaluated = 0ULL;
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < LoopHeadFarmer::kCoreCount;
         ++aHeartIndex) {
        const LoopNewHeart11 &aHeart =
            aPatterns.mHearts[aHeartIndex];
        const DistanceMatrix aDistances =
            HeartTemporalDistances(aHeart.mHeart);
        TailPools aCorePools;
        aCorePools.reserve(LoopHeadFarmer::kPatternsPerCore);

        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(aHeartIndex,
                                             aHeadIndex);
            const std::size_t aProcessedPairIndex =
                LoopNewFarmer::TailPatternIndex(aHeartIndex,
                                                aHeadIndex);
            Generator aGenerator(
                GeneratorSeedForPattern(aPatternIndex));
            const LoopHeadPattern11 &aHead =
                aHeart.mHeads[aHeadIndex].mHead;

            const PairInfoMatrix aPairs = MakePairInfo(
                aHeart.mHeart, aHead, aPatternIndex, aDistances);

            std::priority_queue<
                Candidate,
                std::vector<Candidate>,
                BetterExplorationCandidateComparator> aPreliminaryBest;
            std::unordered_set<std::string> aPairKeys;
            aPairKeys.reserve(static_cast<std::size_t>(
                pExplorationCasesPerPair * 2ULL));
            Candidate aWorstCandidate;
            bool aHasWorstCandidate = false;
            std::uint64_t aValidCases = 0ULL;
            std::uint64_t aAttempts = 0ULL;
            const std::uint64_t aMaximumAttempts =
                pExplorationCasesPerPair >
                    ((std::numeric_limits<std::uint64_t>::max() - 4096ULL) /
                     64ULL)
                    ? std::numeric_limits<std::uint64_t>::max()
                    : (pExplorationCasesPerPair * 64ULL) + 4096ULL;
            while ((aValidCases < pExplorationCasesPerPair) &&
                   (aAttempts < aMaximumAttempts)) {
                ++aAttempts;
                LoopTailPattern11 aTail;
                if (!GenerateTail(aPairs, &aGenerator, &aTail)) {
                    ++aRejectedSchedules;
                    continue;
                }
                const std::string aKey = TailKey(aTail);
                if (!aPairKeys.insert(aKey).second) {
                    ++aRejectedDuplicates;
                    continue;
                }

                const TransitionMatrix aTransition =
                    MakeTransitionMatrix(aHead, aTail);
                const TransitionMetrics aTransitionMetrics =
                    MeasureTransition(aTransition, false);
                if (!aTransitionMetrics.mStronglyConnected) {
                    ++aRejectedTransitions;
                    continue;
                }

                Candidate aCandidate;
                aCandidate.mTail = aTail;
                aCandidate.mKey = aKey;
                aCandidate.mScore = ScoreTail(
                    aHeart.mHeart, aHead, aTail, aPatternIndex,
                    aPairs, aTransitionMetrics);
                ++aValidCases;
                ++aEvaluated;

                if (!aHasWorstCandidate ||
                    ExplorationCandidateIsBetter(
                        aWorstCandidate, aCandidate)) {
                    aWorstCandidate = aCandidate;
                    aHasWorstCandidate = true;
                }
                if (aPreliminaryBest.size() <
                    pExplorationRetainedPerPair) {
                    aPreliminaryBest.push(std::move(aCandidate));
                } else if (ExplorationCandidateIsBetter(
                               aCandidate, aPreliminaryBest.top())) {
                    aPreliminaryBest.pop();
                    aPreliminaryBest.push(std::move(aCandidate));
                }
            }

            if (aValidCases != pExplorationCasesPerPair) {
                int aAllowedPairCount = 0;
                std::string aDegrees;
                for (std::size_t a = 0U; a < kRoleCount; ++a) {
                    int aDegree = 0;
                    for (std::size_t b = 0U; b < kRoleCount; ++b) {
                        aDegree += aPairs[a][b].mAllowed;
                        if (a < b) {
                            aAllowedPairCount +=
                                aPairs[a][b].mAllowed;
                        }
                    }
                    if (!aDegrees.empty()) {
                        aDegrees += ",";
                    }
                    aDegrees += std::to_string(aDegree);
                }
                SetError(pErrorMessage,
                         "Loop tail farmer could not fill the valid tail budget for heart " +
                         std::to_string(aHeartIndex) + " head " +
                         std::to_string(aHeadIndex) +
                         "; valid=" + std::to_string(aValidCases) +
                         " attempts=" + std::to_string(aAttempts) +
                         "; allowed_pairs=" +
                         std::to_string(aAllowedPairCount) +
                         " degrees={" + aDegrees + "}");
                return false;
            }

            std::vector<Candidate> aFinalists;
            aFinalists.reserve(aPreliminaryBest.size());
            while (!aPreliminaryBest.empty()) {
                aFinalists.push_back(aPreliminaryBest.top());
                aPreliminaryBest.pop();
            }
            std::sort(aFinalists.begin(), aFinalists.end(),
                      ExplorationCandidateIsBetter);

            const bool aPrintSample =
                (pPrintEveryPairCount != 0U) &&
                ((aProcessedPairIndex % pPrintEveryPairCount) == 0U);
            if (aPrintSample) {
                std::printf("\nExploration flow sample: core=%zu head=%zu "
                            "pattern=%zu\n",
                            aHeartIndex, aHeadIndex, aPatternIndex);
                PrintTail("GOOD", aFinalists.front());
                PrintTail("BAD ", aWorstCandidate);
                std::printf("  progress: pairs=%zu/%zu evaluated=%llu\n",
                            aProcessedPairIndex + 1U,
                            LoopHeadFarmer::kRetainedPatternCount,
                            static_cast<unsigned long long>(aEvaluated));
            }
            aCorePools.push_back(std::move(aFinalists));
        }

        if (!SaveCorePool(pExplorationPoolFolderPath,
                          aHeartIndex,
                          aExplorationMetadata,
                          aCorePools,
                          pErrorMessage)) {
            return false;
        }
        std::printf("Exploration processed heart %zu/%zu; saved=%s\n",
                    aHeartIndex + 1U,
                    LoopHeadFarmer::kCoreCount,
                    PoolFilePath(pExplorationPoolFolderPath,
                                 aHeartIndex).c_str());
    }

    std::printf("Loop tail Exploration summary: evaluated=%llu "
                "schedule_rejections=%llu transition_rejections=%llu "
                "duplicate_rejections=%llu pool_files=%zu\n",
                static_cast<unsigned long long>(aEvaluated),
                static_cast<unsigned long long>(aRejectedSchedules),
                static_cast<unsigned long long>(aRejectedTransitions),
                static_cast<unsigned long long>(aRejectedDuplicates),
                LoopHeadFarmer::kCoreCount);
    return true;
}

bool LoopTailFarmer::MakeSafe(
    const std::string &pHeartPatternPath,
    const std::string &pHeadPatternPath,
    const std::string &pExplorationPoolFolderPath,
    const std::string &pSafePoolFolderPath,
    const std::uint64_t pExplorationCasesPerPair,
    const std::size_t pExplorationRetainedPerPair,
    const std::size_t pSafeRetainedPerPair,
    const std::size_t pPrintEveryPairCount,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pExplorationCasesPerPair == 0ULL) ||
        (pExplorationRetainedPerPair == 0U) ||
        (pSafeRetainedPerPair == 0U) ||
        (pExplorationRetainedPerPair > pExplorationCasesPerPair) ||
        (pSafeRetainedPerPair > pExplorationRetainedPerPair) ||
        (pExplorationCasesPerPair >
         std::numeric_limits<std::uint32_t>::max()) ||
        (pExplorationRetainedPerPair >
         std::numeric_limits<std::uint32_t>::max()) ||
        (pSafeRetainedPerPair >
         std::numeric_limits<std::uint32_t>::max())) {
        SetError(pErrorMessage,
                 "Loop tail Safe phase had an invalid count configuration");
        return false;
    }

    std::error_code aDirectoryError;
    std::filesystem::create_directories(
        ResolvedPath(pSafePoolFolderPath), aDirectoryError);
    if (aDirectoryError) {
        SetError(pErrorMessage,
                 "Loop tail Safe phase could not create its pool folder: " +
                 aDirectoryError.message());
        return false;
    }

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pHeartPatternPath,
                             pHeadPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    const PoolMetadata aExplorationMetadata = {
        PoolPhase::kExploration,
        pExplorationCasesPerPair,
        0U,
        pExplorationRetainedPerPair,
    };
    const PoolMetadata aSafeMetadata = {
        PoolPhase::kSafe,
        pExplorationCasesPerPair,
        pExplorationRetainedPerPair,
        pSafeRetainedPerPair,
    };
    std::printf("Loop tail Safe phase: load=%zu retain=%zu per "
                "heart/head pair; source=%s output=%s\n",
                pExplorationRetainedPerPair,
                pSafeRetainedPerPair,
                ResolvedPath(pExplorationPoolFolderPath).c_str(),
                ResolvedPath(pSafePoolFolderPath).c_str());

    std::uint64_t aEvaluated = 0ULL;
    for (std::size_t aHeartIndex = 0U;
         aHeartIndex < LoopHeadFarmer::kCoreCount;
         ++aHeartIndex) {
        TailPools aExplorationPools;
        if (!LoadCorePool(pExplorationPoolFolderPath,
                          aHeartIndex,
                          aExplorationMetadata,
                          &aExplorationPools,
                          pErrorMessage)) {
            return false;
        }

        const LoopNewHeart11 &aHeart =
            aPatterns.mHearts[aHeartIndex];
        const DistanceMatrix aDistances =
            HeartTemporalDistances(aHeart.mHeart);
        TailPools aSafePools;
        aSafePools.reserve(LoopHeadFarmer::kPatternsPerCore);
        for (std::size_t aHeadIndex = 0U;
             aHeadIndex < LoopHeadFarmer::kPatternsPerCore;
             ++aHeadIndex) {
            const std::size_t aPatternIndex =
                LoopHeadFarmer::PatternIndex(aHeartIndex,
                                             aHeadIndex);
            const std::size_t aProcessedPairIndex =
                LoopNewFarmer::TailPatternIndex(aHeartIndex,
                                                aHeadIndex);
            const LoopHeadPattern11 &aHead =
                aHeart.mHeads[aHeadIndex].mHead;
            const PairInfoMatrix aPairs = MakePairInfo(
                aHeart.mHeart, aHead, aPatternIndex, aDistances);

            std::vector<Candidate> aCandidates =
                std::move(aExplorationPools[aHeadIndex]);
            std::unordered_set<std::string> aKeys;
            aKeys.reserve(aCandidates.size() * 2U);
            for (Candidate &aCandidate : aCandidates) {
                if (!aKeys.insert(aCandidate.mKey).second ||
                    !TailUsesAllowedPairs(aCandidate.mTail, aPairs)) {
                    SetError(pErrorMessage,
                             "Loop tail Safe phase encountered an invalid Exploration tail");
                    return false;
                }
                const TransitionMatrix aTransition =
                    MakeTransitionMatrix(aHead, aCandidate.mTail);
                const TransitionMetrics aTransitionMetrics =
                    MeasureTransition(aTransition, true);
                if (!aTransitionMetrics.mStronglyConnected) {
                    SetError(pErrorMessage,
                             "Loop tail Safe phase encountered a disconnected Exploration tail");
                    return false;
                }
                aCandidate.mScore = ScoreTail(
                    aHeart.mHeart,
                    aHead,
                    aCandidate.mTail,
                    aPatternIndex,
                    aPairs,
                    aTransitionMetrics);
                ++aEvaluated;
            }

            std::sort(aCandidates.begin(), aCandidates.end(),
                      SafeCandidateIsBetter);
            const bool aPrintSample =
                (pPrintEveryPairCount != 0U) &&
                ((aProcessedPairIndex % pPrintEveryPairCount) == 0U);
            if (aPrintSample) {
                std::printf("\nSafe flow sample: core=%zu head=%zu "
                            "pattern=%zu\n",
                            aHeartIndex, aHeadIndex, aPatternIndex);
                PrintTail("GOOD", aCandidates.front());
                PrintTail("BAD ", aCandidates.back());
                std::printf("  progress: pairs=%zu/%zu evaluated=%llu\n",
                            aProcessedPairIndex + 1U,
                            LoopHeadFarmer::kRetainedPatternCount,
                            static_cast<unsigned long long>(aEvaluated));
            }
            aCandidates.resize(pSafeRetainedPerPair);
            aSafePools.push_back(std::move(aCandidates));
        }

        if (!SaveCorePool(pSafePoolFolderPath,
                          aHeartIndex,
                          aSafeMetadata,
                          aSafePools,
                          pErrorMessage)) {
            return false;
        }
        std::printf("Safe processed heart %zu/%zu; saved=%s\n",
                    aHeartIndex + 1U,
                    LoopHeadFarmer::kCoreCount,
                    PoolFilePath(pSafePoolFolderPath,
                                 aHeartIndex).c_str());
    }

    std::printf("Loop tail Safe summary: evaluated=%llu pool_files=%zu\n",
                static_cast<unsigned long long>(aEvaluated),
                LoopHeadFarmer::kCoreCount);
    return true;
}

bool LoopTailFarmer::Finalize(
    const std::string &pSafePoolFolderPath,
    const std::string &pTailPatternPath,
    const std::uint64_t pExplorationCasesPerPair,
    const std::size_t pExplorationRetainedPerPair,
    const std::size_t pSafeRetainedPerPair,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pExplorationCasesPerPair == 0ULL) ||
        (pExplorationRetainedPerPair == 0U) ||
        (pSafeRetainedPerPair == 0U) ||
        (pExplorationRetainedPerPair > pExplorationCasesPerPair) ||
        (pSafeRetainedPerPair > pExplorationRetainedPerPair)) {
        SetError(pErrorMessage,
                 "Loop tail Final phase had an invalid count configuration");
        return false;
    }

    const PoolMetadata aSafeMetadata = {
        PoolPhase::kSafe,
        pExplorationCasesPerPair,
        pExplorationRetainedPerPair,
        pSafeRetainedPerPair,
    };
    std::printf("Loop tail Final phase: selecting from %zu saved Safe "
                "tails per heart/head pair\n",
                pSafeRetainedPerPair);
    return SelectDiverseTails(pSafePoolFolderPath,
                              pTailPatternPath,
                              aSafeMetadata,
                              pErrorMessage);
}

namespace {

//
// Final 14-nexus loop farm
//

constexpr std::array<std::uint8_t, 8U> kFinalLoopMagic = {
    'M', 'M', 'N', 'E', 'X', 'U', 'S', '1',
};
constexpr std::array<std::uint8_t, 8U> kFinalStateMagic = {
    'M', 'M', 'N', 'X', 'S', 'T', 'A', '1',
};
constexpr std::uint32_t kFinalLoopVersion = 1U;
constexpr std::uint32_t kFinalStateVersion = 1U;
constexpr std::size_t kFinalCoreScoreCount = 12U;
constexpr std::size_t kFinalLoopHeaderByteCount = 100U;
constexpr std::size_t kFinalLoopByteCount =
    kFinalLoopHeaderByteCount +
    (4U * kRoleCount) +
    (2U * kRoleCount) +
    (kFinalCoreScoreCount * sizeof(std::uint32_t)) +
    (kScoreFieldCount * sizeof(std::uint32_t));
constexpr std::size_t kFinalStateByteCount = 52U;

static_assert(kFinalLoopByteCount == 414U);
static_assert(LoopFinalFarmHearts::kHeartCount ==
              LoopFinalFarmThreholds::kHeartThresholds.size());

constexpr bool FinalNexusTablesMatch() {
    for (std::size_t i = 0U;
         i < LoopFinalFarmHearts::kHeartCount;
         ++i) {
        if (LoopFinalFarmHearts::kSourceHeartIndices[i] !=
            LoopFinalFarmThreholds::kHeartThresholds[i]
                .mSourceHeartIndex) {
            return false;
        }
    }
    return true;
}

static_assert(FinalNexusTablesMatch());

struct FinalLoopRecord {
    std::size_t mNexusIndex = 0U;
    std::size_t mSourceHeartIndex = 0U;
    std::uint64_t mLocalIndex = 0ULL;
    std::size_t mPatternIndex = 0U;
    LoopHeadPattern11 mHead;
    LoopCorePattern11 mHeart;
    LoopTailPattern11 mTail;
    MetricValues mValues{};
    int mIntegerScore = 0;
    std::uint64_t mRawAttempt = 0ULL;
    std::uint64_t mAcceptedOrdinal = 0ULL;
};

std::uint64_t FinalConfigurationSignature() {
    std::uint64_t aHash = Top40ScoringSignature();
    for (std::size_t i = 0U;
         i < LoopFinalFarmHearts::kHeartCount;
         ++i) {
        const std::uint64_t aHeartSignature = GoldHeartSignature(
            LoopFinalFarmHearts::kNexuses[i]);
        for (unsigned aByte = 0U;
             aByte < sizeof(aHeartSignature);
             ++aByte) {
            aHash = GoldHashByte(
                aHash,
                static_cast<std::uint8_t>(
                    aHeartSignature >> (aByte * 8U)));
        }
        const std::array<std::uint32_t, 2U> aHeartValues = {{
            static_cast<std::uint32_t>(
                LoopFinalFarmHearts::kSourceHeartIndices[i]),
            static_cast<std::uint32_t>(
                LoopFinalFarmThreholds::MinimumIntegerScoreForNexus(i)),
        }};
        for (const std::uint32_t aValue : aHeartValues) {
            for (unsigned aByte = 0U;
                 aByte < sizeof(aValue);
                 ++aByte) {
                aHash = GoldHashByte(
                    aHash,
                    static_cast<std::uint8_t>(
                        aValue >> (aByte * 8U)));
            }
        }
    }
    const std::array<std::size_t, 3U> aDifferences = {{
        LoopFinalFarmThreholds::kMinimumHeadDifference,
        LoopFinalFarmThreholds::kMinimumTailDifferencePartial,
        LoopFinalFarmThreholds::kMinimumTailDifferenceFull,
    }};
    for (const std::size_t aDifference : aDifferences) {
        for (unsigned aByte = 0U;
             aByte < sizeof(aDifference);
             ++aByte) {
            aHash = GoldHashByte(
                aHash,
                static_cast<std::uint8_t>(
                    aDifference >> (aByte * 8U)));
        }
    }
    return aHash;
}

std::string FinalNexusFolderPath(const std::string &pFolderPath,
                                 const std::size_t pNexusIndex) {
    char aName[64];
    std::snprintf(aName, sizeof(aName),
                  "nexus_%02zu", pNexusIndex);
    return (std::filesystem::path(ResolvedPath(pFolderPath)) / aName)
        .lexically_normal().generic_string();
}

std::string FinalLoopPath(const std::string &pFolderPath,
                          const std::size_t pNexusIndex,
                          const std::uint64_t pLocalIndex) {
    char aName[64];
    std::snprintf(aName, sizeof(aName),
                  "loop_%06llu.bin",
                  static_cast<unsigned long long>(pLocalIndex));
    return (std::filesystem::path(
                FinalNexusFolderPath(pFolderPath, pNexusIndex)) / aName)
        .lexically_normal().generic_string();
}

std::string FinalStatePath(const std::string &pFolderPath) {
    return (std::filesystem::path(ResolvedPath(pFolderPath)) /
            "final_farm_state.bin")
        .lexically_normal().generic_string();
}

bool SaveFinalBytesAtomically(
    const std::string &pPath,
    const std::vector<std::uint8_t> &pBytes,
    std::string *pErrorMessage) {
    const std::string aTemporaryPath = pPath + ".tmp";
    if (!FileIO::Save(aTemporaryPath, pBytes)) {
        SetError(pErrorMessage,
                 "Final loop farm could not save " + aTemporaryPath);
        return false;
    }
    if (std::rename(aTemporaryPath.c_str(), pPath.c_str()) != 0) {
        const std::string aReason = std::strerror(errno);
        std::error_code aCleanupError;
        std::filesystem::remove(aTemporaryPath, aCleanupError);
        SetError(pErrorMessage,
                 "Final loop farm could not install " + pPath +
                 ": " + aReason);
        return false;
    }
    return true;
}

bool SaveFinalLoopRecord(const std::string &pPath,
                         const FinalLoopRecord &pRecord,
                         std::string *pErrorMessage) {
    const int aMinimumScore =
        LoopFinalFarmThreholds::MinimumIntegerScoreForNexus(
            pRecord.mNexusIndex);
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kFinalLoopByteCount);
    aBytes.insert(aBytes.end(),
                  kFinalLoopMagic.begin(), kFinalLoopMagic.end());
    Append32(&aBytes, kFinalLoopVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(kRoleCount));
    Append32(&aBytes, static_cast<std::uint32_t>(kScoreFieldCount));
    Append32(&aBytes, static_cast<std::uint32_t>(kFinalLoopByteCount));
    Append32(&aBytes, static_cast<std::uint32_t>(pRecord.mNexusIndex));
    Append32(&aBytes,
             static_cast<std::uint32_t>(pRecord.mSourceHeartIndex));
    Append64(&aBytes, pRecord.mLocalIndex);
    Append32(&aBytes, static_cast<std::uint32_t>(pRecord.mPatternIndex));
    Append32(&aBytes, pRecord.mHead.mPermutationRank);
    Append32(&aBytes, static_cast<std::uint32_t>(pRecord.mIntegerScore));
    Append32(&aBytes, static_cast<std::uint32_t>(aMinimumScore));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopFinalFarmThreholds::kMinimumHeadDifference));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopFinalFarmThreholds::kMinimumTailDifferencePartial));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopFinalFarmThreholds::kMinimumTailDifferenceFull));
    Append64(&aBytes, pRecord.mRawAttempt);
    Append64(&aBytes, pRecord.mAcceptedOrdinal);
    Append64(&aBytes, GoldHeartSignature(pRecord.mHeart));
    Append64(&aBytes, FinalConfigurationSignature());

    aBytes.insert(aBytes.end(),
                  pRecord.mHead.mWandererForOrbiter.begin(),
                  pRecord.mHead.mWandererForOrbiter.end());
    for (const auto &aRound : pRecord.mHeart.mRounds) {
        aBytes.insert(aBytes.end(), aRound.begin(), aRound.end());
    }
    aBytes.insert(aBytes.end(),
                  pRecord.mTail.mOrbiterAForWanderer.begin(),
                  pRecord.mTail.mOrbiterAForWanderer.end());
    aBytes.insert(aBytes.end(),
                  pRecord.mTail.mOrbiterBForWanderer.begin(),
                  pRecord.mTail.mOrbiterBForWanderer.end());
    for (const std::uint32_t aValue :
         AlienCoreScoreValues(pRecord.mHeart.mScore)) {
        Append32(&aBytes, aValue);
    }
    AppendMetricValues(&aBytes, pRecord.mValues);
    if (aBytes.size() != kFinalLoopByteCount) {
        SetError(pErrorMessage,
                 "Final loop farm built an invalid record size");
        return false;
    }
    return SaveFinalBytesAtomically(pPath, aBytes, pErrorMessage);
}

bool LoadFinalLoopRecord(
    const std::string &pPath,
    const std::size_t pExpectedNexusIndex,
    const std::uint64_t pExpectedLocalIndex,
    FinalLoopRecord *pRecord,
    std::string *pErrorMessage) {
    const LoopCorePattern11 &aExpectedHeart =
        LoopFinalFarmHearts::kNexuses[pExpectedNexusIndex];
    const std::size_t aExpectedSourceHeartIndex =
        LoopFinalFarmHearts::kSourceHeartIndices[pExpectedNexusIndex];
    const int aExpectedMinimumScore =
        LoopFinalFarmThreholds::MinimumIntegerScoreForNexus(
            pExpectedNexusIndex);
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes) ||
        (aBytes.size() != kFinalLoopByteCount) ||
        !std::equal(kFinalLoopMagic.begin(), kFinalLoopMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Final loop farm could not read " + pPath);
        return false;
    }

    std::size_t aOffset = kFinalLoopMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    const std::uint32_t aRoleCount = Read32(aBytes, &aOffset);
    const std::uint32_t aMetricCount = Read32(aBytes, &aOffset);
    const std::uint32_t aByteCount = Read32(aBytes, &aOffset);
    const std::uint32_t aNexusIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aSourceHeartIndex = Read32(aBytes, &aOffset);
    const std::uint64_t aLocalIndex = Read64(aBytes, &aOffset);
    const std::uint32_t aPatternIndex = Read32(aBytes, &aOffset);
    const std::uint32_t aHeadRank = Read32(aBytes, &aOffset);
    const int aIntegerScore = static_cast<int>(Read32(aBytes, &aOffset));
    const int aMinimumScore = static_cast<int>(Read32(aBytes, &aOffset));
    const std::uint32_t aMinimumHead = Read32(aBytes, &aOffset);
    const std::uint32_t aMinimumTailPartial = Read32(aBytes, &aOffset);
    const std::uint32_t aMinimumTailFull = Read32(aBytes, &aOffset);
    const std::uint64_t aRawAttempt = Read64(aBytes, &aOffset);
    const std::uint64_t aAcceptedOrdinal = Read64(aBytes, &aOffset);
    const std::uint64_t aHeartSignature = Read64(aBytes, &aOffset);
    const std::uint64_t aConfigurationSignature =
        Read64(aBytes, &aOffset);
    if ((aVersion != kFinalLoopVersion) ||
        (aRoleCount != kRoleCount) ||
        (aMetricCount != kScoreFieldCount) ||
        (aByteCount != kFinalLoopByteCount) ||
        (aNexusIndex != pExpectedNexusIndex) ||
        (aSourceHeartIndex != aExpectedSourceHeartIndex) ||
        (aLocalIndex != pExpectedLocalIndex) ||
        (aPatternIndex >= LoopHeadFarmer::kRetainedPatternCount) ||
        (aMinimumScore != aExpectedMinimumScore) ||
        (aMinimumHead !=
         LoopFinalFarmThreholds::kMinimumHeadDifference) ||
        (aMinimumTailPartial !=
         LoopFinalFarmThreholds::kMinimumTailDifferencePartial) ||
        (aMinimumTailFull !=
         LoopFinalFarmThreholds::kMinimumTailDifferenceFull) ||
        (aHeartSignature != GoldHeartSignature(aExpectedHeart)) ||
        (aConfigurationSignature != FinalConfigurationSignature()) ||
        (aIntegerScore < aExpectedMinimumScore)) {
        SetError(pErrorMessage,
                 "Final loop farm record metadata did not match " +
                 pPath);
        return false;
    }

    FinalLoopRecord aRecord;
    aRecord.mNexusIndex = aNexusIndex;
    aRecord.mSourceHeartIndex = aSourceHeartIndex;
    aRecord.mLocalIndex = aLocalIndex;
    aRecord.mPatternIndex = aPatternIndex;
    aRecord.mHead.mPermutationRank = aHeadRank;
    aRecord.mIntegerScore = aIntegerScore;
    aRecord.mRawAttempt = aRawAttempt;
    aRecord.mAcceptedOrdinal = aAcceptedOrdinal;
    for (std::uint8_t &aValue :
         aRecord.mHead.mWandererForOrbiter) {
        aValue = aBytes[aOffset++];
    }
    for (auto &aRound : aRecord.mHeart.mRounds) {
        for (std::uint8_t &aValue : aRound) {
            aValue = aBytes[aOffset++];
        }
    }
    for (std::uint8_t &aValue :
         aRecord.mTail.mOrbiterAForWanderer) {
        aValue = aBytes[aOffset++];
    }
    for (std::uint8_t &aValue :
         aRecord.mTail.mOrbiterBForWanderer) {
        aValue = aBytes[aOffset++];
    }
    const auto aExpectedCoreScore =
        AlienCoreScoreValues(aExpectedHeart.mScore);
    for (std::size_t i = 0U; i < kFinalCoreScoreCount; ++i) {
        if (Read32(aBytes, &aOffset) != aExpectedCoreScore[i]) {
            SetError(pErrorMessage,
                     "Final loop farm core score did not match " +
                     pPath);
            return false;
        }
    }
    aRecord.mValues = ReadMetricValues(aBytes, &aOffset);
    if ((aOffset != aBytes.size()) ||
        (aRecord.mHeart.mRounds != aExpectedHeart.mRounds) ||
        !LoopHeadFarmer::IsValid(aRecord.mHead) ||
        (LoopHeadFarmer::Rank(aRecord.mHead) != aHeadRank) ||
        (LoopScorer::Score(aRecord.mValues) != aIntegerScore)) {
        SetError(pErrorMessage,
                 "Final loop farm record body did not validate " +
                 pPath);
        return false;
    }
    aRecord.mHeart.mScore = aExpectedHeart.mScore;

    LoopNewHeart11 aHeart;
    aHeart.mHeart = aExpectedHeart;
    const DistanceMatrix aDistances =
        HeartTemporalDistances(aExpectedHeart);
    const PairInfoMatrix aPairs = MakePairInfo(
        aExpectedHeart,
        aRecord.mHead,
        aRecord.mPatternIndex,
        aDistances);
    Candidate aEvaluated;
    if (!EvaluateAscendencyCandidate(
            aHeart,
            aRecord.mHead,
            aRecord.mPatternIndex,
            aPairs,
            aRecord.mTail,
            &aEvaluated,
            true) ||
        (RankingDisplayValues(aEvaluated.mScore) != aRecord.mValues)) {
        SetError(pErrorMessage,
                 "Final loop farm could not reproduce " + pPath);
        return false;
    }
    *pRecord = std::move(aRecord);
    return true;
}

bool ParseFinalLoopLocalIndex(const std::filesystem::path &pPath,
                              std::uint64_t *pIndex) {
    if (pPath.extension() != ".bin") {
        return false;
    }
    const std::string aName = pPath.stem().generic_string();
    constexpr const char *kPrefix = "loop_";
    if ((aName.rfind(kPrefix, 0U) != 0U) ||
        (aName.size() == std::strlen(kPrefix))) {
        return false;
    }
    std::uint64_t aValue = 0ULL;
    for (std::size_t i = std::strlen(kPrefix); i < aName.size(); ++i) {
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
    *pIndex = aValue;
    return true;
}

bool SaveFinalFarmState(const std::string &pPath,
                        const std::uint64_t pRawAttempts,
                        const std::uint64_t pAcceptedCount,
                        std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kFinalStateByteCount);
    aBytes.insert(aBytes.end(),
                  kFinalStateMagic.begin(), kFinalStateMagic.end());
    Append32(&aBytes, kFinalStateVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopFinalFarmHearts::kHeartCount));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopFinalFarmThreholds::kMinimumHeadDifference));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopFinalFarmThreholds::kMinimumTailDifferencePartial));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopFinalFarmThreholds::kMinimumTailDifferenceFull));
    Append64(&aBytes, FinalConfigurationSignature());
    Append64(&aBytes, pRawAttempts);
    Append64(&aBytes, pAcceptedCount);
    if (aBytes.size() != kFinalStateByteCount) {
        SetError(pErrorMessage,
                 "Final loop farm built an invalid state size");
        return false;
    }
    return SaveFinalBytesAtomically(pPath, aBytes, pErrorMessage);
}

bool LoadFinalFarmState(const std::string &pPath,
                        bool *pFound,
                        std::uint64_t *pRawAttempts,
                        std::uint64_t *pAcceptedCount,
                        std::string *pErrorMessage) {
    *pFound = false;
    std::error_code aExistsError;
    if (!std::filesystem::exists(pPath, aExistsError)) {
        if (aExistsError) {
            SetError(pErrorMessage,
                     "Final loop farm could not inspect its state file");
            return false;
        }
        return true;
    }
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes) ||
        (aBytes.size() != kFinalStateByteCount) ||
        !std::equal(kFinalStateMagic.begin(), kFinalStateMagic.end(),
                    aBytes.begin())) {
        SetError(pErrorMessage,
                 "Final loop farm could not read its state file");
        return false;
    }
    std::size_t aOffset = kFinalStateMagic.size();
    const std::uint32_t aVersion = Read32(aBytes, &aOffset);
    const std::uint32_t aNexusCount = Read32(aBytes, &aOffset);
    const std::uint32_t aMinimumHead = Read32(aBytes, &aOffset);
    const std::uint32_t aMinimumTailPartial = Read32(aBytes, &aOffset);
    const std::uint32_t aMinimumTailFull = Read32(aBytes, &aOffset);
    const std::uint64_t aConfigurationSignature =
        Read64(aBytes, &aOffset);
    const std::uint64_t aRawAttempts = Read64(aBytes, &aOffset);
    const std::uint64_t aAcceptedCount = Read64(aBytes, &aOffset);
    if ((aVersion != kFinalStateVersion) ||
        (aNexusCount != LoopFinalFarmHearts::kHeartCount) ||
        (aMinimumHead !=
         LoopFinalFarmThreholds::kMinimumHeadDifference) ||
        (aMinimumTailPartial !=
         LoopFinalFarmThreholds::kMinimumTailDifferencePartial) ||
        (aMinimumTailFull !=
         LoopFinalFarmThreholds::kMinimumTailDifferenceFull) ||
        (aConfigurationSignature != FinalConfigurationSignature()) ||
        (aOffset != aBytes.size())) {
        SetError(pErrorMessage,
                 "Final loop farm state used different code-defined "
                 "hearts, scoring, thresholds, or difference limits");
        return false;
    }
    *pFound = true;
    *pRawAttempts = aRawAttempts;
    *pAcceptedCount = aAcceptedCount;
    return true;
}

std::size_t FinalNextNexus(
    const std::array<std::uint64_t,
                     LoopFinalFarmHearts::kHeartCount> &pCounts) {
    std::size_t aBestIndex = 0U;
    for (std::size_t i = 1U; i < pCounts.size(); ++i) {
        if (pCounts[i] < pCounts[aBestIndex]) {
            aBestIndex = i;
        }
    }
    return aBestIndex;
}

struct FinalDifferenceConflict {
    std::size_t mNexusIndex = 0U;
    std::uint64_t mLocalIndex = 0ULL;
    LoopHeadTailDifference::Measures mDifference;
};

bool FinalIsDifferentFromPool(
    const LoopHeadPattern11 &pHead,
    const LoopTailPattern11 &pTail,
    const std::vector<FinalLoopRecord> &pSaved,
    LoopHeadTailDifference::Measures *pClosest,
    FinalDifferenceConflict *pConflict) {
    LoopHeadTailDifference::Measures aClosest = {
        kRoleCount, kRoleCount, kRoleCount,
    };
    for (const FinalLoopRecord &aSaved : pSaved) {
        const LoopHeadTailDifference::Measures aDifference =
            LoopHeadTailDifference::Measure(
                pHead, pTail, aSaved.mHead, aSaved.mTail);
        aClosest.mHead = std::min(
            aClosest.mHead, aDifference.mHead);
        aClosest.mTailPartial = std::min(
            aClosest.mTailPartial, aDifference.mTailPartial);
        aClosest.mTailFull = std::min(
            aClosest.mTailFull, aDifference.mTailFull);
        if ((aDifference.mHead <
             LoopFinalFarmThreholds::kMinimumHeadDifference) ||
            (aDifference.mTailPartial <
             LoopFinalFarmThreholds::kMinimumTailDifferencePartial) ||
            (aDifference.mTailFull <
             LoopFinalFarmThreholds::kMinimumTailDifferenceFull)) {
            if (pClosest != nullptr) {
                *pClosest = aClosest;
            }
            if (pConflict != nullptr) {
                pConflict->mNexusIndex = aSaved.mNexusIndex;
                pConflict->mLocalIndex = aSaved.mLocalIndex;
                pConflict->mDifference = aDifference;
            }
            return false;
        }
    }
    if (pClosest != nullptr) {
        *pClosest = aClosest;
    }
    return true;
}

} // namespace

bool LoopTailFarmer::FarmFinalLoops(
    const std::string &pOutputFolderPath,
    const std::uint64_t pNewLoopTarget,
    const std::uint64_t pMaximumAttempts,
    const std::uint64_t pProgressInterval,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pNewLoopTarget == 0ULL) ||
        (pMaximumAttempts == 0ULL) ||
        (pProgressInterval == 0ULL)) {
        SetError(pErrorMessage,
                 "Final loop farm requires positive run counts");
        return false;
    }

    const std::string aOutputFolder =
        ResolvedPath(pOutputFolderPath);
    std::error_code aCreateError;
    std::filesystem::create_directories(aOutputFolder, aCreateError);
    if (aCreateError) {
        SetError(pErrorMessage,
                 "Final loop farm could not create " + aOutputFolder +
                 ": " + aCreateError.message());
        return false;
    }

    std::array<std::uint64_t,
               LoopFinalFarmHearts::kHeartCount> aNexusCounts{};
    std::vector<FinalLoopRecord> aSaved;
    for (std::size_t aNexusIndex = 0U;
         aNexusIndex < LoopFinalFarmHearts::kHeartCount;
         ++aNexusIndex) {
        const std::string aFolder = FinalNexusFolderPath(
            pOutputFolderPath, aNexusIndex);
        std::error_code aFolderError;
        std::filesystem::create_directories(aFolder, aFolderError);
        if (aFolderError) {
            SetError(pErrorMessage,
                     "Final loop farm could not create " + aFolder +
                     ": " + aFolderError.message());
            return false;
        }

        std::vector<std::pair<std::uint64_t,
                              std::filesystem::path>> aPaths;
        std::error_code aEnumerateError;
        std::filesystem::directory_iterator aIterator(
            aFolder, aEnumerateError);
        while (!aEnumerateError &&
               (aIterator != std::filesystem::directory_iterator())) {
            const std::filesystem::directory_entry &aEntry = *aIterator;
            if (aEntry.is_regular_file()) {
                const std::string aName =
                    aEntry.path().filename().generic_string();
                if ((aName == ".DS_Store") ||
                    (aEntry.path().extension() == ".tmp")) {
                    aIterator.increment(aEnumerateError);
                    continue;
                }
                if (aEntry.path().extension() != ".bin") {
                    SetError(pErrorMessage,
                             "Final loop farm only supports .bin loop "
                             "files; found " +
                             aEntry.path().generic_string());
                    return false;
                }
                std::uint64_t aLocalIndex = 0ULL;
                if (!ParseFinalLoopLocalIndex(
                        aEntry.path(), &aLocalIndex)) {
                    SetError(pErrorMessage,
                             "Final loop farm found an invalid .bin "
                             "filename: " +
                             aEntry.path().generic_string());
                    return false;
                }
                aPaths.push_back({aLocalIndex, aEntry.path()});
            }
            aIterator.increment(aEnumerateError);
        }
        if (aEnumerateError) {
            SetError(pErrorMessage,
                     "Final loop farm could not enumerate " + aFolder +
                     ": " + aEnumerateError.message());
            return false;
        }
        std::sort(aPaths.begin(), aPaths.end(),
                  [](const auto &pA, const auto &pB) {
            return pA.first < pB.first;
        });
        for (std::size_t i = 0U; i < aPaths.size(); ++i) {
            const std::uint64_t aExpectedLocalIndex = i + 1ULL;
            if (aPaths[i].first != aExpectedLocalIndex) {
                SetError(pErrorMessage,
                         "Final loop farm found a duplicate or gap in " +
                         aFolder);
                return false;
            }
            FinalLoopRecord aRecord;
            if (!LoadFinalLoopRecord(
                    aPaths[i].second.generic_string(),
                    aNexusIndex,
                    aExpectedLocalIndex,
                    &aRecord,
                    pErrorMessage)) {
                return false;
            }
            aSaved.push_back(std::move(aRecord));
        }
        aNexusCounts[aNexusIndex] = aPaths.size();
    }

    std::sort(aSaved.begin(), aSaved.end(),
              [](const FinalLoopRecord &pA,
                 const FinalLoopRecord &pB) {
        return pA.mAcceptedOrdinal < pB.mAcceptedOrdinal;
    });
    std::array<std::uint64_t,
               LoopFinalFarmHearts::kHeartCount> aExpectedCounts{};
    std::uint64_t aMaximumRecordAttempt = 0ULL;
    for (std::size_t i = 0U; i < aSaved.size(); ++i) {
        const std::size_t aExpectedNexus =
            FinalNextNexus(aExpectedCounts);
        const std::uint64_t aExpectedOrdinal = i + 1ULL;
        const std::uint64_t aExpectedLocalIndex =
            aExpectedCounts[aExpectedNexus] + 1ULL;
        if ((aSaved[i].mAcceptedOrdinal != aExpectedOrdinal) ||
            (aSaved[i].mNexusIndex != aExpectedNexus) ||
            (aSaved[i].mLocalIndex != aExpectedLocalIndex)) {
            SetError(pErrorMessage,
                     "Final loop farm records did not follow count-first, "
                     "then index-first round robin order");
            return false;
        }
        ++aExpectedCounts[aExpectedNexus];
        aMaximumRecordAttempt = std::max(
            aMaximumRecordAttempt, aSaved[i].mRawAttempt);
    }
    if (aExpectedCounts != aNexusCounts) {
        SetError(pErrorMessage,
                 "Final loop farm directory counts did not match its "
                 "accepted record order");
        return false;
    }

    const std::string aStatePath = FinalStatePath(pOutputFolderPath);
    bool aFoundState = false;
    std::uint64_t aTotalRawAttempts = 0ULL;
    std::uint64_t aStateAcceptedCount = 0ULL;
    if (!LoadFinalFarmState(
            aStatePath,
            &aFoundState,
            &aTotalRawAttempts,
            &aStateAcceptedCount,
            pErrorMessage)) {
        return false;
    }
    if (aFoundState && (aStateAcceptedCount > aSaved.size())) {
        SetError(pErrorMessage,
                 "Final loop farm state refers to missing loop files");
        return false;
    }
    aTotalRawAttempts = std::max(
        aTotalRawAttempts, aMaximumRecordAttempt);
    if (!SaveFinalFarmState(
            aStatePath,
            aTotalRawAttempts,
            aSaved.size(),
            pErrorMessage)) {
        return false;
    }

    std::array<DistanceMatrix,
               LoopFinalFarmHearts::kHeartCount> aDistances{};
    for (std::size_t i = 0U; i < aDistances.size(); ++i) {
        aDistances[i] = HeartTemporalDistances(
            LoopFinalFarmHearts::kNexuses[i]);
    }

    std::printf("\nFINAL NEXUS LOOP FARM\n");
    std::printf("loaded=%zu attempts=%llu next-nexus=%02zu "
                "difference={head:%zu partial:%zu full:%zu}\n",
                aSaved.size(),
                static_cast<unsigned long long>(aTotalRawAttempts),
                FinalNextNexus(aNexusCounts),
                LoopFinalFarmThreholds::kMinimumHeadDifference,
                LoopFinalFarmThreholds::kMinimumTailDifferencePartial,
                LoopFinalFarmThreholds::kMinimumTailDifferenceFull);
    std::printf("nexus | source | cutoff | saved\n"
                "------+--------+--------+-------\n");
    for (std::size_t i = 0U; i < aNexusCounts.size(); ++i) {
        std::printf("%5zu | %6zu | %6d | %llu\n",
                    i,
                    LoopFinalFarmHearts::kSourceHeartIndices[i],
                    LoopFinalFarmThreholds::
                        MinimumIntegerScoreForNexus(i),
                    static_cast<unsigned long long>(aNexusCounts[i]));
    }
    std::printf("\n");

    std::uint64_t aRunAttempts = 0ULL;
    std::uint64_t aRunValid = 0ULL;
    std::uint64_t aRunScorePassed = 0ULL;
    std::uint64_t aRunDifferenceRejected = 0ULL;
    std::uint64_t aRunAccepted = 0ULL;
    while ((aRunAccepted < pNewLoopTarget) &&
           (aRunAttempts < pMaximumAttempts)) {
        ++aRunAttempts;
        ++aTotalRawAttempts;
        if ((aRunAttempts % pProgressInterval) == 0ULL) {
            if (!SaveFinalFarmState(
                    aStatePath,
                    aTotalRawAttempts - 1ULL,
                    aSaved.size(),
                    pErrorMessage)) {
                return false;
            }
            std::printf("final progress: tried=%llu valid=%llu "
                        "score-pass=%llu difference-reject=%llu "
                        "saved=%llu/%llu next=%02zu\n",
                        static_cast<unsigned long long>(aRunAttempts),
                        static_cast<unsigned long long>(aRunValid),
                        static_cast<unsigned long long>(aRunScorePassed),
                        static_cast<unsigned long long>(
                            aRunDifferenceRejected),
                        static_cast<unsigned long long>(aRunAccepted),
                        static_cast<unsigned long long>(pNewLoopTarget),
                        FinalNextNexus(aNexusCounts));
        }

        const std::size_t aNexusIndex =
            FinalNextNexus(aNexusCounts);
        const LoopCorePattern11 &aCore =
            LoopFinalFarmHearts::kNexuses[aNexusIndex];
        LoopNewHeart11 aHeart;
        aHeart.mHeart = aCore;
        Generator aGenerator(MixFarmSeed(
            0x4E45585553464152ULL ^
            GoldHeartSignature(aCore) ^
            (aTotalRawAttempts * 0xD1342543DE82EF95ULL)));

        LoopHeadPattern11 aHead;
        aHead.mWandererForOrbiter = IdentityRoles();
        Shuffle(&aHead.mWandererForOrbiter, &aGenerator);
        aHead.mPermutationRank = LoopHeadFarmer::Rank(aHead);
        if (!LoopHeadFarmer::IsValid(aHead)) {
            SetError(pErrorMessage,
                     "Final loop farm generated an invalid head");
            return false;
        }
        const std::size_t aPatternIndex = aGenerator.Below(
            LoopHeadFarmer::kRetainedPatternCount);
        const PairInfoMatrix aPairs = MakePairInfo(
            aCore,
            aHead,
            aPatternIndex,
            aDistances[aNexusIndex]);
        LoopTailPattern11 aTail;
        Candidate aEvaluated;
        if (!GenerateTail(aPairs, &aGenerator, &aTail) ||
            !EvaluateAscendencyCandidate(
                aHeart,
                aHead,
                aPatternIndex,
                aPairs,
                aTail,
                &aEvaluated,
                true)) {
            continue;
        }
        ++aRunValid;
        const MetricValues aValues =
            RankingDisplayValues(aEvaluated.mScore);
        const int aIntegerScore = LoopScorer::Score(aValues);
        if (!LoopFinalFarmThreholds::PassesIntegerScore(
                LoopFinalFarmHearts::kSourceHeartIndices[aNexusIndex],
                aIntegerScore)) {
            continue;
        }
        ++aRunScorePassed;

        LoopHeadTailDifference::Measures aClosest;
        FinalDifferenceConflict aConflict;
        if (!FinalIsDifferentFromPool(
                aHead,
                aTail,
                aSaved,
                &aClosest,
                &aConflict)) {
            ++aRunDifferenceRejected;
            const bool aHeadFailed =
                aConflict.mDifference.mHead <
                LoopFinalFarmThreholds::kMinimumHeadDifference;
            const bool aTailPartialFailed =
                aConflict.mDifference.mTailPartial <
                LoopFinalFarmThreholds::
                    kMinimumTailDifferencePartial;
            const bool aTailFullFailed =
                aConflict.mDifference.mTailFull <
                LoopFinalFarmThreholds::kMinimumTailDifferenceFull;
            std::printf(
                "rejected duplicate: nexus=%02zu score=%d "
                "conflicts-with={nexus:%02zu local:%06llu} "
                "difference={head:%zu partial:%zu full:%zu} "
                "failed={head:%s partial:%s full:%s}\n",
                aNexusIndex,
                aIntegerScore,
                aConflict.mNexusIndex,
                static_cast<unsigned long long>(
                    aConflict.mLocalIndex),
                aConflict.mDifference.mHead,
                aConflict.mDifference.mTailPartial,
                aConflict.mDifference.mTailFull,
                aHeadFailed ? "yes" : "no",
                aTailPartialFailed ? "yes" : "no",
                aTailFullFailed ? "yes" : "no");
            continue;
        }

        FinalLoopRecord aRecord;
        aRecord.mNexusIndex = aNexusIndex;
        aRecord.mSourceHeartIndex =
            LoopFinalFarmHearts::kSourceHeartIndices[aNexusIndex];
        aRecord.mLocalIndex = aNexusCounts[aNexusIndex] + 1ULL;
        aRecord.mPatternIndex = aPatternIndex;
        aRecord.mHead = aHead;
        aRecord.mHeart = aCore;
        aRecord.mTail = aTail;
        aRecord.mValues = aValues;
        aRecord.mIntegerScore = aIntegerScore;
        aRecord.mRawAttempt = aTotalRawAttempts;
        aRecord.mAcceptedOrdinal = aSaved.size() + 1ULL;
        const std::string aRecordPath = FinalLoopPath(
            pOutputFolderPath,
            aNexusIndex,
            aRecord.mLocalIndex);
        if (!SaveFinalLoopRecord(
                aRecordPath, aRecord, pErrorMessage)) {
            return false;
        }
        aSaved.push_back(aRecord);
        ++aNexusCounts[aNexusIndex];
        ++aRunAccepted;
        if (!SaveFinalFarmState(
                aStatePath,
                aTotalRawAttempts,
                aSaved.size(),
                pErrorMessage)) {
            return false;
        }
        std::printf("accepted %llu/%llu: nexus=%02zu local=%06llu "
                    "score=%d closest={head:%zu partial:%zu full:%zu} "
                    "%s\n",
                    static_cast<unsigned long long>(aRunAccepted),
                    static_cast<unsigned long long>(pNewLoopTarget),
                    aNexusIndex,
                    static_cast<unsigned long long>(aRecord.mLocalIndex),
                    aIntegerScore,
                    aClosest.mHead,
                    aClosest.mTailPartial,
                    aClosest.mTailFull,
                    aRecordPath.c_str());
    }

    if (!SaveFinalFarmState(
            aStatePath,
            aTotalRawAttempts,
            aSaved.size(),
            pErrorMessage)) {
        return false;
    }
    std::printf("final run complete: tried=%llu valid=%llu "
                "score-pass=%llu difference-reject=%llu "
                "saved=%llu/%llu\n\n",
                static_cast<unsigned long long>(aRunAttempts),
                static_cast<unsigned long long>(aRunValid),
                static_cast<unsigned long long>(aRunScorePassed),
                static_cast<unsigned long long>(aRunDifferenceRejected),
                static_cast<unsigned long long>(aRunAccepted),
                static_cast<unsigned long long>(pNewLoopTarget));
    return true;
}
