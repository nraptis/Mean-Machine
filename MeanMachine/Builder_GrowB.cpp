//
//  Builder_GrowB.cpp
//  MeanMachine
//
//  Created by icarus black on 7/13/26.
//

#include "Builder_GrowB.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunGrowKeyB.hpp"
#include "ResidualBucket.hpp"

#include <string>
#include <vector>

namespace {

void AddGrowBMatrixDomainWordLines(TwistProgramBranch &pBranch) {
    const std::string aConstants =
        "pWorkSpace->mDomainBundle.mKeyRotateBConstants";
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

bool Builder_GrowB::Build(GTwistExpander *pExpander,
                          ResidualBucket &pResidualBucket,
                          std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowB::Build received null expander";
        }
        return false;
    }

    pExpander->mGrowKeyB.AddLine("// [grow key b]");

    const GTwistRunGrowKeyBConfig::GrowStageConfigs aBuiltStageConfigs =
        GTwistRunGrowKeyBConfig::MakeGrowBConfig(
            pResidualBucket,
            pExpander->mControlCandidateIndex);
    std::vector<GSeedRunStageConfig> aStageConfigs(
        aBuiltStageConfigs.begin(),
        aBuiltStageConfigs.end());
    pExpander->mGrowBStageConfigs = aStageConfigs;
    pExpander->mGrowBMatrixDomain = TwistDomain::kKeyRotateB;

    for (std::size_t i = 0U; i < 3U; ++i) {
        GTwistRunGrowKeyB aRunner(aStageConfigs[i], pResidualBucket);
        if (!aRunner.Plan(pErrorMessage) ||
            !aRunner.Build(pExpander->mGrowKeyB, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_GrowB::Build failed on grow B stage " +
                    std::to_string(i) + ":\n" + *pErrorMessage;
            }
            return false;
        }
    }

    pExpander->mGrowKeyB.AddLine("//");
    AddGrowBMatrixDomainWordLines(pExpander->mGrowKeyB);
    pExpander->mGrowKeyB.AddLine("//");

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
    const std::vector<GSymbol> aAetherLanes = {
        GSymbol::Buf(TwistWorkSpaceSlot::kAetherLaneA),
        GSymbol::Buf(TwistWorkSpaceSlot::kAetherLaneB),
        GSymbol::Buf(TwistWorkSpaceSlot::kAetherLaneC),
        GSymbol::Buf(TwistWorkSpaceSlot::kAetherLaneD),
    };
    const std::vector<GSymbol> aKineticLanes = {
        GSymbol::Buf(TwistWorkSpaceSlot::kKineticLaneA),
        GSymbol::Buf(TwistWorkSpaceSlot::kKineticLaneB),
        GSymbol::Buf(TwistWorkSpaceSlot::kKineticLaneC),
        GSymbol::Buf(TwistWorkSpaceSlot::kKineticLaneD),
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
    //   Aether C, Aether D, Kinetic A, Kinetic B, Kinetic C, Kinetic D
    aDiffusion.mShuffleEntropyA = aAetherLanes[2];
    aDiffusion.mShuffleEntropyB = aAetherLanes[3];
    aDiffusion.mShuffleEntropyC = aKineticLanes[2];
    aDiffusion.mShuffleEntropyD = aKineticLanes[3];
    aDiffusion.mOperationSourceA = aKineticLanes[0];
    aDiffusion.mOperationSourceB = aKineticLanes[1];

    GBatch aDiffusionBatch;
    aDiffusionBatch.mExportsAsBlock = false;
    if (!GRunMatrixDiffusion::Bake(aDiffusion,
                                   &aDiffusionBatch,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Builder_GrowB::Build failed on grow B matrix diffusion:\n" +
                *pErrorMessage;
        }
        return false;
    }
    pExpander->mGrowKeyB.AddBatch(aDiffusionBatch);
    pExpander->mGrowKeyB.AddLine("//");

    for (std::size_t i = 3U; i < aStageConfigs.size(); ++i) {
        GTwistRunGrowKeyB aRunner(aStageConfigs[i], pResidualBucket);
        if (!aRunner.Plan(pErrorMessage) ||
            !aRunner.Build(pExpander->mGrowKeyB, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_GrowB::Build failed on grow B stage " +
                    std::to_string(i) + ":\n" + *pErrorMessage;
            }
            return false;
        }
    }

    return true;
}
