//
//  TwistMix161.cpp
//  MeanMachine
//
//  Created by Dragon on 4/28/26.
//

#include "TwistMix16.hpp"

std::uint16_t TwistMix16::Mix161_000(const std::uint16_t pValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
std::uint16_t TwistMix16::Mix161_001(const std::uint16_t pValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= static_cast<std::uint8_t>(((aTemp << 1U) | (aTemp >> 7U)));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
std::uint16_t TwistMix16::Mix161_002(const std::uint16_t pValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
std::uint16_t TwistMix16::Mix161_003(const std::uint16_t pValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= static_cast<std::uint8_t>(((aTemp << 1U) | (aTemp >> 7U)));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix161_004(const std::uint16_t pValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix161_005(const std::uint16_t pValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix161_006(const std::uint16_t pValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBox[(aOracleA + aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix161_007(const std::uint16_t pValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBox[(aOracleA + aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}



std::uint16_t TwistMix16::Mix162_000(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_001(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_002(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


std::uint16_t TwistMix16::Mix162_003(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_004(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 2U) | (aByteA >> 6U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_005(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 2U) | (aByteA >> 6U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_006(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 2U) | (aByteA >> 6U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_007(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 2U) | (aByteA >> 6U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_008(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_009(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_010(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_011(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_012(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_013(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_014(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix162_015(const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = pValue & 0xFFU;
    std::uint8_t aByteB = (pValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

std::uint16_t TwistMix16::Mix161(const Mix161Type pType,
                                        const std::uint16_t pValue,
                                        const std::uint8_t *pSBox) {
    switch (pType) {
        case Mix161Type::kMix161_000: return Mix161_000(pValue, pSBox);
        case Mix161Type::kMix161_001: return Mix161_001(pValue, pSBox);
        case Mix161Type::kMix161_002: return Mix161_002(pValue, pSBox);
        case Mix161Type::kMix161_003: return Mix161_003(pValue, pSBox);
        case Mix161Type::kMix161_004: return Mix161_004(pValue, pSBox);
        case Mix161Type::kMix161_005: return Mix161_005(pValue, pSBox);
        case Mix161Type::kMix161_006: return Mix161_006(pValue, pSBox);
        case Mix161Type::kMix161_007: return Mix161_007(pValue, pSBox);
        default:
            return pValue;
    }
}

std::uint16_t TwistMix16::Mix162(const Mix162Type pType,
                                        const std::uint16_t pValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    switch (pType) {
        case Mix162Type::kMix162_000: return Mix162_000(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_001: return Mix162_001(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_002: return Mix162_002(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_003: return Mix162_003(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_004: return Mix162_004(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_005: return Mix162_005(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_006: return Mix162_006(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_007: return Mix162_007(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_008: return Mix162_008(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_009: return Mix162_009(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_010: return Mix162_010(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_011: return Mix162_011(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_012: return Mix162_012(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_013: return Mix162_013(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_014: return Mix162_014(pValue, pSBoxA, pSBoxB);
        case Mix162Type::kMix162_015: return Mix162_015(pValue, pSBoxA, pSBoxB);
        default:
            return pValue;
    }
}
