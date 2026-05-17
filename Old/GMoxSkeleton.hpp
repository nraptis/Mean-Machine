#ifndef GMoxSkeleton_hpp
#define GMoxSkeleton_hpp

#include <cstdint>
#include <vector>

#include "GMoxType.hpp"
#include "GMoxModel.hpp"

enum class GMoxPatternKind : std::uint8_t {
    kRingForward,
    kStrideForward,
    kReverseRing,
    kLongCross,
    kInterleave,
    kFoldback
};

struct GMoxForwardRound {
    GMoxType mLead;
    GMoxType mSource;
    GMoxType mFeedback;
};

enum class GMoxUnwindShape : std::uint8_t {
    kCurrentPreviousOrbiter,
    kCurrentScatterOrbiter,
    kOrbiterPair,
    kHiddenPlugMix
};

struct GMoxBackwardRound {
    GMoxUnwindShape mShape;
    GMoxType mTarget;
    GMoxType mInputA;
    GMoxType mInputB;
    GMoxType mInputC;
};

class GMoxSkeletonPass {
public:
    GMoxPatternKind mPattern = GMoxPatternKind::kRingForward;
    std::vector<GMoxForwardRound> mForward;
    std::vector<GMoxBackwardRound> mBackward;
};

class GMoxSkeleton {
public:
    std::vector<GMoxSkeletonPass> mPasses;

    static GMoxSkeleton Build(const GMoxModel &model);
};

#endif /* GMoxSkeleton_hpp */
