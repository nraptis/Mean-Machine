//
//  CornTesting.m
//  CornTesting
//
//  Created by Magneto on 4/20/26.
//

#import <XCTest/XCTest.h>
#include <vector>
#include "SBoxTables.hpp"
#include "TwistWorkSpace.hpp"
#include "TwistSeedBuilder.hpp"
#include "TwistSeeder.hpp"
#include "GStatementRecipe.hpp"

@interface HelloQuickMatch : XCTestCase

@end

@implementation HelloQuickMatch


- (void)fillFakePassword: (std::uint8_t *)buffer {
    
    
    std::uint8_t junk1[8] = { 0x65, 0x70, 0x62, 0x78, 0x81, 0x73, 0x65, 0x77 };
    
    std::vector<std::uint8_t> aSBox1 = SBoxTables::GetTestA();
    std::vector<std::uint8_t> aSBox2 = SBoxTables::GetTestA();
    std::vector<std::uint8_t> aSBox3 = SBoxTables::GetTestA();
    std::vector<std::uint8_t> aSBox4 = SBoxTables::GetTestA();
    
    
    int aIndex = 0;
    int aSample = 0;
    
    while (aIndex < S_BLOCK) {
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < 8)) { buffer[aIndex++] = junk1[aSample]; }
        
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < 2)) { buffer[aIndex++] = 0; }
        
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < S_SBOX)) { buffer[aIndex++] = aSBox1[aSample] ^ aSBox2[aSample]; }
        
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < 2)) { buffer[aIndex++] = 0; }
        
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < S_SBOX)) { buffer[aIndex++] = aSBox2[aSample] ^ aSBox3[aSample]; }
        
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < 2)) { buffer[aIndex++] = 0; }
        
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < S_SBOX)) { buffer[aIndex++] = aSBox3[aSample] ^ aSBox4[aSample]; }
        
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < 2)) { buffer[aIndex++] = 0; }
        
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < S_SBOX)) { buffer[aIndex++] = aSBox4[aSample] ^ aSBox1[aSample]; }
        
        aSample = 0;
        while ((aIndex < S_BLOCK) && (aSample < 2)) { buffer[aIndex++] = 0; }
    }
}

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testOriginalConceptLoop {
    /*
    XCTSkip(@"Draft scaffold: keeping this test parked while the runner/export framework settles.");
    
    std::vector<std::uint8_t> aSBox1 = SBoxTables::GetTestA();
    
    std::uint8_t aSource[S_BLOCK];
    [self fillFakePassword:aSource];
    
    std::uint8_t aDestA[S_BLOCK];
    std::uint8_t aDestB[S_BLOCK];
    
    std::uint64_t aState = 9001; // over 9000
    std::uint64_t aValue, aMix;
    
    for (std::uint64_t aLoop=0; aLoop<S_BLOCK; aLoop++) {
        aMix = aState ^ aSource[aLoop];
        aValue = aSBox1[aMix & 0xFF];
        aState = aValue;
        aDestA[aLoop] = aValue;
    }
    
    for (std::uint64_t aLoop=0; aLoop<100; aLoop++) {
        int aVal = aDestA[aLoop];
        printf("val[%d] = %d\n", (int)aLoop, aVal);
    }
    
    printf("we done.");
    
    GBatch aBatch = TwistSeedBuilder::BuildBaselineBatch();
    
    TwistWorkSpace aWorkSpace;
    aWorkSpace.mDest = aDestB;
    
    TwistSeeder aTwistSeeder; // This should not be the base class of twist seeder, this should be like GTwistSeeder, which can run generator objects.
    // can generate with GBatch? we only need some loose rigging, no final solution
    
    aTwistSeeder.Seed(&aWorkSpace, aSource);
    
    for (std::uint64_t aLoop=0; aLoop<S_BLOCK; aLoop++) {
        if (aDestA[aLoop] != aDestB[aLoop]) {
            printf("testOriginalConceptLoop mismatch on index %llu, expected %x got %x\n", aLoop, (int)aDestA[aLoop], (int)aDestB[aLoop]);
            XCTFail("testOriginalConceptLoop fails");
            return;
        }
    }
    */
}

