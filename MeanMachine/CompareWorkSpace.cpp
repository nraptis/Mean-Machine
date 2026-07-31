//
//  CompareWorkSpace.cpp
//  MeanMachine
//

#include "CompareWorkSpace.hpp"

#include "TwistExpander.hpp"
#include "TwistWorkSpace.hpp"

#include <cstring>
#include <sstream>

namespace {

struct NamedSlot {
    const char                              *mName;
    TwistWorkSpaceSlot                     mSlot;
};

const NamedSlot kWorkSpaceSlots[] = {
    {"source", TwistWorkSpaceSlot::kSourceLane},
    {"nonce", TwistWorkSpaceSlot::kNonceLane},
    {"key_box_a", TwistWorkSpaceSlot::kKeyBoxUnrolledA},
    {"key_box_b", TwistWorkSpaceSlot::kKeyBoxUnrolledB},
    
    {"expansion_lane_a", TwistWorkSpaceSlot::kHeartLaneA},
    {"expansion_lane_b", TwistWorkSpaceSlot::kHeartLaneB},
    {"expansion_lane_c", TwistWorkSpaceSlot::kHeartLaneC},
    {"expansion_lane_d", TwistWorkSpaceSlot::kHeartLaneD},
    
    {"operation_lane_a", TwistWorkSpaceSlot::kSpiritLaneA},
    {"operation_lane_b", TwistWorkSpaceSlot::kSpiritLaneB},
    {"operation_lane_c", TwistWorkSpaceSlot::kSpiritLaneC},
    {"operation_lane_d", TwistWorkSpaceSlot::kSpiritLaneD},
    
    {"fire_lane_a", TwistWorkSpaceSlot::kFireLaneA},
    {"fire_lane_b", TwistWorkSpaceSlot::kFireLaneB},
    {"fire_lane_c", TwistWorkSpaceSlot::kFireLaneC},
    {"fire_lane_d", TwistWorkSpaceSlot::kFireLaneD},
    
    {"water_lane_a", TwistWorkSpaceSlot::kWaterLaneA},
    {"water_lane_b", TwistWorkSpaceSlot::kWaterLaneB},
    {"water_lane_c", TwistWorkSpaceSlot::kWaterLaneC},
    {"water_lane_d", TwistWorkSpaceSlot::kWaterLaneD},
    
    {"earth_lane_a", TwistWorkSpaceSlot::kEarthLaneA},
    {"earth_lane_b", TwistWorkSpaceSlot::kEarthLaneB},
    {"earth_lane_c", TwistWorkSpaceSlot::kEarthLaneC},
    {"earth_lane_d", TwistWorkSpaceSlot::kEarthLaneD},
    
    {"wind_lane_a", TwistWorkSpaceSlot::kWindLaneA},
    {"wind_lane_b", TwistWorkSpaceSlot::kWindLaneB},
    {"wind_lane_c", TwistWorkSpaceSlot::kWindLaneC},
    {"wind_lane_d", TwistWorkSpaceSlot::kWindLaneD},
    
    {"fuse_lane_a", TwistWorkSpaceSlot::kFuseLaneA},
    {"fuse_lane_b", TwistWorkSpaceSlot::kFuseLaneB},
    {"fuse_lane_c", TwistWorkSpaceSlot::kFuseLaneC},
    {"fuse_lane_d", TwistWorkSpaceSlot::kFuseLaneD},
    
    {"scrap_lane_a", TwistWorkSpaceSlot::kWoodLaneA},
    {"scrap_lane_b", TwistWorkSpaceSlot::kWoodLaneB},
    {"scrap_lane_c", TwistWorkSpaceSlot::kWoodLaneC},
    {"scrap_lane_d", TwistWorkSpaceSlot::kWoodLaneD},

    {"lightning_lane_a", TwistWorkSpaceSlot::kLightningLaneA},
    {"lightning_lane_b", TwistWorkSpaceSlot::kLightningLaneB},
    {"lightning_lane_c", TwistWorkSpaceSlot::kLightningLaneC},
    {"lightning_lane_d", TwistWorkSpaceSlot::kLightningLaneD},

    {"magma_lane_a", TwistWorkSpaceSlot::kMagmaLaneA},
    {"magma_lane_b", TwistWorkSpaceSlot::kMagmaLaneB},
    {"magma_lane_c", TwistWorkSpaceSlot::kMagmaLaneC},
    {"magma_lane_d", TwistWorkSpaceSlot::kMagmaLaneD},

    {"soil_lane_a", TwistWorkSpaceSlot::kSoilLaneA},
    {"soil_lane_b", TwistWorkSpaceSlot::kSoilLaneB},
    {"soil_lane_c", TwistWorkSpaceSlot::kSoilLaneC},
    {"soil_lane_d", TwistWorkSpaceSlot::kSoilLaneD},

    {"plasma_lane_a", TwistWorkSpaceSlot::kPlasmaLaneA},
    {"plasma_lane_b", TwistWorkSpaceSlot::kPlasmaLaneB},
    {"plasma_lane_c", TwistWorkSpaceSlot::kPlasmaLaneC},
    {"plasma_lane_d", TwistWorkSpaceSlot::kPlasmaLaneD},

    {"shadow_lane_a", TwistWorkSpaceSlot::kShadowLaneA},
    {"shadow_lane_b", TwistWorkSpaceSlot::kShadowLaneB},
    {"shadow_lane_c", TwistWorkSpaceSlot::kShadowLaneC},
    {"shadow_lane_d", TwistWorkSpaceSlot::kShadowLaneD},

    {"crystal_lane_a", TwistWorkSpaceSlot::kCrystalLaneA},
    {"crystal_lane_b", TwistWorkSpaceSlot::kCrystalLaneB},
    {"crystal_lane_c", TwistWorkSpaceSlot::kCrystalLaneC},
    {"crystal_lane_d", TwistWorkSpaceSlot::kCrystalLaneD},

    {"aether_lane_a", TwistWorkSpaceSlot::kAetherLaneA},
    {"aether_lane_b", TwistWorkSpaceSlot::kAetherLaneB},
    {"aether_lane_c", TwistWorkSpaceSlot::kAetherLaneC},
    {"aether_lane_d", TwistWorkSpaceSlot::kAetherLaneD},

    {"celestial_lane_a", TwistWorkSpaceSlot::kCelestialLaneA},
    {"celestial_lane_b", TwistWorkSpaceSlot::kCelestialLaneB},
    {"celestial_lane_c", TwistWorkSpaceSlot::kCelestialLaneC},
    {"celestial_lane_d", TwistWorkSpaceSlot::kCelestialLaneD},

    {"kinetic_lane_a", TwistWorkSpaceSlot::kKineticLaneA},
    {"kinetic_lane_b", TwistWorkSpaceSlot::kKineticLaneB},
    {"kinetic_lane_c", TwistWorkSpaceSlot::kKineticLaneC},
    {"kinetic_lane_d", TwistWorkSpaceSlot::kKineticLaneD},

    {"vapor_lane_a", TwistWorkSpaceSlot::kVaporLaneA},
    {"vapor_lane_b", TwistWorkSpaceSlot::kVaporLaneB},
    {"vapor_lane_c", TwistWorkSpaceSlot::kVaporLaneC},
    {"vapor_lane_d", TwistWorkSpaceSlot::kVaporLaneD},

    {"invest_lane_a", TwistWorkSpaceSlot::kIceLaneA},
    {"invest_lane_b", TwistWorkSpaceSlot::kIceLaneB},
    {"invest_lane_c", TwistWorkSpaceSlot::kIceLaneC},
    {"invest_lane_d", TwistWorkSpaceSlot::kIceLaneD},
};

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

std::string ByteMismatchMessage(const std::string &pName,
                                const std::size_t pOffset,
                                const std::uint8_t pLeft,
                                const std::uint8_t pRight) {
    std::ostringstream aStream;
    aStream << pName << " mismatch at byte " << pOffset
            << ": left=" << static_cast<unsigned int>(pLeft)
            << " right=" << static_cast<unsigned int>(pRight);
    return aStream.str();
}

bool CompareBytes(const std::string &pName,
                  const std::uint8_t *pLeft,
                  const std::uint8_t *pRight,
                  const std::size_t pByteCount,
                  std::string *pErrorMessage) {
    if ((pLeft == nullptr) || (pRight == nullptr)) {
        SetError(pErrorMessage, pName + " had a null buffer");
        return false;
    }
    
    for (std::size_t i = 0U; i < pByteCount; ++i) {
        if (pLeft[i] != pRight[i]) {
            SetError(pErrorMessage, ByteMismatchMessage(pName, i, pLeft[i], pRight[i]));
            return false;
        }
    }
    return true;
}

bool CompareWorkspaceBuffers(TwistWorkSpace *pLeft,
                             TwistExpander *pLeftExpander,
                             TwistWorkSpace *pRight,
                             TwistExpander *pRightExpander,
                             std::string *pErrorMessage) {
    if ((pLeft == nullptr) || (pRight == nullptr)) {
        SetError(pErrorMessage, "workspace compare had a null workspace");
        return false;
    }
    
    for (const NamedSlot &aSlot : kWorkSpaceSlots) {
        const std::uint8_t *aLeft = TwistWorkSpace::GetBuffer(pLeft, pLeftExpander, aSlot.mSlot);
        const std::uint8_t *aRight = TwistWorkSpace::GetBuffer(pRight, pRightExpander, aSlot.mSlot);
        const std::size_t aByteCount = static_cast<std::size_t>(TwistWorkSpace::GetBufferLength(aSlot.mSlot));
        if (!CompareBytes(aSlot.mName, aLeft, aRight, aByteCount, pErrorMessage)) {
            return false;
        }
    }
    
    return CompareBytes("domain_bundle",
                        reinterpret_cast<const std::uint8_t *>(&pLeft->mDomainBundle),
                        reinterpret_cast<const std::uint8_t *>(&pRight->mDomainBundle),
                        sizeof(pLeft->mDomainBundle),
                        pErrorMessage);
}

} // namespace

