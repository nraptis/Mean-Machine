//
//  GTwistExpander.cpp
//  MeanMachine
//

#include "GTwistExpander.hpp"

#include "Random.hpp"
#include "SaltTables.hpp"
#include "TwistFarm.hpp"
#include "TwistFarmSalt.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdlib>
#include <cstdio>

namespace {

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}

std::uint8_t NonZeroRandomByte() {
    std::uint8_t aValue = Random::GetByte();
    if (aValue == 0U) {
        aValue = 1U;
    }
    return aValue;
}

void RandomizeDomainConstants(TwistDomainConstants *pConstants) {
    if (pConstants == nullptr) {
        return;
    }

    pConstants->mIngress = Random::Get64High();
    pConstants->mScatter = Random::Get64High();
    pConstants->mCross = Random::Get64High();
    pConstants->mMatrixSelectA = Random::Get64High();
    pConstants->mMatrixSelectB = Random::Get64High();
    pConstants->mMatrixUnrollA = NonZeroRandomByte();
    pConstants->mMatrixUnrollB = NonZeroRandomByte();
    pConstants->mMatrixArgA = NonZeroRandomByte();
    pConstants->mMatrixArgB = NonZeroRandomByte();
    pConstants->mMatrixArgC = NonZeroRandomByte();
    pConstants->mMatrixArgD = NonZeroRandomByte();
}

void RandomizeDomainBundleConstants(TwistDomainBundle *pBundle) {
    if (pBundle == nullptr) {
        return;
    }

    RandomizeDomainConstants(&pBundle->mKeyRotateAConstants);
    RandomizeDomainConstants(&pBundle->mKeyRotateBConstants);
    RandomizeDomainConstants(&pBundle->mKeySpawnAConstants);
    RandomizeDomainConstants(&pBundle->mKeySpawnBConstants);
    RandomizeDomainConstants(&pBundle->mSeedConstants);
    RandomizeDomainConstants(&pBundle->mTwistConstants);
}

bool ExecuteBatchJsonText(const std::vector<std::string> &pBatchJsonText,
                          TwistWorkSpace *pWorkSpace,
                          TwistExpander *pExpander,
                          TwistDomainSaltSet *pParamSaltSet,
                          std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                          std::string *pErrorMessage) {
    if (pVariables == nullptr) {
        SetError(pErrorMessage, "batch variable map was null.");
        return false;
    }

    for (const std::string &aBatchJson : pBatchJsonText) {
        GBatch aBatch;
        if (!GBatch::FromJson(aBatchJson, &aBatch, pErrorMessage)) {
            if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
                *pErrorMessage = "failed to parse batch JSON.";
            }
            return false;
        }

        if (!aBatch.ExecuteWithRuntimeVariables(pWorkSpace,
                                                pExpander,
                                                pParamSaltSet,
                                                pVariables,
                                                pErrorMessage)) {
            if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
                *pErrorMessage = "batch execution failed.";
            }
            return false;
        }
    }
    return true;
}

std::string TrimCopy(const std::string &pText) {
    std::size_t aStart = 0U;
    while ((aStart < pText.size()) && std::isspace(static_cast<unsigned char>(pText[aStart]))) {
        aStart += 1U;
    }

    std::size_t aEnd = pText.size();
    while ((aEnd > aStart) && std::isspace(static_cast<unsigned char>(pText[aEnd - 1U]))) {
        aEnd -= 1U;
    }
    return pText.substr(aStart, aEnd - aStart);
}

bool IsIdentifier(const std::string &pName) {
    if (pName.empty()) {
        return false;
    }
    const unsigned char aFirst = static_cast<unsigned char>(pName[0]);
    if (!(std::isalpha(aFirst) || (aFirst == '_'))) {
        return false;
    }
    for (const unsigned char aCh : pName) {
        if (!(std::isalnum(aCh) || (aCh == '_'))) {
            return false;
        }
    }
    return true;
}

void StripOuterParens(std::string *pText) {
    if (pText == nullptr) {
        return;
    }
    while (pText->size() >= 2U && pText->front() == '(' && pText->back() == ')') {
        *pText = TrimCopy(pText->substr(1U, pText->size() - 2U));
    }
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

    StripOuterParens(&pValueText);

    while (!pValueText.empty()) {
        const char aLast = pValueText.back();
        if (aLast == 'u' || aLast == 'U' || aLast == 'l' || aLast == 'L') {
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

const TwistDomainConstants *WorkspaceDomainConstantsForMember(TwistWorkSpace *pWorkSpace,
                                                              const std::string &pMemberName) {
    if (pWorkSpace == nullptr) {
        return nullptr;
    }
    if (pMemberName == "mKeySpawnAConstants") {
        return &pWorkSpace->mDomainBundle.mKeySpawnAConstants;
    }
    if (pMemberName == "mKeySpawnBConstants") {
        return &pWorkSpace->mDomainBundle.mKeySpawnBConstants;
    }
    if (pMemberName == "mSeedConstants") {
        return &pWorkSpace->mDomainBundle.mSeedConstants;
    }
    if (pMemberName == "mTwistConstants") {
        return &pWorkSpace->mDomainBundle.mTwistConstants;
    }
    if (pMemberName == "mKeyRotateAConstants") {
        return &pWorkSpace->mDomainBundle.mKeyRotateAConstants;
    }
    if (pMemberName == "mKeyRotateBConstants") {
        return &pWorkSpace->mDomainBundle.mKeyRotateBConstants;
    }
    return nullptr;
}

bool DomainConstantMemberValue(const TwistDomainConstants *pConstants,
                               const std::string &pMemberName,
                               GRuntimeScalar *pValueOut) {
    if ((pConstants == nullptr) || (pValueOut == nullptr)) {
        return false;
    }

    if (pMemberName == "mIngress") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mIngress); return true; }
    if (pMemberName == "mScatter") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mScatter); return true; }
    if (pMemberName == "mCross") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mCross); return true; }
    if (pMemberName == "mMatrixSelectA") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixSelectA); return true; }
    if (pMemberName == "mMatrixSelectB") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixSelectB); return true; }
    if (pMemberName == "mMatrixUnrollA") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixUnrollA); return true; }
    if (pMemberName == "mMatrixUnrollB") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixUnrollB); return true; }
    if (pMemberName == "mMatrixArgA") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixArgA); return true; }
    if (pMemberName == "mMatrixArgB") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixArgB); return true; }
    if (pMemberName == "mMatrixArgC") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixArgC); return true; }
    if (pMemberName == "mMatrixArgD") { *pValueOut = static_cast<GRuntimeScalar>(pConstants->mMatrixArgD); return true; }

    return false;
}

bool ResolveDomainWordAssignmentValue(const std::string &pRight,
                                      TwistWorkSpace *pWorkSpace,
                                      const TwistDomainConstants *pParamConstants,
                                      const std::unordered_map<std::string, GRuntimeScalar> &pVariables,
                                      GRuntimeScalar *pValueOut) {
    if (pValueOut == nullptr) {
        return false;
    }

    if (IsIdentifier(pRight)) {
        const auto aIterator = pVariables.find(pRight);
        if (aIterator != pVariables.end()) {
            *pValueOut = aIterator->second;
            return true;
        }
        return false;
    }

    const std::string aConstantsPrefix = "pConstants->";
    if (pRight.rfind(aConstantsPrefix, 0U) == 0U) {
        const std::string aMemberName = pRight.substr(aConstantsPrefix.size());
        return DomainConstantMemberValue(pParamConstants,
                                         aMemberName,
                                         pValueOut);
    }

    const std::string aWorkspacePrefix = "pWorkSpace->mDomainBundle.";
    if (pRight.rfind(aWorkspacePrefix, 0U) != 0U) {
        return false;
    }

    const std::string aTail = pRight.substr(aWorkspacePrefix.size());
    const std::size_t aDot = aTail.find('.');
    if (aDot == std::string::npos) {
        return false;
    }

    const std::string aConstantsMember = aTail.substr(0U, aDot);
    const std::string aDomainMember = aTail.substr(aDot + 1U);
    const TwistDomainConstants *aConstants = WorkspaceDomainConstantsForMember(pWorkSpace, aConstantsMember);
    return DomainConstantMemberValue(aConstants, aDomainMember, pValueOut);
}

