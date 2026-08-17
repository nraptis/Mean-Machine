//
//  GSeedRunStageConfigValidator.cpp
//  MeanMachine
//

#include "GSeedRunStageConfigValidator.hpp"
#include "GSymbol.hpp"

#include <array>
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

    if ((pConfig.mSlices.size() != 4U) &&
        (pConfig.mSlices.size() != 6U)) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " must contain exactly four or six slices");
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

bool ValidateFourInputStageEntry(
    const GSeedRunStageConfig &pConfig,
    const std::vector<TwistWorkSpaceSlot> &pPrimarySources,
    std::string *pErrorMessage) {
    if (pPrimarySources.size() != 4U) {
        return true;
    }

    if (pConfig.mSlices[0].mIngressSources[0] != pPrimarySources[3]) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " four-input stage did not start its first loop with its last primary source");
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

std::size_t SourceAppearanceCount(
    const GSeedRunStageSliceSpec &pSlice,
    const TwistWorkSpaceSlot pSlot) {
    std::size_t aCount = 0U;
    for (TwistWorkSpaceSlot aIngressSource : pSlice.mIngressSources) {
        if (aIngressSource == pSlot) {
            ++aCount;
        }
    }
    for (TwistWorkSpaceSlot aCrossSource : pSlice.mCrossSources) {
        if (aCrossSource == pSlot) {
            ++aCount;
        }
    }
    return aCount;
}

bool ValidateScheduledSourceRead(
    const GSeedRunStageConfig &pConfig,
    const GSeedRunStageSliceSpec &pReadSlice,
    const std::size_t pReadIndex,
    const TwistWorkSpaceSlot pWrittenLane,
    const std::size_t pDistance,
    const char *pGraphName,
    std::string *pErrorMessage) {
    const std::size_t aAppearanceCount =
        SourceAppearanceCount(pReadSlice, pWrittenLane);

    bool aMatchesRequiredPosition = false;
    const char *aRequiredPosition = nullptr;
    if (pDistance == 1U) {
        aMatchesRequiredPosition =
            !pReadSlice.mIngressSources.empty() &&
            (pReadSlice.mIngressSources[0] == pWrittenLane);
        aRequiredPosition = "ingress[0] one pass after its write";
    } else if (pDistance == 2U) {
        aMatchesRequiredPosition =
            !pReadSlice.mCrossSources.empty() &&
            (pReadSlice.mCrossSources[0] == pWrittenLane);
        aRequiredPosition = "cross[0] two passes after its write";
    } else if (pDistance == 3U) {
        aMatchesRequiredPosition =
            (pReadSlice.mIngressSources.size() > 1U) &&
            (pReadSlice.mIngressSources[1] == pWrittenLane);
        aRequiredPosition = "ingress[1] three passes after its write";
    }

    if (pDistance <= 3U) {
        if ((aAppearanceCount != 1U) ||
            !aMatchesRequiredPosition) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, pReadIndex) + " " +
                     pGraphName + " must use " +
                     BufName(pWrittenLane) + " exactly once as " +
                     aRequiredPosition);
            return false;
        }
        return true;
    }

    const bool aIsFourthReadWindow = (pDistance == 4U);
    if (aIsFourthReadWindow) {
        const bool aMatchesFourthReadPosition =
            (aAppearanceCount == 1U) &&
            (pReadSlice.mCrossSources.size() > 1U) &&
            (pReadSlice.mCrossSources[1] == pWrittenLane);
        if ((aAppearanceCount != 0U) &&
            !aMatchesFourthReadPosition) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, pReadIndex) + " " +
                     pGraphName + " may use " +
                     BufName(pWrittenLane) +
                     " for its fourth read only as cross[1] " +
                     "exactly four passes after its write");
            return false;
        }
        return true;
    }

    if (aAppearanceCount != 0U) {
        SetError(pErrorMessage,
                 StagePrefix(pConfig, pReadIndex) + " " +
                 pGraphName + " used " +
                 BufName(pWrittenLane) +
                 " outside its permitted fourth-read window");
        return false;
    }

    return true;
}

