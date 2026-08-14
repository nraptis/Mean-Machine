//
//  AppDelegate.m
//  MeanMachine
//
//  Created by John Snow on 4/20/26.
//

// 17 expanders × 656 loops = 11,152 loops

#import "AppDelegate.h"

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "Builder.hpp"
#include "GMagicNumbers.hpp"

#include "KeyForkControl.hpp"
#include "KeyLaneControl.hpp"
#include "LoopRolePermutations.hpp"
#include "ResidualKDFControl.hpp"

int gCandidateIndex = 0;
int gLoopIndex = 0;

namespace {

bool IsRunningUnderXCTest() {
    return (std::getenv("XCTestConfigurationFilePath") != nullptr) ||
    (std::getenv("XCTestBundlePath") != nullptr);
}

const std::array<const char *, 17> &ExpanderNames() {
    static const std::array<const char *, 17> kNames = {{
        "Aldebaran",
        "Altair", "Antares", "Arcturus",
        "Bellatrix", "Capella",
        "Castor", "Mimosa",
        "Polaris", "Pollux",
        "Procyon", "Regulus", "Rigel", "Saiph",
        "Sirius", "Vega", "Betelgeuse"
    }};
    return kNames;
}

bool PrintMutableParameterAdditions() {
    static constexpr std::array<const char *, 13U> kStateNames = {{
        "Ingress", "Carry",
        "WandererA", "WandererB", "WandererC", "WandererD",
        "WandererE", "WandererF", "WandererG", "WandererH",
        "WandererI", "WandererJ", "WandererK",
    }};
    static constexpr std::size_t kSetCount = 3U;
    static constexpr std::size_t kRequiredWordCount =
        kStateNames.size() * kSetCount;
    static constexpr std::size_t kWordsPerHotPair = 2U;
    static_assert(
        kRequiredWordCount <= (G_HOT_PACK_SIZE * kWordsPerHotPair),
        "One HotPack must contain three mutable-parameter sets");

    const std::vector<GHotPack> aHotPacks =
        GMagicNumbers::GetHotPacks(1);
    if (aHotPacks.empty()) {
        std::printf(
            "Could not load a HotPack for mutable-parameter additions.\n");
        return false;
    }
    const GHotPack &aHotPack = aHotPacks.front();

    std::printf("\n");
    for (std::size_t aSetIndex = 0U;
         aSetIndex < kSetCount;
         ++aSetIndex) {
        for (std::size_t aStateIndex = 0U;
             aStateIndex < kStateNames.size();
             ++aStateIndex) {
            const std::size_t aWordIndex =
                (aSetIndex * kStateNames.size()) + aStateIndex;
            const GHotPair &aPair =
                aHotPack.mPair[aWordIndex / kWordsPerHotPair];
            const std::uint64_t aWord =
                ((aWordIndex & 1U) == 0U) ? aPair.mAdd : aPair.mMul;
            const char *aStateName = kStateNames[aStateIndex];
            std::printf(
                "std::uint64_t a%s = 0x%016llXULL;\n",
                aStateName,
                static_cast<unsigned long long>(aWord));
        }
        if (aSetIndex + 1U < kSetCount) {
            std::printf("\n");
        }
    }
    return true;
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

bool GenerateKeyForkControlValueAssets(
    const std::uint64_t pExplorationCases,
    const std::string &pFolder,
    std::string *pErrorMessage) {
    KeyForkControl::Reset();
    for (std::size_t i = 0U;
         i < KeyForkControl::kCandidateCount;
         ++i) {
        const std::string aSummary =
            KeyForkControl::Generate(pExplorationCases);
        if (aSummary.empty()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "KeyForkControl failed to generate candidate " +
                    std::to_string(i + 1U);
            }
            return false;
        }
        std::printf("%s\n", aSummary.c_str());
    }
    if (!KeyForkControl::SaveValues(pFolder,
                                    pErrorMessage)) {
        return false;
    }

    KeyForkControl::Reset();
    return KeyForkControl::LoadValues(pFolder,
                                      pErrorMessage);
}

bool GenerateKeyLaneControlValueAssets(
    const std::uint64_t pExplorationCases,
    const std::string &pFolder,
    std::string *pErrorMessage) {
    KeyLaneControl::Reset();
    const std::string aSummary =
        KeyLaneControl::Generate(pExplorationCases);
    if (aSummary.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "KeyLaneControl failed to generate its assignment table";
        }
        return false;
    }
    std::printf("%s\n", aSummary.c_str());
    if (!KeyLaneControl::SaveValues(pFolder,
                                    pErrorMessage)) {
        return false;
    }

