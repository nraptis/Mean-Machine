//
//  WeakMixFeeler.m
//  CornTesting
//
//  Created by Dragon on 4/28/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "Random.hpp"
#include "SBoxTables.hpp"
#include "GTwistTwister.hpp"
#include "TwistMix16.hpp"
#include "TwistExpander.hpp"
#include <vector>

@interface WeakMixFeeler : XCTestCase

@end

@implementation WeakMixFeeler

- (void)testWarmUp {

    int aHisto[70000];
    memset(aHisto, 0, sizeof(aHisto));
    
    std::vector<std::uint8_t> aSBoxA = SBoxTables::GetDefaultA();
    std::vector<std::uint8_t> aSBoxB = SBoxTables::GetDefaultB();
    std::vector<std::uint8_t> aSBoxC = SBoxTables::GetDefaultC();
    std::vector<std::uint8_t> aSBoxD = SBoxTables::GetDefaultD();
    
    
    for (int i=0;i<100;i++) {
        
        std::uint16_t aNum = Random::Get(65535);
        
        for (int fun=0;fun<24;fun++) {
            std::uint16_t aEvalA = TwistMix16::Mix161(fun, aNum, aSBoxA.data());
            std::uint16_t aEvalB = TwistMix16::Mix161(fun, aNum, aSBoxB.data());
            std::uint16_t aEvalC = TwistMix16::Mix161(fun, aNum, aSBoxC.data());
            std::uint16_t aEvalD = TwistMix16::Mix161(fun, aNum, aSBoxD.data());
            
            printf("[f=%02d] 0x%04X ==> [0x%04X, 0x%04X, 0x%04X, 0x%04X]\n",
                   fun,
                   aNum,
                   aEvalA,
                   aEvalB,
                   aEvalC,
                   aEvalD);
        }
    }
}

- (void)testMix161Qualityaggy {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(20, (int)aSBoxes.size());
    
    const int MAX = 65536;
    
    struct Aggregate {
        int passCount = 0;
        double worstBit = 100.0;
    };
    
    Aggregate agg[24];
    
    for (int s = 0; s < aLimit; s++) {
        
        const std::vector<std::uint8_t> &aSBox = aSBoxes[s];
        
        printf("\n===== SBOX %02d =====\n", s);
        
        printf("SBox[%02d] head: ", s);
        for (int k = 0; k < 16 && k < (int)aSBox.size(); k++) {
            printf("%02X ", aSBox[k]);
        }
        printf("\n");
        
        for (int fun = 0; fun < 24; fun++) {
            
            double bitAvg[16] = {0};
            
            // --- per-bit avalanche ---
            for (int bit = 0; bit < 16; bit++) {
                
                int avalancheTotal = 0;
                
                for (int x = 0; x < MAX; x++) {
                    
                    std::uint16_t out = TwistMix16::Mix161(fun, x, aSBox.data());
                    
                    std::uint16_t flipped = static_cast<std::uint16_t>(x ^ (1U << bit));
                    std::uint16_t out2 = TwistMix16::Mix161(fun, flipped, aSBox.data());
                    
                    std::uint16_t diff = out ^ out2;
                    avalancheTotal += __builtin_popcount(diff);
                }
                
                bitAvg[bit] = (double)avalancheTotal / MAX;
            }
            
            // --- evaluate ---
            double minBit = 100.0;
            double avgAll = 0.0;
            
            for (int b = 0; b < 16; b++) {
                avgAll += bitAvg[b];
                if (bitAvg[b] < minBit) minBit = bitAvg[b];
            }
            
            avgAll /= 16.0;
            
            printf("fun=%02d | avg=%5.2f | minBit=%5.2f\n", fun, avgAll, minBit);
            
            // --- strict filter ---
            if (minBit >= 5.0) {
                agg[fun].passCount++;
            }
            
            if (minBit < agg[fun].worstBit) {
                agg[fun].worstBit = minBit;
            }
        }
    }
    
    // 🔥 Final survivors
    printf("\n===== SURVIVORS (all bits >= 7.0 across S-boxes) =====\n");
    
    for (int fun = 0; fun < 24; fun++) {
        if (agg[fun].passCount == aLimit) {
            printf("fun=%02d | worstBit=%5.2f\n", fun, agg[fun].worstBit);
        }
    }
}

