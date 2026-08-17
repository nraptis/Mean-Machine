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
#include "GFlowPlans.hpp"
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

bool BuildKDFMatrixDiffusion(
    TwistProgramBranch &pBranch,
    const std::string &pBranchName,
    const std::vector<GSymbol> &pInputLanes,
    const std::vector<GSymbol> &pDiffusionOutputLanes,
    const std::vector<GSymbol> &pEntropyLanes,
    std::string *pErrorMessage) {
    if ((pInputLanes.size() != 4U) ||
        (pDiffusionOutputLanes.size() != 4U) ||
        (pEntropyLanes.size() != 4U)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                pBranchName +
                " matrix diffusion did not receive four input, output, "
                "and entropy lanes";
        }
        return false;
    }

    GRunMatrixDiffusionConfig aDiffusion;
    aDiffusion.mInputA = pInputLanes[0];
    aDiffusion.mInputB = pInputLanes[1];
    aDiffusion.mInputC = pInputLanes[2];
    aDiffusion.mInputD = pInputLanes[3];
    aDiffusion.mOutputA = pDiffusionOutputLanes[0];
    aDiffusion.mOutputB = pDiffusionOutputLanes[1];
    aDiffusion.mOutputC = pDiffusionOutputLanes[2];
    aDiffusion.mOutputD = pDiffusionOutputLanes[3];

    aDiffusion.mEntropyA = pEntropyLanes[0];
    aDiffusion.mEntropyB = pEntropyLanes[1];
    aDiffusion.mEntropyC = pEntropyLanes[2];
    aDiffusion.mEntropyD = pEntropyLanes[3];

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
                         const std::array<GSeedRunStageConfig, 3> &pConfigs,
                         const char pKDFLetter,
                         const GFlowPlan &pFlowPlan,
                         std::string *pErrorMessage) {
    const char aUpperText[] = {pKDFLetter, '\0'};
    const char aLowerText[] = {
        static_cast<char>(pKDFLetter - 'A' + 'a'),
        '\0'
    };
    const std::string aBranchName = std::string("kdf-") + aLowerText;
    const std::string aStagePrefix = std::string("GSeedRunKDF_") + aUpperText + "_";

    if (pConfigs.size() != GFlowPlans::ARXStepCount(pFlowPlan)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = aBranchName +
                " stage configuration count did not match its flow plan";
        }
        return false;
    }

    std::size_t aStageIndex = 0U;
    for (const GFlowStep &aStep : pFlowPlan.mSteps) {
        if (aStep.mKind == GFlowStepKind::kARX) {
            const std::string aStageName =
                aStagePrefix + std::string(1U, aStep.mLetter);
            if (!BuildKDFStage<Runner>(pBranch,
                                       pConfigs[aStageIndex],
                                       aStageIndex == 0U,
                                       aStageName.c_str(),
                                       aBranchName.c_str(),
                                       pErrorMessage)) {
                return false;
            }
            ++aStageIndex;
            continue;
        }
        if (aStep.mKind == GFlowStepKind::kDiffuse) {
            const GFlowPlans::SlotArray4 aInputs =
                GFlowPlans::FamilySlots(aStep.mInputs[0]);
            const GFlowPlans::SlotArray4 aOutputs =
                GFlowPlans::FamilySlots(aStep.mOutput);
            const GFlowPlans::SlotArray4 aEntropy =
                GFlowPlans::FamilySlots(aStep.mEntropy);
            const auto Symbols = [](const GFlowPlans::SlotArray4 &pSlots) {
                return std::vector<GSymbol> {
                    BufSymbol(pSlots[0]), BufSymbol(pSlots[1]),
                    BufSymbol(pSlots[2]), BufSymbol(pSlots[3]),
                };
            };
            if (!BuildKDFMatrixDiffusion(pBranch,
                                         aBranchName,
                                         Symbols(aInputs),
                                         Symbols(aOutputs),
                                         Symbols(aEntropy),
                                         pErrorMessage)) {
                return false;
            }
        }
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

char KDFDomainSuffix(const std::size_t pDomainIndex) {
    return static_cast<char>('A' + pDomainIndex);
}

template <typename ConfigArray>
void RetagKDFConfigs(ConfigArray *pConfigs,
                     const char pFamily,
                     const char pDomain) {
    if (pConfigs == nullptr) {
        return;
    }

    for (std::size_t aStageIndex = 0U;
         aStageIndex < pConfigs->size();
         ++aStageIndex) {
        const char aStage = static_cast<char>('A' + aStageIndex);
        GSeedRunStageConfig &aConfig = (*pConfigs)[aStageIndex];
        aConfig.mStageName =
            std::string("GSeedRunKDF_") + pFamily + "_" + aStage + "_" + pDomain;
        aConfig.mBatchName =
            std::string("kdf_") +
            static_cast<char>(pFamily - 'A' + 'a') +
            "_loop_" + static_cast<char>(aStage - 'A' + 'a') +
            "_" + static_cast<char>(pDomain - 'A' + 'a');
        aConfig.mStartLine = "// " + aConfig.mStageName + " " +
            aConfig.mBatchName + " (start)";
        aConfig.mEndLine = "// " + aConfig.mStageName + " " +
            aConfig.mBatchName + " (end)";
    }
}

} // namespace

