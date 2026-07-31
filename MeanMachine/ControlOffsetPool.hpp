#ifndef ControlOffsetPool_hpp
#define ControlOffsetPool_hpp

#include <array>
#include <cstddef>
#include <cstdint>

namespace ControlOffsetPool {

// The first fold has sixteen loops with four source positions, for 64
// offsets. The second fold has four loops with four source positions, for
// 16 offsets. GrowA and GrowB own disjoint sections of each deterministic
// permutation so similar fold families cannot reuse an offset by chance.
constexpr std::size_t kStageOneFoldShiftCount = 64U;
constexpr std::size_t kStageTwoFoldShiftCount = 16U;

constexpr std::size_t kGrowAStageOneShiftStart = 0U;
constexpr std::size_t kGrowAStageOneShiftCount =
    kStageOneFoldShiftCount;
constexpr std::size_t kGrowBStageOneShiftStart =
    kGrowAStageOneShiftStart + kGrowAStageOneShiftCount;
constexpr std::size_t kGrowBStageOneShiftCount =
    kStageOneFoldShiftCount;
constexpr std::size_t kStageOneShiftAllocationCount =
    kGrowBStageOneShiftStart + kGrowBStageOneShiftCount;

constexpr std::size_t kGrowAStageTwoShiftStart = 0U;
constexpr std::size_t kGrowAStageTwoShiftCount =
    kStageTwoFoldShiftCount;
constexpr std::size_t kGrowBStageTwoShiftStart =
    kGrowAStageTwoShiftStart + kGrowAStageTwoShiftCount;
constexpr std::size_t kGrowBStageTwoShiftCount =
    kStageTwoFoldShiftCount;
constexpr std::size_t kStageTwoShiftAllocationCount =
    kGrowBStageTwoShiftStart + kGrowBStageTwoShiftCount;

inline std::size_t Permute(const std::size_t pIndex,
                           const std::size_t pModulus) {
    // The multiplier is odd, so this is a permutation for the power-of-two
    // word-index ranges used by the workspace.
    return ((pIndex * 4051U) + 137U) % pModulus;
}

template <std::size_t Count>
std::array<std::uint16_t, Count> Build(const std::size_t pFirst,
                                       const std::size_t pModulus) {
    std::array<std::uint16_t, Count> aPool{};
    for (std::size_t i = 0U; i < Count; ++i) {
        aPool[i] = static_cast<std::uint16_t>(
            Permute(pFirst + i, pModulus)
        );
    }
    return aPool;
}

} // namespace ControlOffsetPool

#endif /* ControlOffsetPool_hpp */
