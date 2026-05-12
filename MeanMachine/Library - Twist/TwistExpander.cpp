//
//  TwistExpander.cpp
//  MeanMachine
//

#include "TwistExpander.hpp"
#include "TwistCryptoGenerator.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmSalt.hpp"

#include <chrono>
#include <cstdio>
#include <cstring>
#include <random>

namespace {

inline std::uint64_t RotL64(const std::uint64_t pValue,
                            const unsigned int pBits) {
    const unsigned int aShift = pBits & 63U;
    if (aShift == 0U) {
        return pValue;
    }
    return (pValue << aShift) | (pValue >> (64U - aShift));
}

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
    mFarmSBox = nullptr;
    mFarmSalt = nullptr;
    mSource = nullptr;
    mDest = nullptr;
    mKDFCallCounter = 0ULL;
    mKDFSessionNonce = 0ULL;
    mDomainConstantPublicIngress = Mix64(ProcessKDFFreshnessNonce() ^ 0x5055424C4943494EULL);
    mDomainConstantPrivateIngress = Mix64(ProcessKDFFreshnessNonce() ^ 0x505249564154494EULL);
    mDomainConstantCrossIngress = Mix64(ProcessKDFFreshnessNonce() ^ 0x43524F5353494E47ULL);
    std::memset(mSaltA, 0, sizeof(mSaltA));
    std::memset(mSaltB, 0, sizeof(mSaltB));
    std::memset(mSaltC, 0, sizeof(mSaltC));
    std::memset(mSaltD, 0, sizeof(mSaltD));
    std::memset(mSaltE, 0, sizeof(mSaltE));
    std::memset(mSaltF, 0, sizeof(mSaltF));
    std::memset(mSaltG, 0, sizeof(mSaltG));
    std::memset(mSaltH, 0, sizeof(mSaltH));
    std::memset(mDomainSaltKeyBoxA, 0, sizeof(mDomainSaltKeyBoxA));
    std::memset(mDomainSaltKeyBoxB, 0, sizeof(mDomainSaltKeyBoxB));
    std::memset(mDomainSaltKeyBoxC, 0, sizeof(mDomainSaltKeyBoxC));
    std::memset(mDomainSaltKeyBoxD, 0, sizeof(mDomainSaltKeyBoxD));
    std::memset(mDomainSaltKeyBoxE, 0, sizeof(mDomainSaltKeyBoxE));
    std::memset(mDomainSaltKeyBoxF, 0, sizeof(mDomainSaltKeyBoxF));
    std::memset(mDomainSaltMaskBoxA, 0, sizeof(mDomainSaltMaskBoxA));
    std::memset(mDomainSaltMaskBoxB, 0, sizeof(mDomainSaltMaskBoxB));
    std::memset(mDomainSaltMaskBoxC, 0, sizeof(mDomainSaltMaskBoxC));
    std::memset(mDomainSaltMaskBoxD, 0, sizeof(mDomainSaltMaskBoxD));
    std::memset(mDomainSaltMaskBoxE, 0, sizeof(mDomainSaltMaskBoxE));
    std::memset(mDomainSaltMaskBoxF, 0, sizeof(mDomainSaltMaskBoxF));
    std::memset(mDomainSaltWandererA, 0, sizeof(mDomainSaltWandererA));
    std::memset(mDomainSaltWandererB, 0, sizeof(mDomainSaltWandererB));
    std::memset(mDomainSaltWandererC, 0, sizeof(mDomainSaltWandererC));
    std::memset(mDomainSaltWandererD, 0, sizeof(mDomainSaltWandererD));
    std::memset(mDomainSaltWandererE, 0, sizeof(mDomainSaltWandererE));
    std::memset(mDomainSaltWandererF, 0, sizeof(mDomainSaltWandererF));
    std::memset(mDomainSaltOrbiterA, 0, sizeof(mDomainSaltOrbiterA));
    std::memset(mDomainSaltOrbiterB, 0, sizeof(mDomainSaltOrbiterB));
    std::memset(mDomainSaltOrbiterC, 0, sizeof(mDomainSaltOrbiterC));
    std::memset(mDomainSaltOrbiterD, 0, sizeof(mDomainSaltOrbiterD));
    std::memset(mDomainSaltOrbiterE, 0, sizeof(mDomainSaltOrbiterE));
    std::memset(mDomainSaltOrbiterF, 0, sizeof(mDomainSaltOrbiterF));
    std::memset(mDomainSaltPrismA, 0, sizeof(mDomainSaltPrismA));
    std::memset(mDomainSaltPrismB, 0, sizeof(mDomainSaltPrismB));
    std::memset(mDomainSaltPrismC, 0, sizeof(mDomainSaltPrismC));
    std::memset(mDomainSaltPrismD, 0, sizeof(mDomainSaltPrismD));
    std::memset(mDomainSaltPrismE, 0, sizeof(mDomainSaltPrismE));
    std::memset(mDomainSaltPrismF, 0, sizeof(mDomainSaltPrismF));
    std::memset(mDomainSaltSourceA, 0, sizeof(mDomainSaltSourceA));
    std::memset(mDomainSaltSourceB, 0, sizeof(mDomainSaltSourceB));
    std::memset(mDomainSaltSourceC, 0, sizeof(mDomainSaltSourceC));
    std::memset(mDomainSaltSourceD, 0, sizeof(mDomainSaltSourceD));
    std::memset(mDomainSaltSourceE, 0, sizeof(mDomainSaltSourceE));
    std::memset(mDomainSaltSourceF, 0, sizeof(mDomainSaltSourceF));
    std::memset(mSBoxA, 0, sizeof(mSBoxA));
    std::memset(mSBoxB, 0, sizeof(mSBoxB));
    std::memset(mSBoxC, 0, sizeof(mSBoxC));
    std::memset(mSBoxD, 0, sizeof(mSBoxD));
    std::memset(mSBoxE, 0, sizeof(mSBoxE));
    std::memset(mSBoxF, 0, sizeof(mSBoxF));
    std::memset(mSBoxG, 0, sizeof(mSBoxG));
    std::memset(mSBoxH, 0, sizeof(mSBoxH));
}

