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
#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "Random.hpp"
#include "GTwistExpander.hpp"
#include "GSeedRunKDF_A.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistSnow.hpp"
#include "TwistCryptoScoring.hpp"
#include "Rig.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "GAXSK.hpp"
#include "Builder.hpp"
#include "Avalancher.hpp"
#include "Rig.hpp"
#include "SnapShotter.hpp"

#include "SmartSquashControl.hpp"
#include "GrowAControl.hpp"
#include "GrowBControl.hpp"

int gCandidateIndex = 0;

/*

#include "TwistExpander_Alcor.hpp"
#include "TwistExpander_Aldebaran.hpp"
#include "TwistExpander_Alioth.hpp"
#include "TwistExpander_Alkaid.hpp"
#include "TwistExpander_Alnitak.hpp"
#include "TwistExpander_Altair.hpp"
#include "TwistExpander_Ankaa.hpp"
#include "TwistExpander_Antares.hpp"
#include "TwistExpander_Arcturus.hpp"
#include "TwistExpander_Athebyne.hpp"
#include "TwistExpander_Bellatrix.hpp"
#include "TwistExpander_Betelgeuse.hpp"
#include "TwistExpander_Canopus.hpp"
#include "TwistExpander_Capella.hpp"
#include "TwistExpander_Castor.hpp"
#include "TwistExpander_Gemma.hpp"
#include "TwistExpander_Mebsuta.hpp"
#include "TwistExpander_Menkent.hpp"
#include "TwistExpander_Mimosa.hpp"
#include "TwistExpander_Miram.hpp"
#include "TwistExpander_Mirfak.hpp"
#include "TwistExpander_Mothallah.hpp"
#include "TwistExpander_Naos.hpp"
#include "TwistExpander_Polaris.hpp"
#include "TwistExpander_Pollux.hpp"
#include "TwistExpander_Procyon.hpp"
#include "TwistExpander_Regulus.hpp"
#include "TwistExpander_Rigel.hpp"
#include "TwistExpander_Saiph.hpp"
#include "TwistExpander_Sirius.hpp"
#include "TwistExpander_Suhail.hpp"
#include "TwistExpander_Vega.hpp"

 */


#include "TwistExpander_Achernar.hpp"
 
#include "Scanner_MagicNumbers.hpp"
#include "OptimalCombinations.hpp"

#include "DirtyWorkSpace.hpp"
#include "CompareWorkSpace.hpp"


namespace {

bool IsRunningUnderXCTest() {
    return (std::getenv("XCTestConfigurationFilePath") != nullptr) ||
    (std::getenv("XCTestBundlePath") != nullptr);
}

std::vector<std::uint64_t> GenerateUniqueNonces(const std::size_t pCount) {
    std::vector<std::uint64_t> aNonces;
    std::unordered_set<std::uint64_t> aSeen;
    
    while (aNonces.size() < pCount) {
        const std::uint64_t aNonce = Random::Get64();
        if (aSeen.insert(aNonce).second) {
            aNonces.push_back(aNonce);
        }
    }
    
    return aNonces;
}

bool RunRigWithWorkSpace(TwistExpander *pExpander,
                         TwistWorkSpace *pWorkSpace,
                         Rig *pRig,
                         const std::vector<std::uint64_t> &pNonces,
                         std::uint8_t *pPassword,
                         const int pPasswordLength,
                         std::string *pErrorMessage) {
    if ((pExpander == nullptr) || (pWorkSpace == nullptr) || (pRig == nullptr)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "RunRigWithWorkSpace got a null argument";
        }
        return false;
    }
    if (pNonces.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "RunRigWithWorkSpace got no nonces";
        }
        return false;
    }
    
    pRig->SetBlockCount(32);
    if (pRig->mData == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "RunRigWithWorkSpace failed to allocate rig data";
        }
        return false;
    }
    
    TwistFarmSalt aFarmSalt;
    pExpander->Seed(pWorkSpace,
                    &aFarmSalt,
                    pNonces[0],
                    pPassword,
                    static_cast<std::size_t>(pPasswordLength),
                    pRig->mData);
    
    for (std::size_t aBlockIndex = 1U; aBlockIndex < pRig->mBlockCount; ++aBlockIndex) {
        std::uint8_t *aSource = pRig->mData + (aBlockIndex - 1U) * S_BLOCK;
        std::uint8_t *aDest = pRig->mData + aBlockIndex * S_BLOCK;
        pExpander->TwistBlock(pWorkSpace,
                              aSource,
                              aDest);
    }
    
    return true;
}

}

@interface AppDelegate ()

@property (strong) IBOutlet NSWindow *window;
@end