bool ValidateRequiredFourthSourceRead(
    const GSeedRunStageConfig &pConfig,
    const TwistWorkSpaceSlot pWrittenLane,
    const std::size_t pFirstReadIndex,
    const std::size_t pDistanceAtFirstRead,
    const char *pGraphName,
    std::string *pErrorMessage) {
    bool aCanSupportFourthRead = false;
    std::size_t aFourthReadCount = 0U;

    for (std::size_t aReadIndex = pFirstReadIndex;
         aReadIndex < pConfig.mSlices.size();
         ++aReadIndex) {
        const std::size_t aDistance =
            pDistanceAtFirstRead + (aReadIndex - pFirstReadIndex);
        const bool aIsFourthReadWindow = (aDistance == 4U);
        if (!aIsFourthReadWindow) {
            continue;
        }

        aCanSupportFourthRead = true;
        aFourthReadCount +=
            SourceAppearanceCount(pConfig.mSlices[aReadIndex],
                                  pWrittenLane);
    }

    if (aCanSupportFourthRead && (aFourthReadCount != 1U)) {
        SetError(pErrorMessage,
                 pConfig.mStageName + " " + pGraphName +
                 " must use " + BufName(pWrittenLane) +
                 " exactly once for its fourth read at cross[1] " +
                 "exactly four passes after its write");
        return false;
    }

    return true;
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

bool GSeedRunStageConfigValidator::ValidateMidstageList(
    const GSeedRunStageConfig &pConfig,
    std::vector<TwistWorkSpaceSlot> pPrimarySources,
    std::vector<TwistWorkSpaceSlot> pResidualSources,
    std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
    std::string *pErrorMessage) {
    const std::vector<TwistWorkSpaceSlot> aActualSources =
        Sources(pConfig, pExpectedDestinations);

    std::vector<TwistWorkSpaceSlot> aAllowedSources;
    for (TwistWorkSpaceSlot aPrimarySource : pPrimarySources) {
        AppendUniqueSlot(&aAllowedSources, aPrimarySource);
    }
    for (TwistWorkSpaceSlot aResidualSource : pResidualSources) {
        AppendUniqueSlot(&aAllowedSources, aResidualSource);
    }

    std::vector<TwistWorkSpaceSlot> aRequiredSources;
    for (std::size_t aPrimaryIndex = 0U;
         aPrimaryIndex < pPrimarySources.size();
         ++aPrimaryIndex) {
        AppendUniqueSlot(&aRequiredSources,
                         pPrimarySources[aPrimaryIndex]);
    }
    for (TwistWorkSpaceSlot aResidualSource : pResidualSources) {
        AppendUniqueSlot(&aRequiredSources, aResidualSource);
    }

    for (TwistWorkSpaceSlot aActualSource : aActualSources) {
        if (!HasSlot(aAllowedSources, aActualSource)) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " midstage source set contained an unexpected source");
            return false;
        }
    }

    for (TwistWorkSpaceSlot aRequiredSource : aRequiredSources) {
        if (!HasSlot(aActualSources, aRequiredSource)) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " midstage source set omitted required source " +
                     BufName(aRequiredSource));
            return false;
        }
    }

    return true;
}



bool GSeedRunStageConfigValidator::ValidateStarter(const GSeedRunStageConfig &pConfig,
                                                   std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                   std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
                                                   std::string *pErrorMessage) {
    
    std::vector<TwistWorkSpaceSlot> aSources;
    for (TwistWorkSpaceSlot aSlot : pPrimarySources) {
        AppendUniqueSlot(&aSources, aSlot);
    }
    
    if (!ValidateBasicShape(pConfig, pErrorMessage)) {
        return false;
    }
    if (!ValidateFourInputStageEntry(pConfig,
                                     pPrimarySources,
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

    if (!ValidateList(pConfig,
                      aSources,
                      pExpectedDestinations,
                      pErrorMessage)) {
        return false;
    }

    if (!ValidateSourceGraph(pConfig,
                             aSources,
                             pErrorMessage)) {
        return false;
    }
    
    if (!ValidateNonRedundancy(pConfig, pErrorMessage)) {
        return false;
    }
    
    if (!ValidatePrimaryCombinations(pConfig,
                                     pPrimarySources,
                                     pErrorMessage)) {
        return false;
    }
    
    return true;
}

bool GSeedRunStageConfigValidator::ValidateStarterWithResiduals(
    const GSeedRunStageConfig &pConfig,
    std::vector<TwistWorkSpaceSlot> pPrimarySources,
    std::vector<TwistWorkSpaceSlot> pResidualSources,
    std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
    std::string *pErrorMessage) {
    std::vector<TwistWorkSpaceSlot> aSources;
    for (TwistWorkSpaceSlot aSlot : pPrimarySources) {
        AppendUniqueSlot(&aSources, aSlot);
    }
    for (TwistWorkSpaceSlot aSlot : pResidualSources) {
        AppendUniqueSlot(&aSources, aSlot);
    }

    if (!ValidateBasicShape(pConfig, pErrorMessage)) {
        return false;
    }
    if (!ValidateFourInputStageEntry(pConfig,
                                     pPrimarySources,
                                     pErrorMessage)) {
        return false;
    }

    if (pPrimarySources.size() >
        static_cast<std::size_t>(pConfig.mMaxContextSourceCount)) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " starter validation received too many primary sources");
        return false;
    }

    if (!ValidateDestinations(pConfig,
                              pExpectedDestinations,
                              pErrorMessage)) {
        return false;
    }

    if (!ValidateList(pConfig,
                      aSources,
                      pExpectedDestinations,
                      pErrorMessage)) {
        return false;
    }

    if (!ValidateSourceGraph(pConfig,
                             aSources,
                             pErrorMessage)) {
        return false;
    }

    if (!ValidateNonRedundancy(pConfig, pErrorMessage)) {
        return false;
    }

    if (!ValidateResidualGraph(pConfig,
                               pResidualSources,
                               pErrorMessage)) {
        return false;
    }

    if (!ValidatePrimaryCombinations(pConfig,
                                     pPrimarySources,
                                     pErrorMessage)) {
        return false;
    }

    return true;
}

