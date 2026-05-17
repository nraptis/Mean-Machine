//
//  GMoxType.hpp
//  MeanMachine
//
//  Created by Dragon on 5/16/26.
//

#ifndef GMoxType_h
#define GMoxType_h

#pragma once

#include <cstdint>
#include <string>

enum class GMoxRole : std::uint8_t {
    kInvalid = 0,

    kStream,
    kSecret,
    kCarry,

    kOrbiter,
    kWanderer,

    kPlug,
    kLoopSalt,
    kHotAdd,
    kHotMul
};

enum class GMoxStreamKind : std::uint8_t {
    kInvalid = 0,
    kCurrent,
    kPrevious,
    kScatter,
    kCross
};

enum class GMoxSecretKind : std::uint8_t {
    kInvalid = 0,
    kCurrent,
    kPrevious,
    kScatter
};

struct GMoxType {
    GMoxRole role = GMoxRole::kInvalid;
    std::uint8_t index = 0;
    std::uint8_t subkind = 0;

    static GMoxType Stream(GMoxStreamKind kind);
    static GMoxType Secret(GMoxSecretKind kind);
    static GMoxType Carry();

    static GMoxType Orbiter(std::uint8_t index);
    static GMoxType Wanderer(std::uint8_t index);

    bool IsValid() const;
    bool IsOrbiter() const;
    bool IsWanderer() const;
    bool IsHiddenState() const;
    bool IsVisiblePlugInput() const;

    std::string Name() const;
};

#endif /* GMoxType_h */
