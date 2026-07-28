#ifndef ControlOffsetPool_hpp
#define ControlOffsetPool_hpp

#include <array>
#include <cstddef>
#include <cstdint>

namespace ControlOffsetPool {

// Every W_KEY offset family owns a disjoint section of one shared,
// deterministic permutation. This keeps the literal offsets emitted for
// related controls from overlapping while still spreading each section
// throughout the complete offset range.
constexpr std::size_t kGrowAKeyStart = 0U;
constexpr std::size_t kGrowAKeyCount = 20U;
constexpr std::size_t kGrowBKeyStart =
    kGrowAKeyStart + kGrowAKeyCount;
constexpr std::size_t kGrowBKeyCount = 20U;
constexpr std::size_t kFoldSeedKeyStart =
    kGrowBKeyStart + kGrowBKeyCount;
constexpr std::size_t kFoldSeedKeyCount = 64U;
constexpr std::size_t kFoldTwistKeyStart =
    kFoldSeedKeyStart + kFoldSeedKeyCount;
constexpr std::size_t kFoldTwistKeyCount = 64U;
constexpr std::size_t kKeyAllocationCount =
    kFoldTwistKeyStart + kFoldTwistKeyCount;

// Quarter offsets live in a different index space, but GrowA and GrowB still
// receive disjoint sections within that space.
constexpr std::size_t kGrowAQuarterStart = 0U;
constexpr std::size_t kGrowAQuarterCount = 16U;
constexpr std::size_t kGrowBQuarterStart =
    kGrowAQuarterStart + kGrowAQuarterCount;
constexpr std::size_t kGrowBQuarterCount = 16U;
constexpr std::size_t kQuarterAllocationCount =
    kGrowBQuarterStart + kGrowBQuarterCount;

inline std::size_t Permute(const std::size_t pIndex,
                           const std::size_t pModulus) {
    // The multiplier is odd, so this is a permutation for the power-of-two
    // W_KEY and S_QUARTER ranges used by the workspace.
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