- (void)testMix161Quality {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(10, (int)aSBoxes.size());
    
    const int MAX = 65536;
    
    for (int s = 0; s < aLimit; s++) {
        
        const std::vector<std::uint8_t> &aSBox = aSBoxes[s];
        
        printf("\n===== SBOX %02d =====\n", s);
        
        printf("\n===== SBOX %02d =====\n", s);

        // print first 16 entries as hex
        printf("SBox[%02d] head: ", s);
        for (int k = 0; k < 16 && k < (int)aSBox.size(); k++) {
            printf("%02X ", aSBox[k]);
        }
        printf("\n");
        
        struct Result {
            int fun;
            int duplicates;
            double avgDiff;
            double score;
        };
        
        std::vector<Result> results;
        
        for (int fun = 0; fun < 24; fun++) {
            
            std::vector<int> freq(MAX, 0);
            
            int duplicates = 0;
            int avalancheTotal = 0;
            
            for (int x = 0; x < MAX; x++) {
                
                std::uint16_t out = TwistMix16::Mix161(fun, x, aSBox.data());
                freq[out]++;
                
                if (freq[out] > 1) {
                    duplicates++;
                }
                
                // avalanche test
                int aBit = 15; // change this manually

                std::uint16_t out2 = TwistMix16::Mix161(fun,
                                                        static_cast<std::uint16_t>(x ^ (1U << aBit)),
                                                        aSBox.data());
                std::uint16_t diff = out ^ out2;
                
                avalancheTotal += __builtin_popcount(diff);
            }
            
            // --- Scores ---
            
            double collisionScore = 100.0 - (duplicates / 655.0);
            if (collisionScore < 0) collisionScore = 0;
            
            double variance = 0.0;
            for (int k = 0; k < MAX; k++) {
                double d = freq[k] - 1.0;
                variance += d * d;
            }
            
            double distributionScore = 100.0 - (variance / 1000.0);
            if (distributionScore < 0) distributionScore = 0;
            
            double avgDiff = (double)avalancheTotal / MAX;
            double avalancheScore = 100.0 - fabs(avgDiff - 8.0) * 10.0;
            if (avalancheScore < 0) avalancheScore = 0;
            
            double finalScore =
            0.4 * collisionScore +
            0.3 * distributionScore +
            0.3 * avalancheScore;
            
            results.push_back({fun, duplicates, avgDiff, finalScore});
        }
        
        // --- Sort best → worst ---
        std::sort(results.begin(), results.end(),
                  [](const Result &a, const Result &b) {
            return a.score > b.score;
        });
        
        // --- Print ranked results ---
        for (const auto &r : results) {
            printf("fun=%02d | dup=%5d | avgDiff=%5.2f | score=%6.2f\n",
                   r.fun,
                   r.duplicates,
                   r.avgDiff,
                   r.score);
        }
    }
}

