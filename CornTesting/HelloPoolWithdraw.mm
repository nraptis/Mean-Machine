//
//  HelloPoolWithdraw.m
//  CornTesting
//
//  Created by Magneto on 4/21/26.
//

#import <XCTest/XCTest.h>
#include <vector>
#include "TwistWorkSpace.hpp"
#include "TwistSeedBuilder.hpp"
#include "TwistSeeder.hpp"
#include "GStatementRecipe.hpp"
#include "PoolEval.hpp"

@interface HelloPoolWithdraw : XCTestCase

@end

@implementation HelloPoolWithdraw

- (void)testPoolVotesSimpleSymbol {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    const GSymbol d = VarSymbol("d");
    
    aScopeStateGlobal.Consume(a);
    
    aPool.Add(a, "cat", 10);
    aPool.Add(b, "cat", 10, 2);
    aPool.Add(c, "cat", 10, 2);
    aPool.Add(d, "cat", 10);
    
    bool aGot_B1_C0 = false;
    bool aGot_B2_C0 = false;
    
    bool aGot_B0_C1 = false;
    bool aGot_B0_C2 = false;
    
    bool aGot_B1_C1 = false;
    
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         2,
                         3,
                         d,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        if (PoolEval::Count(aSlots, a) != 0) {
            XCTFail("{pool exclusion rules} a expected not exist.");
            return;
        }
        
        if (PoolEval::Count(aSlots, d) != 1) {
            XCTFail("{pool exclusion rules} d expected exist one.");
            return;
        }
        
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        if (aCountB == 0 && aCountC == 0) {
            XCTFail("{pool exclusion rules} there should be a b or c.");
            return;
        }
        
        if (aCountB > 2 || aCountC > 2) {
            XCTFail("{pool exclusion rules} there should not be more than 2 b or c in this scenario.");
            return;
        }
        
        if (aCountB == 1 && aCountC == 0) { aGot_B1_C0 = true; }
        if (aCountB == 2 && aCountC == 0) { aGot_B2_C0 = true; }
        if (aCountB == 0 && aCountC == 1) { aGot_B0_C1 = true; }
        if (aCountB == 0 && aCountC == 2) { aGot_B0_C2 = true; }
        if (aCountB == 1 && aCountC == 1) { aGot_B1_C1 = true; }
        
        if (aGot_B1_C0 && aGot_B2_C0 && aGot_B0_C1 && aGot_B0_C2 && aGot_B1_C1) {
            break;
        }
        
        
    }
    
    if (aGot_B1_C0 && aGot_B2_C0 && aGot_B0_C1 && aGot_B0_C2 && aGot_B1_C1) {
        
    } else {
        XCTFail("{pool exclusion rules} we did not hit all the possible answers in 10,000 tries.");
        return;
    }
}

