//
//  GAXPLQuick.hpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#ifndef GAXPLQuick_hpp
#define GAXPLQuick_hpp

#include "GAXSK.hpp"
#include "GQuick.hpp"
#include "GSeedProgram.hpp"

#include <string>
#include <unordered_map>

class GAXPLQuick {
public:
    static GExpr                                Rotate(const GExpr &pExpr, int pRotation);
    static GExpr                                RotateSymbol(const GSymbol &pSymbol, int pRotation);
    
    static GExpr                                Diffuse(const GExpr &pExpr, GAXSKDiffuseKind pDiffuse);
    static GExpr                                DiffuseAndXor(const GExpr &pExpr,
                                                              const GExpr &pXor,
                                                              GAXSKDiffuseKind pDiffuse);
    
    static GSymbol                              DomainConstantIngress();
    static GSymbol                              DomainConstantScatter();
    static GSymbol                              DomainConstantCross();
    
    static bool                                 BakeInputSlotWord(const GAXSKInputSlot &pSlot,
                                                                  const std::unordered_map<GAXSKSourceKind, GSymbol> &pSourceMap,
                                                                  const std::unordered_map<GAXSKNonceByteKind, GSymbol> &pNonceMap,
                                                                  GExpr *pExpr,
                                                                  int pOffsetRangeLo,
                                                                  int pOffsetRangeHi,
                                                                  std::string *pErrorMessage);
    
    
    static bool                                 BakeInputSlotWordsXorSources(const std::vector<GAXSKInputSlot> &pInputs,
                                                                             const std::unordered_map<GAXSKSourceKind, GSymbol> &pSourceMap,
                                                                             const std::unordered_map<GAXSKNonceByteKind, GSymbol> &pNonceMap,
                                                                             GExpr *pExpr,
                                                                             int pOffsetRangeLo,
                                                                             int pOffsetRangeHi,
                                                                             std::string *pErrorMessage);
    
    static bool                                 BakeInputSlotWordsXorNonces(const std::vector<GAXSKInputSlot> &pInputs,
                                                                            const std::unordered_map<GAXSKSourceKind, GSymbol> &pSourceMap,
                                                                            const std::unordered_map<GAXSKNonceByteKind, GSymbol> &pNonceMap,
                                                                            GExpr *pExpr,
                                                                            std::string *pErrorMessage);
    
};

#endif /* GAXPLQuick_hpp */
