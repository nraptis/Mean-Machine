#ifndef GMoxPlan_hpp
#define GMoxPlan_hpp

#include <cstdint>
#include <vector>

#include "GMoxDatum.hpp"
#include "GMoxFormat.hpp"
#include "GMoxModel.hpp"
#include "GMoxSkeleton.hpp"
#include "GMoxType.hpp"

enum class GMoxStatementKind : std::uint8_t {
    kInvalid = 0,
    kSeed,
    kForwardLead,
    kForwardFeedback,
    kForwardRotate,
    kCrush,
    kUnwind,
    kCarry,
    kHiddenPlugPrep
};

enum class GMoxGroupKind : std::uint8_t {
    kInvalid = 0,
    kSeed,
    kForwardTriplet,
    kCrush,
    kUnwind,
    kCarry,
    kHiddenPlug
};

struct GMoxBlendPlan {
    int mRotationA = -1;
    int mRotationB = -1;
    int mRotationC = -1;
    int mRotationD = -1;
};

struct GMoxTypePair {
    GMoxType mTypeA;
    GMoxType mTypeB;
};

struct GMoxCrushPairPlan {
    GMoxType mTypeA;
    GMoxType mTypeB;
    bool mRotateA = false;
    int mRotationAmount = -1;
};

struct GMoxCrushPlan {
    GMoxCrushPairPlan mPairA;
    GMoxCrushPairPlan mPairB;
    GMoxCrushPairPlan mPairC;
};

struct GMoxCarryPairPlan {
    GMoxType mTypeA;
    GMoxType mTypeB;
    bool mRotateA = false;
    int mRotationAmount = -1;
};

struct GMoxCarryPlan {
    GMoxCarryPairPlan mPairA;
    GMoxCarryPairPlan mPairB;
    GMoxCarryPairPlan mPairC;

    int mSecretCurrentRotation = -1;
    int mMulRotation = -1;
    int mShiftAmount = -1;
};

class GMoxStatement {
public:
    GMoxStatement() = default;
    GMoxStatement(GMoxStatementKind kind, GMoxType target);

    GMoxStatementKind mKind = GMoxStatementKind::kInvalid;
    GMoxGroupKind mGroupKind = GMoxGroupKind::kInvalid;
    GMoxType mTarget;

    int mRotationAmount = -1;
    std::vector<GMoxDatum> mDatums;
};

class GMoxStatementGroup {
public:
    GMoxStatementGroup() = default;
    explicit GMoxStatementGroup(GMoxGroupKind kind);

    GMoxGroupKind mKind = GMoxGroupKind::kInvalid;
    int mZoneIndex = -1;
    std::vector<GMoxStatement *> mStatements;
};

class GMoxPassPlan {
public:
    ~GMoxPassPlan();

    std::vector<GMoxStatement *> mStatements;
    std::vector<GMoxStatementGroup *> mGroups;

    GMoxBlendPlan mStreamInputBlend;
    GMoxBlendPlan mSecretInputBlend;
    GMoxBlendPlan mCrossInputBlend;

    GMoxBlendPlan mStreamScatterBlend;
    GMoxBlendPlan mSecretScatterBlend;

    GMoxCrushPlan mCrushPlan;
    GMoxCarryPlan mCarryPlan;
};

class GMoxPlan {
public:
    ~GMoxPlan();

    GMoxModel mModel;
    GMoxFormat mFormat;
    GMoxSkeleton mSkeleton;

    std::vector<GMoxPassPlan *> mPasses;
};

#endif /* GMoxPlan_hpp */
