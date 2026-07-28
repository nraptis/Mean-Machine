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

#include "GRunMatrixDiffusion.hpp"
#include "Random.hpp"

#include "stdafx.hpp"

#include <array>
#include <sstream>

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

const char *PhaseDisplayName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kKeyRotateA: return "KeyRotate A";
        case TwistDomain::kKeyRotateB: return "KeyRotate B";
        case TwistDomain::kKeySpawnA: return "KeySpawn A";
        case TwistDomain::kKeySpawnB: return "KeySpawn B";
        case TwistDomain::kSeed: return "Seed";
        case TwistDomain::kTwist: return "Twist";
        default:
            return "Invalid";
    }
}

const char *DomainLaneMemberName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kKeyRotateA:
            return "mDomainLaneKeyRotateA";
        case TwistDomain::kKeyRotateB:
            return "mDomainLaneKeyRotateB";
        case TwistDomain::kKeySpawnA:
            return "mDomainLaneKeySpawnA";
        case TwistDomain::kKeySpawnB:
            return "mDomainLaneKeySpawnB";
        case TwistDomain::kSeed:
            return "mDomainLaneSeed";
        case TwistDomain::kTwist:
            return "mDomainLaneTwist";
        default:
            return "";
    }
}

const char *DomainSquashName(const TwistDomain pDomain) {
    switch (pDomain) {
        case TwistDomain::kKeySpawnA:
            return "SquashB";
        case TwistDomain::kKeyRotateB:
        case TwistDomain::kTwist:
            return "SquashA";
        case TwistDomain::kKeySpawnB:
        case TwistDomain::kSeed:
        case TwistDomain::kKeyRotateA:
        default:
            return "SquashC";
    }
}

std::string UInt64Literal(const std::uint64_t pValue) {
    std::ostringstream aStream;
    aStream << "0x" << std::uppercase << std::hex << pValue << "ULL";
    return aStream.str();
}

