//
//  GExpr.cpp
//  Moose Rib
//
//  Created by Whale Farts on 4/20/26.
//

#include "GExpr.hpp"

GOperType OperTypeForExprType(const GExprType pType) {
    switch (pType) {
        case GExprType::kRead: return GOperType::kRead;
        case GExprType::kAdd: return GOperType::kAdd;
        case GExprType::kSub: return GOperType::kSub;
        case GExprType::kMul: return GOperType::kMul;
        case GExprType::kXor: return GOperType::kXor;
        case GExprType::kAnd: return GOperType::kAnd;
        case GExprType::kRotL8: return GOperType::kRotL8;
        case GExprType::kRotL32: return GOperType::kRotL32;
        case GExprType::kRotL64: return GOperType::kRotL64;
        case GExprType::kShiftL: return GOperType::kShiftL;
        case GExprType::kShiftR: return GOperType::kShiftR;
        case GExprType::kOr: return GOperType::kOr;
        case GExprType::kDiffuse64A: return GOperType::kInv;
        case GExprType::kDiffuse64B: return GOperType::kInv;
        case GExprType::kDiffuse64C: return GOperType::kInv;
        case GExprType::kDiffuse32A: return GOperType::kInv;
        case GExprType::kDiffuse32B: return GOperType::kInv;
        case GExprType::kDiffuse32C: return GOperType::kInv;
        case GExprType::kCast32: return GOperType::kInv;
        default: return GOperType::kInv;
    }
}

GOperType OperTypeForExpr(const GExpr pExpr) {
    return OperTypeForExprType(pExpr.mType);
}

