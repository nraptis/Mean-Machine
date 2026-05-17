//
//  GARXFormat.cpp
//  MeanMachine
//
//  Created by Dragon on 5/15/26.
//

#include "GARXFormat.hpp"
#include "GARXPlan.hpp"

static std::vector<int> cSixSixFourPassSaltBiases = {
    0, 6, 10, 14
};

const GARXFormatSixSixFour &GARXFormatSixSixFour::Shared() {
    static GARXFormatSixSixFour aShared;
    return aShared;
}

const char *GARXFormatSixSixFour::Name() const {
    return "GARXFormatSixSixFour";
}

std::size_t GARXFormatSixSixFour::PlanWidth() const {
    return 6;
}

std::size_t GARXFormatSixSixFour::PassCount() const {
    return 4;
}

std::size_t GARXFormatSixSixFour::MaxPlanWidth() const {
    return 11;
}

std::vector<GARXType> GARXFormatSixSixFour::OrbiterTypes() const {
    return {
        GARXType::kOrbiterA,
        GARXType::kOrbiterB,
        GARXType::kOrbiterC,
        GARXType::kOrbiterD,
        GARXType::kOrbiterE,
        GARXType::kOrbiterF
    };
}

std::vector<GARXType> GARXFormatSixSixFour::UnwindTypes() const {
    return {
        GARXType::kUnwindA,
        GARXType::kUnwindB,
        GARXType::kUnwindC,
        GARXType::kUnwindD,
        GARXType::kUnwindE,
        GARXType::kUnwindF
    };
}

const std::vector<int> &GARXFormatSixSixFour::PassSaltBiases() const {
    return cSixSixFourPassSaltBiases;
}

int GARXFormatSixSixFour::PickLoopSaltLane(GARXGroupType pGroupType,
                                           std::size_t pLoopKeyIndexInPhase,
                                           std::size_t pLoopKeyIndexInStatement) const {
    if (pGroupType == GARXGroupType::kSeed) {
        return ((pLoopKeyIndexInStatement & 1U) == 0U)
            ? 0
            : 1;
    }

    if (pGroupType == GARXGroupType::kUnwind) {
        if ((pLoopKeyIndexInPhase & 1U) == 0U) {
            return 4;
        } else {
            return 5;
        }
    }

    return -1;
}

int GARXFormatSixSixFour::PickForwardPlugSaltLane(std::size_t pPlugIndexInGroup,
                                                   std::size_t pForwardGroupIndex,
                                                   std::size_t pPassIndex) const {
    const bool aFlip = (((pForwardGroupIndex + pPassIndex) & 1U) != 0U);

    if (pPlugIndexInGroup == 0U) {
        return aFlip ? 3 : 2;
    }

    return aFlip ? 2 : 3;
}

int GARXFormatSixSixFour::PickSeedPlugSaltLane(std::size_t pPlugIndexInPhase) const {
    return ((pPlugIndexInPhase & 1U) == 0U)
        ? 0
        : 1;
}

int GARXFormatSixSixFour::PickUnwindPlugSaltLane(std::size_t pPlugIndexInPhase) const {
    return ((pPlugIndexInPhase & 1U) == 0U)
        ? 4
        : 5;
}
