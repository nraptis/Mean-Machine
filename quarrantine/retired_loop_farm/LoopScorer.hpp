//
//  LoopScorer.hpp
//  MeanMachine
//

#ifndef LoopScorer_hpp
#define LoopScorer_hpp

#include <array>
#include <cstddef>

class LoopScorer {
public:
    static constexpr std::size_t kMetricCount = 50U;
    static constexpr int kMaximumScore = 260;

    struct Measure {
        int mMinimum;
        int mMaximum;
        bool mHigherIsBetter;
        float mWeight;
    };

    // The limits are fixed from LoopExtremeMeasures as:
    //
    //     minimum = floor(exact minimum * 0.9)
    //     maximum = ceil(exact maximum * 1.25)
    //
    // A zero weight disables that metric.
    static constexpr std::array<Measure, kMetricCount> kMeasures = {{
        {    9,    19, true,   4.0F}, //  0: first_minimum_wanderer_influence
        {    0,     0, true,   0.0F}, //  1: first_minimum_input_coverage
        {    0,     0, true,   0.0F}, //  2: second_minimum_wanderer_influence
        {    0,     0, true,   0.0F}, //  3: second_minimum_input_coverage
        {    9,    19, true,   4.0F}, //  4: minimum_pair_union
        {    1,     4, true,   2.0F}, //  5: minimum_heart_separation
        {    0,     0, true,   0.0F}, //  6: total_heart_separation
        {    0,     0, true,   0.0F}, //  7: minimum_pair_balance
        {    0,     4, true,   3.0F}, //  8: minimum_complement
        {    3,    14, false,  4.0F}, //  9: dominated_pair_count
        { 5356,  7850, true,   6.0F}, // 10: flow_area
        {    0,     0, false,  0.0F}, // 11: arrival_total
        {    0,     0, false,  0.0F}, // 12: maximum_arrival_skew
        {    0,     0, false,  0.0F}, // 13: directed_diameter
        { 2888,  4602, false,  2.0F}, // 14: mean_wanderer_shortest_path_x1000
        { 2970,  5250, false,  5.0F}, // 15: worst_wanderer_mean_shortest_path_x1000
        {    0,     0, true,   0.0F}, // 16: minimum_influenced_wanderers
        {    4,    13, true,   7.0F}, // 17: minimum_wanderers_reached_within_four_edges
        {    0,     0, true,   0.0F}, // 18: mean_four_edge_wanderer_reach_x1000
        {  286,   863, true,   5.0F}, // 19: redundant_early_branch_fraction_x1000
        {    0,     4, false,  4.0F}, // 20: pair_component_count
        {   91,   512, true,  10.0F}, // 21: minimum_subset_expansion
        {    0,     0, true,   0.0F}, // 22: total_subset_expansion
        {    0,     0, true,   0.0F}, // 23: reserved_legacy_spectral_gap
        {    0,     0, true,   0.0F}, // 24: minimum_one_round_wanderer_fanout
        {    0,     0, true,   0.0F}, // 25: mean_one_round_wanderer_fanout_x1000
        {   23,    47, true,  12.0F}, // 26: minimum_source_orbiter_journey_area
        {    1,     9, true,  32.0F}, // 27: minimum_dual_tail_wanderer_reach
        {    0,     0, true,   0.0F}, // 28: mean_dual_tail_wanderer_reach_x1000
        {  175,   388, false,  6.0F}, // 29: maximum_orbiter_shortest_path_load_x1000
        {   55,   110, false, 32.0F}, // 30: maximum_ordered_source_orphan_area
        {    0,     0, false,  0.0F}, // 31: mean_ordered_source_orphan_area_x1000
        {    0,     0, false,  0.0F}, // 32: maximum_last_orphan_latency
        {    0,     9, false,  4.0F}, // 33: maximum_orphan_straggler_gap
        {    7,    12, false,  2.0F}, // 34: maximum_midpoint_source_orphans
        {    3,    12, false,  4.0F}, // 35: maximum_midpoint_destination_orphan_load
        {    2,    10, false,  4.0F}, // 36: maximum_midpoint_co_orphan_load
        {    0,     0, false,  0.0F}, // 37: maximum_source_meeting_orphans
        {  102,   173, false,  2.0F}, // 38: maximum_source_meeting_area
        { 8018, 14000, false,  2.0F}, // 39: mean_source_pair_meeting_latency_x1000
        {    5,    12, false,  8.0F}, // 40: maximum_robust_orphans
        {    0,     0, false,  0.0F}, // 41: mean_robust_orphans_x1000
        {   42,    95, false,  6.0F}, // 42: maximum_ordered_destination_orphan_area
        {   91,   148, false,  8.0F}, // 43: maximum_dual_tail_source_orphan_area
        {    0,     0, false,  0.0F}, // 44: mean_dual_tail_source_orphan_area_x1000
        {    4,    12, false,  6.0F}, // 45: maximum_robust_destination_orphans
        {    8,    34, false, 40.0F}, // 46: maximum_single_orbiter_ordered_pair_damage
        {    0,     0, false,  0.0F}, // 47: mean_single_orbiter_ordered_pair_damage_x1000
        {    2,     5, true,  36.0F}, // 48: minimum_surviving_fanout_after_one_orbiter_removal
        {    0,     0, false,  0.0F}, // 49: maximum_dual_tail_arrival_skew
    }};

    static int Score(const std::array<int, kMetricCount> &pValues);
};

#endif /* LoopScorer_hpp */
