//
//  GCryptoGenerator.hpp
//  MeanMachine
//
//  Created by Codex on 4/29/26.
//

#ifndef GCryptoGenerator_hpp
#define GCryptoGenerator_hpp

#include "GSymbol.hpp"
#include "TwistWorkSpace.hpp"

#include <cstdint>
#include <string>

class GCryptoGenerator {
public:
    static bool                     Make(TwistWorkSpace *pWorkspace,
                                         const GSymbol &pSource,
                                         const GSymbol &pSBoxA,
                                         const GSymbol &pSBoxB,
                                         const GSymbol &pSBoxC,
                                         const GSymbol &pSBoxD,
                                         std::string *pErrorMessage = nullptr) {
        return Make(pWorkspace,
                    nullptr,
                    pSource,
                    pSBoxA,
                    pSBoxB,
                    pSBoxC,
                    pSBoxD,
                    pErrorMessage);
    }

    static bool                     Make(TwistWorkSpace *pWorkspace,
                                         TwistExpander *pExpander,
                                         const GSymbol &pSource,
                                         const GSymbol &pSBoxA,
                                         const GSymbol &pSBoxB,
                                         const GSymbol &pSBoxC,
                                         const GSymbol &pSBoxD,
                                         std::string *pErrorMessage = nullptr) {
        std::uint8_t *aSource = nullptr;
        std::uint8_t *aSBoxA = nullptr;
        std::uint8_t *aSBoxB = nullptr;
        std::uint8_t *aSBoxC = nullptr;
        std::uint8_t *aSBoxD = nullptr;

        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSource, "source", &aSource, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSBoxA, "sbox A", &aSBoxA, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSBoxB, "sbox B", &aSBoxB, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSBoxC, "sbox C", &aSBoxC, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSBoxD, "sbox D", &aSBoxD, pErrorMessage)) { return false; }

        TwistCryptoGenerator aGenerator;
        /*
        aGenerator.StepA_MakeSBoxes(aSource,
                                    aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                    nullptr, nullptr, nullptr, nullptr,
                                    nullptr, nullptr, nullptr, nullptr);
        */
        return true;
    }

    static bool                     Make(TwistWorkSpace *pWorkspace,
                                         const GSymbol &pSource,
                                         const GSymbol &pSBoxA,
                                         const GSymbol &pSBoxB,
                                         const GSymbol &pSBoxC,
                                         const GSymbol &pSBoxD,
                                         const GSymbol &pExistingSBoxA,
                                         const GSymbol &pExistingSBoxB,
                                         const GSymbol &pExistingSBoxC,
                                         const GSymbol &pExistingSBoxD,
                                         std::string *pErrorMessage = nullptr) {
        return Make(pWorkspace,
                    nullptr,
                    pSource,
                    pSBoxA,
                    pSBoxB,
                    pSBoxC,
                    pSBoxD,
                    pExistingSBoxA,
                    pExistingSBoxB,
                    pExistingSBoxC,
                    pExistingSBoxD,
                    pErrorMessage);
    }

    static bool                     Make(TwistWorkSpace *pWorkspace,
                                         TwistExpander *pExpander,
                                         const GSymbol &pSource,
                                         const GSymbol &pSBoxA,
                                         const GSymbol &pSBoxB,
                                         const GSymbol &pSBoxC,
                                         const GSymbol &pSBoxD,
                                         const GSymbol &pExistingSBoxA,
                                         const GSymbol &pExistingSBoxB,
                                         const GSymbol &pExistingSBoxC,
                                         const GSymbol &pExistingSBoxD,
                                         std::string *pErrorMessage = nullptr) {
        std::uint8_t *aSource = nullptr;
        std::uint8_t *aSBoxA = nullptr;
        std::uint8_t *aSBoxB = nullptr;
        std::uint8_t *aSBoxC = nullptr;
        std::uint8_t *aSBoxD = nullptr;
        std::uint8_t *aExistingSBoxAPtr = nullptr;
        std::uint8_t *aExistingSBoxBPtr = nullptr;
        std::uint8_t *aExistingSBoxCPtr = nullptr;
        std::uint8_t *aExistingSBoxDPtr = nullptr;

        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSource, "source", &aSource, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSBoxA, "sbox A", &aSBoxA, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSBoxB, "sbox B", &aSBoxB, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSBoxC, "sbox C", &aSBoxC, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSBoxD, "sbox D", &aSBoxD, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pExistingSBoxA, "existing sbox A", &aExistingSBoxAPtr, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pExistingSBoxB, "existing sbox B", &aExistingSBoxBPtr, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pExistingSBoxC, "existing sbox C", &aExistingSBoxCPtr, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pExistingSBoxD, "existing sbox D", &aExistingSBoxDPtr, pErrorMessage)) { return false; }

        TwistCryptoGenerator aGenerator;
        /*
        aGenerator.StepA_MakeSBoxes(aSource,
                                    aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                    aExistingSBoxAPtr, aExistingSBoxBPtr, aExistingSBoxCPtr, aExistingSBoxDPtr,
                                    nullptr, nullptr, nullptr, nullptr);
        */
        return true;
    }

    static bool                     Salt(TwistWorkSpace *pWorkspace,
                                         const GSymbol &pSource,
                                         const GSymbol &pSaltA,
                                         const GSymbol &pSaltB,
                                         const GSymbol &pSaltC,
                                         const GSymbol &pSaltD,
                                         const GSymbol &pSBoxA,
                                         const GSymbol &pSBoxB,
                                         const GSymbol &pSBoxC,
                                         const GSymbol &pSBoxD,
                                         std::string *pErrorMessage = nullptr) {
        return Salt(pWorkspace,
                    nullptr,
                    pSource,
                    pSaltA,
                    pSaltB,
                    pSaltC,
                    pSaltD,
                    pSBoxA,
                    pSBoxB,
                    pSBoxC,
                    pSBoxD,
                    pErrorMessage);
    }

    static bool                     Salt(TwistWorkSpace *pWorkspace,
                                         TwistExpander *pExpander,
                                         const GSymbol &pSource,
                                         const GSymbol &pSaltA,
                                         const GSymbol &pSaltB,
                                         const GSymbol &pSaltC,
                                         const GSymbol &pSaltD,
                                         const GSymbol &pSBoxA,
                                         const GSymbol &pSBoxB,
                                         const GSymbol &pSBoxC,
                                         const GSymbol &pSBoxD,
                                         std::string *pErrorMessage = nullptr) {
        std::uint8_t *aSource = nullptr;
        std::uint8_t *aSaltA = nullptr;
        std::uint8_t *aSaltB = nullptr;
        std::uint8_t *aSaltC = nullptr;
        std::uint8_t *aSaltD = nullptr;
        std::uint8_t *aSBoxA = nullptr;
        std::uint8_t *aSBoxB = nullptr;
        std::uint8_t *aSBoxC = nullptr;
        std::uint8_t *aSBoxD = nullptr;

        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSource, "source", &aSource, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSaltA, "salt A", &aSaltA, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSaltB, "salt B", &aSaltB, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSaltC, "salt C", &aSaltC, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSaltD, "salt D", &aSaltD, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxA, "sbox A", &aSBoxA, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxB, "sbox B", &aSBoxB, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxC, "sbox C", &aSBoxC, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxD, "sbox D", &aSBoxD, pErrorMessage)) { return false; }

        TwistCryptoGenerator aGenerator;
        /*
        aGenerator.StepB_MakeSalts(aSource,
                                   aSaltA, aSaltB, aSaltC, aSaltD,
                                   aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                   nullptr, nullptr, nullptr, nullptr,
                                   nullptr, nullptr, nullptr, nullptr);
        */
        return true;
    }

    static bool                     Salt(TwistWorkSpace *pWorkspace,
                                         const GSymbol &pSource,
                                         const GSymbol &pSaltA,
                                         const GSymbol &pSaltB,
                                         const GSymbol &pSaltC,
                                         const GSymbol &pSaltD,
                                         const GSymbol &pExistingSaltA,
                                         const GSymbol &pExistingSaltB,
                                         const GSymbol &pExistingSaltC,
                                         const GSymbol &pExistingSaltD,
                                         const GSymbol &pSBoxA,
                                         const GSymbol &pSBoxB,
                                         const GSymbol &pSBoxC,
                                         const GSymbol &pSBoxD,
                                         const GSymbol &pSBoxE,
                                         const GSymbol &pSBoxF,
                                         const GSymbol &pSBoxG,
                                         const GSymbol &pSBoxH,
                                         std::string *pErrorMessage = nullptr) {
        return Salt(pWorkspace,
                    nullptr,
                    pSource,
                    pSaltA,
                    pSaltB,
                    pSaltC,
                    pSaltD,
                    pExistingSaltA,
                    pExistingSaltB,
                    pExistingSaltC,
                    pExistingSaltD,
                    pSBoxA,
                    pSBoxB,
                    pSBoxC,
                    pSBoxD,
                    pSBoxE,
                    pSBoxF,
                    pSBoxG,
                    pSBoxH,
                    pErrorMessage);
    }

    static bool                     Salt(TwistWorkSpace *pWorkspace,
                                         TwistExpander *pExpander,
                                         const GSymbol &pSource,
                                         const GSymbol &pSaltA,
                                         const GSymbol &pSaltB,
                                         const GSymbol &pSaltC,
                                         const GSymbol &pSaltD,
                                         const GSymbol &pExistingSaltA,
                                         const GSymbol &pExistingSaltB,
                                         const GSymbol &pExistingSaltC,
                                         const GSymbol &pExistingSaltD,
                                         const GSymbol &pSBoxA,
                                         const GSymbol &pSBoxB,
                                         const GSymbol &pSBoxC,
                                         const GSymbol &pSBoxD,
                                         const GSymbol &pSBoxE,
                                         const GSymbol &pSBoxF,
                                         const GSymbol &pSBoxG,
                                         const GSymbol &pSBoxH,
                                         std::string *pErrorMessage = nullptr) {
        std::uint8_t *aSource = nullptr;
        std::uint8_t *aSaltA = nullptr;
        std::uint8_t *aSaltB = nullptr;
        std::uint8_t *aSaltC = nullptr;
        std::uint8_t *aSaltD = nullptr;
        std::uint8_t *aExistingSaltA = nullptr;
        std::uint8_t *aExistingSaltB = nullptr;
        std::uint8_t *aExistingSaltC = nullptr;
        std::uint8_t *aExistingSaltD = nullptr;
        std::uint8_t *aSBoxA = nullptr;
        std::uint8_t *aSBoxB = nullptr;
        std::uint8_t *aSBoxC = nullptr;
        std::uint8_t *aSBoxD = nullptr;
        std::uint8_t *aSBoxE = nullptr;
        std::uint8_t *aSBoxF = nullptr;
        std::uint8_t *aSBoxG = nullptr;
        std::uint8_t *aSBoxH = nullptr;

        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSource, "source", &aSource, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSaltA, "salt A", &aSaltA, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSaltB, "salt B", &aSaltB, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSaltC, "salt C", &aSaltC, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pExpander, pSaltD, "salt D", &aSaltD, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pExistingSaltA, "existing salt A", &aExistingSaltA, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pExistingSaltB, "existing salt B", &aExistingSaltB, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pExistingSaltC, "existing salt C", &aExistingSaltC, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pExistingSaltD, "existing salt D", &aExistingSaltD, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxA, "sbox A", &aSBoxA, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxB, "sbox B", &aSBoxB, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxC, "sbox C", &aSBoxC, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxD, "sbox D", &aSBoxD, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxE, "sbox E", &aSBoxE, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxF, "sbox F", &aSBoxF, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxG, "sbox G", &aSBoxG, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExpander, pSBoxH, "sbox H", &aSBoxH, pErrorMessage)) { return false; }

        TwistCryptoGenerator aGenerator;
        /*
        aGenerator.StepB_MakeSalts(aSource,
                                   aSaltA, aSaltB, aSaltC, aSaltD,
                                   aSBoxA, aSBoxB, aSBoxC, aSBoxD,
                                   aSBoxE, aSBoxF, aSBoxG, aSBoxH,
                                   aExistingSaltA, aExistingSaltB, aExistingSaltC, aExistingSaltD);
        */
        return true;
    }

