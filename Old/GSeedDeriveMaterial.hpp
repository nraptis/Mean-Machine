//
//  GSeedDeriveMaterial.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 4/29/26.
//

#ifndef GSeedDeriveMaterial_hpp
#define GSeedDeriveMaterial_hpp

#include "GLoopFragmentComposer.hpp"
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
#include "CSPKDF.hpp"

#include "GCache.hpp"

#define SEED_WORK_LANE_COUNT 4

class GSeedDeriveMaterial {
    
public:
    
    GSeedDeriveMaterial();
    ~GSeedDeriveMaterial();
    
    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);
    
    GSymbol                                 mLoopIndex;
    
    GSymbol                                 mSource;
    
    GSymbol                                 mPrism;
    GSymbol                                 mScatter;
    
    GSymbol                                 mCurrent;
    GSymbol                                 mPrevious;
    
    GSymbol                                 mCarry;
    GSymbol                                 mStreamCross;
    
    GSymbol                                 mUnwindA;
    GSymbol                                 mUnwindB;
    GSymbol                                 mUnwindC;
    GSymbol                                 mUnwindD;
    
    GSymbol                                 mOrbitA;
    GSymbol                                 mOrbitB;
    GSymbol                                 mOrbitC;
    GSymbol                                 mOrbitD;
    
    GSymbol                                 mPlugKeyA;
    GSymbol                                 mPlugKeyB;
    
private:
    
    std::vector<GSymbol>                    mListSBoxes;
    std::vector<GSymbol>                    mListSalts;
    
    std::vector<GSymbol>                    mListWorkers;
    std::vector<GSymbol>                    mListExpansion;
    
    std::vector<GSymbol>                    mListOperationLanes;
    
    
    void                                    Reset();
    
    GSymbol                                 mChunkGlobalRecipeSalt[SEED_WORK_LANE_COUNT];
    GSymbol                                 mRecipeSaltA[SEED_WORK_LANE_COUNT][2];
    GSymbol                                 mRecipeSaltB[SEED_WORK_LANE_COUNT][2];
    
    std::vector<GSymbol>                    mPlugSalts[SEED_WORK_LANE_COUNT];
    std::vector<GSymbol>                    mOrderedSBoxes[SEED_WORK_LANE_COUNT];
    
    GSymbol                                 mDestBuffer[SEED_WORK_LANE_COUNT];
    bool                                    mDestReverse[SEED_WORK_LANE_COUNT];
    GSnowType                               mSnowType[SEED_WORK_LANE_COUNT];
    
    GHotPack                                mHotPacks[SEED_WORK_LANE_COUNT];
    
};

#endif /* GSeedDeriveMaterial_hpp */
