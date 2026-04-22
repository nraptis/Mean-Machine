//
//  TwistSeedProgramTests.mm
//  CornTesting
//

#import <XCTest/XCTest.h>

#include <algorithm>
#include <cstring>
#include <string>

#include "FileIO.hpp"
#include "RTwistRunner.hpp"
#include "SBoxTables.hpp"
#include "TwistSeedBuilder.hpp"

@interface TwistSeedProgramTests : XCTestCase

@end

@implementation TwistSeedProgramTests

- (void)testBaselineBatchExportsAndRoundTrips {
    GBatch aBatch = TwistSeedBuilder::BuildBaselineBatch();

    XCTAssertFalse(aBatch.IsInvalid());
    XCTAssertEqual(aBatch.CountReads(TwistWorkSpaceSlot::kSource), 1U);
    XCTAssertEqual(aBatch.CountReads(TwistWorkSpaceSlot::kSBoxA), 1U);
    XCTAssertEqual(aBatch.CountWrites(TwistWorkSpaceSlot::kWorkLaneA), 1U);
    XCTAssertEqual(aBatch.CountLoopsReading(TwistWorkSpaceSlot::kSource), 1U);
    XCTAssertEqual(aBatch.CountLoopsWriting(TwistWorkSpaceSlot::kWorkLaneA), 1U);

    const std::string aPretty = aBatch.ToPrettyString();
    XCTAssertNotEqual(aPretty.find("mix ="), std::string::npos);
    XCTAssertNotEqual(aPretty.find("sbox_a[mix]"), std::string::npos);

    std::string aJsonError;
    const std::string aJson = aBatch.ToJson(&aJsonError);
    XCTAssertTrue(aJsonError.empty());
    XCTAssertFalse(aJson.empty());

    GBatch aRoundTrip;
    std::string aParseError;
    XCTAssertTrue(GBatch::FromJson(aJson, &aRoundTrip, &aParseError));
    XCTAssertTrue(aParseError.empty());
    XCTAssertEqual(aRoundTrip.CountReads(TwistWorkSpaceSlot::kSource), 1U);
    XCTAssertEqual(aRoundTrip.CountWrites(TwistWorkSpaceSlot::kWorkLaneA), 1U);

    std::string aCppError;
    const std::string aCpp = aRoundTrip.BuildCpp("GeneratedBaselineSeed", &aCppError);
    XCTAssertTrue(aCppError.empty());
    XCTAssertNotEqual(aCpp.find("static void GeneratedBaselineSeed"), std::string::npos);
    XCTAssertNotEqual(aCpp.find("TwistWorkSpace::GetBuffer(pWorkspace, TwistWorkSpaceSlot::kSource)"), std::string::npos);
    XCTAssertNotEqual(aCpp.find("TwistWorkSpace::GetBuffer(pWorkspace, TwistWorkSpaceSlot::kWorkLaneA)"), std::string::npos);
    XCTAssertNotEqual(aCpp.find("mix ="), std::string::npos);
}

- (void)testBaselineBatchExecutesExpectedStateChain {
    GBatch aBatch = TwistSeedBuilder::BuildBaselineBatch();

    TwistWorkSpace aWorkspace;
    std::uint8_t aSource[S_BLOCK];
    std::uint8_t aDest[S_BLOCK];
    std::memset(aSource, 0, sizeof(aSource));
    std::memset(aDest, 0, sizeof(aDest));
    aWorkspace.mSource = aSource;
    aWorkspace.mDest = aDest;

    std::fill(aWorkspace.mSBoxA, aWorkspace.mSBoxA + S_SBOX, 0U);
    for (std::size_t aIndex = 0U; aIndex < S_SBOX; ++aIndex) {
        aWorkspace.mSBoxA[aIndex] = static_cast<std::uint8_t>(aIndex);
    }
    std::fill(aWorkspace.mWorkLaneA, aWorkspace.mWorkLaneA + S_BLOCK, 0U);

    aSource[0] = 1;
    aSource[1] = 2;
    aSource[2] = 3;
    aSource[3] = 4;
    aSource[4] = 5;

    std::string aError;
    XCTAssertTrue(aBatch.Execute(&aWorkspace, &aError));
    XCTAssertTrue(aError.empty());

    XCTAssertEqual(aWorkspace.mWorkLaneA[0], static_cast<std::uint8_t>(1));
    XCTAssertEqual(aWorkspace.mWorkLaneA[1], static_cast<std::uint8_t>(3));
    XCTAssertEqual(aWorkspace.mWorkLaneA[2], static_cast<std::uint8_t>(0));
    XCTAssertEqual(aWorkspace.mWorkLaneA[3], static_cast<std::uint8_t>(4));
    XCTAssertEqual(aWorkspace.mWorkLaneA[4], static_cast<std::uint8_t>(1));
}