bool GSeedRunStageConfigValidator::ValidateKeyEightInput(
    const GSeedRunStageConfig &pConfig,
    std::vector<TwistWorkSpaceSlot> pPrimarySources,
    std::vector<TwistWorkSpaceSlot> pResidualSources,
    std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
    std::string *pErrorMessage) {
    if ((pPrimarySources.size() != 8U) ||
        (pResidualSources.size() != 8U) ||
        (pExpectedDestinations.size() != 4U)) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " key validation requires eight inputs, eight residuals, and four destinations");
        return false;
    }

    std::vector<TwistWorkSpaceSlot> aSources;
    for (TwistWorkSpaceSlot aSlot : pPrimarySources) {
        if ((aSlot == TwistWorkSpaceSlot::kInvalid) ||
            HasSlot(aSources, aSlot)) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " key validation requires eight unique valid inputs");
            return false;
        }
        aSources.push_back(aSlot);
    }
    for (TwistWorkSpaceSlot aSlot : pResidualSources) {
        if ((aSlot == TwistWorkSpaceSlot::kInvalid) ||
            HasSlot(aSources, aSlot)) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " key validation requires eight unique residuals disjoint from its inputs");
            return false;
        }
        aSources.push_back(aSlot);
    }

    if (!ValidateBasicShape(pConfig, pErrorMessage) ||
        !ValidateDestinations(pConfig,
                              pExpectedDestinations,
                              pErrorMessage)) {
        return false;
    }

    if (!ValidateList(pConfig,
                      aSources,
                      pExpectedDestinations,
                      pErrorMessage) ||
        !ValidateSourceGraph(pConfig,
                             aSources,
                             pErrorMessage) ||
        !ValidateNonRedundancy(pConfig,
                               pErrorMessage)) {
        return false;
    }

    const auto Matches = [](
        const std::vector<TwistWorkSpaceSlot> &pActual,
        const std::initializer_list<TwistWorkSpaceSlot> pExpected) {
        return std::vector<TwistWorkSpaceSlot>(pExpected) == pActual;
    };

    const GSeedRunStageSliceSpec &aPassA = pConfig.mSlices[0];
    const GSeedRunStageSliceSpec &aPassB = pConfig.mSlices[1];
    const GSeedRunStageSliceSpec &aPassC = pConfig.mSlices[2];
    const GSeedRunStageSliceSpec &aPassD = pConfig.mSlices[3];

    const bool aMatchesGraph =
        Matches(aPassA.mIngressSources,
                {pPrimarySources[0], pPrimarySources[1],
                 pPrimarySources[2], pPrimarySources[3]}) &&
        Matches(aPassA.mCrossSources,
                {pPrimarySources[4], pPrimarySources[5],
                 pPrimarySources[6], pPrimarySources[7]}) &&
        Matches(aPassB.mIngressSources,
                {pExpectedDestinations[0], pPrimarySources[4],
                 pPrimarySources[5], pResidualSources[0]}) &&
        Matches(aPassB.mCrossSources,
                {pPrimarySources[0], pPrimarySources[1],
                 pResidualSources[1], pResidualSources[2]}) &&
        Matches(aPassC.mIngressSources,
                {pExpectedDestinations[1], pPrimarySources[6],
                 pResidualSources[3], pResidualSources[4]}) &&
        Matches(aPassC.mCrossSources,
                {pExpectedDestinations[0], pPrimarySources[2],
                 pResidualSources[5], pResidualSources[6]}) &&
        Matches(aPassD.mIngressSources,
                {pExpectedDestinations[2], pExpectedDestinations[0],
                 pPrimarySources[7], pResidualSources[5]}) &&
        Matches(aPassD.mCrossSources,
                {pExpectedDestinations[1], pPrimarySources[3],
                 pResidualSources[6], pResidualSources[7]});
    if (!aMatchesGraph) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " did not match the exact eight-input key source graph");
        return false;
    }

    return true;
}

