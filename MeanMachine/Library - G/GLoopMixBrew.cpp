//
//  GLoopMixBrew.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 4/29/26.
//

#include "GLoopMixBrew.hpp"
#include "Random.hpp"
#include "TwistFunctional.hpp"

GLoopFragmentComposerInput GLoopMixBrew::BuildComposerInputForNode(const GLoopMixBrewNode &pNode) const {
    GLoopFragmentComposerInput aInput = pNode.mInput;
    if (aInput.mType == GLoopFragmentComposerInputType::kBuffer) {
        aInput.mInputBuffer.Combine(pNode.mOp);
    } else if (aInput.mType == GLoopFragmentComposerInputType::kVariable) {
        aInput.mInputVariable.Combine(pNode.mOp);
    }
    return aInput;
}

GLoopFragmentComposerInputVariable &GLoopMixBrew::PutVariable(GSymbol pSymbol,
                                                               bool pBefore,
                                                              GLoopFragmentComposerCombineOp pOp) {
    GLoopMixBrewNode aNode;
    aNode.mBefore = pBefore;
    aNode.mOp = pOp;
    GLoopFragmentComposerInputVariable aInput(pSymbol, pOp);
    aNode.mInput = aInput.ToInput();
    mNodes.push_back(aNode);
    return mNodes.back().mInput.mInputVariable;
}

GLoopFragmentComposerInputBuffer &GLoopMixBrew::PutBuffer(GSymbol pSymbol,
                                                           bool pBefore,
                                                          GLoopFragmentComposerCombineOp pOp) {
    GLoopMixBrewNode aNode;
    aNode.mBefore = pBefore;
    aNode.mOp = pOp;
    GLoopFragmentComposerInputBuffer aInput(pSymbol, pOp);
    aNode.mInput = aInput.ToInput();
    mNodes.push_back(aNode);
    return mNodes.back().mInput.mInputBuffer;
}

GLoopFragmentComposerInputVariable &GLoopMixBrew::PutVariableAdd(GSymbol pSymbol, bool pBefore) {
    return PutVariable(pSymbol, pBefore, GLoopFragmentComposerCombineOp::kAdd);
}

GLoopFragmentComposerInputVariable &GLoopMixBrew::PutVariableMul(GSymbol pSymbol, bool pBefore) {
    return PutVariable(pSymbol, pBefore, GLoopFragmentComposerCombineOp::kMul);
}

GLoopFragmentComposerInputVariable &GLoopMixBrew::PutVariableXor(GSymbol pSymbol, bool pBefore) {
    return PutVariable(pSymbol, pBefore, GLoopFragmentComposerCombineOp::kXor);
}

GLoopFragmentComposerInputVariable &GLoopMixBrew::PutVariableRandom(GSymbol pSymbol, bool pBefore) {
    if (Random::Bool()) {
        return PutVariableAdd(pSymbol, pBefore);
    }
    return PutVariableXor(pSymbol, pBefore);
}

GLoopFragmentComposerInputBuffer &GLoopMixBrew::PutBufferAdd(GSymbol pSymbol, bool pBefore) {
    return PutBuffer(pSymbol, pBefore, GLoopFragmentComposerCombineOp::kAdd);
}

GLoopFragmentComposerInputBuffer &GLoopMixBrew::PutBufferMul(GSymbol pSymbol, bool pBefore) {
    return PutBuffer(pSymbol, pBefore, GLoopFragmentComposerCombineOp::kMul);
}

GLoopFragmentComposerInputBuffer &GLoopMixBrew::PutBufferXor(GSymbol pSymbol, bool pBefore) {
    return PutBuffer(pSymbol, pBefore, GLoopFragmentComposerCombineOp::kXor);
}

GLoopFragmentComposerInputBuffer &GLoopMixBrew::PutBufferRandom(GSymbol pSymbol, bool pBefore) {
    if (Random::Bool()) {
        return PutBufferXor(pSymbol, pBefore);
    }
    return PutBufferAdd(pSymbol, pBefore);
}

GLoopMixBrew::GLoopMixBrew() {
    mRandomOrderEnabled = true;
}

