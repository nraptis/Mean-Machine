//
//  GAXPL.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/19/26.
//

#include "GAX.hpp"
#include "TwistArray.hpp"

#include <algorithm>

namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

}

static bool AppendOptionalExpr(std::vector<GExpr> *pTerms,
                               const GExpr &pExpr) {
    if (pTerms == nullptr) {
        return false;
    }

    if (pExpr.IsInvalid() == false) {
        pTerms->push_back(pExpr);
    }

    return true;
}

static int WrapHotIndex(int pHotIndex) {
    if (G_HOT_PACK_SIZE <= 0) {
        return -1;
    }

    int aIndex = pHotIndex % G_HOT_PACK_SIZE;
    if (aIndex < 0) {
        aIndex += G_HOT_PACK_SIZE;
    }

    return aIndex;
}

static bool IsSupportedDestAssignType(GAssignType pAssignType) {
    return (pAssignType == GAssignType::kSet) ||
           (pAssignType == GAssignType::kXorAssign);
}

GSymbol GAXPL::DomainWordSymbol(TwistConstants pConstant) const {
    if (mIsNonKDF) {
        return GSymbol::WorkspaceDomainWord(mDomain, pConstant);
    }

    switch (pConstant) {
        case TwistConstants::kIngress:
            return GAXPLQuick::DomainConstantIngress();
        case TwistConstants::kScatter:
            return GAXPLQuick::DomainConstantScatter();
        case TwistConstants::kCross:
            return GAXPLQuick::DomainConstantCross();
        default:
            return GSymbol();
    }
}

bool GAXPL::MakeHotAddExpr(int pHotIndex,
                           GExpr *pResult,
                           std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXPL::MakeHotAddExpr received null result");
        return false;
    }

    const int aHotIndex = WrapHotIndex(pHotIndex);
    if (aHotIndex < 0) {
        SetError(pErrorMessage, "GAXPL::MakeHotAddExpr could not wrap hot index");
        return false;
    }

    *pResult = GExpr::Const64Hex(
        mHotPack.mPair[static_cast<std::size_t>(aHotIndex)].mAdd
    );

    return !pResult->IsInvalid();
}

bool GAXPL::MakeHotMulExpr(int pHotIndex,
                           GExpr *pResult,
                           std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXPL::MakeHotMulExpr received null result");
        return false;
    }

    const int aHotIndex = WrapHotIndex(pHotIndex);
    if (aHotIndex < 0) {
        SetError(pErrorMessage, "GAXPL::MakeHotMulExpr could not wrap hot index");
        return false;
    }

    *pResult = GExpr::Const64Hex(
        mHotPack.mPair[static_cast<std::size_t>(aHotIndex)].mMul
    );

    return !pResult->IsInvalid();
}
bool GAXPL::MakeVariableTermExpr(const GAXSKUpdateTerm &pTerm,
                                 GExpr *pResult,
                                 std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXPL::MakeVariableTermExpr received null result");
        return false;
    }

    GSymbol aSymbol;
    if (!SymbolForVariable(pTerm.mVariable, &aSymbol, pErrorMessage)) {
        return false;
    }

    if (pTerm.mHasRotation) {
        *pResult = GAXPLQuick::RotateSymbol(aSymbol, pTerm.mRotation);
    } else {
        *pResult = GExpr::Symbol(aSymbol);
    }

    if (pResult->IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::MakeVariableTermExpr produced invalid expression");
        return false;
    }

    return true;
}

bool GAXPL::MakeUpdateTermExpr(const GAXSKUpdateTerm &pTerm,
                               GExpr *pResult,
                               std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXPL::MakeUpdateTermExpr received null result");
        return false;
    }

    switch (pTerm.mKind) {
        case GAXSKModelTermKind::kVariable:
            return MakeVariableTermExpr(pTerm, pResult, pErrorMessage);

        case GAXSKModelTermKind::kHotAdd:
            return MakeHotAddExpr(pTerm.mHotIndex, pResult, pErrorMessage);

        case GAXSKModelTermKind::kHotMul:
            return MakeHotMulExpr(pTerm.mHotIndex, pResult, pErrorMessage);

        default:
            SetError(pErrorMessage, "GAXPL::MakeUpdateTermExpr unsupported update term kind");
            return false;
    }
}

bool GAXPL::MakeUpdateTerms(const GAXSKUpdatePlan &pPlan,
                            std::vector<GExpr> *pTerms,
                            std::string *pErrorMessage) const {
    if (pTerms == nullptr) {
        SetError(pErrorMessage, "GAXPL::MakeUpdateTerms received null terms");
        return false;
    }

    pTerms->clear();

    for (const GAXSKUpdateTerm &aTerm : pPlan.mTerms) {
        GExpr aExpr;
        if (!MakeUpdateTermExpr(aTerm, &aExpr, pErrorMessage)) {
            return false;
        }

        if (aExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::MakeUpdateTerms produced invalid term");
            return false;
        }

        pTerms->push_back(aExpr);
    }

    return true;
}

bool GAXPL::BuildSaltExprMapForRole(GAXSKSaltRole pRole,
                                    int pSaltCount,
                                    const std::vector<GSymbol> &pSaltSymbols,
                                    int *pBehaviorIndex,
                                    std::string *pErrorMessage) {
    if (mSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::BuildSaltExprMapForRole has null skeleton");
        return false;
    }

    if (pBehaviorIndex == nullptr) {
        SetError(pErrorMessage, "GAXPL::BuildSaltExprMapForRole received null behavior index");
        return false;
    }

    if (pSaltCount < 0) {
        SetError(pErrorMessage, "GAXPL::BuildSaltExprMapForRole received negative salt count");
        return false;
    }

    if (pSaltCount == 0) {
        return true;
    }

    if (static_cast<int>(pSaltSymbols.size()) < pSaltCount) {
        SetError(pErrorMessage, "GAXPL::BuildSaltExprMapForRole did not have enough salt symbols");
        return false;
    }

    if ((*pBehaviorIndex + pSaltCount) > static_cast<int>(mSaltBehaviors.size())) {
        SetError(pErrorMessage, "GAXPL::BuildSaltExprMapForRole did not have enough salt behaviors");
        return false;
    }

    std::vector<int> aCandidateStatementIndexes;

    for (int aStatementIndex = 0;
         aStatementIndex < static_cast<int>(mSkeleton->mStatements.size());
         ++aStatementIndex) {

        const GAXSKStatement &aStatement =
            mSkeleton->mStatements[static_cast<std::size_t>(aStatementIndex)];

        bool aIsCandidate = false;

        switch (pRole) {
            case GAXSKSaltRole::kOrbiterAssign:
                aIsCandidate = (aStatement.mKind == GAXSKStatementKind::kOrbiterAssign);
                break;

            case GAXSKSaltRole::kOrbiterUpdate:
                aIsCandidate = (aStatement.mKind == GAXSKStatementKind::kOrbiterAdd ||
                                aStatement.mKind == GAXSKStatementKind::kOrbiterXor);
                break;

            case GAXSKSaltRole::kWandererUpdate:
                aIsCandidate = (aStatement.mKind == GAXSKStatementKind::kWandererAdd ||
                                aStatement.mKind == GAXSKStatementKind::kWandererXor);
                break;

            default:
                SetError(pErrorMessage, "GAXPL::BuildSaltExprMapForRole received invalid salt role");
                return false;
        }

        if (aIsCandidate) {
            aCandidateStatementIndexes.push_back(aStatementIndex);
        }
    }

    if (static_cast<int>(aCandidateStatementIndexes.size()) < pSaltCount) {
        SetError(pErrorMessage, "GAXPL::BuildSaltExprMapForRole did not have enough candidate statements");
        return false;
    }

    std::vector<int> aSaltIndexes;
    aSaltIndexes.reserve(pSaltSymbols.size());

    for (int i = 0; i < static_cast<int>(pSaltSymbols.size()); ++i) {
        if (pSaltSymbols[static_cast<std::size_t>(i)].IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildSaltExprMapForRole found invalid salt symbol");
            return false;
        }

        aSaltIndexes.push_back(i);
    }

    Random::Shuffle(&aCandidateStatementIndexes);
    Random::Shuffle(&aSaltIndexes);

    for (int i = 0; i < pSaltCount; ++i) {
        const int aStatementIndex = aCandidateStatementIndexes[static_cast<std::size_t>(i)];
        const int aSaltIndex = aSaltIndexes[static_cast<std::size_t>(i)];

        const SaltBehavior &aBehavior =
            mSaltBehaviors[static_cast<std::size_t>(*pBehaviorIndex)];

        (*pBehaviorIndex)++;

        const GSymbol &aSaltSymbol =
            pSaltSymbols[static_cast<std::size_t>(aSaltIndex)];

        GExpr aSaltExpr;

        // Replace this with your actual indexed salt-buffer expression builder.
        // Intended emitted shape:
        //   salt[(aIndex + offset) & S_SALT1]
        // or:
        //   salt[(S_SALT1 - aIndex + offset) & S_SALT1]
        aSaltExpr = GQuick::MakeReadBufferOffsetExpressionDirected(
            aSaltSymbol,
            GSymbol::Var(TwistVariable::kIndex),
            aBehavior.mReversed,
            static_cast<std::uint32_t>(aBehavior.mOffset)
        );

        if (aSaltExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildSaltExprMapForRole failed to build salt expression");
            return false;
        }

        mSaltExprMap[aStatementIndex] = aSaltExpr;
    }

    return true;
}

