//
//  GSeedRunKDF.hpp
//  MeanMachine
//
//  Created by Codex on 5/10/26.
//

#ifndef GSeedRunKDF_hpp
#define GSeedRunKDF_hpp

#include "TwistWorkSpace.hpp"
#include "GTermExpander.hpp"
#include "GTwistExpander.hpp"
#include "GQuick.hpp"
#include "GMagicNumbers.hpp"
#include "CSPKDF.hpp"
#include <string>

class GSeedRunKDF {
public:
    GSeedRunKDF();
    ~GSeedRunKDF();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

    GSymbol                                 mLoopIndex;
    GSymbol                                 mSource;

    
    GSymbol                                 mStreamCross;
    GSymbol                                 mStreamCurrent;
    GSymbol                                 mStreamPrevious;
    GSymbol                                 mStreamScatter;
    
    GSymbol                                 mSecretCurrent;
    GSymbol                                 mSecretPrevious;
    GSymbol                                 mSecretScatter;
    GSymbol                                 mSecretWrite;
    
    GSymbol                                 mCarry;
    
    GSymbol                                 mPublicIngressDomainWord;
    GSymbol                                 mPrivateIngressDomainWord;
    GSymbol                                 mCrossIngressDomainWord;

private:
    void                                    Reset();

    std::vector<GSymbol>                    mListSBoxes;
    std::vector<GSymbol>                    mListWorkLanes;
    std::vector<GSymbol>                    mListOpLanes;
    std::vector<GSymbol>                    mListExpanders;
    
    GHotPack                                mHotPack;
    
};

#endif /* GSeedRunKDF_hpp */
