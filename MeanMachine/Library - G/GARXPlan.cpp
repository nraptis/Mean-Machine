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
        { GARXType::kUnwindA, GARXType::kUnwindD },
        { GARXType::kUnwindB, GARXType::kUnwindE },
        { GARXType::kUnwindC, GARXType::kUnwindF }
    },
    {
        { GARXType::kUnwindA, GARXType::kUnwindE },
        { GARXType::kUnwindB, GARXType::kUnwindF },
        { GARXType::kUnwindC, GARXType::kUnwindD }
    },
    {
        { GARXType::kUnwindA, GARXType::kUnwindF },
        { GARXType::kUnwindB, GARXType::kUnwindD },
        { GARXType::kUnwindC, GARXType::kUnwindE }
    },
    {
        { GARXType::kUnwindA, GARXType::kUnwindB },
        { GARXType::kUnwindC, GARXType::kUnwindD },
        { GARXType::kUnwindE, GARXType::kUnwindF }
    }
};

static std::vector<std::vector<GARXTypePair>> cCrushPairPatterns = {
    {
        { GARXType::kOrbiterA, GARXType::kOrbiterB },
        { GARXType::kOrbiterC, GARXType::kOrbiterD },
        { GARXType::kOrbiterE, GARXType::kOrbiterF }
    },
    {
        { GARXType::kOrbiterA, GARXType::kOrbiterD },
        { GARXType::kOrbiterB, GARXType::kOrbiterE },
        { GARXType::kOrbiterC, GARXType::kOrbiterF }
    },
    {
        { GARXType::kOrbiterA, GARXType::kOrbiterE },
        { GARXType::kOrbiterB, GARXType::kOrbiterF },
        { GARXType::kOrbiterC, GARXType::kOrbiterD }
    },
    {
        { GARXType::kOrbiterA, GARXType::kOrbiterF },
        { GARXType::kOrbiterB, GARXType::kOrbiterD },
        { GARXType::kOrbiterC, GARXType::kOrbiterE }
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
        
        if (aBackward.mShape != GARXUnwindShape::kOrbiterPair) {
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

static bool UnwindRowGetsPlugKey(std::size_t pBackwardIndex) {
    switch (pBackwardIndex) {
        case 0:
        case 3:
            return true;
            
        default:
            return false;
    }
}

static GARXStatementPlan *MakeUnwindStatement(const GARXSkeletonBackwardRound &pBackward,
                                              std::size_t pBackwardIndex) {
    
    GARXStatementPlan *aStatement = new GARXStatementPlan(GARXStatementType::kUnwind,
                                                          pBackward.mTarget);
    
    //
    // target = target OP inputA OP inputB OP inputC OP plug_key
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
    
    if (UnwindRowGetsPlugKey(pBackwardIndex)) {
        aStatement->mDatums.push_back(MakePlugKeyDatum(GARXType::kInv, GARXType::kInv));
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
    
    std::vector<GARXType> aOrbiters = {
        GARXType::kOrbiterA,
        GARXType::kOrbiterB,
        GARXType::kOrbiterC,
        GARXType::kOrbiterD,
        GARXType::kOrbiterE,
        GARXType::kOrbiterF
    };
    
    Random::Shuffle(&aOrbiters);
    
    //
    // Assign 4 unique rounds to the 4 contextual unwind rows.
    // This keeps the contextual unwind pressure spread out before statements
    // are ever built.
    //
    for (std::size_t i = 0; i < aContextualIndexes.size(); i++) {
        int aBackwardIndex = aContextualIndexes[i];
        (*pBackward)[aBackwardIndex].mInputC = aOrbiters[i];
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
    
    for (std::size_t n = 0; n < aBackward.size(); n++) {
        GARXStatementPlan *aUnwindStatement = MakeUnwindStatement(aBackward[n],
                                                                  n);
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

static GARXBlendInputPlan MakeBlendPlan() {
    GARXBlendInputPlan aPlan;
    std::vector<std::vector<int>> aPools = cScatterRotationPools;
    Random::Shuffle(&aPools);
    aPlan.mRotationA = Random::Choice(aPools[0]);
    aPlan.mRotationB = Random::Choice(aPools[1]);
    aPlan.mRotationC = Random::Choice(aPools[2]);
    aPlan.mRotationD = Random::Choice(aPools[3]);
    return aPlan;
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

GARXBlendInputPlan::GARXBlendInputPlan() {
    mRotationA = -1; mRotationB = -1; mRotationC = -1; mRotationD = -1;
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

    if (pSeedIndex == 2 || pSeedIndex == 3) {
        aStatement->mDatums.push_back(MakePlugKeyDatum(GARXType::kInv, GARXType::kInv));
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

static int CountForwardTripletGroups(const std::vector<GARXStatementGroup *> &pGroups) {
    int aResult = 0;
    for (GARXStatementGroup *aGroup: pGroups) {
        if (aGroup != nullptr && aGroup->mGroupType == GARXGroupType::kForwardTriplet) {
            aResult++;
        }
    }
    return aResult;
}

static std::vector<int> MakeForwardRotationSchedule(std::size_t pCount) {
    
    std::vector<int> aByteAligned = cByteAlignedRotations;
    std::vector<int> aOdd = cOddRotations;
    
    Random::Shuffle(&aByteAligned);
    Random::Shuffle(&aOdd);
    
    std::size_t aByteAlignedCount = 2;
    if (Random::Bool()) {
        aByteAlignedCount++;
    }
    if (Random::Bool()) {
        aByteAlignedCount++;
    }

    if (aByteAlignedCount > pCount) {
        aByteAlignedCount = pCount;
    }

    std::size_t aOddCount = pCount - aByteAlignedCount;
    if (aOddCount > aOdd.size()) {
        aOddCount = aOdd.size();
        aByteAlignedCount = pCount - aOddCount;
    }
    if (aByteAlignedCount > aByteAligned.size()) {
        return {};
    }
    
    std::vector<int> aResult;
    
    for (std::size_t i = 0; i < aByteAlignedCount; i++) {
        aResult.push_back(aByteAligned[i]);
    }
    
    for (std::size_t i = 0; i < aOddCount; i++) {
        aResult.push_back(aOdd[i]);
    }
    
    Random::Shuffle(&aResult);
    
    if (aResult.size() != pCount) {
        return {};
    }
    
    return aResult;
}

static std::vector<int> MakeSeedRotationSchedule(std::size_t pCount) {
    
    std::vector<int> aPool = cSeedRotations;
    Random::Shuffle(&aPool);

    if (pCount > aPool.size()) {
        return {};
    }
    
    std::vector<int> aResult;
    
    for (std::size_t i = 0; i < pCount; i++) {
        aResult.push_back(aPool[i]);
    }
    
    return aResult;
}

static std::vector<int> MakeLoopSaltOffsetSchedule(int pCount,
                                                   std::size_t pPassIndex,
                                                   const GARXFormat &pFormat) {
    const std::vector<int> &aPassSaltBiases = pFormat.PassSaltBiases();
    int aPassBias = 0;
    if (aPassSaltBiases.empty() == false) {
        aPassBias = aPassSaltBiases[pPassIndex % aPassSaltBiases.size()];
    }
    
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
    
    const int aForwardTripletCount = CountForwardTripletGroups(pGroups);
    if (aForwardTripletCount < 0) {
        return false;
    }
    
    std::vector<int> aRotations = MakeForwardRotationSchedule(static_cast<std::size_t>(aForwardTripletCount));
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
    
    std::size_t aSeedCount = 0;
    for (GARXStatementGroup *aGroup: pGroups) {
        if (aGroup != nullptr && aGroup->mGroupType == GARXGroupType::kSeed) {
            aSeedCount++;
        }
    }
    
    std::vector<int> aRotations = MakeSeedRotationSchedule(aSeedCount);
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
                                  std::size_t pPassIndex,
                                  const GARXFormat &pFormat) {
    
    int aLoopKeySlotCount = CountLoopKeySlots(pGroups);
    
    if (aLoopKeySlotCount <= 0) {
        return true;
    }
    
    std::vector<int> aOffsets = MakeLoopSaltOffsetSchedule(aLoopKeySlotCount,
                                                           pPassIndex,
                                                           pFormat);
    
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

static bool AssignSaltLanes(std::vector<GARXStatementGroup *> &pGroups,
                            std::size_t pPassIndex,
                            const GARXFormat &pFormat) {
    
    std::size_t aSeedLoopKeyIndex = 0;
    std::size_t aSeedPlugKeyIndex = 0;
    std::size_t aUnwindLoopKeyIndex = 0;
    std::size_t aForwardPlugGroupIndex = 0;
    std::size_t aUnwindPlugKeyIndex = 0;
    
    for (GARXStatementGroup *aGroup: pGroups) {
        
        if (aGroup->mGroupType == GARXGroupType::kForwardTriplet) {
            
            std::size_t aPlugIndexInGroup = 0;
            
            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                
                if (aStatement == nullptr) {
                    continue;
                }
                
                for (GARXDatum &aDatum: aStatement->mDatums) {
                    
                    if (aDatum.mKind == GARXDatumKind::kPlugKey) {
                        aDatum.mSaltLaneIndex = pFormat.PickForwardPlugSaltLane(aPlugIndexInGroup,
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

                if (aDatum.mKind == GARXDatumKind::kPlugKey) {
                    if (aGroup->mGroupType == GARXGroupType::kSeed) {
                        aDatum.mSaltLaneIndex = pFormat.PickSeedPlugSaltLane(aSeedPlugKeyIndex);
                        aSeedPlugKeyIndex++;
                    } else if (aGroup->mGroupType == GARXGroupType::kUnwind) {
                        aDatum.mSaltLaneIndex = pFormat.PickUnwindPlugSaltLane(aUnwindPlugKeyIndex);
                        aUnwindPlugKeyIndex++;
                    } else {
                        return false;
                    }

                    if (aDatum.mSaltLaneIndex < 0) {
                        return false;
                    }
                    continue;
                }
                
                if (aDatum.mKind != GARXDatumKind::kLoopKey) {
                    continue;
                }
                
                if (aGroup->mGroupType == GARXGroupType::kSeed) {
                    
                    aDatum.mSaltLaneIndex = pFormat.PickLoopSaltLane(aGroup->mGroupType,
                                                                     aSeedLoopKeyIndex,
                                                                     aLoopKeyIndexInStatement);
                    aSeedLoopKeyIndex++;
                    
                } else if (aGroup->mGroupType == GARXGroupType::kUnwind) {
                    
                    aDatum.mSaltLaneIndex = pFormat.PickLoopSaltLane(aGroup->mGroupType,
                                                                     aUnwindLoopKeyIndex,
                                                                     aLoopKeyIndexInStatement);
                    aUnwindLoopKeyIndex++;
                    
                } else {
                    return false;
                }
                
                if (aDatum.mSaltLaneIndex < 0) { return false; }
                
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
    mSaltLaneIndex = -1;
    
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
    mFormat = &GARXFormatSixSixFour::Shared();
}

GARXPlan::~GARXPlan() {
    for (int aIndex=0; aIndex<mPasses.size(); aIndex++) {
        delete mPasses[aIndex];
    }
    mPasses.clear();
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

bool GARXPlan::Configure(GARXPlan *pPlan) {
    if (pPlan == nullptr) {
        return false;
    }

    if (pPlan->mFormat == nullptr) {
        pPlan->mFormat = &GARXFormatSixSixFour::Shared();
    }
    
    for (GARXPassPlan *aPassPlan: pPlan->mPasses) {
            delete aPassPlan;
    }
    pPlan->mPasses.clear();
    
    const std::vector<GARXType> aOrbiters = pPlan->mFormat->OrbiterTypes();
    if (aOrbiters.empty()) {
        return false;
    }
    if (pPlan->mSkeleton.mPasses.size() != pPlan->mFormat->PassCount()) {
        return false;
    }
    
    for (std::size_t i = 0; i < pPlan->mSkeleton.mPasses.size(); i++) {
        
        GARXPassPlan *aPassPlan = new GARXPassPlan();
        
        aPassPlan->mStreamInputBlend = MakeBlendPlan();
        aPassPlan->mSecretInputBlend = MakeBlendPlan();
        aPassPlan->mCrossInputBlend = MakeBlendPlan();
        aPassPlan->mStreamScatterBlend = MakeBlendPlan();
        aPassPlan->mSecretScatterBlend = MakeBlendPlan();
        
        aPassPlan->mCrushPlan = MakeCrushPlan(i);
        aPassPlan->mCarryPlan = MakeCarryPlan(i);
        
        std::vector<GARXType> aInitializationStates = pPlan->mFormat->UnwindTypes();
        if (aInitializationStates.size() != aOrbiters.size()) {
            delete aPassPlan;
            return false;
        }
        
        Random::Shuffle(&aInitializationStates);
        
        std::vector<GARXType> aSeedTaps;
        
        do {
            aSeedTaps.clear();
            for (std::size_t n = 0; n < aOrbiters.size(); n++) {
                const std::vector<GARXType> &aTapPool = cAllowedSeedTaps[n % cAllowedSeedTaps.size()];
                aSeedTaps.push_back(Random::Choice(aTapPool));
            }
            
        } while (IsValidSeedTapConfiguration(aSeedTaps) == false);
        
        for (std::size_t n = 0; n < aOrbiters.size(); n++) {
            GARXRoundSeedPlan *aSeed = new GARXRoundSeedPlan(
                                      aOrbiters[n],
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

        pPlan->mPasses.push_back(aPassPlan);
    }
    
    for (GARXPassPlan *aPassPlan: pPlan->mPasses) {
        
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
    if (pPlan == nullptr) {
        return false;
    }
    if (pPlan->mFormat == nullptr) {
        pPlan->mFormat = &GARXFormatSixSixFour::Shared();
    }
    
    int aPassIndex = 0;
    for (GARXPassPlan *aPassPlan: pPlan->mPasses) {
        if (aPassPlan == nullptr) {
            return false;
        }

        bool aPlugAssigned = false;
        for (int aAttempt = 0; aAttempt < 64; aAttempt++) {
            if (GARXAssignPlugs(aPassPlan->mGroups)) {
                aPlugAssigned = true;
                break;
            }
        }
        if (aPlugAssigned == false) {
            return false;
        }
        
        if (AssignSeedRotations(aPassPlan->mGroups) == false) {
            return false;
        }
        
        if (AssignUnwindRotations(aPassPlan->mGroups) == false) {
            return false;
        }
        
        if (AssignForwardRotations(aPassPlan->mGroups) == false) {
            return false;
        }
        
        if (AssignLoopSaltOffsets(aPassPlan->mGroups,
                                  static_cast<std::size_t>(aPassIndex),
                                  *pPlan->mFormat) == false) {
            return false;
        }
        
        if (AssignSaltLanes(aPassPlan->mGroups,
                            static_cast<std::size_t>(aPassIndex),
                            *pPlan->mFormat) == false) {
            return false;
        }
        
        aPassIndex++;
    }
    
    return true;
}

static bool StatementHasValidPlugDatums(const GARXStatementPlan &pStatement,
                                        std::size_t pPassIndex,
                                        std::size_t pStatementIndex,
                                        const GARXFormat &) {
    
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
        
        if (aDatum.mSaltLaneIndex < 0 || aDatum.mSaltLaneIndex >= 6) {
            printf("re-roll: pass %zu statement %zu has invalid plug salt lane, lane=%d\n",
                   pPassIndex,
                   pStatementIndex,
                   aDatum.mSaltLaneIndex);
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

static bool StatementHasValidLoopKeyDatums(const GARXStatementPlan &pStatement,
                                           std::size_t pPassIndex,
                                           std::size_t pStatementIndex,
                                           const GARXFormat &) {
    
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
        
        if (aDatum.mSaltLaneIndex < 0 || aDatum.mSaltLaneIndex >= 6) {
            printf("re-roll: pass %zu statement %zu has invalid loop-key salt lane, lane=%d\n",
                   pPassIndex,
                   pStatementIndex,
                   aDatum.mSaltLaneIndex);
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
    if (pPlan->mFormat == nullptr) {
        pPlan->mFormat = &GARXFormatSixSixFour::Shared();
    }
    
    if (pPlan->mPasses.size() != pPlan->mSkeleton.mPasses.size()) {
        printf("re-roll: pass count mismatch, passPlans=%zu skeletonPasses=%zu\n",
               pPlan->mPasses.size(),
               pPlan->mSkeleton.mPasses.size());
        return false;
    }
    
    for (std::size_t aPassIndex = 0; aPassIndex < pPlan->mPasses.size(); aPassIndex++) {
        
        GARXPassPlan *aPassPlan = pPlan->mPasses[aPassIndex];
        
        if (aPassPlan == nullptr) {
            printf("re-roll: pass %zu is null\n", aPassIndex);
            return false;
        }
        
        if (aPassPlan->mRoundSeeds.size() != pPlan->mFormat->PlanWidth()) {
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
                                            aStatementIndex,
                                            *pPlan->mFormat) == false) {
                printf("re-roll: pass %zu statement %zu is invalid plug datums.\n",
                       aPassIndex,
                       aStatementIndex);
                return false;
            }
            
            if (StatementHasValidLoopKeyDatums(*aStatement,
                                               aPassIndex,
                                               aStatementIndex,
                                               *pPlan->mFormat) == false) {
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
