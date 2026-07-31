//
//  GPassFactoryStarter.hpp
//  MeanMachine
//

#ifndef GPassFactoryStarter_hpp
#define GPassFactoryStarter_hpp

#include "GSeedRunStageConfig.hpp"
#include "Random.hpp"

#include <array>
#include <cstddef>
#include <vector>

class GPassFactoryStarter {
public:
    using Slot = TwistWorkSpaceSlot;
    using SlotArray1 = std::array<Slot, 1U>;
    using SlotArray2 = std::array<Slot, 2U>;
    using SlotArray3 = std::array<Slot, 3U>;
    using SlotArray4 = std::array<Slot, 4U>;

    static constexpr std::size_t kKDF_A_AStarterCandidateCount = 36U;
    static constexpr std::size_t kSeed_AStarterCandidateCount = 36U;
    static constexpr std::size_t kTwist_AStarterCandidateCount = 36U;

    static std::vector<GSeedRunStageSliceSpec> KDF_A_AStarterSlices(
        const SlotArray2 &pSources,
        const SlotArray2 &pWarmUpLanes,
        const SlotArray4 &pDestinations,
        const std::size_t pCandidateIndex) {
        const std::size_t aCandidateIndex =
            pCandidateIndex % kKDF_A_AStarterCandidateCount;

        //
        // Source is pSources[0].
        // Nonce is pSources[1].
        //
        // Passes 1 and 2 are fixed. The remaining decisions subdivide the
        // 36 candidates in order:
        //
        //   pass 3: two halves of 18
        //   pass 4: two quarters of 9 within each half
        //   pass 5: three groups of 3 within each quarter
        //   pass 6: three candidates within each group
        //
        const std::size_t aPassThreeConfig =
            aCandidateIndex / 18U;
        const std::size_t aPassFourConfig =
            (aCandidateIndex / 9U) % 2U;
        const std::size_t aPassFiveConfig =
            (aCandidateIndex / 3U) % 3U;
        const std::size_t aPassSixConfig =
            aCandidateIndex % 3U;

        const Slot aPassThreeIngressLane =
            (aPassThreeConfig == 0U) ? pSources[0] : pSources[1];
        const Slot aPassThreeCrossLane =
            (aPassThreeConfig == 0U) ? pSources[1] : pSources[0];

        const Slot aPassFourIngressLane =
            (aPassFourConfig == 0U) ? pSources[0] : pSources[1];
        const Slot aPassFourCrossLane =
            (aPassFourConfig == 0U) ? pSources[1] : pSources[0];

        const Slot aPassFiveIngressLane =
            (aPassFiveConfig == 1U) ? pSources[1] : pSources[0];
        const Slot aPassFiveCrossLane =
            (aPassFiveConfig == 0U) ? pSources[1] :
            (aPassFiveConfig == 1U) ? pSources[0] :
                                      pWarmUpLanes[0];

        const Slot aPassSixIngressLane =
            (aPassSixConfig == 1U) ? pSources[1] : pSources[0];
        const Slot aPassSixCrossLane =
            (aPassSixConfig == 0U) ? pSources[1] :
            (aPassSixConfig == 1U) ? pSources[0] :
                                     pWarmUpLanes[1];

        return {
            //
            // Pass 1
            //
            // Ingress: source, nonce
            // Cross:   nonce, source
            // Write:   destination A
            //
            GSeedRunStageSliceSpec({pSources[0], pSources[1]},
                                   true,
                                   {pSources[1], pSources[0]},
                                   true,
                                   pWarmUpLanes[0],
                                   false),

            //
            // Pass 2
            //
            // Ingress: destination A, source
            // Cross:   source, nonce
            // Write:   destination B
            //
            GSeedRunStageSliceSpec({pWarmUpLanes[0], pSources[0]},
                                   true,
                                   {pSources[0], pSources[1]},
                                   true,
                                   pWarmUpLanes[1],
                                   true),

            //
            // Pass 3
            //
            // Ingress: destination B, DC
            // Cross:   destination A, DC
            // Write:   destination C
            //
            {{pWarmUpLanes[1], aPassThreeIngressLane},
             {pWarmUpLanes[0], aPassThreeCrossLane},
             pDestinations[0],
             false},

            //
            // Pass 4
            //
            // Ingress: destination C, destination A, DC
            // Cross:   destination B, DC
            // Write:   destination D
            //
            {{pDestinations[0],
              pWarmUpLanes[0],
              aPassFourIngressLane},
             {pWarmUpLanes[1], aPassFourCrossLane},
             pDestinations[1],
             true},

            //
            // Pass 5
            //
            // Ingress: destination D, destination B, DC
            // Cross:   destination C, DC
            // Write:   destination E
            //
            {{pDestinations[1],
              pWarmUpLanes[1],
              aPassFiveIngressLane},
             {pDestinations[0], aPassFiveCrossLane},
             pDestinations[2],
             false},

            //
            // Pass 6
            //
            // Ingress: destination E, destination C, DC
            // Cross:   destination D, DC
            // Write:   destination F
            //
            {{pDestinations[2],
              pDestinations[0],
              aPassSixIngressLane},
             {pDestinations[1], aPassSixCrossLane},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> Seed_AStarterSlices(
        const SlotArray2 &pSources,
        const SlotArray2 &pWarmUpLanes,
        const SlotArray4 &pDestinations,
        const std::size_t pCandidateIndex) {
        const std::size_t aCandidateIndex =
            pCandidateIndex % kSeed_AStarterCandidateCount;

        //
        // Source is pSources[0].
        // Nonce is pSources[1].
        //
        //
        // Split the candidate space in the same hierarchical order as KDF-A:
        // halves, quarters, thirds, then individual candidates.
        //
        const std::size_t aPassThreeConfig =
            aCandidateIndex / 18U;
        const std::size_t aPassFourConfig =
            (aCandidateIndex / 9U) % 2U;
        const std::size_t aPassFiveConfig =
            (aCandidateIndex / 3U) % 3U;
        const std::size_t aPassSixConfig =
            aCandidateIndex % 3U;

        //
        // Pass 3:
        //   0: nonce, source
        //   1: source, nonce
        //
        const Slot aPassThreeIngressLane =
            (aPassThreeConfig == 0U) ? pSources[1] : pSources[0];
        const Slot aPassThreeCrossLane =
            (aPassThreeConfig == 0U) ? pSources[0] : pSources[1];

        //
        // Pass 4:
        //   0: nonce, source
        //   1: source, nonce
        //
        const Slot aPassFourIngressLane =
            (aPassFourConfig == 0U) ? pSources[1] : pSources[0];
        const Slot aPassFourCrossLane =
            (aPassFourConfig == 0U) ? pSources[0] : pSources[1];

        //
        // Pass 5:
        //   0: source, destination A
        //   1: source, nonce
        //   2: nonce, source
        //
        const Slot aPassFiveIngressLane =
            (aPassFiveConfig == 2U) ? pSources[1] : pSources[0];
        const Slot aPassFiveCrossLane =
            (aPassFiveConfig == 0U) ? pWarmUpLanes[0] :
            (aPassFiveConfig == 1U) ? pSources[1] :
                                      pSources[0];

        //
        // Pass 6:
        //   0: source, destination B
        //   1: source, nonce
        //   2: nonce, source
        //
        const Slot aPassSixIngressLane =
            (aPassSixConfig == 2U) ? pSources[1] : pSources[0];
        const Slot aPassSixCrossLane =
            (aPassSixConfig == 0U) ? pWarmUpLanes[1] :
            (aPassSixConfig == 1U) ? pSources[1] :
                                     pSources[0];

        return {
            //
            // Pass 1
            //
            // Ingress: source, nonce
            // Cross:   nonce, source
            // Write:   destination A
            //
            GSeedRunStageSliceSpec({pSources[0], pSources[1]},
                                   true,
                                   {pSources[1], pSources[0]},
                                   true,
                                   pWarmUpLanes[0],
                                   false),

            //
            // Pass 2
            //
            // Ingress: destination A, source
            // Cross:   source, nonce
            // Write:   destination B
            //
            GSeedRunStageSliceSpec({pWarmUpLanes[0], pSources[0]},
                                   true,
                                   {pSources[0], pSources[1]},
                                   true,
                                   pWarmUpLanes[1],
                                   true),

            //
            // Pass 3
            //
            {{pWarmUpLanes[1], aPassThreeIngressLane},
             {pWarmUpLanes[0], aPassThreeCrossLane},
             pDestinations[0],
             false},

            //
            // Pass 4
            //
            {{pDestinations[0],
              pWarmUpLanes[0],
              aPassFourIngressLane},
             {pWarmUpLanes[1], aPassFourCrossLane},
             pDestinations[1],
             true},

            //
            // Pass 5
            //
            {{pDestinations[1],
              pWarmUpLanes[1],
              aPassFiveIngressLane},
             {pDestinations[0], aPassFiveCrossLane},
             pDestinations[2],
             false},

            //
            // Pass 6
            //
            {{pDestinations[2],
              pDestinations[0],
              aPassSixIngressLane},
             {pDestinations[1], aPassSixCrossLane},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> Twist_AStarterSlices(
        const SlotArray3 &pSources,
        const SlotArray4 &pResiduals,
        const SlotArray2 &pWarmUpLanes,
        const SlotArray4 &pDestinations,
        const std::size_t pCandidateIndex) {
        const std::size_t aCandidateIndex =
            pCandidateIndex % kTwist_AStarterCandidateCount;

        //
        // Source is pSources[0].
        // Key A is pSources[1].
        // Key B is pSources[2].
        //
        // The 36 candidates are mechanically divided into:
        //
        //   pass 3 key orientation:  2 groups of 18
        //   pass 4 key placement:    3 groups of 6 in each half
        //   pass 5 key placement:    3 groups of 2
        //   pass 5 active key:       2 individual candidates
        //
        const std::size_t aPassThreeOrientation =
            aCandidateIndex / 18U;
        const std::size_t aPassFourPlacement =
            (aCandidateIndex / 6U) % 3U;
        const std::size_t aPassFivePlacement =
            (aCandidateIndex / 2U) % 3U;
        const std::size_t aPassFiveKey =
            aCandidateIndex % 2U;

        const Slot aPassThreeIngressKey =
            (aPassThreeOrientation == 0U) ?
            pSources[1] : pSources[2];
        const Slot aPassThreeCrossKey =
            (aPassThreeOrientation == 0U) ?
            pSources[2] : pSources[1];

        std::vector<Slot> aPassFourIngress = {
            pDestinations[0],
            pWarmUpLanes[0],
        };
        std::vector<Slot> aPassFourCross = {
            pWarmUpLanes[1],
            pSources[0],
        };
        if (aPassFourPlacement == 0U) {
            aPassFourIngress.push_back(aPassThreeIngressKey);
            aPassFourIngress.push_back(aPassThreeCrossKey);
        } else if (aPassFourPlacement == 1U) {
            aPassFourIngress.push_back(aPassThreeIngressKey);
            aPassFourCross.push_back(aPassThreeCrossKey);
        } else {
            aPassFourCross.push_back(aPassThreeIngressKey);
            aPassFourCross.push_back(aPassThreeCrossKey);
        }

        const Slot aPassFiveActiveKey =
            (aPassFiveKey == 0U) ? pSources[1] : pSources[2];
        const Slot aPassSixOppositeKey =
            (aPassFiveKey == 0U) ? pSources[2] : pSources[1];

        std::vector<Slot> aPassFiveIngress = {
            pDestinations[1],
            pWarmUpLanes[1],
        };
        std::vector<Slot> aPassFiveCross = {
            pDestinations[0],
            pWarmUpLanes[0],
        };
        if (aPassFivePlacement == 0U) {
            aPassFiveIngress.push_back(pSources[0]);
            aPassFiveIngress.push_back(aPassFiveActiveKey);
        } else if (aPassFivePlacement == 1U) {
            aPassFiveIngress.push_back(aPassFiveActiveKey);
            aPassFiveIngress.push_back(pSources[0]);
        } else {
            aPassFiveIngress.push_back(pSources[0]);
            aPassFiveCross.push_back(aPassFiveActiveKey);
        }

        std::vector<GSeedRunStageSliceSpec> aSlices;
        aSlices.reserve(6U);

        //
        // Pass 1
        //
        // Ingress: source, key A
        // Cross:   source, key B
        // Write:   destination A
        //
        aSlices.emplace_back(
            std::initializer_list<Slot>{pSources[0], pSources[1]},
            true,
            std::initializer_list<Slot>{pSources[0], pSources[2]},
            true,
            pWarmUpLanes[0],
            false);

        //
        // Pass 2
        //
        // Ingress: destination A, key B
        // Cross:   source, key A
        // Write:   destination B
        //
        aSlices.emplace_back(
            std::initializer_list<Slot>{pWarmUpLanes[0], pSources[2]},
            true,
            std::initializer_list<Slot>{pSources[0], pSources[1]},
            true,
            pWarmUpLanes[1],
            true);

        //
        // Pass 3
        //
        // Source is on ingress. The two keys exchange sides by candidate half.
        //
        aSlices.emplace_back(
            std::initializer_list<Slot>{
                pWarmUpLanes[1],
                pSources[0],
                aPassThreeIngressKey,
            },
            true,
            std::initializer_list<Slot>{
                pWarmUpLanes[0],
                aPassThreeCrossKey,
            },
            true,
            pDestinations[0],
            false);

        //
        // Pass 4
        //
        // Source moves to cross. The ordered key pair is placed wholly on
        // ingress, split between the two sides, or wholly on cross.
        //
        GSeedRunStageSliceSpec aPassFour(
            {},
            true,
            {},
            true,
            pDestinations[1],
            true);
        aPassFour.mIngressSources = aPassFourIngress;
        aPassFour.mCrossSources = aPassFourCross;
        aSlices.push_back(aPassFour);

        //
        // Pass 5
        //
        // Source returns to ingress. Destination A occupies cross[1], its
        // required fourth-read position. The selected key is placed after
        // source, before source, or on cross.
        //
        GSeedRunStageSliceSpec aPassFive(
            {},
            true,
            {},
            true,
            pDestinations[2],
            false);
        aPassFive.mIngressSources = aPassFiveIngress;
        aPassFive.mCrossSources = aPassFiveCross;
        aSlices.push_back(aPassFive);

        //
        // Pass 6
        //
        // Source returns to cross. Destination B occupies cross[1], its
        // required fourth-read position. Ingress uses the key opposite the
        // active key selected for pass 5.
        //
        aSlices.emplace_back(
            std::initializer_list<Slot>{
                pDestinations[2],
                pDestinations[0],
                aPassSixOppositeKey,
            },
            true,
            std::initializer_list<Slot>{
                pDestinations[1],
                pWarmUpLanes[1],
                pSources[0],
            },
            true,
            pDestinations[3],
            true);

        //
        // Water-fill the four fixed Twist residuals into the currently
        // shortest contexts. Ties are resolved from pass one through pass
        // six, ingress before cross. A context is never allowed above four.
        //
        for (Slot aResidual : pResiduals) {
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
                aChosenSlice.mCrossSources.push_back(aResidual);
                aChosenSlice.mIsLastCrossDirectionLocked = false;
            } else {
                aChosenSlice.mIngressSources.push_back(aResidual);
                aChosenSlice.mIsLastIngressDirectionLocked = false;
            }
        }

        return aSlices;
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassThreeInputStarterSlices(
        const SlotArray3 &pPrimary,
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
                                   {pWarmUpLanes[0], pPrimary[1]},
                                   false,
                                   pDestinations[0],
                                   false),

            {{pDestinations[0], pWarmUpLanes[0]},
             {pWarmUpLanes[1], pPrimary[2]},
             pDestinations[1],
             true},

            {{pDestinations[1], pWarmUpLanes[1]},
             {pDestinations[0], pWarmUpLanes[0]},
             pDestinations[2],
             false},

            {{pDestinations[2], pDestinations[0]},
             {pDestinations[1], pWarmUpLanes[1]},
             pDestinations[3],
             true},
        };
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassOneInputStarterSlices(
        const SlotArray1 &pInput,
        const SlotArray2 &pWarmUpLanes,
        const SlotArray4 &pDestinations,
        const std::size_t pCandidateIndex) {
        // The candidate index is intentionally available at the factory
        // boundary. Candidate-specific starter selection will be introduced
        // here without reaching back into a builder or global.
        static_cast<void>(pCandidateIndex);

        return {
            //
            // Pass 1: bootstrap both ARX sides from the sole external source.
            //
            GSeedRunStageSliceSpec({pInput[0], pInput[0]},
                                   true,
                                   {pInput[0], pInput[0]},
                                   true,
                                   pWarmUpLanes[0],
                                   false),

            //
            // Pass 2: consume the first warm-up at ingress[0].
            //
            GSeedRunStageSliceSpec({pWarmUpLanes[0], pInput[0]},
                                   false,
                                   {pInput[0], pInput[0]},
                                   false,
                                   pWarmUpLanes[1],
                                   true),

            //
            // Pass 3: consume the second warm-up at ingress[0] and the first
            // warm-up at cross[0].
            //
            GSeedRunStageSliceSpec({pWarmUpLanes[1], pInput[0]},
                                   false,
                                   {pWarmUpLanes[0], pInput[0]},
                                   false,
                                   pDestinations[0],
                                   false),

            //
            // Passes 4-6 continue the exact ingress[0], cross[0],
            // ingress[1], required cross[1] destination schedule.
            //
            GSeedRunStageSliceSpec({pDestinations[0], pWarmUpLanes[0]},
                                   false,
                                   {pWarmUpLanes[1], pInput[0]},
                                   false,
                                   pDestinations[1],
                                   true),

            GSeedRunStageSliceSpec({pDestinations[1], pWarmUpLanes[1]},
                                   false,
                                   {pDestinations[0], pWarmUpLanes[0]},
                                   false,
                                   pDestinations[2],
                                   false),

            GSeedRunStageSliceSpec({pDestinations[2], pDestinations[0]},
                                   false,
                                   {pDestinations[1], pWarmUpLanes[1]},
                                   true,
                                   pDestinations[3],
                                   true),
        };
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassStarterFourResidualSlices(
        const SlotArray3 &pPrimary,
        const SlotArray4 &pResiduals,
        const SlotArray2 &pWarmUpLanes,
        const SlotArray4 &pDestinations) {
        std::vector<GSeedRunStageSliceSpec> aSlices =
            SixPassThreeInputStarterSlices(pPrimary,
                                           pWarmUpLanes,
                                           pDestinations);
        SlotArray4 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        // FFB: once residuals make four sources available, Source may no
        // longer appear on both ingress and cross as it does in the bare
        // three-input starter.
        aSlices[0].mCrossSources.erase(
            aSlices[0].mCrossSources.begin()
        );
        aSlices[0].mCrossSources.push_back(aResiduals[0]);
        aSlices[0].mIsLastCrossDirectionLocked = false;

        // BBF
        aSlices[1].mCrossSources.push_back(aResiduals[1]);
        aSlices[1].mIsLastCrossDirectionLocked = false;

        // FBF
        aSlices[2].mCrossSources.push_back(aResiduals[2]);
        aSlices[2].mIsLastCrossDirectionLocked = false;

        // BFB
        aSlices[3].mIngressSources.push_back(pPrimary[1]);
        aSlices[3].mIsLastIngressDirectionLocked = true;
        aSlices[3].mCrossSources.push_back(pPrimary[0]);
        aSlices[3].mCrossSources.push_back(aResiduals[3]);
        aSlices[3].mIsLastCrossDirectionLocked = false;

        // Primary B now receives its fourth required use in the BFB pass.
        // Reuse the first warm-up result in pass five instead of reading
        // Primary B a fifth time.
        aSlices[4].mCrossSources.back() = pWarmUpLanes[0];
        return aSlices;
    }

    static std::vector<GSeedRunStageSliceSpec> SixPassOneInputFourResidualSlices(
        const SlotArray1 &pInput,
        const SlotArray4 &pResiduals,
        const SlotArray2 &pWarmUpLanes,
        const SlotArray4 &pDestinations) {
        return {
            //
            // Pass 1
            //
            // Ingress: input, residual A
            // Cross:   input, residual B
            // Write:   warm-up A
            //
            GSeedRunStageSliceSpec({pInput[0], pResiduals[0]},
                                   false,
                                   {pInput[0], pResiduals[1]},
                                   false,
                                   pWarmUpLanes[0],
                                   false),

            //
            // Pass 2
            //
            // Ingress: warm-up A, residual C
            // Cross:   input, residual D
            // Write:   warm-up B
            //
            GSeedRunStageSliceSpec({pWarmUpLanes[0], pResiduals[2]},
                                   false,
                                   {pInput[0], pResiduals[3]},
                                   false,
                                   pWarmUpLanes[1],
                                   true),

            //
            // Pass 3
            //
            // Ingress: warm-up B, input
            // Cross:   warm-up A, input
            // Write:   destination A
            //
            GSeedRunStageSliceSpec({pWarmUpLanes[1], pInput[0]},
                                   false,
                                   {pWarmUpLanes[0], pInput[0]},
                                   false,
                                   pDestinations[0],
                                   false),

            //
            // Pass 4
            //
            // Ingress: destination A, warm-up A
            // Cross:   warm-up B, input
            // Write:   destination B
            //
            GSeedRunStageSliceSpec({pDestinations[0], pWarmUpLanes[0]},
                                   false,
                                   {pWarmUpLanes[1], pInput[0]},
                                   true,
                                   pDestinations[1],
                                   true),

            //
            // Pass 5
            //
            // Ingress: destination B, warm-up B
            // Cross:   destination A, warm-up A
            // Write:   destination C
            //
            GSeedRunStageSliceSpec({pDestinations[1], pWarmUpLanes[1]},
                                   false,
                                   {pDestinations[0], pWarmUpLanes[0]},
                                   false,
                                   pDestinations[2],
                                   false),

            //
            // Pass 6
            //
            // Ingress: destination C, destination A
            // Cross:   destination B, warm-up B
            // Write:   destination D
            //
            GSeedRunStageSliceSpec({pDestinations[2], pDestinations[0]},
                                   true,
                                   {pDestinations[1], pWarmUpLanes[1]},
                                   false,
                                   pDestinations[3],
                                   true),
        };
    }

    static std::vector<GSeedRunStageSliceSpec> FourPassStarterFourResidualSlices(
        const SlotArray3 &pPrimary,
        const SlotArray4 &pResiduals,
        const SlotArray4 &pDestinations) {
        SlotArray4 aResiduals = pResiduals;
        ShuffleArray(&aResiduals);

        return {
            GSeedRunStageSliceSpec({pPrimary[0], pPrimary[1]},
                                   true,
                                   {pPrimary[2], aResiduals[0]},
                                   false,
                                   pDestinations[0],
                                   false),

            GSeedRunStageSliceSpec({pDestinations[0], pPrimary[0], pPrimary[2]},
                                   true,
                                   {pPrimary[1], aResiduals[1]},
                                   false,
                                   pDestinations[1],
                                   true),

            GSeedRunStageSliceSpec({pDestinations[1], pPrimary[1], aResiduals[2]},
                                   false,
                                   {pDestinations[0], pPrimary[0], pPrimary[2]},
                                   true,
                                   pDestinations[2],
                                   false),

            GSeedRunStageSliceSpec({pDestinations[2], pDestinations[0],
                                    pPrimary[2], aResiduals[3]},
                                   false,
                                   {pDestinations[1], pPrimary[0], pPrimary[1]},
                                   true,
                                   pDestinations[3],
                                   true),
        };
    }

private:
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

#endif /* GPassFactoryStarter_hpp */
