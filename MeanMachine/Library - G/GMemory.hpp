//
//  GMemory.hpp
//  MeanMachine
//

#ifndef GMemory_hpp
#define GMemory_hpp

#include "GSeedProgram.hpp"

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

        if (IsWideScratchSaltSlot(pDest.mSlot)) {
            return BakeGrow(pDest, pSource, pStatements, pErrorMessage);
        }
        if (IsWideScratchSaltSlot(pSource.mSlot)) {
            SetError(pErrorMessage, "GMemory byte copy cannot use scratch-salt source buffers.");
            return false;
        }

        const std::string aLine = "TwistMemory::CopyBlock(" +
            BufAliasName(pDest.mSlot) + ", " +
            BufAliasName(pSource.mSlot) + ");";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }

    bool BakeGrow(GSymbol pDest,
                  GSymbol pSource,
                  std::vector<GStatement> *pStatements,
                  std::string *pErrorMessage) const {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GMemory output statement list was null.");
            return false;
        }
        if (!pDest.IsBuf() || !pSource.IsBuf()) {
            SetError(pErrorMessage, "GMemory grow symbols must both be buffer symbols.");
            return false;
        }
        if (!IsWideScratchSaltSlot(pDest.mSlot)) {
            SetError(pErrorMessage, "GMemory grow destination must be a scratch-salt buffer.");
            return false;
        }
        if (IsWideScratchSaltSlot(pSource.mSlot)) {
            SetError(pErrorMessage, "GMemory grow source must be a byte buffer.");
            return false;
        }

        const int aLength = TwistWorkSpace::GetBufferLength(pSource.mSlot);
        if (aLength <= 0) {
            SetError(pErrorMessage, "GMemory grow source length resolved to <= 0.");
            return false;
        }

        const std::string aLine = "TwistMemory::Grow(" +
            BufAliasName(pDest.mSlot) + ", " +
            BufAliasName(pSource.mSlot) + ", " +
            std::to_string(static_cast<unsigned int>(aLength)) + "U);";
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
    static bool IsWideScratchSaltSlot(TwistWorkSpaceSlot pSlot) {
        switch (pSlot) {
            case TwistWorkSpaceSlot::kScratchSaltA:
            case TwistWorkSpaceSlot::kScratchSaltB:
            case TwistWorkSpaceSlot::kScratchSaltC:
            case TwistWorkSpaceSlot::kScratchSaltD:
                return true;
            default:
                return false;
        }
    }

    static void SetError(std::string *pErrorMessage,
                         const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }
};

#endif /* GMemory_hpp */
