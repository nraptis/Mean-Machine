//
//  LoopHeadTailDifference.hpp
//  MeanMachine
//

#ifndef LoopHeadTailDifference_hpp
#define LoopHeadTailDifference_hpp

#include "LoopHeadFarmer.hpp"
#include "LoopNewFarmer.hpp"

#include <cstddef>

class LoopHeadTailDifference {
public:
    struct Measures {
        std::size_t mHead = 0U;
        std::size_t mTailPartial = 0U;
        std::size_t mTailFull = 0U;
    };

    // Head: one point when an orbiter is assigned a different wanderer.
    //
    // Tail, per destination wanderer:
    //     full match:    both unordered-pair orbiters match
    //     partial match: at least one unordered-pair orbiter matches
    //
    // The differences are the inverse, nested measurements:
    //     full difference:    the unordered pairs are not identical
    //     partial difference: the unordered pairs are disjoint
    //
    // Therefore every partial difference is also a full difference. An exact
    // unordered-pair match contributes to neither difference.
    static constexpr Measures Measure(
        const LoopHeadPattern11 &pHeadA,
        const LoopTailPattern11 &pTailA,
        const LoopHeadPattern11 &pHeadB,
        const LoopTailPattern11 &pTailB) {
        Measures aMeasures;
        for (std::size_t i = 0U;
             i < LoopHeadFarmer::kRoleCount;
             ++i) {
            aMeasures.mHead += pHeadA.mWandererForOrbiter[i] !=
                pHeadB.mWandererForOrbiter[i];

            const std::uint8_t aOrbiterA =
                pTailA.mOrbiterAForWanderer[i];
            const std::uint8_t aOrbiterB =
                pTailA.mOrbiterBForWanderer[i];
            const std::uint8_t bOrbiterA =
                pTailB.mOrbiterAForWanderer[i];
            const std::uint8_t bOrbiterB =
                pTailB.mOrbiterBForWanderer[i];
            const std::size_t aSharedCount =
                static_cast<std::size_t>(
                    (aOrbiterA == bOrbiterA) ||
                    (aOrbiterA == bOrbiterB)) +
                static_cast<std::size_t>(
                    (aOrbiterB == bOrbiterA) ||
                    (aOrbiterB == bOrbiterB));
            aMeasures.mTailPartial += aSharedCount == 0U;
            aMeasures.mTailFull += aSharedCount < 2U;
        }
        return aMeasures;
    }

    static constexpr bool Passes(
        const LoopHeadPattern11 &pHeadA,
        const LoopTailPattern11 &pTailA,
        const LoopHeadPattern11 &pHeadB,
        const LoopTailPattern11 &pTailB,
        const std::size_t pMinimumHead,
        const std::size_t pMinimumTailPartial,
        const std::size_t pMinimumTailFull) {
        const Measures aMeasures = Measure(
            pHeadA, pTailA, pHeadB, pTailB);
        return (aMeasures.mHead >= pMinimumHead) &&
               (aMeasures.mTailPartial >= pMinimumTailPartial) &&
               (aMeasures.mTailFull >= pMinimumTailFull);
    }
};

#endif /* LoopHeadTailDifference_hpp */
