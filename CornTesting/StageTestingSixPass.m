#import <XCTest/XCTest.h>

#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryStarter.hpp"
#include "GSeedRunStageConfigValidator.hpp"
#include "GSymbol.hpp"

#include <cstdio>
#include <string>
#include <vector>

namespace {

using Slot = TwistWorkSpaceSlot;

const GPassFactoryMidstage::SlotArray1 kInputs = {
    Slot::kSourceLane,
};

const GPassFactoryStarter::SlotArray2 kTwoInputs = {
    Slot::kSourceLane,
    Slot::kNonceLane,
};

const GPassFactoryStarter::SlotArray3 kThreeInputs = {
    Slot::kSourceLane,
    Slot::kKeyRowReadA,
    Slot::kKeyRowReadB,
};

const GPassFactoryStarter::SlotArray4 kTwistResiduals = {
    Slot::kParamCrossA,
    Slot::kParamCrossB,
    Slot::kParamCrossC,
    Slot::kParamCrossD,
};

const GPassFactoryMidstage::SlotArray2 kWarmUpLanes = {
    Slot::kPlasmaLaneA,
    Slot::kPlasmaLaneB,
};

const GPassFactoryMidstage::SlotArray4 kDestinations = {
    Slot::kWaterLaneA,
    Slot::kWaterLaneB,
    Slot::kWaterLaneC,
    Slot::kWaterLaneD,
};

const GPassFactoryMidstage::SlotArray6 kExpectedDestinations =
    GPassFactoryMidstage::Concat(kWarmUpLanes, kDestinations);

struct PassSourceChoice {
    Slot                                        mIngressSecond;
    Slot                                        mCrossFirst;
    Slot                                        mCrossSecond;
};

GSeedRunStageConfig BaseConfig() {
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageTestingSixPass";
    aConfig.mBatchName = "brute_force_one_input_starter";
    aConfig.mWarmupDestinationCount =
        static_cast<int>(kWarmUpLanes.size());
    aConfig.mExpectedSkeletonCount =
        static_cast<int>(kExpectedDestinations.size());
    aConfig.mHotPackCount =
        static_cast<int>(kExpectedDestinations.size());
    aConfig.mBindDuplicateSourceSlots = true;
    aConfig.mSlices =
        GPassFactoryStarter::SixPassOneInputStarterSlices(
            kInputs,
            kWarmUpLanes,
            kDestinations,
            0U);
    return aConfig;
}

GSeedRunStageConfig BaseTwoInputConfig(const std::size_t pCandidateIndex) {
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageTestingSixPassTwoInput";
    aConfig.mBatchName = "brute_force_two_input_starter";
    aConfig.mWarmupDestinationCount =
        static_cast<int>(kWarmUpLanes.size());
    aConfig.mExpectedSkeletonCount =
        static_cast<int>(kExpectedDestinations.size());
    aConfig.mHotPackCount =
        static_cast<int>(kExpectedDestinations.size());
    aConfig.mUsesSpecialSixPassStarterGraph = true;
    aConfig.mSlices =
        GPassFactoryStarter::KDF_A_AStarterSlices(
            kTwoInputs,
            kWarmUpLanes,
            kDestinations,
            pCandidateIndex);
    return aConfig;
}

GSeedRunStageConfig BaseSeedTwoInputConfig(
    const std::size_t pCandidateIndex) {
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageTestingSeedStarter";
    aConfig.mBatchName = "seed_two_input_starter";
    aConfig.mWarmupDestinationCount =
        static_cast<int>(kWarmUpLanes.size());
    aConfig.mExpectedSkeletonCount =
        static_cast<int>(kExpectedDestinations.size());
    aConfig.mHotPackCount =
        static_cast<int>(kExpectedDestinations.size());
    aConfig.mUsesSpecialSixPassStarterGraph = true;
    aConfig.mSlices =
        GPassFactoryStarter::Seed_AStarterSlices(
            kTwoInputs,
            kWarmUpLanes,
            kDestinations,
            pCandidateIndex);
    return aConfig;
}

GSeedRunStageConfig BaseTwistThreeInputConfig(
    const std::size_t pCandidateIndex) {
    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageTestingTwistStarter";
    aConfig.mBatchName = "twist_three_input_starter";
    aConfig.mWarmupDestinationCount =
        static_cast<int>(kWarmUpLanes.size());
    aConfig.mExpectedSkeletonCount =
        static_cast<int>(kExpectedDestinations.size());
    aConfig.mHotPackCount =
        static_cast<int>(kExpectedDestinations.size());
    aConfig.mUsesSpecialSixPassTwistStarterGraph = true;
    aConfig.mSlices =
        GPassFactoryStarter::Twist_AStarterSlices(
            kThreeInputs,
            kTwistResiduals,
            kWarmUpLanes,
            kDestinations,
            pCandidateIndex);
    return aConfig;
}

std::vector<PassSourceChoice> MakePassSourceChoices(
    const std::vector<Slot> &pAvailableSources,
    const Slot pPreviousDestination) {
    std::vector<PassSourceChoice> aChoices;

    for (const Slot aIngressSecond : pAvailableSources) {
        // The previous destination is already first on ingress. Preserve the
        // factory's two-distinct-sources ingress shape after the bootstrap.
        if (aIngressSecond == pPreviousDestination) {
            continue;
        }

        for (const Slot aCrossFirst : pAvailableSources) {
            for (const Slot aCrossSecond : pAvailableSources) {
                // SixPassOneInputStarterSlices never duplicates a source
                // within one side after its mandatory one-source bootstrap.
                // A lane may still appear once on ingress and once on cross,
                // as the factory's final pass already demonstrates.
                if (aCrossFirst == aCrossSecond) {
                    continue;
                }

                aChoices.push_back({
                    aIngressSecond,
                    aCrossFirst,
                    aCrossSecond,
                });
            }
        }
    }

    return aChoices;
}

void SetPassSources(GSeedRunStageSliceSpec *pSlice,
                    const Slot pPreviousDestination,
                    const PassSourceChoice &pChoice) {
    if (pSlice == nullptr) {
        return;
    }

    pSlice->mIngressSources = {
        pPreviousDestination,
        pChoice.mIngressSecond,
    };
    pSlice->mCrossSources = {
        pChoice.mCrossFirst,
        pChoice.mCrossSecond,
    };
}

bool SlicesEqual(const std::vector<GSeedRunStageSliceSpec> &pLeft,
                 const std::vector<GSeedRunStageSliceSpec> &pRight) {
    if (pLeft.size() != pRight.size()) {
        return false;
    }

    for (std::size_t aIndex = 0U; aIndex < pLeft.size(); ++aIndex) {
        const GSeedRunStageSliceSpec &aLeft = pLeft[aIndex];
        const GSeedRunStageSliceSpec &aRight = pRight[aIndex];

        if ((aLeft.mIngressSources != aRight.mIngressSources) ||
            (aLeft.mCrossSources != aRight.mCrossSources) ||
            (aLeft.mDest != aRight.mDest) ||
            (aLeft.mDestWriteInverted != aRight.mDestWriteInverted) ||
            (aLeft.mIsLastIngressDirectionLocked !=
             aRight.mIsLastIngressDirectionLocked) ||
            (aLeft.mIsLastCrossDirectionLocked !=
             aRight.mIsLastCrossDirectionLocked)) {
            return false;
        }
    }

    return true;
}

void PrintSources(const std::vector<Slot> &pSources) {
    printf("{");
    for (std::size_t aIndex = 0U; aIndex < pSources.size(); ++aIndex) {
        printf("%s%s",
               BufName(pSources[aIndex]).c_str(),
               ((aIndex + 1U) < pSources.size()) ? ", " : "");
    }
    printf("}");
}

void PrintVariation(
    const std::size_t pVariationIndex,
    const std::size_t pExaminedIndex,
    const std::vector<GSeedRunStageSliceSpec> &pSlices) {
    printf("\n");
    printf("============================================================\n");
    printf("SIX-PASS VARIATION %zu (examined candidate %zu)\n",
           pVariationIndex,
           pExaminedIndex);
    printf("============================================================\n");

    for (std::size_t aIndex = 0U; aIndex < pSlices.size(); ++aIndex) {
        const GSeedRunStageSliceSpec &aSlice = pSlices[aIndex];
        printf("Pass %zu\n", aIndex + 1U);
        printf("    Ingress ");
        PrintSources(aSlice.mIngressSources);
        printf("  last_locked=%s\n",
               aSlice.mIsLastIngressDirectionLocked ? "true" : "false");
        printf("    Cross   ");
        PrintSources(aSlice.mCrossSources);
        printf("  last_locked=%s\n",
               aSlice.mIsLastCrossDirectionLocked ? "true" : "false");
        printf("    Dest    %s  inverted=%s\n",
               BufName(aSlice.mDest).c_str(),
               aSlice.mDestWriteInverted ? "true" : "false");
    }

    fflush(stdout);
}

} // namespace