bool GAXPL::BuildNonceExprMapForRole(GAXSKSaltRole pRole,
                                     int pNonceCount,
                                     int *pChoiceIndex,
                                     std::string *pErrorMessage) {
    if (mSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::BuildNonceExprMapForRole has null skeleton");
        return false;
    }

    if (pChoiceIndex == nullptr) {
        SetError(pErrorMessage, "GAXPL::BuildNonceExprMapForRole received null choice index");
        return false;
    }

    if (pNonceCount < 0) {
        SetError(pErrorMessage, "GAXPL::BuildNonceExprMapForRole received negative nonce count");
        return false;
    }

    if (pNonceCount == 0) {
        return true;
    }

    pNonceCount = std::min(pNonceCount, static_cast<int>(mNonceChoices.size()) - *pChoiceIndex);
    if (pNonceCount <= 0) {
        return true;
    }

    if ((*pChoiceIndex + pNonceCount) > static_cast<int>(mNonceChoices.size())) {
        SetError(pErrorMessage, "GAXPL::BuildNonceExprMapForRole did not have enough nonce choices");
        return false;
    }

    if (mNonceBytes.empty()) {
        SetError(pErrorMessage, "GAXPL::BuildNonceExprMapForRole had no nonce symbols");
        return false;
    }

    std::vector<int> aCandidateStatementIndexes;

    for (int aStatementIndex = 0;
         aStatementIndex < static_cast<int>(mSkeleton->mStatements.size());
         ++aStatementIndex) {

        const GAXSKStatement &aStatement =
            mSkeleton->mStatements[static_cast<std::size_t>(aStatementIndex)];

        bool aIsCandidate = false;

        switch (pRole) {
            case GAXSKSaltRole::kOrbiterAssign:
                aIsCandidate = (aStatement.mKind == GAXSKStatementKind::kOrbiterAssign);
                break;

            case GAXSKSaltRole::kOrbiterUpdate:
                aIsCandidate = (aStatement.mKind == GAXSKStatementKind::kOrbiterAdd ||
                                aStatement.mKind == GAXSKStatementKind::kOrbiterXor);
                break;

            case GAXSKSaltRole::kWandererUpdate:
                aIsCandidate = (aStatement.mKind == GAXSKStatementKind::kWandererAdd ||
                                aStatement.mKind == GAXSKStatementKind::kWandererXor);
                break;

            default:
                SetError(pErrorMessage, "GAXPL::BuildNonceExprMapForRole received invalid role");
                return false;
        }

        if (aIsCandidate) {
            aCandidateStatementIndexes.push_back(aStatementIndex);
        }
    }

    Random::Shuffle(&aCandidateStatementIndexes);
    pNonceCount = std::min(pNonceCount, static_cast<int>(aCandidateStatementIndexes.size()));


    for (int i = 0; i < pNonceCount; ++i) {
        const int aStatementIndex = aCandidateStatementIndexes[static_cast<std::size_t>(i)];
        
        const int aChoiceIndex = *pChoiceIndex;

        const NonceSymbolChoice &aChoice =
            mNonceChoices[static_cast<std::size_t>(aChoiceIndex)];

        (*pChoiceIndex)++;

        if (aChoice.mSymbol.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildNonceExprMapForRole found invalid nonce choice");
            return false;
        }

        GExpr aNonceExpr = GExpr::Symbol(aChoice.mSymbol);
        

        if (aNonceExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildNonceExprMapForRole failed to build nonce expression");
            return false;
        }

        mNonceExprMap[aStatementIndex] = aNonceExpr;
    }

    return true;
}

bool GAXPL::BuildNonceExprMap(std::string *pErrorMessage) {
    mNonceExprMap.clear();

    const int kNonceCountOrbiterAssign = Random::Get(2, 4);
    const int kNonceCountOrbiterUpdate = Random::Get(2, 4);
    const int kNonceCountWandererUpdate = Random::Get(2, 4);

    int aChoiceIndex = 0;

    if (!BuildNonceExprMapForRole(GAXSKSaltRole::kOrbiterAssign,
                                  kNonceCountOrbiterAssign,
                                  &aChoiceIndex,
                                  pErrorMessage)) {
        return false;
    }

    if (!BuildNonceExprMapForRole(GAXSKSaltRole::kOrbiterUpdate,
                                  kNonceCountOrbiterUpdate,
                                  &aChoiceIndex,
                                  pErrorMessage)) {
        return false;
    }

    if (!BuildNonceExprMapForRole(GAXSKSaltRole::kWandererUpdate,
                                  kNonceCountWandererUpdate,
                                  &aChoiceIndex,
                                  pErrorMessage)) {
        return false;
    }

    return true;
}

bool GAXPL::BuildRandomNonceMixExpr(int pMinCount,
                                    int pMaxCount,
                                    GExpr *pResult,
                                    std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXPL::BuildRandomNonceMixExpr received null result");
        return false;
    }

    *pResult = GExpr();

    if (mNonceBytes.empty()) {
        SetError(pErrorMessage, "GAXPL::BuildRandomNonceMixExpr had no nonce symbols");
        return false;
    }

    if (pMinCount < 1) {
        pMinCount = 1;
    }
    if (pMaxCount < pMinCount) {
        pMaxCount = pMinCount;
    }

    std::vector<GSymbol> aNonceSymbols = mNonceBytes;
    Random::Shuffle(&aNonceSymbols);

    const int aMaximumCount = std::min(pMaxCount, static_cast<int>(aNonceSymbols.size()));
    const int aMinimumCount = std::min(pMinCount, aMaximumCount);
    const int aNonceCount = Random::Get(aMinimumCount, aMaximumCount);

    std::vector<GExpr> aTerms;
    aTerms.reserve(static_cast<std::size_t>(aNonceCount));

    for (int i = 0; i < aNonceCount; ++i) {
        const GSymbol &aNonceSymbol = aNonceSymbols[static_cast<std::size_t>(i)];
        if (aNonceSymbol.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildRandomNonceMixExpr found invalid nonce symbol");
            return false;
        }

        GExpr aNonceExpr = GExpr::Symbol(aNonceSymbol);
        if (aNonceExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildRandomNonceMixExpr failed to build nonce");
            return false;
        }

        aTerms.push_back(aNonceExpr);
    }

    *pResult = GQuick::XorChain(aTerms);
    if (pResult->IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::BuildRandomNonceMixExpr failed to build nonce chain");
        return false;
    }

    return true;
}

bool GAXPL::BuildSaltExprMap(std::string *pErrorMessage) {
    mSaltExprMap.clear();

    static constexpr int kSaltCountOrbiterAssign = 2;
    static constexpr int kSaltCountOrbiterUpdate = 4;
    static constexpr int kSaltCountWandererUpdate = 2;
    

    int aBehaviorIndex = 0;

    if (!BuildSaltExprMapForRole(GAXSKSaltRole::kOrbiterAssign,
                                 kSaltCountOrbiterAssign,
                                 mSaltsOrbiterAssign,
                                 &aBehaviorIndex,
                                 pErrorMessage)) {
        return false;
    }

    if (!BuildSaltExprMapForRole(GAXSKSaltRole::kOrbiterUpdate,
                                 kSaltCountOrbiterUpdate,
                                 mSaltsOrbiterUpdate,
                                 &aBehaviorIndex,
                                 pErrorMessage)) {
        return false;
    }

    if (!BuildSaltExprMapForRole(GAXSKSaltRole::kWandererUpdate,
                                 kSaltCountWandererUpdate,
                                 mSaltsWandererUpdate,
                                 &aBehaviorIndex,
                                 pErrorMessage)) {
        return false;
    }

    return true;
}

bool GAXPL::EmitAddAssign(GSymbol pTarget,
                          std::vector<GExpr> pTerms,
                          const GExpr &pSaltExpr,
                          const GExpr &pNonceExpr,
                          std::vector<GStatement> *pStatements,
                          std::string *pErrorMessage) const {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::EmitAddAssign received null statements");
        return false;
    }

    AppendOptionalExpr(&pTerms, pSaltExpr);
    AppendOptionalExpr(&pTerms, pNonceExpr);

    if (pTerms.empty()) {
        SetError(pErrorMessage, "GAXPL::EmitAddAssign received no terms");
        return false;
    }

    GExpr aExpr = GQuick::AddChain(pTerms);

    if (aExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::EmitAddAssign produced invalid expression");
        return false;
    }

    pStatements->push_back(
        GStatement::Assign(
            GTarget::Symbol(pTarget),
            aExpr
        )
    );

    return true;
}

