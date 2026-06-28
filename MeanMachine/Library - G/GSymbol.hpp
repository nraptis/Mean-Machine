//
//  GSymbol.hpp
//  Superfox
//

#ifndef GSymbol_hpp
#define GSymbol_hpp

#include <cstdint>
#include <string>
#include "TwistWorkSpace.hpp"

enum class GSymbolType : std::uint8_t {
    kInv = 0,
    kVar = 1,
    kBuf = 2
};

enum class TwistVariable: std::uint8_t {
    kInvalid = 0,

    kIndex = 10, // aIndex
    kNonce = 11, // aNonce
    kParamNonce = 12, // pNonce
    kParamInput = 13, // pSource
    kParamOutput = 14, // pDestination
    kParamSnow = 15, // pSnow

    kDomainWordIngress = 20, // aDomainWordIngress
    kDomainWordScatter = 21, // aDomainWordScatter
    kDomainWordCross = 22, // aDomainWordCross
    
    kDomainWordMatrixSelectA,
    kDomainWordMatrixSelectB,
    
    kDomainWordMatrixUnrollA,
    kDomainWordMatrixUnrollB,
    
    kDomainWordMatrixArgA,
    kDomainWordMatrixArgB,
    
    kDomainWordMatrixArgC,
    kDomainWordMatrixArgD,
    
    kDomainWordMaskMutateA,
    kDomainWordMaskMutateB,

    kIngress = 40, // aIngress
    kPrevious = 41, // aPrevious
    kCross = 42, // aCross
    kCarry = 43, // aCarry
    kScatter = 44, // aScatter

    kWandererA = 120, // aWandererA
    kWandererB = 121,
    kWandererC = 122,
    kWandererD = 123,
    kWandererE = 124,
    kWandererF = 125,
    kWandererG = 126,
    kWandererH = 127,
    kWandererI = 128,
    kWandererJ = 129,
    kWandererK = 130,

    kOrbiterA = 140, // aOrbitA
    kOrbiterB = 141,
    kOrbiterC = 142,
    kOrbiterD = 143,
    kOrbiterE = 144,
    kOrbiterF = 145,
    kOrbiterG = 146,
    kOrbiterH = 147,
    kOrbiterI = 148,
    kOrbiterJ = 149,
    kOrbiterK = 150,

    kSelect = 210, // aSelect
    kMatrixUnrollA = 211, // mMatrixUnrollA
    kMatrixUnrollB = 212, // mMatrixUnrollB
    kMatrixArgA = 215, // mMatrixArgA
    kMatrixArgB = 216, // mMatrixArgB
    kMatrixArgC = 217, // mMatrixArgC
    kMatrixArgD = 218, // mMatrixArgD
    kMaskMutateA = 219, // mMaskMutateA
    kMaskMutateB = 220, // mMaskMutateB
};

enum class TwistConstants : std::uint8_t {
    kInvalid = 0,

    kPublicIngress = 10,
    kScatter = 11,
    kCrossIngress = 12,
    kIngress = kPublicIngress,
    kCross = kCrossIngress,

    kDomainConstantPublicIngress = 20,
    kDomainConstantPrivateIngress = 21,
    kDomainConstantCrossIngress = 22,

    kMatrixSelectA = 30,
    kMatrixSelectB = 31,

    kMatrixUnrollA = 40,
    kMatrixUnrollB = 41,

    kMatrixArgA = 60,
    kMatrixArgB = 61,
    kMatrixArgC = 62,
    kMatrixArgD = 63,

    kMaskMutateA = 70,
    kMaskMutateB = 71,
};

struct GSymbol {
    std::string                         mName;
    GSymbolType                         mType;
    TwistWorkSpaceSlot                  mSlot;
    TwistBufferKey                      mKey;
    
    GSymbol();
    static GSymbol                      Var(const std::string &pName);
    
    static GSymbol                      Var(TwistVariable pVariable);
    static GSymbol                      Var(TwistDomain pDomain, TwistConstants pConstant);
    static GSymbol                      WorkspaceDomainWord(TwistDomain pDomain, TwistConstants pConstant);
    static GSymbol                      Constant(TwistConstants pConstant);
    static GSymbol                      Buf(const TwistWorkSpaceSlot pSlot);
    static GSymbol                      Buf(const TwistBufferKey pKey);

    void                                Set(const GSymbol &pOther);
    void                                Invalidate();
    bool                                IsInvalid() const;
    
    bool                                IsVar() const;
    bool                                IsBuf() const;
    
};

bool                                    operator == (const GSymbol &pSymbolLHS, const GSymbol &pSymbolRHS);
bool                                    operator != (const GSymbol &pSymbolLHS, const GSymbol &pSymbolRHS);


std::string                             BufName(TwistWorkSpaceSlot slot);
std::string                             BufName(TwistBufferKey key);
std::string                             BufName(const GSymbol &symbol);
std::string                             BufAliasName(TwistWorkSpaceSlot slot);
std::string                             BufAliasName(TwistBufferKey key);
std::string                             BufAliasName(const GSymbol &symbol);
std::string                             BufferKeyToken(TwistBufferKey key);
bool                                    BufferKeyFromToken(const std::string &token,
                                                           TwistBufferKey *keyOut);
TwistBufferKey                          ResolveBufferKey(const GSymbol &symbol);
TwistWorkSpaceSlot                      ResolveBufferSlot(const GSymbol &symbol);
std::string                             WorkspaceDomainWordAliasName(TwistDomain domain,
                                                                     TwistConstants constant);
std::string                             WorkspaceDomainWordAccessText(TwistDomain domain,
                                                                      TwistConstants constant);
bool                                    WorkspaceDomainWordAliasInfo(const std::string &name,
                                                                     TwistDomain *domainOut,
                                                                     TwistConstants *constantOut);

GSymbol                                 VarSymbol(const std::string &pName);
GSymbol                                 BufSymbol(const TwistWorkSpaceSlot pSlot);
GSymbol                                 BufSymbol(const TwistBufferKey pKey);
GSymbol                                 BufParamSymbolDomainSalt(TwistWorkSpaceSlot pSlot);

#endif
