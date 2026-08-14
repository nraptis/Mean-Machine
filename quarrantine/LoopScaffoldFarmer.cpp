//
//  LoopScaffoldFarmer.cpp
//  MeanMachine
//

#include "LoopScaffoldFarmer.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "FileIO.hpp"
#include "LoopScaffoldCores.hpp"

namespace {

using LoopScaffoldCores::CoreRound;
using LoopScaffoldCores::kCores;
constexpr std::size_t kRoleCount = LoopScaffoldCores::kRoleCount;
constexpr std::size_t kCoreCount = LoopScaffoldCores::kCoreCount;
constexpr std::size_t kCandidateCount = 33U;
constexpr std::size_t kLoopsPerCandidate = 584U;
constexpr std::size_t kOutputLoopCount =
    kCandidateCount * kLoopsPerCandidate;
constexpr std::size_t kFamiliesPerCandidate = 132U;
constexpr std::size_t kPackCount =
    kCandidateCount * kFamiliesPerCandidate;
constexpr std::size_t kPlanTrialsPerCore = 4U;
constexpr std::size_t kUpdatePairScheduleTrials = 8U;
constexpr int kMinimumRetainedUpdateUnion = 12;
constexpr std::uint64_t kProgressIterationInterval = 1000000ULL;
constexpr std::uint64_t kCheckpointIterationInterval = 10000000ULL;

// Dependency labels used by the structural scorer. These represent the
// state that can actually survive into a loop, plus fresh ingress/cross lane
// material for each modeled iteration. Previous, cross, and scatter are not
// persistent inputs: the generated loop overwrites all three before the
// farmed scaffold consumes them.
using Influence = std::uint32_t;
using InfluenceSet = std::array<Influence, kRoleCount>;

constexpr std::size_t kInitialIngressSource = 11U;
constexpr std::size_t kInitialCarrySource = 12U;
constexpr std::size_t kFirstFreshIngressSource = 13U;
constexpr std::size_t kFirstFreshCrossSource = 14U;
constexpr std::size_t kSecondFreshIngressSource = 15U;
constexpr std::size_t kSecondFreshCrossSource = 16U;
constexpr std::size_t kFirstIterationSourceCount = 15U;
constexpr std::size_t kSecondIterationSourceCount = 17U;
constexpr int kFlowStepsPerIteration = 25;

using ArrivalMatrix = std::array<
    std::array<int, kSecondIterationSourceCount>,
    kRoleCount>;

constexpr int kUnreachableHeartDistance =
    static_cast<int>(kRoleCount) + 1;
using HeartDistanceMatrix = std::array<
    std::array<int, kRoleCount>,
    kRoleCount>;

enum : std::uint8_t {
    kContextIngress = 0U,
    kContextScatter = 1U,
    kContextPrevious = 2U,
    kContextCross = 3U,
};

bool ValidateCoreScaffolds(std::string *pErrorMessage) {
    for (std::size_t aCoreIndex = 0U;
         aCoreIndex < kCoreCount;
         ++aCoreIndex) {
        std::array<int, kRoleCount> aLeadCounts{};
        std::array<int, kRoleCount> aSourceCounts{};
        std::array<int, kRoleCount> aFeedbackCounts{};
        bool aAdjacency[kRoleCount][kRoleCount]{};
        for (const CoreRound &aRound : kCores[aCoreIndex]) {
            if ((aRound.mLead >= kRoleCount) ||
                (aRound.mSource >= kRoleCount) ||
                (aRound.mFeedback >= kRoleCount) ||
                (aRound.mLead == aRound.mSource) ||
                (aRound.mLead == aRound.mFeedback) ||
                (aRound.mSource == aRound.mFeedback)) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage =
                        "Loop scaffold heart core contained an invalid round";
                }
                return false;
            }
            ++aLeadCounts[aRound.mLead];
            ++aSourceCounts[aRound.mSource];
            ++aFeedbackCounts[aRound.mFeedback];
            aAdjacency[aRound.mSource][aRound.mLead] = true;
            aAdjacency[aRound.mLead][aRound.mFeedback] = true;
        }
        for (std::size_t i = 0U; i < kRoleCount; ++i) {
            if ((aLeadCounts[i] != 1) ||
                (aSourceCounts[i] != 1) ||
                (aFeedbackCounts[i] != 1)) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage =
                        "Loop scaffold heart core was not role-balanced";
                }
                return false;
            }
        }
        for (std::size_t aStart = 0U;
             aStart < kRoleCount;
             ++aStart) {
            std::array<bool, kRoleCount> aVisited{};
            std::queue<std::size_t> aQueue;
            aVisited[aStart] = true;
            aQueue.push(aStart);
            while (!aQueue.empty()) {
                const std::size_t aNode = aQueue.front();
                aQueue.pop();
                for (std::size_t aNext = 0U;
                     aNext < kRoleCount;
                     ++aNext) {
                    if (aAdjacency[aNode][aNext] &&
                        !aVisited[aNext]) {
                        aVisited[aNext] = true;
                        aQueue.push(aNext);
                    }
                }
            }
            if (std::find(aVisited.begin(),
                          aVisited.end(), false) != aVisited.end()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage =
                        "Loop scaffold heart core was not strongly connected";
                }
                return false;
            }
        }
    }
    return true;
}

class Generator {
public:
    explicit Generator(const std::uint64_t pSeed)
    : mState(pSeed) {
    }

    std::uint64_t Next() {
        mState += 0x9E3779B97F4A7C15ULL;
        std::uint64_t aValue = mState;
        aValue = (aValue ^ (aValue >> 30U)) * 0xBF58476D1CE4E5B9ULL;
        aValue = (aValue ^ (aValue >> 27U)) * 0x94D049BB133111EBULL;
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
    if ((pValues == nullptr) || (pGenerator == nullptr)) {
        return;
    }
    for (std::size_t i = N; i > 1U; --i) {
        const std::size_t aSwap = pGenerator->Below(i);
        std::swap((*pValues)[i - 1U], (*pValues)[aSwap]);
    }
}

template <typename T>
void ShuffleVector(std::vector<T> *pValues,
                   Generator *pGenerator) {
    if ((pValues == nullptr) || (pGenerator == nullptr)) {
        return;
    }
    for (std::size_t i = pValues->size(); i > 1U; --i) {
        const std::size_t aSwap = pGenerator->Below(i);
        std::swap((*pValues)[i - 1U], (*pValues)[aSwap]);
    }
}

std::array<std::uint8_t, kRoleCount> IdentityRoles() {
    std::array<std::uint8_t, kRoleCount> aResult{};
    for (std::size_t i = 0U; i < aResult.size(); ++i) {
        aResult[i] = static_cast<std::uint8_t>(i);
    }
    return aResult;
}

bool PermutationIsEven(
    const std::array<std::uint8_t, kRoleCount> &pValues) {
    int aInversions = 0;
    for (std::size_t i = 0U; i < pValues.size(); ++i) {
        for (std::size_t j = i + 1U; j < pValues.size(); ++j) {
            aInversions += pValues[i] > pValues[j];
        }
    }
    return (aInversions & 1) == 0;
}

struct PlanScore {
    int mMinimumWandererInfluence = 0;
    int mMinimumInputCoverage = 0;
    int mSecondIterationMinimumWandererInfluence = 0;
    int mSecondIterationMinimumInputCoverage = 0;
    int mMaximumWandererArrivalStep = 0;
    int mWandererArrivalStepTotal = 0;
    int mMaximumSourceArrivalSkew = 0;
    int mLongestFlowStall = 0;
    int mFlowInfluenceArea = 0;
    int mMinimumUpdateUnion = 0;
    int mMinimumUpdateOverlap = 0;
    int mMinimumUpdateUniqueSide = 0;
    int mMinimumUpdateHeartSeparation = 0;
    int mUpdateHeartSeparationTotal = 0;
    int mDominatedUpdatePairCount = 0;
    int mMinimumComplement = 0;
    int mMinimumHeartMultiRouteSources = 0;
    int mHeartRouteMultiplicityTotal = 0;
    int mMinimumOrbiterInfluence = 0;
    int mMiddleInfluence = 0;
    int mEarlyInfluence = 0;
    int mWandererInfluenceTotal = 0;
    int mOrbiterInfluenceTotal = 0;
    int mUpdatePairComplementTotal = 0;
};

int CompareCoverage(const int pWandererInfluenceA,
                    const int pInputCoverageA,
                    const int pWandererInfluenceB,
                    const int pInputCoverageB,
                    const std::size_t pSourceCount) {
    // Row coverage (sources reaching one wanderer) and column coverage
    // (wanderers reached by one source) are the two sides of the same
    // dependency matrix. Compare their normalized bottleneck first so a
    // one-step row gain cannot buy an arbitrary column regression.
    const int aRowA = pWandererInfluenceA *
        static_cast<int>(kRoleCount);
    const int aColumnA = pInputCoverageA *
        static_cast<int>(pSourceCount);
    const int aRowB = pWandererInfluenceB *
        static_cast<int>(kRoleCount);
    const int aColumnB = pInputCoverageB *
        static_cast<int>(pSourceCount);
    const int aFloorA = std::min(aRowA, aColumnA);
    const int aFloorB = std::min(aRowB, aColumnB);
    if (aFloorA != aFloorB) {
        return aFloorA > aFloorB ? 1 : -1;
    }
    const int aTotalA = aRowA + aColumnA;
    const int aTotalB = aRowB + aColumnB;
    if (aTotalA != aTotalB) {
        return aTotalA > aTotalB ? 1 : -1;
    }
    if (pWandererInfluenceA != pWandererInfluenceB) {
        return pWandererInfluenceA > pWandererInfluenceB ? 1 : -1;
    }
    if (pInputCoverageA != pInputCoverageB) {
        return pInputCoverageA > pInputCoverageB ? 1 : -1;
    }
    return 0;
}

bool ScoreIsBetter(const PlanScore &pA,
                   const PlanScore &pB) {
    const int aFirstCoverage = CompareCoverage(
        pA.mMinimumWandererInfluence,
        pA.mMinimumInputCoverage,
        pB.mMinimumWandererInfluence,
        pB.mMinimumInputCoverage,
        kFirstIterationSourceCount);
    if (aFirstCoverage != 0) {
        return aFirstCoverage > 0;
    }
    const int aSecondCoverage = CompareCoverage(
        pA.mSecondIterationMinimumWandererInfluence,
        pA.mSecondIterationMinimumInputCoverage,
        pB.mSecondIterationMinimumWandererInfluence,
        pB.mSecondIterationMinimumInputCoverage,
        kSecondIterationSourceCount);
    if (aSecondCoverage != 0) {
        return aSecondCoverage > 0;
    }
    if (pA.mMinimumUpdateUnion != pB.mMinimumUpdateUnion) {
        return pA.mMinimumUpdateUnion > pB.mMinimumUpdateUnion;
    }
    if (pA.mMinimumOrbiterInfluence != pB.mMinimumOrbiterInfluence) {
        return pA.mMinimumOrbiterInfluence > pB.mMinimumOrbiterInfluence;
    }
    if (pA.mMinimumComplement != pB.mMinimumComplement) {
        return pA.mMinimumComplement > pB.mMinimumComplement;
    }
    if (pA.mMiddleInfluence != pB.mMiddleInfluence) {
        return pA.mMiddleInfluence > pB.mMiddleInfluence;
    }
    if (pA.mEarlyInfluence != pB.mEarlyInfluence) {
        return pA.mEarlyInfluence > pB.mEarlyInfluence;
    }
    if (pA.mWandererInfluenceTotal != pB.mWandererInfluenceTotal) {
        return pA.mWandererInfluenceTotal > pB.mWandererInfluenceTotal;
    }
    if (pA.mOrbiterInfluenceTotal != pB.mOrbiterInfluenceTotal) {
        return pA.mOrbiterInfluenceTotal > pB.mOrbiterInfluenceTotal;
    }
    if (pA.mUpdatePairComplementTotal !=
        pB.mUpdatePairComplementTotal) {
        return pA.mUpdatePairComplementTotal >
               pB.mUpdatePairComplementTotal;
    }

    // The following flow metrics deliberately break ties only after every
    // established coverage criterion. They add temporal discrimination
    // without weakening a previously enforced structural floor.
    // Maximum arrival is diagnostic only: a fresh second-iteration context
    // cannot reach every wanderer before the eleventh sequential update, so
    // every valid N11 scaffold has the same maximum. Arrival skew and total
    // still distinguish directional bottlenecks and overall propagation rate.
    if (pA.mMinimumUpdateHeartSeparation !=
        pB.mMinimumUpdateHeartSeparation) {
        return pA.mMinimumUpdateHeartSeparation >
               pB.mMinimumUpdateHeartSeparation;
    }
    if (pA.mUpdateHeartSeparationTotal !=
        pB.mUpdateHeartSeparationTotal) {
        return pA.mUpdateHeartSeparationTotal >
               pB.mUpdateHeartSeparationTotal;
    }
    if (pA.mMaximumSourceArrivalSkew !=
        pB.mMaximumSourceArrivalSkew) {
        return pA.mMaximumSourceArrivalSkew <
               pB.mMaximumSourceArrivalSkew;
    }
    if (pA.mWandererArrivalStepTotal !=
        pB.mWandererArrivalStepTotal) {
        return pA.mWandererArrivalStepTotal <
               pB.mWandererArrivalStepTotal;
    }
    if (pA.mLongestFlowStall != pB.mLongestFlowStall) {
        return pA.mLongestFlowStall < pB.mLongestFlowStall;
    }
    if (pA.mDominatedUpdatePairCount !=
        pB.mDominatedUpdatePairCount) {
        return pA.mDominatedUpdatePairCount <
               pB.mDominatedUpdatePairCount;
    }
    const int aPairBalanceA = std::min(
        pA.mMinimumUpdateOverlap,
        pA.mMinimumUpdateUniqueSide);
    const int aPairBalanceB = std::min(
        pB.mMinimumUpdateOverlap,
        pB.mMinimumUpdateUniqueSide);
    if (aPairBalanceA != aPairBalanceB) {
        return aPairBalanceA > aPairBalanceB;
    }
    const int aPairShapeTotalA =
        pA.mMinimumUpdateOverlap +
        pA.mMinimumUpdateUniqueSide;
    const int aPairShapeTotalB =
        pB.mMinimumUpdateOverlap +
        pB.mMinimumUpdateUniqueSide;
    if (aPairShapeTotalA != aPairShapeTotalB) {
        return aPairShapeTotalA > aPairShapeTotalB;
    }
    if (pA.mMinimumUpdateOverlap != pB.mMinimumUpdateOverlap) {
        return pA.mMinimumUpdateOverlap > pB.mMinimumUpdateOverlap;
    }
    if (pA.mMinimumUpdateUniqueSide !=
        pB.mMinimumUpdateUniqueSide) {
        return pA.mMinimumUpdateUniqueSide >
               pB.mMinimumUpdateUniqueSide;
    }
    if (pA.mMinimumHeartMultiRouteSources !=
        pB.mMinimumHeartMultiRouteSources) {
        return pA.mMinimumHeartMultiRouteSources >
               pB.mMinimumHeartMultiRouteSources;
    }
    if (pA.mFlowInfluenceArea != pB.mFlowInfluenceArea) {
        return pA.mFlowInfluenceArea > pB.mFlowInfluenceArea;
    }
    if (pA.mHeartRouteMultiplicityTotal !=
        pB.mHeartRouteMultiplicityTotal) {
        return pA.mHeartRouteMultiplicityTotal >
               pB.mHeartRouteMultiplicityTotal;
    }
    return false;
}

struct ScaffoldPlan {
    std::uint8_t mCoreIndex = 0U;
    std::array<std::uint8_t, kRoleCount> mRolePermutation{};

    std::array<std::uint8_t, kRoleCount> mAssignmentTarget{};
    std::array<std::uint8_t, kRoleCount> mAssignmentWanderer{};
    std::array<std::uint8_t, kRoleCount> mAssignmentContext{};
    std::uint16_t mAssignmentCarryMask = 0U;

    std::array<std::uint8_t, kRoleCount> mUpdateTarget{};
    std::array<std::uint8_t, kRoleCount> mUpdateOrbiterA{};
    std::array<std::uint8_t, kRoleCount> mUpdateOrbiterB{};
    std::array<std::uint8_t, kRoleCount> mUpdateContext{};
    std::uint16_t mUpdateXorMask = 0U;
    std::uint16_t mUpdateCarryMask = 0U;
    std::uint16_t mUpdateRotateFirstMask = 0U;

