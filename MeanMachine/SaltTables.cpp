//
//  SaltTables.cpp
//  MeanMachine
//
//  Created by John Snow on 4/27/26.
//

#include "SaltTables.hpp"

#include "GTwistExpander.hpp"
#include "TwistWorkSpace.hpp"
#include "FileIO.hpp"
#include "Random.hpp"

#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <vector>

namespace {

std::vector<std::vector<std::uint8_t>> gSaltTables;
bool gSaltTablesDidLoad = false;

bool IsRunningUnderXCTest() {
    return (std::getenv("XCTestConfigurationFilePath") != nullptr) ||
           (std::getenv("XCTestBundlePath") != nullptr);
}

void AppendIfUnique(std::vector<std::vector<std::uint8_t>> *pDest,
                    const std::vector<std::uint8_t> &pCandidate,
                    const std::size_t pExpectedLength) {
    if ((pDest == nullptr) || (pCandidate.size() != pExpectedLength)) {
        return;
    }
    for (const std::vector<std::uint8_t> &aExisting : *pDest) {
        if (aExisting == pCandidate) {
            return;
        }
    }
    pDest->push_back(pCandidate);
}

std::vector<std::uint8_t> BuildDefaultSalt(const std::uint8_t pSeed,
                                           const std::uint8_t pMultiplier,
                                           const std::uint8_t pXorBias) {
    std::vector<std::uint8_t> aResult;
    aResult.reserve(static_cast<std::size_t>(S_SALT));
    for (std::size_t i = 0U; i < static_cast<std::size_t>(S_SALT); ++i) {
        const std::uint8_t aIndex = static_cast<std::uint8_t>(i & 0xFFU);
        std::uint8_t aValue = static_cast<std::uint8_t>(pSeed + static_cast<std::uint8_t>(aIndex * pMultiplier));
        aValue = static_cast<std::uint8_t>(aValue ^ static_cast<std::uint8_t>((aIndex * 13U) + pXorBias));
        aValue = static_cast<std::uint8_t>(aValue + static_cast<std::uint8_t>((i >> 1U) & 0xFFU));
        aResult.push_back(aValue);
    }
    return aResult;
}

std::vector<std::uint64_t> ExpandSaltToWide(const std::vector<std::uint8_t> &pSource,
                                            const std::uint64_t pSeedA,
                                            const std::uint64_t pSeedB) {
    std::vector<std::uint64_t> aResult(static_cast<std::size_t>(S_SALT), 0ULL);
    if (pSource.empty()) {
        return aResult;
    }

    auto RotL64 = [](const std::uint64_t pValue, const std::uint32_t pShift) -> std::uint64_t {
        const std::uint32_t aShift = (pShift & 63U);
        if (aShift == 0U) {
            return pValue;
        }
        return (pValue << aShift) | (pValue >> (64U - aShift));
    };

    std::uint64_t aStateA = pSeedA ^ (static_cast<std::uint64_t>(pSource.size()) * 0x9E3779B185EBCA87ULL);
    std::uint64_t aStateB = pSeedB ^ 0xD6E8FEB86659FD93ULL;
    for (std::size_t i = 0U; i < pSource.size(); ++i) {
        const std::uint64_t aByte = static_cast<std::uint64_t>(pSource[i]);
        aStateA ^= (aByte + ((static_cast<std::uint64_t>(i) + 1ULL) * 0x100000001B3ULL));
        aStateA = RotL64(aStateA, static_cast<std::uint32_t>((11U + i) & 63U));
        aStateA *= 0x94D049BB133111EBULL;
        aStateB += (aByte ^ (static_cast<std::uint64_t>(i) * 0xA24BAED4963EE407ULL));
        aStateB = RotL64(aStateB, static_cast<std::uint32_t>((19U + (i * 3U)) & 63U));
        aStateB *= 0xC2B2AE3D27D4EB4FULL;
    }

    for (std::size_t i = 0U; i < static_cast<std::size_t>(S_SALT); ++i) {
        const std::size_t aIndexA = i % pSource.size();
        const std::size_t aIndexB = (i * 7U + 3U) % pSource.size();
        const std::size_t aIndexC = (i * 13U + 5U) % pSource.size();
        const std::uint64_t aPack =
            static_cast<std::uint64_t>(pSource[aIndexA]) |
            (static_cast<std::uint64_t>(pSource[aIndexB]) << 16U) |
            (static_cast<std::uint64_t>(pSource[aIndexC]) << 40U);

        aStateA ^= aPack + (static_cast<std::uint64_t>(i + 1U) * 0x9E3779B97F4A7C15ULL);
        aStateA = RotL64(aStateA, static_cast<std::uint32_t>((23U + i) & 63U));
        aStateB += RotL64(aStateA ^ aPack, static_cast<std::uint32_t>((31U + (i * 5U)) & 63U));
        aStateB *= 0xD6E8FEB86659FD93ULL;
        aStateB ^= (aStateB >> 29U);
        aResult[i] = aStateA ^ RotL64(aStateB, static_cast<std::uint32_t>((i * 9U) & 63U)) ^ (aPack * 0x9E3779B185EBCA87ULL);
    }

    return aResult;
}

} // namespace

