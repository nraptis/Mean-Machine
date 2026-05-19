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

#if 0

namespace {

enum class CSPKDFSaltPhase {
    kOrbiterAssign,
    kOrbiterUpdate,
    kWandererUpdate
};

}

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
        case 0: return GARXType::kWandererA;
        case 1: return GARXType::kWandererB;
        case 2: return GARXType::kWandererC;
        case 3: return GARXType::kWandererD;
        case 4: return GARXType::kWandererE;
        case 5: return GARXType::kWandererF;
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

    pPassPlan->mCarryPlan.mPairA.mTypeA = GARXType::kWandererA;
    pPassPlan->mCarryPlan.mPairA.mTypeB = GARXType::kWandererD;
    pPassPlan->mCarryPlan.mPairA.mRotateA = true;
    pPassPlan->mCarryPlan.mPairA.mRotationAmount = 19;

    pPassPlan->mCarryPlan.mPairB.mTypeA = GARXType::kWandererB;
    pPassPlan->mCarryPlan.mPairB.mTypeB = GARXType::kWandererE;
    pPassPlan->mCarryPlan.mPairB.mRotateA = false;
    pPassPlan->mCarryPlan.mPairB.mRotationAmount = 37;

    pPassPlan->mCarryPlan.mPairC.mTypeA = GARXType::kWandererC;
    pPassPlan->mCarryPlan.mPairC.mTypeB = GARXType::kWandererF;
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
                              
                              GSymbol pStreamScatterComponentA,
                              GSymbol pStreamScatterComponentB,
                              GSymbol pStreamScatterComponentC,
                              GSymbol pStreamScatterComponentD,
                              
                              GSymbol pSecretScatterComponentA,
                              GSymbol pSecretScatterComponentB,
                              GSymbol pSecretScatterComponentC,
                              GSymbol pSecretScatterComponentD,
                              
                              const GDomainSaltSet &pDomainSaltSet,
                              
                              GHotPack pHotPack,
                              
                              std::vector<GStatement> *pStatements,
                              std::string *pErrorMessage) {
    
    GSymbol aWandererA = GSymbol::Var(TwistVariable::kWandererA);
    GSymbol aWandererB = GSymbol::Var(TwistVariable::kWandererB);
    GSymbol aWandererC = GSymbol::Var(TwistVariable::kWandererC);
    GSymbol aWandererD = GSymbol::Var(TwistVariable::kWandererD);
    GSymbol aWandererE = GSymbol::Var(TwistVariable::kWandererE);
    GSymbol aWandererF = GSymbol::Var(TwistVariable::kWandererF);

    GSymbol aOrbiterA = GSymbol::Var(TwistVariable::kOrbiterA);
    GSymbol aOrbiterB = GSymbol::Var(TwistVariable::kOrbiterB);
    GSymbol aOrbiterC = GSymbol::Var(TwistVariable::kOrbiterC);
    GSymbol aOrbiterD = GSymbol::Var(TwistVariable::kOrbiterD);
    GSymbol aOrbiterE = GSymbol::Var(TwistVariable::kOrbiterE);
    GSymbol aOrbiterF = GSymbol::Var(TwistVariable::kOrbiterF);
    
    GSymbol aStreamCurrent = GSymbol::Var(TwistVariable::kPublicIngress);
    GSymbol aStreamPrevious = GSymbol::Var(TwistVariable::kPublicPrevious);
    GSymbol aStreamScatter = GSymbol::Var(TwistVariable::kPublicScatter);
    GSymbol aStreamCross = GSymbol::Var(TwistVariable::kCrossIngress);
    
    GSymbol aSecretCurrent = GSymbol::Var(TwistVariable::kPrivateIngress);
    GSymbol aSecretPrevious = GSymbol::Var(TwistVariable::kPrivatePrevious);
    GSymbol aSecretScatter = GSymbol::Var(TwistVariable::kPrivateScatter);
    GSymbol aSecretWrite = GSymbol::Var(TwistVariable::kPrivateWrite);
    
    GSymbol aCarry = GSymbol::Var(TwistVariable::kCarry);
    
    GSymbol aPublicIngressDomainWord = GSymbol::Var(TwistVariable::kPublicIngressDomainWord);
    GSymbol aPrivateIngressDomainWord = GSymbol::Var(TwistVariable::kPrivateIngressDomainWord);
    GSymbol aCrossIngressDomainWord = GSymbol::Var(TwistVariable::kCrossIngressDomainWord);
    
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

    auto RandomDiffuseKind = [&]() -> GDiffuseKind {
        int aRand = Random::Get(3);
        if (aRand == 0) { return GDiffuseKind::kA; }
        if (aRand == 1) { return GDiffuseKind::kB; }
        return GDiffuseKind::kC;
    };
    
    auto TypeSymbol = [&](GARXType pType) -> GSymbol {
        switch (pType) {
            case GARXType::kStreamCurrent: return aStreamCurrent;
            case GARXType::kStreamPrevious: return aStreamPrevious;
            case GARXType::kStreamScatter: return aStreamScatter;
            case GARXType::kStreamCross: return aStreamCross;

            case GARXType::kSecretCurrent: return aSecretCurrent;
            case GARXType::kSecretPrevious: return aSecretPrevious;
            case GARXType::kSecretScatter: return aSecretScatter;

            case GARXType::kCarry: return aCarry;

            case GARXType::kWandererA: return aWandererA;
            case GARXType::kWandererB: return aWandererB;
            case GARXType::kWandererC: return aWandererC;
            case GARXType::kWandererD: return aWandererD;
            case GARXType::kWandererE: return aWandererE;
            case GARXType::kWandererF: return aWandererF;

            case GARXType::kOrbiterA: return aOrbiterA;
            case GARXType::kOrbiterB: return aOrbiterB;
            case GARXType::kOrbiterC: return aOrbiterC;
            case GARXType::kOrbiterD: return aOrbiterD;
            case GARXType::kOrbiterE: return aOrbiterE;
            case GARXType::kOrbiterF: return aOrbiterF;

            default:
                printf("fatal: CSPKDF::Bake invalid GARXType=%s\n",
                       GARXSkeleton::GetTypeName(pType));
                exit(0);
        }
    };

    auto TypeExpr = [&](GARXType pType) -> GExpr {
        return GExpr::Symbol(TypeSymbol(pType));
    };

    auto GetRoundMaterial = [&](CSPKDFSaltPhase pPhase) -> const GDomainSeedRoundMaterial& {
        switch (pPhase) {
            case CSPKDFSaltPhase::kOrbiterAssign: return pDomainSaltSet.mOrbiter;
            case CSPKDFSaltPhase::kOrbiterUpdate: return pDomainSaltSet.mOrbiter;
            case CSPKDFSaltPhase::kWandererUpdate: return pDomainSaltSet.mWanderer;
            default:
                printf("fatal: CSPKDF::Bake invalid salt phase=%d\n",
                       static_cast<int>(pPhase));
                exit(0);
        }
    };

    auto SaltLaneSymbol = [&](CSPKDFSaltPhase pPhase, int pSaltLaneIndex) -> GSymbol {
        if (pSaltLaneIndex < 0 || pSaltLaneIndex >= 6) {
            printf("fatal: CSPKDF::Bake invalid salt lane=%d\n",
                   pSaltLaneIndex);
            exit(0);
        }

        const GDomainSeedRoundMaterial &aMaterial = GetRoundMaterial(pPhase);
        switch (pSaltLaneIndex) {
            case 0: return aMaterial.mSaltA;
            case 1: return aMaterial.mSaltB;
            case 2: return aMaterial.mSaltC;
            case 3: return aMaterial.mSaltD;
            case 4: return aMaterial.mSaltE;
            case 5: return aMaterial.mSaltF;
            default:
                printf("fatal: CSPKDF::Bake invalid salt lane=%d\n",
                       pSaltLaneIndex);
                exit(0);
        }
    };

    auto MakeLoopKeyExpr = [&](const GARXDatum &pDatum,
                               CSPKDFSaltPhase pPhase) -> GExpr {

        if (pDatum.mOffsetAmount < 0) {
            printf("fatal: CSPKDF::Bake loop key has invalid offset\n");
            exit(0);
        }

        GSymbol aSalt = SaltLaneSymbol(pPhase, pDatum.mSaltLaneIndex);

        return GQuick::MakeReadBufferOffsetExpressionDirected(
            aSalt,
            pLoopIndex,
            pDatum.mIsLoopIndexInverted,
            static_cast<std::uint32_t>(pDatum.mOffsetAmount)
        );
    };

    auto MakeDatumExpr = [&](const GARXDatum &pDatum,
                             CSPKDFSaltPhase pPhase,
                             std::size_t pHotIndex) -> GExpr {
        switch (pDatum.mKind) {
            case GARXDatumKind::kType:
                return GQuickARX::MaybeRotL64(TypeExpr(pDatum.mType), pDatum.mRotationAmount);
            case GARXDatumKind::kLoopKey:
                return MakeLoopKeyExpr(pDatum, pPhase);
            case GARXDatumKind::kPlugKey:
                return MakeLoopKeyExpr(pDatum, pPhase);
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
    
    auto MakeStatementTerms = [&](const GARXStatementPlan &pStatement,
                                  CSPKDFSaltPhase pPhase,
                                  std::size_t pHotIndex) -> std::vector<GExpr> {
        std::vector<GExpr> aTerms;
        for (const GARXDatum &aDatum: pStatement.mDatums) {
            if (aDatum.mKind == GARXDatumKind::kHotMul) { continue; }
            aTerms.push_back(MakeDatumExpr(aDatum, pPhase, pHotIndex));
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
                                   CSPKDFSaltPhase pPhase,
                                   std::size_t pHotIndex) -> bool {
        const std::vector<GExpr> aTerms = MakeStatementTerms(pStatement, pPhase, pHotIndex);
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
        
        EmitIngressLane(aStreamCurrent,
                        pPassPlan->mStreamInputBlend,
                        pPublicIngressSourceA,
                        pPublicIngressSourceB,
                        pPublicIngressSourceC,
                        pPublicIngressSourceD,
                        pPublicIngressDomainWord,
                        GDiffuseKind::kA);
        
        EmitIngressLane(aSecretCurrent,
                        pPassPlan->mSecretInputBlend,
                        pPrivateIngressSourceA,
                        pPrivateIngressSourceB,
                        pPrivateIngressSourceC,
                        pPrivateIngressSourceD,
                        pPrivateIngressDomainWord,
                        GDiffuseKind::kB);
        
        EmitIngressLane(aStreamCross,
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

                EmitAssignStatement(*aStatement,
                                    CSPKDFSaltPhase::kOrbiterAssign,
                                    aSeedHotIndex);
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
            
            EmitAssignStatement(*aLeadStatement,
                                CSPKDFSaltPhase::kOrbiterUpdate,
                                aLeadHotIndex);
            EmitAssignStatement(*aFeedbackStatement,
                                CSPKDFSaltPhase::kOrbiterUpdate,
                                aFeedbackHotIndex);
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
    
    auto EmitWanderer = [&]() -> bool {
        
        std::size_t aWandererHotIndex = 18;

        for (GARXStatementGroup *aGroup: pPassPlan->mGroups) {
            if (aGroup == nullptr) {
                printf("fatal: CSPKDF::Bake null group in Wanderer walk\n");
                exit(0);
            }

            if (aGroup->mGroupType != GARXGroupType::kWanderer) {
                continue;
            }

            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                if (aStatement == nullptr) {
                    printf("fatal: CSPKDF::Bake null statement in Wanderer group\n");
                    exit(0);
                }

                if (aStatement->mStatementType != GARXStatementType::kWanderer) {
                    printf("fatal: CSPKDF::Bake unexpected statement in Wanderer group: %s\n",
                           GARXSkeleton::GetStatementKindName(aStatement->mStatementType));
                    exit(0);
                }

            }
        }
        
        for (GARXStatementGroup *aGroup: pPassPlan->mGroups) {
            if (aGroup == nullptr) {
                printf("fatal: CSPKDF::Bake null group in Wanderer walk\n");
                exit(0);
            }
            
            if (aGroup->mGroupType != GARXGroupType::kWanderer) {
                continue;
            }

            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                if (aStatement == nullptr) {
                    printf("fatal: CSPKDF::Bake null statement in Wanderer group\n");
                    exit(0);
                }
                
                if (aStatement->mStatementType != GARXStatementType::kWanderer) {
                    printf("fatal: CSPKDF::Bake unexpected statement in Wanderer group: %s\n",
                           GARXSkeleton::GetStatementKindName(aStatement->mStatementType));
                    exit(0);
                }

                EmitAssignStatement(*aStatement,
                                    CSPKDFSaltPhase::kWandererUpdate,
                                    aWandererHotIndex);
                aWandererHotIndex++;
            }
        }
        
        if (aWandererHotIndex != 24) {
            printf("fatal: CSPKDF::Bake expected 6 Wanderer statements, got %zu\n",
                   aWandererHotIndex - 18);
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
        
        GExpr aExpr = GExpr::Add(GExpr::Symbol(aCarry),
                                 MakeCarryPairExpr(aCarryPlan.mPairA));
        
        aExpr = GExpr::Add(aExpr, MakeCarryPairExpr(aCarryPlan.mPairB));
        aExpr = GExpr::Add(aExpr, MakeCarryPairExpr(aCarryPlan.mPairC));
        
        aExpr = GExpr::Add(
            aExpr,
            GQuickARX::RotL64(GExpr::Symbol(aSecretCurrent),
                              aCarryPlan.mSecretCurrentRotation)
        );
        
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(aCarry, aExpr)
        );
        
        GExpr aMul = GExpr::Mul(
            GExpr::Symbol(aCarry),
            GQuickARX::HotMul(pHotPack, 24)
        );
        
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(
                aCarry,
                GQuickARX::RotL64(aMul, aCarryPlan.mMulRotation)
            )
        );
        
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(
                aCarry,
                GExpr::Xor(
                    GExpr::Symbol(aCarry),
                    GExpr::ShiftR(GExpr::Symbol(aCarry),
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
            GExpr::Symbol(aSecretScatter),
            GExpr::Symbol(aCarry),
            RandomDiffuseKind()
        );
    };
    
    auto EmitScatterStatement = [&]() {
        GExpr aStreamScatterExpr = MakeStreamScatterExpr();
        pStatements->push_back(GQuick::MakeAssignVariableStatement(aStreamScatter,
                                                                   aStreamScatterExpr));

        GExpr aSecretScatterExpr = MakeSecretScatterExpr();
        pStatements->push_back(GQuick::MakeAssignVariableStatement(aSecretScatter,
                                                                   aSecretScatterExpr));
    };
    
    auto EmitCrushStatement = [&]() -> bool {
        
        GExpr aCrushExpr = MakeCrushExpr();

        //
        // Hidden recurrence value.
        // This is also the value written to the byte lane after final 64-bit diffuse.
        //
        pStatements->push_back(
            GQuick::MakeAssignVariableStatement(aSecretCurrent,
                                                aCrushExpr)
        );

        if (pDestWriteInverted) {
            pStatements->push_back(
                GQuick::MakeAssignDestStatementInverted(pDest,
                                                        pLoopIndex,
                                                        aSecretCurrent)
            );
        } else {
            pStatements->push_back(
                GQuick::MakeAssignDestStatement(pDest,
                                                pLoopIndex,
                                                aSecretCurrent)
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
    
    if (EmitWanderer() == false) {
        return false;
    }
    
    pStatements->push_back(GStatement::Comment(""));

    EmitCarryStatement();

    return true;
}

#endif

bool CSPKDF::Bake(GARXPassPlan *,
                  
                  GSymbol,
                  bool,
                  
                  GSymbol,
                  
                  GExpr,
                  GExpr,
                  GExpr,
                  GExpr,
                  
                  GExpr,
                  GExpr,
                  GExpr,
                  GExpr,
                  
                  GExpr,
                  GExpr,
                  GExpr,
                  GExpr,
                  
                  GExpr,
                  GExpr,
                  GExpr,
                  
                  GSymbol,
                  GSymbol,
                  GSymbol,
                  GSymbol,
                  
                  GSymbol,
                  GSymbol,
                  GSymbol,
                  GSymbol,
                  
                  const GDomainSaltSet &,
                  
                  GHotPack,
                  
                  std::vector<GStatement> *,
                  std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = "CSPKDF is deprecated";
    }
    return false;
}
