//
//  LoopHeadFarmer.hpp
//  MeanMachine
//

#ifndef LoopHeadFarmer_hpp
#define LoopHeadFarmer_hpp

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

struct LoopHeadPattern11 {
    // Index = orbiter A...K. Value = wanderer A...K.
    std::array<std::uint8_t, 11U> mWandererForOrbiter{};
    std::uint32_t mPermutationRank = 0U;
    std::uint8_t mWorstDistance = 0U;
    std::uint32_t mDistanceTotal = 0U;
};

class LoopHeadFarmer {
public:
    static constexpr std::size_t kRoleCount = 11U;
    static constexpr std::uint32_t kPermutationCount = 39'916'800U;
    static constexpr std::size_t kCoreCount = 180U;
    static constexpr std::size_t kPatternsPerCore = 110U;
    static constexpr std::size_t kRetainedPatternCount =
        kCoreCount * kPatternsPerCore;

    // The identity mapping is deliberately candidate zero.
    static LoopHeadPattern11 Identity();

    static bool IsValid(const LoopHeadPattern11 &pPattern);

    // Compact, collision-free encodings for later farming machinery.
    // PackedKey uses 44 bits. Rank occupies [0, 11! - 1].
    static std::uint64_t PackedKey(const LoopHeadPattern11 &pPattern);
    static std::uint32_t Rank(const LoopHeadPattern11 &pPattern);
    static LoopHeadPattern11 PatternForRank(std::uint32_t pRank);

    // Patterns are saved in final score order. A core receives one pattern
    // from each consecutive 180-pattern quality band.
    static constexpr std::size_t PatternIndex(
        const std::size_t pCoreIndex,
        const std::size_t pPatternIndex) {
        return (pPatternIndex * kCoreCount) + pCoreIndex;
    }

    static bool Farm(const std::string &pPath,
                     std::string *pErrorMessage = nullptr);

    static bool Load(const std::string &pPath,
                     std::array<LoopHeadPattern11,
                                kRetainedPatternCount> *pPatterns,
                     std::string *pErrorMessage = nullptr);

    // pPermutationLimit == 0 walks the complete 11! space. This is a
    // streaming survey: it does not retain the 39,916,800 candidates.
    static bool Survey(std::uint64_t pPermutationLimit,
                       std::string *pErrorMessage = nullptr);
};

#endif /* LoopHeadFarmer_hpp */
