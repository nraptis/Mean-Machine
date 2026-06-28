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
                                                         GSymbol pOperationIndex,
                                                         GSymbol pSource,
                                                         GSymbol pSourceIndex,
                                                         GSymbol pDestination,
                                                         GSymbol pDestinationIndex,                                                         
                                                         std::vector<GStatement> *pStatements,
                                                         std::string *pErrorMessage);
    
    bool                                    BakeDispatch(GSymbol pOperation,
                                                         GSymbol pOperationIndex,
                                                         GSymbol pSource,
                                                         GSymbol pSourceIndex,
                                                         GSymbol pDestination,
                                                         GSymbol pDestinationIndex,
                                                         GSymbol pUnrollDomainWord,
                                                         GSymbol pArgADomainWord,
                                                         GSymbol pArgBDomainWord,
                                                         GSymbol pArgCDomainWord,
                                                         GSymbol pArgDDomainWord,
                                                         
                                                         std::vector<GStatement> *pStatements,
                                                         std::string *pErrorMessage);
    
    static void                             SetError(std::string *pErrorMessage,
                                                     const std::string &pMessage);

    
};

#endif /* GM88_hpp */
