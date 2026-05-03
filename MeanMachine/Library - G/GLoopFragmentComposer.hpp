//
//  GLoopFragmentComposer.hpp
//  MeanMachine
//
//  Created by Trombone on 4/26/26.
//

#ifndef GLoopFragmentComposer_hpp
#define GLoopFragmentComposer_hpp

#include "GSeedProgram.hpp"
#include "GSymbol.hpp"
#include "GTermExpander.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

enum class GLoopFragmentDomain : std::uint8_t {
    kAuto = 0,
    kBlock = 1,
    kSBox = 2,
    kSalt = 3
};

enum class GLoopFragmentComposerCombineOp : std::uint8_t {
    kAdd = 0,
    kMul = 1,
    kXor = 2,
    kSub = 3
};

enum class GLoopFragmentComposerInputType : std::uint8_t {
    kInv = 0,
    kBuffer = 1,
    kVariable = 2
};

class GLoopFragmentComposer;
class GLoopFragmentComposerInput;

class GLoopFragmentComposerInputBuffer {
public:
    GLoopFragmentComposerInputBuffer();
    explicit GLoopFragmentComposerInputBuffer(GSymbol pBuffer);
    GLoopFragmentComposerInputBuffer(GSymbol pBuffer,
                                     GLoopFragmentComposerCombineOp pCombineOp);
    
    GLoopFragmentComposerInputBuffer        &Base(GSymbol pBaseIndex);
    GLoopFragmentComposerInputBuffer        &Key();
    GLoopFragmentComposerInputBuffer        &Key(GSymbol pKey);
    GLoopFragmentComposerInputBuffer        &KeyWithBuffer(GSymbol pBuffer,
                                                           GSymbol pBufferIndex,
                                                           int pBufferOffset);
    GLoopFragmentComposerInputBuffer        &KeyWithBufferRandomOffset(GSymbol pBuffer,
                                                                       GSymbol pBufferIndex);
    
    GLoopFragmentComposerInputBuffer        &Domain(GLoopFragmentDomain pDomain);
    GLoopFragmentComposerInputBuffer        &Offset();
    GLoopFragmentComposerInputBuffer        &Offset(int pOffset);
    GLoopFragmentComposerInputBuffer        &OffsetIverted();
    GLoopFragmentComposerInputBuffer        &OffsetIverted(int pOffset);
    GLoopFragmentComposerInputBuffer        &OffsetIvertedRandom();
    
    GLoopFragmentComposerInputBuffer        &OffsetDebugMax();
    GLoopFragmentComposerInputBuffer        &Expand(std::uint8_t pExpandProbability,
                                                   bool pAllowMultiply);
    
    GLoopFragmentComposerInputBuffer        &ExpandDebug(GTermPattern pPattern, int pConstantA, int pConstantB);
    GLoopFragmentComposerInputBuffer        &Combine(GLoopFragmentComposerCombineOp pCombineOp);
    GLoopFragmentComposerInputBuffer        &MixInt64Add();
    GLoopFragmentComposerInputBuffer        &MixInt64Xor();
    GLoopFragmentComposerInputBuffer        &MixInt64Mul();
    GLoopFragmentComposerInputBuffer        &MixInt64();
    GLoopFragmentComposerCombineOp          GetCombine() const;
    GLoopFragmentComposerInput              ToInput() const;

    bool                                    IsValid() const;

private:
    friend class GLoopFragmentComposer;

    GLoopFragmentComposerInputBuffer(GLoopFragmentComposer *pComposer,
                                     std::size_t pNodeIndex);

    void                                    InitializeDetached(GSymbol pBuffer,
                                                               GLoopFragmentComposerCombineOp pCombineOp);

    GLoopFragmentComposer                 *mComposer = nullptr;
    std::size_t                            mNodeIndex = 0U;
    GSymbol                                mSymbol;
    GLoopFragmentComposerCombineOp         mCombineOp = GLoopFragmentComposerCombineOp::kAdd;
    GSymbol                                mBaseSymbol;
    bool                                   mBaseFromBuffer = false;
    GSymbol                                mBaseBufferSymbol;
    GSymbol                                mBaseBufferIndexSymbol;
    bool                                   mBaseBufferIndexOffsetIsRandom = false;
    int                                    mBaseBufferIndexOffset = 0;
    GLoopFragmentDomain                    mDomain = GLoopFragmentDomain::kAuto;
    bool                                   mOffsetIsRandom = false;
    bool                                   mOffsetIsDebugMax = false;
    bool                                   mOffsetIsInverted = false;
    int                                    mOffset = 0;
    std::uint8_t                           mExpandProbability = 0U;
    bool                                   mAllowMultiply = true;
    bool                                   mHasDebugExpand = false;
    GTermPattern                           mDebugExpandPattern = GTermPattern::kAdd;
    int                                    mDebugExpandConstantA = 0;
    int                                    mDebugExpandConstantB = 0;
};

