//
//  Builder_Seeder.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Seeder.hpp"
#include "GKDF.hpp"
#include "GSnow.hpp"
#include "GTwistExpander.hpp"
#include "GFarm.hpp"

#include "Random.hpp"

#include "GSeedRunSeed.hpp"
#include "GDomainSchedule.hpp"
#include "GSquashInvestToKeyBoxes.hpp"

#include "GRunMatrixDiffusion.hpp"

#include "GSquash.hpp"

namespace {

const char *PhaseConstantsMemberName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB: return "mPhaseBConstants";
        case TwistDomain::kPhaseC: return "mPhaseCConstants";
        case TwistDomain::kPhaseD: return "mPhaseDConstants";
        case TwistDomain::kPhaseE: return "mPhaseEConstants";
        case TwistDomain::kPhaseF: return "mPhaseFConstants";
        case TwistDomain::kPhaseG: return "mPhaseGConstants";
        case TwistDomain::kPhaseH: return "mPhaseHConstants";
        case TwistDomain::kPhaseA:
        default:
            return "mPhaseAConstants";
    }
}

const char *PhaseSubWordName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB: return "PhaseB";
        case TwistDomain::kPhaseC: return "PhaseC";
        case TwistDomain::kPhaseD: return "PhaseD";
        case TwistDomain::kPhaseE: return "PhaseE";
        case TwistDomain::kPhaseF: return "PhaseF";
        case TwistDomain::kPhaseG: return "PhaseG";
        case TwistDomain::kPhaseH: return "PhaseH";
        case TwistDomain::kPhaseA:
        default:
            return "PhaseA";
    }
}

const char *PhaseDisplayName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kPhaseB: return "Phase B";
        case TwistDomain::kPhaseC: return "Phase C";
        case TwistDomain::kPhaseD: return "Phase D";
        case TwistDomain::kPhaseE: return "Phase E";
        case TwistDomain::kPhaseF: return "Phase F";
        case TwistDomain::kPhaseG: return "Phase G";
        case TwistDomain::kPhaseH: return "Phase H";
        case TwistDomain::kPhaseA:
        default:
            return "Phase A";
    }
}

void AddSeedPhaseHeader(TwistProgramBranch &pBranch,
                        const TwistDomain pDomain) {
    pBranch.AddLine("////////////////////////////////////////////////////////");
    pBranch.AddLine(std::string("////////        ") + PhaseDisplayName(pDomain));
    pBranch.AddLine("////////");
    pBranch.AddLine("");
}

void AddSeedPhaseFooter(TwistProgramBranch &pBranch) {
    pBranch.AddLine("");
    pBranch.AddLine("////////");
    pBranch.AddLine("////////");
    pBranch.AddLine("////////////////////////////////////////////////////////");
    pBranch.AddLine("");
}

void AddSeedMatrixDomainWordLines(TwistProgramBranch &pBranch,
                                  const TwistDomain pDomain,
                                  const bool pDeclare) {
    const std::string aU64Prefix = pDeclare ? "std::uint64_t " : "";
    const std::string aU8Prefix = pDeclare ? "std::uint8_t " : "";
    const std::string aConstants = std::string("pWorkSpace->mDomainBundle.") +
                                   PhaseConstantsMemberName(pDomain);

    pBranch.AddLine(aU64Prefix + "aDomainWordMatrixSelectA = " + aConstants + ".mMatrixSelectA;");
    pBranch.AddLine(aU64Prefix + "aDomainWordMatrixSelectB = " + aConstants + ".mMatrixSelectB;");
    pBranch.AddLine("");
    pBranch.AddLine(aU8Prefix + "aDomainWordMatrixUnrollA = " + aConstants + ".mMatrixUnrollA;");
    pBranch.AddLine(aU8Prefix + "aDomainWordMatrixUnrollB = " + aConstants + ".mMatrixUnrollB;");
    pBranch.AddLine("");
    pBranch.AddLine(aU8Prefix + "aDomainWordMatrixArgA = " + aConstants + ".mMatrixArgA;");
    pBranch.AddLine(aU8Prefix + "aDomainWordMatrixArgB = " + aConstants + ".mMatrixArgB;");
    pBranch.AddLine(aU8Prefix + "aDomainWordMatrixArgC = " + aConstants + ".mMatrixArgC;");
    pBranch.AddLine(aU8Prefix + "aDomainWordMatrixArgD = " + aConstants + ".mMatrixArgD;");
}

