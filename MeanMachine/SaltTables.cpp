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

constexpr std::size_t kSaltWordCount = 32U;
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

SaltTables::Salt BuildDefaultSalt(const std::uint8_t pSeed,
                                  const std::uint8_t pMultiplier,
                                  const std::uint8_t pXorBias) {
    SaltTables::Salt aResult{};
    std::array<std::uint8_t, kSaltByteCount> aBytes{};
    for (std::size_t i = 0U; i < aBytes.size(); ++i) {
        const std::uint8_t aIndex = static_cast<std::uint8_t>(i & 0xFFU);
        std::uint8_t aValue = static_cast<std::uint8_t>(pSeed + static_cast<std::uint8_t>(aIndex * pMultiplier));
        aValue = static_cast<std::uint8_t>(aValue ^ static_cast<std::uint8_t>((aIndex * 13U) + pXorBias));
        aValue = static_cast<std::uint8_t>(aValue + static_cast<std::uint8_t>((i >> 1U) & 0xFFU));
        aBytes[i] = aValue;
    }
    for (std::size_t i = 0U; i < aResult.size(); ++i) {
        aResult[i] = ReadU64LittleEndian(aBytes.data() + (i * sizeof(std::uint64_t)));
    }
    return aResult;
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

void SaltTables::InjectRandomEight(GTwistExpander *pExpander) {
    if (pExpander == nullptr) {
        return;
    }

    const std::vector<Salt> &aLoadedTables = Get();
    std::vector<Salt> aUniqueTables;

    // Eight domains use 13 tables for constants and 24 seed materials use
    // six full salts each: 104 + 144 = 248 records per expander.
    constexpr std::size_t kTablesPerExpander = (8U * 13U) + (24U * 6U);
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
    while (aUniqueTables.size() < 8U) {
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
        pConstants->mIngress = pConstants->mDomainConstantPublicIngress;
        pConstants->mScatter = pConstants->mDomainConstantPrivateIngress;
        pConstants->mCross = pConstants->mDomainConstantCrossIngress;
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
        pConstants->mMaskMutateA = FillDomainConstantByte(pTableCursor + 11U,
                                                          pTagCursor + 11ULL);
        pConstants->mMaskMutateB = FillDomainConstantByte(pTableCursor + 12U,
                                                          pTagCursor + 12ULL);
    };

    TwistDomainSeedRoundMaterial *aMaterials[] = {
        &pExpander->mDomainBundleInbuilt.mPhaseASalts.mWandererUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseASalts.mOrbiterAssign,
        &pExpander->mDomainBundleInbuilt.mPhaseASalts.mOrbiterUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseBSalts.mWandererUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseBSalts.mOrbiterAssign,
        &pExpander->mDomainBundleInbuilt.mPhaseBSalts.mOrbiterUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseCSalts.mWandererUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseCSalts.mOrbiterAssign,
        &pExpander->mDomainBundleInbuilt.mPhaseCSalts.mOrbiterUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseDSalts.mWandererUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseDSalts.mOrbiterAssign,
        &pExpander->mDomainBundleInbuilt.mPhaseDSalts.mOrbiterUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseESalts.mWandererUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseESalts.mOrbiterAssign,
        &pExpander->mDomainBundleInbuilt.mPhaseESalts.mOrbiterUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseFSalts.mWandererUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseFSalts.mOrbiterAssign,
        &pExpander->mDomainBundleInbuilt.mPhaseFSalts.mOrbiterUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseGSalts.mWandererUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseGSalts.mOrbiterAssign,
        &pExpander->mDomainBundleInbuilt.mPhaseGSalts.mOrbiterUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseHSalts.mWandererUpdate,
        &pExpander->mDomainBundleInbuilt.mPhaseHSalts.mOrbiterAssign,
        &pExpander->mDomainBundleInbuilt.mPhaseHSalts.mOrbiterUpdate
    };

    TwistDomainConstants *aConstants[] = {
        &pExpander->mDomainBundleInbuilt.mPhaseAConstants,
        &pExpander->mDomainBundleInbuilt.mPhaseBConstants,
        &pExpander->mDomainBundleInbuilt.mPhaseCConstants,
        &pExpander->mDomainBundleInbuilt.mPhaseDConstants,
        &pExpander->mDomainBundleInbuilt.mPhaseEConstants,
        &pExpander->mDomainBundleInbuilt.mPhaseFConstants,
        &pExpander->mDomainBundleInbuilt.mPhaseGConstants,
        &pExpander->mDomainBundleInbuilt.mPhaseHConstants
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
        aDomainTableCursor += 6U;
    }
}
