//
//  SaltScoreAnalysis.m
//  CornTesting
//
//  Created by Dragon on 5/12/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "TwistWorkSpace.hpp"
#include "Random.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistCryptoScoring.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

@interface SaltScoreAnalysis : XCTestCase
@end

@implementation SaltScoreAnalysis

static std::uint64_t MakeRandom64() {
    std::uint64_t aResult = 0ULL;
    for (int i = 0; i < 8; i++) {
        aResult <<= 8;
        aResult |= static_cast<std::uint64_t>(Random::GetByte());
    }
    return aResult;
}

static void FillRandomSalt(std::uint64_t *pSalt) {
    for (int i = 0; i < S_SALT; i++) {
        pSalt[i] = MakeRandom64();
    }
}

static void FillAllZero(std::uint64_t *pSalt) {
    for (int i = 0; i < S_SALT; i++) {
        pSalt[i] = 0ULL;
    }
}

static void FillAllSame(std::uint64_t *pSalt, std::uint64_t pValue) {
    for (int i = 0; i < S_SALT; i++) {
        pSalt[i] = pValue;
    }
}

static void FillAlternating(std::uint64_t *pSalt) {
    for (int i = 0; i < S_SALT; i++) {
        pSalt[i] = (i & 1) ? 0xAAAAAAAAAAAAAAAAULL : 0x5555555555555555ULL;
    }
}

static void FillRepeatingPattern4(std::uint64_t *pSalt) {
    static const std::uint64_t kPattern[4] = {
        0x0123456789ABCDEFULL,
        0xFEDCBA9876543210ULL,
        0x0F0F0F0F0F0F0F0FULL,
        0xF0F0F0F0F0F0F0F0ULL
    };

    for (int i = 0; i < S_SALT; i++) {
        pSalt[i] = kPattern[i & 3];
    }
}

static void FillCounter(std::uint64_t *pSalt) {
    for (int i = 0; i < S_SALT; i++) {
        pSalt[i] = static_cast<std::uint64_t>(i);
    }
}

static void FillWalkingBit(std::uint64_t *pSalt) {
    for (int i = 0; i < S_SALT; i++) {
        pSalt[i] = 1ULL << (i & 63);
    }
}

static void FillPerfectByteSpread(std::uint64_t *pSalt) {
    std::uint8_t *aBytes = reinterpret_cast<std::uint8_t *>(pSalt);

    for (int i = 0; i < S_SALT * static_cast<int>(sizeof(std::uint64_t)); i++) {
        aBytes[i] = static_cast<std::uint8_t>(i & 255);
    }
}

static int ComputeCombinedScore(TwistCryptoScoring &pScorer,
                                const std::uint64_t *pSalt) {
    const int aBitBalance = pScorer.ComputeBitBalance_Salt(pSalt);
    const int aByteSpread = pScorer.ComputeByteSpread_Salt(pSalt);
    const int aXorDrift = pScorer.ComputeXorDrift_Salt(pSalt);
    const int aAdjacencyPenalty = pScorer.ComputeAdjacencyPenalty_Salt(pSalt);

    std::int64_t aScore =
        static_cast<std::int64_t>(aBitBalance * 8) +
        static_cast<std::int64_t>(aByteSpread * 16) +
        static_cast<std::int64_t>(aXorDrift * 4) -
        static_cast<std::int64_t>(aAdjacencyPenalty * 12);

    if (aScore < 0) {
        aScore = 0;
    }

    if (aScore > std::numeric_limits<int>::max()) {
        aScore = std::numeric_limits<int>::max();
    }

    return static_cast<int>(aScore);
}

static int Percentile(std::vector<int> pValues, double pPercentile) {
    std::sort(pValues.begin(), pValues.end());

    if (pValues.empty()) {
        return 0;
    }

    const double aClamped = std::max(0.0, std::min(100.0, pPercentile));
    const double aIndexFloat = (aClamped / 100.0) * static_cast<double>(pValues.size() - 1);
    const size_t aIndex = static_cast<size_t>(aIndexFloat + 0.5);

    return pValues[aIndex];
}

