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
#include "Builder_Twister.hpp"
#include "Avalancher.hpp"
#include "FileIO.hpp"
#include "GAXSK.hpp"
#include "GFarm.hpp"
#include "GShiftBox.hpp"
#include "GSeedProgram.hpp"
#include "GRunMatrixDiffusion.hpp"
#include "GSeedRunSeed.hpp"
#include "GSquash.hpp"
#include "GTwistRunTwist.hpp"

#if __has_include("TwistExpander_GreekGoatHearder_060.hpp")
#include "TwistExpander_GreekGoatHearder_060.hpp"
#define MEAN_MACHINE_HAS_SPECIAL_CPP 1
#else
#define MEAN_MACHINE_HAS_SPECIAL_CPP 0
#endif
#include "GTwistExpander.hpp"
#include "TwistExpander.hpp"
#include "M88.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistMix32.hpp"
#include "TwistShiftBox.hpp"
#include "TwistSnow.hpp"
#include "TwistSquash.hpp"
#include <array>
#include <cctype>
#include <unordered_map>
#include <vector>

@interface CruelExportTest : XCTestCase

@end

@implementation CruelExportTest

class AvalancherToyExpander : public TwistExpander {
public:
    void TwistBlock(TwistWorkSpace *pWorkSpace,
                    std::uint64_t pNonce,
                    std::uint8_t *pSource,
                    std::size_t pBlockIndex,
                    std::size_t pBlockCount,
                    std::uint8_t *pDestination) override {
        TwistExpander::TwistBlock(pWorkSpace,
                                  pNonce,
                                  pSource,
                                  pBlockIndex,
                                  pBlockCount,
                                  pDestination);
        if ((pSource == nullptr) || (pDestination == nullptr)) {
            return;
        }

        std::uint8_t aCarry = static_cast<std::uint8_t>((pBlockIndex * 29U) +
                                                        (pBlockCount * 11U));
        for (std::size_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
            const std::uint8_t aRight = pSource[(aIndex + 1U) & S_BLOCK1];
            aCarry = static_cast<std::uint8_t>(aCarry + pSource[aIndex] +
                                               ((aRight << 1U) | (aRight >> 7U)) +
                                               static_cast<std::uint8_t>(aIndex));
            pDestination[aIndex] = aCarry;
        }
    }
};

- (void)testAvalancherUsesCandidatePointerForScoresAndStreams {
    AvalancherToyExpander aCandidate;
    std::string aPasswordA = "cat";
    std::string aPasswordB = "eat";

    Avalancher aAvalancher;
    aAvalancher.SetExpander(&aCandidate);
    aAvalancher.SetBlockCount(2U);

    const AvalancherScore aScore = aAvalancher.DiffAB(aPasswordA, aPasswordB);

    XCTAssertTrue(aScore.IsValid(), "Avalancher should compare generated output.");
    XCTAssertTrue(aScore.mByteCount == (S_BLOCK * 2U), "Avalancher should honor block count.");
    XCTAssertTrue(aScore.mDifferentBits > 0U, "Avalancher should report bit differences.");
    aScore.PrintExtended("AvalancherToyExpander");
    aScore.PrintQuick("AvalancherToyExpander");

    const std::vector<std::uint8_t> aOutput = aAvalancher.GetOutput(aPasswordA);
    XCTAssertTrue(aOutput.size() == (S_BLOCK * 2U), "Avalancher should return generated output.");

    const std::string aPath = "/private/tmp/mm_avalancher_stream.bin";
    XCTAssertTrue(aAvalancher.SavePractRandStream(aPasswordA, aPath),
                  "Avalancher should save a stream suitable for external tests.");

    std::vector<std::uint8_t> aLoaded;
    XCTAssertTrue(FileIO::Load(aPath, aLoaded), "Saved stream should load back.");
    XCTAssertTrue(aLoaded.size() == (S_BLOCK * 2U), "Saved stream should have the expected size.");
}

static BOOL SkeletonContainsNonceSlot(const GAXSKSkeleton &pSkeleton) {
    for (const GAXSKStatement &aStatement : pSkeleton.mStatements) {
        if (aStatement.mKind != GAXSKStatementKind::kContextWordAssign) {
            continue;
        }
        
        for (const GAXSKInputSlot &aSlot : aStatement.mContextWord.mSlots) {
            if (aSlot.mKind == GAXSKInputSlotKind::kNonceByte) {
                return YES;
            }
        }
    }
    
    return NO;
}

#if MEAN_MACHINE_HAS_SPECIAL_CPP
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

