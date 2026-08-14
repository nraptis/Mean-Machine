//
//  LoopTailFarmer.hpp
//  MeanMachine
//

#ifndef LoopTailFarmer_hpp
#define LoopTailFarmer_hpp

#include <cstdint>
#include <string>

class LoopTailFarmer {
public:
    // Load, fully validate, and print one final-farm loop record.
    static bool PrintFinalLoop(
        const std::string &pPath,
        std::string *pErrorMessage = nullptr);

    // Resume the code-defined 14-nexus final farm. The output pool is
    // universal across nexuses; every new recipe must satisfy its nexus's
    // integer score threshold and all three structural-difference gates
    // against every previously accepted recipe.
    static bool FarmFinalLoops(
        const std::string &pOutputFolderPath,
        std::uint64_t pNewLoopTarget,
        std::uint64_t pMaximumAttempts,
        std::uint64_t pProgressInterval,
        std::string *pErrorMessage = nullptr);
};

#endif /* LoopTailFarmer_hpp */
