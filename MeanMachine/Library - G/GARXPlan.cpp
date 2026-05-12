//
//  GARXPlan.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/7/26.
//

#include "GARXPlan.hpp"
#include "Random.hpp"
#include "TwistArray.hpp"
#include "GARXPlugMapper.hpp"
#include <unordered_map>

static std::vector<int> cByteAlignedRotations = {
    16, 24, 32, 40, 48
};

static std::vector<int> cOddRotations = {
    7, 13, 21, 29, 37, 43, 51, 57, 63
};

static std::vector<int> cSeedRotations = {
    11, 13, 17, 19, 23, 27, 29, 31,
    35, 37, 41, 43, 45, 51, 53, 57
};


static std::vector<int> cUnwindRotations = {
    7, 11, 13, 17, 19, 23, 29, 31,
    37, 41, 43, 45, 51, 53, 57
};

static std::vector<int> cCarryShifts = {
    27, 29, 31, 33, 37, 41
};

static std::vector<int> cCarryRotations = {
    7, 11, 13, 17, 19, 23,
    29, 31, 37, 41, 43, 51, 53, 57
};

GARXCrushPairPlan::GARXCrushPairPlan() {
    mTypeA = GARXType::kInv;
    mTypeB = GARXType::kInv;
    
    mRotateA = false;
    mRotationAmount = -1;
}

GARXCrushPlan::GARXCrushPlan() {
    mPairA = GARXCrushPairPlan();
    mPairB = GARXCrushPairPlan();
    mPairC = GARXCrushPairPlan();
}

GARXCarryPairPlan::GARXCarryPairPlan() {
    mTypeA = GARXType::kInv;
    mTypeB = GARXType::kInv;
    mRotateA = false;
    mRotationAmount = -1;
}

GARXCarryPlan::GARXCarryPlan() {
    mPairA = GARXCarryPairPlan();
    mPairB = GARXCarryPairPlan();
    mPairC = GARXCarryPairPlan();

    mSecretCurrentRotation = -1;
    mMulRotation = -1;
    mShiftAmount = -1;
}

static std::vector<std::vector<GARXTypePair>> cCarryPairPatterns = {
    {
        { GARXType::kStateA, GARXType::kStateD },
        { GARXType::kStateB, GARXType::kStateE },
        { GARXType::kStateC, GARXType::kStateF }
    },
    {
        { GARXType::kStateA, GARXType::kStateE },
        { GARXType::kStateB, GARXType::kStateF },
        { GARXType::kStateC, GARXType::kStateD }
    },
    {
        { GARXType::kStateA, GARXType::kStateF },
        { GARXType::kStateB, GARXType::kStateD },
        { GARXType::kStateC, GARXType::kStateE }
    },
    {
        { GARXType::kStateA, GARXType::kStateB },
        { GARXType::kStateC, GARXType::kStateD },
        { GARXType::kStateE, GARXType::kStateF }
    }
};

static std::vector<std::vector<GARXTypePair>> cCrushPairPatterns = {
    {
        { GARXType::kRoundA, GARXType::kRoundB },
        { GARXType::kRoundC, GARXType::kRoundD },
        { GARXType::kRoundE, GARXType::kRoundF }
    },
    {
        { GARXType::kRoundA, GARXType::kRoundD },
        { GARXType::kRoundB, GARXType::kRoundE },
        { GARXType::kRoundC, GARXType::kRoundF }
    },
    {
        { GARXType::kRoundA, GARXType::kRoundE },
        { GARXType::kRoundB, GARXType::kRoundF },
        { GARXType::kRoundC, GARXType::kRoundD }
    },
    {
        { GARXType::kRoundA, GARXType::kRoundF },
        { GARXType::kRoundB, GARXType::kRoundD },
        { GARXType::kRoundC, GARXType::kRoundE }
    }
};

static std::vector<int> cCrushRotations = {
    11, 17, 19, 23, 29, 31,
    37, 41, 43, 47, 53, 57
};


static GARXCrushPairPlan MakeCrushPairPlan(const GARXTypePair &pPair,
                                           int pRotationAmount) {
    
    GARXCrushPairPlan aPairPlan;
    
    aPairPlan.mTypeA = pPair.mTypeA;
    aPairPlan.mTypeB = pPair.mTypeB;
    
    aPairPlan.mRotateA = Random::Bool();
    aPairPlan.mRotationAmount = pRotationAmount;
    
    return aPairPlan;
}

static GARXCrushPlan MakeCrushPlan(std::size_t pPassIndex) {
    
    GARXCrushPlan aPlan;
    
    const std::vector<GARXTypePair> &aPattern =
        cCrushPairPatterns[pPassIndex & 3U];
    
    std::vector<int> aRotations = cCrushRotations;
    Random::Shuffle(&aRotations);
    
    aPlan.mPairA = MakeCrushPairPlan(aPattern[0], aRotations[0]);
    aPlan.mPairB = MakeCrushPairPlan(aPattern[1], aRotations[1]);
    aPlan.mPairC = MakeCrushPairPlan(aPattern[2], aRotations[2]);
    
    return aPlan;
}

static GARXCarryPairPlan MakeCarryPairPlan(const GARXTypePair &pPair,
                                           int pRotationAmount) {
    
    GARXCarryPairPlan aPairPlan;
    
    aPairPlan.mTypeA = pPair.mTypeA;
    aPairPlan.mTypeB = pPair.mTypeB;
    aPairPlan.mRotateA = Random::Bool();
    aPairPlan.mRotationAmount = pRotationAmount;
    
    return aPairPlan;
}

static GARXCarryPlan MakeCarryPlan(std::size_t pPassIndex) {
    
    GARXCarryPlan aPlan;
    
    const std::vector<GARXTypePair> &aPattern =
        cCarryPairPatterns[pPassIndex & 3U];
    
    std::vector<int> aRotations = cCarryRotations;
    std::vector<int> aShifts = cCarryShifts;
    
    Random::Shuffle(&aRotations);
    Random::Shuffle(&aShifts);
    
    aPlan.mPairA = MakeCarryPairPlan(aPattern[0], aRotations[0]);
    aPlan.mPairB = MakeCarryPairPlan(aPattern[1], aRotations[1]);
    aPlan.mPairC = MakeCarryPairPlan(aPattern[2], aRotations[2]);
    
    aPlan.mSecretCurrentRotation = aRotations[3];
    aPlan.mMulRotation = aRotations[4];
    aPlan.mShiftAmount = aShifts[0];
    
    return aPlan;
}

static bool IsContextualBackwardRound(const GARXSkeletonBackwardRound &pBackward) {
    
    if (pBackward.mInputA != GARXType::kSecretCurrent) {
        return false;
    }
    
    if ((pBackward.mInputB != GARXType::kSecretPrevious) &&
        (pBackward.mInputB != GARXType::kSecretScatter)) {
        return false;
    }
    
    if (GARXSkeleton::IsRoundType(pBackward.mInputC) == false) {
        return false;
    }
    
    return true;
}

static bool BackwardRoundsHaveGoodRoundPairSpread(const std::vector<GARXSkeletonBackwardRound> &pBackward) {
    
    std::unordered_set<GARXType, GARXTypeHash> aUniqueRounds;
    int aPairRowCount = 0;
    
    for (const GARXSkeletonBackwardRound &aBackward: pBackward) {
        
        if (aBackward.mShape != GARXUnwindShape::kRoundPair) {
            continue;
        }
        
        aPairRowCount++;
        
        if (GARXSkeleton::IsRoundType(aBackward.mInputA)) {
            aUniqueRounds.insert(aBackward.mInputA);
        }
        
        if (GARXSkeleton::IsRoundType(aBackward.mInputB)) {
            aUniqueRounds.insert(aBackward.mInputB);
        }
        
        if (GARXSkeleton::IsRoundType(aBackward.mInputC)) {
            aUniqueRounds.insert(aBackward.mInputC);
        }
    }
    
    if (aPairRowCount != 2) {
        printf("bad round-pair unwind shape: expected 2 pair rows, got %d\n",
               aPairRowCount);
        return false;
    }
    
    if (aUniqueRounds.size() < 3) {
        printf("bad round-pair unwind spread: unique rounds=%zu\n",
               aUniqueRounds.size());
        return false;
    }
    
    return true;
}

static GARXDatum MakeTypeDatum(GARXType pType) {
    GARXDatum aDatum;
    aDatum.mKind = GARXDatumKind::kType;
    aDatum.mType = pType;
    return aDatum;
}

static GARXDatum MakeHotAddDatum() {
    GARXDatum aDatum;
    aDatum.mKind = GARXDatumKind::kHotAdd;
    return aDatum;
}

static GARXDatum MakeHotMulDatum() {
    GARXDatum aDatum;
    aDatum.mKind = GARXDatumKind::kHotMul;
    return aDatum;
}

