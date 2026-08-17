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
    static constexpr std::size_t kRequiredRecipesPerExpander = 656U;

    using ExpanderBuckets = std::array<std::vector<LoopRecipe11>,
                                       kExpanderCount>;

    // Load the fourteen nexus folders, validate every final loop record,
    // shuffle each nexus bucket and the nexus order, then deal every unique
    // recipe round-robin into seventeen independently shuffled expander
    // buckets. Loading fails if any expander receives fewer than 656.
    static bool Load(const std::string &pFolderPath,
                     ExpanderBuckets *pExpanderBuckets,
                     std::string *pErrorMessage = nullptr);
};

#endif /* LoopStitcher_hpp */
