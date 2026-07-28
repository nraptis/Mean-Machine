#include "LaneSplitControl.hpp"

#include "ControlValueFile.hpp"
#include "FileIO.hpp"
#include "Library - G/GSymbol.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <limits>
#include <sstream>
#include <system_error>
#include <utility>

namespace {

constexpr std::size_t kLaneSplitCount = LaneSplitControl::kLaneSplitCount;
constexpr std::size_t kCandidateCount = LaneSplitControl::kCandidateCount;

constexpr std::array<const char *, kCandidateCount> kNames = {
    "Achernar", "Alcor", "Aldebaran", "Alioth", "Alkaid", "Alnitak",
    "Altair", "Ankaa", "Antares", "Arcturus", "Athebyne", "Bellatrix",
    "Betelgeuse", "Canopus", "Capella", "Castor", "Mebsuta", "Menkent",
    "Mimosa", "Miram", "Mirfak", "Mothallah", "Naos", "Polaris",
    "Pollux", "Procyon", "Regulus", "Gemma", "Rigel", "Saiph",
    "Sirius", "Suhail", "Vega"
};

using Order16 = std::array<std::uint8_t, kLaneSplitCount>;

struct RegisteredGroup {
    std::vector<LaneSplitControl::Slot> mLanes;
    std::vector<std::size_t> mLaneIndexes;
};

struct Candidate {
    // [registered lane][logical A-P] -> physical A-P
    std::vector<Order16> mPhysicalLaneSplits;

