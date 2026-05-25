//
//  Builder_Twister.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_Twister.hpp"
#include "GTwistExpander.hpp"

bool Builder_Twister::Build(GTwistExpander *pExpander,
                            std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }

    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_Twister::Build received null expander";
        }
        return false;
    }

    pExpander->mTwister.AddLine("// [twister]");

    return true;
}
