//
//  Builder_KDF.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_KDF.hpp"

#include <array>
#include <string>
#include <vector>

#include "TwistWorkSpace.hpp"
#include "GTwistExpander.hpp"
#include "GSeedRunKDF_A.hpp"
#include "GSeedRunKDF_B.hpp"
#include "GSeedRunKDF_C.hpp"
#include "GSeedRunKDF_D.hpp"
#include "ResidualBucket.hpp"

#include "GRunMatrixDiffusion.hpp"
namespace {

template <typename Runner>
bool BuildKDFStage(TwistProgramBranch &pBranch,
                   const GSeedRunStageConfig &pConfig,
                   const bool pEmitPrologue,
                   const char *pStageName,
                   const char *pBranchName,
                   std::string *pErrorMessage) {
    Runner aRunner(pConfig, pEmitPrologue);
    if (!aRunner.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on ") + pStageName + ".Plan for " +
                pBranchName + "\n" + *pErrorMessage;
        }
        return false;
    }

    if (!aRunner.Build(pBranch, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on ") + pStageName + ".Build for " +
                pBranchName + "\n" + *pErrorMessage;
        }
        return false;
    }

    return true;
}

bool BuildMatrixDiffusionFromPreviousSix(
    TwistProgramBranch &pBranch,
    const std::string &pBranchName,
    const std::vector<GSymbol> &pFuseLanes,
    const std::vector<GSymbol> &pDiffusionOutputLanes,
    const std::vector<GSymbol> &pPreviousSixLanes,
    std::string *pErrorMessage) {
    if ((pFuseLanes.size() != 4U) ||
        (pDiffusionOutputLanes.size() != 4U) ||
        (pPreviousSixLanes.size() != 6U)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                pBranchName +
                " matrix diffusion did not receive four Fuse lanes, "
                "four output lanes, and six preceding lanes";
        }
        return false;
    }

    GRunMatrixDiffusionConfig aDiffusion;
    aDiffusion.mInputA = pFuseLanes[0];
    aDiffusion.mInputB = pFuseLanes[1];
    aDiffusion.mInputC = pFuseLanes[2];
    aDiffusion.mInputD = pFuseLanes[3];
    aDiffusion.mOutputA = pDiffusionOutputLanes[0];
    aDiffusion.mOutputB = pDiffusionOutputLanes[1];
    aDiffusion.mOutputC = pDiffusionOutputLanes[2];
    aDiffusion.mOutputD = pDiffusionOutputLanes[3];

    // Previous six:
    //   [shuffle, shuffle, operation, operation, shuffle, shuffle]
    aDiffusion.mShuffleEntropyA = pPreviousSixLanes[0];
    aDiffusion.mShuffleEntropyB = pPreviousSixLanes[1];
    aDiffusion.mShuffleEntropyC = pPreviousSixLanes[4];
    aDiffusion.mShuffleEntropyD = pPreviousSixLanes[5];
    aDiffusion.mOperationSourceA = pPreviousSixLanes[2];
    aDiffusion.mOperationSourceB = pPreviousSixLanes[3];

    GBatch aBatchDiffusion;
    aBatchDiffusion.mName = pBranchName + "-matrix-diffusion";
    if (!GRunMatrixDiffusion::Bake(aDiffusion,
                                   &aBatchDiffusion,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "error on matrix diffusion for " +
                pBranchName + ": " + *pErrorMessage;
        }
        return false;
    }
    pBranch.AddBatch(aBatchDiffusion);

    return true;
}

template <typename Runner>
bool BuildKDFStyleBranch(TwistProgramBranch &pBranch,
                         const std::array<GSeedRunStageConfig, 4> &pConfigs,
                         const char pKDFLetter,
                         const std::vector<GSymbol> &pFuseLanes,
                         const std::vector<GSymbol> &pDiffusionOutputLanes,
                         const std::vector<GSymbol> &pPreviousSixLanes,
                         std::string *pErrorMessage) {
    const char aUpperText[] = {pKDFLetter, '\0'};
    const char aLowerText[] = {
        static_cast<char>(pKDFLetter - 'A' + 'a'),
        '\0'
    };
    const std::string aBranchName = std::string("kdf-") + aLowerText;
    const std::string aStagePrefix = std::string("GSeedRunKDF_") + aUpperText + "_";

    if (!BuildKDFStage<Runner>(pBranch,
                                pConfigs[0],
                                true,
                                (aStagePrefix + "A").c_str(),
                                aBranchName.c_str(),
                                pErrorMessage) ||
        !BuildKDFStage<Runner>(pBranch,
                                pConfigs[1],
                                false,
                                (aStagePrefix + "B").c_str(),
                                aBranchName.c_str(),
                                pErrorMessage) ||
        !BuildKDFStage<Runner>(pBranch,
                                pConfigs[2],
                                false,
                                (aStagePrefix + "C").c_str(),
                                aBranchName.c_str(),
                                pErrorMessage)) {
        return false;
    }

    if (!BuildMatrixDiffusionFromPreviousSix(pBranch,
                                             aBranchName,
                                             pFuseLanes,
                                             pDiffusionOutputLanes,
                                             pPreviousSixLanes,
                                             pErrorMessage)) {
        return false;
    }

    if (!BuildKDFStage<Runner>(pBranch,
                                pConfigs[3],
                                false,
                                (aStagePrefix + "D").c_str(),
                                aBranchName.c_str(),
                                pErrorMessage)) {
        return false;
    }

    if (pBranch.GetBatchJsonText().empty() &&
        pBranch.GetStringLines().empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "kdf branch export was empty for " +
                aBranchName + " (no batches and no lines)";
        }
        return false;
    }
    return true;
}

} // namespace

