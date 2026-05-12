//
//  GSeedMatrixRollups.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 4/29/26.
//

#include "GSeedMatrixRollups.hpp"
#include "Random.hpp"
#include "TwistCryptoGenerator.hpp"
#include "TwistArray.hpp"
#include <cstdio>
#include <cctype>
#include <cstdlib>

GSeedMatrixRollups::GSeedMatrixRollups() {
    Reset();
}

GSeedMatrixRollups::~GSeedMatrixRollups() {
    
}

void GSeedMatrixRollups::Reset() {
    
    mLoopIndex = VarSymbol("aIndex");
    mLoopIndexInverted = VarSymbol("aWalker");
    
    mPrism = VarSymbol("aPrism");
    mScatter = VarSymbol("aScatter");
    
    
    mCurrent = VarSymbol("aCurrent");
    mPrevious = VarSymbol("aPrevious");
 
    mArgA = VarSymbol("aArgA");
    mArgB = VarSymbol("aArgB");
    
    mKindA = VarSymbol("aKindA");
    mKindB = VarSymbol("aKindB");
    
    mSource = BufSymbol(TwistWorkSpaceSlot::kSource);
    
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
    
    mListKeys.clear();
    mListMasks.clear();
    mListKeys.push_back(BufSymbol(TwistWorkSpaceSlot::kKeyBoxUnrolledA));
    mListKeys.push_back(BufSymbol(TwistWorkSpaceSlot::kKeyBoxUnrolledB));
    
    mListMasks.clear();
    mListMasks.push_back(BufSymbol(TwistWorkSpaceSlot::kMaskBoxUnrolledA));
    mListMasks.push_back(BufSymbol(TwistWorkSpaceSlot::kMaskBoxUnrolledB));
    
    mListOperationLanes.clear();
    mListOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneA));
    mListOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneB));

}

bool GSeedMatrixRollups::Plan(std::string *pErrorMessage) {
    
    Reset();

    mCaseCount[0] = Random::Get(3, 4);
    
    
    for (int i=0; i<2; i++) {
        
        mCaseCount[i] = Random::Get(2, 4);
        
        for (int n=0; n<mCaseCount[i]; n++) {

            int aTotalOpCount = Random::Get(3, 5);
            int aFastOpCount = Random::Get(1, 2);
            aTotalOpCount -= aFastOpCount;
            
            int aMediumOpCount = Random::Get(1, 3);
            
            int aUndershoot = (aTotalOpCount) - (aFastOpCount + aMediumOpCount);
            if (aUndershoot < 0) {
                aMediumOpCount += aUndershoot;
            }
            
            int aSlowOpCount = (aTotalOpCount) - (aFastOpCount + aMediumOpCount);
            
            mFastOpCount[i][n] = aFastOpCount;
            mMediumOpCount[i][n] = aMediumOpCount;
            mSlowOpCount[i][n] = aSlowOpCount;
            
        }
    }
    
    GUnrollCache aUnrollCache;
    aUnrollCache.AddItem(TwistFastMatrixUnrollScheme::kA);
    aUnrollCache.AddItem(TwistFastMatrixUnrollScheme::kB);
    aUnrollCache.AddItem(TwistFastMatrixUnrollScheme::kC);
    aUnrollCache.AddItem(TwistFastMatrixUnrollScheme::kD);
    aUnrollCache.SetLimits(2, 3, 3);
    
    for (int i=0;i<2;i++) {
        int aCaseCount = mCaseCount[i];
        aUnrollCache.Fetch(aCaseCount * 2);
        for (int n=0; n<mCaseCount[i]; n++) {
            mUnrollSchemeA[i][n] = aUnrollCache.mBus[n * 2];
            mUnrollSchemeB[i][n] = aUnrollCache.mBus[n * 2 + 1];
        }
    }
    
    
    
    
    /*
    Random::Shuffle(&mListWorkers);
    Random::Shuffle(&mListExpansion);
    
    Random::Shuffle(&mListMasks);
    Random::Shuffle(&mListKeys);
    
    Random::Shuffle(&mListOperationLanes);
    
    
    for (int i=0; i<SEED_WORK_LANE_COUNT; i++) {
     
        mDestBuffer[i] = mListWorkers[i];
        if ((i & 1) == 0) {
            mDestReverse[i] = false;
        } else {
            mDestReverse[i] = true;
        }
    }
    */
    
    return true;
}

