//
//  LoopRecipeFarmer.hpp
//  MeanMachine
//

#ifndef LoopRecipeFarmer_hpp
#define LoopRecipeFarmer_hpp

#include "LoopNewFarmer.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

struct LoopRecipe11 {
    LoopCorePattern11 mCore;
    LoopHeadPattern11 mHead;
    LoopTailPattern11 mTail;
};

class LoopRecipeFarmer {
public:
    static constexpr std::size_t kExpanderCount = 33U;
    static constexpr std::size_t kRecipesPerExpander =
        LoopHeadFarmer::kRetainedPatternCount / kExpanderCount;
    static_assert(kRecipesPerExpander * kExpanderCount ==
                  LoopHeadFarmer::kRetainedPatternCount);

    // Phase IV: join core + head + tail, shuffle recipes inside every core,
    // shuffle the core buckets, then deal one bucket at a time round-robin.
    static bool Build(const std::string &pCorePatternPath,
                      const std::string &pHeadPatternPath,
                      const std::string &pTailPatternPath,
                      const std::string &pOutputFolderPath,
                      std::uint64_t pShuffleSeed,
                      std::string *pErrorMessage = nullptr);

    static bool Load(const std::string &pRecipeFolderPath,
                     std::size_t pExpanderIndex,
                     std::vector<LoopRecipe11> *pRecipes,
                     std::string *pErrorMessage = nullptr);

    static bool LoadAll(
        const std::string &pRecipeFolderPath,
        std::array<std::vector<LoopRecipe11>, kExpanderCount> *pRecipes,
        std::string *pErrorMessage = nullptr);
};

#endif /* LoopRecipeFarmer_hpp */