    PlanScore mScore;
};

struct AssignmentForTarget {
    std::uint8_t mWanderer = 0U;
    std::uint8_t mContext = 0U;
    bool mUseCarry = false;
};

struct UpdateForTarget {
    std::uint8_t mRotatedOrbiter = 0U;
    std::uint8_t mPlainOrbiter = 0U;
    std::uint8_t mContext = 0U;
    bool mUseXor = false;
    bool mUseCarry = false;
};

std::array<AssignmentForTarget, kRoleCount> AssignmentsByTarget(
    const ScaffoldPlan &pPlan) {
    std::array<AssignmentForTarget, kRoleCount> aResult{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        AssignmentForTarget &aAssignment =
            aResult[pPlan.mAssignmentTarget[i]];
        aAssignment.mWanderer = pPlan.mAssignmentWanderer[i];
        aAssignment.mContext = pPlan.mAssignmentContext[i];
        aAssignment.mUseCarry =
            (pPlan.mAssignmentCarryMask & (1U << i)) != 0U;
    }
    return aResult;
}

std::array<UpdateForTarget, kRoleCount> UpdatesByTarget(
    const ScaffoldPlan &pPlan) {
    std::array<UpdateForTarget, kRoleCount> aResult{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        UpdateForTarget &aUpdate = aResult[pPlan.mUpdateTarget[i]];
        const bool aRotateFirst =
            (pPlan.mUpdateRotateFirstMask & (1U << i)) != 0U;
        aUpdate.mRotatedOrbiter = aRotateFirst
            ? pPlan.mUpdateOrbiterA[i]
            : pPlan.mUpdateOrbiterB[i];
        aUpdate.mPlainOrbiter = aRotateFirst
            ? pPlan.mUpdateOrbiterB[i]
            : pPlan.mUpdateOrbiterA[i];
        aUpdate.mContext = pPlan.mUpdateContext[i];
        aUpdate.mUseXor =
            (pPlan.mUpdateXorMask & (1U << i)) != 0U;
        aUpdate.mUseCarry =
            (pPlan.mUpdateCarryMask & (1U << i)) != 0U;
    }
    return aResult;
}

CoreRound ConcreteRound(const ScaffoldPlan &pPlan,
                        const std::size_t pRoundIndex) {
    const CoreRound &aCore =
        kCores[pPlan.mCoreIndex][pRoundIndex];
    return {
        pPlan.mRolePermutation[aCore.mLead],
        pPlan.mRolePermutation[aCore.mSource],
        pPlan.mRolePermutation[aCore.mFeedback],
    };
}

HeartDistanceMatrix HeartTemporalDistances(
    const ScaffoldPlan &pPlan) {
    // Distances follow the concrete statement order, not numeric role IDs
    // and not an order-free graph. A role may retain an influence until a
    // later round; a path may only traverse an edge after that edge executes.
    HeartDistanceMatrix aDistances{};
    for (std::size_t aSource = 0U;
         aSource < kRoleCount;
         ++aSource) {
        aDistances[aSource].fill(kUnreachableHeartDistance);
        aDistances[aSource][aSource] = 0;
    }

    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const CoreRound aRound = ConcreteRound(pPlan, i);
        for (std::size_t aSource = 0U;
             aSource < kRoleCount;
             ++aSource) {
            if (aDistances[aSource][aRound.mSource] <
                kUnreachableHeartDistance) {
                aDistances[aSource][aRound.mLead] = std::min(
                    aDistances[aSource][aRound.mLead],
                    aDistances[aSource][aRound.mSource] + 1);
            }
            if (aDistances[aSource][aRound.mLead] <
                kUnreachableHeartDistance) {
                aDistances[aSource][aRound.mFeedback] = std::min(
                    aDistances[aSource][aRound.mFeedback],
                    aDistances[aSource][aRound.mLead] + 1);
            }
        }
    }
    return aDistances;
}

int HeartPairSeparation(const HeartDistanceMatrix &pDistances,
                        const std::size_t pA,
                        const std::size_t pB) {
    return std::min(pDistances[pA][pB],
                    pDistances[pB][pA]);
}

int PopCount(const Influence pValue) {
    return __builtin_popcount(static_cast<unsigned int>(pValue));
}

int InfluenceTotal(const InfluenceSet &pInfluence) {
    int aResult = 0;
    for (const Influence aValue : pInfluence) {
        aResult += PopCount(aValue);
    }
    return aResult;
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

struct HeartFlowMetrics {
    int mInfluenceArea = 0;
    int mLongestStall = 0;
};

void PropagateThroughHeart(const ScaffoldPlan &pPlan,
                           const InfluenceSet &pWanderers,
                           const Influence pPrevious,
                           const Influence pIngress,
                           const Influence pCross,
                           const Influence pCarry,
                           InfluenceSet *pOrbiters,
                           int *pEarlyInfluence,
                           int *pMiddleInfluence,
                           HeartFlowMetrics *pFlowMetrics) {
    const Influence aScatter =
        pPrevious | pIngress | pCross | pCarry;
    pOrbiters->fill(0U);
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::size_t aTarget = pPlan.mAssignmentTarget[i];
        const std::size_t aWanderer = pPlan.mAssignmentWanderer[i];
        const std::size_t aContext = pPlan.mAssignmentContext[i];
        Influence aInfluence = pWanderers[aWanderer] |
            ContextInfluence(static_cast<std::uint8_t>(aContext),
                             pIngress, aScatter, pPrevious, pCross);
        if ((pPlan.mAssignmentCarryMask & (1U << i)) != 0U) {
            aInfluence |= pCarry;
        }
        (*pOrbiters)[aTarget] = aInfluence;
    }

    int aPreviousInfluence = InfluenceTotal(*pOrbiters);
    int aCurrentStall = 0;
    if (pFlowMetrics != nullptr) {
        pFlowMetrics->mInfluenceArea = aPreviousInfluence;
        pFlowMetrics->mLongestStall = 0;
    }
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const CoreRound aRound = ConcreteRound(pPlan, i);
        (*pOrbiters)[aRound.mLead] |= (*pOrbiters)[aRound.mSource];
        (*pOrbiters)[aRound.mFeedback] |= (*pOrbiters)[aRound.mLead];

        const int aCurrentInfluence = InfluenceTotal(*pOrbiters);
        if (pFlowMetrics != nullptr) {
            pFlowMetrics->mInfluenceArea += aCurrentInfluence;
            if (aCurrentInfluence == aPreviousInfluence) {
                ++aCurrentStall;
                pFlowMetrics->mLongestStall = std::max(
                    pFlowMetrics->mLongestStall,
                    aCurrentStall);
            } else {
                aCurrentStall = 0;
            }
        }
        aPreviousInfluence = aCurrentInfluence;

        if ((i == 2U) && (pEarlyInfluence != nullptr)) {
            *pEarlyInfluence = InfluenceTotal(*pOrbiters);
        } else if ((i == 5U) && (pMiddleInfluence != nullptr)) {
            *pMiddleInfluence = InfluenceTotal(*pOrbiters);
        }
    }
}

InfluenceSet OrbiterInfluenceAfterHeart(const ScaffoldPlan &pPlan) {
    InfluenceSet aWanderers{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aWanderers[i] = SourceInfluence(i);
    }
    InfluenceSet aOrbiters{};
    PropagateThroughHeart(
        pPlan,
        aWanderers,
        SourceInfluence(kInitialIngressSource),
        SourceInfluence(kFirstFreshIngressSource),
        SourceInfluence(kFirstFreshCrossSource),
        SourceInfluence(kInitialCarrySource),
        &aOrbiters,
        nullptr,
        nullptr,
        nullptr);
    return aOrbiters;
}

struct HeartRouteMetrics {
    int mMinimumMultiRouteSources = 0;
    int mRouteMultiplicityTotal = 0;
};

HeartRouteMetrics MeasureHeartRouteMultiplicity(
    const ScaffoldPlan &pPlan) {
    // This is capped temporal route multiplicity, not a claim of fully
    // vertex-disjoint paths. It distinguishes single-route reachability from
    // dependencies that arrive through multiple ordered heart routes while
    // remaining cheap enough to evaluate inside the farm.
    std::array<
        std::array<std::uint8_t, kFirstIterationSourceCount>,
        kRoleCount> aRoutes{};
    const Influence aPrevious =
        SourceInfluence(kInitialIngressSource);
    const Influence aIngress =
        SourceInfluence(kFirstFreshIngressSource);
    const Influence aCross =
        SourceInfluence(kFirstFreshCrossSource);
    const Influence aCarry =
        SourceInfluence(kInitialCarrySource);
    const Influence aScatter =
        aPrevious | aIngress | aCross | aCarry;

    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::size_t aTarget = pPlan.mAssignmentTarget[i];
        Influence aInfluence =
            SourceInfluence(pPlan.mAssignmentWanderer[i]) |
            ContextInfluence(pPlan.mAssignmentContext[i],
                             aIngress,
                             aScatter,
                             aPrevious,
                             aCross);
        if ((pPlan.mAssignmentCarryMask & (1U << i)) != 0U) {
            aInfluence |= aCarry;
        }
        for (std::size_t aSource = 0U;
             aSource < kFirstIterationSourceCount;
             ++aSource) {
            aRoutes[aTarget][aSource] =
                (aInfluence & SourceInfluence(aSource)) != 0U
                    ? 1U
                    : 0U;
        }
    }

    const auto AddRouteCounts = [](const std::uint8_t pA,
                                   const std::uint8_t pB) {
        return static_cast<std::uint8_t>(
            std::min(3, static_cast<int>(pA) +
                        static_cast<int>(pB)));
    };
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const CoreRound aRound = ConcreteRound(pPlan, i);
        for (std::size_t aSource = 0U;
             aSource < kFirstIterationSourceCount;
             ++aSource) {
            aRoutes[aRound.mLead][aSource] = AddRouteCounts(
                aRoutes[aRound.mLead][aSource],
                aRoutes[aRound.mSource][aSource]);
            aRoutes[aRound.mFeedback][aSource] = AddRouteCounts(
                aRoutes[aRound.mFeedback][aSource],
                aRoutes[aRound.mLead][aSource]);
        }
    }

    HeartRouteMetrics aResult;
    aResult.mMinimumMultiRouteSources =
        static_cast<int>(kFirstIterationSourceCount);
    for (const auto &aDestination : aRoutes) {
        int aMultiRouteSources = 0;
        for (const std::uint8_t aMultiplicity : aDestination) {
            aMultiRouteSources += aMultiplicity >= 2U;
            aResult.mRouteMultiplicityTotal += aMultiplicity;
        }
        aResult.mMinimumMultiRouteSources = std::min(
            aResult.mMinimumMultiRouteSources,
            aMultiRouteSources);
    }
    return aResult;
}

struct IterationInfluence {
    InfluenceSet mOrbiters{};
    Influence mScatter = 0U;
    Influence mIngress = 0U;
    Influence mCarry = 0U;
    int mEarlyInfluence = 0;
    int mMiddleInfluence = 0;
    int mFlowInfluenceArea = 0;
    int mLongestFlowStall = 0;
};

void RecordWandererArrivals(const Influence pInfluence,
                            const std::size_t pWanderer,
                            const int pStep,
                            ArrivalMatrix *pArrivals) {
    if (pArrivals == nullptr) {
        return;
    }
    for (std::size_t aSource = 0U;
         aSource < kSecondIterationSourceCount;
         ++aSource) {
        int &aArrival = (*pArrivals)[pWanderer][aSource];
        if ((aArrival < 0) &&
            ((pInfluence & SourceInfluence(aSource)) != 0U)) {
            aArrival = pStep;
        }
    }
}

IterationInfluence PropagateIteration(
    const ScaffoldPlan &pPlan,
    const std::size_t pFreshIngressSource,
    const std::size_t pFreshCrossSource,
    const int pBaseStep,
    InfluenceSet *pWanderers,
    Influence *pIngress,
    Influence *pCarry,
    ArrivalMatrix *pWandererArrivals) {
    IterationInfluence aResult;

    // Match the generated statement order. Previous receives the surviving
    // ingress, ingress and cross are replaced by fresh lane material, and
    // scatter is then built from all four live inputs.
    const Influence aPrevious = *pIngress;
    const Influence aIngressLane =
        SourceInfluence(pFreshIngressSource);
    const Influence aCross =
        SourceInfluence(pFreshCrossSource);
    aResult.mScatter =
        aPrevious | aIngressLane | aCross | *pCarry;

    HeartFlowMetrics aHeartFlow;
    PropagateThroughHeart(pPlan,
                          *pWanderers,
                          aPrevious,
                          aIngressLane,
                          aCross,
                          *pCarry,
                          &aResult.mOrbiters,
                          &aResult.mEarlyInfluence,
                          &aResult.mMiddleInfluence,
                          &aHeartFlow);
    aResult.mFlowInfluenceArea = aHeartFlow.mInfluenceArea;
    aResult.mLongestFlowStall = aHeartFlow.mLongestStall;

    // The generated ingress crush consumes every orbiter and scatter before
    // the first wanderer update.
    aResult.mIngress = aResult.mScatter;
    for (const Influence aOrbiter : aResult.mOrbiters) {
        aResult.mIngress |= aOrbiter;
    }

    const InfluenceSet aPreviousWanderers = *pWanderers;
    InfluenceSet aUpdatedWanderers = aPreviousWanderers;
    int aPreviousInfluence = InfluenceTotal(aUpdatedWanderers);
    int aCurrentStall = 0;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::size_t aTarget = pPlan.mUpdateTarget[i];
        const std::size_t aOrbiterA = pPlan.mUpdateOrbiterA[i];
        const std::size_t aOrbiterB = pPlan.mUpdateOrbiterB[i];
        const std::size_t aContext = pPlan.mUpdateContext[i];
        Influence aInfluence = aPreviousWanderers[aTarget] |
            aResult.mOrbiters[aOrbiterA] |
            aResult.mOrbiters[aOrbiterB] |
            ContextInfluence(static_cast<std::uint8_t>(aContext),
                             aResult.mIngress,
                             aResult.mScatter,
                             aPrevious,
                             aCross);
        if ((pPlan.mUpdateCarryMask & (1U << i)) != 0U) {
            aInfluence |= *pCarry;
        }
        aUpdatedWanderers[aTarget] = aInfluence;
        RecordWandererArrivals(
            aInfluence,
            aTarget,
            pBaseStep + 14 + static_cast<int>(i),
            pWandererArrivals);

        const int aCurrentInfluence =
            InfluenceTotal(aUpdatedWanderers);
        aResult.mFlowInfluenceArea += aCurrentInfluence;
        if (aCurrentInfluence == aPreviousInfluence) {
            ++aCurrentStall;
            aResult.mLongestFlowStall = std::max(
                aResult.mLongestFlowStall,
                aCurrentStall);
        } else {
            aCurrentStall = 0;
        }
        aPreviousInfluence = aCurrentInfluence;
    }

    // The generated carry crush preserves carry and consumes every updated
    // wanderer plus the newly folded ingress.
    aResult.mCarry = *pCarry | aResult.mIngress;
    for (const Influence aWanderer : aUpdatedWanderers) {
        aResult.mCarry |= aWanderer;
    }

    *pWanderers = aUpdatedWanderers;
    *pIngress = aResult.mIngress;
    *pCarry = aResult.mCarry;
    return aResult;
}

