#import <XCTest/XCTest.h>

#include "LoopScaffoldCores.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

namespace {

using LoopScaffoldCores::CoreRound;
using LoopScaffoldCores::kCoreCount;
using LoopScaffoldCores::kCores;
using LoopScaffoldCores::kRoleCount;

using Core = std::array<CoreRound, kRoleCount>;
using Graph = std::array<std::array<bool, kRoleCount>, kRoleCount>;

struct CoreMeasurement {
    std::size_t mCoreIndex = 0U;
    int mDirectedEdgeCount = 0;
    int mUndirectedEdgeCount = 0;
    int mDuplicateEncounterCount = 0;
    int mReciprocalDirectedPairCount = 0;
    int mMinimumInDegree = 0;
    int mMaximumInDegree = 0;
    int mMinimumOutDegree = 0;
    int mMaximumOutDegree = 0;
    int mDirectedDiameter = 0;
    int mUndirectedDiameter = 0;
    int mArticulationCount = 0;
    int mBridgeCount = 0;
    int mMinimumEdgeCut = 0;
    int mMinimumJourneyPartners = 0;
    int mMaximumJourneyPartners = 0;
    int mMaximumJourneyDuplicates = 0;
    int mMinimumDestinationInfluence = 0;
    int mMaximumDestinationInfluence = 0;
    int mMinimumSourceReach = 0;
    int mMaximumSourceReach = 0;
    int mTemporalInfluenceTotal = 0;
    int mLongestGrowthStall = 0;
    std::array<int, kRoleCount> mInfluenceCurve{};
};

int PopCount(const std::uint16_t pValue) {
    return __builtin_popcount(static_cast<unsigned int>(pValue));
}

Graph DirectedGraph(const Core &pCore) {
    Graph aGraph{};
    for (const CoreRound &aRound : pCore) {
        aGraph[aRound.mSource][aRound.mLead] = true;
        aGraph[aRound.mLead][aRound.mFeedback] = true;
    }
    return aGraph;
}

Graph UndirectedGraph(const Core &pCore) {
    Graph aGraph{};
    for (const CoreRound &aRound : pCore) {
        aGraph[aRound.mSource][aRound.mLead] = true;
        aGraph[aRound.mLead][aRound.mSource] = true;
        aGraph[aRound.mLead][aRound.mFeedback] = true;
        aGraph[aRound.mFeedback][aRound.mLead] = true;
    }
    return aGraph;
}

int GraphDiameter(const Graph &pGraph,
                  const bool pDirected) {
    int aDiameter = 0;
    for (std::size_t aStart = 0U;
         aStart < kRoleCount;
         ++aStart) {
        std::array<int, kRoleCount> aDistance{};
        aDistance.fill(-1);
        std::queue<std::size_t> aQueue;
        aDistance[aStart] = 0;
        aQueue.push(aStart);
        while (!aQueue.empty()) {
            const std::size_t aNode = aQueue.front();
            aQueue.pop();
            for (std::size_t aNext = 0U;
                 aNext < kRoleCount;
                 ++aNext) {
                const bool aConnected = pDirected
                    ? pGraph[aNode][aNext]
                    : (pGraph[aNode][aNext] ||
                       pGraph[aNext][aNode]);
                if (aConnected && (aDistance[aNext] < 0)) {
                    aDistance[aNext] = aDistance[aNode] + 1;
                    aQueue.push(aNext);
                }
            }
        }
        for (const int aValue : aDistance) {
            if (aValue < 0) {
                return std::numeric_limits<int>::max();
            }
            aDiameter = std::max(aDiameter, aValue);
        }
    }
    return aDiameter;
}

void SearchCuts(const Graph &pGraph,
                const std::size_t pNode,
                const std::size_t pParent,
                int *pClock,
                std::array<int, kRoleCount> *pDiscovery,
                std::array<int, kRoleCount> *pLow,
                std::array<bool, kRoleCount> *pArticulation,
                int *pBridgeCount) {
    (*pDiscovery)[pNode] = ++(*pClock);
    (*pLow)[pNode] = (*pDiscovery)[pNode];
    int aChildCount = 0;

    for (std::size_t aNext = 0U;
         aNext < kRoleCount;
         ++aNext) {
        if (!pGraph[pNode][aNext]) {
            continue;
        }
        if ((*pDiscovery)[aNext] == 0) {
            ++aChildCount;
            SearchCuts(pGraph,
                       aNext,
                       pNode,
                       pClock,
                       pDiscovery,
                       pLow,
                       pArticulation,
                       pBridgeCount);
            (*pLow)[pNode] = std::min((*pLow)[pNode],
                                      (*pLow)[aNext]);
            if ((pParent != kRoleCount) &&
                ((*pLow)[aNext] >= (*pDiscovery)[pNode])) {
                (*pArticulation)[pNode] = true;
            }
            if ((*pLow)[aNext] > (*pDiscovery)[pNode]) {
                ++(*pBridgeCount);
            }
        } else if (aNext != pParent) {
            (*pLow)[pNode] = std::min((*pLow)[pNode],
                                      (*pDiscovery)[aNext]);
        }
    }
    if ((pParent == kRoleCount) && (aChildCount > 1)) {
        (*pArticulation)[pNode] = true;
    }
}

std::pair<int, int> ArticulationsAndBridges(
    const Graph &pGraph) {
    std::array<int, kRoleCount> aDiscovery{};
    std::array<int, kRoleCount> aLow{};
    std::array<bool, kRoleCount> aArticulation{};
    int aClock = 0;
    int aBridgeCount = 0;
    SearchCuts(pGraph,
               0U,
               kRoleCount,
               &aClock,
               &aDiscovery,
               &aLow,
               &aArticulation,
               &aBridgeCount);
    return {
        static_cast<int>(std::count(aArticulation.begin(),
                                    aArticulation.end(),
                                    true)),
        aBridgeCount,
    };
}

int MinimumEdgeCut(const Graph &pGraph) {
    int aMinimum = std::numeric_limits<int>::max();
    const std::uint32_t aLimit = 1U << kRoleCount;
    // Keep role zero on the left to avoid evaluating both a cut and its
    // complement. Skip the empty and complete sides.
    for (std::uint32_t aMask = 1U;
         aMask < (aLimit - 1U);
         aMask += 2U) {
        int aCut = 0;
        for (std::size_t i = 0U; i < kRoleCount; ++i) {
            for (std::size_t j = i + 1U; j < kRoleCount; ++j) {
                if (pGraph[i][j] &&
                    (((aMask >> i) & 1U) !=
                     ((aMask >> j) & 1U))) {
                    ++aCut;
                }
            }
        }
        aMinimum = std::min(aMinimum, aCut);
    }
    return aMinimum;
}

CoreMeasurement MeasureCore(const std::size_t pCoreIndex) {
    const Core &aCore = kCores[pCoreIndex];
    const Graph aDirected = DirectedGraph(aCore);
    const Graph aUndirected = UndirectedGraph(aCore);
    CoreMeasurement aResult;
    aResult.mCoreIndex = pCoreIndex;

    std::array<int, kRoleCount> aInDegrees{};
    std::array<int, kRoleCount> aOutDegrees{};
    std::array<std::array<int, kRoleCount>, kRoleCount>
        aEncounterCounts{};
    std::array<std::vector<std::size_t>, kRoleCount> aJourneys;
    for (const CoreRound &aRound : aCore) {
        const std::array<std::pair<std::size_t, std::size_t>, 2U>
            aEncounters = {{
                {aRound.mSource, aRound.mLead},
                {aRound.mLead, aRound.mFeedback},
            }};
        for (const auto &aEncounter : aEncounters) {
            const std::size_t aA = aEncounter.first;
            const std::size_t aB = aEncounter.second;
            ++aEncounterCounts[aA][aB];
            ++aEncounterCounts[aB][aA];
            aJourneys[aA].push_back(aB);
            aJourneys[aB].push_back(aA);
        }
    }

    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        for (std::size_t j = 0U; j < kRoleCount; ++j) {
            if (aDirected[i][j]) {
                ++aResult.mDirectedEdgeCount;
                ++aOutDegrees[i];
                ++aInDegrees[j];
            }
            if ((j > i) && aUndirected[i][j]) {
                ++aResult.mUndirectedEdgeCount;
                aResult.mDuplicateEncounterCount +=
                    std::max(0, aEncounterCounts[i][j] - 1);
            }
            if ((j > i) && aDirected[i][j] && aDirected[j][i]) {
                ++aResult.mReciprocalDirectedPairCount;
            }
        }
    }
    const auto aInRange = std::minmax_element(aInDegrees.begin(),
                                              aInDegrees.end());
    const auto aOutRange = std::minmax_element(aOutDegrees.begin(),
                                               aOutDegrees.end());
    aResult.mMinimumInDegree = *aInRange.first;
    aResult.mMaximumInDegree = *aInRange.second;
    aResult.mMinimumOutDegree = *aOutRange.first;
    aResult.mMaximumOutDegree = *aOutRange.second;
    aResult.mDirectedDiameter = GraphDiameter(aDirected, true);
    aResult.mUndirectedDiameter = GraphDiameter(aUndirected, false);
    const auto aCuts = ArticulationsAndBridges(aUndirected);
    aResult.mArticulationCount = aCuts.first;
    aResult.mBridgeCount = aCuts.second;
    aResult.mMinimumEdgeCut = MinimumEdgeCut(aUndirected);

