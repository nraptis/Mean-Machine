#include "KeyLaneControl.hpp"

#include "ControlValueFile.hpp"
#include "FileIO.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <iomanip>
#include <limits>
#include <random>
#include <sstream>
#include <vector>

namespace {

using Assignment = KeyLaneControl::Assignment;
using Score = KeyLaneControl::Score;
using Slot = KeyLaneControl::Slot;

constexpr std::size_t kSplitCount = 16U;
constexpr std::size_t kCellCount =
    KeyLaneControl::kActiveCandidateCount *
    KeyLaneControl::kKeyFunctionCount;
constexpr std::size_t kOccupancyCellCount =
    kCellCount * kSplitCount;
constexpr std::size_t kRefinementPassCount = 2U;

struct FamilyDefinition {
    const char *mStem;
    std::array<Slot, KeyLaneControl::kFamilyLaneCount> mLanes;
};

constexpr std::array<FamilyDefinition,
                     KeyLaneControl::kFamilyCount> kFamilies = {{
    {"Earth", {Slot::kEarthLaneA, Slot::kEarthLaneB,
                Slot::kEarthLaneC, Slot::kEarthLaneD}},
    {"Fire", {Slot::kFireLaneA, Slot::kFireLaneB,
               Slot::kFireLaneC, Slot::kFireLaneD}},
    {"Wind", {Slot::kWindLaneA, Slot::kWindLaneB,
               Slot::kWindLaneC, Slot::kWindLaneD}},
    {"Water", {Slot::kWaterLaneA, Slot::kWaterLaneB,
                Slot::kWaterLaneC, Slot::kWaterLaneD}},
    {"Rainbow", {Slot::kRainbowLaneA, Slot::kRainbowLaneB,
                Slot::kRainbowLaneC, Slot::kRainbowLaneD}},
    {"Lightning", {Slot::kLightningLaneA, Slot::kLightningLaneB,
                    Slot::kLightningLaneC, Slot::kLightningLaneD}},
    {"Ice", {Slot::kIceLaneA, Slot::kIceLaneB,
              Slot::kIceLaneC, Slot::kIceLaneD}},
    {"Plasma", {Slot::kPlasmaLaneA, Slot::kPlasmaLaneB,
                 Slot::kPlasmaLaneC, Slot::kPlasmaLaneD}},
    {"Shadow", {Slot::kShadowLaneA, Slot::kShadowLaneB,
                 Slot::kShadowLaneC, Slot::kShadowLaneD}},
    {"Crystal", {Slot::kCrystalLaneA, Slot::kCrystalLaneB,
                  Slot::kCrystalLaneC, Slot::kCrystalLaneD}},
    {"Aether", {Slot::kAetherLaneA, Slot::kAetherLaneB,
                 Slot::kAetherLaneC, Slot::kAetherLaneD}},
    {"Celestial", {Slot::kCelestialLaneA, Slot::kCelestialLaneB,
                    Slot::kCelestialLaneC, Slot::kCelestialLaneD}},
    {"Vapor", {Slot::kVaporLaneA, Slot::kVaporLaneB,
                Slot::kVaporLaneC, Slot::kVaporLaneD}},
    {"Kinetic", {Slot::kKineticLaneA, Slot::kKineticLaneB,
                  Slot::kKineticLaneC, Slot::kKineticLaneD}},
    {"Sonic", {Slot::kSonicLaneA, Slot::kSonicLaneB,
                Slot::kSonicLaneC, Slot::kSonicLaneD}},
    {"Planar", {Slot::kPlanarLaneA, Slot::kPlanarLaneB,
                 Slot::kPlanarLaneC, Slot::kPlanarLaneD}},
    {"Frost", {Slot::kFrostLaneA, Slot::kFrostLaneB,
                Slot::kFrostLaneC, Slot::kFrostLaneD}},
    {"Arcane", {Slot::kArcaneLaneA, Slot::kArcaneLaneB,
                 Slot::kArcaneLaneC, Slot::kArcaneLaneD}},
    {"Lunar", {Slot::kLunarLaneA, Slot::kLunarLaneB,
                Slot::kLunarLaneC, Slot::kLunarLaneD}},
    {"Runic", {Slot::kRunicLaneA, Slot::kRunicLaneB,
                Slot::kRunicLaneC, Slot::kRunicLaneD}},
    {"Gloom", {Slot::kGloomLaneA, Slot::kGloomLaneB,
                Slot::kGloomLaneC, Slot::kGloomLaneD}},
    {"Spirit", {Slot::kSpiritLaneA, Slot::kSpiritLaneB,
                 Slot::kSpiritLaneC, Slot::kSpiritLaneD}},
    {"Abjuration", {Slot::kAbjurationLaneA, Slot::kAbjurationLaneB,
                     Slot::kAbjurationLaneC, Slot::kAbjurationLaneD}},
    {"Divination", {Slot::kDivinationLaneA, Slot::kDivinationLaneB,
                     Slot::kDivinationLaneC, Slot::kDivinationLaneD}},
    {"Evocation", {Slot::kEvocationLaneA, Slot::kEvocationLaneB,
                    Slot::kEvocationLaneC, Slot::kEvocationLaneD}},
    {"Alchemy", {Slot::kAlchemyLaneA, Slot::kAlchemyLaneB,
                  Slot::kAlchemyLaneC, Slot::kAlchemyLaneD}},
    {"Augury", {Slot::kAuguryLaneA, Slot::kAuguryLaneB,
                 Slot::kAuguryLaneC, Slot::kAuguryLaneD}},
    {"Psychic", {Slot::kPsychicLaneA, Slot::kPsychicLaneB,
                  Slot::kPsychicLaneC, Slot::kPsychicLaneD}},
    {"Voodoo", {Slot::kVoodooLaneA, Slot::kVoodooLaneB,
                 Slot::kVoodooLaneC, Slot::kVoodooLaneD}},
}};

struct FamilyPlan {
    std::array<std::uint8_t, kSplitCount> mKeyBase{};
    std::array<std::uint8_t, kSplitCount> mSplitOrder{};
    std::array<std::uint8_t,
               KeyLaneControl::kFamilyLaneCount> mMemberOffsets{};
};

struct Evaluation {
    Score mScore{};
};

std::mt19937_64 sRandom;
std::array<Assignment, KeyLaneControl::kAssignmentCount> sAssignments{};
std::vector<FamilyPlan> sPlans;
Score sScore{};
bool sDidReset = false;
bool sHasValues = false;

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

template <std::size_t N>
void Shuffle(std::array<std::uint8_t, N> *pValues) {
    for (std::size_t i = 1U; i < N; ++i) {
        std::uniform_int_distribution<std::size_t> aDistribution(0U, i);
        std::swap((*pValues)[i], (*pValues)[aDistribution(sRandom)]);
    }
}

std::array<std::uint8_t, kSplitCount> RandomPermutation() {
    std::array<std::uint8_t, kSplitCount> aValues{};
    for (std::size_t i = 0U; i < aValues.size(); ++i) {
        aValues[i] = static_cast<std::uint8_t>(i);
    }
    Shuffle(&aValues);
    return aValues;
}

FamilyPlan RandomPlan() {
    FamilyPlan aPlan;
    aPlan.mKeyBase = RandomPermutation();
    aPlan.mSplitOrder = RandomPermutation();
    const std::array<std::uint8_t, kSplitCount> aOffsets =
        RandomPermutation();
    std::copy_n(aOffsets.begin(),
                aPlan.mMemberOffsets.size(),
                aPlan.mMemberOffsets.begin());
    return aPlan;
}

std::uint64_t Pack(
    const std::array<std::uint8_t, kSplitCount> &pValues) {
    std::uint64_t aPacked = 0ULL;
    for (std::size_t i = 0U; i < pValues.size(); ++i) {
        aPacked |= static_cast<std::uint64_t>(pValues[i]) << (4U * i);
    }
    return aPacked;
}

std::uint8_t Nibble(const std::uint64_t pPacked,
                    const std::size_t pIndex) {
    return static_cast<std::uint8_t>(
        (pPacked >> (4U * pIndex)) & 0x0FULL
    );
}

bool IsPermutation(const std::uint64_t pPacked) {
    std::uint16_t aSeen = 0U;
    for (std::size_t i = 0U; i < kSplitCount; ++i) {
        const std::uint16_t aBit = static_cast<std::uint16_t>(
            1U << Nibble(pPacked, i)
        );
        if ((aSeen & aBit) != 0U) {
            return false;
        }
        aSeen = static_cast<std::uint16_t>(aSeen | aBit);
    }
    return aSeen == 0xFFFFU;
}

std::uint8_t PlanSplit(const FamilyPlan &pPlan,
                       const std::size_t pMember,
                       const std::size_t pKey,
                       const std::size_t pCandidate) {
    const std::size_t aKeyPosition =
        (static_cast<std::size_t>(pPlan.mKeyBase[pKey]) +
         static_cast<std::size_t>(pPlan.mMemberOffsets[pMember])) & 15U;
    return pPlan.mSplitOrder[(aKeyPosition + pCandidate) & 15U];
}

std::uint8_t AssignmentSplit(const Assignment &pAssignment,
                             const std::size_t pKey,
                             const std::size_t pCandidate) {
    const std::size_t aKeyPosition = Nibble(pAssignment.mKeyOrder, pKey);
    return Nibble(pAssignment.mSplitOrder,
                  (aKeyPosition + pCandidate) & 15U);
}

std::array<Assignment, KeyLaneControl::kFamilyLaneCount>
AssignmentsForPlan(const std::size_t pFamilyIndex,
                   const FamilyPlan &pPlan) {
    std::array<Assignment, KeyLaneControl::kFamilyLaneCount> aResult{};
    for (std::size_t aMember = 0U;
         aMember < KeyLaneControl::kFamilyLaneCount;
         ++aMember) {
        std::array<std::uint8_t, kSplitCount> aKeyOrder{};
        for (std::size_t aKey = 0U; aKey < kSplitCount; ++aKey) {
            aKeyOrder[aKey] = static_cast<std::uint8_t>(
                (static_cast<std::size_t>(pPlan.mKeyBase[aKey]) +
                 static_cast<std::size_t>(
                     pPlan.mMemberOffsets[aMember])) & 15U
            );
        }
        aResult[aMember] = {
            kFamilies[pFamilyIndex].mLanes[aMember],
            Pack(aKeyOrder),
            Pack(pPlan.mSplitOrder),
        };
    }
    return aResult;
}

std::uint64_t SquareSigned(const std::int64_t pValue) {
    return static_cast<std::uint64_t>(pValue * pValue);
}

void AddFamilyRelationship(
    const FamilyPlan &pLeft,
    const FamilyPlan &pRight,
    std::uint16_t *pWorstRelativeFrequency,
    std::uint16_t *pWorstExactOverlap,
    std::uint64_t *pRelativePenalty) {
    std::array<std::array<std::uint8_t, kSplitCount>,
               kSplitCount> aOutputDifference{};
    for (std::size_t aInputDelta = 0U;
         aInputDelta < kSplitCount;
         ++aInputDelta) {
        for (std::size_t aPosition = 0U;
             aPosition < kSplitCount;
             ++aPosition) {
            const std::size_t aRightPosition =
                (aPosition + aInputDelta) & 15U;
            const std::size_t aOutputDelta =
                (static_cast<std::size_t>(
                     pRight.mSplitOrder[aRightPosition]) + 16U -
                 static_cast<std::size_t>(
                     pLeft.mSplitOrder[aPosition])) & 15U;
            ++aOutputDifference[aInputDelta][aOutputDelta];
        }
    }

    for (std::size_t aLeftMember = 0U;
         aLeftMember < KeyLaneControl::kFamilyLaneCount;
         ++aLeftMember) {
        for (std::size_t aRightMember = 0U;
             aRightMember < KeyLaneControl::kFamilyLaneCount;
             ++aRightMember) {
            std::array<std::uint16_t, kSplitCount> aRelativeCounts{};
            for (std::size_t aKey = 0U; aKey < kSplitCount; ++aKey) {
                const std::size_t aLeftKey =
                    static_cast<std::size_t>(pLeft.mKeyBase[aKey]) +
                    pLeft.mMemberOffsets[aLeftMember];
                const std::size_t aRightKey =
                    static_cast<std::size_t>(pRight.mKeyBase[aKey]) +
                    pRight.mMemberOffsets[aRightMember];
                const std::size_t aInputDelta =
                    (aRightKey + 16U - aLeftKey) & 15U;
                for (std::size_t aOutputDelta = 0U;
                     aOutputDelta < kSplitCount;
                     ++aOutputDelta) {
                    aRelativeCounts[aOutputDelta] =
                        static_cast<std::uint16_t>(
                            aRelativeCounts[aOutputDelta] +
                            aOutputDifference[aInputDelta][aOutputDelta]
                        );
                }
            }

            *pWorstExactOverlap = std::max(
                *pWorstExactOverlap,
                aRelativeCounts[0]
            );
            for (const std::uint16_t aCount : aRelativeCounts) {
                *pWorstRelativeFrequency = std::max(
                    *pWorstRelativeFrequency,
                    aCount
                );
                *pRelativePenalty += SquareSigned(
                    static_cast<std::int64_t>(aCount) - 16
                );
            }
        }
    }
}

std::array<std::uint64_t, 8U> FamilyPhysicalDistances(
    const FamilyPlan &pPlan) {
    std::array<std::uint64_t, 8U> aDistances{};
    for (std::size_t aLag = 1U; aLag <= 8U; ++aLag) {
        std::uint64_t aDistance = 0ULL;
        for (std::size_t aPosition = 0U;
             aPosition < kSplitCount;
             ++aPosition) {
            const int aLeft = pPlan.mSplitOrder[aPosition];
            const int aRight =
                pPlan.mSplitOrder[(aPosition + aLag) & 15U];
            aDistance += static_cast<std::uint64_t>(
                aLeft > aRight ? aLeft - aRight : aRight - aLeft
            );
        }
        aDistances[aLag - 1U] =
            aDistance * KeyLaneControl::kFamilyLaneCount;
    }
    return aDistances;
}

bool Better(const Evaluation &pCandidate,
            const Evaluation &pBest) {
    if (pCandidate.mScore.mMaximumOccupancy !=
        pBest.mScore.mMaximumOccupancy) {
        return pCandidate.mScore.mMaximumOccupancy <
               pBest.mScore.mMaximumOccupancy;
    }
    if (pCandidate.mScore.mMinimumOccupancy !=
        pBest.mScore.mMinimumOccupancy) {
        return pCandidate.mScore.mMinimumOccupancy >
               pBest.mScore.mMinimumOccupancy;
    }
    if (pCandidate.mScore.mOccupancyPenalty !=
        pBest.mScore.mOccupancyPenalty) {
        return pCandidate.mScore.mOccupancyPenalty <
               pBest.mScore.mOccupancyPenalty;
    }
    if (pCandidate.mScore.mWorstRelativeFrequency !=
        pBest.mScore.mWorstRelativeFrequency) {
        return pCandidate.mScore.mWorstRelativeFrequency <
               pBest.mScore.mWorstRelativeFrequency;
    }
    if (pCandidate.mScore.mWorstExactOverlap !=
        pBest.mScore.mWorstExactOverlap) {
        return pCandidate.mScore.mWorstExactOverlap <
               pBest.mScore.mWorstExactOverlap;
    }
    if (pCandidate.mScore.mMinimumCandidateDistance !=
        pBest.mScore.mMinimumCandidateDistance) {
        return pCandidate.mScore.mMinimumCandidateDistance >
               pBest.mScore.mMinimumCandidateDistance;
    }
    if (pCandidate.mScore.mRelativePenalty !=
        pBest.mScore.mRelativePenalty) {
        return pCandidate.mScore.mRelativePenalty <
               pBest.mScore.mRelativePenalty;
    }
    return pCandidate.mScore.mTotalCandidateDistance >
           pBest.mScore.mTotalCandidateDistance;
}

Evaluation EvaluatePlan(
    const FamilyPlan &pPlan,
    const std::vector<FamilyPlan> &pSelectedPlans,
    const std::array<std::uint16_t, kOccupancyCellCount> &pOccupancy,
    const std::array<std::uint64_t, 8U> &pPhysicalDistances,
    const Score &pCurrentScore) {
    Evaluation aEvaluation;
    aEvaluation.mScore = pCurrentScore;

    for (const FamilyPlan &aSelectedPlan : pSelectedPlans) {
        AddFamilyRelationship(aSelectedPlan,
                              pPlan,
                              &aEvaluation.mScore.mWorstRelativeFrequency,
                              &aEvaluation.mScore.mWorstExactOverlap,
                              &aEvaluation.mScore.mRelativePenalty);
    }

    const std::size_t aFamilyCount = pSelectedPlans.size() + 1U;
    std::array<std::uint16_t, kOccupancyCellCount> aOccupancy = pOccupancy;
    for (std::size_t aCandidate = 0U;
         aCandidate < KeyLaneControl::kActiveCandidateCount;
         ++aCandidate) {
        for (std::size_t aKey = 0U;
             aKey < KeyLaneControl::kKeyFunctionCount;
             ++aKey) {
            for (std::size_t aMember = 0U;
                 aMember < KeyLaneControl::kFamilyLaneCount;
                 ++aMember) {
                const std::size_t aSplit =
                    PlanSplit(pPlan, aMember, aKey, aCandidate);
                const std::size_t aIndex =
                    ((aCandidate * KeyLaneControl::kKeyFunctionCount +
                      aKey) * kSplitCount) + aSplit;
                ++aOccupancy[aIndex];
            }
        }
    }

    aEvaluation.mScore.mMinimumOccupancy =
        std::numeric_limits<std::uint16_t>::max();
    aEvaluation.mScore.mMaximumOccupancy = 0U;
    aEvaluation.mScore.mOccupancyPenalty = 0ULL;
    for (const std::uint16_t aCount : aOccupancy) {
        aEvaluation.mScore.mMinimumOccupancy = std::min(
            aEvaluation.mScore.mMinimumOccupancy,
            aCount
        );
        aEvaluation.mScore.mMaximumOccupancy = std::max(
            aEvaluation.mScore.mMaximumOccupancy,
            aCount
        );
        aEvaluation.mScore.mOccupancyPenalty += SquareSigned(
            (4 * static_cast<std::int64_t>(aCount)) -
            static_cast<std::int64_t>(aFamilyCount)
        );
    }

    const std::array<std::uint64_t, 8U> aAddedDistances =
        FamilyPhysicalDistances(pPlan);
    aEvaluation.mScore.mMinimumCandidateDistance =
        std::numeric_limits<std::uint64_t>::max();
    aEvaluation.mScore.mTotalCandidateDistance = 0ULL;
    for (std::size_t i = 0U; i < aAddedDistances.size(); ++i) {
        const std::uint64_t aDistance =
            pPhysicalDistances[i] + aAddedDistances[i];
        aEvaluation.mScore.mMinimumCandidateDistance = std::min(
            aEvaluation.mScore.mMinimumCandidateDistance,
            aDistance
        );
        aEvaluation.mScore.mTotalCandidateDistance += aDistance;
    }
    return aEvaluation;
}

void WritePlanAssignments(const std::size_t pFamilyIndex,
                          const FamilyPlan &pPlan) {
    const auto aFamilyAssignments =
        AssignmentsForPlan(pFamilyIndex, pPlan);
    for (std::size_t aMember = 0U;
         aMember < KeyLaneControl::kFamilyLaneCount;
         ++aMember) {
        sAssignments[(pFamilyIndex * KeyLaneControl::kFamilyLaneCount) +
                     aMember] = aFamilyAssignments[aMember];
    }
}

void AddPlanToState(
    const FamilyPlan &pPlan,
    std::array<std::uint16_t, kOccupancyCellCount> *pOccupancy,
    std::array<std::uint64_t, 8U> *pPhysicalDistances) {
    for (std::size_t aCandidate = 0U;
         aCandidate < KeyLaneControl::kActiveCandidateCount;
         ++aCandidate) {
        for (std::size_t aKey = 0U;
             aKey < KeyLaneControl::kKeyFunctionCount;
             ++aKey) {
            for (std::size_t aMember = 0U;
                 aMember < KeyLaneControl::kFamilyLaneCount;
                 ++aMember) {
                const std::size_t aSplit =
                    PlanSplit(pPlan, aMember, aKey, aCandidate);
                const std::size_t aIndex =
                    ((aCandidate * KeyLaneControl::kKeyFunctionCount +
                      aKey) * kSplitCount) + aSplit;
                ++(*pOccupancy)[aIndex];
            }
        }
    }

    const std::array<std::uint64_t, 8U> aAddedDistances =
        FamilyPhysicalDistances(pPlan);
    for (std::size_t i = 0U; i < aAddedDistances.size(); ++i) {
        (*pPhysicalDistances)[i] += aAddedDistances[i];
    }
}

void CommitPlan(
    const std::size_t pFamilyIndex,
    const FamilyPlan &pPlan,
    std::array<std::uint16_t, kOccupancyCellCount> *pOccupancy,
    std::array<std::uint64_t, 8U> *pPhysicalDistances) {
    WritePlanAssignments(pFamilyIndex, pPlan);
    AddPlanToState(pPlan, pOccupancy, pPhysicalDistances);
    sPlans.push_back(pPlan);
}

void BuildRefinementBase(
    const std::size_t pExcludedFamily,
    std::vector<FamilyPlan> *pOtherPlans,
    std::array<std::uint16_t, kOccupancyCellCount> *pOccupancy,
    std::array<std::uint64_t, 8U> *pPhysicalDistances,
    Score *pBaseScore) {
    pOtherPlans->clear();
    *pOccupancy = {};
    *pPhysicalDistances = {};
    *pBaseScore = {};

    for (std::size_t i = 0U; i < sPlans.size(); ++i) {
        if (i == pExcludedFamily) {
            continue;
        }
        pOtherPlans->push_back(sPlans[i]);
        AddPlanToState(sPlans[i], pOccupancy, pPhysicalDistances);
    }
    for (std::size_t i = 0U; i < pOtherPlans->size(); ++i) {
        for (std::size_t j = i + 1U; j < pOtherPlans->size(); ++j) {
            AddFamilyRelationship((*pOtherPlans)[i],
                                  (*pOtherPlans)[j],
                                  &pBaseScore->mWorstRelativeFrequency,
                                  &pBaseScore->mWorstExactOverlap,
                                  &pBaseScore->mRelativePenalty);
        }
    }
}

Score DirectScore(
    const std::array<Assignment,
                     KeyLaneControl::kAssignmentCount> &pAssignments) {
    Score aScore;
    std::array<std::uint16_t, kOccupancyCellCount> aOccupancy{};

    for (const Assignment &aAssignment : pAssignments) {
        for (std::size_t aCandidate = 0U;
             aCandidate < KeyLaneControl::kActiveCandidateCount;
             ++aCandidate) {
            for (std::size_t aKey = 0U;
                 aKey < KeyLaneControl::kKeyFunctionCount;
                 ++aKey) {
                const std::size_t aSplit =
                    AssignmentSplit(aAssignment, aKey, aCandidate);
                const std::size_t aIndex =
                    ((aCandidate * KeyLaneControl::kKeyFunctionCount +
                      aKey) * kSplitCount) + aSplit;
                ++aOccupancy[aIndex];
            }
        }
    }

    aScore.mMinimumOccupancy =
        std::numeric_limits<std::uint16_t>::max();
    for (const std::uint16_t aCount : aOccupancy) {
        aScore.mMinimumOccupancy = std::min(
            aScore.mMinimumOccupancy,
            aCount
        );
        aScore.mMaximumOccupancy = std::max(
            aScore.mMaximumOccupancy,
            aCount
        );
        aScore.mOccupancyPenalty += SquareSigned(
            (4 * static_cast<std::int64_t>(aCount)) -
            static_cast<std::int64_t>(KeyLaneControl::kFamilyCount)
        );
    }

    aScore.mMinimumCandidateDistance =
        std::numeric_limits<std::uint64_t>::max();
    for (std::size_t aLeftCandidate = 0U;
         aLeftCandidate < KeyLaneControl::kActiveCandidateCount;
         ++aLeftCandidate) {
        for (std::size_t aRightCandidate = aLeftCandidate + 1U;
             aRightCandidate < KeyLaneControl::kActiveCandidateCount;
             ++aRightCandidate) {
            std::uint64_t aDistance = 0ULL;
            for (const Assignment &aAssignment : pAssignments) {
                for (std::size_t aKey = 0U;
                     aKey < KeyLaneControl::kKeyFunctionCount;
                     ++aKey) {
                    const int aLeft = AssignmentSplit(
                        aAssignment, aKey, aLeftCandidate);
                    const int aRight = AssignmentSplit(
                        aAssignment, aKey, aRightCandidate);
                    aDistance += static_cast<std::uint64_t>(
                        aLeft > aRight ? aLeft - aRight : aRight - aLeft
                    );
                }
            }
            aScore.mMinimumCandidateDistance = std::min(
                aScore.mMinimumCandidateDistance,
                aDistance
            );
            aScore.mTotalCandidateDistance += aDistance;
        }
    }

    for (std::size_t aLeftFamily = 0U;
         aLeftFamily < KeyLaneControl::kFamilyCount;
         ++aLeftFamily) {
        for (std::size_t aRightFamily = aLeftFamily + 1U;
             aRightFamily < KeyLaneControl::kFamilyCount;
             ++aRightFamily) {
            for (std::size_t aLeftMember = 0U;
                 aLeftMember < KeyLaneControl::kFamilyLaneCount;
                 ++aLeftMember) {
                const Assignment &aLeft = pAssignments[
                    (aLeftFamily * KeyLaneControl::kFamilyLaneCount) +
                    aLeftMember
                ];
                for (std::size_t aRightMember = 0U;
                     aRightMember < KeyLaneControl::kFamilyLaneCount;
                     ++aRightMember) {
                    const Assignment &aRight = pAssignments[
                        (aRightFamily * KeyLaneControl::kFamilyLaneCount) +
                        aRightMember
                    ];
                    std::array<std::uint16_t, kSplitCount> aRelative{};
                    for (std::size_t aCandidate = 0U;
                         aCandidate < KeyLaneControl::kActiveCandidateCount;
                         ++aCandidate) {
                        for (std::size_t aKey = 0U;
                             aKey < KeyLaneControl::kKeyFunctionCount;
                             ++aKey) {
                            const std::size_t aLeftSplit =
                                AssignmentSplit(aLeft, aKey, aCandidate);
                            const std::size_t aRightSplit =
                                AssignmentSplit(aRight, aKey, aCandidate);
                            ++aRelative[
                                (aRightSplit + 16U - aLeftSplit) & 15U
                            ];
                        }
                    }
                    aScore.mWorstExactOverlap = std::max(
                        aScore.mWorstExactOverlap,
                        aRelative[0]
                    );
                    for (const std::uint16_t aCount : aRelative) {
                        aScore.mWorstRelativeFrequency = std::max(
                            aScore.mWorstRelativeFrequency,
                            aCount
                        );
                        aScore.mRelativePenalty += SquareSigned(
                            static_cast<std::int64_t>(aCount) - 16
                        );
                    }
                }
            }
        }
    }
    return aScore;
}

std::vector<std::uint64_t> AssignmentValues() {
    std::vector<std::uint64_t> aValues;
    aValues.reserve(KeyLaneControl::kAssignmentCount * 3U);
    for (const Assignment &aAssignment : sAssignments) {
        aValues.push_back(static_cast<std::uint64_t>(aAssignment.mLane));
        aValues.push_back(aAssignment.mKeyOrder);
        aValues.push_back(aAssignment.mSplitOrder);
    }
    return aValues;
}

std::string ScoreText(const Score &pScore,
                      const std::uint64_t pCases) {
    std::ostringstream aText;
    aText << "KeyLaneControl cases-per-family=" << pCases
          << " active-candidates="
          << KeyLaneControl::kActiveCandidateCount
          << " families=" << KeyLaneControl::kFamilyCount
          << " assignments=" << KeyLaneControl::kAssignmentCount
          << " relative={worst:" << pScore.mWorstRelativeFrequency
          << ", exact:" << pScore.mWorstExactOverlap
          << ", penalty:" << pScore.mRelativePenalty << "}"
          << " occupancy={" << pScore.mMinimumOccupancy
          << ".." << pScore.mMaximumOccupancy
          << ", penalty:" << pScore.mOccupancyPenalty << "}"
          << " candidate-distance={minimum:"
          << pScore.mMinimumCandidateDistance
          << ", total:" << pScore.mTotalCandidateDistance << "}";
    return aText.str();
}

std::string RenderAssignmentArray() {
    std::ostringstream aText;
    aText << "inline constexpr std::array<Assignment, "
          << KeyLaneControl::kAssignmentCount
          << "U> kAssignments = {{\n";
    for (std::size_t aIndex = 0U;
         aIndex < sAssignments.size();
         ++aIndex) {
        const Assignment &aAssignment = sAssignments[aIndex];
        const std::size_t aFamily =
            aIndex / KeyLaneControl::kFamilyLaneCount;
        const std::size_t aMember =
            aIndex % KeyLaneControl::kFamilyLaneCount;
        aText << "    { Slot::k" << kFamilies[aFamily].mStem
              << "Lane" << static_cast<char>('A' + aMember)
              << ", 0x"
              << std::uppercase << std::hex << std::setw(16)
              << std::setfill('0') << aAssignment.mKeyOrder
              << "ULL, 0x" << std::setw(16)
              << aAssignment.mSplitOrder << "ULL },\n"
              << std::dec;
    }
    aText << "}};";
    return aText.str();
}

} // namespace