@interface StageTestingSixPass : XCTestCase
@end

@implementation StageTestingSixPass

- (void)testBruteForceOneInputStarterVariations {
    GSeedRunStageConfig aConfig = BaseConfig();
    const std::vector<GSeedRunStageSliceSpec> aFactorySlices =
        aConfig.mSlices;

    //
    // Pass 3 has exactly three available sources. The previous destination
    // is required at ingress[0], the first warm-up is required at cross[0],
    // and the sole external source fills both remaining positions.
    //
    const std::vector<PassSourceChoice> aPassThreeChoices = {
        {
            kInputs[0],
            kWarmUpLanes[0],
            kInputs[0],
        },
    };

    //
    // Passes 4-6 use every ordered, two-wide ingress/cross arrangement that:
    //   1. Reads only lanes already available at that pass.
    //   2. Keeps the previous destination first on ingress.
    //   3. Does not duplicate a lane within ingress or within cross.
    //   4. Preserves the factory's direction-lock pattern.
    //
    const std::vector<PassSourceChoice> aPassFourChoices =
        MakePassSourceChoices({
            kInputs[0],
            kWarmUpLanes[0],
            kWarmUpLanes[1],
            kDestinations[0],
        }, kDestinations[0]);

    const std::vector<PassSourceChoice> aPassFiveChoices =
        MakePassSourceChoices({
            kInputs[0],
            kWarmUpLanes[0],
            kWarmUpLanes[1],
            kDestinations[0],
            kDestinations[1],
        }, kDestinations[1]);

    const std::vector<PassSourceChoice> aPassSixChoices =
        MakePassSourceChoices({
            kInputs[0],
            kWarmUpLanes[0],
            kWarmUpLanes[1],
            kDestinations[0],
            kDestinations[1],
            kDestinations[2],
        }, kDestinations[2]);

    const std::size_t aExpectedCandidateCount =
        aPassThreeChoices.size() *
        aPassFourChoices.size() *
        aPassFiveChoices.size() *
        aPassSixChoices.size();

    printf("\n");
    printf("Brute-forcing %zu SixPassOneInputStarterSlices lane graphs.\n",
           aExpectedCandidateCount);
    printf("Direction-lock flags and two-wide context shapes remain fixed.\n");

    std::size_t aExaminedCount = 0U;
    std::size_t aValidCount = 0U;
    bool aFoundFactoryVariation = false;

    for (const PassSourceChoice &aPassThree : aPassThreeChoices) {
        SetPassSources(&aConfig.mSlices[2],
                       kWarmUpLanes[1],
                       aPassThree);

        for (const PassSourceChoice &aPassFour : aPassFourChoices) {
            SetPassSources(&aConfig.mSlices[3],
                           kDestinations[0],
                           aPassFour);

            for (const PassSourceChoice &aPassFive : aPassFiveChoices) {
                SetPassSources(&aConfig.mSlices[4],
                               kDestinations[1],
                               aPassFive);

                for (const PassSourceChoice &aPassSix : aPassSixChoices) {
                    SetPassSources(&aConfig.mSlices[5],
                                   kDestinations[2],
                                   aPassSix);
                    ++aExaminedCount;

                    std::string aErrorMessage;
                    const bool aWasValid =
                        GSeedRunStageConfigValidator::ValidateStarter(
                            aConfig,
                            GPassFactoryMidstage::ToVector(kInputs),
                            GPassFactoryMidstage::ToVector(kExpectedDestinations),
                            &aErrorMessage);
                    if (!aWasValid) {
                        continue;
                    }

                    ++aValidCount;
                    aFoundFactoryVariation =
                        aFoundFactoryVariation ||
                        SlicesEqual(aConfig.mSlices, aFactorySlices);
                    PrintVariation(aValidCount,
                                   aExaminedCount,
                                   aConfig.mSlices);
                }
            }
        }
    }

    printf("\n");
    printf("============================================================\n");
    printf("SIX-PASS BRUTE-FORCE SUMMARY\n");
    printf("Examined: %zu\n", aExaminedCount);
    printf("Valid:    %zu\n", aValidCount);
    printf("Rejected: %zu\n", aExaminedCount - aValidCount);
    printf("Factory schedule discovered: %s\n",
           aFoundFactoryVariation ? "yes" : "no");
    printf("============================================================\n");

    XCTAssertEqual(aExaminedCount, aExpectedCandidateCount);
    XCTAssertEqual(aValidCount, static_cast<std::size_t>(1U));
    XCTAssertTrue(aFoundFactoryVariation);
}

