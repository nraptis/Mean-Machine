#ifndef FoldControlCore_hpp
#define FoldControlCore_hpp

#include "ControlValueFile.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

namespace FoldControlCore {

enum class Flavor {
    kSeed,
    kTwist,
};

void Reset(Flavor pFlavor, std::uint64_t pSeed);
std::string Generate(Flavor pFlavor,
                     std::uint64_t pExplorationCases);
std::string RenderCandidate(Flavor pFlavor,
                            std::size_t pCandidateIndex,
                            const std::string &pClassName);
void Print(Flavor pFlavor);
bool SaveValues(Flavor pFlavor,
                const std::string &pFolder,
                std::string *pErrorMessage);
bool LoadValues(Flavor pFlavor,
                const std::string &pFolder,
                std::string *pErrorMessage);
bool ValidateCandidate(Flavor pFlavor,
                       std::size_t pCandidateIndex,
                       std::string *pErrorMessage);
std::size_t GeneratedCount(Flavor pFlavor);

} // namespace FoldControlCore

#endif /* FoldControlCore_hpp */
