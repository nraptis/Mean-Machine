//
//  TwistExpander.cpp
//  MeanMachine
//

#include "TwistExpander.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistMix64.hpp"

#include <cstdio>
#include <cstring>

namespace {

inline std::uint64_t Mix64(std::uint64_t pValue) {
    pValue ^= (pValue >> 30U);
    pValue *= 0xBF58476D1CE4E5B9ULL;
    pValue ^= (pValue >> 27U);
    pValue *= 0x94D049BB133111EBULL;
    pValue ^= (pValue >> 31U);
    return pValue;
}

} // namespace

TwistExpander::TwistExpander() {
    mWorkspace = nullptr;
    mFarmSalt = nullptr;
    mSource = nullptr;
    mDest = nullptr;
    mKDFCallCounter = 0ULL;
    mKDFSessionNonce = 0ULL;
    mActiveConstants = nullptr;
    mActiveSaltSet = nullptr;
    std::memset(&mDomainBundleInbuilt, 0, sizeof(mDomainBundleInbuilt));
    std::memset(&mDomainBundleEphemeral, 0, sizeof(mDomainBundleEphemeral));
    std::memset(mIndexList256A, 0, sizeof(mIndexList256A));
    std::memset(mIndexList256B, 0, sizeof(mIndexList256B));
    std::memset(mIndexList256C, 0, sizeof(mIndexList256C));
    std::memset(mIndexList256D, 0, sizeof(mIndexList256D));
}

TwistExpander::~TwistExpander() {
    
}

void TwistExpander::KDF(std::uint64_t pNonce,
                        TwistDomainConstants *pDomainConstants,
                        TwistDomainSaltSet *pDomainSaltSet) {
    if ((pDomainConstants == nullptr) ||
        (pDomainSaltSet == nullptr)) {
        return;
    }

    mKDFSessionNonce = pNonce;
    mActiveConstants = pDomainConstants;
    mActiveSaltSet = pDomainSaltSet;
}

void TwistExpander::KDF_A(std::uint64_t pNonce,
                          TwistDomainConstants *pDomainConstants,
                          TwistDomainSaltSet *pDomainSaltSet,
                          std::uint8_t *pSnow,
                          int pIndexKDF) {
    (void)pSnow;
    (void)pIndexKDF;
    TwistExpander::KDF(pNonce,
                       pDomainConstants,
                       pDomainSaltSet);
}

void TwistExpander::KDF_B(std::uint64_t pNonce,
                          TwistDomainConstants *pDomainConstants,
                          TwistDomainSaltSet *pDomainSaltSet,
                          int pIndexKDF) {
    (void)pIndexKDF;
    TwistExpander::KDF(pNonce,
                       pDomainConstants,
                       pDomainSaltSet);
}

void TwistExpander::Seed(TwistWorkSpace *pWorkSpace,
                         TwistFarmSalt *pFarmSalt,
                         std::uint64_t pNonce,
                         std::uint8_t *pPassword,
                         std::size_t pPasswordByteLength,
                         std::uint8_t *pDestination) {
    if (pWorkSpace == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires workspace\n");
        return;
    }
    if (pDestination == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires destination buffer\n");
        return;
    }
    if (pFarmSalt == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires farm salt WorkLane\n");
        return;
    }

    mWorkspace = pWorkSpace;
    mFarmSalt = pFarmSalt;
    mSource = pWorkSpace->mSource;
    mDest = pDestination;
    UnrollPasswordToSource(pWorkSpace->mSource, pPassword, pPasswordByteLength);
    mKDFCallCounter = 0ULL;
    mKDFSessionNonce = Mix64(pNonce);
    mDomainBundleEphemeral.Zero();
    pWorkSpace->mDomainBundle.Zero();
}

void TwistExpander::TwistBlock(TwistWorkSpace *pWorkSpace,
                               std::uint8_t *pSource,
                               std::uint8_t *pDestination) {
    if ((pWorkSpace == nullptr) || (pSource == nullptr) || (pDestination == nullptr)) {
        return;
    }

    mWorkspace = pWorkSpace;
    mSource = pSource;
    mDest = pDestination;
}

