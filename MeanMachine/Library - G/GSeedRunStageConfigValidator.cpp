//
//  GSeedRunStageConfigValidator.cpp
//  MeanMachine
//

#include "GSeedRunStageConfigValidator.hpp"
#include "GSymbol.hpp"

#include <cstddef>
#include <unordered_map>
#include <unordered_set>


namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

bool HasSlot(const std::vector<TwistWorkSpaceSlot> &pSlots,
             const TwistWorkSpaceSlot pSlot) {
    for (TwistWorkSpaceSlot aSlot : pSlots) {
        if (aSlot == pSlot) {
            return true;
        }
    }
    return false;
}

void AppendUniqueSlot(std::vector<TwistWorkSpaceSlot> *pSlots,
                      const TwistWorkSpaceSlot pSlot) {
    if ((pSlots == nullptr) || HasSlot(*pSlots, pSlot)) {
        return;
    }
    pSlots->push_back(pSlot);
}

std::string StagePrefix(const GSeedRunStageConfig &pConfig,
                        const std::size_t pSliceIndex) {
    return pConfig.mStageName + " " + pConfig.mBatchName +
        " slice " + std::to_string(pSliceIndex + 1U) +
        " (slice index = " + std::to_string(pSliceIndex) + ")";
}

bool ValidateContextSources(const GSeedRunStageConfig &pConfig,
                            const std::vector<TwistWorkSpaceSlot> &pSources,
                            const char *pName,
                            const std::size_t pSliceIndex,
                            std::string *pErrorMessage) {
    if ((pSources.size() < 2U) ||
        (pSources.size() > static_cast<std::size_t>(pConfig.mMaxContextSourceCount))) {
        SetError(pErrorMessage,
                 StagePrefix(pConfig, pSliceIndex) + " " +
                 pName + " source count must be between 2 and " +
                 std::to_string(pConfig.mMaxContextSourceCount));
        return false;
    }

    for (std::size_t aIndex = 0U; aIndex < pSources.size(); ++aIndex) {
        if (pSources[aIndex] == TwistWorkSpaceSlot::kInvalid) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, pSliceIndex) + " " +
                     pName + " contained invalid source slot");
            return false;
        }

    }

    return true;
}

bool HasForcedForwardIngressSource(const GSeedRunStageSliceSpec &pSlice,
                                   const TwistWorkSpaceSlot pSlot) {
    const std::vector<TwistWorkSpaceSlot> aIngressSources = pSlice.IngressSources();
    if (aIngressSources.size() < 2U) {
        return false;
    }

    const std::size_t aForcedCount = pSlice.mIsLastIngressDirectionLocked ?
        aIngressSources.size() :
        (aIngressSources.size() - 1U);
    for (std::size_t aIndex = 0U; aIndex < aForcedCount; ++aIndex) {
        if (aIngressSources[aIndex] == pSlot) {
            return true;
        }
    }
    return false;
}

bool ValidatePreviousWriteForward(const GSeedRunStageConfig &pConfig,
                                  std::string *pErrorMessage) {
    for (std::size_t aIndex = 1U; aIndex < pConfig.mSlices.size(); ++aIndex) {
        const TwistWorkSpaceSlot aPreviousWrite = pConfig.mSlices[aIndex - 1U].mDest;
        if (!HasForcedForwardIngressSource(pConfig.mSlices[aIndex], aPreviousWrite)) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, aIndex) +
                     " must force the previous write lane forward on ingress");
            return false;
        }
    }
    return true;
}

bool SlotsEqualAsSet(const std::vector<TwistWorkSpaceSlot> &pLeft,
                     const std::vector<TwistWorkSpaceSlot> &pRight) {
    if (pLeft.size() != pRight.size()) {
        return false;
    }

    for (TwistWorkSpaceSlot aSlot : pLeft) {
        if (!HasSlot(pRight, aSlot)) {
            return false;
        }
    }

    return true;
}

std::vector<TwistWorkSpaceSlot> Destinations(const GSeedRunStageConfig &pConfig) {
    std::vector<TwistWorkSpaceSlot> aResult;
    aResult.reserve(pConfig.mSlices.size());
    for (const GSeedRunStageSliceSpec &aSlice : pConfig.mSlices) {
        aResult.push_back(aSlice.mDest);
    }
    return aResult;
}

std::vector<TwistWorkSpaceSlot> Sources(const GSeedRunStageConfig &pConfig,
                                        const std::vector<TwistWorkSpaceSlot> &pExpectedDestinations) {
    std::vector<TwistWorkSpaceSlot> aResult;
    std::vector<TwistWorkSpaceSlot> aWrittenDestinations;
    for (const GSeedRunStageSliceSpec &aSlice : pConfig.mSlices) {
        for (TwistWorkSpaceSlot aSlot : aSlice.IngressSources()) {
            if (!HasSlot(aWrittenDestinations, aSlot)) {
                AppendUniqueSlot(&aResult, aSlot);
            }
        }
        for (TwistWorkSpaceSlot aSlot : aSlice.CrossSources()) {
            if (!HasSlot(aWrittenDestinations, aSlot)) {
                AppendUniqueSlot(&aResult, aSlot);
            }
        }
        if (HasSlot(pExpectedDestinations, aSlice.mDest)) {
            AppendUniqueSlot(&aWrittenDestinations, aSlice.mDest);
        }
    }
    return aResult;
}

