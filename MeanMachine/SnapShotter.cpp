//
//  SnapShotter.cpp
//  MeanMachine
//
//  Created by icarus black on 6/28/26.
//

#include "SnapShotter.hpp"
#include "FileIO.hpp"

#include <cctype>
#include <cstring>
#include <sstream>

namespace {

constexpr std::size_t kSnapShotterReserveCount = 64U;

std::vector<SnapShotterSlice> &KDFAStorage() {
    static std::vector<SnapShotterSlice> aStorage;
    return aStorage;
}

std::vector<SnapShotterSlice> &KDFBStorage() {
    static std::vector<SnapShotterSlice> aStorage;
    return aStorage;
}

std::vector<SnapShotterSlice> &SEEDStorage() {
    static std::vector<SnapShotterSlice> aStorage;
    return aStorage;
}

std::vector<SnapShotterSlice> &TWISTStorage() {
    static std::vector<SnapShotterSlice> aStorage;
    return aStorage;
}

void CopyBytes(void *pDestination,
               const void *pSource,
               const std::size_t pByteCount) {
    std::memcpy(pDestination, pSource, pByteCount);
}

void CaptureSlice(std::vector<SnapShotterSlice> *pSlices,
                  TwistWorkSpace *pWorkSpace,
                  TwistExpander *pExpander,
                  const std::string &pName) {
    if ((pSlices == nullptr) || (pWorkSpace == nullptr) || (pExpander == nullptr)) {
        return;
    }
    
    pSlices->emplace_back();
    SnapShotterSlice &aSlice = pSlices->back();
    
    aSlice.mName = pName;
    
    CopyBytes(aSlice.mKeyBoxA, pWorkSpace->mKeyBoxA, sizeof(aSlice.mKeyBoxA));
    CopyBytes(aSlice.mKeyBoxB, pWorkSpace->mKeyBoxB, sizeof(aSlice.mKeyBoxB));
    
    CopyBytes(aSlice.mSource, pWorkSpace->mSource, sizeof(aSlice.mSource));
    
    CopyBytes(aSlice.mExpansionLaneA, pWorkSpace->mExpansionLaneA, sizeof(aSlice.mExpansionLaneA));
    CopyBytes(aSlice.mExpansionLaneB, pWorkSpace->mExpansionLaneB, sizeof(aSlice.mExpansionLaneB));
    CopyBytes(aSlice.mExpansionLaneC, pWorkSpace->mExpansionLaneC, sizeof(aSlice.mExpansionLaneC));
    CopyBytes(aSlice.mExpansionLaneD, pWorkSpace->mExpansionLaneD, sizeof(aSlice.mExpansionLaneD));
    
    CopyBytes(aSlice.mWorkLaneA, pWorkSpace->mWorkLaneA, sizeof(aSlice.mWorkLaneA));
    CopyBytes(aSlice.mWorkLaneB, pWorkSpace->mWorkLaneB, sizeof(aSlice.mWorkLaneB));
    CopyBytes(aSlice.mWorkLaneC, pWorkSpace->mWorkLaneC, sizeof(aSlice.mWorkLaneC));
    CopyBytes(aSlice.mWorkLaneD, pWorkSpace->mWorkLaneD, sizeof(aSlice.mWorkLaneD));
    
    CopyBytes(aSlice.mOperationLaneA, pWorkSpace->mOperationLaneA, sizeof(aSlice.mOperationLaneA));
    CopyBytes(aSlice.mOperationLaneB, pWorkSpace->mOperationLaneB, sizeof(aSlice.mOperationLaneB));
    CopyBytes(aSlice.mOperationLaneC, pWorkSpace->mOperationLaneC, sizeof(aSlice.mOperationLaneC));
    CopyBytes(aSlice.mOperationLaneD, pWorkSpace->mOperationLaneD, sizeof(aSlice.mOperationLaneD));
    
    CopyBytes(aSlice.mSnowLaneA, pWorkSpace->mSnowLaneA, sizeof(aSlice.mSnowLaneA));
    CopyBytes(aSlice.mSnowLaneB, pWorkSpace->mSnowLaneB, sizeof(aSlice.mSnowLaneB));
    CopyBytes(aSlice.mSnowLaneC, pWorkSpace->mSnowLaneC, sizeof(aSlice.mSnowLaneC));
    CopyBytes(aSlice.mSnowLaneD, pWorkSpace->mSnowLaneD, sizeof(aSlice.mSnowLaneD));
    
    CopyBytes(aSlice.mFireLaneA, pWorkSpace->mFireLaneA, sizeof(aSlice.mFireLaneA));
    CopyBytes(aSlice.mFireLaneB, pWorkSpace->mFireLaneB, sizeof(aSlice.mFireLaneB));
    CopyBytes(aSlice.mFireLaneC, pWorkSpace->mFireLaneC, sizeof(aSlice.mFireLaneC));
    CopyBytes(aSlice.mFireLaneD, pWorkSpace->mFireLaneD, sizeof(aSlice.mFireLaneD));
    
    CopyBytes(aSlice.mInvestLaneA, pWorkSpace->mInvestLaneA, sizeof(aSlice.mInvestLaneA));
    CopyBytes(aSlice.mInvestLaneB, pWorkSpace->mInvestLaneB, sizeof(aSlice.mInvestLaneB));
    CopyBytes(aSlice.mInvestLaneC, pWorkSpace->mInvestLaneC, sizeof(aSlice.mInvestLaneC));
    CopyBytes(aSlice.mInvestLaneD, pWorkSpace->mInvestLaneD, sizeof(aSlice.mInvestLaneD));
    
    CopyBytes(aSlice.mInvestLaneE, pWorkSpace->mInvestLaneE, sizeof(aSlice.mInvestLaneE));
    CopyBytes(aSlice.mInvestLaneF, pWorkSpace->mInvestLaneF, sizeof(aSlice.mInvestLaneF));
    CopyBytes(aSlice.mInvestLaneG, pWorkSpace->mInvestLaneG, sizeof(aSlice.mInvestLaneG));
    CopyBytes(aSlice.mInvestLaneH, pWorkSpace->mInvestLaneH, sizeof(aSlice.mInvestLaneH));
    
    aSlice.mDomainBundle = pWorkSpace->mDomainBundle;
    aSlice.mDomainBundleInbuilt = pExpander->mDomainBundleInbuilt;
    aSlice.mDomainBundleEphemeral = pExpander->mDomainBundleEphemeral;
}

void StartSlices(std::vector<SnapShotterSlice> *pSlices,
                 TwistWorkSpace *pWorkSpace,
                 TwistExpander *pExpander) {
    if (pSlices == nullptr) {
        return;
    }
    
    pSlices->clear();
    pSlices->reserve(kSnapShotterReserveCount);
    CaptureSlice(pSlices, pWorkSpace, pExpander, "START");
}

std::string JsonEscape(const std::string &pText) {
    std::ostringstream aStream;
    for (const unsigned char aChar : pText) {
        switch (aChar) {
            case '\\': aStream << "\\\\"; break;
            case '"': aStream << "\\\""; break;
            case '\b': aStream << "\\b"; break;
            case '\f': aStream << "\\f"; break;
            case '\n': aStream << "\\n"; break;
            case '\r': aStream << "\\r"; break;
            case '\t': aStream << "\\t"; break;
            default:
                if (aChar < 0x20U) {
                    aStream << "\\u00";
                    const char *aHex = "0123456789abcdef";
                    aStream << aHex[(aChar >> 4U) & 0xFU] << aHex[aChar & 0xFU];
                } else {
                    aStream << static_cast<char>(aChar);
                }
                break;
        }
    }
    return aStream.str();
}

std::string SanitizePathPiece(const std::string &pText) {
    if (pText.empty()) {
        return "empty";
    }
    
    std::string aResult;
    aResult.reserve(pText.size());
    for (const unsigned char aChar : pText) {
        if ((std::isalnum(aChar) != 0) || (aChar == '_') || (aChar == '-')) {
            aResult.push_back(static_cast<char>(aChar));
        } else {
            aResult.push_back('_');
        }
    }
    return aResult.empty() ? std::string("empty") : aResult;
}

std::string ShapeText(const std::vector<std::size_t> &pShape) {
    std::ostringstream aStream;
    aStream << "(";
    for (std::size_t aIndex = 0U; aIndex < pShape.size(); ++aIndex) {
        if (aIndex > 0U) {
            aStream << ", ";
        }
        aStream << pShape[aIndex];
    }
    if (pShape.size() == 1U) {
        aStream << ",";
    }
    aStream << ")";
    return aStream.str();
}

bool SaveTextFile(const std::string &pPath,
                  const std::string &pText) {
    std::vector<std::uint8_t> aBytes(pText.begin(), pText.end());
    return FileIO::Save(pPath, aBytes);
}

bool SaveNpyUInt8(const std::string &pPath,
                  const void *pData,
                  const std::size_t pByteCount,
                  const std::vector<std::size_t> &pShape) {
    if ((pData == nullptr) || pShape.empty()) {
        return false;
    }
    
    std::size_t aExpectedByteCount = 1U;
    for (std::size_t aDimension : pShape) {
        aExpectedByteCount *= aDimension;
    }
    if (aExpectedByteCount != pByteCount) {
        return false;
    }
    
    const std::string aHeaderCore = "{'descr': '|u1', 'fortran_order': False, 'shape': " +
        ShapeText(pShape) + ", }";
    std::string aHeader = aHeaderCore;
    const std::size_t aPrefixLength = 10U;
    const std::size_t aRemainder = (aPrefixLength + aHeader.size() + 1U) % 16U;
    const std::size_t aPadding = (aRemainder == 0U) ? 0U : (16U - aRemainder);
    aHeader.append(aPadding, ' ');
    aHeader.push_back('\n');
    
    if (aHeader.size() > 0xFFFFU) {
        return false;
    }
    
    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(aPrefixLength + aHeader.size() + pByteCount);
    aBytes.push_back(0x93U);
    aBytes.push_back('N');
    aBytes.push_back('U');
    aBytes.push_back('M');
    aBytes.push_back('P');
    aBytes.push_back('Y');
    aBytes.push_back(1U);
    aBytes.push_back(0U);
    
    const std::uint16_t aHeaderLength = static_cast<std::uint16_t>(aHeader.size());
    aBytes.push_back(static_cast<std::uint8_t>(aHeaderLength & 0xFFU));
    aBytes.push_back(static_cast<std::uint8_t>((aHeaderLength >> 8U) & 0xFFU));
    aBytes.insert(aBytes.end(), aHeader.begin(), aHeader.end());
    
    const std::uint8_t *aData = static_cast<const std::uint8_t *>(pData);
    aBytes.insert(aBytes.end(), aData, aData + pByteCount);
    
    return FileIO::Save(pPath, aBytes);
}

void AppendManifestArray(std::ostringstream *pManifest,
                         const std::string &pArrayName,
                         const std::string &pRelativePath,
                         const std::vector<std::size_t> &pShape,
                         bool *pFirstArray) {
    if ((pManifest == nullptr) || (pFirstArray == nullptr)) {
        return;
    }
    
    if (!*pFirstArray) {
        *pManifest << ",\n";
    }
    *pFirstArray = false;
    
    *pManifest << "          \"" << JsonEscape(pArrayName) << "\": { \"path\": \""
               << JsonEscape(pRelativePath) << "\", \"dtype\": \"uint8\", \"shape\": [";
    for (std::size_t aIndex = 0U; aIndex < pShape.size(); ++aIndex) {
        if (aIndex > 0U) {
            *pManifest << ", ";
        }
        *pManifest << pShape[aIndex];
    }
    *pManifest << "] }";
}

bool SaveSliceArray(std::ostringstream *pManifest,
                    const std::string &pRootPath,
                    const std::string &pRelativeFolder,
                    const std::string &pArrayName,
                    const void *pData,
                    const std::size_t pByteCount,
                    const std::vector<std::size_t> &pShape,
                    bool *pFirstArray) {
    const std::string aRelativePath = FileIO::Join(pRelativeFolder, pArrayName + ".npy");
    const std::string aFullPath = FileIO::Join(pRootPath, aRelativePath);
    if (!SaveNpyUInt8(aFullPath, pData, pByteCount, pShape)) {
        return false;
    }
    AppendManifestArray(pManifest, pArrayName, aRelativePath, pShape, pFirstArray);
    return true;
}

bool SaveSlice(const SnapShotterSlice &pSlice,
               const std::string &pRootPath,
               const std::string &pRelativeFolder,
               std::ostringstream *pManifest) {
    if (pManifest == nullptr) {
        return false;
    }
    
    bool aFirstArray = true;
    
    auto SaveKeyBox = [&](const std::string &pName, const void *pData, const std::size_t pByteCount) -> bool {
        return SaveSliceArray(pManifest, pRootPath, pRelativeFolder, pName, pData, pByteCount,
                              { static_cast<std::size_t>(H_KEY), static_cast<std::size_t>(W_KEY) },
                              &aFirstArray);
    };
    auto SaveBlock = [&](const std::string &pName, const void *pData, const std::size_t pByteCount) -> bool {
        return SaveSliceArray(pManifest, pRootPath, pRelativeFolder, pName, pData, pByteCount,
                              { static_cast<std::size_t>(S_BLOCK) },
                              &aFirstArray);
    };
    auto SaveBytes = [&](const std::string &pName, const void *pData, const std::size_t pByteCount) -> bool {
        return SaveSliceArray(pManifest, pRootPath, pRelativeFolder, pName, pData, pByteCount,
                              { pByteCount },
                              &aFirstArray);
    };
    
    if (!SaveKeyBox("key_box_a", pSlice.mKeyBoxA, sizeof(pSlice.mKeyBoxA))) { return false; }
    if (!SaveKeyBox("key_box_b", pSlice.mKeyBoxB, sizeof(pSlice.mKeyBoxB))) { return false; }
    
    if (!SaveBlock("source", pSlice.mSource, sizeof(pSlice.mSource))) { return false; }
    
    if (!SaveBlock("expansion_lane_a", pSlice.mExpansionLaneA, sizeof(pSlice.mExpansionLaneA))) { return false; }
    if (!SaveBlock("expansion_lane_b", pSlice.mExpansionLaneB, sizeof(pSlice.mExpansionLaneB))) { return false; }
    if (!SaveBlock("expansion_lane_c", pSlice.mExpansionLaneC, sizeof(pSlice.mExpansionLaneC))) { return false; }
    if (!SaveBlock("expansion_lane_d", pSlice.mExpansionLaneD, sizeof(pSlice.mExpansionLaneD))) { return false; }
    
    if (!SaveBlock("work_lane_a", pSlice.mWorkLaneA, sizeof(pSlice.mWorkLaneA))) { return false; }
    if (!SaveBlock("work_lane_b", pSlice.mWorkLaneB, sizeof(pSlice.mWorkLaneB))) { return false; }
    if (!SaveBlock("work_lane_c", pSlice.mWorkLaneC, sizeof(pSlice.mWorkLaneC))) { return false; }
    if (!SaveBlock("work_lane_d", pSlice.mWorkLaneD, sizeof(pSlice.mWorkLaneD))) { return false; }
    
    if (!SaveBlock("operation_lane_a", pSlice.mOperationLaneA, sizeof(pSlice.mOperationLaneA))) { return false; }
    if (!SaveBlock("operation_lane_b", pSlice.mOperationLaneB, sizeof(pSlice.mOperationLaneB))) { return false; }
    if (!SaveBlock("operation_lane_c", pSlice.mOperationLaneC, sizeof(pSlice.mOperationLaneC))) { return false; }
    if (!SaveBlock("operation_lane_d", pSlice.mOperationLaneD, sizeof(pSlice.mOperationLaneD))) { return false; }
    
    if (!SaveBlock("snow_lane_a", pSlice.mSnowLaneA, sizeof(pSlice.mSnowLaneA))) { return false; }
    if (!SaveBlock("snow_lane_b", pSlice.mSnowLaneB, sizeof(pSlice.mSnowLaneB))) { return false; }
    if (!SaveBlock("snow_lane_c", pSlice.mSnowLaneC, sizeof(pSlice.mSnowLaneC))) { return false; }
    if (!SaveBlock("snow_lane_d", pSlice.mSnowLaneD, sizeof(pSlice.mSnowLaneD))) { return false; }
    
    if (!SaveBlock("fire_lane_a", pSlice.mFireLaneA, sizeof(pSlice.mFireLaneA))) { return false; }
    if (!SaveBlock("fire_lane_b", pSlice.mFireLaneB, sizeof(pSlice.mFireLaneB))) { return false; }
    if (!SaveBlock("fire_lane_c", pSlice.mFireLaneC, sizeof(pSlice.mFireLaneC))) { return false; }
    if (!SaveBlock("fire_lane_d", pSlice.mFireLaneD, sizeof(pSlice.mFireLaneD))) { return false; }
    
    if (!SaveBlock("invest_lane_a", pSlice.mInvestLaneA, sizeof(pSlice.mInvestLaneA))) { return false; }
    if (!SaveBlock("invest_lane_b", pSlice.mInvestLaneB, sizeof(pSlice.mInvestLaneB))) { return false; }
    if (!SaveBlock("invest_lane_c", pSlice.mInvestLaneC, sizeof(pSlice.mInvestLaneC))) { return false; }
    if (!SaveBlock("invest_lane_d", pSlice.mInvestLaneD, sizeof(pSlice.mInvestLaneD))) { return false; }
    
    if (!SaveBlock("invest_lane_e", pSlice.mInvestLaneE, sizeof(pSlice.mInvestLaneE))) { return false; }
    if (!SaveBlock("invest_lane_f", pSlice.mInvestLaneF, sizeof(pSlice.mInvestLaneF))) { return false; }
    if (!SaveBlock("invest_lane_g", pSlice.mInvestLaneG, sizeof(pSlice.mInvestLaneG))) { return false; }
    if (!SaveBlock("invest_lane_h", pSlice.mInvestLaneH, sizeof(pSlice.mInvestLaneH))) { return false; }
    
    if (!SaveBytes("domain_bundle", &pSlice.mDomainBundle, sizeof(pSlice.mDomainBundle))) { return false; }
    if (!SaveBytes("domain_bundle_inbuilt", &pSlice.mDomainBundleInbuilt, sizeof(pSlice.mDomainBundleInbuilt))) { return false; }
    if (!SaveBytes("domain_bundle_ephemeral", &pSlice.mDomainBundleEphemeral, sizeof(pSlice.mDomainBundleEphemeral))) { return false; }
    
    return true;
}

bool SaveTimeline(std::ostringstream *pManifest,
                  const std::string &pRootPath,
                  const std::string &pTimelineName,
                  const std::vector<SnapShotterSlice> &pSlices,
                  bool *pFirstTimeline) {
    if ((pManifest == nullptr) || (pFirstTimeline == nullptr)) {
        return false;
    }
    
    if (!*pFirstTimeline) {
        *pManifest << ",\n";
    }
    *pFirstTimeline = false;
    
    *pManifest << "    {\n"
               << "      \"name\": \"" << JsonEscape(pTimelineName) << "\",\n"
               << "      \"slice_count\": " << pSlices.size() << ",\n"
               << "      \"slices\": [\n";
    
    for (std::size_t aIndex = 0U; aIndex < pSlices.size(); ++aIndex) {
        const SnapShotterSlice &aSlice = pSlices[aIndex];
        const std::string aSliceFolder = "slice_" + std::to_string(aIndex) + "_" + SanitizePathPiece(aSlice.mName);
        const std::string aRelativeFolder = FileIO::Join(pTimelineName, aSliceFolder);
        
        if (aIndex > 0U) {
            *pManifest << ",\n";
        }
        *pManifest << "        {\n"
                   << "          \"index\": " << aIndex << ",\n"
                   << "          \"name\": \"" << JsonEscape(aSlice.mName) << "\",\n"
                   << "          \"folder\": \"" << JsonEscape(aRelativeFolder) << "\",\n"
                   << "          \"arrays\": {\n";
        
        if (!SaveSlice(aSlice, pRootPath, aRelativeFolder, pManifest)) {
            return false;
        }
        
        *pManifest << "\n"
                   << "          }\n"
                   << "        }";
    }
    
    *pManifest << "\n"
               << "      ]\n"
               << "    }";
    return true;
}

}