void TwistExpander::SquashInvestToKeyBoxes() {
    if (mWorkspace == nullptr) {
        return;
    }

    std::uint8_t *aInvestLaneA = mWorkspace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = mWorkspace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = mWorkspace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = mWorkspace->mInvestLaneD;
    std::uint8_t *aInvestLaneE = mWorkspace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = mWorkspace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = mWorkspace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = mWorkspace->mInvestLaneH;

    std::uint8_t *aKeyBoxA = &(mWorkspace->mKeyBoxA[0][0]);
    for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_KEY); aIndex += 1U) {
        std::uint64_t aKeyIngress =
            (static_cast<std::uint64_t>(aInvestLaneA[aIndex]) << 0U) |
            (static_cast<std::uint64_t>(aInvestLaneD[aIndex]) << 8U) |
            (static_cast<std::uint64_t>(aInvestLaneC[aIndex]) << 16U) |
            (static_cast<std::uint64_t>(aInvestLaneB[aIndex]) << 24U) |
            (static_cast<std::uint64_t>(aInvestLaneE[aIndex]) << 32U) |
            (static_cast<std::uint64_t>(aInvestLaneH[aIndex]) << 40U) |
            (static_cast<std::uint64_t>(aInvestLaneF[aIndex]) << 48U) |
            (static_cast<std::uint64_t>(aInvestLaneG[aIndex]) << 56U);
        aKeyBoxA[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aKeyIngress));
    }

    std::uint8_t *aKeyBoxB = &(mWorkspace->mKeyBoxB[0][0]);
    for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_KEY); aIndex += 1U) {
        std::uint64_t aKeyIngress =
            (static_cast<std::uint64_t>(aInvestLaneH[aIndex]) << 0U) |
            (static_cast<std::uint64_t>(aInvestLaneE[aIndex]) << 8U) |
            (static_cast<std::uint64_t>(aInvestLaneG[aIndex]) << 16U) |
            (static_cast<std::uint64_t>(aInvestLaneF[aIndex]) << 24U) |
            (static_cast<std::uint64_t>(aInvestLaneD[aIndex]) << 32U) |
            (static_cast<std::uint64_t>(aInvestLaneA[aIndex]) << 40U) |
            (static_cast<std::uint64_t>(aInvestLaneC[aIndex]) << 48U) |
            (static_cast<std::uint64_t>(aInvestLaneB[aIndex]) << 56U);
        aKeyBoxB[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aKeyIngress));
    }
}

void TwistExpander::GrowKeyA(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace != nullptr) {
        mWorkspace = pWorkSpace;
    }
}

void TwistExpander::GrowKeyB(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace != nullptr) {
        mWorkspace = pWorkSpace;
    }
}

TwistFarmSalt *TwistExpander::GetFarmSalt() const {
    return mFarmSalt;
}

std::uint64_t TwistExpander::GetSessionNonce() const {
    return mKDFSessionNonce;
}

void TwistExpander::Twist(TwistWorkSpace *pWorkSpace,
                          std::uint8_t *pSource,
                          std::uint8_t *pDestination,
                          std::size_t pDestinationByteLength) {
    if ((pWorkSpace == nullptr) || (pSource == nullptr) || (pDestination == nullptr)) {
        std::printf("fatal: TwistExpander::Twist requires workspace/source/destination\n");
        return;
    }
    if ((pDestinationByteLength % S_BLOCK) != 0U) {
        std::printf("fatal: TwistExpander::Twist needs a multiple of S_BLOCK\n");
        return;
    }
    
    mWorkspace = pWorkSpace;
    mSource = pSource;
    mDest = pDestination;

    for (std::size_t aStartByte = 0U;
         aStartByte < pDestinationByteLength;
         aStartByte += static_cast<std::size_t>(S_BLOCK)) {
        TwistBlock(pWorkSpace,
                   pSource + aStartByte,
                   pDestination + aStartByte);
    }
    
}

void TwistExpander::AutoSeedThenTwist(TwistWorkSpace *pWorkSpace,
                                      TwistFarmSalt *pFarmSalt,
                                      std::uint64_t pNonce,
                                      std::uint8_t *pPassword,
                                      std::size_t pPasswordByteLength,
                                      std::uint8_t *pDestination,
                                      std::size_t pDestinationByteLength) {
    
    if ((pDestinationByteLength % S_BLOCK) != 0U) {
        std::printf("fatal: TwistExpander::AutoSeedThenTwist needs pDestinationByteLength as a multiple of S_BLOCK\n");
        return;
    }
    
    Seed(pWorkSpace,
         pFarmSalt,
         pNonce,
         pPassword, // password
         pPasswordByteLength, // password length
         pDestination);
    
    std::size_t aDestinationIndex = S_BLOCK;
    while (aDestinationIndex < pDestinationByteLength) {
        TwistBlock(pWorkSpace,
                   &pDestination[aDestinationIndex - S_BLOCK], // source
                   &pDestination[aDestinationIndex]); // dest
        aDestinationIndex += S_BLOCK;
    }
    
}

