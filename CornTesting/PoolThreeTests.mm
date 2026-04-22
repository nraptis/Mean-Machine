//
//  PoolThreeTests.m
//  CornTesting
//
//  Created by Magneto on 4/22/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include <vector>
#include "TwistWorkSpace.hpp"
#include "TwistSeedBuilder.hpp"
#include "TwistSeeder.hpp"
#include "GStatementRecipe.hpp"
#include "PoolEval.hpp"

@interface PoolThreeTests : XCTestCase

@end

@implementation PoolThreeTests

- (void)testThreePoolHello {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    
    aPool.Add(a, "cat", 10, 2);
    aPool.Add(b, "cat", 10, 1);
    aPool.Add(c, "cat", 10, 2);
    
    bool aPassRound = false;
    
    std::vector<bool> aAchieveA = {};
    std::vector<bool> aAchieveB = {};
    std::vector<bool> aAchieveC = {};
    
    PoolEval::ResetThree(aAchieveA, aAchieveB, aAchieveC);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         a,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        bool aHardFailure = false;
        if (PoolEval::UpdateThree(1, 2, aCountA,
                                  0, 1, aCountB,
                                  0, 2, aCountC,
                                  aAchieveA,
                                  aAchieveB,
                                  aAchieveC, 1, 4, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario a.");
            return;
        }
    }
    
    if (aPassRound == false) {
        XCTFail("{mini scenarios} failed scenario a.");
        return;
    }
}

- (void)testThreeExhaustA {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    
    
    for (int aFetchMin=0;aFetchMin<4;aFetchMin++) {
        for (int aFetchMax=aFetchMin;aFetchMax<8;aFetchMax++) {
            for (int aReadMaxA=0;aReadMaxA<4;aReadMaxA++) {
                //for (int aDupesA=1;aDupesA<4;aDupesA++) {
                for (int aDupesA=0;aDupesA<4;aDupesA++) {
                
                    for (int aRemoveLocalA=0;aRemoveLocalA<4;aRemoveLocalA++) {
                        for (int aRemoveGlobalA=0;aRemoveGlobalA<4;aRemoveGlobalA++) {
                            
                            
                            
                            GPool aPool(&aScopeRules, &aScopeStateGlobal);
                            const GSymbol a = VarSymbol("a");
                            
                            aScopeRules.SetReadPreferredMaximum(a, aReadMaxA);
                            
                            aPool.Add(a, "cat", 10, aDupesA);
                            
                            bool aPassRound = false;
                            
                            std::vector<bool> aAchieveA = {};
                            std::vector<bool> aAchieveB = {};
                            std::vector<bool> aAchieveC = {};
                            
                            const int aDefaultMaximumA = std::max(1, aDupesA);
                            const int aRuleMaximumA = (aReadMaxA > 0) ? aReadMaxA : aDefaultMaximumA;
                            const int aRangeMaximumA = std::max(0, std::min(aDefaultMaximumA, aRuleMaximumA));
                            const int aPhysicalRemainingA = std::max(0, aDefaultMaximumA - aRemoveLocalA);
                            const int aHistoricalDrawCountA = aRemoveLocalA + aRemoveGlobalA;
                            const int aSoftRemainingA = std::max(0, aRangeMaximumA - aHistoricalDrawCountA);
                            const int aGoodCountA = std::min(aPhysicalRemainingA, aSoftRemainingA);
                            
                            bool aIsExpectedToFail = (aPhysicalRemainingA < aFetchMin);
                            int aFetchMaxAdjustedA = aFetchMin;
                            if (!aIsExpectedToFail) {
                                aFetchMaxAdjustedA = (aGoodCountA < aFetchMin)
                                    ? aFetchMin
                                    : std::min(aFetchMax, aGoodCountA);
                            }
                            
                            printf("Fetch = [%d|%d]  aIsExpectedToFail = %d [aReadMaxA = %d, aDupesA = %d] Fetch[%d to %d] RMV [L:%d G:%d]\n", aFetchMin, aFetchMax, aIsExpectedToFail, aReadMaxA, aDupesA, aFetchMin, aFetchMax, aRemoveLocalA, aRemoveGlobalA);
                            
                            
                            PoolEval::ResetThree(aAchieveA, aAchieveB, aAchieveC);
                            aPassRound = false;
                            for (int i=0;i<100;i++) {
                                GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
                                GScopeState aScopeStateLocalClone = aScopeStateLocal;
                                
                                for (int k=0;k<aRemoveLocalA;k++) {
                                    aScopeStateLocalClone.Consume(a);
                                }
                                
                                for (int k=0;k<aRemoveGlobalA;k++) {
                                    aScopeStateGlobalClone.Consume(a);
                                }
                                
                                
                                std::vector<GStatementSlot> aSlots;
                                std::string aErrorString;
                                if (!aPool.FetchSlots("cat",
                                                      aFetchMin,
                                                      aFetchMax,
                                                      aSlots,
                                                      aScopeStateLocalClone,
                                                      aScopeStateGlobalClone,
                                                      aErrorString)) {
                                    if (aIsExpectedToFail == false) {
                                        XCTFail("{exhaust a} failed fetch slots, was not expected to fail.");
                                        return;
                                    }
                                } else {
                                    
                                    int aCountA = PoolEval::Count(aSlots, a);
                                    int aCountB = 0;
                                    int aCountC = 0;
                                    
                                    bool aHardFailure = false;
                                    if (PoolEval::UpdateThree(aFetchMin, aFetchMaxAdjustedA, aCountA,
                                                              0, 0, aCountB,
                                                              0, 0, aCountC,
                                                              aAchieveA,
                                                              aAchieveB,
                                                              aAchieveC,
                                                              
                                                              aFetchMin,
                                                              aFetchMaxAdjustedA,
                                                              aHardFailure)) {
                                        aPassRound = true;
                                        break;
                                    }
                                    if (aHardFailure) {
                                        XCTFail("{mini scenarios} failed scenario a.");
                                        return;
                                    }
                                    
                                }
                            }
                            
                            if (aIsExpectedToFail == false) {
                                
                                if (aPassRound == false) {
                                    XCTFail("{mini scenarios} failed scenario a.");
                                    return;
                                }
                            }
                            
                        }
                    }
                }
            }
        }
    }
}


@end
