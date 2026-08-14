#import <XCTest/XCTest.h>

#include "GPassFactoryMidstage.hpp"
#include "GPassFactoryTrunk.hpp"
#include "GSeedRunStageConfigValidator.hpp"

#include <string>
#include <utility>
#include <vector>

@interface StageConfigValidatorTesting : XCTestCase
@end

@implementation StageConfigValidatorTesting

- (GSeedRunStageConfig)sixPassConfig {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kEarthLaneA,
        Slot::kEarthLaneB,
        Slot::kEarthLaneC,
        Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aDestinations = {
        Slot::kWindLaneA,
        Slot::kWindLaneB,
        Slot::kWindLaneC,
        Slot::kWindLaneD,
        Slot::kWaterLaneA,
        Slot::kWaterLaneB,
    };

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageConfigValidatorTesting";
    aConfig.mBatchName = "six_pass_source_graph";
    aConfig.mExpectedSkeletonCount =
        static_cast<int>(aDestinations.size());
    aConfig.mHotPackCount =
        static_cast<int>(aDestinations.size());
    aConfig.mSlices =
        GPassFactoryMidstage::SixPassNoResidualSlices(aPrimarySources,
                                              aDestinations);
    return aConfig;
}

- (bool)validateSixPassConfig:(const GSeedRunStageConfig &)pConfig
                    residuals:(const std::vector<TwistWorkSpaceSlot> &)pResiduals
                         error:(std::string *)pErrorMessage {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kEarthLaneA,
        Slot::kEarthLaneB,
        Slot::kEarthLaneC,
        Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray6 aDestinations = {
        Slot::kWindLaneA,
        Slot::kWindLaneB,
        Slot::kWindLaneC,
        Slot::kWindLaneD,
        Slot::kWaterLaneA,
        Slot::kWaterLaneB,
    };

    return GSeedRunStageConfigValidator::ValidateMidstage(
        pConfig,
        GPassFactoryMidstage::ToVector(aPrimarySources),
        pResiduals,
        GPassFactoryMidstage::ToVector(aDestinations),
        pErrorMessage);
}

- (void)testFourInputStageStartsWithLastPrimarySource {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kEarthLaneA,
        Slot::kEarthLaneB,
        Slot::kEarthLaneC,
        Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinations = {
        Slot::kWindLaneA,
        Slot::kWindLaneB,
        Slot::kWindLaneC,
        Slot::kWindLaneD,
    };

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageConfigValidatorTesting";
    aConfig.mBatchName = "four_input_entry";
    aConfig.mExpectedSkeletonCount =
        static_cast<int>(aDestinations.size());
    aConfig.mHotPackCount =
        static_cast<int>(aDestinations.size());
    aConfig.mSlices =
        GPassFactoryMidstage::FourPassNoResidualSlices(aPrimarySources,
                                               aDestinations);

    std::string aErrorMessage;
    const bool aWasValid =
        GSeedRunStageConfigValidator::ValidateMidstage(
            aConfig,
            GPassFactoryMidstage::ToVector(aPrimarySources),
            std::vector<Slot>(),
            GPassFactoryMidstage::ToVector(aDestinations),
            &aErrorMessage);

    XCTAssertTrue(aWasValid, @"%s", aErrorMessage.c_str());
    XCTAssertEqual(aConfig.mSlices[0].mIngressSources[0],
                   aPrimarySources[3]);
}

