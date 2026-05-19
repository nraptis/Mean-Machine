//
//  CSPKDF.hpp
//  MeanMachine
//
//  Created by Dragon on 5/10/26.
//

#ifndef CSPKDF_hpp
#define CSPKDF_hpp

#include "GMagicNumbers.hpp"
#include "GQuick.hpp"
#include "GMagicNumbers.hpp"
#include "GARXPlan.hpp"

struct GDomainSeedRoundMaterial {
    GSymbol                                  mSaltA;
    GSymbol                                  mSaltB;
    GSymbol                                  mSaltC;
    GSymbol                                  mSaltD;
    GSymbol                                  mSaltE;
    GSymbol                                  mSaltF;
};

struct GDomainSaltSet {
    GDomainSeedRoundMaterial                 mWanderer;
    GDomainSeedRoundMaterial                 mOrbiter;
};

class CSPKDF {
    
public:

    static bool Bake(GARXPassPlan *pPassPlan,
                     
                     GSymbol pDest,
                     bool pDestWriteInverted,
                     
                     GSymbol pLoopIndex,
                     
                     GExpr pPublicIngressSourceA,
                     GExpr pPublicIngressSourceB,
                     GExpr pPublicIngressSourceC,
                     GExpr pPublicIngressSourceD,
                     
                     GExpr pPrivateIngressSourceA,
                     GExpr pPrivateIngressSourceB,
                     GExpr pPrivateIngressSourceC,
                     GExpr pPrivateIngressSourceD,
                     
                     GExpr pCrossIngressSourceA,
                     GExpr pCrossIngressSourceB,
                     GExpr pCrossIngressSourceC,
                     GExpr pCrossIngressSourceD,
                     
                     GExpr pPublicIngressDomainWord,
                     GExpr pPrivateIngressDomainWord,
                     GExpr pCrossIngressDomainWord,
                     
                     GSymbol pStreamScatterComponentA,
                     GSymbol pStreamScatterComponentB,
                     GSymbol pStreamScatterComponentC,
                     GSymbol pStreamScatterComponentD,
                     
                     GSymbol pSecretScatterComponentA,
                     GSymbol pSecretScatterComponentB,
                     GSymbol pSecretScatterComponentC,
                     GSymbol pSecretScatterComponentD,
                     
                     const GDomainSaltSet &pDomainSaltSet,
                     
                     GHotPack pHotPack,
                     
                     std::vector<GStatement> *pStatements,
                     std::string *pErrorMessage);
    
};

#endif /* CSPKDF_hpp */
