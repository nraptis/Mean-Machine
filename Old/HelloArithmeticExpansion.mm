//
//  HelloArithmeticExpansion.m
//  CornTesting
//
//  Created by Magneto on 4/22/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include <vector>
#include "SBoxTables.hpp"
#include "TwistWorkSpace.hpp"
#include "TwistSeedBuilder.hpp"
#include "TwistSeeder.hpp"
#include "GStatementRecipe.hpp"
#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "Random.hpp"

@interface HelloArithmeticExpansion : XCTestCase

@end

@implementation HelloArithmeticExpansion

struct NumberRange {
public:
    NumberRange(int pLow, int pHigh, bool pOdd) {
        mLow = pLow;
        mHigh = pHigh;
        mOdd = pOdd;
    }
    int mLow;
    int mHigh;
    bool mOdd;
    bool Match(int pNumber) {
        if (mOdd) {
            if ((pNumber & 1) == 0) {
                return false;
            }
        }
        return ((pNumber >= mLow) && (pNumber <= mHigh));
    }
};

NumberRange cAddSubXorRange(1, 255, false);
NumberRange cMulRange(3, 255, true);
NumberRange cRotRange(1, 7, false);

bool IsValidConstantAddSubXor(const GExpr pExpression) {
    if (pExpression.IsConst()) {
        int aConstant = (int)pExpression.mConstVal;
        return cAddSubXorRange.Match(aConstant);
    }
    return false;
}

bool IsValidConstantMul(const GExpr pExpression) {
    if (pExpression.IsConst()) {
        int aConstant = (int)pExpression.mConstVal;
        return cMulRange.Match(aConstant);
    }
    return false;
}

bool IsValidConstantRot(const GExpr pExpression) {
    if (pExpression.IsConst()) {
        int aConstant = (int)pExpression.mConstVal;
        return cRotRange.Match(aConstant);
    }
    return false;
}

bool IsValidSymbolExactly(const GExpr pExpression, const GSymbol pSymbol) {
    if (pExpression.IsSymbol()) {
        if (pExpression.mSymbol == pSymbol) {
            return true;
        }
    }
    return false;
}

bool IsValidRotateOfSymbol(const GExpr pExpression, const GSymbol pSymbol) {
    GOperType aOper = OperTypeForExpr(pExpression);
    if (aOper != GOperType::kRotL8) { return false; }
    if (pExpression.mA == NULL) { return false; }
    if (pExpression.mB == NULL) { return false; }
    if (pExpression.mA->IsSymbol() == false) { return false; }
    if (pExpression.mB->IsConst() == false) { return false; }
    if (pExpression.mA->mSymbol != pSymbol) { return false; }
    if (cRotRange.Match((int)pExpression.mB->mConstVal) == false) { return false; }
    return true;
}

bool IsValidMulOfSymbol(const GExpr pExpression, const GSymbol pSymbol) {
    GOperType aOper = OperTypeForExpr(pExpression);
    if (aOper != GOperType::kMul) { return false; }
    if (pExpression.mA == NULL) { return false; }
    if (pExpression.mB == NULL) { return false; }
    if (pExpression.mA->IsSymbol() == false) { return false; }
    if (pExpression.mB->IsConst() == false) { return false; }
    if (pExpression.mA->mSymbol != pSymbol) { return false; }
    if (cMulRange.Match((int)pExpression.mB->mConstVal) == false) { return false; }
    return true;
}

bool IsValidAddOfSymbol(const GExpr pExpression, const GSymbol pSymbol) {
    GOperType aOper = OperTypeForExpr(pExpression);
    if (aOper != GOperType::kAdd) { return false; }
    if (pExpression.mA == NULL) { return false; }
    if (pExpression.mB == NULL) { return false; }
    if (pExpression.mA->IsSymbol() == false) { return false; }
    if (pExpression.mB->IsConst() == false) { return false; }
    if (pExpression.mA->mSymbol != pSymbol) { return false; }
    if (cAddSubXorRange.Match((int)pExpression.mB->mConstVal) == false) { return false; }
    return true;
}

bool IsValidSubOfSymbol(const GExpr pExpression, const GSymbol pSymbol) {
    GOperType aOper = OperTypeForExpr(pExpression);
    if (aOper != GOperType::kSub) { return false; }
    if (pExpression.mA == NULL) { return false; }
    if (pExpression.mB == NULL) { return false; }
    if (pExpression.mA->IsSymbol() == false) { return false; }
    if (pExpression.mB->IsConst() == false) { return false; }
    if (pExpression.mA->mSymbol != pSymbol) { return false; }
    if (cAddSubXorRange.Match((int)pExpression.mB->mConstVal) == false) { return false; }
    return true;
}

bool IsValidXorOfSymbol(const GExpr pExpression, const GSymbol pSymbol) {
    GOperType aOper = OperTypeForExpr(pExpression);
    if (aOper != GOperType::kXor) { return false; }
    if (pExpression.mA == NULL) { return false; }
    if (pExpression.mB == NULL) { return false; }
    if (pExpression.mA->IsSymbol() == false) { return false; }
    if (pExpression.mB->IsConst() == false) { return false; }
    if (pExpression.mA->mSymbol != pSymbol) { return false; }
    if (cAddSubXorRange.Match((int)pExpression.mB->mConstVal) == false) { return false; }
    return true;
}

