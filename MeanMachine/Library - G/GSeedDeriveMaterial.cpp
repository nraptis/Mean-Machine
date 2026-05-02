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

GSeedDeriveMaterial::GSeedDeriveMaterial() {
    mLoopIndex = VarSymbol("aIndex");
    mValue = VarSymbol("aValue");
    mValueMix = VarSymbol("aValueMix");
    mCarry = VarSymbol("aCarry");
    mCarryMix = VarSymbol("aCarryMix");
    mSelect = VarSymbol("aSelect");
    mMultiplex = VarSymbol("aMultiplex");
    mUnrollByte = VarSymbol("aUnrollByte");
    
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
    
    mListExpansion.push_back(BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneA));
    mListExpansion.push_back(BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneB));
    mListExpansion.push_back(BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneC));
    mListExpansion.push_back(BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneD));
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
    
    mListExpansion.clear();
    mListExpansion.push_back(BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneA));
    mListExpansion.push_back(BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneB));
    mListExpansion.push_back(BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneC));
    mListExpansion.push_back(BufSymbol(TwistWorkSpaceSlot::kSeedExpansionLaneD));
    
    
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
        
        mValueSourceC[i].Invalidate();
        mValueSourceCEnabled[i] = false;
        mValueSourceCBefore[i] = false;
        
        
        mValueMix64Type_1[i] = Mix64Type_1::kInv;
        mValueMix64Type_4[i] = Mix64Type_4::kInv;
        mValueMix64Type_8[i] = Mix64Type_8::kInv;
        
        mValueMixChoice[i] = false;
        
        mDestBuffer[i].Invalidate();
        mDestReverse[i] = false;
    }
}

bool GSeedDeriveMaterial::PlanPhaseA(std::string *pErrorMessage) {
    
    Reset();
    
    // mListExpansion shuffle
    
    
    mWorkerA = mListWorkers[0];
    mWorkerB = mListWorkers[1];
    mWorkerC = mListWorkers[2];
    mWorkerD = mListWorkers[3];
    
    mSBoxA = mListSBoxes[0];
    mSBoxB = mListSBoxes[1];
    mSBoxC = mListSBoxes[2];
    mSBoxD = mListSBoxes[3];
    
    mExpansionA = mListExpansion[0];
    mExpansionB = mListExpansion[1];
    mExpansionC = mListExpansion[2];
    mExpansionD = mListExpansion[3];

    mSaltA = mListSalts[0];
    mSaltB = mListSalts[1];
    mSaltC = mListSalts[2];
    mSaltD = mListSalts[3];
    
    mDerivedSBoxA = mListDerivedSBoxes[0];
    mDerivedSBoxB = mListDerivedSBoxes[1];
    mDerivedSBoxC = mListDerivedSBoxes[2];
    mDerivedSBoxD = mListDerivedSBoxes[3];
    
    
    for (int i=0; i<SEED_WORK_LANE_COUNT; i++) {
        mValueCarryEnabled[i] = true;
        mValueCarryBefore[i] = true;
        
        mValueSalt[i] = mListSalts[i];
        mValueSaltEnabled[i] = true;
        mValueSaltBefore[i] = true;
        
        mValueSourceA[i].Invalidate();
        mValueSourceAEnabled[i] = false;
        mValueSourceABefore[i] = false;
        
        mValueSourceB[i].Invalidate();
        mValueSourceBEnabled[i] = false;
        mValueSourceBBefore[i] = false;
        
        mValueSourceC[i] = mListExpansion[i];
        mValueSourceCEnabled[i] = true;
        mValueSourceCBefore[i] = Random::Bool();
        
        mValueMix64Type_1[i] = RandomMix64Type_1();
        mValueMix64Type_4[i] = RandomMix64Type_4();
        mValueMix64Type_8[i] = RandomMix64Type_8();
        
        mValueMixChoice[i] = Random::Bool();
        
        mDestBuffer[i] = mListWorkers[i];
        if ((i & 1) == 0) {
            mDestReverse[i] = false;
        } else {
            mDestReverse[i] = true;
        }
    }
    
    mValueSourceA[0] = mSource;
    mValueSourceAEnabled[0] = true;
    mValueSourceABefore[0] = Random::Bool();
    
    mValueSourceB[0] = mListExpansion[0];
    mValueSourceBEnabled[0] = true;
    mValueSourceBBefore[0] = Random::Bool();
    
    mValueSourceC[0] = mListExpansion[0];
    mValueSourceCEnabled[0] = false;
    mValueSourceCBefore[0] = false;
    
    mValueSourceA[1] = mListWorkers[0];
    mValueSourceAEnabled[1] = true;
    mValueSourceABefore[1] = Random::Bool();
    
    mValueSourceB[1] = mSource;
    mValueSourceBEnabled[1] = Random::Bool();
    mValueSourceBBefore[1] = Random::Bool();
    
    mValueSourceC[1] = mListExpansion[1];
    mValueSourceCEnabled[1] = true;
    mValueSourceCBefore[1] = Random::Bool();
    
    mValueSourceA[2] = mListWorkers[1];
    mValueSourceAEnabled[2] = true;
    mValueSourceABefore[2] = Random::Bool();

    mValueSourceB[2] = mListWorkers[0];
    mValueSourceBEnabled[2] = Random::Bool();
    mValueSourceBBefore[2] = Random::Bool();

    mValueSourceC[2] = mListExpansion[2];
    mValueSourceCEnabled[2] = true;
    mValueSourceCBefore[2] = Random::Bool();
    
    mValueSourceA[3] = mListWorkers[2];
    mValueSourceAEnabled[3] = true;
    mValueSourceABefore[3] = Random::Bool();

    mValueSourceB[3] = mListWorkers[1];
    mValueSourceBEnabled[3] = Random::Bool();
    mValueSourceBBefore[3] = Random::Bool();

    mValueSourceC[3] = mListExpansion[3];
    mValueSourceCEnabled[3] = true;
    mValueSourceCBefore[3] = Random::Bool();
    
    return true;
}

