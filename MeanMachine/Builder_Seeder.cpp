//
//  Builder_Seeder.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Seeder.hpp"
#include "GKDF.hpp"
#include "GTwistExpander.hpp"
#include "GFarm.hpp"

#include "ResidualBucket.hpp"

#include "GSeedRunSeed.hpp"
#include "GSeedRunKeyBox.hpp"
#include "GFlowPlans.hpp"

#include "GRunMatrixDiffusion.hpp"
#include "GMagicNumbers.hpp"

#include "stdafx.hpp"

#include <array>
#include <sstream>
#include <utility>

namespace {

const char *PhaseSubWordName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kKeyRotateA: return "KeyRotateA";
        case TwistDomain::kKeyRotateB: return "KeyRotateB";
        case TwistDomain::kKeySpawnA: return "KeySpawnA";
        case TwistDomain::kKeySpawnB: return "KeySpawnB";
        case TwistDomain::kSeed: return "Seed";
        case TwistDomain::kTwist: return "Twist";
        default:
            return "Invalid";
    }
}

const char *DomainDescription(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kKeyRotateA: return "key a rotate";
        case TwistDomain::kKeyRotateB: return "key b rotate";
        case TwistDomain::kKeySpawnA: return "key a spawn";
        case TwistDomain::kKeySpawnB: return "key b spawn";
        case TwistDomain::kSeed: return "seed";
        case TwistDomain::kTwist: return "twist";
        default: return "invalid";
    }
}

std::string UInt64Literal(const std::uint64_t pValue) {
    std::ostringstream aStream;
    aStream << "0x" << std::uppercase << std::hex << pValue << "ULL";
    return aStream.str();
}

std::string KeyLaneMacroPlaceholder(
    const std::size_t pLogicalKeyIndex,
    const char pLaneLetter) {
    const char aKeyBoxName =
        (pLogicalKeyIndex < 8U) ? 'A' : 'B';
    const char aKeyRowName =
        static_cast<char>('A' + (pLogicalKeyIndex % 8U));
    return std::string("KEY_LANE_KEY_") + aKeyBoxName + "_" +
        aKeyRowName + "_IceLane" + pLaneLetter;
}

std::string KeyDiffuseMethodName(
    const char pDiffuseStage,
    const std::size_t pLogicalKeyIndex) {
    const char aKeyBoxName =
        (pLogicalKeyIndex < 8U) ? 'A' : 'B';
    const char aKeyRowName =
        static_cast<char>('A' + (pLogicalKeyIndex % 8U));
    return std::string("KeyDiffuse_") + pDiffuseStage + "_" +
        aKeyBoxName + "_" + aKeyRowName;
}

bool AddKDFStateDeclarations(TwistProgramBranch &pBranch,
                             std::string *pErrorMessage) {
    static constexpr std::array<const char *, 13> kStateNames = {
        "aIngress",
        "aCarry",
        "aWandererA",
        "aWandererB",
        "aWandererC",
        "aWandererD",
        "aWandererE",
        "aWandererF",
        "aWandererG",
        "aWandererH",
        "aWandererI",
        "aWandererJ",
        "aWandererK",
    };
    static_assert(G_HOT_PACK_SIZE >= kStateNames.size(),
                  "A HotPack must contain every Seed ARX-state addition");

    const std::vector<GHotPack> aHotPacks =
        GMagicNumbers::GetHotPacks(1);
    if (aHotPacks.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Builder_Seeder could not obtain a HotPack for the "
                "Seed ARX-state additions";
        }
        return false;
    }
    const GHotPack &aHotPack = aHotPacks.front();

    for (std::size_t aIndex = 0U;
         aIndex < kStateNames.size();
         ++aIndex) {
        const std::string aStateName(kStateNames[aIndex]);
        const std::string aAddWord = UInt64Literal(
            aHotPack.mPair[aIndex].mAdd
        );
        pBranch.AddLine(
            "std::uint64_t " + aStateName + " = *p" +
            aStateName.substr(1U) + " + " + aAddWord + ";"
        );
    }
    return true;
}

void AddSecretDerivationHeader(TwistProgramBranch &pBranch) {
    pBranch.AddLine("////////////////////////////////////////////////////////");
    pBranch.AddLine("//");
    pBranch.AddLine("// Secret material derivation, across 6 domains.");
    pBranch.AddLine("//");
}