PlanScore ScorePlan(const ScaffoldPlan &pPlan) {
    // These bits are dependency labels, not sampled output bits. Propagation
    // follows the complete generated state transition, including context
    // replacement, scatter, ingress crush, and carry crush. It still makes
    // no claim about balance, avalanche, or output-bit behavior.
    InfluenceSet aWanderers{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aWanderers[i] = SourceInfluence(i);
    }
    Influence aIngress = SourceInfluence(kInitialIngressSource);
    Influence aCarry = SourceInfluence(kInitialCarrySource);
    ArrivalMatrix aWandererArrivals{};
    for (auto &aArrivals : aWandererArrivals) {
        aArrivals.fill(-1);
    }
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aWandererArrivals[i][i] = 0;
    }

    const IterationInfluence aFirstIteration = PropagateIteration(
        pPlan,
        kFirstFreshIngressSource,
        kFirstFreshCrossSource,
        0,
        &aWanderers,
        &aIngress,
        &aCarry,
        &aWandererArrivals);
    const HeartDistanceMatrix aHeartDistances =
        HeartTemporalDistances(pPlan);

    int aMinimumOrbiter = static_cast<int>(kFirstIterationSourceCount);
    for (const Influence aValue : aFirstIteration.mOrbiters) {
        aMinimumOrbiter = std::min(aMinimumOrbiter,
                                   PopCount(aValue));
    }

    int aMinimumUpdateUnion =
        static_cast<int>(kFirstIterationSourceCount);
    int aMinimumUpdateOverlap =
        static_cast<int>(kFirstIterationSourceCount);
    int aMinimumUpdateUniqueSide =
        static_cast<int>(kFirstIterationSourceCount);
    int aMinimumUpdateHeartSeparation =
        kUnreachableHeartDistance;
    int aUpdateHeartSeparationTotal = 0;
    int aMinimumComplement =
        static_cast<int>(kFirstIterationSourceCount);
    int aDominatedUpdatePairCount = 0;
    int aUpdatePairComplementTotal = 0;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const std::size_t aOrbiterA = pPlan.mUpdateOrbiterA[i];
        const std::size_t aOrbiterB = pPlan.mUpdateOrbiterB[i];
        const Influence aInfluenceA =
            aFirstIteration.mOrbiters[aOrbiterA];
        const Influence aInfluenceB =
            aFirstIteration.mOrbiters[aOrbiterB];
        const int aUnion = PopCount(
            aInfluenceA | aInfluenceB);
        const int aOverlap = PopCount(
            aInfluenceA & aInfluenceB);
        const int aUniqueSide = std::min(
            PopCount(aInfluenceA & ~aInfluenceB),
            PopCount(aInfluenceB & ~aInfluenceA));
        const int aComplement = PopCount(
            aInfluenceA ^ aInfluenceB);
        const int aHeartSeparation = HeartPairSeparation(
            aHeartDistances,
            aOrbiterA,
            aOrbiterB);
        aDominatedUpdatePairCount += aUniqueSide == 0;
        aMinimumUpdateUnion = std::min(aMinimumUpdateUnion,
                                       aUnion);
        aMinimumUpdateOverlap = std::min(
            aMinimumUpdateOverlap,
            aOverlap);
        aMinimumUpdateUniqueSide = std::min(
            aMinimumUpdateUniqueSide,
            aUniqueSide);
        aMinimumUpdateHeartSeparation = std::min(
            aMinimumUpdateHeartSeparation,
            aHeartSeparation);
        aUpdateHeartSeparationTotal += aHeartSeparation;
        aMinimumComplement = std::min(aMinimumComplement,
                                      aComplement);
        aUpdatePairComplementTotal += aComplement;
    }

    int aMinimumWanderer =
        static_cast<int>(kFirstIterationSourceCount);
    for (const Influence aValue : aWanderers) {
        aMinimumWanderer = std::min(aMinimumWanderer,
                                    PopCount(aValue));
    }

    int aMinimumInputCoverage = 11;
    for (std::size_t aBit = 0U;
         aBit < kFirstIterationSourceCount;
         ++aBit) {
        int aCoverage = 0;
        for (const Influence aValue : aWanderers) {
            if ((aValue & (1U << aBit)) != 0U) {
                ++aCoverage;
            }
        }
        aMinimumInputCoverage = std::min(aMinimumInputCoverage,
                                         aCoverage);
    }
    const int aFirstIterationWandererInfluenceTotal =
        InfluenceTotal(aWanderers);
    const int aFirstIterationOrbiterInfluenceTotal =
        InfluenceTotal(aFirstIteration.mOrbiters);
    const HeartRouteMetrics aHeartRoutes =
        MeasureHeartRouteMultiplicity(pPlan);

    // A second iteration gets distinct fresh ingress/cross labels so the
    // score cannot claim coverage by conflating data from separate reads.
    const IterationInfluence aSecondIteration = PropagateIteration(
        pPlan,
        kSecondFreshIngressSource,
        kSecondFreshCrossSource,
        kFlowStepsPerIteration,
        &aWanderers,
        &aIngress,
        &aCarry,
        &aWandererArrivals);

    int aSecondIterationMinimumWanderer =
        static_cast<int>(kSecondIterationSourceCount);
    for (const Influence aValue : aWanderers) {
        aSecondIterationMinimumWanderer = std::min(
            aSecondIterationMinimumWanderer,
            PopCount(aValue));
    }
    int aSecondIterationMinimumInputCoverage = 11;
    for (std::size_t aBit = 0U;
         aBit < kSecondIterationSourceCount;
         ++aBit) {
        int aCoverage = 0;
        for (const Influence aValue : aWanderers) {
            if ((aValue & (1U << aBit)) != 0U) {
                ++aCoverage;
            }
        }
        aSecondIterationMinimumInputCoverage = std::min(
            aSecondIterationMinimumInputCoverage,
            aCoverage);
    }

    int aMaximumWandererArrivalStep = 0;
    int aWandererArrivalStepTotal = 0;
    int aMaximumSourceArrivalSkew = 0;
    constexpr int kMissingArrivalPenalty =
        (2 * kFlowStepsPerIteration) + 1;
    for (std::size_t aSource = 0U;
         aSource < kSecondIterationSourceCount;
         ++aSource) {
        int aSourceMinimum = kMissingArrivalPenalty;
        int aSourceMaximum = 0;
        for (std::size_t aWanderer = 0U;
             aWanderer < kRoleCount;
             ++aWanderer) {
            const int aRecorded =
                aWandererArrivals[aWanderer][aSource];
            const int aArrival = aRecorded >= 0
                ? aRecorded
                : kMissingArrivalPenalty;
            aSourceMinimum = std::min(aSourceMinimum, aArrival);
            aSourceMaximum = std::max(aSourceMaximum, aArrival);
            aMaximumWandererArrivalStep = std::max(
                aMaximumWandererArrivalStep,
                aArrival);
            aWandererArrivalStepTotal += aArrival;
        }
        aMaximumSourceArrivalSkew = std::max(
            aMaximumSourceArrivalSkew,
            aSourceMaximum - aSourceMinimum);
    }

    PlanScore aScore;
    aScore.mMinimumWandererInfluence = aMinimumWanderer;
    aScore.mMinimumInputCoverage = aMinimumInputCoverage;
    aScore.mSecondIterationMinimumWandererInfluence =
        aSecondIterationMinimumWanderer;
    aScore.mSecondIterationMinimumInputCoverage =
        aSecondIterationMinimumInputCoverage;
    aScore.mMaximumWandererArrivalStep =
        aMaximumWandererArrivalStep;
    aScore.mWandererArrivalStepTotal =
        aWandererArrivalStepTotal;
    aScore.mMaximumSourceArrivalSkew =
        aMaximumSourceArrivalSkew;
    aScore.mLongestFlowStall = std::max(
        aFirstIteration.mLongestFlowStall,
        aSecondIteration.mLongestFlowStall);
    aScore.mFlowInfluenceArea =
        aFirstIteration.mFlowInfluenceArea +
        aSecondIteration.mFlowInfluenceArea;
    aScore.mMinimumUpdateUnion = aMinimumUpdateUnion;
    aScore.mMinimumUpdateOverlap = aMinimumUpdateOverlap;
    aScore.mMinimumUpdateUniqueSide =
        aMinimumUpdateUniqueSide;
    aScore.mMinimumUpdateHeartSeparation =
        aMinimumUpdateHeartSeparation;
    aScore.mUpdateHeartSeparationTotal =
        aUpdateHeartSeparationTotal;
    aScore.mDominatedUpdatePairCount =
        aDominatedUpdatePairCount;
    aScore.mMinimumComplement = aMinimumComplement;
    aScore.mMinimumHeartMultiRouteSources =
        aHeartRoutes.mMinimumMultiRouteSources;
    aScore.mHeartRouteMultiplicityTotal =
        aHeartRoutes.mRouteMultiplicityTotal;
    aScore.mMinimumOrbiterInfluence = aMinimumOrbiter;
    aScore.mMiddleInfluence = aFirstIteration.mMiddleInfluence;
    aScore.mEarlyInfluence = aFirstIteration.mEarlyInfluence;
    aScore.mWandererInfluenceTotal =
        aFirstIterationWandererInfluenceTotal;
    aScore.mOrbiterInfluenceTotal =
        aFirstIterationOrbiterInfluenceTotal;
    aScore.mUpdatePairComplementTotal = aUpdatePairComplementTotal;
    return aScore;
}

bool ContextSchedule(std::array<std::uint8_t, kRoleCount> *pResult,
                     Generator *pGenerator) {
    if ((pResult == nullptr) || (pGenerator == nullptr)) {
        return false;
    }
    for (int aTry = 0; aTry < 128; ++aTry) {
        std::array<std::uint8_t, 4> aContext = {
            kContextIngress, kContextScatter,
            kContextPrevious, kContextCross,
        };
        std::size_t aIndex = 0U;
        for (int aGroup = 0; aGroup < 3; ++aGroup) {
            Shuffle(&aContext, pGenerator);
            for (const std::uint8_t aValue : aContext) {
                if (aIndex >= pResult->size()) {
                    break;
                }
                (*pResult)[aIndex++] = aValue;
            }
        }
        bool aValid = true;
        for (std::size_t i = 1U; i < pResult->size(); ++i) {
            if ((*pResult)[i - 1U] == (*pResult)[i]) {
                aValid = false;
                break;
            }
        }
        if (aValid) {
            return true;
        }
    }
    return false;
}

std::uint16_t AssignmentCarryMask(
    const std::array<std::uint8_t, kRoleCount> &pContext,
    Generator *pGenerator) {
    std::array<std::uint8_t, 4> aKinds = {
        kContextIngress, kContextScatter,
        kContextPrevious, kContextCross,
    };
    Shuffle(&aKinds, pGenerator);
    std::uint16_t aResult = 0U;
    for (std::size_t aKindIndex = 0U; aKindIndex < 3U; ++aKindIndex) {
        std::vector<std::size_t> aRows;
        for (std::size_t i = 0U; i < pContext.size(); ++i) {
            if (pContext[i] == aKinds[aKindIndex]) {
                aRows.push_back(i);
            }
        }
        if (!aRows.empty()) {
            aResult = static_cast<std::uint16_t>(
                aResult | (1U << aRows[pGenerator->Below(aRows.size())]));
        }
    }
    return aResult;
}

bool GenerateUpdatePairs(
    std::array<std::uint8_t, kRoleCount> *pA,
    std::array<std::uint8_t, kRoleCount> *pB,
    const InfluenceSet &pOrbiterInfluence,
    const HeartDistanceMatrix &pHeartDistances,
    Generator *pGenerator) {
    if ((pA == nullptr) || (pB == nullptr) ||
        (pGenerator == nullptr)) {
        return false;
    }
    const auto aIdentity = IdentityRoles();
    bool aFoundSchedule = false;
    std::size_t aValidScheduleCount = 0U;
    std::array<int, 9U> aBestScheduleScore{};
    for (int aTry = 0;
         (aTry < 4096) &&
         (aValidScheduleCount < kUpdatePairScheduleTrials);
         ++aTry) {
        std::array<std::uint8_t, kRoleCount> aCandidateA = aIdentity;
        std::array<std::uint8_t, kRoleCount> aCandidateB = aIdentity;
        Shuffle(&aCandidateA, pGenerator);
        Shuffle(&aCandidateB, pGenerator);
        bool aValid = true;
        std::array<std::array<bool, kRoleCount>, kRoleCount> aPairs{};
        int aMinimumUnion =
            static_cast<int>(kFirstIterationSourceCount);
        int aMinimumOverlap =
            static_cast<int>(kFirstIterationSourceCount);
        int aMinimumUniqueSide =
            static_cast<int>(kFirstIterationSourceCount);
        int aMinimumComplement =
            static_cast<int>(kFirstIterationSourceCount);
        int aTotalUnion = 0;
        int aTotalComplement = 0;
        int aDominatedPairCount = 0;
        int aMinimumHeartSeparation =
            kUnreachableHeartDistance;
        int aHeartSeparationTotal = 0;
        for (std::size_t i = 0U; i < kRoleCount; ++i) {
            const int aHeartSeparation = HeartPairSeparation(
                pHeartDistances,
                aCandidateA[i],
                aCandidateB[i]);
            if ((aCandidateA[i] == aCandidateB[i]) ||
                (aHeartSeparation <= 1)) {
                aValid = false;
                break;
            }
            const std::size_t aLo = std::min(aCandidateA[i],
                                             aCandidateB[i]);
            const std::size_t aHi = std::max(aCandidateA[i],
                                             aCandidateB[i]);
            if (aPairs[aLo][aHi]) {
                aValid = false;
                break;
            }
            aPairs[aLo][aHi] = true;

            const Influence aInfluenceA =
                pOrbiterInfluence[aCandidateA[i]];
            const Influence aInfluenceB =
                pOrbiterInfluence[aCandidateB[i]];
            const int aUnion = PopCount(
                aInfluenceA | aInfluenceB);
            const int aOverlap = PopCount(
                aInfluenceA & aInfluenceB);
            const int aUniqueSide = std::min(
                PopCount(aInfluenceA & ~aInfluenceB),
                PopCount(aInfluenceB & ~aInfluenceA));
            const int aComplement = PopCount(
                aInfluenceA ^ aInfluenceB);
            // A useful update pair must share some context and must not have
            // identical dependency sets.  Separately count cases where one
            // dependency set is strictly contained in the other;
            // eliminating every such case makes a complete six-pack
            // infeasible, so containment is minimized rather than forbidden.
            if ((aOverlap == 0) || (aComplement == 0)) {
                aValid = false;
                break;
            }
            aDominatedPairCount += aUniqueSide == 0;
            aMinimumUnion = std::min(aMinimumUnion, aUnion);
            aMinimumOverlap = std::min(
                aMinimumOverlap,
                aOverlap);
            aMinimumUniqueSide = std::min(
                aMinimumUniqueSide,
                aUniqueSide);
            aMinimumComplement = std::min(aMinimumComplement,
                                          aComplement);
            aTotalUnion += aUnion;
            aTotalComplement += aComplement;
            aMinimumHeartSeparation = std::min(
                aMinimumHeartSeparation,
                aHeartSeparation);
            aHeartSeparationTotal += aHeartSeparation;
        }
        if (!aValid) {
            continue;
        }
        if (aMinimumUnion < kMinimumRetainedUpdateUnion) {
            continue;
        }
        ++aValidScheduleCount;
        const int aMinimumPairBalance = std::min(
            aMinimumOverlap,
            aMinimumUniqueSide);
        const std::array<int, 9U> aScheduleScore = {
            aMinimumUnion,
            -aDominatedPairCount,
            aMinimumPairBalance,
            aMinimumOverlap + aMinimumUniqueSide,
            aMinimumComplement,
            aTotalUnion,
            aTotalComplement,
            aMinimumHeartSeparation,
            aHeartSeparationTotal,
        };
        const bool aBetter =
            !aFoundSchedule || (aScheduleScore > aBestScheduleScore);
        if (aBetter) {
            *pA = aCandidateA;
            *pB = aCandidateB;
            aBestScheduleScore = aScheduleScore;
            aFoundSchedule = true;
        }
    }
    return aFoundSchedule;
}

bool GenerateUpdateCarryMask(const ScaffoldPlan &pPlan,
                             Generator *pGenerator,
                             std::uint16_t *pResult) {
    if ((pGenerator == nullptr) || (pResult == nullptr)) {
        return false;
    }
    std::vector<std::size_t> aAddRows;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        if ((pPlan.mUpdateXorMask & (1U << i)) == 0U) {
            aAddRows.push_back(i);
        }
    }
    for (int aTry = 0; aTry < 128; ++aTry) {
        const std::size_t aRowA =
            aAddRows[pGenerator->Below(aAddRows.size())];
        const std::size_t aRowB =
            aAddRows[pGenerator->Below(aAddRows.size())];
        if ((aRowA == aRowB) ||
            (pPlan.mUpdateContext[aRowA] ==
             pPlan.mUpdateContext[aRowB])) {
            continue;
        }
        std::array<int, kRoleCount> aUsage{};
        ++aUsage[pPlan.mUpdateOrbiterA[aRowA]];
        ++aUsage[pPlan.mUpdateOrbiterB[aRowA]];
        ++aUsage[pPlan.mUpdateOrbiterA[aRowB]];
        ++aUsage[pPlan.mUpdateOrbiterB[aRowB]];
        int aRepeated = 0;
        for (const int aCount : aUsage) {
            if (aCount > 1) {
                aRepeated += aCount - 1;
            }
        }
        if (aRepeated > 1) {
            continue;
        }
        *pResult = static_cast<std::uint16_t>(
            (1U << aRowA) | (1U << aRowB));
        return true;
    }
    return false;
}

bool GeneratePlan(const std::uint8_t pCoreIndex,
                  Generator *pGenerator,
                  ScaffoldPlan *pResult) {
    if ((pGenerator == nullptr) || (pResult == nullptr) ||
        (pCoreIndex >= kCoreCount)) {
        return false;
    }
    ScaffoldPlan aPlan;
    aPlan.mCoreIndex = pCoreIndex;
    const auto aIdentity = IdentityRoles();
    aPlan.mRolePermutation = aIdentity;
    aPlan.mAssignmentTarget = aIdentity;
    aPlan.mAssignmentWanderer = aIdentity;
    aPlan.mUpdateTarget = aIdentity;
    Shuffle(&aPlan.mRolePermutation, pGenerator);
    // Restrict the heart relabeling to the alternating group. Two distinct
    // retained relabelings of the same core can therefore never differ by a
    // single transposition, eliminating the closest six-position heart
    // neighbor while leaving 11! / 2 possible relabelings per core.
    if (!PermutationIsEven(aPlan.mRolePermutation)) {
        std::swap(aPlan.mRolePermutation[0],
                  aPlan.mRolePermutation[1]);
    }
    Shuffle(&aPlan.mAssignmentTarget, pGenerator);
    Shuffle(&aPlan.mAssignmentWanderer, pGenerator);
    Shuffle(&aPlan.mUpdateTarget, pGenerator);

    if (!ContextSchedule(&aPlan.mAssignmentContext, pGenerator) ||
        !ContextSchedule(&aPlan.mUpdateContext, pGenerator)) {
        return false;
    }
    aPlan.mAssignmentCarryMask =
        AssignmentCarryMask(aPlan.mAssignmentContext, pGenerator);
    const auto aOrbiterInfluence = OrbiterInfluenceAfterHeart(aPlan);
    const HeartDistanceMatrix aHeartDistances =
        HeartTemporalDistances(aPlan);
    if (!GenerateUpdatePairs(&aPlan.mUpdateOrbiterA,
                             &aPlan.mUpdateOrbiterB,
                             aOrbiterInfluence,
                             aHeartDistances,
                             pGenerator)) {
        return false;
    }

    const bool aFlip = pGenerator->Bool();
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const bool aUseXor = ((i & 1U) != 0U) ^ aFlip;
        if (aUseXor) {
            aPlan.mUpdateXorMask = static_cast<std::uint16_t>(
                aPlan.mUpdateXorMask | (1U << i));
        }
        if (pGenerator->Bool()) {
            aPlan.mUpdateRotateFirstMask = static_cast<std::uint16_t>(
                aPlan.mUpdateRotateFirstMask | (1U << i));
        }
    }
    if (!GenerateUpdateCarryMask(aPlan,
                                 pGenerator,
                                 &aPlan.mUpdateCarryMask)) {
        return false;
    }

    aPlan.mScore = ScorePlan(aPlan);
    *pResult = aPlan;
    return true;
}

