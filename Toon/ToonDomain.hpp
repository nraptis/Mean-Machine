//
//  ToonDomain.h
//  Valhalla
//
//  Created by Dragon on 5/16/26.
//

#ifndef ToonDomain_h
#define ToonDomain_h

#include "ToonSpace.hpp"
#include <vector>

enum class ToonDomain : std::uint16_t {
    kInvalid = 0x0000,

    kKeyA = 0x0010,
    kKeyB = 0x0020,
    kKeyC = 0x0030,
    kKeyD = 0x0040,

    kWorkLane      = 0x0050,
    kOperationLane = 0x0060,
    kExpansionLane = 0x0070,
};

enum class ToonSaltPhase : std::uint16_t {
    kInvalid = 0,
    kUnwind = 1,
    kOrbiter = 2,
    kOrbiterInit = 3,
};

enum class ToonSaltLane : std::uint16_t {
    kInvalid = 0,

    kA = 1,
    kB = 2,
    kC = 3,
    kD = 4,
    kE = 5,
    kF = 6,
};

enum class ToonSBoxLane : std::uint16_t {
    kInvalid = 0,

    kA = 1,
    kB = 2,
    kC = 3,
    kD = 4,
    kE = 5,
    kF = 6,
    kG = 7,
    kH = 8,
};

enum class ToonSaltOwner : std::uint16_t {
    kInvalid = 0,

    kLocal = 1,
    kInbuilt = 2,
    kEphemeral = 3,
};

enum class ToonSBoxOwner : std::uint16_t {
    kInvalid = 0,

    kLocal = 1,
    kInbuilt = 2,
};

#endif /* ToonDomain_h */