std::vector<std::vector<std::uint8_t>> SaltTables::Get() {
    if (gSaltTablesDidLoad) {
        return gSaltTables;
    }

    if (IsRunningUnderXCTest()) {
        gSaltTablesDidLoad = true;
        return gSaltTables;
    }

    const std::string aDirectory = FileIO::ProjectRoot("Assets/data_salt");
    const std::vector<std::string> aFilePaths = FileIO::GetAllFiles(aDirectory);

    for (const std::string &aFilePath : aFilePaths) {
        std::vector<std::uint8_t> aFileData;
        if (!FileIO::Load(aFilePath, aFileData)) {
            continue;
        }

        for (std::size_t aOffset = 0U; (aOffset + static_cast<std::size_t>(S_SALT)) <= aFileData.size(); aOffset += static_cast<std::size_t>(S_SALT)) {
            std::vector<std::uint8_t> aTable(aFileData.begin() + static_cast<long>(aOffset),
                                             aFileData.begin() + static_cast<long>(aOffset + static_cast<std::size_t>(S_SALT)));
            gSaltTables.push_back(aTable);
        }
    }

    gSaltTablesDidLoad = true;
    return gSaltTables;
}

std::vector<std::uint8_t> SaltTables::GetDefaultA() {
    return BuildDefaultSalt(0x31U, 0x05U, 0xA7U);
}

std::vector<std::uint8_t> SaltTables::GetDefaultB() {
    return BuildDefaultSalt(0x5FU, 0x09U, 0x43U);
}

std::vector<std::uint8_t> SaltTables::GetDefaultC() {
    return BuildDefaultSalt(0x82U, 0x11U, 0x1DU);
}

std::vector<std::uint8_t> SaltTables::GetDefaultD() {
    return BuildDefaultSalt(0xC4U, 0x17U, 0x6BU);
}

