//
//  CSPRNGV2.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/18/26.
//

#include "CSPRNGV2.hpp"
#include "TwistArray.hpp"
#include <cstdio>

namespace {

std::vector<GSymbol> MakeShuffledWanderers() {
    std::vector<GSymbol> aWanderers = {
        GSymbol::Var(TwistVariable::kWandererA),
        GSymbol::Var(TwistVariable::kWandererB),
        GSymbol::Var(TwistVariable::kWandererC),
        GSymbol::Var(TwistVariable::kWandererD),
        GSymbol::Var(TwistVariable::kWandererE),
        GSymbol::Var(TwistVariable::kWandererF),
        GSymbol::Var(TwistVariable::kWandererG),
        GSymbol::Var(TwistVariable::kWandererH),
        GSymbol::Var(TwistVariable::kWandererI),
        GSymbol::Var(TwistVariable::kWandererJ),
        GSymbol::Var(TwistVariable::kWandererK),
    };

    Random::Shuffle(&aWanderers);
    return aWanderers;
}

void AddSymbolsToCache(GSymbolCache *pCache,
                       const std::vector<GSymbol> &pSymbols) {
    if (pCache == nullptr) {
        return;
    }
    for (const GSymbol &aSymbol : pSymbols) {
        pCache->AddItem(&aSymbol);
    }
}

void FillSaltBag(const std::vector<GSymbol> &pSaltsOrbiterAssign,
                 const std::vector<GSymbol> &pSaltsOrbiterUpdate,
                 const std::vector<GSymbol> &pSaltsWandererUpdate,
                 GAXPLSaltBag *pSaltBag) {
    if (pSaltBag == nullptr) {
        return;
    }

    GSymbolCache aCacheOrbiterAssign;
    AddSymbolsToCache(&aCacheOrbiterAssign, pSaltsOrbiterAssign);
    aCacheOrbiterAssign.SetLimits(2, 2, 2);
    aCacheOrbiterAssign.Fetch(2);
    pSaltBag->mOrbiterAssign = {
        *(aCacheOrbiterAssign.mBus[0]), *(aCacheOrbiterAssign.mBus[1]),
    };

    GSymbolCache aCacheOrbiterUpdate;
    AddSymbolsToCache(&aCacheOrbiterUpdate, pSaltsOrbiterUpdate);
    aCacheOrbiterUpdate.SetLimits(2, 3, 4);
    aCacheOrbiterUpdate.Fetch(4);
    pSaltBag->mOrbiterUpdate = {
        *(aCacheOrbiterUpdate.mBus[0]), *(aCacheOrbiterUpdate.mBus[1]),
        *(aCacheOrbiterUpdate.mBus[2]), *(aCacheOrbiterUpdate.mBus[3]),
    };

    GSymbolCache aCacheWandererUpdate;
    AddSymbolsToCache(&aCacheWandererUpdate, pSaltsWandererUpdate);
    aCacheWandererUpdate.SetLimits(2, 2, 2);
    aCacheWandererUpdate.Fetch(2);
    pSaltBag->mWandererUpdate = {
        *(aCacheWandererUpdate.mBus[0]), *(aCacheWandererUpdate.mBus[1]),
    };
}

} // namespace

