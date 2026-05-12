//
//  ShuffleTest.m
//  CornTesting
//
//  Created by Dragon on 5/11/26.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#include "TwistWorkSpace.hpp"
#include "Random.hpp"
#include <cctype>
#include <vector>
#include <unordered_map>

#include "TwistIndexShuffle.hpp"
#include "TwistMix64.hpp"

#include <cstdint>
#include <cstddef>
#include <cstring>

static void PrintIndexListVertical(const char *pTitle,
                                   const std::size_t *pIndexList) {
    
    printf("\n%s\n", pTitle);
    printf("-----------------------------\n");
    
    if (pIndexList == nullptr) {
        printf("(null)\n");
        return;
    }
    
    for (std::size_t i = 0; i < 256; i++) {
        printf("[%03zu] %03zu\n", i, pIndexList[i]);
    }
    
    printf("-----------------------------\n\n");
}

bool ContainsAllUniqueIndices(const std::size_t *pIndexList) {
    
    bool aFound[256];
    memset(aFound, 0, sizeof(aFound));

    for (std::size_t i = 0; i < 256; i++) {
        const std::size_t aIndex = pIndexList[i];

        if (aIndex >= 256) {
            return false;
        }

        if (aFound[aIndex]) {
            return false; // duplicate
        }

        aFound[aIndex] = true;
    }

    return true;
}

static void FillSentinelIndices(std::size_t *pIndexList,
                                std::size_t pValue) {
    
    for (std::size_t i = 0; i < 256; i++) {
        pIndexList[i] = pValue;
    }
}

static bool IsIdentityIndexList(const std::size_t *pIndexList) {
    
    if (pIndexList == nullptr) {
        return false;
    }
    
    for (std::size_t i = 0; i < 256; i++) {
        if (pIndexList[i] != i) {
            return false;
        }
    }
    
    return true;
}

static bool IsAllValue(const std::size_t *pIndexList,
                       std::size_t pValue) {
    
    if (pIndexList == nullptr) {
        return false;
    }
    
    for (std::size_t i = 0; i < 256; i++) {
        if (pIndexList[i] != pValue) {
            return false;
        }
    }
    
    return true;
}

#include <cstdio>
#include <cstdint>
#include <cstring>

static std::uint64_t DiffuseA(std::uint64_t pValue) {
    pValue ^= (pValue >> 30);
    pValue *= 0xBF58476D1CE4E5B9ULL;
    pValue ^= (pValue >> 27);
    pValue *= 0x94D049BB133111EBULL;
    pValue ^= (pValue >> 31);
    return pValue;
}

void TestDiffuseALowByteCoverage() {
    
    bool aSeen[256];
    std::memset(aSeen, 0, sizeof(aSeen));
    
    int aUniqueCount = 0;
    
    for (std::uint64_t i = 0; i < 256; i++) {
        std::uint64_t aMixed = DiffuseA(i);
        std::uint8_t aLowByte = static_cast<std::uint8_t>(aMixed & 0xFFU);
        
        if (!aSeen[aLowByte]) {
            aSeen[aLowByte] = true;
            aUniqueCount++;
        }
        
        std::printf("[%03llu] -> 0x%016llX -> low %03u\n",
                    static_cast<unsigned long long>(i),
                    static_cast<unsigned long long>(aMixed),
                    static_cast<unsigned int>(aLowByte));
    }
    
    std::printf("unique low bytes: %d / 256\n", aUniqueCount);
}

@interface ShuffleTest : XCTestCase

@end

@implementation ShuffleTest

- (void)testDiffuseALowByteCoverageForShiftedByteInputs {
    
    const int aShifts[] = {
        0, 8, 16, 24, 32, 40, 48, 56
    };
    
    for (int aShiftIndex = 0; aShiftIndex < 8; aShiftIndex++) {
        
        const int aShift = aShifts[aShiftIndex];
        
        bool aSeen[256];
        std::memset(aSeen, 0, sizeof(aSeen));
        
        int aUniqueCount = 0;
        for (std::uint64_t aNumber = 0; aNumber < 256; aNumber++) {
            
            const std::uint64_t aInput = aNumber << aShift;
            const std::uint64_t aMixed = TwistMix64::DiffuseC(aInput);
            const std::uint8_t aLowByte = static_cast<std::uint8_t>(aMixed & 0xFFULL);
            
            if (aSeen[aLowByte] == false) {
                aSeen[aLowByte] = true;
                aUniqueCount++;
            }
        }
        
        printf("unique low bytes for shift %02d: %d / 256\n",
               aShift,
               aUniqueCount);
        
        printf("\n");
        
        XCTAssertGreaterThan(aUniqueCount,
                             128,
                             @"DiffuseA(number << shift) should produce a healthy low-byte spread");
    }
}

- (void)testWithFailingEntropyReturnsSortedIndicesaaaaa {
    TestDiffuseALowByteCoverage();
    
}

