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
#include "GTwistExpander.hpp"
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

class GLoopFragmentComposer;

class GLoopFragmentComposerInputBuffer {
public:
    GLoopFragmentComposerInputBuffer();
    
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
    
    GLoopFragmentComposerInputBuffer        &OffsetDebugMax();
    GLoopFragmentComposerInputBuffer        &Expand(std::uint8_t pExpandProbability,
                                                   bool pAllowMultiply);
    
    GLoopFragmentComposerInputBuffer        &ExpandDebug(GTermPattern pPattern, int pConstantA, int pConstantB);

    bool                                    IsValid() const;

private:
    friend class GLoopFragmentComposer;

    GLoopFragmentComposerInputBuffer(GLoopFragmentComposer *pComposer,
                                     std::size_t pNodeIndex);

    GLoopFragmentComposer                 *mComposer = nullptr;
    std::size_t                            mNodeIndex = 0U;
};

class GLoopFragmentComposerInputVariable {
public:
    GLoopFragmentComposerInputVariable();

    GLoopFragmentComposerInputVariable      &Expand(std::uint8_t pExpandProbability,
                                                   bool pAllowMultiply);
    GLoopFragmentComposerInputVariable      &ExpandDebug(GTermPattern pPattern, int pConstantA, int pConstantB);

    bool                                    IsValid() const;

private:
    friend class GLoopFragmentComposer;

    GLoopFragmentComposerInputVariable(GLoopFragmentComposer *pComposer,
                                       std::size_t pNodeIndex);

    GLoopFragmentComposer                 *mComposer = nullptr;
    std::size_t                            mNodeIndex = 0U;
};

class GLoopFragmentComposer {
public:
    GLoopFragmentComposer();
    explicit GLoopFragmentComposer(GSymbol pLoopIndex);
    ~GLoopFragmentComposer();

    void                                    Clear();
    
    // goes
    void                                    SetTarget(GSymbol pTarget);
    
    // We clear and pick our assign type, suck as =, +=, or ^=
    void                                    ResetSetEqual(GSymbol pTarget);
    void                                    ResetAddEqual(GSymbol pTarget);
    void                                    ResetXorEqual(GSymbol pTarget);
    
    void                                    EnableDebugMixAllAdd(); // there is no disable debug.
    void                                    EnableDebugMixAllXor();
    void                                    EnableDebugAddXor(const std::vector<bool> &pIsAdd);
    
    void                                    DisableDebug();
    
    
    //void                                   SetTarget(GSymbol pTarget);
    //void                                   SetTarget(GSymbol pTarget);
    //void                                   SetTarget(GSymbol pTarget);
    
    
    
    void                                   SetLoopIndex(GSymbol pLoopIndex);
    void                                   SetDefaultCombineWeights(int pXorWeight,
                                                                     int pAddWeight);

    GLoopFragmentComposerInputBuffer       MixBuffer(GSymbol pBuffer);
    GLoopFragmentComposerInputVariable     MixVariable(GSymbol pVariable);
    GLoopFragmentComposerInputBuffer       Transform(GSymbol pBuffer);
    

    bool                                   BakeStatements(std::vector<GStatement> *pStatementList,
                                                          std::string *pErrorString);

private:
    enum class NodeType : std::uint8_t {
        kInvalid = 0,
        kMixBuffer = 1,
        kMixVariable = 2,
        kTransform = 3
    };
    
    enum class DeferredCombineOp : std::uint8_t {
        kNone = 0,
        kAdd = 1,
        kXor = 2
    };

    struct Node {
        NodeType                         mType = NodeType::kInvalid;
        GSymbol                          mSymbol;
        GSymbol                          mBaseSymbol;
        bool                             mBaseFromBuffer = false;
        GSymbol                          mBaseBufferSymbol;
        GSymbol                          mBaseBufferIndexSymbol;
        bool                             mBaseBufferIndexOffsetIsRandom = false;
        int                              mBaseBufferIndexOffset = 0;
        GLoopFragmentDomain              mDomain = GLoopFragmentDomain::kAuto;
        bool                             mOffsetIsRandom = false;
        bool                             mOffsetIsDebugMax = false;
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
    bool                                   ConfigureNodeFixedOffset(std::size_t pNodeIndex,
                                                                    int pOffset);
    bool                                   ConfigureNodeOffsetDebugMax(std::size_t pNodeIndex);
    bool                                   ConfigureNodeExpand(std::size_t pNodeIndex,
                                                               std::uint8_t pExpandProbability,
                                                               bool pAllowMultiply);
    bool                                   ConfigureNodeExpandDebug(std::size_t pNodeIndex,
                                                                    GTermPattern pPattern,
                                                                    int pConstantA,
                                                                    int pConstantB);

    void                                   SetConfigError(const std::string &pErrorString);

    bool                                   AddStatement(std::vector<GStatement> *pStatementList,
                                                        const GStatement &pStatement,
                                                        std::string *pErrorString) const;
    bool                                   EmitTargetCombine(const GExpr &pOperandExpr,
                                                            bool *pTargetInitialized,
                                                            std::vector<GStatement> *pStatementList,
                                                            std::string *pErrorString);
    bool                                   EmitBufferNode(const Node &pNode,
                                                          bool *pTargetInitialized,
                                                          std::unordered_map<std::string, int> *pKeyNameCounters,
                                                          std::unordered_map<std::string, int> *pByteNameCounters,
                                                          std::vector<GStatement> *pStatementList,
                                                          std::string *pErrorString);
    bool                                   EmitVariableNode(const Node &pNode,
                                                            bool *pTargetInitialized,
                                                            std::unordered_map<std::string, int> *pVariableTempCounters,
                                                            std::vector<GStatement> *pStatementList,
                                                            std::string *pErrorString);

    GLoopFragmentDomain                    ResolveDomain(const Node &pNode) const;
    int                                    ResolveOffset(const Node &pNode,
                                                         const GSymbol &pBaseSymbol,
                                                         GLoopFragmentDomain pDomain,
                                                         std::string *pErrorString) const;
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
    bool                                   FlushDeferredCombine(std::vector<GStatement> *pStatementList,
                                                               std::string *pErrorString);
    bool                                   ConsumeDebugAddXorIsAdd() const;

    int                                    mCombineXorWeight = 55;
    int                                    mCombineAddWeight = 45;
    GAssignType                            mInitialAssignType = GAssignType::kSet;
    bool                                   mDebugMixAllAdd = false;
    bool                                   mDebugMixAllXor = false;
    bool                                   mDebugAddXorEnabled = false;
    std::vector<bool>                      mDebugAddXorPattern;
    mutable std::size_t                    mDebugAddXorCursor = 0U;
    bool                                   mDeferCombine = false;
    GSymbol                                mTarget;
    GSymbol                                mLoopIndex;
    std::vector<Node>                      mNodes;
    GAssignType                            mDeferredCombineAssignType = GAssignType::kInvalid;
    std::vector<GExpr>                     mDeferredCombineOperands;
    std::vector<DeferredCombineOp>         mDeferredCombineOps;
    std::string                            mConfigError;
};

#endif /* GLoopFragmentComposer_hpp */
