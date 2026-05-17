//
//  CSPKDF.cpp
//  MeanMachine
//
//  Created by Dragon on 5/10/26.
//

#include "CSPKDF.hpp"
#include "TwistArray.hpp"
#include "GQuickARX.hpp"
#include <array>
#include <utility>

GARXType GARXOrbiterByIndex(const std::uint8_t pIndex) {
    switch (pIndex) {
        case 0: return GARXType::kOrbiterA;
        case 1: return GARXType::kOrbiterB;
        case 2: return GARXType::kOrbiterC;
        case 3: return GARXType::kOrbiterD;
        case 4: return GARXType::kOrbiterE;
        case 5: return GARXType::kOrbiterF;
        default: return GARXType::kInv;
    }
}

GARXType GARXWandererByIndex(const std::uint8_t pIndex) {
    switch (pIndex) {
        case 0: return GARXType::kUnwindA;
        case 1: return GARXType::kUnwindB;
        case 2: return GARXType::kUnwindC;
        case 3: return GARXType::kUnwindD;
        case 4: return GARXType::kUnwindE;
        case 5: return GARXType::kUnwindF;
        default: return GARXType::kInv;
    }
}

void ConfigureFallbackCrushCarry(GARXPassPlan *pPassPlan) {
    if (pPassPlan == nullptr) {
        return;
    }

    pPassPlan->mCrushPlan.mPairA.mTypeA = GARXType::kOrbiterA;
    pPassPlan->mCrushPlan.mPairA.mTypeB = GARXType::kOrbiterB;
    pPassPlan->mCrushPlan.mPairA.mRotateA = true;
    pPassPlan->mCrushPlan.mPairA.mRotationAmount = 17;

    pPassPlan->mCrushPlan.mPairB.mTypeA = GARXType::kOrbiterC;
    pPassPlan->mCrushPlan.mPairB.mTypeB = GARXType::kOrbiterD;
    pPassPlan->mCrushPlan.mPairB.mRotateA = false;
    pPassPlan->mCrushPlan.mPairB.mRotationAmount = 29;

    pPassPlan->mCrushPlan.mPairC.mTypeA = GARXType::kOrbiterE;
    pPassPlan->mCrushPlan.mPairC.mTypeB = GARXType::kOrbiterF;
    pPassPlan->mCrushPlan.mPairC.mRotateA = true;
    pPassPlan->mCrushPlan.mPairC.mRotationAmount = 43;

    pPassPlan->mCarryPlan.mPairA.mTypeA = GARXType::kUnwindA;
    pPassPlan->mCarryPlan.mPairA.mTypeB = GARXType::kUnwindD;
    pPassPlan->mCarryPlan.mPairA.mRotateA = true;
    pPassPlan->mCarryPlan.mPairA.mRotationAmount = 19;

    pPassPlan->mCarryPlan.mPairB.mTypeA = GARXType::kUnwindB;
    pPassPlan->mCarryPlan.mPairB.mTypeB = GARXType::kUnwindE;
    pPassPlan->mCarryPlan.mPairB.mRotateA = false;
    pPassPlan->mCarryPlan.mPairB.mRotationAmount = 37;

    pPassPlan->mCarryPlan.mPairC.mTypeA = GARXType::kUnwindC;
    pPassPlan->mCarryPlan.mPairC.mTypeB = GARXType::kUnwindF;
    pPassPlan->mCarryPlan.mPairC.mRotateA = true;
    pPassPlan->mCarryPlan.mPairC.mRotationAmount = 53;

    pPassPlan->mCarryPlan.mSecretCurrentRotation = 23;
    pPassPlan->mCarryPlan.mMulRotation = 31;
    pPassPlan->mCarryPlan.mShiftAmount = 29;
}