    // Verify the exact binary values before making them the frozen source.
    KeyLaneControl::Reset();
    if (!KeyLaneControl::LoadValues(pFolder,
                                    pErrorMessage)) {
        return false;
    }
    return KeyLaneControl::WriteAssignmentsHeader(
        "MeanMachine/KeyLaneAssignments.hpp",
        pErrorMessage
    );
}

bool GenerateResidualKDFControlValueAssets(
    const std::uint64_t pExplorationCases,
    const std::string &pFolder,
    std::string *pErrorMessage) {
    ResidualKDFControl::Reset();
    for (std::size_t i = 0U;
         i < ResidualKDFControl::kCandidateCount;
         ++i) {
        const std::string aSummary =
            ResidualKDFControl::Generate(pExplorationCases);
        if (aSummary.empty()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "ResidualKDFControl failed to generate candidate " +
                    std::to_string(i + 1U);
            }
            return false;
        }
        std::printf("%s\n", aSummary.c_str());
    }
    if (!ResidualKDFControl::SaveValues(pFolder,
                                        pErrorMessage)) {
        return false;
    }

    ResidualKDFControl::Reset();
    return ResidualKDFControl::LoadValues(pFolder,
                                          pErrorMessage);
}

bool GenerateControlValueAssets(const std::uint64_t pExplorationCases,
                                std::string *pErrorMessage) {
    const std::string aKeyForkFolder =
        ControlValueAssetFolder("key_fork_pre_planned",
                                pExplorationCases);
    const std::string aKeyLaneFolder =
        ControlValueAssetFolder("key_lane_pre_planned",
                                pExplorationCases);
    const std::string aResidualKDFFolder =
        ControlValueAssetFolder("residual_kdf_pre_planned",
                                pExplorationCases);
    std::printf("\nGenerating control values with %llu exploration cases...\n",
                static_cast<unsigned long long>(pExplorationCases));

    if (!GenerateKeyForkControlValueAssets(pExplorationCases,
                                           aKeyForkFolder,
                                           pErrorMessage)) {
        return false;
    }

    if (!GenerateKeyLaneControlValueAssets(pExplorationCases,
                                           aKeyLaneFolder,
                                           pErrorMessage)) {
        return false;
    }

    if (!GenerateResidualKDFControlValueAssets(pExplorationCases,
                                               aResidualKDFFolder,
                                               pErrorMessage)) {
        return false;
    }

    std::printf("Saved:\n"
                "    %s\n"
                "    %s\n"
                "    %s\n",
                aKeyForkFolder.c_str(),
                aKeyLaneFolder.c_str(),
                aResidualKDFFolder.c_str());
    return true;
}

