//
//  GDomainSchedule.hpp
//  MeanMachine
//

#ifndef GDomainSchedule_hpp
#define GDomainSchedule_hpp

#include "GSeedRunStageConfig.hpp"
#include "Random.hpp"

#include <array>
#include <cstddef>
#include <vector>

namespace GDomainSchedule {

inline std::vector<TwistDomain> MakeShuffledRoundRobin(
    const std::size_t pDomainCount) {
    // Phases G and H are reserved for the Grow loops. Seeder and Twister
    // distribute only phases A through F across their slices and matrices.
    static const std::array<TwistDomain, 6> kDomains = {
        TwistDomain::kPhaseA,
        TwistDomain::kPhaseB,
        TwistDomain::kPhaseC,
        TwistDomain::kPhaseD,
        TwistDomain::kPhaseE,
        TwistDomain::kPhaseF,
    };

    std::vector<TwistDomain> aResult;
    aResult.reserve(pDomainCount);

    while ((aResult.size() + kDomains.size()) <= pDomainCount) {
        aResult.insert(aResult.end(), kDomains.begin(), kDomains.end());
    }

    if (aResult.size() < pDomainCount) {
        std::vector<TwistDomain> aFinalRound(kDomains.begin(), kDomains.end());
        Random::Shuffle(&aFinalRound);
        const std::size_t aRemaining = pDomainCount - aResult.size();
        aResult.insert(aResult.end(),
                       aFinalRound.begin(),
                       aFinalRound.begin() + aRemaining);
    }

    Random::Shuffle(&aResult);
    return aResult;
}

inline bool AssignShuffledRoundRobin(
    std::vector<GSeedRunStageConfig> *pStageConfigs,
    const std::size_t pExtraDomainCount,
    std::vector<TwistDomain> *pExtraDomains) {
    if ((pStageConfigs == nullptr) || (pExtraDomains == nullptr)) {
        return false;
    }

    std::size_t aScheduledDomainCount = pExtraDomainCount;
    for (const GSeedRunStageConfig &aConfig : *pStageConfigs) {
        aScheduledDomainCount += aConfig.mSlices.size();
    }

    const std::vector<TwistDomain> aSchedule =
        MakeShuffledRoundRobin(aScheduledDomainCount);
    std::size_t aDomainIndex = 0U;
    for (GSeedRunStageConfig &aConfig : *pStageConfigs) {
        aConfig.mSliceDomains.clear();
        aConfig.mSliceDomains.reserve(aConfig.mSlices.size());
        for (std::size_t i = 0U; i < aConfig.mSlices.size(); ++i) {
            aConfig.mSliceDomains.push_back(aSchedule[aDomainIndex++]);
        }
    }

    pExtraDomains->assign(aSchedule.begin() + aDomainIndex,
                          aSchedule.end());
    return pExtraDomains->size() == pExtraDomainCount;
}

} // namespace GDomainSchedule

#endif /* GDomainSchedule_hpp */
