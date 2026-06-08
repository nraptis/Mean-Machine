//
//  M88.cpp
//  CyberMatrix
//
//  Created by Six Pack Abs on 5/29/26.
//

#include "M88.hpp"
#include "M88QuadSelectsA.hpp"
#include "M88QuadSelectsB.hpp"
#include "M88QuadSelectsC.hpp"
#include "M88QuadSelectsD.hpp"
#include <cstdio>

M88::M88() {
    Reset();
}

void M88::Reset() {
    for (std::size_t i = 0; i < 64U; i++) {
        mData[i] = static_cast<std::uint8_t>(i);
    }
}

void M88::Print() const {
    
    for (std::size_t y = 0; y < 8U; y++) {
        for (std::size_t x = 0; x < 8U; x++) {
            const std::size_t aIndex = y * 8U + x;
            std::printf("%3u ", static_cast<unsigned int>(mData[aIndex]));
        }
        
        std::printf("\n");
    }
    
    std::printf("\n");
}

void M88::Dispatch(std::uint8_t *pOperationData,
                   std::size_t pOperationIndex,
                   std::uint8_t *pSource,
                   std::size_t pSourceIndex,
                   std::uint8_t *pDestination,
                   std::size_t pDestinationIndex,
                   std::uint8_t pUnrollDomainWord,
                   std::uint8_t pArgADomainWord,
                   std::uint8_t pArgBDomainWord,
                   std::uint8_t pArgCDomainWord,
                   std::uint8_t pArgDDomainWord) {
    
    std::uint8_t *aOperationData = pOperationData + pOperationIndex;
    std::uint8_t *aSource = pSource + pSourceIndex;
    std::uint8_t *aDestination = pDestination + pDestinationIndex;
    
    memcpy(mData, aSource, 64U);
    
    DispatchPermute(aOperationData[4] ^ pArgADomainWord,
                    aOperationData[5],
                    aOperationData[6],
                    aOperationData[7],
                    aOperationData[8] ^ pArgBDomainWord,
                    aOperationData[9],
                    aOperationData[10],
                    aOperationData[11],
                    
                    aOperationData[12] ^ pArgCDomainWord,
                    aOperationData[13],
                    aOperationData[14],
                    aOperationData[15],
                    aOperationData[16] ^ pArgDDomainWord,
                    aOperationData[17],
                    aOperationData[18],
                    aOperationData[19],
                    
                    aOperationData[20]);
    
    DispatchFullA(aOperationData[21]);
    
    DispatchSwapsA(aOperationData[22] ^ pArgADomainWord,
                   aOperationData[23] ^ pArgBDomainWord);
    
    DispatchQuadA(aOperationData[24] ^ pArgADomainWord);
    DispatchQuadB(aOperationData[25] ^ pArgBDomainWord);
    DispatchQuadC(aOperationData[26] ^ pArgCDomainWord);
    DispatchQuadD(aOperationData[27] ^ pArgDDomainWord);
    
    DispatchSwapsB(aOperationData[28] ^ pArgCDomainWord);
    
    DispatchMini(aOperationData[29]);
    
    DispatchPermute(aOperationData[30] ^ pArgADomainWord,
                    aOperationData[31],
                    aOperationData[32],
                    aOperationData[33],
                    aOperationData[34] ^ pArgBDomainWord,
                    aOperationData[35],
                    aOperationData[36],
                    aOperationData[37],
                    
                    aOperationData[38] ^ pArgCDomainWord,
                    aOperationData[39],
                    aOperationData[40],
                    aOperationData[41],
                    aOperationData[42] ^ pArgDDomainWord,
                    aOperationData[43],
                    aOperationData[44],
                    aOperationData[45],
                    
                    aOperationData[46]);
    
    DispatchMini(aOperationData[47]);
    
    DispatchSwapsB(aOperationData[48] ^ pArgDDomainWord);
    
    DispatchQuadD(aOperationData[49] ^ pArgDDomainWord);
    DispatchQuadC(aOperationData[50] ^ pArgCDomainWord);
    DispatchQuadB(aOperationData[51] ^ pArgBDomainWord);
    DispatchQuadA(aOperationData[52] ^ pArgADomainWord);
    
    DispatchSwapsA(aOperationData[53] ^ pArgCDomainWord,
                   aOperationData[54] ^ pArgDDomainWord);
    
    DispatchFullB(aOperationData[55]);
    
    DispatchUnroll(aDestination,
                   aOperationData[56] ^ pUnrollDomainWord,
                   aOperationData[57] ^ pUnrollDomainWord,
                   aOperationData[58] ^ pUnrollDomainWord,
                   aOperationData[59] ^ pUnrollDomainWord,
                   aOperationData[60] ^ pUnrollDomainWord,
                   aOperationData[61] ^ pUnrollDomainWord,
                   aOperationData[62] ^ pUnrollDomainWord,
                   aOperationData[63] ^ pUnrollDomainWord);
}

