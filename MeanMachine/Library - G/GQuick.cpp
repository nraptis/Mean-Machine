//
//  GQuickStatement.cpp
//  MeanMachine
//
//  Created by Dragon on 5/1/26.
//

#include "GQuick.hpp"


GStatement GQuick::MakeAssignDestStatement(const GSymbol pDest, const GSymbol pIndex, const GSymbol pValue) {
    GExpr aIndexExpr = GExpr::Symbol(pIndex);
    GExpr aValueExpr = GExpr::Symbol(pValue);
    GTarget aDestTarget = GTarget::Write(pDest, aIndexExpr);
    return GStatement::Assign(aDestTarget, aValueExpr);
}

GStatement GQuick::MakeAssignOffsetByteStatement(const GSymbol pTarget,
                                                 const GSymbol pSource,
                                                 const GSymbol pIndex,
                                                 const int pOffset) {
    GTarget aDestTarget = GTarget::Symbol(pTarget);
    GExpr aIndexPlusOffsetExpr = GExpr::Add(GExpr::Symbol(pIndex), GExpr::Const(pOffset));
    GExpr aSourceIndexExpr = GExpr::Read(pSource, aIndexPlusOffsetExpr);
    return GStatement::Assign(aDestTarget, aSourceIndexExpr);
}
