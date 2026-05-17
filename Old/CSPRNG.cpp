//
//  CSPRNG.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/2/26.
//

#include "CSPRNG.hpp"
#include "GSelect.hpp"
#include "TwistArray.hpp"

struct CSPRNGPlugModeHash {
    std::size_t operator()(CSPRNGPlugMode pMode) const {
        return static_cast<std::size_t>(pMode);
    }
};

GExpr CSPRNGPlugPack::GetExpr(CSPRNGPlugMode pPlugMode) {
    
    switch (pPlugMode) {
        case CSPRNGPlugMode::kInv:
            return GExpr::Symbol(mInput);
        case CSPRNGPlugMode::kInputPrevious:
            return GExpr::Symbol(mPrevious);
        case CSPRNGPlugMode::kCross:
            return GExpr::Symbol(mStreamCross);
        case CSPRNGPlugMode::kCarry:
            return GExpr::Symbol(mCarry);
        case CSPRNGPlugMode::kUnwindA:
            return GExpr::Symbol(mUnwindA);
        case CSPRNGPlugMode::kUnwindB:
            return GExpr::Symbol(mUnwindB);
        case CSPRNGPlugMode::kUnwindC:
            return GExpr::Symbol(mUnwindC);
        case CSPRNGPlugMode::kOrbiterA:
            return GExpr::Symbol(mOrbiterA);
        case CSPRNGPlugMode::kOrbiterB:
            return GExpr::Symbol(mOrbiterB);
        case CSPRNGPlugMode::kOrbiterC:
            return GExpr::Symbol(mOrbiterC);
        case CSPRNGPlugMode::kOrbiterD:
            return GExpr::Symbol(mOrbiterD);
        default:
            return GExpr::Symbol(mScatter);
    }
}

GExpr CSPRNG::CreatePlug(GExpr pExpr,
                         bool pAdd,
                         GSymbol pSalt,
                         GIntCache *pRotCache,
                         CSPRNGPlugPack *pPack,
                         std::deque<CSPRNGPlugMode> *pRecent) {
    
    std::unordered_set<CSPRNGPlugMode, CSPRNGPlugModeHash> aIgnore;
    
    if (pSalt.IsInvalid()) {
        printf("fatal: tried to create plug with invalid salt\n");
        return pExpr;
    }
    
    if (pPack == nullptr) {
        printf("fatal: tried to create plug with null pack\n");
        return pExpr;
    }
    
    if (pRecent != nullptr) {
        for (auto &aMode : *pRecent) {
            aIgnore.insert(aMode);
        }
    }
    
    std::vector<CSPRNGPlugMode> aPool;
    
    auto TryAddMode = [&](CSPRNGPlugMode pMode) {
        if (aIgnore.find(pMode) == aIgnore.end()) {
            aPool.push_back(pMode);
        }
    };

    TryAddMode(CSPRNGPlugMode::kInput);
    TryAddMode(CSPRNGPlugMode::kInputPrevious);
    TryAddMode(CSPRNGPlugMode::kScatter);
    TryAddMode(CSPRNGPlugMode::kCross);
    TryAddMode(CSPRNGPlugMode::kCarry);
    TryAddMode(CSPRNGPlugMode::kUnwindA);
    TryAddMode(CSPRNGPlugMode::kUnwindB);
    TryAddMode(CSPRNGPlugMode::kUnwindC);
    TryAddMode(CSPRNGPlugMode::kOrbiterA);
    TryAddMode(CSPRNGPlugMode::kOrbiterB);
    TryAddMode(CSPRNGPlugMode::kOrbiterC);
    TryAddMode(CSPRNGPlugMode::kOrbiterD);
    
    Random::Shuffle(&aPool);
    
    bool aTryTwo = Random::Get(3) != 1;
    
    if (aPool.size() <= 0) {
        printf("fatal: this is an empty pool\n");
        return pExpr;
    }
    
    CSPRNGPlugMode aMode1 = CSPRNGPlugMode::kInv;
    CSPRNGPlugMode aMode2 = CSPRNGPlugMode::kInv;
    
    if (aPool.size() <= 1) {
        aTryTwo = false;
    }
    
    aMode1 = aPool[0];
    
    if (aTryTwo) {
        for (int i = 1; i < aPool.size(); i++) {
            if (!PlugIncompatible(aMode1, aPool[i])) {
                aMode2 = aPool[i];
                break;
            }
        }
        
        if (aMode2 == CSPRNGPlugMode::kInv) {
            aTryTwo = false;
        }
    }
    
    if (pRecent != nullptr) {
        pRecent->push_back(aMode1);
        
        if (aTryTwo) {
            pRecent->push_back(aMode2);
        }
        
        while (pRecent->size() > 8) {
            pRecent->pop_front();
        }
    }
    
    int aRotationIndex = 0;

    if (aTryTwo) {
        aRotationIndex = Random::Get(2);
    }
    
    auto MakePlugTerm = [&](CSPRNGPlugMode pMode, int pTermIndex) -> GExpr {
        GExpr aExpr = pPack->GetExpr(pMode);
        
        // Rotate exactly one selected plug term.
        if (pTermIndex == aRotationIndex) {
            pRotCache->Fetch(1);
            aExpr = GExpr::RotL64(aExpr, GExpr::Const64(pRotCache->mBus[0]));
        }
        return aExpr;
    };
    
    GExpr aSaltKeyExpr;
    if (aTryTwo) {
        GExpr aExpr1 = MakePlugTerm(aMode1, 0);
        GExpr aExpr2 = MakePlugTerm(aMode2, 1);
        if (Random::Bool()) {
            aSaltKeyExpr = GExpr::Add(aExpr1, aExpr2);
        } else {
            aSaltKeyExpr = GExpr::Xor(aExpr1, aExpr2);
        }
    } else {
        aSaltKeyExpr = MakePlugTerm(aMode1, 0);
    }
    
    GExpr aSaltExpr = GQuick::MakeReadBufferReadExpression(pSalt, aSaltKeyExpr);
    
    if (pAdd) {
        return GExpr::Add(pExpr, aSaltExpr);
    } else {
        return GExpr::Xor(pExpr, aSaltExpr);
    }
}

