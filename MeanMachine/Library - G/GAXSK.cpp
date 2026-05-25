//
//  GAXSK.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/18/26.
//

#include "GAXSK.hpp"
#include "GAXSKModel.hpp"
#include "GAXSKPool.hpp"
#include "Random.hpp"
#include "TwistArray.hpp"
#include "GCache.hpp"
#include <array>
#include <span>

namespace {


// N=5, family=RingForward, score=1024
// rotation=0, reflected=true, stride=1, source_phase=2, feedback_phase=4, order_phase=0
// warning: adjacent_edges=5
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N5_P0 = {
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitE },
};

// N=5, family=RingForwardRotated, score=1024
// rotation=0, reflected=false, stride=1, source_phase=1, feedback_phase=3, order_phase=4
// warning: adjacent_edges=5
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N5_P1 = {
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitE },
};

// N=5, family=ReverseRing, score=976
// rotation=0, reflected=false, stride=1, source_phase=4, feedback_phase=3, order_phase=1
// warning: adjacent_edges=5
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N5_P2 = {
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC },
};

// N=5, family=RingForward, score=1024
// rotation=0, reflected=true, stride=0, source_phase=2, feedback_phase=4, order_phase=0
// warning: adjacent_edges=5
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N5_P3 = {
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitC },
};

// N=5, family=RingForwardRotated, score=1024
// rotation=0, reflected=true, stride=1, source_phase=1, feedback_phase=3, order_phase=3
// warning: adjacent_edges=5
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N5_P4 = {
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
};

// N=5, family=ReverseRing, score=976
// rotation=0, reflected=true, stride=0, source_phase=4, feedback_phase=3, order_phase=4
// warning: adjacent_edges=5
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N5_P5 = {
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitC },
};


// N=7, family=StrideForward, score=1180
// rotation=0, reflected=false, stride=0, source_phase=2, feedback_phase=3, order_phase=0
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N7_P0 = {
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
};

// N=7, family=RingForwardRotated, score=1160
// rotation=0, reflected=true, stride=1, source_phase=2, feedback_phase=6, order_phase=6
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N7_P1 = {
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitE },
};

// N=7, family=ReverseRing, score=1068
// rotation=0, reflected=false, stride=1, source_phase=6, feedback_phase=5, order_phase=5
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N7_P2 = {
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitB },
};

// N=7, family=StrideForward, score=1180
// rotation=0, reflected=false, stride=0, source_phase=5, feedback_phase=3, order_phase=1
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N7_P3 = {
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitD },
};

// N=7, family=RingForwardRotated, score=1160
// rotation=0, reflected=true, stride=1, source_phase=2, feedback_phase=6, order_phase=1
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N7_P4 = {
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitA },
};

// N=7, family=StrideForward, score=1180
// rotation=0, reflected=false, stride=0, source_phase=2, feedback_phase=3, order_phase=2
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N7_P5 = {
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitE },
};



// N=9, family=Foldback, score=1180
// rotation=0, reflected=true, stride=0, source_phase=3, feedback_phase=5, order_phase=0
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N9_P0 = {
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitH },
};

// N=9, family=StrideForward, score=1180
// rotation=0, reflected=false, stride=0, source_phase=3, feedback_phase=4, order_phase=2
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N9_P1 = {
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitF },
};

// N=9, family=RingForwardRotated, score=1160
// rotation=0, reflected=false, stride=1, source_phase=2, feedback_phase=8, order_phase=2
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N9_P2 = {
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitC },
};

// N=9, family=StrideForward, score=1180
// rotation=0, reflected=true, stride=2, source_phase=5, feedback_phase=6, order_phase=7
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N9_P3 = {
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitG },
};

// N=9, family=Foldback, score=1180
// rotation=6, reflected=false, stride=0, source_phase=3, feedback_phase=5, order_phase=1
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N9_P4 = {
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitD },
};

// N=9, family=Foldback, score=1180
// rotation=7, reflected=true, stride=0, source_phase=3, feedback_phase=4, order_phase=2
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N9_P5 = {
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitB },
};

// N=11, family=Foldback, score=1180
// rotation=6, reflected=true, stride=4, source_phase=5, feedback_phase=9, order_phase=1
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N11_P0 = {
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitK },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitJ },
};

// N=11, family=Foldback, score=1180
// rotation=2, reflected=false, stride=0, source_phase=7, feedback_phase=6, order_phase=8
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N11_P1 = {
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitK },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitJ },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitD },
};

// N=11, family=StrideForward, score=1180
// rotation=0, reflected=true, stride=4, source_phase=7, feedback_phase=5, order_phase=7
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N11_P2 = {
    { GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitJ },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitK },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitA },
};

// N=11, family=RingForwardRotated, score=1160
// rotation=0, reflected=false, stride=4, source_phase=1, feedback_phase=3, order_phase=0
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N11_P3 = {
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitJ },
    { GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitK },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitE },
};

// N=11, family=StrideForward, score=1180
// rotation=0, reflected=true, stride=4, source_phase=5, feedback_phase=7, order_phase=6
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N11_P4 = {
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitI },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitJ },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitK },
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitG },
};

// N=11, family=RingForwardRotated, score=1160
// rotation=0, reflected=true, stride=4, source_phase=1, feedback_phase=3, order_phase=2
static const std::vector<GAXSKModelOrbiterRound> kOrbiterRounds_N11_P5 = {
    { GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitD },
    { GAXSKVariable::kOrbitC, GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitJ },
    { GAXSKVariable::kOrbitI, GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitE },
    { GAXSKVariable::kOrbitD, GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitK },
    { GAXSKVariable::kOrbitJ, GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitF },
    { GAXSKVariable::kOrbitE, GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitA },
    { GAXSKVariable::kOrbitK, GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitG },
    { GAXSKVariable::kOrbitF, GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitB },
    { GAXSKVariable::kOrbitA, GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitH },
    { GAXSKVariable::kOrbitG, GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitC },
    { GAXSKVariable::kOrbitB, GAXSKVariable::kOrbitH, GAXSKVariable::kOrbitI },
};

static const std::array<std::vector<GAXSKModelOrbiterRound>, 6> kOrbiterRounds5 = {{
    kOrbiterRounds_N5_P0,
    kOrbiterRounds_N5_P1,
    kOrbiterRounds_N5_P2,
    kOrbiterRounds_N5_P3,
    kOrbiterRounds_N5_P4,
    kOrbiterRounds_N5_P5
}};

static const std::array<std::vector<GAXSKModelOrbiterRound>, 6> kOrbiterRounds7 = {{
    kOrbiterRounds_N7_P0,
    kOrbiterRounds_N7_P1,
    kOrbiterRounds_N7_P2,
    kOrbiterRounds_N7_P3,
    kOrbiterRounds_N7_P4,
    kOrbiterRounds_N7_P5
}};

