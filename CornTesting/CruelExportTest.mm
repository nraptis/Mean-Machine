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
#include "TwistExpander_Corndogz.hpp"
#include "GTwistTwister.hpp"
#include "GSeedDeriveMaterial.hpp"
#include "FileIO.hpp"
#include "GExpr.hpp"
#include "GSeedProgram.hpp"

#include "GTwistExpander.hpp"
#include "TwistExpander.hpp"
#include <cctype>
#include <vector>

namespace {

bool LoadTextFile(const std::string &pPath,
                  std::string *pText) {
    if (pText == nullptr) {
        return false;
    }

    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes)) {
        return false;
    }
    pText->assign(aBytes.begin(), aBytes.end());
    return true;
}

bool HasUngroupedMaskTerm(const std::string &pText,
                          const std::string &pMaskToken) {
    std::size_t aPos = 0U;
    while ((aPos = pText.find(pMaskToken, aPos)) != std::string::npos) {
        std::size_t aProbe = aPos;
        while ((aProbe > 0U) &&
               (std::isspace(static_cast<unsigned char>(pText[aProbe - 1U])) != 0)) {
            --aProbe;
        }
        if ((aProbe == 0U) || (pText[aProbe - 1U] != ')')) {
            return true;
        }
        aPos += pMaskToken.size();
    }
    return false;
}

} // namespace

@interface CruelExportTest : XCTestCase

@end

@implementation CruelExportTest

- (void)testRemingtonExportFormatting {
    std::string aError;
    GSeedDeriveMaterial aDeriveMaterial;
    GTwistExpander aExpander;
    aExpander.mNameBase = "Remington";

    if (!aDeriveMaterial.PlanPhaseA(&aError)) {
        XCTFail("%s", aError.c_str());
        return;
    }
    if (!aDeriveMaterial.BuildPhaseA(aExpander.mSeeder, &aError)) {
        XCTFail("%s", aError.c_str());
        return;
    }
    if (!aExpander.ExportCPPProjectRoot("CornTesting/Gen", &aError) ||
        !aExpander.ExportJSONProjectRoot("CornTesting/Gen", &aError)) {
        XCTFail("%s", aError.c_str());
        return;
    }

    const std::string aRemingtonCppPath = FileIO::ProjectRoot("CornTesting/Gen/TwistExpander_Remington.cpp");
    std::string aGeneratedCpp;
    if (!LoadTextFile(aRemingtonCppPath, &aGeneratedCpp)) {
        XCTFail("Failed to load generated Remington C++.");
        return;
    }

    XCTAssertFalse(HasUngroupedMaskTerm(aGeneratedCpp, "& 0x7FU"),
                   "Found ungrouped 0x7F mask term in generated C++.");
    XCTAssertFalse(HasUngroupedMaskTerm(aGeneratedCpp, "& 0xFFU"),
                   "Found ungrouped 0xFF mask term in generated C++.");
    XCTAssertTrue(aGeneratedCpp.find("+ 0ULL") == std::string::npos,
                  "Found + 0ULL in generated C++.");
    const bool aHasWorkLaneAForward =
        (aGeneratedCpp.find("aWorkLaneA[aIndex]") != std::string::npos);
    const bool aHasWorkLaneAInverted =
        (aGeneratedCpp.find("aWorkLaneA[S_BLOCK1 - aIndex]") != std::string::npos);
    XCTAssertTrue(aHasWorkLaneAForward || aHasWorkLaneAInverted,
                  "Expected canonical aWorkLaneA index output.");

    const bool aHasAnyInvertedWorkLane =
        (aGeneratedCpp.find("aWorkLaneA[S_BLOCK1 - aIndex]") != std::string::npos) ||
        (aGeneratedCpp.find("aWorkLaneB[S_BLOCK1 - aIndex]") != std::string::npos) ||
        (aGeneratedCpp.find("aWorkLaneC[S_BLOCK1 - aIndex]") != std::string::npos) ||
        (aGeneratedCpp.find("aWorkLaneD[S_BLOCK1 - aIndex]") != std::string::npos);
    XCTAssertTrue(aHasAnyInvertedWorkLane,
                  "Expected canonical inverted work-lane output.");
}

