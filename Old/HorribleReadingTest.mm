//
//  HorribleReadingTest.m
//  CornTesting
//
//  Created by Dragon on 5/2/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include <algorithm>
#include <vector>

#include "TwistWorkSpace.hpp"
#include "GSymbol.hpp"
#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "GLoopFragmentComposer.hpp"
#include "Varz.hpp"
#include "StatementChecker.hpp"
#include "Random.hpp"
#include "GLoopMixBrew.hpp"
#include "GQuick.hpp"

@interface HorribleReadingTest : XCTestCase

@end

@implementation HorribleReadingTest

static std::string Trim(const std::string& pText) {
    
    std::size_t aBegin = pText.find_first_not_of(" \t\r\n");
    
    if (aBegin == std::string::npos) {
        return "";
    }
    
    std::size_t aEnd = pText.find_last_not_of(" \t\r\n");
    
    return pText.substr(aBegin, aEnd - aBegin + 1U);
}

static bool StatementEqual(const std::string &pActual, const std::string &pExpected) {
    
    if (Trim(pActual) != Trim(pExpected)) {
        printf("Expected: %s\n", pExpected.c_str());
        printf("Got     : %s\n", pActual.c_str());
        printf("--------\n");
        return false;
    }
    if (Trim(pActual).empty()) {
        printf("Expected: %s\n", pExpected.c_str());
        printf("Got     : EMPTY\n");
        printf("--------\n");
        return false;
    }
    if (Trim(pExpected).empty()) {
        printf("Expected: EMPTY\n");
        printf("Got     : %s\n", pExpected.c_str());
        printf("--------\n");
        return false;
    }
    return true;
}

- (void)testHorribleCaseA {
    
    // Special case with loop index, matching buffer size.
    Varz aVars;
    GStatement aStatement = GQuick::MulEqualBufferInverted(aVars.mValue, aVars.mWorkerA, aVars.mLoopIndex, 0);
    std::string aExpected = "     aValue = aValue * aWorkLaneA[(S_BLOCK1 - i)];     ";
    const std::string aActual = aStatement.ToCPPStatements()[0];
    if (!StatementEqual(aActual, aExpected)) {
        XCTFail("statements were not equal (A). actual='%s' expected='%s'",
                aActual.c_str(),
                aExpected.c_str());
    }
}

- (void)testHorribleCaseB {
    Varz aVars;
    GStatement aStatement = GQuick::MulEqualBufferInverted(aVars.mValue, aVars.mWorkerA, aVars.mLoopIndex, 1);
    std::string aExpected = "     aValue = aValue * aWorkLaneA[(S_BLOCK1 - i + 1U)];     ";
    const std::string aActual = aStatement.ToCPPStatements()[0];
    if (!StatementEqual(aActual, aExpected)) {
        XCTFail("statements were not equal (B). actual='%s' expected='%s'",
                aActual.c_str(),
                aExpected.c_str());
    }
}

- (void)testHorribleCaseC {
    
    // Special case with loop index, matching buffer size.
    Varz aVars;
    GStatement aStatement = GQuick::MulEqualBufferInverted(aVars.mValue, aVars.mWorkerA, aVars.mCarry, 0);
    std::string aExpected = "     aValue = aValue * aWorkLaneA[(8191U - aCarry)];     ";
    const std::string aActual = aStatement.ToCPPStatements()[0];
    if (!StatementEqual(aActual, aExpected)) {
        XCTFail("statements were not equal (C). actual='%s' expected='%s'",
                aActual.c_str(),
                aExpected.c_str());
    }
}

- (void)testHorribleCaseD {
    
    // Special case with loop index, matching buffer size.
    Varz aVars;
    GStatement aStatement = GQuick::MulEqualBufferInverted(aVars.mValue, aVars.mWorkerA, aVars.mCarry, 1);
    std::string aExpected = "     aValue = aValue * aWorkLaneA[(8191U - aCarry + 1U)];     ";
    const std::string aActual = aStatement.ToCPPStatements()[0];
    if (!StatementEqual(aActual, aExpected)) {
        XCTFail("statements were not equal (D). actual='%s' expected='%s'",
                aActual.c_str(),
                aExpected.c_str());
    }
}

- (void)testHorribleCaseE {
    
    // Special case with loop index, matching buffer size.
    Varz aVars;
    GStatement aStatement = GQuick::MulEqualBufferInverted(aVars.mValue, aVars.mMaskWriteA, aVars.mCarry, 0);
    std::string aExpected = "     aValue = aValue * aMaskRowWriteA[(127U - aCarry)];     ";
    const std::string aActual = aStatement.ToCPPStatements()[0];
    if (!StatementEqual(aActual, aExpected)) {
        XCTFail("statements were not equal (E). actual='%s' expected='%s'",
                aActual.c_str(),
                aExpected.c_str());
    }
    
}

- (void)testHorribleCaseF {
    Varz aVars;
    const GSymbol aIndex = VarSymbol("aIndex");
    GStatement aStatement = GQuick::MulEqualBuffer(aVars.mValue, aVars.mWorkerA, aIndex, 0);
    std::string aExpected = "     aValue = aValue * aWorkLaneA[aIndex];     ";
    const std::string aActual = aStatement.ToCPPStatements()[0];
    if (!StatementEqual(aActual, aExpected)) {
        XCTFail("statements were not equal (F). actual='%s' expected='%s'",
                aActual.c_str(),
                aExpected.c_str());
    }
}

- (void)testHorribleCaseG {
    Varz aVars;
    const GSymbol aIndex = VarSymbol("aIndex");
    GStatement aStatement = GQuick::MulEqualBufferInverted(aVars.mValue, aVars.mWorkerA, aIndex, 0);
    std::string aExpected = "     aValue = aValue * aWorkLaneA[S_BLOCK1 - aIndex];     ";
    const std::string aActual = aStatement.ToCPPStatements()[0];
    if (!StatementEqual(aActual, aExpected)) {
        XCTFail("statements were not equal (G). actual='%s' expected='%s'",
                aActual.c_str(),
                aExpected.c_str());
    }
}

- (void)testHorribleCaseH {
    Varz aVars;
    GStatement aStatement = GQuick::ShiftLeftEqualVariable(aVars.mValue, aVars.mCarry);
    std::string aExpected = "     aValue = ShiftL64(aValue, aCarry);     ";
    const std::string aActual = aStatement.ToCPPStatements()[0];
    if (!StatementEqual(aActual, aExpected)) {
        XCTFail("statements were not equal (H). actual='%s' expected='%s'",
                aActual.c_str(),
                aExpected.c_str());
    }
}

- (void)testHorribleCaseI {
    Varz aVars;
    GStatement aStatement = GQuick::ShiftRightEqualVariable(aVars.mValue, aVars.mCarry);
    std::string aExpected = "     aValue = ShiftR64(aValue, aCarry);     ";
    const std::string aActual = aStatement.ToCPPStatements()[0];
    if (!StatementEqual(aActual, aExpected)) {
        XCTFail("statements were not equal (I). actual='%s' expected='%s'",
                aActual.c_str(),
                aExpected.c_str());
    }
}

@end
