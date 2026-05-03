//
//  GLoopMixBrew.hpp
//  MeanMachine
//
//  Created by Dragon on 4/29/26.
//

#ifndef GLoopMixBrew_hpp
#define GLoopMixBrew_hpp

#include "TwistWorkSpace.hpp"
#include "TwistMix64.hpp"
#include "GSeedProgram.hpp"
#include "GSymbol.hpp"
#include "GLoopFragmentComposer.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class GLoopMixBrewNode {
public:
    
    bool                                        mBefore = true;
    GLoopFragmentComposerCombineOp              mOp = GLoopFragmentComposerCombineOp::kAdd;
    GLoopFragmentComposerInput                  mInput;
};



class GLoopMixBrew {
    
public:
    enum class TargetCombineMode : std::uint8_t {
        kSet = 0,
        kAdd = 1,
        kXor = 2
    };

    enum class Mix64Family : std::uint8_t {
        kInv = 0,
        k1 = 1,
        k4 = 2,
        k8 = 3
    };

    GLoopMixBrew();
    
    
    GLoopFragmentComposerInputVariable          &PutVariableAdd(GSymbol pSymbol, bool pBefore);
    GLoopFragmentComposerInputVariable          &PutVariableMul(GSymbol pSymbol, bool pBefore);
    GLoopFragmentComposerInputVariable          &PutVariableXor(GSymbol pSymbol, bool pBefore);
    GLoopFragmentComposerInputVariable          &PutVariableRandom(GSymbol pSymbol, bool pBefore);
    
    GLoopFragmentComposerInputBuffer            &PutBufferAdd(GSymbol pSymbol, bool pBefore);
    GLoopFragmentComposerInputBuffer            &PutBufferMul(GSymbol pSymbol, bool pBefore);
    GLoopFragmentComposerInputBuffer            &PutBufferXor(GSymbol pSymbol, bool pBefore);
    GLoopFragmentComposerInputBuffer            &PutBufferRandom(GSymbol pSymbol, bool pBefore);
    
    bool                                        Bake(std::vector<GStatement> *pStatements,
                                                     std::string *pErrorMessage);
    
    
    bool                                        Bake(TargetCombineMode pCombineModeBefore,
                                                     TargetCombineMode pCombineModeAfter,
                                                     std::vector<GStatement> *pStatements,
                                                     std::string *pErrorMessage);
    
    std::vector<GLoopMixBrewNode>               mNodes;
    GSymbol                                     mLoopIndex;
    
    GSymbol                                     mTarget;
    GSymbol                                     mTargetMix;
    
    GSymbol                                     mMixSBoxA;
    GSymbol                                     mMixSBoxB;
    GSymbol                                     mMixSBoxC;
    GSymbol                                     mMixSBoxD;
    GSymbol                                     mMixSBoxE;
    GSymbol                                     mMixSBoxF;
    GSymbol                                     mMixSBoxG;
    GSymbol                                     mMixSBoxH;

    Mix64Family                                 mMix64Family = Mix64Family::kInv;
    Mix64Type_1                                 mMix64Type1 = Mix64Type_1::kInv;
    Mix64Type_4                                 mMix64Type4 = Mix64Type_4::kInv;
    Mix64Type_8                                 mMix64Type8 = Mix64Type_8::kInv;
    std::uint64_t                               mMix64Amount = 0U;
    bool                                        mMix64UseAmount = false;
    
    void                                        SetLoopIndex(GSymbol pLoopIndex);
    
    void                                        SetTarget(GSymbol pTarget, GSymbol pTargetMix);
    
    void                                        SetRandomOrderEnabled(bool pState);
    
    
    // Valid rotation amounts: 3, 5, 7, 11
    void                                        SetMix_1_Random(GSymbol pSBoxA);
    void                                        SetMix_4_Random(GSymbol pSBoxA, GSymbol pSBoxB, GSymbol pSBoxC, GSymbol pSBoxD);
    void                                        SetMix_8_Random(GSymbol pSBoxA, GSymbol pSBoxB, GSymbol pSBoxC, GSymbol pSBoxD,
                                                                GSymbol pSBoxE, GSymbol pSBoxF, GSymbol pSBoxG, GSymbol pSBoxH);

    void                                        SetMix_1(Mix64Type_1 pMixType, GSymbol pSBoxA);
    void                                        SetMix_4(Mix64Type_4 pMixType, GSymbol pSBoxA, GSymbol pSBoxB, GSymbol pSBoxC, GSymbol pSBoxD);
    void                                        SetMix_8(Mix64Type_8 pMixType, GSymbol pSBoxA, GSymbol pSBoxB, GSymbol pSBoxC, GSymbol pSBoxD,
                                                         GSymbol pSBoxE, GSymbol pSBoxF, GSymbol pSBoxG, GSymbol pSBoxH);

    void                                        SetMix_1(Mix64Type_1 pMixType, std::uint64_t pAmount, GSymbol pSBoxA);
    void                                        SetMix_4(Mix64Type_4 pMixType, std::uint64_t pAmount, GSymbol pSBoxA, GSymbol pSBoxB, GSymbol pSBoxC, GSymbol pSBoxD);
    void                                        SetMix_8(Mix64Type_8 pMixType, std::uint64_t pAmount, GSymbol pSBoxA, GSymbol pSBoxB, GSymbol pSBoxC, GSymbol pSBoxD,
                                                         GSymbol pSBoxE, GSymbol pSBoxF, GSymbol pSBoxG, GSymbol pSBoxH);
    
    
    
    bool                                        IsValidSBox(GSymbol pSymbol);
    
private:
    GExpr                                       BuildMixExpr(const GExpr &pInput) const;

    GLoopFragmentComposerInputVariable          &PutVariable(GSymbol pSymbol,
                                                             bool pBefore,
                                                             GLoopFragmentComposerCombineOp pOp);
    GLoopFragmentComposerInputBuffer            &PutBuffer(GSymbol pSymbol,
                                                           bool pBefore,
                                                           GLoopFragmentComposerCombineOp pOp);
    GLoopFragmentComposerInput                  BuildComposerInputForNode(const GLoopMixBrewNode &pNode) const;
    
    bool                                        mRandomOrderEnabled;
    
    
};

#endif /* GLoopMixBrew_hpp */
