//
//  GFastMatrix.cpp
//  MeanMachine
//

#include "GFastMatrix.hpp"
#include "Random.hpp"

#include <algorithm>
#include <unordered_set>


static void AddUniqueOp(std::vector<TwistFastMatrixOp> *pList,
                        TwistFastMatrixOp pOp) {
    if (pList == nullptr) {
        return;
    }

    if (std::find(pList->begin(), pList->end(), pOp) == pList->end()) {
        pList->push_back(pOp);
    }
}

static void AddOneAnchorOp(const std::vector<TwistFastMatrixOp> &pOps,
                           std::vector<TwistFastMatrixOp> *pIgnoreList) {
    if ((pIgnoreList == nullptr) || pOps.empty()) {
        return;
    }

    const TwistFastMatrixOp aAnchor =
        pOps[Random::Get(static_cast<int>(pOps.size()))];

    AddUniqueOp(pIgnoreList, aAnchor);
}

static void AddAllOps(const std::vector<TwistFastMatrixOp> &pOps,
                      std::vector<TwistFastMatrixOp> *pIgnoreList) {
    if (pIgnoreList == nullptr) {
        return;
    }

    for (TwistFastMatrixOp aOp : pOps) {
        AddUniqueOp(pIgnoreList, aOp);
    }
}

static std::vector<TwistFastMatrixOp> PickOpsWithRetry(
    int pCount,
    std::vector<TwistFastMatrixOp> *pPersistentIgnore,
    const std::function<std::vector<TwistFastMatrixOp>(int, std::vector<TwistFastMatrixOp>&)> &pPicker,
    bool pPromoteAll
) {
    std::vector<TwistFastMatrixOp> aResult;

    int aAttempts = 0;
    while ((static_cast<int>(aResult.size()) < pCount) && (aAttempts < 256)) {
        aAttempts++;

        std::vector<TwistFastMatrixOp> aLocalIgnore;
        if (pPersistentIgnore != nullptr) {
            aLocalIgnore = *pPersistentIgnore;
        }

        for (TwistFastMatrixOp aAlreadyPicked : aResult) {
            if (std::find(aLocalIgnore.begin(), aLocalIgnore.end(), aAlreadyPicked) == aLocalIgnore.end()) {
                aLocalIgnore.push_back(aAlreadyPicked);
            }
        }

        const int aNeed = pCount - static_cast<int>(aResult.size());
        std::vector<TwistFastMatrixOp> aPicked = pPicker(aNeed, aLocalIgnore);

        for (TwistFastMatrixOp aOp : aPicked) {
            if (std::find(aResult.begin(), aResult.end(), aOp) == aResult.end()) {
                aResult.push_back(aOp);
            }
        }
    }

    if (static_cast<int>(aResult.size()) != pCount) {
        std::printf("fatal: PickOpsWithRetry failed count=%d got=%zu\n",
                    pCount,
                    aResult.size());
        std::exit(0);
    }

    if (pPersistentIgnore != nullptr) {
        if (pPromoteAll) {
            for (TwistFastMatrixOp aOp : aResult) {
                if (std::find(pPersistentIgnore->begin(), pPersistentIgnore->end(), aOp) == pPersistentIgnore->end()) {
                    pPersistentIgnore->push_back(aOp);
                }
            }
        } else if (!aResult.empty()) {
            const TwistFastMatrixOp aAnchor =
                aResult[Random::Get(static_cast<int>(aResult.size()))];

            if (std::find(pPersistentIgnore->begin(), pPersistentIgnore->end(), aAnchor) == pPersistentIgnore->end()) {
                pPersistentIgnore->push_back(aAnchor);
            }
        }
    }

    return aResult;
}

static void BuildDualDiffuseChannel(GFastMatrixDualDiffuseOperationChannel *pChannel,
                                    std::vector<TwistFastMatrixOp> *pSlowIgnore,
                                    std::vector<TwistFastMatrixOp> *pMediumIgnore,
                                    std::vector<TwistFastMatrixOp> *pFastIgnore) {
    if (pChannel == nullptr) {
        return;
    }

    pChannel->mSlowList =
        PickOpsWithRetry(2, pSlowIgnore,
                         [](int pCount, std::vector<TwistFastMatrixOp> &pIgnore) {
                             return GFastMatrix::GetRandomOpsSlow(pCount, pIgnore);
                         },
                         false);

    pChannel->mMediumList =
        PickOpsWithRetry(4, pMediumIgnore,
                         [](int pCount, std::vector<TwistFastMatrixOp> &pIgnore) {
                             return GFastMatrix::GetRandomOpsMedium(pCount, pIgnore);
                         },
                         true);

    pChannel->mFastList =
        PickOpsWithRetry(2, pFastIgnore,
                         [](int pCount, std::vector<TwistFastMatrixOp> &pIgnore) {
                             return GFastMatrix::GetRandomOpsFast(pCount, pIgnore);
                         },
                         false);

    pChannel->mUnrollSchemeA = GFastMatrix::GetRandomUnrollScheme();

    do {
        pChannel->mUnrollSchemeB = GFastMatrix::GetRandomUnrollScheme();
    } while (pChannel->mUnrollSchemeB == pChannel->mUnrollSchemeA);
}