template <class T>
bool BuildSeedStage(TwistProgramBranch &pBranch,
                    T &pRunner,
                    const char *pStageName,
                    std::string *pErrorMessage) {
    if (!pRunner.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on ") + pStageName + ".Plan for seed\n" + *pErrorMessage;
        }
        return false;
    }

    if (!pRunner.Build(pBranch, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("Builder_Seeder::Build failed to bake ") + pStageName + ":\n" + *pErrorMessage;
        }
        return false;
    }

    return true;
}

bool AddKDFBInvestCapture(TwistProgramBranch &pBranch,
                          const std::vector<GSymbol> &pExpansionLanes,
                          const GSymbol &pInvestLane,
                          std::string *pErrorMessage) {
    if (pExpansionLanes.size() < 4U) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::AddKDFBInvestCapture requires four expansion lanes.";
        }
        return false;
    }

    std::vector<GStatement> aStatements;
    GSquash aSquash;
    if (!aSquash.Bake(pInvestLane,
                      pExpansionLanes[0],
                      pExpansionLanes[1],
                      pExpansionLanes[2],
                      pExpansionLanes[3],
                      GSymbol::Var(TwistVariable::kIndex),
                      &aStatements,
                      pErrorMessage)) {
        return false;
    }

    GBatch aBatch;
    aBatch.mExportsAsBlock = false;
    aBatch.CommitStatements(&aStatements);
    pBranch.AddBatch(aBatch);

    return true;
}

} // namespace

