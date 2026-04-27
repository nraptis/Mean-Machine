//
//  GSeedStepARecipe.cpp
//  MeanMachine
//
//  Created by Magneto on 4/27/26.
//

#include "GSeedStepARecipe.hpp"
#include "GLoopFragmentComposer.hpp"
#include <algorithm>
#include <set>

namespace {

struct SaltBehaviorAssignment {
    LoopSaltBehavior mValue = LoopSaltBehavior::kInv;
    LoopSaltBehavior mCarry = LoopSaltBehavior::kInv;
    LoopSaltBehavior mPermute = LoopSaltBehavior::kInv;
};

struct LoopContractPhaseChoice {
    std::vector<LoopSaltBehavior> mPreferenceOrder;
    LoopSaltBehavior mSelected = LoopSaltBehavior::kInv;
};

std::vector<LoopSaltBehavior> RandomOrder(const std::set<LoopSaltBehavior> &pSet) {
    std::vector<LoopSaltBehavior> aResult;
    for (const LoopSaltBehavior &aBehavior: pSet) {
        aResult.push_back(aBehavior);
    }
    Random::Shuffle(&aResult);
    return aResult;
}

SaltBehaviorAssignment AssignLoopContractBehaviors(
    const std::set<LoopSaltBehavior> &pValueOptions,
    const std::set<LoopSaltBehavior> &pCarryOptions,
    const std::set<LoopSaltBehavior> &pPermuteOptions) {
    
    LoopContractPhaseChoice aChoices[3];
    aChoices[0].mPreferenceOrder = RandomOrder(pValueOptions);
    aChoices[1].mPreferenceOrder = RandomOrder(pCarryOptions);
    aChoices[2].mPreferenceOrder = RandomOrder(pPermuteOptions);
    
    auto isEnabled = [](const std::vector<LoopSaltBehavior> &pList) {
        return pList.empty() == false;
    };
    
    auto isUniqueIfEnabled = [](LoopSaltBehavior a,
                                bool aEnabled,
                                LoopSaltBehavior b,
                                bool bEnabled) {
        if (!aEnabled || !bEnabled) { return true; }
        return a != b;
    };
    
    SaltBehaviorAssignment aResult;
    aResult.mValue = LoopSaltBehavior::kInv;
    aResult.mCarry = LoopSaltBehavior::kInv;
    aResult.mPermute = LoopSaltBehavior::kInv;
    
    bool aValueEnabled = isEnabled(aChoices[0].mPreferenceOrder);
    bool aCarryEnabled = isEnabled(aChoices[1].mPreferenceOrder);
    bool aPermuteEnabled = isEnabled(aChoices[2].mPreferenceOrder);
    
    for (int aTry = 0; aTry < 2; aTry++) {
        if (aValueEnabled) {
            aResult.mValue = Random::Choice(aChoices[0].mPreferenceOrder);
        }
        if (aCarryEnabled) {
            aResult.mCarry = Random::Choice(aChoices[1].mPreferenceOrder);
        }
        if (aPermuteEnabled) {
            aResult.mPermute = Random::Choice(aChoices[2].mPreferenceOrder);
        }
        
        if (isUniqueIfEnabled(aResult.mValue, aValueEnabled, aResult.mCarry, aCarryEnabled) &&
            isUniqueIfEnabled(aResult.mValue, aValueEnabled, aResult.mPermute, aPermuteEnabled) &&
            isUniqueIfEnabled(aResult.mCarry, aCarryEnabled, aResult.mPermute, aPermuteEnabled)) {
            return aResult;
        }
    }
    
    std::set<LoopSaltBehavior> aUsed;
    auto pick = [&](const std::vector<LoopSaltBehavior>& pBehaviorList) {
        for (auto aBehavior : pBehaviorList) {
            if (!aUsed.contains(aBehavior)) {
                aUsed.insert(aBehavior);
                return aBehavior;
            }
        }
        return LoopSaltBehavior::kInv;
    };
    
    aResult.mValue = pick(aChoices[0].mPreferenceOrder);
    aResult.mCarry = pick(aChoices[1].mPreferenceOrder);
    aResult.mPermute = pick(aChoices[2].mPreferenceOrder);
    
    return aResult;
}

void SetWorkLaneError(std::string *pError,
                      const std::string &pMessage) {
    if (pError != nullptr) {
        *pError = pMessage;
    }
}

bool AppendLoopStatement(GLoop *pLoop,
                         GScopeState *pScopeState,
                         const GStatement &pStatement,
                         std::string *pError) {
    if ((pLoop == nullptr) || (pScopeState == nullptr)) {
        SetWorkLaneError(pError, "Internal error: loop append target was null.");
        return false;
    }
    if (pStatement.IsInvalid()) {
        SetWorkLaneError(pError, "Internal error: attempted to append an invalid statement.");
        return false;
    }

    GStatement aStatement = pStatement;
    pLoop->AddBody(aStatement);
    pScopeState->Consume(aStatement);
    return true;
}

bool EmitAssign(GLoop *pLoop,
                GScopeState *pScopeState,
                const GTarget &pTarget,
                const GExpr &pExpression,
                std::string *pError) {
    return AppendLoopStatement(pLoop,
                               pScopeState,
                               GStatement::Assign(pTarget, pExpression),
                               pError);
}

bool EmitXorAssign(GLoop *pLoop,
                   GScopeState *pScopeState,
                   const GTarget &pTarget,
                   const GExpr &pExpression,
                   std::string *pError) {
    return AppendLoopStatement(pLoop,
                               pScopeState,
                               GStatement::XorAssign(pTarget, pExpression),
                               pError);
}

bool EmitRecipeAssign(GLoop *pLoop,
                      GScopeState *pScopeState,
                      GStatementRecipe *pRecipe,
                      GSymbol pTarget,
                      std::string &pError) {
    if (pRecipe == nullptr) {
        pError = "Internal error: recipe assign target was null.";
        return false;
    }

    GStatement aStatement;
    if (!pRecipe->Bake(pTarget, aStatement, pError)) {
        return false;
    }
    return AppendLoopStatement(pLoop, pScopeState, aStatement, &pError);
}

bool EmitRecipeMix(GLoop *pLoop,
                   GScopeState *pScopeState,
                   GStatementRecipe *pRecipe,
                   GSymbol pTarget,
                   std::string &pError) {
    if (pRecipe == nullptr) {
        pError = "Internal error: recipe mix target was null.";
        return false;
    }

    GStatement aStatement;
    if (!pRecipe->BakeMix(pTarget, aStatement, pError)) {
        return false;
    }
    return AppendLoopStatement(pLoop, pScopeState, aStatement, &pError);
}

GExpr SaltReadExpr(GSymbol pSalt,
                   LoopSaltBehavior pBehavior,
                   GSymbol pLoopIndex,
                   GSymbol pSourceByteA,
                   bool pSecondSourceEnabled,
                   GSymbol pSourceByteB,
                   GSymbol pValue,
                   GSymbol pCarry,
                   GSymbol pOracle,
                   int pOffset) {
    switch (pBehavior) {
        case LoopSaltBehavior::kSourceA:
            return GQuick::BufferRead(pSalt, pSourceByteA);
            
        case LoopSaltBehavior::kSourceB:
            if (pSecondSourceEnabled) {
                return GQuick::BufferRead(pSalt, pSourceByteB);
            }
            return GExpr::ReadSaltWrap(pSalt, pLoopIndex, pOracle, pOffset);
        case LoopSaltBehavior::kValue:
            return GQuick::BufferRead(pSalt, pValue);
        case LoopSaltBehavior::kCarry:
            return GQuick::BufferRead(pSalt, pCarry);
        case LoopSaltBehavior::kLoopIndex:
        case LoopSaltBehavior::kInv:
        default:
            return GExpr::ReadSaltWrap(pSalt, pLoopIndex, pOracle, pOffset);
    }
}

} // namespace


