//
//  GSeedRunKDF2.hpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#ifndef GSeedRunKDF2_hpp
#define GSeedRunKDF2_hpp

//#include "TwistWorkSpace.hpp"
#include "GTwistExpander.hpp"
#include "CSPRNGV2.hpp"
#include "GQuick.hpp"
#include "GMagicNumbers.hpp"
#include <string>

class GSeedRunKDF2 {
public:
    GSeedRunKDF2();
    ~GSeedRunKDF2();

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
    std::vector<GAXSKSkeleton>              mARXSkeletons;
    
    std::vector<GHotPack>                   mHotPacks;
    
};


#endif /* GSeedRunKDF2_hpp */