    // [logical A-P][ingress/cross role] -> registered lane
    std::array<std::vector<std::uint8_t>,
               kLaneSplitCount> mRoleLaneIndexes;
};

struct Score {
    std::uint64_t mMinimum = 0ULL;
    std::uint64_t mTotal = 0ULL;
};

std::vector<LaneSplitControl::Slot> gLanes;
std::vector<RegisteredGroup> gGroups;
std::vector<Candidate> gCandidates;
std::vector<std::string> gRendered;
std::uint64_t gRandomState = 0ULL;
bool gDidReset = false;

constexpr std::uint64_t kInfiniteFragmentDistance =
    kLaneSplitCount * 2U;

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

std::uint64_t NextRandom() {
    gRandomState += 0x9E3779B97F4A7C15ULL;
    std::uint64_t aValue = gRandomState;
    aValue = (aValue ^ (aValue >> 30U)) * 0xBF58476D1CE4E5B9ULL;
    aValue = (aValue ^ (aValue >> 27U)) * 0x94D049BB133111EBULL;
    return aValue ^ (aValue >> 31U);
}

std::size_t RandomIndex(const std::size_t pLimit) {
    return pLimit == 0U
        ? 0U
        : static_cast<std::size_t>(NextRandom() % pLimit);
}

template <typename T, std::size_t Count>
void Shuffle(std::array<T, Count> *pValues) {
    for (std::size_t i = Count; i > 1U; --i) {
        std::swap((*pValues)[i - 1U],
                  (*pValues)[RandomIndex(i)]);
    }
}

template <typename T>
void Shuffle(std::vector<T> *pValues) {
    for (std::size_t i = pValues->size(); i > 1U; --i) {
        std::swap((*pValues)[i - 1U],
                  (*pValues)[RandomIndex(i)]);
    }
}

Order16 IdentityOrder() {
    Order16 aOrder{};
    for (std::size_t i = 0U; i < kLaneSplitCount; ++i) {
        aOrder[i] = static_cast<std::uint8_t>(i);
    }
    return aOrder;
}

std::vector<std::uint8_t> IdentityLaneOrder() {
    std::vector<std::uint8_t> aOrder;
    aOrder.reserve(gLanes.size());
    for (std::size_t i = 0U; i < gLanes.size(); ++i) {
        aOrder.push_back(static_cast<std::uint8_t>(i));
    }
    return aOrder;
}

Candidate MakeCandidate() {
    Candidate aCandidate;
    aCandidate.mPhysicalLaneSplits.resize(gLanes.size());

    for (const RegisteredGroup &aGroup : gGroups) {
        Order16 aPhysicalOrder = IdentityOrder();
        Order16 aLogicalOrder = IdentityOrder();
        Order16 aLaneOffsets = IdentityOrder();
        Shuffle(&aPhysicalOrder);
        Shuffle(&aLogicalOrder);
        Shuffle(&aLaneOffsets);

        for (std::size_t aGroupLaneIndex = 0U;
             aGroupLaneIndex < aGroup.mLaneIndexes.size();
             ++aGroupLaneIndex) {
            const std::size_t aLaneIndex =
                aGroup.mLaneIndexes[aGroupLaneIndex];
            const std::size_t aOffset = aLaneOffsets[aGroupLaneIndex];
            for (std::size_t aLogical = 0U;
                 aLogical < kLaneSplitCount;
                 ++aLogical) {
                aCandidate.mPhysicalLaneSplits[aLaneIndex][aLogical] =
                    aPhysicalOrder[(aLogicalOrder[aLogical] + aOffset) %
                                   kLaneSplitCount];
            }
        }
    }

    // Every logical loop uses every registered base lane exactly once.
    // Shuffling this order independently lets any Poison or Plasma lane
    // occupy any ingress or cross role while retaining a four/four split.
    for (std::size_t aLogical = 0U;
         aLogical < kLaneSplitCount;
         ++aLogical) {
        std::vector<std::uint8_t> aRoleLanes =
            IdentityLaneOrder();
        Shuffle(&aRoleLanes);
        aCandidate.mRoleLaneIndexes[aLogical] =
            std::move(aRoleLanes);
    }

    return aCandidate;
}

bool CandidateIsValid(const Candidate &pCandidate) {
    if (pCandidate.mPhysicalLaneSplits.size() != gLanes.size()) {
        return false;
    }

    for (const Order16 &aLane : pCandidate.mPhysicalLaneSplits) {
        std::array<bool, kLaneSplitCount> aSeen{};
        for (std::uint8_t aPhysical : aLane) {
            if ((aPhysical >= kLaneSplitCount) || aSeen[aPhysical]) {
                return false;
            }
            aSeen[aPhysical] = true;
        }
    }

    for (const RegisteredGroup &aGroup : gGroups) {
        for (std::size_t aLogical = 0U;
             aLogical < kLaneSplitCount;
             ++aLogical) {
            std::array<bool, kLaneSplitCount> aSeen{};
            for (std::size_t aLaneIndex : aGroup.mLaneIndexes) {
                const std::uint8_t aPhysical =
                    pCandidate
                        .mPhysicalLaneSplits[aLaneIndex][aLogical];
                if (aSeen[aPhysical]) {
                    return false;
                }
                aSeen[aPhysical] = true;
            }
        }
    }

    for (std::size_t aLogical = 0U;
         aLogical < kLaneSplitCount;
         ++aLogical) {
        const std::vector<std::uint8_t> &aRoleLanes =
            pCandidate.mRoleLaneIndexes[aLogical];
        if (aRoleLanes.size() != gLanes.size()) {
            return false;
        }

        std::vector<bool> aSeen(gLanes.size(), false);
        for (const std::uint8_t aLaneIndex : aRoleLanes) {
            if ((aLaneIndex >= gLanes.size()) ||
                aSeen[aLaneIndex]) {
                return false;
            }
            aSeen[aLaneIndex] = true;
        }
    }
    return true;
}

bool GroupAndPositionForLane(
    const std::size_t pLaneIndex,
    std::size_t *pGroupIndex,
    std::size_t *pPosition) {
    for (std::size_t aGroupIndex = 0U;
         aGroupIndex < gGroups.size();
         ++aGroupIndex) {
        const std::vector<std::size_t> &aLaneIndexes =
            gGroups[aGroupIndex].mLaneIndexes;
        const auto aIterator =
            std::find(aLaneIndexes.begin(),
                      aLaneIndexes.end(),
                      pLaneIndex);
        if (aIterator == aLaneIndexes.end()) {
            continue;
        }
        if (pGroupIndex != nullptr) {
            *pGroupIndex = aGroupIndex;
        }
        if (pPosition != nullptr) {
            *pPosition = static_cast<std::size_t>(
                aIterator - aLaneIndexes.begin()
            );
        }
        return true;
    }
    return false;
}

std::uint64_t FragmentDistance(
    const std::size_t pLeftLane,
    const std::uint8_t pLeftSplit,
    const std::size_t pRightLane,
    const std::uint8_t pRightSplit) {
    if ((pLeftLane == pRightLane) &&
        (pLeftSplit == pRightSplit)) {
        return 0ULL;
    }

    std::size_t aLeftGroup = 0U;
    std::size_t aLeftPosition = 0U;
    std::size_t aRightGroup = 0U;
    std::size_t aRightPosition = 0U;
    if (!GroupAndPositionForLane(pLeftLane,
                                 &aLeftGroup,
                                 &aLeftPosition) ||
        !GroupAndPositionForLane(pRightLane,
                                 &aRightGroup,
                                 &aRightPosition) ||
        (aLeftGroup != aRightGroup)) {
        return kInfiniteFragmentDistance;
    }

    const std::size_t aLaneDistance =
        aLeftPosition > aRightPosition
            ? aLeftPosition - aRightPosition
            : aRightPosition - aLeftPosition;
    if (aLaneDistance > 1U) {
        return kInfiniteFragmentDistance;
    }

    const std::size_t aLeftFlat =
        (aLeftPosition * kLaneSplitCount) + pLeftSplit;
    const std::size_t aRightFlat =
        (aRightPosition * kLaneSplitCount) + pRightSplit;
    return static_cast<std::uint64_t>(
        aLeftFlat > aRightFlat
            ? aLeftFlat - aRightFlat
            : aRightFlat - aLeftFlat
    );
}

std::uint64_t PairDistance(const Candidate &pLeft,
                           const Candidate &pRight) {
    std::uint64_t aDistance = 0ULL;
    for (std::size_t aLogical = 0U;
         aLogical < kLaneSplitCount;
         ++aLogical) {
        for (std::size_t aRole = 0U;
             aRole < gLanes.size();
             ++aRole) {
            const std::size_t aLeftLane =
                pLeft.mRoleLaneIndexes[aLogical][aRole];
            const std::size_t aRightLane =
                pRight.mRoleLaneIndexes[aLogical][aRole];
            aDistance += FragmentDistance(
                aLeftLane,
                pLeft.mPhysicalLaneSplits[aLeftLane][aLogical],
                aRightLane,
                pRight.mPhysicalLaneSplits[aRightLane][aLogical]
            );
        }
    }
    return aDistance;
}

Score FamilyScore(const Candidate &pCandidate) {
    const std::uint64_t aMaximumDistance =
        static_cast<std::uint64_t>(
            gLanes.size() * kLaneSplitCount
        ) * kInfiniteFragmentDistance;
    Score aScore;
    aScore.mMinimum = gCandidates.empty()
        ? aMaximumDistance
        : std::numeric_limits<std::uint64_t>::max();

    for (const Candidate &aOther : gCandidates) {
        const std::uint64_t aDistance =
            PairDistance(pCandidate, aOther);
        aScore.mMinimum =
            std::min(aScore.mMinimum, aDistance);
        aScore.mTotal += aDistance;
    }

    return aScore;
}

bool Better(const Score &pCandidate,
            const Score &pBest) {
    if (pCandidate.mMinimum != pBest.mMinimum) {
        return pCandidate.mMinimum > pBest.mMinimum;
    }
    return pCandidate.mTotal > pBest.mTotal;
}

Candidate Explore(const std::uint64_t pCases,
                  Score *pScore) {
    Candidate aBest;
    Score aBestScore;
    bool aHasBest = false;

    for (std::uint64_t i = 0ULL; i < pCases; ++i) {
        Candidate aCandidate = MakeCandidate();
        if (!CandidateIsValid(aCandidate)) {
            continue;
        }
        const Score aScore = FamilyScore(aCandidate);
        if (!aHasBest || Better(aScore, aBestScore)) {
            aBest = std::move(aCandidate);
            aBestScore = aScore;
            aHasBest = true;
        }
    }

    if (pScore != nullptr) {
        *pScore = aBestScore;
    }
    return aBest;
}

char SplitLetter(const std::size_t pIndex) {
    return static_cast<char>('A' + pIndex);
}

std::string RenderDeclarations(const Candidate &pCandidate,
                               const std::size_t pCandidateIndex,
                               const Score &pScore,
                               const std::uint64_t pCases) {
    std::ostringstream aStream;
    const std::uint64_t aMaximumDistance =
        static_cast<std::uint64_t>(
            gLanes.size() * kLaneSplitCount
        ) * kInfiniteFragmentDistance;

    aStream << "// LaneSplitControl candidate "
            << (pCandidateIndex + 1U)
            << " (" << kNames[pCandidateIndex] << ")\n"
            << "// maximin " << pScore.mMinimum << "/"
            << aMaximumDistance
            << ", family total " << pScore.mTotal
            << ", explored " << pCases << " cases\n";

    for (std::size_t aLogical = 0U;
         aLogical < kLaneSplitCount;
         ++aLogical) {
        aStream << "// loop " << SplitLetter(aLogical)
                << " role mapping:";
        for (const std::uint8_t aLaneIndex :
             pCandidate.mRoleLaneIndexes[aLogical]) {
            const std::uint8_t aPhysical =
                pCandidate
                    .mPhysicalLaneSplits[aLaneIndex][aLogical];
            aStream << " "
                    << BufAliasName(TwistBufferKey::LaneSplit(
                           gLanes[aLaneIndex],
                           aPhysical
                       ));
        }
        aStream << "\n";
    }
    aStream << "\n";

    for (std::size_t aLane = 0U; aLane < gLanes.size(); ++aLane) {
        const LaneSplitControl::Slot aSlot = gLanes[aLane];
        const std::string aBaseAlias = BufAliasName(aSlot);

        for (std::size_t aPhysical = 0U;
             aPhysical < kLaneSplitCount;
             ++aPhysical) {
            const TwistBufferKey aKey = TwistBufferKey::LaneSplit(
                aSlot,
                static_cast<std::uint8_t>(aPhysical)
            );
            aStream << "std::uint8_t *" << BufAliasName(aKey)
                    << " = " << aBaseAlias
                    << " + (W_KEY * " << aPhysical << "U);\n";
        }
        aStream << "\n";
    }

    return aStream.str();
}

bool CandidateAndLaneIndex(const std::size_t pCandidateIndex,
                           const LaneSplitControl::Slot pLane,
                           std::size_t *pLaneIndex,
                           std::string *pErrorMessage) {
    if (pCandidateIndex >= gCandidates.size()) {
        SetError(pErrorMessage,
                 "LaneSplitControl candidate has not been generated");
        return false;
    }
    const auto aIterator = std::find(gLanes.begin(),
                                     gLanes.end(),
                                     pLane);
    if (aIterator == gLanes.end()) {
        SetError(pErrorMessage,
                 "LaneSplitControl lane has not been registered");
        return false;
    }
    if (pLaneIndex != nullptr) {
        *pLaneIndex =
            static_cast<std::size_t>(aIterator - gLanes.begin());
    }
    return true;
}

std::vector<std::uint64_t> CandidateValues(
    const Candidate &pCandidate) {
    std::vector<std::uint64_t> aValues;
    aValues.reserve(
        gLanes.size() * ((kLaneSplitCount * 2U) + 1U)
    );
    for (std::size_t aLane = 0U; aLane < gLanes.size(); ++aLane) {
        aValues.push_back(
            static_cast<std::uint64_t>(gLanes[aLane])
        );
        for (const std::uint8_t aPhysical :
             pCandidate.mPhysicalLaneSplits[aLane]) {
            aValues.push_back(aPhysical);
        }
    }
    for (std::size_t aLogical = 0U;
         aLogical < kLaneSplitCount;
         ++aLogical) {
        for (const std::uint8_t aLaneIndex :
             pCandidate.mRoleLaneIndexes[aLogical]) {
            aValues.push_back(
                static_cast<std::uint64_t>(gLanes[aLaneIndex])
            );
        }
    }
    return aValues;
}

Candidate CandidateFromValues(
    const std::vector<std::uint64_t> &pValues,
    std::string *pWarningMessage) {
    Candidate aCandidate;
    aCandidate.mPhysicalLaneSplits.resize(gLanes.size());
    std::vector<bool> aLoadedLanes(gLanes.size(), false);
    std::size_t aInvalidCount = 0U;

    const std::size_t aRecordWidth = kLaneSplitCount + 1U;
    for (std::size_t aRecord = 0U;
         aRecord < gLanes.size();
         ++aRecord) {
        const std::size_t aBase = aRecord * aRecordWidth;
        const LaneSplitControl::Slot aSlot =
            static_cast<LaneSplitControl::Slot>(
            aBase < pValues.size() ? pValues[aBase] : 0ULL
        );
        const auto aLaneIterator =
            std::find(gLanes.begin(), gLanes.end(), aSlot);
        if (aLaneIterator == gLanes.end()) {
            ++aInvalidCount;
            continue;
        }
        const std::size_t aLaneIndex =
            static_cast<std::size_t>(aLaneIterator - gLanes.begin());
        if (aLoadedLanes[aLaneIndex]) {
            ++aInvalidCount;
            continue;
        }
        aLoadedLanes[aLaneIndex] = true;
        for (std::size_t aLogical = 0U;
             aLogical < kLaneSplitCount;
             ++aLogical) {
            const std::size_t aValueIndex = aBase + 1U + aLogical;
            const std::uint64_t aRaw =
                aValueIndex < pValues.size()
                    ? pValues[aValueIndex]
                    : 0ULL;
            if (aRaw >= kLaneSplitCount) {
                ++aInvalidCount;
                continue;
            }
            aCandidate.mPhysicalLaneSplits[aLaneIndex][aLogical] =
                static_cast<std::uint8_t>(aRaw);
        }
    }

    const std::size_t aRoleBase =
        gLanes.size() * aRecordWidth;
    for (std::size_t aLogical = 0U;
         aLogical < kLaneSplitCount;
         ++aLogical) {
        std::vector<std::uint8_t> &aRoleLanes =
            aCandidate.mRoleLaneIndexes[aLogical];
        aRoleLanes.reserve(gLanes.size());
        for (std::size_t aRole = 0U;
             aRole < gLanes.size();
             ++aRole) {
            const std::size_t aValueIndex =
                aRoleBase + (aLogical * gLanes.size()) + aRole;
            const LaneSplitControl::Slot aSlot =
                static_cast<LaneSplitControl::Slot>(
                    aValueIndex < pValues.size()
                        ? pValues[aValueIndex]
                        : 0ULL
                );
            const auto aLaneIterator =
                std::find(gLanes.begin(), gLanes.end(), aSlot);
            if (aLaneIterator == gLanes.end()) {
                ++aInvalidCount;
                aRoleLanes.push_back(0U);
                continue;
            }
            aRoleLanes.push_back(
                static_cast<std::uint8_t>(
                    aLaneIterator - gLanes.begin()
                )
            );
        }
    }

    if ((pWarningMessage != nullptr) && (aInvalidCount != 0U)) {
        *pWarningMessage =
            "LaneSplitControl contained " +
            std::to_string(aInvalidCount) +
            " invalid value(s).";
    }
    return aCandidate;
}

} // namespace

