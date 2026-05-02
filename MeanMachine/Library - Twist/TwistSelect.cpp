//
//  TwistSelect.cpp
//  MeanMachine
//
//  Created by Dragon on 4/30/26.
//

#include "TwistSelect.hpp"


TwistSelectRange::TwistSelectRange() {
    
    mLo = 0;
    mHi = 0;
}

TwistSelectResult4::TwistSelectResult4() {
    mMask = 0;
}

TwistSelectResult2::TwistSelectResult2() {
    mMask = 0;
}

std::vector<TwistSelectResult2> TwistSelect::GetAll2() {
    
    std::vector<TwistSelectResult2> aResult;
    auto Add = [&](uint8_t pMask, int pLoA, int pHiA) {
        TwistSelectResult2 aItem;
        aItem.mMask = pMask;
        aItem.mRangeA.mLo = pLoA;
        aItem.mRangeA.mHi = pHiA;
        aResult.push_back(aItem);
    };
    
    Add(0x0E, 6, 7);
    Add(0x16, 6, 15);
    Add(0x1A, 10, 15);
    Add(0x1C, 12, 15);
    Add(0x1E, 14, 15);
    Add(0x26, 6, 31);
    Add(0x2A, 10, 31);
    Add(0x2C, 12, 31);
    Add(0x2E, 14, 31);
    Add(0x32, 18, 31);
    Add(0x34, 20, 31);
    Add(0x36, 22, 31);
    Add(0x38, 24, 31);
    Add(0x3A, 26, 31);
    Add(0x3C, 28, 31);
    Add(0x3E, 30, 31);
    Add(0x46, 6, 63);
    Add(0x4A, 10, 63);
    Add(0x4C, 12, 63);
    Add(0x4E, 14, 63);
    Add(0x52, 18, 63);
    Add(0x54, 20, 63);
    Add(0x56, 22, 63);
    Add(0x58, 24, 63);
    Add(0x5A, 26, 63);
    Add(0x5C, 28, 63);
    Add(0x5E, 30, 63);
    Add(0x62, 34, 63);
    Add(0x64, 36, 63);
    Add(0x66, 38, 63);
    Add(0x68, 40, 63);
    Add(0x6A, 42, 63);
    Add(0x6C, 44, 63);
    Add(0x6E, 46, 63);
    Add(0x70, 48, 63);
    Add(0x72, 50, 63);
    Add(0x74, 52, 63);
    Add(0x76, 54, 63);
    Add(0x78, 56, 63);
    Add(0x7A, 58, 63);
    Add(0x7C, 60, 63);
    return aResult;
}

std::vector<TwistSelectResult4> TwistSelect::GetAll4() {
    
    std::vector<TwistSelectResult4> aResult;
    
    auto Add = [&](uint8_t pMask,
                   int pLoA, int pHiA,
                   int pLoB, int pHiB,
                   int pLoC, int pHiC) {
        TwistSelectResult4 aItem;
        aItem.mMask = pMask;
        aItem.mRangeA.mLo = pLoA;
        aItem.mRangeA.mHi = pHiA;
        aItem.mRangeB.mLo = pLoB;
        aItem.mRangeB.mHi = pHiB;
        aItem.mRangeC.mLo = pLoC;
        aItem.mRangeC.mHi = pHiC;
        aResult.push_back(aItem);
    };
    
    Add(0x06, 0,1, 2,3, 4,5);
    Add(0x0A, 0,1, 2,7, 8,9);
    Add(0x0C, 0,3, 4,7, 8,11);
    Add(0x12, 0,1, 2,15, 16,17);
    Add(0x14, 0,3, 4,15, 16,19);
    Add(0x18, 0,7, 8,15, 16,23);
    Add(0x22, 0,1, 2,31, 32,33);
    Add(0x24, 0,3, 4,31, 32,35);
    Add(0x28, 0,7, 8,31, 32,39);
    Add(0x30, 0,15, 16,31, 32,47);
    Add(0x42, 0,1, 2,63, 64,65);
    Add(0x44, 0,3, 4,63, 64,67);
    Add(0x48, 0,7, 8,63, 64,71);
    Add(0x50, 0,15, 16,63, 64,79);
    Add(0x60, 0,31, 32,63, 64,95);
    return aResult;
}
