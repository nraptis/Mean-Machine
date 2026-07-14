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
    using SlotArray2 = std::array<Slot, 2U>;
    using SlotArray3 = std::array<Slot, 3U>;
    using SlotArray4 = std::array<Slot, 4U>;
    using SlotArray6 = std::array<Slot, 6U>;
    using SlotArray8 = std::array<Slot, 8U>;
    using SlotArray12 = std::array<Slot, 12U>;

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

    static std::vector<GSeedRunStageSliceSpec> FourPassTwoResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray2 &pResiduals,
                                                                         const SlotArray4 &pDestinations) {
        SlotArray2 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[3], pPrimary[2]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[2], aResiduals[1]},
             {pPrimary[0], pPrimary[3], pPrimary[1]},
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

    static std::vector<GSeedRunStageSliceSpec> FourPassFourResidualSlices(const SlotArray4 &pPrimary,
                                                                          const SlotArray4 &pResiduals,
                                                                          const SlotArray4 &pDestinations) {
        SlotArray4 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[3], pPrimary[2]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[2], aResiduals[1]},
             {pPrimary[0], pPrimary[3], pPrimary[1]},
             pDestinations[1],
             true},

            {{pDestinations[1], pPrimary[3], aResiduals[2]},
             {pDestinations[0], pPrimary[1], pPrimary[2]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0], aResiduals[3]},
             {pDestinations[1], pPrimary[2], pPrimary[3], pPrimary[0]},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassSixResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray6 &pResiduals,
                                                                         const SlotArray4 &pDestinations) {
        SlotArray6 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[2], pPrimary[3], aResiduals[1]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[2], aResiduals[2]},
             {pPrimary[0], pPrimary[3], aResiduals[3]},
             pDestinations[1],
             true},

            {{pDestinations[1], pPrimary[3], aResiduals[4]},
             {pDestinations[0], pPrimary[1], aResiduals[5]},
             pDestinations[2],
             false},

            {{pDestinations[2], pPrimary[2], pDestinations[0]},
             {pDestinations[1], pPrimary[3], pPrimary[0]},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassEightResidualSlices(const SlotArray4 &pPrimary,
                                                                           const SlotArray8 &pResiduals,
                                                                           const SlotArray4 &pDestinations) {
        SlotArray8 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[2], pPrimary[3], aResiduals[1]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[2], aResiduals[2]},
             {pPrimary[0], pPrimary[3], aResiduals[3]},
             pDestinations[1],
             true},

            {{pDestinations[1], pPrimary[3], aResiduals[4]},
             {pDestinations[0], pPrimary[1], aResiduals[5]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0], aResiduals[6]},
             {pDestinations[1], pPrimary[2], aResiduals[7]},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassTerminalEightResidualSlices(const SlotArray4 &pPrimary,
                                                                                   const SlotArray8 &pResiduals,
                                                                                   const SlotArray4 &pDestinations) {
        SlotArray8 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[2], pPrimary[3], aResiduals[1]},
             pDestinations[0],
             false},

            {{pPrimary[1], pPrimary[2], aResiduals[2]},
             {pPrimary[3], pPrimary[0], aResiduals[3]},
             pDestinations[1],
             true},

            {{pPrimary[2], pPrimary[3], aResiduals[4]},
             {pPrimary[0], pPrimary[1], aResiduals[5]},
             pDestinations[2],
             false},

            {{pPrimary[3], pPrimary[0], aResiduals[6]},
             {pPrimary[1], pPrimary[2], aResiduals[7]},
             pDestinations[3],
             true},
        };
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

    static std::vector<GSeedRunStageSliceSpec> SixPassTwoResidualSlices(const SlotArray4 &pPrimary,
                                                                        const SlotArray2 &pResiduals,
                                                                        const SlotArray6 &pDestinations) {
        SlotArray2 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            GSeedRunStageSliceSpec({pPrimary[0], pPrimary[1], aResiduals[0]},
                                   false,
                                   {pPrimary[2], pPrimary[3], aResiduals[1]},
                                   false,
                                   pDestinations[0],
                                   false),

            GSeedRunStageSliceSpec({pDestinations[0], pPrimary[2], pPrimary[3]},
                                   true,
                                   {pPrimary[0], pPrimary[1]},
                                   true,
                                   pDestinations[1],
                                   true),

            {{pDestinations[1], pPrimary[0]},
             {pDestinations[0], pPrimary[2]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0]},
             {pDestinations[1], pPrimary[3]},
             pDestinations[3],
             true},

            {{pDestinations[3], pDestinations[1]},
             {pDestinations[2], pPrimary[0]},
             pDestinations[4],
             false},

            {{pDestinations[4], pDestinations[2]},
             {pDestinations[3], pPrimary[1]},
             pDestinations[5],
            true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassFourResidualSlices(const SlotArray4 &pPrimary,
                                                                         const SlotArray4 &pResiduals,
                                                                         const SlotArray6 &pDestinations) {
        SlotArray4 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);
        
        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[2], pPrimary[3]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[2], aResiduals[1]},
             {pPrimary[0], pPrimary[3]},
             pDestinations[1],
             true},

            {{pDestinations[1], pPrimary[3], aResiduals[2]},
             {pDestinations[0], pPrimary[1], pPrimary[0]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0], aResiduals[3]},
             {pDestinations[1], pPrimary[3], pPrimary[2]},
             pDestinations[3],
             true},

            {{pDestinations[3], pDestinations[2], pPrimary[1]},
             {pPrimary[2], pDestinations[0], pDestinations[1]},
             pDestinations[4],
             false},

            {{pDestinations[4], pPrimary[0], pPrimary[1]},
             {pDestinations[3], pDestinations[2], pDestinations[1]},
             pDestinations[5],
            true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassSixResidualSlices(const SlotArray4 &pPrimary,
                                                                        const SlotArray6 &pResiduals,
                                                                        const SlotArray6 &pDestinations) {
        SlotArray6 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);
        
        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[2], pPrimary[3]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[2], aResiduals[1]},
             {pPrimary[0], pPrimary[3]},
             pDestinations[1],
             true},

            {{pDestinations[1], pPrimary[3], aResiduals[2]},
             {pDestinations[0], pPrimary[1], pPrimary[0]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0], aResiduals[3]},
             {pDestinations[1], pPrimary[3], pPrimary[2]},
             pDestinations[3],
             true},

            {{pDestinations[3], pDestinations[2], pPrimary[1], aResiduals[4]},
             {pPrimary[2], pDestinations[0], pDestinations[1]},
             pDestinations[4],
             false},

            {{pDestinations[4], pPrimary[0], pPrimary[1], aResiduals[5]},
             {pDestinations[3], pDestinations[2], pDestinations[1]},
             pDestinations[5],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassDiverseSlices(const SlotArray4 &pPrimary,
                                                                    const SlotArray8 &pResiduals,
                                                                    const SlotArray6 &pDestinations) {
        SlotArray8 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[2], pPrimary[3], aResiduals[1]},
             pDestinations[0],
             false},

            {{pPrimary[2], pPrimary[3], aResiduals[2]},
             {pPrimary[0], pPrimary[1], aResiduals[3]},
             pDestinations[1],
             true},

            {{pDestinations[0], pPrimary[0], aResiduals[4]},
             {pPrimary[1], pDestinations[1], aResiduals[5]},
             pDestinations[2],
             false},

            {{pDestinations[1], pPrimary[2], aResiduals[6]},
             {pPrimary[3], pDestinations[0], aResiduals[7]},
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

    static std::vector<GSeedRunStageSliceSpec> SixPassTerminalDiverseSlices(const SlotArray4 &pPrimary,
                                                                            const SlotArray8 &pResiduals,
                                                                            const SlotArray6 &pDestinations) {
        SlotArray8 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], aResiduals[0]},
             {pPrimary[1], aResiduals[1]},
             pDestinations[0],
             false},

            {{pPrimary[2], aResiduals[2]},
             {pPrimary[3], aResiduals[3]},
             pDestinations[1],
             true},

            {{pPrimary[1], aResiduals[4]},
             {pPrimary[0], pPrimary[2]},
             pDestinations[2],
             false},

            {{pPrimary[3], aResiduals[5]},
             {pPrimary[1], pPrimary[0]},
             pDestinations[3],
             true},

            {{pPrimary[0], aResiduals[6]},
             {pPrimary[2], pPrimary[3]},
             pDestinations[4],
             false},

            {{pPrimary[2], aResiduals[7]},
             {pPrimary[3], pPrimary[1]},
             pDestinations[5],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassTwelveResidualSlices(const SlotArray4 &pPrimary,
                                                                           const SlotArray12 &pResiduals,
                                                                           const SlotArray6 &pDestinations) {
        SlotArray12 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            {{pPrimary[0], pPrimary[1], aResiduals[0]},
             {pPrimary[2], pPrimary[3], aResiduals[1]},
             pDestinations[0],
             false},

            {{pDestinations[0], pPrimary[2], aResiduals[2]},
             {pPrimary[0], pPrimary[3], aResiduals[3]},
             pDestinations[1],
             true},

            {{pDestinations[1], pPrimary[0], aResiduals[4]},
             {pDestinations[0], pPrimary[2], aResiduals[5]},
             pDestinations[2],
             false},

            {{pDestinations[2], pPrimary[3], aResiduals[6]},
             {pDestinations[1], pPrimary[0], aResiduals[7]},
             pDestinations[3],
             true},

            {{pDestinations[3], pDestinations[1], aResiduals[8]},
             {pDestinations[2], pDestinations[0], aResiduals[9]},
             pDestinations[4],
             false},

            {{pDestinations[4], pDestinations[2], aResiduals[10]},
             {pDestinations[3], pPrimary[1], aResiduals[11]},
             pDestinations[5],
            true},
        };
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
