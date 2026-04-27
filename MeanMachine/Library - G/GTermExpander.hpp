//
//  GTermExpander.hpp
//  MeanMachine
//

#ifndef GTermExpander_hpp
#define GTermExpander_hpp

#include "GExpr.hpp"

enum class GTermPattern : std::uint8_t {
    kAdd = 0,
    kSub = 1,
    kXor = 2,
    kMul = 3,
    kRotate = 4,
    kMulThenAdd = 5,
    kMulThenSub = 6,
    kMulThenXor = 7,
    kRotateAdd = 8,
    kRotateSub = 9,
    kRotateXor = 10,
    kRotateMul = 11,
    kPostRotateAdd = 12,
    kPostRotateSub = 13,
    kPostRotateXor = 14,
    kPostRotateMul = 15
};

struct GTermExpander {
    
    static GExpr                Expand(GSymbol pSymbol, bool pAllowMultiply);
    static GExpr                Expand(GExpr pExpr, bool pAllowMultiply);
};

#endif /* GTermExpander_hpp */
