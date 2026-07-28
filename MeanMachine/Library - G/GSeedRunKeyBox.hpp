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

using KeyBoxStageConfigs = std::array<GSeedRunStageConfig, 1>;

// Poison A-D are ingress, Plasma A-D are cross, and the sixteen logical
// fragments feed the sixteen direct key-row destinations in one KEY stage.
// Candidate values are loaded from Assets; this path never generates a
// fallback family.
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
