//
//  GSeedWorkerBuilder.cpp
//  MeanMachine
//
//  Created by Dragon on 4/29/26.
//

#include "GSeedWorkerBuilder.hpp"

#include "Random.hpp"
#include "TwistCryptoGenerator.hpp"

#include <cctype>
#include <cstdlib>
#include <unordered_map>


bool                                    PlanPhaseA(std::string &pError);


namespace {

void SetError(std::string *pError,
              const std::string &pMessage) {
    if (pError != nullptr) {
        *pError = pMessage;
    }
}

void ConfigureLoop(GLoop *pLoop,
                   const GSymbol &pLoopIndex) {
    if (pLoop == nullptr) {
        return;
    }
    pLoop->mLoopVariable = pLoopIndex;
    pLoop->mLoopVariableName = pLoopIndex.IsVar() ? pLoopIndex.mName : "aLoopIndex";
    pLoop->mLoopBegin = 0;
    pLoop->mLoopEndText = "S_BLOCK";
    pLoop->mLoopStep = 1;
}

std::string TrimCopy(const std::string &pText) {
    std::size_t aBegin = 0U;
    while ((aBegin < pText.size()) &&
           (std::isspace(static_cast<unsigned char>(pText[aBegin])) != 0)) {
        aBegin += 1U;
    }

    std::size_t aEnd = pText.size();
    while ((aEnd > aBegin) &&
           (std::isspace(static_cast<unsigned char>(pText[aEnd - 1U])) != 0)) {
        aEnd -= 1U;
    }

    return pText.substr(aBegin, aEnd - aBegin);
}

bool ParseIntLiteral(std::string pValueText,
                     int *pValueOut) {
    if (pValueOut == nullptr) {
        return false;
    }

    pValueText = TrimCopy(pValueText);
    if (pValueText.empty()) {
        return false;
    }

    while (!pValueText.empty()) {
        const char aLast = pValueText.back();
        if ((aLast == 'u') || (aLast == 'U') ||
            (aLast == 'l') || (aLast == 'L')) {
            pValueText.pop_back();
            pValueText = TrimCopy(pValueText);
            continue;
        }
        break;
    }

    if (pValueText.empty()) {
        return false;
    }

    const char *aStart = pValueText.c_str();
    char *aEnd = nullptr;
    const long aValue = std::strtol(aStart, &aEnd, 0);
    if ((aEnd == nullptr) || (*aEnd != '\0')) {
        return false;
    }

    *pValueOut = static_cast<int>(aValue);
    return true;
}

bool ResolveAliasSlot(const std::string &pAlias,
                      TwistWorkSpaceSlot *pSlotOut) {
    if (pSlotOut == nullptr) {
        return false;
    }

    static const TwistWorkSpaceSlot kKnownSlots[] = {
        TwistWorkSpaceSlot::kSource,
        TwistWorkSpaceSlot::kDest,

        TwistWorkSpaceSlot::kSaltA,
        TwistWorkSpaceSlot::kSaltB,
        TwistWorkSpaceSlot::kSaltC,
        TwistWorkSpaceSlot::kSaltD,
        TwistWorkSpaceSlot::kDerivedSaltA,
        TwistWorkSpaceSlot::kDerivedSaltB,
        TwistWorkSpaceSlot::kDerivedSaltC,
        TwistWorkSpaceSlot::kDerivedSaltD,
        TwistWorkSpaceSlot::kDerivedSaltE,
        TwistWorkSpaceSlot::kDerivedSaltF,
        TwistWorkSpaceSlot::kDerivedSaltG,
        TwistWorkSpaceSlot::kDerivedSaltH,

        TwistWorkSpaceSlot::kSBoxA,
        TwistWorkSpaceSlot::kSBoxB,
        TwistWorkSpaceSlot::kSBoxC,
        TwistWorkSpaceSlot::kSBoxD,
        TwistWorkSpaceSlot::kDerivedSBoxA,
        TwistWorkSpaceSlot::kDerivedSBoxB,
        TwistWorkSpaceSlot::kDerivedSBoxC,
        TwistWorkSpaceSlot::kDerivedSBoxD,
        TwistWorkSpaceSlot::kDerivedSBoxE,
        TwistWorkSpaceSlot::kDerivedSBoxF,
        TwistWorkSpaceSlot::kDerivedSBoxG,
        TwistWorkSpaceSlot::kDerivedSBoxH,

        TwistWorkSpaceSlot::kSeedExpansionLaneA,
        TwistWorkSpaceSlot::kSeedExpansionLaneB,
        TwistWorkSpaceSlot::kSeedExpansionLaneC,
        TwistWorkSpaceSlot::kSeedExpansionLaneD,

        TwistWorkSpaceSlot::kWorkLaneA,
        TwistWorkSpaceSlot::kWorkLaneB,
        TwistWorkSpaceSlot::kWorkLaneC,
        TwistWorkSpaceSlot::kWorkLaneD,

        TwistWorkSpaceSlot::kOperationLaneA,
        TwistWorkSpaceSlot::kOperationLaneB,

        TwistWorkSpaceSlot::kMaskLaneA,
        TwistWorkSpaceSlot::kMaskLaneB,

        TwistWorkSpaceSlot::kKeyBoxUnrolledA,
        TwistWorkSpaceSlot::kKeyBoxUnrolledB,
        TwistWorkSpaceSlot::kKeyRowReadA,
        TwistWorkSpaceSlot::kKeyRowReadB,
        TwistWorkSpaceSlot::kKeyRowWriteA,
        TwistWorkSpaceSlot::kKeyRowWriteB,

        TwistWorkSpaceSlot::kMaskBoxUnrolledA,
        TwistWorkSpaceSlot::kMaskBoxUnrolledB,
        TwistWorkSpaceSlot::kMaskRowReadA,
        TwistWorkSpaceSlot::kMaskRowReadB,
        TwistWorkSpaceSlot::kMaskRowWriteA,
        TwistWorkSpaceSlot::kMaskRowWriteB
    };

    for (TwistWorkSpaceSlot aSlot : kKnownSlots) {
        if (BufAliasName(aSlot) == pAlias) {
            *pSlotOut = aSlot;
            return true;
        }
    }

    return false;
}

bool ParseCryptoMakeArguments(const std::string &pLine,
                              std::vector<std::string> *pArgsOut) {
    if (pArgsOut == nullptr) {
        return false;
    }

    std::string aLine = TrimCopy(pLine);
    if (aLine.empty()) {
        return false;
    }

    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimCopy(aLine);
    }

