//
//  GSeedDeriveMaterial.cpp
//  MeanMachine
//
//  Created by Dragon on 4/29/26.
//

#include "GSeedDeriveMaterial.hpp"
#include "Random.hpp"
#include "TwistCryptoGenerator.hpp"
#include "TwistArray.hpp"
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
    mCross = VarSymbol("aCross");
    
    mWandererA = VarSymbol("aWandererA");
    mWandererB = VarSymbol("aWandererB");
    mWandererC = VarSymbol("aWandererC");
    mWandererD = VarSymbol("aWandererD");
    
    mOrbitA = VarSymbol("aOrbitA");
    mOrbitB = VarSymbol("aOrbitB");
    mOrbitC = VarSymbol("aOrbitC");
    mOrbitD = VarSymbol("aOrbitD");
    
    mSource = BufSymbol(TwistWorkSpaceSlot::kSource);
    
    std::vector<GHotPack> aHotPacks = GMagicNumbers::GetHotPacks(4);
    
    if ((aHotPacks.size() > 0)) { mHotPacks[0] = aHotPacks[0]; }
    if ((aHotPacks.size() > 1)) { mHotPacks[1] = aHotPacks[1]; }
    if ((aHotPacks.size() > 2)) { mHotPacks[2] = aHotPacks[2]; }
    if ((aHotPacks.size() > 3)) { mHotPacks[3] = aHotPacks[3]; }
    
    mListSBoxesA.clear();
    mListSBoxesA.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxA));
    mListSBoxesA.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxB));
    mListSBoxesA.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxC));
    mListSBoxesA.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxD));
    
    mListSBoxesB.clear();
    mListSBoxesB.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxA));
    mListSBoxesB.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxB));
    mListSBoxesB.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxC));
    mListSBoxesB.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxD));
    mListSBoxesB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxA));
    mListSBoxesB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxB));
    mListSBoxesB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxC));
    mListSBoxesB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxD));
    
    mListSBoxesC.clear();
    mListSBoxesC.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxA));
    mListSBoxesC.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxB));
    mListSBoxesC.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxC));
    mListSBoxesC.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxD));
    mListSBoxesC.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxE));
    mListSBoxesC.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxF));
    mListSBoxesC.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxG));
    mListSBoxesC.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxH));
    
    mListSaltsA.clear();
    mListSaltsA.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltA));
    mListSaltsA.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltB));
    mListSaltsA.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltC));
    mListSaltsA.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltD));
    
    mListSaltsB.clear();
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltA));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltB));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltC));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltD));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSaltA));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSaltB));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSaltC));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSaltD));
    
    mListSaltsB.clear();
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltA));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltB));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltC));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltD));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSaltA));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSaltB));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSaltC));
    mListSaltsB.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSaltD));
    
    mListScratchSalts.clear();
    mListScratchSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kScratchSaltA));
    mListScratchSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kScratchSaltB));
    mListScratchSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kScratchSaltC));
    mListScratchSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kScratchSaltD));
    
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
    }
}

