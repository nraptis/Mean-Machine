//
//  GSeedRunStageConfig.hpp
//  MeanMachine
//

#ifndef GSeedRunStageConfig_hpp
#define GSeedRunStageConfig_hpp

#include "GAXSK.hpp"
#include "GSeedProgram.hpp"

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

struct GSeedRunStageLaneSplit {
    TwistWorkSpaceSlot                      mSlot = TwistWorkSpaceSlot::kInvalid;
    std::uint8_t                            mLaneSplit = 255U;
};

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

    bool HasSource(TwistWorkSpaceSlot pSlot) const {
        for (TwistWorkSpaceSlot aSlot : mIngressSources) {
            if (aSlot == pSlot) {
                return true;
            }
        }
        for (TwistWorkSpaceSlot aSlot : mCrossSources) {
            if (aSlot == pSlot) {
                return true;
            }
        }
        return false;
    }

    bool SetSourceLaneSplit(TwistWorkSpaceSlot pSlot,
                            std::uint8_t pLaneSplit,
                            std::string *pErrorMessage = nullptr) {
        if (!HasSource(pSlot)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "The lane split slot was not a source of this stage slice";
            }
            return false;
        }
        if (pLaneSplit >= 16U) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "The lane split index must be between A and P";
            }
            return false;
        }
        if (TwistWorkSpace::GetBufferLength(pSlot) != S_BLOCK) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "Only full S_BLOCK lanes can be split into W_KEY fragments";
            }
            return false;
        }

        for (GSeedRunStageLaneSplit &aLink : mSourceLaneSplits) {
            if (aLink.mSlot == pSlot) {
                aLink.mLaneSplit = pLaneSplit;
                return true;
            }
        }

        GSeedRunStageLaneSplit aLink;
        aLink.mSlot = pSlot;
        aLink.mLaneSplit = pLaneSplit;
        mSourceLaneSplits.push_back(aLink);
        return true;
    }

    bool SourceLaneSplit(TwistWorkSpaceSlot pSlot,
                         std::uint8_t *pLaneSplit) const {
        for (const GSeedRunStageLaneSplit &aLink : mSourceLaneSplits) {
            if (aLink.mSlot == pSlot) {
                if (pLaneSplit != nullptr) {
                    *pLaneSplit = aLink.mLaneSplit;
                }
                return true;
            }
        }
        return false;
    }

    std::vector<TwistWorkSpaceSlot>         mIngressSources;
    std::vector<TwistWorkSpaceSlot>         mCrossSources;
    std::vector<GSeedRunStageLaneSplit>     mSourceLaneSplits;
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
    GAssignType                             mAssignType = GAssignType::kSet;
    GAXSKDiffuseKind                        mFixedDiffuse = GAXSKDiffuseKind::kInvalid;
    TwistDomain                             mDomain = TwistDomain::kInvalid;
    bool                                    mIsNonKDF = true;
    int                                     mExpectedSkeletonCount = 6;
    int                                     mLoopBegin = 0;
    std::string                             mLoopBeginText;
    int                                     mLoopCeiling = S_BLOCK;
    std::string                             mLoopEndText = "S_BLOCK";
    int                                     mHotPackCount = 12;
    bool                                    mAutoRangeAdjust = true;
    int                                     mSourceOffsetRangeLo = 0;
    int                                     mSourceOffsetRangeHi = 0;
    bool                                    mEmitLaneFlowComments = true;
    int                                     mMaxContextSourceCount = 4;
    int                                     mMaxBoundSourceCount = 8;
    int                                     mWarmupDestinationCount = 0;
    bool                                    mBindDuplicateSourceSlots = false;
    bool                                    mUsesSpecialSixPassStarterGraph = false;
    bool                                    mUsesSpecialSixPassTwistStarterGraph = false;

    std::vector<TwistWorkSpaceSlot>         mSaltsOrbiterAssign;
    std::vector<TwistWorkSpaceSlot>         mSaltsOrbiterUpdate;
    std::vector<TwistWorkSpaceSlot>         mSaltsWandererUpdate;
    std::vector<TwistDomain>                mSliceDomains;
    std::vector<GSeedRunStageSliceSpec>     mSlices;
};

#endif /* GSeedRunStageConfig_hpp */
