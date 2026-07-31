//
//  TwistExpander.cpp
//  MeanMachine
//

#include "TwistExpander.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistMix64.hpp"

#include <cstdio>
#include <cstring>

TwistExpander::TwistExpander() {
    std::memset(&mDomainBundleInbuilt, 0, sizeof(mDomainBundleInbuilt));
    std::memset(&mDomainBundleEphemeral, 0, sizeof(mDomainBundleEphemeral));
}

TwistExpander::~TwistExpander() {
    
}

void TwistExpander::KDF(std::uint64_t pNonce,
                        TwistDomainConstants *pDomainConstants,
                        TwistDomainSaltSet *pDomainSaltSet) {
    (void)pNonce;
    (void)pDomainConstants;
    (void)pDomainSaltSet;
}

void TwistExpander::KDF_A(TwistWorkSpace *pWorkSpace,
                          std::uint64_t pNonce,
                          TwistDomainConstants *pDomainConstants,
                          TwistDomainSaltSet *pDomainSaltSet,
                          MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pIngress;
    (void)pCarry;
    (void)pWandererA;
    (void)pWandererB;
    (void)pWandererC;
    (void)pWandererD;
    (void)pWandererE;
    (void)pWandererF;
    (void)pWandererG;
    (void)pWandererH;
    (void)pWandererI;
    (void)pWandererJ;
    (void)pWandererK;
    TwistExpander::KDF(pNonce,
                       pDomainConstants,
                       pDomainSaltSet);
}

void TwistExpander::KDF_B(TwistWorkSpace *pWorkSpace,
                          std::uint64_t pNonce,
                          TwistDomainConstants *pDomainConstants,
                          TwistDomainSaltSet *pDomainSaltSet,
                          MUTABLE_PARAMS) {
    TwistExpander::KDF_A(pWorkSpace, pNonce, pDomainConstants, pDomainSaltSet,
                         MUTABLE_PARAMS_PASSED);
}

void TwistExpander::KDF_C(TwistWorkSpace *pWorkSpace,
                          std::uint64_t pNonce,
                          TwistDomainConstants *pDomainConstants,
                          TwistDomainSaltSet *pDomainSaltSet,
                          MUTABLE_PARAMS) {
    TwistExpander::KDF_A(pWorkSpace, pNonce, pDomainConstants, pDomainSaltSet,
                         MUTABLE_PARAMS_PASSED);
}

void TwistExpander::KDF_D(TwistWorkSpace *pWorkSpace,
                          std::uint64_t pNonce,
                          TwistDomainConstants *pDomainConstants,
                          TwistDomainSaltSet *pDomainSaltSet,
                          MUTABLE_PARAMS) {
    TwistExpander::KDF_A(pWorkSpace, pNonce, pDomainConstants, pDomainSaltSet,
                         MUTABLE_PARAMS_PASSED);
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
        std::printf("fatal: TwistExpander::Seed requires farm salt\n");
        return;
    }
    UnrollPassword(pWorkSpace->mSourceLane, pPassword, pPasswordByteLength);
    UnrollNonce(pWorkSpace->mNonceLane, pNonce);
    mDomainBundleEphemeral.Zero();
    pWorkSpace->mDomainBundle.Zero();
}

void TwistExpander::TwistBlock(TwistWorkSpace *pWorkSpace,
                               std::uint8_t *pSource,
                               std::uint8_t *pCrossLaneA,
                               std::uint8_t *pCrossLaneB,
                               std::uint8_t *pCrossLaneC,
                               std::uint8_t *pCrossLaneD,
                               std::uint8_t *pDestination) {
    if ((pWorkSpace == nullptr) ||
        (pSource == nullptr) ||
        (pCrossLaneA == nullptr) ||
        (pCrossLaneB == nullptr) ||
        (pCrossLaneC == nullptr) ||
        (pCrossLaneD == nullptr) ||
        (pDestination == nullptr)) {
        return;
    }

}

void TwistExpander::GrowKeyA(TwistWorkSpace *pWorkSpace,
                             MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pIngress;
    (void)pCarry;
    (void)pWandererA;
    (void)pWandererB;
    (void)pWandererC;
    (void)pWandererD;
    (void)pWandererE;
    (void)pWandererF;
    (void)pWandererG;
    (void)pWandererH;
    (void)pWandererI;
    (void)pWandererJ;
    (void)pWandererK;
}

void TwistExpander::GrowKeyB(TwistWorkSpace *pWorkSpace,
                             MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pIngress;
    (void)pCarry;
    (void)pWandererA;
    (void)pWandererB;
    (void)pWandererC;
    (void)pWandererD;
    (void)pWandererE;
    (void)pWandererF;
    (void)pWandererG;
    (void)pWandererH;
    (void)pWandererI;
    (void)pWandererJ;
    (void)pWandererK;
}

