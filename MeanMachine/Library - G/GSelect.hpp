//
//  GSelect.hpp
//  MeanMachine
//
//  Created by Dragon on 4/30/26.
//

#ifndef GSelect_hpp
#define GSelect_hpp


#include "GSeedProgram.hpp"
#include "GSymbol.hpp"
#include <cstdint>

class GSelect {
public:
    GSelect();
    
    static GSelect              Random4();
    static GSelect              Random2();
    
    static GSelect              Demo4(int pIndex1, int pIndex2);
    static GSelect              Demo2(int pIndex1, int pIndex2);
    
    std::uint8_t                mMask;
    std::uint8_t                mThresholdA;
    std::uint8_t                mThresholdB;
    std::uint8_t                mThresholdC;
    
    void                        AddStatementsA(std::vector<GStatement> *pStatements);
    void                        AddStatementA(GStatement *pStatement);
    
    void                        AddStatementsB(std::vector<GStatement> *pStatements);
    void                        AddStatementB(GStatement *pStatement);
    
    void                        AddStatementsC(std::vector<GStatement> *pStatements);
    void                        AddStatementC(GStatement *pStatement);
    
    void                        AddStatementsD(std::vector<GStatement> *pStatements);
    void                        AddStatementD(GStatement *pStatement);
    
    bool                        Bake(GSymbol pSelectVariable,
                                     GExpr pSelectValueExpr,
                                     std::vector<GStatement> *pStatements,
                                     std::string *pErrorMessage);
    bool                        Bake(GSymbol pSelectVariable,
                                     GSymbol pSelectValue,
                                     std::vector<GStatement> *pStatements,
                                     std::string *pErrorMessage);
    
    
        
    
private:
    std::vector<GStatement>         mStatementsAOwned;
    std::vector<GStatement>         mStatementsBOwned;
    std::vector<GStatement>         mStatementsCOwned;
    std::vector<GStatement>         mStatementsDOwned;
};

#endif /* GSelect_hpp */
