//
//  GAXSKPool.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#include "GAXSKPool.hpp"
#include "Random.hpp"
#include "TwistWorkSpace.hpp"


namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

}

GAXSKPool::GAXSKPool() {
    
}

void GAXSKPool::SetSourceCount(int pSourceCount) {
    mSourceCount = pSourceCount;
}

void GAXSKPool::SetOrbiterCount(int pOrbiterCount) {
    mOrbiterCount = pOrbiterCount;
}

void GAXSKPool::SetWandererCount(int pWandererCount) {
    mWandererCount = pWandererCount;
}

bool GAXSKPool::FinalizeCounts(std::string *pErrorMessage) {
    mNoncesIngress.clear();
    mSourcesIngress.clear();
    mNoncesCross.clear();
    mSourcesCross.clear();
    mNoncesOrbiterUpdate.clear();
    mNoncesWandererUpdate.clear();
    
    if (mOrbiterCount <= 0) {
        SetError(pErrorMessage, "GAXSKPool::FinalizeCounts received invalid orbiter count");
        return false;
    }

    if (mWandererCount <= 0) {
        SetError(pErrorMessage, "GAXSKPool::FinalizeCounts received invalid wanderer count");
        return false;
    }

    std::vector<GAXSKNonceByteKind> aNonces;
    aNonces.push_back(GAXSKNonceByteKind::kNonceA);
    aNonces.push_back(GAXSKNonceByteKind::kNonceB);
    aNonces.push_back(GAXSKNonceByteKind::kNonceC);
    aNonces.push_back(GAXSKNonceByteKind::kNonceD);
    aNonces.push_back(GAXSKNonceByteKind::kNonceE);
    aNonces.push_back(GAXSKNonceByteKind::kNonceF);
    aNonces.push_back(GAXSKNonceByteKind::kNonceG);
    aNonces.push_back(GAXSKNonceByteKind::kNonceH);

    const int aMinNoncesIngress = 1;
    const int aMaxNoncesIngress = 3;
    const int aMinNoncesCross = 1;
    const int aMaxNoncesCross = 3;
    const int aMinNoncesOrbiterUpdate = 1;
    int aMaxNoncesOrbiterUpdate = mOrbiterCount;
    const int aMinNoncesWandererUpdate = 1;
    int aMaxNoncesWandererUpdate = mWandererCount;

    int aNonceCountIngress = Random::Get(aMinNoncesIngress, aMaxNoncesIngress);
    int aNonceCountCross = Random::Get(aMinNoncesCross, aMaxNoncesCross);
    int aNonceCountOrbiterUpdate = aMinNoncesOrbiterUpdate;
    int aNonceCountWandererUpdate = aMinNoncesWandererUpdate;

    int aRemainingNonces = 8 - aNonceCountIngress - aNonceCountCross - aNonceCountOrbiterUpdate - aNonceCountWandererUpdate;
    while (aRemainingNonces > 0) {
        if (aNonceCountOrbiterUpdate < aMaxNoncesOrbiterUpdate) {
            if (aNonceCountWandererUpdate < aMaxNoncesWandererUpdate) {
                if (Random::Bool()) {
                    aNonceCountOrbiterUpdate++;
                    aRemainingNonces--;
                } else {
                    aNonceCountWandererUpdate++;
                    aRemainingNonces--;
                }
            } else {
                aNonceCountOrbiterUpdate++;
                aRemainingNonces--;
            }
        } else if (aNonceCountWandererUpdate < aMaxNoncesWandererUpdate) {
            aNonceCountWandererUpdate++;
            aRemainingNonces--;
        } else {
            SetError(pErrorMessage, "GAXSKPool::FinalizeCounts exhausted nonce capacity");
            return false;
        }
    }
    
    int aNonceIndex = 0;
    for (int i=0; i<aNonceCountIngress; i++) { mNoncesIngress.push_back(aNonces[aNonceIndex++]); }
    for (int i=0; i<aNonceCountCross; i++) { mNoncesCross.push_back(aNonces[aNonceIndex++]); }
    for (int i=0; i<aNonceCountOrbiterUpdate; i++) { mNoncesOrbiterUpdate.push_back(aNonces[aNonceIndex++]); }
    for (int i=0; i<aNonceCountWandererUpdate; i++) { mNoncesWandererUpdate.push_back(aNonces[aNonceIndex++]); }

    const int aTotalNonceCount = aNonceCountIngress + aNonceCountCross + aNonceCountOrbiterUpdate + aNonceCountWandererUpdate;
    
    if (aTotalNonceCount != 8) {
        SetError(pErrorMessage, "GAXSKPool::FinalizeCounts failed to allocate exactly 8 nonce bytes");
        return false;
    }
    
    if (mSourceCount == 1) {
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceA);
    } else if (mSourceCount == 2) {
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceB);
    } else if (mSourceCount == 3) {
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceB);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceC);
    } else if (mSourceCount == 4) {
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceB);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceC);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceD);
    } else {
        SetError(pErrorMessage, "GAXSKPool::FinalizeCounts source count must be 1, 2, 3, or 4");
        return false;
    }
    
    return true;
}

