//
//  TwistDiffuse.cpp
//  MeanMachine
//
//  Created by icarus black on 6/23/26.
//

#include "TwistDiffuse.hpp"
#include "TwistIndexShuffle.hpp"

namespace {

void DiffuseLane(std::uint8_t *pInputLaneA,
                 std::uint8_t *pInputLaneB,
                 std::uint8_t *pOutputLane,
                 std::uint8_t *pOperationSourceLane,
                 std::size_t *pIndexListLeft,
                 std::size_t *pIndexListRight,
                 M88 *pMatrix,
                 int pInputOffsetA,
                 int pInputOffsetB) {
    std::size_t aWriteIndex = 0U;
    std::size_t aReadIndexA = 0U;
    std::size_t aReadIndexB = 0U;
    
    for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
        aReadIndexA = (pIndexListLeft[aMatrixDiffusionIndex & S_SBOX1] * 128U) + static_cast<std::size_t>(pInputOffsetA);
        aReadIndexB = (pIndexListRight[aMatrixDiffusionIndex & S_SBOX1] * 128U) + static_cast<std::size_t>(pInputOffsetB);
        if ((pOperationSourceLane[aWriteIndex] & 0x7E) > 62) {
            pMatrix->Dispatch(pOperationSourceLane,
                              aWriteIndex,
                              pInputLaneA,
                              aReadIndexA,
                              pOutputLane,
                              aWriteIndex);
            aWriteIndex = aWriteIndex + 64U;
            pMatrix->Dispatch(pOperationSourceLane,
                              aWriteIndex,
                              pInputLaneB,
                              aReadIndexB,
                              pOutputLane,
                              aWriteIndex);
        } else {
            pMatrix->Dispatch(pOperationSourceLane,
                              aWriteIndex,
                              pInputLaneB,
                              aReadIndexB,
                              pOutputLane,
                              aWriteIndex);
            aWriteIndex = aWriteIndex + 64U;
            pMatrix->Dispatch(pOperationSourceLane,
                              aWriteIndex,
                              pInputLaneA,
                              aReadIndexA,
                              pOutputLane,
                              aWriteIndex);
        }
        aWriteIndex = aWriteIndex + 64U;
    }
}

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
        aReadIndexA = (pIndexListLeft[aMatrixDiffusionIndex & S_SBOX1] * 128U) + static_cast<std::size_t>(pInputOffsetA);
        aReadIndexB = (pIndexListRight[aMatrixDiffusionIndex & S_SBOX1] * 128U) + static_cast<std::size_t>(pInputOffsetB);
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

void TwistDiffuse::Diffuse(std::uint8_t *pInputLaneA,
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
                           M88 *pMatrix) {
    TwistIndexShuffle::ExecuteA(pIndexList256A, pShuffleEntropyLaneA);
    TwistIndexShuffle::ExecuteA(pIndexList256B, pShuffleEntropyLaneB);
    TwistIndexShuffle::ExecuteB(pIndexList256C, pShuffleEntropyLaneA);
    TwistIndexShuffle::ExecuteB(pIndexList256D, pShuffleEntropyLaneB);
    
    DiffuseLane(pInputLaneA,
                pInputLaneB,
                pOutputLaneA,
                pOperationSourceLaneA,
                pIndexList256A,
                pIndexList256B,
                pMatrix,
                0,
                64);
    
    DiffuseLane(pInputLaneA,
                pInputLaneB,
                pOutputLaneB,
                pOperationSourceLaneB,
                pIndexList256C,
                pIndexList256D,
                pMatrix,
                64,
                0);
}

void TwistDiffuse::DiffuseWithDomainWords(std::uint8_t *pInputLaneA,
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
                                          std::uint8_t pMatrixArgD) {
    TwistIndexShuffle::ExecuteA(pIndexList256A, pShuffleEntropyLaneA);
    TwistIndexShuffle::ExecuteA(pIndexList256B, pShuffleEntropyLaneB);
    TwistIndexShuffle::ExecuteB(pIndexList256C, pShuffleEntropyLaneA);
    TwistIndexShuffle::ExecuteB(pIndexList256D, pShuffleEntropyLaneB);
    
    DiffuseLaneWithDomainWords(pInputLaneA,
                               pInputLaneB,
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
    
    DiffuseLaneWithDomainWords(pInputLaneA,
                               pInputLaneB,
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
}
