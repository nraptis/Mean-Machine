//
//  Builder_Twister.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Twister.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunTwist.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "ResidualBucket.hpp"

#include <vector>

namespace {

const char *PhaseConstantsMemberName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kKeyRotateA: return "mKeyRotateAConstants";
        case TwistDomain::kKeyRotateB: return "mKeyRotateBConstants";
        case TwistDomain::kKeySpawnA: return "mKeySpawnAConstants";
        case TwistDomain::kKeySpawnB: return "mKeySpawnBConstants";
        case TwistDomain::kSeed: return "mSeedConstants";
        case TwistDomain::kTwist: return "mTwistConstants";
        default:
            return "";
    }
}

void AddTwistMatrixDomainWordLines(TwistProgramBranch &pBranch,
                                   const TwistDomain pDomain) {
    const std::string aConstants =
        std::string("pWorkSpace->mDomainBundle.") +
        PhaseConstantsMemberName(pDomain);

    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectA = " + aConstants + ".mMatrixSelectA;");
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectB = " + aConstants + ".mMatrixSelectB;");
    pBranch.AddLine("");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollA = " + aConstants + ".mMatrixUnrollA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollB = " + aConstants + ".mMatrixUnrollB;");
    pBranch.AddLine("");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgA = " + aConstants + ".mMatrixArgA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgB = " + aConstants + ".mMatrixArgB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgC = " + aConstants + ".mMatrixArgC;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgD = " + aConstants + ".mMatrixArgD;");
}

bool BuildTwistStage(TwistProgramBranch &pBranch,
                     const GSeedRunStageConfig &pConfig,
                     const bool pEmitPrologue,
                     const char *pStageName,
                     std::string *pErrorMessage) {
    GTwistRunTwist aRunner(pConfig, pEmitPrologue);
    if (!aRunner.Plan(pErrorMessage) ||
        !aRunner.Build(pBranch, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                std::string("Builder_Twister::Build failed on ") +
                pStageName + ":\n" + *pErrorMessage;
        }
        return false;
    }
    return true;
}

} // namespace