static GARXDatum MakeLoopKeyDatum(bool pIsInverted) {
    GARXDatum aDatum;
    aDatum.mKind = GARXDatumKind::kLoopKey;
    aDatum.mIsLoopIndexInverted = pIsInverted;
    aDatum.mOffsetAmount = -1; // filled later
    return aDatum;
}

static GARXDatum MakePlugKeyDatum(GARXType pTypeA, GARXType pTypeB) {
    GARXDatum aDatum;
    aDatum.mKind = GARXDatumKind::kPlugKey;
    aDatum.mPlugTypeA = pTypeA;
    aDatum.mPlugTypeB = pTypeB;
    return aDatum;
}

static bool UnwindRowGetsLoopKey(std::size_t pBackwardIndex) {
    switch (pBackwardIndex) {
        case 0:
        case 3:
            return true;
            
        default:
            return false;
    }
}

static GARXStatementPlan *MakeUnwindStatement(const GARXSkeletonBackwardRound &pBackward,
                                              std::size_t pBackwardIndex,
                                              bool pInversionModality) {
    
    GARXStatementPlan *aStatement = new GARXStatementPlan(GARXStatementType::kUnwind,
                                                          pBackward.mTarget);
    
    //
    // target = target OP inputA OP inputB OP inputC OP loop_key
    //
    aStatement->mDatums.push_back(MakeTypeDatum(pBackward.mTarget));
    
    if (pBackward.mInputA != GARXType::kInv) {
        aStatement->mDatums.push_back(MakeTypeDatum(pBackward.mInputA));
    }
    
    if (pBackward.mInputB != GARXType::kInv) {
        aStatement->mDatums.push_back(MakeTypeDatum(pBackward.mInputB));
    }
    
    if (pBackward.mInputC != GARXType::kInv) {
        aStatement->mDatums.push_back(MakeTypeDatum(pBackward.mInputC));
    }
    
    if (UnwindRowGetsLoopKey(pBackwardIndex)) {
        bool aIsInverted = ((pBackwardIndex & 1U) != 0U);
        if (pInversionModality == true) {
            aIsInverted = !aIsInverted;
        }
        aStatement->mDatums.push_back(MakeLoopKeyDatum(aIsInverted));
    }
    
    aStatement->mDatums.push_back(MakeHotMulDatum());
    
    return aStatement;
}

static bool BackwardRoundsHaveGoodContextualSpread(const std::vector<GARXSkeletonBackwardRound> &pBackward) {
    
    std::vector<GARXType> aContextualRounds;
    
    for (const GARXSkeletonBackwardRound &aBackward: pBackward) {
        
        if (IsContextualBackwardRound(aBackward) == false) {
            continue;
        }
        
        aContextualRounds.push_back(aBackward.mInputC);
    }
    
    if (aContextualRounds.size() != 4) {
        return false;
    }
    
    std::unordered_set<GARXType, GARXTypeHash> aUniqueRounds;
    
    for (GARXType aRound: aContextualRounds) {
        aUniqueRounds.insert(aRound);
    }
    
    //
    // Good enough:
    // 4 contextual rows should cover at least 3 different rounds.
    //
    if (aUniqueRounds.size() < 3) {
        return false;
    }
    
    return true;
}

static void RandomizeContextualBackwardRounds(std::vector<GARXSkeletonBackwardRound> *pBackward) {
    
    if (pBackward == nullptr) {
        return;
    }
    
    std::vector<int> aContextualIndexes;
    
    for (std::size_t i = 0; i < pBackward->size(); i++) {
        if (IsContextualBackwardRound((*pBackward)[i])) {
            aContextualIndexes.push_back(static_cast<int>(i));
        }
    }
    
    if (aContextualIndexes.size() != 4) {
        return;
    }
    
    std::vector<GARXType> aRounds = {
        GARXType::kRoundA,
        GARXType::kRoundB,
        GARXType::kRoundC,
        GARXType::kRoundD,
        GARXType::kRoundE,
        GARXType::kRoundF
    };
    
    Random::Shuffle(&aRounds);
    
    //
    // Assign 4 unique rounds to the 4 contextual unwind rows.
    // This keeps the contextual unwind pressure spread out before statements
    // are ever built.
    //
    for (std::size_t i = 0; i < aContextualIndexes.size(); i++) {
        int aBackwardIndex = aContextualIndexes[i];
        (*pBackward)[aBackwardIndex].mInputC = aRounds[i];
    }
}

static void RemoveUnwindStatementsAndGroups(GARXPassPlan *pPassPlan) {
    
    if (pPassPlan == nullptr) {
        return;
    }
    
    //
    // Delete unwind groups only. Groups do not own statements.
    //
    for (int i = static_cast<int>(pPassPlan->mGroups.size()) - 1; i >= 0; i--) {
        
        GARXStatementGroup *aGroup = pPassPlan->mGroups[i];
        
        if (aGroup == nullptr) {
            pPassPlan->mGroups.erase(pPassPlan->mGroups.begin() + i);
            continue;
        }
        
        if (aGroup->mGroupType == GARXGroupType::kUnwind) {
            delete aGroup;
            pPassPlan->mGroups.erase(pPassPlan->mGroups.begin() + i);
        }
    }
    
    //
    // Delete unwind statements.
    //
    for (int i = static_cast<int>(pPassPlan->mStatements.size()) - 1; i >= 0; i--) {
        
        GARXStatementPlan *aStatement = pPassPlan->mStatements[i];
        
        if (aStatement == nullptr) {
            pPassPlan->mStatements.erase(pPassPlan->mStatements.begin() + i);
            continue;
        }
        
        if (aStatement->mStatementType == GARXStatementType::kUnwind) {
            delete aStatement;
            pPassPlan->mStatements.erase(pPassPlan->mStatements.begin() + i);
        }
    }
}

static bool BuildUnwindStatementsForPass(GARXPassPlan *pPassPlan,
                                         const GARXSkeletonPass &pSkeletonPass) {
    
    if (pPassPlan == nullptr) {
        return false;
    }
    
    RemoveUnwindStatementsAndGroups(pPassPlan);
    
    std::vector<GARXSkeletonBackwardRound> aBackward = pSkeletonPass.mBackward;
    RandomizeContextualBackwardRounds(&aBackward);
    
    if (BackwardRoundsHaveGoodContextualSpread(aBackward) == false) {
        printf("bwr-a\n");
        return false;
    }
    
    if (BackwardRoundsHaveGoodRoundPairSpread(aBackward) == false) {
        printf("bwr-b\n");
        return false;
    }
    
    bool aStateInversionModality = Random::Bool();
    
    for (std::size_t n = 0; n < aBackward.size(); n++) {
        GARXStatementPlan *aUnwindStatement = MakeUnwindStatement(aBackward[n],
                                                                  n,
                                                                  aStateInversionModality);
        if (aUnwindStatement == nullptr) {
            RemoveUnwindStatementsAndGroups(pPassPlan);
            return false;
        }
        
        pPassPlan->mStatements.push_back(aUnwindStatement);
        
        GARXStatementGroup *aGroup = new GARXStatementGroup(GARXGroupType::kUnwind);
        aGroup->mStatements.push_back(aUnwindStatement);
        pPassPlan->mGroups.push_back(aGroup);
    }
    
    return true;
}

static int LoopSaltOffsetDistance(int pOffsetA, int pOffsetB) {
    
    int aOffsetA = pOffsetA & 31;
    int aOffsetB = pOffsetB & 31;
    
    int aDiff = aOffsetA - aOffsetB;
    if (aDiff < 0) {
        aDiff = -aDiff;
    }
    
    int aWrappedDiff = 32 - aDiff;
    
    return (aDiff < aWrappedDiff) ? aDiff : aWrappedDiff;
}

static bool LoopSaltOffsetsAreTooClose(int pOffsetA, int pOffsetB) {
    return LoopSaltOffsetDistance(pOffsetA, pOffsetB) < 5;
}

struct GARXTypeRotationKey {
    GARXType mType;
    int mRotationAmount;
};

struct GARXTypeRotationKeyHash {
    std::size_t operator()(const GARXTypeRotationKey &pKey) const {
        return (static_cast<std::size_t>(pKey.mType) * 257U) ^
               static_cast<std::size_t>(pKey.mRotationAmount);
    }
};

static bool operator==(const GARXTypeRotationKey &pA,
                       const GARXTypeRotationKey &pB) {
    return (pA.mType == pB.mType) &&
           (pA.mRotationAmount == pB.mRotationAmount);
}

static bool InsertTypeRotationKey(std::unordered_set<GARXTypeRotationKey, GARXTypeRotationKeyHash> *pSet,
                                  GARXType pType,
                                  int pRotationAmount) {
    
    if (pType == GARXType::kInv) {
        return true;
    }
    
    if (pRotationAmount < 0) {
        return true;
    }
    
    GARXTypeRotationKey aKey;
    aKey.mType = pType;
    aKey.mRotationAmount = pRotationAmount;
    
    if (pSet->find(aKey) != pSet->end()) {
        printf("duplicate rotation key: type=%s rotation=%d\n",
               GARXSkeleton::GetTypeName(pType),
               pRotationAmount);
        return false;
    }
    
    pSet->insert(aKey);
    return true;
}