- (void)testPoolVotesSimpleExpr {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    
    const GSymbol s = VarSymbol("s");
    const GSymbol t = VarSymbol("t");
    
    const GExpr se = GExpr::Symbol(s);
    const GExpr te = GExpr::Symbol(t);
    
    const GExpr a = GExpr::Add(se, te);
    const GExpr b = GExpr::Sub(se, te);
    const GExpr c = GExpr::Add(te, se);
    const GExpr d = GExpr::Sub(te, se);
    
    aScopeStateGlobal.Consume(a);
    
    aPool.Add(a, "cat", 10);
    aPool.Add(b, "cat", 10, 2);
    aPool.Add(c, "cat", 10, 2);
    aPool.Add(d, "cat", 10);
    
    bool aGot_B1_C0 = false;
    bool aGot_B2_C0 = false;
    
    bool aGot_B0_C1 = false;
    bool aGot_B0_C2 = false;
    
    bool aGot_B1_C1 = false;
    
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         2,
                         3,
                         d,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        if (PoolEval::Count(aSlots, a) != 0) {
            XCTFail("{pool exclusion rules} a expected not exist.");
            return;
        }
        
        if (PoolEval::Count(aSlots, d) != 1) {
            XCTFail("{pool exclusion rules} d expected exist one.");
            return;
        }
        
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        if (aCountB == 0 && aCountC == 0) {
            XCTFail("{pool exclusion rules} there should be a b or c.");
            return;
        }
        
        if (aCountB > 2 || aCountC > 2) {
            XCTFail("{pool exclusion rules} there should not be more than 2 b or c in this scenario.");
            return;
        }
        
        if (aCountB == 1 && aCountC == 0) { aGot_B1_C0 = true; }
        if (aCountB == 2 && aCountC == 0) { aGot_B2_C0 = true; }
        if (aCountB == 0 && aCountC == 1) { aGot_B0_C1 = true; }
        if (aCountB == 0 && aCountC == 2) { aGot_B0_C2 = true; }
        if (aCountB == 1 && aCountC == 1) { aGot_B1_C1 = true; }
        
        if (aGot_B1_C0 && aGot_B2_C0 && aGot_B0_C1 && aGot_B0_C2 && aGot_B1_C1) {
            break;
        }
        
        
    }
    
    if (aGot_B1_C0 && aGot_B2_C0 && aGot_B0_C1 && aGot_B0_C2 && aGot_B1_C1) {
        
    } else {
        XCTFail("{pool exclusion rules} we did not hit all the possible answers in 10,000 tries.");
        return;
    }
    
}

- (void)testPoolVotesSimpleSymbol_LocalB {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    const GSymbol d = VarSymbol("d");
    
    aScopeStateGlobal.Consume(a);
    
    aPool.Add(a, "cat", 10);
    aPool.Add(b, "cat", 10, 2);
    aPool.Add(c, "cat", 10, 2);
    aPool.Add(d, "cat", 10);
    
    bool aGot_B1_C0 = false;
    bool aGot_B0_C1 = false;
    bool aGot_B0_C2 = false;
    bool aGot_B1_C1 = false;
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateLocalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         2,
                         3,
                         d,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        if (PoolEval::Count(aSlots, a) != 0) {
            XCTFail("{pool exclusion rules} a expected not exist.");
            return;
        }
        
        if (PoolEval::Count(aSlots, d) != 1) {
            XCTFail("{pool exclusion rules} d expected exist one.");
            return;
        }
        
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        if (aCountB == 0 && aCountC == 0) {
            XCTFail("{pool exclusion rules} there should be a b or c.");
            return;
        }
        
        if (aCountB > 1 || aCountC > 2) {
            XCTFail("{pool exclusion rules} there should not be more than 1 b or 2 c in this scenario.");
            return;
        }
        
        if (aCountB == 1 && aCountC == 0) { aGot_B1_C0 = true; }
        if (aCountB == 0 && aCountC == 1) { aGot_B0_C1 = true; }
        if (aCountB == 0 && aCountC == 2) { aGot_B0_C2 = true; }
        if (aCountB == 1 && aCountC == 1) { aGot_B1_C1 = true; }
        
        if (aGot_B1_C0 && aGot_B0_C1 && aGot_B0_C2 && aGot_B1_C1) {
            break;
        }
    }
    
    if (aGot_B1_C0 && aGot_B0_C1 && aGot_B0_C2 && aGot_B1_C1) {
        
    } else {
        return;
    }
}

