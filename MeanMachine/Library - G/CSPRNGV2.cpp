//
//  CSPRNGV2.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/18/26.
//

#include "CSPRNGV2.hpp"
#include "TwistArray.hpp"
#include <cstdio>

bool CSPRNGV2::Bake(std::vector<CSPRNGV2Slice> &pSlices,
                    const std::vector<GSymbol> &pSaltsOrbiterAssign,
                    const std::vector<GSymbol> &pSaltsOrbiterUpdate,
                    const std::vector<GSymbol> &pSaltsWandererUpdate,
                    std::vector<GLoop> *pLoops,
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

    GSymbol aWandererA = GSymbol::Var(TwistVariable::kWandererA); GSymbol aWandererB = GSymbol::Var(TwistVariable::kWandererB);
    GSymbol aWandererC = GSymbol::Var(TwistVariable::kWandererC); GSymbol aWandererD = GSymbol::Var(TwistVariable::kWandererD);
    GSymbol aWandererE = GSymbol::Var(TwistVariable::kWandererE); GSymbol aWandererF = GSymbol::Var(TwistVariable::kWandererF);
    GSymbol aWandererG = GSymbol::Var(TwistVariable::kWandererG); GSymbol aWandererH = GSymbol::Var(TwistVariable::kWandererH);
    GSymbol aWandererI = GSymbol::Var(TwistVariable::kWandererI); GSymbol aWandererJ = GSymbol::Var(TwistVariable::kWandererJ);
    GSymbol aWandererK = GSymbol::Var(TwistVariable::kWandererK);

    GSymbol aOrbiterA = GSymbol::Var(TwistVariable::kOrbiterA); GSymbol aOrbiterB = GSymbol::Var(TwistVariable::kOrbiterB);
    GSymbol aOrbiterC = GSymbol::Var(TwistVariable::kOrbiterC); GSymbol aOrbiterD = GSymbol::Var(TwistVariable::kOrbiterD);
    GSymbol aOrbiterE = GSymbol::Var(TwistVariable::kOrbiterE); GSymbol aOrbiterF = GSymbol::Var(TwistVariable::kOrbiterF);
    GSymbol aOrbiterG = GSymbol::Var(TwistVariable::kOrbiterG); GSymbol aOrbiterH = GSymbol::Var(TwistVariable::kOrbiterH);
    GSymbol aOrbiterI = GSymbol::Var(TwistVariable::kOrbiterI); GSymbol aOrbiterJ = GSymbol::Var(TwistVariable::kOrbiterJ);
    GSymbol aOrbiterK = GSymbol::Var(TwistVariable::kOrbiterK);

    GSymbol aNonceByteA = GSymbol::Var("aNonceByteA"); GSymbol aNonceByteB = GSymbol::Var("aNonceByteB");
    GSymbol aNonceByteC = GSymbol::Var("aNonceByteC"); GSymbol aNonceByteD = GSymbol::Var("aNonceByteD");
    GSymbol aNonceByteE = GSymbol::Var("aNonceByteE"); GSymbol aNonceByteF = GSymbol::Var("aNonceByteF");
    GSymbol aNonceByteG = GSymbol::Var("aNonceByteG"); GSymbol aNonceByteH = GSymbol::Var("aNonceByteH");
    
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
        
        pSlices[aSliceIndex].mNonceBytes = {
            aNonceByteA, aNonceByteB, aNonceByteC, aNonceByteD,
            aNonceByteE, aNonceByteF, aNonceByteG, aNonceByteH,
        };
        Random::Shuffle(&pSlices[aSliceIndex].mNonceBytes);
        
        
        pSlices[aSliceIndex].mOrbiters = {
            aOrbiterA, aOrbiterB, aOrbiterC, aOrbiterD,
            aOrbiterE, aOrbiterF, aOrbiterG, aOrbiterH,
            aOrbiterI, aOrbiterJ, aOrbiterK,
        };
        Random::Shuffle(&pSlices[aSliceIndex].mOrbiters);
        
        pSlices[aSliceIndex].mWanderers = {
            aWandererA, aWandererB, aWandererC, aWandererD,
            aWandererE, aWandererF, aWandererG, aWandererH,
            aWandererI, aWandererJ, aWandererK
        };
        Random::Shuffle(&pSlices[aSliceIndex].mWanderers);
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
            pSlices[aSliceIndex].mNonceBytes = {
                aNonceByteA, aNonceByteB, aNonceByteC, aNonceByteD,
                aNonceByteE, aNonceByteF, aNonceByteG, aNonceByteH,
            };
            pSlices[aSliceIndex].mOrbiters = {
                aOrbiterA, aOrbiterB, aOrbiterC, aOrbiterD,
                aOrbiterE, aOrbiterF, aOrbiterG, aOrbiterH,
                aOrbiterI, aOrbiterJ, aOrbiterK,
            };
            pSlices[aSliceIndex].mWanderers = {
                aWandererA, aWandererB, aWandererC, aWandererD,
                aWandererE, aWandererF, aWandererG, aWandererH,
                aWandererI, aWandererJ, aWandererK
            };
        }
        
    }
    
    GAXPL *aPlan = new GAXPL();
    
    int aFullNonceIndex = Random::Get((int)(pSlices.size()));
    
    for (int aSliceIndex=0; aSliceIndex<pSlices.size(); aSliceIndex++) {
        
        const CSPRNGV2Slice &aSlice = pSlices[aSliceIndex];

        GLoop aLoop;
        aLoop.mLoopVariable = aIndex;
        aLoop.mLoopVariableName = aIndex.mName;
        aLoop.mLoopBegin = 0;
        aLoop.mLoopEndText = "S_BLOCK";
        aLoop.mLoopStep = 1;
        
        if (!aPlan->Bake(&aSlice.mARXSkeleton,
                         aSlice.mSaltBag,
                         aSlice.mNonceBytes,
                         aSlice.mSources,
                         aSlice.mOrbiters,
                         aSlice.mWanderers,
                         aSlice.mHotPack,
                         (aFullNonceIndex == aSliceIndex),
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
