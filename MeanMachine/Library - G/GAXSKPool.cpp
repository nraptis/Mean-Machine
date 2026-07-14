//
//  GAXSKPool.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#include "GAX.hpp"
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

int SourceKindIndex(const GAXSKSourceKind pSource) {
    switch (pSource) {
        case GAXSKSourceKind::kSourceA: return 0;
        case GAXSKSourceKind::kSourceB: return 1;
        case GAXSKSourceKind::kSourceC: return 2;
        case GAXSKSourceKind::kSourceD: return 3;
        case GAXSKSourceKind::kSourceE: return 4;
        case GAXSKSourceKind::kSourceF: return 5;
        case GAXSKSourceKind::kSourceG: return 6;
        case GAXSKSourceKind::kSourceH: return 7;
        case GAXSKSourceKind::kSourceI: return 8;
        case GAXSKSourceKind::kSourceJ: return 9;
        default: return -1;
    }
}

bool ValidateExplicitSourceList(const std::vector<GAXSKSourceKind> &pSources,
                                const int pSourceCount,
                                const char *pName,
                                std::string *pErrorMessage) {
    if ((pSources.size() < 2U) || (pSources.size() > 5U)) {
        SetError(pErrorMessage,
                 std::string("GAXSKPool::FinalizeCounts explicit ") +
                 pName + " source count must be between 2 and 5");
        return false;
    }

    for (GAXSKSourceKind aSource : pSources) {
        const int aSourceIndex = SourceKindIndex(aSource);
        if (aSourceIndex < 0) {
            SetError(pErrorMessage,
                     std::string("GAXSKPool::FinalizeCounts explicit ") +
                     pName + " contained invalid source kind");
            return false;
        }

        if (aSourceIndex >= pSourceCount) {
            SetError(pErrorMessage,
                     std::string("GAXSKPool::FinalizeCounts explicit ") +
                     pName + " referenced a source outside the bound source list");
            return false;
        }
    }

    return true;
}

}

GAXSKPool::GAXSKPool() {
    
}

void GAXSKPool::SetSourceCount(int pSourceCount) {
    mSourceCount = pSourceCount;
}

void GAXSKPool::SetSourceLayout(const GAXSKSourceLayout &pSourceLayout) {
    mHasSourceLayout = true;
    mSourceLayout = pSourceLayout;
}

void GAXSKPool::SetOrbiterCount(int pOrbiterCount) {
    mOrbiterCount = pOrbiterCount;
}

void GAXSKPool::SetWandererCount(int pWandererCount) {
    mWandererCount = pWandererCount;
}