void M88::DispatchSwapsA(std::uint8_t pByteA, std::uint8_t pByteB) {
    SwapRows(pByteA, pByteA >> 4);
    SwapColumns(pByteB, pByteB >> 4);
    
}

void M88::DispatchSwapsB(std::uint8_t pByte) {
    SwapMinis(pByte, pByte >> 4);
}

void M88::DispatchUnroll(std::uint8_t *pDestination,
                          std::uint8_t pByteSwapsA,
                          std::uint8_t pByteSwapsB,
                          std::uint8_t pByteSwapsC,
                          std::uint8_t pByteSwapsD,
                          std::uint8_t pByteSwapsE,
                          std::uint8_t pByteSwapsF,
                          std::uint8_t pByteSwapsG,
                          std::uint8_t pByteSwapsH) {
    
    //
    // 1. Build the initial row order.
    //
    // mPermute[0..7] is the output row path.
    // Each value is a row index into mData.
    //
    
    mPermute[0] = 0;
    mPermute[1] = 1;
    mPermute[2] = 2;
    mPermute[3] = 3;
    mPermute[4] = 4;
    mPermute[5] = 5;
    mPermute[6] = 6;
    mPermute[7] = 7;
    
    
    //
    // 2. Shuffle the row order using 8 byte-controlled swaps.
    //
    // Each swap byte uses:
    //
    //   upper nibble bits 4..6 = first index  in mPermute[0..7]
    //   lower nibble bits 0..2 = second index in mPermute[0..7]
    //
    // Bit 7 and bit 3 are ignored.
    //
    std::uint8_t aIndexA = 0;
    std::uint8_t aIndexB = 0;
    std::uint8_t aHold = 0;

    {
        aIndexA = (pByteSwapsA >> 4U) & 0x07U;
        aIndexB = (pByteSwapsA >> 0U) & 0x07U;
        
        aHold = mPermute[aIndexA];
        mPermute[aIndexA] = mPermute[aIndexB];
        mPermute[aIndexB] = aHold;
    }

    {
        aIndexA = (pByteSwapsB >> 5U) & 0x07U;
        aIndexB = (pByteSwapsB >> 1U) & 0x07U;
        
        aHold = mPermute[aIndexA];
        mPermute[aIndexA] = mPermute[aIndexB];
        mPermute[aIndexB] = aHold;
    }

    {
        aIndexA = (pByteSwapsC >> 4U) & 0x07U;
        aIndexB = (pByteSwapsC >> 1U) & 0x07U;
        
        aHold = mPermute[aIndexA];
        mPermute[aIndexA] = mPermute[aIndexB];
        mPermute[aIndexB] = aHold;
    }

    {
        aIndexA = (pByteSwapsD >> 5U) & 0x07U;
        aIndexB = (pByteSwapsD >> 0U) & 0x07U;
        
        aHold = mPermute[aIndexA];
        mPermute[aIndexA] = mPermute[aIndexB];
        mPermute[aIndexB] = aHold;
    }

    {
        aIndexA = (pByteSwapsE >> 0U) & 0x07U;
        aIndexB = (pByteSwapsE >> 4U) & 0x07U;
        
        aHold = mPermute[aIndexA];
        mPermute[aIndexA] = mPermute[aIndexB];
        mPermute[aIndexB] = aHold;
    }

    {
        aIndexA = (pByteSwapsF >> 1U) & 0x07U;
        aIndexB = (pByteSwapsF >> 5U) & 0x07U;
        
        aHold = mPermute[aIndexA];
        mPermute[aIndexA] = mPermute[aIndexB];
        mPermute[aIndexB] = aHold;
    }

    {
        aIndexA = (pByteSwapsG >> 1U) & 0x07U;
        aIndexB = (pByteSwapsG >> 4U) & 0x07U;
        
        aHold = mPermute[aIndexA];
        mPermute[aIndexA] = mPermute[aIndexB];
        mPermute[aIndexB] = aHold;
    }

    {
        aIndexA = (pByteSwapsH >> 0U) & 0x07U;
        aIndexB = (pByteSwapsH >> 5U) & 0x07U;
        
        aHold = mPermute[aIndexA];
        mPermute[aIndexA] = mPermute[aIndexB];
        mPermute[aIndexB] = aHold;
    }
    
    
    //
    // 3. Store the rows in the shuffled order.
    //
    // Each row is 8 bytes.
    //
    
    memcpy(pDestination +  0, mData + (mPermute[0] << 3), 8);
    memcpy(pDestination +  8, mData + (mPermute[1] << 3), 8);
    memcpy(pDestination + 16, mData + (mPermute[2] << 3), 8);
    memcpy(pDestination + 24, mData + (mPermute[3] << 3), 8);
    memcpy(pDestination + 32, mData + (mPermute[4] << 3), 8);
    memcpy(pDestination + 40, mData + (mPermute[5] << 3), 8);
    memcpy(pDestination + 48, mData + (mPermute[6] << 3), 8);
    memcpy(pDestination + 56, mData + (mPermute[7] << 3), 8);
}
void M88::DispatchMini(std::uint8_t pByte) {
    
    
}

