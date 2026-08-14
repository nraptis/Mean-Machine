//
//  GSeedRunKDF_A.hpp
//  MeanMachine
//

#ifndef GSeedRunKDF_A_hpp
#define GSeedRunKDF_A_hpp

#include "GSeedRunStage.hpp"

#include <array>
#include <string>

class ResidualBucket;

namespace GSeedRunKDF_AConfig {

using KDFStageConfigs = std::array<GSeedRunStageConfig, 3>;

KDFStageConfigs                            MakeKDF_AConfig(ResidualBucket &pResidualBucket,
                                                           std::size_t pCandidateIndex);

}

class GSeedRunKDF_A {
public:
    explicit GSeedRunKDF_A(const GSeedRunStageConfig &pConfig,
                           bool pEmitPrologue = false);

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
    bool                                    mEmitPrologue;
};

#endif /* GSeedRunKDF_A_hpp */
