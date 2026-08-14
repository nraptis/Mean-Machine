#ifndef KeyLaneControl_hpp
#define KeyLaneControl_hpp

#include "Library - Twist/TwistWorkSpace.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

class KeyLaneControl {
public:
    using Slot = TwistWorkSpaceSlot;

    static constexpr std::size_t kActiveCandidateCount = 16U;
    static constexpr std::size_t kCandidateCount = 17U;
    static constexpr std::size_t kKeyFunctionCount = 16U;
    static constexpr std::size_t kFamilyCount = 29U;
    static constexpr std::size_t kFamilyLaneCount = 4U;
    static constexpr std::size_t kAssignmentCount =
        kFamilyCount * kFamilyLaneCount;

    struct Assignment {
        Slot mLane = Slot::kInvalid;
        std::uint64_t mKeyOrder = 0ULL;
        std::uint64_t mSplitOrder = 0ULL;
    };

    struct Score {
        std::uint16_t mWorstRelativeFrequency = 0U;
        std::uint16_t mWorstExactOverlap = 0U;
        std::uint16_t mMinimumOccupancy = 0U;
        std::uint16_t mMaximumOccupancy = 0U;
        std::uint64_t mRelativePenalty = 0ULL;
        std::uint64_t mOccupancyPenalty = 0ULL;
        std::uint64_t mMinimumCandidateDistance = 0ULL;
        std::uint64_t mTotalCandidateDistance = 0ULL;
    };

    static void Reset(std::uint64_t pSeed = 0x4B45594C414E4532ULL);

    // One exploration case proposes one complete four-lane family. The
    // control selects every family together and returns one frozen table.
    static std::string Generate(std::uint64_t pExplorationCases = 50000ULL);

    static bool SaveValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static bool LoadValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);

    // Atomically replaces only the kAssignments array in the checked-in
    // KeyLaneAssignments header. All validation code remains hand-written.
    static bool WriteAssignmentsHeader(
        const std::string &pHeaderPath,
        std::string *pErrorMessage = nullptr);

    static bool Validate(std::string *pErrorMessage = nullptr);
    static const Assignment *AssignmentAt(std::size_t pIndex);
    static const Score *CurrentScore();
    static bool HasValues();
};

#endif /* KeyLaneControl_hpp */