bool GSeedRunStageConfigValidator::ValidateGrowSixInput(
    const GSeedRunStageConfig &pConfig,
    std::vector<TwistWorkSpaceSlot> pPrimarySources,
    std::vector<TwistWorkSpaceSlot> pResidualSources,
    std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
    std::string *pErrorMessage) {
    if ((pPrimarySources.size() != 6U) ||
        (pResidualSources.size() != 12U) ||
        (pExpectedDestinations.size() != 4U)) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " Grow-six validation requires six inputs, twelve residuals, and four destinations");
        return false;
    }

    if (!ValidateBasicShape(pConfig, pErrorMessage) ||
        !ValidateDestinations(pConfig,
                              pExpectedDestinations,
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

    if (!ValidateList(pConfig,
                      aSources,
                      pExpectedDestinations,
                      pErrorMessage) ||
        !ValidateSourceGraph(pConfig,
                             aSources,
                             pErrorMessage) ||
        !ValidateNonRedundancy(pConfig,
                               pErrorMessage)) {
        return false;
    }

    const auto Matches = [](
        const std::vector<TwistWorkSpaceSlot> &pActual,
        const std::initializer_list<TwistWorkSpaceSlot> pExpected) {
        return std::vector<TwistWorkSpaceSlot>(pExpected) == pActual;
    };

    const GSeedRunStageSliceSpec &aPassA = pConfig.mSlices[0];
    const GSeedRunStageSliceSpec &aPassB = pConfig.mSlices[1];
    const GSeedRunStageSliceSpec &aPassC = pConfig.mSlices[2];
    const GSeedRunStageSliceSpec &aPassD = pConfig.mSlices[3];

    const bool aMatchesGraph =
        Matches(aPassA.mIngressSources,
                {pPrimarySources[3], pPrimarySources[1],
                 pPrimarySources[4], pResidualSources[0]}) &&
        Matches(aPassA.mCrossSources,
                {pPrimarySources[2], pPrimarySources[0],
                 pPrimarySources[4], pResidualSources[1]}) &&
        Matches(aPassB.mIngressSources,
                {pExpectedDestinations[0], pPrimarySources[2],
                 pPrimarySources[5], pResidualSources[2]}) &&
        Matches(aPassB.mCrossSources,
                {pPrimarySources[3], pPrimarySources[1],
                 pPrimarySources[4], pResidualSources[3]}) &&
        Matches(aPassC.mIngressSources,
                {pExpectedDestinations[1], pPrimarySources[3],
                 pResidualSources[4], pResidualSources[5]}) &&
        Matches(aPassC.mCrossSources,
                {pExpectedDestinations[0], pPrimarySources[2],
                 pResidualSources[6], pResidualSources[7]}) &&
        Matches(aPassD.mIngressSources,
                {pExpectedDestinations[2], pExpectedDestinations[0],
                 pResidualSources[8], pResidualSources[9]}) &&
        Matches(aPassD.mCrossSources,
                {pExpectedDestinations[1], pPrimarySources[3],
                 pResidualSources[10], pResidualSources[11]});
    if (!aMatchesGraph) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " did not match the exact six-input Grow source graph");
        return false;
    }

    for (const GSeedRunStageSliceSpec &aSlice : pConfig.mSlices) {
        if (!aSlice.mIsLastIngressDirectionLocked ||
            !aSlice.mIsLastCrossDirectionLocked) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " six-input Grow sources must be direction locked");
            return false;
        }
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
    if (!ValidateFourInputStageEntry(pConfig,
                                     pPrimarySources,
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

    if (!ValidateMidstageList(pConfig,
                              pPrimarySources,
                              pResidualSources,
                              pExpectedDestinations,
                              pErrorMessage)) {
        return false;
    }

    if (!ValidateSourceGraphMidstage(pConfig,
                                     pPrimarySources,
                                     aSources,
                                     pErrorMessage)) {
        return false;
    }

    if (!ValidateResidualGraph(pConfig, pResidualSources, pErrorMessage)) {
        return false;
    }

    
    if (!ValidateNonRedundancy(pConfig, pErrorMessage)) {
        return false;
    }

    return true;
}

bool GSeedRunStageConfigValidator::ValidateTrunk(
    const GSeedRunStageConfig &pConfig,
    std::vector<TwistWorkSpaceSlot> pPrimarySources,
    std::vector<TwistWorkSpaceSlot> pResidualSources,
    std::vector<TwistWorkSpaceSlot> pExpectedDestinations,
    std::string *pErrorMessage) {
    if (!ValidateBasicShape(pConfig, pErrorMessage)) {
        return false;
    }

    if (pPrimarySources.size() != 4U) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " trunk validation requires exactly four primary sources");
        return false;
    }

    if (pResidualSources.empty()) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " trunk validation requires a residual for pass four's wildcard");
        return false;
    }

    std::vector<TwistWorkSpaceSlot> aSources;
    for (TwistWorkSpaceSlot aPrimarySource : pPrimarySources) {
        if ((aPrimarySource == TwistWorkSpaceSlot::kInvalid) ||
            HasSlot(aSources, aPrimarySource)) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " trunk validation requires four unique valid primary sources");
            return false;
        }
        aSources.push_back(aPrimarySource);
    }
    for (TwistWorkSpaceSlot aResidualSource : pResidualSources) {
        if (HasSlot(pPrimarySources, aResidualSource)) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " trunk residual source overlapped a primary source");
            return false;
        }
        if (HasSlot(pExpectedDestinations, aResidualSource)) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " trunk residual source overlapped a destination");
            return false;
        }
        AppendUniqueSlot(&aSources, aResidualSource);
    }

    if (!ValidateDestinations(pConfig,
                              pExpectedDestinations,
                              pErrorMessage)) {
        return false;
    }

    if (!ValidateList(pConfig,
                      aSources,
                      pExpectedDestinations,
                      pErrorMessage)) {
        return false;
    }

    if (!ValidateSourceGraphTrunk(pConfig,
                                  pPrimarySources,
                                  pResidualSources,
                                  aSources,
                                  pErrorMessage)) {
        return false;
    }

    if (!ValidateResidualGraph(pConfig,
                               pResidualSources,
                               pErrorMessage)) {
        return false;
    }

    if (!ValidateNonRedundancy(pConfig, pErrorMessage)) {
        return false;
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
    std::unordered_set<int> aDestinationSlots;
    std::unordered_set<int> aWrittenDestinations;

    for (const GSeedRunStageSliceSpec &aSlice : pConfig.mSlices) {
        const int aDestinationKey = static_cast<int>(aSlice.mDest);
        if (!aDestinationSlots.insert(aDestinationKey).second) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " source graph wrote the same destination lane more than once");
            return false;
        }
    }

    for (TwistWorkSpaceSlot aSlot : pSources) {
        if (aSlot == TwistWorkSpaceSlot::kInvalid) {
            SetError(pErrorMessage,
                     pConfig.mStageName + " source graph contained invalid initial source");
            return false;
        }
        AppendUniqueSlot(&aAvailableSources, aSlot);
    }

    auto ValidateReadAvailability =
        [&](const TwistWorkSpaceSlot pSlot,
            const std::size_t pSliceIndex,
            const char *pSideName) -> bool {
        const int aSlotKey = static_cast<int>(pSlot);
        if ((aDestinationSlots.find(aSlotKey) != aDestinationSlots.end()) &&
            (aWrittenDestinations.find(aSlotKey) == aWrittenDestinations.end())) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, pSliceIndex) +
                     " source graph " + pSideName + " read " +
                     BufName(pSlot) +
                     " before its destination write");
            return false;
        }

        if (!HasSlot(aAvailableSources, pSlot)) {
            SetError(pErrorMessage,
                     StagePrefix(pConfig, pSliceIndex) +
                     " source graph " + pSideName +
                     " read before source was available");
            return false;
        }

        return true;
    };

    for (std::size_t aSliceIndex = 0U; aSliceIndex < pConfig.mSlices.size(); ++aSliceIndex) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aSliceIndex];
        const std::vector<TwistWorkSpaceSlot> aIngressSources = aSlice.IngressSources();
        const std::vector<TwistWorkSpaceSlot> aCrossSources = aSlice.CrossSources();

        for (TwistWorkSpaceSlot aSlot : aIngressSources) {
            if (!ValidateReadAvailability(aSlot,
                                          aSliceIndex,
                                          "ingress")) {
                return false;
            }
        }

        for (TwistWorkSpaceSlot aSlot : aCrossSources) {
            if (!ValidateReadAvailability(aSlot,
                                          aSliceIndex,
                                          "cross")) {
                return false;
            }
        }

        AppendUniqueSlot(&aAvailableSources, aSlice.mDest);
        aWrittenDestinations.insert(static_cast<int>(aSlice.mDest));
    }

    for (std::size_t aWriteIndex = 0U;
         aWriteIndex < pConfig.mSlices.size();
         ++aWriteIndex) {
        const TwistWorkSpaceSlot aWrittenLane =
            pConfig.mSlices[aWriteIndex].mDest;

        for (std::size_t aReadIndex = aWriteIndex + 1U;
             aReadIndex < pConfig.mSlices.size();
             ++aReadIndex) {
            const std::size_t aDistance = aReadIndex - aWriteIndex;
            const GSeedRunStageSliceSpec &aReadSlice =
                pConfig.mSlices[aReadIndex];
            if (!ValidateScheduledSourceRead(pConfig,
                                             aReadSlice,
                                             aReadIndex,
                                             aWrittenLane,
                                             aDistance,
                                             "source graph",
                                             pErrorMessage)) {
                return false;
            }
        }

        if (!ValidateRequiredFourthSourceRead(
                pConfig,
                aWrittenLane,
                aWriteIndex + 1U,
                1U,
                "source graph",
                pErrorMessage)) {
            return false;
        }
    }

    return true;
}