static const std::array<std::vector<GAXSKModelOrbiterRound>, 6> kOrbiterRounds9 = {{
    kOrbiterRounds_N9_P0,
    kOrbiterRounds_N9_P1,
    kOrbiterRounds_N9_P2,
    kOrbiterRounds_N9_P3,
    kOrbiterRounds_N9_P4,
    kOrbiterRounds_N9_P5
}};

static const std::array<std::vector<GAXSKModelOrbiterRound>, 6> kOrbiterRounds11 = {{
    kOrbiterRounds_N11_P0,
    kOrbiterRounds_N11_P1,
    kOrbiterRounds_N11_P2,
    kOrbiterRounds_N11_P3,
    kOrbiterRounds_N11_P4,
    kOrbiterRounds_N11_P5
}};


void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

static int CrushRotationDistanceForFormat(int pRotationCount) {
    switch (pRotationCount) {
        case 0:
        case 1:
            return 32;
            
        case 2:
            return 24;
            
        case 3:
            return 16;
            
        case 4:
            return 12;
            
        case 5:
            return 10;
            
        case 6:
            return 8;
            
        case 7:
            return 6;
            
        case 8:
            return 4;
            
        case 9:
        case 10:
            return 3;
            
        default:
            return 2;
    }
}

bool IsOrbiterVariable(GAXSKVariable pVariable) {
    switch (pVariable) {
        case GAXSKVariable::kOrbitA:
        case GAXSKVariable::kOrbitB:
        case GAXSKVariable::kOrbitC:
        case GAXSKVariable::kOrbitD:
        case GAXSKVariable::kOrbitE:
        case GAXSKVariable::kOrbitF:
        case GAXSKVariable::kOrbitG:
        case GAXSKVariable::kOrbitH:
        case GAXSKVariable::kOrbitI:
        case GAXSKVariable::kOrbitJ:
        case GAXSKVariable::kOrbitK:
            return true;

        default:
            return false;
    }
}

bool IsWandererVariable(GAXSKVariable pVariable) {
    switch (pVariable) {
        case GAXSKVariable::kWandererA:
        case GAXSKVariable::kWandererB:
        case GAXSKVariable::kWandererC:
        case GAXSKVariable::kWandererD:
        case GAXSKVariable::kWandererE:
        case GAXSKVariable::kWandererF:
        case GAXSKVariable::kWandererG:
        case GAXSKVariable::kWandererH:
        case GAXSKVariable::kWandererI:
        case GAXSKVariable::kWandererJ:
        case GAXSKVariable::kWandererK:
            return true;

        default:
            return false;
    }
}

static int PassCountForFormat(GAXSFormat pFormat) {
    switch (pFormat) {
        case GAXSFormat::kN5: return 6;
        case GAXSFormat::kN7: return 6;
        case GAXSFormat::kN9: return 6;
        case GAXSFormat::kN11: return 6;
        default: return 0;
    }
}

static int SizeForFormat(GAXSFormat pFormat) {
    switch (pFormat) {
        case GAXSFormat::kN5: return 5;
        case GAXSFormat::kN7: return 7;
        case GAXSFormat::kN9: return 9;
        case GAXSFormat::kN11: return 11;
        default: return 0;
    }
}

static std::span<const GAXSKModelOrbiterRound> RoundsForFormatPass(GAXSFormat pFormat, int pPassIndex) {
    switch (pFormat) {
        case GAXSFormat::kN5:
            return kOrbiterRounds5[pPassIndex % 6];

        case GAXSFormat::kN7:
            return kOrbiterRounds7[pPassIndex % 6];

        case GAXSFormat::kN9:
            return kOrbiterRounds9[pPassIndex % 6];

        case GAXSFormat::kN11:
            return kOrbiterRounds11[pPassIndex % 6];

        default:
            return {};
    }
}

}

GAXSK::GAXSK() {
    mFormat = GAXSFormat::kInvalid;
    mHasDomainMix = false;
}

GAXSK::~GAXSK() {
    Reset();
}

int GAXSK::GetIndexForOrbiter(GAXSKVariable pOrbiter) {
    switch (pOrbiter) {
        case GAXSKVariable::kOrbitA: return 0;
        case GAXSKVariable::kOrbitB: return 1;
        case GAXSKVariable::kOrbitC: return 2;
        case GAXSKVariable::kOrbitD: return 3;
        case GAXSKVariable::kOrbitE: return 4;
        case GAXSKVariable::kOrbitF: return 5;
        case GAXSKVariable::kOrbitG: return 6;
        case GAXSKVariable::kOrbitH: return 7;
        case GAXSKVariable::kOrbitI: return 8;
        case GAXSKVariable::kOrbitJ: return 9;
        case GAXSKVariable::kOrbitK: return 10;
        default: return -1;
    }
}

static int CountEvenRotationSlots(const std::vector<bool> &pIsEven) {
    int aResult = 0;

    for (bool aValue : pIsEven) {
        if (aValue) {
            aResult++;
        }
    }

    return aResult;
}

static bool EvenRotationSlotsHaveMinimumDistance(const std::vector<bool> &pIsEven,
                                                 int pMinimumDistance) {
    int aPreviousEvenIndex = -1;

    for (int aIndex = 0; aIndex < static_cast<int>(pIsEven.size()); aIndex++) {
        if (pIsEven[static_cast<std::size_t>(aIndex)] == false) {
            continue;
        }

        if (aPreviousEvenIndex >= 0) {
            if ((aIndex - aPreviousEvenIndex) < pMinimumDistance) {
                return false;
            }
        }

        aPreviousEvenIndex = aIndex;
    }

    return true;
}

static bool ChooseEvenRotationSlots(int pCount,
                                    int pEvenCount,
                                    int pMinimumEvenDistance,
                                    std::vector<bool> *pIsEven,
                                    std::string *pErrorMessage) {
    if (pIsEven == nullptr) {
        SetError(pErrorMessage, "ChooseEvenRotationSlots received null result");
        return false;
    }

    pIsEven->clear();

    if (pCount <= 0) {
        return true;
    }

    if (pEvenCount < 0 || pEvenCount > pCount) {
        SetError(pErrorMessage, "ChooseEvenRotationSlots received invalid even count");
        return false;
    }

    pIsEven->resize(static_cast<std::size_t>(pCount), false);

    if (pEvenCount == 0) {
        return true;
    }

    int aTryCount = 0;

    do {
        for (int aIndex = 0; aIndex < pCount; aIndex++) {
            (*pIsEven)[static_cast<std::size_t>(aIndex)] = false;
        }

        for (int aIndex = 0; aIndex < pEvenCount; aIndex++) {
            (*pIsEven)[static_cast<std::size_t>(Random::Get(pCount))] = true;
        }

        aTryCount++;
        if (aTryCount > 10000) {
            SetError(pErrorMessage, "ChooseEvenRotationSlots failed to choose even slots");
            return false;
        }

    } while (
        CountEvenRotationSlots(*pIsEven) != pEvenCount ||
        EvenRotationSlotsHaveMinimumDistance(*pIsEven, pMinimumEvenDistance) == false
    );

    return true;
}

