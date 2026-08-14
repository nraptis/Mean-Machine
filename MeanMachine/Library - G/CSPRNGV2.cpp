//
//  CSPRNGV2.cpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/18/26.
//

#include "CSPRNGV2.hpp"
#include "TwistArray.hpp"
#include <algorithm>
#include <array>
#include <cstdio>
#include <limits>

namespace {

constexpr std::size_t kSaltLaneCount = 8U;
constexpr std::size_t kNonceWordCount = 16U;

int NonceKindIndex(const GAXSKNonceByteKind pKind) {
    switch (pKind) {
        case GAXSKNonceByteKind::kNonceA: return 0;
        case GAXSKNonceByteKind::kNonceB: return 1;
        case GAXSKNonceByteKind::kNonceC: return 2;
        case GAXSKNonceByteKind::kNonceD: return 3;
        case GAXSKNonceByteKind::kNonceE: return 4;
        case GAXSKNonceByteKind::kNonceF: return 5;
        case GAXSKNonceByteKind::kNonceG: return 6;
        case GAXSKNonceByteKind::kNonceH: return 7;
        case GAXSKNonceByteKind::kNonceI: return 8;
        case GAXSKNonceByteKind::kNonceJ: return 9;
        case GAXSKNonceByteKind::kNonceK: return 10;
        case GAXSKNonceByteKind::kNonceL: return 11;
        case GAXSKNonceByteKind::kNonceM: return 12;
        case GAXSKNonceByteKind::kNonceN: return 13;
        case GAXSKNonceByteKind::kNonceO: return 14;
        case GAXSKNonceByteKind::kNonceP: return 15;
        default: return -1;
    }
}

int SymbolIndex(const std::vector<GSymbol> &pNonceWords,
                const GSymbol &pSymbol) {
    for (std::size_t i = 0U; i < pNonceWords.size(); ++i) {
        if (pNonceWords[i] == pSymbol) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

std::vector<GSymbol> MakeCanonicalWanderers() {
    return {
        GSymbol::Var(TwistVariable::kWandererA),
        GSymbol::Var(TwistVariable::kWandererB),
        GSymbol::Var(TwistVariable::kWandererC),
        GSymbol::Var(TwistVariable::kWandererD),
        GSymbol::Var(TwistVariable::kWandererE),
        GSymbol::Var(TwistVariable::kWandererF),
        GSymbol::Var(TwistVariable::kWandererG),
        GSymbol::Var(TwistVariable::kWandererH),
        GSymbol::Var(TwistVariable::kWandererI),
        GSymbol::Var(TwistVariable::kWandererJ),
        GSymbol::Var(TwistVariable::kWandererK),
    };
}

bool FillSaltBag(const std::vector<GSymbol> &pSaltsOrbiterAssign,
                 const std::vector<GSymbol> &pSaltsOrbiterUpdate,
                 const std::vector<GSymbol> &pSaltsWandererUpdate,
                 GAXPLSaltBag *pSaltBag,
                 std::string *pErrorMessage) {
    if (pSaltBag == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "CSPRNGV2::FillSaltBag received null salt bag";
        }
        return false;
    }

    if ((pSaltsOrbiterAssign.size() != kSaltLaneCount) ||
        (pSaltsOrbiterUpdate.size() != kSaltLaneCount) ||
        (pSaltsWandererUpdate.size() != kSaltLaneCount)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage =
                "CSPRNGV2::FillSaltBag requires exactly eight salts for every role";
        }
        return false;
    }

    pSaltBag->mOrbiterAssign = pSaltsOrbiterAssign;
    pSaltBag->mOrbiterUpdate = pSaltsOrbiterUpdate;
    pSaltBag->mWandererUpdate = pSaltsWandererUpdate;
    return true;
}

bool PlanNonceWords(const std::vector<GSymbol> &pNonceWords,
                    std::vector<CSPRNGV2Slice> *pSlices,
                    std::string *pErrorMessage) {
    if ((pSlices == nullptr) ||
        (pNonceWords.size() != kNonceWordCount)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "CSPRNGV2::PlanNonceWords received invalid inputs";
        }
        return false;
    }

    std::array<int, kNonceWordCount> aUsage = {};

