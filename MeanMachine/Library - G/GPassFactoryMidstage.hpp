//
//  GPassFactoryMidstage.hpp
//  MeanMachine
//

#ifndef GPassFactoryMidstage_hpp
#define GPassFactoryMidstage_hpp

#include "GSeedRunStageConfig.hpp"
#include "Random.hpp"

#include <array>
#include <cstddef>
#include <utility>
#include <vector>

class GPassFactoryMidstage {
public:
    using Slot = TwistWorkSpaceSlot;
    using SlotArray1 = std::array<Slot, 1U>;
    using SlotArray2 = std::array<Slot, 2U>;
    using SlotArray3 = std::array<Slot, 3U>;
    using SlotArray4 = std::array<Slot, 4U>;
    using SlotArray5 = std::array<Slot, 5U>;
    using SlotArray6 = std::array<Slot, 6U>;
    using SlotArray7 = std::array<Slot, 7U>;
    using SlotArray8 = std::array<Slot, 8U>;
    using SlotArray9 = std::array<Slot, 9U>;
    using SlotArray10 = std::array<Slot, 10U>;
    using SlotArray11 = std::array<Slot, 11U>;
    using SlotArray12 = std::array<Slot, 12U>;
    using SlotArray13 = std::array<Slot, 13U>;
    using SlotArray14 = std::array<Slot, 14U>;
    using SlotArray15 = std::array<Slot, 15U>;
    using SlotArray16 = std::array<Slot, 16U>;
    using SlotArray17 = std::array<Slot, 17U>;
    using SlotArray18 = std::array<Slot, 18U>;
    using SlotArray19 = std::array<Slot, 19U>;
    using SlotArray21 = std::array<Slot, 21U>;
    using SlotArray22 = std::array<Slot, 22U>;
    using SlotArray23 = std::array<Slot, 23U>;
    using SlotArray24 = std::array<Slot, 24U>;

    template <std::size_t N>
    static std::vector<Slot> ToVector(const std::array<Slot, N> &pItems) {
        return std::vector<Slot>(pItems.begin(), pItems.end());
    }

