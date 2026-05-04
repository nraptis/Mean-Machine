//
//  AppDelegate.m
//  MeanMachine
//
//  Created by John Snow on 4/20/26.
//

#import "AppDelegate.h"

#include "FileIO.hpp"
#include "SBoxTables.hpp"

#include <algorithm>
#include <array>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <limits>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "TwistFastMatrix.hpp"
#include "Random.hpp"
#include "GTwistExpander.hpp"
#include "TwistCryptoGenerator.hpp"
#include "GSeedDeriveMaterial.hpp"
#include "TwistSnow.hpp"
#include "SBoxMaterial.hpp"
#include "TwistCryptoScoring.hpp"
#include "FrodoShireA.hpp"
#include "ByteString.hpp"
#include "Rig.hpp"

@interface AppDelegate ()

@property (strong) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    (void)aNotification;
    
    /*
    std::vector<std::string> aPasswords;
    aPasswords.push_back("cat");
    aPasswords.push_back("dog");
    aPasswords.push_back("ham");
    
    
    
    int aBlockCount = 32;
    
    
    unsigned char aPassword[3];
    
    Rig aRig;
    aRig.SetBlockCount(aBlockCount);
    
    int aNumber = 0;
    
    for (int aLetter1=0; aLetter1<256; aLetter1++) {
        for (int aLetter2=0; aLetter2<256; aLetter2++) {
            //for (int aLetter3=0; aLetter3<256; aLetter3++) {
                
                FrodoShireA aShire;
                
                aPassword[0] = aLetter1;
                aPassword[1] = aLetter2;
                //aPassword[2] = aLetter3;
                
                aRig.Run(&aShire, aPassword, 2);
                
                
                //aRig.SaveByteStreamProjectRootLastAsciiPassword();
                
                aRig.SaveByteStreamProjectRoot("streams", "str_", aNumber++);
            //}
            
            
        }
    }
    */
    

    
    
    /*
    TwistCryptoScoring aScoring;
    auto aSBoxes = SBoxTables::Get();
    printf("there are %d s boxes to scan\n", (int)aSBoxes.size());
    
    for (int aSBoxIndex = 0; aSBoxIndex < (int)aSBoxes.size(); aSBoxIndex++) {
        
        auto &aSBox = aSBoxes[aSBoxIndex];
        
        auto aCycle0 = aScoring.ComputeMinimumCycle_256(aSBox.data(), (int)aSBox.size());
        //auto aCycle1 = aScoring.ComputeMinimumCycleRotL1AfterGate_256(aSBox.data(), (int)aSBox.size());
        auto aCycle3 = aScoring.ComputeMinimumCycleRotL3AfterGate_256(aSBox.data(), (int)aSBox.size());
        auto aCycle5 = aScoring.ComputeMinimumCycleRotL5AfterGate_256(aSBox.data(), (int)aSBox.size());
        //auto aCycle7 = aScoring.ComputeMinimumCycleRotL7AfterGate_256(aSBox.data(), (int)aSBox.size());
        
        auto aMinCycle = aCycle0;
        
        //if (aCycle1 < aMinCycle) { aMinCycle = aCycle1; }
        if (aCycle3 < aMinCycle) { aMinCycle = aCycle3; }
        if (aCycle5 < aMinCycle) { aMinCycle = aCycle5; }
        //if (aCycle7 < aMinCycle) { aMinCycle = aCycle7; }
        
        if (aMinCycle >= 2) {
            printf("S box %d of %d had min cycle of %d\n",
                   aSBoxIndex,
                   (int)aSBoxes.size(),
                   (int)aMinCycle);
        }
    }
    */
    
    
    GSeedDeriveMaterial aDer;
    std::string aError;
    GTwistExpander aExpander;
    aExpander.mNameBase = "Goose";
    
    if (!aDer.PlanPhaseA(&aError)) {
        printf("error on GSeedDeriveMaterial.PlanPhaseA\n");
        printf("%s\n", aError.c_str());
        return;
    }
    
    if (!aDer.BuildPhaseA(aExpander.mSeeder, &aError)) {
        printf("error on GSeedDeriveMaterial.BuildPhaseA\n");
        printf("%s\n", aError.c_str());
        return;
    }
    
    
    if (!aExpander.ExportCPPProjectRoot("CornTesting/Gen", &aError) ||
        !aExpander.ExportJSONProjectRoot("CornTesting/Gen", &aError) ||
        !aExpander.ExportCPPProjectRoot("aaa/bbb/ccc", &aError) ||
        !aExpander.ExportJSONProjectRoot("aaa/bbb/ccc", &aError)) {
        printf("expander export failed: %s\n", aError.c_str());
        return;
    }
    
    
    printf("process finished\n");

    // if (IsRunningUnderXCTest()) { return; }
    
    /*
    TwistCryptoGenerator aGen;
    TwistCryptoScoring aAnalyzer;

    std::uint8_t aSource[S_BLOCK];
    for (int i=0;i<S_BLOCK;i++) {
        aSource[i] = Random::Get(256);
    }
    
    std::uint8_t aBox1[256];
    std::uint8_t aBox2[256];
    std::uint8_t aBox3[256];
    std::uint8_t aBox4[256];
    aGen.Make(aSource, aBox1, aBox2, aBox3, aBox4);
    
    std::uint8_t aSalt1[128];
    std::uint8_t aSalt2[128];
    std::uint8_t aSalt3[128];
    std::uint8_t aSalt4[128];
    
    aGen.Salt(aSource,
              aSalt1,
              aSalt2,
              aSalt3,
              aSalt4,
              aBox1,
              aBox2,
              aBox3,
              aBox4);
    
    std::uint8_t aBox5[256];
    std::uint8_t aBox6[256];
    std::uint8_t aBox7[256];
    std::uint8_t aBox8[256];
    aGen.Make(aSource, aBox5, aBox6, aBox7, aBox8);
    
    std::uint8_t aSalt5[128];
    std::uint8_t aSalt6[128];
    std::uint8_t aSalt7[128];
    std::uint8_t aSalt8[128];
    
    aGen.Salt(aSource,
              aSalt5,
              aSalt6,
              aSalt7,
              aSalt8,
              aSalt1,
              aSalt2,
              aSalt3,
              aSalt4,
              aBox1,
              aBox2,
              aBox3,
              aBox4,
              aBox5,
              aBox6,
              aBox7,
              aBox8);
    */

    
    
    
    
    /*
    if (!aSeedWorkerBuilder.BuildPhaseA(aSeedBranch, aError)) {
        
    }
    
    
    if (!aRecipeSpace.Plan(false, aErrorString)) {
        printf("{real seeder flow} stepA pass1 plan failed: %s\n", aErrorString.c_str());
        return;
    }
    
    
   
    if (!aRecipeSpace.Bake(aBatch1.mLoops, aErrorString)) {
        printf("{real seeder flow} stepA pass1 bake failed: %s\n", aErrorString.c_str());
        return;
    }
    
    GBatch aBatch2;
    if (!aRecipeSpace.Plan(true, aErrorString)) {
        printf("{real seeder flow} stepA pass2 plan failed: %s\n", aErrorString.c_str());
        return;
    }
    
    
   
    if (!aRecipeSpace.Bake(aBatch2.mLoops, aErrorString)) {
        printf("{real seeder flow} stepA pass2 bake failed: %s\n", aErrorString.c_str());
        return;
    }
    
    
    printf("ok, the plan worked\n");
    
    printf("%s\n", aBatch1.ToPrettyString().c_str());
    
    printf("ok, the plan worked\n");
    
    printf("%s\n", aBatch2.ToPrettyString().c_str());
    
    printf("ok, the plan worked\n");
    
    
    
    GTwistExpander aExpander;
    
    aExpander.mSeeder.AddBatch(aBatch1);
    aExpander.mSeeder.AddBatch(aBatch2);
    
    aExpander.mSeeder.AddAssignByteLine("aValue", Random::Get(200000000));
    aExpander.mSeeder.AddAssignByteLine("aCarry", Random::Get(200000000));
    aExpander.mSeeder.AddAssignByteLine("aPermute", Random::Get(200000000));
    
    aExpander.mNameBase = "Froyo";
    
    if (!aExpander.ExportCPPProjectRoot("CornTesting/Gen", &aErrorString) ||
        !aExpander.ExportJSONProjectRoot("CornTesting/Gen", &aErrorString) ||
        !aExpander.ExportCPPProjectRoot("aaa/bbb/ccc", &aErrorString) ||
        !aExpander.ExportJSONProjectRoot("aaa/bbb/ccc", &aErrorString)) {
        printf("expander export failed: %s\n", aErrorString.c_str());
        return;
    }
    
    */
    
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    (void)aNotification;
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end
