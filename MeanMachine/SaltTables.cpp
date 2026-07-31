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

std::vector<SaltTables::Salt> gSaltTables;
bool gSaltTablesDidLoad = false;
std::size_t gSaltTableCursor = 0U;

constexpr std::size_t kSaltWordCount = 512U;
constexpr std::size_t kSaltByteCount = kSaltWordCount * sizeof(std::uint64_t);

static_assert(S_SALT == kSaltWordCount,
              "Salt_Farm records must match the runtime salt word count.");

bool IsRunningUnderXCTest() {
    return (std::getenv("XCTestConfigurationFilePath") != nullptr) ||
           (std::getenv("XCTestBundlePath") != nullptr);
}

std::uint64_t ReadU64LittleEndian(const std::uint8_t *pSource) {
    return static_cast<std::uint64_t>(pSource[0]) |
           (static_cast<std::uint64_t>(pSource[1]) << 8U) |
           (static_cast<std::uint64_t>(pSource[2]) << 16U) |
           (static_cast<std::uint64_t>(pSource[3]) << 24U) |
           (static_cast<std::uint64_t>(pSource[4]) << 32U) |
           (static_cast<std::uint64_t>(pSource[5]) << 40U) |
           (static_cast<std::uint64_t>(pSource[6]) << 48U) |
           (static_cast<std::uint64_t>(pSource[7]) << 56U);
}

} // namespace

const std::vector<SaltTables::Salt> &SaltTables::Get() {
    if (gSaltTablesDidLoad) {
        return gSaltTables;
    }

    if (IsRunningUnderXCTest()) {
        gSaltTablesDidLoad = true;
        std::printf("SaltTables loaded 0 salts (asset loading disabled under XCTest).\n");
        return gSaltTables;
    }

    const std::string aDirectory = FileIO::ProjectRoot("Assets/data_salt");
    const std::vector<std::string> aFilePaths = FileIO::GetAllFiles(aDirectory);

    for (const std::string &aFilePath : aFilePaths) {
        std::vector<std::uint8_t> aFileData;
        if (!FileIO::Load(aFilePath, aFileData)) {
            continue;
        }

        if ((aFileData.size() % kSaltByteCount) != 0U) {
            std::printf("SaltTables ignored malformed file %s: %zu bytes is not a multiple of %zu.\n",
                        aFilePath.c_str(),
                        aFileData.size(),
                        kSaltByteCount);
            continue;
        }

        for (std::size_t aOffset = 0U; aOffset < aFileData.size(); aOffset += kSaltByteCount) {
            Salt aSalt{};
            for (std::size_t aWordIndex = 0U; aWordIndex < aSalt.size(); ++aWordIndex) {
                aSalt[aWordIndex] = ReadU64LittleEndian(
                    aFileData.data() + aOffset + (aWordIndex * sizeof(std::uint64_t)));
            }
            gSaltTables.push_back(aSalt);
        }
    }

    Random::Shuffle(&gSaltTables);
    gSaltTableCursor = 0U;
    gSaltTablesDidLoad = true;
    std::printf("SaltTables loaded and shuffled %zu salts.\n",
                gSaltTables.size());
    return gSaltTables;
}

