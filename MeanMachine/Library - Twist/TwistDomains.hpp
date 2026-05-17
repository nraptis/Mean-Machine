//
//  TwistDomains.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/7/26.
//

#ifndef TwistDomains_hpp
#define TwistDomains_hpp

#include <cstdint>

enum class TwistDomain : std::uint8_t {
    kInv = 0,
    
    // Fine-grained salt domains.
    kSaltsKeyAUnwind = 10,
    kSaltsKeyAOrbiter = 11,
    kSaltsKeyAOrbiterInit = 12,

    kSaltsKeyBUnwind = 13,
    kSaltsKeyBOrbiter = 14,
    kSaltsKeyBOrbiterInit = 15,

    kSaltsMaskAUnwind = 16,
    kSaltsMaskAOrbiter = 17,
    kSaltsMaskAOrbiterInit = 18,

    kSaltsMaskBUnwind = 19,
    kSaltsMaskBOrbiter = 20,
    kSaltsMaskBOrbiterInit = 21,

    kSaltsWorkLaneUnwind = 22,
    kSaltsWorkLaneOrbiter = 23,
    kSaltsWorkLaneOrbiterInit = 24,

    kSaltsMaskLaneUnwind = 25,
    kSaltsMaskLaneOrbiter = 26,
    kSaltsMaskLaneOrbiterInit = 27,

    kSaltsOperationLaneUnwind = 28,
    kSaltsOperationLaneOrbiter = 29,
    kSaltsOperationLaneOrbiterInit = 30,

    // Fine-grained s-box domains.
    kSBoxesKeyA = 40,
    kSBoxesKeyB = 41,
    kSBoxesMaskA = 42,
    kSBoxesMaskB = 43,
    kSBoxesWorkLane = 44,
    kSBoxesMaskLane = 45,
    kSBoxesOperationLane = 46
};

#endif /* TwistDomains_hpp */