//
// Loop salt banks are 32 bytes, so offsets are chosen modulo 32.
//
// These offsets are public schedule constants, not secret material. Their job is
// to keep forward/reverse loop salt reads from repeatedly touching the same
// aligned positions. We prefer odd offsets because they walk the 32-byte ring
// without matching byte-pair or word-style boundaries.
//
// Offsets such as 11, 13, 17, 19, 23, and 29 are useful here because they are
// awkward relative to the 32-byte salt width. Since the ring is only 32 bytes,
// larger constants are not useful unless their value modulo 32 is intentional.
//
// Within one pass, loop-key offsets should be unique when possible. For paired
// forward/reverse loop keys in the same statement, avoid using mirror
// complements such as 11 and 21 unless explicitly intended.
//
static std::vector<int> cLoopSaltOffsets = {
    3, 5, 7, 9,
    11, 13, 17, 19,
    21, 23, 25, 27,
    29
};

static bool LoopSaltOffsetsAreComplements(int pOffsetA,
                                          int pOffsetB) {
    
    int aOffsetA = pOffsetA & 31;
    int aOffsetB = pOffsetB & 31;
    
    if (aOffsetA == 0 || aOffsetB == 0) {
        return false;
    }
    
    return (((aOffsetA + aOffsetB) & 31) == 0);
}

static int CountLoopKeySlots(const std::vector<GARXStatementGroup *> &pGroups) {
    
    int aResult = 0;
    for (GARXStatementGroup *aGroup: pGroups) {
        for (GARXStatementPlan *aStatement: aGroup->mStatements) {
            for (const GARXDatum &aDatum: aStatement->mDatums) {
                if (aDatum.mKind == GARXDatumKind::kLoopKey) {
                    aResult++;
                }
            }
        }
    }
    
    return aResult;
}

static std::vector<std::vector<int>> cScatterRotationPools = {
    {  5, 7, 9, 11, 13 },
    { 19, 21, 23, 27, 29 },
    { 31, 35, 37, 41, 43 },
    { 47, 49, 51, 53, 57 }
};

static GARXBlendPlan MakeBlendPlan() {
    GARXBlendPlan aPlan;
    std::vector<std::vector<int>> aPools = cScatterRotationPools;
    Random::Shuffle(&aPools);
    aPlan.mRotationA = Random::Choice(aPools[0]);
    aPlan.mRotationB = Random::Choice(aPools[1]);
    aPlan.mRotationC = Random::Choice(aPools[2]);
    aPlan.mRotationD = Random::Choice(aPools[3]);
    return aPlan;
}

static void PrintBlendPlan(const GARXBlendPlan &pBlendPlan,
                           const char *pSectionName,
                           const char *pBlendName,
                           bool pIncludeRotations) {
    printf("[%s]\n", pSectionName);
    if (pIncludeRotations) {
        printf("%s = diffuse((rot(thing_a,%d) ^ rot(thing_b,%d)) + (rot(thing_c,%d) ^ rot(thing_d,%d)))\n\n",
               pBlendName,
               pBlendPlan.mRotationA,
               pBlendPlan.mRotationB,
               pBlendPlan.mRotationC,
               pBlendPlan.mRotationD);
    } else {
        printf("%s = diffuse((rot(thing_a,A) ^ rot(thing_b,B)) + (rot(thing_c,C) ^ rot(thing_d,D)))\n\n",
               pBlendName);
    }
}
static void PrintStatementCompact(const GARXStatementPlan &pStatement,
                                  bool pIncludePlugs,
                                  bool pIncludeRotations) {
    
    if (pStatement.mStatementType == GARXStatementType::kCrush) {
        printf("*crush %s*\n", GARXSkeleton::GetTypeName(pStatement.mTarget));
        return;
    }
    
    if (pStatement.mStatementType == GARXStatementType::kForwardRotate) {
        
        if (pStatement.mRotationAmount >= 0) {
            printf("%s <- rot(%s * <hot_mul>, %d)\n",
                   GARXSkeleton::GetTypeName(pStatement.mTarget),
                   GARXSkeleton::GetTypeName(pStatement.mTarget),
                   pStatement.mRotationAmount);
        } else {
            printf("%s <- rot(%s * <hot_mul>)\n",
                   GARXSkeleton::GetTypeName(pStatement.mTarget),
                   GARXSkeleton::GetTypeName(pStatement.mTarget));
        }
        
        return;
    }
    
    printf("%s =", GARXSkeleton::GetTypeName(pStatement.mTarget));
    
    for (std::size_t k = 0; k < pStatement.mDatums.size(); k++) {
        const GARXDatum &aDatum = pStatement.mDatums[k];
        
        if (k > 0) {
            printf(" +");
        }
        
        if (aDatum.mKind == GARXDatumKind::kType) {
            //printf(" %s", GARXSkeleton::GetTypeName(aDatum.mType));
            if (pIncludeRotations && aDatum.mRotationAmount >= 0) {
                printf(" rot(%s,%d)",
                       GARXSkeleton::GetTypeName(aDatum.mType),
                       aDatum.mRotationAmount);
            } else {
                printf(" %s", GARXSkeleton::GetTypeName(aDatum.mType));
            }
            
        } else if (aDatum.mKind == GARXDatumKind::kLoopKey) {
            
            const char *aDirection = aDatum.mIsLoopIndexInverted ? "reverse" : "forward";
            
            if ((aDatum.mSaltDomain != GARXSaltDomain::kInv) &&
                (aDatum.mOffsetAmount >= 0)) {
                
                printf(" <loop_key:%s,%s,%d>",
                       GARXSkeleton::GetSaltDomainName(aDatum.mSaltDomain),
                       aDirection,
                       aDatum.mOffsetAmount);
                
            } else if (aDatum.mSaltDomain != GARXSaltDomain::kInv) {
                
                printf(" <loop_key:%s,%s>",
                       GARXSkeleton::GetSaltDomainName(aDatum.mSaltDomain),
                       aDirection);
                
            } else if (aDatum.mOffsetAmount >= 0) {
                
                printf(" <loop_key:%s,%d>",
                       aDirection,
                       aDatum.mOffsetAmount);
                
            } else {
                
                printf(" <loop_key:%s>", aDirection);
            }
        } else if (aDatum.mKind == GARXDatumKind::kPlugKey) {
            
            if (pIncludePlugs) {
                
                const char *aDomainName = GARXSkeleton::GetSaltDomainName(aDatum.mSaltDomain);
                const char *aTypeAName = GARXSkeleton::GetTypeName(aDatum.mPlugTypeA);
                const char *aTypeBName = GARXSkeleton::GetTypeName(aDatum.mPlugTypeB);
                
                if (aDatum.mSaltDomain != GARXSaltDomain::kInv) {
                    
                    if (aDatum.mRotationAmount >= 0) {
                        if (aDatum.mOffsetAmount >= 0) {
                            printf(" <plug_key:%s,rot(%s,%d),%s,+%d>",
                                   aDomainName,
                                   aTypeAName,
                                   aDatum.mRotationAmount,
                                   aTypeBName,
                                   aDatum.mOffsetAmount);
                        } else {
                            printf(" <plug_key:%s,rot(%s,%d),%s>",
                                   aDomainName,
                                   aTypeAName,
                                   aDatum.mRotationAmount,
                                   aTypeBName);
                        }
                    } else {
                        if (aDatum.mOffsetAmount >= 0) {
                            printf(" <plug_key:%s,%s,%s,+%d>",
                                   aDomainName,
                                   aTypeAName,
                                   aTypeBName,
                                   aDatum.mOffsetAmount);
                        } else {
                            printf(" <plug_key:%s,%s,%s>",
                                   aDomainName,
                                   aTypeAName,
                                   aTypeBName);
                        }
                    }
                    
                } else {
                    
                    if (aDatum.mRotationAmount >= 0) {
                        if (aDatum.mOffsetAmount >= 0) {
                            printf(" <plug_key:rot(%s,%d),%s,+%d>",
                                   aTypeAName,
                                   aDatum.mRotationAmount,
                                   aTypeBName,
                                   aDatum.mOffsetAmount);
                        } else {
                            printf(" <plug_key:rot(%s,%d),%s>",
                                   aTypeAName,
                                   aDatum.mRotationAmount,
                                   aTypeBName);
                        }
                    } else {
                        if (aDatum.mOffsetAmount >= 0) {
                            printf(" <plug_key:%s,%s,+%d>",
                                   aTypeAName,
                                   aTypeBName,
                                   aDatum.mOffsetAmount);
                        } else {
                            printf(" <plug_key:%s,%s>",
                                   aTypeAName,
                                   aTypeBName);
                        }
                    }
                }
                
            } else {
                
                printf(" <plug_key>");
            }
        } else if (aDatum.mKind == GARXDatumKind::kHotAdd) {
            printf(" <hot_add>");
        } else if (aDatum.mKind == GARXDatumKind::kHotMul) {
            printf(" <hot_mul>");
        } else {
            printf(" <%s>", GARXSkeleton::GetDatumKindName(aDatum.mKind));
        }
    }

    printf("\n");
}

