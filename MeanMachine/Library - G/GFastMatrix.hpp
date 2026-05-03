//
//  GFastMatrix.hpp
//  MeanMachine
//

#ifndef GFastMatrix_hpp
#define GFastMatrix_hpp

#include "GSeedProgram.hpp"
#include "Random.hpp"
#include "TwistFastMatrix.hpp"

#include <algorithm>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

enum class GFastMatrixType : std::uint8_t {
    kA = 0,
    kB = 1
};

using GFastMatrixOp = TwistFastMatrixOp;

class GFastMatrix {
public:
    struct Step {
        GFastMatrixOp                      mOp = GFastMatrixOp::kInv;
        std::uint8_t                       mArg1 = 0U;
        std::uint8_t                       mArg2 = 0U;
        GSymbol                            mArg1Symbol;
        GSymbol                            mArg2Symbol;
        std::vector<GStatement>            mOperationStatements;
    };
    
    static TwistFastMatrixUnrollScheme GetRandomUnrollScheme() {
        std::vector<TwistFastMatrixUnrollScheme> aOptions;
        aOptions.push_back(TwistFastMatrixUnrollScheme::kA);
        aOptions.push_back(TwistFastMatrixUnrollScheme::kB);
        aOptions.push_back(TwistFastMatrixUnrollScheme::kC);
        aOptions.push_back(TwistFastMatrixUnrollScheme::kD);
        return aOptions[Random::Get((int)aOptions.size())];
    }
    
    
    static std::vector<TwistFastMatrixOp> GetRandomOpsFromList(
        const std::vector<TwistFastMatrixOp>& pSourceList,
        int pCount,
        std::vector<TwistFastMatrixOp>& pIgnoreList
                                                               ) {
        std::vector<TwistFastMatrixOp> aResult;
        
        for (int aPickIndex = 0; aPickIndex < pCount; aPickIndex++) {
            std::vector<TwistFastMatrixOp> aAvailableList;
            
            for (TwistFastMatrixOp aOp : pSourceList) {
                if (std::find(pIgnoreList.begin(), pIgnoreList.end(), aOp) == pIgnoreList.end()) {
                    aAvailableList.push_back(aOp);
                }
            }
            
            if (aAvailableList.empty()) {
                break;
            }
            
            TwistFastMatrixOp aOp = GetRandomOpFromList(aAvailableList, aAvailableList[0]);
            
            aResult.push_back(aOp);
            
            std::vector<TwistFastMatrixOp> aChosenOps = aResult;
            
            for (TwistFastMatrixOp aIgnoredOp : pIgnoreList) {
                aChosenOps.push_back(aIgnoredOp);
            }
            
            std::vector<TwistFastMatrixOp> aConflicts = TwistFastMatrix::GetConflictingOps(aChosenOps);
            
            for (TwistFastMatrixOp aConflict : aConflicts) {
                pIgnoreList.push_back(aConflict);
            }
        }
        
        Random::Shuffle(&aResult);
        
        return aResult;
    }
    
    static std::vector<TwistFastMatrixOp> GetRandomOpsFast(
        int pCount,
        std::vector<TwistFastMatrixOp>& pIgnoreList
    ) {
        return GetRandomOpsFromList(
            TwistFastMatrix::GetAllTypesFast(),
            pCount,
            pIgnoreList
        );
    }

    static std::vector<TwistFastMatrixOp> GetRandomOpsMedium(
        int pCount,
        std::vector<TwistFastMatrixOp>& pIgnoreList
    ) {
        return GetRandomOpsFromList(
            TwistFastMatrix::GetAllTypesMedium(),
            pCount,
            pIgnoreList
        );
    }

    static std::vector<TwistFastMatrixOp> GetRandomOpsSlow(
        int pCount,
        std::vector<TwistFastMatrixOp>& pIgnoreList
    ) {
        return GetRandomOpsFromList(
            TwistFastMatrix::GetAllTypesSlow(),
            pCount,
            pIgnoreList
        );
    }
    
    
    
    explicit GFastMatrix(GFastMatrixType pType = GFastMatrixType::kA)
    : mType(pType) {
    }

    void SetType(GFastMatrixType pType) {
        mType = pType;
    }

    GFastMatrixType GetType() const {
        return mType;
    }

    void Clear() {
        mSteps.clear();
    }
    
    GFastMatrix &Perform(GFastMatrixOp pOp) {
        return Perform(pOp, 0U, 0U);
    }