- (void)testFourInputStageRejectsAnyOtherFirstPrimarySource {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kEarthLaneA,
        Slot::kEarthLaneB,
        Slot::kEarthLaneC,
        Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinations = {
        Slot::kWindLaneA,
        Slot::kWindLaneB,
        Slot::kWindLaneC,
        Slot::kWindLaneD,
    };

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageConfigValidatorTesting";
    aConfig.mBatchName = "four_input_entry_rejection";
    aConfig.mExpectedSkeletonCount =
        static_cast<int>(aDestinations.size());
    aConfig.mHotPackCount =
        static_cast<int>(aDestinations.size());
    aConfig.mSlices =
        GPassFactoryMidstage::FourPassNoResidualSlices(aPrimarySources,
                                               aDestinations);
    aConfig.mSlices[0].mIngressSources[0] = aPrimarySources[0];

    std::string aErrorMessage;
    const bool aWasValid =
        GSeedRunStageConfigValidator::ValidateMidstage(
            aConfig,
            GPassFactoryMidstage::ToVector(aPrimarySources),
            std::vector<Slot>(),
            GPassFactoryMidstage::ToVector(aDestinations),
            &aErrorMessage);

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("last primary source"),
                      std::string::npos);
}

- (void)testValidatorRejectsPassCountsOtherThanFourOrSix {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kEarthLaneA,
        Slot::kEarthLaneB,
        Slot::kEarthLaneC,
        Slot::kEarthLaneD,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinations = {
        Slot::kWindLaneA,
        Slot::kWindLaneB,
        Slot::kWindLaneC,
        Slot::kWindLaneD,
    };

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageConfigValidatorTesting";
    aConfig.mBatchName = "unsupported_pass_count";
    aConfig.mSlices =
        GPassFactoryMidstage::FourPassNoResidualSlices(aPrimarySources,
                                               aDestinations);
    aConfig.mSlices.pop_back();
    aConfig.mExpectedSkeletonCount =
        static_cast<int>(aConfig.mSlices.size());
    aConfig.mHotPackCount =
        static_cast<int>(aConfig.mSlices.size());

    std::string aErrorMessage;
    const bool aWasValid =
        GSeedRunStageConfigValidator::ValidateMidstage(
            aConfig,
            GPassFactoryMidstage::ToVector(aPrimarySources),
            std::vector<Slot>(),
            {
                aDestinations[0],
                aDestinations[1],
                aDestinations[2],
            },
            &aErrorMessage);

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("four or six slices"),
                      std::string::npos);
}

- (void)testSourceGraphAcceptsRequiredFourthUseAtSecondCrossPosition {
    using Slot = TwistWorkSpaceSlot;

    const GSeedRunStageConfig aConfig = [self sixPassConfig];
    const Slot aFirstDestination = aConfig.mSlices[0].mDest;

    XCTAssertEqual(aConfig.mSlices[1].mIngressSources[0],
                   aFirstDestination);
    XCTAssertEqual(aConfig.mSlices[2].mCrossSources[0],
                   aFirstDestination);
    XCTAssertEqual(aConfig.mSlices[3].mIngressSources[1],
                   aFirstDestination);
    XCTAssertEqual(aConfig.mSlices[4].mCrossSources[1],
                   aFirstDestination);

    std::string aErrorMessage;
    const bool aWasValid =
        [self validateSixPassConfig:aConfig
                         residuals:std::vector<Slot>()
                              error:&aErrorMessage];

    XCTAssertTrue(aWasValid, @"%s", aErrorMessage.c_str());
}

- (void)testMidstageContinuesPreviousFourPrimaryWrites {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kEarthLaneA,
        Slot::kEarthLaneB,
        Slot::kEarthLaneC,
        Slot::kEarthLaneD,
    };
    const GSeedRunStageConfig aConfig = [self sixPassConfig];

    XCTAssertEqual(aConfig.mSlices[0].mIngressSources[0],
                   aPrimarySources[3]);
    XCTAssertEqual(aConfig.mSlices[0].mCrossSources[0],
                   aPrimarySources[2]);
    XCTAssertEqual(aConfig.mSlices[0].mIngressSources[1],
                   aPrimarySources[1]);
    XCTAssertEqual(aConfig.mSlices[0].mCrossSources[1],
                   aPrimarySources[0]);

    std::string aErrorMessage;
    const bool aWasValid =
        [self validateSixPassConfig:aConfig
                         residuals:std::vector<Slot>()
                              error:&aErrorMessage];

    XCTAssertTrue(aWasValid, @"%s", aErrorMessage.c_str());
}

