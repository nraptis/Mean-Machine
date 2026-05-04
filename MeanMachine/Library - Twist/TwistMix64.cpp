//
//  TwistMix64.cpp
//  MeanMachine
//
//  Created by Dragon on 5/1/26.
//

#include "TwistMix64.hpp"

std::vector<Mix64Type_1> TwistMix64::GetAll_1() {
    return {
        Mix64Type_1::kGatePrism_1_8,
        Mix64Type_1::kGateRoll_1_1,
        Mix64Type_1::kGateRoll_1_4,
        Mix64Type_1::kGateRoll_1_8,
        Mix64Type_1::kGateTurn_1_1,
        Mix64Type_1::kGateTurn_1_4,
        Mix64Type_1::kGateTurn_1_8
    };
}

std::vector<Mix64Type_4> TwistMix64::GetAll_4() {
    return {
        Mix64Type_4::kGatePrismA_4_8,
        Mix64Type_4::kGatePrismB_4_8,
        Mix64Type_4::kGatePrismC_4_8,
        Mix64Type_4::kGateRoll_4_4,
        Mix64Type_4::kGateRollA_4_8,
        Mix64Type_4::kGateRollB_4_8,
        Mix64Type_4::kGateRollC_4_8,
        Mix64Type_4::kGateTurn_4_4,
        Mix64Type_4::kGateTurnA_4_8,
        Mix64Type_4::kGateTurnB_4_8,
        Mix64Type_4::kGateTurnC_4_8
    };
}

std::vector<Mix64Type_8> TwistMix64::GetAll_8() {
    return {
        Mix64Type_8::kGatePrism_8_8,
        Mix64Type_8::kGateRoll_8_8,
        Mix64Type_8::kGateTurn_8_8
    };
}

std::uint64_t TwistMix64::GatePrism_1_1(const std::uint64_t pValue,
                                        const std::uint8_t* pSBoxA) {
    std::uint8_t aByte0 = pValue;

    aByte0 = pSBoxA[aByte0];

    return (pValue & 0xFFFFFFFFFFFFFF00ULL)
         |  static_cast<std::uint64_t>(aByte0);
}

std::uint64_t TwistMix64::GatePrism_1_4(const std::uint64_t pValue,
                                        const std::uint8_t* pSBoxA) {
    std::uint8_t aByte0 = pValue;
    std::uint8_t aByte1 = pValue >> 8U;
    std::uint8_t aByte2 = pValue >> 16U;
    std::uint8_t aByte3 = pValue >> 24U;

    aByte0 = pSBoxA[aByte0];
    aByte1 = pSBoxA[aByte1];
    aByte2 = pSBoxA[aByte2];
    aByte3 = pSBoxA[aByte3];

    return (pValue & 0xFFFFFFFF00000000ULL)
         |  static_cast<std::uint64_t>(aByte0)
         | (static_cast<std::uint64_t>(aByte1) <<  8U)
         | (static_cast<std::uint64_t>(aByte2) << 16U)
         | (static_cast<std::uint64_t>(aByte3) << 24U);
}

std::uint64_t TwistMix64::GatePrism_1_8(const std::uint64_t pValue,
                                        const std::uint8_t* pSBoxA) {
    std::uint8_t aByte0 = pValue;
    std::uint8_t aByte1 = pValue >> 8U;
    std::uint8_t aByte2 = pValue >> 16U;
    std::uint8_t aByte3 = pValue >> 24U;
    std::uint8_t aByte4 = pValue >> 32U;
    std::uint8_t aByte5 = pValue >> 40U;
    std::uint8_t aByte6 = pValue >> 48U;
    std::uint8_t aByte7 = pValue >> 56U;

    aByte0 = pSBoxA[aByte0];
    aByte1 = pSBoxA[aByte1];
    aByte2 = pSBoxA[aByte2];
    aByte3 = pSBoxA[aByte3];
    aByte4 = pSBoxA[aByte4];
    aByte5 = pSBoxA[aByte5];
    aByte6 = pSBoxA[aByte6];
    aByte7 = pSBoxA[aByte7];

    return  static_cast<std::uint64_t>(aByte0)
          | (static_cast<std::uint64_t>(aByte1) <<  8U)
          | (static_cast<std::uint64_t>(aByte2) << 16U)
          | (static_cast<std::uint64_t>(aByte3) << 24U)
          | (static_cast<std::uint64_t>(aByte4) << 32U)
          | (static_cast<std::uint64_t>(aByte5) << 40U)
          | (static_cast<std::uint64_t>(aByte6) << 48U)
          | (static_cast<std::uint64_t>(aByte7) << 56U);
}