bool GAXSK::ChooseUpdateRotations(int pCount,
                                  int pMinimumDistance,
                                  bool pAllowEvenRotation,
                                  std::vector<int> *pResult,
                                  std::string *pErrorMessage) {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::ChooseUpdateRotations received null result");
        return false;
    }

    pResult->clear();

    if (pCount <= 0) {
        return true;
    }

    static const std::vector<int> kGAXSKOddRotations = {
        3, 5, 11, 13, 19, 21, 23, 27, 29,
        35, 37, 39, 41, 43, 47, 51, 53, 57
    };

    static const std::vector<int> kGAXSKEvenRotations = {
        4, 6, 10, 12, 14, 18, 20, 22, 24, 26, 28, 30,
        34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60
    };

    const int aEvenCount = pAllowEvenRotation ? (pCount / 4) : 0;
    const int aMinimumEvenDistance = 4;

    std::vector<bool> aIsEven;
    if (!ChooseEvenRotationSlots(pCount,
                                 aEvenCount,
                                 aMinimumEvenDistance,
                                 &aIsEven,
                                 pErrorMessage)) {
        return false;
    }

    std::vector<int> aRotations;
    aRotations.resize(static_cast<std::size_t>(pCount));

    int aTryCount = 0;

    do {
        for (int aIndex = 0; aIndex < pCount; aIndex++) {
            if (aIsEven[static_cast<std::size_t>(aIndex)]) {
                aRotations[static_cast<std::size_t>(aIndex)] =
                    Random::Choice(kGAXSKEvenRotations);
            } else {
                aRotations[static_cast<std::size_t>(aIndex)] =
                    Random::Choice(kGAXSKOddRotations);
            }
        }

        aTryCount++;
        if (aTryCount > 10000) {
            SetError(pErrorMessage, "GAXSK::ChooseUpdateRotations failed to choose rotations");
            return false;
        }

    } while (RotationsClash_64_N(aRotations, pMinimumDistance));

    *pResult = aRotations;
    return true;
}

bool GAXSK::AreOrbitersAdjacent(GAXSKVariable pOrbiterA,
                                GAXSKVariable pOrbiterB) {
    const int aIndexA = GetIndexForOrbiter(pOrbiterA);
    const int aIndexB = GetIndexForOrbiter(pOrbiterB);

    if ((aIndexA < 0) || (aIndexB < 0)) {
        return false;
    }

    if (aIndexA == aIndexB) {
        return true;
    }

    int aDelta = aIndexA - aIndexB;
    if (aDelta < 0) {
        aDelta = -aDelta;
    }

    return (aDelta == 1);
}

bool GAXSK::RotationsClash_64_2(int pRotationA, int pRotationB) {
    return RotationsClash_64_N(pRotationA, pRotationB, 2);
}

bool GAXSK::RotationsClash_64_2(const std::vector<int> &pRotations) {
    return RotationsClash_64_N(pRotations, 2);
}

bool GAXSK::RotationsClash_64_8(int pRotationA, int pRotationB) {
    return RotationsClash_64_N(pRotationA, pRotationB, 8);
}

bool GAXSK::RotationsClash_64_8(const std::vector<int> &pRotations) {
    return RotationsClash_64_N(pRotations, 8);
}

bool GAXSK::RotationsClash_64_12(int pRotationA, int pRotationB) {
    return RotationsClash_64_N(pRotationA, pRotationB, 12);
}

bool GAXSK::RotationsClash_64_12(const std::vector<int> &pRotations) {
    return RotationsClash_64_N(pRotations, 12);
}

bool GAXSK::RotationsClash_64_N(int pRotationA,
                                int pRotationB,
                                int pMinimumDistance) {
    if ((pRotationA < 0) || (pRotationA >= 64)) {
        return true;
    }

    if ((pRotationB < 0) || (pRotationB >= 64)) {
        return true;
    }

    if (pMinimumDistance < 0) {
        return true;
    }

    int aDelta = pRotationA - pRotationB;
    if (aDelta < 0) {
        aDelta = -aDelta;
    }

    if (aDelta > 32) {
        aDelta = 64 - aDelta;
    }

    return (aDelta < pMinimumDistance);
}

bool GAXSK::RotationsClash_64_N(const std::vector<int> &pRotations,
                                int pMinimumDistance) {
    for (std::size_t aIndexA = 0; aIndexA < pRotations.size(); aIndexA++) {
        for (std::size_t aIndexB = aIndexA + 1U; aIndexB < pRotations.size(); aIndexB++) {
            if (RotationsClash_64_N(pRotations[aIndexA],
                                    pRotations[aIndexB],
                                    pMinimumDistance)) {
                return true;
            }
        }
    }

    return false;
}

void GAXSK::Reset() {
    mFormat = GAXSFormat::kInvalid;
    mHasDomainMix = false;
    mLaneCounts.clear();

    for (int aPoolIndex = 0; aPoolIndex < mPools.size(); aPoolIndex++) {
        delete mPools[aPoolIndex];
    }
    mPools.clear();
}

GAXSKModel GAXSK::MakeModelForFormatPass(GAXSFormat pFormat,
                                          int pPassIndex) {
    const auto aRounds = RoundsForFormatPass(pFormat, pPassIndex);

    if (aRounds.empty()) {
        return GAXSKModel();
    }

    return GAXSKModel::MakeOrbiterPlan(aRounds);
}


GAXSKSourceKind GAXSK::SourceForIndex(int pIndex) {
    switch (pIndex) {
        case 0: return GAXSKSourceKind::kSourceA;
        case 1: return GAXSKSourceKind::kSourceB;
        case 2: return GAXSKSourceKind::kSourceC;
        case 3: return GAXSKSourceKind::kSourceD;
        default: return GAXSKSourceKind::kInvalid;
    }
}

GAXSKNonceByteKind GAXSK::NonceForIndex(int pIndex) {
    switch (pIndex & 7) {
        case 0: return GAXSKNonceByteKind::kNonceA;
        case 1: return GAXSKNonceByteKind::kNonceB;
        case 2: return GAXSKNonceByteKind::kNonceC;
        case 3: return GAXSKNonceByteKind::kNonceD;
        case 4: return GAXSKNonceByteKind::kNonceE;
        case 5: return GAXSKNonceByteKind::kNonceF;
        case 6: return GAXSKNonceByteKind::kNonceG;
        default: return GAXSKNonceByteKind::kNonceH;
    }
}

