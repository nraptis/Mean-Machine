//
//  CodexConsistencyTests.mm
//  CornTesting
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

#include "Avalancher.hpp"
#include "ConsistencyTestsShared.hpp"
#include "Random.hpp"
#include "Rig.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistWorkSpace.hpp"

#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

@interface CodexConsistencyTests : XCTestCase

@end

namespace {

struct SeedCapture {
    TwistWorkSpace mWorkSpace;
    std::vector<std::uint8_t> mDestination;
    std::vector<std::uint8_t> mKeyBoxA;
    std::vector<std::uint8_t> mKeyBoxB;
};

static bool BytesAreEqual(const std::uint8_t *pA,
                          const std::uint8_t *pB,
                          const std::size_t pCount) {
    return std::memcmp(pA, pB, pCount) == 0;
}

static bool VectorBytesAreEqual(const std::vector<std::uint8_t> &pA,
                                const std::vector<std::uint8_t> &pB) {
    return (pA.size() == pB.size()) && (std::memcmp(pA.data(), pB.data(), pA.size()) == 0);
}

static bool BufferIsAllZero(const std::uint8_t *pBytes,
                            const std::size_t pCount) {
    for (std::size_t aIndex = 0U; aIndex < pCount; aIndex += 1U) {
        if (pBytes[aIndex] != 0U) {
            return false;
        }
    }
    return true;
}

static bool BufferHasAnyDifference(const std::uint8_t *pA,
                                   const std::uint8_t *pB,
                                   const std::size_t pCount) {
    return !BytesAreEqual(pA, pB, pCount);
}

static bool KeyRowsAreAllIdentical(const std::uint8_t pKeyBox[H_KEY][W_KEY]) {
    for (int aRow = 1; aRow < H_KEY; aRow += 1) {
        if (!BytesAreEqual(pKeyBox[0], pKeyBox[aRow], W_KEY)) {
            return false;
        }
    }
    return true;
}

static void AssertHealthyKeyBox(XCTestCase *pTest,
                                const char *pLabel,
                                const std::uint8_t pKeyBox[H_KEY][W_KEY]) {
    XCTAssertFalse(BufferIsAllZero(&pKeyBox[0][0], S_KEY),
                   @"%s should not be all zero", pLabel);
    for (int aRow = 0; aRow < H_KEY; aRow += 1) {
        XCTAssertFalse(BufferIsAllZero(pKeyBox[aRow], W_KEY),
                       @"%s row %d should not be all zero", pLabel, aRow);
    }
    XCTAssertFalse(KeyRowsAreAllIdentical(pKeyBox),
                   @"%s should not have every row identical", pLabel);
    (void)pTest;
}

static void FillPattern(std::uint8_t *pBytes,
                        const std::size_t pCount,
                        const std::uint32_t pSeed) {
    std::uint32_t aState = pSeed;
    for (std::size_t aIndex = 0U; aIndex < pCount; aIndex += 1U) {
        aState = (aState * 1664525U) + 1013904223U;
        pBytes[aIndex] = static_cast<std::uint8_t>((aState >> 24U) ^ (aIndex * 29U));
    }
}

static std::uint8_t *InvestLaneAt(TwistWorkSpace *pWorkSpace,
                                  const int pIndex) {
    switch (pIndex) {
        case 0: return pWorkSpace->mInvestLaneA;
        case 1: return pWorkSpace->mInvestLaneB;
        case 2: return pWorkSpace->mInvestLaneC;
        case 3: return pWorkSpace->mInvestLaneD;
        case 4: return pWorkSpace->mInvestLaneE;
        case 5: return pWorkSpace->mInvestLaneF;
        case 6: return pWorkSpace->mInvestLaneG;
        case 7: return pWorkSpace->mInvestLaneH;
        default: return pWorkSpace->mInvestLaneA;
    }
}

static void FillInvestLanes(TwistWorkSpace *pWorkSpace) {
    for (int aLane = 0; aLane < 8; aLane += 1) {
        FillPattern(InvestLaneAt(pWorkSpace, aLane),
                    S_BLOCK,
                    0xA31C0001U + static_cast<std::uint32_t>(aLane * 0x101U));
    }
}

static void CopyKeyBoxA(const TwistWorkSpace &pWorkSpace,
                        std::vector<std::uint8_t> *pResult) {
    pResult->assign(&pWorkSpace.mKeyBoxA[0][0], &pWorkSpace.mKeyBoxA[0][0] + S_KEY);
}

static void CopyKeyBoxB(const TwistWorkSpace &pWorkSpace,
                        std::vector<std::uint8_t> *pResult) {
    pResult->assign(&pWorkSpace.mKeyBoxB[0][0], &pWorkSpace.mKeyBoxB[0][0] + S_KEY);
}

static SeedCapture RunSeedOnce(ConsistencyTestsShared::Expander *pExpander,
                               const std::string &pPassword) {
    SeedCapture aResult;
    aResult.mDestination.resize(S_BLOCK);

    TwistFarmSalt aFarmSalt;
    std::uint8_t *aPasswordBytes = nullptr;
    if (!pPassword.empty()) {
        aPasswordBytes = reinterpret_cast<std::uint8_t *>(const_cast<char *>(pPassword.data()));
    }

    pExpander->Seed(&aResult.mWorkSpace,
                    &aFarmSalt,
                    0xC0DEC0FFEE123456ULL,
                    aPasswordBytes,
                    static_cast<unsigned int>(pPassword.size()),
                    aResult.mDestination.data());

    CopyKeyBoxA(aResult.mWorkSpace, &aResult.mKeyBoxA);
    CopyKeyBoxB(aResult.mWorkSpace, &aResult.mKeyBoxB);
    return aResult;
}

static void AssertSeedCapturesEqual(const SeedCapture &pA,
                                    const SeedCapture &pB,
                                    NSString *pLabel) {
    XCTAssertTrue(VectorBytesAreEqual(pA.mDestination, pB.mDestination),
                  @"%@ destination changed", pLabel);
    XCTAssertTrue(VectorBytesAreEqual(pA.mKeyBoxA, pB.mKeyBoxA),
                  @"%@ key box A changed", pLabel);
    XCTAssertTrue(VectorBytesAreEqual(pA.mKeyBoxB, pB.mKeyBoxB),
                  @"%@ key box B changed", pLabel);
}

static bool ScratchLanesAreZeroedAfterSeed(const TwistWorkSpace &pWorkSpace) {
    return BufferIsAllZero(pWorkSpace.mSource, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mExpansionLaneA, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mExpansionLaneB, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mExpansionLaneC, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mExpansionLaneD, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mWorkLaneA, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mWorkLaneB, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mWorkLaneC, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mWorkLaneD, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mOperationLaneA, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mOperationLaneB, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mOperationLaneC, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mOperationLaneD, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mSnowLaneA, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mSnowLaneB, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mSnowLaneC, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mSnowLaneD, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mFireLaneA, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mFireLaneB, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mFireLaneC, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mFireLaneD, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mInvestLaneA, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mInvestLaneB, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mInvestLaneC, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mInvestLaneD, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mInvestLaneE, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mInvestLaneF, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mInvestLaneG, S_BLOCK) &&
           BufferIsAllZero(pWorkSpace.mInvestLaneH, S_BLOCK);
}

} // namespace