void SaltTables::InjectRandomDomains(GTwistExpander *pExpander) {
    if (pExpander == nullptr) {
        return;
    }

    const std::vector<Salt> &aLoadedTables = Get();
    std::vector<Salt> aUniqueTables;

    // Six domains use 13 tables for constants and 18 seed materials use
    // eight full salts each: 78 + 144 = 222 records per expander.
    constexpr std::size_t kTablesPerExpander = (6U * 13U) + (18U * 8U);
    aUniqueTables.reserve(kTablesPerExpander);
    if (!aLoadedTables.empty()) {
        for (std::size_t i = 0U; i < kTablesPerExpander; ++i) {
            if (gSaltTableCursor >= gSaltTables.size()) {
                Random::Shuffle(&gSaltTables);
                gSaltTableCursor = 0U;
                std::printf("SaltTables exhausted all %zu salts; reshuffled for reuse.\n",
                            gSaltTables.size());
            }
            aUniqueTables.push_back(gSaltTables[gSaltTableCursor]);
            gSaltTableCursor += 1U;
        }
    }


    if (aUniqueTables.empty()) {
        printf("salt table EMPTY?\n");
        return;
    }

    const Salt aFallbackTable = aUniqueTables.front();
    while (aUniqueTables.size() < 4U) {
        aUniqueTables.push_back(aFallbackTable);
    }

    auto FillDomainSalt = [&](std::uint64_t *pDest,
                              std::size_t pTableIndex) {
        if ((pDest == nullptr) || aUniqueTables.empty()) {
            return;
        }
        const Salt &aTable = aUniqueTables[pTableIndex % aUniqueTables.size()];
        std::memcpy(pDest,
                    aTable.data(),
                    sizeof(aTable));
    };

    auto FillDomainConstant = [&](std::size_t pTableIndex,
                                  std::uint64_t pTag) -> std::uint64_t {
        const Salt &aTable = aUniqueTables[pTableIndex % aUniqueTables.size()];
        std::uint64_t aValue = aTable[static_cast<std::size_t>(pTag) & static_cast<std::size_t>(S_SALT1)];
        if (aValue == 0ULL) {
            aValue = pTag | 1ULL;
        }
        return aValue;
    };
    
    auto FillDomainConstantByte = [&](std::size_t pTableIndex,
                                      std::uint64_t pTag) -> std::uint8_t {
        std::uint8_t aValue = static_cast<std::uint8_t>(FillDomainConstant(pTableIndex, pTag) & 0xFFU);
        if (aValue == 0U) {
            aValue = static_cast<std::uint8_t>((pTag & 0xFFU) | 1U);
        }
        return aValue;
    };

    auto FillSeedMaterial = [&](TwistDomainSeedRoundMaterial *pMaterial,
                                std::size_t pTableCursor) {
        if (pMaterial == nullptr) {
            return;
        }
        FillDomainSalt(pMaterial->mSaltA, pTableCursor + 0U);
        FillDomainSalt(pMaterial->mSaltB, pTableCursor + 1U);
        FillDomainSalt(pMaterial->mSaltC, pTableCursor + 2U);
        FillDomainSalt(pMaterial->mSaltD, pTableCursor + 3U);
        FillDomainSalt(pMaterial->mSaltE, pTableCursor + 4U);
        FillDomainSalt(pMaterial->mSaltF, pTableCursor + 5U);
        FillDomainSalt(pMaterial->mSaltG, pTableCursor + 6U);
        FillDomainSalt(pMaterial->mSaltH, pTableCursor + 7U);
    };

    auto FillDomainConstants = [&](TwistDomainConstants *pConstants,
                                   std::size_t pTableCursor,
                                   std::uint64_t pTagCursor) {
        if (pConstants == nullptr) {
            return;
        }
        pConstants->mIngress = FillDomainConstant(pTableCursor + 0U,
                                                  pTagCursor + 0ULL);
        pConstants->mScatter = FillDomainConstant(pTableCursor + 1U,
                                                  pTagCursor + 1ULL);
        pConstants->mCross = FillDomainConstant(pTableCursor + 2U,
                                                pTagCursor + 2ULL);
        pConstants->mMatrixSelectA = FillDomainConstant(pTableCursor + 3U,
                                                        pTagCursor + 3ULL);
        pConstants->mMatrixSelectB = FillDomainConstant(pTableCursor + 4U,
                                                        pTagCursor + 4ULL);
        pConstants->mMatrixUnrollA = FillDomainConstantByte(pTableCursor + 5U,
                                                            pTagCursor + 5ULL);
        pConstants->mMatrixUnrollB = FillDomainConstantByte(pTableCursor + 6U,
                                                            pTagCursor + 6ULL);
        pConstants->mMatrixArgA = FillDomainConstantByte(pTableCursor + 7U,
                                                          pTagCursor + 7ULL);
        pConstants->mMatrixArgB = FillDomainConstantByte(pTableCursor + 8U,
                                                          pTagCursor + 8ULL);
        pConstants->mMatrixArgC = FillDomainConstantByte(pTableCursor + 9U,
                                                          pTagCursor + 9ULL);
        pConstants->mMatrixArgD = FillDomainConstantByte(pTableCursor + 10U,
                                                          pTagCursor + 10ULL);
    };

    TwistDomainSeedRoundMaterial *aMaterials[] = {
        &pExpander->GetDomainBundleInbuilt()->mKeyRotateASalts.mWandererUpdate,
        &pExpander->GetDomainBundleInbuilt()->mKeyRotateASalts.mOrbiterAssign,
        &pExpander->GetDomainBundleInbuilt()->mKeyRotateASalts.mOrbiterUpdate,
        &pExpander->GetDomainBundleInbuilt()->mKeyRotateBSalts.mWandererUpdate,
        &pExpander->GetDomainBundleInbuilt()->mKeyRotateBSalts.mOrbiterAssign,
        &pExpander->GetDomainBundleInbuilt()->mKeyRotateBSalts.mOrbiterUpdate,
        &pExpander->GetDomainBundleInbuilt()->mKeySpawnASalts.mWandererUpdate,
        &pExpander->GetDomainBundleInbuilt()->mKeySpawnASalts.mOrbiterAssign,
        &pExpander->GetDomainBundleInbuilt()->mKeySpawnASalts.mOrbiterUpdate,
        &pExpander->GetDomainBundleInbuilt()->mKeySpawnBSalts.mWandererUpdate,
        &pExpander->GetDomainBundleInbuilt()->mKeySpawnBSalts.mOrbiterAssign,
        &pExpander->GetDomainBundleInbuilt()->mKeySpawnBSalts.mOrbiterUpdate,
        &pExpander->GetDomainBundleInbuilt()->mTwistSalts.mWandererUpdate,
        &pExpander->GetDomainBundleInbuilt()->mTwistSalts.mOrbiterAssign,
        &pExpander->GetDomainBundleInbuilt()->mTwistSalts.mOrbiterUpdate,
        &pExpander->GetDomainBundleInbuilt()->mSeedSalts.mWandererUpdate,
        &pExpander->GetDomainBundleInbuilt()->mSeedSalts.mOrbiterAssign,
        &pExpander->GetDomainBundleInbuilt()->mSeedSalts.mOrbiterUpdate
    };

    TwistDomainConstants *aConstants[] = {
        &pExpander->GetDomainBundleInbuilt()->mKeyRotateAConstants,
        &pExpander->GetDomainBundleInbuilt()->mKeyRotateBConstants,
        &pExpander->GetDomainBundleInbuilt()->mKeySpawnAConstants,
        &pExpander->GetDomainBundleInbuilt()->mKeySpawnBConstants,
        &pExpander->GetDomainBundleInbuilt()->mTwistConstants,
        &pExpander->GetDomainBundleInbuilt()->mSeedConstants
    };

    std::size_t aDomainTableCursor = 0U;
    std::uint64_t aDomainTag = 1ULL;
    for (TwistDomainConstants *aConstant : aConstants) {
        FillDomainConstants(aConstant,
                            aDomainTableCursor,
                            aDomainTag);
        aDomainTableCursor += 13U;
        aDomainTag += 13ULL;
    }

    for (TwistDomainSeedRoundMaterial *aMaterial : aMaterials) {
        FillSeedMaterial(aMaterial,
                         aDomainTableCursor);
        aDomainTableCursor += 8U;
    }
}
