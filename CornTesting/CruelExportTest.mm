//
//  CruelExportTest.m
//  CornTesting
//
//  Created by John Snow on 4/24/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "TwistWorkSpace.hpp"
#include "Random.hpp"

#include "Builder_KDF.hpp"
#include "Builder_Seeder.hpp"
#include "FileIO.hpp"
#include "GFarm.hpp"
#include "GInvest.hpp"
#include "GShiftBox.hpp"
#include "GSeedProgram.hpp"
#include "GRunMaskBraidDiffusion.hpp"
#include "GRunMaskWeaveDiffusion.hpp"
#include "TwistExpander_Kerpal_0006.hpp"
#include "GTwistExpander.hpp"
#include "TwistExpander.hpp"
#include "TwistFastMatrix.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistMasking.hpp"
#include "TwistShiftBox.hpp"
#include "TwistSnow.hpp"
#include <cctype>
#include <unordered_map>
#include <vector>

@interface CruelExportTest : XCTestCase

@end

@implementation CruelExportTest

static BOOL CompareUInt64Value(const char *pLabel,
                               std::uint64_t pValueA,
                               std::uint64_t pValueB,
                               std::string *pError) {
    if (pValueA != pValueB) {
        if (pError != nullptr) {
            char aBuffer[512];
            snprintf(aBuffer,
                     sizeof(aBuffer),
                     "%s mismatch: A=%llu B=%llu",
                     pLabel,
                     static_cast<unsigned long long>(pValueA),
                     static_cast<unsigned long long>(pValueB));
            *pError = aBuffer;
        }
        return NO;
    }
    return YES;
}



static BOOL CompareUInt8Value(const char *pLabel,
                              std::uint8_t pValueA,
                              std::uint8_t pValueB,
                              std::string *pError) {
    if (pValueA != pValueB) {
        if (pError != nullptr) {
            char aBuffer[512];
            snprintf(aBuffer,
                     sizeof(aBuffer),
                     "%s mismatch: A=%u B=%u",
                     pLabel,
                     static_cast<unsigned int>(pValueA),
                     static_cast<unsigned int>(pValueB));
            *pError = aBuffer;
        }
        return NO;
    }
    return YES;
}

static BOOL CompareSaltLane(const char *pLabel,
                            const std::uint64_t *pSaltA,
                            const std::uint64_t *pSaltB,
                            std::string *pError) {
    for (int i = 0; i < S_SALT; ++i) {
        if (pSaltA[i] != pSaltB[i]) {
            if (pError != nullptr) {
                char aBuffer[512];
                snprintf(aBuffer,
                         sizeof(aBuffer),
                         "%s[%d] mismatch: A=%llu B=%llu",
                         pLabel,
                         i,
                         static_cast<unsigned long long>(pSaltA[i]),
                         static_cast<unsigned long long>(pSaltB[i]));
                *pError = aBuffer;
            }
            return NO;
        }
    }
    return YES;
}