void KeyLaneControl::Reset(const std::uint64_t pSeed) {
    sRandom.seed(pSeed == 0ULL ? 0x4B45594C414E4532ULL : pSeed);
    sAssignments = {};
    sPlans.clear();
    sScore = {};
    sDidReset = true;
    sHasValues = false;
}

std::string KeyLaneControl::Generate(
    const std::uint64_t pExplorationCases) {
    if (!sDidReset) {
        return "";
    }

    const std::uint64_t aCases =
        std::max<std::uint64_t>(1ULL, pExplorationCases);
    std::array<std::uint16_t, kOccupancyCellCount> aOccupancy{};
    std::array<std::uint64_t, 8U> aPhysicalDistances{};
    Score aCurrentScore{};

    for (std::size_t aFamilyIndex = 0U;
         aFamilyIndex < kFamilyCount;
         ++aFamilyIndex) {
        FamilyPlan aBestPlan{};
        Evaluation aBestEvaluation;
        aBestEvaluation.mScore.mWorstRelativeFrequency =
            std::numeric_limits<std::uint16_t>::max();
        bool aHasBest = false;

        for (std::uint64_t aCase = 0ULL; aCase < aCases; ++aCase) {
            const FamilyPlan aPlan = RandomPlan();
            const Evaluation aEvaluation = EvaluatePlan(
                aPlan,
                sPlans,
                aOccupancy,
                aPhysicalDistances,
                aCurrentScore
            );
            if (!aHasBest || Better(aEvaluation, aBestEvaluation)) {
                aBestPlan = aPlan;
                aBestEvaluation = aEvaluation;
                aHasBest = true;
            }
        }

        if (!aHasBest) {
            return "";
        }
        CommitPlan(aFamilyIndex,
                   aBestPlan,
                   &aOccupancy,
                   &aPhysicalDistances);
        aCurrentScore = aBestEvaluation.mScore;
        std::printf(
            "KeyLaneControl family %2zu/%zu %-11s "
            "relative=%u occupancy=%u..%u distance=%llu\n",
            aFamilyIndex + 1U,
            kFamilyCount,
            kFamilies[aFamilyIndex].mStem,
            static_cast<unsigned>(
                aCurrentScore.mWorstRelativeFrequency),
            static_cast<unsigned>(aCurrentScore.mMinimumOccupancy),
            static_cast<unsigned>(aCurrentScore.mMaximumOccupancy),
            static_cast<unsigned long long>(
                aCurrentScore.mMinimumCandidateDistance)
        );
    }

    // Revisit every coordinate after the complete table exists. This removes
    // the construction-order bias of a purely greedy family-by-family run.
    for (std::size_t aPass = 0U;
         aPass < kRefinementPassCount;
         ++aPass) {
        for (std::size_t aFamilyIndex = 0U;
             aFamilyIndex < kFamilyCount;
             ++aFamilyIndex) {
            std::vector<FamilyPlan> aOtherPlans;
            std::array<std::uint16_t,
                       kOccupancyCellCount> aBaseOccupancy{};
            std::array<std::uint64_t, 8U> aBasePhysical{};
            Score aBaseScore{};
            BuildRefinementBase(aFamilyIndex,
                                &aOtherPlans,
                                &aBaseOccupancy,
                                &aBasePhysical,
                                &aBaseScore);

            FamilyPlan aBestPlan = sPlans[aFamilyIndex];
            Evaluation aBestEvaluation = EvaluatePlan(
                aBestPlan,
                aOtherPlans,
                aBaseOccupancy,
                aBasePhysical,
                aBaseScore
            );
            for (std::uint64_t aCase = 0ULL;
                 aCase < aCases;
                 ++aCase) {
                const FamilyPlan aPlan = RandomPlan();
                const Evaluation aEvaluation = EvaluatePlan(
                    aPlan,
                    aOtherPlans,
                    aBaseOccupancy,
                    aBasePhysical,
                    aBaseScore
                );
                if (Better(aEvaluation, aBestEvaluation)) {
                    aBestPlan = aPlan;
                    aBestEvaluation = aEvaluation;
                }
            }
            sPlans[aFamilyIndex] = aBestPlan;
            WritePlanAssignments(aFamilyIndex, aBestPlan);
        }

        const Score aPassScore = DirectScore(sAssignments);
        std::printf(
            "KeyLaneControl refinement %zu/%zu "
            "relative=%u occupancy=%u..%u distance=%llu\n",
            aPass + 1U,
            kRefinementPassCount,
            static_cast<unsigned>(aPassScore.mWorstRelativeFrequency),
            static_cast<unsigned>(aPassScore.mMinimumOccupancy),
            static_cast<unsigned>(aPassScore.mMaximumOccupancy),
            static_cast<unsigned long long>(
                aPassScore.mMinimumCandidateDistance)
        );
    }

    sScore = DirectScore(sAssignments);
    (void)aCurrentScore;
    std::string aError;
    sHasValues = true;
    if (!Validate(&aError)) {
        std::printf("KeyLaneControl generated invalid values: %s\n",
                    aError.c_str());
        sHasValues = false;
        return "";
    }
    return ScoreText(sScore, aCases);
}