    const std::size_t aCallPos = aLine.find(".Make(");
    if (aCallPos == std::string::npos) {
        return false;
    }

    const std::size_t aOpen = aCallPos + 6U;
    const std::size_t aClose = aLine.rfind(')');
    if ((aClose == std::string::npos) || (aClose < aOpen)) {
        return false;
    }

    const std::string aArgsText = aLine.substr(aOpen, aClose - aOpen);
    std::vector<std::string> aArgs;

    std::size_t aCursor = 0U;
    while (aCursor < aArgsText.size()) {
        const std::size_t aComma = aArgsText.find(',', aCursor);
        std::string aToken = (aComma == std::string::npos)
            ? aArgsText.substr(aCursor)
            : aArgsText.substr(aCursor, aComma - aCursor);
        aToken = TrimCopy(aToken);
        if (!aToken.empty()) {
            aArgs.push_back(aToken);
        }
        if (aComma == std::string::npos) {
            break;
        }
        aCursor = aComma + 1U;
    }

    if (aArgs.empty()) {
        return false;
    }

    *pArgsOut = std::move(aArgs);
    return true;
}

bool ExecuteCryptoMakeLine(const std::string &pLine,
                           TwistWorkSpace *pWorkspace,
                           std::string *pError) {
    std::vector<std::string> aArgs;
    if (!ParseCryptoMakeArguments(pLine, &aArgs)) {
        return false;
    }

    if ((aArgs.size() != 5U) && (aArgs.size() != 9U)) {
        SetError(pError, "TwistCryptoGenerator::Make expects 5 or 9 arguments.");
        return false;
    }

    std::vector<std::uint8_t *> aBuffers;
    aBuffers.reserve(aArgs.size());
    for (const std::string &aAlias : aArgs) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveAliasSlot(aAlias, &aSlot)) {
            SetError(pError, "Unknown buffer alias in TwistCryptoGenerator::Make call: " + aAlias);
            return false;
        }

        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, aSlot);
        if (aBuffer == nullptr) {
            SetError(pError, "Resolved null buffer for alias: " + aAlias);
            return false;
        }
        aBuffers.push_back(aBuffer);
    }

    TwistCryptoGenerator aGenerator;
    if (aBuffers.size() == 5U) {
        aGenerator.Make(aBuffers[0],
                        aBuffers[1],
                        aBuffers[2],
                        aBuffers[3],
                        aBuffers[4]);
    } else {
        aGenerator.Make(aBuffers[0],
                        aBuffers[1],
                        aBuffers[2],
                        aBuffers[3],
                        aBuffers[4],
                        aBuffers[5],
                        aBuffers[6],
                        aBuffers[7],
                        aBuffers[8]);
    }

    return true;
}

