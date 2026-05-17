//
//  GKDF.hpp
//  MeanMachine
//
//  Created by Dragon on 5/11/26.
//

#ifndef GKDF_hpp
#define GKDF_hpp

#include "GSeedProgram.hpp"
#include "TwistDomains.hpp"

#include <string>
#include <vector>

class GKDF {
public:
    bool                                Bake(TwistDomain pDomain,
                                             GSymbol pSourceBuffer,
                                             GSymbol pKDFBuffer,
                                             std::vector<GStatement> *pStatements,
                                             std::string *pErrorMessage);
};

#endif /* GKDF_hpp */
