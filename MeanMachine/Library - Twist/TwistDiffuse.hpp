//
//  TwistDiffuse.hpp
//  MeanMachine
//
//  Created by icarus black on 6/23/26.
//

#ifndef TwistDiffuse_hpp
#define TwistDiffuse_hpp

#include <cstdint>
#include <cstddef>

#include "M88/M88.hpp"
#include "TwistWorkSpace.hpp"

class TwistDiffuse {
    
public:
    
    static void                 Diffuse(std::uint8_t *pInputLaneA,
                                        std::uint8_t *pInputLaneB,
                                        std::uint8_t *pOutputLaneA,
                                        std::uint8_t *pOutputLaneB,
                                        std::uint8_t *pShuffleEntropyLaneA,
                                        std::uint8_t *pShuffleEntropyLaneB,
                                        std::uint8_t *pOperationSourceLaneA,
                                        std::uint8_t *pOperationSourceLaneB,
                                        std::size_t *pIndexList256A,
                                        std::size_t *pIndexList256B,
                                        std::size_t *pIndexList256C,
                                        std::size_t *pIndexList256D,
                                        M88 *pMatrix);
    
    static void                 DiffuseWithDomainWords(std::uint8_t *pInputLaneA,
                                                       std::uint8_t *pInputLaneB,
                                                       std::uint8_t *pOutputLaneA,
                                                       std::uint8_t *pOutputLaneB,
                                                       std::uint8_t *pShuffleEntropyLaneA,
                                                       std::uint8_t *pShuffleEntropyLaneB,
                                                       std::uint8_t *pOperationSourceLaneA,
                                                       std::uint8_t *pOperationSourceLaneB,
                                                       std::size_t *pIndexList256A,
                                                       std::size_t *pIndexList256B,
                                                       std::size_t *pIndexList256C,
                                                       std::size_t *pIndexList256D,
                                                       M88 *pMatrix,
                                                       std::uint64_t pMatrixSelectA,
                                                       std::uint64_t pMatrixSelectB,
                                                       std::uint8_t pMatrixUnrollA,
                                                       std::uint8_t pMatrixUnrollB,
                                                       std::uint8_t pMatrixArgA,
                                                       std::uint8_t pMatrixArgB,
                                                       std::uint8_t pMatrixArgC,
                                                       std::uint8_t pMatrixArgD);
    
    
};

#endif /* TwistDiffuse_hpp */