std::string AssignmentKey(const ScaffoldPlan &pPlan) {
    // Assignment statements write distinct orbiters and do not depend on one
    // another. Canonicalize by destination so a row permutation is not
    // mistaken for a new dependency graph.
    std::string aKey;
    aKey.reserve(33U);
    const auto aAssignments = AssignmentsByTarget(pPlan);
    for (const AssignmentForTarget &aAssignment : aAssignments) {
        aKey.push_back(static_cast<char>(aAssignment.mWanderer));
        aKey.push_back(static_cast<char>(aAssignment.mContext));
        aKey.push_back(static_cast<char>(aAssignment.mUseCarry));
    }
    return aKey;
}

std::string HeartKey(const ScaffoldPlan &pPlan) {
    std::string aKey;
    aKey.reserve(33U);
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const CoreRound aRound = ConcreteRound(pPlan, i);
        aKey.push_back(static_cast<char>(aRound.mLead));
        aKey.push_back(static_cast<char>(aRound.mSource));
        aKey.push_back(static_cast<char>(aRound.mFeedback));
    }
    return aKey;
}

std::string UpdateKey(const ScaffoldPlan &pPlan) {
    // Wanderer updates likewise write distinct targets. The meaningful pair
    // is which orbiter is rotated versus left plain, not whether that orbiter
    // happened to be stored in the generator's A or B field.
    std::string aKey;
    aKey.reserve(55U);
    const auto aUpdates = UpdatesByTarget(pPlan);
    for (const UpdateForTarget &aUpdate : aUpdates) {
        aKey.push_back(static_cast<char>(aUpdate.mRotatedOrbiter));
        aKey.push_back(static_cast<char>(aUpdate.mPlainOrbiter));
        aKey.push_back(static_cast<char>(aUpdate.mContext));
        aKey.push_back(static_cast<char>(aUpdate.mUseXor));
        aKey.push_back(static_cast<char>(aUpdate.mUseCarry));
    }
    return aKey;
}

std::uint64_t RolePermutationKey(const ScaffoldPlan &pPlan) {
    std::uint64_t aResult = 0ULL;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aResult |= static_cast<std::uint64_t>(pPlan.mRolePermutation[i])
                   << (4U * i);
    }
    return aResult;
}

std::uint64_t RolePermutationKey(
    const std::array<std::uint8_t, kRoleCount> &pPermutation) {
    std::uint64_t aResult = 0ULL;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aResult |= static_cast<std::uint64_t>(pPermutation[i])
                   << (4U * i);
    }
    return aResult;
}

int AssignmentDistance(const ScaffoldPlan &pA,
                       const ScaffoldPlan &pB) {
    int aDistance = 0;
    const auto aAssignmentsA = AssignmentsByTarget(pA);
    const auto aAssignmentsB = AssignmentsByTarget(pB);
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aDistance += aAssignmentsA[i].mWanderer !=
                     aAssignmentsB[i].mWanderer;
        aDistance += aAssignmentsA[i].mContext !=
                     aAssignmentsB[i].mContext;
        aDistance += aAssignmentsA[i].mUseCarry !=
                     aAssignmentsB[i].mUseCarry;
    }
    return aDistance;
}

int HeartDistance(const ScaffoldPlan &pA,
                  const ScaffoldPlan &pB) {
    int aDistance = 0;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const CoreRound aRoundA = ConcreteRound(pA, i);
        const CoreRound aRoundB = ConcreteRound(pB, i);
        aDistance += aRoundA.mLead != aRoundB.mLead;
        aDistance += aRoundA.mSource != aRoundB.mSource;
        aDistance += aRoundA.mFeedback != aRoundB.mFeedback;
    }
    return aDistance;
}

int UpdateDistance(const ScaffoldPlan &pA,
                   const ScaffoldPlan &pB) {
    int aDistance = 0;
    const auto aUpdatesA = UpdatesByTarget(pA);
    const auto aUpdatesB = UpdatesByTarget(pB);
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aDistance += aUpdatesA[i].mRotatedOrbiter !=
                     aUpdatesB[i].mRotatedOrbiter;
        aDistance += aUpdatesA[i].mPlainOrbiter !=
                     aUpdatesB[i].mPlainOrbiter;
        aDistance += aUpdatesA[i].mContext !=
                     aUpdatesB[i].mContext;
        aDistance += aUpdatesA[i].mUseXor !=
                     aUpdatesB[i].mUseXor;
        aDistance += aUpdatesA[i].mUseCarry !=
                     aUpdatesB[i].mUseCarry;
    }
    return aDistance;
}

struct ScaffoldPack {
    std::array<ScaffoldPlan, kCoreCount> mPlans{};
    PlanScore mWorstScore;
    PlanScore mTotalScore;
    int mMinimumDistance = 0;
    int mMinimumAssignmentDistance = 0;
    int mMinimumHeartDistance = 0;
    int mMinimumUpdateDistance = 0;
};

int WholeDistance(const ScaffoldPlan &pA,
                  const ScaffoldPlan &pB) {
    return AssignmentDistance(pA, pB) +
           HeartDistance(pA, pB) +
           UpdateDistance(pA, pB);
}

void OrderPackForExecution(ScaffoldPack *pPack,
                           const std::size_t pSelectedCount,
                           const ScaffoldPlan *pPreviousPlan) {
    if ((pPack == nullptr) || (pSelectedCount < 2U) ||
        (pSelectedCount > pPack->mPlans.size())) {
        return;
    }

    const std::array<ScaffoldPlan, kCoreCount> aOriginal = pPack->mPlans;
    std::array<std::size_t, kCoreCount> aOrder{};
    for (std::size_t i = 0U; i < pSelectedCount; ++i) {
        aOrder[i] = i;
    }

    std::array<std::size_t, kCoreCount> aBestOrder = aOrder;
    int aBestBoundaryCoreRepeat = 1;
    int aBestMinimumDistance = -1;
    int aBestDistanceTotal = -1;
    do {
        const bool aBoundaryCoreRepeat =
            (pPreviousPlan != nullptr) &&
            (pPreviousPlan->mCoreIndex ==
             aOriginal[aOrder[0]].mCoreIndex);
        int aMinimumDistance = std::numeric_limits<int>::max();
        int aDistanceTotal = 0;
        if (pPreviousPlan != nullptr) {
            const int aDistance = WholeDistance(
                *pPreviousPlan, aOriginal[aOrder[0]]);
            aMinimumDistance = std::min(aMinimumDistance, aDistance);
            aDistanceTotal += aDistance;
        }
        for (std::size_t i = 1U; i < pSelectedCount; ++i) {
            const int aDistance = WholeDistance(
                aOriginal[aOrder[i - 1U]], aOriginal[aOrder[i]]);
            aMinimumDistance = std::min(aMinimumDistance, aDistance);
            aDistanceTotal += aDistance;
        }

        const int aBoundaryRepeatValue = aBoundaryCoreRepeat ? 1 : 0;
        const bool aBetter =
            (aBoundaryRepeatValue < aBestBoundaryCoreRepeat) ||
            ((aBoundaryRepeatValue == aBestBoundaryCoreRepeat) &&
             (aMinimumDistance > aBestMinimumDistance)) ||
            ((aBoundaryRepeatValue == aBestBoundaryCoreRepeat) &&
             (aMinimumDistance == aBestMinimumDistance) &&
             (aDistanceTotal > aBestDistanceTotal));
        if (aBetter) {
            aBestOrder = aOrder;
            aBestBoundaryCoreRepeat = aBoundaryRepeatValue;
            aBestMinimumDistance = aMinimumDistance;
            aBestDistanceTotal = aDistanceTotal;
        }
    } while (std::next_permutation(aOrder.begin(),
                                   aOrder.begin() + pSelectedCount));

    for (std::size_t i = 0U; i < pSelectedCount; ++i) {
        pPack->mPlans[i] = aOriginal[aBestOrder[i]];
    }
}

void AddScore(const PlanScore &pSource,
              PlanScore *pDestination) {
    pDestination->mMinimumWandererInfluence +=
        pSource.mMinimumWandererInfluence;
    pDestination->mMinimumInputCoverage +=
        pSource.mMinimumInputCoverage;
    pDestination->mSecondIterationMinimumWandererInfluence +=
        pSource.mSecondIterationMinimumWandererInfluence;
    pDestination->mSecondIterationMinimumInputCoverage +=
        pSource.mSecondIterationMinimumInputCoverage;
    pDestination->mMaximumWandererArrivalStep +=
        pSource.mMaximumWandererArrivalStep;
    pDestination->mWandererArrivalStepTotal +=
        pSource.mWandererArrivalStepTotal;
    pDestination->mMaximumSourceArrivalSkew +=
        pSource.mMaximumSourceArrivalSkew;
    pDestination->mLongestFlowStall +=
        pSource.mLongestFlowStall;
    pDestination->mFlowInfluenceArea +=
        pSource.mFlowInfluenceArea;
    pDestination->mMinimumUpdateUnion +=
        pSource.mMinimumUpdateUnion;
    pDestination->mMinimumUpdateOverlap +=
        pSource.mMinimumUpdateOverlap;
    pDestination->mMinimumUpdateUniqueSide +=
        pSource.mMinimumUpdateUniqueSide;
    pDestination->mMinimumUpdateHeartSeparation +=
        pSource.mMinimumUpdateHeartSeparation;
    pDestination->mUpdateHeartSeparationTotal +=
        pSource.mUpdateHeartSeparationTotal;
    pDestination->mDominatedUpdatePairCount +=
        pSource.mDominatedUpdatePairCount;
    pDestination->mMinimumComplement +=
        pSource.mMinimumComplement;
    pDestination->mMinimumHeartMultiRouteSources +=
        pSource.mMinimumHeartMultiRouteSources;
    pDestination->mHeartRouteMultiplicityTotal +=
        pSource.mHeartRouteMultiplicityTotal;
    pDestination->mMinimumOrbiterInfluence +=
        pSource.mMinimumOrbiterInfluence;
    pDestination->mMiddleInfluence +=
        pSource.mMiddleInfluence;
    pDestination->mEarlyInfluence +=
        pSource.mEarlyInfluence;
    pDestination->mWandererInfluenceTotal +=
        pSource.mWandererInfluenceTotal;
    pDestination->mOrbiterInfluenceTotal +=
        pSource.mOrbiterInfluenceTotal;
    pDestination->mUpdatePairComplementTotal +=
        pSource.mUpdatePairComplementTotal;
}

void KeepComponentwiseMinimum(const PlanScore &pSource,
                              PlanScore *pDestination) {
    pDestination->mMinimumWandererInfluence = std::min(
        pDestination->mMinimumWandererInfluence,
        pSource.mMinimumWandererInfluence);
    pDestination->mMinimumInputCoverage = std::min(
        pDestination->mMinimumInputCoverage,
        pSource.mMinimumInputCoverage);
    pDestination->mSecondIterationMinimumWandererInfluence = std::min(
        pDestination->mSecondIterationMinimumWandererInfluence,
        pSource.mSecondIterationMinimumWandererInfluence);
    pDestination->mSecondIterationMinimumInputCoverage = std::min(
        pDestination->mSecondIterationMinimumInputCoverage,
        pSource.mSecondIterationMinimumInputCoverage);
    pDestination->mMaximumWandererArrivalStep = std::max(
        pDestination->mMaximumWandererArrivalStep,
        pSource.mMaximumWandererArrivalStep);
    pDestination->mWandererArrivalStepTotal = std::max(
        pDestination->mWandererArrivalStepTotal,
        pSource.mWandererArrivalStepTotal);
    pDestination->mMaximumSourceArrivalSkew = std::max(
        pDestination->mMaximumSourceArrivalSkew,
        pSource.mMaximumSourceArrivalSkew);
    pDestination->mLongestFlowStall = std::max(
        pDestination->mLongestFlowStall,
        pSource.mLongestFlowStall);
    pDestination->mFlowInfluenceArea = std::min(
        pDestination->mFlowInfluenceArea,
        pSource.mFlowInfluenceArea);
    pDestination->mMinimumUpdateUnion = std::min(
        pDestination->mMinimumUpdateUnion,
        pSource.mMinimumUpdateUnion);
    pDestination->mMinimumUpdateOverlap = std::min(
        pDestination->mMinimumUpdateOverlap,
        pSource.mMinimumUpdateOverlap);
    pDestination->mMinimumUpdateUniqueSide = std::min(
        pDestination->mMinimumUpdateUniqueSide,
        pSource.mMinimumUpdateUniqueSide);
    pDestination->mMinimumUpdateHeartSeparation = std::min(
        pDestination->mMinimumUpdateHeartSeparation,
        pSource.mMinimumUpdateHeartSeparation);
    pDestination->mUpdateHeartSeparationTotal = std::min(
        pDestination->mUpdateHeartSeparationTotal,
        pSource.mUpdateHeartSeparationTotal);
    pDestination->mDominatedUpdatePairCount = std::max(
        pDestination->mDominatedUpdatePairCount,
        pSource.mDominatedUpdatePairCount);
    pDestination->mMinimumComplement = std::min(
        pDestination->mMinimumComplement,
        pSource.mMinimumComplement);
    pDestination->mMinimumHeartMultiRouteSources = std::min(
        pDestination->mMinimumHeartMultiRouteSources,
        pSource.mMinimumHeartMultiRouteSources);
    pDestination->mHeartRouteMultiplicityTotal = std::min(
        pDestination->mHeartRouteMultiplicityTotal,
        pSource.mHeartRouteMultiplicityTotal);
    pDestination->mMinimumOrbiterInfluence = std::min(
        pDestination->mMinimumOrbiterInfluence,
        pSource.mMinimumOrbiterInfluence);
    pDestination->mMiddleInfluence = std::min(
        pDestination->mMiddleInfluence,
        pSource.mMiddleInfluence);
    pDestination->mEarlyInfluence = std::min(
        pDestination->mEarlyInfluence,
        pSource.mEarlyInfluence);
    pDestination->mWandererInfluenceTotal = std::min(
        pDestination->mWandererInfluenceTotal,
        pSource.mWandererInfluenceTotal);
    pDestination->mOrbiterInfluenceTotal = std::min(
        pDestination->mOrbiterInfluenceTotal,
        pSource.mOrbiterInfluenceTotal);
    pDestination->mUpdatePairComplementTotal = std::min(
        pDestination->mUpdatePairComplementTotal,
        pSource.mUpdatePairComplementTotal);
}

void ScorePack(ScaffoldPack *pPack) {
    if (pPack == nullptr) {
        return;
    }
    pPack->mWorstScore = pPack->mPlans[0].mScore;
    pPack->mTotalScore = PlanScore();
    pPack->mMinimumDistance = std::numeric_limits<int>::max();
    pPack->mMinimumAssignmentDistance = std::numeric_limits<int>::max();
    pPack->mMinimumHeartDistance = std::numeric_limits<int>::max();
    pPack->mMinimumUpdateDistance = std::numeric_limits<int>::max();
    for (std::size_t i = 0U; i < pPack->mPlans.size(); ++i) {
        KeepComponentwiseMinimum(pPack->mPlans[i].mScore,
                                 &pPack->mWorstScore);
        AddScore(pPack->mPlans[i].mScore,
                 &pPack->mTotalScore);
        for (std::size_t j = i + 1U; j < pPack->mPlans.size(); ++j) {
            const int aAssignmentDistance =
                AssignmentDistance(pPack->mPlans[i], pPack->mPlans[j]);
            const int aHeartDistance =
                HeartDistance(pPack->mPlans[i], pPack->mPlans[j]);
            const int aUpdateDistance =
                UpdateDistance(pPack->mPlans[i], pPack->mPlans[j]);
            pPack->mMinimumDistance = std::min(
                pPack->mMinimumDistance,
                aAssignmentDistance + aHeartDistance + aUpdateDistance);
            pPack->mMinimumAssignmentDistance = std::min(
                pPack->mMinimumAssignmentDistance,
                aAssignmentDistance);
            pPack->mMinimumHeartDistance = std::min(
                pPack->mMinimumHeartDistance,
                aHeartDistance);
            pPack->mMinimumUpdateDistance = std::min(
                pPack->mMinimumUpdateDistance,
                aUpdateDistance);
        }
    }
}

