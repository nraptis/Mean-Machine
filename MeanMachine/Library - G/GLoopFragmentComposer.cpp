//
//  GLoopFragmentComposer.cpp
//  MeanMachine
//
//  Created by Trombone on 4/26/26.
//

#include "GLoopFragmentComposer.hpp"

#include "Random.hpp"
#include "TwistFunctional.hpp"

#include <algorithm>

namespace {

void SetError(std::string *pErrorString,
              const std::string &pMessage) {
    if (pErrorString != nullptr) {
        *pErrorString = pMessage;
    }
}

bool IsLoopIndexLike(const GSymbol &pSymbol) {
    if (!pSymbol.IsVar()) {
        return false;
    }
    return pSymbol.mName.find("LoopIndex") != std::string::npos;
}

bool IsSBoxSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSBoxA:
        case TwistWorkSpaceSlot::kSBoxB:
        case TwistWorkSpaceSlot::kSBoxC:
        case TwistWorkSpaceSlot::kSBoxD:
            return true;
        default:
            return false;
    }
}

bool IsSaltSlot(const TwistWorkSpaceSlot pSlot) {
    switch (pSlot) {
        case TwistWorkSpaceSlot::kSaltA:
        case TwistWorkSpaceSlot::kSaltB:
        case TwistWorkSpaceSlot::kSaltC:
        case TwistWorkSpaceSlot::kSaltD:
            return true;
        default:
            return false;
    }
}

int PositiveMod(const int pValue,
                const int pBase) {
    if (pBase <= 0) {
        return pValue;
    }
    int aValue = pValue % pBase;
    if (aValue < 0) {
        aValue += pBase;
    }
    return aValue;
}

std::string SuffixForCounter(int pCounter) {
    if (pCounter < 0) {
        pCounter = 0;
    }

    std::string aSuffix;
    int aValue = pCounter;
    do {
        const int aCharIndex = aValue % 26;
        aSuffix.insert(aSuffix.begin(), static_cast<char>('A' + aCharIndex));
        aValue = (aValue / 26) - 1;
    } while (aValue >= 0);

    return aSuffix;
}

bool EndsWith(const std::string &pText,
              const std::string &pSuffix) {
    if (pSuffix.size() > pText.size()) {
        return false;
    }
    return pText.compare(pText.size() - pSuffix.size(), pSuffix.size(), pSuffix) == 0;
}

bool StartsWith(const std::string &pText,
                const std::string &pPrefix) {
    if (pPrefix.size() > pText.size()) {
        return false;
    }
    return pText.compare(0U, pPrefix.size(), pPrefix) == 0;
}

bool IsWideIndexVariableName(const std::string &pName) {
    return EndsWith(pName, "Key") || StartsWith(pName, "aOracle");
}

bool CanUseDirectBlockIndex(const GSymbol &pIndexSymbol,
                            const GSymbol &pLoopIndex) {
    if (!pIndexSymbol.IsVar()) {
        return false;
    }
    if (!pLoopIndex.IsInvalid() && (pIndexSymbol == pLoopIndex)) {
        return true;
    }
    return !IsWideIndexVariableName(pIndexSymbol.mName);
}

std::string KeyStemForSymbol(const GSymbol &pSymbol) {
    if (pSymbol.IsVar()) {
        return pSymbol.mName;
    }
    if (pSymbol.IsBuf()) {
        return BufAliasName(pSymbol.mSlot);
    }
    return "key";
}

} // namespace

GLoopFragmentComposerInputBuffer::GLoopFragmentComposerInputBuffer() = default;

