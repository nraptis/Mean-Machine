//
//  GSeedWorkerBuilder.hpp
//  MeanMachine
//
//  Created by Dragon on 4/29/26.
//

#ifndef GSeedWorkerBuilder_hpp
#define GSeedWorkerBuilder_hpp

#include "GLoopFragmentComposer.hpp"
#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "GTwistExpander.hpp"
#include "TwistCryptoScoring.hpp"
#include "TwistMix16.hpp"


#define SEED_WORK_LANE_COUNT 4

class GSeedWorkerBuilder {
    
public:
    
    GSeedWorkerBuilder();
    ~GSeedWorkerBuilder();
    
    bool                                    PlanPhaseA(std::string &pError);
    
    
    bool                                    BuildPhaseA(TwistProgramBranch &pBranch,
                                                        std::string &pError);
    bool                                    ExecuteBranch(TwistWorkSpace *pWorkspace,
                                                          const TwistProgramBranch &pBranch,
                                                          std::string &pError);
    
    GSymbol                                 mLoopIndex;
    
    GSymbol                                 mSource;
    
    GSymbol                                 mValue;
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
    
    GSymbol                                 BuildManagedMixSymbol(GSymbol pTarget) const;
    
    
    
};

#endif /* GSeedWorkerBuilder_hpp */