std::uint64_t TwistMix64::GatePrism_4_4(const std::uint64_t pValue,
                                        const std::uint8_t* pSBoxA,
                                        const std::uint8_t* pSBoxB,
                                        const std::uint8_t* pSBoxC,
                                        const std::uint8_t* pSBoxD) {
    std::uint8_t aByte0 = pValue;
    std::uint8_t aByte1 = pValue >> 8U;
    std::uint8_t aByte2 = pValue >> 16U;
    std::uint8_t aByte3 = pValue >> 24U;

    aByte0 = pSBoxA[aByte0];
    aByte1 = pSBoxB[aByte1];
    aByte2 = pSBoxC[aByte2];
    aByte3 = pSBoxD[aByte3];

    return (pValue & 0xFFFFFFFF00000000ULL)
         |  static_cast<std::uint64_t>(aByte0)
         | (static_cast<std::uint64_t>(aByte1) <<  8U)
         | (static_cast<std::uint64_t>(aByte2) << 16U)
         | (static_cast<std::uint64_t>(aByte3) << 24U);
}

std::uint64_t TwistMix64::GatePrismA_4_8(const std::uint64_t pValue,
                                         const std::uint8_t* pSBoxA,
                                         const std::uint8_t* pSBoxB,
                                         const std::uint8_t* pSBoxC,
                                         const std::uint8_t* pSBoxD) {
    std::uint8_t aByte0 = pValue;
    std::uint8_t aByte1 = pValue >> 8U;
    std::uint8_t aByte2 = pValue >> 16U;
    std::uint8_t aByte3 = pValue >> 24U;
    std::uint8_t aByte4 = pValue >> 32U;
    std::uint8_t aByte5 = pValue >> 40U;
    std::uint8_t aByte6 = pValue >> 48U;
    std::uint8_t aByte7 = pValue >> 56U;

    // [aabbccdd]
    aByte0 = pSBoxA[aByte0];
    aByte1 = pSBoxA[aByte1];
    aByte2 = pSBoxB[aByte2];
    aByte3 = pSBoxB[aByte3];
    aByte4 = pSBoxC[aByte4];
    aByte5 = pSBoxC[aByte5];
    aByte6 = pSBoxD[aByte6];
    aByte7 = pSBoxD[aByte7];

    return  static_cast<std::uint64_t>(aByte0)
          | (static_cast<std::uint64_t>(aByte1) <<  8U)
          | (static_cast<std::uint64_t>(aByte2) << 16U)
          | (static_cast<std::uint64_t>(aByte3) << 24U)
          | (static_cast<std::uint64_t>(aByte4) << 32U)
          | (static_cast<std::uint64_t>(aByte5) << 40U)
          | (static_cast<std::uint64_t>(aByte6) << 48U)
          | (static_cast<std::uint64_t>(aByte7) << 56U);
}