static std::vector<std::vector<GARXType>> cAllowedSeedTaps = {
    { GARXType::kSecretCurrent },
    { GARXType::kSecretPrevious, GARXType::kSecretScatter },
    { GARXType::kSecretPrevious, GARXType::kSecretScatter, GARXType::kCarry },
    { GARXType::kSecretCurrent, GARXType::kSecretScatter, GARXType::kCarry },
    { GARXType::kSecretCurrent, GARXType::kSecretScatter, GARXType::kCarry },
    { GARXType::kSecretPrevious, GARXType::kSecretScatter, GARXType::kCarry },
};
static std::unordered_map<GARXType, int, GARXTypeHash> cMinimumSeedTaps = {
    { GARXType::kSecretCurrent, 2 },
    { GARXType::kSecretPrevious, 1 },
    { GARXType::kCarry, 1 }
};

static std::unordered_map<GARXType, int, GARXTypeHash> cMaximumSeedTaps = {
    { GARXType::kSecretCurrent, 2 },
    { GARXType::kSecretPrevious, 2 },
    { GARXType::kCarry, 1 },
    { GARXType::kSecretScatter, 2 }
};

static GARXSaltDomain PickLoopSaltDomainForStatement(GARXGroupType pGroupType,
                                                     std::size_t pLoopKeyIndexInPhase,
                                                     std::size_t pLoopKeyIndexInStatement) {
    
    if (pGroupType == GARXGroupType::kSeed) {
        return ((pLoopKeyIndexInStatement & 1U) == 0U)
            ? GARXSaltDomain::kInitA
            : GARXSaltDomain::kInitB;
    }
    
    if (pGroupType == GARXGroupType::kUnwind) {
        if ((pLoopKeyIndexInPhase & 1U) == 0U) {
            return GARXSaltDomain::kUnwindA;
        } else {
            return GARXSaltDomain::kUnwindB;
        }
    }
    
    return GARXSaltDomain::kInv;
}

GARXBlendPlan::GARXBlendPlan() {
    mRotationA = -1; mRotationB = -1; mRotationC = -1; mRotationD = -1;
}

static GARXSaltDomain PickPlugSaltDomainForSlot(std::size_t pPlugIndexInGroup,
                                                std::size_t pForwardGroupIndex,
                                                std::size_t pPassIndex) {
    
    bool aFlip = (((pForwardGroupIndex + pPassIndex) & 1U) != 0U);
    
    if (pPlugIndexInGroup == 0) {
        return aFlip ? GARXSaltDomain::kPlugB : GARXSaltDomain::kPlugA;
    }
    
    return aFlip ? GARXSaltDomain::kPlugA : GARXSaltDomain::kPlugB;
}

static bool IsValidSeedTapConfiguration(std::vector<GARXType> &pTypes) {
    if (TwistArray::AllInValidRanges_Pessimistic<GARXType, GARXTypeHash>(&pTypes,
                                                                         &cMinimumSeedTaps,
                                                                         &cMaximumSeedTaps) == false) {
        return false;
    }
    
    for (GARXType &aType: pTypes) {
        int aMinimumDistance = TwistArray::MinimumDistance(&pTypes, aType);
        if ((aMinimumDistance >= 0) && (aMinimumDistance < 3)) { return false; }
    }
    
    return true;
}

static bool SeedPlanGutsAreUnique(const std::vector<GARXRoundSeedPlan *> &pSeeds) {
    for (std::size_t i = 0; i < pSeeds.size(); i++) {
        const GARXRoundSeedPlan *aSeedA = pSeeds[i];
        if (aSeedA == nullptr) {
            return false;
        }
        for (std::size_t n = i + 1; n < pSeeds.size(); n++) {
            const GARXRoundSeedPlan *aSeedB = pSeeds[n];
            if (aSeedB == nullptr) {
                return false;
            }
            if ((aSeedA->mState == aSeedB->mState) &&
                (aSeedA->mTap == aSeedB->mTap)) {
                return false;
            }
        }
    }
    return true;
}

const char *GARXStatementGroup::GetTypeName(GARXGroupType pType) {
    switch (pType) {
        case GARXGroupType::kSeed: return "seed";
        case GARXGroupType::kForwardTriplet: return "forward_triplet";
        case GARXGroupType::kCrush: return "crush";
        case GARXGroupType::kUnwind: return "unwind";
        case GARXGroupType::kCarry: return "carry";
        default: return "invalid";
    }
}

static GARXStatementPlan *MakeSeedStatement(GARXRoundSeedPlan *pSeed,
                                            std::size_t pSeedIndex) {
    
    GARXStatementPlan *aStatement = new GARXStatementPlan(GARXStatementType::kRoundSeed, pSeed->mTarget);

    aStatement->mDatums.push_back(MakeTypeDatum(pSeed->mState));
    aStatement->mDatums.push_back(MakeTypeDatum(pSeed->mTap));
    aStatement->mDatums.push_back(MakeHotAddDatum());
    
    if (Random::Bool()) {
        if (pSeedIndex == 2) {
            aStatement->mDatums.push_back(MakeLoopKeyDatum(true));
            aStatement->mDatums.push_back(MakeLoopKeyDatum(false));
        }
    } else {
        if (pSeedIndex == 2) {
            aStatement->mDatums.push_back(MakeLoopKeyDatum(false));
            aStatement->mDatums.push_back(MakeLoopKeyDatum(true));
        }
    }
    
    if (Random::Bool()) {
        if (pSeedIndex == 3) {
            aStatement->mDatums.push_back(MakeLoopKeyDatum(true));
            aStatement->mDatums.push_back(MakeLoopKeyDatum(false));
        }
    } else {
        if (pSeedIndex == 3) {
            aStatement->mDatums.push_back(MakeLoopKeyDatum(false));
            aStatement->mDatums.push_back(MakeLoopKeyDatum(true));
        }
    }

    return aStatement;
}

static GARXStatementPlan *MakeForwardLeadStatement(const GARXSkeletonForwardRound &pForward) {
    GARXStatementPlan *aStatement = new GARXStatementPlan(GARXStatementType::kForwardLead, pForward.mLead);
    aStatement->mDatums.push_back(MakeTypeDatum(pForward.mLead));
    aStatement->mDatums.push_back(MakeTypeDatum(pForward.mSource));
    aStatement->mDatums.push_back(MakeHotAddDatum());
    aStatement->mDatums.push_back(MakePlugKeyDatum(GARXType::kInv, GARXType::kInv));
    return aStatement;
}

static GARXStatementPlan *MakeForwardFeedbackStatement(const GARXSkeletonForwardRound &pForward) {
    GARXStatementPlan *aStatement = new GARXStatementPlan(GARXStatementType::kForwardFeedback, pForward.mFeedback);
    aStatement->mDatums.push_back(MakeTypeDatum(pForward.mFeedback));
    aStatement->mDatums.push_back(MakeTypeDatum(pForward.mLead));
    aStatement->mDatums.push_back(MakeHotAddDatum());
    aStatement->mDatums.push_back(MakePlugKeyDatum(GARXType::kInv, GARXType::kInv));
    return aStatement;
}

static GARXStatementPlan *MakeForwardRotateStatement(const GARXSkeletonForwardRound &pForward) {
    
    GARXStatementPlan *aStatement = new GARXStatementPlan(GARXStatementType::kForwardRotate,
                                                          pForward.mFeedback);
    
    aStatement->mDatums.push_back(MakeTypeDatum(pForward.mFeedback));
    aStatement->mDatums.push_back(MakeHotMulDatum());
    
    return aStatement;
}

static std::vector<int> MakeForwardRotationSchedule() {
    
    std::vector<int> aByteAligned = cByteAlignedRotations;
    std::vector<int> aOdd = cOddRotations;
    
    Random::Shuffle(&aByteAligned);
    Random::Shuffle(&aOdd);
    
    int aByteAlignedCount = 2;
    if (Random::Bool()) {
        aByteAlignedCount++;
    }
    if (Random::Bool()) {
        aByteAlignedCount++;
    }
    
    int aOddCount = 6 - aByteAlignedCount;
    
    std::vector<int> aResult;
    
    for (int i = 0; i < aByteAlignedCount; i++) {
        aResult.push_back(aByteAligned[i]);
    }
    
    for (int i = 0; i < aOddCount; i++) {
        aResult.push_back(aOdd[i]);
    }
    
    Random::Shuffle(&aResult);
    
    return aResult;
}

static std::vector<int> MakeSeedRotationSchedule() {
    
    std::vector<int> aPool = cSeedRotations;
    Random::Shuffle(&aPool);
    
    std::vector<int> aResult;
    
    for (int i = 0; i < 6; i++) {
        aResult.push_back(aPool[i]);
    }
    
    return aResult;
}

