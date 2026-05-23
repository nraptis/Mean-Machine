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
#include "GMagicNumbers.hpp"


#include <string>
#include <vector>
#include <unordered_map>

struct GAXPLSaltBag {
    std::vector<GSymbol>                                mOrbiterAssign; // 2 salts
    std::vector<GSymbol>                                mOrbiterUpdate; // 4 salts
    std::vector<GSymbol>                                mWandererUpdate; // 2 salts
};

struct SaltBehavior {
    bool mReversed = false;
    int mOffset = -1;
};

struct NonceBehavior {
    int mRotation = -1;
};

struct NonceSymbolChoice {
    GSymbol mSymbol;
    bool mPreferred = false;
    bool mUseFullNonce = false;
};

class GAXPL {
public:
    
    bool                                                MakeSaltBehaviors(std::vector<SaltBehavior> *pResult,
                                                                          std::string *pErrorMessage) const;
    
    bool                                                MakeNonceBehaviors(std::vector<NonceBehavior> *pResult,
                                                                           std::string *pErrorMessage) const;
    
    
    
    void                                                Reset();
    
    bool                                                Bake(const GAXSKSkeleton *pSkeleton,
                                                             const GAXPLSaltBag &pSaltBag,
                                                             const std::vector<GSymbol> &pNonceBytes,
                                                             const std::vector<GSymbol> &pSources,
                                                             const std::vector<GSymbol> &pOrbiters,
                                                             const std::vector<GSymbol> &pWanderers,
                                                             GHotPack pHotPack,
                                                             bool pUseFullNonce,
                                                             GSymbol pDest,
                                                             bool pDestWriteInverted,
                                                             GLoop *pLoop,
                                                             std::string *pErrorMessage);
    
    bool                                                Configure(const GAXSKSkeleton *pSkeleton,
                                                                  const GAXPLSaltBag &pSaltBag,
                                                                  const std::vector<GSymbol> &pNonceBytes,
                                                                  const std::vector<GSymbol> &pSources,
                                                                  const std::vector<GSymbol> &pOrbiters,
                                                                  const std::vector<GSymbol> &pWanderers,
                                                                  GHotPack pHotPack,
                                                                  bool pUseFullNonce,
                                                                  GSymbol pDest,
                                                                  bool pDestWriteInverted,
                                                                  GLoop *pLoop,
                                                                  std::string *pErrorMessage);
    
    
    bool                                                MakeHotAddExpr(int pHotIndex,
                                                                       GExpr *pResult,
                                                                       std::string *pErrorMessage) const;
    
    bool                                                MakeHotMulExpr(int pHotIndex,
                                                                       GExpr *pResult,
                                                                       std::string *pErrorMessage) const;
    
    bool                                                MakeVariableTermExpr(const GAXSKUpdateTerm &pTerm,
                                                                             GExpr *pResult,
                                                                             std::string *pErrorMessage) const;
    
    bool                                                MakeUpdateTermExpr(const GAXSKUpdateTerm &pTerm,
                                                                           GExpr *pResult,
                                                                           std::string *pErrorMessage) const;
    
    bool                                                GenerateCarryCrushStatement(const GAXSKStatement &pStatement,
                                     std::vector<GStatement> *pStatements,
                                     std::string *pErrorMessage);
    
    
    bool                                                MakeUpdateTerms(const GAXSKUpdatePlan &pPlan,
                                                                        std::vector<GExpr> *pTerms,
                                                                        std::string *pErrorMessage) const;
    
    bool                                                EmitAddAssign(GSymbol pTarget,
                                                                      std::vector<GExpr> pTerms,
                                                                      const GExpr &pSaltExpr,
                                                                      const GExpr &pNonceExpr,
                                                                      std::vector<GStatement> *pStatements,
                                                                      std::string *pErrorMessage) const;
    
