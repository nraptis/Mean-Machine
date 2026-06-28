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
#include "GSeedRunKDF_A.hpp"
#include "GSeedRunKDF_B.hpp"

#include "GRunMatrixDiffusion.hpp"
namespace {

template <typename Runner>
bool BuildKDFStage(TwistProgramBranch &pBranch,
                   const char *pStageName,
                   const char *pBranchName,
                   std::string *pErrorMessage) {
    Runner aRunner;

    if (!aRunner.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on ") + pStageName + ".Plan for " +
                pBranchName + "\n" + *pErrorMessage;
        }
        return false;
    }

    if (!aRunner.Build(pBranch, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on ") + pStageName + ".Build for " +
                pBranchName + "\n" + *pErrorMessage;
        }
        return false;
    }

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
    
    if (!BuildKDFStage<GSeedRunKDF_A_A>(pExpander->mKDF_A,
                                        "GSeedRunKDF_A_A",
                                        "kdf-a",
                                        pErrorMessage)) {
        return false;
    }

    if (!BuildKDFStage<GSeedRunKDF_A_B>(pExpander->mKDF_A,
                                        "GSeedRunKDF_A_B",
                                        "kdf-a",
                                        pErrorMessage)) {
        return false;
    }

    if (!BuildKDFStage<GSeedRunKDF_A_C>(pExpander->mKDF_A,
                                        "GSeedRunKDF_A_C",
                                        "kdf-a",
                                        pErrorMessage)) {
        return false;
    }

    if (pExpander->mKDF_A.GetBatchJsonText().empty() &&
        pExpander->mKDF_A.GetStringLines().empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("kdf branch export was empty for ") + std::string("kdf-a") + " (no batches and no lines)";
        }
        return false;
    }
    
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
    
    
    for (int i=0;i<4;i+=2) {
        
        GRunMatrixDiffusionConfig aDiffusionA;
        aDiffusionA.mInputA = aWorkLanes[i];
        aDiffusionA.mInputB = aWorkLanes[i + 1];
        aDiffusionA.mOutputA = aExpansionLanes[i];
        aDiffusionA.mOutputB =  aExpansionLanes[i + 1];
        
        aDiffusionA.mShuffleEntropyA = aOperationLanes[(i + 0) % 4];
        aDiffusionA.mShuffleEntropyB = aOperationLanes[(i + 1) % 4];
        aDiffusionA.mOperationSourceA = aOperationLanes[(i + 2) % 4];
        aDiffusionA.mOperationSourceB = aOperationLanes[(i + 3) % 4];
        
        aDiffusionA.mUseDomainWords = true;
        
        GBatch aBatchDiffusion;
        aBatchDiffusion.mName = "kdf-a-matrix-diffusion";
        
        if (!GRunMatrixDiffusion::Bake(aDiffusionA, &aBatchDiffusion, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("error on matrix diffusion for ") + std::string("kdf-a") + ": " + *pErrorMessage;
            }
            return false;
        }
        pExpander->mKDF_A.AddBatch(aBatchDiffusion);
    }
    
    
    
    if (!BuildKDFStage<GSeedRunKDF_A_D>(pExpander->mKDF_A,
                                        "GSeedRunKDF_A_D",
                                        "kdf-a",
                                        pErrorMessage)) {
        return false;
    }

    if (pExpander->mKDF_A.GetBatchJsonText().empty() &&
        pExpander->mKDF_A.GetStringLines().empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("kdf branch export was empty for ") + std::string("kdf-a") + " (no batches and no lines)";
        }
        return false;
    }
    
    if (!BuildKDFStage<GSeedRunKDF_B_A>(pExpander->mKDF_B,
                                        "GSeedRunKDF_B_A",
                                        "kdf-b",
                                        pErrorMessage)) {
        return false;
    }

    if (!BuildKDFStage<GSeedRunKDF_B_B>(pExpander->mKDF_B,
                                        "GSeedRunKDF_B_B",
                                        "kdf-b",
                                        pErrorMessage)) {
        return false;
    }

    if (!BuildKDFStage<GSeedRunKDF_B_C>(pExpander->mKDF_B,
                                        "GSeedRunKDF_B_C",
                                        "kdf-b",
                                        pErrorMessage)) {
        return false;
    }

    for (int i=0;i<4;i+=2) {
        
        GRunMatrixDiffusionConfig aDiffusionB;
        aDiffusionB.mInputA = aExpansionLanes[i];
        aDiffusionB.mInputB = aExpansionLanes[i + 1];
        aDiffusionB.mOutputA = aWorkLanes[i];
        aDiffusionB.mOutputB = aWorkLanes[i + 1];
        
        aDiffusionB.mShuffleEntropyA = aOperationLanes[(i + 0) % 4];
        aDiffusionB.mShuffleEntropyB = aOperationLanes[(i + 1) % 4];
        aDiffusionB.mOperationSourceA = aOperationLanes[(i + 2) % 4];
        aDiffusionB.mOperationSourceB = aOperationLanes[(i + 3) % 4];
        
        aDiffusionB.mUseDomainWords = true;
        
        GBatch aBatchDiffusion;
        aBatchDiffusion.mName = "kdf-b-matrix-diffusion";
        
        if (!GRunMatrixDiffusion::Bake(aDiffusionB, &aBatchDiffusion, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("error on matrix diffusion for ") + std::string("kdf-b") + ": " + *pErrorMessage;
            }
            return false;
        }
        pExpander->mKDF_B.AddBatch(aBatchDiffusion);
    }

    if (!BuildKDFStage<GSeedRunKDF_B_D>(pExpander->mKDF_B,
                                        "GSeedRunKDF_B_D",
                                        "kdf-b",
                                        pErrorMessage)) {
        return false;
    }

    if (pExpander->mKDF_B.GetBatchJsonText().empty() &&
        pExpander->mKDF_B.GetStringLines().empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("kdf branch export was empty for ") + std::string("kdf-b") + " (no batches and no lines)";
        }
        return false;
    }

    return true;
}
