//
//  GPrintTool.hpp
//  MeanMachine
//

#ifndef GPrintTool_hpp
#define GPrintTool_hpp

#include "GSeedRunStageConfig.hpp"
#include "GSymbol.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class GPrintTool {
public:
    static void AddStage(GSeedRunStageConfig &pConfig) {
        Step aStep;
        aStep.mKind = "stage";
        aStep.mName = pConfig.mStageName;
        if (!pConfig.mBatchName.empty()) {
            aStep.mName += " ";
            aStep.mName += pConfig.mBatchName;
        }

        for (std::size_t aIndex = 0U; aIndex < pConfig.mSlices.size(); ++aIndex) {
            const GSeedRunStageSliceSpec &aSlice = pConfig.mSlices[aIndex];

            Slice aPrintedSlice;
            aPrintedSlice.mName = "slice_" + std::to_string(aIndex);
            aPrintedSlice.mDest = aSlice.mDest;
            aPrintedSlice.mIngress = aSlice.IngressSources();
            aPrintedSlice.mCross = aSlice.CrossSources();

            for (TwistWorkSpaceSlot aSlot : aPrintedSlice.mIngress) {
                AddLaneUse(&aStep, aSlot, true);
            }
            for (TwistWorkSpaceSlot aSlot : aPrintedSlice.mCross) {
                AddLaneUse(&aStep, aSlot, true);
            }
            AddLaneUse(&aStep, aSlice.mDest, false);

            aStep.mSlices.push_back(aPrintedSlice);
        }

        Steps().push_back(aStep);
    }

    static void AddDiffusion(const char *pSource,
                             const char *pDest) {
        Step aStep;
        aStep.mKind = "diffusion";
        aStep.mName = "matrix_diffusion";

        aStep.mReadText = (pSource != nullptr) ? pSource : "";
        aStep.mWriteText = (pDest != nullptr) ? pDest : "";

        std::vector<TwistWorkSpaceSlot> aSourceSlots = ParseSlots(aStep.mReadText);
        std::vector<TwistWorkSpaceSlot> aDestSlots = ParseSlots(aStep.mWriteText);

        for (TwistWorkSpaceSlot aSlot : aSourceSlots) {
            AddLaneUse(&aStep, aSlot, true);
        }
        for (TwistWorkSpaceSlot aSlot : aDestSlots) {
            AddLaneUse(&aStep, aSlot, false);
        }

        Steps().push_back(aStep);
    }

    static void Print() {
        const std::vector<Step> &aSteps = Steps();

        std::printf("\n========================================================\n");
        std::printf("GPrintTool lane flow\n");
        std::printf("========================================================\n");

        if (aSteps.empty()) {
            std::printf("(no steps recorded)\n");
        }

        for (std::size_t aStepIndex = 0U; aStepIndex < aSteps.size(); ++aStepIndex) {
            const Step &aStep = aSteps[aStepIndex];
            std::printf("[%zu] %s: %s\n",
                        aStepIndex,
                        aStep.mKind.c_str(),
                        aStep.mName.c_str());

            if (aStep.mKind == "stage") {
                std::printf("    read lanes : %s\n", JoinSlots(UniqueReadSlots(aStep)).c_str());
                std::printf("    write lanes: %s\n", JoinSlots(UniqueWriteSlots(aStep)).c_str());

                for (const Slice &aSlice : aStep.mSlices) {
                    std::printf("      %s ingress[%s] cross[%s] -> %s\n",
                                aSlice.mName.c_str(),
                                JoinSlots(aSlice.mIngress).c_str(),
                                JoinSlots(aSlice.mCross).c_str(),
                                BufName(aSlice.mDest).c_str());
                }
            } else {
                std::printf("    read from: %s\n", aStep.mReadText.c_str());
                std::printf("    write to : %s\n", aStep.mWriteText.c_str());
            }
        }

        std::printf("\n========================================================\n");
        std::printf("GPrintTool lane use counts per added step\n");
        std::printf("========================================================\n");

        for (std::size_t aStepIndex = 0U; aStepIndex < aSteps.size(); ++aStepIndex) {
            const Step &aStep = aSteps[aStepIndex];
            std::printf("[%zu] %s: %s\n",
                        aStepIndex,
                        aStep.mKind.c_str(),
                        aStep.mName.c_str());
            PrintCounts("reads ", aStep.mReadCounts);
            PrintCounts("writes", aStep.mWriteCounts);
        }

        std::map<std::string, int> aTotalReads;
        std::map<std::string, int> aTotalWrites;
        for (const Step &aStep : aSteps) {
            MergeCounts(&aTotalReads, aStep.mReadCounts);
            MergeCounts(&aTotalWrites, aStep.mWriteCounts);
        }

        std::printf("\n========================================================\n");
        std::printf("GPrintTool total lane use counts\n");
        std::printf("========================================================\n");
        PrintCounts("reads ", aTotalReads);
        PrintCounts("writes", aTotalWrites);
        std::printf("========================================================\n\n");
    }

    static void Reset() {
        Steps().clear();
    }

