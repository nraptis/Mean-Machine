//
//  GAXSKPool.hpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#ifndef GAXSKPool_hpp
#define GAXSKPool_hpp

#include "GAXSK.hpp"
#include <vector>
#include <string>

struct GAXSKInputSlotOrdering {
    std::vector<GAXSKInputSlot>             mIngress;
    std::vector<GAXSKInputSlot>             mCross;
};

class GAXSKPool {
public:
    GAXSKPool();
    
    void                                    SetSourceCount(int pSourceCount);
    void                                    SetOrbiterCount(int pOrbiterCount);
    void                                    SetWandererCount(int pWandererCount);
    bool                                    FinalizeCounts(std::string *pErrorMessage);
    
    bool                                    GenerateInputSlotOrdering(GAXSKInputSlotOrdering *pResult, std::string *pErrorMessage);
    
    std::vector<GAXSKNonceByteKind>         mNoncesIngress;
    std::vector<GAXSKSourceKind>            mSourcesIngress;
    
    std::vector<GAXSKNonceByteKind>         mNoncesCross;
    std::vector<GAXSKSourceKind>            mSourcesCross;
    
    std::vector<GAXSKNonceByteKind>         mNoncesOrbiterUpdate;
    std::vector<GAXSKNonceByteKind>         mNoncesWandererUpdate;
    
private:
    
    int                                     mSourceCount = 0;
    int                                     mOrbiterCount = 0;
    int                                     mWandererCount = 0;
    
};

#endif /* GAXSKPool_hpp */
