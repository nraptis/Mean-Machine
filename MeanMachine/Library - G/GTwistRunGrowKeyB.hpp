//
//  GTwistRunGrowKeyB.hpp
//  MeanMachine
//

#ifndef GTwistRunGrowKeyB_hpp
#define GTwistRunGrowKeyB_hpp

#include "GSeedRunStage.hpp"

#include <array>
#include <cstddef>
#include <string>

class ResidualBucket;

namespace GTwistRunGrowKeyBConfig {

using GrowStageConfigs = std::array<GSeedRunStageConfig, 5>;

GrowStageConfigs                            MakeGrowBConfig(ResidualBucket &pResidualBucket,
                                                            std::size_t pCandidateIndex);

}

class GTwistRunGrowKeyB {
public:
    explicit GTwistRunGrowKeyB(ResidualBucket &pResidualBucket);
    GTwistRunGrowKeyB(const GSeedRunStageConfig &pConfig,
                      ResidualBucket &pResidualBucket);
    ~GTwistRunGrowKeyB();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

#endif /* GTwistRunGrowKeyB_hpp */