bool ResolveAliasSlot(const std::string &pAlias,
                      TwistWorkSpaceSlot *pSlotOut) {
    if (pSlotOut == nullptr) {
        return false;
    }

    auto NormalizeAliasToken = [](const std::string &pToken) -> std::string {
        std::string aToken = TrimCopy(pToken);
        if (aToken.empty()) {
            return aToken;
        }

        while (!aToken.empty() && ((aToken[0] == '&') || (aToken[0] == '*'))) {
            aToken.erase(aToken.begin());
            aToken = TrimCopy(aToken);
        }

        const std::size_t aBracketPos = aToken.find('[');
        if (aBracketPos != std::string::npos) {
            aToken = TrimCopy(aToken.substr(0U, aBracketPos));
        }

        const std::size_t aMatsPos = aToken.find("mMats");
        if (aMatsPos != std::string::npos) {
            std::string aMatsToken = TrimCopy(aToken.substr(aMatsPos));
            while (!aMatsToken.empty()) {
                const char aLast = aMatsToken.back();
                if ((aLast == ';') || (aLast == ')')) {
                    aMatsToken.pop_back();
                    aMatsToken = TrimCopy(aMatsToken);
                    continue;
                }
                break;
            }
            return aMatsToken;
        }

        const std::size_t aArrowPos = aToken.rfind("->");
        const std::size_t aDotPos = aToken.rfind('.');
        std::size_t aMemberPos = std::string::npos;
        if (aArrowPos != std::string::npos) {
            aMemberPos = aArrowPos + 2U;
        }
        if (aDotPos != std::string::npos) {
            const std::size_t aDotMemberPos = aDotPos + 1U;
            if ((aMemberPos == std::string::npos) || (aDotMemberPos > aMemberPos)) {
                aMemberPos = aDotMemberPos;
            }
        }
        if ((aMemberPos != std::string::npos) && (aMemberPos < aToken.size())) {
            aToken = TrimCopy(aToken.substr(aMemberPos));
        }

        return aToken;
    };

    const std::string aAlias = NormalizeAliasToken(pAlias);
    std::string aKeyToken = aAlias;
    if (aKeyToken.rfind("bufkey:", 0U) == 0U) {
        aKeyToken = aKeyToken.substr(7U);
    }
    TwistBufferKey aParsedKey;
    if (BufferKeyFromToken(aKeyToken, &aParsedKey)) {
        const TwistWorkSpaceSlot aResolvedSlot = ResolveBufferSlot(GSymbol::Buf(aParsedKey));
        if (aResolvedSlot != TwistWorkSpaceSlot::kInvalid) {
            *pSlotOut = aResolvedSlot;
            return true;
        }
    }

    for (int aValue = 0; aValue <= 512; ++aValue) {
        const TwistWorkSpaceSlot aSlot = static_cast<TwistWorkSpaceSlot>(aValue);
        const std::string aSlotAlias = BufAliasName(aSlot);
        if ((aSlotAlias == "aInvalidBuffer") || (aSlotAlias == "invalid")) {
            continue;
        }
        if (aSlotAlias == aAlias) {
            *pSlotOut = aSlot;
            return true;
        }
    }

    struct AliasSlotPair {
        const char *mAlias;
        TwistWorkSpaceSlot mSlot;
    };

    static const AliasSlotPair kWorkspaceFieldAliases[] = {
        {"aSource", TwistWorkSpaceSlot::kSourceLane},
        {"mSourceLane", TwistWorkSpaceSlot::kSourceLane},
        {"aNonceLane", TwistWorkSpaceSlot::kNonceLane},
        {"mNonceLane", TwistWorkSpaceSlot::kNonceLane},
        {"pSource", TwistWorkSpaceSlot::kParamSource},
        {"pSourceInput", TwistWorkSpaceSlot::kParamSource},
        {"aDestination", TwistWorkSpaceSlot::kParamDestination},
        {"mDest", TwistWorkSpaceSlot::kParamDestination},
        {"pInput", TwistWorkSpaceSlot::kParamSource},
        {"pDestination", TwistWorkSpaceSlot::kParamDestination},
        {"pOutput", TwistWorkSpaceSlot::kParamDestination},
        {"mSaltA", TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignA},
        {"mSaltB", TwistWorkSpaceSlot::kParamDomainSaltOrbiterAssignB},
        {"mSaltC", TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateC},
        {"mSaltD", TwistWorkSpaceSlot::kParamDomainSaltOrbiterUpdateD},
        {"mSaltE", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateE},
        {"mSaltF", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateF},
        {"mSaltG", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateG},
        {"mSaltH", TwistWorkSpaceSlot::kParamDomainSaltWandererUpdateH},
        {"mHeartLaneA", TwistWorkSpaceSlot::kHeartLaneA},
        {"mHeartLaneB", TwistWorkSpaceSlot::kHeartLaneB},
        {"mHeartLaneC", TwistWorkSpaceSlot::kHeartLaneC},
        {"mHeartLaneD", TwistWorkSpaceSlot::kHeartLaneD},
        {"mSpiritLaneA", TwistWorkSpaceSlot::kSpiritLaneA},
        {"mSpiritLaneB", TwistWorkSpaceSlot::kSpiritLaneB},
        {"mSpiritLaneC", TwistWorkSpaceSlot::kSpiritLaneC},
        {"mSpiritLaneD", TwistWorkSpaceSlot::kSpiritLaneD},
        {"mFireLaneA", TwistWorkSpaceSlot::kFireLaneA},
        {"mFireLaneB", TwistWorkSpaceSlot::kFireLaneB},
        {"mFireLaneC", TwistWorkSpaceSlot::kFireLaneC},
        {"mFireLaneD", TwistWorkSpaceSlot::kFireLaneD},
        {"mWaterLaneA", TwistWorkSpaceSlot::kWaterLaneA},
        {"mWaterLaneB", TwistWorkSpaceSlot::kWaterLaneB},
        {"mWaterLaneC", TwistWorkSpaceSlot::kWaterLaneC},
        {"mWaterLaneD", TwistWorkSpaceSlot::kWaterLaneD},
        {"mEarthLaneA", TwistWorkSpaceSlot::kEarthLaneA},
        {"mEarthLaneB", TwistWorkSpaceSlot::kEarthLaneB},
        {"mEarthLaneC", TwistWorkSpaceSlot::kEarthLaneC},
        {"mEarthLaneD", TwistWorkSpaceSlot::kEarthLaneD},
        {"mWindLaneA", TwistWorkSpaceSlot::kWindLaneA},
        {"mWindLaneB", TwistWorkSpaceSlot::kWindLaneB},
        {"mWindLaneC", TwistWorkSpaceSlot::kWindLaneC},
        {"mWindLaneD", TwistWorkSpaceSlot::kWindLaneD},
        {"mFuseLaneA", TwistWorkSpaceSlot::kFuseLaneA},
        {"mFuseLaneB", TwistWorkSpaceSlot::kFuseLaneB},
        {"mFuseLaneC", TwistWorkSpaceSlot::kFuseLaneC},
        {"mFuseLaneD", TwistWorkSpaceSlot::kFuseLaneD},
        {"mWoodLaneA", TwistWorkSpaceSlot::kWoodLaneA},
        {"mWoodLaneB", TwistWorkSpaceSlot::kWoodLaneB},
        {"mWoodLaneC", TwistWorkSpaceSlot::kWoodLaneC},
        {"mWoodLaneD", TwistWorkSpaceSlot::kWoodLaneD},
        {"mLightningLaneA", TwistWorkSpaceSlot::kLightningLaneA},
        {"mLightningLaneB", TwistWorkSpaceSlot::kLightningLaneB},
        {"mLightningLaneC", TwistWorkSpaceSlot::kLightningLaneC},
        {"mLightningLaneD", TwistWorkSpaceSlot::kLightningLaneD},
        {"mMagmaLaneA", TwistWorkSpaceSlot::kMagmaLaneA},
        {"mMagmaLaneB", TwistWorkSpaceSlot::kMagmaLaneB},
        {"mMagmaLaneC", TwistWorkSpaceSlot::kMagmaLaneC},
        {"mMagmaLaneD", TwistWorkSpaceSlot::kMagmaLaneD},
        {"mSoilLaneA", TwistWorkSpaceSlot::kSoilLaneA},
        {"mSoilLaneB", TwistWorkSpaceSlot::kSoilLaneB},
        {"mSoilLaneC", TwistWorkSpaceSlot::kSoilLaneC},
        {"mSoilLaneD", TwistWorkSpaceSlot::kSoilLaneD},
        {"mPlasmaLaneA", TwistWorkSpaceSlot::kPlasmaLaneA},
        {"mPlasmaLaneB", TwistWorkSpaceSlot::kPlasmaLaneB},
        {"mPlasmaLaneC", TwistWorkSpaceSlot::kPlasmaLaneC},
        {"mPlasmaLaneD", TwistWorkSpaceSlot::kPlasmaLaneD},
        {"mShadowLaneA", TwistWorkSpaceSlot::kShadowLaneA},
        {"mShadowLaneB", TwistWorkSpaceSlot::kShadowLaneB},
        {"mShadowLaneC", TwistWorkSpaceSlot::kShadowLaneC},
        {"mShadowLaneD", TwistWorkSpaceSlot::kShadowLaneD},
        {"mCrystalLaneA", TwistWorkSpaceSlot::kCrystalLaneA},
        {"mCrystalLaneB", TwistWorkSpaceSlot::kCrystalLaneB},
        {"mCrystalLaneC", TwistWorkSpaceSlot::kCrystalLaneC},
        {"mCrystalLaneD", TwistWorkSpaceSlot::kCrystalLaneD},
        {"mAetherLaneA", TwistWorkSpaceSlot::kAetherLaneA},
        {"mAetherLaneB", TwistWorkSpaceSlot::kAetherLaneB},
        {"mAetherLaneC", TwistWorkSpaceSlot::kAetherLaneC},
        {"mAetherLaneD", TwistWorkSpaceSlot::kAetherLaneD},
        {"mCelestialLaneA", TwistWorkSpaceSlot::kCelestialLaneA},
        {"mCelestialLaneB", TwistWorkSpaceSlot::kCelestialLaneB},
        {"mCelestialLaneC", TwistWorkSpaceSlot::kCelestialLaneC},
        {"mCelestialLaneD", TwistWorkSpaceSlot::kCelestialLaneD},
        {"mKineticLaneA", TwistWorkSpaceSlot::kKineticLaneA},
        {"mKineticLaneB", TwistWorkSpaceSlot::kKineticLaneB},
        {"mKineticLaneC", TwistWorkSpaceSlot::kKineticLaneC},
        {"mKineticLaneD", TwistWorkSpaceSlot::kKineticLaneD},
        {"mVaporLaneA", TwistWorkSpaceSlot::kVaporLaneA},
        {"mVaporLaneB", TwistWorkSpaceSlot::kVaporLaneB},
        {"mVaporLaneC", TwistWorkSpaceSlot::kVaporLaneC},
        {"mVaporLaneD", TwistWorkSpaceSlot::kVaporLaneD},
        {"mIceLaneA", TwistWorkSpaceSlot::kIceLaneA},
        {"mIceLaneB", TwistWorkSpaceSlot::kIceLaneB},
        {"mIceLaneC", TwistWorkSpaceSlot::kIceLaneC},
        {"mIceLaneD", TwistWorkSpaceSlot::kIceLaneD},
        {"mKeyBoxUnrolledA", TwistWorkSpaceSlot::kKeyBoxUnrolledA},
        {"mKeyBoxUnrolledB", TwistWorkSpaceSlot::kKeyBoxUnrolledB},
        {"mKeyRowReadA", TwistWorkSpaceSlot::kKeyRowReadA},
        {"mKeyRowReadB", TwistWorkSpaceSlot::kKeyRowReadB},
        {"mKeyRowWriteA", TwistWorkSpaceSlot::kKeyRowWriteA},
        {"mKeyRowWriteB", TwistWorkSpaceSlot::kKeyRowWriteB},
        {"mKeyRowA0", TwistWorkSpaceSlot::kKeyRowA0},
        {"mKeyRowA1", TwistWorkSpaceSlot::kKeyRowA1},
        {"mKeyRowA2", TwistWorkSpaceSlot::kKeyRowA2},
        {"mKeyRowA3", TwistWorkSpaceSlot::kKeyRowA3},
        {"mKeyRowA4", TwistWorkSpaceSlot::kKeyRowA4},
        {"mKeyRowA5", TwistWorkSpaceSlot::kKeyRowA5},
        {"mKeyRowA6", TwistWorkSpaceSlot::kKeyRowA6},
        {"mKeyRowA7", TwistWorkSpaceSlot::kKeyRowA7},
        {"mKeyRowB0", TwistWorkSpaceSlot::kKeyRowB0},
        {"mKeyRowB1", TwistWorkSpaceSlot::kKeyRowB1},
        {"mKeyRowB2", TwistWorkSpaceSlot::kKeyRowB2},
        {"mKeyRowB3", TwistWorkSpaceSlot::kKeyRowB3},
        {"mKeyRowB4", TwistWorkSpaceSlot::kKeyRowB4},
        {"mKeyRowB5", TwistWorkSpaceSlot::kKeyRowB5},
        {"mKeyRowB6", TwistWorkSpaceSlot::kKeyRowB6},
        {"mKeyRowB7", TwistWorkSpaceSlot::kKeyRowB7},
        {"mIndexList256A", TwistWorkSpaceSlot::kIndexList256A},
        {"mIndexList256B", TwistWorkSpaceSlot::kIndexList256B},
        {"mIndexList256C", TwistWorkSpaceSlot::kIndexList256C},
        {"mIndexList256D", TwistWorkSpaceSlot::kIndexList256D}
    };

    for (const AliasSlotPair &aPair : kWorkspaceFieldAliases) {
        if (aAlias == aPair.mAlias) {
            *pSlotOut = aPair.mSlot;
            return true;
        }
    }

    return false;
}

