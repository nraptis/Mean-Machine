#ifndef ResidualKDFControl_hpp
#define ResidualKDFControl_hpp

#include "Library - Twist/TwistWorkSpace.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

class ResidualBucket;

class ResidualKDFControl {
public:
    using Slot = TwistWorkSpaceSlot;

    static constexpr std::size_t kCandidateCount = 17U;
    static constexpr std::size_t kDomainCount = 6U;
    static constexpr std::size_t kWithdrawalCountPerDomain = 7U;
    static constexpr std::size_t kWithdrawalCount =
        kDomainCount * kWithdrawalCountPerDomain;
    static constexpr std::size_t kResidualSlotCountPerDomain = 95U;
    static constexpr std::size_t kResidualSlotCount =
        kDomainCount * kResidualSlotCountPerDomain;

    struct Candidate {
        std::array<Slot, kResidualSlotCount> mSlots{};
    };

    static void Reset(std::uint64_t pSeed = 0x52455349444B4446ULL);

    // Each call adds one complete six-domain schedule. For candidates after
    // the first, N independently valid flows are explored and the flow with
    // the greatest minimum distance from the retained family is selected.
    static std::string Generate(std::uint64_t pExplorationCases = 50000ULL);

    static bool SaveValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);
    static bool LoadValues(const std::string &pFolder,
                           std::string *pErrorMessage = nullptr);

    static bool ApplyCandidate(std::size_t pCandidateIndex,
                               ResidualBucket *pResidualBucket,
                               std::string *pErrorMessage = nullptr);
    static bool FinishCandidate(ResidualBucket *pResidualBucket,
                                std::string *pErrorMessage = nullptr);
    static bool ValidateCandidate(std::size_t pCandidateIndex,
                                  std::string *pErrorMessage = nullptr);
    static const Candidate *CandidateAt(std::size_t pCandidateIndex);
    static std::size_t GeneratedCount();
};

#endif /* ResidualKDFControl_hpp */