class GLoopFragmentComposerInputVariable {
public:
    GLoopFragmentComposerInputVariable();
    explicit GLoopFragmentComposerInputVariable(GSymbol pVariable);
    GLoopFragmentComposerInputVariable(GSymbol pVariable,
                                       GLoopFragmentComposerCombineOp pCombineOp);

    GLoopFragmentComposerInputVariable      &Expand(std::uint8_t pExpandProbability,
                                                   bool pAllowMultiply);
    GLoopFragmentComposerInputVariable      &ExpandDebug(GTermPattern pPattern, int pConstantA, int pConstantB);
    GLoopFragmentComposerInputVariable      &Combine(GLoopFragmentComposerCombineOp pCombineOp);
    GLoopFragmentComposerInputVariable      &MixInt64Add();
    GLoopFragmentComposerInputVariable      &MixInt64Xor();
    GLoopFragmentComposerInputVariable      &MixInt64Mul();
    GLoopFragmentComposerInputVariable      &MixInt64();
    GLoopFragmentComposerCombineOp          GetCombine() const;
    GLoopFragmentComposerInput              ToInput() const;

    bool                                    IsValid() const;

private:
    friend class GLoopFragmentComposer;

    GLoopFragmentComposerInputVariable(GLoopFragmentComposer *pComposer,
                                       std::size_t pNodeIndex);

    void                                    InitializeDetached(GSymbol pVariable,
                                                               GLoopFragmentComposerCombineOp pCombineOp);

    GLoopFragmentComposer                 *mComposer = nullptr;
    std::size_t                            mNodeIndex = 0U;
    GSymbol                                mSymbol;
    GLoopFragmentComposerCombineOp         mCombineOp = GLoopFragmentComposerCombineOp::kAdd;
    std::uint8_t                           mExpandProbability = 0U;
    bool                                   mAllowMultiply = true;
    bool                                   mHasDebugExpand = false;
    GTermPattern                           mDebugExpandPattern = GTermPattern::kAdd;
    int                                    mDebugExpandConstantA = 0;
    int                                    mDebugExpandConstantB = 0;
};

class GLoopFragmentComposerInput {
public:
    GLoopFragmentComposerInput() = default;
    explicit GLoopFragmentComposerInput(const GLoopFragmentComposerInputBuffer &pInputBuffer);
    explicit GLoopFragmentComposerInput(const GLoopFragmentComposerInputVariable &pInputVariable);

    bool                                    IsValid() const;

    GLoopFragmentComposerInputType          mType = GLoopFragmentComposerInputType::kInv;
    GLoopFragmentComposerInputBuffer        mInputBuffer;
    GLoopFragmentComposerInputVariable      mInputVariable;
};

class GLoopFragmentComposer {
public:
    GLoopFragmentComposer();
    explicit GLoopFragmentComposer(GSymbol pLoopIndex);
    ~GLoopFragmentComposer();

    void                                    Clear();
    
    // goes
    void                                    SetTarget(GSymbol pTarget);
    GSymbol                                 GetTarget() const;
    
    // We clear and pick how the composed expression combines with target.
    void                                    ResetSetEqual(GSymbol pTarget);
    void                                    ResetAddEqual(GSymbol pTarget);
    void                                    ResetXorEqual(GSymbol pTarget);
    
    void                                    SetLoopIndex(GSymbol pLoopIndex);

    GLoopFragmentComposerInputBuffer        MixBuffer(GSymbol pBuffer);
    GLoopFragmentComposerInputBuffer        MixBufferAdd(GSymbol pBuffer);
    GLoopFragmentComposerInputBuffer        MixBufferMul(GSymbol pBuffer);
    GLoopFragmentComposerInputBuffer        MixBufferXor(GSymbol pBuffer);
    GLoopFragmentComposerInputBuffer        MixInt64Add(GSymbol pBuffer);
    GLoopFragmentComposerInputBuffer        MixInt64Xor(GSymbol pBuffer);
    GLoopFragmentComposerInputBuffer        MixInt64Mul(GSymbol pBuffer);
    GLoopFragmentComposerInputBuffer        MixInt64(GSymbol pBuffer);
    GLoopFragmentComposerInputBuffer        &MixInt64Add();
    GLoopFragmentComposerInputBuffer        &MixInt64Xor();
    GLoopFragmentComposerInputBuffer        &MixInt64Mul();
    GLoopFragmentComposerInputBuffer        &MixInt64();

