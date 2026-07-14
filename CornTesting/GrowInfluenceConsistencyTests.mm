//
//  GrowInfluenceConsistencyTestsA.m
//  CornTesting
//
//  Created by icarus black on 6/25/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "TwistWorkSpace.hpp"
#include "Random.hpp"
#include "ConsistencyTestsShared.hpp"
#include <unordered_map>
#include <vector>

#define IGNORE_GROW_TESTS 1

@interface GrowInfluenceConsistencyTests : XCTestCase

@end

@implementation GrowInfluenceConsistencyTests


static inline void CopyPhaseGSalts(TwistWorkSpace *pDest,
                                   const TwistWorkSpace *pSource) {
    pDest->mDomainBundle.mPhaseGSalts.mOrbiterAssign =
        pSource->mDomainBundle.mPhaseGSalts.mOrbiterAssign;

    pDest->mDomainBundle.mPhaseGSalts.mOrbiterUpdate =
        pSource->mDomainBundle.mPhaseGSalts.mOrbiterUpdate;

    pDest->mDomainBundle.mPhaseGSalts.mWandererUpdate =
        pSource->mDomainBundle.mPhaseGSalts.mWandererUpdate;
}

static inline void CopyPhaseHSalts(TwistWorkSpace *pDest,
                                   const TwistWorkSpace *pSource) {
    pDest->mDomainBundle.mPhaseHSalts.mOrbiterAssign =
        pSource->mDomainBundle.mPhaseHSalts.mOrbiterAssign;

    pDest->mDomainBundle.mPhaseHSalts.mOrbiterUpdate =
        pSource->mDomainBundle.mPhaseHSalts.mOrbiterUpdate;

    pDest->mDomainBundle.mPhaseHSalts.mWandererUpdate =
        pSource->mDomainBundle.mPhaseHSalts.mWandererUpdate;
}

