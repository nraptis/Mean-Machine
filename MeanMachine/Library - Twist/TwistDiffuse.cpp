//
//  TwistDiffuse.cpp
//  MeanMachine
//
//  Created by icarus black on 6/23/26.
//

#include "TwistDiffuse.hpp"
#include "TwistIndexShuffle.hpp"

namespace {

void DiffuseLaneWithDomainWords(std::uint8_t *pInputLaneA,
                                std::uint8_t *pInputLaneB,
                                std::uint8_t *pOutputLane,
                                std::uint8_t *pOperationSourceLane,
                                std::size_t *pIndexListLeft,
                                std::size_t *pIndexListRight,
                                M88 *pMatrix,
                                int pInputOffsetA,
                                int pInputOffsetB,
                                std::uint64_t pMatrixSelect,
                                std::uint8_t pMatrixUnroll,
                                std::uint8_t pMatrixArgA,
                                std::uint8_t pMatrixArgB,
                                std::uint8_t pMatrixArgC,
                                std::uint8_t pMatrixArgD) {
    std::size_t aWriteIndex = 0U;
    std::size_t aReadIndexA = 0U;
    std::size_t aReadIndexB = 0U;
    
    for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
        aReadIndexA = (pIndexListLeft[aMatrixDiffusionIndex & 255] * 128U) + static_cast<std::size_t>(pInputOffsetA);
        aReadIndexB = (pIndexListRight[aMatrixDiffusionIndex & 255] * 128U) + static_cast<std::size_t>(pInputOffsetB);
        if (((pOperationSourceLane[aWriteIndex] ^ pMatrixSelect) & 0x7E) > 62) {
            pMatrix->Dispatch(pOperationSourceLane,
                              aWriteIndex,
                              pInputLaneA,
                              aReadIndexA,
                              pOutputLane,
                              aWriteIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
            aWriteIndex = aWriteIndex + 64U;
            pMatrix->Dispatch(pOperationSourceLane,
                              aWriteIndex,
                              pInputLaneB,
                              aReadIndexB,
                              pOutputLane,
                              aWriteIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
        } else {
            pMatrix->Dispatch(pOperationSourceLane,
                              aWriteIndex,
                              pInputLaneB,
                              aReadIndexB,
                              pOutputLane,
                              aWriteIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
            aWriteIndex = aWriteIndex + 64U;
            pMatrix->Dispatch(pOperationSourceLane,
                              aWriteIndex,
                              pInputLaneA,
                              aReadIndexA,
                              pOutputLane,
                              aWriteIndex,
                              pMatrixUnroll,
                              pMatrixArgA,
                              pMatrixArgB,
                              pMatrixArgC,
                              pMatrixArgD);
        }
        aWriteIndex = aWriteIndex + 64U;
    }
}

} // namespace

void TwistDiffuse::DiffuseWithDomainWords(std::uint8_t *pInputLaneA,
                                          std::uint8_t *pInputLaneB,
                                          std::uint8_t *pInputLaneC,
                                          std::uint8_t *pInputLaneD,
                                          std::uint8_t *pOutputLaneA,
                                          std::uint8_t *pOutputLaneB,
                                          std::uint8_t *pOutputLaneC,
                                          std::uint8_t *pOutputLaneD,
                                          std::uint8_t *pShuffleEntropyLaneA,
                                          std::uint8_t *pShuffleEntropyLaneB,
                                          std::uint8_t *pShuffleEntropyLaneC,
                                          std::uint8_t *pShuffleEntropyLaneD,
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
                                          std::uint8_t pMatrixArgD) {
    TwistIndexShuffle::Execute(pIndexList256A, pShuffleEntropyLaneA);
    TwistIndexShuffle::Execute(pIndexList256B, pShuffleEntropyLaneB);
    TwistIndexShuffle::Execute(pIndexList256C, pShuffleEntropyLaneC);
    TwistIndexShuffle::Execute(pIndexList256D, pShuffleEntropyLaneD);
    
    // A @ 0, C @ 64
    DiffuseLaneWithDomainWords(pInputLaneA,
                               pInputLaneC,
                               pOutputLaneA,
                               pOperationSourceLaneA,
                               pIndexList256A,
                               pIndexList256B,
                               pMatrix,
                               0,
                               64,
                               pMatrixSelectA,
                               pMatrixUnrollA,
                               pMatrixArgA,
                               pMatrixArgB,
                               pMatrixArgC,
                               pMatrixArgD);
    
    // A @ 64, D @ 0
    DiffuseLaneWithDomainWords(pInputLaneA,
                               pInputLaneD,
                               pOutputLaneB,
                               pOperationSourceLaneB,
                               pIndexList256C,
                               pIndexList256D,
                               pMatrix,
                               64,
                               0,
                               pMatrixSelectB,
                               pMatrixUnrollB,
                               pMatrixArgA,
                               pMatrixArgB,
                               pMatrixArgC,
                               pMatrixArgD);

    // B @ 64, C @ 0
    DiffuseLaneWithDomainWords(pInputLaneB,
                               pInputLaneC,
                               pOutputLaneC,
                               pOperationSourceLaneA,
                               pIndexList256A,
                               pIndexList256B,
                               pMatrix,
                               64,
                               0,
                               pMatrixSelectA,
                               pMatrixUnrollA,
                               pMatrixArgA,
                               pMatrixArgB,
                               pMatrixArgC,
                               pMatrixArgD);

    // B @ 0, D @ 64
    DiffuseLaneWithDomainWords(pInputLaneB,
                               pInputLaneD,
                               pOutputLaneD,
                               pOperationSourceLaneB,
                               pIndexList256C,
                               pIndexList256D,
                               pMatrix,
                               0,
                               64,
                               pMatrixSelectB,
                               pMatrixUnrollB,
                               pMatrixArgA,
                               pMatrixArgB,
                               pMatrixArgC,
                               pMatrixArgD);
}
