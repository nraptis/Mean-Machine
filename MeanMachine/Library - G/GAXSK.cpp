//
//  GAXSK.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/18/26.
//

#include "GAXSK.hpp"
#include "GAXSKPool.hpp"


namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

}

GAXSK::GAXSK() {
    mFormat = GAXSFormat::kInvalid;
    mHasDomainMix = false;
}

GAXSK::~GAXSK() {
    Reset();
}

bool GAXSK::RotationsClash_64_8(int pRotationA, int pRotationB) {
    if ((pRotationA < 0) || (pRotationA >= 64)) {
        return true;
    }
    
    if ((pRotationB < 0) || (pRotationB >= 64)) {
        return true;
    }
    
    int aDelta = pRotationA - pRotationB;
    if (aDelta < 0) {
        aDelta = -aDelta;
    }
    
    if (aDelta > 32) {
        aDelta = 64 - aDelta;
    }
    
    return (aDelta < 8);
}

bool GAXSK::RotationsClash_64_8(std::vector<int> pRotations) {
    for (int aIndexA = 0; aIndexA < pRotations.size(); aIndexA++) {
        for (int aIndexB = aIndexA + 1; aIndexB < pRotations.size(); aIndexB++) {
            if (RotationsClash_64_8(pRotations[aIndexA], pRotations[aIndexB])) {
                return true;
            }
        }
    }
    
    return false;
}

void GAXSK::Reset() {
    mFormat = GAXSFormat::kInvalid;
    mHasDomainMix = false;
    mLaneCounts.clear();

    for (int aPoolIndex = 0; aPoolIndex < mPools.size(); aPoolIndex++) {
        delete mPools[aPoolIndex];
    }
    mPools.clear();
}

GAXSKSourceKind GAXSK::SourceForIndex(int pIndex) {
    switch (pIndex) {
        case 0: return GAXSKSourceKind::kSourceA;
        case 1: return GAXSKSourceKind::kSourceB;
        case 2: return GAXSKSourceKind::kSourceC;
        case 3: return GAXSKSourceKind::kSourceD;
        default: return GAXSKSourceKind::kInvalid;
    }
}

GAXSKNonceByteKind GAXSK::NonceForIndex(int pIndex) {
    switch (pIndex & 7) {
        case 0: return GAXSKNonceByteKind::kNonceA;
        case 1: return GAXSKNonceByteKind::kNonceB;
        case 2: return GAXSKNonceByteKind::kNonceC;
        case 3: return GAXSKNonceByteKind::kNonceD;
        case 4: return GAXSKNonceByteKind::kNonceE;
        case 5: return GAXSKNonceByteKind::kNonceF;
        case 6: return GAXSKNonceByteKind::kNonceG;
        default: return GAXSKNonceByteKind::kNonceH;
    }
}

bool GAXSK::GetPassCount(int *pResult, std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::GetPassCount received null result");
        return false;
    }

    *pResult = 0;

    switch (mFormat) {
        case GAXSFormat::kSixSix:
            *pResult = 4;
            break;

        default:
            SetError(pErrorMessage, "GAXSK::GetPassCount received unsupported format");
            return false;
    }

    if (*pResult <= 0) {
        SetError(pErrorMessage, "GAXSK::GetPassCount produced invalid pass count");
        return false;
    }

    return true;
}

bool GAXSK::GetOrbiterCount(int *pResult,
                            std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::GetOrbiterCount received null result");
        return false;
    }

    *pResult = 0;

    switch (mFormat) {
        case GAXSFormat::kSixSix:
            *pResult = 6;
            break;

        default:
            SetError(pErrorMessage, "GAXSK::GetOrbiterCount received unsupported format");
            return false;
    }

    if (*pResult <= 0) {
        SetError(pErrorMessage, "GAXSK::GetOrbiterCount produced invalid orbiter count");
        return false;
    }

    return true;
}

bool GAXSK::GetWandererCount(int *pResult,
                             std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::GetWandererCount received null result");
        return false;
    }

    *pResult = 0;

    switch (mFormat) {
        case GAXSFormat::kSixSix:
            *pResult = 6;
            break;

        default:
            SetError(pErrorMessage, "GAXSK::GetWandererCount received unsupported format");
            return false;
    }

    if (*pResult <= 0) {
        SetError(pErrorMessage, "GAXSK::GetWandererCount produced invalid wanderer count");
        return false;
    }

    return true;
}

bool GAXSK::GetLaneCountForPass(int pPassIndex, int *pResult, std::string *pErrorMessage) const {
    
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::GetLaneCountForPass received null result");
        return false;
    }

    *pResult = 0;

    if (mLaneCounts.empty()) {
        SetError(pErrorMessage, "GAXSK::GetLaneCountForPass received no lane counts");
        return false;
    }

    if (pPassIndex < 0) {
        SetError(pErrorMessage, "GAXSK::GetLaneCountForPass received negative pass index");
        return false;
    }

    if (static_cast<std::size_t>(pPassIndex) < mLaneCounts.size()) {
        *pResult = mLaneCounts[static_cast<std::size_t>(pPassIndex)];
    } else {
        *pResult = mLaneCounts.back();
    }

    if ((*pResult < 1) || (*pResult > 4)) {
        SetError(pErrorMessage, "GAXSK::GetLaneCountForPass lane count must be 1, 2, 3, or 4");
        return false;
    }

    return true;
}