- (void)testMix162Quality {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(4, (int)aSBoxes.size());
    
    const int MAX = 65536;
    
    for (int s0 = 0; s0 < aLimit; s0++) {
        for (int s1 = 0; s1 < aLimit; s1++) {
            
            const std::vector<std::uint8_t> &aSBoxA = aSBoxes[s0];
            const std::vector<std::uint8_t> &aSBoxB = aSBoxes[s1];
            
            
            
            struct Result {
                int fun;
                int duplicates;
                double avgDiff;
                double score;
            };
            
            std::vector<Result> results;
            
            for (int fun = 0; fun < 48; fun++) {
                
                std::vector<int> freq(MAX, 0);
                
                int duplicates = 0;
                int avalancheTotal = 0;
                
                for (int x = 0; x < MAX; x++) {
                    
                    std::uint16_t out = TwistMix16::Mix162(fun, x, aSBoxA.data(), aSBoxB.data());
                    freq[out]++;
                    
                    if (freq[out] > 1) {
                        duplicates++;
                    }
                    
                    int aBit = 1; // change this manually

                    // avalanche test
                    std::uint16_t out2 = TwistMix16::Mix162(fun,
                                                            static_cast<std::uint16_t>(x ^ (1U << aBit)),
                                                            aSBoxA.data(),
                                                            aSBoxB.data());
                    std::uint16_t diff = out ^ out2;
                    
                    avalancheTotal += __builtin_popcount(diff);
                }
                
                // --- Scores ---
                
                double collisionScore = 100.0 - (duplicates / 655.0);
                if (collisionScore < 0) collisionScore = 0;
                
                double variance = 0.0;
                for (int k = 0; k < MAX; k++) {
                    double d = freq[k] - 1.0;
                    variance += d * d;
                }
                
                double distributionScore = 100.0 - (variance / 1000.0);
                if (distributionScore < 0) distributionScore = 0;
                
                double avgDiff = (double)avalancheTotal / MAX;
                double avalancheScore = 100.0 - fabs(avgDiff - 8.0) * 10.0;
                if (avalancheScore < 0) avalancheScore = 0;
                
                double finalScore =
                0.4 * collisionScore +
                0.3 * distributionScore +
                0.3 * avalancheScore;
                
                results.push_back({fun, duplicates, avgDiff, finalScore});
            }
            
            // --- Sort best → worst ---
            std::sort(results.begin(), results.end(),
                      [](const Result &a, const Result &b) {
                return a.score > b.score;
            });
            
            // --- Print ranked results ---
            for (const auto &r : results) {
                printf("fun=%02d | dup=%5d | avgDiff=%5.2f | score=%6.2f\n",
                       r.fun,
                       r.duplicates,
                       r.avgDiff,
                       r.score);
            }
            
        }
    }
}


- (void)testMix162DeepQuality {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(4, (int)aSBoxes.size());
    
    const int MAX = 65536;
    
    for (int s0 = 0; s0 < aLimit; s0++) {
        for (int s1 = 0; s1 < aLimit; s1++) {
            
            const std::vector<std::uint8_t> &aSBoxA = aSBoxes[s0];
            const std::vector<std::uint8_t> &aSBoxB = aSBoxes[s1];
            
            printf("\n===== SBOX PAIR (%d, %d) =====\n", s0, s1);
            
            struct Result {
                int fun;
                int duplicates;
                double avg1;     // 1-bit avg
                double min1;     // worst 1-bit
                double avg2;     // 2-bit avg
                double score;
            };
            
            std::vector<Result> results;
            
            for (int fun = 0; fun < 48; fun++) {
                
                std::vector<int> freq(MAX, 0);
                
                int duplicates = 0;
                
                double bitSum[16] = {0};
                double bitMin[16];
                
                for (int i = 0; i < 16; i++) bitMin[i] = 100.0;
                
                double twoBitTotal = 0;
                int twoBitCount = 0;
                
                for (int x = 0; x < MAX; x++) {
                    
                    std::uint16_t out = TwistMix16::Mix162(fun, x,
                                                           aSBoxA.data(),
                                                           aSBoxB.data());
                    
                    freq[out]++;
                    if (freq[out] > 1) duplicates++;
                    
                    // -------- 1-BIT AVALANCHE --------
                    for (int bit = 0; bit < 16; bit++) {
                        
                        std::uint16_t flipped =
                        static_cast<std::uint16_t>(x ^ (1U << bit));
                        
                        std::uint16_t out2 =
                        TwistMix16::Mix162(fun, flipped,
                                           aSBoxA.data(),
                                           aSBoxB.data());
                        
                        std::uint16_t diff = out ^ out2;
                        int pc = __builtin_popcount(diff);
                        
                        bitSum[bit] += pc;
                    }
                    
                    // -------- 2-BIT AVALANCHE (sampled) --------
                    for (int bit1 = 0; bit1 < 16; bit1 += 3) {
                        for (int bit2 = bit1 + 1; bit2 < 16; bit2 += 5) {
                            
                            std::uint16_t flipped =
                            static_cast<std::uint16_t>(x ^
                                                      (1U << bit1) ^
                                                      (1U << bit2));
                            
                            std::uint16_t out2 =
                            TwistMix16::Mix162(fun, flipped,
                                               aSBoxA.data(),
                                               aSBoxB.data());
                            
                            std::uint16_t diff = out ^ out2;
                            
                            twoBitTotal += __builtin_popcount(diff);
                            twoBitCount++;
                        }
                    }
                }
                
                // -------- finalize stats --------
                
                double avg1 = 0.0;
                double min1 = 100.0;
                
                for (int bit = 0; bit < 16; bit++) {
                    double v = bitSum[bit] / MAX;
                    avg1 += v;
                    if (v < min1) min1 = v;
                }
                
                avg1 /= 16.0;
                
                double avg2 = twoBitTotal / (double)twoBitCount;
                
                // -------- scoring (balanced) --------
                
                double score =
                (avg1 * 2.0) +          // strong overall diffusion
                (min1 * 4.0) +          // punish weak directions
                (avg2 * 1.5) -          // nonlinear interaction
                (duplicates * 0.001);   // slight penalty
                
                results.push_back({fun, duplicates, avg1, min1, avg2, score});
            }
            
            // -------- sort --------
            
            std::sort(results.begin(), results.end(),
                      [](const Result &a, const Result &b) {
                return a.score > b.score;
            });
            
            // -------- print --------
            
            for (const auto &r : results) {
                printf("fun=%02d | dup=%5d | avg1=%5.2f | min1=%5.2f | avg2=%5.2f | score=%6.2f\n",
                       r.fun,
                       r.duplicates,
                       r.avg1,
                       r.min1,
                       r.avg2,
                       r.score);
            }
            
            // -------- survivors --------
            
            printf("\n--- STRONG SURVIVORS ---\n");
            for (const auto &r : results) {
                if (r.min1 >= 7.2 && r.avg2 >= 7.5) {
                    printf("KEEP fun=%02d (min1=%5.2f avg2=%5.2f)\n",
                           r.fun, r.min1, r.avg2);
                }
            }
        }
    }
}