void M88::DispatchQuadA(std::uint8_t pByte) {
    
    
}

void M88::DispatchQuadB(std::uint8_t pByte) {
    
    
}

void M88::DispatchQuadC(std::uint8_t pByte) {
    
    
}

void M88::DispatchQuadD(std::uint8_t pByte) {
    
    
}

void M88::DispatchFullA(std::uint8_t pByte) {
    
    
}

void M88::DispatchFullB(std::uint8_t pByte) {
    
    
}

void M88::DispatchPermute(std::uint8_t pByteSelect_QuadA_A,
                           std::uint8_t pByteSelect_QuadA_B,
                           std::uint8_t pByteSelect_QuadB_A,
                           std::uint8_t pByteSelect_QuadB_B,
                           std::uint8_t pByteSelect_QuadC_A,
                           std::uint8_t pByteSelect_QuadC_B,
                           std::uint8_t pByteSelect_QuadD_A,
                           std::uint8_t pByteSelect_QuadD_B,
                           
                           std::uint8_t pByteSwapsA,
                           std::uint8_t pByteSwapsB,
                           std::uint8_t pByteSwapsC,
                           std::uint8_t pByteSwapsD,
                           std::uint8_t pByteSwapsE,
                           std::uint8_t pByteSwapsF,
                           std::uint8_t pByteSwapsG,
                           std::uint8_t pByteSwapsH,
                           
                          std::uint8_t pByteAmount) {
    
    std::uint8_t aAmount = pByteAmount & 0x0FU;
    
    if (aAmount == 0) {
        return;
    }
    
    const std::uint8_t *aPickA = M88QuadSelectsA::Pick4(pByteSelect_QuadA_A, pByteSelect_QuadA_B);
    const std::uint8_t *aPickB = M88QuadSelectsB::Pick4(pByteSelect_QuadB_A, pByteSelect_QuadB_B);
    const std::uint8_t *aPickC = M88QuadSelectsC::Pick4(pByteSelect_QuadC_A, pByteSelect_QuadC_B);
    const std::uint8_t *aPickD = M88QuadSelectsD::Pick4(pByteSelect_QuadD_A, pByteSelect_QuadD_B);
    
    mPermute[0]  = aPickA[0]; mPermute[1]  = aPickA[1]; mPermute[2]  = aPickA[2]; mPermute[3]  = aPickA[3];
    mPermute[4]  = aPickB[0]; mPermute[5]  = aPickB[1]; mPermute[6]  = aPickB[2]; mPermute[7]  = aPickB[3];
    mPermute[8]  = aPickC[0]; mPermute[9]  = aPickC[1]; mPermute[10] = aPickC[2]; mPermute[11] = aPickC[3];
    mPermute[12] = aPickD[0]; mPermute[13] = aPickD[1]; mPermute[14] = aPickD[2]; mPermute[15] = aPickD[3];
    
    std::uint8_t aIndexA = 0; std::uint8_t aIndexB = 0; std::uint8_t aHold = 0;
    
    aIndexA = (pByteSwapsA >> 4U) & 0x0FU;
    aIndexB = (pByteSwapsA >> 0U) & 0x0FU;
    aHold = mPermute[aIndexA];
    mPermute[aIndexA] = mPermute[aIndexB];
    mPermute[aIndexB] = aHold;
    
    aIndexA = (pByteSwapsB >> 4U) & 0x0FU;
    aIndexB = (pByteSwapsB >> 0U) & 0x0FU;
    aHold = mPermute[aIndexA];
    mPermute[aIndexA] = mPermute[aIndexB];
    mPermute[aIndexB] = aHold;
    
    aIndexA = (pByteSwapsC >> 4U) & 0x0FU;
    aIndexB = (pByteSwapsC >> 0U) & 0x0FU;
    aHold = mPermute[aIndexA];
    mPermute[aIndexA] = mPermute[aIndexB];
    mPermute[aIndexB] = aHold;
    
    aIndexA = (pByteSwapsD >> 4U) & 0x0FU;
    aIndexB = (pByteSwapsD >> 0U) & 0x0FU;
    aHold = mPermute[aIndexA];
    mPermute[aIndexA] = mPermute[aIndexB];
    mPermute[aIndexB] = aHold;
    
    aIndexA = (pByteSwapsE >> 4U) & 0x0FU;
    aIndexB = (pByteSwapsE >> 0U) & 0x0FU;
    aHold = mPermute[aIndexA];
    mPermute[aIndexA] = mPermute[aIndexB];
    mPermute[aIndexB] = aHold;
    
    aIndexA = (pByteSwapsF >> 4U) & 0x0FU;
    aIndexB = (pByteSwapsF >> 0U) & 0x0FU;
    aHold = mPermute[aIndexA];
    mPermute[aIndexA] = mPermute[aIndexB];
    mPermute[aIndexB] = aHold;
    
    aIndexA = (pByteSwapsG >> 4U) & 0x0FU;
    aIndexB = (pByteSwapsG >> 0U) & 0x0FU;
    aHold = mPermute[aIndexA];
    mPermute[aIndexA] = mPermute[aIndexB];
    mPermute[aIndexB] = aHold;
    
    aIndexA = (pByteSwapsH >> 4U) & 0x0FU;
    aIndexB = (pByteSwapsH >> 0U) & 0x0FU;
    aHold = mPermute[aIndexA];
    mPermute[aIndexA] = mPermute[aIndexB];
    mPermute[aIndexB] = aHold;
    
    
    
    
    mPermuteTemp[0]  = mPermute[(0  + 16 - aAmount) & 0x0F];
    mPermuteTemp[1]  = mPermute[(1  + 16 - aAmount) & 0x0F];
    mPermuteTemp[2]  = mPermute[(2  + 16 - aAmount) & 0x0F];
    mPermuteTemp[3]  = mPermute[(3  + 16 - aAmount) & 0x0F];
    mPermuteTemp[4]  = mPermute[(4  + 16 - aAmount) & 0x0F];
    mPermuteTemp[5]  = mPermute[(5  + 16 - aAmount) & 0x0F];
    mPermuteTemp[6]  = mPermute[(6  + 16 - aAmount) & 0x0F];
    mPermuteTemp[7]  = mPermute[(7  + 16 - aAmount) & 0x0F];
    mPermuteTemp[8]  = mPermute[(8  + 16 - aAmount) & 0x0F];
    mPermuteTemp[9]  = mPermute[(9  + 16 - aAmount) & 0x0F];
    mPermuteTemp[10] = mPermute[(10 + 16 - aAmount) & 0x0F];
    mPermuteTemp[11] = mPermute[(11 + 16 - aAmount) & 0x0F];
    mPermuteTemp[12] = mPermute[(12 + 16 - aAmount) & 0x0F];
    mPermuteTemp[13] = mPermute[(13 + 16 - aAmount) & 0x0F];
    mPermuteTemp[14] = mPermute[(14 + 16 - aAmount) & 0x0F];
    mPermuteTemp[15] = mPermute[(15 + 16 - aAmount) & 0x0F];
    
    mPermuteData[0]  = mData[mPermuteTemp[0]];
    mPermuteData[1]  = mData[mPermuteTemp[1]];
    mPermuteData[2]  = mData[mPermuteTemp[2]];
    mPermuteData[3]  = mData[mPermuteTemp[3]];
    mPermuteData[4]  = mData[mPermuteTemp[4]];
    mPermuteData[5]  = mData[mPermuteTemp[5]];
    mPermuteData[6]  = mData[mPermuteTemp[6]];
    mPermuteData[7]  = mData[mPermuteTemp[7]];
    mPermuteData[8]  = mData[mPermuteTemp[8]];
    mPermuteData[9]  = mData[mPermuteTemp[9]];
    mPermuteData[10] = mData[mPermuteTemp[10]];
    mPermuteData[11] = mData[mPermuteTemp[11]];
    mPermuteData[12] = mData[mPermuteTemp[12]];
    mPermuteData[13] = mData[mPermuteTemp[13]];
    mPermuteData[14] = mData[mPermuteTemp[14]];
    mPermuteData[15] = mData[mPermuteTemp[15]];
    
    mData[mPermute[0]]  = mPermuteData[0];
    mData[mPermute[1]]  = mPermuteData[1];
    mData[mPermute[2]]  = mPermuteData[2];
    mData[mPermute[3]]  = mPermuteData[3];
    mData[mPermute[4]]  = mPermuteData[4];
    mData[mPermute[5]]  = mPermuteData[5];
    mData[mPermute[6]]  = mPermuteData[6];
    mData[mPermute[7]]  = mPermuteData[7];
    mData[mPermute[8]]  = mPermuteData[8];
    mData[mPermute[9]]  = mPermuteData[9];
    mData[mPermute[10]] = mPermuteData[10];
    mData[mPermute[11]] = mPermuteData[11];
    mData[mPermute[12]] = mPermuteData[12];
    mData[mPermute[13]] = mPermuteData[13];
    mData[mPermute[14]] = mPermuteData[14];
    mData[mPermute[15]] = mPermuteData[15];
}

