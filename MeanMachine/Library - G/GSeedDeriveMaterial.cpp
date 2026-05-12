//
//  GSeedDeriveMaterial.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 4/29/26.
//

#include "GSeedDeriveMaterial.hpp"
#include "Random.hpp"
#include "TwistCryptoGenerator.hpp"
#include "TwistArray.hpp"
#include <cstdio>
#include <cctype>
#include <cstdlib>

GSeedDeriveMaterial::GSeedDeriveMaterial() {
    Reset();
}

GSeedDeriveMaterial::~GSeedDeriveMaterial() {
    
}

void GSeedDeriveMaterial::Reset() {
    
    mLoopIndex = VarSymbol("aIndex");
    
    mPrism = VarSymbol("aPrism");
    mScatter = VarSymbol("aScatter");
    
    mCurrent = VarSymbol("aCurrent");
    mPrevious = VarSymbol("aPrevious");
    mCarry = VarSymbol("aCarry");
    mStreamCross = VarSymbol("aCross");
    
    mWandererA = VarSymbol("aWandererA");
    mWandererB = VarSymbol("aWandererB");
    mWandererC = VarSymbol("aWandererC");
    mWandererD = VarSymbol("aWandererD");
    
    mOrbitA = VarSymbol("aOrbitA");
    mOrbitB = VarSymbol("aOrbitB");
    mOrbitC = VarSymbol("aOrbitC");
    mOrbitD = VarSymbol("aOrbitD");
    
    mPlugKeyA = VarSymbol("aPlugKeyA");
    mPlugKeyB = VarSymbol("aPlugKeyB");
    
    
    mSource = BufSymbol(TwistWorkSpaceSlot::kSource);
    
    std::vector<GHotPack> aHotPacks = GMagicNumbers::GetHotPacks(4);
    
    if ((aHotPacks.size() > 0)) { mHotPacks[0] = aHotPacks[0]; }
    if ((aHotPacks.size() > 1)) { mHotPacks[1] = aHotPacks[1]; }
    if ((aHotPacks.size() > 2)) { mHotPacks[2] = aHotPacks[2]; }
    if ((aHotPacks.size() > 3)) { mHotPacks[3] = aHotPacks[3]; }
    
    mListSBoxes.clear();
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxA));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxB));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxC));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxD));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxE));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxF));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxG));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxH));

    mListSalts.clear();
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltA));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltB));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltC));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltD));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltE));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltF));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltG));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltH));
    
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
    
    mListOperationLanes.clear();
    mListOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneA));
    mListOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneB));
    
    
    mSnowType[0] = GSnowType::kAES;
    mSnowType[1] = GSnowType::kChaCha;
    mSnowType[2] = GSnowType::kSha;
    mSnowType[3] = GSnowType::kAria;
    
    for (int i = 3; i > 0; --i) {
        const int j = Random::Get(i + 1); // 0...i
        std::swap(mSnowType[i], mSnowType[j]);
    }
    
    for (int i=0; i<SEED_WORK_LANE_COUNT; i++) {
        mDestBuffer[i].Invalidate();
        mDestReverse[i] = false;
        mChunkGlobalRecipeSalt[i].Invalidate();
        mRecipeSaltA[i][0].Invalidate();
        mRecipeSaltA[i][1].Invalidate();
        mRecipeSaltB[i][0].Invalidate();
        mRecipeSaltB[i][1].Invalidate();
    }
}