void SnapShotter::SnapStart_KDFA(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander) {
    StartSlices(&KDFAStorage(), pWorkSpace, pExpander);
}

void SnapShotter::SnapUpdate_KDFA(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander, std::string pName) {
    CaptureSlice(&KDFAStorage(), pWorkSpace, pExpander, pName);
}

void SnapShotter::SnapStart_KDFB(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander) {
    StartSlices(&KDFBStorage(), pWorkSpace, pExpander);
}

void SnapShotter::SnapUpdate_KDFB(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander, std::string pName) {
    CaptureSlice(&KDFBStorage(), pWorkSpace, pExpander, pName);
}

void SnapShotter::SnapStart_SEED(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander) {
    StartSlices(&SEEDStorage(), pWorkSpace, pExpander);
}

void SnapShotter::SnapUpdate_SEED(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander, std::string pName) {
    CaptureSlice(&SEEDStorage(), pWorkSpace, pExpander, pName);
}

void SnapShotter::SnapStart_TWIST(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander) {
    StartSlices(&TWISTStorage(), pWorkSpace, pExpander);
}

void SnapShotter::SnapUpdate_TWIST(TwistWorkSpace *pWorkSpace, TwistExpander *pExpander, std::string pName) {
    CaptureSlice(&TWISTStorage(), pWorkSpace, pExpander, pName);
}

