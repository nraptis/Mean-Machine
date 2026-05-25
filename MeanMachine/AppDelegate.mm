//
//  AppDelegate.m
//  MeanMachine
//
//  Created by John Snow on 4/20/26.
//

#import "AppDelegate.h"

#include "FileIO.hpp"

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
#include "TwistSnow.hpp"
#include "TwistCryptoScoring.hpp"
#include "Rig.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "GAXSK.hpp"
#include "Builder.hpp"
#include "SixELRig.hpp"


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
    


    /*
    unsigned char aPassword[3];

    int aNumber = 0;
    
    int aRoundCounts[5];
    aRoundCounts[0] = 1;
    aRoundCounts[1] = 2;
    aRoundCounts[2] = 4;
    aRoundCounts[3] = 8;
    aRoundCounts[4] = 16;
    
    for (int aLetter1 = 'a'; aLetter1 <= 'z'; aLetter1++) {
        for (int aLetter2 = 'a'; aLetter2 <= 'z'; aLetter2++) {
            for (int aLetter3 = 'a'; aLetter3 <= 'z'; aLetter3++) {
                
                
                aPassword[0] = static_cast<unsigned char>(aLetter1);
                aPassword[1] = static_cast<unsigned char>(aLetter2);
                aPassword[2] = static_cast<unsigned char>(aLetter3);
                
                
                for (int aRoundIndex=0; aRoundIndex<5; aRoundIndex++) {
                    
                    SixELRig *aRig = new SixELRig();
                    aRig->SetRoundCount(aRoundCounts[aRoundIndex]);
                    
                    
                    TwistExpander_WiseOwl_0006 *aExpander = new TwistExpander_WiseOwl_0006();
                    
                    aRig->Run(aExpander,
                              aPassword,
                              3);
                    
                    aRig->SaveByteStreamProjectRoot("streams", "str_", aNumber++);
                    
                    printf("exported %d\n", aNumber);
                    
                    delete aExpander;
                    delete aRig;
                    
                }
            }
        }
    }
    */
    
    /*
    std::vector<std::string> aFilePaths =
        FileIO::GetAllFilesRecursive(FileIO::ProjectRoot("streams"));

    for (const std::string &aFile : aFilePaths) {
        if ((aFile.size() < 4) ||
            (aFile.substr(aFile.size() - 4) != ".bin")) {
            continue;
        }

        std::vector<std::uint8_t> aData;
        if (FileIO::Load(aFile, aData) == false) {
            continue;
        }

        printf("\n==============================\n");
        printf("file: %s\n", aFile.c_str());
        printf("size: %zu\n", aData.size());

        PrintHexChunk(aData, 0, 512, "front");

        PrintHexChunk(aData, S_BLOCK - 256, 512, "around S_BLOCK boundary");

        PrintHexChunk(aData, (S_BLOCK * 2) - 256, 512, "around 2*S_BLOCK boundary");
        PrintHexChunk(aData, (S_BLOCK * 3) - 256, 512, "around 3*S_BLOCK boundary");
        PrintHexChunk(aData, (S_BLOCK * 4) - 256, 512, "around 4*S_BLOCK boundary");
        PrintHexChunk(aData, (S_BLOCK * 5) - 256, 512, "around 5*S_BLOCK boundary");

        if (aData.size() >= 512) {
            PrintHexChunk(aData, aData.size() - 512, 512, "end");
        }
    }
    */
    

    
    if (IsRunningUnderXCTest() == false) {
        std::string aError;
        
        if (!Builder::Go("CornTesting/Gen",
                         "Kerpal",
                         6,
                         4,
                         &aError)) {
            printf("Builder::Go failed:\n%s\n", aError.c_str());
            return;
        }
        
        printf("done export...\n");
    }
    
    

    /*
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

        
        if (!aExpander.ExportCPPProjectRoot("CornTesting/Gen", &aError) ||
            !aExpander.ExportJSONProjectRoot("CornTesting/Gen", &aError)) {
            printf("expander export failed: %s\n", aError.c_str());
            return;
        }
        printf("done export...\n");
        
        
    }
    */
    
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