bool GSeedRunStageConfigValidator::ValidateSourceGraphMidstage(
    const GSeedRunStageConfig &pConfig,
    std::vector<TwistWorkSpaceSlot> pPrimarySources,
    std::vector<TwistWorkSpaceSlot> pSources,
    std::string *pErrorMessage) {
    if (pPrimarySources.empty() ||
        (pPrimarySources.size() > 4U)) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " midstage source graph requires between one and four ordered primary sources");
        return false;
    }

    std::unordered_set<int> aPrimarySourceSet;
    for (TwistWorkSpaceSlot aPrimarySource : pPrimarySources) {
        if (aPrimarySource == TwistWorkSpaceSlot::kInvalid) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " midstage source graph contained an invalid primary source");
            return false;
        }
        if (!aPrimarySourceSet.insert(
                static_cast<int>(aPrimarySource)).second) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " midstage source graph contained duplicate primary sources");
            return false;
        }
    }

    if (!ValidateSourceGraph(pConfig,
                             pSources,
                             pErrorMessage)) {
        return false;
    }

    for (std::size_t aPrimaryIndex = 0U;
         aPrimaryIndex < pPrimarySources.size();
         ++aPrimaryIndex) {
        const TwistWorkSpaceSlot aPrimarySource =
            pPrimarySources[aPrimaryIndex];
        const std::size_t aDistanceAtFirstPass =
            pPrimarySources.size() - aPrimaryIndex;

        for (std::size_t aReadIndex = 0U;
             aReadIndex < pConfig.mSlices.size();
             ++aReadIndex) {
            const std::size_t aDistance =
                aDistanceAtFirstPass + aReadIndex;
            if (!ValidateScheduledSourceRead(
                    pConfig,
                    pConfig.mSlices[aReadIndex],
                    aReadIndex,
                    aPrimarySource,
                    aDistance,
                    "midstage source graph",
                    pErrorMessage)) {
                return false;
            }
        }

        if (!ValidateRequiredFourthSourceRead(
                pConfig,
                aPrimarySource,
                0U,
                aDistanceAtFirstPass,
                "midstage source graph",
                pErrorMessage)) {
            return false;
        }
    }

    return true;
}

