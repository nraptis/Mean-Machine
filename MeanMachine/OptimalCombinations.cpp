//
//  OptimalCombinations.cpp
//  MeanMachine
//

#include "OptimalCombinations.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "FileIO.hpp"
#include "Random.hpp"

namespace {

constexpr int kMaxWidth = 11;

struct Candidate {
    std::array<std::uint8_t, kMaxWidth>          mOrder{};
    std::array<std::uint8_t, kMaxWidth>          mPosition{};
    std::uint16_t                                mMinScore = 0U;
    bool                                        mChosen = false;
};

std::vector<std::uint64_t> Factorials(const int pWidth) {
    std::vector<std::uint64_t> aFactorials(static_cast<std::size_t>(pWidth + 1), 1ULL);
    for (int aIndex = 1; aIndex <= pWidth; ++aIndex) {
        aFactorials[static_cast<std::size_t>(aIndex)] =
            aFactorials[static_cast<std::size_t>(aIndex - 1)] * static_cast<std::uint64_t>(aIndex);
    }
    return aFactorials;
}

std::array<std::uint8_t, kMaxWidth> IdentityOrder(const int pWidth) {
    std::array<std::uint8_t, kMaxWidth> aOrder{};
    for (int aIndex = 0; aIndex < pWidth; ++aIndex) {
        aOrder[static_cast<std::size_t>(aIndex)] = static_cast<std::uint8_t>(aIndex);
    }
    return aOrder;
}

std::array<std::uint8_t, kMaxWidth> PositionsForOrder(const std::array<std::uint8_t, kMaxWidth> &pOrder,
                                                      const int pWidth) {
    std::array<std::uint8_t, kMaxWidth> aPositions{};
    for (int aIndex = 0; aIndex < pWidth; ++aIndex) {
        aPositions[static_cast<std::size_t>(pOrder[static_cast<std::size_t>(aIndex)])] =
            static_cast<std::uint8_t>(aIndex);
    }
    return aPositions;
}

std::array<std::uint8_t, kMaxWidth> UnrankPermutation(std::uint64_t pRank,
                                                      const int pWidth,
                                                      const std::vector<std::uint64_t> &pFactorials) {
    std::array<std::uint8_t, kMaxWidth> aOrder{};
    std::vector<std::uint8_t> aDigits;
    aDigits.reserve(static_cast<std::size_t>(pWidth));
    for (int aIndex = 0; aIndex < pWidth; ++aIndex) {
        aDigits.push_back(static_cast<std::uint8_t>(aIndex));
    }
    
    for (int aIndex = 0; aIndex < pWidth; ++aIndex) {
        const std::uint64_t aFactorial =
            pFactorials[static_cast<std::size_t>(pWidth - 1 - aIndex)];
        const std::size_t aDigitIndex =
            static_cast<std::size_t>(pRank / aFactorial);
        pRank %= aFactorial;
        
        aOrder[static_cast<std::size_t>(aIndex)] = aDigits[aDigitIndex];
        aDigits.erase(aDigits.begin() + static_cast<std::ptrdiff_t>(aDigitIndex));
    }
    
    return aOrder;
}

std::uint16_t DistanceScore(const std::array<std::uint8_t, kMaxWidth> &pPositionA,
                            const std::array<std::uint8_t, kMaxWidth> &pPositionB,
                            const int pWidth) {
    int aScore = 0;
    for (int aDigit = 0; aDigit < pWidth; ++aDigit) {
        const int aPosA = static_cast<int>(pPositionA[static_cast<std::size_t>(aDigit)]);
        const int aPosB = static_cast<int>(pPositionB[static_cast<std::size_t>(aDigit)]);
        const int aDelta = std::abs(aPosA - aPosB);
        aScore += std::min(aDelta, pWidth - aDelta);
    }
    return static_cast<std::uint16_t>(aScore);
}

Candidate MakeCandidate(const std::array<std::uint8_t, kMaxWidth> &pOrder,
                        const int pWidth,
                        const std::array<std::uint8_t, kMaxWidth> &pIdentityPositions) {
    Candidate aCandidate;
    aCandidate.mOrder = pOrder;
    aCandidate.mPosition = PositionsForOrder(pOrder, pWidth);
    aCandidate.mMinScore = DistanceScore(aCandidate.mPosition, pIdentityPositions, pWidth);
    return aCandidate;
}

bool SamePrefixOrder(const std::array<std::uint8_t, kMaxWidth> &pA,
                     const std::array<std::uint8_t, kMaxWidth> &pB,
                     const int pWidth) {
    for (int aIndex = 0; aIndex < pWidth; ++aIndex) {
        if (pA[static_cast<std::size_t>(aIndex)] != pB[static_cast<std::size_t>(aIndex)]) {
            return false;
        }
    }
    return true;
}

bool BuildCandidatePool(const int pWidth,
                        const std::size_t pNeededCount,
                        const std::size_t pCandidateLimit,
                        std::vector<Candidate> *pCandidates,
                        std::string *pErrorMessage) {
    if (pCandidates == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "OptimalCombinations got null candidate pool";
        }
        return false;
    }
    if ((pWidth <= 1) || (pWidth > kMaxWidth)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "OptimalCombinations got unsupported width";
        }
        return false;
    }
    
    pCandidates->clear();
    
    const std::vector<std::uint64_t> aFactorials = Factorials(pWidth);
    const std::uint64_t aTotalPermutationCount = aFactorials[static_cast<std::size_t>(pWidth)];
    if (aTotalPermutationCount <= 1ULL) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "OptimalCombinations got no usable permutations";
        }
        return false;
    }
    
    const std::array<std::uint8_t, kMaxWidth> aIdentityOrder = IdentityOrder(pWidth);
    const std::array<std::uint8_t, kMaxWidth> aIdentityPositions =
        PositionsForOrder(aIdentityOrder, pWidth);
    
    const std::uint64_t aUsablePermutationCount = aTotalPermutationCount - 1ULL;
    const bool aUseAllPermutations =
        (pCandidateLimit == 0U) ||
        (static_cast<std::uint64_t>(pCandidateLimit) >= aUsablePermutationCount);
    const std::size_t aCandidateCount =
        aUseAllPermutations ?
        static_cast<std::size_t>(aUsablePermutationCount) :
        std::max(pNeededCount, pCandidateLimit);
    
    pCandidates->reserve(aCandidateCount);
    
    if (aUseAllPermutations) {
        std::array<std::uint8_t, kMaxWidth> aOrder = aIdentityOrder;
        std::size_t aProcessedCount = 0U;
        while (std::next_permutation(aOrder.begin(),
                                     aOrder.begin() + static_cast<std::ptrdiff_t>(pWidth))) {
            pCandidates->push_back(MakeCandidate(aOrder, pWidth, aIdentityPositions));
            aProcessedCount += 1U;
            if ((aProcessedCount % 200000U) == 0U) {
                std::printf("OptimalCombinations kN%d: processed %zu / %llu permutations\n",
                            pWidth,
                            aProcessedCount,
                            static_cast<unsigned long long>(aUsablePermutationCount));
                std::fflush(stdout);
            }
        }
        return true;
    }
    
    std::unordered_set<std::uint64_t> aRanks;
    aRanks.reserve(aCandidateCount * 2U);
    
    while (pCandidates->size() < aCandidateCount) {
        const std::uint64_t aRank = Random::Get64(aTotalPermutationCount);
        if (aRank == 0ULL) {
            continue;
        }
        if (!aRanks.insert(aRank).second) {
            continue;
        }
        
        const std::array<std::uint8_t, kMaxWidth> aOrder =
            UnrankPermutation(aRank, pWidth, aFactorials);
        if (SamePrefixOrder(aOrder, aIdentityOrder, pWidth)) {
            continue;
        }
        pCandidates->push_back(MakeCandidate(aOrder, pWidth, aIdentityPositions));
    }
    
    return true;
}