[[maybe_unused]] static BOOL CompareDomainBundle(const char *pLabel,
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

    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseDSalts", pLabel);
    if (!CompareDomainSaltSet(aLabel, pA.mPhaseDSalts, pB.mPhaseDSalts, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseDConstants", pLabel);
    if (!CompareDomainConstants(aLabel, pA.mPhaseDConstants, pB.mPhaseDConstants, pError)) { return NO; }

    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseESalts", pLabel);
    if (!CompareDomainSaltSet(aLabel, pA.mPhaseESalts, pB.mPhaseESalts, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseEConstants", pLabel);
    if (!CompareDomainConstants(aLabel, pA.mPhaseEConstants, pB.mPhaseEConstants, pError)) { return NO; }

    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseFSalts", pLabel);
    if (!CompareDomainSaltSet(aLabel, pA.mPhaseFSalts, pB.mPhaseFSalts, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseFConstants", pLabel);
    if (!CompareDomainConstants(aLabel, pA.mPhaseFConstants, pB.mPhaseFConstants, pError)) { return NO; }

    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseGSalts", pLabel);
    if (!CompareDomainSaltSet(aLabel, pA.mPhaseGSalts, pB.mPhaseGSalts, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseGConstants", pLabel);
    if (!CompareDomainConstants(aLabel, pA.mPhaseGConstants, pB.mPhaseGConstants, pError)) { return NO; }

    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseHSalts", pLabel);
    if (!CompareDomainSaltSet(aLabel, pA.mPhaseHSalts, pB.mPhaseHSalts, pError)) { return NO; }
    
    snprintf(aLabel, sizeof(aLabel), "%s.mPhaseHConstants", pLabel);
    if (!CompareDomainConstants(aLabel, pA.mPhaseHConstants, pB.mPhaseHConstants, pError)) { return NO; }
    
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


[[maybe_unused]] static BOOL CompareWorkspaceBoxes(const char *pLabel,
                                                   const TwistWorkSpace &pA,
                                                   const TwistWorkSpace &pB,
                                                   std::string *pError) {
    if (!CompareKeyBoxA(pLabel, pA, pB, pError)) { return NO; }
    if (!CompareKeyBoxB(pLabel, pA, pB, pError)) { return NO; }
    return YES;
}
#endif

- (void)testKerpalFixture {
#if MEAN_MACHINE_HAS_SPECIAL_CPP
    const char *pwd = "a man a plan canal";
    int ps = (int)strlen(pwd);

    TwistExpander_GreekGoatHearder_060 aExpander;
    TwistWorkSpace aWorkSpace;
    TwistFarmSalt aFarmSalt;
    unsigned char aSource[S_BLOCK];
    unsigned char aDest[S_BLOCK];

    std::memset(aSource, 0, sizeof(aSource));
    std::memset(aDest, 0, sizeof(aDest));
    aExpander.Seed(&aWorkSpace, &aFarmSalt, 0ULL, aSource, (std::uint8_t *)pwd, ps, aDest);

    std::uint8_t aTwistSource[S_BLOCK];
    std::uint8_t aTwistDest[S_BLOCK];
    std::memset(aTwistSource, 0x42, sizeof(aTwistSource));
    std::memset(aTwistDest, 0, sizeof(aTwistDest));
    aExpander.TwistBlock(&aWorkSpace, 1ULL, aTwistSource, 0U, 1U, aTwistDest);

    XCTAssertTrue(true, "Exported C++ fixture compiled and ran.");

#if 0
    
    // This is exported from something in G, as C++ code we can drop in over DemoExpander
    
    TwistExpander_GreekGoatHearder_060 aExpanderA;
    //GTwistExpander aExpanderA;
    
    // This uses json load;
    GTwistExpander aExpanderB;
    
    std::string aLoadError;
    if (!aExpanderB.LoadJSONProjectRoot("CornTesting/Gen/GreekGoatHearder_060.json", &aLoadError)) {
        XCTFail("%s", aLoadError.c_str());
        return;
    }
    
    unsigned char aSourceA[S_BLOCK];
    unsigned char aSourceB[S_BLOCK];
    
    unsigned char aDestA[S_BLOCK];
    unsigned char aDestB[S_BLOCK];
    
    
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
    
    aExpanderA.Seed(&aWorkSpaceA, &aFarmSaltA, 0ULL, aSourceA, (std::uint8_t *)pwd, ps, aDestA);
    aExpanderB.Seed(&aWorkSpaceB, &aFarmSaltB, 0ULL, aSourceB, (std::uint8_t *)pwd, ps, aDestB);
    
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
    
    
    
    /*
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
    */
    
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
    
    
    for (int i=0;i<S_BLOCK;i++) {
        if (aDestA[i] != aDestB[i]) {
            XCTFail("{export test} dest lane mismatched at %d: A=%u B=%u", i, aDestA[i], aDestB[i]);
            return;
        }
    }
    
#endif
#endif
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

- (void)testIgnoreNoncesProducesNonceFreeSkeletonAndExportedStage {
    GAXSK aAXSK;
    std::vector<GAXSKSkeleton> aSkeletons;
    std::string aError;
    
    XCTAssertTrue(aAXSK.Bake(GAXSFormat::kN5,
                             true,
                             {3, 4, 4, 4},
                             false,
                             GAssignType::kSet,
                             &aSkeletons,
                             &aError),
                  "GAXSK bake failed: %s", aError.c_str());
    XCTAssertFalse(aSkeletons.empty(), "Expected ignored-nonce bake to produce skeletons.");
    
    for (const GAXSKSkeleton &aSkeleton : aSkeletons) {
        XCTAssertFalse(SkeletonContainsNonceSlot(aSkeleton),
                       "pIgnoreNonces should remove nonce input slots.");
    }
    
    GTwistExpander aExpander;
    aExpander.mNameBase = "IgnoreNonceStage";
    
    auto aBuildStage = [&](auto &pStage, const char *pName) {
        XCTAssertTrue(pStage.Plan(&aError), "%s plan failed: %s", pName, aError.c_str());
        XCTAssertTrue(pStage.Build(aExpander.mSeed, &aError), "%s build failed: %s", pName, aError.c_str());
    };
    
    GTwistRunTwist_A aTwistA;
    GTwistRunTwist_B aTwistB;
    GTwistRunTwist_C aTwistC;
    GSeedRunSeed_C aSeedC(false);
    GSeedRunSeed_D aSeedD(false);
    aBuildStage(aTwistA, "GTwistRunTwist_A");
    aBuildStage(aTwistB, "GTwistRunTwist_B");
    aBuildStage(aTwistC, "GTwistRunTwist_C");
    aBuildStage(aSeedC, "GSeedRunSeed_C");
    aBuildStage(aSeedD, "GSeedRunSeed_D");
    
    const std::string aExportRoot = "/private/tmp/mm_ignore_nonce_stage";
    XCTAssertTrue(aExpander.ExportCPPProjectRoot(aExportRoot, &aError),
                  "Export failed: %s", aError.c_str());
    
    std::vector<std::uint8_t> aCppBytes;
    const std::string aCppPath = FileIO::Join(aExportRoot, "TwistExpander_IgnoreNonceStage.cpp");
    XCTAssertTrue(FileIO::Load(aCppPath, aCppBytes), "Failed to load emitted cpp file.");
    
    const std::string aCpp(aCppBytes.begin(), aCppBytes.end());
    XCTAssertTrue(aCpp.find("aNonceByte") == std::string::npos,
                  "Ignored-nonce stage export should not declare or reference nonce bytes.");
    XCTAssertTrue(aCpp.find("pNonce >>") == std::string::npos,
                  "Ignored-nonce stage export should not derive nonce bytes.");
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
    XCTAssertTrue(aFarm.BakeInbuilt(GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneD),
                                    GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneC),
                                    GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneB),
                                    GSymbol::Buf(TwistWorkSpaceSlot::kOperationLaneA),
                                    "D",
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
    XCTAssertTrue(aBlock.find("pFarmSalt->Derive(aOperationLaneD, mDomainBundleInbuilt.mPhaseDSalts.mOrbiterAssign.mSaltA") != std::string::npos,
                  "Expected inbuilt phase D orbiter-assign salt farm round.");
    XCTAssertTrue(aBlock.find("TwistFarmConstants::Derive(aOperationLaneA, &(mDomainBundleInbuilt.mPhaseDConstants));") != std::string::npos,
                  "Expected inbuilt phase D constants farm round.");
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
    std::vector<std::uint8_t> aHppBytes;
    const std::string aHppPath = FileIO::Join(aExportRoot, "TwistExpander_EmitShape.hpp");
    XCTAssertTrue(FileIO::Load(aHppPath, aHppBytes), "Failed to load emitted hpp file.");

    const std::string aCpp(aCppBytes.begin(), aCppBytes.end());
    const std::string aHpp(aHppBytes.begin(), aHppBytes.end());
    XCTAssertTrue(aCpp.find("std::uint64_t aPrevious = 0x") != std::string::npos &&
                  aCpp.find("std::uint64_t aIngress = 0x") != std::string::npos &&
                  aCpp.find("std::uint64_t aCarry = 0x") != std::string::npos,
                  "Expected fixed-random core scalar declarations.");
    if (aCpp.find("std::uint64_t aOrbiterA") != std::string::npos) {
        XCTAssertTrue(aCpp.find("std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;") != std::string::npos,
                      "Expected grouped orbiter declarations when orbiters are active.");
    }
    XCTAssertTrue(aCpp.find("std::uint64_t aWandererA = 0x") != std::string::npos &&
                  aCpp.find("std::uint64_t aWandererB = 0x") != std::string::npos &&
                  aCpp.find("std::uint64_t aWandererC = 0x") != std::string::npos &&
                  aCpp.find("std::uint64_t aWandererD = 0x") != std::string::npos,
                  "Expected fixed-random wanderer declarations.");
    XCTAssertTrue(aCpp.find("aSnowLane") == std::string::npos,
                  "KDF export should not declare workspace snow lane aliases.");
    XCTAssertTrue(aCpp.find("mDomainBundleInbuilt.mPhaseESalts = kPhaseESalts;") != std::string::npos,
                  "Expected exported constructor to install phase E salts.");
    XCTAssertTrue(aCpp.find("const TwistDomainConstants TwistExpander_EmitShape::kPhaseFConstants") != std::string::npos,
                  "Expected exported phase F constants definition.");
    XCTAssertTrue(aCpp.find("const TwistDomainConstants TwistExpander_EmitShape::kPhaseGConstants") != std::string::npos,
                  "Expected exported phase G constants definition.");
    XCTAssertTrue(aCpp.find("const TwistDomainConstants TwistExpander_EmitShape::kPhaseHConstants") != std::string::npos,
                  "Expected exported phase H constants definition.");
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
    XCTAssertTrue(aCpp.find("KDF_A_A kdf_a_loop_a:") != std::string::npos,
                  "Expected generated KDF-A ARX call marker.");
    XCTAssertTrue(aCpp.find("KDF_A_B kdf_a_loop_b:") != std::string::npos,
                  "Expected generated KDF-A/B ARX call marker.");
    XCTAssertTrue(aCpp.find("KDF_A_C kdf_a_loop_c:") != std::string::npos,
                  "Expected generated KDF-A/C ARX call marker.");
    XCTAssertTrue(aCpp.find("KDF_A_D kdf_a_loop_d:") != std::string::npos,
                  "Expected generated KDF-A/D ARX call marker.");
    XCTAssertTrue(aCpp.find("KDF_B_A kdf_b_loop_a:") != std::string::npos,
                  "Expected generated KDF-B/A ARX call marker.");
    XCTAssertTrue(aCpp.find("KDF_B_B kdf_b_loop_b:") != std::string::npos,
                  "Expected generated KDF-B/B ARX call marker.");
    XCTAssertTrue(aCpp.find("KDF_B_C kdf_b_loop_c:") != std::string::npos,
                  "Expected generated KDF-B/C ARX call marker.");
    XCTAssertTrue(aCpp.find("KDF_B_D kdf_b_loop_d:") != std::string::npos,
                  "Expected generated KDF-B/D ARX call marker.");
    XCTAssertTrue(aHpp.find("#include \"TwistExpander_EmitShape_Arx.hpp\"") != std::string::npos,
                  "Expected KDF export header to include its ARX companion.");
    XCTAssertTrue(aCpp.find("#include \"TwistExpander_EmitShape_Arx.hpp\"") == std::string::npos,
                  "Expected KDF export cpp to get the ARX type through its header.");
    XCTAssertTrue(aCpp.find("TwistExpander_EmitShape_Arx aArx;") == std::string::npos,
                  "Expected KDF export to call the ARX companion statically.");
    XCTAssertTrue(aCpp.find("TwistExpander_EmitShape_Arx::KDF_A_A(") != std::string::npos,
                  "Expected KDF export to call the ARX companion statically.");
    XCTAssertTrue(aCpp.find("TwistExpander_EmitShape_Arx::KDF_A_B(") != std::string::npos,
                  "Expected KDF export to call the ARX companion for KDF_A_B.");
    XCTAssertTrue(aCpp.find("TwistExpander_EmitShape_Arx::KDF_A_C(") != std::string::npos,
                  "Expected KDF export to call the ARX companion for KDF_A_C.");
    XCTAssertTrue(aCpp.find("TwistExpander_EmitShape_Arx::KDF_A_D(") != std::string::npos,
                  "Expected KDF export to call the ARX companion for KDF_A_D.");
    XCTAssertTrue(aCpp.find("TwistExpander_EmitShape_Arx::KDF_B_A(") != std::string::npos,
                  "Expected KDF export to call the ARX companion for KDF_B_A.");
    XCTAssertTrue(aCpp.find("TwistExpander_EmitShape_Arx::KDF_B_B(") != std::string::npos,
                  "Expected KDF export to call the ARX companion for KDF_B_B.");
    XCTAssertTrue(aCpp.find("TwistExpander_EmitShape_Arx::KDF_B_C(") != std::string::npos,
                  "Expected KDF export to call the ARX companion for KDF_B_C.");
    XCTAssertTrue(aCpp.find("TwistExpander_EmitShape_Arx::KDF_B_D(") != std::string::npos,
                  "Expected KDF export to call the ARX companion for KDF_B_D.");
    XCTAssertTrue(aCpp.find("GSeedRunKDF_A_A kdf_a_loop_a (start)") == std::string::npos,
                  "Expected KDF export to omit the old inline KDF_A_A marker.");
    XCTAssertTrue(aCpp.find("GSeedRunKDF_A_B kdf_a_loop_b (start)") == std::string::npos,
                  "Expected KDF export to omit the old inline KDF_A_B marker.");
    XCTAssertTrue(aCpp.find("GSeedRunKDF_A_C kdf_a_loop_c (start)") == std::string::npos,
                  "Expected KDF export to omit the old inline KDF_A_C marker.");
    XCTAssertTrue(aCpp.find("GSeedRunKDF_A_D kdf_a_loop_d (start)") == std::string::npos,
                  "Expected KDF export to omit the old inline KDF_A_D marker.");
    XCTAssertTrue(aCpp.find("GSeedRunKDF_B_A kdf_b_loop_a (start)") == std::string::npos,
                  "Expected KDF export to omit the old inline KDF_B_A marker.");
    XCTAssertTrue(aCpp.find("GSeedRunKDF_B_B kdf_b_loop_b (start)") == std::string::npos,
                  "Expected KDF export to omit the old inline KDF_B_B marker.");
    XCTAssertTrue(aCpp.find("GSeedRunKDF_B_C kdf_b_loop_c (start)") == std::string::npos,
                  "Expected KDF export to omit the old inline KDF_B_C marker.");
    XCTAssertTrue(aCpp.find("GSeedRunKDF_B_D kdf_b_loop_d (start)") == std::string::npos,
                  "Expected KDF export to omit the old inline KDF_B_D marker.");
    XCTAssertTrue(aCpp.find("aDestination = mDest") == std::string::npos,
                  "KDF export should not declare a destination alias.");
    XCTAssertTrue(aCpp.find("std::uint8_t *mSource") == std::string::npos,
                  "KDF export should not declare a source member alias.");
    XCTAssertTrue(aCpp.find("mDest == nullptr") == std::string::npos,
                  "KDF export should not require mDest.");
    XCTAssertTrue(aCpp.find("aDomainWordMaskMutateA") == std::string::npos,
                  "Generated export should not use mask mutate domain word A.");
    XCTAssertTrue(aCpp.find("aDomainWordMaskMutateB") == std::string::npos,
                  "Generated export should not use mask mutate domain word B.");
    XCTAssertTrue(aCpp.find("TwistDiffuse::DiffuseWithDomainWords(aWorkLaneA, aWorkLaneB,  // input lanes") != std::string::npos &&
                  aCpp.find("aExpandLaneA, aExpandLaneB, // output lanes") != std::string::npos,
                  "Expected Builder_KDF to include the KDF-A work-to-expansion matrix diffusion.");
    XCTAssertTrue(aCpp.find("TwistDiffuse::DiffuseWithDomainWords(aExpandLaneA, aExpandLaneB,  // input lanes") != std::string::npos &&
                  aCpp.find("aWorkLaneA, aWorkLaneB, // output lanes") != std::string::npos,
                  "Expected Builder_KDF to include the KDF-B expansion-to-work matrix diffusion.");

    const std::size_t aKDFAStart = aCpp.find("void TwistExpander_EmitShape::KDF_A(");
    const std::size_t aSeedStart = aCpp.find("void TwistExpander_EmitShape::Seed(");
    XCTAssertTrue((aKDFAStart != std::string::npos) && (aSeedStart != std::string::npos) && (aKDFAStart < aSeedStart),
                  "Expected KDF functions before Seed.");
    const std::string aKDFText = aCpp.substr(aKDFAStart, aSeedStart - aKDFAStart);
    XCTAssertTrue(aKDFText.find("aKeyBoxUnrolledA") == std::string::npos,
                  "KDF export should not declare key box aliases.");
    XCTAssertTrue(aKDFText.find("aKeyRowReadA") == std::string::npos,
                  "KDF export should not declare key row aliases.");
    XCTAssertTrue(aKDFText.find("aSnowLane") == std::string::npos,
                  "KDF export should not declare snow lane aliases.");
    XCTAssertTrue(aKDFText.find("aMaskLaneA") == std::string::npos,
                  "KDF export should not declare mask lane aliases.");

    const std::size_t aFirstArxCall = aCpp.find("    TwistExpander_EmitShape_Arx::KDF_A_A(");
    const std::size_t aPreviousInit = aCpp.find("        aPrevious = ");
    const std::size_t aCarryInit = aCpp.find("        aCarry = ");
    const std::size_t aWandererKInit = aCpp.find("        aWandererK = ");
    XCTAssertTrue(aFirstArxCall != std::string::npos, "Expected generated KDF ARX call.");
    XCTAssertTrue((aPreviousInit != std::string::npos) && (aPreviousInit < aFirstArxCall),
                  "Expected aPrevious to be randomized before the KDF ARX call.");
    XCTAssertTrue((aCarryInit != std::string::npos) && (aCarryInit < aFirstArxCall),
                  "Expected aCarry to be randomized before the KDF ARX call.");
    XCTAssertTrue((aWandererKInit != std::string::npos) && (aWandererKInit < aFirstArxCall),
                  "Expected all wanderers to be randomized before the KDF ARX call.");
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
    auto CountText = [](const std::string &pText, const std::string &pNeedle) -> std::size_t {
        std::size_t aCount = 0U;
        std::size_t aOffset = pText.find(pNeedle);
        while (aOffset != std::string::npos) {
            aCount += 1U;
            aOffset = pText.find(pNeedle, aOffset + pNeedle.size());
        }
        return aCount;
    };
    const std::size_t aZero = aCpp.find("TwistMemory::ZeroKeyBoxA");
    const std::size_t aSnow = aCpp.find("TwistSnow::");
    std::size_t aFourthSnow = aSnow;
    for (int i = 1; (i < 4) && (aFourthSnow != std::string::npos); ++i) {
        aFourthSnow = aCpp.find("TwistSnow::", aFourthSnow + 1U);
    }
    const std::size_t aSnowAssign = aCpp.find("    mSnow = aSnowLane");
    const std::size_t aKDF = aCpp.find("    KDF_A(pNonce,");
    const std::size_t aSnowAssignA = CountText(aCpp, "    mSnow = aSnowLaneA;");
    const std::size_t aSnowAssignB = CountText(aCpp, "    mSnow = aSnowLaneB;");
    const std::size_t aSnowAssignC = CountText(aCpp, "    mSnow = aSnowLaneC;");
    const std::size_t aSnowAssignD = CountText(aCpp, "    mSnow = aSnowLaneD;");

    XCTAssertTrue(aZero != std::string::npos, "Expected exported seed memory zero.");
    XCTAssertTrue(aSnow != std::string::npos, "Expected exported seed snow setup.");
    XCTAssertTrue(aFourthSnow != std::string::npos, "Expected exported seed to build four snow lanes.");
    XCTAssertTrue(aCpp.find("    mSource = pSource;") == std::string::npos,
                  "Base Seed already points mSource at pSource.");
    XCTAssertTrue(aCpp.find("[[maybe_unused]] std::uint8_t *aSource = TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(0));") == std::string::npos,
                  "Seed export should not declare an opaque source alias.");
    XCTAssertTrue(aCpp.find("[[maybe_unused]] std::uint8_t *aDestination = TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(1));") == std::string::npos,
                  "Seed export should not declare an opaque destination alias.");
    XCTAssertTrue(aCpp.find("aSnowLaneA = pWorkSpace->mSnowLaneA") != std::string::npos &&
                  aCpp.find("aSnowLaneB = pWorkSpace->mSnowLaneB") != std::string::npos &&
                  aCpp.find("aSnowLaneC = pWorkSpace->mSnowLaneC") != std::string::npos &&
                  aCpp.find("aSnowLaneD = pWorkSpace->mSnowLaneD") != std::string::npos,
                  "Seed export should declare all four snow lane aliases.");
    XCTAssertTrue(CountText(aCpp, " = pWorkSpace->mInvestLane") == 8U,
                  "Seed export should capture all eight KDF-B phases into shuffled invest lanes.");
    XCTAssertTrue(CountText(aCpp, "TwistSquash::Squash") == 9U,
                  "Seed export should emit eight invest-lane squashes plus the final output squash.");
    XCTAssertTrue(CountText(aCpp, "KDF_B Phase") == 16U,
                  "Seed export should bracket each KDF-B invest capture with searchable phase comments.");
    XCTAssertTrue(aSnowAssign != std::string::npos, "Expected exported seed KDF snow assignment.");
    XCTAssertTrue(aKDF != std::string::npos, "Expected exported seed KDF call.");
    XCTAssertTrue(CountText(aCpp, "    KDF_A(pNonce,") == 8U,
                  "Expected seed KDF_A to run once for each phase A-H.");
    XCTAssertTrue(CountText(aCpp, "    mSnow = aSnowLane") == 8U,
                  "Expected seed KDF snow assignment once per phase.");
    XCTAssertTrue(aSnowAssignA <= 2U && aSnowAssignB <= 2U && aSnowAssignC <= 2U && aSnowAssignD <= 2U,
                  "Expected each snow lane to be used at most twice.");
    XCTAssertTrue(aZero < aKDF, "Memory zero should export before KDF.");
    XCTAssertTrue(aSnow < aKDF, "Snow setup should export before KDF.");
    XCTAssertTrue(aFourthSnow < aSnowAssign, "All snow lanes should be built before KDF snow assignment.");
    XCTAssertTrue(aSnowAssign < aKDF, "Snow assignment should export before KDF.");
}

- (void)testTwisterExportUsesNamedTwistRunStages {
    GTwistExpander aExpander;
    aExpander.mNameBase = "TwisterStageNames";

    Builder_Twister aTwister;
    std::string aError;
    XCTAssertTrue(aTwister.Build(&aExpander, &aError),
                  "Twister build failed: %s", aError.c_str());

    const std::string aExportRoot = "/private/tmp/mm_twister_stage_names";
    XCTAssertTrue(aExpander.ExportCPPProjectRoot(aExportRoot, &aError),
                  "Export failed: %s", aError.c_str());

    std::vector<std::uint8_t> aCppBytes;
    const std::string aCppPath = FileIO::Join(aExportRoot, "TwistExpander_TwisterStageNames.cpp");
    XCTAssertTrue(FileIO::Load(aCppPath, aCppBytes), "Failed to load emitted cpp file.");
    std::vector<std::uint8_t> aHppBytes;
    const std::string aHppPath = FileIO::Join(aExportRoot, "TwistExpander_TwisterStageNames.hpp");
    XCTAssertTrue(FileIO::Load(aHppPath, aHppBytes), "Failed to load emitted hpp file.");
    std::vector<std::uint8_t> aArxCppBytes;
    const std::string aArxCppPath = FileIO::Join(aExportRoot, "TwistExpander_TwisterStageNames_Arx.cpp");
    XCTAssertTrue(FileIO::Load(aArxCppPath, aArxCppBytes), "Failed to load emitted ARX cpp file.");
    std::vector<std::uint8_t> aArxHppBytes;
    const std::string aArxHppPath = FileIO::Join(aExportRoot, "TwistExpander_TwisterStageNames_Arx.hpp");
    XCTAssertTrue(FileIO::Load(aArxHppPath, aArxHppBytes), "Failed to load emitted ARX hpp file.");

    const std::string aCpp(aCppBytes.begin(), aCppBytes.end());
    const std::string aHpp(aHppBytes.begin(), aHppBytes.end());
    const std::string aArxCpp(aArxCppBytes.begin(), aArxCppBytes.end());
    const std::string aArxHpp(aArxHppBytes.begin(), aArxHppBytes.end());
    auto CountText = [](const std::string &pText, const std::string &pNeedle) -> std::size_t {
        std::size_t aCount = 0U;
        std::size_t aOffset = pText.find(pNeedle);
        while (aOffset != std::string::npos) {
            aCount += 1U;
            aOffset = pText.find(pNeedle, aOffset + pNeedle.size());
        }
        return aCount;
    };
    XCTAssertTrue(aHpp.find("std::size_t pBlockIndex") != std::string::npos,
                  "Expected exported TwistBlock declaration to include block index.");
    XCTAssertTrue(aHpp.find("std::size_t pBlockCount") != std::string::npos,
                  "Expected exported TwistBlock declaration to include block count.");
    XCTAssertTrue(aArxHpp.find("class TwistExpander_TwisterStageNames_Arx {") != std::string::npos,
                  "Expected exported ARX companion class.");
    XCTAssertTrue(aArxHpp.find("void KDF_A_A(") != std::string::npos,
                  "Expected exported ARX companion KDF_A_A declaration.");
    XCTAssertTrue(aArxHpp.find("void KDF_A_B(") != std::string::npos,
                  "Expected exported ARX companion KDF_A_B declaration.");
    XCTAssertTrue(aArxHpp.find("void KDF_A_C(") != std::string::npos,
                  "Expected exported ARX companion KDF_A_C declaration.");
    XCTAssertTrue(aArxHpp.find("void KDF_A_D(") != std::string::npos,
                  "Expected exported ARX companion KDF_A_D declaration.");
    XCTAssertTrue(aArxHpp.find("void KDF_B_A(") != std::string::npos,
                  "Expected exported ARX companion KDF_B_A declaration.");
    XCTAssertTrue(aArxHpp.find("void KDF_B_B(") != std::string::npos,
                  "Expected exported ARX companion KDF_B_B declaration.");
    XCTAssertTrue(aArxHpp.find("void KDF_B_C(") != std::string::npos,
                  "Expected exported ARX companion KDF_B_C declaration.");
    XCTAssertTrue(aArxHpp.find("void KDF_B_D(") != std::string::npos,
                  "Expected exported ARX companion KDF_B_D declaration.");
    XCTAssertTrue(aArxHpp.find("void Seed_A(") != std::string::npos,
                  "Expected exported ARX companion Seed_A declaration.");
    XCTAssertTrue(aArxHpp.find("void Seed_B(") != std::string::npos,
                  "Expected exported ARX companion Seed_B declaration.");
    XCTAssertTrue(aArxHpp.find("void Seed_C(") != std::string::npos,
                  "Expected exported ARX companion Seed_C declaration.");
    XCTAssertTrue(aArxHpp.find("void Seed_D(") != std::string::npos,
                  "Expected exported ARX companion Seed_D declaration.");
    XCTAssertTrue(aArxHpp.find("void Twist_A(") != std::string::npos,
                  "Expected exported ARX companion Twist_A declaration.");
    XCTAssertTrue(aArxHpp.find("void Twist_B(") != std::string::npos,
                  "Expected exported ARX companion Twist_B declaration.");
    XCTAssertTrue(aArxHpp.find("override") == std::string::npos,
                  "Expected exported ARX companion to use static helpers.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::KDF_A_A(") != std::string::npos,
                  "Expected exported ARX companion KDF_A_A definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::KDF_A_B(") != std::string::npos,
                  "Expected exported ARX companion KDF_A_B definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::KDF_A_C(") != std::string::npos,
                  "Expected exported ARX companion KDF_A_C definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::KDF_A_D(") != std::string::npos,
                  "Expected exported ARX companion KDF_A_D definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::KDF_B_A(") != std::string::npos,
                  "Expected exported ARX companion KDF_B_A definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::KDF_B_B(") != std::string::npos,
                  "Expected exported ARX companion KDF_B_B definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::KDF_B_C(") != std::string::npos,
                  "Expected exported ARX companion KDF_B_C definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::KDF_B_D(") != std::string::npos,
                  "Expected exported ARX companion KDF_B_D definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::Seed_A(") != std::string::npos,
                  "Expected exported ARX companion Seed_A definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::Seed_B(") != std::string::npos,
                  "Expected exported ARX companion Seed_B definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::Seed_C(") != std::string::npos,
                  "Expected exported ARX companion Seed_C definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::Seed_D(") != std::string::npos,
                  "Expected exported ARX companion Seed_D definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::Twist_A(") != std::string::npos,
                  "Expected exported ARX companion Twist_A definition.");
    XCTAssertTrue(aArxCpp.find("void TwistExpander_TwisterStageNames_Arx::Twist_B(") != std::string::npos,
                  "Expected exported ARX companion Twist_B definition.");
    XCTAssertTrue(aArxCpp.find("std::uint64_t aWandererA = *pWandererA;") != std::string::npos,
                  "Expected KDF_A_A to load wanderer state from pointer.");
    XCTAssertTrue(aArxCpp.find("*pWandererA = aWandererA;") != std::string::npos,
                  "Expected KDF_A_A to store wanderer state back to pointer.");
    XCTAssertTrue(aArxCpp.find("std::uint64_t aIngress = *pIngress;") != std::string::npos,
                  "Expected KDF_A_A to load ingress state from pointer.");
    XCTAssertTrue(aArxCpp.find("*pIngress = aIngress;") != std::string::npos,
                  "Expected KDF_A_A to store ingress state back to pointer.");
    XCTAssertTrue(aArxCpp.find("nullptr") == std::string::npos,
                  "Expected exported ARX helper to omit defensive null checks.");
    XCTAssertTrue(CountText(aArxCpp, "// kdf_a_loop_a loop ") == 6U,
                  "Expected exported KDF_A_A ARX companion to contain six 11-orbiter loops.");
    XCTAssertTrue(CountText(aArxCpp, "// kdf_a_loop_b loop ") == 4U,
                  "Expected exported KDF_A_B ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// kdf_a_loop_c loop ") == 4U,
                  "Expected exported KDF_A_C ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// kdf_a_loop_d loop ") == 4U,
                  "Expected exported KDF_A_D ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// kdf_b_loop_a loop ") == 4U,
                  "Expected exported KDF_B_A ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// kdf_b_loop_b loop ") == 4U,
                  "Expected exported KDF_B_B ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// kdf_b_loop_c loop ") == 6U,
                  "Expected exported KDF_B_C ARX companion to contain six loops.");
    XCTAssertTrue(CountText(aArxCpp, "// kdf_b_loop_d loop ") == 4U,
                  "Expected exported KDF_B_D ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// seed_loop_a loop ") == 4U,
                  "Expected exported Seed_A ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// seed_loop_b loop ") == 4U,
                  "Expected exported Seed_B ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// seed_loop_c loop ") == 4U,
                  "Expected exported Seed_C ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// seed_loop_d loop ") == 4U,
                  "Expected exported Seed_D ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// twist_loop_a loop ") == 4U,
                  "Expected exported Twist_A ARX companion to contain four loops.");
    XCTAssertTrue(CountText(aArxCpp, "// twist_loop_b loop ") == 4U,
                  "Expected exported Twist_B ARX companion to contain four loops.");
    XCTAssertTrue(aArxCpp.find("// read from: mSource, mSnow") != std::string::npos &&
                  aArxCpp.find("// write to: aWorkLaneA") != std::string::npos,
                  "Expected KDF_A_A first loop to read source/snow and write work A.");
    XCTAssertTrue(aArxCpp.find("// read from: mSource, mSnow, aWorkLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aWorkLaneB") != std::string::npos,
                  "Expected KDF_A_A second loop to include work A and write work B.");
    XCTAssertTrue(aArxCpp.find("// read from: mSource, mSnow, aWorkLaneA, aWorkLaneB") != std::string::npos &&
                  aArxCpp.find("// write to: aExpandLaneA") != std::string::npos,
                  "Expected KDF_A_A third loop to write expansion A.");
    XCTAssertTrue(aArxCpp.find("// read from: mSnow, aWorkLaneA, aWorkLaneB, aExpandLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aExpandLaneB") != std::string::npos,
                  "Expected KDF_A_A fourth loop to write expansion B.");
    XCTAssertTrue(aArxCpp.find("// read from: aWorkLaneA, aWorkLaneB, aExpandLaneA, aExpandLaneB") != std::string::npos &&
                  aArxCpp.find("// write to: aExpandLaneC") != std::string::npos,
                  "Expected KDF_A_A fifth loop to write expansion C.");
    XCTAssertTrue(aArxCpp.find("// read from: aWorkLaneB, aExpandLaneA, aExpandLaneB, aExpandLaneC") != std::string::npos &&
                  aArxCpp.find("// write to: aExpandLaneD") != std::string::npos,
                  "Expected KDF_A_A sixth loop to write expansion D.");
    XCTAssertTrue(aArxCpp.find("// read from: aExpandLaneD, aExpandLaneC, aExpandLaneB, aExpandLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aOperationLaneA") != std::string::npos,
                  "Expected KDF_A_B first loop to read expansion lanes and write operation A.");
    XCTAssertTrue(aArxCpp.find("// read from: aOperationLaneD, aOperationLaneC, aOperationLaneB, aOperationLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aWorkLaneA") != std::string::npos,
                  "Expected KDF_A_C first loop to read operation lanes and write work A.");
    XCTAssertTrue(aArxCpp.find("// read from: aExpandLaneD, aExpandLaneC, aExpandLaneB, aExpandLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aWorkLaneA") != std::string::npos,
                  "Expected KDF_A_D first loop to read expansion lanes and write work A.");
    XCTAssertTrue(aArxCpp.find("// read from: aWorkLaneD, aWorkLaneC, aWorkLaneB, aWorkLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aExpandLaneA") != std::string::npos,
                  "Expected KDF_B_A first loop to read work lanes and write expansion A.");
    XCTAssertTrue(aArxCpp.find("// read from: aExpandLaneD, aExpandLaneC, aExpandLaneB, aExpandLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aOperationLaneA") != std::string::npos,
                  "Expected KDF_B_B first loop to read expansion lanes and write operation A.");
    XCTAssertTrue(aArxCpp.find("// read from: aOperationLaneD, aOperationLaneC, aOperationLaneB, aOperationLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aWorkLaneA") != std::string::npos,
                  "Expected KDF_B_C first loop to read operation lanes and write work A.");
    XCTAssertTrue(aArxCpp.find("// read from: aWorkLaneA, aOperationLaneD, aOperationLaneC, aOperationLaneB") != std::string::npos &&
                  aArxCpp.find("// write to: aWorkLaneB") != std::string::npos,
                  "Expected KDF_B_C second loop to use work A and write work B.");
    XCTAssertTrue(aArxCpp.find("// read from: aWorkLaneB, aWorkLaneA, aOperationLaneD, aOperationLaneC") != std::string::npos &&
                  aArxCpp.find("// write to: aExpandLaneA") != std::string::npos,
                  "Expected KDF_B_C third loop to use work lanes and write expansion A.");
    XCTAssertTrue(aArxCpp.find("// KDF_B_D kdf_b_loop_d (start)") != std::string::npos &&
                  aArxCpp.find("// read from: aWorkLaneD, aWorkLaneC, aWorkLaneB, aWorkLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aExpandLaneA") != std::string::npos,
                  "Expected KDF_B_D first loop to read work lanes and write expansion A.");
    XCTAssertTrue(aArxCpp.find("// GTwistRunTwist_A twist_loop_a (start)") != std::string::npos,
                  "Expected Twist_A body marker in the ARX companion.");
    XCTAssertTrue(aArxCpp.find("// read from: mSource, aKeyBoxUnrolledA, aKeyBoxUnrolledB") != std::string::npos &&
                  aArxCpp.find("// write to: aExpandLaneA") != std::string::npos,
                  "Expected Twist_A first loop to read source/key boxes and write expansion A.");
    XCTAssertTrue(aArxCpp.find("// GTwistRunTwist_B twist_loop_b (start)") != std::string::npos,
                  "Expected Twist_B body marker in the ARX companion.");
    XCTAssertTrue(aArxCpp.find("// read from: aExpandLaneD, aExpandLaneC, aExpandLaneB, aExpandLaneA") != std::string::npos &&
                  aArxCpp.find("// write to: aOperationLaneA") != std::string::npos,
                  "Expected Twist_B first loop to read expansion lanes and write operation A.");
    XCTAssertTrue(aCpp.find("std::size_t pBlockIndex") != std::string::npos,
                  "Expected exported TwistBlock definition to include block index.");
    XCTAssertTrue(aCpp.find("std::size_t pBlockCount") != std::string::npos,
                  "Expected exported TwistBlock definition to include block count.");
    XCTAssertTrue(aHpp.find("#include \"TwistExpander_TwisterStageNames_Arx.hpp\"") != std::string::npos,
                  "Expected exported twister header to include its ARX companion.");
    XCTAssertTrue(aCpp.find("#include \"TwistExpander_TwisterStageNames_Arx.hpp\"") == std::string::npos,
                  "Expected exported twister cpp to get the ARX type through its header.");
    const std::size_t aTwistA = aCpp.find("GTwistRunTwist_A twist_loop_a:");
    const std::size_t aTwistB = aCpp.find("GTwistRunTwist_B twist_loop_b:");
    const std::size_t aTwistC = aCpp.find("GTwistRunTwist_C twist_loop_c (start)");
    XCTAssertTrue(aTwistA != std::string::npos, "Expected named twist loop A marker.");
    XCTAssertTrue(aTwistB != std::string::npos, "Expected named twist loop B marker.");
    XCTAssertTrue(aTwistC != std::string::npos, "Expected named twist loop C marker.");
    XCTAssertTrue(aTwistA < aTwistB && aTwistB < aTwistC,
                  "Expected twist loops in A, B, C order.");
    XCTAssertTrue(aCpp.find("GTwistRunTwist15") == std::string::npos,
                  "Export should not mention numbered twist stages.");
    XCTAssertTrue(aCpp.find("TwistExpander_TwisterStageNames_Arx::Twist_A(") != std::string::npos,
                  "Expected TwistBlock to call the ARX helper for twist loop A.");
    XCTAssertTrue(aCpp.find("TwistExpander_TwisterStageNames_Arx::Twist_B(") != std::string::npos,
                  "Expected TwistBlock to call the ARX helper for twist loop B.");
    XCTAssertTrue(aCpp.find("GTwistRunTwist_A twist_loop_a (start)") == std::string::npos,
                  "Expected full twist loop A body to live in the ARX companion.");
    XCTAssertTrue(aCpp.find("GTwistRunTwist_B twist_loop_b (start)") == std::string::npos,
                  "Expected full twist loop B body to live in the ARX companion.");
    XCTAssertTrue(aArxCpp.find("GTwistRunTwist_A twist_loop_a lane group") != std::string::npos,
                  "Expected twist loop A lane group comment in the ARX companion.");
    XCTAssertTrue(aArxCpp.find("GTwistRunTwist_B twist_loop_b lane group") != std::string::npos,
                  "Expected twist loop B lane group comment in the ARX companion.");
    XCTAssertTrue(aCpp.find("// write to: aKeyRowWriteA (^=)") != std::string::npos,
                  "Expected grow-key xor write lane comment.");
    XCTAssertTrue(CountText(aCpp, "TwistSquash::Squash") == 1U,
                  "Twister export should emit exactly one final output squash.");

    const std::size_t aTwistBlock = aCpp.find("void TwistExpander_TwisterStageNames::TwistBlock(");
    const std::size_t aGrowACall = aCpp.find("    GrowKeyA(pWorkSpace);", aTwistBlock);
    const std::size_t aGrowBCall = aCpp.find("    GrowKeyB(pWorkSpace);", aTwistBlock);
    const std::size_t aGrowAMethod = aCpp.find("void TwistExpander_TwisterStageNames::GrowKeyA(");
    const std::size_t aGrowBMethod = aCpp.find("void TwistExpander_TwisterStageNames::GrowKeyB(");
    const std::size_t aGrowExpandA = aCpp.find("GTwistRunGrowKeyA grow_key_a_expand_a (start)");
    const std::size_t aGrowExpandB = aCpp.find("GTwistRunGrowKeyA grow_key_a_expand_b (start)");
    const std::size_t aGrowLoopA = aCpp.find("GTwistRunGrowKeyA twist_key_box_loop_a (start)");
    const std::size_t aGrowBExpandA = aCpp.find("GTwistRunGrowKeyB grow_key_b_expand_a (start)");
    const std::size_t aGrowBExpandB = aCpp.find("GTwistRunGrowKeyB grow_key_b_expand_b (start)");
    const std::size_t aGrowLoopB = aCpp.find("GTwistRunGrowKeyB twist_key_box_loop_b (start)");
    const std::size_t aGrowBNextMethod = (aGrowBMethod == std::string::npos) ?
        std::string::npos :
        aCpp.find("\nvoid TwistExpander_TwisterStageNames::", aGrowBMethod + 1U);
    const std::size_t aGrowBStaticDefinitions = (aGrowBMethod == std::string::npos) ?
        std::string::npos :
        aCpp.find("\nconst TwistDomain", aGrowBMethod + 1U);
    const std::size_t aGrowBMethodEnd = (aGrowBNextMethod != std::string::npos) ?
        aGrowBNextMethod :
        aGrowBStaticDefinitions;
    const std::string aGrowAText = ((aGrowAMethod != std::string::npos) &&
                                    (aGrowBMethod != std::string::npos) &&
                                    (aGrowAMethod < aGrowBMethod)) ?
        aCpp.substr(aGrowAMethod, aGrowBMethod - aGrowAMethod) :
        "";
    const std::string aGrowBText = (aGrowBMethod == std::string::npos) ?
        "" :
        (aGrowBMethodEnd == std::string::npos) ?
        aCpp.substr(aGrowBMethod) :
        aCpp.substr(aGrowBMethod, aGrowBMethodEnd - aGrowBMethod);
    XCTAssertTrue(aTwistBlock != std::string::npos, "Expected generated TwistBlock method.");
    XCTAssertTrue(aGrowACall != std::string::npos, "Expected TwistBlock to call GrowKeyA.");
    XCTAssertTrue(aGrowBCall != std::string::npos, "Expected TwistBlock to call GrowKeyB.");
    XCTAssertTrue(aGrowAMethod != std::string::npos, "Expected generated GrowKeyA method.");
    XCTAssertTrue(aGrowBMethod != std::string::npos, "Expected generated GrowKeyB method.");
    XCTAssertTrue(aGrowACall < aGrowAMethod && aGrowBCall < aGrowAMethod,
                  "Grow-key calls should be emitted at the end of TwistBlock.");
    XCTAssertTrue(aGrowExpandA > aGrowAMethod && aGrowExpandA < aGrowBMethod,
                  "grow_key_a_expand_a should live inside GrowKeyA.");
    XCTAssertTrue(aGrowExpandB > aGrowExpandA && aGrowExpandB < aGrowBMethod,
                  "grow_key_a_expand_b should follow grow_key_a_expand_a inside GrowKeyA.");
    XCTAssertTrue(aGrowLoopA > aGrowExpandB && aGrowLoopA < aGrowBMethod,
                  "twist_key_box_loop_a should be the final GrowKeyA loop.");
    XCTAssertTrue(aGrowBExpandA > aGrowBMethod,
                  "grow_key_b_expand_a should live inside GrowKeyB.");
    XCTAssertTrue(aGrowBExpandB > aGrowBExpandA,
                  "grow_key_b_expand_b should follow grow_key_b_expand_a inside GrowKeyB.");
    XCTAssertTrue(aGrowLoopB > aGrowBExpandB,
                  "twist_key_box_loop_b should be the final GrowKeyB loop.");
    XCTAssertTrue(aGrowAText.find("PhaseD") != std::string::npos,
                  "GrowKeyA should use phase D salt aliases.");
    XCTAssertTrue(aGrowBText.find("PhaseD") != std::string::npos,
                  "GrowKeyB should use phase D salt aliases.");
    XCTAssertTrue(aGrowAText.find("PhaseC") == std::string::npos,
                  "GrowKeyA should not use phase C salt aliases.");
    XCTAssertTrue(aGrowBText.find("PhaseC") == std::string::npos,
                  "GrowKeyB should not use phase C salt aliases.");
    XCTAssertTrue(aGrowAText.find("aWorkLaneA") != std::string::npos &&
                  aGrowAText.find("aWorkLaneB") != std::string::npos &&
                  aGrowAText.find("aWorkLaneC") != std::string::npos &&
                  aGrowAText.find("aWorkLaneD") != std::string::npos,
                  "GrowKeyA should consume all four work lanes.");
    XCTAssertTrue(aGrowBText.find("aWorkLaneA") != std::string::npos &&
                  aGrowBText.find("aWorkLaneB") != std::string::npos &&
                  aGrowBText.find("aWorkLaneC") != std::string::npos &&
                  aGrowBText.find("aWorkLaneD") != std::string::npos,
                  "GrowKeyB should consume all four work lanes.");
    XCTAssertTrue(aGrowAText.find("aKeyRowWriteA") != std::string::npos,
                  "GrowKeyA should write key row A.");
    XCTAssertTrue(aGrowBText.find("aKeyRowWriteB") != std::string::npos,
                  "GrowKeyB should write key row B.");
    XCTAssertTrue(aGrowBText.find("for (std::size_t aIndex = static_cast<std::size_t>((S_BLOCK >> 1));") != std::string::npos,
                  "GrowKeyB loops should start at S_BLOCK >> 1.");
    XCTAssertTrue(aGrowBText.find("aIndex < static_cast<std::size_t>(S_BLOCK)") != std::string::npos,
                  "GrowKeyB loops should run to S_BLOCK.");
    XCTAssertTrue(aCpp.find("if ((pBlockCount - pBlockIndex) > static_cast<std::size_t>(H_KEY_A)) {") != std::string::npos,
                  "TwistBlock should grow key box A only before the final H_KEY_A blocks.");
    XCTAssertTrue(aCpp.find("TwistShiftBox::ShiftKeyBoxA(pWorkSpace);") != std::string::npos,
                  "TwistBlock should shift key box A when it does not need new key material.");
    XCTAssertTrue(aCpp.find("if ((pBlockCount - pBlockIndex) > static_cast<std::size_t>(H_KEY_B)) {") != std::string::npos,
                  "TwistBlock should grow key box B only before the final H_KEY_B blocks.");
    XCTAssertTrue(aCpp.find("TwistShiftBox::ShiftKeyBoxB(pWorkSpace);") != std::string::npos,
                  "TwistBlock should shift key box B when it does not need new key material.");
    XCTAssertTrue(aCpp.find("pBlockIndex < pBlockCount") == std::string::npos,
                  "TwistBlock should trust the block index/count invariant and emit only the remaining-block check.");
}