    for (CSPRNGV2Slice &aSlice : *pSlices) {
        aSlice.mNoncePlan = GAXPLNoncePlan();
        if (!aSlice.mARXSkeleton.HasNonceSlots()) {
            aSlice.mNonceBytes.clear();
            continue;
        }

        const auto IsValidRoleCount = [](const int pCount) {
            return (pCount >= 2) && (pCount <= 4);
        };
        if (!IsValidRoleCount(aSlice.mNonceCountOrbiterAssign) ||
            !IsValidRoleCount(aSlice.mNonceCountOrbiterUpdate) ||
            !IsValidRoleCount(aSlice.mNonceCountWandererUpdate)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "CSPRNGV2 nonce role counts must be between two and four";
            }
            return false;
        }

        const int aPlannedWordCount =
            3 +
            aSlice.mNonceCountOrbiterAssign +
            aSlice.mNonceCountOrbiterUpdate +
            aSlice.mNonceCountWandererUpdate;
        if (aPlannedWordCount > static_cast<int>(kNonceWordCount)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "CSPRNGV2 nonce plan exceeded the A-P word pool";
            }
            return false;
        }

        std::vector<int> aContextIndexes;
        for (const GAXSKStatement &aStatement :
             aSlice.mARXSkeleton.mStatements) {
            if (aStatement.mKind !=
                GAXSKStatementKind::kContextWordAssign) {
                continue;
            }
            for (const GAXSKInputSlot &aSlot :
                 aStatement.mContextWord.mSlots) {
                if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
                    continue;
                }
                const int aContextIndex = NonceKindIndex(aSlot.mNonceByte);
                if ((aContextIndex < 0) ||
                    (std::find(aContextIndexes.begin(),
                               aContextIndexes.end(),
                               aContextIndex) != aContextIndexes.end())) {
                    if (pErrorMessage != nullptr) {
                        *pErrorMessage =
                            "CSPRNGV2 found invalid context nonce slots";
                    }
                    return false;
                }
                aContextIndexes.push_back(aContextIndex);
            }
        }
        if (aContextIndexes.size() != 2U) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "CSPRNGV2 expected exactly two context nonce slots";
            }
            return false;
        }

        aSlice.mNonceBytes = pNonceWords;
        Random::Shuffle(&aSlice.mNonceBytes);

        std::array<bool, kNonceWordCount> aSelected = {};
        int aContextCount = 0;

        for (const GAXSKStatement &aStatement :
             aSlice.mARXSkeleton.mStatements) {
            if (aStatement.mKind !=
                GAXSKStatementKind::kContextWordAssign) {
                continue;
            }
            for (const GAXSKInputSlot &aSlot :
                 aStatement.mContextWord.mSlots) {
                if (aSlot.mKind != GAXSKInputSlotKind::kNonceByte) {
                    continue;
                }
                const int aMappedIndex = NonceKindIndex(aSlot.mNonceByte);
                if ((aMappedIndex < 0) ||
                    (static_cast<std::size_t>(aMappedIndex) >=
                     aSlice.mNonceBytes.size())) {
                    if (pErrorMessage != nullptr) {
                        *pErrorMessage =
                            "CSPRNGV2 could not resolve a context nonce";
                    }
                    return false;
                }
                const int aWordIndex =
                    SymbolIndex(pNonceWords,
                                aSlice.mNonceBytes[
                                    static_cast<std::size_t>(aMappedIndex)]);
                if (aWordIndex < 0) {
                    if (pErrorMessage != nullptr) {
                        *pErrorMessage =
                            "CSPRNGV2 could not identify a context nonce word";
                    }
                    return false;
                }
                if (!aSelected[static_cast<std::size_t>(aWordIndex)]) {
                    aSelected[static_cast<std::size_t>(aWordIndex)] = true;
                    aUsage[static_cast<std::size_t>(aWordIndex)] += 1;
                    aContextCount += 1;
                }
            }
        }

        if (aContextCount != 2) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage =
                    "CSPRNGV2 expected exactly two context nonce words";
            }
            return false;
        }

        auto Withdraw = [&]() -> GSymbol {
            int aLowestUsage = std::numeric_limits<int>::max();
            std::vector<int> aCandidates;
            for (std::size_t i = 0U;
                 i < kNonceWordCount;
                 ++i) {
                if (aSelected[i]) {
                    continue;
                }
                if (aUsage[i] < aLowestUsage) {
                    aLowestUsage = aUsage[i];
                    aCandidates.clear();
                }
                if (aUsage[i] == aLowestUsage) {
                    aCandidates.push_back(static_cast<int>(i));
                }
            }
            if (aCandidates.empty()) {
                return GSymbol();
            }
            const int aCandidateIndex =
                aCandidates[static_cast<std::size_t>(
                    Random::Get(static_cast<int>(aCandidates.size())))];
            aSelected[static_cast<std::size_t>(aCandidateIndex)] = true;
            aUsage[static_cast<std::size_t>(aCandidateIndex)] += 1;
            return pNonceWords[static_cast<std::size_t>(aCandidateIndex)];
        };

        aSlice.mNoncePlan.mScatter = Withdraw();
        for (int i = 0; i < aSlice.mNonceCountOrbiterAssign; ++i) {
            aSlice.mNoncePlan.mOrbiterAssign.push_back(Withdraw());
        }
        for (int i = 0; i < aSlice.mNonceCountOrbiterUpdate; ++i) {
            aSlice.mNoncePlan.mOrbiterUpdate.push_back(Withdraw());
        }
        for (int i = 0; i < aSlice.mNonceCountWandererUpdate; ++i) {
            aSlice.mNoncePlan.mWandererUpdate.push_back(Withdraw());
        }

        if (aSlice.mNoncePlan.mScatter.IsInvalid()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "CSPRNGV2 exhausted the nonce-word pool";
            }
            return false;
        }
    }

    return true;
}

} // namespace

