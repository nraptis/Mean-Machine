//
//  GSelect.cpp
//  MeanMachine
//
//  Created by Dragon on 4/30/26.
//

#include "GSelect.hpp"
#include "TwistSelect.hpp"
#include "Random.hpp"

#include <utility>

namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != NULL) {
        *pErrorMessage = pMessage;
    }
}

void AppendStatements(std::vector<GStatement> *pOutput,
                      const std::vector<GStatement> *pStatements) {
    if ((pOutput == NULL) || (pStatements == NULL)) {
        return;
    }
    pOutput->insert(pOutput->end(), pStatements->begin(), pStatements->end());
}

void AppendStatementsWithPrefix(std::vector<GStatement> *pOutput,
                                const std::vector<GStatement> *pStatements,
                                const std::string &pPrefix) {
    if ((pOutput == NULL) || (pStatements == NULL)) {
        return;
    }
    for (const GStatement &aStatement : *pStatements) {
        GStatement aCopy = aStatement;
        aCopy.mOutputPrefix = pPrefix;
        pOutput->push_back(std::move(aCopy));
    }
}

GStatement RawLineWithPrefix(const std::string &pLine,
                             const std::string &pPrefix) {
    GStatement aStatement = GStatement::RawLine(pLine);
    aStatement.mOutputPrefix = pPrefix;
    return aStatement;
}

} // namespace

GSelect::GSelect() {
    mMask = 0;
    mThresholdA = 0;
    mThresholdB = 0;
    mThresholdC = 0;
}

GSelect GSelect::Random4() {
    GSelect aResult;
    
    std::vector<TwistSelectResult4> aList = TwistSelect::GetAll4();
    
    if (aList.size() <= 0) { return aResult; }
    
    
    TwistSelectResult4 aChoice = aList[Random::Get((int)aList.size())];
    
    aResult.mMask = aChoice.mMask;
    aResult.mThresholdA = Random::Get(aChoice.mRangeA.mLo, aChoice.mRangeA.mHi);
    aResult.mThresholdB = Random::Get(aChoice.mRangeB.mLo, aChoice.mRangeB.mHi);
    aResult.mThresholdC = Random::Get(aChoice.mRangeC.mLo, aChoice.mRangeC.mHi);
    return aResult;
}

GSelect GSelect::Random2() {
    GSelect aResult;
    
    std::vector<TwistSelectResult2> aList = TwistSelect::GetAll2();
    
    if (aList.size() <= 0) { return aResult; }
    
    
    TwistSelectResult2 aChoice = aList[Random::Get((int)aList.size())];
    
    aResult.mMask = aChoice.mMask;
    aResult.mThresholdA = Random::Get(aChoice.mRangeA.mLo, aChoice.mRangeA.mHi);
    return aResult;
}

GSelect GSelect::Demo4(int pIndex1, int pIndex2) {
    GSelect aResult;
    
    std::vector<TwistSelectResult4> aList = TwistSelect::GetAll4();
    
    if (aList.size() <= 0) { return aResult; }
    
    pIndex1 = (pIndex1 % ((int)aList.size()));
    
    if (pIndex1 < 0) {
        pIndex1 += aList.size();
    }
    
    TwistSelectResult4 aChoice = aList[pIndex1];
    
    aResult.mMask = aChoice.mMask;
    
    aResult.mThresholdA = aChoice.mRangeA.mLo;
    aResult.mThresholdB = aChoice.mRangeB.mLo;
    aResult.mThresholdC = aChoice.mRangeC.mLo;
    
    int aRangeA = (aChoice.mRangeA.mHi - aChoice.mRangeA.mLo + 1);
    if (aRangeA > 1) {
        int aOffset = (pIndex2 % aRangeA);
        aResult.mThresholdA += aOffset;
    }
    
    int aRangeB = (aChoice.mRangeB.mHi - aChoice.mRangeB.mLo + 1);
    if (aRangeB > 1) {
        int aOffset = (pIndex2 % aRangeB);
        aResult.mThresholdB += aOffset;
    }
    
    int aRangeC = (aChoice.mRangeC.mHi - aChoice.mRangeC.mLo + 1);
    if (aRangeC > 1) {
        int aOffset = (pIndex2 % aRangeC);
        aResult.mThresholdC += aOffset;
    }
    
    return aResult;
}

GSelect GSelect::Demo2(int pIndex1, int pIndex2) {
    
    GSelect aResult;
    
    std::vector<TwistSelectResult2> aList = TwistSelect::GetAll2();
    
    if (aList.size() <= 0) { return aResult; }
    
    pIndex1 = (pIndex1 % ((int)aList.size()));
    
    if (pIndex1 < 0) {
        pIndex1 += aList.size();
    }
    
    TwistSelectResult2 aChoice = aList[pIndex1];
    
    aResult.mMask = aChoice.mMask;
    
    aResult.mThresholdA = aChoice.mRangeA.mLo;
    
    int aRangeA = (aChoice.mRangeA.mHi - aChoice.mRangeA.mLo + 1);
    if (aRangeA > 1) {
        int aOffset = (pIndex2 % aRangeA);
        aResult.mThresholdA += aOffset;
    }
    
    return aResult;
}

