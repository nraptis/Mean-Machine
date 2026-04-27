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

void SaltTables::InjectRandomFour(GTwistExpander *pExpander) {
    if (pExpander == nullptr) {
        return;
    }

    std::vector<std::vector<std::uint8_t>> aUniqueTables;
    for (const std::vector<std::uint8_t> &aTable : Get()) {
        AppendIfUnique(&aUniqueTables, aTable, S_SALT);
    }

    if (aUniqueTables.size() < 4U) {
        AppendIfUnique(&aUniqueTables, GetDefaultA(), S_SALT);
    }
    if (aUniqueTables.size() < 4U) {
        AppendIfUnique(&aUniqueTables, GetDefaultB(), S_SALT);
    }
    if (aUniqueTables.size() < 4U) {
        AppendIfUnique(&aUniqueTables, GetDefaultC(), S_SALT);
    }
    if (aUniqueTables.size() < 4U) {
        AppendIfUnique(&aUniqueTables, GetDefaultD(), S_SALT);
    }

    if (aUniqueTables.empty()) {
        return;
    }

    Random::Shuffle(&aUniqueTables);
    const std::vector<std::uint8_t> aFallbackTable = aUniqueTables.front();
    while (aUniqueTables.size() < 4U) {
        aUniqueTables.push_back(aFallbackTable);
    }

    pExpander->_mSaltA = aUniqueTables[0];
    pExpander->_mSaltB = aUniqueTables[1];
    pExpander->_mSaltC = aUniqueTables[2];
    pExpander->_mSaltD = aUniqueTables[3];
}
