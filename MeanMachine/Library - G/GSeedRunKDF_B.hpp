//
//  GSeedRunKDF_B.hpp
//  MeanMachine
//

#ifndef GSeedRunKDF_B_hpp
#define GSeedRunKDF_B_hpp

#include "GSeedRunStage.hpp"

#include <array>
#include <string>

class ResidualBucket;

namespace GSeedRunKDF_BConfig {

using KDFStageConfigs = std::array<GSeedRunStageConfig, 4>;

KDFStageConfigs                            MakeKDF_BConfig(ResidualBucket &pResidualBucket);

}

class GSeedRunKDF_B {
public:
    explicit GSeedRunKDF_B(const GSeedRunStageConfig &pConfig,
                           bool pEmitPrologue = false);

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
    bool                                    mEmitPrologue;
};

#endif /* GSeedRunKDF_B_hpp */
