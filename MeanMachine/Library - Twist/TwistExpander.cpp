//
//  TwistExpander.cpp
//  MeanMachine
//

#include "TwistExpander.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmSalt.hpp"

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

inline void CopyGlobalSBoxesToSet(TwistDomainSBoxSet *pDest,
                                  const std::uint8_t *pSBoxA,
                                  const std::uint8_t *pSBoxB,
                                  const std::uint8_t *pSBoxC,
                                  const std::uint8_t *pSBoxD,
                                  const std::uint8_t *pSBoxE,
                                  const std::uint8_t *pSBoxF,
                                  const std::uint8_t *pSBoxG,
                                  const std::uint8_t *pSBoxH) {
    if (pDest == nullptr) {
        return;
    }
    std::memcpy(pDest->mSBoxA, pSBoxA, sizeof(pDest->mSBoxA));
    std::memcpy(pDest->mSBoxB, pSBoxB, sizeof(pDest->mSBoxB));
    std::memcpy(pDest->mSBoxC, pSBoxC, sizeof(pDest->mSBoxC));
    std::memcpy(pDest->mSBoxD, pSBoxD, sizeof(pDest->mSBoxD));
    std::memcpy(pDest->mSBoxE, pSBoxE, sizeof(pDest->mSBoxE));
    std::memcpy(pDest->mSBoxF, pSBoxF, sizeof(pDest->mSBoxF));
    std::memcpy(pDest->mSBoxG, pSBoxG, sizeof(pDest->mSBoxG));
    std::memcpy(pDest->mSBoxH, pSBoxH, sizeof(pDest->mSBoxH));
}

inline void CopySetToGlobalSBoxes(const TwistDomainSBoxSet *pSource,
                                  std::uint8_t *pSBoxA,
                                  std::uint8_t *pSBoxB,
                                  std::uint8_t *pSBoxC,
                                  std::uint8_t *pSBoxD,
                                  std::uint8_t *pSBoxE,
                                  std::uint8_t *pSBoxF,
                                  std::uint8_t *pSBoxG,
                                  std::uint8_t *pSBoxH) {
    if (pSource == nullptr) {
        return;
    }
    std::memcpy(pSBoxA, pSource->mSBoxA, S_SBOX);
    std::memcpy(pSBoxB, pSource->mSBoxB, S_SBOX);
    std::memcpy(pSBoxC, pSource->mSBoxC, S_SBOX);
    std::memcpy(pSBoxD, pSource->mSBoxD, S_SBOX);
    std::memcpy(pSBoxE, pSource->mSBoxE, S_SBOX);
    std::memcpy(pSBoxF, pSource->mSBoxF, S_SBOX);
    std::memcpy(pSBoxG, pSource->mSBoxG, S_SBOX);
    std::memcpy(pSBoxH, pSource->mSBoxH, S_SBOX);
}

} // namespace