void ApplyScalarAssignmentLine(const std::string &pRawLine,
                               std::unordered_map<std::string, int> *pVariables) {
    if (pVariables == nullptr) {
        return;
    }

    std::string aLine = pRawLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimCopy(aLine);
    if (aLine.empty()) {
        return;
    }

    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimCopy(aLine);
    }
    if (aLine.empty()) {
        return;
    }

    const std::size_t aEqual = aLine.find('=');
    if (aEqual == std::string::npos) {
        return;
    }

    std::string aLeft = TrimCopy(aLine.substr(0U, aEqual));
    std::string aRight = TrimCopy(aLine.substr(aEqual + 1U));
    if (aLeft.empty() || aRight.empty()) {
        return;
    }

    if ((aLeft.find('*') != std::string::npos) ||
        (aLeft.find('[') != std::string::npos) ||
        (aLeft.find('(') != std::string::npos) ||
        (aLeft.find(')') != std::string::npos)) {
        return;
    }

    const std::size_t aLastSpace = aLeft.find_last_of(" \t");
    const std::string aName = (aLastSpace == std::string::npos)
        ? aLeft
        : TrimCopy(aLeft.substr(aLastSpace + 1U));
    if (aName.empty()) {
        return;
    }

    int aValue = 0;
    if (!ParseIntLiteral(aRight, &aValue)) {
        return;
    }

    (*pVariables)[aName] = aValue;
}

} // namespace

GSeedWorkerBuilder::GSeedWorkerBuilder() {
    mLoopIndex = VarSymbol("aLoopIndex");
    mValue = VarSymbol("aValue");
    mCarry = VarSymbol("aCarry");
    mSource = BufSymbol(TwistWorkSpaceSlot::kSource);

    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxA));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxB));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxC));
    mListSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kSBoxD));

    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltA));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltB));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltC));
    mListSalts.push_back(BufSymbol(TwistWorkSpaceSlot::kSaltD));

    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxA));
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxB));
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxC));
    mListDerivedSBoxes.push_back(BufSymbol(TwistWorkSpaceSlot::kDerivedSBoxD));

    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneA));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneB));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneC));
    mListWorkers.push_back(BufSymbol(TwistWorkSpaceSlot::kWorkLaneD));
}

GSeedWorkerBuilder::~GSeedWorkerBuilder() {
}

GSymbol GSeedWorkerBuilder::BuildManagedMixSymbol(GSymbol pTarget) const {
    if (!pTarget.IsVar()) {
        return VarSymbol("aValueMix");
    }
    return VarSymbol(pTarget.mName + "Mix");
}

bool GSeedWorkerBuilder::BuildPhaseA(TwistProgramBranch &pBranch,
                                     std::string &pError) {
    pError.clear();
    pBranch.Clear();

    mWorkerA = mListWorkers[0];
    mWorkerB = mListWorkers[1];
    mWorkerC = mListWorkers[2];
    mWorkerD = mListWorkers[3];

    mSaltA = mListSalts[0];
    mSaltB = mListSalts[1];
    mSaltC = mListSalts[2];
    mSaltD = mListSalts[3];

    mSBoxA = mListSBoxes[0];
    mSBoxB = mListSBoxes[1];
    mSBoxC = mListSBoxes[2];
    mSBoxD = mListSBoxes[3];

    mDerivedSBoxA = mListDerivedSBoxes[0];
    mDerivedSBoxB = mListDerivedSBoxes[1];
    mDerivedSBoxC = mListDerivedSBoxes[2];
    mDerivedSBoxD = mListDerivedSBoxes[3];

    // tiny demo loop 1 (transform model):
    // aValueMix = (aValue + aCarry) ^ aSBoxA[aLoopIndex & 0xFFU];
    // aValue = TwistMix16::Mix161_004(aValueMix, aSBoxB);
    const GSymbol aValueMix = BuildManagedMixSymbol(mValue);

    GBatch aLoopBatchA;
    aLoopBatchA.mName = "seed_phase_a_loop_1";
    GLoop aLoopA;
    ConfigureLoop(&aLoopA, mLoopIndex);

    GLoopFragmentComposer aComposerA(mLoopIndex);
    aComposerA.ResetSetEqual(aValueMix);
    aComposerA.EnableDebugAddXor({ true, false }); // target, +carry, ^sbox
    aComposerA.MixVariable(mValue);
    aComposerA.MixVariable(mCarry);
    aComposerA.MixBuffer(mSBoxA)
        .Key(mLoopIndex)
        .Domain(GLoopFragmentDomain::kSBox)
        .Offset(0);

    if (!aComposerA.BakeStatements(&aLoopA.mBodyStatements, &pError)) {
        return false;
    }

    aLoopA.mBodyStatements.push_back(
        GStatement::Assign(
            GTarget::Symbol(mValue),
            GExpr::Mix161(GExpr::Symbol(aValueMix), Mix161Type::kMix161_004, mSBoxB)));

    aLoopBatchA.CommitLoop(aLoopA);
    pBranch.AddBatch(aLoopBatchA);

    // derive 4 s-boxes (shows up in exported C++ and executes in branch runtime)
    pBranch.AddLine("TwistCryptoGenerator aCryptoGenerator;");
    pBranch.AddLine("aCryptoGenerator.Make(aSource, aDerivedSBoxA, aDerivedSBoxB, aDerivedSBoxC, aDerivedSBoxD);");

    // tiny demo loop 2 (transform model):
    // aValueMix = aCarry ^ aValue;
    // aValue = TwistMix16::Mix161_005(aValueMix, aDerivedSBoxA);
    GBatch aLoopBatchB;
    aLoopBatchB.mName = "seed_phase_a_loop_2";
    GLoop aLoopB;
    ConfigureLoop(&aLoopB, mLoopIndex);

    GLoopFragmentComposer aComposerB(mLoopIndex);
    aComposerB.ResetSetEqual(aValueMix);
    aComposerB.EnableDebugAddXor({ false }); // target, ^value
    aComposerB.MixVariable(mCarry);
    aComposerB.MixVariable(mValue);

    if (!aComposerB.BakeStatements(&aLoopB.mBodyStatements, &pError)) {
        return false;
    }

    aLoopB.mBodyStatements.push_back(
        GStatement::Assign(
            GTarget::Symbol(mValue),
            GExpr::Mix161(GExpr::Symbol(aValueMix), Mix161Type::kMix161_005, mDerivedSBoxA)));

    aLoopBatchB.CommitLoop(aLoopB);
    pBranch.AddBatch(aLoopBatchB);

    return true;
}

