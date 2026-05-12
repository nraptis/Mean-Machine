//
//  CSPKDF.hpp
//  MeanMachine
//
//  Created by Dragon on 5/10/26.
//

#ifndef CSPKDF_hpp
#define CSPKDF_hpp

#include "GMagicNumbers.hpp"
#include "GLoopFragmentComposer.hpp"
#include "GLoopMixBrew.hpp"
#include "GQuick.hpp"
#include "GMagicNumbers.hpp"
#include "GARXPlan.hpp"

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
                     
                     GSymbol pStateA,
                     GSymbol pStateB,
                     GSymbol pStateC,
                     GSymbol pStateD,
                     GSymbol pStateE,
                     GSymbol pStateF,
                     
                     GSymbol pRoundA,
                     GSymbol pRoundB,
                     GSymbol pRoundC,
                     GSymbol pRoundD,
                     GSymbol pRoundE,
                     GSymbol pRoundF,
                     
                     GSymbol pDomainSaltA,
                     GSymbol pDomainSaltB,
                     GSymbol pDomainSaltC,
                     GSymbol pDomainSaltD,
                     GSymbol pDomainSaltE,
                     GSymbol pDomainSaltF,
                     
                     GSymbol pWorldSaltA,
                     GSymbol pWorldSaltB,
                     GSymbol pWorldSaltC,
                     GSymbol pWorldSaltD,
                     GSymbol pWorldSaltE,
                     GSymbol pWorldSaltF,
                     GSymbol pWorldSaltG,
                     GSymbol pWorldSaltH,
                     
                     GSymbol pPlugKeyA,
                     GSymbol pPlugKeyB,
                     
                     std::vector<GSymbol> pSBoxes,
                     
                     GHotPack pHotPack,
                     
                     std::vector<GStatement> *pStatements,
                     std::string *pErrorMessage);
    
};

#endif /* CSPKDF_hpp */