static void PrintDistribution(const char *pName,
                              const std::vector<int> &pValues) {
    if (pValues.empty()) {
        return;
    }

    int aMin = pValues[0];
    int aMax = pValues[0];
    long long aSum = 0;

    for (const int v : pValues) {
        aMin = std::min(aMin, v);
        aMax = std::max(aMax, v);
        aSum += v;
    }

    const double aMean = static_cast<double>(aSum) / static_cast<double>(pValues.size());

    printf("\n%s\n", pName);
    printf("  min   = %d\n", aMin);
    printf("  p01   = %d\n", Percentile(pValues, 1.0));
    printf("  p05   = %d\n", Percentile(pValues, 5.0));
    printf("  p10   = %d\n", Percentile(pValues, 10.0));
    printf("  mean  = %.2f\n", aMean);
    printf("  p50   = %d\n", Percentile(pValues, 50.0));
    printf("  p90   = %d\n", Percentile(pValues, 90.0));
    printf("  p95   = %d\n", Percentile(pValues, 95.0));
    printf("  p99   = %d\n", Percentile(pValues, 99.0));
    printf("  max   = %d\n", aMax);
}

static void PrintOneSalt(const char *pName,
                         TwistCryptoScoring &pScorer,
                         const std::uint64_t *pSalt) {
    const int aBitBalance = pScorer.ComputeBitBalance_Salt(pSalt);
    const int aByteSpread = pScorer.ComputeByteSpread_Salt(pSalt);
    const int aXorDrift = pScorer.ComputeXorDrift_Salt(pSalt);
    const int aAdjacencyPenalty = pScorer.ComputeAdjacencyPenalty_Salt(pSalt);
    const int aCombinedScore = ComputeCombinedScore(pScorer, pSalt);

    printf("\n%s\n", pName);
    printf("  BitBalance       = %d\n", aBitBalance);
    printf("  ByteSpread       = %d\n", aByteSpread);
    printf("  XorDrift         = %d\n", aXorDrift);
    printf("  AdjacencyPenalty = %d\n", aAdjacencyPenalty);
    printf("  CombinedScore    = %d\n", aCombinedScore);
}

static void PrintDistribution(const char *pName,
                              const char *pConstPrefix,
                              const std::vector<int> &pValues) {
    if (pValues.empty()) {
        return;
    }

    int aMin = pValues[0];
    int aMax = pValues[0];
    long long aSum = 0;

    for (const int v : pValues) {
        aMin = std::min(aMin, v);
        aMax = std::max(aMax, v);
        aSum += v;
    }

    const double aMean = static_cast<double>(aSum) / static_cast<double>(pValues.size());

    const int aP01 = Percentile(pValues, 1.0);
    const int aP10 = Percentile(pValues, 10.0);
    const int aP20 = Percentile(pValues, 20.0);
    const int aP40 = Percentile(pValues, 40.0);
    const int aP50 = Percentile(pValues, 50.0);
    const int aP60 = Percentile(pValues, 60.0);
    const int aP80 = Percentile(pValues, 80.0);
    const int aP90 = Percentile(pValues, 90.0);
    const int aP99 = Percentile(pValues, 99.0);

    printf("\n%s\n", pName);
    printf("  min   = %d\n", aMin);
    printf("  p01   = %d\n", aP01);
    printf("  p10   = %d\n", aP10);
    printf("  p20   = %d\n", aP20);
    printf("  p40   = %d\n", aP40);
    printf("  mean  = %.2f\n", aMean);
    printf("  p50   = %d\n", aP50);
    printf("  p60   = %d\n", aP60);
    printf("  p80   = %d\n", aP80);
    printf("  p90   = %d\n", aP90);
    printf("  p99   = %d\n", aP99);
    printf("  max   = %d\n", aMax);

    printf("\n");
    printf("static constexpr int kSalt%sMin  = %d;\n", pConstPrefix, aMin);
    printf("static constexpr int kSalt%sP01  = %d;\n", pConstPrefix, aP01);
    printf("static constexpr int kSalt%sP10  = %d;\n", pConstPrefix, aP10);
    printf("static constexpr int kSalt%sP20  = %d;\n", pConstPrefix, aP20);
    printf("static constexpr int kSalt%sP40  = %d;\n", pConstPrefix, aP40);
    printf("static constexpr int kSalt%sP50  = %d;\n", pConstPrefix, aP50);
    printf("static constexpr int kSalt%sP60  = %d;\n", pConstPrefix, aP60);
    printf("static constexpr int kSalt%sP80  = %d;\n", pConstPrefix, aP80);
    printf("static constexpr int kSalt%sP90  = %d;\n", pConstPrefix, aP90);
    printf("static constexpr int kSalt%sP99  = %d;\n", pConstPrefix, aP99);
    printf("static constexpr int kSalt%sMax  = %d;\n", pConstPrefix, aMax);
    printf("static constexpr int kSalt%sMean = %d;\n", pConstPrefix, static_cast<int>(aMean + 0.5));
}