bool GSeedWorkerBuilder::ExecuteBranch(TwistWorkSpace *pWorkspace,
                                       const TwistProgramBranch &pBranch,
                                       std::string &pError) {
    pError.clear();

    if (pWorkspace == nullptr) {
        pError = "GSeedWorkerBuilder::ExecuteBranch received a null workspace.";
        return false;
    }

    std::unordered_map<std::string, int> aVariables;

    auto ExecuteBatchByIndex = [&](const std::size_t pBatchIndex) -> bool {
        if (pBatchIndex >= pBranch.GetBatchJsonText().size()) {
            pError = "Branch batch step index was out of range.";
            return false;
        }

        const std::string &aBatchJson = pBranch.GetBatchJsonText()[pBatchIndex];
        GBatch aBatch;
        if (!GBatch::FromJson(aBatchJson, &aBatch, &pError)) {
            if (pError.empty()) {
                pError = "Failed to parse branch batch JSON in ExecuteBranch.";
            }
            return false;
        }

        if (!aBatch.ExecuteWithVariables(pWorkspace, &aVariables, &pError)) {
            if (pError.empty()) {
                pError = "Failed to execute branch batch.";
            }
            return false;
        }
        return true;
    };

    const std::vector<TwistProgramBranchStep> &aSteps = pBranch.GetSteps();
    if (aSteps.empty()) {
        for (const std::string &aLine : pBranch.GetStringLines()) {
            std::string aLineError;
            const bool aExecutedCrypto = ExecuteCryptoMakeLine(aLine, pWorkspace, &aLineError);
            if (!aLineError.empty()) {
                pError = "GSeedWorkerBuilder branch line failed: " + aLineError;
                return false;
            }

            if (aExecutedCrypto) {
                continue;
            }

            ApplyScalarAssignmentLine(aLine, &aVariables);
        }

        for (std::size_t aBatchIndex = 0U; aBatchIndex < pBranch.GetBatchJsonText().size(); ++aBatchIndex) {
            if (!ExecuteBatchByIndex(aBatchIndex)) {
                return false;
            }
        }
        return true;
    }

    for (const TwistProgramBranchStep &aStep : aSteps) {
        if (aStep.mType == TwistProgramBranchStepType::kLine) {
            if (aStep.mIndex >= pBranch.GetStringLines().size()) {
                pError = "Branch line step index was out of range.";
                return false;
            }

            const std::string &aLine = pBranch.GetStringLines()[aStep.mIndex];
            std::string aLineError;
            const bool aExecutedCrypto = ExecuteCryptoMakeLine(aLine, pWorkspace, &aLineError);
            if (!aLineError.empty()) {
                pError = "GSeedWorkerBuilder branch line failed: " + aLineError;
                return false;
            }

            if (!aExecutedCrypto) {
                ApplyScalarAssignmentLine(aLine, &aVariables);
            }
            continue;
        }

        if (aStep.mType == TwistProgramBranchStepType::kBatch) {
            if (!ExecuteBatchByIndex(aStep.mIndex)) {
                return false;
            }
            continue;
        }

        pError = "Branch step type was invalid.";
        return false;
    }

    return true;
}
