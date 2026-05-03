//
//  CSPRNG.cpp
//  MeanMachine
//
//  Created by Dragon on 5/2/26.
//

#include "CSPRNG.hpp"
#include "GSelect.hpp"
#include "TwistArray.hpp"

bool CSPRNG::Bake(bool pWriteReversed,
                  int pFamilyIndex,
                  
                  GSymbol pDest,
                  GSymbol pLoopIndex,
                  
                  GSymbol pFreshByte,
                  
                  GSymbol pValue,
                  GSymbol pValuePrevious,
                  GSymbol pValueMix,
                  
                  GSymbol pSecureByteA,
                  GSymbol pSecureByteB,
                  
                  GSymbol pCross,
                  
                  GSymbol pSelect,
                  
                  GSymbol pCarry,
                  
                  GSymbol pHalfA,
                  GSymbol pHalfB,
                  
                  GSymbol pFixedSaltA,
                  GSymbol pFixedSaltB,
                  GSymbol pFixedSaltC,
                  GSymbol pFixedSaltD,
                  
                  
                  GSymbol pScratchSaltA,
                  GSymbol pScratchSaltB,
                  GSymbol pScratchSaltC,
                  GSymbol pScratchSaltD,
                  
                  GSymbol pSBoxA,
                  GSymbol pSBoxB,
                  GSymbol pSBoxC,
                  GSymbol pSBoxD,
                  
                  GSymbol pWandererA,
                  GSymbol pWandererB,
                  GSymbol pWandererC,
                  
                  GSymbol pOrbiterA,
                  GSymbol pOrbiterB,
                  GSymbol pOrbiterC,
                  GSymbol pOrbiterD,
                  
                  Mix64Type_4 pMixTypeA,
                  Mix64Type_4 pMixTypeB,
                  Mix64Type_4 pMixTypeC,
                  Mix64Type_4 pMixTypeD,
                  
                  GRotationFamily &pRotationFamily,
                  GHotPack pHotPack,
                  
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) {
    
    auto PopRandomScratchSalt = [&]() -> GSymbol {
        std::vector<GSymbol> aSalts;

        if (pScratchSaltA.IsInvalid() == false) { aSalts.push_back(pScratchSaltA); }
        if (pScratchSaltB.IsInvalid() == false) { aSalts.push_back(pScratchSaltB); }
        if (pScratchSaltC.IsInvalid() == false) { aSalts.push_back(pScratchSaltC); }
        if (pScratchSaltD.IsInvalid() == false) { aSalts.push_back(pScratchSaltD); }

        if (aSalts.empty()) {
            return GSymbol();
        }

        return aSalts[Random::Get(static_cast<int>(aSalts.size()))];
    };
    
    
    const int cRotationDepth = 4;
    int aRotationSmallIndex = 0;
    auto PopSmallRotation = [&]() -> int {
        const int aRotation =
        pRotationFamily.mLow[pFamilyIndex][aRotationSmallIndex];
        aRotationSmallIndex += 1;
        if (aRotationSmallIndex >= cRotationDepth) {
            aRotationSmallIndex = 0;
        }
        return aRotation;
    };
    
    int aRotationHealthyIndex = 0;
    auto PopHealthyRotation = [&]() -> int {
        const int aRotation =
        pRotationFamily.mHealthy[pFamilyIndex][aRotationHealthyIndex];
        aRotationHealthyIndex += 1;
        if (aRotationHealthyIndex >= cRotationDepth) {
            aRotationHealthyIndex = 0;
        }
        return aRotation;
    };
    
    int aRotationMediumIndex = 0;
    auto PopMediumRotation = [&]() -> int {
        const int aRotation =
        pRotationFamily.mMedium[pFamilyIndex][aRotationMediumIndex];
        aRotationMediumIndex += 1;
        if (aRotationMediumIndex >= cRotationDepth) {
            aRotationMediumIndex = 0;
        }
        return aRotation;
    };
    
    int aRotationLargeIndex = 0;
        auto PopLargeRotation = [&]() -> int {
            const int aRotation =
            pRotationFamily.mHigh[pFamilyIndex][aRotationLargeIndex];
            aRotationLargeIndex += 1;
            if (aRotationLargeIndex >= cRotationDepth) {
                aRotationLargeIndex = 0;
            }
            return aRotation;
        };
    
    std::vector<GStatement> aTempStatements;
    GStatement aStatement;

    
    {
        pStatements->push_back(GStatement::Comment("a = s0 + e + hot0.add;"));
        GExpr aExprPrevious;
        int aWhich = Random::Get(3);
        if (aWhich == 0) {
            aExprPrevious = GExpr::RotL64(GExpr::Symbol(pFreshByte), GExpr::Const64(PopHealthyRotation()));
        } else if (aWhich == 1) {
            aExprPrevious = GExpr::RotL64(GExpr::Symbol(pFreshByte), GExpr::Const64(PopSmallRotation()));
        } else {
            aExprPrevious = GExpr::RotL64(GExpr::Symbol(pFreshByte), GExpr::Const64(PopMediumRotation()));
        }
        GExpr aExprLeft = GExpr::Add(GExpr::Symbol(pWandererA), aExprPrevious);
        GExpr aAddExpr = GExpr::Add(aExprLeft, GExpr::Const64(pHotPack.mPair[0].mAdd));
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterA, aAddExpr));
    }

    {
        pStatements->push_back(GStatement::Comment("b = s1 ^ previous ^ hot1.add;"));
        GExpr aExprPrevious;
        int aWhich = Random::Get(3);
        if (aWhich == 0) {
            aExprPrevious = GExpr::RotL64(GExpr::Symbol(pValuePrevious), GExpr::Const64(PopMediumRotation()));
        } else if (aWhich == 1) {
            aExprPrevious = GExpr::RotL64(GExpr::Symbol(pValuePrevious), GExpr::Const64(PopLargeRotation()));
        } else {
            aExprPrevious = GExpr::RotL64(GExpr::Symbol(pValuePrevious), GExpr::Const64(PopHealthyRotation()));
        }
        GExpr aExprLeft = GExpr::Xor(GExpr::Symbol(pWandererB), aExprPrevious);
        GExpr aXorExpr = GExpr::Xor(aExprLeft, GExpr::Const64(pHotPack.mPair[1].mAdd));
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterB, aXorExpr));
    }

    {
        pStatements->push_back(GStatement::Comment("c = s2 + cross + fixedSaltA + scratchSaltA;"));
        
        
        int aSaltInversionScheme = Random::Get(2);
        GExpr aFixedSaltExpr;
        GExpr aScratchSaltExpr;
        if (aSaltInversionScheme == 0) {
            aFixedSaltExpr = GQuick::MakeReadBufferOffsetExpression(pFixedSaltA, pLoopIndex);
            aScratchSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(pScratchSaltA, pLoopIndex);
        } else {
            aFixedSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(pFixedSaltA, pLoopIndex);
            aScratchSaltExpr = GQuick::MakeReadBufferOffsetExpression(pScratchSaltA, pLoopIndex);
        }
        
        GExpr aExprCross;
        int aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprCross = GExpr::RotL64(GExpr::Symbol(pCross), GExpr::Const64(PopMediumRotation()));
        } else if (aWhich == 1) {
            aExprCross = GExpr::RotL64(GExpr::Symbol(pCross), GExpr::Const64(PopLargeRotation()));
        } else if (aWhich == 2) {
            aExprCross = GExpr::RotL64(GExpr::Symbol(pCross), GExpr::Const64(PopLargeRotation()));
        } else {
            aExprCross = GExpr::RotL64(GExpr::Symbol(pCross), GExpr::Const64(PopHealthyRotation()));
        }
        GExpr aExprLeftLeft = GExpr::Add(GExpr::Symbol(pWandererC), aExprCross);
        GExpr aExprLeft = GExpr::Add(aExprLeftLeft, aFixedSaltExpr);
        GExpr aAddExpr = GExpr::Add(aExprLeft, aScratchSaltExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterC, aAddExpr));
    }


    {
        pStatements->push_back(GStatement::Comment("d = carry ^ fixedSaltB ^ scratchSaltB ^ RotL64(e, r0);"));
        
        int aSaltInversionScheme = Random::Get(2);
        GExpr aFixedSaltExpr;
        GExpr aScratchSaltExpr;
        if (aSaltInversionScheme == 0) {
            aFixedSaltExpr = GQuick::MakeReadBufferOffsetExpression(pFixedSaltB, pLoopIndex);
            aScratchSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(pScratchSaltB, pLoopIndex);
        } else {
            aFixedSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(pFixedSaltB, pLoopIndex);
            aScratchSaltExpr = GQuick::MakeReadBufferOffsetExpression(pScratchSaltB, pLoopIndex);
        }
        
        GExpr aExprPrevious;
        int aWhich = Random::Get(2);
        if (aWhich == 0) {
            aExprPrevious = GExpr::RotL64(GExpr::Symbol(pFreshByte), GExpr::Const64(PopMediumRotation()));
        } else {
            aExprPrevious = GExpr::RotL64(GExpr::Symbol(pFreshByte), GExpr::Const64(PopHealthyRotation()));
        }
        GExpr aExprCarry;
        aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprCarry = GExpr::RotL64(GExpr::Symbol(pCarry), GExpr::Const64(PopMediumRotation()));
        } else if (aWhich == 1) {
            aExprCarry = GExpr::RotL64(GExpr::Symbol(pCarry), GExpr::Const64(PopLargeRotation()));
        } else if (aWhich == 2) {
            aExprCarry = GExpr::RotL64(GExpr::Symbol(pCarry), GExpr::Const64(PopLargeRotation()));
        } else {
            aExprCarry = GExpr::RotL64(GExpr::Symbol(pCarry), GExpr::Const64(PopHealthyRotation()));
        }
        
        GExpr aExprLeftLeft = GExpr::Xor(aExprCarry, aExprPrevious);
        GExpr aExprLeft = GExpr::Xor(aExprLeftLeft, aFixedSaltExpr);
        
        GExpr aXorExpr = GExpr::Xor(aExprLeft, aScratchSaltExpr);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aXorExpr));
    }
    
    {
        pStatements->push_back(GStatement::Comment("a += b;"));
        pStatements->push_back(GStatement::Comment("d ^= a;"));
        pStatements->push_back(GStatement::Comment("d = RotL64(d, r1);"));
        
        
        int aConstantPlan = Random::Get(3);
        
        int aSaltPlan = Random::Get(2);
        int aSaltIndex = Random::Get(2);
        GSymbol aSalt = PopRandomScratchSalt();
        
        int aCrazySalt = Random::Get(8);
        GExpr aSaltKeyExpr;
        if (aCrazySalt == 0) {
            aSaltKeyExpr = GExpr::Add(pCarry, pSecureByteA);
        } else if (aCrazySalt == 1) {
            aSaltKeyExpr = GExpr::Add(pCarry, pSecureByteB);
        } else if (aCrazySalt == 2) {
            aSaltKeyExpr = GExpr::Xor(pCarry, pSecureByteA);
        } else if (aCrazySalt == 3) {
            aSaltKeyExpr = GExpr::Xor(pCarry, pSecureByteB);
        } else if (aCrazySalt == 4) {
            aSaltKeyExpr = GExpr::Add(pValuePrevious, pSecureByteA);
        } else if (aCrazySalt == 5) {
            aSaltKeyExpr = GExpr::Add(pValuePrevious, pSecureByteB);
        } else if (aCrazySalt == 6) {
            aSaltKeyExpr = GExpr::Xor(pValuePrevious, pSecureByteA);
        } else {
            aSaltKeyExpr = GExpr::Xor(pValuePrevious, pSecureByteB);
        }
        
        GExpr aSaltExpr = GQuick::MakeReadBufferOffsetExpression(aSalt, aSaltKeyExpr);
        
        // Try to fix these down:
        GExpr aExprOrbitA;
        GExpr aExprOrbitRight;
        if (aConstantPlan == 0) {
            if (aSaltPlan == 0) {
                aExprOrbitRight = GExpr::Add(pOrbiterB, GExpr::Add(aSaltExpr, pHotPack.mPair[2].mAdd));
            } else {
                aExprOrbitRight = GExpr::Add(pOrbiterB, GExpr::Const64(pHotPack.mPair[2].mAdd));
            }
        } else {
            if (aSaltPlan == 0) {
                aExprOrbitRight = GExpr::Add(pOrbiterB, aSaltExpr);
            } else {
                aExprOrbitRight = GExpr::Symbol(pOrbiterB);
            }
        }
        aExprOrbitA = GExpr::Add(pOrbiterA, aExprOrbitRight);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterA, aExprOrbitA));
        
        
        
        GExpr aExprOrbitD;

        if (aConstantPlan == 1) {
            if (aSaltPlan == 1) {
                aExprOrbitRight = GExpr::Xor(pOrbiterA, GExpr::Xor(aSaltExpr, GExpr::Const64(pHotPack.mPair[2].mAdd)));
            } else {
                aExprOrbitRight = GExpr::Xor(pOrbiterA, GExpr::Const64(pHotPack.mPair[2].mAdd));
            }
        } else {
            if (aSaltPlan == 1) {
                aExprOrbitRight = GExpr::Xor(pOrbiterA, aSaltExpr);
            } else {
                aExprOrbitRight = GExpr::Symbol(pOrbiterA);
            }
        }

        aExprOrbitD = GExpr::Xor(pOrbiterD, aExprOrbitRight);

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD)
        );
        

        int aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprOrbitD = GExpr::RotL64(GExpr::Symbol(pOrbiterD), GExpr::Const64(PopMediumRotation()));
        } else if (aWhich == 1) {
            aExprOrbitD = GExpr::RotL64(GExpr::Symbol(pOrbiterD), GExpr::Const64(PopLargeRotation()));
        } else if (aWhich == 2) {
            aExprOrbitD = GExpr::RotL64(GExpr::Symbol(pOrbiterD), GExpr::Const64(PopLargeRotation()));
        } else {
            aExprOrbitD = GExpr::RotL64(GExpr::Symbol(pOrbiterD), GExpr::Const64(PopHealthyRotation()));
        }

        pStatements->push_back(GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD));
    }
    
    {
        pStatements->push_back(GStatement::Comment("c += d;"));
        pStatements->push_back(GStatement::Comment("b ^= c;"));
        pStatements->push_back(GStatement::Comment("b = RotL64(b, r2);"));
        
        
        int aConstantPlan = Random::Get(3);
        
        int aSaltPlan = Random::Get(2);
        int aSaltIndex = Random::Get(2);
        GSymbol aSalt = PopRandomScratchSalt();
        
        //
        // Different salt key family for this leg.
        // Instead of carry / valuePrevious, use current value / cross / secure bytes.
        //
        int aCrazySalt = Random::Get(8);
        GExpr aSaltKeyExpr;
        if (aCrazySalt == 0) {
            aSaltKeyExpr = GExpr::Add(pValue, pSecureByteA);
        } else if (aCrazySalt == 1) {
            aSaltKeyExpr = GExpr::Add(pValue, pSecureByteB);
        } else if (aCrazySalt == 2) {
            aSaltKeyExpr = GExpr::Xor(pValue, pSecureByteA);
        } else if (aCrazySalt == 3) {
            aSaltKeyExpr = GExpr::Xor(pValue, pSecureByteB);
        } else if (aCrazySalt == 4) {
            aSaltKeyExpr = GExpr::Add(pCross, pSecureByteA);
        } else if (aCrazySalt == 5) {
            aSaltKeyExpr = GExpr::Add(pCross, pSecureByteB);
        } else if (aCrazySalt == 6) {
            aSaltKeyExpr = GExpr::Xor(pCross, pSecureByteA);
        } else {
            aSaltKeyExpr = GExpr::Xor(pCross, pSecureByteB);
        }
        
        GExpr aSaltExpr = GQuick::MakeReadBufferOffsetExpression(aSalt, aSaltKeyExpr);
        
        //
        // c += d;
        //
        GExpr aExprOrbitC;
        GExpr aExprOrbitRight;
        
        if (aConstantPlan == 0) {
            if (aSaltPlan == 0) {
                aExprOrbitRight = GExpr::Add(
                    pOrbiterD,
                    GExpr::Add(aSaltExpr, GExpr::Const64(pHotPack.mPair[3].mAdd))
                );
            } else {
                aExprOrbitRight = GExpr::Add(
                    pOrbiterD,
                    GExpr::Const64(pHotPack.mPair[3].mAdd)
                );
            }
        } else {
            if (aSaltPlan == 0) {
                aExprOrbitRight = GExpr::Add(pOrbiterD, aSaltExpr);
            } else {
                aExprOrbitRight = GExpr::Symbol(pOrbiterD);
            }
        }
        
        aExprOrbitC = GExpr::Add(pOrbiterC, aExprOrbitRight);
        
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterC, aExprOrbitC)
        );
        
        
        //
        // b ^= c;
        //
        GExpr aExprOrbitB;
        
        if (aConstantPlan == 1) {
            if (aSaltPlan == 1) {
                aExprOrbitRight = GExpr::Xor(
                    pOrbiterC,
                    GExpr::Xor(aSaltExpr, GExpr::Const64(pHotPack.mPair[3].mAdd))
                );
            } else {
                aExprOrbitRight = GExpr::Xor(
                    pOrbiterC,
                    GExpr::Const64(pHotPack.mPair[3].mAdd)
                );
            }
        } else {
            if (aSaltPlan == 1) {
                aExprOrbitRight = GExpr::Xor(pOrbiterC, aSaltExpr);
            } else {
                aExprOrbitRight = GExpr::Symbol(pOrbiterC);
            }
        }
        
        aExprOrbitB = GExpr::Xor(pOrbiterB, aExprOrbitRight);
        
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB)
        );
        
        
        //
        // b = RotL64(b, r2);
        //
        int aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprOrbitB = GExpr::RotL64(
                GExpr::Symbol(pOrbiterB),
                GExpr::Const64(PopMediumRotation())
            );
        } else if (aWhich == 1) {
            aExprOrbitB = GExpr::RotL64(
                GExpr::Symbol(pOrbiterB),
                GExpr::Const64(PopLargeRotation())
            );
        } else if (aWhich == 2) {
            aExprOrbitB = GExpr::RotL64(
                GExpr::Symbol(pOrbiterB),
                GExpr::Const64(PopLargeRotation())
            );
        } else {
            aExprOrbitB = GExpr::RotL64(
                GExpr::Symbol(pOrbiterB),
                GExpr::Const64(PopHealthyRotation())
            );
        }
        
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB)
        );
    }
    
    
    {
        pStatements->push_back(GStatement::Comment("a += b + hot4.add;"));
        pStatements->push_back(GStatement::Comment("d ^= a;"));
        pStatements->push_back(GStatement::Comment("d *= hot4.mul;"));
        pStatements->push_back(GStatement::Comment("d = RotL64(d, r3);"));

        //
        // a += b + hot3.add;
        //
        GExpr aExprOrbitA = GExpr::Add(
            pOrbiterA,
            GExpr::Add(
                pOrbiterB,
                GExpr::Const64(pHotPack.mPair[4].mAdd)
            )
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterA, aExprOrbitA)
        );

        //
        // d ^= a;
        //
        GExpr aExprOrbitD = GExpr::Xor(
            pOrbiterD,
            pOrbiterA
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD)
        );

        //
        // d *= hot3.mul;
        //
        aExprOrbitD = GExpr::Mul(
            pOrbiterD,
            GExpr::Const64(pHotPack.mPair[4].mMul)
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD)
        );

        //
        // d = RotL64(d, r3);
        //
        int aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprOrbitD = GExpr::RotL64(
                pOrbiterD,
                GExpr::Const64(PopMediumRotation())
            );
        } else if (aWhich == 1) {
            aExprOrbitD = GExpr::RotL64(
                pOrbiterD,
                GExpr::Const64(PopLargeRotation())
            );
        } else if (aWhich == 2) {
            aExprOrbitD = GExpr::RotL64(
                pOrbiterD,
                GExpr::Const64(PopLargeRotation())
            );
        } else {
            aExprOrbitD = GExpr::RotL64(
                pOrbiterD,
                GExpr::Const64(PopHealthyRotation())
            );
        }

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterD, aExprOrbitD)
        );
    }
    
    
    {
        pStatements->push_back(GStatement::Comment("c += d + hot4.add;"));
        pStatements->push_back(GStatement::Comment("b ^= c;"));
        pStatements->push_back(GStatement::Comment("b *= hot4.mul;"));
        pStatements->push_back(GStatement::Comment("b = RotL64(b, r4);"));

        //
        // c += d + hot3.add;
        //
        GExpr aExprOrbitC = GExpr::Add(
            pOrbiterC,
            GExpr::Add(
                pOrbiterD,
                GExpr::Const64(pHotPack.mPair[5].mAdd)
            )
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterC, aExprOrbitC)
        );

        //
        // b ^= c;
        //
        GExpr aExprOrbitB = GExpr::Xor(
            pOrbiterB,
            pOrbiterC
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB)
        );

        //
        // b *= hot3.mul;
        //
        aExprOrbitB = GExpr::Mul(
            pOrbiterB,
            GExpr::Const64(pHotPack.mPair[5].mMul)
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB)
        );

        //
        // b = RotL64(b, r4);
        //
        int aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprOrbitB = GExpr::RotL64(
                pOrbiterB,
                GExpr::Const64(PopMediumRotation())
            );
        } else if (aWhich == 1) {
            aExprOrbitB = GExpr::RotL64(
                pOrbiterB,
                GExpr::Const64(PopLargeRotation())
            );
        } else if (aWhich == 2) {
            aExprOrbitB = GExpr::RotL64(
                pOrbiterB,
                GExpr::Const64(PopLargeRotation())
            );
        } else {
            aExprOrbitB = GExpr::RotL64(
                pOrbiterB,
                GExpr::Const64(PopHealthyRotation())
            );
        }

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pOrbiterB, aExprOrbitB)
        );
    }
    
    

    {
        GSymbol aMainUpdateComponentA; GSymbol aMainUpdateComponentB; GSymbol aMainUpdateComponentC; GSymbol aMainUpdateComponentD;
        if (Random::Bool()) {
            aMainUpdateComponentA = pOrbiterA;
            aMainUpdateComponentB = pOrbiterB;
            aMainUpdateComponentC = pOrbiterC;
            aMainUpdateComponentD = pOrbiterD;
        } else {
            aMainUpdateComponentA = pOrbiterA;
            aMainUpdateComponentB = pOrbiterD;
            aMainUpdateComponentC = pOrbiterB;
            aMainUpdateComponentD = pOrbiterC;
        }
        GExpr aMainUpdateExprA = GExpr::Symbol(aMainUpdateComponentA);
        GExpr aMainUpdateExprB = GExpr::Symbol(aMainUpdateComponentB);
        GExpr aMainUpdateExprC = GExpr::Symbol(aMainUpdateComponentC);
        GExpr aMainUpdateExprD = GExpr::Symbol(aMainUpdateComponentD);
        if (Random::Bool()) {
            aMainUpdateExprA = GExpr::RotL64(GExpr::Symbol(aMainUpdateComponentA), GExpr::Const64(PopMediumRotation()));
        } else {
            aMainUpdateExprB = GExpr::RotL64(GExpr::Symbol(aMainUpdateComponentB), GExpr::Const64(PopMediumRotation()));
        }
        if (Random::Bool()) {
            aMainUpdateExprC = GExpr::RotL64(GExpr::Symbol(aMainUpdateComponentC), GExpr::Const64(PopMediumRotation()));
        } else {
            aMainUpdateExprD = GExpr::RotL64(GExpr::Symbol(aMainUpdateComponentD), GExpr::Const64(PopMediumRotation()));
        }
        
        pStatements->push_back(GStatement::Comment("Chain up \"p\" main combine expression"));
        GExpr aMainUpdateExprHalfA = GExpr::Xor(aMainUpdateExprA, aMainUpdateExprB);
        GExpr aMainUpdateExprHalfB = GExpr::Xor(aMainUpdateExprC, aMainUpdateExprD);
        GExpr aMainUpdateExpr = GExpr::Add(aMainUpdateExprHalfA, aMainUpdateExprHalfB);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pFreshByte, aMainUpdateExpr));
        
        
        
        
        GExpr aMainSnowPartA;
        GExpr aMainSnowPartB;
        GExpr aMainSnowPartC;
        int aWhichMainSnow = Random::Get(2);
        if (aWhichMainSnow == 0) {
            aMainSnowPartA = GExpr::ShiftL(GExpr::Symbol(pSecureByteA), GExpr::Const64(32));
            aMainSnowPartB = GExpr::Symbol(pSecureByteB);
            aMainSnowPartC = GExpr::RotL64(GExpr::Symbol(pValuePrevious), GExpr::Const64(PopMediumRotation()));
        } else {
            aMainSnowPartA = GExpr::Symbol(pSecureByteA);
            aMainSnowPartB = GExpr::ShiftL(GExpr::Symbol(pSecureByteB), GExpr::Const64(32));
            aMainSnowPartC = GExpr::RotL64(GExpr::Symbol(pValuePrevious), GExpr::Const64(PopMediumRotation()));
        }
        GExpr aMainSnowGuts = GExpr::Xor(aMainSnowPartA, GExpr::Xor(aMainSnowPartB, aMainSnowPartC));
        GExpr aMainSnow = GExpr::Diffuse(aMainSnowGuts);
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pValueMix, aMainSnow));
        
        pStatements->push_back(GStatement::Comment("Push \"p\" through secure byte diffusion word"));
        if (Random::Bool()) {
            aMainUpdateExpr = GExpr::Xor(GExpr::Symbol(pFreshByte), GExpr::Symbol(pValueMix));
        } else {
            aMainUpdateExpr = GExpr::Add(GExpr::Symbol(pFreshByte), GExpr::Symbol(pValueMix));
        }
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pFreshByte, aMainUpdateExpr));
        
        
        pStatements->push_back(GQuick::DiffuseEqual(pFreshByte));
    }
    
    
    
    if (pWriteReversed) {
        pStatements->push_back(GQuick::MakeAssignDestStatementInverted(pDest, pLoopIndex, pFreshByte));
    } else {
        pStatements->push_back(GQuick::MakeAssignDestStatement(pDest, pLoopIndex, pFreshByte));
    }
    
    pStatements->push_back(GStatement::Comment("Pass \"p\" through prismatic gate"));
    GExpr aMixOptionA = GExpr::Mix64_4(GExpr::Symbol(pFreshByte), pMixTypeA, (std::uint64_t)PopHealthyRotation(), pSBoxA, pSBoxB, pSBoxC, pSBoxD);
    GExpr aMixOptionB = GExpr::Mix64_4(GExpr::Symbol(pFreshByte), pMixTypeB, (std::uint64_t)PopHealthyRotation(), pSBoxA, pSBoxB, pSBoxC, pSBoxD);
    GExpr aMixOptionC = GExpr::Mix64_4(GExpr::Symbol(pFreshByte), pMixTypeC, (std::uint64_t)PopHealthyRotation(), pSBoxA, pSBoxB, pSBoxC, pSBoxD);
    GExpr aMixOptionD = GExpr::Mix64_4(GExpr::Symbol(pFreshByte), pMixTypeD, (std::uint64_t)PopHealthyRotation(), pSBoxA, pSBoxB, pSBoxC, pSBoxD);
    GStatement aMixStatementA = GQuick::MakeAssignVariableStatement(pFreshByte, aMixOptionA);
    GStatement aMixStatementB = GQuick::MakeAssignVariableStatement(pFreshByte, aMixOptionB);
    GStatement aMixStatementC = GQuick::MakeAssignVariableStatement(pFreshByte, aMixOptionC);
    GStatement aMixStatementD = GQuick::MakeAssignVariableStatement(pFreshByte, aMixOptionD);
    
    
    {
        // Pick scheme for a select flag
        
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, pFreshByte));
        
        if (Random::Bool()) {
            pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Xor(pValue, GExpr::RotL64(pWandererA, PopLargeRotation()))));
        } else {
            pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Xor(pValue, GExpr::RotL64(pWandererB, PopLargeRotation()))));
        }
        
        std::vector<GSymbol> aScrabble;
        aScrabble.push_back(pOrbiterA);
        aScrabble.push_back(pOrbiterB);
        aScrabble.push_back(pOrbiterC);
        aScrabble.push_back(pOrbiterD);
        Random::Shuffle(&aScrabble);
        GSymbol aSymbolA = aScrabble[0];
        GSymbol aSymbolB = aScrabble[1];
        GExpr aSelectExpr;
        
        int aWhichRotation = Random::Get(3);
        int aRotationAmount = PopMediumRotation();
        
        if (aWhichRotation == 0) {
            aSelectExpr = GExpr::Xor(GExpr::RotL64(pValue, aRotationAmount), GExpr::Xor(aSymbolA, aSymbolB));
        } else if (aWhichRotation == 1) {
            aSelectExpr = GExpr::Xor(pValue, GExpr::Xor(GExpr::RotL64(aSymbolA, aRotationAmount), aSymbolB));
        } else {
            aSelectExpr = GExpr::Xor(pValue, GExpr::Xor(aSymbolA, GExpr::RotL64(aSymbolB, aRotationAmount)));
        }
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, aSelectExpr));
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Diffuse(GExpr::Symbol(pValue))));
        
        if (Random::Bool()) {
            if (Random::Bool()) {
                if (Random::Bool()) {
                    pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Xor(pValue, GExpr::RotL64(pSecureByteA, PopSmallRotation()))));
                } else {
                    pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Xor(pValue, GExpr::RotL64(pSecureByteB, PopSmallRotation()))));
                }
            } else {
                if (Random::Bool()) {
                    pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Xor(pValue, GExpr::RotL64(pSecureByteA, PopMediumRotation()))));
                } else {
                    pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Xor(pValue, GExpr::RotL64(pSecureByteB, PopMediumRotation()))));
                }
            }
        } else {
            if (Random::Bool()) {
                if (Random::Bool()) {
                    pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Add(pValue, GExpr::RotL64(pSecureByteA, PopSmallRotation()))));
                } else {
                    pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Add(pValue, GExpr::RotL64(pSecureByteB, PopSmallRotation()))));
                }
            } else {
                if (Random::Bool()) {
                    pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Add(pValue, GExpr::RotL64(pSecureByteA, PopMediumRotation()))));
                } else {
                    pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Add(pValue, GExpr::RotL64(pSecureByteB, PopMediumRotation()))));
                }
            }
        }
        
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pValue, GExpr::Diffuse(GExpr::Symbol(pValue))));
        
    }
    
    if (Random::Bool()) {
        GSelect aSelect = GSelect::Random2();
        aSelect.AddStatementA(aMixStatementA);
        aSelect.AddStatementB(aMixStatementB);
        if (!aSelect.Bake(pSelect,
                          pValue,
                          &aTempStatements,
                          pErrorMessage)) {
            printf("CSPRNG failed to bake select (2 case): %s\n", pErrorMessage->c_str());
            return false;
        }
        TwistArray::Append(pStatements, &aTempStatements);
        aTempStatements.clear();
    } else {
        GSelect aSelect = GSelect::Random4();
        aSelect.AddStatementA(aMixStatementA);
        aSelect.AddStatementB(aMixStatementB);
        aSelect.AddStatementC(aMixStatementC);
        aSelect.AddStatementD(aMixStatementD);
        if (!aSelect.Bake(pSelect,
                          pValue,
                          &aTempStatements,
                          pErrorMessage)) {
            printf("CSPRNG failed to bake select (4 case): %s\n", pErrorMessage->c_str());
            return false;
        }
        TwistArray::Append(pStatements, &aTempStatements);
        aTempStatements.clear();
    }
    
    
    
    
    {
        pStatements->push_back(GStatement::Comment("s0 += e ^ previous ^ d;"));
        pStatements->push_back(GStatement::Comment("s0 *= hot0.mul;"));
        pStatements->push_back(GStatement::Comment("s0 = RotL64(s0, r3);"));

        //
        // s0 += e ^ previous ^ d;
        //
        GExpr aFeedbackExpr = GExpr::Xor(
            pFreshByte, // e / gated feedback word
            GExpr::Xor(
                pValuePrevious,
                pOrbiterD
            )
        );

        GExpr aExprWandererA = GExpr::Add(
            pWandererA,
            aFeedbackExpr
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pWandererA, aExprWandererA)
        );
        
        
        int aSaltIndex = Random::Get(2);
        GSymbol aSalt;
        if (aSaltIndex == 0) {
            aSalt = pFixedSaltA;
        } else {
            aSalt = pFixedSaltB;
        }
        
        int aCrazySalt = Random::Get(8);
        GExpr aSaltKeyExpr;

        if (aCrazySalt == 0) {
            aSaltKeyExpr = GExpr::Add(pCross, pSecureByteA);
        } else if (aCrazySalt == 1) {
            aSaltKeyExpr = GExpr::Add(pCross, pSecureByteB);
        } else if (aCrazySalt == 2) {
            aSaltKeyExpr = GExpr::Xor(pCross, pSecureByteA);
        } else if (aCrazySalt == 3) {
            aSaltKeyExpr = GExpr::Xor(pCross, pSecureByteB);
        } else if (aCrazySalt == 4) {
            aSaltKeyExpr = GExpr::Add(pCarry, pSecureByteA);
        } else if (aCrazySalt == 5) {
            aSaltKeyExpr = GExpr::Xor(pCarry, pSecureByteB);
        } else if (aCrazySalt == 6) {
            aSaltKeyExpr = GExpr::Add(pValuePrevious, pCross);
        } else {
            aSaltKeyExpr = GExpr::Xor(pValuePrevious, pCross);
        }

        GExpr aSaltExpr = GQuick::MakeReadBufferOffsetExpression(aSalt, aSaltKeyExpr);
        
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pWandererA, GExpr::Add(pWandererA, aSaltExpr)));
        

        //
        // s0 *= hot0.mul;
        //
        aExprWandererA = GExpr::Mul(
            pWandererA,
            GExpr::Const64(pHotPack.mPair[0].mMul)
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pWandererA, aExprWandererA)
        );

        //
        // s0 = RotL64(s0, r3);
        //
        int aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprWandererA = GExpr::RotL64(
                pWandererA,
                GExpr::Const64(PopMediumRotation())
            );
        } else if (aWhich == 1) {
            aExprWandererA = GExpr::RotL64(
                pWandererA,
                GExpr::Const64(PopLargeRotation())
            );
        } else if (aWhich == 2) {
            aExprWandererA = GExpr::RotL64(
                pWandererA,
                GExpr::Const64(PopLargeRotation())
            );
        } else {
            aExprWandererA = GExpr::RotL64(
                pWandererA,
                GExpr::Const64(PopHealthyRotation())
            );
        }

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pWandererA, aExprWandererA)
        );
    }
    
    {
        pStatements->push_back(GStatement::Comment("s1 ^= e + cross + a;"));
        pStatements->push_back(GStatement::Comment("s1 *= hot1.mul;"));
        pStatements->push_back(GStatement::Comment("s1 = RotL64(s1, r4);"));

        //
        // s1 ^= e + cross + a;
        //
        GExpr aFeedbackExpr = GExpr::Add(
            pFreshByte, // e / gated feedback word
            GExpr::Add(
                pCross,
                pOrbiterA
            )
        );

        //
        // Optional salt XOR into the s1 feedback side.
        //
        int aSaltIndex = Random::Get(2);
        GSymbol aSalt = PopRandomScratchSalt();

        int aCrazySalt = Random::Get(8);
        GExpr aSaltKeyExpr;

        if (aCrazySalt == 0) {
            aSaltKeyExpr = GExpr::Add(pCross, pSecureByteA);
        } else if (aCrazySalt == 1) {
            aSaltKeyExpr = GExpr::Add(pCross, pSecureByteB);
        } else if (aCrazySalt == 2) {
            aSaltKeyExpr = GExpr::Xor(pCross, pSecureByteA);
        } else if (aCrazySalt == 3) {
            aSaltKeyExpr = GExpr::Xor(pCross, pSecureByteB);
        } else if (aCrazySalt == 4) {
            aSaltKeyExpr = GExpr::Add(pFreshByte, pSecureByteA);
        } else if (aCrazySalt == 5) {
            aSaltKeyExpr = GExpr::Xor(pFreshByte, pSecureByteB);
        } else if (aCrazySalt == 6) {
            aSaltKeyExpr = GExpr::Add(pOrbiterA, pCross);
        } else {
            aSaltKeyExpr = GExpr::Xor(pOrbiterA, pCross);
        }

        GExpr aSaltExpr = GQuick::MakeReadBufferOffsetExpression(aSalt, aSaltKeyExpr);

        aFeedbackExpr = GExpr::Xor(aFeedbackExpr, aSaltExpr);

        GExpr aExprWandererB = GExpr::Xor(
            pWandererB,
            aFeedbackExpr
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pWandererB, aExprWandererB)
        );

        //
        // s1 *= hot1.mul;
        //
        aExprWandererB = GExpr::Mul(
            pWandererB,
            GExpr::Const64(pHotPack.mPair[1].mMul)
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pWandererB, aExprWandererB)
        );

        //
        // s1 = RotL64(s1, r4);
        //
        int aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprWandererB = GExpr::RotL64(
                pWandererB,
                GExpr::Const64(PopMediumRotation())
            );
        } else if (aWhich == 1) {
            aExprWandererB = GExpr::RotL64(
                pWandererB,
                GExpr::Const64(PopLargeRotation())
            );
        } else if (aWhich == 2) {
            aExprWandererB = GExpr::RotL64(
                pWandererB,
                GExpr::Const64(PopLargeRotation())
            );
        } else {
            aExprWandererB = GExpr::RotL64(
                pWandererB,
                GExpr::Const64(PopHealthyRotation())
            );
        }

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pWandererB, aExprWandererB)
        );
    }
    
    {
        pStatements->push_back(GStatement::Comment("s2 += b ^ c ^ fixedSalt;"));
        pStatements->push_back(GStatement::Comment("s2 *= hot2.mul;"));
        pStatements->push_back(GStatement::Comment("s2 = RotL64(s2, r5);"));

        //
        // Pick fixed salt A/B.
        //
        int aSaltIndex = Random::Get(2);
        GSymbol aSalt;
        if (aSaltIndex == 0) {
            aSalt = pFixedSaltA;
        } else {
            aSalt = pFixedSaltB;
        }

        //
        // Fixed salt read. Keep this simpler than the scratch salt reads.
        //
        GExpr aSaltExpr;
        if (Random::Bool()) {
            aSaltExpr = GQuick::MakeReadBufferOffsetExpression(aSalt, pLoopIndex);
        } else {
            aSaltExpr = GQuick::MakeReadBufferOffsetExpressionInverted(aSalt, pLoopIndex);
        }

        //
        // s2 += b ^ c ^ fixedSalt;
        //
        GExpr aFeedbackExpr = GExpr::Xor(
            pOrbiterB,
            GExpr::Xor(
                pOrbiterC,
                aSaltExpr
            )
        );

        GExpr aExprWandererC = GExpr::Add(
            pWandererC,
            aFeedbackExpr
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pWandererC, aExprWandererC)
        );

        //
        // s2 *= hot2.mul;
        //
        aExprWandererC = GExpr::Mul(
            pWandererC,
            GExpr::Const64(pHotPack.mPair[2].mMul)
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pWandererC, aExprWandererC)
        );

        //
        // s2 = RotL64(s2, r5);
        //
        int aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprWandererC = GExpr::RotL64(
                pWandererC,
                GExpr::Const64(PopMediumRotation())
            );
        } else if (aWhich == 1) {
            aExprWandererC = GExpr::RotL64(
                pWandererC,
                GExpr::Const64(PopLargeRotation())
            );
        } else if (aWhich == 2) {
            aExprWandererC = GExpr::RotL64(
                pWandererC,
                GExpr::Const64(PopLargeRotation())
            );
        } else {
            aExprWandererC = GExpr::RotL64(
                pWandererC,
                GExpr::Const64(PopHealthyRotation())
            );
        }

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pWandererC, aExprWandererC)
        );
    }
    
    {
        pStatements->push_back(GStatement::Comment("carry += s0 ^ s1 ^ s2 ^ e;"));
        pStatements->push_back(GStatement::Comment("carry *= hot7.mul;"));
        pStatements->push_back(GStatement::Comment("carry = RotL64(carry, r6);"));
        pStatements->push_back(GStatement::Comment("carry ^= carry >> rshift;"));

        //
        // carry += s0 ^ s1 ^ s2 ^ e;
        //
        GExpr aFeedbackExpr = GExpr::Xor(
            pWandererA,
            GExpr::Xor(
                pWandererB,
                GExpr::Xor(
                    pWandererC,
                    pFreshByte // gated e
                )
            )
        );

        GExpr aExprCarry = GExpr::Add(
            pCarry,
            aFeedbackExpr
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pCarry, aExprCarry)
        );

        //
        // carry *= hot5.mul;
        //
        aExprCarry = GExpr::Mul(
            pCarry,
            GExpr::Const64(pHotPack.mPair[7].mMul)
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pCarry, aExprCarry)
        );

        //
        // carry = RotL64(carry, r6);
        //
        int aWhich = Random::Get(4);
        if (aWhich == 0) {
            aExprCarry = GExpr::RotL64(
                pCarry,
                GExpr::Const64(PopMediumRotation())
            );
        } else if (aWhich == 1) {
            aExprCarry = GExpr::RotL64(
                pCarry,
                GExpr::Const64(PopLargeRotation())
            );
        } else if (aWhich == 2) {
            aExprCarry = GExpr::RotL64(
                pCarry,
                GExpr::Const64(PopLargeRotation())
            );
        } else {
            aExprCarry = GExpr::RotL64(
                pCarry,
                GExpr::Const64(PopHealthyRotation())
            );
        }

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pCarry, aExprCarry)
        );

        //
        // carry ^= carry >> 33;
        //
        
        std::vector<int> aCarryShifts = {
            23, 27, 29, 31, 33, 37, 41, 43, 47
        };
        
        
        aExprCarry = GExpr::Xor(
            pCarry,
            GExpr::ShiftR(pCarry, GExpr::Const64(Random::Choice(aCarryShifts)))
        );

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pCarry, aExprCarry)
        );
    }
    
    
    
    return true;
    
}
