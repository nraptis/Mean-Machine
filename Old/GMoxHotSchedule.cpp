#include "GMoxHotSchedule.hpp"

GMoxHotSchedule GMoxHotSchedule::Build(const GMoxFormat &format) {
    GMoxHotSchedule result;

    const std::size_t width = format.mOrbiterCount;

    result.mSeedBase = 0;
    result.mForwardBase = result.mSeedBase + width;
    result.mUnwindBase = result.mForwardBase + (width * 2);
    result.mCarryIndex = result.mUnwindBase + format.mWandererCount;

    return result;
}
