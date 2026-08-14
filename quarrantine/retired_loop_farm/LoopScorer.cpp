//
//  LoopScorer.cpp
//  MeanMachine
//

#include "LoopScorer.hpp"

int LoopScorer::Score(
    const std::array<int, kMetricCount> &pValues) {
    int aScore = 0;

    for (std::size_t i = 0U; i < kMeasures.size(); ++i) {
        const Measure &aMeasure = kMeasures[i];
        if (aMeasure.mWeight == 0.0F) {
            continue;
        }

        const int aValue = pValues[i] < aMeasure.mMinimum
            ? aMeasure.mMinimum
            : (pValues[i] > aMeasure.mMaximum
                   ? aMeasure.mMaximum
                   : pValues[i]);

        float aPercent = 0.5F;
        if (aMeasure.mMinimum < aMeasure.mMaximum) {
            aPercent = static_cast<float>(
                aValue - aMeasure.mMinimum) /
                static_cast<float>(
                    aMeasure.mMaximum - aMeasure.mMinimum);
            if (!aMeasure.mHigherIsBetter) {
                aPercent = 1.0F - aPercent;
            }
        }

        const float aWeightF = aMeasure.mWeight;
        const int aFinal = static_cast<int>(
            (aPercent * aWeightF) + 0.5F);
        aScore += aFinal;
    }

    return aScore;
}
