//
//  GQuickARX.hpp
//  MeanMachine
//
//  Created by Dragon on 5/10/26.
//

#ifndef GQuickARX_hpp
#define GQuickARX_hpp

#include "GQuick.hpp"
#include "GMagicNumbers.hpp"

enum class GDiffuseKind : std::uint8_t {
    kInv = 0,
    kA = 1,
    kB = 2,
    kC = 3
};

struct GARXSymbolPack {
    
    GSymbol mStreamCurrent;
    GSymbol mStreamPrevious;
    GSymbol mStreamScatter;
    
    GSymbol mSecretCurrent;
    GSymbol mSecretPrevious;
    GSymbol mSecretScatter;
    
    
    GSymbol mStreamCross;
    GSymbol mCarry;

    GSymbol mWandererA;
    GSymbol mWandererB;
    GSymbol mWandererC;
    GSymbol mWandererD;
    GSymbol mWandererE;
    GSymbol mWandererF;

    GSymbol mOrbiterA;
    GSymbol mOrbiterB;
    GSymbol mOrbiterC;
    GSymbol mOrbiterD;
    GSymbol mOrbiterE;
    GSymbol mOrbiterF;

    GSymbol mDomainSaltA;
    GSymbol mDomainSaltB;
    GSymbol mDomainSaltC;
    GSymbol mDomainSaltD;
    GSymbol mDomainSaltE;
    GSymbol mDomainSaltF;

    GSymbol mPlugKeyA;
    GSymbol mPlugKeyB;
};

class GQuickARX {
public:

    static GExpr Diffuse(const GExpr &pExpr,
                         GDiffuseKind pKind);

    static GExpr RotL64(const GExpr &pExpr,
                        int pRotation);

    static GExpr MaybeRotL64(const GExpr &pExpr,
                             int pRotation);

    static GExpr XorPair(const GExpr &pA,
                         const GExpr &pB);

    static GExpr XorPairRotA(const GSymbol &pA,
                             const GSymbol &pB,
                             int pRotation);

    static GExpr XorPairRotB(const GSymbol &pA,
                             const GSymbol &pB,
                             int pRotation);

    static GExpr XorAddXorDiffuse(const GExpr &pA,
                                  const GExpr &pB,
                                  const GExpr &pC,
                                  const GExpr &pD,
                                  GDiffuseKind pDiffuseKind);

    static GExpr Crush3XorPairsDiffuse(const GExpr &pPairA,
                                       const GExpr &pPairB,
                                       const GExpr &pPairC,
                                       const GExpr &pScatter,
                                       const GExpr &pCarry,
                                       GDiffuseKind pDiffuseKind);

    static GExpr MulConstRotL64(const GSymbol &pSymbol,
                                std::uint64_t pMul,
                                int pRotation);

    static GExpr MakeLoopSaltRead(const GSymbol &pSalt,
                                  const GSymbol &pLoopIndex,
                                  bool pInverted,
                                  int pOffset);
    
    
    static GExpr PlugKeyRefreshA(const GARXSymbolPack &pPack,
                                 GDiffuseKind pDiffuseKind);

    static GExpr PlugKeyRefreshB(const GARXSymbolPack &pPack,
                                 GDiffuseKind pDiffuseKind);

    static GStatement MakePlugKeyRefreshAStatement(const GARXSymbolPack &pPack,
                                                   GDiffuseKind pDiffuseKind);

    static GStatement MakePlugKeyRefreshBStatement(const GARXSymbolPack &pPack,
                                                   GDiffuseKind pDiffuseKind);

    static GExpr PlugKeyMix(const GSymbol &pPlugKey,
                            const GExpr &pTermA,
                            const GExpr &pTermB);

    static GStatement PlugKeyMixAssign(const GSymbol &pPlugKey,
                                       const GExpr &pTermA,
                                       const GExpr &pTermB);

    static GExpr PlugSaltRead(const GSymbol &pSalt,
                              const GSymbol &pPlugKey);

    static GExpr PlugSaltRead(const GSymbol &pSalt,
                              const GSymbol &pPlugKey,
                              int pOffset);

    static GExpr HotAdd(const GHotPack &pHotPack,
                        std::size_t pHotIndex);

    static GExpr HotMul(const GHotPack &pHotPack,
                        std::size_t pHotIndex);

    static GExpr AddStatementTerms(const std::vector<GExpr> &pTerms);

    static GStatement MulRotAssign(const GSymbol &pTarget,
                                   const GHotPack &pHotPack,
                                   std::size_t pHotIndex,
                                   int pRotation);

    static GStatement GatePrism8ThenDiffuseAssign(const GSymbol &pTarget,
                                                  const std::vector<GSymbol> &pSBoxes,
                                                  GDiffuseKind pPostDiffuseKind);
    
};

#endif
