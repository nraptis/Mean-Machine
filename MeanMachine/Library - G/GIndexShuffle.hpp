//
//  GIndexShuffle.hpp
//  MeanMachine
//

#ifndef GIndexShuffle_hpp
#define GIndexShuffle_hpp

#include "GSeedProgram.hpp"

class GIndexShuffle {
public:
    static bool BakeExecute256(const GSymbol pIndexList,
                               const GSymbol pEntropySource,
                               std::vector<GStatement> *pStatements,
                               std::string *pErrorMessage) {
        if (pStatements == nullptr) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GIndexShuffle::BakeExecute256 requires statement output.";
            }
            return false;
        }
        if (!pIndexList.IsBuf() || !pEntropySource.IsBuf()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GIndexShuffle::BakeExecute256 requires buffer symbols.";
            }
            return false;
        }
        bool aIndexListValid = false;
        const TwistBufferKey aIndexListKey = ResolveBufferKey(pIndexList);
        if (aIndexListKey.IsValid() &&
            aIndexListKey.mKind == TwistBufferKind::kDirect) {
            switch (aIndexListKey.mDirect) {
                case TwistDirectBuffer::kIndexList256A:
                case TwistDirectBuffer::kIndexList256B:
                case TwistDirectBuffer::kIndexList256C:
                case TwistDirectBuffer::kIndexList256D:
                    aIndexListValid = true;
                    break;
                default:
                    break;
            }
        }
        if (!aIndexListValid) {
            const TwistWorkSpaceSlot aIndexListSlot = ResolveBufferSlot(pIndexList);
            aIndexListValid =
                (aIndexListSlot == TwistWorkSpaceSlot::kIndexList256A) ||
                (aIndexListSlot == TwistWorkSpaceSlot::kIndexList256B) ||
                (aIndexListSlot == TwistWorkSpaceSlot::kIndexList256C) ||
                (aIndexListSlot == TwistWorkSpaceSlot::kIndexList256D);
        }
        if (!aIndexListValid) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GIndexShuffle::BakeExecute256 index-list key must be one of index_list_256_a/b/c/d.";
            }
            return false;
        }

        const std::string aIndexAlias = BufAliasName(pIndexList);
        const std::string aEntropyAlias = BufAliasName(pEntropySource);
        if (aIndexAlias.empty() || aEntropyAlias.empty()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GIndexShuffle::BakeExecute256 failed to resolve buffer alias.";
            }
            return false;
        }

        pStatements->push_back(
            GStatement::RawLine("TwistIndexShuffle::Execute256(" + aIndexAlias + ", " + aEntropyAlias + ");")
        );
        return true;
    }
};

#endif /* GIndexShuffle_hpp */