- (void)testMutatedBatchTracksSaltAndCarryStructure {
    TwistSeedLoopOptions aOptions;
    aOptions.mMutations.mAddSourceConstant = true;
    aOptions.mMutations.mRotateState = true;
    aOptions.mMutations.mUseSaltTerm = true;
    aOptions.mMutations.mBiasLookupIndex = true;
    aOptions.mMutations.mUseCarry = true;
    aOptions.mMutations.mMaskState = true;

    GBatch aBatch = TwistSeedBuilder::BuildBaselineBatch(aOptions);

    XCTAssertEqual(aBatch.CountReads(TwistWorkSpaceSlot::kSource), 1U);
    XCTAssertEqual(aBatch.CountReads(TwistWorkSpaceSlot::kSaltA), 1U);
    XCTAssertEqual(aBatch.CountReads(TwistWorkSpaceSlot::kSBoxA), 1U);
    XCTAssertEqual(aBatch.CountReads(TwistWorkSpaceSlot::kSBoxB), 1U);
    XCTAssertEqual(aBatch.CountWrites(TwistWorkSpaceSlot::kWorkLaneA), 1U);

    const std::string aPretty = aBatch.ToPrettyString();
    XCTAssertNotEqual(aPretty.find("salt_a[i]"), std::string::npos);
    XCTAssertNotEqual(aPretty.find("carry_a"), std::string::npos);
    XCTAssertNotEqual(aPretty.find("rotl8(state, 4)"), std::string::npos);
}

- (void)testDefaultSaltsAreEmbeddedAndSeededWithoutDisk {
    const std::vector<std::uint8_t> aTestA = SBoxTables::GetTestA();
    const std::vector<std::uint8_t> aTestB = SBoxTables::GetTestB();
    const std::vector<std::uint8_t> aTestC = SBoxTables::GetTestC();
    const std::vector<std::uint8_t> aTestD = SBoxTables::GetTestD();

    const std::vector<std::uint8_t> aSaltA = SBoxTables::GetSaltA();
    const std::vector<std::uint8_t> aSaltB = SBoxTables::GetSaltB();
    const std::vector<std::uint8_t> aSaltC = SBoxTables::GetSaltC();
    const std::vector<std::uint8_t> aSaltD = SBoxTables::GetSaltD();

    XCTAssertEqual(aSaltA.size(), static_cast<std::size_t>(S_SALT));
    XCTAssertEqual(aSaltB.size(), static_cast<std::size_t>(S_SALT));
    XCTAssertEqual(aSaltC.size(), static_cast<std::size_t>(S_SALT));
    XCTAssertEqual(aSaltD.size(), static_cast<std::size_t>(S_SALT));

    XCTAssertTrue(std::equal(aTestA.begin(), aTestA.end(), aSaltA.begin()));
    XCTAssertTrue(std::equal(aTestB.begin(), aTestB.end(), aSaltA.begin() + S_SBOX));
    XCTAssertTrue(std::equal(aTestC.begin(), aTestC.end(), aSaltB.begin()));
    XCTAssertTrue(std::equal(aTestD.begin(), aTestD.end(), aSaltB.begin() + S_SBOX));
    XCTAssertEqual(aSaltA, aSaltC);
    XCTAssertEqual(aSaltB, aSaltD);

    TwistSeeder aSeeder;
    XCTAssertTrue(std::equal(aSaltA.begin(), aSaltA.end(), aSeeder.mSaltA));
    XCTAssertTrue(std::equal(aSaltB.begin(), aSaltB.end(), aSeeder.mSaltB));
    XCTAssertTrue(std::equal(aSaltC.begin(), aSaltC.end(), aSeeder.mSaltC));
    XCTAssertTrue(std::equal(aSaltD.begin(), aSaltD.end(), aSeeder.mSaltD));
}

