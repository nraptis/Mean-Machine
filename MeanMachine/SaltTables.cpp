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

    std::uint64_t aUnwindA = pSeedA ^ (static_cast<std::uint64_t>(pSource.size()) * 0x9E3779B185EBCA87ULL);
    std::uint64_t aUnwindB = pSeedB ^ 0xD6E8FEB86659FD93ULL;
    for (std::size_t i = 0U; i < pSource.size(); ++i) {
        const std::uint64_t aByte = static_cast<std::uint64_t>(pSource[i]);
        aUnwindA ^= (aByte + ((static_cast<std::uint64_t>(i) + 1ULL) * 0x100000001B3ULL));
        aUnwindA = RotL64(aUnwindA, static_cast<std::uint32_t>((11U + i) & 63U));
        aUnwindA *= 0x94D049BB133111EBULL;
        aUnwindB += (aByte ^ (static_cast<std::uint64_t>(i) * 0xA24BAED4963EE407ULL));
        aUnwindB = RotL64(aUnwindB, static_cast<std::uint32_t>((19U + (i * 3U)) & 63U));
        aUnwindB *= 0xC2B2AE3D27D4EB4FULL;
    }

    for (std::size_t i = 0U; i < static_cast<std::size_t>(S_SALT); ++i) {
        const std::size_t aIndexA = i % pSource.size();
        const std::size_t aIndexB = (i * 7U + 3U) % pSource.size();
        const std::size_t aIndexC = (i * 13U + 5U) % pSource.size();
        const std::uint64_t aPack =
            static_cast<std::uint64_t>(pSource[aIndexA]) |
            (static_cast<std::uint64_t>(pSource[aIndexB]) << 16U) |
            (static_cast<std::uint64_t>(pSource[aIndexC]) << 40U);

        aUnwindA ^= aPack + (static_cast<std::uint64_t>(i + 1U) * 0x9E3779B97F4A7C15ULL);
        aUnwindA = RotL64(aUnwindA, static_cast<std::uint32_t>((23U + i) & 63U));
        aUnwindB += RotL64(aUnwindA ^ aPack, static_cast<std::uint32_t>((31U + (i * 5U)) & 63U));
        aUnwindB *= 0xD6E8FEB86659FD93ULL;
        aUnwindB ^= (aUnwindB >> 29U);
        aResult[i] = aUnwindA ^ RotL64(aUnwindB, static_cast<std::uint32_t>((i * 9U) & 63U)) ^ (aPack * 0x9E3779B185EBCA87ULL);
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

    auto FillDomainSalt = [&](std::uint64_t *pDest,
                              std::size_t pTableIndex,
                              std::uint64_t pTag) {
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
        std::memcpy(pDest,
                    aWide.data(),
                    sizeof(std::uint64_t) * static_cast<std::size_t>(S_SALT));
    };

    auto FillDomainConstant = [&](std::size_t pTableIndex,
                                  std::uint64_t pTag) -> std::uint64_t {
        const std::vector<std::uint8_t> &aTable = aUniqueTables[pTableIndex % aUniqueTables.size()];
        const std::uint64_t aSeedA = 0x9E3779B97F4A7C15ULL ^ (pTag * 0xA24BAED4963EE407ULL);
        const std::uint64_t aSeedB = 0xD6E8FEB86659FD93ULL ^ (pTag * 0x94D049BB133111EBULL);
        const std::vector<std::uint64_t> aWide = ExpandSaltToWide(aTable, aSeedA, aSeedB);
        if (aWide.empty()) {
            return 0ULL;
        }
        return aWide[static_cast<std::size_t>(pTag) & static_cast<std::size_t>(S_SALT1)];
    };

    auto FillSeedMaterial = [&](TwistDomainSeedRoundMaterial *pMaterial,
                                std::size_t pTableCursor,
                                std::uint64_t pTagCursor) {
        if (pMaterial == nullptr) {
            return;
        }
        FillDomainSalt(pMaterial->mSaltA, pTableCursor + 0U, pTagCursor + 0ULL);
        FillDomainSalt(pMaterial->mSaltB, pTableCursor + 1U, pTagCursor + 1ULL);
        FillDomainSalt(pMaterial->mSaltC, pTableCursor + 2U, pTagCursor + 2ULL);
        FillDomainSalt(pMaterial->mSaltD, pTableCursor + 3U, pTagCursor + 3ULL);
        FillDomainSalt(pMaterial->mSaltE, pTableCursor + 4U, pTagCursor + 4ULL);
        FillDomainSalt(pMaterial->mSaltF, pTableCursor + 5U, pTagCursor + 5ULL);
    };

    auto FillDomainConstants = [&](TwistDomainConstants *pConstants,
                                   std::size_t pTableCursor,
                                   std::uint64_t pTagCursor) {
        if (pConstants == nullptr) {
            return;
        }
        pConstants->mDomainConstantPublicIngress = FillDomainConstant(pTableCursor + 0U,
                                                                      pTagCursor + 0ULL);
        pConstants->mDomainConstantPrivateIngress = FillDomainConstant(pTableCursor + 1U,
                                                                       pTagCursor + 1ULL);
        pConstants->mDomainConstantCrossIngress = FillDomainConstant(pTableCursor + 2U,
                                                                     pTagCursor + 2ULL);
    };

    TwistDomainSeedRoundMaterial *aMaterials[] = {
        &pExpander->mDomainBundleInbuilt.mKeyASalts.mUnwind,
        &pExpander->mDomainBundleInbuilt.mKeyASalts.mOrbiter,
        &pExpander->mDomainBundleInbuilt.mKeyASalts.mOrbiterInit,
        &pExpander->mDomainBundleInbuilt.mKeyBSalts.mUnwind,
        &pExpander->mDomainBundleInbuilt.mKeyBSalts.mOrbiter,
        &pExpander->mDomainBundleInbuilt.mKeyBSalts.mOrbiterInit,
        &pExpander->mDomainBundleInbuilt.mMaskASalts.mUnwind,
        &pExpander->mDomainBundleInbuilt.mMaskASalts.mOrbiter,
        &pExpander->mDomainBundleInbuilt.mMaskASalts.mOrbiterInit,
        &pExpander->mDomainBundleInbuilt.mMaskBSalts.mUnwind,
        &pExpander->mDomainBundleInbuilt.mMaskBSalts.mOrbiter,
        &pExpander->mDomainBundleInbuilt.mMaskBSalts.mOrbiterInit,
        &pExpander->mDomainBundleInbuilt.mWorkLaneSalts.mUnwind,
        &pExpander->mDomainBundleInbuilt.mWorkLaneSalts.mOrbiter,
        &pExpander->mDomainBundleInbuilt.mWorkLaneSalts.mOrbiterInit,
        &pExpander->mDomainBundleInbuilt.mMaskLaneSalts.mUnwind,
        &pExpander->mDomainBundleInbuilt.mMaskLaneSalts.mOrbiter,
        &pExpander->mDomainBundleInbuilt.mMaskLaneSalts.mOrbiterInit,
        &pExpander->mDomainBundleInbuilt.mOperationLaneSalts.mUnwind,
        &pExpander->mDomainBundleInbuilt.mOperationLaneSalts.mOrbiter,
        &pExpander->mDomainBundleInbuilt.mOperationLaneSalts.mOrbiterInit
    };

    TwistDomainConstants *aConstants[] = {
        &pExpander->mDomainBundleInbuilt.mKeyAConstants,
        &pExpander->mDomainBundleInbuilt.mKeyBConstants,
        &pExpander->mDomainBundleInbuilt.mMaskAConstants,
        &pExpander->mDomainBundleInbuilt.mMaskBConstants,
        &pExpander->mDomainBundleInbuilt.mWorkLaneConstants,
        &pExpander->mDomainBundleInbuilt.mMaskLaneConstants,
        &pExpander->mDomainBundleInbuilt.mOperationLaneConstants
    };

    std::size_t aDomainTableCursor = 8U;
    std::uint64_t aDomainTag = 1ULL;
    for (TwistDomainConstants *aConstant : aConstants) {
        FillDomainConstants(aConstant,
                            aDomainTableCursor,
                            aDomainTag);
        aDomainTableCursor += 3U;
        aDomainTag += 3ULL;
    }

    for (TwistDomainSeedRoundMaterial *aMaterial : aMaterials) {
        FillSeedMaterial(aMaterial,
                         aDomainTableCursor,
                         aDomainTag);
        aDomainTableCursor += 6U;
        aDomainTag += 6ULL;
    }
}

void SaltTables::InjectRandomFour(GTwistExpander *pExpander) {
    InjectRandomEight(pExpander);
}
