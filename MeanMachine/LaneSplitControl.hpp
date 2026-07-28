#ifndef LaneSplitControl_hpp
#define LaneSplitControl_hpp

#include "Library - G/GSeedRunStageConfig.hpp"

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

class LaneSplitControl {
public:
    using Slot = TwistWorkSpaceSlot;
    using LaneGroup = std::vector<Slot>;

    static constexpr std::size_t kCandidateCount = 33U;
    static constexpr std::size_t kLaneSplitCount = 16U;

    static void Reset(std::uint64_t pSeed = 0x4C414E4553504C54ULL);

    // A group defines one contiguous fragment-distance family. A-P are
    // adjacent within a lane, and the end of one lane continues into the
    // next lane in the same group. Non-adjacent lanes and other groups use
    // the infinite-distance score.
    static bool AddLaneGroup(const LaneGroup &pLanes,
                             std::string *pErrorMessage = nullptr);
    static bool AddLaneGroup(std::initializer_list<Slot> pLanes,
                             std::string *pErrorMessage = nullptr);

    static std::string Generate(std::uint64_t pExplorationCases = 50000ULL);

    static bool PhysicalLaneSplit(std::size_t pCandidateIndex,
                                  Slot pLane,
                                  std::size_t pLogicalLaneSplit,
                                  std::uint8_t *pPhysicalLaneSplit,
                                  std::string *pErrorMessage = nullptr);

    // Replaces the slice's ingress/cross roles with the candidate's freely
    // shuffled lane order, then adds the physical-fragment links consumed
    // by GSeedRunStage. Every registered lane is used exactly once.
    static bool LinkStageSlice(GSeedRunStageSliceSpec *pStageSlice,
                               std::size_t pCandidateIndex,
                               std::size_t pLogicalLaneSplit,
                               std::string *pErrorMessage = nullptr);

    // Slice zero uses logical A, slice one uses B, and so on through P.
    static bool LinkStageConfig(GSeedRunStageConfig *pConfig,
                                std::size_t pCandidateIndex,
                                std::string *pErrorMessage = nullptr);

    // Use this overload when stage order and logical A-P order differ.
    static bool LinkStageConfig(
        GSeedRunStageConfig *pConfig,
        std::size_t pCandidateIndex,
        const std::vector<std::uint8_t> &pLogicalLaneSplits,
        std::string *pErrorMessage = nullptr);

    static std::string Declarations(std::size_t pCandidateIndex);
    static void Print();
    static bool SaveValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static bool LoadValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static std::size_t GeneratedCount();
};

#endif /* LaneSplitControl_hpp */
