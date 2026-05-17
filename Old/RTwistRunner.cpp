//
//  RTwistRunner.cpp
//  MeanMachine
//

#include "RTwistRunner.hpp"

#include "FileIO.hpp"

#include <vector>

void TwistWorkSpaceBindExternalBuffers(std::uint8_t *pSource,
                                       std::uint8_t *pDest);

namespace {

void SetError(std::string *pError,
              const std::string &pMessage) {
    if (pError != nullptr) {
        *pError = pMessage;
    }
}

bool LoadTextFile(const std::string &pPath,
                  std::string *pText,
                  std::string *pError) {
    if (pText == nullptr) {
        SetError(pError, "Text output was null.");
        return false;
    }

    std::vector<std::uint8_t> aData;
    if (!FileIO::Load(pPath, aData)) {
        SetError(pError, "Failed to load file: " + pPath);
        return false;
    }

    pText->assign(aData.begin(), aData.end());
    return true;
}

bool SaveTextFile(const std::string &pPath,
                  const std::string &pText,
                  std::string *pError) {
    std::vector<std::uint8_t> aData(pText.begin(), pText.end());
    if (!FileIO::Save(pPath, aData)) {
        SetError(pError, "Failed to save file: " + pPath);
        return false;
    }
    return true;
}

} // namespace

bool RTwistRunner::LoadSeedBatchFromJsonText(const std::string &pJsonText,
                                             GBatch *pBatch,
                                             std::string *pError) {
    return GBatch::FromJson(pJsonText, pBatch, pError);
}

bool RTwistRunner::LoadSeedBatchFromJsonFile(const std::string &pPath,
                                             GBatch *pBatch,
                                             std::string *pError) {
    std::string aText;
    if (!LoadTextFile(pPath, &aText, pError)) {
        return false;
    }
    return LoadSeedBatchFromJsonText(aText, pBatch, pError);
}

bool RTwistRunner::ConfigureSeederFromJsonText(GTwistSeeder *pSeeder,
                                               const std::string &pJsonText,
                                               std::string *pError) {
    if (pSeeder == nullptr) {
        SetError(pError, "Seeder output was null.");
        return false;
    }

    GBatch aBatch;
    if (!LoadSeedBatchFromJsonText(pJsonText, &aBatch, pError)) {
        return false;
    }

    pSeeder->SetSeedBatch(aBatch);
    return true;
}

bool RTwistRunner::ConfigureSeederFromJsonFile(GTwistSeeder *pSeeder,
                                               const std::string &pPath,
                                               std::string *pError) {
    std::string aText;
    if (!LoadTextFile(pPath, &aText, pError)) {
        return false;
    }
    return ConfigureSeederFromJsonText(pSeeder, aText, pError);
}

bool RTwistRunner::SaveSeedBatchJsonFile(const GBatch &pBatch,
                                         const std::string &pPath,
                                         std::string *pError) {
    const std::string aJson = pBatch.ToJson(pError);
    if (aJson.empty()) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Batch JSON export was empty.";
        }
        return false;
    }
    return SaveTextFile(pPath, aJson, pError);
}

bool RTwistRunner::SaveSeederJsonFile(const GTwistSeeder &pSeeder,
                                      const std::string &pPath,
                                      std::string *pError) {
    return SaveSeedBatchJsonFile(pSeeder.GetSeedBatch(), pPath, pError);
}

bool RTwistRunner::SaveSeedBatchCppFile(const GBatch &pBatch,
                                        const std::string &pFunctionName,
                                        const std::string &pPath,
                                        std::string *pError) {
    const std::string aCpp = pBatch.BuildCpp(pFunctionName, pError);
    if (aCpp.empty()) {
        if ((pError != nullptr) && pError->empty()) {
            *pError = "Batch C++ export was empty.";
        }
        return false;
    }
    return SaveTextFile(pPath, aCpp, pError);
}

bool RTwistRunner::SaveSeederCppFile(const GTwistSeeder &pSeeder,
                                     const std::string &pFunctionName,
                                     const std::string &pPath,
                                     std::string *pError) {
    return SaveSeedBatchCppFile(pSeeder.GetSeedBatch(), pFunctionName, pPath, pError);
}

bool RTwistRunner::RunSeedBatch(const GBatch &pBatch,
                                TwistWorkSpace *pWorkspace,
                                std::uint8_t *pSource,
                                std::string *pError) {
    if (pWorkspace == nullptr) {
        SetError(pError, "Workspace was null.");
        return false;
    }
    if (pSource == nullptr) {
        SetError(pError, "Source buffer was null.");
        return false;
    }

    GTwistSeeder aSeeder;
    aSeeder.SetSeedBatch(pBatch);

    TwistWorkSpaceBindExternalBuffers(pSource, nullptr);
    aSeeder.CopyTablesToWorkspace(pWorkspace);

    return pBatch.Execute(pWorkspace, pError);
}