bool CSPRNG::PlugIncompatible(CSPRNGPlugMode pPlugModeA,
                              CSPRNGPlugMode pPlugModeB) {
    
    if (pPlugModeA == pPlugModeB) {
        return true;
    }
    
    auto IsPair = [](CSPRNGPlugMode pA,
                     CSPRNGPlugMode pB,
                     CSPRNGPlugMode pX,
                     CSPRNGPlugMode pY) -> bool {
        return (
            (pA == pX && pB == pY) ||
            (pA == pY && pB == pX)
        );
    };
    
    // Direct seed relationships:
    // a = s0 + ...
    // b = s1 ^ ...
    // c = s2 + ...
    // d = carry ^ ...
    if (IsPair(pPlugModeA, pPlugModeB, CSPRNGPlugMode::kOrbiterA, CSPRNGPlugMode::kUnwindA)) {
        return true;
    }
    
    if (IsPair(pPlugModeA, pPlugModeB, CSPRNGPlugMode::kOrbiterB, CSPRNGPlugMode::kUnwindB)) {
        return true;
    }
    
    if (IsPair(pPlugModeA, pPlugModeB, CSPRNGPlugMode::kOrbiterC, CSPRNGPlugMode::kUnwindC)) {
        return true;
    }
    
    if (IsPair(pPlugModeA, pPlugModeB, CSPRNGPlugMode::kOrbiterD, CSPRNGPlugMode::kCarry)) {
        return true;
    }
    
    if (IsPair(pPlugModeA, pPlugModeB, CSPRNGPlugMode::kInputPrevious, CSPRNGPlugMode::kInput)) {
        return true;
    }
    
    
    return false;
}