bool ValidateBasicShape(const GSeedRunStageConfig &pConfig,
                        std::string *pErrorMessage) {
    if (pConfig.mSlices.empty()) {
        SetError(pErrorMessage, pConfig.mStageName + " had no slices");
        return false;
    }

    if (pConfig.mExpectedSkeletonCount != static_cast<int>(pConfig.mSlices.size())) {
        SetError(pErrorMessage,
                 pConfig.mStageName + " expected skeleton count did not match slice count");
        return false;
    }

    if (pConfig.mHotPackCount < static_cast<int>(pConfig.mSlices.size())) {
        SetError(pErrorMessage, pConfig.mStageName + " had insufficient hot pack count");
        return false;
    }

    for (std::size_t aIndex = 0U; aIndex < pConfig.mSlices.size(); ++aIndex) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aIndex];
        if (aSlice.mDest == TwistWorkSpaceSlot::kInvalid) {
            SetError(pErrorMessage, StagePrefix(pConfig, aIndex) + " had invalid destination slot");
            return false;
        }

        if (!ValidateContextSources(pConfig,
                                    aSlice.IngressSources(),
                                    "ingress",
                                    aIndex,
                                    pErrorMessage)) {
            return false;
        }

        if (!ValidateContextSources(pConfig,
                                    aSlice.CrossSources(),
                                    "cross",
                                    aIndex,
                                    pErrorMessage)) {
            return false;
        }
    }

    return true;
}

bool ValidateSpecialTwelvePassLoopShape(const GSeedRunStageConfig &pConfig,
                                        const bool pIsSpecialTwelvePassLoop,
                                        std::string *pErrorMessage) {
    int aFiveWideIngressCount = 0;
    int aFiveWideCrossCount = 0;

    for (std::size_t aIndex = 0U; aIndex < pConfig.mSlices.size(); ++aIndex) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aIndex];
        const std::size_t aIngressCount = aSlice.IngressSources().size();
        const std::size_t aCrossCount = aSlice.CrossSources().size();

        if (aIngressCount > 4U) {
            aFiveWideIngressCount += 1;
        }
        if (aCrossCount > 4U) {
            aFiveWideCrossCount += 1;
        }
    }

    if (!pIsSpecialTwelvePassLoop) {
        if ((aFiveWideIngressCount > 0) || (aFiveWideCrossCount > 0)) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " used five-wide sources without special twelve-pass validation");
            return false;
        }
        return true;
    }

    if (pConfig.mSlices.size() != 12U) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " special twelve-pass loop must have exactly 12 slices");
        return false;
    }

    if (aFiveWideIngressCount > 1) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " special twelve-pass loop used more than one five-wide ingress");
        return false;
    }

    if (aFiveWideCrossCount > 1) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " special twelve-pass loop used more than one five-wide cross");
        return false;
    }

    return true;
}

std::string DirectionText(const bool pForward) {
    return pForward ? "forward" : "backward";
}

std::string CombinationText(const std::vector<SlotAndDirection> &pCombination) {
    std::string aResult;
    for (std::size_t aIndex = 0U; aIndex < pCombination.size(); ++aIndex) {
        if (!aResult.empty()) {
            aResult += ", ";
        }
        aResult += BufName(pCombination[aIndex].mSlot);
        aResult += " [";
        aResult += DirectionText(pCombination[aIndex].mForward);
        aResult += "]";
    }
    return aResult;
}

std::vector<std::vector<SlotAndDirection>> StarterPrimaryCombinations(std::vector<TwistWorkSpaceSlot> pSlots) {
    if (pSlots.size() != 3U) {
        return {};
    }

    return {
        {{pSlots[0], true}, {pSlots[1], true}, {pSlots[2], false}},
        {{pSlots[0], true}, {pSlots[1], false}, {pSlots[2], true}},
        {{pSlots[0], false}, {pSlots[1], true}, {pSlots[2], false}},
        {{pSlots[0], false}, {pSlots[1], false}, {pSlots[2], true}},
    };
}

} // namespace

bool GSeedRunStageConfigValidator::IsForcedForward(const GSeedRunStageSliceSpec &pSlice,
                                                   TwistWorkSpaceSlot pSlot) {
    const std::vector<TwistWorkSpaceSlot> aIngressSources = pSlice.IngressSources();
    if (aIngressSources.empty()) {
        return false;
    }

    const std::size_t aForcedCount = pSlice.mIsLastIngressDirectionLocked ?
        aIngressSources.size() :
        aIngressSources.size() - 1U;
    for (std::size_t aIndex = 0U; aIndex < aForcedCount; ++aIndex) {
        if (aIngressSources[aIndex] == pSlot) {
            return true;
        }
    }
    return false;
}