- (void)testSeederPostKDFSeedLoopsUseNonceOnlyInFirstPhase {
    GTwistExpander aExpander;
    aExpander.mNameBase = "SeederSeedPhases";

    Builder_Seeder aSeeder;
    std::string aError;
    XCTAssertTrue(aSeeder.Build(&aExpander, &aError),
                  "Seeder build failed: %s", aError.c_str());

    const std::string aExportRoot = "/private/tmp/mm_seeder_seed_phases";
    XCTAssertTrue(aExpander.ExportCPPProjectRoot(aExportRoot, &aError),
                  "Export failed: %s", aError.c_str());

    std::vector<std::uint8_t> aCppBytes;
    const std::string aCppPath = FileIO::Join(aExportRoot, "TwistExpander_SeederSeedPhases.cpp");
    XCTAssertTrue(FileIO::Load(aCppPath, aCppBytes), "Failed to load emitted cpp file.");
    std::vector<std::uint8_t> aArxCppBytes;
    const std::string aArxCppPath = FileIO::Join(aExportRoot, "TwistExpander_SeederSeedPhases_Arx.cpp");
    XCTAssertTrue(FileIO::Load(aArxCppPath, aArxCppBytes), "Failed to load emitted ARX cpp file.");

    const std::string aCpp(aCppBytes.begin(), aCppBytes.end());
    const std::string aArxCpp(aArxCppBytes.begin(), aArxCppBytes.end());
    const std::size_t aSeedLoopA = aCpp.find("GSeedRunSeed_A seed_loop_a:");
    const std::size_t aSeedLoopB = aCpp.find("GSeedRunSeed_B seed_loop_b:");
    const std::size_t aSeedLoopC = aCpp.find("GSeedRunSeed_C seed_loop_c:");
    const std::size_t aSeedLoopD = aCpp.find("GSeedRunSeed_D seed_loop_d:");
    XCTAssertTrue(aSeedLoopA != std::string::npos, "Expected seed loop A.");
    XCTAssertTrue(aSeedLoopB != std::string::npos, "Expected seed loop B.");
    XCTAssertTrue(aSeedLoopC != std::string::npos, "Expected seed loop C.");
    XCTAssertTrue(aSeedLoopD != std::string::npos, "Expected seed loop D.");
    XCTAssertTrue(aSeedLoopA < aSeedLoopB && aSeedLoopB < aSeedLoopC && aSeedLoopC < aSeedLoopD,
                  "Expected seed loops in phase order A, B, C, D.");
    
    const std::size_t aSeedCallA = aCpp.find("TwistExpander_SeederSeedPhases_Arx::Seed_A(");
    const std::size_t aSeedCallB = aCpp.find("TwistExpander_SeederSeedPhases_Arx::Seed_B(");
    const std::size_t aSeedCallC = aCpp.find("TwistExpander_SeederSeedPhases_Arx::Seed_C(");
    const std::size_t aSeedCallD = aCpp.find("TwistExpander_SeederSeedPhases_Arx::Seed_D(");
    XCTAssertTrue(aSeedCallA != std::string::npos && aSeedCallB != std::string::npos &&
                  aSeedCallC != std::string::npos && aSeedCallD != std::string::npos,
                  "Expected seed loops to call the ARX helper.");
    XCTAssertTrue(aSeedCallA < aSeedCallB && aSeedCallB < aSeedCallC && aSeedCallC < aSeedCallD,
                  "Expected seed ARX calls in A, B, C, D order.");
    XCTAssertTrue(aCpp.find("GSeedRunSeed_A seed_loop_a (start)") == std::string::npos &&
                  aCpp.find("GSeedRunSeed_B seed_loop_b (start)") == std::string::npos &&
                  aCpp.find("GSeedRunSeed_C seed_loop_c (start)") == std::string::npos &&
                  aCpp.find("GSeedRunSeed_D seed_loop_d (start)") == std::string::npos,
                  "Expected full seed loop bodies to live in the ARX companion.");
    
    const std::size_t aArxSeedLoopA = aArxCpp.find("GSeedRunSeed_A seed_loop_a (start)");
    const std::size_t aArxSeedLoopB = aArxCpp.find("GSeedRunSeed_B seed_loop_b (start)");
    const std::size_t aArxSeedLoopC = aArxCpp.find("GSeedRunSeed_C seed_loop_c (start)");
    const std::size_t aArxSeedLoopD = aArxCpp.find("GSeedRunSeed_D seed_loop_d (start)");
    XCTAssertTrue(aArxSeedLoopA != std::string::npos, "Expected generated seed loop A marker to include the stage name.");
    XCTAssertTrue(aArxSeedLoopB != std::string::npos, "Expected generated seed loop B marker to include the stage name.");
    XCTAssertTrue(aArxSeedLoopC != std::string::npos, "Expected generated seed loop C marker to include the stage name.");
    XCTAssertTrue(aArxSeedLoopD != std::string::npos, "Expected generated seed loop D marker to include the stage name.");
    XCTAssertTrue(aArxSeedLoopA < aArxSeedLoopB && aArxSeedLoopB < aArxSeedLoopC && aArxSeedLoopC < aArxSeedLoopD,
                  "Expected ARX seed loop bodies in phase order A, B, C, D.");

    const std::size_t aSeedMethodA = aArxCpp.find("void TwistExpander_SeederSeedPhases_Arx::Seed_A(");
    const std::size_t aSeedMethodB = aArxCpp.find("void TwistExpander_SeederSeedPhases_Arx::Seed_B(");
    const std::size_t aSeedMethodC = aArxCpp.find("void TwistExpander_SeederSeedPhases_Arx::Seed_C(");
    const std::size_t aSeedMethodD = aArxCpp.find("void TwistExpander_SeederSeedPhases_Arx::Seed_D(");
    XCTAssertTrue(aSeedMethodA != std::string::npos && aSeedMethodB != std::string::npos &&
                  aSeedMethodC != std::string::npos && aSeedMethodD != std::string::npos,
                  "Expected all seed ARX helper methods.");
    if (aSeedMethodA == std::string::npos || aSeedMethodB == std::string::npos ||
        aSeedMethodC == std::string::npos || aSeedMethodD == std::string::npos) {
        return;
    }
    XCTAssertTrue(aSeedMethodA < aSeedMethodB && aSeedMethodB < aSeedMethodC && aSeedMethodC < aSeedMethodD,
                  "Expected seed ARX helper methods in A, B, C, D order.");

    const std::size_t aNonceDecl = aArxCpp.find("[[maybe_unused]] std::uint64_t aNonceByteA = ((pNonce >> 0U) & 0xFFULL);",
                                                aSeedMethodA);
    XCTAssertTrue(aNonceDecl != std::string::npos, "Expected Seed_A nonce byte declarations.");
    XCTAssertTrue(aNonceDecl < aArxSeedLoopA, "Expected seed nonces to be declared before the first seed loop.");

    const std::string aLoopAText = aArxCpp.substr(aSeedMethodA, aSeedMethodB - aSeedMethodA);
    const std::string aLoopBText = aArxCpp.substr(aSeedMethodB, aSeedMethodC - aSeedMethodB);
    const std::string aLoopCText = aArxCpp.substr(aSeedMethodC, aSeedMethodD - aSeedMethodC);
    const std::string aLoopDText = aArxCpp.substr(aSeedMethodD);
    XCTAssertTrue(aLoopAText.find("aNonceByte") != std::string::npos,
                  "The first seed loop set should use nonce bytes.");
    XCTAssertTrue(aLoopBText.find("aNonceByte") == std::string::npos,
                  "Seed loop B should ignore nonce bytes.");
    XCTAssertTrue(aLoopCText.find("aNonceByte") == std::string::npos,
                  "Seed loop C should ignore nonce bytes.");
    XCTAssertTrue(aLoopDText.find("aNonceByte") == std::string::npos,
                  "Seed loop D should ignore nonce bytes.");

    const std::size_t aKDFPhaseA = aCpp.find("KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants)");
    const std::size_t aKDFPhaseB = aCpp.find("KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants)");
    const std::size_t aKDFPhaseC = aCpp.find("KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants)");
    const std::size_t aKDFPhaseD = aCpp.find("KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants)");
    const std::size_t aKDFPhaseE = aCpp.find("KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants)");
    const std::size_t aKDFPhaseF = aCpp.find("KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants)");
    const std::size_t aKDFPhaseG = aCpp.find("KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants)");
    const std::size_t aKDFPhaseH = aCpp.find("KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants)");
    XCTAssertTrue(aKDFPhaseA != std::string::npos && aKDFPhaseB != std::string::npos &&
                  aKDFPhaseC != std::string::npos && aKDFPhaseD != std::string::npos &&
                  aKDFPhaseE != std::string::npos && aKDFPhaseF != std::string::npos &&
                  aKDFPhaseG != std::string::npos && aKDFPhaseH != std::string::npos,
                  "Expected seed KDF to run phases A-H.");
    XCTAssertTrue(aKDFPhaseA < aKDFPhaseB && aKDFPhaseB < aKDFPhaseC &&
                  aKDFPhaseC < aKDFPhaseD && aKDFPhaseD < aKDFPhaseE &&
                  aKDFPhaseE < aKDFPhaseF && aKDFPhaseF < aKDFPhaseG &&
                  aKDFPhaseG < aKDFPhaseH,
                  "Expected seed KDF phases in A, B, C, D, E, F, G, H order.");

    const std::size_t aPhaseA = aArxCpp.find("pWorkSpace->mDomainBundle.mPhaseAConstants.mIngress;");
    const std::size_t aPhaseB = aArxCpp.find("pWorkSpace->mDomainBundle.mPhaseBConstants.mIngress;");
    const std::size_t aPhaseC = aArxCpp.find("pWorkSpace->mDomainBundle.mPhaseCConstants.mIngress;");
    const std::size_t aPhaseD = aArxCpp.find("pWorkSpace->mDomainBundle.mPhaseDConstants.mIngress;");
    const std::size_t aMatrixC = aCpp.find("pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;");
    XCTAssertTrue(aPhaseA != std::string::npos && aPhaseB != std::string::npos &&
                  aPhaseC != std::string::npos && aPhaseD != std::string::npos,
                  "Expected seed phase domain constants.");
    XCTAssertTrue(aPhaseA < aPhaseB && aPhaseB < aPhaseC && aPhaseC < aPhaseD,
                  "Expected seed phase domain constants in A, B, C, D order.");
    XCTAssertTrue(aMatrixC != std::string::npos,
                  "Expected seed matrix constants to use phase C.");
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

- (void)testRuntimeMatrixRawLineDispatchMatchesM88 {
    TwistWorkSpace aWorkSpace;
    std::memset(aWorkSpace.mWorkLaneA, 0, S_BLOCK);
    std::memset(aWorkSpace.mWorkLaneB, 0, S_BLOCK);
    std::memset(aWorkSpace.mOperationLaneA, 0, S_BLOCK);
    for (int i = 0; i < 64; ++i) {
        aWorkSpace.mWorkLaneA[i] = static_cast<std::uint8_t>(i);
        aWorkSpace.mOperationLaneA[i] = static_cast<std::uint8_t>((i * 37 + 11) & 0xFF);
    }

    GTwistExpander aExpander;
    GBatch aBatch;
    std::vector<GStatement> aStatements;
    aStatements.push_back(GStatement::RawLine("mMatrix.Dispatch(aOperationLaneA, aMatrixOperationIndex, aWorkLaneA, aMatrixLoadIndexA, aWorkLaneB, aMatrixStoreIndexA, aDomainWordMatrixUnrollA, aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD);"));
    aBatch.CommitStatements(&aStatements);

    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    aVariables["aMatrixOperationIndex"] = 0ULL;
    aVariables["aMatrixLoadIndexA"] = 0ULL;
    aVariables["aMatrixStoreIndexA"] = 0ULL;
    aVariables["aDomainWordMatrixUnrollA"] = 0x21ULL;
    aVariables["aDomainWordMatrixArgA"] = 0x31ULL;
    aVariables["aDomainWordMatrixArgB"] = 0x41ULL;
    aVariables["aDomainWordMatrixArgC"] = 0x51ULL;
    aVariables["aDomainWordMatrixArgD"] = 0x61ULL;

    std::string aError;
    XCTAssertTrue(aBatch.ExecuteWithVariables(&aWorkSpace, &aExpander, &aVariables, &aError),
                  "%s", aError.c_str());

    M88 aExpectedMatrix;
    std::uint8_t aExpected[64];
    std::memset(aExpected, 0, sizeof(aExpected));
    aExpectedMatrix.Dispatch(aWorkSpace.mOperationLaneA,
                             0U,
                             aWorkSpace.mWorkLaneA,
                             0U,
                             aExpected,
                             0U,
                             0x21U,
                             0x31U,
                             0x41U,
                             0x51U,
                             0x61U);

    XCTAssertTrue(std::memcmp(aExpected, aWorkSpace.mWorkLaneB, sizeof(aExpected)) == 0,
                  "Runtime M88 raw-line execution should match direct C++ execution.");
}

- (void)testRuntimeRawIfByteMaskGreaterBranches {
    auto RunCase = [&](const std::uint8_t pOperationByte,
                       const GRuntimeScalar pSelectWord,
                       const GRuntimeScalar pExpectedFlag) {
        TwistWorkSpace aWorkSpace;
        std::memset(aWorkSpace.mOperationLaneA, 0, S_BLOCK);
        aWorkSpace.mOperationLaneA[0] = pOperationByte;

        GTwistExpander aExpander;
        GBatch aBatch;
        std::vector<GStatement> aStatements;
        aStatements.push_back(GStatement::Assign(
            GTarget::Symbol(GSymbol::Var("aWriteIndex")),
            GExpr::Const64(0ULL)));
        aStatements.push_back(GStatement::Assign(
            GTarget::Symbol(GSymbol::Var("aRuntimeBranchFlag")),
            GExpr::Const64(0ULL)));
        aStatements.push_back(GStatement::RawLine("if (((aOperationLaneA[aWriteIndex] ^ aDomainWordMatrixSelectA) & 0x7E) > 62) {"));
        aStatements.push_back(GStatement::Assign(
            GTarget::Symbol(GSymbol::Var("aRuntimeBranchFlag")),
            GExpr::Const64(1ULL)));
        aStatements.push_back(GStatement::RawLine("} else {"));
        aStatements.push_back(GStatement::Assign(
            GTarget::Symbol(GSymbol::Var("aRuntimeBranchFlag")),
            GExpr::Const64(2ULL)));
        aStatements.push_back(GStatement::RawLine("}"));
        aBatch.CommitStatements(&aStatements);

        std::unordered_map<std::string, GRuntimeScalar> aVariables;
        aVariables["aDomainWordMatrixSelectA"] = pSelectWord;
        std::string aError;
        XCTAssertTrue(aBatch.ExecuteWithVariables(&aWorkSpace, &aExpander, &aVariables, &aError),
                      "%s", aError.c_str());
        XCTAssertTrue(aVariables["aRuntimeBranchFlag"] == pExpectedFlag,
                      "Runtime raw if should select the expected branch.");
        };

    RunCase(0U, 64ULL, 1ULL);
    RunCase(64U, 64ULL, 2ULL);
}

- (void)testRunMatrixDiffusionExportsTwistDiffuse {
    GRunMatrixDiffusionConfig aConfig;
    aConfig.mInputA = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
    aConfig.mInputB = BufSymbol(TwistWorkSpaceSlot::kWorkLaneB);
    aConfig.mOutputA = BufSymbol(TwistWorkSpaceSlot::kExpansionLaneA);
    aConfig.mOutputB = BufSymbol(TwistWorkSpaceSlot::kExpansionLaneB);
    aConfig.mShuffleEntropyA = BufSymbol(TwistWorkSpaceSlot::kOperationLaneA);
    aConfig.mShuffleEntropyB = BufSymbol(TwistWorkSpaceSlot::kOperationLaneB);
    aConfig.mOperationSourceA = BufSymbol(TwistWorkSpaceSlot::kOperationLaneC);
    aConfig.mOperationSourceB = BufSymbol(TwistWorkSpaceSlot::kOperationLaneD);

    GBatch aBatch;
    std::string aError;
    XCTAssertTrue(GRunMatrixDiffusion::Bake(aConfig, &aBatch, &aError),
                  "%s", aError.c_str());

    const std::string aJson = aBatch.ToJson(&aError);
    XCTAssertFalse(aJson.empty(), "%s", aError.c_str());

    GBatch aRoundTrip;
    XCTAssertTrue(GBatch::FromJson(aJson, &aRoundTrip, &aError),
                  "%s", aError.c_str());

    const std::string aBlock = aRoundTrip.BuildCppScopeBlock(&aError, false);
    XCTAssertFalse(aBlock.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("TwistDiffuse::DiffuseWithDomainWords(") != std::string::npos,
                  "Matrix diffusion export should emit the shared TwistDiffuse helper.");
    XCTAssertTrue(aBlock.find("&mMatrix") != std::string::npos,
                  "Matrix diffusion export should pass the expander matrix.");
    XCTAssertTrue(aBlock.find("mMatrix.Dispatch(") == std::string::npos,
                  "Matrix diffusion export should not re-expand M88 dispatch calls.");
    XCTAssertTrue(aBlock.find("TwistIndexShuffle::") == std::string::npos,
                  "Matrix diffusion export should keep index shuffle inside TwistDiffuse.");
    XCTAssertTrue(aBlock.find("aOperationLaneC") != std::string::npos,
                  "Matrix diffusion export should reference operation lane C.");
    XCTAssertTrue(aBlock.find("aOperationLaneD") != std::string::npos,
                  "Matrix diffusion export should reference operation lane D.");
    XCTAssertTrue(aBlock.find("aDomainWordMatrixUnrollA") != std::string::npos,
                  "Matrix diffusion export should pass matrix unroll domain word A.");
    XCTAssertTrue(aBlock.find("aDomainWordMatrixUnrollB") != std::string::npos,
                  "Matrix diffusion export should pass matrix unroll domain word B.");
    XCTAssertTrue(aBlock.find("aDomainWordMatrixSelectA") != std::string::npos,
                  "Matrix diffusion export should pass matrix select domain word A.");
    XCTAssertTrue(aBlock.find("aDomainWordMatrixSelectB") != std::string::npos,
                  "Matrix diffusion export should pass matrix select domain word B.");
    XCTAssertTrue(aBlock.find("aDomainWordMatrixArgA") != std::string::npos,
                  "Matrix diffusion export should pass matrix arg domain word A.");
    XCTAssertTrue(aBlock.find("aDomainWordMatrixArgB") != std::string::npos,
                  "Matrix diffusion export should pass matrix arg domain word B.");
    XCTAssertTrue(aBlock.find("aDomainWordMatrixArgC") != std::string::npos,
                  "Matrix diffusion export should pass matrix arg domain word C.");
    XCTAssertTrue(aBlock.find("aDomainWordMatrixArgD") != std::string::npos,
                  "Matrix diffusion export should pass matrix arg domain word D.");
    XCTAssertTrue(aBlock.find("static_cast<std::uint8_t>(aDomainWordMatrixUnrollA)") == std::string::npos,
                  "Matrix diffusion export should not cast uint8_t domain words back to uint8_t.");
    XCTAssertTrue(aBlock.find("static_cast<std::uint8_t>(aDomainWordMatrixArgA)") == std::string::npos,
                  "Matrix diffusion export should not cast uint8_t domain words back to uint8_t.");
    XCTAssertTrue(aBlock.find("aExpandLaneA") != std::string::npos,
                  "Matrix diffusion export should reference output expansion lane A.");
    XCTAssertTrue(aBlock.find("aExpandLaneB") != std::string::npos,
                  "Matrix diffusion export should reference output expansion lane B.");
    XCTAssertTrue(aBlock.find("// twist_seed_batch index shuffle") != std::string::npos,
                  "Matrix diffusion export should describe index shuffle lane flow.");
    XCTAssertTrue(aBlock.find("// read from: aOperationLaneA, aOperationLaneB") != std::string::npos,
                  "Matrix diffusion export should describe shuffle read lanes.");
    XCTAssertTrue(aBlock.find("// write to: aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D") != std::string::npos,
                  "Matrix diffusion export should describe index-list writes.");
    XCTAssertTrue(aBlock.find("// twist_seed_batch aExpandLaneA matrix loop") != std::string::npos,
                  "Matrix diffusion export should describe matrix loop A.");
    XCTAssertTrue(aBlock.find("// read from: aWorkLaneA, aWorkLaneB, aOperationLaneC, aIndexList256A, aIndexList256B") != std::string::npos,
                  "Matrix diffusion export should describe matrix loop A reads.");
    XCTAssertTrue(aBlock.find("// write to: aExpandLaneA") != std::string::npos,
                  "Matrix diffusion export should describe matrix loop A write.");
    XCTAssertTrue(aBlock.find("aMatrixDiffusionIndex") == std::string::npos,
                  "Matrix diffusion export should not emit direct diffusion loops.");
    XCTAssertTrue(aBlock.find("aReadIndexA") == std::string::npos,
                  "Matrix diffusion export should keep read-index temporaries inside TwistDiffuse.");
    XCTAssertTrue(aBlock.find("aReadIndexB") == std::string::npos,
                  "Matrix diffusion export should keep read-index temporaries inside TwistDiffuse.");
    XCTAssertTrue(aBlock.find("aMatrixSlotA") == std::string::npos,
                  "Matrix diffusion export should not emit old matrix slot temporaries.");
    XCTAssertTrue(aBlock.find("aM88") == std::string::npos,
                  "Matrix diffusion export should not emit old M88 temporaries.");

    aConfig.mUseDomainWords = false;
    GBatch aNoDomainBatch;
    XCTAssertTrue(GRunMatrixDiffusion::Bake(aConfig, &aNoDomainBatch, &aError),
                  "%s", aError.c_str());
    const std::string aNoDomainBlock = aNoDomainBatch.BuildCppScopeBlock(&aError, false);
    XCTAssertFalse(aNoDomainBlock.empty(), "%s", aError.c_str());
    XCTAssertTrue(aNoDomainBlock.find("TwistDiffuse::Diffuse(") != std::string::npos,
                  "Matrix diffusion export should use the no-domain helper when requested.");
    XCTAssertTrue(aNoDomainBlock.find("TwistDiffuse::DiffuseWithDomainWords(") == std::string::npos,
                  "No-domain matrix diffusion export should not use domain-word helper.");
    XCTAssertTrue(aNoDomainBlock.find("aDomainWordMatrix") == std::string::npos,
                  "No-domain matrix diffusion export should not reference matrix domain words.");
}

- (void)testRunMatrixDiffusionPreservesCombinedHistogram {
    auto MakeCombinedHistogram = [](const std::uint8_t *pLaneA,
                                    const std::uint8_t *pLaneB) {
        std::array<std::uint64_t, 256U> aHistogram{};
        for (std::size_t i = 0U; i < S_BLOCK; i += 1U) {
            aHistogram[pLaneA[i]] += 1U;
            aHistogram[pLaneB[i]] += 1U;
        }
        return aHistogram;
    };

    auto AssertHistogramsEqual = [](const std::array<std::uint64_t, 256U> &pExpected,
                                    const std::array<std::uint64_t, 256U> &pActual) {
        for (std::size_t i = 0U; i < pExpected.size(); i += 1U) {
            XCTAssertTrue(pExpected[i] == pActual[i],
                          "Histogram mismatch for value %zu: work=%llu expand=%llu",
                          i,
                          static_cast<unsigned long long>(pExpected[i]),
                          static_cast<unsigned long long>(pActual[i]));
        }
    };

    TwistWorkSpace aWorkSpace;
    for (std::size_t i = 0U; i < S_BLOCK; i += 1U) {
        aWorkSpace.mWorkLaneA[i] = static_cast<std::uint8_t>((i * 17U + 11U) & 0xFFU);
        aWorkSpace.mWorkLaneB[i] = static_cast<std::uint8_t>((i * 29U + 71U) & 0xFFU);
        aWorkSpace.mExpansionLaneA[i] = 0U;
        aWorkSpace.mExpansionLaneB[i] = 0U;
        aWorkSpace.mOperationLaneA[i] = static_cast<std::uint8_t>((i * 37U + 3U) & 0xFFU);
        aWorkSpace.mOperationLaneB[i] = static_cast<std::uint8_t>((i * 53U + 5U) & 0xFFU);
        aWorkSpace.mOperationLaneC[i] = static_cast<std::uint8_t>((i * 71U + 7U) & 0xFFU);
        aWorkSpace.mOperationLaneD[i] = static_cast<std::uint8_t>((i * 97U + 13U) & 0xFFU);
    }

    GRunMatrixDiffusionConfig aConfig;
    aConfig.mInputA = BufSymbol(TwistWorkSpaceSlot::kWorkLaneA);
    aConfig.mInputB = BufSymbol(TwistWorkSpaceSlot::kWorkLaneB);
    aConfig.mOutputA = BufSymbol(TwistWorkSpaceSlot::kExpansionLaneA);
    aConfig.mOutputB = BufSymbol(TwistWorkSpaceSlot::kExpansionLaneB);
    aConfig.mShuffleEntropyA = BufSymbol(TwistWorkSpaceSlot::kOperationLaneA);
    aConfig.mShuffleEntropyB = BufSymbol(TwistWorkSpaceSlot::kOperationLaneB);
    aConfig.mOperationSourceA = BufSymbol(TwistWorkSpaceSlot::kOperationLaneC);
    aConfig.mOperationSourceB = BufSymbol(TwistWorkSpaceSlot::kOperationLaneD);

    GBatch aBatch;
    std::string aError;
    XCTAssertTrue(GRunMatrixDiffusion::Bake(aConfig, &aBatch, &aError),
                  "%s", aError.c_str());

    GTwistExpander aExpander;
    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    aVariables["aDomainWordMatrixUnrollA"] = 0x21ULL;
    aVariables["aDomainWordMatrixUnrollB"] = 0x22ULL;
    aVariables["aDomainWordMatrixSelectA"] = 0x1122334455667788ULL;
    aVariables["aDomainWordMatrixSelectB"] = 0x8877665544332211ULL;
    aVariables["aDomainWordMatrixArgA"] = 0x31ULL;
    aVariables["aDomainWordMatrixArgB"] = 0x41ULL;
    aVariables["aDomainWordMatrixArgC"] = 0x51ULL;
    aVariables["aDomainWordMatrixArgD"] = 0x61ULL;

    const auto aWorkHistogram = MakeCombinedHistogram(aWorkSpace.mWorkLaneA,
                                                      aWorkSpace.mWorkLaneB);
    XCTAssertTrue(aBatch.ExecuteWithVariables(&aWorkSpace, &aExpander, &aVariables, &aError),
                  "%s", aError.c_str());
    const auto aExpandHistogram = MakeCombinedHistogram(aWorkSpace.mExpansionLaneA,
                                                        aWorkSpace.mExpansionLaneB);
    AssertHistogramsEqual(aWorkHistogram, aExpandHistogram);
}

- (void)testDiffuse64AExpressionEmissionUsesTwistMix64 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::Diffuse64A(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix64::DiffuseA(") != std::string::npos,
                  "Expected TwistMix64::DiffuseA call in emitted C++.");
}

- (void)testDiffuse64BExpressionEmissionUsesTwistMix64 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::Diffuse64B(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix64::DiffuseB(") != std::string::npos,
                  "Expected TwistMix64::DiffuseB call in emitted C++.");
}

- (void)testDiffuse64CExpressionEmissionUsesTwistMix64 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::Diffuse64C(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix64::DiffuseC(") != std::string::npos,
                  "Expected TwistMix64::DiffuseC call in emitted C++.");
}

- (void)testDiffuse32AExpressionEmissionUsesTwistMix32 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::Diffuse32A(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix32::DiffuseA(") != std::string::npos,
                  "Expected TwistMix32::DiffuseA call in emitted C++.");
    XCTAssertTrue(aLines[0].find("static_cast<std::uint32_t>(aValue)") != std::string::npos,
                  "Expected the 32-bit diffuse input to be narrowed explicitly.");
}

- (void)testDiffuse32BExpressionEmissionUsesTwistMix32 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::Diffuse32B(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix32::DiffuseB(") != std::string::npos,
                  "Expected TwistMix32::DiffuseB call in emitted C++.");
}

- (void)testDiffuse32CExpressionEmissionUsesTwistMix32 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::Diffuse32C(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix32::DiffuseC(") != std::string::npos,
                  "Expected TwistMix32::DiffuseC call in emitted C++.");
}

- (void)testDiffuseExpressionJsonUsesWidthFirstTokensAndReadsLegacy64Tokens {
    const GSymbol aValue = GSymbol::Var("aValue");
    GBatch aBatch;
    std::vector<GStatement> aStatements;
    aStatements.push_back(GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::Diffuse64A(GExpr::Symbol(aValue))));
    aStatements.push_back(GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::Diffuse32A(GExpr::Symbol(aValue))));
    aBatch.CommitStatements(&aStatements);

    std::string aError;
    const std::string aJson = aBatch.ToJson(&aError);
    XCTAssertFalse(aJson.empty(), "%s", aError.c_str());
    XCTAssertTrue(aJson.find("\"diffuse64_a\"") != std::string::npos,
                  "Expected serialized JSON to use the width-first 64-bit diffuse token.");
    XCTAssertTrue(aJson.find("\"diffuse32_a\"") != std::string::npos,
                  "Expected serialized JSON to use the width-first 32-bit diffuse token.");

    std::string aLegacyJson = aJson;
    const std::string aNewToken = "\"diffuse64_a\"";
    const std::size_t aTokenIndex = aLegacyJson.find(aNewToken);
    XCTAssertTrue(aTokenIndex != std::string::npos,
                  "Expected serialized JSON to contain a 64-bit diffuse token.");
    if (aTokenIndex != std::string::npos) {
        aLegacyJson.replace(aTokenIndex, aNewToken.size(), "\"diffuse_a64\"");
    }

    GBatch aRoundTrip;
    XCTAssertTrue(GBatch::FromJson(aLegacyJson, &aRoundTrip, &aError),
                  "%s", aError.c_str());
    const std::string aBlock = aRoundTrip.BuildCppScopeBlock(&aError, false);
    XCTAssertFalse(aBlock.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("TwistMix64::DiffuseA(") != std::string::npos,
                  "Expected the legacy diffuse_a64 token to read as Diffuse64A.");
    XCTAssertTrue(aBlock.find("TwistMix32::DiffuseA(") != std::string::npos,
                  "Expected the 32-bit diffuse token to survive JSON round trip.");
}

