//
//  GSeedRunKeyBox.hpp
//  MeanMachine
//

#ifndef GSeedRunKeyBox_hpp
#define GSeedRunKeyBox_hpp

#include "GFlowPlans.hpp"
#include "GSeedRunStage.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

class ResidualBucket;

namespace GSeedRunKeyBoxConfig {

using KeyBoxStageConfigs = std::array<
    GSeedRunStageConfig,
    GFlowPlans::kKeyStageConfigCount>;

// Each key flow has five independently generated four-loop ARX stages and two
// per-flow mini-diffusions. The exact lane chain lives in GFlowPlans::Key();
// each stage operates on the current flow's assigned lane sixteenths.

bool MakeKeyBoxConfigs(std::size_t pCandidateIndex,
                       const ResidualBucket &pSeedResidualBucket,
                       KeyBoxStageConfigs *pConfigs,
                       std::string *pErrorMessage = nullptr);

}

class GSeedRunKEY {
public:
    explicit GSeedRunKEY(
        const GSeedRunStageConfig &pConfig);

    bool Plan(std::string *pErrorMessage);
    bool Build(TwistProgramBranch &pBranch,
               std::string *pErrorMessage);

private:
    GSeedRunStage mStage;
};

#endif /* GSeedRunKeyBox_hpp */