- (void)testConcept {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    
    const GSymbol aLoopIndex = VarSymbol("loop");
    const GSymbol aSourceBase = BufSymbol(TwistWorkSpaceSlot::kSource);
    const GExpr aSource = GExpr::Read(aSourceBase, GExpr::Symbol(aLoopIndex));
    
    const GSymbol aState = VarSymbol("state");
    const GSymbol aCarry = VarSymbol("carry");
    const GSymbol aMix = VarSymbol("mix");
    
    GStatementRecipe aRecipeSetMix;
    aRecipeSetMix.Add(aSource, 100); // must use
    aRecipeSetMix.Add(aState, 100); // must use
    aRecipeSetMix.Add(aCarry, 50); // must use
    
    
    
    // We make 50% chance of each.
    aRecipeSetMix.ClearOpWeights(aSource);
    aRecipeSetMix.SetOpWeight(aState, GOperType::kAdd, 100);
    aRecipeSetMix.SetOpWeight(aState, GOperType::kXor, 100);
    
    // Then, in our case, this rule kicks in. Saying we cannot have (source + state)
    // So, the only option left is (source ^ state)
    aRecipeSetMix.SetOpPairDisallow(aSource, aState, GOperType::kAdd);
    
    aRecipeSetMix.ClearOpWeights(aCarry);
    aRecipeSetMix.SetOpWeight(aCarry, GOperType::kMul, 100);
    
    GStatement aMixSt;
    std::string aErrorString;
    
    if (!aRecipeSetMix.Bake(aMix,
                            aMixSt,
                            aScopeRules,
                            aScopeStateGlobal,
                            aScopeStateLocal,
                            aPool,
                            aErrorString)) {
        printf("bake error: %s\n", aErrorString.c_str());
        XCTFail("{mix statement} failed to bake.");
        return;
    }
    
    aScopeStateLocal.Consume(aMixSt);
    
    if (aMixSt.HasExprSymbol(0) == false) {
        XCTFail("{mix statement} Expected symbol 0");
        return;
    }
    if (aSourceBase != aMixSt.GetExprSymbol(0)) {
        XCTFail("{mix statement} Expected symbol 0 was source base");
        return;
    }
    
    if (aMixSt.HasExprSymbol(1) == false) {
        XCTFail("{mix statement} Expected symbol 1");
        return;
    }
    if (aLoopIndex != aMixSt.GetExprSymbol(1)) {
        XCTFail("{mix statement} Expected symbol 1 was loop index");
        return;
    }
    
    if (aMixSt.HasExprSymbol(2) == false) {
        XCTFail("{mix statement} Expected symbol 2");
        return;
    }
    
    if (aState != aMixSt.GetExprSymbol(2)) {
        XCTFail("{mix statement} Expected symbol 2 was state");
        return;
    }
    
    if (aMixSt.HasExprOper(0) == false) {
        XCTFail("{mix statement} Expected oper 0");
        return;
    }
    
    if (aMixSt.GetExprOper(0) != GOperType::kRead) {
        XCTFail("{mix statement} Expected oper 0 was read");
        return;
    }
    
    if (aMixSt.HasExprOper(1) == false) {
        XCTFail("{mix statement} Expected oper 1");
        return;
    }
    
    if (aMixSt.GetExprOper(1) != GOperType::kXor) {
        XCTFail("{mix statement} Expected oper 1 was xor");
        return;
    }
    
    
    // If we have * carry
    if (aMixSt.HasExprSymbol(3)) {
        if (aMixSt.GetExprSymbol(3) != aCarry) {
            XCTFail("{mix statement} a Expected symbol 3 was carry");
            return;
        }
        
        if (aMixSt.HasExprSymbol(4)) {
            XCTFail("{mix statement} a Trailing symbol not expected");
            return;
        }
        
        if (aMixSt.GetExprOper(3) != GOperType::kInv) {
            XCTFail("{mix statement} a we should have invalid trailing oper");
            return;
        }
        
        if (aMixSt.GetExprSymbol(4).IsInvalid() == false) {
            XCTFail("{mix statement} a Expected symbol 4 was invalid");
            return;
        }
        
    } else {
        if (aMixSt.GetExprOper(2) != GOperType::kInv) {
            XCTFail("{mix statement} b we did not use carry, got a trailing oper");
            return;
        }
        
        if (aMixSt.GetExprSymbol(3).IsInvalid() == false) {
            XCTFail("{mix statement} b Expected symbol 3 was invalid");
            return;
        }
    }
    
    
    
    if (aMixSt.HasAssignOper(0) == true) {
        XCTFail("{mix statement} Expected no assign oper 0");
        return;
    }
    if (aMixSt.HasAssignSymbol(0) == false) {
        XCTFail("{mix statement} Expected to have assign symbol 0");
        return;
    }
    if (aMix != aMixSt.GetAssignSymbol(0)) {
        XCTFail("{mix statement} Expected assign symbol 0 was mix");
        return;
    }
    
    
    
    if (aMixSt.HasAssignSymbol(1) != false) {
        XCTFail("{mix statement} Expected not to have assign symbol 1");
        return;
    }
    if (aMixSt.GetAssignSymbol(1).IsInvalid() == false) {
        XCTFail("{mix statement} Expected assign symbol 1 was invalid");
        return;
    }
    
}

