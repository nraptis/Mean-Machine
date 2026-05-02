//
//  GMasking.hpp
//  MeanMachine
//

#ifndef GMasking_hpp
#define GMasking_hpp

#include "GSeedProgram.hpp"
#include "TwistMasking.hpp"
#include "Random.hpp"

#include <cstdint>
#include <string>
#include <vector>

class GMasking {
public:
    
    TwistMaskBraidType              GetRandomBraidType() {
        std::vector<TwistMaskBraidType> aList = TwistMasking::GetAllBraidTypes();
        return aList[Random::Get((int)aList.size())];
    }
    
    TwistMaskWeaveType              GetRandomWeaveType() {
        std::vector<TwistMaskWeaveType> aList = TwistMasking::GetAllWeaveTypes();
        return aList[Random::Get((int)aList.size())];
    }
    
    bool BakeBraid(TwistMaskBraidType pType,
                   GSymbol pSourceA,
                   GSymbol pSourceB,
                   GSymbol pMask,
                   std::vector<GStatement> *pStatements,
                   std::string *pErrorMessage) const {
        return BakeBraidCall(pType, pSourceA, pSourceB, pMask, pStatements, pErrorMessage);
    }

    bool BakeBraidA(GSymbol pSourceA,
                    GSymbol pSourceB,
                    GSymbol pMask,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        return BakeBraid(TwistMaskBraidType::kA, pSourceA, pSourceB, pMask, pStatements, pErrorMessage);
    }

    bool BakeBraidB(GSymbol pSourceA,
                    GSymbol pSourceB,
                    GSymbol pMask,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        return BakeBraid(TwistMaskBraidType::kB, pSourceA, pSourceB, pMask, pStatements, pErrorMessage);
    }

    bool BakeBraidC(GSymbol pSourceA,
                    GSymbol pSourceB,
                    GSymbol pMask,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        return BakeBraid(TwistMaskBraidType::kC, pSourceA, pSourceB, pMask, pStatements, pErrorMessage);
    }

    bool BakeWeave(TwistMaskWeaveType pType,
                   GSymbol pSourceA,
                   GSymbol pSourceB,
                   GSymbol pDest,
                   GSymbol pMask,
                   std::vector<GStatement> *pStatements,
                   std::string *pErrorMessage) const {
        return BakeWeaveCall(pType, pSourceA, pSourceB, pDest, pMask, pStatements, pErrorMessage);
    }

    bool BakeWeaveA(GSymbol pSourceA,
                    GSymbol pSourceB,
                    GSymbol pDest,
                    GSymbol pMask,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        return BakeWeave(TwistMaskWeaveType::kA, pSourceA, pSourceB, pDest, pMask, pStatements, pErrorMessage);
    }

    bool BakeWeaveB(GSymbol pSourceA,
                    GSymbol pSourceB,
                    GSymbol pDest,
                    GSymbol pMask,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        return BakeWeave(TwistMaskWeaveType::kB, pSourceA, pSourceB, pDest, pMask, pStatements, pErrorMessage);
    }

    bool BakeWeaveC(GSymbol pSourceA,
                    GSymbol pSourceB,
                    GSymbol pDest,
                    GSymbol pMask,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        return BakeWeave(TwistMaskWeaveType::kC, pSourceA, pSourceB, pDest, pMask, pStatements, pErrorMessage);
    }

    bool BakeWeaveD(GSymbol pSourceA,
                    GSymbol pSourceB,
                    GSymbol pDest,
                    GSymbol pMask,
                    std::vector<GStatement> *pStatements,
                    std::string *pErrorMessage) const {
        return BakeWeave(TwistMaskWeaveType::kD, pSourceA, pSourceB, pDest, pMask, pStatements, pErrorMessage);
    }

private:
    static void SetError(std::string *pErrorMessage,
                         const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }

    static std::string BraidToken(const TwistMaskBraidType pType) {
        switch (pType) {
            case TwistMaskBraidType::kA: return "TwistMaskBraidType::kA";
            case TwistMaskBraidType::kB: return "TwistMaskBraidType::kB";
            case TwistMaskBraidType::kC: return "TwistMaskBraidType::kC";
            default: return "TwistMaskBraidType::kA";
        }
    }

    static std::string WeaveToken(const TwistMaskWeaveType pType) {
        switch (pType) {
            case TwistMaskWeaveType::kA: return "TwistMaskWeaveType::kA";
            case TwistMaskWeaveType::kB: return "TwistMaskWeaveType::kB";
            case TwistMaskWeaveType::kC: return "TwistMaskWeaveType::kC";
            case TwistMaskWeaveType::kD: return "TwistMaskWeaveType::kD";
            default: return "TwistMaskWeaveType::kA";
        }
    }

