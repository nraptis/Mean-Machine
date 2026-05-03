//
//  GSeedDeriveMaterial.hpp
//  MeanMachine
//
//  Created by Dragon on 4/29/26.
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
#include "CSPRNG.hpp"

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
    
    GSymbol                                 mValue;
    GSymbol                                 mValueMix;
    GSymbol                                 mValuePrevious;
    
    GSymbol                                 mFreshByte;
    
    GSymbol                                 mSecureA;
    GSymbol                                 mSecureB;
    
    GSymbol                                 mCarry;
    GSymbol                                 mCarryMix;
    
    GSymbol                                 mCross;
    
    GSymbol                                 mHalfA;
    GSymbol                                 mHalfB;
    
    GSymbol                                 mSelect;
    GSymbol                                 mMultiplex;
    
    GSymbol                                 mUnrollByte;
    
    GSymbol                                 mWandererA;
    GSymbol                                 mWandererB;
    GSymbol                                 mWandererC;
    GSymbol                                 mWandererD;
    
    GSymbol                                 mOrbitA;
    GSymbol                                 mOrbitB;
    GSymbol                                 mOrbitC;
    GSymbol                                 mOrbitD;
    
    
private:
    
    std::vector<GSymbol>                    mListSBoxes;
    std::vector<GSymbol>                    mListSalts;
    std::vector<GSymbol>                    mListScratchSalts;
    
    std::vector<GSymbol>                    mListWorkers;
    std::vector<GSymbol>                    mListExpansion;
    
    std::vector<GSymbol>                    mListDerivedSBoxes;
    std::vector<GSymbol>                    mListDerivedSalts;
    
    GSymbol                                 BuildMixSymbol(GSymbol pTarget) const;
    
    void                                    Reset();
    
    bool                                    mValueCarryEnabled[SEED_WORK_LANE_COUNT];
    bool                                    mValueCarryBefore[SEED_WORK_LANE_COUNT];

    GSymbol                                 mValueSalt[SEED_WORK_LANE_COUNT];
    bool                                    mValueSaltEnabled[SEED_WORK_LANE_COUNT];
    bool                                    mValueSaltBefore[SEED_WORK_LANE_COUNT];
    
    GSymbol                                 mValueSourceA[SEED_WORK_LANE_COUNT];
    bool                                    mValueSourceAEnabled[SEED_WORK_LANE_COUNT];
    bool                                    mValueSourceABefore[SEED_WORK_LANE_COUNT];

    GSymbol                                 mValueSourceB[SEED_WORK_LANE_COUNT];
    bool                                    mValueSourceBEnabled[SEED_WORK_LANE_COUNT];
    bool                                    mValueSourceBBefore[SEED_WORK_LANE_COUNT];
    
    GSymbol                                 mValueSourceC[SEED_WORK_LANE_COUNT];
    bool                                    mValueSourceCEnabled[SEED_WORK_LANE_COUNT];
    bool                                    mValueSourceCBefore[SEED_WORK_LANE_COUNT];
    
    Mix64Type_1                             mValueMix64Type_1[SEED_WORK_LANE_COUNT];
    Mix64Type_4                             mValueMix64Type_4[SEED_WORK_LANE_COUNT];
    Mix64Type_8                             mValueMix64Type_8[SEED_WORK_LANE_COUNT];
    bool                                    mValueMixChoice[SEED_WORK_LANE_COUNT];
    
    GSymbol                                 mValueSBoxes[8][SEED_WORK_LANE_COUNT];
    
    
    GSymbol                                 mDestBuffer[SEED_WORK_LANE_COUNT];
    bool                                    mDestReverse[SEED_WORK_LANE_COUNT];
    
    GSnowType                               mSnowType[SEED_WORK_LANE_COUNT];
    
    GBoxFamily                              mBoxFamily;
    GBoxFamily                              mSaltFamily;
    GBoxFamily                              mScratchSaltFamily;
    
    GOperationFamily                        mMixOperationFamily;
    
    GRotationFamily                         mRotationFamily;
    GHotPack                                mHotPacks[SEED_WORK_LANE_COUNT];
    
    //TwistHotPair                            mHotPairs[SEED_WORK_LANE_COUNT][3];
    
        
    Mix64Type_1                             RandomMix64Type_1();
    Mix64Type_4                             RandomMix64Type_4();
    Mix64Type_8                             RandomMix64Type_8();
    
    
    
};

#endif /* GSeedDeriveMaterial_hpp */