- (void)testSquashPacksFourLanesThroughTwistMix32 {
    std::vector<GStatement> aStatements;
    std::string aError;
    GSquash aSquash;
    const GSymbol aIndex = GSymbol::Var(TwistVariable::kIndex);
    XCTAssertTrue(aSquash.Bake(GSymbol::Var(TwistVariable::kParamOutput),
                               GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneA),
                               GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneB),
                               GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneC),
                               GSymbol::Buf(TwistWorkSpaceSlot::kWorkLaneD),
                               aIndex,
                               &aStatements,
                               &aError),
                  "%s", aError.c_str());

    GBatch aBatch;
    aBatch.CommitStatements(&aStatements);
    const std::string aBlock = aBatch.BuildCppScopeBlock(&aError, true);
    XCTAssertFalse(aBlock.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("TwistSquash::Squash") != std::string::npos,
                  "Expected GSquash to emit a TwistSquash call.\n%s", aBlock.c_str());
    XCTAssertTrue(aBlock.find("TwistSquash::SquashA(") != std::string::npos ||
                  aBlock.find("TwistSquash::SquashB(") != std::string::npos ||
                  aBlock.find("TwistSquash::SquashC(") != std::string::npos,
                  "Expected GSquash to choose one 32-bit squash variant.");
    XCTAssertTrue(aBlock.find("std::uint8_t *aWorkLaneA = TwistWorkSpace::GetBuffer") != std::string::npos,
                  "Expected work lane A alias to be declared.");
    XCTAssertTrue(aBlock.find("std::uint8_t *aWorkLaneD = TwistWorkSpace::GetBuffer") != std::string::npos,
                  "Expected work lane D alias to be declared.");
    XCTAssertTrue(aBlock.find("std::uint32_t aSquash") == std::string::npos,
                  "GSquash should delegate the block loop to TwistSquash.");
    XCTAssertTrue(aBlock.find("TwistMix32::Diffuse") == std::string::npos,
                  "GSquash should not inline the diffuse anymore.");
}

