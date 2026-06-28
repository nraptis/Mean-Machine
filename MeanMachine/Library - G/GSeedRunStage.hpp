//
//  GSeedRunStage.hpp
//  MeanMachine
//

#ifndef GSeedRunStage_hpp
#define GSeedRunStage_hpp

#include "CSPRNGV2.hpp"
#include "GMagicNumbers.hpp"
#include "GSeedRunStageConfig.hpp"
#include "GTwistExpander.hpp"
#include <cstddef>
#include <cstdio>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct GSeedRunStageSourceBinding {
    std::vector<TwistWorkSpaceSlot>         mSourceSlots;
    GAXSKSourceLayout                       mSourceLayout;
};

class GSeedRunStage {
public:
    explicit GSeedRunStage(GSeedRunStageConfig pConfig)
    : mConfig(std::move(pConfig)) {
        Reset();
    }

    void Reset() {
        mSaltsOrbiterAssign = SymbolsForSlots(mConfig.mSaltsOrbiterAssign);
        mSaltsOrbiterUpdate = SymbolsForSlots(mConfig.mSaltsOrbiterUpdate);
        mSaltsWandererUpdate = SymbolsForSlots(mConfig.mSaltsWandererUpdate);
        mARXSkeletons.clear();
        mHotPacks = GMagicNumbers::GetHotPacks(mConfig.mHotPackCount);
    }

    bool Plan(std::string *pErrorMessage) {
        ClearError(pErrorMessage);

        Reset();

        std::vector<GAXSKSourceLayout> aSourceLayouts;
        std::vector<int> aLaneCounts;
        aSourceLayouts.reserve(mConfig.mSlices.size());
        aLaneCounts.reserve(mConfig.mSlices.size());

        for (std::size_t aIndex = 0U; aIndex < mConfig.mSlices.size(); ++aIndex) {
            GSeedRunStageSourceBinding aBinding;
            if (!BuildSourceBinding(mConfig.mSlices[aIndex],
                                    aIndex,
                                    &aBinding,
                                    pErrorMessage)) {
                return false;
            }

            aSourceLayouts.push_back(aBinding.mSourceLayout);
            aLaneCounts.push_back(static_cast<int>(aBinding.mSourceSlots.size()));
        }

        GAXSK aAXSK;
        if (!aAXSK.Bake(mConfig.mFormat,
                        mConfig.mIgnoreNonces,
                        aLaneCounts,
                        aSourceLayouts,
                        mConfig.mHasDomainMix,
                        mConfig.mAssignType,
                        &mARXSkeletons,
                        pErrorMessage)) {
            if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
                *pErrorMessage = "GAXSK::Bake failed while planning " + mConfig.mStageName;
            }
            return false;
        }

