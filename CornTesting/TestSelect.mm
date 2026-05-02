//
//  TestSelect.m
//  CornTesting
//
//  Created by Dragon on 4/30/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "GSelect.hpp"
#include "GLoopMixBrew.hpp"
#include "GFastMatrix.hpp"
#include "Varz.hpp"
#include "StatementChecker.hpp"
#include "TwistExpander.hpp"

@interface TestSelect : XCTestCase

@end

@implementation TestSelect

- (void)testSelectStatement4WaySingleTab {
    GSelect aSelect;
    aSelect.mThresholdA = 1;
    aSelect.mThresholdB = 2;
    aSelect.mThresholdC = 3;

    GStatement aStmtA = GStatement::Assign(GTarget::Symbol(GSymbol::Var("aBranchA")),
                                           GExpr::Symbol(GSymbol::Var("aValueA")));
    GStatement aStmtB = GStatement::Assign(GTarget::Symbol(GSymbol::Var("aBranchB")),
                                           GExpr::Symbol(GSymbol::Var("aValueB")));
    GStatement aStmtC = GStatement::Assign(GTarget::Symbol(GSymbol::Var("aBranchC")),
                                           GExpr::Symbol(GSymbol::Var("aValueC")));
    GStatement aStmtD = GStatement::Assign(GTarget::Symbol(GSymbol::Var("aBranchD")),
                                           GExpr::Symbol(GSymbol::Var("aValueD")));
    
    aSelect.AddStatementA(&aStmtA);
    aSelect.AddStatementB(&aStmtB);
    aSelect.AddStatementC(&aStmtC);
    aSelect.AddStatementD(&aStmtD);

    std::vector<GStatement> aStatementList;
    std::string aError;
    if (!aSelect.Bake(GSymbol::Var("aSelect"),
                      GExpr::Symbol(GSymbol::Var("aInput")),
                      &aStatementList,
                      &aError)) {
        XCTFail("select bake statements failed");
        return;
    }

    std::vector<std::string> expected = {
        "aSelect = aInput;",
        "if (aSelect > 3) {",
        "\taBranchD = aValueD;",
        "} else {",
        "\tif (aSelect > 2) {",
        "\taBranchC = aValueC;",
        "\t} else {",
        "\tif (aSelect > 1) {",
        "\taBranchB = aValueB;",
        "\t} else {",
        "\taBranchA = aValueA;",
        "\t}",
        "\t}",
        "}"
    };

    if (!StatementChecker::Eval(aStatementList, expected)) {
        XCTFail("statement checker failed");
        return;
    }
}


