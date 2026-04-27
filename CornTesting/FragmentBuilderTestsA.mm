//
//  FragmentBuilderTestsA.m
//  CornTesting
//
//  Created by Trombone on 4/26/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include <algorithm>
#include <vector>

#include "TwistWorkSpace.hpp"
#include "GSymbol.hpp"
#include "TwistFunctional.hpp"
#include "GTermExpander.hpp"
#include "GLoopFragmentComposer.hpp"
#include "Varz.hpp"
#include "StatementChecker.hpp"
#include "Random.hpp"

/*
 When is Byte suffix created?
 for every case where the variable being read is not
 a.) a plain symbol (example: aValue)
 b.) just a buffer read, including the mask (example: aWorkerA[aWorkerAKeyA], example: aSaltA[i & 0x7FU])
 */

@interface FragmentBuilderTestsA : XCTestCase

@end

@implementation FragmentBuilderTestsA

- (void)testValuePlusExpandedCarry {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixVariable(aVars.mCarry).ExpandDebug(GTermPattern::kRotateAdd, 3, 177);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aCarryByteA = RotL8((aCarry + 177U), 3U);",
        "aValue = aCarryByteA;"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testValuePlusEqualsCarry {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetAddEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixVariable(aVars.mCarry);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aValue += aCarry;"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testCarrySaltBox {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetAddEqual(aVars.mCarry);
    aComposer.EnableDebugMixAllAdd();
    
    aComposer.MixBuffer(aVars.mSaltA).Key()
        .ExpandDebug(GTermPattern::kPostRotateMul, 55, 22);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aSaltAByteA = RotL8(aSaltA[i & 0x7FU], 7U) * 22U;",
        "aCarry += aSaltAByteA;"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testCarrySaltBoxSelfReference {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetAddEqual(aVars.mCarry);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mSaltA).Key(aVars.mCarry).Offset(71);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aSaltAKeyA = aCarry + 71U;",
        "aCarry += aSaltA[aSaltAKeyA & 0x7FU];"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testValueTwoSameWorkersOddCycle {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mWorkerA).Offset(765).Key(aVars.mValue);
    aComposer.MixBuffer(aVars.mWorkerA).Offset(432).Key(aVars.mValue);
    
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aWorkLaneAKeyA = aValue + 765U;",
        "if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }",
        "aWorkLaneAKeyB = aValue + 432U;",
        "if (aWorkLaneAKeyB >= S_BLOCK) { aWorkLaneAKeyB -= S_BLOCK; }",
        "aValue = aWorkLaneA[aWorkLaneAKeyA] + aWorkLaneA[aWorkLaneAKeyB];"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testWithoutOffsetOrMod {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mWorkerA);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aValue = aWorkLaneA[i];"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testWithoutOffset {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mWorkerA).ExpandDebug(GTermPattern::kXor, 0xFA, 0XDE);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aWorkLaneAByteA = aWorkLaneA[i] ^ 250U;",
        "aValue = aWorkLaneAByteA;"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testWithoutMod {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mWorkerA).Offset(1);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aWorkLaneAKeyA = i + 1U;",
        "if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }",
        "aValue = aWorkLaneA[aWorkLaneAKeyA];"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testUpdateSBoxUpdateSimple {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllXor();
    aComposer.MixBuffer(aVars.mSaltA);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixBuffer(aVars.mSaltB);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aValue = aSaltA[i & 0x7FU];",
        "aValue = aSBoxA[aValue];",
        "aValue ^= aSaltB[i & 0x7FU];",
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testUpdateSBoxUpdateWithJustOffset {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllXor();
    aComposer.MixBuffer(aVars.mSaltA).Offset(125);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixBuffer(aVars.mSaltB).Offset(127);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aSaltAKeyA = i + 125U;",
        "aValue = aSaltA[aSaltAKeyA & 0x7FU];",
        "aValue = aSBoxA[aValue];",
        "aSaltBKeyA = i + 127U;",
        "aValue ^= aSaltB[aSaltBKeyA & 0x7FU];"
    };

    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
    
}

- (void)testUpdateSBoxUpdateJustMods {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllXor();
    aComposer.MixBuffer(aVars.mSaltA).ExpandDebug(GTermPattern::kXor, 0x37, 0);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixBuffer(aVars.mSaltB).ExpandDebug(GTermPattern::kMul, 199, 0);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aSaltAByteA = aSaltA[i & 0x7FU] ^ 55U;",
        "aValue = aSaltAByteA;",
        "aValue = aSBoxA[aValue];",
        "aSaltBByteA = aSaltB[i & 0x7FU] * 199U;",
        "aValue ^= aSaltBByteA;"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testUpdateSBoxUpdateSimpleWithTrickyPreSBoxOp {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllXor();
    aComposer.MixBuffer(aVars.mSaltA);
    aComposer.Transform(aVars.mSBoxA).ExpandDebug(GTermPattern::kMul, 121, 0);
    aComposer.MixBuffer(aVars.mSaltB);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aValue = aSaltA[i & 0x7FU];",
        "aSBoxAByteA = aSBoxA[aValue] * 121U;",
        "aValue = aSBoxAByteA;",
        "aValue ^= aSaltB[i & 0x7FU];"
    };

    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testUpdateSBoxUpdateWithOffsetAndMods {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllXor();
    aComposer.MixBuffer(aVars.mSaltA).Offset(125).ExpandDebug(GTermPattern::kXor, 0xDD, 0);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixBuffer(aVars.mSaltB).Offset(127).ExpandDebug(GTermPattern::kMul, 61, 0);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aSaltAKeyA = i + 125U;",
        "aSaltAByteA = aSaltA[aSaltAKeyA & 0x7FU] ^ 221U;",
        "aValue = aSaltAByteA;",
        "aValue = aSBoxA[aValue];",
        "aSaltBKeyA = i + 127U;",
        "aSaltBByteA = aSaltB[aSaltBKeyA & 0x7FU] * 61U;",
        "aValue ^= aSaltBByteA;",
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testUpdateValueIndexValue {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mWorkerA).Key(aVars.mValue);
    aComposer.MixBuffer(aVars.mWorkerB).Key(aVars.mValue);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixBuffer(aVars.mWorkerA).Key(aVars.mValue);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aValue = aWorkLaneA[aValue] + aWorkLaneB[aValue];",
        "aValue = aSBoxA[aValue];",
        "aValue += aWorkLaneA[aValue];"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testUpdateCarryIndexValue {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mWorkerA).Key(aVars.mCarry).ExpandDebug(GTermPattern::kMul, 113, 0);
    aComposer.MixBuffer(aVars.mWorkerB).Key(aVars.mCarry);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixBuffer(aVars.mWorkerA).Key(aVars.mCarry).Offset(21);
    aComposer.MixBuffer(aVars.mWorkerB).Key(aVars.mCarry);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aWorkLaneAByteA = aWorkLaneA[aCarry] * 113U;",
        "aValue = aWorkLaneAByteA + aWorkLaneB[aCarry];",
        "aValue = aSBoxA[aValue];",
        "aWorkLaneAKeyA = aCarry + 21U;",
        "if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }",
        "aValue += aWorkLaneA[aWorkLaneAKeyA] + aWorkLaneB[aCarry];",
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testUpdateTwistUpdate {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixVariable(aVars.mCarry);
    aComposer.MixBuffer(aVars.mSaltC).Key(aVars.mLoopIndex);
    aComposer.Transform(aVars.mValue).ExpandDebug(GTermPattern::kPostRotateMul, 7, 31);
    aComposer.MixBuffer(aVars.mSaltB);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aValue = aCarry + aSaltC[i & 0x7FU];",
        "aValue = RotL8(aValue, 7U) * 31U;",
        "aValue += aSaltB[i & 0x7FU];"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testUpdateTripleSameWorker {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllXor();
    aComposer.MixBuffer(aVars.mWorkerA).Offset(20).ExpandDebug(GTermPattern::kAdd, 25, 0);
    aComposer.MixBuffer(aVars.mWorkerA).Offset(120).ExpandDebug(GTermPattern::kAdd, 125, 0);
    aComposer.MixBuffer(aVars.mWorkerA).Offset(220).ExpandDebug(GTermPattern::kAdd, 225, 0);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aWorkLaneAKeyA = i + 20U;",
        "if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }",
        "aWorkLaneAByteA = aWorkLaneA[aWorkLaneAKeyA] + 25U;",
        
        "aWorkLaneAKeyB = i + 120U;",
        "if (aWorkLaneAKeyB >= S_BLOCK) { aWorkLaneAKeyB -= S_BLOCK; }",
        "aWorkLaneAByteB = aWorkLaneA[aWorkLaneAKeyB] + 125U;",
        
        "aWorkLaneAKeyC = i + 220U;",
        "if (aWorkLaneAKeyC >= S_BLOCK) { aWorkLaneAKeyC -= S_BLOCK; }",
        "aWorkLaneAByteC = aWorkLaneA[aWorkLaneAKeyC] + 225U;",
        
        "aValue = (aWorkLaneAByteA ^ aWorkLaneAByteB) ^ aWorkLaneAByteC;",
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testDoublePhaseHop {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllXor();
    aComposer.MixVariable(aVars.mCarry);
    aComposer.MixVariable(aVars.mPermute);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixBuffer(aVars.mWorkerA);
    aComposer.MixBuffer(aVars.mWorkerB);
    aComposer.Transform(aVars.mSBoxB);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aValue = aCarry ^ aPermute;",
        "aValue = aSBoxA[aValue];",
        "aValue ^= aWorkLaneA[i] ^ aWorkLaneB[i];",
        "aValue = aSBoxB[aValue];"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testDoublePhaseHopWithButter {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllXor();
    aComposer.MixVariable(aVars.mCarry).ExpandDebug(GTermPattern::kMulThenSub, 33, 21);
    aComposer.MixVariable(aVars.mPermute).ExpandDebug(GTermPattern::kRotate, 1, 0);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixBuffer(aVars.mWorkerA).Key(aVars.mValue).Offset(10);
    aComposer.MixBuffer(aVars.mWorkerB).Key(aVars.mValue).Offset(20);
    aComposer.Transform(aVars.mSBoxB);
    aComposer.MixVariable(aVars.mCarry);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aCarryByteA = (aCarry * 33U) - 21U;",
        "aPermuteByteA = RotL8(aPermute, 1U);",
        "aValue = aCarryByteA ^ aPermuteByteA;",
        "aValue = aSBoxA[aValue];",
        "aWorkLaneAKeyA = aValue + 10U;",
        "if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }",
        "aWorkLaneBKeyA = aValue + 20U;",
        "if (aWorkLaneBKeyA >= S_BLOCK) { aWorkLaneBKeyA -= S_BLOCK; }",
        "aValue ^= aWorkLaneA[aWorkLaneAKeyA] ^ aWorkLaneB[aWorkLaneBKeyA];",
        "aValue = aSBoxB[aValue];",
        "aValue ^= aCarry;"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testAnotherScenario {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    
    aComposer.MixBuffer(aVars.mSaltA).Key(aVars.mValue).Offset(5).ExpandDebug(GTermPattern::kMul, 29, 0);
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mValue).Offset(10).ExpandDebug(GTermPattern::kXor, 0xDD, 0);
    
    aComposer.Transform(aVars.mSBoxA);
    aComposer.Transform(aVars.mSBoxB);
    
    aComposer.MixBuffer(aVars.mSaltA).Key(aVars.mValue).Offset(15).ExpandDebug(GTermPattern::kSub, 20, 0);
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mValue).Offset(20).ExpandDebug(GTermPattern::kRotate, 4, 0);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aSaltAKeyA = aValue + 5U;",
        "aSaltAByteA = aSaltA[aSaltAKeyA & 0x7FU] * 29U;",
        "aSBoxAKeyA = aValue + 10U;",
        "aSBoxAByteA = aSBoxA[aSBoxAKeyA & 0xFFU] ^ 221U;",
        "aValue = aSaltAByteA + aSBoxAByteA;",
        "aValue = aSBoxA[aValue];",
        "aValue = aSBoxB[aValue];",
        "aSaltAKeyB = aValue + 15U;",
        "aSaltAByteB = aSaltA[aSaltAKeyB & 0x7FU] - 20U;",
        "aSBoxAKeyB = aValue + 20U;",
        "aSBoxAByteB = RotL8(aSBoxA[aSBoxAKeyB & 0xFFU], 4U);",
        "aValue += aSaltAByteB + aSBoxAByteB;"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testMoreBananas {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mCarry);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mSaltA).Key(aVars.mValue).Offset(5).ExpandDebug(GTermPattern::kMul, 29, 0);
    aComposer.MixBuffer(aVars.mSaltA).Key(aVars.mValue).Offset(5);
    aComposer.MixBuffer(aVars.mSaltA).ExpandDebug(GTermPattern::kMul, 29, 0);
    aComposer.MixBuffer(aVars.mSaltA);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixVariable(aVars.mCarry).ExpandDebug(GTermPattern::kRotateAdd, 1, 17);
    aComposer.Transform(aVars.mSBoxA);
    aComposer.MixVariable(aVars.mCarry).ExpandDebug(GTermPattern::kAdd, 1, 0);
    aComposer.MixVariable(aVars.mCarry).ExpandDebug(GTermPattern::kAdd, 1, 0);
    
    aComposer.Transform(aVars.mSBoxA);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aSaltAKeyA = aValue + 5U;",
        "aSaltAByteA = aSaltA[aSaltAKeyA & 0x7FU] * 29U;",
        "aSaltAKeyB = aValue + 5U;",
        "aSaltAByteB = aSaltA[i & 0x7FU] * 29U;",
        "aCarry = ((aSaltAByteA + aSaltA[aSaltAKeyB & 0x7FU]) + aSaltAByteB) + aSaltA[i & 0x7FU];",
        "aCarry = aSBoxA[aCarry];",
        "aCarryByteA = RotL8((aCarry + 17U), 1U);",
        "aCarry += aCarryByteA;",
        "aCarry = aSBoxA[aCarry];",
        "aCarryByteB = aCarry + 1U;",
        "aCarryByteC = aCarry + 1U;",
        "aCarry += aCarryByteB + aCarryByteC;",
        "aCarry = aSBoxA[aCarry];",
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testDuplicateExpandedKeyedBuffer {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    
    aComposer.MixBuffer(aVars.mWorkerA)
        .Key(aVars.mValue)
        .Offset(5)
        .ExpandDebug(GTermPattern::kAdd, 7, 0);
    
    aComposer.MixBuffer(aVars.mWorkerA)
        .Key(aVars.mValue)
        .Offset(5)
        .ExpandDebug(GTermPattern::kAdd, 7, 0);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aWorkLaneAKeyA = aValue + 5U;",
        "if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }",
        "aWorkLaneAByteA = aWorkLaneA[aWorkLaneAKeyA] + 7U;",
        "aWorkLaneAKeyB = aValue + 5U;",
        "if (aWorkLaneAKeyB >= S_BLOCK) { aWorkLaneAKeyB -= S_BLOCK; }",
        "aWorkLaneAByteB = aWorkLaneA[aWorkLaneAKeyB] + 7U;",
        "aValue = aWorkLaneAByteA + aWorkLaneAByteB;",
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
    
}

- (void)testSBoxWithLoopIndex {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    
    aComposer.MixVariable(aVars.mCarry);
    aComposer.MixBuffer(aVars.mSBoxA);

    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aValue = aCarry + aSBoxA[i & 0xFFU];",
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
    
}

- (void)testSBoxIllegal {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    
    aComposer.MixBuffer(aVars.mSBoxA);
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mCarry);
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mSBoxC);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statement should fail here\n");
        XCTFail("bake statements unexpectedly succeeded");
        return;
    }
}

- (void)testSBoxWithMixedIndixes {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mLoopIndex);
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mValue);
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mCarry);
    
    aComposer.Transform(aVars.mSBoxD).ExpandDebug(GTermPattern::kMul, 33, 0);

    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aValue = (aSBoxA[i & 0xFFU] + aSBoxA[aValue]) + aSBoxA[aCarry];",
        "aSBoxDByteA = aSBoxD[aValue] * 33U;",
        "aValue = aSBoxDByteA;",
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
    
}