- (void)testPoolVotesSimpleSymbol_LocalC {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    const GSymbol d = VarSymbol("d");
    
    aScopeStateGlobal.Consume(a);
    
    aPool.Add(a, "cat", 10);
    aPool.Add(b, "cat", 10, 2);
    aPool.Add(c, "cat", 10, 2);
    aPool.Add(d, "cat", 10);
    
    bool aGot_B1_C0 = false;
    bool aGot_B2_C0 = false;
    
    bool aGot_B0_C1 = false;
    
    bool aGot_B1_C1 = false;
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateLocalClone.Consume(c);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         2,
                         3,
                         d,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        if (PoolEval::Count(aSlots, a) != 0) {
            XCTFail("{pool exclusion rules} a expected not exist.");
            return;
        }
        
        if (PoolEval::Count(aSlots, d) != 1) {
            XCTFail("{pool exclusion rules} d expected exist one.");
            return;
        }
        
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        if (aCountB == 0 && aCountC == 0) {
            XCTFail("{pool exclusion rules} there should be a b or c.");
            return;
        }
        
        if (aCountB > 2 || aCountC > 1) {
            XCTFail("{pool exclusion rules} there should not be more than 2 b or 1 c in this scenario.");
            return;
        }
        
        if (aCountB == 1 && aCountC == 0) { aGot_B1_C0 = true; }
        if (aCountB == 2 && aCountC == 0) { aGot_B2_C0 = true; }
        if (aCountB == 0 && aCountC == 1) { aGot_B0_C1 = true; }
        if (aCountB == 1 && aCountC == 1) { aGot_B1_C1 = true; }
        
        if (aGot_B1_C0 && aGot_B2_C0 && aGot_B0_C1 && aGot_B1_C1) {
            break;
        }
    }
    
    if (aGot_B1_C0 && aGot_B2_C0 && aGot_B0_C1 && aGot_B1_C1) {
        
    } else {
        XCTFail("{pool exclusion rules} we did not hit all the possible answers in 10,000 tries.");
        return;
    }
    
}

- (void)testPoolVotesSimpleSymbol_GlobalB {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    const GSymbol d = VarSymbol("d");
    
    aScopeStateGlobal.Consume(a);
    
    aPool.Add(a, "cat", 10);
    aPool.Add(b, "cat", 10, 2);
    aPool.Add(c, "cat", 10, 2);
    aPool.Add(d, "cat", 10);
    
    bool aGot_B1_C0 = false;
    
    bool aGot_B0_C1 = false;
    bool aGot_B0_C2 = false;
    
    bool aGot_B1_C1 = false;
    
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         2,
                         3,
                         d,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        if (PoolEval::Count(aSlots, a) != 0) {
            XCTFail("{pool exclusion rules} a expected not exist.");
            return;
        }
        
        if (PoolEval::Count(aSlots, d) != 1) {
            XCTFail("{pool exclusion rules} d expected exist one.");
            return;
        }
        
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        if (aCountB == 0 && aCountC == 0) {
            XCTFail("{pool exclusion rules} there should be a b or c.");
            return;
        }
        
        if (aCountB > 1 || aCountC > 2) {
            XCTFail("{pool exclusion rules} there should not be more than 2 b or 1 c in this scenario.");
            return;
        }
        
        if (aCountB == 1 && aCountC == 0) { aGot_B1_C0 = true; }
        if (aCountB == 0 && aCountC == 1) { aGot_B0_C1 = true; }
        if (aCountB == 0 && aCountC == 2) { aGot_B0_C2 = true; }
        if (aCountB == 1 && aCountC == 1) { aGot_B1_C1 = true; }
        
        if (aGot_B1_C0 && aGot_B0_C1 && aGot_B0_C2 && aGot_B1_C1) {
            break;
        }
        
        
    }
    
    if (aGot_B1_C0 && aGot_B0_C1 && aGot_B0_C2 && aGot_B1_C1) {
        
    } else {
        XCTFail("{pool exclusion rules} we did not hit all the possible answers in 10,000 tries.");
        return;
    }
}

