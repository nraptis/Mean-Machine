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
#include <vector>
#include <unordered_map>
#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"
#include "Random.hpp"
#include "GTwistExpander.hpp"
#include "GSeedRunKDF_A.hpp"
#include "GSeedRunKeyBox.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistSnow.hpp"
#include "TwistCryptoScoring.hpp"
#include "Rig.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "GAXSK.hpp"
#include "Builder.hpp"
#include "Avalancher.hpp"

#include "GrowAControl.hpp"
#include "GrowBControl.hpp"
#include "FoldSeedControl.hpp"
#include "FoldTwistControl.hpp"
#include "LaneSplitControl.hpp"

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

bool AddKeyBoxLaneSplitGroups(std::string *pErrorMessage) {
    return LaneSplitControl::AddLaneGroup(
               {
                   TwistWorkSpaceSlot::kPoisonLaneA,
                   TwistWorkSpaceSlot::kPoisonLaneB,
                   TwistWorkSpaceSlot::kPoisonLaneC,
                   TwistWorkSpaceSlot::kPoisonLaneD,
               },
               pErrorMessage) &&
           LaneSplitControl::AddLaneGroup(
               {
                   TwistWorkSpaceSlot::kPlasmaLaneA,
                   TwistWorkSpaceSlot::kPlasmaLaneB,
                   TwistWorkSpaceSlot::kPlasmaLaneC,
                   TwistWorkSpaceSlot::kPlasmaLaneD,
               },
               pErrorMessage);
}

std::string ControlValueAssetFolder(const char *pStem,
                                    const std::uint64_t pExplorationCases) {
    char aCaseText[32];
    std::snprintf(aCaseText,
                  sizeof(aCaseText),
                  "%010llu",
                  static_cast<unsigned long long>(pExplorationCases));
    return std::string("Assets/") + pStem + "_" + aCaseText;
}

bool GenerateControlValueAssets(const std::uint64_t pExplorationCases,
                                std::string *pErrorMessage) {
    const std::string aGrowAFolder =
        ControlValueAssetFolder("grow_a_pre_planned",
                                pExplorationCases);
    const std::string aGrowBFolder =
        ControlValueAssetFolder("grow_b_pre_planned",
                                pExplorationCases);
    const std::string aLaneSplitFolder =
        ControlValueAssetFolder("lane_split_pre_planned",
                                pExplorationCases);
    const std::string aFoldSeedFolder =
        ControlValueAssetFolder("fold_seed_pre_planned",
                                pExplorationCases);
    const std::string aFoldTwistFolder =
        ControlValueAssetFolder("fold_twist_pre_planned",
                                pExplorationCases);

    std::printf("\nGenerating control values with %llu exploration cases...\n",
                static_cast<unsigned long long>(pExplorationCases));

    GrowAControl::Reset();
    for (std::size_t i = 0U;
         i < GrowAControl::kCandidateCount;
         ++i) {
        GrowAControl::Generate(pExplorationCases);
    }
    if (!GrowAControl::SaveValues(aGrowAFolder,
                                  pErrorMessage)) {
        return false;
    }
    GrowAControl::Reset();
    if (!GrowAControl::LoadValues(aGrowAFolder,
                                  pErrorMessage)) {
        return false;
    }

    GrowBControl::Reset();
    for (std::size_t i = 0U;
         i < GrowBControl::kCandidateCount;
         ++i) {
        GrowBControl::Generate(pExplorationCases);
    }
    if (!GrowBControl::SaveValues(aGrowBFolder,
                                  pErrorMessage)) {
        return false;
    }
    GrowBControl::Reset();
    if (!GrowBControl::LoadValues(aGrowBFolder,
                                  pErrorMessage)) {
        return false;
    }

    FoldSeedControl::Reset();
    for (std::size_t i = 0U;
         i < FoldSeedControl::kCandidateCount;
         ++i) {
        FoldSeedControl::Generate(pExplorationCases);
    }
    if (!FoldSeedControl::SaveValues(aFoldSeedFolder,
                                     pErrorMessage)) {
        return false;
    }
    FoldSeedControl::Reset();
    if (!FoldSeedControl::LoadValues(aFoldSeedFolder,
                                     pErrorMessage)) {
        return false;
    }

    FoldTwistControl::Reset();
    for (std::size_t i = 0U;
         i < FoldTwistControl::kCandidateCount;
         ++i) {
        FoldTwistControl::Generate(pExplorationCases);
    }
    if (!FoldTwistControl::SaveValues(aFoldTwistFolder,
                                      pErrorMessage)) {
        return false;
    }
    FoldTwistControl::Reset();
    if (!FoldTwistControl::LoadValues(aFoldTwistFolder,
                                      pErrorMessage)) {
        return false;
    }

    LaneSplitControl::Reset();
    if (!AddKeyBoxLaneSplitGroups(pErrorMessage)) {
        return false;
    }
    for (std::size_t i = 0U;
         i < LaneSplitControl::kCandidateCount;
         ++i) {
        if (LaneSplitControl::Generate(pExplorationCases).empty()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "LaneSplitControl failed to generate candidate " +
                    std::to_string(i + 1U);
            }
            return false;
        }
    }
    if (!LaneSplitControl::SaveValues(aLaneSplitFolder,
                                      pErrorMessage)) {
        return false;
    }

    // Verify that this generated family can be consumed from its files.
    LaneSplitControl::Reset();
    if (!AddKeyBoxLaneSplitGroups(pErrorMessage)) {
        return false;
    }
    if (!LaneSplitControl::LoadValues(aLaneSplitFolder,
                                      pErrorMessage)) {
        return false;
    }

    std::printf("Saved:\n"
                "    %s\n"
                "    %s\n"
                "    %s\n"
                "    %s\n"
                "    %s\n",
                aGrowAFolder.c_str(),
                aGrowBFolder.c_str(),
                aFoldSeedFolder.c_str(),
                aFoldTwistFolder.c_str(),
                aLaneSplitFolder.c_str());
    return true;
}

