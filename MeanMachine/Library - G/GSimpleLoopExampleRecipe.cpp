//
//  GSimpleLoopExampleRecipe.cpp
//  MeanMachine
//
//  Created by Trombone on 4/26/26.
//

#include "GSimpleLoopExampleRecipe.hpp"
#include "GLoopFragmentComposer.hpp"

GSimpleLoopExampleRecipe::GSimpleLoopExampleRecipe() {
    
    mLoopIndex = VarSymbol("aLoopIndex");
    
    mValue = VarSymbol("aValue");
    
    mCarry = VarSymbol("aCarry");
    
    mSBoxA = BufSymbol(TwistWorkSpaceSlot::kSBoxA);
    mSBoxB = BufSymbol(TwistWorkSpaceSlot::kSBoxB);
    mSBoxC = BufSymbol(TwistWorkSpaceSlot::kSBoxC);
    
    mSaltA = BufSymbol(TwistWorkSpaceSlot::kSaltA);
    mSaltB = BufSymbol(TwistWorkSpaceSlot::kSaltB);
    
    mWorkLaneA = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
    mWorkLaneB = BufSymbol(TwistWorkSpaceSlot::kWorkLaneB);
}

bool GSimpleLoopExampleRecipe::Plan(std::string &pErrorString) {
    
    return true;
}


