//
//  GTwistRunTwist.hpp
//  MeanMachine
//

#ifndef GTwistRunTwist_hpp
#define GTwistRunTwist_hpp

#include "GSeedRunStage.hpp"
#include <string>

namespace GTwistRunTwistConfig {

GSeedRunStageConfig                         MakeTwist_AConfig();
GSeedRunStageConfig                         MakeTwist_BConfig();
GSeedRunStageConfig                         MakeTwist_CConfig();
GSeedRunStageConfig                         MakeTwist_DConfig();
GSeedRunStageConfig                         MakeTwist_EConfig();
GSeedRunStageConfig                         MakeTwist_FConfig();
GSeedRunStageConfig                         MakeTwist_GConfig();

}

class GTwistRunTwist_A {
public:
    GTwistRunTwist_A();
    explicit GTwistRunTwist_A(GSeedRunStageConfig pConfig);
    ~GTwistRunTwist_A();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

class GTwistRunTwist_B {
public:
    GTwistRunTwist_B();
    explicit GTwistRunTwist_B(GSeedRunStageConfig pConfig);
    ~GTwistRunTwist_B();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

class GTwistRunTwist_C {
public:
    GTwistRunTwist_C();
    explicit GTwistRunTwist_C(GSeedRunStageConfig pConfig);
    ~GTwistRunTwist_C();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

class GTwistRunTwist_D {
public:
    GTwistRunTwist_D();
    explicit GTwistRunTwist_D(GSeedRunStageConfig pConfig);
    ~GTwistRunTwist_D();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

class GTwistRunTwist_E {
public:
    GTwistRunTwist_E();
    explicit GTwistRunTwist_E(GSeedRunStageConfig pConfig);
    ~GTwistRunTwist_E();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

class GTwistRunTwist_F {
public:
    GTwistRunTwist_F();
    explicit GTwistRunTwist_F(GSeedRunStageConfig pConfig);
    ~GTwistRunTwist_F();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

class GTwistRunTwist_G {
public:
    GTwistRunTwist_G();
    explicit GTwistRunTwist_G(GSeedRunStageConfig pConfig);
    ~GTwistRunTwist_G();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

#endif /* GTwistRunTwist_hpp */