bool GSeedDeriveMaterial::Plan(std::string *pErrorMessage) {
    
    Reset();
    
    //Random::Shuffle(&mListWorkers);
    
    
    // Random::Shuffle(&mListSalts);
    
    
    
    for (int i = 0; i < SEED_WORK_LANE_COUNT; i++) {
        // One globally unique held-out salt per chunk.
        mChunkGlobalRecipeSalt[i] = mListSalts[i];

        std::vector<GSymbol> aChunkRecipeSalts;
        aChunkRecipeSalts.push_back(mChunkGlobalRecipeSalt[i]);

        // Each chunk uses exactly 4 held-out recipe salts.
        while (aChunkRecipeSalts.size() < 4U) {
            GSymbol aSalt = Random::Choice(mListSalts);
            bool aAlreadyInChunk = false;

            for (std::size_t aIndex = 0U; aIndex < aChunkRecipeSalts.size(); ++aIndex) {
                if (aChunkRecipeSalts[aIndex] == aSalt) {
                    aAlreadyInChunk = true;
                    break;
                }
            }

            if (!aAlreadyInChunk) {
                aChunkRecipeSalts.push_back(aSalt);
            }
        }

        // Build loop pairs: 2 recipe salts per loop.
        // One loop gets the chunk-global salt as one of its two taps.
        GSymbol aGlobalPartner = aChunkRecipeSalts[1];
        GSymbol aPairX = aChunkRecipeSalts[2];
        GSymbol aPairY = aChunkRecipeSalts[3];

        const bool aGlobalOnFirstLoop = Random::Bool();
        if (aGlobalOnFirstLoop) {
            mRecipeSaltA[i][0] = mChunkGlobalRecipeSalt[i];
            mRecipeSaltB[i][0] = aGlobalPartner;
            mRecipeSaltA[i][1] = aPairX;
            mRecipeSaltB[i][1] = aPairY;
        } else {
            mRecipeSaltA[i][0] = aPairX;
            mRecipeSaltB[i][0] = aPairY;
            mRecipeSaltA[i][1] = mChunkGlobalRecipeSalt[i];
            mRecipeSaltB[i][1] = aGlobalPartner;
        }

        if (Random::Bool()) {
            std::swap(mRecipeSaltA[i][0], mRecipeSaltB[i][0]);
        }
        if (Random::Bool()) {
            std::swap(mRecipeSaltA[i][1], mRecipeSaltB[i][1]);
        }

        // Plug salts are exactly the remaining salts (8 total - 4 held out = 4 plugs).
        mPlugSalts[i].clear();
        for (std::size_t aSaltIndex = 0U; aSaltIndex < mListSalts.size(); ++aSaltIndex) {
            const GSymbol aSalt = mListSalts[aSaltIndex];
            bool aHeldOut = false;
            for (std::size_t aRecipeIndex = 0U; aRecipeIndex < aChunkRecipeSalts.size(); ++aRecipeIndex) {
                if (aChunkRecipeSalts[aRecipeIndex] == aSalt) {
                    aHeldOut = true;
                    break;
                }
            }

            if (!aHeldOut) {
                mPlugSalts[i].push_back(aSalt);
            }
        }
        Random::Shuffle(&mPlugSalts[i]);
    }
    
    for (int i=0; i<SEED_WORK_LANE_COUNT; i++) {

        bool aAccepted = false;
        for (int aTry=0; aTry<10000; aTry++) {

            mOrderedSBoxes[i].clear();
            TwistArray::Append(&mOrderedSBoxes[i], &mListSBoxes);
            Random::Shuffle(&mOrderedSBoxes[i]);

            bool aGood = true;

            for (int j=0; j<i; j++) {
                int aCollisions = 0;

                const int aSize = static_cast<int>(
                    std::min(mOrderedSBoxes[i].size(), mOrderedSBoxes[j].size())
                );

                for (int k=0; k<aSize; k++) {
                    if (mOrderedSBoxes[i][k] == mOrderedSBoxes[j][k]) {
                        aCollisions++;

                        if (aCollisions > 2) {
                            aGood = false;
                            break;
                        }
                    }
                }

                if (!aGood) {
                    break;
                }
            }

            if (aGood) {
                printf("s-box success after %d loops\n", aTry);
                aAccepted = true;
                break;
            }
        }

        if (!aAccepted) {
            printf("Failed to find low-collision S-box order for lane %d\n", i);
        } else {
            
        }
    }
    
    for (int i=0; i<SEED_WORK_LANE_COUNT; i++) {
        mDestBuffer[i] = mListWorkers[i];
        if ((i & 1) == 0) {
            mDestReverse[i] = false;
        } else {
            mDestReverse[i] = true;
        }
    }
    
    return true;
}

