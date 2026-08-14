#include "ResidualKDFControl.hpp"

#include "ControlValueFile.hpp"
#include "FileIO.hpp"
#include "Random.hpp"
#include "ResidualBucket.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <limits>
#include <sstream>
#include <vector>

namespace {

using Candidate = ResidualKDFControl::Candidate;
using Slot = ResidualKDFControl::Slot;

constexpr std::array<std::size_t,
                     ResidualKDFControl::kWithdrawalCountPerDomain>
kWithdrawalSizes = {{8U, 12U, 15U, 15U, 15U, 15U, 15U}};

struct Distance {
    std::uint64_t mExact = 0ULL;
    std::uint64_t mFamily = 0ULL;
    std::uint64_t mWeighted = 0ULL;
    std::uint64_t mMinimumWithdrawalExact =
        std::numeric_limits<std::uint64_t>::max();
    std::uint64_t mMinimumWithdrawalFamily =
        std::numeric_limits<std::uint64_t>::max();
    std::uint64_t mMinimumWithdrawalWeighted =
        std::numeric_limits<std::uint64_t>::max();
};

struct Score {
    std::uint64_t mMinimumWithdrawalWeighted = 0ULL;
    std::uint64_t mMinimumWithdrawalFamily = 0ULL;
    std::uint64_t mMinimumWithdrawalExact = 0ULL;
    std::uint64_t mMinimumWeighted = 0ULL;
    std::uint64_t mMinimumFamily = 0ULL;
    std::uint64_t mMinimumExact = 0ULL;
    std::uint64_t mTotalWeighted = 0ULL;
    std::uint64_t mTotalFamily = 0ULL;
    std::uint64_t mTotalExact = 0ULL;
};

std::vector<Candidate> sCandidates;
bool sDidReset = false;

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

template <typename... Slots>
std::vector<Slot> SlotList(const Slots... pSlots) {
    return {pSlots...};
}

void SimulateOneDomain(ResidualBucket *pBucket) {
    // KDF A — Stage A
    pBucket->Remove(SlotList(Slot::kSourceLane,
                             Slot::kNonceLane,
                             Slot::kShadowLaneA,
                             Slot::kShadowLaneB,
                             Slot::kShadowLaneC,
                             Slot::kShadowLaneD));

    // KDF A — Stage B
    pBucket->Remove(SlotList(Slot::kShadowLaneA,
                             Slot::kShadowLaneB,
                             Slot::kShadowLaneC,
                             Slot::kShadowLaneD,
                             Slot::kFireLaneA,
                             Slot::kFireLaneB,
                             Slot::kFireLaneC,
                             Slot::kFireLaneD));
    pBucket->AddResiduals(SlotList(Slot::kShadowLaneA,
                                   Slot::kShadowLaneB,
                                   Slot::kShadowLaneC,
                                   Slot::kShadowLaneD));
    pBucket->AddResiduals(SlotList(Slot::kFireLaneA,
                                   Slot::kFireLaneB,
                                   Slot::kFireLaneC,
                                   Slot::kFireLaneD));

    // KDF A — Stage C
    pBucket->Remove(SlotList(Slot::kVaporLaneA,
                             Slot::kVaporLaneB,
                             Slot::kVaporLaneC,
                             Slot::kVaporLaneD,
                             Slot::kKineticLaneA,
                             Slot::kKineticLaneB,
                             Slot::kKineticLaneC,
                             Slot::kKineticLaneD));
    pBucket->Withdraw("KDF A — Stage C", 8);
    pBucket->AddResiduals(SlotList(Slot::kVaporLaneA,
                                   Slot::kVaporLaneB,
                                   Slot::kVaporLaneC,
                                   Slot::kVaporLaneD));

    // KDF B — Stage A
    pBucket->Remove(SlotList(Slot::kKineticLaneA,
                             Slot::kKineticLaneB,
                             Slot::kKineticLaneC,
                             Slot::kKineticLaneD,
                             Slot::kEvocationLaneA,
                             Slot::kEvocationLaneB,
                             Slot::kEvocationLaneC,
                             Slot::kEvocationLaneD));
    pBucket->Withdraw("KDF B — Stage A", 12);
    pBucket->AddResiduals(SlotList(Slot::kKineticLaneA,
                                   Slot::kKineticLaneB,
                                   Slot::kKineticLaneC,
                                   Slot::kKineticLaneD));

    // KDF B — Stage B
    pBucket->Remove(SlotList(Slot::kEvocationLaneA,
                             Slot::kEvocationLaneB,
                             Slot::kEvocationLaneC,
                             Slot::kEvocationLaneD,
                             Slot::kRunicLaneA,
                             Slot::kRunicLaneB,
                             Slot::kRunicLaneC,
                             Slot::kRunicLaneD));
    pBucket->Withdraw("KDF B — Stage B", 15);
    pBucket->AddResiduals(SlotList(Slot::kEvocationLaneA,
                                   Slot::kEvocationLaneB,
                                   Slot::kEvocationLaneC,
                                   Slot::kEvocationLaneD));
    pBucket->AddResiduals(SlotList(Slot::kRunicLaneA,
                                   Slot::kRunicLaneB,
                                   Slot::kRunicLaneC,
                                   Slot::kRunicLaneD));

    // KDF B — Stage C
    pBucket->Remove(SlotList(Slot::kDivinationLaneA,
                             Slot::kDivinationLaneB,
                             Slot::kDivinationLaneC,
                             Slot::kDivinationLaneD,
                             Slot::kAbjurationLaneA,
                             Slot::kAbjurationLaneB,
                             Slot::kAbjurationLaneC,
                             Slot::kAbjurationLaneD));
    pBucket->Withdraw("KDF B — Stage C", 15);
    pBucket->AddResiduals(SlotList(Slot::kDivinationLaneA,
                                   Slot::kDivinationLaneB,
                                   Slot::kDivinationLaneC,
                                   Slot::kDivinationLaneD));

    // KDF C — Stage A
    pBucket->Remove(SlotList(Slot::kAbjurationLaneA,
                             Slot::kAbjurationLaneB,
                             Slot::kAbjurationLaneC,
                             Slot::kAbjurationLaneD,
                             Slot::kAetherLaneA,
                             Slot::kAetherLaneB,
                             Slot::kAetherLaneC,
                             Slot::kAetherLaneD));
    pBucket->Withdraw("KDF C — Stage A", 15);
    pBucket->AddResiduals(SlotList(Slot::kAbjurationLaneA,
                                   Slot::kAbjurationLaneB,
                                   Slot::kAbjurationLaneC,
                                   Slot::kAbjurationLaneD));

    // KDF C — Stage B
    pBucket->Remove(SlotList(Slot::kAetherLaneA,
                             Slot::kAetherLaneB,
                             Slot::kAetherLaneC,
                             Slot::kAetherLaneD,
                             Slot::kLunarLaneA,
                             Slot::kLunarLaneB,
                             Slot::kLunarLaneC,
                             Slot::kLunarLaneD));
    pBucket->Withdraw("KDF C — Stage B", 15);
    pBucket->AddResiduals(SlotList(Slot::kAetherLaneA,
                                   Slot::kAetherLaneB,
                                   Slot::kAetherLaneC,
                                   Slot::kAetherLaneD));
    pBucket->AddResiduals(SlotList(Slot::kLunarLaneA,
                                   Slot::kLunarLaneB,
                                   Slot::kLunarLaneC,
                                   Slot::kLunarLaneD));

    // KDF C — Stage C
    pBucket->Remove(SlotList(Slot::kEarthLaneA,
                             Slot::kEarthLaneB,
                             Slot::kEarthLaneC,
                             Slot::kEarthLaneD,
                             Slot::kCrystalLaneA,
                             Slot::kCrystalLaneB,
                             Slot::kCrystalLaneC,
                             Slot::kCrystalLaneD));
    pBucket->Withdraw("KDF C — Stage C", 15);
    pBucket->AddResiduals(SlotList(Slot::kEarthLaneA,
                                   Slot::kEarthLaneB,
                                   Slot::kEarthLaneC,
                                   Slot::kEarthLaneD));
}

std::vector<std::vector<Slot>> CandidateWithdrawals(
    const Candidate &pCandidate) {
    std::vector<std::vector<Slot>> aResult;
    aResult.reserve(ResidualKDFControl::kWithdrawalCount);
    std::size_t aSlotIndex = 0U;
    for (std::size_t aDomain = 0U;
         aDomain < ResidualKDFControl::kDomainCount;
         ++aDomain) {
        for (const std::size_t aCount : kWithdrawalSizes) {
            aResult.emplace_back(
                pCandidate.mSlots.begin() +
                    static_cast<std::ptrdiff_t>(aSlotIndex),
                pCandidate.mSlots.begin() +
                    static_cast<std::ptrdiff_t>(aSlotIndex + aCount)
            );
            aSlotIndex += aCount;
        }
    }
    return aResult;
}

Candidate RandomCandidate() {
    ResidualBucket aBucket;
    aBucket.SetVerbose(false);
    aBucket.BeginWithdrawalRecording();
    for (std::size_t aDomain = 0U;
         aDomain < ResidualKDFControl::kDomainCount;
         ++aDomain) {
        SimulateOneDomain(&aBucket);
    }

    Candidate aCandidate;
    std::size_t aSlotIndex = 0U;
    for (const std::vector<Slot> &aWithdrawal :
         aBucket.RecordedWithdrawals()) {
        for (const Slot aSlot : aWithdrawal) {
            if (aSlotIndex < aCandidate.mSlots.size()) {
                aCandidate.mSlots[aSlotIndex++] = aSlot;
            }
        }
    }
    return aCandidate;
}

std::size_t LaneFamily(const Slot pSlot) {
    constexpr std::array<Slot, 25U> kFamilyStarts = {{
        Slot::kEarthLaneA, Slot::kFireLaneA, Slot::kWindLaneA,
        Slot::kWaterLaneA, Slot::kRainbowLaneA, Slot::kLightningLaneA,
        Slot::kIceLaneA, Slot::kPlasmaLaneA, Slot::kShadowLaneA,
        Slot::kCrystalLaneA, Slot::kAetherLaneA, Slot::kCelestialLaneA,
        Slot::kVaporLaneA, Slot::kKineticLaneA, Slot::kSonicLaneA,
        Slot::kPlanarLaneA, Slot::kFrostLaneA, Slot::kArcaneLaneA,
        Slot::kLunarLaneA, Slot::kRunicLaneA, Slot::kGloomLaneA,
        Slot::kAbjurationLaneA, Slot::kDivinationLaneA,
        Slot::kEvocationLaneA, Slot::kSpiritLaneA,
    }};
    const int aValue = static_cast<int>(pSlot);
    for (std::size_t i = 0U; i < kFamilyStarts.size(); ++i) {
        const int aOffset = aValue - static_cast<int>(kFamilyStarts[i]);
        if ((aOffset >= 0) && (aOffset < 4)) {
            return i;
        }
    }
    return kFamilyStarts.size() + static_cast<std::size_t>(aValue);
}

Distance CandidateDistance(const Candidate &pLeft,
                           const Candidate &pRight) {
    Distance aDistance;
    std::size_t aSlotIndex = 0U;
    for (std::size_t aDomain = 0U;
         aDomain < ResidualKDFControl::kDomainCount;
         ++aDomain) {
        for (const std::size_t aWithdrawalSize : kWithdrawalSizes) {
            std::uint64_t aWithdrawalExact = 0ULL;
            std::uint64_t aWithdrawalFamily = 0ULL;
            for (std::size_t i = 0U; i < aWithdrawalSize; ++i) {
                const Slot aLeft = pLeft.mSlots[aSlotIndex + i];
                const Slot aRight = pRight.mSlots[aSlotIndex + i];
                if (aLeft != aRight) {
                    ++aWithdrawalExact;
                }
                if (LaneFamily(aLeft) != LaneFamily(aRight)) {
                    ++aWithdrawalFamily;
                }
            }
            const std::uint64_t aWithdrawalWeighted =
                aWithdrawalExact + (4ULL * aWithdrawalFamily);
            aDistance.mMinimumWithdrawalExact = std::min(
                aDistance.mMinimumWithdrawalExact,
                aWithdrawalExact
            );
            aDistance.mMinimumWithdrawalFamily = std::min(
                aDistance.mMinimumWithdrawalFamily,
                aWithdrawalFamily
            );
            aDistance.mMinimumWithdrawalWeighted = std::min(
                aDistance.mMinimumWithdrawalWeighted,
                aWithdrawalWeighted
            );
            aDistance.mExact += aWithdrawalExact;
            aDistance.mFamily += aWithdrawalFamily;
            aSlotIndex += aWithdrawalSize;
        }
    }
    aDistance.mWeighted = aDistance.mExact + (4ULL * aDistance.mFamily);
    return aDistance;
}

Score CandidateScore(const Candidate &pCandidate) {
    Score aScore;
    if (sCandidates.empty()) {
        aScore.mMinimumWithdrawalWeighted =
            std::numeric_limits<std::uint64_t>::max();
        aScore.mMinimumWithdrawalFamily =
            std::numeric_limits<std::uint64_t>::max();
        aScore.mMinimumWithdrawalExact =
            std::numeric_limits<std::uint64_t>::max();
        aScore.mMinimumWeighted = std::numeric_limits<std::uint64_t>::max();
        aScore.mMinimumFamily = std::numeric_limits<std::uint64_t>::max();
        aScore.mMinimumExact = std::numeric_limits<std::uint64_t>::max();
        return aScore;
    }

    aScore.mMinimumWithdrawalWeighted =
        std::numeric_limits<std::uint64_t>::max();
    aScore.mMinimumWithdrawalFamily =
        std::numeric_limits<std::uint64_t>::max();
    aScore.mMinimumWithdrawalExact =
        std::numeric_limits<std::uint64_t>::max();
    aScore.mMinimumWeighted = std::numeric_limits<std::uint64_t>::max();
    aScore.mMinimumFamily = std::numeric_limits<std::uint64_t>::max();
    aScore.mMinimumExact = std::numeric_limits<std::uint64_t>::max();
    for (const Candidate &aSelected : sCandidates) {
        const Distance aDistance = CandidateDistance(pCandidate, aSelected);
        aScore.mMinimumWithdrawalWeighted = std::min(
            aScore.mMinimumWithdrawalWeighted,
            aDistance.mMinimumWithdrawalWeighted
        );
        aScore.mMinimumWithdrawalFamily = std::min(
            aScore.mMinimumWithdrawalFamily,
            aDistance.mMinimumWithdrawalFamily
        );
        aScore.mMinimumWithdrawalExact = std::min(
            aScore.mMinimumWithdrawalExact,
            aDistance.mMinimumWithdrawalExact
        );
        aScore.mMinimumWeighted = std::min(aScore.mMinimumWeighted,
                                           aDistance.mWeighted);
        aScore.mMinimumFamily = std::min(aScore.mMinimumFamily,
                                         aDistance.mFamily);
        aScore.mMinimumExact = std::min(aScore.mMinimumExact,
                                        aDistance.mExact);
        aScore.mTotalWeighted += aDistance.mWeighted;
        aScore.mTotalFamily += aDistance.mFamily;
        aScore.mTotalExact += aDistance.mExact;
    }
    return aScore;
}

bool Better(const Score &pCandidate,
            const Score &pBest) {
    if (pCandidate.mMinimumWithdrawalWeighted !=
        pBest.mMinimumWithdrawalWeighted) {
        return pCandidate.mMinimumWithdrawalWeighted >
               pBest.mMinimumWithdrawalWeighted;
    }
    if (pCandidate.mMinimumWithdrawalFamily !=
        pBest.mMinimumWithdrawalFamily) {
        return pCandidate.mMinimumWithdrawalFamily >
               pBest.mMinimumWithdrawalFamily;
    }
    if (pCandidate.mMinimumWithdrawalExact !=
        pBest.mMinimumWithdrawalExact) {
        return pCandidate.mMinimumWithdrawalExact >
               pBest.mMinimumWithdrawalExact;
    }
    if (pCandidate.mMinimumWeighted != pBest.mMinimumWeighted) {
        return pCandidate.mMinimumWeighted > pBest.mMinimumWeighted;
    }
    if (pCandidate.mMinimumFamily != pBest.mMinimumFamily) {
        return pCandidate.mMinimumFamily > pBest.mMinimumFamily;
    }
    if (pCandidate.mMinimumExact != pBest.mMinimumExact) {
        return pCandidate.mMinimumExact > pBest.mMinimumExact;
    }
    if (pCandidate.mTotalWeighted != pBest.mTotalWeighted) {
        return pCandidate.mTotalWeighted > pBest.mTotalWeighted;
    }
    if (pCandidate.mTotalFamily != pBest.mTotalFamily) {
        return pCandidate.mTotalFamily > pBest.mTotalFamily;
    }
    return pCandidate.mTotalExact > pBest.mTotalExact;
}

std::vector<std::uint64_t> CandidateValues(const Candidate &pCandidate) {
    std::vector<std::uint64_t> aValues;
    aValues.reserve(pCandidate.mSlots.size());
    for (const Slot aSlot : pCandidate.mSlots) {
        aValues.push_back(static_cast<std::uint64_t>(aSlot));
    }
    return aValues;
}

Candidate CandidateFromValues(const std::vector<std::uint64_t> &pValues) {
    Candidate aCandidate;
    if (pValues.size() != aCandidate.mSlots.size()) {
        return aCandidate;
    }
    for (std::size_t i = 0U; i < pValues.size(); ++i) {
        aCandidate.mSlots[i] = static_cast<Slot>(pValues[i]);
    }
    return aCandidate;
}

bool Validate(const Candidate &pCandidate,
              std::string *pErrorMessage) {
    ResidualBucket aBucket;
    aBucket.SetVerbose(false);
    const std::vector<std::vector<Slot>> aWithdrawals =
        CandidateWithdrawals(pCandidate);
    if (aWithdrawals.size() != ResidualKDFControl::kWithdrawalCount) {
        SetError(pErrorMessage,
                 "Residual KDF candidate had the wrong withdrawal count");
        return false;
    }
    if (!aBucket.SetPlannedWithdrawals(aWithdrawals, pErrorMessage)) {
        return false;
    }
    for (std::size_t aDomain = 0U;
         aDomain < ResidualKDFControl::kDomainCount;
         ++aDomain) {
        SimulateOneDomain(&aBucket);
    }
    return aBucket.FinishPlannedWithdrawals(pErrorMessage);
}

} // namespace

