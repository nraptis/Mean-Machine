#include "GMoxSkeleton.hpp"

static GMoxPatternKind PatternForPass(std::size_t passIndex) {
    switch (passIndex % 4) {
        case 0: return GMoxPatternKind::kRingForward;
        case 1: return GMoxPatternKind::kStrideForward;
        case 2: return GMoxPatternKind::kReverseRing;
        default: return GMoxPatternKind::kLongCross;
    }
}

static int ForwardStrideForPattern(GMoxPatternKind pattern, std::size_t width) {
    if (width <= 1) {
        return 0;
    }

    switch (pattern) {
        case GMoxPatternKind::kRingForward:
            return 1;

        case GMoxPatternKind::kStrideForward:
            return width > 2 ? 2 : 1;

        case GMoxPatternKind::kReverseRing:
            return -1;

        case GMoxPatternKind::kLongCross:
            return static_cast<int>((width / 2) == 0 ? 1 : (width / 2));

        case GMoxPatternKind::kInterleave:
            return width > 3 ? 3 : 1;

        case GMoxPatternKind::kFoldback:
            return -2;

        default:
            return 1;
    }
}

static std::size_t WrapIndex(int value, std::size_t width) {
    int w = static_cast<int>(width);
    int v = value % w;

    if (v < 0) {
        v += w;
    }

    return static_cast<std::size_t>(v);
}

static void BuildForwardRounds(GMoxSkeletonPass *pass,
                               GMoxPatternKind pattern,
                               std::size_t width) {
    if (pass == nullptr || width == 0) {
        return;
    }

    const int sourceStride = ForwardStrideForPattern(pattern, width);
    const int feedbackStride = sourceStride + 2;

    for (std::size_t i = 0; i < width; i++) {
        GMoxForwardRound round;

        round.mLead = GMoxType::Orbiter(static_cast<std::uint8_t>(i));
        round.mSource = GMoxType::Orbiter(
            static_cast<std::uint8_t>(WrapIndex(static_cast<int>(i) + sourceStride, width))
        );
        round.mFeedback = GMoxType::Orbiter(
            static_cast<std::uint8_t>(WrapIndex(static_cast<int>(i) + feedbackStride, width))
        );

        pass->mForward.push_back(round);
    }
}

static void BuildBackwardRounds(GMoxSkeletonPass *pass,
                                const GMoxModel &model) {
    if (pass == nullptr) {
        return;
    }

    const std::size_t wandererCount = model.mWandererCount;
    const std::size_t orbiterCount = model.mOrbiterCount;

    if (wandererCount == 0 || orbiterCount == 0) {
        return;
    }

    for (std::size_t i = 0; i < wandererCount; i++) {
        GMoxBackwardRound round;

        round.mTarget = GMoxType::Wanderer(static_cast<std::uint8_t>(i));

        if (model.mUseHiddenStateAsSaltPlug &&
            model.mHiddenPlugRoundIndex >= 0 &&
            static_cast<std::size_t>(model.mHiddenPlugRoundIndex) == i) {
            round.mShape = GMoxUnwindShape::kHiddenPlugMix;
            round.mInputA = GMoxType::Secret(GMoxSecretKind::kCurrent);
            round.mInputB = GMoxType::Wanderer(
                static_cast<std::uint8_t>(WrapIndex(static_cast<int>(i) - 1, wandererCount))
            );
            round.mInputC = GMoxType::Orbiter(
                static_cast<std::uint8_t>(i % orbiterCount)
            );
        } else if ((i & 1U) == 0U) {
            round.mShape = GMoxUnwindShape::kCurrentPreviousOrbiter;
            round.mInputA = GMoxType::Secret(GMoxSecretKind::kCurrent);
            round.mInputB = GMoxType::Secret(GMoxSecretKind::kPrevious);
            round.mInputC = GMoxType::Orbiter(
                static_cast<std::uint8_t>(i % orbiterCount)
            );
        } else {
            round.mShape = GMoxUnwindShape::kOrbiterPair;
            round.mInputA = GMoxType::Orbiter(
                static_cast<std::uint8_t>(i % orbiterCount)
            );
            round.mInputB = GMoxType::Orbiter(
                static_cast<std::uint8_t>((i + 1) % orbiterCount)
            );
            round.mInputC = GMoxType::Secret(GMoxSecretKind::kScatter);
        }

        pass->mBackward.push_back(round);
    }
}

GMoxSkeleton GMoxSkeleton::Build(const GMoxModel &model) {
    GMoxSkeleton result;

    for (std::size_t passIndex = 0; passIndex < model.mPassCount; passIndex++) {
        GMoxSkeletonPass pass;

        pass.mPattern = PatternForPass(passIndex);

        BuildForwardRounds(&pass, pass.mPattern, model.mOrbiterCount);
        BuildBackwardRounds(&pass, model);

        result.mPasses.push_back(pass);
    }

    return result;
}