void LaneSplitControl::Reset(const std::uint64_t pSeed) {
    static_assert(S_BLOCK == (W_KEY * kLaneSplitCount),
                  "LaneSplitControl needs sixteen W_KEY fragments.");
    gLanes.clear();
    gGroups.clear();
    gCandidates.clear();
    gRendered.clear();
    gRandomState =
        pSeed == 0ULL ? 0x4C414E4553504C54ULL : pSeed;
    gDidReset = true;
}

bool LaneSplitControl::AddLaneGroup(const LaneGroup &pLanes,
                                    std::string *pErrorMessage) {
    if (!gDidReset) {
        SetError(pErrorMessage,
                 "LaneSplitControl::Reset must be called first");
        return false;
    }
    if (!gCandidates.empty()) {
        SetError(pErrorMessage,
                 "Lane groups cannot change after candidate generation starts");
        return false;
    }
    if (pLanes.empty() || (pLanes.size() > kLaneSplitCount)) {
        SetError(pErrorMessage,
                 "A lane group must contain between one and sixteen lanes");
        return false;
    }

    for (Slot aLane : pLanes) {
        if (aLane == Slot::kInvalid) {
            SetError(pErrorMessage,
                     "A lane group contained an invalid slot");
            return false;
        }
        if (TwistWorkSpace::GetBufferLength(aLane) != S_BLOCK) {
            SetError(pErrorMessage,
                     "A lane group contained a non-S_BLOCK slot");
            return false;
        }
        if ((std::find(gLanes.begin(), gLanes.end(), aLane) !=
             gLanes.end()) ||
            (std::count(pLanes.begin(),
                        pLanes.end(),
                        aLane) > 1)) {
            SetError(pErrorMessage,
                     "A lane can only be registered once");
            return false;
        }
    }

    RegisteredGroup aGroup;
    for (Slot aLane : pLanes) {
        aGroup.mLanes.push_back(aLane);
        aGroup.mLaneIndexes.push_back(gLanes.size());
        gLanes.push_back(aLane);
    }
    gGroups.push_back(std::move(aGroup));
    return true;
}

