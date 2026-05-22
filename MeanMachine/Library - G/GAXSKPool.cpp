//
//  GAXSKPool.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#include "GAXSKPool.hpp"
#include "Random.hpp"
#include "TwistWorkSpace.hpp"
#include "TwistArray.hpp"

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

    const int aMinNoncesIngress = 2;
    const int aMaxNoncesIngress = 3;
    const int aMinNoncesCross = 2;
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
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceA);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceA);
    } else if (mSourceCount == 2) {
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceB);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceB);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceA);
    } else if (mSourceCount == 3) {
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceB);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceC);
        if (Random::Bool()) {
            mSourcesCross.push_back(GAXSKSourceKind::kSourceB);
        } else {
            mSourcesCross.push_back(GAXSKSourceKind::kSourceA);
        }
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

bool GAXSKPool::GenerateInputSlotOrdering(GAXSKInputSlotOrdering *pResult,
                                          std::string *pErrorMessage) {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSKPool::GenerateInputSlotOrdering received null result");
        return false;
    }

    pResult->mIngress.clear();
    pResult->mCross.clear();

    std::vector<GAXSKInputSlot> aIngress;
    std::vector<GAXSKInputSlot> aCross;

    for (std::size_t i = 0U; i < mNoncesIngress.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kNonceByte;
        aSlot.mSource = GAXSKSourceKind::kInvalid;
        aSlot.mNonceByte = mNoncesIngress[i];
        aSlot.mRotation = 0;
        aSlot.mReverse = false;
        aSlot.mOffset = 0;
        aIngress.push_back(aSlot);
    }

    for (std::size_t i = 0U; i < mSourcesIngress.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kSource;
        aSlot.mSource = mSourcesIngress[i];
        aSlot.mNonceByte = GAXSKNonceByteKind::kInvalid;
        aSlot.mRotation = 0;
        aSlot.mReverse = false;
        aSlot.mOffset = 0;
        aIngress.push_back(aSlot);
    }

    for (std::size_t i = 0U; i < mNoncesCross.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kNonceByte;
        aSlot.mSource = GAXSKSourceKind::kInvalid;
        aSlot.mNonceByte = mNoncesCross[i];
        aSlot.mRotation = 0;
        aSlot.mReverse = false;
        aSlot.mOffset = 0;
        aCross.push_back(aSlot);
    }

    for (std::size_t i = 0U; i < mSourcesCross.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kSource;
        aSlot.mSource = mSourcesCross[i];
        aSlot.mNonceByte = GAXSKNonceByteKind::kInvalid;
        aSlot.mRotation = 0;
        aSlot.mReverse = true;
        aSlot.mOffset = 0;
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

    static const std::vector<int> kGAXSKOddRotations = {
        3, 5, 11, 13, 19, 21, 23, 27, 29,
        35, 37, 39, 41, 43, 47, 51, 53, 57
    };

    static const std::vector<int> kGAXSKEvenRotations = {
        4, 6, 10, 12, 14, 18, 20, 22, 24, 26, 28,
        30, 34, 36, 38, 40, 42, 44, 46, 48, 50,
        52, 54, 56, 58, 60
    };

    auto IsSmallRotation = [](int pRotation) -> bool {
        return pRotation <= 6;
    };

    auto CountSmallRotations = [&](const std::vector<int> &pRotations) -> int {
        int aCount = 0;
        for (int aRotation : pRotations) {
            if (IsSmallRotation(aRotation)) {
                aCount++;
            }
        }
        return aCount;
    };

    auto AssignRotations = [&](std::vector<GAXSKInputSlot> *pList,
                               const char *pErrorText) -> bool {
        if (pList == nullptr) {
            SetError(pErrorMessage, "GAXSKPool::GenerateInputSlotOrdering received null rotation list");
            return false;
        }

        const int aCount = static_cast<int>(pList->size());
        if (aCount <= 0) {
            SetError(pErrorMessage, pErrorText);
            return false;
        }

        std::vector<bool> aIsEven;
        std::vector<int> aRotations;

        aIsEven.resize(static_cast<std::size_t>(aCount), false);
        aRotations.resize(static_cast<std::size_t>(aCount), 0);

        // Exactly one even rotation per ingress/cross expression.
        aIsEven[static_cast<std::size_t>(Random::Get(aCount))] = true;

        int aTryCount = 0;

        do {
            for (int i = 0; i < aCount; i++) {
                if (aIsEven[static_cast<std::size_t>(i)]) {
                    aRotations[static_cast<std::size_t>(i)] = Random::Choice(kGAXSKEvenRotations);
                } else {
                    aRotations[static_cast<std::size_t>(i)] = Random::Choice(kGAXSKOddRotations);
                }
            }

            aTryCount++;
            if (aTryCount > 10000) {
                SetError(pErrorMessage, pErrorText);
                return false;
            }

        } while (GAXSK::RotationsClash_64_8(aRotations) ||
                 (CountSmallRotations(aRotations) > 1));

        for (int i = 0; i < aCount; i++) {
            (*pList)[static_cast<std::size_t>(i)].mRotation =
                aRotations[static_cast<std::size_t>(i)];
        }

        return true;
    };

    if (!AssignRotations(&aIngress,
                         "GAXSKPool::GenerateInputSlotOrdering failed to choose ingress rotations")) {
        return false;
    }

    if (!AssignRotations(&aCross,
                         "GAXSKPool::GenerateInputSlotOrdering failed to choose cross rotations")) {
        return false;
    }

    std::vector<int> aOffsets;
    aOffsets.resize(4U);

    do {
        aOffsets[0] = Random::Get(1, S_BLOCK1);
        aOffsets[1] = Random::Get(1, S_BLOCK1);
        aOffsets[2] = Random::Get(1, S_BLOCK1);
        aOffsets[3] = Random::Get(1, S_BLOCK1);
    } while (TwistArray::AnyEqual(&aOffsets));

    const int aOffsetIngressA = aOffsets[0];
    const int aOffsetIngressB = aOffsets[1];
    const int aOffsetCrossA = aOffsets[2];
    const int aOffsetCrossB = aOffsets[3];
    
    const bool aLockDirections = (mSourceCount <= 2);

    int aIngressSourceCount = 0;
    for (std::size_t i = 0U; i < aIngress.size(); i++) {
        if (aIngress[i].mKind != GAXSKInputSlotKind::kSource) {
            continue;
        }


        // Ingress source slots.
        if (aIngressSourceCount == 0) {
            aIngress[i].mReverse = false;
            aIngress[i].mOffset = aOffsetIngressA;
        } else {
            aIngress[i].mReverse = aLockDirections ? false : Random::Bool();
            aIngress[i].mOffset = aOffsetIngressB;
        }

        aIngressSourceCount++;
    }

    int aCrossSourceCount = 0;
    for (std::size_t i = 0U; i < aCross.size(); i++) {
        if (aCross[i].mKind != GAXSKInputSlotKind::kSource) {
            continue;
        }

        // Cross source slots.
        if (aCrossSourceCount == 0) {
            aCross[i].mReverse = true;
            aCross[i].mOffset = aOffsetCrossA;
        } else {
            aCross[i].mReverse = aLockDirections ? true : Random::Bool();
            aCross[i].mOffset = aOffsetCrossB;
        }

        aCrossSourceCount++;
    }

    pResult->mIngress = aIngress;
    pResult->mCross = aCross;

    return true;
}