bool ParseCryptoCallArguments(const std::string &pLine,
                              const std::string &pMethodName,
                              std::vector<std::string> *pArgsOut) {
    if (pArgsOut == nullptr) {
        return false;
    }

    std::string aLine = TrimCopy(pLine);
    if (aLine.empty()) {
        return false;
    }

    std::size_t aComment = aLine.find("//");
    while (aComment != std::string::npos) {
        const std::size_t aLineEnd = aLine.find('\n', aComment);
        if (aLineEnd == std::string::npos) {
            aLine.erase(aComment);
            break;
        }
        aLine.erase(aComment, aLineEnd - aComment);
        aComment = aLine.find("//", aComment);
    }
    aLine = TrimCopy(aLine);

    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimCopy(aLine);
    }

    const std::string aCallTokenDot = "." + pMethodName + "(";
    const std::string aCallTokenArrow = "->" + pMethodName + "(";
    const std::string aCallTokenScope = "::" + pMethodName + "(";
    const std::string aCallTokenPlain = pMethodName + "(";
    std::size_t aCallPos = aLine.find(aCallTokenDot);
    std::size_t aOpen = std::string::npos;
    if (aCallPos != std::string::npos) {
        aOpen = aCallPos + aCallTokenDot.size();
    } else {
        aCallPos = aLine.find(aCallTokenArrow);
        if (aCallPos != std::string::npos) {
            aOpen = aCallPos + aCallTokenArrow.size();
        } else {
            aCallPos = aLine.find(aCallTokenScope);
            if (aCallPos != std::string::npos) {
                aOpen = aCallPos + aCallTokenScope.size();
            } else if (aLine.rfind(aCallTokenPlain, 0U) == 0U) {
                aCallPos = 0U;
                aOpen = aCallTokenPlain.size();
            }
        }
    }

    if ((aCallPos == std::string::npos) || (aOpen == std::string::npos)) {
        return false;
    }

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

bool ExecuteCryptoGeneratorCallLine(const std::string &pLine,
                                    TwistWorkSpace *pWorkSpace,
                                    TwistExpander *pExpander,
                                    std::string *pErrorMessage) {
    enum class CryptoMethod : std::uint8_t {
        kStepB_MakeSalts = 1,
        kStepD_MakeSalts = 3
    };

    std::vector<std::string> aArgs;
    CryptoMethod aMethod = CryptoMethod::kStepB_MakeSalts;
    if (ParseCryptoCallArguments(pLine, "StepB_MakeSalts", &aArgs)) {
        aMethod = CryptoMethod::kStepB_MakeSalts;
    } else if (ParseCryptoCallArguments(pLine, "StepD_MakeSalts", &aArgs)) {
        aMethod = CryptoMethod::kStepD_MakeSalts;
    } else {
        return false;
    }

    const bool aValidCount =
        ((aMethod == CryptoMethod::kStepB_MakeSalts) && (aArgs.size() == 17U)) ||
        ((aMethod == CryptoMethod::kStepD_MakeSalts) && (aArgs.size() == 25U));
    if (!aValidCount) {
        if (aMethod == CryptoMethod::kStepB_MakeSalts) {
            SetError(pErrorMessage, "StepB_MakeSalts expects 17 arguments.");
        } else {
            SetError(pErrorMessage, "StepD_MakeSalts expects 25 arguments.");
        }
        return false;
    }

    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        SetError(pErrorMessage, "Legacy crypto-step call execution was missing required runtime inputs.");
        return false;
    }

    std::vector<std::uint8_t *> aBuffers;
    aBuffers.reserve(aArgs.size());
    for (const std::string &aAlias : aArgs) {
        TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
        if (!ResolveAliasSlot(aAlias, &aSlot)) {
            SetError(pErrorMessage, "Unknown buffer alias in legacy crypto-step call: " + aAlias);
            return false;
        }

        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkSpace, pExpander, aSlot);
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "Resolved null buffer for alias: " + aAlias);
            return false;
        }
        aBuffers.push_back(aBuffer);
    }

    if (aMethod == CryptoMethod::kStepB_MakeSalts) {
        return true;
    }

    if (aMethod == CryptoMethod::kStepD_MakeSalts) {
        return true;
    }
    SetError(pErrorMessage, "Unsupported legacy crypto-step call.");
    return false;
}

