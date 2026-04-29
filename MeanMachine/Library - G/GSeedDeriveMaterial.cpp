//
//  GSeedDeriveMaterial.cpp
//  MeanMachine
//
//  Created by Dragon on 4/29/26.
//

#include "GSeedDeriveMaterial.hpp"
#include "Random.hpp"
#include "TwistCryptoGenerator.hpp"
#include <cctype>
#include <cstdlib>
#include <unordered_map>
#include <functional>

GSeedDeriveMaterial::GSeedDeriveMaterial() {
    mLoopIndex = VarSymbol("aLoopIndex");
    mValue = VarSymbol("aValue");
    mValueMix = VarSymbol("aValueMix");
    mCarry = VarSymbol("aCarry");
    mSource = BufSymbol(TwistWorkSpaceSlot::kSource);

    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxA));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxB));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxC));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxD));

    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltA));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltB));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltC));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltD));

    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxA));
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxB));
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxC));
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxD));

    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneA));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneB));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneC));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneD));
}

GSeedDeriveMaterial::~GSeedDeriveMaterial() {
    
}

GSymbol GSeedDeriveMaterial::BuildMixSymbol(GSymbol pTarget) const {
    if (!pTarget.IsVar()) {
        return VarSymbol("aValueMix");
    }
    return VarSymbol(pTarget.mName + "Mix");
}



void GSeedDeriveMaterial::Reset() {
    
    mListSBoxes.clear();
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxA));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxB));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxC));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxD));

    mListSalts.clear();
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltA));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltB));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltC));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltD));

    mListDerivedSBoxes.clear();
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxA));
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxB));
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxC));
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxD));

    mListWorkers.clear();
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneA));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneB));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneC));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneD));
    
    for (int i=0; i<SEED_WORK_LANE_COUNT; i++) {
        mValueCarryEnabled[i] = false;
        mValueCarryBefore[i] = false;
        
        mValueSalt[i].Invalidate();
        mValueSaltEnabled[i] = false;
        mValueSaltBefore[i] = false;
        
        mValueSourceA[i].Invalidate();
        mValueSourceAEnabled[i] = false;
        mValueSourceABefore[i] = false;
        
        mValueSourceB[i].Invalidate();
        mValueSourceBEnabled[i] = false;
        mValueSourceBBefore[i] = false;
        
        mValueMix161Type[i] = Mix161Type::kInv;
        mValueMix162Type[i] = Mix162Type::kInv;
        mValueMixChoice[i] = false;
        
        mDestBuffer[i].Invalidate();
        mDestReverse[i] = false;
    }
}

bool GSeedDeriveMaterial::PlanPhaseA(std::string &pError) {
    
    Reset();
    
    for (int i=0; i<SEED_WORK_LANE_COUNT; i++) {
        mValueCarryEnabled[i] = true;
        mValueCarryBefore[i] = true;
        
        mValueSalt[i] = mListSalts[i];
        mValueSaltEnabled[i] = true;
        mValueSaltBefore[i] = true;
        
        mValueSourceA[i] = mListWorkers[i];
        mValueSourceAEnabled[i] = true;
        mValueSourceABefore[i] = false;
        
        mValueSourceB[i] = mListWorkers[(i + 1) % SEED_WORK_LANE_COUNT];
        mValueSourceBEnabled[i] = true;
        mValueSourceBBefore[i] = false;
        
        mValueMix161Type[i] = RandomMix161Type();
        mValueMix162Type[i] = RandomMix162Type();
        mValueMixChoice[i] = Random::Bool();
    }
    
    return true;
}