- (void)testCycleLengths_Mix161 {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(4, (int)aSBoxes.size());
    
    for (int s = 0; s < aLimit; s++) {
        
        const auto &aSBox = aSBoxes[s];
        
        printf("\n===== SBOX %d =====\n", s);
        
        for (int fun = 0; fun < 14; fun++) {
            
            std::uint16_t seed = 0xACE1; // fixed probe
            std::uint16_t x = seed;
            
            int count = 0;
            const int MAX_STEPS = 200000;
            
            do {
                x = TwistMix16::Mix161(fun, x, aSBox.data());
                count++;
                
                if (count >= MAX_STEPS) break;
                
            } while (x != seed);
            
            printf("fun=%02d | cycleLen=%6d\n", fun, count);
        }
    }
}

- (void)testMix161CycleRobustness {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(500, (int)aSBoxes.size());
    
    const int MAX_STEPS = 200000;
    
    int goodCount[24] = {0};
    int badCount[24]  = {0};
    
    for (int s = 0; s < aLimit; s++) {
        
        const auto &aSBox = aSBoxes[s];
        
        for (int fun = 0; fun < 14; fun++) {
            
            std::uint16_t seed = 0xACE1;
            std::uint16_t x = seed;
            
            int count = 0;
            
            do {
                x = TwistMix16::Mix161(fun, x, aSBox.data());
                count++;
                
                if (count >= MAX_STEPS) break;
                
            } while (x != seed);
            
            if (count >= MAX_STEPS) {
                goodCount[fun]++;
            } else {
                badCount[fun]++;
            }
        }
    }
    
    printf("\n===== CYCLE ROBUSTNESS =====\n");
    
    for (int fun = 0; fun < 24; fun++) {
        printf("fun=%02d | good=%4d | bad=%4d | passRate=%5.2f%%\n",
               fun,
               goodCount[fun],
               badCount[fun],
               100.0 * goodCount[fun] / aLimit);
    }
}