@implementation AppDelegate


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    (void)aNotification;

    /*
    std::uint64_t aExplorationCases = 500ULL;
    while (true) {
        char aExplorationDigits[32];
        std::snprintf(aExplorationDigits,
                      sizeof(aExplorationDigits),
                      "%016llu",
                      static_cast<unsigned long long>(aExplorationCases));
        const std::string aExplorationText(aExplorationDigits);
        std::printf("Starting control exploration round with %s cases.\n",
                    aExplorationText.c_str());

        SmartSquashControl::Reset();
        for (std::size_t i = 0U;
             i < SmartSquashControl::kCandidateCount;
             ++i) {
            SmartSquashControl::GenerateSquashInvestToKeyBoxes(
                aExplorationCases);
        }

        SmartSquashControl::Print();

        std::string aError;
        const std::string aSquashPath =
            "Assets/squash_pre_planned_" + aExplorationText +
            "/SmartSquashPreview.cpp";
        if (!SmartSquashControl::SavePreview(aSquashPath, &aError)) {
            std::printf("%s\n", aError.c_str());
        }

        // ------------------

        GrowBControl::Reset();
        for (std::size_t i = 0U;
             i < GrowBControl::kCandidateCount;
             ++i) {
            GrowBControl::Generate(aExplorationCases);
        }

        GrowBControl::Print();

        std::string aGrowBError;
        const std::string aGrowBPath =
            "Assets/grow_b_pre_planned_" + aExplorationText +
            "/GrowBPreview.cpp";
        if (!GrowBControl::SavePreview(aGrowBPath, &aGrowBError)) {
            std::printf("%s\n", aGrowBError.c_str());
        }

        // ------------------

        GrowAControl::Reset();
        for (std::size_t i = 0U;
             i < GrowAControl::kCandidateCount;
             ++i) {
            GrowAControl::Generate(aExplorationCases);
        }

        GrowAControl::Print();

        std::string aGrowAError;
        const std::string aGrowAPath =
            "Assets/grow_a_pre_planned_" + aExplorationText +
            "/GrowAPreview.cpp";
        if (!GrowAControl::SavePreview(aGrowAPath, &aGrowAError)) {
            std::printf("%s\n", aGrowAError.c_str());
        }

        std::printf("Finished control exploration round with %s cases.\n",
                    aExplorationText.c_str());
        const std::uint64_t aMaximumCases =
            std::numeric_limits<std::uint64_t>::max();
        aExplorationCases =
            (aExplorationCases > (aMaximumCases / 10ULL)) ?
            aMaximumCases :
            (aExplorationCases * 10ULL);
    }

    return;
    
    //Scanner_MagicNumbers::Check();
    
    //return;
    */
    
    /*
    if (IsRunningUnderXCTest() == false) {
        std::string aError;

        if (!Builder::Go("CornTesting/Gen",
                         "Achernar",
                         26,
                         8,
                         true,
                         &aError)) {
            printf("Builder::Go failed:\n%s\n", aError.c_str());
            return;
        }
    }
    printf("Done with export block...\n");
    
    return;
    */
    
    
    printf("App is awake and running...\n");
    
    
    if (IsRunningUnderXCTest()) {
        printf("skipping app, xc test...\n");
        return;
    }
    printf("Done with optimal combinations...\n");
    
    
    /*
    TwistExpander_Achernar aExpander;

    Rig aRig;
    aRig.SetBlockCount(2);

    std::uint8_t aPassword[32] = {
        'c', 'o', 'r', 'r', 'e', 'c', 't', 'h', 'o', 'r', 's', 'e',
        'b', 'a', 't', 't', 'e', 'r', 'y', 's', 't', 'a', 'p', 'l',
        'e', 'r', 'o', 'c', 'k', 's',
        0, 0
    };

    aRig.Run(&aExpander,
             aPassword,
             30);

    SnapShotter::SaveProjectRoot("dump",
                                 "EXPORTS");

    printf("exported...\n");
    
    return;
    */
    
    
    /*
    unsigned char aPassword[3];

    int aNumber = 50;
    
    
    for (int aLetter1 = 'a'; aLetter1 <= 'z'; aLetter1++) {
        for (int aLetter2 = 'a'; aLetter2 <= 'z'; aLetter2++) {
            for (int aLetter3 = 'a'; aLetter3 <= 'z'; aLetter3++) {
                
                TwistExpander_BaseBall aExpanderA;
                TwistExpander_BaseBall aExpanderB;
                
                TwistWorkSpace aWorkSpaceA;
                TwistWorkSpace aWorkSpaceB;
                TwistWorkSpace aWorkSpaceC;
                
                aPassword[0] = static_cast<unsigned char>(aLetter1);
                aPassword[1] = static_cast<unsigned char>(aLetter2);
                aPassword[2] = static_cast<unsigned char>(aLetter3);
                
                const std::vector<std::uint64_t> aNonces = GenerateUniqueNonces(5U);
                
                DirtyWorkSpace::Scramble(&aWorkSpaceA, &aExpanderA);
                DirtyWorkSpace::Scramble(&aWorkSpaceB, &aExpanderB);
                DirtyWorkSpace::Scramble(&aWorkSpaceC, nullptr);
                
                Rig aRigA;
                Rig aRigB;
                Rig aRigC;
                
                std::string aErrorMessage;
                if (!RunRigWithWorkSpace(&aExpanderA, &aWorkSpaceA, &aRigA, aNonces, aPassword, 3, &aErrorMessage)) {
                    printf("rig A failed for %c%c%c: %s\n", aPassword[0], aPassword[1], aPassword[2], aErrorMessage.c_str());
                    return;
                }
                if (!RunRigWithWorkSpace(&aExpanderB, &aWorkSpaceB, &aRigB, aNonces, aPassword, 3, &aErrorMessage)) {
                    printf("rig B failed for %c%c%c: %s\n", aPassword[0], aPassword[1], aPassword[2], aErrorMessage.c_str());
                    return;
                }
                
                if (!CompareWorkSpace::CompareBlocks(aRigA.mData, aRigB.mData, 32U, &aErrorMessage)) {
                    printf("A/B destination compare failed for %c%c%c: %s\n", aPassword[0], aPassword[1], aPassword[2], aErrorMessage.c_str());
                    return;
                }
                
                if (!RunRigWithWorkSpace(&aExpanderA, &aWorkSpaceC, &aRigC, aNonces, aPassword, 3, &aErrorMessage)) {
                    printf("rig C failed for %c%c%c: %s\n", aPassword[0], aPassword[1], aPassword[2], aErrorMessage.c_str());
                    return;
                }
                
                if (!CompareWorkSpace::CompareBlocks(aRigB.mData, aRigC.mData, 32U, &aErrorMessage)) {
                    printf("B/C destination compare failed for %c%c%c: %s\n", aPassword[0], aPassword[1], aPassword[2], aErrorMessage.c_str());
                    return;
                }
                
                aRigC.SaveByteStreamProjectRoot("streams", "str_", aNumber++);
                printf("exported %d\n", aNumber);
            }
        }
    }
    return;
    */
    
    
    
     
    
    
   
    
    
    
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
                    
                    TwistExpander_Soccer aCandidate;
                    
                    Rig aRig;
                    aRig.SetBlockCount(32);
                    aRig.Run(&aCandidate, aPassword, 3);
                    
                    aRig.SaveByteStreamProjectRoot("streams", "str_", aNumber++);

                    printf("exported %d\n", aNumber);
                    
                }
            }
        }
    }
    return;
    */
    
    
    
    
    

    /*
    if (IsRunningUnderXCTest() == false) {
        Soccer aCandidate;
        
        std::string aPasswordA = "cat";
        std::string aPasswordB = "eat";
        
        Avalancher aAva;
        aAva.SetExpander(&aCandidate);
        
        auto aResult = aAva.DiffAB(aPasswordA, aPasswordB);
        aResult.PrintExtended("Soccer");
        aResult.PrintQuick("Soccer");
        
    }
    */
    
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
                    
                    Soccer aCandidate;
                    
                    Rig aRig;
                    aRig.SetBlockCount(32);
                    aRig.Run(&aCandidate, aPassword, 3);
                    
                    aRig.SaveByteStreamProjectRoot("streams", "str_", aNumber++);

                    printf("exported %d\n", aNumber);
                    
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
        std::vector<std::string> aNames = {
            "Achernar",
            "Alcor",
            "Aldebaran",
            "Alioth",
            "Alkaid",
            "Alnitak",
            "Altair",
            "Ankaa",
            "Antares",
            "Arcturus",
            "Athebyne",
            "Bellatrix",
            "Betelgeuse",
            "Canopus",
            "Capella",
            "Castor",
            "Mebsuta",
            "Menkent",
            "Mimosa",
            "Miram",
            "Mirfak",
            "Mothallah",
            "Naos",
            "Polaris",
            "Pollux",
            "Procyon",
            "Regulus",
            "Gemma",
            "Rigel",
            "Saiph",
            "Sirius",
            "Suhail",
            "Vega"
            
        };
        
        printf("name count is %d\n", (int)aNames.size());
        
        for (auto aName: aNames) {
            if (!Builder::Go("CornTesting/Gen",
                             aName,
                             26,
                             8,
                             false,
                             &aError)) {
                printf("Builder::Go failed:\n%s\n", aError.c_str());
                return;
            }
            gCandidateIndex++;
        }

        printf("done export...\n");
    }
    
    
    return;
    

    /*
    if (IsRunningUnderXCTest() == false) {
        
        
        GSeedRunKDF_A_A aKDF;
        std::string aError;
        GTwistExpander aExpander;
        aExpander.mNameBase = "Toberman";
        
        if (!aKDF.Plan(&aError)) {
            printf("error on GSeedRunKDF_A_A.Plan\n");
            printf("%s\n", aError.c_str());
            return;
        }
        
        if (!aKDF.Build(aExpander.mKDF, &aError)) {
            printf("error on GSeedRunKDF_A_A.Build\n");
            printf("%s\n", aError.c_str());
            return;
        }
        if (aExpander.mKDF.GetBatchJsonText().empty() &&
            aExpander.mKDF.GetStringLines().empty()) {
            printf("error on GSeedRunKDF_A_A.Build\n");
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