bool GSeedDeriveMaterial::Build(TwistProgramBranch &pBranch,
                                      std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) { pErrorMessage->clear(); }
    
    GBatch aBatch;
    std::vector<GStatement> aStatements;
    GStatement aStatement;
    GMemory aMemory;
    const GSymbol aReloop = VarSymbol("aReloop");
    const std::uint64_t kFarmTargets[SEED_WORK_LANE_COUNT] = {16ULL, 32ULL, 48ULL, 64ULL};

    aBatch.AddComment("Reset farm state for this seed pass.");
    aStatements.push_back(GStatement::RawLine("pFarmSBox->Reset();"));
    aStatements.push_back(GStatement::RawLine("pFarmSalt->Reset();"));
    aBatch.CommitStatements(&aStatements);

    auto AppendLaneLoop = [&](GWhile *pWhile,
                              const int pLaneIndex,
                              const int pLoopInChunk,
                              const GSymbol pInput,
                              const GSymbol pStreamCrossSource,
                              const GSymbol pSnowLane,
                              const GSymbol pDest,
                              const bool pDestWriteInverted,
                              const bool pSnowReadInverted,
                              const bool pInputReadInverted,
                              const bool pStreamCrossReadInverted) -> bool {
        GLoop aLoop;
        aLoop.mLoopVariable = mLoopIndex;
        aLoop.mLoopVariableName = mLoopIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 1;

        std::vector<GSymbol> aWanderers;
        aWanderers.push_back(mWandererA);
        aWanderers.push_back(mWandererB);
        aWanderers.push_back(mWandererC);
        aWanderers.push_back(mWandererD);
        Random::Shuffle(&aWanderers);

        std::vector<GSymbol> aOrbiters;
        aOrbiters.push_back(mOrbitA);
        aOrbiters.push_back(mOrbitB);
        aOrbiters.push_back(mOrbitC);
        aOrbiters.push_back(mOrbitD);
        Random::Shuffle(&aOrbiters);

        aStatement = GQuick::MakeAssignVariableStatement(mPrevious, mCurrent);
        aLoop.AddBody(&aStatement);

        GExpr aPrimaryByte;
        if (pInputReadInverted) {
            aPrimaryByte = GQuick::MakeReadBufferReadExpressionInverted(pInput, mLoopIndex);
        } else {
            aPrimaryByte = GQuick::MakeReadBufferReadExpression(pInput, mLoopIndex);
        }

        GExpr aSnowByte;
        if (pSnowReadInverted) {
            aSnowByte = GQuick::MakeReadBufferReadExpressionInverted(pSnowLane, mLoopIndex);
        } else {
            aSnowByte = GQuick::MakeReadBufferReadExpression(pSnowLane, mLoopIndex);
        }

        GExpr aCrossExpr;
        if (pStreamCrossReadInverted) {
            aCrossExpr = GQuick::MakeReadBufferReadExpressionInverted(pStreamCrossSource, mLoopIndex);
        } else {
            aCrossExpr = GQuick::MakeReadBufferReadExpression(pStreamCrossSource, mLoopIndex);
        }

        const GExpr aStreamByteExpr = GExpr::Xor(aPrimaryByte, GExpr::ShiftL(aSnowByte, GExpr::Const64(32ULL)));
        aStatement = GQuick::MakeAssignVariableStatement(mCurrent, aStreamByteExpr);
        aLoop.AddBody(&aStatement);

        aStatement = GQuick::MakeAssignVariableStatement(mStreamCross, aCrossExpr);
        aLoop.AddBody(&aStatement);

        std::vector<Mix64Type_8> aMixTypes8;
        aMixTypes8.push_back(Mix64Type_8::kGateRoll_8_8);
        aMixTypes8.push_back(Mix64Type_8::kGateTurn_8_8);
        aMixTypes8.push_back(Mix64Type_8::kGatePrism_8_8);

        std::vector<int> aRotationsLow = GRotationFamily::GetListLow();
        std::vector<int> aRotationsMedium = GRotationFamily::GetListMedium();
        std::vector<int> aRotationsHigh = GRotationFamily::GetListHigh();
        std::vector<int> aRotationsRandom = GRotationFamily::GetListAll();

        aLoop.AddBodyComment("__START_CSPRNG");
        if (!CSPRNG::Bake(pDest,
                          pDestWriteInverted,
                          mLoopIndex,
                          mCurrent,
                          mPrevious,
                          mPrism,
                          false,
                          mScatter,
                          mStreamCross,
                          mCarry,
                          aWanderers[0],
                          aWanderers[1],
                          aWanderers[2],
                          aOrbiters[0],
                          aOrbiters[1],
                          aOrbiters[2],
                          aOrbiters[3],
                          mRecipeSaltA[pLaneIndex][pLoopInChunk],
                          mRecipeSaltB[pLaneIndex][pLoopInChunk],
                          mOrderedSBoxes[pLaneIndex],
                          mPlugSalts[pLaneIndex],
                          aRotationsLow,
                          aRotationsMedium,
                          aRotationsHigh,
                          aRotationsRandom,
                          aMixTypes8,
                          mHotPacks[pLaneIndex],
                          &aStatements,
                          pErrorMessage)) {
            std::printf("CSPRNG::Bake failed: %s\n", (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "");
            return false;
        }
        aLoop.AddBody(&aStatements);
        aLoop.AddBodyComment("__END_CSPRNG");

        pWhile->CommitLoop(&aLoop);
        return true;
    };

    auto AppendOperationLaneLoop = [&](const int pPairIndex,
                                       const GSymbol pWorkerA,
                                       const GSymbol pWorkerB,
                                       const bool pReadInverted,
                                       const GSymbol pDest) -> bool {
        const int aConfigLane = (pPairIndex * 2);
        const int aRecipeLoopInChunk = pPairIndex;

        GLoop aLoop;
        aLoop.mLoopVariable = mLoopIndex;
        aLoop.mLoopVariableName = mLoopIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 1;

        std::vector<GSymbol> aWanderers;
        aWanderers.push_back(mWandererA);
        aWanderers.push_back(mWandererB);
        aWanderers.push_back(mWandererC);
        aWanderers.push_back(mWandererD);
        Random::Shuffle(&aWanderers);

        std::vector<GSymbol> aOrbiters;
        aOrbiters.push_back(mOrbitA);
        aOrbiters.push_back(mOrbitB);
        aOrbiters.push_back(mOrbitC);
        aOrbiters.push_back(mOrbitD);
        Random::Shuffle(&aOrbiters);

        aStatement = GQuick::MakeAssignVariableStatement(mPrevious, mCurrent);
        aLoop.AddBody(&aStatement);

        const GExpr aSourceByte = pReadInverted ?
            GQuick::MakeReadBufferReadExpressionInverted(mSource, mLoopIndex) :
            GQuick::MakeReadBufferReadExpression(mSource, mLoopIndex);
        const GExpr aWorkerAByte = pReadInverted ?
            GQuick::MakeReadBufferReadExpressionInverted(pWorkerA, mLoopIndex) :
            GQuick::MakeReadBufferReadExpression(pWorkerA, mLoopIndex);
        const GExpr aWorkerBByte = pReadInverted ?
            GQuick::MakeReadBufferReadExpressionInverted(pWorkerB, mLoopIndex) :
            GQuick::MakeReadBufferReadExpression(pWorkerB, mLoopIndex);
        const GExpr aPackedExpr = GExpr::Or(
            GExpr::ShiftL(aSourceByte, GExpr::Const64(16ULL)),
            GExpr::Or(
                GExpr::ShiftL(aWorkerAByte, GExpr::Const64(8ULL)),
                aWorkerBByte
            )
        );
        const GExpr aCrossPackedExpr = GExpr::Or(
            GExpr::ShiftL(aWorkerAByte, GExpr::Const64(8ULL)),
            aWorkerBByte
        );

        aStatement = GQuick::MakeAssignVariableStatement(mCurrent, aPackedExpr);
        aLoop.AddBody(&aStatement);

        // Cross feed for operation lanes excludes source.
        aStatement = GQuick::MakeAssignVariableStatement(mStreamCross, aCrossPackedExpr);
        aLoop.AddBody(&aStatement);

        std::vector<Mix64Type_8> aMixTypes8;
        aMixTypes8.push_back(Mix64Type_8::kGateRoll_8_8);
        aMixTypes8.push_back(Mix64Type_8::kGateTurn_8_8);
        aMixTypes8.push_back(Mix64Type_8::kGatePrism_8_8);

        std::vector<int> aRotationsLow = GRotationFamily::GetListLow();
        std::vector<int> aRotationsMedium = GRotationFamily::GetListMedium();
        std::vector<int> aRotationsHigh = GRotationFamily::GetListHigh();
        std::vector<int> aRotationsRandom = GRotationFamily::GetListAll();

        if (!CSPRNG::Bake(pDest,
                          false,
                          mLoopIndex,
                          mCurrent,
                          mPrevious,
                          mPrism,
                          true,
                          mScatter,
                          mStreamCross,
                          mCarry,
                          aWanderers[0],
                          aWanderers[1],
                          aWanderers[2],
                          aOrbiters[0],
                          aOrbiters[1],
                          aOrbiters[2],
                          aOrbiters[3],
                          mRecipeSaltA[aConfigLane][aRecipeLoopInChunk],
                          mRecipeSaltB[aConfigLane][aRecipeLoopInChunk],
                          mOrderedSBoxes[aConfigLane],
                          mPlugSalts[aConfigLane],
                          aRotationsLow,
                          aRotationsMedium,
                          aRotationsHigh,
                          aRotationsRandom,
                          aMixTypes8,
                          mHotPacks[aConfigLane],
                          &aStatements,
                          pErrorMessage)) {
            std::printf("CSPRNG::Bake operation lane failed: %s\n", (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "");
            return false;
        }
        aLoop.AddBody(&aStatements);
        aBatch.CommitLoop(&aLoop);
        return true;
    };

    for (int i = 0; i < SEED_WORK_LANE_COUNT; i++) {
        const GSymbol aSnowLane = mListExpansion[i];
        const GSymbol aScratchLane = mListExpansion[(i + 1) % SEED_WORK_LANE_COUNT];
        const GSymbol aWorkerLane = mDestBuffer[i];
        const GSymbol aWorkerSeed = (i == 0) ? mSource : mDestBuffer[i - 1];

        GSnow aSnow;
        switch (mSnowType[i]) {
            case GSnowType::kAES:
                aBatch.AddComment("Making snow counter: aes 256");
                break;
            case GSnowType::kChaCha:
                aBatch.AddComment("Making snow counter: cha cha 20");
                break;
            case GSnowType::kSha:
                aBatch.AddComment("Making snow counter: sha 256");
                break;
            case GSnowType::kAria:
                aBatch.AddComment("Making snow counter: aria 256");
                break;
            default:
                std::printf("bad snow type\n");
                return false;
        }

        if (!aSnow.Bake(mSnowType[i], mSource, aSnowLane, &aStatements, pErrorMessage)) {
            std::printf("snow bake failed: %s\n", (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "");
            return false;
        }
        aBatch.CommitStatements(&aStatements);

        aBatch.AddComment("Initialize worker lane for this pass.");
        if (!aMemory.BakeCopy(aWorkerLane, aWorkerSeed, &aStatements, pErrorMessage)) {
            std::printf("memory copy failed: %s\n", (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "");
            return false;
        }
        aBatch.CommitStatements(&aStatements);

        aStatements.push_back(GStatement::Assign(GTarget::Symbol(aReloop), GExpr::Const64(1ULL)));
        aBatch.CommitStatements(&aStatements);

        GWhile aWhile;
        aWhile.SetCondition(aReloop);

        if (!AppendLaneLoop(&aWhile,
                            i,
                            0,
                            aWorkerLane,
                            aWorkerLane,
                            aSnowLane,
                            aScratchLane,
                            false,
                            ((i & 1) == 0),
                            false,
                            true)) {
            return false;
        }

        {
            const std::string aFarmSBoxLine =
                aReloop.mName + " = pFarmSBox->TillBytes(" +
                BufAliasName(aScratchLane.mSlot) + ", " +
                BufAliasName(aSnowLane.mSlot) + ", " +
                std::to_string(static_cast<unsigned long long>(kFarmTargets[i])) +
                "ULL) ? 0ULL : 1ULL;";
            aStatements.push_back(GStatement::RawLine(aFarmSBoxLine));
            aWhile.CommitStatements(&aStatements);
        }

        if (!AppendLaneLoop(&aWhile,
                            i,
                            1,
                            aScratchLane,
                            aWorkerLane,
                            aSnowLane,
                            aWorkerLane,
                            mDestReverse[i],
                            ((i & 1) != 0),
                            false,
                            false)) {
            return false;
        }
        
        {
            const std::string aFarmSaltLine =
                aReloop.mName + " = pFarmSalt->TillBytes(" +
                BufAliasName(aWorkerLane.mSlot) + ", " +
                BufAliasName(aSnowLane.mSlot) + ", " +
                std::to_string(static_cast<unsigned long long>(kFarmTargets[i])) +
                "ULL) ? " + aReloop.mName + " : 1ULL;";
            aStatements.push_back(GStatement::RawLine(aFarmSaltLine));
            aWhile.CommitStatements(&aStatements);
        }

        aBatch.CommitWhile(&aWhile);

        aBatch.AddComment("Secure zero on snow + scratch expansion lanes.");
        if (!aMemory.BakeZero(aSnowLane, &aStatements, pErrorMessage)) {
            std::printf("BakeZero snow lane failed: %s\n", (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "");
            return false;
        }
        if (!aMemory.BakeZero(aScratchLane, &aStatements, pErrorMessage)) {
            std::printf("BakeZero scratch lane failed: %s\n", (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "");
            return false;
        }
        aBatch.CommitStatements(&aStatements);
    }

    aBatch.AddComment("Generate operation lanes from source + worker pairs.");
    const int aInvertedOperationPass = Random::Get(2);
    if (!AppendOperationLaneLoop(0,
                                 mDestBuffer[0],
                                 mDestBuffer[1],
                                 (aInvertedOperationPass == 0),
                                 mListOperationLanes[0])) {
        return false;
    }
    if (!AppendOperationLaneLoop(1,
                                 mDestBuffer[2],
                                 mDestBuffer[3],
                                 (aInvertedOperationPass == 1),
                                 mListOperationLanes[1])) {
        return false;
    }

    pBranch.AddBatch(aBatch);
    return true;
}
