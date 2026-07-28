#import <XCTest/XCTest.h>

#include "FoldSeedControl.hpp"
#include "FoldTwistControl.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace {

std::size_t CountText(const std::string &pText,
                      const std::string &pNeedle) {
    std::size_t aCount = 0U;
    std::size_t aPosition = 0U;
    while ((aPosition = pText.find(pNeedle, aPosition)) !=
           std::string::npos) {
        ++aCount;
        aPosition += pNeedle.size();
    }
    return aCount;
}

} // namespace

@interface SmokeTests : XCTestCase
@end

@implementation SmokeTests

- (void)testFoldControlsGenerateCompleteCandidate {
    FoldSeedControl::Reset(0x464F4C4453454544ULL);
    FoldTwistControl::Reset(0x464F4C4454574953ULL);

    const std::string aSeed =
        FoldSeedControl::Generate(64ULL);
    const std::string aTwist =
        FoldTwistControl::Generate(64ULL);
    const std::string aSeedSelected =
        FoldSeedControl::Generate(64ULL);
    const std::string aTwistSelected =
        FoldTwistControl::Generate(64ULL);

    std::string aError;
    XCTAssertTrue(FoldSeedControl::ValidateCandidate(0U, &aError),
                  @"%s", aError.c_str());
    XCTAssertTrue(FoldTwistControl::ValidateCandidate(0U, &aError),
                  @"%s", aError.c_str());
    XCTAssertTrue(FoldSeedControl::ValidateCandidate(1U, &aError),
                  @"%s", aError.c_str());
    XCTAssertTrue(FoldTwistControl::ValidateCandidate(1U, &aError),
                  @"%s", aError.c_str());

    XCTAssertEqual(CountText(aSeed, "FoldSeed — Chunk "), 16U);
    XCTAssertEqual(CountText(aTwist, "FoldTwist — Chunk "), 16U);
    XCTAssertNotEqual(
        aSeed.find("initial random-shuffle baseline"),
        std::string::npos);
    XCTAssertNotEqual(
        aTwist.find("initial random-shuffle baseline"),
        std::string::npos);
    XCTAssertNotEqual(
        aSeedSelected.find(
            "Structural distance from earlier candidates: nearest "),
        std::string::npos);
    XCTAssertNotEqual(
        aTwistSelected.find(
            "Structural distance from earlier candidates: nearest "),
        std::string::npos);
    XCTAssertEqual(CountText(aSeed, "std::uint8_t *aDestinationLane"),
                   16U);
    XCTAssertEqual(CountText(aTwist, "std::uint8_t *aDestinationLane"),
                   16U);
    for (const char aChunk : {
             'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
             'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
         }) {
        const std::string aWrite =
            std::string("aDestinationLane") + aChunk + "[aIndex] =";
        XCTAssertEqual(CountText(aSeed, aWrite), 1U);
        XCTAssertEqual(CountText(aTwist, aWrite), 1U);
    }
}

- (void)testPersistedFoldControlAssets {
    FoldSeedControl::Reset();
    FoldTwistControl::Reset();

    std::vector<std::string> aWarnings;
    std::string aError;
    XCTAssertTrue(
        FoldSeedControl::LoadValues(
            "Assets/fold_seed_pre_planned",
            &aWarnings,
            &aError),
        @"%s", aError.c_str());
    XCTAssertTrue(
        FoldTwistControl::LoadValues(
            "Assets/fold_twist_pre_planned",
            &aWarnings,
            &aError),
        @"%s", aError.c_str());
    XCTAssertTrue(aWarnings.empty());
    XCTAssertEqual(FoldSeedControl::GeneratedCount(),
                   FoldSeedControl::kCandidateCount);
    XCTAssertEqual(FoldTwistControl::GeneratedCount(),
                   FoldTwistControl::kCandidateCount);

    for (std::size_t i = 0U;
         i < FoldSeedControl::kCandidateCount;
         ++i) {
        aError.clear();
        XCTAssertTrue(
            FoldSeedControl::ValidateCandidate(i, &aError),
            @"FoldSeed candidate %zu: %s", i + 1U, aError.c_str());
        aError.clear();
        XCTAssertTrue(
            FoldTwistControl::ValidateCandidate(i, &aError),
            @"FoldTwist candidate %zu: %s", i + 1U, aError.c_str());
    }
}

@end