bool GAXPL::EmitXorAssign(GSymbol pTarget,
                          std::vector<GExpr> pTerms,
                          const GExpr &pSaltExpr,
                          const GExpr &pNonceExpr,
                          std::vector<GStatement> *pStatements,
                          std::string *pErrorMessage) const {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::EmitXorAssign received null statements");
        return false;
    }

    AppendOptionalExpr(&pTerms, pSaltExpr);
    AppendOptionalExpr(&pTerms, pNonceExpr);

    if (pTerms.empty()) {
        SetError(pErrorMessage, "GAXPL::EmitXorAssign received no terms");
        return false;
    }

    GExpr aExpr = GQuick::XorChain(pTerms);

    if (aExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::EmitXorAssign produced invalid expression");
        return false;
    }

    pStatements->push_back(
        GStatement::Assign(
            GTarget::Symbol(pTarget),
            aExpr
        )
    );

    return true;
}

bool GAXPL::EmitMulRotate(const GAXSKUpdatePlan &pPlan,
                          GSymbol pTarget,
                          std::vector<GStatement> *pStatements,
                          std::string *pErrorMessage) const {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::EmitMulRotate received null statements");
        return false;
    }

    const int aRotation = pPlan.mHasRotation ? pPlan.mRotation : 32;

    GExpr aMulExpr;
    bool aFoundHotMul = false;

    for (const GAXSKUpdateTerm &aTerm : pPlan.mTerms) {
        if (aTerm.mKind == GAXSKModelTermKind::kHotMul) {
            if (!MakeHotMulExpr(aTerm.mHotIndex, &aMulExpr, pErrorMessage)) {
                return false;
            }

            aFoundHotMul = true;
            break;
        }
    }

    if (!aFoundHotMul) {
        SetError(pErrorMessage, "GAXPL::EmitMulRotate found no hot mul term");
        return false;
    }

    GExpr aExpr = GExpr::Mul(
        GExpr::Symbol(pTarget),
        aMulExpr
    );

    if (aExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::EmitMulRotate failed to build mul expression");
        return false;
    }

    aExpr = GQuick::RotL64(aExpr, aRotation);

    if (aExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::EmitMulRotate failed to build rotate expression");
        return false;
    }

    pStatements->push_back(
        GStatement::Assign(
            GTarget::Symbol(pTarget),
            aExpr
        )
    );

    return true;
}

bool GAXPL::EmitWandererUpdate(const GAXSKUpdatePlan &pPlan,
                               GSymbol pTarget,
                               bool pUseXorBoundary,
                               const GExpr &pSaltExpr,
                               const GExpr &pNonceExpr,
                               std::vector<GStatement> *pStatements,
                               std::string *pErrorMessage) const {
    std::vector<GExpr> aMixTerms;

    for (const GAXSKUpdateTerm &aTerm : pPlan.mTerms) {
        if (aTerm.mKind == GAXSKModelTermKind::kVariable &&
            aTerm.mVariable == pPlan.mTarget) {
            continue;
        }

        GExpr aExpr;
        if (!MakeUpdateTermExpr(aTerm, &aExpr, pErrorMessage)) {
            return false;
        }

        aMixTerms.push_back(aExpr);
    }

    AppendOptionalExpr(&aMixTerms, pNonceExpr);

    if (aMixTerms.empty()) {
        SetError(pErrorMessage, "GAXPL::EmitWandererUpdate received no mix terms");
        return false;
    }

    GExpr aMix = GQuick::AddChain(aMixTerms);

    if (aMix.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::EmitWandererUpdate failed to build mix");
        return false;
    }

    if (pSaltExpr.IsInvalid() == false) {
        // Future salt policy can choose add or xor. For now, leave prepared.
        aMix = GExpr::Add(aMix, pSaltExpr);
    }

    GExpr aExpr;
    if (pUseXorBoundary) {
        aExpr = GExpr::Xor(GExpr::Symbol(pTarget), aMix);
    } else {
        aExpr = GExpr::Add(GExpr::Symbol(pTarget), aMix);
    }

    if (aExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::EmitWandererUpdate produced invalid expression");
        return false;
    }

    pStatements->push_back(
        GStatement::Assign(
            GTarget::Symbol(pTarget),
            aExpr
        )
    );

    return true;
}

bool GAXPL::MakeSaltBehaviors(std::vector<SaltBehavior> *pResult,
                              std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "salt behavior output pointer was null.";
        }
        return false;
    }

    static constexpr int kBehaviorCount = 16;
    static constexpr int kReverseCount = 8;

    pResult->clear();
    pResult->reserve(kBehaviorCount);

    std::vector<int> aOddOffsets = {
        3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29
    };

    std::vector<int> aEvenOffsets = {
        4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28
    };

    Random::Shuffle(&aOddOffsets);
    Random::Shuffle(&aEvenOffsets);

    std::vector<int> aOffsets;
    aOffsets.reserve(kBehaviorCount);

    for (int i = 0; i < 10; i++) {
        aOffsets.push_back(aOddOffsets[i]);
    }

    for (int i = 0; i < 6; i++) {
        aOffsets.push_back(aEvenOffsets[i]);
    }

    Random::Shuffle(&aOffsets);

    std::vector<int> aReverseFlags;
    aReverseFlags.reserve(kBehaviorCount);

    for (int i = 0; i < kBehaviorCount; ++i) {
        aReverseFlags.push_back(i < kReverseCount ? 1 : 0);
    }

    Random::Shuffle(&aReverseFlags);

    for (int i = 0; i < kBehaviorCount; ++i) {
        SaltBehavior aBehavior;
        aBehavior.mReversed = (aReverseFlags[i] != 0);
        aBehavior.mOffset = aOffsets[i];
        pResult->push_back(aBehavior);
    }

    return true;
}

void GAXPL::Reset() {
    mSkeleton = nullptr;
    mLoop = nullptr;

    mSaltsOrbiterAssign.clear();
    mSaltsOrbiterUpdate.clear();
    mSaltsWandererUpdate.clear();

    mNonceBytes.clear();
    mSources.clear();
    mOrbiters.clear();
    mWanderers.clear();

    mSourceMap.clear();
    mNonceMap.clear();
    mOrbiterMap.clear();
    mWandererMap.clear();
    
    mSaltExprMap.clear();
    mNonceExprMap.clear();

    mSaltBehaviors.clear();

    mPreferredNonceSymbols.clear();
    mFallbackNonceSymbols.clear();
    
    mNonceChoices.clear();
    
    mUseFullNonce = false;
    mDestAssignType = GAssignType::kSet;
}


bool GAXPL::Configure(const GAXSKSkeleton *pSkeleton,
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
                 std::string *pErrorMessage) {
    
    Reset();
    
    if (!MakeSaltBehaviors(&mSaltBehaviors, pErrorMessage)) { return false; }
    
    if (pSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::Configure received null skeleton");
        return false;
    }

    if (pLoop == nullptr) {
        SetError(pErrorMessage, "GAXPL::Configure received null loop");
        return false;
    }
    
    mSkeleton = pSkeleton;
    mLoop = pLoop;

    if (!IsSupportedDestAssignType(pSkeleton->mAssignType)) {
        SetError(pErrorMessage, "GAXPL::Configure received unsupported destination assign type");
        return false;
    }
    
    TwistArray::Replace(&mSaltsOrbiterAssign, &(pSaltBag.mOrbiterAssign));
    TwistArray::Replace(&mSaltsOrbiterUpdate, &(pSaltBag.mOrbiterUpdate));
    TwistArray::Replace(&mSaltsWandererUpdate, &(pSaltBag.mWandererUpdate));

    const bool aHasNonceSlots = pSkeleton->HasNonceSlots();
    if (aHasNonceSlots) {
        TwistArray::Replace(&mNonceBytes, &(pNonceBytes));
        mUseFullNonce = pUseFullNonce;
    } else {
        mNonceBytes.clear();
        mUseFullNonce = false;
    }

    TwistArray::Replace(&mSources, &(pSources));
    TwistArray::Replace(&mOrbiters, &(pOrbiters));
    TwistArray::Replace(&mWanderers, &(pWanderers));
    
    mHotPack = pHotPack;
    mDestAssignType = pSkeleton->mAssignType;
    
    mDest = pDest;
    mDestWriteInverted = pDestWriteInverted;
    
    if (!BuildSourceMap(pErrorMessage)) { return false; }
    if (!BuildNonceMap(pErrorMessage)) { return false; }
    if (!BuildOrbiterMap(pErrorMessage)) { return false; }
    if (!BuildWandererMap(pErrorMessage)) { return false; }
    
    return true;
}