- (void)testTwistSquashRuntimeUsesTwistMix32 {
    std::vector<std::uint8_t> aLaneA(S_BLOCK, 0U);
    std::vector<std::uint8_t> aLaneB(S_BLOCK, 0U);
    std::vector<std::uint8_t> aLaneC(S_BLOCK, 0U);
    std::vector<std::uint8_t> aLaneD(S_BLOCK, 0U);
    std::vector<std::uint8_t> aOutputA(S_BLOCK, 0U);
    std::vector<std::uint8_t> aOutputB(S_BLOCK, 0U);
    std::vector<std::uint8_t> aOutputC(S_BLOCK, 0U);

    const std::size_t aIndex = 17U;
    aLaneA[aIndex] = 0x12U;
    aLaneB[aIndex] = 0x34U;
    aLaneC[aIndex] = 0x56U;
    aLaneD[aIndex] = 0x78U;

    TwistSquash::SquashA(aLaneA.data(), aLaneB.data(), aLaneC.data(), aLaneD.data(), aOutputA.data());
    TwistSquash::SquashB(aLaneA.data(), aLaneB.data(), aLaneC.data(), aLaneD.data(), aOutputB.data());
    TwistSquash::SquashC(aLaneA.data(), aLaneB.data(), aLaneC.data(), aLaneD.data(), aOutputC.data());

    const std::uint32_t aPacked =
        (static_cast<std::uint32_t>(aLaneA[aIndex]) << 0U) |
        (static_cast<std::uint32_t>(aLaneB[aIndex]) << 8U) |
        (static_cast<std::uint32_t>(aLaneC[aIndex]) << 16U) |
        (static_cast<std::uint32_t>(aLaneD[aIndex]) << 24U);

    XCTAssertEqual(aOutputA[aIndex], static_cast<std::uint8_t>(TwistMix32::DiffuseA(aPacked)));
    XCTAssertEqual(aOutputB[aIndex], static_cast<std::uint8_t>(TwistMix32::DiffuseB(aPacked)));
    XCTAssertEqual(aOutputC[aIndex], static_cast<std::uint8_t>(TwistMix32::DiffuseC(aPacked)));
}