- (void)testPoolVotesSimpleSymbol_GlobalC {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    const GSymbol d = VarSymbol("d");
    
    aScopeStateGlobal.Consume(a);
    
    aPool.Add(a, "cat", 10);
    aPool.Add(b, "cat", 10, 2);
    aPool.Add(c, "cat", 10, 2);
    aPool.Add(d, "cat", 10);
    
    bool aGot_B1_C0 = false;
    bool aGot_B2_C0 = false;
    bool aGot_B0_C1 = false;
    bool aGot_B1_C1 = false;
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(c);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         2,
                         3,
                         d,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        if (PoolEval::Count(aSlots, a) != 0) {
            XCTFail("{pool exclusion rules} a expected not exist.");
            return;
        }
        
        if (PoolEval::Count(aSlots, d) != 1) {
            XCTFail("{pool exclusion rules} d expected exist one.");
            return;
        }
        
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        if (aCountB == 0 && aCountC == 0) {
            XCTFail("{pool exclusion rules} there should be a b or c.");
            return;
        }
        
        if (aCountB > 2 || aCountC > 1) {
            XCTFail("{pool exclusion rules} there should not be more than 2 b or 1 c in this scenario.");
            return;
        }
        
        if (aCountB == 1 && aCountC == 0) { aGot_B1_C0 = true; }
        if (aCountB == 2 && aCountC == 0) { aGot_B2_C0 = true; }
        if (aCountB == 0 && aCountC == 1) { aGot_B0_C1 = true; }
        if (aCountB == 1 && aCountC == 1) { aGot_B1_C1 = true; }
        
        if (aGot_B1_C0 && aGot_B2_C0 && aGot_B0_C1 && aGot_B1_C1) {
            break;
        }
        
        
    }
    
    if (aGot_B1_C0 && aGot_B2_C0 && aGot_B0_C1 && aGot_B1_C1) {
        
    } else {
        XCTFail("{pool exclusion rules} we did not hit all the possible answers in 10,000 tries.");
        return;
    }
}

- (void)testPoolVotesSimpleSymbol_GlobalC_LocalC {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    const GSymbol d = VarSymbol("d");
    
    aScopeStateGlobal.Consume(a);
    
    aPool.Add(a, "cat", 10);
    aPool.Add(b, "cat", 10, 2);
    aPool.Add(c, "cat", 10, 2);
    aPool.Add(d, "cat", 10);
    
    bool aGot_B1_C0 = false;
    bool aGot_B2_C0 = false;
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(c);
        aScopeStateLocalClone.Consume(c);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         2,
                         3,
                         d,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        if (PoolEval::Count(aSlots, a) != 0) {
            XCTFail("{pool exclusion rules} a expected not exist.");
            return;
        }
        
        if (PoolEval::Count(aSlots, d) != 1) {
            XCTFail("{pool exclusion rules} d expected exist one.");
            return;
        }
        
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        if (aCountB == 0 && aCountC == 0) {
            XCTFail("{pool exclusion rules} there should be a b or c.");
            return;
        }
        
        if (aCountB > 2 || aCountC > 0) {
            XCTFail("{pool exclusion rules} there should not be more than 2 b or 0 c in this scenario.");
            return;
        }
        
        if (aCountB == 1 && aCountC == 0) { aGot_B1_C0 = true; }
        if (aCountB == 2 && aCountC == 0) { aGot_B2_C0 = true; }
        if (aGot_B1_C0 && aGot_B2_C0) {
            break;
        }
    }
    
    if (aGot_B1_C0 && aGot_B2_C0) {
        
    } else {
        XCTFail("{pool exclusion rules} we did not hit all the possible answers in 10,000 tries.");
        return;
    }
}

