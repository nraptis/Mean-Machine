//
//  SmartSquashControl.hpp
//  MeanMachine
//
//  Created by icarus black on 7/10/26.
//

#ifndef SmartSquashControl_hpp
#define SmartSquashControl_hpp

#include <cstddef>
#include <cstdint>
#include <string>

class SmartSquashControl {
public:
    static constexpr std::size_t kCandidateCount = 33U;

    // Call once before building a 33-member family. The seed makes a preview repeatable.
    static void Reset(std::uint64_t pSeed = 0x534D415254535153ULL);

    // Builds one family member. pExplorationCases may be 500,000,000 or more.
    // Calling this a 34th time after Reset intentionally aborts.
    static std::string GenerateSquashInvestToKeyBoxes(
        std::uint64_t pExplorationCases = 500000ULL);

    static void Print();
    // pPath is always resolved relative to the project root, even with a leading slash.
    // Also writes one numbered candidate file per generated candidate beside the preview.
    static bool SavePreview(const std::string &pPath,
                            std::string *pErrorMessage = nullptr);
    static std::size_t GeneratedCount();
};

#endif /* SmartSquashControl_hpp */
