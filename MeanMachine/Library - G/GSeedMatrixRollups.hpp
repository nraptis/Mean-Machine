//
//  GSeedMatrixRollups.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/4/26.
//

#ifndef GSeedMatrixRollups_hpp
#define GSeedMatrixRollups_hpp

#include "GSeedDeriveMaterial.hpp"

class GSeedMatrixRollups {
    
public:
    
    GSeedMatrixRollups();
    ~GSeedMatrixRollups();
    
    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);
    
    
    GSymbol                                 mMaskA;
    GSymbol                                 mMaskB;
    GSymbol                                 mKeyA;
    GSymbol                                 mKeyB;
    
    GSymbol                                 mLoopIndex;
    GSymbol                                 mLoopIndexInverted;
    
    GSymbol                                 mSource;
    
    GSymbol                                 mPrism;
    GSymbol                                 mScatter;
    
    GSymbol                                 mCurrent;
    GSymbol                                 mPrevious;

    GSymbol                                 mArgA;
    GSymbol                                 mArgB;
    
    GSymbol                                 mKindA;
    GSymbol                                 mKindB;
    
    
private:
    
    std::vector<GSymbol>                    mListWorkers;
    std::vector<GSymbol>                    mListExpansion;
    
    std::vector<GSymbol>                    mListMasks;
    std::vector<GSymbol>                    mListKeys;
    
    std::vector<GSymbol>                    mListOperationLanes;
    
    
    void                                    Reset();
    
    int                                     mCaseCount[2];
    int                                     mFastOpCount[2][4]; // one for each of up to 4 cases
    int                                     mMediumOpCount[2][4]; // one for each of up to 4 cases
    int                                     mSlowOpCount[2][4]; // one for each of up to 4 cases
    
    TwistFastMatrixUnrollScheme             mUnrollSchemeA[2][4];
    TwistFastMatrixUnrollScheme             mUnrollSchemeB[2][4];
    
    
    
};

#endif /* GSeedMatrixRollups_hpp */
