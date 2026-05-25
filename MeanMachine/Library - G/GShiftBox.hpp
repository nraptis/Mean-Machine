//
//  GShiftBox.hpp
//  MeanMachine
//

#ifndef GShiftBox_hpp
#define GShiftBox_hpp

#include "GSeedProgram.hpp"

#include <string>
#include <vector>

class GShiftBox {
public:
    bool BakeShiftKeyBoxA(std::vector<GStatement> *pStatements,
                          std::string *pErrorMessage) const {
        return BakeShiftCall("ShiftKeyBoxA", pStatements, pErrorMessage);
    }

    bool BakeShiftKeyBoxB(std::vector<GStatement> *pStatements,
                          std::string *pErrorMessage) const {
        return BakeShiftCall("ShiftKeyBoxB", pStatements, pErrorMessage);
    }

    bool BakeShiftMaskBoxA(std::vector<GStatement> *pStatements,
                           std::string *pErrorMessage) const {
        return BakeShiftCall("ShiftMaskBoxA", pStatements, pErrorMessage);
    }

    bool BakeShiftMaskBoxB(std::vector<GStatement> *pStatements,
                           std::string *pErrorMessage) const {
        return BakeShiftCall("ShiftMaskBoxB", pStatements, pErrorMessage);
    }

private:
    bool BakeShiftCall(const char *pMethodName,
                       std::vector<GStatement> *pStatements,
                       std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GShiftBox output statement list was null.");
            return false;
        }

        pStatements->push_back(GStatement::RawLine(std::string("TwistShiftBox::") + pMethodName + "(pWorkSpace);"));
        return true;
    }

    static void SetError(std::string *pErrorMessage,
                         const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }
};

#endif /* GShiftBox_hpp */
