//
//  GTwistRunTwist.hpp
//  MeanMachine
//

#ifndef GTwistRunTwist_hpp
#define GTwistRunTwist_hpp

#include "GSeedRunStage.hpp"

#include <array>
#include <cstddef>
#include <string>

class ResidualBucket;

namespace GTwistRunTwistConfig {

using TwistStageConfigs = std::array<GSeedRunStageConfig, 3>;

TwistStageConfigs                          MakeTwistConfig(ResidualBucket &pResidualBucket,
                                                          std::size_t pCandidateIndex);

}

class GTwistRunTwist {
public:
    explicit GTwistRunTwist(const GSeedRunStageConfig &pConfig,
                            bool pEmitPrologue = false);

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
    bool                                    mEmitPrologue;
};

#endif /* GTwistRunTwist_hpp */