- (void)testSnowAndInvestLaneSlotsExposeAliases {
    XCTAssertTrue(TwistWorkSpaceSlot::kSnowLaneA == TwistWorkSpaceSlot::kSnowLaneA);
    XCTAssertTrue(TwistWorkSpaceSlot::kSnowLaneB == TwistWorkSpaceSlot::kSnowLaneB);
    XCTAssertTrue(TwistWorkSpaceSlot::kSnowLaneC == TwistWorkSpaceSlot::kSnowLaneC);
    XCTAssertTrue(TwistWorkSpaceSlot::kSnowLaneD == TwistWorkSpaceSlot::kSnowLaneD);

    XCTAssertTrue(BufAliasName(TwistWorkSpaceSlot::kInvestA) == "aInvestLaneA");
    XCTAssertTrue(BufAliasName(TwistWorkSpaceSlot::kInvestH) == "aInvestLaneH");
    XCTAssertTrue(BufName(TwistWorkSpaceSlot::kInvestA) == "invest_a");
    XCTAssertTrue(BufName(TwistWorkSpaceSlot::kInvestH) == "invest_h");
    XCTAssertTrue(TwistWorkSpace::GetBufferLength(TwistWorkSpaceSlot::kInvestA) == S_BLOCK);
    XCTAssertTrue(TwistWorkSpace::GetBufferLength(TwistWorkSpaceSlot::kInvestH) == S_BLOCK);

    TwistWorkSpace aWorkSpace;
    GTwistExpander aExpander;
    XCTAssertTrue(TwistWorkSpace::GetBuffer(&aWorkSpace, &aExpander, TwistWorkSpaceSlot::kInvestA) == aWorkSpace.mInvestLaneA);
    XCTAssertTrue(TwistWorkSpace::GetBuffer(&aWorkSpace, &aExpander, TwistWorkSpaceSlot::kInvestH) == aWorkSpace.mInvestLaneH);
}

