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
        case GExprType::kMix64_8: return GOperType::kInv;
        case GExprType::kDiffuseA64: return GOperType::kInv;
        case GExprType::kDiffuseB64: return GOperType::kInv;
        case GExprType::kDiffuseC64: return GOperType::kInv;
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

bool Mix64Type8NeedsAmount(const Mix64Type_8 pType) {
    switch (pType) {
        case Mix64Type_8::kGatePrism_8_8:
            return false;
        case Mix64Type_8::kGateRoll_8_8:
        case Mix64Type_8::kGateTurn_8_8:
            return true;
        default:
            return false;
    }
}

GExpr BuildWrappedRead(const GReadWrapType pWrapType,
                       const GSymbol &pSymbol,
                       const GSymbol &pIndex,
                       const GSymbol &pIndexOracle,
                       const int pOffset) {
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
    aExpr.mReadWrapOffset = pOffset;
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
        case GExprType::kMix64_8:
            if (pExpr.mA != nullptr) {
                AppendSymbols(*pExpr.mA, pSymbols);
            }
            pSymbols->push_back(pExpr.mMix64SBoxA);
            pSymbols->push_back(pExpr.mMix64SBoxB);
            pSymbols->push_back(pExpr.mMix64SBoxC);
            pSymbols->push_back(pExpr.mMix64SBoxD);
            pSymbols->push_back(pExpr.mMix64SBoxE);
            pSymbols->push_back(pExpr.mMix64SBoxF);
            pSymbols->push_back(pExpr.mMix64SBoxG);
            pSymbols->push_back(pExpr.mMix64SBoxH);
            return;

        case GExprType::kDiffuseA64:
        case GExprType::kDiffuseB64:
        case GExprType::kDiffuseC64:
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
        case GExprType::kMix64_8:
        case GExprType::kDiffuseA64:
        case GExprType::kDiffuseB64:
        case GExprType::kDiffuseC64:
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
                   ",oracle=" + ExprKeyInner(GExpr::Symbol(pExpr.mReadWrapOracleSymbol)) +
                   ",offset=" + std::to_string(pExpr.mReadWrapOffset) + ")";
        case GExprType::kMix64_8:
            return "mix64_8(type=" + std::to_string(static_cast<int>(pExpr.mMix64Type8)) +
                   ",amount=" + std::to_string(static_cast<unsigned long long>(pExpr.mMix64Amount)) +
                   ",has_amount=" + std::to_string(pExpr.mMix64UseAmount ? 1 : 0) +
                   ",sbox_a=" + ExprKeyInner(GExpr::Symbol(pExpr.mMix64SBoxA)) +
                   ",sbox_b=" + ExprKeyInner(GExpr::Symbol(pExpr.mMix64SBoxB)) +
                   ",sbox_c=" + ExprKeyInner(GExpr::Symbol(pExpr.mMix64SBoxC)) +
                   ",sbox_d=" + ExprKeyInner(GExpr::Symbol(pExpr.mMix64SBoxD)) +
                   ",sbox_e=" + ExprKeyInner(GExpr::Symbol(pExpr.mMix64SBoxE)) +
                   ",sbox_f=" + ExprKeyInner(GExpr::Symbol(pExpr.mMix64SBoxF)) +
                   ",sbox_g=" + ExprKeyInner(GExpr::Symbol(pExpr.mMix64SBoxG)) +
                   ",sbox_h=" + ExprKeyInner(GExpr::Symbol(pExpr.mMix64SBoxH)) +
                   ",value=" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";

        case GExprType::kDiffuseA64:
            return "diffuse64(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";
        case GExprType::kDiffuseB64:
            return "diffuse64_b(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";
        case GExprType::kDiffuseC64:
            return "diffuse64_c(" + ((pExpr.mA != nullptr) ? ExprKeyInner(*pExpr.mA) : "null") + ")";

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

GExpr GExpr::DiffuseA(std::uint64_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = TwistMix64::DiffuseA(pVal);
    return aExpr;
}

GExpr GExpr::DiffuseA(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kDiffuseA64;
    aExpr.mA = std::make_shared<GExpr>(pExpr);
    return aExpr;
}

GExpr GExpr::DiffuseB(std::uint64_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = TwistMix64::DiffuseB(pVal);
    return aExpr;
}

GExpr GExpr::DiffuseB(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kDiffuseB64;
    aExpr.mA = std::make_shared<GExpr>(pExpr);
    return aExpr;
}

GExpr GExpr::DiffuseC(std::uint64_t pVal) {
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = TwistMix64::DiffuseC(pVal);
    return aExpr;
}

GExpr GExpr::DiffuseC(const GExpr &pExpr) {
    GExpr aExpr;
    aExpr.mType = GExprType::kDiffuseC64;
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
    aExpr.mReadWrapOffset = 0;
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

GExpr GExpr::Mix64_8(const GExpr &pValue,
                     Mix64Type_8 pMixType,
                     const GSymbol &pSBoxA,
                     const GSymbol &pSBoxB,
                     const GSymbol &pSBoxC,
                     const GSymbol &pSBoxD,
                     const GSymbol &pSBoxE,
                     const GSymbol &pSBoxF,
                     const GSymbol &pSBoxG,
                     const GSymbol &pSBoxH) {
    GExpr aExpr;
    aExpr.mType = GExprType::kMix64_8;
    aExpr.mA = std::make_shared<GExpr>(pValue);
    aExpr.mMix64Type8 = pMixType;
    aExpr.mMix64UseAmount = false;
    aExpr.mMix64Amount = 0U;
    aExpr.mMix64SBoxA = pSBoxA;
    aExpr.mMix64SBoxB = pSBoxB;
    aExpr.mMix64SBoxC = pSBoxC;
    aExpr.mMix64SBoxD = pSBoxD;
    aExpr.mMix64SBoxE = pSBoxE;
    aExpr.mMix64SBoxF = pSBoxF;
    aExpr.mMix64SBoxG = pSBoxG;
    aExpr.mMix64SBoxH = pSBoxH;
    return aExpr;
}

GExpr GExpr::Mix64_8(const GExpr &pValue,
                     Mix64Type_8 pMixType,
                     std::uint64_t pAmount,
                     const GSymbol &pSBoxA,
                     const GSymbol &pSBoxB,
                     const GSymbol &pSBoxC,
                     const GSymbol &pSBoxD,
                     const GSymbol &pSBoxE,
                     const GSymbol &pSBoxF,
                     const GSymbol &pSBoxG,
                     const GSymbol &pSBoxH) {
    GExpr aExpr = Mix64_8(pValue, pMixType, pSBoxA, pSBoxB, pSBoxC, pSBoxD, pSBoxE, pSBoxF, pSBoxG, pSBoxH);
    aExpr.mMix64UseAmount = true;
    aExpr.mMix64Amount = pAmount;
    return aExpr;
}

GExpr GExpr::ReadBlockWrap(const GSymbol &pSymbol,
                           const GSymbol &pIndex,
                           const GSymbol &pIndexOracle,
                           int pOffset) {
    return BuildWrappedRead(GReadWrapType::kBlock, pSymbol, pIndex, pIndexOracle, pOffset);
}

GExpr GExpr::ReadSBoxWrap(const GSymbol &pSymbol,
                          const GSymbol &pIndex,
                          const GSymbol &pIndexOracle,
                          int pOffset) {
    return BuildWrappedRead(GReadWrapType::kSBox, pSymbol, pIndex, pIndexOracle, pOffset);
}

GExpr GExpr::ReadSaltWrap(const GSymbol &pSymbol,
                          const GSymbol &pIndex,
                          const GSymbol &pIndexOracle,
                          int pOffset) {
    return BuildWrappedRead(GReadWrapType::kSalt, pSymbol, pIndex, pIndexOracle, pOffset);
}

GExpr GExpr::ReadMaskAWrap(const GSymbol &pSymbol,
                           const GSymbol &pIndex,
                           const GSymbol &pIndexOracle,
                           int pOffset) {
    return BuildWrappedRead(GReadWrapType::kMaskA, pSymbol, pIndex, pIndexOracle, pOffset);
}

GExpr GExpr::ReadMaskBWrap(const GSymbol &pSymbol,
                           const GSymbol &pIndex,
                           const GSymbol &pIndexOracle,
                           int pOffset) {
    return BuildWrappedRead(GReadWrapType::kMaskB, pSymbol, pIndex, pIndexOracle, pOffset);
}

GExpr GExpr::ReadKeyAWrap(const GSymbol &pSymbol,
                          const GSymbol &pIndex,
                          const GSymbol &pIndexOracle,
                          int pOffset) {
    return BuildWrappedRead(GReadWrapType::kKeyA, pSymbol, pIndex, pIndexOracle, pOffset);
}

GExpr GExpr::ReadKeyBWrap(const GSymbol &pSymbol,
                          const GSymbol &pIndex,
                          const GSymbol &pIndexOracle,
                          int pOffset) {
    return BuildWrappedRead(GReadWrapType::kKeyB, pSymbol, pIndex, pIndexOracle, pOffset);
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
    mReadWrapOffset = pOther.mReadWrapOffset;
    mMix64Type8 = pOther.mMix64Type8;
    mMix64UseAmount = pOther.mMix64UseAmount;
    mMix64Amount = pOther.mMix64Amount;
    mMix64SBoxA = pOther.mMix64SBoxA;
    mMix64SBoxB = pOther.mMix64SBoxB;
    mMix64SBoxC = pOther.mMix64SBoxC;
    mMix64SBoxD = pOther.mMix64SBoxD;
    mMix64SBoxE = pOther.mMix64SBoxE;
    mMix64SBoxF = pOther.mMix64SBoxF;
    mMix64SBoxG = pOther.mMix64SBoxG;
    mMix64SBoxH = pOther.mMix64SBoxH;
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
    mReadWrapOffset = 0;
    mMix64Type8 = Mix64Type_8::kInv;
    mMix64UseAmount = false;
    mMix64Amount = 0U;
    mMix64SBoxA.Invalidate();
    mMix64SBoxB.Invalidate();
    mMix64SBoxC.Invalidate();
    mMix64SBoxD.Invalidate();
    mMix64SBoxE.Invalidate();
    mMix64SBoxF.Invalidate();
    mMix64SBoxG.Invalidate();
    mMix64SBoxH.Invalidate();
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
            
        case GExprType::kMix64_8:
            return (mA == nullptr) || mA->IsInvalid() ||
                   (!mMix64SBoxA.IsBuf()) ||
                   (!mMix64SBoxB.IsBuf()) ||
                   (!mMix64SBoxC.IsBuf()) ||
                   (!mMix64SBoxD.IsBuf()) ||
                   (!mMix64SBoxE.IsBuf()) ||
                   (!mMix64SBoxF.IsBuf()) ||
                   (!mMix64SBoxG.IsBuf()) ||
                   (!mMix64SBoxH.IsBuf()) ||
                   (mMix64Type8 == Mix64Type_8::kInv) ||
                   (Mix64Type8NeedsAmount(mMix64Type8) && !mMix64UseAmount);

        case GExprType::kDiffuseA64:
        case GExprType::kDiffuseB64:
        case GExprType::kDiffuseC64:
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
                   (pLHS.mReadWrapOffset == pRHS.mReadWrapOffset) &&
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
        case GExprType::kMix64_8:
            return ExprPtrEqual(pLHS.mA, pRHS.mA) &&
                   (pLHS.mMix64Type8 == pRHS.mMix64Type8) &&
                   (pLHS.mMix64UseAmount == pRHS.mMix64UseAmount) &&
                   (pLHS.mMix64Amount == pRHS.mMix64Amount) &&
                   (pLHS.mMix64SBoxA == pRHS.mMix64SBoxA) &&
                   (pLHS.mMix64SBoxB == pRHS.mMix64SBoxB) &&
                   (pLHS.mMix64SBoxC == pRHS.mMix64SBoxC) &&
                   (pLHS.mMix64SBoxD == pRHS.mMix64SBoxD) &&
                   (pLHS.mMix64SBoxE == pRHS.mMix64SBoxE) &&
                   (pLHS.mMix64SBoxF == pRHS.mMix64SBoxF) &&
                   (pLHS.mMix64SBoxG == pRHS.mMix64SBoxG) &&
                   (pLHS.mMix64SBoxH == pRHS.mMix64SBoxH);
        case GExprType::kDiffuseA64:
        case GExprType::kDiffuseB64:
        case GExprType::kDiffuseC64:
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
