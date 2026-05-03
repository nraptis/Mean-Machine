//
//  GQuickStatement.cpp
//  MeanMachine
//
//  Created by Dragon on 5/1/26.
//

#include "GQuick.hpp"
#include "Random.hpp"

namespace {

int BufferLengthForSymbol(const GSymbol pBuffer) {
    const int aBufferLength = TwistWorkSpace::GetBufferLength(pBuffer.mSlot);
    if (aBufferLength > 0) {
        return aBufferLength;
    }
    return S_BLOCK;
}

std::uint32_t RandomOffsetForBuffer(const GSymbol pBuffer) {
    const int aBufferLength = BufferLengthForSymbol(pBuffer);
    return (aBufferLength > 1) ? static_cast<std::uint32_t>(Random::Get(aBufferLength)) : 0U;
}

GExpr ApplySignedOffset(const GExpr &pIndex,
                        const int pOffset) {
    if (pOffset < 0) {
        return GExpr::Sub(pIndex, GExpr::Const32(-pOffset));
    }
    return GExpr::Add(pIndex, GExpr::Const32(pOffset));
}

GExpr InvertedIndexExpr(const GSymbol pBuffer,
                        const GExpr &pIndex) {
    const int aCeiling = BufferLengthForSymbol(pBuffer) - 1;
    return GExpr::Sub(GExpr::Const32(aCeiling), pIndex);
}

GExpr BuildBufferReadExpr(const GSymbol pBuffer,
                          const GSymbol pIndex,
                          const int pOffset) {
    const GExpr aIndexExpr = ApplySignedOffset(GExpr::Symbol(pIndex), pOffset);
    return GQuick::MakeReadBufferReadExpression(pBuffer, aIndexExpr);
}

GExpr BuildBufferReadExprInverted(const GSymbol pBuffer,
                                  const GSymbol pIndex,
                                  const int pOffset) {
    const GExpr aInvertedIndexExpr = InvertedIndexExpr(pBuffer, GExpr::Symbol(pIndex));
    const GExpr aOffsetIndexExpr = ApplySignedOffset(aInvertedIndexExpr, pOffset);
    return GQuick::MakeReadBufferReadExpression(pBuffer, aOffsetIndexExpr);
}

GStatement BuildAssignToSymbol(const GSymbol pSymbol,
                               const GExpr &pExpression) {
    return GStatement::Assign(GTarget::Symbol(pSymbol), pExpression);
}

} // namespace

GExpr GQuick::MakeReadBufferOffsetExpression(const GSymbol pBuffer,
                                             const GSymbol pIndex,
                                             const std::uint32_t pOffset) {
    return MakeReadBufferOffsetExpression(pBuffer,
                                          GExpr::Symbol(pIndex),
                                          pOffset);
}

GExpr GQuick::MakeReadBufferOffsetExpression(const GSymbol pBuffer,
                                             const GSymbol pIndex) {
    return MakeReadBufferOffsetExpression(pBuffer,
                                          GExpr::Symbol(pIndex));
}

GExpr GQuick::MakeReadBufferOffsetExpressionInverted(const GSymbol pBuffer,
                                                     const GSymbol pIndex,
                                                     const std::uint32_t pOffset) {
    return MakeReadBufferOffsetExpressionInverted(pBuffer,
                                                  GExpr::Symbol(pIndex),
                                                  pOffset);
}

GExpr GQuick::MakeReadBufferOffsetExpressionInverted(const GSymbol pBuffer,
                                                     const GSymbol pIndex) {
    return MakeReadBufferOffsetExpressionInverted(pBuffer,
                                                  GExpr::Symbol(pIndex));
}

GExpr GQuick::MakeReadBufferOffsetExpression(const GSymbol pBuffer,
                                             GExpr pIndex,
                                             const std::uint32_t pOffset) {
    const GExpr aOffsetExpr = GExpr::Add(pIndex, GExpr::Const32(static_cast<int>(pOffset)));
    return GExpr::Read(pBuffer, aOffsetExpr);
}

GExpr GQuick::MakeReadBufferOffsetExpression(const GSymbol pBuffer,
                                             GExpr pIndex) {
    return MakeReadBufferOffsetExpression(pBuffer,
                                          pIndex,
                                          RandomOffsetForBuffer(pBuffer));
}

GExpr GQuick::MakeReadBufferOffsetExpressionInverted(const GSymbol pBuffer,
                                                     GExpr pIndex,
                                                     const std::uint32_t pOffset) {
    const GExpr aInvertedIndexExpr = InvertedIndexExpr(pBuffer, pIndex);
    const GExpr aOffsetIndexExpr = GExpr::Add(aInvertedIndexExpr,
                                              GExpr::Const32(static_cast<int>(pOffset)));
    return GExpr::Read(pBuffer, aOffsetIndexExpr);
}

GExpr GQuick::MakeReadBufferOffsetExpressionInverted(const GSymbol pBuffer,
                                                     GExpr pIndex) {
    return MakeReadBufferOffsetExpressionInverted(pBuffer,
                                                  pIndex,
                                                  RandomOffsetForBuffer(pBuffer));
}