void M88::SwapRows(std::uint8_t pRowA, std::uint8_t pRowB) {

    std::uint8_t aRowA = (pRowA & 7U) << 3U;
    std::uint8_t aRowB = (pRowB & 7U) << 3U;

    if (aRowA == aRowB) { return; }

    std::uint8_t aHold = 0;

    aHold = mData[aRowA + 0U];
    mData[aRowA + 0U] = mData[aRowB + 0U];
    mData[aRowB + 0U] = aHold;

    aHold = mData[aRowA + 1U];
    mData[aRowA + 1U] = mData[aRowB + 1U];
    mData[aRowB + 1U] = aHold;

    aHold = mData[aRowA + 2U];
    mData[aRowA + 2U] = mData[aRowB + 2U];
    mData[aRowB + 2U] = aHold;

    aHold = mData[aRowA + 3U];
    mData[aRowA + 3U] = mData[aRowB + 3U];
    mData[aRowB + 3U] = aHold;

    aHold = mData[aRowA + 4U];
    mData[aRowA + 4U] = mData[aRowB + 4U];
    mData[aRowB + 4U] = aHold;

    aHold = mData[aRowA + 5U];
    mData[aRowA + 5U] = mData[aRowB + 5U];
    mData[aRowB + 5U] = aHold;

    aHold = mData[aRowA + 6U];
    mData[aRowA + 6U] = mData[aRowB + 6U];
    mData[aRowB + 6U] = aHold;

    aHold = mData[aRowA + 7U];
    mData[aRowA + 7U] = mData[aRowB + 7U];
    mData[aRowB + 7U] = aHold;
}

