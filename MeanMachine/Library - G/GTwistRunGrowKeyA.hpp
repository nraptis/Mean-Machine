//
//  GTwistRunGrowKeyA.hpp
//  MeanMachine
//

#ifndef GTwistRunGrowKeyA_hpp
#define GTwistRunGrowKeyA_hpp

#include "GSeedRunStage.hpp"

#include <string>

namespace GTwistRunGrowKeyConfig {

GSeedRunStageConfig                         MakeGrowAConfig();
GSeedRunStageConfig                         MakeGrowBConfig();

}

class GTwistRunGrowKeyA {
public:
    GTwistRunGrowKeyA();
    ~GTwistRunGrowKeyA();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

class GTwistRunGrowKeyB {
public:
    GTwistRunGrowKeyB();
    ~GTwistRunGrowKeyB();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch,
                                                  std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

#endif /* GTwistRunGrowKeyA_hpp */