bool GSeedRunStageConfigValidator::ValidateSourceGraphTrunk(
    const GSeedRunStageConfig &pConfig,
    std::vector<TwistWorkSpaceSlot> pPrimarySources,
    std::vector<TwistWorkSpaceSlot> pResidualSources,
    std::vector<TwistWorkSpaceSlot> pSources,
    std::string *pErrorMessage) {
    if ((pPrimarySources.size() != 4U) ||
        (pConfig.mSlices.size() < 4U)) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " trunk source graph requires four primary sources and at least four passes");
        return false;
    }

    const TwistWorkSpaceSlot aPrimaryA = pPrimarySources[0];
    const TwistWorkSpaceSlot aPrimaryB = pPrimarySources[1];
    const TwistWorkSpaceSlot aPrimaryC = pPrimarySources[2];
    const TwistWorkSpaceSlot aPrimaryD = pPrimarySources[3];

    const GSeedRunStageSliceSpec &aPassA = pConfig.mSlices[0];
    const GSeedRunStageSliceSpec &aPassB = pConfig.mSlices[1];
    const GSeedRunStageSliceSpec &aPassC = pConfig.mSlices[2];
    const GSeedRunStageSliceSpec &aPassD = pConfig.mSlices[3];

    const auto HasPosition =
        [](const std::vector<TwistWorkSpaceSlot> &pSlots,
           const std::size_t pIndex,
           const TwistWorkSpaceSlot pExpected) -> bool {
            return (pSlots.size() > pIndex) &&
                (pSlots[pIndex] == pExpected);
        };

    if (!HasPosition(aPassA.mIngressSources, 0U, aPrimaryA) ||
        !HasPosition(aPassA.mIngressSources, 1U, aPrimaryB) ||
        !HasPosition(aPassA.mCrossSources, 0U, aPrimaryC) ||
        !HasPosition(aPassA.mCrossSources, 1U, aPrimaryD)) {
        SetError(pErrorMessage,
                 StagePrefix(pConfig, 0U) +
                 " trunk source graph requires ingress [primary A, primary B] and cross [primary C, primary D]");
        return false;
    }

    if (!HasPosition(aPassB.mIngressSources, 0U, aPassA.mDest) ||
        !HasPosition(aPassB.mIngressSources, 1U, aPrimaryC) ||
        !HasPosition(aPassB.mCrossSources, 0U, aPrimaryA) ||
        !HasPosition(aPassB.mCrossSources, 1U, aPrimaryB)) {
        SetError(pErrorMessage,
                 StagePrefix(pConfig, 1U) +
                 " trunk source graph requires ingress [destination A, primary C] and cross [primary A, primary B]");
        return false;
    }

    if (!HasPosition(aPassC.mIngressSources, 0U, aPassB.mDest) ||
        !HasPosition(aPassC.mIngressSources, 1U, aPrimaryD) ||
        !HasPosition(aPassC.mCrossSources, 0U, aPassA.mDest) ||
        !HasPosition(aPassC.mCrossSources, 1U, aPrimaryB)) {
        SetError(pErrorMessage,
                 StagePrefix(pConfig, 2U) +
                 " trunk source graph requires ingress [destination B, primary D] and cross [destination A, primary B]");
        return false;
    }

    const bool aPassDUsesDestinationA =
        HasPosition(aPassD.mIngressSources, 1U, aPassA.mDest);
    const bool aPassDUsesResidualInstead =
        (aPassD.mIngressSources.size() > 1U) &&
        HasSlot(pResidualSources, aPassD.mIngressSources[1]);

    if (!HasPosition(aPassD.mIngressSources, 0U, aPassC.mDest) ||
        (!aPassDUsesDestinationA && !aPassDUsesResidualInstead) ||
        !HasPosition(aPassD.mCrossSources, 0U, aPassB.mDest) ||
        (aPassD.mCrossSources.size() < 2U) ||
        !HasSlot(pResidualSources, aPassD.mCrossSources[1])) {
        SetError(pErrorMessage,
                 StagePrefix(pConfig, 3U) +
                 " trunk source graph requires ingress [destination C, optional destination A or residual] and cross [destination B, residual wildcard]");
        return false;
    }

    if (!IsForcedForward(aPassA, aPrimaryB) ||
        !IsForcedBackward(aPassA, aPrimaryD) ||
        !IsForcedForward(aPassB, aPrimaryC) ||
        !IsForcedBackward(aPassB, aPrimaryB) ||
        !IsForcedForward(aPassC, aPrimaryD)) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " trunk source graph did not preserve its required primary directions");
        return false;
    }

    for (std::size_t aSliceIndex = 0U;
         aSliceIndex < pConfig.mSlices.size();
         ++aSliceIndex) {
        const GSeedRunStageSliceSpec &aSlice =
            pConfig.mSlices[aSliceIndex];
        const std::vector<TwistWorkSpaceSlot> aPrimarySlots = {
            aPrimaryA, aPrimaryB, aPrimaryC, aPrimaryD,
        };
        for (TwistWorkSpaceSlot aPrimarySlot : aPrimarySlots) {
            bool aExpectedHere = false;
            if (aSliceIndex == 0U) {
                aExpectedHere = true;
            } else if (aSliceIndex == 1U) {
                aExpectedHere =
                    (aPrimarySlot == aPrimaryA) ||
                    (aPrimarySlot == aPrimaryB) ||
                    (aPrimarySlot == aPrimaryC);
            } else if (aSliceIndex == 2U) {
                aExpectedHere =
                    (aPrimarySlot == aPrimaryB) ||
                    (aPrimarySlot == aPrimaryD);
            }

            const std::size_t aAppearanceCount =
                SourceAppearanceCount(aSlice, aPrimarySlot);
            if ((aExpectedHere && (aAppearanceCount != 1U)) ||
                (!aExpectedHere && (aAppearanceCount != 0U))) {
                SetError(pErrorMessage,
                         StagePrefix(pConfig, aSliceIndex) +
                         " trunk source graph used a primary outside its exact trunk positions");
                return false;
            }
        }
    }

    // Destination A's third read is the one optional departure from the
    // normal destination schedule. ValidateSourceGraph remains the single
    // implementation of availability and all subsequent scheduling rules;
    // supply Destination A in a validation-only copy when the trunk used a
    // second residual in that optional position.
    GSeedRunStageConfig aSourceGraphConfig = pConfig;
    if (!aPassDUsesDestinationA) {
        aSourceGraphConfig.mSlices[3].mIngressSources[1] =
            aPassA.mDest;
    }

    return ValidateSourceGraph(aSourceGraphConfig,
                               pSources,
                               pErrorMessage);
}