bool GSeedMatrixRollups::Build(TwistProgramBranch &pBranch,
                                      std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) { pErrorMessage->clear(); }

    GBatch aBatch;

    struct MatrixPairConfig {
        GSymbol mSourceA;
        GSymbol mSourceB;
        GSymbol mDestA;
        GSymbol mDestB;
        GSymbol mOperationLane;
        int mTemplateIndex;
        bool mSourceAInverted;
        bool mSourceBInverted;
    };

    auto BakeMatrixPair = [&](const MatrixPairConfig &pConfig,
                              const int pOperationBaseOffset) -> bool {
        if (pConfig.mTemplateIndex < 0 || pConfig.mTemplateIndex > 1) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "invalid template index for matrix pair";
            }
            return false;
        }

        GLoop aLoop;
        aLoop.mLoopVariable = mLoopIndex;
        aLoop.mLoopVariableName = mLoopIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 64;

        GStatement aWalkerStatement = GQuick::MakeAssignVariableStatement(
            mLoopIndexInverted,
            GExpr::Sub(GExpr::Const64(static_cast<std::uint64_t>(S_BLOCK - 64)),
                       GExpr::Symbol(mLoopIndex)));
        aLoop.AddBody(&aWalkerStatement);

        auto BuildCaseStatements = [&](const int pCaseIndex,
                                       std::vector<GStatement> *pCaseStatements) -> bool {
            if (pCaseStatements == nullptr) {
                return false;
            }
            pCaseStatements->clear();

            GFastMatrix aMatrixA(GFastMatrixType::kA);
            GFastMatrix aMatrixB(GFastMatrixType::kB);

            const GSymbol aLoadIndexA = pConfig.mSourceAInverted ? mLoopIndexInverted : mLoopIndex;
            const GSymbol aLoadIndexB = pConfig.mSourceBInverted ? mLoopIndexInverted : mLoopIndex;

            if (!aMatrixA.BakeLoad(pConfig.mSourceA, aLoadIndexA, pCaseStatements, pErrorMessage)) {
                return false;
            }
            if (!aMatrixB.BakeLoad(pConfig.mSourceB, aLoadIndexB, pCaseStatements, pErrorMessage)) {
                return false;
            }

            struct OpCountRoll {
                int mFast = 0;
                int mMedium = 0;
                int mSlow = 0;
            };

            auto RollOpCounts = [&]() -> OpCountRoll {
                OpCountRoll aResult;

                int aTotalOpCount = Random::Get(3, 5);
                int aFastOpCount = Random::Get(1, 2);
                int aMediumOpCount = Random::Get(1, 3);

                if ((aFastOpCount + aMediumOpCount) > aTotalOpCount) {
                    aMediumOpCount = aTotalOpCount - aFastOpCount;
                }
                if (aMediumOpCount < 0) {
                    aMediumOpCount = 0;
                }

                int aSlowOpCount = aTotalOpCount - (aFastOpCount + aMediumOpCount);
                if (aSlowOpCount < 0) {
                    aSlowOpCount = 0;
                }

                aResult.mFast = aFastOpCount;
                aResult.mMedium = aMediumOpCount;
                aResult.mSlow = aSlowOpCount;
                return aResult;
            };

            auto BuildOpsList = [&](const OpCountRoll &pCounts,
                                    std::vector<TwistFastMatrixOp> *pIgnoreList) -> std::vector<TwistFastMatrixOp> {
                std::vector<TwistFastMatrixOp> aFastOps =
                    GFastMatrix::GetRandomOpsFast(pCounts.mFast, *pIgnoreList);
                std::vector<TwistFastMatrixOp> aMediumOps =
                    GFastMatrix::GetRandomOpsMedium(pCounts.mMedium, *pIgnoreList);
                std::vector<TwistFastMatrixOp> aSlowOps =
                    GFastMatrix::GetRandomOpsSlow(pCounts.mSlow, *pIgnoreList);

                std::vector<TwistFastMatrixOp> aOpsList;
                TwistArray::Append(&aOpsList, &aFastOps);
                TwistArray::Append(&aOpsList, &aMediumOps);
                TwistArray::Append(&aOpsList, &aSlowOps);
                Random::Shuffle(&aOpsList);
                return aOpsList;
            };

            const OpCountRoll aCountsA = RollOpCounts();
            const OpCountRoll aCountsB = RollOpCounts();

            std::vector<TwistFastMatrixOp> aIgnoreListA;
            std::vector<TwistFastMatrixOp> aOpsListA = BuildOpsList(aCountsA, &aIgnoreListA);

            std::vector<TwistFastMatrixOp> aIgnoreListB = TwistFastMatrix::GetConflictingOps(aOpsListA);
            if (!aOpsListA.empty() && Random::Bool()) {
                // Allow at most one shared op between matrix A and matrix B.
                const TwistFastMatrixOp aSharedCandidate = aOpsListA[Random::Get(static_cast<int>(aOpsListA.size()))];
                aIgnoreListB.erase(
                    std::remove(aIgnoreListB.begin(), aIgnoreListB.end(), aSharedCandidate),
                    aIgnoreListB.end());
            }
            std::vector<TwistFastMatrixOp> aOpsListB = BuildOpsList(aCountsB, &aIgnoreListB);

            int aOperationOffset = pOperationBaseOffset + 1;
            auto QueueMatrixOps = [&](GFastMatrix *pMatrix,
                                      const std::vector<TwistFastMatrixOp> &pOpsList,
                                      const bool pUseArgBForSingleByte) {
                for (std::size_t aOpIndex = 0U; aOpIndex < pOpsList.size(); ++aOpIndex) {
                    const TwistFastMatrixOp aOp = pOpsList[aOpIndex];
                    const std::uint8_t aValueByteCount = TwistFastMatrix::OpValueByteCount(aOp);
                    if (aValueByteCount >= 2U) {
                        pMatrix->Perform(aOp,
                                         mArgA, pConfig.mOperationLane, mLoopIndex, aOperationOffset + 0,
                                         mArgB, pConfig.mOperationLane, mLoopIndex, aOperationOffset + 1);
                        aOperationOffset += 2;
                    } else if (aValueByteCount >= 1U) {
                        if (pUseArgBForSingleByte) {
                            pMatrix->Perform(aOp, mArgB, pConfig.mOperationLane, mLoopIndex, aOperationOffset);
                        } else {
                            pMatrix->Perform(aOp, mArgA, pConfig.mOperationLane, mLoopIndex, aOperationOffset);
                        }
                        aOperationOffset += 1;
                    } else {
                        pMatrix->Perform(aOp);
                    }
                }
            };

            // 1) load both matrices 2) all ops for A 3) store A 4) all ops for B 5) store B
            QueueMatrixOps(&aMatrixA, aOpsListA, false);
            if (!aMatrixA.BakePerform(pCaseStatements, pErrorMessage)) {
                return false;
            }

            const unsigned int aKindOffsetA = static_cast<unsigned int>(aOperationOffset);
            pCaseStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    mKindA,
                    GQuick::MakeReadBufferOffsetExpression(
                        pConfig.mOperationLane,
                        mLoopIndex,
                        aKindOffsetA)));
            aOperationOffset += 1;

            if (!aMatrixA.BakeUnroll(pConfig.mDestA,
                                     mLoopIndex,
                                     mUnrollSchemeA[pConfig.mTemplateIndex][pCaseIndex],
                                     mKindA,
                                     pCaseStatements,
                                     pErrorMessage)) {
                return false;
            }

            QueueMatrixOps(&aMatrixB, aOpsListB, true);
            if (!aMatrixB.BakePerform(pCaseStatements, pErrorMessage)) {
                return false;
            }

            const unsigned int aKindOffsetB = static_cast<unsigned int>(aOperationOffset);
            pCaseStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    mKindB,
                    GQuick::MakeReadBufferOffsetExpression(
                        pConfig.mOperationLane,
                        mLoopIndex,
                        aKindOffsetB)));
            aOperationOffset += 1;

            if (!aMatrixB.BakeUnroll(pConfig.mDestB,
                                     mLoopIndex,
                                     mUnrollSchemeB[pConfig.mTemplateIndex][pCaseIndex],
                                     mKindB,
                                     pCaseStatements,
                                     pErrorMessage)) {
                return false;
            }

            return true;
        };

        std::vector<GStatement> aCaseStatements[4];
        const int aCaseCount = mCaseCount[pConfig.mTemplateIndex];
        for (int aCaseIndex = 0; aCaseIndex < aCaseCount; ++aCaseIndex) {
            if (!BuildCaseStatements(aCaseIndex, &aCaseStatements[aCaseIndex])) {
                return false;
            }
        }

        GSelect aSelect = (aCaseCount <= 2) ? GSelect::Random2() : GSelect::Random4();
        if (aCaseCount >= 1) { aSelect.AddStatementsA(&aCaseStatements[0]); }
        if (aCaseCount >= 2) { aSelect.AddStatementsB(&aCaseStatements[1]); }
        if (aCaseCount >= 3) { aSelect.AddStatementsC(&aCaseStatements[2]); }
        if (aCaseCount >= 4) { aSelect.AddStatementsD(&aCaseStatements[3]); }

        std::vector<GStatement> aSelectStatements;
        if (!aSelect.Bake(mPrism,
                          GQuick::MakeReadBufferOffsetExpression(
                              pConfig.mOperationLane,
                              mLoopIndex,
                              static_cast<std::uint32_t>(pOperationBaseOffset)),
                          &aSelectStatements,
                          pErrorMessage)) {
            return false;
        }

        aLoop.AddBody(&aSelectStatements);
        aBatch.CommitLoop(&aLoop);
        return true;
    };

    auto BakePhase = [&](const char *pLabel,
                         const MatrixPairConfig &pLaneA,
                         const MatrixPairConfig &pLaneB,
                         const int pOperationBaseOffset) -> bool {
        aBatch.AddComment(std::string("phase: ") + pLabel);
        if (!BakeMatrixPair(pLaneA, pOperationBaseOffset)) { return false; }
        if (!BakeMatrixPair(pLaneB, pOperationBaseOffset)) { return false; }
        return true;
    };

    auto SelectPhaseOpLanes = [&]() -> std::pair<GSymbol, GSymbol> {
        if (Random::Bool()) {
            return std::make_pair(mListOperationLanes[0], mListOperationLanes[1]);
        }
        return std::make_pair(mListOperationLanes[1], mListOperationLanes[0]);
    };

    auto MakeMatrixPairConfigDirect = [&](GSymbol pSourceA,
                                          GSymbol pSourceB,
                                          GSymbol pDestA,
                                          GSymbol pDestB,
                                          const GSymbol pOperationLane,
                                          const int pTemplateIndex) -> MatrixPairConfig {
        return MatrixPairConfig {
            pSourceA,
            pSourceB,
            pDestA,
            pDestB,
            pOperationLane,
            pTemplateIndex,
            Random::Bool(),
            Random::Bool()
        };
    };

    // pass 1
    {
        const auto aOpLanes = SelectPhaseOpLanes();
        const MatrixPairConfig aLaneA = MakeMatrixPairConfigDirect(
            mListWorkers[0], mListWorkers[1],
            mListExpansion[0], mListExpansion[1],
            aOpLanes.first,
            0);
        const MatrixPairConfig aLaneB = MakeMatrixPairConfigDirect(
            mListWorkers[2], mListWorkers[3],
            mListExpansion[2], mListExpansion[3],
            aOpLanes.second,
            1);
        if (!BakePhase("workers -> expansion [offset 0]", aLaneA, aLaneB, 0)) {
            return false;
        }
    }

    // pass 2
    {
        const auto aOpLanes = SelectPhaseOpLanes();
        const MatrixPairConfig aLaneA = MakeMatrixPairConfigDirect(
            mListExpansion[0], mListExpansion[2],
            mListWorkers[1], mListWorkers[3],
            aOpLanes.first,
            0);
        const MatrixPairConfig aLaneB = MakeMatrixPairConfigDirect(
            mListExpansion[1], mListExpansion[3],
            mListWorkers[0], mListWorkers[2],
            aOpLanes.second,
            1);
        if (!BakePhase("expansion -> workers [offset 20]", aLaneA, aLaneB, 20)) {
            return false;
        }
    }

    // pass 3
    {
        const auto aOpLanes = SelectPhaseOpLanes();
        const MatrixPairConfig aLaneA = MakeMatrixPairConfigDirect(
            mListWorkers[0], mListWorkers[3],
            mListExpansion[0], mListExpansion[2],
            aOpLanes.first,
            0);
        const MatrixPairConfig aLaneB = MakeMatrixPairConfigDirect(
            mListWorkers[1], mListWorkers[2],
            mListExpansion[1], mListExpansion[3],
            aOpLanes.second,
            1);
        if (!BakePhase("workers -> expansion [offset 40]", aLaneA, aLaneB, 40)) {
            return false;
        }
    }

    pBranch.AddBatch(aBatch);
    return true;
}