    aResult.mMinimumJourneyPartners =
        static_cast<int>(kRoleCount);
    for (const auto &aJourney : aJourneys) {
        std::array<bool, kRoleCount> aSeen{};
        for (const std::size_t aPartner : aJourney) {
            aSeen[aPartner] = true;
        }
        const int aUnique = static_cast<int>(
            std::count(aSeen.begin(), aSeen.end(), true));
        aResult.mMinimumJourneyPartners = std::min(
            aResult.mMinimumJourneyPartners,
            aUnique);
        aResult.mMaximumJourneyPartners = std::max(
            aResult.mMaximumJourneyPartners,
            aUnique);
        aResult.mMaximumJourneyDuplicates = std::max(
            aResult.mMaximumJourneyDuplicates,
            static_cast<int>(aJourney.size()) - aUnique);
    }

    std::array<std::uint16_t, kRoleCount> aInfluence{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aInfluence[i] = static_cast<std::uint16_t>(1U << i);
    }
    int aPreviousTotal = static_cast<int>(kRoleCount);
    int aCurrentStall = 0;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const CoreRound &aRound = aCore[i];
        aInfluence[aRound.mLead] = static_cast<std::uint16_t>(
            aInfluence[aRound.mLead] |
            aInfluence[aRound.mSource]);
        aInfluence[aRound.mFeedback] = static_cast<std::uint16_t>(
            aInfluence[aRound.mFeedback] |
            aInfluence[aRound.mLead]);
        int aTotal = 0;
        for (const std::uint16_t aValue : aInfluence) {
            aTotal += PopCount(aValue);
        }
        aResult.mInfluenceCurve[i] = aTotal;
        if (aTotal == aPreviousTotal) {
            ++aCurrentStall;
            aResult.mLongestGrowthStall = std::max(
                aResult.mLongestGrowthStall,
                aCurrentStall);
        } else {
            aCurrentStall = 0;
        }
        aPreviousTotal = aTotal;
    }

    aResult.mMinimumDestinationInfluence =
        static_cast<int>(kRoleCount);
    std::array<int, kRoleCount> aSourceReach{};
    for (const std::uint16_t aValue : aInfluence) {
        const int aCount = PopCount(aValue);
        aResult.mMinimumDestinationInfluence = std::min(
            aResult.mMinimumDestinationInfluence,
            aCount);
        aResult.mMaximumDestinationInfluence = std::max(
            aResult.mMaximumDestinationInfluence,
            aCount);
        aResult.mTemporalInfluenceTotal += aCount;
        for (std::size_t aSource = 0U;
             aSource < kRoleCount;
             ++aSource) {
            aSourceReach[aSource] +=
                (aValue & (1U << aSource)) != 0U;
        }
    }
    const auto aReachRange = std::minmax_element(aSourceReach.begin(),
                                                aSourceReach.end());
    aResult.mMinimumSourceReach = *aReachRange.first;
    aResult.mMaximumSourceReach = *aReachRange.second;
    return aResult;
}

