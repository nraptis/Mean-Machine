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
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "TwistFastMatrix.hpp"
#include "Random.hpp"
#include "GTwistExpander.hpp"
#include "GSeedRunKDF2.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistSnow.hpp"
#include "TwistCryptoScoring.hpp"
#include "Rig.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "GAXSK.hpp"


namespace {

bool IsRunningUnderXCTest() {
    return (std::getenv("XCTestConfigurationFilePath") != nullptr) ||
    (std::getenv("XCTestBundlePath") != nullptr);
}

}

@interface AppDelegate ()

@property (strong) IBOutlet NSWindow *window;
@end

@implementation AppDelegate


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    (void)aNotification;

    if (IsRunningUnderXCTest() == false) {
        GSeedRunKDF2 aKDF;
        std::string aError;
        GTwistExpander aExpander;
        aExpander.mNameBase = "Toberman";
        
        if (!aKDF.Plan(&aError)) {
            printf("error on GSeedRunKDF2.Plan\n");
            printf("%s\n", aError.c_str());
            return;
        }
        
        if (!aKDF.Build(aExpander.mKDF, &aError)) {
            printf("error on GSeedRunKDF2.Build\n");
            printf("%s\n", aError.c_str());
            return;
        }
        if (aExpander.mKDF.GetBatchJsonText().empty() &&
            aExpander.mKDF.GetStringLines().empty()) {
            printf("error on GSeedRunKDF2.Build\n");
            printf("kdf branch export was empty (no batches and no lines)\n");
            return;
        }
        
        aExpander.mSeed.AddLine("// [phase ii]");
     
        /*
        GSeedMatrixRollups aMatr;
        if (!aMatr.Plan(&aError)) {
            printf("error on GSeedMatrixRollups.Plan\n");
            printf("%s\n", aError.c_str());
            return;
        }
        
        if (!aMatr.Build(aExpander.mSeed, &aError)) {
            printf("error on GSeedMatrixRollups.Build\n");
            printf("%s\n", aError.c_str());
            return;
        }
       
        
        
        GRunMatrixDiffusionConfig aDiffusionA;
        aDiffusionA.mInputA = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
        aDiffusionA.mInputB = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
        aDiffusionA.mOutputA = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
        aDiffusionA.mOutputB = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
        aDiffusionA.mShuffleEntropyA = BufSymbol(TwistWorkSpaceSlot::kIndexList256A);
        aDiffusionA.mShuffleEntropyB = BufSymbol(TwistWorkSpaceSlot::kIndexList256A);
        aDiffusionA.mShuffleEntropyC = BufSymbol(TwistWorkSpaceSlot::kIndexList256A);
        aDiffusionA.mShuffleEntropyD = BufSymbol(TwistWorkSpaceSlot::kIndexList256A);
        aDiffusionA.mOperationSourceA = BufSymbol(TwistWorkSpaceSlot::kOperationLaneA);
        aDiffusionA.mOperationSourceB = BufSymbol(TwistWorkSpaceSlot::kOperationLaneA);

        GBatch aBatch;
        aBatch.AddComment("seed-matrix-diffusion: workA/workC -> maskA/maskB");
        if (!GRunMatrixDiffusion::Bake(aDiffusionA, &aBatch, &aError)) {
            printf("error on matrix dif: %s\n", aError.c_str());
            return;
        }
        
        aExpander.mKDF.AddBatch(aBatch);
        
        printf("trying export...\n");
         */
        
        if (!aExpander.ExportCPPProjectRoot("CornTesting/Gen", &aError) ||
            !aExpander.ExportJSONProjectRoot("CornTesting/Gen", &aError)) {
            printf("expander export failed: %s\n", aError.c_str());
            return;
        }
        printf("done export...\n");
        
        
    }
    
    /*
    unsigned char aPassword[3];

    int aNumber = 0;
    
    int aBlockCount = 1;

    TwistWorkSpace aWorkSpace;
    TwistFarmSBox aFarmSBox;
    TwistFarmSalt aFarmSalt;

    int aDataLength = S_BLOCK * aBlockCount;
    std::uint8_t * aSource= new std::uint8_t[aDataLength];
    std::uint8_t *aLaneA= new std::uint8_t[aDataLength];
    std::uint8_t *aLaneB= new std::uint8_t[aDataLength];
    std::uint8_t *aLaneC= new std::uint8_t[aDataLength];

    Rig aRig;
    aRig.SetBlockCount(aBlockCount);
    
    int aCOunt = 0;
    for (int aLetter1 = 'a'; aLetter1 <= 'z'; aLetter1++) {
        
        aPassword[0] = static_cast<unsigned char>(aLetter1);
        //aPassword[1] = static_cast<unsigned char>(aLetter2);
        //aPassword[2] = static_cast<unsigned char>(aLetter3);
        
        
        LardExpander::UnrollPasswordToSource(aSource,
                                             aPassword,
                                             1,
                                             aDataLength);
        
        LardExpander aExpander;
        aExpander.mDataLength = aDataLength;
        aExpander.mPassword = aSource;
        aExpander.mLaneA = aLaneA;
        aExpander.mLaneB = aLaneB;
        aExpander.mLaneC = aLaneC;
        aExpander.mLaneD = aRig.mData;
        
        aExpander.Roll();
        
        aRig.SaveByteStreamProjectRoot("streams", "str_", aNumber++);
        
        printf("exported %d\n", aNumber);
        
    }
    
    return;
    
    
    
    */
   
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    (void)aNotification;
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end
