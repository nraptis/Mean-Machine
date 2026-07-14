//
//  GSeedRunKDF_A.hpp
//  MeanMachine
//

#ifndef GSeedRunKDF_A_hpp
#define GSeedRunKDF_A_hpp

#include "GSeedRunStage.hpp"
#include <string>

namespace GSeedRunKDF_AConfig {

GSeedRunStageConfig                         MakeKDF_A_AConfig();
GSeedRunStageConfig                         MakeKDF_A_BConfig();
GSeedRunStageConfig                         MakeKDF_A_CConfig();
GSeedRunStageConfig                         MakeKDF_A_DConfig();
GSeedRunStageConfig                         MakeKDF_A_EConfig();

}

class GSeedRunKDF_A_A {
public:
    GSeedRunKDF_A_A();
    ~GSeedRunKDF_A_A();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();
    GSeedRunStage                           mStage;
};

class GSeedRunKDF_A_B {
public:
    GSeedRunKDF_A_B();
    ~GSeedRunKDF_A_B();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();
    GSeedRunStage                           mStage;
};

class GSeedRunKDF_A_C {
public:
    GSeedRunKDF_A_C();
    ~GSeedRunKDF_A_C();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();
    GSeedRunStage                           mStage;
};

class GSeedRunKDF_A_D {
public:
    GSeedRunKDF_A_D();
    ~GSeedRunKDF_A_D();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();
    GSeedRunStage                           mStage;
};

class GSeedRunKDF_A_E {
public:
    GSeedRunKDF_A_E();
    ~GSeedRunKDF_A_E();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();
    GSeedRunStage                           mStage;
};

#endif /* GSeedRunKDF_A_hpp */
