//
//  TwistSeedBuilder.cpp
//  MeanMachine
//

#include "TwistSeedBuilder.hpp"

GSymbol VarSymbol(const std::string &pName) {
    return GSymbol::Var(pName);
}

GSymbol BufSymbol(const TwistWorkSpaceSlot pSlot) {
    return GSymbol::Buf(pSlot);
}

GLoop TwistSeedBuilder::BuildBaselineLoop(const TwistSeedLoopOptions &pOptions) {
    const GSymbol aLoopIndex = VarSymbol(pOptions.mLoopIndexName);
    const GSymbol aState = VarSymbol(pOptions.mStateName);
    const GSymbol aMix = VarSymbol(pOptions.mMixName);
    const GSymbol aValue = VarSymbol(pOptions.mValueName);
    const GSymbol aCarry = VarSymbol(pOptions.mCarryName);

    const GExpr aLoopExpr = GExpr::Symbol(aLoopIndex);
    const GExpr aSourceRead = GExpr::Read(BufSymbol(pOptions.mSourceSlot), aLoopExpr);
    GExpr aMixLeft = aSourceRead;
    if (pOptions.mMutations.mAddSourceConstant) {
        aMixLeft = GExpr::Add(aMixLeft, GExpr::Const(pOptions.mMutations.mSourceConstant));
    }

    GExpr aStateInput = GExpr::Symbol(aState);
    if (pOptions.mMutations.mRotateState) {
        aStateInput = GExpr::RotateLeft8(aStateInput, GExpr::Const(pOptions.mMutations.mRotateAmount));
    }

    GExpr aMixExpr = GExpr::Xor(aMixLeft, aStateInput);
    if (pOptions.mMutations.mUseSaltTerm) {
        GExpr aSaltTerm = GExpr::Read(BufSymbol(pOptions.mSaltSlot), aLoopExpr);
        aSaltTerm = GExpr::Mul(aSaltTerm, GExpr::Const(pOptions.mMutations.mSaltMultiply));
        aMixExpr = GExpr::Xor(aMixExpr, aSaltTerm);
    }

    GExpr aLookupIndex = GExpr::Symbol(aMix);
    if (pOptions.mMutations.mBiasLookupIndex) {
        aLookupIndex = GExpr::Add(aLookupIndex, GExpr::Const(pOptions.mMutations.mLookupBias));
    }
    if (pOptions.mMutations.mUseCarry) {
        GExpr aCarryExpr = GExpr::Add(GExpr::Symbol(aCarry), GExpr::Const(pOptions.mMutations.mCarryBias));
        aLookupIndex = GExpr::Xor(aLookupIndex, aCarryExpr);
    }

    GExpr aStateExpr = GExpr::Symbol(aValue);
    if (pOptions.mMutations.mMaskState) {
        const GExpr aMaskExpr = GExpr::Read(BufSymbol(pOptions.mMaskSlot), aLoopExpr);
        const GExpr aMaskedValue = GExpr::And(GExpr::Symbol(aValue), aMaskExpr);
        const GExpr aShiftedValue = GExpr::Add(GExpr::Symbol(aValue), GExpr::Const(pOptions.mMutations.mStateAdd));
        aStateExpr = GExpr::Xor(aMaskedValue, aShiftedValue);
    }

    GLoop aLoop;
    aLoop.mLoopVariable = aLoopIndex;
    aLoop.mLoopVariableName = pOptions.mLoopIndexName;
    aLoop.mLoopBegin = 0;
    aLoop.mLoopEndText = "S_BLOCK";
    aLoop.mLoopStep = 1;

    aLoop.mInitializationStatements.push_back(
        GStatement::Assign(GTarget::Symbol(aState), GExpr::Const(0))
    );
    if (pOptions.mMutations.mUseCarry) {
        aLoop.mInitializationStatements.push_back(
            GStatement::Assign(GTarget::Symbol(aCarry), GExpr::Const(0))
        );
    }

    aLoop.mBodyStatements.push_back(
        GStatement::Assign(GTarget::Symbol(aMix), aMixExpr)
    );
    aLoop.mBodyStatements.push_back(
        GStatement::Assign(GTarget::Symbol(aValue),
                           GExpr::Read(BufSymbol(pOptions.mLookupSlot), aLookupIndex))
    );
    aLoop.mBodyStatements.push_back(
        GStatement::Assign(GTarget::Symbol(aState), aStateExpr)
    );
    aLoop.mBodyStatements.push_back(
        GStatement::Assign(GTarget::Write(BufSymbol(pOptions.mOutputSlot), aLoopExpr),
                           GExpr::Symbol(aState))
    );

    if (pOptions.mMutations.mUseCarry) {
        aLoop.mBodyStatements.push_back(
            GStatement::Assign(GTarget::Symbol(aCarry), GExpr::Symbol(aValue))
        );
    }

    return aLoop;
}

GBatch TwistSeedBuilder::BuildBaselineBatch(const TwistSeedLoopOptions &pOptions) {
    GBatch aBatch;
    aBatch.mName = "baseline_seed_batch";
    aBatch.CommitLoop(BuildBaselineLoop(pOptions));
    return aBatch;
}
