//
//  GSeedRunKeyBox.hpp
//  MeanMachine
//

#ifndef GSeedRunKeyBox_hpp
#define GSeedRunKeyBox_hpp

#include "GSeedRunStage.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace GSeedRunKeyBoxConfig {

using KeyBoxStageConfigs = std::array<GSeedRunStageConfig, 16>;

// Crystal A-D and Plasma A-D feed sixteen independently generated KEY stages.
// Each stage uses one logical lane fragment A-P from the required eight-lane
// LaneSplit_Candidate family.
bool LoadLaneSplitValues(std::string *pErrorMessage = nullptr);

bool MakeKeyBoxConfigs(std::size_t pCandidateIndex,
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