GAXSKInputSlot GAXSK::MakeSourceSlot(GAXSKSourceKind pSource,
                                     int pOffset,
                                     bool pReverse,
                                     int pRotation) {
    GAXSKInputSlot aSlot;
    aSlot.mKind = GAXSKInputSlotKind::kSource;
    aSlot.mSource = pSource;
    aSlot.mNonceByte = GAXSKNonceByteKind::kInvalid;
    aSlot.mOffset = pOffset;
    aSlot.mReverse = pReverse;
    aSlot.mRotation = pRotation;
    return aSlot;
}

GAXSKInputSlot GAXSK::MakeNonceSlot(GAXSKNonceByteKind pNonce,
                                    int pRotation) {
    GAXSKInputSlot aSlot;
    aSlot.mKind = GAXSKInputSlotKind::kNonceByte;
    aSlot.mSource = GAXSKSourceKind::kInvalid;
    aSlot.mNonceByte = pNonce;
    aSlot.mOffset = 0;
    aSlot.mReverse = false;
    aSlot.mRotation = pRotation;
    return aSlot;
}

GAXSKStatement GAXSK::MakePreviousAssignStatement() {
    GAXSKStatement aStatement;
    aStatement.mKind = GAXSKStatementKind::kPreviousAssign;
    aStatement.mTarget = GAXSKVariable::kPrevious;
    aStatement.mSource = GAXSKVariable::kIngress;
    return aStatement;
}

GAXSKStatement GAXSK::MakeContextWordStatement(GAXSKVariable pTarget,
                                               GAXSKDiffuseKind pDiffuse,
                                               bool pIsIngress) {
    GAXSKStatement aStatement;
    aStatement.mKind = GAXSKStatementKind::kContextWordAssign;
    aStatement.mTarget = pTarget;

    aStatement.mContextWord.mTarget = pTarget;
    aStatement.mContextWord.mHasDomainMix = mHasDomainMix;
    aStatement.mContextWord.mIsIngress = pIsIngress;
    aStatement.mContextWord.mDiffuse = pDiffuse;

    return aStatement;
}

bool GAXSK::MakeScatterMixStatement(GAXSKStatement *pResult,
                                    std::string *pErrorMessage) {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::MakeScatterMixStatement received null result");
        return false;
    }

    GAXSKStatement aStatement;
    aStatement.mKind = GAXSKStatementKind::kScatterMix;
    aStatement.mTarget = GAXSKVariable::kScatter;

    aStatement.mScatterMix.mTarget = GAXSKVariable::kScatter;
    aStatement.mScatterMix.mHasDomainMix = mHasDomainMix;
    aStatement.mScatterMix.mDiffuse = GAXSKDiffuseKind::kDiffuseB;

    // Tiny first version.
    aStatement.mScatterMix.mXorTerms.push_back({ GAXSKVariable::kIngress, 17 });
    aStatement.mScatterMix.mXorTerms.push_back({ GAXSKVariable::kCross, 41 });

    aStatement.mScatterMix.mAddTerms.push_back({ GAXSKVariable::kPrevious, 29 });
    aStatement.mScatterMix.mAddTerms.push_back({ GAXSKVariable::kCarry, 53 });

    *pResult = aStatement;
    return true;
}

bool GAXSK::BuildTinySkeletonForLaneCount(int pLaneCount,
                                          GAXSKSkeleton *pSkeleton,
                                          std::string *pErrorMessage) {
    if (pSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXSK::Bake received null skeleton");
        return false;
    }

    if (pLaneCount < 1 || pLaneCount > 4) {
        SetError(pErrorMessage, "GAXSK::Bake lane count must be 1, 2, 3, or 4");
        return false;
    }

    pSkeleton->mStatements.clear();

    pSkeleton->mStatements.push_back(MakePreviousAssignStatement());

    GAXSKStatement aIngress = MakeContextWordStatement(GAXSKVariable::kIngress, GAXSKDiffuseKind::kDiffuseA, true);
    GAXSKStatement aCross = MakeContextWordStatement(GAXSKVariable::kCross, GAXSKDiffuseKind::kDiffuseC, false);
    
    // Always include nonce pressure. This keeps the tiny skeleton stable.
    aIngress.mContextWord.mSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceA, 7));
    aIngress.mContextWord.mSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceB, 19));
    aIngress.mContextWord.mSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceC, 37));
    aIngress.mContextWord.mSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceD, 53));

    aCross.mContextWord.mSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceE, 11));
    aCross.mContextWord.mSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceF, 23));
    aCross.mContextWord.mSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceG, 41));
    aCross.mContextWord.mSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceH, 59));

    if (pLaneCount == 1) {
        aIngress.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 0, false, 13)
        );

        aCross.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 17, true, 43)
        );

    } else if (pLaneCount == 2) {
        aIngress.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 0, false, 13)
        );

        aCross.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceB, 17, true, 43)
        );

    } else if (pLaneCount == 3) {
        aIngress.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 0, false, 13)
        );
        aIngress.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceB, 11, false, 29)
        );

        aCross.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceC, 17, true, 43)
        );

    } else {
        aIngress.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 0, false, 13)
        );
        aIngress.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceB, 11, false, 29)
        );

        aCross.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceC, 17, true, 43)
        );
        aCross.mContextWord.mSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceD, 5, true, 61)
        );
    }

    pSkeleton->mStatements.push_back(aIngress);
    pSkeleton->mStatements.push_back(aCross);

    return true;
}