GLoopFragmentComposerInputBuffer::GLoopFragmentComposerInputBuffer(GLoopFragmentComposer *pComposer,
                                                                   std::size_t pNodeIndex) {
    mComposer = pComposer;
    mNodeIndex = pNodeIndex;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Base(GSymbol pBaseIndex) {
    if (IsValid()) {
        mComposer->ConfigureNodeBase(mNodeIndex, pBaseIndex);
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Key() {
    if (IsValid()) {
        mComposer->ConfigureNodeLoopKey(mNodeIndex);
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Key(GSymbol pKey) {
    return Base(pKey);
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::KeyWithBuffer(GSymbol pBuffer,
                                                                                   GSymbol pBufferIndex,
                                                                                   int pBufferOffset) {
    if (IsValid()) {
        mComposer->ConfigureNodeBaseFromBuffer(mNodeIndex, pBuffer, pBufferIndex, pBufferOffset);
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::KeyWithBufferRandomOffset(GSymbol pBuffer,
                                                                                               GSymbol pBufferIndex) {
    if (IsValid()) {
        mComposer->ConfigureNodeBaseFromBufferRandomOffset(mNodeIndex, pBuffer, pBufferIndex);
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Domain(GLoopFragmentDomain pDomain) {
    if (IsValid()) {
        mComposer->ConfigureNodeDomain(mNodeIndex, pDomain);
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Offset() {
    if (IsValid()) {
        mComposer->ConfigureNodeRandomOffset(mNodeIndex);
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Offset(int pOffset) {
    if (IsValid()) {
        mComposer->ConfigureNodeFixedOffset(mNodeIndex, pOffset);
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::OffsetDebugMax() {
    if (IsValid()) {
        mComposer->ConfigureNodeOffsetDebugMax(mNodeIndex);
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Expand(std::uint8_t pExpandProbability,
                                                                           bool pAllowMultiply) {
    if (IsValid()) {
        mComposer->ConfigureNodeExpand(mNodeIndex, pExpandProbability, pAllowMultiply);
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::ExpandDebug(GTermPattern pPattern,
                                                                                 int pConstantA,
                                                                                 int pConstantB) {
    if (IsValid()) {
        mComposer->ConfigureNodeExpandDebug(mNodeIndex, pPattern, pConstantA, pConstantB);
    }
    return *this;
}

bool GLoopFragmentComposerInputBuffer::IsValid() const {
    return (mComposer != nullptr) && (mNodeIndex < mComposer->mNodes.size());
}

GLoopFragmentComposerInputVariable::GLoopFragmentComposerInputVariable() = default;

GLoopFragmentComposerInputVariable::GLoopFragmentComposerInputVariable(GLoopFragmentComposer *pComposer,
                                                                       std::size_t pNodeIndex) {
    mComposer = pComposer;
    mNodeIndex = pNodeIndex;
}

GLoopFragmentComposerInputVariable &GLoopFragmentComposerInputVariable::Expand(std::uint8_t pExpandProbability,
                                                                               bool pAllowMultiply) {
    if (IsValid()) {
        mComposer->ConfigureNodeExpand(mNodeIndex, pExpandProbability, pAllowMultiply);
    }
    return *this;
}

GLoopFragmentComposerInputVariable &GLoopFragmentComposerInputVariable::ExpandDebug(GTermPattern pPattern,
                                                                                     int pConstantA,
                                                                                     int pConstantB) {
    if (IsValid()) {
        mComposer->ConfigureNodeExpandDebug(mNodeIndex, pPattern, pConstantA, pConstantB);
    }
    return *this;
}

bool GLoopFragmentComposerInputVariable::IsValid() const {
    return (mComposer != nullptr) && (mNodeIndex < mComposer->mNodes.size());
}

GLoopFragmentComposer::GLoopFragmentComposer() = default;

GLoopFragmentComposer::GLoopFragmentComposer(GSymbol pLoopIndex) {
    mLoopIndex = pLoopIndex;
}

GLoopFragmentComposer::~GLoopFragmentComposer() = default;

void GLoopFragmentComposer::Clear() {
    mNodes.clear();
    mDeferredCombineOperands.clear();
    mDeferredCombineOps.clear();
    mDeferCombine = false;
    mDeferredCombineAssignType = GAssignType::kInvalid;
    mConfigError.clear();
}

void GLoopFragmentComposer::SetTarget(GSymbol pTarget) {
    mTarget = pTarget;
}

void GLoopFragmentComposer::ResetSetEqual(GSymbol pTarget) {
    Clear();
    SetTarget(pTarget);
    mInitialAssignType = GAssignType::kSet;
    DisableDebug();
}

void GLoopFragmentComposer::ResetAddEqual(GSymbol pTarget) {
    Clear();
    SetTarget(pTarget);
    mInitialAssignType = GAssignType::kAddAssign;
    DisableDebug();
}

void GLoopFragmentComposer::ResetXorEqual(GSymbol pTarget) {
    Clear();
    SetTarget(pTarget);
    mInitialAssignType = GAssignType::kXorAssign;
    DisableDebug();
}

void GLoopFragmentComposer::EnableDebugMixAllAdd() {
    mDebugMixAllAdd = true;
    mDebugMixAllXor = false;
    mDebugAddXorEnabled = false;
    mDebugAddXorPattern.clear();
    mDebugAddXorCursor = 0U;
}

void GLoopFragmentComposer::EnableDebugMixAllXor() {
    mDebugMixAllXor = true;
    mDebugMixAllAdd = false;
    mDebugAddXorEnabled = false;
    mDebugAddXorPattern.clear();
    mDebugAddXorCursor = 0U;
}

void GLoopFragmentComposer::EnableDebugAddXor(const std::vector<bool> &pIsAdd) {
    mDebugMixAllAdd = false;
    mDebugMixAllXor = false;
    mDebugAddXorEnabled = !pIsAdd.empty();
    mDebugAddXorPattern = pIsAdd;
    mDebugAddXorCursor = 0U;
}

void GLoopFragmentComposer::DisableDebug() {
    mDebugMixAllAdd = false;
    mDebugMixAllXor = false;
    mDebugAddXorEnabled = false;
    mDebugAddXorPattern.clear();
    mDebugAddXorCursor = 0U;
}

void GLoopFragmentComposer::SetLoopIndex(GSymbol pLoopIndex) {
    mLoopIndex = pLoopIndex;
}

void GLoopFragmentComposer::SetDefaultCombineWeights(int pXorWeight,
                                                     int pAddWeight) {
    mCombineXorWeight = pXorWeight;
    mCombineAddWeight = pAddWeight;
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::MixBuffer(GSymbol pBuffer) {
    Node aNode;
    aNode.mType = NodeType::kMixBuffer;
    aNode.mSymbol = pBuffer;
    aNode.mBaseSymbol = mLoopIndex.IsInvalid() ? mTarget : mLoopIndex;
    mNodes.push_back(aNode);
    if (!pBuffer.IsBuf()) {
        SetConfigError("MixBuffer expected a buffer symbol.");
    }
    return GLoopFragmentComposerInputBuffer(this, mNodes.size() - 1U);
}

GLoopFragmentComposerInputVariable GLoopFragmentComposer::MixVariable(GSymbol pVariable) {
    Node aNode;
    aNode.mType = NodeType::kMixVariable;
    aNode.mSymbol = pVariable;
    mNodes.push_back(aNode);
    if (!pVariable.IsVar()) {
        SetConfigError("MixVariable expected a variable symbol.");
    }
    return GLoopFragmentComposerInputVariable(this, mNodes.size() - 1U);
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::Transform(GSymbol pBuffer) {
    Node aNode;
    aNode.mType = NodeType::kTransform;
    aNode.mSymbol = pBuffer;
    aNode.mBaseSymbol = mTarget.IsInvalid() ? mLoopIndex : mTarget;
    mNodes.push_back(aNode);
    if (!pBuffer.IsBuf() && !pBuffer.IsVar()) {
        SetConfigError("Transform expected a buffer or variable symbol.");
    }
    return GLoopFragmentComposerInputBuffer(this, mNodes.size() - 1U);
}

bool GLoopFragmentComposer::ConfigureNodeBase(std::size_t pNodeIndex,
                                              GSymbol pBaseIndex) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting base.");
        return false;
    }
    if (pBaseIndex.IsInvalid()) {
        SetConfigError("Composer base symbol was invalid.");
        return false;
    }
    mNodes[pNodeIndex].mBaseSymbol = pBaseIndex;
    mNodes[pNodeIndex].mBaseFromBuffer = false;
    mNodes[pNodeIndex].mBaseBufferSymbol.Invalidate();
    mNodes[pNodeIndex].mBaseBufferIndexSymbol.Invalidate();
    mNodes[pNodeIndex].mBaseBufferIndexOffsetIsRandom = false;
    mNodes[pNodeIndex].mBaseBufferIndexOffset = 0;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeBaseFromBuffer(std::size_t pNodeIndex,
                                                        GSymbol pBuffer,
                                                        GSymbol pBufferIndex,
                                                        int pBufferOffset) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting buffer-based key.");
        return false;
    }
    if (!pBuffer.IsBuf()) {
        SetConfigError("Composer buffer-based key source must be a buffer symbol.");
        return false;
    }
    if (!pBufferIndex.IsVar()) {
        SetConfigError("Composer buffer-based key index must be a variable symbol.");
        return false;
    }
    if (pBufferOffset < 0) {
        SetConfigError("Composer buffer-based key offset must be >= 0.");
        return false;
    }

    Node &aNode = mNodes[pNodeIndex];
    aNode.mBaseFromBuffer = true;
    aNode.mBaseBufferSymbol = pBuffer;
    aNode.mBaseBufferIndexSymbol = pBufferIndex;
    aNode.mBaseBufferIndexOffsetIsRandom = false;
    aNode.mBaseBufferIndexOffset = pBufferOffset;
    aNode.mBaseSymbol = pBufferIndex;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeBaseFromBufferRandomOffset(std::size_t pNodeIndex,
                                                                    GSymbol pBuffer,
                                                                    GSymbol pBufferIndex) {
    if (!ConfigureNodeBaseFromBuffer(pNodeIndex, pBuffer, pBufferIndex, 0)) {
        return false;
    }
    mNodes[pNodeIndex].mBaseBufferIndexOffsetIsRandom = true;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeLoopKey(std::size_t pNodeIndex) {
    if (mLoopIndex.IsInvalid()) {
        SetConfigError("Composer loop key requested, but loop symbol was invalid.");
        return false;
    }
    return ConfigureNodeBase(pNodeIndex, mLoopIndex);
}

bool GLoopFragmentComposer::ConfigureNodeDomain(std::size_t pNodeIndex,
                                                GLoopFragmentDomain pDomain) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting domain.");
        return false;
    }
    mNodes[pNodeIndex].mDomain = pDomain;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeRandomOffset(std::size_t pNodeIndex) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting offset.");
        return false;
    }
    mNodes[pNodeIndex].mOffsetIsRandom = true;
    mNodes[pNodeIndex].mOffsetIsDebugMax = false;
    mNodes[pNodeIndex].mOffset = 0;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeFixedOffset(std::size_t pNodeIndex,
                                                     int pOffset) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting offset.");
        return false;
    }
    mNodes[pNodeIndex].mOffsetIsRandom = false;
    mNodes[pNodeIndex].mOffsetIsDebugMax = false;
    mNodes[pNodeIndex].mOffset = pOffset;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeOffsetDebugMax(std::size_t pNodeIndex) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting max-debug offset.");
        return false;
    }
    mNodes[pNodeIndex].mOffsetIsRandom = false;
    mNodes[pNodeIndex].mOffsetIsDebugMax = true;
    mNodes[pNodeIndex].mOffset = 0;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeExpand(std::size_t pNodeIndex,
                                                std::uint8_t pExpandProbability,
                                                bool pAllowMultiply) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting expansion.");
        return false;
    }
    mNodes[pNodeIndex].mExpandProbability = pExpandProbability;
    mNodes[pNodeIndex].mAllowMultiply = pAllowMultiply;
    mNodes[pNodeIndex].mHasDebugExpand = false;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeExpandDebug(std::size_t pNodeIndex,
                                                     GTermPattern pPattern,
                                                     int pConstantA,
                                                     int pConstantB) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting debug expansion.");
        return false;
    }
    mNodes[pNodeIndex].mHasDebugExpand = true;
    mNodes[pNodeIndex].mDebugExpandPattern = pPattern;
    mNodes[pNodeIndex].mDebugExpandConstantA = pConstantA;
    mNodes[pNodeIndex].mDebugExpandConstantB = pConstantB;
    mNodes[pNodeIndex].mExpandProbability = 100U;
    return true;
}

void GLoopFragmentComposer::SetConfigError(const std::string &pErrorString) {
    if (mConfigError.empty()) {
        mConfigError = pErrorString;
    }
}

bool GLoopFragmentComposer::AddStatement(std::vector<GStatement> *pStatementList,
                                         const GStatement &pStatement,
                                         std::string *pErrorString) const {
    if (pStatementList == nullptr) {
        SetError(pErrorString, "Composer output statement list was null.");
        return false;
    }
    if (pStatement.IsInvalid()) {
        SetError(pErrorString, "Composer attempted to emit an invalid statement.");
        return false;
    }
    pStatementList->push_back(pStatement);
    return true;
}

bool GLoopFragmentComposer::EmitTargetCombine(const GExpr &pOperandExpr,
                                              bool *pTargetInitialized,
                                              std::vector<GStatement> *pStatementList,
                                              std::string *pErrorString) {
    if ((pTargetInitialized == nullptr) || pOperandExpr.IsInvalid()) {
        SetError(pErrorString, "Composer could not combine into target due to invalid state.");
        return false;
    }

    if (mDeferCombine) {
        if (mDeferredCombineOperands.empty()) {
            if (!(*pTargetInitialized)) {
                mDeferredCombineAssignType = mInitialAssignType;
            } else if (mDebugMixAllAdd) {
                mDeferredCombineAssignType = GAssignType::kAddAssign;
            } else if (mDebugMixAllXor) {
                mDeferredCombineAssignType = GAssignType::kXorAssign;
            } else {
                mDeferredCombineAssignType = GAssignType::kSet;
                mDeferredCombineOperands.push_back(GExpr::Symbol(mTarget));
            }
        }

        if (!mDeferredCombineOperands.empty()) {
            DeferredCombineOp aCombineOp = DeferredCombineOp::kNone;

            if (mDebugMixAllAdd) {
                aCombineOp = DeferredCombineOp::kAdd;
            } else if (mDebugMixAllXor) {
                aCombineOp = DeferredCombineOp::kXor;
            } else if (mDebugAddXorEnabled) {
                aCombineOp = ConsumeDebugAddXorIsAdd() ? DeferredCombineOp::kAdd
                                                       : DeferredCombineOp::kXor;
            } else {
                const int aXorWeight = std::max(0, mCombineXorWeight);
                const int aAddWeight = std::max(0, mCombineAddWeight);
                const int aTotalWeight = aXorWeight + aAddWeight;

                if ((aTotalWeight == 0) || (Random::Get(aTotalWeight) < aXorWeight)) {
                    aCombineOp = DeferredCombineOp::kXor;
                } else {
                    aCombineOp = DeferredCombineOp::kAdd;
                }
            }

            if (aCombineOp == DeferredCombineOp::kNone) {
                SetError(pErrorString, "Composer could not resolve deferred combine operation.");
                return false;
            }
            mDeferredCombineOps.push_back(aCombineOp);
        }
        mDeferredCombineOperands.push_back(pOperandExpr);
        *pTargetInitialized = true;
        return true;
    }

    if (!(*pTargetInitialized)) {
        *pTargetInitialized = true;
        GStatement aStatement;
        switch (mInitialAssignType) {
            case GAssignType::kAddAssign:
                aStatement = GStatement::AddAssign(GTarget::Symbol(mTarget),
                                                   pOperandExpr);
                break;
            case GAssignType::kXorAssign:
                aStatement = GStatement::XorAssign(GTarget::Symbol(mTarget),
                                                   pOperandExpr);
                break;
            case GAssignType::kSet:
            default:
                aStatement = GStatement::Assign(GTarget::Symbol(mTarget),
                                                pOperandExpr);
                break;
        }
        return AddStatement(pStatementList, aStatement, pErrorString);
    }

    if (mDebugMixAllAdd) {
        return AddStatement(pStatementList,
                            GStatement::AddAssign(GTarget::Symbol(mTarget),
                                                  pOperandExpr),
                            pErrorString);
    }
    if (mDebugMixAllXor) {
        return AddStatement(pStatementList,
                            GStatement::XorAssign(GTarget::Symbol(mTarget),
                                                  pOperandExpr),
                            pErrorString);
    }
    if (mDebugAddXorEnabled) {
        if (ConsumeDebugAddXorIsAdd()) {
            return AddStatement(pStatementList,
                                GStatement::AddAssign(GTarget::Symbol(mTarget),
                                                      pOperandExpr),
                                pErrorString);
        }
        return AddStatement(pStatementList,
                            GStatement::XorAssign(GTarget::Symbol(mTarget),
                                                  pOperandExpr),
                            pErrorString);
    }

    const int aXorWeight = std::max(0, mCombineXorWeight);
    const int aAddWeight = std::max(0, mCombineAddWeight);
    const int aTotalWeight = aXorWeight + aAddWeight;

    if ((aTotalWeight == 0) || (Random::Get(aTotalWeight) < aXorWeight)) {
        return AddStatement(pStatementList,
                            GStatement::XorAssign(GTarget::Symbol(mTarget),
                                                  pOperandExpr),
                            pErrorString);
    }

    return AddStatement(pStatementList,
                        GStatement::AddAssign(GTarget::Symbol(mTarget),
                                              pOperandExpr),
                        pErrorString);
}

bool GLoopFragmentComposer::EmitBufferNode(const Node &pNode,
                                           bool *pTargetInitialized,
                                           std::unordered_map<std::string, int> *pKeyNameCounters,
                                           std::unordered_map<std::string, int> *pByteNameCounters,
                                           std::vector<GStatement> *pStatementList,
                                           std::string *pErrorString) {
    const bool aIsBufferTransform = pNode.mSymbol.IsBuf();
    const bool aIsVariableTransform = (pNode.mType == NodeType::kTransform) && pNode.mSymbol.IsVar();
    if (!aIsBufferTransform && !aIsVariableTransform) {
        SetError(pErrorString, "Composer node had an invalid symbol for buffer/transform emission.");
        return false;
    }
    if (pNode.mType != NodeType::kMixBuffer && pNode.mType != NodeType::kTransform) {
        SetError(pErrorString, "Composer buffer node had an invalid type.");
        return false;
    }

    bool aShouldExpand = false;
    if (pNode.mHasDebugExpand) {
        aShouldExpand = true;
    } else if ((pNode.mExpandProbability > 0U) && Random::Chance(pNode.mExpandProbability)) {
        aShouldExpand = true;
    }

    if (aIsVariableTransform) {
        const GExpr aBaseExpr = GExpr::Symbol(pNode.mSymbol);
        const GExpr aTransformExpr = aShouldExpand
            ? (pNode.mHasDebugExpand
               ? BuildExpandedExpressionDebug(pNode, aBaseExpr)
               : BuildExpandedExpression(aBaseExpr, pNode.mAllowMultiply))
            : aBaseExpr;
        if (pTargetInitialized != nullptr) {
            *pTargetInitialized = true;
        }
        return AddStatement(pStatementList,
                            GStatement::Assign(GTarget::Symbol(mTarget), aTransformExpr),
                            pErrorString);
    }

    const GLoopFragmentDomain aDomain = ResolveDomain(pNode);
    GSymbol aBaseSymbol = pNode.mBaseSymbol.IsInvalid()
        ? ((pNode.mType == NodeType::kTransform)
           ? mTarget
           : (mLoopIndex.IsInvalid() ? mTarget : mLoopIndex))
        : pNode.mBaseSymbol;

    GExpr aBaseExpr;
    if (pNode.mBaseFromBuffer) {
        if (!pNode.mBaseBufferSymbol.IsBuf() || !pNode.mBaseBufferIndexSymbol.IsVar()) {
            SetError(pErrorString, "Composer buffer node had an invalid buffer-based key source.");
            return false;
        }
        if (pNode.mBaseBufferIndexOffset < 0) {
            SetError(pErrorString, "Composer buffer-based key offset must be >= 0.");
            return false;
        }

        constexpr int kMaxByteValue = 255;
        const int aMaxSafeBlockOffset = std::max(0, S_BLOCK - (kMaxByteValue + 1));

        int aBaseBufferIndexOffset = pNode.mBaseBufferIndexOffset;
        if (pNode.mBaseBufferIndexOffsetIsRandom) {
            if (IsSBoxSlot(pNode.mBaseBufferSymbol.mSlot)) {
                aBaseBufferIndexOffset = Random::Get(S_SBOX);
            } else if (IsSaltSlot(pNode.mBaseBufferSymbol.mSlot)) {
                aBaseBufferIndexOffset = Random::Get(S_SALT);
            } else {
                const bool aBaseIsLoopIndex = IsLoopIndexLike(pNode.mBaseBufferIndexSymbol);
                aBaseBufferIndexOffset = aBaseIsLoopIndex ? Random::Get(S_BLOCK)
                                                          : Random::Get(aMaxSafeBlockOffset + 1);
            }
        }

        if ((aBaseBufferIndexOffset != 0) && !IsSBoxSlot(pNode.mBaseBufferSymbol.mSlot) && !IsSaltSlot(pNode.mBaseBufferSymbol.mSlot)) {
            const std::string aBaseKeyStem = KeyStemForSymbol(pNode.mBaseBufferSymbol) + "Key";
            int aBaseKeyCounter = 0;
            if (pKeyNameCounters != nullptr) {
                aBaseKeyCounter = (*pKeyNameCounters)[aBaseKeyStem]++;
            }
            const GSymbol aBaseKeySymbol = VarSymbol(aBaseKeyStem + SuffixForCounter(aBaseKeyCounter));
            aBaseExpr = GExpr::ReadBlockWrap(pNode.mBaseBufferSymbol,
                                             pNode.mBaseBufferIndexSymbol,
                                             aBaseKeySymbol,
                                             aBaseBufferIndexOffset);
        } else {
            GExpr aBufferIndexExpr = GExpr::Symbol(pNode.mBaseBufferIndexSymbol);
            if (aBaseBufferIndexOffset != 0) {
                aBufferIndexExpr = GExpr::Add(aBufferIndexExpr, GExpr::Const(aBaseBufferIndexOffset));
            }
            aBaseExpr = GExpr::Read(pNode.mBaseBufferSymbol, aBufferIndexExpr);
        }
        aBaseSymbol = pNode.mBaseBufferIndexSymbol;
    } else {
        if (aBaseSymbol.IsInvalid()) {
            SetError(pErrorString, "Composer buffer node did not have a valid base symbol.");
            return false;
        }
        if (!aBaseSymbol.IsVar()) {
            SetError(pErrorString, "Composer buffer node base symbol must be a variable.");
            return false;
        }
        aBaseExpr = GExpr::Symbol(aBaseSymbol);
    }

    const int aOffset = ResolveOffset(pNode, aBaseSymbol, aDomain, pErrorString);
    if (aOffset < 0) {
        if ((pErrorString == nullptr) || pErrorString->empty()) {
            SetError(pErrorString, "Composer resolved an invalid offset.");
        }
        return false;
    }

    if (pNode.mBaseFromBuffer && (aDomain == GLoopFragmentDomain::kBlock) && (aOffset != 0)) {
        SetError(pErrorString, "Composer does not support block wrap offset with buffer-based keys yet.");
        return false;
    }

    const bool aCanDirectBlockRead = !pNode.mBaseFromBuffer &&
                                     (aDomain == GLoopFragmentDomain::kBlock) &&
                                     (aOffset == 0) &&
                                     CanUseDirectBlockIndex(aBaseSymbol, mLoopIndex);
    const bool aCanInlineNonBlockRead = (aDomain != GLoopFragmentDomain::kBlock) &&
                                        (aOffset == 0);
    const bool aUseBlockWrapRead = (aDomain == GLoopFragmentDomain::kBlock) &&
                                   !pNode.mBaseFromBuffer &&
                                   !aCanDirectBlockRead;

    const bool aNeedKey = (aDomain == GLoopFragmentDomain::kBlock)
        ? aUseBlockWrapRead
        : !aCanInlineNonBlockRead;
    const bool aNeedByte = aShouldExpand;
    BufferTemp aTemp = BuildBufferTemp(pNode,
                                       aNeedKey,
                                       aNeedByte,
                                       pKeyNameCounters,
                                       pByteNameCounters);

    if (aNeedKey && (aDomain != GLoopFragmentDomain::kBlock)) {
        GExpr aKeyExpr = aBaseExpr;
        if (aOffset != 0) {
            aKeyExpr = GExpr::Add(aKeyExpr, GExpr::Const(aOffset));
        }

        if (!AddStatement(pStatementList,
                          GStatement::Assign(GTarget::Symbol(aTemp.mKeySymbol), aKeyExpr),
                          pErrorString)) {
            return false;
        }
    }

    GExpr aReadExpr;
    if (aDomain == GLoopFragmentDomain::kBlock) {
        if (aUseBlockWrapRead) {
            aReadExpr = GExpr::ReadBlockWrap(pNode.mSymbol, aBaseSymbol, aTemp.mKeySymbol, aOffset);
        } else {
            aReadExpr = GExpr::Read(pNode.mSymbol, aBaseExpr);
        }
    } else {
        if (aNeedKey) {
            aReadExpr = GExpr::Read(pNode.mSymbol, GExpr::Symbol(aTemp.mKeySymbol));
        } else {
            GExpr aIndexExpr = aBaseExpr;
            if (aOffset != 0) {
                aIndexExpr = GExpr::Add(aIndexExpr, GExpr::Const(aOffset));
            }
            aReadExpr = GExpr::Read(pNode.mSymbol, aIndexExpr);
        }
    }

    if (aNeedByte) {
        const GExpr aByteExpr = aShouldExpand
            ? (pNode.mHasDebugExpand
               ? BuildExpandedExpressionDebug(pNode, aReadExpr)
               : BuildExpandedExpression(aReadExpr, pNode.mAllowMultiply))
            : aReadExpr;

        if (!AddStatement(pStatementList,
                          GStatement::Assign(GTarget::Symbol(aTemp.mByteSymbol), aByteExpr),
                          pErrorString)) {
            return false;
        }
    }

    if (pNode.mType == NodeType::kTransform) {
        if (pTargetInitialized != nullptr) {
            *pTargetInitialized = true;
        }
        if (!aNeedByte) {
            return AddStatement(pStatementList,
                                GStatement::Assign(GTarget::Symbol(mTarget), aReadExpr),
                                pErrorString);
        }
        return AddStatement(pStatementList,
                            GStatement::Assign(GTarget::Symbol(mTarget),
                                               GExpr::Symbol(aTemp.mByteSymbol)),
                            pErrorString);
    }

    if (!aNeedByte) {
        return EmitTargetCombine(aReadExpr, pTargetInitialized, pStatementList, pErrorString);
    }

    return EmitTargetCombine(GExpr::Symbol(aTemp.mByteSymbol),
                             pTargetInitialized,
                             pStatementList,
                             pErrorString);
}

bool GLoopFragmentComposer::EmitVariableNode(const Node &pNode,
                                             bool *pTargetInitialized,
                                             std::unordered_map<std::string, int> *pVariableTempCounters,
                                             std::vector<GStatement> *pStatementList,
                                             std::string *pErrorString) {
    if (!pNode.mSymbol.IsVar()) {
        SetError(pErrorString, "Composer variable node had an invalid variable symbol.");
        return false;
    }

    GSymbol aOperandSymbol = pNode.mSymbol;
    if (pNode.mHasDebugExpand || ((pNode.mExpandProbability > 0U) && Random::Chance(pNode.mExpandProbability))) {
        aOperandSymbol = BuildVariableTemp(pNode.mSymbol, pVariableTempCounters);

        const GExpr aExpandedExpr = pNode.mHasDebugExpand
            ? BuildExpandedExpressionDebug(pNode, GExpr::Symbol(pNode.mSymbol))
            : BuildExpandedExpression(GExpr::Symbol(pNode.mSymbol), pNode.mAllowMultiply);

        if (!AddStatement(pStatementList,
                          GStatement::Assign(GTarget::Symbol(aOperandSymbol), aExpandedExpr),
                          pErrorString)) {
            return false;
        }
    }

    return EmitTargetCombine(GExpr::Symbol(aOperandSymbol),
                             pTargetInitialized,
                             pStatementList,
                             pErrorString);
}

GLoopFragmentDomain GLoopFragmentComposer::ResolveDomain(const Node &pNode) const {
    if (pNode.mDomain != GLoopFragmentDomain::kAuto) {
        return pNode.mDomain;
    }
    if (pNode.mSymbol.IsBuf()) {
        if (IsSBoxSlot(pNode.mSymbol.mSlot)) {
            return GLoopFragmentDomain::kSBox;
        }
        if (IsSaltSlot(pNode.mSymbol.mSlot)) {
            return GLoopFragmentDomain::kSalt;
        }
    }
    return GLoopFragmentDomain::kBlock;
}

int GLoopFragmentComposer::ResolveOffset(const Node &pNode,
                                         const GSymbol &pBaseSymbol,
                                         GLoopFragmentDomain pDomain,
                                         std::string *pErrorString) const {
    constexpr int kMaxByteValue = 255;
    const bool aBaseIsLoopIndex = IsLoopIndexLike(pBaseSymbol);
    const int aMaxSafeBlockOffset = std::max(0, S_BLOCK - (kMaxByteValue + 1));

    if (pNode.mOffsetIsDebugMax) {
        switch (pDomain) {
            case GLoopFragmentDomain::kSBox:
                return S_SBOX - 1;
            case GLoopFragmentDomain::kSalt:
                return S_SALT - 1;
            case GLoopFragmentDomain::kBlock:
            default:
                return aBaseIsLoopIndex ? (S_BLOCK - 1) : aMaxSafeBlockOffset;
        }
    }

    if (pNode.mOffsetIsRandom) {
        switch (pDomain) {
            case GLoopFragmentDomain::kSBox:
                return Random::Get(S_SBOX);

            case GLoopFragmentDomain::kSalt:
                return Random::Get(S_SALT);

            case GLoopFragmentDomain::kBlock:
            default:
                return aBaseIsLoopIndex ? Random::Get(S_BLOCK)
                                        : Random::Get(aMaxSafeBlockOffset + 1);
        }
    }

    if (pNode.mOffset < 0) {
        SetError(pErrorString, "Composer fixed offsets must be >= 0.");
        return -1;
    }

    switch (pDomain) {
        case GLoopFragmentDomain::kSBox:
            return PositiveMod(pNode.mOffset, S_SBOX);

        case GLoopFragmentDomain::kSalt:
            return PositiveMod(pNode.mOffset, S_SALT);

        case GLoopFragmentDomain::kBlock:
        default:
            if (aBaseIsLoopIndex) {
                return PositiveMod(pNode.mOffset, S_BLOCK);
            }
            if (pNode.mOffset > aMaxSafeBlockOffset) {
                SetError(pErrorString,
                         "Composer block offset overflowed non-loop base safety envelope (max " +
                         std::to_string(aMaxSafeBlockOffset) + ").");
                return -1;
            }
            return pNode.mOffset;
    }
}

GLoopFragmentComposer::BufferTemp GLoopFragmentComposer::BuildBufferTemp(
    const Node &pNode,
    bool pNeedKey,
    bool pNeedByte,
    std::unordered_map<std::string, int> *pKeyNameCounters,
    std::unordered_map<std::string, int> *pByteNameCounters) const {
    BufferTemp aTemp;

    const std::string aKeyStem = KeyStemForSymbol(pNode.mSymbol) + "Key";
    const std::string aByteStem = BufAliasName(pNode.mSymbol.mSlot) + "Byte";

    if (pNeedKey) {
        int aKeyCounter = 0;
        if (pKeyNameCounters != nullptr) {
            aKeyCounter = (*pKeyNameCounters)[aKeyStem]++;
        }
        aTemp.mKeySymbol = VarSymbol(aKeyStem + SuffixForCounter(aKeyCounter));
    }

    if (pNeedByte) {
        int aByteCounter = 0;
        if (pByteNameCounters != nullptr) {
            aByteCounter = (*pByteNameCounters)[aByteStem]++;
        }
        aTemp.mByteSymbol = VarSymbol(aByteStem + SuffixForCounter(aByteCounter));
    }

    return aTemp;
}

GSymbol GLoopFragmentComposer::BuildVariableTemp(
    const GSymbol &pVariable,
    std::unordered_map<std::string, int> *pVariableTempCounters) const {
    if (!pVariable.IsVar()) {
        return pVariable;
    }

    const std::string aStem = EndsWith(pVariable.mName, "Byte")
        ? pVariable.mName
        : (pVariable.mName + "Byte");

    int aCounter = 0;
    if (pVariableTempCounters != nullptr) {
        aCounter = (*pVariableTempCounters)[aStem]++;
    }
    return VarSymbol(aStem + SuffixForCounter(aCounter));
}

GExpr GLoopFragmentComposer::BuildExpandedExpression(const GExpr &pBaseExpr,
                                                     bool pAllowMultiply) const {
    std::vector<int> aOperations = {0, 1, 2, 3};
    if (pAllowMultiply) {
        aOperations.push_back(4);
    }

    const int aChoice = aOperations[static_cast<std::size_t>(Random::Get(static_cast<int>(aOperations.size())))];
    switch (aChoice) {
        case 0:
            return GExpr::Add(pBaseExpr, GExpr::Const(Random::Get(1, 31)));
        case 1:
            return GExpr::Xor(pBaseExpr, GExpr::Const(Random::Get(1, 255)));
        case 2:
            return GExpr::Sub(pBaseExpr, GExpr::Const(Random::Get(1, 17)));
        case 3:
            return GExpr::RotL8(pBaseExpr, GExpr::Const(Random::Get(1, 7)));
        case 4:
            return GExpr::Mul(pBaseExpr, GExpr::Const(Random::Get(2, 33)));
        default:
            return pBaseExpr;
    }
}

GExpr GLoopFragmentComposer::BuildExpandedExpressionDebug(const Node &pNode,
                                                          const GExpr &pBaseExpr) const {
    const int aRotateRaw = pNode.mDebugExpandConstantA;
    const int aRotateSafe = (aRotateRaw <= 0) ? 1 : (aRotateRaw & 7);
    const int aRotateAmount = (aRotateSafe == 0) ? 1 : aRotateSafe;
    const GExpr aConstA = GExpr::Const(pNode.mDebugExpandConstantA);
    const GExpr aConstB = GExpr::Const(pNode.mDebugExpandConstantB);
    const GExpr aRotateExpr = GExpr::Const(aRotateAmount);

    switch (pNode.mDebugExpandPattern) {
        case GTermPattern::kAdd:
            return GExpr::Add(pBaseExpr, aConstA);
        case GTermPattern::kSub:
            return GExpr::Sub(pBaseExpr, aConstA);
        case GTermPattern::kXor:
            return GExpr::Xor(pBaseExpr, aConstA);
        case GTermPattern::kMul:
            return GExpr::Mul(pBaseExpr, aConstA);
        case GTermPattern::kRotate:
            return GExpr::RotL8(pBaseExpr, aRotateExpr);
        case GTermPattern::kMulThenAdd:
            return GExpr::Add(GExpr::Mul(pBaseExpr, aConstA), aConstB);
        case GTermPattern::kMulThenSub:
            return GExpr::Sub(GExpr::Mul(pBaseExpr, aConstA), aConstB);
        case GTermPattern::kMulThenXor:
            return GExpr::Xor(GExpr::Mul(pBaseExpr, aConstA), aConstB);
        case GTermPattern::kRotateAdd:
            return GExpr::RotL8(GExpr::Add(pBaseExpr, aConstB), aRotateExpr);
        case GTermPattern::kRotateSub:
            return GExpr::RotL8(GExpr::Sub(pBaseExpr, aConstB), aRotateExpr);
        case GTermPattern::kRotateXor:
            return GExpr::RotL8(GExpr::Xor(pBaseExpr, aConstB), aRotateExpr);
        case GTermPattern::kRotateMul:
            return GExpr::RotL8(GExpr::Mul(pBaseExpr, aConstB), aRotateExpr);
        case GTermPattern::kPostRotateAdd:
            return GExpr::Add(GExpr::RotL8(pBaseExpr, aRotateExpr), aConstB);
        case GTermPattern::kPostRotateSub:
            return GExpr::Sub(GExpr::RotL8(pBaseExpr, aRotateExpr), aConstB);
        case GTermPattern::kPostRotateXor:
            return GExpr::Xor(GExpr::RotL8(pBaseExpr, aRotateExpr), aConstB);
        case GTermPattern::kPostRotateMul:
            return GExpr::Mul(GExpr::RotL8(pBaseExpr, aRotateExpr), aConstB);
        default:
            return pBaseExpr;
    }
}

bool GLoopFragmentComposer::ShouldDeferCombine() const {
    if (mInitialAssignType == GAssignType::kInvalid) {
        return false;
    }
    for (const Node &aNode : mNodes) {
        if (aNode.mType == NodeType::kMixBuffer || aNode.mType == NodeType::kMixVariable) {
            return true;
        }
    }
    return false;
}

GExpr GLoopFragmentComposer::BuildDeferredExpression() const {
    if (mDeferredCombineOperands.empty()) {
        return GExpr();
    }
    if (mDeferredCombineOperands.size() == 1U) {
        return mDeferredCombineOperands[0];
    }
    if ((mDeferredCombineOps.size() + 1U) != mDeferredCombineOperands.size()) {
        return GExpr();
    }

    GExpr aExpr = mDeferredCombineOperands[0];
    for (std::size_t aIndex = 1U; aIndex < mDeferredCombineOperands.size(); ++aIndex) {
        const GExpr &aOperandExpr = mDeferredCombineOperands[aIndex];
        const DeferredCombineOp aCombineOp = mDeferredCombineOps[aIndex - 1U];
        switch (aCombineOp) {
            case DeferredCombineOp::kAdd:
                aExpr = GExpr::Add(aExpr, aOperandExpr);
                break;
            case DeferredCombineOp::kXor:
                aExpr = GExpr::Xor(aExpr, aOperandExpr);
                break;
            default:
                return GExpr();
        }
    }
    return aExpr;
}

bool GLoopFragmentComposer::FlushDeferredCombine(std::vector<GStatement> *pStatementList,
                                                 std::string *pErrorString) {
    if (!mDeferCombine || mDeferredCombineOperands.empty()) {
        mDeferredCombineOps.clear();
        return true;
    }

    const GExpr aCombinedExpr = BuildDeferredExpression();
    mDeferredCombineOperands.clear();
    mDeferredCombineOps.clear();
    if (aCombinedExpr.IsInvalid()) {
        SetError(pErrorString, "Composer failed to build deferred combine expression.");
        return false;
    }

    GStatement aStatement;
    switch (mDeferredCombineAssignType) {
        case GAssignType::kAddAssign:
            aStatement = GStatement::AddAssign(GTarget::Symbol(mTarget), aCombinedExpr);
            break;
        case GAssignType::kXorAssign:
            aStatement = GStatement::XorAssign(GTarget::Symbol(mTarget), aCombinedExpr);
            break;
        case GAssignType::kSet:
        default:
            aStatement = GStatement::Assign(GTarget::Symbol(mTarget), aCombinedExpr);
            break;
    }
    mDeferredCombineAssignType = GAssignType::kInvalid;
    return AddStatement(pStatementList, aStatement, pErrorString);
}

bool GLoopFragmentComposer::ConsumeDebugAddXorIsAdd() const {
    if (!mDebugAddXorEnabled || mDebugAddXorPattern.empty()) {
        return true;
    }
    const std::size_t aIndex = std::min(mDebugAddXorCursor, mDebugAddXorPattern.size() - 1U);
    const bool aIsAdd = mDebugAddXorPattern[aIndex];
    if ((mDebugAddXorCursor + 1U) < mDebugAddXorPattern.size()) {
        mDebugAddXorCursor += 1U;
    }
    return aIsAdd;
}

bool GLoopFragmentComposer::BakeStatements(std::vector<GStatement> *pStatementList,
                                           std::string *pErrorString) {
    if (pStatementList == nullptr) {
        SetError(pErrorString, "Composer output statement list was null.");
        return false;
    }

    if (!mConfigError.empty()) {
        SetError(pErrorString, mConfigError);
        return false;
    }

    if (!mTarget.IsVar()) {
        SetError(pErrorString, "Composer target must be a valid variable symbol.");
        return false;
    }

    if (mNodes.empty()) {
        SetError(pErrorString, "Composer had no nodes to bake.");
        return false;
    }

    bool aTargetInitialized = false;
    std::unordered_map<std::string, int> aKeyNameCounters;
    std::unordered_map<std::string, int> aByteNameCounters;
    std::unordered_map<std::string, int> aVariableTempCounters;
    mDeferredCombineOperands.clear();
    mDeferredCombineOps.clear();
    mDeferCombine = ShouldDeferCombine();
    mDebugAddXorCursor = 0U;
    mDeferredCombineAssignType = GAssignType::kInvalid;

    for (const Node &aNode : mNodes) {
        if (mDeferCombine && (aNode.mType == NodeType::kTransform)) {
            if (!FlushDeferredCombine(pStatementList, pErrorString)) {
                return false;
            }
        }

        switch (aNode.mType) {
            case NodeType::kMixBuffer:
            case NodeType::kTransform:
                if (!EmitBufferNode(aNode,
                                    &aTargetInitialized,
                                    &aKeyNameCounters,
                                    &aByteNameCounters,
                                    pStatementList,
                                    pErrorString)) {
                    return false;
                }
                break;

            case NodeType::kMixVariable:
                if (!EmitVariableNode(aNode,
                                      &aTargetInitialized,
                                      &aVariableTempCounters,
                                      pStatementList,
                                      pErrorString)) {
                    return false;
                }
                break;

            default:
                SetError(pErrorString, "Composer encountered an invalid node type while baking.");
                return false;
        }
    }

    if (!FlushDeferredCombine(pStatementList, pErrorString)) {
        return false;
    }

    if (!aTargetInitialized) {
        SetError(pErrorString, "Composer could not initialize target during bake.");
        return false;
    }

    return true;
}
