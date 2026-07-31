#include "ResidualBucket.hpp"

#include "Random.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>

namespace {

constexpr std::size_t kMaximumUsageCount = 4U;
constexpr const char *kReportRule =
    "--------------------------------------------";

struct ResidualLaneFamily {
    TwistWorkSpaceSlot                      mFirst;
    const char                              *mName;
};

constexpr std::array<ResidualLaneFamily, 21> kResidualLaneFamilies = {{
    {TwistWorkSpaceSlot::kEarthLaneA, "earth"},
    {TwistWorkSpaceSlot::kFireLaneA, "fire"},
    {TwistWorkSpaceSlot::kWindLaneA, "wind"},
    {TwistWorkSpaceSlot::kWaterLaneA, "water"},
    {TwistWorkSpaceSlot::kHeartLaneA, "heart"},
    {TwistWorkSpaceSlot::kSoilLaneA, "soil"},
    {TwistWorkSpaceSlot::kLightningLaneA, "lightning"},
    {TwistWorkSpaceSlot::kIceLaneA, "ice"},
    {TwistWorkSpaceSlot::kWoodLaneA, "wood"},
    {TwistWorkSpaceSlot::kMagmaLaneA, "magma"},
    {TwistWorkSpaceSlot::kPlasmaLaneA, "plasma"},
    {TwistWorkSpaceSlot::kShadowLaneA, "shadow"},
    {TwistWorkSpaceSlot::kCrystalLaneA, "crystal"},
    {TwistWorkSpaceSlot::kAetherLaneA, "aether"},
    {TwistWorkSpaceSlot::kCelestialLaneA, "celestial"},
    {TwistWorkSpaceSlot::kKineticLaneA, "kinetic"},
    {TwistWorkSpaceSlot::kVaporLaneA, "vapor"},
    {TwistWorkSpaceSlot::kSpiritLaneA, "spirit"},
    {TwistWorkSpaceSlot::kFuseLaneA, "fuse"},
}};

std::string ResidualName(const TwistWorkSpaceSlot pResidual) {
    const int aResidualValue = static_cast<int>(pResidual);
    for (const ResidualLaneFamily &aFamily : kResidualLaneFamilies) {
        const int aOffset =
            aResidualValue - static_cast<int>(aFamily.mFirst);
        if ((aOffset >= 0) && (aOffset < 4)) {
            std::string aName = aFamily.mName;
            aName += "_";
            aName.push_back(static_cast<char>('a' + aOffset));
            return aName;
        }
    }

    switch (pResidual) {
        case TwistWorkSpaceSlot::kSourceLane:
            return "source";
        case TwistWorkSpaceSlot::kNonceLane:
            return "nonce";
        case TwistWorkSpaceSlot::kKeyRowReadA:
            return "key_a";
        case TwistWorkSpaceSlot::kKeyRowReadB:
            return "key_b";
        default:
            return "slot_" + std::to_string(aResidualValue);
    }
}

void PrintResidualList(const char *pLabel,
                       const std::vector<TwistWorkSpaceSlot> &pResiduals) {
    std::vector<TwistWorkSpaceSlot> aSortedResiduals = pResiduals;
    std::sort(
        aSortedResiduals.begin(),
        aSortedResiduals.end(),
        [](const TwistWorkSpaceSlot pLHS,
           const TwistWorkSpaceSlot pRHS) {
            return ResidualName(pLHS) < ResidualName(pRHS);
        }
    );

    char aPrefixBuffer[64];
    const int aLabelWidth =
        (std::string(pLabel) == "Chosen") ? 7 : 6;
    std::snprintf(aPrefixBuffer,
                  sizeof(aPrefixBuffer),
                  "%-*s(%2zu): ",
                  aLabelWidth,
                  pLabel,
                  aSortedResiduals.size());
    const std::string aPrefix = aPrefixBuffer;

    printf("%s{", aPrefix.c_str());
    if (aSortedResiduals.empty()) {
        printf(" }\n");
        return;
    }

    printf(" ");
    for (std::size_t i = 0U; i < aSortedResiduals.size(); ++i) {
        if ((i > 0U) && ((i % 4U) == 0U)) {
            printf("\n%*s",
                   static_cast<int>(aPrefix.size() + 2U),
                   "");
        }

        const std::string aName = ResidualName(aSortedResiduals[i]);
        printf("%s%s",
               aName.c_str(),
               ((i + 1U) < aSortedResiduals.size()) ? "," : "");
        if (((i + 1U) < aSortedResiduals.size()) &&
            (((i + 1U) % 4U) != 0U)) {
            printf(" ");
        }
    }
    printf(" }\n");
}

} // namespace