- (void)testMix162LinearBiasProbe {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(4, (int)aSBoxes.size());
    
    const int MAX = 65536;
    
    std::uint16_t aInputMasks[] = {
        0x0001, 0x0002, 0x0004, 0x0008,
        0x0010, 0x0020, 0x0040, 0x0080,
        0x0100, 0x0200, 0x0400, 0x0800,
        0x1000, 0x2000, 0x4000, 0x8000,
        0x00FF, 0xFF00, 0x0F0F, 0xF0F0,
        0x3333, 0xCCCC, 0x5555, 0xAAAA,
        0xFFFF
    };
    
    std::uint16_t aOutputMasks[] = {
        0x0001, 0x0002, 0x0004, 0x0008,
        0x0010, 0x0020, 0x0040, 0x0080,
        0x0100, 0x0200, 0x0400, 0x0800,
        0x1000, 0x2000, 0x4000, 0x8000,
        0x00FF, 0xFF00, 0x0F0F, 0xF0F0,
        0x3333, 0xCCCC, 0x5555, 0xAAAA,
        0xFFFF
    };
    
    const int aInputMaskCount = sizeof(aInputMasks) / sizeof(aInputMasks[0]);
    const int aOutputMaskCount = sizeof(aOutputMasks) / sizeof(aOutputMasks[0]);
    
    for (int s0 = 0; s0 < aLimit; s0++) {
        for (int s1 = 0; s1 < aLimit; s1++) {
            
            const std::vector<std::uint8_t> &aSBoxA = aSBoxes[s0];
            const std::vector<std::uint8_t> &aSBoxB = aSBoxes[s1];
            
            printf("\n===== SBOX PAIR (%d, %d) LINEAR BIAS =====\n", s0, s1);
            
            struct Result {
                int fun;
                int maxBias;
                double avgBias;
            };
            
            std::vector<Result> results;
            
            for (int fun = 0; fun < 20; fun++) {
                
                int aMaxBias = 0;
                long long aBiasTotal = 0;
                int aBiasCount = 0;
                
                for (int aInputMaskIndex = 0; aInputMaskIndex < aInputMaskCount; aInputMaskIndex++) {
                    std::uint16_t aInputMask = aInputMasks[aInputMaskIndex];
                    
                    for (int aOutputMaskIndex = 0; aOutputMaskIndex < aOutputMaskCount; aOutputMaskIndex++) {
                        std::uint16_t aOutputMask = aOutputMasks[aOutputMaskIndex];
                        
                        int aCorrelation = 0;
                        
                        for (int x = 0; x < MAX; x++) {
                            
                            std::uint16_t aOut = TwistMix16::Mix162(fun,
                                                                     static_cast<std::uint16_t>(x),
                                                                     aSBoxA.data(),
                                                                     aSBoxB.data());
                            
                            int aInputParity = __builtin_popcount(x & aInputMask) & 1;
                            int aOutputParity = __builtin_popcount(aOut & aOutputMask) & 1;
                            
                            if (aInputParity == aOutputParity) {
                                aCorrelation++;
                            } else {
                                aCorrelation--;
                            }
                        }
                        
                        int aBias = abs(aCorrelation);
                        
                        if (aBias > aMaxBias) {
                            aMaxBias = aBias;
                        }
                        
                        aBiasTotal += aBias;
                        aBiasCount++;
                    }
                }
                
                double aAvgBias = (double)aBiasTotal / (double)aBiasCount;
                results.push_back({fun, aMaxBias, aAvgBias});
            }
            
            std::sort(results.begin(), results.end(),
                      [](const Result &a, const Result &b) {
                if (a.maxBias != b.maxBias) return a.maxBias < b.maxBias;
                return a.avgBias < b.avgBias;
            });
            
            for (const auto &r : results) {
                printf("fun=%02d | maxBias=%5d | avgBias=%8.2f\n",
                       r.fun,
                       r.maxBias,
                       r.avgBias);
            }
        }
    }
}

