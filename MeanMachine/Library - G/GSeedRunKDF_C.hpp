//
//  GSeedRunKDF_C.hpp
//  MeanMachine
//

#ifndef GSeedRunKDF_C_hpp
#define GSeedRunKDF_C_hpp

#include "GSeedRunStage.hpp"

#include <array>
#include <string>

class ResidualBucket;

namespace GSeedRunKDF_CConfig {

using KDFStageConfigs = std::array<GSeedRunStageConfig, 3>;

KDFStageConfigs                            MakeKDF_CConfig(ResidualBucket &pResidualBucket,
                                                           std::size_t pCandidateIndex);

}

class GSeedRunKDF_C {
public:
    explicit GSeedRunKDF_C(const GSeedRunStageConfig &pConfig,
                           bool pEmitPrologue = false);

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
    bool                                    mEmitPrologue;
};

#endif /* GSeedRunKDF_C_hpp */