    GFastMatrix &Perform(GFastMatrixOp pOp,
                         GSymbol pOperationByteA,
                         GSymbol pOperationSourceA,
                         GSymbol pOperationSourceIndexA,
                         int pOperationSourceOffsetA) {
        Step aStep;
        aStep.mOp = pOp;
        aStep.mArg1 = 0U;
        aStep.mArg2 = 0U;
        aStep.mArg1Symbol = pOperationByteA;
        aStep.mArg2Symbol = GSymbol();
        aStep.mOperationStatements.push_back(BuildOperationReadStatement(pOperationByteA,
                                                                         pOperationSourceA,
                                                                         pOperationSourceIndexA,
                                                                         pOperationSourceOffsetA));
        mSteps.push_back(aStep);
        return *this;
    }

    GFastMatrix &Perform(GFastMatrixOp pOp,
                         GSymbol pOperationByteA,
                         GSymbol pOperationSourceA,
                         GSymbol pOperationSourceIndexA,
                         int pOperationSourceOffsetA,
                         GSymbol pOperationByteB,
                         GSymbol pOperationSourceB,
                         GSymbol pOperationSourceIndexB,
                         int pOperationSourceOffsetB) {
        Step aStep;
        aStep.mOp = pOp;
        aStep.mArg1 = 0U;
        aStep.mArg2 = 0U;
        aStep.mArg1Symbol = pOperationByteA;
        aStep.mArg2Symbol = pOperationByteB;
        aStep.mOperationStatements.push_back(BuildOperationReadStatement(pOperationByteA,
                                                                         pOperationSourceA,
                                                                         pOperationSourceIndexA,
                                                                         pOperationSourceOffsetA));
        aStep.mOperationStatements.push_back(BuildOperationReadStatement(pOperationByteB,
                                                                         pOperationSourceB,
                                                                         pOperationSourceIndexB,
                                                                         pOperationSourceOffsetB));
        mSteps.push_back(aStep);
        return *this;
    }

    GFastMatrix &Perform(GFastMatrixOp pOp,
                         std::uint8_t pArg1,
                         std::uint8_t pArg2) {
        Step aStep;
        aStep.mOp = pOp;
        aStep.mArg1 = pArg1;
        aStep.mArg2 = pArg2;
        mSteps.push_back(aStep);
        return *this;
    }

    bool BakeLoad(GSymbol pSource,
                  GSymbol pLoopIndex,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GFastMatrix::BakeLoad output statement list was null.");
            return false;
        }
        if (!pSource.IsBuf()) {
            SetError(pErrorMessage, "GFastMatrix::BakeLoad source must be a buffer symbol.");
            return false;
        }
        if (!pLoopIndex.IsVar()) {
            SetError(pErrorMessage, "GFastMatrix::BakeLoad loop index must be a variable symbol.");
            return false;
        }

