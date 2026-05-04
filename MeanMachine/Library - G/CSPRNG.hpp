//
//  CSPRNG.hpp
//  MeanMachine
//
//  Created by Dragon on 5/2/26.
//

#ifndef CSPRNG_hpp
#define CSPRNG_hpp

#include <stdio.h>
#include "GMagicNumbers.hpp"
#include "GFamily.hpp"
#include "GLoopFragmentComposer.hpp"
#include "GLoopMixBrew.hpp"
#include "GQuick.hpp"
#include "GSelect.hpp"
#include "GMagicNumbers.hpp"
#include "GCache.hpp"
#include <deque>
#include <unordered_set>

enum class CSPRNGPlugMode : std::uint8_t {
    kInv = 1,
    kInput = 2,
    kInputPrevious = 3,
    kScatter = 5,
    kCross = 8,
    kCarry = 9,
    kWandererA = 11,
    kWandererB = 12,
    kWandererC = 13,
    kOrbiterA = 14,
    kOrbiterB = 15,
    kOrbiterC = 16,
    kOrbiterD = 17
};

struct CSPRNGPlugPack {
    
    GSymbol mInput;
    GSymbol mPrevious;
    GSymbol mScatter;
    GSymbol mCross;
    GSymbol mCarry;
    GSymbol mWandererA;
    GSymbol mWandererB;
    GSymbol mWandererC;
    GSymbol mOrbiterA;
    GSymbol mOrbiterB;
    GSymbol mOrbiterC;
    GSymbol mOrbiterD;
    
    GExpr GetExpr(CSPRNGPlugMode pPlugMode);
};

class CSPRNG {
    
public:
    
    static GExpr CreatePlug(GExpr pExpr,
                            bool pAdd,
                            GSymbol pSalt,
                            GIntCache *pRotCache,
                            CSPRNGPlugPack *pPack,
                            std::deque<CSPRNGPlugMode> *pRecent);
    
    static bool PlugIncompatible(CSPRNGPlugMode pPlugModeA,
                                 CSPRNGPlugMode pPlugModeB);
    
    
    static bool Bake(GSymbol pDest,
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
                     std::string *pErrorMessage);
    
};

#endif /* CSPRNG_hpp */
