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
    
    mOutputDirectoryPassers = "_sbox_permuted_filter/";
    //mOutputDirectoryPassers = "good_noisers/";
    
    mOutputFilePrefix = "sbox_scanned_";
    mOutputFileExtension = ".bin";
    mOutputFileDigitCount = 6;
    
    mStringsPerOutputFilePassers = 256;
    
    mFileIndexPassers = 0;
    
}

void SBoxMaterial::AddPasser(const std::vector<std::uint8_t> &pBox) {
    mListPassers.push_back(pBox);
    if (mListPassers.size() >= mStringsPerOutputFilePassers) {
        WriteOutPassers();
    }
}

bool SBoxMaterial::WriteOutPasser(std::vector<std::vector<std::uint8_t>> &mList) {
    if (mList.size() <= 0) {
        return true;
    }
    
    std::vector<std::uint8_t> aFileContent;

    for (const std::vector<std::uint8_t> &aString : mList) {
        aFileContent.insert(aFileContent.end(),
                            aString.begin(),
                            aString.end());
    }
    
    std::string aFileName = FileIO::SequenceFile(mOutputFilePrefix,
                                                 static_cast<int>(mFileIndexPassers),
                                                 mOutputFileExtension,
                                                 static_cast<int>(mOutputFileDigitCount));
    std::string aFilePath = FileIO::ProjectRoot(FileIO::Join(mOutputDirectoryPassers, aFileName));
    if (FileIO::Save(aFilePath, aFileContent.data(), (int)aFileContent.size())) {
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
