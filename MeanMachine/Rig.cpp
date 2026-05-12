//
//  Rig.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/4/26.
//

#include "Rig.hpp"
#include <cctype>
#include <cstdio>

Rig::Rig() {
    mData = NULL;
    mDataLength = 0;
    mBlockCount = 0;
    mLastPasswordTag = "";
}

Rig::~Rig() {
    delete [] mData;
    mData = NULL;
}

void Rig::SetBlockCount(int pBlockCount) {
    delete [] mData;
    mData = NULL;
    mDataLength = 0;
    mBlockCount = 0;
    if (pBlockCount > 0) {
        mDataLength = S_BLOCK * pBlockCount;
        mData = new std::uint8_t[mDataLength];
        memset(mData, 0, mDataLength);
        mBlockCount = pBlockCount;
    }    
}

void Rig::Run(TwistExpander *pExpander,
              std::uint8_t *pPassword,
              int pPasswordLength) {
    mLastPasswordTag = "empty";
    if ((pPassword != nullptr) && (pPasswordLength > 0)) {
        bool aAsciiOnly = true;
        for (int i = 0; i < pPasswordLength; i++) {
            const unsigned char aChar = static_cast<unsigned char>(pPassword[i]);
            if ((aChar < 32U) || (aChar > 126U)) {
                aAsciiOnly = false;
                break;
            }
        }

        if (aAsciiOnly) {
            mLastPasswordTag.clear();
            for (int i = 0; i < pPasswordLength; i++) {
                const unsigned char aChar = static_cast<unsigned char>(pPassword[i]);
                if (std::isalnum(aChar) || aChar == '_' || aChar == '-') {
                    mLastPasswordTag.push_back(static_cast<char>(aChar));
                } else {
                    mLastPasswordTag.push_back('_');
                }
            }
            if (mLastPasswordTag.empty()) {
                mLastPasswordTag = "empty";
            }
        } else {
            mLastPasswordTag.clear();
            char aHex[3];
            for (int i = 0; i < pPasswordLength; i++) {
                std::snprintf(aHex, sizeof(aHex), "%02x", static_cast<unsigned char>(pPassword[i]));
                mLastPasswordTag += aHex;
            }
            if (mLastPasswordTag.empty()) {
                mLastPasswordTag = "empty";
            }
        }
    }
    
    TwistWorkSpace aWorkSpace;
    
    std::uint8_t aSource[S_BLOCK];
    memset(aSource, 0, S_BLOCK);
    pExpander->UnrollPasswordToSource(aSource, pPassword, pPasswordLength);
    
    pExpander->TwistBlock(&aWorkSpace,
                     aSource,
                     mData);
    
    for (int aBlockIndex=1; aBlockIndex<mBlockCount; aBlockIndex++) {
        
        std::uint8_t *aSource = mData + (aBlockIndex - 1) * S_BLOCK;
        std::uint8_t *aDest = mData + (aBlockIndex) * S_BLOCK;
        
        
        pExpander->TwistBlock(&aWorkSpace,
                              aSource,
                              aDest);
        
    }
    
    
}

bool Rig::SaveByteStream(const std::string &pFolder) const {
    if ((mData == nullptr) || (mDataLength <= 0)) { return false; }
    const std::string aPath = FileIO::Join(pFolder, "byte_stream.bin");
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}

bool Rig::SaveByteStreamProjectRoot(const std::string &pFolder) const {
    if ((mData == nullptr) || (mDataLength <= 0)) { return false; }
    const std::string aPath = FileIO::ProjectRoot(FileIO::Join(pFolder, "byte_stream.bin"));
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}

bool Rig::SaveByteStreamLastAsciiPassword(const std::string &pFolder) const {
    if ((mData == nullptr) || (mDataLength <= 0)) { return false; }
    const std::string aFileName = "byte_stream_" + (mLastPasswordTag.empty() ? std::string("empty") : mLastPasswordTag) + ".bin";
    const std::string aPath = FileIO::Join(pFolder, aFileName);
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}

bool Rig::SaveByteStreamProjectRootLastAsciiPassword(const std::string &pFolder) const {
    if ((mData == nullptr) || (mDataLength <= 0)) { return false; }
    const std::string aFileName = "byte_stream_" + (mLastPasswordTag.empty() ? std::string("empty") : mLastPasswordTag) + ".bin";
    const std::string aPath = FileIO::ProjectRoot(FileIO::Join(pFolder, aFileName));
    return FileIO::Save(aPath, mData, static_cast<int>(mDataLength));
}

bool Rig::SaveByteStream(const std::string &pFolder,
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

bool Rig::SaveByteStreamProjectRoot(const std::string &pFolder,
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