std::uint64_t TwistMix64::GatePrismB_4_8(const std::uint64_t pValue,
                                         const std::uint8_t* pSBoxA,
                                         const std::uint8_t* pSBoxB,
                                         const std::uint8_t* pSBoxC,
                                         const std::uint8_t* pSBoxD) {
    std::uint8_t aByte0 = pValue;
    std::uint8_t aByte1 = pValue >> 8U;
    std::uint8_t aByte2 = pValue >> 16U;
    std::uint8_t aByte3 = pValue >> 24U;
    std::uint8_t aByte4 = pValue >> 32U;
    std::uint8_t aByte5 = pValue >> 40U;
    std::uint8_t aByte6 = pValue >> 48U;
    std::uint8_t aByte7 = pValue >> 56U;

    // [abcdabcd]
    aByte0 = pSBoxA[aByte0];
    aByte1 = pSBoxB[aByte1];
    aByte2 = pSBoxC[aByte2];
    aByte3 = pSBoxD[aByte3];
    aByte4 = pSBoxA[aByte4];
    aByte5 = pSBoxB[aByte5];
    aByte6 = pSBoxC[aByte6];
    aByte7 = pSBoxD[aByte7];

    return  static_cast<std::uint64_t>(aByte0)
          | (static_cast<std::uint64_t>(aByte1) <<  8U)
          | (static_cast<std::uint64_t>(aByte2) << 16U)
          | (static_cast<std::uint64_t>(aByte3) << 24U)
          | (static_cast<std::uint64_t>(aByte4) << 32U)
          | (static_cast<std::uint64_t>(aByte5) << 40U)
          | (static_cast<std::uint64_t>(aByte6) << 48U)
          | (static_cast<std::uint64_t>(aByte7) << 56U);
}

std::uint64_t TwistMix64::GatePrismC_4_8(const std::uint64_t pValue,
                                         const std::uint8_t* pSBoxA,
                                         const std::uint8_t* pSBoxB,
                                         const std::uint8_t* pSBoxC,
                                         const std::uint8_t* pSBoxD) {
    std::uint8_t aByte0 = pValue;
    std::uint8_t aByte1 = pValue >> 8U;
    std::uint8_t aByte2 = pValue >> 16U;
    std::uint8_t aByte3 = pValue >> 24U;
    std::uint8_t aByte4 = pValue >> 32U;
    std::uint8_t aByte5 = pValue >> 40U;
    std::uint8_t aByte6 = pValue >> 48U;
    std::uint8_t aByte7 = pValue >> 56U;

    // [abcddcba]
    aByte0 = pSBoxA[aByte0];
    aByte1 = pSBoxB[aByte1];
    aByte2 = pSBoxC[aByte2];
    aByte3 = pSBoxD[aByte3];
    aByte4 = pSBoxD[aByte4];
    aByte5 = pSBoxC[aByte5];
    aByte6 = pSBoxB[aByte6];
    aByte7 = pSBoxA[aByte7];

    return  static_cast<std::uint64_t>(aByte0)
          | (static_cast<std::uint64_t>(aByte1) <<  8U)
          | (static_cast<std::uint64_t>(aByte2) << 16U)
          | (static_cast<std::uint64_t>(aByte3) << 24U)
          | (static_cast<std::uint64_t>(aByte4) << 32U)
          | (static_cast<std::uint64_t>(aByte5) << 40U)
          | (static_cast<std::uint64_t>(aByte6) << 48U)
          | (static_cast<std::uint64_t>(aByte7) << 56U);
}

std::uint64_t TwistMix64::GatePrism_8_8(const std::uint64_t pValue,
                                        const std::uint8_t* pSBoxA,
                                        const std::uint8_t* pSBoxB,
                                        const std::uint8_t* pSBoxC,
                                        const std::uint8_t* pSBoxD,
                                        const std::uint8_t* pSBoxE,
                                        const std::uint8_t* pSBoxF,
                                        const std::uint8_t* pSBoxG,
                                        const std::uint8_t* pSBoxH) {
    std::uint8_t aByte0 = pValue;
    std::uint8_t aByte1 = pValue >> 8U;
    std::uint8_t aByte2 = pValue >> 16U;
    std::uint8_t aByte3 = pValue >> 24U;
    std::uint8_t aByte4 = pValue >> 32U;
    std::uint8_t aByte5 = pValue >> 40U;
    std::uint8_t aByte6 = pValue >> 48U;
    std::uint8_t aByte7 = pValue >> 56U;

    aByte0 = pSBoxA[aByte0];
    aByte1 = pSBoxB[aByte1];
    aByte2 = pSBoxC[aByte2];
    aByte3 = pSBoxD[aByte3];
    aByte4 = pSBoxE[aByte4];
    aByte5 = pSBoxF[aByte5];
    aByte6 = pSBoxG[aByte6];
    aByte7 = pSBoxH[aByte7];

    return  static_cast<std::uint64_t>(aByte0)
          | (static_cast<std::uint64_t>(aByte1) <<  8U)
          | (static_cast<std::uint64_t>(aByte2) << 16U)
          | (static_cast<std::uint64_t>(aByte3) << 24U)
          | (static_cast<std::uint64_t>(aByte4) << 32U)
          | (static_cast<std::uint64_t>(aByte5) << 40U)
          | (static_cast<std::uint64_t>(aByte6) << 48U)
          | (static_cast<std::uint64_t>(aByte7) << 56U);
}