- (void)testGrow_A {
    
#ifdef IGNORE_GROW_TESTS
    return;
#endif
    
    std::uint8_t aDataLaneA[S_BLOCK];
    std::uint8_t aDataLaneB[S_BLOCK];
    std::uint8_t aDataLaneC[S_BLOCK];
    std::uint8_t aDataLaneD[S_BLOCK];
    
    for (int i=0;i<S_BLOCK;i++) {
        aDataLaneA[i] = Random::GetByte();
        aDataLaneB[i] = Random::GetByte();
        aDataLaneC[i] = Random::GetByte();
        aDataLaneD[i] = Random::GetByte();
    }
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    
    
    std::uint64_t aPreviousOriginal = aVarsOriginal.mPrevious;
    std::uint64_t aIngressOriginal = aVarsOriginal.mIngress;
    std::uint64_t aCarryOriginal = aVarsOriginal.mCarry;
    std::uint64_t aWandererAOriginal = aVarsOriginal.mWandererA;
    std::uint64_t aWandererBOriginal = aVarsOriginal.mWandererB;
    std::uint64_t aWandererCOriginal = aVarsOriginal.mWandererC;
    std::uint64_t aWandererDOriginal = aVarsOriginal.mWandererD;
    std::uint64_t aWandererEOriginal = aVarsOriginal.mWandererE;
    std::uint64_t aWandererFOriginal = aVarsOriginal.mWandererF;
    std::uint64_t aWandererGOriginal = aVarsOriginal.mWandererG;
    std::uint64_t aWandererHOriginal = aVarsOriginal.mWandererH;
    std::uint64_t aWandererIOriginal = aVarsOriginal.mWandererI;
    std::uint64_t aWandererJOriginal = aVarsOriginal.mWandererJ;
    std::uint64_t aWandererKOriginal = aVarsOriginal.mWandererK;
    
    std::uint64_t aPrevious = aPreviousOriginal;
    std::uint64_t aIngress = aIngressOriginal;
    std::uint64_t aCarry = aCarryOriginal;
    std::uint64_t aWandererA = aWandererAOriginal;
    std::uint64_t aWandererB = aWandererBOriginal;
    std::uint64_t aWandererC = aWandererCOriginal;
    std::uint64_t aWandererD = aWandererDOriginal;
    std::uint64_t aWandererE = aWandererEOriginal;
    std::uint64_t aWandererF = aWandererFOriginal;
    std::uint64_t aWandererG = aWandererGOriginal;
    std::uint64_t aWandererH = aWandererHOriginal;
    std::uint64_t aWandererI = aWandererIOriginal;
    std::uint64_t aWandererJ = aWandererJOriginal;
    std::uint64_t aWandererK = aWandererKOriginal;
    
    
    memcpy(aVarsOriginal.mWorkSpace.mWorkLaneA, aDataLaneA, S_BLOCK);
    memcpy(aVarsOriginal.mWorkSpace.mWorkLaneB, aDataLaneB, S_BLOCK);
    memcpy(aVarsOriginal.mWorkSpace.mWorkLaneC, aDataLaneC, S_BLOCK);
    memcpy(aVarsOriginal.mWorkSpace.mWorkLaneD, aDataLaneD, S_BLOCK);
    
    auto aExpander = ConsistencyTestsShared::Expander();
    
    CONSISTENCY_TESTS_ARX::GROW_A(&aVarsOriginal.mWorkSpace,
                        &aPrevious,
                        &aIngress,
                        &aCarry,
                        &aWandererA,
                        &aWandererB,
                        &aWandererC,
                        &aWandererD,
                        &aWandererE,
                        &aWandererF,
                        &aWandererG,
                        &aWandererH,
                        &aWandererI,
                        &aWandererJ,
                        &aWandererK);
    aExpander.GrowKeyA(&aVarsOriginal.mWorkSpace);
    
    std::uint8_t aKeyRowOriginal[W_KEY];
    std::uint8_t aKeyRowCheck[W_KEY];
    
    memcpy(aKeyRowOriginal, &(aVarsOriginal.mWorkSpace.mKeyBoxA[0][0]), W_KEY);
    NSLog(@"hello from test");
    
    for (int aLaneIndex=0; aLaneIndex<4; aLaneIndex++) {
        
        printf("Checking Lane %d\n", aLaneIndex);
        
        for (int aByteIndex=0; aByteIndex<S_BLOCK; aByteIndex++) {
            
            if ((aByteIndex % 64) == 0) {
                printf("Checking Byte %d\n", aByteIndex);
            }
            
            ConsistencyTestsArxVariables aVarsCheckA = ConsistencyTestsShared::MakeArxVariables();
            CopyPhaseGSalts(&aVarsCheckA.mWorkSpace, &aVarsOriginal.mWorkSpace);
            
            aPrevious = aPreviousOriginal; aIngress = aIngressOriginal; aCarry = aCarryOriginal;
            aWandererA = aWandererAOriginal; aWandererB = aWandererBOriginal;
            aWandererC = aWandererCOriginal; aWandererD = aWandererDOriginal; aWandererE = aWandererEOriginal;
            aWandererF = aWandererFOriginal; aWandererG = aWandererGOriginal; aWandererH = aWandererHOriginal;
            aWandererI = aWandererIOriginal; aWandererJ = aWandererJOriginal; aWandererK = aWandererKOriginal;
            
            CONSISTENCY_TESTS_ARX::GROW_A(&aVarsCheckA.mWorkSpace,
                                &aPrevious,
                                &aIngress,
                                &aCarry,
                                &aWandererA,
                                &aWandererB,
                                &aWandererC,
                                &aWandererD,
                                &aWandererE,
                                &aWandererF,
                                &aWandererG,
                                &aWandererH,
                                &aWandererI,
                                &aWandererJ,
                                &aWandererK);
            aExpander.GrowKeyA(&aVarsCheckA.mWorkSpace);
            
            memcpy(aKeyRowCheck, &(aVarsCheckA.mWorkSpace.mKeyBoxA[0][0]), W_KEY);
            
            bool aAllEqual = true;
            for (int n=0; n<W_KEY; n++) {
                if (aKeyRowOriginal[n] != aKeyRowCheck[n]) {
                    aAllEqual = false;
                    break;
                }
            }
            
            if (aAllEqual == true) {
                XCTFail("expected the keys to be different here, a-1");
                return;
            }
            
            
            
            
            ConsistencyTestsArxVariables aVarsCheckB = ConsistencyTestsShared::MakeArxVariables();
            CopyPhaseGSalts(&aVarsCheckB.mWorkSpace, &aVarsOriginal.mWorkSpace);
            
            memcpy(aVarsCheckB.mWorkSpace.mWorkLaneA, aDataLaneA, S_BLOCK);
            memcpy(aVarsCheckB.mWorkSpace.mWorkLaneB, aDataLaneB, S_BLOCK);
            memcpy(aVarsCheckB.mWorkSpace.mWorkLaneC, aDataLaneC, S_BLOCK);
            memcpy(aVarsCheckB.mWorkSpace.mWorkLaneD, aDataLaneD, S_BLOCK);
            
            aPrevious = aPreviousOriginal; aIngress = aIngressOriginal; aCarry = aCarryOriginal;
            aWandererA = aWandererAOriginal; aWandererB = aWandererBOriginal;
            aWandererC = aWandererCOriginal; aWandererD = aWandererDOriginal; aWandererE = aWandererEOriginal;
            aWandererF = aWandererFOriginal; aWandererG = aWandererGOriginal; aWandererH = aWandererHOriginal;
            aWandererI = aWandererIOriginal; aWandererJ = aWandererJOriginal; aWandererK = aWandererKOriginal;
            
            CONSISTENCY_TESTS_ARX::GROW_A(&aVarsCheckB.mWorkSpace,
                                &aPrevious,
                                &aIngress,
                                &aCarry,
                                &aWandererA,
                                &aWandererB,
                                &aWandererC,
                                &aWandererD,
                                &aWandererE,
                                &aWandererF,
                                &aWandererG,
                                &aWandererH,
                                &aWandererI,
                                &aWandererJ,
                                &aWandererK);
            aExpander.GrowKeyA(&aVarsCheckB.mWorkSpace);
            
            memcpy(aKeyRowCheck, &(aVarsCheckB.mWorkSpace.mKeyBoxA[0][0]), W_KEY);
            
            
            aAllEqual = true;
            for (int n=0; n<W_KEY; n++) {
                if (aKeyRowOriginal[n] != aKeyRowCheck[n]) {
                    aAllEqual = false;
                    break;
                }
            }
            
            if (aAllEqual == false) {
                // always fails here now
                XCTFail("expected the keys to be the same here, a-2");
                return;
            }
            
            
            bool aChangingTheByteDidChangeTheKey = false;
            
            int aLoopCount = 0;
            for (std::size_t aChangeValue=0; aChangeValue<256; aChangeValue++) {
                
                aLoopCount++;
                
                ConsistencyTestsArxVariables aVarsCheckC = ConsistencyTestsShared::MakeArxVariables();
                CopyPhaseGSalts(&aVarsCheckC.mWorkSpace, &aVarsOriginal.mWorkSpace);
                
                memcpy(aVarsCheckC.mWorkSpace.mWorkLaneA, aDataLaneA, S_BLOCK);
                memcpy(aVarsCheckC.mWorkSpace.mWorkLaneB, aDataLaneB, S_BLOCK);
                memcpy(aVarsCheckC.mWorkSpace.mWorkLaneC, aDataLaneC, S_BLOCK);
                memcpy(aVarsCheckC.mWorkSpace.mWorkLaneD, aDataLaneD, S_BLOCK);
                
                if (aLaneIndex == 0) {
                    aVarsCheckC.mWorkSpace.mWorkLaneA[aByteIndex] = aChangeValue;
                } else if (aLaneIndex == 1) {
                    aVarsCheckC.mWorkSpace.mWorkLaneB[aByteIndex] = aChangeValue;
                } else if (aLaneIndex == 1) {
                    aVarsCheckC.mWorkSpace.mWorkLaneC[aByteIndex] = aChangeValue;
                } else {
                    aVarsCheckC.mWorkSpace.mWorkLaneD[aByteIndex] = aChangeValue;
                }
                
                aPrevious = aPreviousOriginal; aIngress = aIngressOriginal; aCarry = aCarryOriginal;
                aWandererA = aWandererAOriginal; aWandererB = aWandererBOriginal;
                aWandererC = aWandererCOriginal; aWandererD = aWandererDOriginal; aWandererE = aWandererEOriginal;
                aWandererF = aWandererFOriginal; aWandererG = aWandererGOriginal; aWandererH = aWandererHOriginal;
                aWandererI = aWandererIOriginal; aWandererJ = aWandererJOriginal; aWandererK = aWandererKOriginal;
                
                CONSISTENCY_TESTS_ARX::GROW_A(&aVarsCheckC.mWorkSpace,
                                    &aPrevious,
                                    &aIngress,
                                    &aCarry,
                                    &aWandererA,
                                    &aWandererB,
                                    &aWandererC,
                                    &aWandererD,
                                    &aWandererE,
                                    &aWandererF,
                                    &aWandererG,
                                    &aWandererH,
                                    &aWandererI,
                                    &aWandererJ,
                                    &aWandererK);
                aExpander.GrowKeyA(&aVarsCheckC.mWorkSpace);
                
                memcpy(aKeyRowCheck, &(aVarsCheckC.mWorkSpace.mKeyBoxA[0][0]), W_KEY);
                
                aAllEqual = true;
                for (int n=0; n<W_KEY; n++) {
                    if (aKeyRowOriginal[n] != aKeyRowCheck[n]) {
                        aAllEqual = false;
                        break;
                    }
                }
                
                if (aAllEqual == false) {
                    aChangingTheByteDidChangeTheKey = true;
                    break;
                }
                
            }
            
            if (aChangingTheByteDidChangeTheKey == false) {
                XCTFail("this byte %d %d has no influence", aLaneIndex, aByteIndex);
                return;
            } else {
                //printf("for lane %d, byte %d, it took %d tries and it changed the key...\n", aLaneIndex, aByteIndex, aLoopCount);
                
            }
        }
    }
    
}


