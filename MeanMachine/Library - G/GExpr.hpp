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
#include "TwistMix32.hpp"
#include "TwistMix64.hpp"

enum class GOperType : std::uint8_t {
    kInv = 0,
    kRead = 3,
    kAdd = 4,
    kSub = 5,
    kMul = 6,
    kXor = 7,
    kAnd = 8,
    kRotL8 = 9,
    kRotL32 = 10,
    kShiftL = 11,
    kShiftR = 12,
    kOr = 13,
    kRotL64 = 14
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
    kRotL8 = 9,
    kRotL32 = 10,
    kShiftL = 11,
    kShiftR = 12,
    kOr = 13,
    kRotL64 = 17,
    kDiffuse64A = 18,
    kDiffuse64B = 19,
    kDiffuse64C = 20,
    kDiffuse32A = 21,
    kDiffuse32B = 22,
    kDiffuse32C = 23,
    kCast32 = 24
};

enum class GReadWrapType : std::uint8_t {
    kNone = 0,
    kBlock = 1,
    kSBox = 2,
    kSalt = 3,
    kKeyA = 4,
    kKeyB = 5
};

struct GExpr {
    
public:
    GExprType                           mType;
    GSymbol                             mSymbol;
    std::uint64_t                       mConstVal;
    bool                                mConstPreferHex;

    GReadWrapType                       mReadWrapType;
    GSymbol                             mReadWrapIndexSymbol;
    GSymbol                             mReadWrapOracleSymbol;

    // buffer reads use mSymbol as the source and mIndex as the wrapped index.
    std::shared_ptr<GExpr>              mIndex;

    // ops use mA and mB.
    std::shared_ptr<GExpr>              mA;
    std::shared_ptr<GExpr>              mB;
    
    GExpr();
    