private:
    struct Slice {
        std::string                             mName;
        std::vector<TwistWorkSpaceSlot>         mIngress;
        std::vector<TwistWorkSpaceSlot>         mCross;
        TwistWorkSpaceSlot                      mDest = TwistWorkSpaceSlot::kInvalid;
    };

    struct Step {
        std::string                             mKind;
        std::string                             mName;
        std::string                             mReadText;
        std::string                             mWriteText;
        std::vector<Slice>                      mSlices;
        std::map<std::string, int>              mReadCounts;
        std::map<std::string, int>              mWriteCounts;
    };

    static std::vector<Step> &Steps() {
        static std::vector<Step> aSteps;
        return aSteps;
    }

    static void AddLaneUse(Step *pStep,
                           const TwistWorkSpaceSlot pSlot,
                           const bool pIsRead) {
        if ((pStep == nullptr) || (pSlot == TwistWorkSpaceSlot::kInvalid)) {
            return;
        }
        std::map<std::string, int> &aCounts = pIsRead ? pStep->mReadCounts : pStep->mWriteCounts;
        aCounts[BufName(pSlot)] += 1;
    }

    static std::string Normalize(const std::string &pText) {
        std::string aResult;
        aResult.reserve(pText.size());
        for (char aChar : pText) {
            if (std::isalnum(static_cast<unsigned char>(aChar))) {
                aResult.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(aChar))));
            }
        }
        return aResult;
    }

    static void AppendUnique(std::vector<TwistWorkSpaceSlot> *pSlots,
                             const TwistWorkSpaceSlot pSlot) {
        if ((pSlots == nullptr) || (pSlot == TwistWorkSpaceSlot::kInvalid)) {
            return;
        }
        if (std::find(pSlots->begin(), pSlots->end(), pSlot) == pSlots->end()) {
            pSlots->push_back(pSlot);
        }
    }

    static std::vector<TwistWorkSpaceSlot> AllKnownSlots() {
        using Slot = TwistWorkSpaceSlot;
        return {
            Slot::kSource, Slot::kParamSource, Slot::kParamDestination, Slot::kParamSnow,
            Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD,
            Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD,
            Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD,
            Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kSnowLaneC, Slot::kSnowLaneD,
            Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD,
            Slot::kWaterLaneA, Slot::kWaterLaneB, Slot::kWaterLaneC, Slot::kWaterLaneD,
            Slot::kEarthLaneA, Slot::kEarthLaneB, Slot::kEarthLaneC, Slot::kEarthLaneD,
            Slot::kWindLaneA, Slot::kWindLaneB, Slot::kWindLaneC, Slot::kWindLaneD,
            Slot::kFuseLaneA, Slot::kFuseLaneB, Slot::kFuseLaneC, Slot::kFuseLaneD,
            Slot::kScrapLaneA, Slot::kScrapLaneB, Slot::kScrapLaneC, Slot::kScrapLaneD,
            Slot::kMergeLaneA, Slot::kMergeLaneB, Slot::kMergeLaneC, Slot::kMergeLaneD,
            Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD,
            Slot::kInvestE, Slot::kInvestF, Slot::kInvestG, Slot::kInvestH,
            Slot::kKeyRowReadA, Slot::kKeyRowReadB, Slot::kKeyRowWriteA, Slot::kKeyRowWriteB,
            Slot::kKeyBoxUnrolledA, Slot::kKeyBoxUnrolledB,
            Slot::kIndexList256A, Slot::kIndexList256B, Slot::kIndexList256C, Slot::kIndexList256D,
        };
    }

    static std::vector<TwistWorkSpaceSlot> GroupSlots(const std::string &pToken) {
        using Slot = TwistWorkSpaceSlot;
        const std::string aToken = Normalize(pToken);
        if ((aToken == "expand") || (aToken == "expansion") || (aToken == "seed")) {
            return {Slot::kExpansionLaneA, Slot::kExpansionLaneB, Slot::kExpansionLaneC, Slot::kExpansionLaneD};
        }
        if (aToken == "work") {
            return {Slot::kWorkLaneA, Slot::kWorkLaneB, Slot::kWorkLaneC, Slot::kWorkLaneD};
        }
        if ((aToken == "op") || (aToken == "operation")) {
            return {Slot::kOperationLaneA, Slot::kOperationLaneB, Slot::kOperationLaneC, Slot::kOperationLaneD};
        }
        if (aToken == "snow") {
            return {Slot::kSnowLaneA, Slot::kSnowLaneB, Slot::kSnowLaneC, Slot::kSnowLaneD};
        }
        if (aToken == "fire") {
            return {Slot::kFireLaneA, Slot::kFireLaneB, Slot::kFireLaneC, Slot::kFireLaneD};
        }
        if (aToken == "water") {
            return {Slot::kWaterLaneA, Slot::kWaterLaneB, Slot::kWaterLaneC, Slot::kWaterLaneD};
        }
        if (aToken == "earth") {
            return {Slot::kEarthLaneA, Slot::kEarthLaneB, Slot::kEarthLaneC, Slot::kEarthLaneD};
        }
        if (aToken == "wind") {
            return {Slot::kWindLaneA, Slot::kWindLaneB, Slot::kWindLaneC, Slot::kWindLaneD};
        }
        if (aToken == "fuse") {
            return {Slot::kFuseLaneA, Slot::kFuseLaneB, Slot::kFuseLaneC, Slot::kFuseLaneD};
        }
        if (aToken == "scrap") {
            return {Slot::kScrapLaneA, Slot::kScrapLaneB, Slot::kScrapLaneC, Slot::kScrapLaneD};
        }
        if (aToken == "merge") {
            return {Slot::kMergeLaneA, Slot::kMergeLaneB, Slot::kMergeLaneC, Slot::kMergeLaneD};
        }
        if (aToken == "invest") {
            return {Slot::kInvestA, Slot::kInvestB, Slot::kInvestC, Slot::kInvestD,
                    Slot::kInvestE, Slot::kInvestF, Slot::kInvestG, Slot::kInvestH};
        }
        return {};
    }

    static std::vector<TwistWorkSpaceSlot> ParseSlots(const std::string &pText) {
        std::vector<TwistWorkSpaceSlot> aResult;
        std::string aToken;

        auto FlushToken = [&]() {
            if (aToken.empty()) {
                return;
            }

            for (TwistWorkSpaceSlot aSlot : GroupSlots(aToken)) {
                AppendUnique(&aResult, aSlot);
            }

            const std::string aNormalized = Normalize(aToken);
            for (TwistWorkSpaceSlot aSlot : AllKnownSlots()) {
                if ((aNormalized == Normalize(BufName(aSlot))) ||
                    (aNormalized == Normalize(BufAliasName(aSlot)))) {
                    AppendUnique(&aResult, aSlot);
                }
            }

            aToken.clear();
        };

        for (char aChar : pText) {
            if (std::isalnum(static_cast<unsigned char>(aChar)) || (aChar == '_')) {
                aToken.push_back(aChar);
            } else {
                FlushToken();
            }
        }
        FlushToken();

        return aResult;
    }

    static std::vector<TwistWorkSpaceSlot> UniqueReadSlots(const Step &pStep) {
        std::vector<TwistWorkSpaceSlot> aResult;
        for (const Slice &aSlice : pStep.mSlices) {
            for (TwistWorkSpaceSlot aSlot : aSlice.mIngress) {
                AppendUnique(&aResult, aSlot);
            }
            for (TwistWorkSpaceSlot aSlot : aSlice.mCross) {
                AppendUnique(&aResult, aSlot);
            }
        }
        return aResult;
    }

    static std::vector<TwistWorkSpaceSlot> UniqueWriteSlots(const Step &pStep) {
        std::vector<TwistWorkSpaceSlot> aResult;
        for (const Slice &aSlice : pStep.mSlices) {
            AppendUnique(&aResult, aSlice.mDest);
        }
        return aResult;
    }

    static std::string JoinSlots(const std::vector<TwistWorkSpaceSlot> &pSlots) {
        if (pSlots.empty()) {
            return "(none)";
        }

        std::ostringstream aStream;
        for (std::size_t aIndex = 0U; aIndex < pSlots.size(); ++aIndex) {
            if (aIndex > 0U) {
                aStream << ", ";
            }
            aStream << BufName(pSlots[aIndex]);
        }
        return aStream.str();
    }

    static void PrintCounts(const char *pLabel,
                            const std::map<std::string, int> &pCounts) {
        std::printf("    %s: ", pLabel);
        if (pCounts.empty()) {
            std::printf("(none)\n");
            return;
        }

        bool aNeedsComma = false;
        for (const auto &aEntry : pCounts) {
            if (aNeedsComma) {
                std::printf(", ");
            }
            std::printf("%s=%d", aEntry.first.c_str(), aEntry.second);
            aNeedsComma = true;
        }
        std::printf("\n");
    }

    static void MergeCounts(std::map<std::string, int> *pDest,
                            const std::map<std::string, int> &pSource) {
        if (pDest == nullptr) {
            return;
        }
        for (const auto &aEntry : pSource) {
            (*pDest)[aEntry.first] += aEntry.second;
        }
    }
};

#endif /* GPrintTool_hpp */