- (void)testRunnerJsonRoundTripAndExecutionMatchSeeder {
    TwistSeeder aSeeder;
    TwistSeedLoopOptions aOptions;
    aOptions.mMutations.mUseSaltTerm = true;
    aSeeder.SetSeedBatch(TwistSeedBuilder::BuildBaselineBatch(aOptions));

    std::string aJsonError;
    const std::string aJson = aSeeder.GetJson(&aJsonError);
    XCTAssertTrue(aJsonError.empty());
    XCTAssertFalse(aJson.empty());
    XCTAssertNotEqual(aSeeder.GetPrettyPrint().find("salt_a[i]"), std::string::npos);

    GBatch aBatch;
    std::string aLoadError;
    XCTAssertTrue(RTwistRunner::LoadSeedBatchFromJsonText(aJson, &aBatch, &aLoadError));
    XCTAssertTrue(aLoadError.empty());

    TwistSeeder aConfiguredSeeder;
    std::string aConfigureError;
    XCTAssertTrue(RTwistRunner::ConfigureSeederFromJsonText(&aConfiguredSeeder, aJson, &aConfigureError));
    XCTAssertTrue(aConfigureError.empty());
    XCTAssertEqual(aConfiguredSeeder.GetPrettyPrint(), aSeeder.GetPrettyPrint());

    const std::string aJsonPath = "/tmp/meanmachine_runner_seed.json";
    const std::string aCppPath = "/tmp/meanmachine_runner_seed.cpp";

    std::string aSaveJsonError;
    XCTAssertTrue(RTwistRunner::SaveSeederJsonFile(aSeeder, aJsonPath, &aSaveJsonError));
    XCTAssertTrue(aSaveJsonError.empty());

    std::string aSaveCppError;
    XCTAssertTrue(RTwistRunner::SaveSeederCppFile(aSeeder, "GeneratedRunnerSeed", aCppPath, &aSaveCppError));
    XCTAssertTrue(aSaveCppError.empty());

    GBatch aFileBatch;
    std::string aFileLoadError;
    XCTAssertTrue(RTwistRunner::LoadSeedBatchFromJsonFile(aJsonPath, &aFileBatch, &aFileLoadError));
    XCTAssertTrue(aFileLoadError.empty());
    XCTAssertEqual(aFileBatch.ToPrettyString(), aSeeder.GetPrettyPrint());

    std::vector<std::uint8_t> aCppBytes;
    XCTAssertTrue(FileIO::Load(aCppPath, aCppBytes));
    const std::string aCppText(aCppBytes.begin(), aCppBytes.end());
    XCTAssertNotEqual(aCppText.find("GeneratedRunnerSeed"), std::string::npos);
    XCTAssertNotEqual(aCppText.find("TwistWorkSpaceSlot::kSaltA"), std::string::npos);

    std::uint8_t aSource[S_BLOCK];
    std::uint8_t aDestA[S_BLOCK];
    std::uint8_t aDestB[S_BLOCK];
    for (std::size_t aIndex = 0U; aIndex < S_BLOCK; ++aIndex) {
        aSource[aIndex] = static_cast<std::uint8_t>((aIndex * 37U + 11U) & 0xFFU);
    }
    std::memset(aDestA, 0, sizeof(aDestA));
    std::memset(aDestB, 0, sizeof(aDestB));

    TwistWorkSpace aWorkspaceA;
    TwistWorkSpace aWorkspaceB;
    aWorkspaceA.mDest = aDestA;
    aWorkspaceB.mDest = aDestB;

    aSeeder.Seed(&aWorkspaceA, aSource);

    std::string aRunError;
    XCTAssertTrue(RTwistRunner::RunSeedBatch(aFileBatch, &aWorkspaceB, aSource, &aRunError));
    XCTAssertTrue(aRunError.empty());

    XCTAssertTrue(std::equal(aWorkspaceA.mWorkLaneA, aWorkspaceA.mWorkLaneA + S_BLOCK, aWorkspaceB.mWorkLaneA));
    XCTAssertTrue(std::equal(aWorkspaceA.mSaltA, aWorkspaceA.mSaltA + S_SALT, aWorkspaceB.mSaltA));
    XCTAssertTrue(std::equal(aWorkspaceA.mSaltB, aWorkspaceA.mSaltB + S_SALT, aWorkspaceB.mSaltB));
}

@end
