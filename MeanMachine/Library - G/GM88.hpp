//
//  GM88.hpp
//  MeanMachine
//
//  Created by nick raptis on 6/8/26.
//

#ifndef GM88_hpp
#define GM88_hpp

#include "GSeedProgram.hpp"

#include <cstdint>
#include <string>
#include <vector>


class GM88 {
public:
    
    GM88();
    
    void                                    Clear();
    
    bool                                    BakeDispatch(GSymbol pOperation,
                                                         GExpr pOperationIndex,
                                                         GSymbol pSource,
                                                         GExpr pSourceIndex,
                                                         GSymbol pDestination,
                                                         GExpr pDestinationIndex,
                                                         GExpr pUnrollDomainWord,
                                                         GExpr pArgADomainWord,
                                                         GExpr pArgBDomainWord,
                                                         GExpr pArgCDomainWord,
                                                         GExpr pArgDDomainWord,
                                                         
                                                         std::vector<GStatement> *pStatements,
                                                         std::string *pErrorMessage);
    
    static void                             SetError(std::string *pErrorMessage,
                                                     const std::string &pMessage);

    
};

#endif /* GM88_hpp */
