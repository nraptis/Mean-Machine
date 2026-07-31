//
//  Builder_GrowA.cpp
//  MeanMachine
//
//  Created by icarus black on 7/13/26.
//

#include "Builder_GrowA.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunGrowKeyA.hpp"
#include "ResidualBucket.hpp"

#include <string>
#include <vector>

namespace {

void AddGrowAMatrixDomainWordLines(TwistProgramBranch &pBranch) {
    const std::string aConstants =
        "pWorkSpace->mDomainBundle.mKeyRotateAConstants";
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectA = " + aConstants + ".mMatrixSelectA;");
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectB = " + aConstants + ".mMatrixSelectB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollA = " + aConstants + ".mMatrixUnrollA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollB = " + aConstants + ".mMatrixUnrollB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgA = " + aConstants + ".mMatrixArgA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgB = " + aConstants + ".mMatrixArgB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgC = " + aConstants + ".mMatrixArgC;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgD = " + aConstants + ".mMatrixArgD;");
}

} // namespace

bool Builder_GrowA::Build(GTwistExpander *pExpander,
                          ResidualBucket &pResidualBucket,
                          std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowA::Build received null expander";
        }
        return false;
    }

    pExpander->mGrowKeyA.AddLine("// [grow key a]");

    const GTwistRunGrowKeyAConfig::GrowStageConfigs aBuiltStageConfigs =
        GTwistRunGrowKeyAConfig::MakeGrowAConfig(
            pResidualBucket,
            pExpander->mControlCandidateIndex);
    std::vector<GSeedRunStageConfig> aStageConfigs(
        aBuiltStageConfigs.begin(),
        aBuiltStageConfigs.end());
    pExpander->mGrowAStageConfigs = aStageConfigs;
    pExpander->mGrowAMatrixDomain = TwistDomain::kKeyRotateA;

    for (std::size_t i = 0U; i < 3U; ++i) {
        GTwistRunGrowKeyA aRunner(aStageConfigs[i], pResidualBucket);
        if (!aRunner.Plan(pErrorMessage) ||
            !aRunner.Build(pExpander->mGrowKeyA, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_GrowA::Build failed on grow A stage " +
                    std::to_string(i) + ":\n" + *pErrorMessage;
            }
            return false;
        }
    }

    pExpander->mGrowKeyA.AddLine("//");
    AddGrowAMatrixDomainWordLines(pExpander->mGrowKeyA);
    pExpander->mGrowKeyA.AddLine("//");

    const std::vector<GSymbol> aFuseLanes = {
        GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneA),
        GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneB),
        GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneC),
        GSymbol::Buf(TwistWorkSpaceSlot::kFuseLaneD),
    };
    const std::vector<GSymbol> aVaporLanes = {
        GSymbol::Buf(TwistWorkSpaceSlot::kVaporLaneA),
        GSymbol::Buf(TwistWorkSpaceSlot::kVaporLaneB),
        GSymbol::Buf(TwistWorkSpaceSlot::kVaporLaneC),
        GSymbol::Buf(TwistWorkSpaceSlot::kVaporLaneD),
    };
    const std::vector<GSymbol> aShadowLanes = {
        GSymbol::Buf(TwistWorkSpaceSlot::kShadowLaneA),
        GSymbol::Buf(TwistWorkSpaceSlot::kShadowLaneB),
        GSymbol::Buf(TwistWorkSpaceSlot::kShadowLaneC),
        GSymbol::Buf(TwistWorkSpaceSlot::kShadowLaneD),
    };
    const std::vector<GSymbol> aWindLanes = {
        GSymbol::Buf(TwistWorkSpaceSlot::kWindLaneA),
        GSymbol::Buf(TwistWorkSpaceSlot::kWindLaneB),
        GSymbol::Buf(TwistWorkSpaceSlot::kWindLaneC),
        GSymbol::Buf(TwistWorkSpaceSlot::kWindLaneD),
    };

    GRunMatrixDiffusionConfig aDiffusion;
    aDiffusion.mInputA = aFuseLanes[0];
    aDiffusion.mInputB = aFuseLanes[1];
    aDiffusion.mInputC = aFuseLanes[2];
    aDiffusion.mInputD = aFuseLanes[3];
    aDiffusion.mOutputA = aVaporLanes[0];
    aDiffusion.mOutputB = aVaporLanes[1];
    aDiffusion.mOutputC = aVaporLanes[2];
    aDiffusion.mOutputD = aVaporLanes[3];

    // Previous six:
    //   Shadow C, Shadow D, Wind A, Wind B, Wind C, Wind D
    aDiffusion.mShuffleEntropyA = aShadowLanes[2];
    aDiffusion.mShuffleEntropyB = aShadowLanes[3];
    aDiffusion.mShuffleEntropyC = aWindLanes[2];
    aDiffusion.mShuffleEntropyD = aWindLanes[3];
    aDiffusion.mOperationSourceA = aWindLanes[0];
    aDiffusion.mOperationSourceB = aWindLanes[1];

    GBatch aDiffusionBatch;
    aDiffusionBatch.mExportsAsBlock = false;
    if (!GRunMatrixDiffusion::Bake(aDiffusion,
                                   &aDiffusionBatch,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Builder_GrowA::Build failed on grow A matrix diffusion:\n" +
                *pErrorMessage;
        }
        return false;
    }
    pExpander->mGrowKeyA.AddBatch(aDiffusionBatch);
    pExpander->mGrowKeyA.AddLine("//");

    for (std::size_t i = 3U; i < aStageConfigs.size(); ++i) {
        GTwistRunGrowKeyA aRunner(aStageConfigs[i], pResidualBucket);
        if (!aRunner.Plan(pErrorMessage) ||
            !aRunner.Build(pExpander->mGrowKeyA, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_GrowA::Build failed on grow A stage " +
                    std::to_string(i) + ":\n" + *pErrorMessage;
            }
            return false;
        }
    }

    return true;
}
