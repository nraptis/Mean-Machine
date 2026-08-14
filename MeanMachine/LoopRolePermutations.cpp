#include "LoopRolePermutations.hpp"

#include "Combinations11.hpp"
#include "FileIO.hpp"
#include "Random.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <set>
#include <string>
#include <vector>

namespace {

using Permutation = LoopRolePermutations::Permutation;
using PermutationList = std::vector<Permutation>;
using PermutationSet = std::set<Permutation>;

static_assert(kCombinations11_Width ==
              static_cast<int>(LoopRolePermutations::kPermutationWidth));
static_assert(kCombinations11_Count >=
              static_cast<int>(
                  LoopRolePermutations::kSelectedPermutationCount));

void SetError(std::string *pErrorMessage,
              const std::string &pText) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pText;
    }
}

std::string FileName(const std::string &pFolder,
                     const char *pRole,
                     const std::size_t pExpanderIndex) {
    char aName[32];
    std::snprintf(aName,
                  sizeof(aName),
                  "expander_%02zu.bin",
                  pExpanderIndex);
    return FileIO::Join(
        FileIO::Join(FileIO::ProjectRoot(pFolder), pRole),
        aName
    );
}

bool IsPermutation(const Permutation &pPermutation) {
    std::array<bool, LoopRolePermutations::kPermutationWidth> aSeen{};
    for (const std::uint8_t aValue : pPermutation) {
        if ((aValue >= LoopRolePermutations::kPermutationWidth) ||
            aSeen[aValue]) {
            return false;
        }
        aSeen[aValue] = true;
    }
    return true;
}

PermutationList SourcePermutations() {
    PermutationList aResult;
    aResult.reserve(static_cast<std::size_t>(kCombinations11_Count));
    for (std::size_t i = 0U;
         i < static_cast<std::size_t>(kCombinations11_Count);
         ++i) {
        Permutation aPermutation{};
        std::copy_n(kCombinations11[i],
                    LoopRolePermutations::kPermutationWidth,
                    aPermutation.begin());
        aResult.push_back(aPermutation);
    }
    return aResult;
}

std::vector<std::uint8_t> Serialize(
    const PermutationList &pPermutations) {
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(pPermutations.size() *
                   LoopRolePermutations::kPermutationWidth);
    for (const Permutation &aPermutation : pPermutations) {
        aBytes.insert(aBytes.end(),
                      aPermutation.begin(),
                      aPermutation.end());
    }
    return aBytes;
}

bool Deserialize(const std::string &pPath,
                 PermutationList *pPermutations,
                 std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes)) {
        SetError(pErrorMessage,
                 "Could not load permutation file " + pPath);
        return false;
    }
    if (aBytes.size() != LoopRolePermutations::kFileByteCount) {
        SetError(pErrorMessage,
                 "Permutation file had the wrong byte count: " + pPath);
        return false;
    }

    pPermutations->clear();
    pPermutations->reserve(LoopRolePermutations::kPermutationCount);
    for (std::size_t i = 0U;
         i < LoopRolePermutations::kPermutationCount;
         ++i) {
        Permutation aPermutation{};
        const auto aBegin =
            aBytes.begin() + static_cast<std::ptrdiff_t>(
                i * LoopRolePermutations::kPermutationWidth);
        std::copy_n(aBegin,
                    LoopRolePermutations::kPermutationWidth,
                    aPermutation.begin());
        if (!IsPermutation(aPermutation)) {
            SetError(pErrorMessage,
                     "Permutation file contained an invalid record: " +
                     pPath);
            pPermutations->clear();
            return false;
        }
        pPermutations->push_back(aPermutation);
    }
    return true;
}

bool VerifyFile(const std::string &pPath,
                const PermutationSet &pExpected,
                std::string *pErrorMessage) {
    PermutationList aPermutations;
    if (!Deserialize(pPath, &aPermutations, pErrorMessage)) {
        return false;
    }
    const PermutationSet aActual(aPermutations.begin(),
                                 aPermutations.end());
    if ((aActual.size() != LoopRolePermutations::kPermutationCount) ||
        (aActual != pExpected)) {
        SetError(pErrorMessage,
                 "Permutation file did not contain its exact assigned half: " +
                 pPath);
        return false;
    }
    return true;
}

bool VerifyFiles(const std::string &pFolder,
                 const PermutationSet &pFirstHalf,
                 const PermutationSet &pSecondHalf,
                 std::string *pErrorMessage) {
    for (std::size_t i = 0U;
         i < LoopRolePermutations::kExpanderCount;
         ++i) {
        const bool aFirstHalfForOrbiters =
            i < LoopRolePermutations::kFirstHalfExpanderCount;
        const PermutationSet &aOrbiterExpected =
            aFirstHalfForOrbiters ? pFirstHalf : pSecondHalf;
        const PermutationSet &aWandererExpected =
            aFirstHalfForOrbiters ? pSecondHalf : pFirstHalf;
        if (!VerifyFile(FileName(pFolder, "orbiters", i),
                        aOrbiterExpected,
                        pErrorMessage) ||
            !VerifyFile(FileName(pFolder, "wanderers", i),
                        aWandererExpected,
                        pErrorMessage)) {
            return false;
        }
    }
    SetError(pErrorMessage, "");
    return true;
}

} // namespace

