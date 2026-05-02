//
//  GSnow.hpp
//  MeanMachine
//

#ifndef GSnow_hpp
#define GSnow_hpp

#include "GSeedProgram.hpp"

class GSnow {
public:
    bool BakeAES256(GSymbol pSource,
                    GSymbol pDest,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        return BakeCounterCall("AES256Counter", pSource, pDest, pStatements, pErrorMessage);
    }

    bool BakeChaCha20(GSymbol pSource,
                      GSymbol pDest,
                      std::vector<GStatement> *pStatements,
                      std::string *pErrorMessage) const {
        return BakeCounterCall("ChaCha20Counter", pSource, pDest, pStatements, pErrorMessage);
    }

    bool BakeSha256(GSymbol pSource,
                    GSymbol pDest,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        return BakeCounterCall("Sha256Counter", pSource, pDest, pStatements, pErrorMessage);
    }

    bool BakeAria256(GSymbol pSource,
                     GSymbol pDest,
                     std::vector<GStatement> *pStatements,
                     std::string *pErrorMessage) const {
        return BakeCounterCall("Aria256Counter", pSource, pDest, pStatements, pErrorMessage);
    }

private:
    static void SetError(std::string *pErrorMessage,
                         const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }

    static bool BakeCounterCall(const char *pMethodName,
                                GSymbol pSource,
                                GSymbol pDest,
                                std::vector<GStatement> *pStatements,
                                std::string *pErrorMessage) {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GSnow output statement list was null.");
            return false;
        }
        if (!pSource.IsBuf()) {
            SetError(pErrorMessage, "GSnow source must be a buffer symbol.");
            return false;
        }
        if (!pDest.IsBuf()) {
            SetError(pErrorMessage, "GSnow destination must be a buffer symbol.");
            return false;
        }
        if (pMethodName == nullptr || pMethodName[0] == '\0') {
            SetError(pErrorMessage, "GSnow method name was invalid.");
            return false;
        }

        const std::string aLine = std::string("TwistSnow::") + pMethodName + "(" +
            BufAliasName(pSource.mSlot) + ", " +
            BufAliasName(pDest.mSlot) + ");";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }
};

#endif /* GSnow_hpp */
