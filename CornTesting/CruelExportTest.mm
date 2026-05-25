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
#include "TwistExpander_WiseOwl_0006.hpp"

#include "Builder_KDF.hpp"
#include "FileIO.hpp"
#include "GSeedProgram.hpp"
#include "GTwistExpander.hpp"
#include "TwistExpander.hpp"
#include "TwistFastMatrix.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistFarmSalt.hpp"
#include <cctype>
#include <unordered_map>
#include <vector>

@interface CruelExportTest : XCTestCase

@end

@implementation CruelExportTest

- (void)testExportedTwister {
    
    
    const char *pwd = "a man a plan canal";
    int ps = (int)strlen(pwd);
    
    // This is exported from something in G, as C++ code we can drop in over DemoExpander
    
    TwistExpander_WiseOwl_0006 aExpanderA;
    //GTwistExpander aExpanderA;
    
    // This uses json load;
    GTwistExpander aExpanderB;
    
    std::string aLoadError;
    if (!aExpanderB.LoadJSONProjectRoot("CornTesting/Gen/WiseOwl_0006.json", &aLoadError)) {
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
    memset(aWorkSpaceA.mWorkLaneE, 0, S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneF, 0, S_BLOCK);
    
    
    memset(aWorkSpaceB.mWorkLaneA, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneB, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneC, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneD, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneE, 0, S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneF, 0, S_BLOCK);
    
    memset(aWorkSpaceA.mExpansionLaneA, 0, S_BLOCK);
    memset(aWorkSpaceA.mExpansionLaneB, 0, S_BLOCK);
    memset(aWorkSpaceA.mExpansionLaneC, 0, S_BLOCK);
    memset(aWorkSpaceA.mExpansionLaneD, 0, S_BLOCK);
    memset(aWorkSpaceA.mExpansionLaneE, 0, S_BLOCK);
    memset(aWorkSpaceA.mExpansionLaneF, 0, S_BLOCK);
    
    
    memset(aWorkSpaceB.mExpansionLaneA, 0, S_BLOCK);
    memset(aWorkSpaceB.mExpansionLaneB, 0, S_BLOCK);
    memset(aWorkSpaceB.mExpansionLaneC, 0, S_BLOCK);
    memset(aWorkSpaceB.mExpansionLaneD, 0, S_BLOCK);
    memset(aWorkSpaceB.mExpansionLaneE, 0, S_BLOCK);
    memset(aWorkSpaceB.mExpansionLaneF, 0, S_BLOCK);
    
    memset(aWorkSpaceA.mOperationLaneA, 0, S_BLOCK);
    memset(aWorkSpaceA.mOperationLaneB, 0, S_BLOCK);
    memset(aWorkSpaceA.mOperationLaneC, 0, S_BLOCK);
    memset(aWorkSpaceA.mOperationLaneD, 0, S_BLOCK);
    memset(aWorkSpaceA.mOperationLaneE, 0, S_BLOCK);
    memset(aWorkSpaceA.mOperationLaneF, 0, S_BLOCK);
    
    
    memset(aWorkSpaceB.mOperationLaneA, 0, S_BLOCK);
    memset(aWorkSpaceB.mOperationLaneB, 0, S_BLOCK);
    memset(aWorkSpaceB.mOperationLaneC, 0, S_BLOCK);
    memset(aWorkSpaceB.mOperationLaneD, 0, S_BLOCK);
    memset(aWorkSpaceB.mOperationLaneE, 0, S_BLOCK);
    memset(aWorkSpaceB.mOperationLaneF, 0, S_BLOCK);
    
    for (int i=0;i<S_BLOCK;i++) {
        
        
        aWorkSpaceA.mWorkLaneA[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneA[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneB[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneB[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneC[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneC[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneD[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneD[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneE[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneE[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneF[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneF[i] = Random::GetByte();
        
        
        aWorkSpaceA.mExpansionLaneA[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneA[i] = Random::GetByte();
        aWorkSpaceA.mExpansionLaneB[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneB[i] = Random::GetByte();
        aWorkSpaceA.mExpansionLaneC[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneC[i] = Random::GetByte();
        aWorkSpaceA.mExpansionLaneD[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneD[i] = Random::GetByte();
        aWorkSpaceA.mExpansionLaneE[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneE[i] = Random::GetByte();
        aWorkSpaceA.mExpansionLaneF[i] = Random::GetByte();
        aWorkSpaceB.mExpansionLaneF[i] = Random::GetByte();
        
        
        aWorkSpaceA.mOperationLaneA[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneA[i] = Random::GetByte();
        aWorkSpaceA.mOperationLaneB[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneB[i] = Random::GetByte();
        aWorkSpaceA.mOperationLaneC[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneC[i] = Random::GetByte();
        aWorkSpaceA.mOperationLaneD[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneD[i] = Random::GetByte();
        aWorkSpaceA.mOperationLaneE[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneE[i] = Random::GetByte();
        aWorkSpaceA.mOperationLaneF[i] = Random::GetByte();
        aWorkSpaceB.mOperationLaneF[i] = Random::GetByte();
        
        
        
        aWorkSpaceA.mMaskLaneA[i] = Random::GetByte();
        aWorkSpaceB.mMaskLaneA[i] = Random::GetByte();
        aWorkSpaceA.mMaskLaneB[i] = Random::GetByte();
        aWorkSpaceB.mMaskLaneB[i] = Random::GetByte();
        
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
    
    
    
    
    
    TwistFarmSBox aFarmSBoxA;
    TwistFarmSalt aFarmSaltA;
    
    TwistFarmSBox aFarmSBoxB;
    TwistFarmSalt aFarmSaltB;
    
    aExpanderA.Seed(&aWorkSpaceA, &aFarmSBoxA, &aFarmSaltA, 0ULL, aSourceA, (std::uint8_t *)pwd, ps);
    aExpanderB.Seed(&aWorkSpaceB, &aFarmSBoxB, &aFarmSaltB, 0ULL, aSourceB, (std::uint8_t *)pwd, ps);
    
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
        
        if (aWorkSpaceA.mExpansionLaneE[i] != aWorkSpaceB.mExpansionLaneE[i]) {
            XCTFail("{export test} expand lane e mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpansionLaneE[i], aWorkSpaceB.mExpansionLaneE[i]);
            return;
        }
        
        if (aWorkSpaceA.mExpansionLaneF[i] != aWorkSpaceB.mExpansionLaneF[i]) {
            XCTFail("{export test} expand lane f mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpansionLaneF[i], aWorkSpaceB.mExpansionLaneF[i]);
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
        
        if (aWorkSpaceA.mOperationLaneE[i] != aWorkSpaceB.mOperationLaneE[i]) {
            XCTFail("{export test} oper lane e mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mOperationLaneE[i], aWorkSpaceB.mOperationLaneE[i]);
            return;
        }
        
        if (aWorkSpaceA.mOperationLaneF[i] != aWorkSpaceB.mOperationLaneF[i]) {
            XCTFail("{export test} oper lane f mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mOperationLaneF[i], aWorkSpaceB.mOperationLaneF[i]);
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
        
        /*
        if (aWorkSpaceA.mWorkLaneE[i] != aWorkSpaceB.mWorkLaneE[i]) {
            XCTFail("{export test} work lane e mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneE[i], aWorkSpaceB.mWorkLaneE[i]);
            return;
        }
        
        if (aWorkSpaceA.mWorkLaneF[i] != aWorkSpaceB.mWorkLaneF[i]) {
            XCTFail("{export test} work lane f mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mWorkLaneF[i], aWorkSpaceB.mWorkLaneF[i]);
            return;
        }
        */
    }
    
    /*
     for (int aRow = 0; aRow < H_KEY_A; ++aRow) {
     for (int aCol = 0; aCol < W_KEY_A; ++aCol) {
     const std::uint8_t aValueA = aWorkSpaceA.mKeyBoxA[aRow][aCol];
     const std::uint8_t aValueB = aWorkSpaceB.mKeyBoxA[aRow][aCol];
     if (aValueA != aValueB) {
     XCTFail("{export test} key box a mismatch at row=%d col=%d: A=%u B=%u",
     aRow, aCol, aValueA, aValueB);
     return;
     }
     }
     }
     
     for (int aRow = 0; aRow < H_KEY_B; ++aRow) {
     for (int aCol = 0; aCol < W_KEY_B; ++aCol) {
     const std::uint8_t aValueA = aWorkSpaceA.mKeyBoxB[aRow][aCol];
     const std::uint8_t aValueB = aWorkSpaceB.mKeyBoxB[aRow][aCol];
     if (aValueA != aValueB) {
     XCTFail("{export test} key box b mismatch at row=%d col=%d: A=%u B=%u",
     aRow, aCol, aValueA, aValueB);
     return;
     }
     }
     }
     
     for (int aRow = 0; aRow < H_MASK_A; ++aRow) {
     for (int aCol = 0; aCol < W_MASK_A; ++aCol) {
     const std::uint8_t aValueA = aWorkSpaceA.mMaskBoxA[aRow][aCol];
     const std::uint8_t aValueB = aWorkSpaceB.mMaskBoxA[aRow][aCol];
     if (aValueA != aValueB) {
     XCTFail("{export test} mask box a mismatch at row=%d col=%d: A=%u B=%u",
     aRow, aCol, aValueA, aValueB);
     return;
     }
     }
     }
     
     for (int aRow = 0; aRow < H_MASK_B; ++aRow) {
     for (int aCol = 0; aCol < W_MASK_B; ++aCol) {
     const std::uint8_t aValueA = aWorkSpaceA.mMaskBoxB[aRow][aCol];
     const std::uint8_t aValueB = aWorkSpaceB.mMaskBoxB[aRow][aCol];
     if (aValueA != aValueB) {
     XCTFail("{export test} mask box b mismatch at row=%d col=%d: A=%u B=%u",
     aRow, aCol, aValueA, aValueB);
     return;
     }
     }
     }
     */
    
    
    /*
     
     for (int i=0;i<S_BLOCK;i++) {
     
     if (aWorkSpaceA.mMaskLaneA[i] != aWorkSpaceB.mMaskLaneA[i]) {
     XCTFail("{export test} mask lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mMaskLaneA[i], aWorkSpaceB.mMaskLaneA[i]);
     return;
     }
     
     if (aWorkSpaceA.mMaskLaneB[i] != aWorkSpaceB.mMaskLaneB[i]) {
     XCTFail("{export test} mask lane b mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mMaskLaneB[i], aWorkSpaceB.mMaskLaneB[i]);
     return;
     }
     
     }
     //std::uint8_t *pSource = pSource;
     
     */
    
    
    
    
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
    XCTAssertTrue(aCpp.find("std::uint64_t aOrbitA = 0; std::uint64_t aOrbitB = 0; std::uint64_t aOrbitC = 0; std::uint64_t aOrbitD = 0;") != std::string::npos,
                  "Expected grouped orbiter declarations.");
    XCTAssertTrue(aCpp.find("std::uint64_t aWandererA = 0; std::uint64_t aWandererB = 0; std::uint64_t aWandererC = 0; std::uint64_t aWandererD = 0;") != std::string::npos,
                  "Expected grouped wanderer declarations.");
    XCTAssertTrue(aCpp.find("void TwistExpander_EmitShape::KDF_A(") != std::string::npos,
                  "Expected exported KDF_A function.");
    XCTAssertTrue(aCpp.find("void TwistExpander_EmitShape::KDF_B(") != std::string::npos,
                  "Expected exported KDF_B function.");
    XCTAssertTrue(aCpp.find("kdf-a-matrix-diffusion") != std::string::npos,
                  "Expected Builder_KDF to include the matrix diffusion batch.");

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
