//
//  Builder.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include <cstdio>
#include <sstream>
#include <iomanip>

#include "Builder.hpp"

#include "Builder_KDF.hpp"
#include "Builder_Seeder.hpp"
#include "Builder_Twister.hpp"
#include "Builder_GrowA.hpp"
#include "Builder_GrowB.hpp"
#include "GPrintTool.hpp"
#include "GTwistExpander.hpp"

#include <sstream>
#include <iomanip>

std::string Builder::MakeNameBase(const std::string &pFilePrefix,
                                  int pTrialNumber,
                                  int pLeadingZeros) {
    std::ostringstream aStream;

    aStream << pFilePrefix << "_"
            << std::setw(pLeadingZeros)
            << std::setfill('0')
            << pTrialNumber;

    return aStream.str();
}

bool Builder::Go(const std::string &pOutputRoot,
                 const std::string &pFilePrefix,
                 int pTrialNumber,
                 int pLeadingZeros,
                 std::string *pErrorMessage) {
    return Builder::Go(pOutputRoot,
                       pFilePrefix,
                       pTrialNumber,
                       pLeadingZeros,
                       false,
                       pErrorMessage);
}

bool Builder::Go(const std::string &pOutputRoot,
                 const std::string &pFilePrefix,
                 int pTrialNumber,
                 int pLeadingZeros,
                 bool pUseSnapShotter,
                 std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    GPrintTool::Reset();

    GTwistExpander aExpander;
    aExpander.mNameBase = pFilePrefix;
    
    /*
    MakeNameBase(pFilePrefix,
                                       pTrialNumber,
                                       pLeadingZeros);
    */

    std::string aError;

    Builder_KDF aKDFBuilder;
    if (!aKDFBuilder.Build(&aExpander, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_KDF failed:\n" + aError;
        }
        return false;
    }

    Builder_Seeder aSeederBuilder;
    if (!aSeederBuilder.Build(&aExpander, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Seeder failed:\n" + aError;
        }
        return false;
    }

    Builder_Twister aTwisterBuilder;
    if (!aTwisterBuilder.Build(&aExpander, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister failed:\n" + aError;
        }
        return false;
    }

    Builder_GrowA aGrowABuilder;
    if (!aGrowABuilder.Build(&aExpander, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowA failed:\n" + aError;
        }
        return false;
    }

    Builder_GrowB aGrowBBuilder;
    if (!aGrowBBuilder.Build(&aExpander, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowB failed:\n" + aError;
        }
        return false;
    }

    if (!aExpander.ExportCPPProjectRoot(pOutputRoot, pUseSnapShotter, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "ExportCPPProjectRoot failed:\n" + aError;
        }
        return false;
    }

    return true;
}