bool GAXPL::Bake(int pOffsetRangeLo,
                 int pOffsetRangeHi,
                 const GAXSKSkeleton *pSkeleton,
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
                 std::string *pErrorMessage) {
    if (!Configure(pSkeleton, pSaltBag, pNonceBytes, pSources, pOrbiters, pWanderers,
                   pHotPack, pUseFullNonce, pDest, pDestWriteInverted, pLoop, pErrorMessage)) {
        return false;
    }
    
    if (!GenerateStatements(pOffsetRangeLo, pOffsetRangeHi, pErrorMessage)) {
        return false;
    }
    
    return true;
}

int GAXPL::GetOrbiterIndex(GAXSKVariable pVariable) const {
    switch (pVariable) {
        case GAXSKVariable::kOrbitA: return 0;
        case GAXSKVariable::kOrbitB: return 1;
        case GAXSKVariable::kOrbitC: return 2;
        case GAXSKVariable::kOrbitD: return 3;
        case GAXSKVariable::kOrbitE: return 4;
        case GAXSKVariable::kOrbitF: return 5;
        case GAXSKVariable::kOrbitG: return 6;
        case GAXSKVariable::kOrbitH: return 7;
        case GAXSKVariable::kOrbitI: return 8;
        case GAXSKVariable::kOrbitJ: return 9;
        case GAXSKVariable::kOrbitK: return 10;
        default: return -1;
    }
}

int GAXPL::GetWandererIndex(GAXSKVariable pVariable) const {
    switch (pVariable) {
        case GAXSKVariable::kWandererA: return 0;
        case GAXSKVariable::kWandererB: return 1;
        case GAXSKVariable::kWandererC: return 2;
        case GAXSKVariable::kWandererD: return 3;
        case GAXSKVariable::kWandererE: return 4;
        case GAXSKVariable::kWandererF: return 5;
        case GAXSKVariable::kWandererG: return 6;
        case GAXSKVariable::kWandererH: return 7;
        case GAXSKVariable::kWandererI: return 8;
        case GAXSKVariable::kWandererJ: return 9;
        case GAXSKVariable::kWandererK: return 10;
        default: return -1;
    }
}

int GAXPL::GetNonceByteIndex(GAXSKNonceByteKind pNonce) const {
    switch (pNonce) {
        case GAXSKNonceByteKind::kNonceA: return 0;
        case GAXSKNonceByteKind::kNonceB: return 1;
        case GAXSKNonceByteKind::kNonceC: return 2;
        case GAXSKNonceByteKind::kNonceD: return 3;
        case GAXSKNonceByteKind::kNonceE: return 4;
        case GAXSKNonceByteKind::kNonceF: return 5;
        case GAXSKNonceByteKind::kNonceG: return 6;
        case GAXSKNonceByteKind::kNonceH: return 7;
        case GAXSKNonceByteKind::kNonceI: return 8;
        case GAXSKNonceByteKind::kNonceJ: return 9;
        case GAXSKNonceByteKind::kNonceK: return 10;
        case GAXSKNonceByteKind::kNonceL: return 11;
        case GAXSKNonceByteKind::kNonceM: return 12;
        case GAXSKNonceByteKind::kNonceN: return 13;
        case GAXSKNonceByteKind::kNonceO: return 14;
        case GAXSKNonceByteKind::kNonceP: return 15;
        default: return -1;
    }
}

int GAXPL::GetSourceIndex(GAXSKSourceKind pSource) const {
    switch (pSource) {
        case GAXSKSourceKind::kSourceA: return 0;
        case GAXSKSourceKind::kSourceB: return 1;
        case GAXSKSourceKind::kSourceC: return 2;
        case GAXSKSourceKind::kSourceD: return 3;
        case GAXSKSourceKind::kSourceE: return 4;
        case GAXSKSourceKind::kSourceF: return 5;
        case GAXSKSourceKind::kSourceG: return 6;
        case GAXSKSourceKind::kSourceH: return 7;
        case GAXSKSourceKind::kSourceI: return 8;
        case GAXSKSourceKind::kSourceJ: return 9;
        default: return -1;
    }
}

GAXSKVariable GAXPL::GetOrbiterVariableForIndex(int pIndex) const {
    switch (pIndex) {
        case 0: return GAXSKVariable::kOrbitA;
        case 1: return GAXSKVariable::kOrbitB;
        case 2: return GAXSKVariable::kOrbitC;
        case 3: return GAXSKVariable::kOrbitD;
        case 4: return GAXSKVariable::kOrbitE;
        case 5: return GAXSKVariable::kOrbitF;
        case 6: return GAXSKVariable::kOrbitG;
        case 7: return GAXSKVariable::kOrbitH;
        case 8: return GAXSKVariable::kOrbitI;
        case 9: return GAXSKVariable::kOrbitJ;
        case 10: return GAXSKVariable::kOrbitK;
        default: return GAXSKVariable::kInvalid;
    }
}

GAXSKVariable GAXPL::GetWandererVariableForIndex(int pIndex) const {
    switch (pIndex) {
        case 0: return GAXSKVariable::kWandererA;
        case 1: return GAXSKVariable::kWandererB;
        case 2: return GAXSKVariable::kWandererC;
        case 3: return GAXSKVariable::kWandererD;
        case 4: return GAXSKVariable::kWandererE;
        case 5: return GAXSKVariable::kWandererF;
        case 6: return GAXSKVariable::kWandererG;
        case 7: return GAXSKVariable::kWandererH;
        case 8: return GAXSKVariable::kWandererI;
        case 9: return GAXSKVariable::kWandererJ;
        case 10: return GAXSKVariable::kWandererK;
        default: return GAXSKVariable::kInvalid;
    }
}

bool GAXPL::BuildSourceMap(std::string *pErrorMessage) {
    mSourceMap.clear();

    if (mSkeleton == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GAXPL::BuildSourceMap has null skeleton";
        }
        return false;
    }

    for (std::size_t aStatementIndex = 0;
         aStatementIndex < mSkeleton->mStatements.size();
         ++aStatementIndex) {

        const GAXSKStatement &aStatement =
            mSkeleton->mStatements[aStatementIndex];

        if (aStatement.mKind != GAXSKStatementKind::kContextWordAssign) {
            continue;
        }

        const GAXSKContextWordPlan &aPlan = aStatement.mContextWord;

        for (std::size_t aSlotIndex = 0;
             aSlotIndex < aPlan.mSlots.size();
             ++aSlotIndex) {

            const GAXSKInputSlot &aSlot = aPlan.mSlots[aSlotIndex];

            if (aSlot.mKind != GAXSKInputSlotKind::kSource) {
                continue;
            }

            const int aSourceIndex = GetSourceIndex(aSlot.mSource);
            if (aSourceIndex < 0) {
                SetError(pErrorMessage,
                         "GAXPL::BuildSourceMap found invalid source kind at statement=" +
                         std::to_string(aStatementIndex) +
                         ", slot=" +
                         std::to_string(aSlotIndex));
                return false;
            }

            if (static_cast<std::size_t>(aSourceIndex) >= mSources.size()) {
                SetError(pErrorMessage,
                         "GAXPL::BuildSourceMap could not bind skeleton source at statement=" +
                         std::to_string(aStatementIndex) +
                         ", slot=" +
                         std::to_string(aSlotIndex) +
                         ", source_index=" +
                         std::to_string(aSourceIndex) +
                         ", source_count=" +
                         std::to_string(mSources.size()));
                return false;
            }

            if (mSources[static_cast<std::size_t>(aSourceIndex)].IsInvalid()) {
                SetError(pErrorMessage,
                         "GAXPL::BuildSourceMap source symbol is invalid at statement=" +
                         std::to_string(aStatementIndex) +
                         ", slot=" +
                         std::to_string(aSlotIndex) +
                         ", source_index=" +
                         std::to_string(aSourceIndex));
                return false;
            }

            mSourceMap[aSlot.mSource] =
                mSources[static_cast<std::size_t>(aSourceIndex)];
        }
    }

    return true;
}

