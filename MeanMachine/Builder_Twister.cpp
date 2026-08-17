//
//  Builder_Twister.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Twister.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunTwist.hpp"
#include "GFlowPlans.hpp"
#include "GRunMatrixDiffusion.hpp"
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

bool AddMatrixDiffusion(TwistProgramBranch &pBranch,
                        const std::vector<GSymbol> &pInputs,
                        const std::vector<GSymbol> &pOutputs,
                        const std::vector<GSymbol> &pEntropy,
                        const char *pDescription,
                        std::string *pErrorMessage) {
    GRunMatrixDiffusionConfig aConfig;
    aConfig.mInputA = pInputs[0];
    aConfig.mInputB = pInputs[1];
    aConfig.mInputC = pInputs[2];
    aConfig.mInputD = pInputs[3];
    aConfig.mOutputA = pOutputs[0];
    aConfig.mOutputB = pOutputs[1];
    aConfig.mOutputC = pOutputs[2];
    aConfig.mOutputD = pOutputs[3];
    aConfig.mEntropyA = pEntropy[0];
    aConfig.mEntropyB = pEntropy[1];
    aConfig.mEntropyC = pEntropy[2];
    aConfig.mEntropyD = pEntropy[3];

    GBatch aBatch;
    aBatch.mExportsAsBlock = false;
    if (!GRunMatrixDiffusion::Bake(aConfig,
                                   &aBatch,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                std::string("error on ") + pDescription +
                " matrix diffusion for twist: " + *pErrorMessage;
        }
        return false;
    }
    pBranch.AddBatch(aBatch);
    return true;
}

std::vector<GSymbol> Symbols(
    const GFlowPlans::SlotArray4 &pSlots) {
    return {
        BufSymbol(pSlots[0]), BufSymbol(pSlots[1]),
        BufSymbol(pSlots[2]), BufSymbol(pSlots[3]),
    };
}

} // namespace

bool Builder_Twister::Build(GTwistExpander *pExpander,
                            std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build received null expander";
        }
        return false;
    }

    const GFlowPlan &aTwistPlan = GFlowPlans::Twist();
    const GTwistRunTwistConfig::TwistStageConfigs aBuiltStageConfigs =
        GTwistRunTwistConfig::MakeTwistConfig(
            pExpander->mControlCandidateIndex);
    const std::vector<GSeedRunStageConfig> aStageConfigs(
        aBuiltStageConfigs.begin(),
        aBuiltStageConfigs.end());

    if (aStageConfigs.size() !=
        GFlowPlans::ARXStepCount(aTwistPlan)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Twist stage configuration count did not match its flow plan";
        }
        return false;
    }

    pExpander->mTwistStageConfigs = aStageConfigs;
    pExpander->mTwistMatrixDomains.assign(
        GFlowPlans::DiffusionCount(aTwistPlan),
        TwistDomain::kTwist);

    const std::vector<GFlowStep> aTwistARXSteps =
        GFlowPlans::ARXSteps(aTwistPlan);
    const std::vector<TwistWorkSpaceSlot> aForkEarthLanes =
        GFlowPlans::InputSlots(aTwistARXSteps.back());
    if (aStageConfigs.empty() ||
        (aStageConfigs.back().mSlices.size() !=
         pExpander->mTwistForkCrystalLanes.size()) ||
        (aForkEarthLanes.size() !=
         pExpander->mTwistForkEarthLanes.size())) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Twist's final stage must read and write four fork lanes";
        }
        return false;
    }
    for (std::size_t i = 0U;
         i < pExpander->mTwistForkCrystalLanes.size();
         ++i) {
        const TwistWorkSpaceSlot aForkEarth = aForkEarthLanes[i];
        const TwistWorkSpaceSlot aForkCrystal =
            aStageConfigs.back().mSlices[i].mDest;
        if ((TwistWorkSpace::GetBufferLength(aForkEarth) != S_BLOCK) ||
            (TwistWorkSpace::GetBufferLength(aForkCrystal) != S_BLOCK)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Twist's Earth/Crystal fork lanes must be full S_BLOCK lanes";
            }
            return false;
        }
        pExpander->mTwistForkEarthLanes[i] = aForkEarth;
        pExpander->mTwistForkCrystalLanes[i] = aForkCrystal;
    }

    std::size_t aStageIndex = 0U;
    bool aAddedMatrixDomainWords = false;
    for (const GFlowStep &aStep : aTwistPlan.mSteps) {
        if (aStep.mKind == GFlowStepKind::kARX) {
            const std::string aStageName =
                "GTwistRunTwist_" + std::string(1U, aStep.mLetter);
            if (!BuildTwistStage(pExpander->mTwister,
                                 aStageConfigs[aStageIndex],
                                 aStageIndex == 0U,
                                 aStageName.c_str(),
                                 pErrorMessage)) {
                return false;
            }
            ++aStageIndex;
            continue;
        }
        if (aStep.mKind == GFlowStepKind::kDiffuse) {
            if (!aAddedMatrixDomainWords) {
                AddTwistMatrixDomainWordLines(pExpander->mTwister,
                                              TwistDomain::kTwist);
                aAddedMatrixDomainWords = true;
            }
            const GFlowPlans::SlotArray4 aInputSlots =
                GFlowPlans::FamilySlots(aStep.mInputs[0]);
            const GFlowPlans::SlotArray4 aOutputSlots =
                GFlowPlans::FamilySlots(aStep.mOutput);
            const GFlowPlans::SlotArray4 aEntropySlots =
                GFlowPlans::FamilySlots(aStep.mEntropy);
            if (!AddMatrixDiffusion(
                    pExpander->mTwister,
                    Symbols(aInputSlots),
                    Symbols(aOutputSlots),
                    Symbols(aEntropySlots),
                    "only",
                    pErrorMessage)) {
                return false;
            }
        }
    }

    return true;
}