@implementation CodexConsistencyTests

- (void)testKdfAAndKdfBMoveTheExpectedLaneSets {
    ConsistencyTestsArxVariables aVars = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsShared::Expander aExpander = ConsistencyTestsShared::MakeExpander();
    aExpander.mWorkspace = &aVars.mWorkSpace;
    aExpander.mSource = aVars.mWorkSpace.mSource;

    TwistWorkSpace aBeforeKdfA = aVars.mWorkSpace;
    aExpander.KDF_A(aVars.mNonce,
                    &aVars.mConstants,
                    &aVars.mDomainSaltSet,
                    aVars.mSnow);

    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfA.mExpansionLaneA, aVars.mWorkSpace.mExpansionLaneA, S_BLOCK), @"KDF_A should write expansion lane A.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfA.mExpansionLaneB, aVars.mWorkSpace.mExpansionLaneB, S_BLOCK), @"KDF_A should write expansion lane B.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfA.mExpansionLaneC, aVars.mWorkSpace.mExpansionLaneC, S_BLOCK), @"KDF_A should write expansion lane C.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfA.mExpansionLaneD, aVars.mWorkSpace.mExpansionLaneD, S_BLOCK), @"KDF_A should write expansion lane D.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfA.mWorkLaneA, aVars.mWorkSpace.mWorkLaneA, S_BLOCK), @"KDF_A should leave live data in work lane A.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfA.mWorkLaneB, aVars.mWorkSpace.mWorkLaneB, S_BLOCK), @"KDF_A should leave live data in work lane B.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfA.mWorkLaneC, aVars.mWorkSpace.mWorkLaneC, S_BLOCK), @"KDF_A should leave live data in work lane C.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfA.mWorkLaneD, aVars.mWorkSpace.mWorkLaneD, S_BLOCK), @"KDF_A should leave live data in work lane D.");

    TwistWorkSpace aBeforeKdfB = aVars.mWorkSpace;
    aExpander.KDF_B(aVars.mNonce,
                    &aVars.mConstants,
                    &aVars.mDomainSaltSet);

    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfB.mExpansionLaneA, aVars.mWorkSpace.mExpansionLaneA, S_BLOCK), @"KDF_B should write expansion lane A.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfB.mExpansionLaneB, aVars.mWorkSpace.mExpansionLaneB, S_BLOCK), @"KDF_B should write expansion lane B.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfB.mExpansionLaneC, aVars.mWorkSpace.mExpansionLaneC, S_BLOCK), @"KDF_B should write expansion lane C.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfB.mExpansionLaneD, aVars.mWorkSpace.mExpansionLaneD, S_BLOCK), @"KDF_B should write expansion lane D.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfB.mOperationLaneA, aVars.mWorkSpace.mOperationLaneA, S_BLOCK), @"KDF_B should touch operation lane A.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfB.mOperationLaneB, aVars.mWorkSpace.mOperationLaneB, S_BLOCK), @"KDF_B should touch operation lane B.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfB.mOperationLaneC, aVars.mWorkSpace.mOperationLaneC, S_BLOCK), @"KDF_B should touch operation lane C.");
    XCTAssertTrue(BufferHasAnyDifference(aBeforeKdfB.mOperationLaneD, aVars.mWorkSpace.mOperationLaneD, S_BLOCK), @"KDF_B should touch operation lane D.");
}

