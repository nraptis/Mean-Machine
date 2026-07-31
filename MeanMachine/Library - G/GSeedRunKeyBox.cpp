//
//  GSeedRunKeyBox.cpp
//  MeanMachine
//

#include "GSeedRunKeyBox.hpp"

#include "LaneSplitControl.hpp"

#include <array>
#include <vector>

namespace {

using Slot = TwistWorkSpaceSlot;

std::vector<Slot> PhaseSalts(const TwistDomain pDomain,
                             const Slot pBaseSlot,
                             const int pLaneCount) {
    int aPhaseIndex = 0;
    switch (pDomain) {
        case TwistDomain::kKeySpawnA: aPhaseIndex = 1; break;
        case TwistDomain::kSeed: aPhaseIndex = 2; break;
        case TwistDomain::kTwist: aPhaseIndex = 3; break;
        case TwistDomain::kKeyRotateB: aPhaseIndex = 4; break;
        case TwistDomain::kKeySpawnB: aPhaseIndex = 5; break;
        case TwistDomain::kKeyRotateA:
        default:
            aPhaseIndex = 0;
            break;
    }

    std::vector<Slot> aResult;
    aResult.reserve(static_cast<std::size_t>(pLaneCount));
    const int aBase = static_cast<int>(pBaseSlot);
    const int aOffset = aPhaseIndex * 24;
    for (int i = 0; i < pLaneCount; ++i) {
        aResult.push_back(
            static_cast<Slot>(aBase + aOffset + i)
        );
    }
    return aResult;
}

GSeedRunStageConfig BaseConfig(const char *pStageName,
                               const char *pBatchName,
                               const TwistDomain pDomain,
                               const GAXSFormat pFormat) {
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pBatchName;
    aConfig.mFormat = pFormat;
    aConfig.mIgnoreNonces = false;
    aConfig.mAssignType = GAssignType::kSet;
    aConfig.mDomain = pDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 1;
    aConfig.mHotPackCount = 1;
    aConfig.mMaxContextSourceCount = 4;
    aConfig.mMaxBoundSourceCount = 8;
    aConfig.mBindDuplicateSourceSlots = false;
    aConfig.mFixedDiffuse = GAXSKDiffuseKind::kDiffuseA;
    aConfig.mAutoRangeAdjust = false;
    aConfig.mSourceOffsetRangeLo = 0;
    aConfig.mSourceOffsetRangeHi = W_KEY1;
    aConfig.mEmitLaneFlowComments = true;
    aConfig.mSaltsOrbiterAssign =
        PhaseSalts(pDomain,
                   Slot::kKeyRotateASaltOrbiterAssignA,
                   8);
    aConfig.mSaltsOrbiterUpdate =
        PhaseSalts(pDomain,
                   Slot::kKeyRotateASaltOrbiterUpdateA,
                   8);
    aConfig.mSaltsWandererUpdate =
        PhaseSalts(pDomain,
                   Slot::kKeyRotateASaltWandererUpdateA,
                   8);
    return aConfig;
}

GSeedRunStageConfig MakeSingleLoopConfig(
    const char *pStageName,
    const char *pBatchName,
    const Slot pDestination,
    const TwistDomain pDomain,
    const GAXSFormat pFormat) {
    GSeedRunStageConfig aConfig =
        BaseConfig(pStageName, pBatchName, pDomain, pFormat);
    aConfig.mSlices.push_back(
        GSeedRunStageSliceSpec(
            {
                Slot::kCrystalLaneA,
                Slot::kCrystalLaneB,
                Slot::kCrystalLaneC,
                Slot::kCrystalLaneD,
            },
            false,
            {
                Slot::kPlasmaLaneA,
                Slot::kPlasmaLaneB,
                Slot::kPlasmaLaneC,
                Slot::kPlasmaLaneD,
            },
            true,
            pDestination,
            false
        )
    );
    aConfig.mSliceDomains.push_back(pDomain);
    return aConfig;
}

} // namespace

namespace GSeedRunKeyBoxConfig {

bool LoadLaneSplitValues(std::string *pErrorMessage) {
    if (LaneSplitControl::GeneratedCount() ==
        LaneSplitControl::kCandidateCount) {
        return true;
    }
    if (LaneSplitControl::GeneratedCount() != 0U) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "LaneSplitControl had a partial candidate family";
        }
        return false;
    }

    LaneSplitControl::Reset();
    if (!LaneSplitControl::AddLaneGroup(
            {
                Slot::kCrystalLaneA,
                Slot::kCrystalLaneB,
                Slot::kCrystalLaneC,
                Slot::kCrystalLaneD,
            },
            pErrorMessage) ||
        !LaneSplitControl::AddLaneGroup(
            {
                Slot::kPlasmaLaneA,
                Slot::kPlasmaLaneB,
                Slot::kPlasmaLaneC,
                Slot::kPlasmaLaneD,
            },
            pErrorMessage)) {
        return false;
    }

    if (!LaneSplitControl::LoadValues(
            "Assets/lane_split_pre_planned",
            pErrorMessage)) {
        return false;
    }
    return true;
}