void AddDomainHeader(TwistProgramBranch &pBranch,
                     const std::size_t pDomainIndex,
                     const std::size_t pDomainCount,
                     const TwistDomain pDomain) {
    pBranch.AddLine(
        "// Domain " + std::to_string(pDomainIndex + 1U) + " of " +
        std::to_string(pDomainCount) + ", " + DomainDescription(pDomain) + ":"
    );
    pBranch.AddLine("//");
}

void AddKDFEntryFlowComment(TwistProgramBranch &pBranch,
                            const GFlowPlan &pPlan,
                            const bool pAddLeadingSeparator) {
    if (pAddLeadingSeparator) {
        pBranch.AddLine("//");
    }

    const std::vector<GFlowStep> aARXSteps =
        GFlowPlans::ARXSteps(pPlan);
    if (!aARXSteps.empty()) {
        pBranch.AddLine(
            "// src: " +
            GFlowPlans::FlowCommentList(aARXSteps.front().mInputs));
        pBranch.AddLine(
            "// dst: " + GFlowPlans::FlowCommentList(
                {aARXSteps.front().mOutput}));
    }
    pBranch.AddLine("//");
}

std::array<GSymbol, 4U> FinalARXDestinationSymbols(
    const GFlowPlan &pPlan) {
    const std::vector<GFlowStep> aARXSteps =
        GFlowPlans::ARXSteps(pPlan);
    const GFlowPlans::SlotArray4 aSlots =
        GFlowPlans::FamilySlots(aARXSteps.back().mOutput);
    return {{
        BufSymbol(aSlots[0]), BufSymbol(aSlots[1]),
        BufSymbol(aSlots[2]), BufSymbol(aSlots[3]),
    }};
}

void AddFarmStatements(TwistProgramBranch &pBranch,
                       const std::vector<GStatement> &pStatements,
                       const bool pAddTrailingBlankLine = true) {
    for (std::size_t aStatementIndex = 0U;
         aStatementIndex < pStatements.size();
        ++aStatementIndex) {
        if (aStatementIndex > 0U) {
            pBranch.AddLine("");
        }
        pBranch.AddLine(pStatements[aStatementIndex].mRawLine);
    }
    if (pAddTrailingBlankLine) {
        pBranch.AddLine("");
    }
}

void AddSeedMatrixDomainWordLines(TwistProgramBranch &pBranch) {
    const std::string aConstants =
        "pWorkSpace->mDomainBundle.mSeedConstants";

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

bool BuildSeedStage(TwistProgramBranch &pBranch,
                    const GSeedRunStageConfig &pConfig,
                    const bool pUseNonces,
                    const bool pEmitNoncePrologue,
                    const char *pStageName,
                    std::string *pErrorMessage) {
    GSeedRunSeed aRunner(pConfig,
                         pUseNonces,
                         pEmitNoncePrologue);
    if (!aRunner.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on ") + pStageName + ".Plan for seed\n" + *pErrorMessage;
        }
        return false;
    }

    if (!aRunner.Build(pBranch, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("Builder_Seeder::Build failed to bake ") + pStageName + ":\n" + *pErrorMessage;
        }
        return false;
    }

    return true;
}

bool BuildSeedDiffusion(TwistProgramBranch &pBranch,
                        const GFlowStep &pPlan,
                        const std::size_t pDiffusionIndex,
                        std::string *pErrorMessage) {
    const GFlowPlans::SlotArray4 aInputs =
        GFlowPlans::FamilySlots(pPlan.mInputs[0]);
    const GFlowPlans::SlotArray4 aOutputs =
        GFlowPlans::FamilySlots(pPlan.mOutput);
    const GFlowPlans::SlotArray4 aEntropy =
        GFlowPlans::FamilySlots(pPlan.mEntropy);
    GRunMatrixDiffusionConfig aConfig;
    aConfig.mInputA = BufSymbol(aInputs[0]);
    aConfig.mInputB = BufSymbol(aInputs[1]);
    aConfig.mInputC = BufSymbol(aInputs[2]);
    aConfig.mInputD = BufSymbol(aInputs[3]);
    aConfig.mOutputA = BufSymbol(aOutputs[0]);
    aConfig.mOutputB = BufSymbol(aOutputs[1]);
    aConfig.mOutputC = BufSymbol(aOutputs[2]);
    aConfig.mOutputD = BufSymbol(aOutputs[3]);
    aConfig.mEntropyA = BufSymbol(aEntropy[0]);
    aConfig.mEntropyB = BufSymbol(aEntropy[1]);
    aConfig.mEntropyC = BufSymbol(aEntropy[2]);
    aConfig.mEntropyD = BufSymbol(aEntropy[3]);

    GBatch aBatch;
    if (!GRunMatrixDiffusion::Bake(aConfig,
                                   &aBatch,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "error on seed matrix diffusion " +
                std::to_string(pDiffusionIndex + 1U) + ": " +
                *pErrorMessage;
        }
        return false;
    }
    pBranch.AddBatch(aBatch);
    return true;
}

} // namespace