std::uint64_t TwistMix64::GateRoll_1_1(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA) {
    return GatePrism_1_1(pValue, pSBoxA)
         ^ RotL64(pValue, pAmount);
}

std::uint64_t TwistMix64::GateRoll_1_4(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA) {
    return GatePrism_1_4(pValue, pSBoxA)
         ^ RotL64(pValue, pAmount);
}

std::uint64_t TwistMix64::GateRoll_1_8(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA) {
    return GatePrism_1_8(pValue, pSBoxA)
         ^ RotL64(pValue, pAmount);
}

std::uint64_t TwistMix64::GateTurn_1_1(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA) {
    return GatePrism_1_1(RotL64(pValue, pAmount), pSBoxA);
}

std::uint64_t TwistMix64::GateTurn_1_4(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA) {
    return GatePrism_1_4(RotL64(pValue, pAmount), pSBoxA);
}

std::uint64_t TwistMix64::GateTurn_1_8(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA) {
    return GatePrism_1_8(RotL64(pValue, pAmount), pSBoxA);
}

std::uint64_t TwistMix64::GateRoll_4_4(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA,
                                       const std::uint8_t* pSBoxB,
                                       const std::uint8_t* pSBoxC,
                                       const std::uint8_t* pSBoxD) {
    return GatePrism_4_4(pValue, pSBoxA, pSBoxB, pSBoxC, pSBoxD)
         ^ RotL64(pValue, pAmount);
}

std::uint64_t TwistMix64::GateRollA_4_8(const std::uint64_t pValue,
                                        const std::uint64_t pAmount,
                                        const std::uint8_t* pSBoxA,
                                        const std::uint8_t* pSBoxB,
                                        const std::uint8_t* pSBoxC,
                                        const std::uint8_t* pSBoxD) {
    return GatePrismA_4_8(pValue, pSBoxA, pSBoxB, pSBoxC, pSBoxD)
         ^ RotL64(pValue, pAmount);
}

std::uint64_t TwistMix64::GateRollB_4_8(const std::uint64_t pValue,
                                        const std::uint64_t pAmount,
                                        const std::uint8_t* pSBoxA,
                                        const std::uint8_t* pSBoxB,
                                        const std::uint8_t* pSBoxC,
                                        const std::uint8_t* pSBoxD) {
    return GatePrismB_4_8(pValue, pSBoxA, pSBoxB, pSBoxC, pSBoxD)
         ^ RotL64(pValue, pAmount);
}

std::uint64_t TwistMix64::GateRollC_4_8(const std::uint64_t pValue,
                                        const std::uint64_t pAmount,
                                        const std::uint8_t* pSBoxA,
                                        const std::uint8_t* pSBoxB,
                                        const std::uint8_t* pSBoxC,
                                        const std::uint8_t* pSBoxD) {
    return GatePrismC_4_8(pValue, pSBoxA, pSBoxB, pSBoxC, pSBoxD)
         ^ RotL64(pValue, pAmount);
}

std::uint64_t TwistMix64::GateTurn_4_4(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA,
                                       const std::uint8_t* pSBoxB,
                                       const std::uint8_t* pSBoxC,
                                       const std::uint8_t* pSBoxD) {
    return GatePrism_4_4(RotL64(pValue, pAmount),
                         pSBoxA,
                         pSBoxB,
                         pSBoxC,
                         pSBoxD);
}