GSeedStepARecipeWorkSpace::GSeedStepARecipeWorkSpace() {
    
}

bool GSeedStepARecipeWorkSpace::Plan(bool pSecondPass, std::string &pErrorString) {
    
    const std::string aCategryIdentifierSalt = "t";
    const std::string aCategryIdentifierSBox = "s";
    
    GScopeRules aScopeRules;
    
    GPool aGlobalPool(&aScopeRules);
    
    GScopeState aStateGlobal;
    GScopeState aStateLocal[SEED_WORK_LANE_COUNT];
    
    std::vector<GPool> mLoopPools;
    mLoopPools.reserve(SEED_WORK_LANE_COUNT);
    for (int i = 0; i < SEED_WORK_LANE_COUNT; i++) {
        mLoopPools.emplace_back(&aScopeRules);
    }
    
    aStateGlobal.Clear();
    for (int i=0;i<SEED_WORK_LANE_COUNT;i++) {
        aStateLocal[i].Clear();
    }
    
    mSource = BufSymbol(TwistWorkSpaceSlot::kSource);
    
    GSymbol aDests[SEED_WORK_LANE_COUNT];
    GSymbol aSalts[SEED_WORK_LANE_COUNT];
    GSymbol aSBoxes[SEED_WORK_LANE_COUNT];
    
    aSalts[0] = BufSymbol(TwistWorkSpaceSlot::kSaltA);
    aSalts[1] = BufSymbol(TwistWorkSpaceSlot::kSaltB);
    aSalts[2] = BufSymbol(TwistWorkSpaceSlot::kSaltC);
    aSalts[3] = BufSymbol(TwistWorkSpaceSlot::kSaltD);
    
    aDests[0] = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
    aDests[1] = BufSymbol(TwistWorkSpaceSlot::kWorkLaneB);
    aDests[2] = BufSymbol(TwistWorkSpaceSlot::kWorkLaneC);
    aDests[3] = BufSymbol(TwistWorkSpaceSlot::kWorkLaneD);
    
    aSBoxes[0] = BufSymbol(TwistWorkSpaceSlot::kSBoxA);
    aSBoxes[1] = BufSymbol(TwistWorkSpaceSlot::kSBoxB);
    aSBoxes[2] = BufSymbol(TwistWorkSpaceSlot::kSBoxC);
    aSBoxes[3] = BufSymbol(TwistWorkSpaceSlot::kSBoxD);
    
    //Random::Shuffle(aDests, SEED_WORK_LANE_COUNT);
    //Random::Shuffle(aSalts, SEED_WORK_LANE_COUNT);
    //Random::Shuffle(aSBoxes, SEED_WORK_LANE_COUNT);
    
    
    mWorkerA = aDests[0];
    mWorkerB = aDests[1];
    mWorkerC = aDests[2];
    mWorkerD = aDests[3];
    
    mSaltA = aSalts[0];
    mSaltB = aSalts[1];
    mSaltC = aSalts[2];
    mSaltD = aSalts[3];
    
    mSBoxA = aSBoxes[0];
    mSBoxB = aSBoxes[1];
    mSBoxC = aSBoxes[2];
    mSBoxD = aSBoxes[3];
    
    
    mLoopIndex = VarSymbol("aLoopIndex");
    mValue = VarSymbol("aValue");
    mPermute = VarSymbol("aPermute");
    mCarry = VarSymbol("aCarry");
    
    
    for (int i=0;i<SEED_WORK_LANE_COUNT;i++) {
        aScopeRules.SetReadPreferredMaximum(aSBoxes[i], 3);
        aScopeRules.SetReadPreferredMaximum(aSalts[i], 3);
    }

    
    if (pSecondPass == false) {

        // Pass1:
        //
        // SBoxes:
        // L1: must A, not D  → {A,B,C}
        // L2: must B, not A  → {B,C,D}
        // L3: must C, not B  → {C,D,A}
        // L4: must D, not C  → {D,A,B}
        mLoopPools[0].Add(mSBoxA, aCategryIdentifierSBox, 0, 2);
        mLoopPools[0].Add(mSBoxB, aCategryIdentifierSBox, 0, 2);
        mLoopPools[0].Add(mSBoxC, aCategryIdentifierSBox, 0, 2);
        
        mLoopPools[1].Add(mSBoxB, aCategryIdentifierSBox, 0, 2);
        mLoopPools[1].Add(mSBoxC, aCategryIdentifierSBox, 0, 2);
        mLoopPools[1].Add(mSBoxD, aCategryIdentifierSBox, 0, 2);
        
        mLoopPools[2].Add(mSBoxC, aCategryIdentifierSBox, 0, 2);
        mLoopPools[2].Add(mSBoxD, aCategryIdentifierSBox, 0, 2);
        mLoopPools[2].Add(mSBoxA, aCategryIdentifierSBox, 0, 2);
        
        mLoopPools[3].Add(mSBoxD, aCategryIdentifierSBox, 0, 2);
        mLoopPools[3].Add(mSBoxA, aCategryIdentifierSBox, 0, 2);
        mLoopPools[3].Add(mSBoxB, aCategryIdentifierSBox, 0, 2);
        
        // Salts:
        // L1: must C, not A  → {C,B,D}
        // L2: must D, not B  → {D,C,A}
        // L3: must A, not C  → {A,D,B}
        // L4: must B, not D  → {B,A,C}
        
        mLoopPools[0].Add(mSaltB, aCategryIdentifierSalt, 0, 2);
        mLoopPools[0].Add(mSaltC, aCategryIdentifierSalt, 0, 2);
        mLoopPools[0].Add(mSaltD, aCategryIdentifierSalt, 0, 2);
        
        mLoopPools[1].Add(mSaltC, aCategryIdentifierSalt, 0, 2);
        mLoopPools[1].Add(mSaltD, aCategryIdentifierSalt, 0, 2);
        mLoopPools[1].Add(mSaltA, aCategryIdentifierSalt, 0, 2);
        
        mLoopPools[2].Add(mSaltD, aCategryIdentifierSalt, 0, 2);
        mLoopPools[2].Add(mSaltA, aCategryIdentifierSalt, 0, 2);
        mLoopPools[2].Add(mSaltB, aCategryIdentifierSalt, 0, 2);
        
        mLoopPools[3].Add(mSaltA, aCategryIdentifierSalt, 0, 2);
        mLoopPools[3].Add(mSaltB, aCategryIdentifierSalt, 0, 2);
        mLoopPools[3].Add(mSaltC, aCategryIdentifierSalt, 0, 2);
        
    } else {
        
        // Pass2:
        //
        // SBoxes:
        // L1: must C, not A  → {C,B,D}
        // L2: must D, not B  → {D,C,A}
        // L3: must A, not C  → {A,D,B}
        // L4: must B, not D  → {B,A,C}
        mLoopPools[0].Add(mSBoxC, aCategryIdentifierSBox, 0, 2);
        mLoopPools[0].Add(mSBoxB, aCategryIdentifierSBox, 0, 2);
        mLoopPools[0].Add(mSBoxD, aCategryIdentifierSBox, 0, 2);
        
        mLoopPools[1].Add(mSBoxD, aCategryIdentifierSBox, 0, 2);
        mLoopPools[1].Add(mSBoxC, aCategryIdentifierSBox, 0, 2);
        mLoopPools[1].Add(mSBoxA, aCategryIdentifierSBox, 0, 2);
        
        mLoopPools[2].Add(mSBoxA, aCategryIdentifierSBox, 0, 2);
        mLoopPools[2].Add(mSBoxD, aCategryIdentifierSBox, 0, 2);
        mLoopPools[2].Add(mSBoxB, aCategryIdentifierSBox, 0, 2);
        
        mLoopPools[3].Add(mSBoxB, aCategryIdentifierSBox, 0, 2);
        mLoopPools[3].Add(mSBoxA, aCategryIdentifierSBox, 0, 2);
        mLoopPools[3].Add(mSBoxC, aCategryIdentifierSBox, 0, 2);
        
        
        // Salts:
        // L1: must B, not C  → {B,A,D}
        // L2: must C, not D  → {C,A,B}
        // L3: must D, not B  → {D,C,A}
        // L4: must A, not C  → {A,B,D}
        mLoopPools[0].Add(mSaltB, aCategryIdentifierSalt, 0, 2);
        mLoopPools[0].Add(mSaltA, aCategryIdentifierSalt, 0, 2);
        mLoopPools[0].Add(mSaltD, aCategryIdentifierSalt, 0, 2);
        
        mLoopPools[1].Add(mSaltC, aCategryIdentifierSalt, 0, 2);
        mLoopPools[1].Add(mSaltA, aCategryIdentifierSalt, 0, 2);
        mLoopPools[1].Add(mSaltB, aCategryIdentifierSalt, 0, 2);
        
        mLoopPools[2].Add(mSaltD, aCategryIdentifierSalt, 0, 2);
        mLoopPools[2].Add(mSaltC, aCategryIdentifierSalt, 0, 2);
        mLoopPools[2].Add(mSaltA, aCategryIdentifierSalt, 0, 2);
        
        mLoopPools[3].Add(mSaltA, aCategryIdentifierSalt, 0, 2);
        mLoopPools[3].Add(mSaltB, aCategryIdentifierSalt, 0, 2);
        mLoopPools[3].Add(mSaltD, aCategryIdentifierSalt, 0, 2);
    }
    
    
    
    bool aUseCarry[SEED_WORK_LANE_COUNT];
    int aUseCarryCount = Random::Get(SEED_WORK_LANE_CARRY_MIN, SEED_WORK_LANE_CARRY_MAX);
    memset(aUseCarry, 0, sizeof(aUseCarry));
    std::vector<int> aCarryIndices = Random::RandomIndicesInRange(aUseCarryCount, SEED_WORK_LANE_COUNT);
    for (int i=0;i<aCarryIndices.size();i++) {
        aUseCarry[aCarryIndices[i]] = true;
    }

    bool aUsePermute[SEED_WORK_LANE_COUNT];
    int aUsePermuteCount = Random::Get(SEED_WORK_LANE_PERMUTE_MIN, SEED_WORK_LANE_PERMUTE_MAX);
    memset(aUsePermute, 0, sizeof(aUsePermute));
    std::vector<int> aPermuteIndices = Random::RandomIndicesInRange(aUsePermuteCount, SEED_WORK_LANE_COUNT);
    for (int i=0;i<aPermuteIndices.size();i++) {
        aUsePermute[aPermuteIndices[i]] = true;
    }
    
    // Always use permute or carry.
    for (int i=0;i<SEED_WORK_LANE_COUNT;i++) {
        if ((aUseCarry[i] == false) && (aUsePermute[i] == false)) {
            int aPick = Random::Get(2);
            if (aPick == 0) {
                aUseCarry[i] = true;
            } else {
                aUsePermute[i] = true;
            }
        }
    }
    
    
    // Pick sources
    for (int aWhich=0; aWhich<SEED_WORK_LANE_COUNT; aWhich++) {
        
        // Pass1:
        // (       src ) => w_a
        // (src? + w_a ) => w_b
        // (w_a? + w_b ) => w_c
        // (w_b? + w_c ) => w_d

        // Pass2:
        // (w_c? + w_d ) => w_a
        // (w_d? + w_a ) => w_b
        // (w_a? + w_b ) => w_c
        // (w_b? + w_c ) => w_d
        
        mLoopContracts[aWhich].mSourceA.Invalidate();
        mLoopContracts[aWhich].mSourceB.Invalidate();
        
        bool aAllowSecondSource = true;
        bool aUseSecondSource = false;
        if (aWhich == 0) {
            if (pSecondPass) {
                aAllowSecondSource = true;
            } else {
                aAllowSecondSource = false;
            }
        }
        
        if (aAllowSecondSource) {
            aUseSecondSource = (Random::Get(3) != 1);
        }
        
        if (pSecondPass) {
            if (aWhich == 3) { mLoopContracts[aWhich].mSourceA = mWorkerC; }
            else if (aWhich == 2) { mLoopContracts[aWhich].mSourceA = mWorkerB; }
            else if (aWhich == 1) { mLoopContracts[aWhich].mSourceA = mWorkerA; }
            else  { mLoopContracts[aWhich].mSourceA = mWorkerD; }
            if ((aAllowSecondSource == true) && (aUseSecondSource == true)) {
                if (aWhich == 3) { mLoopContracts[aWhich].mSourceB = mWorkerB; }
                else if (aWhich == 2) { mLoopContracts[aWhich].mSourceB = mWorkerA; }
                else if (aWhich == 1) { mLoopContracts[aWhich].mSourceB = mWorkerD; }
                else  { mLoopContracts[aWhich].mSourceB = mWorkerC; }
            }
        } else {
            if (aWhich == 3) { mLoopContracts[aWhich].mSourceA = mWorkerC; }
            else if (aWhich == 2) { mLoopContracts[aWhich].mSourceA = mWorkerB; }
            else if (aWhich == 1) { mLoopContracts[aWhich].mSourceA = mWorkerA; }
            else  { mLoopContracts[aWhich].mSourceA = mSource; }
            if ((aAllowSecondSource == true) && (aUseSecondSource == true)) {
                if (aWhich == 3) { mLoopContracts[aWhich].mSourceB = mWorkerB; }
                else if (aWhich == 2) { mLoopContracts[aWhich].mSourceB = mWorkerA; }
                else if (aWhich == 1) { mLoopContracts[aWhich].mSourceB = mSource; }
            }
        }
        if (mLoopContracts[aWhich].mSourceB.IsInvalid()) {
            mLoopContracts[aWhich].mSecondSourceEnabled = false;
        } else {
            mLoopContracts[aWhich].mSecondSourceEnabled = true;
        }
        
        if (mLoopContracts[aWhich].mSourceB.IsInvalid() == false) {
            std::vector<LoopSecondSourceMode> aSecondSourceOptions = {
                LoopSecondSourceMode::kValue,
            };
            if (aUseCarry[aWhich] == true) {
                aSecondSourceOptions.push_back(LoopSecondSourceMode::kCarry);
            }
            if (aUsePermute[aWhich] == true) {
                aSecondSourceOptions.push_back(LoopSecondSourceMode::kPermute);
            }
            mLoopContracts[aWhich].mSecondSourceMode = Random::Choice(aSecondSourceOptions);
        } else {
            mLoopContracts[aWhich].mSecondSourceMode = LoopSecondSourceMode::kInv;
        }
    }
    
    // Pick loop order
    for (int aWhich=0; aWhich<SEED_WORK_LANE_COUNT; aWhich++) {
        int aPick = Random::Bool();
        if (aPick == true) {
            mLoopContracts[aWhich].mLoopOrder = SeedLoopOrder::kValueCarryPermute;
        } else {
            mLoopContracts[aWhich].mLoopOrder = SeedLoopOrder::kValuePermuteCarry;
        }
        
    }
    
    // Pick destinations
    for (int aWhich=0; aWhich<SEED_WORK_LANE_COUNT; aWhich++) {
        
        // Pass1 and Pass2:
        // w_a
        // w_b
        // w_c
        // w_d
        if (aWhich == 0) { mLoopContracts[aWhich].mDest = mWorkerA; }
        else if (aWhich == 1) { mLoopContracts[aWhich].mDest = mWorkerB; }
        else if (aWhich == 2) { mLoopContracts[aWhich].mDest = mWorkerC; }
        else  { mLoopContracts[aWhich].mDest = mWorkerD; }
    }
    
    for (int aWhich=0; aWhich<SEED_WORK_LANE_COUNT; aWhich++) {
        
        mLoopContracts[aWhich].mCarryEnabled = aUseCarry[aWhich];
        mLoopContracts[aWhich].mPermuteEnabled = aUsePermute[aWhich];
        
    }
    
    for (int aWhich=0; aWhich<SEED_WORK_LANE_COUNT; aWhich++) {
        mLoopContracts[aWhich].mCarrySBoxBehavior = LoopSBoxBehavior::kInv;
        mLoopContracts[aWhich].mPermuteSBoxBehavior = LoopSBoxBehavior::kInv;
        if (mLoopContracts[aWhich].mPermuteEnabled == true) {
            if (mLoopContracts[aWhich].mCarryEnabled == true) {
                int aChoice = Random::Get(2);
                if (aChoice == 1) {
                    mLoopContracts[aWhich].mCarrySBoxBehavior = LoopSBoxBehavior::kMixWithLoopIndex;
                } else {
                    mLoopContracts[aWhich].mPermuteSBoxBehavior = LoopSBoxBehavior::kMixWithLoopIndex;
                }
            } else {
                mLoopContracts[aWhich].mPermuteSBoxBehavior = LoopSBoxBehavior::kMixWithLoopIndex;
            }
        } else if (mLoopContracts[aWhich].mCarryEnabled == true) {
            mLoopContracts[aWhich].mCarrySBoxBehavior = LoopSBoxBehavior::kMixWithLoopIndex;
        }
    }
    
    for (int aWhich=0; aWhich<SEED_WORK_LANE_COUNT; aWhich++) {
        
        std::set<LoopSaltBehavior> aValueSaltBehaviors;
        if (true) {
            aValueSaltBehaviors.insert(LoopSaltBehavior::kLoopIndex);
            aValueSaltBehaviors.insert(LoopSaltBehavior::kSourceA);
            if (mLoopContracts[aWhich].mCarryEnabled == true) {
                aValueSaltBehaviors.insert(LoopSaltBehavior::kCarry);
            }
            if (mLoopContracts[aWhich].mSecondSourceEnabled == true) {
                aValueSaltBehaviors.insert(LoopSaltBehavior::kSourceB);
            }
        }
        
        std::set<LoopSaltBehavior> aCarrySaltBehaviors;
        if (mLoopContracts[aWhich].mCarryEnabled == true) {
            aCarrySaltBehaviors.insert(LoopSaltBehavior::kLoopIndex);
            aCarrySaltBehaviors.insert(LoopSaltBehavior::kValue);
            aCarrySaltBehaviors.insert(LoopSaltBehavior::kSourceA);
            if (mLoopContracts[aWhich].mSecondSourceEnabled == true) {
                aCarrySaltBehaviors.insert(LoopSaltBehavior::kSourceB);
            }
        }
        
        std::set<LoopSaltBehavior> aPermuteSaltBehaviors;
        if (mLoopContracts[aWhich].mPermuteEnabled == true) {
            aPermuteSaltBehaviors.insert(LoopSaltBehavior::kLoopIndex);
            aPermuteSaltBehaviors.insert(LoopSaltBehavior::kValue);
            aPermuteSaltBehaviors.insert(LoopSaltBehavior::kSourceA);
            if (mLoopContracts[aWhich].mCarryEnabled == true) {
                aPermuteSaltBehaviors.insert(LoopSaltBehavior::kCarry);
            }
            if (mLoopContracts[aWhich].mSecondSourceEnabled == true) {
                aPermuteSaltBehaviors.insert(LoopSaltBehavior::kSourceB);
            }
        }
        
        SaltBehaviorAssignment aSaltBehaviorAssignment = AssignLoopContractBehaviors(aValueSaltBehaviors,
                                                                                     aCarrySaltBehaviors,
                                                                                     aPermuteSaltBehaviors);
        
        mLoopContracts[aWhich].mValueSaltBehavior = aSaltBehaviorAssignment.mValue;
        mLoopContracts[aWhich].mCarrySaltBehavior = aSaltBehaviorAssignment.mCarry;
        mLoopContracts[aWhich].mPermuteSaltBehavior = aSaltBehaviorAssignment.mPermute;
        
    }
    
    for (int aWhich=0; aWhich<SEED_WORK_LANE_COUNT; aWhich++) {
        
        std::vector<SeedConsumeOrder> aConsumeOrderChoices = { SeedConsumeOrder::kBeforeSBox, SeedConsumeOrder::kAfterSBox };
        
        mLoopContracts[aWhich].mValueConsumeOrder_Carry = Random::Choice(aConsumeOrderChoices);
        mLoopContracts[aWhich].mValueConsumeOrder_SourceB = Random::Choice(aConsumeOrderChoices);
        mLoopContracts[aWhich].mValueConsumeOrder_Salt = Random::Choice(aConsumeOrderChoices);
        
        mLoopContracts[aWhich].mCarryConsumeOrder_Value = Random::Choice(aConsumeOrderChoices);
        mLoopContracts[aWhich].mCarryConsumeOrder_SourceB = Random::Choice(aConsumeOrderChoices);
        mLoopContracts[aWhich].mCarryConsumeOrder_Salt = Random::Choice(aConsumeOrderChoices);
        
        mLoopContracts[aWhich].mPermuteConsumeOrder_Carry = Random::Choice(aConsumeOrderChoices);
        mLoopContracts[aWhich].mPermuteConsumeOrder_Value = Random::Choice(aConsumeOrderChoices);
        mLoopContracts[aWhich].mPermuteConsumeOrder_Salt = Random::Choice(aConsumeOrderChoices);
        mLoopContracts[aWhich].mPermuteConsumeOrder_SourceB = Random::Choice(aConsumeOrderChoices);
        
        mLoopContracts[aWhich].mPermuteUseCarry = Random::Bool();
        
        
    }
    
    enum class SeedLoopOrder : std::uint8_t {
        kValueCarryPermute = 0,
        kValuePermuteCarry = 1,
    };
    
    for (int aWhich=0; aWhich<SEED_WORK_LANE_COUNT; aWhich++) {
        
        std::vector<GSymbol> aFetchedSalts;
        std::vector<GSymbol> aFetchedSBoxes;
        
        aStateLocal[aWhich].Clear();
        
        GSymbol aRequired;
        if (pSecondPass == false) {
            // Pass1:
            // Salts:
            // L1: must C, not A  → {C,B,D}
            // L2: must D, not B  → {D,C,A}
            // L3: must A, not C  → {A,D,B}
            // L4: must B, not D  → {B,A,C}
            if (aWhich == 1) { aRequired = mSaltD; }
            else if (aWhich == 2) { aRequired = mSaltA; }
            else if (aWhich == 3) { aRequired = mSaltB; }
            else { aRequired = mSaltC; }
        } else {
            // Pass2:
            // Salts:
            // L1: must B, not C  → {B,A,D}
            // L2: must C, not D  → {C,A,B}
            // L3: must D, not B  → {D,C,A}
            // L4: must A, not C  → {A,B,D}
            if (aWhich == 0) { aRequired = mSaltB; }
            else if (aWhich == 1) { aRequired = mSaltC; }
            else if (aWhich == 2) { aRequired = mSaltD; }
            else { aRequired = mSaltA; }
        }
        
        std::vector<GStatementSlot> aSlotListSalts;
        if (!mLoopPools[aWhich].FetchSlots(aCategryIdentifierSalt,
                                           3,
                                           aRequired,
                                           aSlotListSalts,
                                           aStateLocal[aWhich],
                                           aStateGlobal,
                                           pErrorString)) {
            return false;
        }
        
        for (int i=0; i<aSlotListSalts.size(); i++) {
            switch (aSlotListSalts[i].mType) {
                case GStatementSlotType::kInv:
                    pErrorString = "Plan: Invalid Slot Type, Expected Symbol (Salt)";
                    return false;
                case GStatementSlotType::kSymbol:
                    aFetchedSalts.push_back(aSlotListSalts[i].mSymbol);
                    break;
                case GStatementSlotType::kExpr:
                    pErrorString = "Plan: Invalid Slot Type, Expected Symbol (Salt)";
                    return false;
            }
        }
        
        if (aSlotListSalts.size() < 3) {
            pErrorString = "Plan: We needed to get 3 salts here. (Salt)";
            return false;
        }
        
        if (pSecondPass == false) {
            // Pass1:
            // SBoxes:
            // L1: must A, not D  → {A,B,C}
            // L2: must B, not A  → {B,C,D}
            // L3: must C, not B  → {C,D,A}
            // L4: must D, not C  → {D,A,B}
            if (aWhich == 1) { aRequired = mSBoxB; }
            else if (aWhich == 2) { aRequired = mSBoxC; }
            else if (aWhich == 3) { aRequired = mSBoxD; }
            else { aRequired = mSBoxA; }
        } else {
            // Pass2:
            // SBoxes:
            // L1: must C, not A  → {C,B,D}
            // L2: must D, not B  → {D,C,A}
            // L3: must A, not C  → {A,D,B}
            // L4: must B, not D  → {B,A,C}
            if (aWhich == 0) { aRequired = mSBoxC; }
            else if (aWhich == 1) { aRequired = mSBoxD; }
            else if (aWhich == 2) { aRequired = mSBoxA; }
            else { aRequired = mSBoxB; }
        }
        
        std::vector<GStatementSlot> aSlotListSBoxes;
        if (!mLoopPools[aWhich].FetchSlots(aCategryIdentifierSBox,
                                           3,
                                           aRequired,
                                           aSlotListSBoxes,
                                           aStateLocal[aWhich],
                                           aStateGlobal,
                                           pErrorString)) {
            return false;
        }
        
        for (int i=0; i<aSlotListSBoxes.size(); i++) {
            switch (aSlotListSBoxes[i].mType) {
                    
                case GStatementSlotType::kInv:
                    pErrorString = "Plan: Invalid Slot Type, Expected Symbol (S-Box)";
                    return false;
                case GStatementSlotType::kSymbol:
                    aFetchedSBoxes.push_back(aSlotListSBoxes[i].mSymbol);
                    break;
                case GStatementSlotType::kExpr:
                    pErrorString = "Plan: Invalid Slot Type, Expected Symbol (S-Box)";
                    return false;
            }
        }
        
        if (aSlotListSBoxes.size() < 3) {
            pErrorString = "Plan: We needed to get 3 s-boxes here. (S-Box)";
            return false;
        }
        
        
        mLoopContracts[aWhich].mValueSalt = aFetchedSalts[0];
        mLoopContracts[aWhich].mValueSBox = aFetchedSBoxes[0];
        aStateLocal[aWhich].Consume(aFetchedSalts[0]);
        aStateLocal[aWhich].Consume(aFetchedSBoxes[0]);
        
        if (mLoopContracts[aWhich].mCarryEnabled) {
            mLoopContracts[aWhich].mCarrySalt = aFetchedSalts[1];
            mLoopContracts[aWhich].mCarrySBox = aFetchedSBoxes[1];
            aStateLocal[aWhich].Consume(aFetchedSalts[1]);
            aStateLocal[aWhich].Consume(aFetchedSBoxes[1]);
        }
        
        if (mLoopContracts[aWhich].mPermuteEnabled) {
            mLoopContracts[aWhich].mPermuteSalt = aFetchedSalts[2];
            mLoopContracts[aWhich].mPermuteSBox = aFetchedSBoxes[2];
            aStateLocal[aWhich].Consume(aFetchedSalts[2]);
            aStateLocal[aWhich].Consume(aFetchedSBoxes[2]);
        }
        
        aStateGlobal.Consume(aStateLocal[aWhich]);
        
    }
    
    return true;
}


