#ifndef FoldSeedControl_hpp
#define FoldSeedControl_hpp

#include <cstddef>
#include <cstdint>
#include <string>

class FoldSeedControl {
public:
    static constexpr std::size_t kCandidateCount = 33U;

    static void Reset(std::uint64_t pSeed = 0x464F4C4453454544ULL);
    static std::string Generate(std::uint64_t pExplorationCases = 50000ULL);
    static std::string RenderCandidate(std::size_t pCandidateIndex,
                                       const std::string &pClassName);
    static void Print();
    static bool SaveValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static bool LoadValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static bool ValidateCandidate(std::size_t pCandidateIndex,
                                  std::string *pErrorMessage = nullptr);
    static std::size_t GeneratedCount();
};

#endif /* FoldSeedControl_hpp */