bool GSeedRunStageConfigValidator::IsForcedBackward(const GSeedRunStageSliceSpec &pSlice,
                                                    TwistWorkSpaceSlot pSlot) {
    const std::vector<TwistWorkSpaceSlot> aCrossSources = pSlice.CrossSources();
    if (aCrossSources.empty()) {
        return false;
    }

    const std::size_t aForcedCount = pSlice.mIsLastCrossDirectionLocked ?
        aCrossSources.size() :
        aCrossSources.size() - 1U;
    for (std::size_t aIndex = 0U; aIndex < aForcedCount; ++aIndex) {
        if (aCrossSources[aIndex] == pSlot) {
            return true;
        }
    }
    return false;
}

void GSeedRunStageConfigValidator::AllDirectionCombinationsHelper(std::vector<TwistWorkSpaceSlot> pSlots,
                                                                  std::vector<bool> *pDirections,
                                                                  std::vector<std::vector<SlotAndDirection>> *pResult) {
    
    if ((pDirections == nullptr) || (pResult == nullptr)) {
        return;
    }

    if (pDirections->size() == pSlots.size()) {
        std::vector<SlotAndDirection> aCombination;
        aCombination.reserve(pSlots.size());
        for (std::size_t aIndex = 0U; aIndex < pSlots.size(); ++aIndex) {
            SlotAndDirection aEntry;
            aEntry.mSlot = pSlots[aIndex];
            aEntry.mForward = (*pDirections)[aIndex];
            aCombination.push_back(aEntry);
        }
        pResult->push_back(aCombination);
        return;
    }

    pDirections->push_back(true);
    AllDirectionCombinationsHelper(pSlots, pDirections, pResult);
    pDirections->pop_back();

    pDirections->push_back(false);
    AllDirectionCombinationsHelper(pSlots, pDirections, pResult);
    pDirections->pop_back();
}

std::vector<std::vector<SlotAndDirection>> GSeedRunStageConfigValidator::AllDirectionCombinations(std::vector<TwistWorkSpaceSlot> pSlots) {
    std::vector<bool> aDirections;
    std::vector<std::vector<SlotAndDirection>> aResult;
    AllDirectionCombinationsHelper(pSlots, &aDirections, &aResult);
    return aResult;
}

bool GSeedRunStageConfigValidator::ValidateDestinations(const GSeedRunStageConfig &pConfig,
                                                        std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                        std::string *pErrorMessage) {
    if (pExpectedDestinations.size() != pConfig.mSlices.size()) {
        SetError(pErrorMessage,
                 pConfig.mStageName + " expected destination count did not match slice count");
        return false;
    }

    for (std::size_t aIndex = 0U; aIndex < pConfig.mSlices.size(); ++aIndex) {
        const bool aExpectedInverted = ((aIndex % 2U) == 1U);
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aIndex];

        if (aSlice.mDest != pExpectedDestinations[aIndex]) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, aIndex) +
                     " destination did not match expected destination order");
            return false;
        }

        if (aSlice.mDestWriteInverted != aExpectedInverted) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, aIndex) +
                     " destination inversion pattern did not match false/true alternation");
            return false;
        }
    }

    return true;
}

bool GSeedRunStageConfigValidator::ValidateList(const GSeedRunStageConfig &pConfig,
                                                std::vector<TwistWorkSpaceSlot> pSources,
                                                std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                std::string *pErrorMessage) {
    
    if (!SlotsEqualAsSet(Destinations(pConfig), pExpectedDestinations)) {
        SetError(pErrorMessage,
                 pConfig.mStageName + " destination set did not match expected destinations");
        return false;
    }

    if (!SlotsEqualAsSet(Sources(pConfig, pExpectedDestinations), pSources)) {
        SetError(pErrorMessage,
                 pConfig.mStageName + " external source set did not match expected sources");
        return false;
    }

    return true;
}



bool GSeedRunStageConfigValidator::ValidateStarter(const GSeedRunStageConfig &pConfig,
                                                   std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                   std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                   bool pIsSpecialTwelvePassLoop,
                                                   std::string *pErrorMessage) {
    
    std::vector<TwistWorkSpaceSlot> aSources;
    for (TwistWorkSpaceSlot aSlot : pPrimarySources) {
        AppendUniqueSlot(&aSources, aSlot);
    }
    
    if (!ValidateBasicShape(pConfig, pErrorMessage)) {
        return false;
    }

    if (!ValidateSpecialTwelvePassLoopShape(pConfig,
                                            pIsSpecialTwelvePassLoop,
                                            pErrorMessage)) {
        return false;
    }
    
    if (pPrimarySources.size() > static_cast<std::size_t>(pConfig.mMaxContextSourceCount)) {
        SetError(pErrorMessage,
                 pConfig.mStageName + " starter validation received too many primary sources");
        return false;
    }

    if (!ValidateDestinations(pConfig, pExpectedDestinations, pErrorMessage)) {
        return false;
    }

    if (!ValidateList(pConfig, aSources, pExpectedDestinations, pErrorMessage)) {
        return false;
    }

    if (!ValidateSequencing(pConfig, aSources, pErrorMessage)) {
        return false;
    }

    if (!ValidateSourceGraph(pConfig, aSources, pErrorMessage)) {
        return false;
    }

    if (!ValidatePreviousWriteForward(pConfig, pErrorMessage)) {
        return false;
    }
    
    if (!ValidateImmediatelyUsePreviousDest(pConfig, pErrorMessage)) {
        return false;
    }
    
    if (!ValidateSufficientDestUsage(pConfig,
                                     true,
                                     pErrorMessage)) {
        return false;
    }
    
    if (!ValidateNonRedundancy(pConfig, pErrorMessage)) {
        return false;
    }
    
    if (!ValidatePrimaryCombinations(pConfig, pPrimarySources, pErrorMessage)) {
        return false;
    }
    
    return true;
}