    GLoopFragmentComposerInputVariable      MixVariable(GSymbol pVariable);
    GLoopFragmentComposerInputVariable      MixVariableAdd(GSymbol pVariable);
    GLoopFragmentComposerInputVariable      MixVariableMul(GSymbol pVariable);
    GLoopFragmentComposerInputVariable      MixVariableXor(GSymbol pVariable);

    bool                                    AddInput(const GLoopFragmentComposerInputBuffer &pInputBuffer);
    bool                                    AddInput(const GLoopFragmentComposerInputVariable &pInputVariable);
    bool                                    AddInput(const GLoopFragmentComposerInput &pInput);
    bool                                    AddInputs(const std::vector<GLoopFragmentComposerInput> &pInputs);
    GLoopFragmentComposer                   &Shuffle();

    bool                                    Bake(std::vector<GStatement> *pStatements,
                                                          std::string *pErrorMessage);
    
    bool                                    ResolveToStatementsAndExpression(std::vector<GStatement> *pStatements,
                                                                             GExpr &pExpr,
                                                                             std::string *pErrorMessage);
    

private:
    enum class TargetCombineMode : std::uint8_t {
        kInvalid = 0,
        kSet = 1,
        kAdd = 2,
        kXor = 3
    };

    enum class NodeType : std::uint8_t {
        kInvalid = 0,
        kMixBuffer = 1,
        kMixVariable = 2
    };
    
    enum class DeferredCombineOp : std::uint8_t {
        kNone = 0,
        kAdd = 1,
        kMul = 2,
        kXor = 3,
        kSub = 4
    };

    struct Node {
        NodeType                         mType = NodeType::kInvalid;
        GSymbol                          mSymbol;
        GLoopFragmentComposerCombineOp   mCombineOp = GLoopFragmentComposerCombineOp::kAdd;
        GSymbol                          mBaseSymbol;
        bool                             mBaseFromBuffer = false;
        GSymbol                          mBaseBufferSymbol;
        GSymbol                          mBaseBufferIndexSymbol;
        bool                             mBaseBufferIndexOffsetIsRandom = false;
        int                              mBaseBufferIndexOffset = 0;
        GLoopFragmentDomain              mDomain = GLoopFragmentDomain::kAuto;
        bool                             mOffsetIsRandom = false;
        bool                             mOffsetIsDebugMax = false;
        bool                             mOffsetIsInverted = false;
        int                              mOffset = 0;
        std::uint8_t                     mExpandProbability = 0U;
        bool                             mAllowMultiply = true;
        bool                             mHasDebugExpand = false;
        GTermPattern                     mDebugExpandPattern = GTermPattern::kAdd;
        int                              mDebugExpandConstantA = 0;
        int                              mDebugExpandConstantB = 0;
    };

    struct BufferTemp {
        GSymbol                          mKeySymbol;
        GSymbol                          mByteSymbol;
    };

    friend class GLoopFragmentComposerInputBuffer;
    friend class GLoopFragmentComposerInputVariable;

    bool                                   ConfigureNodeBase(std::size_t pNodeIndex,
                                                             GSymbol pBaseIndex);
    bool                                   ConfigureNodeBaseFromBuffer(std::size_t pNodeIndex,
                                                                       GSymbol pBuffer,
                                                                       GSymbol pBufferIndex,
                                                                       int pBufferOffset);
    bool                                   ConfigureNodeBaseFromBufferRandomOffset(std::size_t pNodeIndex,
                                                                                   GSymbol pBuffer,
                                                                                   GSymbol pBufferIndex);
    bool                                   ConfigureNodeLoopKey(std::size_t pNodeIndex);
    bool                                   ConfigureNodeDomain(std::size_t pNodeIndex,
                                                               GLoopFragmentDomain pDomain);
    bool                                   ConfigureNodeRandomOffset(std::size_t pNodeIndex);
    bool                                   ConfigureNodeInvertedRandomOffset(std::size_t pNodeIndex);
    bool                                   ConfigureNodeFixedOffset(std::size_t pNodeIndex,
                                                                    int pOffset);
    bool                                   ConfigureNodeInvertedOffset(std::size_t pNodeIndex,
                                                                       int pOffset);
    bool                                   ConfigureNodeOffsetDebugMax(std::size_t pNodeIndex);
    bool                                   ConfigureNodeExpand(std::size_t pNodeIndex,
                                                               std::uint8_t pExpandProbability,
                                                               bool pAllowMultiply);
    bool                                   ConfigureNodeExpandDebug(std::size_t pNodeIndex,
                                                                    GTermPattern pPattern,
                                                                    int pConstantA,
                                                                    int pConstantB);

