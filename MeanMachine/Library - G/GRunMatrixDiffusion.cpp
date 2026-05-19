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

    const GSymbol aIndexListA = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256A));
    const GSymbol aIndexListB = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256B));
    const GSymbol aIndexListC = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256C));
    const GSymbol aIndexListD = BufSymbol(TwistBufferKey::Direct(TwistDirectBuffer::kIndexList256D));

    const GSymbol aLoopIndex = VarSymbol("aMatrixDiffusionIndex");
    const GSymbol aSelect = pConfig.mSelect.IsVar() ? pConfig.mSelect : VarSymbol("aMatrixDiffusionSelect");
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
    const GSymbol aKindA = VarSymbol("aMatrixKindA");
    const GSymbol aKindB = VarSymbol("aMatrixKindB");

    std::vector<GStatement> aStatements;
    if (!GIndexShuffle::BakeExecute256(aIndexListA, pConfig.mShuffleEntropyA, &aStatements, pErrorMessage)) {
        return false;
    }
    if (!GIndexShuffle::BakeExecute256(aIndexListB, pConfig.mShuffleEntropyB, &aStatements, pErrorMessage)) {
        return false;
    }
    if (!GIndexShuffle::BakeExecute256(aIndexListC, pConfig.mShuffleEntropyC, &aStatements, pErrorMessage)) {
        return false;
    }
    if (!GIndexShuffle::BakeExecute256(aIndexListD, pConfig.mShuffleEntropyD, &aStatements, pErrorMessage)) {
        return false;
    }
    aStatements.push_back(GQuick::MakeAssignVariableStatement(aOperationIndex, GExpr::Const64(0ULL)));
    aStatements.push_back(GQuick::MakeAssignVariableStatement(aWriteIndex, GExpr::Const64(0ULL)));
    pBatch->CommitStatements(&aStatements);

    auto BakeSingleLoop = [&](const GSymbol pIndexListLeft,
                              const GSymbol pIndexListRight,
                              const GSymbol pOutputBuffer,
                              const GSymbol pOperationSource,
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

        auto BakeCase = [&](std::vector<GStatement> *pCaseStatements,
                            const TwistFastMatrixOp pOpA1,
                            const TwistFastMatrixOp pOpA2,
                            const TwistFastMatrixOp pOpB1,
                            const TwistFastMatrixOp pOpB2) -> bool {
            if (pCaseStatements == nullptr) {
                SetError(pErrorMessage, "GRunMatrixDiffusion null case statement output.");
                return false;
            }

            GFastMatrix aMatrixA(GFastMatrixType::kA);
            GFastMatrix aMatrixB(GFastMatrixType::kB);

            aMatrixA.Perform(pOpA1);
            aMatrixA.Perform(pOpA2,
                             aMatrixArgA, pOperationSource, aOperationIndex, 1,
                             aMatrixArgB, pOperationSource, aOperationIndex, 2);
            aMatrixB.Perform(pOpB1);
            aMatrixB.Perform(pOpB2,
                             aMatrixArgC, pOperationSource, aOperationIndex, 3,
                             aMatrixArgD, pOperationSource, aOperationIndex, 4);

            if (!aMatrixA.BakePerform(pCaseStatements, pErrorMessage)) {
                return false;
            }
            if (!aMatrixB.BakePerform(pCaseStatements, pErrorMessage)) {
                return false;
            }

            pCaseStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    aKindA,
                    GQuick::MakeReadBufferOffsetExpression(pOperationSource, aOperationIndex, 5U)));
            pCaseStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    aKindB,
                    GQuick::MakeReadBufferOffsetExpression(pOperationSource, aOperationIndex, 6U)));

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
                                     TwistFastMatrixUnrollScheme::kA,
                                     aKindA,
                                     pCaseStatements,
                                     pErrorMessage)) {
                return false;
            }
            if (!aMatrixB.BakeUnroll(pOutputBuffer,
                                     aStoreIndexB,
                                     TwistFastMatrixUnrollScheme::kC,
                                     aKindB,
                                     pCaseStatements,
                                     pErrorMessage)) {
                return false;
            }

            pCaseStatements->push_back(GQuick::AddEqual64(aOperationIndex, 7ULL));
            pCaseStatements->push_back(GQuick::AddEqual64(aWriteIndex, 128ULL));
            return true;
        };

        if (!BakeCase(&aCaseStatementsA,
                      TwistFastMatrixOp::kRotateLeft,
                      TwistFastMatrixOp::kSwapRows,
                      TwistFastMatrixOp::kRotateLeft,
                      TwistFastMatrixOp::kSwapRows)) {
            return false;
        }
        if (!BakeCase(&aCaseStatementsB,
                      TwistFastMatrixOp::kRotateLeft,
                      TwistFastMatrixOp::kSwapCols,
                      TwistFastMatrixOp::kRotateRight,
                      TwistFastMatrixOp::kSwapColsOdd)) {
            return false;
        }
        if (!BakeCase(&aCaseStatementsC,
                      TwistFastMatrixOp::kTransposeMainDiagonal,
                      TwistFastMatrixOp::kSwapRowsEven,
                      TwistFastMatrixOp::kFlipVertical,
                      TwistFastMatrixOp::kSwapRowsOdd)) {
            return false;
        }

        GSelect aSelectPlan = GSelect::Random4();
        aSelectPlan.AddStatementsA(&aCaseStatementsA);
        aSelectPlan.AddStatementsB(&aCaseStatementsB);
        aSelectPlan.AddStatementsC(&aCaseStatementsC);

        std::vector<GStatement> aSelectStatements;
        if (!aSelectPlan.Bake(aSelect,
                              GQuick::MakeReadBufferOffsetExpression(pOperationSource, aOperationIndex, 0U),
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

    return BakeSingleLoop(aIndexListC,
                          aIndexListD,
                          pConfig.mOutputB,
                          pConfig.mOperationSourceB,
                          64,
                          0,
                          64,
                          0);
}
