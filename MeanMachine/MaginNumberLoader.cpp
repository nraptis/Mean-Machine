//
//  MaginNumberLoader.cpp
//  Soccer
//
//  Created by Codex on 7/9/26.
//

#include "MaginNumberLoader.hpp"

#include "FileIO.hpp"
#include "Library - G/GMagicNumbers.hpp"

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

namespace {

std::uint64_t ReadU64(const std::vector<std::uint8_t> &pBytes,
                      std::size_t pIndex) {
    return static_cast<std::uint64_t>(pBytes[pIndex]) |
    (static_cast<std::uint64_t>(pBytes[pIndex + 1U]) << 8) |
    (static_cast<std::uint64_t>(pBytes[pIndex + 2U]) << 16) |
    (static_cast<std::uint64_t>(pBytes[pIndex + 3U]) << 24) |
    (static_cast<std::uint64_t>(pBytes[pIndex + 4U]) << 32) |
    (static_cast<std::uint64_t>(pBytes[pIndex + 5U]) << 40) |
    (static_cast<std::uint64_t>(pBytes[pIndex + 6U]) << 48) |
    (static_cast<std::uint64_t>(pBytes[pIndex + 7U]) << 56);
}

void PrintHotPair(int pPairIndex,
                  std::uint64_t pAdd,
                  std::uint64_t pMul) {
    std::printf("Pair %3d: 0x%016llx 0x%016llx\n",
                pPairIndex,
                static_cast<unsigned long long>(pAdd),
                static_cast<unsigned long long>(pMul));
}

bool ParseFile(const std::string &pPath,
               int *pPackIndex,
               std::vector<GHotPack> *pHotPacks,
               std::string *pErrorMessage) {
    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes)) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "MaginNumberLoader failed to load " + pPath;
        }
        return false;
    }
    
    std::size_t aIndex = 0U;
    int aPairIndex = 1;
    GHotPack aPack{};
    
    while (aIndex < aBytes.size()) {
        if ((aIndex + 16U) > aBytes.size()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "MaginNumberLoader found a truncated pair in " + pPath;
            }
            return false;
        }
        
        const GHotPair aPair{ReadU64(aBytes, aIndex),
                             ReadU64(aBytes, aIndex + 8U)};
        
        //PrintHotPair(aPairIndex, aPair.mAdd, aPair.mMul);
        
        if (aPairIndex > G_HOT_PACK_SIZE) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "MaginNumberLoader found too many pairs in a pack in " + pPath;
            }
            return false;
        }
        aPack.mPair[static_cast<std::size_t>(aPairIndex - 1)] = aPair;
        aIndex += 16U;
        aPairIndex += 1;
        
        if ((aIndex < aBytes.size()) && (aBytes[aIndex] == static_cast<std::uint8_t>('_'))) {
            aIndex += 1U;
            if ((aIndex + 16U) > aBytes.size()) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "MaginNumberLoader found a truncated paired record in " + pPath;
                }
                return false;
            }
            
            const GHotPair aPairedPair{ReadU64(aBytes, aIndex),
                                       ReadU64(aBytes, aIndex + 8U)};
            
            //PrintHotPair(aPairIndex, aPairedPair.mAdd, aPairedPair.mMul);
            
            if (aPairIndex > G_HOT_PACK_SIZE) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "MaginNumberLoader found too many pairs in a pack in " + pPath;
                }
                return false;
            }
            aPack.mPair[static_cast<std::size_t>(aPairIndex - 1)] = aPairedPair;
            aIndex += 16U;
            aPairIndex += 1;
        }
        
        if (aIndex >= aBytes.size()) {
            break;
        }
        
        const std::uint8_t aTerminator = aBytes[aIndex++];
        if (aTerminator == static_cast<std::uint8_t>('@')) {
            if (aPairIndex != (G_HOT_PACK_SIZE + 1)) {
                if (pErrorMessage != nullptr) {
                    *pErrorMessage = "MaginNumberLoader found an incomplete pack in " + pPath;
                }
                return false;
            }
            pHotPacks->push_back(aPack);
            aPack = {};
            if ((aIndex < aBytes.size()) && (aBytes[aIndex] == static_cast<std::uint8_t>('\n'))) {
                aIndex += 1U;
            }
            
            //std::printf("========\n");
            
            *pPackIndex += 1;
            aPairIndex = 1;
            
            /*
            if (aIndex < aBytes.size()) {
                std::printf("========\n");
                std::printf("Pack #%d\n", *pPackIndex);
            }
            */
            continue;
        }
        
        if (aTerminator != static_cast<std::uint8_t>('$')) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "MaginNumberLoader found a bad record terminator in " + pPath;
            }
            return false;
        }
        
        if ((aIndex < aBytes.size()) && (aBytes[aIndex] == static_cast<std::uint8_t>('\n'))) {
            aIndex += 1U;
        }
    }
    
    if (aPairIndex != 1) {
        if (aPairIndex != (G_HOT_PACK_SIZE + 1)) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "MaginNumberLoader found an incomplete final pack in " + pPath;
            }
            return false;
        }
        pHotPacks->push_back(aPack);
        *pPackIndex += 1;
    }

    return true;
}

} // namespace

bool MaginNumberLoader::Load(const std::string &pOutputFolder,
                             std::vector<GHotPack> &pHotPacks,
                             std::string *pErrorMessage) {
    pHotPacks.clear();
    if (pOutputFolder.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "MaginNumberLoader output folder was empty.";
        }
        return false;
    }
    
    const std::string aRootPath = FileIO::ProjectRoot(pOutputFolder);
    const std::vector<std::string> aFiles = FileIO::GetAllFiles(aRootPath);
    if (aFiles.empty()) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "MaginNumberLoader found no files in " + aRootPath;
        }
        return false;
    }
    
    int aPackIndex = 0;
    for (const std::string &aFile : aFiles) {
        if (ParseFile(aFile, &aPackIndex, &pHotPacks, pErrorMessage)) {
            printf("Loaded hot pack file {%s}, now have %zu packs!\n", aFile.c_str(), pHotPacks.size());
            
        } else {
            pHotPacks.clear();
            return false;
        }
    }
    
    return true;
}