namespace {

GExpr BinaryExpr(const GExprType pType,
                 const GExpr &pA,
                 const GExpr &pB) {
    GExpr aExpr;
    aExpr.mType = pType;
    aExpr.mA = std::make_shared<GExpr>(pA);
    aExpr.mB = std::make_shared<GExpr>(pB);
    return aExpr;
}

bool HasReadWrap(const GExpr &pExpr) {
    return pExpr.mReadWrapType != GReadWrapType::kNone;
}

GExpr BuildWrappedRead(const GReadWrapType pWrapType,
                       const GSymbol &pSymbol,
                       const GSymbol &pIndex,
                       const GSymbol &pIndexOracle) {
    if (pSymbol.IsInvalid() || pIndex.IsInvalid()) {
        return GExpr();
    }

    if (pIndexOracle.IsInvalid()) {
        return GExpr::Read(pSymbol, GExpr::Symbol(pIndex));
    }

    GExpr aExpr = GExpr::Read(pSymbol, GExpr::Symbol(pIndexOracle));
    aExpr.mReadWrapType = pWrapType;
    aExpr.mReadWrapIndexSymbol = pIndex;
    aExpr.mReadWrapOracleSymbol = pIndexOracle;
    return aExpr;
}

void AppendSymbols(const GExpr &pExpr,
                   std::vector<GSymbol> *pSymbols) {
    if (pSymbols == NULL || pExpr.IsInvalid()) {
        return;
    }

    switch (pExpr.mType) {
        case GExprType::kSymbol:
            pSymbols->push_back(pExpr.mSymbol);
            return;

        case GExprType::kRead:
            pSymbols->push_back(pExpr.mSymbol);
            if (pExpr.mIndex != nullptr) {
                AppendSymbols(*pExpr.mIndex, pSymbols);
            }
            if (HasReadWrap(pExpr)) {
                pSymbols->push_back(pExpr.mReadWrapIndexSymbol);
                pSymbols->push_back(pExpr.mReadWrapOracleSymbol);
            }
            return;
        case GExprType::kDiffuse64A:
        case GExprType::kDiffuse64B:
        case GExprType::kDiffuse64C:
        case GExprType::kDiffuse32A:
        case GExprType::kDiffuse32B:
        case GExprType::kDiffuse32C:
        case GExprType::kCast32:
            if (pExpr.mA != nullptr) {
                AppendSymbols(*pExpr.mA, pSymbols);
            }
            return;

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kOr:
        case GExprType::kRotL8:
        case GExprType::kRotL32:
        case GExprType::kRotL64:
        case GExprType::kShiftL:
        case GExprType::kShiftR:
            if (pExpr.mA != nullptr) {
                AppendSymbols(*pExpr.mA, pSymbols);
            }
            if (pExpr.mB != nullptr) {
                AppendSymbols(*pExpr.mB, pSymbols);
            }
            return;

        default:
            return;
    }
}

void AppendOps(const GExpr &pExpr,
               std::vector<GOperType> *pOps) {
    if (pOps == NULL || pExpr.IsInvalid()) {
        return;
    }

    switch (pExpr.mType) {
        case GExprType::kRead:
            if (pExpr.mIndex != nullptr) {
                AppendOps(*pExpr.mIndex, pOps);
            }
            pOps->push_back(GOperType::kRead);
            return;

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kOr:
        case GExprType::kRotL8:
        case GExprType::kRotL32:
        case GExprType::kRotL64:
        case GExprType::kShiftL:
        case GExprType::kShiftR:
            if (pExpr.mA != nullptr) {
                AppendOps(*pExpr.mA, pOps);
            }
            if (pExpr.mB != nullptr) {
                AppendOps(*pExpr.mB, pOps);
            }
            pOps->push_back(OperTypeForExprType(pExpr.mType));
            return;
        case GExprType::kDiffuse64A:
        case GExprType::kDiffuse64B:
        case GExprType::kDiffuse64C:
        case GExprType::kDiffuse32A:
        case GExprType::kDiffuse32B:
        case GExprType::kDiffuse32C:
        case GExprType::kCast32:
            if (pExpr.mA != nullptr) {
                AppendOps(*pExpr.mA, pOps);
            }
            return;

        default:
            return;
    }
}

bool ExprPtrEqual(const std::shared_ptr<GExpr> &pLHS,
                  const std::shared_ptr<GExpr> &pRHS) {
    if (pLHS == nullptr || pRHS == nullptr) {
        return pLHS == pRHS;
    }
    return (*pLHS == *pRHS);
}

std::string ExprKeyInner(const GExpr &pExpr) {
    switch (pExpr.mType) {
        case GExprType::kInv:
            return "inv";

        case GExprType::kSymbol:
            if (pExpr.mSymbol.IsVar()) {
                return "sym:var:" + pExpr.mSymbol.mName;
            }
            if (pExpr.mSymbol.IsBuf()) {
                const TwistBufferKey aKey = ResolveBufferKey(pExpr.mSymbol);
                if (aKey.IsValid()) {
                    return "sym:buf:key:" + BufName(aKey);
                }
                return "sym:buf:" + std::to_string(static_cast<int>(pExpr.mSymbol.mSlot));
            }
            return "sym:invalid";

        case GExprType::kConst:
            return "const:" + std::to_string(pExpr.mConstVal);

        case GExprType::kRead:
            return "read(" + ExprKeyInner(GExpr::Symbol(pExpr.mSymbol)) + "," +
                   ((pExpr.mIndex != nullptr) ? ExprKeyInner(*pExpr.mIndex) : "null") +
                   ",wrap=" + std::to_string(static_cast<int>(pExpr.mReadWrapType)) +
                   ",base=" + ExprKeyInner(GExpr::Symbol(pExpr.mReadWrapIndexSymbol)) +
                   ",oracle=" + ExprKeyInner(GExpr::Symbol(pExpr.mReadWrapOracleSymbol)) + ")";
        case GExprType::kDiffuse64A:
            return "diffuse64_a(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";
        case GExprType::kDiffuse64B:
            return "diffuse64_b(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";
        case GExprType::kDiffuse64C:
            return "diffuse64_c(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";
        case GExprType::kDiffuse32A:
            return "diffuse32_a(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";
        case GExprType::kDiffuse32B:
            return "diffuse32_b(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";
        case GExprType::kDiffuse32C:
            return "diffuse32_c(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";
        case GExprType::kCast32:
            return "cast32(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kOr:
        case GExprType::kRotL8:
        case GExprType::kRotL32:
        case GExprType::kRotL64:
        case GExprType::kShiftL:
        case GExprType::kShiftR:
            return std::to_string(static_cast<int>(pExpr.mType)) + "(" +
                   ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + "," +
                   ((pExpr.mB != nullptr) ? ExprKeyInner(*pExpr.mB) : "null") + ")";
    }

    return "inv";
}

} // namespace

GExpr::GExpr() {
    Invalidate();
}