bool SelectCombinations(const OptimalCombinations::Job &pJob,
                        std::vector<Candidate> *pSelected,
                        std::string *pErrorMessage) {
    if (pSelected == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "OptimalCombinations got null selected list";
        }
        return false;
    }
    pSelected->clear();
    
    std::vector<Candidate> aCandidates;
    if (!BuildCandidatePool(pJob.mWidth,
                            pJob.mNeededCount,
                            pJob.mCandidateLimit,
                            &aCandidates,
                            pErrorMessage)) {
        return false;
    }
    
    if (aCandidates.size() < pJob.mNeededCount) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "OptimalCombinations candidate pool was smaller than needed count";
        }
        return false;
    }
    
    pSelected->reserve(pJob.mNeededCount);
    
    std::printf("OptimalCombinations kN%d: pool=%zu, target=%zu, seeded with identity.\n",
                pJob.mWidth,
                aCandidates.size(),
                pJob.mNeededCount);
    
    while (pSelected->size() < pJob.mNeededCount) {
        std::uint16_t aBestScore = 0U;
        std::size_t aBestIndex = static_cast<std::size_t>(-1);
        std::size_t aTieCount = 0U;
        
        for (std::size_t aIndex = 0U; aIndex < aCandidates.size(); ++aIndex) {
            const Candidate &aCandidate = aCandidates[aIndex];
            if (aCandidate.mChosen) {
                continue;
            }
            if ((aBestIndex == static_cast<std::size_t>(-1)) ||
                (aCandidate.mMinScore > aBestScore)) {
                aBestScore = aCandidate.mMinScore;
                aBestIndex = aIndex;
                aTieCount = 1U;
            } else if (aCandidate.mMinScore == aBestScore) {
                aTieCount += 1U;
                if (Random::Get(static_cast<int>(aTieCount)) == 0) {
                    aBestIndex = aIndex;
                }
            }
        }
        
        if (aBestIndex == static_cast<std::size_t>(-1)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "OptimalCombinations ran out of candidates";
            }
            return false;
        }
        
        Candidate &aSelected = aCandidates[aBestIndex];
        aSelected.mChosen = true;
        pSelected->push_back(aSelected);
        
        const Candidate &aJustSelected = pSelected->back();
        for (Candidate &aCandidate: aCandidates) {
            if (aCandidate.mChosen || (aCandidate.mMinScore == 0U)) {
                continue;
            }
            const std::uint16_t aDistance =
                DistanceScore(aCandidate.mPosition, aJustSelected.mPosition, pJob.mWidth);
            if (aDistance < aCandidate.mMinScore) {
                aCandidate.mMinScore = aDistance;
            }
        }
        
        if ((pSelected->size() % 64U) == 0U || (pSelected->size() == pJob.mNeededCount)) {
            std::printf("OptimalCombinations kN%d: %zu / %zu, best distance=%u, ties=%zu\n",
                        pJob.mWidth,
                        pSelected->size(),
                        pJob.mNeededCount,
                        static_cast<unsigned int>(aBestScore),
                        aTieCount);
        }
    }
    
    return true;
}

