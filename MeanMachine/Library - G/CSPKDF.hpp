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

struct TwistDomainSeedRoundMaterial;

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
                     
                     GSymbol pStreamCurrent,
                     GSymbol pStreamPrevious,
                     GSymbol pStreamScatter,
                     GSymbol pStreamCross,
                     
                     GSymbol pStreamScatterComponentA,
                     GSymbol pStreamScatterComponentB,
                     GSymbol pStreamScatterComponentC,
                     GSymbol pStreamScatterComponentD,
                     
                     GSymbol pSecretCurrent,
                     GSymbol pSecretPrevious,
                     GSymbol pSecretScatter,
                     GSymbol pSecretWrite,
                     
                     GSymbol pSecretScatterComponentA,
                     GSymbol pSecretScatterComponentB,
                     GSymbol pSecretScatterComponentC,
                     GSymbol pSecretScatterComponentD,
                     
                     GSymbol pCarry,
                     
                     GSymbol pUnwindA,
                     GSymbol pUnwindB,
                     GSymbol pUnwindC,
                     GSymbol pUnwindD,
                     GSymbol pUnwindE,
                     GSymbol pUnwindF,
                     
                     GSymbol pOrbiterA,
                     GSymbol pOrbiterB,
                     GSymbol pOrbiterC,
                     GSymbol pOrbiterD,
                     GSymbol pOrbiterE,
                     GSymbol pOrbiterF,

                     TwistDomainSeedRoundMaterial *pMatsUnwind,
                     TwistDomainSeedRoundMaterial *pMatsOrbiter,
                     TwistDomainSeedRoundMaterial *pMatsOrbiterInit,
                     
                     GSymbol pPlugKeyA,
                     GSymbol pPlugKeyB,
                     GSymbol pPlugKeyC,
                     GSymbol pPlugKeyD,
                     GSymbol pPlugKeyE,
                     GSymbol pPlugKeyF,
                     
                     std::vector<GSymbol> pSBoxes,
                     
                     GHotPack pHotPack,
                     
                     std::vector<GStatement> *pStatements,
                     std::string *pErrorMessage);
    
};

#endif /* CSPKDF_hpp */
