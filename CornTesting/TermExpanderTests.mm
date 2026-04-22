//
//  TermExpanderTests.mm
//  CornTesting
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include <algorithm>
#include <string>
#include <unordered_set>
#include "GTermExpander.hpp"

namespace {

bool ExprIsSymbol(const GExpr &pExpr, const GSymbol pSymbol) {
    return (pExpr.mType == GExprType::kSymbol) && (pExpr.mSymbol == pSymbol);
}

bool ExprIsConstInRange(const GExpr &pExpr,
                        const std::uint64_t pMinimum,
                        const std::uint64_t pMaximum) {
    return (pExpr.mType == GExprType::kConst) &&
           (pExpr.mConstVal >= pMinimum) &&
           (pExpr.mConstVal <= pMaximum);
}

bool ExprIsArithmeticConst(const GExpr &pExpr) {
    return ExprIsConstInRange(pExpr, 1ULL, 255ULL);
}

bool ExprIsOddMultiplyConst(const GExpr &pExpr) {
    if ((pExpr.mType != GExprType::kConst) || ((pExpr.mConstVal & 1ULL) == 0ULL)) {
        return false;
    }
    return ExprIsConstInRange(pExpr, 3ULL, 255ULL);
}

bool ExprIsRotateConst(const GExpr &pExpr) {
    return ExprIsConstInRange(pExpr, 1ULL, 7ULL);
}

bool ExprIsBinary(const GExpr &pExpr, const GExprType pType) {
    return (pExpr.mType == pType) && (pExpr.mA != nullptr) && (pExpr.mB != nullptr);
}

bool ExprIsRotateOfSymbol(const GExpr &pExpr,
                          const GSymbol pSymbol) {
    return ExprIsBinary(pExpr, GExprType::kRotateLeft8) &&
           ExprIsSymbol(*pExpr.mA, pSymbol) &&
           ExprIsRotateConst(*pExpr.mB);
}

bool ExprIsInnerTerm(const GExpr &pExpr,
                     const GExprType pType,
                     const GSymbol pSymbol) {
    if (!ExprIsBinary(pExpr, pType) || !ExprIsSymbol(*pExpr.mA, pSymbol)) {
        return false;
    }

    if (pType == GExprType::kMul) {
        return ExprIsOddMultiplyConst(*pExpr.mB);
    }

    return ExprIsArithmeticConst(*pExpr.mB);
}

bool ExprUsesOnlySymbol(const GExpr &pExpr, const GSymbol pSymbol) {
    const std::vector<GSymbol> aSymbols = pExpr.GetSymbols();
    return std::all_of(aSymbols.begin(),
                       aSymbols.end(),
                       [pSymbol](const GSymbol &pExprSymbol) {
                           return pExprSymbol == pSymbol;
                       });
}

std::string ClassifyPattern(const GExpr &pExpr,
                            const GSymbol pSymbol) {
    if (ExprIsBinary(pExpr, GExprType::kAdd) &&
        ExprIsSymbol(*pExpr.mA, pSymbol) &&
        ExprIsArithmeticConst(*pExpr.mB)) {
        return "add";
    }
    if (ExprIsBinary(pExpr, GExprType::kSub) &&
        ExprIsSymbol(*pExpr.mA, pSymbol) &&
        ExprIsArithmeticConst(*pExpr.mB)) {
        return "sub";
    }
    if (ExprIsBinary(pExpr, GExprType::kXor) &&
        ExprIsSymbol(*pExpr.mA, pSymbol) &&
        ExprIsArithmeticConst(*pExpr.mB)) {
        return "xor";
    }
    if (ExprIsBinary(pExpr, GExprType::kMul) &&
        ExprIsSymbol(*pExpr.mA, pSymbol) &&
        ExprIsOddMultiplyConst(*pExpr.mB)) {
        return "mul";
    }
    if (ExprIsRotateOfSymbol(pExpr, pSymbol)) {
        return "rotate";
    }

    if (ExprIsBinary(pExpr, GExprType::kAdd) &&
        ExprIsInnerTerm(*pExpr.mA, GExprType::kMul, pSymbol) &&
        ExprIsArithmeticConst(*pExpr.mB)) {
        return "mul_add";
    }
    if (ExprIsBinary(pExpr, GExprType::kSub) &&
        ExprIsInnerTerm(*pExpr.mA, GExprType::kMul, pSymbol) &&
        ExprIsArithmeticConst(*pExpr.mB)) {
        return "mul_sub";
    }
    if (ExprIsBinary(pExpr, GExprType::kXor) &&
        ExprIsInnerTerm(*pExpr.mA, GExprType::kMul, pSymbol) &&
        ExprIsArithmeticConst(*pExpr.mB)) {
        return "mul_xor";
    }

    if (ExprIsBinary(pExpr, GExprType::kRotateLeft8) && ExprIsRotateConst(*pExpr.mB)) {
        if (ExprIsInnerTerm(*pExpr.mA, GExprType::kAdd, pSymbol)) {
            return "rot_add";
        }
        if (ExprIsInnerTerm(*pExpr.mA, GExprType::kSub, pSymbol)) {
            return "rot_sub";
        }
        if (ExprIsInnerTerm(*pExpr.mA, GExprType::kXor, pSymbol)) {
            return "rot_xor";
        }
        if (ExprIsInnerTerm(*pExpr.mA, GExprType::kMul, pSymbol)) {
            return "rot_mul";
        }
    }

    if (ExprIsBinary(pExpr, GExprType::kAdd) &&
        ExprIsRotateOfSymbol(*pExpr.mA, pSymbol) &&
        ExprIsArithmeticConst(*pExpr.mB)) {
        return "post_rot_add";
    }
    if (ExprIsBinary(pExpr, GExprType::kSub) &&
        ExprIsRotateOfSymbol(*pExpr.mA, pSymbol) &&
        ExprIsArithmeticConst(*pExpr.mB)) {
        return "post_rot_sub";
    }
    if (ExprIsBinary(pExpr, GExprType::kXor) &&
        ExprIsRotateOfSymbol(*pExpr.mA, pSymbol) &&
        ExprIsArithmeticConst(*pExpr.mB)) {
        return "post_rot_xor";
    }
    if (ExprIsBinary(pExpr, GExprType::kMul) &&
        ExprIsRotateOfSymbol(*pExpr.mA, pSymbol) &&
        ExprIsOddMultiplyConst(*pExpr.mB)) {
        return "post_rot_mul";
    }

    return "";
}

void AssertCatalogCoverage(const bool pAllowMultiply,
                           const std::size_t pExpectedCount) {
    const GSymbol a = GSymbol::Var("a");
    std::unordered_set<std::string> aSeen;

    for (int aIndex = 0; aIndex < 20000; ++aIndex) {
        const GExpr aExpr = GTermExpander::Expand(a, pAllowMultiply);

        XCTAssertFalse(aExpr.IsInvalid());
        XCTAssertTrue(ExprUsesOnlySymbol(aExpr, a));

        const std::string aPattern = ClassifyPattern(aExpr, a);
        XCTAssertFalse(aPattern.empty());
        if (!pAllowMultiply) {
            XCTAssertEqual(aPattern.find("mul"), std::string::npos);
        }

        aSeen.insert(aPattern);
        if (aSeen.size() == pExpectedCount) {
            return;
        }
    }

    XCTFail("Did not observe every expected term-expander pattern.");
}

} // namespace

@interface TermExpanderTests : XCTestCase

@end

@implementation TermExpanderTests

- (void)testTermExpanderCatalog {
    AssertCatalogCoverage(true, 16U);
}

- (void)testTermExpanderCatalogWithoutMultiply {
    AssertCatalogCoverage(false, 10U);
}

@end
