//
//  Builder.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include <cstdio>

#include "Builder.hpp"

#include "Builder_KDF.hpp"
#include "Builder_Seeder.hpp"
#include "Builder_Twister.hpp"
#include "Builder_GrowA.hpp"
#include "Builder_GrowB.hpp"
#include "GAXSK.hpp"
#include "GPrintTool.hpp"
#include "GTwistExpander.hpp"
#include "ResidualBucket.hpp"
#include "stdafx.hpp"
bool Builder::Go(const std::string &pOutputRoot,
                 const std::string &pFilePrefix,
                 std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    GPrintTool::Reset();
    gLoopIndex = 0;

    GTwistExpander aExpander;
    aExpander.mNameBase = pFilePrefix;
    if (gCandidateIndex < 0) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder received a negative candidate index";
        }
        return false;
    }
    if (static_cast<std::size_t>(gCandidateIndex) >=
        GAXSK::LoopPatternCandidateCount11()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder candidate index exceeded the loaded "
                "loop-pattern assets";
        }
        return false;
    }
    std::string aError;
    if (!GAXSK::LoadLoopPatterns11(&aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder could not load loop patterns:\n" +
                aError;
        }
        return false;
    }
    const std::size_t aExpectedLoopCount =
        GAXSK::LoopPatternCountPerCandidate11();
    std::printf("Loaded loop recipes candidate %d: [0, %zu] "
                "(%zu consumed structures)\n",
                gCandidateIndex,
                aExpectedLoopCount - 1U,
                aExpectedLoopCount);
    aExpander.mControlCandidateIndex =
        static_cast<std::size_t>(gCandidateIndex);

    // All six domain-specific KDF-A through KDF-C chains share one residual
    // schedule.
    ResidualBucket aKDFResidualBucket;
    Builder_KDF aKDFBuilder;
    if (!aKDFBuilder.Build(&aExpander,
                           aKDFResidualBucket,
                           &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_KDF failed:\n" + aError;
        }
        return false;
    }

    // Main Seed and its independent key-row flows own a fresh residual
    // schedule. No KDF usage counts cross this boundary.
    ResidualBucket aSeedResidualBucket;
    Builder_Seeder aSeederBuilder;
    if (!aSeederBuilder.Build(&aExpander,
                              aSeedResidualBucket,
                              &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder failed:\n" + aError;
        }
        return false;
    }

    Builder_Twister aTwisterBuilder;
    if (!aTwisterBuilder.Build(&aExpander,
                               &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister failed:\n" + aError;
        }
        return false;
    }

    // Split Twist's reusable material between two independent KeyRotate
    // domains. Grow A receives the A/C lanes; Grow B receives B/D.
    ResidualBucket aResidualBucketGrowA;
    aResidualBucketGrowA.AddResiduals("Grow A — Initial (1)", {
        TwistWorkSpaceSlot::kEarthLaneA,
        TwistWorkSpaceSlot::kEarthLaneC,
    }, 1U);
    aResidualBucketGrowA.AddResiduals("Grow A — Initial (2)", {
        TwistWorkSpaceSlot::kLunarLaneA,
        TwistWorkSpaceSlot::kLunarLaneC,
    }, 2U);
    aResidualBucketGrowA.AddResiduals("Grow A — Initial (3)", {
        TwistWorkSpaceSlot::kAetherLaneA,
        TwistWorkSpaceSlot::kAetherLaneC,
    }, 3U);

    ResidualBucket aResidualBucketGrowB;
    aResidualBucketGrowB.AddResiduals("Grow B — Initial (1)", {
        TwistWorkSpaceSlot::kEarthLaneB,
        TwistWorkSpaceSlot::kEarthLaneD,
    }, 1U);
    aResidualBucketGrowB.AddResiduals("Grow B — Initial (2)", {
        TwistWorkSpaceSlot::kLunarLaneB,
        TwistWorkSpaceSlot::kLunarLaneD,
    }, 2U);
    aResidualBucketGrowB.AddResiduals("Grow B — Initial (3)", {
        TwistWorkSpaceSlot::kAetherLaneB,
        TwistWorkSpaceSlot::kAetherLaneD,
    }, 3U);

    Builder_GrowA aGrowABuilder;
    if (!aGrowABuilder.Build(&aExpander,
                             aResidualBucketGrowA,
                            &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowA failed:\n" + aError;
        }
        return false;
    }

    Builder_GrowB aGrowBBuilder;
    if (!aGrowBBuilder.Build(&aExpander,
                             aResidualBucketGrowB,
                            &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowB failed:\n" + aError;
        }
        return false;
    }

    if (static_cast<std::size_t>(gLoopIndex) != aExpectedLoopCount) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder planning consumed " +
                std::to_string(gLoopIndex) +
                " loop patterns; expected " +
                std::to_string(aExpectedLoopCount);
        }
        return false;
    }

    // Planning builds every loop once. The exporter bakes those same stage
    // configs again, so restart at the first structure for the final product.
    gLoopIndex = 0;

    if (!aExpander.ExportCPPProjectRoot(pOutputRoot, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "ExportCPPProjectRoot failed:\n" + aError;
        }
        return false;
    }

    if (static_cast<std::size_t>(gLoopIndex) != aExpectedLoopCount) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder export consumed " +
                std::to_string(gLoopIndex) +
                " loop patterns; expected " +
                std::to_string(aExpectedLoopCount);
        }
        return false;
    }

    return true;
}
