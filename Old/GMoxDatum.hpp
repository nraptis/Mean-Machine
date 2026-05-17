//
//  GMoxDatum.hpp
//  MeanMachine
//
//  Created by Dragon on 5/16/26.
//

#ifndef GMoxDatum_hpp
#define GMoxDatum_hpp

#include "GMoxType.hpp"
#include <cstdint>

enum class GMoxDatumKind : std::uint8_t {
    kInvalid = 0,
    kType,
    kLoopKey,
    kPlugKey,
    kHotAdd,
    kHotMul
};

struct GMoxDatum {
    GMoxDatumKind mKind = GMoxDatumKind::kInvalid;

    GMoxType mType;

    int mOffsetAmount = -1;
    int mRotationAmount = -1;
    int mSaltLaneIndex = -1;

    bool mIsLoopIndexInverted = false;

    GMoxType mPlugTypeA;
    GMoxType mPlugTypeB;
};

#endif /* GMoxDatum_hpp */
