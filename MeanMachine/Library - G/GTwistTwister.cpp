//
//  GTwistTwister.cpp
//  MeanMachine
//

#include "GTwistTwister.hpp"

GTwistTwister::GTwistTwister()
: GTwistExpander() {
}

GTwistTwister::~GTwistTwister() {
}

bool GTwistTwister::LoadProjectRoot(const std::string &pJsonPath,
                                    std::string *pErrorMessage) {
    return LoadJSONProjectRoot(pJsonPath, pErrorMessage);
}
