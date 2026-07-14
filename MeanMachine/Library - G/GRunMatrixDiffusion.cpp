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
    if (!EnsureBufferSymbol(pConfig.mOutputA, "output_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOutputB, "output_b", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyA, "shuffle_entropy_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mShuffleEntropyB, "shuffle_entropy_b", pErrorMessage)) { return false; }
    
    if (!EnsureBufferSymbol(pConfig.mOperationSourceA, "operation_source_a", pErrorMessage)) { return false; }
    if (!EnsureBufferSymbol(pConfig.mOperationSourceB, "operation_source_b", pErrorMessage)) { return false; }

    std::ostringstream aReadLanes;
    aReadLanes << BufName(pConfig.mInputA) << ", "
               << BufName(pConfig.mInputB) << ", "
               << BufName(pConfig.mShuffleEntropyA) << ", "
               << BufName(pConfig.mShuffleEntropyB) << ", "
               << BufName(pConfig.mOperationSourceA) << ", "
               << BufName(pConfig.mOperationSourceB);

    std::ostringstream aWriteLanes;
    aWriteLanes << BufName(pConfig.mOutputA) << ", "
                << BufName(pConfig.mOutputB);
    GPrintTool::AddDiffusion(aReadLanes.str().c_str(),
                             aWriteLanes.str().c_str());
    
    const GSymbol aIndexListA = BufSymbol(TwistWorkSpaceSlot::kIndexList256A);
    const GSymbol aIndexListB = BufSymbol(TwistWorkSpaceSlot::kIndexList256B);
    const GSymbol aIndexListC = BufSymbol(TwistWorkSpaceSlot::kIndexList256C);
    const GSymbol aIndexListD = BufSymbol(TwistWorkSpaceSlot::kIndexList256D);

    std::vector<GStatement> aStatements;

    std::ostringstream aCall;
    aCall << "TwistDiffuse::";
    if (pConfig.mUseDomainWords) {
        aCall << "DiffuseWithDomainWords(";
    } else {
        aCall << "Diffuse(";
    }
    aCall << BufAliasName(pConfig.mInputA) << ", "
          << BufAliasName(pConfig.mInputB) << ",  // input lanes\n"
          << "                     "
          << BufAliasName(pConfig.mOutputA) << ", "
          << BufAliasName(pConfig.mOutputB) << ", // output lanes\n"
          << "                     "
          << BufAliasName(pConfig.mShuffleEntropyA) << ", "
          << BufAliasName(pConfig.mShuffleEntropyB) << ", // index shuffle seeds\n"
          << "                     "
          << BufAliasName(pConfig.mOperationSourceA) << ", "
          << BufAliasName(pConfig.mOperationSourceB) << ", // operation seeds\n"
          << "                     "
          << BufAliasName(aIndexListA) << ", "
          << BufAliasName(aIndexListB) << ", "
          << BufAliasName(aIndexListC) << ", "
          << BufAliasName(aIndexListD) << ",\n"
          << "                     &mMatrix";
    if (pConfig.mUseDomainWords) {
        aCall << ",\n"
              << "                     "
              << GSymbol::Var(TwistVariable::kDomainWordMatrixSelectA).mName << ", "
              << GSymbol::Var(TwistVariable::kDomainWordMatrixSelectB).mName << ", "
              << "// matrix select\n"
              << "                     "
              << GSymbol::Var(TwistVariable::kDomainWordMatrixUnrollA).mName << ", "
              << GSymbol::Var(TwistVariable::kDomainWordMatrixUnrollB).mName << ", "
              << "// matrix unroll\n"
              << "                     "
              << GSymbol::Var(TwistVariable::kDomainWordMatrixArgA).mName << ", "
              << GSymbol::Var(TwistVariable::kDomainWordMatrixArgB).mName << ", "
              << GSymbol::Var(TwistVariable::kDomainWordMatrixArgC).mName << ", "
              << GSymbol::Var(TwistVariable::kDomainWordMatrixArgD).mName
              << "); // matrix args";
    } else {
        aCall << ");";
    }
    aStatements.push_back(GStatement::RawLine(aCall.str()));
    pBatch->CommitStatements(&aStatements);
    return true;
}
