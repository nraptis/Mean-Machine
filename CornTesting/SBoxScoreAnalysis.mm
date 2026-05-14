//
//  SBoxScoreAnalysis.m
//  CornTesting
//
//  Created by Dragon on 5/13/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "TwistWorkSpace.hpp"
#include "Random.hpp"
#include "TwistFarmSBox.hpp"
#include "TwistCryptoScoring.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

@interface SBoxScoreAnalysis : XCTestCase
@end

@implementation SBoxScoreAnalysis

static void PrintSBoxTable(const char *pName, const std::uint8_t *pSBox) {
    printf("\n%s table:\n", pName);

    for (int row = 0; row < 16; row++) {
        printf("  ");
        for (int col = 0; col < 16; col++) {
            const int aIndex = row * 16 + col;
            printf("0x%02X", pSBox[aIndex]);

            if (aIndex != 255) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

- (void)testTwistFarmSBoxDeriveEightSBoxesFromRandomBlock {
    
    std::uint8_t aSource[S_BLOCK];
    
    for (int i = 0; i < S_BLOCK; i++) {
        aSource[i] = Random::GetByte();
    }
    
    TwistFarmSBox aFarm;
    TwistCryptoScoring aScorer;
    
    std::uint8_t aSBoxA[S_SBOX];
    std::uint8_t aSBoxB[S_SBOX];
    std::uint8_t aSBoxC[S_SBOX];
    std::uint8_t aSBoxD[S_SBOX];
    std::uint8_t aSBoxE[S_SBOX];
    std::uint8_t aSBoxF[S_SBOX];
    std::uint8_t aSBoxG[S_SBOX];
    std::uint8_t aSBoxH[S_SBOX];
    
    std::memset(aSBoxA, 0, sizeof(aSBoxA));
    std::memset(aSBoxB, 0, sizeof(aSBoxB));
    std::memset(aSBoxC, 0, sizeof(aSBoxC));
    std::memset(aSBoxD, 0, sizeof(aSBoxD));
    std::memset(aSBoxE, 0, sizeof(aSBoxE));
    std::memset(aSBoxF, 0, sizeof(aSBoxF));
    std::memset(aSBoxG, 0, sizeof(aSBoxG));
    std::memset(aSBoxH, 0, sizeof(aSBoxH));
    
    aFarm.Derive(aSource,
                 aSBoxA,
                 aSBoxB,
                 aSBoxC,
                 aSBoxD,
                 aSBoxE,
                 aSBoxF,
                 aSBoxG,
                 aSBoxH);
    
    printf("\n========================================\n");
    printf("TwistFarmSBox::Derive eight S-boxes from random S_BLOCK\n");
    printf("S_BLOCK = %d bytes\n", S_BLOCK);
    printf("S_SBOX = %d bytes\n", S_SBOX);
    printf("SBOX_BYTES_PER_CANDIDATE = %d\n", SBOX_BYTES_PER_CANDIDATE);
    printf("SBOX_CANDIDATE_COUNT = %d\n", SBOX_CANDIDATE_COUNT);
    printf("========================================\n");
    
    printf("sbox,permutation,ddt_max,walsh,sac_avg,sac_max,bic_avg,bic_max,combined_grade\n");
    
    std::uint8_t *aSBoxes[8] = {
        aSBoxA,
        aSBoxB,
        aSBoxC,
        aSBoxD,
        aSBoxE,
        aSBoxF,
        aSBoxG,
        aSBoxH
    };
    
    const char *aNames[8] = {
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H"
    };
    
    
    printf("\n========================================\n");
    printf("Final selected S-box tables\n");
    printf("========================================\n");

    for (int i = 0; i < 8; i++) {
        PrintSBoxTable(aNames[i], aSBoxes[i]);
    }
    
    
    for (int i = 0; i < 8; i++) {
        const std::uint8_t *aSBox = aSBoxes[i];
        
        const bool aPermutation = aScorer.ComputeIsPermutation_SBox(aSBox);
        const std::int32_t aDDTMax = aScorer.ComputeDDTMax_SBox(aSBox);
        const std::int32_t aWalsh = aScorer.ComputeWalsh_SBox(aSBox);
        
        TwistCryptoMaxAverageResponse aSacBias =
            aScorer.ComputeSacBias_SBox(aSBox);
        
        TwistCryptoMaxAverageResponse aBicBias =
            aScorer.ComputeBicBias_SBox(aSBox);
        
        const int aCombinedGrade =
            aScorer.ComputeCombinedSBoxGrade(aSBox);
        
        printf("%s,%d,%d,%d,%.4f,%u,%.4f,%u,{%d}\n",
               aNames[i],
               aPermutation ? 1 : 0,
               aDDTMax,
               aWalsh,
               aSacBias.mAverage,
               aSacBias.mMax,
               aBicBias.mAverage,
               aBicBias.mMax,
               aCombinedGrade);
    }
    
    
}

static void HistogramAddInt(int *pBuckets,
                            int pBucketCount,
                            int pValue) {
    if (pValue < 0) {
        pValue = 0;
    }

    if (pValue >= pBucketCount) {
        pValue = pBucketCount - 1;
    }

    pBuckets[pValue]++;
}

static void HistogramAddFloatFloor(int *pBuckets,
                                   int pBucketCount,
                                   float pValue) {
    int aBucket = static_cast<int>(pValue);

    if (aBucket < 0) {
        aBucket = 0;
    }

    if (aBucket >= pBucketCount) {
        aBucket = pBucketCount - 1;
    }

    pBuckets[aBucket]++;
}

static void PrintHistogramInt(const char *pName,
                              const int *pBuckets,
                              int pBucketCount) {
    printf("\n%s histogram:\n", pName);

    for (int i = 0; i < pBucketCount; i++) {
        if (pBuckets[i] != 0) {
            printf("  %2d : %d\n", i, pBuckets[i]);
        }
    }
}

static void PrintHistogramFloatBuckets(const char *pName,
                                       const int *pBuckets,
                                       int pBucketCount) {
    printf("\n%s histogram floor buckets:\n", pName);

    for (int i = 0; i < pBucketCount; i++) {
        if (pBuckets[i] != 0) {
            printf("  [%2d, %2d) : %d\n", i, i + 1, pBuckets[i]);
        }
    }
}

static int ScoreLowerIsBetterFloat(float pValue,
                                   float pBest,
                                   float pWorst) {
    if (pValue <= pBest) {
        return 100;
    }

    if (pValue >= pWorst) {
        return 0;
    }

    float aT = (pValue - pBest) / (pWorst - pBest);
    int aScore = static_cast<int>((1.0f - aT) * 100.0f + 0.5f);

    if (aScore < 0) {
        aScore = 0;
    }

    if (aScore > 100) {
        aScore = 100;
    }

    return aScore;
}

static int ScoreLowerIsBetterInt(int pValue,
                                 int pBest,
                                 int pWorst) {
    if (pValue <= pBest) {
        return 100;
    }

    if (pValue >= pWorst) {
        return 0;
    }

    float aT = static_cast<float>(pValue - pBest) /
               static_cast<float>(pWorst - pBest);

    int aScore = static_cast<int>((1.0f - aT) * 100.0f + 0.5f);

    if (aScore < 0) {
        aScore = 0;
    }

    if (aScore > 100) {
        aScore = 100;
    }

    return aScore;
}

static int ComputeFourMetricSBoxScore(TwistCryptoMaxAverageResponse pSacBias,
                                      TwistCryptoMaxAverageResponse pBicBias) {
    // These ranges are guesses for analysis.
    // Adjust after seeing the histogram.
    const int aSacAverageScore = ScoreLowerIsBetterFloat(pSacBias.mAverage, 0.0f, 7.0f);
    const int aSacMaxScore     = ScoreLowerIsBetterInt(pSacBias.mMax, 0, 18);

    const int aBicAverageScore = ScoreLowerIsBetterFloat(pBicBias.mAverage, 0.0f, 7.0f);
    const int aBicMaxScore     = ScoreLowerIsBetterInt(pBicBias.mMax, 0, 18);

    return (aSacAverageScore +
            aSacMaxScore +
            aBicAverageScore +
            aBicMaxScore) / 4;
}

- (void)testTwistCryptoScoringSBoxScoreComponentSacAverage {
    TwistCryptoScoring aScorer;

    printf("\n========================================\n");
    printf("SBox SAC average component score test\n");
    printf("========================================\n");

    for (float v = 4.50f; v <= 9.51f; v += 0.01f) {
        int aScore = 0;
        int aRedFlagPoints = 0;

        aScorer.ComputeCombinedSBoxGrade_Component_SacAverage(v,
                                                              &aScore,
                                                              &aRedFlagPoints);

        printf("SAC average %.2f -> score %3d, red flags %d\n",
               v,
               aScore,
               aRedFlagPoints);
    }
}

- (void)testTwistCryptoScoringSBoxScoreComponentSacMax {
    TwistCryptoScoring aScorer;

    printf("\n========================================\n");
    printf("SBox SAC max component score test\n");
    printf("========================================\n");

    for (int v = 8; v <= 24; v += 2) {
        int aScore = 0;
        int aRedFlagPoints = 0;

        aScorer.ComputeCombinedSBoxGrade_Component_SacMax(v,
                                                          &aScore,
                                                          &aRedFlagPoints);

        printf("SAC max %2d -> score %3d, red flags %d\n",
               v,
               aScore,
               aRedFlagPoints);
    }
}

- (void)testTwistCryptoScoringSBoxScoreComponentBicAverage {
    TwistCryptoScoring aScorer;

    printf("\n========================================\n");
    printf("SBox BIC average component score test\n");
    printf("========================================\n");

    for (float v = 5.00f; v <= 8.51f; v += 0.01f) {
        int aScore = 0;
        int aRedFlagPoints = 0;

        aScorer.ComputeCombinedSBoxGrade_Component_BicAverage(v,
                                                              &aScore,
                                                              &aRedFlagPoints);

        printf("BIC average %.2f -> score %3d, red flags %d\n",
               v,
               aScore,
               aRedFlagPoints);
    }
}

- (void)testTwistFarmSBoxCandidateScoreHistogramsWithMaxMaps {
    
    static constexpr float kSacAverageStart = 4.5f;
    static constexpr float kBicAverageStart = 5.0f;
    static constexpr float kAverageStep = 0.1f;
    
    static constexpr int kTargetSBoxCount = 100;
    static constexpr int kSBoxesToAnalyzePerBlock = 64;
    static constexpr int kBlockCount =
        (kTargetSBoxCount + kSBoxesToAnalyzePerBlock - 1) / kSBoxesToAnalyzePerBlock;

    static constexpr int kSacAverageBucketCount = 50;
    static constexpr int kBicAverageBucketCount = 40;

    int aSacAverageHistogram[kSacAverageBucketCount];
    int aBicAverageHistogram[kBicAverageBucketCount];
    int aScoreHistogram[101];

    std::memset(aSacAverageHistogram, 0, sizeof(aSacAverageHistogram));
    std::memset(aBicAverageHistogram, 0, sizeof(aBicAverageHistogram));
    std::memset(aScoreHistogram, 0, sizeof(aScoreHistogram));

    std::unordered_map<std::uint32_t, int> aSacMaxMap;
    std::unordered_map<std::uint32_t, int> aBicMaxMap;

    auto AddFloatTenthBucket = [](int *pBuckets,
                                  int pBucketCount,
                                  float pValue,
                                  float pStart,
                                  float pStep) {
        int aBucket = static_cast<int>((pValue - pStart) / pStep);

        if (aBucket < 0) {
            aBucket = 0;
        }

        if (aBucket >= pBucketCount) {
            aBucket = pBucketCount - 1;
        }

        pBuckets[aBucket]++;
    };

    auto ScoreLowerIsBetterFloat = [](float pValue,
                                      float pBest,
                                      float pWorst) -> int {
        if (pValue <= pBest) {
            return 100;
        }

        if (pValue >= pWorst) {
            return 0;
        }

        float aT = (pValue - pBest) / (pWorst - pBest);
        int aScore = static_cast<int>((1.0f - aT) * 100.0f + 0.5f);

        if (aScore < 0) {
            return 0;
        }

        if (aScore > 100) {
            return 100;
        }

        return aScore;
    };

    auto ScoreLowerIsBetterUInt32 = [](std::uint32_t pValue,
                                       std::uint32_t pBest,
                                       std::uint32_t pWorst) -> int {
        if (pValue <= pBest) {
            return 100;
        }

        if (pValue >= pWorst) {
            return 0;
        }

        float aT =
            static_cast<float>(pValue - pBest) /
            static_cast<float>(pWorst - pBest);

        int aScore = static_cast<int>((1.0f - aT) * 100.0f + 0.5f);

        if (aScore < 0) {
            return 0;
        }

        if (aScore > 100) {
            return 100;
        }

        return aScore;
    };

    auto AddScoreBucket = [](int *pBuckets, int pScore) {
        if (pScore < 0) {
            pScore = 0;
        }

        if (pScore > 100) {
            pScore = 100;
        }

        pBuckets[pScore]++;
    };

    int aTotal = 0;
    int aRejectedNotPermutation = 0;

    int aRejectSacAverage = 0;
    int aRejectSacMax = 0;
    int aRejectBicAverage = 0;
    int aRejectBicMax = 0;

    float aSacAverageMin = 999999.0f;
    float aSacAverageMax = -999999.0f;
    float aBicAverageMin = 999999.0f;
    float aBicAverageMax = -999999.0f;

    std::uint32_t aSacMaxMin = UINT32_MAX;
    std::uint32_t aSacMaxMax = 0;
    std::uint32_t aBicMaxMin = UINT32_MAX;
    std::uint32_t aBicMaxMax = 0;

    double aSacAverageSum = 0.0;
    double aBicAverageSum = 0.0;
    double aSacMaxSum = 0.0;
    double aBicMaxSum = 0.0;
    double aScoreSum = 0.0;

    TwistCryptoScoring aScorer;

    for (int v = 0; (v < kBlockCount) && (aTotal < kTargetSBoxCount); v++) {
        std::uint8_t aSource[S_BLOCK];

        for (int i = 0; i < S_BLOCK; i++) {
            aSource[i] = Random::GetByte();
        }

        TwistFarmSBox aFarm;

        std::uint8_t aSBoxA[S_SBOX];
        std::uint8_t aSBoxB[S_SBOX];
        std::uint8_t aSBoxC[S_SBOX];
        std::uint8_t aSBoxD[S_SBOX];
        std::uint8_t aSBoxE[S_SBOX];
        std::uint8_t aSBoxF[S_SBOX];
        std::uint8_t aSBoxG[S_SBOX];
        std::uint8_t aSBoxH[S_SBOX];

        std::memset(aSBoxA, 0, sizeof(aSBoxA));
        std::memset(aSBoxB, 0, sizeof(aSBoxB));
        std::memset(aSBoxC, 0, sizeof(aSBoxC));
        std::memset(aSBoxD, 0, sizeof(aSBoxD));
        std::memset(aSBoxE, 0, sizeof(aSBoxE));
        std::memset(aSBoxF, 0, sizeof(aSBoxF));
        std::memset(aSBoxG, 0, sizeof(aSBoxG));
        std::memset(aSBoxH, 0, sizeof(aSBoxH));

        aFarm.Derive(aSource,
                     aSBoxA,
                     aSBoxB,
                     aSBoxC,
                     aSBoxD,
                     aSBoxE,
                     aSBoxF,
                     aSBoxG,
                     aSBoxH);

        for (int s = 0;
             (s < kSBoxesToAnalyzePerBlock) && (aTotal < kTargetSBoxCount);
             s++) {
            std::uint8_t *aSBox = aFarm.mCandidateSBox[s];

            if (!aScorer.ComputeIsPermutation_SBox(aSBox)) {
                aRejectedNotPermutation++;
                continue;
            }

            TwistCryptoMaxAverageResponse aSacBias =
                aScorer.ComputeSacBias_SBox(aSBox);

            TwistCryptoMaxAverageResponse aBicBias =
                aScorer.ComputeBicBias_SBox(aSBox);

            AddFloatTenthBucket(aSacAverageHistogram,
                                kSacAverageBucketCount,
                                aSacBias.mAverage,
                                kSacAverageStart,
                                kAverageStep);

            AddFloatTenthBucket(aBicAverageHistogram,
                                kBicAverageBucketCount,
                                aBicBias.mAverage,
                                kBicAverageStart,
                                kAverageStep);

            aSacMaxMap[aSacBias.mMax]++;
            aBicMaxMap[aBicBias.mMax]++;

            const int aSacAverageScore =
                ScoreLowerIsBetterFloat(aSacBias.mAverage, 6.0f, 8.0f);

            const int aSacMaxScore =
                ScoreLowerIsBetterUInt32(aSacBias.mMax, 8U, 18U);

            const int aBicAverageScore =
                ScoreLowerIsBetterFloat(aBicBias.mAverage, 5.0f, 7.0f);

            const int aBicMaxScore =
                ScoreLowerIsBetterUInt32(aBicBias.mMax, 8U, 18U);

            const int aScore =
                (aSacAverageScore +
                 aSacMaxScore +
                 aBicAverageScore +
                 aBicMaxScore) / 4;

            AddScoreBucket(aScoreHistogram, aScore);

            if (aSacBias.mAverage >= 7.0f) {
                aRejectSacAverage++;
            }

            if (aSacBias.mMax > 18U) {
                aRejectSacMax++;
            }

            if (aBicBias.mAverage >= 7.0f) {
                aRejectBicAverage++;
            }

            if (aBicBias.mMax > 18U) {
                aRejectBicMax++;
            }

            aSacAverageMin = std::min(aSacAverageMin, aSacBias.mAverage);
            aSacAverageMax = std::max(aSacAverageMax, aSacBias.mAverage);

            aBicAverageMin = std::min(aBicAverageMin, aBicBias.mAverage);
            aBicAverageMax = std::max(aBicAverageMax, aBicBias.mAverage);

            aSacMaxMin = std::min(aSacMaxMin, aSacBias.mMax);
            aSacMaxMax = std::max(aSacMaxMax, aSacBias.mMax);

            aBicMaxMin = std::min(aBicMaxMin, aBicBias.mMax);
            aBicMaxMax = std::max(aBicMaxMax, aBicBias.mMax);

            aSacAverageSum += aSacBias.mAverage;
            aBicAverageSum += aBicBias.mAverage;
            aSacMaxSum += aSacBias.mMax;
            aBicMaxSum += aBicBias.mMax;
            aScoreSum += aScore;

            aTotal++;
        }
    }

    printf("\n========================================\n");
    printf("SBox candidate score analysis summary\n");
    printf("========================================\n");
    printf("target sboxes: %d\n", kTargetSBoxCount);
    printf("total analyzed permutation sboxes: %d\n", aTotal);
    printf("rejected non-permutation candidates: %d\n", aRejectedNotPermutation);

    if (aTotal > 0) {
        printf("\nSAC average histogram:\n");
        for (int i = 0; i < kSacAverageBucketCount; i++) {
            float aLo = kSacAverageStart + static_cast<float>(i) * kAverageStep;
            float aHi = aLo + kAverageStep;
            printf("  %.1f..<%.1f : %d\n", aLo, aHi, aSacAverageHistogram[i]);
        }

        printf("\nSAC max min/avg/max: %u / %.4f / %u\n",
               aSacMaxMin,
               aSacMaxSum / static_cast<double>(aTotal),
               aSacMaxMax);

        printf("SAC max count map:\n");
        for (std::uint32_t i = 8; i <= 48; i += 2) {
            int aCount = 0;

            auto aFind = aSacMaxMap.find(i);
            if (aFind != aSacMaxMap.end()) {
                aCount = aFind->second;
            }

            printf("  %2u : %d\n", i, aCount);
        }

        printf("\nBIC average histogram:\n");
        for (int i = 0; i < kBicAverageBucketCount; i++) {
            float aLo = kBicAverageStart + static_cast<float>(i) * kAverageStep;
            float aHi = aLo + kAverageStep;
            printf("  %.1f..<%.1f : %d\n", aLo, aHi, aBicAverageHistogram[i]);
        }

        printf("\nBIC max min/avg/max: %u / %.4f / %u\n",
               aBicMaxMin,
               aBicMaxSum / static_cast<double>(aTotal),
               aBicMaxMax);

        printf("BIC max count map:\n");
        for (std::uint32_t i = 8; i <= 48; i += 2) {
            int aCount = 0;

            auto aFind = aBicMaxMap.find(i);
            if (aFind != aBicMaxMap.end()) {
                aCount = aFind->second;
            }

            printf("  %2u : %d\n", i, aCount);
        }

        printf("\nreject-style counts using current gates:\n");
        printf("  SAC average >= 7.0 : %d\n", aRejectSacAverage);
        printf("  SAC max > 18       : %d\n", aRejectSacMax);
        printf("  BIC average >= 7.0 : %d\n", aRejectBicAverage);
        printf("  BIC max > 18       : %d\n", aRejectBicMax);

        printf("\nscore avg: %.4f\n",
               aScoreSum / static_cast<double>(aTotal));
    }

    printf("\n0-100 combined score histogram:\n");
    for (int i = 0; i <= 100; i++) {
        if (aScoreHistogram[i] != 0) {
            printf("  %3d : %d\n", i, aScoreHistogram[i]);
        }
    }

    XCTAssertEqual(aTotal, kTargetSBoxCount);
}


@end