    template <std::size_t N, std::size_t M>
    static std::array<Slot, N + M> Concat(const std::array<Slot, N> &pFirst,
                                          const std::array<Slot, M> &pSecond) {
        std::array<Slot, N + M> aResult = {};
        for (std::size_t aIndex = 0U; aIndex < N; ++aIndex) {
            aResult[aIndex] = pFirst[aIndex];
        }
        for (std::size_t aIndex = 0U; aIndex < M; ++aIndex) {
            aResult[N + aIndex] = pSecond[aIndex];
        }
        return aResult;
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassNoResidualSlices(const SlotArray4 &pPrimary,
                                                                        const SlotArray4 &pDestinations) {
        return {
            {{pPrimary[3], pPrimary[1]},
             {pPrimary[2], pPrimary[0]},
             pDestinations[0],
             false},

            GSeedRunStageSliceSpec({pDestinations[0], pPrimary[2]},
                                   true,
                                   {pPrimary[3], pPrimary[1]},
                                   false,
                                   pDestinations[1],
                                   true),

            {{pDestinations[1], pPrimary[3]},
             {pDestinations[0], pPrimary[2]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0]},
             {pDestinations[1], pPrimary[3]},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassOneResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray1 &pResiduals,
                                                                         const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassTwoResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray2 &pResiduals,
                                                                         const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassThreeResidualSlices(const SlotArray4 &pPrimary,
                                                                           const SlotArray3 &pResiduals,
                                                                           const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassFourResidualSlices(const SlotArray4 &pPrimary,
                                                                          const SlotArray4 &pResiduals,
                                                                          const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassFiveResidualSlices(const SlotArray4 &pPrimary,
                                                                          const SlotArray5 &pResiduals,
                                                                          const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassSixResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray6 &pResiduals,
                                                                         const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassSevenResidualSlices(const SlotArray4 &pPrimary,
                                                                           const SlotArray7 &pResiduals,
                                                                           const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassEightResidualSlices(const SlotArray4 &pPrimary,
                                                                           const SlotArray8 &pResiduals,
                                                                           const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassNineResidualSlices(const SlotArray4 &pPrimary,
                                                                          const SlotArray9 &pResiduals,
                                                                          const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassTenResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray10 &pResiduals,
                                                                         const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassElevenResidualSlices(const SlotArray4 &pPrimary,
                                                                            const SlotArray11 &pResiduals,
                                                                            const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassTwelveResidualSlices(const SlotArray4 &pPrimary,
                                                                            const SlotArray12 &pResiduals,
                                                                            const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassThirteenResidualSlices(const SlotArray4 &pPrimary,
                                                                              const SlotArray13 &pResiduals,
                                                                              const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassFourteenResidualSlices(const SlotArray4 &pPrimary,
                                                                              const SlotArray14 &pResiduals,
                                                                              const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassFifteenResidualSlices(const SlotArray4 &pPrimary,
                                                                             const SlotArray15 &pResiduals,
                                                                             const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassSixteenResidualSlices(const SlotArray4 &pPrimary,
                                                                             const SlotArray16 &pResiduals,
                                                                             const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassVariableResidualSlices(
        const SlotArray4 &pPrimary,
        const std::vector<Slot> &pResiduals,
        const SlotArray4 &pDestinations) {
        if (pResiduals.empty()) {
            return FourPassNoResidualSlices(pPrimary,
                                            pDestinations);
        }
        if (pResiduals.size() > 16U) {
            return {};
        }
        return AddShortestContextResiduals(
            FourPassResidualBaseSlices(pPrimary,
                                       pDestinations),
            pResiduals);
    }

private:
    template <std::size_t N>
    static std::vector<GSeedRunStageSliceSpec> FourPassResidualSlices(const SlotArray4 &pPrimary,
                                                                      const std::array<Slot, N> &pResiduals,
                                                                      const SlotArray4 &pDestinations) {
        static_assert((N >= 1U) && (N <= 16U));
        return AddShortestContextResiduals(
            FourPassResidualBaseSlices(pPrimary,
                                       pDestinations),
            pResiduals);
    }

    template <std::size_t N>
    static std::vector<GSeedRunStageSliceSpec> AddShortestContextResiduals(
        std::vector<GSeedRunStageSliceSpec> pSlices,
        const std::array<Slot, N> &pResiduals) {
        static_assert(N <= 24U);
        std::array<Slot, N> aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return AddShortestContextResidualsDynamic(
            std::move(pSlices),
            std::vector<Slot>(aResiduals.begin(), aResiduals.end()));
    }

    static std::vector<GSeedRunStageSliceSpec> AddShortestContextResiduals(
        std::vector<GSeedRunStageSliceSpec> pSlices,
        const std::vector<Slot> &pResiduals) {
        std::vector<Slot> aResiduals = pResiduals;
        Random::Shuffle(&aResiduals);
        return AddShortestContextResidualsDynamic(std::move(pSlices),
                                                  std::move(aResiduals));
    }

    static std::vector<GSeedRunStageSliceSpec> AddShortestContextResidualsDynamic(
        std::vector<GSeedRunStageSliceSpec> pSlices,
        std::vector<Slot> aResiduals) {

        // Water-fill the contexts. Each residual goes to the currently
        // shortest ingress/cross list. Ties are resolved mechanically from
        // the first pass to the last, ingress before cross within a pass.
        // No context may contain more than four sources.
        for (std::size_t aResidualIndex = 0U;
             aResidualIndex < aResiduals.size();
             ++aResidualIndex) {
            std::size_t aChosenPass = pSlices.size();
            std::size_t aChosenCount = 5U;
            bool aUseCross = false;

            for (std::size_t aPassIndex = 0U;
                 aPassIndex < pSlices.size();
                 ++aPassIndex) {
                const GSeedRunStageSliceSpec &aSlice =
                    pSlices[aPassIndex];
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

            if (aChosenPass >= pSlices.size()) {
                break;
            }

            GSeedRunStageSliceSpec &aChosenSlice =
                pSlices[aChosenPass];
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
        return pSlices;
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassResidualBaseSlices(
        const SlotArray4 &pPrimary,
        const SlotArray4 &pDestinations) {
        return {
            {{pPrimary[3], pPrimary[1]},
             {pPrimary[2], pPrimary[0]},
             pDestinations[0],
             false},

            GSeedRunStageSliceSpec({pDestinations[0], pPrimary[2]},
                                   true,
                                   {pPrimary[3], pPrimary[1]},
                                   true,
                                   pDestinations[1],
                                   true),

            GSeedRunStageSliceSpec({pDestinations[1], pPrimary[3]},
                                   true,
                                   {pDestinations[0], pPrimary[2]},
                                   true,
                                   pDestinations[2],
                                   false),

            {{pDestinations[2], pDestinations[0]},
             {pDestinations[1], pPrimary[3]},
             pDestinations[3],
             true},
        };
    }

    template <std::size_t N>
    static void ShuffleArray(std::array<Slot, N> *pItems) {
        if ((pItems == nullptr) || (N < 2U)) {
            return;
        }
        for (std::size_t i = 1U; i < N; ++i) {
            const std::size_t aSwapIndex = static_cast<std::size_t>(Random::Get(static_cast<int>(i + 1U)));
            std::swap((*pItems)[i], (*pItems)[aSwapIndex]);
        }
    }
};

#endif /* GPassFactoryMidstage_hpp */
