#ifndef KeyForkControl_hpp
#define KeyForkControl_hpp

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

class KeyForkControl {
public:
    static constexpr std::size_t kCandidateCount = 17U;
    static constexpr std::size_t kForkCount = 2U;
    static constexpr std::size_t kOutputLaneCount = 4U;
    static constexpr std::size_t kStageLaneCount = 4U;
    static constexpr std::size_t kInputCount = 2U;
    static constexpr std::size_t kSourceLaneCount = 8U;
    // Logical source blocks. Fork A/B map these to complementary physical
    // parity, while logical quarters map directly to physical quarters.
    static constexpr std::size_t kSourceBlockCount = 32U;
    static constexpr std::size_t kMuBlockCount = 8U;
    static constexpr std::size_t kLelBlockCount = 4U;
    static constexpr std::size_t kGozBlockCount = 2U;

    static constexpr std::size_t PhysicalSourceBlock(
        const std::size_t pFork,
        const std::size_t pSourceLane,
        const std::size_t pLogicalBlock) {
        // Fork A: odd/even/odd/even across A-D in both families.
        // Fork B owns the complementary parity in every source lane.
        const std::size_t aForkAParity =
            1U ^ (pSourceLane & 1U);
        return (pLogicalBlock * 2U) + (aForkAParity ^ pFork);
    }

    struct BlockPick {
        std::uint8_t mLane = 0U;
        std::uint8_t mBlock = 0U;
    };

    using InputPair = std::array<BlockPick, kInputCount>;
    using MuPlans =
        std::array<std::array<std::array<std::array<InputPair,
                                                    kMuBlockCount>,
                                         kStageLaneCount>,
                              kOutputLaneCount>,
                   kForkCount>;
    using LelPlans =
        std::array<std::array<std::array<std::array<InputPair,
                                                    kLelBlockCount>,
                                         kStageLaneCount>,
                              kOutputLaneCount>,
                   kForkCount>;
    using GozPlans =
        std::array<std::array<std::array<std::array<InputPair,
                                                    kGozBlockCount>,
                                         kStageLaneCount>,
                              kOutputLaneCount>,
                   kForkCount>;

    struct Candidate {
        MuPlans mMu{};
        LelPlans mLel{};
        GozPlans mGoz{};
    };

    static void Reset(std::uint64_t pSeed = 0x4B4559464F524B34ULL);
    static std::string Generate(std::uint64_t pExplorationCases = 50000ULL);
    static bool SaveValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static bool LoadValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static bool ValidateCandidate(std::size_t pCandidateIndex,
                                  std::string *pErrorMessage = nullptr);
    static const Candidate *CandidateAt(std::size_t pCandidateIndex);
    static std::size_t GeneratedCount();
};

#endif /* KeyForkControl_hpp */