bool GSeedRunStageConfigValidator::ValidateResidualGraph(const GSeedRunStageConfig &pConfig,
                                                         std::vector<TwistWorkSpaceSlot> pResiduals,
                                                         std::string *pErrorMessage) {
    if (pResiduals.empty()) {
        return true;
    }

    // ValidateBasicShape already enforces the actual ingress/cross capacity
    // for every slice. Keep only the workspace-wide residual ceiling here so
    // a compact graph may use spare capacity unevenly across its passes.
    if (pResiduals.size() > 24U) {
        SetError(pErrorMessage,
                 pConfig.mStageName +
                 " residual graph had more than the supported residual source capacity");
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

    std::unordered_map<int, std::size_t> aResidualUseCounts;
    for (std::size_t aSliceIndex = 0U; aSliceIndex < pConfig.mSlices.size(); ++aSliceIndex) {
        const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aSliceIndex];
        const std::vector<TwistWorkSpaceSlot> aIngressSources = aSlice.IngressSources();
        const std::vector<TwistWorkSpaceSlot> aCrossSources = aSlice.CrossSources();

        auto CheckResidualSuffix = [&](const std::vector<TwistWorkSpaceSlot> &pSources,
                                       const char *pPositionName) -> bool {
            bool aFoundResidual = false;
            for (std::size_t aSourceIndex = 0U; aSourceIndex < pSources.size(); ++aSourceIndex) {
                const TwistWorkSpaceSlot aSource = pSources[aSourceIndex];
                if (!HasSlot(pResiduals, aSource)) {
                    if (aFoundResidual) {
                        SetError(pErrorMessage,
                                 StagePrefix(pConfig, aSliceIndex) +
                                 " residual graph used a non-residual after the " +
                                 std::string(pPositionName) +
                                 " residual suffix began");
                        return false;
                    }
                    continue;
                }

                aFoundResidual = true;
                aResidualUseCounts[static_cast<int>(aSource)] += 1U;
            }
            return true;
        };

        if (!CheckResidualSuffix(aIngressSources, "ingress")) {
            return false;
        }
        if (!CheckResidualSuffix(aCrossSources, "cross")) {
            return false;
        }
    }

    for (TwistWorkSpaceSlot aResidual : pResiduals) {
        const std::size_t aUseCount =
            aResidualUseCounts[static_cast<int>(aResidual)];
        if (aUseCount == 0U) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " residual graph did not discover residual source " +
                     BufName(aResidual));
            return false;
        }
        if (aUseCount != 1U) {
            SetError(pErrorMessage,
                     pConfig.mStageName +
                     " residual graph used residual source " +
                     BufName(aResidual) +
                     " more than once");
            return false;
        }
    }

    return true;
}


bool GSeedRunStageConfigValidator::ValidatePrimaryCombinations(const GSeedRunStageConfig &pConfig,
                                                                              std::vector<TwistWorkSpaceSlot> pPrimarySources,
                                                               std::string *pErrorMessage) {
    
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
