//
//  SixELSixELRig.cpp
//  MeanMachine
//
//  Created by nicholas on 5/24/26.
//

#include "SixELRig.hpp"
#include <cctype>
#include <cstdio>

SixELRig::SixELRig() {
    mData = NULL;
    mDataLength = 0;
    mRoundCount = 0;
    mLastPasswordTag = "";
    std::memset(mSource, 0, S_BLOCK);
}

SixELRig::~SixELRig() {
    delete [] mData;
    mData = NULL;
}

void SixELRig::SetRoundCount(int pRoundCount) {
    delete [] mData;
    mData = NULL;
    mDataLength = 0;
    mRoundCount = 0;

    if (pRoundCount > 0) {
        mDataLength = static_cast<std::size_t>(pRoundCount) * 4U * S_BLOCK;
        mData = new std::uint8_t[mDataLength];
        std::memset(mData, 0, mDataLength);
        mRoundCount = static_cast<std::size_t>(pRoundCount);
    }
}

void SixELRig::Run(TwistExpander *pExpander,
                   std::uint8_t *pPassword,
                   int pPasswordLength) {
    if ((pExpander == nullptr) || (mData == nullptr) || (mRoundCount <= 0)) {
        return;
    }

    std::memset(mSource, 0, S_BLOCK);
    pExpander->UnrollPasswordToSource(mSource, pPassword, pPasswordLength);

    pExpander->mWorkspace = &mWorkSpace;
    pExpander->mSource = mSource;
    pExpander->mDest = mData;

    for (std::size_t aRound = 0; aRound < mRoundCount; ++aRound) {
        pExpander->KDF_A(0ULL,
                         &mWorkSpace.mDomainBundle.mPhaseAConstants,
                         &mWorkSpace.mDomainBundle.mPhaseASalts);

        std::uint8_t *aDest = mData + (aRound * 4 * S_BLOCK);

        
        std::memcpy(aDest + 0 * S_BLOCK, mWorkSpace.mExpansionLaneA, S_BLOCK);
        std::memcpy(aDest + 1 * S_BLOCK, mWorkSpace.mExpansionLaneB, S_BLOCK);
        std::memcpy(aDest + 2 * S_BLOCK, mWorkSpace.mExpansionLaneC, S_BLOCK);
        std::memcpy(aDest + 3 * S_BLOCK, mWorkSpace.mExpansionLaneD, S_BLOCK);
        
        /*
        std::memcpy(aDest + 0 * S_BLOCK, mWorkSpace.mWorkLaneA, S_BLOCK);
        std::memcpy(aDest + 1 * S_BLOCK, mWorkSpace.mWorkLaneB, S_BLOCK);
        std::memcpy(aDest + 2 * S_BLOCK, mWorkSpace.mWorkLaneC, S_BLOCK);
        std::memcpy(aDest + 3 * S_BLOCK, mWorkSpace.mWorkLaneD, S_BLOCK);
        */
        
        /*
        
        
        
        
        
        
        
        std::memcpy(aDest + 0 * S_BLOCK, mWorkSpace.mOperationLaneA, S_BLOCK);
        std::memcpy(aDest + 1 * S_BLOCK, mWorkSpace.mOperationLaneB, S_BLOCK);
        std::memcpy(aDest + 2 * S_BLOCK, mWorkSpace.mOperationLaneC, S_BLOCK);
        std::memcpy(aDest + 3 * S_BLOCK, mWorkSpace.mOperationLaneD, S_BLOCK);
        */

        std::memcpy(mSource, aDest + 3 * S_BLOCK, S_BLOCK);
        
        
    }
}

bool SixELRig::SaveByteStream(const std::string &pFolder) const {
    if ((mData == nullptr) || (mDataLength <= 0)) { return false; }
    const std::string aPath = FileIO::Join(pFolder, "byte_stream.bin");
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}

bool SixELRig::SaveByteStreamProjectRoot(const std::string &pFolder) const {
    if ((mData == nullptr) || (mDataLength <= 0)) { return false; }
    const std::string aPath = FileIO::ProjectRoot(FileIO::Join(pFolder, "byte_stream.bin"));
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}

bool SixELRig::SaveByteStreamLastAsciiPassword(const std::string &pFolder) const {
    if ((mData == nullptr) || (mDataLength <= 0)) { return false; }
    const std::string aFileName = "byte_stream_" + (mLastPasswordTag.empty() ? std::string("empty") : mLastPasswordTag) + ".bin";
    const std::string aPath = FileIO::Join(pFolder, aFileName);
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}

bool SixELRig::SaveByteStreamProjectRootLastAsciiPassword(const std::string &pFolder) const {
    if ((mData == nullptr) || (mDataLength <= 0)) { return false; }
    const std::string aFileName = "byte_stream_" + (mLastPasswordTag.empty() ? std::string("empty") : mLastPasswordTag) + ".bin";
    const std::string aPath = FileIO::ProjectRoot(FileIO::Join(pFolder, aFileName));
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}

bool SixELRig::SaveByteStream(const std::string &pFolder,
                         const std::string &pBaseFile,
                         int pFileNumber) const {
    if ((mData == nullptr) || (mDataLength <= 0) || pBaseFile.empty()) { return false; }
    std::string aBase = pBaseFile;
    if ((aBase.size() > 4) && (aBase.substr(aBase.size() - 4) == ".bin")) {
        aBase = aBase.substr(0, aBase.size() - 4);
    }
    const std::string aFileName = FileIO::SequenceFile(aBase + "_", pFileNumber, ".bin", 6);
    const std::string aPath = FileIO::Join(pFolder, aFileName);
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}

bool SixELRig::SaveByteStreamProjectRoot(const std::string &pFolder,
                                    const std::string &pBaseFile,
                                    int pFileNumber) const {
    if ((mData == nullptr) || (mDataLength <= 0) || pBaseFile.empty()) { return false; }
    std::string aBase = pBaseFile;
    if ((aBase.size() > 4) && (aBase.substr(aBase.size() - 4) == ".bin")) {
        aBase = aBase.substr(0, aBase.size() - 4);
    }
    const std::string aFileName = FileIO::SequenceFile(aBase + "_", pFileNumber, ".bin", 6);
    const std::string aPath = FileIO::ProjectRoot(FileIO::Join(pFolder, aFileName));
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}