void ResidualKDFControl::Reset(const std::uint64_t pSeed) {
    sCandidates.clear();
    Random::Seed(static_cast<int>(pSeed ^ (pSeed >> 32U)));
    sDidReset = true;
}

std::string ResidualKDFControl::Generate(
    const std::uint64_t pExplorationCases) {
    if (!sDidReset || (sCandidates.size() >= kCandidateCount)) {
        return "";
    }
    const std::uint64_t aCases =
        std::max<std::uint64_t>(1ULL, pExplorationCases);
    Candidate aBest{};
    Score aBestScore{};
    bool aHasBest = false;
    for (std::uint64_t aCase = 0ULL; aCase < aCases; ++aCase) {
        const Candidate aCandidate = RandomCandidate();
        const Score aScore = CandidateScore(aCandidate);
        if (!aHasBest || Better(aScore, aBestScore)) {
            aBest = aCandidate;
            aBestScore = aScore;
            aHasBest = true;
        }
    }
    std::string aError;
    if (!aHasBest || !Validate(aBest, &aError)) {
        return "";
    }
    sCandidates.push_back(aBest);

    std::ostringstream aText;
    aText << "ResidualKDFControl candidate " << sCandidates.size()
          << "/" << kCandidateCount << " cases=" << aCases;
    if (sCandidates.size() == 1U) {
        aText << " distance=first";
    } else {
        aText << " withdrawal-min={weighted:"
              << aBestScore.mMinimumWithdrawalWeighted
              << ", family:" << aBestScore.mMinimumWithdrawalFamily
              << ", exact:" << aBestScore.mMinimumWithdrawalExact << "}"
              << " flow-min={weighted:" << aBestScore.mMinimumWeighted
              << ", family:" << aBestScore.mMinimumFamily
              << ", exact:" << aBestScore.mMinimumExact << "}"
              << " total={weighted:" << aBestScore.mTotalWeighted
              << ", family:" << aBestScore.mTotalFamily
              << ", exact:" << aBestScore.mTotalExact << "}";
    }
    return aText.str();
}