bool GSeedRunStageConfigValidator::ValidateMidstage(const GSeedRunStageConfig &pConfig,
                                                    std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                    std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                    std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                    std::string *pErrorMessage) {
    if (!ValidateBasicShape(pConfig, pErrorMessage)) {
        return false;
    }

    if (!ValidateSpecialTwelvePassLoopShape(pConfig,
                                            false,
                                            pErrorMessage)) {
        return false;
    }
    
    std::vector<TwistWorkSpaceSlot> aSources;
    for (TwistWorkSpaceSlot aSlot : pPrimarySources) {
        AppendUniqueSlot(&aSources, aSlot);
    }
    for (TwistWorkSpaceSlot aSlot : pResidualSources) {
        AppendUniqueSlot(&aSources, aSlot);
    }

    if (!ValidateDestinations(pConfig, pExpectedDestinations, pErrorMessage)) {
        return false;
    }

    if (!ValidateList(pConfig, aSources, pExpectedDestinations, pErrorMessage)) {
        return false;
    }

    if (!ValidateSequencing(pConfig, aSources, pErrorMessage)) {
        return false;
    }

    if (!ValidateSourceGraph(pConfig, aSources, pErrorMessage)) {
        return false;
    }

    if (!ValidateResidualGraph(pConfig, pResidualSources, pErrorMessage)) {
        return false;
    }

    if (!ValidatePreviousWriteForward(pConfig, pErrorMessage)) {
        return false;
    }
    
    if (!ValidateImmediatelyUsePreviousDest(pConfig, pErrorMessage)) {
        return false;
    }
    
    if (!ValidateSufficientDestUsage(pConfig,
                                     true,
                                     pErrorMessage)) {
        return false;
    }
    
    if (!ValidateNonRedundancy(pConfig, pErrorMessage)) {
        return false;
    }

    if (!ValidateMidstageSourceDiversity(pConfig,
                                        pPrimarySources,
                                        pErrorMessage)) {
        return false;
    }
    
    return true;
}

bool GSeedRunStageConfigValidator::ValidateTerminalMidstage(const GSeedRunStageConfig &pConfig,
                                                            std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                            std::vector<TwistWorkSpaceSlot> pResidualSources,
                                                            std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                            std::string *pErrorMessage) {
    if (!ValidateBasicShape(pConfig, pErrorMessage)) {
        return false;
    }

    if (!ValidateSpecialTwelvePassLoopShape(pConfig,
                                            false,
                                            pErrorMessage)) {
        return false;
    }

    std::vector<TwistWorkSpaceSlot> aSources;
    for (TwistWorkSpaceSlot aSlot : pPrimarySources) {
        AppendUniqueSlot(&aSources, aSlot);
    }
    for (TwistWorkSpaceSlot aSlot : pResidualSources) {
        AppendUniqueSlot(&aSources, aSlot);
    }

    if (!ValidateDestinations(pConfig, pExpectedDestinations, pErrorMessage)) {
        return false;
    }

    if (!ValidateList(pConfig, aSources, pExpectedDestinations, pErrorMessage)) {
        return false;
    }

    if (!ValidateSequencing(pConfig, aSources, pErrorMessage)) {
        return false;
    }

    if (!ValidateSourceGraph(pConfig, aSources, pErrorMessage)) {
        return false;
    }

    if (!ValidateResidualGraph(pConfig, pResidualSources, pErrorMessage)) {
        return false;
    }

    if (!ValidateNonRedundancy(pConfig, pErrorMessage)) {
        return false;
    }

    if (!ValidateMidstageSourceDiversity(pConfig,
                                         pPrimarySources,
                                         pErrorMessage)) {
        return false;
    }

    return true;
}