static std::vector<int> cPassSaltBiases = {
    0, 6, 10, 14
};

static std::vector<int> MakeLoopSaltOffsetSchedule(int pCount,
                                                   std::size_t pPassIndex) {
    
    int aPassBias = cPassSaltBiases[pPassIndex & 3U];
    
    std::vector<int> aPool;
    
    for (int aOffset: cLoopSaltOffsets) {
        int aBiasedOffset = (aOffset + aPassBias) & 31;
        
        if (aBiasedOffset == 0) {
            continue;
        }
        
        aPool.push_back(aBiasedOffset);
    }
    
    Random::Shuffle(&aPool);
    
    std::vector<int> aResult;
    
    for (int i = 0; i < pCount; i++) {
        if (i < static_cast<int>(aPool.size())) {
            aResult.push_back(aPool[i]);
        } else {
            return aResult;
        }
    }
    
    return aResult;
}

static bool AssignForwardRotations(std::vector<GARXStatementGroup *> &pGroups) {
    
    std::vector<int> aRotations = MakeForwardRotationSchedule();
    std::size_t aRotationIndex = 0;
    
    for (GARXStatementGroup *aGroup: pGroups) {
        
        if (aGroup->mGroupType != GARXGroupType::kForwardTriplet) {
            continue;
        }
        
        for (GARXStatementPlan *aStatement: aGroup->mStatements) {
            
            if (aStatement->mStatementType == GARXStatementType::kForwardRotate) {
                
                if (aRotationIndex >= aRotations.size()) {
                    return false;
                }
                
                aStatement->mRotationAmount = aRotations[aRotationIndex];
                aRotationIndex++;
            }
        }
    }
    
    return (aRotationIndex == aRotations.size());
}

static bool AssignUnwindRotations(std::vector<GARXStatementGroup *> &pGroups) {
    
    std::vector<int> aRotations = cUnwindRotations;
    Random::Shuffle(&aRotations);
    
    std::size_t aRotationIndex = 0;
    
    for (GARXStatementGroup *aGroup: pGroups) {
        
        if (aGroup->mGroupType != GARXGroupType::kUnwind) {
            continue;
        }
        
        for (GARXStatementPlan *aStatement: aGroup->mStatements) {
            
            for (GARXDatum &aDatum: aStatement->mDatums) {
                
                if (aDatum.mKind != GARXDatumKind::kType) {
                    continue;
                }
                
                //
                // Do not rotate the target/self state.
                // Do not rotate rounds yet.
                // Rotate only hidden context inputs entering unwind.
                //
                if (aDatum.mType == aStatement->mTarget) {
                    continue;
                }
                
                if (GARXSkeleton::IsRoundType(aDatum.mType)) {
                    continue;
                }
                
                if (aDatum.mType == GARXType::kCarry) {
                    continue;
                }
                
                if (GARXSkeleton::IsSecretContextType(aDatum.mType) == false) {
                    continue;
                }
                
                if (aRotationIndex >= aRotations.size()) {
                    return false;
                }
                
                aDatum.mRotationAmount = aRotations[aRotationIndex];
                aRotationIndex++;
            }
        }
    }
    
    return true;
}

static bool AssignSeedRotations(std::vector<GARXStatementGroup *> &pGroups) {
    
    std::vector<int> aRotations = MakeSeedRotationSchedule();
    std::size_t aRotationIndex = 0;
    
    for (GARXStatementGroup *aGroup: pGroups) {
        
        if (aGroup->mGroupType != GARXGroupType::kSeed) {
            continue;
        }
        
        if (aGroup->mStatements.size() <= 0) {
            continue;
        }
        
        GARXStatementPlan *aStatement = aGroup->mStatements[0];
        if (aStatement == nullptr) {
            continue;
        }
        
        if (aRotationIndex >= aRotations.size()) {
            return false;
        }
        
        // Seed statement shape:
        // target <- state + tap + hot_add ...
        // datum 0 = state
        // datum 1 = stream tap
        if (aStatement->mDatums.size() > 1) {
            GARXDatum &aTapDatum = aStatement->mDatums[1];
            if (aTapDatum.mKind == GARXDatumKind::kType) {
                aTapDatum.mRotationAmount = aRotations[aRotationIndex];
            }
        }
        
        aRotationIndex++;
    }
    
    return (aRotationIndex == aRotations.size());
}

static bool AssignLoopSaltOffsets(std::vector<GARXStatementGroup *> &pGroups,
                                  std::size_t pPassIndex) {
    
    int aLoopKeySlotCount = CountLoopKeySlots(pGroups);
    
    if (aLoopKeySlotCount <= 0) {
        return true;
    }
    
    std::vector<int> aOffsets = MakeLoopSaltOffsetSchedule(aLoopKeySlotCount, pPassIndex);
    
    if (static_cast<int>(aOffsets.size()) != aLoopKeySlotCount) {
        return false;
    }
    
    std::size_t aOffsetIndex = 0;
    
    for (GARXStatementGroup *aGroup: pGroups) {
        
        for (GARXStatementPlan *aStatement: aGroup->mStatements) {
            
            std::vector<GARXDatum *> aLoopDatums;
            
            for (GARXDatum &aDatum: aStatement->mDatums) {
                if (aDatum.mKind == GARXDatumKind::kLoopKey) {
                    aLoopDatums.push_back(&aDatum);
                }
            }
            
            if (aLoopDatums.empty()) {
                continue;
            }
            
            if (aLoopDatums.size() == 1) {
                
                if (aOffsetIndex >= aOffsets.size()) {
                    return false;
                }
                
                aLoopDatums[0]->mOffsetAmount = aOffsets[aOffsetIndex];
                aOffsetIndex++;
                
            } else if (aLoopDatums.size() == 2) {
                
                if (aOffsetIndex + 1 >= aOffsets.size()) {
                    return false;
                }
                
                int aOffsetA = aOffsets[aOffsetIndex];
                int aOffsetB = aOffsets[aOffsetIndex + 1];
                
                if (LoopSaltOffsetsAreComplements(aOffsetA, aOffsetB) ||
                    LoopSaltOffsetsAreTooClose(aOffsetA, aOffsetB)) {
                    
                    bool aDidFix = false;
                    
                    for (std::size_t k = aOffsetIndex + 2; k < aOffsets.size(); k++) {
                        if ((LoopSaltOffsetsAreComplements(aOffsetA, aOffsets[k]) == false) &&
                            (LoopSaltOffsetsAreTooClose(aOffsetA, aOffsets[k]) == false)) {
                            
                            std::swap(aOffsets[aOffsetIndex + 1], aOffsets[k]);
                            aOffsetB = aOffsets[aOffsetIndex + 1];
                            aDidFix = true;
                            break;
                        }
                    }
                    
                    if (aDidFix == false) {
                        return false;
                    }
                }
                
                aLoopDatums[0]->mOffsetAmount = aOffsetA;
                aLoopDatums[1]->mOffsetAmount = aOffsetB;
                
                aOffsetIndex += 2;
                
            } else {
                return false;
            }
        }
    }
    
    return (aOffsetIndex == aOffsets.size());
}

static bool AssignSaltDomains(std::vector<GARXStatementGroup *> &pGroups,
                              std::size_t pPassIndex) {
    
    std::size_t aSeedLoopKeyIndex = 0;
    std::size_t aUnwindLoopKeyIndex = 0;
    std::size_t aForwardPlugGroupIndex = 0;
    
    for (GARXStatementGroup *aGroup: pGroups) {
        
        if (aGroup->mGroupType == GARXGroupType::kForwardTriplet) {
            
            std::size_t aPlugIndexInGroup = 0;
            
            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                
                if (aStatement == nullptr) {
                    continue;
                }
                
                for (GARXDatum &aDatum: aStatement->mDatums) {
                    
                    if (aDatum.mKind == GARXDatumKind::kPlugKey) {
                        aDatum.mSaltDomain = PickPlugSaltDomainForSlot(aPlugIndexInGroup,
                                                                       aForwardPlugGroupIndex,
                                                                       pPassIndex);
                        aPlugIndexInGroup++;
                    }
                }
            }
            
            if (aPlugIndexInGroup > 0) {
                aForwardPlugGroupIndex++;
            }
            
            continue;
        }
        
        for (GARXStatementPlan *aStatement: aGroup->mStatements) {
            
            std::size_t aLoopKeyIndexInStatement = 0;
            
            for (GARXDatum &aDatum: aStatement->mDatums) {
                
                if (aDatum.mKind != GARXDatumKind::kLoopKey) {
                    continue;
                }
                
                if (aGroup->mGroupType == GARXGroupType::kSeed) {
                    
                    aDatum.mSaltDomain = PickLoopSaltDomainForStatement(aGroup->mGroupType,
                                                                        aSeedLoopKeyIndex,
                                                                        aLoopKeyIndexInStatement);
                    aSeedLoopKeyIndex++;
                    
                } else if (aGroup->mGroupType == GARXGroupType::kUnwind) {
                    
                    aDatum.mSaltDomain = PickLoopSaltDomainForStatement(aGroup->mGroupType,
                                                                        aUnwindLoopKeyIndex,
                                                                        aLoopKeyIndexInStatement);
                    aUnwindLoopKeyIndex++;
                    
                } else {
                    return false;
                }
                
                if (aDatum.mSaltDomain == GARXSaltDomain::kInv) {
                    return false;
                }
                
                aLoopKeyIndexInStatement++;
            }
        }
    }
    
    return true;
}



