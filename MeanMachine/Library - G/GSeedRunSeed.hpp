//
//  GSeedRunSeed.hpp
//  MeanMachine
//

#ifndef GSeedRunSeed_hpp
#define GSeedRunSeed_hpp

#include "GSeedRunStage.hpp"
#include <string>

namespace GSeedRunSeedConfig {

GSeedRunStageConfig                         MakeSeed_AConfig(bool pUseNonces);
GSeedRunStageConfig                         MakeSeed_BConfig(bool pUseNonces);
GSeedRunStageConfig                         MakeSeed_CConfig(bool pUseNonces);
GSeedRunStageConfig                         MakeSeed_DConfig(bool pUseNonces);
GSeedRunStageConfig                         MakeSeed_EConfig(bool pUseNonces);
GSeedRunStageConfig                         MakeSeed_FConfig(bool pUseNonces);
GSeedRunStageConfig                         MakeSeed_GConfig(bool pUseNonces);
GSeedRunStageConfig                         MakeSeed_HConfig(bool pUseNonces);
GSeedRunStageConfig                         MakeSeed_IConfig(bool pUseNonces);

}

class GSeedRunSeed_A {
public:
    explicit GSeedRunSeed_A(bool pUseNonces = true, bool pEmitNoncePrologue = true);
    ~GSeedRunSeed_A();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

class GSeedRunSeed_B {
public:
    explicit GSeedRunSeed_B(bool pUseNonces = true, bool pEmitNoncePrologue = true);
    ~GSeedRunSeed_B();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

class GSeedRunSeed_C {
public:
    explicit GSeedRunSeed_C(bool pUseNonces = true, bool pEmitNoncePrologue = true);
    ~GSeedRunSeed_C();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

class GSeedRunSeed_D {
public:
    explicit GSeedRunSeed_D(bool pUseNonces = true, bool pEmitNoncePrologue = true);
    ~GSeedRunSeed_D();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

class GSeedRunSeed_E {
public:
    explicit GSeedRunSeed_E(bool pUseNonces = true, bool pEmitNoncePrologue = true);
    ~GSeedRunSeed_E();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

class GSeedRunSeed_F {
public:
    explicit GSeedRunSeed_F(bool pUseNonces = true, bool pEmitNoncePrologue = true);
    ~GSeedRunSeed_F();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

class GSeedRunSeed_G {
public:
    explicit GSeedRunSeed_G(bool pUseNonces = true, bool pEmitNoncePrologue = true);
    ~GSeedRunSeed_G();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

class GSeedRunSeed_H {
public:
    explicit GSeedRunSeed_H(bool pUseNonces = true, bool pEmitNoncePrologue = true);
    ~GSeedRunSeed_H();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

class GSeedRunSeed_I {
public:
    explicit GSeedRunSeed_I(bool pUseNonces = true, bool pEmitNoncePrologue = true);
    ~GSeedRunSeed_I();

    bool                                    Plan(std::string *pErrorMessage);
    bool                                    Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);

private:
    void                                    Reset();

    GSeedRunStage                           mStage;
    bool                                    mUseNonces;
    bool                                    mEmitNoncePrologue;
};

#endif /* GSeedRunSeed_hpp */