    bool                                                EmitXorAssign(GSymbol pTarget,
                                                                      std::vector<GExpr> pTerms,
                                                                      const GExpr &pSaltExpr,
                                                                      const GExpr &pNonceExpr,
                                                                      std::vector<GStatement> *pStatements,
                                                                      std::string *pErrorMessage) const;
    
    bool                                                EmitMulRotate(const GAXSKUpdatePlan &pPlan,
                                                                      GSymbol pTarget,
                                                                      std::vector<GStatement> *pStatements,
                                                                      std::string *pErrorMessage) const;
    
    bool                                                EmitWandererUpdate(const GAXSKUpdatePlan &pPlan,
                                                                           GSymbol pTarget,
                                                                           bool pUseXorBoundary,
                                                                           const GExpr &pSaltExpr,
                                                                           const GExpr &pNonceExpr,
                                                                           std::vector<GStatement> *pStatements,
                                                                           std::string *pErrorMessage) const;
    
    
    const GAXSKSkeleton                                 *mSkeleton = nullptr;
    GLoop                                               *mLoop = nullptr;
    
    std::vector<GSymbol>                                mSaltsOrbiterAssign;
    std::vector<GSymbol>                                mSaltsOrbiterUpdate;
    std::vector<GSymbol>                                mSaltsWandererUpdate;
    std::vector<GSymbol>                                mNonceBytes;
    std::vector<GSymbol>                                mSources;
    std::vector<GSymbol>                                mOrbiters;
    std::vector<GSymbol>                                mWanderers;
    
    GHotPack                                            mHotPack;
    
    GSymbol                                             mDest;
    bool                                                mDestWriteInverted;
    
    std::unordered_map<GAXSKSourceKind, GSymbol>        mSourceMap;
    std::unordered_map<GAXSKNonceByteKind, GSymbol>     mNonceMap;
    std::unordered_map<GAXSKVariable, GSymbol>          mOrbiterMap;
    std::unordered_map<GAXSKVariable, GSymbol>          mWandererMap;
    
    std::unordered_map<int, GExpr>                      mSaltExprMap;
    std::unordered_map<int, GExpr>                      mNonceExprMap;
    
    std::vector<SaltBehavior>                           mSaltBehaviors;
    std::vector<NonceBehavior>                          mNonceBehaviors;
    
    
    std::vector<GSymbol>                                mPreferredNonceSymbols;
    std::vector<GSymbol>                                mFallbackNonceSymbols;
    std::vector<NonceSymbolChoice>                      mNonceChoices;
    
    bool                                                mUseFullNonce = false;
    
    bool                                                BuildNonceChoices(std::string *pErrorMessage);
    
    bool                                                BuildSaltExprMap(std::string *pErrorMessage);
    
    bool                                                BuildSaltExprMapForRole(GAXSKSaltRole pRole,
                                                                                int pSaltCount,
                                                                                const std::vector<GSymbol> &pSaltSymbols,
                                                                                int *pBehaviorIndex,
                                                                                std::string *pErrorMessage);
    
    bool                                                BuildNonceExprMap(std::string *pErrorMessage);
    
    bool                                                BuildNonceExprMapForRole(GAXSKSaltRole pRole,
                                                                                 int pNonceCount,
                                                                                 int *pBehaviorIndex,
                                                                                 std::string *pErrorMessage);
    
    
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
    
    bool                                                GenerateUpdateStatement(int pStatementIndex,
                                                                                const GAXSKStatement &pStatement,
                                                                                std::vector<GStatement> *pStatements,
                                                                                std::string *pErrorMessage);
    
    // store maps as member variables, so we do not need to pass them all over.
    
    bool                                                GenerateIngressCrushStatement(const GAXSKStatement &pStatement,
                                                                                      std::vector<GStatement> *pStatements,
                                                                                      std::string *pErrorMessage);
    
    bool                                                MakeCrushPairExpr(const GAXSKCrushPairPlan &pPair,
                                                                          GExpr *pResult,
                                                                          std::string *pErrorMessage) const;
    
    
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