bool Builder_KDF::Build(GTwistExpander *pExpander,
                        std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_KDF::Build received null expander";
        }
        return false;
    }

    std::vector<GSymbol> aFuseLanes;
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneA));
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneB));
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneC));
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneD));

    const std::vector<GSymbol> aFireLanes = {
        BufSymbol(TwistWorkSpaceSlot::kFireLaneA),
        BufSymbol(TwistWorkSpaceSlot::kFireLaneB),
        BufSymbol(TwistWorkSpaceSlot::kFireLaneC),
        BufSymbol(TwistWorkSpaceSlot::kFireLaneD),
    };

    const std::vector<GSymbol> aWaterLanes = {
        BufSymbol(TwistWorkSpaceSlot::kWaterLaneA),
        BufSymbol(TwistWorkSpaceSlot::kWaterLaneB),
        BufSymbol(TwistWorkSpaceSlot::kWaterLaneC),
        BufSymbol(TwistWorkSpaceSlot::kWaterLaneD),
    };

    const std::vector<GSymbol> aWindLanes = {
        BufSymbol(TwistWorkSpaceSlot::kWindLaneA),
        BufSymbol(TwistWorkSpaceSlot::kWindLaneB),
        BufSymbol(TwistWorkSpaceSlot::kWindLaneC),
        BufSymbol(TwistWorkSpaceSlot::kWindLaneD),
    };

    const std::vector<GSymbol> aSoilLanes = {
        BufSymbol(TwistWorkSpaceSlot::kSoilLaneA),
        BufSymbol(TwistWorkSpaceSlot::kSoilLaneB),
        BufSymbol(TwistWorkSpaceSlot::kSoilLaneC),
        BufSymbol(TwistWorkSpaceSlot::kSoilLaneD),
    };

    const std::vector<GSymbol> aLightningLanes = {
        BufSymbol(TwistWorkSpaceSlot::kLightningLaneA),
        BufSymbol(TwistWorkSpaceSlot::kLightningLaneB),
        BufSymbol(TwistWorkSpaceSlot::kLightningLaneC),
        BufSymbol(TwistWorkSpaceSlot::kLightningLaneD),
    };

    const std::vector<GSymbol> aIceLanes = {
        BufSymbol(TwistWorkSpaceSlot::kIceLaneA),
        BufSymbol(TwistWorkSpaceSlot::kIceLaneB),
        BufSymbol(TwistWorkSpaceSlot::kIceLaneC),
        BufSymbol(TwistWorkSpaceSlot::kIceLaneD),
    };

    const std::vector<GSymbol> aMagmaLanes = {
        BufSymbol(TwistWorkSpaceSlot::kMagmaLaneA),
        BufSymbol(TwistWorkSpaceSlot::kMagmaLaneB),
        BufSymbol(TwistWorkSpaceSlot::kMagmaLaneC),
        BufSymbol(TwistWorkSpaceSlot::kMagmaLaneD),
    };

    const std::vector<GSymbol> aPlasmaLanes = {
        BufSymbol(TwistWorkSpaceSlot::kPlasmaLaneA),
        BufSymbol(TwistWorkSpaceSlot::kPlasmaLaneB),
        BufSymbol(TwistWorkSpaceSlot::kPlasmaLaneC),
        BufSymbol(TwistWorkSpaceSlot::kPlasmaLaneD),
    };

    const std::vector<GSymbol> aShadowLanes = {
        BufSymbol(TwistWorkSpaceSlot::kShadowLaneA),
        BufSymbol(TwistWorkSpaceSlot::kShadowLaneB),
        BufSymbol(TwistWorkSpaceSlot::kShadowLaneC),
        BufSymbol(TwistWorkSpaceSlot::kShadowLaneD),
    };

    const std::vector<GSymbol> aAetherLanes = {
        BufSymbol(TwistWorkSpaceSlot::kAetherLaneA),
        BufSymbol(TwistWorkSpaceSlot::kAetherLaneB),
        BufSymbol(TwistWorkSpaceSlot::kAetherLaneC),
        BufSymbol(TwistWorkSpaceSlot::kAetherLaneD),
    };

    const std::vector<GSymbol> aCelestialLanes = {
        BufSymbol(TwistWorkSpaceSlot::kCelestialLaneA),
        BufSymbol(TwistWorkSpaceSlot::kCelestialLaneB),
        BufSymbol(TwistWorkSpaceSlot::kCelestialLaneC),
        BufSymbol(TwistWorkSpaceSlot::kCelestialLaneD),
    };

    const std::vector<GSymbol> aVaporLanes = {
        BufSymbol(TwistWorkSpaceSlot::kVaporLaneA),
        BufSymbol(TwistWorkSpaceSlot::kVaporLaneB),
        BufSymbol(TwistWorkSpaceSlot::kVaporLaneC),
        BufSymbol(TwistWorkSpaceSlot::kVaporLaneD),
    };

    ResidualBucket aResidualBucket;

    const GSeedRunKDF_AConfig::KDFStageConfigs aKDFAConfigs =
        GSeedRunKDF_AConfig::MakeKDF_AConfig(aResidualBucket);

    if (!BuildKDFStage<GSeedRunKDF_A>(pExpander->mKDF_A,
                                       aKDFAConfigs[0],
                                       true,
                                       "GSeedRunKDF_A_A",
                                       "kdf-a",
                                       pErrorMessage)) {
        return false;
    }

    if (!BuildKDFStage<GSeedRunKDF_A>(pExpander->mKDF_A,
                                       aKDFAConfigs[1],
                                       false,
                                       "GSeedRunKDF_A_B",
                                       "kdf-a",
                                       pErrorMessage)) {
        return false;
    }

    if (!BuildKDFStage<GSeedRunKDF_A>(pExpander->mKDF_A,
                                       aKDFAConfigs[2],
                                       false,
                                       "GSeedRunKDF_A_C",
                                       "kdf-a",
                                       pErrorMessage)) {
        return false;
    }

    if (pExpander->mKDF_A.GetBatchJsonText().empty() &&
        pExpander->mKDF_A.GetStringLines().empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("kdf branch export was empty for ") + std::string("kdf-a") + " (no batches and no lines)";
        }
        return false;
    }

    const std::vector<GSymbol> aKDFAPreviousSixLanes = {
        aFireLanes[2], aFireLanes[3],
        aWindLanes[0], aWindLanes[1],
        aWindLanes[2], aWindLanes[3],
    };
    if (!BuildMatrixDiffusionFromPreviousSix(pExpander->mKDF_A,
                                             "kdf-a",
                                             aFuseLanes,
                                             aWaterLanes,
                                             aKDFAPreviousSixLanes,
                                             pErrorMessage)) {
        return false;
    }

    if (!BuildKDFStage<GSeedRunKDF_A>(pExpander->mKDF_A,
                                       aKDFAConfigs[3],
                                       false,
                                       "GSeedRunKDF_A_D",
                                       "kdf-a",
                                       pErrorMessage)) {
        return false;
    }
    const GSeedRunKDF_BConfig::KDFStageConfigs aKDFBConfigs =
        GSeedRunKDF_BConfig::MakeKDF_BConfig(aResidualBucket);
    const std::vector<GSymbol> aKDFBPreviousSixLanes = {
        aSoilLanes[2], aSoilLanes[3],
        aLightningLanes[0], aLightningLanes[1],
        aLightningLanes[2], aLightningLanes[3],
    };
    if (!BuildKDFStyleBranch<GSeedRunKDF_B>(pExpander->mKDF_B,
                                            aKDFBConfigs,
                                            'B',
                                            aFuseLanes,
                                            aIceLanes,
                                            aKDFBPreviousSixLanes,
                                            pErrorMessage)) {
        return false;
    }

    const GSeedRunKDF_CConfig::KDFStageConfigs aKDFCConfigs =
        GSeedRunKDF_CConfig::MakeKDF_CConfig(aResidualBucket);
    const std::vector<GSymbol> aKDFCPreviousSixLanes = {
        aMagmaLanes[2], aMagmaLanes[3],
        aPlasmaLanes[0], aPlasmaLanes[1],
        aPlasmaLanes[2], aPlasmaLanes[3],
    };
    if (!BuildKDFStyleBranch<GSeedRunKDF_C>(pExpander->mKDF_C,
                                            aKDFCConfigs,
                                            'C',
                                            aFuseLanes,
                                            aShadowLanes,
                                            aKDFCPreviousSixLanes,
                                            pErrorMessage)) {
        return false;
    }

    const GSeedRunKDF_DConfig::KDFStageConfigs aKDFDConfigs =
        GSeedRunKDF_DConfig::MakeKDF_DConfig(aResidualBucket);
    const std::vector<GSymbol> aKDFDPreviousSixLanes = {
        aAetherLanes[2], aAetherLanes[3],
        aCelestialLanes[0], aCelestialLanes[1],
        aCelestialLanes[2], aCelestialLanes[3],
    };
    if (!BuildKDFStyleBranch<GSeedRunKDF_D>(pExpander->mKDF_D,
                                            aKDFDConfigs,
                                            'D',
                                            aFuseLanes,
                                            aVaporLanes,
                                            aKDFDPreviousSixLanes,
                                            pErrorMessage)) {
        return false;
    }

    return true;
}
