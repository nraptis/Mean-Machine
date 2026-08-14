//
//  LoopRecipeFarmer.cpp
//  MeanMachine
//

#include "LoopRecipeFarmer.hpp"

#include "FileIO.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <filesystem>
#include <numeric>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

namespace {

constexpr std::array<std::uint8_t, 8U> kFileMagic = {
    'M', 'M', 'R', 'E', 'C', 'P', '1', '1',
};
constexpr std::uint32_t kFileVersion = 1U;
constexpr std::size_t kCoreByteCount =
    LoopHeadFarmer::kRoleCount * 3U;
constexpr std::size_t kHeadByteCount =
    LoopHeadFarmer::kRoleCount;
constexpr std::size_t kTailByteCount =
    LoopHeadFarmer::kRoleCount * 2U;
constexpr std::size_t kRecipeByteCount =
    kCoreByteCount + kHeadByteCount + kTailByteCount;
constexpr std::size_t kHeaderByteCount = 48U;

using RecipeBuckets = std::array<
    std::vector<LoopRecipe11>, LoopHeadFarmer::kCoreCount>;
using ExpanderRecipes = std::array<
    std::vector<LoopRecipe11>, LoopRecipeFarmer::kExpanderCount>;

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

std::string ResolvedPath(const std::string &pPath) {
    const std::filesystem::path aPath(pPath);
    return aPath.is_absolute()
        ? aPath.lexically_normal().generic_string()
        : FileIO::ProjectRoot(pPath);
}

std::string RecipePath(const std::string &pFolderPath,
                       const std::size_t pExpanderIndex) {
    char aFileName[64];
    std::snprintf(aFileName,
                  sizeof(aFileName),
                  "expander_loop_%02zu.bin",
                  pExpanderIndex);
    return FileIO::Join(ResolvedPath(pFolderPath), aFileName);
}

void Append32(std::vector<std::uint8_t> *pBytes,
              const std::uint32_t pValue) {
    for (unsigned i = 0U; i < 4U; ++i) {
        pBytes->push_back(static_cast<std::uint8_t>(
            pValue >> (i * 8U)));
    }
}

void Append64(std::vector<std::uint8_t> *pBytes,
              const std::uint64_t pValue) {
    for (unsigned i = 0U; i < 8U; ++i) {
        pBytes->push_back(static_cast<std::uint8_t>(
            pValue >> (i * 8U)));
    }
}

bool Read32(const std::vector<std::uint8_t> &pBytes,
            std::size_t *pOffset,
            std::uint32_t *pValue) {
    if ((*pOffset + 4U) > pBytes.size()) {
        return false;
    }
    *pValue = 0U;
    for (unsigned i = 0U; i < 4U; ++i) {
        *pValue |= static_cast<std::uint32_t>(
            pBytes[*pOffset + i]) << (i * 8U);
    }
    *pOffset += 4U;
    return true;
}

bool Read64(const std::vector<std::uint8_t> &pBytes,
            std::size_t *pOffset,
            std::uint64_t *pValue) {
    if ((*pOffset + 8U) > pBytes.size()) {
        return false;
    }
    *pValue = 0ULL;
    for (unsigned i = 0U; i < 8U; ++i) {
        *pValue |= static_cast<std::uint64_t>(
            pBytes[*pOffset + i]) << (i * 8U);
    }
    *pOffset += 8U;
    return true;
}

void AppendRecipe(std::vector<std::uint8_t> *pBytes,
                  const LoopRecipe11 &pRecipe) {
    for (const auto &aRound : pRecipe.mCore.mRounds) {
        pBytes->insert(pBytes->end(), aRound.begin(), aRound.end());
    }
    pBytes->insert(
        pBytes->end(),
        pRecipe.mHead.mWandererForOrbiter.begin(),
        pRecipe.mHead.mWandererForOrbiter.end());
    pBytes->insert(
        pBytes->end(),
        pRecipe.mTail.mOrbiterAForWanderer.begin(),
        pRecipe.mTail.mOrbiterAForWanderer.end());
    pBytes->insert(
        pBytes->end(),
        pRecipe.mTail.mOrbiterBForWanderer.begin(),
        pRecipe.mTail.mOrbiterBForWanderer.end());
}

bool ReadRecipe(const std::vector<std::uint8_t> &pBytes,
                std::size_t *pOffset,
                LoopRecipe11 *pRecipe) {
    if ((*pOffset + kRecipeByteCount) > pBytes.size()) {
        return false;
    }
    *pRecipe = {};
    for (auto &aRound : pRecipe->mCore.mRounds) {
        for (std::uint8_t &aRole : aRound) {
            aRole = pBytes[(*pOffset)++];
        }
    }
    for (std::uint8_t &aWanderer :
         pRecipe->mHead.mWandererForOrbiter) {
        aWanderer = pBytes[(*pOffset)++];
    }
    pRecipe->mHead.mPermutationRank =
        LoopHeadFarmer::Rank(pRecipe->mHead);
    for (std::uint8_t &aOrbiter :
         pRecipe->mTail.mOrbiterAForWanderer) {
        aOrbiter = pBytes[(*pOffset)++];
    }
    for (std::uint8_t &aOrbiter :
         pRecipe->mTail.mOrbiterBForWanderer) {
        aOrbiter = pBytes[(*pOffset)++];
    }
    return LoopNewFarmer::RecipeIsValid(
        pRecipe->mCore, pRecipe->mHead, pRecipe->mTail);
}

std::string RecipeKey(const LoopRecipe11 &pRecipe) {
    std::string aKey;
    aKey.reserve(kRecipeByteCount);
    for (const auto &aRound : pRecipe.mCore.mRounds) {
        for (const std::uint8_t aRole : aRound) {
            aKey.push_back(static_cast<char>(aRole));
        }
    }
    for (const std::uint8_t aWanderer :
         pRecipe.mHead.mWandererForOrbiter) {
        aKey.push_back(static_cast<char>(aWanderer));
    }
    for (const std::uint8_t aOrbiter :
         pRecipe.mTail.mOrbiterAForWanderer) {
        aKey.push_back(static_cast<char>(aOrbiter));
    }
    for (const std::uint8_t aOrbiter :
         pRecipe.mTail.mOrbiterBForWanderer) {
        aKey.push_back(static_cast<char>(aOrbiter));
    }
    return aKey;
}

bool SaveExpanderRecipes(const std::string &pOutputFolderPath,
                         const std::size_t pExpanderIndex,
                         const std::uint64_t pShuffleSeed,
                         const std::vector<LoopRecipe11> &pRecipes,
                         std::string *pErrorMessage) {
    if (pRecipes.size() != LoopRecipeFarmer::kRecipesPerExpander) {
        SetError(pErrorMessage,
                 "Loop recipe expander did not receive exactly 600 recipes");
        return false;
    }

    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kHeaderByteCount +
                   (pRecipes.size() * kRecipeByteCount));
    aBytes.insert(aBytes.end(), kFileMagic.begin(), kFileMagic.end());
    Append32(&aBytes, kFileVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopHeadFarmer::kRoleCount));
    Append32(&aBytes, static_cast<std::uint32_t>(pExpanderIndex));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopRecipeFarmer::kExpanderCount));
    Append32(&aBytes, static_cast<std::uint32_t>(pRecipes.size()));
    Append32(&aBytes, static_cast<std::uint32_t>(kRecipeByteCount));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopHeadFarmer::kCoreCount));
    Append32(&aBytes, static_cast<std::uint32_t>(
        LoopHeadFarmer::kPatternsPerCore));
    Append64(&aBytes, pShuffleSeed);
    for (const LoopRecipe11 &aRecipe : pRecipes) {
        AppendRecipe(&aBytes, aRecipe);
    }

    const std::string aPath = RecipePath(
        pOutputFolderPath, pExpanderIndex);
    if (!FileIO::Save(aPath, aBytes)) {
        SetError(pErrorMessage,
                 "Loop recipe farmer could not save " + aPath);
        return false;
    }
    return true;
}

} // namespace

