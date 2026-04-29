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
        "aWorkLaneAKeyA &= 0x1FFFU;",
        "aWorkLaneAKeyB = aValue + 432U;",
        "aWorkLaneAKeyB &= 0x1FFFU;",
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
        "aWorkLaneAKeyA &= 0x1FFFU;",
        "aValue = aWorkLaneA[aWorkLaneAKeyA];"
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
        "aWorkLaneAKeyA &= 0x1FFFU;",
        "aWorkLaneAByteA = aWorkLaneA[aWorkLaneAKeyA] + 25U;",
        
        "aWorkLaneAKeyB = i + 120U;",
        "aWorkLaneAKeyB &= 0x1FFFU;",
        "aWorkLaneAByteB = aWorkLaneA[aWorkLaneAKeyB] + 125U;",
        
        "aWorkLaneAKeyC = i + 220U;",
        "aWorkLaneAKeyC &= 0x1FFFU;",
        "aWorkLaneAByteC = aWorkLaneA[aWorkLaneAKeyC] + 225U;",
        
        "aValue = (aWorkLaneAByteA ^ aWorkLaneAByteB) ^ aWorkLaneAByteC;",
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
        "aWorkLaneAKeyA &= 0x1FFFU;",
        "aWorkLaneAByteA = aWorkLaneA[aWorkLaneAKeyA] + 7U;",
        "aWorkLaneAKeyB = aValue + 5U;",
        "aWorkLaneAKeyB &= 0x1FFFU;",
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
        "aWorkLaneAKeyA &= 0x1FFFU;",
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
        "aWorkLaneAKeyA &= 0x1FFFU;",
        "aSaltAKeyA = aWorkLaneA[aWorkLaneAKeyA] + 108U;",
        "aValue = aSaltA[aSaltAKeyA & 0x7FU];"
    };

    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

- (void)testQuic {
    
    Varz aVars;
    GLoopFragmentComposer aComposer(aVars.mLoopIndex);
    
    aComposer.ResetAddEqual(aVars.mValue);
    aComposer.MixBuffer(aVars.mSaltA).Offset(100);
    aComposer.MixVariable(aVars.mCarry).ExpandDebug(GTermPattern::kMul, 33, 0);
    
    std::vector<GStatement> aStatements;
    std::string err;
    if (!aComposer.BakeStatements(&aStatements, &err)) {
        printf("bake statements failed: %s\n", err.c_str());
        XCTFail("bake statements failed");
        return;
    }

    std::vector<std::string> expected = {
        "aWorkLaneAKeyA = i + " + std::to_string(111) + "U;",
        "aWorkLaneAKeyA &= 0x1FFFU;",
        "aSaltAKeyA = aWorkLaneA[aWorkLaneAKeyA] + 108U;",
        "aValue = aSaltA[aSaltAKeyA & 0x7FU];"
    };

    if (!StatementChecker::Eval(aStatements, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}

@end