bool KeyLaneControl::SaveValues(
    const std::string &pFolder,
    std::string *pErrorMessage) {
    if (!sHasValues || !Validate(pErrorMessage)) {
        return false;
    }
    return ControlValueFile::Save(
        FileIO::Join(FileIO::ProjectRoot(pFolder),
                     "KeyLaneAssignments.bin"),
        ControlValueFile::Kind::kKeyLane,
        AssignmentValues(),
        pErrorMessage
    );
}

bool KeyLaneControl::LoadValues(
    const std::string &pFolder,
    std::string *pErrorMessage) {
    if (!sDidReset || sHasValues) {
        SetError(pErrorMessage,
                 "KeyLaneControl::Reset must precede value loading");
        return false;
    }
    std::vector<std::uint64_t> aValues;
    if (!ControlValueFile::Load(
            FileIO::Join(FileIO::ProjectRoot(pFolder),
                         "KeyLaneAssignments.bin"),
            ControlValueFile::Kind::kKeyLane,
            kAssignmentCount * 3U,
            &aValues,
            pErrorMessage)) {
        return false;
    }
    for (std::size_t i = 0U; i < kAssignmentCount; ++i) {
        sAssignments[i] = {
            static_cast<Slot>(aValues[(i * 3U) + 0U]),
            aValues[(i * 3U) + 1U],
            aValues[(i * 3U) + 2U],
        };
    }
    sScore = DirectScore(sAssignments);
    sHasValues = true;
    if (!Validate(pErrorMessage)) {
        sHasValues = false;
        return false;
    }
    SetError(pErrorMessage, "");
    return true;
}