bool LaneSplitControl::AddLaneGroup(
    const std::initializer_list<Slot> pLanes,
    std::string *pErrorMessage) {
    return AddLaneGroup(LaneGroup(pLanes), pErrorMessage);
}

std::string LaneSplitControl::Generate(
    const std::uint64_t pExplorationCases) {
    if (!gDidReset || gGroups.empty() ||
        (gCandidates.size() >= kCandidateCount)) {
        return "";
    }

    const std::uint64_t aCases =
        std::max<std::uint64_t>(1ULL, pExplorationCases);
    Score aScore;
    const std::uint64_t aEffectiveCases =
        gCandidates.empty() ? 1ULL : aCases;
    Candidate aCandidate = Explore(aEffectiveCases, &aScore);
    if (!CandidateIsValid(aCandidate)) {
        return "";
    }
    const std::size_t aIndex = gCandidates.size();
    const std::string aRendered =
        RenderDeclarations(aCandidate,
                           aIndex,
                           aScore,
                           aEffectiveCases);
    gCandidates.push_back(std::move(aCandidate));
    gRendered.push_back(aRendered);
    return aRendered;
}

bool LaneSplitControl::PhysicalLaneSplit(
    const std::size_t pCandidateIndex,
    const Slot pLane,
    const std::size_t pLogicalLaneSplit,
    std::uint8_t *pPhysicalLaneSplit,
    std::string *pErrorMessage) {
    if (pPhysicalLaneSplit == nullptr) {
        SetError(pErrorMessage,
                 "Physical lane split output was null");
        return false;
    }
    if (pLogicalLaneSplit >= kLaneSplitCount) {
        SetError(pErrorMessage,
                 "Logical lane split must be between A and P");
        return false;
    }

    std::size_t aLaneIndex = 0U;
    if (!CandidateAndLaneIndex(pCandidateIndex,
                               pLane,
                               &aLaneIndex,
                               pErrorMessage)) {
        return false;
    }
    *pPhysicalLaneSplit =
        gCandidates[pCandidateIndex]
            .mPhysicalLaneSplits[aLaneIndex][pLogicalLaneSplit];
    return true;
}

