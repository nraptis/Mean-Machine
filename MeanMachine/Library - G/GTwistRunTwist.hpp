//
//  GTwistRunTwist.hpp
//  MeanMachine
//

#ifndef GTwistRunTwist_hpp
#define GTwistRunTwist_hpp

#include "GSeedRunStage.hpp"
#include <string>

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

#endif /* GTwistRunTwist_hpp */