bool KeyLaneControl::WriteAssignmentsHeader(
    const std::string &pHeaderPath,
    std::string *pErrorMessage) {
    if (!sHasValues || !Validate(pErrorMessage)) {
        return false;
    }
    const std::string aPath = FileIO::ProjectRoot(pHeaderPath);
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(aPath, aBytes)) {
        SetError(pErrorMessage,
                 "KeyLaneControl could not load header " + aPath);
        return false;
    }
    const std::string aCurrent(aBytes.begin(), aBytes.end());
    const std::string aMarker =
        "inline constexpr std::array<Assignment,";
    const std::size_t aStart = aCurrent.find(aMarker);
    const std::size_t aEndMarker =
        aStart == std::string::npos
            ? std::string::npos
            : aCurrent.find("}};", aStart);
    if ((aStart == std::string::npos) ||
        (aEndMarker == std::string::npos)) {
        SetError(pErrorMessage,
                 "KeyLaneControl could not find the assignment array in " +
                     aPath);
        return false;
    }

    std::string aUpdated = aCurrent.substr(0U, aStart);
    aUpdated += RenderAssignmentArray();
    aUpdated += aCurrent.substr(aEndMarker + 3U);

    const std::string aTemporaryPath = aPath + ".tmp";
    const std::vector<std::uint8_t> aUpdatedBytes(
        aUpdated.begin(), aUpdated.end());
    if (!FileIO::Save(aTemporaryPath, aUpdatedBytes) ||
        (std::rename(aTemporaryPath.c_str(), aPath.c_str()) != 0)) {
        std::remove(aTemporaryPath.c_str());
        SetError(pErrorMessage,
                 "KeyLaneControl could not atomically replace " + aPath);
        return false;
    }
    SetError(pErrorMessage, "");
    return true;
}