// Assumes the work space is seeded...
void TwistExpander::AutoTwist(TwistWorkSpace *pWorkSpace,
                              std::uint8_t *pSource,
                              std::uint8_t *pDestination,
                              std::size_t pDestinationByteLength) {
    
    TwistBlock(pWorkSpace,
               pSource,
               pDestination); // dest
    
    std::size_t aDestinationIndex = S_BLOCK;
    while (aDestinationIndex < pDestinationByteLength) {
        TwistBlock(pWorkSpace,
                   &pDestination[aDestinationIndex - S_BLOCK], // source
                   &pDestination[aDestinationIndex]); // dest
        aDestinationIndex += S_BLOCK;
    }
    
}

void TwistExpander::UnrollPasswordToSource(std::uint8_t *pSource,
                            std::uint8_t *pPassword,
                            std::size_t pPasswordByteLength) {
    if (pSource == nullptr) {
        return;
    }

    std::memset(pSource, 0, static_cast<std::size_t>(S_BLOCK));
    if ((pPassword == nullptr) || (pPasswordByteLength == 0U)) {
        return;
    }

    std::size_t aInitialCopy = pPasswordByteLength;
    if (aInitialCopy > static_cast<std::size_t>(S_BLOCK)) {
        aInitialCopy = static_cast<std::size_t>(S_BLOCK);
    }

    std::memcpy(pSource, pPassword, static_cast<std::size_t>(aInitialCopy));
    if (aInitialCopy < static_cast<std::size_t>(S_BLOCK)) {
        pSource[aInitialCopy++] = 0;
    }
    if (aInitialCopy < static_cast<std::size_t>(S_BLOCK)) {
        pSource[aInitialCopy++] = 0;
    }

    std::size_t aFilled = aInitialCopy;
    while (aFilled < static_cast<std::size_t>(S_BLOCK)) {
        std::size_t aChunk = aFilled;
        if ((aFilled + aChunk) > static_cast<std::size_t>(S_BLOCK)) {
            aChunk = static_cast<std::size_t>(S_BLOCK) - aFilled;
        }
        std::memcpy(pSource + aFilled, pSource, static_cast<std::size_t>(aChunk));
        aFilled += aChunk;
    }
}

void TwistExpander::UnrollPasswordToSource(std::uint8_t *pSource,
                                           std::uint8_t *pPassword,
                                           std::size_t pPasswordByteLength,
                                           std::size_t pSourceByteLength) {
    if (pSource == nullptr) {
        return;
    }

    if (pSourceByteLength == 0U) {
        return;
    }

    std::memset(pSource, 0, static_cast<std::size_t>(pSourceByteLength));

    if ((pPassword == nullptr) || (pPasswordByteLength == 0U)) {
        return;
    }

    std::size_t aInitialCopy = pPasswordByteLength;
    if (aInitialCopy > pSourceByteLength) {
        aInitialCopy = pSourceByteLength;
    }

    std::memcpy(pSource, pPassword, static_cast<std::size_t>(aInitialCopy));

    if (aInitialCopy < pSourceByteLength) {
        pSource[aInitialCopy++] = 0;
    }

    if (aInitialCopy < pSourceByteLength) {
        pSource[aInitialCopy++] = 0;
    }

    std::size_t aFilled = aInitialCopy;

    while (aFilled < pSourceByteLength) {
        std::size_t aChunk = aFilled;

        if (aChunk == 0U) {
            break;
        }

        if ((aFilled + aChunk) > pSourceByteLength) {
            aChunk = pSourceByteLength - aFilled;
        }

        std::memcpy(pSource + aFilled,
                    pSource,
                    static_cast<std::size_t>(aChunk));

        aFilled += aChunk;
    }
}

void TwistExpander::Zero() {
    Zero_PostSeed();
    mDomainBundleInbuilt.Zero();
    if (mWorkspace != NULL) {
        mWorkspace->Zero();
    }
}

void TwistExpander::Zero_PostSeed() {
    if (mWorkspace != NULL) {
        mWorkspace->Zero_PostSeed();
    }
    
    memset(mIndexList256A, 0, sizeof(mIndexList256A));
    memset(mIndexList256B, 0, sizeof(mIndexList256B));
    memset(mIndexList256C, 0, sizeof(mIndexList256C));
    memset(mIndexList256D, 0, sizeof(mIndexList256D));
    
    mDomainBundleEphemeral.Zero();
    
    mKDFSessionNonce = 0;
}
