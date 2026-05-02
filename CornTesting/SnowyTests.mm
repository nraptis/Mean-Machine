//
//  SnowyTests.m
//  CornTesting
//
//  Created by Dragon on 4/30/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "GSelect.hpp"
#include "GLoopMixBrew.hpp"
#include "Varz.hpp"
#include "StatementChecker.hpp"
#include "TwistSnow.hpp"
#include "TwistExpander.hpp"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <unistd.h>

static bool HexToBytes(const char *pHex,
                       std::uint8_t *pDest,
                       std::size_t pDestLength) {

    if (pHex == nullptr) {
        return false;
    }

    for (std::size_t aIndex = 0; aIndex < pDestLength; aIndex++) {
        unsigned int aByte = 0;
        if (std::sscanf(pHex + (aIndex * 2U), "%2x", &aByte) != 1) {
            return false;
        }
        pDest[aIndex] = static_cast<std::uint8_t>(aByte);
    }

    return true;
}

static std::string BytesToHex(const std::uint8_t *pSource,
                              std::size_t pSourceLength) {

    static constexpr char S_HEX[] = "0123456789abcdef";
    std::string aHex;
    aHex.reserve(pSourceLength * 2U);

    for (std::size_t aIndex = 0; aIndex < pSourceLength; aIndex++) {
        const std::uint8_t aValue = pSource[aIndex];
        aHex.push_back(S_HEX[(aValue >> 4) & 0x0FU]);
        aHex.push_back(S_HEX[(aValue >> 0) & 0x0FU]);
    }

    return aHex;
}

static bool CipherSupportedAtPath(const char *pOpenSSLPath,
                                  const char *pCipherName) {

    if ((pOpenSSLPath == nullptr) || (pCipherName == nullptr)) {
        return false;
    }

    if (::access(pOpenSSLPath, X_OK) != 0) {
        return false;
    }

    NSPipe *aPipe = [NSPipe pipe];
    NSTask *aTask = [[NSTask alloc] init];
    [aTask setLaunchPath:[NSString stringWithUTF8String:pOpenSSLPath]];
    [aTask setArguments:@[@"enc", @"-ciphers"]];
    [aTask setStandardOutput:aPipe];
    [aTask setStandardError:aPipe];

    @try {
        [aTask launch];
        [aTask waitUntilExit];
    } @catch (NSException *pEx) {
        (void)pEx;
        return false;
    }

    if ([aTask terminationStatus] != 0) {
        return false;
    }

    NSData *aData = [[aPipe fileHandleForReading] readDataToEndOfFile];
    if (aData == nil) {
        return false;
    }

    NSString *aText = [[NSString alloc] initWithData:aData encoding:NSUTF8StringEncoding];
    if (aText == nil) {
        return false;
    }

    const std::string aHaystack = [aText UTF8String];
    const std::string aNeedle = std::string("-") + pCipherName;
    return aHaystack.find(aNeedle) != std::string::npos;
}

static bool ResolveOpenSSLPathForCipher(const char *pCipherName,
                                        std::string *pOpenSSLPath) {

    std::vector<std::string> aCandidates;

    const char *aEnvOpenSSL = std::getenv("OPENSSL_BIN");
    if ((aEnvOpenSSL != nullptr) && (aEnvOpenSSL[0] != 0)) {
        aCandidates.emplace_back(aEnvOpenSSL);
    }

    aCandidates.emplace_back("/opt/anaconda3/bin/openssl");
    aCandidates.emplace_back("/opt/homebrew/bin/openssl");
    aCandidates.emplace_back("/usr/local/bin/openssl");
    aCandidates.emplace_back("/usr/bin/openssl");

    for (const std::string &aPath : aCandidates) {
        if (CipherSupportedAtPath(aPath.c_str(), pCipherName)) {
            *pOpenSSLPath = aPath;
            return true;
        }
    }

    return false;
}