bool GLoopMixBrew::IsValidSBox(GSymbol pSymbol) {
    if (pSymbol.mType != GSymbolType::kBuf) {
        return false;
    }
    if (TwistWorkSpace::IsSBox(pSymbol.mSlot) == false) {
        return false;
    }
    return true;
}

void GLoopMixBrew::SetLoopIndex(GSymbol pLoopIndex) {
    mLoopIndex = pLoopIndex;
}

void GLoopMixBrew::SetTarget(GSymbol pTarget, GSymbol pTargetMix) {
    mTarget = pTarget;
    mTargetMix = pTargetMix;
}

void GLoopMixBrew::SetRandomOrderEnabled(bool pState) {
    mRandomOrderEnabled = pState;
}

namespace {
bool Mix64Type1NeedsAmount(const Mix64Type_1 pType) {
    switch (pType) {
        case Mix64Type_1::kGatePrism_1_8:
            return false;
        case Mix64Type_1::kGateRoll_1_1:
        case Mix64Type_1::kGateRoll_1_4:
        case Mix64Type_1::kGateRoll_1_8:
        case Mix64Type_1::kGateTurn_1_1:
        case Mix64Type_1::kGateTurn_1_4:
        case Mix64Type_1::kGateTurn_1_8:
            return true;
        default:
            return false;
    }
}

bool Mix64Type4NeedsAmount(const Mix64Type_4 pType) {
    switch (pType) {
        case Mix64Type_4::kGatePrismA_4_8:
        case Mix64Type_4::kGatePrismB_4_8:
        case Mix64Type_4::kGatePrismC_4_8:
            return false;
        case Mix64Type_4::kGateRoll_4_4:
        case Mix64Type_4::kGateRollA_4_8:
        case Mix64Type_4::kGateRollB_4_8:
        case Mix64Type_4::kGateRollC_4_8:
        case Mix64Type_4::kGateTurn_4_4:
        case Mix64Type_4::kGateTurnA_4_8:
        case Mix64Type_4::kGateTurnB_4_8:
        case Mix64Type_4::kGateTurnC_4_8:
            return true;
        default:
            return false;
    }
}

bool Mix64Type8NeedsAmount(const Mix64Type_8 pType) {
    switch (pType) {
        case Mix64Type_8::kGatePrism_8_8:
            return false;
        case Mix64Type_8::kGateRoll_8_8:
        case Mix64Type_8::kGateTurn_8_8:
            return true;
        default:
            return false;
    }
}
} // namespace


void GLoopMixBrew::SetMix_8_Random(GSymbol pSBoxA,
                                   GSymbol pSBoxB,
                                   GSymbol pSBoxC,
                                   GSymbol pSBoxD,
                                   GSymbol pSBoxE,
                                   GSymbol pSBoxF,
                                   GSymbol pSBoxG,
                                   GSymbol pSBoxH) {
    std::vector<Mix64Type_8> aOptions = TwistMix64::GetAll_8();
    Mix64Type_8 aChosenType = Mix64Type_8::kInv;
    if (!aOptions.empty()) {
        aChosenType = Random::Choice(aOptions);
    }
    if (Mix64Type8NeedsAmount(aChosenType)) {
        const std::vector<std::uint64_t> aRotates = {3U, 5U, 7U, 11U};
        SetMix_8(aChosenType, Random::Choice(aRotates), pSBoxA, pSBoxB, pSBoxC, pSBoxD, pSBoxE, pSBoxF, pSBoxG, pSBoxH);
    } else {
        SetMix_8(aChosenType, pSBoxA, pSBoxB, pSBoxC, pSBoxD, pSBoxE, pSBoxF, pSBoxG, pSBoxH);
    }
}

void GLoopMixBrew::SetMix_8(Mix64Type_8 pMixType,
                            GSymbol pSBoxA,
                            GSymbol pSBoxB,
                            GSymbol pSBoxC,
                            GSymbol pSBoxD,
                            GSymbol pSBoxE,
                            GSymbol pSBoxF,
                            GSymbol pSBoxG,
                            GSymbol pSBoxH) {
    mMix64Family = Mix64Family::k8;
    mMix64Type8 = pMixType;
    mMix64UseAmount = false;
    mMix64Amount = 0U;
    mMixSBoxA = pSBoxA;
    mMixSBoxB = pSBoxB;
    mMixSBoxC = pSBoxC;
    mMixSBoxD = pSBoxD;
    mMixSBoxE = pSBoxE;
    mMixSBoxF = pSBoxF;
    mMixSBoxG = pSBoxG;
    mMixSBoxH = pSBoxH;
}