GExpr GQuick::MakeReadBufferReadExpression(const GSymbol pBuffer,
                                           const GSymbol pIndex) {
    return MakeReadBufferReadExpression(pBuffer, GExpr::Symbol(pIndex));
}

GExpr GQuick::MakeReadBufferReadExpressionInverted(const GSymbol pBuffer,
                                                   const GSymbol pIndex) {
    return MakeReadBufferReadExpressionInverted(pBuffer, GExpr::Symbol(pIndex));
}

GExpr GQuick::MakeReadBufferReadExpression(const GSymbol pBuffer,
                                           GExpr pIndex) {
    return GExpr::Read(pBuffer, pIndex);
}

GExpr GQuick::MakeReadBufferReadExpressionInverted(const GSymbol pBuffer,
                                                   GExpr pIndex) {
    return GExpr::Read(pBuffer, InvertedIndexExpr(pBuffer, pIndex));
}

GStatement GQuick::MakeAssignVariableStatement(const GSymbol pTarget, const GExpr pExpr) {
    GTarget aTarget = GTarget::Symbol(pTarget);
    return GStatement::Assign(aTarget, pExpr);
}

GStatement GQuick::MakeAssignVariableStatement(const GSymbol pTarget, const GSymbol pValue) {
    
    GExpr aValueExpr = GExpr::Symbol(pValue);
    GTarget aTarget = GTarget::Symbol(pTarget);
    return GStatement::Assign(aTarget, aValueExpr);
}

GStatement GQuick::MakeAssignVariableStatement(const GSymbol pTarget, const GSymbol pBuffer, const GSymbol pIndex) {
    
    GTarget aDestTarget = GTarget::Symbol(pTarget);
    GExpr aIndexExpr = GExpr::Symbol(pIndex);
    GExpr aSourceIndexExpr = GExpr::Read(pBuffer, aIndexExpr);
    return GStatement::Assign(aDestTarget, aSourceIndexExpr);
    
}

GStatement GQuick::MakeAssignVariableStatementInverted(const GSymbol pTarget, const GSymbol pBuffer, const GSymbol pIndex) {
    int aBufferLength = TwistWorkSpace::GetBufferLength(pBuffer.mSlot);
    if (aBufferLength < 128) { aBufferLength = 128; }
    int aCeiling = aBufferLength - 1;
    GExpr aIndexExpr = GExpr::Sub(GExpr::Const32(aCeiling),
                                  GExpr(GExpr::Symbol(pIndex)));
    GExpr aValueExpr = GExpr::Read(pBuffer, aIndexExpr);
    GTarget aTarget = GTarget::Symbol(pTarget);
    return GStatement::Assign(aTarget, aValueExpr);
}

GStatement GQuick::MakeAssignDestStatement(const GSymbol pDest, const GSymbol pIndex, const GSymbol pValue) {
    GExpr aIndexExpr = GExpr::Symbol(pIndex);
    GExpr aValueExpr = GExpr::Symbol(pValue);
    GTarget aDestTarget = GTarget::Write(pDest, aIndexExpr);
    return GStatement::Assign(aDestTarget, aValueExpr);
}



GStatement GQuick::MakeAssignDestStatementInverted(const GSymbol pDest, const GSymbol pIndex, const GSymbol pValue) {
    
    int aBufferLength = TwistWorkSpace::GetBufferLength(pDest.mSlot);
    if (aBufferLength < 128) { aBufferLength = 128; }
    int aCeiling = aBufferLength - 1;
    GExpr aIndexExpr = GExpr::Sub(GExpr::Const32(aCeiling),
                                  GExpr(GExpr::Symbol(pIndex)));
    GExpr aValueExpr = GExpr::Symbol(pValue);
    GTarget aDestTarget = GTarget::Write(pDest, aIndexExpr);
    return GStatement::Assign(aDestTarget, aValueExpr);
    
}

GStatement GQuick::MakeAssignOffsetByteStatement(const GSymbol pTarget,
                                                 const GSymbol pSource,
                                                 const GSymbol pIndex,
                                                 const int pOffset) {
    GTarget aDestTarget = GTarget::Symbol(pTarget);
    GExpr aIndexPlusOffsetExpr = GExpr::Add(GExpr::Symbol(pIndex), GExpr::Const32(pOffset));
    GExpr aSourceIndexExpr = GExpr::Read(pSource, aIndexPlusOffsetExpr);
    return GStatement::Assign(aDestTarget, aSourceIndexExpr);
}


GStatement GQuick::MulEqual64(const GSymbol pSymbol, const std::uint64_t pAmount) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::Mul(GExpr::Symbol(pSymbol), GExpr::Const64(pAmount));
    return GStatement::Assign(aTarget, aExpr);
    
}

GStatement GQuick::DiffuseEqual(const GSymbol pSymbol) {
    return BuildAssignToSymbol(pSymbol, GExpr::Diffuse(GExpr::Symbol(pSymbol)));
}

