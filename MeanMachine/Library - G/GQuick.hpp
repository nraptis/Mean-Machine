//
//  GQuickStatement.hpp
//  MeanMachine
//
//  Created by Dragon on 5/1/26.
//

#ifndef GQuickStatement_hpp
#define GQuickStatement_hpp

#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"
#include "GSymbol.hpp"
#include "GSeedProgram.hpp"

class GQuick {
public:
    
    static GStatement                               MakeAssignDestStatement(const GSymbol pDest, const GSymbol pIndex, const GSymbol pValue);
    
    static GStatement                               MakeAssignOffsetByteStatement(const GSymbol pTarget, const GSymbol pSource,
                                                                                  const GSymbol pIndex, const int pOffset);
    
};

#endif /* GQuickStatement_hpp */
