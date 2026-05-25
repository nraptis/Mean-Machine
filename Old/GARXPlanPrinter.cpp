//
//  GARXPlanPrinter.cpp
//  MeanMachine
//
//  Created by Dragon on 5/15/26.
//

#include "GARXPlan.hpp"
#include <cstdio>

static void PrintBlendPlan(const GARXBlendInputPlan &pBlendPlan,
                           const char *pSectionName,
                           const char *pBlendName,
                           bool pIncludeRotations) {
    printf("[%s]\n", pSectionName);
    if (pIncludeRotations) {
        printf("%s = diffuse((rot(thing_a,%d) ^ rot(thing_b,%d)) + (rot(thing_c,%d) ^ rot(thing_d,%d)))\n\n",
               pBlendName,
               pBlendPlan.mRotationA,
               pBlendPlan.mRotationB,
               pBlendPlan.mRotationC,
               pBlendPlan.mRotationD);
    } else {
        printf("%s = diffuse((rot(thing_a,A) ^ rot(thing_b,B)) + (rot(thing_c,C) ^ rot(thing_d,D)))\n\n",
               pBlendName);
    }
}

static void PrintStatementCompact(const GARXStatementPlan &pStatement,
                                  bool pIncludePlugs,
                                  bool pIncludeRotations) {
    if (pStatement.mStatementType == GARXStatementType::kCrush) {
        printf("*crush %s*\n", GARXSkeleton::GetTypeName(pStatement.mTarget));
        return;
    }

    if (pStatement.mStatementType == GARXStatementType::kForwardRotate) {
        if (pStatement.mRotationAmount >= 0) {
            printf("%s <- rot(%s * <hot_mul>, %d)\n",
                   GARXSkeleton::GetTypeName(pStatement.mTarget),
                   GARXSkeleton::GetTypeName(pStatement.mTarget),
                   pStatement.mRotationAmount);
        } else {
            printf("%s <- rot(%s * <hot_mul>)\n",
                   GARXSkeleton::GetTypeName(pStatement.mTarget),
                   GARXSkeleton::GetTypeName(pStatement.mTarget));
        }

        return;
    }

    printf("%s =", GARXSkeleton::GetTypeName(pStatement.mTarget));

    for (std::size_t k = 0; k < pStatement.mDatums.size(); k++) {
        const GARXDatum &aDatum = pStatement.mDatums[k];

        if (k > 0) {
            printf(" +");
        }

        if (aDatum.mKind == GARXDatumKind::kType) {
            if (pIncludeRotations && aDatum.mRotationAmount >= 0) {
                printf(" rot(%s,%d)",
                       GARXSkeleton::GetTypeName(aDatum.mType),
                       aDatum.mRotationAmount);
            } else {
                printf(" %s", GARXSkeleton::GetTypeName(aDatum.mType));
            }
        } else if (aDatum.mKind == GARXDatumKind::kLoopKey) {
            const char *aDirection = aDatum.mIsLoopIndexInverted ? "reverse" : "forward";

            if ((aDatum.mSaltLaneIndex >= 0) &&
                (aDatum.mOffsetAmount >= 0)) {
                printf(" <loop_key:lane=%d,%s,%d>",
                       aDatum.mSaltLaneIndex,
                       aDirection,
                       aDatum.mOffsetAmount);
            } else if (aDatum.mSaltLaneIndex >= 0) {
                printf(" <loop_key:lane=%d,%s>",
                       aDatum.mSaltLaneIndex,
                       aDirection);
            } else if (aDatum.mOffsetAmount >= 0) {
                printf(" <loop_key:%s,%d>",
                       aDirection,
                       aDatum.mOffsetAmount);
            } else {
                printf(" <loop_key:%s>", aDirection);
            }
        } else if (aDatum.mKind == GARXDatumKind::kPlugKey) {
            if (pIncludePlugs) {
                const char *aTypeAName = GARXSkeleton::GetTypeName(aDatum.mPlugTypeA);
                const char *aTypeBName = GARXSkeleton::GetTypeName(aDatum.mPlugTypeB);

                if (aDatum.mSaltLaneIndex >= 0) {
                    if (aDatum.mRotationAmount >= 0) {
                        if (aDatum.mOffsetAmount >= 0) {
                            printf(" <plug_key:lane=%d,rot(%s,%d),%s,+%d>",
                                   aDatum.mSaltLaneIndex,
                                   aTypeAName,
                                   aDatum.mRotationAmount,
                                   aTypeBName,
                                   aDatum.mOffsetAmount);
                        } else {
                            printf(" <plug_key:lane=%d,rot(%s,%d),%s>",
                                   aDatum.mSaltLaneIndex,
                                   aTypeAName,
                                   aDatum.mRotationAmount,
                                   aTypeBName);
                        }
                    } else {
                        if (aDatum.mOffsetAmount >= 0) {
                            printf(" <plug_key:lane=%d,%s,%s,+%d>",
                                   aDatum.mSaltLaneIndex,
                                   aTypeAName,
                                   aTypeBName,
                                   aDatum.mOffsetAmount);
                        } else {
                            printf(" <plug_key:lane=%d,%s,%s>",
                                   aDatum.mSaltLaneIndex,
                                   aTypeAName,
                                   aTypeBName);
                        }
                    }
                } else {
                    if (aDatum.mRotationAmount >= 0) {
                        if (aDatum.mOffsetAmount >= 0) {
                            printf(" <plug_key:rot(%s,%d),%s,+%d>",
                                   aTypeAName,
                                   aDatum.mRotationAmount,
                                   aTypeBName,
                                   aDatum.mOffsetAmount);
                        } else {
                            printf(" <plug_key:rot(%s,%d),%s>",
                                   aTypeAName,
                                   aDatum.mRotationAmount,
                                   aTypeBName);
                        }
                    } else {
                        if (aDatum.mOffsetAmount >= 0) {
                            printf(" <plug_key:%s,%s,+%d>",
                                   aTypeAName,
                                   aTypeBName,
                                   aDatum.mOffsetAmount);
                        } else {
                            printf(" <plug_key:%s,%s>",
                                   aTypeAName,
                                   aTypeBName);
                        }
                    }
                }
            } else {
                printf(" <plug_key>");
            }
        } else if (aDatum.mKind == GARXDatumKind::kHotAdd) {
            printf(" <hot_add>");
        } else if (aDatum.mKind == GARXDatumKind::kHotMul) {
            printf(" <hot_mul>");
        } else {
            printf(" <%s>", GARXSkeleton::GetDatumKindName(aDatum.mKind));
        }
    }

    printf("\n");
}

