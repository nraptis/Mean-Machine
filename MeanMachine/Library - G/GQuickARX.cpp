//
//  GQuickARX.cpp
//  MeanMachine
//
//  Created by Dragon on 5/10/26.
//

#include "GQuickARX.hpp"

GExpr GQuickARX::Diffuse(const GExpr &pExpr,
                         GDiffuseKind pKind) {
    switch (pKind) {
        case GDiffuseKind::kA:
            return GExpr::DiffuseA(pExpr);
        case GDiffuseKind::kB:
            return GExpr::DiffuseB(pExpr);
        case GDiffuseKind::kC:
            return GExpr::DiffuseC(pExpr);
        default:
            return GExpr::DiffuseA(pExpr);
    }
}

GExpr GQuickARX::RotL64(const GExpr &pExpr,
                        int pRotation) {
    return GExpr::RotL64(pExpr,
                         GExpr::Const64(static_cast<std::uint64_t>(pRotation)));
}

GExpr GQuickARX::MaybeRotL64(const GExpr &pExpr,
                             int pRotation) {
    if (pRotation < 0) {
        return pExpr;
    }
    return RotL64(pExpr, pRotation);
}

GExpr GQuickARX::XorPair(const GExpr &pA,
                         const GExpr &pB) {
    return GExpr::Xor(pA, pB);
}

GExpr GQuickARX::XorPairRotA(const GSymbol &pA,
                             const GSymbol &pB,
                             int pRotation) {
    return GExpr::Xor(RotL64(GExpr::Symbol(pA), pRotation),
                      GExpr::Symbol(pB));
}

GExpr GQuickARX::XorPairRotB(const GSymbol &pA,
                             const GSymbol &pB,
                             int pRotation) {
    return GExpr::Xor(GExpr::Symbol(pA),
                      RotL64(GExpr::Symbol(pB), pRotation));
}

GExpr GQuickARX::XorAddXorDiffuse(const GExpr &pA,
                                  const GExpr &pB,
                                  const GExpr &pC,
                                  const GExpr &pD,
                                  GDiffuseKind pDiffuseKind) {
    GExpr aLeft = GExpr::Xor(pA, pB);
    GExpr aRight = GExpr::Xor(pC, pD);
    return Diffuse(GExpr::Add(aLeft, aRight), pDiffuseKind);
}

GExpr GQuickARX::Crush3XorPairsDiffuse(const GExpr &pPairA,
                                       const GExpr &pPairB,
                                       const GExpr &pPairC,
                                       const GExpr &pScatter,
                                       const GExpr &pCarry,
                                       GDiffuseKind pDiffuseKind) {
    GExpr aExpr = GExpr::Add(pPairA, pPairB);
    aExpr = GExpr::Add(aExpr, pPairC);
    aExpr = GExpr::Add(aExpr, pScatter);
    aExpr = GExpr::Add(aExpr, pCarry);
    return Diffuse(aExpr, pDiffuseKind);
}

GExpr GQuickARX::MulConstRotL64(const GSymbol &pSymbol,
                                std::uint64_t pMul,
                                int pRotation) {
    GExpr aExpr = GExpr::Mul(GExpr::Symbol(pSymbol),
                             GExpr::Const64(pMul));
    return RotL64(aExpr, pRotation);
}

GExpr GQuickARX::MakeLoopSaltRead(const GSymbol &pSalt,
                                  const GSymbol &pLoopIndex,
                                  bool pInverted,
                                  int pOffset) {
    return GQuick::MakeReadBufferOffsetExpressionDirected(
        pSalt,
        pLoopIndex,
        pInverted,
        static_cast<std::uint32_t>(pOffset)
    );
}

GExpr GQuickARX::PlugKeyRefreshA(const GARXSymbolPack &pPack,
                                 GDiffuseKind pDiffuseKind) {
    GExpr aExpr = GExpr::Xor(GExpr::Symbol(pPack.mStreamCurrent),
                             GExpr::Symbol(pPack.mStreamScatter));
    aExpr = GExpr::Xor(aExpr, GExpr::Symbol(pPack.mCarry));
    return Diffuse(aExpr, pDiffuseKind);
}

GExpr GQuickARX::PlugKeyRefreshB(const GARXSymbolPack &pPack,
                                 GDiffuseKind pDiffuseKind) {
    GExpr aExpr = GExpr::Xor(GExpr::Symbol(pPack.mStreamPrevious),
                             GExpr::Symbol(pPack.mStreamCross));
    aExpr = GExpr::Xor(aExpr, GExpr::Symbol(pPack.mCarry));
    return Diffuse(aExpr, pDiffuseKind);
}