bool Builder_Seeder::Build(GTwistExpander *pExpander,
                           std::string *pErrorMessage) {
    
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build received null expander";
        }
        return false;
    }
    
    const GSymbol aSource = GSymbol::Buf(TwistWorkSpaceSlot::kSource);
    
    pExpander->mSeed.AddLine("// [seed]");
    
    
    std::vector<GStatement> aStatements;
    
    std::vector<GSymbol> aFuseLanes;
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneA));
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneB));
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneC));
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneD));
    
    std::vector<GSymbol> aEarthLanes;
    aEarthLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kEarthLaneA));
    aEarthLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kEarthLaneB));
    aEarthLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kEarthLaneC));
    aEarthLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kEarthLaneD));
    
    std::vector<GSymbol> aFireLanes;
    aFireLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFireLaneA));
    aFireLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFireLaneB));
    aFireLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFireLaneC));
    aFireLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFireLaneD));
    
    std::vector<GSymbol> aWindLanes;
    aWindLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWindLaneA));
    aWindLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWindLaneB));
    aWindLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWindLaneC));
    aWindLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWindLaneD));
    
    std::vector<GSymbol> aWaterLanes;
    aWaterLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWaterLaneA));
    aWaterLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWaterLaneB));
    aWaterLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWaterLaneC));
    aWaterLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWaterLaneD));
    
    std::vector<GSymbol> aWorkLanes;
    aWorkLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneA));
    aWorkLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneB));
    aWorkLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneC));
    aWorkLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneD));
    
    std::vector<GSymbol> aExpansionLanes;
    aExpansionLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kExpansionLaneA));
    aExpansionLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kExpansionLaneB));
    aExpansionLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kExpansionLaneC));
    aExpansionLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kExpansionLaneD));
    
    std::vector<GSymbol> aOperationLanes;
    aOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneA));
    aOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneB));
    aOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneC));
    aOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneD));
    
    std::vector<TwistDomain> aDomains;
    aDomains.push_back(TwistDomain::kPhaseA);
    aDomains.push_back(TwistDomain::kPhaseB);
    aDomains.push_back(TwistDomain::kPhaseC);
    aDomains.push_back(TwistDomain::kPhaseD);
    aDomains.push_back(TwistDomain::kPhaseE);
    aDomains.push_back(TwistDomain::kPhaseF);
    aDomains.push_back(TwistDomain::kPhaseG);
    aDomains.push_back(TwistDomain::kPhaseH);

    std::vector<GSymbol> aInvestLanes;
    aInvestLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kInvestA));
    aInvestLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kInvestB));
    aInvestLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kInvestC));
    aInvestLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kInvestD));
    aInvestLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kInvestE));
    aInvestLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kInvestF));
    aInvestLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kInvestG));
    aInvestLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kInvestH));
    
    std::vector<GSymbol> aSnowLanes;
    aSnowLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneA));
    aSnowLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneB));
    aSnowLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneC));
    aSnowLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneD));
    
    std::vector<GSnowType> aSnowTypes;
    aSnowTypes.push_back(GSnowType::kAES);
    aSnowTypes.push_back(GSnowType::kChaCha);
    aSnowTypes.push_back(GSnowType::kSha);
    aSnowTypes.push_back(GSnowType::kAria);
    Random::Shuffle(&aSnowTypes);

    for (std::size_t aSnowIndex = 0U; aSnowIndex < aSnowLanes.size(); ++aSnowIndex) {
        GBatch aSnowBatch;
        aSnowBatch.mExportsAsBlock = false;
        GSnow aSnow;
        
        if (!aSnow.Bake(aSnowTypes[aSnowIndex], aSource, aSnowLanes[aSnowIndex], &aStatements, pErrorMessage)) {
            std::printf("snow bake failed: %s\n", (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "");
            return false;
        }
        aSnowBatch.CommitStatements(&aStatements);
        aStatements.clear();
        pExpander->mSeed.AddBatch(aSnowBatch);
    }

    std::vector<GSymbol> aPhaseSnowLanes = aSnowLanes;
    Random::Shuffle(&aPhaseSnowLanes);
    for (std::size_t aReuseIndex = 0U; aPhaseSnowLanes.size() < aDomains.size(); ++aReuseIndex) {
        aPhaseSnowLanes.push_back(aPhaseSnowLanes[aReuseIndex]);
    }

    for (std::size_t aDomainIndex = 0U; aDomainIndex < aDomains.size(); ++aDomainIndex) {
        const std::string aDomainPartialName = PhaseSubWordName(aDomains[aDomainIndex]);

        AddSeedPhaseHeader(pExpander->mSeed, aDomains[aDomainIndex]);
        
        std::vector<GStatement> aStatementsKDFA;
        GKDF_A aKDF_A;
        aKDF_A.mKDFSnow = aPhaseSnowLanes[aDomainIndex];
        if (!aKDF_A.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kInbuilt,
                         static_cast<int>(aDomainIndex),
                         &aStatementsKDFA,
                         pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake inbuilt KDF:\n" + *pErrorMessage;
            }
            return false;
        }
        for (const GStatement &aStatement : aStatementsKDFA) {
            if (!aStatement.IsRawLine()) {
                continue;
            }
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("");

        std::vector<GStatement> aStatementsFarmA;
        GFarm aFarm;
        if (!aFarm.BakeEphemeral(aWaterLanes[0],
                                 aWaterLanes[1],
                                 aWaterLanes[2],
                                 aWaterLanes[3],
                                 aDomainPartialName,
                                 &aStatementsFarmA,
                                 pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake farm after KDFA:\n" + *pErrorMessage;
            }
            return false;
        }
        
        for (const GStatement &aStatement : aStatementsFarmA) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("");
        
        std::vector<GStatement> aStatementsKDFB;
        GKDF_B aKDF_B;
        if (!aKDF_B.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kEphemeral,
                         static_cast<int>(aDomainIndex),
                         &aStatementsKDFB,
                         pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake inbuilt KDF_B:\n" + *pErrorMessage;
            }
            return false;
        }
        for (const GStatement &aStatement : aStatementsKDFB) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("");

        if (!AddKDFBInvestCapture(pExpander->mSeed,
                                  aExpansionLanes,
                                  aInvestLanes[aDomainIndex],
                                  pErrorMessage)) {
            return false;
        }
        pExpander->mSeed.AddLine("");
        
        
        std::vector<GStatement> aStatementsFarmB;
        if (!aFarm.BakeWorkspace(aExpansionLanes[0],
                                 aExpansionLanes[1],
                                 aExpansionLanes[2],
                                 aExpansionLanes[3],
                                 aDomainPartialName,
                                 &aStatementsFarmB,
                                 pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake farm after KDFA:\n" + *pErrorMessage;
            }
            return false;
        }
        
        
        
        
        for (const GStatement &aStatement : aStatementsFarmB) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }

        AddSeedPhaseFooter(pExpander->mSeed);
    }

    GSquashInvestToKeyBoxes aSquashInvest;
    if (!aSquashInvest.Build(pExpander->mSeed, pErrorMessage)) {
        return false;
    }

    return Build_PostKDF(pExpander, pErrorMessage);
    
}