- (void)testKDFParameterBuffersEmitDirectIndexedAccess {
    const GSymbol aInput = GSymbol::Buf(TwistWorkSpaceSlot::kParamSource);
    const GSymbol aOutput = GSymbol::Buf(TwistWorkSpaceSlot::kParamDestination);
    const GSymbol aMemberSource = GSymbol::Buf(TwistWorkSpaceSlot::kSource);
    const GSymbol aIndex = GSymbol::Var(TwistVariable::kIndex);
    const GSymbol aIngress = GSymbol::Var(TwistVariable::kIngress);

    const GStatement aReadStatement = GStatement::Assign(
        GTarget::Symbol(aIngress),
        GExpr::Read(aInput, GExpr::Add(GExpr::Symbol(aIndex), GExpr::Const32(7))));
    const std::vector<std::string> aReadLines = aReadStatement.ToCPPStatements();

    XCTAssertTrue(aReadLines.size() == 1U,
                  "Expected a single C++ read statement line.");
    XCTAssertTrue(aReadLines[0].find("pSource[((aIndex + 7U)) & S_BLOCK1]") != std::string::npos,
                  "Expected direct pSource indexed read emission.");
    XCTAssertTrue(aReadLines[0].find("aInvalidBuffer") == std::string::npos,
                  "Parameter buffer read should not emit aInvalidBuffer.");

    const GStatement aMemberReadStatement = GStatement::Assign(
        GTarget::Symbol(aIngress),
        GExpr::Read(aMemberSource, GExpr::Add(GExpr::Symbol(aIndex), GExpr::Const32(9))));
    const std::vector<std::string> aMemberReadLines = aMemberReadStatement.ToCPPStatements();

    XCTAssertTrue(aMemberReadLines.size() == 1U,
                  "Expected a single member-source read statement line.");
    XCTAssertTrue(aMemberReadLines[0].find("mSource[((aIndex + 9U)) & S_BLOCK1]") != std::string::npos,
                  "Expected kSource to emit mSource indexed access.");

    const GStatement aWriteStatement = GStatement::Assign(
        GTarget::Write(aOutput, GExpr::Sub(GExpr::Const32(S_BLOCK1), GExpr::Symbol(aIndex))),
        GExpr::Symbol(aIngress));
    const std::vector<std::string> aWriteLines = aWriteStatement.ToCPPStatements();

    XCTAssertTrue(aWriteLines.size() == 1U,
                  "Expected a single C++ write statement line.");
    XCTAssertTrue(aWriteLines[0].find("pDestination[S_BLOCK1 - aIndex] = aIngress;") != std::string::npos,
                  "Expected direct pDestination indexed write emission.");
    XCTAssertTrue(aWriteLines[0].find("aInvalidBuffer") == std::string::npos,
                  "Parameter buffer write should not emit aInvalidBuffer.");

    GBatch aBatch;
    std::vector<GStatement> aStatements;
    aStatements.push_back(aReadStatement);
    aBatch.CommitStatements(&aStatements);
    std::string aError;
    const std::string aBlock = aBatch.BuildCppScopeBlock(&aError, true);
    XCTAssertTrue(aError.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("std::uint8_t *pSource") == std::string::npos,
                  "Parameter source should not get a local pointer declaration.");
    XCTAssertTrue(aBlock.find("TwistWorkSpace::GetBuffer(pWorkSpace, static_cast<TwistWorkSpaceSlot>(2))") == std::string::npos,
                  "Parameter source should not use an opaque workspace lookup.");
}

