#ifndef GMoxModel_hpp
#define GMoxModel_hpp

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "GMoxFormat.hpp"

enum class GMoxModelSize : std::uint8_t {
    kFour = 4,
    kSix = 6,
    kSeven = 7,
    kNine = 9,
    kEleven = 11
};

enum class GMoxFlavorKind : std::uint8_t {
    kCompact = 0,
    kBalanced = 1,
    kWideCross = 2,
    kHeavyHidden = 3
};

class GMoxModel {
public:
    std::string mName;
    GMoxModelSize mSize = GMoxModelSize::kFour;
    GMoxFlavorKind mFlavor = GMoxFlavorKind::kCompact;

    std::size_t mOrbiterCount = 4;
    std::size_t mWandererCount = 4;
    std::size_t mPassCount = 4;

    bool mUseHiddenStateAsSaltPlug = false;
    int mHiddenPlugRoundIndex = -1;

    std::vector<int> mForwardStrides;
    std::vector<int> mFeedbackStrides;
    std::vector<int> mUnwindStrides;

    GMoxFormat MakeFormat() const;
};

#endif /* GMoxModel_hpp */