void GSelect::AddStatementsA(std::vector<GStatement> *pStatements) {
    if (pStatements != NULL) {
        AppendStatements(&mStatementsAOwned, pStatements);
        pStatements->clear();
    }
}

void GSelect::AddStatementA(GStatement *pStatement) {
    if (pStatement == NULL) {
        return;
    }
    mStatementsAOwned.push_back(*pStatement);
    pStatement->Invalidate();
}

void GSelect::AddStatementsB(std::vector<GStatement> *pStatements) {
    if (pStatements != NULL) {
        AppendStatements(&mStatementsBOwned, pStatements);
        pStatements->clear();
    }
}

void GSelect::AddStatementB(GStatement *pStatement) {
    if (pStatement == NULL) {
        return;
    }
    mStatementsBOwned.push_back(*pStatement);
    pStatement->Invalidate();
}

void GSelect::AddStatementsC(std::vector<GStatement> *pStatements) {
    if (pStatements != NULL) {
        AppendStatements(&mStatementsCOwned, pStatements);
        pStatements->clear();
    }
}

void GSelect::AddStatementC(GStatement *pStatement) {
    if (pStatement == NULL) {
        return;
    }
    mStatementsCOwned.push_back(*pStatement);
    pStatement->Invalidate();
}

void GSelect::AddStatementsD(std::vector<GStatement> *pStatements) {
    if (pStatements != NULL) {
        AppendStatements(&mStatementsDOwned, pStatements);
        pStatements->clear();
    }
}

void GSelect::AddStatementD(GStatement *pStatement) {
    if (pStatement == NULL) {
        return;
    }
    mStatementsDOwned.push_back(*pStatement);
    pStatement->Invalidate();
}

bool GSelect::Bake(GSymbol pSelectVariable,
                   GExpr pSelectValueExpr,
                   std::vector<GStatement> *pStatements,
                   std::string *pErrorMessage) {
    if (!pSelectVariable.IsVar()) {
        SetError(pErrorMessage, "GSelect::Bake requires a variable symbol target.");
        return false;
    }
    if (pStatements == NULL) {
        SetError(pErrorMessage, "GSelect::Bake had a null output statement vector.");
        return false;
    }

    const std::vector<GStatement> *aStatementsA = &mStatementsAOwned;
    const std::vector<GStatement> *aStatementsB = &mStatementsBOwned;
    const std::vector<GStatement> *aStatementsC = &mStatementsCOwned;
    const std::vector<GStatement> *aStatementsD = &mStatementsDOwned;

    const bool aUseFourWay = !aStatementsC->empty() || !aStatementsD->empty();

    std::vector<GStatement> aResult;
    aResult.push_back(GStatement::Assign(GTarget::Symbol(pSelectVariable), pSelectValueExpr));

    const std::string aSelectName = pSelectVariable.mName;
    if (!aUseFourWay) {
        aResult.push_back(GStatement::RawLine("if (" + aSelectName + " > " + std::to_string(static_cast<int>(mThresholdA)) + ") {"));
        AppendStatementsWithPrefix(&aResult, aStatementsA, "\t");
        aResult.push_back(GStatement::RawLine("} else {"));
        AppendStatementsWithPrefix(&aResult, aStatementsB, "\t");
        aResult.push_back(GStatement::RawLine("}"));
    } else {
        aResult.push_back(GStatement::RawLine("if (" + aSelectName + " > " + std::to_string(static_cast<int>(mThresholdC)) + ") {"));
        AppendStatementsWithPrefix(&aResult, aStatementsD, "\t");
        aResult.push_back(GStatement::RawLine("} else {"));
        aResult.push_back(RawLineWithPrefix("if (" + aSelectName + " > " + std::to_string(static_cast<int>(mThresholdB)) + ") {", "\t"));
        AppendStatementsWithPrefix(&aResult, aStatementsC, "\t");
        aResult.push_back(RawLineWithPrefix("} else {", "\t"));
        aResult.push_back(RawLineWithPrefix("if (" + aSelectName + " > " + std::to_string(static_cast<int>(mThresholdA)) + ") {", "\t"));
        AppendStatementsWithPrefix(&aResult, aStatementsB, "\t");
        aResult.push_back(RawLineWithPrefix("} else {", "\t"));
        AppendStatementsWithPrefix(&aResult, aStatementsA, "\t");
        aResult.push_back(RawLineWithPrefix("}", "\t"));
        aResult.push_back(RawLineWithPrefix("}", "\t"));
        aResult.push_back(GStatement::RawLine("}"));
    }

    *pStatements = std::move(aResult);
    return true;
}

bool GSelect::Bake(GSymbol pSelectVariable,
                   GSymbol pSelectValue,
                   std::vector<GStatement> *pStatements,
                   std::string *pErrorMessage) {
    return Bake(pSelectVariable, GExpr::Symbol(pSelectValue), pStatements, pErrorMessage);
}