    static GExpr                        Symbol(const GSymbol &pSymbol);
    static GExpr                        Const(std::uint64_t pVal);
    static GExpr                        Const8(int pVal);
    static GExpr                        Const32(int pVal);
    static GExpr                        Const64(std::uint64_t pVal);
    static GExpr                        Const64Hex(std::uint64_t pVal);
    static GExpr                        Cast32(const GExpr &pExpr);
    static GExpr                        Diffuse64A(std::uint64_t pVal);
    static GExpr                        Diffuse64A(const GExpr &pExpr);
    static GExpr                        Diffuse64B(std::uint64_t pVal);
    static GExpr                        Diffuse64B(const GExpr &pExpr);
    static GExpr                        Diffuse64C(std::uint64_t pVal);
    static GExpr                        Diffuse64C(const GExpr &pExpr);
    static GExpr                        Diffuse32A(std::uint32_t pVal);
    static GExpr                        Diffuse32A(const GExpr &pExpr);
    static GExpr                        Diffuse32B(std::uint32_t pVal);
    static GExpr                        Diffuse32B(const GExpr &pExpr);
    static GExpr                        Diffuse32C(std::uint32_t pVal);
    static GExpr                        Diffuse32C(const GExpr &pExpr);
    static GExpr                        Read(const GSymbol &pSymbol, const GExpr &pIndex);
    static GExpr                        Add(const GExpr &a, const GExpr &b);
    static GExpr                        Add(const GSymbol &a, const GSymbol &b);
    static GExpr                        Add(const GSymbol &a, const GExpr &b);
    static GExpr                        Add(const GExpr &a, const GSymbol &b);
    static GExpr                        Add(const GSymbol &a, std::uint64_t b);
    static GExpr                        Add(const GExpr &a, std::uint64_t b);
    static GExpr                        Sub(const GExpr &a, const GExpr &b);
    static GExpr                        Sub(const GSymbol &a, const GSymbol &b);
    static GExpr                        Sub(const GSymbol &a, const GExpr &b);
    static GExpr                        Sub(const GExpr &a, const GSymbol &b);
    static GExpr                        Sub(const GSymbol &a, std::uint64_t b);
    static GExpr                        Sub(const GExpr &a, std::uint64_t b);
    static GExpr                        Mul(const GExpr &a, const GExpr &b);
    static GExpr                        Mul(const GSymbol &a, const GSymbol &b);
    static GExpr                        Mul(const GSymbol &a, const GExpr &b);
    static GExpr                        Mul(const GExpr &a, const GSymbol &b);
    static GExpr                        Mul(const GSymbol &a, std::uint64_t b);
    static GExpr                        Mul(const GExpr &a, std::uint64_t b);
    static GExpr                        Xor(const GExpr &a, const GExpr &b);
    static GExpr                        Xor(const GSymbol &a, const GSymbol &b);
    static GExpr                        Xor(const GSymbol &a, const GExpr &b);
    static GExpr                        Xor(const GExpr &a, const GSymbol &b);
    static GExpr                        Xor(const GSymbol &a, std::uint64_t b);
    static GExpr                        Xor(const GExpr &a, std::uint64_t b);
    static GExpr                        And(const GExpr &a, const GExpr &b);
    static GExpr                        And(const GSymbol &a, const GSymbol &b);
    static GExpr                        And(const GSymbol &a, const GExpr &b);
    static GExpr                        And(const GExpr &a, const GSymbol &b);
    static GExpr                        And(const GSymbol &a, std::uint64_t b);
    static GExpr                        And(const GExpr &a, std::uint64_t b);
    static GExpr                        Or(const GExpr &a, const GExpr &b);
    static GExpr                        Or(const GSymbol &a, const GSymbol &b);
    static GExpr                        Or(const GSymbol &a, const GExpr &b);
    static GExpr                        Or(const GExpr &a, const GSymbol &b);
    static GExpr                        Or(const GSymbol &a, std::uint64_t b);
    static GExpr                        Or(const GExpr &a, std::uint64_t b);
    static GExpr                        RotL8(const GExpr &a, const GExpr &b);
    static GExpr                        RotL8(const GSymbol &a, const GSymbol &b);
    static GExpr                        RotL8(const GSymbol &a, const GExpr &b);
    static GExpr                        RotL8(const GExpr &a, const GSymbol &b);
    static GExpr                        RotL8(const GSymbol &a, std::uint64_t b);
    static GExpr                        RotL8(const GExpr &a, std::uint64_t b);
    static GExpr                        RotL32(const GExpr &a, const GExpr &b);
    static GExpr                        RotL32(const GSymbol &a, const GSymbol &b);
    static GExpr                        RotL32(const GSymbol &a, const GExpr &b);
    static GExpr                        RotL32(const GExpr &a, const GSymbol &b);
    static GExpr                        RotL32(const GSymbol &a, std::uint64_t b);
    static GExpr                        RotL32(const GExpr &a, std::uint64_t b);
    static GExpr                        RotL64(const GExpr &a, const GExpr &b);
    static GExpr                        RotL64(const GSymbol &a, const GSymbol &b);
    static GExpr                        RotL64(const GSymbol &a, const GExpr &b);
    static GExpr                        RotL64(const GExpr &a, const GSymbol &b);
    static GExpr                        RotL64(const GSymbol &a, std::uint64_t b);
    static GExpr                        RotL64(const GExpr &a, std::uint64_t b);
    static GExpr                        ShiftL(const GExpr &a, const GExpr &b);
    static GExpr                        ShiftL(const GSymbol &a, const GSymbol &b);
    static GExpr                        ShiftL(const GSymbol &a, const GExpr &b);
    static GExpr                        ShiftL(const GExpr &a, const GSymbol &b);
    static GExpr                        ShiftL(const GSymbol &a, std::uint64_t b);
    static GExpr                        ShiftL(const GExpr &a, std::uint64_t b);
    static GExpr                        ShiftR(const GExpr &a, const GExpr &b);
    static GExpr                        ShiftR(const GSymbol &a, const GSymbol &b);
    static GExpr                        ShiftR(const GSymbol &a, const GExpr &b);
    static GExpr                        ShiftR(const GExpr &a, const GSymbol &b);
    static GExpr                        ShiftR(const GSymbol &a, std::uint64_t b);
    static GExpr                        ShiftR(const GExpr &a, std::uint64_t b);
    
    // before this statement, c++ code needs to populate pIndexOracle from pIndex.
    static GExpr                        ReadBlockWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle);
    static GExpr                        ReadSBoxWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle);
    static GExpr                        ReadSaltWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle);
    static GExpr                        ReadKeyAWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle);
    static GExpr                        ReadKeyBWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle);
    
    void                                Set(const GExpr &pOther);
    void                                Invalidate();
    
    bool                                IsInvalid() const;
    bool                                IsSymbol() const;
    bool                                IsConst() const;
    bool                                IsRead() const;
    
    std::vector<GSymbol>                GetSymbols() const;
    std::vector<GOperType>              GetOps() const;
    
};

bool                                    operator == (const GExpr &pLHS, const GExpr &pRHS);
bool                                    operator != (const GExpr &pLHS, const GExpr &pRHS);
std::string                             GExprKey(const GExpr &pExpr);

GOperType                               OperTypeForExprType(const GExprType pType);
GOperType                               OperTypeForExpr(const GExpr pExpr);

#endif