static bool RunOpenSSLKeystream(const char *pCipherName,
                                const std::string &pKeyHex,
                                const std::string &pIvHex,
                                std::vector<std::uint8_t> *pDest,
                                std::string *pErrorMessage) {

    std::string aOpenSSLPath;
    if (!ResolveOpenSSLPathForCipher(pCipherName, &aOpenSSLPath)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("no openssl binary with cipher support for ") + pCipherName;
        }
        return false;
    }

    char aTempDirTemplate[] = "/tmp/twist_snow_cmp_XXXXXX";
    char *aTempDir = ::mkdtemp(aTempDirTemplate);
    if (aTempDir == nullptr) {
        if (pErrorMessage != nullptr) { *pErrorMessage = "mkdtemp failed"; }
        return false;
    }

    const std::string aInPath = std::string(aTempDir) + "/in.bin";
    const std::string aOutPath = std::string(aTempDir) + "/out.bin";

    {
        std::vector<std::uint8_t> aZeroInput(static_cast<std::size_t>(S_BLOCK), 0U);
        FILE *aFile = std::fopen(aInPath.c_str(), "wb");
        if (aFile == nullptr) {
            if (pErrorMessage != nullptr) { *pErrorMessage = "failed to open temp input"; }
            return false;
        }

        const std::size_t aWriteCount = std::fwrite(aZeroInput.data(),
                                                    1U,
                                                    aZeroInput.size(),
                                                    aFile);
        std::fclose(aFile);

        if (aWriteCount != aZeroInput.size()) {
            if (pErrorMessage != nullptr) { *pErrorMessage = "failed to write temp input"; }
            return false;
        }
    }

    NSString *aCipherArg = [NSString stringWithFormat:@"-%s", pCipherName];
    NSString *aKeyArg = [NSString stringWithUTF8String:pKeyHex.c_str()];
    NSString *aIvArg = [NSString stringWithUTF8String:pIvHex.c_str()];
    NSString *aInArg = [NSString stringWithUTF8String:aInPath.c_str()];
    NSString *aOutArg = [NSString stringWithUTF8String:aOutPath.c_str()];
    NSString *aOpenSSLPathArg = [NSString stringWithUTF8String:aOpenSSLPath.c_str()];

    NSPipe *aErrorPipe = [NSPipe pipe];
    NSTask *aTask = [[NSTask alloc] init];
    [aTask setLaunchPath:aOpenSSLPathArg];
    [aTask setArguments:@[@"enc",
                          aCipherArg,
                          @"-nosalt",
                          @"-K",
                          aKeyArg,
                          @"-iv",
                          aIvArg,
                          @"-in",
                          aInArg,
                          @"-out",
                          aOutArg]];
    [aTask setStandardError:aErrorPipe];

    @try {
        [aTask launch];
        [aTask waitUntilExit];
    } @catch (NSException *pEx) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = std::string("failed to launch openssl: ") +
                      [[pEx reason] UTF8String];
        }
        return false;
    }

    if ([aTask terminationStatus] != 0) {
        NSData *aErrorData = [[aErrorPipe fileHandleForReading] readDataToEndOfFile];
        if (pErrorMessage != nullptr) {
            NSString *aErrorText = [[NSString alloc] initWithData:aErrorData
                                                          encoding:NSUTF8StringEncoding];
            if (aErrorText == nil) {
                *pErrorMessage = "openssl failed";
            } else {
                *pErrorMessage = [aErrorText UTF8String];
            }
        }
        return false;
    }

    NSData *aOutData = [NSData dataWithContentsOfFile:aOutArg];
    if (aOutData == nil) {
        if (pErrorMessage != nullptr) { *pErrorMessage = "failed to read openssl output"; }
        return false;
    }

    const std::size_t aByteLength = static_cast<std::size_t>([aOutData length]);
    pDest->resize(aByteLength);
    std::memcpy(pDest->data(), [aOutData bytes], aByteLength);
    return true;
}

@interface SnowyTests : XCTestCase

@end

@implementation SnowyTests

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

- (void)testAES256CounterMatchesFipsVector {

    std::uint8_t aSource[S_BLOCK];
    std::uint8_t aDest[S_BLOCK];
    std::memset(aSource, 0, sizeof(aSource));
    std::memset(aDest, 0, sizeof(aDest));

    for (int aIndex = 0; aIndex < 32; aIndex++) {
        aSource[aIndex] = static_cast<std::uint8_t>(aIndex);
    }

    if (!HexToBytes("00112233445566778899aabbccddeeff", aSource + 32, 16U)) {
        XCTFail("hex parse failed");
        return;
    }

    TwistSnow::AES256Counter(aSource, aDest);

    std::uint8_t aExpected[16];
    if (!HexToBytes("8ea2b7ca516745bfeafc49904b496089", aExpected, 16U)) {
        XCTFail("hex parse failed");
        return;
    }

    if (std::memcmp(aDest, aExpected, sizeof(aExpected)) != 0) {
        XCTFail("AES256Counter vector mismatch");
        return;
    }
}