bool GSeedDeriveMaterial::BuildPhaseA(TwistProgramBranch &pBranch,
                                     std::string &pError) {
    pError.clear();
    pBranch.Clear();

    mWorkerA = mListWorkers[0];
    mWorkerB = mListWorkers[1];
    mWorkerC = mListWorkers[2];
    mWorkerD = mListWorkers[3];

    mSaltA = mListSalts[0];
    mSaltB = mListSalts[1];
    mSaltC = mListSalts[2];
    mSaltD = mListSalts[3];

    mSBoxA = mListSBoxes[0];
    mSBoxB = mListSBoxes[1];
    mSBoxC = mListSBoxes[2];
    mSBoxD = mListSBoxes[3];

    mDerivedSBoxA = mListDerivedSBoxes[0];
    mDerivedSBoxB = mListDerivedSBoxes[1];
    mDerivedSBoxC = mListDerivedSBoxes[2];
    mDerivedSBoxD = mListDerivedSBoxes[3];

    
    GBatch aLoopBatchA;
    aLoopBatchA.mName = "seed_phase_a_loop_1";
    GLoop aLoop;
    aLoop.mLoopVariable = mLoopIndex;
    aLoop.mLoopVariableName = mLoopIndex.mName;
    aLoop.mLoopBegin = 0;
    aLoop.mLoopEndText = "S_BLOCK";
    aLoop.mLoopStep = 1;
    
    GLoopFragmentComposer aComposerValue(mLoopIndex);
    GLoopFragmentComposer aComposerValueMix(mLoopIndex);

    for (int i=0; i<SEED_WORK_LANE_COUNT; i++) {
        
        std::vector<std::function<void()>> aValueActionsPre;
        std::vector<std::function<void()>> aValueActionsPost;
        
        aComposerValue.ResetSetEqual(mValue);
        aComposerValueMix.ResetSetEqual(mValueMix);
        
        if (mValueCarryEnabled[i] == true) {
            GLoopFragmentComposer *aComposer;
            
            if (mValueCarryBefore[i]) { aComposer = &aComposerValueMix; } else { aComposer = &aComposerValue; }
            
            GSymbol aCarry = mCarry;
            auto aAction = [aComposer, aCarry]() {
                aComposer->MixVariable(aCarry);
            };
            
            if (mValueCarryBefore[i]) { aValueActionsPre.push_back(aAction); } else { aValueActionsPost.push_back(aAction); }
        }
        
        if (mValueSourceAEnabled[i] == true) {
            GLoopFragmentComposer *aComposer;
            
            if (mValueSourceABefore[i]) { aComposer = &aComposerValueMix; } else { aComposer = &aComposerValue; }
            
            GSymbol aSource = mValueSourceA[i];
            auto aAction = [aComposer, aSource]() {
                aComposer->MixBuffer(aSource).Offset();
            };
            
            if (mValueSourceABefore[i]) { aValueActionsPre.push_back(aAction); } else { aValueActionsPost.push_back(aAction); }
        }
        
        if (mValueSourceBEnabled[i] == true) {
            GLoopFragmentComposer *aComposer;
            
            if (mValueSourceBBefore[i]) { aComposer = &aComposerValueMix; } else { aComposer = &aComposerValue; }
            
            GSymbol aSource = mValueSourceB[i];
            auto aAction = [aComposer, aSource]() {
                aComposer->MixBuffer(aSource).Offset();
            };
            
            if (mValueSourceBBefore[i]) { aValueActionsPre.push_back(aAction); } else { aValueActionsPost.push_back(aAction); }
        }
        
        if (mValueSaltEnabled[i] == true) {
            GLoopFragmentComposer *aComposer;
            
            if (mValueSaltBefore[i]) { aComposer = &aComposerValueMix; } else { aComposer = &aComposerValue; }
            
            GSymbol aSource = mValueSalt[i];
            auto aAction = [aComposer, aSource]() {
                aComposer->MixBuffer(aSource).Offset();
            };
            
            if (mValueSaltBefore[i]) { aValueActionsPre.push_back(aAction); } else { aValueActionsPost.push_back(aAction); }
        }
        
        // later on

        if (aValueActionsPre.size() > 0) {
            
            for (auto aAction: aValueActionsPre) {
                aAction();
            }
            if (!aComposerValueMix.BakeStatements(&(aLoop.mBodyStatements), &pError)) {
                return false;
            }
            
            aLoop.mBodyStatements.push_back(
                GStatement::Assign(
                    GTarget::Symbol(mValue),
                    GExpr::Mix161(GExpr::Symbol(mValueMix), Mix161Type::kMix161_005, mSBoxA)));
            if (aValueActionsPost.size() > 0) {
                
                for (auto aAction: aValueActionsPost) {
                    aAction();
                }
                if (!aComposerValue.BakeStatements(&(aLoop.mBodyStatements), &pError)) {
                    return false;
                }
            }
            
        } else {
            // All post actions...
            
            aLoop.mBodyStatements.push_back(
                GStatement::Assign(
                    GTarget::Symbol(mValue),
                    GExpr::Mix161(GExpr::Symbol(mValueMix), Mix161Type::kMix161_005, mSBoxA)));
            
        }
        
        
    }
    
    
    GBatch aBatch;
    aBatch.CommitLoop(aLoop);
    pBranch.AddBatch(aBatch);

    /*
    GLoopFragmentComposer aComposerA(mLoopIndex);
    aComposerA.ResetSetEqual(aValueMix);
    aComposerA.EnableDebugAddXor({ true, false }); // target, +carry, ^sbox
    aComposerA.MixVariable(mValue);
    aComposerA.MixVariable(mCarry);
    aComposerA.MixBuffer(mSBoxA)
        .Key(mLoopIndex)
        .Domain(GLoopFragmentDomain::kSBox)
        .Offset(0);

    if (!aComposerA.BakeStatements(&aLoop.mBodyStatements, &pError)) {
        return false;
    }

    aLoop.mBodyStatements.push_back(
        GStatement::Assign(
            GTarget::Symbol(mValue),
            GExpr::Mix161(GExpr::Symbol(aValueMix), Mix161Type::kMix161_004, mSBoxB)));

    aLoopBatchA.CommitLoop(aLoop);
    pBranch.AddBatch(aLoopBatchA);

    // derive 4 s-boxes (shows up in exported C++ and executes in branch runtime)
    pBranch.AddLine("TwistCryptoGenerator aCryptoGenerator;");
    pBranch.AddLine("aCryptoGenerator.Make(aSource, aDerivedSBoxA, aDerivedSBoxB, aDerivedSBoxC, aDerivedSBoxD);");

    // tiny demo loop 2 (transform model):
    // aValueMix = aCarry ^ aValue;
    // aValue = TwistMix16::Mix161_005(aValueMix, aDerivedSBoxA);
    GBatch aLoopBatchB;
    aLoopBatchB.mName = "seed_phase_a_loop_2";
    GLoop aLoopB;
    ConfigureLoop(&aLoopB, mLoopIndex);

    GLoopFragmentComposer aComposerB(mLoopIndex);
    aComposerB.ResetSetEqual(aValueMix);
    aComposerB.EnableDebugAddXor({ false }); // target, ^value
    aComposerB.MixVariable(mCarry);
    aComposerB.MixVariable(mValue);

    if (!aComposerB.BakeStatements(&aLoopB.mBodyStatements, &pError)) {
        return false;
    }

    aLoopB.mBodyStatements.push_back(
        GStatement::Assign(
            GTarget::Symbol(mValue),
            GExpr::Mix161(GExpr::Symbol(aValueMix), Mix161Type::kMix161_005, mDerivedSBoxA)));

    aLoopBatchB.CommitLoop(aLoopB);
    pBranch.AddBatch(aLoopBatchB);
    */

    return true;
}

