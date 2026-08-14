//
//  Builder_GrowB.cpp
//  MeanMachine
//

#include "Builder_GrowB.hpp"
#include "Builder_GrowCommon.hpp"
#include "GTwistExpander.hpp"
#include "GTwistRunGrowKeyB.hpp"
#include "ResidualBucket.hpp"

bool Builder_GrowB::Build(GTwistExpander *pExpander,
                          ResidualBucket &pResidualBucket,
                          std::string *pErrorMessage) {
    if (pExpander == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "Builder_GrowB::Build received null expander";
        }
        return false;
    }

    const GTwistRunGrowKeyBConfig::GrowStageConfigs aStageConfigs =
        GTwistRunGrowKeyBConfig::MakeGrowBConfig(
            pResidualBucket,
            pExpander->mControlCandidateIndex);
    pExpander->mGrowBStageConfigs.assign(aStageConfigs.begin(),
                                         aStageConfigs.end());
    pExpander->mGrowBMatrixDomain = TwistDomain::kKeyRotateB;

    return Builder_GrowCommon::Build<GTwistRunGrowKeyB>(
        pExpander->mGrowKeyB,
        aStageConfigs,
        pResidualBucket,
        GFlowPlans::GrowB(),
        'B',
        1U,
        pErrorMessage);
}