    void                                   SetConfigError(const std::string &pErrorMessage);

    bool                                   AddStatement(std::vector<GStatement> *pStatements,
                                                        const GStatement &pStatement,
                                                        std::string *pErrorMessage) const;
    bool                                   EmitTargetCombine(const GExpr &pOperandExpr,
                                                            GLoopFragmentComposerCombineOp pCombineOp,
                                                            bool *pTargetInitialized,
                                                            std::vector<GStatement> *pStatements,
                                                            std::string *pErrorMessage);
    bool                                   EmitBufferNode(const Node &pNode,
                                                          bool *pTargetInitialized,
                                                          std::unordered_map<std::string, int> *pKeyNameCounters,
                                                          std::unordered_map<std::string, int> *pByteNameCounters,
                                                          std::vector<GStatement> *pStatements,
                                                          std::string *pErrorMessage);
    bool                                   EmitVariableNode(const Node &pNode,
                                                            bool *pTargetInitialized,
                                                            std::unordered_map<std::string, int> *pVariableTempCounters,
                                                            std::vector<GStatement> *pStatements,
                                                            std::string *pErrorMessage);
    bool                                   FillNodeFromInputBuffer(const GLoopFragmentComposerInputBuffer &pInputBuffer,
                                                                   Node *pNode,
                                                                   std::string *pErrorMessage) const;
    bool                                   FillNodeFromInputVariable(const GLoopFragmentComposerInputVariable &pInputVariable,
                                                                     Node *pNode,
                                                                     std::string *pErrorMessage) const;

    GLoopFragmentDomain                    ResolveDomain(const Node &pNode) const;
    int                                    ResolveOffset(const Node &pNode,
                                                         const GSymbol &pBaseSymbol,
                                                         GLoopFragmentDomain pDomain,
                                                         std::string *pErrorMessage) const;
    BufferTemp                             BuildBufferTemp(const Node &pNode,
                                                          bool pNeedKey,
                                                          bool pNeedByte,
                                                          std::unordered_map<std::string, int> *pKeyNameCounters,
                                                          std::unordered_map<std::string, int> *pByteNameCounters) const;
    GSymbol                                BuildVariableTemp(const GSymbol &pVariable,
                                                            std::unordered_map<std::string, int> *pVariableTempCounters) const;
    GExpr                                  BuildExpandedExpression(const GExpr &pBaseExpr,
                                                                   bool pAllowMultiply) const;
    GExpr                                  BuildExpandedExpressionDebug(const Node &pNode,
                                                                        const GExpr &pBaseExpr) const;
    bool                                   ShouldDeferCombine() const;
    GExpr                                  BuildDeferredExpression() const;
    bool                                   FlushDeferredCombine(std::vector<GStatement> *pStatements,
                                                               std::string *pErrorMessage);

    TargetCombineMode                      mInitialCombineMode = TargetCombineMode::kSet;
    bool                                   mDeferCombine = false;
    GSymbol                                mTarget;
    GSymbol                                mLoopIndex;
    std::vector<Node>                      mNodes;
    TargetCombineMode                      mDeferredCombineMode = TargetCombineMode::kInvalid;
    std::vector<GExpr>                     mDeferredCombineOperands;
    std::vector<DeferredCombineOp>         mDeferredCombineOps;
    GLoopFragmentComposerCombineOp         mDeferredNextCombineOp = GLoopFragmentComposerCombineOp::kAdd;
    std::string                            mConfigError;
    bool                                   mShufflePending = false;
    GLoopFragmentComposerInputBuffer       mLastBufferInputHandle;
};

#endif /* GLoopFragmentComposer_hpp */
