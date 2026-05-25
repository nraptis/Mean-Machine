//
//  GRunMaskWeaveDiffusion.cpp
//  MeanMachine
//

#include "GRunMaskWeaveDiffusion.hpp"

namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

bool EnsureBufferSymbol(const GSymbol &pSymbol,
                        const char *pLabel,
                        std::string *pErrorMessage) {
    if (pSymbol.IsBuf()) {
        return true;
    }
    SetError(pErrorMessage, std::string("GRunMaskWeaveDiffusion expected buffer symbol for ") + pLabel + ".");
    return false;
}

} // namespace

bool GRunMaskWeaveDiffusion::Bake(const GRunMaskWeaveDiffusionConfig &pConfig,
                                  GBatch *pBatch,
                                  std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    if (pBatch == nullptr) {
        SetError(pErrorMessage, "GRunMaskWeaveDiffusion requires a batch output.");
        return false;
    }

    if (!EnsureBufferSymbol(pConfig.mInputA, "input_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mInputB, "input_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOutput, "output", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mMaskLane, "mask_lane", pErrorMessage)) { return false; }

    GSymbol aMaskDomainWord = pConfig.mMaskDomainWord;
    if (aMaskDomainWord.IsInvalid()) {
        aMaskDomainWord = GSymbol::Var(TwistVariable::kDomainWordMaskMutateA);
    }

    GMasking aMasking;
    std::vector<GStatement> aStatements;
    if (!aMasking.BakeWeave(pConfig.mWeaveType,
                            pConfig.mInputA,
                            pConfig.mInputB,
                            pConfig.mOutput,
                            pConfig.mMaskLane,
                            aMaskDomainWord,
                            &aStatements,
                            pErrorMessage)) {
        return false;
    }

    pBatch->CommitStatements(&aStatements);
    return true;
}