void TwistExpander::Twist(TwistWorkSpace *pWorkSpace,
                          std::uint8_t *pSource,
                          std::uint8_t *pCrossLaneA,
                          std::uint8_t *pCrossLaneB,
                          std::uint8_t *pCrossLaneC,
                          std::uint8_t *pCrossLaneD,
                          std::uint8_t *pDestination,
                          std::size_t pDestinationByteLength) {
    if ((pWorkSpace == nullptr) ||
        (pSource == nullptr) ||
        (pCrossLaneA == nullptr) ||
        (pCrossLaneB == nullptr) ||
        (pCrossLaneC == nullptr) ||
        (pCrossLaneD == nullptr) ||
        (pDestination == nullptr)) {
        std::printf("fatal: TwistExpander::Twist requires workspace/source/cross lanes/destination\n");
        return;
    }
    if ((pDestinationByteLength % S_BLOCK) != 0U) {
        std::printf("fatal: TwistExpander::Twist needs a multiple of S_BLOCK\n");
        return;
    }
    
    for (std::size_t aStartByte = 0U;
         aStartByte < pDestinationByteLength;
         aStartByte += static_cast<std::size_t>(S_BLOCK)) {
        TwistBlock(pWorkSpace,
                   pSource + aStartByte,
                   pCrossLaneA,
                   pCrossLaneB,
                   pCrossLaneC,
                   pCrossLaneD,
                   pDestination + aStartByte);
    }
    
}

void TwistExpander::AutoSeedThenTwist(TwistWorkSpace *pWorkSpace,
                                      TwistFarmSalt *pFarmSalt,
                                      std::uint64_t pNonce,
                                      std::uint8_t *pPassword,
                                      std::size_t pPasswordByteLength,
                                      std::uint8_t *pCrossLaneA,
                                      std::uint8_t *pCrossLaneB,
                                      std::uint8_t *pCrossLaneC,
                                      std::uint8_t *pCrossLaneD,
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
                   pCrossLaneA,
                   pCrossLaneB,
                   pCrossLaneC,
                   pCrossLaneD,
                   &pDestination[aDestinationIndex]); // dest
        aDestinationIndex += S_BLOCK;
    }
    
}

// Assumes the work space is seeded...
void TwistExpander::AutoTwist(TwistWorkSpace *pWorkSpace,
                              std::uint8_t *pSource,
                              std::uint8_t *pCrossLaneA,
                              std::uint8_t *pCrossLaneB,
                              std::uint8_t *pCrossLaneC,
                              std::uint8_t *pCrossLaneD,
                              std::uint8_t *pDestination,
                              std::size_t pDestinationByteLength) {
    
    TwistBlock(pWorkSpace,
               pSource,
               pCrossLaneA,
               pCrossLaneB,
               pCrossLaneC,
               pCrossLaneD,
               pDestination); // dest
    
    std::size_t aDestinationIndex = S_BLOCK;
    while (aDestinationIndex < pDestinationByteLength) {
        TwistBlock(pWorkSpace,
                   &pDestination[aDestinationIndex - S_BLOCK], // source
                   pCrossLaneA,
                   pCrossLaneB,
                   pCrossLaneC,
                   pCrossLaneD,
                   &pDestination[aDestinationIndex]); // dest
        aDestinationIndex += S_BLOCK;
    }
    
}

void TwistExpander::UnrollPassword(std::uint8_t *pSourceLane,
                                   std::uint8_t *pPassword,
                                   std::size_t pPasswordByteLength) {
    if (pSourceLane == nullptr) {
        return;
    }

    std::memset(pSourceLane, 0, static_cast<std::size_t>(S_BLOCK));
    if ((pPassword == nullptr) || (pPasswordByteLength == 0U)) {
        return;
    }

    std::size_t aInitialCopy = pPasswordByteLength;
    if (aInitialCopy > static_cast<std::size_t>(S_BLOCK)) {
        aInitialCopy = static_cast<std::size_t>(S_BLOCK);
    }

    std::memcpy(pSourceLane, pPassword, static_cast<std::size_t>(aInitialCopy));
    if (aInitialCopy < static_cast<std::size_t>(S_BLOCK)) {
        pSourceLane[aInitialCopy++] = 0;
    }
    if (aInitialCopy < static_cast<std::size_t>(S_BLOCK)) {
        pSourceLane[aInitialCopy++] = 0;
    }

    std::size_t aFilled = aInitialCopy;
    while (aFilled < static_cast<std::size_t>(S_BLOCK)) {
        std::size_t aChunk = aFilled;
        if ((aFilled + aChunk) > static_cast<std::size_t>(S_BLOCK)) {
            aChunk = static_cast<std::size_t>(S_BLOCK) - aFilled;
        }
        std::memcpy(pSourceLane + aFilled,
                    pSourceLane,
                    static_cast<std::size_t>(aChunk));
        aFilled += aChunk;
    }
}

