//
//  CornTesting.m
//  CornTesting
//
//  Created by Magneto on 4/20/26.
//

#import <XCTest/XCTest.h>
#include <vector>
#include "SBoxTables.hpp"
#include "CryptoAnalyzer.hpp"

@interface CornTesting : XCTestCase

@end

@implementation CornTesting

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    
    auto aListOfBoxes = SBoxTables::Get();
    
    CryptoAnalyzer aAnalyzer;
    int aLoops = 0;
    for (auto &aSBox: aListOfBoxes) {
        
        ByteString aByteString(aSBox);
        int aDDTMax = aAnalyzer.ComputeDifferenceDistributionTableMax_256(aByteString);
        int aWalsh = aAnalyzer.ComputeLinearCorrelationMax_256(aByteString);
        int aMinComponentDegree = aAnalyzer.ComputeMinimumComponentAlgebraicDegree_256(aByteString);
        int aMaxComponentDegree = aAnalyzer.ComputeMaximumComponentAlgebraicDegree_256(aByteString);
        int aSacMaxBias = aAnalyzer.ComputeSacMaxBias_256(aByteString);
        double aSacAverageBias = aAnalyzer.ComputeSacAverageBias_256(aByteString);
        int aBicMaxBias = aAnalyzer.ComputeBicMaxBias_256(aByteString);
        double aBicAverageBias = aAnalyzer.ComputeBicAverageBias_256(aByteString);
        
        printf("ddt: %d wal: %d deg: (%d, %d) sac: (%f, %d) bic: (%f, %d) \n", aDDTMax, aWalsh, aMinComponentDegree, aMaxComponentDegree,
               aSacAverageBias, aSacMaxBias,
               aBicAverageBias, aBicMaxBias);
        
        if (++aLoops > 10) { break; }
    }
    
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