bool CSPKDF::Bake(GARXPassPlan *pPassPlan,
                              
                              GSymbol pDest,
                              bool pDestWriteInverted,
                              
                              GSymbol pLoopIndex,
                  
                              GExpr pPublicIngressSourceA,
                              GExpr pPublicIngressSourceB,
                              GExpr pPublicIngressSourceC,
                              GExpr pPublicIngressSourceD,
                              GExpr pPrivateIngressSourceA,
                              GExpr pPrivateIngressSourceB,
                              GExpr pPrivateIngressSourceC,
                              GExpr pPrivateIngressSourceD,
                              GExpr pCrossIngressSourceA,
                              GExpr pCrossIngressSourceB,
                              GExpr pCrossIngressSourceC,
                              GExpr pCrossIngressSourceD,
                              GExpr pPublicIngressDomainWord,
                              GExpr pPrivateIngressDomainWord,
                              GExpr pCrossIngressDomainWord,
                                          
                              GSymbol pStreamCurrent,
                              GSymbol pStreamPrevious,
                              GSymbol pStreamScatter,
                              GSymbol pStreamCross,
                              
                              GSymbol pStreamScatterComponentA,
                              GSymbol pStreamScatterComponentB,
                              GSymbol pStreamScatterComponentC,
                              GSymbol pStreamScatterComponentD,
                              
                              
                              
                              GSymbol pSecretCurrent,
                              GSymbol pSecretPrevious,
                              GSymbol pSecretScatter,
                              GSymbol pSecretWrite,
                              
                              GSymbol pSecretScatterComponentA,
                              GSymbol pSecretScatterComponentB,
                              GSymbol pSecretScatterComponentC,
                              GSymbol pSecretScatterComponentD,
                              
                              GSymbol pCarry,
                              
                              GSymbol pUnwindA,
                              GSymbol pUnwindB,
                              GSymbol pUnwindC,
                              GSymbol pUnwindD,
                              GSymbol pUnwindE,
                              GSymbol pUnwindF,
                              
                              GSymbol pOrbiterA,
                              GSymbol pOrbiterB,
                              GSymbol pOrbiterC,
                              GSymbol pOrbiterD,
                              GSymbol pOrbiterE,
                              GSymbol pOrbiterF,

                              TwistDomainSeedRoundMaterial *pMatsUnwind,
                              TwistDomainSeedRoundMaterial *pMatsOrbiter,
                              TwistDomainSeedRoundMaterial *pMatsOrbiterInit,
                              
                              GSymbol pPlugKeyA,
                              GSymbol pPlugKeyB,
                              GSymbol pPlugKeyC,
                              GSymbol pPlugKeyD,
                              GSymbol pPlugKeyE,
                              GSymbol pPlugKeyF,
                              
                              std::vector<GSymbol> pSBoxes,
                              
                              GHotPack pHotPack,
                              
                              std::vector<GStatement> *pStatements,
                              std::string *pErrorMessage) {
    
    if (pPassPlan == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "CSPKDF::Bake received null GARXPassPlan";
        }
        return false;
    }
    
    if (pStatements == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "CSPKDF::Bake received null statement vector";
        }
        return false;
    }

    if (pSBoxes.size() < 8) {
        printf("fatal: CSPKDF::Bake requires at least 8 sboxes for crush mix64_8\n");
        exit(0);
    }

    (void)pMatsUnwind;
    (void)pMatsOrbiter;
    (void)pMatsOrbiterInit;

    const GSymbol aDomainSaltA = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiterInit, TwistSaltLane::kA);
    const GSymbol aDomainSaltB = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiterInit, TwistSaltLane::kB);
    const GSymbol aDomainSaltC = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiter, TwistSaltLane::kC);
    const GSymbol aDomainSaltD = BufParamSymbolDomainSalt(TwistSaltPhase::kOrbiter, TwistSaltLane::kD);
    const GSymbol aDomainSaltE = BufParamSymbolDomainSalt(TwistSaltPhase::kUnwind, TwistSaltLane::kE);
    const GSymbol aDomainSaltF = BufParamSymbolDomainSalt(TwistSaltPhase::kUnwind, TwistSaltLane::kF);
    
    auto RandomDiffuseKind = [&]() -> GDiffuseKind {
        int aRand = Random::Get(3);
        if (aRand == 0) { return GDiffuseKind::kA; }
        if (aRand == 1) { return GDiffuseKind::kB; }
        return GDiffuseKind::kC;
    };
    
    auto TypeSymbol = [&](GARXType pType) -> GSymbol {
        switch (pType) {
            case GARXType::kStreamCurrent: return pStreamCurrent;
            case GARXType::kStreamPrevious: return pStreamPrevious;
            case GARXType::kStreamScatter: return pStreamScatter;
            case GARXType::kStreamCross: return pStreamCross;

            case GARXType::kSecretCurrent: return pSecretCurrent;
            case GARXType::kSecretPrevious: return pSecretPrevious;
            case GARXType::kSecretScatter: return pSecretScatter;

            case GARXType::kCarry: return pCarry;

            case GARXType::kUnwindA: return pUnwindA;
            case GARXType::kUnwindB: return pUnwindB;
            case GARXType::kUnwindC: return pUnwindC;
            case GARXType::kUnwindD: return pUnwindD;
            case GARXType::kUnwindE: return pUnwindE;
            case GARXType::kUnwindF: return pUnwindF;

            case GARXType::kOrbiterA: return pOrbiterA;
            case GARXType::kOrbiterB: return pOrbiterB;
            case GARXType::kOrbiterC: return pOrbiterC;
            case GARXType::kOrbiterD: return pOrbiterD;
            case GARXType::kOrbiterE: return pOrbiterE;
            case GARXType::kOrbiterF: return pOrbiterF;

            default:
                printf("fatal: CSPKDF::Bake invalid GARXType=%s\n",
                       GARXSkeleton::GetTypeName(pType));
                exit(0);
        }
    };

    auto TypeExpr = [&](GARXType pType) -> GExpr {
        return GExpr::Symbol(TypeSymbol(pType));
    };

    auto RotTypeExpr = [&](GARXType pType, int pRotation) -> GExpr {
        if (pRotation < 0) {
            printf("fatal: CSPKDF::Bake tried to rotate %s with invalid rotation=%d\n",
                   GARXSkeleton::GetTypeName(pType),
                   pRotation);
            exit(0);
        }

        return GQuick::RotL64(TypeExpr(pType), pRotation);
    };

    const GSymbol aSaltLanes[6] = {
        aDomainSaltA,
        aDomainSaltB,
        aDomainSaltC,
        aDomainSaltD,
        aDomainSaltE,
        aDomainSaltF
    };

    const GSymbol aPlugKeyLanes[6] = {
        pPlugKeyA,
        pPlugKeyB,
        pPlugKeyC,
        pPlugKeyD,
        pPlugKeyE,
        pPlugKeyF
    };

    auto SaltLaneSymbol = [&](int pSaltLaneIndex) -> GSymbol {
        if (pSaltLaneIndex < 0 || pSaltLaneIndex >= 6) {
            printf("fatal: CSPKDF::Bake invalid salt lane=%d\n",
                   pSaltLaneIndex);
            exit(0);
        }
        return aSaltLanes[pSaltLaneIndex];
    };

    auto PlugKeySymbolForLane = [&](int pSaltLaneIndex) -> GSymbol {
        if (pSaltLaneIndex < 0 || pSaltLaneIndex >= 6) {
            printf("fatal: CSPKDF::Bake invalid plug-key lane=%d\n",
                   pSaltLaneIndex);
            exit(0);
        }
        return aPlugKeyLanes[pSaltLaneIndex];
    };
    
    auto MakeLoopKeyExpr = [&](const GARXDatum &pDatum) -> GExpr {

        if (pDatum.mOffsetAmount < 0) {
            printf("fatal: CSPKDF::Bake loop key has invalid offset\n");
            exit(0);
        }

        GSymbol aSalt = SaltLaneSymbol(pDatum.mSaltLaneIndex);

        return GQuick::MakeReadBufferOffsetExpressionDirected(
            aSalt,
            pLoopIndex,
            pDatum.mIsLoopIndexInverted,
            static_cast<std::uint32_t>(pDatum.mOffsetAmount)
        );
    };

    auto MakePlugKeyExpr = [&](const GARXDatum &pDatum) -> GExpr {
        
        if (pDatum.mPlugTypeA == GARXType::kInv ||
            pDatum.mPlugTypeB == GARXType::kInv ||
            pDatum.mRotationAmount < 0 ||
            pDatum.mOffsetAmount < 0) {
            printf("fatal: CSPKDF::Bake invalid plug datum lane=%d typeA=%s typeB=%s rot=%d off=%d\n",
                   pDatum.mSaltLaneIndex,
                   GARXSkeleton::GetTypeName(pDatum.mPlugTypeA),
                   GARXSkeleton::GetTypeName(pDatum.mPlugTypeB),
                   pDatum.mRotationAmount,
                   pDatum.mOffsetAmount);
            exit(0);
        }
        
        GSymbol aSalt = SaltLaneSymbol(pDatum.mSaltLaneIndex);
        GSymbol aPlugKey = PlugKeySymbolForLane(pDatum.mSaltLaneIndex);
        
        return GQuickARX::PlugSaltRead(aSalt, aPlugKey, pDatum.mOffsetAmount);
    };
    
    auto MakeDatumExpr = [&](const GARXDatum &pDatum,
                             std::size_t pHotIndex) -> GExpr {
        switch (pDatum.mKind) {
            case GARXDatumKind::kType:
                return GQuickARX::MaybeRotL64(TypeExpr(pDatum.mType), pDatum.mRotationAmount);
            case GARXDatumKind::kLoopKey:
                return MakeLoopKeyExpr(pDatum);
            case GARXDatumKind::kPlugKey:
                return MakePlugKeyExpr(pDatum);
            case GARXDatumKind::kHotAdd:
                return GQuickARX::HotAdd(pHotPack, pHotIndex);
            case GARXDatumKind::kHotMul:
                return GQuickARX::HotMul(pHotPack, pHotIndex);
            default:
                printf("fatal: CSPKDF::Bake invalid datum kind=%s\n",
                       GARXSkeleton::GetDatumKindName(pDatum.mKind));
                exit(0);
        }
    };
    
    auto EmitPlugPrepForStatement = [&](const GARXStatementPlan &pStatement) {
        
        for (const GARXDatum &aDatum: pStatement.mDatums) {
            
            if (aDatum.mKind != GARXDatumKind::kPlugKey) {
                continue;
            }
            
            if (aDatum.mPlugTypeA == GARXType::kInv ||
                aDatum.mPlugTypeB == GARXType::kInv ||
                aDatum.mRotationAmount < 0 ||
                aDatum.mOffsetAmount < 0) {
                printf("fatal: CSPKDF::Bake invalid plug datum lane=%d typeA=%s typeB=%s rot=%d off=%d\n",
                       aDatum.mSaltLaneIndex,
                       GARXSkeleton::GetTypeName(aDatum.mPlugTypeA),
                       GARXSkeleton::GetTypeName(aDatum.mPlugTypeB),
                       aDatum.mRotationAmount,
                       aDatum.mOffsetAmount);
                exit(0);
            }
            
            GSymbol aPlugKey = PlugKeySymbolForLane(aDatum.mSaltLaneIndex);
            
            GExpr aTermA = RotTypeExpr(aDatum.mPlugTypeA,
                                       aDatum.mRotationAmount);
            GExpr aTermB = TypeExpr(aDatum.mPlugTypeB);
            
            pStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    aPlugKey,
                    GQuickARX::Diffuse(GExpr::Xor(aTermA, aTermB),
                                       RandomDiffuseKind())
                )
            );
        }
    };
    
    auto MakeStatementTerms = [&](const GARXStatementPlan &pStatement,
                                  std::size_t pHotIndex) -> std::vector<GExpr> {
        std::vector<GExpr> aTerms;
        for (const GARXDatum &aDatum: pStatement.mDatums) {
            if (aDatum.mKind == GARXDatumKind::kHotMul) { continue; }
            aTerms.push_back(MakeDatumExpr(aDatum, pHotIndex));
        }
        return aTerms;
    };
    
    auto EmitAddChainAssign = [&](GSymbol pTarget,
                                  const std::vector<GExpr> &pTerms) -> bool {
        if (pTerms.empty()) {
            return false;
        }

        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(
                pTarget,
                GQuick::AddChain(pTerms)
            )
        );
        
        return true;
    };
    
    auto EmitAssignStatement = [&](const GARXStatementPlan &pStatement,
                                   std::size_t pHotIndex) -> bool {
        const std::vector<GExpr> aTerms = MakeStatementTerms(pStatement, pHotIndex);
        return EmitAddChainAssign(TypeSymbol(pStatement.mTarget), aTerms);
    };
    
    auto EmitRotateStatement = [&](const GARXStatementPlan &pStatement,
                                   std::size_t pHotIndex) -> bool {
        pStatements->push_back(
            GQuickARX::MulRotAssign(TypeSymbol(pStatement.mTarget),
                                     pHotPack,
                                     pHotIndex,
                                     pStatement.mRotationAmount)
        );
        return true;
    };
    
    auto IsValidSymbol = [&](const GSymbol &pSymbol) -> bool {
        return !pSymbol.IsInvalid();
    };

    auto MakeScatterExpr = [&](const GARXBlendInputPlan &pScatterPlan,
                               GSymbol pComponentA,
                               GSymbol pComponentB,
                               GSymbol pComponentC,
                               GSymbol pComponentD,
                               const char *pName) -> GExpr {
        
        struct ScatterComponent {
            GSymbol mSymbol;
            int mRotation;
        };
        
        ScatterComponent aComponents[4] = {
            { pComponentA, pScatterPlan.mRotationA },
            { pComponentB, pScatterPlan.mRotationB },
            { pComponentC, pScatterPlan.mRotationC },
            { pComponentD, pScatterPlan.mRotationD }
        };
        
        std::vector<GExpr> aTerms;
        int aInvalidCount = 0;
        
        for (int i = 0; i < 4; i++) {
            if (IsValidSymbol(aComponents[i].mSymbol) == false) {
                aInvalidCount++;
                continue;
            }
            
            if (aComponents[i].mRotation < 0) {
                printf("fatal: CSPKDF::Bake %s scatter component %d has invalid rotation=%d\n",
                       pName,
                       i,
                       aComponents[i].mRotation);
                exit(0);
            }
            
            aTerms.push_back(
                GQuickARX::RotL64(GExpr::Symbol(aComponents[i].mSymbol),
                                  aComponents[i].mRotation)
            );
        }
        
        if (aInvalidCount > 2) {
            printf("fatal: CSPKDF::Bake %s scatter has too many invalid components, invalid=%d\n",
                   pName,
                   aInvalidCount);
            exit(0);
        }
        
        if (aTerms.size() < 2) {
            printf("fatal: CSPKDF::Bake %s scatter has too few live components, live=%zu\n",
                   pName,
                   aTerms.size());
            exit(0);
        }
        
        if (aTerms.size() == 2) {
            return GQuickARX::Diffuse(
                GExpr::Xor(aTerms[0], aTerms[1]),
                RandomDiffuseKind()
            );
        }
        
        if (aTerms.size() == 3) {
            return GQuickARX::Diffuse(
                GExpr::Add(GExpr::Xor(aTerms[0], aTerms[1]),
                           aTerms[2]),
                RandomDiffuseKind()
            );
        }
        
        return GQuickARX::XorAddXorDiffuse(
            aTerms[0],
            aTerms[1],
            aTerms[2],
            aTerms[3],
            RandomDiffuseKind()
        );
    };

    auto EmitIngressStatements = [&]() {
        auto EmitIngressLane = [&](const GSymbol pTarget,
                                   const GARXBlendInputPlan &pBlendPlan,
                                   const GExpr &pSourceA,
                                   const GExpr &pSourceB,
                                   const GExpr &pSourceC,
                                   const GExpr &pSourceD,
                                   const GExpr &pDomainWord,
                                   const GDiffuseKind pDiffuseKind) {
            const GExpr aPairA = GExpr::Xor(
                GQuickARX::RotL64(pSourceA, pBlendPlan.mRotationA),
                GQuickARX::RotL64(pSourceB, pBlendPlan.mRotationB)
            );
            const GExpr aPairB = GExpr::Xor(
                GQuickARX::RotL64(pSourceC, pBlendPlan.mRotationC),
                GQuickARX::RotL64(pSourceD, pBlendPlan.mRotationD)
            );
            
            pStatements->push_back(
                GQuick::MakeAssignVariableStatement(pTarget, aPairA)
            );
            pStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    pTarget,
                    GExpr::Add(GExpr::Symbol(pTarget), aPairB)
                )
            );
            pStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    pTarget,
                    GExpr::Xor(GExpr::Symbol(pTarget), pDomainWord)
                )
            );
            pStatements->push_back(
                GQuick::MakeAssignVariableStatement(
                    pTarget,
                    GQuickARX::Diffuse(GExpr::Symbol(pTarget), pDiffuseKind)
                )
            );
        };
        
        EmitIngressLane(pStreamCurrent,
                        pPassPlan->mStreamInputBlend,
                        pPublicIngressSourceA,
                        pPublicIngressSourceB,
                        pPublicIngressSourceC,
                        pPublicIngressSourceD,
                        pPublicIngressDomainWord,
                        GDiffuseKind::kA);
        
        EmitIngressLane(pSecretCurrent,
                        pPassPlan->mSecretInputBlend,
                        pPrivateIngressSourceA,
                        pPrivateIngressSourceB,
                        pPrivateIngressSourceC,
                        pPrivateIngressSourceD,
                        pPrivateIngressDomainWord,
                        GDiffuseKind::kB);
        
        EmitIngressLane(pStreamCross,
                        pPassPlan->mCrossInputBlend,
                        pCrossIngressSourceA,
                        pCrossIngressSourceB,
                        pCrossIngressSourceC,
                        pCrossIngressSourceD,
                        pCrossIngressDomainWord,
                        GDiffuseKind::kC);
    };

    
    auto EmitSeeds = [&]() -> bool {
        
        std::size_t aSeedHotIndex = 0;

        for (GARXStatementGroup *aGroup: pPassPlan->mGroups) {
            if (aGroup == nullptr) {
                printf("fatal: CSPKDF::Bake null group in seed walk\n");
                exit(0);
            }

            if (aGroup->mGroupType != GARXGroupType::kSeed) {
                continue;
            }

            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                if (aStatement == nullptr) {
                    printf("fatal: CSPKDF::Bake null statement in seed group\n");
                    exit(0);
                }

                if (aStatement->mStatementType != GARXStatementType::kRoundSeed) {
                    printf("fatal: CSPKDF::Bake unexpected statement in seed group: %s\n",
                           GARXSkeleton::GetStatementKindName(aStatement->mStatementType));
                    exit(0);
                }

                EmitPlugPrepForStatement(*aStatement);
            }
        }
        
        for (GARXStatementGroup *aGroup: pPassPlan->mGroups) {
            if (aGroup == nullptr) {
                printf("fatal: CSPKDF::Bake null group in seed walk\n");
                exit(0);
            }
            
            if (aGroup->mGroupType != GARXGroupType::kSeed) {
                continue;
            }
            
            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                if (aStatement == nullptr) {
                    printf("fatal: CSPKDF::Bake null statement in seed group\n");
                    exit(0);
                }
                
                if (aStatement->mStatementType != GARXStatementType::kRoundSeed) {
                    printf("fatal: CSPKDF::Bake unexpected statement in seed group: %s\n",
                           GARXSkeleton::GetStatementKindName(aStatement->mStatementType));
                    exit(0);
                }

                EmitAssignStatement(*aStatement, aSeedHotIndex);
                aSeedHotIndex++;
            }
        }
        
        if (aSeedHotIndex != 6) {
            printf("fatal: CSPKDF::Bake expected 6 seed statements, got %zu\n",
                   aSeedHotIndex);
            exit(0);
        }
        
        return true;
    };
    
    auto EmitForwardWalk = [&]() -> bool {
        
        std::size_t aForwardHotIndex = 6;
        
        bool aFirst = true;
        for (GARXStatementGroup *aGroup: pPassPlan->mGroups) {
            if (aGroup == nullptr) {
                printf("fatal: CSPKDF::Bake null group in forward walk\n");
                exit(0);
            }
            
            if (aGroup->mGroupType != GARXGroupType::kForwardTriplet) {
                continue;
            }
            
            if (aFirst == true) {
                aFirst = false;
            } else {
                pStatements->push_back(GStatement::Comment(""));
            }
            
            GARXStatementPlan *aLeadStatement = nullptr;
            GARXStatementPlan *aFeedbackStatement = nullptr;
            GARXStatementPlan *aRotateStatement = nullptr;

            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                if (aStatement == nullptr) {
                    printf("fatal: CSPKDF::Bake null statement in forward group\n");
                    exit(0);
                }
                
                switch (aStatement->mStatementType) {
                    case GARXStatementType::kForwardLead:
                        aLeadStatement = aStatement;
                        break;
                        
                    case GARXStatementType::kForwardFeedback:
                        aFeedbackStatement = aStatement;
                        break;
                        
                    case GARXStatementType::kForwardRotate:
                        aRotateStatement = aStatement;
                        break;
                        
                    default:
                        printf("fatal: CSPKDF::Bake unexpected statement in forward group: %s\n",
                               GARXSkeleton::GetStatementKindName(aStatement->mStatementType));
                        exit(0);
                }
            }
            
            if (aLeadStatement == nullptr ||
                aFeedbackStatement == nullptr ||
                aRotateStatement == nullptr) {
                printf("fatal: CSPKDF::Bake incomplete forward triplet, lead=%p feedback=%p rotate=%p\n",
                       static_cast<void *>(aLeadStatement),
                       static_cast<void *>(aFeedbackStatement),
                       static_cast<void *>(aRotateStatement));
                exit(0);
            }
            
            std::size_t aLeadHotIndex = aForwardHotIndex++;
            std::size_t aFeedbackHotIndex = aForwardHotIndex++;
            
            EmitPlugPrepForStatement(*aLeadStatement);
            EmitPlugPrepForStatement(*aFeedbackStatement);
            
            EmitAssignStatement(*aLeadStatement, aLeadHotIndex);
            EmitAssignStatement(*aFeedbackStatement, aFeedbackHotIndex);
            EmitRotateStatement(*aRotateStatement, aFeedbackHotIndex);
        }
        
        return true;
    };
    
    auto MakeStreamScatterExpr = [&]() -> GExpr {
        return MakeScatterExpr(pPassPlan->mStreamScatterBlend,
                               pStreamScatterComponentA,
                               pStreamScatterComponentB,
                               pStreamScatterComponentC,
                               pStreamScatterComponentD,
                               "stream");
    };

    auto MakeSecretScatterExpr = [&]() -> GExpr {
        return MakeScatterExpr(pPassPlan->mSecretScatterBlend,
                               pSecretScatterComponentA,
                               pSecretScatterComponentB,
                               pSecretScatterComponentC,
                               pSecretScatterComponentD,
                               "secret");
    };
    
    
    auto MakeCrushPairExpr = [&](const GARXCrushPairPlan &pPair) -> GExpr {
        if (pPair.mRotateA) {
            return GQuickARX::XorPairRotA(TypeSymbol(pPair.mTypeA),
                                          TypeSymbol(pPair.mTypeB),
                                          pPair.mRotationAmount);
        } else {
            return GQuickARX::XorPairRotB(TypeSymbol(pPair.mTypeA),
                                          TypeSymbol(pPair.mTypeB),
                                          pPair.mRotationAmount);
        }
    };
    
    auto EmitUnwind = [&]() -> bool {
        
        std::size_t aUnwindHotIndex = 18;

        for (GARXStatementGroup *aGroup: pPassPlan->mGroups) {
            if (aGroup == nullptr) {
                printf("fatal: CSPKDF::Bake null group in unwind walk\n");
                exit(0);
            }

            if (aGroup->mGroupType != GARXGroupType::kUnwind) {
                continue;
            }

            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                if (aStatement == nullptr) {
                    printf("fatal: CSPKDF::Bake null statement in unwind group\n");
                    exit(0);
                }

                if (aStatement->mStatementType != GARXStatementType::kUnwind) {
                    printf("fatal: CSPKDF::Bake unexpected statement in unwind group: %s\n",
                           GARXSkeleton::GetStatementKindName(aStatement->mStatementType));
                    exit(0);
                }

                EmitPlugPrepForStatement(*aStatement);
            }
        }
        
        for (GARXStatementGroup *aGroup: pPassPlan->mGroups) {
            if (aGroup == nullptr) {
                printf("fatal: CSPKDF::Bake null group in unwind walk\n");
                exit(0);
            }
            
            if (aGroup->mGroupType != GARXGroupType::kUnwind) {
                continue;
            }

            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                if (aStatement == nullptr) {
                    printf("fatal: CSPKDF::Bake null statement in unwind group\n");
                    exit(0);
                }
                
                if (aStatement->mStatementType != GARXStatementType::kUnwind) {
                    printf("fatal: CSPKDF::Bake unexpected statement in unwind group: %s\n",
                           GARXSkeleton::GetStatementKindName(aStatement->mStatementType));
                    exit(0);
                }

                EmitAssignStatement(*aStatement, aUnwindHotIndex);
                aUnwindHotIndex++;
            }
        }
        
        if (aUnwindHotIndex != 24) {
            printf("fatal: CSPKDF::Bake expected 6 unwind statements, got %zu\n",
                   aUnwindHotIndex - 18);
            exit(0);
        }
        
        return true;
    };
    
    auto MakeCarryPairExpr = [&](const GARXCarryPairPlan &pPair) -> GExpr {
        if (pPair.mRotateA) {
            return GExpr::Xor(
                GQuickARX::RotL64(GExpr::Symbol(TypeSymbol(pPair.mTypeA)),
                                  pPair.mRotationAmount),
                GExpr::Symbol(TypeSymbol(pPair.mTypeB))
            );
        } else {
            return GExpr::Xor(
                GExpr::Symbol(TypeSymbol(pPair.mTypeA)),
                GQuickARX::RotL64(GExpr::Symbol(TypeSymbol(pPair.mTypeB)),
                                  pPair.mRotationAmount)
            );
        }
    };
    
    auto EmitCarryStatement = [&]() -> bool {
        
        const GARXCarryPlan &aCarryPlan = pPassPlan->mCarryPlan;
        
        GExpr aExpr = GExpr::Add(GExpr::Symbol(pCarry),
                                 MakeCarryPairExpr(aCarryPlan.mPairA));
        
        aExpr = GExpr::Add(aExpr, MakeCarryPairExpr(aCarryPlan.mPairB));
        aExpr = GExpr::Add(aExpr, MakeCarryPairExpr(aCarryPlan.mPairC));
        
        aExpr = GExpr::Add(
            aExpr,
            GQuickARX::RotL64(GExpr::Symbol(pSecretCurrent),
                              aCarryPlan.mSecretCurrentRotation)
        );
        
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pCarry, aExpr)
        );
        
        GExpr aMul = GExpr::Mul(
            GExpr::Symbol(pCarry),
            GQuickARX::HotMul(pHotPack, 24)
        );
        
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(
                pCarry,
                GQuickARX::RotL64(aMul, aCarryPlan.mMulRotation)
            )
        );
        
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(
                pCarry,
                GExpr::Xor(
                    GExpr::Symbol(pCarry),
                    GExpr::ShiftR(GExpr::Symbol(pCarry),
                                    GExpr::Const64(static_cast<std::uint64_t>(aCarryPlan.mShiftAmount)))
                )
            )
        );
        
        return true;
    };
    
    auto MakeCrushExpr = [&]() -> GExpr {
        
        const GARXCrushPlan &aCrushPlan = pPassPlan->mCrushPlan;
        
        return GQuickARX::Crush3XorPairsDiffuse(
            MakeCrushPairExpr(aCrushPlan.mPairA),
            MakeCrushPairExpr(aCrushPlan.mPairB),
            MakeCrushPairExpr(aCrushPlan.mPairC),
            GExpr::Symbol(pSecretScatter),
            GExpr::Symbol(pCarry),
            RandomDiffuseKind()
        );
    };
    
    auto EmitScatterStatement = [&]() {
        GExpr aStreamScatterExpr = MakeStreamScatterExpr();
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pStreamScatter,
                                                                   aStreamScatterExpr));

        GExpr aSecretScatterExpr = MakeSecretScatterExpr();
        pStatements->push_back(GQuick::MakeAssignVariableStatement(pSecretScatter,
                                                                   aSecretScatterExpr));
    };
    
    auto EmitCrushStatement = [&]() -> bool {
        
        GExpr aCrushExpr = MakeCrushExpr();

        //
        // Hidden recurrence value.
        // This is also the value written to the byte lane after final 64-bit diffuse.
        //
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(pSecretCurrent,
                                                aCrushExpr)
        );

        if (pDestWriteInverted) {
            pStatements->push_back(
                GQuick::MakeAssignDestStatementInverted(pDest,
                                                        pLoopIndex,
                                                        pSecretCurrent)
            );
        } else {
            pStatements->push_back(
                GQuick::MakeAssignDestStatement(pDest,
                                                pLoopIndex,
                                                pSecretCurrent)
            );
        }
        
        return true;
    };
    
    EmitIngressStatements();
    
    pStatements->push_back(GStatement::Comment(""));
    
    EmitScatterStatement();
    
    pStatements->push_back(GStatement::Comment(""));
    
    if (EmitSeeds() == false) {
        return false;
    }

    pStatements->push_back(GStatement::Comment(""));
    
    if (EmitForwardWalk() == false) {
        return false;
    }

    pStatements->push_back(GStatement::Comment(""));
    
    if (EmitCrushStatement() == false) {
        return false;
    }
    
    pStatements->push_back(GStatement::Comment(""));
    
    if (EmitUnwind() == false) {
        return false;
    }
    
    pStatements->push_back(GStatement::Comment(""));

    EmitCarryStatement();

    return true;
}
