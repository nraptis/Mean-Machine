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
    kMix64_1 = 14,
    kMix64_4 = 15,
    kMix64_8 = 16,
    kRotL64 = 17,
    kDiffuse64 = 18
};

enum class GReadWrapType : std::uint8_t {
    kNone = 0,
    kBlock = 1,
    kSBox = 2,
    kSalt = 3,
    kMaskA = 4,
    kMaskB = 5,
    kKeyA = 6,
    kKeyB = 7
};

struct GExpr {
    
public:
    GExprType                           mType;
    GSymbol                             mSymbol;
    std::uint64_t                       mConstVal;

    GReadWrapType                       mReadWrapType;
    GSymbol                             mReadWrapIndexSymbol;
    GSymbol                             mReadWrapOracleSymbol;
    int                                 mReadWrapOffset;

    Mix64Type_1                         mMix64Type1;
    Mix64Type_4                         mMix64Type4;
    Mix64Type_8                         mMix64Type8;
    bool                                mMix64UseAmount;
    std::uint64_t                       mMix64Amount;
    GSymbol                             mMix64SBoxA;
    GSymbol                             mMix64SBoxB;
    GSymbol                             mMix64SBoxC;
    GSymbol                             mMix64SBoxD;
    GSymbol                             mMix64SBoxE;
    GSymbol                             mMix64SBoxF;
    GSymbol                             mMix64SBoxG;
    GSymbol                             mMix64SBoxH;
    
    // buffer reads use mSymbol as the source and mIndex as the wrapped index.
    std::shared_ptr<GExpr>              mIndex;

    // ops use mA and mB.
    std::shared_ptr<GExpr>              mA;
    std::shared_ptr<GExpr>              mB;
    
    GExpr();
    
    static GExpr                        Symbol(const GSymbol &pSymbol);
    static GExpr                        Const8(int pVal);
    static GExpr                        Const32(int pVal);
    static GExpr                        Const64(std::uint64_t pVal);
    static GExpr                        Diffuse(std::uint64_t pVal);
    static GExpr                        Diffuse(const GExpr &pExpr);
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
    
    static GExpr                        Mix64_1(const GExpr &pValue,
                                                Mix64Type_1 pMixType,
                                                const GSymbol &pSBoxA);
    static GExpr                        Mix64_4(const GExpr &pValue,
                                                Mix64Type_4 pMixType,
                                                const GSymbol &pSBoxA,
                                                const GSymbol &pSBoxB,
                                                const GSymbol &pSBoxC,
                                                const GSymbol &pSBoxD);
    static GExpr                        Mix64_8(const GExpr &pValue,
                                                Mix64Type_8 pMixType,
                                                const GSymbol &pSBoxA,
                                                const GSymbol &pSBoxB,
                                                const GSymbol &pSBoxC,
                                                const GSymbol &pSBoxD,
                                                const GSymbol &pSBoxE,
                                                const GSymbol &pSBoxF,
                                                const GSymbol &pSBoxG,
                                                const GSymbol &pSBoxH);
    static GExpr                        Mix64_1(const GExpr &pValue,
                                                Mix64Type_1 pMixType,
                                                std::uint64_t pAmount,
                                                const GSymbol &pSBoxA);
    static GExpr                        Mix64_4(const GExpr &pValue,
                                                Mix64Type_4 pMixType,
                                                std::uint64_t pAmount,
                                                const GSymbol &pSBoxA,
                                                const GSymbol &pSBoxB,
                                                const GSymbol &pSBoxC,
                                                const GSymbol &pSBoxD);
    static GExpr                        Mix64_8(const GExpr &pValue,
                                                Mix64Type_8 pMixType,
                                                std::uint64_t pAmount,
                                                const GSymbol &pSBoxA,
                                                const GSymbol &pSBoxB,
                                                const GSymbol &pSBoxC,
                                                const GSymbol &pSBoxD,
                                                const GSymbol &pSBoxE,
                                                const GSymbol &pSBoxF,
                                                const GSymbol &pSBoxG,
                                                const GSymbol &pSBoxH);
    
    // what this means.
    // in c++ code
    // before this statement
    // we need:
    // pIndexOracle = pIndex + pOffset;
    // pIndexOracle &= 0x1FFFU;
    //
    // then, the inbuilt twist library does not do the if-statement injection, or the extra assignment.
    //
    static GExpr                        ReadBlockWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle, int pOffset);
    static GExpr                        ReadSBoxWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle, int pOffset);
    static GExpr                        ReadSaltWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle, int pOffset);
    static GExpr                        ReadMaskAWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle, int pOffset);
    static GExpr                        ReadMaskBWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle, int pOffset);
    static GExpr                        ReadKeyAWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle, int pOffset);
    static GExpr                        ReadKeyBWrap(const GSymbol &pSymbol, const GSymbol &pIndex, const GSymbol &pIndexOracle, int pOffset);
    
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
