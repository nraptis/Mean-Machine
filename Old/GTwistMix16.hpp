//
//  GTwistMix16.hpp
//  MeanMachine
//
//  Created by Dragon on 4/29/26.
//

#ifndef GTwistMix16_hpp
#define GTwistMix16_hpp

#include "TwistMix16.hpp"
#include "GSymbol.hpp"
#include "GExpr.hpp"
#include "GSeedProgram.hpp"
#include "GLoopFragmentComposer.hpp"

class GTwistMix16 {
public:
    // Explicit S-box overloads.
    static bool            Mix161SetEqual(GSymbol pSymbol,
                                          Mix161Type pMixType,
                                          const GExpr &pExpr,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161AddEqual(GSymbol pSymbol,
                                          Mix161Type pMixType,
                                          const GExpr &pExpr,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161XorEqual(GSymbol pSymbol,
                                          Mix161Type pMixType,
                                          const GExpr &pExpr,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);

    static bool            Mix161SetEqual(GSymbol pSymbol,
                                          const GExpr &pExpr,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161AddEqual(GSymbol pSymbol,
                                          const GExpr &pExpr,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161XorEqual(GSymbol pSymbol,
                                          const GExpr &pExpr,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);

    static bool            Mix161SetEqual(GLoopFragmentComposer &pComposer,
                                          Mix161Type pMixType,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161AddEqual(GLoopFragmentComposer &pComposer,
                                          Mix161Type pMixType,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161XorEqual(GLoopFragmentComposer &pComposer,
                                          Mix161Type pMixType,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);

    static bool            Mix161SetEqual(GLoopFragmentComposer &pComposer,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161AddEqual(GLoopFragmentComposer &pComposer,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161XorEqual(GLoopFragmentComposer &pComposer,
                                          GSymbol pSBox,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);

    // Legacy compatibility overloads using `kSBoxA`.
    static bool            Mix161SetEqual(GSymbol pSymbol,
                                          Mix161Type pMixType,
                                          const GExpr &pExpr,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161AddEqual(GSymbol pSymbol,
                                          Mix161Type pMixType,
                                          const GExpr &pExpr,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161XorEqual(GSymbol pSymbol,
                                          Mix161Type pMixType,
                                          const GExpr &pExpr,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);

    static bool            Mix161SetEqual(GSymbol pSymbol,
                                          const GExpr &pExpr,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161AddEqual(GSymbol pSymbol,
                                          const GExpr &pExpr,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161XorEqual(GSymbol pSymbol,
                                          const GExpr &pExpr,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);

    static bool            Mix161SetEqual(GLoopFragmentComposer &pComposer,
                                          Mix161Type pMixType,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161AddEqual(GLoopFragmentComposer &pComposer,
                                          Mix161Type pMixType,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161XorEqual(GLoopFragmentComposer &pComposer,
                                          Mix161Type pMixType,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);

    static bool            Mix161SetEqual(GLoopFragmentComposer &pComposer,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161AddEqual(GLoopFragmentComposer &pComposer,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
    static bool            Mix161XorEqual(GLoopFragmentComposer &pComposer,
                                          std::vector<GStatement> *pStatementList,
                                          std::string *pError);
};

#endif /* GTwistMix16_hpp */