bool CSPRNG::Bake(GSymbol pDest,
                  bool pDestWriteInverted,
                  
                  GSymbol pLoopIndex,
                  
                  GSymbol pCurrent,
                  GSymbol pPrevious,
                  
                  GSymbol pPrism,
                  bool pIgnorePrism,
                  GSymbol pScatter,
                  
                  GSymbol pStreamCross,
                  GSymbol pCarry,
                  
                  GSymbol pUnwindA,
                  GSymbol pUnwindB,
                  GSymbol pUnwindC,
                  
                  GSymbol pOrbiterA,
                  GSymbol pOrbiterB,
                  GSymbol pOrbiterC,
                  GSymbol pOrbiterD,
                  
                  GSymbol pRecipeSaltA,
                  GSymbol pRecipeSaltB,
                  
                  std::vector<GSymbol> pSBoxes,
                  std::vector<GSymbol> pSalts,
                  
                  std::vector<int> pRotationsLow,
                  std::vector<int> pRotationsMedium,
                  std::vector<int> pRotationsHigh,
                  std::vector<int> pRotationsRandom,
                  
                  std::vector<Mix64Type_8> pMixTypes8,
                  
                  GHotPack pHotPack,
                  
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) {
    
    bool aDisableComments = true;
    
    std::deque<CSPRNGPlugMode> aRecentPlugDeque;
    
    
    std::vector<GSymbol> aSBoxesPermutationA;
    std::vector<GSymbol> aSBoxesPermutationB;
    std::vector<GSymbol> aSBoxesPermutationC;
    std::vector<GSymbol> aSBoxesPermutationD;

    std::vector<GSymbol>* aPermutations[4] = {
        &aSBoxesPermutationA,
        &aSBoxesPermutationB,
        &aSBoxesPermutationC,
        &aSBoxesPermutationD
    };

    for (int aPermIndex = 0; aPermIndex < 4; aPermIndex++) {

        bool aAccepted = false;

        for (int aTry = 0; aTry < 10000; aTry++) {

            aPermutations[aPermIndex]->clear();
            TwistArray::Append(aPermutations[aPermIndex], &pSBoxes);
            Random::Shuffle(aPermutations[aPermIndex]);

            bool aGood = true;

            for (int aOtherPermIndex = 0; aOtherPermIndex < aPermIndex; aOtherPermIndex++) {
                for (int i = 0; i < 8; i++) {
                    if ((*aPermutations[aPermIndex])[i] == (*aPermutations[aOtherPermIndex])[i]) {
                        aGood = false;
                        break;
                    }
                }

                if (!aGood) {
                    break;
                }
            }

            if (aGood) {
                aAccepted = true;
                break;
            }
        }
    }
    
    
    int aHotIndex = Random::Get(3);
    
    CSPRNGPlugPack aPlugPack;
    aPlugPack.mInput = pCurrent;
    aPlugPack.mPrevious = pPrevious;
    aPlugPack.mScatter = pScatter;
    aPlugPack.mStreamCross = pStreamCross;
    aPlugPack.mCarry = pCarry;
    aPlugPack.mUnwindA = pUnwindA;
    aPlugPack.mUnwindB = pUnwindB;
    aPlugPack.mUnwindC = pUnwindC;
    aPlugPack.mOrbiterA = pOrbiterA;
    aPlugPack.mOrbiterB = pOrbiterB;
    aPlugPack.mOrbiterC = pOrbiterC;
    aPlugPack.mOrbiterD = pOrbiterD;

    GIntCache aRotCacheLow;
    aRotCacheLow.AddItems(pRotationsLow);
    aRotCacheLow.SetLimits(2, 3, 3);

    GIntCache aRotCacheMedium;
    aRotCacheMedium.AddItems(pRotationsMedium);
    aRotCacheMedium.SetLimits(3, 4, 5);

    GIntCache aRotCacheHigh;
    aRotCacheHigh.AddItems(pRotationsHigh);
    aRotCacheHigh.SetLimits(3, 4, 5);

    GIntCache aRotCacheRandom;
    aRotCacheRandom.AddItems(pRotationsLow);
    aRotCacheRandom.AddItems(pRotationsMedium);
    aRotCacheRandom.AddItems(pRotationsHigh);
    aRotCacheRandom.SetLimits(3, 4, 5);

    aRotCacheLow.LinkSharedHistory(&aRotCacheRandom.mHistory);
    aRotCacheMedium.LinkSharedHistory(&aRotCacheRandom.mHistory);
    aRotCacheHigh.LinkSharedHistory(&aRotCacheRandom.mHistory);

    aRotCacheRandom.LinkSharedHistory(&aRotCacheLow.mHistory);
    aRotCacheRandom.LinkSharedHistory(&aRotCacheMedium.mHistory);
    aRotCacheRandom.LinkSharedHistory(&aRotCacheHigh.mHistory);

    GMix648Cache aMix648Cache;
    aMix648Cache.AddItems(pMixTypes8);
    aMix648Cache.SetLimits(2, 2, 2);
    
    GSymbolCache aSaltCacheFixed;
    for (int i=0; i<pSalts.size(); i++) {
        aSaltCacheFixed.AddItem(&(pSalts[i]));
    }
    
    // 4 guarantees that we follow the correct salt
    // pattern for operation groups 1 and 2
    aSaltCacheFixed.SetLimits(4, 6, 6);
    
    
    GSymbolCache aSBoxCache;
    for (int i=0; i<pSBoxes.size(); i++) {
        aSBoxCache.AddItem(&(pSBoxes[i]));
    }
    if (pSalts.size() <= 4) {
        aSBoxCache.SetLimits(2, 3, 4);
    } else {
        aSBoxCache.SetLimits(4, 6, 8);
    }
    
    auto PopRandomFixedSalt = [&]() -> GSymbol {
        aSaltCacheFixed.Fetch(1);
        return *(aSaltCacheFixed.mBus[0]);
    };
    
    auto PopLowRotation = [&]() -> int {
        aRotCacheLow.Fetch(1);
        return aRotCacheLow.mBus[0];
    };

    auto PopMediumRotation = [&]() -> int {
        aRotCacheMedium.Fetch(1);
        return aRotCacheMedium.mBus[0];
    };

    auto PopHighRotation = [&]() -> int {
        aRotCacheHigh.Fetch(1);
        return aRotCacheHigh.mBus[0];
    };

    auto PopRandomRotation = [&]() -> int {
        aRotCacheRandom.Fetch(1);
        return aRotCacheRandom.mBus[0];
    };
    
    auto RotLow = [&](GExpr pExpr) -> GExpr {
        return GExpr::RotL64(pExpr, GExpr::Const64(PopLowRotation()));
    };

    auto RotMedium = [&](GExpr pExpr) -> GExpr {
        return GExpr::RotL64(pExpr, GExpr::Const64(PopMediumRotation()));
    };

    auto RotHigh = [&](GExpr pExpr) -> GExpr {
        return GExpr::RotL64(pExpr, GExpr::Const64(PopHighRotation()));
    };

    auto RotRandom = [&](GExpr pExpr) -> GExpr {
        return GExpr::RotL64(pExpr, GExpr::Const64(PopRandomRotation()));
    };
    
    auto RotMostlyMedium = [&](GExpr pExpr) -> GExpr {
        int aWhich = Random::Get(3);

        if (aWhich == 0) {
            return RotRandom(pExpr);
        } else if (aWhich == 1) {
            return RotLow(pExpr);
        }

        return RotMedium(pExpr);
    };

    auto RotMediumHighRandom = [&](GExpr pExpr) -> GExpr {
        int aWhich = Random::Get(4);

        if (aWhich == 0) {
            return RotMedium(pExpr);
        } else if (aWhich == 1) {
            return RotHigh(pExpr);
        } else if (aWhich == 2) {
            return RotHigh(pExpr);
        }

        return RotRandom(pExpr);
    };
    
    auto RotMediumOrRandom = [&](GExpr pExpr) -> GExpr {
        if (Random::Bool()) {
            return GExpr::RotL64(pExpr, GExpr::Const64(PopMediumRotation()));
        }
        
        return GExpr::RotL64(pExpr, GExpr::Const64(PopRandomRotation()));
    };

    auto RotMediumHigh = [&](GExpr pExpr) -> GExpr {
        if (Random::Bool()) {
            return RotMedium(pExpr);
        }

        return RotHigh(pExpr);
    };
    
    auto DiffuseRandom = [&](GExpr pExpr) -> GExpr {
        int aWhich = Random::Get(3);
        
        if (aWhich == 0) {
            return GExpr::DiffuseA(pExpr);
        } else if (aWhich == 1) {
            return GExpr::DiffuseB(pExpr);
        }
        
        return GExpr::DiffuseC(pExpr);
    };
    
    auto PrismSet = [&](GExpr pExpr) {
        if (pIgnorePrism) {
            return;
        }
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pPrism, pExpr));
    };

    auto PrismDiffuse = [&]() {
        if (pIgnorePrism) {
            return;
        }
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pPrism, DiffuseRandom(GExpr::Symbol(pPrism))));
    };
    
    bool aPrismAddCadence = Random::Bool();
    
    auto EmitComment = [&](const std::string &pText) {
        if (pText.empty() || !aDisableComments) {
            pStatements->push_back(GStatement::Comment(pText));
        }
    };
    
    struct PrismScheduleTerm {
        GSymbol mSymbol;
        bool mRotate = false;
    };
    
    struct PrismScheduleSaltPlug {
        bool mAdd = true;
        GSymbol mSalt;
    };
    
    struct PrismScheduleUpdate {
        std::vector<PrismScheduleTerm> mTerms;
        std::vector<PrismScheduleSaltPlug> mSaltPlugs;
    };
    
    std::vector<PrismScheduleUpdate> aPrismSchedule(4);
    
    auto UpdateLoad = [&](int pUpdateIndex) -> int {
        if ((pUpdateIndex < 0) || (pUpdateIndex >= static_cast<int>(aPrismSchedule.size()))) {
            return 0;
        }
        const PrismScheduleUpdate &aUpdate = aPrismSchedule[static_cast<std::size_t>(pUpdateIndex)];
        return static_cast<int>(aUpdate.mTerms.size() + aUpdate.mSaltPlugs.size());
    };
    
    auto PickLeastOccupiedIndex = [&](const std::vector<int> &pCandidateUpdates) -> int {
        if (pCandidateUpdates.empty()) {
            return 0;
        }
        
        int aBestLoad = UpdateLoad(pCandidateUpdates[0]);
        for (std::size_t i = 1U; i < pCandidateUpdates.size(); ++i) {
            const int aLoad = UpdateLoad(pCandidateUpdates[i]);
            if (aLoad < aBestLoad) {
                aBestLoad = aLoad;
            }
        }
        
        std::vector<int> aLeastOccupied;
        for (std::size_t i = 0U; i < pCandidateUpdates.size(); ++i) {
            if (UpdateLoad(pCandidateUpdates[i]) == aBestLoad) {
                aLeastOccupied.push_back(pCandidateUpdates[i]);
            }
        }
        
        if (aLeastOccupied.empty()) {
            return pCandidateUpdates[0];
        }
        
        return aLeastOccupied[static_cast<std::size_t>(Random::Get(static_cast<int>(aLeastOccupied.size())))];
    };
    
    auto AssignTermToUpdate = [&](int pUpdateIndex,
                                  GSymbol pSymbol) {
        if ((pUpdateIndex < 0) || (pUpdateIndex >= static_cast<int>(aPrismSchedule.size()))) {
            return;
        }
        PrismScheduleTerm aTerm;
        aTerm.mSymbol = pSymbol;
        aTerm.mRotate = false;
        aPrismSchedule[static_cast<std::size_t>(pUpdateIndex)].mTerms.push_back(aTerm);
    };
    
    auto AssignTermToLeastOccupied = [&](const std::vector<int> &pCandidateUpdates,
                                         GSymbol pSymbol) {
        const int aUpdateIndex = PickLeastOccupiedIndex(pCandidateUpdates);
        AssignTermToUpdate(aUpdateIndex, pSymbol);
    };
    
    // Fixed anchors:
    // Update 1 == prism update #2 (overall update 2): pOrbiterC
    // Update 3 == prism update #4 (overall update 4): pOrbiterB
    // Update 4 == prism update #5 (overall update 5): pOrbiterD
    AssignTermToUpdate(0, pOrbiterC);
    AssignTermToUpdate(2, pOrbiterB);
    AssignTermToUpdate(3, pOrbiterD);
    
    // pUnwindA goes to update 4 or 5.
    AssignTermToUpdate(Random::Bool() ? 2 : 3, pUnwindA);
    
    // Distribute carry/previous/cross to least-occupied updates.
    std::vector<GSymbol> aRemainingPrismTerms = { pCarry, pPrevious, pStreamCross };
    Random::Shuffle(&aRemainingPrismTerms);
    for (std::size_t i = 0U; i < aRemainingPrismTerms.size(); ++i) {
        AssignTermToLeastOccupied({0, 1, 2, 3}, aRemainingPrismTerms[i]);
    }
    
    // Make 2 salt plugs mandatory for now; assign to least-occupied updates.
    for (int aPlugIndex = 0; aPlugIndex < 2; ++aPlugIndex) {
        const int aUpdateIndex = PickLeastOccupiedIndex({0, 1, 2, 3});
        PrismScheduleSaltPlug aPlug;
        aPlug.mAdd = Random::Bool();
        aPlug.mSalt = PopRandomFixedSalt();
        aPrismSchedule[static_cast<std::size_t>(aUpdateIndex)].mSaltPlugs.push_back(aPlug);
    }
    
    // Rotate 1-2 terms per update (or all terms if fewer than that).
    for (std::size_t aUpdateIndex = 0U; aUpdateIndex < aPrismSchedule.size(); ++aUpdateIndex) {
        std::vector<PrismScheduleTerm> &aTerms = aPrismSchedule[aUpdateIndex].mTerms;
        if (aTerms.empty()) {
            continue;
        }
        
        std::vector<int> aIndices;
        for (std::size_t i = 0U; i < aTerms.size(); ++i) {
            aIndices.push_back(static_cast<int>(i));
            aTerms[i].mRotate = false;
        }
        Random::Shuffle(&aIndices);
        
        int aRotateCount = 1 + Random::Get(2); // 1..2
        if (aRotateCount > static_cast<int>(aTerms.size())) {
            aRotateCount = static_cast<int>(aTerms.size());
        }
        
        for (int i = 0; i < aRotateCount; ++i) {
            aTerms[static_cast<std::size_t>(aIndices[static_cast<std::size_t>(i)])].mRotate = true;
        }
    }
    
    auto BuildPrismTermExpr = [&](int pUpdateIndex) -> GExpr {
        if ((pUpdateIndex < 0) || (pUpdateIndex >= static_cast<int>(aPrismSchedule.size()))) {
            return GExpr::Symbol(pCarry);
        }
        
        const PrismScheduleUpdate &aUpdate = aPrismSchedule[static_cast<std::size_t>(pUpdateIndex)];
        const std::vector<PrismScheduleTerm> &aTerms = aUpdate.mTerms;
        if (aTerms.empty()) {
            return GExpr::Symbol(pCarry);
        }
        
        auto MakeTermExpr = [&](const PrismScheduleTerm &pTerm) -> GExpr {
            GExpr aExpr = GExpr::Symbol(pTerm.mSymbol);
            if (pTerm.mRotate) {
                aExpr = RotMediumHighRandom(aExpr);
            }
            return aExpr;
        };
        
        GExpr aExpr = MakeTermExpr(aTerms[0]);
        for (std::size_t i = 1U; i < aTerms.size(); ++i) {
            GExpr aNextExpr = MakeTermExpr(aTerms[i]);
            if (Random::Bool()) {
                aExpr = GExpr::Add(aExpr, aNextExpr);
            } else {
                aExpr = GExpr::Xor(aExpr, aNextExpr);
            }
        }
        
        for (std::size_t i = 0U; i < aUpdate.mSaltPlugs.size(); ++i) {
            aExpr = CreatePlug(aExpr,
                               aUpdate.mSaltPlugs[i].mAdd,
                               aUpdate.mSaltPlugs[i].mSalt,
                               &aRotCacheMedium,
                               &aPlugPack,
                               &aRecentPlugDeque);
        }
        
        return aExpr;
    };

    auto FetchSBoxPack8 = [&]() -> std::array<GSymbol, 8> {
        aSBoxCache.Fetch(8);
        
        return {
            *(aSBoxCache.mBus[0]),
            *(aSBoxCache.mBus[1]),
            *(aSBoxCache.mBus[2]),
            *(aSBoxCache.mBus[3]),
            *(aSBoxCache.mBus[4]),
            *(aSBoxCache.mBus[5]),
            *(aSBoxCache.mBus[6]),
            *(aSBoxCache.mBus[7])
        };
    };
    
    auto MakeRandomLoopSaltPair = [&]() -> std::pair<GExpr, GExpr> {
        GExpr aFixedSaltExpr;
        GExpr aSecondSaltExpr;
        
        if (Random::Bool()) {
            aFixedSaltExpr = GQuick::MakeReadBufferOffsetExpression(
                PopRandomFixedSalt(),
                pLoopIndex
            );
            
            aSecondSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(
                PopRandomFixedSalt(),
                pLoopIndex
            );
        } else {
            aFixedSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(
                PopRandomFixedSalt(),
                pLoopIndex
            );
            
            aSecondSaltExpr = GQuick::MakeReadBufferOffsetExpression(
                PopRandomFixedSalt(),
                pLoopIndex
            );
        }
        
        return { aFixedSaltExpr, aSecondSaltExpr };
    };
    
    
    {
        
        
        
        EmitComment("scatter = mix(secure_a, secure_b, previous)");
        
        
        GExpr aMainSnowPartA;
        GExpr aMainSnowPartB;
        GExpr aMainSnowPartC;
        int aWhichMainSnow = Random::Get(2);
        if (aWhichMainSnow == 0) {
            aMainSnowPartA = GExpr::ShiftL(GExpr::Symbol(pCurrent), GExpr::Const64(32));
            aMainSnowPartB = GExpr::Symbol(pStreamCross);
            aMainSnowPartC = GExpr::RotL64(GExpr::Symbol(pPrevious), GExpr::Const64(PopMediumRotation()));
        } else {
            aMainSnowPartA = GExpr::Symbol(pCurrent);
            aMainSnowPartB = GExpr::ShiftL(GExpr::Symbol(pStreamCross), GExpr::Const64(32));
            aMainSnowPartC = GExpr::RotL64(GExpr::Symbol(pPrevious), GExpr::Const64(PopMediumRotation()));
        }
        GExpr aMainSnowGuts = GExpr::Xor(aMainSnowPartA, GExpr::Xor(aMainSnowPartB, aMainSnowPartC));
        GExpr aMainSnow = GExpr::DiffuseA(aMainSnowGuts);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pScatter, aMainSnow));
        
        
    }
    
    {
        int aHotA = aHotIndex++;
        int aHotB = aHotIndex++;
        
        EmitComment("a = s0 + rot(e) + hot.add + plug[+];");
        EmitComment("b = s1 ^ rot(previous) ^ hot.add ^ plug[^];");
        EmitComment("c = s2 + rot(cross) + fixedSalt[i/~i] + fixedSalt[~i/i];");
        EmitComment("d = rot(carry) ^ rot(e) ^ fixedSalt[i/~i] ^ fixedSalt[~i/i];");
        EmitComment("prism = e;");
        
        GExpr aExprOrbitA = GExpr::Symbol(pUnwindA);
        aExprOrbitA = GExpr::Add(aExprOrbitA, RotMostlyMedium(GExpr::Symbol(pCurrent)));
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Const64(pHotPack.mPair[aHotA].mAdd));
        aExprOrbitA = CreatePlug(aExprOrbitA, true, pRecipeSaltA, &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterA, aExprOrbitA));
        
        GExpr aExprOrbitB = GExpr::Symbol(pUnwindB);
        aExprOrbitB = GExpr::Xor(aExprOrbitB, RotMediumHighRandom(GExpr::Symbol(pPrevious)));
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Const64(pHotPack.mPair[aHotB].mAdd));
        aExprOrbitB = CreatePlug(aExprOrbitB, false, pRecipeSaltB, &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        auto aSaltPairC = MakeRandomLoopSaltPair();
        
        GExpr aExprOrbitC = GExpr::Symbol(pUnwindC);
        aExprOrbitC = GExpr::Add(aExprOrbitC, RotMediumHighRandom(GExpr::Symbol(pStreamCross)));
        aExprOrbitC = GExpr::Add(aExprOrbitC, aSaltPairC.first);
        aExprOrbitC = GExpr::Add(aExprOrbitC, aSaltPairC.second);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterC, aExprOrbitC));

        auto aSaltPairD = MakeRandomLoopSaltPair();
        
        GExpr aExprOrbitD = RotMediumHighRandom(GExpr::Symbol(pCarry));
        aExprOrbitD = GExpr::Xor(aExprOrbitD, RotMediumOrRandom(GExpr::Symbol(pCurrent)));
        aExprOrbitD = GExpr::Xor(aExprOrbitD, aSaltPairD.first);
        aExprOrbitD = GExpr::Xor(aExprOrbitD, aSaltPairD.second);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
        
        PrismSet(GExpr::Symbol(pCurrent));
        
        
        
    }
    
    {
        int aHotA = aHotIndex++;
        int aHotD = aHotIndex++;
        int aHotPrism = aHotIndex++;
        
        EmitComment("a = a + b + hot.add + plug[+];");
        EmitComment("d = d ^ a ^ hot.add ^ plug[^];");
        EmitComment("d = rot(d * hot.mul);");
        
        
        GExpr aExprOrbitA = GExpr::Symbol(pOrbiterA);
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Symbol(pOrbiterB));
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Const64(pHotPack.mPair[aHotA].mAdd));
        aExprOrbitA = CreatePlug(aExprOrbitA, true, PopRandomFixedSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterA, aExprOrbitA));
        
        GExpr aExprOrbitD = GExpr::Symbol(pOrbiterD);
        aExprOrbitD = GExpr::Xor(aExprOrbitD, GExpr::Symbol(pOrbiterA));
        aExprOrbitD = GExpr::Xor(aExprOrbitD, GExpr::Const64(pHotPack.mPair[aHotD].mAdd));
        aExprOrbitD = CreatePlug(aExprOrbitD, false, PopRandomFixedSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
        
        aExprOrbitD = GExpr::Mul(GExpr::Symbol(pOrbiterD), GExpr::Const64(pHotPack.mPair[aHotD].mMul));
        aExprOrbitD = RotMediumHighRandom(aExprOrbitD);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
        
        if (!pIgnorePrism) {
            GExpr aExprPrism = GExpr::Symbol(pPrism);
            GExpr aExprPrismTerm = BuildPrismTermExpr(0);
            
            if (aPrismAddCadence) {
                aExprPrism = GExpr::Add(aExprPrism, aExprPrismTerm);
                aExprPrism = GExpr::Add(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mAdd));
            } else {
                aExprPrism = GExpr::Xor(aExprPrism, aExprPrismTerm);
                aExprPrism = GExpr::Xor(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mAdd));
            }
            
            aPrismAddCadence = !aPrismAddCadence;
            
            aExprPrism = GExpr::Mul(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mMul));
            pStatements->push_back(GQuick::MakeAssignVariableStatement(pPrism, aExprPrism));
        }
        
        
        
        }
        
    {
        int aHotC = aHotIndex++;
        int aHotB = aHotIndex++;
        int aHotPrism = aHotIndex++;
        
        EmitComment("c = c + d + hot.add + plug[+];");
        EmitComment("b = b ^ c ^ hot.add ^ plug[^];");
        EmitComment("b = rot(b);");
        EmitComment("prism = (prism OP mix(a) OP hot.add) * hot.mul;");
        
        
        GExpr aExprOrbitC = GExpr::Symbol(pOrbiterC);
        aExprOrbitC = GExpr::Add(aExprOrbitC, GExpr::Symbol(pOrbiterD));
        aExprOrbitC = GExpr::Add(aExprOrbitC, GExpr::Const64(pHotPack.mPair[aHotC].mAdd));
        aExprOrbitC = CreatePlug(aExprOrbitC, true, PopRandomFixedSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterC, aExprOrbitC));
        
        GExpr aExprOrbitB = GExpr::Symbol(pOrbiterB);
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Symbol(pOrbiterC));
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Const64(pHotPack.mPair[aHotB].mAdd));
        aExprOrbitB = CreatePlug(aExprOrbitB, false, PopRandomFixedSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        aExprOrbitB = RotMediumHighRandom(GExpr::Symbol(pOrbiterB));
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        if (!pIgnorePrism) {
            GExpr aExprPrism = GExpr::Symbol(pPrism);
            GExpr aExprPrismTerm = BuildPrismTermExpr(1);
            
            if (aPrismAddCadence) {
                aExprPrism = GExpr::Add(aExprPrism, aExprPrismTerm);
                aExprPrism = GExpr::Add(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mAdd));
            } else {
                aExprPrism = GExpr::Xor(aExprPrism, aExprPrismTerm);
                aExprPrism = GExpr::Xor(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mAdd));
            }
            
            aPrismAddCadence = !aPrismAddCadence;
            
            aExprPrism = GExpr::Mul(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mMul));
            pStatements->push_back(GQuick::MakeAssignVariableStatement(pPrism, aExprPrism));
        }
        
        
        
    }
    
    {
        int aHotA = aHotIndex++;
        int aHotD = aHotIndex++;
        int aHotPrism = aHotIndex++;
        
        EmitComment("a = a + b + hot.add + plug[+];");
        EmitComment("d = d ^ a ^ hot.add ^ plug[^];");
        EmitComment("d = rot(d * hot.mul);");
        
        
        GExpr aExprOrbitA = GExpr::Symbol(pOrbiterA);
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Symbol(pOrbiterB));
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Const64(pHotPack.mPair[aHotA].mAdd));
        aExprOrbitA = CreatePlug(aExprOrbitA, true, PopRandomFixedSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterA, aExprOrbitA));
        
        GExpr aExprOrbitD = GExpr::Symbol(pOrbiterD);
        aExprOrbitD = GExpr::Xor(aExprOrbitD, GExpr::Symbol(pOrbiterA));
        aExprOrbitD = GExpr::Xor(aExprOrbitD, GExpr::Const64(pHotPack.mPair[aHotD].mAdd));
        aExprOrbitD = CreatePlug(aExprOrbitD, false, PopRandomFixedSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
        
        aExprOrbitD = GExpr::Mul(GExpr::Symbol(pOrbiterD), GExpr::Const64(pHotPack.mPair[aHotD].mMul));
        aExprOrbitD = RotMediumHighRandom(aExprOrbitD);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
        
        if (!pIgnorePrism) {
            GExpr aExprPrism = GExpr::Symbol(pPrism);
            GExpr aExprPrismTerm = BuildPrismTermExpr(2);
            
            if (aPrismAddCadence) {
                aExprPrism = GExpr::Add(aExprPrism, aExprPrismTerm);
                aExprPrism = GExpr::Add(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mAdd));
            } else {
                aExprPrism = GExpr::Xor(aExprPrism, aExprPrismTerm);
                aExprPrism = GExpr::Xor(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mAdd));
            }
            
            aPrismAddCadence = !aPrismAddCadence;
            
            aExprPrism = GExpr::Mul(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mMul));
            pStatements->push_back(GQuick::MakeAssignVariableStatement(pPrism, aExprPrism));
        }
        
        
        
    }
    
    {
        int aHotC = aHotIndex++;
        int aHotB = aHotIndex++;
        int aHotPrism = aHotIndex++;
        
        EmitComment("c = c + d + hot.add + plug[+];");
        EmitComment("b = b ^ c ^ hot.add ^ plug[^];");
        EmitComment("b = rot(b * hot.mul);");
        
        
        GExpr aExprOrbitC = GExpr::Symbol(pOrbiterC);
        aExprOrbitC = GExpr::Add(aExprOrbitC, GExpr::Symbol(pOrbiterD));
        aExprOrbitC = GExpr::Add(aExprOrbitC, GExpr::Const64(pHotPack.mPair[aHotC].mAdd));
        aExprOrbitC = CreatePlug(aExprOrbitC, true, PopRandomFixedSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterC, aExprOrbitC));
        
        GExpr aExprOrbitB = GExpr::Symbol(pOrbiterB);
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Symbol(pOrbiterC));
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Const64(pHotPack.mPair[aHotB].mAdd));
        aExprOrbitB = CreatePlug(aExprOrbitB, false, PopRandomFixedSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        aExprOrbitB = GExpr::Mul(GExpr::Symbol(pOrbiterB), GExpr::Const64(pHotPack.mPair[aHotB].mMul));
        aExprOrbitB = RotMediumHighRandom(aExprOrbitB);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        if (!pIgnorePrism) {
            GExpr aExprPrism = GExpr::Symbol(pPrism);
            GExpr aExprPrismTerm = BuildPrismTermExpr(3);
            
            if (aPrismAddCadence) {
                aExprPrism = GExpr::Add(aExprPrism, aExprPrismTerm);
                aExprPrism = GExpr::Add(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mAdd));
            } else {
                aExprPrism = GExpr::Xor(aExprPrism, aExprPrismTerm);
                aExprPrism = GExpr::Xor(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mAdd));
            }
            
            aPrismAddCadence = !aPrismAddCadence;
            
            aExprPrism = GExpr::Mul(aExprPrism, GExpr::Const64(pHotPack.mPair[aHotPrism].mMul));
            pStatements->push_back(GQuick::MakeAssignVariableStatement(pPrism, aExprPrism));
        }
        
        
        
    }
    
    
    {
        EmitComment("e = mix(a, b, c, d)");
        EmitComment("e = diffuse(e OP scatter)");
        
        if (pDestWriteInverted) {
            EmitComment("dest[~i] = e");
        } else {
            EmitComment("dest[i] = e");
        }
        
        
        
        GSymbol aMainUpdateComponentA;
        GSymbol aMainUpdateComponentB;
        GSymbol aMainUpdateComponentC;
        GSymbol aMainUpdateComponentD;
        
        if (Random::Bool()) {
            aMainUpdateComponentA = pOrbiterA;
            aMainUpdateComponentB = pOrbiterB;
            aMainUpdateComponentC = pOrbiterC;
            aMainUpdateComponentD = pOrbiterD;
        } else {
            aMainUpdateComponentA = pOrbiterA;
            aMainUpdateComponentB = pOrbiterD;
            aMainUpdateComponentC = pOrbiterB;
            aMainUpdateComponentD = pOrbiterC;
        }
        
        GExpr aMainUpdateExprA = GExpr::Symbol(aMainUpdateComponentA);
        GExpr aMainUpdateExprB = GExpr::Symbol(aMainUpdateComponentB);
        GExpr aMainUpdateExprC = GExpr::Symbol(aMainUpdateComponentC);
        GExpr aMainUpdateExprD = GExpr::Symbol(aMainUpdateComponentD);
        
        if (Random::Bool()) {
            aMainUpdateExprA = RotMedium(GExpr::Symbol(aMainUpdateComponentA));
        } else {
            aMainUpdateExprB = RotMedium(GExpr::Symbol(aMainUpdateComponentB));
        }
        
        if (Random::Bool()) {
            aMainUpdateExprC = RotMedium(GExpr::Symbol(aMainUpdateComponentC));
        } else {
            aMainUpdateExprD = RotMedium(GExpr::Symbol(aMainUpdateComponentD));
        }
        
        GExpr aMainUpdateExprHalfA = GExpr::Xor(aMainUpdateExprA, aMainUpdateExprB);
        GExpr aMainUpdateExprHalfB = GExpr::Xor(aMainUpdateExprC, aMainUpdateExprD);
        GExpr aMainUpdateExpr = GExpr::Add(aMainUpdateExprHalfA, aMainUpdateExprHalfB);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pCurrent, aMainUpdateExpr));
        
        if (Random::Bool()) {
            aMainUpdateExpr = GExpr::Xor(GExpr::Symbol(pCurrent), GExpr::Symbol(pScatter));
        } else {
            aMainUpdateExpr = GExpr::Add(GExpr::Symbol(pCurrent), GExpr::Symbol(pScatter));
        }
        
        aMainUpdateExpr = DiffuseRandom(aMainUpdateExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pCurrent, aMainUpdateExpr));
        
        if (pDestWriteInverted) {
            pStatements->push_back(GQuick::MakeAssignDestStatementInverted(pDest, pLoopIndex, pCurrent));
        } else {
            pStatements->push_back(GQuick::MakeAssignDestStatement(pDest, pLoopIndex, pCurrent));
        }
        
        
        
    }
    
    if (!pIgnorePrism) {
        std::vector<GStatement> aTempStatements;
        
        EmitComment("prism = diffuse(prism)");
        EmitComment("feedback gate: e = gate(e, prism)");
        
        
        PrismDiffuse();
        
        auto aSBoxes = FetchSBoxPack8();
        GSymbol aSBoxA = aSBoxes[0];
        GSymbol aSBoxB = aSBoxes[1];
        GSymbol aSBoxC = aSBoxes[2];
        GSymbol aSBoxD = aSBoxes[3];
        GSymbol aSBoxE = aSBoxes[4];
        GSymbol aSBoxF = aSBoxes[5];
        GSymbol aSBoxG = aSBoxes[6];
        GSymbol aSBoxH = aSBoxes[7];
        
        std::vector<GSymbol> aSBoxesBase;
        aSBoxesBase.push_back(aSBoxA);
        aSBoxesBase.push_back(aSBoxB);
        aSBoxesBase.push_back(aSBoxC);
        aSBoxesBase.push_back(aSBoxD);
        aSBoxesBase.push_back(aSBoxE);
        aSBoxesBase.push_back(aSBoxF);
        aSBoxesBase.push_back(aSBoxG);
        aSBoxesBase.push_back(aSBoxH);
        
        std::vector<GSymbol> aSBoxesPermutationA = aSBoxesBase;
        std::vector<GSymbol> aSBoxesPermutationB = aSBoxesBase;
        std::vector<GSymbol> aSBoxesPermutationC = aSBoxesBase;
        std::vector<GSymbol> aSBoxesPermutationD = aSBoxesBase;
        Random::Shuffle(&aSBoxesPermutationA);
        Random::Shuffle(&aSBoxesPermutationB);
        Random::Shuffle(&aSBoxesPermutationC);
        Random::Shuffle(&aSBoxesPermutationD);
        
        const int aCaseCount = 2 + Random::Get(3); // 2, 3, or 4
        aMix648Cache.Fetch(aCaseCount);
        
        auto MakeMixOptionFromPermutation = [&](int pMixIndex, const std::vector<GSymbol> &pPermutation) -> GExpr {
            return GExpr::Mix64_8(GExpr::Symbol(pCurrent),
                                  aMix648Cache.mBus[pMixIndex],
                                  static_cast<std::uint64_t>(PopRandomRotation()),
                                  pPermutation[0], pPermutation[1], pPermutation[2], pPermutation[3],
                                  pPermutation[4], pPermutation[5], pPermutation[6], pPermutation[7]);
        };
        
        GExpr aMixOptionA = MakeMixOptionFromPermutation(0, aSBoxesPermutationA);
        GExpr aMixOptionB = MakeMixOptionFromPermutation(1, aSBoxesPermutationB);
        GStatement aMixStatementA = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionA);
        GStatement aMixStatementB = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionB);
        
        GSelect aSelect = (aCaseCount == 2) ? GSelect::Random2() : GSelect::Random4();
        aSelect.AddStatementA(aMixStatementA);
        aSelect.AddStatementB(aMixStatementB);
        
        if (aCaseCount >= 3) {
            GExpr aMixOptionC = MakeMixOptionFromPermutation(2, aSBoxesPermutationC);
            GStatement aMixStatementC = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionC);
            aSelect.AddStatementC(aMixStatementC);
        }
        
        if (aCaseCount >= 4) {
            GExpr aMixOptionD = MakeMixOptionFromPermutation(3, aSBoxesPermutationD);
            GStatement aMixStatementD = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionD);
            aSelect.AddStatementD(aMixStatementD);
        }
        
        if (!aSelect.Bake(pPrism, &aTempStatements, pErrorMessage)) {
            printf("CSPRNG failed to bake feedback gate select 8-box (%d case): %s\n",
                   aCaseCount,
                   pErrorMessage->c_str());
            return false;
        }
        
        TwistArray::Append(pStatements, &aTempStatements);
        aTempStatements.clear();
        
        
    }
    
    {
        int aHotS0 = aHotIndex++;
        
        EmitComment("s0 = s0 + (e ^ previous ^ d);");
        EmitComment("s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);");
        
        
        GExpr aFeedbackFresh = GExpr::Symbol(pCurrent);
        GExpr aFeedbackPrevious = GExpr::Symbol(pPrevious);
        GExpr aFeedbackD = GExpr::Symbol(pOrbiterD);
        
        int aRotateFeedbackTerm = Random::Get(3);
        if (aRotateFeedbackTerm == 0) {
            aFeedbackFresh = RotMediumHighRandom(aFeedbackFresh);
        } else if (aRotateFeedbackTerm == 1) {
            aFeedbackPrevious = RotMostlyMedium(aFeedbackPrevious);
        } else {
            aFeedbackD = RotMediumHighRandom(aFeedbackD);
        }
        
        GExpr aFeedbackExpr = GExpr::Xor(aFeedbackFresh, GExpr::Xor(aFeedbackPrevious, aFeedbackD));
        
        GExpr aExprUnwindA = GExpr::Add(GExpr::Symbol(pUnwindA), aFeedbackExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pUnwindA, aExprUnwindA));
        
        GSymbol aLoopSalt = PopRandomFixedSalt();
        GExpr aLoopSaltExpr;
        
        if (Random::Bool()) {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpression(aLoopSalt, pLoopIndex);
        } else {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(aLoopSalt, pLoopIndex);
        }
        
        aExprUnwindA = GExpr::Add(GExpr::Symbol(pUnwindA), aLoopSaltExpr);
        aExprUnwindA = GExpr::Mul(aExprUnwindA, GExpr::Const64(pHotPack.mPair[aHotS0].mMul));
        aExprUnwindA = RotMediumHigh(aExprUnwindA);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pUnwindA, aExprUnwindA));
        
        
        
    }
    
    {
        int aHotS1 = aHotIndex++;
        
        EmitComment("s1 = s1 ^ (e + cross + a);");
        EmitComment("s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);");
        
        
        GExpr aFeedbackFresh = GExpr::Symbol(pCurrent);
        GExpr aFeedbackCross = GExpr::Symbol(pStreamCross);
        GExpr aFeedbackA = GExpr::Symbol(pOrbiterA);
        
        int aRotateFeedbackTerm = Random::Get(3);
        if (aRotateFeedbackTerm == 0) {
            aFeedbackFresh = RotMediumHighRandom(aFeedbackFresh);
        } else if (aRotateFeedbackTerm == 1) {
            aFeedbackCross = RotMostlyMedium(aFeedbackCross);
        } else {
            aFeedbackA = RotMediumHighRandom(aFeedbackA);
        }
        
        GExpr aFeedbackExpr = GExpr::Add(aFeedbackFresh, GExpr::Add(aFeedbackCross, aFeedbackA));
        
        GExpr aExprUnwindB = GExpr::Xor(GExpr::Symbol(pUnwindB), aFeedbackExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pUnwindB, aExprUnwindB));
        
        GSymbol aLoopSalt = PopRandomFixedSalt();
        GExpr aLoopSaltExpr;
        
        if (Random::Bool()) {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpression(aLoopSalt, pLoopIndex);
        } else {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(aLoopSalt, pLoopIndex);
        }
        
        aExprUnwindB = GExpr::Xor(GExpr::Symbol(pUnwindB), aLoopSaltExpr);
        aExprUnwindB = GExpr::Mul(aExprUnwindB, GExpr::Const64(pHotPack.mPair[aHotS1].mMul));
        aExprUnwindB = RotMediumHigh(aExprUnwindB);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pUnwindB, aExprUnwindB));
    }
    
    {
        int aHotS2 = aHotIndex++;
        
        EmitComment("s2 = s2 + (b ^ c ^ loopSalt[i/~i]);");
        EmitComment("s2 = rot(s2 * hot.mul);");
        
        
        GExpr aFeedbackB = GExpr::Symbol(pOrbiterB);
        GExpr aFeedbackC = GExpr::Symbol(pOrbiterC);
        
        int aRotateFeedbackTerm = Random::Get(2);
        if (aRotateFeedbackTerm == 0) {
            aFeedbackB = RotMediumHighRandom(aFeedbackB);
        } else {
            aFeedbackC = RotMediumHighRandom(aFeedbackC);
        }
        
        GSymbol aLoopSalt = PopRandomFixedSalt();
        GExpr aLoopSaltExpr;
        
        if (Random::Bool()) {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpression(aLoopSalt, pLoopIndex);
        } else {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(aLoopSalt, pLoopIndex);
        }
        
        GExpr aFeedbackExpr = GExpr::Xor(aFeedbackB, GExpr::Xor(aFeedbackC, aLoopSaltExpr));
        
        GExpr aExprUnwindC = GExpr::Add(GExpr::Symbol(pUnwindC), aFeedbackExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pUnwindC, aExprUnwindC));
        
        aExprUnwindC = GExpr::Mul(GExpr::Symbol(pUnwindC), GExpr::Const64(pHotPack.mPair[aHotS2].mMul));
        aExprUnwindC = RotMediumHigh(aExprUnwindC);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pUnwindC, aExprUnwindC));
        
        
        
    }
    
    {
        int aHotCarry = aHotIndex++;
        
        EmitComment("carry = carry + (s0 ^ s1 ^ s2 ^ e);");
        EmitComment("carry = rot(carry * hot.mul);");
        EmitComment("carry = carry ^ (carry >> rshift);");
        
        
        GExpr aFeedbackS0 = GExpr::Symbol(pUnwindA);
        GExpr aFeedbackS1 = GExpr::Symbol(pUnwindB);
        GExpr aFeedbackS2 = GExpr::Symbol(pUnwindC);
        GExpr aFeedbackE = GExpr::Symbol(pCurrent);
        
        int aRotateFeedbackTerm = Random::Get(4);
        if (aRotateFeedbackTerm == 0) {
            aFeedbackS0 = RotMostlyMedium(aFeedbackS0);
        } else if (aRotateFeedbackTerm == 1) {
            aFeedbackS1 = RotMostlyMedium(aFeedbackS1);
        } else if (aRotateFeedbackTerm == 2) {
            aFeedbackS2 = RotMostlyMedium(aFeedbackS2);
        } else {
            aFeedbackE = RotMostlyMedium(aFeedbackE);
        }
        
        GExpr aFeedbackExpr = GExpr::Xor(aFeedbackS0,
                                         GExpr::Xor(aFeedbackS1,
                                                    GExpr::Xor(aFeedbackS2, aFeedbackE)));
        
        GExpr aExprCarry = GExpr::Add(GExpr::Symbol(pCarry), aFeedbackExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pCarry, aExprCarry));
        
        aExprCarry = GExpr::Mul(GExpr::Symbol(pCarry), GExpr::Const64(pHotPack.mPair[aHotCarry].mMul));
        aExprCarry = RotMediumHigh(aExprCarry);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pCarry, aExprCarry));
        
        std::vector<int> aCarryShifts = { 23, 27, 29, 31, 33, 37, 41, 43, 47 };
        
        aExprCarry = GExpr::Xor(GExpr::Symbol(pCarry),
                                GExpr::ShiftR(GExpr::Symbol(pCarry), GExpr::Const64(Random::Choice(aCarryShifts))));
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pCarry, aExprCarry));
    }
    
    return true;
    
}