TwistExpander::~TwistExpander() {
    
}

void TwistExpander::KDF(TwistDomain pDomain,
                        std::uint64_t pDomainConstantPublicIngress,
                        std::uint64_t pDomainConstantPrivateIngress,
                        std::uint64_t pDomainConstantCrossIngress,
                        std::uint64_t *pDomainSaltA,
                        std::uint64_t *pDomainSaltB,
                        std::uint64_t *pDomainSaltC,
                        std::uint64_t *pDomainSaltD,
                        std::uint64_t *pDomainSaltE,
                        std::uint64_t *pDomainSaltF) {
    if ((pDomainSaltA == nullptr) || (pDomainSaltB == nullptr) || (pDomainSaltC == nullptr) ||
        (pDomainSaltD == nullptr) || (pDomainSaltE == nullptr) || (pDomainSaltF == nullptr)) {
        return;
    }

    std::uint64_t *aOutputs[6] = {
        pDomainSaltA,
        pDomainSaltB,
        pDomainSaltC,
        pDomainSaltD,
        pDomainSaltE,
        pDomainSaltF
    };

    static const std::uint64_t kDomainConstants[6] = {
        0x243F6A8885A308D3ULL,
        0x13198A2E03707344ULL,
        0xA4093822299F31D0ULL,
        0x082EFA98EC4E6C89ULL,
        0x452821E638D01377ULL,
        0xBE5466CF34E90C6CULL
    };

    const std::uint64_t aDomainTag = static_cast<std::uint64_t>(static_cast<std::uint8_t>(pDomain));
    const std::uint64_t aDomainSalt = Mix64(0xC6A4A7935BD1E995ULL ^ (aDomainTag * 0x9E3779B185EBCA87ULL));
    const std::uint64_t aCallIndex = mKDFCallCounter++;
    const std::uint64_t aSessionNonce = mKDFSessionNonce;
    const std::uint64_t aPublicIngressConstant = (pDomainConstantPublicIngress != 0ULL) ?
        pDomainConstantPublicIngress : mDomainConstantPublicIngress;
    const std::uint64_t aPrivateIngressConstant = (pDomainConstantPrivateIngress != 0ULL) ?
        pDomainConstantPrivateIngress : mDomainConstantPrivateIngress;
    const std::uint64_t aCrossIngressConstant = (pDomainConstantCrossIngress != 0ULL) ?
        pDomainConstantCrossIngress : mDomainConstantCrossIngress;
    std::uint64_t aState = 0x9E3779B97F4A7C15ULL ^
                           Mix64(aCallIndex + 0xD1B54A32D192ED03ULL) ^
                           Mix64(aSessionNonce ^ 0xA4093822299F31D0ULL) ^
                           Mix64(aPublicIngressConstant ^ 0x243F6A8885A308D3ULL) ^
                           Mix64(aPrivateIngressConstant ^ 0x13198A2E03707344ULL) ^
                           Mix64(aCrossIngressConstant ^ 0xA4093822299F31D0ULL) ^
                           aDomainSalt;

    for (std::uint32_t i = 0U; i < S_SALT; ++i) {
        const std::uint32_t aIdx = i & static_cast<std::uint32_t>(S_SALT1);
        const std::uint32_t aIdxB = (i + 3U) & static_cast<std::uint32_t>(S_SALT1);
        const std::uint32_t aIdxC = (i + 7U) & static_cast<std::uint32_t>(S_SALT1);

        std::uint64_t aSourceBlend = 0ULL;
        if (mSource != nullptr) {
            const std::uint32_t aSourceIndexA = static_cast<std::uint32_t>((i * 131U + (aCallIndex * 17ULL)) & static_cast<std::uint64_t>(S_BLOCK1));
            const std::uint32_t aSourceIndexB = static_cast<std::uint32_t>((i * 197U + (aCallIndex * 29ULL)) & static_cast<std::uint64_t>(S_BLOCK1));
            const std::uint64_t aByteA = static_cast<std::uint64_t>(mSource[aSourceIndexA]);
            const std::uint64_t aByteB = static_cast<std::uint64_t>(mSource[aSourceIndexB]);
            aSourceBlend = (aByteA << 8U) | aByteB;
        }

        std::uint64_t aWorkspaceBlend = 0ULL;
        if (mWorkspace != nullptr) {
            const std::uint32_t aSourceIndexA = static_cast<std::uint32_t>((i * 131U + (aCallIndex * 17ULL)) & static_cast<std::uint64_t>(S_BLOCK1));
            const std::uint32_t aSourceIndexB = static_cast<std::uint32_t>((i * 197U + (aCallIndex * 29ULL)) & static_cast<std::uint64_t>(S_BLOCK1));
            const std::uint64_t aWorkA = static_cast<std::uint64_t>(mWorkspace->mWorkLaneA[aSourceIndexA]);
            const std::uint64_t aWorkB = static_cast<std::uint64_t>(mWorkspace->mWorkLaneB[aSourceIndexB]);
            const std::uint64_t aWorkC = static_cast<std::uint64_t>(mWorkspace->mWorkLaneC[aSourceIndexA]);
            const std::uint64_t aWorkD = static_cast<std::uint64_t>(mWorkspace->mWorkLaneD[aSourceIndexB]);
            aWorkspaceBlend = (aWorkA << 24U) ^ (aWorkB << 16U) ^ (aWorkC << 8U) ^ aWorkD;
        }

        const std::uint64_t aSaltBlend =
            mSaltA[aIdx] ^
            RotL64(mSaltB[aIdxB], 7U) ^
            RotL64(mSaltC[aIdxC], 13U) ^
            RotL64(mSaltD[aIdx], 19U) ^
            RotL64(mSaltE[aIdxB], 29U) ^
            RotL64(mSaltF[aIdxC], 37U) ^
            RotL64(mSaltG[aIdx], 43U) ^
            RotL64(mSaltH[aIdxB], 53U);

        aState = Mix64(aState ^ aSaltBlend ^ aSourceBlend ^ aWorkspaceBlend ^
                       RotL64(aPublicIngressConstant, (i * 3U) & 63U) ^
                       RotL64(aPrivateIngressConstant, (i * 7U) & 63U) ^
                       RotL64(aCrossIngressConstant, (i * 13U) & 63U) ^
                       RotL64(aSessionNonce, (i * 11U) & 63U) ^
                       RotL64(aDomainSalt, (i * 5U) & 63U) ^
                       (0x9E3779B185EBCA87ULL * static_cast<std::uint64_t>(i + 1U)));

        for (int lane = 0; lane < 6; ++lane) {
            std::uint64_t aLaneValue = aState ^
                                       kDomainConstants[lane] ^
                                       RotL64(aPublicIngressConstant, static_cast<unsigned int>((lane * 5 + i) & 63U)) ^
                                       RotL64(aPrivateIngressConstant, static_cast<unsigned int>((lane * 11 + i) & 63U)) ^
                                       RotL64(aCrossIngressConstant, static_cast<unsigned int>((lane * 17 + i) & 63U)) ^
                                       RotL64(aSessionNonce ^ kDomainConstants[lane],
                                              static_cast<unsigned int>((lane * 7 + i) & 63U)) ^
                                       RotL64(aSaltBlend, static_cast<unsigned int>((lane * 9 + i) & 63U));
            aLaneValue = Mix64(aLaneValue + (static_cast<std::uint64_t>(lane + 1) * 0xD6E8FEB86659FD93ULL));
            aOutputs[lane][i] = aLaneValue;
        }
    }
}