bool CompareWorkSpace::Compare(TwistWorkSpace *pLeft,
                               TwistWorkSpace *pRight,
                               std::string *pErrorMessage) {
    return CompareWorkspaceBuffers(pLeft, nullptr, pRight, nullptr, pErrorMessage);
}

bool CompareWorkSpace::Compare(TwistWorkSpace *pLeft,
                               TwistExpander *pLeftExpander,
                               TwistWorkSpace *pRight,
                               TwistExpander *pRightExpander,
                               std::string *pErrorMessage) {
    if (!CompareWorkspaceBuffers(pLeft, pLeftExpander, pRight, pRightExpander, pErrorMessage)) {
        return false;
    }
    
    if ((pLeftExpander == nullptr) || (pRightExpander == nullptr)) {
        return true;
    }
    
    return CompareBytes("expander_domain_bundle_ephemeral",
                        reinterpret_cast<const std::uint8_t *>(pLeftExpander->GetDomainBundleEphemeral()),
                        reinterpret_cast<const std::uint8_t *>(pRightExpander->GetDomainBundleEphemeral()),
                        sizeof(*(pLeftExpander->GetDomainBundleEphemeral())),
                        pErrorMessage);
}

bool CompareWorkSpace::CompareBlocks(const std::uint8_t *pLeft,
                                     const std::uint8_t *pRight,
                                     const std::size_t pBlockCount,
                                     std::string *pErrorMessage) {
    return CompareBytes("blocks", pLeft, pRight, pBlockCount * S_BLOCK, pErrorMessage);
}
