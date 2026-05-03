//
//  CSPRNG.hpp
//  MeanMachine
//
//  Created by Dragon on 5/2/26.
//

#ifndef CSPRNG_hpp
#define CSPRNG_hpp

#include <stdio.h>
#include "GMagicNumbers.hpp"
#include "GFamily.hpp"
#include "GLoopFragmentComposer.hpp"
#include "GLoopMixBrew.hpp"
#include "GQuick.hpp"
#include "GSelect.hpp"
#include "GMagicNumbers.hpp"

//#include "GFastMatrix.hpp"

class CSPRNG {
    
public:
    
    static bool             Bake(bool pWriteReversed,
                                 int pFamilyIndex,
                                 
                                 GSymbol pDest,
                                 GSymbol pLoopIndex,
                                 
                                 GSymbol pFreshByte,
                                 
                                 GSymbol pValue,
                                 GSymbol pValuePrevious,
                                 GSymbol pValueMix,
                                 
                                 
                                 GSymbol pSecureByteA,
                                 GSymbol pSecureByteB,
                                 
                                 GSymbol pCross,
                                 
                                 GSymbol pSelect,
                                 
                                 GSymbol pCarry,
                                 
                                 GSymbol pHalfA,
                                 GSymbol pHalfB,
                                 
                                 
                                 GSymbol pFixedSaltA,
                                 GSymbol pFixedSaltB,
                                 GSymbol pFixedSaltC,
                                 GSymbol pFixedSaltD,
                                 
                                 
                                 GSymbol pScratchSaltA,
                                 GSymbol pScratchSaltB,
                                 GSymbol pScratchSaltC,
                                 GSymbol pScratchSaltD,
                                 
                                 
                                 GSymbol pSBoxA,
                                 GSymbol pSBoxB,
                                 GSymbol pSBoxC,
                                 GSymbol pSBoxD,
                                 
                                 GSymbol pWandererA,
                                 GSymbol pWandererB,
                                 GSymbol pWandererC,
                                 
                                 GSymbol pOrbiterA,
                                 GSymbol pOrbiterB,
                                 GSymbol pOrbiterC,
                                 GSymbol pOrbiterD,
                                 
                                 Mix64Type_4 pMixTypeA,
                                 Mix64Type_4 pMixTypeB,
                                 Mix64Type_4 pMixTypeC,
                                 Mix64Type_4 pMixTypeD,
                                 
                                 GRotationFamily &pRotationFamily,
                                 GHotPack pHotPack,
                                 
                                 std::vector<GStatement> *pStatements,
                                 std::string *pErrorMessage);
    
    
    
};

#endif /* CSPRNG_hpp */
