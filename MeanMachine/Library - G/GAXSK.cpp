//
//  GAXSK.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/18/26.
//

#include "GAXSK.hpp"

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

void GAXSK::SetError(std::string *pErrorMessage, const std::string &pMessage) {
    if (pErrorMessage != nullptr) { *pErrorMessage = pMessage; }
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
                                               bool pIsIngress,
                                               bool pHasDomainMix) {
    GAXSKStatement aStatement;
    aStatement.mKind = GAXSKStatementKind::kContextWordAssign;
    aStatement.mTarget = pTarget;

    aStatement.mContextWord.mTarget = pTarget;
    aStatement.mContextWord.mHasDomainMix = pHasDomainMix;
    aStatement.mContextWord.mIsIngress = pIsIngress;
    aStatement.mContextWord.mDiffuse = pDiffuse;

    return aStatement;
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

    GAXSKStatement aIngress =
        MakeContextWordStatement(GAXSKVariable::kIngress,
                                 GAXSKDiffuseKind::kDiffuseA,
                                 true,
                                 true);

    GAXSKStatement aCross =
        MakeContextWordStatement(GAXSKVariable::kCross,
                                 GAXSKDiffuseKind::kDiffuseC,
                                 false,
                                 true);

    // Always include nonce pressure. This keeps the tiny skeleton stable.
    aIngress.mContextWord.mXorSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceA, 7));
    aIngress.mContextWord.mXorSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceB, 19));
    aIngress.mContextWord.mAddXorSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceC, 37));
    aIngress.mContextWord.mAddXorSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceD, 53));

    aCross.mContextWord.mXorSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceE, 11));
    aCross.mContextWord.mXorSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceF, 23));
    aCross.mContextWord.mAddXorSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceG, 41));
    aCross.mContextWord.mAddXorSlots.push_back(MakeNonceSlot(GAXSKNonceByteKind::kNonceH, 59));

    if (pLaneCount == 1) {
        aIngress.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 0, false, 13)
        );

        aCross.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 17, true, 43)
        );

    } else if (pLaneCount == 2) {
        aIngress.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 0, false, 13)
        );

        aCross.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceB, 17, true, 43)
        );

    } else if (pLaneCount == 3) {
        aIngress.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 0, false, 13)
        );
        aIngress.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceB, 11, false, 29)
        );

        aCross.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceC, 17, true, 43)
        );

    } else {
        aIngress.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceA, 0, false, 13)
        );
        aIngress.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceB, 11, false, 29)
        );

        aCross.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceC, 17, true, 43)
        );
        aCross.mContextWord.mAddXorSlots.push_back(
            MakeSourceSlot(GAXSKSourceKind::kSourceD, 5, true, 61)
        );
    }

    pSkeleton->mStatements.push_back(aIngress);
    pSkeleton->mStatements.push_back(aCross);

    return true;
}

bool GAXSK::Bake(GAXSFormat pFormat,
                 std::vector<int> pLaneCounts,
                 bool pHasDomainMix,
                 std::vector<GAXSKSkeleton> *pResult,
                 std::string *pErrorMessage) {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::Bake received null result");
        return false;
    }

    pResult->clear();

    if (pFormat != GAXSFormat::kSixSix) {
        SetError(pErrorMessage, "GAXSK::Bake unsupported format");
        return false;
    }

    if (pLaneCounts.empty()) {
        SetError(pErrorMessage, "GAXSK::Bake received no lane counts");
        return false;
    }

    for (int aLaneCount : pLaneCounts) {
        GAXSKSkeleton aSkeleton;

        if (BuildTinySkeletonForLaneCount(aLaneCount,
                                          &aSkeleton,
                                          pErrorMessage) == false) {
            pResult->clear();
            return false;
        }

        pResult->push_back(aSkeleton);
    }

    return true;
}
