//
//  GExpr.hpp
//  Moose Rib
//
//  Created by Whale Farts on 4/20/26.
//

#ifndef GExpr_hpp
#define GExpr_hpp

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "GSymbol.hpp"

enum class GOperType : std::uint8_t {
    kInv = 0,
    kRead = 3,
    kAdd = 4,
    kSub = 5,
    kMul = 6,
    kXor = 7,
    kAnd = 8,
    kRotateLeft8 = 9,
    kRotateRight8 = 10
};

enum class GExprType : std::uint8_t {
    kInv = 0,
    kSymbol = 1,
    kConst = 2,
    kRead = 3,
    kAdd = 4,
    kSub = 5,
    kMul = 6,
    kXor = 7,
    kAnd = 8,
    kRotateLeft8 = 9,
    kRotateRight8 = 10
};

struct GExpr {
    
public:
    GExprType                   mType;
    GSymbol                     mSymbol;
    std::uint64_t               mConstVal;
    
    // buffer reads use mSymbol as the source and mIndex as the wrapped index.
    std::shared_ptr<GExpr>      mIndex;

    // ops use mA and mB.
    std::shared_ptr<GExpr>      mA;
    std::shared_ptr<GExpr>      mB;
    
    GExpr();
    
    static GExpr                Symbol(const GSymbol &pSymbol);
    static GExpr                Const(std::uint64_t pVal);
    static GExpr                Read(const GSymbol &pSymbol,
                                     const GExpr &pIndex);
    static GExpr                Add(const GExpr &a, const GExpr &b);
    static GExpr                Sub(const GExpr &a, const GExpr &b);
    static GExpr                Mul(const GExpr &a, const GExpr &b);
    static GExpr                Xor(const GExpr &a, const GExpr &b);
    static GExpr                And(const GExpr &a, const GExpr &b);
    static GExpr                RotateLeft8(const GExpr &a, const GExpr &b);
    static GExpr                RotateRight8(const GExpr &a, const GExpr &b);
    
    void                        Set(const GExpr &pOther);
    void                        Invalidate();
    
    bool                        IsInvalid() const;
    bool                        IsSymbol() const;
    bool                        IsConst() const;
    bool                        IsRead() const;
    
    std::vector<GSymbol>        GetSymbols() const;
    std::vector<GOperType>      GetOps() const;
    
    
};

bool                                    operator == (const GExpr &pLHS, const GExpr &pRHS);
bool                                    operator != (const GExpr &pLHS, const GExpr &pRHS);
std::string                             GExprKey(const GExpr &pExpr);

#endif