bool EquivalentUnderTransform(
    const Core &pA,
    const Core &pB,
    const std::size_t pRoundOffset,
    const bool pReverseRounds,
    const std::array<std::size_t, 3U> &pPositions,
    std::array<int, kRoleCount> *pResultMap = nullptr) {
    std::array<int, kRoleCount> aMap{};
    std::array<int, kRoleCount> aReverseMap{};
    aMap.fill(-1);
    aReverseMap.fill(-1);

    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::size_t aBIndex = pReverseRounds
            ? ((pRoundOffset + kRoleCount - i) % kRoleCount)
            : ((pRoundOffset + i) % kRoleCount);
        const CoreRound &aRoundA = pA[i];
        const CoreRound &aRoundB = pB[aBIndex];
        const std::array<std::uint8_t, 3U> aRolesA = {
            aRoundA.mLead,
            aRoundA.mSource,
            aRoundA.mFeedback,
        };
        const std::array<std::uint8_t, 3U> aRolesB = {
            aRoundB.mLead,
            aRoundB.mSource,
            aRoundB.mFeedback,
        };
        for (std::size_t p = 0U; p < 3U; ++p) {
            const std::size_t aFrom = aRolesA[p];
            const std::size_t aTo = aRolesB[pPositions[p]];
            if (((aMap[aFrom] >= 0) &&
                 (aMap[aFrom] != static_cast<int>(aTo))) ||
                ((aReverseMap[aTo] >= 0) &&
                 (aReverseMap[aTo] != static_cast<int>(aFrom)))) {
                return false;
            }
            aMap[aFrom] = static_cast<int>(aTo);
            aReverseMap[aTo] = static_cast<int>(aFrom);
        }
    }
    if (std::find(aMap.begin(), aMap.end(), -1) != aMap.end()) {
        return false;
    }
    if (pResultMap != nullptr) {
        *pResultMap = aMap;
    }
    return true;
}