GARXDatum::GARXDatum() {
    mKind = GARXDatumKind::kInv;
    mType = GARXType::kInv;
    mOffsetAmount = -1;
    mRotationAmount = -1;
    mPlugTypeA = GARXType::kInv;
    mPlugTypeB = GARXType::kInv;
    mIsLoopIndexInverted = false;
    //mSaltBankIndex = -1;
    mSaltDomain = GARXSaltDomain::kInv;
    
}

GARXStatementPlan::GARXStatementPlan() {
    mStatementType = GARXStatementType::kInv;
    mGroupType = GARXGroupType::kInv;
    mTarget = GARXType::kInv;
    mRotationAmount = -1;
}

GARXStatementPlan::GARXStatementPlan(GARXStatementType pType, GARXType pTarget) {
    mStatementType = pType;
    mGroupType = GARXGroupType::kInv;
    mTarget = pTarget;
    mRotationAmount = -1;
}

GARXRoundSeedPlan::GARXRoundSeedPlan() {
    mTarget = GARXType::kInv;
    mState = GARXType::kInv;
    mTap = GARXType::kInv;
}

GARXRoundSeedPlan::GARXRoundSeedPlan(GARXType pTarget,
                                         GARXType pState,
                                         GARXType pTap) {
    mTarget = pTarget;
    mState = pState;
    mTap = pTap;
}

GARXPassPlan::GARXPassPlan() {
    
}

GARXPassPlan::~GARXPassPlan() {
    for (int aIndex=0; aIndex<mRoundSeeds.size(); aIndex++) {
        delete mRoundSeeds[aIndex];
    }
    mRoundSeeds.clear();
    
    for (int aIndex=0; aIndex<mGroups.size(); aIndex++) {
        delete mGroups[aIndex];
    }
    mGroups.clear();
    
    
    for (int aIndex=0; aIndex<mStatements.size(); aIndex++) {
        delete mStatements[aIndex];
    }
    mStatements.clear();
}

GARXStatementGroup::GARXStatementGroup() {
    mGroupType = GARXGroupType::kInv;
    mZoneIndex = -1;
}

GARXStatementGroup::GARXStatementGroup(GARXGroupType pKind) {
    mGroupType = pKind;
    mZoneIndex = -1;
}

GARXPlan::GARXPlan() {
    
}

GARXPlan::~GARXPlan() {
    for (int aIndex=0; aIndex<mPassPlans.size(); aIndex++) {
        delete mPassPlans[aIndex];
    }
    mPassPlans.clear();
}

bool GARXPlan::Bake(GARXPlan *pPlan) {
    if (pPlan == nullptr) {
        printf("fatal: tried to bake a null GARXPlan plan\n");
        exit(0);
    }
    
    int aAttempt = 0;
    const int aMaxAttempts = 10000;
    
    while (aAttempt < aMaxAttempts) {
        if (Configure(pPlan) == false) {
            aAttempt++;
            continue;
        }

        if (IsValid(pPlan)) {
            return true;
        } else {
            aAttempt++;
        }
    }
    
    printf("GARXPlan::Bake failed after %d attempts\n", aMaxAttempts);
    
    return false;
}

static int ScatterRotationPoolIndex(int pRotation) {
    for (std::size_t p = 0; p < cScatterRotationPools.size(); p++) {
        for (int aRotation: cScatterRotationPools[p]) {
            if (aRotation == pRotation) {
                return static_cast<int>(p);
            }
        }
    }
    return -1;
}

bool GARXPlan::Configure(GARXPlan *pPlan) {
    
    for (GARXPassPlan *aPassPlan: pPlan->mPassPlans) {
            delete aPassPlan;
    }
    pPlan->mPassPlans.clear();
    
    
    std::vector<GARXType> aRounds = {
        GARXType::kRoundA,
        GARXType::kRoundB,
        GARXType::kRoundC,
        GARXType::kRoundD,
        GARXType::kRoundE,
        GARXType::kRoundF
    };
    
    for (std::size_t i = 0; i < pPlan->mSkeleton.mPasses.size(); i++) {
        
        GARXPassPlan *aPassPlan = new GARXPassPlan();
        
        aPassPlan->mStreamInputBlend = MakeBlendPlan();
        aPassPlan->mSecretInputBlend = MakeBlendPlan();
        aPassPlan->mCrossInputBlend = MakeBlendPlan();
        aPassPlan->mStreamScatterBlend = MakeBlendPlan();
        aPassPlan->mSecretScatterBlend = MakeBlendPlan();
        
        aPassPlan->mCrushPlan = MakeCrushPlan(i);
        aPassPlan->mCarryPlan = MakeCarryPlan(i);
        
        std::vector<GARXType> aInitializationStates = {
            GARXType::kStateA,
            GARXType::kStateB,
            GARXType::kStateC,
            GARXType::kStateD,
            GARXType::kStateE,
            GARXType::kStateF
        };
        
        Random::Shuffle(&aInitializationStates);
        
        std::vector<GARXType> aSeedTaps;
        
        do {
            aSeedTaps.clear();
            for (std::size_t n = 0; n < cAllowedSeedTaps.size(); n++) {
                aSeedTaps.push_back(Random::Choice(cAllowedSeedTaps[n]));
            }
            
        } while (IsValidSeedTapConfiguration(aSeedTaps) == false);
        
        for (std::size_t n = 0; n < aRounds.size(); n++) {
            GARXRoundSeedPlan *aSeed = new GARXRoundSeedPlan(
                                      aRounds[n],
                                      aInitializationStates[n],
                                      aSeedTaps[n]
                                      );
            
            aPassPlan->mRoundSeeds.push_back(aSeed);
            
            GARXStatementPlan *aStatement = MakeSeedStatement(aSeed, n);
            aPassPlan->mStatements.push_back(aStatement);
            
            GARXStatementGroup *aGroup = new GARXStatementGroup(GARXGroupType::kSeed);
            aGroup->mStatements.push_back(aStatement);
            aPassPlan->mGroups.push_back(aGroup);
        }
        
        const GARXSkeletonPass &aSkeletonRound = pPlan->mSkeleton.mPasses[i];
        
        for (std::size_t n = 0; n < aSkeletonRound.mForward.size(); n++) {
            const GARXSkeletonForwardRound &aForward = aSkeletonRound.mForward[n];
            
            GARXStatementPlan *aLeadStatement = MakeForwardLeadStatement(aForward);
            GARXStatementPlan *aFeedbackStatement = MakeForwardFeedbackStatement(aForward);
            GARXStatementPlan *aRotateStatement = MakeForwardRotateStatement(aForward);
            
            aPassPlan->mStatements.push_back(aLeadStatement);
            aPassPlan->mStatements.push_back(aFeedbackStatement);
            aPassPlan->mStatements.push_back(aRotateStatement);
            
            GARXStatementGroup *aGroup = new GARXStatementGroup(GARXGroupType::kForwardTriplet);
            aGroup->mStatements.push_back(aLeadStatement);
            aGroup->mStatements.push_back(aFeedbackStatement);
            aGroup->mStatements.push_back(aRotateStatement);
            aPassPlan->mGroups.push_back(aGroup);
        }
        
        GARXStatementPlan *aCrushStatement = new GARXStatementPlan(GARXStatementType::kCrush, GARXType::kSecretCurrent);
        aPassPlan->mStatements.push_back(aCrushStatement);

        GARXStatementGroup *aGroup = new GARXStatementGroup(GARXGroupType::kCrush);
        aGroup->mStatements.push_back(aCrushStatement);
        aPassPlan->mGroups.push_back(aGroup);
        
        
        if (BuildUnwindStatementsForPass(aPassPlan, aSkeletonRound) == false) {
            delete aPassPlan;
            continue;
        }
        
        GARXStatementPlan *aCarryStatement =
            new GARXStatementPlan(GARXStatementType::kCarry, GARXType::kCarry);

        aPassPlan->mStatements.push_back(aCarryStatement);

        GARXStatementGroup *aCarryGroup = new GARXStatementGroup(GARXGroupType::kCarry);
        aCarryGroup->mStatements.push_back(aCarryStatement);
        aPassPlan->mGroups.push_back(aCarryGroup);

        pPlan->mPassPlans.push_back(aPassPlan);
    }
    
    for (GARXPassPlan *aPassPlan: pPlan->mPassPlans) {
        
        for (std::size_t g = 0; g < aPassPlan->mGroups.size(); g++) {
            
            GARXStatementGroup *aGroup = aPassPlan->mGroups[g];
            
            aGroup->mZoneIndex = static_cast<int>(g);
            
            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                if (aStatement != nullptr) {
                    aStatement->mGroupType = aGroup->mGroupType;
                }
            }
        }
    }
    
    return Configure_ProceedWithGroups(pPlan);
}

