//
//  TwistSquash.hpp
//  MeanMachine
//
//  Created by icarus black on 6/23/26.
//

#ifndef TwistSquash_hpp
#define TwistSquash_hpp

#include <cstdint>
#include "TwistWorkSpace.hpp"

class TwistSquash {
    
public:
    
    static void             SquashA(std::uint8_t *pInputLaneA,
                                    std::uint8_t *pInputLaneB,
                                    std::uint8_t *pInputLaneC,
                                    std::uint8_t *pInputLaneD,
                                    std::uint8_t *pOutputLane);
    static void             SquashB(std::uint8_t *pInputLaneA,
                                    std::uint8_t *pInputLaneB,
                                    std::uint8_t *pInputLaneC,
                                    std::uint8_t *pInputLaneD,
                                    std::uint8_t *pOutputLane);
    static void             SquashC(std::uint8_t *pInputLaneA,
                                    std::uint8_t *pInputLaneB,
                                    std::uint8_t *pInputLaneC,
                                    std::uint8_t *pInputLaneD,
                                    std::uint8_t *pOutputLane);
    
    
    /*
     [aaaa aaaa aaaa aaaa]
     [bbbb bbbb bbbb bbbb]
     [cccc cccc cccc cccc]
     [dddd dddd dddd dddd]
     
     =>
     
     input quarter 0 [abcd] -> output lane A quarter 0
     input quarter 1 [abcd] -> output lane B quarter 0
     input quarter 2 [abcd] -> output lane C quarter 0
     input quarter 3 [abcd] -> output lane D quarter 0

     Only the first quarter of each output lane is written.
     
     */
    static void             FoldQuarterA(std::uint8_t *pInputLaneA,
                                         std::uint8_t *pInputLaneB,
                                         std::uint8_t *pInputLaneC,
                                         std::uint8_t *pInputLaneD,
                                         std::uint8_t *pOutputLaneA,
                                         std::uint8_t *pOutputLaneB,
                                         std::uint8_t *pOutputLaneC,
                                         std::uint8_t *pOutputLaneD);
    
    
};


#endif /* TwistSquash_hpp */
