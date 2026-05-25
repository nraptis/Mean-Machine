//
//  GRunMaskBraidDiffusion.cpp
//  MeanMachine
//
//  Created by nicholas on 5/25/26.
//

#include "GRunMaskBraidDiffusion.hpp"

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
    SetError(pErrorMessage, std::string("GRunMaskBraidDiffusion expected buffer symbol for ") + pLabel + ".");
    return false;
}

} // namespace

bool GRunMaskBraidDiffusion::Bake(const GRunMaskBraidDiffusionConfig &pConfig,
                                  GBatch *pBatch,
                                  std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    if (pBatch == nullptr) {
        SetError(pErrorMessage, "GRunMaskBraidDiffusion requires a batch output.");
        return false;
    }

    if (!EnsureBufferSymbol(pConfig.mInputA, "input_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mInputB, "input_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mMaskLane, "mask_lane", pErrorMessage)) { return false; }

    GSymbol aMaskDomainWord = pConfig.mMaskDomainWord;
    if (aMaskDomainWord.IsInvalid()) {
        aMaskDomainWord = GSymbol::Var(TwistVariable::kDomainWordMaskMutateA);
    }

    GMasking aMasking;
    std::vector<GStatement> aStatements;
    if (!aMasking.BakeBraid(pConfig.mBraidType,
                            pConfig.mInputA,
                            pConfig.mInputB,
                            pConfig.mMaskLane,
                            aMaskDomainWord,
                            &aStatements,
                            pErrorMessage)) {
        return false;
    }

    pBatch->CommitStatements(&aStatements);
    return true;
}