bool LoopRecipeFarmer::Build(
    const std::string &pCorePatternPath,
    const std::string &pHeadPatternPath,
    const std::string &pTailPatternPath,
    const std::string &pOutputFolderPath,
    const std::uint64_t pShuffleSeed,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");

    LoopNewPatternFile11 aPatterns;
    if (!LoopNewFarmer::Load(pCorePatternPath,
                             pHeadPatternPath,
                             pTailPatternPath,
                             &aPatterns,
                             pErrorMessage)) {
        return false;
    }

    RecipeBuckets aBuckets;
    for (std::size_t aCoreIndex = 0U;
         aCoreIndex < aPatterns.mHearts.size();
         ++aCoreIndex) {
        const LoopNewHeart11 &aHeart = aPatterns.mHearts[aCoreIndex];
        std::vector<LoopRecipe11> &aBucket = aBuckets[aCoreIndex];
        aBucket.reserve(LoopHeadFarmer::kPatternsPerCore);
        for (const LoopNewHead11 &aHead : aHeart.mHeads) {
            LoopRecipe11 aRecipe;
            aRecipe.mCore = aHeart.mHeart;
            aRecipe.mHead = aHead.mHead;
            aRecipe.mTail = aHead.mTail;
            aBucket.push_back(std::move(aRecipe));
        }
    }

    std::mt19937_64 aGenerator(pShuffleSeed);
    for (std::vector<LoopRecipe11> &aBucket : aBuckets) {
        std::shuffle(aBucket.begin(), aBucket.end(), aGenerator);
    }
    std::array<std::size_t, LoopHeadFarmer::kCoreCount> aBucketOrder{};
    std::iota(aBucketOrder.begin(), aBucketOrder.end(), 0U);
    std::shuffle(aBucketOrder.begin(), aBucketOrder.end(), aGenerator);

    ExpanderRecipes aExpanderRecipes;
    for (auto &aRecipes : aExpanderRecipes) {
        aRecipes.reserve(kRecipesPerExpander);
    }
    std::size_t aExpanderIndex = 0U;
    for (const std::size_t aBucketIndex : aBucketOrder) {
        for (const LoopRecipe11 &aRecipe : aBuckets[aBucketIndex]) {
            aExpanderRecipes[aExpanderIndex].push_back(aRecipe);
            aExpanderIndex = (aExpanderIndex + 1U) % kExpanderCount;
        }
    }
    if (aExpanderIndex != 0U) {
        SetError(pErrorMessage,
                 "Loop recipe round-robin did not end on an expander boundary");
        return false;
    }

    for (std::size_t i = 0U; i < aExpanderRecipes.size(); ++i) {
        if (!SaveExpanderRecipes(pOutputFolderPath,
                                 i,
                                 pShuffleSeed,
                                 aExpanderRecipes[i],
                                 pErrorMessage)) {
            return false;
        }
    }

    std::array<std::vector<LoopRecipe11>, kExpanderCount> aVerification;
    if (!LoadAll(pOutputFolderPath, &aVerification, pErrorMessage)) {
        return false;
    }
    std::printf("Loop recipe Phase IV wrote %zu recipes as %zu files x "
                "%zu recipes; seed=0x%016llX; output=%s\n",
                LoopHeadFarmer::kRetainedPatternCount,
                kExpanderCount,
                kRecipesPerExpander,
                static_cast<unsigned long long>(pShuffleSeed),
                ResolvedPath(pOutputFolderPath).c_str());
    return true;
}

