//
//  SelectLineTest.m
//  CornTesting
//
//  Created by Dragon on 5/3/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "TwistWorkSpace.hpp"
#include "Random.hpp"
#include "GTwistTwister.hpp"
#include "GSeedDeriveMaterial.hpp"
#include "FileIO.hpp"
#include "GExpr.hpp"
#include "GSeedProgram.hpp"
#include "GSelect.hpp"

#include "GTwistExpander.hpp"
#include "TwistExpander.hpp"
#include <vector>

@interface SelectLineTest : XCTestCase

@end

@implementation SelectLineTest

- (void)testSelectFour {

    int aCountA = 0;
    int aCountB = 0;
    int aCountC = 0;
    int aCountD = 0;
    
    for (int aSelect=0;aSelect<256;aSelect++) {
        
        if ((aSelect & 0x12U) > 8) {
            if ((aSelect & 0x12U) > 16) {
                aCountA++;
            } else {
                aCountB++;
            }
        } else {
            if ((aSelect & 0x12U) > 0) {
                aCountC++;
            } else {
                aCountD++;
            }
        }
    }
    
    if ((aCountA != 64) || (aCountB != 64) || (aCountC != 64) || (aCountD != 64)) {
        printf("Select Equal Test Failed [%d %d %d %d]\n", aCountA, aCountB, aCountC, aCountD);
        XCTFail("Select line 4 failed.");
        return;
    }
    
}

- (void)testSelectTwo {

    int aCountA = 0;
    int aCountB = 0;
    
    for (int aSelect=0;aSelect<256;aSelect++) {
        
        if ((aSelect & 0x7CU) > 61) {
            aCountA++;
        } else {
            aCountB++;
        }
    }
    
    if ((aCountA != 128) || (aCountB != 128)) {
        printf("Select Equal Test Failed [%d %d]\n", aCountA, aCountB);
        XCTFail("Select line 2 failed.");
        return;
    }
    
}

- (void)testBakeUsesSelectValueWithoutTempAssign {
    GSelect aSelect;
    aSelect.mMask = 0x0CU;
    aSelect.mThresholdA = 3;
    aSelect.AddStatementA(GStatement::RawLine("A();"));
    aSelect.AddStatementB(GStatement::RawLine("B();"));

    std::vector<GStatement> aStatements;
    std::string aError;
    const bool aBaked = aSelect.Bake(GSymbol::Var("aPrism"), &aStatements, &aError);
    XCTAssertTrue(aBaked, "Expected bake success.");
    XCTAssertTrue(aStatements.size() == 5U, "Expected 5 lines for two-way select.");
    XCTAssertTrue(aStatements[0].IsRawLine(), "Expected raw line conditional.");
    XCTAssertTrue(aStatements[0].mRawLine.find("if ((aPrism & 0x0CU) > 3)") != std::string::npos,
                  "Expected condition to use select value symbol directly.");
    for (const GStatement &aStatement : aStatements) {
        XCTAssertFalse(aStatement.IsRawLine() && aStatement.mRawLine.find("aSelect = aPrism") != std::string::npos,
                       "Unexpected temporary select assignment.");
    }
}

@end
