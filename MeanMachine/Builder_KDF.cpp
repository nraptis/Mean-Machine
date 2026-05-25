//
//  Builder_KDF.cpp
//  MeanMachine
//
//  Created by nicholas on 5/23/26.
//

#include "Builder_KDF.hpp"


#include <cstring>
#include <cstdint>
#include <string>
#include <vector>

#include "TwistWorkSpace.hpp"
#include "Random.hpp"
#include "GTwistExpander.hpp"
#include "GSeedRunKDF2.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "GAXSK.hpp"

namespace {

bool BuildKDFBranch(TwistProgramBranch &pBranch,
                    const char *pLabel,
                    std::string *pErrorMessage) {
    GSeedRunKDF2 aKDF;
    std::string aError;

    if (!aKDF.Plan(&aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GSeedRunKDF2.Plan for ") + pLabel + "\n" + aError;
        }
        return false;
    }

    if (!aKDF.Build(pBranch, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GSeedRunKDF2.Build for ") + pLabel + "\n" + aError;
        }
        return false;
    }

    if (pBranch.GetBatchJsonText().empty() &&
        pBranch.GetStringLines().empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("kdf branch export was empty for ") + pLabel + " (no batches and no lines)";
        }
        return false;
    }

    /*
    GRunMatrixDiffusionConfig aDiffusionA;
    aDiffusionA.mInputA = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
    aDiffusionA.mInputB = BufSymbol(TwistWorkSpaceSlot::kWorkLaneC);

    aDiffusionA.mOutputA = BufSymbol(TwistWorkSpaceSlot::kExpansionLaneA);
    aDiffusionA.mOutputB = BufSymbol(TwistWorkSpaceSlot::kExpansionLaneB);

    aDiffusionA.mShuffleEntropyA = BufSymbol(TwistWorkSpaceSlot::kOperationLaneA);
    aDiffusionA.mShuffleEntropyB = BufSymbol(TwistWorkSpaceSlot::kOperationLaneB);
    aDiffusionA.mShuffleEntropyC = BufSymbol(TwistWorkSpaceSlot::kOperationLaneC);
    aDiffusionA.mShuffleEntropyD = BufSymbol(TwistWorkSpaceSlot::kOperationLaneD);

    aDiffusionA.mOperationSourceA = BufSymbol(TwistWorkSpaceSlot::kOperationLaneE);
    aDiffusionA.mOperationSourceB = BufSymbol(TwistWorkSpaceSlot::kOperationLaneF);

    GBatch aBatch;
    aBatch.AddComment(std::string(pLabel) + "-matrix-diffusion: workA/workC -> expansionA/expansionB");

    if (!GRunMatrixDiffusion::Bake(aDiffusionA, &aBatch, &aError)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on matrix diffusion for ") + pLabel + ": " + aError;
        }
        return false;
    }

    pBranch.AddBatch(aBatch);
     
    */
     
    return true;
}

} // namespace

bool Builder_KDF::Build(GTwistExpander *pExpander,
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

    if (!BuildKDFBranch(pExpander->mKDF_A, "kdf-a", pErrorMessage)) {
        return false;
    }
    if (!BuildKDFBranch(pExpander->mKDF_B, "kdf-b", pErrorMessage)) {
        return false;
    }
    pExpander->mKDF = pExpander->mKDF_A;

    return true;
}