bool PackIsBetter(const ScaffoldPack &pA,
                  const ScaffoldPack &pB) {
    if (ScoreIsBetter(pA.mWorstScore, pB.mWorstScore)) {
        return true;
    }
    if (ScoreIsBetter(pB.mWorstScore, pA.mWorstScore)) {
        return false;
    }
    if (pA.mMinimumHeartDistance != pB.mMinimumHeartDistance) {
        return pA.mMinimumHeartDistance > pB.mMinimumHeartDistance;
    }
    if (pA.mMinimumAssignmentDistance !=
        pB.mMinimumAssignmentDistance) {
        return pA.mMinimumAssignmentDistance >
               pB.mMinimumAssignmentDistance;
    }
    if (pA.mMinimumUpdateDistance != pB.mMinimumUpdateDistance) {
        return pA.mMinimumUpdateDistance > pB.mMinimumUpdateDistance;
    }
    if (pA.mMinimumDistance != pB.mMinimumDistance) {
        return pA.mMinimumDistance > pB.mMinimumDistance;
    }
    return ScoreIsBetter(pA.mTotalScore, pB.mTotalScore);
}

struct PackBetterComparator {
    bool operator()(const ScaffoldPack &pA,
                    const ScaffoldPack &pB) const {
        return PackIsBetter(pA, pB);
    }
};

using PackHeap = std::priority_queue<
    ScaffoldPack,
    std::vector<ScaffoldPack>,
    PackBetterComparator>;

bool GeneratePack(Generator *pGenerator,
                  ScaffoldPack *pResult) {
    if ((pGenerator == nullptr) || (pResult == nullptr)) {
        return false;
    }
    ScaffoldPack aPack;
    std::array<std::uint8_t, kCoreCount> aCoreOrder = {
        0U, 1U, 2U, 3U, 4U, 5U,
    };
    Shuffle(&aCoreOrder, pGenerator);
    for (std::size_t i = 0U; i < aPack.mPlans.size(); ++i) {
        bool aFoundPlan = false;
        ScaffoldPlan aBestPlan;
        for (std::size_t aTrial = 0U;
             aTrial < kPlanTrialsPerCore;
             ++aTrial) {
            ScaffoldPlan aTrialPlan;
            if (!GeneratePlan(aCoreOrder[i],
                              pGenerator,
                              &aTrialPlan)) {
                continue;
            }
            if (!aFoundPlan ||
                ScoreIsBetter(aTrialPlan.mScore,
                              aBestPlan.mScore)) {
                aBestPlan = aTrialPlan;
                aFoundPlan = true;
            }
        }
        if (!aFoundPlan) {
            return false;
        }
        aPack.mPlans[i] = aBestPlan;
    }
    ScorePack(&aPack);
    *pResult = aPack;
    return true;
}

void AddPackKeys(const ScaffoldPack &pPack,
                 std::unordered_set<std::string> *pAssignments,
                 std::unordered_set<std::string> *pHearts,
                 std::unordered_set<std::string> *pUpdates,
                 std::array<std::unordered_set<std::uint64_t>,
                            kCoreCount> *pRolePermutations) {
    for (const ScaffoldPlan &aPlan : pPack.mPlans) {
        pAssignments->insert(AssignmentKey(aPlan));
        pHearts->insert(HeartKey(aPlan));
        pUpdates->insert(UpdateKey(aPlan));
        (*pRolePermutations)[aPlan.mCoreIndex].insert(
            RolePermutationKey(aPlan));
    }
}

void RemovePackKeys(const ScaffoldPack &pPack,
                    std::unordered_set<std::string> *pAssignments,
                    std::unordered_set<std::string> *pHearts,
                    std::unordered_set<std::string> *pUpdates,
                    std::array<std::unordered_set<std::uint64_t>,
                               kCoreCount> *pRolePermutations) {
    for (const ScaffoldPlan &aPlan : pPack.mPlans) {
        pAssignments->erase(AssignmentKey(aPlan));
        pHearts->erase(HeartKey(aPlan));
        pUpdates->erase(UpdateKey(aPlan));
        (*pRolePermutations)[aPlan.mCoreIndex].erase(
            RolePermutationKey(aPlan));
    }
}

bool CrossCoreHeartIsSeparated(
    const ScaffoldPack &pPack,
    const std::array<std::unordered_set<std::uint64_t>,
                     kCoreCount> &pRolePermutations) {
    // Cores 3 and 5 are exactly isomorphic under this odd permutation.
    // Because retained relabelings use even permutations, the 55 nearest
    // reachable cross-core neighbors are its one-transposition variants,
    // each at heart distance six. Reject all of them explicitly.
    static constexpr std::size_t kCoreA = 3U;
    static constexpr std::size_t kCoreB = 5U;
    static constexpr std::array<std::uint8_t, kRoleCount> kExactMap = {
        1U, 0U, 10U, 9U, 8U, 7U, 6U, 5U, 4U, 3U, 2U,
    };

    const ScaffoldPlan *aPlanA = nullptr;
    const ScaffoldPlan *aPlanB = nullptr;
    for (const ScaffoldPlan &aPlan : pPack.mPlans) {
        if (aPlan.mCoreIndex == kCoreA) {
            aPlanA = &aPlan;
        } else if (aPlan.mCoreIndex == kCoreB) {
            aPlanB = &aPlan;
        }
    }
    if ((aPlanA == nullptr) || (aPlanB == nullptr) ||
        (HeartDistance(*aPlanA, *aPlanB) <= 6)) {
        return false;
    }

    for (std::size_t aSwapA = 0U; aSwapA < kRoleCount; ++aSwapA) {
        for (std::size_t aSwapB = aSwapA + 1U;
             aSwapB < kRoleCount;
             ++aSwapB) {
            std::array<std::uint8_t, kRoleCount> aMap = kExactMap;
            std::swap(aMap[aSwapA], aMap[aSwapB]);

            std::array<std::uint8_t, kRoleCount> aForbiddenB{};
            std::array<std::uint8_t, kRoleCount> aForbiddenA{};
            for (std::size_t i = 0U; i < kRoleCount; ++i) {
                aForbiddenB[aMap[i]] = aPlanA->mRolePermutation[i];
                aForbiddenA[i] = aPlanB->mRolePermutation[aMap[i]];
            }
            if ((pRolePermutations[kCoreB].find(
                     RolePermutationKey(aForbiddenB)) !=
                 pRolePermutations[kCoreB].end()) ||
                (pRolePermutations[kCoreA].find(
                     RolePermutationKey(aForbiddenA)) !=
                 pRolePermutations[kCoreA].end())) {
                return false;
            }
        }
    }
    return true;
}

bool PackKeysAreUnique(
    const ScaffoldPack &pPack,
    const std::unordered_set<std::string> &pAssignments,
    const std::unordered_set<std::string> &pHearts,
    const std::unordered_set<std::string> &pUpdates) {
    std::unordered_set<std::string> aLocalAssignments;
    std::unordered_set<std::string> aLocalHearts;
    std::unordered_set<std::string> aLocalUpdates;
    for (const ScaffoldPlan &aPlan : pPack.mPlans) {
        const std::string aAssignment = AssignmentKey(aPlan);
        const std::string aHeart = HeartKey(aPlan);
        const std::string aUpdate = UpdateKey(aPlan);
        if ((pAssignments.find(aAssignment) != pAssignments.end()) ||
            (pHearts.find(aHeart) != pHearts.end()) ||
            (pUpdates.find(aUpdate) != pUpdates.end()) ||
            !aLocalAssignments.insert(aAssignment).second ||
            !aLocalHearts.insert(aHeart).second ||
            !aLocalUpdates.insert(aUpdate).second) {
            return false;
        }
    }
    return true;
}

std::vector<int> FamilyLengthsOneCandidate() {
    std::vector<int> aResult;
    aResult.reserve(kFamiliesPerCandidate);

    for (int aDomain = 0; aDomain < 6; ++aDomain) {
        const int aKDFLengths[16] = {
            6, 6, 4, 4,
            4, 4, 4, 4,
            4, 4, 4, 4,
            4, 4, 4, 4,
        };
        aResult.insert(aResult.end(),
                       std::begin(aKDFLengths),
                       std::end(aKDFLengths));
    }

    const int aSeedLengths[14] = {
        6, 6, 4, 6, 6, 4, 6,
        6, 4, 6, 6, 4, 6, 6,
    };
    aResult.insert(aResult.end(),
                   std::begin(aSeedLengths),
                   std::end(aSeedLengths));

    // Four planning families cover the sixteen single-loop KEY functions.
    aResult.insert(aResult.end(), {4, 4, 4, 4});

    const int aTwistLengths[8] = {6, 6, 4, 6, 6, 4, 6, 6};
    aResult.insert(aResult.end(),
                   std::begin(aTwistLengths),
                   std::end(aTwistLengths));

    for (int i = 0; i < 10; ++i) {
        aResult.push_back(4);
    }

    return aResult;
}

struct OutputBalanceCounts {
    std::size_t mLoopCount = 0U;
    std::array<std::size_t, kCoreCount> mCore{};
    std::array<std::array<std::size_t, kRoleCount>, kRoleCount>
        mAssignmentPair{};
    std::array<std::array<std::size_t, kRoleCount>, kRoleCount>
        mUpdatePair{};
    std::array<std::array<std::size_t, 4U>, kRoleCount>
        mAssignmentContext{};
    std::array<std::array<std::size_t, 4U>, kRoleCount>
        mUpdateContext{};
};

void AddPlanToOutputCounts(const ScaffoldPlan &pPlan,
                           OutputBalanceCounts *pCounts) {
    ++pCounts->mLoopCount;
    ++pCounts->mCore[pPlan.mCoreIndex];
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        ++pCounts->mAssignmentPair[pPlan.mAssignmentTarget[i]]
                                  [pPlan.mAssignmentWanderer[i]];
        const std::size_t aPairLo = std::min(
            pPlan.mUpdateOrbiterA[i], pPlan.mUpdateOrbiterB[i]);
        const std::size_t aPairHi = std::max(
            pPlan.mUpdateOrbiterA[i], pPlan.mUpdateOrbiterB[i]);
        ++pCounts->mUpdatePair[aPairLo][aPairHi];
        ++pCounts->mAssignmentContext[pPlan.mAssignmentTarget[i]]
                                     [pPlan.mAssignmentContext[i]];
        ++pCounts->mUpdateContext[pPlan.mUpdateTarget[i]]
                                 [pPlan.mUpdateContext[i]];
    }
}

double IncrementCost(const std::size_t pCount,
                     const double pExpectedCount) {
    // Increase in sum-of-squares when a bin changes from n to n + 1,
    // normalized so each independent histogram has comparable influence.
    return static_cast<double>((2U * pCount) + 1U) /
           std::max(1.0, pExpectedCount);
}

double PlanOutputBalanceCost(const ScaffoldPlan &pPlan,
                             const OutputBalanceCounts &pCounts) {
    const double aLoops = static_cast<double>(pCounts.mLoopCount);
    const double aAssignmentExpected =
        (aLoops * 11.0 / 121.0) + 1.0;
    const double aUpdateExpected =
        (aLoops * 11.0 / 44.0) + 1.0;
    const double aContextExpected =
        (aLoops * 11.0 / 44.0) + 1.0;
    double aResult = 0.0;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aResult += IncrementCost(
            pCounts.mAssignmentPair[pPlan.mAssignmentTarget[i]]
                                   [pPlan.mAssignmentWanderer[i]],
            aAssignmentExpected);
        const std::size_t aPairLo = std::min(
            pPlan.mUpdateOrbiterA[i], pPlan.mUpdateOrbiterB[i]);
        const std::size_t aPairHi = std::max(
            pPlan.mUpdateOrbiterA[i], pPlan.mUpdateOrbiterB[i]);
        aResult += IncrementCost(
            pCounts.mUpdatePair[aPairLo][aPairHi],
            aUpdateExpected);
        aResult += IncrementCost(
            pCounts.mAssignmentContext[pPlan.mAssignmentTarget[i]]
                                      [pPlan.mAssignmentContext[i]],
            aContextExpected);
        aResult += IncrementCost(
            pCounts.mUpdateContext[pPlan.mUpdateTarget[i]]
                                  [pPlan.mUpdateContext[i]],
            aContextExpected);
    }
    return aResult;
}

void BalancePackOutputOrder(std::vector<ScaffoldPack> *pPacks) {
    const std::vector<int> aFamilyLengths =
        FamilyLengthsOneCandidate();
    OutputBalanceCounts aCounts;
    std::size_t aPackIndex = 0U;
    for (std::size_t aCandidate = 0U;
         aCandidate < kCandidateCount;
         ++aCandidate) {
        ScaffoldPlan aPreviousPlan;
        bool aHasPreviousPlan = false;
        for (const int aFamilyLength : aFamilyLengths) {
            ScaffoldPack &aPack = (*pPacks)[aPackIndex++];
            if (aFamilyLength == 4) {
                std::uint32_t aBestMask = 0U;
                std::size_t aBestCoreCost =
                    std::numeric_limits<std::size_t>::max();
                double aBestBalanceCost =
                    std::numeric_limits<double>::max();
                for (std::uint32_t aMask = 0U;
                     aMask < (1U << kCoreCount);
                     ++aMask) {
                    if (__builtin_popcount(aMask) != 4) {
                        continue;
                    }
                    std::size_t aCoreCost = 0U;
                    double aBalanceCost = 0.0;
                    for (std::size_t i = 0U; i < kCoreCount; ++i) {
                        if ((aMask & (1U << i)) == 0U) {
                            continue;
                        }
                        const ScaffoldPlan &aPlan = aPack.mPlans[i];
                        aCoreCost += aCounts.mCore[aPlan.mCoreIndex];
                        aBalanceCost += PlanOutputBalanceCost(aPlan, aCounts);
                    }
                    if ((aCoreCost < aBestCoreCost) ||
                        ((aCoreCost == aBestCoreCost) &&
                         (aBalanceCost < aBestBalanceCost))) {
                        aBestMask = aMask;
                        aBestCoreCost = aCoreCost;
                        aBestBalanceCost = aBalanceCost;
                    }
                }

                std::array<ScaffoldPlan, kCoreCount> aOrdered{};
                std::size_t aWriteIndex = 0U;
                for (int aSelected = 1; aSelected >= 0; --aSelected) {
                    for (std::size_t i = 0U; i < kCoreCount; ++i) {
                        const bool aIsSelected =
                            (aBestMask & (1U << i)) != 0U;
                        if (aIsSelected == (aSelected != 0)) {
                            aOrdered[aWriteIndex++] = aPack.mPlans[i];
                        }
                    }
                }
                aPack.mPlans = aOrdered;
            }

            OrderPackForExecution(
                &aPack,
                static_cast<std::size_t>(aFamilyLength),
                aHasPreviousPlan ? &aPreviousPlan : nullptr);
            for (int i = 0; i < aFamilyLength; ++i) {
                AddPlanToOutputCounts(
                    aPack.mPlans[static_cast<std::size_t>(i)],
                    &aCounts);
            }
            aPreviousPlan = aPack.mPlans[
                static_cast<std::size_t>(aFamilyLength - 1)];
            aHasPreviousPlan = true;
        }
    }
}

std::vector<ScaffoldPack> FinalizePacks(PackHeap pHeap) {
    std::vector<ScaffoldPack> aResult;
    aResult.reserve(pHeap.size());
    while (!pHeap.empty()) {
        aResult.push_back(pHeap.top());
        pHeap.pop();
    }
    std::sort(aResult.begin(),
              aResult.end(),
              [](const ScaffoldPack &pA,
                 const ScaffoldPack &pB) {
        return PackIsBetter(pA, pB);
    });
    Generator aGenerator(0x60E5A3C91B47D2F8ULL);
    ShuffleVector(&aResult, &aGenerator);
    BalancePackOutputOrder(&aResult);
    return aResult;
}

void EmitByteArray(std::ostringstream *pStream,
                   const std::array<std::uint8_t, kRoleCount> &pValues) {
    *pStream << "{ ";
    for (std::size_t i = 0U; i < pValues.size(); ++i) {
        *pStream << static_cast<unsigned int>(pValues[i]) << "U";
        if ((i + 1U) < pValues.size()) {
            *pStream << ", ";
        }
    }
    *pStream << " }";
}

