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

    GSymbol                                 mWandererA;
    GSymbol                                 mWandererB;
    GSymbol                                 mWandererC;
    GSymbol                                 mWandererD;
    GSymbol                                 mWandererE;
    GSymbol                                 mWandererF;

    GSymbol                                 mOrbiterA;
    GSymbol                                 mOrbiterB;
    GSymbol                                 mOrbiterC;
    GSymbol                                 mOrbiterD;
    GSymbol                                 mOrbiterE;
    GSymbol                                 mOrbiterF;

    GSymbol                                 mPlugKeyA;
    GSymbol                                 mPlugKeyB;

    // Defaults to Source-domain salts, but callers can override before Build().
    GSymbol                                 mDomainSaltA;
    GSymbol                                 mDomainSaltB;
    GSymbol                                 mDomainSaltC;
    GSymbol                                 mDomainSaltD;
    GSymbol                                 mDomainSaltE;
    GSymbol                                 mDomainSaltF;
    
    GSymbol                                 mPublicIngressDomainWord;
    GSymbol                                 mPrivateIngressDomainWord;
    GSymbol                                 mCrossIngressDomainWord;

private:
    void                                    Reset();

    std::vector<GSymbol>                    mListSBoxes;
    std::vector<GSymbol>                    mListWorldSalts;
    std::vector<GSymbol>                    mListWorkers;
    std::vector<GSymbol>                    mListOpLanes;
    
    GHotPack                                mHotPack;
    
};

#endif /* GSeedRunKDF_hpp */
