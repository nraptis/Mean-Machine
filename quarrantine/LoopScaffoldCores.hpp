//
//  LoopScaffoldCores.hpp
//  MeanMachine
//

#ifndef LoopScaffoldCores_hpp
#define LoopScaffoldCores_hpp

#include <array>
#include <cstddef>
#include <cstdint>

namespace LoopScaffoldCores {

constexpr std::size_t kRoleCount = 11U;
constexpr std::size_t kCoreCount = 6U;

struct CoreRound {
    std::uint8_t mLead = 0U;
    std::uint8_t mSource = 0U;
    std::uint8_t mFeedback = 0U;
};

// Each triplet emits one ordered heart unit:
//
//     lead = lead ARX source;
//     feedback = feedback ARX updated-lead;
//     feedback = rotate/finalize(feedback);
//
// A role permutation changes the concrete labels without changing this
// ordered topology.
inline constexpr std::array<
    std::array<CoreRound, kRoleCount>,
    kCoreCount> kCores = {{
    {{
        {0U, 2U, 3U}, {1U, 4U, 6U}, {5U, 8U, 0U},
        {7U, 9U, 1U}, {10U, 3U, 5U}, {2U, 6U, 7U},
        {4U, 0U, 10U}, {8U, 1U, 2U}, {9U, 5U, 4U},
        {3U, 7U, 8U}, {6U, 10U, 9U},
    }},
    {{
        {6U, 4U, 0U}, {8U, 10U, 4U}, {7U, 5U, 10U},
        {2U, 9U, 5U}, {1U, 6U, 9U}, {3U, 8U, 6U},
        {0U, 7U, 8U}, {4U, 2U, 7U}, {10U, 1U, 2U},
        {5U, 3U, 1U}, {9U, 0U, 3U},
    }},
    {{
        {9U, 7U, 6U}, {4U, 2U, 1U}, {10U, 8U, 7U},
        {5U, 3U, 2U}, {0U, 9U, 8U}, {6U, 4U, 3U},
        {1U, 10U, 9U}, {7U, 5U, 4U}, {2U, 0U, 10U},
        {8U, 6U, 5U}, {3U, 1U, 0U},
    }},
    {{
        {5U, 10U, 9U}, {10U, 4U, 3U}, {4U, 9U, 8U},
        {9U, 3U, 2U}, {3U, 8U, 7U}, {8U, 2U, 1U},
        {2U, 7U, 6U}, {7U, 1U, 0U}, {1U, 6U, 5U},
        {6U, 0U, 10U}, {0U, 5U, 4U},
    }},
    {{
        {3U, 0U, 1U}, {9U, 6U, 7U}, {4U, 1U, 2U},
        {10U, 7U, 8U}, {5U, 2U, 3U}, {0U, 8U, 9U},
        {6U, 3U, 4U}, {1U, 9U, 10U}, {7U, 4U, 5U},
        {2U, 10U, 0U}, {8U, 5U, 6U},
    }},
    {{
        {7U, 2U, 3U}, {2U, 8U, 9U}, {8U, 3U, 4U},
        {3U, 9U, 10U}, {9U, 4U, 5U}, {4U, 10U, 0U},
        {10U, 5U, 6U}, {5U, 0U, 1U}, {0U, 6U, 7U},
        {6U, 1U, 2U}, {1U, 7U, 8U},
    }},
}};

} // namespace LoopScaffoldCores

#endif /* LoopScaffoldCores_hpp */
