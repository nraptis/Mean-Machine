//
//  HelloArithmeticExpansion.m
//  CornTesting
//
//  Created by Magneto on 4/22/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include <vector>
#include "SBoxTables.hpp"
#include "TwistWorkSpace.hpp"
#include "TwistSeedBuilder.hpp"
#include "TwistSeeder.hpp"
#include "GStatementRecipe.hpp"
#include "TwistFunctional.hpp"
#include "Random.hpp"

@interface HelloArithmeticExpansion : XCTestCase

@end

@implementation HelloArithmeticExpansion


- (void)testOutPatterns {
    
    
    // Core patterns:
    /*
     a + s1
     a - s1
     a ^ s1
     a * s1                  // odd
     rotl8(a, s1)
     
     (a * s1) + s2           // odd s1
     (a * s1) - s2           // odd s1
     (a * s1) ^ s2           // odd s1
     
     rotl8(a + s1, s2)
     rotl8(a - s1, s2)
     rotl8(a ^ s1, s2)
     rotl8(a * s1, s2)       // odd s1
     
     rotl8(a, s2) + s1
     rotl8(a, s2) - s1
     rotl8(a, s2) ^ s1
     rotl8(a, s2) * s1
     */
    
}


- (void)testSomeOperatorStuff {
    
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
        
        /*
         
         I want to tell aRecipeSetMix
         
         With probability @ 75 (meaning 75/100 times)
         
         With operands (+, *, rotl8)
         
         At relative likelihoods (45, 40, 15) [note: this is *not* the thing we already have]
         
         and value ranges (1-255, 2-63, 1-7)
         
         to transform "aAlways", for example into
         
         (aAlways + 17) or (aAlways rotl8 5) or (aAlways * 3)
         
         What I want is: propose an API, but do not implement it.
         
         It seems like it needs to be bundles with Add, so we can do 2 ways for same variable, e.g.
         
         (source rotl8 3) ^ (source + 15)
         
         however, that isn't 'top prioity'
         
         we probably want to turn this into 3 or 4 total pre-baked choices.
         
         i'm sure we want to exclude some values, that may be cryptographically weak, which you probably know
         
         categories that come to mind:
         
         just rotate
         
         
         
            mix = ((source[i] * 33) ^ (source[i - 1]) ^ state + (salt[i] * carry)
            value = s_box_a[mix % 255]
            state = value

            carry ^= (value rotl8 5) + s_box_b[i]
            carry = s_box_a[carry]
         
         
         
        */
        
        aRecipeSetMix.Add(aAlways, 100);
        aRecipeSetMix.Add(aMaybe1, 50);
        aRecipeSetMix.Add(aMaybe2, 50);
        
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


@end