static BOOL CompareSeedRoundMaterial(const char *pLabel,
                                     const TwistDomainSeedRoundMaterial &pA,
                                     const TwistDomainSeedRoundMaterial &pB,
                                     std::string *pError) {
    char aLabel[256];
    
    snprintf(aLabel, sizeof(aLabel), "%s.mSaltA", pLabel);
    if (!CompareSaltLane(aLabel, pA.mSaltA, pB.mSaltA, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mSaltB", pLabel);
    if (!CompareSaltLane(aLabel, pA.mSaltB, pB.mSaltB, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mSaltC", pLabel);
    if (!CompareSaltLane(aLabel, pA.mSaltC, pB.mSaltC, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mSaltD", pLabel);
    if (!CompareSaltLane(aLabel, pA.mSaltD, pB.mSaltD, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mSaltE", pLabel);
    if (!CompareSaltLane(aLabel, pA.mSaltE, pB.mSaltE, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mSaltF", pLabel);
    if (!CompareSaltLane(aLabel, pA.mSaltF, pB.mSaltF, pError)) { return NO; }
    
    return YES;
}

static BOOL CompareDomainSaltSet(const char *pLabel,
                                 const TwistDomainSaltSet &pA,
                                 const TwistDomainSaltSet &pB,
                                 std::string *pError) {
    char aLabel[256];
    
    snprintf(aLabel, sizeof(aLabel), "%s.mOrbiterAssign", pLabel);
    if (!CompareSeedRoundMaterial(aLabel, pA.mOrbiterAssign, pB.mOrbiterAssign, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mOrbiterUpdate", pLabel);
    if (!CompareSeedRoundMaterial(aLabel, pA.mOrbiterUpdate, pB.mOrbiterUpdate, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mWandererUpdate", pLabel);
    if (!CompareSeedRoundMaterial(aLabel, pA.mWandererUpdate, pB.mWandererUpdate, pError)) { return NO; }
    
    return YES;
}

static BOOL CompareDomainConstants(const char *pLabel,
                                   const TwistDomainConstants &pA,
                                   const TwistDomainConstants &pB,
                                   std::string *pError) {
    char aLabel[256];
    
    snprintf(aLabel, sizeof(aLabel), "%s.mIngress", pLabel);
    if (!CompareUInt64Value(aLabel, pA.mIngress, pB.mIngress, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mScatter", pLabel);
    if (!CompareUInt64Value(aLabel, pA.mScatter, pB.mScatter, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mCross", pLabel);
    if (!CompareUInt64Value(aLabel, pA.mCross, pB.mCross, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mDomainConstantPublicIngress", pLabel);
    if (!CompareUInt64Value(aLabel, pA.mDomainConstantPublicIngress, pB.mDomainConstantPublicIngress, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mDomainConstantPrivateIngress", pLabel);
    if (!CompareUInt64Value(aLabel, pA.mDomainConstantPrivateIngress, pB.mDomainConstantPrivateIngress, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mDomainConstantCrossIngress", pLabel);
    if (!CompareUInt64Value(aLabel, pA.mDomainConstantCrossIngress, pB.mDomainConstantCrossIngress, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMatrixSelectA", pLabel);
    if (!CompareUInt64Value(aLabel, pA.mMatrixSelectA, pB.mMatrixSelectA, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMatrixSelectB", pLabel);
    if (!CompareUInt64Value(aLabel, pA.mMatrixSelectB, pB.mMatrixSelectB, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMatrixUnrollA", pLabel);
    if (!CompareUInt8Value(aLabel, pA.mMatrixUnrollA, pB.mMatrixUnrollA, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMatrixUnrollB", pLabel);
    if (!CompareUInt8Value(aLabel, pA.mMatrixUnrollB, pB.mMatrixUnrollB, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMatrixArgA", pLabel);
    if (!CompareUInt8Value(aLabel, pA.mMatrixArgA, pB.mMatrixArgA, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMatrixArgB", pLabel);
    if (!CompareUInt8Value(aLabel, pA.mMatrixArgB, pB.mMatrixArgB, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMatrixArgC", pLabel);
    if (!CompareUInt8Value(aLabel, pA.mMatrixArgC, pB.mMatrixArgC, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMatrixArgD", pLabel);
    if (!CompareUInt8Value(aLabel, pA.mMatrixArgD, pB.mMatrixArgD, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMaskMutateA", pLabel);
    if (!CompareUInt8Value(aLabel, pA.mMaskMutateA, pB.mMaskMutateA, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mMaskMutateB", pLabel);
    if (!CompareUInt8Value(aLabel, pA.mMaskMutateB, pB.mMaskMutateB, pError)) { return NO; }
    
    return YES;
}

static BOOL CompareDomainBundle(const char *pLabel,
                                const TwistDomainBundle &pA,
                                const TwistDomainBundle &pB,
                                std::string *pError) {
    char aLabel[256];
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseASalts", pLabel);
    if (!CompareDomainSaltSet(aLabel, pA.mPhaseASalts, pB.mPhaseASalts, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseAConstants", pLabel);
    if (!CompareDomainConstants(aLabel, pA.mPhaseAConstants, pB.mPhaseAConstants, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseBSalts", pLabel);
    if (!CompareDomainSaltSet(aLabel, pA.mPhaseBSalts, pB.mPhaseBSalts, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseBConstants", pLabel);
    if (!CompareDomainConstants(aLabel, pA.mPhaseBConstants, pB.mPhaseBConstants, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseCSalts", pLabel);
    if (!CompareDomainSaltSet(aLabel, pA.mPhaseCSalts, pB.mPhaseCSalts, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseCConstants", pLabel);
    if (!CompareDomainConstants(aLabel, pA.mPhaseCConstants, pB.mPhaseCConstants, pError)) { return NO; }
    
    return YES;
}

static BOOL CompareKeyBoxA(const char *pLabel,
                           const TwistWorkSpace &pA,
                           const TwistWorkSpace &pB,
                           std::string *pError) {
    char aLabel[256];
    
    for (int aRow = 0; aRow < H_KEY_A; ++aRow) {
        for (int aCol = 0; aCol < W_KEY_A; ++aCol) {
            snprintf(aLabel, sizeof(aLabel), "%s.mKeyBoxA[%d][%d]", pLabel, aRow, aCol);
            if (!CompareUInt8Value(aLabel, pA.mKeyBoxA[aRow][aCol], pB.mKeyBoxA[aRow][aCol], pError)) {
                return NO;
            }
        }
    }
    
    return YES;
}

static BOOL CompareKeyBoxB(const char *pLabel,
                           const TwistWorkSpace &pA,
                           const TwistWorkSpace &pB,
                           std::string *pError) {
    char aLabel[256];
    
    for (int aRow = 0; aRow < H_KEY_B; ++aRow) {
        for (int aCol = 0; aCol < W_KEY_B; ++aCol) {
            snprintf(aLabel, sizeof(aLabel), "%s.mKeyBoxB[%d][%d]", pLabel, aRow, aCol);
            if (!CompareUInt8Value(aLabel, pA.mKeyBoxB[aRow][aCol], pB.mKeyBoxB[aRow][aCol], pError)) {
                return NO;
            }
        }
    }
    
    return YES;
}


static BOOL CompareMaskBoxA(const char *pLabel,
                            const TwistWorkSpace &pA,
                            const TwistWorkSpace &pB,
                            std::string *pError) {
    char aLabel[256];
    
    for (int aRow = 0; aRow < H_MASK_A; ++aRow) {
        for (int aCol = 0; aCol < W_MASK_A; ++aCol) {
            snprintf(aLabel, sizeof(aLabel), "%s.mMaskBoxA[%d][%d]", pLabel, aRow, aCol);
            if (!CompareUInt8Value(aLabel, pA.mMaskBoxA[aRow][aCol], pB.mMaskBoxA[aRow][aCol], pError)) {
                return NO;
            }
        }
    }
    
    return YES;
}

static BOOL CompareMaskBoxB(const char *pLabel,
                            const TwistWorkSpace &pA,
                            const TwistWorkSpace &pB,
                            std::string *pError) {
    char aLabel[256];
    
    for (int aRow = 0; aRow < H_MASK_B; ++aRow) {
        for (int aCol = 0; aCol < W_MASK_B; ++aCol) {
            snprintf(aLabel, sizeof(aLabel), "%s.mMaskBoxB[%d][%d]", pLabel, aRow, aCol);
            if (!CompareUInt8Value(aLabel, pA.mMaskBoxB[aRow][aCol], pB.mMaskBoxB[aRow][aCol], pError)) {
                return NO;
            }
        }
    }
    
    return YES;
}

static BOOL CompareWorkspaceBoxes(const char *pLabel,
                                  const TwistWorkSpace &pA,
                                  const TwistWorkSpace &pB,
                                  std::string *pError) {
    if (!CompareKeyBoxA(pLabel, pA, pB, pError)) { return NO; }
    if (!CompareKeyBoxB(pLabel, pA, pB, pError)) { return NO; }
    if (!CompareMaskBoxA(pLabel, pA, pB, pError)) { return NO; }
    if (!CompareMaskBoxB(pLabel, pA, pB, pError)) { return NO; }
    return YES;
}

- (void)testKerpalFixture {
    
    
    const char *pwd = "a man a plan canal";
    int ps = (int)strlen(pwd);
    
    // This is exported from something in G, as C++ code we can drop in over DemoExpander
    
    TwistExpander_Kerpal_0006 aExpanderA;
    //GTwistExpander aExpanderA;
    
    // This uses json load;
    GTwistExpander aExpanderB;
    
    std::string aLoadError;
    if (!aExpanderB.LoadJSONProjectRoot("CornTesting/Gen/Kerpal_0006.json", &aLoadError)) {
        XCTFail("%s", aLoadError.c_str());
        return;
    }
    
    unsigned char aSourceA[S_BLOCK];
    unsigned char aSourceB[S_BLOCK];
    
    TwistWorkSpace aWorkSpaceA;
    TwistWorkSpace aWorkSpaceB;
    
    memset(aWorkSpaceA.mWorkLaneA, 0, S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneB, 0, S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneC, 0, S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneD, 0, S_BLOCK);
    
    memset(aWorkSpaceB.mWorkLaneA, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneB, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneC, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneD, 0, S_BLOCK);
    
    memset(aWorkSpaceA.mExpansionLaneA, 0, S_BLOCK);
    memset(aWorkSpaceA.mExpansionLaneB, 0, S_BLOCK);
    memset(aWorkSpaceA.mExpansionLaneC, 0, S_BLOCK);
    memset(aWorkSpaceA.mExpansionLaneD, 0, S_BLOCK);
    
    memset(aWorkSpaceB.mExpansionLaneA, 0, S_BLOCK);
    memset(aWorkSpaceB.mExpansionLaneB, 0, S_BLOCK);
    memset(aWorkSpaceB.mExpansionLaneC, 0, S_BLOCK);
    memset(aWorkSpaceB.mExpansionLaneD, 0, S_BLOCK);
    
    memset(aWorkSpaceA.mOperationLaneA, 0, S_BLOCK);
    memset(aWorkSpaceA.mOperationLaneB, 0, S_BLOCK);
    memset(aWorkSpaceA.mOperationLaneC, 0, S_BLOCK);
    memset(aWorkSpaceA.mOperationLaneD, 0, S_BLOCK);
    
    memset(aWorkSpaceB.mOperationLaneA, 0, S_BLOCK);
    memset(aWorkSpaceB.mOperationLaneB, 0, S_BLOCK);
    memset(aWorkSpaceB.mOperationLaneC, 0, S_BLOCK);
    memset(aWorkSpaceB.mOperationLaneD, 0, S_BLOCK);
    
    memset(aWorkSpaceA.mSnowLaneA, 0, S_BLOCK);
    memset(aWorkSpaceA.mSnowLaneB, 0, S_BLOCK);
    memset(aWorkSpaceA.mSnowLaneC, 0, S_BLOCK);
    memset(aWorkSpaceA.mSnowLaneD, 0, S_BLOCK);
    
    memset(aWorkSpaceB.mSnowLaneA, 0, S_BLOCK);
    memset(aWorkSpaceB.mSnowLaneB, 0, S_BLOCK);
    memset(aWorkSpaceB.mSnowLaneC, 0, S_BLOCK);
    memset(aWorkSpaceB.mSnowLaneD, 0, S_BLOCK);
    
    
    for (int i=0;i<S_BLOCK;i++) {
        
        
        aWorkSpaceA.mWorkLaneA[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneA[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneB[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneB[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneC[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneC[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneD[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneD[i] = Random::GetByte();
        
        
        aWorkSpaceA.mExpansionLaneA[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneA[i] = Random::GetByte();
        aWorkSpaceA.mExpansionLaneB[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneB[i] = Random::GetByte();
        aWorkSpaceA.mExpansionLaneC[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneC[i] = Random::GetByte();
        aWorkSpaceA.mExpansionLaneD[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneD[i] = Random::GetByte();
        
        
        aWorkSpaceA.mOperationLaneA[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneA[i] = Random::GetByte();
        aWorkSpaceA.mOperationLaneB[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneB[i] = Random::GetByte();
        aWorkSpaceA.mOperationLaneC[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneC[i] = Random::GetByte();
        aWorkSpaceA.mOperationLaneD[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneD[i] = Random::GetByte();
        
        aWorkSpaceA.mSnowLaneA[i] = Random::GetByte();
        aWorkSpaceB.mSnowLaneA[i] = Random::GetByte();
        aWorkSpaceA.mSnowLaneB[i] = Random::GetByte();
        aWorkSpaceB.mSnowLaneB[i] = Random::GetByte();
        
        aWorkSpaceA.mSnowLaneC[i] = Random::GetByte();
        aWorkSpaceB.mSnowLaneC[i] = Random::GetByte();
        
        aWorkSpaceA.mSnowLaneD[i] = Random::GetByte();
        aWorkSpaceB.mSnowLaneD[i] = Random::GetByte();
        
    }
    
    /*
     memset(aWorkSpaceA.mWorkLaneA,0,S_BLOCK);
     memset(aWorkSpaceA.mWorkLaneB,0,S_BLOCK);
     memset(aWorkSpaceA.mWorkLaneC,0,S_BLOCK);
     memset(aWorkSpaceA.mWorkLaneD,0,S_BLOCK);
     memset(aWorkSpaceB.mWorkLaneA,0,S_BLOCK);
     memset(aWorkSpaceB.mWorkLaneB,0,S_BLOCK);
     memset(aWorkSpaceB.mWorkLaneC,0,S_BLOCK);
     memset(aWorkSpaceB.mWorkLaneD,0,S_BLOCK);
     */
    
    
    
    
    TwistFarmSalt aFarmSaltA;
    
    TwistFarmSalt aFarmSaltB;
    
    aExpanderA.Seed(&aWorkSpaceA, &aFarmSaltA, 0ULL, aSourceA, (std::uint8_t *)pwd, ps);
    aExpanderB.Seed(&aWorkSpaceB, &aFarmSaltB, 0ULL, aSourceB, (std::uint8_t *)pwd, ps);
    
    for (int i=0;i<S_BLOCK;i++) {
        if (aWorkSpaceA.mExpansionLaneA[i] != aWorkSpaceB.mExpansionLaneA[i]) {
            XCTFail("{export test} expand lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpansionLaneA[i], aWorkSpaceB.mExpansionLaneA[i]);
            return;
        }
        if (aWorkSpaceA.mExpansionLaneB[i] != aWorkSpaceB.mExpansionLaneB[i]) {
            XCTFail("{export test} expand lane b mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpansionLaneB[i], aWorkSpaceB.mExpansionLaneB[i]);
            return;
        }
        if (aWorkSpaceA.mExpansionLaneC[i] != aWorkSpaceB.mExpansionLaneC[i]) {
            XCTFail("{export test} expand lane c mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpansionLaneC[i], aWorkSpaceB.mExpansionLaneC[i]);
            return;
        }
        if (aWorkSpaceA.mExpansionLaneD[i] != aWorkSpaceB.mExpansionLaneD[i]) {
            XCTFail("{export test} expand lane d mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpansionLaneD[i], aWorkSpaceB.mExpansionLaneD[i]);
            return;
        }
        
    }
    
    for (int i=0;i<S_BLOCK;i++) {
        if (aWorkSpaceA.mOperationLaneA[i] != aWorkSpaceB.mOperationLaneA[i]) {
            XCTFail("{export test} oper lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mOperationLaneA[i], aWorkSpaceB.mOperationLaneA[i]);
            return;
        }
        if (aWorkSpaceA.mOperationLaneB[i] != aWorkSpaceB.mOperationLaneB[i]) {
            XCTFail("{export test} oper lane b mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mOperationLaneB[i], aWorkSpaceB.mOperationLaneB[i]);
            return;
        }
        if (aWorkSpaceA.mOperationLaneC[i] != aWorkSpaceB.mOperationLaneC[i]) {
            XCTFail("{export test} oper lane c mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mOperationLaneC[i], aWorkSpaceB.mOperationLaneC[i]);
            return;
        }
        if (aWorkSpaceA.mOperationLaneD[i] != aWorkSpaceB.mOperationLaneD[i]) {
            XCTFail("{export test} oper lane d mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mOperationLaneD[i], aWorkSpaceB.mOperationLaneD[i]);
            return;
        }
        
    }
    
    
    for (int i=0;i<S_BLOCK;i++) {
        
        if (aWorkSpaceA.mWorkLaneA[i] != aWorkSpaceB.mWorkLaneA[i]) {
            XCTFail("{export test} work lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneA[i], aWorkSpaceB.mWorkLaneA[i]);
            return;
        }
        
        if (aWorkSpaceA.mWorkLaneB[i] != aWorkSpaceB.mWorkLaneB[i]) {
            XCTFail("{export test} work lane b mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneB[i], aWorkSpaceB.mWorkLaneB[i]);
            return;
        }
        if (aWorkSpaceA.mWorkLaneC[i] != aWorkSpaceB.mWorkLaneC[i]) {
            XCTFail("{export test} work lane c mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneC[i], aWorkSpaceB.mWorkLaneC[i]);
            return;
        }
        if (aWorkSpaceA.mWorkLaneD[i] != aWorkSpaceB.mWorkLaneD[i]) {
            XCTFail("{export test} work lane d mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneD[i], aWorkSpaceB.mWorkLaneD[i]);
            return;
        }
        
    }
    
    
    for (int i=0;i<S_BLOCK;i++) {
        if (aWorkSpaceA.mSnowLaneA[i] != aWorkSpaceB.mSnowLaneA[i]) {
            XCTFail("{export test} snow lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mSnowLaneA[i], aWorkSpaceB.mSnowLaneA[i]);
            return;
        }
        if (aWorkSpaceA.mSnowLaneB[i] != aWorkSpaceB.mSnowLaneB[i]) {
            XCTFail("{export test} snow lane b mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mSnowLaneB[i], aWorkSpaceB.mSnowLaneB[i]);
            return;
        }
        if (aWorkSpaceA.mSnowLaneC[i] != aWorkSpaceB.mSnowLaneC[i]) {
            XCTFail("{export test} snow lane c mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mSnowLaneC[i], aWorkSpaceB.mSnowLaneC[i]);
            return;
        }
        if (aWorkSpaceA.mSnowLaneD[i] != aWorkSpaceB.mSnowLaneD[i]) {
            XCTFail("{export test} snow lane d mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mSnowLaneD[i], aWorkSpaceB.mSnowLaneD[i]);
            return;
        }
    }
    
    std::string aCompareError;
    
    aCompareError.clear();
    if (!CompareDomainBundle("workspace domain bundle",
                             aWorkSpaceA.mDomainBundle,
                             aWorkSpaceB.mDomainBundle,
                             &aCompareError)) {
        XCTFail("{export test} %s", aCompareError.c_str());
        return;
    }

    aCompareError.clear();
    if (!CompareWorkspaceBoxes("workspace boxes",
                               aWorkSpaceA,
                               aWorkSpaceB,
                               &aCompareError)) {
        XCTFail("{export test} %s", aCompareError.c_str());
        return;
    }

    aCompareError.clear();
    if (!CompareWorkspaceBoxes("workspace boxes",
                               aWorkSpaceA,
                               aWorkSpaceB,
                               &aCompareError)) {
        XCTFail("{export test} %s", aCompareError.c_str());
        return;
    }
    
}

- (void)testRotL32EmissionUsesRotL32 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::RotL32(GExpr::Symbol(aValue), GExpr::Const32(7)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("RotL32(") != std::string::npos,
                  "Expected RotL32 in emitted C++.");
    XCTAssertTrue(aLines[0].find("RotL16(") == std::string::npos,
                  "Unexpected RotL16 in emitted C++ for kRotL32.");
}

- (void)testBatchCommitStatementsEmitsTopLevelStatementsWithoutLoop {
    GBatch aBatch;
    std::vector<GStatement> aStatements;
    aStatements.push_back(GStatement::Assign(
        GTarget::Symbol(GSymbol::Var(TwistVariable::kOrbiterA)),
        GExpr::Const64(123ULL)));
    aBatch.CommitStatements(&aStatements);

    std::string aError;
    const std::string aBlock = aBatch.BuildCppScopeBlock(&aError, false);

    XCTAssertTrue(aError.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("for (") == std::string::npos,
                  "Top-level batch statements should not be emitted inside a loop.");
    XCTAssertTrue(aBlock.find("aOrbiterA = 123U;") != std::string::npos,
                  "Expected the top-level statement to be emitted directly.");

    GBatch aRuntimeBatch;
    std::vector<GStatement> aRuntimeStatements;
    aRuntimeStatements.push_back(GStatement::AddAssign(
        GTarget::Symbol(GSymbol::Var(TwistVariable::kOrbiterA)),
        GExpr::Const64(1ULL)));
    aRuntimeBatch.CommitStatements(&aRuntimeStatements);

    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    aVariables["aOrbiterA"] = 0ULL;
    aError.clear();
    XCTAssertTrue(aRuntimeBatch.ExecuteWithVariables(nullptr, nullptr, &aVariables, &aError),
                  "%s", aError.c_str());
    XCTAssertTrue(aVariables["aOrbiterA"] == 1ULL,
                  "Top-level batch statements should execute exactly once.");
}

- (void)testMaskBraidDiffusionEmitsDomainWordAndMaskingUsesIt {
    std::uint8_t aLaneA[16];
    std::uint8_t aLaneB[16];
    std::uint8_t aMask[16];
    for (int i = 0; i < 16; ++i) {
        aLaneA[i] = 0x0F;
        aLaneB[i] = 0xF0;
        aMask[i] = 0x00;
    }
    TwistMasking::MaskBraid(TwistMaskBraidType::kA,
                            aLaneA,
                            aLaneB,
                            16,
                            aMask,
                            16,
                            0xFF);
    for (int i = 0; i < 16; ++i) {
        XCTAssertTrue(aLaneA[i] == 0xF0,
                      "Mask domain word should mutate mask byte before braid.");
        XCTAssertTrue(aLaneB[i] == 0x0F,
                      "Mask domain word should mutate mask byte before braid.");
    }

    GRunMaskBraidDiffusionConfig aConfig;
    aConfig.mInputA = GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneA);
    aConfig.mInputB = GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneB);
    aConfig.mMaskLane = GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneA);
    aConfig.mMaskDomainWord = GSymbol::Var(TwistVariable::kDomainWordMaskMutateB);
    aConfig.mBraidType = TwistMaskBraidType::kB;

    GBatch aBatch;
    std::string aError;
    XCTAssertTrue(GRunMaskBraidDiffusion::Bake(aConfig, &aBatch, &aError),
                  "%s", aError.c_str());
    const std::string aBlock = aBatch.BuildCppScopeBlock(&aError, false);
    XCTAssertTrue(aError.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("TwistMasking::MaskBraid(TwistMaskBraidType::kB, aWorkLaneA, aWorkLaneB, S_BLOCK, aOperationLaneA, S_BLOCK, aDomainWordMaskMutateB);") != std::string::npos,
                  "Expected mask braid diffusion to emit the domain word argument.");
}

- (void)testMaskWeaveDiffusionEmitsDomainWord {
    GRunMaskWeaveDiffusionConfig aConfig;
    aConfig.mInputA = GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneA);
    aConfig.mInputB = GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneB);
    aConfig.mOutput = GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneC);
    aConfig.mMaskLane = GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneA);
    aConfig.mMaskDomainWord = GSymbol::Var(TwistVariable::kDomainWordMaskMutateB);
    aConfig.mWeaveType = TwistMaskWeaveType::kC;

    GBatch aBatch;
    std::string aError;
    XCTAssertTrue(GRunMaskWeaveDiffusion::Bake(aConfig, &aBatch, &aError),
                  "%s", aError.c_str());
    const std::string aBlock = aBatch.BuildCppScopeBlock(&aError, false);
    XCTAssertTrue(aError.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("TwistMasking::MaskWeave(TwistMaskWeaveType::kC, aWorkLaneA, aWorkLaneB, aWorkLaneC, S_BLOCK, aOperationLaneA, S_BLOCK, aDomainWordMaskMutateB);") != std::string::npos,
                  "Expected mask weave diffusion to emit the domain word argument.");
}

- (void)testInvestAndShiftBoxEmitAndExecute {
    GInvest aInvest;
    GShiftBox aShiftBox;
    std::vector<GStatement> aStatements;
    std::string aError;
    XCTAssertTrue(aInvest.BakeInvestBlockKeyBoxA(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneA),
                                                 &aStatements,
                                                 &aError),
                  "%s", aError.c_str());
    XCTAssertTrue(aShiftBox.BakeShiftMaskBoxA(&aStatements, &aError),
                  "%s", aError.c_str());

    GBatch aBatch;
    aBatch.CommitStatements(&aStatements);
    const std::string aBlock = aBatch.BuildCppScopeBlock(&aError, false);
    XCTAssertTrue(aError.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("TwistInvest::InvestBlockKeyBoxA(aWorkLaneA, pWorkSpace);") != std::string::npos,
                  "Expected GInvest to emit pWorkSpace-backed invest call.");
    XCTAssertTrue(aBlock.find("TwistShiftBox::ShiftMaskBoxA(pWorkSpace);") != std::string::npos,
                  "Expected GShiftBox to emit pWorkSpace-backed shift call.");

    GTwistExpander aExpander;
    TwistWorkSpace aWorkSpace;
    for (int i = 0; i < S_BLOCK; ++i) {
        aWorkSpace.mWorkLaneA[i] = 1;
    }
    aWorkSpace.mMaskBoxA[1][0] = 77;
    XCTAssertTrue(aBatch.Execute(&aWorkSpace, &aExpander, &aError),
                  "%s", aError.c_str());
    XCTAssertTrue(aWorkSpace.mKeyBoxA[0][0] != 0,
                  "Invest should mutate key box A from the configured source.");
    XCTAssertTrue(aWorkSpace.mMaskBoxA[0][0] == 77,
                  "ShiftMaskBoxA should call through to the workspace shift helper.");
}

- (void)testGFarmEmitsEphemeralAndWorkspaceDomainTargets {
    GFarm aFarm;
    std::vector<GStatement> aStatements;
    std::string aError;

    XCTAssertTrue(aFarm.BakeEphemeral(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneD),
                                      GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneC),
                                      GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneB),
                                      GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneA),
                                      "PhaseA",
                                      &aStatements,
                                      &aError),
                  "%s", aError.c_str());
    XCTAssertTrue(aFarm.BakeWorkspace(GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneC),
                                      GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneB),
                                      GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneA),
                                      GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneA),
                                      "mPhaseB",
                                      &aStatements,
                                      &aError),
                  "%s", aError.c_str());

    GBatch aBatch;
    aBatch.CommitStatements(&aStatements);
    const std::string aBlock = aBatch.BuildCppScopeBlock(&aError, false);
    XCTAssertTrue(aError.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("pFarmSalt->Derive(aWorkLaneD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltA") != std::string::npos,
                  "Expected ephemeral orbiter-assign salt farm round.");
    XCTAssertTrue(aBlock.find("pFarmSalt->Derive(aWorkLaneC, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltA") != std::string::npos,
                  "Expected ephemeral orbiter-update salt farm round.");
    XCTAssertTrue(aBlock.find("pFarmSalt->Derive(aWorkLaneB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltA") != std::string::npos,
                  "Expected ephemeral wanderer-update salt farm round.");
    XCTAssertTrue(aBlock.find("TwistFarmConstants::Derive(aWorkLaneA, &(mDomainBundleEphemeral.mPhaseAConstants));") != std::string::npos,
                  "Expected ephemeral constants farm round.");
    XCTAssertTrue(aBlock.find("pFarmSalt->Derive(aWorkLaneC, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA") != std::string::npos,
                  "Expected workspace orbiter-assign salt farm round.");
    XCTAssertTrue(aBlock.find("TwistFarmConstants::Derive(aOperationLaneA, &(pWorkSpace->mDomainBundle.mPhaseBConstants));") != std::string::npos,
                  "Expected workspace constants farm round.");
}

- (void)testKDFBuilderEmitsGroupedDeclarationsAndRandomInitializers {
    GTwistExpander aExpander;
    aExpander.mNameBase = "EmitShape";

    Builder_KDF aKDF;
    std::string aError;
    XCTAssertTrue(aKDF.Build(&aExpander, &aError),
                  "KDF build failed: %s", aError.c_str());

    const std::string aExportRoot = "/private/tmp/mm_kdf_emit_shape";
    XCTAssertTrue(aExpander.ExportCPPProjectRoot(aExportRoot, &aError),
                  "Export failed: %s", aError.c_str());

    std::vector<std::uint8_t> aCppBytes;
    const std::string aCppPath = FileIO::Join(aExportRoot, "TwistExpander_EmitShape.cpp");
    XCTAssertTrue(FileIO::Load(aCppPath, aCppBytes), "Failed to load emitted cpp file.");

    const std::string aCpp(aCppBytes.begin(), aCppBytes.end());
    XCTAssertTrue(aCpp.find("std::uint64_t aPrevious = 0; std::uint64_t aIngress = 0; std::uint64_t aCross = 0; std::uint64_t aScatter = 0;") != std::string::npos,
                  "Expected grouped core scalar declarations.");
    XCTAssertTrue(aCpp.find("std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;") != std::string::npos,
                  "Expected grouped orbiter declarations.");
    XCTAssertTrue(aCpp.find("std::uint64_t aWandererA = 0; std::uint64_t aWandererB = 0; std::uint64_t aWandererC = 0; std::uint64_t aWandererD = 0;") != std::string::npos,
                  "Expected grouped wanderer declarations.");
    XCTAssertTrue(aCpp.find("[[maybe_unused]] std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;") != std::string::npos,
                  "Expected exported snow lane aliases.");
    XCTAssertTrue(aCpp.find("[[maybe_unused]] std::size_t *aIndexList256A = mIndexList256A;") != std::string::npos,
                  "Expected exported index-list aliases to use expander members.");
    XCTAssertTrue(aCpp.find("pDomainSBoxSet") == std::string::npos,
                  "KDF export should not include S-box parameters.");
    XCTAssertTrue(aCpp.find("mSBox") == std::string::npos,
                  "KDF export should not include S-box aliases.");
    XCTAssertTrue(aCpp.find("aIndexList256A = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer") == std::string::npos,
                  "Index-list aliases should not use opaque workspace-slot lookups.");
    XCTAssertTrue(aCpp.find("void TwistExpander_EmitShape::KDF_A(") != std::string::npos,
                  "Expected exported KDF_A function.");
    XCTAssertTrue(aCpp.find("void TwistExpander_EmitShape::KDF_B(") != std::string::npos,
                  "Expected exported KDF_B function.");
    XCTAssertTrue(aCpp.find("void TwistExpander_EmitShape::KDF(std::uint64_t") == std::string::npos,
                  "Expected exported KDF wrapper to be omitted.");
    XCTAssertTrue(aCpp.find("aDestination = mDest") == std::string::npos,
                  "KDF export should not declare a destination alias.");
    XCTAssertTrue(aCpp.find("mDest == nullptr") == std::string::npos,
                  "KDF export should not require mDest.");
    XCTAssertTrue(aCpp.find("std::uint8_t aDomainWordMaskMutateA = pConstants->mMaskMutateA;") != std::string::npos,
                  "Mask mutate domain word should be byte-sized.");
    XCTAssertTrue(aCpp.find("kdf-a-matrix-diffusion") != std::string::npos,
                  "Expected Builder_KDF to include the matrix diffusion batch.");

    const std::size_t aKDFAStart = aCpp.find("void TwistExpander_EmitShape::KDF_A(");
    const std::size_t aSeedStart = aCpp.find("void TwistExpander_EmitShape::Seed(");
    XCTAssertTrue((aKDFAStart != std::string::npos) && (aSeedStart != std::string::npos) && (aKDFAStart < aSeedStart),
                  "Expected KDF functions before Seed.");
    const std::string aKDFText = aCpp.substr(aKDFAStart, aSeedStart - aKDFAStart);
    XCTAssertTrue(aKDFText.find("aKeyBoxUnrolledA") == std::string::npos,
                  "KDF export should not declare key box aliases.");
    XCTAssertTrue(aKDFText.find("aKeyRowReadA") == std::string::npos,
                  "KDF export should not declare key row aliases.");
    XCTAssertTrue(aKDFText.find("aMaskBoxUnrolledA") == std::string::npos,
                  "KDF export should not declare mask box aliases.");
    XCTAssertTrue(aKDFText.find("aMaskRowReadA") == std::string::npos,
                  "KDF export should not declare mask row aliases.");
    XCTAssertTrue(aKDFText.find("aSnowLaneA") == std::string::npos,
                  "KDF export should not declare snow lane aliases.");
    XCTAssertTrue(aKDFText.find("aMaskLaneA") == std::string::npos,
                  "KDF export should not declare mask lane aliases.");

    const std::size_t aLoop = aCpp.find("        for (std::size_t aIndex");
    const std::size_t aPreviousInit = aCpp.find("        aPrevious = ");
    const std::size_t aCarryInit = aCpp.find("        aCarry = ");
    const std::size_t aWandererKInit = aCpp.find("        aWandererK = ");
    XCTAssertTrue(aLoop != std::string::npos, "Expected generated KDF loop.");
    XCTAssertTrue((aPreviousInit != std::string::npos) && (aPreviousInit < aLoop),
                  "Expected aPrevious to be randomized before the KDF loop.");
    XCTAssertTrue((aCarryInit != std::string::npos) && (aCarryInit < aLoop),
                  "Expected aCarry to be randomized before the KDF loop.");
    XCTAssertTrue((aWandererKInit != std::string::npos) && (aWandererKInit < aLoop),
                  "Expected all wanderers to be randomized before the KDF loop.");
}

- (void)testSeederExportPreservesSetupBeforeKDF {
    GTwistExpander aExpander;
    aExpander.mNameBase = "SeederOrder";

    Builder_Seeder aSeeder;
    std::string aError;
    XCTAssertTrue(aSeeder.Build(&aExpander, &aError),
                  "Seeder build failed: %s", aError.c_str());

    const std::string aExportRoot = "/private/tmp/mm_seeder_order";
    XCTAssertTrue(aExpander.ExportCPPProjectRoot(aExportRoot, &aError),
                  "Export failed: %s", aError.c_str());

    std::vector<std::uint8_t> aCppBytes;
    const std::string aCppPath = FileIO::Join(aExportRoot, "TwistExpander_SeederOrder.cpp");
    XCTAssertTrue(FileIO::Load(aCppPath, aCppBytes), "Failed to load emitted cpp file.");

    const std::string aCpp(aCppBytes.begin(), aCppBytes.end());
    const std::size_t aZero = aCpp.find("TwistMemory::ZeroKeyBoxA");
    const std::size_t aSnow = aCpp.find("TwistSnow::");
    const std::size_t aSourceAssign = aCpp.find("    mSource = aSource;");
    const std::size_t aSnowAssign = aCpp.find("    mSnow = aSnowLane");
    const std::size_t aKDF = aCpp.find("    KDF_A(pNonce,");

    XCTAssertTrue(aZero != std::string::npos, "Expected exported seed memory zero.");
    XCTAssertTrue(aSnow != std::string::npos, "Expected exported seed snow setup.");
    XCTAssertTrue(aSourceAssign != std::string::npos, "Expected exported seed source assignment.");
    XCTAssertTrue(aSnowAssign != std::string::npos, "Expected exported seed KDF snow assignment.");
    XCTAssertTrue(aKDF != std::string::npos, "Expected exported seed KDF call.");
    XCTAssertTrue(aZero < aKDF, "Memory zero should export before KDF.");
    XCTAssertTrue(aSnow < aKDF, "Snow setup should export before KDF.");
    XCTAssertTrue(aSourceAssign < aKDF, "Source assignment should export before KDF.");
    XCTAssertTrue(aSnowAssign < aKDF, "Snow assignment should export before KDF.");
}



- (void)testRuntimeRawSnowLineMatchesExportedCounter {
    std::uint8_t aSource[S_BLOCK];
    for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); ++i) {
        aSource[i] = static_cast<std::uint8_t>((i * 37U + 11U) & 0xFFU);
    }

    TwistWorkSpace aWorkSpace;
    GTwistExpander aExpander;
    aExpander.mSource = aSource;

    std::uint8_t aExpectedA[S_BLOCK];
    std::uint8_t aExpectedB[S_BLOCK];
    std::uint8_t aExpectedC[S_BLOCK];
    std::uint8_t aExpectedD[S_BLOCK];
    TwistSnow::AES256Counter(aSource, aExpectedA);
    TwistSnow::ChaCha20Counter(aSource, aExpectedB);
    TwistSnow::Sha256Counter(aSource, aExpectedC);
    TwistSnow::Aria256Counter(aSource, aExpectedD);

    GBatch aBatch;
    std::vector<GStatement> aStatements;
    aStatements.push_back(GStatement::RawLine("TwistSnow::AES256Counter(aSource, aSnowLaneA);"));
    aStatements.push_back(GStatement::RawLine("TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);"));
    aStatements.push_back(GStatement::RawLine("TwistSnow::Sha256Counter(aSource, aSnowLaneC);"));
    aStatements.push_back(GStatement::RawLine("TwistSnow::Aria256Counter(aSource, aSnowLaneD);"));
    aBatch.CommitStatements(&aStatements);

    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    std::string aError;
    XCTAssertTrue(aBatch.ExecuteWithVariables(&aWorkSpace, &aExpander, &aVariables, &aError),
                  "Snow batch execution failed: %s", aError.c_str());
    XCTAssertTrue(std::memcmp(aExpectedA, aWorkSpace.mSnowLaneA, sizeof(aExpectedA)) == 0,
                  "AES snow runtime line did not match direct counter.");
    XCTAssertTrue(std::memcmp(aExpectedB, aWorkSpace.mSnowLaneB, sizeof(aExpectedB)) == 0,
                  "ChaCha snow runtime line did not match direct counter.");
    XCTAssertTrue(std::memcmp(aExpectedC, aWorkSpace.mSnowLaneC, sizeof(aExpectedC)) == 0,
                  "Sha snow runtime line did not match direct counter.");
    XCTAssertTrue(std::memcmp(aExpectedD, aWorkSpace.mSnowLaneD, sizeof(aExpectedD)) == 0,
                  "Aria snow runtime line did not match direct counter.");
}

- (void)testRuntimeMatrixRawLineAcceptsOneArgumentOps {
    TwistWorkSpace aWorkSpace;
    std::memset(aWorkSpace.mWorkLaneA, 0, S_BLOCK);
    std::memset(aWorkSpace.mWorkLaneB, 0, S_BLOCK);
    for (int i = 0; i < 64; ++i) {
        aWorkSpace.mWorkLaneA[i] = static_cast<std::uint8_t>(i);
    }

    GTwistExpander aExpander;
    GBatch aBatch;
    std::vector<GStatement> aStatements;
    aStatements.push_back(GStatement::RawLine("mMatrixA.LoadAndReset(aWorkLaneA + aMatrixLoadIndexA);"));
    aStatements.push_back(GStatement::RawLine("mMatrixA.ReverseRow(aMatrixArgA);"));
    aStatements.push_back(GStatement::RawLine("mMatrixA.Store(aWorkLaneB + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixUnrollWordA);"));
    aBatch.CommitStatements(&aStatements);

    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    aVariables["aMatrixLoadIndexA"] = 0ULL;
    aVariables["aMatrixStoreIndexA"] = 0ULL;
    aVariables["aMatrixArgA"] = 2ULL;
    aVariables["aMatrixUnrollWordA"] = 0ULL;

    std::string aError;
    XCTAssertTrue(aBatch.ExecuteWithVariables(&aWorkSpace, &aExpander, &aVariables, &aError),
                  "%s", aError.c_str());

    TwistFastMatrix aExpectedMatrix;
    std::uint8_t aExpected[64];
    aExpectedMatrix.LoadAndReset(aWorkSpace.mWorkLaneA);
    aExpectedMatrix.ReverseRow(2U);
    aExpectedMatrix.Store(aExpected, TwistFastMatrixUnrollScheme::kA, 0U);

    XCTAssertTrue(std::memcmp(aExpected, aWorkSpace.mWorkLaneB, sizeof(aExpected)) == 0,
                  "Runtime matrix raw-line execution should match direct C++ execution.");
}

- (void)testDiffuseAExpressionEmissionUsesTwistMix64 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::DiffuseA(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix64::DiffuseA(") != std::string::npos,
                  "Expected TwistMix64::DiffuseA call in emitted C++.");
}

- (void)testDiffuseBExpressionEmissionUsesTwistMix64 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::DiffuseB(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix64::DiffuseB(") != std::string::npos,
                  "Expected TwistMix64::DiffuseB call in emitted C++.");
}

- (void)testDiffuseCExpressionEmissionUsesTwistMix64 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::DiffuseC(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix64::DiffuseC(") != std::string::npos,
                  "Expected TwistMix64::DiffuseC call in emitted C++.");
}

- (void)testKDFParameterBuffersEmitDirectIndexedAccess {
    const GSymbol aInput = GSymbol::Var(TwistVariable::kParamInput);
    const GSymbol aOutput = GSymbol::Var(TwistVariable::kParamOutput);
    const GSymbol aIndex = GSymbol::Var(TwistVariable::kIndex);
    const GSymbol aIngress = GSymbol::Var(TwistVariable::kIngress);

    const GStatement aReadStatement = GStatement::Assign(
        GTarget::Symbol(aIngress),
        GExpr::Read(aInput, GExpr::Add(GExpr::Symbol(aIndex), GExpr::Const32(7))));
    const std::vector<std::string> aReadLines = aReadStatement.ToCPPStatements();

    XCTAssertTrue(aReadLines.size() == 1U,
                  "Expected a single C++ read statement line.");
    XCTAssertTrue(aReadLines[0].find("aSource[((aIndex + 7U)) & S_BLOCK1]") != std::string::npos,
                  "Expected direct aSource indexed read emission.");
    XCTAssertTrue(aReadLines[0].find("aInvalidBuffer") == std::string::npos,
                  "Parameter buffer read should not emit aInvalidBuffer.");

    const GStatement aWriteStatement = GStatement::Assign(
        GTarget::Write(aOutput, GExpr::Sub(GExpr::Const32(S_BLOCK1), GExpr::Symbol(aIndex))),
        GExpr::Symbol(aIngress));
    const std::vector<std::string> aWriteLines = aWriteStatement.ToCPPStatements();

    XCTAssertTrue(aWriteLines.size() == 1U,
                  "Expected a single C++ write statement line.");
    XCTAssertTrue(aWriteLines[0].find("aDestination[S_BLOCK1 - aIndex] = aIngress;") != std::string::npos,
                  "Expected direct aDestination indexed write emission.");
    XCTAssertTrue(aWriteLines[0].find("aInvalidBuffer") == std::string::npos,
                  "Parameter buffer write should not emit aInvalidBuffer.");
}

/*
- (void)testSeedMatrixRollupsEmitsExpansionLanes {
    GSeedMatrixRollups aRollups;
    std::string aError;
    XCTAssertTrue(aRollups.Plan(&aError), "Plan failed: %s", aError.c_str());

    GTwistExpander aExpander;
    aExpander.mNameBase = "EmitCheck";
    XCTAssertTrue(aRollups.Build(aExpander.mSeed, &aError), "Build failed: %s", aError.c_str());

    const std::string aExportRoot = "/private/tmp/mm_emit_check";
    XCTAssertTrue(aExpander.ExportCPPProjectRoot(aExportRoot, &aError), "Export failed: %s", aError.c_str());

    std::vector<std::uint8_t> aCppBytes;
    const std::string aCppPath = FileIO::Join(aExportRoot, "TwistExpander_EmitCheck.cpp");
    XCTAssertTrue(FileIO::Load(aCppPath, aCppBytes), "Failed to load emitted cpp file.");
    XCTAssertTrue(!aCppBytes.empty(), "Emitted cpp file was empty.");

    const std::string aCpp(aCppBytes.begin(), aCppBytes.end());
    XCTAssertTrue(aCpp.find("aExpandLaneA") != std::string::npos, "Expected expansion lane A emission.");
    XCTAssertTrue(aCpp.find("aExpandLaneB") != std::string::npos, "Expected expansion lane B emission.");
    XCTAssertTrue(aCpp.find("aExpandLaneC") != std::string::npos, "Expected expansion lane C emission.");
    XCTAssertTrue(aCpp.find("aExpandLaneD") != std::string::npos, "Expected expansion lane D emission.");
    XCTAssertTrue(aCpp.find("switch (aPrism % ") != std::string::npos, "Expected switch-based matrix case emission.");
}
*/


@end