- (void)testProbabilityHasInfluence {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    
    const GSymbol aTarget = VarSymbol("target");
    
    const GSymbol aAlways = VarSymbol("always");
    const GSymbol aMaybe1 = VarSymbol("maybe_1");
    const GSymbol aMaybe2 = VarSymbol("maybe_2");
    
    
    bool aMaybe1_True = false;
    bool aMaybe1_False = false;
    
    bool aMaybe2_True = false;
    bool aMaybe2_False = false;
    
    
    
    for (int i=0;i<10000;i++) {
        
        aScopeStateLocal.Clear();
        
        GStatementRecipe aRecipeSetMix;
        aRecipeSetMix.Add(aAlways, 100); // must use
        aRecipeSetMix.Add(aMaybe1, 50); // 50%
        aRecipeSetMix.Add(aMaybe2, 50); // 50%
        
        GStatement aTargetSt;
        
        std::string aErrorString;
        if (!aRecipeSetMix.Bake(aTarget,
                                aTargetSt,
                                aScopeRules,
                                aScopeStateGlobal,
                                aScopeStateLocal,
                                aPool,
                                aErrorString)) {
            printf("bake error: %s\n", aErrorString.c_str());
            XCTFail("{mix statement} failed to bake.");
            return;
        }
        
        if (!aTargetSt.HasExprSymbol(aAlways)) {
            XCTFail("{mix statement} always there symbol was missing");
            return;
        }
        if (!aTargetSt.HasAssignSymbol(aTarget)) {
            XCTFail("{mix statement} target assign symbol was missing");
            return;
        }
        if (aTargetSt.HasAssignSymbol(aMaybe1)) {
            XCTFail("{mix statement} target assign symbol had invalid maybe symbol, should be only in expr");
            return;
        }
        if (aTargetSt.HasAssignSymbol(aMaybe2)) {
            XCTFail("{mix statement} target assign symbol had invalid maybe symbol, should be only in expr");
            return;
        }
        
        
        if (aTargetSt.HasExprSymbol(aMaybe1)) {
            aMaybe1_True = true;
        } else {
            aMaybe1_False = true;
        }
        
        if (aTargetSt.HasExprSymbol(aMaybe2)) {
            aMaybe2_True = true;
        } else {
            aMaybe2_False = true;
        }
        
        if (aMaybe1_True && aMaybe1_False && aMaybe2_True && aMaybe2_False) {
            break;
        }
        
        
    }
    
    if (aMaybe1_True && aMaybe1_False && aMaybe2_True && aMaybe2_False) {
        
    } else {
        XCTFail("{mix statement} The 'maybe 1' and 'maybe 2' did not get both within 10000 trials.");
        return;
    }
    
    // We would update state global after loop is baked.
    
}

