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
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyA, "shuffle_entropy_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyB, "shuffle_entropy_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyC, "shuffle_entropy_c", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyD, "shuffle_entropy_d", pErrorMessage)) { return false; }
    
    if (!EnsureBufferSymbol(pConfig.mOperationSourceA, "operation_source_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOperationSourceB, "operation_source_b", pErrorMessage)) { return false; }
    pBatch->mExportsAsBlock = false;

    std::ostringstream aReadLanes;
    aReadLanes << BufName(pConfig.mInputA) << ", "
               << BufName(pConfig.mInputB) << ", "
               << BufName(pConfig.mInputC) << ", "
               << BufName(pConfig.mInputD) << ", "
               << BufName(pConfig.mShuffleEntropyA) << ", "
               << BufName(pConfig.mShuffleEntropyB) << ", "
               << BufName(pConfig.mShuffleEntropyC) << ", "
               << BufName(pConfig.mShuffleEntropyD) << ", "
               << BufName(pConfig.mOperationSourceA) << ", "
               << BufName(pConfig.mOperationSourceB);

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
          << BufAliasName(pConfig.mShuffleEntropyA) << ", "
          << BufAliasName(pConfig.mShuffleEntropyB) << ", "
          << BufAliasName(pConfig.mShuffleEntropyC) << ", "
          << BufAliasName(pConfig.mShuffleEntropyD) << ", // index shuffle seeds\n"
          << "        "
          << BufAliasName(pConfig.mOperationSourceA) << ", "
          << BufAliasName(pConfig.mOperationSourceB) << ", // operation seeds\n"
          << "        "
          << BufAliasName(aIndexListA) << ", "
          << BufAliasName(aIndexListB) << ", "
          << BufAliasName(aIndexListC) << ", "
          << BufAliasName(aIndexListD) << ", "
          << "&mMatrix, "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixSelectA).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixSelectB).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixUnrollA).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixUnrollB).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixArgA).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixArgB).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixArgC).mName << ", "
          << GSymbol::Var(TwistVariable::kDomainWordMatrixArgD).mName
          << ");";
    aStatements.push_back(GStatement::RawLine(aCall.str()));
    pBatch->CommitStatements(&aStatements);
    return true;
}
