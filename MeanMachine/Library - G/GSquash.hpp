//
//  GSquash.hpp
//  MeanMachine
//
//  Created by nick raptis on 6/10/26.
//

#ifndef GSquash_hpp
#define GSquash_hpp

#include "GSeedProgram.hpp"
#include "GSymbol.hpp"
#include <cstdint>

class GSquash {
public:
    GSquash();
    
    bool                        Bake(GSymbol pDest,
                                     
                                     GSymbol pSourceA,
                                     GSymbol pSourceB,
                                     GSymbol pSourceC,
                                     GSymbol pSourceD,
                                     
                                     GSymbol pIndex,
                                     
                                     std::vector<GStatement> *pStatements,
                                     std::string *pErrorMessage);
    
};

#endif /* GSquash_hpp */