TwistExpander::TwistExpander() {
    mWorkspace = nullptr;
    mFarmSBox = nullptr;
    mFarmSalt = nullptr;
    mSource = nullptr;
    mDest = nullptr;
    mKDFCallCounter = 0ULL;
    mKDFSessionNonce = 0ULL;
    mActiveConstants = nullptr;
    mActiveSaltSet = nullptr;
    mActiveSBoxSet = nullptr;
    std::memset(&mDomainBundleInbuilt, 0, sizeof(mDomainBundleInbuilt));
    std::memset(&mDomainBundleEphemeral, 0, sizeof(mDomainBundleEphemeral));
    auto SeedDomainConstants = [&](TwistDomainConstants *pConstants,
                                   const std::uint64_t pDomainTag) {
        if (pConstants == nullptr) {
            return;
        }
        pConstants->mDomainConstantPublicIngress = Mix64((0x5055424C4943494EULL ^ pDomainTag) ^ ProcessKDFFreshnessNonce());
        pConstants->mDomainConstantPrivateIngress = Mix64((0x505249564154494EULL ^ pDomainTag) ^ ProcessKDFFreshnessNonce());
        pConstants->mDomainConstantCrossIngress = Mix64((0x43524F5353494E47ULL ^ pDomainTag) ^ ProcessKDFFreshnessNonce());
    };
    SeedDomainConstants(&mDomainBundleInbuilt.mKeyAConstants, 0x4B45595F415F4B44ULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mKeyBConstants, 0x4B45595F425F4B44ULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mMaskAConstants, 0x4D41534B415F4B44ULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mMaskBConstants, 0x4D41534B425F4B44ULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mWorkLaneConstants, 0x574F524B4C4E4B44ULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mMaskLaneConstants, 0x4D4C4E454D4B5344ULL);
    SeedDomainConstants(&mDomainBundleInbuilt.mOperationLaneConstants, 0x4F504C4E4B44584FULL);
    std::memset(mIndexList256A, 0, sizeof(mIndexList256A));
    std::memset(mIndexList256B, 0, sizeof(mIndexList256B));
    std::memset(mIndexList256C, 0, sizeof(mIndexList256C));
    std::memset(mIndexList256D, 0, sizeof(mIndexList256D));
    std::memset(mSBoxA, 0, sizeof(mSBoxA));
    std::memset(mSBoxB, 0, sizeof(mSBoxB));
    std::memset(mSBoxC, 0, sizeof(mSBoxC));
    std::memset(mSBoxD, 0, sizeof(mSBoxD));
    std::memset(mSBoxE, 0, sizeof(mSBoxE));
    std::memset(mSBoxF, 0, sizeof(mSBoxF));
    std::memset(mSBoxG, 0, sizeof(mSBoxG));
    std::memset(mSBoxH, 0, sizeof(mSBoxH));
    SyncDomainBundleInbuiltFromLegacy();
    std::memcpy(&mDomainBundleEphemeral, &mDomainBundleInbuilt, sizeof(mDomainBundleEphemeral));
}

TwistExpander::~TwistExpander() {
    
}

void TwistExpander::SyncDomainBundleInbuiltFromLegacy() {
    CopyGlobalSBoxesToSet(&mDomainBundleInbuilt.mKeyASBoxes, mSBoxA, mSBoxB, mSBoxC, mSBoxD, mSBoxE, mSBoxF, mSBoxG, mSBoxH);
    CopyGlobalSBoxesToSet(&mDomainBundleInbuilt.mKeyBSBoxes, mSBoxA, mSBoxB, mSBoxC, mSBoxD, mSBoxE, mSBoxF, mSBoxG, mSBoxH);
    CopyGlobalSBoxesToSet(&mDomainBundleInbuilt.mMaskASBoxes, mSBoxA, mSBoxB, mSBoxC, mSBoxD, mSBoxE, mSBoxF, mSBoxG, mSBoxH);
    CopyGlobalSBoxesToSet(&mDomainBundleInbuilt.mMaskBSBoxes, mSBoxA, mSBoxB, mSBoxC, mSBoxD, mSBoxE, mSBoxF, mSBoxG, mSBoxH);
    CopyGlobalSBoxesToSet(&mDomainBundleInbuilt.mWorkLaneSBoxes, mSBoxA, mSBoxB, mSBoxC, mSBoxD, mSBoxE, mSBoxF, mSBoxG, mSBoxH);
    CopyGlobalSBoxesToSet(&mDomainBundleInbuilt.mMaskLaneSBoxes, mSBoxA, mSBoxB, mSBoxC, mSBoxD, mSBoxE, mSBoxF, mSBoxG, mSBoxH);
    CopyGlobalSBoxesToSet(&mDomainBundleInbuilt.mOperationLaneSBoxes, mSBoxA, mSBoxB, mSBoxC, mSBoxD, mSBoxE, mSBoxF, mSBoxG, mSBoxH);
}

