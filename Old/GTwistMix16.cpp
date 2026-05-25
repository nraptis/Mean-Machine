//
//  GTwistMix16.cpp
//  MeanMachine
//
//  Created by Dragon on 4/29/26.
//

#include "GTwistMix16.hpp"

#include "Random.hpp"

namespace {

struct Mix161Config {
    bool        mOracleAUsesRotate = false;   // false => aByteA, true => RotL8(aByteA, 1)
    bool        mOracleBUsesRotate = false;   // false => aByteB, true => RotL8(aByteB, 1)
    bool        mUseAddIndex = false;         // false => xor, true => add
    int         mTempRotateAmount = 3;        // 3 or 5
    bool        mByteAUsesRotatedTemp = false;// false => aByteA ^= aTemp, true => aByteA ^= RotL8(aTemp, 1)
};

void SetError(std::string *pError,
              const std::string &pMessage) {
    if (pError != nullptr) {
        *pError = pMessage;
    }
}

bool AddStatement(std::vector<GStatement> *pStatementList,
                  const GStatement &pStatement,
                  std::string *pError) {
    if (pStatementList == nullptr) {
        SetError(pError, "GTwistMix16 output statement list was null.");
        return false;
    }
    if (pStatement.IsInvalid()) {
        SetError(pError, "GTwistMix16 tried to emit an invalid statement.");
        return false;
    }
    pStatementList->push_back(pStatement);
    return true;
}

bool ResolveMix161Config(const Mix161Type pMixType,
                         Mix161Config *pConfig,
                         std::string *pError) {
    if (pConfig == nullptr) {
        SetError(pError, "GTwistMix16 config output was null.");
        return false;
    }

    const int aIndex = static_cast<int>(pMixType) - 1;
    if (aIndex < 0 || aIndex > 11) {
        SetError(pError, "GTwistMix16 mix type was outside the supported Mix161 range.");
        return false;
    }

    static const Mix161Config kConfigs[12] = {
        { true,  false, false, 3, false }, // 000
        { true,  false, false, 3, true  }, // 001
        { true,  false, false, 5, false }, // 002
        { true,  false, false, 5, true  }, // 003
        { true,  false, true,  3, false }, // 004
        { true,  false, true,  3, true  }, // 005
        { true,  false, true,  5, false }, // 006
        { true,  false, true,  5, true  }, // 007
        { false, true,  false, 3, false }, // 008
        { false, true,  false, 5, false }, // 009
        { false, true,  true,  3, false }, // 010
        { false, true,  true,  5, false }, // 011
    };

    *pConfig = kConfigs[aIndex];
    return true;
}

Mix161Type RandomMix161Type() {
    return static_cast<Mix161Type>(Random::Get(1, 12));
}

bool EmitMix161(GAssignType pAssignType,
                GSymbol pTarget,
                Mix161Type pMixType,
                const GExpr &pInputExpr,
                GSymbol pSBox,
                std::vector<GStatement> *pStatementList,
                std::string *pError) {
    if (pStatementList == nullptr) {
        SetError(pError, "GTwistMix16 output statement list was null.");
        return false;
    }

    if (!pTarget.IsVar()) {
        SetError(pError, "GTwistMix16 target must be a valid variable symbol.");
        return false;
    }

    if (!pSBox.IsBuf()) {
        SetError(pError, "GTwistMix16 S-box symbol must be a buffer symbol.");
        return false;
    }

    if (pInputExpr.IsInvalid()) {
        SetError(pError, "GTwistMix16 input expression was invalid.");
        return false;
    }

    Mix161Config aConfig;
    if (!ResolveMix161Config(pMixType, &aConfig, pError)) {
        return false;
    }

    const GExpr aMixExpr = GExpr::Mix161(pInputExpr, pMixType, pSBox);
    switch (pAssignType) {
        case GAssignType::kSet:
            return AddStatement(pStatementList,
                                GStatement::Assign(GTarget::Symbol(pTarget), aMixExpr),
                                pError);

        case GAssignType::kAddAssign:
            return AddStatement(pStatementList,
                                GStatement::AddAssign(GTarget::Symbol(pTarget), aMixExpr),
                                pError);

        case GAssignType::kXorAssign:
            return AddStatement(pStatementList,
                                GStatement::XorAssign(GTarget::Symbol(pTarget), aMixExpr),
                                pError);

        default:
            SetError(pError, "GTwistMix16 assign type was invalid.");
            return false;
    }
}

bool BakeComposerThenMix(GLoopFragmentComposer &pComposer,
                         GAssignType pMixAssignType,
                         Mix161Type pMixType,
                         GSymbol pSBox,
                         std::vector<GStatement> *pStatementList,
                         std::string *pError) {
    if (!pComposer.BakeStatements(pStatementList, pError)) {
        return false;
    }

    const GSymbol aTarget = pComposer.GetTarget();
    if (!aTarget.IsVar()) {
        SetError(pError, "GTwistMix16 composer target was invalid.");
        return false;
    }

    return EmitMix161(pMixAssignType,
                      aTarget,
                      pMixType,
                      GExpr::Symbol(aTarget),
                      pSBox,
                      pStatementList,
                      pError);
}

GSymbol DefaultSBoxSymbol() {
    return BufSymbol(TwistWorkSpaceSlot::kSBoxA);
}

} // namespace

