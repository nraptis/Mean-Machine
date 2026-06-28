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
                        GSymbol pOperationIndex,
                        GSymbol pSource,
                        GSymbol pSourceIndex,
                        GSymbol pDestination,
                        GSymbol pDestinationIndex,
                        std::vector<GStatement> *pStatements,
                        std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GM88::BakeDispatch output statement list was null.");
        return false;
    }
    if (!pOperation.IsBuf()) {
        SetError(pErrorMessage, "GM88::BakeDispatch operation data must be a buffer symbol.");
        return false;
    }
    if (!pSource.IsBuf()) {
        SetError(pErrorMessage, "GM88::BakeDispatch source must be a buffer symbol.");
        return false;
    }
    if (!pDestination.IsBuf()) {
        SetError(pErrorMessage, "GM88::BakeDispatch destination must be a buffer symbol.");
        return false;
    }
    if (!pOperationIndex.IsVar() ||
        !pSourceIndex.IsVar() ||
        !pDestinationIndex.IsVar()) {
        SetError(pErrorMessage, "GM88::BakeDispatch indexes and domain words must be variable symbols.");
        return false;
    }
    
    const std::string aLine =
    "\tmMatrix.Dispatch(" +
    BufAliasName(pOperation) + ", " +
    pOperationIndex.mName + ",\n" +
    "\t\t\t\t\t\t\t" + BufAliasName(pSource) + ", " +
    pSourceIndex.mName + ",\n" +
    "\t\t\t\t\t\t\t" + BufAliasName(pDestination) + ", " +
    pDestinationIndex.mName + ");";
    
    pStatements->push_back(GStatement::RawLine(aLine));
    
    return true;
}

bool GM88::BakeDispatch(GSymbol pOperation,
                        GSymbol pOperationIndex,
                        GSymbol pSource,
                        GSymbol pSourceIndex,
                        GSymbol pDestination,
                        GSymbol pDestinationIndex,
                        GSymbol pUnrollDomainWord,
                        GSymbol pArgADomainWord,
                        GSymbol pArgBDomainWord,
                        GSymbol pArgCDomainWord,
                        GSymbol pArgDDomainWord,
                        std::vector<GStatement> *pStatements,
                        std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "GM88::BakeDispatch output statement list was null.");
        return false;
    }
    if (!pOperation.IsBuf()) {
        SetError(pErrorMessage, "GM88::BakeDispatch operation data must be a buffer symbol.");
        return false;
    }
    if (!pSource.IsBuf()) {
        SetError(pErrorMessage, "GM88::BakeDispatch source must be a buffer symbol.");
        return false;
    }
    if (!pDestination.IsBuf()) {
        SetError(pErrorMessage, "GM88::BakeDispatch destination must be a buffer symbol.");
        return false;
    }
    if (!pOperationIndex.IsVar() ||
        !pSourceIndex.IsVar() ||
        !pDestinationIndex.IsVar() ||
        !pUnrollDomainWord.IsVar() ||
        !pArgADomainWord.IsVar() ||
        !pArgBDomainWord.IsVar() ||
        !pArgCDomainWord.IsVar() ||
        !pArgDDomainWord.IsVar()) {
        SetError(pErrorMessage, "GM88::BakeDispatch indexes and domain words must be variable symbols.");
        return false;
    }
    
    const std::string aLine =
    "\tmMatrix.Dispatch(" +
    BufAliasName(pOperation) + ", " +
    pOperationIndex.mName + ",\n" +
    "\t\t\t\t\t\t\t" + BufAliasName(pSource) + ", " +
    pSourceIndex.mName + ",\n" +
    "\t\t\t\t\t\t\t" + BufAliasName(pDestination) + ", " +
    pDestinationIndex.mName + ",\n" +
    "\t\t\t\t\t\t\t" + pUnrollDomainWord.mName + ",\n" +
    "\t\t\t\t\t\t\t" + pArgADomainWord.mName + ", " +
    pArgBDomainWord.mName + ", " +
    pArgCDomainWord.mName + ", " +
    pArgDDomainWord.mName + ");";
    
    pStatements->push_back(GStatement::RawLine(aLine));
    
    return true;
}

void GM88::SetError(std::string *pErrorMessage,
                    const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
    }
}