bool GSeedDeriveMaterial::PlanPhaseA(std::string *pErrorMessage) {
    
    Reset();
    
    Random::Shuffle(&mListWorkers);
    Random::Shuffle(&mListSBoxesA);
    Random::Shuffle(&mListSBoxesB);
    Random::Shuffle(&mListSBoxesC);
    
    Random::Shuffle(&mListSaltsA);
    Random::Shuffle(&mListSaltsB);
    
    Random::Shuffle(&mListScratchSalts);
    
    mBoxFamilyA.Build(mListSBoxesA, 4);
    mBoxFamilyB.Build(mListSBoxesB, 8);
    mBoxFamilyC.Build(mListSBoxesC, 8);
    
    mSaltFamilyA.Build(mListSaltsA, 4);
    mSaltFamilyB.Build(mListSaltsB, 8);
    
    mScratchSaltFamily.Build(mListScratchSalts, 4);
    
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

bool GSeedDeriveMaterial::BuildPhaseA(TwistProgramBranch &pBranch,
                                      std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) { pErrorMessage->clear(); }
    pBranch.Clear();
    
    if (!BuildSnow(pBranch, pErrorMessage)) {
        printf("build snow failed, %s\n", pErrorMessage->c_str());
        return false;
    }
    
    
    
    
    // aState ^= aChar + 0x9E3779B97F4A7C15ULL + (aState << 6) + (aState >> 2);
    // aState *= 0xD6E8FEB86659FD93ULL;

    // We need these to emit to the c++
    GBatch aBatchRoundOne;
    std::vector<GStatement> aStatements;
    GStatement aStatement;
    
    GSymbol aSnowLane = mListExpansion[0];
    
    for (int i=0; i<4; i++) {
        
        GSnow aSnow;
        switch (mSnowType[i]) {
                
            case GSnowType::kAES:
                aBatchRoundOne.AddComment("Making snow counter: aes 256");
                break;
            case GSnowType::kChaCha:
                aBatchRoundOne.AddComment("Making snow counter: cha cha 20");
                break;
            case GSnowType::kSha:
                aBatchRoundOne.AddComment("Making snow counter: sha 256");
                break;
                break;
            case GSnowType::kAria:
                aBatchRoundOne.AddComment("Making snow counter: aria 256");
                break;
            default:
                printf("bad snow type\n");
                return false;
        }
        
        if (!aSnow.Bake(mSnowType[i],
                        mSource,
                        aSnowLane, &aStatements, pErrorMessage)) {
            printf("snow bake failed a: %s\n", pErrorMessage->c_str());
            return false;
        }
        
        aBatchRoundOne.CommitStatements(&aStatements);
        
        GMemory aMemory;
        const GSymbol aDerivedSaltA = BufSymbol(TwistWorkSpaceSlot::kDerivedSaltA);
        const GSymbol aDerivedSaltB = BufSymbol(TwistWorkSpaceSlot::kDerivedSaltB);
        const GSymbol aDerivedSaltC = BufSymbol(TwistWorkSpaceSlot::kDerivedSaltC);
        const GSymbol aDerivedSaltD = BufSymbol(TwistWorkSpaceSlot::kDerivedSaltD);
        const GSymbol aDerivedSBoxA = BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxA);
        const GSymbol aDerivedSBoxB = BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxB);
        const GSymbol aDerivedSBoxC = BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxC);
        const GSymbol aDerivedSBoxD = BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxD);

        GSymbol aScratchSources[4];
        bool aUseGrowB[4];

        if (i == 0) {
            aScratchSources[0] = mSaltFamilyA.mBox[i][0];
            aScratchSources[1] = mSaltFamilyA.mBox[i][1];
            aScratchSources[2] = mSaltFamilyA.mBox[i][2];
            aScratchSources[3] = mSaltFamilyA.mBox[i][3];
            aUseGrowB[0] = false;
            aUseGrowB[1] = true;
            aUseGrowB[2] = false;
            aUseGrowB[3] = true;
        } else if (i == 1) {
            aScratchSources[0] = aDerivedSBoxA;
            aScratchSources[1] = aDerivedSBoxB;
            aScratchSources[2] = aDerivedSBoxC;
            aScratchSources[3] = aDerivedSBoxD;
            aUseGrowB[0] = true;
            aUseGrowB[1] = false;
            aUseGrowB[2] = true;
            aUseGrowB[3] = false;
        } else if (i == 2) {
            aScratchSources[0] = aDerivedSaltA;
            aScratchSources[1] = aDerivedSaltB;
            aScratchSources[2] = aDerivedSaltC;
            aScratchSources[3] = aDerivedSaltD;
            aUseGrowB[0] = false;
            aUseGrowB[1] = true;
            aUseGrowB[2] = false;
            aUseGrowB[3] = true;
        } else {
            aScratchSources[0] = aDerivedSaltC;
            aScratchSources[1] = mSaltFamilyB.mBox[i][1];
            aScratchSources[2] = aDerivedSaltA;
            aScratchSources[3] = mSaltFamilyB.mBox[i][6];
            aUseGrowB[0] = true;
            aUseGrowB[1] = false;
            aUseGrowB[2] = true;
            aUseGrowB[3] = false;
        }

        for (int aScratchIndex = 0; aScratchIndex < 4; ++aScratchIndex) {
            const bool aOk = aUseGrowB[aScratchIndex] ?
                aMemory.BakeGrowB(mScratchSaltFamily.mBox[i][aScratchIndex],
                                  aScratchSources[aScratchIndex],
                                  &aStatements,
                                  pErrorMessage) :
                aMemory.BakeGrowA(mScratchSaltFamily.mBox[i][aScratchIndex],
                                  aScratchSources[aScratchIndex],
                                  &aStatements,
                                  pErrorMessage);
            if (!aOk) {
                printf("Bake memory grow failed (%d, %d): %s\n", i, aScratchIndex, pErrorMessage->c_str());
            }
        }
        
        aBatchRoundOne.CommitStatements(&aStatements);
        
        GLoop aLoop;
        aLoop.mLoopVariable = mLoopIndex;
        aLoop.mLoopVariableName = mLoopIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 1;
        
        // State goes into value
        std::vector<GSymbol> aWandererers;
        aWandererers.push_back(mWandererA);
        aWandererers.push_back(mWandererB);
        aWandererers.push_back(mWandererC);
        aWandererers.push_back(mWandererD);
        Random::Shuffle(&aWandererers);
        
        aStatement = GQuick::MakeAssignVariableStatement(mPrevious, mCurrent);
        aLoop.AddBody(&aStatement);
        
        
        
        GExpr aPrimaryByte;
        GExpr aSnowByte;
        GExpr aStreamByteExpr;
        GExpr aCrossExpr;

        if (i == 0) {
            aPrimaryByte = GQuick::MakeReadBufferReadExpression(mSource, mLoopIndex);
            aSnowByte = GQuick::MakeReadBufferReadExpressionInverted(aSnowLane, mLoopIndex);
            aCrossExpr = GQuick::MakeReadBufferReadExpressionInverted(mSource, mLoopIndex);
        } else if (i == 1) {
            aPrimaryByte = GQuick::MakeReadBufferReadExpression(mDestBuffer[0], mLoopIndex);
            aSnowByte = GQuick::MakeReadBufferReadExpression(aSnowLane, mLoopIndex);
            aCrossExpr = GQuick::MakeReadBufferReadExpression(mSource, mLoopIndex);
        } else if (i == 2) {
            aPrimaryByte = GQuick::MakeReadBufferReadExpression(mDestBuffer[1], mLoopIndex);
            aSnowByte = GQuick::MakeReadBufferReadExpressionInverted(aSnowLane, mLoopIndex);
            aCrossExpr = GQuick::MakeReadBufferReadExpressionInverted(mDestBuffer[0], mLoopIndex);
        } else {
            aPrimaryByte = GQuick::MakeReadBufferReadExpression(mDestBuffer[2], mLoopIndex);
            aSnowByte = GQuick::MakeReadBufferReadExpression(aSnowLane, mLoopIndex);
            aCrossExpr = GQuick::MakeReadBufferReadExpression(mDestBuffer[1], mLoopIndex);
        }

        aStreamByteExpr = GExpr::Xor(aPrimaryByte, GExpr::ShiftL(aSnowByte, GExpr::Const64(32)));

        aStatement = GQuick::MakeAssignVariableStatement(mCurrent, aStreamByteExpr);
        aLoop.AddBody(&aStatement);

        aStatement = GQuick::MakeAssignVariableStatement(mCross, aCrossExpr);
        aLoop.AddBody(&aStatement);
        
        std::vector<GSymbol> aOrbiters;
        aOrbiters.push_back(mOrbitA);
        aOrbiters.push_back(mOrbitB);
        aOrbiters.push_back(mOrbitC);
        aOrbiters.push_back(mOrbitD);
        Random::Shuffle(&aOrbiters);
        
        std::vector<GSymbol> aSBoxes;
        
        if (i == 0) {
            aSBoxes.push_back(mBoxFamilyA.mBox[i][0]);
            aSBoxes.push_back(mBoxFamilyA.mBox[i][1]);
            aSBoxes.push_back(mBoxFamilyA.mBox[i][2]);
            aSBoxes.push_back(mBoxFamilyA.mBox[i][3]);
        } else if (i == 1) {
            aSBoxes.push_back(mBoxFamilyB.mBox[i][0]);
            aSBoxes.push_back(mBoxFamilyB.mBox[i][1]);
            aSBoxes.push_back(mBoxFamilyB.mBox[i][2]);
            aSBoxes.push_back(mBoxFamilyB.mBox[i][3]);
            aSBoxes.push_back(mBoxFamilyB.mBox[i][4]);
            aSBoxes.push_back(mBoxFamilyB.mBox[i][5]);
            aSBoxes.push_back(mBoxFamilyB.mBox[i][6]);
            aSBoxes.push_back(mBoxFamilyB.mBox[i][7]);
        } else {
            aSBoxes.push_back(mBoxFamilyC.mBox[i][0]);
            aSBoxes.push_back(mBoxFamilyC.mBox[i][1]);
            aSBoxes.push_back(mBoxFamilyC.mBox[i][2]);
            aSBoxes.push_back(mBoxFamilyC.mBox[i][3]);
            aSBoxes.push_back(mBoxFamilyC.mBox[i][4]);
            aSBoxes.push_back(mBoxFamilyC.mBox[i][5]);
            aSBoxes.push_back(mBoxFamilyC.mBox[i][6]);
            aSBoxes.push_back(mBoxFamilyC.mBox[i][7]);
        }
        
        std::vector<GSymbol> aSaltsFixed;
        if ((i == 0) || (i == 1)) {
            aSaltsFixed.push_back(mSaltFamilyA.mBox[i][0]);
            aSaltsFixed.push_back(mSaltFamilyA.mBox[i][1]);
            aSaltsFixed.push_back(mSaltFamilyA.mBox[i][2]);
            aSaltsFixed.push_back(mSaltFamilyA.mBox[i][3]);
        } else {
            aSaltsFixed.push_back(mSaltFamilyB.mBox[i][0]);
            aSaltsFixed.push_back(mSaltFamilyB.mBox[i][1]);
            aSaltsFixed.push_back(mSaltFamilyB.mBox[i][2]);
            aSaltsFixed.push_back(mSaltFamilyB.mBox[i][3]);
            aSaltsFixed.push_back(mSaltFamilyB.mBox[i][4]);
            aSaltsFixed.push_back(mSaltFamilyB.mBox[i][5]);
            aSaltsFixed.push_back(mSaltFamilyB.mBox[i][6]);
            aSaltsFixed.push_back(mSaltFamilyB.mBox[i][7]);
        }
        
        std::vector<GSymbol> aSaltsScratch;
        aSaltsScratch.push_back(mScratchSaltFamily.mBox[i][0]);
        aSaltsScratch.push_back(mScratchSaltFamily.mBox[i][1]);
        aSaltsScratch.push_back(mScratchSaltFamily.mBox[i][2]);
        aSaltsScratch.push_back(mScratchSaltFamily.mBox[i][3]);
        
        std::vector<Mix64Type_4> aMixTypes4;
        aMixTypes4.push_back(Mix64Type_4::kGateRollA_4_8);
        aMixTypes4.push_back(Mix64Type_4::kGateRollB_4_8);
        aMixTypes4.push_back(Mix64Type_4::kGateRollC_4_8);
        aMixTypes4.push_back(Mix64Type_4::kGateTurnA_4_8);
        aMixTypes4.push_back(Mix64Type_4::kGateTurnB_4_8);
        aMixTypes4.push_back(Mix64Type_4::kGateTurnC_4_8);
        
        std::vector<Mix64Type_8> aMixTypes8;
        aMixTypes8.push_back(Mix64Type_8::kGateRoll_8_8);
        aMixTypes8.push_back(Mix64Type_8::kGateTurn_8_8);
        aMixTypes8.push_back(Mix64Type_8::kGatePrism_8_8);
        
        std::vector<int> aRotationsLow = GRotationFamily::GetListLow();
        std::vector<int> aRotationsMedium = GRotationFamily::GetListMedium();
        std::vector<int> aRotationsHigh = GRotationFamily::GetListHigh();
        std::vector<int> aRotationsRandom = GRotationFamily::GetListAll();
        
        aLoop.AddBodyComment("__START_CSPRNG");
        
        if (!CSPRNG::Bake(mDestBuffer[i],
                          mDestReverse[i],
                          mLoopIndex,
                          mCurrent,
                          mPrevious,
                          mPrism,
                          mScatter,
                          mCross,
                          mCarry,
                          aWandererers[0],
                          aWandererers[1],
                          aWandererers[2],
                          aOrbiters[0],
                          aOrbiters[1],
                          aOrbiters[2],
                          aOrbiters[3],
                          aSBoxes,
                          aSaltsFixed,
                          aSaltsScratch,
                          aRotationsLow,
                          aRotationsMedium,
                          aRotationsHigh,
                          aRotationsRandom,
                          aMixTypes4,
                          aMixTypes8,
                          mHotPacks[i],
                          &aStatements,
                          pErrorMessage)) {
            printf("CSPRNG failed: %s\n", pErrorMessage->c_str());
            return false;
        }
        
        aLoop.AddBody(&aStatements);
        aLoop.AddBodyComment("__END_CSPRNG");
        
        aBatchRoundOne.CommitLoop(&aLoop);
        
        if (!aMemory.BakeZero(aSnowLane,
                              &aStatements,
                              pErrorMessage)) {
            printf("Bake memory zero failed a: %s\n", pErrorMessage->c_str());
        }
        
        aBatchRoundOne.AddComment("Secure zero on crypto buffer.");
        aBatchRoundOne.CommitStatements(&aStatements);
        
        {
            const GSymbol aCryptoSource = mDestBuffer[i];
            const std::string aCryptoSourceAlias = BufAliasName(aCryptoSource.mSlot);

            // Flush this loop as its own branch step so derive calls can run after each lane pass.
            pBranch.AddBatch(aBatchRoundOne);
            aBatchRoundOne = GBatch();

            // After loop 1, derive 4 s-boxes with the worker that was written.
            if (i == 0) {
                pBranch.AddLine("pCryptoGenerator->Make(" + aCryptoSourceAlias +
                                ", pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);");
            } else if (i == 1) {
                pBranch.AddLine("pCryptoGenerator->Salt(" + aCryptoSourceAlias +
                                ", pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, "
                                "pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);");
            } else if (i == 2) {
                pBranch.AddLine("pCryptoGenerator->Salt(" + aCryptoSourceAlias +
                                ", pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, "
                                "pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, "
                                "pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD, "
                                "pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);");
            } else {
                pBranch.AddLine("pCryptoGenerator->Salt(" + aCryptoSourceAlias +
                                ", pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, "
                                "pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, "
                                "pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD, "
                                "pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);");
            }
        }
    }
    
    

    return true;
}


