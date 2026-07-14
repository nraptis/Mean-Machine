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
    {"source", TwistWorkSpaceSlot::kSource},
    {"key_box_a", TwistWorkSpaceSlot::kKeyBoxUnrolledA},
    {"key_box_b", TwistWorkSpaceSlot::kKeyBoxUnrolledB},
    
    {"expansion_lane_a", TwistWorkSpaceSlot::kExpansionLaneA},
    {"expansion_lane_b", TwistWorkSpaceSlot::kExpansionLaneB},
    {"expansion_lane_c", TwistWorkSpaceSlot::kExpansionLaneC},
    {"expansion_lane_d", TwistWorkSpaceSlot::kExpansionLaneD},
    
    {"work_lane_a", TwistWorkSpaceSlot::kWorkLaneA},
    {"work_lane_b", TwistWorkSpaceSlot::kWorkLaneB},
    {"work_lane_c", TwistWorkSpaceSlot::kWorkLaneC},
    {"work_lane_d", TwistWorkSpaceSlot::kWorkLaneD},
    
    {"operation_lane_a", TwistWorkSpaceSlot::kOperationLaneA},
    {"operation_lane_b", TwistWorkSpaceSlot::kOperationLaneB},
    {"operation_lane_c", TwistWorkSpaceSlot::kOperationLaneC},
    {"operation_lane_d", TwistWorkSpaceSlot::kOperationLaneD},
    
    {"snow_lane_a", TwistWorkSpaceSlot::kSnowLaneA},
    {"snow_lane_b", TwistWorkSpaceSlot::kSnowLaneB},
    {"snow_lane_c", TwistWorkSpaceSlot::kSnowLaneC},
    {"snow_lane_d", TwistWorkSpaceSlot::kSnowLaneD},
    
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
    
    {"scrap_lane_a", TwistWorkSpaceSlot::kScrapLaneA},
    {"scrap_lane_b", TwistWorkSpaceSlot::kScrapLaneB},
    {"scrap_lane_c", TwistWorkSpaceSlot::kScrapLaneC},
    {"scrap_lane_d", TwistWorkSpaceSlot::kScrapLaneD},
    
    {"merge_lane_a", TwistWorkSpaceSlot::kMergeLaneA},
    {"merge_lane_b", TwistWorkSpaceSlot::kMergeLaneB},
    {"merge_lane_c", TwistWorkSpaceSlot::kMergeLaneC},
    {"merge_lane_d", TwistWorkSpaceSlot::kMergeLaneD},
    
    {"invest_lane_a", TwistWorkSpaceSlot::kInvestA},
    {"invest_lane_b", TwistWorkSpaceSlot::kInvestB},
    {"invest_lane_c", TwistWorkSpaceSlot::kInvestC},
    {"invest_lane_d", TwistWorkSpaceSlot::kInvestD},
    {"invest_lane_e", TwistWorkSpaceSlot::kInvestE},
    {"invest_lane_f", TwistWorkSpaceSlot::kInvestF},
    {"invest_lane_g", TwistWorkSpaceSlot::kInvestG},
    {"invest_lane_h", TwistWorkSpaceSlot::kInvestH},
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
                        reinterpret_cast<const std::uint8_t *>(&pLeftExpander->mDomainBundleEphemeral),
                        reinterpret_cast<const std::uint8_t *>(&pRightExpander->mDomainBundleEphemeral),
                        sizeof(pLeftExpander->mDomainBundleEphemeral),
                        pErrorMessage);
}

bool CompareWorkSpace::CompareBlocks(const std::uint8_t *pLeft,
                                     const std::uint8_t *pRight,
                                     const std::size_t pBlockCount,
                                     std::string *pErrorMessage) {
    return CompareBytes("blocks", pLeft, pRight, pBlockCount * S_BLOCK, pErrorMessage);
}
