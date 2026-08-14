//
//  LoopWeights.hpp
//  MeanMachine
//

#ifndef LoopWeights_hpp
#define LoopWeights_hpp

#include <array>
#include <cstddef>

// Estimated importance weights for the 50 values returned by
// RankingDisplayValues(). The entries intentionally follow the display/CSV
// order, not the legacy binary order returned by ScoreValues().
//
// The raw weights are intentionally not percentages. A candidate's final
// score is normalized by WeightTotal() into [0, 100]:
//
//     raw = sum(weight * direction-adjusted percent)
//     score = 100 * raw / WeightTotal()
//
// LoopScorer combines these weights with its fixed shared ranges. One score
// therefore means the same thing for every heart. Hard
// validity and gold-stat gates should be applied before this score; a strong
// weighted result must not buy its way past a required structural property.
class LoopWeights {
public:
    static constexpr std::size_t kMetricCount = 50U;

    struct MetricWeight {
        const char *mName;
        bool mHigherIsBetter;
        unsigned int mWeight;
    };

    // The four dominant measurements use 40, 36, 32, and 32. The next
    // strongest measurement is 12, which leaves an intentional gap between
    // primary failure modes and supporting evidence. Every participating
    // secondary measurement still has a weight in [2, 12].
    //
    // A zero is also a computation mask for weighted searches: the metric is
    // invariant, retired, excessively coarse, or substantially duplicates a
    // stronger weighted measurement.
    static constexpr std::array<MetricWeight, kMetricCount> kMetrics = {{
        // Basic pair quality and first-iteration influence.
        {"first_minimum_wanderer_influence", true,   4U},
        {"first_minimum_input_coverage", true,       0U}, // Same signal as the preceding metric.
        {"second_minimum_wanderer_influence", true,  0U}, // Observed invariant.
        {"second_minimum_input_coverage", true,      0U}, // Observed invariant.
        {"minimum_pair_union", true,                 4U},
        {"minimum_heart_separation", true,           2U},
        {"total_heart_separation", true,             0U}, // Heart-heavy restatement of separation.
        {"minimum_pair_balance", true,               0U}, // Nearly constant and weakly discriminating.
        {"minimum_complement", true,                 3U},
        {"dominated_pair_count", false,              4U},
        {"flow_area", true,                          6U},

        // Invariants and graph-spread measurements.
        {"arrival_total", false,                     0U}, // Observed invariant.
        {"maximum_arrival_skew", false,              0U}, // Observed invariant.
        {"directed_diameter", false,                 0U}, // Coarse form of the path distribution.
        {"mean_wanderer_shortest_path_x1000", false, 2U}, // Small global companion to the worst-source measurement.
        {"worst_wanderer_mean_shortest_path_x1000", false, 5U},
        {"minimum_influenced_wanderers", true,       0U}, // Observed invariant.
        {"minimum_wanderers_reached_within_four_edges", true, 7U},
        {"mean_four_edge_wanderer_reach_x1000", true, 0U}, // Correlates with mean shortest path.
        {"redundant_early_branch_fraction_x1000", true, 5U},
        {"pair_component_count", false,              4U},
        {"minimum_subset_expansion", true,          10U},
        {"total_subset_expansion", true,             0U}, // Minimum expansion protects the bottleneck.
        {"reserved_legacy_spectral_gap", true,       0U}, // Retired; serialized as zero.
        {"minimum_one_round_wanderer_fanout", true,  0U}, // Coarse and usually tied at its ceiling.
        {"mean_one_round_wanderer_fanout_x1000", true, 0U}, // Near-duplicate of the minimum.
        {"minimum_source_orbiter_journey_area", true, 12U},

        // Remaining graph-spread, primary, and ordered-journey metrics.
        {"minimum_dual_tail_wanderer_reach", true,   32U},
        {"mean_dual_tail_wanderer_reach_x1000", true, 0U}, // Minimum protects the weakest source.
        {"maximum_orbiter_shortest_path_load_x1000", false, 6U},
        {"maximum_ordered_source_orphan_area", false, 32U},
        {"mean_ordered_source_orphan_area_x1000", false, 0U}, // Maximum protects the weakest source.
        {"maximum_last_orphan_latency", false,       0U}, // Strongly restates one-round fanout.
        {"maximum_orphan_straggler_gap", false,      4U},
        {"maximum_midpoint_source_orphans", false,   2U},
        {"maximum_midpoint_destination_orphan_load", false, 4U},
        {"maximum_midpoint_co_orphan_load", false,   4U},
        {"maximum_source_meeting_orphans", false,    0U}, // Observed invariant.
        {"maximum_source_meeting_area", false,       2U},
        {"mean_source_pair_meeting_latency_x1000", false, 2U},
        {"maximum_robust_orphans", false,            8U},
        {"mean_robust_orphans_x1000", false,         0U}, // Duplicates removal-damage behavior.
        {"maximum_ordered_destination_orphan_area", false, 6U},
        {"maximum_dual_tail_source_orphan_area", false, 8U},
        {"mean_dual_tail_source_orphan_area_x1000", false, 0U}, // Duplicates dual-tail reach.
        {"maximum_robust_destination_orphans", false, 6U},

        // Primary failure modes. These dominate, but they do not erase the
        // supporting measurements above.
        {"maximum_single_orbiter_ordered_pair_damage", false, 40U},
        {"mean_single_orbiter_ordered_pair_damage_x1000", false, 0U}, // Maximum is more protective.
        {"minimum_surviving_fanout_after_one_orbiter_removal", true, 36U},
        {"maximum_dual_tail_arrival_skew", false,     0U}, // Nearly invariant in observed populations.
    }};