void AddKDFStateReset(TwistProgramBranch &pBranch,
                      const std::string &pPurpose) {
    static constexpr std::array<const char *, 14> kStateNames = {
        "aPrevious",
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

    pBranch.AddLine("// Reset ARX state for " + pPurpose + ".");
    for (const char *aStateName : kStateNames) {
        pBranch.AddLine(
            std::string(aStateName) + " = " +
            UInt64Literal(Random::Get64High()) + ";"
        );
    }
    pBranch.AddLine("");
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

} // namespace

bool Builder_Seeder::Build(GTwistExpander *pExpander,
                           ResidualBucket &pResidualBucket,
                           std::string *pErrorMessage) {

    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build received null expander";
        }
        return false;
    }

    pExpander->mSeed.AddLine("// [seed]");

    std::vector<GSymbol> aPoisonLanes;
    aPoisonLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA));
    aPoisonLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPoisonLaneB));
    aPoisonLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPoisonLaneC));
    aPoisonLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPoisonLaneD));

    std::vector<GSymbol> aHeartLanes;
    aHeartLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kHeartLaneA));
    aHeartLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kHeartLaneB));
    aHeartLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kHeartLaneC));
    aHeartLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kHeartLaneD));

    std::vector<GSymbol> aWoodLanes;
    aWoodLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWoodLaneA));
    aWoodLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWoodLaneB));
    aWoodLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWoodLaneC));
    aWoodLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWoodLaneD));

    std::vector<GSymbol> aCrystalLanes;
    aCrystalLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCrystalLaneA));
    aCrystalLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCrystalLaneB));
    aCrystalLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCrystalLaneC));
    aCrystalLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCrystalLaneD));

    std::vector<TwistDomain> aDomains;
    aDomains.push_back(TwistDomain::kKeyRotateA);
    aDomains.push_back(TwistDomain::kKeyRotateB);
    aDomains.push_back(TwistDomain::kKeySpawnA);
    aDomains.push_back(TwistDomain::kKeySpawnB);
    aDomains.push_back(TwistDomain::kTwist);
    aDomains.push_back(TwistDomain::kSeed);

    std::vector<GSymbol> aSnowLanes;
    aSnowLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneA));
    aSnowLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneB));
    aSnowLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneC));
    aSnowLanes.push_back(GSymbol::Buf(TwistWorkSpaceSlot::kSnowLaneD));

    const std::array<GSymbol, 3> aKDFSnowLanes = {
        aSnowLanes[0],
        aSnowLanes[1],
        aSnowLanes[2],
    };

    for (std::size_t aDomainIndex = 0U; aDomainIndex < aDomains.size(); ++aDomainIndex) {
        const std::string aDomainPartialName = PhaseSubWordName(aDomains[aDomainIndex]);

        AddSeedPhaseHeader(pExpander->mSeed, aDomains[aDomainIndex]);
        AddKDFStateReset(
            pExpander->mSeed,
            PhaseDisplayName(aDomains[aDomainIndex])
        );

        std::vector<GStatement> aStatementsKDFA;
        GKDF_A aKDF_A;
        aKDF_A.mKDFSnowLanes = aKDFSnowLanes;
        if (!aKDF_A.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kInbuilt,
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
        pExpander->mSeed.AddLine("////////");

        std::vector<GStatement> aStatementsFarmA;
        GFarm aFarm;
        if (!aFarm.BakeEphemeral(aHeartLanes[0],
                                 aHeartLanes[1],
                                 aHeartLanes[2],
                                 aHeartLanes[3],
                                 aDomainPartialName,
                                 &aStatementsFarmA,
                                 pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake farm after KDFA:\n" + *pErrorMessage;
            }
            return false;
        }

        for (std::size_t aStatementIndex = 0U;
             aStatementIndex < aStatementsFarmA.size();
             ++aStatementIndex) {
            if ((aStatementIndex + 1U) == aStatementsFarmA.size()) {
                pExpander->mSeed.AddLine("////////");
            }
            pExpander->mSeed.AddLine(aStatementsFarmA[aStatementIndex].mRawLine);
        }
        pExpander->mSeed.AddLine("////////");

        std::vector<GStatement> aStatementsKDFB;
        GKDF_B aKDF_B;
        aKDF_B.mKDFSnowLanes = aKDFSnowLanes;
        if (!aKDF_B.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kEphemeral,
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
        pExpander->mSeed.AddLine("////////");

        //
        // KDF_B wood lanes -> workspace domain material.
        //
        std::vector<GStatement> aStatementsFarmAfterKDFB;
        if (!aFarm.BakeWorkspace(aWoodLanes[0],
                                 aWoodLanes[1],
                                 aWoodLanes[2],
                                 aWoodLanes[3],
                                 aDomainPartialName,
                                 &aStatementsFarmAfterKDFB,
                                 pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_Seeder::Build failed to derive workspace "
                    "material after KDF_B:\n" + *pErrorMessage;
            }
            return false;
        }
        pExpander->mSeed.AddLine(
            "// wood lanes to pWorkSpace->mDomainBundle"
        );
        for (const GStatement &aStatement :
             aStatementsFarmAfterKDFB) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("////////");

        std::vector<GStatement> aStatementsKDFC;
        GKDF_C aKDF_C;
        aKDF_C.mKDFSnowLanes = aKDFSnowLanes;
        if (!aKDF_C.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kEphemeral,
                         &aStatementsKDFC,
                         pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake KDF_C:\n" + *pErrorMessage;
            }
            return false;
        }
        for (const GStatement &aStatement : aStatementsKDFC) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("////////");

        //
        // KDF_C crystal lanes -> ephemeral domain material.
        //
        std::vector<GStatement> aStatementsFarmAfterKDFC;
        if (!aFarm.BakeEphemeral(aCrystalLanes[0],
                                 aCrystalLanes[1],
                                 aCrystalLanes[2],
                                 aCrystalLanes[3],
                                 aDomainPartialName,
                                 &aStatementsFarmAfterKDFC,
                                 pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_Seeder::Build failed to derive ephemeral "
                    "material after KDF_C:\n" + *pErrorMessage;
            }
            return false;
        }
        pExpander->mSeed.AddLine(
            "// crystal lanes to mDomainBundleEphemeral"
        );
        for (const GStatement &aStatement :
             aStatementsFarmAfterKDFC) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("////////");

        std::vector<GStatement> aStatementsKDFD;
        GKDF_D aKDF_D;
        aKDF_D.mKDFSnowLanes = aKDFSnowLanes;
        if (!aKDF_D.Bake(aDomains[aDomainIndex],
                         GKDFMaterialBundle::kEphemeral,
                         &aStatementsKDFD,
                         pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Builder_Seeder::Build failed to bake KDF_D:\n" + *pErrorMessage;
            }
            return false;
        }
        for (const GStatement &aStatement : aStatementsKDFD) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("////////");

        //
        // KDF_D poison lanes -> final workspace domain material.
        //
        std::vector<GStatement> aStatementsFarmAfterKDFD;
        if (!aFarm.BakeWorkspace(aPoisonLanes[0],
                                 aPoisonLanes[1],
                                 aPoisonLanes[2],
                                 aPoisonLanes[3],
                                 aDomainPartialName,
                                 &aStatementsFarmAfterKDFD,
                                 pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "Builder_Seeder::Build failed to derive final workspace "
                    "material after KDF_D:\n" + *pErrorMessage;
            }
            return false;
        }

        pExpander->mSeed.AddLine(
            "// poison lanes to pWorkSpace->mDomainBundle"
        );
        for (const GStatement &aStatement :
             aStatementsFarmAfterKDFD) {
            pExpander->mSeed.AddLine(aStatement.mRawLine);
        }
        pExpander->mSeed.AddLine("////////");
        pExpander->mSeed.AddLine(
            std::string("TwistSquash::") +
            DomainSquashName(aDomains[aDomainIndex]) +
            "(aPoisonLaneA, aPoisonLaneB, aPoisonLaneC, aPoisonLaneD, "
            "pWorkSpace->" +
            DomainLaneMemberName(aDomains[aDomainIndex]) +
            ");"
        );
        pExpander->mSeed.AddLine("////////");

        AddSeedPhaseFooter(pExpander->mSeed);
    }

    AddKDFStateReset(pExpander->mSeed, "Seed stages");

    return Build_PostKDF(pExpander,
                         pResidualBucket,
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
                                           pResidualBucket);
    std::vector<GSeedRunStageConfig> aStageConfigs(
        aBuiltStageConfigs.begin(),
        aBuiltStageConfigs.end());
    pExpander->mSeedStageConfigs = aStageConfigs;
    pExpander->mSeedMatrixDomains.assign(4U, TwistDomain::kSeed);

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

    std::vector<GSymbol> aIceLanes;
    aIceLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kIceLaneA));
    aIceLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kIceLaneB));
    aIceLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kIceLaneC));
    aIceLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kIceLaneD));

    std::vector<GSymbol> aHeartLanes;
    aHeartLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kHeartLaneA));
    aHeartLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kHeartLaneB));
    aHeartLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kHeartLaneC));
    aHeartLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kHeartLaneD));

    std::vector<GSymbol> aLightningLanes;
    aLightningLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kLightningLaneA));
    aLightningLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kLightningLaneB));
    aLightningLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kLightningLaneC));
    aLightningLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kLightningLaneD));

    std::vector<GSymbol> aPlasmaLanes;
    aPlasmaLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPlasmaLaneA));
    aPlasmaLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPlasmaLaneB));
    aPlasmaLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPlasmaLaneC));
    aPlasmaLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPlasmaLaneD));

    std::vector<GSymbol> aMagmaLanes;
    aMagmaLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kMagmaLaneA));
    aMagmaLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kMagmaLaneB));
    aMagmaLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kMagmaLaneC));
    aMagmaLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kMagmaLaneD));

    std::vector<GSymbol> aCrystalLanes;
    aCrystalLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCrystalLaneA));
    aCrystalLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCrystalLaneB));
    aCrystalLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCrystalLaneC));
    aCrystalLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCrystalLaneD));

    std::vector<GSymbol> aAetherLanes;
    aAetherLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kAetherLaneA));
    aAetherLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kAetherLaneB));
    aAetherLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kAetherLaneC));
    aAetherLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kAetherLaneD));

    std::vector<GSymbol> aCelestialLanes;
    aCelestialLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCelestialLaneA));
    aCelestialLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCelestialLaneB));
    aCelestialLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCelestialLaneC));
    aCelestialLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kCelestialLaneD));

    std::vector<GSymbol> aWoodLanes;
    aWoodLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWoodLaneA));
    aWoodLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWoodLaneB));
    aWoodLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWoodLaneC));
    aWoodLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kWoodLaneD));

    std::vector<GSymbol> aPoisonLanes;
    aPoisonLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPoisonLaneA));
    aPoisonLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPoisonLaneB));
    aPoisonLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPoisonLaneC));
    aPoisonLanes.push_back(BufSymbol(TwistWorkSpaceSlot::kPoisonLaneD));



    for (std::size_t i = 0U; i < 3U; ++i) {
        const std::string aStageName =
            "GSeedRunSeed_" + std::string(1, static_cast<char>('A' + i));
        if (!BuildSeedStage(pExpander->mSeed,
                            aStageConfigs[i],
                            true,
                            false,
                            aStageName.c_str(),
                            pErrorMessage)) {
            return false;
        }
    }

    pExpander->mSeed.AddLine("//");
    AddSeedMatrixDomainWordLines(pExpander->mSeed);
    pExpander->mSeed.AddLine("//");

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
    //   Plasma C, Plasma D, Magma A, Magma B, Magma C, Magma D
    aDiffusionA.mShuffleEntropyA = aPlasmaLanes[2];
    aDiffusionA.mShuffleEntropyB = aPlasmaLanes[3];
    aDiffusionA.mShuffleEntropyC = aMagmaLanes[2];
    aDiffusionA.mShuffleEntropyD = aMagmaLanes[3];
    aDiffusionA.mOperationSourceA = aMagmaLanes[0];
    aDiffusionA.mOperationSourceB = aMagmaLanes[1];

    GBatch aBatchDiffusionA;
    if (!GRunMatrixDiffusion::Bake(aDiffusionA,
                                   &aBatchDiffusionA,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on first matrix diffusion for seed: ") + *pErrorMessage;
        }
        return false;
    }
    pExpander->mSeed.AddBatch(aBatchDiffusionA);

    for (std::size_t i = 3U; i < 6U; ++i) {
        const std::string aStageName =
            "GSeedRunSeed_" + std::string(1, static_cast<char>('A' + i));
        if (!BuildSeedStage(pExpander->mSeed,
                            aStageConfigs[i],
                            true,
                            false,
                            aStageName.c_str(),
                            pErrorMessage)) {
            return false;
        }
    }

    pExpander->mSeed.AddLine("//");

    GRunMatrixDiffusionConfig aDiffusionB;
    aDiffusionB.mInputA = aFuseLanes[0];
    aDiffusionB.mInputB = aFuseLanes[1];
    aDiffusionB.mInputC = aFuseLanes[2];
    aDiffusionB.mInputD = aFuseLanes[3];
    aDiffusionB.mOutputA = aWindLanes[0];
    aDiffusionB.mOutputB = aWindLanes[1];
    aDiffusionB.mOutputC = aWindLanes[2];
    aDiffusionB.mOutputD = aWindLanes[3];

    // Previous six:
    //   Crystal C, Crystal D, Earth A, Earth B, Earth C, Earth D
    aDiffusionB.mShuffleEntropyA = aCrystalLanes[2];
    aDiffusionB.mShuffleEntropyB = aCrystalLanes[3];
    aDiffusionB.mShuffleEntropyC = aEarthLanes[2];
    aDiffusionB.mShuffleEntropyD = aEarthLanes[3];
    aDiffusionB.mOperationSourceA = aEarthLanes[0];
    aDiffusionB.mOperationSourceB = aEarthLanes[1];

    GBatch aBatchDiffusionB;
    if (!GRunMatrixDiffusion::Bake(aDiffusionB,
                                   &aBatchDiffusionB,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on second matrix diffusion for seed: ") + *pErrorMessage;
        }
        return false;
    }
    pExpander->mSeed.AddBatch(aBatchDiffusionB);

    for (std::size_t i = 6U; i < 9U; ++i) {
        const std::string aStageName =
            "GSeedRunSeed_" + std::string(1, static_cast<char>('A' + i));
        if (!BuildSeedStage(pExpander->mSeed,
                            aStageConfigs[i],
                            true,
                            false,
                            aStageName.c_str(),
                            pErrorMessage)) {
            return false;
        }
    }

    pExpander->mSeed.AddLine("//");

    GRunMatrixDiffusionConfig aDiffusionC;
    aDiffusionC.mInputA = aFuseLanes[0];
    aDiffusionC.mInputB = aFuseLanes[1];
    aDiffusionC.mInputC = aFuseLanes[2];
    aDiffusionC.mInputD = aFuseLanes[3];
    aDiffusionC.mOutputA = aCelestialLanes[0];
    aDiffusionC.mOutputB = aCelestialLanes[1];
    aDiffusionC.mOutputC = aCelestialLanes[2];
    aDiffusionC.mOutputD = aCelestialLanes[3];
    // Previous six:
    //   Aether C, Aether D, Fire A, Fire B, Fire C, Fire D
    aDiffusionC.mShuffleEntropyA = aAetherLanes[2];
    aDiffusionC.mShuffleEntropyB = aAetherLanes[3];
    aDiffusionC.mShuffleEntropyC = aFireLanes[2];
    aDiffusionC.mShuffleEntropyD = aFireLanes[3];
    aDiffusionC.mOperationSourceA = aFireLanes[0];
    aDiffusionC.mOperationSourceB = aFireLanes[1];

    GBatch aBatchDiffusionC;
    if (!GRunMatrixDiffusion::Bake(aDiffusionC,
                                   &aBatchDiffusionC,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "error on third matrix diffusion for seed: " +
                *pErrorMessage;
        }
        return false;
    }
    pExpander->mSeed.AddBatch(aBatchDiffusionC);

    for (std::size_t i = 9U; i < 12U; ++i) {
        const std::string aStageName =
            "GSeedRunSeed_" + std::string(1, static_cast<char>('A' + i));
        if (!BuildSeedStage(pExpander->mSeed,
                            aStageConfigs[i],
                            true,
                            false,
                            aStageName.c_str(),
                            pErrorMessage)) {
            return false;
        }
    }

    pExpander->mSeed.AddLine("//");

    GRunMatrixDiffusionConfig aDiffusionD;
    aDiffusionD.mInputA = aFuseLanes[0];
    aDiffusionD.mInputB = aFuseLanes[1];
    aDiffusionD.mInputC = aFuseLanes[2];
    aDiffusionD.mInputD = aFuseLanes[3];
    aDiffusionD.mOutputA = aWoodLanes[0];
    aDiffusionD.mOutputB = aWoodLanes[1];
    aDiffusionD.mOutputC = aWoodLanes[2];
    aDiffusionD.mOutputD = aWoodLanes[3];
    // Previous six:
    //   Lightning C, Lightning D, Ice A, Ice B, Ice C, Ice D
    aDiffusionD.mShuffleEntropyA = aLightningLanes[2];
    aDiffusionD.mShuffleEntropyB = aLightningLanes[3];
    aDiffusionD.mShuffleEntropyC = aIceLanes[2];
    aDiffusionD.mShuffleEntropyD = aIceLanes[3];
    aDiffusionD.mOperationSourceA = aIceLanes[0];
    aDiffusionD.mOperationSourceB = aIceLanes[1];

    GBatch aBatchDiffusionD;
    if (!GRunMatrixDiffusion::Bake(aDiffusionD,
                                   &aBatchDiffusionD,
                                   pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "error on fourth matrix diffusion for seed: " +
                *pErrorMessage;
        }
        return false;
    }
    pExpander->mSeed.AddBatch(aBatchDiffusionD);

    for (std::size_t i = 12U; i < 14U; ++i) {
        const std::string aStageName =
            "GSeedRunSeed_" + std::string(1, static_cast<char>('A' + i));
        if (!BuildSeedStage(pExpander->mSeed,
                            aStageConfigs[i],
                            true,
                            false,
                            aStageName.c_str(),
                            pErrorMessage)) {
            return false;
        }
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
    pExpander->mSeed.AddLine("// [KEY — sixteen key rows, lane splits A-P]");
    pExpander->mSeed.AddLine("//");
    GSeedRunKEY aKeyBox(aKeyBoxConfigs[0]);
    if (!aKeyBox.Plan(pErrorMessage) ||
        !aKeyBox.Build(pExpander->mSeed, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Builder_Seeder failed on GSeedRunKEY:\n" +
                *pErrorMessage;
        }
        return false;
    }
    return true;
}