- (void)testExportedTwister {
    

    const char *pwd = "a man a plan a canal";
    int ps = (int)strlen(pwd);
    
    // This is exported from something in G, as C++ code we can drop in over DemoExpander
    TwistExpander_Corndogz aExpanderA;
    
    // This uses json load;
    GTwistTwister aExpanderB;
    
    std::string aLoadError;
    if (!aExpanderB.LoadProjectRoot("CornTesting/Gen/Corndogz.json", &aLoadError)) {
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
        
        aWorkSpaceA.mExpandLaneA[i] = Random::GetByte();
        aWorkSpaceB.mExpandLaneA[i] = Random::GetByte();
        aWorkSpaceA.mExpandLaneB[i] = Random::GetByte();
        aWorkSpaceB.mExpandLaneB[i] = Random::GetByte();
        aWorkSpaceA.mExpandLaneC[i] = Random::GetByte();
        aWorkSpaceB.mExpandLaneC[i] = Random::GetByte();
        aWorkSpaceA.mExpandLaneD[i] = Random::GetByte();
        aWorkSpaceB.mExpandLaneD[i] = Random::GetByte();
    }
    
    memset(aWorkSpaceA.mWorkLaneA,0,S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneB,0,S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneC,0,S_BLOCK);
    memset(aWorkSpaceA.mWorkLaneD,0,S_BLOCK);
    memset(aWorkSpaceA.mExpandLaneA,0,S_BLOCK);
    memset(aWorkSpaceA.mExpandLaneB,0,S_BLOCK);
    memset(aWorkSpaceA.mExpandLaneC,0,S_BLOCK);
    memset(aWorkSpaceA.mExpandLaneD,0,S_BLOCK);
    
    memset(aWorkSpaceB.mWorkLaneA,0,S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneB,0,S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneC,0,S_BLOCK);
    memset(aWorkSpaceB.mWorkLaneD,0,S_BLOCK);
    memset(aWorkSpaceB.mExpandLaneA,0,S_BLOCK);
    memset(aWorkSpaceB.mExpandLaneB,0,S_BLOCK);
    memset(aWorkSpaceB.mExpandLaneC,0,S_BLOCK);
    memset(aWorkSpaceB.mExpandLaneD,0,S_BLOCK);
    
    
    
    aExpanderA.Seed(&aWorkSpaceA, aSourceA, (std::uint8_t *)pwd, ps);
    aExpanderB.Seed(&aWorkSpaceB, aSourceB, (std::uint8_t *)pwd, ps);

    
    for (int i=0;i<S_BLOCK;i++) {
        if (aWorkSpaceA.mExpandLaneA[i] != aWorkSpaceB.mExpandLaneA[i]) {
            XCTFail("{export test} expand lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpandLaneA[i], aWorkSpaceB.mExpandLaneA[i]);
            return;
        }
        if (aWorkSpaceA.mExpandLaneB[i] != aWorkSpaceB.mExpandLaneB[i]) {
            XCTFail("{export test} expand lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpandLaneB[i], aWorkSpaceB.mExpandLaneB[i]);
            return;
        }
        if (aWorkSpaceA.mExpandLaneC[i] != aWorkSpaceB.mExpandLaneC[i]) {
            XCTFail("{export test} expand lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpandLaneC[i], aWorkSpaceB.mExpandLaneC[i]);
            return;
        }
        if (aWorkSpaceA.mExpandLaneD[i] != aWorkSpaceB.mExpandLaneD[i]) {
            XCTFail("{export test} expand lane a mismatched at %d: A=%u B=%u", i, aWorkSpaceA.mExpandLaneD[i], aWorkSpaceB.mExpandLaneD[i]);
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
    
    
    //std::uint8_t *pSource = pSource;
    
    
    
    
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

- (void)testDiffuseExpressionEmissionUsesTwistMix64 {
    const GSymbol aValue = GSymbol::Var("aValue");
    const GStatement aStatement = GStatement::Assign(
        GTarget::Symbol(aValue),
        GExpr::Diffuse(GExpr::Symbol(aValue)));
    const std::vector<std::string> aLines = aStatement.ToCPPStatements();

    XCTAssertTrue(aLines.size() == 1U,
                  "Expected a single C++ statement line.");
    XCTAssertTrue(aLines[0].find("TwistMix64::Diffuse(") != std::string::npos,
                  "Expected TwistMix64::Diffuse call in emitted C++.");
}



@end
