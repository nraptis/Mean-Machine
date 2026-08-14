//
//  LoopNexusHearts.hpp
//  MeanMachine
//

#ifndef LoopNexusHearts_hpp
#define LoopNexusHearts_hpp

#include "LoopPatterns.hpp"

#include <array>
#include <cstddef>

class LoopNexusHearts {
public:
    static constexpr std::size_t kHeartCount = 14U;

    inline static constexpr LoopCorePattern11 mNexus00 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  2U,  7U }}, {{  8U,  9U, 10U }},
            {{  5U,  7U,  0U }}, {{  1U,  6U,  4U }},
            {{ 10U,  0U,  3U }}, {{  2U,  5U,  9U }},
            {{  7U,  3U,  8U }}, {{  9U, 10U,  1U }},
            {{  4U,  8U,  6U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 8U, 8U, 41U, 28U, 112U, 603U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus01 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  2U,  7U }}, {{  8U,  3U,  9U }},
            {{  5U,  7U, 10U }}, {{  4U,  0U,  1U }},
            {{  9U, 10U,  6U }}, {{  2U,  5U,  3U }},
            {{  1U,  6U,  8U }}, {{  7U,  9U,  0U }},
            {{ 10U,  8U,  4U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 8U, 8U, 31U, 28U, 112U, 604U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus02 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  2U,  7U }}, {{  8U,  9U,  1U }},
            {{ 10U,  5U,  4U }}, {{  7U,  8U,  0U }},
            {{  2U, 10U,  3U }}, {{  4U,  0U,  6U }},
            {{  1U,  7U,  9U }}, {{  5U,  6U,  8U }},
            {{  9U,  3U, 10U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 7U, 8U, 33U, 36U, 101U, 531U, 5U },
    };

    inline static constexpr LoopCorePattern11 mNexus03 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  2U,  7U }}, {{  8U,  9U,  1U }},
            {{ 10U,  5U,  4U }}, {{  7U,  8U,  0U }},
            {{  2U, 10U,  3U }}, {{  4U,  0U,  6U }},
            {{  1U,  3U,  9U }}, {{  5U,  6U,  8U }},
            {{  9U,  7U, 10U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 7U, 8U, 37U, 31U, 103U, 541U, 5U },
    };

    inline static constexpr LoopCorePattern11 mNexus04 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  2U,  7U }}, {{  8U,  9U, 10U }},
            {{  5U,  6U,  1U }}, {{ 10U,  7U,  0U }},
            {{  1U,  3U,  4U }}, {{  2U,  5U,  9U }},
            {{  4U,  0U,  8U }}, {{  9U, 10U,  6U }},
            {{  7U,  8U,  3U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 7U, 8U, 30U, 29U, 103U, 555U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus05 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  2U,  7U }}, {{  8U,  9U,  1U }},
            {{ 10U,  5U,  4U }}, {{  7U,  8U,  0U }},
            {{  2U, 10U,  3U }}, {{  5U,  0U,  6U }},
            {{  1U,  3U,  9U }}, {{  4U,  6U,  8U }},
            {{  9U,  7U, 10U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 7U, 7U, 37U, 31U, 101U, 535U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus06 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  0U,  7U }}, {{  8U,  5U,  9U }},
            {{ 10U,  2U,  3U }}, {{  7U,  9U,  1U }},
            {{  4U,  8U,  0U }}, {{  1U,  3U,  6U }},
            {{  5U,  7U, 10U }}, {{  2U,  6U,  8U }},
            {{  9U, 10U,  4U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 6U, 8U, 33U, 32U, 107U, 569U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus07 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  7U,  8U }}, {{  5U,  2U,  9U }},
            {{ 10U,  8U,  0U }}, {{  1U,  3U,  4U }},
            {{  9U,  0U,  6U }}, {{  7U,  5U,  3U }},
            {{  2U,  6U, 10U }}, {{  8U,  9U,  1U }},
            {{  4U, 10U,  7U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 6U, 8U, 31U, 28U, 107U, 554U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus08 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  7U,  8U }}, {{  5U,  2U,  9U }},
            {{ 10U,  8U,  0U }}, {{  1U,  3U,  4U }},
            {{  9U,  0U,  6U }}, {{  4U,  5U,  7U }},
            {{  2U,  6U, 10U }}, {{  8U,  9U,  1U }},
            {{  7U, 10U,  3U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 6U, 8U, 30U, 28U, 106U, 547U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus09 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  7U,  8U }}, {{  5U,  2U,  9U }},
            {{ 10U,  8U,  0U }}, {{  1U,  6U,  4U }},
            {{  9U,  0U,  3U }}, {{  7U,  5U,  1U }},
            {{  2U,  3U, 10U }}, {{  8U,  9U,  7U }},
            {{  4U, 10U,  6U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 6U, 8U, 29U, 28U, 108U, 556U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus10 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  7U,  8U }}, {{  9U, 10U,  4U }},
            {{  7U,  2U,  1U }}, {{  5U,  8U,  0U }},
            {{  1U,  9U,  3U }}, {{  4U,  5U,  6U }},
            {{ 10U,  0U,  7U }}, {{  2U,  6U,  9U }},
            {{  8U,  3U, 10U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 6U, 7U, 36U, 34U, 97U, 500U, 5U },
    };

    inline static constexpr LoopCorePattern11 mNexus11 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  7U,  8U }}, {{  9U,  5U,  0U }},
            {{ 10U,  2U,  1U }}, {{  7U,  8U,  4U }},
            {{  1U,  9U,  3U }}, {{  4U, 10U,  6U }},
            {{  5U,  0U,  7U }}, {{  2U,  6U,  9U }},
            {{  8U,  3U, 10U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 6U, 7U, 37U, 32U, 94U, 495U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus12 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  7U,  8U }}, {{  1U,  9U,  4U }},
            {{ 10U,  5U,  0U }}, {{  2U,  8U,  7U }},
            {{  9U,  0U,  3U }}, {{  4U,  2U,  6U }},
            {{  7U, 10U,  1U }}, {{  5U,  6U,  9U }},
            {{  8U,  3U, 10U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 6U, 7U, 36U, 32U, 97U, 505U, 4U },
    };

    inline static constexpr LoopCorePattern11 mNexus13 = {
        {{
            {{  0U,  1U,  2U }}, {{  3U,  4U,  5U }},
            {{  6U,  2U,  7U }}, {{  8U,  9U,  4U }},
            {{ 10U,  7U,  1U }}, {{  9U,  5U,  0U }},
            {{  2U, 10U,  3U }}, {{  4U,  0U,  6U }},
            {{  7U,  3U,  8U }}, {{  1U,  6U,  9U }},
            {{  5U,  8U, 10U }},
        }},
        { 22U, 0U, 1U, 0U, 0U, 6U, 7U, 39U, 29U, 98U, 534U, 4U },
    };

    inline static constexpr std::array<LoopCorePattern11, kHeartCount>
        kNexuses = {{
            mNexus00, mNexus01, mNexus02, mNexus03,
            mNexus04, mNexus05, mNexus06, mNexus07,
            mNexus08, mNexus09, mNexus10, mNexus11,
            mNexus12, mNexus13,
        }};

    inline static constexpr std::array<std::size_t, kHeartCount>
        kSourceHeartIndices = {{
            0U, 1U, 2U, 3U, 6U, 9U, 17U,
            20U, 21U, 22U, 29U, 36U, 37U, 58U,
        }};
};

#endif /* LoopNexusHearts_hpp */