- (void)testTwistFarmSaltDeriveSixSaltsFromRandomBlock {
    
    std::uint8_t aSource[S_BLOCK];
    
    for (int i = 0; i < S_BLOCK; i++) {
        aSource[i] = Random::GetByte();
    }
    
    TwistFarmSalt aFarmSalt;
    TwistCryptoScoring aScorer;
    
    std::uint64_t aSaltA[S_SALT];
    std::uint64_t aSaltB[S_SALT];
    std::uint64_t aSaltC[S_SALT];
    std::uint64_t aSaltD[S_SALT];
    std::uint64_t aSaltE[S_SALT];
    std::uint64_t aSaltF[S_SALT];
    
    std::memset(aSaltA, 0, sizeof(aSaltA));
    std::memset(aSaltB, 0, sizeof(aSaltB));
    std::memset(aSaltC, 0, sizeof(aSaltC));
    std::memset(aSaltD, 0, sizeof(aSaltD));
    std::memset(aSaltE, 0, sizeof(aSaltE));
    std::memset(aSaltF, 0, sizeof(aSaltF));
    
    aFarmSalt.Derive(aSource,
                     aSaltA,
                     aSaltB,
                     aSaltC,
                     aSaltD,
                     aSaltE,
                     aSaltF);
    
    printf("\n========================================\n");
    printf("TwistFarmSalt::Derive six salts from random S_BLOCK\n");
    printf("S_BLOCK = %d bytes\n", S_BLOCK);
    printf("S_SALT = %d words, salt bytes = %d\n", S_SALT, S_SALT * 8);
    printf("SALT_CANDIDATE_COUNT = %d\n", SALT_CANDIDATE_COUNT);
    printf("========================================\n");
    
    printf("salt,bit_balance,byte_spread,xor_drift,adjacency_penalty,combined_grade\n");
    
    const std::uint64_t *aSalts[6] = {
        aSaltA,
        aSaltB,
        aSaltC,
        aSaltD,
        aSaltE,
        aSaltF
    };
    
    const char *aNames[6] = {
        "A",
        "B",
        "C",
        "D",
        "E",
        "F"
    };
    
    for (int i = 0; i < 6; i++) {
        const std::uint64_t *aSalt = aSalts[i];
        
        const int aBitBalance = aScorer.ComputeBitBalance_Salt(aSalt);
        const int aByteSpread = aScorer.ComputeByteSpread_Salt(aSalt);
        const int aXorDrift = aScorer.ComputeXorDrift_Salt(aSalt);
        const int aAdjacencyPenalty = aScorer.ComputeAdjacencyPenalty_Salt(aSalt);
        const int aCombinedGrade = aScorer.ComputeCombinedSaltGrade(aSalt);
        
        printf("%s,%d,%d,%d,%d,{%d}\n",
               aNames[i],
               aBitBalance,
               aByteSpread,
               aXorDrift,
               aAdjacencyPenalty,
               aCombinedGrade);
    }
}

static void PrintSaltHexArray(const char *pName,
                              const std::uint64_t *pSalt) {
    printf("\n%s = {\n", pName);
    
    for (int i = 0; i < S_SALT; i++) {
        printf("    0x%016llXULL%s\n",
               static_cast<unsigned long long>(pSalt[i]),
               (i == (S_SALT - 1)) ? "" : ",");
    }
    
    printf("};\n");
}

