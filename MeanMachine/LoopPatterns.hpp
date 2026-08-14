//
//  LoopPatterns.hpp
//  MeanMachine
//

#ifndef LoopPatterns_hpp
#define LoopPatterns_hpp

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

constexpr std::size_t LOOP_PATTERN_ROLE_COUNT_11 = 11U;
constexpr std::size_t LOOP_RECIPE_METRIC_COUNT_11 = 50U;

struct LoopCorePatternScore11 {
    std::uint32_t mDirectedEdgeCount = 0U;
    std::uint32_t mReciprocalEdgeCount = 0U;
    std::uint32_t mStronglyConnected = 0U;
    std::uint32_t mArticulationPointCount = 0U;
    std::uint32_t mBridgeCount = 0U;
    std::uint32_t mMinimumDestinationSources = 0U;
    std::uint32_t mMinimumSourceReach = 0U;
    std::uint32_t mMinimumDestinationCurveArea = 0U;
    std::uint32_t mMinimumSourceCurveArea = 0U;
    std::uint32_t mFinalInfluenceTotal = 0U;
    std::uint32_t mInfluenceCurveArea = 0U;
    std::uint32_t mDirectedDiameter = 0U;
};

struct LoopCorePattern11 {
    // Row-major triplets. Each triplet is { lead, source, feedback }.
    std::array<std::array<std::uint8_t, 3U>,
               LOOP_PATTERN_ROLE_COUNT_11> mRounds{};
    LoopCorePatternScore11 mScore;
};

struct LoopHeadPattern11 {
    // Index = orbiter A...K. Value = wanderer A...K.
    std::array<std::uint8_t,
               LOOP_PATTERN_ROLE_COUNT_11> mWandererForOrbiter{};
    std::uint32_t mPermutationRank = 0U;
    std::uint8_t mWorstDistance = 0U;
    std::uint32_t mDistanceTotal = 0U;
};

struct LoopTailPattern11 {
    // Both arrays are indexed by destination wanderer A...K.
    std::array<std::uint8_t,
               LOOP_PATTERN_ROLE_COUNT_11> mOrbiterAForWanderer{};
    std::array<std::uint8_t,
               LOOP_PATTERN_ROLE_COUNT_11> mOrbiterBForWanderer{};
};

struct LoopRecipeMetadata11 {
    std::size_t mNexusIndex = 0U;
    std::size_t mSourceHeartIndex = 0U;
    std::uint64_t mFileIndex = 0ULL;
    std::uint32_t mPatternIndex = 0U;
    std::int32_t mIntegerScore = 0;
    std::int32_t mMinimumScore = 0;
    std::uint64_t mRawAttempt = 0ULL;
    std::uint64_t mAcceptedOrdinal = 0ULL;
    std::string mSourceFile;
    std::array<std::int32_t,
               LOOP_RECIPE_METRIC_COUNT_11> mMetrics{};
};

struct LoopRecipe11 {
    LoopCorePattern11 mCore;
    LoopHeadPattern11 mHead;
    LoopTailPattern11 mTail;
    LoopRecipeMetadata11 mMetadata;
};

#endif /* LoopPatterns_hpp */
