//
//  TwistRankPrune.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/4/26.
//

#ifndef TwistRankPrune_hpp
#define TwistRankPrune_hpp

#include <cstdint>

class TwistRankPrune {
    
public:
    
    static int                          Execute(std::uint8_t **pMainList,
                                                int pItemCount,
                                                std::uint32_t *pRanks,
                                                int pMinimumTake);
    
};

#endif /* TwistRankPrune_hpp */