        const std::string aLine = MatrixObjectName(mType) + ".LoadAndReset(" +
            BufAliasName(pSource.mSlot) + " + " + pLoopIndex.mName + ");";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }

    bool BakePerform(std::vector<GStatement> *pStatements,
                     std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GFastMatrix::BakePerform output statement list was null.");
            return false;
        }

        const std::string aMatrixName = MatrixObjectName(mType);
        for (const Step &aStep : mSteps) {
            if (aStep.mOp == GFastMatrixOp::kInv) {
                SetError(pErrorMessage, "GFastMatrix::BakePerform encountered an invalid matrix op.");
                return false;
            }
            for (const GStatement &aOperationStatement : aStep.mOperationStatements) {
                pStatements->push_back(aOperationStatement);
            }

            const std::string aArg1Text = aStep.mArg1Symbol.IsVar()
                ? aStep.mArg1Symbol.mName
                : (std::to_string(static_cast<unsigned int>(aStep.mArg1)) + "U");
            const std::string aArg2Text = aStep.mArg2Symbol.IsVar()
                ? aStep.mArg2Symbol.mName
                : (std::to_string(static_cast<unsigned int>(aStep.mArg2)) + "U");

            const std::string aMethodName = TwistFastMatrix::GetFunctionName(aStep.mOp);
            if (aMethodName.empty()) {
                SetError(pErrorMessage, "GFastMatrix::BakePerform encountered a matrix op without a function name.");
                return false;
            }

            const std::string aLine = aMatrixName + "." + aMethodName + "(" +
                aArg1Text + ", " +
                aArg2Text + ");";
            pStatements->push_back(GStatement::RawLine(aLine));
        }
        return true;
    }

    bool BakeUnrollRandom(GSymbol pDest,
                          GSymbol pLoopIndex,
                          std::uint8_t pUnrollByte,
                          std::vector<GStatement> *pStatements,
                          std::string *pErrorMessage) const {
        const TwistFastMatrixUnrollScheme aRandomScheme =
            static_cast<TwistFastMatrixUnrollScheme>(Random::Get(4));
        return BakeUnrollRandom(pDest, pLoopIndex, aRandomScheme, pUnrollByte, pStatements, pErrorMessage);
    }

    bool BakeUnrollRandom(GSymbol pDest,
                          GSymbol pLoopIndex,
                          TwistFastMatrixUnrollScheme pUnrollScheme,
                          std::uint8_t pUnrollByte,
                          std::vector<GStatement> *pStatements,
                          std::string *pErrorMessage) const {
        return BakeUnroll(pDest, pLoopIndex, pUnrollScheme, pUnrollByte, pStatements, pErrorMessage);
    }

    bool BakeUnroll(GSymbol pDest,
                    GSymbol pLoopIndex,
                    TwistFastMatrixUnrollScheme pUnrollScheme,
                    std::uint8_t pUnrollByte,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GFastMatrix::BakeUnroll output statement list was null.");
            return false;
        }
        if (!pDest.IsBuf()) {
            SetError(pErrorMessage, "GFastMatrix::BakeUnroll destination must be a buffer symbol.");
            return false;
        }
        if (!pLoopIndex.IsVar()) {
            SetError(pErrorMessage, "GFastMatrix::BakeUnroll loop index must be a variable symbol.");
            return false;
        }

        const std::string aLine = MatrixObjectName(mType) + ".Store(" +
            BufAliasName(pDest.mSlot) + " + " + pLoopIndex.mName + ", " +
            TwistFastMatrix::UnrollSchemeToken(pUnrollScheme) + ", " +
            std::to_string(static_cast<unsigned int>(pUnrollByte)) + "U);";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }

    bool BakeUnroll(GSymbol pDest,
                    GSymbol pLoopIndex,
                    TwistFastMatrixUnrollScheme pUnrollScheme,
                    GSymbol pUnrollByte,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GFastMatrix::BakeUnroll output statement list was null.");
            return false;
        }
        if (!pDest.IsBuf()) {
            SetError(pErrorMessage, "GFastMatrix::BakeUnroll destination must be a buffer symbol.");
            return false;
        }
        if (!pLoopIndex.IsVar()) {
            SetError(pErrorMessage, "GFastMatrix::BakeUnroll loop index must be a variable symbol.");
            return false;
        }
        if (!pUnrollByte.IsVar()) {
            SetError(pErrorMessage, "GFastMatrix::BakeUnroll unroll byte symbol must be a variable symbol.");
            return false;
        }

        const std::string aLine = MatrixObjectName(mType) + ".Store(" +
            BufAliasName(pDest.mSlot) + " + " + pLoopIndex.mName + ", " +
            TwistFastMatrix::UnrollSchemeToken(pUnrollScheme) + ", " +
            pUnrollByte.mName + ");";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }

private:
    static GStatement BuildOperationReadStatement(GSymbol pOperationByte,
                                                  GSymbol pOperationSource,
                                                  GSymbol pOperationSourceIndex,
                                                  int pOperationSourceOffset) {
        return GStatement::Assign(
            GTarget::Symbol(pOperationByte),
            GExpr::Read(
                pOperationSource,
                GExpr::Add(GExpr::Symbol(pOperationSourceIndex),
                           GExpr::Const32(pOperationSourceOffset))));
    }

    static TwistFastMatrixOp GetRandomOpFromList(const std::vector<TwistFastMatrixOp> &pList,
                                                 TwistFastMatrixOp pFallback) {
        if (pList.empty()) {
            return pFallback;
        }
        return pList[static_cast<std::size_t>(Random::Get(static_cast<int>(pList.size())))];
    }

    static std::vector<TwistFastMatrixOp> GetRandomOpsFromList(
        const std::vector<TwistFastMatrixOp> &pSource,
        int pCount,
        const std::vector<TwistFastMatrixOp> &pIgnoreList) {
        if (pCount <= 0) {
            return {};
        }

        std::unordered_set<TwistFastMatrixOp> aIgnore;
        for (const TwistFastMatrixOp aOp : pIgnoreList) {
            aIgnore.insert(aOp);
        }

        std::vector<TwistFastMatrixOp> aFiltered;
        aFiltered.reserve(pSource.size());
        for (const TwistFastMatrixOp aOp : pSource) {
            if (aIgnore.find(aOp) == aIgnore.end()) {
                aFiltered.push_back(aOp);
            }
        }

        Random::Shuffle(&aFiltered);

        const std::size_t aTakeCount = std::min<std::size_t>(
            static_cast<std::size_t>(pCount),
            aFiltered.size());
        return std::vector<TwistFastMatrixOp>(aFiltered.begin(), aFiltered.begin() + aTakeCount);
    }

    static std::string MatrixObjectName(GFastMatrixType pType) {
        return (pType == GFastMatrixType::kB) ? "mMatrixB" : "mMatrixA";
    }

    static void SetError(std::string *pErrorMessage,
                         const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }

    GFastMatrixType                      mType = GFastMatrixType::kA;
    std::vector<Step>                    mSteps;
};

#endif /* GFastMatrix_hpp */
