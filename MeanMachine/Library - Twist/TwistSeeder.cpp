//
//  TwistSeeder.cpp
//  Gorgon
//
//  Created by Sonic The Hedge Whore on 4/9/26.
//

#include "TwistSeeder.hpp"
#include "SBoxTables.hpp"
#include "TwistSeedBuilder.hpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace {

void FillIdentity(std::uint8_t *pDest,
                  const std::size_t pLength) {
    for (std::size_t aIndex = 0U; aIndex < pLength; ++aIndex) {
        pDest[aIndex] = static_cast<std::uint8_t>(aIndex & 0xFFU);
    }
}

void CopyBytes(std::uint8_t *pDest,
               const std::uint8_t *pSource,
               const std::size_t pLength) {
    if ((pDest == NULL) || (pSource == NULL) || (pLength == 0U)) {
        return;
    }
    std::memcpy(pDest, pSource, pLength);
}

void CopyVectorBytes(std::uint8_t *pDest,
                     const std::vector<std::uint8_t> &pSource,
                     const std::size_t pLength) {
    if (pDest == NULL || pLength == 0U || pSource.empty()) {
        return;
    }
    const std::size_t aCopyLength = std::min(pLength, pSource.size());
    CopyBytes(pDest, pSource.data(), aCopyLength);
}

void LoadDefaultSBoxes(std::uint8_t *pA,
                       std::uint8_t *pB,
                       std::uint8_t *pC,
                       std::uint8_t *pD) {
    FillIdentity(pA, S_SBOX);
    FillIdentity(pB, S_SBOX);
    FillIdentity(pC, S_SBOX);
    FillIdentity(pD, S_SBOX);

    std::vector<std::vector<std::uint8_t>> aBoxes = SBoxTables::Get();
    
    if (aBoxes.size() > 0U && (aBoxes)[0].size() >= S_SBOX) {
        CopyBytes(pA, (aBoxes)[0].data(), S_SBOX);
    }
    if (aBoxes.size() > 1U && (aBoxes)[1].size() >= S_SBOX) {
        CopyBytes(pB, (aBoxes)[1].data(), S_SBOX);
    } else {
        CopyBytes(pB, pA, S_SBOX);
    }
    if (aBoxes.size() > 2U && (aBoxes)[2].size() >= S_SBOX) {
        CopyBytes(pC, (aBoxes)[2].data(), S_SBOX);
    } else {
        CopyBytes(pC, pA, S_SBOX);
    }
    if (aBoxes.size() > 3U && (aBoxes)[3].size() >= S_SBOX) {
        CopyBytes(pD, (aBoxes)[3].data(), S_SBOX);
    } else {
        CopyBytes(pD, pA, S_SBOX);
    }
}

void LoadDefaultSalts(std::uint8_t *pA,
                      std::uint8_t *pB,
                      std::uint8_t *pC,
                      std::uint8_t *pD) {
    std::fill(pA, pA + S_SALT, 0U);
    std::fill(pB, pB + S_SALT, 0U);
    std::fill(pC, pC + S_SALT, 0U);
    std::fill(pD, pD + S_SALT, 0U);

    const std::vector<std::uint8_t> aSaltA = SBoxTables::GetSaltA();
    const std::vector<std::uint8_t> aSaltB = SBoxTables::GetSaltB();
    const std::vector<std::uint8_t> aSaltC = SBoxTables::GetSaltC();
    const std::vector<std::uint8_t> aSaltD = SBoxTables::GetSaltD();

    CopyVectorBytes(pA, aSaltA, S_SALT);
    CopyVectorBytes(pB, aSaltB.empty() ? aSaltA : aSaltB, S_SALT);
    CopyVectorBytes(pC, aSaltC.empty() ? aSaltA : aSaltC, S_SALT);
    CopyVectorBytes(pD, aSaltD.empty() ? aSaltB : aSaltD, S_SALT);
}

void CopySeederTablesToWorkspace(const TwistSeeder *pSeeder,
                                 TwistWorkSpace *pWorkspace) {
    CopyBytes(pWorkspace->mSBoxA, pSeeder->mSBoxA, S_SBOX);
    CopyBytes(pWorkspace->mSBoxB, pSeeder->mSBoxB, S_SBOX);
    CopyBytes(pWorkspace->mSBoxC, pSeeder->mSBoxC, S_SBOX);
    CopyBytes(pWorkspace->mSBoxD, pSeeder->mSBoxD, S_SBOX);

    CopyBytes(pWorkspace->mSaltA, pSeeder->mSaltA, S_SALT);
    CopyBytes(pWorkspace->mSaltB, pSeeder->mSaltB, S_SALT);
    CopyBytes(pWorkspace->mSaltC, pSeeder->mSaltC, S_SALT);
    CopyBytes(pWorkspace->mSaltD, pSeeder->mSaltD, S_SALT);
}

} // namespace

TwistSeeder::TwistSeeder() {
    mWorkspace = NULL;
    mSeedBatch = TwistSeedBuilder::BuildBaselineBatch();
    LoadDefaultSBoxes(mSBoxA, mSBoxB, mSBoxC, mSBoxD);
    LoadDefaultSalts(mSaltA, mSaltB, mSaltC, mSaltD);
}

TwistSeeder::~TwistSeeder() {
    
}

void TwistSeeder::Seed(TwistWorkSpace *pWorkspace, std::uint8_t *pSource) {
    mWorkspace = pWorkspace;
    if (mWorkspace == NULL) {
        std::printf("fatal: TwistSeeder::Seed requires a workspace.\n");
        std::exit(0);
    }
    mWorkspace->mSource = pSource;

    CopySeederTablesToWorkspace(this, mWorkspace);

    std::string aError;
    if (!mSeedBatch.Execute(mWorkspace, &aError)) {
        std::printf("fatal: TwistSeeder batch execution failed: %s\n", aError.c_str());
        std::exit(0);
    }
}

void TwistSeeder::SetSeedBatch(const GBatch &pBatch) {
    mSeedBatch = pBatch;
}

const GBatch& TwistSeeder::GetSeedBatch() const {
    return mSeedBatch;
}

std::string TwistSeeder::GetPrettyPrint() const {
    return mSeedBatch.ToPrettyString();
}

std::string TwistSeeder::GetJson(std::string *pError) const {
    return mSeedBatch.ToJson(pError);
}

std::string TwistSeeder::GetCpp(const std::string &pFunctionName,
                                std::string *pError) const {
    return mSeedBatch.BuildCpp(pFunctionName, pError);
}
