//
//  Builder_GrowCommon.hpp
//  MeanMachine
//

#ifndef Builder_GrowCommon_hpp
#define Builder_GrowCommon_hpp

#include "GFlowPlans.hpp"
#include "GPrintTool.hpp"
#include "GSeedRunStageConfig.hpp"
#include "GTwistExpander.hpp"
#include "ResidualBucket.hpp"

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace Builder_GrowCommon {

inline std::string LowerLaneList(const GFlowLane pLane) {
    std::string aStem(GFlowPlans::LaneStem(pLane));
    for (char &aCharacter : aStem) {
        if ((aCharacter >= 'A') && (aCharacter <= 'Z')) {
            aCharacter = static_cast<char>(
                aCharacter - 'A' + 'a');
        }
    }
    return aStem + "_a, " + aStem + "_b, " +
        aStem + "_c, " + aStem + "_d";
}

inline std::string WorkSpaceLane(const GFlowLane pLane,
                                 const char pLaneLetter) {
    return std::string("pWorkSpace->m") +
        GFlowPlans::LaneStem(pLane) +
        "Lane" + pLaneLetter;
}

inline void AddMatrixDomainWordLines(TwistProgramBranch &pBranch,
                                     const char pKeyName) {
    const std::string aConstants =
        std::string("pWorkSpace->mDomainBundle.mKeyRotate") +
        pKeyName + "Constants";
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectA = " + aConstants + ".mMatrixSelectA;");
    pBranch.AddLine("std::uint64_t aDomainWordMatrixSelectB = " + aConstants + ".mMatrixSelectB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollA = " + aConstants + ".mMatrixUnrollA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixUnrollB = " + aConstants + ".mMatrixUnrollB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgA = " + aConstants + ".mMatrixArgA;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgB = " + aConstants + ".mMatrixArgB;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgC = " + aConstants + ".mMatrixArgC;");
    pBranch.AddLine("std::uint8_t aDomainWordMatrixArgD = " + aConstants + ".mMatrixArgD;");
}

inline void AddMiniDiffusion(TwistProgramBranch &pBranch,
                             const GFlowStep &pStep,
                             const char pKeyName,
                             const bool pAddLeadingBlankLine) {
    const std::string aSourceLanes =
        LowerLaneList(pStep.mInputs[0]) + ", " +
        LowerLaneList(pStep.mEntropy);
    const std::string aDestinationLanes =
        LowerLaneList(pStep.mOutput);
    GPrintTool::AddDiffusion(aSourceLanes.c_str(),
                             aDestinationLanes.c_str());
    if (pAddLeadingBlankLine) {
        pBranch.AddLine("");
    }

    std::string aCall =
        std::string("TwistDiffuse::KeyDiffuseWithDomainWords") +
        pKeyName + "(\n";
    const auto AddLanePair = [&aCall](const GFlowLane pLane,
                                      const char pLaneA,
                                      const char pLaneB,
                                      const char *pComment) {
        aCall += "    " + WorkSpaceLane(pLane, pLaneA) + ", " +
            WorkSpaceLane(pLane, pLaneB) + ", // " + pComment + "\n";
    };
    AddLanePair(pStep.mEntropy, 'A', 'B', "entropy lanes");
    AddLanePair(pStep.mEntropy, 'C', 'D', "entropy lanes");
    AddLanePair(pStep.mInputs[0], 'A', 'B', "input lanes");
    AddLanePair(pStep.mInputs[0], 'C', 'D', "input lanes");
    AddLanePair(pStep.mOutput, 'A', 'B', "output lanes");
    AddLanePair(pStep.mOutput, 'C', 'D', "output lanes");
    aCall +=
        "    pWorkSpace->mIndexList256A, pWorkSpace->mIndexList256B, pWorkSpace->mIndexList256C, pWorkSpace->mIndexList256D,\n"
        "    &mMatrix, aDomainWordMatrixSelectA, aDomainWordMatrixSelectB,\n"
        "    aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB,\n"
        "    aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD);";
    pBranch.AddLine(aCall);
    pBranch.AddLine("");
}

inline void AddKeyWrite(TwistProgramBranch &pBranch,
                        const char pKeyName,
                        const std::size_t pLaneSplit) {
    pBranch.AddLine(
        std::string("TwistShiftBox::ShiftKeyBox") +
        pKeyName + "(pWorkSpace);");

    const std::string aOffset = (pLaneSplit == 0U) ?
        "" : " + (W_KEY * " + std::to_string(pLaneSplit) + "U)";
    pBranch.AddLine(
        "TwistSquash::SquashKeyA(\n"
        "    pWorkSpace->mIceLaneA" + aOffset + ",\n"
        "    pWorkSpace->mIceLaneB" + aOffset + ",\n"
        "    pWorkSpace->mIceLaneC" + aOffset + ",\n"
        "    pWorkSpace->mIceLaneD" + aOffset + ",\n"
        "    &(pWorkSpace->mKeyBox" + std::string(1U, pKeyName) +
        "[0][0]));");
}

template <typename Runner, std::size_t N>
bool Build(TwistProgramBranch &pBranch,
           const std::array<GSeedRunStageConfig, N> &pConfigs,
           ResidualBucket &pResidualBucket,
           const GFlowPlan &pPlan,
           const char pKeyName,
           const std::size_t pLaneSplit,
           std::string *pErrorMessage) {
    if (N != GFlowPlans::ARXStepCount(pPlan)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                std::string("Grow ") + pKeyName +
                " stage configuration count did not match its flow plan";
        }
        return false;
    }

    std::size_t aStageIndex = 0U;
    std::size_t aDiffusionIndex = 0U;

    for (const GFlowStep &aStep : pPlan.mSteps) {
        if (aStep.mKind == GFlowStepKind::kARX) {
            Runner aRunner(pConfigs[aStageIndex], pResidualBucket);
            if (!aRunner.Plan(pErrorMessage) ||
                !aRunner.Build(pBranch, pErrorMessage)) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage =
                        std::string("Grow ") + pKeyName +
                        " failed on ARX stage " +
                        std::to_string(aStageIndex) + ":\n" +
                        *pErrorMessage;
                }
                return false;
            }
            ++aStageIndex;
            continue;
        }

        if (aStep.mKind == GFlowStepKind::kDiffuse) {
            if (aDiffusionIndex == 0U) {
                AddMatrixDomainWordLines(pBranch, pKeyName);
            }
            AddMiniDiffusion(pBranch,
                             aStep,
                             pKeyName,
                             aDiffusionIndex == 0U);
            ++aDiffusionIndex;
            continue;
        }

        if (aStep.mKind == GFlowStepKind::kSquashKey) {
            AddKeyWrite(pBranch, pKeyName, pLaneSplit);
        }
    }
    return true;
}

} // namespace Builder_GrowCommon

#endif /* Builder_GrowCommon_hpp */
