//
//  GSeedRunSeed.hpp
//  MeanMachine
//

#ifndef GSeedRunSeed_hpp
#define GSeedRunSeed_hpp

#include "GSeedRunStage.hpp"

#include <array>
#include <string>

class ResidualBucket;

namespace GSeedRunSeedConfig {

using SeedStageConfigs = std::array<GSeedRunStageConfig, 17>;

SeedStageConfigs                           MakeSeedConfig(bool pUseNonces,
                                                          ResidualBucket &pResidualBucket,
                                                          std::size_t pCandidateIndex);

}

class GSeedRunSeed {
public:
    GSeedRunSeed(const GSeedRunStageConfig &pConfig,
                 bool pUseNonces,
                 bool pEmitNoncePrologue = false);

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

#endif /* GSeedRunSeed_hpp */
