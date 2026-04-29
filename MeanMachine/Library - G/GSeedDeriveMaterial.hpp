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
#include "TwistCryptoScoring.hpp"
#include "TwistMix16.hpp"


#define SEED_WORK_LANE_COUNT 4

class GSeedDeriveMaterial {
    
public:
    
    GSeedDeriveMaterial();
    ~GSeedDeriveMaterial();
    
    bool                                    PlanPhaseA(std::string &pError);
    bool                                    BuildPhaseA(TwistProgramBranch &pBranch,
                                                        std::string &pError);
    
    GSymbol                                 mLoopIndex;
    
    GSymbol                                 mSource;
    
    GSymbol                                 mValue;
    GSymbol                                 mValueMix;
    
    GSymbol                                 mCarry;
    
    GSymbol                                 mSBoxA;
    GSymbol                                 mSBoxB;
    GSymbol                                 mSBoxC;
    GSymbol                                 mSBoxD;
    
    GSymbol                                 mDerivedSBoxA;
    GSymbol                                 mDerivedSBoxB;
    GSymbol                                 mDerivedSBoxC;
    GSymbol                                 mDerivedSBoxD;
    
    GSymbol                                 mSaltA;
    GSymbol                                 mSaltB;
    GSymbol                                 mSaltC;
    GSymbol                                 mSaltD;
    
    GSymbol                                 mDerivedSaltA;
    GSymbol                                 mDerivedSaltB;
    GSymbol                                 mDerivedSaltC;
    GSymbol                                 mDerivedSaltD;
    
    GSymbol                                 mWorkerA;
    GSymbol                                 mWorkerB;
    GSymbol                                 mWorkerC;
    GSymbol                                 mWorkerD;
    
private:
    
    
    
    std::vector<GSymbol>                    mListSBoxes;
    std::vector<GSymbol>                    mListSalts;
    std::vector<GSymbol>                    mListWorkers;
    
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

    Mix161Type                              mValueMix161Type[SEED_WORK_LANE_COUNT];
    Mix162Type                              mValueMix162Type[SEED_WORK_LANE_COUNT];
    bool                                    mValueMixChoice[SEED_WORK_LANE_COUNT];
    
    //
    
    bool                                    mCarryValueEnabled[SEED_WORK_LANE_COUNT];
    bool                                    mCarryValueBefore[SEED_WORK_LANE_COUNT];
    
    GSymbol                                 mCarrySalt[SEED_WORK_LANE_COUNT];
    bool                                    mCarrySaltEnabled[SEED_WORK_LANE_COUNT];
    bool                                    mCarrySaltBefore[SEED_WORK_LANE_COUNT];
    
    GSymbol                                 mCarrySourceA[SEED_WORK_LANE_COUNT];
    bool                                    mCarrySourceAEnabled[SEED_WORK_LANE_COUNT];
    bool                                    mCarrySourceABefore[SEED_WORK_LANE_COUNT];

    GSymbol                                 mCarrySourceB[SEED_WORK_LANE_COUNT];
    bool                                    mCarrySourceBEnabled[SEED_WORK_LANE_COUNT];
    bool                                    mCarrySourceBBefore[SEED_WORK_LANE_COUNT];
    
    
    //

    GSymbol                                 mDestBuffer[SEED_WORK_LANE_COUNT];
    bool                                    mDestReverse[SEED_WORK_LANE_COUNT];
    
    Mix161Type                              RandomMix161Type();
    Mix162Type                              RandomMix162Type();
    
};

#endif /* GSeedDeriveMaterial_hpp */
