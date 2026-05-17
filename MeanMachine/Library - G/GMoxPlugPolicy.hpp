#ifndef GMoxPlugPolicy_hpp
#define GMoxPlugPolicy_hpp

#include <cstddef>
#include <cstdint>
#include <vector>

#include "GMoxFormat.hpp"
#include "GMoxPlan.hpp"
#include "GMoxType.hpp"

enum class GMoxPlugTapClass : std::uint8_t {
    kStreamOnly,
    kStreamAndCarry,
    kStreamAndIntermediateHidden,
    kAnyNonOutputHidden
};

struct GMoxPlugSlot {
    GMoxType mTapA;
    GMoxType mTapB;
    int mRotation = -1;
    int mOffset = -1;
    int mSaltLane = -1;
};

class GMoxPlugPolicy {
public:
    GMoxPlugTapClass mTapClass = GMoxPlugTapClass::kStreamOnly;

    bool mEnableHiddenStatePlugOnIntermediateRound = false;
    std::size_t mHiddenPlugPassIndex = 1;
    std::size_t mHiddenPlugGroupIndex = 0;

    std::vector<GMoxType> MakeTapPool(const GMoxFormat &format,
                                      std::size_t passIndex,
                                      std::size_t groupIndex) const;

    bool Assign(std::vector<GMoxStatementGroup *> &groups,
                const GMoxFormat &format,
                std::size_t passIndex) const;
};

#endif /* GMoxPlugPolicy_hpp */
