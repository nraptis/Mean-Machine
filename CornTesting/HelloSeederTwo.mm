//
//  HelloSeederTwo.m
//  CornTesting
//
//  Created by John Snow on 4/22/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include <algorithm>
#include <vector>
#include "SBoxTables.hpp"
#include "TwistWorkSpace.hpp"
//#include "TwistSeedBuilder.hpp"
#include "TwistSeeder.hpp"
#include "GStatementRecipe.hpp"
#include "GSymbol.hpp"
#include "GSeedProgram.hpp"

#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "Random.hpp"
//#include "GSeedWorkLaneRecipe.hpp"
#include "GSeedStepARecipe.hpp"



@interface HelloSeederTwo : XCTestCase

@end

@implementation HelloSeederTwo

- (void)testRealSeedFlow {
    
    
    
    std::string aErrorString;
    GSeedStepARecipeWorkSpace aRecipeSpace;
    
    
    GBatch aBatch1;
    if (!aRecipeSpace.Plan(false, aErrorString)) {
        XCTFail("{real seeder flow} work lane recipe failed to plan.");
        return;
    }
    
    if (!aRecipeSpace.Bake(aBatch1.mLoops, aErrorString)) {
        XCTFail("{real seeder flow} work lane recipe failed to plan.");
        return;
    }
    
    GBatch aBatch2;
    if (!aRecipeSpace.Plan(true, aErrorString)) {
        XCTFail("{real seeder flow} work lane recipe failed to plan.");
        return;
    }
    
    
   
    if (!aRecipeSpace.Bake(aBatch2.mLoops, aErrorString)) {
        XCTFail("{real seeder flow} work lane recipe failed to plan.");
        return;
    }
    
    
    
    printf("ok, the plan worked\n");
    
    printf("%s\n", aBatch1.ToPrettyString().c_str());
    
    
    printf("ok, the plan worked\n");
    
    printf("%s\n", aBatch2.ToPrettyString().c_str());
    
    printf("ok, the plan worked\n");
    
    

}



@end
