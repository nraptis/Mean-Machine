//
//  LoopNewFarmer.hpp
//  MeanMachine
//

#ifndef LoopNewFarmer_hpp
#define LoopNewFarmer_hpp

#include "LoopCorePatterns.hpp"
#include "LoopHeadFarmer.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

struct LoopTailPattern11 {
    // Both arrays are indexed by destination wanderer A...K.
    std::array<std::uint8_t,
               LoopHeadFarmer::kRoleCount> mOrbiterAForWanderer{};
    std::array<std::uint8_t,
               LoopHeadFarmer::kRoleCount> mOrbiterBForWanderer{};
};

struct LoopNewHead11 {
    LoopHeadPattern11 mHead;
    LoopTailPattern11 mTail;
};

struct LoopNewHeart11 {
    LoopCorePattern11 mHeart;
    std::array<LoopNewHead11,
               LoopHeadFarmer::kPatternsPerCore> mHeads{};
};

struct LoopNewPatternFile11 {
    std::array<LoopNewHeart11,
               LoopHeadFarmer::kCoreCount> mHearts{};
};

class LoopNewFarmer {
public:
    // Tail records are heart-major: all 110 heads for heart zero, then all
    // 110 heads for heart one, and so on.
    static constexpr std::size_t TailPatternIndex(
        const std::size_t pHeartIndex,
        const std::size_t pHeadIndex) {
        return (pHeartIndex * LoopHeadFarmer::kPatternsPerCore) +
               pHeadIndex;
    }

    // Loads the independently farmed heart and head assets, then joins them
    // using LoopHeadFarmer's saved round-robin layout.
    static bool Load(const std::string &pHeartPatternPath,
                     const std::string &pHeadPatternPath,
                     LoopNewPatternFile11 *pFile,
                     std::string *pErrorMessage = nullptr);

    // Loads and joins all three independently stored pieces of a loop.
    static bool Load(const std::string &pHeartPatternPath,
                     const std::string &pHeadPatternPath,
                     const std::string &pTailPatternPath,
                     LoopNewPatternFile11 *pFile,
                     std::string *pErrorMessage = nullptr);

    static bool LoadTailPatterns(
        const std::string &pTailPatternPath,
        LoopNewPatternFile11 *pFile,
        std::string *pErrorMessage = nullptr);

    // Validates the structural pieces stored in a ready-to-use loop recipe.
    static bool RecipeIsValid(const LoopCorePattern11 &pCore,
                              const LoopHeadPattern11 &pHead,
                              const LoopTailPattern11 &pTail);
};

#endif /* LoopNewFarmer_hpp */