bool LaneSplitControl::LinkStageSlice(
    GSeedRunStageSliceSpec *pStageSlice,
    const std::size_t pCandidateIndex,
    const std::size_t pLogicalLaneSplit,
    std::string *pErrorMessage) {
    if (pStageSlice == nullptr) {
        SetError(pErrorMessage,
                 "Stage slice was null");
        return false;
    }

    if (pCandidateIndex >= gCandidates.size()) {
        SetError(pErrorMessage,
                 "LaneSplitControl candidate has not been generated");
        return false;
    }
    if (pLogicalLaneSplit >= kLaneSplitCount) {
        SetError(pErrorMessage,
                 "Logical lane split must be between A and P");
        return false;
    }

    const Candidate &aCandidate =
        gCandidates[pCandidateIndex];
    const std::vector<std::uint8_t> &aRoleLanes =
        aCandidate.mRoleLaneIndexes[pLogicalLaneSplit];
    const std::size_t aSourceCount =
        pStageSlice->mIngressSources.size() +
        pStageSlice->mCrossSources.size();
    if (aRoleLanes.size() != aSourceCount) {
        SetError(pErrorMessage,
                 "Stage slice source count did not match the registered "
                 "lane role count");
        return false;
    }

    pStageSlice->mSourceLaneSplits.clear();
    for (std::size_t aRole = 0U;
         aRole < aRoleLanes.size();
         ++aRole) {
        const std::size_t aLaneIndex = aRoleLanes[aRole];
        if (aLaneIndex >= gLanes.size()) {
            SetError(pErrorMessage,
                     "LaneSplitControl role referenced an invalid lane");
            return false;
        }
        const Slot aLane = gLanes[aLaneIndex];
        if (aRole < pStageSlice->mIngressSources.size()) {
            pStageSlice->mIngressSources[aRole] = aLane;
        } else {
            pStageSlice->mCrossSources[
                aRole - pStageSlice->mIngressSources.size()
            ] = aLane;
        }
        std::uint8_t aPhysicalLaneSplit = 255U;
        if (!PhysicalLaneSplit(pCandidateIndex,
                               aLane,
                               pLogicalLaneSplit,
                               &aPhysicalLaneSplit,
                               pErrorMessage) ||
            !pStageSlice->SetSourceLaneSplit(aLane,
                                             aPhysicalLaneSplit,
                                             pErrorMessage)) {
            return false;
        }
    }
    return true;
}