void TwistExpander::KDF(std::uint64_t *pDomainSaltA,
                        std::uint64_t *pDomainSaltB,
                        std::uint64_t *pDomainSaltC,
                        std::uint64_t *pDomainSaltD,
                        std::uint64_t *pDomainSaltE,
                        std::uint64_t *pDomainSaltF) {
    KDF(TwistDomain::kInv,
        mDomainConstantPublicIngress,
        mDomainConstantPrivateIngress,
        mDomainConstantCrossIngress,
        pDomainSaltA,
        pDomainSaltB,
        pDomainSaltC,
        pDomainSaltD,
        pDomainSaltE,
        pDomainSaltF);
}

void TwistExpander::Seed(TwistWorkSpace *pWorkspace,
                         TwistCryptoGenerator *pCryptoGenerator,
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
    if (pCryptoGenerator == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires crypto generator\n");
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
    
    KDF(TwistDomain::kKeyBoxA,
        mDomainConstantPublicIngress,
        mDomainConstantPrivateIngress,
        mDomainConstantCrossIngress,
        mDomainSaltKeyBoxA, mDomainSaltKeyBoxB, mDomainSaltKeyBoxC,
        mDomainSaltKeyBoxD, mDomainSaltKeyBoxE, mDomainSaltKeyBoxF);
    KDF(TwistDomain::kMaskBoxA,
        mDomainConstantPublicIngress,
        mDomainConstantPrivateIngress,
        mDomainConstantCrossIngress,
        mDomainSaltMaskBoxA, mDomainSaltMaskBoxB, mDomainSaltMaskBoxC,
        mDomainSaltMaskBoxD, mDomainSaltMaskBoxE, mDomainSaltMaskBoxF);
    KDF(TwistDomain::kSalts,
        mDomainConstantPublicIngress,
        mDomainConstantPrivateIngress,
        mDomainConstantCrossIngress,
        mDomainSaltWandererA, mDomainSaltWandererB, mDomainSaltWandererC,
        mDomainSaltWandererD, mDomainSaltWandererE, mDomainSaltWandererF);
    KDF(TwistDomain::kSBoxes,
        mDomainConstantPublicIngress,
        mDomainConstantPrivateIngress,
        mDomainConstantCrossIngress,
        mDomainSaltOrbiterA, mDomainSaltOrbiterB, mDomainSaltOrbiterC,
        mDomainSaltOrbiterD, mDomainSaltOrbiterE, mDomainSaltOrbiterF);
    KDF(TwistDomain::kKeyBoxB,
        mDomainConstantPublicIngress,
        mDomainConstantPrivateIngress,
        mDomainConstantCrossIngress,
        mDomainSaltPrismA, mDomainSaltPrismB, mDomainSaltPrismC,
        mDomainSaltPrismD, mDomainSaltPrismE, mDomainSaltPrismF);
    KDF(TwistDomain::kMaskBoxB,
        mDomainConstantPublicIngress,
        mDomainConstantPrivateIngress,
        mDomainConstantCrossIngress,
        mDomainSaltSourceA, mDomainSaltSourceB, mDomainSaltSourceC,
        mDomainSaltSourceD, mDomainSaltSourceE, mDomainSaltSourceF);
    
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