GExpr GExpr::Symbol(const GSymbol &pSymbol) {
    GExpr aExpr;
    aExpr.mType = GExprType::kSymbol;
    aExpr.mSymbol = pSymbol;
    return aExpr;
}

GExpr GExpr::Const(std::uint64_t pVal) {
    return Const64(pVal);
}

GExpr GExpr::Const8(int pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = static_cast<std::uint64_t>(static_cast<std::uint8_t>(pVal));
    return aExpr;
}

GExpr GExpr::Const32(int pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = static_cast<std::uint64_t>(static_cast<std::uint32_t>(pVal));
    return aExpr;
}

GExpr GExpr::Const64(std::uint64_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = pVal;
    return aExpr;
}

GExpr GExpr::Cast32(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kCast32;
    aExpr.mA = std::make_shared<GExpr>(pExpr);
    return aExpr;
}

GExpr GExpr::Diffuse64A(std::uint64_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = TwistMix64::DiffuseA(pVal);
    return aExpr;
}

GExpr GExpr::Diffuse64A(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kDiffuse64A;
    aExpr.mA = std::make_shared<GExpr>(pExpr);
    return aExpr;
}

GExpr GExpr::Diffuse64B(std::uint64_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = TwistMix64::DiffuseB(pVal);
    return aExpr;
}

GExpr GExpr::Diffuse64B(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kDiffuse64B;
    aExpr.mA = std::make_shared<GExpr>(pExpr);
    return aExpr;
}

GExpr GExpr::Diffuse64C(std::uint64_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = TwistMix64::DiffuseC(pVal);
    return aExpr;
}

GExpr GExpr::Diffuse64C(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kDiffuse64C;
    aExpr.mA = std::make_shared<GExpr>(pExpr);
    return aExpr;
}

GExpr GExpr::Diffuse32A(std::uint32_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = static_cast<std::uint64_t>(TwistMix32::DiffuseA(pVal));
    return aExpr;
}

GExpr GExpr::Diffuse32A(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kDiffuse32A;
    aExpr.mA = std::make_shared<GExpr>(pExpr);
    return aExpr;
}

GExpr GExpr::Diffuse32B(std::uint32_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = static_cast<std::uint64_t>(TwistMix32::DiffuseB(pVal));
    return aExpr;
}

GExpr GExpr::Diffuse32B(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kDiffuse32B;
    aExpr.mA = std::make_shared<GExpr>(pExpr);
    return aExpr;
}

GExpr GExpr::Diffuse32C(std::uint32_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = static_cast<std::uint64_t>(TwistMix32::DiffuseC(pVal));
    return aExpr;
}

GExpr GExpr::Diffuse32C(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kDiffuse32C;
    aExpr.mA = std::make_shared<GExpr>(pExpr);
    return aExpr;
}

GExpr GExpr::Read(const GSymbol &pSymbol,
                  const GExpr &pIndex) {
    GExpr aExpr;
    aExpr.mType = GExprType::kRead;
    aExpr.mSymbol = pSymbol;
    aExpr.mIndex = std::make_shared<GExpr>(pIndex);
    aExpr.mReadWrapType = GReadWrapType::kNone;
    aExpr.mReadWrapIndexSymbol.Invalidate();
    aExpr.mReadWrapOracleSymbol.Invalidate();
    return aExpr;
}

GExpr GExpr::Add(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kAdd, a, b);
}

GExpr GExpr::Add(const GSymbol &a, const GSymbol &b) {
    return Add(Symbol(a), Symbol(b));
}

GExpr GExpr::Add(const GSymbol &a, const GExpr &b) {
    return Add(Symbol(a), b);
}

GExpr GExpr::Add(const GExpr &a, const GSymbol &b) {
    return Add(a, Symbol(b));
}

GExpr GExpr::Add(const GSymbol &a, std::uint64_t b) {
    return Add(Symbol(a), Const64(b));
}

GExpr GExpr::Add(const GExpr &a, std::uint64_t b) {
    return Add(a, Const64(b));
}

GExpr GExpr::Sub(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kSub, a, b);
}

GExpr GExpr::Sub(const GSymbol &a, const GSymbol &b) {
    return Sub(Symbol(a), Symbol(b));
}

GExpr GExpr::Sub(const GSymbol &a, const GExpr &b) {
    return Sub(Symbol(a), b);
}

