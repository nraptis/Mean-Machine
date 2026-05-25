//
//  GSeedRunKDF3.hpp
//  MeanMachine
//
//  Created by nicholas on 5/25/26.
//

#ifndef GSeedRunKDF3_hpp
#define GSeedRunKDF3_hpp

#include "GTwistExpander.hpp"
#include "CSPRNGV2.hpp"
#include "GQuick.hpp"
#include "GMagicNumbers.hpp"
#include <string>

class GSeedRunKDF3 {
public:
    GSeedRunKDF3();
    ~GSeedRunKDF3();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);
    
private:
    void                                    Reset();
    
    std::vector<GSymbol>                    mSaltsOrbiterAssign;
    std::vector<GSymbol>                    mSaltsOrbiterUpdate;
    std::vector<GSymbol>                    mSaltsWandererUpdate;
    
    std::vector<GSymbol>                    mWorkLanes;
    std::vector<GSymbol>                    mOperationLanes;
    std::vector<GSymbol>                    mExpansionLanes;
    
    std::vector<GAXSKSkeleton>              mARXSkeletonsA;
    std::vector<GAXSKSkeleton>              mARXSkeletonsB;
    std::vector<GAXSKSkeleton>              mARXSkeletonsC;
    
    std::vector<GHotPack>                   mHotPacksA;
    std::vector<GHotPack>                   mHotPacksB;
    std::vector<GHotPack>                   mHotPacksC;
    
};


#endif /* GSeedRunKDF3_hpp */