bool GAXSK::BuildSkeletonForLaneCount(int pPassIndex,
                                      int pLaneCount,
                                      GAXSKSkeleton *pSkeleton,
                                      std::string *pErrorMessage) {
    if (pSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount received null skeleton");
        return false;
    }

    if (pPassIndex < 0) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount received negative pass index");
        return false;
    }

    if (static_cast<std::size_t>(pPassIndex) >= mPools.size()) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount pass index exceeded pool count");
        return false;
    }

    if ((pLaneCount < 1) || (pLaneCount > 4)) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount lane count must be 1, 2, 3, or 4");
        return false;
    }

    GAXSKPool *aPool = mPools[static_cast<std::size_t>(pPassIndex)];
    if (aPool == nullptr) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount found null pool");
        return false;
    }

    GAXSKInputSlotOrdering aOrdering;
    if (!aPool->GenerateInputSlotOrdering(&aOrdering, pErrorMessage)) {
        return false;
    }

    if (aOrdering.mIngress.empty()) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount received empty ingress ordering");
        return false;
    }

    if (aOrdering.mCross.empty()) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount received empty cross ordering");
        return false;
    }

    pSkeleton->mStatements.clear();

    pSkeleton->mStatements.push_back(MakePreviousAssignStatement());

    GAXSKStatement aIngress = MakeContextWordStatement(GAXSKVariable::kIngress,
                                                       GAXSKDiffuseKind::kDiffuseA,
                                                       true);

    GAXSKStatement aCross = MakeContextWordStatement(GAXSKVariable::kCross,
                                                     GAXSKDiffuseKind::kDiffuseC,
                                                     false);

    aIngress.mContextWord.mSlots = aOrdering.mIngress;
    aCross.mContextWord.mSlots = aOrdering.mCross;

    pSkeleton->mStatements.push_back(aIngress);
    pSkeleton->mStatements.push_back(aCross);
    
    
    GAXSKStatement aScatter;
    if (!MakeScatterMixStatement(&aScatter, pErrorMessage)) {
        return false;
    }
    pSkeleton->mStatements.push_back(aScatter);
    
    
    return true;
}

bool GAXSK::Bake(GAXSFormat pFormat,
                 std::vector<int> pLaneCounts,
                 bool pHasDomainMix,
                 std::vector<GAXSKSkeleton> *pResult,
                 std::string *pErrorMessage) {
    Reset();

    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::Bake received null result");
        return false;
    }

    pResult->clear();

    mFormat = pFormat;
    mHasDomainMix = pHasDomainMix;
    mLaneCounts = pLaneCounts;

    int aPassCount = 0;
    if (!GetPassCount(&aPassCount, pErrorMessage)) {
        return false;
    }

    if (aPassCount >= 8) {
        SetError(pErrorMessage,
                 std::string("GAXSK::Bake invalid pass count: ") + std::to_string(aPassCount));
        return false;
    }

    mPools.reserve(static_cast<std::size_t>(aPassCount));
    for (int aPoolIndex = 0; aPoolIndex < aPassCount; aPoolIndex++) {
        mPools.push_back(new GAXSKPool());
    }

    for (int aPassIndex = 0; aPassIndex < aPassCount; aPassIndex++) {
        int aLaneCount = 0;
        if (!GetLaneCountForPass(aPassIndex,
                                 &aLaneCount,
                                 pErrorMessage)) {
            return false;
        }
        
        int aOrbiterCount = 0;
        if (!GetOrbiterCount(&aOrbiterCount, pErrorMessage)) {
            return false;
        }

        int aWandererCount = 0;
        if (!GetWandererCount(&aWandererCount, pErrorMessage)) {
            return false;
        }
        
        mPools[aPassIndex]->SetSourceCount(aLaneCount);
        mPools[aPassIndex]->SetOrbiterCount(aOrbiterCount);
        mPools[aPassIndex]->SetWandererCount(aWandererCount);
        
        if (!mPools[aPassIndex]->FinalizeCounts(pErrorMessage)) {
            return false;
        }
        

        GAXSKSkeleton aSkeleton;

        if (!BuildSkeletonForLaneCount(aPassIndex,
                                       aLaneCount,
                                       &aSkeleton,
                                       pErrorMessage)) {
            pResult->clear();
            return false;
        }

        pResult->push_back(aSkeleton);
    }

    return true;
}
