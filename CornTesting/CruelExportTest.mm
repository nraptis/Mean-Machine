//
//  CruelExportTest.m
//  CornTesting
//
//  Created by John Snow on 4/24/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "TwistWorkSpace.hpp"
#include "Random.hpp"
#include "TwistExpander_FrodoBaggins.hpp"
#include "GTwistTwister.hpp"
#include "GTwistExpander.hpp"
#include "TwistExpander.hpp"
#include <vector>

@interface CruelExportTest : XCTestCase

@end

@implementation CruelExportTest

- (void)testExportedTwister {
    
    
    /*
     {
        // the pre-step
        std::string aErrorString;
        GSeedWorkLaneRecipeWorkSpace aRecipeSpace;
        
        
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
        
        GTwistExpander aExpanderBuilder;
        
        SBoxTables::CustomInjectFourSalt(&aExpanderBuilder);
        SBoxTables::CustomInjectFourSBox(&aExpanderBuilder);
        
        aExpanderBuilder.mNameBase = "Flyyyyy"; // DemoExpander, DemoSeeder, DemoTwister

        aExpanderBuilder.mSeeder.AddBatch(aBatch1);
        aExpanderBuilder.mSeeder.AddBatch(aBatch2);

        aExpanderBuilder.mTwister.AddBatch(aBatch2); // example, it has the twister and the seeder

        // String-only lines for direct, non-calculated snippets.
        aExpanderBuilder.mSeeder.AddWorkspaceAliasLine("aSaltA", "mSaltA");
        aExpanderBuilder.mTwister.AddWorkspaceAliasLine("aSaltA", "mSaltA");

        // Calculated-value line sample.
        aExpanderBuilder.mSeeder.AddAssignByteLine("aCarry", 0xDCU);
        aExpanderBuilder.mTwister.AddAssignByteLine("aCarry", 0xFAU);

        if (!aExpanderBuilder.ExportCPPProjectRoot("generated/cpp//")) {
            XCTFail("{export test} C++ export failed.");
            return;
        }
        if (!aExpanderBuilder.ExportJSONProjectRoot("Assets/test/pooop.json")) {
            XCTFail("{export test} JSON export failed.");
            return;
        }
        
        
        
    }
    */
    
    
    const char *pwd = "a man a plan a canal";
    int ps = (int)strlen(pwd);
    
    // This is exported from something in G, as C++ code we can drop in over DemoExpander
    TwistExpander_FrodoBaggins aExpanderA;
    
    // This uses json load;
    GTwistTwister aExpanderB;
    
    std::string aLoadError;
    if (!aExpanderB.LoadProjectRoot("aaa/bbb/ccc/FrodoBaggins.json", &aLoadError)) {
        XCTFail("%s", aLoadError.c_str());
        return;
    }
    
    unsigned char aSourceA[S_BLOCK];
    unsigned char aSourceB[S_BLOCK];
    
    TwistWorkSpace aWorkSpaceA;
    TwistWorkSpace aWorkSpaceB;
    
    memset(aWorkSpaceA.mWorkLaneA, 0, S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneB, 0, S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneC, 0, S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneD, 0, S_BLOCK);
    
    memset(aWorkSpaceB.mWorkLaneA, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneB, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneC, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneD, 0, S_BLOCK);
    
    aExpanderA.Seed(&aWorkSpaceA, aSourceA, (std::uint8_t *)pwd, ps);
    aExpanderB.Seed(&aWorkSpaceB, aSourceB, (std::uint8_t *)pwd, ps);

    for (int i=0;i<S_BLOCK;i++) {
        if (aWorkSpaceA.mWorkLaneA[i] != aWorkSpaceB.mWorkLaneA[i]) {
            XCTFail("{export test} work lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneA[i], aWorkSpaceB.mWorkLaneA[i]);
            return;
        }
        if (aWorkSpaceA.mWorkLaneB[i] != aWorkSpaceB.mWorkLaneB[i]) {
            XCTFail("{export test} work lane b mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneB[i], aWorkSpaceB.mWorkLaneB[i]);
            return;
        }
        if (aWorkSpaceA.mWorkLaneC[i] != aWorkSpaceB.mWorkLaneC[i]) {
            XCTFail("{export test} work lane c mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneC[i], aWorkSpaceB.mWorkLaneC[i]);
            return;
        }
        if (aWorkSpaceA.mWorkLaneD[i] != aWorkSpaceB.mWorkLaneD[i]) {
            XCTFail("{export test} work lane d mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneD[i], aWorkSpaceB.mWorkLaneD[i]);
            return;
        }
    }
    
    
    
}



@end
