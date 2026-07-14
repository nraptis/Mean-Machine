//
//  DirtyWorkSpace.cpp
//  MeanMachine
//
//  Created by icarus black on 6/30/26.
//

#include "DirtyWorkSpace.hpp"

#include "Random.hpp"
#include "TwistExpander.hpp"
#include "TwistWorkSpace.hpp"

#include <cstddef>
#include <cstdint>

namespace {

void FillRandomBytes(void *pBuffer,
                     const std::size_t pByteCount) {
    if (pBuffer == nullptr) {
        return;
    }
    
    std::uint8_t *aBytes = static_cast<std::uint8_t *>(pBuffer);
    for (std::size_t i = 0U; i < pByteCount; ++i) {
        aBytes[i] = Random::GetByte();
    }
}

void ScrambleSlot(TwistWorkSpace *pWorkSpace,
                  TwistExpander *pExpander,
                  const TwistWorkSpaceSlot pSlot) {
    std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkSpace, pExpander, pSlot);
    if (aBuffer == nullptr) {
        return;
    }
    
    FillRandomBytes(aBuffer, static_cast<std::size_t>(TwistWorkSpace::GetBufferLength(pSlot)));
}

} // namespace

void DirtyWorkSpace::Scramble(TwistWorkSpace *pWorkSpace,
                              TwistExpander *pExpander) {
    if (pWorkSpace == nullptr) {
        return;
    }
    
    const TwistWorkSpaceSlot aSlots[] = {
        TwistWorkSpaceSlot::kSource,
        TwistWorkSpaceSlot::kKeyBoxUnrolledA,
        TwistWorkSpaceSlot::kKeyBoxUnrolledB,
        
        TwistWorkSpaceSlot::kExpansionLaneA,
        TwistWorkSpaceSlot::kExpansionLaneB,
        TwistWorkSpaceSlot::kExpansionLaneC,
        TwistWorkSpaceSlot::kExpansionLaneD,
        
        TwistWorkSpaceSlot::kWorkLaneA,
        TwistWorkSpaceSlot::kWorkLaneB,
        TwistWorkSpaceSlot::kWorkLaneC,
        TwistWorkSpaceSlot::kWorkLaneD,
        
        TwistWorkSpaceSlot::kOperationLaneA,
        TwistWorkSpaceSlot::kOperationLaneB,
        TwistWorkSpaceSlot::kOperationLaneC,
        TwistWorkSpaceSlot::kOperationLaneD,
        
        TwistWorkSpaceSlot::kSnowLaneA,
        TwistWorkSpaceSlot::kSnowLaneB,
        TwistWorkSpaceSlot::kSnowLaneC,
        TwistWorkSpaceSlot::kSnowLaneD,
        
        TwistWorkSpaceSlot::kFireLaneA,
        TwistWorkSpaceSlot::kFireLaneB,
        TwistWorkSpaceSlot::kFireLaneC,
        TwistWorkSpaceSlot::kFireLaneD,
        
        TwistWorkSpaceSlot::kWaterLaneA,
        TwistWorkSpaceSlot::kWaterLaneB,
        TwistWorkSpaceSlot::kWaterLaneC,
        TwistWorkSpaceSlot::kWaterLaneD,
        
        TwistWorkSpaceSlot::kEarthLaneA,
        TwistWorkSpaceSlot::kEarthLaneB,
        TwistWorkSpaceSlot::kEarthLaneC,
        TwistWorkSpaceSlot::kEarthLaneD,
        
        TwistWorkSpaceSlot::kWindLaneA,
        TwistWorkSpaceSlot::kWindLaneB,
        TwistWorkSpaceSlot::kWindLaneC,
        TwistWorkSpaceSlot::kWindLaneD,
        
        TwistWorkSpaceSlot::kFuseLaneA,
        TwistWorkSpaceSlot::kFuseLaneB,
        TwistWorkSpaceSlot::kFuseLaneC,
        TwistWorkSpaceSlot::kFuseLaneD,
        
        TwistWorkSpaceSlot::kScrapLaneA,
        TwistWorkSpaceSlot::kScrapLaneB,
        TwistWorkSpaceSlot::kScrapLaneC,
        TwistWorkSpaceSlot::kScrapLaneD,
        
        TwistWorkSpaceSlot::kMergeLaneA,
        TwistWorkSpaceSlot::kMergeLaneB,
        TwistWorkSpaceSlot::kMergeLaneC,
        TwistWorkSpaceSlot::kMergeLaneD,
        
        TwistWorkSpaceSlot::kInvestA,
        TwistWorkSpaceSlot::kInvestB,
        TwistWorkSpaceSlot::kInvestC,
        TwistWorkSpaceSlot::kInvestD,
        TwistWorkSpaceSlot::kInvestE,
        TwistWorkSpaceSlot::kInvestF,
        TwistWorkSpaceSlot::kInvestG,
        TwistWorkSpaceSlot::kInvestH,
    };
    
    for (const TwistWorkSpaceSlot aSlot : aSlots) {
        ScrambleSlot(pWorkSpace, pExpander, aSlot);
    }
    
    FillRandomBytes(&pWorkSpace->mDomainBundle, sizeof(pWorkSpace->mDomainBundle));
    
    if (pExpander != nullptr) {
        FillRandomBytes(&pExpander->mDomainBundleEphemeral, sizeof(pExpander->mDomainBundleEphemeral));
    }
}
