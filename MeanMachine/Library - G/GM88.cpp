//
//  GM88.cpp
//  MeanMachine
//
//  Created by nick raptis on 6/8/26.
//

#include "GM88.hpp"

GM88::GM88() {
    
}


void GM88::Clear() {
    
}

bool GM88::BakeDispatch(GSymbol pOperation,
                        GExpr pOperationIndex,
                        GSymbol pSource,
                        GExpr pSourceIndex,
                        GSymbol pDestination,
                        GExpr pDestinationIndex,
                        GExpr pUnrollDomainWord,
                        GExpr pArgADomainWord,
                        GExpr pArgBDomainWord,
                        GExpr pArgCDomainWord,
                        GExpr pArgDDomainWord,
                        std::vector<GStatement> *pStatements,
                        std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GM88::BakeDispatch output statement list was null.");
        return false;
    }
    if (pOperationIndex.IsInvalid()) {
        SetError(pErrorMessage, "GM88::BakeDispatch operation index expression was invalid.");
        return false;
    }
    if (pSourceIndex.IsInvalid()) {
        SetError(pErrorMessage, "GM88::BakeDispatch source index expression was invalid.");
        return false;
    }
    if (pDestinationIndex.IsInvalid()) {
        SetError(pErrorMessage, "GM88::BakeDispatch destination index expression was invalid.");
        return false;
    }
    if (pUnrollDomainWord.IsInvalid()) {
        SetError(pErrorMessage, "GM88::BakeDispatch unroll domain word expression was invalid.");
        return false;
    }
    if (pArgADomainWord.IsInvalid()) {
        SetError(pErrorMessage, "GM88::BakeDispatch arg A domain word expression was invalid.");
        return false;
    }
    if (pArgBDomainWord.IsInvalid()) {
        SetError(pErrorMessage, "GM88::BakeDispatch arg B domain word expression was invalid.");
        return false;
    }
    if (pArgCDomainWord.IsInvalid()) {
        SetError(pErrorMessage, "GM88::BakeDispatch arg C domain word expression was invalid.");
        return false;
    }
    if (pArgDDomainWord.IsInvalid()) {
        SetError(pErrorMessage, "GM88::BakeDispatch arg D domain word expression was invalid.");
        return false;
    }
    if (!pSource.IsBuf()) {
        SetError(pErrorMessage, "GM88::BakeDispatch source must be a buffer symbol.");
        return false;
    }
    if (!pOperation.IsBuf()) {
        SetError(pErrorMessage, "GM88::BakeDispatch operation data must be a buffer symbol.");
        return false;
    }
    if (!pDestination.IsBuf()) {
        SetError(pErrorMessage, "GM88::BakeDispatch destination must be a buffer symbol.");
        return false;
    }

    const GSymbol aOperationIndex = VarSymbol("aM88OperationIndex");
    const GSymbol aSourceIndex = VarSymbol("aM88SourceIndex");
    const GSymbol aDestinationIndex = VarSymbol("aM88DestinationIndex");
    const GSymbol aUnrollDomainWord = VarSymbol("aM88UnrollDomainWord");
    const GSymbol aArgADomainWord = VarSymbol("aM88ArgADomainWord");
    const GSymbol aArgBDomainWord = VarSymbol("aM88ArgBDomainWord");
    const GSymbol aArgCDomainWord = VarSymbol("aM88ArgCDomainWord");
    const GSymbol aArgDDomainWord = VarSymbol("aM88ArgDDomainWord");

    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aOperationIndex), pOperationIndex));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aSourceIndex), pSourceIndex));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aDestinationIndex), pDestinationIndex));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aUnrollDomainWord), pUnrollDomainWord));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aArgADomainWord), pArgADomainWord));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aArgBDomainWord), pArgBDomainWord));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aArgCDomainWord), pArgCDomainWord));
    pStatements->push_back(GStatement::Assign(GTarget::Symbol(aArgDDomainWord), pArgDDomainWord));

    const std::string aLine =
        "mMatrix.Dispatch(" +
        BufAliasName(pOperation) + ", " +
        aOperationIndex.mName + ", " +
        BufAliasName(pSource) + ", " +
        aSourceIndex.mName + ", " +
        BufAliasName(pDestination) + ", " +
        aDestinationIndex.mName + ", " +
        "static_cast<std::uint8_t>(" + aUnrollDomainWord.mName + "), " +
        "static_cast<std::uint8_t>(" + aArgADomainWord.mName + "), " +
        "static_cast<std::uint8_t>(" + aArgBDomainWord.mName + "), " +
        "static_cast<std::uint8_t>(" + aArgCDomainWord.mName + "), " +
        "static_cast<std::uint8_t>(" + aArgDDomainWord.mName + "));";

    pStatements->push_back(GStatement::RawLine(aLine));
    
    return true;
}

void GM88::SetError(std::string *pErrorMessage,
                    const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}