bool GAXSKPool::FinalizeCounts(bool pIgnoreNonces,
                               std::string *pErrorMessage) {
    mNoncesIngress.clear();
    mSourcesIngress.clear();
    mNoncesCross.clear();
    mSourcesCross.clear();
    
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
    aNonces.push_back(GAXSKNonceByteKind::kNonceI);
    aNonces.push_back(GAXSKNonceByteKind::kNonceJ);
    aNonces.push_back(GAXSKNonceByteKind::kNonceK);
    aNonces.push_back(GAXSKNonceByteKind::kNonceL);
    aNonces.push_back(GAXSKNonceByteKind::kNonceM);
    aNonces.push_back(GAXSKNonceByteKind::kNonceN);
    aNonces.push_back(GAXSKNonceByteKind::kNonceO);
    aNonces.push_back(GAXSKNonceByteKind::kNonceP);
    Random::Shuffle(&aNonces);

    int aNonceCountIngress = 1;
    int aNonceCountCross = 1;
    
    if (pIgnoreNonces == true) {
        aNonceCountIngress = 0;
        aNonceCountCross = 0;
    }
    
    int aNonceIndex = 0;
    for (int i=0; i<aNonceCountIngress; i++) { mNoncesIngress.push_back(aNonces[aNonceIndex++]); }
    for (int i=0; i<aNonceCountCross; i++) { mNoncesCross.push_back(aNonces[aNonceIndex++]); }

    const int aTotalNonceCount = aNonceCountIngress + aNonceCountCross;
    
    const int aExpectedNonceCount = pIgnoreNonces ? 0 : 2;
    if (aTotalNonceCount != aExpectedNonceCount) {
        SetError(pErrorMessage, "GAXSKPool::FinalizeCounts failed to allocate context nonce byte count");
        return false;
    }
    
    if (mHasSourceLayout) {
        if (!ValidateExplicitSourceList(mSourceLayout.mIngress,
                                        mSourceCount,
                                        "ingress",
                                        pErrorMessage)) {
            return false;
        }

        if (!ValidateExplicitSourceList(mSourceLayout.mCross,
                                        mSourceCount,
                                        "cross",
                                        pErrorMessage)) {
            return false;
        }

        mSourcesIngress = mSourceLayout.mIngress;
        mSourcesCross = mSourceLayout.mCross;
    } else if (mSourceCount == 1) {
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceA);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceA);
    } else if (mSourceCount == 2) {
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceB);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceA);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceB);
    } else if (mSourceCount == 3) {
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceA);
        mSourcesIngress.push_back(GAXSKSourceKind::kSourceB);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceC);
        mSourcesCross.push_back(GAXSKSourceKind::kSourceA);
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
        aIngress.push_back(aSlot);
    }

    for (std::size_t i = 0U; i < mSourcesIngress.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kSource;
        aSlot.mSource = mSourcesIngress[i];
        aSlot.mNonceByte = GAXSKNonceByteKind::kInvalid;
        aSlot.mRotation = 0;
        aSlot.mReverse = false;
        aIngress.push_back(aSlot);
    }

    for (std::size_t i = 0U; i < mNoncesCross.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kNonceByte;
        aSlot.mSource = GAXSKSourceKind::kInvalid;
        aSlot.mNonceByte = mNoncesCross[i];
        aSlot.mRotation = 0;
        aSlot.mReverse = false;
        aCross.push_back(aSlot);
    }

    for (std::size_t i = 0U; i < mSourcesCross.size(); i++) {
        GAXSKInputSlot aSlot;
        aSlot.mKind = GAXSKInputSlotKind::kSource;
        aSlot.mSource = mSourcesCross[i];
        aSlot.mNonceByte = GAXSKNonceByteKind::kInvalid;
        aSlot.mRotation = 0;
        aSlot.mReverse = true;
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

    /*
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
     */
    
    if (mHasSourceLayout) {
        int aIngressSourceCount = 0;
        for (std::size_t i = 0U; i < aIngress.size(); i++) {
            if (aIngress[i].mKind != GAXSKInputSlotKind::kSource) {
                continue;
            }

            const bool aIsRandomDirection =
                !mSourcesIngress.empty() &&
                (static_cast<std::size_t>(aIngressSourceCount) == (mSourcesIngress.size() - 1U)) &&
                !mSourceLayout.mIsLastIngressDirectionLocked;
            aIngress[i].mReverse = aIsRandomDirection ? Random::Bool() : false;
            aIngressSourceCount++;
        }

        int aCrossSourceCount = 0;
        for (std::size_t i = 0U; i < aCross.size(); i++) {
            if (aCross[i].mKind != GAXSKInputSlotKind::kSource) {
                continue;
            }

            const bool aIsRandomDirection =
                !mSourcesCross.empty() &&
                (static_cast<std::size_t>(aCrossSourceCount) == (mSourcesCross.size() - 1U)) &&
                !mSourceLayout.mIsLastCrossDirectionLocked;
            aCross[i].mReverse = aIsRandomDirection ? Random::Bool() : true;
            aCrossSourceCount++;
        }
    } else {
        const bool aLockDirections = (mSourceCount <= 2);

        int aIngressSourceCount = 0;
        for (std::size_t i = 0U; i < aIngress.size(); i++) {
            if (aIngress[i].mKind != GAXSKInputSlotKind::kSource) {
                continue;
            }


            // Ingress source slots.
            if (aIngressSourceCount == 0) {
                aIngress[i].mReverse = false;
                //aIngress[i].mOffset = aOffsetIngressA;
            } else {
                aIngress[i].mReverse = aLockDirections ? false : Random::Bool();
                //aIngress[i].mOffset = aOffsetIngressB;
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
                //aCross[i].mOffset = aOffsetCrossA;
            } else {
                aCross[i].mReverse = aLockDirections ? true : Random::Bool();
                //aCross[i].mOffset = aOffsetCrossB;
            }

            aCrossSourceCount++;
        }
    }

    pResult->mIngress = aIngress;
    pResult->mCross = aCross;

    return true;
}