bool GAXSK::GetPassCount(int *pResult,
                         std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::GetPassCount received null result");
        return false;
    }

    *pResult = PassCountForFormat(mFormat);

    if (*pResult <= 0) {
        SetError(pErrorMessage, "GAXSK::GetPassCount received unsupported format");
        return false;
    }

    return true;
}

bool GAXSK::GetOrbiterCount(int *pResult,
                            std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::GetOrbiterCount received null result");
        return false;
    }

    *pResult = SizeForFormat(mFormat);

    if (*pResult <= 0) {
        SetError(pErrorMessage, "GAXSK::GetOrbiterCount received unsupported format");
        return false;
    }

    return true;
}

bool GAXSK::GetWandererCount(int *pResult,
                             std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::GetWandererCount received null result");
        return false;
    }

    *pResult = SizeForFormat(mFormat);

    if (*pResult <= 0) {
        SetError(pErrorMessage, "GAXSK::GetWandererCount produced invalid wanderer count");
        return false;
    }

    return true;
}

bool GAXSK::GetLaneCountForPass(int pPassIndex, int *pResult, std::string *pErrorMessage) const {
    
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::GetLaneCountForPass received null result");
        return false;
    }

    *pResult = 0;

    if (mLaneCounts.empty()) {
        SetError(pErrorMessage, "GAXSK::GetLaneCountForPass received no lane counts");
        return false;
    }

    if (pPassIndex < 0) {
        SetError(pErrorMessage, "GAXSK::GetLaneCountForPass received negative pass index");
        return false;
    }

    if (static_cast<std::size_t>(pPassIndex) < mLaneCounts.size()) {
        *pResult = mLaneCounts[static_cast<std::size_t>(pPassIndex)];
    } else {
        *pResult = mLaneCounts.back();
    }

    if ((*pResult < 1) || (*pResult > 4)) {
        SetError(pErrorMessage, "GAXSK::GetLaneCountForPass lane count must be 1, 2, 3, or 4");
        return false;
    }

    return true;
}

GAXSKStatement GAXSK::MakeCommentStatement() {
    GAXSKStatement aStatement;
    aStatement.mKind = GAXSKStatementKind::kComment;
    return aStatement;
}

GAXSKInputSlot GAXSK::MakeSourceSlot(GAXSKSourceKind pSource,
                                     int pOffset,
                                     bool pReverse,
                                     int pRotation) {
    GAXSKInputSlot aSlot;
    aSlot.mKind = GAXSKInputSlotKind::kSource;
    aSlot.mSource = pSource;
    aSlot.mNonceByte = GAXSKNonceByteKind::kInvalid;
    aSlot.mOffset = pOffset;
    aSlot.mReverse = pReverse;
    aSlot.mRotation = pRotation;
    return aSlot;
}

GAXSKInputSlot GAXSK::MakeNonceSlot(GAXSKNonceByteKind pNonce,
                                    int pRotation) {
    GAXSKInputSlot aSlot;
    aSlot.mKind = GAXSKInputSlotKind::kNonceByte;
    aSlot.mSource = GAXSKSourceKind::kInvalid;
    aSlot.mNonceByte = pNonce;
    aSlot.mOffset = 0;
    aSlot.mReverse = false;
    aSlot.mRotation = pRotation;
    return aSlot;
}

GAXSKStatement GAXSK::MakePreviousAssignStatement() {
    GAXSKStatement aStatement;
    aStatement.mKind = GAXSKStatementKind::kPreviousAssign;
    aStatement.mTarget = GAXSKVariable::kPrevious;
    aStatement.mSource = GAXSKVariable::kIngress;
    return aStatement;
}

GAXSKStatement GAXSK::MakeContextWordStatement(GAXSKVariable pTarget,
                                               GAXSKDiffuseKind pDiffuse,
                                               bool pIsIngress) {
    GAXSKStatement aStatement;
    aStatement.mKind = GAXSKStatementKind::kContextWordAssign;
    aStatement.mTarget = pTarget;

    aStatement.mContextWord.mTarget = pTarget;
    aStatement.mContextWord.mHasDomainMix = mHasDomainMix;
    aStatement.mContextWord.mIsIngress = pIsIngress;
    aStatement.mContextWord.mDiffuse = pDiffuse;

    return aStatement;
}

bool GAXSK::MakeCarryMixStatement(const std::vector<GAXSKVariable> &pWanderers,
                                  GAXSKStatement *pResult,
                                  std::string *pErrorMessage) {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::MakeCarryMixStatement received null result");
        return false;
    }

    if (pWanderers.empty()) {
        SetError(pErrorMessage, "GAXSK::MakeCarryMixStatement received no wanderers");
        return false;
    }

    for (GAXSKVariable aWanderer : pWanderers) {
        if (!IsWandererVariable(aWanderer)) {
            SetError(pErrorMessage, "GAXSK::MakeCarryMixStatement received non-wanderer variable");
            return false;
        }
    }

    GAXSKStatement aStatement;
    aStatement.mKind = GAXSKStatementKind::kCarryCrush;
    aStatement.mTarget = GAXSKVariable::kCarry;

    GAXSKCrushPlan &aPlan = aStatement.mCarry;
    aPlan.mTarget = GAXSKVariable::kCarry;
    aPlan.mPairs.clear();
    aPlan.mHasOdd = false;
    aPlan.mOdd = GAXSKCrushOddPlan();

    aPlan.mHasFinalTerm = true;
    aPlan.mFinalTerm.mVariable = GAXSKVariable::kIngress;
    aPlan.mFinalTerm.mRotation = -1;

    aPlan.mOuterOp = GAXSKOpKind::kAdd;
    aPlan.mHasDiffuse = true;

    std::vector<GAXSKDiffuseKind> aDiffuseList = {
        GAXSKDiffuseKind::kDiffuseA,
        GAXSKDiffuseKind::kDiffuseB,
        GAXSKDiffuseKind::kDiffuseC
    };
    aPlan.mDiffuse = Random::Choice(aDiffuseList);

    std::vector<GAXSKVariable> aWanderers = pWanderers;
    Random::Shuffle(&aWanderers);

    const int aPairCount = static_cast<int>(aWanderers.size()) / 2;
    const bool aHasOdd = ((aWanderers.size() & 1U) != 0U);

    const int aRotationCount = static_cast<int>(aWanderers.size()) + 1;
    
    const int aMinimumDistance =
        CrushRotationDistanceForFormat(aRotationCount);

    std::vector<int> aRotations;
    if (!ChooseUpdateRotations(aRotationCount,
                               aMinimumDistance,
                               true,
                               &aRotations,
                               pErrorMessage)) {
        return false;
    }

    int aRotationIndex = 0;

    for (int aPairIndex = 0; aPairIndex < aPairCount; ++aPairIndex) {
        const int aWandererIndexA = aPairIndex * 2;
        const int aWandererIndexB = aWandererIndexA + 1;

        GAXSKCrushPairPlan aPair;
        aPair.mA = aWanderers[static_cast<std::size_t>(aWandererIndexA)];
        aPair.mB = aWanderers[static_cast<std::size_t>(aWandererIndexB)];

        aPair.mRotateA = Random::Bool();
        aPair.mRotation = aRotations[static_cast<std::size_t>(aRotationIndex)];
        aRotationIndex++;

        aPair.mOp = GAXSKOpKind::kXor;

        aPlan.mPairs.push_back(aPair);
    }

    if (aHasOdd) {
        aPlan.mHasOdd = true;
        aPlan.mOdd.mVariable = aWanderers.back();
        aPlan.mOdd.mHasRotation = true;
        aPlan.mOdd.mRotation = aRotations[static_cast<std::size_t>(aRotationIndex)];
        aRotationIndex++;
    }

    aPlan.mFinalTerm.mRotation = aRotations[static_cast<std::size_t>(aRotationIndex)];
    aRotationIndex++;

    *pResult = aStatement;
    return true;
}