bool CSPRNGV2::Bake(bool pIsNonKDF,
                    TwistDomain pDomain,
                    std::vector<CSPRNGV2Slice> &pSlices,
                    const std::vector<GSymbol> &pSaltsOrbiterAssign,
                    const std::vector<GSymbol> &pSaltsOrbiterUpdate,
                    const std::vector<GSymbol> &pSaltsWandererUpdate,
                    std::vector<GLoop> *pLoops,
                    bool pAutoRangeAdjust,
                    std::string *pErrorMessage) {
    
    if (pLoops == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "CSPRNGV2::Bake received null loop output";
        }
        return false;
    }
    
    if ((pSaltsOrbiterAssign.size() != kSaltLaneCount) ||
        (pSaltsOrbiterUpdate.size() != kSaltLaneCount) ||
        (pSaltsWandererUpdate.size() != kSaltLaneCount)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "CSPRNGV2::Bake requires exactly eight salts for every role";
        }
        return false;
    }
    
    GSymbol aIndex = GSymbol::Var(TwistVariable::kIndex);
    
    GSymbol aOrbiterA = GSymbol::Var(TwistVariable::kOrbiterA); GSymbol aOrbiterB = GSymbol::Var(TwistVariable::kOrbiterB);
    GSymbol aOrbiterC = GSymbol::Var(TwistVariable::kOrbiterC); GSymbol aOrbiterD = GSymbol::Var(TwistVariable::kOrbiterD);
    GSymbol aOrbiterE = GSymbol::Var(TwistVariable::kOrbiterE); GSymbol aOrbiterF = GSymbol::Var(TwistVariable::kOrbiterF);
    GSymbol aOrbiterG = GSymbol::Var(TwistVariable::kOrbiterG); GSymbol aOrbiterH = GSymbol::Var(TwistVariable::kOrbiterH);
    GSymbol aOrbiterI = GSymbol::Var(TwistVariable::kOrbiterI); GSymbol aOrbiterJ = GSymbol::Var(TwistVariable::kOrbiterJ);
    GSymbol aOrbiterK = GSymbol::Var(TwistVariable::kOrbiterK);
    
    std::vector<GSymbol> aNonceWords = {
        GSymbol::Var("aNonceWordA"),
        GSymbol::Var("aNonceWordB"),
        GSymbol::Var("aNonceWordC"),
        GSymbol::Var("aNonceWordD"),
        GSymbol::Var("aNonceWordE"),
        GSymbol::Var("aNonceWordF"),
        GSymbol::Var("aNonceWordG"),
        GSymbol::Var("aNonceWordH"),
        GSymbol::Var("aNonceWordI"),
        GSymbol::Var("aNonceWordJ"),
        GSymbol::Var("aNonceWordK"),
        GSymbol::Var("aNonceWordL"),
        GSymbol::Var("aNonceWordM"),
        GSymbol::Var("aNonceWordN"),
        GSymbol::Var("aNonceWordO"),
        GSymbol::Var("aNonceWordP"),
    };
    
    for (int aSliceIndex=0; aSliceIndex<pSlices.size(); aSliceIndex++) {
        if (!pSlices[aSliceIndex].mSaltsOrbiterAssign.empty() ||
            !pSlices[aSliceIndex].mSaltsOrbiterUpdate.empty() ||
            !pSlices[aSliceIndex].mSaltsWandererUpdate.empty()) {
            if (!FillSaltBag(pSlices[aSliceIndex].mSaltsOrbiterAssign,
                             pSlices[aSliceIndex].mSaltsOrbiterUpdate,
                             pSlices[aSliceIndex].mSaltsWandererUpdate,
                             &(pSlices[aSliceIndex].mSaltBag),
                             pErrorMessage)) {
                return false;
            }
        } else {
            if (!FillSaltBag(pSaltsOrbiterAssign,
                             pSaltsOrbiterUpdate,
                             pSaltsWandererUpdate,
                             &(pSlices[aSliceIndex].mSaltBag),
                             pErrorMessage)) {
                return false;
            }
        }
    }
    
    if (!PlanNonceWords(aNonceWords, &pSlices, pErrorMessage)) {
        return false;
    }

    for (int aSliceIndex=0; aSliceIndex<pSlices.size(); aSliceIndex++) {
        // GAXSK has already applied the saved per-loop role permutations.
        // Keep these symbol maps canonical so that no second, unreported
        // permutation is composed over the selected orbiter and wanderer maps.
        pSlices[aSliceIndex].mOrbiters = {
            aOrbiterA, aOrbiterB, aOrbiterC, aOrbiterD,
            aOrbiterE, aOrbiterF, aOrbiterG, aOrbiterH,
            aOrbiterI, aOrbiterJ, aOrbiterK,
        };

        pSlices[aSliceIndex].mWanderers = MakeCanonicalWanderers();
    }
    
    GAXPL *aPlan = new GAXPL();
    
    aPlan->mIsNonKDF = pIsNonKDF;
    aPlan->mDomain = pDomain;
    
    int aSliceCount = (int)pSlices.size();
    
    for (int aSliceIndex=0; aSliceIndex<pSlices.size(); aSliceIndex++) {
        
        //const
        CSPRNGV2Slice &aSlice = pSlices[aSliceIndex];
        aPlan->mDomain = (aSlice.mDomain == TwistDomain::kInvalid) ? pDomain : aSlice.mDomain;
        
        if (pAutoRangeAdjust == true) {
            int aCeiling = aSlice.mLoopCeiling;
            
            int aLo = (aSliceIndex * aCeiling) / aSliceCount;
            int aHi = ((aSliceIndex + 1) * aCeiling) / aSliceCount;
            
            aSlice.mSourceRangesLo = aLo;
            aSlice.mSourceRangesHi = aHi;
        }
        
        GLoop aLoop;
        aLoop.mLoopVariable = aIndex;
        aLoop.mLoopVariableName = aIndex.mName;
        aLoop.mLoopBegin = aSlice.mLoopBegin;
        aLoop.mLoopBeginText = aSlice.mLoopBeginText;
        aLoop.mLoopEndText = aSlice.mLoopEndText.empty() ? "S_BLOCK" : aSlice.mLoopEndText;
        aLoop.mLoopStep = 1;
        
        if (!aPlan->Bake(aSlice.mSourceRangesLo,
                         aSlice.mSourceRangesHi,
                         &aSlice.mARXSkeleton,
                         aSlice.mSaltBag,
                         aSlice.mNonceBytes,
                         aSlice.mNoncePlan,
                         aSlice.mSources,
                         aSlice.mOrbiters,
                         aSlice.mWanderers,
                         aSlice.mHotPack,
                         false,
                         aSlice.mDest,
                         aSlice.mDestWriteInverted,
                         &aLoop,
                         pErrorMessage)) {
            const char *aErrorText = (pErrorMessage != nullptr) ? pErrorMessage->c_str() : "unknown error";
            printf("GAXPL::Bake Error => %s\n", aErrorText);
            delete aPlan;
            return false;
        }
        
        pLoops->push_back(aLoop);
    }
    
    delete aPlan;
    return true;
    
}
