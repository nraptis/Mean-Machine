//
//  TwistExpander.cpp
//  MeanMachine
//

#include "TwistExpander.hpp"
#include "TwistFarmSalt.hpp"

#include <cstdio>
#include <cstring>

TwistExpander::TwistExpander() {
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
    (void)pNonce;
    (void)pDomainConstants;
    (void)pDomainSaltSet;
}

void TwistExpander::KDF_A(TwistWorkSpace *pWorkSpace,
                          std::uint64_t pNonce,
                          TwistDomainConstants *pDomainConstants,
                          TwistDomainSaltSet *pDomainSaltSet,
                          std::uint8_t *pSnowLaneA,
                          std::uint8_t *pSnowLaneB,
                          std::uint8_t *pSnowLaneC,
                          MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pSnowLaneA;
    (void)pSnowLaneB;
    (void)pSnowLaneC;
    (void)pPrevious;
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
                          std::uint8_t *pSnowLaneA,
                          std::uint8_t *pSnowLaneB,
                          std::uint8_t *pSnowLaneC,
                          MUTABLE_PARAMS) {
    TwistExpander::KDF_A(pWorkSpace, pNonce, pDomainConstants, pDomainSaltSet,
                         pSnowLaneA, pSnowLaneB, pSnowLaneC,
                         pPrevious, pIngress, pCarry,
                         pWandererA, pWandererB, pWandererC, pWandererD,
                         pWandererE, pWandererF, pWandererG, pWandererH,
                         pWandererI, pWandererJ, pWandererK);
}

void TwistExpander::KDF_C(TwistWorkSpace *pWorkSpace,
                          std::uint64_t pNonce,
                          TwistDomainConstants *pDomainConstants,
                          TwistDomainSaltSet *pDomainSaltSet,
                          std::uint8_t *pSnowLaneA,
                          std::uint8_t *pSnowLaneB,
                          std::uint8_t *pSnowLaneC,
                          MUTABLE_PARAMS) {
    TwistExpander::KDF_A(pWorkSpace, pNonce, pDomainConstants, pDomainSaltSet,
                         pSnowLaneA, pSnowLaneB, pSnowLaneC,
                         pPrevious, pIngress, pCarry,
                         pWandererA, pWandererB, pWandererC, pWandererD,
                         pWandererE, pWandererF, pWandererG, pWandererH,
                         pWandererI, pWandererJ, pWandererK);
}

void TwistExpander::KDF_D(TwistWorkSpace *pWorkSpace,
                          std::uint64_t pNonce,
                          TwistDomainConstants *pDomainConstants,
                          TwistDomainSaltSet *pDomainSaltSet,
                          std::uint8_t *pSnowLaneA,
                          std::uint8_t *pSnowLaneB,
                          std::uint8_t *pSnowLaneC,
                          MUTABLE_PARAMS) {
    TwistExpander::KDF_A(pWorkSpace, pNonce, pDomainConstants, pDomainSaltSet,
                         pSnowLaneA, pSnowLaneB, pSnowLaneC,
                         pPrevious, pIngress, pCarry,
                         pWandererA, pWandererB, pWandererC, pWandererD,
                         pWandererE, pWandererF, pWandererG, pWandererH,
                         pWandererI, pWandererJ, pWandererK);
}

void TwistExpander::Seed(TwistWorkSpace *pWorkSpace,
                         TwistFarmSalt *pFarmSalt,
                         std::uint64_t pNonce,
                         std::uint8_t *pPassword,
                         std::size_t pPasswordByteLength,
                         std::uint8_t *pSnowLaneA,
                         std::uint8_t *pSnowLaneB,
                         std::uint8_t *pSnowLaneC,
                         std::uint8_t *pSnowLaneD,
                         std::uint8_t *pDestination) {
    (void)pNonce;
    if (pWorkSpace == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires workspace\n");
        return;
    }
    if (pDestination == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires destination buffer\n");
        return;
    }
    if (pFarmSalt == nullptr) {
        std::printf("fatal: TwistExpander::Seed requires farm salt PoisonLane\n");
        return;
    }
    if ((pSnowLaneA == nullptr) ||
        (pSnowLaneB == nullptr) ||
        (pSnowLaneC == nullptr) ||
        (pSnowLaneD == nullptr)) {
        std::printf("fatal: TwistExpander::Seed requires four snow lanes\n");
        return;
    }

    UnrollPasswordToSource(pWorkSpace->mSource, pPassword, pPasswordByteLength);
    mDomainBundleEphemeral.Zero();
    pWorkSpace->mDomainBundle.Zero();
}

