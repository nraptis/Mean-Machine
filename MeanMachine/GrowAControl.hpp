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
    static void Print();
    static bool SavePreview(const std::string &pPath,
                            std::string *pErrorMessage = nullptr);
};

#endif /* GrowAControl_hpp */