std::string EmitHeader(const std::vector<ScaffoldPack> &pPacks) {
    const std::vector<int> aFamilyLengths =
        FamilyLengthsOneCandidate();
    std::ostringstream aStream;
    aStream << "//\n";
    aStream << "//  LoopScaffolds11.hpp\n";
    aStream << "//  Structurally farmed complete loop scaffolds.\n";
    aStream << "//\n\n";
    aStream << "#ifndef LoopScaffolds11_hpp\n";
    aStream << "#define LoopScaffolds11_hpp\n\n";
    aStream << "#include <cstddef>\n";
    aStream << "#include <cstdint>\n\n";
    aStream << "struct LoopScaffoldCoreRound11 {\n";
    aStream << "    std::uint8_t mLeadRole;\n";
    aStream << "    std::uint8_t mSourceRole;\n";
    aStream << "    std::uint8_t mFeedbackRole;\n";
    aStream << "};\n\n";
    aStream << "struct LoopScaffold11 {\n";
    aStream << "    std::uint8_t mCoreIndex;\n";
    aStream << "    std::uint8_t mRolePermutation[11];\n";
    aStream << "    std::uint8_t mAssignmentTarget[11];\n";
    aStream << "    std::uint8_t mAssignmentWanderer[11];\n";
    aStream << "    std::uint8_t mAssignmentContext[11];\n";
    aStream << "    std::uint16_t mAssignmentCarryMask;\n";
    aStream << "    std::uint8_t mUpdateTarget[11];\n";
    aStream << "    std::uint8_t mUpdateOrbiterA[11];\n";
    aStream << "    std::uint8_t mUpdateOrbiterB[11];\n";
    aStream << "    std::uint8_t mUpdateContext[11];\n";
    aStream << "    std::uint16_t mUpdateXorMask;\n";
    aStream << "    std::uint16_t mUpdateCarryMask;\n";
    aStream << "    std::uint16_t mUpdateRotateFirstMask;\n";
    aStream << "};\n\n";
    aStream << "static constexpr std::size_t "
               "kLoopScaffolds11CandidateCount = 33U;\n";
    aStream << "static constexpr std::size_t "
               "kLoopScaffolds11PerCandidate = 584U;\n";
    aStream << "static constexpr std::size_t "
               "kLoopScaffolds11Count = 19272U;\n";
    aStream << "static constexpr std::size_t "
               "kLoopScaffoldCoreCount11 = 6U;\n";
    aStream << "static constexpr std::size_t "
               "kLoopScaffoldRoundCount11 = 11U;\n\n";
    aStream << "static const LoopScaffoldCoreRound11 "
               "kLoopScaffoldCores11[6][11] = {\n";
    for (std::size_t aCoreIndex = 0U;
         aCoreIndex < kCoreCount;
         ++aCoreIndex) {
        aStream << "    {\n        ";
        for (std::size_t aRoundIndex = 0U;
             aRoundIndex < kRoleCount;
             ++aRoundIndex) {
            const CoreRound &aRound =
                kCores[aCoreIndex][aRoundIndex];
            aStream << "{ "
                    << static_cast<unsigned int>(aRound.mLead)
                    << "U, "
                    << static_cast<unsigned int>(aRound.mSource)
                    << "U, "
                    << static_cast<unsigned int>(aRound.mFeedback)
                    << "U }";
            if ((aRoundIndex + 1U) < kRoleCount) {
                aStream << ", ";
            }
        }
        aStream << "\n    }";
        if ((aCoreIndex + 1U) < kCoreCount) {
            aStream << ",";
        }
        aStream << "\n";
    }
    aStream << "};\n\n";
    aStream << "static constexpr std::size_t LoopScaffold11Index(\n";
    aStream << "    const std::size_t pCandidateIndex,\n";
    aStream << "    const std::size_t pLoopIndex) {\n";
    aStream << "    return (pCandidateIndex * "
               "kLoopScaffolds11PerCandidate) + pLoopIndex;\n";
    aStream << "}\n\n";
    aStream << "static const LoopScaffold11 "
               "kLoopScaffolds11[19272] = {\n";

    std::size_t aPackIndex = 0U;
    std::size_t aOutputIndex = 0U;
    for (std::size_t aCandidate = 0U;
         aCandidate < kCandidateCount;
         ++aCandidate) {
        for (const int aFamilyLength : aFamilyLengths) {
            const ScaffoldPack &aPack = pPacks[aPackIndex++];
            for (int aLoop = 0; aLoop < aFamilyLength; ++aLoop) {
                const ScaffoldPlan &aPlan =
                    aPack.mPlans[static_cast<std::size_t>(aLoop)];
                aStream << "    {\n";
                aStream << "        "
                        << static_cast<unsigned int>(aPlan.mCoreIndex)
                        << "U,\n        ";
                EmitByteArray(&aStream, aPlan.mRolePermutation);
                aStream << ",\n        ";
                EmitByteArray(&aStream, aPlan.mAssignmentTarget);
                aStream << ",\n        ";
                EmitByteArray(&aStream, aPlan.mAssignmentWanderer);
                aStream << ",\n        ";
                EmitByteArray(&aStream, aPlan.mAssignmentContext);
                aStream << ",\n        " << aPlan.mAssignmentCarryMask
                        << "U,\n        ";
                EmitByteArray(&aStream, aPlan.mUpdateTarget);
                aStream << ",\n        ";
                EmitByteArray(&aStream, aPlan.mUpdateOrbiterA);
                aStream << ",\n        ";
                EmitByteArray(&aStream, aPlan.mUpdateOrbiterB);
                aStream << ",\n        ";
                EmitByteArray(&aStream, aPlan.mUpdateContext);
                aStream << ",\n        " << aPlan.mUpdateXorMask
                        << "U, " << aPlan.mUpdateCarryMask
                        << "U, " << aPlan.mUpdateRotateFirstMask
                        << "U\n";
                aStream << "    }, // scaffold " << aOutputIndex
                        << ", candidate " << aCandidate
                        << ", core "
                        << static_cast<unsigned int>(aPlan.mCoreIndex)
                        << "\n";
                ++aOutputIndex;
            }
        }
    }
    aStream << "};\n\n";
    aStream << "#endif /* LoopScaffolds11_hpp */\n";
    return aStream.str();
}

bool ValidateSelectedOutput(const std::vector<ScaffoldPack> &pPacks,
                            std::string *pErrorMessage) {
    if (pPacks.size() != kPackCount) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Loop scaffold output had the wrong pack count";
        }
        return false;
    }

    const std::vector<int> aFamilyLengths =
        FamilyLengthsOneCandidate();
    std::unordered_set<std::string> aAssignments;
    std::unordered_set<std::string> aHearts;
    std::unordered_set<std::string> aUpdates;
    aAssignments.reserve(kOutputLoopCount * 2U);
    aHearts.reserve(kOutputLoopCount * 2U);
    aUpdates.reserve(kOutputLoopCount * 2U);

    std::size_t aPackIndex = 0U;
    std::size_t aLoopCount = 0U;
    for (std::size_t aCandidate = 0U;
         aCandidate < kCandidateCount;
         ++aCandidate) {
        const ScaffoldPlan *aPreviousPlan = nullptr;
        for (const int aFamilyLength : aFamilyLengths) {
            if (aPackIndex >= pPacks.size()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage =
                        "Loop scaffold output exhausted its packs early";
                }
                return false;
            }
            const ScaffoldPack &aPack = pPacks[aPackIndex++];
            for (int aLoop = 0; aLoop < aFamilyLength; ++aLoop) {
                const ScaffoldPlan &aPlan =
                    aPack.mPlans[static_cast<std::size_t>(aLoop)];
                if ((aPreviousPlan != nullptr) &&
                    (aPreviousPlan->mCoreIndex == aPlan.mCoreIndex)) {
                    if (pErrorMessage != nullptr) {
                        *pErrorMessage =
                            "Loop scaffold output repeated an ARX core on consecutive loops";
                    }
                    return false;
                }
                const PlanScore aPlanScore = ScorePlan(aPlan);
                if ((aPlanScore.mSecondIterationMinimumWandererInfluence !=
                     static_cast<int>(kSecondIterationSourceCount)) ||
                    (aPlanScore.mSecondIterationMinimumInputCoverage !=
                     static_cast<int>(kRoleCount))) {
                    if (pErrorMessage != nullptr) {
                        *pErrorMessage =
                            "Loop scaffold output did not reach full structural dependency coverage by iteration two";
                    }
                    return false;
                }
                if (!aAssignments.insert(AssignmentKey(aPlan)).second ||
                    !aHearts.insert(HeartKey(aPlan)).second ||
                    !aUpdates.insert(UpdateKey(aPlan)).second) {
                    if (pErrorMessage != nullptr) {
                        *pErrorMessage =
                            "Loop scaffold output repeated one of its three structural pieces";
                    }
                    return false;
                }
                aPreviousPlan = &aPlan;
                ++aLoopCount;
            }
        }
    }

    if ((aPackIndex != pPacks.size()) ||
        (aLoopCount != kOutputLoopCount) ||
        (aAssignments.size() != kOutputLoopCount) ||
        (aHearts.size() != kOutputLoopCount) ||
        (aUpdates.size() != kOutputLoopCount)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Loop scaffold output did not contain 19,272 independently unique triples";
        }
        return false;
    }

    std::printf("Validated emitted scaffolds: loops=%zu assignments=%zu "
                "hearts=%zu updates=%zu\n",
                aLoopCount,
                aAssignments.size(),
                aHearts.size(),
                aUpdates.size());
    return true;
}

struct EncodedScaffold {
    std::uint64_t mAssignmentWanderer = 0ULL;
    std::uint64_t mAssignmentContext = 0ULL;
    std::uint16_t mAssignmentCarry = 0U;

    std::uint64_t mHeartLead = 0ULL;
    std::uint64_t mHeartSource = 0ULL;
    std::uint64_t mHeartFeedback = 0ULL;

    std::uint64_t mUpdateRotatedOrbiter = 0ULL;
    std::uint64_t mUpdatePlainOrbiter = 0ULL;
    std::uint64_t mUpdateContext = 0ULL;
    std::uint16_t mUpdateXor = 0U;
    std::uint16_t mUpdateCarry = 0U;
};

std::uint64_t PackNibbles(
    const std::array<std::uint8_t, kRoleCount> &pValues) {
    std::uint64_t aResult = 0ULL;
    for (std::size_t i = 0U; i < pValues.size(); ++i) {
        aResult |= static_cast<std::uint64_t>(pValues[i]) << (i * 4U);
    }
    return aResult;
}

EncodedScaffold EncodeScaffold(const ScaffoldPlan &pPlan) {
    EncodedScaffold aResult;
    const auto aAssignments = AssignmentsByTarget(pPlan);
    std::array<std::uint8_t, kRoleCount> aAssignmentWanderer{};
    std::array<std::uint8_t, kRoleCount> aAssignmentContext{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aAssignmentWanderer[i] = aAssignments[i].mWanderer;
        aAssignmentContext[i] = aAssignments[i].mContext;
        if (aAssignments[i].mUseCarry) {
            aResult.mAssignmentCarry = static_cast<std::uint16_t>(
                aResult.mAssignmentCarry | (1U << i));
        }
    }
    aResult.mAssignmentWanderer = PackNibbles(aAssignmentWanderer);
    aResult.mAssignmentContext = PackNibbles(aAssignmentContext);

    std::array<std::uint8_t, kRoleCount> aLead{};
    std::array<std::uint8_t, kRoleCount> aSource{};
    std::array<std::uint8_t, kRoleCount> aFeedback{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        const CoreRound aRound = ConcreteRound(pPlan, i);
        aLead[i] = aRound.mLead;
        aSource[i] = aRound.mSource;
        aFeedback[i] = aRound.mFeedback;
    }
    aResult.mHeartLead = PackNibbles(aLead);
    aResult.mHeartSource = PackNibbles(aSource);
    aResult.mHeartFeedback = PackNibbles(aFeedback);

    const auto aUpdates = UpdatesByTarget(pPlan);
    std::array<std::uint8_t, kRoleCount> aRotatedOrbiter{};
    std::array<std::uint8_t, kRoleCount> aPlainOrbiter{};
    std::array<std::uint8_t, kRoleCount> aUpdateContext{};
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        aRotatedOrbiter[i] = aUpdates[i].mRotatedOrbiter;
        aPlainOrbiter[i] = aUpdates[i].mPlainOrbiter;
        aUpdateContext[i] = aUpdates[i].mContext;
        if (aUpdates[i].mUseXor) {
            aResult.mUpdateXor = static_cast<std::uint16_t>(
                aResult.mUpdateXor | (1U << i));
        }
        if (aUpdates[i].mUseCarry) {
            aResult.mUpdateCarry = static_cast<std::uint16_t>(
                aResult.mUpdateCarry | (1U << i));
        }
    }
    aResult.mUpdateRotatedOrbiter = PackNibbles(aRotatedOrbiter);
    aResult.mUpdatePlainOrbiter = PackNibbles(aPlainOrbiter);
    aResult.mUpdateContext = PackNibbles(aUpdateContext);
    return aResult;
}

int ChangedNibbles(std::uint64_t pValue) {
    pValue |= pValue >> 1U;
    pValue |= pValue >> 2U;
    return __builtin_popcountll(pValue & 0x11111111111ULL);
}

void EncodedDistances(const EncodedScaffold &pA,
                      const EncodedScaffold &pB,
                      int *pAssignment,
                      int *pHeart,
    int *pUpdate) {
    *pAssignment =
        ChangedNibbles(pA.mAssignmentWanderer ^ pB.mAssignmentWanderer) +
        ChangedNibbles(pA.mAssignmentContext ^ pB.mAssignmentContext) +
        __builtin_popcount(static_cast<unsigned int>(
            pA.mAssignmentCarry ^ pB.mAssignmentCarry));
    *pHeart =
        ChangedNibbles(pA.mHeartLead ^ pB.mHeartLead) +
        ChangedNibbles(pA.mHeartSource ^ pB.mHeartSource) +
        ChangedNibbles(pA.mHeartFeedback ^ pB.mHeartFeedback);
    *pUpdate =
        ChangedNibbles(pA.mUpdateRotatedOrbiter ^
                       pB.mUpdateRotatedOrbiter) +
        ChangedNibbles(pA.mUpdatePlainOrbiter ^
                       pB.mUpdatePlainOrbiter) +
        ChangedNibbles(pA.mUpdateContext ^ pB.mUpdateContext) +
        __builtin_popcount(static_cast<unsigned int>(
            pA.mUpdateXor ^ pB.mUpdateXor)) +
        __builtin_popcount(static_cast<unsigned int>(
            pA.mUpdateCarry ^ pB.mUpdateCarry));
}

struct DistanceSummary {
    int mMinimum = 0;
    int mP01 = 0;
    int mP05 = 0;
    int mMedian = 0;
    int mP95 = 0;
    int mMaximum = 0;
};

DistanceSummary SummarizeDistances(std::vector<int> pValues) {
    std::sort(pValues.begin(), pValues.end());
    const auto At = [&](const double pFraction) -> int {
        const std::size_t aIndex = static_cast<std::size_t>(
            pFraction * static_cast<double>(pValues.size() - 1U));
        return pValues[aIndex];
    };
    return {
        pValues.front(),
        At(0.01),
        At(0.05),
        At(0.50),
        At(0.95),
        pValues.back(),
    };
}

void PrintNearestSummary(const char *pName,
                         const DistanceSummary &pSummary) {
    std::printf("    %-11s min=%d p01=%d p05=%d median=%d p95=%d max=%d\n",
                pName,
                pSummary.mMinimum,
                pSummary.mP01,
                pSummary.mP05,
                pSummary.mMedian,
                pSummary.mP95,
                pSummary.mMaximum);
}