- (void)testPatternsExactMatchWithMultiply {
    
    const GSymbol aSource = BufSymbol(TwistWorkSpaceSlot::kSource);
    
    for (int k=0;k<1000;k++) {
        
        const GExpr aExpression = GTermExpander::Expand(aSource, true);
        
        GOperType aOper = OperTypeForExpr(aExpression);
        
        if (aExpression.mA == NULL) {
            XCTFail("{arith} aExpression.mA was null");
            return;
        }
        
        if (aExpression.mB == NULL) {
            XCTFail("{arith} aExpression.mA was null");
            return;
        }
        
        if (aOper == GOperType::kAdd) {
            
            // a + s1
            // (a * s1) + s2           // odd s1
            // rotl8(a, s2) + s1
            
            bool aValidLHS1 = IsValidRotateOfSymbol(*aExpression.mA, aSource);
            bool aValidLHS2 = IsValidSymbolExactly(*aExpression.mA, aSource);
            bool aValidLHS3 = IsValidMulOfSymbol(*aExpression.mA, aSource);
            if ((aValidLHS1 == false) && (aValidLHS2 == false) && (aValidLHS3 == false)) {
                XCTFail("{arith} lhs of add can be [symbol] or [rotl8 symbol] or [mul symbol]");
                return;
            }
            bool aValidRHS = IsValidConstantAddSubXor(*aExpression.mB);
            if (aValidRHS == false) {
                XCTFail("{arith} add should have gotten a constant in [1...255]");
                return;
            }
        } else if (aOper == GOperType::kSub) {
            
            // a - s1
            // (a * s1) - s2           // odd s1
            // rotl8(a, s2) - s1
            
            bool aValidLHS1 = IsValidRotateOfSymbol(*aExpression.mA, aSource);
            bool aValidLHS2 = IsValidSymbolExactly(*aExpression.mA, aSource);
            bool aValidLHS3 = IsValidMulOfSymbol(*aExpression.mA, aSource);
            if ((aValidLHS1 == false) && (aValidLHS2 == false) && (aValidLHS3 == false)) {
                XCTFail("{arith} lhs of sub can be [symbol] or [rotl8 symbol] or [mul symbol]");
                return;
            }
            bool aValidRHS = IsValidConstantAddSubXor(*aExpression.mB);
            if (aValidRHS == false) {
                XCTFail("{arith} sub should have gotten a constant in [1...255]");
                return;
            }
        } else if (aOper == GOperType::kXor) {
            
            // a ^ s1
            // (a * s1) ^ s2           // odd s1
            // rotl8(a, s2) ^ s1
            
            bool aValidLHS1 = IsValidRotateOfSymbol(*aExpression.mA, aSource);
            bool aValidLHS2 = IsValidSymbolExactly(*aExpression.mA, aSource);
            bool aValidLHS3 = IsValidMulOfSymbol(*aExpression.mA, aSource);
            if ((aValidLHS1 == false) && (aValidLHS2 == false) && (aValidLHS3 == false)) {
                XCTFail("{arith} lhs of xor can be [symbol] or [rotl8 symbol] or [mul symbol]");
                return;
            }
            bool aValidRHS = IsValidConstantAddSubXor(*aExpression.mB);
            if (aValidRHS == false) {
                XCTFail("{arith} xor should have gotten a constant in [1...255]");
                return;
            }
        } else if (aOper == GOperType::kMul) {
            
            // a * s1                  // odd
            // rotl8(a, s2) * s1
            
            bool aValidLHS1 = IsValidRotateOfSymbol(*aExpression.mA, aSource);
            bool aValidLHS2 = IsValidSymbolExactly(*aExpression.mA, aSource);
            
            if ((aValidLHS1 == false) && (aValidLHS2 == false)) {
                XCTFail("{arith} lhs of mul can be [symbol] or [rotl8 symbol]");
                return;
            }
            bool aValidRHS = IsValidConstantMul(*aExpression.mB);
            if (aValidRHS == false) {
                XCTFail("{arith} mul should have gotten a constant in [3, 5, ..., 253, 255]");
                return;
            }
        } else if (aOper == GOperType::kRotL8) {
            
            // rotl8(a, s1)
            
            // rotl8(a + s1, s2)
            // rotl8(a - s1, s2)
            // rotl8(a ^ s1, s2)
            // rotl8(a * s1, s2)       // odd s1
            
            bool aValidLHS1 = IsValidSymbolExactly(*aExpression.mA, aSource);
            
            bool aValidLHS2 = IsValidAddOfSymbol(*aExpression.mA, aSource);
            bool aValidLHS3 = IsValidSubOfSymbol(*aExpression.mA, aSource);
            bool aValidLHS4 = IsValidMulOfSymbol(*aExpression.mA, aSource);
            bool aValidLHS5 = IsValidXorOfSymbol(*aExpression.mA, aSource);
            
            if ((aValidLHS1 == false) && (aValidLHS2 == false) && (aValidLHS3 == false) && (aValidLHS4 == false) && (aValidLHS5 == false)) {
                XCTFail("{arith} lhs of rotate can be [symbol] or [add symbol] or [sub symbol] or [mul symbol] or [xor symbol]");
                return;
            }
            
            bool aValidRHS = IsValidConstantRot(*aExpression.mB);
            if (aValidRHS == false) {
                XCTFail("{arith} rotate should have gotten a constant in [1...7]");
                return;
            }
        } else {
            XCTFail("{arith} the expanded term was not correct. none of the expected operators.");
            return;
        }
    }
}



@end