- (void)testPoolVotesSimpleSymbol_GlobalB_LocalC {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    const GSymbol d = VarSymbol("d");
    
    aScopeStateGlobal.Consume(a);
    
    aPool.Add(a, "cat", 10);
    aPool.Add(b, "cat", 10, 2);
    aPool.Add(c, "cat", 10, 2);
    aPool.Add(d, "cat", 10);
    
    bool aGot_B1_C0 = false;
    bool aGot_B0_C1 = false;
    bool aGot_B1_C1 = false;
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(b);
        aScopeStateLocalClone.Consume(c);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         2,
                         3,
                         d,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        if (PoolEval::Count(aSlots, a) != 0) {
            XCTFail("{pool exclusion rules} a expected not exist.");
            return;
        }
        
        if (PoolEval::Count(aSlots, d) != 1) {
            XCTFail("{pool exclusion rules} d expected exist one.");
            return;
        }
        
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        if (aCountB == 0 && aCountC == 0) {
            XCTFail("{pool exclusion rules} there should be a b or c.");
            return;
        }
        
        if (aCountB > 2 || aCountC > 2) {
            XCTFail("{pool exclusion rules} there should not be more than 1 b or 1 c in this scenario.");
            return;
        }
        
        if (aCountB == 1 && aCountC == 0) { aGot_B1_C0 = true; }
        if (aCountB == 0 && aCountC == 1) { aGot_B0_C1 = true; }
        if (aCountB == 1 && aCountC == 1) { aGot_B1_C1 = true; }
        if (aGot_B1_C0 && aGot_B0_C1 && aGot_B1_C1) {
            break;
        }
    }
    
    if (aGot_B1_C0 && aGot_B0_C1 && aGot_B1_C1) {
        
    } else {
        XCTFail("{pool exclusion rules} we did not hit all the possible answers in 10,000 tries.");
        return;
    }
}

- (void)testGlobalLimiting {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    const GSymbol d = VarSymbol("d");
    
    aScopeRules.SetReadPreferredMaximum(a, 1);
    aScopeRules.SetReadPreferredMaximum(b, 2);
    aScopeRules.SetReadPreferredMaximum(c, 3);
    aScopeRules.SetReadPreferredMaximum(d, 4);
    
    aScopeStateGlobal.Consume(a);
    aScopeStateGlobal.Consume(b);
    aScopeStateGlobal.Consume(c);
    
    aPool.Add(a, "cat", 10, 10);
    aPool.Add(b, "cat", 10, 10);
    aPool.Add(c, "cat", 10, 10);
    aPool.Add(d, "cat", 10, 10);
    
    bool aGotB0 = false;
    bool aGotB1 = false;
    
    bool aGotC0 = false;
    bool aGotC1 = false;
    
    bool aGotD1 = false;
    bool aGotD2 = false;
    bool aGotD3 = false;
    bool aGotD4 = false;
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateLocalClone.Consume(c);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         8, // max = [b, c, d, d, d, d], i overshot to 8 on purpose, not reachable.
                         d,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        int aCountD = PoolEval::Count(aSlots, d);
        
        if (aCountD < 1) {
            XCTFail("{pool exclusion rules} d expected exist one.");
            return;
        }
        
        if (aCountA > 0) {
            XCTFail("{pool exclusion rules} maximum for a expected to be 0.");
            return;
        }
        
        if (aCountB > 1) {
            XCTFail("{pool exclusion rules} maximum for b expected to be 1.");
            return;
        }
        
        if (aCountC > 2) {
            XCTFail("{pool exclusion rules} maximum for c expected to be 2.");
            return;
        }
        
        if (aCountD > 4) {
            XCTFail("{pool exclusion rules} maximum for d expected to be 4.");
            return;
        }
        
        if (aCountB == 0) { aGotB0 = true; }
        if (aCountB == 1) { aGotB1 = true; }
        
        if (aCountC == 0) { aGotC0 = true; }
        if (aCountC == 1) { aGotC1 = true; }
        
        if (aCountD == 1) { aGotD1 = true; }
        if (aCountD == 2) { aGotD2 = true; }
        if (aCountD == 3) { aGotD3 = true; }
        if (aCountD == 4) { aGotD4 = true; }
        
        if (aGotB0 && aGotB1 && aGotC0 && aGotC1 && aGotD1 && aGotD2 && aGotD3 && aGotD4) {
            break;
        }
    }
    
    if (aGotB0 && aGotB1 && aGotC0 && aGotC1 && aGotD1 && aGotD2 && aGotD3 && aGotD4) {
        
    } else {
        XCTFail("{pool exclusion rules} we did not hit all the possible answers in 10,000 tries.");
        return;
    }
}