bool CSPRNGV2::Bake(bool pIsNonKDF,
                    TwistDomain pDomain,
                    std::vector<CSPRNGV2Slice> &pSlices,
                    const std::vector<GSymbol> &pSaltsOrbiterAssign,
                    const std::vector<GSymbol> &pSaltsOrbiterUpdate,
                    const std::vector<GSymbol> &pSaltsWandererUpdate,
                    std::vector<GLoop> *pLoops,
                    bool pAutoRangeAdjust,
                    std::string *pErrorMessage) {
    
    if (pLoops == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "CSPRNGV2::Bake received null loop output";
        }
        return false;
    }
    
    if (pSaltsOrbiterAssign.size() < 2 ||
        pSaltsOrbiterUpdate.size() < 4 ||
        pSaltsWandererUpdate.size() < 2) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "CSPRNGV2::Bake received too few salts";
        }
        return false;
    }
    
    GSymbol aIndex = GSymbol::Var(TwistVariable::kIndex);
    
    GSymbol aOrbiterA = GSymbol::Var(TwistVariable::kOrbiterA); GSymbol aOrbiterB = GSymbol::Var(TwistVariable::kOrbiterB);
    GSymbol aOrbiterC = GSymbol::Var(TwistVariable::kOrbiterC); GSymbol aOrbiterD = GSymbol::Var(TwistVariable::kOrbiterD);
    GSymbol aOrbiterE = GSymbol::Var(TwistVariable::kOrbiterE); GSymbol aOrbiterF = GSymbol::Var(TwistVariable::kOrbiterF);
    GSymbol aOrbiterG = GSymbol::Var(TwistVariable::kOrbiterG); GSymbol aOrbiterH = GSymbol::Var(TwistVariable::kOrbiterH);
    GSymbol aOrbiterI = GSymbol::Var(TwistVariable::kOrbiterI); GSymbol aOrbiterJ = GSymbol::Var(TwistVariable::kOrbiterJ);
    GSymbol aOrbiterK = GSymbol::Var(TwistVariable::kOrbiterK);
    
    std::vector<GSymbol> aNonceWords = {
        GSymbol::Var("aNonceWordA"),
        GSymbol::Var("aNonceWordB"),
        GSymbol::Var("aNonceWordC"),
        GSymbol::Var("aNonceWordD"),
        GSymbol::Var("aNonceWordE"),
        GSymbol::Var("aNonceWordF"),
        GSymbol::Var("aNonceWordG"),
        GSymbol::Var("aNonceWordH"),
        GSymbol::Var("aNonceWordI"),
        GSymbol::Var("aNonceWordJ"),
        GSymbol::Var("aNonceWordK"),
        GSymbol::Var("aNonceWordL"),
        GSymbol::Var("aNonceWordM"),
        GSymbol::Var("aNonceWordN"),
        GSymbol::Var("aNonceWordO"),
        GSymbol::Var("aNonceWordP"),
    };
    
    GSymbolCache aCacheOrbiterAssign;
    for (int aSaltIndex=0; aSaltIndex< pSaltsOrbiterAssign.size(); aSaltIndex++) {
        aCacheOrbiterAssign.AddItem(&(pSaltsOrbiterAssign[aSaltIndex]));
    }
    aCacheOrbiterAssign.SetLimits(2, 2, 2);
    
    GSymbolCache aCacheOrbiterUpdate;
    for (int aSaltIndex=0; aSaltIndex< pSaltsOrbiterUpdate.size(); aSaltIndex++) {
        aCacheOrbiterUpdate.AddItem(&(pSaltsOrbiterUpdate[aSaltIndex]));
    }
    aCacheOrbiterUpdate.SetLimits(2, 3, 4);
    
    GSymbolCache aCacheWandererUpdate;
    for (int aSaltIndex=0; aSaltIndex< pSaltsWandererUpdate.size(); aSaltIndex++) {
        aCacheWandererUpdate.AddItem(&(pSaltsWandererUpdate[aSaltIndex]));
    }
    aCacheWandererUpdate.SetLimits(2, 2, 2);
    
    for (int aSliceIndex=0; aSliceIndex<pSlices.size(); aSliceIndex++) {
        if (!pSlices[aSliceIndex].mSaltsOrbiterAssign.empty() ||
            !pSlices[aSliceIndex].mSaltsOrbiterUpdate.empty() ||
            !pSlices[aSliceIndex].mSaltsWandererUpdate.empty()) {
            if ((pSlices[aSliceIndex].mSaltsOrbiterAssign.size() < 2U) ||
                (pSlices[aSliceIndex].mSaltsOrbiterUpdate.size() < 4U) ||
                (pSlices[aSliceIndex].mSaltsWandererUpdate.size() < 2U)) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "CSPRNGV2::Bake received incomplete per-slice salts";
                }
                return false;
            }
            FillSaltBag(pSlices[aSliceIndex].mSaltsOrbiterAssign,
                        pSlices[aSliceIndex].mSaltsOrbiterUpdate,
                        pSlices[aSliceIndex].mSaltsWandererUpdate,
                        &(pSlices[aSliceIndex].mSaltBag));
            continue;
        }

        aCacheOrbiterAssign.Fetch(2);
        pSlices[aSliceIndex].mSaltBag.mOrbiterAssign = {
            *(aCacheOrbiterAssign.mBus[0]), *(aCacheOrbiterAssign.mBus[1]),
        };
        
        aCacheOrbiterUpdate.Fetch(4);
        pSlices[aSliceIndex].mSaltBag.mOrbiterUpdate = {
            *(aCacheOrbiterUpdate.mBus[0]), *(aCacheOrbiterUpdate.mBus[1]),
            *(aCacheOrbiterUpdate.mBus[2]), *(aCacheOrbiterUpdate.mBus[3]),
        };
        
        aCacheWandererUpdate.Fetch(2);
        pSlices[aSliceIndex].mSaltBag.mWandererUpdate = {
            *(aCacheWandererUpdate.mBus[0]), *(aCacheWandererUpdate.mBus[1]),
        };
    }
    
    for (int aSliceIndex=0; aSliceIndex<pSlices.size(); aSliceIndex++) {
        if (pSlices[aSliceIndex].mARXSkeleton.HasNonceSlots()) {
            pSlices[aSliceIndex].mNonceBytes = aNonceWords;
            Random::Shuffle(&pSlices[aSliceIndex].mNonceBytes);
        } else {
            pSlices[aSliceIndex].mNonceBytes.clear();
        }
        
        
        pSlices[aSliceIndex].mOrbiters = {
            aOrbiterA, aOrbiterB, aOrbiterC, aOrbiterD,
            aOrbiterE, aOrbiterF, aOrbiterG, aOrbiterH,
            aOrbiterI, aOrbiterJ, aOrbiterK,
        };
        Random::Shuffle(&pSlices[aSliceIndex].mOrbiters);
        
        pSlices[aSliceIndex].mWanderers = MakeShuffledWanderers();
    }
    
    bool NO_SHUFFLE = false;
    
    if (NO_SHUFFLE == true) {
        for (int aSliceIndex=0; aSliceIndex<pSlices.size(); aSliceIndex++) {
            aCacheOrbiterAssign.Fetch(2);
            pSlices[aSliceIndex].mSaltBag.mOrbiterAssign = {
                pSaltsOrbiterAssign[0], pSaltsOrbiterAssign[1],
            };
            
            aCacheOrbiterUpdate.Fetch(4);
            pSlices[aSliceIndex].mSaltBag.mOrbiterUpdate = {
                pSaltsOrbiterUpdate[0], pSaltsOrbiterUpdate[1],
                pSaltsOrbiterUpdate[2], pSaltsOrbiterUpdate[3],
            };
            
            aCacheWandererUpdate.Fetch(2);
            pSlices[aSliceIndex].mSaltBag.mWandererUpdate = {
                pSaltsWandererUpdate[0], pSaltsWandererUpdate[1],
            };
        }
        for (int aSliceIndex=0; aSliceIndex<pSlices.size(); aSliceIndex++) {
            if (pSlices[aSliceIndex].mARXSkeleton.HasNonceSlots()) {
                pSlices[aSliceIndex].mNonceBytes = aNonceWords;
                Random::Shuffle(&pSlices[aSliceIndex].mNonceBytes);
            } else {
                pSlices[aSliceIndex].mNonceBytes.clear();
            }
            pSlices[aSliceIndex].mOrbiters = {
                aOrbiterA, aOrbiterB, aOrbiterC, aOrbiterD,
                aOrbiterE, aOrbiterF, aOrbiterG, aOrbiterH,
                aOrbiterI, aOrbiterJ, aOrbiterK,
            };
            pSlices[aSliceIndex].mWanderers = MakeShuffledWanderers();
        }
        
    }
    
    GAXPL *aPlan = new GAXPL();
    
    aPlan->mIsNonKDF = pIsNonKDF;
    aPlan->mDomain = pDomain;
    
    int aSliceCount = (int)pSlices.size();
    
    for (int aSliceIndex=0; aSliceIndex<pSlices.size(); aSliceIndex++) {
        
        //const
        CSPRNGV2Slice &aSlice = pSlices[aSliceIndex];
        aPlan->mDomain = (aSlice.mDomain == TwistDomain::kInvalid) ? pDomain : aSlice.mDomain;
        
        if (pAutoRangeAdjust == true) {
            int aCeiling = aSlice.mLoopCeiling;
            
            int aLo = (aSliceIndex * aCeiling) / aSliceCount;
            int aHi = ((aSliceIndex + 1) * aCeiling) / aSliceCount;
            
            aSlice.mSourceRangesLo = aLo;
            aSlice.mSourceRangesHi = aHi;
        }
        
        GLoop aLoop;
        aLoop.mLoopVariable = aIndex;
        aLoop.mLoopVariableName = aIndex.mName;
        aLoop.mLoopBegin = aSlice.mLoopBegin;
        aLoop.mLoopBeginText = aSlice.mLoopBeginText;
        aLoop.mLoopEndText = aSlice.mLoopEndText.empty() ? "S_BLOCK" : aSlice.mLoopEndText;
        aLoop.mLoopStep = 1;
        
        if (!aPlan->Bake(aSlice.mSourceRangesLo,
                         aSlice.mSourceRangesHi,
                         &aSlice.mARXSkeleton,
                         aSlice.mSaltBag,
                         aSlice.mNonceBytes,
                         aSlice.mSources,
                         aSlice.mOrbiters,
                         aSlice.mWanderers,
                         aSlice.mHotPack,
                         false,
                         aSlice.mDest,
                         aSlice.mDestWriteInverted,
                         &aLoop,
                         pErrorMessage)) {
            const char *aErrorText = (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "unknown error";
            printf("GAXPL::Bake Error => %s\n", aErrorText);
            delete aPlan;
            return false;
        }
        
        pLoops->push_back(aLoop);
    }
    
    delete aPlan;
    return true;
    
}