bool GAXSK::MakeIngressCrushStatement(GAXSKVariable pTarget,
                                      const std::vector<GAXSKVariable> &pOrbiters,
                                      GAXSKStatement *pResult,
                                      std::string *pErrorMessage) {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::MakeIngressCrushStatement received null result");
        return false;
    }

    if (pTarget != GAXSKVariable::kIngress) {
        SetError(pErrorMessage, "GAXSK::MakeIngressCrushStatement target must be ingress");
        return false;
    }

    if (pOrbiters.empty()) {
        SetError(pErrorMessage, "GAXSK::MakeIngressCrushStatement received no orbiters");
        return false;
    }

    for (GAXSKVariable aOrbiter : pOrbiters) {
        if (!IsOrbiterVariable(aOrbiter)) {
            SetError(pErrorMessage, "GAXSK::MakeIngressCrushStatement received non-orbiter variable");
            return false;
        }
    }

    GAXSKStatement aStatement;
    aStatement.mKind = GAXSKStatementKind::kIngressCrush;
    aStatement.mTarget = pTarget;

    GAXSKCrushPlan &aPlan = aStatement.mCrush;
    aPlan.mTarget = pTarget;
    aPlan.mPairs.clear();
    aPlan.mHasOdd = false;
    aPlan.mOdd = GAXSKCrushOddPlan();

    aPlan.mHasDiffuse = true;

    std::vector<GAXSKDiffuseKind> aDiffuseList = {
        GAXSKDiffuseKind::kDiffuseA,
        GAXSKDiffuseKind::kDiffuseB,
        GAXSKDiffuseKind::kDiffuseC
    };
    aPlan.mDiffuse = Random::Choice(aDiffuseList);

    std::vector<GAXSKVariable> aOrbiters = pOrbiters;
    Random::Shuffle(&aOrbiters);

    const int aPairCount = static_cast<int>(aOrbiters.size()) / 2;
    const bool aHasOdd = ((aOrbiters.size() & 1U) != 0U);

    aPlan.mOuterOp = GAXSKOpKind::kAdd;

    const int aRotationCount = static_cast<int>(aOrbiters.size());
    
    const int aMinimumDistance =
        CrushRotationDistanceForFormat(aRotationCount);

    std::vector<int> aRotations;
    if (!ChooseUpdateRotations(aRotationCount,
                               aMinimumDistance,
                               true,
                               &aRotations,
                               pErrorMessage)) {
        return false;
    }

    int aRotationIndex = 0;

    for (int aPairIndex = 0; aPairIndex < aPairCount; ++aPairIndex) {
        const int aOrbiterIndexA = aPairIndex * 2;
        const int aOrbiterIndexB = aOrbiterIndexA + 1;

        GAXSKCrushPairPlan aPair;
        aPair.mA = aOrbiters[static_cast<std::size_t>(aOrbiterIndexA)];
        aPair.mB = aOrbiters[static_cast<std::size_t>(aOrbiterIndexB)];

        aPair.mRotateA = Random::Bool();
        aPair.mRotation = aRotations[static_cast<std::size_t>(aRotationIndex)];
        aRotationIndex++;

        aPair.mOp = GAXSKOpKind::kXor;

        aPlan.mPairs.push_back(aPair);
    }

    if (aHasOdd) {
        aPlan.mHasOdd = true;
        aPlan.mOdd.mVariable = aOrbiters.back();
        aPlan.mOdd.mHasRotation = true;
        aPlan.mOdd.mRotation = aRotations[static_cast<std::size_t>(aRotationIndex)];
        aRotationIndex++;
    }

    *pResult = aStatement;
    return true;
}

bool GAXSK::MakeScatterMixStatement(GAXSKStatement *pResult,
                                    std::string *pErrorMessage) {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::MakeScatterMixStatement received null result");
        return false;
    }

    pResult->mKind = GAXSKStatementKind::kScatterMix;
    pResult->mTarget = GAXSKVariable::kScatter;

    GAXSKScatterMixPlan &aPlan = pResult->mScatterMix;

    aPlan.mTarget = GAXSKVariable::kScatter;
    aPlan.mHasDomainMix = mHasDomainMix;

    std::vector<GAXSKDiffuseKind> aDiffuseList = {
        GAXSKDiffuseKind::kDiffuseA,
        GAXSKDiffuseKind::kDiffuseB,
        GAXSKDiffuseKind::kDiffuseC
    };
    aPlan.mDiffuse = Random::Choice(aDiffuseList);

    // Legal base layout:
    //
    //   pair A: ingress with carry
    //   pair B: previous with cross
    //
    // This avoids ingress with previous.
    aPlan.mLeftPair.mLeft.mVariable = GAXSKVariable::kIngress;
    aPlan.mLeftPair.mRight.mVariable = GAXSKVariable::kCarry;

    aPlan.mRightPair.mLeft.mVariable = GAXSKVariable::kPrevious;
    aPlan.mRightPair.mRight.mVariable = GAXSKVariable::kCross;

    if (Random::Bool()) { std::swap(aPlan.mLeftPair.mLeft, aPlan.mRightPair.mLeft); }
    if (Random::Bool()) { std::swap(aPlan.mLeftPair, aPlan.mRightPair); }
    if (Random::Bool()) { std::swap(aPlan.mLeftPair.mLeft, aPlan.mLeftPair.mRight); }
    if (Random::Bool()) { std::swap(aPlan.mRightPair.mLeft, aPlan.mRightPair.mRight); }
    
    static const std::vector<int> kGAXSKOddRotations = { 3, 5, 11, 13, 19, 21, 23, 27, 29, 35, 37, 39, 41, 43, 47, 51, 53, 57 };
    static const std::vector<int> kGAXSKEvenRotations = { 4, 6, 10, 12, 14, 18, 20, 22, 24, 26, 28, 30, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60 };

    int aWhichEven = Random::Get(4);

    std::vector<int> aRotations;
    aRotations.resize(4);

    int aTryCount = 0;

    do {
        for (std::size_t aIndex = 0; aIndex < aRotations.size(); aIndex++) {
            if (static_cast<int>(aIndex) == aWhichEven) {
                aRotations[aIndex] = Random::Choice(kGAXSKEvenRotations);
            } else {
                aRotations[aIndex] = Random::Choice(kGAXSKOddRotations);
            }
        }

        aTryCount++;
        if (aTryCount > 10000) {
            SetError(pErrorMessage, "GAXSK::MakeScatterMixStatement failed to choose scatter rotations");
            return false;
        }
    } while (RotationsClash_64_12(aRotations));
    
    aPlan.mLeftPair.mLeft.mRotation = aRotations[0];
    aPlan.mLeftPair.mRight.mRotation = aRotations[1];
    aPlan.mRightPair.mLeft.mRotation = aRotations[2];
    aPlan.mRightPair.mRight.mRotation = aRotations[3];
    
    static const std::vector<GAXSKScatterMixOp> kScatterMixOps = {
        GAXSKScatterMixOp::kAdd,
        GAXSKScatterMixOp::kXor
    };

    std::vector<GAXSKScatterMixOp> aOps;
    aOps.resize(3);

    do {
        aOps[0] = Random::Choice(kScatterMixOps);
        aOps[1] = Random::Choice(kScatterMixOps);
        aOps[2] = Random::Choice(kScatterMixOps);
    } while (TwistArray::AllEqual(&aOps));

    aPlan.mLeftPair.mOp = aOps[0];
    aPlan.mRightPair.mOp = aOps[1];
    aPlan.mOuterOp = aOps[2];

    return true;
}