- (void)testGlobalTieBreaking {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    const GSymbol c = VarSymbol("c");
    
    aScopeRules.SetReadPreferredMaximum(a, 3);
    aScopeRules.SetReadPreferredMaximum(b, 3);
    aScopeRules.SetReadPreferredMaximum(c, 1000);
    
    aPool.Add(a, "cat", 10, 10);
    aPool.Add(b, "cat", 10, 10);
    aPool.Add(c, "cat", 10, 10);
    
    bool aGotA0 = false;
    bool aGotA1 = false;
    
    bool aGotB0 = false;
    bool aGotB1 = false;
    
    bool aGotC1 = false;
    bool aGotC2 = false;
    bool aGotC3 = false;
    bool aGotC4 = false;
    bool aGotC5 = false;
    bool aGotC6 = false;
    bool aGotC7 = false;
    bool aGotC8 = false;
    
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(a);
        aScopeStateGlobalClone.Consume(b);
        aScopeStateGlobalClone.Consume(c);
        
        aScopeStateLocalClone.Consume(a);
        aScopeStateLocalClone.Consume(b);
        aScopeStateLocalClone.Consume(c);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         3,
                         8, // max = [b, c, d, d, d, d], i overshot to 8 on purpose, not reachable.
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        int aCountC = PoolEval::Count(aSlots, c);
        
        if (aCountA > 1) {
            XCTFail("{pool exclusion rules} a is expected to limit at 1.");
            return;
        }
        
        if (aCountB > 1) {
            XCTFail("{pool exclusion rules} b is expected to limit at 1.");
            return;
        }
        
        if (aCountC < 1) {
            XCTFail("{pool exclusion rules} c is expected to at least 1 in this setup.");
            return;
        }
        
        if (aCountC > 8) {
            XCTFail("{pool exclusion rules} c is expected to limit at 8.");
            return;
        }
        
        if ((aCountA + aCountB + aCountC) > 8) {
            XCTFail("{pool exclusion rules} count of a, b, and c sum to over 8");
            return;
        }
        
        if ((aCountA + aCountB + aCountC) < 3) {
            XCTFail("{pool exclusion rules} count of a, b, and c sum to under 3");
            return;
        }
        
        if (aCountA == 0) { aGotA0 = true; }
        if (aCountA == 1) { aGotA1 = true; }
        
        if (aCountB == 0) { aGotB0 = true; }
        if (aCountB == 1) { aGotB1 = true; }
        
        if (aCountC == 1) { aGotC1 = true; }
        if (aCountC == 2) { aGotC2 = true; }
        if (aCountC == 3) { aGotC3 = true; }
        if (aCountC == 4) { aGotC4 = true; }
        if (aCountC == 5) { aGotC5 = true; }
        if (aCountC == 6) { aGotC6 = true; }
        if (aCountC == 7) { aGotC7 = true; }
        if (aCountC == 8) { aGotC8 = true; }
        
        
        bool aGotA0 = false; bool aGotA1 = false;
        
        bool aGotB0 = false; bool aGotB1 = false;
        
        bool aGotC0 = false; bool aGotC1 = false; bool aGotC2 = false;
        bool aGotC3 = false; bool aGotC4 = false; bool aGotC5 = false;
        bool aGotC6 = false; bool aGotC7 = false; bool aGotC8 = false;
        
        if (aGotA0 & aGotA1 & aGotB0 & aGotB1 & aGotC0 & aGotC1 & aGotC2 & aGotC3 & aGotC4 & aGotC5 & aGotC6 & aGotC7 & aGotC8) {
            break;
        }
        
    }
    
    if (aGotA0 & aGotA1 & aGotB0 & aGotB1 & aGotC1 & aGotC2 & aGotC3 & aGotC4 & aGotC5 & aGotC6 & aGotC7 & aGotC8) {
        
    } else {
        XCTFail("{pool exclusion rules} we did not hit all the possible answers in 10,000 tries.");
        return;
    }
}