bool GSeedRunStageConfigValidator::ValidateSequencing(const GSeedRunStageConfig &pConfig,
                                                      std::vector<TwistWorkSpaceSlot> pAllSources,
                                                      std::string *pErrorMessage) {
    std::unordered_set<int> aAvailableSources;
    aAvailableSources.reserve(pAllSources.size() + pConfig.mSlices.size());
    for (TwistWorkSpaceSlot aSlot : pAllSources) {
        if (aSlot == TwistWorkSpaceSlot::kInvalid) {
            SetError(pErrorMessage,
                     pConfig.mStageName + " sources contained invalid slot");
            return false;
        }
        aAvailableSources.insert(static_cast<int>(aSlot));
    }

    for (std::size_t aIndex = 0U; aIndex < pConfig.mSlices.size(); ++aIndex) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aIndex];

        for (TwistWorkSpaceSlot aSlot : aSlice.IngressSources()) {
            if (aAvailableSources.find(static_cast<int>(aSlot)) == aAvailableSources.end()) {
                SetError(pErrorMessage,
                         StagePrefix(pConfig, aIndex) +
                         " ingress reads from a lane before it is available");
                return false;
            }
        }

        for (TwistWorkSpaceSlot aSlot : aSlice.CrossSources()) {
            if (aAvailableSources.find(static_cast<int>(aSlot)) == aAvailableSources.end()) {
                SetError(pErrorMessage,
                         StagePrefix(pConfig, aIndex) +
                         " cross reads from a lane before it is available");
                return false;
            }
        }

        aAvailableSources.insert(static_cast<int>(aSlice.mDest));
    }

    return true;
}


bool GSeedRunStageConfigValidator::ValidateImmediatelyUsePreviousDest(const GSeedRunStageConfig &pConfig,
                                                                      std::string *pErrorMessage) {
    
    for (std::size_t aIndex = 1; aIndex < pConfig.mSlices.size(); ++aIndex) {
        const GSeedRunStageSliceSpec &aSlicePrev = pConfig.mSlices[aIndex - 1];
        const GSeedRunStageSliceSpec &aSliceCurr = pConfig.mSlices[aIndex];
        
        if (aSliceCurr.mIngressSources[0] != aSlicePrev.mDest) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, aIndex) +
                     " failed to use previous dest as first source");
            return false;
        }
    }
    
    /*
    for (std::size_t aIndex = 2; aIndex < pConfig.mSlices.size(); ++aIndex) {
        const GSeedRunStageSliceSpec &aSliceBack2 = pConfig.mSlices[aIndex - 2];
        const GSeedRunStageSliceSpec &aSliceCurr = pConfig.mSlices[aIndex];
        
        if (aSliceCurr.mCrossSources[0] != aSliceBack2.mDest) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, aIndex) +
                     " failed to use previous dest as first cross (2 back)");
            return false;
        }
        
    }
    */
    
    return true;
}


bool GSeedRunStageConfigValidator::ValidateSufficientDestUsage(const GSeedRunStageConfig &pConfig,
                                                               const bool pRequireTailReadPressure,
                                                               std::string *pErrorMessage) {
    
    for (std::size_t aIndex = 0U; aIndex < pConfig.mSlices.size(); ++aIndex) {
        if (aIndex < static_cast<std::size_t>(pConfig.mWarmupDestinationCount)) {
            continue;
        }

        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aIndex];
        const TwistWorkSpaceSlot aDest = aSlice.mDest;
        int aUseCount = 0;
        bool aHasForcedForward = false;
        bool aHasForcedBackward = false;
        
        for (std::size_t aUseIndex = aIndex + 1U;
             aUseIndex < pConfig.mSlices.size();
             ++aUseIndex) {
            const GSeedRunStageSliceSpec &aUseSlice = pConfig.mSlices[aUseIndex];
            
            if (HasSlot(aUseSlice.IngressSources(), aDest)) {
                aUseCount += 1;
                aHasForcedForward = aHasForcedForward || IsForcedForward(aUseSlice, aDest);
            }
            
            if (HasSlot(aUseSlice.CrossSources(), aDest)) {
                aUseCount += 1;
                aHasForcedBackward = aHasForcedBackward || IsForcedBackward(aUseSlice, aDest);
            }
        }

        const std::size_t aRemainingPassCount = pConfig.mSlices.size() - aIndex - 1U;
        const int aRequiredUseCount = pRequireTailReadPressure ?
            static_cast<int>((aRemainingPassCount < 3U) ? aRemainingPassCount : 3U) :
            1;
        
        if (aIndex + 1U >= pConfig.mSlices.size()) {
            if (aUseCount != 0) {
                SetError(pErrorMessage,
                         StagePrefix(pConfig, aIndex) +
                         " final destination lane had unexpected future use count");
                return false;
            }
            continue;
        }
        
        if (aUseCount < aRequiredUseCount) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, aIndex) +
                     " destination lane had insufficient later reads: expected " +
                     std::to_string(aRequiredUseCount) +
                     ", found " + std::to_string(aUseCount));
            return false;
        }
        
        const int aDirectionUseCount = pRequireTailReadPressure ? aRequiredUseCount : aUseCount;

        if ((aDirectionUseCount == 1) && !aHasForcedForward) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, aIndex) +
                     " destination lane was used once but was not forced-forward");
            return false;
        }
        
        if ((aDirectionUseCount >= 2) && (!aHasForcedForward || !aHasForcedBackward)) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, aIndex) +
                     " destination lane was used more than once but did not have forced-forward and forced-backward coverage");
            return false;
        }
    }
    
    return true;
}


