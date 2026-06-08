//
//  GFarm.hpp
//  MeanMachine
//

#ifndef GFarm_hpp
#define GFarm_hpp

#include "GFarmConstants.hpp"
#include "GKDF.hpp"

#include <string>
#include <vector>

class GFarm {
public:
    bool                                Bake(GKDFMaterialBundle pBundle,
                                             GSymbol pBufferSymbolOrbiterAssign,
                                             GSymbol pBufferSymbolOrbiterUpdate,
                                             GSymbol pBufferSymbolWandererUpdate,
                                             GSymbol pBufferSymbolConstants,
                                             const std::string &pPhaseSubWord,
                                             std::vector<GStatement> *pStatements,
                                             std::string *pErrorMessage) const {
        if (pErrorMessage != nullptr) {
            pErrorMessage->clear();
        }

        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GFarm::Bake requires statement output.");
            return false;
        }
        if (!ValidateSource(pBufferSymbolOrbiterAssign, "orbiter assign", pErrorMessage) ||
            !ValidateSource(pBufferSymbolOrbiterUpdate, "orbiter update", pErrorMessage) ||
            !ValidateSource(pBufferSymbolWandererUpdate, "wanderer update", pErrorMessage) ||
            !ValidateSource(pBufferSymbolConstants, "constants", pErrorMessage)) {
            return false;
        }

        const std::string aPhaseMember = NormalizePhaseSubWord(pPhaseSubWord);
        if (aPhaseMember.empty()) {
            SetError(pErrorMessage, "GFarm::Bake requires phase sub-word PhaseA, PhaseB, PhaseC, or PhaseD.");
            return false;
        }

        const std::string aBundlePrefix = BundlePrefix(pBundle);
        if (aBundlePrefix.empty()) {
            SetError(pErrorMessage, "GFarm::Bake requires inbuilt, ephemeral, or workspace bundle.");
            return false;
        }

        const std::string aSaltSet = aBundlePrefix + "." + aPhaseMember + "Salts";
        AddFarmSaltRound(BufAliasName(pBufferSymbolOrbiterAssign),
                         aSaltSet + ".mOrbiterAssign",
                         pStatements);
        AddFarmSaltRound(BufAliasName(pBufferSymbolOrbiterUpdate),
                         aSaltSet + ".mOrbiterUpdate",
                         pStatements);
        AddFarmSaltRound(BufAliasName(pBufferSymbolWandererUpdate),
                         aSaltSet + ".mWandererUpdate",
                         pStatements);

        GFarmConstants aFarmConstants;
        return aFarmConstants.Bake(BufAliasName(pBufferSymbolConstants),
                                   aBundlePrefix + "." + aPhaseMember + "Constants",
                                   pStatements,
                                   pErrorMessage);
    }

    bool                                BakeEphemeral(GSymbol pBufferSymbolOrbiterAssign,
                                                      GSymbol pBufferSymbolOrbiterUpdate,
                                                      GSymbol pBufferSymbolWandererUpdate,
                                                      GSymbol pBufferSymbolConstants,
                                                      const std::string &pPhaseSubWord,
                                                      std::vector<GStatement> *pStatements,
                                                      std::string *pErrorMessage) const {
        return Bake(GKDFMaterialBundle::kEphemeral,
                    pBufferSymbolOrbiterAssign,
                    pBufferSymbolOrbiterUpdate,
                    pBufferSymbolWandererUpdate,
                    pBufferSymbolConstants,
                    pPhaseSubWord,
                    pStatements,
                    pErrorMessage);
    }

    bool                                BakeWorkspace(GSymbol pBufferSymbolOrbiterAssign,
                                                      GSymbol pBufferSymbolOrbiterUpdate,
                                                      GSymbol pBufferSymbolWandererUpdate,
                                                      GSymbol pBufferSymbolConstants,
                                                      const std::string &pPhaseSubWord,
                                                      std::vector<GStatement> *pStatements,
                                                      std::string *pErrorMessage) const {
        return Bake(GKDFMaterialBundle::kWorkspace,
                    pBufferSymbolOrbiterAssign,
                    pBufferSymbolOrbiterUpdate,
                    pBufferSymbolWandererUpdate,
                    pBufferSymbolConstants,
                    pPhaseSubWord,
                    pStatements,
                    pErrorMessage);
    }

    bool                                BakeInbuilt(GSymbol pBufferSymbolOrbiterAssign,
                                                    GSymbol pBufferSymbolOrbiterUpdate,
                                                    GSymbol pBufferSymbolWandererUpdate,
                                                    GSymbol pBufferSymbolConstants,
                                                    const std::string &pPhaseSubWord,
                                                    std::vector<GStatement> *pStatements,
                                                    std::string *pErrorMessage) const {
        return Bake(GKDFMaterialBundle::kInbuilt,
                    pBufferSymbolOrbiterAssign,
                    pBufferSymbolOrbiterUpdate,
                    pBufferSymbolWandererUpdate,
                    pBufferSymbolConstants,
                    pPhaseSubWord,
                    pStatements,
                    pErrorMessage);
    }