static void PrintCrushPair(const GARXCrushPairPlan &pPair) {
    if (pPair.mRotateA) {
        printf("(rot(%s,%d) ^ %s)",
               GARXSkeleton::GetTypeName(pPair.mTypeA),
               pPair.mRotationAmount,
               GARXSkeleton::GetTypeName(pPair.mTypeB));
    } else {
        printf("(%s ^ rot(%s,%d))",
               GARXSkeleton::GetTypeName(pPair.mTypeA),
               GARXSkeleton::GetTypeName(pPair.mTypeB),
               pPair.mRotationAmount);
    }
}

static void PrintCrushPlan(const GARXCrushPlan &pCrushPlan) {
    printf("input = diffuse(");
    PrintCrushPair(pCrushPlan.mPairA);
    printf(" + ");
    PrintCrushPair(pCrushPlan.mPairB);
    printf(" + ");
    PrintCrushPair(pCrushPlan.mPairC);
    printf(" + scatter + carry)\n");
    printf("input = mix64_8(input, gate_prism_8_8)\n");
}

void GARXPlan::Print(GARXPlan *pPlan) {
    GARXPlanPrinter::Print(pPlan);
}

void GARXPlan::Print(GARXPlan *pPlan,
                     bool pIncludePlugs,
                     bool pIncludeRotations) {
    GARXPlanPrinter::Print(pPlan, pIncludePlugs, pIncludeRotations);
}

void GARXPlanPrinter::Print(GARXPlan *pPlan) {
    Print(pPlan, true, true);
}

void GARXPlanPrinter::Print(GARXPlan *pPlan,
                            bool pIncludePlugs,
                            bool pIncludeRotations) {
    if (pPlan == nullptr) {
        printf("GARXPlan: null\n");
        return;
    }

    printf("\nGARX PLAN\n");
    printf("=========\n");

    for (std::size_t i = 0; i < pPlan->mPassPlans.size(); i++) {
        GARXPassPlan *aPassPlan = pPlan->mPassPlans[i];
        if (aPassPlan == nullptr) {
            continue;
        }

        printf("\nPASS %zu\n", i);
        printf("------\n\n");

        PrintBlendPlan(aPassPlan->mStreamInputBlend,
                       "stream_input",
                       "stream_input",
                       pIncludeRotations);
        PrintBlendPlan(aPassPlan->mSecretInputBlend,
                       "secret_input",
                       "secret_input",
                       pIncludeRotations);
        PrintBlendPlan(aPassPlan->mCrossInputBlend,
                       "cross_input",
                       "cross_input",
                       pIncludeRotations);
        PrintBlendPlan(aPassPlan->mStreamScatterBlend,
                       "stream_scatter",
                       "stream_scatter",
                       pIncludeRotations);
        PrintBlendPlan(aPassPlan->mSecretScatterBlend,
                       "secret_scatter",
                       "secret_scatter",
                       pIncludeRotations);

        GARXGroupType aPreviousKind = GARXGroupType::kInv;

        for (std::size_t g = 0; g < aPassPlan->mGroups.size(); g++) {
            GARXStatementGroup *aGroup = aPassPlan->mGroups[g];
            if (aGroup == nullptr) {
                continue;
            }

            bool aNeedsBlankLine = false;
            if (g > 0) {
                if (aGroup->mGroupType == GARXGroupType::kForwardTriplet) {
                    aNeedsBlankLine = true;
                } else if (aGroup->mGroupType == GARXGroupType::kCrush) {
                    aNeedsBlankLine = true;
                } else if (aGroup->mGroupType == GARXGroupType::kUnwind &&
                           aPreviousKind != GARXGroupType::kUnwind) {
                    aNeedsBlankLine = true;
                }
            }

            if (aNeedsBlankLine) {
                printf("\n");
            }

            printf("[zone %d: %s]\n",
                   aGroup->mZoneIndex,
                   GARXStatementGroup::GetTypeName(aGroup->mGroupType));

            for (GARXStatementPlan *aStatement: aGroup->mStatements) {
                if (aStatement->mStatementType == GARXStatementType::kCrush) {
                    PrintCrushPlan(aPassPlan->mCrushPlan);
                } else {
                    PrintStatementCompact(*aStatement,
                                          pIncludePlugs,
                                          pIncludeRotations);
                }
            }

            aPreviousKind = aGroup->mGroupType;
        }

        printf("\n");
    }

    printf("\n");
}