static int MinimumRotationDistanceForFormat(GAXSFormat pFormat,
                                            int pRotationCount) {
    if (pRotationCount <= 1) {
        return 12;
    }

    switch (pFormat) {
        case GAXSFormat::kN5:
            return pRotationCount >= 4 ? 8 : 12;

        case GAXSFormat::kN7:
            return pRotationCount >= 6 ? 6 : 12;

        case GAXSFormat::kN9:
            return pRotationCount >= 8 ? 4 : 8;

        case GAXSFormat::kN11:
            return pRotationCount >= 10 ? 2 : 4;

        default:
            return 8;
    }
}

bool GAXSK::InfuseUpdateRotationSlots(std::vector<GAXSKUpdateRotationSlot> *pSlots,
                                      GAXSKUpdateRotationParityMode pParityMode,
                                      std::string *pErrorMessage) {
    if (pSlots == nullptr) {
        SetError(pErrorMessage, "GAXSK::InfuseUpdateRotationSlots received null slots");
        return false;
    }

    int aRotationCount = static_cast<int>(pSlots->size());
    if (aRotationCount <= 0) {
        return true;
    }

    const int aMinimumDistance = MinimumRotationDistanceForFormat(mFormat, aRotationCount);
    
    std::vector<int> aRotations;
    if (!ChooseUpdateRotations(aRotationCount,
                               aMinimumDistance,
                               pParityMode == GAXSKUpdateRotationParityMode::kAllowEven,
                               &aRotations,
                               pErrorMessage)) {
        return false;
    }

    for (int aIndex = 0; aIndex < aRotationCount; aIndex++) {
        GAXSKUpdateRotationSlot &aSlot = (*pSlots)[static_cast<std::size_t>(aIndex)];

        if (aSlot.mTerm != nullptr) {
            aSlot.mTerm->mRotation = aRotations[static_cast<std::size_t>(aIndex)];
        } else if (aSlot.mStatementRotation != nullptr) {
            *(aSlot.mStatementRotation) = aRotations[static_cast<std::size_t>(aIndex)];
        }
    }

    return true;
}

bool GAXSK::BuildSkeletonForLaneCount(int pPassIndex,
                                      int pLaneCount,
                                      GAXSKSkeleton *pSkeleton,
                                      std::string *pErrorMessage) {
    if (pSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount received null skeleton");
        return false;
    }
    
    if (pPassIndex < 0) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount received negative pass index");
        return false;
    }
    
    if (static_cast<std::size_t>(pPassIndex) >= mPools.size()) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount pass index exceeded pool count");
        return false;
    }
    
    if ((pLaneCount < 1) || (pLaneCount > 4)) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount lane count must be 1, 2, 3, or 4");
        return false;
    }
    
    GAXSKPool *aPool = mPools[static_cast<std::size_t>(pPassIndex)];
    if (aPool == nullptr) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount found null pool");
        return false;
    }
    
    GAXSKInputSlotOrdering aOrdering;
    if (!aPool->GenerateInputSlotOrdering(&aOrdering, pErrorMessage)) {
        return false;
    }
    
    if (aOrdering.mIngress.empty()) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount received empty ingress ordering");
        return false;
    }
    
    if (aOrdering.mCross.empty()) {
        SetError(pErrorMessage, "GAXSK::BuildSkeletonForLaneCount received empty cross ordering");
        return false;
    }
    
    pSkeleton->mStatements.clear();
    
    pSkeleton->mStatements.push_back(MakePreviousAssignStatement());
    
    std::vector<GAXSKDiffuseKind> aDiffuseList = { GAXSKDiffuseKind::kDiffuseA, GAXSKDiffuseKind::kDiffuseB, GAXSKDiffuseKind::kDiffuseC };
    
    GAXSKStatement aIngress = MakeContextWordStatement(GAXSKVariable::kIngress,
                                                       Random::Choice(aDiffuseList),
                                                       true);
    
    GAXSKStatement aCross = MakeContextWordStatement(GAXSKVariable::kCross,
                                                     Random::Choice(aDiffuseList),
                                                     false);
    
    aIngress.mContextWord.mSlots = aOrdering.mIngress;
    aCross.mContextWord.mSlots = aOrdering.mCross;
    
    pSkeleton->mStatements.push_back(aIngress);
    pSkeleton->mStatements.push_back(aCross);
    
    GAXSKStatement aScatter;
    if (!MakeScatterMixStatement(&aScatter, pErrorMessage)) {
        return false;
    }
    pSkeleton->mStatements.push_back(aScatter);
    
    GAXSKModel aModel = MakeModelForFormatPass(mFormat, pPassIndex);
    
    if (!FinishModelStatements(aModel,
                               &pSkeleton->mStatements,
                               pErrorMessage)) {
        return false;
    }
    
    
    
    
    

    return true;
}