- (void)testSelectStatementHelloWorld {
    
    GSelect aSelect = GSelect::Demo2(111, 222);
    printf("aSelect = %d\n", aSelect.mThresholdA);
    printf("aSelect = 0x%02X\n", aSelect.mMask);
    
    Varz aVars;
    std::string aError;

    std::vector<GStatement> aStatementListA;
    GLoopFragmentComposer aFragmentComposerA(aVars.mLoopIndex);
    aFragmentComposerA.ResetXorEqual(aVars.mCarry);
    aFragmentComposerA.MixBuffer(aVars.mSaltA).Offset(100);
    aFragmentComposerA.MixBuffer(aVars.mSaltB).Offset(25);
    
    if (!aFragmentComposerA.Bake(&aStatementListA, &aError)) {
        printf("bake statements failed: %s\n", aError.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    
    std::vector<GStatement> aStatementListB;
    GLoopFragmentComposer aFragmentComposerB(aVars.mLoopIndex);
    aFragmentComposerB.ResetXorEqual(aVars.mCarry);
    aFragmentComposerB.MixBuffer(aVars.mSaltD).Key(aVars.mValue);
    if (!aFragmentComposerB.Bake(&aStatementListB, &aError)) {
        printf("bake statements failed: %s\n", aError.c_str());
        XCTFail("bake statements failed");
        return;
    }
    
    aSelect.AddStatementsA(&aStatementListA);
    aSelect.AddStatementsB(&aStatementListB);
    
    std::vector<GStatement> aStatementList;
    GExpr aSelectExpr = GExpr::Read(aVars.mWorkerA, GExpr::Symbol(aVars.mLoopIndex));
    if (!aSelect.Bake(aVars.mSelect, aSelectExpr, &aStatementList, &aError)) {
        
        printf("select bake statements failed: %s\n", aError.c_str());
        XCTFail("select bake statements failed");
        return;
        
    }
    
    std::vector<std::string> expected = {
        "aSelect = aWorkLaneA[i];",
        "if (aSelect > 52) {",
        "\taSaltAKeyA = i + 100U;",
        "\taSaltBKeyA = i + 25U;",
        "\taCarry ^= aSaltA[aSaltAKeyA & 0x7FU] + aSaltB[aSaltBKeyA & 0x7FU];",
        "} else {",
        "\taCarry ^= aSaltD[aValue & 0x7FU];",
        "}"
    };
    
    if (!StatementChecker::Eval(aStatementList, expected)) {
        XCTFail("statement checker failed");
        return;
    }
    
    
    
    
    
    
}

- (void)testSelectStatementJsonRoundTripRuntime {
    
    GSelect aSelect = GSelect::Demo2(111, 222);
    Varz aVars;
    std::string aError;

    std::vector<GStatement> aStatementListA;
    GLoopFragmentComposer aFragmentComposerA(aVars.mLoopIndex);
    aFragmentComposerA.ResetXorEqual(aVars.mCarry);
    aFragmentComposerA.MixBuffer(aVars.mSaltA).Offset(100);
    aFragmentComposerA.MixBuffer(aVars.mSaltB).Offset(25);
    if (!aFragmentComposerA.Bake(&aStatementListA, &aError)) {
        XCTFail("bake statements failed");
        return;
    }

    std::vector<GStatement> aStatementListB;
    GLoopFragmentComposer aFragmentComposerB(aVars.mLoopIndex);
    aFragmentComposerB.ResetXorEqual(aVars.mCarry);
    aFragmentComposerB.MixBuffer(aVars.mSaltD).Key(aVars.mValue);
    if (!aFragmentComposerB.Bake(&aStatementListB, &aError)) {
        XCTFail("bake statements failed");
        return;
    }

    aSelect.AddStatementsA(&aStatementListA);
    aSelect.AddStatementsB(&aStatementListB);

    std::vector<GStatement> aStatementList;
    GExpr aSelectExpr = GExpr::Read(aVars.mWorkerA, GExpr::Symbol(aVars.mLoopIndex));
    if (!aSelect.Bake(aVars.mSelect, aSelectExpr, &aStatementList, &aError)) {
        XCTFail("select bake statements failed");
        return;
    }

    GLoop aLoop;
    aLoop.mLoopVariable = aVars.mLoopIndex;
    aLoop.mLoopVariableName = aVars.mLoopIndex.mName;
    aLoop.mLoopBegin = 0;
    aLoop.mLoopEndText = "1";
    aLoop.mLoopStep = 1;
    aLoop.mBodyStatements = aStatementList;

    GBatch aBatch;
    aBatch.CommitLoop(&aLoop);

    std::string aCppError;
    const std::string aCpp = aBatch.BuildCppScopeBlock(&aCppError, false);
    if (aCpp.empty()) {
        XCTFail("cpp generation failed");
        return;
    }
    if ((aCpp.find("if (aSelect > 52) {") == std::string::npos) ||
        (aCpp.find("} else {") == std::string::npos)) {
        XCTFail("cpp generation missing select control flow");
        return;
    }

    const std::string aJson = aBatch.ToJson(&aError);
    if (aJson.empty()) {
        XCTFail("batch json export failed");
        return;
    }

    GBatch aBatchRoundTrip;
    if (!GBatch::FromJson(aJson, &aBatchRoundTrip, &aError)) {
        XCTFail("batch json import failed");
        return;
    }

    TwistWorkSpace aWorkspaceA;
    TwistExpander aExpanderA;
    aWorkspaceA.mWorkLaneA[0] = 60;
    aExpanderA.mSaltA[100] = 5;
    aExpanderA.mSaltB[25] = 7;
    std::unordered_map<std::string, int> aVarsA;
    aVarsA[aVars.mCarry.mName] = 0;
    if (!aBatchRoundTrip.ExecuteWithVariables(&aWorkspaceA, &aExpanderA, &aVarsA, &aError)) {
        XCTFail("batch execute failed");
        return;
    }
    if (aVarsA[aVars.mCarry.mName] != 12) {
        XCTFail("branch A runtime mismatch");
        return;
    }

    TwistWorkSpace aWorkspaceB;
    TwistExpander aExpanderB;
    aWorkspaceB.mWorkLaneA[0] = 40;
    aExpanderB.mSaltD[0] = 9;
    std::unordered_map<std::string, int> aVarsB;
    aVarsB[aVars.mCarry.mName] = 0;
    aVarsB[aVars.mValue.mName] = 0;
    if (!aBatchRoundTrip.ExecuteWithVariables(&aWorkspaceB, &aExpanderB, &aVarsB, &aError)) {
        XCTFail("batch execute failed");
        return;
    }
    if (aVarsB[aVars.mCarry.mName] != 9) {
        XCTFail("branch B runtime mismatch");
        return;
    }
}

- (void)testFastMatrixBakeAndExecute {
    Varz aVars;
    std::string aError;

    GFastMatrix aFast(GFastMatrixType::kA);
    aFast.Perform(GFastMatrixOp::kReverseRow, 2U, 0U);
    aFast.Perform(GFastMatrixOp::kSwapCols, 1U, 6U);
    aFast.Perform(GFastMatrixOp::kShiftRing8A, 3U, 0U);

    std::vector<GStatement> aPre;
    std::vector<GStatement> aBody;
    std::vector<GStatement> aPost;
    if (!aFast.BakeLoad(aVars.mWorkerA, aVars.mLoopIndex, &aPre, &aError)) {
        XCTFail("fast matrix bake load failed");
        return;
    }
    if (!aFast.BakePerform(&aBody, &aError)) {
        XCTFail("fast matrix bake perform failed");
        return;
    }
    if (!aFast.BakeUnroll(aVars.mWorkerB, aVars.mLoopIndex, TwistFastMatrixUnrollScheme::kA, 0U, &aPost, &aError)) {
        XCTFail("fast matrix bake unroll failed");
        return;
    }

    std::vector<std::string> expectedPre = {
        "mMatrixA.LoadAndReset(aWorkLaneA + i);"
    };
    std::vector<std::string> expectedBody = {
        "mMatrixA.ReverseRow(2U, 0U);",
        "mMatrixA.SwapCols(1U, 6U);",
        "mMatrixA.ShiftRing8A(3U, 0U);"
    };
    std::vector<std::string> expectedPost = {
        "mMatrixA.Store(aWorkLaneB + i, TwistFastMatrixUnrollScheme::kA, 0U);"
    };
    if (!StatementChecker::Eval(aPre, expectedPre) ||
        !StatementChecker::Eval(aBody, expectedBody) ||
        !StatementChecker::Eval(aPost, expectedPost)) {
        XCTFail("fast matrix baked statement mismatch");
        return;
    }

    GLoop aLoop;
    aLoop.mLoopVariable = aVars.mLoopIndex;
    aLoop.mLoopVariableName = aVars.mLoopIndex.mName;
    aLoop.mLoopBegin = 32;
    aLoop.mLoopEndText = "33";
    aLoop.mLoopStep = 1;
    aLoop.mBodyStatements.insert(aLoop.mBodyStatements.end(), aPre.begin(), aPre.end());
    aLoop.mBodyStatements.insert(aLoop.mBodyStatements.end(), aBody.begin(), aBody.end());
    aLoop.mBodyStatements.insert(aLoop.mBodyStatements.end(), aPost.begin(), aPost.end());

    GBatch aBatch;
    aBatch.CommitLoop(&aLoop);

    TwistWorkSpace aWorkspace;
    TwistExpander aExpander;
    for (int aIndex = 0; aIndex < S_BLOCK; ++aIndex) {
        aWorkspace.mWorkLaneA[aIndex] = static_cast<std::uint8_t>(aIndex & 0xFF);
        aWorkspace.mWorkLaneB[aIndex] = 0U;
    }
    std::unordered_map<std::string, int> aRuntimeVars;
    if (!aBatch.ExecuteWithVariables(&aWorkspace, &aExpander, &aRuntimeVars, &aError)) {
        printf("execute failed: %s\n", aError.c_str());
        XCTFail("fast matrix batch execute failed");
        return;
    }

    TwistFastMatrix aExpectedMatrix;
    aExpectedMatrix.LoadAndReset(aWorkspace.mWorkLaneA + 32);
    aExpectedMatrix.ExecuteOp(TwistFastMatrixOp::kReverseRow, 2U, 0U);
    aExpectedMatrix.ExecuteOp(TwistFastMatrixOp::kSwapCols, 1U, 6U);
    aExpectedMatrix.ExecuteOp(TwistFastMatrixOp::kShiftRing8A, 3U, 0U);
    std::uint8_t aExpectedBlock[64];
    aExpectedMatrix.Store(aExpectedBlock, TwistFastMatrixUnrollScheme::kA, 0U);

    for (int aIndex = 0; aIndex < 64; ++aIndex) {
        if (aWorkspace.mWorkLaneB[32 + aIndex] != aExpectedBlock[aIndex]) {
            XCTFail("fast matrix runtime result mismatch");
            return;
        }
    }
}

- (void)testFastMatrixSpeedBuckets {
    std::vector<TwistFastMatrixOp> aFast = TwistFastMatrix::GetAllTypesFast();
    std::vector<TwistFastMatrixOp> aMedium = TwistFastMatrix::GetAllTypesMedium();
    std::vector<TwistFastMatrixOp> aSlow = TwistFastMatrix::GetAllTypesSlow();

    auto Contains = [](const std::vector<TwistFastMatrixOp> &pList, TwistFastMatrixOp pValue) {
        for (TwistFastMatrixOp aType : pList) {
            if (aType == pValue) {
                return true;
            }
        }
        return false;
    };

    if (!Contains(aFast, TwistFastMatrixOp::kReverseRow) ||
        !Contains(aFast, TwistFastMatrixOp::kSwapSixteenths)) {
        XCTFail("fast matrix fast-bucket classification mismatch");
        return;
    }
    if (!Contains(aMedium, TwistFastMatrixOp::kShiftRing16A) ||
        !Contains(aMedium, TwistFastMatrixOp::kRotateRightQuarterA)) {
        XCTFail("fast matrix medium-bucket classification mismatch");
        return;
    }
    if (!Contains(aSlow, TwistFastMatrixOp::kRotateRight) ||
        !Contains(aSlow, TwistFastMatrixOp::kPinwheelRight)) {
        XCTFail("fast matrix slow-bucket classification mismatch");
        return;
    }
}


- (void)testSelect4 {
    
    for (int aTrial=0; aTrial<32; aTrial++) {
        
        GSelect aSelect = GSelect::Random4();
        
        int aCountA = 0;
        int aCountB = 0;
        int aCountC = 0;
        int aCountD = 0;
        for (int aByte=0; aByte<256;aByte++) {
            int aSelectLine = aSelect.mMask & aByte;
            
            if (aSelectLine > aSelect.mThresholdC) {
                aCountD++;
            } else if (aSelectLine > aSelect.mThresholdB) {
                aCountC++;
            } else if (aSelectLine > aSelect.mThresholdA) {
                aCountB++;
            } else {
                aCountA++;
            }
        }
        if (aCountA != 64) {
            printf("GSelect::Random4() failed, got %d of count a\n", aCountA);
            XCTFail("select test failed select 4, case a");
            return;
        }
        if (aCountB != 64) {
            printf("GSelect::Random4() failed, got %d of count b\n", aCountA);
            XCTFail("select test failed select 4, case b");
            return;
        }
        if (aCountC != 64) {
            printf("GSelect::Random4() failed, got %d of count c\n", aCountA);
            XCTFail("select test failed select 4, case c");
            return;
        }
        if (aCountD != 64) {
            printf("GSelect::Random4() failed, got %d of count d\n", aCountA);
            XCTFail("select test failed select 4, case d");
            return;
        }
    }
}

- (void)testSelect2 {
    
    for (int aTrial=0; aTrial<32; aTrial++) {
        
        GSelect aSelect = GSelect::Random2();
        
        int aCountA = 0;
        int aCountB = 0;
        for (int aByte=0; aByte<256;aByte++) {
            int aSelectLine = aSelect.mMask & aByte;
            if (aSelectLine > aSelect.mThresholdA) {
                aCountB++;
            } else {
                aCountA++;
            }
        }
        if (aCountA != 128) {
            printf("GSelect::Random4() failed, got %d of count a\n", aCountA);
            XCTFail("select test failed select 2, case a");
            return;
        }
        if (aCountB != 128) {
            printf("GSelect::Random4() failed, got %d of count b\n", aCountA);
            XCTFail("select test failed select 2, case b");
            return;
        }
    }
}



@end
