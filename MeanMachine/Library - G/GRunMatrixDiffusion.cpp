//
//  GRunMatrixDiffusion.cpp
//  MeanMachine
//
//  Created by Dragon on 5/15/26.
//

#include "GRunMatrixDiffusion.hpp"
#include "GIndexShuffle.hpp"
#include "GQuick.hpp"
#include "GSelect.hpp"
#include "TwistArray.hpp"
#include "Random.hpp"


namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

bool EnsureBufferSymbol(const GSymbol &pSymbol,
                        const char *pLabel,
                        std::string *pErrorMessage) {
    if (pSymbol.IsBuf()) {
        return true;
    }
    SetError(pErrorMessage, std::string("GRunMatrixDiffusion expected buffer symbol for ") + pLabel + ".");
    return false;
}

static std::vector<TwistFastMatrixOp> FlattenDualDiffuseChannel(
    const GFastMatrixDualDiffuseOperationChannel &pChannel
) {
    std::vector<TwistFastMatrixOp> aResult;

    TwistArray::Append(&aResult, &pChannel.mFastList);
    TwistArray::Append(&aResult, &pChannel.mMediumList);
    TwistArray::Append(&aResult, &pChannel.mSlowList);

    Random::Shuffle(&aResult);
    return aResult;
}

} // namespace