void SaltTables::InjectRandomEight(GTwistExpander *pExpander) {
    if (pExpander == nullptr) {
        return;
    }

    std::vector<std::vector<std::uint8_t>> aUniqueTables;
    for (const std::vector<std::uint8_t> &aTable : Get()) {
        AppendIfUnique(&aUniqueTables, aTable, S_SALT);
    }

    if (aUniqueTables.size() < 8U) {
        AppendIfUnique(&aUniqueTables, GetDefaultA(), S_SALT);
    }
    if (aUniqueTables.size() < 8U) {
        AppendIfUnique(&aUniqueTables, GetDefaultB(), S_SALT);
    }
    if (aUniqueTables.size() < 8U) {
        AppendIfUnique(&aUniqueTables, GetDefaultC(), S_SALT);
    }
    if (aUniqueTables.size() < 8U) {
        AppendIfUnique(&aUniqueTables, GetDefaultD(), S_SALT);
    }
    if (aUniqueTables.size() < 8U) {
        AppendIfUnique(&aUniqueTables, GetDefaultA(), S_SALT);
    }
    if (aUniqueTables.size() < 8U) {
        AppendIfUnique(&aUniqueTables, GetDefaultB(), S_SALT);
    }
    if (aUniqueTables.size() < 8U) {
        AppendIfUnique(&aUniqueTables, GetDefaultC(), S_SALT);
    }
    if (aUniqueTables.size() < 8U) {
        AppendIfUnique(&aUniqueTables, GetDefaultD(), S_SALT);
    }

    if (aUniqueTables.empty()) {
        return;
    }

    Random::Shuffle(&aUniqueTables);
    const std::vector<std::uint8_t> aFallbackTable = aUniqueTables.front();
    while (aUniqueTables.size() < 8U) {
        aUniqueTables.push_back(aFallbackTable);
    }

    pExpander->_mSaltA = ExpandSaltToWide(aUniqueTables[0], 0x243F6A8885A308D3ULL, 0x13198A2E03707344ULL);
    pExpander->_mSaltB = ExpandSaltToWide(aUniqueTables[1], 0xA4093822299F31D0ULL, 0x082EFA98EC4E6C89ULL);
    pExpander->_mSaltC = ExpandSaltToWide(aUniqueTables[2], 0x452821E638D01377ULL, 0xBE5466CF34E90C6CULL);
    pExpander->_mSaltD = ExpandSaltToWide(aUniqueTables[3], 0xC0AC29B7C97C50DDULL, 0x3F84D5B5B5470917ULL);
    pExpander->_mSaltE = ExpandSaltToWide(aUniqueTables[4], 0x9216D5D98979FB1BULL, 0xD1310BA698DFB5ACULL);
    pExpander->_mSaltF = ExpandSaltToWide(aUniqueTables[5], 0x2FFD72DBD01ADFB7ULL, 0xB8E1AFED6A267E96ULL);
    pExpander->_mSaltG = ExpandSaltToWide(aUniqueTables[6], 0xBA7C9045F12C7F99ULL, 0x24A19947B3916CF7ULL);
    pExpander->_mSaltH = ExpandSaltToWide(aUniqueTables[7], 0x0801F2E2858EFC16ULL, 0x636920D871574E69ULL);

    auto FillDomainSalt = [&](std::uint64_t *pDest, std::size_t pTableIndex, std::uint64_t pTag) {
        if ((pDest == nullptr) || aUniqueTables.empty()) {
            return;
        }
        const std::vector<std::uint8_t> &aTable = aUniqueTables[pTableIndex % aUniqueTables.size()];
        const std::uint64_t aSeedA = 0x243F6A8885A308D3ULL ^ (pTag * 0x9E3779B185EBCA87ULL);
        const std::uint64_t aSeedB = 0x13198A2E03707344ULL ^ (pTag * 0xD6E8FEB86659FD93ULL);
        std::vector<std::uint64_t> aWide = ExpandSaltToWide(aTable, aSeedA, aSeedB);
        if (aWide.size() < static_cast<std::size_t>(S_SALT)) {
            aWide.resize(static_cast<std::size_t>(S_SALT), 0ULL);
        }
        std::memcpy(pDest, aWide.data(), sizeof(std::uint64_t) * static_cast<std::size_t>(S_SALT));
    };

    std::size_t aDomainTableCursor = 8U;
    std::uint64_t aDomainTag = 1ULL;

    FillDomainSalt(pExpander->mDomainSaltKeyBoxA, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltKeyBoxB, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltKeyBoxC, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltKeyBoxD, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltKeyBoxE, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltKeyBoxF, aDomainTableCursor++, aDomainTag++);

    FillDomainSalt(pExpander->mDomainSaltMaskBoxA, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltMaskBoxB, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltMaskBoxC, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltMaskBoxD, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltMaskBoxE, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltMaskBoxF, aDomainTableCursor++, aDomainTag++);

    FillDomainSalt(pExpander->mDomainSaltWandererA, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltWandererB, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltWandererC, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltWandererD, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltWandererE, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltWandererF, aDomainTableCursor++, aDomainTag++);

    FillDomainSalt(pExpander->mDomainSaltOrbiterA, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltOrbiterB, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltOrbiterC, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltOrbiterD, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltOrbiterE, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltOrbiterF, aDomainTableCursor++, aDomainTag++);

    FillDomainSalt(pExpander->mDomainSaltPrismA, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltPrismB, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltPrismC, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltPrismD, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltPrismE, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltPrismF, aDomainTableCursor++, aDomainTag++);

    FillDomainSalt(pExpander->mDomainSaltSourceA, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltSourceB, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltSourceC, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltSourceD, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltSourceE, aDomainTableCursor++, aDomainTag++);
    FillDomainSalt(pExpander->mDomainSaltSourceF, aDomainTableCursor++, aDomainTag++);
}

void SaltTables::InjectRandomFour(GTwistExpander *pExpander) {
    InjectRandomEight(pExpander);
}
