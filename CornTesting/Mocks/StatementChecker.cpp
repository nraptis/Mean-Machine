//
//  StatementChecker.cpp
//  CornTesting
//
//  Created by Trombone on 4/26/26.
//

#include "StatementChecker.hpp"
#include <algorithm>
#include <string>
#include <vector>

namespace {

std::vector<std::string> FlattenCPPStatements(const std::vector<GStatement> &pStatements) {
    std::vector<std::string> aLines;
    for (const GStatement &aStatement : pStatements) {
        const std::vector<std::string> aStatementLines = aStatement.ToCPPStatements();
        aLines.insert(aLines.end(), aStatementLines.begin(), aStatementLines.end());
    }
    return aLines;
}

} // namespace

StatementChecker::StatementChecker() {
    
}

StatementChecker::~StatementChecker() {
    
}

bool StatementChecker::Eval(const std::vector<GStatement> &pStatements,
                            const std::vector<std::string> &pExpected) {
    
    bool aResult = true;
    
    const std::vector<std::string> aStatementCPP = FlattenCPPStatements(pStatements);
    
    int aCount = static_cast<int>(std::min(aStatementCPP.size(), pExpected.size()));
    for (int i=0; i<aCount; i++) {
        if (aStatementCPP[i] != pExpected[i]) {
            printf("Statement at [%d] did not match.\n", i);
            printf("statement: %s\n", aStatementCPP[i].c_str());
            printf("expected: %s\n", pExpected[i].c_str());
            printf("$$$$$$$$$\n");
            
            aResult = false;
        }
    }
    
    for (int i = aCount; i < static_cast<int>(aStatementCPP.size()); i++) {
        printf("Statement at [%d] did not match.\n", i);
        printf("statement: %s\n", aStatementCPP[i].c_str());
        printf("no statement was expected.\n");
        printf("$$$$$$$$$\n");
        
        aResult = false;
    }
    
    for (int i=aCount;i<pExpected.size();i++) {
        printf("Statement at [%d] did not match.\n", i);
        printf("no statement existed.\n");
        printf("expected: %s\n", pExpected[i].c_str());
        aResult = false;
    }
    
    if (aResult == false) {
        printf("------\n");
        printf("Expected C++:\n\n");
        for (int i = 0; i < static_cast<int>(pExpected.size()); i++) {
            printf("%s\n", pExpected[i].c_str());
            aResult = false;
        }
        printf("\n------\n");
        printf("Generated C++:\n\n");
        for (int i = 0; i < static_cast<int>(aStatementCPP.size()); i++) {
            printf("%s\n", aStatementCPP[i].c_str());
            aResult = false;
        }
        printf("\n------\n");
        
    }
    
    
    return aResult;
}
