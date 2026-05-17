//
//  GARXTypes.h
//  MeanMachine
//
//  Created by Dragon on 5/15/26.
//

#ifndef GARXTypes_h
#define GARXTypes_h

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_set>

enum class GARXType : std::uint8_t {
    kInv = 0,

    kStreamCurrent = 1,
    kStreamPrevious = 2,
    kStreamScatter = 3,
    kStreamCross = 4,

    kSecretCurrent = 5,
    kSecretPrevious = 6,
    kSecretScatter = 7,
    
    kCarry = 8,

    kUnwindA = 10,
    kUnwindB = 11,
    kUnwindC = 12,
    kUnwindD = 13,
    kUnwindE = 14,
    kUnwindF = 15,
    kUnwindG = 16,
    kUnwindH = 17,
    kUnwindI = 18,
    kUnwindJ = 19,
    kUnwindK = 20,

    kOrbiterA = 30,
    kOrbiterB = 31,
    kOrbiterC = 32,
    kOrbiterD = 33,
    kOrbiterE = 34,
    kOrbiterF = 35,
    kOrbiterG = 36,
    kOrbiterH = 37,
    kOrbiterI = 38,
    kOrbiterJ = 39,
    kOrbiterK = 40
};

struct GARXTypeHash {
    std::size_t operator()(GARXType pType) const { return static_cast<std::size_t>(pType); }
};

struct GARXTypePair {
    GARXType mTypeA;
    GARXType mTypeB;
};

class GARXCrushPairPlan {
public:
    GARXCrushPairPlan();

    GARXType mTypeA;
    GARXType mTypeB;

    bool mRotateA;
    int mRotationAmount;

};

class GARXCrushPlan {
public:
    GARXCrushPlan();

    GARXCrushPairPlan mPairA;
    GARXCrushPairPlan mPairB;
    GARXCrushPairPlan mPairC;
};

class GARXCarryPairPlan {
public:
    GARXCarryPairPlan();

    GARXType mTypeA;
    GARXType mTypeB;

    bool mRotateA;
    int mRotationAmount;
};

class GARXCarryPlan {
public:
    GARXCarryPlan();

    GARXCarryPairPlan mPairA;
    GARXCarryPairPlan mPairB;
    GARXCarryPairPlan mPairC;

    int mSecretCurrentRotation;
    int mMulRotation;
    int mShiftAmount;
};

class GARXBlendInputPlan {
public:
    GARXBlendInputPlan();
    
    int mRotationA;
    int mRotationB;
    int mRotationC;
    int mRotationD;
};

enum class GARXDatumKind : std::uint8_t {
    kInv = 0,
    kType = 1,
    kLoopKey = 2,
    kPlugKey = 3,
    kHotAdd = 4,
    kHotMul = 5
};

struct GARXDatum {
public:
    GARXDatum();
    
    GARXDatumKind                           mKind;
    GARXType                                mType;
    int                                     mOffsetAmount;
    int                                     mRotationAmount;
    GARXType                                mPlugTypeA;
    GARXType                                mPlugTypeB;
    bool                                    mIsLoopIndexInverted;
    int                                     mSaltLaneIndex;
    
};

enum class GARXGroupType : std::uint8_t {
    kInv = 0,
    kSeed = 1,
    kForwardTriplet = 2,
    kCrush = 3,
    kUnwind = 4,
    kCarry = 5
};

#endif /* GARXTypes_h */