- (void)testWithFailingEntropyReturnsSortedIndices {
    
    std::size_t aIndices[256];
    FillSentinelIndices(aIndices, 9999);
    
    std::uint8_t aEntropyBuffer[S_BLOCK];
    
    /*
     First Fisher-Yates step has remaining == 256, so 255 is valid.
     After that, remaining == 255, and 255 is rejected.
     With all bytes set to 255, the shuffle cannot complete.
     
     Expected contract:
     Execute256 initializes the destination to sorted 0..255,
     then only commits shuffle work if enough entropy is available.
     */
    for (std::size_t i = 0; i < S_BLOCK; i++) {
        aEntropyBuffer[i] = 255;
    }
    
    TwistIndexShuffle::Execute256(aIndices, aEntropyBuffer);
    
    PrintIndexListVertical("Failing entropy / should return sorted identity", aIndices);
    
    XCTAssertTrue(IsIdentityIndexList(aIndices),
                  @"failing entropy should return sorted identity indices");
    
    XCTAssertTrue(ContainsAllUniqueIndices(aIndices),
                  @"sorted identity indices should still be a valid permutation");
}

- (void)testWithAllZeroEntropy {
    
    std::size_t aIndices[256];
    FillSentinelIndices(aIndices, 9999);
    
    std::uint8_t aEntropyBuffer[S_BLOCK];
    
    for (std::size_t i = 0; i < S_BLOCK; i++) {
        aEntropyBuffer[i] = 0;
    }
    
    TwistIndexShuffle::Execute256(aIndices, aEntropyBuffer);
    
    PrintIndexListVertical("All zero entropy", aIndices);
    
    XCTAssertTrue(ContainsAllUniqueIndices(aIndices),
                  @"all-zero entropy should still produce a valid permutation");
    
    /*
     With forward Fisher-Yates and offset 0 every time, this should remain identity.
     That is valid. It is not random, but it is a legal permutation.
     */
    XCTAssertTrue(IsIdentityIndexList(aIndices),
                  @"all-zero entropy should produce identity for offset-based forward shuffle");
}

- (void)testWithAscendingEntropyPattern {
    
    std::size_t aIndices[256];
    FillSentinelIndices(aIndices, 9999);
    
    std::uint8_t aEntropyBuffer[S_BLOCK];
    
    for (std::size_t i = 0; i < S_BLOCK; i++) {
        aEntropyBuffer[i] = static_cast<std::uint8_t>(i & 0xFFU);
    }
    
    TwistIndexShuffle::Execute256(aIndices, aEntropyBuffer);
    
    PrintIndexListVertical("Ascending entropy pattern", aIndices);
    
    XCTAssertTrue(ContainsAllUniqueIndices(aIndices),
                  @"ascending entropy pattern should produce a valid permutation");
}

- (void)testWithDescendingEntropyPattern {
    
    std::size_t aIndices[256];
    FillSentinelIndices(aIndices, 9999);
    
    std::uint8_t aEntropyBuffer[S_BLOCK];
    
    for (std::size_t i = 0; i < S_BLOCK; i++) {
        aEntropyBuffer[i] = static_cast<std::uint8_t>(255U - (i & 0xFFU));
    }
    
    TwistIndexShuffle::Execute256(aIndices, aEntropyBuffer);
    
    PrintIndexListVertical("Descending entropy pattern", aIndices);
    
    XCTAssertTrue(ContainsAllUniqueIndices(aIndices),
                  @"descending entropy pattern should produce a valid permutation");
}

- (void)testWithRandomEntropy {
    
    std::size_t aIndices[256];
    FillSentinelIndices(aIndices, 9999);
    
    std::uint8_t aEntropyBuffer[S_BLOCK];
    
    for (std::size_t i = 0; i < S_BLOCK; i++) {
        aEntropyBuffer[i] = static_cast<std::uint8_t>(Random::Get(0, 256));
    }
    
    TwistIndexShuffle::Execute256(aIndices, aEntropyBuffer);
    
    PrintIndexListVertical("Random entropy", aIndices);
    
    XCTAssertTrue(ContainsAllUniqueIndices(aIndices),
                  @"random entropy should produce a valid permutation");
}

- (void)testWithLowRangeEntropy {
    
    std::size_t aIndices[256];
    FillSentinelIndices(aIndices, 9999);
    
    std::uint8_t aEntropyBuffer[S_BLOCK];
    
    /*
     Values only in 32..223. This is weird but should still usually provide
     enough accepted samples because rejection sampling will skip invalid bytes.
     */
    for (std::size_t i = 0; i < S_BLOCK; i++) {
        aEntropyBuffer[i] = static_cast<std::uint8_t>(Random::Get(32, 224));
    }
    
    TwistIndexShuffle::Execute256(aIndices, aEntropyBuffer);
    
    PrintIndexListVertical("Low-range entropy 32..223", aIndices);
    
    XCTAssertTrue(ContainsAllUniqueIndices(aIndices),
                  @"low-range entropy should still produce a valid permutation if enough samples are accepted");
}

- (void)testWithHighRange {
    
    std::size_t aIndices[256];
    FillSentinelIndices(aIndices, 9999);
    
    std::uint8_t aEntropyBuffer[S_BLOCK];
    
    /*
     Values only in 32..223. This is weird but should still usually provide
     enough accepted samples because rejection sampling will skip invalid bytes.
     */
    for (std::size_t i = 0; i < S_BLOCK; i++) {
        aEntropyBuffer[i] = static_cast<std::uint8_t>(Random::Get(220, 255));
    }
    
    TwistIndexShuffle::Execute256(aIndices, aEntropyBuffer);
    
    PrintIndexListVertical("high-range entropy 225...255", aIndices);
    
    XCTAssertTrue(ContainsAllUniqueIndices(aIndices),
                  @"high-range entropy should still produce a valid permutation if enough samples are accepted");
}



@end