- (void)testKDF_A_AStarterCandidates {
    setvbuf(stdout, nullptr, _IONBF, 0);

    const std::size_t aCandidateCount =
        GPassFactoryStarter::kKDF_A_AStarterCandidateCount;
    std::size_t aGeneratedCount = 0U;
    std::size_t aValidatedCount = 0U;
    std::vector<std::vector<GSeedRunStageSliceSpec>> aCandidates;
    std::vector<std::vector<GSeedRunStageSliceSpec>> aUniqueCandidates;

    printf("\n");
    printf("============================================================\n");
    printf("KDF_A_A STARTER CANDIDATES\n");
    printf("Inputs: ");
    PrintSources(GPassFactoryMidstage::ToVector(kTwoInputs));
    printf("\n");
    printf("Every factory candidate follows.\n");
    printf("============================================================\n");

    for (std::size_t aCandidateIndex = 0U;
         aCandidateIndex < aCandidateCount;
         ++aCandidateIndex) {
        GSeedRunStageConfig aConfig =
            BaseTwoInputConfig(aCandidateIndex);

        ++aGeneratedCount;
        std::string aErrorMessage;
        const bool aWasValid =
            GSeedRunStageConfigValidator::ValidateStarter(
                aConfig,
                GPassFactoryMidstage::ToVector(kTwoInputs),
                GPassFactoryMidstage::ToVector(kExpectedDestinations),
                &aErrorMessage);
        if (!aWasValid) {
            printf("Candidate %zu failed ValidateStarter: %s\n",
                   aCandidateIndex,
                   aErrorMessage.c_str());
            continue;
        }

        for (const GSeedRunStageSliceSpec &aSlice :
             aConfig.mSlices) {
            XCTAssertLessThanOrEqual(
                aSlice.mIngressSources.size(),
                static_cast<std::size_t>(4U));
            XCTAssertLessThanOrEqual(
                aSlice.mCrossSources.size(),
                static_cast<std::size_t>(4U));
        }

        ++aValidatedCount;
        PrintVariation(aCandidateIndex,
                       aCandidateIndex,
                       aConfig.mSlices);
        aCandidates.push_back(aConfig.mSlices);

        bool aWasAlreadyPresent = false;
        for (const std::vector<GSeedRunStageSliceSpec> &aExisting :
             aUniqueCandidates) {
            if (SlicesEqual(aExisting, aConfig.mSlices)) {
                aWasAlreadyPresent = true;
                break;
            }
        }
        if (!aWasAlreadyPresent) {
            aUniqueCandidates.push_back(aConfig.mSlices);
        }
    }

    const GSeedRunStageConfig aFirstConfig =
        BaseTwoInputConfig(0U);
    const GSeedRunStageConfig aWrappedConfig =
        BaseTwoInputConfig(aCandidateCount);

    printf("\n");
    printf("============================================================\n");
    printf("KDF_A_A STARTER CANDIDATE SUMMARY\n");
    printf("Generated: %zu\n", aGeneratedCount);
    printf("Validated: %zu\n", aValidatedCount);
    printf("Distinct schedules: %zu\n", aUniqueCandidates.size());
    printf("Candidate %zu wraps to candidate 0: %s\n",
           aCandidateCount,
           SlicesEqual(aFirstConfig.mSlices,
                       aWrappedConfig.mSlices) ? "yes" : "no");
    printf("============================================================\n");

    XCTAssertEqual(aGeneratedCount, aCandidateCount);
    XCTAssertEqual(aValidatedCount, aCandidateCount);
    XCTAssertEqual(aCandidates.size(), aCandidateCount);
    XCTAssertEqual(aUniqueCandidates.size(), aCandidateCount);
    XCTAssertEqual(aCandidates[0][2].mIngressSources[1],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[17][2].mIngressSources[1],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[18][2].mIngressSources[1],
                   Slot::kNonceLane);
    XCTAssertEqual(aCandidates[8][3].mIngressSources[2],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[9][3].mIngressSources[2],
                   Slot::kNonceLane);
    XCTAssertEqual(aCandidates[0][4].mCrossSources[1],
                   Slot::kNonceLane);
    XCTAssertEqual(aCandidates[3][4].mCrossSources[1],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[6][4].mCrossSources[1],
                   kWarmUpLanes[0]);
    XCTAssertEqual(aCandidates[0][5].mCrossSources[1],
                   Slot::kNonceLane);
    XCTAssertEqual(aCandidates[1][5].mCrossSources[1],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[2][5].mCrossSources[1],
                   kWarmUpLanes[1]);
    XCTAssertTrue(SlicesEqual(aFirstConfig.mSlices,
                              aWrappedConfig.mSlices));
}

