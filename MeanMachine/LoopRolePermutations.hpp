#ifndef LoopRolePermutations_hpp
#define LoopRolePermutations_hpp

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

class LoopRolePermutations {
public:
    static constexpr std::size_t kExpanderCount = 17U;
    static constexpr std::size_t kFirstHalfExpanderCount = 9U;
    static constexpr std::size_t kPermutationWidth = 11U;
    static constexpr std::size_t kPermutationCount = 656U;
    static constexpr std::size_t kSelectedPermutationCount =
        kPermutationCount * 2U;
    static constexpr std::size_t kFileByteCount =
        kPermutationCount * kPermutationWidth;

    using Permutation =
        std::array<std::uint8_t, kPermutationWidth>;

    // Shuffle Combinations11 once, divide the first 1,312 permutations into
    // two halves, and independently shuffle the assigned half for every file.
    static bool Generate(const std::string &pFolder,
                         std::string *pErrorMessage = nullptr);

    // Validate every emitted file, including its exact source-half membership.
    static bool Verify(const std::string &pFolder,
                       std::string *pErrorMessage = nullptr);

    static bool LoadCandidate(
        const std::string &pFolder,
        std::size_t pCandidateIndex,
        std::vector<Permutation> *pOrbiters,
        std::vector<Permutation> *pWanderers,
        std::string *pErrorMessage = nullptr);

    // Position A-K is the logical scaffold role; the letter stored at that
    // position is the concrete variable assigned to the role.
    static std::string Letters(const Permutation &pPermutation);
};

#endif /* LoopRolePermutations_hpp */