bool GAXSKPool::GenerateInputSlotOrdering(GAXSKInputSlotOrdering *pResult, std::string *pErrorMessage) {
    
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSKPool::GenerateInputSlotOrdering received null result");
        return false;
    }
    
    pResult->mIngress.clear();
    pResult->mCross.clear();
    
    std::vector<GAXSKInputSlot> aIngress;
    std::vector<GAXSKInputSlot> aCross;
    
    for (int i = 0; i < mNoncesIngress.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kNonceByte;
        aSlot.mSource = GAXSKSourceKind::kInvalid;
        aSlot.mNonceByte = mNoncesIngress[i];
        aIngress.push_back(aSlot);
    }
    
    for (int i = 0; i < mSourcesIngress.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kSource;
        aSlot.mSource = mSourcesIngress[i];
        aSlot.mNonceByte = GAXSKNonceByteKind::kInvalid;
        aIngress.push_back(aSlot);
    }
    
    for (int i = 0; i < mNoncesCross.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kNonceByte;
        aSlot.mSource = GAXSKSourceKind::kInvalid;
        aSlot.mNonceByte = mNoncesCross[i];
        aCross.push_back(aSlot);
    }
    
    for (int i = 0; i < mSourcesCross.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kSource;
        aSlot.mSource = mSourcesCross[i];
        aSlot.mNonceByte = GAXSKNonceByteKind::kInvalid;
        aCross.push_back(aSlot);
    }
    
    if (aIngress.empty()) {
        SetError(pErrorMessage, "GAXSKPool::GenerateInputSlotOrdering produced empty ingress slots");
        return false;
    }
    
    if (aCross.empty()) {
        SetError(pErrorMessage, "GAXSKPool::GenerateInputSlotOrdering produced empty cross slots");
        return false;
    }
    
    std::vector<std::vector<GAXSKInputSlot> *> aLists;
    aLists.push_back(&aIngress);
    aLists.push_back(&aCross);
    
    static const std::vector<int> kGAXSKOddRotations = {
        1, 3, 5, 11, 13, 19, 21, 23, 27, 29, 35, 37, 39, 41, 43, 47, 51, 53, 57
    };

    static const std::vector<int> kGAXSKEvenRotations = {
        2, 4, 6, 10, 12, 14, 18, 20, 22, 24, 26, 28, 30, 34, 36, 38, 40, 42, 44,
        46, 48, 50, 52, 54, 56, 58, 60, 62
    };

    for (int aListIndex=0; aListIndex<aLists.size(); aListIndex++) {
        
        std::vector<GAXSKInputSlot> *aList = aLists[aListIndex];
        
        std::vector<bool> aIsEven;
        std::vector<int> aRotation;
        int aCount = (int)aList->size();
        for (int i=0; i<aCount; i++) {
            aIsEven.push_back(false);
            aRotation.push_back(0);
        }
        aIsEven[Random::Get(aCount)] = true;
        
        do {
            for (int i=0; i<aCount; i++) {
                if (aIsEven[i] == true) {
                    aRotation[i] = Random::Choice(kGAXSKEvenRotations);
                } else {
                    aRotation[i] = Random::Choice(kGAXSKOddRotations);
                }
            }
        } while (GAXSK::RotationsClash_64_8(aRotation));
        
        for (int i = 0; i < aCount; i++) {
            (*aList)[i].mRotation = aRotation[i];
        }
        
        int aOffsetSecondIngress = Random::Get(1, S_BLOCK1);
        int aOffsetSecondCross = Random::Get(1, S_BLOCK1);

        int aIngressSourceCount = 0;
        for (int i=0; i<aIngress.size(); i++) {
            if (aIngress[i].mKind != GAXSKInputSlotKind::kSource) {
                continue;
            }

            aIngress[i].mReverse = false;
            aIngress[i].mOffset = 0;

            if (aIngressSourceCount == 1) {
                aIngress[i].mOffset = aOffsetSecondIngress;

                if (mSourcesIngress.size() > 1) {
                    aIngress[i].mReverse = Random::Bool();
                }
            }

            aIngressSourceCount++;
        }

        int aCrossSourceCount = 0;
        for (int i=0; i<aCross.size(); i++) {
            if (aCross[i].mKind != GAXSKInputSlotKind::kSource) {
                continue;
            }

            aCross[i].mReverse = true;
            aCross[i].mOffset = 0;

            if (aCrossSourceCount == 1) {
                aCross[i].mOffset = aOffsetSecondCross;
            }

            aCrossSourceCount++;
        }
    }
    
    pResult->mIngress = aIngress;
    pResult->mCross = aCross;
    
    return true;
}