void AnalyzeSelectedOutput(const std::vector<ScaffoldPack> &pPacks,
                           const std::uint64_t pIterationCount) {
    const std::vector<int> aFamilyLengths =
        FamilyLengthsOneCandidate();
    std::vector<const ScaffoldPlan *> aPlans;
    aPlans.reserve(kOutputLoopCount);
    std::size_t aPackIndex = 0U;
    for (std::size_t aCandidate = 0U;
         aCandidate < kCandidateCount;
         ++aCandidate) {
        for (const int aFamilyLength : aFamilyLengths) {
            const ScaffoldPack &aPack = pPacks[aPackIndex++];
            for (int aLoop = 0; aLoop < aFamilyLength; ++aLoop) {
                aPlans.push_back(
                    &aPack.mPlans[static_cast<std::size_t>(aLoop)]);
            }
        }
    }

    std::array<std::size_t, kCoreCount> aCoreCounts{};
    std::array<std::array<std::size_t, kRoleCount>, kRoleCount>
        aAssignmentPairCounts{};
    std::array<std::array<std::size_t, kRoleCount>, kRoleCount>
        aUpdatePairCounts{};
    std::array<std::array<std::size_t, 4U>, kRoleCount>
        aAssignmentContextCounts{};
    std::array<std::array<std::size_t, 4U>, kRoleCount>
        aUpdateContextCounts{};
    std::size_t aForbiddenUpdatePairCount = 0U;
    std::vector<int> aArrivalMaximums;
    std::vector<int> aArrivalTotals;
    std::vector<int> aArrivalSkews;
    std::vector<int> aFlowStalls;
    std::vector<int> aFlowAreas;
    std::vector<int> aDominatedUpdatePairCounts;
    std::vector<int> aMultiRouteSourceCounts;
    std::vector<int> aUpdateHeartSeparationMinimums;
    std::vector<int> aUpdateHeartSeparationTotals;
    std::array<std::vector<int>, kCoreCount>
        aDominatedUpdatePairCountsByCore;
    aArrivalMaximums.reserve(aPlans.size());
    aArrivalTotals.reserve(aPlans.size());
    aArrivalSkews.reserve(aPlans.size());
    aFlowStalls.reserve(aPlans.size());
    aFlowAreas.reserve(aPlans.size());
    aDominatedUpdatePairCounts.reserve(aPlans.size());
    aMultiRouteSourceCounts.reserve(aPlans.size());
    aUpdateHeartSeparationMinimums.reserve(aPlans.size());
    aUpdateHeartSeparationTotals.reserve(aPlans.size());

    std::vector<EncodedScaffold> aEncoded;
    aEncoded.reserve(aPlans.size());
    for (const ScaffoldPlan *aPlan : aPlans) {
        const HeartDistanceMatrix aHeartDistances =
            HeartTemporalDistances(*aPlan);
        aArrivalMaximums.push_back(
            aPlan->mScore.mMaximumWandererArrivalStep);
        aArrivalTotals.push_back(
            aPlan->mScore.mWandererArrivalStepTotal);
        aArrivalSkews.push_back(
            aPlan->mScore.mMaximumSourceArrivalSkew);
        aFlowStalls.push_back(
            aPlan->mScore.mLongestFlowStall);
        aFlowAreas.push_back(
            aPlan->mScore.mFlowInfluenceArea);
        aDominatedUpdatePairCounts.push_back(
            aPlan->mScore.mDominatedUpdatePairCount);
        aDominatedUpdatePairCountsByCore[aPlan->mCoreIndex].push_back(
            aPlan->mScore.mDominatedUpdatePairCount);
        aMultiRouteSourceCounts.push_back(
            aPlan->mScore.mMinimumHeartMultiRouteSources);
        aUpdateHeartSeparationMinimums.push_back(
            aPlan->mScore.mMinimumUpdateHeartSeparation);
        aUpdateHeartSeparationTotals.push_back(
            aPlan->mScore.mUpdateHeartSeparationTotal);
        ++aCoreCounts[aPlan->mCoreIndex];
        for (std::size_t i = 0U; i < kRoleCount; ++i) {
            ++aAssignmentPairCounts[aPlan->mAssignmentTarget[i]]
                                   [aPlan->mAssignmentWanderer[i]];
            const std::size_t aPairLo = std::min(
                aPlan->mUpdateOrbiterA[i],
                aPlan->mUpdateOrbiterB[i]);
            const std::size_t aPairHi = std::max(
                aPlan->mUpdateOrbiterA[i],
                aPlan->mUpdateOrbiterB[i]);
            ++aUpdatePairCounts[aPairLo][aPairHi];
            aForbiddenUpdatePairCount += HeartPairSeparation(
                aHeartDistances,
                aPlan->mUpdateOrbiterA[i],
                aPlan->mUpdateOrbiterB[i]) <= 1;
            ++aAssignmentContextCounts[aPlan->mAssignmentTarget[i]]
                                      [aPlan->mAssignmentContext[i]];
            ++aUpdateContextCounts[aPlan->mUpdateTarget[i]]
                                  [aPlan->mUpdateContext[i]];
        }
        aEncoded.push_back(EncodeScaffold(*aPlan));
    }

    std::vector<int> aNearestAssignment(aPlans.size(), 1000);
    std::vector<int> aNearestHeart(aPlans.size(), 1000);
    std::vector<int> aNearestUpdate(aPlans.size(), 1000);
    std::vector<int> aNearestWhole(aPlans.size(), 1000);
    int aNearestHeartSameCore = std::numeric_limits<int>::max();
    int aNearestHeartDifferentCore = std::numeric_limits<int>::max();
    for (std::size_t i = 0U; i < aEncoded.size(); ++i) {
        for (std::size_t j = i + 1U; j < aEncoded.size(); ++j) {
            int aAssignment = 0;
            int aHeart = 0;
            int aUpdate = 0;
            EncodedDistances(aEncoded[i], aEncoded[j],
                             &aAssignment, &aHeart, &aUpdate);
            const int aWhole = aAssignment + aHeart + aUpdate;
            aNearestAssignment[i] = std::min(aNearestAssignment[i],
                                             aAssignment);
            aNearestAssignment[j] = std::min(aNearestAssignment[j],
                                             aAssignment);
            aNearestHeart[i] = std::min(aNearestHeart[i], aHeart);
            aNearestHeart[j] = std::min(aNearestHeart[j], aHeart);
            if (aPlans[i]->mCoreIndex == aPlans[j]->mCoreIndex) {
                aNearestHeartSameCore = std::min(
                    aNearestHeartSameCore, aHeart);
            } else {
                aNearestHeartDifferentCore = std::min(
                    aNearestHeartDifferentCore, aHeart);
            }
            aNearestUpdate[i] = std::min(aNearestUpdate[i], aUpdate);
            aNearestUpdate[j] = std::min(aNearestUpdate[j], aUpdate);
            aNearestWhole[i] = std::min(aNearestWhole[i], aWhole);
            aNearestWhole[j] = std::min(aNearestWhole[j], aWhole);
        }
    }

    auto MinMaxMatrix = [](const auto &pMatrix,
                           const bool pUpperTriangleOnly) {
        std::size_t aMinimum = std::numeric_limits<std::size_t>::max();
        std::size_t aMaximum = 0U;
        for (std::size_t i = 0U; i < pMatrix.size(); ++i) {
            for (std::size_t j = 0U; j < pMatrix[i].size(); ++j) {
                if (pUpperTriangleOnly && (j <= i)) {
                    continue;
                }
                aMinimum = std::min(aMinimum, pMatrix[i][j]);
                aMaximum = std::max(aMaximum, pMatrix[i][j]);
            }
        }
        return std::pair<std::size_t, std::size_t>(aMinimum, aMaximum);
    };

    const auto aAssignmentPairs = MinMaxMatrix(aAssignmentPairCounts, false);
    std::size_t aUpdatePairMinimum =
        std::numeric_limits<std::size_t>::max();
    std::size_t aUpdatePairMaximum = 0U;
    for (std::size_t i = 0U; i < kRoleCount; ++i) {
        for (std::size_t j = i + 1U; j < kRoleCount; ++j) {
            aUpdatePairMinimum = std::min(
                aUpdatePairMinimum, aUpdatePairCounts[i][j]);
            aUpdatePairMaximum = std::max(
                aUpdatePairMaximum, aUpdatePairCounts[i][j]);
        }
    }
    const auto aAssignmentContexts =
        MinMaxMatrix(aAssignmentContextCounts, false);
    const auto aUpdateContexts =
        MinMaxMatrix(aUpdateContextCounts, false);
    const auto aCoreRange = std::minmax_element(aCoreCounts.begin(),
                                               aCoreCounts.end());
    PlanScore aComponentwiseDependencyFloor =
        aPlans.front()->mScore;
    for (const ScaffoldPlan *aPlan : aPlans) {
        KeepComponentwiseMinimum(aPlan->mScore,
                                 &aComponentwiseDependencyFloor);
    }
    const DistanceSummary aAssignmentSummary =
        SummarizeDistances(aNearestAssignment);
    const DistanceSummary aHeartSummary =
        SummarizeDistances(aNearestHeart);
    const DistanceSummary aUpdateSummary =
        SummarizeDistances(aNearestUpdate);
    const DistanceSummary aWholeSummary =
        SummarizeDistances(aNearestWhole);
    const DistanceSummary aArrivalMaximumSummary =
        SummarizeDistances(aArrivalMaximums);
    const DistanceSummary aArrivalTotalSummary =
        SummarizeDistances(aArrivalTotals);
    const DistanceSummary aArrivalSkewSummary =
        SummarizeDistances(aArrivalSkews);
    const DistanceSummary aFlowStallSummary =
        SummarizeDistances(aFlowStalls);
    const DistanceSummary aFlowAreaSummary =
        SummarizeDistances(aFlowAreas);
    const DistanceSummary aDominatedUpdateSummary =
        SummarizeDistances(aDominatedUpdatePairCounts);
    const DistanceSummary aMultiRouteSourceSummary =
        SummarizeDistances(aMultiRouteSourceCounts);
    const DistanceSummary aUpdateHeartSeparationMinimumSummary =
        SummarizeDistances(aUpdateHeartSeparationMinimums);
    const DistanceSummary aUpdateHeartSeparationTotalSummary =
        SummarizeDistances(aUpdateHeartSeparationTotals);
    const int aFirstCoverageFloor = std::min(
        aComponentwiseDependencyFloor.mMinimumWandererInfluence *
            static_cast<int>(kRoleCount),
        aComponentwiseDependencyFloor.mMinimumInputCoverage *
            static_cast<int>(kFirstIterationSourceCount));
    const int aFirstCoverageDenominator =
        static_cast<int>(kRoleCount * kFirstIterationSourceCount);
    const int aSecondCoverageFloor = std::min(
        aComponentwiseDependencyFloor.
            mSecondIterationMinimumWandererInfluence *
            static_cast<int>(kRoleCount),
        aComponentwiseDependencyFloor.
            mSecondIterationMinimumInputCoverage *
            static_cast<int>(kSecondIterationSourceCount));
    const int aSecondCoverageDenominator =
        static_cast<int>(kRoleCount * kSecondIterationSourceCount);
    int aAdjacentSameCoreCount = 0;
    int aMinimumAdjacentWholeDistance =
        std::numeric_limits<int>::max();
    for (std::size_t aCandidate = 0U;
         aCandidate < kCandidateCount;
         ++aCandidate) {
        const std::size_t aCandidateBase =
            aCandidate * kLoopsPerCandidate;
        for (std::size_t i = 1U; i < kLoopsPerCandidate; ++i) {
            const ScaffoldPlan &aPrevious =
                *aPlans[aCandidateBase + i - 1U];
            const ScaffoldPlan &aCurrent =
                *aPlans[aCandidateBase + i];
            aAdjacentSameCoreCount +=
                aPrevious.mCoreIndex == aCurrent.mCoreIndex;
            aMinimumAdjacentWholeDistance = std::min(
                aMinimumAdjacentWholeDistance,
                WholeDistance(aPrevious, aCurrent));
        }
    }
    const std::size_t aPairComparisonCount =
        (aPlans.size() * (aPlans.size() - 1U)) / 2U;

    std::printf("Loop scaffold structural analysis (%zu exact pair comparisons):\n",
                aPairComparisonCount);
    std::printf("    core counts min=%zu max=%zu\n",
                *aCoreRange.first,
                *aCoreRange.second);
    std::printf("    assignment role-pair counts min=%zu max=%zu\n",
                aAssignmentPairs.first,
                aAssignmentPairs.second);
    std::printf("    update role-pair counts min=%zu max=%zu"
                " heart_distance_le_1=%zu\n",
                aUpdatePairMinimum,
                aUpdatePairMaximum,
                aForbiddenUpdatePairCount);
    std::printf("    assignment target/context counts min=%zu max=%zu\n",
                aAssignmentContexts.first,
                aAssignmentContexts.second);
    std::printf("    update target/context counts min=%zu max=%zu\n",
                aUpdateContexts.first,
                aUpdateContexts.second);
    std::printf("    componentwise dependency floor: wanderer_min=%d input_coverage=%d "
                "second_wanderer_min=%d second_input_coverage=%d "
                "arrival_max=%d arrival_total=%d arrival_skew=%d "
                "stall_max=%d flow_area=%d update_union_min=%d "
                "update_overlap_min=%d update_unique_side_min=%d "
                "update_heart_separation_min=%d "
                "update_heart_separation_total=%d "
                "dominated_update_pairs_max=%d "
                "multi_route_sources_min=%d route_total=%d "
                "orbiter_min=%d complement_min=%d middle=%d early=%d\n",
                aComponentwiseDependencyFloor.mMinimumWandererInfluence,
                aComponentwiseDependencyFloor.mMinimumInputCoverage,
                aComponentwiseDependencyFloor.
                    mSecondIterationMinimumWandererInfluence,
                aComponentwiseDependencyFloor.
                    mSecondIterationMinimumInputCoverage,
                aComponentwiseDependencyFloor.
                    mMaximumWandererArrivalStep,
                aComponentwiseDependencyFloor.
                    mWandererArrivalStepTotal,
                aComponentwiseDependencyFloor.
                    mMaximumSourceArrivalSkew,
                aComponentwiseDependencyFloor.mLongestFlowStall,
                aComponentwiseDependencyFloor.mFlowInfluenceArea,
                aComponentwiseDependencyFloor.mMinimumUpdateUnion,
                aComponentwiseDependencyFloor.mMinimumUpdateOverlap,
                aComponentwiseDependencyFloor.
                    mMinimumUpdateUniqueSide,
                aComponentwiseDependencyFloor.
                    mMinimumUpdateHeartSeparation,
                aComponentwiseDependencyFloor.
                    mUpdateHeartSeparationTotal,
                aComponentwiseDependencyFloor.
                    mDominatedUpdatePairCount,
                aComponentwiseDependencyFloor.
                    mMinimumHeartMultiRouteSources,
                aComponentwiseDependencyFloor.
                    mHeartRouteMultiplicityTotal,
                aComponentwiseDependencyFloor.mMinimumOrbiterInfluence,
                aComponentwiseDependencyFloor.mMinimumComplement,
                aComponentwiseDependencyFloor.mMiddleInfluence,
                aComponentwiseDependencyFloor.mEarlyInfluence);
    std::printf("    nearest-neighbor structural distances:\n");
    PrintNearestSummary("assignment", aAssignmentSummary);
    PrintNearestSummary("heart", aHeartSummary);
    std::printf("    heart split same-core min=%d different-core min=%d\n",
                aNearestHeartSameCore,
                aNearestHeartDifferentCore);
    PrintNearestSummary("update", aUpdateSummary);
    PrintNearestSummary("whole", aWholeSummary);
    std::printf("    retained flow metric distributions:\n");
    PrintNearestSummary("arrival_max", aArrivalMaximumSummary);
    PrintNearestSummary("arrival_sum", aArrivalTotalSummary);
    PrintNearestSummary("arrival_skew", aArrivalSkewSummary);
    PrintNearestSummary("flow_stall", aFlowStallSummary);
    PrintNearestSummary("flow_area", aFlowAreaSummary);
    PrintNearestSummary("dominated", aDominatedUpdateSummary);
    PrintNearestSummary("multi_route", aMultiRouteSourceSummary);
    PrintNearestSummary("heart_sep_min",
                        aUpdateHeartSeparationMinimumSummary);
    PrintNearestSummary("heart_sep_sum",
                        aUpdateHeartSeparationTotalSummary);
    for (std::size_t i = 0U; i < kCoreCount; ++i) {
        const DistanceSummary aCoreDominatedSummary =
            SummarizeDistances(aDominatedUpdatePairCountsByCore[i]);
        char aName[16]{};
        std::snprintf(aName, sizeof(aName), "dom_core_%zu", i);
        PrintNearestSummary(aName, aCoreDominatedSummary);
    }
    std::printf("    execution order: adjacent_same_core=%d "
                "minimum_adjacent_whole_distance=%d\n",
                aAdjacentSameCoreCount,
                aMinimumAdjacentWholeDistance);

    const auto EmitSummary = [](std::ostringstream *pStream,
                                const char *pName,
                                const DistanceSummary &pSummary,
                                const bool pTrailingComma) {
        *pStream << "    \"" << pName << "\": {"
                 << "\"min\": " << pSummary.mMinimum
                 << ", \"p01\": " << pSummary.mP01
                 << ", \"p05\": " << pSummary.mP05
                 << ", \"median\": " << pSummary.mMedian
                 << ", \"p95\": " << pSummary.mP95
                 << ", \"max\": " << pSummary.mMaximum
                 << "}" << (pTrailingComma ? "," : "") << "\n";
    };
    std::ostringstream aReport;
    aReport << "{\n"
            << "  \"format_version\": 8,\n"
            << "  \"measurement_scope\": \"complete generated-loop "
               "structural dependency propagation; not cryptographic "
               "output-bit testing\",\n"
            << "  \"dependency_model\": \"context replacement, scatter, "
               "orbiter assignment, heart, ingress crush, wanderer update, "
               "and carry crush in generated execution order\",\n"
            << "  \"tracked_sources\": {\"iteration_one\": "
            << kFirstIterationSourceCount
            << ", \"iteration_two\": "
            << kSecondIterationSourceCount << "},\n"
            << "  \"coverage_ranking\": \"maximize the worse normalized "
               "row/column dependency coverage, then their combined "
               "coverage\",\n"
            << "  \"flow_timing_model\": \"25 ordered structural steps "
               "per iteration: assignment, 11 heart rounds, ingress crush, "
               "11 wanderer updates, and carry crush\",\n"
            << "  \"maximum_arrival_note\": \"reported but not ranked; "
               "the sequential N11 update shape fixes it for every valid "
               "scaffold\",\n"
            << "  \"route_metric_scope\": \"capped temporal route "
               "multiplicity through the heart; not vertex-disjoint-path "
               "proof\",\n"
            << "  \"heart_separation_model\": \"shortest causal path "
               "through the concrete, round-ordered heart; unreachable "
               "within one heart is represented as role_count_plus_one\",\n"
            << "  \"flow_area_scope\": \"sum of orbiter dependency "
               "populations after assignment and each heart round, plus "
               "wanderer dependency populations after each update\",\n"
            << "  \"context_timing_scope\": \"previous, fresh ingress, "
               "fresh cross, and carry/scatter influence are tracked through "
               "their actual assignment and update positions\",\n"
            << "  \"distance_basis\": \"assignment and update phases "
               "canonicalized by destination; heart remains round-ordered\",\n"
            << "  \"candidate_iterations\": "
            << pIterationCount << ",\n"
            << "  \"plan_trials_per_core\": "
            << kPlanTrialsPerCore << ",\n"
            << "  \"update_pair_schedule_trials\": "
            << kUpdatePairScheduleTrials << ",\n"
            << "  \"emitted_loops\": " << aPlans.size() << ",\n"
            << "  \"exact_pair_comparisons\": "
            << aPairComparisonCount << ",\n"
            << "  \"balance\": {\n"
            << "    \"core_min\": " << *aCoreRange.first << ",\n"
            << "    \"core_max\": " << *aCoreRange.second << ",\n"
            << "    \"assignment_pair_min\": "
            << aAssignmentPairs.first << ",\n"
            << "    \"assignment_pair_max\": "
            << aAssignmentPairs.second << ",\n"
            << "    \"update_role_pair_min\": "
            << aUpdatePairMinimum << ",\n"
            << "    \"update_role_pair_max\": "
            << aUpdatePairMaximum << ",\n"
            << "    \"heart_distance_le_1_update_pair_uses\": "
            << aForbiddenUpdatePairCount << ",\n"
            << "    \"assignment_context_min\": "
            << aAssignmentContexts.first << ",\n"
            << "    \"assignment_context_max\": "
            << aAssignmentContexts.second << ",\n"
            << "    \"update_context_min\": "
            << aUpdateContexts.first << ",\n"
            << "    \"update_context_max\": "
            << aUpdateContexts.second << "\n"
            << "  },\n"
            << "  \"componentwise_dependency_floor\": {\n"
            << "    \"minimum_wanderer_influence\": "
            << aComponentwiseDependencyFloor.mMinimumWandererInfluence << ",\n"
            << "    \"minimum_input_coverage\": "
            << aComponentwiseDependencyFloor.mMinimumInputCoverage << ",\n"
            << "    \"second_iteration_minimum_wanderer_influence\": "
            << aComponentwiseDependencyFloor.
                mSecondIterationMinimumWandererInfluence << ",\n"
            << "    \"second_iteration_minimum_input_coverage\": "
            << aComponentwiseDependencyFloor.
                mSecondIterationMinimumInputCoverage << ",\n"
            << "    \"first_iteration_normalized_floor\": {"
            << "\"numerator\": " << aFirstCoverageFloor
            << ", \"denominator\": " << aFirstCoverageDenominator
            << "},\n"
            << "    \"second_iteration_normalized_floor\": {"
            << "\"numerator\": " << aSecondCoverageFloor
            << ", \"denominator\": " << aSecondCoverageDenominator
            << "},\n"
            << "    \"maximum_wanderer_arrival_step\": "
            << aComponentwiseDependencyFloor.
                mMaximumWandererArrivalStep << ",\n"
            << "    \"wanderer_arrival_step_total\": "
            << aComponentwiseDependencyFloor.
                mWandererArrivalStepTotal << ",\n"
            << "    \"maximum_source_arrival_skew\": "
            << aComponentwiseDependencyFloor.
                mMaximumSourceArrivalSkew << ",\n"
            << "    \"longest_flow_stall\": "
            << aComponentwiseDependencyFloor.mLongestFlowStall << ",\n"
            << "    \"flow_influence_area\": "
            << aComponentwiseDependencyFloor.mFlowInfluenceArea << ",\n"
            << "    \"minimum_update_union\": "
            << aComponentwiseDependencyFloor.mMinimumUpdateUnion << ",\n"
            << "    \"minimum_update_overlap\": "
            << aComponentwiseDependencyFloor.mMinimumUpdateOverlap << ",\n"
            << "    \"minimum_update_unique_side\": "
            << aComponentwiseDependencyFloor.
                mMinimumUpdateUniqueSide << ",\n"
            << "    \"minimum_update_heart_separation\": "
            << aComponentwiseDependencyFloor.
                mMinimumUpdateHeartSeparation << ",\n"
            << "    \"update_heart_separation_total\": "
            << aComponentwiseDependencyFloor.
                mUpdateHeartSeparationTotal << ",\n"
            << "    \"maximum_dominated_update_pair_count\": "
            << aComponentwiseDependencyFloor.
                mDominatedUpdatePairCount << ",\n"
            << "    \"minimum_heart_multi_route_sources\": "
            << aComponentwiseDependencyFloor.
                mMinimumHeartMultiRouteSources << ",\n"
            << "    \"heart_route_multiplicity_total\": "
            << aComponentwiseDependencyFloor.
                mHeartRouteMultiplicityTotal << ",\n"
            << "    \"minimum_orbiter_influence\": "
            << aComponentwiseDependencyFloor.mMinimumOrbiterInfluence << ",\n"
            << "    \"minimum_complement\": "
            << aComponentwiseDependencyFloor.mMinimumComplement << ",\n"
            << "    \"middle_influence\": "
            << aComponentwiseDependencyFloor.mMiddleInfluence << ",\n"
            << "    \"early_influence\": "
            << aComponentwiseDependencyFloor.mEarlyInfluence << ",\n"
            << "    \"wanderer_influence_total\": "
            << aComponentwiseDependencyFloor.mWandererInfluenceTotal << ",\n"
            << "    \"orbiter_influence_total\": "
            << aComponentwiseDependencyFloor.mOrbiterInfluenceTotal << ",\n"
            << "    \"update_pair_complement_total\": "
            << aComponentwiseDependencyFloor.mUpdatePairComplementTotal << "\n"
            << "  },\n"
            << "  \"nearest_neighbor_distance\": {\n";
    EmitSummary(&aReport, "assignment", aAssignmentSummary, true);
    EmitSummary(&aReport, "heart", aHeartSummary, true);
    EmitSummary(&aReport, "update", aUpdateSummary, true);
    EmitSummary(&aReport, "whole", aWholeSummary, false);
    aReport << "  },\n"
            << "  \"flow_metric_distribution\": {\n";
    EmitSummary(&aReport, "maximum_arrival", aArrivalMaximumSummary, true);
    EmitSummary(&aReport, "arrival_total", aArrivalTotalSummary, true);
    EmitSummary(&aReport, "maximum_arrival_skew", aArrivalSkewSummary, true);
    EmitSummary(&aReport, "longest_stall", aFlowStallSummary, true);
    EmitSummary(&aReport, "influence_area", aFlowAreaSummary, true);
    EmitSummary(&aReport, "dominated_update_pairs", aDominatedUpdateSummary, true);
    EmitSummary(&aReport, "minimum_multi_route_sources", aMultiRouteSourceSummary, true);
    EmitSummary(&aReport, "minimum_update_heart_separation",
                aUpdateHeartSeparationMinimumSummary, true);
    EmitSummary(&aReport, "update_heart_separation_total",
                aUpdateHeartSeparationTotalSummary, false);
    aReport << "  },\n"
            << "  \"heart_minimum_by_relation\": {"
            << "\"same_core\": " << aNearestHeartSameCore
            << ", \"different_core\": "
            << aNearestHeartDifferentCore << "},\n"
            << "  \"execution_order\": {"
            << "\"adjacent_same_core\": "
            << aAdjacentSameCoreCount
            << ", \"minimum_adjacent_whole_distance\": "
            << aMinimumAdjacentWholeDistance << "},\n"
            << "  \"hard_guarantees\": [\n"
            << "    \"all fixed heart cores are strongly connected and "
               "use every role exactly once as lead, source, and feedback\",\n"
            << "    \"all three emitted pieces are globally unique after "
               "canonicalizing independent phases by destination\",\n"
            << "    \"all role relabelings are even permutations\",\n"
            << "    \"the 55 reachable distance-six core-3/core-5 "
               "relationships are rejected\",\n"
            << "    \"zero-complement update pairs are rejected after "
               "heart propagation\",\n"
            << "    \"every update pair schedule preserves a minimum "
               "twelve-source dependency union\",\n"
            << "    \"every update pair has shared dependencies; schedules "
               "are ranked to minimize pairs where one side contributes no "
               "exclusive dependency\",\n"
            << "    \"direct causal heart pairs, plus repeated "
               "unordered update pairs, are rejected inside each loop\",\n"
            << "    \"all 17 modeled persistent and per-iteration fresh "
               "dependency classes reach every wanderer by the end of the "
               "second complete loop iteration\",\n"
            << "    \"consecutive emitted loops inside an expander never "
               "reuse the same ARX core\"\n"
            << "  ]\n"
            << "}\n";
    const std::string aReportText = aReport.str();
    const std::vector<std::uint8_t> aReportBytes(aReportText.begin(),
                                                aReportText.end());
    const std::string aReportPath = FileIO::ProjectRoot(
        FileIO::Join("MeanMachine", "LoopScaffolds11_Analysis.json"));
    if (FileIO::Save(aReportPath, aReportBytes)) {
        std::printf("Loop scaffold farmer wrote %s\n",
                    aReportPath.c_str());
    } else {
        std::printf("Loop scaffold farmer could not write %s\n",
                    aReportPath.c_str());
    }
}

