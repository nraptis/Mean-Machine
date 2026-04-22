//
//  TwistSeedBuilder.hpp
//  MeanMachine
//

#ifndef TwistSeedBuilder_hpp
#define TwistSeedBuilder_hpp

#include "GSeedProgram.hpp"

GSymbol VarSymbol(const std::string &pName);

GSymbol BufSymbol(const TwistWorkSpaceSlot pSlot);

struct TwistSeedMutationOptions {
    bool                                mAddSourceConstant = false;
    bool                                mRotateState = false;
    bool                                mUseSaltTerm = false;
    bool                                mBiasLookupIndex = false;
    bool                                mUseCarry = false;
    bool                                mMaskState = false;

    std::uint8_t                        mSourceConstant = 17;
    std::uint8_t                        mRotateAmount = 4;
    std::uint8_t                        mSaltMultiply = 3;
    std::uint8_t                        mLookupBias = 1;
    std::uint8_t                        mCarryBias = 71;
    std::uint8_t                        mStateAdd = 119;
};

struct TwistSeedLoopOptions {
    std::string                         mLoopIndexName = "i";
    std::string                         mStateName = "state";
    std::string                         mMixName = "mix";
    std::string                         mValueName = "value";
    std::string                         mCarryName = "carry_a";

    TwistWorkSpaceSlot                  mSourceSlot = TwistWorkSpaceSlot::kSource;
    TwistWorkSpaceSlot                  mOutputSlot = TwistWorkSpaceSlot::kWorkLaneA;
    TwistWorkSpaceSlot                  mLookupSlot = TwistWorkSpaceSlot::kSBoxA;
    TwistWorkSpaceSlot                  mMaskSlot = TwistWorkSpaceSlot::kSBoxB;
    TwistWorkSpaceSlot                  mSaltSlot = TwistWorkSpaceSlot::kSaltA;

    TwistSeedMutationOptions            mMutations;
};

class TwistSeedBuilder {
public:
    static GLoop                        BuildBaselineLoop(const TwistSeedLoopOptions &pOptions = TwistSeedLoopOptions());
    static GBatch                       BuildBaselineBatch(const TwistSeedLoopOptions &pOptions = TwistSeedLoopOptions());
};

#endif /* TwistSeedBuilder_hpp */