void GLoopMixBrew::SetMix_8(Mix64Type_8 pMixType,
                            std::uint64_t pAmount,
                            GSymbol pSBoxA,
                            GSymbol pSBoxB,
                            GSymbol pSBoxC,
                            GSymbol pSBoxD,
                            GSymbol pSBoxE,
                            GSymbol pSBoxF,
                            GSymbol pSBoxG,
                            GSymbol pSBoxH) {
    SetMix_8(pMixType, pSBoxA, pSBoxB, pSBoxC, pSBoxD, pSBoxE, pSBoxF, pSBoxG, pSBoxH);
    mMix64UseAmount = true;
    mMix64Amount = pAmount;
}

GExpr GLoopMixBrew::BuildMixExpr(const GExpr &pInput) const {
    if (mMix64Family == Mix64Family::k8) {
        if (mMix64UseAmount) {
            return GExpr::Mix64_8(pInput, mMix64Type8, mMix64Amount, mMixSBoxA, mMixSBoxB, mMixSBoxC, mMixSBoxD, mMixSBoxE, mMixSBoxF, mMixSBoxG, mMixSBoxH);
        }
        return GExpr::Mix64_8(pInput, mMix64Type8, mMixSBoxA, mMixSBoxB, mMixSBoxC, mMixSBoxD, mMixSBoxE, mMixSBoxF, mMixSBoxG, mMixSBoxH);
    }
    return GExpr();
}

bool GLoopMixBrew::Bake(std::vector<GStatement> *pStatements,
                                                 std::string *pErrorMessage) {
    return Bake(TargetCombineMode::kSet,
                TargetCombineMode::kXor,
                pStatements,
                pErrorMessage);
}