    static constexpr unsigned int WeightTotal() {
        unsigned int aTotal = 0U;
        for (const MetricWeight &aMetric : kMetrics) {
            aTotal += aMetric.mWeight;
        }
        return aTotal;
    }

    static constexpr bool IsEnabled(const std::size_t pMetric) {
        return kMetrics[pMetric].mWeight != 0U;
    }

    static constexpr bool HasValidWeightRange() {
        for (const MetricWeight &aMetric : kMetrics) {
            if ((aMetric.mWeight != 0U) &&
                ((aMetric.mWeight < 2U) ||
                 (aMetric.mWeight > 40U))) {
                return false;
            }
        }
        return true;
    }

    // Converts one raw measurement to [0, 1]. Lower-is-better metrics are
    // reversed. A metric with no observed range is neutral rather than best
    // or worst; normally such a metric should also have zero weight.
    static constexpr double Percent(const int pValue,
                                    const int pMinimum,
                                    const int pMaximum,
                                    const bool pHigherIsBetter) {
        if (pMinimum >= pMaximum) {
            return 0.5;
        }

        const int aClampedValue = pValue < pMinimum
            ? pMinimum
            : (pValue > pMaximum ? pMaximum : pValue);
        const double aPercent =
            static_cast<double>(aClampedValue - pMinimum) /
            static_cast<double>(pMaximum - pMinimum);
        return pHigherIsBetter ? aPercent : (1.0 - aPercent);
    }

    template <typename MetricContainer>
    static constexpr double Score(
        const MetricContainer &pValues,
        const MetricContainer &pMinimums,
        const MetricContainer &pMaximums) {
        double aScore = 0.0;
        for (std::size_t i = 0U; i < kMetrics.size(); ++i) {
            const MetricWeight &aMetric = kMetrics[i];
            if (aMetric.mWeight == 0U) {
                continue;
            }
            aScore += static_cast<double>(aMetric.mWeight) * Percent(
                pValues[i], pMinimums[i], pMaximums[i],
                aMetric.mHigherIsBetter);
        }
        return aScore;
    }
};

static_assert(LoopWeights::WeightTotal() == 260U,
              "Unexpected loop metric weight total");
static_assert(LoopWeights::HasValidWeightRange(),
              "Active loop metric weights must be in [2, 40]");

#endif /* LoopWeights_hpp */