bool PermutationIsEven(
    const std::array<int, kRoleCount> &pValues) {
    int aInversions = 0;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        for (std::size_t j = i + 1U; j < kRoleCount; ++j) {
            aInversions += pValues[i] > pValues[j];
        }
    }
    return (aInversions & 1) == 0;
}

bool EquivalentByRelabeling(const Core &pA,
                            const Core &pB) {
    return EquivalentUnderTransform(
        pA, pB, 0U, false, {0U, 1U, 2U});
}

bool EquivalentByCyclicRelabeling(const Core &pA,
                                  const Core &pB) {
    for (std::size_t aOffset = 0U;
         aOffset < kRoleCount;
         ++aOffset) {
        if (EquivalentUnderTransform(
                pA, pB, aOffset, false, {0U, 1U, 2U})) {
            return true;
        }
    }
    return false;
}

bool EquivalentAsUnorientedTripletShape(const Core &pA,
                                        const Core &pB) {
    std::array<std::size_t, 3U> aPositions = {0U, 1U, 2U};
    do {
        for (const bool aReverse : {false, true}) {
            for (std::size_t aOffset = 0U;
                 aOffset < kRoleCount;
                 ++aOffset) {
                if (EquivalentUnderTransform(
                        pA,
                        pB,
                        aOffset,
                        aReverse,
                        aPositions)) {
                    return true;
                }
            }
        }
    } while (std::next_permutation(aPositions.begin(),
                                   aPositions.end()));
    return false;
}

void PrintMeasurement(const CoreMeasurement &pValue) {
    printf("CORE %zu\n", pValue.mCoreIndex);
    printf("    graph: directed_edges=%d undirected_edges=%d "
           "duplicates=%d reciprocal=%d\n",
           pValue.mDirectedEdgeCount,
           pValue.mUndirectedEdgeCount,
           pValue.mDuplicateEncounterCount,
           pValue.mReciprocalDirectedPairCount);
    printf("    degree: in=%d..%d out=%d..%d "
           "directed_diameter=%d undirected_diameter=%d\n",
           pValue.mMinimumInDegree,
           pValue.mMaximumInDegree,
           pValue.mMinimumOutDegree,
           pValue.mMaximumOutDegree,
           pValue.mDirectedDiameter,
           pValue.mUndirectedDiameter);
    printf("    cuts: articulation=%d bridges=%d min_edge_cut=%d\n",
           pValue.mArticulationCount,
           pValue.mBridgeCount,
           pValue.mMinimumEdgeCut);
    printf("    journey: unique_partners=%d..%d "
           "max_duplicate_encounters=%d\n",
           pValue.mMinimumJourneyPartners,
           pValue.mMaximumJourneyPartners,
           pValue.mMaximumJourneyDuplicates);
    printf("    temporal: destination_sources=%d..%d "
           "source_reach=%d..%d total=%d stall=%d\n",
           pValue.mMinimumDestinationInfluence,
           pValue.mMaximumDestinationInfluence,
           pValue.mMinimumSourceReach,
           pValue.mMaximumSourceReach,
           pValue.mTemporalInfluenceTotal,
           pValue.mLongestGrowthStall);
    printf("    curve:");
    for (const int aValue : pValue.mInfluenceCurve) {
        printf(" %d", aValue);
    }
    printf("\n");
}

} // namespace

@interface CoreMeasureTest : XCTestCase
@end

@implementation CoreMeasureTest

