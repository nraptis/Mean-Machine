//
//  GQuickStatement.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/1/26.
//

#ifndef GQuickStatement_hpp
#define GQuickStatement_hpp

#include "TwistWorkSpace.hpp"
#include "TwistFunctional.hpp"
#include "GSymbol.hpp"
#include "GSeedProgram.hpp"

class GQuick {
public:
    
    
    // the modulo is handled by GExpr::Read()
    //buffer[(index + offset) % size]
    static GExpr                                    MakeReadBufferOffsetExpression(GSymbol pBuffer, GSymbol pIndex, std::uint32_t pOffset);

    // the modulo is handled by GExpr::Read()
    //buffer[(index + rand_offset) % size]
    static GExpr                                    MakeReadBufferOffsetExpression(GSymbol pBuffer, GSymbol pIndex);

    // the modulo is handled by GExpr::Read()
    //buffer[(size - 1 - index + offset) % size]
    static GExpr                                    MakeReadBufferOffsetExpressionInverted(GSymbol pBuffer, GSymbol pIndex, std::uint32_t pOffset);

    // the modulo is handled by GExpr::Read()
    //buffer[(size - 1 - index + rand_offset) % size]
    static GExpr                                    MakeReadBufferOffsetExpressionInverted(GSymbol pBuffer, GSymbol pIndex);

    // the modulo is handled by GExpr::Read()
    //buffer[(index + offset) % size]
    static GExpr                                    MakeReadBufferOffsetExpression(GSymbol pBuffer, GExpr pIndex, std::uint32_t pOffset);

    // the modulo is handled by GExpr::Read()
    //buffer[(index + rand_offset) % size]
    static GExpr                                    MakeReadBufferOffsetExpression(GSymbol pBuffer, GExpr pIndex);

    // the modulo is handled by GExpr::Read()
    //buffer[(size - 1 - index + offset) % size]
    static GExpr                                    MakeReadBufferOffsetExpressionInverted(GSymbol pBuffer, GExpr pIndex, std::uint32_t pOffset);

    // the modulo is handled by GExpr::Read()
    //buffer[(size - 1 - index + rand_offset) % size]
    static GExpr                                    MakeReadBufferOffsetExpressionInverted(GSymbol pBuffer, GExpr pIndex);


    // the modulo is handled by GExpr::Read()
    //buffer[(index) % size]
    static GExpr                                    MakeReadBufferReadExpression(GSymbol pBuffer, GSymbol pIndex);

    // the modulo is handled by GExpr::Read()
    //buffer[(size - 1 - index) % size]
    static GExpr                                    MakeReadBufferReadExpressionInverted(GSymbol pBuffer, GSymbol pIndex);

    // the modulo is handled by GExpr::Read()
    //buffer[(index) % size]
    static GExpr                                    MakeReadBufferReadExpression(GSymbol pBuffer, GExpr pIndex);

    // the modulo is handled by GExpr::Read()
    //buffer[(size - 1 - index) % size]
    static GExpr                                    MakeReadBufferReadExpressionInverted(GSymbol pBuffer, GExpr pIndex);
    
    
    
    
    
    
    static GStatement                               MakeAssignVariableStatement(const GSymbol pTarget, const GExpr pExpr);
    static GStatement                               MakeAssignVariableStatement(const GSymbol pTarget, const GSymbol pValue);
    
    
    static GStatement                               MakeAssignVariableStatement(const GExpr pTargetExpr, const GExpr pExpr);
    static GStatement                               MakeAssignVariableStatement(const GExpr pTargetExpr, const GSymbol pValue);
    
    
    
    static GStatement                               MakeAssignVariableStatement(const GSymbol pTarget, const GSymbol pBuffer, const GSymbol pIndex);
    static GStatement                               MakeAssignVariableStatementInverted(const GSymbol pTarget, const GSymbol pBuffer, const GSymbol pIndex);
    