void TwistExpander::UnrollPassword(std::uint8_t *pSourceLane,
                                   std::uint8_t *pPassword,
                                   std::size_t pPasswordByteLength,
                                   std::size_t pSourceLaneByteLength) {
    if (pSourceLane == nullptr) {
        return;
    }

    if (pSourceLaneByteLength == 0U) {
        return;
    }

    std::memset(pSourceLane, 0, static_cast<std::size_t>(pSourceLaneByteLength));

    if ((pPassword == nullptr) || (pPasswordByteLength == 0U)) {
        return;
    }

    std::size_t aInitialCopy = pPasswordByteLength;
    if (aInitialCopy > pSourceLaneByteLength) {
        aInitialCopy = pSourceLaneByteLength;
    }

    std::memcpy(pSourceLane, pPassword, static_cast<std::size_t>(aInitialCopy));

    if (aInitialCopy < pSourceLaneByteLength) {
        pSourceLane[aInitialCopy++] = 0;
    }

    if (aInitialCopy < pSourceLaneByteLength) {
        pSourceLane[aInitialCopy++] = 0;
    }

    std::size_t aFilled = aInitialCopy;

    while (aFilled < pSourceLaneByteLength) {
        std::size_t aChunk = aFilled;

        if (aChunk == 0U) {
            break;
        }

        if ((aFilled + aChunk) > pSourceLaneByteLength) {
            aChunk = pSourceLaneByteLength - aFilled;
        }

        std::memcpy(pSourceLane + aFilled,
                    pSourceLane,
                    static_cast<std::size_t>(aChunk));

        aFilled += aChunk;
    }
}

void TwistExpander::UnrollNonce(std::uint8_t *pNonceLane,
                                std::uint64_t pNonce) {
    if (pNonceLane == nullptr) {
        return;
    }

    const std::uint64_t aNonceWordA = TwistMix64::DiffuseA(pNonce);
    const std::uint64_t aNonceWordB = TwistMix64::DiffuseB(pNonce);
    const std::uint64_t aNonceWordC = TwistMix64::DiffuseC(pNonce);

    const std::uint8_t aNonceBytes[24] = {
        static_cast<std::uint8_t>(aNonceWordA >>  0U),
        static_cast<std::uint8_t>(aNonceWordA >>  8U),
        static_cast<std::uint8_t>(aNonceWordA >> 16U),
        static_cast<std::uint8_t>(aNonceWordA >> 24U),
        static_cast<std::uint8_t>(aNonceWordA >> 32U),
        static_cast<std::uint8_t>(aNonceWordA >> 40U),
        static_cast<std::uint8_t>(aNonceWordA >> 48U),
        static_cast<std::uint8_t>(aNonceWordA >> 56U),

        static_cast<std::uint8_t>(aNonceWordB >>  0U),
        static_cast<std::uint8_t>(aNonceWordB >>  8U),
        static_cast<std::uint8_t>(aNonceWordB >> 16U),
        static_cast<std::uint8_t>(aNonceWordB >> 24U),
        static_cast<std::uint8_t>(aNonceWordB >> 32U),
        static_cast<std::uint8_t>(aNonceWordB >> 40U),
        static_cast<std::uint8_t>(aNonceWordB >> 48U),
        static_cast<std::uint8_t>(aNonceWordB >> 56U),

        static_cast<std::uint8_t>(aNonceWordC >>  0U),
        static_cast<std::uint8_t>(aNonceWordC >>  8U),
        static_cast<std::uint8_t>(aNonceWordC >> 16U),
        static_cast<std::uint8_t>(aNonceWordC >> 24U),
        static_cast<std::uint8_t>(aNonceWordC >> 32U),
        static_cast<std::uint8_t>(aNonceWordC >> 40U),
        static_cast<std::uint8_t>(aNonceWordC >> 48U),
        static_cast<std::uint8_t>(aNonceWordC >> 56U),
    };

    std::memcpy(pNonceLane, aNonceBytes, sizeof(aNonceBytes));

    std::size_t aFilled = sizeof(aNonceBytes);
    while (aFilled < static_cast<std::size_t>(S_BLOCK)) {
        std::size_t aChunk = aFilled;
        if ((aFilled + aChunk) > static_cast<std::size_t>(S_BLOCK)) {
            aChunk = static_cast<std::size_t>(S_BLOCK) - aFilled;
        }
        std::memcpy(pNonceLane + aFilled,
                    pNonceLane,
                    aChunk);
        aFilled += aChunk;
    }
}

void TwistExpander::Zero() {
    Zero_PostSeed();
    mDomainBundleInbuilt.Zero();
}

void TwistExpander::Zero_PostSeed() {
    mDomainBundleEphemeral.Zero();
}