bool LoopRolePermutations::Generate(
    const std::string &pFolder,
    std::string *pErrorMessage) {
    PermutationList aSource = SourcePermutations();
    const PermutationSet aAllSource(aSource.begin(), aSource.end());
    if (aAllSource.size() != aSource.size()) {
        SetError(pErrorMessage,
                 "Combinations11 contained duplicate permutations");
        return false;
    }
    for (const Permutation &aPermutation : aSource) {
        if (!IsPermutation(aPermutation)) {
            SetError(pErrorMessage,
                     "Combinations11 contained an invalid permutation");
            return false;
        }
    }

    Random::Shuffle(&aSource);
    PermutationList aFirstHalf(
        aSource.begin(),
        aSource.begin() + static_cast<std::ptrdiff_t>(kPermutationCount)
    );
    PermutationList aSecondHalf(
        aSource.begin() + static_cast<std::ptrdiff_t>(kPermutationCount),
        aSource.begin() +
            static_cast<std::ptrdiff_t>(kSelectedPermutationCount)
    );
    const PermutationSet aFirstHalfSet(aFirstHalf.begin(),
                                       aFirstHalf.end());
    const PermutationSet aSecondHalfSet(aSecondHalf.begin(),
                                        aSecondHalf.end());

    for (std::size_t i = 0U; i < kExpanderCount; ++i) {
        const bool aFirstHalfForOrbiters =
            i < kFirstHalfExpanderCount;
        PermutationList aOrbiters =
            aFirstHalfForOrbiters ? aFirstHalf : aSecondHalf;
        PermutationList aWanderers =
            aFirstHalfForOrbiters ? aSecondHalf : aFirstHalf;
        Random::Shuffle(&aOrbiters);
        Random::Shuffle(&aWanderers);

        const std::string aOrbiterPath =
            FileName(pFolder, "orbiters", i);
        const std::string aWandererPath =
            FileName(pFolder, "wanderers", i);
        if (!FileIO::Save(aOrbiterPath, Serialize(aOrbiters)) ||
            !FileIO::Save(aWandererPath, Serialize(aWanderers))) {
            SetError(pErrorMessage,
                     "Could not save permutation assets for expander " +
                     std::to_string(i));
            return false;
        }
    }

    if (!VerifyFiles(pFolder,
                     aFirstHalfSet,
                     aSecondHalfSet,
                     pErrorMessage)) {
        return false;
    }

    std::printf(
        "Saved 17 orbiter files and 17 wanderer files: "
        "656 permutations x 11 bytes each.\n"
        "Expanders 00-08: orbiters=half-1 wanderers=half-2.\n"
        "Expanders 09-16: orbiters=half-2 wanderers=half-1.\n"
    );
    SetError(pErrorMessage, "");
    return true;
}

bool LoopRolePermutations::Verify(
    const std::string &pFolder,
    std::string *pErrorMessage) {
    // The source split is randomized at generation time, so exact membership
    // is recovered from expander 00 and checked against all remaining files.
    PermutationList aFirstHalf;
    PermutationList aSecondHalf;
    if (!Deserialize(FileName(pFolder, "orbiters", 0U),
                     &aFirstHalf,
                     pErrorMessage) ||
        !Deserialize(FileName(pFolder, "wanderers", 0U),
                     &aSecondHalf,
                     pErrorMessage)) {
        return false;
    }
    const PermutationSet aFirstHalfSet(aFirstHalf.begin(),
                                       aFirstHalf.end());
    const PermutationSet aSecondHalfSet(aSecondHalf.begin(),
                                        aSecondHalf.end());
    if ((aFirstHalfSet.size() != kPermutationCount) ||
        (aSecondHalfSet.size() != kPermutationCount)) {
        SetError(pErrorMessage,
                 "Permutation reference files contained duplicate records");
        return false;
    }
    for (const Permutation &aPermutation : aFirstHalfSet) {
        if (aSecondHalfSet.contains(aPermutation)) {
            SetError(pErrorMessage,
                     "The two selected permutation halves overlapped");
            return false;
        }
    }
    return VerifyFiles(pFolder,
                       aFirstHalfSet,
                       aSecondHalfSet,
                       pErrorMessage);
}

bool LoopRolePermutations::LoadCandidate(
    const std::string &pFolder,
    const std::size_t pCandidateIndex,
    std::vector<Permutation> *pOrbiters,
    std::vector<Permutation> *pWanderers,
    std::string *pErrorMessage) {
    if ((pOrbiters == nullptr) || (pWanderers == nullptr)) {
        SetError(pErrorMessage,
                 "Loop-role permutation destination was null");
        return false;
    }
    pOrbiters->clear();
    pWanderers->clear();
    if (pCandidateIndex >= kExpanderCount) {
        SetError(pErrorMessage,
                 "Loop-role permutation candidate index was out of range");
        return false;
    }
    if (!Deserialize(FileName(pFolder, "orbiters", pCandidateIndex),
                     pOrbiters,
                     pErrorMessage) ||
        !Deserialize(FileName(pFolder, "wanderers", pCandidateIndex),
                     pWanderers,
                     pErrorMessage)) {
        pOrbiters->clear();
        pWanderers->clear();
        return false;
    }
    SetError(pErrorMessage, "");
    return true;
}

std::string LoopRolePermutations::Letters(
    const Permutation &pPermutation) {
    std::string aResult;
    aResult.reserve(kPermutationWidth);
    for (const std::uint8_t aValue : pPermutation) {
        if (aValue >= kPermutationWidth) {
            return "INVALID";
        }
        aResult.push_back(static_cast<char>('A' + aValue));
    }
    return aResult;
}