GExpr GExpr::Sub(const GExpr &a, const GSymbol &b) {
    return Sub(a, Symbol(b));
}

GExpr GExpr::Sub(const GSymbol &a, std::uint64_t b) {
    return Sub(Symbol(a), Const64(b));
}

GExpr GExpr::Sub(const GExpr &a, std::uint64_t b) {
    return Sub(a, Const64(b));
}

GExpr GExpr::Mul(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kMul, a, b);
}

GExpr GExpr::Mul(const GSymbol &a, const GSymbol &b) {
    return Mul(Symbol(a), Symbol(b));
}

GExpr GExpr::Mul(const GSymbol &a, const GExpr &b) {
    return Mul(Symbol(a), b);
}

GExpr GExpr::Mul(const GExpr &a, const GSymbol &b) {
    return Mul(a, Symbol(b));
}

GExpr GExpr::Mul(const GSymbol &a, std::uint64_t b) {
    return Mul(Symbol(a), Const64(b));
}

GExpr GExpr::Mul(const GExpr &a, std::uint64_t b) {
    return Mul(a, Const64(b));
}

GExpr GExpr::Xor(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kXor, a, b);
}

GExpr GExpr::Xor(const GSymbol &a, const GSymbol &b) {
    return Xor(Symbol(a), Symbol(b));
}

GExpr GExpr::Xor(const GSymbol &a, const GExpr &b) {
    return Xor(Symbol(a), b);
}

GExpr GExpr::Xor(const GExpr &a, const GSymbol &b) {
    return Xor(a, Symbol(b));
}

GExpr GExpr::Xor(const GSymbol &a, std::uint64_t b) {
    return Xor(Symbol(a), Const64(b));
}

GExpr GExpr::Xor(const GExpr &a, std::uint64_t b) {
    return Xor(a, Const64(b));
}

GExpr GExpr::And(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kAnd, a, b);
}

GExpr GExpr::And(const GSymbol &a, const GSymbol &b) {
    return And(Symbol(a), Symbol(b));
}

GExpr GExpr::And(const GSymbol &a, const GExpr &b) {
    return And(Symbol(a), b);
}

GExpr GExpr::And(const GExpr &a, const GSymbol &b) {
    return And(a, Symbol(b));
}

GExpr GExpr::And(const GSymbol &a, std::uint64_t b) {
    return And(Symbol(a), Const64(b));
}

GExpr GExpr::And(const GExpr &a, std::uint64_t b) {
    return And(a, Const64(b));
}

GExpr GExpr::Or(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kOr, a, b);
}

GExpr GExpr::Or(const GSymbol &a, const GSymbol &b) {
    return Or(Symbol(a), Symbol(b));
}

GExpr GExpr::Or(const GSymbol &a, const GExpr &b) {
    return Or(Symbol(a), b);
}

GExpr GExpr::Or(const GExpr &a, const GSymbol &b) {
    return Or(a, Symbol(b));
}

GExpr GExpr::Or(const GSymbol &a, std::uint64_t b) {
    return Or(Symbol(a), Const64(b));
}

GExpr GExpr::Or(const GExpr &a, std::uint64_t b) {
    return Or(a, Const64(b));
}

GExpr GExpr::RotL8(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kRotL8, a, b);
}

GExpr GExpr::RotL8(const GSymbol &a, const GSymbol &b) {
    return RotL8(Symbol(a), Symbol(b));
}

GExpr GExpr::RotL8(const GSymbol &a, const GExpr &b) {
    return RotL8(Symbol(a), b);
}

GExpr GExpr::RotL8(const GExpr &a, const GSymbol &b) {
    return RotL8(a, Symbol(b));
}

GExpr GExpr::RotL8(const GSymbol &a, std::uint64_t b) {
    return RotL8(Symbol(a), Const64(b));
}

GExpr GExpr::RotL8(const GExpr &a, std::uint64_t b) {
    return RotL8(a, Const64(b));
}

GExpr GExpr::RotL32(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kRotL32, a, b);
}

GExpr GExpr::RotL32(const GSymbol &a, const GSymbol &b) {
    return RotL32(Symbol(a), Symbol(b));
}

GExpr GExpr::RotL32(const GSymbol &a, const GExpr &b) {
    return RotL32(Symbol(a), b);
}

GExpr GExpr::RotL32(const GExpr &a, const GSymbol &b) {
    return RotL32(a, Symbol(b));
}

