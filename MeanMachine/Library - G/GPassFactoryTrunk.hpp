//
//  GPassFactoryTrunk.hpp
//  MeanMachine
//

#ifndef GPassFactoryTrunk_hpp
#define GPassFactoryTrunk_hpp

#include "GSeedRunStageConfig.hpp"
#include "Random.hpp"

#include <array>
#include <cstddef>
#include <vector>

class GPassFactoryTrunk {
public:
    using Slot = TwistWorkSpaceSlot;
    using SlotArray4 = std::array<Slot, 4U>;
    using SlotArray6 = std::array<Slot, 6U>;

    template <std::size_t N>
    static std::vector<GSeedRunStageSliceSpec> FourPassTrunkSlices(
        const SlotArray4 &pPrimary,
        const std::array<Slot, N> &pResiduals,
        const SlotArray4 &pDestinations) {
        static_assert((N >= 1U) && (N <= 18U));
        return TrunkSlices<4U>(pPrimary,
                              pResiduals,
                              pDestinations);
    }

    template <std::size_t N>
    static std::vector<GSeedRunStageSliceSpec> SixPassTrunkSlices(
        const SlotArray4 &pPrimary,
        const std::array<Slot, N> &pResiduals,
        const SlotArray6 &pDestinations) {
        static_assert((N >= 1U) && (N <= 24U));
        return TrunkSlices<6U>(pPrimary,
                              pResiduals,
                              pDestinations);
    }

private:
    template <std::size_t PassCount,
              std::size_t N,
              std::size_t DestinationCount>
    static std::vector<GSeedRunStageSliceSpec> TrunkSlices(
        const SlotArray4 &pPrimary,
        const std::array<Slot, N> &pResiduals,
        const std::array<Slot, DestinationCount> &pDestinations) {
        static_assert((PassCount == 4U) || (PassCount == 6U));
        static_assert(PassCount == DestinationCount);
        static_assert(N >= 1U);

        std::array<Slot, N> aResiduals = pResiduals;
        ShuffleArray(&aResiduals);
        constexpr bool aReplaceOptionalDestinationA =
            (PassCount == 4U) && (N == 18U);

        std::vector<GSeedRunStageSliceSpec> aSlices = {
            GSeedRunStageSliceSpec({pPrimary[0], pPrimary[1]},
                                   true,
                                   {pPrimary[2], pPrimary[3]},
                                   true,
                                   pDestinations[0],
                                   false),

            GSeedRunStageSliceSpec({pDestinations[0], pPrimary[2]},
                                   true,
                                   {pPrimary[0], pPrimary[1]},
                                   true,
                                   pDestinations[1],
                                   true),

            GSeedRunStageSliceSpec({pDestinations[1], pPrimary[3]},
                                   true,
                                   {pDestinations[0], pPrimary[1]},
                                   false,
                                   pDestinations[2],
                                   false),

            GSeedRunStageSliceSpec({pDestinations[2]},
                                   false,
                                   {pDestinations[1], aResiduals[0]},
                                   false,
                                   pDestinations[3],
                                   true),
        };

        if constexpr (aReplaceOptionalDestinationA) {
            aSlices[3].mIngressSources.push_back(aResiduals[1]);
        } else {
            aSlices[3].mIngressSources.push_back(pDestinations[0]);
        }

        if constexpr (PassCount == 6U) {
            aSlices.push_back(
                GSeedRunStageSliceSpec({pDestinations[3], pDestinations[1]},
                                       false,
                                       {pDestinations[2], pDestinations[0]},
                                       false,
                                       pDestinations[4],
                                       false));
            aSlices.push_back(
                GSeedRunStageSliceSpec({pDestinations[4], pDestinations[2]},
                                       false,
                                       {pDestinations[3], pDestinations[1]},
                                       false,
                                       pDestinations[5],
                                       true));
        }

        // Residual zero is the mandatory pass-four wildcard. Residual one is
        // also reserved by the saturated four-pass flavor. Water-fill every
        // remaining residual into the currently shortest context, resolving
        // ties from the first pass to the last and ingress before cross.
        constexpr std::size_t aFirstDistributedResidual =
            aReplaceOptionalDestinationA ? 2U : 1U;
        for (std::size_t aResidualIndex = aFirstDistributedResidual;
             aResidualIndex < N;
             ++aResidualIndex) {
            std::size_t aChosenPass = aSlices.size();
            std::size_t aChosenCount = 5U;
            bool aUseCross = false;

            for (std::size_t aPassIndex = 0U;
                 aPassIndex < aSlices.size();
                 ++aPassIndex) {
                const GSeedRunStageSliceSpec &aSlice =
                    aSlices[aPassIndex];
                const std::size_t aIngressCount =
                    aSlice.mIngressSources.size();
                if ((aIngressCount < 4U) &&
                    (aIngressCount < aChosenCount)) {
                    aChosenPass = aPassIndex;
                    aChosenCount = aIngressCount;
                    aUseCross = false;
                }

                const std::size_t aCrossCount =
                    aSlice.mCrossSources.size();
                if ((aCrossCount < 4U) &&
                    (aCrossCount < aChosenCount)) {
                    aChosenPass = aPassIndex;
                    aChosenCount = aCrossCount;
                    aUseCross = true;
                }
            }

            if (aChosenPass >= aSlices.size()) {
                break;
            }

            GSeedRunStageSliceSpec &aChosenSlice =
                aSlices[aChosenPass];
            if (aUseCross) {
                aChosenSlice.mCrossSources.push_back(
                    aResiduals[aResidualIndex]);
                aChosenSlice.mIsLastCrossDirectionLocked = false;
            } else {
                aChosenSlice.mIngressSources.push_back(
                    aResiduals[aResidualIndex]);
                aChosenSlice.mIsLastIngressDirectionLocked = false;
            }
        }

        return aSlices;
    }

    template <std::size_t N>
    static void ShuffleArray(std::array<Slot, N> *pItems) {
        if ((pItems == nullptr) || (N < 2U)) {
            return;
        }
        for (std::size_t i = 1U; i < N; ++i) {
            const std::size_t aSwapIndex =
                static_cast<std::size_t>(
                    Random::Get(static_cast<int>(i + 1U)));
            std::swap((*pItems)[i], (*pItems)[aSwapIndex]);
        }
    }
};

#endif /* GPassFactoryTrunk_hpp */