bool GAXPL::BuildNonceMap(std::string *pErrorMessage) {
    mNonceMap.clear();

    if (mSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::BuildNonceMap has null skeleton");
        return false;
    }

    for (const GAXSKStatement &aStatement : mSkeleton->mStatements) {
        if (aStatement.mKind != GAXSKStatementKind::kContextWordAssign) {
            continue;
        }

        const GAXSKContextWordPlan &aPlan = aStatement.mContextWord;

        for (const GAXSKInputSlot &aSlot : aPlan.mSlots) {
            if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
                continue;
            }

            const int aNonceIndex = GetNonceByteIndex(aSlot.mNonceByte);
            if (aNonceIndex < 0) {
                SetError(pErrorMessage, "GAXPL::BuildNonceMap found invalid nonce byte kind");
                return false;
            }

            if (static_cast<std::size_t>(aNonceIndex) >= mNonceBytes.size()) {
                SetError(pErrorMessage, "GAXPL::BuildNonceMap could not bind skeleton nonce byte");
                return false;
            }

            if (mNonceBytes[static_cast<std::size_t>(aNonceIndex)].IsInvalid()) {
                SetError(pErrorMessage, "GAXPL::BuildNonceMap nonce byte symbol is invalid");
                return false;
            }

            mNonceMap[aSlot.mNonceByte] = mNonceBytes[static_cast<std::size_t>(aNonceIndex)];
        }
    }

    return true;
}

bool GAXPL::BuildOrbiterMap(std::string *pErrorMessage) {
    mOrbiterMap.clear();

    for (std::size_t aIndex = 0; aIndex < mOrbiters.size(); ++aIndex) {
        const GAXSKVariable aVariable = GetOrbiterVariableForIndex(static_cast<int>(aIndex));
        if (aVariable == GAXSKVariable::kInvalid) {
            SetError(pErrorMessage, "GAXPL::BuildOrbiterMap received too many orbiters");
            return false;
        }

        if (mOrbiters[aIndex].IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildOrbiterMap orbiter symbol is invalid");
            return false;
        }

        mOrbiterMap[aVariable] = mOrbiters[aIndex];
    }

    return true;
}

bool GAXPL::BuildWandererMap(std::string *pErrorMessage) {
    mWandererMap.clear();

    for (std::size_t aIndex = 0; aIndex < mWanderers.size(); ++aIndex) {
        const GAXSKVariable aVariable = GetWandererVariableForIndex(static_cast<int>(aIndex));
        if (aVariable == GAXSKVariable::kInvalid) {
            SetError(pErrorMessage, "GAXPL::BuildWandererMap received too many wanderers");
            return false;
        }

        if (mWanderers[aIndex].IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildWandererMap wanderer symbol is invalid");
            return false;
        }

        mWandererMap[aVariable] = mWanderers[aIndex];
    }

    return true;
}

bool GAXPL::SymbolForVariable(GAXSKVariable pVariable,
                              GSymbol *pResult,
                              std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXPL::SymbolForVariable received null result");
        return false;
    }

    *pResult = GSymbol();

    switch (pVariable) {
        case GAXSKVariable::kIngress:
            *pResult = GSymbol::Var(TwistVariable::kIngress);
            break;
        case GAXSKVariable::kCross:
            *pResult = GSymbol::Var(TwistVariable::kCross);
            break;
        case GAXSKVariable::kPrevious:
            *pResult = GSymbol::Var(TwistVariable::kPrevious);
            break;
        case GAXSKVariable::kScatter:
            *pResult = GSymbol::Var(TwistVariable::kScatter);
            break;
        case GAXSKVariable::kCarry:
            *pResult = GSymbol::Var(TwistVariable::kCarry);
            break;
        default:
            if (GetOrbiterIndex(pVariable) >= 0) {
                const auto aIterator = mOrbiterMap.find(pVariable);
                if (aIterator == mOrbiterMap.end()) {
                    SetError(pErrorMessage, "GAXPL::SymbolForVariable could not bind orbiter");
                    return false;
                }
                *pResult = aIterator->second;
            } else if (GetWandererIndex(pVariable) >= 0) {
                const auto aIterator = mWandererMap.find(pVariable);
                if (aIterator == mWandererMap.end()) {
                    SetError(pErrorMessage, "GAXPL::SymbolForVariable could not bind wanderer");
                    return false;
                }
                *pResult = aIterator->second;
            } else {
                SetError(pErrorMessage, "GAXPL::SymbolForVariable received invalid variable");
                return false;
            }
            break;
    }

    if (pResult->IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::SymbolForVariable produced invalid symbol");
        return false;
    }

    return true;
}

bool GAXPL::GeneratePreviousAssignStatement(const GAXSKStatement &pStatement,
                                            std::vector<GStatement> *pStatements,
                                            std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GeneratePreviousAssignStatement received null statements");
        return false;
    }
    GSymbol aTarget;
    if (!SymbolForVariable(pStatement.mTarget, &aTarget, pErrorMessage)) {
        return false;
    }
    GSymbol aSource;
    if (!SymbolForVariable(pStatement.mSource, &aSource, pErrorMessage)) {
        return false;
    }
    pStatements->push_back(GStatement::Comment(""));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget), GExpr::Symbol(aSource)));
    return true;
}

bool GAXPL::MakeCrushPairExpr(const GAXSKCrushPairPlan &pPair,
                              GExpr *pResult,
                              std::string *pErrorMessage) const {
    if (pResult == nullptr) {
        SetError(pErrorMessage, "GAXPL::MakeCrushPairExpr received null result");
        return false;
    }

    *pResult = GExpr();

    if (pPair.mA == GAXSKVariable::kInvalid ||
        pPair.mB == GAXSKVariable::kInvalid) {
        SetError(pErrorMessage, "GAXPL::MakeCrushPairExpr received invalid pair variable");
        return false;
    }

    if (pPair.mRotation < 0 || pPair.mRotation >= 64) {
        SetError(pErrorMessage, "GAXPL::MakeCrushPairExpr received invalid rotation");
        return false;
    }

    GSymbol aSymbolA;
    if (!SymbolForVariable(pPair.mA, &aSymbolA, pErrorMessage)) {
        return false;
    }

    GSymbol aSymbolB;
    if (!SymbolForVariable(pPair.mB, &aSymbolB, pErrorMessage)) {
        return false;
    }

    GExpr aExprA = GExpr::Symbol(aSymbolA);
    GExpr aExprB = GExpr::Symbol(aSymbolB);

    if (aExprA.IsInvalid() || aExprB.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::MakeCrushPairExpr failed to build symbol expression");
        return false;
    }

    if (pPair.mRotateA) {
        aExprA = GAXPLQuick::RotateSymbol(aSymbolA, pPair.mRotation);
    } else {
        aExprB = GAXPLQuick::RotateSymbol(aSymbolB, pPair.mRotation);
    }

    if (aExprA.IsInvalid() || aExprB.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::MakeCrushPairExpr failed to rotate pair expression");
        return false;
    }

    switch (pPair.mOp) {
        case GAXSKOpKind::kAdd:
            *pResult = GExpr::Add(aExprA, aExprB);
            break;

        case GAXSKOpKind::kXor:
            *pResult = GExpr::Xor(aExprA, aExprB);
            break;

        default:
            SetError(pErrorMessage, "GAXPL::MakeCrushPairExpr received invalid pair op");
            return false;
    }

    if (pResult->IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::MakeCrushPairExpr produced invalid expression");
        return false;
    }

    return true;
}