bool GSeedStepARecipeWorkSpace::Bake(std::vector<GLoop> &pResult, std::string &pErrorString) {
    
    pResult.clear();

    for (int aWhich = 0; aWhich < SEED_WORK_LANE_COUNT; ++aWhich) {
        GLoop aLoop;
        aLoop.mLoopVariable = mLoopIndex;
        aLoop.mLoopVariableName = "aLoopIndex";
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 1;

        GScopeState aStateLocal;
        aStateLocal.Clear();
        
        GStatementRecipe aRecipe;
        
        GLoopFragmentComposer aComposerValue(mLoopIndex);
        GLoopFragmentComposer aComposerCarry(mLoopIndex);
        GLoopFragmentComposer aComposerPermute(mLoopIndex);
        
        
        
        const GSeedStepARecipeLoopContract &aContract = mLoopContracts[aWhich];
        
        
        aComposerValue.ResetSetEqual(mValue);
        
        // source a
        aComposerValue.MixBuffer(aContract.mSourceA).Offset().Expand(50, true);
        
        // source b before
        if (aContract.mSecondSourceEnabled == true) {
            if (aContract.mSecondSourceMode == LoopSecondSourceMode::kValue) {
                if (aContract.mValueConsumeOrder_SourceB == SeedConsumeOrder::kBeforeSBox) {
                    aComposerValue.MixBuffer(aContract.mSourceB).Offset().Expand(50, true);
                }
            }
        }
        
        // carry before
        if (aContract.mCarryEnabled) {
            if (aContract.mValueConsumeOrder_Carry == SeedConsumeOrder::kBeforeSBox) {
                aComposerValue.MixVariable(mCarry).Expand(50, true);
            }
        }
        
        // salt before
        if (aContract.mValueConsumeOrder_Salt == SeedConsumeOrder::kBeforeSBox) {
            switch (aContract.mValueSaltBehavior) {
                case LoopSaltBehavior::kSourceA:
                    aComposerValue.MixBuffer(aContract.mValueSalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceA, mLoopIndex);
                    break;
                case LoopSaltBehavior::kSourceB:
                    aComposerValue.MixBuffer(aContract.mValueSalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceB, mLoopIndex);
                    break;
                case LoopSaltBehavior::kCarry:
                    aComposerValue.MixBuffer(aContract.mValueSalt).Offset().Key(mCarry);
                    break;
                default:
                    aComposerValue.MixBuffer(aContract.mValueSalt).Offset().Key(mLoopIndex);
            }
        }
        
        aComposerValue.Transform(aContract.mValueSBox);
        
        // source b after
        if (aContract.mSecondSourceEnabled == true) {
            if (aContract.mSecondSourceMode == LoopSecondSourceMode::kValue) {
                if (aContract.mValueConsumeOrder_SourceB == SeedConsumeOrder::kAfterSBox) {
                    aComposerValue.MixBuffer(aContract.mSourceB).Offset().Expand(50, true);
                }
            }
        }
        
        // carry after
        if (aContract.mCarryEnabled) {
            if (aContract.mValueConsumeOrder_Carry == SeedConsumeOrder::kAfterSBox) {
                aComposerValue.MixVariable(mCarry).Expand(50, true);
            }
        }
        
        // salt after
        if (aContract.mValueConsumeOrder_Salt == SeedConsumeOrder::kAfterSBox) {
            switch (aContract.mValueSaltBehavior) {
                case LoopSaltBehavior::kSourceA:
                    aComposerValue.MixBuffer(aContract.mValueSalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceA, mLoopIndex);
                    break;
                case LoopSaltBehavior::kSourceB:
                    aComposerValue.MixBuffer(aContract.mValueSalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceB, mLoopIndex);
                    break;
                case LoopSaltBehavior::kCarry:
                    aComposerValue.MixBuffer(aContract.mValueSalt).Offset().Key(mCarry);
                    break;
                default:
                    aComposerValue.MixBuffer(aContract.mValueSalt).Offset().Key(mLoopIndex);
            }
        }
        
        
        if (!aComposerValue.BakeStatements(&aLoop.mBodyStatements, &pErrorString)) {
            printf("errored on aComposerValue.BakeStatements\\()\n");
            return false;
        }
        
        
        auto BuildCarry = [&]() -> bool {
            if (aContract.mCarryEnabled == false) {
                return true;
            }
            
            if (Random::Bool()) {
                aComposerCarry.ResetAddEqual(mCarry);
            } else {
                aComposerCarry.ResetXorEqual(mCarry);
            }
            
            
            // value before
            if (aContract.mCarryConsumeOrder_Value == SeedConsumeOrder::kBeforeSBox) {
                aComposerCarry.MixVariable(mValue).Expand(50, true);
            }
            
            // source b before
            if (aContract.mSecondSourceEnabled == true) {
                if (aContract.mSecondSourceMode == LoopSecondSourceMode::kCarry) {
                    if (aContract.mCarryConsumeOrder_SourceB == SeedConsumeOrder::kBeforeSBox) {
                        aComposerCarry.MixBuffer(aContract.mSourceB).Offset().Expand(50, true);
                    }
                }
            }
            
            // salt before
            if (aContract.mCarryConsumeOrder_Salt == SeedConsumeOrder::kBeforeSBox) {
                switch (aContract.mCarrySaltBehavior) {
                    case LoopSaltBehavior::kValue:
                        aComposerCarry.MixBuffer(aContract.mCarrySalt).Offset().Key(mValue);
                        break;
                    case LoopSaltBehavior::kSourceA:
                        aComposerCarry.MixBuffer(aContract.mCarrySalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceA, mLoopIndex);
                        break;
                    case LoopSaltBehavior::kSourceB:
                        aComposerCarry.MixBuffer(aContract.mCarrySalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceB, mLoopIndex);
                        break;
                    default:
                        aComposerCarry.MixBuffer(aContract.mCarrySalt).Offset().Key(mLoopIndex);
                }
            }
            
            switch (aContract.mCarrySBoxBehavior) {
                case LoopSBoxBehavior::kMixWithLoopIndex:
                    aComposerCarry.MixBuffer(aContract.mCarrySBox).Key(mLoopIndex);
                    break;
                case LoopSBoxBehavior::kPassSelfThrough:
                    aComposerCarry.Transform(aContract.mCarrySBox);
                    break;
                default:
                    break;
            }
            
            // value after
            if (aContract.mCarryConsumeOrder_Value == SeedConsumeOrder::kAfterSBox) {
                aComposerCarry.MixVariable(mValue).Expand(50, true);
            }
            
            // source b after
            if (aContract.mSecondSourceEnabled == true) {
                if (aContract.mSecondSourceMode == LoopSecondSourceMode::kCarry) {
                    if (aContract.mCarryConsumeOrder_SourceB == SeedConsumeOrder::kAfterSBox) {
                        aComposerCarry.MixBuffer(aContract.mSourceB).Offset().Expand(50, true);
                    }
                }
            }
            
            // salt after
            if (aContract.mCarryConsumeOrder_Salt == SeedConsumeOrder::kAfterSBox) {
                switch (aContract.mCarrySaltBehavior) {
                    case LoopSaltBehavior::kValue:
                        aComposerCarry.MixBuffer(aContract.mCarrySalt).Offset().Key(mValue);
                        break;
                    case LoopSaltBehavior::kSourceA:
                        aComposerCarry.MixBuffer(aContract.mCarrySalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceA, mLoopIndex);
                        break;
                    case LoopSaltBehavior::kSourceB:
                        aComposerCarry.MixBuffer(aContract.mCarrySalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceB, mLoopIndex);
                        break;
                    default:
                        aComposerCarry.MixBuffer(aContract.mCarrySalt).Offset().Key(mLoopIndex);
                }
            }
            
            if (!aComposerCarry.BakeStatements(&aLoop.mBodyStatements, &pErrorString)) {
                printf("errored on aComposerCarry.BakeStatements()\n");
                return false;
            }
            
            return true;
        };
        
        auto BuildPermute = [&]() -> bool {
            if (aContract.mPermuteEnabled == false) {
                return true;
            }
            
            aComposerPermute.ResetAddEqual(mPermute);
            
            // value before
            if (aContract.mPermuteConsumeOrder_Value == SeedConsumeOrder::kBeforeSBox) {
                aComposerPermute.MixVariable(mValue).Expand(50, true);
            }
            
            // carry before
            if (aContract.mCarryEnabled) {
                if (aContract.mPermuteUseCarry == true) {
                    if (aContract.mPermuteConsumeOrder_Carry == SeedConsumeOrder::kBeforeSBox) {
                        aComposerPermute.MixVariable(mCarry).Expand(50, true);
                    }
                }
            }
            
            // source b before
            if (aContract.mSecondSourceEnabled == true) {
                if (aContract.mSecondSourceMode == LoopSecondSourceMode::kPermute) {
                    if (aContract.mPermuteConsumeOrder_SourceB == SeedConsumeOrder::kBeforeSBox) {
                        aComposerPermute.MixBuffer(aContract.mSourceB).Offset().Expand(50, true);
                    }
                }
            }
            
            // salt before
            if (aContract.mPermuteConsumeOrder_Salt == SeedConsumeOrder::kBeforeSBox) {
                switch (aContract.mPermuteSaltBehavior) {
                    case LoopSaltBehavior::kValue:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().Key(mValue);
                        break;
                    case LoopSaltBehavior::kCarry:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().Key(mCarry);
                        break;
                    case LoopSaltBehavior::kSourceA:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceA, mLoopIndex);
                        break;
                    case LoopSaltBehavior::kSourceB:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceB, mLoopIndex);
                        break;
                    default:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().Key(mLoopIndex);
                }
            }
            
            switch (aContract.mPermuteSBoxBehavior) {
                case LoopSBoxBehavior::kMixWithLoopIndex:
                    aComposerPermute.MixBuffer(aContract.mPermuteSBox).Key(mLoopIndex);
                    break;
                case LoopSBoxBehavior::kPassSelfThrough:
                    aComposerPermute.Transform(aContract.mPermuteSBox);
                    break;
                default:
                    break;
            }
            
            // value after
            if (aContract.mPermuteConsumeOrder_Value == SeedConsumeOrder::kAfterSBox) {
                aComposerPermute.MixVariable(mValue).Expand(50, true);
            }
            
            // carry after
            if (aContract.mCarryEnabled) {
                if (aContract.mPermuteUseCarry == true) {
                    if (aContract.mPermuteConsumeOrder_Carry == SeedConsumeOrder::kAfterSBox) {
                        aComposerPermute.MixVariable(mCarry).Expand(50, true);
                    }
                }
            }
            
            // source b after
            if (aContract.mSecondSourceEnabled == true) {
                if (aContract.mSecondSourceMode == LoopSecondSourceMode::kPermute) {
                    if (aContract.mPermuteConsumeOrder_SourceB == SeedConsumeOrder::kAfterSBox) {
                        aComposerPermute.MixBuffer(aContract.mSourceB).Offset().Expand(50, true);
                    }
                }
            }
            
            // salt after
            if (aContract.mPermuteConsumeOrder_Salt == SeedConsumeOrder::kAfterSBox) {
                switch (aContract.mPermuteSaltBehavior) {
                    case LoopSaltBehavior::kValue:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().Key(mValue);
                        break;
                    case LoopSaltBehavior::kCarry:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().Key(mCarry);
                        break;
                    case LoopSaltBehavior::kSourceA:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceA, mLoopIndex);
                        break;
                    case LoopSaltBehavior::kSourceB:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().KeyWithBufferRandomOffset(aContract.mSourceB, mLoopIndex);
                        break;
                    default:
                        aComposerPermute.MixBuffer(aContract.mPermuteSalt).Offset().Key(mLoopIndex);
                }
            }
            
            if (!aComposerPermute.BakeStatements(&aLoop.mBodyStatements, &pErrorString)) {
                printf("errored on aComposerPermute.BakeStatements()\n");
                return false;
            }
            
            GTarget aValueTarget = GTarget::Symbol(mValue);
            GExpr aValueExpr = GExpr::Symbol(mValue);
            GExpr aPermuteExpr = GExpr::Symbol(mPermute);
            GStatement aPermuteValueStatement = GStatement::Assign(aValueTarget, GExpr::RotL8(aValueExpr, aPermuteExpr));
            aLoop.mBodyStatements.push_back(aPermuteValueStatement);
            
            return true;
        };
        
        switch (aContract.mLoopOrder) {
            case SeedLoopOrder::kValueCarryPermute:
                if (!BuildCarry()) {
                    printf("errored on BuildCarry()\n");
                    return false;
                }
                if (!BuildPermute()) {
                    printf("errored on BuildPermute()\n");
                    return false;
                }
                break;
            default:
                if (!BuildPermute()) {
                    printf("errored on BuildPermute()\n");
                    return false;
                }
                if (!BuildCarry()) {
                    printf("errored on BuildCarry()\n");
                    return false;
                }
                break;
        }
        
        GExpr aLoopIndexExpr = GExpr::Symbol(mLoopIndex);
        GTarget aDestTarget = GTarget::Write(aContract.mDest, aLoopIndexExpr);
        GExpr aValueExpr = GExpr::Symbol(mValue);
        GStatement aDestAssignStatement = GStatement::Assign(aDestTarget, aValueExpr);
        aLoop.mBodyStatements.push_back(aDestAssignStatement);
        
        pResult.push_back(aLoop);
    }

    return true;
    
}