- (void)testMidstageRejectsOmittedOldestPrimaryFourthUse {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = [self sixPassConfig];
    const Slot aReplacementResidual = Slot::kFireLaneA;
    aConfig.mSlices[0].mCrossSources[1] = aReplacementResidual;

    std::string aErrorMessage;
    const bool aWasValid =
        [self validateSixPassConfig:aConfig
                         residuals:{aReplacementResidual}
                              error:&aErrorMessage];

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("omitted required source"),
                      std::string::npos);
}

- (void)testMidstageRejectsBrokenPrimaryContinuation {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = [self sixPassConfig];
    std::swap(aConfig.mSlices[0].mCrossSources[0],
              aConfig.mSlices[0].mCrossSources[1]);

    std::string aErrorMessage;
    const bool aWasValid =
        [self validateSixPassConfig:aConfig
                         residuals:std::vector<Slot>()
                              error:&aErrorMessage];

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("midstage source graph"),
                      std::string::npos);
}

- (void)testSourceGraphRejectsOmittedFourthUse {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = [self sixPassConfig];
    const Slot aReplacementResidual = Slot::kFireLaneA;
    aConfig.mSlices[4].mCrossSources[1] = aReplacementResidual;

    std::string aErrorMessage;
    const bool aWasValid =
        [self validateSixPassConfig:aConfig
                         residuals:{aReplacementResidual}
                              error:&aErrorMessage];

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("fourth read"),
                      std::string::npos);
}

- (void)testSourceGraphRejectsFourthUseOutsideSecondCrossPosition {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = [self sixPassConfig];
    const Slot aFirstDestination = aConfig.mSlices[0].mDest;
    const Slot aReplacementResidual = Slot::kFireLaneA;
    aConfig.mSlices[4].mCrossSources[1] = aReplacementResidual;
    aConfig.mSlices[4].mIngressSources.push_back(aFirstDestination);

    std::string aErrorMessage;
    const bool aWasValid =
        [self validateSixPassConfig:aConfig
                         residuals:{aReplacementResidual}
                              error:&aErrorMessage];

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("fourth read only as cross[1]"),
                      std::string::npos);
}

- (void)testSourceGraphRejectsMandatoryUseOutsideRequiredPosition {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = [self sixPassConfig];
    std::swap(aConfig.mSlices[2].mCrossSources[0],
              aConfig.mSlices[2].mCrossSources[1]);

    std::string aErrorMessage;
    const bool aWasValid =
        [self validateSixPassConfig:aConfig
                         residuals:std::vector<Slot>()
                              error:&aErrorMessage];

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("cross[0] two passes after its write"),
                      std::string::npos);
}

- (void)testSourceGraphRejectsDestinationReadBeforeWrite {
    using Slot = TwistWorkSpaceSlot;

    GSeedRunStageConfig aConfig = [self sixPassConfig];
    const Slot aFutureDestination = aConfig.mSlices[5].mDest;
    aConfig.mSlices[0].mIngressSources.push_back(aFutureDestination);

    std::string aErrorMessage;
    const bool aWasValid =
        [self validateSixPassConfig:aConfig
                         residuals:{aFutureDestination}
                              error:&aErrorMessage];

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("before its destination write"),
                      std::string::npos);
}

