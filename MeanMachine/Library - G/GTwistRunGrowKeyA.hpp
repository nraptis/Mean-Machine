//
//  GTwistRunGrowKeyA.hpp
//  MeanMachine
//

#ifndef GTwistRunGrowKeyA_hpp
#define GTwistRunGrowKeyA_hpp

#include "GSeedRunStage.hpp"

#include <array>
#include <string>

class ResidualBucket;

namespace GTwistRunGrowKeyAConfig {

using GrowStageConfigs = std::array<GSeedRunStageConfig, 4>;

GrowStageConfigs                            MakeGrowAConfig(ResidualBucket &pResidualBucket);

}

class GTwistRunGrowKeyA {
public:
    explicit GTwistRunGrowKeyA(ResidualBucket &pResidualBucket);
    GTwistRunGrowKeyA(const GSeedRunStageConfig &pConfig,
                      ResidualBucket &pResidualBucket);
    ~GTwistRunGrowKeyA();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

#endif /* GTwistRunGrowKeyA_hpp */
