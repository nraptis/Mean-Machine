//
//  ArrangementFour.cpp
//  MeanMachine
//
//  Created by nick on 7/29/26.
//

#include "ArrangementFour.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

namespace {

using Arrangement = std::array<std::size_t, 4U>;

constexpr std::array<Arrangement, 24U> kArrangements = {{
    
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 2U, 3U }},
    
    /*
    {{ 0U, 1U, 2U, 3U }},
    {{ 0U, 1U, 3U, 2U }},
    {{ 0U, 2U, 1U, 3U }},
    {{ 0U, 2U, 3U, 1U }},
    {{ 0U, 3U, 1U, 2U }},
    {{ 0U, 3U, 2U, 1U }},

    {{ 1U, 0U, 2U, 3U }},
    {{ 1U, 0U, 3U, 2U }},
    {{ 1U, 2U, 0U, 3U }},
    {{ 1U, 2U, 3U, 0U }},
    {{ 1U, 3U, 0U, 2U }},
    {{ 1U, 3U, 2U, 0U }},

    {{ 2U, 0U, 1U, 3U }},
    {{ 2U, 0U, 3U, 1U }},
    {{ 2U, 1U, 0U, 3U }},
    {{ 2U, 1U, 3U, 0U }},
    {{ 2U, 3U, 0U, 1U }},
    {{ 2U, 3U, 1U, 0U }},

    {{ 3U, 0U, 1U, 2U }},
    {{ 3U, 0U, 2U, 1U }},
    {{ 3U, 1U, 0U, 2U }},
    {{ 3U, 1U, 2U, 0U }},
    {{ 3U, 2U, 0U, 1U }},
    {{ 3U, 2U, 1U, 0U }},
    */
    
}};

constexpr bool IsCompleteArrangement(const Arrangement &pArrangement) {
    std::array<bool, 4U> aSeen = {{ false, false, false, false }};

    for (const std::size_t aIndex : pArrangement) {
        if ((aIndex >= aSeen.size()) || aSeen[aIndex]) {
            return false;
        }
        aSeen[aIndex] = true;
    }

    return aSeen[0] && aSeen[1] && aSeen[2] && aSeen[3];
}

constexpr bool AreAllArrangementsUnique() {
    for (std::size_t aIndex = 0U; aIndex < kArrangements.size(); ++aIndex) {
        if (!IsCompleteArrangement(kArrangements[aIndex])) {
            return false;
        }

        for (std::size_t aOtherIndex = aIndex + 1U;
             aOtherIndex < kArrangements.size();
             ++aOtherIndex) {
            if (kArrangements[aIndex] == kArrangements[aOtherIndex]) {
                return false;
            }
        }
    }

    return true;
}

std::size_t WrappedArrangementIndex(const int pIndex,
                                    const int pOffset) {
    constexpr std::int64_t kArrangementCount =
        static_cast<std::int64_t>(kArrangements.size());

    const std::int64_t aCombinedIndex =
        static_cast<std::int64_t>(pIndex) +
        static_cast<std::int64_t>(pOffset);
    const std::int64_t aWrappedIndex =
        ((aCombinedIndex % kArrangementCount) + kArrangementCount) %
        kArrangementCount;

    return static_cast<std::size_t>(aWrappedIndex);
}

} // namespace

ArrangementFour::SlotArray4 ArrangementFour::Arrange(
    const SlotArray4 &pItems,
    const int pIndex,
    const int pOffset) {
    const Arrangement &aArrangement =
        kArrangements[WrappedArrangementIndex(pIndex, pOffset)];

    return {{
        pItems[aArrangement[0]],
        pItems[aArrangement[1]],
        pItems[aArrangement[2]],
        pItems[aArrangement[3]],
    }};
}

std::vector<TwistWorkSpaceSlot> ArrangementFour::Arrange(
    const std::vector<TwistWorkSpaceSlot> &pItems,
    const int pIndex,
    const int pOffset) {
    if (pItems.size() != 4U) {
        return {};
    }

    const Arrangement &aArrangement =
        kArrangements[WrappedArrangementIndex(pIndex, pOffset)];

    return {
        pItems[aArrangement[0]],
        pItems[aArrangement[1]],
        pItems[aArrangement[2]],
        pItems[aArrangement[3]],
    };
}
