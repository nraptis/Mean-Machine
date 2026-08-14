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
    static constexpr std::size_t kLaneCount = 4U;
    static constexpr std::size_t kStageOneBlockCount = 4U;
    static constexpr std::size_t kStageOneInputCount = 2U;
    static constexpr std::size_t kSourceHalfBlockCount = 8U;
    static constexpr std::size_t kStageTwoOutputCount = 4U;
    static constexpr std::size_t kStageTwoSourceBlockCount = 4U;

    struct StageOne {
        // [fork][source lane]. Fork B always receives the complementary half.
        std::array<std::array<std::uint8_t, kLaneCount>,
                   kForkCount> mSourceHalves{};

        // [fork][destination lane][destination block][input byte]
        std::array<std::array<std::array<std::array<std::uint8_t,
                                                    kStageOneInputCount>,
                                         kStageOneBlockCount>,
                              kLaneCount>,
                   kForkCount> mSourceLanes{};
        std::array<std::array<std::array<std::array<std::uint8_t,
                                                    kStageOneInputCount>,
                                         kStageOneBlockCount>,
                              kLaneCount>,
                   kForkCount> mSourceBlocks{};
        std::array<std::array<std::array<std::array<std::uint16_t,
                                                    kStageOneInputCount>,
                                         kStageOneBlockCount>,
                              kLaneCount>,
                   kForkCount> mSourceOffsets{};
        std::array<std::array<std::array<std::array<std::uint8_t,
                                                    kStageOneInputCount>,
                                         kStageOneBlockCount>,
                              kLaneCount>,
                   kForkCount> mWordShifts{};
        std::array<std::array<std::array<std::uint8_t,
                                         kStageOneBlockCount>,
                              kLaneCount>,
                   kForkCount> mOutputShifts{};
    };

    struct StageTwo {
        // [fork][output lane][source lane]
        std::array<std::array<std::array<std::uint8_t,
                                         kLaneCount>,
                              kStageTwoOutputCount>,
                   kForkCount> mSourceBlocks{};
        std::array<std::array<std::array<std::uint16_t,
                                         kLaneCount>,
                              kStageTwoOutputCount>,
                   kForkCount> mSourceOffsets{};
        std::array<std::array<std::array<std::uint8_t,
                                         kLaneCount>,
                              kStageTwoOutputCount>,
                   kForkCount> mWordShifts{};
        std::array<std::array<std::uint8_t,
                              kStageTwoOutputCount>,
                   kForkCount> mOutputShifts{};
    };

    struct Candidate {
        StageOne mStageOne{};
        StageTwo mStageTwo{};
    };

    static void Reset(std::uint64_t pSeed = 0x4B4559464F524B32ULL);
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