GStatement GQuickARX::MakePlugKeyRefreshAStatement(const GARXSymbolPack &pPack,
                                                   GDiffuseKind pDiffuseKind) {
    return GQuick::MakeAssignVariableStatement(
        pPack.mPlugKeyA,
        PlugKeyRefreshA(pPack, pDiffuseKind)
    );
}

GStatement GQuickARX::MakePlugKeyRefreshBStatement(const GARXSymbolPack &pPack,
                                                   GDiffuseKind pDiffuseKind) {
    return GQuick::MakeAssignVariableStatement(
        pPack.mPlugKeyB,
        PlugKeyRefreshB(pPack, pDiffuseKind)
    );
}

GExpr GQuickARX::PlugKeyMix(const GSymbol &pPlugKey,
                            const GExpr &pTermA,
                            const GExpr &pTermB) {
    return GExpr::Xor(GExpr::Symbol(pPlugKey),
                      GExpr::Xor(pTermA, pTermB));
}

GStatement GQuickARX::PlugKeyMixAssign(const GSymbol &pPlugKey,
                                       const GExpr &pTermA,
                                       const GExpr &pTermB) {
    return GQuick::MakeAssignVariableStatement(
        pPlugKey,
        PlugKeyMix(pPlugKey, pTermA, pTermB)
    );
}

GExpr GQuickARX::PlugSaltRead(const GSymbol &pSalt,
                              const GSymbol &pPlugKey) {
    return GQuick::MakeReadBufferReadExpression(pSalt,
                                                GExpr::Symbol(pPlugKey));
}

GExpr GQuickARX::PlugSaltRead(const GSymbol &pSalt,
                              const GSymbol &pPlugKey,
                              int pOffset) {
    if (pOffset < 0) {
        return PlugSaltRead(pSalt, pPlugKey);
    }
    return GQuick::MakeReadBufferOffsetExpression(pSalt,
                                                  GExpr::Symbol(pPlugKey),
                                                  static_cast<std::uint32_t>(pOffset));
}

GExpr GQuickARX::HotAdd(const GHotPack &pHotPack,
                        std::size_t pHotIndex) {
    if (pHotIndex >= pHotPack.mPair.size()) {
        printf("fatal: GQuickARX::HotAdd index out of range: %zu\n", pHotIndex);
        exit(0);
    }

    return GExpr::Const64(pHotPack.mPair[pHotIndex].mAdd);
}

GExpr GQuickARX::HotMul(const GHotPack &pHotPack,
                        std::size_t pHotIndex) {
    if (pHotIndex >= pHotPack.mPair.size()) {
        printf("fatal: GQuickARX::HotMul index out of range: %zu\n", pHotIndex);
        exit(0);
    }

    return GExpr::Const64(pHotPack.mPair[pHotIndex].mMul);
}

GExpr GQuickARX::AddStatementTerms(const std::vector<GExpr> &pTerms) {
    if (pTerms.empty()) {
        printf("fatal: GQuickARX::AddStatementTerms got empty term list\n");
        exit(0);
    }

    return GQuick::AddChain(pTerms);
}

GStatement GQuickARX::MulRotAssign(const GSymbol &pTarget,
                                   const GHotPack &pHotPack,
                                   std::size_t pHotIndex,
                                   int pRotation) {
    if (pRotation < 0) {
        printf("fatal: GQuickARX::MulRotAssign invalid rotation=%d\n", pRotation);
        exit(0);
    }

    GExpr aExpr = GExpr::Mul(GExpr::Symbol(pTarget),
                             HotMul(pHotPack, pHotIndex));
    aExpr = RotL64(aExpr, pRotation);

    return GQuick::MakeAssignVariableStatement(pTarget, aExpr);
}

GStatement GQuickARX::GatePrism8ThenDiffuseAssign(const GSymbol &pTarget,
                                                  const std::vector<GSymbol> &pSBoxes,
                                                  GDiffuseKind pPostDiffuseKind) {
    if (pSBoxes.size() < 8) {
        printf("fatal: GQuickARX::GatePrism8ThenDiffuseAssign requires 8 sboxes\n");
        exit(0);
    }

    GExpr aMixExpr = GExpr::Mix64_8(GExpr::Symbol(pTarget),
                                    Mix64Type_8::kGatePrism_8_8,
                                    0ULL,
                                    pSBoxes[0], pSBoxes[1], pSBoxes[2], pSBoxes[3],
                                    pSBoxes[4], pSBoxes[5], pSBoxes[6], pSBoxes[7]);

    GExpr aPostDiffuse = Diffuse(aMixExpr, pPostDiffuseKind);

    return GQuick::MakeAssignVariableStatement(pTarget, aPostDiffuse);
}
