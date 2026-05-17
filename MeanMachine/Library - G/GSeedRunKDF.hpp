//
//  GSeedRunKDF.hpp
//  MeanMachine
//
//  Created by Codex on 5/10/26.
//

#ifndef GSeedRunKDF_hpp
#define GSeedRunKDF_hpp

#include "GLoopFragmentComposer.hpp"
#include "TwistWorkSpace.hpp"
#include "GTermExpander.hpp"
#include "GTwistExpander.hpp"
#include "GQuick.hpp"
#include "GMagicNumbers.hpp"
#include "GFamily.hpp"
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

    
    GSymbol                                 mStreamCurrent;
    GSymbol                                 mStreamPrevious;
    GSymbol                                 mStreamScatter;
    
    GSymbol                                 mSecretCurrent;
    GSymbol                                 mSecretPrevious;
    GSymbol                                 mSecretScatter;
    GSymbol                                 mSecretWrite;
    
    GSymbol                                 mStreamCross;
    GSymbol                                 mCarry;

    GSymbol                                 mUnwindA;
    GSymbol                                 mUnwindB;
    GSymbol                                 mUnwindC;
    GSymbol                                 mUnwindD;
    GSymbol                                 mUnwindE;
    GSymbol                                 mUnwindF;

    GSymbol                                 mOrbiterA;
    GSymbol                                 mOrbiterB;
    GSymbol                                 mOrbiterC;
    GSymbol                                 mOrbiterD;
    GSymbol                                 mOrbiterE;
    GSymbol                                 mOrbiterF;

    GSymbol                                 mPlugKeyA;
    GSymbol                                 mPlugKeyB;
    GSymbol                                 mPlugKeyC;
    GSymbol                                 mPlugKeyD;
    GSymbol                                 mPlugKeyE;
    GSymbol                                 mPlugKeyF;

    GSymbol                                 mPublicIngressDomainWord;
    GSymbol                                 mPrivateIngressDomainWord;
    GSymbol                                 mCrossIngressDomainWord;

private:
    void                                    Reset();

    std::vector<GSymbol>                    mListSBoxes;
    std::vector<GSymbol>                    mListWorkers;
    std::vector<GSymbol>                    mListOpLanes;
    std::vector<GSymbol>                    mListExpanders;
    
    GHotPack                                mHotPack;
    
};

#endif /* GSeedRunKDF_hpp */