- (void)testFourPassTrunkUsesExactMatrixEntryGraph {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kWaterLaneA,
        Slot::kWaterLaneB,
        Slot::kWaterLaneC,
        Slot::kWaterLaneD,
    };
    const GPassFactoryMidstage::SlotArray1 aResiduals = {
        Slot::kFireLaneA,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinations = {
        Slot::kRainbowLaneA,
        Slot::kRainbowLaneB,
        Slot::kRainbowLaneC,
        Slot::kRainbowLaneD,
    };

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageConfigValidatorTesting";
    aConfig.mBatchName = "four_pass_trunk";
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    aConfig.mSlices =
        GPassFactoryTrunk::FourPassTrunkSlices(aPrimarySources,
                                          aResiduals,
                                          aDestinations);

    XCTAssertEqual(aConfig.mSlices[0].mIngressSources[0],
                   aPrimarySources[0]);
    XCTAssertEqual(aConfig.mSlices[0].mIngressSources[1],
                   aPrimarySources[1]);
    XCTAssertEqual(aConfig.mSlices[0].mCrossSources[0],
                   aPrimarySources[2]);
    XCTAssertEqual(aConfig.mSlices[0].mCrossSources[1],
                   aPrimarySources[3]);
    XCTAssertEqual(aConfig.mSlices[3].mCrossSources[1],
                   aResiduals[0]);

    std::string aErrorMessage;
    const bool aWasValid =
        GSeedRunStageConfigValidator::ValidateTrunk(
            aConfig,
            GPassFactoryMidstage::ToVector(aPrimarySources),
            GPassFactoryMidstage::ToVector(aResiduals),
            GPassFactoryMidstage::ToVector(aDestinations),
            &aErrorMessage);

    XCTAssertTrue(aWasValid, @"%s", aErrorMessage.c_str());
}

- (void)testSixPassTrunkContinuesNormalDestinationGraph {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kWaterLaneA,
        Slot::kWaterLaneB,
        Slot::kWaterLaneC,
        Slot::kWaterLaneD,
    };
    const GPassFactoryMidstage::SlotArray5 aResiduals = {
        Slot::kFireLaneA,
        Slot::kFireLaneB,
        Slot::kFireLaneC,
        Slot::kFireLaneD,
        Slot::kEarthLaneA,
    };
    const GPassFactoryMidstage::SlotArray6 aDestinations = {
        Slot::kRainbowLaneA,
        Slot::kRainbowLaneB,
        Slot::kRainbowLaneC,
        Slot::kRainbowLaneD,
        Slot::kIceLaneA,
        Slot::kIceLaneB,
    };

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageConfigValidatorTesting";
    aConfig.mBatchName = "six_pass_trunk";
    aConfig.mExpectedSkeletonCount = 6;
    aConfig.mHotPackCount = 6;
    aConfig.mSlices =
        GPassFactoryTrunk::SixPassTrunkSlices(aPrimarySources,
                                         aResiduals,
                                         aDestinations);

    std::string aErrorMessage;
    const bool aWasValid =
        GSeedRunStageConfigValidator::ValidateTrunk(
            aConfig,
            GPassFactoryMidstage::ToVector(aPrimarySources),
            GPassFactoryMidstage::ToVector(aResiduals),
            GPassFactoryMidstage::ToVector(aDestinations),
            &aErrorMessage);

    XCTAssertTrue(aWasValid, @"%s", aErrorMessage.c_str());
    XCTAssertEqual(aConfig.mSlices[4].mIngressSources[0],
                   aDestinations[3]);
    XCTAssertEqual(aConfig.mSlices[4].mCrossSources[0],
                   aDestinations[2]);
    XCTAssertEqual(aConfig.mSlices[5].mIngressSources[0],
                   aDestinations[4]);
}