- (void)testSBoxWithMixedIndixesAndMutate {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mLoopIndex);
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mValue);
    aComposer.MixBuffer(aVars.mSBoxA).Key(aVars.mCarry).ExpandDebug(GTermPattern::kMulThenAdd, 47, 211);
    
    aComposer.Transform(aVars.mSBoxD).ExpandDebug(GTermPattern::kPostRotateSub, 7, 111);
    aComposer.MixVariable(aVars.mCarry);

    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    std::vector<std::string> expected = {
        "aSBoxAByteA = (aSBoxA[aCarry] * 47U) + 211U;",
        "aValue = (aSBoxA[i & 0xFFU] + aSBoxA[aValue]) + aSBoxAByteA;",
        "aSBoxDByteA = RotL8(aSBoxD[aValue], 7U) - 111U;",
        "aValue = aSBoxDByteA;",
        "aValue += aCarry;"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
    
}

- (void)testPermuteAddAndXorCase {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);

    aComposer.ResetSetEqual(aVars.mPermute);
    aComposer.EnableDebugAddXor({false, true});

    aComposer.MixVariable(aVars.mValue);
    aComposer.MixVariable(aVars.mCarry).ExpandDebug(GTermPattern::kAdd, 12, 0);
    aComposer.MixBuffer(aVars.mSaltD).Offset(31);

    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    
    std::vector<std::string> expected = {
        "aCarryByteA = aCarry + 12U;",
        "aSaltDKeyA = i + 31U;",
        "aPermute = (aValue ^ aCarryByteA) + aSaltD[aSaltDKeyA & 0x7FU];"
    };
    
    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
    
}