bool LaneSplitControl::LinkStageConfig(
    GSeedRunStageConfig *pConfig,
    const std::size_t pCandidateIndex,
    std::string *pErrorMessage) {
    if (pConfig == nullptr) {
        SetError(pErrorMessage,
                 "Stage config was null");
        return false;
    }
    if (pConfig->mSlices.size() > kLaneSplitCount) {
        SetError(pErrorMessage,
                 "Automatic stage linking supports at most sixteen slices");
        return false;
    }

    std::vector<std::uint8_t> aLogicalLaneSplits;
    aLogicalLaneSplits.reserve(pConfig->mSlices.size());
    for (std::size_t i = 0U; i < pConfig->mSlices.size(); ++i) {
        aLogicalLaneSplits.push_back(static_cast<std::uint8_t>(i));
    }
    return LinkStageConfig(pConfig,
                           pCandidateIndex,
                           aLogicalLaneSplits,
                           pErrorMessage);
}

bool LaneSplitControl::LinkStageConfig(
    GSeedRunStageConfig *pConfig,
    const std::size_t pCandidateIndex,
    const std::vector<std::uint8_t> &pLogicalLaneSplits,
    std::string *pErrorMessage) {
    if (pConfig == nullptr) {
        SetError(pErrorMessage,
                 "Stage config was null");
        return false;
    }
    if (pLogicalLaneSplits.size() != pConfig->mSlices.size()) {
        SetError(pErrorMessage,
                 "Logical lane split count did not match stage slice count");
        return false;
    }
    if (pConfig->mSlices.empty()) {
        SetError(pErrorMessage,
                 "Stage config had no slices to link");
        return false;
    }

    // A split is a W_KEY-sized view. Keeping the stage loop at S_BLOCK
    // would revisit the same fragment sixteen times through W_KEY1.
    GSeedRunStageConfig aLinkedConfig = *pConfig;
    aLinkedConfig.mLoopBegin = 0;
    aLinkedConfig.mLoopBeginText.clear();
    aLinkedConfig.mLoopCeiling = W_KEY;
    aLinkedConfig.mLoopEndText = "W_KEY";

    for (std::size_t i = 0U; i < aLinkedConfig.mSlices.size(); ++i) {
        if (!LinkStageSlice(&aLinkedConfig.mSlices[i],
                            pCandidateIndex,
                            pLogicalLaneSplits[i],
                            pErrorMessage)) {
            return false;
        }
    }
    *pConfig = std::move(aLinkedConfig);
    return true;
}

