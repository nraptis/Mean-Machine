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

enum class TwistVariable : std::uint8_t {
    kIndex = 0,
    kCarry = 1,

    kPublicIngress = 2,
    kPublicPrevious = 3,
    kPublicScatter = 4,

    kPrivateIngress = 5,
    kPrivatePrevious = 6,
    kPrivateScatter = 7,
    kPrivateWrite = 8,

    kCrossIngress = 9,

    kUnwindA = 10,
    kUnwindB = 11,
    kUnwindC = 12,
    kUnwindD = 13,
    kUnwindE = 14,
    kUnwindF = 15,

    kOrbiterA = 16,
    kOrbiterB = 17,
    kOrbiterC = 18,
    kOrbiterD = 19,
    kOrbiterE = 20,
    kOrbiterF = 21,

    kPlugKeyA = 22,
    kPlugKeyB = 23,
    kPlugKeyC = 24,
    kPlugKeyD = 25,
    kPlugKeyE = 26,
    kPlugKeyF = 27,

    kPublicIngressDomainWord = 28,
    kPrivateIngressDomainWord = 29,
    kCrossIngressDomainWord = 30
};

enum class TwistConstants : std::uint8_t {
    kPublicIngress = 0,
    kPrivateIngress = 1,
    kCrossIngress = 2
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

GSymbol                                 VarSymbol(const std::string &pName);
GSymbol                                 BufSymbol(const TwistWorkSpaceSlot pSlot);
GSymbol                                 BufSymbol(const TwistBufferKey pKey);
GSymbol                                 BufParamSymbolDomainSalt(TwistSaltPhase pPhase,
                                                                 TwistSaltLane pLane);
GSymbol                                 BufParamSymbolDomainSBox(TwistSBoxLane pLane);

#endif