std::string HeaderGuardForFileName(const char *pFileName) {
    std::string aGuard = pFileName == nullptr ? "Combinations_hpp" : pFileName;
    for (char &aChar: aGuard) {
        if (((aChar >= 'a') && (aChar <= 'z')) ||
            ((aChar >= 'A') && (aChar <= 'Z')) ||
            ((aChar >= '0') && (aChar <= '9'))) {
            if ((aChar >= 'a') && (aChar <= 'z')) {
                aChar = static_cast<char>(aChar - ('a' - 'A'));
            }
            continue;
        }
        aChar = '_';
    }
    return aGuard;
}

std::string EmitHeader(const OptimalCombinations::Job &pJob,
                       const std::vector<Candidate> &pSelected) {
    const std::string aGuard = HeaderGuardForFileName(pJob.mFileName);
    
    std::ostringstream aStream;
    aStream << "//\n";
    aStream << "//  " << pJob.mFileName << "\n";
    aStream << "//  Generated by OptimalCombinations.\n";
    aStream << "//\n\n";
    aStream << "#ifndef " << aGuard << "\n";
    aStream << "#define " << aGuard << "\n\n";
    aStream << "#include <cstdint>\n\n";
    aStream << "static constexpr int " << pJob.mArrayName << "_Width = " << pJob.mWidth << ";\n";
    aStream << "static constexpr int " << pJob.mArrayName << "_Count = "
            << pSelected.size() << ";\n";
    aStream << "static const std::uint8_t " << pJob.mArrayName << "["
            << pSelected.size() << "][" << pJob.mWidth << "] = {\n";
    
    for (const Candidate &aCandidate: pSelected) {
        aStream << "    {";
        for (int aIndex = 0; aIndex < pJob.mWidth; ++aIndex) {
            if (aIndex > 0) {
                aStream << ", ";
            }
            aStream << static_cast<unsigned int>(aCandidate.mOrder[static_cast<std::size_t>(aIndex)]) << "U";
        }
        aStream << "}, // difference score: "
                << static_cast<unsigned int>(aCandidate.mMinScore)
                << "\n";
    }
    
    aStream << "};\n\n";
    aStream << "#endif /* " << aGuard << " */\n";
    return aStream.str();
}

bool SaveTextProjectRoot(const char *pFileName,
                         const std::string &pText,
                         std::string *pErrorMessage) {
    const std::string aPath = FileIO::ProjectRoot(FileIO::Join("MeanMachine", pFileName));
    std::vector<std::uint8_t> aBytes(pText.begin(), pText.end());
    if (!FileIO::Save(aPath, aBytes)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "OptimalCombinations failed to save: " + aPath;
        }
        return false;
    }
    std::printf("OptimalCombinations wrote %s\n", aPath.c_str());
    return true;
}

} // namespace

bool OptimalCombinations::BuildProjectRoot(std::string *pErrorMessage) {
    const Job aJobs[] = {
        //{7, 50U * 33U, 0U, "Combinations07.hpp", "kCombinations07"},
        //{9, 60U * 33U, 0U, "Combinations09.hpp", "kCombinations09"},
        {11, 40U * 33U, 0U, "Combinations11.hpp", "kCombinations11"},
    };
    
    return BuildProjectRoot(aJobs,
                            sizeof(aJobs) / sizeof(aJobs[0]),
                            pErrorMessage);
}

bool OptimalCombinations::BuildProjectRoot(const Job *pJobs,
                                           std::size_t pJobCount,
                                           std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    
    if ((pJobs == nullptr) || (pJobCount == 0U)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "OptimalCombinations got no jobs";
        }
        return false;
    }
    
    for (std::size_t aJobIndex = 0U; aJobIndex < pJobCount; ++aJobIndex) {
        const Job &aJob = pJobs[aJobIndex];
        std::vector<Candidate> aSelected;
        if (!SelectCombinations(aJob, &aSelected, pErrorMessage)) {
            return false;
        }
        
        const std::string aHeader = EmitHeader(aJob, aSelected);
        if (!SaveTextProjectRoot(aJob.mFileName, aHeader, pErrorMessage)) {
            return false;
        }
    }
    
    return true;
}
