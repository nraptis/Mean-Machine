#include "SBoxMaterial.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <format>
#include <limits>
#include <string>
#include <unistd.h>
#include "FileIO.hpp"

SBoxMaterial::SBoxMaterial() {
    
    mOutputDirectoryPassers = "_sbox_permuted/";
    //mOutputDirectoryPassers = "good_noisers/";
    
    mOutputFilePrefix = "sbox_scanned_";
    mOutputFileExtension = ".bin";
    mOutputFileDigitCount = 6;
    
    mStringsPerOutputFilePassers = 256;
    
    mFileIndexPassers = 0;
    
}

void SBoxMaterial::AddPasser(const ByteString &pString) {
    mListPassers.push_back(pString);
    if (mListPassers.size() >= mStringsPerOutputFilePassers) {
        WriteOutPassers();
    }
}

bool SBoxMaterial::WriteOutPasser(std::vector<ByteString> &mList) {
    if (mList.size() <= 0) {
        return true;
    }
    
    ByteString aFileContent;
    for (const ByteString &aString : mList) {
        aFileContent.Append(aString);
    }
    std::string aFileName = FileIO::SequenceFile(mOutputFilePrefix,
                                                 static_cast<int>(mFileIndexPassers),
                                                 mOutputFileExtension,
                                                 static_cast<int>(mOutputFileDigitCount));
    std::string aFilePath = FileIO::ProjectRoot(FileIO::Join(mOutputDirectoryPassers, aFileName));
    if (FileIO::Save(aFilePath, aFileContent.mData, aFileContent.mLength)) {
        ++mFileIndexPassers;
        return true;
    } else {
        return false;
    }
}



bool SBoxMaterial::WriteOutPassers() {

    if (!mListPassers.empty()) {
        if (WriteOutPasser(mListPassers)) {
            mListPassers.clear();
        } else {
            return false;
        }
    }

    return mListPassers.empty();
}
