#include "GMoxFormat.hpp"

std::vector<GMoxType> GMoxFormat::Orbiters() const {
    std::vector<GMoxType> result;
    result.reserve(mOrbiterCount);

    for (std::size_t i = 0; i < mOrbiterCount; i++) {
        result.push_back(GMoxType::Orbiter(static_cast<std::uint8_t>(i)));
    }

    return result;
}

std::vector<GMoxType> GMoxFormat::Wanderers() const {
    std::vector<GMoxType> result;
    result.reserve(mWandererCount);

    for (std::size_t i = 0; i < mWandererCount; i++) {
        result.push_back(GMoxType::Wanderer(static_cast<std::uint8_t>(i)));
    }

    return result;
}

bool GMoxFormat::IsValid() const {
    if (mOrbiterCount == 0) {
        return false;
    }

    if (mWandererCount == 0) {
        return false;
    }

    if (mPassCount == 0) {
        return false;
    }

    if (mSaltLaneCount == 0) {
        return false;
    }

    if (mPlugLaneCount == 0) {
        return false;
    }

    if (mOrbiterCount > 255 || mWandererCount > 255) {
        return false;
    }

    return true;
}