- (void)testSmallExampleWithWeirdNumbers {
    
    static_assert((SALT_CANDIDATE_COUNT * S_SALT * sizeof(std::uint64_t)) == S_BLOCK,
                  "SALT_CANDIDATE_COUNT must exactly cover S_BLOCK.");
    
    std::uint8_t aSource[S_BLOCK];
    std::memset(aSource, 0, sizeof(aSource));
    
    std::uint64_t *aCandidateSalt =
        reinterpret_cast<std::uint64_t *>(aSource);
    
    // First 4 candidates are good random salts.
    for (int aCandidateIndex = 0; aCandidateIndex < 4; aCandidateIndex++) {
        std::uint64_t *aSalt = &(aCandidateSalt[aCandidateIndex * S_SALT]);
        
        for (int i = 0; i < S_SALT; i++) {
            std::uint64_t aWord = 0ULL;
            
            for (int b = 0; b < 8; b++) {
                aWord <<= 8;
                aWord |= static_cast<std::uint64_t>(Random::GetByte());
            }
            
            aSalt[i] = aWord;
        }
    }
    
    // Remaining candidates are bad: each salt is one repeated value.
    for (int aCandidateIndex = 4; aCandidateIndex < SALT_CANDIDATE_COUNT; aCandidateIndex++) {
        std::uint64_t *aSalt = &(aCandidateSalt[aCandidateIndex * S_SALT]);
        
        const std::uint64_t aRepeatedValue =
            0x1111111111111111ULL *
            static_cast<std::uint64_t>((aCandidateIndex & 0xFULL) + 1);
        
        for (int i = 0; i < S_SALT; i++) {
            aSalt[i] = aRepeatedValue;
        }
    }
    
    TwistFarmSalt aFarmSalt;
    TwistCryptoScoring aScorer;
    
    std::uint64_t aSaltA[S_SALT];
    std::uint64_t aSaltB[S_SALT];
    std::uint64_t aSaltC[S_SALT];
    std::uint64_t aSaltD[S_SALT];
    std::uint64_t aSaltE[S_SALT];
    std::uint64_t aSaltF[S_SALT];
    
    std::memset(aSaltA, 0, sizeof(aSaltA));
    std::memset(aSaltB, 0, sizeof(aSaltB));
    std::memset(aSaltC, 0, sizeof(aSaltC));
    std::memset(aSaltD, 0, sizeof(aSaltD));
    std::memset(aSaltE, 0, sizeof(aSaltE));
    std::memset(aSaltF, 0, sizeof(aSaltF));
    
    aFarmSalt.Derive(aSource,
                     aSaltA,
                     aSaltB,
                     aSaltC,
                     aSaltD,
                     aSaltE,
                     aSaltF);
    
    const std::uint64_t *aSelectedSalts[6] = {
        aSaltA,
        aSaltB,
        aSaltC,
        aSaltD,
        aSaltE,
        aSaltF
    };
    
    const char *aSelectedNames[6] = {
        "aSaltA",
        "aSaltB",
        "aSaltC",
        "aSaltD",
        "aSaltE",
        "aSaltF"
    };
    
    printf("\n========================================\n");
    printf("Selected salts from weird-number test\n");
    printf("========================================\n");
    printf("salt,bit_balance,byte_spread,xor_drift,adjacency_penalty,combined_grade\n");
    
    for (int i = 0; i < 6; i++) {
        const std::uint64_t *aSalt = aSelectedSalts[i];
        
        const int aBitBalance = aScorer.ComputeBitBalance_Salt(aSalt);
        const int aByteSpread = aScorer.ComputeByteSpread_Salt(aSalt);
        const int aXorDrift = aScorer.ComputeXorDrift_Salt(aSalt);
        const int aAdjacencyPenalty = aScorer.ComputeAdjacencyPenalty_Salt(aSalt);
        const int aCombinedGrade = aScorer.ComputeCombinedSaltGrade(aSalt);
        
        printf("%s,%d,%d,%d,%d,{%d}\n",
               aSelectedNames[i],
               aBitBalance,
               aByteSpread,
               aXorDrift,
               aAdjacencyPenalty,
               aCombinedGrade);
    }
    
    PrintSaltHexArray("aSaltA", aSaltA);
    PrintSaltHexArray("aSaltB", aSaltB);
    PrintSaltHexArray("aSaltC", aSaltC);
    PrintSaltHexArray("aSaltD", aSaltD);
    PrintSaltHexArray("aSaltE", aSaltE);
    PrintSaltHexArray("aSaltF", aSaltF);
}