std::string LaneSplitControl::Declarations(
    const std::size_t pCandidateIndex) {
    return pCandidateIndex < gRendered.size()
        ? gRendered[pCandidateIndex]
        : "";
}

void LaneSplitControl::Print() {
    for (const std::string &aText : gRendered) {
        std::printf("%s\n", aText.c_str());
    }
}

bool LaneSplitControl::SaveValues(const std::string &pFolder,
                                  std::string *pErrorMessage) {
    if (gCandidates.size() != kCandidateCount) {
        SetError(pErrorMessage,
                 "LaneSplitControl needs all 33 candidates before "
                 "saving values.");
        return false;
    }

    const std::string aFolder = FileIO::ProjectRoot(pFolder);
    for (std::size_t i = 0U; i < gCandidates.size(); ++i) {
        if (!CandidateIsValid(gCandidates[i])) {
            SetError(pErrorMessage,
                     "LaneSplitControl refused to save invalid candidate " +
                     std::to_string(i + 1U) + ".");
            return false;
        }
        char aName[48];
        std::snprintf(aName,
                      sizeof(aName),
                      "LaneSplit_Candidate%02zu.bin",
                      i + 1U);
        const std::string aCandidatePath =
            FileIO::Join(aFolder, aName);
        if (!ControlValueFile::Save(
                aCandidatePath,
                ControlValueFile::Kind::kLaneSplit,
                CandidateValues(gCandidates[i]),
                pErrorMessage)) {
            return false;
        }
    }
    return true;
}

