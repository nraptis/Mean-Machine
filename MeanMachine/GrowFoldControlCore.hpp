#ifndef GrowFoldControlCore_hpp
#define GrowFoldControlCore_hpp

#include "ControlOffsetPool.hpp"
#include "ControlValueFile.hpp"
#include "FileIO.hpp"
#include "Library - Twist/TwistWorkSpace.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace GrowFoldControlCore {

enum class Family {
    kGrowA,
    kGrowB,
};

template <Family FoldFamily>
class Control {
public:
    static constexpr std::size_t kCandidateCount = 33U;

    static void Reset(const std::uint64_t pSeed) {
        sCandidates.clear();
        sRendered.clear();
        sFrequencies = FrequencyTable{};

        sStageOneShiftPool =
            ControlOffsetPool::Build<kStageOneShiftValueCount>(
                StageOneShiftStart(),
                kStageOneLength
            );
        sStageTwoShiftPool =
            ControlOffsetPool::Build<kStageTwoShiftValueCount>(
                StageTwoShiftStart(),
                kStageTwoLength
            );

        static_assert(
            ControlOffsetPool::kStageOneShiftAllocationCount <=
                kStageOneLength,
            "Preplanned first-stage fold shifts exceed W_KEY."
        );
        static_assert(
            ControlOffsetPool::kStageTwoShiftAllocationCount <=
                kStageTwoLength,
            "Preplanned second-stage fold shifts exceed W_KEY."
        );
        static_assert(S_BLOCK == 32768,
                      "Generated key folding requires 32,768-byte lanes.");
        static_assert(W_KEY == 2048,
                      "Generated key folding requires 2,048-byte key rows.");
        static_assert((S_BLOCK / W_KEY) == kStageOneBlockCount,
                      "A full lane must contain sixteen key-row chunks.");
        static_assert((S_QUARTER / W_KEY) == kQuarterChunkCount,
                      "A quarter lane must contain four key-row chunks.");
        InitializeShiftFrequencies(
            &sFrequencies.mStageOne,
            kStageOneLength
        );
        InitializeShiftFrequencies(
            &sFrequencies.mStageTwo,
            kStageTwoLength
        );

        sRandomState = pSeed == 0ULL ? DefaultSeed() : pSeed;
        sDidReset = true;
    }

    static std::string Generate(const std::uint64_t pExplorationCases) {
        if (!sDidReset || sCandidates.size() >= kCandidateCount) {
            std::abort();
        }

        const std::uint64_t aCases =
            std::max<std::uint64_t>(1ULL, pExplorationCases);
        const std::uint64_t aEffectiveCases =
            sCandidates.empty() ? 1ULL : aCases;

        Score aScore;
        Candidate aCandidate = Explore(aEffectiveCases, &aScore);
        std::string aValidationError;
        if (!Validate(aCandidate, &aValidationError)) {
            std::abort();
        }

        const Score aDirectScore = DirectFamilyScore(aCandidate);
        if ((aScore.mMinimum != aDirectScore.mMinimum) ||
            (aScore.mTotal != aDirectScore.mTotal)) {
            std::abort();
        }

        const std::size_t aCandidateIndex = sCandidates.size();
        AddToFrequencies(aCandidate);
        sCandidates.push_back(aCandidate);
        sRendered.push_back(
            Render(aCandidate,
                   aCandidateIndex,
                   aScore,
                   aEffectiveCases)
        );
        return sRendered.back();
    }

    static std::string RenderCandidate(
        const std::size_t pCandidateIndex) {
        if (pCandidateIndex >= sCandidates.size()) {
            return "";
        }

        Score aScore{
            std::numeric_limits<std::uint64_t>::max(),
            0ULL,
        };
        if (pCandidateIndex != 0U) {
            for (std::size_t i = 0U; i < pCandidateIndex; ++i) {
                const std::uint64_t aDistance =
                    Distance(sCandidates[pCandidateIndex], sCandidates[i]);
                aScore.mMinimum =
                    std::min(aScore.mMinimum, aDistance);
                aScore.mTotal += aDistance;
            }
        }
        return Render(sCandidates[pCandidateIndex],
                      pCandidateIndex,
                      aScore,
                      0ULL);
    }

    static void Print() {
        for (const std::string &aText : sRendered) {
            std::printf("%s\n", aText.c_str());
        }
    }

    static bool SaveValues(const std::string &pFolder,
                           std::string *pErrorMessage) {
        if (sCandidates.size() != kCandidateCount) {
            SetError(pErrorMessage,
                     std::string(ControlName()) +
                         " needs all 33 candidates before saving values.");
            return false;
        }

        const std::string aFolder = FileIO::ProjectRoot(pFolder);
        for (std::size_t i = 0U; i < sCandidates.size(); ++i) {
            std::string aValidationError;
            if (!Validate(sCandidates[i], &aValidationError)) {
                SetError(
                    pErrorMessage,
                    std::string(ControlName()) +
                        " refused to save candidate " +
                        std::to_string(i + 1U) + ": " +
                        aValidationError
                );
                return false;
            }

            char aName[48];
            CandidateFileName(i, aName, sizeof(aName));
            if (!ControlValueFile::Save(
                    FileIO::Join(aFolder, aName),
                    ValueKind(),
                    CandidateValues(sCandidates[i]),
                    pErrorMessage)) {
                return false;
            }
        }
        return true;
    }

