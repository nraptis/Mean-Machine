//
//  GSeedRunKeyBox.cpp
//  MeanMachine
//

#include "GSeedRunKeyBox.hpp"

#include "LaneSplitControl.hpp"

#include <array>
#include <utility>
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
    const int aOffset = aPhaseIndex * 18;
    for (int i = 0; i < pLaneCount; ++i) {
        aResult.push_back(
            static_cast<Slot>(aBase + aOffset + i)
        );
    }
    return aResult;
}

GSeedRunStageConfig BaseConfig(const char *pStageName,
                               const char *pBatchName) {
    constexpr TwistDomain kDefaultDomain = TwistDomain::kKeySpawnA;

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = pStageName;
    aConfig.mBatchName = pBatchName;
    aConfig.mFormat = GAXSFormat::kN9;
    aConfig.mIgnoreNonces = false;
    aConfig.mHasDomainMix = true;
    aConfig.mAssignType = GAssignType::kSet;
    // Rows A0-A7 use this default. Rows B0-B7 explicitly override it with
    // kKeySpawnB through mSliceDomains below.
    aConfig.mDomain = kDefaultDomain;
    aConfig.mIsNonKDF = true;
    aConfig.mExpectedSkeletonCount = 8;
    aConfig.mHotPackCount = 8;
    aConfig.mMaxContextSourceCount = 4;
    aConfig.mMaxBoundSourceCount = 8;
    aConfig.mBindDuplicateSourceSlots = false;
    aConfig.mAutoRangeAdjust = false;
    aConfig.mSourceOffsetRangeLo = 0;
    aConfig.mSourceOffsetRangeHi = W_KEY1;
    aConfig.mEmitLaneFlowComments = true;
    aConfig.mSaltsOrbiterAssign =
        PhaseSalts(kDefaultDomain,
                   Slot::kKeyRotateASaltOrbiterAssignA,
                   6);
    aConfig.mSaltsOrbiterUpdate =
        PhaseSalts(kDefaultDomain,
                   Slot::kKeyRotateASaltOrbiterUpdateA,
                   6);
    aConfig.mSaltsWandererUpdate =
        PhaseSalts(kDefaultDomain,
                   Slot::kKeyRotateASaltWandererUpdateA,
                   6);
    return aConfig;
}

GSeedRunStageConfig MakeSixteenLoopConfig(
    const char *pStageName,
    const char *pBatchName,
    const std::array<Slot, 16> &pDestinations) {
    GSeedRunStageConfig aConfig =
        BaseConfig(pStageName, pBatchName);
    aConfig.mExpectedSkeletonCount =
        static_cast<int>(pDestinations.size());
    aConfig.mHotPackCount =
        static_cast<int>(pDestinations.size());

    for (std::size_t i = 0U; i < pDestinations.size(); ++i) {
        aConfig.mSlices.push_back(
            GSeedRunStageSliceSpec(
                {
                    Slot::kPoisonLaneA,
                    Slot::kPoisonLaneB,
                    Slot::kPoisonLaneC,
                    Slot::kPoisonLaneD,
                },
                false,
                {
                    Slot::kPlasmaLaneA,
                    Slot::kPlasmaLaneB,
                    Slot::kPlasmaLaneC,
                    Slot::kPlasmaLaneD,
                },
                true,
                pDestinations[i],
                false
            )
        );
        aConfig.mSliceDomains.push_back(
            i < 8U
                ? TwistDomain::kKeySpawnA
                : TwistDomain::kKeySpawnB
        );
    }
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
                Slot::kPoisonLaneA,
                Slot::kPoisonLaneB,
                Slot::kPoisonLaneC,
                Slot::kPoisonLaneD,
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

    GSeedRunStageConfig aConfig =
        MakeSixteenLoopConfig("GSeedRunKEY",
                              "key_box",
                              aDestinations);

    if (!LaneSplitControl::LinkStageConfig(
            &aConfig,
            pCandidateIndex,
            pErrorMessage)) {
        return false;
    }

    (*pConfigs)[0] = std::move(aConfig);
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