void TwistExpander::SyncLegacyFromDomainBundleInbuilt() {
    CopySetToGlobalSBoxes(&mDomainBundleInbuilt.mWorkLaneSBoxes,
                          mSBoxA,
                          mSBoxB,
                          mSBoxC,
                          mSBoxD,
                          mSBoxE,
                          mSBoxF,
                          mSBoxG,
                          mSBoxH);
}

void TwistExpander::KDF(std::uint8_t *pSource,
                        std::uint8_t *pDest,
                        TwistDomainConstants *pDomainConstants,
                        TwistDomainSaltSet *pDomainSaltSet,
                        TwistDomainSBoxSet *pDomainSBoxSet) {
    if ((pSource == nullptr) || (pDest == nullptr) ||
        (pDomainConstants == nullptr) ||
        (pDomainSaltSet == nullptr) ||
        (pDomainSBoxSet == nullptr)) {
        return;
    }

    mSource = pSource;
    mDest = pDest;
    mActiveConstants = pDomainConstants;
    mActiveSaltSet = pDomainSaltSet;
    mActiveSBoxSet = pDomainSBoxSet;
}

void TwistExpander::Seed(TwistWorkSpace *pWorkspace,
                         TwistFarmSBox *pFarmSBox,
                         TwistFarmSalt *pFarmSalt,
                         std::uint8_t *pSource,
                         std::uint8_t *pPassword,
                         unsigned int pPasswordByteLength) {
    if (pWorkspace == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires workspace\n");
        return;
    }
    if (pSource == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires source buffer\n");
        return;
    }
    if (pFarmSBox == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires farm s-box worker\n");
        return;
    }
    if (pFarmSalt == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires farm salt worker\n");
        return;
    }

    mWorkspace = pWorkspace;
    mFarmSBox = pFarmSBox;
    mFarmSalt = pFarmSalt;
    mSource = pSource;
    mDest = nullptr;
    UnrollPasswordToSource(pSource, pPassword, pPasswordByteLength);
    mKDFCallCounter = 0ULL;
    mKDFSessionNonce = ProcessKDFFreshnessNonce();
    SyncDomainBundleInbuiltFromLegacy();
    std::memcpy(&mDomainBundleEphemeral, &mDomainBundleInbuilt, sizeof(mDomainBundleEphemeral));
    pWorkspace->mDomainBundle = mDomainBundleEphemeral;
}

void TwistExpander::TwistBlock(TwistWorkSpace *pWorkspace,
                               std::uint8_t *pSource,
                               std::uint8_t *pDestination) {
    if ((pWorkspace == nullptr) || (pSource == nullptr) || (pDestination == nullptr)) {
        return;
    }

    mWorkspace = pWorkspace;
    mSource = pSource;
    mDest = pDestination;
}

TwistFarmSBox *TwistExpander::GetFarmSBox() const {
    return mFarmSBox;
}

TwistFarmSalt *TwistExpander::GetFarmSalt() const {
    return mFarmSalt;
}

void TwistExpander::Twist(TwistWorkSpace *pWorkspace,
                          std::uint8_t *pSource,
                          std::uint8_t *pDestination,
                          unsigned int pDestinationByteLength) {
    if ((pWorkspace == nullptr) || (pSource == nullptr) || (pDestination == nullptr)) {
        std::printf("fatal: TwistExpander::Twist requires workspace/source/destination\n");
        return;
    }
    if ((pDestinationByteLength % S_BLOCK) != 0U) {
        std::printf("fatal: TwistExpander::Twist needs a multiple of S_BLOCK\n");
        return;
    }
    
    mWorkspace = pWorkspace;
    mSource = pSource;
    mDest = pDestination;

    for (unsigned int aStartByte = 0U;
         aStartByte < pDestinationByteLength;
         aStartByte += S_BLOCK) {
        TwistBlock(pWorkspace, pSource + aStartByte, pDestination + aStartByte);
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