Mix161Type GSeedDeriveMaterial::RandomMix161Type() {
    std::vector<Mix161Type> aTypes = {
        Mix161Type::kMix161_000,
        Mix161Type::kMix161_001,
        Mix161Type::kMix161_002,
        Mix161Type::kMix161_003,
        Mix161Type::kMix161_004,
        Mix161Type::kMix161_005,
        Mix161Type::kMix161_006,
        Mix161Type::kMix161_007
    };
    return Random::Choice(aTypes);
}

Mix162Type GSeedDeriveMaterial::RandomMix162Type() {
    std::vector<Mix162Type> aTypes = {
        Mix162Type::kMix162_000,
        Mix162Type::kMix162_001,
        Mix162Type::kMix162_002,
        Mix162Type::kMix162_003,
        Mix162Type::kMix162_004,
        Mix162Type::kMix162_005,
        Mix162Type::kMix162_006,
        Mix162Type::kMix162_007,
        Mix162Type::kMix162_008,
        Mix162Type::kMix162_009,
        Mix162Type::kMix162_010,
        Mix162Type::kMix162_011,
        Mix162Type::kMix162_012,
        Mix162Type::kMix162_013,
        Mix162Type::kMix162_014,
        Mix162Type::kMix162_015
    };
    return Random::Choice(aTypes);
}
