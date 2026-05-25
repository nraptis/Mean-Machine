//
//  Builder_Seeder.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Seeder.hpp"
#include "GFarmConstants.hpp"
#include "GKDF.hpp"
#include "GTwistExpander.hpp"

namespace {

void AddFarmSaltRound(const std::string &pSource,
                      const std::string &pRound,
                      std::vector<GStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }

    pStatements->push_back(GStatement::RawLine(
        "pFarmSalt->Derive(" + pSource + ",\n"
        "                  " + pRound + ".mSaltA,\n"
        "                  " + pRound + ".mSaltB,\n"
        "                  " + pRound + ".mSaltC,\n"
        "                  " + pRound + ".mSaltD,\n"
        "                  " + pRound + ".mSaltE,\n"
        "                  " + pRound + ".mSaltF);"));
}

void AddFarmSBoxes(const std::string &pSource,
                   const std::string &pSBoxes,
                   std::vector<GStatement> *pStatements) {
    if (pStatements == nullptr) {
        return;
    }

    pStatements->push_back(GStatement::RawLine(
        "pFarmSBox->Derive(" + pSource + ",\n"
        "                  " + pSBoxes + ".mSBoxA,\n"
        "                  " + pSBoxes + ".mSBoxB,\n"
        "                  " + pSBoxes + ".mSBoxC,\n"
        "                  " + pSBoxes + ".mSBoxD,\n"
        "                  " + pSBoxes + ".mSBoxE,\n"
        "                  " + pSBoxes + ".mSBoxF,\n"
        "                  " + pSBoxes + ".mSBoxG,\n"
        "                  " + pSBoxes + ".mSBoxH);"));
}

bool AddFarmPhaseA(const std::string &pBundle,
                   std::vector<GStatement> *pStatements,
                   std::string *pErrorMessage) {
    AddFarmSaltRound("aWorkLaneF",
                     pBundle + ".mPhaseASalts.mOrbiterAssign",
                     pStatements);
    AddFarmSaltRound("aWorkLaneE",
                     pBundle + ".mPhaseASalts.mOrbiterUpdate",
                     pStatements);
    AddFarmSaltRound("aWorkLaneD",
                     pBundle + ".mPhaseASalts.mWandererUpdate",
                     pStatements);
    AddFarmSBoxes("aWorkLaneC",
                  pBundle + ".mPhaseASBoxes",
                  pStatements);

    GFarmConstants aFarmConstants;
    return aFarmConstants.Bake("aWorkLaneB",
                               pBundle + ".mPhaseAConstants",
                               pStatements,
                               pErrorMessage);
}

} // namespace

bool Builder_Seeder::Build(GTwistExpander *pExpander,
                           std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build received null expander";
        }
        return false;
    }

    pExpander->mSeed.AddLine("// [seed]");

    std::vector<GStatement> aStatements;
    std::string aError;

    GKDF_A aKDF_A;
    if (!aKDF_A.Bake(TwistDomain::kPhaseA,
                     "aSource",
                     "aMaskLaneA",
                     GKDFMaterialBundle::kInbuilt,
                     &aStatements,
                     &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build failed to bake inbuilt KDF:\n" + aError;
        }
        return false;
    }

    
    /*
    if (!AddFarmPhaseA("mDomainBundleEphemeral", &aStatements, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build failed to bake ephemeral farm constants:\n" + aError;
        }
        return false;
    }

    GKDF_B aKDF_B;
    if (!aKDF_B.Bake(TwistDomain::kPhaseA,
                     "aMaskLaneA",
                     "aMaskLaneB",
                     GKDFMaterialBundle::kEphemeral,
                     &aStatements,
                     &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build failed to bake ephemeral KDF:\n" + aError;
        }
        return false;
    }

    if (!AddFarmPhaseA("pWorkspace->mDomainBundle", &aStatements, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder::Build failed to bake workspace farm constants:\n" + aError;
        }
        return false;
    }
    */

    for (const GStatement &aStatement : aStatements) {
        if (!aStatement.IsRawLine()) {
            continue;
        }
        pExpander->mSeed.AddLine(aStatement.mRawLine);
    }
    

    return true;
}
