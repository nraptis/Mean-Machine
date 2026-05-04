//
//  TwistExpander.cpp
//  MeanMachine
//

#include "TwistExpander.hpp"
#include "TwistCryptoGenerator.hpp"

#include <cstdio>
#include <cstring>

TwistExpander::TwistExpander() {
    mWorkspace = nullptr;
    mSource = nullptr;
    mDest = nullptr;
    std::memset(mSaltA, 0, sizeof(mSaltA));
    std::memset(mSaltB, 0, sizeof(mSaltB));
    std::memset(mSaltC, 0, sizeof(mSaltC));
    std::memset(mSaltD, 0, sizeof(mSaltD));
    std::memset(mScratchSaltA, 0, sizeof(mScratchSaltA));
    std::memset(mScratchSaltB, 0, sizeof(mScratchSaltB));
    std::memset(mScratchSaltC, 0, sizeof(mScratchSaltC));
    std::memset(mScratchSaltD, 0, sizeof(mScratchSaltD));
    std::memset(mSBoxA, 0, sizeof(mSBoxA));
    std::memset(mSBoxB, 0, sizeof(mSBoxB));
    std::memset(mSBoxC, 0, sizeof(mSBoxC));
    std::memset(mSBoxD, 0, sizeof(mSBoxD));
}

TwistExpander::~TwistExpander() {
    
}

void TwistExpander::Seed(TwistWorkSpace *pWorkspace,
                         TwistCryptoGenerator *pCryptoGenerator,
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

    mWorkspace = pWorkspace;
    mSource = pSource;
    mDest = nullptr;
    UnrollPasswordToSource(pSource, pPassword, pPasswordByteLength);
    
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

void TwistExpander::Twist(TwistWorkSpace *pWorkspace,
                          std::uint8_t *pSource,
                          std::uint8_t *pDestination,
                          unsigned int pDestinationByteLength) {
    if ((pWorkspace == nullptr) || (pSource == nullptr) || (pDestination == nullptr)) {\
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