- (void)testSquashInvestToKeyBoxesUsesEveryInvestLaneForBothBoxes {
    ConsistencyTestsShared::Expander aExpander = ConsistencyTestsShared::MakeExpander();
    TwistWorkSpace aBaseWorkSpace;
    FillInvestLanes(&aBaseWorkSpace);
    aExpander.mWorkspace = &aBaseWorkSpace;
    aExpander.SquashInvestToKeyBoxes();

    AssertHealthyKeyBox(self, "SquashInvestToKeyBoxes key box A", aBaseWorkSpace.mKeyBoxA);
    AssertHealthyKeyBox(self, "SquashInvestToKeyBoxes key box B", aBaseWorkSpace.mKeyBoxB);

    std::vector<std::uint8_t> aBaseKeyBoxA;
    std::vector<std::uint8_t> aBaseKeyBoxB;
    CopyKeyBoxA(aBaseWorkSpace, &aBaseKeyBoxA);
    CopyKeyBoxB(aBaseWorkSpace, &aBaseKeyBoxB);

    for (int aLane = 0; aLane < 8; aLane += 1) {
        TwistWorkSpace aTrialWorkSpace = aBaseWorkSpace;
        std::uint8_t *aLaneBytes = InvestLaneAt(&aTrialWorkSpace, aLane);
        for (std::size_t aChunk = 0U; aChunk < 16U; aChunk += 1U) {
            const std::size_t aOffset = (aChunk * W_KEY) + (((aChunk + 1U) * 137U + static_cast<std::size_t>(aLane * 29)) & W_KEY1);
            aLaneBytes[aOffset] = static_cast<std::uint8_t>(aLaneBytes[aOffset] ^ 0xA5U);
        }

        aExpander.mWorkspace = &aTrialWorkSpace;
        aExpander.SquashInvestToKeyBoxes();

        XCTAssertTrue(BufferHasAnyDifference(aBaseKeyBoxA.data(), &aTrialWorkSpace.mKeyBoxA[0][0], S_KEY),
                      @"Changing invest lane %d should influence key box A.", aLane);
        XCTAssertTrue(BufferHasAnyDifference(aBaseKeyBoxB.data(), &aTrialWorkSpace.mKeyBoxB[0][0], S_KEY),
                      @"Changing invest lane %d should influence key box B.", aLane);
    }
}

