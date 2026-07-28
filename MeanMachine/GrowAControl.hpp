#ifndef GrowAControl_hpp
#define GrowAControl_hpp

#include <cstddef>
#include <cstdint>
#include <string>

class GrowAControl {
public:
    static constexpr std::size_t kCandidateCount = 33U;

    static void Reset(std::uint64_t pSeed = 0x47524F57415F3333ULL);
    static std::string Generate(std::uint64_t pExplorationCases = 50000ULL);
    static std::string RenderCandidate(std::size_t pCandidateIndex);
    static void Print();
    static bool SaveValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static bool LoadValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static bool ValidateCandidate(std::size_t pCandidateIndex,
                                  std::string *pErrorMessage = nullptr);
    static std::size_t GeneratedCount();
};

#endif /* GrowAControl_hpp */
