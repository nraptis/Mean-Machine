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
                                         std::string *pError = nullptr) {
        std::uint8_t *aSource = nullptr;
        std::uint8_t *aSBoxA = nullptr;
        std::uint8_t *aSBoxB = nullptr;
        std::uint8_t *aSBoxC = nullptr;
        std::uint8_t *aSBoxD = nullptr;

        if (!ResolveRequiredBuffer(pWorkspace, pSource, "source", &aSource, pError)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxA, "sbox A", &aSBoxA, pError)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxB, "sbox B", &aSBoxB, pError)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxC, "sbox C", &aSBoxC, pError)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxD, "sbox D", &aSBoxD, pError)) { return false; }

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
                                         std::string *pError = nullptr) {
        std::uint8_t *aSource = nullptr;
        std::uint8_t *aSBoxA = nullptr;
        std::uint8_t *aSBoxB = nullptr;
        std::uint8_t *aSBoxC = nullptr;
        std::uint8_t *aSBoxD = nullptr;
        std::uint8_t *aExistingSBoxA = nullptr;
        std::uint8_t *aExistingSBoxB = nullptr;
        std::uint8_t *aExistingSBoxC = nullptr;
        std::uint8_t *aExistingSBoxD = nullptr;

        if (!ResolveRequiredBuffer(pWorkspace, pSource, "source", &aSource, pError)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxA, "sbox A", &aSBoxA, pError)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxB, "sbox B", &aSBoxB, pError)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxC, "sbox C", &aSBoxC, pError)) { return false; }
        if (!ResolveRequiredBuffer(pWorkspace, pSBoxD, "sbox D", &aSBoxD, pError)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExistingSBoxA, "existing sbox A", &aExistingSBoxA, pError)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExistingSBoxB, "existing sbox B", &aExistingSBoxB, pError)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExistingSBoxC, "existing sbox C", &aExistingSBoxC, pError)) { return false; }
        if (!ResolveOptionalBuffer(pWorkspace, pExistingSBoxD, "existing sbox D", &aExistingSBoxD, pError)) { return false; }

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
    static void                     SetError(std::string *pError,
                                             const std::string &pMessage) {
        if (pError != nullptr) {
            *pError = pMessage;
        }
    }

    static bool                     ResolveRequiredBuffer(TwistWorkSpace *pWorkspace,
                                                          const GSymbol &pSymbol,
                                                          const std::string &pLabel,
                                                          std::uint8_t **pBufferOut,
                                                          std::string *pError) {
        if (pBufferOut == nullptr) {
            SetError(pError, "GCryptoGenerator output buffer pointer was null.");
            return false;
        }
        *pBufferOut = nullptr;

        if (pWorkspace == nullptr) {
            SetError(pError, "GCryptoGenerator workspace was null.");
            return false;
        }

        if (!pSymbol.IsBuf()) {
            SetError(pError, "GCryptoGenerator expected a buffer symbol for " + pLabel + ".");
            return false;
        }

        std::uint8_t *aBuffer = TwistWorkSpace::GetBuffer(pWorkspace, pSymbol.mSlot);
        if (aBuffer == nullptr) {
            SetError(pError, "GCryptoGenerator resolved null buffer for " + pLabel + ".");
            return false;
        }

        *pBufferOut = aBuffer;
        return true;
    }

    static bool                     ResolveOptionalBuffer(TwistWorkSpace *pWorkspace,
                                                          const GSymbol &pSymbol,
                                                          const std::string &pLabel,
                                                          std::uint8_t **pBufferOut,
                                                          std::string *pError) {
        if (pBufferOut == nullptr) {
            SetError(pError, "GCryptoGenerator optional output buffer pointer was null.");
            return false;
        }
        *pBufferOut = nullptr;

        if (pSymbol.IsInvalid()) {
            return true;
        }

        return ResolveRequiredBuffer(pWorkspace, pSymbol, pLabel, pBufferOut, pError);
    }
};

#endif /* GCryptoGenerator_hpp */