bool GSeedDeriveMaterial::BuildPhaseA(TwistProgramBranch &pBranch,
                                      std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) { pErrorMessage->clear(); }
    pBranch.Clear();

    
    
    
    
    
    if (!BuildSnow(pBranch, pErrorMessage)) {
        printf("build snow failed, %s\n", pErrorMessage->c_str());
        return false;
    }
    
    
    
    
    
    {
        
        
        

        
        
        mValueSourceA[0] = mSource;
        
        mValueSourceBEnabled[0] = false;
        mValueSourceB[0] = mSource;
        
        mValueSourceA[0] = mExpansionA;
        mValueSourceB[0] = mSource;
    }
    
    
    
    // aState ^= aChar + 0x9E3779B97F4A7C15ULL + (aState << 6) + (aState >> 2);
    // aState *= 0xD6E8FEB86659FD93ULL;
    
    GBatch aBatchRoundOne;
    
    for (int i=0; i<4; i++) {
        
        GLoop aLoop;
        aLoop.mLoopVariable = mLoopIndex;
        aLoop.mLoopVariableName = mLoopIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 1;
        
        std::vector<GStatement> aStatements;
        
        
        GLoopMixBrew aMixBrew;
        aMixBrew.SetLoopIndex(mLoopIndex);
        aMixBrew.SetTarget(mValue, mValueMix);
        
        aMixBrew.SetMix_1(Mix64Type_1::kGateRoll_1_1, 3, mSBoxA);
        
        
        // We need .OffsetIverted() [ this picks random value]
        // We need .OffsetIvertedRandom() [this randomly chooses inverted or not inverted, then randomly chooses value]
        aMixBrew.PutBufferXor(mListSalts[i], mValueSaltBefore[i]).OffsetIverted(99);
        
        if ((mValueSourceAEnabled[i] == true) && (mValueSourceA[i].IsInvalid() == false)) {
            
            // We need "PutBufferRandom"
            aMixBrew.PutBufferAdd(mValueSourceA[i], mValueSourceABefore[i]);
        }
        
        if ((mValueSourceBEnabled[i] == true) && (mValueSourceB[i].IsInvalid() == false)) {
            
            // We need "PutBufferRandom"
            aMixBrew.PutBufferAdd(mValueSourceB[i], mValueSourceBBefore[i]);
        }
        
        if ((mValueSourceCEnabled[i] == true) && (mValueSourceC[i].IsInvalid() == false)) {
            
            // We need "PutBufferRandom"
            aMixBrew.PutBufferAdd(mValueSourceB[i], mValueSourceCBefore[i]);
        }

        if (!aMixBrew.Bake(GAssignType::kXorAssign, GAssignType::kAddAssign, &aStatements, pErrorMessage)) {
            printf("mix brew bake failed: %s\n", pErrorMessage->c_str());
            return false;
        }
        
        aLoop.AddBody(&aStatements);
        
        // We need: MakeAssignDestStatementInverted
        GStatement aAssignDestStatement = GQuick::MakeAssignDestStatement(mDestBuffer[i], mLoopIndex, mValue);
        
        aLoop.AddBody(&aAssignDestStatement);
        
        
        aBatchRoundOne.CommitLoop(&aLoop);
    }
    
    pBranch.AddBatch(aBatchRoundOne);
    

    
    /*
     GBatch aBatchExpansion;
    aBatchExpansion.mName = "pre-step, known counters";
    for (int i=0;i<SEED_WORK_LANE_COUNT;i++) {
        
        GLoop aLoop;
        aLoop.mLoopVariable = mLoopIndex;
        aLoop.mLoopVariableName = mLoopIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 1;
        
        GExpr aLoopIndex = GExpr::Symbol(mLoopIndex);
        GExpr aRead = GExpr::Read(mSource, aLoopIndex);
        GTarget aWrite = GTarget::Write(mListExpansion[i], aLoopIndex);
        
        
        
        aComposer.ResetSetEqual(mValue);
        aComposer.MixBuffer(mSource);
        aComposer.MixVariable(mValue).ExpandDebug(GTermPattern::kMul, 33, 0);
        aComposer.MixVariable(mCarry).ExpandDebug(GTermPattern::kPostRotateMul, 3, 21);
        
        
        if (!aComposer.Bake(&aStatements, pErrorMessage)) {
            printf("bake statements failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
            return false;
        }
        aLoop.AddBodyComment("Update value, demo");
        aLoop.AddBody(&aStatements);
        aLoop.AddBodyEmptyLine();
        
        
        
        aComposer.ResetSetEqual(mCarry);
        aComposer.MixVariable(mCarry).ExpandDebug(GTermPattern::kMul, 27, 0);
        aComposer.MixBuffer(mSaltA).ExpandDebug(GTermPattern::kAdd, 7, 0);
        if (!aComposer.Bake(&aStatements, pErrorMessage)) {
            printf("bake statements failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
            return false;
        }
        
        
        aLoop.AddBodyComment("Update carry, demo");
        aLoop.AddBody(&aStatements);
        aLoop.AddBodyEmptyLine();
        
        
        GStatement aAssignDestStatement = GQuick::MakeAssignDestStatement(mListExpansion[i],
                                                                 mLoopIndex,
                                                                 mValue);
        aLoop.AddBody(&aAssignDestStatement);
        aLoop.AddBodyComment("--------------");
        
        aBatchExpansion.CommitLoop(&aLoop);
    }
    pBranch.AddBatch(aBatchExpansion);
    */
    
    
    GBatch aBatchMatrix;
    aBatchMatrix.mName = "matrix_op_step";

    for (int i=0;i<SEED_WORK_LANE_COUNT;i++) {
        GLoop aLoop;
        aLoop.mLoopVariable = mLoopIndex;
        aLoop.mLoopVariableName = mLoopIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 64;
        
        std::vector<TwistFastMatrixOp> aIgnoreList;
        
        std::vector<TwistFastMatrixOp> aSlowA = GFastMatrix::GetRandomOpsSlow(18, aIgnoreList);
        std::vector<TwistFastMatrixOp> aMedA = GFastMatrix::GetRandomOpsMedium(18, aIgnoreList);
        std::vector<TwistFastMatrixOp> aFastA = GFastMatrix::GetRandomOpsFast(18, aIgnoreList);
        
        std::vector<TwistFastMatrixOp> aSlowB = GFastMatrix::GetRandomOpsSlow(18, aIgnoreList);
        std::vector<TwistFastMatrixOp> aMedB = GFastMatrix::GetRandomOpsMedium(18, aIgnoreList);
        std::vector<TwistFastMatrixOp> aFastC = GFastMatrix::GetRandomOpsFast(18, aIgnoreList);
        
        std::vector<TwistFastMatrixOp> aOps;
        aOps.insert(aOps.end(), aSlowA.begin(), aSlowA.end());
        aOps.insert(aOps.end(), aMedA.begin(),  aMedA.end());
        aOps.insert(aOps.end(), aFastA.begin(), aFastA.end());

        aOps.insert(aOps.end(), aSlowB.begin(), aSlowB.end());
        aOps.insert(aOps.end(), aMedB.begin(),  aMedB.end());
        aOps.insert(aOps.end(), aFastC.begin(), aFastC.end());
        
        
        GFastMatrix aMatrix(GFastMatrixType::kA);
        std::vector<GStatement> aMatrixStatements;
        if (!aMatrix.BakeLoad(mListWorkers[i], mLoopIndex, &aMatrixStatements, pErrorMessage)) {
            printf("bake load failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
            return false;
        }
        aLoop.AddBody(&aMatrixStatements);
        
        
        int a=0;
        for (auto &s: aOps) {
            
            std::string aByteA = "aByte___" + std::to_string(a++);
            std::string aByteB = "aByte___" + std::to_string(a++);
            GSymbol aVarA = VarSymbol(aByteA);
            GSymbol aVarB = VarSymbol(aByteB);
            
            aMatrix.Perform(s);
            /*
                            aVarA, mListWorkers[i], mLoopIndex, Random::Get(16),
                            aVarB, mListWorkers[i], mLoopIndex, Random::Get(16));
            */
            
        }
        
        aMatrixStatements.clear();
        if (!aMatrix.BakePerform(&aMatrixStatements, pErrorMessage)) {
            printf("bake perform failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
            return false;
        }
        aLoop.AddBody(&aMatrixStatements);
        
        
        GStatement aUnrollByteStatement = GQuick::MakeAssignOffsetByteStatement(mUnrollByte, mListWorkers[(i + 1) % 4], mLoopIndex, Random::Get(16));
        aLoop.AddBody(&aUnrollByteStatement);
        
        TwistFastMatrixUnrollScheme aUnroll = GFastMatrix::GetRandomUnrollScheme();
        
        aMatrixStatements.clear();
        if (!aMatrix.BakeUnroll(mListWorkers[i], mLoopIndex, aUnroll, mUnrollByte, &aMatrixStatements, pErrorMessage)) {
            printf("bake unroll failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
            return false;
        }
        aLoop.AddBody(&aMatrixStatements);
        
        aBatchMatrix.CommitLoop(&aLoop);
        
        
    }
    pBranch.AddBatch(aBatchMatrix);
    
    std::vector<GStatement> aStatements;
    GBatch aBatchMasks;
    aBatchMasks.mName = "masks step";
    GMasking aMasking;
    if (!aMasking.BakeBraidA(mListExpansion[0],
                             mListExpansion[1],
                             mListExpansion[2],
                             &aStatements,
                             pErrorMessage)) {
        printf("bake braid a failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
        return false;
    }
    aBatchMasks.CommitStatements(&aStatements);
    pBranch.AddBatch(aBatchMasks);
    
    //aBatchMaskez.CommitLoop(<#const GLoop &pLoop#>)
    
    
    
    /*
    GBatch aLoopBatchA;
    aLoopBatchA.mName = "seed_phase_a_loop_1";
    GLoop aLoop;
    aLoop.mLoopVariable = mLoopIndex;
    aLoop.mLoopVariableName = mLoopIndex.mName;
    aLoop.mLoopBegin = 0;
    aLoop.mLoopEndText = "S_BLOCK";
    aLoop.mLoopStep = 1;

    
    // GSelect
    
    GLoopMixBrew aMixBrewA;
    aMixBrewA.SetRandomOrderEnabled(false);
    aMixBrewA.SetLoopIndex(mLoopIndex);
    aMixBrewA.SetTarget(mValue, mValueMix);
    aMixBrewA.SetMix_4(Mix64Type_4::kGatePrismB_4_8, mSBoxA, mSBoxB, mSBoxA, mSBoxB);
    aMixBrewA.PutVariableAdd(mValue, true);
    aMixBrewA.PutVariableAdd(mCarry, true).ExpandDebug(GTermPattern::kPostRotateAdd, 5, 115);
    aMixBrewA.PutBufferXor(mSource, false);
    std::vector<GStatement> aStatementsA;
    if (!aMixBrewA.Bake(GAssignType::kXorAssign, GAssignType::kAddAssign, &aStatementsA, pErrorMessage)) {
        printf("bake statements failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
        return false;
    }
    
    GLoopMixBrew aMixBrewB;
    aMixBrewB.SetRandomOrderEnabled(false);
    aMixBrewB.SetLoopIndex(mLoopIndex);
    aMixBrewB.SetTarget(mCarry, mCarryMix);
    aMixBrewB.SetMix_1(Mix64Type_1::kGateRoll_1_8, 5U, mSBoxD);
    aMixBrewB.PutBufferXor(mSource, false);
    aMixBrewB.PutVariableAdd(mCarry, true).ExpandDebug(GTermPattern::kPostRotateAdd, 5, 115);
    
    std::vector<GStatement> aStatementsB;
    if (!aMixBrewB.Bake(GAssignType::kAddAssign, GAssignType::kAddAssign, &aStatementsB, pErrorMessage)) {
        printf("bake statements failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
        return false;
    }
    
    
    GLoopFragmentComposer aComposerSelect;
    aComposerSelect.ResetSetEqual(mMultiplex);
    aComposerSelect.MixBuffer(mSource).OffsetIverted(8050).ExpandDebug(GTermPattern::kMulThenXor, 111, 0xDF).Key(mLoopIndex).OffsetIverted(119);
    aComposerSelect.MixVariable(mValue).ExpandDebug(GTermPattern::kMul, 33, 0);
    std::vector<GStatement> aStatementsMultiplex;
    if (!aComposerSelect.Bake(&aStatementsMultiplex, pErrorMessage)) {
        printf("bake statements failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
        return false;
    }
    aLoop.AddBody(&aStatementsMultiplex);
    
    GSelect aSelect = GSelect::Random2();
    
    aSelect.AddStatementsA(&aStatementsA);
    aSelect.AddStatementsB(&aStatementsB);
    
    std::vector<GStatement> aStatementsSelect;
    if (!aSelect.Bake(mSelect, mMultiplex, &aStatementsSelect, pErrorMessage)) {
        printf("bake statements failed: %s\n", ((pErrorMessage != nullptr) ? pErrorMessage->c_str() : ""));
        return false;
    }
    
    aLoop.AddBody(&aStatementsSelect);
    
    GStatement aAssignDestA = GQuick::MakeAssignDestStatement(mWorkerA, mLoopIndex, mValue);
    
    aLoop.AddBody(&aAssignDestA);
    
    GBatch aBatch;
    aBatch.CommitLoop(&aLoop);
    pBranch.AddBatch(aBatch);
    */
    
    

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

    if (!aComposerA.Bake(&aLoop.mBodyStatements, pErrorMessage)) {
        return false;
    }

    aLoop.mBodyStatements.push_back(
        GStatement::Assign(
            GTarget::Symbol(mValue),
            GExpr::Mix161(GExpr::Symbol(aValueMix), Mix161Type::kMix161_004, mSBoxB)));

    aLoopBatchA.CommitLoop(&aLoop);
    pBranch.AddBatch(aLoopBatchA);

    // derive 4 s-boxes (shows up in exported C++ and executes in branch runtime)
    pBranch.AddLine("TwistCryptoGenerator aCryptoGenerator;");
    pBranch.AddLine("aCryptoGenerator.Make(aSource, aDerivedSBoxA, aDerivedSBoxB, aDerivedSBoxC, aDerivedSBoxD);");

    // tiny demo loop 2 (transform model):
    // aValueMix = aCarry ^ aValue;
    // aValue = TwistMix64::Mix161_005(aValueMix, aDerivedSBoxA);
    GBatch aLoopBatchB;
    aLoopBatchB.mName = "seed_phase_a_loop_2";
    GLoop aLoopB;
    ConfigureLoop(&aLoopB, mLoopIndex);

    GLoopFragmentComposer aComposerB(mLoopIndex);
    aComposerB.ResetSetEqual(aValueMix);
    aComposerB.EnableDebugAddXor({ false }); // target, ^value
    aComposerB.MixVariable(mCarry);
    aComposerB.MixVariable(mValue);

    if (!aComposerB.Bake(&aLoopB.mBodyStatements, pErrorMessage)) {
        return false;
    }

    aLoopB.mBodyStatements.push_back(
        GStatement::Assign(
            GTarget::Symbol(mValue),
            GExpr::Mix161(GExpr::Symbol(aValueMix), Mix161Type::kMix161_005, mDerivedSBoxA)));

    aLoopBatchB.CommitLoop(&aLoopB);
    pBranch.AddBatch(aLoopBatchB);
    */

    return true;
}

Mix64Type_1 GSeedDeriveMaterial::RandomMix64Type_1() {
    std::vector<Mix64Type_1> aTypes = TwistMix64::GetAll_1();
    return Random::Choice(aTypes);
}

Mix64Type_4 GSeedDeriveMaterial::RandomMix64Type_4() {
    std::vector<Mix64Type_4> aTypes = TwistMix64::GetAll_4();
    return Random::Choice(aTypes);
}

Mix64Type_8 GSeedDeriveMaterial::RandomMix64Type_8() {
    std::vector<Mix64Type_8> aTypes = TwistMix64::GetAll_8();
    return Random::Choice(aTypes);
}

bool GSeedDeriveMaterial::BuildSnow(TwistProgramBranch &pBranch, std::string *pErrorMessage) {
    
    GBatch aBatchSnow;
    aBatchSnow.mName = "Snow";
    GSnow aSnow;
    
    std::vector<GStatement> aSnowStatements;
    if (!aSnow.BakeAES256(mSource, mListExpansion[0], &aSnowStatements, pErrorMessage)) {
        printf("aes failed\n");
        return false;
    }
    if (!aSnow.BakeChaCha20(mSource, mListExpansion[1], &aSnowStatements, pErrorMessage)) {
        printf("cha cha failed\n");
        return false;
    }
    if (!aSnow.BakeAria256(mSource, mListExpansion[2], &aSnowStatements, pErrorMessage)) {
        printf("aria failed\n");
        return false;
    }
    if (!aSnow.BakeSha256(mSource, mListExpansion[3], &aSnowStatements, pErrorMessage)) {
        printf("sha failed\n");
        return false;
    }
    aBatchSnow.CommitStatements(&aSnowStatements);
    
    return true;
}