bool GAXPL::GenerateIngressCrushStatement(const GAXSKStatement &pStatement,
                                          std::vector<GStatement> *pStatements,
                                          std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement received null statements");
        return false;
    }

    if (pStatement.mKind != GAXSKStatementKind::kIngressCrush) {
        SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement received wrong statement kind");
        return false;
    }

    const GAXSKCrushPlan &aPlan = pStatement.mCrush;

    if (aPlan.mTarget != GAXSKVariable::kIngress) {
        SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement target must be ingress");
        return false;
    }

    GSymbol aTarget;
    if (!SymbolForVariable(aPlan.mTarget, &aTarget, pErrorMessage)) {
        return false;
    }

    std::vector<GExpr> aTerms;
    aTerms.reserve(aPlan.mPairs.size() + (aPlan.mHasOdd ? 1U : 0U));

    for (const GAXSKCrushPairPlan &aPair : aPlan.mPairs) {
        GExpr aPairExpr;
        if (!MakeCrushPairExpr(aPair, &aPairExpr, pErrorMessage)) {
            return false;
        }

        if (aPairExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement produced invalid pair expression");
            return false;
        }

        aTerms.push_back(aPairExpr);
    }

    if (aPlan.mHasOdd) {
        if (aPlan.mOdd.mVariable == GAXSKVariable::kInvalid) {
            SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement received invalid odd variable");
            return false;
        }

        GSymbol aOddSymbol;
        if (!SymbolForVariable(aPlan.mOdd.mVariable, &aOddSymbol, pErrorMessage)) {
            return false;
        }

        GExpr aOddExpr;

        if (aPlan.mOdd.mHasRotation) {
            if (aPlan.mOdd.mRotation < 0 || aPlan.mOdd.mRotation >= 64) {
                SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement received invalid odd rotation");
                return false;
            }

            aOddExpr = GAXPLQuick::RotateSymbol(aOddSymbol, aPlan.mOdd.mRotation);
        } else {
            aOddExpr = GExpr::Symbol(aOddSymbol);
        }

        if (aOddExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement failed to build odd expression");
            return false;
        }

        aTerms.push_back(aOddExpr);
    }

    if (aTerms.empty()) {
        SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement received no crush terms");
        return false;
    }

    //pStatements->push_back(GStatement::Comment(""));

    // First assignment is directly to the first orbiter-derived crush term.
    // No need for:
    //   aIngress = 0U;
    pStatements->push_back(
        GStatement::Assign(
            GTarget::Symbol(aTarget),
            aTerms[0]
        )
    );

    // Remaining pair / odd terms accumulate into ingress.
    for (std::size_t aTermIndex = 1U; aTermIndex < aTerms.size(); ++aTermIndex) {
        GExpr aExpr;

        switch (aPlan.mOuterOp) {
            case GAXSKOpKind::kAdd:
                aExpr = GExpr::Add(GExpr::Symbol(aTarget), aTerms[aTermIndex]);
                break;

            case GAXSKOpKind::kXor:
                aExpr = GExpr::Xor(GExpr::Symbol(aTarget), aTerms[aTermIndex]);
                break;

            default:
                SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement received invalid outer op");
                return false;
        }

        if (aExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement failed to accumulate crush term");
            return false;
        }

        pStatements->push_back(
            GStatement::Assign(
                GTarget::Symbol(aTarget),
                aExpr
            )
        );
    }

    // Old-style finalization:
    //   ingress = Diffuse(ingress + scatter)
    GSymbol aScatterSymbol;
    if (!SymbolForVariable(GAXSKVariable::kScatter, &aScatterSymbol, pErrorMessage)) {
        return false;
    }

    GExpr aFinalizeExpr = GExpr::Add(
        GExpr::Symbol(aTarget),
        GExpr::Symbol(aScatterSymbol)
    );
    
    

    if (aFinalizeExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement failed to add scatter");
        return false;
    }

    if (aPlan.mHasDiffuse) {
        aFinalizeExpr = GAXPLQuick::Diffuse(aFinalizeExpr, aPlan.mDiffuse);

        if (aFinalizeExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateIngressCrushStatement failed to diffuse ingress crush");
            return false;
        }
    }

    pStatements->push_back(
        GStatement::Assign(
            GTarget::Symbol(aTarget),
            aFinalizeExpr
        )
    );
    
    

    return true;
}

bool GAXPL::GenerateContextWordStatement(int pOffsetRangeLo,
                                         int pOffsetRangeHi,
                                         const GAXSKStatement &pStatement,
                                         std::vector<GStatement> *pStatements,
                                         std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateContextWordStatement received null statements");
        return false;
    }
    
    const GAXSKContextWordPlan &aPlan = pStatement.mContextWord;
    
    GSymbol aTarget;
    if (!SymbolForVariable(aPlan.mTarget, &aTarget, pErrorMessage)) {
        return false;
    }
    
    pStatements->push_back(GStatement::Comment(""));
    
    GExpr aSourceExpr;
    if (!GAXPLQuick::BakeInputSlotWordsXorSources(aPlan.mSlots,
                                                  mSourceMap,
                                                  mNonceMap,
                                                  &aSourceExpr,
                                                  pOffsetRangeLo,
                                                  pOffsetRangeHi,
                                                  pErrorMessage)) {
        return false;
    }
    
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget),
                                              aSourceExpr));
    
    GExpr aFinalizeExpr = GExpr::Symbol(aTarget);
    if (aFinalizeExpr.IsInvalid()) {
        SetError(pErrorMessage,
                 "GAXPL::GenerateContextWordStatement failed to build context word symbol expression");
        return false;
    }
    
    if (aPlan.mHasDomainMix) {
        GSymbol aDomainWord;
        
        if (aPlan.mIsIngress == true) {
            aDomainWord = DomainWordSymbol(TwistConstants::kIngress);
        } else {
            aDomainWord = DomainWordSymbol(TwistConstants::kCross);
        }
        
        aFinalizeExpr = GExpr::Xor(aFinalizeExpr, GExpr::Symbol(aDomainWord));
        if (aFinalizeExpr.IsInvalid()) {
            SetError(pErrorMessage,
                     "GAXPL::GenerateContextWordStatement failed to mix context word domain");
            return false;
        }
    }
    
    if (mNonceMap.size() > 0) {
        GExpr aNonceExpr;
        if (!GAXPLQuick::BakeInputSlotWordsXorNonces(aPlan.mSlots,
                                                     mSourceMap,
                                                     mNonceMap,
                                                     &aNonceExpr,
                                                     pErrorMessage)) {
            return false;
        }
        
        aFinalizeExpr = GExpr::Xor(aFinalizeExpr, aNonceExpr);
        if (aFinalizeExpr.IsInvalid()) {
            SetError(pErrorMessage,
                     "GAXPL::GenerateContextWordStatement failed to mix context word nonce");
            return false;
        }
    }
    
    GExpr aDiffuse = GAXPLQuick::Diffuse(aFinalizeExpr,
                                         aPlan.mDiffuse);
    
    if (aDiffuse.IsInvalid()) {
        SetError(pErrorMessage,
                 "GAXPL::GenerateContextWordStatement failed to diffuse context word");
        return false;
    }
    
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget),
                                              aDiffuse));
    
    return true;
}

bool GAXPL::GenerateScatterMixStatement(const GAXSKStatement &pStatement,
                                        std::vector<GStatement> *pStatements,
                                        std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement received null statements");
        return false;
    }

    const GAXSKScatterMixPlan &aPlan = pStatement.mScatterMix;

    GSymbol aTarget;
    if (!SymbolForVariable(aPlan.mTarget, &aTarget, pErrorMessage)) {
        return false;
    }

    auto BuildTermExpr = [&](const GAXSKVariableTerm &pTerm,
                             GExpr *pResult,
                             const char *pErrorText) -> bool {
        if (pResult == nullptr) {
            SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement received null term result");
            return false;
        }

        GSymbol aSymbol;
        if (!SymbolForVariable(pTerm.mVariable, &aSymbol, pErrorMessage)) {
            return false;
        }

        GExpr aExpr = GAXPLQuick::RotateSymbol(aSymbol, pTerm.mRotation);
        if (aExpr.IsInvalid()) {
            SetError(pErrorMessage, pErrorText);
            return false;
        }

        *pResult = aExpr;
        return true;
    };

    auto ApplyScatterOp = [&](const GExpr &pLeft,
                              const GExpr &pRight,
                              GAXSKScatterMixOp pOp,
                              GExpr *pResult,
                              const char *pErrorText) -> bool {
        if (pResult == nullptr) {
            SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement received null op result");
            return false;
        }

        switch (pOp) {
            case GAXSKScatterMixOp::kAdd:
                *pResult = GExpr::Add(pLeft, pRight);
                break;

            case GAXSKScatterMixOp::kXor:
                *pResult = GExpr::Xor(pLeft, pRight);
                break;

            default:
                SetError(pErrorMessage, pErrorText);
                return false;
        }

        if (pResult->IsInvalid()) {
            SetError(pErrorMessage, pErrorText);
            return false;
        }

        return true;
    };

    GExpr aLeftA;
    GExpr aLeftB;
    GExpr aRightA;
    GExpr aRightB;

    if (!BuildTermExpr(aPlan.mLeftPair.mLeft,
                       &aLeftA,
                       "GAXPL::GenerateScatterMixStatement failed to build left pair left term")) {
        return false;
    }

    if (!BuildTermExpr(aPlan.mLeftPair.mRight,
                       &aLeftB,
                       "GAXPL::GenerateScatterMixStatement failed to build left pair right term")) {
        return false;
    }

    if (!BuildTermExpr(aPlan.mRightPair.mLeft,
                       &aRightA,
                       "GAXPL::GenerateScatterMixStatement failed to build right pair left term")) {
        return false;
    }

    if (!BuildTermExpr(aPlan.mRightPair.mRight,
                       &aRightB,
                       "GAXPL::GenerateScatterMixStatement failed to build right pair right term")) {
        return false;
    }

    GExpr aLeftPairExpr;
    if (!ApplyScatterOp(aLeftA,
                        aLeftB,
                        aPlan.mLeftPair.mOp,
                        &aLeftPairExpr,
                        "GAXPL::GenerateScatterMixStatement failed to build left pair expression")) {
        return false;
    }

    GExpr aRightPairExpr;
    if (!ApplyScatterOp(aRightA,
                        aRightB,
                        aPlan.mRightPair.mOp,
                        &aRightPairExpr,
                        "GAXPL::GenerateScatterMixStatement failed to build right pair expression")) {
        return false;
    }

    GExpr aScatterExpr;
    if (!ApplyScatterOp(aLeftPairExpr,
                        aRightPairExpr,
                        aPlan.mOuterOp,
                        &aScatterExpr,
                        "GAXPL::GenerateScatterMixStatement failed to build outer scatter expression")) {
        return false;
    }

    if (aScatterExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement produced invalid scatter expression");
        return false;
    }

    pStatements->push_back(GStatement::Comment(""));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget), aScatterExpr));

    GExpr aFinalizeExpr = GExpr::Symbol(aTarget);
    if (aFinalizeExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement produced invalid scatter symbol expression");
        return false;
    }

    if (aPlan.mHasDomainMix) {
        GSymbol aDomainWord = DomainWordSymbol(TwistConstants::kScatter);

        if (aDomainWord.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement produced invalid domain word");
            return false;
        }

        aFinalizeExpr = GExpr::Xor(aFinalizeExpr, GExpr::Symbol(aDomainWord));
        if (aFinalizeExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement failed to apply scatter domain mix");
            return false;
        }
    }

    if (!mNonceBytes.empty()) {
        GExpr aNonceExpr;
        if (!BuildRandomNonceMixExpr(1, 1, &aNonceExpr, pErrorMessage)) {
            return false;
        }

        aFinalizeExpr = GExpr::Xor(aFinalizeExpr, aNonceExpr);
        if (aFinalizeExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement failed to build scatter nonce mix");
            return false;
        }
    }

    aFinalizeExpr = GAXPLQuick::Diffuse(aFinalizeExpr, aPlan.mDiffuse);

    if (aFinalizeExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::GenerateScatterMixStatement failed to diffuse scatter");
        return false;
    }

    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aTarget), aFinalizeExpr));
    
    pStatements->push_back(GStatement::Comment(""));

    return true;
}

