//
//  RTwistRunner.cpp
//  MeanMachine
//

#include "RTwistRunner.hpp"

#include "FileIO.hpp"

#include <cstring>
#include <vector>

namespace {

void SetError(std::string *pError,
              const std::string &pMessage) {
    if (pError != NULL) {
        *pError = pMessage;
    }
}

bool LoadTextFile(const std::string &pPath,
                  std::string *pText,
                  std::string *pError) {
    if (pText == NULL) {
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

void CopySeederTablesToWorkspace(const TwistSeeder &pSeeder,
                                 TwistWorkSpace *pWorkspace) {
    if (pWorkspace == NULL) {
        return;
    }

    std::memcpy(pWorkspace->mSBoxA, pSeeder.mSBoxA, S_SBOX);
    std::memcpy(pWorkspace->mSBoxB, pSeeder.mSBoxB, S_SBOX);
    std::memcpy(pWorkspace->mSBoxC, pSeeder.mSBoxC, S_SBOX);
    std::memcpy(pWorkspace->mSBoxD, pSeeder.mSBoxD, S_SBOX);

    std::memcpy(pWorkspace->mSaltA, pSeeder.mSaltA, S_SALT);
    std::memcpy(pWorkspace->mSaltB, pSeeder.mSaltB, S_SALT);
    std::memcpy(pWorkspace->mSaltC, pSeeder.mSaltC, S_SALT);
    std::memcpy(pWorkspace->mSaltD, pSeeder.mSaltD, S_SALT);
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

bool RTwistRunner::ConfigureSeederFromJsonText(TwistSeeder *pSeeder,
                                               const std::string &pJsonText,
                                               std::string *pError) {
    if (pSeeder == NULL) {
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

bool RTwistRunner::ConfigureSeederFromJsonFile(TwistSeeder *pSeeder,
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
        if ((pError != NULL) && pError->empty()) {
            *pError = "Batch JSON export was empty.";
        }
        return false;
    }
    return SaveTextFile(pPath, aJson, pError);
}

bool RTwistRunner::SaveSeederJsonFile(const TwistSeeder &pSeeder,
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
        if ((pError != NULL) && pError->empty()) {
            *pError = "Batch C++ export was empty.";
        }
        return false;
    }
    return SaveTextFile(pPath, aCpp, pError);
}

bool RTwistRunner::SaveSeederCppFile(const TwistSeeder &pSeeder,
                                     const std::string &pFunctionName,
                                     const std::string &pPath,
                                     std::string *pError) {
    return SaveSeedBatchCppFile(pSeeder.GetSeedBatch(), pFunctionName, pPath, pError);
}

bool RTwistRunner::RunSeedBatch(const GBatch &pBatch,
                                TwistWorkSpace *pWorkspace,
                                std::uint8_t *pSource,
                                std::string *pError) {
    if (pWorkspace == NULL) {
        SetError(pError, "Workspace was null.");
        return false;
    }
    if (pSource == NULL) {
        SetError(pError, "Source buffer was null.");
        return false;
    }

    TwistSeeder aSeeder;
    aSeeder.SetSeedBatch(pBatch);

    pWorkspace->mSource = pSource;
    CopySeederTablesToWorkspace(aSeeder, pWorkspace);

    return pBatch.Execute(pWorkspace, pError);
}
