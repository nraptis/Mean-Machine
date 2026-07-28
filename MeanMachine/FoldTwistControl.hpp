#ifndef FoldTwistControl_hpp
#define FoldTwistControl_hpp

#include <cstddef>
#include <cstdint>
#include <string>

class FoldTwistControl {
public:
    static constexpr std::size_t kCandidateCount = 33U;

    static void Reset(std::uint64_t pSeed = 0x464F4C4454574953ULL);
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

#endif /* FoldTwistControl_hpp */