int RunControlValueExporter() {
    static constexpr std::array<std::uint64_t, 20U> kExplorationCases = {
        1000ULL, 2500ULL, 5000ULL,
        10000ULL, 25000ULL, 50000ULL,
        100000ULL, 250000ULL, 500000ULL,
        1000000ULL, 2500000ULL, 5000000ULL,
        10000000ULL, 25000000ULL, 50000000ULL,
        100000000ULL, 200000000ULL, 300000000ULL,
        400000000ULL, 500000000ULL,
    };

    for (const std::uint64_t aExplorationCases : kExplorationCases) {
        std::string aError;
        if (!GenerateControlValueAssets(aExplorationCases, &aError)) {
            std::printf("Control value generation failed at %llu cases:\n%s\n",
                        static_cast<unsigned long long>(aExplorationCases),
                        aError.c_str());
            return 1;
        }
    }

    return 0;
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

extern "C" int MeanMachineBuildExpanderRange(int pStartIndex,
                                               int pCount);

extern "C" int MeanMachineBuildAllExpanders(void) {
    return MeanMachineBuildExpanderRange(
        0, static_cast<int>(ExpanderNames().size()));
}

extern "C" int MeanMachineBuildExpanderRange(const int pStartIndex,
                                               const int pCount) {
    if (!PrintMutableParameterAdditions()) {
        return 1;
    }

    if ((pStartIndex < 0) || (pCount < 0) ||
        (pStartIndex > static_cast<int>(ExpanderNames().size())) ||
        (pCount > (static_cast<int>(ExpanderNames().size()) - pStartIndex))) {
        std::printf("invalid expander range: start=%d count=%d\n",
                    pStartIndex,
                    pCount);
        return 1;
    }

    std::string aError;
    gCandidateIndex = pStartIndex;
    const int aEndIndex = pStartIndex + pCount;
    for (; gCandidateIndex < aEndIndex; ++gCandidateIndex) {
        const char *aName = ExpanderNames()[
            static_cast<std::size_t>(gCandidateIndex)];
        std::printf("exporting candidate %d: %s\n",
                    gCandidateIndex,
                    aName);
        if (!Builder::Go("CornTesting/Gen", aName, &aError)) {
            std::printf("Builder::Go failed for %s:\n%s\n",
                        aName,
                        aError.c_str());
            return 1;
        }
    }
    return 0;
}

extern "C" int MeanMachineRegenerateKeyForkControl(
    const std::uint64_t pExplorationCases) {
    std::string aError;
    if (!GenerateKeyForkControlValueAssets(
            pExplorationCases,
            "Assets/key_fork_pre_planned",
            &aError)) {
        std::printf("Key-fork control generation failed:\n%s\n",
                    aError.c_str());
        return 1;
    }
    std::printf("Regenerated mandatory KeyFork control with %llu cases.\n",
                static_cast<unsigned long long>(pExplorationCases));
    return 0;
}

extern "C" int MeanMachineRegenerateKeyLaneControl(
    const std::uint64_t pExplorationCases) {
    std::string aError;
    if (!GenerateKeyLaneControlValueAssets(
            pExplorationCases,
            "Assets/key_lane_pre_planned",
            &aError)) {
        std::printf("Key-lane control generation failed:\n%s\n",
                    aError.c_str());
        return 1;
    }
    std::printf(
        "Regenerated mandatory KeyLane assignment table with %llu cases "
        "per family.\n",
        static_cast<unsigned long long>(pExplorationCases));
    return 0;
}

extern "C" int MeanMachineRegenerateResidualKDFControl(
    const std::uint64_t pExplorationCases) {
    std::string aError;
    if (!GenerateResidualKDFControlValueAssets(
            pExplorationCases,
            "Assets/residual_kdf_pre_planned",
            &aError)) {
        std::printf("Residual KDF control generation failed:\n%s\n",
                    aError.c_str());
        return 1;
    }
    std::printf(
        "Regenerated mandatory ResidualKDF control with %llu trials "
        "per candidate.\n",
        static_cast<unsigned long long>(pExplorationCases));
    return 0;
}

extern "C" int MeanMachineGenerateLoopRolePermutations(void) {
    std::string aError;
    if (!LoopRolePermutations::Generate("Assets/permutations", &aError)) {
        std::printf("Loop-role permutation generation failed:\n%s\n",
                    aError.c_str());
        return 1;
    }
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

    //MeanMachineRunExporter();

    //MeanMachineRegenerateKeyLaneControl(1000ULL);

    //MeanMachineRegenerateResidualKDFControl(1000ULL);

    //MeanMachineGenerateLoopRolePermutations();

    MeanMachineBuildAllExpanders();

    //MeanMachineBuildExpanderRange(0, 1);
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    (void)aNotification;
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end
