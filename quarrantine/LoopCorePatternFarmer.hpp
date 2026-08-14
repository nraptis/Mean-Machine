//
//  LoopCorePatternFarmer.hpp
//  MeanMachine
//

#ifndef LoopCorePatternFarmer_hpp
#define LoopCorePatternFarmer_hpp

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

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
    std::array<std::array<std::uint8_t, 3U>, 11U> mRounds{};
    LoopCorePatternScore11 mScore;
};

struct LoopCorePatternFile11 {
    std::uint64_t mEvaluatedCount = 0ULL;
    std::uint64_t mEligibleCount = 0ULL;
    LoopCorePatternScore11 mWholeWorst;
    LoopCorePatternScore11 mWholeBest;
    LoopCorePatternScore11 mChosenWorst;
    LoopCorePatternScore11 mChosenBest;
    std::vector<LoopCorePattern11> mPatterns;
};

class LoopCorePatternFarmer {
public:
    static bool Load(const std::string &pPath,
                     LoopCorePatternFile11 *pFile,
                     std::string *pErrorMessage = nullptr);
};

#endif /* LoopCorePatternFarmer_hpp */