void M88::SwapColumns(std::uint8_t pColA, std::uint8_t pColB) {

    std::uint8_t aColA = pColA & 7;
    std::uint8_t aColB = pColB & 7;

    if (aColA == aColB) { return; }

    std::uint8_t aHold;

    for (std::uint8_t aRowIndex = 0; aRowIndex < 8; ++aRowIndex) {

        std::uint8_t aBase = aRowIndex << 3;

        aHold = mData[aBase + aColA];
        mData[aBase + aColA] = mData[aBase + aColB];
        mData[aBase + aColB] = aHold;
    }
}

void M88::SwapMinis(std::uint8_t pBlockA, std::uint8_t pBlockB) {

    std::uint8_t aBlockA = pBlockA & 15;
    std::uint8_t aBlockB = pBlockB & 15;

    if (aBlockA == aBlockB) { return; }

    // decode A
    std::uint8_t aRowA = (aBlockA >> 2) << 1;
    std::uint8_t aColA = (aBlockA & 3) << 1;

    // decode B
    std::uint8_t aRowB = (aBlockB >> 2) << 1;
    std::uint8_t aColB = (aBlockB & 3) << 1;

    std::uint8_t aBaseaByte0 = (aRowA + 0) << 3;
    std::uint8_t aBaseaByte1 = (aRowA + 1) << 3;

    std::uint8_t aBaseB0 = (aRowB + 0) << 3;
    std::uint8_t aBaseB1 = (aRowB + 1) << 3;

    std::uint8_t aHold;

    // (0,0)
    aHold = mData[aBaseaByte0 + aColA + 0];
    mData[aBaseaByte0 + aColA + 0] = mData[aBaseB0 + aColB + 0];
    mData[aBaseB0 + aColB + 0] = aHold;

    // (0,1)
    aHold = mData[aBaseaByte0 + aColA + 1];
    mData[aBaseaByte0 + aColA + 1] = mData[aBaseB0 + aColB + 1];
    mData[aBaseB0 + aColB + 1] = aHold;

    // (1,0)
    aHold = mData[aBaseaByte1 + aColA + 0];
    mData[aBaseaByte1 + aColA + 0] = mData[aBaseB1 + aColB + 0];
    mData[aBaseB1 + aColB + 0] = aHold;

    // (1,1)
    aHold = mData[aBaseaByte1 + aColA + 1];
    mData[aBaseaByte1 + aColA + 1] = mData[aBaseB1 + aColB + 1];
    mData[aBaseB1 + aColB + 1] = aHold;
}