bool Builder_KDF::Build(GTwistExpander *pExpander,
                        ResidualBucket &pResidualBucket,
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

    pExpander->mKDFStageConfigs.clear();
    pExpander->mKDFStageConfigs.reserve(54U);
    for (std::size_t aDomainIndex = 0U; aDomainIndex < 6U; ++aDomainIndex) {
        const char aDomainSuffix = KDFDomainSuffix(aDomainIndex);
        const std::size_t aCandidateIndex =
            pExpander->mControlCandidateIndex + aDomainIndex;
        const std::size_t aBranchBase = aDomainIndex * 3U;

        GSeedRunKDF_AConfig::KDFStageConfigs aKDFAConfigs =
            GSeedRunKDF_AConfig::MakeKDF_AConfig(pResidualBucket,
                                                 aCandidateIndex);
        RetagKDFConfigs(&aKDFAConfigs, 'A', aDomainSuffix);
        TwistProgramBranch &aKDFABranch =
            pExpander->mKDFDomainBranches[aBranchBase + 0U];
        aKDFABranch.Clear();
        if (!BuildKDFStyleBranch<GSeedRunKDF_A>(aKDFABranch,
                                                aKDFAConfigs, 'A',
                                                GFlowPlans::KDFA(),
                                                pErrorMessage)) {
            return false;
        }
        pExpander->mKDFStageConfigs.insert(
            pExpander->mKDFStageConfigs.end(),
            aKDFAConfigs.begin(), aKDFAConfigs.end());

        GSeedRunKDF_BConfig::KDFStageConfigs aKDFBConfigs =
            GSeedRunKDF_BConfig::MakeKDF_BConfig(pResidualBucket,
                                                 aCandidateIndex);
        RetagKDFConfigs(&aKDFBConfigs, 'B', aDomainSuffix);
        TwistProgramBranch &aKDFBBranch =
            pExpander->mKDFDomainBranches[aBranchBase + 1U];
        aKDFBBranch.Clear();
        if (!BuildKDFStyleBranch<GSeedRunKDF_B>(aKDFBBranch,
                                                aKDFBConfigs, 'B',
                                                GFlowPlans::KDFB(),
                                                pErrorMessage)) {
            return false;
        }
        pExpander->mKDFStageConfigs.insert(
            pExpander->mKDFStageConfigs.end(),
            aKDFBConfigs.begin(), aKDFBConfigs.end());

        GSeedRunKDF_CConfig::KDFStageConfigs aKDFCConfigs =
            GSeedRunKDF_CConfig::MakeKDF_CConfig(pResidualBucket,
                                                 aCandidateIndex);
        RetagKDFConfigs(&aKDFCConfigs, 'C', aDomainSuffix);
        TwistProgramBranch &aKDFCBranch =
            pExpander->mKDFDomainBranches[aBranchBase + 2U];
        aKDFCBranch.Clear();
        if (!BuildKDFStyleBranch<GSeedRunKDF_C>(aKDFCBranch,
                                                aKDFCConfigs, 'C',
                                                GFlowPlans::KDFC(),
                                                pErrorMessage)) {
            return false;
        }
        pExpander->mKDFStageConfigs.insert(
            pExpander->mKDFStageConfigs.end(),
            aKDFCConfigs.begin(), aKDFCConfigs.end());

    }

    return true;
}
