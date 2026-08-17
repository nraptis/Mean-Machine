//
//  GRunMatrixDiffusion.cpp
//  MeanMachine
//
//  Created by Dragon on 5/15/26.
//

#include "GRunMatrixDiffusion.hpp"
#include "GPrintTool.hpp"

#include <sstream>
#include <vector>

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
    SetError(pErrorMessage, std::string("GRunMatrixDiffusion expected buffer symbol for ") + pLabel + ".");
    return false;
}

}

bool GRunMatrixDiffusion::Bake(const GRunMatrixDiffusionConfig &pConfig,
                               GBatch *pBatch,
                               std::string *pErrorMessage) {
    if (pErrorMessage != nullptr) {
        pErrorMessage->clear();
    }
    if (pBatch == nullptr) {
        SetError(pErrorMessage, "GRunMatrixDiffusion requires a batch output.");
        return false;
    }
    if (!EnsureBufferSymbol(pConfig.mInputA, "input_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mInputB, "input_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mInputC, "input_c", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mInputD, "input_d", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOutputA, "output_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOutputB, "output_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOutputC, "output_c", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOutputD, "output_d", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mEntropyA, "entropy_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mEntropyB, "entropy_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mEntropyC, "entropy_c", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mEntropyD, "entropy_d", pErrorMessage)) { return false; }
    pBatch->mExportsAsBlock = false;

    std::ostringstream aReadLanes;
    aReadLanes << BufName(pConfig.mInputA) << ", "
               << BufName(pConfig.mInputB) << ", "
               << BufName(pConfig.mInputC) << ", "
               << BufName(pConfig.mInputD) << ", "
               << BufName(pConfig.mEntropyA) << ", "
               << BufName(pConfig.mEntropyB) << ", "
               << BufName(pConfig.mEntropyC) << ", "
               << BufName(pConfig.mEntropyD);

    std::ostringstream aWriteLanes;
    aWriteLanes << BufName(pConfig.mOutputA) << ", "
                << BufName(pConfig.mOutputB) << ", "
                << BufName(pConfig.mOutputC) << ", "
                << BufName(pConfig.mOutputD);
    GPrintTool::AddDiffusion(aReadLanes.str().c_str(),
                             aWriteLanes.str().c_str());
    
    const GSymbol aIndexListA = BufSymbol(TwistWorkSpaceSlot::kIndexList256A);
    const GSymbol aIndexListB = BufSymbol(TwistWorkSpaceSlot::kIndexList256B);
    const GSymbol aIndexListC = BufSymbol(TwistWorkSpaceSlot::kIndexList256C);
    const GSymbol aIndexListD = BufSymbol(TwistWorkSpaceSlot::kIndexList256D);

    std::vector<GStatement> aStatements;

    std::ostringstream aCall;
    aCall << "TwistDiffuse::DiffuseWithDomainWords(\n"
          << "        "
          << BufAliasName(pConfig.mEntropyA) << ", "
          << BufAliasName(pConfig.mEntropyB) << ", "
          << BufAliasName(pConfig.mEntropyC) << ", "
          << BufAliasName(pConfig.mEntropyD) << ", // entropy lanes\n"
          << "        "
          << BufAliasName(pConfig.mInputA) << ", "
          << BufAliasName(pConfig.mInputB) << ", "
          << BufAliasName(pConfig.mInputC) << ", "
          << BufAliasName(pConfig.mInputD) << ",  // input lanes\n"
          << "        "
          << BufAliasName(pConfig.mOutputA) << ", "
          << BufAliasName(pConfig.mOutputB) << ", "
          << BufAliasName(pConfig.mOutputC) << ", "
          << BufAliasName(pConfig.mOutputD) << ", // output lanes\n"
          << "        "
          << BufAliasName(aIndexListA) << ", "
          << BufAliasName(aIndexListB) << ", "
          << BufAliasName(aIndexListC) << ", "
          << BufAliasName(aIndexListD) << ",\n"
          << "        &mMatrix,\n"
          << "        "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixSelectA).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixSelectB).mName << ",\n"
          << "        "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixUnrollA).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixUnrollB).mName << ",\n"
          << "        "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixArgA).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixArgB).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixArgC).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixArgD).mName
          << ");";
    aStatements.push_back(GStatement::RawLine(aCall.str()));
    pBatch->CommitStatements(&aStatements);
    return true;
}
