#ifndef GMoxHotSchedule_hpp
#define GMoxHotSchedule_hpp

#include <cstddef>

#include "GMoxFormat.hpp"

class GMoxHotSchedule {
public:
    std::size_t mSeedBase = 0;
    std::size_t mForwardBase = 0;
    std::size_t mUnwindBase = 0;
    std::size_t mCarryIndex = 0;

    static GMoxHotSchedule Build(const GMoxFormat &format);
};

#endif /* GMoxHotSchedule_hpp */