- (void)testChaCha20CounterMatchesRFC8439BlockVector {

    std::uint8_t aSource[S_BLOCK];
    std::uint8_t aDest[S_BLOCK];
    std::memset(aSource, 0, sizeof(aSource));
    std::memset(aDest, 0, sizeof(aDest));

    for (int aIndex = 0; aIndex < 32; aIndex++) {
        aSource[aIndex] = static_cast<std::uint8_t>(aIndex);
    }

    // IETF ChaCha20 layout: 32-bit counter (little endian) + 96-bit nonce.
    aSource[32] = 0x01;
    aSource[33] = 0x00;
    aSource[34] = 0x00;
    aSource[35] = 0x00;

    if (!HexToBytes("000000090000004a00000000", aSource + 36, 12U)) {
        XCTFail("hex parse failed");
        return;
    }

    TwistSnow::ChaCha20Counter(aSource, aDest);

    std::uint8_t aExpected[64];
    if (!HexToBytes("10f1e7e4d13b5915500fdd1fa32071c4"
                    "c7d1f4c733c068030422aa9ac3d46c4e"
                    "d2826446079faa0914c2d705d98b02a2"
                    "b5129cd1de164eb9cbd083e8a2503c4e",
                    aExpected,
                    64U)) {
        XCTFail("hex parse failed");
        return;
    }

    if (std::memcmp(aDest, aExpected, sizeof(aExpected)) != 0) {
        XCTFail("ChaCha20Counter vector mismatch");
        return;
    }
}

- (void)testAria256CounterMatchesRFC5794Vector {

    std::uint8_t aSource[S_BLOCK];
    std::uint8_t aDest[S_BLOCK];
    std::memset(aSource, 0, sizeof(aSource));
    std::memset(aDest, 0, sizeof(aDest));

    for (int aIndex = 0; aIndex < 32; aIndex++) {
        aSource[aIndex] = static_cast<std::uint8_t>(aIndex);
    }

    if (!HexToBytes("00112233445566778899aabbccddeeff", aSource + 32, 16U)) {
        XCTFail("hex parse failed");
        return;
    }

    TwistSnow::Aria256Counter(aSource, aDest);

    std::uint8_t aExpected[16];
    if (!HexToBytes("f92bd7c79fb72e2f2b8f80c1972d24fc", aExpected, 16U)) {
        XCTFail("hex parse failed");
        return;
    }

    if (std::memcmp(aDest, aExpected, sizeof(aExpected)) != 0) {
        XCTFail("Aria256Counter vector mismatch");
        return;
    }
}

- (void)testCounterStreamsMatchOpenSSLAtSBlockSize {

    std::uint8_t aSource[S_BLOCK];
    std::uint8_t aDest[S_BLOCK];
    std::memset(aSource, 0, sizeof(aSource));
    std::memset(aDest, 0, sizeof(aDest));

    for (int aIndex = 0; aIndex < 48; aIndex++) {
        aSource[aIndex] = static_cast<std::uint8_t>((aIndex * 37 + 11) & 0xFF);
    }

    const std::string aKeyHex = BytesToHex(aSource, 32U);
    const std::string aIvHex = BytesToHex(aSource + 32, 16U);

    struct CounterCase {
        const char *mName;
        const char *mOpenSslCipher;
        void (*mCounterFn)(std::uint8_t *, std::uint8_t *);
    };

    const CounterCase aCases[] = {
        {"AES256Counter", "aes-256-ctr", &TwistSnow::AES256Counter},
        {"ChaCha20Counter", "chacha20", &TwistSnow::ChaCha20Counter},
        {"Aria256Counter", "aria-256-ctr", &TwistSnow::Aria256Counter}
    };

    for (const CounterCase &aCase : aCases) {

        std::memset(aDest, 0, sizeof(aDest));
        aCase.mCounterFn(aSource, aDest);

        std::vector<std::uint8_t> aOpenSSL;
        std::string aError;
        if (!RunOpenSSLKeystream(aCase.mOpenSslCipher, aKeyHex, aIvHex, &aOpenSSL, &aError)) {
            XCTFail("%s: OpenSSL run failed: %s", aCase.mName, aError.c_str());
            return;
        }

        if (aOpenSSL.size() != static_cast<std::size_t>(S_BLOCK)) {
            XCTFail("%s: OpenSSL output length mismatch (got %zu, expected %d)",
                    aCase.mName,
                    aOpenSSL.size(),
                    S_BLOCK);
            return;
        }

        const int aMismatch = std::memcmp(aDest, aOpenSSL.data(), static_cast<std::size_t>(S_BLOCK));
        if (aMismatch != 0) {
            std::size_t aFirstMismatchIndex = 0U;
            while (aFirstMismatchIndex < static_cast<std::size_t>(S_BLOCK) &&
                   aDest[aFirstMismatchIndex] == aOpenSSL[aFirstMismatchIndex]) {
                aFirstMismatchIndex += 1U;
            }

            XCTFail("%s: mismatch at byte %zu (ours=%02x openssl=%02x)",
                    aCase.mName,
                    aFirstMismatchIndex,
                    aDest[aFirstMismatchIndex],
                    aOpenSSL[aFirstMismatchIndex]);
            return;
        }
    }
}



@end
