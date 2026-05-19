//
//  GMemory.hpp
//  MeanMachine
//

#ifndef GMemory_hpp
#define GMemory_hpp

#include "GSeedProgram.hpp"
#include <algorithm>

class GMemory {
public:
    
    bool BakeZero(GSymbol pSource,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GMemory output statement list was null.");
            return false;
        }
        if (!pSource.IsBuf()) {
            SetError(pErrorMessage, "GMemory source must be a buffer symbol.");
            return false;
        }

        const std::string aLine = "TwistMemory::ZeroBlock(" +
            BufAliasName(pSource.mSlot) + ");";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }
    
    bool BakeZero(GSymbol pSource,
                  std::uint32_t pLength,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) const {
        (void)pLength;
        return BakeZero(pSource, pStatements, pErrorMessage);
    }
    
    bool Bake(GSymbol pSource,
              std::vector<GStatement> *pStatements,
              std::string *pErrorMessage) const {
        return BakeZero(pSource, pStatements, pErrorMessage);
    }
    
    bool BakeCopy(GSymbol pDest,
                  GSymbol pSource,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GMemory output statement list was null.");
            return false;
        }
        if (!pDest.IsBuf() || !pSource.IsBuf()) {
            SetError(pErrorMessage, "GMemory copy symbols must both be buffer symbols.");
            return false;
        }

        const int aDestLength = TwistWorkSpace::GetBufferLength(pDest.mSlot);
        const int aSourceLength = TwistWorkSpace::GetBufferLength(pSource.mSlot);
        if ((aDestLength <= 0) || (aSourceLength <= 0)) {
            SetError(pErrorMessage, "GMemory copy source/destination length resolved to <= 0.");
            return false;
        }

        const int aCopyLength = std::min(aDestLength, aSourceLength);
        const std::string aLine = "TwistMemory::Copy(" +
            BufAliasName(pDest.mSlot) + ", " +
            BufAliasName(pSource.mSlot) + ", " +
            std::to_string(static_cast<unsigned int>(aCopyLength)) + "U);";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }
    
    bool BakeSwap(GSymbol pBufferA,
                  GSymbol pBufferB,
                  GSymbol pTemp,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GMemory output statement list was null.");
            return false;
        }
        if (!pBufferA.IsBuf() || !pBufferB.IsBuf() || !pTemp.IsBuf()) {
            SetError(pErrorMessage, "GMemory swap symbols must all be buffer symbols.");
            return false;
        }

        const std::string aLine = "TwistMemory::SwapBlock(" +
            BufAliasName(pBufferA.mSlot) + ", " +
            BufAliasName(pBufferB.mSlot) + ", " +
            BufAliasName(pTemp.mSlot) + ");";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }
    
private:
    static void SetError(std::string *pErrorMessage,
                         const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }
};

#endif /* GMemory_hpp */
