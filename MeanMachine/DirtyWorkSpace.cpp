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
        TwistWorkSpaceSlot::kSourceLane,
        TwistWorkSpaceSlot::kNonceLane,
        TwistWorkSpaceSlot::kKeyBoxUnrolledA,
        TwistWorkSpaceSlot::kKeyBoxUnrolledB,
        
        TwistWorkSpaceSlot::kHeartLaneA,
        TwistWorkSpaceSlot::kHeartLaneB,
        TwistWorkSpaceSlot::kHeartLaneC,
        TwistWorkSpaceSlot::kHeartLaneD,
        
        TwistWorkSpaceSlot::kSpiritLaneA,
        TwistWorkSpaceSlot::kSpiritLaneB,
        TwistWorkSpaceSlot::kSpiritLaneC,
        TwistWorkSpaceSlot::kSpiritLaneD,
        
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
        
        TwistWorkSpaceSlot::kWoodLaneA,
        TwistWorkSpaceSlot::kWoodLaneB,
        TwistWorkSpaceSlot::kWoodLaneC,
        TwistWorkSpaceSlot::kWoodLaneD,

        TwistWorkSpaceSlot::kLightningLaneA,
        TwistWorkSpaceSlot::kLightningLaneB,
        TwistWorkSpaceSlot::kLightningLaneC,
        TwistWorkSpaceSlot::kLightningLaneD,

        TwistWorkSpaceSlot::kMagmaLaneA,
        TwistWorkSpaceSlot::kMagmaLaneB,
        TwistWorkSpaceSlot::kMagmaLaneC,
        TwistWorkSpaceSlot::kMagmaLaneD,

        TwistWorkSpaceSlot::kSoilLaneA,
        TwistWorkSpaceSlot::kSoilLaneB,
        TwistWorkSpaceSlot::kSoilLaneC,
        TwistWorkSpaceSlot::kSoilLaneD,

        TwistWorkSpaceSlot::kPlasmaLaneA,
        TwistWorkSpaceSlot::kPlasmaLaneB,
        TwistWorkSpaceSlot::kPlasmaLaneC,
        TwistWorkSpaceSlot::kPlasmaLaneD,

        TwistWorkSpaceSlot::kShadowLaneA,
        TwistWorkSpaceSlot::kShadowLaneB,
        TwistWorkSpaceSlot::kShadowLaneC,
        TwistWorkSpaceSlot::kShadowLaneD,

        TwistWorkSpaceSlot::kCrystalLaneA,
        TwistWorkSpaceSlot::kCrystalLaneB,
        TwistWorkSpaceSlot::kCrystalLaneC,
        TwistWorkSpaceSlot::kCrystalLaneD,

        TwistWorkSpaceSlot::kAetherLaneA,
        TwistWorkSpaceSlot::kAetherLaneB,
        TwistWorkSpaceSlot::kAetherLaneC,
        TwistWorkSpaceSlot::kAetherLaneD,

        TwistWorkSpaceSlot::kCelestialLaneA,
        TwistWorkSpaceSlot::kCelestialLaneB,
        TwistWorkSpaceSlot::kCelestialLaneC,
        TwistWorkSpaceSlot::kCelestialLaneD,

        TwistWorkSpaceSlot::kKineticLaneA,
        TwistWorkSpaceSlot::kKineticLaneB,
        TwistWorkSpaceSlot::kKineticLaneC,
        TwistWorkSpaceSlot::kKineticLaneD,

        TwistWorkSpaceSlot::kVaporLaneA,
        TwistWorkSpaceSlot::kVaporLaneB,
        TwistWorkSpaceSlot::kVaporLaneC,
        TwistWorkSpaceSlot::kVaporLaneD,

        TwistWorkSpaceSlot::kIceLaneA,
        TwistWorkSpaceSlot::kIceLaneB,
        TwistWorkSpaceSlot::kIceLaneC,
        TwistWorkSpaceSlot::kIceLaneD,
    };
    
    for (const TwistWorkSpaceSlot aSlot : aSlots) {
        ScrambleSlot(pWorkSpace, pExpander, aSlot);
    }
    
    FillRandomBytes(&pWorkSpace->mDomainBundle, sizeof(pWorkSpace->mDomainBundle));
    
    if (pExpander != nullptr) {
        FillRandomBytes(pExpander->GetDomainBundleEphemeral(),
                        sizeof(*(pExpander->GetDomainBundleEphemeral())));
    }
}
