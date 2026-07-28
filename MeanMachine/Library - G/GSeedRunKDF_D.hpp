//
//  GSeedRunKDF_D.hpp
//  MeanMachine
//

#ifndef GSeedRunKDF_D_hpp
#define GSeedRunKDF_D_hpp

#include "GSeedRunStage.hpp"

#include <array>
#include <string>

class ResidualBucket;

namespace GSeedRunKDF_DConfig {

using KDFStageConfigs = std::array<GSeedRunStageConfig, 4>;

KDFStageConfigs                            MakeKDF_DConfig(ResidualBucket &pResidualBucket);

}

class GSeedRunKDF_D {
public:
    explicit GSeedRunKDF_D(const GSeedRunStageConfig &pConfig,
                           bool pEmitPrologue = false);

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
    bool                                    mEmitPrologue;
};

#endif /* GSeedRunKDF_D_hpp */
