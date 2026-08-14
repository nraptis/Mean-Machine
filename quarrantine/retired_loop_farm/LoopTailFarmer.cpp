//
//  LoopTailFarmer.cpp
//  MeanMachine
//

#include "LoopTailFarmer.hpp"

#include "FileIO.hpp"
#include "LoopFinalFarmHearts.hpp"
#include "LoopFinalFarmThreholds.hpp"
#include "LoopHeadTailDifference.hpp"
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
#include <fcntl.h>
#include <iomanip>
#include <limits>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <sys/file.h>
#include <unordered_set>
#include <unistd.h>
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

class FinalFarmLock {
public:
    ~FinalFarmLock() {
        if (mFileDescriptor >= 0) {
            ::flock(mFileDescriptor, LOCK_UN);
            ::close(mFileDescriptor);
        }
    }

    bool Acquire(const std::string &pPath,
                 std::string *pErrorMessage) {
        mFileDescriptor = ::open(
            pPath.c_str(), O_CREAT | O_RDWR, 0600);
        if (mFileDescriptor < 0) {
            SetError(pErrorMessage,
                     "Final loop farm could not open its process lock: " +
                     std::string(std::strerror(errno)));
            return false;
        }
        if (::flock(mFileDescriptor, LOCK_EX | LOCK_NB) != 0) {
            SetError(pErrorMessage,
                     "Another final loop farm is already using " + pPath);
            return false;
        }
        return true;
    }

private:
    int mFileDescriptor = -1;
};

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
    aKey.reserve(kRoleCount * 2U);
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

struct Candidate {
    LoopTailPattern11 mTail;
    TailScore mScore;
    std::string mKey;
};
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
bool EvaluateFinalCandidate(
    const LoopCorePattern11 &pHeart,
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
        pHeart,
        pHead,
        pTail,
        pPatternIndex,
        pPairs,
        aTransitionMetrics,
        pWeightedOnly);
    return true;
}
std::uint64_t MixFarmSeed(std::uint64_t pValue) {
    pValue = (pValue ^ (pValue >> 30U)) *
        0xBF58476D1CE4E5B9ULL;
    pValue = (pValue ^ (pValue >> 27U)) *
        0x94D049BB133111EBULL;
    return pValue ^ (pValue >> 31U);
}

using MetricValues = std::array<int, kScoreFieldCount>;

static_assert(LoopScorer::kMetricCount == kScoreFieldCount,
              "Loop scorer must match the scoring metric count");