bool Builder_Seeder::Build(GTwistExpander *pExpander,
                           ResidualBucket &pSeedResidualBucket,
                           std::string *pErrorMessage) {

    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build received null expander";
        }
        return false;
    }

    const GFlowPlan &aKDFAPlan = GFlowPlans::KDFA();
    const GFlowPlan &aKDFBPlan = GFlowPlans::KDFB();
    const GFlowPlan &aKDFCPlan = GFlowPlans::KDFC();
    const std::array<GSymbol, 4U> aFarmLanesA =
        FinalARXDestinationSymbols(aKDFAPlan);
    const std::array<GSymbol, 4U> aFarmLanesB =
        FinalARXDestinationSymbols(aKDFBPlan);
    const std::array<GSymbol, 4U> aFarmLanesC =
        FinalARXDestinationSymbols(aKDFCPlan);

    std::vector<TwistDomain> aDomains;
    aDomains.push_back(TwistDomain::kKeyRotateA);
    aDomains.push_back(TwistDomain::kKeyRotateB);
    aDomains.push_back(TwistDomain::kKeySpawnA);
    aDomains.push_back(TwistDomain::kKeySpawnB);
    aDomains.push_back(TwistDomain::kTwist);
    aDomains.push_back(TwistDomain::kSeed);

    if (!AddKDFStateDeclarations(pExpander->mSeed,
                                 pErrorMessage)) {
        return false;
    }
    pExpander->mSeed.AddLine("");

    AddSecretDerivationHeader(pExpander->mSeed);

    for (std::size_t aDomainIndex = 0U; aDomainIndex < aDomains.size(); ++aDomainIndex) {
        const std::string aDomainPartialName = PhaseSubWordName(aDomains[aDomainIndex]);

        AddDomainHeader(pExpander->mSeed,
                        aDomainIndex,
                        aDomains.size(),
                        aDomains[aDomainIndex]);

        std::vector<GStatement> aStatementsKDFA;
        GKDF_A aKDF_A;
        if (!aKDF_A.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kInbuilt,
                         &aStatementsKDFA,
                         pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake inbuilt KDF:\n" + *pErrorMessage;
            }
            return false;
        }
        AddKDFEntryFlowComment(pExpander->mSeed,
                               aKDFAPlan,
                               false);
        for (const GStatement &aStatement : aStatementsKDFA) {
            if (!aStatement.IsRawLine()) {
                continue;
            }
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("");

        std::vector<GStatement> aStatementsFarmA;
        GFarm aFarm;
        if (!aFarm.BakeEphemeralA(aFarmLanesA[0],
                                  aFarmLanesA[1],
                                  aFarmLanesA[2],
                                  aFarmLanesA[3],
                                  aDomainPartialName,
                                  &aStatementsFarmA,
                                  pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake farm after KDFA:\n" + *pErrorMessage;
            }
            return false;
        }

        AddFarmStatements(pExpander->mSeed, aStatementsFarmA);

        std::vector<GStatement> aStatementsKDFB;
        GKDF_B aKDF_B;
        if (!aKDF_B.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kEphemeralA,
                         &aStatementsKDFB,
                         pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake inbuilt KDF_B:\n" + *pErrorMessage;
            }
            return false;
        }
        AddKDFEntryFlowComment(pExpander->mSeed,
                               aKDFBPlan,
                               true);
        for (const GStatement &aStatement : aStatementsKDFB) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("");

        std::vector<GStatement> aStatementsFarmAfterKDFB;
        if (!aFarm.BakeEphemeralB(aFarmLanesB[0],
                                  aFarmLanesB[1],
                                  aFarmLanesB[2],
                                  aFarmLanesB[3],
                                  aDomainPartialName,
                                  &aStatementsFarmAfterKDFB,
                                  pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_Seeder::Build failed to derive ephemeral-B "
                    "material after KDF_B:\n" + *pErrorMessage;
            }
            return false;
        }
        AddFarmStatements(pExpander->mSeed, aStatementsFarmAfterKDFB);

        std::vector<GStatement> aStatementsKDFC;
        GKDF_C aKDF_C;
        if (!aKDF_C.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kEphemeralB,
                         &aStatementsKDFC,
                         pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake KDF_C:\n" + *pErrorMessage;
            }
            return false;
        }
        AddKDFEntryFlowComment(pExpander->mSeed,
                               aKDFCPlan,
                               true);
        for (const GStatement &aStatement : aStatementsKDFC) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("");

        std::vector<GStatement> aStatementsFarmAfterKDFC;
        if (!aFarm.BakeWorkspace(aFarmLanesC[0],
                                 aFarmLanesC[1],
                                 aFarmLanesC[2],
                                 aFarmLanesC[3],
                                 aDomainPartialName,
                                 &aStatementsFarmAfterKDFC,
                                 pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_Seeder::Build failed to derive final workspace "
                    "material after KDF_C:\n" + *pErrorMessage;
            }
            return false;
        }
        AddFarmStatements(pExpander->mSeed,
                          aStatementsFarmAfterKDFC,
                          false);
        pExpander->mSeed.AddLine("//");
    }

    pExpander->mSeed.AddLine("////////////////////////////////////////////////////////");
    pExpander->mSeed.AddLine("");
    pExpander->mSeed.AddLine("");
    pExpander->mSeed.AddLine("////////////////////////////////////////////////////////");
    pExpander->mSeed.AddLine("//");
    pExpander->mSeed.AddLine("// Main seed loops");

    return Build_PostKDF(pExpander,
                         pSeedResidualBucket,
                         pErrorMessage);

}

