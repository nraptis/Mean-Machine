//
//  StatementChecker.hpp
//  CornTesting
//
//  Created by Trombone on 4/26/26.
//

#ifndef StatementChecker_hpp
#define StatementChecker_hpp

#include "TwistWorkSpace.hpp"
#include "GSymbol.hpp"
#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "GLoopFragmentComposer.hpp"
#include "Varz.hpp"

class StatementChecker {
public:
    StatementChecker();
    ~StatementChecker();
    
    static bool                             Eval(const std::vector<GStatement> &pStatements,
                                                 const std::vector<std::string> &pExpected);
    
    
    
};

#endif /* StatementChecker_hpp */