bool ExecuteCryptoMakeLine(const std::string &pLine,
                           TwistWorkSpace *pWorkSpace,
                           TwistExpander *pExpander,
                           std::string *pErrorMessage) {
    return ExecuteCryptoGeneratorCallLine(pLine, pWorkSpace, pExpander, pErrorMessage);
}

bool ExecuteCryptoSaltLine(const std::string &pLine,
                           TwistWorkSpace *pWorkSpace,
                           TwistExpander *pExpander,
                           std::string *pErrorMessage) {
    return ExecuteCryptoGeneratorCallLine(pLine, pWorkSpace, pExpander, pErrorMessage);
}

std::string NormalizeRoundMaterialToken(const std::string &pToken) {
    std::string aToken = TrimCopy(pToken);
    while (!aToken.empty() && (aToken.front() == '&')) {
        aToken.erase(aToken.begin());
        aToken = TrimCopy(aToken);
    }
    while ((aToken.size() >= 2U) && (aToken.front() == '(') && (aToken.back() == ')')) {
        aToken = TrimCopy(aToken.substr(1U, aToken.size() - 2U));
    }

    const char *kPrefixes[] = {
        "pWorkSpace->",
        "mWorkspace->",
        "(*pWorkSpace).",
        "(*mWorkspace).",
        "this->",
        "pExpander->",
        "(*pExpander)."
    };
    for (const char *aPrefix : kPrefixes) {
        const std::string aPrefixText(aPrefix);
        if (aToken.rfind(aPrefixText, 0U) == 0U) {
            aToken = TrimCopy(aToken.substr(aPrefixText.size()));
            break;
        }
    }
    return aToken;
}

std::string NormalizeConstantsToken(const std::string &pToken) {
    std::string aToken = TrimCopy(pToken);
    while (!aToken.empty() && (aToken.front() == '&')) {
        aToken.erase(aToken.begin());
        aToken = TrimCopy(aToken);
    }
    while ((aToken.size() >= 2U) && (aToken.front() == '(') && (aToken.back() == ')')) {
        aToken = TrimCopy(aToken.substr(1U, aToken.size() - 2U));
    }

    const char *kPrefixes[] = {
        "pWorkSpace->",
        "mWorkspace->",
        "(*pWorkSpace).",
        "(*mWorkspace).",
        "this->",
        "pExpander->",
        "(*pExpander)."
    };
    for (const char *aPrefix : kPrefixes) {
        const std::string aPrefixText(aPrefix);
        if (aToken.rfind(aPrefixText, 0U) == 0U) {
            aToken = TrimCopy(aToken.substr(aPrefixText.size()));
            break;
        }
    }
    return aToken;
}