bool GAXSK::MakeModelUpdateStatement(const GAXSKModelStatement &pModelStatement,
                                     GAXSKStatement *pResult,
                                     std::string *pErrorMessage) {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::MakeModelUpdateStatement received null result");
        return false;
    }

    if (pModelStatement.mTarget == GAXSKVariable::kInvalid) {
        SetError(pErrorMessage, "GAXSK::MakeModelUpdateStatement received invalid target");
        return false;
    }

    GAXSKStatement aStatement;
    aStatement.mTarget = pModelStatement.mTarget;
    aStatement.mUpdate.mTarget = pModelStatement.mTarget;

    const bool aIsOrbiter = IsOrbiterVariable(pModelStatement.mTarget);
    const bool aIsWanderer = IsWandererVariable(pModelStatement.mTarget);

    if (!aIsOrbiter && !aIsWanderer) {
        SetError(pErrorMessage, "GAXSK::MakeModelUpdateStatement target is not orbiter or wanderer");
        return false;
    }

    switch (pModelStatement.mOperation) {
        case GAXSKModelOperation::kSet:
            if (!aIsOrbiter) {
                SetError(pErrorMessage, "GAXSK::MakeModelUpdateStatement kSet currently only supports orbiters");
                return false;
            }
            aStatement.mKind = GAXSKStatementKind::kOrbiterAssign;
            break;

        case GAXSKModelOperation::kAdd:
            aStatement.mKind = aIsOrbiter
                ? GAXSKStatementKind::kOrbiterAdd
                : GAXSKStatementKind::kWandererAdd;
            break;

        case GAXSKModelOperation::kXor:
            aStatement.mKind = aIsOrbiter
                ? GAXSKStatementKind::kOrbiterXor
                : GAXSKStatementKind::kWandererXor;
            break;

        case GAXSKModelOperation::kMulRotate:
            aStatement.mKind = aIsOrbiter
                ? GAXSKStatementKind::kOrbiterMulRotate
                : GAXSKStatementKind::kWandererMulRotate;
            break;

        default:
            SetError(pErrorMessage, "GAXSK::MakeModelUpdateStatement received invalid operation");
            return false;
    }

    for (const GAXSKModelTerm &aModelTerm : pModelStatement.mTerms) {
        GAXSKUpdateTerm aTerm;

        aTerm.mKind = aModelTerm.mKind;
        aTerm.mVariable = aModelTerm.mVariable;
        aTerm.mHotIndex = aModelTerm.mHotIndex;
        aTerm.mHasRotation = aModelTerm.mNeedsRotation;
        aTerm.mRotation = -1;
        aStatement.mUpdate.mTerms.push_back(aTerm);
    }

    aStatement.mUpdate.mHasRotation = pModelStatement.mNeedsRotation;
    aStatement.mUpdate.mRotation = -1;

    *pResult = aStatement;
    return true;
}