    static bool IsBlockSizedSlot(const TwistWorkSpaceSlot pSlot) {
        switch (pSlot) {
            case TwistWorkSpaceSlot::kSource:
            case TwistWorkSpaceSlot::kSeedExpansionLaneA:
            case TwistWorkSpaceSlot::kSeedExpansionLaneB:
            case TwistWorkSpaceSlot::kSeedExpansionLaneC:
            case TwistWorkSpaceSlot::kSeedExpansionLaneD:
            case TwistWorkSpaceSlot::kWorkLaneA:
            case TwistWorkSpaceSlot::kWorkLaneB:
            case TwistWorkSpaceSlot::kWorkLaneC:
            case TwistWorkSpaceSlot::kWorkLaneD:
            case TwistWorkSpaceSlot::kOperationLaneA:
            case TwistWorkSpaceSlot::kOperationLaneB:
            case TwistWorkSpaceSlot::kMaskLaneA:
            case TwistWorkSpaceSlot::kMaskLaneB:
                return true;
            default:
                return false;
        }
    }

    static bool ResolveMaskLengthToken(const GSymbol pMask,
                                       std::string *pLengthToken,
                                       std::string *pErrorMessage) {
        if (pLengthToken == nullptr) {
            SetError(pErrorMessage, "GMasking mask length token output was null.");
            return false;
        }
        if (!pMask.IsBuf()) {
            SetError(pErrorMessage, "GMasking mask symbol must be a buffer symbol.");
            return false;
        }
        if (IsBlockSizedSlot(pMask.mSlot)) {
            *pLengthToken = "S_BLOCK";
            return true;
        }
        switch (pMask.mSlot) {
            case TwistWorkSpaceSlot::kKeyRowReadA:
                *pLengthToken = "W_KEY_A";
                return true;
            case TwistWorkSpaceSlot::kKeyRowReadB:
                *pLengthToken = "W_KEY_B";
                return true;
            case TwistWorkSpaceSlot::kMaskRowReadA:
                *pLengthToken = "W_MASK_A";
                return true;
            case TwistWorkSpaceSlot::kMaskRowReadB:
                *pLengthToken = "W_MASK_B";
                return true;
            default:
                SetError(pErrorMessage, "GMasking mask symbol must be key row read, mask row read, or block-sized lane.");
                return false;
        }
    }

    static bool BakeBraidCall(TwistMaskBraidType pType,
                              GSymbol pSourceA,
                              GSymbol pSourceB,
                              GSymbol pMask,
                              std::vector<GStatement> *pStatements,
                              std::string *pErrorMessage) {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GMasking output statement list was null.");
            return false;
        }
        if (!pSourceA.IsBuf() || !pSourceB.IsBuf() || !pMask.IsBuf()) {
            SetError(pErrorMessage, "GMasking braid symbols must be buffer symbols.");
            return false;
        }
        std::string aMaskLengthToken;
        if (!ResolveMaskLengthToken(pMask, &aMaskLengthToken, pErrorMessage)) {
            return false;
        }

        const std::string aLine = "TwistMasking::MaskBraid(" + BraidToken(pType) + ", " +
            BufAliasName(pSourceA.mSlot) + ", " +
            BufAliasName(pSourceB.mSlot) + ", " +
            "S_BLOCK, " +
            BufAliasName(pMask.mSlot) + ", " +
            aMaskLengthToken + ");";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }

    static bool BakeWeaveCall(TwistMaskWeaveType pType,
                              GSymbol pSourceA,
                              GSymbol pSourceB,
                              GSymbol pDest,
                              GSymbol pMask,
                              std::vector<GStatement> *pStatements,
                              std::string *pErrorMessage) {
        if (pStatements == nullptr) {
            SetError(pErrorMessage, "GMasking output statement list was null.");
            return false;
        }
        if (!pSourceA.IsBuf() || !pSourceB.IsBuf() || !pDest.IsBuf() || !pMask.IsBuf()) {
            SetError(pErrorMessage, "GMasking weave symbols must be buffer symbols.");
            return false;
        }
        std::string aMaskLengthToken;
        if (!ResolveMaskLengthToken(pMask, &aMaskLengthToken, pErrorMessage)) {
            return false;
        }

        const std::string aLine = "TwistMasking::MaskWeave(" + WeaveToken(pType) + ", " +
            BufAliasName(pSourceA.mSlot) + ", " +
            BufAliasName(pSourceB.mSlot) + ", " +
            BufAliasName(pDest.mSlot) + ", " +
            "S_BLOCK, " +
            BufAliasName(pMask.mSlot) + ", " +
            aMaskLengthToken + ");";
        pStatements->push_back(GStatement::RawLine(aLine));
        return true;
    }
};

#endif /* GMasking_hpp */
