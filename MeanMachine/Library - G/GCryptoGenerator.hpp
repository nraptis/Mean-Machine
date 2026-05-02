//
//  GCryptoGenerator.hpp
//  MeanMachine
//
//  Created by Codex on 4/29/26.
//

#ifndef GCryptoGenerator_hpp
#define GCryptoGenerator_hpp

#include "GSymbol.hpp"
#include "TwistCryptoGenerator.hpp"
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
        std::uint8_t *aSource = nullptr;
        std::uint8_t *aSBoxA = nullptr;
        std::uint8_t *aSBoxB = nullptr;
        std::uint8_t *aSBoxC = nullptr;
        std::uint8_t *aSBoxD = nullptr;

        if (!ResolveRequiredBuffer(pWorkspace, pSource, "source", &aSource, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxA, "sbox A", &aSBoxA, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxB, "sbox B", &aSBoxB, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxC, "sbox C", &aSBoxC, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxD, "sbox D", &aSBoxD, pErrorMessage)) { return false; }

        TwistCryptoGenerator aGenerator;
        aGenerator.Make(aSource, aSBoxA, aSBoxB, aSBoxC, aSBoxD);
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
        std::uint8_t *aSource = nullptr;
        std::uint8_t *aSBoxA = nullptr;
        std::uint8_t *aSBoxB = nullptr;
        std::uint8_t *aSBoxC = nullptr;
        std::uint8_t *aSBoxD = nullptr;
        std::uint8_t *aExistingSBoxA = nullptr;
        std::uint8_t *aExistingSBoxB = nullptr;
        std::uint8_t *aExistingSBoxC = nullptr;
        std::uint8_t *aExistingSBoxD = nullptr;

        if (!ResolveRequiredBuffer(pWorkspace, pSource, "source", &aSource, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxA, "sbox A", &aSBoxA, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxB, "sbox B", &aSBoxB, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxC, "sbox C", &aSBoxC, pErrorMessage)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxD, "sbox D", &aSBoxD, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExistingSBoxA, "existing sbox A", &aExistingSBoxA, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExistingSBoxB, "existing sbox B", &aExistingSBoxB, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExistingSBoxC, "existing sbox C", &aExistingSBoxC, pErrorMessage)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExistingSBoxD, "existing sbox D", &aExistingSBoxD, pErrorMessage)) { return false; }

        TwistCryptoGenerator aGenerator;
        aGenerator.Make(aSource,
                        aSBoxA,
                        aSBoxB,
                        aSBoxC,
                        aSBoxD,
                        aExistingSBoxA,
                        aExistingSBoxB,
                        aExistingSBoxC,
                        aExistingSBoxD);
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

        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pSymbol.mSlot);
        if (aBuffer == nullptr) {
            SetError(pErrorMessage, "GCryptoGenerator resolved null buffer for " + pLabel + ".");
            return false;
        }

        *pBufferOut = aBuffer;
        return true;
    }

    static bool                     ResolveOptionalBuffer(TwistWorkSpace *pWorkspace,
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

        return ResolveRequiredBuffer(pWorkspace, pSymbol, pLabel, pBufferOut, pErrorMessage);
    }
};

#endif /* GCryptoGenerator_hpp */
