//
//  GExpr.cpp
//  Moose Rib
//
//  Created by Whale Farts on 4/20/26.
//

#include "GExpr.hpp"

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

GOperType OperTypeForExprType(const GExprType pType) {
    switch (pType) {
        case GExprType::kRead: return GOperType::kRead;
        case GExprType::kAdd: return GOperType::kAdd;
        case GExprType::kSub: return GOperType::kSub;
        case GExprType::kMul: return GOperType::kMul;
        case GExprType::kXor: return GOperType::kXor;
        case GExprType::kAnd: return GOperType::kAnd;
        case GExprType::kRotateLeft8: return GOperType::kRotateLeft8;
        case GExprType::kRotateRight8: return GOperType::kRotateRight8;
        default: return GOperType::kInv;
    }
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
            return;

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kRotateLeft8:
        case GExprType::kRotateRight8:
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
        case GExprType::kRotateLeft8:
        case GExprType::kRotateRight8:
            if (pExpr.mA != nullptr) {
                AppendOps(*pExpr.mA, pOps);
            }
            if (pExpr.mB != nullptr) {
                AppendOps(*pExpr.mB, pOps);
            }
            pOps->push_back(OperTypeForExprType(pExpr.mType));
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
                return "sym:buf:" + std::to_string(static_cast<int>(pExpr.mSymbol.mSlot));
            }
            return "sym:invalid";

        case GExprType::kConst:
            return "const:" + std::to_string(pExpr.mConstVal);

        case GExprType::kRead:
            return "read(" + ExprKeyInner(GExpr::Symbol(pExpr.mSymbol)) + "," +
                   ((pExpr.mIndex != nullptr) ? ExprKeyInner(*pExpr.mIndex) : "null") + ")";

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kRotateLeft8:
        case GExprType::kRotateRight8:
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
    GExpr aExpr;
    aExpr.mType = GExprType::kConst;
    aExpr.mConstVal = pVal;
    return aExpr;
}

GExpr GExpr::Read(const GSymbol &pSymbol,
                  const GExpr &pIndex) {
    GExpr aExpr;
    aExpr.mType = GExprType::kRead;
    aExpr.mSymbol = pSymbol;
    aExpr.mIndex = std::make_shared<GExpr>(pIndex);
    return aExpr;
}

GExpr GExpr::Add(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kAdd, a, b);
}

GExpr GExpr::Sub(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kSub, a, b);
}

GExpr GExpr::Mul(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kMul, a, b);
}

GExpr GExpr::Xor(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kXor, a, b);
}

GExpr GExpr::And(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kAnd, a, b);
}

GExpr GExpr::RotateLeft8(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kRotateLeft8, a, b);
}

GExpr GExpr::RotateRight8(const GExpr &a, const GExpr &b) {
    return BinaryExpr(GExprType::kRotateRight8, a, b);
}

void GExpr::Set(const GExpr &pOther) {
    mType = pOther.mType;
    mSymbol = pOther.mSymbol;
    mConstVal = pOther.mConstVal;
    mIndex = pOther.mIndex;
    mA = pOther.mA;
    mB = pOther.mB;
}

void GExpr::Invalidate() {
    mType = GExprType::kInv;
    mSymbol.Invalidate();
    mConstVal = 0;
    mIndex.reset();
    mA.reset();
    mB.reset();
}

bool GExpr::IsInvalid() const {
    switch (mType) {
        case GExprType::kSymbol:
            return mSymbol.IsInvalid();

        case GExprType::kConst:
            return false;

        case GExprType::kRead:
            return mSymbol.IsInvalid() || (mIndex == nullptr) || mIndex->IsInvalid();

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kRotateLeft8:
        case GExprType::kRotateRight8:
            return (mA == nullptr) || (mB == nullptr) ||
                   mA->IsInvalid() || mB->IsInvalid();

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
                   ExprPtrEqual(pLHS.mIndex, pRHS.mIndex);

        case GExprType::kAdd:
        case GExprType::kSub:
        case GExprType::kMul:
        case GExprType::kXor:
        case GExprType::kAnd:
        case GExprType::kRotateLeft8:
        case GExprType::kRotateRight8:
            return ExprPtrEqual(pLHS.mA, pRHS.mA) &&
                   ExprPtrEqual(pLHS.mB, pRHS.mB);
    }

    return false;
}

bool operator != (const GExpr &pLHS, const GExpr &pRHS) {
    return !(pLHS == pRHS);
}

std::string GExprKey(const GExpr &pExpr) {
    return ExprKeyInner(pExpr);
}