bool GARXPlan::Configure_ProceedWithGroups(GARXPlan *pPlan) {
    
    int aPassIndex = 0;
    for (GARXPassPlan *aPassPlan: pPlan->mPassPlans) {
        
        GARXPlugMapper *aMapper = new GARXPlugMapper(aPassPlan->mGroups);
        
        bool aReloop = true;
        while (aReloop == true) {
            aReloop = false;
            if (!aMapper->AttemptAssignment()) {
                aReloop = true;
            }
        }

        delete aMapper;
        
        if (AssignSeedRotations(aPassPlan->mGroups) == false) {
            return false;
        }
        
        if (AssignUnwindRotations(aPassPlan->mGroups) == false) {
            return false;
        }
        
        if (AssignForwardRotations(aPassPlan->mGroups) == false) {
            return false;
        }
        
        if (AssignLoopSaltOffsets(aPassPlan->mGroups, aPassIndex) == false) {
            return false;
        }
        
        if (AssignSaltDomains(aPassPlan->mGroups, aPassIndex) == false) {
            return false;
        }
        
        aPassIndex++;
    }
    
    return true;
}

static bool IsPlugSaltDomain(GARXSaltDomain pDomain) {
    return (pDomain == GARXSaltDomain::kPlugA) ||
           (pDomain == GARXSaltDomain::kPlugB);
}

static bool IsValidCrushPlan(const GARXCrushPlan &pCrushPlan,
                             std::size_t pPassIndex) {
    
    const GARXCrushPairPlan aPairs[3] = {
        pCrushPlan.mPairA,
        pCrushPlan.mPairB,
        pCrushPlan.mPairC
    };
    
    std::unordered_set<GARXType, GARXTypeHash> aTypes;
    
    for (int i = 0; i < 3; i++) {
        if (GARXSkeleton::IsRoundType(aPairs[i].mTypeA) == false ||
            GARXSkeleton::IsRoundType(aPairs[i].mTypeB) == false) {
            printf("re-roll: pass %zu crush has invalid round type\n", pPassIndex);
            return false;
        }
        
        if (aPairs[i].mTypeA == aPairs[i].mTypeB) {
            printf("re-roll: pass %zu crush repeats round inside pair\n", pPassIndex);
            return false;
        }
        
        if (aPairs[i].mRotationAmount < 0) {
            printf("re-roll: pass %zu crush has invalid rotation\n", pPassIndex);
            return false;
        }
        
        aTypes.insert(aPairs[i].mTypeA);
        aTypes.insert(aPairs[i].mTypeB);
    }
    
    if (aTypes.size() != 6) {
        printf("re-roll: pass %zu crush does not cover six unique rounds\n", pPassIndex);
        return false;
    }
    
    return true;
}

static bool StatementHasValidPlugDatums(const GARXStatementPlan &pStatement,
                                        std::size_t pPassIndex,
                                        std::size_t pStatementIndex) {
    
    for (const GARXDatum &aDatum: pStatement.mDatums) {
        
        if (aDatum.mKind != GARXDatumKind::kPlugKey) {
            continue;
        }
        
        if (aDatum.mPlugTypeA == GARXType::kInv) {
            printf("re-roll: pass %zu statement %zu has invalid plug type A\n",
                   pPassIndex,
                   pStatementIndex);
            return false;
        }
        
        if (aDatum.mPlugTypeB == GARXType::kInv) {
            printf("re-roll: pass %zu statement %zu has invalid plug type B\n",
                   pPassIndex,
                   pStatementIndex);
            return false;
        }
        
        if (aDatum.mPlugTypeA == aDatum.mPlugTypeB) {
            printf("re-roll: pass %zu statement %zu has self plug pair, type=%s\n",
                   pPassIndex,
                   pStatementIndex,
                   GARXSkeleton::GetTypeName(aDatum.mPlugTypeA));
            return false;
        }
        
        if (aDatum.mRotationAmount < 0) {
            printf("re-roll: pass %zu statement %zu has unassigned plug rotation\n",
                   pPassIndex,
                   pStatementIndex);
            return false;
        }
        
        if (aDatum.mOffsetAmount < 0) {
            printf("re-roll: pass %zu statement %zu has unassigned plug offset\n",
                   pPassIndex,
                   pStatementIndex);
            return false;
        }
        
        if (IsPlugSaltDomain(aDatum.mSaltDomain) == false) {
            printf("re-roll: pass %zu statement %zu has invalid plug salt domain, domain=%s\n",
                   pPassIndex,
                   pStatementIndex,
                   GARXSkeleton::GetSaltDomainName(aDatum.mSaltDomain));
            return false;
        }
    }
    
    return true;
}

static bool IsPlanBackedStatement(GARXStatementType pType) {
    return (pType == GARXStatementType::kCrush) ||
           (pType == GARXStatementType::kCarry);
}


static bool IsValidStatement(const GARXStatementPlan &pStatement) {
    
    if (pStatement.mStatementType == GARXStatementType::kInv) {
        return false;
    }
    
    if (IsPlanBackedStatement(pStatement.mStatementType) == false) {
        if (pStatement.mTarget == GARXType::kInv) {
            return false;
        }
    }
    
    if (IsPlanBackedStatement(pStatement.mStatementType) == false) {
        if (pStatement.mDatums.empty()) {
            return false;
        }
    }
    
    for (const GARXDatum &aDatum: pStatement.mDatums) {
        if (aDatum.mKind == GARXDatumKind::kInv) {
            return false;
        }
    }
    
    return true;
}