bool GAXPL::GenerateCarryCrushStatement(const GAXSKStatement &pStatement,
                                        std::vector<GStatement> *pStatements,
                                        std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement received null statements");
        return false;
    }

    if (pStatement.mKind != GAXSKStatementKind::kCarryCrush) {
        SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement received wrong statement kind");
        return false;
    }

    const GAXSKCrushPlan &aPlan = pStatement.mCarry;

    if (aPlan.mTarget != GAXSKVariable::kCarry) {
        SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement target must be carry");
        return false;
    }

    GSymbol aTarget;
    if (!SymbolForVariable(aPlan.mTarget, &aTarget, pErrorMessage)) {
        return false;
    }

    if (aPlan.mOuterOp != GAXSKOpKind::kAdd) {
        SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement expected add outer op");
        return false;
    }

    pStatements->push_back(GStatement::Comment(""));

    for (const GAXSKCrushPairPlan &aPair : aPlan.mPairs) {
        GExpr aPairExpr;
        if (!MakeCrushPairExpr(aPair, &aPairExpr, pErrorMessage)) {
            return false;
        }

        if (aPairExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement produced invalid pair expression");
            return false;
        }

        GExpr aExpr = GExpr::Add(GExpr::Symbol(aTarget), aPairExpr);

        if (aExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement failed to add pair expression");
            return false;
        }

        pStatements->push_back(
            GStatement::Assign(
                GTarget::Symbol(aTarget),
                aExpr
            )
        );
    }

    if (aPlan.mHasOdd) {
        if (aPlan.mOdd.mVariable == GAXSKVariable::kInvalid) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement received invalid odd variable");
            return false;
        }

        GSymbol aOddSymbol;
        if (!SymbolForVariable(aPlan.mOdd.mVariable, &aOddSymbol, pErrorMessage)) {
            return false;
        }

        GExpr aOddExpr;

        if (aPlan.mOdd.mHasRotation) {
            if (aPlan.mOdd.mRotation < 0 || aPlan.mOdd.mRotation >= 64) {
                SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement received invalid odd rotation");
                return false;
            }

            aOddExpr = GAXPLQuick::RotateSymbol(aOddSymbol, aPlan.mOdd.mRotation);
        } else {
            aOddExpr = GExpr::Symbol(aOddSymbol);
        }

        if (aOddExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement failed to build odd expression");
            return false;
        }

        GExpr aExpr = GExpr::Add(GExpr::Symbol(aTarget), aOddExpr);

        if (aExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement failed to add odd expression");
            return false;
        }

        pStatements->push_back(
            GStatement::Assign(
                GTarget::Symbol(aTarget),
                aExpr
            )
        );
    }

    if (aPlan.mHasFinalTerm) {
        if (aPlan.mFinalTerm.mVariable == GAXSKVariable::kInvalid) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement received invalid final term");
            return false;
        }

        if (aPlan.mFinalTerm.mRotation < 0 ||
            aPlan.mFinalTerm.mRotation >= 64) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement received invalid final rotation");
            return false;
        }

        GSymbol aFinalSymbol;
        if (!SymbolForVariable(aPlan.mFinalTerm.mVariable, &aFinalSymbol, pErrorMessage)) {
            return false;
        }

        GExpr aFinalExpr = GAXPLQuick::RotateSymbol(aFinalSymbol,
                                                    aPlan.mFinalTerm.mRotation);

        if (aFinalExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement failed to build final expression");
            return false;
        }

        GExpr aExpr = GExpr::Add(GExpr::Symbol(aTarget), aFinalExpr);

        if (aExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement failed to add final expression");
            return false;
        }

        pStatements->push_back(
            GStatement::Assign(
                GTarget::Symbol(aTarget),
                aExpr
            )
        );
    }

    GExpr aDiffuseExpr = GExpr::Symbol(aTarget);

    if (aDiffuseExpr.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement produced invalid carry expression");
        return false;
    }

    if (aPlan.mHasDiffuse) {
        aDiffuseExpr = GAXPLQuick::Diffuse(aDiffuseExpr, aPlan.mDiffuse);

        if (aDiffuseExpr.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::GenerateCarryCrushStatement failed to diffuse carry");
            return false;
        }
    }

    pStatements->push_back(
        GStatement::Assign(
            GTarget::Symbol(aTarget),
            aDiffuseExpr
        )
    );

    return true;
}

bool GAXPL::GenerateUpdateStatement(int pStatementIndex,
                                    const GAXSKStatement &pStatement,
                                    std::vector<GStatement> *pStatements,
                                    std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateUpdateStatement received null statements");
        return false;
    }

    const GAXSKUpdatePlan &aPlan = pStatement.mUpdate;

    GSymbol aTarget;
    if (!SymbolForVariable(aPlan.mTarget, &aTarget, pErrorMessage)) {
        return false;
    }
    

    // These are placeholders for the upcoming assignment-list binder.
    GExpr aSaltExpr;
    GExpr aNonceExpr;
    
    auto aSaltIt = mSaltExprMap.find(pStatementIndex);
    if (aSaltIt != mSaltExprMap.end()) {
        aSaltExpr = aSaltIt->second;
    }

    auto aNonceIt = mNonceExprMap.find(pStatementIndex);
    if (aNonceIt != mNonceExprMap.end()) {
        aNonceExpr = aNonceIt->second;
    }

    switch (pStatement.mKind) {
        case GAXSKStatementKind::kOrbiterAssign:
        case GAXSKStatementKind::kOrbiterAdd: {
            std::vector<GExpr> aTerms;
            if (!MakeUpdateTerms(aPlan, &aTerms, pErrorMessage)) {
                return false;
            }

            return EmitAddAssign(aTarget,
                                 aTerms,
                                 aSaltExpr,
                                 aNonceExpr,
                                 pStatements,
                                 pErrorMessage);
        }

        case GAXSKStatementKind::kOrbiterXor: {
            std::vector<GExpr> aTerms;
            if (!MakeUpdateTerms(aPlan, &aTerms, pErrorMessage)) {
                return false;
            }

            return EmitXorAssign(aTarget,
                                 aTerms,
                                 aSaltExpr,
                                 aNonceExpr,
                                 pStatements,
                                 pErrorMessage);
        }

        case GAXSKStatementKind::kWandererAdd:
            return EmitWandererUpdate(aPlan,
                                      aTarget,
                                      false,
                                      aSaltExpr,
                                      aNonceExpr,
                                      pStatements,
                                      pErrorMessage);

        case GAXSKStatementKind::kWandererXor:
            return EmitWandererUpdate(aPlan,
                                      aTarget,
                                      true,
                                      aSaltExpr,
                                      aNonceExpr,
                                      pStatements,
                                      pErrorMessage);

        case GAXSKStatementKind::kOrbiterMulRotate:
        case GAXSKStatementKind::kWandererMulRotate:
            return EmitMulRotate(aPlan,
                                 aTarget,
                                 pStatements,
                                 pErrorMessage);

        default:
            SetError(pErrorMessage, "GAXPL::GenerateUpdateStatement received unsupported statement kind");
            return false;
    }
}

