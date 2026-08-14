//
//  GFarm.hpp
//  MeanMachine
//

#ifndef GFarm_hpp
#define GFarm_hpp

#include "GKDF.hpp"

#include <string>
#include <vector>

class GFarm {
public:
    bool                                Bake(GKDFMaterialBundle pBundle,
                                             GSymbol pBufferSymbolLaneA,
                                             GSymbol pBufferSymbolLaneB,
                                             GSymbol pBufferSymbolLaneC,
                                             GSymbol pBufferSymbolLaneD,
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
        if (!ValidateSource(pBufferSymbolLaneA, "lane A constants", pErrorMessage) ||
            !ValidateSource(pBufferSymbolLaneB, "lane B salts", pErrorMessage) ||
            !ValidateSource(pBufferSymbolLaneC, "lane C salts", pErrorMessage) ||
            !ValidateSource(pBufferSymbolLaneD, "lane D salts", pErrorMessage)) {
            return false;
        }

        const std::string aPhaseMember = NormalizePhaseSubWord(pPhaseSubWord);
        if (aPhaseMember.empty()) {
            SetError(pErrorMessage,
                     "GFarm::Bake requires KeyRotateA, KeyRotateB, "
                     "KeySpawnA, KeySpawnB, Seed, or Twist.");
            return false;
        }

        const std::string aBundlePrefix = BundlePrefix(pBundle);
        if (aBundlePrefix.empty()) {
            SetError(pErrorMessage, "GFarm::Bake requires inbuilt, ephemeral, or workspace bundle.");
            return false;
        }

        const std::string aSaltSet = aBundlePrefix + "." + aPhaseMember + "Salts";
        AddFarm(BufAliasName(pBufferSymbolLaneB),
                BufAliasName(pBufferSymbolLaneC),
                BufAliasName(pBufferSymbolLaneD),
                BufAliasName(pBufferSymbolLaneA),
                aSaltSet,
                aBundlePrefix + "." + aPhaseMember + "Constants",
                pStatements);
        return true;
    }

    bool                                BakeEphemeralA(GSymbol pBufferSymbolLaneA,
                                                       GSymbol pBufferSymbolLaneB,
                                                       GSymbol pBufferSymbolLaneC,
                                                       GSymbol pBufferSymbolLaneD,
                                                       const std::string &pPhaseSubWord,
                                                       std::vector<GStatement> *pStatements,
                                                       std::string *pErrorMessage) const {
        return Bake(GKDFMaterialBundle::kEphemeralA,
                    pBufferSymbolLaneA,
                    pBufferSymbolLaneB,
                    pBufferSymbolLaneC,
                    pBufferSymbolLaneD,
                    pPhaseSubWord,
                    pStatements,
                    pErrorMessage);
    }

    bool                                BakeEphemeralB(GSymbol pBufferSymbolLaneA,
                                                       GSymbol pBufferSymbolLaneB,
                                                       GSymbol pBufferSymbolLaneC,
                                                       GSymbol pBufferSymbolLaneD,
                                                       const std::string &pPhaseSubWord,
                                                       std::vector<GStatement> *pStatements,
                                                       std::string *pErrorMessage) const {
        return Bake(GKDFMaterialBundle::kEphemeralB,
                    pBufferSymbolLaneA,
                    pBufferSymbolLaneB,
                    pBufferSymbolLaneC,
                    pBufferSymbolLaneD,
                    pPhaseSubWord,
                    pStatements,
                    pErrorMessage);
    }

    bool                                BakeWorkspace(GSymbol pBufferSymbolLaneA,
                                                      GSymbol pBufferSymbolLaneB,
                                                      GSymbol pBufferSymbolLaneC,
                                                      GSymbol pBufferSymbolLaneD,
                                                      const std::string &pPhaseSubWord,
                                                      std::vector<GStatement> *pStatements,
                                                      std::string *pErrorMessage) const {
        return Bake(GKDFMaterialBundle::kWorkspace,
                    pBufferSymbolLaneA,
                    pBufferSymbolLaneB,
                    pBufferSymbolLaneC,
                    pBufferSymbolLaneD,
                    pPhaseSubWord,
                    pStatements,
                    pErrorMessage);
    }

    bool                                BakeInbuilt(GSymbol pBufferSymbolLaneA,
                                                    GSymbol pBufferSymbolLaneB,
                                                    GSymbol pBufferSymbolLaneC,
                                                    GSymbol pBufferSymbolLaneD,
                                                    const std::string &pPhaseSubWord,
                                                    std::vector<GStatement> *pStatements,
                                                    std::string *pErrorMessage) const {
        return Bake(GKDFMaterialBundle::kInbuilt,
                    pBufferSymbolLaneA,
                    pBufferSymbolLaneB,
                    pBufferSymbolLaneC,
                    pBufferSymbolLaneD,
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
            case GKDFMaterialBundle::kEphemeralA:
                return "mDomainBundleEphemeralA";
            case GKDFMaterialBundle::kEphemeralB:
                return "mDomainBundleEphemeralB";
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

        if ((pPhaseSubWord == "A") || (pPhaseSubWord == "PhaseA") ||
            (pPhaseSubWord == "mPhaseA") || (pPhaseSubWord == "KeyRotate") ||
            (pPhaseSubWord == "mKeyRotate") ||
            (pPhaseSubWord == "KeyRotateA") ||
            (pPhaseSubWord == "mKeyRotateA")) {
            return "mKeyRotateA";
        }
        if ((pPhaseSubWord == "B") || (pPhaseSubWord == "PhaseB") ||
            (pPhaseSubWord == "mPhaseB") || (pPhaseSubWord == "KeySpawn") ||
            (pPhaseSubWord == "mKeySpawn") ||
            (pPhaseSubWord == "KeySpawnA") ||
            (pPhaseSubWord == "mKeySpawnA")) {
            return "mKeySpawnA";
        }
        if ((pPhaseSubWord == "KeyRotateB") ||
            (pPhaseSubWord == "mKeyRotateB")) {
            return "mKeyRotateB";
        }
        if ((pPhaseSubWord == "KeySpawnB") ||
            (pPhaseSubWord == "mKeySpawnB")) {
            return "mKeySpawnB";
        }
        if ((pPhaseSubWord == "C") || (pPhaseSubWord == "PhaseC") ||
            (pPhaseSubWord == "mPhaseC") || (pPhaseSubWord == "Seed") ||
            (pPhaseSubWord == "mSeed")) {
            return "mSeed";
        }
        if ((pPhaseSubWord == "D") || (pPhaseSubWord == "PhaseD") ||
            (pPhaseSubWord == "mPhaseD") || (pPhaseSubWord == "Twist") ||
            (pPhaseSubWord == "mTwist")) {
            return "mTwist";
        }
        return "";
    }

    static void                         AddFarm(const std::string &pSaltLaneA,
                                                const std::string &pSaltLaneB,
                                                const std::string &pSaltLaneC,
                                                const std::string &pConstantLane,
                                                const std::string &pSaltSet,
                                                const std::string &pConstants,
                                                std::vector<GStatement> *pStatements) {
        pStatements->push_back(GStatement::RawLine(
            "TwistFarm::Farm(pFarmSalt,\n"
            "                " +
            pSaltLaneA + ", " +
            pSaltLaneB + ", " +
            pSaltLaneC + ", " +
            pConstantLane + ", // farm lanes\n"
            "                aStasisLaneA, aStasisLaneB, aStasisLaneC, // temp/fold lanes\n"
            "                &" +
            pSaltSet + ",\n"
            "                &(" +
            pConstants + "));"));
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