- (void)testPhaseDomainSaltSlotsEmitWorkspaceSaltAliases {
    const GSymbol aSalt = GSymbol::Buf(TwistWorkSpaceSlot::kPhaseASaltOrbiterAssignA);
    const GSymbol aSaltH = GSymbol::Buf(TwistWorkSpaceSlot::kPhaseHSaltWandererUpdateF);
    const GSymbol aIngress = GSymbol::Var(TwistVariable::kIngress);
    const GSymbol aCross = GSymbol::Var(TwistVariable::kCross);

    XCTAssertTrue(BufName(TwistWorkSpaceSlot::kPhaseASaltOrbiterAssignA) == "phase_a_salt_orbiter_assign_a",
                  "Expected phase salt JSON/buffer name.");
    XCTAssertTrue(BufAliasName(TwistWorkSpaceSlot::kPhaseASaltOrbiterAssignA) == "aPhaseAOrbiterAssignSaltA",
                  "Expected phase salt C++ alias name.");
    XCTAssertTrue(BufName(TwistWorkSpaceSlot::kPhaseHSaltWandererUpdateF) == "phase_h_salt_wanderer_update_f",
                  "Expected phase H salt JSON/buffer name.");
    XCTAssertTrue(BufAliasName(TwistWorkSpaceSlot::kPhaseHSaltWandererUpdateF) == "aPhaseHWandererUpdateSaltF",
                  "Expected phase H salt C++ alias name.");

    GBatch aBatch;
    std::vector<GStatement> aStatements;
    aStatements.push_back(GStatement::Assign(
        GTarget::Symbol(aIngress),
        GExpr::Read(aSalt, GExpr::Const32(5))));
    aStatements.push_back(GStatement::Assign(
        GTarget::Symbol(aCross),
        GExpr::Read(aSaltH, GExpr::Const32(7))));
    aBatch.CommitStatements(&aStatements);

    std::string aError;
    const std::string aBlock = aBatch.BuildCppScopeBlock(&aError, true);
    XCTAssertTrue(aError.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("std::uint64_t *aPhaseAOrbiterAssignSaltA") != std::string::npos,
                  "Expected salt alias to be a uint64_t pointer.");
    XCTAssertTrue(aBlock.find("aPhaseAOrbiterAssignSaltA[(5U) & S_SALT1]") != std::string::npos,
                  "Expected salt read to wrap with S_SALT1.");
    XCTAssertTrue(aBlock.find("std::uint64_t *aPhaseHWandererUpdateSaltF") != std::string::npos,
                  "Expected phase H salt alias to be a uint64_t pointer.");
    XCTAssertTrue(aBlock.find("aPhaseHWandererUpdateSaltF[(7U) & S_SALT1]") != std::string::npos,
                  "Expected phase H salt read to wrap with S_SALT1.");

    TwistWorkSpace aWorkSpace;
    GTwistExpander aRuntimeExpander;
    aWorkSpace.mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA[5] = 0x1122334455667788ULL;
    aWorkSpace.mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF[7] = 0x8877665544332211ULL;
    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    XCTAssertTrue(aBatch.ExecuteWithVariables(&aWorkSpace, &aRuntimeExpander, &aVariables, &aError),
                  "Phase salt runtime read failed: %s", aError.c_str());
    XCTAssertTrue(aVariables["aIngress"] == 0x1122334455667788ULL,
                  "Expected runtime to read phase A workspace salt.");
    XCTAssertTrue(aVariables["aCross"] == 0x8877665544332211ULL,
                  "Expected runtime to read phase H workspace salt.");

    GTwistExpander aExportExpander;
    aExportExpander.mNameBase = "PhaseSalt";
    aExportExpander.mSeed.AddBatch(aBatch);
    const std::string aExportRoot = "/private/tmp/mm_phase_salt_emit";
    XCTAssertTrue(aExportExpander.ExportCPPProjectRoot(aExportRoot, &aError),
                  "Export failed: %s", aError.c_str());

    std::vector<std::uint8_t> aCppBytes;
    const std::string aCppPath = FileIO::Join(aExportRoot, "TwistExpander_PhaseSalt.cpp");
    XCTAssertTrue(FileIO::Load(aCppPath, aCppBytes), "Failed to load emitted cpp file.");
    const std::string aCpp(aCppBytes.begin(), aCppBytes.end());
    XCTAssertTrue(aCpp.find("[[maybe_unused]] std::uint64_t *aPhaseAOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA;") != std::string::npos,
                  "Expected exported seed to alias phase A workspace salt.");
    XCTAssertTrue(aCpp.find("[[maybe_unused]] std::uint64_t *aPhaseHWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF;") != std::string::npos,
                  "Expected exported seed to alias phase H workspace salt.");
    XCTAssertTrue(aCpp.find("const TwistDomainSaltSet TwistExpander_PhaseSalt::kPhaseHSalts") != std::string::npos,
                  "Expected exported phase H static salt pack.");
}

- (void)testPhaseDomainWordsEmitWorkspaceConstants {
    const GSymbol aPhaseAIngress = GSymbol::WorkspaceDomainWord(TwistDomain::kPhaseA,
                                                                TwistConstants::kIngress);
    const GSymbol aPhaseDCross = GSymbol::WorkspaceDomainWord(TwistDomain::kPhaseD,
                                                              TwistConstants::kCross);
    const GSymbol aPhaseHScatter = GSymbol::WorkspaceDomainWord(TwistDomain::kPhaseH,
                                                                TwistConstants::kScatter);
    const GSymbol aIngress = GSymbol::Var(TwistVariable::kIngress);
    const GSymbol aCross = GSymbol::Var(TwistVariable::kCross);
    const GSymbol aScatter = GSymbol::Var(TwistVariable::kScatter);

    XCTAssertTrue(aPhaseAIngress.mName == "aPhaseADomainWordIngress",
                  "Expected phase A ingress domain-word alias.");
    XCTAssertTrue(aPhaseDCross.mName == "aPhaseDDomainWordCross",
                  "Expected phase D cross domain-word alias.");
    XCTAssertTrue(aPhaseHScatter.mName == "aPhaseHDomainWordScatter",
                  "Expected phase H scatter domain-word alias.");

    GBatch aBatch;
    std::vector<GStatement> aStatements;
    aStatements.push_back(GStatement::Assign(
        GTarget::Symbol(aIngress),
        GExpr::Xor(GExpr::Symbol(aPhaseAIngress), GExpr::Const64(0x0102030405060708ULL))));
    aStatements.push_back(GStatement::Assign(
        GTarget::Symbol(aCross),
        GExpr::Symbol(aPhaseDCross)));
    aStatements.push_back(GStatement::Assign(
        GTarget::Symbol(aScatter),
        GExpr::Symbol(aPhaseHScatter)));
    aBatch.CommitStatements(&aStatements);

    std::string aError;
    const std::string aBlock = aBatch.BuildCppScopeBlock(&aError, true);
    XCTAssertTrue(aError.empty(), "%s", aError.c_str());
    XCTAssertTrue(aBlock.find("const std::uint64_t &aPhaseADomainWordIngress = pWorkSpace->mDomainBundle.mPhaseAConstants.mIngress;") != std::string::npos,
                  "Expected phase A ingress domain word to bind from workspace constants.");
    XCTAssertTrue(aBlock.find("const std::uint64_t &aPhaseDDomainWordCross = pWorkSpace->mDomainBundle.mPhaseDConstants.mCross;") != std::string::npos,
                  "Expected phase D cross domain word to bind from workspace constants.");
    XCTAssertTrue(aBlock.find("const std::uint64_t &aPhaseHDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseHConstants.mScatter;") != std::string::npos,
                  "Expected phase H scatter domain word to bind from workspace constants.");
    XCTAssertTrue(aBlock.find("aPhaseADomainWordIngress = 0;") == std::string::npos,
                  "Phase domain word should not get a zero scalar declaration.");

    TwistWorkSpace aWorkSpace;
    GTwistExpander aRuntimeExpander;
    aWorkSpace.mDomainBundle.mPhaseAConstants.mIngress = 0x1122334455667788ULL;
    aWorkSpace.mDomainBundle.mPhaseDConstants.mCross = 0xAABBCCDDEEFF0011ULL;
    aWorkSpace.mDomainBundle.mPhaseHConstants.mScatter = 0x9988776655443322ULL;
    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    XCTAssertTrue(aBatch.ExecuteWithVariables(&aWorkSpace, &aRuntimeExpander, &aVariables, &aError),
                  "Phase domain word runtime read failed: %s", aError.c_str());
    XCTAssertTrue(aVariables["aIngress"] == (0x1122334455667788ULL ^ 0x0102030405060708ULL),
                  "Expected runtime to read phase A ingress from workspace constants.");
    XCTAssertTrue(aVariables["aCross"] == 0xAABBCCDDEEFF0011ULL,
                  "Expected runtime to read phase D cross from workspace constants.");
    XCTAssertTrue(aVariables["aScatter"] == 0x9988776655443322ULL,
                  "Expected runtime to read phase H scatter from workspace constants.");

    GTwistExpander aExportExpander;
    aExportExpander.mNameBase = "PhaseDomainWord";
    aExportExpander.mSeed.AddBatch(aBatch);
    const std::string aExportRoot = "/private/tmp/mm_phase_domain_word_emit";
    XCTAssertTrue(aExportExpander.ExportCPPProjectRoot(aExportRoot, &aError),
                  "Export failed: %s", aError.c_str());

    std::vector<std::uint8_t> aCppBytes;
    const std::string aCppPath = FileIO::Join(aExportRoot, "TwistExpander_PhaseDomainWord.cpp");
    XCTAssertTrue(FileIO::Load(aCppPath, aCppBytes), "Failed to load emitted cpp file.");
    const std::string aCpp(aCppBytes.begin(), aCppBytes.end());
    XCTAssertTrue(aCpp.find("const std::uint64_t &aPhaseADomainWordIngress = pWorkSpace->mDomainBundle.mPhaseAConstants.mIngress;") != std::string::npos,
                  "Expected exported seed to bind phase A ingress domain word.");
    XCTAssertTrue(aCpp.find("const std::uint64_t &aPhaseDDomainWordCross = pWorkSpace->mDomainBundle.mPhaseDConstants.mCross;") != std::string::npos,
                  "Expected exported seed to bind phase D cross domain word.");
    XCTAssertTrue(aCpp.find("const std::uint64_t &aPhaseHDomainWordScatter = pWorkSpace->mDomainBundle.mPhaseHConstants.mScatter;") != std::string::npos,
                  "Expected exported seed to bind phase H scatter domain word.");
    XCTAssertTrue(aCpp.find("aPhaseADomainWordIngress = 0;") == std::string::npos,
                  "Exported seed should not zero-declare phase domain words.");
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
