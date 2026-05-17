//
//  MixBrewTests.m
//  CornTesting
//
//  Created by Dragon on 4/29/26.
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

@interface MixBrewTests : XCTestCase

@end

@implementation MixBrewTests

- (void)testComposerFailsWhenImplicitLoopIndexIsUnset {
    Varz aVars;

    GLoopFragmentComposer aComposer;
    aComposer.ResetSetEqual(aVars.mSelect);
    aComposer.MixBuffer(aVars.mSaltA).OffsetIverted(100);

    std::vector<GStatement> aStatements;
    std::string aError;
    if (aComposer.Bake(&aStatements, &aError)) {
        XCTFail("composer bake should fail when implicit loop index is required but unset");
        return;
    }

    if (aError.find("required loop index") == std::string::npos) {
        printf("unexpected error: %s\n", aError.c_str());
        XCTFail("composer bake failed with unexpected error message");
        return;
    }
}

@end