- (void)testMix162DifferentialProbe {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(4, (int)aSBoxes.size());
    
    const int MAX = 65536;
    
    std::uint16_t aDifferences[] = {
        0x0001, 0x0002, 0x0004, 0x0008,
        0x0010, 0x0020, 0x0040, 0x0080,
        0x0100, 0x0200, 0x0400, 0x0800,
        0x1000, 0x2000, 0x4000, 0x8000,
        0x00FF, 0xFF00, 0x0F0F, 0xF0F0,
        0x3333, 0xCCCC, 0x5555, 0xAAAA,
        0xFFFF
    };
    
    const int aDifferenceCount = sizeof(aDifferences) / sizeof(aDifferences[0]);
    
    for (int s0 = 0; s0 < aLimit; s0++) {
        for (int s1 = 0; s1 < aLimit; s1++) {
            
            const std::vector<std::uint8_t> &aSBoxA = aSBoxes[s0];
            const std::vector<std::uint8_t> &aSBoxB = aSBoxes[s1];
            
            printf("\n===== SBOX PAIR (%d, %d) DIFFERENTIAL =====\n", s0, s1);
            
            struct Result {
                int fun;
                int maxBucket;
                double avgMaxBucket;
            };
            
            std::vector<Result> results;
            
            for (int fun = 0; fun < 20; fun++) {
                
                int aWorstBucket = 0;
                double aBucketTotal = 0.0;
                
                std::vector<int> aFrequency(MAX, 0);
                
                for (int aDifferenceIndex = 0; aDifferenceIndex < aDifferenceCount; aDifferenceIndex++) {
                    
                    std::uint16_t aInputDifference = aDifferences[aDifferenceIndex];
                    
                    std::fill(aFrequency.begin(), aFrequency.end(), 0);
                    
                    for (int x = 0; x < MAX; x++) {
                        
                        std::uint16_t aOutA = TwistMix16::Mix162(fun,
                                                                  static_cast<std::uint16_t>(x),
                                                                  aSBoxA.data(),
                                                                  aSBoxB.data());
                        
                        std::uint16_t aOutB = TwistMix16::Mix162(fun,
                                                                  static_cast<std::uint16_t>(x ^ aInputDifference),
                                                                  aSBoxA.data(),
                                                                  aSBoxB.data());
                        
                        std::uint16_t aOutputDifference = aOutA ^ aOutB;
                        aFrequency[aOutputDifference]++;
                    }
                    
                    int aMaxBucket = 0;
                    for (int k = 0; k < MAX; k++) {
                        if (aFrequency[k] > aMaxBucket) {
                            aMaxBucket = aFrequency[k];
                        }
                    }
                    
                    if (aMaxBucket > aWorstBucket) {
                        aWorstBucket = aMaxBucket;
                    }
                    
                    aBucketTotal += aMaxBucket;
                }
                
                double aAvgMaxBucket = aBucketTotal / (double)aDifferenceCount;
                results.push_back({fun, aWorstBucket, aAvgMaxBucket});
            }
            
            std::sort(results.begin(), results.end(),
                      [](const Result &a, const Result &b) {
                if (a.maxBucket != b.maxBucket) return a.maxBucket < b.maxBucket;
                return a.avgMaxBucket < b.avgMaxBucket;
            });
            
            for (const auto &r : results) {
                printf("fun=%02d | maxBucket=%5d | avgMaxBucket=%8.2f\n",
                       r.fun,
                       r.maxBucket,
                       r.avgMaxBucket);
            }
        }
    }
}

- (void)testMix162CycleRobustness {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    
    const int aSBoxLimit = std::min(500, (int)aSBoxes.size());
    const int MAX_STEPS = 200000;
    
    int aGoodCount[48] = {0};
    int aBadCount[48] = {0};
    int aShortestCycle[48];
    
    for (int fun = 0; fun < 48; fun++) {
        aShortestCycle[fun] = MAX_STEPS;
    }
    
    for (int s = 0; s < aSBoxLimit; s++) {
        
        const std::vector<std::uint8_t> &aSBoxA = aSBoxes[s];
        const std::vector<std::uint8_t> &aSBoxB = aSBoxes[(s + 1) % aSBoxLimit];
        
        for (int fun = 0; fun < 48; fun++) {
            
            std::uint16_t aSeed = 0xACE1;
            std::uint16_t aValue = aSeed;
            
            int aCycleLength = 0;
            
            do {
                aValue = TwistMix16::Mix162(fun,
                                            aValue,
                                            aSBoxA.data(),
                                            aSBoxB.data());
                
                aCycleLength++;
                
                if (aCycleLength >= MAX_STEPS) {
                    break;
                }
                
            } while (aValue != aSeed);
            
            if (aCycleLength >= MAX_STEPS) {
                aGoodCount[fun]++;
            } else {
                aBadCount[fun]++;
                
                if (aCycleLength < aShortestCycle[fun]) {
                    aShortestCycle[fun] = aCycleLength;
                }
            }
        }
    }
    
    printf("\n===== MIX162 CYCLE ROBUSTNESS =====\n");
    
    for (int fun = 0; fun < 48; fun++) {
        
        double aPassRate = 0.0;
        if (aSBoxLimit > 0) {
            aPassRate = 100.0 * (double)aGoodCount[fun] / (double)aSBoxLimit;
        }
        
        printf("fun=%02d | good=%4d | bad=%4d | passRate=%6.2f%% | shortest=%6d\n",
               fun,
               aGoodCount[fun],
               aBadCount[fun],
               aPassRate,
               aShortestCycle[fun]);
    }
}