bool LaneSplitControl::LoadValues(
    const std::string &pFolder,
    std::string *pErrorMessage) {
    if (!gDidReset || gGroups.empty() || !gCandidates.empty()) {
        SetError(pErrorMessage,
                 "LaneSplitControl::Reset and AddLaneGroup must precede "
                 "value loading.");
        return false;
    }

    const std::string aFolder = FileIO::ProjectRoot(pFolder);
    const std::size_t aExpectedValueCount =
        gLanes.size() * ((kLaneSplitCount * 2U) + 1U);
    for (std::size_t i = 0U; i < kCandidateCount; ++i) {
        char aName[48];
        std::snprintf(aName,
                      sizeof(aName),
                      "LaneSplit_Candidate%02zu.bin",
                      i + 1U);
        std::vector<std::uint64_t> aValues;
        std::string aLoadWarning;
        if (!ControlValueFile::Load(
                FileIO::Join(aFolder, aName),
                ControlValueFile::Kind::kLaneSplit,
                aExpectedValueCount,
                &aValues,
                &aLoadWarning)) {
            SetError(pErrorMessage, aLoadWarning);
            return false;
        }
        std::string aValueWarning;
        Candidate aCandidate =
            CandidateFromValues(aValues, &aValueWarning);
        if (!aValueWarning.empty()) {
            SetError(pErrorMessage, aValueWarning);
            return false;
        }
        if (!CandidateIsValid(aCandidate)) {
            SetError(pErrorMessage,
                     "LaneSplitControl candidate " +
                     std::to_string(i + 1U) +
                     " was not a complete lane/split permutation.");
            return false;
        }
        const Score aScore = FamilyScore(aCandidate);
        const std::string aRendered =
            RenderDeclarations(aCandidate, i, aScore, 0ULL);
        gCandidates.push_back(std::move(aCandidate));
        gRendered.push_back(aRendered);
    }
    return true;
}

std::size_t LaneSplitControl::GeneratedCount() {
    return gCandidates.size();
}
