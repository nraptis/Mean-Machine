//
//  TwistExpander.cpp
//  MeanMachine
//

#include "TwistExpander.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistMix64.hpp"

#include <chrono>
#include <cstdio>
#include <cstring>
#include <random>

namespace {

inline std::uint64_t Mix64(std::uint64_t pValue) {
    pValue ^= (pValue >> 30U);
    pValue *= 0xBF58476D1CE4E5B9ULL;
    pValue ^= (pValue >> 27U);
    pValue *= 0x94D049BB133111EBULL;
    pValue ^= (pValue >> 31U);
    return pValue;
}

inline std::uint64_t BuildProcessKDFFreshnessNonce() {
    std::uint64_t aSeed = 0xD1B54A32D192ED03ULL;
    
    const std::uint64_t aClockTick = static_cast<std::uint64_t>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );
    aSeed ^= Mix64(aClockTick ^ 0x9E3779B97F4A7C15ULL);
    
    std::random_device aRandomDevice;
    aSeed ^= Mix64(static_cast<std::uint64_t>(aRandomDevice()) << 32U);
    aSeed ^= Mix64(static_cast<std::uint64_t>(aRandomDevice()));
    
    return Mix64(aSeed);
}

inline std::uint64_t ProcessKDFFreshnessNonce() {
    static const std::uint64_t kProcessNonce = BuildProcessKDFFreshnessNonce();
    return kProcessNonce;
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
    auto SeedDomainConstants = [&](TwistDomainConstants *pConstants,
                                   const std::uint64_t pDomainTag) {
        if (pConstants == nullptr) {
            return;
        }
        pConstants->mIngress = Mix64((0x5055424C4943494EULL ^ pDomainTag) ^ ProcessKDFFreshnessNonce());
        pConstants->mScatter = Mix64((0x505249564154494EULL ^ pDomainTag) ^ ProcessKDFFreshnessNonce());
        pConstants->mCross = Mix64((0x43524F5353494E47ULL ^ pDomainTag) ^ ProcessKDFFreshnessNonce());
        pConstants->mDomainConstantPublicIngress = pConstants->mIngress;
        pConstants->mDomainConstantPrivateIngress = pConstants->mScatter;
        pConstants->mDomainConstantCrossIngress = pConstants->mCross;
        
        auto Next64 = [&](const std::uint64_t pLane) -> std::uint64_t {
            const std::uint64_t aLaneSeed =
                pDomainTag ^
                (0x9E3779B97F4A7C15ULL * (pLane + 1ULL)) ^
                ProcessKDFFreshnessNonce();
            std::uint64_t aValue = Mix64(aLaneSeed);
            if (aValue == 0ULL) {
                aValue = pLane | 1ULL;
            }
            return aValue;
        };
        auto NextByte = [&](const std::uint64_t pLane) -> std::uint8_t {
            std::uint8_t aValue = static_cast<std::uint8_t>(Next64(pLane) & 0xFFU);
            if (aValue == 0U) {
                aValue = static_cast<std::uint8_t>((pLane & 0xFFU) | 1U);
            }
            return aValue;
        };
        
        pConstants->mMatrixSelectA = Next64(0x10ULL);
        pConstants->mMatrixSelectB = Next64(0x11ULL);
        pConstants->mMatrixUnrollA = NextByte(0x12ULL);
        pConstants->mMatrixUnrollB = NextByte(0x13ULL);
        pConstants->mMatrixArgA = NextByte(0x14ULL);
        pConstants->mMatrixArgB = NextByte(0x15ULL);
        pConstants->mMatrixArgC = NextByte(0x16ULL);
        pConstants->mMatrixArgD = NextByte(0x17ULL);
        pConstants->mMaskMutateA = NextByte(0x18ULL);
        pConstants->mMaskMutateB = NextByte(0x19ULL);
    };
    SeedDomainConstants(&mDomainBundleInbuilt.mPhaseAConstants, 0x50484153455F415FULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mPhaseBConstants, 0x50484153455F425FULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mPhaseCConstants, 0x50484153455F435FULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mPhaseDConstants, 0x50484153455F445FULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mPhaseEConstants, 0x50484153455F455FULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mPhaseFConstants, 0x50484153455F465FULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mPhaseGConstants, 0x50484153455F475FULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mPhaseHConstants, 0x50484153455F485FULL);
    std::memset(mIndexList256A, 0, sizeof(mIndexList256A));
    std::memset(mIndexList256B, 0, sizeof(mIndexList256B));
    std::memset(mIndexList256C, 0, sizeof(mIndexList256C));
    std::memset(mIndexList256D, 0, sizeof(mIndexList256D));
    std::memcpy(&mDomainBundleEphemeral, &mDomainBundleInbuilt, sizeof(mDomainBundleEphemeral));
}