- (void)testMeasureCoreShapes {
    printf("\n============================================================\n");
    printf("CORE MEASUREMENTS\n");
    printf("============================================================\n");

    std::vector<CoreMeasurement> aMeasurements;
    for (std::size_t i = 0U; i < kCoreCount; ++i) {
        const CoreMeasurement aMeasurement = MeasureCore(i);
        aMeasurements.push_back(aMeasurement);
        PrintMeasurement(aMeasurement);

        XCTAssertEqual(aMeasurement.mDirectedEdgeCount > 0, true);
        XCTAssertNotEqual(aMeasurement.mDirectedDiameter,
                          std::numeric_limits<int>::max());
        XCTAssertEqual(aMeasurement.mArticulationCount, 0);
        XCTAssertEqual(aMeasurement.mBridgeCount, 0);
    }

    std::sort(aMeasurements.begin(),
              aMeasurements.end(),
              [](const CoreMeasurement &pA,
                 const CoreMeasurement &pB) {
        const auto Grade = [](const CoreMeasurement &pValue) {
            return std::make_tuple(
                std::min(pValue.mMinimumSourceReach,
                         pValue.mMinimumDestinationInfluence),
                pValue.mMinimumSourceReach +
                    pValue.mMinimumDestinationInfluence,
                pValue.mTemporalInfluenceTotal,
                pValue.mMinimumJourneyPartners,
                pValue.mMinimumEdgeCut,
                -pValue.mDirectedDiameter);
        };
        return Grade(pA) > Grade(pB);
    });
    printf("    diagnostic order:");
    for (const CoreMeasurement &aValue : aMeasurements) {
        printf(" %zu", aValue.mCoreIndex);
    }
    printf("\n");
}

- (void)testMeasureCoreEquivalenceClasses {
    printf("\n============================================================\n");
    printf("CORE EQUIVALENCE\n");
    printf("E=exact relabel, R=round rotation + relabel, "
           "S=unoriented shape, -=distinct\n");
    printf("============================================================\n    ");
    for (std::size_t j = 0U; j < kCoreCount; ++j) {
        printf(" %zu", j);
    }
    printf("\n");
    for (std::size_t i = 0U; i < kCoreCount; ++i) {
        printf("%zu:  ", i);
        for (std::size_t j = 0U; j < kCoreCount; ++j) {
            char aKind = '-';
            if (EquivalentByRelabeling(kCores[i], kCores[j])) {
                aKind = 'E';
            } else if (EquivalentByCyclicRelabeling(
                           kCores[i], kCores[j])) {
                aKind = 'R';
            } else if (EquivalentAsUnorientedTripletShape(
                           kCores[i], kCores[j])) {
                aKind = 'S';
            }
            printf(" %c", aKind);
        }
        printf("\n");
    }
    printf("\n    exact relabeling parity:\n");
    for (std::size_t i = 0U; i < kCoreCount; ++i) {
        for (std::size_t j = i + 1U; j < kCoreCount; ++j) {
            std::array<int, kRoleCount> aMap{};
            if (EquivalentUnderTransform(
                    kCores[i],
                    kCores[j],
                    0U,
                    false,
                    {0U, 1U, 2U},
                    &aMap)) {
                printf("        core %zu -> core %zu: %s\n",
                       i,
                       j,
                       PermutationIsEven(aMap) ? "even" : "odd");
            }
        }
    }
}

- (void)testExplainRolePermutationCount {
    constexpr std::uint64_t aAllRolePermutations =
        39'916'800ULL;
    constexpr std::uint64_t aEvenRolePermutations =
        aAllRolePermutations / 2ULL;
    constexpr std::uint64_t aNominalLabeledHearts =
        aEvenRolePermutations * kCoreCount;

    printf("\n============================================================\n");
    printf("CORE PLAN SPACE\n");
    printf("============================================================\n");
    printf("    intrinsic ordered cores: %zu\n", kCoreCount);
    printf("    all labels per core: %llu\n",
           static_cast<unsigned long long>(aAllRolePermutations));
    printf("    retained even labels per core: %llu\n",
           static_cast<unsigned long long>(aEvenRolePermutations));
    printf("    nominal labeled hearts: %llu\n",
           static_cast<unsigned long long>(aNominalLabeledHearts));
    printf("    note: labels produce concrete variety, not new "
           "unlabeled topology. Assignment and update schedules multiply "
           "the full scaffold space separately.\n");

    XCTAssertEqual(aEvenRolePermutations, 19'958'400ULL);
    XCTAssertEqual(aNominalLabeledHearts, 119'750'400ULL);
}

@end