    static GStatement                               MakeAssignDestStatement(const GSymbol pDest, const GSymbol pIndex, const GSymbol pValue);
    static GStatement                               MakeAssignDestStatementInverted(const GSymbol pDest, const GSymbol pIndex, const GSymbol pValue);
    
    static GStatement                               MakeAssignOffsetByteStatement(const GSymbol pTarget, const GSymbol pSource,
                                                                                  const GSymbol pIndex, const int pOffset);
    
    
    static GStatement                               DiffuseAEqual(const GSymbol pSymbol);
    static GStatement                               DiffuseBEqual(const GSymbol pSymbol);
    static GStatement                               DiffuseCEqual(const GSymbol pSymbol);
    static GStatement                               MulEqual64(const GSymbol pSymbol, const std::uint64_t pAmount);
    static GStatement                               AddEqual64(const GSymbol pSymbol, const std::uint64_t pAmount);
    static GStatement                               XorEqual64(const GSymbol pSymbol, const std::uint64_t pAmount);
    static GStatement                               ShiftRightEqual64(const GSymbol pSymbol, const std::uint64_t pAmount);
    static GStatement                               ShiftLeftEqual64(const GSymbol pSymbol, const std::uint64_t pAmount);
    static GStatement                               RotateLeftEqual64(const GSymbol pSymbol, const std::uint64_t pAmount);
    
    static GStatement                               MulEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol);
    static GStatement                               AddEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol);
    static GStatement                               XorEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol);
    static GStatement                               ShiftRightEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol);
    static GStatement                               ShiftLeftEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol);
    static GStatement                               RotateLeftEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol);
    static GStatement                               XorRotateLeftEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol, const int pAmount);
    static GStatement                               AddRotateLeftEqualVariable(const GSymbol pSymbol, const GSymbol pOtherSymbol, const int pAmount);
    
    
    
    // symbol *= buffer[index + offset]
    static GStatement                               MulEqualBuffer(const GSymbol pSymbol, const GSymbol pBuffer, const GSymbol pIndex, const int pOffset);
    static GStatement                               AddEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);
    static GStatement                               XorEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);
    static GStatement                               ShiftRightEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);
    static GStatement                               ShiftLeftEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);
    static GStatement                               RotateLeftEqualBuffer(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);


    // symbol *= buffer[buffer_size - 1 - index + offset]
    static GStatement                               MulEqualBufferInverted(const GSymbol pSymbol, const GSymbol pBuffer, const GSymbol pIndex, const int pOffset);
    static GStatement                               AddEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);
    static GStatement                               XorEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);
    static GStatement                               ShiftRightEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);
    static GStatement                               ShiftLeftEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);
    static GStatement                               RotateLeftEqualBufferInverted(const GSymbol pSymbol, const GSymbol pOtherSymbol, const GSymbol pIndex, const int pOffset);
    
    static GExpr                                    RotL64(const GExpr &pExpr, int pRotation);
    static GExpr                                    RotL64(const GSymbol &pSymbol, int pRotation);
    
    static GExpr                                    MulConstRotL64(const GSymbol &pSymbol, std::uint64_t pMul, int pRotation);
    
    static GExpr                                    AddChain(const std::vector<GExpr> &pExprs);
    static GExpr                                    XorChain(const std::vector<GExpr> &pExprs);
    
    static GExpr                                    MakeReadBufferOffsetExpressionDirected(const GSymbol pBuffer,
                                                        const GSymbol pIndex,
                                                        bool pInverted,
                                                        std::uint32_t pOffset);

    static GExpr                                    MakeReadBufferOffsetExpressionDirected(const GSymbol pBuffer,
                                                        GExpr pIndex,
                                                        bool pInverted,
                                                        std::uint32_t pOffset);
    
    static GStatement                               MakeAssignDestStatement(const GSymbol pDest,
                                              const GSymbol pIndex,
                                              const GExpr pValue);

    static GStatement                               MakeAssignDestStatementInverted(const GSymbol pDest,
                                                      const GSymbol pIndex,
                                                      const GExpr pValue);
    
};

#endif /* GQuickStatement_hpp */