GFastMatrix::GFastMatrix(GFastMatrixType pType)
: mType(pType) {
}

void GFastMatrix::SetType(GFastMatrixType pType) {
    mType = pType;
}

GFastMatrixType GFastMatrix::GetType() const {
    return mType;
}

void GFastMatrix::Clear() {
    mSteps.clear();
}

TwistFastMatrixUnrollScheme GFastMatrix::GetRandomUnrollScheme() {
    std::vector<TwistFastMatrixUnrollScheme> aOptions;
    aOptions.push_back(TwistFastMatrixUnrollScheme::kA);
    aOptions.push_back(TwistFastMatrixUnrollScheme::kB);
    aOptions.push_back(TwistFastMatrixUnrollScheme::kC);
    aOptions.push_back(TwistFastMatrixUnrollScheme::kD);
    return aOptions[Random::Get(static_cast<int>(aOptions.size()))];
}

std::vector<TwistFastMatrixOp> GFastMatrix::GetRandomOpsFromList(
    const std::vector<TwistFastMatrixOp> &pSourceList,
    int pCount,
    std::vector<TwistFastMatrixOp> &pIgnoreList
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

std::vector<TwistFastMatrixOp> GFastMatrix::GetRandomOpsFast(
    int pCount,
    std::vector<TwistFastMatrixOp> &pIgnoreList
) {
    return GetRandomOpsFromList(TwistFastMatrix::GetAllTypesFast(), pCount, pIgnoreList);
}

std::vector<TwistFastMatrixOp> GFastMatrix::GetRandomOpsMedium(
    int pCount,
    std::vector<TwistFastMatrixOp> &pIgnoreList
) {
    return GetRandomOpsFromList(TwistFastMatrix::GetAllTypesMedium(), pCount, pIgnoreList);
}

std::vector<TwistFastMatrixOp> GFastMatrix::GetRandomOpsSlow(
    int pCount,
    std::vector<TwistFastMatrixOp> &pIgnoreList
) {
    return GetRandomOpsFromList(TwistFastMatrix::GetAllTypesSlow(), pCount, pIgnoreList);
}

GFastMatrix &GFastMatrix::Perform(GFastMatrixOp pOp) {
    return Perform(pOp, 0U, 0U);
}

GFastMatrix &GFastMatrix::Perform(GFastMatrixOp pOp,
                                  GSymbol pArg1Symbol) {
    Step aStep;
    aStep.mOp = pOp;
    aStep.mArg1 = 0U;
    aStep.mArg2 = 0U;
    aStep.mArg1Symbol = pArg1Symbol;
    aStep.mArg2Symbol = GSymbol();
    mSteps.push_back(aStep);
    return *this;
}

GFastMatrix &GFastMatrix::Perform(GFastMatrixOp pOp,
                                  GSymbol pArg1Symbol,
                                  GSymbol pArg2Symbol) {
    Step aStep;
    aStep.mOp = pOp;
    aStep.mArg1 = 0U;
    aStep.mArg2 = 0U;
    aStep.mArg1Symbol = pArg1Symbol;
    aStep.mArg2Symbol = pArg2Symbol;
    mSteps.push_back(aStep);
    return *this;
}

GFastMatrix &GFastMatrix::Perform(GFastMatrixOp pOp,
                                  GSymbol pOperationByteA,
                                  GSymbol pOperationSourceA,
                                  GSymbol pOperationSourceIndexA,
                                  std::uint32_t pOperationSourceOffsetA) {
    Step aStep;
    aStep.mOp = pOp;
    aStep.mArg1 = 0U;
    aStep.mArg2 = 0U;
    aStep.mArg1Symbol = pOperationByteA;
    aStep.mArg2Symbol = GSymbol();

    aStep.mHasArg1Read = true;
    aStep.mArg1Read.mOperationByte = pOperationByteA;
    aStep.mArg1Read.mOperationSource = pOperationSourceA;
    aStep.mArg1Read.mOperationSourceIndex = pOperationSourceIndexA;
    aStep.mArg1Read.mOperationSourceOffset = pOperationSourceOffsetA;

    mSteps.push_back(aStep);
    return *this;
}

GFastMatrix &GFastMatrix::Perform(GFastMatrixOp pOp,
                                  GSymbol pOperationByteA,
                                  GSymbol pOperationSourceA,
                                  GSymbol pOperationSourceIndexA,
                                  std::uint32_t pOperationSourceOffsetA,
                                  GSymbol pOperationByteB,
                                  GSymbol pOperationSourceB,
                                  GSymbol pOperationSourceIndexB,
                                  std::uint32_t pOperationSourceOffsetB) {
    Step aStep;
    aStep.mOp = pOp;
    aStep.mArg1 = 0U;
    aStep.mArg2 = 0U;
    aStep.mArg1Symbol = pOperationByteA;
    aStep.mArg2Symbol = pOperationByteB;

    aStep.mHasArg1Read = true;
    aStep.mArg1Read.mOperationByte = pOperationByteA;
    aStep.mArg1Read.mOperationSource = pOperationSourceA;
    aStep.mArg1Read.mOperationSourceIndex = pOperationSourceIndexA;
    aStep.mArg1Read.mOperationSourceOffset = pOperationSourceOffsetA;

    aStep.mHasArg2Read = true;
    aStep.mArg2Read.mOperationByte = pOperationByteB;
    aStep.mArg2Read.mOperationSource = pOperationSourceB;
    aStep.mArg2Read.mOperationSourceIndex = pOperationSourceIndexB;
    aStep.mArg2Read.mOperationSourceOffset = pOperationSourceOffsetB;

    mSteps.push_back(aStep);
    return *this;
}

GFastMatrix &GFastMatrix::Perform(GFastMatrixOp pOp,
                                  std::uint8_t pArg1,
                                  std::uint8_t pArg2) {
    Step aStep;
    aStep.mOp = pOp;
    aStep.mArg1 = pArg1;
    aStep.mArg2 = pArg2;
    mSteps.push_back(aStep);
    return *this;
}

bool GFastMatrix::BakeLoad(GSymbol pSource,
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

bool GFastMatrix::BakePerform(std::vector<GStatement> *pStatements,
                              std::string *pErrorMessage) const {
    return BakePerform(pStatements,
                       GSymbol(),
                       GSymbol(),
                       GSymbol(),
                       GSymbol(),
                       pErrorMessage);
}

bool GFastMatrix::BakePerform(std::vector<GStatement> *pStatements,
                              GSymbol pDomainWordArgA,
                              GSymbol pDomainWordArgB,
                              GSymbol pDomainWordArgC,
                              GSymbol pDomainWordArgD,
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

        const bool aUsesArg1 = TwistFastMatrix::OpUsesArg1(aStep.mOp);
        const bool aUsesArg2 = TwistFastMatrix::OpUsesArg2(aStep.mOp);

        if (aUsesArg1 && aStep.mHasArg1Read) {
            pStatements->push_back(
                BuildOperationReadStatement(
                    aStep.mArg1Read,
                    DomainWordForOperationOffset(aStep.mArg1Read.mOperationSourceOffset,
                                                 pDomainWordArgA,
                                                 pDomainWordArgB,
                                                 pDomainWordArgC,
                                                 pDomainWordArgD)));
        }

        if (aUsesArg2 && aStep.mHasArg2Read) {
            pStatements->push_back(
                BuildOperationReadStatement(
                    aStep.mArg2Read,
                    DomainWordForOperationOffset(aStep.mArg2Read.mOperationSourceOffset,
                                                 pDomainWordArgA,
                                                 pDomainWordArgB,
                                                 pDomainWordArgC,
                                                 pDomainWordArgD)));
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

        std::string aLine = aMatrixName + "." + aMethodName + "(";
        if (aUsesArg1) {
            aLine += aArg1Text;
        }
        if (aUsesArg2) {
            if (aUsesArg1) {
                aLine += ", ";
            }
            aLine += aArg2Text;
        }
        aLine += ");";

        pStatements->push_back(GStatement::RawLine(aLine));
    }
    return true;
}

bool GFastMatrix::BakeUnroll(GSymbol pDest,
                             GSymbol pLoopIndex,
                             TwistFastMatrixUnrollScheme pUnrollScheme,
                             GSymbol pUnrollWord,
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
    if (!pUnrollWord.IsVar()) {
        SetError(pErrorMessage, "GFastMatrix::BakeUnroll unroll word symbol must be a variable symbol.");
        return false;
    }

    const std::string aLine = MatrixObjectName(mType) + ".Store(" +
        BufAliasName(pDest.mSlot) + " + " + pLoopIndex.mName + ", " +
        TwistFastMatrix::UnrollSchemeToken(pUnrollScheme) + ", " +
        pUnrollWord.mName + ");";
    pStatements->push_back(GStatement::RawLine(aLine));
    return true;
}

GStatement GFastMatrix::BuildOperationReadStatement(const ArgRead &pRead,
                                                    GSymbol pDomainWord) {
    GExpr aExpression = GExpr::Read(
        pRead.mOperationSource,
        GExpr::Add(GExpr::Symbol(pRead.mOperationSourceIndex),
                   GExpr::Const32(pRead.mOperationSourceOffset)));

    if (pDomainWord.IsVar()) {
        aExpression = GExpr::Xor(aExpression,
                                 GExpr::Symbol(pDomainWord));
    }

    return GStatement::Assign(GTarget::Symbol(pRead.mOperationByte),
                              aExpression);
}

GSymbol GFastMatrix::DomainWordForOperationOffset(std::uint32_t pOperationSourceOffset,
                                                  GSymbol pDomainWordArgA,
                                                  GSymbol pDomainWordArgB,
                                                  GSymbol pDomainWordArgC,
                                                  GSymbol pDomainWordArgD) {
    switch (pOperationSourceOffset) {
        case 1U:
            return pDomainWordArgA;
        case 2U:
            return pDomainWordArgB;
        case 3U:
            return pDomainWordArgC;
        case 4U:
            return pDomainWordArgD;
        default:
            return GSymbol();
    }
}

TwistFastMatrixOp GFastMatrix::GetRandomOpFromList(const std::vector<TwistFastMatrixOp> &pList,
                                                   TwistFastMatrixOp pFallback) {
    if (pList.empty()) {
        return pFallback;
    }
    return pList[static_cast<std::size_t>(Random::Get(static_cast<int>(pList.size())))];
}

std::vector<TwistFastMatrixOp> GFastMatrix::GetRandomOpsFromListInternal(
    const std::vector<TwistFastMatrixOp> &pSource,
    int pCount,
    const std::vector<TwistFastMatrixOp> &pIgnoreList
) {
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

std::string GFastMatrix::MatrixObjectName(GFastMatrixType pType) {
    return (pType == GFastMatrixType::kB) ? "mMatrixB" : "mMatrixA";
}

void GFastMatrix::SetError(std::string *pErrorMessage,
                           const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

void GFastMatrix::GetDualDiffuseOps(GFastMatrixDualDiffuseOperationPack *pResult) {
    if (pResult == nullptr) {
        return;
    }

    {
        std::vector<TwistFastMatrixOp> aSlowIgnore;
        std::vector<TwistFastMatrixOp> aMediumIgnore;
        std::vector<TwistFastMatrixOp> aFastIgnore;

        BuildDualDiffuseChannel(&pResult->mChannelA_1,
                                &aSlowIgnore,
                                &aMediumIgnore,
                                &aFastIgnore);

        BuildDualDiffuseChannel(&pResult->mChannelA_2,
                                &aSlowIgnore,
                                &aMediumIgnore,
                                &aFastIgnore);

        BuildDualDiffuseChannel(&pResult->mChannelA_3,
                                &aSlowIgnore,
                                &aMediumIgnore,
                                &aFastIgnore);

        BuildDualDiffuseChannel(&pResult->mChannelA_4,
                                &aSlowIgnore,
                                &aMediumIgnore,
                                &aFastIgnore);
    }

    {
        std::vector<TwistFastMatrixOp> aSlowIgnore;
        std::vector<TwistFastMatrixOp> aMediumIgnore;
        std::vector<TwistFastMatrixOp> aFastIgnore;

        BuildDualDiffuseChannel(&pResult->mChannelB_1,
                                &aSlowIgnore,
                                &aMediumIgnore,
                                &aFastIgnore);

        BuildDualDiffuseChannel(&pResult->mChannelB_2,
                                &aSlowIgnore,
                                &aMediumIgnore,
                                &aFastIgnore);

        BuildDualDiffuseChannel(&pResult->mChannelB_3,
                                &aSlowIgnore,
                                &aMediumIgnore,
                                &aFastIgnore);

        BuildDualDiffuseChannel(&pResult->mChannelB_4,
                                &aSlowIgnore,
                                &aMediumIgnore,
                                &aFastIgnore);
    }
}