- (void)testPermuteAddFoldedValueXorSalt {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);

    aComposer.ResetAddEqual(aVars.mPermute);
    aComposer.EnableDebugAddXor({false});
    aComposer.MixVariable(aVars.mValue);
    aComposer.MixBuffer(aVars.mSaltB).Offset(108);

    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }

    std::vector<std::string> expected = {
        "aSaltBKeyA = i + 108U;",
        "aPermute += aValue ^ aSaltB[aSaltBKeyA & 0x7FU];"
    };

    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testPermuteAddFoldedValueCarryXorSalt {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);

    aComposer.ResetAddEqual(aVars.mPermute);
    aComposer.EnableDebugAddXor({true, false});
    aComposer.MixVariable(aVars.mValue);
    aComposer.MixVariable(aVars.mCarry).ExpandDebug(GTermPattern::kRotate, 6, 0);
    aComposer.MixBuffer(aVars.mSaltA).Offset(19);

    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }

    std::vector<std::string> expected = {
        "aCarryByteA = RotL8(aCarry, 6U);",
        "aSaltAKeyA = i + 19U;",
        "aPermute += (aValue + aCarryByteA) ^ aSaltA[aSaltAKeyA & 0x7FU];"
    };

    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testSaltKeyWithBufferSource {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);

    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mSaltA).Offset(108).KeyWithBuffer(aVars.mWorkerA, aVars.mLoopIndex, 0);

    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }

    std::vector<std::string> expected = {
        "aSaltAKeyA = aWorkLaneA[i] + 108U;",
        "aValue = aSaltA[aSaltAKeyA & 0x7FU];"
    };

    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testSaltKeyWithBufferSourceOffset {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);

    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mSaltA).Offset(108).KeyWithBuffer(aVars.mWorkerA, aVars.mLoopIndex, 112);

    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }

    std::vector<std::string> expected = {
        "aWorkLaneAKeyA = i + 112U;",
        "if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }",
        "aSaltAKeyA = aWorkLaneA[aWorkLaneAKeyA] + 108U;",
        "aValue = aSaltA[aSaltAKeyA & 0x7FU];"
    };

    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testSaltKeyWithBufferRandomOffset {
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);

    Random::Seed(1337);
    const int aExpectedOffset = Random::Get(S_BLOCK);
    Random::Seed(1337);

    aComposer.ResetSetEqual(aVars.mValue);
    aComposer.EnableDebugMixAllAdd();
    aComposer.MixBuffer(aVars.mSaltA).Offset(108).KeyWithBufferRandomOffset(aVars.mWorkerA, aVars.mLoopIndex);

    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }

    std::vector<std::string> expected = {
        "aWorkLaneAKeyA = i + " + std::to_string(aExpectedOffset) + "U;",
        "if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }",
        "aSaltAKeyA = aWorkLaneA[aWorkLaneAKeyA] + 108U;",
        "aValue = aSaltA[aSaltAKeyA & 0x7FU];"
    };

    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}



@end
