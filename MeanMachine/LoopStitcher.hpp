//
//  LoopStitcher.hpp
//  MeanMachine
//

#ifndef LoopStitcher_hpp
#define LoopStitcher_hpp

#include "LoopPatterns.hpp"

#include <array>
#include <cstddef>
#include <string>
#include <vector>

class LoopStitcher {
public:
    static constexpr std::size_t kHeartCount = 14U;
    static constexpr std::size_t kExpanderCount = 17U;
    // The generated expander consumes 656 loop structures. Keep the same
    // 72-record cushion that the previous 528/600 layout used.
    static constexpr std::size_t kRecipesPerExpander = 728U;

    using ExpanderBuckets = std::array<std::vector<LoopRecipe11>,
                                       kExpanderCount>;

    // Load the fourteen nexus folders, validate every final loop record,
    // shuffle each nexus bucket and the nexus order, then deal the recipes
    // round-robin into seventeen independently shuffled expander buckets.
    static bool Load(const std::string &pFolderPath,
                     ExpanderBuckets *pExpanderBuckets,
                     std::string *pErrorMessage = nullptr);
};

#endif /* LoopStitcher_hpp */