bool LoopRecipeFarmer::Load(
    const std::string &pRecipeFolderPath,
    const std::size_t pExpanderIndex,
    std::vector<LoopRecipe11> *pRecipes,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if ((pRecipes == nullptr) || (pExpanderIndex >= kExpanderCount)) {
        SetError(pErrorMessage,
                 "Loop recipe load received an invalid destination or expander index");
        return false;
    }

    const std::string aPath = RecipePath(
        pRecipeFolderPath, pExpanderIndex);
    std::vector<std::uint8_t> aBytes;
    const std::size_t aExpectedByteCount =
        kHeaderByteCount + (kRecipesPerExpander * kRecipeByteCount);
    if (!FileIO::Load(aPath, aBytes) ||
        (aBytes.size() != aExpectedByteCount) ||
        !std::equal(kFileMagic.begin(), kFileMagic.end(), aBytes.begin())) {
        SetError(pErrorMessage,
                 "Loop recipe file had an invalid size or header: " + aPath);
        return false;
    }

    std::size_t aOffset = kFileMagic.size();
    std::uint32_t aVersion = 0U;
    std::uint32_t aRoleCount = 0U;
    std::uint32_t aSavedExpanderIndex = 0U;
    std::uint32_t aExpanderCount = 0U;
    std::uint32_t aRecipeCount = 0U;
    std::uint32_t aRecipeByteCount = 0U;
    std::uint32_t aCoreCount = 0U;
    std::uint32_t aRecipesPerCore = 0U;
    std::uint64_t aShuffleSeed = 0ULL;
    if (!Read32(aBytes, &aOffset, &aVersion) ||
        !Read32(aBytes, &aOffset, &aRoleCount) ||
        !Read32(aBytes, &aOffset, &aSavedExpanderIndex) ||
        !Read32(aBytes, &aOffset, &aExpanderCount) ||
        !Read32(aBytes, &aOffset, &aRecipeCount) ||
        !Read32(aBytes, &aOffset, &aRecipeByteCount) ||
        !Read32(aBytes, &aOffset, &aCoreCount) ||
        !Read32(aBytes, &aOffset, &aRecipesPerCore) ||
        !Read64(aBytes, &aOffset, &aShuffleSeed) ||
        (aVersion != kFileVersion) ||
        (aRoleCount != LoopHeadFarmer::kRoleCount) ||
        (aSavedExpanderIndex != pExpanderIndex) ||
        (aExpanderCount != kExpanderCount) ||
        (aRecipeCount != kRecipesPerExpander) ||
        (aRecipeByteCount != kRecipeByteCount) ||
        (aCoreCount != LoopHeadFarmer::kCoreCount) ||
        (aRecipesPerCore != LoopHeadFarmer::kPatternsPerCore)) {
        SetError(pErrorMessage,
                 "Loop recipe file had incompatible metadata: " + aPath);
        return false;
    }

    pRecipes->clear();
    pRecipes->reserve(kRecipesPerExpander);
    for (std::size_t i = 0U; i < kRecipesPerExpander; ++i) {
        LoopRecipe11 aRecipe;
        if (!ReadRecipe(aBytes, &aOffset, &aRecipe)) {
            SetError(pErrorMessage,
                     "Loop recipe file contained an invalid recipe: " + aPath);
            return false;
        }
        pRecipes->push_back(std::move(aRecipe));
    }
    if (aOffset != aBytes.size()) {
        SetError(pErrorMessage,
                 "Loop recipe file did not end on its record boundary: " +
                 aPath);
        return false;
    }
    return true;
}