- (void)testFourPassTrunkUsesOptionalDestinationSlotForEighteenthResidual {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kWaterLaneA,
        Slot::kWaterLaneB,
        Slot::kWaterLaneC,
        Slot::kWaterLaneD,
    };
    const GPassFactoryMidstage::SlotArray18 aResiduals = {
        Slot::kFireLaneA, Slot::kFireLaneB,
        Slot::kFireLaneC, Slot::kFireLaneD,
        Slot::kEarthLaneA, Slot::kEarthLaneB,
        Slot::kEarthLaneC, Slot::kEarthLaneD,
        Slot::kWindLaneA, Slot::kWindLaneB,
        Slot::kWindLaneC, Slot::kWindLaneD,
        Slot::kWoodLaneA, Slot::kWoodLaneB,
        Slot::kWoodLaneC, Slot::kWoodLaneD,
        Slot::kSpiritLaneA, Slot::kSpiritLaneB,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinations = {
        Slot::kRainbowLaneA,
        Slot::kRainbowLaneB,
        Slot::kRainbowLaneC,
        Slot::kRainbowLaneD,
    };

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageConfigValidatorTesting";
    aConfig.mBatchName = "eighteen_residual_trunk";
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    aConfig.mSlices =
        GPassFactoryTrunk::FourPassTrunkSlices(aPrimarySources,
                                          aResiduals,
                                          aDestinations);

    std::string aErrorMessage;
    const bool aWasValid =
        GSeedRunStageConfigValidator::ValidateTrunk(
            aConfig,
            GPassFactoryMidstage::ToVector(aPrimarySources),
            GPassFactoryMidstage::ToVector(aResiduals),
            GPassFactoryMidstage::ToVector(aDestinations),
            &aErrorMessage);

    XCTAssertTrue(aWasValid, @"%s", aErrorMessage.c_str());
    XCTAssertNotEqual(aConfig.mSlices[3].mIngressSources[1],
                      aDestinations[0]);
}

- (void)testTrunkRejectsMissingResidualWildcard {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kWaterLaneA,
        Slot::kWaterLaneB,
        Slot::kWaterLaneC,
        Slot::kWaterLaneD,
    };
    const GPassFactoryMidstage::SlotArray1 aFactoryResidual = {
        Slot::kFireLaneA,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinations = {
        Slot::kRainbowLaneA,
        Slot::kRainbowLaneB,
        Slot::kRainbowLaneC,
        Slot::kRainbowLaneD,
    };

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageConfigValidatorTesting";
    aConfig.mBatchName = "missing_trunk_wildcard";
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    aConfig.mSlices =
        GPassFactoryTrunk::FourPassTrunkSlices(aPrimarySources,
                                          aFactoryResidual,
                                          aDestinations);

    std::string aErrorMessage;
    const bool aWasValid =
        GSeedRunStageConfigValidator::ValidateTrunk(
            aConfig,
            GPassFactoryMidstage::ToVector(aPrimarySources),
            std::vector<Slot>(),
            GPassFactoryMidstage::ToVector(aDestinations),
            &aErrorMessage);

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("requires a residual"),
                      std::string::npos);
}

- (void)testTrunkRejectsWrongPrimaryPosition {
    using Slot = TwistWorkSpaceSlot;

    const GPassFactoryMidstage::SlotArray4 aPrimarySources = {
        Slot::kWaterLaneA,
        Slot::kWaterLaneB,
        Slot::kWaterLaneC,
        Slot::kWaterLaneD,
    };
    const GPassFactoryMidstage::SlotArray1 aResiduals = {
        Slot::kFireLaneA,
    };
    const GPassFactoryMidstage::SlotArray4 aDestinations = {
        Slot::kRainbowLaneA,
        Slot::kRainbowLaneB,
        Slot::kRainbowLaneC,
        Slot::kRainbowLaneD,
    };

    GSeedRunStageConfig aConfig;
    aConfig.mStageName = "StageConfigValidatorTesting";
    aConfig.mBatchName = "wrong_trunk_primary";
    aConfig.mExpectedSkeletonCount = 4;
    aConfig.mHotPackCount = 4;
    aConfig.mSlices =
        GPassFactoryTrunk::FourPassTrunkSlices(aPrimarySources,
                                          aResiduals,
                                          aDestinations);
    std::swap(aConfig.mSlices[1].mCrossSources[0],
              aConfig.mSlices[1].mCrossSources[1]);

    std::string aErrorMessage;
    const bool aWasValid =
        GSeedRunStageConfigValidator::ValidateTrunk(
            aConfig,
            GPassFactoryMidstage::ToVector(aPrimarySources),
            GPassFactoryMidstage::ToVector(aResiduals),
            GPassFactoryMidstage::ToVector(aDestinations),
            &aErrorMessage);

    XCTAssertFalse(aWasValid);
    XCTAssertNotEqual(aErrorMessage.find("trunk source graph"),
                      std::string::npos);
}

@end