static bool PassHasUniqueTypeRotationsByGroup(GARXPassPlan *pPassPlan) {
    
    std::unordered_set<GARXTypeRotationKey, GARXTypeRotationKeyHash> aSeedUsed;
    std::unordered_set<GARXTypeRotationKey, GARXTypeRotationKeyHash> aPlugUsed;
    std::unordered_set<GARXTypeRotationKey, GARXTypeRotationKeyHash> aUnwindUsed;
    
    for (GARXStatementPlan *aStatement: pPassPlan->mStatements) {
        
        for (const GARXDatum &aDatum: aStatement->mDatums) {
            
            if (aStatement->mStatementType == GARXStatementType::kRoundSeed) {
                
                if (aDatum.mKind == GARXDatumKind::kType) {
                    if (InsertTypeRotationKey(&aSeedUsed,
                                              aDatum.mType,
                                              aDatum.mRotationAmount) == false) {
                        printf("duplicate seed rotation\n");
                        return false;
                    }
                }
                
            } else if (aStatement->mStatementType == GARXStatementType::kUnwind) {
                
                if (aDatum.mKind == GARXDatumKind::kType) {
                    if (InsertTypeRotationKey(&aUnwindUsed,
                                              aDatum.mType,
                                              aDatum.mRotationAmount) == false) {
                        printf("duplicate unwind rotation\n");
                        return false;
                    }
                }
                
            } else {
                
                if (aDatum.mKind == GARXDatumKind::kPlugKey) {
                    if (InsertTypeRotationKey(&aPlugUsed,
                                              aDatum.mPlugTypeA,
                                              aDatum.mRotationAmount) == false) {
                        printf("duplicate plug rotation\n");
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

static bool IsLoopSaltDomain(GARXSaltDomain pDomain) {
    return (pDomain == GARXSaltDomain::kInitA) ||
           (pDomain == GARXSaltDomain::kInitB) ||
           (pDomain == GARXSaltDomain::kUnwindA) ||
           (pDomain == GARXSaltDomain::kUnwindB);
}

static bool StatementHasValidLoopKeyDatums(const GARXStatementPlan &pStatement,
                                           std::size_t pPassIndex,
                                           std::size_t pStatementIndex) {
    
    for (const GARXDatum &aDatum: pStatement.mDatums) {
        
        if (aDatum.mKind != GARXDatumKind::kLoopKey) {
            continue;
        }
        
        if (aDatum.mOffsetAmount < 0) {
            printf("re-roll: pass %zu statement %zu has unassigned loop-key offset\n",
                   pPassIndex,
                   pStatementIndex);
            return false;
        }
        
        if (IsLoopSaltDomain(aDatum.mSaltDomain) == false) {
            printf("re-roll: pass %zu statement %zu has invalid loop-key salt domain, domain=%s\n",
                   pPassIndex,
                   pStatementIndex,
                   GARXSkeleton::GetSaltDomainName(aDatum.mSaltDomain));
            return false;
        }
    }
    
    return true;
}

bool GARXPlan::IsValid(GARXPlan *pPlan) {
    
    if (pPlan == nullptr) {
        printf("re-roll: plan is null\n");
        return false;
    }
    
    if (pPlan->mPassPlans.size() != pPlan->mSkeleton.mPasses.size()) {
        printf("re-roll: pass count mismatch, passPlans=%zu skeletonPasses=%zu\n",
               pPlan->mPassPlans.size(),
               pPlan->mSkeleton.mPasses.size());
        return false;
    }
    
    for (std::size_t aPassIndex = 0; aPassIndex < pPlan->mPassPlans.size(); aPassIndex++) {
        
        GARXPassPlan *aPassPlan = pPlan->mPassPlans[aPassIndex];
        
        if (aPassPlan == nullptr) {
            printf("re-roll: pass %zu is null\n", aPassIndex);
            return false;
        }
        
        if (aPassPlan->mRoundSeeds.size() != 6) {
            printf("re-roll: pass %zu has wrong seed count, count=%zu\n",
                   aPassIndex,
                   aPassPlan->mRoundSeeds.size());
            return false;
        }
        
        if (aPassPlan->mStatements.size() < aPassPlan->mRoundSeeds.size()) {
            printf("re-roll: pass %zu has too few statements, statements=%zu seeds=%zu\n",
                   aPassIndex,
                   aPassPlan->mStatements.size(),
                   aPassPlan->mRoundSeeds.size());
            return false;
        }
        
        for (std::size_t aStatementIndex = 0;
             aStatementIndex < aPassPlan->mStatements.size();
             aStatementIndex++) {
            
            GARXStatementPlan *aStatement = aPassPlan->mStatements[aStatementIndex];
            
            if (aStatement == nullptr) {
                printf("re-roll: pass %zu statement %zu is null\n",
                       aPassIndex,
                       aStatementIndex);
                return false;
            }
            
            if (IsValidStatement(*aStatement) == false) {
                printf("re-roll: pass %zu statement %zu is invalid, type=%s target=%s\n",
                       aPassIndex,
                       aStatementIndex,
                       GARXSkeleton::GetStatementKindName(aStatement->mStatementType),
                       GARXSkeleton::GetTypeName(aStatement->mTarget));
                return false;
            }
            
            
            if (StatementHasValidPlugDatums(*aStatement,
                                            aPassIndex,
                                            aStatementIndex) == false) {
                printf("re-roll: pass %zu statement %zu is invalid plug datums.\n",
                       aPassIndex,
                       aStatementIndex);
                return false;
            }
            
            if (StatementHasValidLoopKeyDatums(*aStatement,
                                               aPassIndex,
                                               aStatementIndex) == false) {
                printf("re-roll: pass %zu statement %zu is invalid loopsalt datums.\n",
                       aPassIndex,
                       aStatementIndex);
                return false;
            }
            
        }
        
        std::vector<GARXType> aSeedTaps;
        
        for (std::size_t aSeedIndex = 0;
             aSeedIndex < aPassPlan->mRoundSeeds.size();
             aSeedIndex++) {
            
            GARXRoundSeedPlan *aSeed = aPassPlan->mRoundSeeds[aSeedIndex];
            
            if (aSeed == nullptr) {
                printf("re-roll: pass %zu seed %zu is null\n",
                       aPassIndex,
                       aSeedIndex);
                return false;
            }
            
            if (aSeed->mTarget == GARXType::kInv) {
                printf("re-roll: pass %zu seed %zu has invalid target\n",
                       aPassIndex,
                       aSeedIndex);
                return false;
            }
            
            if (aSeed->mState == GARXType::kInv) {
                printf("re-roll: pass %zu seed %zu has invalid state\n",
                       aPassIndex,
                       aSeedIndex);
                return false;
            }
            
            if (aSeed->mTap == GARXType::kInv) {
                printf("re-roll: pass %zu seed %zu has invalid tap\n",
                       aPassIndex,
                       aSeedIndex);
                return false;
            }
            
            aSeedTaps.push_back(aSeed->mTap);
        }
        
        if (SeedPlanGutsAreUnique(aPassPlan->mRoundSeeds) == false) {
            printf("re-roll: pass %zu seed guts are not unique\n",
                   aPassIndex);
            return false;
        }
        
        if (IsValidSeedTapConfiguration(aSeedTaps) == false) {
            printf("re-roll: pass %zu seed tap configuration is invalid\n",
                   aPassIndex);
            return false;
        }
        
        if (PassHasUniqueTypeRotationsByGroup(aPassPlan) == false) {
            printf("re-roll: pass %zu has duplicate type rotation inside a rotation domain\n",
                   aPassIndex);
            return false;
        }
        
    }
    
    return true;
}

void GARXPlan::Print(GARXPlan *pPlan) {
    GARXPlanPrinter::Print(pPlan);
}

static void PrintCrushPair(const GARXCrushPairPlan &pPair) {
    if (pPair.mRotateA) {
        printf("(rot(%s,%d) ^ %s)",
               GARXSkeleton::GetTypeName(pPair.mTypeA),
               pPair.mRotationAmount,
               GARXSkeleton::GetTypeName(pPair.mTypeB));
    } else {
        printf("(%s ^ rot(%s,%d))",
               GARXSkeleton::GetTypeName(pPair.mTypeA),
               GARXSkeleton::GetTypeName(pPair.mTypeB),
               pPair.mRotationAmount);
    }
}

static void PrintCrushPlan(const GARXCrushPlan &pCrushPlan) {
    printf("input = diffuse(");
    PrintCrushPair(pCrushPlan.mPairA);
    printf(" + ");
    PrintCrushPair(pCrushPlan.mPairB);
    printf(" + ");
    PrintCrushPair(pCrushPlan.mPairC);
    printf(" + scatter + carry)\n");
    printf("input = mix64_8(input, gate_prism_8_8)\n");
}

void GARXPlan::Print(GARXPlan *pPlan,
                     bool pIncludePlugs,
                     bool pIncludeRotations) {
    GARXPlanPrinter::Print(pPlan, pIncludePlugs, pIncludeRotations);
}

void GARXPlanPrinter::Print(GARXPlan *pPlan) {
    Print(pPlan, true, true);
}

void GARXPlanPrinter::Print(GARXPlan *pPlan,
                            bool pIncludePlugs,
                            bool pIncludeRotations) {
    
    if (pPlan == nullptr) {
        printf("GARXPlan: null\n");
        return;
    }
    
    printf("\nGARX PLAN\n");
    printf("=========\n");
    
    for (std::size_t i = 0; i < pPlan->mPassPlans.size(); i++) {
        
        GARXPassPlan *aPassPlan = pPlan->mPassPlans[i];
        if (aPassPlan == nullptr) {
            continue;
        }
        
        printf("\nPASS %zu\n", i);
        printf("------\n\n");
        
        PrintBlendPlan(aPassPlan->mStreamInputBlend,
                       "stream_input",
                       "stream_input",
                       pIncludeRotations);
        PrintBlendPlan(aPassPlan->mSecretInputBlend,
                       "secret_input",
                       "secret_input",
                       pIncludeRotations);
        PrintBlendPlan(aPassPlan->mCrossInputBlend,
                       "cross_input",
                       "cross_input",
                       pIncludeRotations);
        PrintBlendPlan(aPassPlan->mStreamScatterBlend,
                       "stream_scatter",
                       "stream_scatter",
                       pIncludeRotations);
        PrintBlendPlan(aPassPlan->mSecretScatterBlend,
                       "secret_scatter",
                       "secret_scatter",
                       pIncludeRotations);
        
        GARXGroupType aPreviousKind = GARXGroupType::kInv;
        
        for (std::size_t g = 0; g < aPassPlan->mGroups.size(); g++) {
            
            GARXStatementGroup *aGroup = aPassPlan->mGroups[g];
            if (aGroup == nullptr) {
                continue;
            }
            
            
            
            bool aNeedsBlankLine = false;
            
            if (g > 0) {
                if (aGroup->mGroupType == GARXGroupType::kForwardTriplet) {
                    aNeedsBlankLine = true;
                } else if (aGroup->mGroupType == GARXGroupType::kCrush) {
                    aNeedsBlankLine = true;
                } else if (aGroup->mGroupType == GARXGroupType::kUnwind &&
                           aPreviousKind != GARXGroupType::kUnwind) {
                    aNeedsBlankLine = true;
                }
            }
            
            if (aNeedsBlankLine) {
                printf("\n");
            }
            
            printf("[zone %d: %s]\n",
                   aGroup->mZoneIndex,
                   GARXStatementGroup::GetTypeName(aGroup->mGroupType));
            
            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                
                if (aStatement->mStatementType == GARXStatementType::kCrush) {
                    PrintCrushPlan(aPassPlan->mCrushPlan);
                } else {
                    PrintStatementCompact(*aStatement,
                                          pIncludePlugs,
                                          pIncludeRotations);
                }
                
            }
            
            aPreviousKind = aGroup->mGroupType;
        }
        
        printf("\n");
    }
    
    printf("\n");
}
