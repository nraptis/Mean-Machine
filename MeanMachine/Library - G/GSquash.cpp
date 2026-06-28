//
//  GSquash.cpp
//  MeanMachine
//
//  Created by nick raptis on 6/10/26.
//

#include "GSquash.hpp"
#include "Random.hpp"

#include <vector>

GSquash::GSquash() {
    
}

bool GSquash::Bake(GSymbol pDest,
                                 
                   GSymbol pSourceA,
                   GSymbol pSourceB,
                   GSymbol pSourceC,
                   GSymbol pSourceD,
                   
                   GSymbol pIndex,
                   
                   std::vector<GStatement> *pStatements,
                   std::string *pErrorMessage) {
    
    if (pStatements == nullptr) {
        if (pErrorMessage != nullptr) {
            *pErrorMessage = "GSquash::Bake received null statement output";
        }
        return false;
    }
    (void)pIndex;

    auto ValidateBlockBuffer = [&](const GSymbol &pSymbol,
                                   const char *pLabel) -> bool {
        if (!pSymbol.IsBuf()) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("GSquash ") + pLabel + " must be a buffer symbol.";
            }
            return false;
        }
        const int aLength = pSymbol.mKey.IsValid()
            ? TwistWorkSpace::GetBufferLength(pSymbol.mKey)
            : TwistWorkSpace::GetBufferLength(pSymbol.mSlot);
        if (aLength != S_BLOCK) {
            if (pErrorMessage != nullptr) {
                *pErrorMessage = std::string("GSquash ") + pLabel + " must resolve to a block-sized buffer.";
            }
            return false;
        }
        return true;
    };

    if (!ValidateBlockBuffer(pDest, "destination") ||
        !ValidateBlockBuffer(pSourceA, "source A") ||
        !ValidateBlockBuffer(pSourceB, "source B") ||
        !ValidateBlockBuffer(pSourceC, "source C") ||
        !ValidateBlockBuffer(pSourceD, "source D")) {
        return false;
    }
    
    const char *aMethod = "SquashA";
    switch (Random::Get(3)) {
        case 0:
            aMethod = "SquashA";
            break;
        case 1:
            aMethod = "SquashB";
            break;
        default:
            aMethod = "SquashC";
            break;
    }

    const std::string aLine = std::string("TwistSquash::") + aMethod + "(" +
        BufAliasName(pSourceA) + ", " +
        BufAliasName(pSourceB) + ", " +
        BufAliasName(pSourceC) + ", " +
        BufAliasName(pSourceD) + ", " +
        BufAliasName(pDest) + ");";
    pStatements->push_back(GStatement::RawLine(aLine));
    
    return true;    
}