void AppendMetricValues(std::vector<std::uint8_t> *pBytes,
                        const MetricValues &pValues) {
    for (const int aValue : pValues) {
        Append32(pBytes, static_cast<std::uint32_t>(aValue));
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
std::uint64_t HashByte(std::uint64_t pHash,
                       const std::uint8_t pByte) {
    return (pHash ^ static_cast<std::uint64_t>(pByte)) *
        0x100000001B3ULL;
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

std::uint64_t WeightSignature() {
    std::uint64_t aHash = 0xCBF29CE484222325ULL;
    for (const LoopWeights::MetricWeight &aMetric :
         LoopWeights::kMetrics) {
        for (const char *aCharacter = aMetric.mName;
             *aCharacter != '\0';
             ++aCharacter) {
            aHash = HashByte(
                aHash, static_cast<std::uint8_t>(*aCharacter));
        }
        aHash = HashByte(aHash, 0U);
        aHash = HashByte(
            aHash, aMetric.mHigherIsBetter ? 1U : 0U);
        for (unsigned i = 0U; i < sizeof(aMetric.mWeight); ++i) {
            aHash = HashByte(
                aHash,
                static_cast<std::uint8_t>(
                    aMetric.mWeight >> (i * 8U)));
        }
    }
    return aHash;
}

std::uint64_t FinalScoringSignature() {
    std::uint64_t aHash = WeightSignature();
    // Version the per-metric integer-rounding score itself, not only the
    // weight table used to construct it.
    aHash = HashByte(aHash, 1U);
    for (const LoopScorer::Measure &aMeasure : LoopScorer::kMeasures) {
        aHash = HashByte(
            aHash, aMeasure.mHigherIsBetter ? 1U : 0U);
        std::uint32_t aWeightBits = 0U;
        static_assert(sizeof(aWeightBits) == sizeof(aMeasure.mWeight));
        std::memcpy(&aWeightBits, &aMeasure.mWeight, sizeof(aWeightBits));
        for (unsigned aByte = 0U; aByte < sizeof(aWeightBits); ++aByte) {
            aHash = HashByte(
                aHash,
                static_cast<std::uint8_t>(aWeightBits >> (aByte * 8U)));
        }
        const std::array<std::uint32_t, 2U> aLimits = {
            static_cast<std::uint32_t>(aMeasure.mMinimum),
            static_cast<std::uint32_t>(aMeasure.mMaximum),
        };
        for (const std::uint32_t aLimit : aLimits) {
            for (unsigned aByte = 0U; aByte < sizeof(aLimit); ++aByte) {
                aHash = HashByte(
                    aHash,
                    static_cast<std::uint8_t>(aLimit >> (aByte * 8U)));
            }
        }
    }
    return aHash;
}
std::array<std::uint32_t, 12U>
FinalCoreScoreValues(const LoopCorePatternScore11 &pScore) {
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

} // namespace

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
constexpr std::uint32_t kFinalLegacyVersion = 1U;
constexpr std::uint32_t kFinalLoopVersion = 2U;
constexpr std::uint32_t kFinalStateVersion = 2U;
constexpr std::size_t kFinalCoreScoreCount = 12U;
constexpr std::size_t kFinalLoopHeaderByteCount = 100U;
constexpr std::size_t kFinalLoopByteCount =
    kFinalLoopHeaderByteCount +
    (4U * kRoleCount) +
    (2U * kRoleCount) +
    (kFinalCoreScoreCount * sizeof(std::uint32_t)) +
    (kScoreFieldCount * sizeof(std::uint32_t));
constexpr std::size_t kFinalStateByteCount = 52U;
constexpr std::size_t kFinalLoopIntegrityOffset = 92U;
constexpr std::size_t kFinalStateIntegrityOffset = 28U;

static_assert(kFinalLoopByteCount == 414U);
static_assert(kFinalLoopIntegrityOffset + sizeof(std::uint64_t) ==
              kFinalLoopHeaderByteCount);
static_assert(kFinalStateIntegrityOffset +
              (3U * sizeof(std::uint64_t)) == kFinalStateByteCount);
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
    std::uint64_t aHash = FinalScoringSignature();
    for (std::size_t i = 0U;
         i < LoopFinalFarmHearts::kHeartCount;
         ++i) {
        const std::uint64_t aHeartSignature = HeartSignature(
            LoopFinalFarmHearts::kNexuses[i]);
        for (unsigned aByte = 0U;
             aByte < sizeof(aHeartSignature);
             ++aByte) {
            aHash = HashByte(
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
                aHash = HashByte(
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
            aHash = HashByte(
                aHash,
                static_cast<std::uint8_t>(
                    aDifference >> (aByte * 8U)));
        }
    }
    return aHash;
}

std::uint64_t FinalIntegrityHash(
    const std::vector<std::uint8_t> &pBytes,
    const std::size_t pIntegrityOffset) {
    std::uint64_t aHash = 0xCBF29CE484222325ULL;
    for (std::size_t i = 0U; i < pBytes.size(); ++i) {
        if ((i >= pIntegrityOffset) &&
            (i < pIntegrityOffset + sizeof(std::uint64_t))) {
            continue;
        }
        aHash = HashByte(aHash, pBytes[i]);
    }
    return aHash;
}

void Store64(std::vector<std::uint8_t> *pBytes,
             const std::size_t pOffset,
             const std::uint64_t pValue) {
    for (unsigned i = 0U; i < sizeof(pValue); ++i) {
        (*pBytes)[pOffset + i] = static_cast<std::uint8_t>(
            pValue >> (i * 8U));
    }
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
    const int aFileDescriptor = ::open(
        aTemporaryPath.c_str(),
        O_CREAT | O_TRUNC | O_WRONLY,
        0600);
    if (aFileDescriptor < 0) {
        SetError(pErrorMessage,
                 "Final loop farm could not open " + aTemporaryPath +
                 ": " + std::strerror(errno));
        return false;
    }

    std::size_t aWritten = 0U;
    while (aWritten < pBytes.size()) {
        const ssize_t aWriteCount = ::write(
            aFileDescriptor,
            pBytes.data() + aWritten,
            pBytes.size() - aWritten);
        if (aWriteCount < 0) {
            if (errno == EINTR) {
                continue;
            }
            const std::string aReason = std::strerror(errno);
            ::close(aFileDescriptor);
            std::error_code aCleanupError;
            std::filesystem::remove(aTemporaryPath, aCleanupError);
            SetError(pErrorMessage,
                     "Final loop farm could not write " +
                     aTemporaryPath + ": " + aReason);
            return false;
        }
        if (aWriteCount == 0) {
            ::close(aFileDescriptor);
            std::error_code aCleanupError;
            std::filesystem::remove(aTemporaryPath, aCleanupError);
            SetError(pErrorMessage,
                     "Final loop farm made no progress writing " +
                     aTemporaryPath);
            return false;
        }
        aWritten += static_cast<std::size_t>(aWriteCount);
    }

    bool aDidFlush = false;
#if defined(F_FULLFSYNC)
    aDidFlush = ::fcntl(aFileDescriptor, F_FULLFSYNC) == 0;
#endif
    if (!aDidFlush) {
        aDidFlush = ::fsync(aFileDescriptor) == 0;
    }
    if (!aDidFlush) {
        const std::string aReason = std::strerror(errno);
        ::close(aFileDescriptor);
        std::error_code aCleanupError;
        std::filesystem::remove(aTemporaryPath, aCleanupError);
        SetError(pErrorMessage,
                 "Final loop farm could not flush " + aTemporaryPath +
                 ": " + aReason);
        return false;
    }
    if (::close(aFileDescriptor) != 0) {
        const std::string aReason = std::strerror(errno);
        std::error_code aCleanupError;
        std::filesystem::remove(aTemporaryPath, aCleanupError);
        SetError(pErrorMessage,
                 "Final loop farm could not close " + aTemporaryPath +
                 ": " + aReason);
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

    const std::filesystem::path aParentPath =
        std::filesystem::path(pPath).parent_path();
    const int aDirectoryDescriptor = ::open(
        aParentPath.c_str(), O_RDONLY);
    if (aDirectoryDescriptor < 0) {
        SetError(pErrorMessage,
                 "Final loop farm could not open its output directory " +
                 aParentPath.generic_string() + ": " +
                 std::strerror(errno));
        return false;
    }
    if ((::fsync(aDirectoryDescriptor) != 0) &&
        (errno != EINVAL)) {
        const std::string aReason = std::strerror(errno);
        ::close(aDirectoryDescriptor);
        SetError(pErrorMessage,
                 "Final loop farm could not flush its output directory " +
                 aParentPath.generic_string() + ": " + aReason);
        return false;
    }
    if (::close(aDirectoryDescriptor) != 0) {
        SetError(pErrorMessage,
                 "Final loop farm could not close its output directory " +
                 aParentPath.generic_string() + ": " +
                 std::strerror(errno));
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
    Append64(&aBytes, HeartSignature(pRecord.mHeart));
    Append64(&aBytes, 0ULL);

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
         FinalCoreScoreValues(pRecord.mHeart.mScore)) {
        Append32(&aBytes, aValue);
    }
    AppendMetricValues(&aBytes, pRecord.mValues);
    if (aBytes.size() != kFinalLoopByteCount) {
        SetError(pErrorMessage,
                 "Final loop farm built an invalid record size");
        return false;
    }
    Store64(&aBytes,
            kFinalLoopIntegrityOffset,
            FinalIntegrityHash(aBytes, kFinalLoopIntegrityOffset));
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
    const bool aIsLegacyVersion =
        aVersion == kFinalLegacyVersion;
    const bool aIsCurrentVersion =
        aVersion == kFinalLoopVersion;
    const bool aIntegrityIsValid = aIsLegacyVersion
        ? aConfigurationSignature != 0ULL
        : (aIsCurrentVersion &&
           (aConfigurationSignature == FinalIntegrityHash(
                aBytes, kFinalLoopIntegrityOffset)));
    if ((!aIsLegacyVersion && !aIsCurrentVersion) ||
        (aRoleCount != kRoleCount) ||
        (aMetricCount != kScoreFieldCount) ||
        (aByteCount != kFinalLoopByteCount) ||
        (aNexusIndex != pExpectedNexusIndex) ||
        (aSourceHeartIndex != aExpectedSourceHeartIndex) ||
        (aLocalIndex != pExpectedLocalIndex) ||
        (aPatternIndex >= LoopHeadFarmer::kRetainedPatternCount) ||
        (aMinimumHead > kRoleCount) ||
        (aMinimumTailPartial > kRoleCount) ||
        (aMinimumTailFull > kRoleCount) ||
        (aHeartSignature != HeartSignature(aExpectedHeart)) ||
        !aIntegrityIsValid ||
        (aIntegerScore < aMinimumScore)) {
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
        FinalCoreScoreValues(aExpectedHeart.mScore);
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

    const DistanceMatrix aDistances =
        HeartTemporalDistances(aExpectedHeart);
    const PairInfoMatrix aPairs = MakePairInfo(
        aExpectedHeart,
        aRecord.mHead,
        aRecord.mPatternIndex,
        aDistances);
    Candidate aEvaluated;
    if (!EvaluateFinalCandidate(
            aExpectedHeart,
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
    Append64(&aBytes, 0ULL);
    Append64(&aBytes, pRawAttempts);
    Append64(&aBytes, pAcceptedCount);
    if (aBytes.size() != kFinalStateByteCount) {
        SetError(pErrorMessage,
                 "Final loop farm built an invalid state size");
        return false;
    }
    Store64(&aBytes,
            kFinalStateIntegrityOffset,
            FinalIntegrityHash(aBytes, kFinalStateIntegrityOffset));
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
        std::printf(
            "ignoring corrupt final farm state; rebuilding from loop "
            "records: %s\n",
            pPath.c_str());
        return true;
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
    const bool aIsLegacyVersion =
        aVersion == kFinalLegacyVersion;
    const bool aIsCurrentVersion =
        aVersion == kFinalStateVersion;
    const bool aIntegrityIsValid = aIsLegacyVersion
        ? aConfigurationSignature != 0ULL
        : (aIsCurrentVersion &&
           (aConfigurationSignature == FinalIntegrityHash(
                aBytes, kFinalStateIntegrityOffset)));
    if ((!aIsLegacyVersion && !aIsCurrentVersion) ||
        (aNexusCount != LoopFinalFarmHearts::kHeartCount) ||
        (aMinimumHead > kRoleCount) ||
        (aMinimumTailPartial > kRoleCount) ||
        (aMinimumTailFull > kRoleCount) ||
        !aIntegrityIsValid ||
        (aOffset != aBytes.size())) {
        std::printf(
            "ignoring invalid final farm state metadata; rebuilding "
            "from loop records: %s\n",
            pPath.c_str());
        return true;
    }
    if ((aMinimumHead !=
         LoopFinalFarmThreholds::kMinimumHeadDifference) ||
        (aMinimumTailPartial !=
         LoopFinalFarmThreholds::kMinimumTailDifferencePartial) ||
        (aMinimumTailFull !=
         LoopFinalFarmThreholds::kMinimumTailDifferenceFull) ||
        (aIsLegacyVersion &&
         (aConfigurationSignature != FinalConfigurationSignature()))) {
        std::printf(
            "resuming final farm with updated policy: "
            "stored={head:%u partial:%u full:%u} "
            "current={head:%zu partial:%zu full:%zu}\n",
            aMinimumHead,
            aMinimumTailPartial,
            aMinimumTailFull,
            LoopFinalFarmThreholds::kMinimumHeadDifference,
            LoopFinalFarmThreholds::kMinimumTailDifferencePartial,
            LoopFinalFarmThreholds::kMinimumTailDifferenceFull);
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

bool ParseFinalLoopNexusIndex(
    const std::filesystem::path &pPath,
    std::size_t *pNexusIndex) {
    const std::string aFolderName =
        pPath.parent_path().filename().string();
    constexpr const char *kPrefix = "nexus_";
    if ((aFolderName.size() <= 6U) ||
        (aFolderName.compare(0U, 6U, kPrefix) != 0)) {
        return false;
    }

    std::size_t aConsumed = 0U;
    std::uint64_t aValue = 0ULL;
    try {
        aValue = std::stoull(aFolderName.substr(6U), &aConsumed, 10);
    } catch (...) {
        return false;
    }
    if ((aConsumed != (aFolderName.size() - 6U)) ||
        (aValue >= LoopFinalFarmHearts::kHeartCount)) {
        return false;
    }
    *pNexusIndex = static_cast<std::size_t>(aValue);
    return true;
}

void PrintFinalLoopRecord(const std::string &pPath,
                          const FinalLoopRecord &pRecord) {
    std::printf("\nFINAL NEXUS LOOP STRUCTURE\n");
    std::printf("file: %s\n", pPath.c_str());
    std::printf("nexus=%02zu source-heart=%zu local=%06llu "
                "pattern=%zu score=%d raw-attempt=%llu "
                "accepted=%llu\n\n",
                pRecord.mNexusIndex,
                pRecord.mSourceHeartIndex,
                static_cast<unsigned long long>(pRecord.mLocalIndex),
                pRecord.mPatternIndex,
                pRecord.mIntegerScore,
                static_cast<unsigned long long>(pRecord.mRawAttempt),
                static_cast<unsigned long long>(
                    pRecord.mAcceptedOrdinal));

    std::printf("HEAD — ORBITER ASSIGNMENTS\n");
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        std::printf("  Orbiter %c <- Wanderer %c\n",
                    static_cast<char>('A' + i),
                    static_cast<char>(
                        'A' + pRecord.mHead.mWandererForOrbiter[i]));
    }

    std::printf("\nHEART — CORE ROUNDS {lead, source, feedback}\n");
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::array<std::uint8_t, 3U> &aRound =
            pRecord.mHeart.mRounds[i];
        std::printf("  Round %c: {%c, %c, %c}\n",
                    static_cast<char>('A' + i),
                    static_cast<char>('A' + aRound[0]),
                    static_cast<char>('A' + aRound[1]),
                    static_cast<char>('A' + aRound[2]));
    }

    std::printf("\nTAIL — WANDERER UPDATES\n");
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        std::printf("  Wanderer %c <- Orbiter %c + Orbiter %c\n",
                    static_cast<char>('A' + i),
                    static_cast<char>(
                        'A' + pRecord.mTail.mOrbiterAForWanderer[i]),
                    static_cast<char>(
                        'A' + pRecord.mTail.mOrbiterBForWanderer[i]));
    }
    std::printf("\n");
}

} // namespace

bool LoopTailFarmer::PrintFinalLoop(
    const std::string &pPath,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    const std::string aResolvedPath = ResolvedPath(pPath);
    const std::filesystem::path aPath(aResolvedPath);
    std::size_t aNexusIndex = 0U;
    std::uint64_t aLocalIndex = 0ULL;
    if (!ParseFinalLoopNexusIndex(aPath, &aNexusIndex) ||
        !ParseFinalLoopLocalIndex(aPath, &aLocalIndex)) {
        SetError(pErrorMessage,
                 "Final loop path did not identify a nexus and loop: " +
                 aResolvedPath);
        return false;
    }

    FinalLoopRecord aRecord;
    if (!LoadFinalLoopRecord(
            aResolvedPath,
            aNexusIndex,
            aLocalIndex,
            &aRecord,
            pErrorMessage)) {
        return false;
    }
    PrintFinalLoopRecord(aResolvedPath, aRecord);
    return true;
}

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

    FinalFarmLock aFarmLock;
    if (!aFarmLock.Acquire(
            (std::filesystem::path(aOutputFolder) /
             ".final_farm.lock").generic_string(),
            pErrorMessage)) {
        return false;
    }

    std::array<std::uint64_t,
               LoopFinalFarmHearts::kHeartCount> aNexusCounts{};
    std::array<std::uint64_t,
               LoopFinalFarmHearts::kHeartCount> aNextLocalIndices{};
    std::array<std::unordered_set<std::uint64_t>,
               LoopFinalFarmHearts::kHeartCount> aLocalIndices;
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
                    std::printf(
                        "ignoring unrelated final farm file: %s\n",
                        aEntry.path().generic_string().c_str());
                    aIterator.increment(aEnumerateError);
                    continue;
                }
                std::uint64_t aLocalIndex = 0ULL;
                if (!ParseFinalLoopLocalIndex(
                        aEntry.path(), &aLocalIndex)) {
                    std::printf(
                        "ignoring invalid final farm filename: %s\n",
                        aEntry.path().generic_string().c_str());
                    aIterator.increment(aEnumerateError);
                    continue;
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
        for (const auto &aPath : aPaths) {
            if (aLocalIndices[aNexusIndex].find(aPath.first) !=
                aLocalIndices[aNexusIndex].end()) {
                std::printf(
                    "ignoring duplicate final farm index: %s\n",
                    aPath.second.generic_string().c_str());
                continue;
            }
            FinalLoopRecord aRecord;
            std::string aRecordError;
            if (!LoadFinalLoopRecord(
                    aPath.second.generic_string(),
                    aNexusIndex,
                    aPath.first,
                    &aRecord,
                    &aRecordError)) {
                std::printf(
                    "ignoring corrupt final loop; its slot will be "
                    "overwritten: %s\nreason: %s\n",
                    aPath.second.generic_string().c_str(),
                    aRecordError.c_str());
                continue;
            }
            aLocalIndices[aNexusIndex].insert(aPath.first);
            aSaved.push_back(std::move(aRecord));
        }
        aNexusCounts[aNexusIndex] =
            aLocalIndices[aNexusIndex].size();
        aNextLocalIndices[aNexusIndex] = 1ULL;
        while (aLocalIndices[aNexusIndex].find(
                   aNextLocalIndices[aNexusIndex]) !=
               aLocalIndices[aNexusIndex].end()) {
            ++aNextLocalIndices[aNexusIndex];
        }
    }

    std::sort(aSaved.begin(), aSaved.end(),
              [](const FinalLoopRecord &pA,
                 const FinalLoopRecord &pB) {
        return pA.mAcceptedOrdinal < pB.mAcceptedOrdinal;
    });
    std::uint64_t aMaximumRecordAttempt = 0ULL;
    std::uint64_t aMaximumAcceptedOrdinal = 0ULL;
    for (const FinalLoopRecord &aRecord : aSaved) {
        aMaximumRecordAttempt = std::max(
            aMaximumRecordAttempt, aRecord.mRawAttempt);
        aMaximumAcceptedOrdinal = std::max(
            aMaximumAcceptedOrdinal, aRecord.mAcceptedOrdinal);
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
    if (aFoundState && (aStateAcceptedCount != aSaved.size())) {
        std::printf(
            "final farm state count differed from recoverable records: "
            "state=%llu records=%zu; using records\n",
            static_cast<unsigned long long>(aStateAcceptedCount),
            aSaved.size());
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
    std::uint64_t aRunHeadRejected = 0ULL;
    std::uint64_t aRunTailPartialRejected = 0ULL;
    std::uint64_t aRunTailFullRejected = 0ULL;
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
                        "{head:%llu partial:%llu full:%llu} "
                        "run-saved=%llu total=%zu next=%02zu\n",
                        static_cast<unsigned long long>(aRunAttempts),
                        static_cast<unsigned long long>(aRunValid),
                        static_cast<unsigned long long>(aRunScorePassed),
                        static_cast<unsigned long long>(
                            aRunDifferenceRejected),
                        static_cast<unsigned long long>(
                            aRunHeadRejected),
                        static_cast<unsigned long long>(
                            aRunTailPartialRejected),
                        static_cast<unsigned long long>(
                            aRunTailFullRejected),
                        static_cast<unsigned long long>(aRunAccepted),
                        aSaved.size(),
                        FinalNextNexus(aNexusCounts));
        }

        const std::size_t aNexusIndex =
            FinalNextNexus(aNexusCounts);
        const LoopCorePattern11 &aCore =
            LoopFinalFarmHearts::kNexuses[aNexusIndex];
        Generator aGenerator(MixFarmSeed(
            0x4E45585553464152ULL ^
            HeartSignature(aCore) ^
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
            !EvaluateFinalCandidate(
                aCore,
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
            aRunHeadRejected += aHeadFailed;
            aRunTailPartialRejected += aTailPartialFailed;
            aRunTailFullRejected += aTailFullFailed;
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
        aRecord.mLocalIndex = aNextLocalIndices[aNexusIndex];
        aRecord.mPatternIndex = aPatternIndex;
        aRecord.mHead = aHead;
        aRecord.mHeart = aCore;
        aRecord.mTail = aTail;
        aRecord.mValues = aValues;
        aRecord.mIntegerScore = aIntegerScore;
        aRecord.mRawAttempt = aTotalRawAttempts;
        aRecord.mAcceptedOrdinal = aMaximumAcceptedOrdinal + 1ULL;
        const std::string aRecordPath = FinalLoopPath(
            pOutputFolderPath,
            aNexusIndex,
            aRecord.mLocalIndex);
        if (!SaveFinalLoopRecord(
                aRecordPath, aRecord, pErrorMessage)) {
            return false;
        }
        aSaved.push_back(aRecord);
        aMaximumAcceptedOrdinal = aRecord.mAcceptedOrdinal;
        aLocalIndices[aNexusIndex].insert(aRecord.mLocalIndex);
        do {
            ++aNextLocalIndices[aNexusIndex];
        } while (aLocalIndices[aNexusIndex].find(
                     aNextLocalIndices[aNexusIndex]) !=
                 aLocalIndices[aNexusIndex].end());
        ++aNexusCounts[aNexusIndex];
        ++aRunAccepted;
        if (!SaveFinalFarmState(
                aStatePath,
                aTotalRawAttempts,
                aSaved.size(),
                pErrorMessage)) {
            return false;
        }
        std::printf("accepted: run=%llu total=%zu nexus=%02zu "
                    "local=%06llu "
                    "score=%d closest={head:%zu partial:%zu full:%zu} "
                    "%s\n",
                    static_cast<unsigned long long>(aRunAccepted),
                    aSaved.size(),
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
                "{head:%llu partial:%llu full:%llu} saved=%llu\n\n",
                static_cast<unsigned long long>(aRunAttempts),
                static_cast<unsigned long long>(aRunValid),
                static_cast<unsigned long long>(aRunScorePassed),
                static_cast<unsigned long long>(aRunDifferenceRejected),
                static_cast<unsigned long long>(aRunHeadRejected),
                static_cast<unsigned long long>(aRunTailPartialRejected),
                static_cast<unsigned long long>(aRunTailFullRejected),
                static_cast<unsigned long long>(aRunAccepted));
    return true;
}