bool GTwistMix16::Mix161SetEqual(GSymbol pSymbol,
                                 Mix161Type pMixType,
                                 const GExpr &pExpr,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return EmitMix161(GAssignType::kSet,
                      pSymbol,
                      pMixType,
                      pExpr,
                      pSBox,
                      pStatementList,
                      pError);
}

bool GTwistMix16::Mix161AddEqual(GSymbol pSymbol,
                                 Mix161Type pMixType,
                                 const GExpr &pExpr,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return EmitMix161(GAssignType::kAddAssign,
                      pSymbol,
                      pMixType,
                      pExpr,
                      pSBox,
                      pStatementList,
                      pError);
}

bool GTwistMix16::Mix161XorEqual(GSymbol pSymbol,
                                 Mix161Type pMixType,
                                 const GExpr &pExpr,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return EmitMix161(GAssignType::kXorAssign,
                      pSymbol,
                      pMixType,
                      pExpr,
                      pSBox,
                      pStatementList,
                      pError);
}

bool GTwistMix16::Mix161SetEqual(GSymbol pSymbol,
                                 const GExpr &pExpr,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161SetEqual(pSymbol,
                          RandomMix161Type(),
                          pExpr,
                          pSBox,
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161AddEqual(GSymbol pSymbol,
                                 const GExpr &pExpr,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161AddEqual(pSymbol,
                          RandomMix161Type(),
                          pExpr,
                          pSBox,
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161XorEqual(GSymbol pSymbol,
                                 const GExpr &pExpr,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161XorEqual(pSymbol,
                          RandomMix161Type(),
                          pExpr,
                          pSBox,
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161SetEqual(GLoopFragmentComposer &pComposer,
                                 Mix161Type pMixType,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return BakeComposerThenMix(pComposer,
                               GAssignType::kSet,
                               pMixType,
                               pSBox,
                               pStatementList,
                               pError);
}

bool GTwistMix16::Mix161AddEqual(GLoopFragmentComposer &pComposer,
                                 Mix161Type pMixType,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return BakeComposerThenMix(pComposer,
                               GAssignType::kAddAssign,
                               pMixType,
                               pSBox,
                               pStatementList,
                               pError);
}

bool GTwistMix16::Mix161XorEqual(GLoopFragmentComposer &pComposer,
                                 Mix161Type pMixType,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return BakeComposerThenMix(pComposer,
                               GAssignType::kXorAssign,
                               pMixType,
                               pSBox,
                               pStatementList,
                               pError);
}

bool GTwistMix16::Mix161SetEqual(GLoopFragmentComposer &pComposer,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161SetEqual(pComposer,
                          RandomMix161Type(),
                          pSBox,
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161AddEqual(GLoopFragmentComposer &pComposer,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161AddEqual(pComposer,
                          RandomMix161Type(),
                          pSBox,
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161XorEqual(GLoopFragmentComposer &pComposer,
                                 GSymbol pSBox,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161XorEqual(pComposer,
                          RandomMix161Type(),
                          pSBox,
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161SetEqual(GSymbol pSymbol,
                                 Mix161Type pMixType,
                                 const GExpr &pExpr,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161SetEqual(pSymbol,
                          pMixType,
                          pExpr,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161AddEqual(GSymbol pSymbol,
                                 Mix161Type pMixType,
                                 const GExpr &pExpr,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161AddEqual(pSymbol,
                          pMixType,
                          pExpr,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161XorEqual(GSymbol pSymbol,
                                 Mix161Type pMixType,
                                 const GExpr &pExpr,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161XorEqual(pSymbol,
                          pMixType,
                          pExpr,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161SetEqual(GSymbol pSymbol,
                                 const GExpr &pExpr,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161SetEqual(pSymbol,
                          pExpr,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161AddEqual(GSymbol pSymbol,
                                 const GExpr &pExpr,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161AddEqual(pSymbol,
                          pExpr,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161XorEqual(GSymbol pSymbol,
                                 const GExpr &pExpr,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161XorEqual(pSymbol,
                          pExpr,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161SetEqual(GLoopFragmentComposer &pComposer,
                                 Mix161Type pMixType,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161SetEqual(pComposer,
                          pMixType,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161AddEqual(GLoopFragmentComposer &pComposer,
                                 Mix161Type pMixType,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161AddEqual(pComposer,
                          pMixType,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161XorEqual(GLoopFragmentComposer &pComposer,
                                 Mix161Type pMixType,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161XorEqual(pComposer,
                          pMixType,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161SetEqual(GLoopFragmentComposer &pComposer,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161SetEqual(pComposer,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161AddEqual(GLoopFragmentComposer &pComposer,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161AddEqual(pComposer,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}

bool GTwistMix16::Mix161XorEqual(GLoopFragmentComposer &pComposer,
                                 std::vector<GStatement> *pStatementList,
                                 std::string *pError) {
    return Mix161XorEqual(pComposer,
                          DefaultSBoxSymbol(),
                          pStatementList,
                          pError);
}
