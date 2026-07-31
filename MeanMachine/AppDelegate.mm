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
#include "Rig.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "GAXSK.hpp"
#include "Builder.hpp"
#include "Avalancher.hpp"

#include "GrowAControl.hpp"
#include "GrowBControl.hpp"
#include "LaneSplitControl.hpp"
#include "SaltTables.hpp"
#include "GMagicNumbers.hpp"

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

// #include "TwistExpander_Achernar.hpp"
 
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
                   TwistWorkSpaceSlot::kCrystalLaneA,
                   TwistWorkSpaceSlot::kCrystalLaneB,
                   TwistWorkSpaceSlot::kCrystalLaneC,
                   TwistWorkSpaceSlot::kCrystalLaneD,
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
                "    %s\n",
                aGrowAFolder.c_str(),
                aGrowBFolder.c_str(),
                aLaneSplitFolder.c_str());
    return true;
}

bool GenerateFoldControlValueAssets(
    const std::uint64_t pExplorationCases,
    const std::string &pGrowAFolder,
    const std::string &pGrowBFolder,
    std::string *pErrorMessage) {
    GrowAControl::Reset();
    for (std::size_t i = 0U;
         i < GrowAControl::kCandidateCount;
         ++i) {
        GrowAControl::Generate(pExplorationCases);
    }
    if (!GrowAControl::SaveValues(pGrowAFolder,
                                  pErrorMessage)) {
        return false;
    }
    GrowAControl::Reset();
    if (!GrowAControl::LoadValues(pGrowAFolder,
                                  pErrorMessage)) {
        return false;
    }

    GrowBControl::Reset();
    for (std::size_t i = 0U;
         i < GrowBControl::kCandidateCount;
         ++i) {
        GrowBControl::Generate(pExplorationCases);
    }
    if (!GrowBControl::SaveValues(pGrowBFolder,
                                  pErrorMessage)) {
        return false;
    }
    GrowBControl::Reset();
    return GrowBControl::LoadValues(pGrowBFolder,
                                    pErrorMessage);
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

extern "C" int MeanMachineBuildTestExpander(void) {
    std::string aError;
    gCandidateIndex = 0;
    if (!Builder::Go("CornTesting/Gen", "Achernar", &aError)) {
        std::printf("Builder::Go failed for Achernar:\n%s\n",
                    aError.c_str());
        return 1;
    }
    return 0;
}

extern "C" int MeanMachineRegenerateFoldControls(void) {
    std::string aError;
    if (!GenerateFoldControlValueAssets(
            100ULL,
            "Assets/grow_a_pre_planned",
            "Assets/grow_b_pre_planned",
            &aError)) {
        std::printf("Fold control generation failed:\n%s\n",
                    aError.c_str());
        return 1;
    }
    std::printf("Regenerated mandatory GrowA and GrowB fold controls.\n");
    return 0;
}

@interface AppDelegate ()

@property (strong) IBOutlet NSWindow *window;
@end

@implementation AppDelegate


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    (void)aNotification;
    
    printf("App is awake and running...\n");
    
    
    if (IsRunningUnderXCTest()) {
        printf("skipping app, xc test...\n");
        return;
    }
    
    /*
    if (MeanMachineRunExporter() != 0) {
        return;
    }
    printf("Done with export block...\n");
    
    return;
    */
     
    
    /*
    {
        std::vector<SaltTables::Salt> aSalts = SaltTables::Get();
        std::vector<GHotPack> aPacks = GMagicNumbers::GetHotPacks(37500);
        std::set<std::uint64_t> aMap;
        int aCompareCount = 0;
        for (auto aSalt : aSalts) {
            for (int i=0;i<512;i++) {
                std::uint64_t aValue = aSalt[i];
                if (aMap.contains(aValue)) {
                    printf("dupe from salt...\n");
                    exit(0);
                }
                aMap.insert(aValue);
                aCompareCount++;
            }
        }
        
        printf("compared all salts, no dupes (%d)\n", aCompareCount);
        
        for (auto aPack : aPacks) {
            for (int i=0;i<G_HOT_PACK_SIZE;i++) {
                GHotPair aPair = aPack.mPair[i];
                std::uint64_t aValueA = aPair.mAdd;
                if (aMap.contains(aValueA)) {
                    printf("dupe from add...\n");
                    exit(0);
                }
                aMap.insert(aValueA);
                aCompareCount++;
                
                std::uint64_t aValueB = aPair.mMul;
                if (aMap.contains(aValueB)) {
                    printf("dupe from mul...\n");
                    exit(0);
                }
                aMap.insert(aValueB);
                aCompareCount++;
            }
        }
        
        printf("compared all pairs, no dupes (%d)\n", aCompareCount);
    }
     */
    
    /*
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

}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    (void)aNotification;
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end