bool Builder_Seeder::Build_PostKDF(GTwistExpander *pExpander,
                                   std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build_PostKDF received null expander";
        }
        return false;
    }

    std::vector<GSeedRunStageConfig> aStageConfigs = {
        GSeedRunSeedConfig::MakeSeed_AConfig(true),
        GSeedRunSeedConfig::MakeSeed_BConfig(true),
        GSeedRunSeedConfig::MakeSeed_CConfig(true),
        GSeedRunSeedConfig::MakeSeed_DConfig(true),
        GSeedRunSeedConfig::MakeSeed_EConfig(true),
        GSeedRunSeedConfig::MakeSeed_FConfig(true),
        GSeedRunSeedConfig::MakeSeed_GConfig(true),
        GSeedRunSeedConfig::MakeSeed_HConfig(true),
        GSeedRunSeedConfig::MakeSeed_IConfig(true),
    };
    std::vector<TwistDomain> aMatrixDomains;
    if (!GDomainSchedule::AssignShuffledRoundRobin(&aStageConfigs,
                                                   2U,
                                                   &aMatrixDomains)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder failed to assign its domain schedule";
        }
        return false;
    }
    pExpander->mSeedStageConfigs = aStageConfigs;
    pExpander->mSeedMatrixDomains = aMatrixDomains;
    
    std::vector<GSymbol> aInvestLanes;
    aInvestLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kInvestE));
    aInvestLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kInvestF));
    aInvestLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kInvestG));
    aInvestLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kInvestH));
    
    std::vector<GSymbol> aFuseLanes;
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneA));
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneB));
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneC));
    aFuseLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFuseLaneD));
    
    std::vector<GSymbol> aEarthLanes;
    aEarthLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kEarthLaneA));
    aEarthLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kEarthLaneB));
    aEarthLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kEarthLaneC));
    aEarthLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kEarthLaneD));
    
    std::vector<GSymbol> aFireLanes;
    aFireLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFireLaneA));
    aFireLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFireLaneB));
    aFireLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFireLaneC));
    aFireLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kFireLaneD));
    
    std::vector<GSymbol> aWindLanes;
    aWindLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWindLaneA));
    aWindLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWindLaneB));
    aWindLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWindLaneC));
    aWindLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWindLaneD));
    
    std::vector<GSymbol> aWaterLanes;
    aWaterLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWaterLaneA));
    aWaterLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWaterLaneB));
    aWaterLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWaterLaneC));
    aWaterLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWaterLaneD));
    
    std::vector<GSymbol> aWorkLanes;
    aWorkLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneA));
    aWorkLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneB));
    aWorkLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneC));
    aWorkLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneD));
    
    std::vector<GSymbol> aExpansionLanes;
    aExpansionLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kExpansionLaneA));
    aExpansionLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kExpansionLaneB));
    aExpansionLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kExpansionLaneC));
    aExpansionLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kExpansionLaneD));
    
    std::vector<GSymbol> aOperationLanes;
    aOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneA));
    aOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneB));
    aOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneC));
    aOperationLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kOperationLaneD));
    
    std::vector<GSymbol> aSnowLanes;
    aSnowLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kSnowLaneA));
    aSnowLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kSnowLaneB));
    aSnowLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kSnowLaneC));
    aSnowLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kSnowLaneD));

    GSeedRunSeed_A aRunnerSeedA(aStageConfigs[0], true, false);
    if (!BuildSeedStage(pExpander->mSeed, aRunnerSeedA, "GSeedRunSeed_A", pErrorMessage)) {
        return false;
    }
    
    GSeedRunSeed_B aRunnerSeedB(aStageConfigs[1], true, false);
    if (!BuildSeedStage(pExpander->mSeed, aRunnerSeedB, "GSeedRunSeed_B", pErrorMessage)) {
        return false;
    }
    
    GSeedRunSeed_C aRunnerSeedC(aStageConfigs[2], true, false);
    if (!BuildSeedStage(pExpander->mSeed, aRunnerSeedC, "GSeedRunSeed_C", pErrorMessage)) {
        return false;
    }
    
    GSeedRunSeed_D aRunnerSeedD(aStageConfigs[3], true, false);
    if (!BuildSeedStage(pExpander->mSeed, aRunnerSeedD, "GSeedRunSeed_D", pErrorMessage)) {
        return false;
    }
    
    AddSeedMatrixDomainWordLines(pExpander->mSeed, aMatrixDomains[0], true);
    
    for (int i=0;i<4;i+=2) {
        
        GRunMatrixDiffusionConfig aDiffusionA;
        aDiffusionA.mInputA = aFuseLanes[i];
        aDiffusionA.mInputB = aFuseLanes[i + 1];
        aDiffusionA.mOutputA = aFireLanes[i];
        aDiffusionA.mOutputB =  aFireLanes[i + 1];
        
        aDiffusionA.mShuffleEntropyA = aOperationLanes[(i + 2) % 4];
        aDiffusionA.mShuffleEntropyB = aOperationLanes[(i + 3) % 4];
        aDiffusionA.mOperationSourceA = aOperationLanes[(i + 0) % 4];
        aDiffusionA.mOperationSourceB = aOperationLanes[(i + 1) % 4];
        
        aDiffusionA.mUseDomainWords = true;
        
        
        GBatch aBatchDiffusion;
        
        if (!GRunMatrixDiffusion::Bake(aDiffusionA, &aBatchDiffusion, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("error on matrix diffusion for ") + std::string("kdf-a") + ": " + *pErrorMessage;
            }
            return false;
        }
        pExpander->mSeed.AddBatch(aBatchDiffusion);
    }
    
    GSeedRunSeed_E aRunnerSeedE(aStageConfigs[4], true, false);
    if (!BuildSeedStage(pExpander->mSeed, aRunnerSeedE, "GSeedRunSeed_E", pErrorMessage)) {
        return false;
    }

    GSeedRunSeed_F aRunnerSeedF(aStageConfigs[5], true, false);
    if (!BuildSeedStage(pExpander->mSeed, aRunnerSeedF, "GSeedRunSeed_F", pErrorMessage)) {
        return false;
    }
    
    GSeedRunSeed_G aRunnerSeedG(aStageConfigs[6], true, false);
    if (!BuildSeedStage(pExpander->mSeed, aRunnerSeedG, "GSeedRunSeed_G", pErrorMessage)) {
        return false;
    }

    GSeedRunSeed_H aRunnerSeedH(aStageConfigs[7], true, false);
    if (!BuildSeedStage(pExpander->mSeed, aRunnerSeedH, "GSeedRunSeed_H", pErrorMessage)) {
        return false;
    }
    
    AddSeedMatrixDomainWordLines(pExpander->mSeed, aMatrixDomains[1], false);
    
    pExpander->mSeed.AddLine("//");
    
    for (int i=0;i<4;i+=2) {
        
        GRunMatrixDiffusionConfig aDiffusionA;
        aDiffusionA.mInputA = aFuseLanes[i];
        aDiffusionA.mInputB = aFuseLanes[i + 1];
        aDiffusionA.mOutputA = aInvestLanes[i];
        aDiffusionA.mOutputB =  aInvestLanes[i + 1];
        
        aDiffusionA.mShuffleEntropyA = aOperationLanes[(i + 2) % 4];
        aDiffusionA.mShuffleEntropyB = aOperationLanes[(i + 3) % 4];
        aDiffusionA.mOperationSourceA = aOperationLanes[(i + 0) % 4];
        aDiffusionA.mOperationSourceB = aOperationLanes[(i + 1) % 4];
        
        aDiffusionA.mUseDomainWords = true;
        
        GBatch aBatchDiffusion;
        
        if (!GRunMatrixDiffusion::Bake(aDiffusionA, &aBatchDiffusion, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("error on matrix diffusion for ") + std::string("kdf-a") + ": " + *pErrorMessage;
            }
            return false;
        }
        pExpander->mSeed.AddBatch(aBatchDiffusion);
    }
    
    

    GSeedRunSeed_I aRunnerSeedI(aStageConfigs[8], true, false);
    if (!BuildSeedStage(pExpander->mSeed, aRunnerSeedI, "GSeedRunSeed_I", pErrorMessage)) {
        return false;
    }
    
    std::vector<GStatement> aStatementsSquash;
    GSymbol aIndex = GSymbol::Var(TwistVariable::kIndex);
    GSquash aSquash;
    if (!aSquash.Bake(GSymbol::Var(TwistVariable::kParamOutput),
                      aWorkLanes[0],
                      aWorkLanes[1],
                      aWorkLanes[2],
                      aWorkLanes[3],
                      
                      aIndex,
                      
                      &aStatementsSquash,
                      pErrorMessage)) {
        return false;
    }
    
    GBatch aFinishBatch;
    aFinishBatch.mExportsAsBlock = false;
    aFinishBatch.CommitStatements(&aStatementsSquash);
    pExpander->mSeed.AddBatch(aFinishBatch);
    
    return true;
}