bool SaveHeader(const char *pFileName,
                const std::vector<ScaffoldPack> &pPacks,
                std::string *pErrorMessage) {
    if (pPacks.size() != kPackCount) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Loop scaffold farmer had the wrong pack count";
        }
        return false;
    }
    const std::vector<int> aFamilyLengths =
        FamilyLengthsOneCandidate();
    int aLoopCount = 0;
    for (const int aLength : aFamilyLengths) {
        aLoopCount += aLength;
    }
    if ((aFamilyLengths.size() != kFamiliesPerCandidate) ||
        (aLoopCount != static_cast<int>(kLoopsPerCandidate))) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Loop scaffold family schedule did not total 584 loops";
        }
        return false;
    }

    if (!ValidateSelectedOutput(pPacks, pErrorMessage)) {
        return false;
    }

    const std::string aText = EmitHeader(pPacks);
    const std::string aPath = FileIO::ProjectRoot(
        FileIO::Join("MeanMachine", pFileName));
    const std::vector<std::uint8_t> aBytes(aText.begin(), aText.end());
    if (!FileIO::Save(aPath, aBytes)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Loop scaffold farmer failed to save " + aPath;
        }
        return false;
    }
    std::printf("Loop scaffold farmer wrote %s\n", aPath.c_str());
    return true;
}

} // namespace

bool LoopScaffoldFarmer::Run(const std::uint64_t pIterationCount,
                             std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    if (pIterationCount == 0ULL) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Loop scaffold farming needs a positive iteration count";
        }
        return false;
    }
    if (!ValidateCoreScaffolds(pErrorMessage)) {
        return false;
    }

    using Clock = std::chrono::steady_clock;
    const auto aStart = Clock::now();
    const std::uint64_t aProgressIterationInterval =
        std::min<std::uint64_t>(
            kProgressIterationInterval,
            std::max<std::uint64_t>(1000ULL, pIterationCount / 20ULL));
    std::uint64_t aNextProgress = aProgressIterationInterval;
    std::uint64_t aNextCheckpoint = kCheckpointIterationInterval;

    Generator aGenerator(0xD6A17B903C5E42F1ULL);
    PackHeap aBest;
    std::unordered_set<std::string> aAssignments;
    std::unordered_set<std::string> aHearts;
    std::unordered_set<std::string> aUpdates;
    std::array<std::unordered_set<std::uint64_t>, kCoreCount>
        aRolePermutations;
    aAssignments.reserve(kPackCount * 12U);
    aHearts.reserve(kPackCount * 12U);
    aUpdates.reserve(kPackCount * 12U);
    for (auto &aCorePermutations : aRolePermutations) {
        aCorePermutations.reserve(kPackCount * 2U);
    }

    std::uint64_t aAttempts = 0ULL;
    std::uint64_t aValid = 0ULL;
    std::uint64_t aReplacements = 0ULL;

    std::printf("Loop scaffold farmer: %llu candidate iterations, "
                "%zu retained six-packs, "
                "three globally unique pieces per retained loop\n",
                static_cast<unsigned long long>(pIterationCount),
                kPackCount);
    std::fflush(stdout);

    while (aAttempts < pIterationCount) {
        const std::uint64_t aRemaining = pIterationCount - aAttempts;
        const std::size_t aBatchCount = static_cast<std::size_t>(
            std::min<std::uint64_t>(256ULL, aRemaining));
        for (std::size_t aBatch = 0U; aBatch < aBatchCount; ++aBatch) {
            ++aAttempts;
            ScaffoldPack aCandidate;
            if (!GeneratePack(&aGenerator, &aCandidate)) {
                continue;
            }
            ++aValid;

            if (aBest.size() >= kPackCount &&
                !PackIsBetter(aCandidate, aBest.top())) {
                continue;
            }
            if (!PackKeysAreUnique(aCandidate,
                                   aAssignments,
                                   aHearts,
                                   aUpdates) ||
                !CrossCoreHeartIsSeparated(aCandidate,
                                           aRolePermutations)) {
                continue;
            }

            if (aBest.size() >= kPackCount) {
                RemovePackKeys(aBest.top(),
                               &aAssignments,
                               &aHearts,
                               &aUpdates,
                               &aRolePermutations);
                aBest.pop();
                ++aReplacements;
            }
            AddPackKeys(aCandidate,
                        &aAssignments,
                        &aHearts,
                        &aUpdates,
                        &aRolePermutations);
            aBest.push(aCandidate);
        }

        const auto aNow = Clock::now();
        if (aAttempts >= aNextProgress) {
            const double aSeconds =
                std::chrono::duration<double>(aNow - aStart).count();
            std::printf("scaffold farm %llu/%llu: valid=%llu "
                        "retained=%zu replacements=%llu rate=%.0f packs/s",
                        static_cast<unsigned long long>(aAttempts),
                        static_cast<unsigned long long>(pIterationCount),
                        static_cast<unsigned long long>(aValid),
                        aBest.size(),
                        static_cast<unsigned long long>(aReplacements),
                        static_cast<double>(aAttempts) / aSeconds);
            if (!aBest.empty()) {
                std::printf(" weakest_dependency={wanderer:%d "
                            "input_coverage:%d second_wanderer:%d "
                            "second_input_coverage:%d arrival:%d "
                            "skew:%d} "
                            "pack_min={assignment:%d heart:%d "
                            "update:%d whole:%d}",
                            aBest.top().mWorstScore.
                                mMinimumWandererInfluence,
                            aBest.top().mWorstScore.
                                mMinimumInputCoverage,
                            aBest.top().mWorstScore.
                                mSecondIterationMinimumWandererInfluence,
                            aBest.top().mWorstScore.
                                mSecondIterationMinimumInputCoverage,
                            aBest.top().mWorstScore.
                                mMaximumWandererArrivalStep,
                            aBest.top().mWorstScore.
                                mMaximumSourceArrivalSkew,
                            aBest.top().mMinimumAssignmentDistance,
                            aBest.top().mMinimumHeartDistance,
                            aBest.top().mMinimumUpdateDistance,
                            aBest.top().mMinimumDistance);
            }
            std::printf("\n");
            std::fflush(stdout);
            aNextProgress += aProgressIterationInterval;
        }

        if ((aAttempts >= aNextCheckpoint) &&
            (aBest.size() == kPackCount)) {
            const std::vector<ScaffoldPack> aCheckpoint =
                FinalizePacks(aBest);
            if (!SaveHeader("LoopScaffolds11_FarmingCheckpoint.hpp",
                            aCheckpoint,
                            pErrorMessage)) {
                return false;
            }
            aNextCheckpoint += kCheckpointIterationInterval;
        }
    }

    if (aBest.size() != kPackCount) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Loop scaffold farmer ended before filling its winner set";
        }
        return false;
    }

    const std::vector<ScaffoldPack> aSelected = FinalizePacks(aBest);
    AnalyzeSelectedOutput(aSelected, aAttempts);
    if (!SaveHeader("LoopScaffolds11_FarmingCheckpoint.hpp",
                    aSelected,
                    pErrorMessage) ||
        !SaveHeader("LoopScaffolds11.hpp",
                    aSelected,
                    pErrorMessage)) {
        return false;
    }

    const double aSeconds =
        std::chrono::duration<double>(Clock::now() - aStart).count();
    std::printf("Loop scaffold farming complete: iterations=%llu "
                "elapsed=%.1f minutes valid=%llu replacements=%llu, "
                "assignments=%zu hearts=%zu updates=%zu\n",
                static_cast<unsigned long long>(aAttempts),
                aSeconds / 60.0,
                static_cast<unsigned long long>(aValid),
                static_cast<unsigned long long>(aReplacements),
                aAssignments.size(),
                aHearts.size(),
                aUpdates.size());
    return true;
}
