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
#include "GSeedRunKDF3.hpp"

#include "GRunMatrixDiffusion.hpp"
#include "GRunMaskBraidDiffusion.hpp"

#include "GAXSK.hpp"

namespace {

bool BuildKDFBranch(TwistProgramBranch &pBranch,
                    const char *pLabel,
                    std::string *pErrorMessage) {
    
    
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
    
    GSeedRunKDF2 aKDF2;
    
    if (!aKDF2.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GSeedRunKDF2.Plan for ") + "kdf-a" + "\n" + *pErrorMessage;
        }
        return false;
    }
    
    if (!aKDF2.Build(pExpander->mKDF_A, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GSeedRunKDF2.Build for ") + std::string("kdf-a") + "\n" + *pErrorMessage;
        }
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
        
        GBatch aBatchDiffusion;
        aBatchDiffusion.AddComment(std::string("kdf-a") + "-matrix-diffusion: yeah");
        
        if (!GRunMatrixDiffusion::Bake(aDiffusionA, &aBatchDiffusion, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("error on matrix diffusion for ") + std::string("kdf-a") + ": " + *pErrorMessage;
            }
            return false;
        }
        pExpander->mKDF_A.AddBatch(aBatchDiffusion);
    }
    
    
    
    GSeedRunKDF3 aKDF3;
    
    if (!aKDF3.Plan(pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GSeedRunKDF3.Plan for ") + "kdf-a" + "\n" + *pErrorMessage;
        }
        return false;
    }
    
    if (!aKDF3.Build(pExpander->mKDF_B, pErrorMessage)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("error on GSeedRunKDF3.Build for ") + std::string("kdf-a") + "\n" + *pErrorMessage;
        }
        return false;
    }
    
    if (pExpander->mKDF_B.GetBatchJsonText().empty() &&
        pExpander->mKDF_B.GetStringLines().empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("kdf branch export was empty for ") + std::string("kdf-a") + " (no batches and no lines)";
        }
        return false;
    }
    
    /*
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
     */
    
    
    std::vector<TwistMaskBraidType> aBraidTypes;
    aBraidTypes.push_back(TwistMaskBraidType::kA);
    aBraidTypes.push_back(TwistMaskBraidType::kB);
    aBraidTypes.push_back(TwistMaskBraidType::kC);
    aBraidTypes.push_back(Random::Choice(aBraidTypes));
    Random::Shuffle(&aBraidTypes);
    
    int aBraidTypeIndex = 0;
    int aOperationLaneIndex = 0;
    
    for (int i=0;i<4;i+=2) {
        
        GRunMaskBraidDiffusionConfig aDiffusionA;
        aDiffusionA.mInputA = aExpansionLanes[i];
        aDiffusionA.mInputB = aExpansionLanes[i + 1];
        aDiffusionA.mMaskLane = aOperationLanes[aOperationLaneIndex++];
        aDiffusionA.mBraidType = aBraidTypes[aBraidTypeIndex++];
        
        if (i == 0) {
            aDiffusionA.mMaskDomainWord = GSymbol::Var(TwistVariable::kDomainWordMaskMutateA);
        } else {
            aDiffusionA.mMaskDomainWord = GSymbol::Var(TwistVariable::kDomainWordMaskMutateB);
        }
        
        GBatch aBatchDiffusion;
        aBatchDiffusion.AddComment(std::string("kdf-a") + "-matrix-diffusion: yeah");
        
        if (!GRunMaskBraidDiffusion::Bake(aDiffusionA, &aBatchDiffusion, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("error on matrix diffusion for ") + std::string("kdf-a") + ": " + *pErrorMessage;
            }
            return false;
        }
        pExpander->mKDF_B.AddBatch(aBatchDiffusion);
    }
    
    std::swap(aExpansionLanes[1], aExpansionLanes[3]);
    if (Random::Bool()) {
        std::swap(aExpansionLanes[0], aExpansionLanes[1]);
    }
    if (Random::Bool()) {
        std::swap(aExpansionLanes[2], aExpansionLanes[3]);
    }
    
    for (int i=0;i<4;i+=2) {
        
        GRunMaskBraidDiffusionConfig aDiffusionA;
        aDiffusionA.mInputA = aExpansionLanes[i];
        aDiffusionA.mInputB = aExpansionLanes[i + 1];
        aDiffusionA.mMaskLane = aOperationLanes[aOperationLaneIndex++];
        aDiffusionA.mBraidType = aBraidTypes[aBraidTypeIndex++];
        
        if (i == 0) {
            aDiffusionA.mMaskDomainWord = GSymbol::Var(TwistVariable::kDomainWordMaskMutateA);
        } else {
            aDiffusionA.mMaskDomainWord = GSymbol::Var(TwistVariable::kDomainWordMaskMutateB);
        }
        
        GBatch aBatchDiffusion;
        aBatchDiffusion.AddComment(std::string("kdf-a") + "-matrix-diffusion: yeah");
        
        if (!GRunMaskBraidDiffusion::Bake(aDiffusionA, &aBatchDiffusion, pErrorMessage)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("error on matrix diffusion for ") + std::string("kdf-a") + ": " + *pErrorMessage;
            }
            return false;
        }
        pExpander->mKDF_B.AddBatch(aBatchDiffusion);
    }
    
    return true;
}