bool MakeKeyBoxConfigs(const std::size_t pCandidateIndex,
                       KeyBoxStageConfigs *pConfigs,
                       std::string *pErrorMessage) {
    if (pConfigs == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Key-box config output was null";
        }
        return false;
    }
    if (!LoadLaneSplitValues(pErrorMessage)) {
        return false;
    }
    if (pCandidateIndex >= LaneSplitControl::GeneratedCount()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "Key-box lane-split candidate was out of range";
        }
        return false;
    }

    // Lane Plan

    const std::array<Slot, 16> aDestinations = {
        Slot::kKeyRowA0, Slot::kKeyRowA1,
        Slot::kKeyRowA2, Slot::kKeyRowA3,
        Slot::kKeyRowA4, Slot::kKeyRowA5,
        Slot::kKeyRowA6, Slot::kKeyRowA7,
        Slot::kKeyRowB0, Slot::kKeyRowB1,
        Slot::kKeyRowB2, Slot::kKeyRowB3,
        Slot::kKeyRowB4, Slot::kKeyRowB5,
        Slot::kKeyRowB6, Slot::kKeyRowB7,
    };

    static constexpr std::array<const char *, 16> kStageNames = {
        "GSeedRunKEY_A_A", "GSeedRunKEY_A_B",
        "GSeedRunKEY_A_C", "GSeedRunKEY_A_D",
        "GSeedRunKEY_A_E", "GSeedRunKEY_A_F",
        "GSeedRunKEY_A_G", "GSeedRunKEY_A_H",
        "GSeedRunKEY_B_A", "GSeedRunKEY_B_B",
        "GSeedRunKEY_B_C", "GSeedRunKEY_B_D",
        "GSeedRunKEY_B_E", "GSeedRunKEY_B_F",
        "GSeedRunKEY_B_G", "GSeedRunKEY_B_H",
    };
    static constexpr std::array<const char *, 16> kBatchNames = {
        "key_a_loop_a", "key_a_loop_b",
        "key_a_loop_c", "key_a_loop_d",
        "key_a_loop_e", "key_a_loop_f",
        "key_a_loop_g", "key_a_loop_h",
        "key_b_loop_a", "key_b_loop_b",
        "key_b_loop_c", "key_b_loop_d",
        "key_b_loop_e", "key_b_loop_f",
        "key_b_loop_g", "key_b_loop_h",
    };
    static constexpr std::array<GAXSFormat, 16> kFormats = {
        GAXSFormat::kN11, GAXSFormat::kN11,
        GAXSFormat::kN11, GAXSFormat::kN11,
        GAXSFormat::kN11, GAXSFormat::kN11,
        GAXSFormat::kN11, GAXSFormat::kN11,
        GAXSFormat::kN11, GAXSFormat::kN11,
        GAXSFormat::kN11, GAXSFormat::kN11,
        GAXSFormat::kN11, GAXSFormat::kN11,
        GAXSFormat::kN11, GAXSFormat::kN11,
    };

    // Stage Construction

    for (std::size_t i = 0U; i < pConfigs->size(); ++i) {
        const TwistDomain aDomain =
            i < 8U
                ? TwistDomain::kKeySpawnA
                : TwistDomain::kKeySpawnB;
        GSeedRunStageConfig aConfig =
            MakeSingleLoopConfig(kStageNames[i],
                                 kBatchNames[i],
                                 aDestinations[i],
                                 aDomain,
                                 kFormats[i]);

        const std::vector<std::uint8_t> aLogicalLaneSplits = {
            static_cast<std::uint8_t>(i),
        };
        if (!LaneSplitControl::LinkStageConfig(
                &aConfig,
                pCandidateIndex,
                aLogicalLaneSplits,
                pErrorMessage)) {
            return false;
        }
        (*pConfigs)[i] = std::move(aConfig);
    }
    return true;
}

} // namespace GSeedRunKeyBoxConfig

GSeedRunKEY::GSeedRunKEY(
    const GSeedRunStageConfig &pConfig)
: mStage(pConfig) {
}

bool GSeedRunKEY::Plan(
    std::string *pErrorMessage) {
    return mStage.Plan(pErrorMessage);
}

bool GSeedRunKEY::Build(
    TwistProgramBranch &pBranch,
    std::string *pErrorMessage) {
    return mStage.Build(pBranch, pErrorMessage);
}
