//
//  Builder_GrowB.cpp
//  MeanMachine
//
//  Created by icarus black on 7/13/26.
//

#include "Builder_GrowB.hpp"
#include "GKeyFoldA.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunGrowKeyA.hpp"

bool Builder_GrowB::Build(GTwistExpander *pExpander,
                          std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowB::Build received null expander";
        }
        return false;
    }

    pExpander->mGrowKeyB.AddLine("// [grow key b]");

    GTwistRunGrowKeyB aRunner;
    if (!aRunner.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowB::Build failed to plan GTwistRunGrowKeyB:\n" +
                *pErrorMessage;
        }
        return false;
    }
    if (!aRunner.Build(pExpander->mGrowKeyB, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowB::Build failed to build GTwistRunGrowKeyB:\n" +
                *pErrorMessage;
        }
        return false;
    }

    GKeyFoldA aKeyFold;
    if (!aKeyFold.BakeGrowKeyB(pExpander->mGrowKeyB, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowB::Build failed to bake GKeyFoldA grow key B:\n" +
                *pErrorMessage;
        }
        return false;
    }

    return true;
}