bool LoopRecipeFarmer::LoadAll(
    const std::string &pRecipeFolderPath,
    std::array<std::vector<LoopRecipe11>, kExpanderCount> *pRecipes,
    std::string *pErrorMessage) {
    SetError(pErrorMessage, "");
    if (pRecipes == nullptr) {
        SetError(pErrorMessage,
                 "Loop recipe load-all destination was null");
        return false;
    }

    std::unordered_set<std::string> aKeys;
    aKeys.reserve(LoopHeadFarmer::kRetainedPatternCount * 2U);
    std::size_t aTotalCount = 0U;
    for (std::size_t i = 0U; i < kExpanderCount; ++i) {
        if (!Load(pRecipeFolderPath,
                  i,
                  &(*pRecipes)[i],
                  pErrorMessage)) {
            return false;
        }
        for (const LoopRecipe11 &aRecipe : (*pRecipes)[i]) {
            if (!aKeys.insert(RecipeKey(aRecipe)).second) {
                SetError(pErrorMessage,
                         "Loop recipe files contained a duplicate recipe");
                return false;
            }
            ++aTotalCount;
        }
    }
    if (aTotalCount != LoopHeadFarmer::kRetainedPatternCount) {
        SetError(pErrorMessage,
                 "Loop recipe files did not contain exactly 19,800 recipes");
        return false;
    }
    std::printf("Loaded loop recipes: %zu expanders x %zu recipes = %zu\n",
                kExpanderCount,
                kRecipesPerExpander,
                aTotalCount);
    return true;
}
