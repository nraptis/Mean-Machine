//
//  GInvest.hpp
//  MeanMachine
//

#ifndef GInvest_hpp
#define GInvest_hpp

#include "GSeedProgram.hpp"

#include <string>
#include <vector>

class GInvest {
public:
    bool BakeInvestBlockKeyBoxA(GSymbol pSource,
                                std::vector<GStatement> *pStatements,
                                std::string *pErrorMessage) const {
        return BakeInvestCall("InvestBlockKeyBoxA", pSource, pStatements, pErrorMessage);
    }

    bool BakeInvestBlockKeyBoxB(GSymbol pSource,
                                std::vector<GStatement> *pStatements,
                                std::string *pErrorMessage) const {
        return BakeInvestCall("InvestBlockKeyBoxB", pSource, pStatements, pErrorMessage);
    }

    bool BakeInvestBlockMaskBoxA(GSymbol pSource,
                                 std::vector<GStatement> *pStatements,
                                 std::string *pErrorMessage) const {
        return BakeInvestCall("InvestBlockMaskBoxA", pSource, pStatements, pErrorMessage);
    }

    bool BakeInvestBlockMaskBoxB(GSymbol pSource,
                                 std::vector<GStatement> *pStatements,
                                 std::string *pErrorMessage) const {
        return BakeInvestCall("InvestBlockMaskBoxB", pSource, pStatements, pErrorMessage);
    }

private:
    bool BakeInvestCall(const char *pMethodName,
                        GSymbol pSource,
                        std::vector<GStatement> *pStatements,
                        std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GInvest output statement list was null.");
            return false;
        }
        if (!pSource.IsBuf()) {
            SetError(pErrorMessage, "GInvest source must be a buffer symbol.");
            return false;
        }

        const int aSourceLength = pSource.mKey.IsValid()
            ? TwistWorkSpace::GetBufferLength(pSource.mKey)
            : TwistWorkSpace::GetBufferLength(pSource.mSlot);
        if (aSourceLength != S_BLOCK) {
            SetError(pErrorMessage, "GInvest source must resolve to a block-sized buffer.");
            return false;
        }

        const std::string aLine = std::string("TwistInvest::") + pMethodName + "(" +
            BufAliasName(pSource) + ", pWorkSpace);";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }

    static void SetError(std::string *pErrorMessage,
                         const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }
};

#endif /* GInvest_hpp */
