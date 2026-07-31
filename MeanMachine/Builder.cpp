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
#include "GPrintTool.hpp"
#include "GTwistExpander.hpp"
#include "ResidualBucket.hpp"
#include "Random.hpp"
#include "stdafx.hpp"
bool Builder::Go(const std::string &pOutputRoot,
                 const std::string &pFilePrefix,
                 std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    GPrintTool::Reset();

    GTwistExpander aExpander;
    aExpander.mNameBase = pFilePrefix;
    if (gCandidateIndex < 0) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder received a negative candidate index";
        }
        return false;
    }
    aExpander.mControlCandidateIndex =
        static_cast<std::size_t>(gCandidateIndex);
    std::string aError;

    Builder_KDF aKDFBuilder;
    if (!aKDFBuilder.Build(&aExpander, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_KDF failed:\n" + aError;
        }
        return false;
    }

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

    ResidualBucket aTwistResidualBucket;
    Builder_Twister aTwisterBuilder;
    if (!aTwisterBuilder.Build(&aExpander,
                               aTwistResidualBucket,
                               &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister failed:\n" + aError;
        }
        return false;
    }

    using Slot = TwistWorkSpaceSlot;
    
    std::vector<Slot> aPool0 = {
        Slot::kMagmaLaneA, Slot::kMagmaLaneB, Slot::kMagmaLaneC, Slot::kMagmaLaneD,
        Slot::kPlasmaLaneC, Slot::kPlasmaLaneD };
    Random::Shuffle(&aPool0);

    std::vector<Slot> aPool1 = {
        Slot::kWoodLaneA, Slot::kWoodLaneB, Slot::kWoodLaneC, Slot::kWoodLaneD,
        Slot::kPlasmaLaneA, Slot::kPlasmaLaneB };
    Random::Shuffle(&aPool1);

    std::vector<Slot> aPool2 = {
        Slot::kIceLaneA, Slot::kIceLaneB, Slot::kIceLaneC, Slot::kIceLaneD,
        Slot::kLightningLaneA, Slot::kLightningLaneB, Slot::kLightningLaneC, Slot::kLightningLaneD };
    Random::Shuffle(&aPool2);

    std::vector<Slot> aPool3 = {
        Slot::kWaterLaneA, Slot::kWaterLaneB, Slot::kWaterLaneC, Slot::kWaterLaneD, // 4
        Slot::kHeartLaneA, Slot::kHeartLaneB, Slot::kHeartLaneC, Slot::kHeartLaneD, // 8
        Slot::kEarthLaneA, Slot::kEarthLaneB, Slot::kEarthLaneC, Slot::kEarthLaneD, // 12
        Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD, // 16
        Slot::kSoilLaneA, Slot::kSoilLaneB, Slot::kSoilLaneC, Slot::kSoilLaneD }; // 20
    Random::Shuffle(&aPool3);
    
    ResidualBucket aResidualBucketGrowA;
    ResidualBucket aResidualBucketGrowB;
    
    
    aResidualBucketGrowA.AddResiduals("Estimate-Grow-A (0)", { aPool0[0], aPool0[2], aPool0[4] }, 0);
    aResidualBucketGrowB.AddResiduals("Estimate-Grow-B (0)", { aPool0[1], aPool0[3], aPool0[5] }, 0);

    aResidualBucketGrowA.AddResiduals("Estimate-Grow-A (1)", { aPool1[0], aPool1[2], aPool1[4] }, 1);
    aResidualBucketGrowB.AddResiduals("Estimate-Grow-B (1)", { aPool1[1], aPool1[3], aPool1[5] }, 1);
    
    aResidualBucketGrowA.AddResiduals("Estimate-Grow-A (2)", {
        aPool2[0], aPool2[2],
        aPool2[4], aPool2[6]}, 2);
    aResidualBucketGrowB.AddResiduals("Estimate-Grow-B (2)", {
        aPool2[1], aPool2[3],
        aPool2[5], aPool2[7]}, 2);
    
    aResidualBucketGrowA.AddResiduals("Estimate-Grow-A (3)", {
        aPool3[ 0], aPool3[ 2], aPool3[ 4], aPool3[ 6],
        aPool3[ 8], aPool3[10], aPool3[12], aPool3[14],
        aPool3[16], aPool3[18]}, 3);
    
    aResidualBucketGrowB.AddResiduals("Estimate-Grow-B (3)", {
        aPool3[ 1], aPool3[ 3], aPool3[ 5], aPool3[ 7],
        aPool3[ 9], aPool3[11], aPool3[13], aPool3[15],
        aPool3[17], aPool3[19]}, 3);
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

    if (!aExpander.ExportCPPProjectRoot(pOutputRoot, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "ExportCPPProjectRoot failed:\n" + aError;
        }
        return false;
    }

    return true;
}