- (void)testSeedProducesHealthyDestinationKeyBoxesAndScratchCleanup {
    ConsistencyTestsShared::Expander aExpander = ConsistencyTestsShared::MakeExpander();
    SeedCapture aSeed = RunSeedOnce(&aExpander, "codex-audit-seed");

    XCTAssertFalse(BufferIsAllZero(aSeed.mDestination.data(), aSeed.mDestination.size()),
                   @"Seed destination should not be all zero.");
    AssertHealthyKeyBox(self, "Seed key box A", aSeed.mWorkSpace.mKeyBoxA);
    AssertHealthyKeyBox(self, "Seed key box B", aSeed.mWorkSpace.mKeyBoxB);
    XCTAssertTrue(ScratchLanesAreZeroedAfterSeed(aSeed.mWorkSpace),
                  @"Seed should keep key boxes and domain bundle, then clear scratch lanes.");
}

- (void)testSeedCanBeReusedWithoutPoisoningTheExpander {
    ConsistencyTestsShared::Expander aFreshA = ConsistencyTestsShared::MakeExpander();
    SeedCapture aFreshFirst = RunSeedOnce(&aFreshA, "cat");

    ConsistencyTestsShared::Expander aReusable = ConsistencyTestsShared::MakeExpander();
    SeedCapture aReusableFirst = RunSeedOnce(&aReusable, "cat");
    AssertSeedCapturesEqual(aFreshFirst, aReusableFirst, @"first reusable seed");

    SeedCapture aReusableSecond = RunSeedOnce(&aReusable, "cat");

    ConsistencyTestsShared::Expander aFreshB = ConsistencyTestsShared::MakeExpander();
    SeedCapture aFreshSecond = RunSeedOnce(&aFreshB, "cat");
    AssertSeedCapturesEqual(aFreshSecond, aReusableSecond, @"second reusable seed");
}

- (void)testDifferentPasswordsChangeSeedDestinationAndKeyBoxes {
    ConsistencyTestsShared::Expander aExpanderA = ConsistencyTestsShared::MakeExpander();
    ConsistencyTestsShared::Expander aExpanderB = ConsistencyTestsShared::MakeExpander();

    SeedCapture aSeedA = RunSeedOnce(&aExpanderA, "cat");
    SeedCapture aSeedB = RunSeedOnce(&aExpanderB, "eat");

    XCTAssertFalse(VectorBytesAreEqual(aSeedA.mDestination, aSeedB.mDestination),
                   @"Different passwords should change the seed destination.");
    XCTAssertFalse(VectorBytesAreEqual(aSeedA.mKeyBoxA, aSeedB.mKeyBoxA),
                   @"Different passwords should change key box A.");
    XCTAssertFalse(VectorBytesAreEqual(aSeedA.mKeyBoxB, aSeedB.mKeyBoxB),
                   @"Different passwords should change key box B.");
}

