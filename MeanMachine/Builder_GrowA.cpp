//
//  Builder_GrowA.cpp
//  MeanMachine
//

#include "Builder_GrowA.hpp"
#include "Builder_GrowCommon.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunGrowKeyA.hpp"
#include "ResidualBucket.hpp"

bool Builder_GrowA::Build(GTwistExpander *pExpander,
                          ResidualBucket &pResidualBucket,
                          std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowA::Build received null expander";
        }
        return false;
    }

    const GTwistRunGrowKeyAConfig::GrowStageConfigs aStageConfigs =
        GTwistRunGrowKeyAConfig::MakeGrowAConfig(
            pResidualBucket,
            pExpander->mControlCandidateIndex);
    pExpander->mGrowAStageConfigs.assign(aStageConfigs.begin(),
                                         aStageConfigs.end());
    pExpander->mGrowAMatrixDomain = TwistDomain::kKeyRotateA;

    return Builder_GrowCommon::Build<GTwistRunGrowKeyA>(
        pExpander->mGrowKeyA,
        aStageConfigs,
        pResidualBucket,
        GFlowPlans::GrowA(),
        'A',
        0U,
        pErrorMessage);
}