bool GSeedRunStageConfigValidator::ValidateNonRedundancy(const GSeedRunStageConfig &pConfig,
                                                         std::string *pErrorMessage) {
    if (pConfig.mBindDuplicateSourceSlots) {
        return true;
    }

    for (std::size_t aSliceIndex = 0U; aSliceIndex < pConfig.mSlices.size(); ++aSliceIndex) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aSliceIndex];
        const std::vector<TwistWorkSpaceSlot> aIngressSources = aSlice.IngressSources();
        const std::vector<TwistWorkSpaceSlot> aCrossSources = aSlice.CrossSources();
        
        for (std::size_t aIndex = 0U; aIndex < aIngressSources.size(); ++aIndex) {
            for (std::size_t aOtherIndex = aIndex + 1U;
                 aOtherIndex < aIngressSources.size();
                 ++aOtherIndex) {
                if (aIngressSources[aIndex] == aIngressSources[aOtherIndex]) {
                    SetError(pErrorMessage,
                             StagePrefix(pConfig, aSliceIndex) +
                             " used the same ingress source lane twice");
                    return false;
                }
            }
        }
        
        for (std::size_t aIndex = 0U; aIndex < aCrossSources.size(); ++aIndex) {
            for (std::size_t aOtherIndex = aIndex + 1U;
                 aOtherIndex < aCrossSources.size();
                 ++aOtherIndex) {
                if (aCrossSources[aIndex] == aCrossSources[aOtherIndex]) {
                    SetError(pErrorMessage,
                             StagePrefix(pConfig, aSliceIndex) +
                             " used the same cross source lane twice");
                    return false;
                }
            }
        }
        
        if (aSliceIndex > 0U) {
            for (std::size_t aIngressIndex = 0U;
                 aIngressIndex < aIngressSources.size();
                 ++aIngressIndex) {
                for (std::size_t aCrossIndex = 0U;
                     aCrossIndex < aCrossSources.size();
                     ++aCrossIndex) {
                    const bool aSameLane = (aIngressSources[aIngressIndex] == aCrossSources[aCrossIndex]);
                    const bool aIngressIsRandom = (aIngressIndex == (aIngressSources.size() - 1U)) &&
                        !aSlice.mIsLastIngressDirectionLocked;
                    const bool aCrossIsRandom = (aCrossIndex == (aCrossSources.size() - 1U)) &&
                        !aSlice.mIsLastCrossDirectionLocked;
                    
                    if (aSameLane && (aIngressIsRandom || aCrossIsRandom)) {
                        SetError(pErrorMessage,
                                 StagePrefix(pConfig, aSliceIndex) +
                                 " used the same source lane in a random position");
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

bool GSeedRunStageConfigValidator::ValidateSourceGraph(const GSeedRunStageConfig &pConfig,
                                                       std::vector<TwistWorkSpaceSlot> pSources,
                                                       std::string *pErrorMessage) {
    std::vector<TwistWorkSpaceSlot> aAvailableSources;
    std::unordered_map<int, int> aSourceUseCount;
    for (TwistWorkSpaceSlot aSlot : pSources) {
        if (aSlot == TwistWorkSpaceSlot::kInvalid) {
            SetError(pErrorMessage,
                     pConfig.mStageName + " source graph contained invalid initial source");
            return false;
        }
        AppendUniqueSlot(&aAvailableSources, aSlot);
    }

    auto CountSourceUse = [&](const TwistWorkSpaceSlot pSlot,
                              const std::size_t pSliceIndex) -> bool {
        const int aKey = static_cast<int>(pSlot);
        const int aCount = aSourceUseCount[aKey] + 1;
        aSourceUseCount[aKey] = aCount;
        if (aCount > 4) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, pSliceIndex) +
                     " source graph used " + BufName(pSlot) +
                     " more than 4 times (count = " +
                     std::to_string(aCount) + ")");
            return false;
        }
        return true;
    };

    for (std::size_t aSliceIndex = 0U; aSliceIndex < pConfig.mSlices.size(); ++aSliceIndex) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aSliceIndex];
        const std::vector<TwistWorkSpaceSlot> aIngressSources = aSlice.IngressSources();
        const std::vector<TwistWorkSpaceSlot> aCrossSources = aSlice.CrossSources();
        const std::size_t aSourceCount = aAvailableSources.size();

        std::vector<TwistWorkSpaceSlot> aSliceReadSources;

        for (TwistWorkSpaceSlot aSlot : aIngressSources) {
            if (!HasSlot(aAvailableSources, aSlot)) {
                SetError(pErrorMessage,
                         StagePrefix(pConfig, aSliceIndex) +
                         " source graph ingress read before source was available");
                return false;
            }
            aSliceReadSources.push_back(aSlot);
        }

        for (TwistWorkSpaceSlot aSlot : aCrossSources) {
            if (!HasSlot(aAvailableSources, aSlot)) {
                SetError(pErrorMessage,
                         StagePrefix(pConfig, aSliceIndex) +
                         " source graph cross read before source was available");
                return false;
            }
            aSliceReadSources.push_back(aSlot);
        }

        if (aSourceCount < 2U) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, aSliceIndex) +
                     " source graph requires at least 2 available sources");
            return false;
        }

        if (aSourceCount == 2U) {
            const bool aMatchesTwoSourceShape =
                (aIngressSources.size() == 2U) &&
                (aCrossSources.size() == 2U) &&
                (aCrossSources[0] == aIngressSources[1]) &&
                (aCrossSources[1] == aIngressSources[0]);

            if (!aMatchesTwoSourceShape) {
                SetError(pErrorMessage,
                         StagePrefix(pConfig, aSliceIndex) +
                         " source graph with 2 available sources must use ingress [a, b], cross [b, a]");
                return false;
            }
        } else if (aSourceCount == 3U) {
            const bool aMatchesThreeSourceShape =
                (aIngressSources.size() == 2U) &&
                (aCrossSources.size() == 2U) &&
                (aCrossSources[0] == aIngressSources[0]) &&
                (aCrossSources[1] != aIngressSources[0]) &&
                (aCrossSources[1] != aIngressSources[1]);

            if (!aMatchesThreeSourceShape) {
                SetError(pErrorMessage,
                         StagePrefix(pConfig, aSliceIndex) +
                         " source graph with 3 available sources must use ingress [a, b], cross [a, c]");
                return false;
            }
        } else {
            std::vector<TwistWorkSpaceSlot> aSeenSources;
            for (TwistWorkSpaceSlot aSlot : aIngressSources) {
                if (HasSlot(aSeenSources, aSlot)) {
                    SetError(pErrorMessage,
                             StagePrefix(pConfig, aSliceIndex) +
                             " source graph used a duplicate source with 4 or more available sources");
                    return false;
                }
                AppendUniqueSlot(&aSeenSources, aSlot);
            }

            for (TwistWorkSpaceSlot aSlot : aCrossSources) {
                if (HasSlot(aSeenSources, aSlot)) {
                    SetError(pErrorMessage,
                             StagePrefix(pConfig, aSliceIndex) +
                             " source graph used a duplicate source with 4 or more available sources");
                    return false;
                }
                AppendUniqueSlot(&aSeenSources, aSlot);
            }
        }

        if (aSourceCount < 4U) {
            std::vector<TwistWorkSpaceSlot> aUniqueSliceReadSources;
            for (TwistWorkSpaceSlot aSlot : aSliceReadSources) {
                AppendUniqueSlot(&aUniqueSliceReadSources, aSlot);
            }

            for (TwistWorkSpaceSlot aSlot : aUniqueSliceReadSources) {
                if (!CountSourceUse(aSlot, aSliceIndex)) {
                    return false;
                }
            }
        } else {
            for (TwistWorkSpaceSlot aSlot : aSliceReadSources) {
                if (!CountSourceUse(aSlot, aSliceIndex)) {
                    return false;
                }
            }
        }

        AppendUniqueSlot(&aAvailableSources, aSlice.mDest);
    }

    return true;
}