const std::vector<SnapShotterSlice> &SnapShotter::Slices_KDFA() {
    return KDFAStorage();
}

const std::vector<SnapShotterSlice> &SnapShotter::Slices_KDFB() {
    return KDFBStorage();
}

const std::vector<SnapShotterSlice> &SnapShotter::Slices_SEED() {
    return SEEDStorage();
}

const std::vector<SnapShotterSlice> &SnapShotter::Slices_TWIST() {
    return TWISTStorage();
}

void SnapShotter::ClearAll() {
    KDFAStorage().clear();
    KDFBStorage().clear();
    SEEDStorage().clear();
    TWISTStorage().clear();
}

bool SnapShotter::SaveProjectRoot(const std::string &pFolder,
                                  const std::string &pFileName) {
    const std::string aFileName = pFileName.empty() ? std::string("snapshots") : pFileName;
    const std::string aRootPath = FileIO::ProjectRoot(FileIO::Join(pFolder, aFileName));
    
    std::ostringstream aManifest;
    aManifest << "{\n"
              << "  \"format\": \"mean_machine_snapshots_npy_v1\",\n"
              << "  \"dtype\": \"uint8\",\n"
              << "  \"constants\": {\n"
              << "    \"S_BLOCK\": " << S_BLOCK << ",\n"
              << "    \"W_KEY\": " << W_KEY << ",\n"
              << "    \"H_KEY\": " << H_KEY << ",\n"
              << "    \"sizeof_TwistDomainBundle\": " << sizeof(TwistDomainBundle) << "\n"
              << "  },\n"
              << "  \"python_hint\": \"arr = numpy.load(root / path_from_manifest)\",\n"
              << "  \"timelines\": [\n";
    
    bool aFirstTimeline = true;
    if (!SaveTimeline(&aManifest, aRootPath, "KDFA", KDFAStorage(), &aFirstTimeline)) { return false; }
    if (!SaveTimeline(&aManifest, aRootPath, "KDFB", KDFBStorage(), &aFirstTimeline)) { return false; }
    if (!SaveTimeline(&aManifest, aRootPath, "SEED", SEEDStorage(), &aFirstTimeline)) { return false; }
    if (!SaveTimeline(&aManifest, aRootPath, "TWIST", TWISTStorage(), &aFirstTimeline)) { return false; }
    
    aManifest << "\n"
              << "  ]\n"
              << "}\n";
    
    return SaveTextFile(FileIO::Join(aRootPath, "manifest.json"), aManifest.str());
}