void ResidualBucket::AddResiduals(
    const std::string &pStageName,
    std::vector<TwistWorkSpaceSlot> pResiduals) {
    AddResiduals(pStageName,
                 pResiduals,
                 0U);
}

void ResidualBucket::AddResiduals(
    const std::string &pStageName,
    std::vector<TwistWorkSpaceSlot> pResiduals,
    const std::uint8_t pInitialUsageCount) {
    AddResidualsInternal(pStageName,
                         std::move(pResiduals),
                         pInitialUsageCount,
                         true);
}

void ResidualBucket::AddResiduals(
    std::vector<TwistWorkSpaceSlot> pResiduals,
    const std::uint8_t pInitialUsageCount) {
    AddResidualsInternal("",
                         std::move(pResiduals),
                         pInitialUsageCount,
                         false);
}

void ResidualBucket::AddResidualsInternal(
    const std::string &pStageName,
    std::vector<TwistWorkSpaceSlot> pResiduals,
    const std::uint8_t pInitialUsageCount,
    const bool pPrintAddedResiduals) {
    if (pInitialUsageCount > kMaximumUsageCount) {
        printf("ResidualBucket::AddResiduals received usage count %u for %s\n",
               static_cast<unsigned int>(pInitialUsageCount),
               pStageName.c_str());
        exit(0);
    }

    std::vector<TwistWorkSpaceSlot> aAddedResiduals;
    for (const TwistWorkSpaceSlot aResidual : pResiduals) {
        if (aResidual == TwistWorkSpaceSlot::kInvalid) {
            continue;
        }

        const auto aMatch = std::find_if(
            mEntries.begin(),
            mEntries.end(),
            [aResidual](const Entry &pEntry) {
                return pEntry.mResidual == aResidual;
            }
        );
        if (aMatch == mEntries.end()) {
            mEntries.push_back(
                {aResidual, pInitialUsageCount}
            );
            aAddedResiduals.push_back(aResidual);
        }
    }
    if (pPrintAddedResiduals) {
        PrintResidualList("Added", aAddedResiduals);
        printf("\n");
    }
}

void ResidualBucket::Remove(
    const std::vector<TwistWorkSpaceSlot> &pResiduals) {
    mEntries.erase(
        std::remove_if(
            mEntries.begin(),
            mEntries.end(),
            [&pResiduals](const Entry &pEntry) {
                return std::find(pResiduals.begin(),
                                 pResiduals.end(),
                                 pEntry.mResidual) != pResiduals.end();
            }
        ),
        mEntries.end()
    );
}

std::size_t ResidualBucket::CountValidResiduals() const {
    return static_cast<std::size_t>(
        std::count_if(
            mEntries.begin(),
            mEntries.end(),
            [](const Entry &pEntry) {
                return pEntry.mUsageCount < kMaximumUsageCount;
            }
        )
    );
}