- (void)testGrow_B {
    
#ifdef IGNORE_GROW_TESTS
    return;
#endif
    
    std::uint8_t aDataLaneA[S_BLOCK];
    std::uint8_t aDataLaneB[S_BLOCK];
    std::uint8_t aDataLaneC[S_BLOCK];
    std::uint8_t aDataLaneD[S_BLOCK];
    
    for (int i=0;i<S_BLOCK;i++) {
        aDataLaneA[i] = Random::GetByte();
        aDataLaneB[i] = Random::GetByte();
        aDataLaneC[i] = Random::GetByte();
        aDataLaneD[i] = Random::GetByte();
    }
    
    ConsistencyTestsArxVariables aVarsOriginal = ConsistencyTestsShared::MakeArxVariables();
    
    
    std::uint64_t aPreviousOriginal = aVarsOriginal.mPrevious;
    std::uint64_t aIngressOriginal = aVarsOriginal.mIngress;
    std::uint64_t aCarryOriginal = aVarsOriginal.mCarry;
    std::uint64_t aWandererAOriginal = aVarsOriginal.mWandererA;
    std::uint64_t aWandererBOriginal = aVarsOriginal.mWandererB;
    std::uint64_t aWandererCOriginal = aVarsOriginal.mWandererC;
    std::uint64_t aWandererDOriginal = aVarsOriginal.mWandererD;
    std::uint64_t aWandererEOriginal = aVarsOriginal.mWandererE;
    std::uint64_t aWandererFOriginal = aVarsOriginal.mWandererF;
    std::uint64_t aWandererGOriginal = aVarsOriginal.mWandererG;
    std::uint64_t aWandererHOriginal = aVarsOriginal.mWandererH;
    std::uint64_t aWandererIOriginal = aVarsOriginal.mWandererI;
    std::uint64_t aWandererJOriginal = aVarsOriginal.mWandererJ;
    std::uint64_t aWandererKOriginal = aVarsOriginal.mWandererK;
    
    std::uint64_t aPrevious = aPreviousOriginal;
    std::uint64_t aIngress = aIngressOriginal;
    std::uint64_t aCarry = aCarryOriginal;
    std::uint64_t aWandererA = aWandererAOriginal;
    std::uint64_t aWandererB = aWandererBOriginal;
    std::uint64_t aWandererC = aWandererCOriginal;
    std::uint64_t aWandererD = aWandererDOriginal;
    std::uint64_t aWandererE = aWandererEOriginal;
    std::uint64_t aWandererF = aWandererFOriginal;
    std::uint64_t aWandererG = aWandererGOriginal;
    std::uint64_t aWandererH = aWandererHOriginal;
    std::uint64_t aWandererI = aWandererIOriginal;
    std::uint64_t aWandererJ = aWandererJOriginal;
    std::uint64_t aWandererK = aWandererKOriginal;
    
    
    memcpy(aVarsOriginal.mWorkSpace.mExpansionLaneA, aDataLaneA, S_BLOCK);
    memcpy(aVarsOriginal.mWorkSpace.mExpansionLaneB, aDataLaneB, S_BLOCK);
    memcpy(aVarsOriginal.mWorkSpace.mExpansionLaneC, aDataLaneC, S_BLOCK);
    memcpy(aVarsOriginal.mWorkSpace.mExpansionLaneD, aDataLaneD, S_BLOCK);
    
    auto aExpander = ConsistencyTestsShared::Expander();
    
    CONSISTENCY_TESTS_ARX::GROW_B(&aVarsOriginal.mWorkSpace,
                        &aPrevious,
                        &aIngress,
                        &aCarry,
                        &aWandererA,
                        &aWandererB,
                        &aWandererC,
                        &aWandererD,
                        &aWandererE,
                        &aWandererF,
                        &aWandererG,
                        &aWandererH,
                        &aWandererI,
                        &aWandererJ,
                        &aWandererK);
    aExpander.GrowKeyB(&aVarsOriginal.mWorkSpace);
    
    std::uint8_t aKeyRowOriginal[W_KEY];
    std::uint8_t aKeyRowCheck[W_KEY];
    
    memcpy(aKeyRowOriginal, &(aVarsOriginal.mWorkSpace.mKeyBoxB[0][0]), W_KEY);
    NSLog(@"hello from test");
    
    for (int aLaneIndex=0; aLaneIndex<4; aLaneIndex++) {
        
        printf("Checking Lane %d\n", aLaneIndex);
        
        for (int aByteIndex=0; aByteIndex<S_BLOCK; aByteIndex++) {
            
            if ((aByteIndex % 64) == 0) {
                printf("Checking Byte %d\n", aByteIndex);
            }
            
            ConsistencyTestsArxVariables aVarsCheckA = ConsistencyTestsShared::MakeArxVariables();
            CopyPhaseHSalts(&aVarsCheckA.mWorkSpace, &aVarsOriginal.mWorkSpace);
            
            aPrevious = aPreviousOriginal; aIngress = aIngressOriginal; aCarry = aCarryOriginal;
            aWandererA = aWandererAOriginal; aWandererB = aWandererBOriginal;
            aWandererC = aWandererCOriginal; aWandererD = aWandererDOriginal; aWandererE = aWandererEOriginal;
            aWandererF = aWandererFOriginal; aWandererG = aWandererGOriginal; aWandererH = aWandererHOriginal;
            aWandererI = aWandererIOriginal; aWandererJ = aWandererJOriginal; aWandererK = aWandererKOriginal;
            
            CONSISTENCY_TESTS_ARX::GROW_B(&aVarsCheckA.mWorkSpace,
                                &aPrevious,
                                &aIngress,
                                &aCarry,
                                &aWandererA,
                                &aWandererB,
                                &aWandererC,
                                &aWandererD,
                                &aWandererE,
                                &aWandererF,
                                &aWandererG,
                                &aWandererH,
                                &aWandererI,
                                &aWandererJ,
                                &aWandererK);
            aExpander.GrowKeyB(&aVarsCheckA.mWorkSpace);
            
            memcpy(aKeyRowCheck, &(aVarsCheckA.mWorkSpace.mKeyBoxB[0][0]), W_KEY);
            
            bool aAllEqual = true;
            for (int n=0; n<W_KEY; n++) {
                if (aKeyRowOriginal[n] != aKeyRowCheck[n]) {
                    aAllEqual = false;
                    break;
                }
            }
            
            if (aAllEqual == true) {
                XCTFail("expected the keys to be different here, a-1");
                return;
            }
            
            ConsistencyTestsArxVariables aVarsCheckB = ConsistencyTestsShared::MakeArxVariables();
            CopyPhaseHSalts(&aVarsCheckB.mWorkSpace, &aVarsOriginal.mWorkSpace);
            
            memcpy(aVarsCheckB.mWorkSpace.mExpansionLaneA, aDataLaneA, S_BLOCK);
            memcpy(aVarsCheckB.mWorkSpace.mExpansionLaneB, aDataLaneB, S_BLOCK);
            memcpy(aVarsCheckB.mWorkSpace.mExpansionLaneC, aDataLaneC, S_BLOCK);
            memcpy(aVarsCheckB.mWorkSpace.mExpansionLaneD, aDataLaneD, S_BLOCK);
            
            aPrevious = aPreviousOriginal; aIngress = aIngressOriginal; aCarry = aCarryOriginal;
            aWandererA = aWandererAOriginal; aWandererB = aWandererBOriginal;
            aWandererC = aWandererCOriginal; aWandererD = aWandererDOriginal; aWandererE = aWandererEOriginal;
            aWandererF = aWandererFOriginal; aWandererG = aWandererGOriginal; aWandererH = aWandererHOriginal;
            aWandererI = aWandererIOriginal; aWandererJ = aWandererJOriginal; aWandererK = aWandererKOriginal;
            
            CONSISTENCY_TESTS_ARX::GROW_B(&aVarsCheckB.mWorkSpace,
                                &aPrevious,
                                &aIngress,
                                &aCarry,
                                &aWandererA,
                                &aWandererB,
                                &aWandererC,
                                &aWandererD,
                                &aWandererE,
                                &aWandererF,
                                &aWandererG,
                                &aWandererH,
                                &aWandererI,
                                &aWandererJ,
                                &aWandererK);
            aExpander.GrowKeyB(&aVarsCheckB.mWorkSpace);
            
            memcpy(aKeyRowCheck, &(aVarsCheckB.mWorkSpace.mKeyBoxB[0][0]), W_KEY);
            
            
            aAllEqual = true;
            for (int n=0; n<W_KEY; n++) {
                if (aKeyRowOriginal[n] != aKeyRowCheck[n]) {
                    aAllEqual = false;
                    break;
                }
            }
            
            if (aAllEqual == false) {
                // always fails here now
                XCTFail("expected the keys to be the same here, a-2");
                return;
            }
            
            
            bool aChangingTheByteDidChangeTheKey = false;
            
            int aLoopCount = 0;
            for (std::size_t aChangeValue=0; aChangeValue<256; aChangeValue++) {
                
                aLoopCount++;
                
                ConsistencyTestsArxVariables aVarsCheckC = ConsistencyTestsShared::MakeArxVariables();
                CopyPhaseHSalts(&aVarsCheckC.mWorkSpace, &aVarsOriginal.mWorkSpace);
                
                memcpy(aVarsCheckC.mWorkSpace.mExpansionLaneA, aDataLaneA, S_BLOCK);
                memcpy(aVarsCheckC.mWorkSpace.mExpansionLaneB, aDataLaneB, S_BLOCK);
                memcpy(aVarsCheckC.mWorkSpace.mExpansionLaneC, aDataLaneC, S_BLOCK);
                memcpy(aVarsCheckC.mWorkSpace.mExpansionLaneD, aDataLaneD, S_BLOCK);
                
                if (aLaneIndex == 0) {
                    aVarsCheckC.mWorkSpace.mExpansionLaneA[aByteIndex] = aChangeValue;
                } else if (aLaneIndex == 1) {
                    aVarsCheckC.mWorkSpace.mExpansionLaneB[aByteIndex] = aChangeValue;
                } else if (aLaneIndex == 1) {
                    aVarsCheckC.mWorkSpace.mExpansionLaneC[aByteIndex] = aChangeValue;
                } else {
                    aVarsCheckC.mWorkSpace.mExpansionLaneD[aByteIndex] = aChangeValue;
                }
                
                aPrevious = aPreviousOriginal; aIngress = aIngressOriginal; aCarry = aCarryOriginal;
                aWandererA = aWandererAOriginal; aWandererB = aWandererBOriginal;
                aWandererC = aWandererCOriginal; aWandererD = aWandererDOriginal; aWandererE = aWandererEOriginal;
                aWandererF = aWandererFOriginal; aWandererG = aWandererGOriginal; aWandererH = aWandererHOriginal;
                aWandererI = aWandererIOriginal; aWandererJ = aWandererJOriginal; aWandererK = aWandererKOriginal;
                
                CONSISTENCY_TESTS_ARX::GROW_B(&aVarsCheckC.mWorkSpace,
                                    &aPrevious,
                                    &aIngress,
                                    &aCarry,
                                    &aWandererA,
                                    &aWandererB,
                                    &aWandererC,
                                    &aWandererD,
                                    &aWandererE,
                                    &aWandererF,
                                    &aWandererG,
                                    &aWandererH,
                                    &aWandererI,
                                    &aWandererJ,
                                    &aWandererK);
                aExpander.GrowKeyB(&aVarsCheckC.mWorkSpace);
                
                memcpy(aKeyRowCheck, &(aVarsCheckC.mWorkSpace.mKeyBoxB[0][0]), W_KEY);
                
                aAllEqual = true;
                for (int n=0; n<W_KEY; n++) {
                    if (aKeyRowOriginal[n] != aKeyRowCheck[n]) {
                        aAllEqual = false;
                        break;
                    }
                }
                
                if (aAllEqual == false) {
                    aChangingTheByteDidChangeTheKey = true;
                    break;
                }
                
            }
            
            if (aChangingTheByteDidChangeTheKey == false) {
                XCTFail("this byte %d %d has no influence", aLaneIndex, aByteIndex);
                return;
            }
            
        }
        
    }
    
}

@end