private:
    static bool                         ValidateSource(GSymbol pSymbol,
                                                       const char *pName,
                                                       std::string *pErrorMessage) {
        if (!pSymbol.IsBuf()) {
            SetError(pErrorMessage, std::string("GFarm ") + pName + " source must be a buffer symbol.");
            return false;
        }

        const int aLength = pSymbol.mKey.IsValid()
            ? TwistWorkSpace::GetBufferLength(pSymbol.mKey)
            : TwistWorkSpace::GetBufferLength(pSymbol.mSlot);
        if (aLength <= 0) {
            SetError(pErrorMessage, std::string("GFarm ") + pName + " source resolved to an empty buffer.");
            return false;
        }
        return true;
    }

    static std::string                  BundlePrefix(GKDFMaterialBundle pBundle) {
        switch (pBundle) {
            case GKDFMaterialBundle::kInbuilt:
                return "mDomainBundleInbuilt";
            case GKDFMaterialBundle::kEphemeral:
                return "mDomainBundleEphemeral";
            case GKDFMaterialBundle::kWorkspace:
                return "pWorkSpace->mDomainBundle";
            default:
                return "";
        }
    }

    static std::string                  NormalizePhaseSubWord(std::string pPhaseSubWord) {
        pPhaseSubWord = Trim(pPhaseSubWord);
        const std::size_t aDot = pPhaseSubWord.rfind('.');
        if (aDot != std::string::npos) {
            pPhaseSubWord = Trim(pPhaseSubWord.substr(aDot + 1U));
        }

        StripSuffix(&pPhaseSubWord, "Constants");
        StripSuffix(&pPhaseSubWord, "Salts");
        pPhaseSubWord = Trim(pPhaseSubWord);

        if ((pPhaseSubWord == "A") ||
            (pPhaseSubWord == "B") ||
            (pPhaseSubWord == "C") ||
            (pPhaseSubWord == "D")) {
            pPhaseSubWord = "Phase" + pPhaseSubWord;
        }
        if (pPhaseSubWord.rfind("m", 0U) != 0U) {
            pPhaseSubWord = "m" + pPhaseSubWord;
        }

        if ((pPhaseSubWord == "mPhaseA") ||
            (pPhaseSubWord == "mPhaseB") ||
            (pPhaseSubWord == "mPhaseC") ||
            (pPhaseSubWord == "mPhaseD")) {
            return pPhaseSubWord;
        }
        return "";
    }

    static void                         AddFarmSaltRound(const std::string &pSource,
                                                         const std::string &pRound,
                                                         std::vector<GStatement> *pStatements) {
        pStatements->push_back(GStatement::RawLine(
            "pFarmSalt->Derive(" + pSource + ", " +
            pRound + ".mSaltA, " +
            pRound + ".mSaltB, " +
            pRound + ".mSaltC, " +
            pRound + ".mSaltD, " +
            pRound + ".mSaltE, " +
            pRound + ".mSaltF);"));
    }

    static std::string                  Trim(const std::string &pText) {
        std::size_t aBegin = 0U;
        while ((aBegin < pText.size()) && IsSpace(pText[aBegin])) {
            ++aBegin;
        }
        std::size_t aEnd = pText.size();
        while ((aEnd > aBegin) && IsSpace(pText[aEnd - 1U])) {
            --aEnd;
        }
        return pText.substr(aBegin, aEnd - aBegin);
    }

    static bool                         IsSpace(char pChar) {
        return (pChar == ' ') ||
               (pChar == '\t') ||
               (pChar == '\n') ||
               (pChar == '\r') ||
               (pChar == '\f') ||
               (pChar == '\v');
    }

    static void                         StripSuffix(std::string *pText,
                                                    const char *pSuffix) {
        if ((pText == nullptr) || (pSuffix == nullptr)) {
            return;
        }
        const std::string aSuffix(pSuffix);
        if ((pText->size() >= aSuffix.size()) &&
            (pText->compare(pText->size() - aSuffix.size(), aSuffix.size(), aSuffix) == 0)) {
            pText->erase(pText->size() - aSuffix.size());
        }
    }

    static void                         SetError(std::string *pErrorMessage,
                                                 const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }
};

#endif /* GFarm_hpp */