        return true;
    }

    bool Build(TwistProgramBranch &pBranch,
               std::string *pErrorMessage) {
        ClearError(pErrorMessage);

        if (mARXSkeletons.size() != static_cast<std::size_t>(mConfig.mExpectedSkeletonCount)) {
            SetError(pErrorMessage, mConfig.mStageName + " had incorrect GAXSK skeleton counts");
            return false;
        }

        if (mHotPacks.size() < mConfig.mSlices.size()) {
            SetError(pErrorMessage, mConfig.mStageName + " had insufficient hot packs");
            return false;
        }

        if (mARXSkeletons.size() < mConfig.mSlices.size()) {
            SetError(pErrorMessage, mConfig.mStageName + " had fewer skeletons than slices");
            return false;
        }

        if (!mConfig.mStartLine.empty()) {
            pBranch.AddLine(mConfig.mStartLine);
        }

        std::vector<CSPRNGV2Slice> aSlices;
        for (std::size_t aIndex = 0; aIndex < mConfig.mSlices.size(); ++aIndex) {
            const GSeedRunStageSliceSpec &aSpec = mConfig.mSlices[aIndex];

            GSeedRunStageSourceBinding aBinding;
            if (!BuildSourceBinding(aSpec,
                                    aIndex,
                                    &aBinding,
                                    pErrorMessage)) {
                return false;
            }

            CSPRNGV2Slice aSlice = {};
            aSlice.mARXSkeleton = mARXSkeletons[aIndex];
            aSlice.mDest = GSymbol::Buf(aSpec.mDest);
            aSlice.mDestWriteInverted = aSpec.mDestWriteInverted;
            aSlice.mHotPack = mHotPacks[aIndex];
            aSlice.mLoopBegin = mConfig.mLoopBegin;
            aSlice.mLoopBeginText = mConfig.mLoopBeginText;
            aSlice.mLoopCeiling = mConfig.mLoopCeiling;
            aSlice.mLoopEndText = mConfig.mLoopEndText;

            for (TwistWorkSpaceSlot aSlot : aBinding.mSourceSlots) {
                aSlice.mSources.push_back(GSymbol::Buf(aSlot));
            }

            if (aIndex < mConfig.mSliceDomains.size()) {
                const TwistDomain aSliceDomain = mConfig.mSliceDomains[aIndex];
                if (aSliceDomain != TwistDomain::kInvalid) {
                    using Slot = TwistWorkSpaceSlot;
                    aSlice.mDomain = aSliceDomain;
                    aSlice.mSaltsOrbiterAssign = SymbolsForSlots(PhaseSalts(aSliceDomain,
                                                                             Slot::kPhaseASaltOrbiterAssignA,
                                                                             6));
                    aSlice.mSaltsOrbiterUpdate = SymbolsForSlots(PhaseSalts(aSliceDomain,
                                                                            Slot::kPhaseASaltOrbiterUpdateA,
                                                                            6));
                    aSlice.mSaltsWandererUpdate = SymbolsForSlots(PhaseSalts(aSliceDomain,
                                                                              Slot::kPhaseASaltWandererUpdateA,
                                                                              6));
                }
            }

            aSlices.push_back(aSlice);
        }

        std::vector<GLoop> aLoops;
        if (!CSPRNGV2::Bake(mConfig.mIsNonKDF,
                            mConfig.mDomain,
                            aSlices,
                            mSaltsOrbiterAssign,
                            mSaltsOrbiterUpdate,
                            mSaltsWandererUpdate,
                            &aLoops,
                            mConfig.mAutoRangeAdjust,
                            pErrorMessage)) {
            const char *aErrorText = (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "unknown error";
            std::printf("error with CSPRNGV2::Bake %s => %s\n",
                        mConfig.mStageName.c_str(),
                        aErrorText);
            return false;
        }

        GBatch aBatch;
        aBatch.mName = mConfig.mBatchName;
        if (mConfig.mEmitLaneFlowComments &&
            mConfig.mEmitGroupLaneFlowComments &&
            (mConfig.mSlices.size() > 1U)) {
            AddLaneFlowCommentBlock(&aBatch,
                                    mConfig.mStageName + " " + mConfig.mBatchName + " lane group",
                                    CollectGroupReadSlots(),
                                    CollectGroupWriteSlots(),
                                    true);
        }
        for (std::size_t aIndex = 0U; aIndex < aLoops.size(); ++aIndex) {
            GLoop aLoop = aLoops[aIndex];
            if (mConfig.mEmitLaneFlowComments && (aIndex < mConfig.mSlices.size())) {
                const GSeedRunStageSliceSpec &aSpec = mConfig.mSlices[aIndex];
                AddLoopLaneFlowComments(&aLoop,
                                        mConfig.mBatchName + " loop " + std::to_string(aIndex + 1U),
                                        aSpec.IngressSources(),
                                        aSpec.CrossSources(),
                                        { aSpec.mDest });
            }
            aBatch.CommitLoop(aLoop);
        }
        pBranch.AddBatch(aBatch);

        if (!mConfig.mEndLine.empty()) {
            pBranch.AddLine(mConfig.mEndLine);
        }

        return true;
    }

private:
    static void ClearError(std::string *pErrorMessage) {
        if (pErrorMessage != nullptr) {
            pErrorMessage->clear();
        }
    }

    static void SetError(std::string *pErrorMessage,
                         const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }

    static std::vector<GSymbol> SymbolsForSlots(const std::vector<TwistWorkSpaceSlot> &pSlots) {
        std::vector<GSymbol> aResult;
        aResult.reserve(pSlots.size());

        for (TwistWorkSpaceSlot aSlot : pSlots) {
            aResult.push_back(GSymbol::Buf(aSlot));
        }

        return aResult;
    }

    static int PhaseIndex(const TwistDomain pDomain) {
        switch (pDomain) {
            case TwistDomain::kPhaseB: return 1;
            case TwistDomain::kPhaseC: return 2;
            case TwistDomain::kPhaseD: return 3;
            case TwistDomain::kPhaseE: return 4;
            case TwistDomain::kPhaseF: return 5;
            case TwistDomain::kPhaseG: return 6;
            case TwistDomain::kPhaseH: return 7;
            case TwistDomain::kPhaseA:
            default:
                return 0;
        }
    }

    static std::vector<TwistWorkSpaceSlot> PhaseSalts(const TwistDomain pDomain,
                                                       const TwistWorkSpaceSlot pBaseSlot,
                                                       const int pLaneCount) {
        const int aBase = static_cast<int>(pBaseSlot);
        const int aOffset = PhaseIndex(pDomain) * 18;

        std::vector<TwistWorkSpaceSlot> aResult;
        aResult.reserve(static_cast<std::size_t>(pLaneCount));
        for (int i = 0; i < pLaneCount; ++i) {
            aResult.push_back(static_cast<TwistWorkSpaceSlot>(aBase + aOffset + i));
        }
        return aResult;
    }

    static void AppendUniqueSlot(std::vector<TwistWorkSpaceSlot> *pSlots,
                                 const TwistWorkSpaceSlot pSlot) {
        if (pSlots == nullptr) {
            return;
        }
        for (TwistWorkSpaceSlot aSlot : *pSlots) {
            if (aSlot == pSlot) {
                return;
            }
        }
        pSlots->push_back(pSlot);
    }

    static GAXSKSourceKind SourceKindForIndex(const std::size_t pIndex) {
        switch (pIndex) {
            case 0U: return GAXSKSourceKind::kSourceA;
            case 1U: return GAXSKSourceKind::kSourceB;
            case 2U: return GAXSKSourceKind::kSourceC;
            case 3U: return GAXSKSourceKind::kSourceD;
            case 4U: return GAXSKSourceKind::kSourceE;
            case 5U: return GAXSKSourceKind::kSourceF;
            case 6U: return GAXSKSourceKind::kSourceG;
            case 7U: return GAXSKSourceKind::kSourceH;
            case 8U: return GAXSKSourceKind::kSourceI;
            case 9U: return GAXSKSourceKind::kSourceJ;
            default: return GAXSKSourceKind::kInvalid;
        }
    }

    static bool ValidateContextSources(const std::vector<TwistWorkSpaceSlot> &pSources,
                                       const char *pName,
                                       const std::string &pStageName,
                                       const std::string &pBatchName,
                                       const std::size_t pSliceIndex,
                                       const int pMaxSourceCount,
                                       std::string *pErrorMessage) {
        if ((pSources.size() < 2U) || (pSources.size() > static_cast<std::size_t>(pMaxSourceCount))) {
            SetError(pErrorMessage,
                     pStageName + " " + pBatchName +
                     " slice " + std::to_string(pSliceIndex + 1U) +
                     " " + pName + " source count must be between 2 and " +
                     std::to_string(pMaxSourceCount));
            return false;
        }

        return true;
    }

    static bool SourceKindForSlot(const std::vector<TwistWorkSpaceSlot> &pBoundSlots,
                                  const TwistWorkSpaceSlot pSlot,
                                  GAXSKSourceKind *pResult,
                                  std::string *pErrorMessage) {
        if (pResult == nullptr) {
            SetError(pErrorMessage, "GSeedRunStage::SourceKindForSlot received null result");
            return false;
        }

        *pResult = GAXSKSourceKind::kInvalid;
        for (std::size_t aIndex = 0U; aIndex < pBoundSlots.size(); ++aIndex) {
            if (pBoundSlots[aIndex] == pSlot) {
                *pResult = SourceKindForIndex(aIndex);
                break;
            }
        }

        if (*pResult == GAXSKSourceKind::kInvalid) {
            SetError(pErrorMessage, "GSeedRunStage::SourceKindForSlot failed to bind source slot");
            return false;
        }

        return true;
    }

    bool BuildSourceBinding(const GSeedRunStageSliceSpec &pSpec,
                            const std::size_t pSliceIndex,
                            GSeedRunStageSourceBinding *pResult,
                            std::string *pErrorMessage) const {
        if (pResult == nullptr) {
            SetError(pErrorMessage, "GSeedRunStage::BuildSourceBinding received null result");
            return false;
        }

        pResult->mSourceSlots.clear();
        pResult->mSourceLayout.mIngress.clear();
        pResult->mSourceLayout.mCross.clear();

        const std::vector<TwistWorkSpaceSlot> aIngressSources = pSpec.IngressSources();
        const std::vector<TwistWorkSpaceSlot> aCrossSources = pSpec.CrossSources();

        if (!ValidateContextSources(aIngressSources,
                                    "ingress",
                                    mConfig.mStageName,
                                    mConfig.mBatchName,
                                    pSliceIndex,
                                    mConfig.mMaxContextSourceCount,
                                    pErrorMessage)) {
            return false;
        }

        if (!ValidateContextSources(aCrossSources,
                                    "cross",
                                    mConfig.mStageName,
                                    mConfig.mBatchName,
                                    pSliceIndex,
                                    mConfig.mMaxContextSourceCount,
                                    pErrorMessage)) {
            return false;
        }

        if (mConfig.mBindDuplicateSourceSlots) {
            for (TwistWorkSpaceSlot aSlot : aIngressSources) {
                pResult->mSourceSlots.push_back(aSlot);
            }
            for (TwistWorkSpaceSlot aSlot : aCrossSources) {
                pResult->mSourceSlots.push_back(aSlot);
            }
        } else {
            for (TwistWorkSpaceSlot aSlot : aIngressSources) {
                AppendUniqueSlot(&pResult->mSourceSlots, aSlot);
            }
            for (TwistWorkSpaceSlot aSlot : aCrossSources) {
                AppendUniqueSlot(&pResult->mSourceSlots, aSlot);
            }
        }

        if (pResult->mSourceSlots.size() > static_cast<std::size_t>(mConfig.mMaxBoundSourceCount)) {
            SetError(pErrorMessage,
                     mConfig.mStageName + " " + mConfig.mBatchName +
                     " slice " + std::to_string(pSliceIndex + 1U) +
                     " bound more than " + std::to_string(mConfig.mMaxBoundSourceCount) +
                     " input lanes");
            return false;
        }

        if (aIngressSources.size() > static_cast<std::size_t>(mConfig.mMaxContextSourceCount)) {
            SetError(pErrorMessage,
                     mConfig.mStageName + " " + mConfig.mBatchName +
                     " slice " + std::to_string(pSliceIndex + 1U) +
                     " bound more than " + std::to_string(mConfig.mMaxContextSourceCount) +
                     " input lanes (ingress)");
            return false;
        }
        
        if (aCrossSources.size() > static_cast<std::size_t>(mConfig.mMaxContextSourceCount)) {
            SetError(pErrorMessage,
                     mConfig.mStageName + " " + mConfig.mBatchName +
                     " slice " + std::to_string(pSliceIndex + 1U) +
                     " bound more than " + std::to_string(mConfig.mMaxContextSourceCount) +
                     " input lanes (cross)");
            return false;
        }

        if (mConfig.mBindDuplicateSourceSlots) {
            for (std::size_t aIndex = 0U; aIndex < aIngressSources.size(); ++aIndex) {
                const GAXSKSourceKind aSourceKind = SourceKindForIndex(aIndex);
                if (aSourceKind == GAXSKSourceKind::kInvalid) {
                    SetError(pErrorMessage,
                             mConfig.mStageName + " " + mConfig.mBatchName +
                             " failed to bind duplicate ingress source kind");
                    return false;
                }
                pResult->mSourceLayout.mIngress.push_back(aSourceKind);
            }
            for (std::size_t aIndex = 0U; aIndex < aCrossSources.size(); ++aIndex) {
                const GAXSKSourceKind aSourceKind = SourceKindForIndex(aIngressSources.size() + aIndex);
                if (aSourceKind == GAXSKSourceKind::kInvalid) {
                    SetError(pErrorMessage,
                             mConfig.mStageName + " " + mConfig.mBatchName +
                             " failed to bind duplicate cross source kind");
                    return false;
                }
                pResult->mSourceLayout.mCross.push_back(aSourceKind);
            }
        } else {
            for (TwistWorkSpaceSlot aSlot : aIngressSources) {
                GAXSKSourceKind aSourceKind = GAXSKSourceKind::kInvalid;
                if (!SourceKindForSlot(pResult->mSourceSlots,
                                       aSlot,
                                       &aSourceKind,
                                       pErrorMessage)) {
                    return false;
                }
                pResult->mSourceLayout.mIngress.push_back(aSourceKind);
            }

            for (TwistWorkSpaceSlot aSlot : aCrossSources) {
                GAXSKSourceKind aSourceKind = GAXSKSourceKind::kInvalid;
                if (!SourceKindForSlot(pResult->mSourceSlots,
                                       aSlot,
                                       &aSourceKind,
                                       pErrorMessage)) {
                    return false;
                }
                pResult->mSourceLayout.mCross.push_back(aSourceKind);
            }
        }

        return true;
    }

    static std::string AssignSuffix(const GAssignType pAssignType) {
        switch (pAssignType) {
            case GAssignType::kAddAssign: return " (+=)";
            case GAssignType::kXorAssign: return " (^=)";
            case GAssignType::kOrAssign: return " (|=)";
            default: return "";
        }
    }

    static std::string JoinLaneNames(const std::vector<TwistWorkSpaceSlot> &pSlots,
                                     const GAssignType pAssignType = GAssignType::kSet) {
        if (pSlots.empty()) {
            return "(none)";
        }

        std::ostringstream aStream;
        for (std::size_t aIndex = 0U; aIndex < pSlots.size(); ++aIndex) {
            if (aIndex > 0U) {
                aStream << ", ";
            }
            aStream << BufAliasName(pSlots[aIndex]);
            if (pAssignType != GAssignType::kSet) {
                aStream << AssignSuffix(pAssignType);
            }
        }
        return aStream.str();
    }

    static std::string JoinLaneDirections(const std::vector<TwistWorkSpaceSlot> &pSlots,
                                          const bool pIsIngress) {
        if (pSlots.empty()) {
            return "(none)";
        }

        std::ostringstream aStream;
        for (std::size_t aIndex = 0U; aIndex < pSlots.size(); ++aIndex) {
            if (aIndex > 0U) {
                aStream << ", ";
            }

            const bool aIsRandomDirection = (aIndex == (pSlots.size() - 1U));

            aStream << BufAliasName(pSlots[aIndex]) << " ";
            if (aIsRandomDirection) {
                aStream << (pIsIngress ? "forward/backward random" : "backward/forward random");
            } else {
                aStream << (pIsIngress ? "forward forced" : "backward forced");
            }
        }
        return aStream.str();
    }

    std::vector<TwistWorkSpaceSlot> CollectGroupReadSlots() const {
        std::vector<TwistWorkSpaceSlot> aResult;
        for (const GSeedRunStageSliceSpec &aSpec : mConfig.mSlices) {
            for (TwistWorkSpaceSlot aSlot : aSpec.IngressSources()) {
                AppendUniqueSlot(&aResult, aSlot);
            }
            for (TwistWorkSpaceSlot aSlot : aSpec.CrossSources()) {
                AppendUniqueSlot(&aResult, aSlot);
            }
        }
        return aResult;
    }

    std::vector<TwistWorkSpaceSlot> CollectGroupWriteSlots() const {
        std::vector<TwistWorkSpaceSlot> aResult;
        for (const GSeedRunStageSliceSpec &aSpec : mConfig.mSlices) {
            AppendUniqueSlot(&aResult, aSpec.mDest);
        }
        return aResult;
    }

    static std::vector<GStatement> LaneFlowCommentStatements(const std::string &pTitle,
                                                             const std::vector<TwistWorkSpaceSlot> &pReadSlots,
                                                             const std::vector<TwistWorkSpaceSlot> &pWriteSlots,
                                                             const GAssignType pAssignType) {
        std::vector<GStatement> aStatements;
        aStatements.push_back(GStatement::Comment(pTitle));
        aStatements.push_back(GStatement::Comment("read from: " + JoinLaneNames(pReadSlots)));
        aStatements.push_back(GStatement::Comment("write to: " + JoinLaneNames(pWriteSlots, pAssignType)));
        return aStatements;
    }

    void AddLaneFlowCommentBlock(GBatch *pBatch,
                                 const std::string &pTitle,
                                 const std::vector<TwistWorkSpaceSlot> &pReadSlots,
                                 const std::vector<TwistWorkSpaceSlot> &pWriteSlots,
                                 const bool pUseAssignSuffix) const {
        if (pBatch == nullptr) {
            return;
        }
        std::vector<GStatement> aStatements = LaneFlowCommentStatements(
            pTitle,
            pReadSlots,
            pWriteSlots,
            pUseAssignSuffix ? mConfig.mAssignType : GAssignType::kSet);
        pBatch->CommitStatements(&aStatements);
    }

    void AddLoopLaneFlowComments(GLoop *pLoop,
                                 const std::string &pTitle,
                                 const std::vector<TwistWorkSpaceSlot> &pIngressSlots,
                                 const std::vector<TwistWorkSpaceSlot> &pCrossSlots,
                                 const std::vector<TwistWorkSpaceSlot> &pWriteSlots) const {
        if (pLoop == nullptr) {
            return;
        }
        std::vector<GStatement> aStatements;
        aStatements.push_back(GStatement::Comment(pTitle));
        aStatements.push_back(GStatement::Comment("ingress from: " + JoinLaneNames(pIngressSlots)));
        aStatements.push_back(GStatement::Comment("ingress directions: " + JoinLaneDirections(pIngressSlots, true)));
        aStatements.push_back(GStatement::Comment("cross from: " + JoinLaneNames(pCrossSlots)));
        aStatements.push_back(GStatement::Comment("cross directions: " + JoinLaneDirections(pCrossSlots, false)));
        aStatements.push_back(GStatement::Comment("write to: " + JoinLaneNames(pWriteSlots, mConfig.mAssignType)));
        pLoop->mInitializationStatements.insert(pLoop->mInitializationStatements.begin(),
                                                aStatements.begin(),
                                                aStatements.end());
    }

    GSeedRunStageConfig                     mConfig;
    std::vector<GSymbol>                    mSaltsOrbiterAssign;
    std::vector<GSymbol>                    mSaltsOrbiterUpdate;
    std::vector<GSymbol>                    mSaltsWandererUpdate;
    std::vector<GAXSKSkeleton>              mARXSkeletons;
    std::vector<GHotPack>                   mHotPacks;
};

#endif /* GSeedRunStage_hpp */