- (void)testCombinedSaltGradeComponentSweeps {
    
    TwistCryptoScoring aScorer;
    
    printf("\n========================================\n");
    printf("CombinedSaltGrade component sweep: 100..1200\n");
    printf("========================================\n");
    printf("value,bit_score,bit_flags,byte_score,byte_flags,xor_score,xor_flags,adj_score,adj_flags\n");
    
    for (int v = 100; v <= 1200; v++) {
        int aBitScore = 0;
        int aBitFlags = 0;
        aScorer.ComputeCombinedSaltGrade_Component_BitBalance(v, &aBitScore, &aBitFlags);
        
        int aByteScore = 0;
        int aByteFlags = 0;
        aScorer.ComputeCombinedSaltGrade_Component_ByteSpread(v, &aByteScore, &aByteFlags);
        
        int aXorScore = 0;
        int aXorFlags = 0;
        aScorer.ComputeCombinedSaltGrade_Component_XorDrift(v, &aXorScore, &aXorFlags);
        
        int aAdjScore = 0;
        int aAdjFlags = 0;
        aScorer.ComputeCombinedSaltGrade_Component_AdjacencyPenalty(v, &aAdjScore, &aAdjFlags);
        
        printf("%d\t\t%d,%d\t\t%d,%d\t\t%d,%d\t\t%d,%d\n",
               v,
               aBitScore,
               aBitFlags,
               aByteScore,
               aByteFlags,
               aXorScore,
               aXorFlags,
               aAdjScore,
               aAdjFlags);
    }
}

- (void)testSomeSaltScores {

    static constexpr int kTrialCount = 64;

    TwistCryptoScoring aScorer;
    std::uint64_t aSalt[S_SALT];

    printf("\n========================================\n");
    printf("Random salt scores\n");
    printf("S_SALT = %d words, bytes = %d\n", S_SALT, S_SALT * 8);
    printf("Trials = %d\n", kTrialCount);
    printf("========================================\n");

    printf("index,bit_balance,byte_spread,xor_drift,adjacency_penalty,combined_grade\n");

    for (int aTrialIndex = 0; aTrialIndex < kTrialCount; aTrialIndex++) {
        FillRandomSalt(aSalt);

        const int aBitBalance = aScorer.ComputeBitBalance_Salt(aSalt);
        const int aByteSpread = aScorer.ComputeByteSpread_Salt(aSalt);
        const int aXorDrift = aScorer.ComputeXorDrift_Salt(aSalt);
        const int aAdjacencyPenalty = aScorer.ComputeAdjacencyPenalty_Salt(aSalt);
        const int aCombinedGrade = aScorer.ComputeCombinedSaltGrade(aSalt);

        printf("%d,%d,%d,%d,%d,{%d}\n",
               aTrialIndex,
               aBitBalance,
               aByteSpread,
               aXorDrift,
               aAdjacencyPenalty,
               aCombinedGrade);
    }

    printf("\n========================================\n");
    printf("Outlier / pathological salts\n");
    printf("========================================\n");

    FillAllZero(aSalt);
    PrintOneSalt("All zero", aScorer, aSalt);

    FillAllSame(aSalt, 0xFFFFFFFFFFFFFFFFULL);
    PrintOneSalt("All ones", aScorer, aSalt);

    FillAllSame(aSalt, 0x0123456789ABCDEFULL);
    PrintOneSalt("All same 0x0123456789ABCDEF", aScorer, aSalt);

    FillAlternating(aSalt);
    PrintOneSalt("Alternating 0x55 / 0xAA", aScorer, aSalt);

    FillRepeatingPattern4(aSalt);
    PrintOneSalt("Repeating pattern of 4 words", aScorer, aSalt);

    FillCounter(aSalt);
    PrintOneSalt("Counter words 0, 1, 2, 3...", aScorer, aSalt);

    FillWalkingBit(aSalt);
    PrintOneSalt("Walking bit", aScorer, aSalt);

    FillPerfectByteSpread(aSalt);
    PrintOneSalt("Perfect byte spread 0..255", aScorer, aSalt);
}

@end