bool Builder_Seeder::Build_PostKDF(GTwistExpander *pExpander,
                                   ResidualBucket &pResidualBucket,
                                   std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build_PostKDF received null expander";
        }
        return false;
    }

    const GSeedRunSeedConfig::SeedStageConfigs aBuiltStageConfigs =
        GSeedRunSeedConfig::MakeSeedConfig(true,
                                           pResidualBucket,
                                           pExpander->mControlCandidateIndex);
    std::vector<GSeedRunStageConfig> aStageConfigs(
        aBuiltStageConfigs.begin(),
        aBuiltStageConfigs.end());
    pExpander->mSeedStageConfigs = aStageConfigs;
    const GFlowPlan &aSeedPlan = GFlowPlans::Seed();
    if (aStageConfigs.size() !=
        GFlowPlans::ARXStepCount(aSeedPlan)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Seed stage configuration count did not match its flow plan";
        }
        return false;
    }
    pExpander->mSeedMatrixDomains.assign(
        GFlowPlans::DiffusionCount(aSeedPlan), TwistDomain::kSeed);

    std::size_t aStageIndex = 0U;
    std::size_t aDiffusionIndex = 0U;
    bool aAddedMatrixDomainWords = false;
    for (const GFlowStep &aStep : aSeedPlan.mSteps) {
        if (aStep.mKind == GFlowStepKind::kDiffuse) {
            if (!aAddedMatrixDomainWords) {
                AddSeedMatrixDomainWordLines(pExpander->mSeed);
                aAddedMatrixDomainWords = true;
            }
            if (!BuildSeedDiffusion(pExpander->mSeed,
                                    aStep,
                                    aDiffusionIndex,
                                    pErrorMessage)) {
                return false;
            }
            ++aDiffusionIndex;
            continue;
        }
        if (aStep.mKind != GFlowStepKind::kARX) {
            continue;
        }
        const char aStageLetter = aStep.mLetter;
        const std::string aStageName =
            "GSeedRunSeed_" + std::string(1U, aStageLetter);
        if (!BuildSeedStage(pExpander->mSeed,
                            aStageConfigs[aStageIndex],
                            true,
                            false,
                            aStageName.c_str(),
                            pErrorMessage)) {
            return false;
        }

        ++aStageIndex;
    }

    if (gCandidateIndex < 0) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Builder_Seeder received a negative candidate index";
        }
        return false;
    }

    GSeedRunKeyBoxConfig::KeyBoxStageConfigs aKeyBoxConfigs;
    if (!GSeedRunKeyBoxConfig::MakeKeyBoxConfigs(
            static_cast<std::size_t>(gCandidateIndex),
            pResidualBucket,
            &aKeyBoxConfigs,
            pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Builder_Seeder failed to make key-box configs:\n" +
                *pErrorMessage;
        }
        return false;
    }
    pExpander->mSeedKeyBoxStageConfigs.assign(
        aKeyBoxConfigs.begin(),
        aKeyBoxConfigs.end()
    );

    pExpander->mSeed.AddLine("//");
    pExpander->mSeed.AddLine("////////////////////////////////////////////////////////");
    pExpander->mSeed.AddLine("");

    pExpander->mSeed.AddLine("////////////////////////////////////////////////////////");
    pExpander->mSeed.AddLine("//");
    pExpander->mSeed.AddLine("// Folding main seed loops into destination");
    pExpander->mSeed.AddLine("//");
    pExpander->mSeed.AddLine("SEED_DESTINATION_SQUASH;");
    pExpander->mSeed.AddLine("//");
    pExpander->mSeed.AddLine("////////////////////////////////////////////////////////");
    pExpander->mSeed.AddLine("");
    pExpander->mSeed.AddLine("WRITE_OUT_MAIN_ARX_STATE;");
    pExpander->mSeed.AddLine("");

    pExpander->mSeed.AddLine("////////////////////////////////////////////////////////");
    pExpander->mSeed.AddLine("//");
    pExpander->mSeed.AddLine("// Independent key-row flows");
    pExpander->mSeed.AddLine("//");

    const auto BuildKeyStage = [&](const std::size_t pConfigIndex) {
        GSeedRunKEY aKeyBox(aKeyBoxConfigs[pConfigIndex]);
        if (!aKeyBox.Plan(pErrorMessage) ||
            !aKeyBox.Build(pExpander->mSeed, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_Seeder failed on " +
                    aKeyBoxConfigs[pConfigIndex].mStageName + ":\n" +
                    *pErrorMessage;
            }
            return false;
        }
        return true;
    };

    for (std::size_t aLogicalKeyIndex = 0U;
         aLogicalKeyIndex < GFlowPlans::kKeyFlowCount;
         ++aLogicalKeyIndex) {
        const char aKeyBoxName =
            (aLogicalKeyIndex < GFlowPlans::kKeyBoxFlowCount) ? 'A' : 'B';
        const char aKeyRowName = static_cast<char>(
            'A' + (aLogicalKeyIndex % GFlowPlans::kKeyBoxFlowCount));
        const std::size_t aKeyRowIndex =
            aLogicalKeyIndex % GFlowPlans::kKeyBoxFlowCount;

        if (aLogicalKeyIndex == GFlowPlans::kKeyBoxFlowCount) {
            pExpander->mSeed.AddLine("RESTORE_MAIN_ARX_STATE;");
            pExpander->mSeed.AddLine("");
        }

        pExpander->mSeed.AddLine(
            "// Key flow — " + std::string(1U, aKeyBoxName) + " / " +
            std::string(1U, aKeyRowName)
        );
        pExpander->mSeed.AddLine("");

        std::size_t aKeyARXIndex = 0U;
        std::size_t aKeyDiffuseIndex = 0U;
        for (const GFlowStep &aStep : GFlowPlans::Key().mSteps) {
            if (aStep.mKind == GFlowStepKind::kARX) {
                if (!BuildKeyStage(
                        (aKeyARXIndex * 16U) + aLogicalKeyIndex)) {
                    return false;
                }
                ++aKeyARXIndex;
                continue;
            }
            if (aStep.mKind == GFlowStepKind::kDiffuse) {
                const char aDiffuseStage = static_cast<char>(
                    'A' + aKeyDiffuseIndex);
                pExpander->mSeed.AddLine(
                    KeyDiffuseMethodName(aDiffuseStage,
                                         aLogicalKeyIndex) +
                    "(pWorkSpace);"
                );
                pExpander->mSeed.AddLine("");
                ++aKeyDiffuseIndex;
                continue;
            }
            if (aStep.mKind == GFlowStepKind::kSquashKey) {
                pExpander->mSeed.AddLine(
                    "TwistSquash::SquashKeyA(" +
                    KeyLaneMacroPlaceholder(aLogicalKeyIndex, 'A') + ", " +
                    KeyLaneMacroPlaceholder(aLogicalKeyIndex, 'B') + ", " +
                    KeyLaneMacroPlaceholder(aLogicalKeyIndex, 'C') + ", " +
                    KeyLaneMacroPlaceholder(aLogicalKeyIndex, 'D') + ", " +
                    "&(pWorkSpace->mKeyBox" +
                    std::string(1U, aKeyBoxName) +
                    "[" + std::to_string(aKeyRowIndex) + "U][0]));"
                );
                pExpander->mSeed.AddLine("");
            }
        }
    }
    pExpander->mSeed.AddLine("//");
    pExpander->mSeed.AddLine("////////////////////////////////////////////////////////");
    return true;
}