bool ResidualKDFControl::SaveValues(
    const std::string &pFolder,
    std::string *pErrorMessage) {
    if (sCandidates.size() != kCandidateCount) {
        SetError(pErrorMessage,
                 "ResidualKDFControl requires all 17 candidates before saving");
        return false;
    }
    std::vector<std::uint64_t> aValues;
    aValues.reserve(kCandidateCount * kResidualSlotCount);
    for (std::size_t i = 0U; i < sCandidates.size(); ++i) {
        std::string aError;
        if (!Validate(sCandidates[i], &aError)) {
            SetError(pErrorMessage,
                     "ResidualKDFControl candidate " +
                     std::to_string(i) + " was invalid: " + aError);
            return false;
        }
        const std::vector<std::uint64_t> aCandidateValues =
            CandidateValues(sCandidates[i]);
        aValues.insert(aValues.end(),
                       aCandidateValues.begin(),
                       aCandidateValues.end());
    }
    return ControlValueFile::Save(
        FileIO::Join(FileIO::ProjectRoot(pFolder), "ResidualKDF.bin"),
        ControlValueFile::Kind::kResidualKDF,
        aValues,
        pErrorMessage
    );
}

bool ResidualKDFControl::LoadValues(
    const std::string &pFolder,
    std::string *pErrorMessage) {
    if (!sDidReset || !sCandidates.empty()) {
        SetError(pErrorMessage,
                 "ResidualKDFControl::Reset must precede value loading");
        return false;
    }
    std::vector<std::uint64_t> aValues;
    if (!ControlValueFile::Load(
            FileIO::Join(FileIO::ProjectRoot(pFolder), "ResidualKDF.bin"),
            ControlValueFile::Kind::kResidualKDF,
            kCandidateCount * kResidualSlotCount,
            &aValues,
            pErrorMessage)) {
        return false;
    }
    for (std::size_t aCandidateIndex = 0U;
         aCandidateIndex < kCandidateCount;
         ++aCandidateIndex) {
        const auto aBegin = aValues.begin() + static_cast<std::ptrdiff_t>(
            aCandidateIndex * kResidualSlotCount
        );
        const std::vector<std::uint64_t> aCandidateValues(
            aBegin,
            aBegin + static_cast<std::ptrdiff_t>(kResidualSlotCount)
        );
        Candidate aCandidate = CandidateFromValues(aCandidateValues);
        std::string aError;
        if (!Validate(aCandidate, &aError)) {
            SetError(pErrorMessage,
                     "ResidualKDFControl candidate " +
                     std::to_string(aCandidateIndex) +
                     " was invalid: " + aError);
            return false;
        }
        sCandidates.push_back(aCandidate);
    }
    SetError(pErrorMessage, "");
    return true;
}