std::uint64_t TwistMix64::GateTurnA_4_8(const std::uint64_t pValue,
                                        const std::uint64_t pAmount,
                                        const std::uint8_t* pSBoxA,
                                        const std::uint8_t* pSBoxB,
                                        const std::uint8_t* pSBoxC,
                                        const std::uint8_t* pSBoxD) {
    return GatePrismA_4_8(RotL64(pValue, pAmount),
                          pSBoxA,
                          pSBoxB,
                          pSBoxC,
                          pSBoxD);
}

std::uint64_t TwistMix64::GateTurnB_4_8(const std::uint64_t pValue,
                                        const std::uint64_t pAmount,
                                        const std::uint8_t* pSBoxA,
                                        const std::uint8_t* pSBoxB,
                                        const std::uint8_t* pSBoxC,
                                        const std::uint8_t* pSBoxD) {
    return GatePrismB_4_8(RotL64(pValue, pAmount),
                          pSBoxA,
                          pSBoxB,
                          pSBoxC,
                          pSBoxD);
}

std::uint64_t TwistMix64::GateTurnC_4_8(const std::uint64_t pValue,
                                        const std::uint64_t pAmount,
                                        const std::uint8_t* pSBoxA,
                                        const std::uint8_t* pSBoxB,
                                        const std::uint8_t* pSBoxC,
                                        const std::uint8_t* pSBoxD) {
    return GatePrismC_4_8(RotL64(pValue, pAmount),
                          pSBoxA,
                          pSBoxB,
                          pSBoxC,
                          pSBoxD);
}

std::uint64_t TwistMix64::GateRoll_8_8(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA,
                                       const std::uint8_t* pSBoxB,
                                       const std::uint8_t* pSBoxC,
                                       const std::uint8_t* pSBoxD,
                                       const std::uint8_t* pSBoxE,
                                       const std::uint8_t* pSBoxF,
                                       const std::uint8_t* pSBoxG,
                                       const std::uint8_t* pSBoxH) {
    return GatePrism_8_8(pValue,
                         pSBoxA,
                         pSBoxB,
                         pSBoxC,
                         pSBoxD,
                         pSBoxE,
                         pSBoxF,
                         pSBoxG,
                         pSBoxH)
         ^ RotL64(pValue, pAmount);
}

std::uint64_t TwistMix64::GateTurn_8_8(const std::uint64_t pValue,
                                       const std::uint64_t pAmount,
                                       const std::uint8_t* pSBoxA,
                                       const std::uint8_t* pSBoxB,
                                       const std::uint8_t* pSBoxC,
                                       const std::uint8_t* pSBoxD,
                                       const std::uint8_t* pSBoxE,
                                       const std::uint8_t* pSBoxF,
                                       const std::uint8_t* pSBoxG,
                                       const std::uint8_t* pSBoxH) {
    return GatePrism_8_8(RotL64(pValue, pAmount),
                         pSBoxA,
                         pSBoxB,
                         pSBoxC,
                         pSBoxD,
                         pSBoxE,
                         pSBoxF,
                         pSBoxG,
                         pSBoxH);
}

std::uint64_t TwistMix64::DiffuseA(std::uint64_t pValue) {
    pValue ^= (pValue >> 30);
    pValue *= 0xBF58476D1CE4E5B9ULL;
    pValue ^= (pValue >> 27);
    pValue *= 0x94D049BB133111EBULL;
    pValue ^= (pValue >> 31);
    return pValue;
}

std::uint64_t TwistMix64::DiffuseB(std::uint64_t pValue) {
    pValue ^= pValue >> 33;
    pValue *= 0xFF51AFD7ED558CCDULL;
    pValue ^= pValue >> 33;
    pValue *= 0xC4CEB9FE1A85EC53ULL;
    pValue ^= pValue >> 33;
    return pValue;
}

std::uint64_t TwistMix64::DiffuseC(std::uint64_t pValue) {
    pValue ^= pValue >> 33;
    pValue *= 0x62A9D9ED799705F5ULL;
    pValue ^= pValue >> 28;
    pValue *= 0xCB24D0A5C88C35B3ULL;
    pValue ^= pValue >> 32;
    return pValue;
}
