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
    {"rainbow_lane_a", TwistWorkSpaceSlot::kRainbowLaneA},
    {"rainbow_lane_b", TwistWorkSpaceSlot::kRainbowLaneB},
    {"rainbow_lane_c", TwistWorkSpaceSlot::kRainbowLaneC},
    {"rainbow_lane_d", TwistWorkSpaceSlot::kRainbowLaneD},
    
    {"earth_lane_a", TwistWorkSpaceSlot::kEarthLaneA},
    {"earth_lane_b", TwistWorkSpaceSlot::kEarthLaneB},
    {"earth_lane_c", TwistWorkSpaceSlot::kEarthLaneC},
    {"earth_lane_d", TwistWorkSpaceSlot::kEarthLaneD},
    
    {"wind_lane_a", TwistWorkSpaceSlot::kWindLaneA},
    {"wind_lane_b", TwistWorkSpaceSlot::kWindLaneB},
    {"wind_lane_c", TwistWorkSpaceSlot::kWindLaneC},
    {"wind_lane_d", TwistWorkSpaceSlot::kWindLaneD},
    
    {"lightning_lane_a", TwistWorkSpaceSlot::kLightningLaneA},
    {"lightning_lane_b", TwistWorkSpaceSlot::kLightningLaneB},
    {"lightning_lane_c", TwistWorkSpaceSlot::kLightningLaneC},
    {"lightning_lane_d", TwistWorkSpaceSlot::kLightningLaneD},

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

    {"vapor_lane_a", TwistWorkSpaceSlot::kVaporLaneA},
    {"vapor_lane_b", TwistWorkSpaceSlot::kVaporLaneB},
    {"vapor_lane_c", TwistWorkSpaceSlot::kVaporLaneC},
    {"vapor_lane_d", TwistWorkSpaceSlot::kVaporLaneD},

    {"kinetic_lane_a", TwistWorkSpaceSlot::kKineticLaneA},
    {"kinetic_lane_b", TwistWorkSpaceSlot::kKineticLaneB},
    {"kinetic_lane_c", TwistWorkSpaceSlot::kKineticLaneC},
    {"kinetic_lane_d", TwistWorkSpaceSlot::kKineticLaneD},
    {"sonic_lane_a", TwistWorkSpaceSlot::kSonicLaneA},
    {"sonic_lane_b", TwistWorkSpaceSlot::kSonicLaneB},
    {"sonic_lane_c", TwistWorkSpaceSlot::kSonicLaneC},
    {"sonic_lane_d", TwistWorkSpaceSlot::kSonicLaneD},
    {"planar_lane_a", TwistWorkSpaceSlot::kPlanarLaneA},
    {"planar_lane_b", TwistWorkSpaceSlot::kPlanarLaneB},
    {"planar_lane_c", TwistWorkSpaceSlot::kPlanarLaneC},
    {"planar_lane_d", TwistWorkSpaceSlot::kPlanarLaneD},
    {"frost_lane_a", TwistWorkSpaceSlot::kFrostLaneA},
    {"frost_lane_b", TwistWorkSpaceSlot::kFrostLaneB},
    {"frost_lane_c", TwistWorkSpaceSlot::kFrostLaneC},
    {"frost_lane_d", TwistWorkSpaceSlot::kFrostLaneD},
    {"arcane_lane_a", TwistWorkSpaceSlot::kArcaneLaneA},
    {"arcane_lane_b", TwistWorkSpaceSlot::kArcaneLaneB},
    {"arcane_lane_c", TwistWorkSpaceSlot::kArcaneLaneC},
    {"arcane_lane_d", TwistWorkSpaceSlot::kArcaneLaneD},
    {"lunar_lane_a", TwistWorkSpaceSlot::kLunarLaneA},
    {"lunar_lane_b", TwistWorkSpaceSlot::kLunarLaneB},
    {"lunar_lane_c", TwistWorkSpaceSlot::kLunarLaneC},
    {"lunar_lane_d", TwistWorkSpaceSlot::kLunarLaneD},
    {"runic_lane_a", TwistWorkSpaceSlot::kRunicLaneA},
    {"runic_lane_b", TwistWorkSpaceSlot::kRunicLaneB},
    {"runic_lane_c", TwistWorkSpaceSlot::kRunicLaneC},
    {"runic_lane_d", TwistWorkSpaceSlot::kRunicLaneD},
    {"gloom_lane_a", TwistWorkSpaceSlot::kGloomLaneA},
    {"gloom_lane_b", TwistWorkSpaceSlot::kGloomLaneB},
    {"gloom_lane_c", TwistWorkSpaceSlot::kGloomLaneC},
    {"gloom_lane_d", TwistWorkSpaceSlot::kGloomLaneD},
    {"abjuration_lane_a", TwistWorkSpaceSlot::kAbjurationLaneA},
    {"abjuration_lane_b", TwistWorkSpaceSlot::kAbjurationLaneB},
    {"abjuration_lane_c", TwistWorkSpaceSlot::kAbjurationLaneC},
    {"abjuration_lane_d", TwistWorkSpaceSlot::kAbjurationLaneD},
    {"divination_lane_a", TwistWorkSpaceSlot::kDivinationLaneA},
    {"divination_lane_b", TwistWorkSpaceSlot::kDivinationLaneB},
    {"divination_lane_c", TwistWorkSpaceSlot::kDivinationLaneC},
    {"divination_lane_d", TwistWorkSpaceSlot::kDivinationLaneD},
    {"evocation_lane_a", TwistWorkSpaceSlot::kEvocationLaneA},
    {"evocation_lane_b", TwistWorkSpaceSlot::kEvocationLaneB},
    {"evocation_lane_c", TwistWorkSpaceSlot::kEvocationLaneC},
    {"evocation_lane_d", TwistWorkSpaceSlot::kEvocationLaneD},
    {"stasis_lane_a", TwistWorkSpaceSlot::kStasisLaneA},
    {"stasis_lane_b", TwistWorkSpaceSlot::kStasisLaneB},
    {"stasis_lane_c", TwistWorkSpaceSlot::kStasisLaneC},

    {"alchemy_lane_a", TwistWorkSpaceSlot::kAlchemyLaneA},
    {"alchemy_lane_b", TwistWorkSpaceSlot::kAlchemyLaneB},
    {"alchemy_lane_c", TwistWorkSpaceSlot::kAlchemyLaneC},
    {"alchemy_lane_d", TwistWorkSpaceSlot::kAlchemyLaneD},
    {"augury_lane_a", TwistWorkSpaceSlot::kAuguryLaneA},
    {"augury_lane_b", TwistWorkSpaceSlot::kAuguryLaneB},
    {"augury_lane_c", TwistWorkSpaceSlot::kAuguryLaneC},
    {"augury_lane_d", TwistWorkSpaceSlot::kAuguryLaneD},
    {"psychic_lane_a", TwistWorkSpaceSlot::kPsychicLaneA},
    {"psychic_lane_b", TwistWorkSpaceSlot::kPsychicLaneB},
    {"psychic_lane_c", TwistWorkSpaceSlot::kPsychicLaneC},
    {"psychic_lane_d", TwistWorkSpaceSlot::kPsychicLaneD},
    {"voodoo_lane_a", TwistWorkSpaceSlot::kVoodooLaneA},
    {"voodoo_lane_b", TwistWorkSpaceSlot::kVoodooLaneB},
    {"voodoo_lane_c", TwistWorkSpaceSlot::kVoodooLaneC},
    {"voodoo_lane_d", TwistWorkSpaceSlot::kVoodooLaneD},

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
    
    if (!CompareBytes("expander_domain_bundle_ephemeral_a",
                      reinterpret_cast<const std::uint8_t *>(pLeftExpander->GetDomainBundleEphemeralA()),
                      reinterpret_cast<const std::uint8_t *>(pRightExpander->GetDomainBundleEphemeralA()),
                      sizeof(*(pLeftExpander->GetDomainBundleEphemeralA())),
                      pErrorMessage)) {
        return false;
    }
    return CompareBytes("expander_domain_bundle_ephemeral_b",
                        reinterpret_cast<const std::uint8_t *>(pLeftExpander->GetDomainBundleEphemeralB()),
                        reinterpret_cast<const std::uint8_t *>(pRightExpander->GetDomainBundleEphemeralB()),
                        sizeof(*(pLeftExpander->GetDomainBundleEphemeralB())),
                        pErrorMessage);
}

bool CompareWorkSpace::CompareBlocks(const std::uint8_t *pLeft,
                                     const std::uint8_t *pRight,
                                     const std::size_t pBlockCount,
                                     std::string *pErrorMessage) {
    return CompareBytes("blocks", pLeft, pRight, pBlockCount * S_BLOCK, pErrorMessage);
}
