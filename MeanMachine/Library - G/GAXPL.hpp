//
//  GAXPL.hpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#ifndef GAXPL_hpp
#define GAXPL_hpp

#include "GAXSK.hpp"
#include "GQuick.hpp"
#include "GSeedProgram.hpp"

#include <string>
#include <vector>
#include <unordered_map>

struct GAXPLSaltBag {
    std::vector<GSymbol>                                mOrbiterAssign; // 2 salts
    std::vector<GSymbol>                                mOrbiterUpdate; // 4 salts
    std::vector<GSymbol>                                mWandererUpdate; // 2 salts
};

class GAXPL {
public:
    
    
    void                                                Reset();
    
    bool                                                Bake(const GAXSKSkeleton *pSkeleton,
                                                             const GAXPLSaltBag &pSaltBag,
                                                             const std::vector<GSymbol> &pNonceBytes,
                                                             const std::vector<GSymbol> &pSources,
                                                             const std::vector<GSymbol> &pOrbiters,
                                                             const std::vector<GSymbol> &pWanderers,
                                                             
                                                             GLoop *pLoop,
                                                             std::string *pErrorMessage);
    
    bool                                                Configure(const GAXSKSkeleton *pSkeleton,
                                                                  const GAXPLSaltBag &pSaltBag,
                                                                  const std::vector<GSymbol> &pNonceBytes,
                                                                  const std::vector<GSymbol> &pSources,
                                                                  const std::vector<GSymbol> &pOrbiters,
                                                                  const std::vector<GSymbol> &pWanderers,
                                                                  
                                                                  GLoop *pLoop,
                                                                  std::string *pErrorMessage);
    
    const GAXSKSkeleton                                 *mSkeleton = nullptr;
    GLoop                                               *mLoop = nullptr;
    
    std::vector<GSymbol>                                mSaltsOrbiterAssign;
    std::vector<GSymbol>                                mSaltsOrbiterUpdate;
    std::vector<GSymbol>                                mSaltsWandererUpdate;
    std::vector<GSymbol>                                mNonceBytes;
    std::vector<GSymbol>                                mSources;
    std::vector<GSymbol>                                mOrbiters;
    std::vector<GSymbol>                                mWanderers;
    
    std::unordered_map<GAXSKSourceKind, GSymbol>        mSourceMap;
    std::unordered_map<GAXSKNonceByteKind, GSymbol>     mNonceMap;
    std::unordered_map<GAXSKVariable, GSymbol>          mOrbiterMap;
    std::unordered_map<GAXSKVariable, GSymbol>          mWandererMap;
    
    
    bool                                                GenerateStatements(std::string *pErrorMessage);
    
    bool                                                GeneratePreviousAssignStatement(const GAXSKStatement &pStatement,
                                                                                        std::vector<GStatement> *pStatements,
                                                                                        std::string *pErrorMessage);
    
    bool                                                GenerateContextWordStatement(const GAXSKStatement &pStatement,
                                                                                     std::vector<GStatement> *pStatements,
                                                                                     std::string *pErrorMessage);
    
    bool                                                GenerateScatterMixStatement(const GAXSKStatement &pStatement,
                                                                                    std::vector<GStatement> *pStatements,
                                                                                    std::string *pErrorMessage);
    
    bool                                                GenerateUpdateStatement(const GAXSKStatement &pStatement,
                                                                                std::vector<GStatement> *pStatements,
                                                                                std::string *pErrorMessage);
    
    // store maps as member variables, so we do not need to pass them all over.
    
    
private:
    
    GAXSKVariable                                       GetOrbiterVariableForIndex(int pIndex) const;
    GAXSKVariable                                       GetWandererVariableForIndex(int pIndex) const;
    
    int                                                 GetOrbiterIndex(GAXSKVariable pVariable) const;
    int                                                 GetWandererIndex(GAXSKVariable pVariable) const;
    int                                                 GetNonceByteIndex(GAXSKNonceByteKind pNonce) const;
    int                                                 GetSourceIndex(GAXSKSourceKind pSource) const;
    
    bool                                                BuildSourceMap(std::string *pErrorMessage);
    bool                                                BuildNonceMap(std::string *pErrorMessage);
    bool                                                BuildOrbiterMap(std::string *pErrorMessage);
    bool                                                BuildWandererMap(std::string *pErrorMessage);
    
    bool                                                SymbolForVariable(GAXSKVariable pVariable,
                                                                          GSymbol *pResult,
                                                                          std::string *pErrorMessage) const;
    
};

#endif /* GAXPL_hpp */
