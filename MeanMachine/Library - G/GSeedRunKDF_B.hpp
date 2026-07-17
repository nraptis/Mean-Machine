//
//  GSeedRunKDF_B.hpp
//  MeanMachine
//

#ifndef GSeedRunKDF_B_hpp
#define GSeedRunKDF_B_hpp

#include "GSeedRunStage.hpp"
#include <string>

namespace GSeedRunKDF_BConfig {

GSeedRunStageConfig                         MakeKDF_B_AConfig();
GSeedRunStageConfig                         MakeKDF_B_BConfig();
GSeedRunStageConfig                         MakeKDF_B_CConfig();
GSeedRunStageConfig                         MakeKDF_B_DConfig();

}

class GSeedRunKDF_B_A {
public:
    GSeedRunKDF_B_A();
    ~GSeedRunKDF_B_A();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
};

class GSeedRunKDF_B_B {
public:
    GSeedRunKDF_B_B();
    ~GSeedRunKDF_B_B();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
};

class GSeedRunKDF_B_C {
public:
    GSeedRunKDF_B_C();
    ~GSeedRunKDF_B_C();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
};

class GSeedRunKDF_B_D {
public:
    GSeedRunKDF_B_D();
    ~GSeedRunKDF_B_D();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    GSeedRunStage                           mStage;
};

#endif /* GSeedRunKDF_B_hpp */
