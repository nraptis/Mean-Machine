//
//  ArrangementFour.hpp
//  MeanMachine
//
//  Created by nick on 7/29/26.
//

#ifndef ArrangementFour_hpp
#define ArrangementFour_hpp

#include "Library - Twist/TwistWorkSpace.hpp"

#include <array>
#include <cstddef>
#include <vector>

class ArrangementFour {
public:
    using SlotArray4 = std::array<TwistWorkSpaceSlot, 4U>;

    static SlotArray4                                      Arrange(
        const SlotArray4 &pItems,
        int pIndex,
        int pOffset);

    static std::vector<TwistWorkSpaceSlot>                Arrange(
        const std::vector<TwistWorkSpaceSlot> &pItems,
        int pIndex,
        int pOffset);
};

#endif /* ArrangementFour_hpp */
