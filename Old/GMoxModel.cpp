#include "GMoxModel.hpp"

GMoxFormat GMoxModel::MakeFormat() const {
    GMoxFormat result;

    result.mName = mName;
    result.mOrbiterCount = mOrbiterCount;
    result.mWandererCount = mWandererCount;
    result.mPassCount = mPassCount;

    result.mSaltLaneCount = 6;
    result.mPlugLaneCount = 6;

    result.mAllowHiddenStatePlugTaps = mUseHiddenStateAsSaltPlug;
    result.mAllowIntermediateHiddenPlugTaps = mUseHiddenStateAsSaltPlug;

    result.mPassSaltBiases = { 0, 6, 10, 14 };

    return result;
}