bool ResolveConstantsToken(const std::string &pToken,
                           TwistWorkSpace *pWorkSpace,
                           TwistExpander *pExpander,
                           TwistDomainConstants **pConstantsResolved) {
    if (pConstantsResolved == nullptr) {
        return false;
    }

    const std::string aToken = NormalizeConstantsToken(pToken);
    if (aToken.empty()) {
        return false;
    }

    auto TryWorkspaceConstants = [&](const std::string &pName,
                                     TwistDomainConstants *pConstants) -> bool {
        if ((pWorkSpace == nullptr) || (pConstants == nullptr) || (aToken != pName)) {
            return false;
        }
        *pConstantsResolved = pConstants;
        return true;
    };

    if (TryWorkspaceConstants("mDomainBundle.mKeyRotateAConstants", &pWorkSpace->mDomainBundle.mKeyRotateAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mKeyRotateBConstants", &pWorkSpace->mDomainBundle.mKeyRotateBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mKeySpawnAConstants", &pWorkSpace->mDomainBundle.mKeySpawnAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mKeySpawnBConstants", &pWorkSpace->mDomainBundle.mKeySpawnBConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mSeedConstants", &pWorkSpace->mDomainBundle.mSeedConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mTwistConstants", &pWorkSpace->mDomainBundle.mTwistConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mKeyAConstants", &pWorkSpace->mDomainBundle.mKeyRotateAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mKeyBConstants", &pWorkSpace->mDomainBundle.mKeySpawnAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mMaskAConstants", &pWorkSpace->mDomainBundle.mKeyRotateAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mMaskBConstants", &pWorkSpace->mDomainBundle.mKeySpawnAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mMaskLaneConstants", &pWorkSpace->mDomainBundle.mKeySpawnAConstants)) { return true; }
    if (TryWorkspaceConstants("mDomainBundle.mSpiritLaneConstants", &pWorkSpace->mDomainBundle.mSeedConstants)) { return true; }

    if (pExpander == nullptr) {
        return false;
    }

    if (aToken == "mDomainBundleEphemeral.mKeyRotateAConstants") {
        *pConstantsResolved = &(pExpander->GetDomainBundleEphemeral()->mKeyRotateAConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mKeyRotateBConstants") {
        *pConstantsResolved = &(pExpander->GetDomainBundleEphemeral()->mKeyRotateBConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mKeySpawnAConstants") {
        *pConstantsResolved = &(pExpander->GetDomainBundleEphemeral()->mKeySpawnAConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mKeySpawnBConstants") {
        *pConstantsResolved = &(pExpander->GetDomainBundleEphemeral()->mKeySpawnBConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mSeedConstants") {
        *pConstantsResolved = &(pExpander->GetDomainBundleEphemeral()->mSeedConstants);
        return true;
    }
    if (aToken == "mDomainBundleEphemeral.mTwistConstants") {
        *pConstantsResolved = &(pExpander->GetDomainBundleEphemeral()->mTwistConstants);
        return true;
    }

    if ((aToken == "mConstantsPhaseA") ||
        (aToken == "mConstantsKeyA") ||
        (aToken == "mConstantsMaskA") ||
        (aToken == "mDomainBundleInbuilt.mKeyRotateAConstants") ||
        (aToken == "mDomainBundleInbuilt.mKeyAConstants") ||
        (aToken == "mDomainBundleInbuilt.mMaskAConstants")) {
        *pConstantsResolved = &(pExpander->GetDomainBundleInbuilt()->mKeyRotateAConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseB") ||
        (aToken == "mConstantsKeyB") ||
        (aToken == "mConstantsMaskB") ||
        (aToken == "mConstantsMaskLane") ||
        (aToken == "mDomainBundleInbuilt.mKeySpawnAConstants") ||
        (aToken == "mDomainBundleInbuilt.mKeyBConstants") ||
        (aToken == "mDomainBundleInbuilt.mMaskBConstants") ||
        (aToken == "mDomainBundleInbuilt.mMaskLaneConstants")) {
        *pConstantsResolved = &(pExpander->GetDomainBundleInbuilt()->mKeySpawnAConstants);
        return true;
    }
    if (aToken == "mDomainBundleInbuilt.mKeyRotateBConstants") {
        *pConstantsResolved = &(pExpander->GetDomainBundleInbuilt()->mKeyRotateBConstants);
        return true;
    }
    if (aToken == "mDomainBundleInbuilt.mKeySpawnBConstants") {
        *pConstantsResolved = &(pExpander->GetDomainBundleInbuilt()->mKeySpawnBConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseC") ||
        (aToken == "mConstantsSpiritLane") ||
        (aToken == "mDomainBundleInbuilt.mSeedConstants") ||
        (aToken == "mDomainBundleInbuilt.mSpiritLaneConstants")) {
        *pConstantsResolved = &(pExpander->GetDomainBundleInbuilt()->mSeedConstants);
        return true;
    }
    if ((aToken == "mConstantsPhaseD") ||
        (aToken == "mDomainBundleInbuilt.mTwistConstants")) {
        *pConstantsResolved = &(pExpander->GetDomainBundleInbuilt()->mTwistConstants);
        return true;
    }
    return false;
}

bool ResolveSaltSetToken(const std::string &pToken,
                         TwistWorkSpace *pWorkSpace,
                         TwistExpander *pExpander,
                         TwistDomainSaltSet **pSaltSetResolved) {
    if (pSaltSetResolved == nullptr) {
        return false;
    }

    const std::string aToken = NormalizeRoundMaterialToken(pToken);
    if (aToken.empty()) {
        return false;
    }

    auto TryWorkspaceSet = [&](const std::string &pName,
                               TwistDomainSaltSet *pSet) -> bool {
        if ((pWorkSpace == nullptr) || (pSet == nullptr)) {
            return false;
        }
        if (aToken != pName) {
            return false;
        }
        *pSaltSetResolved = pSet;
        return true;
    };

    if (TryWorkspaceSet("mDomainBundle.mKeyRotateASalts", &pWorkSpace->mDomainBundle.mKeyRotateASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeyRotateBSalts", &pWorkSpace->mDomainBundle.mKeyRotateBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeySpawnASalts", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeySpawnBSalts", &pWorkSpace->mDomainBundle.mKeySpawnBSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mSeedSalts", &pWorkSpace->mDomainBundle.mSeedSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mTwistSalts", &pWorkSpace->mDomainBundle.mTwistSalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeyASalts", &pWorkSpace->mDomainBundle.mKeyRotateASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mKeyBSalts", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskASalts", &pWorkSpace->mDomainBundle.mKeyRotateASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskBSalts", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mMaskLaneSalts", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mDomainBundle.mSpiritLaneSalts", &pWorkSpace->mDomainBundle.mSeedSalts)) { return true; }

    // Legacy compatibility tokens.
    if (TryWorkspaceSet("mMatsKeyAOrbiterInit", &pWorkSpace->mDomainBundle.mKeyRotateASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyAOrbiter", &pWorkSpace->mDomainBundle.mKeyRotateASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyAWanderer", &pWorkSpace->mDomainBundle.mKeyRotateASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyBOrbiterInit", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyBOrbiter", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mMatsKeyBWanderer", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskAOrbiterInit", &pWorkSpace->mDomainBundle.mKeyRotateASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskAOrbiter", &pWorkSpace->mDomainBundle.mKeyRotateASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskAWanderer", &pWorkSpace->mDomainBundle.mKeyRotateASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskBOrbiterInit", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskBOrbiter", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskBWanderer", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskLaneOrbiterInit", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskLaneOrbiter", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mMatsMaskLaneWanderer", &pWorkSpace->mDomainBundle.mKeySpawnASalts)) { return true; }
    if (TryWorkspaceSet("mMatsSpiritLaneOrbiterInit", &pWorkSpace->mDomainBundle.mSeedSalts)) { return true; }
    if (TryWorkspaceSet("mMatsSpiritLaneOrbiter", &pWorkSpace->mDomainBundle.mSeedSalts)) { return true; }
    if (TryWorkspaceSet("mMatsSpiritLaneWanderer", &pWorkSpace->mDomainBundle.mSeedSalts)) { return true; }

    if (pExpander != nullptr) {
        auto TryExpanderSet = [&](const std::string &pName,
                                  TwistDomainSaltSet *pSet) -> bool {
            if (pSet == nullptr) {
                return false;
            }
            if (aToken != pName) {
                return false;
            }
            *pSaltSetResolved = pSet;
            return true;
        };

        if (TryExpanderSet("mDomainBundleInbuilt.mKeyRotateASalts", &pExpander->GetDomainBundleInbuilt()->mKeyRotateASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mKeyRotateBSalts", &pExpander->GetDomainBundleInbuilt()->mKeyRotateBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mKeySpawnASalts", &pExpander->GetDomainBundleInbuilt()->mKeySpawnASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mKeySpawnBSalts", &pExpander->GetDomainBundleInbuilt()->mKeySpawnBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mSeedSalts", &pExpander->GetDomainBundleInbuilt()->mSeedSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mTwistSalts", &pExpander->GetDomainBundleInbuilt()->mTwistSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mKeyRotateASalts", &pExpander->GetDomainBundleEphemeral()->mKeyRotateASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mKeyRotateBSalts", &pExpander->GetDomainBundleEphemeral()->mKeyRotateBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mKeySpawnASalts", &pExpander->GetDomainBundleEphemeral()->mKeySpawnASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mKeySpawnBSalts", &pExpander->GetDomainBundleEphemeral()->mKeySpawnBSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mSeedSalts", &pExpander->GetDomainBundleEphemeral()->mSeedSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleEphemeral.mTwistSalts", &pExpander->GetDomainBundleEphemeral()->mTwistSalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mKeyASalts", &pExpander->GetDomainBundleInbuilt()->mKeyRotateASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mKeyBSalts", &pExpander->GetDomainBundleInbuilt()->mKeySpawnASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mMaskASalts", &pExpander->GetDomainBundleInbuilt()->mKeyRotateASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mMaskBSalts", &pExpander->GetDomainBundleInbuilt()->mKeySpawnASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mMaskLaneSalts", &pExpander->GetDomainBundleInbuilt()->mKeySpawnASalts)) { return true; }
        if (TryExpanderSet("mDomainBundleInbuilt.mSpiritLaneSalts", &pExpander->GetDomainBundleInbuilt()->mSeedSalts)) { return true; }
    }

    return false;
}

struct BranchRuntimePointers {
    std::uint8_t *pSource = nullptr;
    std::uint8_t *pDestination = nullptr;
    TwistFarmSalt *pFarmSalt = nullptr;
    TwistDomainConstants *pDomainConstants = nullptr;
    TwistDomainSaltSet *pDomainSaltSet = nullptr;
};

bool ResolveBufferPointerToken(const std::string &pToken,
                               TwistWorkSpace *pWorkSpace,
                               TwistExpander *pExpander,
                               const BranchRuntimePointers *pPointers,
                               std::uint8_t **pBufferResolved) {
    if ((pWorkSpace == nullptr) || (pExpander == nullptr) || (pBufferResolved == nullptr)) {
        return false;
    }

    std::string aToken = TrimCopy(pToken);
    if (!aToken.empty() && (aToken.back() == ';')) {
        aToken.pop_back();
        aToken = TrimCopy(aToken);
    }
    while (!aToken.empty() && ((aToken.front() == '&') || (aToken.front() == '*'))) {
        aToken.erase(aToken.begin());
        aToken = TrimCopy(aToken);
    }
    StripOuterParens(&aToken);

    if ((aToken == "mSource") || (aToken == "this->mSource") || (aToken == "pExpander->mSource")) {
        *pBufferResolved = (pPointers == nullptr) ? nullptr : pPointers->pSource;
        return *pBufferResolved != nullptr;
    }
    if ((aToken == "mDest") || (aToken == "this->mDest") || (aToken == "pExpander->mDest")) {
        *pBufferResolved = (pPointers == nullptr) ? nullptr : pPointers->pDestination;
        return *pBufferResolved != nullptr;
    }
    TwistWorkSpaceSlot aSlot = TwistWorkSpaceSlot::kInvalid;
    if (!ResolveAliasSlot(aToken, &aSlot)) {
        return false;
    }

    *pBufferResolved = TwistWorkSpace::GetBuffer(
        pWorkSpace,
        pExpander,
        aSlot,
        (pPointers == nullptr) ? nullptr : pPointers->pSource,
        (pPointers == nullptr) ? nullptr : pPointers->pDestination,
        (pPointers == nullptr) ? nullptr : pPointers->pDomainSaltSet);
    return *pBufferResolved != nullptr;
}

bool ExecuteKDFBufferAssignmentLine(const std::string &pLine,
                                    TwistWorkSpace *pWorkSpace,
                                    TwistExpander *pExpander,
                                    BranchRuntimePointers *pPointers,
                                    std::string *pErrorMessage) {
    std::string aLine = pLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimCopy(aLine);
    if (!aLine.empty() && (aLine.back() == ';')) {
        aLine.pop_back();
        aLine = TrimCopy(aLine);
    }
    const std::size_t aEqual = aLine.find('=');
    if (aEqual == std::string::npos) {
        return false;
    }

    const std::string aLeft = NormalizeRoundMaterialToken(aLine.substr(0U, aEqual));
    const std::string aRight = TrimCopy(aLine.substr(aEqual + 1U));
    if ((aLeft != "mSource") && (aLeft != "mDest")) {
        return false;
    }

    std::uint8_t *aBuffer = nullptr;
    if (!ResolveBufferPointerToken(aRight, pWorkSpace, pExpander, pPointers, &aBuffer)) {
        SetError(pErrorMessage, "KDF buffer assignment resolved null or unknown source: " + aRight);
        return false;
    }

    if (pPointers == nullptr) {
        SetError(pErrorMessage, "KDF buffer assignment had no runtime pointer context.");
        return false;
    }
    if (aLeft == "mSource") {
        pPointers->pSource = aBuffer;
    } else {
        pPointers->pDestination = aBuffer;
    }
    return true;
}

bool ExecuteFarmLine(const std::string &pLine,
                     TwistWorkSpace *pWorkSpace,
                     TwistExpander *pExpander,
                     const BranchRuntimePointers *pPointers,
                     std::string *pErrorMessage) {
    if (pLine.find("TwistFarm::Farm") == std::string::npos) {
        return false;
    }

    std::vector<std::string> aArgs;
    if (!ParseCryptoCallArguments(pLine, "Farm", &aArgs)) {
        return false;
    }
    if (aArgs.size() != 10U) {
        SetError(pErrorMessage, "TwistFarm::Farm expects exactly 10 arguments.");
        return false;
    }

    TwistFarmSalt *aFarmSalt = (pPointers == nullptr) ? nullptr : pPointers->pFarmSalt;
    if (aFarmSalt == nullptr) {
        SetError(pErrorMessage, "TwistFarm::Farm execution had no active farm.");
        return false;
    }

    if (TrimCopy(aArgs[0]) != "pFarmSalt") {
        SetError(pErrorMessage, "TwistFarm::Farm farm argument was invalid: " + aArgs[0]);
        return false;
    }

    std::uint8_t *aLanes[7] = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
    };
    for (std::size_t i = 0U; i < 7U; ++i) {
        if (!ResolveBufferPointerToken(aArgs[i + 1U],
                                       pWorkSpace,
                                       pExpander,
                                       pPointers,
                                       &aLanes[i])) {
            SetError(pErrorMessage,
                     "TwistFarm::Farm lane alias was invalid: " + aArgs[i + 1U]);
            return false;
        }
    }

    TwistDomainSaltSet *aSaltSet = nullptr;
    if (!ResolveSaltSetToken(aArgs[8], pWorkSpace, pExpander, &aSaltSet)) {
        SetError(pErrorMessage, "TwistFarm::Farm salt-set token was invalid: " + aArgs[8]);
        return false;
    }
    TwistDomainConstants *aConstants = nullptr;
    if (!ResolveConstantsToken(aArgs[9], pWorkSpace, pExpander, &aConstants)) {
        SetError(pErrorMessage, "TwistFarm::Farm constants token was invalid: " + aArgs[9]);
        return false;
    }

    TwistFarm::Farm(
        aFarmSalt,
        aLanes[0],
        aLanes[1],
        aLanes[2],
        aLanes[3],
        aLanes[4],
        aLanes[5],
        aLanes[6],
        aSaltSet,
        aConstants);
    return true;
}

bool ExecuteKDFLine(const std::string &pLine,
                    TwistWorkSpace *pWorkSpace,
                    TwistExpander *pExpander,
                    BranchRuntimePointers *pPointers,
                    std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                    std::string *pErrorMessage) {
    std::vector<std::string> aArgs;
    std::string aFunctionName;
    if (ParseCryptoCallArguments(pLine, "KDF_A", &aArgs)) {
        aFunctionName = "KDF_A";
    } else if (ParseCryptoCallArguments(pLine, "KDF_B", &aArgs)) {
        aFunctionName = "KDF_B";
    } else if (ParseCryptoCallArguments(pLine, "KDF_C", &aArgs)) {
        aFunctionName = "KDF_C";
    } else if (ParseCryptoCallArguments(pLine, "KDF_D", &aArgs)) {
        aFunctionName = "KDF_D";
    } else if (ParseCryptoCallArguments(pLine, "KDF", &aArgs)) {
        aFunctionName = "KDF";
    } else {
        return false;
    }

    if ((aFunctionName == "KDF_A") ||
        (aFunctionName == "KDF_B") ||
        (aFunctionName == "KDF_C") ||
        (aFunctionName == "KDF_D")) {
        if (!aArgs.empty() && (TrimCopy(aArgs.front()) == "pWorkSpace")) {
            aArgs.erase(aArgs.begin());
        }
    }

    if ((pWorkSpace == nullptr) || (pExpander == nullptr)) {
        SetError(pErrorMessage, "KDF call execution was missing required runtime inputs.");
        return false;
    }

    auto ResolveNonceToken = [&](const std::string &pToken,
                                 std::uint64_t *pNonceOut) -> bool {
        if (pNonceOut == nullptr) {
            return false;
        }
        const std::string aNonceToken = TrimCopy(pToken);
        if (aNonceToken == "pNonce") {
            *pNonceOut = 0ULL;
            if (pVariables != nullptr) {
                const auto aIterator = pVariables->find("pNonce");
                if (aIterator != pVariables->end()) {
                    *pNonceOut = static_cast<std::uint64_t>(aIterator->second);
                }
            }
            return true;
        }
        if (pVariables != nullptr) {
            const auto aIterator = pVariables->find(aNonceToken);
            if (aIterator != pVariables->end()) {
                *pNonceOut = static_cast<std::uint64_t>(aIterator->second);
                return true;
            }
        }

        char *aEnd = nullptr;
        const unsigned long long aParsed = std::strtoull(aNonceToken.c_str(), &aEnd, 0);
        if ((aEnd == nullptr) || (*aEnd != '\0')) {
            return false;
        }
        *pNonceOut = static_cast<std::uint64_t>(aParsed);
        return true;
    };

    bool aUsesKDFStateArguments = false;
    bool aUsesExplicitBuffers = false;
    bool aHasExplicitNonce = false;

    if ((aFunctionName == "KDF_A") ||
        (aFunctionName == "KDF_B") ||
        (aFunctionName == "KDF_C") ||
        (aFunctionName == "KDF_D")) {
        if (aArgs.size() != 16U) {
            SetError(pErrorMessage,
                     aFunctionName +
                     " call expects nonce, constants, salts, and thirteen "
                     "ARX state pointers.");
            return false;
        }
        aUsesKDFStateArguments = true;
        aHasExplicitNonce = true;
    } else {
        if ((aArgs.size() != 2U) && (aArgs.size() != 3U) &&
            (aArgs.size() != 4U) && (aArgs.size() != 5U)) {
            SetError(pErrorMessage,
                     "KDF call expects exactly 2, 3, 4, or 5 arguments.");
            return false;
        }
        aUsesExplicitBuffers = (aArgs.size() == 4U) || (aArgs.size() == 5U);
        aHasExplicitNonce = (aArgs.size() == 3U) || (aArgs.size() == 5U);
    }

    std::uint64_t aNonce = 0ULL;
    if (pVariables != nullptr) {
        const auto aNonceIterator = pVariables->find("pNonce");
        if (aNonceIterator != pVariables->end()) {
            aNonce = static_cast<std::uint64_t>(aNonceIterator->second);
        }
    }
    std::size_t aOffset = 0U;
    if (aHasExplicitNonce) {
        aOffset = 1U;
        if (!ResolveNonceToken(aArgs[0], &aNonce)) {
            SetError(pErrorMessage, "KDF nonce token was invalid: " + aArgs[0]);
            return false;
        }
    }
    if (aUsesExplicitBuffers) {
        std::uint8_t *aSource = nullptr;
        if (!ResolveBufferPointerToken(aArgs[aOffset + 0U], pWorkSpace, pExpander, pPointers, &aSource)) {
            SetError(pErrorMessage, "KDF source alias resolved to null or unknown: " + aArgs[aOffset + 0U]);
            return false;
        }
        std::uint8_t *aDest = nullptr;
        if (!ResolveBufferPointerToken(aArgs[aOffset + 1U], pWorkSpace, pExpander, pPointers, &aDest)) {
            SetError(pErrorMessage, "KDF destination alias resolved to null or unknown: " + aArgs[aOffset + 1U]);
            return false;
        }
        if (pPointers != nullptr) {
            pPointers->pSource = aSource;
            pPointers->pDestination = aDest;
        }
        aOffset += 2U;
    }

    TwistDomainConstants *aConstants = nullptr;
    if (!ResolveConstantsToken(aArgs[aOffset + 0U], pWorkSpace, pExpander, &aConstants)) {
        SetError(pErrorMessage, "KDF constants token was invalid: " + aArgs[aOffset + 0U]);
        return false;
    }
    TwistDomainSaltSet *aSaltSet = nullptr;
    if (!ResolveSaltSetToken(aArgs[aOffset + 1U], pWorkSpace, pExpander, &aSaltSet)) {
        SetError(pErrorMessage, "KDF salt-set token was invalid: " + aArgs[aOffset + 1U]);
        return false;
    }

    static const std::array<const char *, 13> kStateNames = {
        "aIngress", "aCarry",
        "aWandererA", "aWandererB", "aWandererC", "aWandererD",
        "aWandererE", "aWandererF", "aWandererG", "aWandererH",
        "aWandererI", "aWandererJ", "aWandererK",
    };
    std::array<std::uint64_t, kStateNames.size()> aState{};
    if (aUsesKDFStateArguments) {
        for (std::size_t i = 0U; i < kStateNames.size(); ++i) {
            std::string aStateToken = TrimCopy(aArgs[aOffset + 2U + i]);
            while (!aStateToken.empty() &&
                   ((aStateToken.front() == '&') ||
                    (aStateToken.front() == '*'))) {
                aStateToken.erase(aStateToken.begin());
                aStateToken = TrimCopy(aStateToken);
            }
            if (aStateToken != kStateNames[i]) {
                SetError(pErrorMessage,
                         aFunctionName +
                         " ARX state pointer order was invalid at " +
                         std::string(kStateNames[i]) + ".");
                return false;
            }
            if (pVariables != nullptr) {
                const auto aIterator = pVariables->find(kStateNames[i]);
                if (aIterator != pVariables->end()) {
                    aState[i] =
                        static_cast<std::uint64_t>(aIterator->second);
                }
            }
        }
    }

    auto StoreState = [&]() {
        if (pVariables == nullptr) {
            return;
        }
        for (std::size_t i = 0U; i < kStateNames.size(); ++i) {
            (*pVariables)[kStateNames[i]] =
                static_cast<GRuntimeScalar>(aState[i]);
        }
    };

    if (aFunctionName == "KDF_A") {
        pExpander->KDF_A(pWorkSpace,
                         aNonce,
                         aConstants,
                         aSaltSet,
                         &aState[0], &aState[1], &aState[2],
                         &aState[3], &aState[4], &aState[5], &aState[6],
                         &aState[7], &aState[8], &aState[9], &aState[10],
                         &aState[11], &aState[12]);
        StoreState();
    } else if (aFunctionName == "KDF_B") {
        pExpander->KDF_B(pWorkSpace,
                         aNonce,
                         aConstants,
                         aSaltSet,
                         &aState[0], &aState[1], &aState[2],
                         &aState[3], &aState[4], &aState[5], &aState[6],
                         &aState[7], &aState[8], &aState[9], &aState[10],
                         &aState[11], &aState[12]);
        StoreState();
    } else if (aFunctionName == "KDF_C") {
        pExpander->KDF_C(pWorkSpace,
                         aNonce,
                         aConstants,
                         aSaltSet,
                         &aState[0], &aState[1], &aState[2],
                         &aState[3], &aState[4], &aState[5], &aState[6],
                         &aState[7], &aState[8], &aState[9], &aState[10],
                         &aState[11], &aState[12]);
        StoreState();
    } else if (aFunctionName == "KDF_D") {
        pExpander->KDF_D(pWorkSpace,
                         aNonce,
                         aConstants,
                         aSaltSet,
                         &aState[0], &aState[1], &aState[2],
                         &aState[3], &aState[4], &aState[5], &aState[6],
                         &aState[7], &aState[8], &aState[9], &aState[10],
                         &aState[11], &aState[12]);
        StoreState();
    } else {
        pExpander->KDF(aNonce,
                       aConstants,
                       aSaltSet);
    }
    return true;
}

bool ApplyBranchStringLine(const std::string &pRawLine,
                           TwistWorkSpace *pWorkSpace,
                           TwistExpander *pExpander,
                           BranchRuntimePointers *pPointers,
                           std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                           std::string *pErrorMessage) {
    if ((pWorkSpace == nullptr) || (pVariables == nullptr)) {
        SetError(pErrorMessage, "Branch string-line execution had null inputs.");
        return false;
    }

    std::string aLineError;
    const bool aExecutedCrypto = ExecuteCryptoMakeLine(pRawLine, pWorkSpace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedCrypto) {
        return true;
    }

    const bool aExecutedCryptoSalt = ExecuteCryptoSaltLine(pRawLine, pWorkSpace, pExpander, &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedCryptoSalt) {
        return true;
    }

    const bool aExecutedKDFBufferAssignment = ExecuteKDFBufferAssignmentLine(
        pRawLine,
        pWorkSpace,
        pExpander,
        pPointers,
        &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedKDFBufferAssignment) {
        return true;
    }

    const bool aExecutedKDF = ExecuteKDFLine(
        pRawLine,
        pWorkSpace,
        pExpander,
        pPointers,
        pVariables,
        &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedKDF) {
        return true;
    }

    const bool aExecutedFarm = ExecuteFarmLine(
        pRawLine,
        pWorkSpace,
        pExpander,
        pPointers,
        &aLineError);
    if (!aLineError.empty()) {
        SetError(pErrorMessage, aLineError);
        return false;
    }
    if (aExecutedFarm) {
        return true;
    }

    std::string aHookLine = pRawLine;
    const std::size_t aHookComment = aHookLine.find("//");
    if (aHookComment != std::string::npos) {
        aHookLine = aHookLine.substr(0U, aHookComment);
    }
    aHookLine = TrimCopy(aHookLine);
    if (!aHookLine.empty() && aHookLine.back() == ';') {
        aHookLine.pop_back();
        aHookLine = TrimCopy(aHookLine);
    }
    std::string aRuntimeRawLine = pRawLine;
    const std::size_t aRuntimeComment = aRuntimeRawLine.find("//");
    if (aRuntimeComment != std::string::npos) {
        aRuntimeRawLine = aRuntimeRawLine.substr(0U, aRuntimeComment);
    }
    aRuntimeRawLine = TrimCopy(aRuntimeRawLine);
    if (!aRuntimeRawLine.empty() && aRuntimeRawLine.back() == ';') {
        aRuntimeRawLine.pop_back();
        aRuntimeRawLine = TrimCopy(aRuntimeRawLine);
    }
    if ((aRuntimeRawLine.rfind("TwistSquash::", 0U) == 0U) ||
        (aRuntimeRawLine.rfind("TwistDiffuse::", 0U) == 0U) ||
        (aRuntimeRawLine.rfind("TwistShiftBox::", 0U) == 0U) ||
        (aRuntimeRawLine.rfind("TwistShuffle::", 0U) == 0U) ||
        (aRuntimeRawLine.rfind("mMatrix.", 0U) == 0U)) {
        std::vector<GStatement> aRuntimeStatements;
        aRuntimeStatements.push_back(GStatement::RawLine(pRawLine));
        GBatch aRuntimeBatch;
        aRuntimeBatch.CommitStatements(&aRuntimeStatements);
        if (!aRuntimeBatch.ExecuteWithVariables(pWorkSpace, pExpander, pVariables, &aLineError)) {
            if (!aLineError.empty()) {
                SetError(pErrorMessage, aLineError);
            }
            return false;
        }
        return true;
    }

    std::string aLine = pRawLine;
    const std::size_t aComment = aLine.find("//");
    if (aComment != std::string::npos) {
        aLine = aLine.substr(0U, aComment);
    }
    aLine = TrimCopy(aLine);
    if (aLine.empty()) {
        return true;
    }

    if (!aLine.empty() && aLine.back() == ';') {
        aLine.pop_back();
        aLine = TrimCopy(aLine);
    }
    if (aLine.empty()) {
        return true;
    }

    const std::size_t aEqual = aLine.find('=');
    if (aEqual == std::string::npos) {
        return true;
    }

    std::string aLeft = TrimCopy(aLine.substr(0U, aEqual));
    std::string aRight = TrimCopy(aLine.substr(aEqual + 1U));
    if (aLeft.empty() || aRight.empty()) {
        return true;
    }

    if ((aLeft.find('*') != std::string::npos) ||
        (aLeft.find('[') != std::string::npos) ||
        (aLeft.find('(') != std::string::npos) ||
        (aLeft.find(')') != std::string::npos)) {
        return true;
    }

    const std::size_t aLastSpace = aLeft.find_last_of(" \t");
    const std::string aName = (aLastSpace == std::string::npos)
        ? aLeft
        : TrimCopy(aLeft.substr(aLastSpace + 1U));
    if (!IsIdentifier(aName)) {
        return true;
    }

    GRuntimeScalar aDomainAssignmentValue = 0ULL;
    if (ResolveDomainWordAssignmentValue(aRight,
                                         pWorkSpace,
                                         (pPointers == nullptr)
                                             ? nullptr
                                             : pPointers->pDomainConstants,
                                         *pVariables,
                                         &aDomainAssignmentValue)) {
        (*pVariables)[aName] = aDomainAssignmentValue;
        return true;
    }

    int aValue = 0;
    if (!ParseIntLiteral(aRight, &aValue)) {
        return true;
    }

    (*pVariables)[aName] = static_cast<GRuntimeScalar>(aValue);
    return true;
}

bool ApplyBranchStringLines(const std::vector<std::string> &pLines,
                            TwistWorkSpace *pWorkSpace,
                            TwistExpander *pExpander,
                            BranchRuntimePointers *pPointers,
                            std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                            std::string *pErrorMessage) {
    for (const std::string &aRawLine : pLines) {
        if (!ApplyBranchStringLine(aRawLine,
                                   pWorkSpace,
                                   pExpander,
                                   pPointers,
                                   pVariables,
                                   pErrorMessage)) {
            return false;
        }
    }
    return true;
}

bool ExecuteBatchJsonByIndex(const TwistProgramBranch &pBranch,
                             std::size_t pBatchIndex,
                             TwistWorkSpace *pWorkSpace,
                             TwistExpander *pExpander,
                             TwistDomainSaltSet *pParamSaltSet,
                             std::unordered_map<std::string, GRuntimeScalar> *pVariables,
                             std::string *pErrorMessage) {
    if (pBatchIndex >= pBranch.GetBatchJsonText().size()) {
        SetError(pErrorMessage, "Branch batch step index was out of range during execution.");
        return false;
    }

    GBatch aBatch;
    if (!GBatch::FromJson(pBranch.GetBatchJsonText()[pBatchIndex], &aBatch, pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "Failed to parse branch batch JSON.";
        }
        return false;
    }

    if (!aBatch.ExecuteWithRuntimeVariables(pWorkSpace,
                                            pExpander,
                                            pParamSaltSet,
                                            pVariables,
                                            pErrorMessage)) {
        if ((pErrorMessage != nullptr) && pErrorMessage->empty()) {
            *pErrorMessage = "Branch batch execution failed.";
        }
        return false;
    }

    return true;
}

[[maybe_unused]] bool ExecuteBranch(const TwistProgramBranch &pBranch,
                                    TwistWorkSpace *pWorkSpace,
                                    TwistExpander *pExpander,
                                    TwistFarmSalt *pFarmSalt,
                                    std::uint8_t *pSource,
                                    std::uint8_t *pDestination,
                                    TwistDomainConstants *pDomainConstants,
                                    TwistDomainSaltSet *pDomainSaltSet,
                                    const std::unordered_map<std::string, GRuntimeScalar> *pInitialVariables,
                                    std::string *pErrorMessage) {
    if (pWorkSpace == nullptr) {
        SetError(pErrorMessage, "Branch execution received a null workspace.");
        return false;
    }

    std::unordered_map<std::string, GRuntimeScalar> aVariables;
    if (pInitialVariables != nullptr) {
        aVariables = *pInitialVariables;
    }
    BranchRuntimePointers aPointers;
    aPointers.pSource = pSource;
    aPointers.pDestination = pDestination;
    aPointers.pFarmSalt = pFarmSalt;
    aPointers.pDomainConstants = pDomainConstants;
    aPointers.pDomainSaltSet = pDomainSaltSet;
    const std::vector<TwistProgramBranchStep> &aSteps = pBranch.GetSteps();
    if (aSteps.empty()) {
        if (!ApplyBranchStringLines(pBranch.GetStringLines(),
                                    pWorkSpace,
                                    pExpander,
                                    &aPointers,
                                    &aVariables,
                                    pErrorMessage)) {
            return false;
        }
        return ExecuteBatchJsonText(pBranch.GetBatchJsonText(),
                                    pWorkSpace,
                                    pExpander,
                                    pDomainSaltSet,
                                    &aVariables,
                                    pErrorMessage);
    }

    for (const TwistProgramBranchStep &aStep : aSteps) {
        if (aStep.mType == TwistProgramBranchStepType::kLine) {
            if (aStep.mIndex >= pBranch.GetStringLines().size()) {
                SetError(pErrorMessage, "Branch line step index was out of range during execution.");
                return false;
            }
            if (!ApplyBranchStringLine(pBranch.GetStringLines()[aStep.mIndex],
                                       pWorkSpace,
                                       pExpander,
                                       &aPointers,
                                       &aVariables,
                                       pErrorMessage)) {
                return false;
            }
            continue;
        }

        if (aStep.mType == TwistProgramBranchStepType::kBatch) {
            if (!ExecuteBatchJsonByIndex(pBranch,
                                         aStep.mIndex,
                                         pWorkSpace,
                                         pExpander,
                                         pDomainSaltSet,
                                         &aVariables,
                                         pErrorMessage)) {
                return false;
            }
            continue;
        }

        SetError(pErrorMessage, "Branch step type was invalid during execution.");
        return false;
    }

    return true;
}

} // namespace

GTwistExpander::GTwistExpander()
: TwistExpander() {
    mNameBase = "Generated";

    RandomizeDomainBundleConstants(&mDomainBundleInbuilt);
    SaltTables::InjectRandomDomains(this);
    RefreshTablePointers();
}

GTwistExpander::~GTwistExpander() {

}

void GTwistExpander::RefreshTablePointers() {
}

void GTwistExpander::KDF(std::uint64_t pNonce,
                         TwistDomainConstants *pDomainConstants,
                         TwistDomainSaltSet *pDomainSaltSet) {
    (void)pNonce;
    (void)pDomainConstants;
    (void)pDomainSaltSet;
}

void GTwistExpander::KDF_A(TwistWorkSpace *pWorkSpace,
                           std::uint64_t pNonce,
                           TwistDomainConstants *pDomainConstants,
                           TwistDomainSaltSet *pDomainSaltSet,
                           MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pNonce;
    (void)pDomainConstants;
    (void)pDomainSaltSet;
    (void)pIngress;
    (void)pCarry;
    (void)pWandererA;
    (void)pWandererB;
    (void)pWandererC;
    (void)pWandererD;
    (void)pWandererE;
    (void)pWandererF;
    (void)pWandererG;
    (void)pWandererH;
    (void)pWandererI;
    (void)pWandererJ;
    (void)pWandererK;
}

void GTwistExpander::KDF_B(TwistWorkSpace *pWorkSpace,
                           std::uint64_t pNonce,
                           TwistDomainConstants *pDomainConstants,
                           TwistDomainSaltSet *pDomainSaltSet,
                           MUTABLE_PARAMS) {
    KDF_A(pWorkSpace,
          pNonce,
          pDomainConstants,
          pDomainSaltSet,
          MUTABLE_PARAMS_PASSED);
}

void GTwistExpander::KDF_C(TwistWorkSpace *pWorkSpace,
                           std::uint64_t pNonce,
                           TwistDomainConstants *pDomainConstants,
                           TwistDomainSaltSet *pDomainSaltSet,
                           MUTABLE_PARAMS) {
    KDF_A(pWorkSpace,
          pNonce,
          pDomainConstants,
          pDomainSaltSet,
          MUTABLE_PARAMS_PASSED);
}

void GTwistExpander::KDF_D(TwistWorkSpace *pWorkSpace,
                           std::uint64_t pNonce,
                           TwistDomainConstants *pDomainConstants,
                           TwistDomainSaltSet *pDomainSaltSet,
                           MUTABLE_PARAMS) {
    KDF_A(pWorkSpace,
          pNonce,
          pDomainConstants,
          pDomainSaltSet,
          MUTABLE_PARAMS_PASSED);
}

void GTwistExpander::Seed(TwistWorkSpace *pWorkSpace,
                          TwistFarmSalt *pFarmSalt,
                          std::uint64_t pNonce,
                          std::uint8_t *pPassword,
                          std::size_t pPasswordByteLength,
                          std::uint8_t *pDestination) {
    RefreshTablePointers();
    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr) ||
        (pDestination == nullptr)) {
        return;
    }
    UnrollPassword(pWorkSpace->mSourceLane,
                   pPassword,
                   pPasswordByteLength);
    UnrollNonce(pWorkSpace->mNonceLane, pNonce);
    mDomainBundleEphemeral.Zero();
    pWorkSpace->mDomainBundle.Zero();
}

void GTwistExpander::TwistBlock(TwistWorkSpace *pWorkSpace,
                                std::uint8_t *pSource,
                                std::uint8_t *pCrossLaneA,
                                std::uint8_t *pCrossLaneB,
                                std::uint8_t *pCrossLaneC,
                                std::uint8_t *pCrossLaneD,
                                std::uint8_t *pDestination) {
    (void)pWorkSpace;
    (void)pSource;
    (void)pCrossLaneA;
    (void)pCrossLaneB;
    (void)pCrossLaneC;
    (void)pCrossLaneD;
    (void)pDestination;
}

void GTwistExpander::GrowKeyA(TwistWorkSpace *pWorkSpace,
                              MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pIngress;
    (void)pCarry;
    (void)pWandererA;
    (void)pWandererB;
    (void)pWandererC;
    (void)pWandererD;
    (void)pWandererE;
    (void)pWandererF;
    (void)pWandererG;
    (void)pWandererH;
    (void)pWandererI;
    (void)pWandererJ;
    (void)pWandererK;
}

void GTwistExpander::GrowKeyB(TwistWorkSpace *pWorkSpace,
                              MUTABLE_PARAMS) {
    (void)pWorkSpace;
    (void)pIngress;
    (void)pCarry;
    (void)pWandererA;
    (void)pWandererB;
    (void)pWandererC;
    (void)pWandererD;
    (void)pWandererE;
    (void)pWandererF;
    (void)pWandererG;
    (void)pWandererH;
    (void)pWandererI;
    (void)pWandererJ;
    (void)pWandererK;
}

bool GTwistExpander::LoadJSONProjectRoot(const std::string &pJsonPath,
                                         std::string *pErrorMessage) {
    (void)pJsonPath;
    SetError(pErrorMessage, "GTwistExpander JSON loading has been removed; export and use generated C++ instead.");
    return false;
}