- (void)testGlobalLocalRuleMiniScenarios {
    
    GScopeRules aScopeRules;
    GScopeState aScopeStateGlobal;
    GScopeState aScopeStateLocal;
    GPool aPool(&aScopeRules, &aScopeStateGlobal);
    const GSymbol a = VarSymbol("a");
    const GSymbol b = VarSymbol("b");
    
    aScopeRules.SetReadPreferredMaximum(a, 4);
    aScopeRules.SetReadPreferredMaximum(b, 4);
    
    aPool.Add(a, "cat", 10, 2);
    aPool.Add(b, "cat", 10, 2);
    
    bool aPassRound = false;
    
    std::vector<bool> aAchieveA = {false, false};
    std::vector<bool> aAchieveB = {false, false};
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 2, aCountA,
                                0, 2, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 4, aHardFailure)) {
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
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(a);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 1, aCountA,
                                0, 2, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 3, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario b.");
            return;
        }
    }
    
    if (aPassRound == false) {
        XCTFail("{mini scenarios} failed scenario b.");
        return;
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 2, aCountA,
                                0, 1, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 3, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario c.");
            return;
        }
    }
    
    if (aPassRound == false) {
        XCTFail("{mini scenarios} failed scenario c.");
        return;
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(b);
        aScopeStateLocalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(1, 2, aCountA,
                                0, 0, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 2, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario d.");
            return;
        }
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(b);
        aScopeStateGlobalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(1, 2, aCountA,
                                0, 0, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 2, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario e.");
            return;
        }
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateLocalClone.Consume(b);
        aScopeStateLocalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(1, 2, aCountA,
                                0, 0, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 2, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario f.");
            return;
        }
    }
    
    if (aPassRound == false) {
        XCTFail("{mini scenarios} failed scenario d.");
        return;
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(a);
        aScopeStateLocalClone.Consume(a);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 0, aCountA,
                                1, 2, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 2, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario g.");
            return;
        }
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateLocalClone.Consume(a);
        aScopeStateLocalClone.Consume(a);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 0, aCountA,
                                1, 2, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 2, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario h.");
            return;
        }
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(a);
        aScopeStateGlobalClone.Consume(a);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 0, aCountA,
                                1, 2, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 2, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario i.");
            return;
        }
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(a);
        aScopeStateGlobalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 1, aCountA,
                                0, 1, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 3, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario j.");
            return;
        }
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(a);
        aScopeStateLocalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 1, aCountA,
                                0, 1, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 3, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario k.");
            return;
        }
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateLocalClone.Consume(a);
        aScopeStateGlobalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 1, aCountA,
                                0, 1, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 3, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario l.");
            return;
        }
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateGlobalClone.Consume(a);
        aScopeStateGlobalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 1, aCountA,
                                0, 1, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 3, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario n.");
            return;
        }
    }
    
    PoolEval::ResetTwo(aAchieveA, aAchieveB);
    aPassRound = false;
    for (int i=0;i<1000;i++) {
        GScopeState aScopeStateGlobalClone = aScopeStateGlobal;
        GScopeState aScopeStateLocalClone = aScopeStateLocal;
        
        aScopeStateLocalClone.Consume(a);
        aScopeStateLocalClone.Consume(b);
        
        std::vector<GStatementSlot> aSlots;
        std::string aErrorString;
        aPool.FetchSlots("cat",
                         1,
                         4,
                         aSlots,
                         aScopeStateLocalClone,
                         aScopeStateGlobalClone,
                         aErrorString);
        
        int aCountA = PoolEval::Count(aSlots, a);
        int aCountB = PoolEval::Count(aSlots, b);
        bool aHardFailure = false;
        if (PoolEval::UpdateTwo(0, 1, aCountA,
                                0, 1, aCountB,
                                aAchieveA,
                                aAchieveB, 1, 3, aHardFailure)) {
            aPassRound = true;
            break;
        }
        if (aHardFailure) {
            XCTFail("{mini scenarios} failed scenario o.");
            return;
        }
    }
    
    
}



@end