- (void)testTieBreaker {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    
    const GSymbol aLoopIndex = VarSymbol("loop");
    const GSymbol aSourceBase = BufSymbol(TwistWorkSpaceSlot::kSource);
    const GExpr aSource = GExpr::Read(aSourceBase, GExpr::Symbol(aLoopIndex));
    
    const GSymbol aDoubleStep = VarSymbol("stepper");
    
    const GSymbol aCarryA = VarSymbol("carry_a");
    const GSymbol aCarryB = VarSymbol("carry_b");
    const GSymbol aCarryC = VarSymbol("carry_c");
    
    
    aPool.Add(aCarryA, "carry", 0);
    aPool.Add(aCarryB, "carry", 0);
    aPool.Add(aCarryC, "carry", 0);
    
    // We make it seem like the world consumed carry a
    aScopeRules.SetReadPreferredMaximum(aCarryA, 1);
    aScopeStateGlobal.Consume(aCarryA);
    
    bool aGotB0 = false;
    bool aGotB1 = false;
    
    bool aGotC0 = false;
    bool aGotC1 = false;
    
    
    
    for (int i=0;i<10000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        std::vector<GStatementSlot> aFetchedCarries;
        std::string aErrorString;
        if (!aPool.FetchSlots("carry", 2, aFetchedCarries, aScopeStateLocalClone, aScopeStateGlobalClone, aErrorString)) {
            printf("fetch error: %s\n", aErrorString.c_str());
            XCTFail("{fetch carries} failed to fetch.");
            return;
        }
        
        if (aFetchedCarries.size() != 2) {
            XCTFail("{fetch carries} shoulda fetch 2 carries.");
            return;
        }
        
        if (!(aFetchedCarries[0].mType == GStatementSlotType::kSymbol)) {
            XCTFail("{fetch carries} shoulda fetch symbol carry 0.");
            return;
        }
        
        if (!(aFetchedCarries[1].mType == GStatementSlotType::kSymbol)) {
            XCTFail("{fetch carries} shoulda fetch symbol carry 1.");
            return;
        }
        
        if (aFetchedCarries[0].mSymbol == aCarryB) {
            if (aFetchedCarries[1].mSymbol != aCarryC) {
                XCTFail("{fetch carries} got carry b, but not carry c");
                return;
            }
            aGotB0 = true;
            
        } else if (aFetchedCarries[0].mSymbol == aCarryC) {
            if (aFetchedCarries[1].mSymbol != aCarryB) {
                XCTFail("{fetch carries} got carry c, but not carry b");
                return;
            }
            
        } else {
            XCTFail("{fetch carries} should only have fetches carries b and c.");
            return;
        }
        
        
        GStatementRecipe aRecipeTarget;
        aRecipeTarget.Add(aFetchedCarries[0], 100); // must use
        aRecipeTarget.Add(aFetchedCarries[1], 100); // must use
        
        GStatement aStepSt;
        
        if (!aRecipeTarget.Bake(aDoubleStep,
                                aStepSt,
                                aScopeRules,
                                aScopeStateGlobalClone,
                                aScopeStateLocalClone,
                                aPool,
                                aErrorString)) {
            printf("bake error: %s\n", aErrorString.c_str());
            XCTFail("{step statement} failed to bake.");
            return;
        }
        
        aScopeStateLocalClone.Consume(aStepSt);
        
        
        if (aStepSt.HasExprSymbol(aCarryA) != false) {
            XCTFail("{step statement} expected to not have carry a");
            return;
        }
        
        if (aStepSt.HasExprSymbol(aCarryB) == false) {
            XCTFail("{step statement} expected to have carry b");
            return;
        }
        
        if (aStepSt.HasExprSymbol(aCarryC) == false) {
            XCTFail("{step statement} expected to have carry c");
            return;
        }
        
        if (aStepSt.GetExprSymbol(0) == aCarryB) {
            aGotB0 = true;
        }
        if (aStepSt.GetExprSymbol(1) == aCarryB) {
            aGotB1 = true;
        }
        
        if (aStepSt.GetExprSymbol(0) == aCarryC) {
            aGotC0 = true;
        }
        if (aStepSt.GetExprSymbol(1) == aCarryC) {
            aGotC1 = true;
        }
        
        if (aGotB0 && aGotB1 && aGotC0 && aGotC1) {
            break;
        }
    }
    
    
    if (aGotB0 && aGotB1 && aGotC0 && aGotC1) {
        
    } else {
        XCTFail("{step statement} the variability of the pool did not work.");
        return;
    }
    
    // We would update state global after loop is baked.
    
}

@end