GStatement GQuick::AddEqual64(const GSymbol pSymbol, const std::uint64_t pAmount) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::Add(GExpr::Symbol(pSymbol), GExpr::Const64(pAmount));
    return GStatement::Assign(aTarget, aExpr);
    
}

GStatement GQuick::XorEqual64(const GSymbol pSymbol, const std::uint64_t pAmount) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::Xor(GExpr::Symbol(pSymbol), GExpr::Const64(pAmount));
    return GStatement::Assign(aTarget, aExpr);
    
}

GStatement GQuick::ShiftRightEqual64(const GSymbol pSymbol, const std::uint64_t pAmount) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::ShiftR(GExpr::Symbol(pSymbol), GExpr::Const64(pAmount));
    return GStatement::Assign(aTarget, aExpr);
    
}

GStatement GQuick::ShiftLeftEqual64(const GSymbol pSymbol, const std::uint64_t pAmount) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::ShiftL(GExpr::Symbol(pSymbol), GExpr::Const64(pAmount));
    return GStatement::Assign(aTarget, aExpr);
}


GStatement GQuick::RotateLeftEqual64(const GSymbol pSymbol, const std::uint64_t pAmount) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::RotL64(GExpr::Symbol(pSymbol), GExpr::Const64(pAmount));
    return GStatement::Assign(aTarget, aExpr);
}


GStatement GQuick::MulEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::Mul(GExpr::Symbol(pSymbol), GExpr::Symbol(pOtherSymbol));
    return GStatement::Assign(aTarget, aExpr);
}

GStatement GQuick::AddEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::Add(GExpr::Symbol(pSymbol), GExpr::Symbol(pOtherSymbol));
    return GStatement::Assign(aTarget, aExpr);
}

GStatement GQuick::XorEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::Xor(GExpr::Symbol(pSymbol), GExpr::Symbol(pOtherSymbol));
    return GStatement::Assign(aTarget, aExpr);
}


GStatement GQuick::ShiftRightEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::ShiftR(GExpr::Symbol(pSymbol), GExpr::Symbol(pOtherSymbol));
    return GStatement::Assign(aTarget, aExpr);
}

GStatement GQuick::ShiftLeftEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::ShiftL(GExpr::Symbol(pSymbol), GExpr::Symbol(pOtherSymbol));
    return GStatement::Assign(aTarget, aExpr);
}


GStatement GQuick::RotateLeftEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    GExpr aExpr = GExpr::RotL64(GExpr::Symbol(pSymbol), GExpr::Symbol(pOtherSymbol));
    return GStatement::Assign(aTarget, aExpr);
}

GStatement GQuick::XorRotateLeftEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol, const int pAmount) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    const GExpr aRotatedExpr = GExpr::RotL64(GExpr::Symbol(pOtherSymbol), GExpr::Const64(pAmount));
    GExpr aExpr = GExpr::Xor(GExpr::Symbol(pSymbol), aRotatedExpr);
    return GStatement::Assign(aTarget, aExpr);
}

GStatement GQuick::AddRotateLeftEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol, const int pAmount) {
    GTarget aTarget = GTarget::Symbol(pSymbol);
    const GExpr aRotatedExpr = GExpr::RotL64(GExpr::Symbol(pOtherSymbol), GExpr::Const64(pAmount));
    GExpr aExpr = GExpr::Add(GExpr::Symbol(pSymbol), aRotatedExpr);
    return GStatement::Assign(aTarget, aExpr);
}

GStatement GQuick::MulEqualBuffer(const GSymbol pSymbol, const GSymbol pBuffer, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::Mul(GExpr::Symbol(pSymbol), BuildBufferReadExpr(pBuffer, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::AddEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::Add(GExpr::Symbol(pSymbol), BuildBufferReadExpr(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::XorEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::Xor(GExpr::Symbol(pSymbol), BuildBufferReadExpr(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::ShiftRightEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::ShiftR(GExpr::Symbol(pSymbol), BuildBufferReadExpr(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::ShiftLeftEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::ShiftL(GExpr::Symbol(pSymbol), BuildBufferReadExpr(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::RotateLeftEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::RotL64(GExpr::Symbol(pSymbol), BuildBufferReadExpr(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::MulEqualBufferInverted(const GSymbol pSymbol, const GSymbol pBuffer, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::Mul(GExpr::Symbol(pSymbol), BuildBufferReadExprInverted(pBuffer, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::AddEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::Add(GExpr::Symbol(pSymbol), BuildBufferReadExprInverted(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::XorEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::Xor(GExpr::Symbol(pSymbol), BuildBufferReadExprInverted(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::ShiftRightEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::ShiftR(GExpr::Symbol(pSymbol), BuildBufferReadExprInverted(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::ShiftLeftEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::ShiftL(GExpr::Symbol(pSymbol), BuildBufferReadExprInverted(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}

GStatement GQuick::RotateLeftEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset) {
    const GExpr aExpr = GExpr::RotL64(GExpr::Symbol(pSymbol), BuildBufferReadExprInverted(pOtherSymbol, pIndex, pOffset));
    return BuildAssignToSymbol(pSymbol, aExpr);
}
