//
//  GSelect.cpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 4/30/26.
//

#include "GSelect.hpp"
#include "Random.hpp"

#include <cstdio>
#include <utility>
#include <vector>

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

void AppendSwitchSelectStatements(const std::string &pSelectVariableName,
                                  const std::vector<const std::vector<GStatement> *> &pBuckets,
                                  std::vector<GStatement> *pOutput) {
    if ((pOutput == NULL) || pBuckets.empty()) {
        return;
    }

    if (pBuckets.size() == 1U) {
        AppendStatements(pOutput, pBuckets[0]);
        return;
    }

    pOutput->push_back(GStatement::RawLine("switch (" + pSelectVariableName + " % " + std::to_string(static_cast<unsigned int>(pBuckets.size())) + "U) {"));
    for (std::size_t aCaseIndex = 0U; aCaseIndex < pBuckets.size(); ++aCaseIndex) {
        pOutput->push_back(RawLineWithPrefix("case " + std::to_string(static_cast<unsigned int>(aCaseIndex)) + "U: {", "\t"));
        AppendStatementsWithPrefix(pOutput, pBuckets[aCaseIndex], "\t\t");
        pOutput->push_back(RawLineWithPrefix("break;", "\t\t"));
        pOutput->push_back(RawLineWithPrefix("}", "\t"));
    }
    pOutput->push_back(GStatement::RawLine("}"));
}

void CollectPopulatedSelectBuckets(const std::vector<GStatement> *pStatementsA,
                                   const std::vector<GStatement> *pStatementsB,
                                   const std::vector<GStatement> *pStatementsC,
                                   const std::vector<GStatement> *pStatementsD,
                                   std::vector<const std::vector<GStatement> *> *pBuckets) {
    if (pBuckets == NULL) {
        return;
    }
    pBuckets->clear();

    if ((pStatementsA != NULL) && !pStatementsA->empty()) {
        pBuckets->push_back(pStatementsA);
    }
    if ((pStatementsB != NULL) && !pStatementsB->empty()) {
        pBuckets->push_back(pStatementsB);
    }
    if ((pStatementsC != NULL) && !pStatementsC->empty()) {
        pBuckets->push_back(pStatementsC);
    }
    if ((pStatementsD != NULL) && !pStatementsD->empty()) {
        pBuckets->push_back(pStatementsD);
    }
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
    aResult.mMask = Random::GetByte();
    aResult.mThresholdA = Random::GetByte();
    aResult.mThresholdB = Random::GetByte();
    aResult.mThresholdC = Random::GetByte();
    return aResult;
}

GSelect GSelect::Random2() {
    GSelect aResult;
    aResult.mMask = Random::GetByte();
    aResult.mThresholdA = Random::GetByte();
    aResult.mThresholdB = 0U;
    aResult.mThresholdC = 0U;
    return aResult;
}

GSelect GSelect::Demo4(int pIndex1, int pIndex2) {
    GSelect aResult;
    aResult.mMask = static_cast<std::uint8_t>(pIndex1 & 0xFF);
    aResult.mThresholdA = static_cast<std::uint8_t>(pIndex2 & 0xFF);
    aResult.mThresholdB = static_cast<std::uint8_t>((pIndex1 + pIndex2) & 0xFF);
    aResult.mThresholdC = static_cast<std::uint8_t>((pIndex1 ^ pIndex2) & 0xFF);
    return aResult;
}

GSelect GSelect::Demo2(int pIndex1, int pIndex2) {
    GSelect aResult;
    aResult.mMask = static_cast<std::uint8_t>(pIndex1 & 0xFF);
    aResult.mThresholdA = static_cast<std::uint8_t>(pIndex2 & 0xFF);
    aResult.mThresholdB = 0U;
    aResult.mThresholdC = 0U;
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

void GSelect::AddStatementA(GStatement pStatement) {
    mStatementsAOwned.push_back(pStatement);
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

void GSelect::AddStatementB(GStatement pStatement) {
    mStatementsBOwned.push_back(pStatement);
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

void GSelect::AddStatementC(GStatement pStatement) {
    mStatementsCOwned.push_back(pStatement);
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

void GSelect::AddStatementD(GStatement pStatement) {
    mStatementsDOwned.push_back(pStatement);
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

    std::vector<const std::vector<GStatement> *> aBuckets;
    CollectPopulatedSelectBuckets(aStatementsA, aStatementsB, aStatementsC, aStatementsD, &aBuckets);
    if (aBuckets.empty()) {
        SetError(pErrorMessage, "GSelect::Bake requires at least one non-empty statement bucket.");
        return false;
    }
    if (aBuckets.size() > 4U) {
        SetError(pErrorMessage, "GSelect::Bake supports at most four populated statement buckets.");
        return false;
    }

    std::vector<GStatement> aResult;
    aResult.push_back(GStatement::Assign(GTarget::Symbol(pSelectVariable), pSelectValueExpr));
    AppendSwitchSelectStatements(pSelectVariable.mName, aBuckets, &aResult);

    *pStatements = std::move(aResult);
    return true;
}

bool GSelect::Bake(GSymbol pSelectValue,
                   std::vector<GStatement> *pStatements,
                   std::string *pErrorMessage) {
    if (!pSelectValue.IsVar()) {
        SetError(pErrorMessage, "GSelect::Bake requires a variable symbol select value.");
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

    std::vector<const std::vector<GStatement> *> aBuckets;
    CollectPopulatedSelectBuckets(aStatementsA, aStatementsB, aStatementsC, aStatementsD, &aBuckets);
    if (aBuckets.empty()) {
        SetError(pErrorMessage, "GSelect::Bake requires at least one non-empty statement bucket.");
        return false;
    }
    if (aBuckets.size() > 4U) {
        SetError(pErrorMessage, "GSelect::Bake supports at most four populated statement buckets.");
        return false;
    }

    std::vector<GStatement> aResult;
    AppendSwitchSelectStatements(pSelectValue.mName, aBuckets, &aResult);

    *pStatements = std::move(aResult);
    return true;
}
