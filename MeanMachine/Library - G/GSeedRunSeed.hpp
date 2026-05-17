//
//  GSeedRunSeed.hpp
//  MeanMachine
//
//  Created by Codex on 5/11/26.
//

#ifndef GSeedRunSeed_hpp
#define GSeedRunSeed_hpp

#include "GKDF.hpp"
#include "GTwistExpander.hpp"

#include <string>

class GSeedRunSeed {
public:
    GSeedRunSeed();
    ~GSeedRunSeed();

    bool                                Plan(std::string *pErrorMessage);
    bool                                Build(TwistProgramBranch &pBranch, std::string *pErrorMessage);
};

#endif /* GSeedRunSeed_hpp */