    static bool LoadValues(const std::string &pFolder,
                           std::string *pErrorMessage) {
        if (!sDidReset || !sCandidates.empty()) {
            SetError(pErrorMessage,
                     std::string(ControlName()) +
                         "::Reset must precede value loading.");
            return false;
        }

        const std::string aFolder = FileIO::ProjectRoot(pFolder);
        for (std::size_t i = 0U; i < kCandidateCount; ++i) {
            char aName[48];
            CandidateFileName(i, aName, sizeof(aName));

            std::vector<std::uint64_t> aValues;
            std::string aLoadError;
            if (!ControlValueFile::Load(
                    FileIO::Join(aFolder, aName),
                    ValueKind(),
                    kCandidateValueCount,
                    &aValues,
                    &aLoadError)) {
                SetError(pErrorMessage, aLoadError);
                return false;
            }

            std::string aValueError;
            Candidate aCandidate =
                CandidateFromValues(aValues, &aValueError);
            if (!aValueError.empty()) {
                SetError(pErrorMessage, aValueError);
                return false;
            }

            std::string aValidationError;
            if (!Validate(aCandidate, &aValidationError)) {
                SetError(
                    pErrorMessage,
                    std::string(ControlName()) + " candidate " +
                        std::to_string(i + 1U) +
                        " was invalid: " + aValidationError
                );
                return false;
            }

            const Score aScore = DirectFamilyScore(aCandidate);
            AddToFrequencies(aCandidate);
            sCandidates.push_back(aCandidate);
            sRendered.push_back(Render(aCandidate, i, aScore, 0ULL));
        }
        return true;
    }

    static bool ValidateCandidate(
        const std::size_t pCandidateIndex,
        std::string *pErrorMessage) {
        if (pCandidateIndex >= sCandidates.size()) {
            SetError(pErrorMessage,
                     std::string(ControlName()) +
                         " candidate index was out of range.");
            return false;
        }
        return Validate(sCandidates[pCandidateIndex], pErrorMessage);
    }

    static std::size_t GeneratedCount() {
        return sCandidates.size();
    }

private:
    static constexpr std::size_t kSourceCount = 4U;
    static constexpr std::size_t kSourceChunkCount = 16U;
    static constexpr std::size_t kQuarterChunkCount = 4U;
    static constexpr std::size_t kStageOneBlockCount = 16U;
    static constexpr std::size_t kStageTwoBlockCount = 4U;
    static constexpr std::size_t kStageOneShiftValueCount =
        kSourceCount * kStageOneBlockCount;
    static constexpr std::size_t kStageTwoShiftValueCount =
        kSourceCount * kStageTwoBlockCount;
    static constexpr std::size_t kCandidateValueCount =
        (kStageOneShiftValueCount * 3U) +
        (kStageTwoShiftValueCount * 3U);
    static constexpr std::size_t kStageOneLength =
        static_cast<std::size_t>(W_KEY);
    static constexpr std::size_t kStageTwoLength =
        static_cast<std::size_t>(W_KEY);
    static constexpr std::uint64_t kStageOneDistanceWeight = 1ULL;
    static constexpr std::uint64_t kStageTwoDistanceWeight = 3ULL;
    static constexpr std::uint64_t kMaximumPairDistance =
        (static_cast<std::uint64_t>(
             kStageOneShiftValueCount * 3U
         ) * kStageOneDistanceWeight) +
        (static_cast<std::uint64_t>(
             kStageTwoShiftValueCount * 3U
         ) * kStageTwoDistanceWeight);
    using FinalWordShiftArrangement =
        std::array<std::size_t, kSourceCount>;

    inline static constexpr
        std::array<FinalWordShiftArrangement, 24U>
        kFinalWordShiftArrangements = {{
            {{ 0U, 1U, 2U, 3U }},
            {{ 0U, 1U, 3U, 2U }},
            {{ 0U, 2U, 1U, 3U }},
            {{ 0U, 2U, 3U, 1U }},
            {{ 0U, 3U, 1U, 2U }},
            {{ 0U, 3U, 2U, 1U }},

            {{ 1U, 0U, 2U, 3U }},
            {{ 1U, 0U, 3U, 2U }},
            {{ 1U, 2U, 0U, 3U }},
            {{ 1U, 2U, 3U, 0U }},
            {{ 1U, 3U, 0U, 2U }},
            {{ 1U, 3U, 2U, 0U }},

            {{ 2U, 0U, 1U, 3U }},
            {{ 2U, 0U, 3U, 1U }},
            {{ 2U, 1U, 0U, 3U }},
            {{ 2U, 1U, 3U, 0U }},
            {{ 2U, 3U, 0U, 1U }},
            {{ 2U, 3U, 1U, 0U }},

            {{ 3U, 0U, 1U, 2U }},
            {{ 3U, 0U, 2U, 1U }},
            {{ 3U, 1U, 0U, 2U }},
            {{ 3U, 1U, 2U, 0U }},
            {{ 3U, 2U, 0U, 1U }},
            {{ 3U, 2U, 1U, 0U }},
        }};

    // All 24 arrangements occur once. Nine balanced, non-identity
    // arrangements occur a second time to fill the 33 candidates.
    inline static constexpr std::array<std::size_t, kCandidateCount>
        kFinalWordShiftSchedule = {{
            0U, 1U, 2U, 3U,
            4U, 5U, 6U, 7U,
            8U, 9U, 10U, 11U,
            12U, 13U, 14U, 15U,
            16U, 17U, 18U, 19U,
            20U, 21U, 22U, 23U,

            1U, 2U, 3U,
            6U, 11U, 12U,
            17U, 20U, 22U,
        }};