bool ResidualKDFControl::ApplyCandidate(
    const std::size_t pCandidateIndex,
    ResidualBucket *pResidualBucket,
    std::string *pErrorMessage) {
    if ((pResidualBucket == nullptr) ||
        (pCandidateIndex >= sCandidates.size())) {
        SetError(pErrorMessage,
                 "ResidualKDFControl candidate was unavailable");
        return false;
    }
    return pResidualBucket->SetPlannedWithdrawals(
        CandidateWithdrawals(sCandidates[pCandidateIndex]),
        pErrorMessage
    );
}

bool ResidualKDFControl::FinishCandidate(
    ResidualBucket *pResidualBucket,
    std::string *pErrorMessage) {
    if (pResidualBucket == nullptr) {
        SetError(pErrorMessage,
                 "ResidualKDFControl received a null residual bucket");
        return false;
    }
    return pResidualBucket->FinishPlannedWithdrawals(pErrorMessage);
}

bool ResidualKDFControl::ValidateCandidate(
    const std::size_t pCandidateIndex,
    std::string *pErrorMessage) {
    if (pCandidateIndex >= sCandidates.size()) {
        SetError(pErrorMessage,
                 "ResidualKDFControl candidate index was out of range");
        return false;
    }
    return Validate(sCandidates[pCandidateIndex], pErrorMessage);
}

const ResidualKDFControl::Candidate *ResidualKDFControl::CandidateAt(
    const std::size_t pCandidateIndex) {
    return pCandidateIndex < sCandidates.size()
        ? &sCandidates[pCandidateIndex]
        : nullptr;
}

std::size_t ResidualKDFControl::GeneratedCount() {
    return sCandidates.size();
}