bool GSeedRunStageConfigValidator::ValidateResidualGraph(const GSeedRunStageConfig &pConfig,
                                                         std::vector<TwistWorkSpaceSlot> pResiduals,
                                                         std::string *pErrorMessage) {
    if (pResiduals.empty()) {
        return true;
    }

    const std::size_t aMaxResidualCount = pConfig.mSlices.size() * 2U;
    if (pResiduals.size() > aMaxResidualCount) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " residual graph had more residual sources than available random source slots");
        return false;
    }

    std::unordered_set<int> aExpectedResiduals;
    for (TwistWorkSpaceSlot aResidual : pResiduals) {
        if (aResidual == TwistWorkSpaceSlot::kInvalid) {
            SetError(pErrorMessage,
                     pConfig.mStageName + " residual graph contained invalid residual source");
            return false;
        }

        const int aResidualKey = static_cast<int>(aResidual);
        if (aExpectedResiduals.find(aResidualKey) != aExpectedResiduals.end()) {
            SetError(pErrorMessage,
                     pConfig.mStageName + " residual graph contained duplicate residual source");
            return false;
        }
        aExpectedResiduals.insert(aResidualKey);
    }

    std::unordered_set<int> aDiscoveredResiduals;
    for (std::size_t aSliceIndex = 0U; aSliceIndex < pConfig.mSlices.size(); ++aSliceIndex) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aSliceIndex];
        const std::vector<TwistWorkSpaceSlot> aIngressSources = aSlice.IngressSources();
        const std::vector<TwistWorkSpaceSlot> aCrossSources = aSlice.CrossSources();

        auto CheckResidualPosition = [&](const std::vector<TwistWorkSpaceSlot> &pSources,
                                         const char *pPositionName) -> bool {
            for (std::size_t aSourceIndex = 0U; aSourceIndex < pSources.size(); ++aSourceIndex) {
                const TwistWorkSpaceSlot aSource = pSources[aSourceIndex];
                if (!HasSlot(pResiduals, aSource)) {
                    continue;
                }

                if (aSourceIndex + 1U != pSources.size()) {
                    SetError(pErrorMessage,
                             StagePrefix(pConfig, aSliceIndex) +
                             " residual graph used a residual outside the " +
                             std::string(pPositionName) +
                             " random source position");
                    return false;
                }

                aDiscoveredResiduals.insert(static_cast<int>(aSource));
            }
            return true;
        };

        if (!CheckResidualPosition(aIngressSources, "ingress")) {
            return false;
        }
        if (!CheckResidualPosition(aCrossSources, "cross")) {
            return false;
        }
    }

    for (TwistWorkSpaceSlot aResidual : pResiduals) {
        if (aDiscoveredResiduals.find(static_cast<int>(aResidual)) == aDiscoveredResiduals.end()) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " residual graph did not discover residual source " +
                     BufName(aResidual));
            return false;
        }
    }

    return true;
}


