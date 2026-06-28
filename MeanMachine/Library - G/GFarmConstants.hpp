//
//  GFarmConstants.hpp
//  MeanMachine
//

#ifndef GFarmConstants_hpp
#define GFarmConstants_hpp

#include "GSeedProgram.hpp"

#include <string>
#include <vector>

class GFarmConstants {
public:
    bool                                Bake(const std::string &pSource,
                                             const std::string &pConstants,
                                             std::vector<GStatement> *pStatements,
                                             std::string *pErrorMessage) {
        if (pErrorMessage != nullptr) {
            pErrorMessage->clear();
        }

        if (pStatements == nullptr) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GFarmConstants::Bake requires statement output.";
            }
            return false;
        }
        if (pSource.empty() || pConstants.empty()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GFarmConstants::Bake requires source and constants expressions.";
            }
            return false;
        }

        pStatements->push_back(GStatement::RawLine(
            "TwistFarmConstants::Derive(" + pSource + ", &(" + pConstants + "));"));
        return true;
    }
};

#endif /* GFarmConstants_hpp */
