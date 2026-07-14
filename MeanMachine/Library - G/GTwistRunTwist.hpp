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

}

class GTwistRunTwist_A {
public:
    GTwistRunTwist_A();
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
    ~GTwistRunTwist_E();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
};

#endif /* GTwistRunTwist_hpp */
