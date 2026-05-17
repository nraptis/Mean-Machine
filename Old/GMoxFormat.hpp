#ifndef GMoxFormat_hpp
#define GMoxFormat_hpp

#include <cstddef>
#include <string>
#include <vector>

#include "GMoxType.hpp"

class GMoxFormat {
public:
    std::string mName;

    std::size_t mOrbiterCount = 4;
    std::size_t mWandererCount = 4;
    std::size_t mPassCount = 4;

    std::size_t mSaltLaneCount = 6;
    std::size_t mPlugLaneCount = 6;

    bool mAllowHiddenStatePlugTaps = false;
    bool mAllowIntermediateHiddenPlugTaps = true;

    std::vector<int> mPassSaltBiases;

    std::vector<GMoxType> Orbiters() const;
    std::vector<GMoxType> Wanderers() const;

    bool IsValid() const;
};

#endif /* GMoxFormat_hpp */