void TwistExpander::TwistBlock(TwistWorkSpace *pWorkSpace,
                               std::uint8_t *pSource,
                               std::uint8_t *pSnowLaneA,
                               std::uint8_t *pSnowLaneB,
                               std::uint8_t *pSnowLaneC,
                               std::uint8_t *pSnowLaneD,
                               std::uint8_t *pDestination) {
    if ((pWorkSpace == nullptr) ||
        (pSource == nullptr) ||
        (pSnowLaneA == nullptr) ||
        (pSnowLaneB == nullptr) ||
        (pSnowLaneC == nullptr) ||
        (pSnowLaneD == nullptr) ||
        (pDestination == nullptr)) {
        return;
    }

}

void TwistExpander::FoldSeed(TwistWorkSpace *pWorkSpace,
                             std::uint8_t *pDestination) {
    (void)pWorkSpace;
    (void)pDestination;
}

void TwistExpander::FoldTwist(TwistWorkSpace *pWorkSpace,
                              std::uint8_t *pDestination) {
    (void)pWorkSpace;
    (void)pDestination;
}

void TwistExpander::GrowKeyA(TwistWorkSpace *pWorkSpace,
                             MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pPrevious;
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
    (void)pPrevious;
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
                          std::uint8_t *pSnowLaneA,
                          std::uint8_t *pSnowLaneB,
                          std::uint8_t *pSnowLaneC,
                          std::uint8_t *pSnowLaneD,
                          std::uint8_t *pDestination,
                          std::size_t pDestinationByteLength) {
    if ((pWorkSpace == nullptr) ||
        (pSource == nullptr) ||
        (pSnowLaneA == nullptr) ||
        (pSnowLaneB == nullptr) ||
        (pSnowLaneC == nullptr) ||
        (pSnowLaneD == nullptr) ||
        (pDestination == nullptr)) {
        std::printf("fatal: TwistExpander::Twist requires workspace/source/snow lanes/destination\n");
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
                   pSnowLaneA,
                   pSnowLaneB,
                   pSnowLaneC,
                   pSnowLaneD,
                   pDestination + aStartByte);
    }
    
}

void TwistExpander::AutoSeedThenTwist(TwistWorkSpace *pWorkSpace,
                                      TwistFarmSalt *pFarmSalt,
                                      std::uint64_t pNonce,
                                      std::uint8_t *pPassword,
                                      std::size_t pPasswordByteLength,
                                      std::uint8_t *pSnowLaneA,
                                      std::uint8_t *pSnowLaneB,
                                      std::uint8_t *pSnowLaneC,
                                      std::uint8_t *pSnowLaneD,
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
         pSnowLaneA,
         pSnowLaneB,
         pSnowLaneC,
         pSnowLaneD,
         pDestination);
    
    std::size_t aDestinationIndex = S_BLOCK;
    while (aDestinationIndex < pDestinationByteLength) {
        TwistBlock(pWorkSpace,
                   &pDestination[aDestinationIndex - S_BLOCK], // source
                   pSnowLaneA,
                   pSnowLaneB,
                   pSnowLaneC,
                   pSnowLaneD,
                   &pDestination[aDestinationIndex]); // dest
        aDestinationIndex += S_BLOCK;
    }
    
}

// Assumes the work space is seeded...
void TwistExpander::AutoTwist(TwistWorkSpace *pWorkSpace,
                              std::uint8_t *pSource,
                              std::uint8_t *pSnowLaneA,
                              std::uint8_t *pSnowLaneB,
                              std::uint8_t *pSnowLaneC,
                              std::uint8_t *pSnowLaneD,
                              std::uint8_t *pDestination,
                              std::size_t pDestinationByteLength) {
    
    TwistBlock(pWorkSpace,
               pSource,
               pSnowLaneA,
               pSnowLaneB,
               pSnowLaneC,
               pSnowLaneD,
               pDestination); // dest
    
    std::size_t aDestinationIndex = S_BLOCK;
    while (aDestinationIndex < pDestinationByteLength) {
        TwistBlock(pWorkSpace,
                   &pDestination[aDestinationIndex - S_BLOCK], // source
                   pSnowLaneA,
                   pSnowLaneB,
                   pSnowLaneC,
                   pSnowLaneD,
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
}

void TwistExpander::Zero_PostSeed() {
    memset(mIndexList256A, 0, sizeof(mIndexList256A));
    memset(mIndexList256B, 0, sizeof(mIndexList256B));
    memset(mIndexList256C, 0, sizeof(mIndexList256C));
    memset(mIndexList256D, 0, sizeof(mIndexList256D));
    mDomainBundleEphemeral.Zero();
}