bool GSeedDeriveMaterial::BuildSnow(TwistProgramBranch &pBranch, std::string *pErrorMessage) {
    
    /*
    // We cannot add a comment line to batch
    GBatch aBatch;
    aBatch.mName = "Snow";
    GSnow aSnow;
    std::vector<GStatement> aStatements;
    if (!aSnow.BakeAES256(mSource, mListExpansion[0], &aStatements, pErrorMessage)) {
        printf("aes failed\n");
        return false;
    }
    if (!aSnow.BakeChaCha20(mSource, mListExpansion[1], &aStatements, pErrorMessage)) {
        printf("cha cha failed\n");
        return false;
    }
    if (!aSnow.BakeAria256(mSource, mListExpansion[2], &aStatements, pErrorMessage)) {
        printf("aria failed\n");
        return false;
    }
    if (!aSnow.BakeSha256(mSource, mListExpansion[3], &aStatements, pErrorMessage)) {
        printf("sha failed\n");
        return false;
    }
    aBatch.CommitStatements(&aStatements);
    pBranch.AddBatch(aBatch);
    */
    return true;
}

bool GSeedDeriveMaterial::BuildZero(GSymbol pSymbol, TwistProgramBranch &pBranch, std::string *pErrorMessage) {

    // We cannot add a comment line to batch
    GBatch aBatch;
    aBatch.mName = "Zero";
    GMemory aMemory;
    
    std::vector<GStatement> aStatements;
    
    if (!aMemory.BakeZero(pSymbol, &aStatements, pErrorMessage)) {
        printf("zero failed\n");
        return false;
    }
    
    aBatch.AddComment("Secure Zero Out");
    aBatch.CommitStatements(&aStatements);
    pBranch.AddBatch(aBatch);
    return true;
    
    return true;
}