bool GSeedRunStageConfigValidator::ValidatePrimaryCombinations(const GSeedRunStageConfig &pConfig,
                                                                              std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                               std::string *pErrorMessage) {
    
    if ((pPrimarySources.size() == 3U) &&
        ((pPrimarySources[0] != TwistWorkSpaceSlot::kSource) ||
         (pPrimarySources[1] != TwistWorkSpaceSlot::kKeyRowReadA) ||
         (pPrimarySources[2] != TwistWorkSpaceSlot::kKeyRowReadB))) {
        SetError(pErrorMessage,
                 pConfig.mStageName + " " + pConfig.mBatchName +
                 " three-primary validation expects sources ordered as source, key_a, key_b");
        return false;
    }
    
    std::vector<std::vector<SlotAndDirection>> aExpectedCombos = (pPrimarySources.size() == 3U) ?
        StarterPrimaryCombinations(pPrimarySources) :
        AllDirectionCombinations(pPrimarySources);
    std::vector<bool> aContains;
    for (std::size_t i = 0U; i < aExpectedCombos.size(); ++i) {
        aContains.push_back(false);
    }
    
    for (std::size_t aSliceIndex = 0U; aSliceIndex < pConfig.mSlices.size(); ++aSliceIndex) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aSliceIndex];
        
        for (std::size_t aComboIndex = 0U; aComboIndex < aExpectedCombos.size(); ++aComboIndex) {
            bool aContainsAll = true;
            const std::vector<SlotAndDirection> &aCombo = aExpectedCombos[aComboIndex];
            for (const SlotAndDirection &aEntry : aCombo) {
                const bool aSliceContainsDirection = aEntry.mForward ?
                    IsForcedForward(aSlice, aEntry.mSlot) :
                    IsForcedBackward(aSlice, aEntry.mSlot);
                if (!aSliceContainsDirection) {
                    aContainsAll = false;
                    break;
                }
            }
            if (aContainsAll) {
                aContains[aComboIndex] = true;
            }
        }
    }
    
    for (std::size_t i = 0U; i < aExpectedCombos.size(); ++i) {
        if (aContains[i] == false) {
            SetError(pErrorMessage,
                     pConfig.mStageName + " " + pConfig.mBatchName +
                     " expected " + CombinationText(aExpectedCombos[i]) +
                     " as a primary source direction combination, did not find");
            return false;
        }
        
    }
    
    
    return true;
}


bool GSeedRunStageConfigValidator::ValidateMidstageSourceDiversity(const GSeedRunStageConfig &pConfig,
                                                                              std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                                  std::string *pErrorMessage) {
    
    for (TwistWorkSpaceSlot aPrimarySource : pPrimarySources) {
        bool aHasForcedForward = false;
        bool aHasForcedBackward = false;
        int aUseCount = 0;

        for (const GSeedRunStageSliceSpec &aSlice : pConfig.mSlices) {
            const std::vector<TwistWorkSpaceSlot> aIngressSources = aSlice.IngressSources();
            const std::vector<TwistWorkSpaceSlot> aCrossSources = aSlice.CrossSources();

            for (TwistWorkSpaceSlot aSource : aIngressSources) {
                if (aSource == aPrimarySource) {
                    aUseCount += 1;
                }
            }

            for (TwistWorkSpaceSlot aSource : aCrossSources) {
                if (aSource == aPrimarySource) {
                    aUseCount += 1;
                }
            }

            aHasForcedForward = aHasForcedForward || IsForcedForward(aSlice, aPrimarySource);
            aHasForcedBackward = aHasForcedBackward || IsForcedBackward(aSlice, aPrimarySource);
        }

        if (!aHasForcedForward) {
            SetError(pErrorMessage,
                     pConfig.mStageName + " " + pConfig.mBatchName +
                     " primary source " + BufName(aPrimarySource) +
                     " was never forced-forward");
            return false;
        }

        if (!aHasForcedBackward) {
            SetError(pErrorMessage,
                     pConfig.mStageName + " " + pConfig.mBatchName +
                     " primary source " + BufName(aPrimarySource) +
                     " was never forced-backward");
            return false;
        }

        if (aUseCount > 4) {
            SetError(pErrorMessage,
                     pConfig.mStageName + " " + pConfig.mBatchName +
                     " primary source " + BufName(aPrimarySource) +
                     " was used more than 4 times: " +
                     std::to_string(aUseCount));
            return false;
        }
    }
    
    return true;
}