bool GAXPL::BuildNonceChoices(std::string *pErrorMessage) {
    static constexpr int kNonceChoiceCount = 12;

    mNonceChoices.clear();
    mNonceChoices.reserve(kNonceChoiceCount);

    if (mNonceBytes.empty()) {
        SetError(pErrorMessage, "GAXPL::BuildNonceChoices had no nonce symbols");
        return false;
    }

    for (const GSymbol &aSymbol : mNonceBytes) {
        if (aSymbol.IsInvalid()) {
            SetError(pErrorMessage, "GAXPL::BuildNonceChoices found invalid nonce symbol");
            return false;
        }
    }

    auto PushSymbolChoice = [&](const GSymbol &pSymbol, bool pPreferred) -> bool {
        if (pSymbol.IsInvalid()) {
            return false;
        }

        NonceSymbolChoice aChoice;
        aChoice.mSymbol = pSymbol;
        aChoice.mPreferred = pPreferred;

        mNonceChoices.push_back(aChoice);
        return true;
    };

    for (const GSymbol &aSymbol : mPreferredNonceSymbols) {
        if (static_cast<int>(mNonceChoices.size()) >= kNonceChoiceCount) {
            break;
        }

        if (!PushSymbolChoice(aSymbol, true)) {
            SetError(pErrorMessage, "GAXPL::BuildNonceChoices failed to push preferred nonce");
            return false;
        }
    }

    for (const GSymbol &aSymbol : mFallbackNonceSymbols) {
        if (static_cast<int>(mNonceChoices.size()) >= kNonceChoiceCount) {
            break;
        }

        if (!PushSymbolChoice(aSymbol, false)) {
            SetError(pErrorMessage, "GAXPL::BuildNonceChoices failed to push fallback nonce");
            return false;
        }
    }

    while (static_cast<int>(mNonceChoices.size()) < kNonceChoiceCount) {
        const int aIndex = Random::Get(static_cast<int>(mNonceBytes.size()));

        if (!PushSymbolChoice(mNonceBytes[static_cast<std::size_t>(aIndex)], false)) {
            SetError(pErrorMessage, "GAXPL::BuildNonceChoices failed to reuse nonce");
            return false;
        }
    }

    Random::Shuffle(&mNonceChoices);

    return true;
}

bool GAXPL::GenerateStatements(int pOffsetRangeLo,
                               int pOffsetRangeHi,
                               std::string *pErrorMessage) {
    if (mLoop == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateStatements received null loop");
        return false;
    }

    if (mSkeleton == nullptr) {
        SetError(pErrorMessage, "GAXPL::GenerateStatements received null skeleton");
        return false;
    }
    
    
    
    mPreferredNonceSymbols.clear();
    mFallbackNonceSymbols.clear();
    
    std::vector<bool> aUsed(mNonceBytes.size(), false);
    bool aHasNonceSlots = false;

    for (const GAXSKStatement &aStatement : mSkeleton->mStatements) {
        if (aStatement.mKind != GAXSKStatementKind::kContextWordAssign) {
            continue;
        }

        for (const GAXSKInputSlot &aSlot : aStatement.mContextWord.mSlots) {
            if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
                continue;
            }

            aHasNonceSlots = true;
            const int aNonceIndex = GetNonceByteIndex(aSlot.mNonceByte);
            if (aNonceIndex >= 0 && static_cast<std::size_t>(aNonceIndex) < aUsed.size()) {
                aUsed[static_cast<std::size_t>(aNonceIndex)] = true;
            }
        }
    }

    if (aHasNonceSlots) {
        for (std::size_t i = 0U; i < mNonceBytes.size(); ++i) {
            if (static_cast<std::size_t>(i) >= mNonceBytes.size()) {
                SetError(pErrorMessage, "GAXPL::BuildNonceExprMap missing nonce byte symbol");
                return false;
            }

            if (mNonceBytes[i].IsInvalid()) {
                SetError(pErrorMessage, "GAXPL::BuildNonceExprMap found invalid nonce byte symbol");
                return false;
            }

            if (aUsed[i]) {
                mFallbackNonceSymbols.push_back(mNonceBytes[i]);
            } else {
                mPreferredNonceSymbols.push_back(mNonceBytes[i]);
            }
        }
    
        Random::Shuffle(&mPreferredNonceSymbols);
        Random::Shuffle(&mFallbackNonceSymbols);
        
        if (!BuildNonceChoices(pErrorMessage)) {
            return false;
        }
    }
    
    if (!BuildSaltExprMap(pErrorMessage)) {
        return false;
    }
    
    if (aHasNonceSlots) {
        if (!BuildNonceExprMap(pErrorMessage)) {
            return false;
        }
    }
    
    mNonceChoices.clear();

    std::vector<GStatement> aStatements;
    for (int aStatementIndex = 0; aStatementIndex < mSkeleton->mStatements.size(); aStatementIndex++) {
        
        const GAXSKStatement &aSkeletonStatement =
            mSkeleton->mStatements[static_cast<std::size_t>(aStatementIndex)];
        
        if (aSkeletonStatement.mKind == GAXSKStatementKind::kComment) {
            aStatements.push_back(GStatement::Comment(""));
            continue;
        }
        
        if (aSkeletonStatement.mKind == GAXSKStatementKind::kPreviousAssign) {
            if (!GeneratePreviousAssignStatement(aSkeletonStatement,
                                                 &aStatements,
                                                 pErrorMessage)) {
                return false;
            }
            continue;
        }
        

        if (aSkeletonStatement.mKind == GAXSKStatementKind::kContextWordAssign) {
            if (!GenerateContextWordStatement(pOffsetRangeLo,
                                              pOffsetRangeHi,
                                              aSkeletonStatement,
                                              &aStatements,
                                              pErrorMessage)) {
                return false;
            }
            continue;
        }
        
        if (aSkeletonStatement.mKind == GAXSKStatementKind::kScatterMix) {
            if (!GenerateScatterMixStatement(aSkeletonStatement,
                                             &aStatements,
                                             pErrorMessage)) {
                return false;
            }
            continue;
        }
        
        if (aSkeletonStatement.mKind == GAXSKStatementKind::kIngressCrush) {
            if (!GenerateIngressCrushStatement(aSkeletonStatement,
                                               &aStatements,
                                               pErrorMessage)) {
                return false;
            }
            continue;
        }
        
        if (aSkeletonStatement.mKind == GAXSKStatementKind::kCarryCrush) {
            if (!GenerateCarryCrushStatement(aSkeletonStatement,
                                             &aStatements,
                                             pErrorMessage)) {
                return false;
            }
            continue;
        }
        
        if (aSkeletonStatement.mKind == GAXSKStatementKind::kOrbiterAssign ||
            aSkeletonStatement.mKind == GAXSKStatementKind::kOrbiterAdd ||
            aSkeletonStatement.mKind == GAXSKStatementKind::kOrbiterXor ||
            aSkeletonStatement.mKind == GAXSKStatementKind::kOrbiterMulRotate ||
            aSkeletonStatement.mKind == GAXSKStatementKind::kWandererAdd ||
            aSkeletonStatement.mKind == GAXSKStatementKind::kWandererXor ||
            aSkeletonStatement.mKind == GAXSKStatementKind::kWandererMulRotate) {
            if (!GenerateUpdateStatement(aStatementIndex, aSkeletonStatement, &aStatements, pErrorMessage)) {
                return false;
            }
            continue;
        }
        
        SetError(pErrorMessage,
                 "GAXPL::GenerateStatements unsupported statement kind: " +
                 std::to_string(static_cast<int>(aSkeletonStatement.mKind)));
        return false;
    }
    
    if (mDest.IsInvalid()) {
        SetError(pErrorMessage, "GAXPL::GenerateStatements received invalid dest symbol");
        return false;
    }

    GSymbol aIndexSymbol = GSymbol::Var(TwistVariable::kIndex);
    GSymbol aIngressSymbol = GSymbol::Var(TwistVariable::kIngress);

    aStatements.push_back(GStatement::Comment(""));

    if (mDestWriteInverted) {
        GStatement aDestStatement =
            GQuick::MakeAssignDestStatementInverted(
                    mDest,
                    aIndexSymbol,
                    aIngressSymbol
        );
        aDestStatement.mAssignType = mDestAssignType;
        aStatements.push_back(aDestStatement);
    } else {
        GStatement aDestStatement =
            GQuick::MakeAssignDestStatement(
                    mDest,
                    aIndexSymbol,
                    aIngressSymbol
        );
        aDestStatement.mAssignType = mDestAssignType;
        aStatements.push_back(aDestStatement);
    }
    
    mLoop->AddBody(&aStatements);
    return true;
}
