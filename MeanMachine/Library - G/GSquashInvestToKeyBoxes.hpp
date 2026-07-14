//
//  GSquashInvestToKeyBoxes.hpp
//  MeanMachine
//

#ifndef GSquashInvestToKeyBoxes_hpp
#define GSquashInvestToKeyBoxes_hpp

#include "GTwistExpander.hpp"

#include <string>

class GSquashInvestToKeyBoxes {
public:
    bool                        Build(TwistProgramBranch &pBranch,
                                      std::string *pErrorMessage) {
        (void)pErrorMessage;

        pBranch.AddLine("// GSquashInvestToKeyBoxes (start)");
        pBranch.AddLine("SquashInvestToKeyBoxes();");
        pBranch.AddLine("// GSquashInvestToKeyBoxes (end)");
        pBranch.AddLine("//");

        return true;
    }
};

#endif /* GSquashInvestToKeyBoxes_hpp */
