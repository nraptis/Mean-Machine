//
//  GRunMatrixDiffusion.cpp
//  MeanMachine
//
//  Created by Dragon on 5/15/26.
//

#include "GRunMatrixDiffusion.hpp"
#include "GIndexShuffle.hpp"
#include "GM88.hpp"
#include "GQuick.hpp"


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

}

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
    
    if (!EnsureBufferSymbol(pConfig.mOperationSourceA, "operation_source_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOperationSourceB, "operation_source_b", pErrorMessage)) { return false; }
    
    const GSymbol aIndexListA = BufSymbol(TwistWorkSpaceSlot::kIndexList256A);
    const GSymbol aIndexListB = BufSymbol(TwistWorkSpaceSlot::kIndexList256B);
    const GSymbol aIndexListC = BufSymbol(TwistWorkSpaceSlot::kIndexList256C);
    const GSymbol aIndexListD = BufSymbol(TwistWorkSpaceSlot::kIndexList256D);
    
    const GSymbol aLoopIndex = VarSymbol("aMatrixDiffusionIndex");
    const GSymbol aWriteIndex = VarSymbol("aMatrixWriteIndex");
    const GSymbol aSlotA = VarSymbol("aMatrixSlotA");
    const GSymbol aSlotB = VarSymbol("aMatrixSlotB");
    const GSymbol aLoadIndexA = VarSymbol("aMatrixLoadIndexA");
    const GSymbol aLoadIndexB = VarSymbol("aMatrixLoadIndexB");
    
    
    std::vector<GStatement> aStatements;
    if (!GIndexShuffle::BakeA(aIndexListA, pConfig.mShuffleEntropyA, &aStatements, pErrorMessage)) {
        return false;
    }
    if (!GIndexShuffle::BakeA(aIndexListB, pConfig.mShuffleEntropyB, &aStatements, pErrorMessage)) {
        return false;
    }
    if (!GIndexShuffle::BakeB(aIndexListC, pConfig.mShuffleEntropyA, &aStatements, pErrorMessage)) {
        return false;
    }
    if (!GIndexShuffle::BakeB(aIndexListD, pConfig.mShuffleEntropyB, &aStatements, pErrorMessage)) {
        return false;
    }
    aStatements.push_back(GQuick::MakeAssignVariableStatement(aWriteIndex, GExpr::Const64(0ULL)));
    pBatch->CommitStatements(&aStatements);
    
    auto BakeSingleLoop = [&](const GSymbol pIndexListLeft,
                              const GSymbol pIndexListRight,
                              const GSymbol pOutputBuffer,
                              const GSymbol pOperationSource,
                              const GSymbol pUnrollDomainWord,
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
        GM88 aMatrix;
        const GExpr aDispatchIndexA = GExpr::Add(GExpr::Symbol(aWriteIndex),
                                                 GExpr::Const64(static_cast<std::uint64_t>(pOutputOffsetA)));
        const GExpr aDispatchIndexB = GExpr::Add(GExpr::Symbol(aWriteIndex),
                                                 GExpr::Const64(static_cast<std::uint64_t>(pOutputOffsetB)));
        const GExpr aArgDomainWordA = GExpr::Symbol(GSymbol::Var(TwistVariable::kDomainWordMatrixArgA));
        const GExpr aArgDomainWordB = GExpr::Symbol(GSymbol::Var(TwistVariable::kDomainWordMatrixArgB));
        const GExpr aArgDomainWordC = GExpr::Symbol(GSymbol::Var(TwistVariable::kDomainWordMatrixArgC));
        const GExpr aArgDomainWordD = GExpr::Symbol(GSymbol::Var(TwistVariable::kDomainWordMatrixArgD));
        if (!aMatrix.BakeDispatch(pOperationSource,
                                  aDispatchIndexA,
                                  pConfig.mInputA,
                                  GExpr::Symbol(aLoadIndexA),
                                  pOutputBuffer,
                                  aDispatchIndexA,
                                  GExpr::Symbol(pUnrollDomainWord),
                                  aArgDomainWordA,
                                  aArgDomainWordB,
                                  aArgDomainWordC,
                                  aArgDomainWordD,
                                  &aSharedStatements,
                                  pErrorMessage)) {
            return false;
        }

        if (!aMatrix.BakeDispatch(pOperationSource,
                                  aDispatchIndexB,
                                  pConfig.mInputB,
                                  GExpr::Symbol(aLoadIndexB),
                                  pOutputBuffer,
                                  aDispatchIndexB,
                                  GExpr::Symbol(pUnrollDomainWord),
                                  aArgDomainWordA,
                                  aArgDomainWordB,
                                  aArgDomainWordC,
                                  aArgDomainWordD,
                                  &aSharedStatements,
                                  pErrorMessage)) {
            return false;
        }

        aSharedStatements.push_back(GQuick::AddEqual64(aWriteIndex, 128ULL));
        aLoop.AddBody(&aSharedStatements);
        pBatch->CommitLoop(&aLoop);
        return true;
    };
    
    if (!BakeSingleLoop(aIndexListA,
                        aIndexListB,
                        pConfig.mOutputA,
                        pConfig.mOperationSourceA,
                        GSymbol::Var(TwistVariable::kDomainWordMatrixUnrollA),
                        0,
                        64,
                        0,
                        64)) {
        return false;
    }
    
    aStatements.clear();
    aStatements.push_back(GQuick::MakeAssignVariableStatement(aWriteIndex, GExpr::Const64(0ULL)));
    pBatch->CommitStatements(&aStatements);
    
    if (!BakeSingleLoop(aIndexListC,
                        aIndexListD,
                        pConfig.mOutputB,
                        pConfig.mOperationSourceB,
                        GSymbol::Var(TwistVariable::kDomainWordMatrixUnrollB),
                        64,
                        0,
                        64,
                        0)) {
        return false;
    }
    return true;
}