GExpr GExpr::RotL32(const GSymbol &a, std::uint64_t b) {
    return RotL32(Symbol(a), Const64(b));
}

GExpr GExpr::RotL32(const GExpr &a, std::uint64_t b) {
    return RotL32(a, Const64(b));
}

GExpr GExpr::RotL64(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kRotL64, a, b);
}

GExpr GExpr::RotL64(const GSymbol &a, const GSymbol &b) {
    return RotL64(Symbol(a), Symbol(b));
}

GExpr GExpr::RotL64(const GSymbol &a, const GExpr &b) {
    return RotL64(Symbol(a), b);
}

GExpr GExpr::RotL64(const GExpr &a, const GSymbol &b) {
    return RotL64(a, Symbol(b));
}

GExpr GExpr::RotL64(const GSymbol &a, std::uint64_t b) {
    return RotL64(Symbol(a), Const64(b));
}

GExpr GExpr::RotL64(const GExpr &a, std::uint64_t b) {
    return RotL64(a, Const64(b));
}

GExpr GExpr::ShiftL(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kShiftL, a, b);
}

GExpr GExpr::ShiftL(const GSymbol &a, const GSymbol &b) {
    return ShiftL(Symbol(a), Symbol(b));
}

GExpr GExpr::ShiftL(const GSymbol &a, const GExpr &b) {
    return ShiftL(Symbol(a), b);
}

GExpr GExpr::ShiftL(const GExpr &a, const GSymbol &b) {
    return ShiftL(a, Symbol(b));
}

GExpr GExpr::ShiftL(const GSymbol &a, std::uint64_t b) {
    return ShiftL(Symbol(a), Const64(b));
}

GExpr GExpr::ShiftL(const GExpr &a, std::uint64_t b) {
    return ShiftL(a, Const64(b));
}

GExpr GExpr::ShiftR(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kShiftR, a, b);
}

GExpr GExpr::ShiftR(const GSymbol &a, const GSymbol &b) {
    return ShiftR(Symbol(a), Symbol(b));
}

GExpr GExpr::ShiftR(const GSymbol &a, const GExpr &b) {
    return ShiftR(Symbol(a), b);
}

GExpr GExpr::ShiftR(const GExpr &a, const GSymbol &b) {
    return ShiftR(a, Symbol(b));
}

GExpr GExpr::ShiftR(const GSymbol &a, std::uint64_t b) {
    return ShiftR(Symbol(a), Const64(b));
}

GExpr GExpr::ShiftR(const GExpr &a, std::uint64_t b) {
    return ShiftR(a, Const64(b));
}

GExpr GExpr::ReadBlockWrap(const GSymbol &pSymbol,
                           const GSymbol &pIndex,
                           const GSymbol &pIndexOracle) {
    return BuildWrappedRead(GReadWrapType::kBlock, pSymbol, pIndex, pIndexOracle);
}

GExpr GExpr::ReadSBoxWrap(const GSymbol &pSymbol,
                          const GSymbol &pIndex,
                          const GSymbol &pIndexOracle) {
    return BuildWrappedRead(GReadWrapType::kSBox, pSymbol, pIndex, pIndexOracle);
}

GExpr GExpr::ReadSaltWrap(const GSymbol &pSymbol,
                          const GSymbol &pIndex,
                          const GSymbol &pIndexOracle) {
    return BuildWrappedRead(GReadWrapType::kSalt, pSymbol, pIndex, pIndexOracle);
}

GExpr GExpr::ReadKeyAWrap(const GSymbol &pSymbol,
                          const GSymbol &pIndex,
                          const GSymbol &pIndexOracle) {
    return BuildWrappedRead(GReadWrapType::kKeyA, pSymbol, pIndex, pIndexOracle);
}

GExpr GExpr::ReadKeyBWrap(const GSymbol &pSymbol,
                          const GSymbol &pIndex,
                          const GSymbol &pIndexOracle) {
    return BuildWrappedRead(GReadWrapType::kKeyB, pSymbol, pIndex, pIndexOracle);
}