- (void)testSeed_AStarterCandidates {
    setvbuf(stdout, nullptr, _IONBF, 0);

    const std::size_t aCandidateCount =
        GPassFactoryStarter::kSeed_AStarterCandidateCount;
    std::size_t aGeneratedCount = 0U;
    std::size_t aValidatedCount = 0U;
    std::vector<std::vector<GSeedRunStageSliceSpec>> aCandidates;
    std::vector<std::vector<GSeedRunStageSliceSpec>> aUniqueCandidates;

    printf("\n");
    printf("============================================================\n");
    printf("SEED_A STARTER CANDIDATES\n");
    printf("Inputs: ");
    PrintSources(GPassFactoryMidstage::ToVector(kTwoInputs));
    printf("\n");
    printf("Every factory candidate follows.\n");
    printf("============================================================\n");

    for (std::size_t aCandidateIndex = 0U;
         aCandidateIndex < aCandidateCount;
         ++aCandidateIndex) {
        GSeedRunStageConfig aConfig =
            BaseSeedTwoInputConfig(aCandidateIndex);

        ++aGeneratedCount;
        std::string aErrorMessage;
        const bool aWasValid =
            GSeedRunStageConfigValidator::ValidateStarter(
                aConfig,
                GPassFactoryMidstage::ToVector(kTwoInputs),
                GPassFactoryMidstage::ToVector(kExpectedDestinations),
                &aErrorMessage);
        if (!aWasValid) {
            printf("Candidate %zu failed ValidateStarter: %s\n",
                   aCandidateIndex,
                   aErrorMessage.c_str());
            continue;
        }

        for (const GSeedRunStageSliceSpec &aSlice :
             aConfig.mSlices) {
            XCTAssertLessThanOrEqual(
                aSlice.mIngressSources.size(),
                static_cast<std::size_t>(4U));
            XCTAssertLessThanOrEqual(
                aSlice.mCrossSources.size(),
                static_cast<std::size_t>(4U));
        }

        ++aValidatedCount;
        PrintVariation(aCandidateIndex,
                       aCandidateIndex,
                       aConfig.mSlices);
        aCandidates.push_back(aConfig.mSlices);

        bool aWasAlreadyPresent = false;
        for (const std::vector<GSeedRunStageSliceSpec> &aExisting :
             aUniqueCandidates) {
            if (SlicesEqual(aExisting, aConfig.mSlices)) {
                aWasAlreadyPresent = true;
                break;
            }
        }
        if (!aWasAlreadyPresent) {
            aUniqueCandidates.push_back(aConfig.mSlices);
        }
    }

    const GSeedRunStageConfig aFirstConfig =
        BaseSeedTwoInputConfig(0U);
    const GSeedRunStageConfig aWrappedConfig =
        BaseSeedTwoInputConfig(aCandidateCount);

    printf("\n");
    printf("============================================================\n");
    printf("SEED_A STARTER CANDIDATE SUMMARY\n");
    printf("Generated: %zu\n", aGeneratedCount);
    printf("Validated: %zu\n", aValidatedCount);
    printf("Distinct schedules: %zu\n", aUniqueCandidates.size());
    printf("Candidate %zu wraps to candidate 0: %s\n",
           aCandidateCount,
           SlicesEqual(aFirstConfig.mSlices,
                       aWrappedConfig.mSlices) ? "yes" : "no");
    printf("============================================================\n");

    XCTAssertEqual(aGeneratedCount, aCandidateCount);
    XCTAssertEqual(aValidatedCount, aCandidateCount);
    XCTAssertEqual(aCandidates.size(), aCandidateCount);
    XCTAssertEqual(aUniqueCandidates.size(), aCandidateCount);
    XCTAssertEqual(aCandidates[0][2].mIngressSources[1],
                   Slot::kNonceLane);
    XCTAssertEqual(aCandidates[17][2].mIngressSources[1],
                   Slot::kNonceLane);
    XCTAssertEqual(aCandidates[18][2].mIngressSources[1],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[8][3].mIngressSources[2],
                   Slot::kNonceLane);
    XCTAssertEqual(aCandidates[9][3].mIngressSources[2],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[0][4].mCrossSources[1],
                   kWarmUpLanes[0]);
    XCTAssertEqual(aCandidates[3][4].mCrossSources[1],
                   Slot::kNonceLane);
    XCTAssertEqual(aCandidates[6][4].mCrossSources[1],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[0][5].mCrossSources[1],
                   kWarmUpLanes[1]);
    XCTAssertEqual(aCandidates[1][5].mCrossSources[1],
                   Slot::kNonceLane);
    XCTAssertEqual(aCandidates[2][5].mCrossSources[1],
                   Slot::kSourceLane);
    XCTAssertTrue(SlicesEqual(aFirstConfig.mSlices,
                              aWrappedConfig.mSlices));
}