bool KeyLaneControl::Validate(std::string *pErrorMessage) {
    if (!sHasValues) {
        SetError(pErrorMessage, "KeyLaneControl has no values");
        return false;
    }

    for (std::size_t aIndex = 0U;
         aIndex < kAssignmentCount;
         ++aIndex) {
        const std::size_t aFamily = aIndex / kFamilyLaneCount;
        const std::size_t aMember = aIndex % kFamilyLaneCount;
        const Assignment &aAssignment = sAssignments[aIndex];
        if (aAssignment.mLane != kFamilies[aFamily].mLanes[aMember]) {
            SetError(pErrorMessage,
                     "KeyLaneControl lane order did not match its family");
            return false;
        }
        if (!IsPermutation(aAssignment.mKeyOrder) ||
            !IsPermutation(aAssignment.mSplitOrder)) {
            SetError(pErrorMessage,
                     "KeyLaneControl assignment was not two permutations");
            return false;
        }
        for (std::size_t aCandidate = 0U;
             aCandidate < kActiveCandidateCount;
             ++aCandidate) {
            std::uint16_t aSeen = 0U;
            for (std::size_t aKey = 0U;
                 aKey < kKeyFunctionCount;
                 ++aKey) {
                aSeen = static_cast<std::uint16_t>(
                    aSeen |
                    (1U << AssignmentSplit(
                        aAssignment, aKey, aCandidate))
                );
            }
            if (aSeen != 0xFFFFU) {
                SetError(pErrorMessage,
                         "A key-lane assignment did not use every split");
                return false;
            }
        }
    }

    for (std::size_t aFamily = 0U;
         aFamily < kFamilyCount;
         ++aFamily) {
        for (std::size_t aCandidate = 0U;
             aCandidate < kActiveCandidateCount;
             ++aCandidate) {
            for (std::size_t aKey = 0U;
                 aKey < kKeyFunctionCount;
                 ++aKey) {
                std::uint16_t aSeen = 0U;
                for (std::size_t aMember = 0U;
                     aMember < kFamilyLaneCount;
                     ++aMember) {
                    const Assignment &aAssignment = sAssignments[
                        (aFamily * kFamilyLaneCount) + aMember
                    ];
                    const std::uint16_t aBit =
                        static_cast<std::uint16_t>(
                            1U << AssignmentSplit(
                                aAssignment, aKey, aCandidate)
                        );
                    if ((aSeen & aBit) != 0U) {
                        SetError(pErrorMessage,
                                 "A lane family reused a split");
                        return false;
                    }
                    aSeen = static_cast<std::uint16_t>(aSeen | aBit);
                }
            }
        }
    }

    for (std::size_t aLeft = 0U;
         aLeft < kAssignmentCount;
         ++aLeft) {
        for (std::size_t aRight = aLeft + 1U;
             aRight < kAssignmentCount;
             ++aRight) {
            bool aIdentical = true;
            for (std::size_t aCandidate = 0U;
                 aCandidate < kActiveCandidateCount && aIdentical;
                 ++aCandidate) {
                for (std::size_t aKey = 0U;
                     aKey < kKeyFunctionCount;
                     ++aKey) {
                    if (AssignmentSplit(sAssignments[aLeft],
                                        aKey,
                                        aCandidate) !=
                        AssignmentSplit(sAssignments[aRight],
                                        aKey,
                                        aCandidate)) {
                        aIdentical = false;
                        break;
                    }
                }
            }
            if (aIdentical) {
                SetError(pErrorMessage,
                         "Two key lanes had identical assignment schedules");
                return false;
            }
        }
    }

    // This is the maximum possible Hamming separation: for every lane/key
    // coordinate, all sixteen active expanders select different splits.
    for (const Assignment &aAssignment : sAssignments) {
        for (std::size_t aKey = 0U;
             aKey < kKeyFunctionCount;
             ++aKey) {
            std::uint16_t aSeen = 0U;
            for (std::size_t aCandidate = 0U;
                 aCandidate < kActiveCandidateCount;
                 ++aCandidate) {
                const std::uint16_t aBit =
                    static_cast<std::uint16_t>(
                        1U << AssignmentSplit(
                            aAssignment, aKey, aCandidate)
                    );
                if ((aSeen & aBit) != 0U) {
                    SetError(pErrorMessage,
                             "Active expanders reused a key-lane split");
                    return false;
                }
                aSeen = static_cast<std::uint16_t>(aSeen | aBit);
            }
        }
    }

    SetError(pErrorMessage, "");
    return true;
}

const KeyLaneControl::Assignment *KeyLaneControl::AssignmentAt(
    const std::size_t pIndex) {
    return sHasValues && (pIndex < sAssignments.size())
        ? &sAssignments[pIndex]
        : nullptr;
}

const KeyLaneControl::Score *KeyLaneControl::CurrentScore() {
    return sHasValues ? &sScore : nullptr;
}

bool KeyLaneControl::HasValues() {
    return sHasValues;
}