- (void)testTwistBlockSourceInfluencesDestinationAndAdvancesKeyRows {
    ConsistencyTestsShared::Expander aExpanderA = ConsistencyTestsShared::MakeExpander();
    ConsistencyTestsShared::Expander aExpanderB = ConsistencyTestsShared::MakeExpander();

    SeedCapture aSeedA = RunSeedOnce(&aExpanderA, "twist-source");
    SeedCapture aSeedB = RunSeedOnce(&aExpanderB, "twist-source");
    AssertSeedCapturesEqual(aSeedA, aSeedB, @"twist setup seed");

    TwistWorkSpace aWorkSpaceA = aSeedA.mWorkSpace;
    TwistWorkSpace aWorkSpaceB = aSeedB.mWorkSpace;
    std::vector<std::uint8_t> aSourceA = aSeedA.mDestination;
    std::vector<std::uint8_t> aSourceB = aSeedB.mDestination;
    aSourceB[0] = static_cast<std::uint8_t>(aSourceB[0] ^ 0x5AU);

    std::vector<std::uint8_t> aDestA(S_BLOCK);
    std::vector<std::uint8_t> aDestB(S_BLOCK);
    std::uint8_t aOldKeyRowA0[W_KEY];
    std::uint8_t aOldKeyRowB0[W_KEY];
    std::memcpy(aOldKeyRowA0, aWorkSpaceA.mKeyBoxA[0], W_KEY);
    std::memcpy(aOldKeyRowB0, aWorkSpaceA.mKeyBoxB[0], W_KEY);

    aExpanderA.TwistBlock(&aWorkSpaceA,
                          0xF00D123456789ABCULL,
                          aSourceA.data(),
                          1U,
                          12U,
                          aDestA.data());
    aExpanderB.TwistBlock(&aWorkSpaceB,
                          0xF00D123456789ABCULL,
                          aSourceB.data(),
                          1U,
                          12U,
                          aDestB.data());

    XCTAssertFalse(BufferIsAllZero(aDestA.data(), aDestA.size()),
                   @"Twist destination should not be all zero.");
    XCTAssertTrue(BufferHasAnyDifference(aDestA.data(), aDestB.data(), S_BLOCK),
                  @"Changing one source byte should influence TwistBlock destination.");
    XCTAssertTrue(BytesAreEqual(aOldKeyRowA0, aWorkSpaceA.mKeyBoxA[1], W_KEY),
                  @"GrowKeyA should shift old row 0 to row 1 before writing the new row.");
    XCTAssertTrue(BytesAreEqual(aOldKeyRowB0, aWorkSpaceA.mKeyBoxB[1], W_KEY),
                  @"GrowKeyB should shift old row 0 to row 1 before writing the new row.");
    XCTAssertTrue(BufferHasAnyDifference(aOldKeyRowA0, aWorkSpaceA.mKeyBoxA[0], W_KEY),
                  @"GrowKeyA should write a new key row 0.");
    XCTAssertTrue(BufferHasAnyDifference(aOldKeyRowB0, aWorkSpaceA.mKeyBoxB[0], W_KEY),
                  @"GrowKeyB should write a new key row 0.");
}

- (void)testAvalancherReusesTheSharedCandidateSafely {
    ConsistencyTestsShared::Expander aCandidate = ConsistencyTestsShared::MakeExpander();

    Avalancher aAvalancher;
    aAvalancher.SetExpander(&aCandidate);
    aAvalancher.SetBlockCount(2U);

    std::vector<std::uint8_t> aFirst = aAvalancher.GetOutput("cat");
    std::vector<std::uint8_t> aSecond = aAvalancher.GetOutput("cat");

    XCTAssertFalse(aFirst.empty(), @"Avalancher should produce the first output.");
    XCTAssertTrue(VectorBytesAreEqual(aFirst, aSecond),
                  @"Avalancher should get stable output when it reuses the same candidate for the same password.");
}

@end
