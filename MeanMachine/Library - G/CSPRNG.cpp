//
//  CSPRNG.cpp
//  MeanMachine
//
//  Created by Dragon on 5/2/26.
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
            return GExpr::Symbol(mCross);
        case CSPRNGPlugMode::kCarry:
            return GExpr::Symbol(mCarry);
        case CSPRNGPlugMode::kWandererA:
            return GExpr::Symbol(mWandererA);
        case CSPRNGPlugMode::kWandererB:
            return GExpr::Symbol(mWandererB);
        case CSPRNGPlugMode::kWandererC:
            return GExpr::Symbol(mWandererC);
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
    TryAddMode(CSPRNGPlugMode::kWandererA);
    TryAddMode(CSPRNGPlugMode::kWandererB);
    TryAddMode(CSPRNGPlugMode::kWandererC);
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
    if (IsPair(pPlugModeA, pPlugModeB, CSPRNGPlugMode::kOrbiterA, CSPRNGPlugMode::kWandererA)) {
        return true;
    }
    
    if (IsPair(pPlugModeA, pPlugModeB, CSPRNGPlugMode::kOrbiterB, CSPRNGPlugMode::kWandererB)) {
        return true;
    }
    
    if (IsPair(pPlugModeA, pPlugModeB, CSPRNGPlugMode::kOrbiterC, CSPRNGPlugMode::kWandererC)) {
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
                  GSymbol pScatter,
                  
                  GSymbol pCross,
                  GSymbol pCarry,
                  
                  GSymbol pWandererA,
                  GSymbol pWandererB,
                  GSymbol pWandererC,
                  
                  GSymbol pOrbiterA,
                  GSymbol pOrbiterB,
                  GSymbol pOrbiterC,
                  GSymbol pOrbiterD,
                  
                  std::vector<GSymbol> pSBoxes,
                  std::vector<GSymbol> pSaltsFixed,
                  std::vector<GSymbol> pSaltsScratch,
                  
                  std::vector<int> pRotationsLow,
                  std::vector<int> pRotationsMedium,
                  std::vector<int> pRotationsHigh,
                  std::vector<int> pRotationsRandom,
                  
                  std::vector<Mix64Type_4> pMixTypes4,
                  std::vector<Mix64Type_8> pMixTypes8,
                  
                  GHotPack pHotPack,
                  
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) {
    
    std::deque<CSPRNGPlugMode> aRecentPlugDeque;
    
    int aHotIndex = 0;
    
    CSPRNGPlugPack aPlugPack;
    aPlugPack.mInput = pCurrent;
    aPlugPack.mPrevious = pPrevious;
    aPlugPack.mScatter = pScatter;
    aPlugPack.mCross = pCross;
    aPlugPack.mCarry = pCarry;
    aPlugPack.mWandererA = pWandererA;
    aPlugPack.mWandererB = pWandererB;
    aPlugPack.mWandererC = pWandererC;
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
    
    GMix644Cache aMix644Cache;
    aMix644Cache.AddItems(pMixTypes4);
    aMix644Cache.SetLimits(2, 3, 4);
    
    GMix648Cache aMix648Cache;
    aMix648Cache.AddItems(pMixTypes8);
    aMix648Cache.SetLimits(2, 2, 2);
    
    GSymbolCache aSaltCacheScratch;
    for (int i=0; i<pSaltsScratch.size(); i++) {
        aSaltCacheScratch.AddItem(&(pSaltsScratch[i]));
    }
    aSaltCacheScratch.SetLimits(2, 3, 4);
    
    GSymbolCache aSaltCacheFixed;
    for (int i=0; i<pSaltsFixed.size(); i++) {
        aSaltCacheFixed.AddItem(&(pSaltsFixed[i]));
    }
    if (pSaltsFixed.size() <= 4) {
        aSaltCacheFixed.SetLimits(4, 4, 4);
    } else {
        aSaltCacheFixed.SetLimits(2, 4, 6);
    }
    
    GSymbolCache aSBoxCache;
    for (int i=0; i<pSBoxes.size(); i++) {
        aSBoxCache.AddItem(&(pSBoxes[i]));
    }
    if (pSaltsFixed.size() <= 4) {
        aSBoxCache.SetLimits(2, 3, 4);
    } else {
        aSBoxCache.SetLimits(4, 6, 8);
    }
    
    auto PopRandomScratchSalt = [&]() -> GSymbol {
        aSaltCacheScratch.Fetch(1);
        return *(aSaltCacheScratch.mBus[0]);
    };
    
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
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pPrism, pExpr));
    };

    auto PrismDiffuse = [&]() {
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pPrism, DiffuseRandom(GExpr::Symbol(pPrism))));
    };
    
    bool aPrismAddCadence = Random::Bool();

    
    auto PrismTerm = [&](GSymbol pSymbol) -> GExpr {
        int aWhich = Random::Get(4);
        
        if (aWhich == 0) {
            return GExpr::Symbol(pSymbol);
        } else if (aWhich == 1) {
            return RotMostlyMedium(GExpr::Symbol(pSymbol));
        } else if (aWhich == 2) {
            return RotMediumHighRandom(GExpr::Symbol(pSymbol));
        }
        
        return GExpr::Xor(GExpr::Symbol(pSymbol), RotMostlyMedium(GExpr::Symbol(pCarry)));
    };

    auto FetchSBoxPack4 = [&]() -> std::array<GSymbol, 4> {
        aSBoxCache.Fetch(4);
        
        return {
            *(aSBoxCache.mBus[0]),
            *(aSBoxCache.mBus[1]),
            *(aSBoxCache.mBus[2]),
            *(aSBoxCache.mBus[3])
        };
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
        GExpr aScratchSaltExpr;
        
        if (Random::Bool()) {
            aFixedSaltExpr = GQuick::MakeReadBufferOffsetExpression(
                PopRandomFixedSalt(),
                pLoopIndex
            );
            
            aScratchSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(
                PopRandomScratchSalt(),
                pLoopIndex
            );
        } else {
            aFixedSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(
                PopRandomFixedSalt(),
                pLoopIndex
            );
            
            aScratchSaltExpr = GQuick::MakeReadBufferOffsetExpression(
                PopRandomScratchSalt(),
                pLoopIndex
            );
        }
        
        return { aFixedSaltExpr, aScratchSaltExpr };
    };
    
    
    {
        
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("scatter = mix(secure_a, secure_b, previous)"));
        pStatements->push_back(GStatement::Comment(""));
        
        GExpr aMainSnowPartA;
        GExpr aMainSnowPartB;
        GExpr aMainSnowPartC;
        int aWhichMainSnow = Random::Get(2);
        if (aWhichMainSnow == 0) {
            aMainSnowPartA = GExpr::ShiftL(GExpr::Symbol(pCurrent), GExpr::Const64(32));
            aMainSnowPartB = GExpr::Symbol(pCross);
            aMainSnowPartC = GExpr::RotL64(GExpr::Symbol(pPrevious), GExpr::Const64(PopMediumRotation()));
        } else {
            aMainSnowPartA = GExpr::Symbol(pCurrent);
            aMainSnowPartB = GExpr::ShiftL(GExpr::Symbol(pCross), GExpr::Const64(32));
            aMainSnowPartC = GExpr::RotL64(GExpr::Symbol(pPrevious), GExpr::Const64(PopMediumRotation()));
        }
        GExpr aMainSnowGuts = GExpr::Xor(aMainSnowPartA, GExpr::Xor(aMainSnowPartB, aMainSnowPartC));
        GExpr aMainSnow = GExpr::DiffuseA(aMainSnowGuts);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pScatter, aMainSnow));
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    {
        int aHotA = aHotIndex++;
        int aHotB = aHotIndex++;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("a = s0 + rot(e) + hot.add + plug[+];"));
        pStatements->push_back(GStatement::Comment("b = s1 ^ rot(previous) ^ hot.add ^ plug[^];"));
        pStatements->push_back(GStatement::Comment("c = s2 + rot(cross) + fixedSalt[i/~i] + scratchSalt[~i/i];"));
        pStatements->push_back(GStatement::Comment("d = rot(carry) ^ rot(e) ^ fixedSalt[i/~i] ^ scratchSalt[~i/i];"));
        pStatements->push_back(GStatement::Comment("prism = e;"));
        pStatements->push_back(GStatement::Comment(""));
        GExpr aExprOrbitA = GExpr::Symbol(pWandererA);
        aExprOrbitA = GExpr::Add(aExprOrbitA, RotMostlyMedium(GExpr::Symbol(pCurrent)));
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Const64(pHotPack.mPair[aHotA].mAdd));
        aExprOrbitA = CreatePlug(aExprOrbitA, true, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterA, aExprOrbitA));
        
        GExpr aExprOrbitB = GExpr::Symbol(pWandererB);
        aExprOrbitB = GExpr::Xor(aExprOrbitB, RotMediumHighRandom(GExpr::Symbol(pPrevious)));
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Const64(pHotPack.mPair[aHotB].mAdd));
        aExprOrbitB = CreatePlug(aExprOrbitB, false, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        auto aSaltPairC = MakeRandomLoopSaltPair();
        
        GExpr aExprOrbitC = GExpr::Symbol(pWandererC);
        aExprOrbitC = GExpr::Add(aExprOrbitC, RotMediumHighRandom(GExpr::Symbol(pCross)));
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
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    {
        int aHotA = aHotIndex++;
        int aHotD = aHotIndex++;
        int aHotPrism = aHotIndex++;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("a = a + b + hot.add + plug[+];"));
        pStatements->push_back(GStatement::Comment("d = d ^ a ^ hot.add ^ plug[^];"));
        pStatements->push_back(GStatement::Comment("d = rot(d * hot.mul);"));
        pStatements->push_back(GStatement::Comment("prism = (prism OP mix(c) OP hot.add) * hot.mul;"));
        pStatements->push_back(GStatement::Comment(""));
        
        GExpr aExprOrbitA = GExpr::Symbol(pOrbiterA);
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Symbol(pOrbiterB));
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Const64(pHotPack.mPair[aHotA].mAdd));
        aExprOrbitA = CreatePlug(aExprOrbitA, true, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterA, aExprOrbitA));
        
        GExpr aExprOrbitD = GExpr::Symbol(pOrbiterD);
        aExprOrbitD = GExpr::Xor(aExprOrbitD, GExpr::Symbol(pOrbiterA));
        aExprOrbitD = GExpr::Xor(aExprOrbitD, GExpr::Const64(pHotPack.mPair[aHotD].mAdd));
        aExprOrbitD = CreatePlug(aExprOrbitD, false, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
        
        aExprOrbitD = GExpr::Mul(GExpr::Symbol(pOrbiterD), GExpr::Const64(pHotPack.mPair[aHotD].mMul));
        aExprOrbitD = RotMediumHighRandom(aExprOrbitD);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
        
        GExpr aExprPrism = GExpr::Symbol(pPrism);
        GExpr aExprPrismTerm = PrismTerm(pOrbiterC);
        
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
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    {
        int aHotC = aHotIndex++;
        int aHotB = aHotIndex++;
        int aHotPrism = aHotIndex++;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("c = c + d + hot.add + plug[+];"));
        pStatements->push_back(GStatement::Comment("b = b ^ c ^ hot.add ^ plug[^];"));
        pStatements->push_back(GStatement::Comment("b = rot(b);"));
        pStatements->push_back(GStatement::Comment("prism = (prism OP mix(a) OP hot.add) * hot.mul;"));
        pStatements->push_back(GStatement::Comment(""));
        
        GExpr aExprOrbitC = GExpr::Symbol(pOrbiterC);
        aExprOrbitC = GExpr::Add(aExprOrbitC, GExpr::Symbol(pOrbiterD));
        aExprOrbitC = GExpr::Add(aExprOrbitC, GExpr::Const64(pHotPack.mPair[aHotC].mAdd));
        aExprOrbitC = CreatePlug(aExprOrbitC, true, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterC, aExprOrbitC));
        
        GExpr aExprOrbitB = GExpr::Symbol(pOrbiterB);
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Symbol(pOrbiterC));
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Const64(pHotPack.mPair[aHotB].mAdd));
        aExprOrbitB = CreatePlug(aExprOrbitB, false, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        aExprOrbitB = RotMediumHighRandom(GExpr::Symbol(pOrbiterB));
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        GExpr aExprPrism = GExpr::Symbol(pPrism);
        GExpr aExprPrismTerm = PrismTerm(pOrbiterA);
        
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
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    //TODO: Remove after wider hot pairs
    aHotIndex = 0;

    {
        int aHotA = aHotIndex++;
        int aHotD = aHotIndex++;
        int aHotPrism = aHotIndex++;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("a = a + b + hot.add + plug[+];"));
        pStatements->push_back(GStatement::Comment("d = d ^ a ^ hot.add ^ plug[^];"));
        pStatements->push_back(GStatement::Comment("d = rot(d * hot.mul);"));
        pStatements->push_back(GStatement::Comment("prism = (prism OP mix(b) OP hot.add) * hot.mul;"));
        pStatements->push_back(GStatement::Comment(""));
        
        GExpr aExprOrbitA = GExpr::Symbol(pOrbiterA);
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Symbol(pOrbiterB));
        aExprOrbitA = GExpr::Add(aExprOrbitA, GExpr::Const64(pHotPack.mPair[aHotA].mAdd));
        aExprOrbitA = CreatePlug(aExprOrbitA, true, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterA, aExprOrbitA));
        
        GExpr aExprOrbitD = GExpr::Symbol(pOrbiterD);
        aExprOrbitD = GExpr::Xor(aExprOrbitD, GExpr::Symbol(pOrbiterA));
        aExprOrbitD = GExpr::Xor(aExprOrbitD, GExpr::Const64(pHotPack.mPair[aHotD].mAdd));
        aExprOrbitD = CreatePlug(aExprOrbitD, false, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
        
        aExprOrbitD = GExpr::Mul(GExpr::Symbol(pOrbiterD), GExpr::Const64(pHotPack.mPair[aHotD].mMul));
        aExprOrbitD = RotMediumHighRandom(aExprOrbitD);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
        
        GExpr aExprPrism = GExpr::Symbol(pPrism);
        GExpr aExprPrismTerm = PrismTerm(pOrbiterB);
        
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
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    {
        int aHotC = aHotIndex++;
        int aHotB = aHotIndex++;
        int aHotPrism = aHotIndex++;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("c = c + d + hot.add + plug[+];"));
        pStatements->push_back(GStatement::Comment("b = b ^ c ^ hot.add ^ plug[^];"));
        pStatements->push_back(GStatement::Comment("b = rot(b * hot.mul);"));
        pStatements->push_back(GStatement::Comment("prism = (prism OP mix(d) OP hot.add) * hot.mul;"));
        pStatements->push_back(GStatement::Comment(""));
        
        GExpr aExprOrbitC = GExpr::Symbol(pOrbiterC);
        aExprOrbitC = GExpr::Add(aExprOrbitC, GExpr::Symbol(pOrbiterD));
        aExprOrbitC = GExpr::Add(aExprOrbitC, GExpr::Const64(pHotPack.mPair[aHotC].mAdd));
        aExprOrbitC = CreatePlug(aExprOrbitC, true, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterC, aExprOrbitC));
        
        GExpr aExprOrbitB = GExpr::Symbol(pOrbiterB);
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Symbol(pOrbiterC));
        aExprOrbitB = GExpr::Xor(aExprOrbitB, GExpr::Const64(pHotPack.mPair[aHotB].mAdd));
        aExprOrbitB = CreatePlug(aExprOrbitB, false, PopRandomScratchSalt(), &aRotCacheMedium, &aPlugPack, &aRecentPlugDeque);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        aExprOrbitB = GExpr::Mul(GExpr::Symbol(pOrbiterB), GExpr::Const64(pHotPack.mPair[aHotB].mMul));
        aExprOrbitB = RotMediumHighRandom(aExprOrbitB);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB));
        
        GExpr aExprPrism = GExpr::Symbol(pPrism);
        GExpr aExprPrismTerm = PrismTerm(pOrbiterD);
        
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
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    
    {
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("e = mix(a, b, c, d)"));
        pStatements->push_back(GStatement::Comment("e = diffuse(e OP scatter)"));
        
        if (pDestWriteInverted) {
            pStatements->push_back(GStatement::Comment("dest[~i] = e"));
        } else {
            pStatements->push_back(GStatement::Comment("dest[i] = e"));
        }
        
        pStatements->push_back(GStatement::Comment(""));
        
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
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    {
        std::vector<GStatement> aTempStatements;
        GStatement aStatement;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("prism = diffuse(prism)"));
        pStatements->push_back(GStatement::Comment("feedback gate: e = gate(e, prism)"));
        pStatements->push_back(GStatement::Comment(""));
        
        PrismDiffuse();
        
        
        {
            std::vector<GStatement> aTempStatements;
            
            pStatements->push_back(GStatement::Comment(""));
            pStatements->push_back(GStatement::Comment("prism = diffuse(prism)"));
            pStatements->push_back(GStatement::Comment("feedback gate: e = gate(e, prism)"));
            pStatements->push_back(GStatement::Comment(""));
            
            PrismDiffuse();
            
            if ((pSBoxes.size() >= 8) && (pMixTypes8.size() > 0)) {
                auto aSBoxes = FetchSBoxPack8();
                GSymbol aSBoxA = aSBoxes[0];
                GSymbol aSBoxB = aSBoxes[1];
                GSymbol aSBoxC = aSBoxes[2];
                GSymbol aSBoxD = aSBoxes[3];
                GSymbol aSBoxE = aSBoxes[4];
                GSymbol aSBoxF = aSBoxes[5];
                GSymbol aSBoxG = aSBoxes[6];
                GSymbol aSBoxH = aSBoxes[7];
                
                if (Random::Bool()) {
                    aMix648Cache.Fetch(2);
                    
                    GExpr aMixOptionA = GExpr::Mix64_8(GExpr::Symbol(pCurrent), aMix648Cache.mBus[0],
                                                       (std::uint64_t)PopRandomRotation(),
                                                       aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                                       aSBoxE, aSBoxF, aSBoxG, aSBoxH);
                    GExpr aMixOptionB = GExpr::Mix64_8(GExpr::Symbol(pCurrent), aMix648Cache.mBus[1],
                                                       (std::uint64_t)PopRandomRotation(),
                                                       aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                                       aSBoxE, aSBoxF, aSBoxG, aSBoxH);
                    
                    GStatement aMixStatementA = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionA);
                    GStatement aMixStatementB = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionB);
                    
                    GSelect aSelect = GSelect::Random2();
                    aSelect.AddStatementA(aMixStatementA);
                    aSelect.AddStatementB(aMixStatementB);
                    
                    if (!aSelect.Bake(pPrism, &aTempStatements, pErrorMessage)) {
                        printf("CSPRNG failed to bake feedback gate select 8-box (2 case): %s\n", pErrorMessage->c_str());
                        return false;
                    }
                    
                    TwistArray::Append(pStatements, &aTempStatements);
                    aTempStatements.clear();
                } else {
                    aMix648Cache.Fetch(4);
                    
                    GExpr aMixOptionA = GExpr::Mix64_8(GExpr::Symbol(pCurrent), aMix648Cache.mBus[0],
                                                       (std::uint64_t)PopRandomRotation(),
                                                       aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                                       aSBoxE, aSBoxF, aSBoxG, aSBoxH);
                    GExpr aMixOptionB = GExpr::Mix64_8(GExpr::Symbol(pCurrent), aMix648Cache.mBus[1],
                                                       (std::uint64_t)PopRandomRotation(),
                                                       aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                                       aSBoxE, aSBoxF, aSBoxG, aSBoxH);
                    GExpr aMixOptionC = GExpr::Mix64_8(GExpr::Symbol(pCurrent), aMix648Cache.mBus[2],
                                                       (std::uint64_t)PopRandomRotation(),
                                                       aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                                       aSBoxE, aSBoxF, aSBoxG, aSBoxH);
                    GExpr aMixOptionD = GExpr::Mix64_8(GExpr::Symbol(pCurrent), aMix648Cache.mBus[3],
                                                       (std::uint64_t)PopRandomRotation(),
                                                       aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                                       aSBoxE, aSBoxF, aSBoxG, aSBoxH);
                    
                    GStatement aMixStatementA = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionA);
                    GStatement aMixStatementB = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionB);
                    GStatement aMixStatementC = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionC);
                    GStatement aMixStatementD = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionD);
                    
                    GSelect aSelect = GSelect::Random4();
                    aSelect.AddStatementA(aMixStatementA);
                    aSelect.AddStatementB(aMixStatementB);
                    aSelect.AddStatementC(aMixStatementC);
                    aSelect.AddStatementD(aMixStatementD);
                    
                    if (!aSelect.Bake(pPrism, &aTempStatements, pErrorMessage)) {
                        printf("CSPRNG failed to bake feedback gate select 8-box (4 case): %s\n", pErrorMessage->c_str());
                        return false;
                    }
                    
                    TwistArray::Append(pStatements, &aTempStatements);
                    aTempStatements.clear();
                }
            } else {
                auto aSBoxes = FetchSBoxPack4();
                GSymbol aSBoxA = aSBoxes[0];
                GSymbol aSBoxB = aSBoxes[1];
                GSymbol aSBoxC = aSBoxes[2];
                GSymbol aSBoxD = aSBoxes[3];
                
                if (Random::Bool()) {
                    aMix644Cache.Fetch(2);
                    
                    GExpr aMixOptionA = GExpr::Mix64_4(GExpr::Symbol(pCurrent), aMix644Cache.mBus[0],
                                                       (std::uint64_t)PopRandomRotation(), aSBoxA, aSBoxB, aSBoxC, aSBoxD);
                    GExpr aMixOptionB = GExpr::Mix64_4(GExpr::Symbol(pCurrent), aMix644Cache.mBus[1],
                                                       (std::uint64_t)PopRandomRotation(), aSBoxA, aSBoxB, aSBoxC, aSBoxD);
                    
                    GStatement aMixStatementA = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionA);
                    GStatement aMixStatementB = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionB);
                    
                    GSelect aSelect = GSelect::Random2();
                    aSelect.AddStatementA(aMixStatementA);
                    aSelect.AddStatementB(aMixStatementB);
                    
                    if (!aSelect.Bake(pPrism, &aTempStatements, pErrorMessage)) {
                        printf("CSPRNG failed to bake feedback gate select 4-box (2 case): %s\n", pErrorMessage->c_str());
                        return false;
                    }
                    
                    TwistArray::Append(pStatements, &aTempStatements);
                    aTempStatements.clear();
                } else {
                    aMix644Cache.Fetch(4);
                    
                    GExpr aMixOptionA = GExpr::Mix64_4(GExpr::Symbol(pCurrent), aMix644Cache.mBus[0],
                                                       (std::uint64_t)PopRandomRotation(), aSBoxA, aSBoxB, aSBoxC, aSBoxD);
                    GExpr aMixOptionB = GExpr::Mix64_4(GExpr::Symbol(pCurrent), aMix644Cache.mBus[1],
                                                       (std::uint64_t)PopRandomRotation(), aSBoxA, aSBoxB, aSBoxC, aSBoxD);
                    GExpr aMixOptionC = GExpr::Mix64_4(GExpr::Symbol(pCurrent), aMix644Cache.mBus[2],
                                                       (std::uint64_t)PopRandomRotation(), aSBoxA, aSBoxB, aSBoxC, aSBoxD);
                    GExpr aMixOptionD = GExpr::Mix64_4(GExpr::Symbol(pCurrent), aMix644Cache.mBus[3],
                                                       (std::uint64_t)PopRandomRotation(), aSBoxA, aSBoxB, aSBoxC, aSBoxD);
                    
                    GStatement aMixStatementA = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionA);
                    GStatement aMixStatementB = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionB);
                    GStatement aMixStatementC = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionC);
                    GStatement aMixStatementD = GQuick::MakeAssignVariableStatement(pCurrent, aMixOptionD);
                    
                    GSelect aSelect = GSelect::Random4();
                    aSelect.AddStatementA(aMixStatementA);
                    aSelect.AddStatementB(aMixStatementB);
                    aSelect.AddStatementC(aMixStatementC);
                    aSelect.AddStatementD(aMixStatementD);
                    
                    if (!aSelect.Bake(pPrism, &aTempStatements, pErrorMessage)) {
                        printf("CSPRNG failed to bake feedback gate select 4-box (4 case): %s\n", pErrorMessage->c_str());
                        return false;
                    }
                    
                    TwistArray::Append(pStatements, &aTempStatements);
                    aTempStatements.clear();
                }
            }
            
            pStatements->push_back(GStatement::Comment(""));
            pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
        }
    }
    
    {
        int aHotS0 = aHotIndex++;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("s0 = s0 + (e ^ previous ^ d);"));
        pStatements->push_back(GStatement::Comment("s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);"));
        pStatements->push_back(GStatement::Comment(""));
        
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
        
        GExpr aExprWandererA = GExpr::Add(GExpr::Symbol(pWandererA), aFeedbackExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pWandererA, aExprWandererA));
        
        GSymbol aLoopSalt = Random::Bool() ? PopRandomFixedSalt() : PopRandomScratchSalt();
        GExpr aLoopSaltExpr;
        
        if (Random::Bool()) {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpression(aLoopSalt, pLoopIndex);
        } else {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(aLoopSalt, pLoopIndex);
        }
        
        aExprWandererA = GExpr::Add(GExpr::Symbol(pWandererA), aLoopSaltExpr);
        aExprWandererA = GExpr::Mul(aExprWandererA, GExpr::Const64(pHotPack.mPair[aHotS0].mMul));
        aExprWandererA = RotMediumHigh(aExprWandererA);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pWandererA, aExprWandererA));
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    //TODO: aHotIndex overflow again
    aHotIndex = 0;
    
    {
        int aHotS1 = aHotIndex++;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("s1 = s1 ^ (e + cross + a);"));
        pStatements->push_back(GStatement::Comment("s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);"));
        pStatements->push_back(GStatement::Comment(""));
        
        GExpr aFeedbackFresh = GExpr::Symbol(pCurrent);
        GExpr aFeedbackCross = GExpr::Symbol(pCross);
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
        
        GExpr aExprWandererB = GExpr::Xor(GExpr::Symbol(pWandererB), aFeedbackExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pWandererB, aExprWandererB));
        
        GSymbol aLoopSalt = Random::Bool() ? PopRandomFixedSalt() : PopRandomScratchSalt();
        GExpr aLoopSaltExpr;
        
        if (Random::Bool()) {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpression(aLoopSalt, pLoopIndex);
        } else {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(aLoopSalt, pLoopIndex);
        }
        
        aExprWandererB = GExpr::Xor(GExpr::Symbol(pWandererB), aLoopSaltExpr);
        aExprWandererB = GExpr::Mul(aExprWandererB, GExpr::Const64(pHotPack.mPair[aHotS1].mMul));
        aExprWandererB = RotMediumHigh(aExprWandererB);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pWandererB, aExprWandererB));
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    {
        int aHotS2 = aHotIndex++;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("s2 = s2 + (b ^ c ^ loopSalt[i/~i]);"));
        pStatements->push_back(GStatement::Comment("s2 = rot(s2 * hot.mul);"));
        pStatements->push_back(GStatement::Comment(""));
        
        GExpr aFeedbackB = GExpr::Symbol(pOrbiterB);
        GExpr aFeedbackC = GExpr::Symbol(pOrbiterC);
        
        int aRotateFeedbackTerm = Random::Get(2);
        if (aRotateFeedbackTerm == 0) {
            aFeedbackB = RotMediumHighRandom(aFeedbackB);
        } else {
            aFeedbackC = RotMediumHighRandom(aFeedbackC);
        }
        
        GSymbol aLoopSalt = Random::Bool() ? PopRandomFixedSalt() : PopRandomScratchSalt();
        GExpr aLoopSaltExpr;
        
        if (Random::Bool()) {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpression(aLoopSalt, pLoopIndex);
        } else {
            aLoopSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(aLoopSalt, pLoopIndex);
        }
        
        GExpr aFeedbackExpr = GExpr::Xor(aFeedbackB, GExpr::Xor(aFeedbackC, aLoopSaltExpr));
        
        GExpr aExprWandererC = GExpr::Add(GExpr::Symbol(pWandererC), aFeedbackExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pWandererC, aExprWandererC));
        
        aExprWandererC = GExpr::Mul(GExpr::Symbol(pWandererC), GExpr::Const64(pHotPack.mPair[aHotS2].mMul));
        aExprWandererC = RotMediumHigh(aExprWandererC);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pWandererC, aExprWandererC));
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
    
    {
        int aHotCarry = aHotIndex++;
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment("carry = carry + (s0 ^ s1 ^ s2 ^ e);"));
        pStatements->push_back(GStatement::Comment("carry = rot(carry * hot.mul);"));
        pStatements->push_back(GStatement::Comment("carry = carry ^ (carry >> rshift);"));
        pStatements->push_back(GStatement::Comment(""));
        
        GExpr aFeedbackS0 = GExpr::Symbol(pWandererA);
        GExpr aFeedbackS1 = GExpr::Symbol(pWandererB);
        GExpr aFeedbackS2 = GExpr::Symbol(pWandererC);
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
        
        pStatements->push_back(GStatement::Comment(""));
        pStatements->push_back(GStatement::Comment(">>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<"));
    }
     
    
    return true;
    
}
