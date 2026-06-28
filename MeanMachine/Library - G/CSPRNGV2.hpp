//
//  CSPRNGV2.hpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/18/26.
//

#ifndef CSPRNGV2_hpp
#define CSPRNGV2_hpp

#include "GMagicNumbers.hpp"
#include "GQuick.hpp"
#include "GMagicNumbers.hpp"
#include "GAX.hpp"
#include "GCache.hpp"
#include <string>

struct CSPRNGV2Slice {
    
    // These are set by kdf:
    GAXSKSkeleton               mARXSkeleton;
    GSymbol                     mDest;
    bool                        mDestWriteInverted;
    std::vector<GSymbol>        mSources;
    int                         mSourceRangesLo;
    int                         mSourceRangesHi;
    
    GHotPack                    mHotPack;
    TwistDomain                 mDomain = TwistDomain::kInvalid;
    
    // These are not set by kdf:
    GAXPLSaltBag                mSaltBag;
    std::vector<GSymbol>        mSaltsOrbiterAssign;
    std::vector<GSymbol>        mSaltsOrbiterUpdate;
    std::vector<GSymbol>        mSaltsWandererUpdate;
    std::vector<GSymbol>        mNonceBytes;
    
    std::vector<GSymbol>        mOrbiters;
    std::vector<GSymbol>        mWanderers;
    
    int                         mLoopCeiling;
    int                         mLoopBegin;
    std::string                 mLoopBeginText;
    std::string                 mLoopEndText;
};

class CSPRNGV2 {
public:
    static bool Bake(bool pIsNonKDF,
                     TwistDomain pDomain,
                     
                     std::vector<CSPRNGV2Slice> &pSlices,
                     const std::vector<GSymbol> &pSaltsOrbiterAssign,
                     const std::vector<GSymbol> &pSaltsOrbiterUpdate,
                     const std::vector<GSymbol> &pSaltsWandererUpdate,
                     std::vector<GLoop> *pLoops,
                     bool pAutoRangeAdjust,
                     std::string *pErrorMessage);
    
};

#endif /* CSPRNGV2_hpp */