- (void)testMix162CycleExplore {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(50, (int)aSBoxes.size()); // start smaller
    
    const int MAX_VISIT = 65536; // full state space
    
    for (int s = 0; s < aLimit; s++) {
        
        const auto &aSBoxA = aSBoxes[s];
        const auto &aSBoxB = aSBoxes[(s + 1) % aLimit];
        
        printf("\n===== SBOX PAIR %d =====\n", s);
        
        for (int fun = 0; fun < 48; fun++) {
            
            static bool visited[65536];
            memset(visited, 0, sizeof(visited));
            
            std::uint16_t x = 0xACE1;
            int steps = 0;
            
            while (true) {
                
                if (visited[x]) {
                    // found a loop
                    break;
                }
                
                visited[x] = true;
                
                x = TwistMix16::Mix162(fun, x,
                                       aSBoxA.data(),
                                       aSBoxB.data());
                
                steps++;
                
                if (steps >= MAX_VISIT) {
                    // explored whole reachable space
                    break;
                }
            }
            
            printf("fun=%02d | steps=%6d\n", fun, steps);
        }
    }
}


- (void)testCycleGuesses {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(4, (int)aSBoxes.size());
    
    const int MAX = 65536;
    
    bool aVisit[65536];
    memset(aVisit, 0, sizeof(aVisit));
    
    for (int s0 = 0; s0 < aLimit; s0++) {
        for (int s1 = 0; s1 < aLimit; s1++) {
            
            const std::vector<std::uint8_t> &aSBoxA = aSBoxes[s0];
            const std::vector<std::uint8_t> &aSBoxB = aSBoxes[s1];
            

            
            for (int fun = 0; fun < 48; fun++) {
                
                std::vector<int> freq(MAX, 0);
                
                for (int x = 0; x < MAX; x++) {
                    
                    std::uint16_t aSeeker = x;
                    
                    std::uint16_t aCycleLength = 0;
                    
                    memset(aVisit, 0, sizeof(aVisit));
                    
                    while (aVisit[aSeeker] == false) {
                        
                        
                        aVisit[aSeeker] = true;
                        aSeeker = TwistMix16::Mix162(fun, aSeeker, aSBoxA.data(), aSBoxB.data());
                        
                        
                        aCycleLength++;
                    }
                    
                    printf("cycle was %d\n", aCycleLength);
                }
                
            }
        }
    }
}

- (void)testFixedPointPercent {
    
    std::vector<std::vector<std::uint8_t>> aSBoxes = SBoxTables::Get();
    int aLimit = std::min(4, (int)aSBoxes.size());
    
    const int MAX = 65536;
    
    for (int s0 = 0; s0 < aLimit; s0++) {
        for (int s1 = 0; s1 < aLimit; s1++) {
            
            const std::vector<std::uint8_t> &aSBoxA = aSBoxes[s0];
            const std::vector<std::uint8_t> &aSBoxB = aSBoxes[s1];
            
            printf("\n===== SBOX PAIR %d, %d =====\n", s0, s1);
            
            for (int fun = 0; fun < 48; fun++) {
                
                int fixedCount = 0;
                
                for (int x = 0; x < MAX; x++) {
                    
                    std::uint16_t in = (std::uint16_t)x;
                    std::uint16_t out = TwistMix16::Mix162(fun,
                                                            in,
                                                            aSBoxA.data(),
                                                            aSBoxB.data());
                    
                    if (out == in) {
                        fixedCount++;
                    }
                }
                
                double percent = 100.0 * (double)fixedCount / (double)MAX;
                
                printf("fun=%02d | fixed=%5d | percent=%9.6f%%\n",
                       fun,
                       fixedCount,
                       percent);
            }
        }
    }
}

@end