bool GLoopMixBrew::Bake(TargetCombineMode pCombineModeBefore,
                        TargetCombineMode pCombineModeAfter,
                        std::vector<GStatement> *pStatements,
                        std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GLoopMixBrew.Error: Statement list is NULL, how could you allow that?";
        }
        return false;
    }
    
    switch (pCombineModeBefore) {
        case TargetCombineMode::kSet:
        case TargetCombineMode::kAdd:
        case TargetCombineMode::kXor:
            break;
        default:
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GLoopMixBrew.Error: Assignment (before) type must be set, add assign, or xor assign.";
            }
            return false;
    }
    
    switch (pCombineModeAfter) {
        case TargetCombineMode::kAdd:
        case TargetCombineMode::kXor:
            break;
        default:
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GLoopMixBrew.Error: Assignment (after) type must be add assign, or xor assign.";
            }
            return false;
    }
    
    if (mTarget.IsInvalid()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GLoopMixBrew.Error: Target is invalid. Did you call SetTarget(...)?";
        }
        return false;
    }
    
    if (mMix64Family == Mix64Family::k8) {
        if (mMix64Type8 == Mix64Type_8::kInv) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GLoopMixBrew.Error: Mix family is k8, but mix type is invalid.";
            }
            return false;
        }
        if (!IsValidSBox(mMixSBoxA) || !IsValidSBox(mMixSBoxB) || !IsValidSBox(mMixSBoxC) || !IsValidSBox(mMixSBoxD) ||
            !IsValidSBox(mMixSBoxE) || !IsValidSBox(mMixSBoxF) || !IsValidSBox(mMixSBoxG) || !IsValidSBox(mMixSBoxH)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GLoopMixBrew.Error: Mix family is k8, but one or more s-box symbols are not valid.";
            }
            return false;
        }
        if (Mix64Type8NeedsAmount(mMix64Type8) && !mMix64UseAmount) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GLoopMixBrew.Error: Mix family is k8, selected type requires an amount.";
            }
            return false;
        }
    } else {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GLoopMixBrew.Error: Mix is invalid. Did you call SetMix_1(...), SetMix_4(...), SetMix_8(...), or random variants?";
        }
        return false;
    }
    
    std::vector<GLoopMixBrewNode> aBeforeList;
    std::vector<GLoopMixBrewNode> aAfterList;
    
    for (const GLoopMixBrewNode &aNode : mNodes) {
        if (aNode.mBefore) {
            aBeforeList.push_back(aNode);
            
        } else {
            aAfterList.push_back(aNode);
        }
    }
    
    if (mRandomOrderEnabled == true) {
        Random::Shuffle(&aBeforeList);
        Random::Shuffle(&aAfterList);
    }
    
    
    if (aBeforeList.size() <= 0) {
        const GExpr aMixExpr = BuildMixExpr(GExpr::Symbol(mTarget));
        if (pCombineModeBefore == TargetCombineMode::kAdd) {
            pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget),
                                                      GExpr::Add(GExpr::Symbol(mTarget), aMixExpr)));
        } else if (pCombineModeBefore == TargetCombineMode::kXor) {
            pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget),
                                                      GExpr::Xor(GExpr::Symbol(mTarget), aMixExpr)));
        } else {
            pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget), aMixExpr));
        }
    } else {
        if (aBeforeList.size() == 1) {
            GLoopFragmentComposer aComposer(mLoopIndex);
            auto aInput = BuildComposerInputForNode(aBeforeList[0]);
            if (!aComposer.AddInput(aInput)) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GLoopMixBrew.Error: Failed to add single before input.";
                }
                return false;
            }
            
            GExpr aExpression;
            
            if (!aComposer.ResolveToStatementsAndExpression(pStatements,
                                                            aExpression,
                                                            pErrorMessage)) {
                return false;
            }
            
            const GExpr aMixExpr = BuildMixExpr(aExpression);
            if (pCombineModeBefore == TargetCombineMode::kAdd) {
                pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget),
                                                          GExpr::Add(GExpr::Symbol(mTarget), aMixExpr)));
            } else if (pCombineModeBefore == TargetCombineMode::kXor) {
                pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget),
                                                          GExpr::Xor(GExpr::Symbol(mTarget), aMixExpr)));
            } else {
                pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget), aMixExpr));
            }
            
        } else {
            GLoopFragmentComposer aComposer(mLoopIndex);
            aComposer.SetTarget(mTargetMix);
            
            for (auto &aItem: aBeforeList) {
                auto aInput = BuildComposerInputForNode(aItem);
                if (!aComposer.AddInput(aInput)) {
                    if (pErrorMessage != nullptr) {
                        *pErrorMessage = "GLoopMixBrew.Error: Failed to add before composer input.";
                    }
                    return false;
                }
            }
            
            if (!aComposer.Bake(pStatements,
                                          pErrorMessage)) {
                return false;
            }
            
            if (aAfterList.size() > 0) {
                
            } else {
                
            }
            
            const GExpr aMixExpr = BuildMixExpr(GExpr::Symbol(mTargetMix));
            if (pCombineModeBefore == TargetCombineMode::kAdd) {
                pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget),
                                                          GExpr::Add(GExpr::Symbol(mTarget), aMixExpr)));
            } else if (pCombineModeBefore == TargetCombineMode::kXor) {
                pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget),
                                                          GExpr::Xor(GExpr::Symbol(mTarget), aMixExpr)));
            } else {
                pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget), aMixExpr));
            }
        }
    }
    
    if (aAfterList.size() > 0) {
        GLoopFragmentComposer aComposer(mLoopIndex);
        for (auto &aItem: aAfterList) {
            auto aInput = BuildComposerInputForNode(aItem);
            if (!aComposer.AddInput(aInput)) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "GLoopMixBrew.Error: Failed to add after composer input.";
                }
                return false;
            }
        }
        
        GExpr aAfterExpression;
        if (!aComposer.ResolveToStatementsAndExpression(pStatements,
                                                        aAfterExpression,
                                                        pErrorMessage)) {
            return false;
        }
        
        if (pCombineModeAfter == TargetCombineMode::kAdd) {
            pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget),
                                                      GExpr::Add(GExpr::Symbol(mTarget), aAfterExpression)));
        } else {
            pStatements->push_back(GStatement::Assign(GTarget::Symbol(mTarget),
                                                      GExpr::Xor(GExpr::Symbol(mTarget), aAfterExpression)));
        }
        
    }
    
    return true;
    
}