- (void)testTwist_AStarterCandidates {
    setvbuf(stdout, nullptr, _IONBF, 0);

    const std::size_t aCandidateCount =
        GPassFactoryStarter::kTwist_AStarterCandidateCount;
    std::size_t aValidatedCount = 0U;
    std::vector<std::vector<GSeedRunStageSliceSpec>> aCandidates;
    std::vector<std::vector<GSeedRunStageSliceSpec>> aUniqueCandidates;

    printf("\n");
    printf("============================================================\n");
    printf("TWIST_A STARTER CANDIDATES\n");
    printf("Inputs: ");
    PrintSources(GPassFactoryMidstage::ToVector(kThreeInputs));
    printf("\n");
    printf("Every factory candidate follows.\n");
    printf("============================================================\n");

    for (std::size_t aCandidateIndex = 0U;
         aCandidateIndex < aCandidateCount;
         ++aCandidateIndex) {
        GSeedRunStageConfig aConfig =
            BaseTwistThreeInputConfig(aCandidateIndex);

        std::string aErrorMessage;
        const bool aWasValid =
            GSeedRunStageConfigValidator::ValidateStarterWithResiduals(
                aConfig,
                GPassFactoryMidstage::ToVector(kThreeInputs),
                GPassFactoryMidstage::ToVector(kTwistResiduals),
                GPassFactoryMidstage::ToVector(kExpectedDestinations),
                &aErrorMessage);
        if (!aWasValid) {
            printf("Candidate %zu failed ValidateStarter: %s\n",
                   aCandidateIndex,
                   aErrorMessage.c_str());
            continue;
        }

        if (aConfig.mUsesSpecialSixPassTwistStarterGraph) {
            for (const GSeedRunStageSliceSpec &aSlice :
                 aConfig.mSlices) {
                XCTAssertLessThanOrEqual(
                    aSlice.mIngressSources.size(),
                    static_cast<std::size_t>(4U));
                XCTAssertLessThanOrEqual(
                    aSlice.mCrossSources.size(),
                    static_cast<std::size_t>(4U));
            }
        }

        ++aValidatedCount;
        PrintVariation(aCandidateIndex,
                       aCandidateIndex,
                       aConfig.mSlices);
        aCandidates.push_back(aConfig.mSlices);

        bool aWasAlreadyPresent = false;
        for (const std::vector<GSeedRunStageSliceSpec> &aExisting :
             aUniqueCandidates) {
            if (SlicesEqual(aExisting, aConfig.mSlices)) {
                aWasAlreadyPresent = true;
                break;
            }
        }
        if (!aWasAlreadyPresent) {
            aUniqueCandidates.push_back(aConfig.mSlices);
        }
    }

    const GSeedRunStageConfig aFirstConfig =
        BaseTwistThreeInputConfig(0U);
    const GSeedRunStageConfig aWrappedConfig =
        BaseTwistThreeInputConfig(aCandidateCount);

    printf("\n");
    printf("============================================================\n");
    printf("TWIST_A STARTER CANDIDATE SUMMARY\n");
    printf("Generated: %zu\n", aCandidateCount);
    printf("Validated: %zu\n", aValidatedCount);
    printf("Distinct schedules: %zu\n", aUniqueCandidates.size());
    printf("Candidate %zu wraps to candidate 0: %s\n",
           aCandidateCount,
           SlicesEqual(aFirstConfig.mSlices,
                       aWrappedConfig.mSlices) ? "yes" : "no");
    printf("============================================================\n");

    XCTAssertEqual(aValidatedCount, aCandidateCount);
    XCTAssertEqual(aCandidates.size(), aCandidateCount);
    XCTAssertEqual(aUniqueCandidates.size(), aCandidateCount);

    // The four residuals fill the earliest shortest contexts first.
    XCTAssertEqual(aCandidates[0][0].mIngressSources[2],
                   Slot::kParamCrossA);
    XCTAssertEqual(aCandidates[0][0].mCrossSources[2],
                   Slot::kParamCrossB);
    XCTAssertEqual(aCandidates[0][1].mIngressSources[2],
                   Slot::kParamCrossC);
    XCTAssertEqual(aCandidates[0][1].mCrossSources[2],
                   Slot::kParamCrossD);

    // Pass 3 is split into two contiguous halves.
    XCTAssertEqual(aCandidates[0][2].mIngressSources[2],
                   Slot::kKeyRowReadA);
    XCTAssertEqual(aCandidates[17][2].mIngressSources[2],
                   Slot::kKeyRowReadA);
    XCTAssertEqual(aCandidates[18][2].mIngressSources[2],
                   Slot::kKeyRowReadB);

    // Pass 4 advances through all-ingress, split, and all-cross shapes.
    XCTAssertEqual(aCandidates[0][3].mIngressSources.size(),
                   static_cast<std::size_t>(4U));
    XCTAssertEqual(aCandidates[0][3].mCrossSources.size(),
                   static_cast<std::size_t>(2U));
    XCTAssertEqual(aCandidates[6][3].mIngressSources.size(),
                   static_cast<std::size_t>(3U));
    XCTAssertEqual(aCandidates[6][3].mCrossSources.size(),
                   static_cast<std::size_t>(3U));
    XCTAssertEqual(aCandidates[12][3].mIngressSources.size(),
                   static_cast<std::size_t>(2U));
    XCTAssertEqual(aCandidates[12][3].mCrossSources.size(),
                   static_cast<std::size_t>(4U));

    // Pass 5 advances through after-source, before-source, and cross shapes.
    XCTAssertEqual(aCandidates[0][4].mIngressSources[2],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[0][4].mIngressSources[3],
                   Slot::kKeyRowReadA);
    XCTAssertEqual(aCandidates[1][4].mIngressSources[3],
                   Slot::kKeyRowReadB);
    XCTAssertEqual(aCandidates[2][4].mIngressSources[2],
                   Slot::kKeyRowReadA);
    XCTAssertEqual(aCandidates[2][4].mIngressSources[3],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[4][4].mCrossSources[2],
                   Slot::kKeyRowReadA);

    // Pass 6 uses the key opposite the pass-5 active key.
    XCTAssertEqual(aCandidates[0][5].mIngressSources[2],
                   Slot::kKeyRowReadB);
    XCTAssertEqual(aCandidates[1][5].mIngressSources[2],
                   Slot::kKeyRowReadA);

    // Source alternates ingress/cross from passes 3 through 6.
    XCTAssertEqual(aCandidates[0][2].mIngressSources[1],
                   Slot::kSourceLane);
    XCTAssertEqual(aCandidates[0][3].mCrossSources[1],
                   Slot::kSourceLane);
    XCTAssertTrue(aCandidates[0][4].HasSource(Slot::kSourceLane));
    XCTAssertEqual(aCandidates[0][5].mCrossSources[2],
                   Slot::kSourceLane);

    XCTAssertTrue(SlicesEqual(aFirstConfig.mSlices,
                              aWrappedConfig.mSlices));
}

@end