int RunControlValueExporter() {
    std::uint64_t aExplorationCases = 100ULL;
    for (;;) {
        std::string aError;
        if (!GenerateControlValueAssets(aExplorationCases, &aError)) {
            std::printf("Control value generation failed at %llu cases:\n%s\n",
                        static_cast<unsigned long long>(aExplorationCases),
                        aError.c_str());
            return 1;
        }

        if (aExplorationCases >
            (std::numeric_limits<std::uint64_t>::max() / 5ULL)) {
            std::printf("Control value generation reached the largest "
                        "safe exploration count.\n");
            return 0;
        }
        aExplorationCases *= 5ULL;
    }
}

}

extern "C" int MeanMachineRunExporter(void) {
    return RunControlValueExporter();
}

@interface AppDelegate ()

@property (strong) IBOutlet NSWindow *window;
@end

@implementation AppDelegate


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    (void)aNotification;
    
    printf("App is awake and running...\n");
    
    /*
    if (IsRunningUnderXCTest()) {
        printf("skipping app, xc test...\n");
        return;
    }
    */
    
    
    {
        printf("exporting 1 test expander...\n");
        std::string aError;
        gCandidateIndex = 0;
        if (!Builder::Go("CornTesting/Gen",
                         "Achernar",
                         &aError)) {
            std::printf("Builder::Go failed for %s:\n%s\n",
                        "Achernar",
                        aError.c_str());
        }
        ++gCandidateIndex;
        return;
    }
    
    
    //Scanner_MagicNumbers::Check();
    //return;
    
    /*
    if (MeanMachineRunExporter() != 0) {
        return;
    }
    printf("Done with export block...\n");
    
    return;
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
        
        gCandidateIndex = 0;
        for (auto aName: aNames) {
            if (!Builder::Go("CornTesting/Gen",
                             aName,
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
    printf("Done with optimal combinations...\n");
    
    
    
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

                std::array<std::uint8_t, S_BLOCK> aSnowSource{};
                std::array<std::uint8_t, S_BLOCK> aSnowLaneA{};
                std::array<std::uint8_t, S_BLOCK> aSnowLaneB{};
                std::array<std::uint8_t, S_BLOCK> aSnowLaneC{};
                std::array<std::uint8_t, S_BLOCK> aSnowLaneD{};
                TwistExpander::UnrollPasswordToSource(aSnowSource.data(),
                                                      aPassword,
                                                      3U);
                TwistSnow::BuildLanes(aSnowSource.data(),
                                      aSnowLaneA.data(),
                                      aSnowLaneB.data(),
                                      aSnowLaneC.data(),
                                      aSnowLaneD.data());
                
                const std::vector<std::uint64_t> aNonces = GenerateUniqueNonces(5U);
                
                DirtyWorkSpace::Scramble(&aWorkSpaceA, &aExpanderA);
                DirtyWorkSpace::Scramble(&aWorkSpaceB, &aExpanderB);
                DirtyWorkSpace::Scramble(&aWorkSpaceC, nullptr);
                
                Rig aRigA;
                Rig aRigB;
                Rig aRigC;
                
                std::string aErrorMessage;
                if (!RunRigWithWorkSpace(&aExpanderA, &aWorkSpaceA, &aRigA, aNonces, aPassword, 3,
                                         aSnowLaneA.data(), aSnowLaneB.data(),
                                         aSnowLaneC.data(), aSnowLaneD.data(),
                                         &aErrorMessage)) {
                    printf("rig A failed for %c%c%c: %s\n", aPassword[0], aPassword[1], aPassword[2], aErrorMessage.c_str());
                    return;
                }
                if (!RunRigWithWorkSpace(&aExpanderB, &aWorkSpaceB, &aRigB, aNonces, aPassword, 3,
                                         aSnowLaneA.data(), aSnowLaneB.data(),
                                         aSnowLaneC.data(), aSnowLaneD.data(),
                                         &aErrorMessage)) {
                    printf("rig B failed for %c%c%c: %s\n", aPassword[0], aPassword[1], aPassword[2], aErrorMessage.c_str());
                    return;
                }
                
                if (!CompareWorkSpace::CompareBlocks(aRigA.mData, aRigB.mData, 32U, &aErrorMessage)) {
                    printf("A/B destination compare failed for %c%c%c: %s\n", aPassword[0], aPassword[1], aPassword[2], aErrorMessage.c_str());
                    return;
                }
                
                if (!RunRigWithWorkSpace(&aExpanderA, &aWorkSpaceC, &aRigC, aNonces, aPassword, 3,
                                         aSnowLaneA.data(), aSnowLaneB.data(),
                                         aSnowLaneC.data(), aSnowLaneD.data(),
                                         &aErrorMessage)) {
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
        aDiffusionA.mInputA = BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA);
        aDiffusionA.mInputB = BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA);
        aDiffusionA.mInputC = BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA);
        aDiffusionA.mInputD = BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA);
        aDiffusionA.mOutputA = BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA);
        aDiffusionA.mOutputB = BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA);
        aDiffusionA.mOutputC = BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA);
        aDiffusionA.mOutputD = BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA);
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