bool Builder_Twister::Build(GTwistExpander *pExpander,
                            ResidualBucket &pResidualBucket,
                            std::string *pErrorMessage) {

    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build received null expander";
        }
        return false;
    }

    const GTwistRunTwistConfig::TwistStageConfigs aBuiltStageConfigs =
        GTwistRunTwistConfig::MakeTwistConfig(
            pResidualBucket,
            pExpander->mControlCandidateIndex);
    std::vector<GSeedRunStageConfig> aStageConfigs(
        aBuiltStageConfigs.begin(),
        aBuiltStageConfigs.end());

    pExpander->mTwistStageConfigs = aStageConfigs;
    pExpander->mTwistMatrixDomains.assign(2U, TwistDomain::kTwist);

    pExpander->mTwister.AddLine("// [twist]");

    std::vector<GSymbol> aHeartLanes;
    aHeartLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kHeartLaneA));
    aHeartLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kHeartLaneB));
    aHeartLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kHeartLaneC));
    aHeartLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kHeartLaneD));

    std::vector<GSymbol> aFuseLanes;
    aFuseLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneA));
    aFuseLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneB));
    aFuseLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneC));
    aFuseLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneD));

    std::vector<GSymbol> aFireLanes;
    aFireLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFireLaneA));
    aFireLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFireLaneB));
    aFireLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFireLaneC));
    aFireLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kFireLaneD));

    std::vector<GSymbol> aWaterLanes;
    aWaterLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWaterLaneA));
    aWaterLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWaterLaneB));
    aWaterLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWaterLaneC));
    aWaterLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWaterLaneD));


    std::vector<GSymbol> aLightningLanes;
    aLightningLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kLightningLaneA));
    aLightningLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kLightningLaneB));
    aLightningLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kLightningLaneC));
    aLightningLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kLightningLaneD));

    std::vector<GSymbol> aIceLanes;
    aIceLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kIceLaneA));
    aIceLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kIceLaneB));
    aIceLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kIceLaneC));
    aIceLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kIceLaneD));

    std::vector<GSymbol> aWoodLanes;
    aWoodLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWoodLaneA));
    aWoodLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWoodLaneB));
    aWoodLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWoodLaneC));
    aWoodLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kWoodLaneD));

    for (std::size_t i = 0U; i < 3U; ++i) {
        const std::string aStageName =
            "GTwistRunTwist_" + std::string(1, static_cast<char>('A' + i));
        if (!BuildTwistStage(pExpander->mTwister,
                             aStageConfigs[i],
                             i == 0U,
                             aStageName.c_str(),
                             pErrorMessage)) {
            return false;
        }
    }

    pExpander->mTwister.AddLine("//");

    AddTwistMatrixDomainWordLines(pExpander->mTwister,
                                  TwistDomain::kTwist);

    GRunMatrixDiffusionConfig aDiffusionA;
    aDiffusionA.mInputA = aFuseLanes[0];
    aDiffusionA.mInputB = aFuseLanes[1];
    aDiffusionA.mInputC = aFuseLanes[2];
    aDiffusionA.mInputD = aFuseLanes[3];
    aDiffusionA.mOutputA = aHeartLanes[0];
    aDiffusionA.mOutputB = aHeartLanes[1];
    aDiffusionA.mOutputC = aHeartLanes[2];
    aDiffusionA.mOutputD = aHeartLanes[3];

    // Previous six:
    //   Fire C, Fire D, Water A, Water B, Water C, Water D
    aDiffusionA.mShuffleEntropyA = aFireLanes[2];
    aDiffusionA.mShuffleEntropyB = aFireLanes[3];
    aDiffusionA.mShuffleEntropyC = aWaterLanes[2];
    aDiffusionA.mShuffleEntropyD = aWaterLanes[3];
    aDiffusionA.mOperationSourceA = aWaterLanes[0];
    aDiffusionA.mOperationSourceB = aWaterLanes[1];

    GBatch aBatchDiffusionA;
    aBatchDiffusionA.mExportsAsBlock = false;

    if (!GRunMatrixDiffusion::Bake(aDiffusionA,
                                   &aBatchDiffusionA,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on matrix diffusion for twist: ") + *pErrorMessage;
        }
        return false;
    }
    pExpander->mTwister.AddBatch(aBatchDiffusionA);

    pExpander->mTwister.AddLine("//");

    for (std::size_t i = 3U; i < 6U; ++i) {
        const std::string aStageName =
            "GTwistRunTwist_" + std::string(1, static_cast<char>('A' + i));
        if (!BuildTwistStage(pExpander->mTwister,
                             aStageConfigs[i],
                             false,
                             aStageName.c_str(),
                             pErrorMessage)) {
            return false;
        }
    }

    GRunMatrixDiffusionConfig aDiffusionB;
    aDiffusionB.mInputA = aFuseLanes[0];
    aDiffusionB.mInputB = aFuseLanes[1];
    aDiffusionB.mInputC = aFuseLanes[2];
    aDiffusionB.mInputD = aFuseLanes[3];
    aDiffusionB.mOutputA = aWoodLanes[0];
    aDiffusionB.mOutputB = aWoodLanes[1];
    aDiffusionB.mOutputC = aWoodLanes[2];
    aDiffusionB.mOutputD = aWoodLanes[3];
    // Previous six:
    //   Lightning C, Lightning D, Ice A, Ice B, Ice C, Ice D
    aDiffusionB.mShuffleEntropyA = aLightningLanes[2];
    aDiffusionB.mShuffleEntropyB = aLightningLanes[3];
    aDiffusionB.mShuffleEntropyC = aIceLanes[2];
    aDiffusionB.mShuffleEntropyD = aIceLanes[3];
    aDiffusionB.mOperationSourceA = aIceLanes[0];
    aDiffusionB.mOperationSourceB = aIceLanes[1];

    GBatch aBatchDiffusionB;
    aBatchDiffusionB.mExportsAsBlock = false;
    if (!GRunMatrixDiffusion::Bake(aDiffusionB,
                                   &aBatchDiffusionB,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                std::string("error on second matrix diffusion for twist: ") +
                *pErrorMessage;
        }
        return false;
    }
    pExpander->mTwister.AddBatch(aBatchDiffusionB);

    pExpander->mTwister.AddLine("//");

    for (std::size_t i = 6U; i < 8U; ++i) {
        const std::string aStageName =
            "GTwistRunTwist_" + std::string(1, static_cast<char>('A' + i));
        if (!BuildTwistStage(pExpander->mTwister,
                             aStageConfigs[i],
                             false,
                             aStageName.c_str(),
                             pErrorMessage)) {
            return false;
        }
    }

    return true;

}
