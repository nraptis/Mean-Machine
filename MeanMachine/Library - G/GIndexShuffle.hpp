//
//  GIndexShuffle.hpp
//  MeanMachine
//

#ifndef GIndexShuffle_hpp
#define GIndexShuffle_hpp

#include "GSeedProgram.hpp"

#include <string>

class GIndexShuffle {
public:
    static bool BakeA(const GSymbol pIndexList,
                      const GSymbol pEntropySource,
                      std::vector<GStatement> *pStatements,
                      std::string *pErrorMessage) {
        return Bake("ExecuteA", pIndexList, pEntropySource, pStatements, pErrorMessage);
    }

    static bool BakeB(const GSymbol pIndexList,
                      const GSymbol pEntropySource,
                      std::vector<GStatement> *pStatements,
                      std::string *pErrorMessage) {
        return Bake("ExecuteB", pIndexList, pEntropySource, pStatements, pErrorMessage);
    }

private:
    static bool Bake(const char *pMethodName,
                     const GSymbol pIndexList,
                     const GSymbol pEntropySource,
                     std::vector<GStatement> *pStatements,
                     std::string *pErrorMessage) {
        if (pStatements == nullptr) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GIndexShuffle::Bake requires statement output.";
            }
            return false;
        }
        if (!pIndexList.IsBuf() || !pEntropySource.IsBuf()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GIndexShuffle::Bake requires buffer symbols.";
            }
            return false;
        }
        const TwistWorkSpaceSlot aIndexListSlot = ResolveBufferSlot(pIndexList);
        const bool aIndexListValid =
            (aIndexListSlot == TwistWorkSpaceSlot::kIndexList256A) ||
            (aIndexListSlot == TwistWorkSpaceSlot::kIndexList256B) ||
            (aIndexListSlot == TwistWorkSpaceSlot::kIndexList256C) ||
            (aIndexListSlot == TwistWorkSpaceSlot::kIndexList256D);
        if (!aIndexListValid) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GIndexShuffle::Bake index-list key must be one of index_list_256_a/b/c/d.";
            }
            return false;
        }

        const std::string aIndexAlias = BufAliasName(pIndexList);
        const std::string aEntropyAlias = BufAliasName(pEntropySource);
        if (aIndexAlias.empty() || aEntropyAlias.empty()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = "GIndexShuffle::Bake failed to resolve buffer alias.";
            }
            return false;
        }

        pStatements->push_back(
            GStatement::RawLine(std::string("TwistIndexShuffle::") + pMethodName + "(" + aIndexAlias + ", " + aEntropyAlias + ");")
        );
        return true;
    }
};

#endif /* GIndexShuffle_hpp */