void ResidualBucket::Print(
    const std::string &pStageName) const {
    std::array<std::vector<TwistWorkSpaceSlot>,
               kMaximumUsageCount + 1U> aReportTiers;
    for (const Entry &aEntry : mEntries) {
        const std::size_t aTierIndex =
            std::min(static_cast<std::size_t>(aEntry.mUsageCount),
                     kMaximumUsageCount);
        aReportTiers[aTierIndex].push_back(aEntry.mResidual);
    }

    printf("%s\n", kReportRule);
    printf("-------- %s --------\n", pStageName.c_str());
    PrintResidualList("Stale", aReportTiers[4]);
    PrintResidualList("Three", aReportTiers[3]);
    PrintResidualList("Two", aReportTiers[2]);
    PrintResidualList("One", aReportTiers[1]);
    PrintResidualList("Zero", aReportTiers[0]);
    printf("%s\n\n", kReportRule);
}

std::vector<TwistWorkSpaceSlot> ResidualBucket::Withdraw(
    const std::string &pStageName,
    const int pCount) {
    std::vector<TwistWorkSpaceSlot> aResult;

    const std::size_t aEligibleCount = static_cast<std::size_t>(
        std::count_if(
            mEntries.begin(),
            mEntries.end(),
            [](const Entry &pEntry) {
                return pEntry.mUsageCount < kMaximumUsageCount;
            }
        )
    );

    std::array<std::vector<TwistWorkSpaceSlot>,
               kMaximumUsageCount + 1U> aReportTiers;
    for (const Entry &aEntry : mEntries) {
        const std::size_t aTierIndex =
            std::min(static_cast<std::size_t>(aEntry.mUsageCount),
                     kMaximumUsageCount);
        aReportTiers[aTierIndex].push_back(aEntry.mResidual);
    }

    printf("%s\n", kReportRule);
    printf("-------- %s --------\n", pStageName.c_str());
    PrintResidualList("Stale", aReportTiers[4]);
    PrintResidualList("Three", aReportTiers[3]);
    PrintResidualList("Two", aReportTiers[2]);
    PrintResidualList("One", aReportTiers[1]);
    PrintResidualList("Zero", aReportTiers[0]);
    printf("--------\n");

    if ((pCount < 0) ||
        (static_cast<std::size_t>(pCount) > aEligibleCount)) {
        printf("Fetched (%zu)\n", aEligibleCount);
        printf("OVER-WITHDRAW: requested %d residuals, but only %zu were available\n",
               pCount,
               aEligibleCount);
        printf("%s\n\n", kReportRule);
        exit(0);
    }

    const std::size_t aWithdrawCount =
        static_cast<std::size_t>(pCount);
    aResult.reserve(aWithdrawCount);

    // Snapshot each tier before increasing any counts. This prevents an entry
    // promoted from one tier from being selected again in this withdrawal.
    std::array<std::vector<std::size_t>, kMaximumUsageCount> aUsageTiers;
    for (std::size_t i = 0U; i < mEntries.size(); ++i) {
        const std::size_t aUsageCount =
            static_cast<std::size_t>(mEntries[i].mUsageCount);
        if (aUsageCount < kMaximumUsageCount) {
            aUsageTiers[aUsageCount].push_back(i);
        }
    }

    for (std::size_t aUsageCount = 0U;
         aUsageCount < aUsageTiers.size();
         ++aUsageCount) {
        std::vector<std::size_t> &aTier = aUsageTiers[aUsageCount];
        Random::Shuffle(&aTier);
    }

    for (const std::vector<std::size_t> &aTier : aUsageTiers) {
        for (const std::size_t aEntryIndex : aTier) {
            if (aResult.size() == aWithdrawCount) {
                break;
            }

            Entry &aEntry = mEntries[aEntryIndex];
            ++aEntry.mUsageCount;
            aResult.push_back(aEntry.mResidual);
        }
        if (aResult.size() == aWithdrawCount) {
            break;
        }
    }

    printf("Fetched (%zu)\n", aResult.size());
    PrintResidualList("Chosen", aResult);
    printf("%s\n", kReportRule);

    return aResult;
}