void GExpr::Set(const GExpr &pOther) {
    mType = pOther.mType;
    mSymbol = pOther.mSymbol;
    mConstVal = pOther.mConstVal;
    mIndex = pOther.mIndex;
    mA = pOther.mA;
    mB = pOther.mB;
    mReadWrapType = pOther.mReadWrapType;
    mReadWrapIndexSymbol = pOther.mReadWrapIndexSymbol;
    mReadWrapOracleSymbol = pOther.mReadWrapOracleSymbol;
}

void GExpr::Invalidate() {
    mType = GExprType::kInv;
    mSymbol.Invalidate();
    mConstVal = 0;
    mIndex.reset();
    mA.reset();
    mB.reset();
    mReadWrapType = GReadWrapType::kNone;
    mReadWrapIndexSymbol.Invalidate();
    mReadWrapOracleSymbol.Invalidate();
}

bool GExpr::IsInvalid() const {
    switch (mType) {
        case GExprType::kSymbol:
            return mSymbol.IsInvalid();

        case GExprType::kConst:
            return false;

        case GExprType::kRead:
            return mSymbol.IsInvalid() || (mIndex == nullptr) || mIndex->IsInvalid() ||
                   ((mReadWrapType != GReadWrapType::kNone) &&
                    (mReadWrapIndexSymbol.IsInvalid() || mReadWrapOracleSymbol.IsInvalid()));

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kOr:
        case GExprType::kRotL8:
        case GExprType::kRotL32:
        case GExprType::kRotL64:
        case GExprType::kShiftL:
        case GExprType::kShiftR:
            return (mA == nullptr) || (mB == nullptr) ||
                   mA->IsInvalid() || mB->IsInvalid();
            
        case GExprType::kDiffuse64A:
        case GExprType::kDiffuse64B:
        case GExprType::kDiffuse64C:
        case GExprType::kDiffuse32A:
        case GExprType::kDiffuse32B:
        case GExprType::kDiffuse32C:
        case GExprType::kCast32:
            return (mA == nullptr) || mA->IsInvalid();

        default:
            return true;
    }
}

bool GExpr::IsSymbol() const {
    return mType == GExprType::kSymbol;
}

bool GExpr::IsConst() const {
    return mType == GExprType::kConst;
}

bool GExpr::IsRead() const {
    return mType == GExprType::kRead;
}

std::vector<GSymbol> GExpr::GetSymbols() const {
    std::vector<GSymbol> aSymbols;
    AppendSymbols(*this, &aSymbols);
    return aSymbols;
}

std::vector<GOperType> GExpr::GetOps() const {
    std::vector<GOperType> aOps;
    AppendOps(*this, &aOps);
    return aOps;
}

bool operator == (const GExpr &pLHS, const GExpr &pRHS) {
    if (pLHS.mType != pRHS.mType) {
        return false;
    }

    switch (pLHS.mType) {
        case GExprType::kInv:
            return true;

        case GExprType::kSymbol:
            return pLHS.mSymbol == pRHS.mSymbol;

        case GExprType::kConst:
            return pLHS.mConstVal == pRHS.mConstVal;

        case GExprType::kRead:
            return (pLHS.mSymbol == pRHS.mSymbol) &&
                   ExprPtrEqual(pLHS.mIndex, pRHS.mIndex) &&
                   (pLHS.mReadWrapType == pRHS.mReadWrapType) &&
                   (pLHS.mReadWrapIndexSymbol == pRHS.mReadWrapIndexSymbol) &&
                   (pLHS.mReadWrapOracleSymbol == pRHS.mReadWrapOracleSymbol);

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kOr:
        case GExprType::kRotL8:
        case GExprType::kRotL32:
        case GExprType::kRotL64:
        case GExprType::kShiftL:
        case GExprType::kShiftR:
            return ExprPtrEqual(pLHS.mA, pRHS.mA) &&
                   ExprPtrEqual(pLHS.mB, pRHS.mB);
        case GExprType::kDiffuse64A:
        case GExprType::kDiffuse64B:
        case GExprType::kDiffuse64C:
        case GExprType::kDiffuse32A:
        case GExprType::kDiffuse32B:
        case GExprType::kDiffuse32C:
        case GExprType::kCast32:
            return ExprPtrEqual(pLHS.mA, pRHS.mA);
    }

    return false;
}

bool operator != (const GExpr &pLHS, const GExpr &pRHS) {
    return !(pLHS == pRHS);
}

std::string GExprKey(const GExpr &pExpr) {
    return ExprKeyInner(pExpr);
}