bool GAXSK::FinishModelStatements(const GAXSKModel &pModel,
                                  std::vector<GAXSKStatement> *pStatements,
                                  std::string *pErrorMessage) {
    
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXSK::FinishModelStatements received null statements");
        return false;
    }
    
    std::vector<GAXSKStatement> aUpdateStatements;
    aUpdateStatements.reserve(pModel.mStatements.size());

    std::vector<GAXSKUpdateRotationSlot> aOrbiterAssignContextSlots;
    std::vector<GAXSKUpdateRotationSlot> aOrbiterAssignCarrySlots;
    std::vector<GAXSKUpdateRotationSlot> aOrbiterUpdateContextSlots;
    std::vector<GAXSKUpdateRotationSlot> aOrbiterHotMulSlots;

    std::vector<GAXSKUpdateRotationSlot> aWandererContextSlots;
    std::vector<GAXSKUpdateRotationSlot> aWandererOrbiterSlots;
    std::vector<GAXSKUpdateRotationSlot> aWandererCarrySlots;

    auto AddTermSlot = [](std::vector<GAXSKUpdateRotationSlot> *pSlots,
                          GAXSKUpdateTerm *pTerm) {
        if ((pSlots == nullptr) || (pTerm == nullptr)) {
            return;
        }

        GAXSKUpdateRotationSlot aSlot;
        aSlot.mTerm = pTerm;
        pSlots->push_back(aSlot);
    };

    auto AddStatementSlot = [](std::vector<GAXSKUpdateRotationSlot> *pSlots,
                               int *pRotation) {
        if ((pSlots == nullptr) || (pRotation == nullptr)) {
            return;
        }

        GAXSKUpdateRotationSlot aSlot;
        aSlot.mStatementRotation = pRotation;
        pSlots->push_back(aSlot);
    };

    auto IsContextVariable = [](GAXSKVariable pVariable) -> bool {
        switch (pVariable) {
            case GAXSKVariable::kIngress:
            case GAXSKVariable::kScatter:
            case GAXSKVariable::kPrevious:
            case GAXSKVariable::kCross:
                return true;

            default:
                return false;
        }
    };

    for (const GAXSKModelStatement &aModelStatement : pModel.mStatements) {
        GAXSKStatement aUpdateStatement;

        if (!MakeModelUpdateStatement(aModelStatement,
                                      &aUpdateStatement,
                                      pErrorMessage)) {
            return false;
        }

        aUpdateStatements.push_back(aUpdateStatement);
    }

    for (GAXSKStatement &aStatement : aUpdateStatements) {
        const bool aIsOrbiterAssign = (aStatement.mKind == GAXSKStatementKind::kOrbiterAssign);

        const bool aIsOrbiterUpdate = (aStatement.mKind == GAXSKStatementKind::kOrbiterAdd ||
                                       aStatement.mKind == GAXSKStatementKind::kOrbiterXor);

        const bool aIsOrbiterMul = (aStatement.mKind == GAXSKStatementKind::kOrbiterMulRotate);

        const bool aIsWandererUpdate = (aStatement.mKind == GAXSKStatementKind::kWandererAdd ||
                                        aStatement.mKind == GAXSKStatementKind::kWandererXor);

        if (aIsOrbiterMul && aStatement.mUpdate.mHasRotation) {
            AddStatementSlot(&aOrbiterHotMulSlots, &aStatement.mUpdate.mRotation);
        }

        for (GAXSKUpdateTerm &aTerm : aStatement.mUpdate.mTerms) {
            if (!aTerm.mHasRotation) {
                continue;
            }

            if (aIsOrbiterAssign && IsContextVariable(aTerm.mVariable)) {
                AddTermSlot(&aOrbiterAssignContextSlots, &aTerm);
            } else if (aIsOrbiterAssign && aTerm.mVariable == GAXSKVariable::kCarry) {
                AddTermSlot(&aOrbiterAssignCarrySlots, &aTerm);
            } else if (aIsOrbiterUpdate && IsContextVariable(aTerm.mVariable)) {
                AddTermSlot(&aOrbiterUpdateContextSlots, &aTerm);
            } else if (aIsWandererUpdate && IsContextVariable(aTerm.mVariable)) {
                AddTermSlot(&aWandererContextSlots, &aTerm);
            } else if (aIsWandererUpdate && aTerm.mVariable == GAXSKVariable::kCarry) {
                AddTermSlot(&aWandererCarrySlots, &aTerm);
            } else if (aIsWandererUpdate && IsOrbiterVariable(aTerm.mVariable)) {
                AddTermSlot(&aWandererOrbiterSlots, &aTerm);
            }
        }
    }

    if (!InfuseUpdateRotationSlots(&aOrbiterAssignContextSlots,
                                   GAXSKUpdateRotationParityMode::kAllowEven,
                                   pErrorMessage)) { return false; }

    if (!InfuseUpdateRotationSlots(&aOrbiterAssignCarrySlots,
                                   GAXSKUpdateRotationParityMode::kSuppressEven,
                                   pErrorMessage)) { return false; }

    if (!InfuseUpdateRotationSlots(&aOrbiterUpdateContextSlots,
                                   GAXSKUpdateRotationParityMode::kAllowEven,
                                   pErrorMessage)) { return false; }

    if (!InfuseUpdateRotationSlots(&aOrbiterHotMulSlots,
                                   GAXSKUpdateRotationParityMode::kSuppressEven,
                                   pErrorMessage)) { return false; }

    if (!InfuseUpdateRotationSlots(&aWandererContextSlots,
                                   GAXSKUpdateRotationParityMode::kAllowEven,
                                   pErrorMessage)) { return false; }

    if (!InfuseUpdateRotationSlots(&aWandererOrbiterSlots,
                                   GAXSKUpdateRotationParityMode::kAllowEven,
                                   pErrorMessage)) { return false; }

    if (!InfuseUpdateRotationSlots(&aWandererCarrySlots,
                                   GAXSKUpdateRotationParityMode::kSuppressEven,
                                   pErrorMessage)) { return false; }

    bool aDidInsertIngressCrush = false;
    bool aDidCommentWandererUpdate = false;

    for (std::size_t aIndex = 0U; aIndex < aUpdateStatements.size(); ++aIndex) {
        const GAXSKStatement &aStatement = aUpdateStatements[aIndex];

        const bool aIsOrbiterAssign =
            aStatement.mKind == GAXSKStatementKind::kOrbiterAssign;

        const bool aIsOrbiterMulRotate =
            aStatement.mKind == GAXSKStatementKind::kOrbiterMulRotate;

        const bool aIsWandererUpdate =
            aStatement.mKind == GAXSKStatementKind::kWandererAdd ||
            aStatement.mKind == GAXSKStatementKind::kWandererXor ||
            aStatement.mKind == GAXSKStatementKind::kWandererMulRotate;

        if (!aDidInsertIngressCrush && aIsWandererUpdate) {
            GAXSKStatement aIngressCrush;

            if (!MakeIngressCrushStatement(GAXSKVariable::kIngress,
                                           pModel.mOrbiters,
                                           &aIngressCrush,
                                           pErrorMessage)) {
                return false;
            }

            pStatements->push_back(aIngressCrush);
            aDidInsertIngressCrush = true;
        }

        if (aIsWandererUpdate && !aDidCommentWandererUpdate) {
            pStatements->push_back(MakeCommentStatement());
            aDidCommentWandererUpdate = true;
        }

        pStatements->push_back(aStatement);

        const bool aHasNext = ((aIndex + 1U) < aUpdateStatements.size());

        bool aNextIsOrbiterAssign = false;
        if (aHasNext) {
            const GAXSKStatement &aNextStatement = aUpdateStatements[aIndex + 1U];
            aNextIsOrbiterAssign =
                aNextStatement.mKind == GAXSKStatementKind::kOrbiterAssign;
        }

        // 1.0: after the orbiter-assign block.
        if (aIsOrbiterAssign && !aNextIsOrbiterAssign) {
            pStatements->push_back(MakeCommentStatement());
        }

        // 2.0: after each orbiter update triplet.
        if (aIsOrbiterMulRotate) {
            pStatements->push_back(MakeCommentStatement());
        }
    }

    if (!aDidInsertIngressCrush) {
        SetError(pErrorMessage, "GAXSK::FinishModelStatements failed to insert ingress crush");
        return false;
    }
    
    GAXSKStatement aCarryCrush;

    if (!MakeCarryMixStatement(pModel.mWanderers,
                               &aCarryCrush,
                               pErrorMessage)) {
        return false;
    }

    pStatements->push_back(aCarryCrush);
    
    return true;
}

bool GAXSK::Bake(GAXSFormat pFormat,
                 std::vector<int> pLaneCounts,
                 bool pHasDomainMix,
                 std::vector<GAXSKSkeleton> *pResult,
                 std::string *pErrorMessage) {
    Reset();

    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXSK::Bake received null result");
        return false;
    }

    pResult->clear();

    mFormat = pFormat;
    mHasDomainMix = pHasDomainMix;
    mLaneCounts = pLaneCounts;

    int aPassCount = 0;
    if (!GetPassCount(&aPassCount, pErrorMessage)) {
        return false;
    }

    if (aPassCount >= 8) {
        SetError(pErrorMessage,
                 std::string("GAXSK::Bake invalid pass count: ") + std::to_string(aPassCount));
        return false;
    }

    mPools.reserve(static_cast<std::size_t>(aPassCount));
    for (int aPoolIndex = 0; aPoolIndex < aPassCount; aPoolIndex++) {
        mPools.push_back(new GAXSKPool());
    }

    for (int aPassIndex = 0; aPassIndex < aPassCount; aPassIndex++) {
        int aLaneCount = 0;
        if (!GetLaneCountForPass(aPassIndex,
                                 &aLaneCount,
                                 pErrorMessage)) {
            return false;
        }
        
        int aOrbiterCount = 0;
        if (!GetOrbiterCount(&aOrbiterCount, pErrorMessage)) {
            return false;
        }

        int aWandererCount = 0;
        if (!GetWandererCount(&aWandererCount, pErrorMessage)) {
            return false;
        }
        
        mPools[aPassIndex]->SetSourceCount(aLaneCount);
        mPools[aPassIndex]->SetOrbiterCount(aOrbiterCount);
        mPools[aPassIndex]->SetWandererCount(aWandererCount);
        
        if (!mPools[aPassIndex]->FinalizeCounts(pErrorMessage)) {
            return false;
        }
        

        GAXSKSkeleton aSkeleton;

        if (!BuildSkeletonForLaneCount(aPassIndex,
                                       aLaneCount,
                                       &aSkeleton,
                                       pErrorMessage)) {
            pResult->clear();
            return false;
        }

        pResult->push_back(aSkeleton);
    }

    return true;
}