TwistExpander::~TwistExpander() {
    
}

void TwistExpander::KDF(std::uint64_t pNonce,
                        TwistDomainConstants *pDomainConstants,
                        TwistDomainSaltSet *pDomainSaltSet) {
    if ((mSource == nullptr) ||
        (pDomainConstants == nullptr) ||
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
                         unsigned int pPasswordByteLength,
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
    mKDFSessionNonce = Mix64(pNonce ^ ProcessKDFFreshnessNonce());
    std::memcpy(&mDomainBundleEphemeral, &mDomainBundleInbuilt, sizeof(mDomainBundleEphemeral));
    pWorkSpace->mDomainBundle = mDomainBundleEphemeral;
}

void TwistExpander::TwistBlock(TwistWorkSpace *pWorkSpace,
                               std::uint64_t pNonce,
                               std::uint8_t *pSource,
                               std::size_t pBlockIndex,
                               std::size_t pBlockCount,
                               std::uint8_t *pDestination) {
    (void)pBlockIndex;
    (void)pBlockCount;
    if ((pWorkSpace == nullptr) || (pSource == nullptr) || (pDestination == nullptr)) {
        return;
    }

    mWorkspace = pWorkSpace;
    mSource = pSource;
    mDest = pDestination;
    mKDFSessionNonce = pNonce;
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
                          std::uint64_t pNonce,
                          std::uint8_t *pSource,
                          std::uint8_t *pDestination,
                          unsigned int pDestinationByteLength) {
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

    const std::size_t aBlockCount = static_cast<std::size_t>(pDestinationByteLength / S_BLOCK);
    std::size_t aBlockIndex = 0U;
    for (unsigned int aStartByte = 0U;
         aStartByte < pDestinationByteLength;
         aStartByte += S_BLOCK, aBlockIndex += 1U) {
        TwistBlock(pWorkSpace,
                   pNonce,
                   pSource + aStartByte,
                   aBlockIndex,
                   aBlockCount,
                   pDestination + aStartByte);
    }
    
}

void TwistExpander::UnrollPasswordToSource(std::uint8_t *pSource,
                            std::uint8_t *pPassword,
                            const unsigned int pPasswordByteLength) {
    if (pSource == nullptr) {
        return;
    }

    std::memset(pSource, 0, static_cast<std::size_t>(S_BLOCK));
    if ((pPassword == nullptr) || (pPasswordByteLength == 0U)) {
        return;
    }

    unsigned int aInitialCopy = pPasswordByteLength;
    if (aInitialCopy > S_BLOCK) {
        aInitialCopy = S_BLOCK;
    }

    std::memcpy(pSource, pPassword, static_cast<std::size_t>(aInitialCopy));
    if (aInitialCopy < S_BLOCK) {
        pSource[aInitialCopy++] = 0;
    }
    if (aInitialCopy < S_BLOCK) {
        pSource[aInitialCopy++] = 0;
    }

    unsigned int aFilled = aInitialCopy;
    while (aFilled < S_BLOCK) {
        unsigned int aChunk = aFilled;
        if ((aFilled + aChunk) > S_BLOCK) {
            aChunk = S_BLOCK - aFilled;
        }
        std::memcpy(pSource + aFilled, pSource, static_cast<std::size_t>(aChunk));
        aFilled += aChunk;
    }
}

void TwistExpander::UnrollPasswordToSource(std::uint8_t *pSource,
                                           std::uint8_t *pPassword,
                                           const unsigned int pPasswordByteLength,
                                           const unsigned int pSourceByteLength) {
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

    unsigned int aInitialCopy = pPasswordByteLength;
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

    unsigned int aFilled = aInitialCopy;

    while (aFilled < pSourceByteLength) {
        unsigned int aChunk = aFilled;

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
