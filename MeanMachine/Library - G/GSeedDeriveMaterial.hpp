//
//  GSeedDeriveMaterial.hpp
//  MeanMachine
//
//  Created by Dragon on 4/29/26.
//

#ifndef GSeedDeriveMaterial_hpp
#define GSeedDeriveMaterial_hpp

#include "GLoopFragmentComposer.hpp"
#include "GCryptoGenerator.hpp"
#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "GTwistExpander.hpp"
#include "TwistMix64.hpp"
#include "GSelect.hpp"
#include "GLoopMixBrew.hpp"
#include "GQuick.hpp"
#include "GFastMatrix.hpp"
#include "GSnow.hpp"
#include "GMasking.hpp"
#include "GMagicNumbers.hpp"
#include "GFamily.hpp"
#include "GMemory.hpp"
#include "CSPRNG.hpp"
#include "GCache.hpp"

#define SEED_WORK_LANE_COUNT 4

class GSeedDeriveMaterial {
    
public:
    
    GSeedDeriveMaterial();
    ~GSeedDeriveMaterial();
    
    bool                                    PlanPhaseA(std::string *pErrorMessage);
    bool                                    BuildPhaseA(TwistProgramBranch &pBranch, std::string *pErrorMessage);
    bool                                    BuildSnow(TwistProgramBranch &pBranch, std::string *pErrorMessage);
    bool                                    BuildZero(GSymbol pSymbol, TwistProgramBranch &pBranch, std::string *pErrorMessage);
    
    GSymbol                                 mLoopIndex;
    
    GSymbol                                 mSource;
    
    GSymbol                                 mPrism;
    GSymbol                                 mScatter;
    
    GSymbol                                 mCurrent;
    GSymbol                                 mPrevious;
    
    GSymbol                                 mCarry;
    GSymbol                                 mCross;
    
    GSymbol                                 mWandererA;
    GSymbol                                 mWandererB;
    GSymbol                                 mWandererC;
    GSymbol                                 mWandererD;
    
    GSymbol                                 mOrbitA;
    GSymbol                                 mOrbitB;
    GSymbol                                 mOrbitC;
    GSymbol                                 mOrbitD;
    
    
private:
    
    std::vector<GSymbol>                    mListSBoxesA;
    std::vector<GSymbol>                    mListSBoxesB;
    std::vector<GSymbol>                    mListSBoxesC;
    
    std::vector<GSymbol>                    mListSaltsA;
    std::vector<GSymbol>                    mListSaltsB;
    std::vector<GSymbol>                    mListScratchSalts;
    
    std::vector<GSymbol>                    mListWorkers;
    std::vector<GSymbol>                    mListExpansion;
    
    
    void                                    Reset();
    
    GSymbol                                 mValueSBoxes[8][SEED_WORK_LANE_COUNT];
    
    GSymbol                                 mDestBuffer[SEED_WORK_LANE_COUNT];
    bool                                    mDestReverse[SEED_WORK_LANE_COUNT];
    GSnowType                               mSnowType[SEED_WORK_LANE_COUNT];
    
    GBoxFamily                              mBoxFamilyA;
    GBoxFamily                              mBoxFamilyB;
    GBoxFamily                              mBoxFamilyC;
    
    GBoxFamily                              mSaltFamilyA;
    GBoxFamily                              mSaltFamilyB;
    
    GBoxFamily                              mScratchSaltFamily;
    
    
    GHotPack                                mHotPacks[SEED_WORK_LANE_COUNT];
    
};

#endif /* GSeedDeriveMaterial_hpp */