bool GSimpleLoopExampleRecipe::Bake(std::vector<GLoop> &pResult,
                                    bool pValueOrder[4],
                                    bool pValueSBoxReadUsesValueItself,
                                    bool pCarryOrder[4],
                                    bool pCarrySBoxReadUsesValueItself,
                                    std::string &pErrorString) {
    if ((pValueOrder == nullptr) || (pCarryOrder == nullptr)) {
        pErrorString = "Bake expected non-null ordering arrays.";
        return false;
    }

    const bool aValueConsumesSaltABeforeSBoxA = pValueOrder[0];
    const bool aValueConsumesWorkLaneABeforeSBoxA = pValueOrder[1];
    const bool aValueConsumesCarryBeforeValue = pValueOrder[2];

    const bool aCarryConsumesSaltBBeforeSBoxB = pCarryOrder[0];
    const bool aCarryConsumesWorkLaneBBeforeSBoxB = pCarryOrder[1];
    const bool aCarryConsumesSBoxCBeforeSBoxB = pCarryOrder[2];
    const bool aCarryConsumesValueBeforeSBoxB = pCarryOrder[3];

    pResult.clear();

    GLoop aLoop;
    aLoop.mLoopVariable = mLoopIndex;
    aLoop.mLoopVariableName = mLoopIndex.IsVar() ? mLoopIndex.mName : "aLoop";
    aLoop.mLoopBegin = 0;
    aLoop.mLoopEndText = "S_BLOCK";
    aLoop.mLoopStep = 1;

    auto AppendBodyStatement = [&](const GStatement &pStatement) -> bool {
        if (pStatement.IsInvalid()) {
            pErrorString = "Bake attempted to append an invalid loop statement.";
            return false;
        }
        aLoop.mBodyStatements.push_back(pStatement);
        return true;
    };

    if (!AppendBodyStatement(GStatement::Assign(GTarget::Symbol(mValue),
                                                GExpr::Read(mWorkLaneA, GExpr::Symbol(mLoopIndex))))) {
        return false;
    }
    if (!AppendBodyStatement(GStatement::Assign(GTarget::Symbol(mCarry),
                                                GExpr::Read(mWorkLaneB, GExpr::Symbol(mLoopIndex))))) {
        return false;
    }

    GLoopFragmentComposer aComposer;
    aComposer.SetLoopIndex(mLoopIndex);

    // Value pipeline.
    aComposer.Clear();
    aComposer.SetTarget(mValue);
    aComposer.SetLoopIndex(mLoopIndex);

    auto AddValueSaltMix = [&]() {
        aComposer.MixBuffer(mSaltA)
            .Base(mLoopIndex)
            .Domain(GLoopFragmentDomain::kSalt)
            .Offset()
            .Expand(75U, true);
    };
    auto AddValueWorkLaneMix = [&]() {
        aComposer.MixBuffer(mWorkLaneA)
            .Base(mLoopIndex)
            .Domain(GLoopFragmentDomain::kBlock)
            .Offset()
            .Expand(65U, true);
    };
    auto AddValueCarryMix = [&]() {
        aComposer.MixVariable(mCarry).Expand(50U, true);
    };

    if (aValueConsumesSaltABeforeSBoxA) { AddValueSaltMix(); }
    if (aValueConsumesWorkLaneABeforeSBoxA) { AddValueWorkLaneMix(); }
    if (aValueConsumesCarryBeforeValue) { AddValueCarryMix(); }

    GLoopFragmentComposerInputBuffer aValueTransform = aComposer.Transform(mSBoxA);
    aValueTransform.Domain(GLoopFragmentDomain::kSBox).Offset();
    if (pValueSBoxReadUsesValueItself) {
        aValueTransform.Base(mValue);
    } else {
        aValueTransform.Base(mCarry);
    }

    if (!aValueConsumesSaltABeforeSBoxA) { AddValueSaltMix(); }
    if (!aValueConsumesWorkLaneABeforeSBoxA) { AddValueWorkLaneMix(); }
    if (!aValueConsumesCarryBeforeValue) { AddValueCarryMix(); }

    if (!aComposer.BakeStatements(&aLoop.mBodyStatements, &pErrorString)) {
        return false;
    }

    // Carry pipeline.
    aComposer.Clear();
    aComposer.SetTarget(mCarry);
    aComposer.SetLoopIndex(mLoopIndex);

    auto AddCarrySaltMix = [&]() {
        aComposer.MixBuffer(mSaltB)
            .Base(mLoopIndex)
            .Domain(GLoopFragmentDomain::kSalt)
            .Offset()
            .Expand(65U, false);
    };
    auto AddCarryWorkLaneMix = [&]() {
        aComposer.MixBuffer(mWorkLaneB)
            .Base(mLoopIndex)
            .Domain(GLoopFragmentDomain::kBlock)
            .Offset()
            .Expand(65U, true);
    };
    auto AddCarrySBoxCMix = [&]() {
        aComposer.MixBuffer(mSBoxC)
            .Base(mLoopIndex)
            .Domain(GLoopFragmentDomain::kSBox)
            .Offset()
            .Expand(35U, false);
    };
    auto AddCarryValueMix = [&]() {
        aComposer.MixVariable(mValue).Expand(45U, true);
    };

    if (aCarryConsumesSaltBBeforeSBoxB) { AddCarrySaltMix(); }
    if (aCarryConsumesWorkLaneBBeforeSBoxB) { AddCarryWorkLaneMix(); }
    if (aCarryConsumesSBoxCBeforeSBoxB) { AddCarrySBoxCMix(); }
    if (aCarryConsumesValueBeforeSBoxB) { AddCarryValueMix(); }

    GLoopFragmentComposerInputBuffer aCarryTransform = aComposer.Transform(mSBoxB);
    aCarryTransform.Domain(GLoopFragmentDomain::kSBox).Offset();
    if (pCarrySBoxReadUsesValueItself) {
        aCarryTransform.Base(mCarry);
    } else {
        aCarryTransform.Base(mValue);
    }

    if (!aCarryConsumesSaltBBeforeSBoxB) { AddCarrySaltMix(); }
    if (!aCarryConsumesWorkLaneBBeforeSBoxB) { AddCarryWorkLaneMix(); }
    if (!aCarryConsumesSBoxCBeforeSBoxB) { AddCarrySBoxCMix(); }
    if (!aCarryConsumesValueBeforeSBoxB) { AddCarryValueMix(); }

    if (!aComposer.BakeStatements(&aLoop.mBodyStatements, &pErrorString)) {
        return false;
    }

    if (!AppendBodyStatement(GStatement::Assign(GTarget::Write(mWorkLaneA, GExpr::Symbol(mLoopIndex)),
                                                GExpr::Symbol(mValue)))) {
        return false;
    }
    if (!AppendBodyStatement(GStatement::Assign(GTarget::Write(mWorkLaneB, GExpr::Symbol(mLoopIndex)),
                                                GExpr::Symbol(mCarry)))) {
        return false;
    }

    pResult.push_back(aLoop);
    return true;
}
