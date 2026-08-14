//
//  LoopFinalFarmThreholds.hpp
//  MeanMachine
//

#ifndef LoopFinalFarmThreholds_hpp
#define LoopFinalFarmThreholds_hpp

#include <array>
#include <cstddef>

class LoopFinalFarmThreholds {
public:
    struct HeartThreshold {
        std::size_t mSourceHeartIndex;
        int mMinimumIntegerScore;
    };

    static constexpr std::array<HeartThreshold, 14U> kHeartThresholds = {{
        {  0U, 168 },
        {  1U, 168 },
        {  2U, 176 },
        {  3U, 176 },
        {  6U, 170 },
        {  9U, 168 },
        { 17U, 170 },
        { 20U, 168 },
        { 21U, 170 },
        { 22U, 170 },
        { 29U, 170 },
        { 36U, 168 },
        { 37U, 170 },
        { 58U, 168 },
    }};

    static constexpr std::size_t kMinimumHeadDifference = 3U;
    static constexpr std::size_t kMinimumTailDifferencePartial = 1U;
    static constexpr std::size_t kMinimumTailDifferenceFull = 7U;

    static constexpr int MinimumIntegerScoreForNexus(
        const std::size_t pNexusIndex) {
        return pNexusIndex < kHeartThresholds.size()
            ? kHeartThresholds[pNexusIndex].mMinimumIntegerScore
            : 0;
    }

    static constexpr bool PassesIntegerScore(
        const std::size_t pSourceHeartIndex,
        const int pIntegerScore) {
        for (const HeartThreshold &aHeart : kHeartThresholds) {
            if (aHeart.mSourceHeartIndex == pSourceHeartIndex) {
                return pIntegerScore >= aHeart.mMinimumIntegerScore;
            }
        }
        return false;
    }

    static constexpr bool HeartIndicesAreStrictlyIncreasing() {
        for (std::size_t i = 1U; i < kHeartThresholds.size(); ++i) {
            if (kHeartThresholds[i - 1U].mSourceHeartIndex >=
                kHeartThresholds[i].mSourceHeartIndex) {
                return false;
            }
        }
        return true;
    }
};

static_assert(LoopFinalFarmThreholds::HeartIndicesAreStrictlyIncreasing());

#endif /* LoopFinalFarmThreholds_hpp */