private:
    static void                     SetError(std::string *pErrorMessage,
                                             const std::string &pMessage) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = pMessage;
        }
    }

    static bool                     ResolveRequiredBuffer(TwistWorkSpace *pWorkspace,
                                                          TwistExpander *pExpander,
                                                          const GSymbol &pSymbol,
                                                          const std::string &pLabel,
                                                          std::uint8_t **pBufferOut,
                                                          std::string *pErrorMessage) {
        if (pBufferOut == nullptr) {
            SetError(pErrorMessage, "GCryptoGenerator output buffer pointer was null.");
            return false;
        }
        *pBufferOut = nullptr;

        if (pWorkspace == nullptr) {
            SetError(pErrorMessage, "GCryptoGenerator workspace was null.");
            return false;
        }

        if (!pSymbol.IsBuf()) {
            SetError(pErrorMessage, "GCryptoGenerator expected a buffer symbol for " + pLabel + ".");
            return false;
        }

        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pExpander, pSymbol.mSlot);
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "GCryptoGenerator resolved null buffer for " + pLabel + ".");
            return false;
        }

        *pBufferOut = aBuffer;
        return true;
    }

    static bool                     ResolveOptionalBuffer(TwistWorkSpace *pWorkspace,
                                                          TwistExpander *pExpander,
                                                          const GSymbol &pSymbol,
                                                          const std::string &pLabel,
                                                          std::uint8_t **pBufferOut,
                                                          std::string *pErrorMessage) {
        if (pBufferOut == nullptr) {
            SetError(pErrorMessage, "GCryptoGenerator optional output buffer pointer was null.");
            return false;
        }
        *pBufferOut = nullptr;

        if (pSymbol.IsInvalid()) {
            return true;
        }

        return ResolveRequiredBuffer(pWorkspace, pExpander, pSymbol, pLabel, pBufferOut, pErrorMessage);
    }
};

#endif /* GCryptoGenerator_hpp */
