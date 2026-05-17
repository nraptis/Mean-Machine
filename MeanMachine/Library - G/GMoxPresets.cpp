#include "GMoxPresets.hpp"

static GMoxModel MakeModel(const std::string &name,
                           GMoxModelSize size,
                           GMoxFlavorKind flavor,
                           std::size_t passCount,
                           bool hiddenPlug,
                           int hiddenPlugRound) {
    GMoxModel result;

    const std::size_t width = static_cast<std::size_t>(size);

    result.mName = name;
    result.mSize = size;
    result.mFlavor = flavor;

    result.mOrbiterCount = width;
    result.mWandererCount = width;
    result.mPassCount = passCount;

    result.mUseHiddenStateAsSaltPlug = hiddenPlug;
    result.mHiddenPlugRoundIndex = hiddenPlugRound;

    result.mForwardStrides = { 1, 2, -1, static_cast<int>(width / 2) };
    result.mFeedbackStrides = { 3, 4, -3, static_cast<int>((width / 2) + 1) };
    result.mUnwindStrides = { 1, -1, 2, -2 };

    return result;
}

GMoxModel GMoxPresets::FourCompact() {
    return MakeModel("GMox4Compact",
                     GMoxModelSize::kFour,
                     GMoxFlavorKind::kCompact,
                     4,
                     true,
                     1);
}

GMoxModel GMoxPresets::SixBalanced() {
    return MakeModel("GMox6Balanced",
                     GMoxModelSize::kSix,
                     GMoxFlavorKind::kBalanced,
                     4,
                     false,
                     -1);
}

GMoxModel GMoxPresets::SevenAsymmetric() {
    return MakeModel("GMox7Asymmetric",
                     GMoxModelSize::kSeven,
                     GMoxFlavorKind::kBalanced,
                     5,
                     true,
                     2);
}

GMoxModel GMoxPresets::NineWideCross() {
    return MakeModel("GMox9WideCross",
                     GMoxModelSize::kNine,
                     GMoxFlavorKind::kWideCross,
                     5,
                     true,
                     3);
}

GMoxModel GMoxPresets::ElevenHeavyHidden() {
    return MakeModel("GMox11HeavyHidden",
                     GMoxModelSize::kEleven,
                     GMoxFlavorKind::kHeavyHidden,
                     6,
                     true,
                     4);
}

std::vector<GMoxModel> GMoxPresets::CandidateModels() {
    return {
        FourCompact(),
        SixBalanced(),
        SevenAsymmetric(),
        NineWideCross(),
        ElevenHeavyHidden()
    };
}

std::vector<GMoxModel> GMoxPresets::RecommendedFourFlavors() {
    return {
        FourCompact(),
        SixBalanced(),
        SevenAsymmetric(),
        NineWideCross()
    };
}
