//
//  GSimpleLoopExampleRecipe.hpp
//  MeanMachine
//
//  Created by Trombone on 4/26/26.
//

#ifndef GSimpleLoopExampleRecipe_hpp
#define GSimpleLoopExampleRecipe_hpp

#include "GSeedProgram.hpp"
#include "GSymbol.hpp"
#include "GStatementRecipe.hpp"
#include "GQuick.hpp"
#include "Random.hpp"
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

struct GSimpleLoopExampleRecipe {
public:
    GSimpleLoopExampleRecipe();
    
    
    // value consumes:
    // salt a, work lane a, s-box a, carry
    
    // carry consumes:
    // salt b, work lane b, s-box b, s-box c, value
    
    
    bool                                Plan(std::string &pErrorString);
    bool                                Bake(std::vector<GLoop> &pResult,
                                             bool pValueOrder[4],
                                             bool pValueSBoxReadUsesValueItself,
                                             bool pCarryOrder[4],
                                             bool pCarrySBoxReadUsesValueItself,
                                             std::string &pErrorString);
    
    GSymbol                             mLoopIndex;
    
    GSymbol                             mValue;
    
    GSymbol                             mCarry;
    
    GSymbol                             mSBoxA;
    GSymbol                             mSBoxB;
    GSymbol                             mSBoxC;
    
    GSymbol                             mSaltA;
    GSymbol                             mSaltB;
    
    GSymbol                             mWorkLaneA;
    GSymbol                             mWorkLaneB;
        
};

#endif /* GSimpleLoopExampleRecipe_hpp */