    static constexpr bool IsValidFinalWordShiftSchedule() {
        std::array<std::size_t, 24U> aArrangementCounts{};
        std::array<
            std::array<std::size_t, kSourceCount>,
            kSourceCount> aPositionCounts{};

        for (const std::size_t aArrangementIndex :
             kFinalWordShiftSchedule) {
            if (aArrangementIndex >=
                kFinalWordShiftArrangements.size()) {
                return false;
            }
            ++aArrangementCounts[aArrangementIndex];
            const FinalWordShiftArrangement &aArrangement =
                kFinalWordShiftArrangements[aArrangementIndex];
            for (std::size_t aSource = 0U;
                 aSource < kSourceCount;
                 ++aSource) {
                ++aPositionCounts[aSource][aArrangement[aSource]];
            }
        }

        if (aArrangementCounts[0] != 1U) {
            return false;
        }
        for (const std::size_t aCount : aArrangementCounts) {
            if ((aCount < 1U) || (aCount > 2U)) {
                return false;
            }
        }
        for (const auto &aPosition : aPositionCounts) {
            for (const std::size_t aCount : aPosition) {
                if ((aCount < 8U) || (aCount > 9U)) {
                    return false;
                }
            }
        }
        return true;
    }

    static_assert(
        IsValidFinalWordShiftSchedule(),
        "Final key-fold byte placements must use every permutation once "
        "or twice, use identity once, and remain position-balanced."
    );

    template <std::size_t BlockCount>
    struct Stage {
        using Route = std::array<std::uint8_t, BlockCount>;
        using Shifts = std::array<std::uint16_t, BlockCount>;
        using WordShifts = std::array<std::uint8_t, BlockCount>;

        std::array<Route, kSourceCount> mSourceIndices{};
        std::array<Shifts, kSourceCount> mShifts{};
        std::array<WordShifts, kSourceCount> mWordShifts{};
    };

    struct Candidate {
        Stage<kStageOneBlockCount> mStageOne{};
        Stage<kStageTwoBlockCount> mStageTwo{};
    };

    struct Score {
        std::uint64_t mMinimum = 0ULL;
        std::uint64_t mTotal = 0ULL;
    };

    template <std::size_t BlockCount>
    struct StageFrequencyTable {
        std::array<
            std::array<
                std::array<
                    std::uint8_t,
                    kSourceChunkCount>,
                BlockCount>,
            kSourceCount> mSourceIndices{};
        std::array<
            std::array<
                std::vector<std::uint8_t>,
                BlockCount>,
            kSourceCount> mShifts{};
        std::array<
            std::array<
                std::array<
                    std::uint8_t,
                    kSourceCount>,
                BlockCount>,
            kSourceCount> mWordShifts{};
    };

    struct FrequencyTable {
        StageFrequencyTable<kStageOneBlockCount> mStageOne{};
        StageFrequencyTable<kStageTwoBlockCount> mStageTwo{};
        std::size_t mCandidateCount = 0U;
    };

    inline static std::vector<Candidate> sCandidates{};
    inline static std::vector<std::string> sRendered{};
    inline static FrequencyTable sFrequencies{};
    inline static std::array<std::uint16_t, kStageOneShiftValueCount>
        sStageOneShiftPool{};
    inline static std::array<std::uint16_t, kStageTwoShiftValueCount>
        sStageTwoShiftPool{};
    inline static std::uint64_t sRandomState = 0ULL;
    inline static bool sDidReset = false;

    static constexpr bool IsGrowA() {
        return FoldFamily == Family::kGrowA;
    }

    static const FinalWordShiftArrangement &
    FinalWordShifts(const std::size_t pCandidateIndex) {
        const std::size_t aArrangementIndex =
            kFinalWordShiftSchedule[
                pCandidateIndex %
                kFinalWordShiftSchedule.size()
            ];
        return kFinalWordShiftArrangements[aArrangementIndex];
    }

    static constexpr const char *ControlName() {
        return IsGrowA() ? "GrowAControl" : "GrowBControl";
    }

    static constexpr const char *CandidateStem() {
        return IsGrowA() ? "GrowKeyA" : "GrowKeyB";
    }

    static constexpr const char *SourceLaneFamily() {
        return IsGrowA() ? "Kinetic" : "Shadow";
    }

    static constexpr const char *ShiftFunction() {
        return IsGrowA()
            ? "TwistShiftBox::ShiftKeyBoxA"
            : "TwistShiftBox::ShiftKeyBoxB";
    }

    static constexpr const char *KeyBoxName() {
        return IsGrowA() ? "mKeyBoxA" : "mKeyBoxB";
    }

    static constexpr ControlValueFile::Kind ValueKind() {
        return IsGrowA()
            ? ControlValueFile::Kind::kGrowA
            : ControlValueFile::Kind::kGrowB;
    }

    static constexpr std::uint64_t DefaultSeed() {
        return IsGrowA()
            ? 0x47524F57415F3333ULL
            : 0x47524F57425F3333ULL;
    }

    static constexpr std::size_t StageOneShiftStart() {
        return IsGrowA()
            ? ControlOffsetPool::kGrowAStageOneShiftStart
            : ControlOffsetPool::kGrowBStageOneShiftStart;
    }

    static constexpr std::size_t StageTwoShiftStart() {
        return IsGrowA()
            ? ControlOffsetPool::kGrowAStageTwoShiftStart
            : ControlOffsetPool::kGrowBStageTwoShiftStart;
    }

    static void SetError(std::string *pErrorMessage,
                         const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }

    static void CandidateFileName(const std::size_t pCandidateIndex,
                                  char *pName,
                                  const std::size_t pNameSize) {
        std::snprintf(pName,
                      pNameSize,
                      "%s_Candidate%02zu.bin",
                      CandidateStem(),
                      pCandidateIndex + 1U);
    }

    static std::uint64_t NextRandom() {
        sRandomState += 0x9E3779B97F4A7C15ULL;
        std::uint64_t aValue = sRandomState;
        aValue =
            (aValue ^ (aValue >> 30U)) * 0xBF58476D1CE4E5B9ULL;
        aValue =
            (aValue ^ (aValue >> 27U)) * 0x94D049BB133111EBULL;
        return aValue ^ (aValue >> 31U);
    }

    static std::size_t RandomIndex(const std::size_t pLimit) {
        return pLimit == 0U
            ? 0U
            : static_cast<std::size_t>(NextRandom() % pLimit);
    }

    template <typename Value, std::size_t Count>
    static void Shuffle(std::array<Value, Count> *pValues) {
        for (std::size_t i = Count; i > 1U; --i) {
            std::swap((*pValues)[i - 1U],
                      (*pValues)[RandomIndex(i)]);
        }
    }

    template <std::size_t BlockCount>
    static void InitializeShiftFrequencies(
        StageFrequencyTable<BlockCount> *pFrequencies,
        const std::size_t pShiftLimit) {
        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            for (std::size_t aBlock = 0U;
                 aBlock < BlockCount;
                 ++aBlock) {
                pFrequencies->mShifts[aSource][aBlock].assign(
                    pShiftLimit,
                    0U
                );
            }
        }
    }

    template <std::size_t BlockCount>
    static typename Stage<BlockCount>::Route RandomRoute() {
        typename Stage<BlockCount>::Route aRoute{};
        for (std::size_t i = 0U;
             i < BlockCount;
             ++i) {
            aRoute[i] = static_cast<std::uint8_t>(i);
        }
        Shuffle(&aRoute);
        return aRoute;
    }

    static bool StageOneRouteAvoidsPriorSources(
        const Stage<kStageOneBlockCount> &pStage,
        const std::size_t pSource,
        const Stage<kStageOneBlockCount>::Route &pRoute) {
        for (std::size_t aBlock = 0U;
             aBlock < kStageOneBlockCount;
             ++aBlock) {
            for (std::size_t aPriorSource = 0U;
                 aPriorSource < pSource;
                 ++aPriorSource) {
                if (pRoute[aBlock] ==
                    pStage.mSourceIndices[aPriorSource][aBlock]) {
                    return false;
                }
            }
        }
        return true;
    }

    static bool StageOneChunksAreDistinctPerLoop(
        const Stage<kStageOneBlockCount> &pStage) {
        for (std::size_t aBlock = 0U;
             aBlock < kStageOneBlockCount;
             ++aBlock) {
            std::array<bool, kStageOneBlockCount> aSeen{};
            for (std::size_t aSource = 0U;
                 aSource < kSourceCount;
                 ++aSource) {
                const std::uint8_t aChunk =
                    pStage.mSourceIndices[aSource][aBlock];
                if ((aChunk >= kStageOneBlockCount) ||
                    aSeen[aChunk]) {
                    return false;
                }
                aSeen[aChunk] = true;
            }
        }
        return true;
    }

    static bool StageTwoHasAtMostOneRepeatedQuarterPerLoop(
        const Stage<kStageTwoBlockCount> &pStage) {
        for (std::size_t aBlock = 0U;
             aBlock < kStageTwoBlockCount;
             ++aBlock) {
            std::array<bool, kStageTwoBlockCount> aSeen{};
            std::size_t aUniqueQuarterCount = 0U;
            for (std::size_t aSource = 0U;
                 aSource < kSourceCount;
                 ++aSource) {
                const std::uint8_t aQuarter =
                    pStage.mSourceIndices[aSource][aBlock];
                if (aQuarter >= kStageTwoBlockCount) {
                    return false;
                }
                if (!aSeen[aQuarter]) {
                    aSeen[aQuarter] = true;
                    ++aUniqueQuarterCount;
                }
            }
            if (aUniqueQuarterCount < 3U) {
                return false;
            }
        }
        return true;
    }

    template <std::size_t BlockCount>
    static void FillWordShifts(Stage<BlockCount> *pStage) {
        for (std::size_t aBlock = 0U;
             aBlock < BlockCount;
             ++aBlock) {
            std::array<std::uint8_t, kSourceCount> aWordShiftOrder = {
                0U, 1U, 2U, 3U,
            };
            Shuffle(&aWordShiftOrder);
            for (std::size_t aSource = 0U;
                 aSource < kSourceCount;
                 ++aSource) {
                pStage->mWordShifts[aSource][aBlock] =
                    aWordShiftOrder[aSource];
            }
        }
    }

    static Candidate MakeCandidate() {
        Candidate aCandidate;
        auto aStageOneShifts = sStageOneShiftPool;
        auto aStageTwoShifts = sStageTwoShiftPool;
        Shuffle(&aStageOneShifts);
        Shuffle(&aStageTwoShifts);

        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            typename Stage<kStageOneBlockCount>::Route aRoute;
            do {
                aRoute = RandomRoute<kStageOneBlockCount>();
            } while (!StageOneRouteAvoidsPriorSources(
                aCandidate.mStageOne,
                aSource,
                aRoute
            ));
            aCandidate.mStageOne.mSourceIndices[aSource] =
                aRoute;
            for (std::size_t aBlock = 0U;
                 aBlock < kStageOneBlockCount;
                 ++aBlock) {
                aCandidate.mStageOne.mShifts[aSource][aBlock] =
                    aStageOneShifts[
                        (aSource * kStageOneBlockCount) + aBlock
                    ];
            }
        }
        FillWordShifts(&aCandidate.mStageOne);

        do {
            for (std::size_t aSource = 0U;
                 aSource < kSourceCount;
                 ++aSource) {
                aCandidate.mStageTwo.mSourceIndices[aSource] =
                    RandomRoute<kStageTwoBlockCount>();
            }
        } while (!StageTwoHasAtMostOneRepeatedQuarterPerLoop(
            aCandidate.mStageTwo
        ));

        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            for (std::size_t aBlock = 0U;
                 aBlock < kStageTwoBlockCount;
                 ++aBlock) {
                aCandidate.mStageTwo.mShifts[aSource][aBlock] =
                    aStageTwoShifts[
                        (aSource * kStageTwoBlockCount) + aBlock
                    ];
            }
        }
        FillWordShifts(&aCandidate.mStageTwo);
        return aCandidate;
    }

    template <std::size_t BlockCount>
    static void AppendStageValues(
        const Stage<BlockCount> &pStage,
        std::vector<std::uint64_t> *pValues) {
        for (const auto &aRoute : pStage.mSourceIndices) {
            for (const std::uint8_t aValue : aRoute) {
                pValues->push_back(aValue);
            }
        }
        for (const auto &aShifts : pStage.mShifts) {
            for (const std::uint16_t aValue : aShifts) {
                pValues->push_back(aValue);
            }
        }
        for (const auto &aWordShifts : pStage.mWordShifts) {
            for (const std::uint8_t aValue : aWordShifts) {
                pValues->push_back(aValue);
            }
        }
    }

    static std::vector<std::uint64_t> CandidateValues(
        const Candidate &pCandidate) {
        std::vector<std::uint64_t> aValues;
        aValues.reserve(kCandidateValueCount);
        AppendStageValues(pCandidate.mStageOne, &aValues);
        AppendStageValues(pCandidate.mStageTwo, &aValues);
        return aValues;
    }

    static Candidate CandidateFromValues(
        const std::vector<std::uint64_t> &pValues,
        std::string *pErrorMessage) {
        Candidate aCandidate;
        std::size_t aValueIndex = 0U;
        std::size_t aInvalidCount = 0U;

        auto Next = [&](const std::uint64_t pLimit) {
            const std::uint64_t aRaw =
                aValueIndex < pValues.size()
                    ? pValues[aValueIndex]
                    : 0ULL;
            ++aValueIndex;
            if (aRaw >= pLimit) {
                ++aInvalidCount;
                return 0ULL;
            }
            return aRaw;
        };

        auto ReadStage = [&]<std::size_t BlockCount>(
            Stage<BlockCount> *pStage,
            const std::uint64_t pSourceIndexLimit,
            const std::uint64_t pShiftLimit) {
            for (auto &aRoute : pStage->mSourceIndices) {
                for (std::uint8_t &aValue : aRoute) {
                    aValue = static_cast<std::uint8_t>(
                        Next(pSourceIndexLimit)
                    );
                }
            }
            for (auto &aShifts : pStage->mShifts) {
                for (std::uint16_t &aValue : aShifts) {
                    aValue = static_cast<std::uint16_t>(
                        Next(pShiftLimit)
                    );
                }
            }
            for (auto &aWordShifts : pStage->mWordShifts) {
                for (std::uint8_t &aValue : aWordShifts) {
                    aValue = static_cast<std::uint8_t>(
                        Next(kSourceCount)
                    );
                }
            }
        };
        ReadStage(&aCandidate.mStageOne,
                  kSourceChunkCount,
                  kStageOneLength);
        ReadStage(&aCandidate.mStageTwo,
                  kQuarterChunkCount,
                  kStageTwoLength);

        if (aInvalidCount != 0U) {
            SetError(
                pErrorMessage,
                std::string(ControlName()) + " contained " +
                    std::to_string(aInvalidCount) +
                    " out-of-range value(s)."
            );
        } else if (pErrorMessage != nullptr) {
            pErrorMessage->clear();
        }
        return aCandidate;
    }

    template <std::size_t BlockCount>
    static std::uint64_t StageDistance(
        const Stage<BlockCount> &pLeft,
        const Stage<BlockCount> &pRight,
        const std::uint64_t pWeight) {
        std::uint64_t aDistance = 0ULL;
        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            for (std::size_t aBlock = 0U;
                 aBlock < BlockCount;
                 ++aBlock) {
                aDistance +=
                    pLeft.mSourceIndices[aSource][aBlock] !=
                    pRight.mSourceIndices[aSource][aBlock]
                        ? pWeight
                        : 0ULL;
                aDistance +=
                    pLeft.mShifts[aSource][aBlock] !=
                    pRight.mShifts[aSource][aBlock]
                        ? pWeight
                        : 0ULL;
                aDistance +=
                    pLeft.mWordShifts[aSource][aBlock] !=
                    pRight.mWordShifts[aSource][aBlock]
                        ? pWeight
                        : 0ULL;
            }
        }
        return aDistance;
    }

    static std::uint64_t Distance(const Candidate &pLeft,
                                  const Candidate &pRight) {
        return
            StageDistance(pLeft.mStageOne,
                          pRight.mStageOne,
                          kStageOneDistanceWeight) +
            StageDistance(pLeft.mStageTwo,
                          pRight.mStageTwo,
                          kStageTwoDistanceWeight);
    }

    static std::uint64_t MinimumDistance(
        const Candidate &pCandidate) {
        if (sCandidates.empty()) {
            return std::numeric_limits<std::uint64_t>::max();
        }
        std::uint64_t aMinimum =
            std::numeric_limits<std::uint64_t>::max();
        for (const Candidate &aExisting : sCandidates) {
            aMinimum =
                std::min(aMinimum,
                         Distance(pCandidate, aExisting));
        }
        return aMinimum;
    }

    template <std::size_t BlockCount>
    static std::uint64_t StageTotalDistance(
        const Stage<BlockCount> &pStage,
        const StageFrequencyTable<BlockCount> &pFrequencies,
        const std::uint64_t pCandidateCount,
        const std::uint64_t pWeight) {
        std::uint64_t aTotal = 0ULL;
        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            for (std::size_t aBlock = 0U;
                 aBlock < BlockCount;
                 ++aBlock) {
                const std::uint8_t aSourceIndex =
                    pStage.mSourceIndices[aSource][aBlock];
                const std::uint16_t aShift =
                    pStage.mShifts[aSource][aBlock];
                const std::uint8_t aWordShift =
                    pStage.mWordShifts[aSource][aBlock];
                aTotal +=
                    (pCandidateCount -
                     pFrequencies.mSourceIndices[aSource][aBlock]
                                                [aSourceIndex]) *
                    pWeight;
                aTotal +=
                    (pCandidateCount -
                     pFrequencies.mShifts[aSource][aBlock][aShift]) *
                    pWeight;
                aTotal +=
                    (pCandidateCount -
                     pFrequencies.mWordShifts[aSource][aBlock]
                                                 [aWordShift]) *
                    pWeight;
            }
        }
        return aTotal;
    }

    static std::uint64_t TotalDistance(
        const Candidate &pCandidate) {
        const std::uint64_t aCandidateCount =
            static_cast<std::uint64_t>(
                sFrequencies.mCandidateCount
            );
        return
            StageTotalDistance(
                pCandidate.mStageOne,
                sFrequencies.mStageOne,
                aCandidateCount,
                kStageOneDistanceWeight
            ) +
            StageTotalDistance(
                pCandidate.mStageTwo,
                sFrequencies.mStageTwo,
                aCandidateCount,
                kStageTwoDistanceWeight
            );
    }

    static Score FamilyScore(const Candidate &pCandidate) {
        return {
            MinimumDistance(pCandidate),
            TotalDistance(pCandidate),
        };
    }

    static Score DirectFamilyScore(const Candidate &pCandidate) {
        if (sCandidates.empty()) {
            return {
                std::numeric_limits<std::uint64_t>::max(),
                0ULL,
            };
        }

        Score aScore{
            std::numeric_limits<std::uint64_t>::max(),
            0ULL,
        };
        for (const Candidate &aExisting : sCandidates) {
            const std::uint64_t aDistance =
                Distance(pCandidate, aExisting);
            aScore.mMinimum =
                std::min(aScore.mMinimum, aDistance);
            aScore.mTotal += aDistance;
        }
        return aScore;
    }

    static bool Better(const Score &pLeft,
                       const Score &pRight) {
        return (pLeft.mMinimum > pRight.mMinimum) ||
               ((pLeft.mMinimum == pRight.mMinimum) &&
                (pLeft.mTotal > pRight.mTotal));
    }

    static Candidate Explore(const std::uint64_t pCases,
                             Score *pScore) {
        Candidate aBest = MakeCandidate();
        Score aBestScore = FamilyScore(aBest);
        for (std::uint64_t i = 1ULL; i < pCases; ++i) {
            Candidate aTrial = MakeCandidate();
            const Score aTrialScore = FamilyScore(aTrial);
            if (Better(aTrialScore, aBestScore)) {
                aBest = aTrial;
                aBestScore = aTrialScore;
            }
        }
        if (pScore != nullptr) {
            *pScore = aBestScore;
        }
        return aBest;
    }

    template <std::size_t BlockCount>
    static void AddStageToFrequencies(
        const Stage<BlockCount> &pStage,
        StageFrequencyTable<BlockCount> *pFrequencies) {
        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            for (std::size_t aBlock = 0U;
                 aBlock < BlockCount;
                 ++aBlock) {
                const std::uint8_t aSourceIndex =
                    pStage.mSourceIndices[aSource][aBlock];
                const std::uint16_t aShift =
                    pStage.mShifts[aSource][aBlock];
                const std::uint8_t aWordShift =
                    pStage.mWordShifts[aSource][aBlock];
                ++pFrequencies
                      ->mSourceIndices[aSource][aBlock][aSourceIndex];
                ++pFrequencies
                      ->mShifts[aSource][aBlock][aShift];
                ++pFrequencies
                      ->mWordShifts[aSource][aBlock][aWordShift];
            }
        }
    }

    static void AddToFrequencies(
        const Candidate &pCandidate) {
        AddStageToFrequencies(pCandidate.mStageOne,
                              &sFrequencies.mStageOne);
        AddStageToFrequencies(pCandidate.mStageTwo,
                              &sFrequencies.mStageTwo);
        ++sFrequencies.mCandidateCount;
    }

    template <std::size_t Count>
    static bool IsCompleteRoute(
        const std::array<std::uint8_t, Count> &pValues) {
        std::array<std::uint8_t, Count> aSorted = pValues;
        std::sort(aSorted.begin(), aSorted.end());
        for (std::size_t i = 0U; i < Count; ++i) {
            if (aSorted[i] != i) {
                return false;
            }
        }
        return true;
    }

    static bool IsStageTwoPermutation(
        const Stage<kStageTwoBlockCount> &pStage) {
        for (const auto &aRoute : pStage.mSourceIndices) {
            if (!IsCompleteRoute(aRoute)) {
                return false;
            }
        }
        return true;
    }

    template <std::size_t Count>
    static bool SameValues(
        std::array<std::uint16_t, Count> pLeft,
        std::array<std::uint16_t, Count> pRight) {
        std::sort(pLeft.begin(), pLeft.end());
        std::sort(pRight.begin(), pRight.end());
        return pLeft == pRight;
    }

    template <std::size_t BlockCount>
    static bool ValidateWordShifts(
        const Stage<BlockCount> &pStage,
        std::string *pErrorMessage) {
        for (std::size_t aBlock = 0U;
             aBlock < BlockCount;
             ++aBlock) {
            std::array<bool, kSourceCount> aSeen{};
            for (std::size_t aSource = 0U;
                 aSource < kSourceCount;
                 ++aSource) {
                const std::uint8_t aWordShift =
                    pStage.mWordShifts[aSource][aBlock];
                if ((aWordShift >= kSourceCount) ||
                    aSeen[aWordShift]) {
                    SetError(
                        pErrorMessage,
                        std::string(ControlName()) +
                            " word-byte shifts were not a "
                            "permutation of 0, 8, 16, and 24."
                    );
                    return false;
                }
                aSeen[aWordShift] = true;
            }
        }
        return true;
    }

    template <std::size_t BlockCount>
    static std::array<std::uint16_t,
                      kSourceCount * BlockCount>
    FlattenShifts(const Stage<BlockCount> &pStage) {
        std::array<std::uint16_t,
                   kSourceCount * BlockCount> aShifts{};
        std::size_t aShiftIndex = 0U;
        for (const auto &aSourceShifts : pStage.mShifts) {
            for (const std::uint16_t aShift : aSourceShifts) {
                aShifts[aShiftIndex++] = aShift;
            }
        }
        return aShifts;
    }

    static bool Validate(const Candidate &pCandidate,
                         std::string *pErrorMessage) {
        for (const auto &aRoute :
             pCandidate.mStageOne.mSourceIndices) {
            if (!IsCompleteRoute(aRoute)) {
                SetError(
                    pErrorMessage,
                    std::string(ControlName()) +
                        " first-stage source-index array was not "
                        "a permutation of all sixteen chunks."
                );
                return false;
            }
        }
        if (!StageOneChunksAreDistinctPerLoop(
            pCandidate.mStageOne
        )) {
            SetError(
                pErrorMessage,
                std::string(ControlName()) +
                    " first-stage loop reused a chunk number "
                    "across source lanes."
            );
            return false;
        }
        if (!IsStageTwoPermutation(pCandidate.mStageTwo)) {
            SetError(
                pErrorMessage,
                std::string(ControlName()) +
                    " each second-stage quarter did not use "
                    "all four of its chunks exactly once."
            );
            return false;
        }
        if (!StageTwoHasAtMostOneRepeatedQuarterPerLoop(
            pCandidate.mStageTwo
        )) {
            SetError(
                pErrorMessage,
                std::string(ControlName()) +
                    " second-stage loop used fewer than three "
                    "distinct quarter indices."
            );
            return false;
        }
        if (!ValidateWordShifts(pCandidate.mStageOne,
                                pErrorMessage) ||
            !ValidateWordShifts(pCandidate.mStageTwo,
                                pErrorMessage)) {
            return false;
        }

        const auto aStageOneShifts =
            FlattenShifts(pCandidate.mStageOne);
        if (!SameValues(aStageOneShifts,
                        sStageOneShiftPool)) {
            SetError(
                pErrorMessage,
                std::string(ControlName()) +
                    " first stage did not use its complete "
                    "preplanned shift pool."
            );
            return false;
        }
        const auto aStageTwoShifts =
            FlattenShifts(pCandidate.mStageTwo);
        if (!SameValues(aStageTwoShifts,
                        sStageTwoShiftPool)) {
            SetError(
                pErrorMessage,
                std::string(ControlName()) +
                    " second stage did not use its complete "
                    "preplanned shift pool."
            );
            return false;
        }

        if (pErrorMessage != nullptr) {
            pErrorMessage->clear();
        }
        return true;
    }

    static char Letter(const std::size_t pIndex) {
        return static_cast<char>('A' + pIndex);
    }

    template <std::size_t BlockCount>
    static void RenderFoldWord(std::ostringstream *pStream,
                               const char *pDestination,
                               const std::size_t pBlock,
                               const bool pFirstStage,
                               const Stage<BlockCount> &pStage) {
        *pStream
            << (pFirstStage
                    ? "    // Chunks: "
                    : "    // Quarters A-D, chunks: ");
        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            *pStream
                << static_cast<std::size_t>(
                       pStage.mSourceIndices[aSource][pBlock]
                   );
            if (aSource + 1U != kSourceCount) {
                *pStream << ", ";
            }
        }
        *pStream
            << "\n"
            << "    for (std::size_t aIndex = 0U; "
            << "aIndex < W_KEY"
            << "; aIndex += 1U) {\n";
        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            const std::size_t aSourceIndex =
                pStage.mSourceIndices[aSource][pBlock];
            const std::size_t aSourceShift =
                pStage.mShifts[aSource][pBlock];
            *pStream
                << "        const std::size_t aIndex"
                << Letter(aSource) << " = ("
                << aSourceIndex
                << "U * W_KEY) + ((aIndex + " << aSourceShift
                << "U) & W_KEY1);\n";
        }

        *pStream
            << "\n"
            << "        std::uint32_t aFoldValue = 0U;\n";
        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            const std::size_t aWordShift =
                static_cast<std::size_t>(
                    pStage.mWordShifts[aSource][pBlock]
                ) * 8U;
            const std::string aSourceName =
                pFirstStage
                    ? std::string("aSourceLane") + Letter(aSource)
                    : std::string("aFoldLane") + Letter(aSource);
            *pStream
                << "        aFoldValue |= "
                << "static_cast<std::uint32_t>("
                << aSourceName << "[aIndex" << Letter(aSource)
                << "]) << " << aWordShift << "U;\n";
        }
        *pStream
            << "        aFoldValue = "
               "TwistMix32::DiffuseA(aFoldValue);\n"
            << "        " << pDestination
            << "[aIndex] = static_cast<std::uint8_t>("
               "aFoldValue);\n"
            << "    }\n";
    }

    static void RenderFoldPointers(std::ostringstream *pStream,
                                   const char *pLanePrefix) {
        for (std::size_t aBlock = 0U;
             aBlock < kStageOneBlockCount;
             ++aBlock) {
            const std::size_t aLane = aBlock / 4U;
            const std::size_t aChunk = aBlock % 4U;
            *pStream
                << "    std::uint8_t *aFold"
                << Letter(aBlock) << " = " << pLanePrefix
                << Letter(aLane) << " + "
                << "(" << aChunk << "U * W_KEY);\n";
        }
    }

    static std::string Render(const Candidate &pCandidate,
                              const std::size_t pCandidateIndex,
                              const Score &pScore,
                              const std::uint64_t pCases) {
        std::ostringstream aStream;
        const FinalWordShiftArrangement &aFinalWordShifts =
            FinalWordShifts(pCandidateIndex);
        aStream
            << "    // " << ControlName() << " candidate "
            << (pCandidateIndex + 1U) << " of 33\n"
            << "    // Exploration cases: " << pCases << "\n";
        if (pCandidateIndex == 0U) {
            aStream
                << "    // Structural distance: baseline candidate\n";
        } else {
            aStream
                << "    // Structural maximin " << pScore.mMinimum
                << " / " << kMaximumPairDistance
                << "; family total " << pScore.mTotal << "\n";
        }

        for (std::size_t aLane = 0U;
             aLane < kSourceCount;
             ++aLane) {
            aStream
                << "    std::uint8_t *aSourceLane"
                << Letter(aLane)
                << " = pWorkSpace->m"
                << SourceLaneFamily() << "Lane"
                << Letter(aLane) << ";\n";
        }
        aStream << "\n";
        for (std::size_t aLane = 0U;
             aLane < kSourceCount;
             ++aLane) {
            aStream
                << "    std::uint8_t *aFoldLane"
                << Letter(aLane)
                << " = pWorkSpace->mSpiritLane"
                << Letter(aLane) << ";\n";
        }
        aStream
            << "\n"
            << "    std::uint8_t *aKeyRow = "
               "&(pWorkSpace->"
            << KeyBoxName() << "[0][0]);\n"
            << "\n"
            << "    static_assert(S_BLOCK == 32768, "
               "\"Key folding requires 32,768-byte lanes.\");\n"
            << "    static_assert(W_KEY == 2048, "
               "\"Key folding requires 2,048-byte key rows.\");\n"
            << "\n"
            << "    " << ShiftFunction()
            << "(pWorkSpace);\n"
            << "\n"
            << "    // Fold Stage I\n\n";

        RenderFoldPointers(&aStream, "aFoldLane");
        aStream << "\n";
        for (std::size_t aBlock = 0U;
             aBlock < kStageOneBlockCount;
             ++aBlock) {
            RenderFoldWord(
                &aStream,
                (std::string("aFold") + Letter(aBlock)).c_str(),
                aBlock,
                true,
                pCandidate.mStageOne
            );
            if (aBlock + 1U != kStageOneBlockCount) {
                aStream << "\n";
            }
        }
        aStream << "\n";

        aStream
            << "    // Fold Stage II\n\n";
        for (std::size_t aBlock = 0U;
             aBlock < kStageTwoBlockCount;
             ++aBlock) {
            RenderFoldWord(
                &aStream,
                (std::string("aSourceLane") +
                 Letter(aBlock)).c_str(),
                aBlock,
                false,
                pCandidate.mStageTwo
            );
            if (aBlock + 1U != kStageTwoBlockCount) {
                aStream << "\n";
            }
        }
        aStream
            << "\n"
            << "    // Fold Stage III\n"
            << "\n"
            << "    for (std::size_t aIndex = 0U; "
               "aIndex < W_KEY; aIndex += 1U) {\n"
            << "        std::uint32_t aValue = 0U;\n";
        for (std::size_t aSource = 0U;
             aSource < kSourceCount;
             ++aSource) {
            aStream
                << "        aValue |= "
                   "static_cast<std::uint32_t>("
                << "aSourceLane" << Letter(aSource)
                << "[aIndex]) << "
                << (aFinalWordShifts[aSource] * 8U)
                << "U;\n";
        }
        aStream
            << "        aValue = TwistMix32::DiffuseA(aValue);\n"
            << "        aKeyRow[aIndex] = "
               "static_cast<std::uint8_t>(aValue);\n"
            << "    }\n";

        return aStream.str();
    }
};

} // namespace GrowFoldControlCore

#endif /* GrowFoldControlCore_hpp */