bool GRunMatrixDiffusion::Bake(const GRunMatrixDiffusionConfig &pConfig,
                               GBatch *pBatch,
                               std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    if (pBatch == nullptr) {
        SetError(pErrorMessage, "GRunMatrixDiffusion requires a batch output.");
        return false;
    }
    
    if (!EnsureBufferSymbol(pConfig.mInputA, "input_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mInputB, "input_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOutputA, "output_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOutputB, "output_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyA, "shuffle_entropy_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyB, "shuffle_entropy_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyC, "shuffle_entropy_c", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyD, "shuffle_entropy_d", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOperationSourceA, "operation_source_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOperationSourceB, "operation_source_b", pErrorMessage)) { return false; }
    
    const GSymbol aIndexListA = BufSymbol(TwistWorkSpaceSlot::kIndexList256A);
    const GSymbol aIndexListB = BufSymbol(TwistWorkSpaceSlot::kIndexList256B);
    const GSymbol aIndexListC = BufSymbol(TwistWorkSpaceSlot::kIndexList256C);
    const GSymbol aIndexListD = BufSymbol(TwistWorkSpaceSlot::kIndexList256D);
    
    const GSymbol aLoopIndex = VarSymbol("aMatrixDiffusionIndex");
    const GSymbol aSelect = GSymbol::Var(TwistVariable::kSelect);
    const GSymbol aOperationIndex = VarSymbol("aMatrixOperationIndex");
    const GSymbol aWriteIndex = VarSymbol("aMatrixWriteIndex");
    const GSymbol aSlotA = VarSymbol("aMatrixSlotA");
    const GSymbol aSlotB = VarSymbol("aMatrixSlotB");
    const GSymbol aLoadIndexA = VarSymbol("aMatrixLoadIndexA");
    const GSymbol aLoadIndexB = VarSymbol("aMatrixLoadIndexB");
    const GSymbol aStoreIndexA = VarSymbol("aMatrixStoreIndexA");
    const GSymbol aStoreIndexB = VarSymbol("aMatrixStoreIndexB");
    const GSymbol aMatrixArgA = VarSymbol("aMatrixArgA");
    const GSymbol aMatrixArgB = VarSymbol("aMatrixArgB");
    const GSymbol aMatrixArgC = VarSymbol("aMatrixArgC");
    const GSymbol aMatrixArgD = VarSymbol("aMatrixArgD");
    
    const GSymbol aUnrollWordA = VarSymbol("aMatrixUnrollWordA");
    const GSymbol aUnrollWordB = VarSymbol("aMatrixUnrollWordB");
    
    
    GFastMatrixDualDiffuseOperationPack aOpPack;
    GFastMatrix::GetDualDiffuseOps(&aOpPack);
    
    /*
    std::vector<TwistFastMatrixOp> aCaseOpsA = FlattenDualDiffuseChannel(aOpPack.mChannelA_1);
    std::vector<TwistFastMatrixOp> aCaseOpsB = FlattenDualDiffuseChannel(aOpPack.mChannelA_2);
    std::vector<TwistFastMatrixOp> aCaseOpsC = FlattenDualDiffuseChannel(aOpPack.mChannelA_3);
    std::vector<TwistFastMatrixOp> aCaseOpsD = FlattenDualDiffuseChannel(aOpPack.mChannelA_4);
    
    std::vector<TwistFastMatrixOp> aCaseOpsE = FlattenDualDiffuseChannel(aOpPack.mChannelB_1);
    std::vector<TwistFastMatrixOp> aCaseOpsF = FlattenDualDiffuseChannel(aOpPack.mChannelB_2);
    std::vector<TwistFastMatrixOp> aCaseOpsG = FlattenDualDiffuseChannel(aOpPack.mChannelB_3);
    std::vector<TwistFastMatrixOp> aCaseOpsH = FlattenDualDiffuseChannel(aOpPack.mChannelB_4);
    */
    
    
    std::vector<GStatement> aStatements;
    if (!GIndexShuffle::BakeA(aIndexListA, pConfig.mShuffleEntropyA, &aStatements, pErrorMessage)) {
        return false;
    }
    if (!GIndexShuffle::BakeB(aIndexListB, pConfig.mShuffleEntropyB, &aStatements, pErrorMessage)) {
        return false;
    }
    if (!GIndexShuffle::BakeA(aIndexListC, pConfig.mShuffleEntropyC, &aStatements, pErrorMessage)) {
        return false;
    }
    if (!GIndexShuffle::BakeB(aIndexListD, pConfig.mShuffleEntropyD, &aStatements, pErrorMessage)) {
        return false;
    }
    aStatements.push_back(GQuick::MakeAssignVariableStatement(aOperationIndex, GExpr::Const64(0ULL)));
    aStatements.push_back(GQuick::MakeAssignVariableStatement(aWriteIndex, GExpr::Const64(0ULL)));
    pBatch->CommitStatements(&aStatements);
    
    
    auto XorOperationByteWithDomain =
    [&](const GSymbol &pOperationSource,
        const GSymbol &pOperationIndex,
        const std::uint32_t pOffset,
        const TwistVariable pDomainVariable) -> GExpr {
        return GExpr::Xor(
                          GQuick::MakeReadBufferOffsetExpression(pOperationSource,
                                                                 pOperationIndex,
                                                                 pOffset),
                          GExpr::Symbol(GSymbol::Var(pDomainVariable))
                          );
    };
    
    auto BakeSingleLoop = [&](const GSymbol pIndexListLeft,
                              const GSymbol pIndexListRight,
                              const GSymbol pOutputBuffer,
                              const GSymbol pOperationSource,
                              const TwistVariable pSelectDomainVariable,
                              const bool pUseChannelB,
                              const int pInputOffsetA,
                              const int pInputOffsetB,
                              const int pOutputOffsetA,
                              const int pOutputOffsetB) -> bool {
        
        GLoop aLoop;
        aLoop.mLoopVariable = aLoopIndex;
        aLoop.mLoopVariableName = aLoopIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "256";
        aLoop.mLoopStep = 1;
        
        aLoop.AddBody(GQuick::MakeAssignVariableStatement(
                                                          aSlotA,
                                                          GQuick::MakeReadBufferOffsetExpression(pIndexListLeft, aLoopIndex, 0U)));
        aLoop.AddBody(GQuick::MakeAssignVariableStatement(
                                                          aSlotB,
                                                          GQuick::MakeReadBufferOffsetExpression(pIndexListRight, aLoopIndex, 0U)));
        
        aLoop.AddBody(GQuick::MakeAssignVariableStatement(
                                                          aLoadIndexA,
                                                          GExpr::Add(
                                                                     GExpr::Mul(GExpr::Symbol(aSlotA), GExpr::Const64(128ULL)),
                                                                     GExpr::Const64(static_cast<std::uint64_t>(pInputOffsetA)))));
        aLoop.AddBody(GQuick::MakeAssignVariableStatement(
                                                          aLoadIndexB,
                                                          GExpr::Add(
                                                                     GExpr::Mul(GExpr::Symbol(aSlotB), GExpr::Const64(128ULL)),
                                                                     GExpr::Const64(static_cast<std::uint64_t>(pInputOffsetB)))));
        
        std::vector<GStatement> aSharedStatements;
        GFastMatrix aLoadA(GFastMatrixType::kA);
        GFastMatrix aLoadB(GFastMatrixType::kB);
        if (!aLoadA.BakeLoad(pConfig.mInputA, aLoadIndexA, &aSharedStatements, pErrorMessage)) {
            return false;
        }
        if (!aLoadB.BakeLoad(pConfig.mInputB, aLoadIndexB, &aSharedStatements, pErrorMessage)) {
            return false;
        }
        aLoop.AddBody(&aSharedStatements);
        
        std::vector<GStatement> aCaseStatementsA;
        std::vector<GStatement> aCaseStatementsB;
        std::vector<GStatement> aCaseStatementsC;
        std::vector<GStatement> aCaseStatementsD;
        
        auto BakeCase = [&](std::vector<GStatement> *pCaseStatements,
                            const GFastMatrixDualDiffuseOperationChannel &pChannel) -> bool {
            if (pCaseStatements == nullptr) {
                SetError(pErrorMessage, "GRunMatrixDiffusion null case statement output.");
                return false;
            }
            
            std::vector<TwistFastMatrixOp> aOps = FlattenDualDiffuseChannel(pChannel);

            if (aOps.empty()) {
                SetError(pErrorMessage, "GRunMatrixDiffusion expected at least one matrix op per case.");
                return false;
            }

            GFastMatrix aMatrixA(GFastMatrixType::kA);
            GFastMatrix aMatrixB(GFastMatrixType::kB);

            for (std::size_t aIndex = 0U; aIndex < aOps.size(); aIndex++) {
                const TwistFastMatrixOp aOp = aOps[aIndex];

                if ((aIndex & 1U) == 0U) {
                    aMatrixA.Perform(aOp,
                                     aMatrixArgA, pOperationSource, aOperationIndex, 1U,
                                     aMatrixArgB, pOperationSource, aOperationIndex, 2U);
                } else {
                    aMatrixB.Perform(aOp,
                                     aMatrixArgC, pOperationSource, aOperationIndex, 3U,
                                     aMatrixArgD, pOperationSource, aOperationIndex, 4U);
                }
            }

            if (!aMatrixA.BakePerform(pCaseStatements,
                                      GSymbol::Var(TwistVariable::kDomainWordMatrixArgA),
                                      GSymbol::Var(TwistVariable::kDomainWordMatrixArgB),
                                      GSymbol::Var(TwistVariable::kDomainWordMatrixArgC),
                                      GSymbol::Var(TwistVariable::kDomainWordMatrixArgD),
                                      pErrorMessage)) {
                return false;
            }

            if (!aMatrixB.BakePerform(pCaseStatements,
                                      GSymbol::Var(TwistVariable::kDomainWordMatrixArgA),
                                      GSymbol::Var(TwistVariable::kDomainWordMatrixArgB),
                                      GSymbol::Var(TwistVariable::kDomainWordMatrixArgC),
                                      GSymbol::Var(TwistVariable::kDomainWordMatrixArgD),
                                      pErrorMessage)) {
                return false;
            }
            
            pCaseStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    aUnrollWordA,
                    XorOperationByteWithDomain(pOperationSource,
                                               aOperationIndex,
                                               5U,
                                               TwistVariable::kDomainWordMatrixUnrollA)));

            pCaseStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    aUnrollWordB,
                    XorOperationByteWithDomain(pOperationSource,
                                               aOperationIndex,
                                               6U,
                                               TwistVariable::kDomainWordMatrixUnrollB)));
            
            pCaseStatements->push_back(
                                       GQuick::MakeAssignVariableStatement(
                                                                           aStoreIndexA,
                                                                           GExpr::Add(GExpr::Symbol(aWriteIndex),
                                                                                      GExpr::Const64(static_cast<std::uint64_t>(pOutputOffsetA)))));
            pCaseStatements->push_back(
                                       GQuick::MakeAssignVariableStatement(
                                                                           aStoreIndexB,
                                                                           GExpr::Add(GExpr::Symbol(aWriteIndex),
                                                                                      GExpr::Const64(static_cast<std::uint64_t>(pOutputOffsetB)))));
            
            if (!aMatrixA.BakeUnroll(pOutputBuffer,
                                     aStoreIndexA,
                                     pChannel.mUnrollSchemeA,
                                     aUnrollWordA,
                                     pCaseStatements,
                                     pErrorMessage)) {
                return false;
            }
            
            if (!aMatrixB.BakeUnroll(pOutputBuffer,
                                     aStoreIndexB,
                                     pChannel.mUnrollSchemeB,
                                     aUnrollWordB,
                                     pCaseStatements,
                                     pErrorMessage)) {
                return false;
            }
            
            pCaseStatements->push_back(GQuick::AddEqual64(aOperationIndex, 7ULL));
            pCaseStatements->push_back(GQuick::AddEqual64(aWriteIndex, 128ULL));
            return true;
        };
        
        std::vector<TwistFastMatrixOp> aIgnoreListA;
        std::vector<TwistFastMatrixOp> aOpsListA = GFastMatrix::GetRandomOpsFast(2, aIgnoreListA);
        
        
        const GFastMatrixDualDiffuseOperationChannel &aSelectedChannelA =
            pUseChannelB ? aOpPack.mChannelB_1 : aOpPack.mChannelA_1;

        const GFastMatrixDualDiffuseOperationChannel &aSelectedChannelB =
            pUseChannelB ? aOpPack.mChannelB_2 : aOpPack.mChannelA_2;

        const GFastMatrixDualDiffuseOperationChannel &aSelectedChannelC =
            pUseChannelB ? aOpPack.mChannelB_3 : aOpPack.mChannelA_3;

        const GFastMatrixDualDiffuseOperationChannel &aSelectedChannelD =
            pUseChannelB ? aOpPack.mChannelB_4 : aOpPack.mChannelA_4;

        BakeCase(&aCaseStatementsA, aSelectedChannelA);
        BakeCase(&aCaseStatementsB, aSelectedChannelB);
        BakeCase(&aCaseStatementsC, aSelectedChannelC);
        BakeCase(&aCaseStatementsD, aSelectedChannelD);
        
        aLoop.AddBody(
            GQuick::MakeAssignVariableStatement(
                aSelect,
                XorOperationByteWithDomain(pOperationSource,
                                           aOperationIndex,
                                           0U,
                                           pSelectDomainVariable)));
        
        GSelect aSelectPlan = GSelect::Random4();
        aSelectPlan.AddStatementsA(&aCaseStatementsA);
        aSelectPlan.AddStatementsB(&aCaseStatementsB);
        aSelectPlan.AddStatementsC(&aCaseStatementsC);
        aSelectPlan.AddStatementsD(&aCaseStatementsD);
        
        std::vector<GStatement> aSelectStatements;
        if (!aSelectPlan.Bake(aSelect,
                              &aSelectStatements,
                              pErrorMessage)) {
            return false;
        }
        aLoop.AddBody(&aSelectStatements);
        
        pBatch->CommitLoop(&aLoop);
        return true;
    };
    
    if (!BakeSingleLoop(aIndexListA,
                        aIndexListB,
                        pConfig.mOutputA,
                        pConfig.mOperationSourceA,
                        TwistVariable::kDomainWordMatrixSelectA,
                        false,
                        0,
                        64,
                        0,
                        64)) {
        return false;
    }
    
    aStatements.clear();
    aStatements.push_back(GQuick::MakeAssignVariableStatement(aOperationIndex, GExpr::Const64(0ULL)));
    aStatements.push_back(GQuick::MakeAssignVariableStatement(aWriteIndex, GExpr::Const64(0ULL)));
    pBatch->CommitStatements(&aStatements);
    
    if (!BakeSingleLoop(aIndexListC,
                        aIndexListD,
                        pConfig.mOutputB,
                        pConfig.mOperationSourceB,
                        TwistVariable::kDomainWordMatrixSelectB,
                        true,
                        64,
                        0,
                        64,
                        0)) {
        return false;
    }
    
    return true;
}
