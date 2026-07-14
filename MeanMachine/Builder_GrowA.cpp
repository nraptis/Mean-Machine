//
//  Builder_GrowA.cpp
//  MeanMachine
//
//  Created by icarus black on 7/13/26.
//

#include "Builder_GrowA.hpp"
#include "GKeyFoldA.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunGrowKeyA.hpp"

bool Builder_GrowA::Build(GTwistExpander *pExpander,
                          std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowA::Build received null expander";
        }
        return false;
    }

    pExpander->mGrowKeyA.AddLine("// [grow key a]");

    GTwistRunGrowKeyA aRunner;
    if (!aRunner.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowA::Build failed to plan GTwistRunGrowKeyA:\n" +
                *pErrorMessage;
        }
        return false;
    }
    if (!aRunner.Build(pExpander->mGrowKeyA, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowA::Build failed to build GTwistRunGrowKeyA:\n" +
                *pErrorMessage;
        }
        return false;
    }

    GKeyFoldA aKeyFold;
    if (!aKeyFold.BakeGrowKeyA(pExpander->mGrowKeyA, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowA::Build failed to bake GKeyFoldA grow key A:\n" +
                *pErrorMessage;
        }
        return false;
    }

    return true;
}
