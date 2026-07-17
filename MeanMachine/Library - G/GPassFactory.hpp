//
//  GPassFactory.hpp
//  MeanMachine
//

#ifndef GPassFactory_hpp
#define GPassFactory_hpp

#include "GSeedRunStageConfig.hpp"
#include "Random.hpp"

#include <array>
#include <cstddef>
#include <vector>

class GPassFactory {
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
    using SlotArray14 = std::array<Slot, 14U>;
    using SlotArray16 = std::array<Slot, 16U>;
    using SlotArray18 = std::array<Slot, 18U>;

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

    static std::vector<GSeedRunStageSliceSpec> KDF_A_AStarterSlices(const SlotArray2 &pSources,
                                                                    const SlotArray2 &pWarmUpLanes,
                                                                    const SlotArray4 &pDestinations) {
        return {
            // 2-source graph: ingress [source, snow], cross [snow, source].
            GSeedRunStageSliceSpec({pSources[0], pSources[1]},
                                   true,
                                   {pSources[1], pSources[0]},
                                   true,
                                   pWarmUpLanes[0],
                                   false),

            // 3-source graph: previous write is the shared source.
            GSeedRunStageSliceSpec({pWarmUpLanes[0], pSources[0]},
                                   true,
                                   {pWarmUpLanes[0], pSources[1]},
                                   true,
                                   pWarmUpLanes[1],
                                   true),

            // 4-source graph and onward: no duplicate lane reads in a slice.
            {{pWarmUpLanes[1], pSources[0]},
             {pSources[1], pWarmUpLanes[0]},
             pDestinations[0],
             false},

            {{pDestinations[0], pWarmUpLanes[1]},
             {pWarmUpLanes[0], pSources[0]},
             pDestinations[1],
             true},

            {{pDestinations[1], pWarmUpLanes[1]},
             {pDestinations[0], pSources[1]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0]},
             {pDestinations[1], pWarmUpLanes[0]},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> Seed_AStarterSlices(const SlotArray3 &pPrimary,
                                                                   const SlotArray2 &pWarmUpLanes,
                                                                   const SlotArray4 &pDestinations) {
        return {
            GSeedRunStageSliceSpec({pPrimary[0], pPrimary[1]},
                                   true,
                                   {pPrimary[0], pPrimary[2]},
                                   true,
                                   pWarmUpLanes[0],
                                   false),

            GSeedRunStageSliceSpec({pWarmUpLanes[0], pPrimary[2]},
                                   true,
                                   {pPrimary[0], pPrimary[1]},
                                   true,
                                   pWarmUpLanes[1],
                                   true),

            GSeedRunStageSliceSpec({pWarmUpLanes[1], pPrimary[0], pPrimary[2]},
                                   true,
                                   {pPrimary[1], pWarmUpLanes[0]},
                                   false,
                                   pDestinations[0],
                                   false),

            {{pDestinations[0], pWarmUpLanes[0]},
             {pWarmUpLanes[1], pPrimary[2]},
             pDestinations[1],
             true},

            {{pDestinations[1], pWarmUpLanes[1]},
             {pDestinations[0], pPrimary[1]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0]},
             {pDestinations[1], pWarmUpLanes[1]},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassNoResidualSlices(const SlotArray4 &pPrimary,
                                                                        const SlotArray4 &pDestinations) {
        return {
            {{pPrimary[0], pPrimary[1]},
             {pPrimary[2], pPrimary[3]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[1], pPrimary[2]},
             {pPrimary[0], pPrimary[3]},
             pDestinations[1],
             true},

            {{pDestinations[1], pPrimary[3], pPrimary[0]},
             {pDestinations[0], pPrimary[1], pPrimary[2]},
             pDestinations[2],
             false},

            {{pDestinations[2], pPrimary[2], pDestinations[0]},
             {pDestinations[1], pPrimary[3], pPrimary[0]},
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

    static std::vector<GSeedRunStageSliceSpec> FourPassFourteenResidualSlices(const SlotArray4 &pPrimary,
                                                                              const SlotArray14 &pResiduals,
                                                                              const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassSixteenResidualSlices(const SlotArray4 &pPrimary,
                                                                             const SlotArray16 &pResiduals,
                                                                             const SlotArray4 &pDestinations) {
        return FourPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassIndependentEightResidualSlices(const SlotArray4 &pPrimary,
                                                                                       const SlotArray8 &pResiduals,
                                                                                       const SlotArray4 &pDestinations) {
        return AddRoundRobinResiduals<4U>(FourPassIndependentBaseSlices(pPrimary,
                                                                        pDestinations),
                                          pResiduals);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassNoResidualSlices(const SlotArray4 &pPrimary,
                                                                       const SlotArray6 &pDestinations) {
        return {
            GSeedRunStageSliceSpec({pPrimary[0], pPrimary[1]},
                                   false,
                                   {pPrimary[2], pPrimary[3]},
                                   false,
                                   pDestinations[0],
                                   false),

            GSeedRunStageSliceSpec({pDestinations[0], pPrimary[2], pPrimary[3]},
                                   false,
                                   {pDestinations[0], pPrimary[0], pPrimary[1]},
                                   false,
                                   pDestinations[1],
                                   true),

            {{pDestinations[1], pPrimary[0], pPrimary[1]},
             {pDestinations[0], pPrimary[2], pPrimary[3]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0], pPrimary[2]},
             {pDestinations[1], pPrimary[3], pPrimary[0]},
             pDestinations[3],
             true},

            {{pDestinations[3], pDestinations[1], pPrimary[3]},
             {pDestinations[2], pDestinations[0], pPrimary[1]},
             pDestinations[4],
             false},

            {{pDestinations[4], pDestinations[2], pPrimary[0]},
             {pDestinations[3], pDestinations[1], pPrimary[2]},
             pDestinations[5],
            true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassOneResidualSlices(const SlotArray4 &pPrimary,
                                                                        const SlotArray1 &pResiduals,
                                                                        const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassTwoResidualSlices(const SlotArray4 &pPrimary,
                                                                        const SlotArray2 &pResiduals,
                                                                        const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassThreeResidualSlices(const SlotArray4 &pPrimary,
                                                                          const SlotArray3 &pResiduals,
                                                                          const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassFourResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray4 &pResiduals,
                                                                         const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassFiveResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray5 &pResiduals,
                                                                         const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassSixResidualSlices(const SlotArray4 &pPrimary,
                                                                        const SlotArray6 &pResiduals,
                                                                        const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassSevenResidualSlices(const SlotArray4 &pPrimary,
                                                                          const SlotArray7 &pResiduals,
                                                                          const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassEightResidualSlices(const SlotArray4 &pPrimary,
                                                                          const SlotArray8 &pResiduals,
                                                                          const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassNineResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray9 &pResiduals,
                                                                         const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassTenResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray10 &pResiduals,
                                                                         const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassDiverseSlices(const SlotArray4 &pPrimary,
                                                                    const SlotArray8 &pResiduals,
                                                                    const SlotArray6 &pDestinations) {
        return AddRoundRobinResiduals<6U>(SixPassDiverseBaseSlices(pPrimary,
                                                                   pDestinations),
                                          pResiduals);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassElevenResidualSlices(const SlotArray4 &pPrimary,
                                                                           const SlotArray11 &pResiduals,
                                                                           const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassTwelveResidualSlices(const SlotArray4 &pPrimary,
                                                                           const SlotArray12 &pResiduals,
                                                                           const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassFourteenResidualSlices(const SlotArray4 &pPrimary,
                                                                             const SlotArray14 &pResiduals,
                                                                             const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassSixteenResidualSlices(const SlotArray4 &pPrimary,
                                                                            const SlotArray16 &pResiduals,
                                                                            const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassEighteenResidualSlices(const SlotArray4 &pPrimary,
                                                                             const SlotArray18 &pResiduals,
                                                                             const SlotArray6 &pDestinations) {
        return SixPassResidualSlices(pPrimary, pResiduals, pDestinations);
    }

    static std::vector<GSeedRunStageSliceSpec> EightPassEightResidualSlices(const SlotArray4 &pPrimary,
                                                                            const SlotArray8 &pResiduals,
                                                                            const SlotArray8 &pDestinations) {
        SlotArray8 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[3], pPrimary[2]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[2], aResiduals[1]},
             {pPrimary[0], pPrimary[3]},
             pDestinations[1],
             true},

            {{pDestinations[1], pPrimary[3], aResiduals[2]},
             {pDestinations[0], pPrimary[1], pPrimary[2]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0], aResiduals[3]},
             {pDestinations[1], pPrimary[0], pPrimary[1]},
             pDestinations[3],
             true},

            {{pDestinations[3], pDestinations[1], aResiduals[4]},
             {pDestinations[2], pPrimary[2], pPrimary[3]},
             pDestinations[4],
             false},

            {{pDestinations[4], pDestinations[2], aResiduals[5]},
             {pDestinations[3], pPrimary[0]},
             pDestinations[5],
             true},

            {{pDestinations[5], pDestinations[3], aResiduals[6]},
             {pDestinations[4], pDestinations[2]},
             pDestinations[6],
             false},

            {{pDestinations[6], pDestinations[4], aResiduals[7]},
             {pDestinations[5], pDestinations[3]},
             pDestinations[7],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> EightPassTwelveResidualSlices(const SlotArray4 &pPrimary,
                                                                             const SlotArray12 &pResiduals,
                                                                             const SlotArray8 &pDestinations) {
        SlotArray12 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[2], pPrimary[3], aResiduals[8]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[2], aResiduals[1]},
             {pPrimary[0], pPrimary[3], aResiduals[9]},
             pDestinations[1],
             true},

            {{pDestinations[1], pPrimary[3], aResiduals[2]},
             {pDestinations[0], pPrimary[1], pPrimary[2], aResiduals[10]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0], aResiduals[3]},
             {pDestinations[1], pPrimary[0], pPrimary[1], aResiduals[11]},
             pDestinations[3],
             true},

            {{pDestinations[3], pDestinations[1], aResiduals[4]},
             {pDestinations[2], pPrimary[2], pPrimary[3]},
             pDestinations[4],
             false},

            {{pDestinations[4], pDestinations[2], aResiduals[5]},
             {pDestinations[3], pPrimary[0]},
             pDestinations[5],
             true},

            {{pDestinations[5], pDestinations[3], aResiduals[6]},
             {pDestinations[4], pDestinations[2]},
             pDestinations[6],
             false},

            {{pDestinations[6], pDestinations[4], aResiduals[7]},
             {pDestinations[5], pDestinations[3]},
             pDestinations[7],
             true},
        };
    }

private:
    template <std::size_t N>
    static std::vector<GSeedRunStageSliceSpec> FourPassResidualSlices(const SlotArray4 &pPrimary,
                                                                      const std::array<Slot, N> &pResiduals,
                                                                      const SlotArray4 &pDestinations) {
        static_assert(((N >= 1U) && (N <= 12U)) || (N == 14U) || (N == 16U));
        return AddRoundRobinResiduals<4U>(FourPassResidualBaseSlices(pPrimary,
                                                                     pDestinations),
                                          pResiduals);
    }

    template <std::size_t N>
    static std::vector<GSeedRunStageSliceSpec> SixPassResidualSlices(const SlotArray4 &pPrimary,
                                                                     const std::array<Slot, N> &pResiduals,
                                                                     const SlotArray6 &pDestinations) {
        static_assert(((N >= 1U) && (N <= 12U)) ||
                      (N == 14U) || (N == 16U) || (N == 18U));
        return AddRoundRobinResiduals<6U>(SixPassResidualBaseSlices(pPrimary,
                                                                    pDestinations),
                                          pResiduals);
    }

    template <std::size_t PassCount, std::size_t N>
    static std::vector<GSeedRunStageSliceSpec> AddRoundRobinResiduals(
        std::vector<GSeedRunStageSliceSpec> pSlices,
        const std::array<Slot, N> &pResiduals) {
        static_assert(N <= 18U);
        std::array<Slot, N> aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        // Fill each pass once before starting the next ingress/cross column.
        // Four-pass groups therefore form ae/bf/cg/dh at eight residuals,
        // and aei/bfj/cgk/dhl at twelve residuals.
        for (std::size_t aResidualIndex = 0U;
             aResidualIndex < N;
             ++aResidualIndex) {
            const std::size_t aPassIndex = aResidualIndex % PassCount;
            const std::size_t aColumnIndex = aResidualIndex / PassCount;
            const bool aUseCross = (aColumnIndex & 1U) != 0U;
            GSeedRunStageSliceSpec &aSlice = pSlices[aPassIndex];
            if (aUseCross) {
                aSlice.mCrossSources.push_back(aResiduals[aResidualIndex]);
                aSlice.mIsLastCrossDirectionLocked = false;
            } else {
                aSlice.mIngressSources.push_back(aResiduals[aResidualIndex]);
                aSlice.mIsLastIngressDirectionLocked = false;
            }
        }
        return pSlices;
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassResidualBaseSlices(
        const SlotArray4 &pPrimary,
        const SlotArray4 &pDestinations) {
        return {
            {{pPrimary[0], pPrimary[1]},
             {pPrimary[2], pPrimary[3]},
             pDestinations[0],
             false},

            GSeedRunStageSliceSpec({pDestinations[0], pPrimary[2]},
                                   true,
                                   {pPrimary[0], pPrimary[3]},
                                   true,
                                   pDestinations[1],
                                   true),

            GSeedRunStageSliceSpec({pDestinations[1], pPrimary[3]},
                                   true,
                                   {pDestinations[0], pPrimary[1]},
                                   true,
                                   pDestinations[2],
                                   false),

            {{pDestinations[2], pDestinations[0]},
             {pDestinations[1], pPrimary[2]},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassIndependentBaseSlices(
        const SlotArray4 &pPrimary,
        const SlotArray4 &pDestinations) {
        return {
            {{pPrimary[0], pPrimary[1]},
             {pPrimary[2], pPrimary[3]},
             pDestinations[0],
             false},

            {{pPrimary[1], pPrimary[2]},
             {pPrimary[3], pPrimary[0]},
             pDestinations[1],
             true},

            {{pPrimary[2], pPrimary[3]},
             {pPrimary[0], pPrimary[1]},
             pDestinations[2],
             false},

            {{pPrimary[3], pPrimary[0]},
             {pPrimary[1], pPrimary[2]},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassResidualBaseSlices(
        const SlotArray4 &pPrimary,
        const SlotArray6 &pDestinations) {
        return {
            {{pPrimary[0], pPrimary[1]},
             {pPrimary[2], pPrimary[3]},
             pDestinations[0],
             false},

            GSeedRunStageSliceSpec({pDestinations[0], pPrimary[2]},
                                   true,
                                   {pPrimary[0], pPrimary[3]},
                                   true,
                                   pDestinations[1],
                                   true),

            {{pDestinations[1], pPrimary[0]},
             {pDestinations[0], pPrimary[2]},
             pDestinations[2],
             false},

            GSeedRunStageSliceSpec({pDestinations[2], pPrimary[3]},
                                   true,
                                   {pDestinations[1], pPrimary[0]},
                                   false,
                                   pDestinations[3],
                                   true),

            {{pDestinations[3], pDestinations[1]},
             {pDestinations[2], pDestinations[0]},
             pDestinations[4],
             false},

            GSeedRunStageSliceSpec({pDestinations[4], pDestinations[2]},
                                   false,
                                   {pDestinations[3], pPrimary[1]},
                                   true,
                                   pDestinations[5],
                                   true),
        };
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassDiverseBaseSlices(
        const SlotArray4 &pPrimary,
        const SlotArray6 &pDestinations) {
        return {
            {{pPrimary[0], pPrimary[1]},
             {pPrimary[2], pPrimary[3]},
             pDestinations[0],
             false},

            {{pPrimary[2], pPrimary[3]},
             {pPrimary[0], pPrimary[1]},
             pDestinations[1],
             true},

            {{pDestinations[0], pPrimary[0]},
             {pPrimary[1], pDestinations[1]},
             pDestinations[2],
             false},

            {{pDestinations[1], pPrimary[2]},
             {pPrimary[3], pDestinations[0]},
             pDestinations[3],
             true},

            {{pDestinations[2], pDestinations[0], pPrimary[1]},
             {pPrimary[2], pDestinations[1], pDestinations[3]},
             pDestinations[4],
             false},

            {{pDestinations[3], pDestinations[2], pPrimary[3]},
             {pPrimary[0], pDestinations[4], pDestinations[1]},
             pDestinations[5],
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

#endif /* GPassFactory_hpp */
