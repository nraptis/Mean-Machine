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
#include "GSeedDeriveMaterial.hpp"
#include "GSeedMatrixRollups.hpp"
#include "FileIO.hpp"
#include "GSeedProgram.hpp"
#include "GTwistExpander.hpp"
#include "TwistExpander.hpp"
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

    //TwistExpander_Gollum aExpanderA;
    GTwistExpander aExpanderA;
    
    // This uses json load;
    GTwistExpander aExpanderB;
    
    std::string aLoadError;
    if (!aExpanderB.LoadJSONProjectRoot("CornTesting/Gen/Gollum.json", &aLoadError)) {
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
    
    for (int i=0;i<S_BLOCK;i++) {
        aWorkSpaceA.mWorkLaneA[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneA[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneB[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneB[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneC[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneC[i] = Random::GetByte();
        aWorkSpaceA.mWorkLaneD[i] = Random::GetByte();
        aWorkSpaceB.mWorkLaneD[i] = Random::GetByte();
        
        aWorkSpaceA.mListExpansionLaneA[i] = Random::GetByte();
        aWorkSpaceB.mListExpansionLaneA[i] = Random::GetByte();
        aWorkSpaceA.mListExpansionLaneB[i] = Random::GetByte();
        aWorkSpaceB.mListExpansionLaneB[i] = Random::GetByte();
        aWorkSpaceA.mListExpansionLaneC[i] = Random::GetByte();
        aWorkSpaceB.mListExpansionLaneC[i] = Random::GetByte();
        aWorkSpaceA.mListExpansionLaneD[i] = Random::GetByte();
        aWorkSpaceB.mListExpansionLaneD[i] = Random::GetByte();
        
        aWorkSpaceA.mMaskLaneA[i] = Random::GetByte();
        aWorkSpaceB.mMaskLaneA[i] = Random::GetByte();
        aWorkSpaceA.mMaskLaneB[i] = Random::GetByte();
        aWorkSpaceB.mMaskLaneB[i] = Random::GetByte();
    }
    
    memset(aWorkSpaceA.mListExpansionLaneA,0,S_BLOCK);
    memset(aWorkSpaceA.mListExpansionLaneB,0,S_BLOCK);
    memset(aWorkSpaceA.mListExpansionLaneC,0,S_BLOCK);
    memset(aWorkSpaceA.mListExpansionLaneD,0,S_BLOCK);
    memset(aWorkSpaceB.mListExpansionLaneA,0,S_BLOCK);
    memset(aWorkSpaceB.mListExpansionLaneB,0,S_BLOCK);
    memset(aWorkSpaceB.mListExpansionLaneC,0,S_BLOCK);
    memset(aWorkSpaceB.mListExpansionLaneD,0,S_BLOCK);
    
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
    
    
    
    
    
    TwistFarmSBox aFarmSBox;
    TwistFarmSalt aFarmSalt;
    
    aExpanderA.Seed(&aWorkSpaceA, &aFarmSBox, &aFarmSalt, 0ULL, aSourceA, (std::uint8_t *)pwd, ps);
    
    aExpanderB.Seed(&aWorkSpaceB, &aFarmSBox, &aFarmSalt, 0ULL, aSourceB, (std::uint8_t *)pwd, ps);

    
    for (int i=0;i<S_BLOCK;i++) {
        if (aWorkSpaceA.mListExpansionLaneA[i] != aWorkSpaceB.mListExpansionLaneA[i]) {
            XCTFail("{export test} expand lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mListExpansionLaneA[i], aWorkSpaceB.mListExpansionLaneA[i]);
            return;
        }
        if (aWorkSpaceA.mListExpansionLaneB[i] != aWorkSpaceB.mListExpansionLaneB[i]) {
            XCTFail("{export test} expand lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mListExpansionLaneB[i], aWorkSpaceB.mListExpansionLaneB[i]);
            return;
        }
        if (aWorkSpaceA.mListExpansionLaneC[i] != aWorkSpaceB.mListExpansionLaneC[i]) {
            XCTFail("{export test} expand lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mListExpansionLaneC[i], aWorkSpaceB.mListExpansionLaneC[i]);
            return;
        }
        if (aWorkSpaceA.mListExpansionLaneD[i] != aWorkSpaceB.mListExpansionLaneD[i]) {
            XCTFail("{export test} expand lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mListExpansionLaneD[i], aWorkSpaceB.mListExpansionLaneD[i]);
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



@end
