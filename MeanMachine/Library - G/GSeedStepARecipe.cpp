//
//  GSeedStepARecipe.cpp
//  MeanMachine
//
//  Created by Magneto on 4/27/26.
//

#include "GSeedStepARecipe.hpp"
#include "GLoopFragmentComposer.hpp"
#include <algorithm>
#include <array>
#include <functional>
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

} // namespace


GSeedStepARecipeWorkSpace::GSeedStepARecipeWorkSpace() {
    mSecondPass = false;
}

bool GSeedStepARecipeWorkSpace::Plan(bool pSecondPass, std::string &pErrorString) {
    
    mSecondPass = pSecondPass;
    
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
    
    
    mValueNibbleA = VarSymbol("aValueNibbleA");
    mValueNibbleB = VarSymbol("aValueNibbleB");
    mValueNibbleC = VarSymbol("aValueNibbleC");
    mValueNibbleD = VarSymbol("aValueNibbleD");
    
    
    for (int i=0;i<SEED_WORK_LANE_COUNT;i++) {
        aScopeRules.SetReadPreferredMaximum(aSBoxes[i], 3);
        aScopeRules.SetReadPreferredMaximum(aSalts[i], 3);
    }
    
    
    for (int i=0;i<SEED_WORK_LANE_COUNT;i++) {
        mLoopContracts[i].mValueTransformPlusA = Random::Bool();
        mLoopContracts[i].mValueTransformPlusB = Random::Bool();
        mLoopContracts[i].mValueTransformPlusC = Random::Bool();
        mLoopContracts[i].mValueTransformPlusD = Random::Bool();
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
    
    
    
    //GSymbol                                 mValueTransformSBoxA;
    //GSymbol                                 mValueTransformSBoxB;
    //GSymbol                                 mValueTransformSBoxC;
    //GSymbol                                 mValueTransformSBoxD;
    
    for (int aWhich=0; aWhich<SEED_WORK_LANE_COUNT; aWhich++) {
        
        std::vector<GSymbol> aBoxList;
        aBoxList.push_back(mSBoxA);
        aBoxList.push_back(mSBoxB);
        aBoxList.push_back(mSBoxC);
        aBoxList.push_back(mSBoxD);
        Random::Shuffle(&aBoxList);
        
        mLoopContracts[aWhich].mValueTransformSBoxA = aBoxList[0];
        mLoopContracts[aWhich].mValueTransformSBoxB = aBoxList[1];
        mLoopContracts[aWhich].mValueTransformSBoxC = aBoxList[2];
        mLoopContracts[aWhich].mValueTransformSBoxD = aBoxList[3];
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
        mLoopContracts[aWhich].mValueConsumeOrder_SourceA = Random::Choice(aConsumeOrderChoices);
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
        
        aStateLocal[aWhich].Clear();
        
        bool aPlannedLane = false;
        std::string aLaneErrorString = "Plan: lane planner did not produce a result.";
        
        for (int aLaneTry=0; ((aLaneTry<128) && (aPlannedLane == false)); aLaneTry++) {
            
            std::vector<GSymbol> aFetchedSalts;
            std::vector<GSymbol> aFetchedSBoxes;
            GScopeState aLocalLaneState;
            aLocalLaneState.Clear();
            
            GSymbol aRequiredSalt;
            if (pSecondPass == false) {
                // Pass1:
                // Salts:
                // L1: must C, not A  → {C,B,D}
                // L2: must D, not B  → {D,C,A}
                // L3: must A, not C  → {A,D,B}
                // L4: must B, not D  → {B,A,C}
                if (aWhich == 1) { aRequiredSalt = mSaltD; }
                else if (aWhich == 2) { aRequiredSalt = mSaltA; }
                else if (aWhich == 3) { aRequiredSalt = mSaltB; }
                else { aRequiredSalt = mSaltC; }
            } else {
                // Pass2:
                // Salts:
                // L1: must B, not C  → {B,A,D}
                // L2: must C, not D  → {C,A,B}
                // L3: must D, not B  → {D,C,A}
                // L4: must A, not C  → {A,B,D}
                if (aWhich == 0) { aRequiredSalt = mSaltB; }
                else if (aWhich == 1) { aRequiredSalt = mSaltC; }
                else if (aWhich == 2) { aRequiredSalt = mSaltD; }
                else { aRequiredSalt = mSaltA; }
            }
            
            std::vector<GStatementSlot> aSlotListSalts;
            if (!mLoopPools[aWhich].FetchSlots(aCategryIdentifierSalt,
                                               3,
                                               aRequiredSalt,
                                               aSlotListSalts,
                                               aLocalLaneState,
                                               aStateGlobal,
                                               aLaneErrorString)) {
                continue;
            }
            
            bool aLaneValid = true;
            for (int i=0; i<aSlotListSalts.size(); i++) {
                switch (aSlotListSalts[i].mType) {
                    case GStatementSlotType::kInv:
                    case GStatementSlotType::kExpr:
                        aLaneErrorString = "Plan: Invalid Slot Type, Expected Symbol (Salt)";
                        aLaneValid = false;
                        break;
                    case GStatementSlotType::kSymbol:
                        aFetchedSalts.push_back(aSlotListSalts[i].mSymbol);
                        break;
                }
                if (aLaneValid == false) {
                    break;
                }
            }
            if (aLaneValid == false) {
                continue;
            }
            if (aSlotListSalts.size() < 3) {
                aLaneErrorString = "Plan: We needed to get 3 salts here. (Salt)";
                continue;
            }
            
            GSymbol aRequiredSBox;
            if (pSecondPass == false) {
                // Pass1:
                // SBoxes:
                // L1: must A, not D  → {A,B,C}
                // L2: must B, not A  → {B,C,D}
                // L3: must C, not B  → {C,D,A}
                // L4: must D, not C  → {D,A,B}
                if (aWhich == 1) { aRequiredSBox = mSBoxB; }
                else if (aWhich == 2) { aRequiredSBox = mSBoxC; }
                else if (aWhich == 3) { aRequiredSBox = mSBoxD; }
                else { aRequiredSBox = mSBoxA; }
            } else {
                // Pass2:
                // SBoxes:
                // L1: must C, not A  → {C,B,D}
                // L2: must D, not B  → {D,C,A}
                // L3: must A, not C  → {A,D,B}
                // L4: must B, not D  → {B,A,C}
                if (aWhich == 0) { aRequiredSBox = mSBoxC; }
                else if (aWhich == 1) { aRequiredSBox = mSBoxD; }
                else if (aWhich == 2) { aRequiredSBox = mSBoxA; }
                else { aRequiredSBox = mSBoxB; }
            }
            
            std::vector<GStatementSlot> aSlotListSBoxes;
            if (!mLoopPools[aWhich].FetchSlots(aCategryIdentifierSBox,
                                               3,
                                               aRequiredSBox,
                                               aSlotListSBoxes,
                                               aLocalLaneState,
                                               aStateGlobal,
                                               aLaneErrorString)) {
                continue;
            }
            
            for (int i=0; i<aSlotListSBoxes.size(); i++) {
                switch (aSlotListSBoxes[i].mType) {
                    case GStatementSlotType::kInv:
                    case GStatementSlotType::kExpr:
                        aLaneErrorString = "Plan: Invalid Slot Type, Expected Symbol (S-Box)";
                        aLaneValid = false;
                        break;
                    case GStatementSlotType::kSymbol:
                        aFetchedSBoxes.push_back(aSlotListSBoxes[i].mSymbol);
                        break;
                }
                if (aLaneValid == false) {
                    break;
                }
            }
            if (aLaneValid == false) {
                continue;
            }
            if (aSlotListSBoxes.size() < 3) {
                aLaneErrorString = "Plan: We needed to get 3 s-boxes here. (S-Box)";
                continue;
            }
            
            mLoopContracts[aWhich].mValueSalt = aFetchedSalts[0];
            aLocalLaneState.Consume(aFetchedSalts[0]);
            
            if (mLoopContracts[aWhich].mCarryEnabled) {
                mLoopContracts[aWhich].mCarrySalt = aFetchedSalts[1];
                mLoopContracts[aWhich].mCarrySBox = aFetchedSBoxes[0];
                aLocalLaneState.Consume(aFetchedSalts[1]);
                aLocalLaneState.Consume(aFetchedSBoxes[0]);
            }
            
            if (mLoopContracts[aWhich].mPermuteEnabled) {
                mLoopContracts[aWhich].mPermuteSalt = aFetchedSalts[2];
                mLoopContracts[aWhich].mPermuteSBoxA = aFetchedSBoxes[1];
                mLoopContracts[aWhich].mPermuteSBoxB = aFetchedSBoxes[2];
                aLocalLaneState.Consume(aFetchedSalts[2]);
                aLocalLaneState.Consume(aFetchedSBoxes[1]);
                aLocalLaneState.Consume(aFetchedSBoxes[2]);
            }
            
            aStateLocal[aWhich] = aLocalLaneState;
            aStateGlobal.Consume(aStateLocal[aWhich]);
            aPlannedLane = true;
        }
        
        if (aPlannedLane == false) {
            pErrorString = "Plan: failed to assign lane " + std::to_string(aWhich) + " after 128 attempts. Last error: " + aLaneErrorString;
            return false;
        }
    }
    
    if (pSecondPass == false) {
        int aPasswordReadCount = Random::Get(2);
        if (aPasswordReadCount != 0) {
            int aWhich = Random::Get(2, 3);
            mLoopContracts[aWhich].mSourceB = mSource;
            mLoopContracts[aWhich].mSecondSourceEnabled = true;
        }
    } else {
        int aPasswordReadCount = Random::Get(1, 2);
        std::vector<int> aPasswordReadList;
        aPasswordReadList.push_back(0);
        aPasswordReadList.push_back(1);
        aPasswordReadList.push_back(2);
        Random::Shuffle(&aPasswordReadList);
        if (aPasswordReadCount > 0) {
            mLoopContracts[aPasswordReadList[0]].mSourceB = mSource;
            mLoopContracts[aPasswordReadList[0]].mSecondSourceEnabled = true;
        }
        if (aPasswordReadCount > 1) {
            mLoopContracts[aPasswordReadList[1]].mSourceB = mSource;
            mLoopContracts[aPasswordReadList[1]].mSecondSourceEnabled = true;
        }
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
        aComposerValue.MixVariable(mValue).Expand(50, false);
        
        // source a before
        if (aContract.mValueConsumeOrder_SourceA == SeedConsumeOrder::kBeforeSBox) {
            aComposerValue.MixBuffer(aContract.mSourceA).Offset().Expand(50, true);
        }
        
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
        
        /*
        aComposerValue.Transform().TransformSchemeQuadBoxNibbles(aContract.mValueTransformSBoxA,
                                                                 aContract.mValueTransformSBoxB,
                                                                 aContract.mValueTransformSBoxC,
                                                                 aContract.mValueTransformSBoxD);
        */
        
        /*
        aComposerValue.Transform().TransformSchemeQuadBoxNibbles(aContract.mValueTransformSBoxA,
                                                                 aContract.mValueTransformSBoxB,
                                                                 aContract.mValueTransformSBoxC,
                                                                 aContract.mValueTransformSBoxD,
                                                                 mValueNibbleC,
                                                                 mValueNibbleD,
                                                                 mValueNibbleB,
                                                                 mValueNibbleA,
                                                                 aContract.mValueTransformPlusA,
                                                                 aContract.mValueTransformPlusB,
                                                                 aContract.mValueTransformPlusC,
                                                                 aContract.mValueTransformPlusD);
        */
        
        aComposerValue.Transform().TransformSchemeQuadBoxNibbles(aContract.mValueTransformSBoxA,
                                                                 aContract.mValueTransformSBoxB,
                                                                 aContract.mValueTransformSBoxC,
                                                                 aContract.mValueTransformSBoxD,
                                                                 mValueNibbleC,
                                                                 mValueNibbleD,
                                                                 mValueNibbleB,
                                                                 mValueNibbleA,
                                                                 aContract.mValueTransformPlusA,
                                                                 aContract.mValueTransformPlusB,
                                                                 aContract.mValueTransformPlusC,
                                                                 aContract.mValueTransformPlusD);

        // a = s[a ^ c]
        // b = s[b ^ d]
        // c = s[c ^ a]
        // d = s[d ^ b]

        // mValueNibbleC means c is in place of all a
        // mValueNibbleD means d is in place of all b
        
        
                                                                 
                                                                 

        
        // source a after
        if (aContract.mValueConsumeOrder_SourceA == SeedConsumeOrder::kAfterSBox) {
            aComposerValue.MixBuffer(aContract.mSourceA).Offset().Expand(50, true);
        }
        
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
            if (!pErrorString.empty()) {
                printf("composer error: %s\n", pErrorString.c_str());
            }
            return false;
        }
        
        
        auto BuildCarry = [&]() -> bool {
            if (aContract.mCarryEnabled == false) {
                return true;
            }

            aComposerCarry.ResetSetEqual(mCarry);
            aComposerCarry.MixVariable(mCarry).Expand(50, false);
            
            
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
                    aComposerCarry.MixBuffer(aContract.mCarrySBox).Key(mLoopIndex).Offset();
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
                if (!pErrorString.empty()) {
                    printf("composer error: %s\n", pErrorString.c_str());
                }
                return false;
            }
            
            return true;
        };
        
        auto BuildPermute = [&]() -> bool {
            if (aContract.mPermuteEnabled == false) {
                return true;
            }
            
            aComposerPermute.ResetSetEqual(mPermute);
            
            aComposerPermute.MixVariable(mPermute).Expand(50, false);
            
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
                    aComposerPermute.MixBuffer(aContract.mPermuteSBoxA).Key(mLoopIndex).Offset();
                    break;
                case LoopSBoxBehavior::kPassSelfThrough:
                    break;
                default:
                    break;
            }
            
            aComposerPermute.Transform().TransformSchemeSingleBoxRotate(aContract.mPermuteSBoxB, Random::Get(1, 4));
            
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
                if (!pErrorString.empty()) {
                    printf("composer error: %s\n", pErrorString.c_str());
                }
                return false;
            }
            
            GTarget aValueTarget = GTarget::Symbol(mValue);
            GExpr aValueExpr = GExpr::Symbol(mValue);
            GExpr aPermuteExpr = GExpr::Symbol(mPermute);
            GStatement aPermuteValueStatement = GStatement::Assign(aValueTarget, GExpr::RotL32(aValueExpr, aPermuteExpr));
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
        
        const bool aIsOddLoop = ((aWhich & 1) == 1);
        const bool aWriteForward = (mSecondPass == aIsOddLoop);
        GExpr aLoopIndexExpr = GExpr::Symbol(mLoopIndex);
        GExpr aDestIndexExpr = aWriteForward
            ? aLoopIndexExpr
            : GExpr::Sub(GExpr::Const(S_BLOCK - 1), aLoopIndexExpr);
        GTarget aDestTarget = GTarget::Write(aContract.mDest, aDestIndexExpr);
        GExpr aValueExpr = GExpr::Symbol(mValue);
        GStatement aDestAssignStatement = GStatement::Assign(aDestTarget, aValueExpr);
        aLoop.mBodyStatements.push_back(aDestAssignStatement);
        
        pResult.push_back(aLoop);
    }

    return true;
    
}
