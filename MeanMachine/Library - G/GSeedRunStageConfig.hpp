//
//  GSeedRunStageConfig.hpp
//  MeanMachine
//

#ifndef GSeedRunStageConfig_hpp
#define GSeedRunStageConfig_hpp

#include "GAXSK.hpp"
#include "GSeedProgram.hpp"

#include <cstddef>
#include <initializer_list>
#include <string>
#include <vector>

struct GSeedRunStageSliceSpec {
    GSeedRunStageSliceSpec(std::initializer_list<TwistWorkSpaceSlot> pIngressSources,
                           std::initializer_list<TwistWorkSpaceSlot> pCrossSources,
                           TwistWorkSpaceSlot pDest,
                           bool pDestWriteInverted)
    : mIngressSources(pIngressSources),
      mCrossSources(pCrossSources),
      mDest(pDest),
      mDestWriteInverted(pDestWriteInverted) {
    }

    GSeedRunStageSliceSpec(std::initializer_list<TwistWorkSpaceSlot> pIngressSources,
                           bool pIsLastIngressDirectionLocked,
                           std::initializer_list<TwistWorkSpaceSlot> pCrossSources,
                           bool pIsLastCrossDirectionLocked,
                           TwistWorkSpaceSlot pDest,
                           bool pDestWriteInverted)
    : mIngressSources(pIngressSources),
      mCrossSources(pCrossSources),
      mDest(pDest),
      mDestWriteInverted(pDestWriteInverted),
      mIsLastIngressDirectionLocked(pIsLastIngressDirectionLocked),
      mIsLastCrossDirectionLocked(pIsLastCrossDirectionLocked) {
    }

    std::vector<TwistWorkSpaceSlot> IngressSources() const {
        return mIngressSources;
    }

    std::vector<TwistWorkSpaceSlot> CrossSources() const {
        return mCrossSources;
    }

    std::vector<TwistWorkSpaceSlot>         mIngressSources;
    std::vector<TwistWorkSpaceSlot>         mCrossSources;
    TwistWorkSpaceSlot                      mDest;
    bool                                    mDestWriteInverted;
    bool                                    mIsLastIngressDirectionLocked = false;
    bool                                    mIsLastCrossDirectionLocked = false;
};

struct GSeedRunStageConfig {
    std::string                             mStageName;
    std::string                             mBatchName;
    std::string                             mStartLine;
    std::string                             mEndLine;

    GAXSFormat                              mFormat = GAXSFormat::kInvalid;
    bool                                    mIgnoreNonces = false;
    bool                                    mHasDomainMix = true;
    GAssignType                             mAssignType = GAssignType::kSet;
    TwistDomain                             mDomain = TwistDomain::kInvalid;
    bool                                    mIsNonKDF = true;
    int                                     mExpectedSkeletonCount = 6;
    int                                     mLoopBegin = 0;
    std::string                             mLoopBeginText;
    int                                     mLoopCeiling = S_BLOCK;
    std::string                             mLoopEndText = "S_BLOCK";
    int                                     mHotPackCount = 12;
    bool                                    mAutoRangeAdjust = true;
    bool                                    mEmitLaneFlowComments = true;
    bool                                    mEmitGroupLaneFlowComments = true;
    int                                     mMaxContextSourceCount = 4;
    int                                     mMaxBoundSourceCount = 8;
    int                                     mWarmupDestinationCount = 0;
    bool                                    mBindDuplicateSourceSlots = false;

    std::vector<TwistWorkSpaceSlot>         mSaltsOrbiterAssign;
    std::vector<TwistWorkSpaceSlot>         mSaltsOrbiterUpdate;
    std::vector<TwistWorkSpaceSlot>         mSaltsWandererUpdate;
    std::vector<TwistDomain>                mSliceDomains;
    std::vector<GSeedRunStageSliceSpec>     mSlices;
};

#endif /* GSeedRunStageConfig_hpp */
