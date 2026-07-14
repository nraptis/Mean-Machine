//
//  ArxConsistencyTests.m
//  CornTesting
//
//  Created by icarus black on 6/23/26.
//


#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "TwistWorkSpace.hpp"
#include "Random.hpp"
#include "ConsistencyTestsShared.hpp"
#include <unordered_map>
#include <vector>

@interface ArxConsistencyTests : XCTestCase

@end

@implementation ArxConsistencyTests

- (void)testKDF_A_A {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::KDF_A_A(&aVarsTrialA.mWorkSpace,
                         aVarsTrialA.mNonce,
                         &aVarsTrialA.mConstants,
                         &aVarsTrialA.mDomainSaltSet,
                         
                         aVarsTrialA.mSnow,
                         &aVarsTrialA.mPrevious,
                         &aVarsTrialA.mIngress,
                         &aVarsTrialA.mCarry,
                         &aVarsTrialA.mWandererA,
                         &aVarsTrialA.mWandererB,
                         &aVarsTrialA.mWandererC,
                         &aVarsTrialA.mWandererD,
                         &aVarsTrialA.mWandererE,
                         &aVarsTrialA.mWandererF,
                         &aVarsTrialA.mWandererG,
                         &aVarsTrialA.mWandererH,
                         &aVarsTrialA.mWandererI,
                         &aVarsTrialA.mWandererJ,
                         &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::KDF_A_A(&aVarsTrialB.mWorkSpace,
                             aVarsTrialB.mNonce,
                             &aVarsTrialB.mConstants,
                             &aVarsTrialB.mDomainSaltSet,
                         
                             aVarsTrialB.mSnow,
                             &aVarsTrialB.mPrevious,
                             &aVarsTrialB.mIngress,
                             &aVarsTrialB.mCarry,
                             &aVarsTrialB.mWandererA,
                             &aVarsTrialB.mWandererB,
                             &aVarsTrialB.mWandererC,
                             &aVarsTrialB.mWandererD,
                             &aVarsTrialB.mWandererE,
                             &aVarsTrialB.mWandererF,
                             &aVarsTrialB.mWandererG,
                             &aVarsTrialB.mWandererH,
                             &aVarsTrialB.mWandererI,
                             &aVarsTrialB.mWandererJ,
                             &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
    
}

- (void)testKDF_A_B {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::KDF_A_B(&aVarsTrialA.mWorkSpace,
                         aVarsTrialA.mNonce,
                         &aVarsTrialA.mConstants,
                         &aVarsTrialA.mDomainSaltSet,
                         
                         &aVarsTrialA.mPrevious,
                         &aVarsTrialA.mIngress,
                         &aVarsTrialA.mCarry,
                         &aVarsTrialA.mWandererA,
                         &aVarsTrialA.mWandererB,
                         &aVarsTrialA.mWandererC,
                         &aVarsTrialA.mWandererD,
                         &aVarsTrialA.mWandererE,
                         &aVarsTrialA.mWandererF,
                         &aVarsTrialA.mWandererG,
                         &aVarsTrialA.mWandererH,
                         &aVarsTrialA.mWandererI,
                         &aVarsTrialA.mWandererJ,
                         &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::KDF_A_B(&aVarsTrialB.mWorkSpace,
                             aVarsTrialB.mNonce,
                             &aVarsTrialB.mConstants,
                             &aVarsTrialB.mDomainSaltSet,
                         
                             &aVarsTrialB.mPrevious,
                             &aVarsTrialB.mIngress,
                             &aVarsTrialB.mCarry,
                             &aVarsTrialB.mWandererA,
                             &aVarsTrialB.mWandererB,
                             &aVarsTrialB.mWandererC,
                             &aVarsTrialB.mWandererD,
                             &aVarsTrialB.mWandererE,
                             &aVarsTrialB.mWandererF,
                             &aVarsTrialB.mWandererG,
                             &aVarsTrialB.mWandererH,
                             &aVarsTrialB.mWandererI,
                             &aVarsTrialB.mWandererJ,
                             &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
    
}

- (void)testKDF_A_C {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::KDF_A_C(&aVarsTrialA.mWorkSpace,
                         aVarsTrialA.mNonce,
                         &aVarsTrialA.mConstants,
                         &aVarsTrialA.mDomainSaltSet,
                         
                         &aVarsTrialA.mPrevious,
                         &aVarsTrialA.mIngress,
                         &aVarsTrialA.mCarry,
                         &aVarsTrialA.mWandererA,
                         &aVarsTrialA.mWandererB,
                         &aVarsTrialA.mWandererC,
                         &aVarsTrialA.mWandererD,
                         &aVarsTrialA.mWandererE,
                         &aVarsTrialA.mWandererF,
                         &aVarsTrialA.mWandererG,
                         &aVarsTrialA.mWandererH,
                         &aVarsTrialA.mWandererI,
                         &aVarsTrialA.mWandererJ,
                         &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesABAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected work lanes A/B not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::KDF_A_C(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                         &aVarsTrialB.mConstants,
                         &aVarsTrialB.mDomainSaltSet,
                         
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesABAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected work lanes A/B equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testKDF_A_D {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::KDF_A_D(&aVarsTrialA.mWorkSpace,
                         aVarsTrialA.mNonce,
                         &aVarsTrialA.mConstants,
                         &aVarsTrialA.mDomainSaltSet,
                         
                         &aVarsTrialA.mPrevious,
                         &aVarsTrialA.mIngress,
                         &aVarsTrialA.mCarry,
                         &aVarsTrialA.mWandererA,
                         &aVarsTrialA.mWandererB,
                         &aVarsTrialA.mWandererC,
                         &aVarsTrialA.mWandererD,
                         &aVarsTrialA.mWandererE,
                         &aVarsTrialA.mWandererF,
                         &aVarsTrialA.mWandererG,
                         &aVarsTrialA.mWandererH,
                         &aVarsTrialA.mWandererI,
                         &aVarsTrialA.mWandererJ,
                         &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesABAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected work lanes A/B not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::KDF_A_D(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                         &aVarsTrialB.mConstants,
                         &aVarsTrialB.mDomainSaltSet,
                         
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesABAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected work lanes A/B equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testKDF_B_A {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::KDF_B_A(&aVarsTrialA.mWorkSpace,
                         aVarsTrialA.mNonce,
                         &aVarsTrialA.mConstants,
                         &aVarsTrialA.mDomainSaltSet,
                         &aVarsTrialA.mPrevious,
                         &aVarsTrialA.mIngress,
                         &aVarsTrialA.mCarry,
                         &aVarsTrialA.mWandererA,
                         &aVarsTrialA.mWandererB,
                         &aVarsTrialA.mWandererC,
                         &aVarsTrialA.mWandererD,
                         &aVarsTrialA.mWandererE,
                         &aVarsTrialA.mWandererF,
                         &aVarsTrialA.mWandererG,
                         &aVarsTrialA.mWandererH,
                         &aVarsTrialA.mWandererI,
                         &aVarsTrialA.mWandererJ,
                         &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::KDF_B_A(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                         &aVarsTrialB.mConstants,
                         &aVarsTrialB.mDomainSaltSet,
                         
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testKDF_B_B {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::KDF_B_B(&aVarsTrialA.mWorkSpace,
                         aVarsTrialA.mNonce,
                         &aVarsTrialA.mConstants,
                         &aVarsTrialA.mDomainSaltSet,
                         
                         &aVarsTrialA.mPrevious,
                         &aVarsTrialA.mIngress,
                         &aVarsTrialA.mCarry,
                         &aVarsTrialA.mWandererA,
                         &aVarsTrialA.mWandererB,
                         &aVarsTrialA.mWandererC,
                         &aVarsTrialA.mWandererD,
                         &aVarsTrialA.mWandererE,
                         &aVarsTrialA.mWandererF,
                         &aVarsTrialA.mWandererG,
                         &aVarsTrialA.mWandererH,
                         &aVarsTrialA.mWandererI,
                         &aVarsTrialA.mWandererJ,
                         &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected opration lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::KDF_B_B(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                         &aVarsTrialB.mConstants,
                         &aVarsTrialB.mDomainSaltSet,
                         
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected opration lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testKDF_B_C {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::KDF_B_C(&aVarsTrialA.mWorkSpace,
                         aVarsTrialA.mNonce,
                         &aVarsTrialA.mConstants,
                         &aVarsTrialA.mDomainSaltSet,
                         
                         &aVarsTrialA.mPrevious,
                         &aVarsTrialA.mIngress,
                         &aVarsTrialA.mCarry,
                         &aVarsTrialA.mWandererA,
                         &aVarsTrialA.mWandererB,
                         &aVarsTrialA.mWandererC,
                         &aVarsTrialA.mWandererD,
                         &aVarsTrialA.mWandererE,
                         &aVarsTrialA.mWandererF,
                         &aVarsTrialA.mWandererG,
                         &aVarsTrialA.mWandererH,
                         &aVarsTrialA.mWandererI,
                         &aVarsTrialA.mWandererJ,
                         &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::KDF_B_C(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                         &aVarsTrialB.mConstants,
                         &aVarsTrialB.mDomainSaltSet,
                         
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testKDF_B_D {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::KDF_B_D(&aVarsTrialA.mWorkSpace,
                         aVarsTrialA.mNonce,
                         &aVarsTrialA.mConstants,
                         &aVarsTrialA.mDomainSaltSet,
                         
                         &aVarsTrialA.mPrevious,
                         &aVarsTrialA.mIngress,
                         &aVarsTrialA.mCarry,
                         &aVarsTrialA.mWandererA,
                         &aVarsTrialA.mWandererB,
                         &aVarsTrialA.mWandererC,
                         &aVarsTrialA.mWandererD,
                         &aVarsTrialA.mWandererE,
                         &aVarsTrialA.mWandererF,
                         &aVarsTrialA.mWandererG,
                         &aVarsTrialA.mWandererH,
                         &aVarsTrialA.mWandererI,
                         &aVarsTrialA.mWandererJ,
                         &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::KDF_B_D(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                         &aVarsTrialB.mConstants,
                         &aVarsTrialB.mDomainSaltSet,
                         
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testSeed_A {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::Seed_A(&aVarsTrialA.mWorkSpace,
                             aVarsTrialA.mNonce,
                        
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::Seed_A(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                        
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testSeed_B {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::Seed_B(&aVarsTrialA.mWorkSpace,
                             aVarsTrialA.mNonce,
                        
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::Seed_B(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                        
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testSeed_C {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::Seed_C(&aVarsTrialA.mWorkSpace,
                             aVarsTrialA.mNonce,
                        
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::Seed_C(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                        
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
}

- (void)testSeed_D {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::Seed_D(&aVarsTrialA.mWorkSpace,
                             aVarsTrialA.mNonce,
                        
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::Seed_D(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                        
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testSeed_E {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::Seed_E(&aVarsTrialA.mWorkSpace,
                             aVarsTrialA.mNonce,
                        
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::Seed_E(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                        
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testSeed_F {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::Seed_F(&aVarsTrialA.mWorkSpace,
                             aVarsTrialA.mNonce,
                        
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::Seed_F(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mNonce,
                        
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testTwist_A {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::Twist_A(&aVarsTrialA.mWorkSpace,
                             aVarsTrialA.mSource,
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::Twist_A(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mSource,
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
}

- (void)testTwist_B {

    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::Twist_B(&aVarsTrialA.mWorkSpace,
                             aVarsTrialA.mSource,
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::Twist_B(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mSource,
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureOperationLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}


- (void)testTwist_C {
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::Twist_C(&aVarsTrialA.mWorkSpace,
                             aVarsTrialA.mSource,
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::Twist_C(&aVarsTrialB.mWorkSpace,
                         aVarsTrialB.mSource,
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
}

- (void)testGrow_A {

    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::GROW_A(&aVarsTrialA.mWorkSpace,
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::GROW_A(&aVarsTrialB.mWorkSpace,
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureExpansionLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}

- (void)testGrow_B {

    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    ConsistencyTestsArxVariables aVarsTrialA = aVarsOriginal.Clone();
    ConsistencyTestsArxVariables aVarsTrialB = aVarsOriginal.Clone();
    CONSISTENCY_TESTS_ARX::GROW_B(&aVarsTrialA.mWorkSpace,
                             &aVarsTrialA.mPrevious,
                             &aVarsTrialA.mIngress,
                             &aVarsTrialA.mCarry,
                             &aVarsTrialA.mWandererA,
                             &aVarsTrialA.mWandererB,
                             &aVarsTrialA.mWandererC,
                             &aVarsTrialA.mWandererD,
                             &aVarsTrialA.mWandererE,
                             &aVarsTrialA.mWandererF,
                             &aVarsTrialA.mWandererG,
                             &aVarsTrialA.mWandererH,
                             &aVarsTrialA.mWandererI,
                             &aVarsTrialA.mWandererJ,
                             &aVarsTrialA.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesAreNotEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes not equal, suspiciously they were equal");
        return;
    }
    
    CONSISTENCY_TESTS_ARX::GROW_B(&aVarsTrialB.mWorkSpace,
                         &aVarsTrialB.mPrevious,
                         &aVarsTrialB.mIngress,
                         &aVarsTrialB.mCarry,
                         &aVarsTrialB.mWandererA,
                         &aVarsTrialB.mWandererB,
                         &aVarsTrialB.mWandererC,
                         &aVarsTrialB.mWandererD,
                         &aVarsTrialB.mWandererE,
                         &aVarsTrialB.mWandererF,
                         &aVarsTrialB.mWandererG,
                         &aVarsTrialB.mWandererH,
                         &aVarsTrialB.mWandererI,
                         &aVarsTrialB.mWandererJ,
                         &aVarsTrialB.mWandererK);
    
    if (!ConsistencyTestsShared::EnsureWorkLanesAreEqual(&aVarsTrialA.mWorkSpace, &aVarsTrialB.mWorkSpace)) {
        XCTFail("expected expansions lanes equal, suspiciously they were not equal");
        return;
    }
    
}


@end
