//
//  Scanner_MagicNumbers.cpp
//  MeanMachine
//
//  Created by icarus black on 7/9/26.
//

#include "Scanner_MagicNumbers.hpp"

#include <cstdio>
#include <set>
#include <unordered_map>

#include "Library - G/GMagicNumbers.hpp"

namespace {

struct MagicNumberLocation {
    std::size_t mPackIndex = 0U;
    std::size_t mPairIndex = 0U;
    const char *mRole = "";
};

void PrintLocation(const MagicNumberLocation &pLocation) {
    std::printf("pack %zu, pair %zu, %s",
                pLocation.mPackIndex,
                pLocation.mPairIndex,
                pLocation.mRole);
}

void PrintNumber(const std::uint64_t pNumber) {
    std::printf("0x%016llX", static_cast<unsigned long long>(pNumber));
}

void CheckNumber(const std::uint64_t pNumber,
                 const MagicNumberLocation &pLocation,
                 std::unordered_map<std::uint64_t, MagicNumberLocation> *pFirstGlobalLocation,
                 std::unordered_map<std::uint64_t, MagicNumberLocation> *pFirstLocalLocation,
                 std::set<std::size_t> *pDeletePackIndices,
                 int *pDuplicateCount) {
    auto aLocalIt = pFirstLocalLocation->find(pNumber);
    if (aLocalIt != pFirstLocalLocation->end()) {
        std::printf("duplicate number inside hot pack: ");
        PrintNumber(pNumber);
        std::printf(" first at ");
        PrintLocation(aLocalIt->second);
        std::printf(", later at ");
        PrintLocation(pLocation);
        std::printf(" -> delete pack %zu\n", pLocation.mPackIndex);
        pDeletePackIndices->insert(pLocation.mPackIndex);
        *pDuplicateCount += 1;
    } else {
        (*pFirstLocalLocation)[pNumber] = pLocation;
    }

    auto aGlobalIt = pFirstGlobalLocation->find(pNumber);
    if (aGlobalIt != pFirstGlobalLocation->end()) {
        if (aGlobalIt->second.mPackIndex != pLocation.mPackIndex) {
            std::printf("duplicate number across hot packs: ");
            PrintNumber(pNumber);
            std::printf(" first at ");
            PrintLocation(aGlobalIt->second);
            std::printf(", later at ");
            PrintLocation(pLocation);
            std::printf(" -> delete pack %zu\n", pLocation.mPackIndex);
            pDeletePackIndices->insert(pLocation.mPackIndex);
            *pDuplicateCount += 1;
        }
    } else {
        (*pFirstGlobalLocation)[pNumber] = pLocation;
    }
}

} // namespace

bool Scanner_MagicNumbers::Check() {
    std::unordered_map<std::uint64_t, MagicNumberLocation> aFirstGlobalLocation;
    std::set<std::size_t> aDeletePackIndices;
    int aDuplicateCount = 0;

    for (std::size_t aPackIndex = 0U; aPackIndex < GHotPacks::sPack.size(); ++aPackIndex) {
        const GHotPack &aPack = GHotPacks::sPack[aPackIndex];
        std::unordered_map<std::uint64_t, MagicNumberLocation> aFirstLocalLocation;

        for (std::size_t aPairIndex = 0U; aPairIndex < aPack.mPair.size(); ++aPairIndex) {
            const GHotPair &aPair = aPack.mPair[aPairIndex];

            CheckNumber(aPair.mAdd,
                        MagicNumberLocation{ aPackIndex, aPairIndex, "add" },
                        &aFirstGlobalLocation,
                        &aFirstLocalLocation,
                        &aDeletePackIndices,
                        &aDuplicateCount);

            CheckNumber(aPair.mMul,
                        MagicNumberLocation{ aPackIndex, aPairIndex, "mul" },
                        &aFirstGlobalLocation,
                        &aFirstLocalLocation,
                        &aDeletePackIndices,
                        &aDuplicateCount);
        }
    }

    std::printf("Scanner_MagicNumbers::Check scanned %zu hot packs.\n",
                GHotPacks::sPack.size());
    if (aDeletePackIndices.empty()) {
        std::printf("No duplicate hot-pack numbers found.\n");
        return true;
    }

    std::printf("Found %d duplicate number hits. Delete later hot-pack indices:",
                aDuplicateCount);
    for (const std::size_t aPackIndex : aDeletePackIndices) {
        std::printf(" %zu", aPackIndex);
    }
    std::printf("\n");
    return false;
}
