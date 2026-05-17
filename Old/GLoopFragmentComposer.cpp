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

void SetError(std::string *pErrorMessage,
              const std::string &pMessage) {
    if (pErrorMessage != nullptr) {
        *pErrorMessage = pMessage;
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

GLoopFragmentComposerInputBuffer::GLoopFragmentComposerInputBuffer(GSymbol pBuffer) {
    InitializeDetached(pBuffer, GLoopFragmentComposerCombineOp::kAdd);
}

GLoopFragmentComposerInputBuffer::GLoopFragmentComposerInputBuffer(
    GSymbol pBuffer,
    GLoopFragmentComposerCombineOp pCombineOp) {
    InitializeDetached(pBuffer, pCombineOp);
}

GLoopFragmentComposerInputBuffer::GLoopFragmentComposerInputBuffer(GLoopFragmentComposer *pComposer,
                                                                   std::size_t pNodeIndex) {
    mComposer = pComposer;
    mNodeIndex = pNodeIndex;
    if ((mComposer != nullptr) && (mNodeIndex < mComposer->mNodes.size())) {
        const GLoopFragmentComposer::Node &aNode = mComposer->mNodes[mNodeIndex];
        if (aNode.mType == GLoopFragmentComposer::NodeType::kMixBuffer) {
            mSymbol = aNode.mSymbol;
            mCombineOp = aNode.mCombineOp;
            mBaseSymbol = aNode.mBaseSymbol;
            mBaseFromBuffer = aNode.mBaseFromBuffer;
            mBaseBufferSymbol = aNode.mBaseBufferSymbol;
            mBaseBufferIndexSymbol = aNode.mBaseBufferIndexSymbol;
            mBaseBufferIndexOffsetIsRandom = aNode.mBaseBufferIndexOffsetIsRandom;
            mBaseBufferIndexOffset = aNode.mBaseBufferIndexOffset;
            mDomain = aNode.mDomain;
            mOffsetIsRandom = aNode.mOffsetIsRandom;
            mOffsetIsDebugMax = aNode.mOffsetIsDebugMax;
            mOffsetIsInverted = aNode.mOffsetIsInverted;
            mOffset = aNode.mOffset;
            mExpandProbability = aNode.mExpandProbability;
            mAllowMultiply = aNode.mAllowMultiply;
            mHasDebugExpand = aNode.mHasDebugExpand;
            mDebugExpandPattern = aNode.mDebugExpandPattern;
            mDebugExpandConstantA = aNode.mDebugExpandConstantA;
            mDebugExpandConstantB = aNode.mDebugExpandConstantB;
        }
    }
}

void GLoopFragmentComposerInputBuffer::InitializeDetached(GSymbol pBuffer,
                                                          GLoopFragmentComposerCombineOp pCombineOp) {
    mComposer = nullptr;
    mNodeIndex = 0U;
    mSymbol = pBuffer;
    mCombineOp = pCombineOp;
    mBaseSymbol.Invalidate();
    mBaseFromBuffer = false;
    mBaseBufferSymbol.Invalidate();
    mBaseBufferIndexSymbol.Invalidate();
    mBaseBufferIndexOffsetIsRandom = false;
    mBaseBufferIndexOffset = 0;
    mDomain = GLoopFragmentDomain::kAuto;
    mOffsetIsRandom = false;
    mOffsetIsDebugMax = false;
    mOffsetIsInverted = false;
    mOffset = 0;
    mExpandProbability = 0U;
    mAllowMultiply = true;
    mHasDebugExpand = false;
    mDebugExpandPattern = GTermPattern::kAdd;
    mDebugExpandConstantA = 0;
    mDebugExpandConstantB = 0;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Base(GSymbol pBaseIndex) {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeBase(mNodeIndex, pBaseIndex);
        }
        mBaseSymbol = pBaseIndex;
        mBaseFromBuffer = false;
        mBaseBufferSymbol.Invalidate();
        mBaseBufferIndexSymbol.Invalidate();
        mBaseBufferIndexOffsetIsRandom = false;
        mBaseBufferIndexOffset = 0;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Key() {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeLoopKey(mNodeIndex);
        }
        mBaseSymbol.Invalidate();
        mBaseFromBuffer = false;
        mBaseBufferSymbol.Invalidate();
        mBaseBufferIndexSymbol.Invalidate();
        mBaseBufferIndexOffsetIsRandom = false;
        mBaseBufferIndexOffset = 0;
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
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeBaseFromBuffer(mNodeIndex, pBuffer, pBufferIndex, pBufferOffset);
        }
        mBaseFromBuffer = true;
        mBaseBufferSymbol = pBuffer;
        mBaseBufferIndexSymbol = pBufferIndex;
        mBaseBufferIndexOffsetIsRandom = false;
        mBaseBufferIndexOffset = pBufferOffset;
        mBaseSymbol = pBufferIndex;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::KeyWithBufferRandomOffset(GSymbol pBuffer,
                                                                                               GSymbol pBufferIndex) {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeBaseFromBufferRandomOffset(mNodeIndex, pBuffer, pBufferIndex);
        }
        mBaseFromBuffer = true;
        mBaseBufferSymbol = pBuffer;
        mBaseBufferIndexSymbol = pBufferIndex;
        mBaseBufferIndexOffsetIsRandom = true;
        mBaseBufferIndexOffset = 0;
        mBaseSymbol = pBufferIndex;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Domain(GLoopFragmentDomain pDomain) {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeDomain(mNodeIndex, pDomain);
        }
        mDomain = pDomain;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Offset() {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeRandomOffset(mNodeIndex);
        }
        mOffsetIsRandom = true;
        mOffsetIsDebugMax = false;
        mOffsetIsInverted = false;
        mOffset = 0;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Offset(int pOffset) {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeFixedOffset(mNodeIndex, pOffset);
        }
        mOffsetIsRandom = false;
        mOffsetIsDebugMax = false;
        mOffsetIsInverted = false;
        mOffset = pOffset;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::OffsetIverted() {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeInvertedRandomOffset(mNodeIndex);
        }
        mOffsetIsRandom = true;
        mOffsetIsDebugMax = false;
        mOffsetIsInverted = true;
        mOffset = 0;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::OffsetIverted(int pOffset) {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeInvertedOffset(mNodeIndex, pOffset);
        }
        mOffsetIsRandom = false;
        mOffsetIsDebugMax = false;
        mOffsetIsInverted = true;
        mOffset = pOffset;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::OffsetIvertedRandom() {
    if (Random::Bool()) {
        return OffsetIverted();
    }
    return Offset();
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::OffsetDebugMax() {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeOffsetDebugMax(mNodeIndex);
        }
        mOffsetIsRandom = false;
        mOffsetIsDebugMax = true;
        mOffsetIsInverted = false;
        mOffset = 0;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Expand(std::uint8_t pExpandProbability,
                                                                           bool pAllowMultiply) {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeExpand(mNodeIndex, pExpandProbability, pAllowMultiply);
        }
        mExpandProbability = pExpandProbability;
        mAllowMultiply = pAllowMultiply;
        mHasDebugExpand = false;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::ExpandDebug(GTermPattern pPattern,
                                                                                 int pConstantA,
                                                                                 int pConstantB) {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeExpandDebug(mNodeIndex, pPattern, pConstantA, pConstantB);
        }
        mHasDebugExpand = true;
        mDebugExpandPattern = pPattern;
        mDebugExpandConstantA = pConstantA;
        mDebugExpandConstantB = pConstantB;
        mExpandProbability = 100U;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::Combine(GLoopFragmentComposerCombineOp pCombineOp) {
    mCombineOp = pCombineOp;
    if ((mComposer != nullptr) && (mNodeIndex < mComposer->mNodes.size())) {
        mComposer->mNodes[mNodeIndex].mCombineOp = pCombineOp;
    }
    return *this;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::MixInt64Add() {
    return Combine(GLoopFragmentComposerCombineOp::kAdd);
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::MixInt64Xor() {
    return Combine(GLoopFragmentComposerCombineOp::kXor);
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::MixInt64Mul() {
    return Combine(GLoopFragmentComposerCombineOp::kMul);
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposerInputBuffer::MixInt64() {
    if (Random::Bool()) {
        return MixInt64Add();
    }
    return MixInt64Xor();
}

GLoopFragmentComposerCombineOp GLoopFragmentComposerInputBuffer::GetCombine() const {
    return mCombineOp;
}

GLoopFragmentComposerInput GLoopFragmentComposerInputBuffer::ToInput() const {
    return GLoopFragmentComposerInput(*this);
}

bool GLoopFragmentComposerInputBuffer::IsValid() const {
    if (mComposer != nullptr) {
        return (mNodeIndex < mComposer->mNodes.size()) &&
               (mComposer->mNodes[mNodeIndex].mType == GLoopFragmentComposer::NodeType::kMixBuffer);
    }
    return mSymbol.IsBuf();
}

GLoopFragmentComposerInputVariable::GLoopFragmentComposerInputVariable() = default;

GLoopFragmentComposerInputVariable::GLoopFragmentComposerInputVariable(GSymbol pVariable) {
    InitializeDetached(pVariable, GLoopFragmentComposerCombineOp::kAdd);
}

GLoopFragmentComposerInputVariable::GLoopFragmentComposerInputVariable(
    GSymbol pVariable,
    GLoopFragmentComposerCombineOp pCombineOp) {
    InitializeDetached(pVariable, pCombineOp);
}

GLoopFragmentComposerInputVariable::GLoopFragmentComposerInputVariable(GLoopFragmentComposer *pComposer,
                                                                       std::size_t pNodeIndex) {
    mComposer = pComposer;
    mNodeIndex = pNodeIndex;
    if ((mComposer != nullptr) && (mNodeIndex < mComposer->mNodes.size())) {
        const GLoopFragmentComposer::Node &aNode = mComposer->mNodes[mNodeIndex];
        if (aNode.mType == GLoopFragmentComposer::NodeType::kMixVariable) {
            mSymbol = aNode.mSymbol;
            mCombineOp = aNode.mCombineOp;
            mExpandProbability = aNode.mExpandProbability;
            mAllowMultiply = aNode.mAllowMultiply;
            mHasDebugExpand = aNode.mHasDebugExpand;
            mDebugExpandPattern = aNode.mDebugExpandPattern;
            mDebugExpandConstantA = aNode.mDebugExpandConstantA;
            mDebugExpandConstantB = aNode.mDebugExpandConstantB;
        }
    }
}

void GLoopFragmentComposerInputVariable::InitializeDetached(GSymbol pVariable,
                                                            GLoopFragmentComposerCombineOp pCombineOp) {
    mComposer = nullptr;
    mNodeIndex = 0U;
    mSymbol = pVariable;
    mCombineOp = pCombineOp;
    mExpandProbability = 0U;
    mAllowMultiply = true;
    mHasDebugExpand = false;
    mDebugExpandPattern = GTermPattern::kAdd;
    mDebugExpandConstantA = 0;
    mDebugExpandConstantB = 0;
}

GLoopFragmentComposerInputVariable &GLoopFragmentComposerInputVariable::Expand(std::uint8_t pExpandProbability,
                                                                               bool pAllowMultiply) {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeExpand(mNodeIndex, pExpandProbability, pAllowMultiply);
        }
        mExpandProbability = pExpandProbability;
        mAllowMultiply = pAllowMultiply;
        mHasDebugExpand = false;
    }
    return *this;
}

GLoopFragmentComposerInputVariable &GLoopFragmentComposerInputVariable::ExpandDebug(GTermPattern pPattern,
                                                                                     int pConstantA,
                                                                                     int pConstantB) {
    if (IsValid()) {
        if (mComposer != nullptr) {
            mComposer->ConfigureNodeExpandDebug(mNodeIndex, pPattern, pConstantA, pConstantB);
        }
        mHasDebugExpand = true;
        mDebugExpandPattern = pPattern;
        mDebugExpandConstantA = pConstantA;
        mDebugExpandConstantB = pConstantB;
        mExpandProbability = 100U;
    }
    return *this;
}

GLoopFragmentComposerInputVariable &GLoopFragmentComposerInputVariable::Combine(GLoopFragmentComposerCombineOp pCombineOp) {
    mCombineOp = pCombineOp;
    if ((mComposer != nullptr) && (mNodeIndex < mComposer->mNodes.size())) {
        mComposer->mNodes[mNodeIndex].mCombineOp = pCombineOp;
    }
    return *this;
}

GLoopFragmentComposerInputVariable &GLoopFragmentComposerInputVariable::MixInt64Add() {
    return Combine(GLoopFragmentComposerCombineOp::kAdd);
}

GLoopFragmentComposerInputVariable &GLoopFragmentComposerInputVariable::MixInt64Xor() {
    return Combine(GLoopFragmentComposerCombineOp::kXor);
}

GLoopFragmentComposerInputVariable &GLoopFragmentComposerInputVariable::MixInt64Mul() {
    return Combine(GLoopFragmentComposerCombineOp::kMul);
}

GLoopFragmentComposerInputVariable &GLoopFragmentComposerInputVariable::MixInt64() {
    if (Random::Bool()) {
        return MixInt64Add();
    }
    return MixInt64Xor();
}

GLoopFragmentComposerCombineOp GLoopFragmentComposerInputVariable::GetCombine() const {
    return mCombineOp;
}

GLoopFragmentComposerInput GLoopFragmentComposerInputVariable::ToInput() const {
    return GLoopFragmentComposerInput(*this);
}

bool GLoopFragmentComposerInputVariable::IsValid() const {
    if (mComposer != nullptr) {
        return (mNodeIndex < mComposer->mNodes.size()) &&
               (mComposer->mNodes[mNodeIndex].mType == GLoopFragmentComposer::NodeType::kMixVariable);
    }
    return mSymbol.IsVar();
}

GLoopFragmentComposerInput::GLoopFragmentComposerInput(const GLoopFragmentComposerInputBuffer &pInputBuffer) {
    mType = GLoopFragmentComposerInputType::kBuffer;
    mInputBuffer = pInputBuffer;
}

GLoopFragmentComposerInput::GLoopFragmentComposerInput(const GLoopFragmentComposerInputVariable &pInputVariable) {
    mType = GLoopFragmentComposerInputType::kVariable;
    mInputVariable = pInputVariable;
}

bool GLoopFragmentComposerInput::IsValid() const {
    if (mType == GLoopFragmentComposerInputType::kBuffer) {
        return mInputBuffer.IsValid();
    }
    if (mType == GLoopFragmentComposerInputType::kVariable) {
        return mInputVariable.IsValid();
    }
    return false;
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
    mDeferredCombineMode = TargetCombineMode::kInvalid;
    mConfigError.clear();
    mShufflePending = false;
    mLastBufferInputHandle = GLoopFragmentComposerInputBuffer();
}

void GLoopFragmentComposer::SetTarget(GSymbol pTarget) {
    mTarget = pTarget;
}

GSymbol GLoopFragmentComposer::GetTarget() const {
    return mTarget;
}

void GLoopFragmentComposer::ResetSetEqual(GSymbol pTarget) {
    Clear();
    SetTarget(pTarget);
    mInitialCombineMode = TargetCombineMode::kSet;
}

void GLoopFragmentComposer::ResetAddEqual(GSymbol pTarget) {
    Clear();
    SetTarget(pTarget);
    mInitialCombineMode = TargetCombineMode::kAdd;
}

void GLoopFragmentComposer::ResetXorEqual(GSymbol pTarget) {
    Clear();
    SetTarget(pTarget);
    mInitialCombineMode = TargetCombineMode::kXor;
}

void GLoopFragmentComposer::SetLoopIndex(GSymbol pLoopIndex) {
    mLoopIndex = pLoopIndex;
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::MixBuffer(GSymbol pBuffer) {
    return MixBufferAdd(pBuffer);
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::MixBufferAdd(GSymbol pBuffer) {
    Node aNode;
    aNode.mType = NodeType::kMixBuffer;
    aNode.mSymbol = pBuffer;
    aNode.mCombineOp = GLoopFragmentComposerCombineOp::kAdd;
    aNode.mBaseSymbol.Invalidate();
    mNodes.push_back(aNode);
    if (!pBuffer.IsBuf()) {
        SetConfigError("MixBuffer expected a buffer symbol.");
    }
    return GLoopFragmentComposerInputBuffer(this, mNodes.size() - 1U);
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::MixBufferMul(GSymbol pBuffer) {
    GLoopFragmentComposerInputBuffer aInput = MixBufferAdd(pBuffer);
    return aInput.Combine(GLoopFragmentComposerCombineOp::kMul);
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::MixBufferXor(GSymbol pBuffer) {
    GLoopFragmentComposerInputBuffer aInput = MixBufferAdd(pBuffer);
    return aInput.Combine(GLoopFragmentComposerCombineOp::kXor);
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::MixInt64Add(GSymbol pBuffer) {
    return MixBufferAdd(pBuffer);
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::MixInt64Xor(GSymbol pBuffer) {
    return MixBufferXor(pBuffer);
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::MixInt64Mul(GSymbol pBuffer) {
    return MixBufferMul(pBuffer);
}

GLoopFragmentComposerInputBuffer GLoopFragmentComposer::MixInt64(GSymbol pBuffer) {
    if (Random::Bool()) {
        return MixInt64Add(pBuffer);
    }
    return MixInt64Xor(pBuffer);
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposer::MixInt64Add() {
    if (mNodes.empty() || (mNodes.back().mType != NodeType::kMixBuffer)) {
        SetConfigError("MixInt64Add requires a prior MixBuffer* node.");
        mLastBufferInputHandle = GLoopFragmentComposerInputBuffer();
        return mLastBufferInputHandle;
    }
    mLastBufferInputHandle = GLoopFragmentComposerInputBuffer(this, mNodes.size() - 1U);
    mLastBufferInputHandle.MixInt64Add();
    return mLastBufferInputHandle;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposer::MixInt64Xor() {
    if (mNodes.empty() || (mNodes.back().mType != NodeType::kMixBuffer)) {
        SetConfigError("MixInt64Xor requires a prior MixBuffer* node.");
        mLastBufferInputHandle = GLoopFragmentComposerInputBuffer();
        return mLastBufferInputHandle;
    }
    mLastBufferInputHandle = GLoopFragmentComposerInputBuffer(this, mNodes.size() - 1U);
    mLastBufferInputHandle.MixInt64Xor();
    return mLastBufferInputHandle;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposer::MixInt64Mul() {
    if (mNodes.empty() || (mNodes.back().mType != NodeType::kMixBuffer)) {
        SetConfigError("MixInt64Mul requires a prior MixBuffer* node.");
        mLastBufferInputHandle = GLoopFragmentComposerInputBuffer();
        return mLastBufferInputHandle;
    }
    mLastBufferInputHandle = GLoopFragmentComposerInputBuffer(this, mNodes.size() - 1U);
    mLastBufferInputHandle.MixInt64Mul();
    return mLastBufferInputHandle;
}

GLoopFragmentComposerInputBuffer &GLoopFragmentComposer::MixInt64() {
    if (Random::Bool()) {
        return MixInt64Add();
    }
    return MixInt64Xor();
}

GLoopFragmentComposerInputVariable GLoopFragmentComposer::MixVariable(GSymbol pVariable) {
    return MixVariableAdd(pVariable);
}

GLoopFragmentComposerInputVariable GLoopFragmentComposer::MixVariableAdd(GSymbol pVariable) {
    Node aNode;
    aNode.mType = NodeType::kMixVariable;
    aNode.mSymbol = pVariable;
    aNode.mCombineOp = GLoopFragmentComposerCombineOp::kAdd;
    mNodes.push_back(aNode);
    if (!pVariable.IsVar()) {
        SetConfigError("MixVariable expected a variable symbol.");
    }
    return GLoopFragmentComposerInputVariable(this, mNodes.size() - 1U);
}

GLoopFragmentComposerInputVariable GLoopFragmentComposer::MixVariableMul(GSymbol pVariable) {
    GLoopFragmentComposerInputVariable aInput = MixVariableAdd(pVariable);
    return aInput.Combine(GLoopFragmentComposerCombineOp::kMul);
}

GLoopFragmentComposerInputVariable GLoopFragmentComposer::MixVariableXor(GSymbol pVariable) {
    GLoopFragmentComposerInputVariable aInput = MixVariableAdd(pVariable);
    return aInput.Combine(GLoopFragmentComposerCombineOp::kXor);
}

bool GLoopFragmentComposer::FillNodeFromInputBuffer(const GLoopFragmentComposerInputBuffer &pInputBuffer,
                                                    Node *pNode,
                                                    std::string *pErrorMessage) const {
    if (pNode == nullptr) {
        SetError(pErrorMessage, "Composer input buffer destination node was null.");
        return false;
    }

    if (!pInputBuffer.IsValid()) {
        SetError(pErrorMessage, "Composer input buffer was invalid.");
        return false;
    }

    pNode->mType = NodeType::kMixBuffer;
    pNode->mSymbol = pInputBuffer.mSymbol;
    pNode->mCombineOp = pInputBuffer.mCombineOp;
    pNode->mBaseSymbol = pInputBuffer.mBaseSymbol;
    pNode->mBaseFromBuffer = pInputBuffer.mBaseFromBuffer;
    pNode->mBaseBufferSymbol = pInputBuffer.mBaseBufferSymbol;
    pNode->mBaseBufferIndexSymbol = pInputBuffer.mBaseBufferIndexSymbol;
    pNode->mBaseBufferIndexOffsetIsRandom = pInputBuffer.mBaseBufferIndexOffsetIsRandom;
    pNode->mBaseBufferIndexOffset = pInputBuffer.mBaseBufferIndexOffset;
    pNode->mDomain = pInputBuffer.mDomain;
    pNode->mOffsetIsRandom = pInputBuffer.mOffsetIsRandom;
    pNode->mOffsetIsDebugMax = pInputBuffer.mOffsetIsDebugMax;
    pNode->mOffsetIsInverted = pInputBuffer.mOffsetIsInverted;
    pNode->mOffset = pInputBuffer.mOffset;
    pNode->mExpandProbability = pInputBuffer.mExpandProbability;
    pNode->mAllowMultiply = pInputBuffer.mAllowMultiply;
    pNode->mHasDebugExpand = pInputBuffer.mHasDebugExpand;
    pNode->mDebugExpandPattern = pInputBuffer.mDebugExpandPattern;
    pNode->mDebugExpandConstantA = pInputBuffer.mDebugExpandConstantA;
    pNode->mDebugExpandConstantB = pInputBuffer.mDebugExpandConstantB;
    return true;
}

bool GLoopFragmentComposer::FillNodeFromInputVariable(const GLoopFragmentComposerInputVariable &pInputVariable,
                                                      Node *pNode,
                                                      std::string *pErrorMessage) const {
    if (pNode == nullptr) {
        SetError(pErrorMessage, "Composer input variable destination node was null.");
        return false;
    }

    if (!pInputVariable.IsValid()) {
        SetError(pErrorMessage, "Composer input variable was invalid.");
        return false;
    }

    pNode->mType = NodeType::kMixVariable;
    pNode->mSymbol = pInputVariable.mSymbol;
    pNode->mCombineOp = pInputVariable.mCombineOp;
    pNode->mExpandProbability = pInputVariable.mExpandProbability;
    pNode->mAllowMultiply = pInputVariable.mAllowMultiply;
    pNode->mHasDebugExpand = pInputVariable.mHasDebugExpand;
    pNode->mDebugExpandPattern = pInputVariable.mDebugExpandPattern;
    pNode->mDebugExpandConstantA = pInputVariable.mDebugExpandConstantA;
    pNode->mDebugExpandConstantB = pInputVariable.mDebugExpandConstantB;
    return true;
}

bool GLoopFragmentComposer::AddInput(const GLoopFragmentComposerInputBuffer &pInputBuffer) {
    if ((pInputBuffer.mComposer == this) && (pInputBuffer.mNodeIndex < mNodes.size())) {
        return true;
    }

    Node aNode;
    std::string aError;
    if (!FillNodeFromInputBuffer(pInputBuffer, &aNode, &aError)) {
        SetConfigError(aError);
        return false;
    }
    if (aNode.mBaseSymbol.IsInvalid() && !aNode.mBaseFromBuffer) {
        aNode.mBaseSymbol = mLoopIndex;
    }
    mNodes.push_back(aNode);
    return true;
}

bool GLoopFragmentComposer::AddInput(const GLoopFragmentComposerInputVariable &pInputVariable) {
    if ((pInputVariable.mComposer == this) && (pInputVariable.mNodeIndex < mNodes.size())) {
        return true;
    }

    Node aNode;
    std::string aError;
    if (!FillNodeFromInputVariable(pInputVariable, &aNode, &aError)) {
        SetConfigError(aError);
        return false;
    }
    mNodes.push_back(aNode);
    return true;
}

bool GLoopFragmentComposer::AddInput(const GLoopFragmentComposerInput &pInput) {
    switch (pInput.mType) {
        case GLoopFragmentComposerInputType::kBuffer:
            return AddInput(pInput.mInputBuffer);
        case GLoopFragmentComposerInputType::kVariable:
            return AddInput(pInput.mInputVariable);
        case GLoopFragmentComposerInputType::kInv:
        default:
            SetConfigError("Composer input wrapper was invalid.");
            return false;
    }
}

bool GLoopFragmentComposer::AddInputs(const std::vector<GLoopFragmentComposerInput> &pInputs) {
    bool aResult = true;
    for (const GLoopFragmentComposerInput &aInput : pInputs) {
        if (!AddInput(aInput)) {
            aResult = false;
            break;
        }
    }
    return aResult;
}

GLoopFragmentComposer &GLoopFragmentComposer::Shuffle() {
    mShufflePending = true;
    return *this;
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
    mNodes[pNodeIndex].mOffsetIsInverted = false;
    mNodes[pNodeIndex].mOffset = 0;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeInvertedRandomOffset(std::size_t pNodeIndex) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting offset.");
        return false;
    }
    mNodes[pNodeIndex].mOffsetIsRandom = true;
    mNodes[pNodeIndex].mOffsetIsDebugMax = false;
    mNodes[pNodeIndex].mOffsetIsInverted = true;
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
    mNodes[pNodeIndex].mOffsetIsInverted = false;
    mNodes[pNodeIndex].mOffset = pOffset;
    return true;
}

bool GLoopFragmentComposer::ConfigureNodeInvertedOffset(std::size_t pNodeIndex,
                                                        int pOffset) {
    if (pNodeIndex >= mNodes.size()) {
        SetConfigError("Composer node index was out of range while setting offset.");
        return false;
    }
    mNodes[pNodeIndex].mOffsetIsRandom = false;
    mNodes[pNodeIndex].mOffsetIsDebugMax = false;
    mNodes[pNodeIndex].mOffsetIsInverted = true;
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
    mNodes[pNodeIndex].mOffsetIsInverted = false;
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

void GLoopFragmentComposer::SetConfigError(const std::string &pErrorMessage) {
    if (mConfigError.empty()) {
        mConfigError = pErrorMessage;
    }
}

bool GLoopFragmentComposer::AddStatement(std::vector<GStatement> *pStatements,
                                         const GStatement &pStatement,
                                         std::string *pErrorMessage) const {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "Composer output statement list was null.");
        return false;
    }
    if (pStatement.IsInvalid()) {
        SetError(pErrorMessage, "Composer attempted to emit an invalid statement.");
        return false;
    }
    pStatements->push_back(pStatement);
    return true;
}

bool GLoopFragmentComposer::EmitTargetCombine(const GExpr &pOperandExpr,
                                              GLoopFragmentComposerCombineOp pCombineOp,
                                              bool *pTargetInitialized,
                                              std::vector<GStatement> *pStatements,
                                              std::string *pErrorMessage) {
    if ((pTargetInitialized == nullptr) || pOperandExpr.IsInvalid()) {
        SetError(pErrorMessage, "Composer could not combine into target due to invalid state.");
        return false;
    }

    if (mDeferCombine) {
        if (mDeferredCombineOperands.empty()) {
            if (!(*pTargetInitialized)) {
                mDeferredCombineMode = mInitialCombineMode;
            } else {
                mDeferredCombineMode = TargetCombineMode::kSet;
                mDeferredCombineOperands.push_back(GExpr::Symbol(mTarget));
            }
        }

        if (!mDeferredCombineOperands.empty()) {
            DeferredCombineOp aCombineOp = DeferredCombineOp::kAdd;
            switch (mDeferredNextCombineOp) {
                case GLoopFragmentComposerCombineOp::kAdd: aCombineOp = DeferredCombineOp::kAdd; break;
                case GLoopFragmentComposerCombineOp::kMul: aCombineOp = DeferredCombineOp::kMul; break;
                case GLoopFragmentComposerCombineOp::kXor: aCombineOp = DeferredCombineOp::kXor; break;
                case GLoopFragmentComposerCombineOp::kSub: aCombineOp = DeferredCombineOp::kSub; break;
            }

            if (aCombineOp == DeferredCombineOp::kNone) {
                SetError(pErrorMessage, "Composer could not resolve deferred combine operation.");
                return false;
            }
            mDeferredCombineOps.push_back(aCombineOp);
        }
        mDeferredCombineOperands.push_back(pOperandExpr);
        mDeferredNextCombineOp = pCombineOp;
        *pTargetInitialized = true;
        return true;
    }

    if (!(*pTargetInitialized)) {
        *pTargetInitialized = true;
        GStatement aStatement;
        switch (mInitialCombineMode) {
            case TargetCombineMode::kAdd:
                aStatement = GStatement::Assign(GTarget::Symbol(mTarget),
                                                GExpr::Add(GExpr::Symbol(mTarget), pOperandExpr));
                break;
            case TargetCombineMode::kXor:
                aStatement = GStatement::Assign(GTarget::Symbol(mTarget),
                                                GExpr::Xor(GExpr::Symbol(mTarget), pOperandExpr));
                break;
            case TargetCombineMode::kSet:
            default:
                aStatement = GStatement::Assign(GTarget::Symbol(mTarget),
                                                pOperandExpr);
                break;
        }
        mDeferredNextCombineOp = pCombineOp;
        return AddStatement(pStatements, aStatement, pErrorMessage);
    }

    if (mDeferredNextCombineOp == GLoopFragmentComposerCombineOp::kAdd) {
        mDeferredNextCombineOp = pCombineOp;
        return AddStatement(pStatements,
                            GStatement::Assign(GTarget::Symbol(mTarget),
                                               GExpr::Add(GExpr::Symbol(mTarget), pOperandExpr)),
                            pErrorMessage);
    }
    if (mDeferredNextCombineOp == GLoopFragmentComposerCombineOp::kXor) {
        mDeferredNextCombineOp = pCombineOp;
        return AddStatement(pStatements,
                            GStatement::Assign(GTarget::Symbol(mTarget),
                                               GExpr::Xor(GExpr::Symbol(mTarget), pOperandExpr)),
                            pErrorMessage);
    }
    if (mDeferredNextCombineOp == GLoopFragmentComposerCombineOp::kMul) {
        mDeferredNextCombineOp = pCombineOp;
        return AddStatement(pStatements,
                            GStatement::Assign(GTarget::Symbol(mTarget),
                                               GExpr::Mul(GExpr::Symbol(mTarget), pOperandExpr)),
                            pErrorMessage);
    }
    if (mDeferredNextCombineOp == GLoopFragmentComposerCombineOp::kSub) {
        mDeferredNextCombineOp = pCombineOp;
        return AddStatement(pStatements,
                            GStatement::Assign(GTarget::Symbol(mTarget),
                                               GExpr::Sub(GExpr::Symbol(mTarget), pOperandExpr)),
                            pErrorMessage);
    }

    SetError(pErrorMessage, "Composer combine op was invalid.");
    return false;
}

bool GLoopFragmentComposer::EmitBufferNode(const Node &pNode,
                                           bool *pTargetInitialized,
                                           std::unordered_map<std::string, int> *pKeyNameCounters,
                                           std::unordered_map<std::string, int> *pByteNameCounters,
                                           std::vector<GStatement> *pStatements,
                                           std::string *pErrorMessage) {
    if (!pNode.mSymbol.IsBuf()) {
        SetError(pErrorMessage, "Composer buffer node had an invalid buffer symbol.");
        return false;
    }
    if (pNode.mType != NodeType::kMixBuffer) {
        SetError(pErrorMessage, "Composer buffer node had an invalid type.");
        return false;
    }

    bool aShouldExpand = false;
    if (pNode.mHasDebugExpand) {
        aShouldExpand = true;
    } else if ((pNode.mExpandProbability > 0U) && Random::Chance(pNode.mExpandProbability)) {
        aShouldExpand = true;
    }

    const GLoopFragmentDomain aDomain = ResolveDomain(pNode);
    GSymbol aBaseSymbol = pNode.mBaseSymbol;
    if (!pNode.mBaseFromBuffer && aBaseSymbol.IsInvalid()) {
        if (mLoopIndex.IsInvalid()) {
            SetError(pErrorMessage, "Composer buffer node required loop index, but no loop symbol or explicit key was provided.");
            return false;
        }
        aBaseSymbol = mLoopIndex;
    }

    GExpr aBaseExpr;
    if (pNode.mBaseFromBuffer) {
        if (!pNode.mBaseBufferSymbol.IsBuf() || !pNode.mBaseBufferIndexSymbol.IsVar()) {
            SetError(pErrorMessage, "Composer buffer node had an invalid buffer-based key source.");
            return false;
        }
        if (pNode.mBaseBufferIndexOffset < 0) {
            SetError(pErrorMessage, "Composer buffer-based key offset must be >= 0.");
            return false;
        }

        int aBaseBufferIndexOffset = pNode.mBaseBufferIndexOffset;
        if (pNode.mBaseBufferIndexOffsetIsRandom) {
            if (TwistWorkSpace::IsSBox(pNode.mBaseBufferSymbol.mSlot)) {
                aBaseBufferIndexOffset = Random::Get(S_SBOX);
            } else if (TwistWorkSpace::IsSalt(pNode.mBaseBufferSymbol.mSlot)) {
                aBaseBufferIndexOffset = Random::Get(S_SALT);
            } else {
                aBaseBufferIndexOffset = Random::Get(S_BLOCK);
            }
        }

        if ((aBaseBufferIndexOffset != 0) && !TwistWorkSpace::IsSBox(pNode.mBaseBufferSymbol.mSlot) && !TwistWorkSpace::IsSalt(pNode.mBaseBufferSymbol.mSlot)) {
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
                aBufferIndexExpr = GExpr::Add(aBufferIndexExpr, GExpr::Const32(aBaseBufferIndexOffset));
            }
            aBaseExpr = GExpr::Read(pNode.mBaseBufferSymbol, aBufferIndexExpr);
        }
        aBaseSymbol = pNode.mBaseBufferIndexSymbol;
    } else {
        if (aBaseSymbol.IsInvalid()) {
            SetError(pErrorMessage, "Composer buffer node did not have a valid base symbol.");
            return false;
        }
        if (!aBaseSymbol.IsVar()) {
            SetError(pErrorMessage, "Composer buffer node base symbol must be a variable.");
            return false;
        }
        aBaseExpr = GExpr::Symbol(aBaseSymbol);
    }

    const int aOffset = ResolveOffset(pNode, aBaseSymbol, aDomain, pErrorMessage);
    if (aOffset < 0) {
        if ((pErrorMessage == nullptr) || pErrorMessage->empty()) {
            SetError(pErrorMessage, "Composer resolved an invalid offset.");
        }
        return false;
    }

    if (pNode.mBaseFromBuffer && (aDomain == GLoopFragmentDomain::kBlock) && (aOffset != 0)) {
        SetError(pErrorMessage, "Composer does not support block wrap offset with buffer-based keys yet.");
        return false;
    }

    const bool aCanDirectBlockRead = !pNode.mBaseFromBuffer &&
                                     (aDomain == GLoopFragmentDomain::kBlock) &&
                                     (aOffset == 0) &&
                                     !pNode.mOffsetIsInverted &&
                                     CanUseDirectBlockIndex(aBaseSymbol, mLoopIndex);
    const bool aCanInlineNonBlockRead = (aDomain != GLoopFragmentDomain::kBlock) &&
                                        (aOffset == 0) &&
                                        !pNode.mOffsetIsInverted;
    const bool aUseBlockWrapRead = (aDomain == GLoopFragmentDomain::kBlock) &&
                                   !pNode.mBaseFromBuffer &&
                                   !pNode.mOffsetIsInverted &&
                                   !aCanDirectBlockRead;

    const bool aNeedKey = (aDomain == GLoopFragmentDomain::kBlock)
        ? (aUseBlockWrapRead || pNode.mOffsetIsInverted)
        : !aCanInlineNonBlockRead;
    const bool aNeedByte = aShouldExpand;
    BufferTemp aTemp = BuildBufferTemp(pNode,
                                       aNeedKey,
                                       aNeedByte,
                                       pKeyNameCounters,
                                       pByteNameCounters);

    if (aNeedKey && !aUseBlockWrapRead) {
        GExpr aKeyExpr = aBaseExpr;
        if (pNode.mOffsetIsInverted) {
            int aDomainMax = S_BLOCK - 1;
            switch (aDomain) {
                case GLoopFragmentDomain::kSBox:
                    aDomainMax = S_SBOX - 1;
                    break;
                case GLoopFragmentDomain::kSalt:
                    aDomainMax = S_SALT - 1;
                    break;
                case GLoopFragmentDomain::kBlock:
                default:
                    aDomainMax = S_BLOCK - 1;
                    break;
            }
            aKeyExpr = GExpr::Sub(GExpr::Const32(aDomainMax), aBaseExpr);
        }
        if (aOffset != 0) {
            aKeyExpr = GExpr::Add(aKeyExpr, GExpr::Const32(aOffset));
        }

        if (!AddStatement(pStatements,
                          GStatement::Assign(GTarget::Symbol(aTemp.mKeySymbol), aKeyExpr),
                          pErrorMessage)) {
            return false;
        }
    }

    GExpr aReadExpr;
    if (aDomain == GLoopFragmentDomain::kBlock) {
        if (aUseBlockWrapRead) {
            aReadExpr = GExpr::ReadBlockWrap(pNode.mSymbol, aBaseSymbol, aTemp.mKeySymbol, aOffset);
        } else if (aNeedKey) {
            const GExpr aKeyIndexExpr = GExpr::And(GExpr::Symbol(aTemp.mKeySymbol), GExpr::Const32(S_BLOCK1));
            aReadExpr = GExpr::Read(pNode.mSymbol, aKeyIndexExpr);
        } else {
            aReadExpr = GExpr::Read(pNode.mSymbol, aBaseExpr);
        }
    } else {
        if (aNeedKey) {
            aReadExpr = GExpr::Read(pNode.mSymbol, GExpr::Symbol(aTemp.mKeySymbol));
        } else {
            GExpr aIndexExpr = aBaseExpr;
            if (aOffset != 0) {
                aIndexExpr = GExpr::Add(aIndexExpr, GExpr::Const32(aOffset));
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

        if (!AddStatement(pStatements,
                          GStatement::Assign(GTarget::Symbol(aTemp.mByteSymbol), aByteExpr),
                          pErrorMessage)) {
            return false;
        }
    }

    if (!aNeedByte) {
        return EmitTargetCombine(aReadExpr, pNode.mCombineOp, pTargetInitialized, pStatements, pErrorMessage);
    }

    return EmitTargetCombine(GExpr::Symbol(aTemp.mByteSymbol),
                             pNode.mCombineOp,
                             pTargetInitialized,
                             pStatements,
                             pErrorMessage);
}

bool GLoopFragmentComposer::EmitVariableNode(const Node &pNode,
                                             bool *pTargetInitialized,
                                             std::unordered_map<std::string, int> *pVariableTempCounters,
                                             std::vector<GStatement> *pStatements,
                                             std::string *pErrorMessage) {
    if (!pNode.mSymbol.IsVar()) {
        SetError(pErrorMessage, "Composer variable node had an invalid variable symbol.");
        return false;
    }

    GSymbol aOperandSymbol = pNode.mSymbol;
    if (pNode.mHasDebugExpand || ((pNode.mExpandProbability > 0U) && Random::Chance(pNode.mExpandProbability))) {
        aOperandSymbol = BuildVariableTemp(pNode.mSymbol, pVariableTempCounters);

        const GExpr aExpandedExpr = pNode.mHasDebugExpand
            ? BuildExpandedExpressionDebug(pNode, GExpr::Symbol(pNode.mSymbol))
            : BuildExpandedExpression(GExpr::Symbol(pNode.mSymbol), pNode.mAllowMultiply);

        if (!AddStatement(pStatements,
                          GStatement::Assign(GTarget::Symbol(aOperandSymbol), aExpandedExpr),
                          pErrorMessage)) {
            return false;
        }
    }

    return EmitTargetCombine(GExpr::Symbol(aOperandSymbol),
                             pNode.mCombineOp,
                             pTargetInitialized,
                             pStatements,
                             pErrorMessage);
}

GLoopFragmentDomain GLoopFragmentComposer::ResolveDomain(const Node &pNode) const {
    if (pNode.mDomain != GLoopFragmentDomain::kAuto) {
        return pNode.mDomain;
    }
    if (pNode.mSymbol.IsBuf()) {
        if (TwistWorkSpace::IsSBox(pNode.mSymbol.mSlot)) {
            return GLoopFragmentDomain::kSBox;
        }
        if (TwistWorkSpace::IsSalt(pNode.mSymbol.mSlot)) {
            return GLoopFragmentDomain::kSalt;
        }
    }
    return GLoopFragmentDomain::kBlock;
}

int GLoopFragmentComposer::ResolveOffset(const Node &pNode,
                                         const GSymbol &pBaseSymbol,
                                         GLoopFragmentDomain pDomain,
                                         std::string *pErrorMessage) const {
    (void)pBaseSymbol;

    if (pNode.mOffsetIsDebugMax) {
        switch (pDomain) {
            case GLoopFragmentDomain::kSBox:
                return S_SBOX - 1;
            case GLoopFragmentDomain::kSalt:
                return S_SALT - 1;
            case GLoopFragmentDomain::kBlock:
            default:
                return S_BLOCK - 1;
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
                return Random::Get(S_BLOCK);
        }
    }

    if (pNode.mOffset < 0) {
        SetError(pErrorMessage, "Composer fixed offsets must be >= 0.");
        return -1;
    }

    switch (pDomain) {
        case GLoopFragmentDomain::kSBox:
            return PositiveMod(pNode.mOffset, S_SBOX);

        case GLoopFragmentDomain::kSalt:
            return PositiveMod(pNode.mOffset, S_SALT);

        case GLoopFragmentDomain::kBlock:
        default:
            return PositiveMod(pNode.mOffset, S_BLOCK);
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
            return GExpr::Add(pBaseExpr, GExpr::Const32(Random::Get(1, 31)));
        case 1:
            return GExpr::Xor(pBaseExpr, GExpr::Const32(Random::Get(1, 255)));
        case 2:
            return GExpr::Sub(pBaseExpr, GExpr::Const32(Random::Get(1, 17)));
        case 3:
            return GExpr::RotL8(pBaseExpr, GExpr::Const32(Random::Get(1, 7)));
        case 4:
            return GExpr::Mul(pBaseExpr, GExpr::Const32(Random::Get(2, 33)));
        default:
            return pBaseExpr;
    }
}

GExpr GLoopFragmentComposer::BuildExpandedExpressionDebug(const Node &pNode,
                                                          const GExpr &pBaseExpr) const {
    const int aRotateRaw = pNode.mDebugExpandConstantA;
    const int aRotateSafe = (aRotateRaw <= 0) ? 1 : (aRotateRaw & 7);
    const int aRotateAmount = (aRotateSafe == 0) ? 1 : aRotateSafe;
    const GExpr aConstA = GExpr::Const32(pNode.mDebugExpandConstantA);
    const GExpr aConstB = GExpr::Const32(pNode.mDebugExpandConstantB);
    const GExpr aRotateExpr = GExpr::Const32(aRotateAmount);

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
    if (mInitialCombineMode == TargetCombineMode::kInvalid) {
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

    std::size_t aOpIndex = 0U;
    std::size_t aOperandIndex = 0U;

    auto ParseMul = [&]() -> GExpr {
        if (aOperandIndex >= mDeferredCombineOperands.size()) {
            return GExpr();
        }
        GExpr aExpr = mDeferredCombineOperands[aOperandIndex++];
        while ((aOpIndex < mDeferredCombineOps.size()) &&
               (mDeferredCombineOps[aOpIndex] == DeferredCombineOp::kMul)) {
            if (aOperandIndex >= mDeferredCombineOperands.size()) {
                return GExpr();
            }
            aExpr = GExpr::Mul(aExpr, mDeferredCombineOperands[aOperandIndex++]);
            ++aOpIndex;
        }
        return aExpr;
    };

    auto ParseAddSub = [&]() -> GExpr {
        GExpr aExpr = ParseMul();
        if (aExpr.IsInvalid()) {
            return aExpr;
        }
        while (aOpIndex < mDeferredCombineOps.size()) {
            const DeferredCombineOp aOp = mDeferredCombineOps[aOpIndex];
            if ((aOp != DeferredCombineOp::kAdd) && (aOp != DeferredCombineOp::kSub)) {
                break;
            }
            ++aOpIndex;
            GExpr aRight = ParseMul();
            if (aRight.IsInvalid()) {
                return GExpr();
            }
            if (aOp == DeferredCombineOp::kAdd) {
                aExpr = GExpr::Add(aExpr, aRight);
            } else {
                aExpr = GExpr::Sub(aExpr, aRight);
            }
        }
        return aExpr;
    };

    GExpr aExpr = ParseAddSub();
    if (aExpr.IsInvalid()) {
        return GExpr();
    }
    while (aOpIndex < mDeferredCombineOps.size()) {
        if (mDeferredCombineOps[aOpIndex] != DeferredCombineOp::kXor) {
            return GExpr();
        }
        ++aOpIndex;
        GExpr aRight = ParseAddSub();
        if (aRight.IsInvalid()) {
            return GExpr();
        }
        aExpr = GExpr::Xor(aExpr, aRight);
    }

    if (aOperandIndex != mDeferredCombineOperands.size()) {
        return GExpr();
    }
    return aExpr;
}

bool GLoopFragmentComposer::FlushDeferredCombine(std::vector<GStatement> *pStatements,
                                                 std::string *pErrorMessage) {
    if (!mDeferCombine || mDeferredCombineOperands.empty()) {
        mDeferredCombineOps.clear();
        return true;
    }

    const GExpr aCombinedExpr = BuildDeferredExpression();
    mDeferredCombineOperands.clear();
    mDeferredCombineOps.clear();
    if (aCombinedExpr.IsInvalid()) {
        SetError(pErrorMessage, "Composer failed to build deferred combine expression.");
        return false;
    }

    GStatement aStatement;
    switch (mDeferredCombineMode) {
        case TargetCombineMode::kAdd:
            aStatement = GStatement::Assign(GTarget::Symbol(mTarget),
                                            GExpr::Add(GExpr::Symbol(mTarget), aCombinedExpr));
            break;
        case TargetCombineMode::kXor:
            aStatement = GStatement::Assign(GTarget::Symbol(mTarget),
                                            GExpr::Xor(GExpr::Symbol(mTarget), aCombinedExpr));
            break;
        case TargetCombineMode::kSet:
        default:
            aStatement = GStatement::Assign(GTarget::Symbol(mTarget), aCombinedExpr);
            break;
    }
    mDeferredCombineMode = TargetCombineMode::kInvalid;
    return AddStatement(pStatements, aStatement, pErrorMessage);
}

bool GLoopFragmentComposer::ResolveToStatementsAndExpression(std::vector<GStatement> *pStatements,
                                                             GExpr &pExpr,
                                                             std::string *pErrorMessage) {
    pExpr = GExpr();

    if (pStatements == nullptr) {
        SetError(pErrorMessage, "Composer output statement list was null.");
        return false;
    }

    if (!mConfigError.empty()) {
        SetError(pErrorMessage, mConfigError);
        return false;
    }

    if (mNodes.empty()) {
        SetError(pErrorMessage, "Composer had no nodes to resolve.");
        return false;
    }

    bool aTargetInitialized = false;
    std::unordered_map<std::string, int> aKeyNameCounters;
    std::unordered_map<std::string, int> aByteNameCounters;
    std::unordered_map<std::string, int> aVariableTempCounters;
    mDeferredCombineOperands.clear();
    mDeferredCombineOps.clear();
    mDeferCombine = true;
    mDeferredCombineMode = TargetCombineMode::kInvalid;
    mDeferredNextCombineOp = GLoopFragmentComposerCombineOp::kAdd;
    
    std::vector<std::size_t> aNodeOrder;
    aNodeOrder.reserve(mNodes.size());
    for (std::size_t aNodeIndex = 0U; aNodeIndex < mNodes.size(); ++aNodeIndex) {
        aNodeOrder.push_back(aNodeIndex);
    }
    if (mShufflePending) {
        Random::Shuffle(&aNodeOrder);
        mShufflePending = false;
    }

    for (const std::size_t aNodeIndex : aNodeOrder) {
        const Node &aNode = mNodes[aNodeIndex];
        switch (aNode.mType) {
            case NodeType::kMixBuffer:
                if (!EmitBufferNode(aNode,
                                    &aTargetInitialized,
                                    &aKeyNameCounters,
                                    &aByteNameCounters,
                                    pStatements,
                                    pErrorMessage)) {
                    return false;
                }
                break;

            case NodeType::kMixVariable:
                if (!EmitVariableNode(aNode,
                                      &aTargetInitialized,
                                      &aVariableTempCounters,
                                      pStatements,
                                      pErrorMessage)) {
                    return false;
                }
                break;

            default:
                SetError(pErrorMessage, "Composer encountered an invalid node type while resolving.");
                return false;
        }
    }

    if (!aTargetInitialized) {
        SetError(pErrorMessage, "Composer could not resolve any operands.");
        return false;
    }

    pExpr = BuildDeferredExpression();
    mDeferredCombineOperands.clear();
    mDeferredCombineOps.clear();
    mDeferredCombineMode = TargetCombineMode::kInvalid;
    mDeferredNextCombineOp = GLoopFragmentComposerCombineOp::kAdd;
    mDeferCombine = false;

    if (pExpr.IsInvalid()) {
        SetError(pErrorMessage, "Composer failed to build resolved expression.");
        return false;
    }

    return true;
}

bool GLoopFragmentComposer::Bake(std::vector<GStatement> *pStatements,
                                           std::string *pErrorMessage) {
    if (pStatements == nullptr) {
        SetError(pErrorMessage, "Composer output statement list was null.");
        return false;
    }

    if (!mConfigError.empty()) {
        SetError(pErrorMessage, mConfigError);
        return false;
    }

    if (!mTarget.IsVar()) {
        SetError(pErrorMessage, "Composer target must be a valid variable symbol.");
        return false;
    }

    if (mNodes.empty()) {
        SetError(pErrorMessage, "Composer had no nodes to bake.");
        return false;
    }

    bool aTargetInitialized = false;
    std::unordered_map<std::string, int> aKeyNameCounters;
    std::unordered_map<std::string, int> aByteNameCounters;
    std::unordered_map<std::string, int> aVariableTempCounters;
    mDeferredCombineOperands.clear();
    mDeferredCombineOps.clear();
    mDeferCombine = ShouldDeferCombine();
    mDeferredCombineMode = TargetCombineMode::kInvalid;
    mDeferredNextCombineOp = GLoopFragmentComposerCombineOp::kAdd;
    
    std::vector<std::size_t> aNodeOrder;
    aNodeOrder.reserve(mNodes.size());
    for (std::size_t aNodeIndex = 0U; aNodeIndex < mNodes.size(); ++aNodeIndex) {
        aNodeOrder.push_back(aNodeIndex);
    }
    if (mShufflePending) {
        Random::Shuffle(&aNodeOrder);
        mShufflePending = false;
    }

    for (const std::size_t aNodeIndex : aNodeOrder) {
        const Node &aNode = mNodes[aNodeIndex];
        switch (aNode.mType) {
            case NodeType::kMixBuffer:
                if (!EmitBufferNode(aNode,
                                    &aTargetInitialized,
                                    &aKeyNameCounters,
                                    &aByteNameCounters,
                                    pStatements,
                                    pErrorMessage)) {
                    return false;
                }
                break;

            case NodeType::kMixVariable:
                if (!EmitVariableNode(aNode,
                                      &aTargetInitialized,
                                      &aVariableTempCounters,
                                      pStatements,
                                      pErrorMessage)) {
                    return false;
                }
                break;

            default:
                SetError(pErrorMessage, "Composer encountered an invalid node type while baking.");
                return false;
        }
    }

    if (!FlushDeferredCombine(pStatements, pErrorMessage)) {
        return false;
    }

    if (!aTargetInitialized) {
        SetError(pErrorMessage, "Composer could not initialize target during bake.");
        return false;
    }

    return true;
}
