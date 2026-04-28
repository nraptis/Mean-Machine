//
//  TwistMix161.cpp
//  MeanMachine
//
//  Created by Dragon on 4/28/26.
//

#include "TwistMix16.hpp"



inline std::uint16_t TwistMix16::Mix161_000(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
inline std::uint16_t TwistMix16::Mix161_001(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= static_cast<std::uint8_t>(((aTemp << 1U) | (aTemp >> 7U)));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
inline std::uint16_t TwistMix16::Mix161_002(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
inline std::uint16_t TwistMix16::Mix161_003(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= static_cast<std::uint8_t>(((aTemp << 1U) | (aTemp >> 7U)));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
inline std::uint16_t TwistMix16::Mix161_004(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA + aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
inline std::uint16_t TwistMix16::Mix161_005(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA + aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= static_cast<std::uint8_t>(((aTemp << 1U) | (aTemp >> 7U)));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
inline std::uint16_t TwistMix16::Mix161_006(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA + aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
inline std::uint16_t TwistMix16::Mix161_007(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBox[(aOracleA + aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= static_cast<std::uint8_t>(((aTemp << 1U) | (aTemp >> 7U)));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}
inline std::uint16_t TwistMix16::Mix161_008(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

inline std::uint16_t TwistMix16::Mix161_009(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBox[(aOracleA ^ aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

inline std::uint16_t TwistMix16::Mix161_010(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBox[(aOracleA + aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}

inline std::uint16_t TwistMix16::Mix161_011(const std::uint16_t aValue,
                                        const std::uint8_t *pSBox) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBox[(aOracleA + aOracleB) & 0xFFU];
    aTemp = static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)));
    aByteB ^= aTemp;
    aByteA ^= aTemp;

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}




inline std::uint16_t TwistMix16::Mix162_000(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB + aTemp) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_001(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB + aTemp) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_002(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_003(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_004(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_005(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 2U) | (aByteB >> 6U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}




inline std::uint16_t TwistMix16::Mix162_006(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 2U) | (aByteA >> 6U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_007(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 2U) | (aByteA >> 6U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_008(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 2U) | (aByteA >> 6U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_009(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 2U) | (aByteA >> 6U)));
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}



inline std::uint16_t TwistMix16::Mix162_010(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB + aTemp) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_011(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB + aTemp) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_012(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_013(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_014(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_015(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = static_cast<std::uint8_t>(((aByteA << 1U) | (aByteA >> 7U)));
    std::uint8_t aOracleB = aByteB;

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_016(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_017(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 3U) | (aTemp >> 5U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_018(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 3U) | (aByteB >> 5U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


inline std::uint16_t TwistMix16::Mix162_019(const std::uint16_t aValue,
                                        const std::uint8_t *pSBoxA,
                                        const std::uint8_t *pSBoxB) {
    std::uint8_t aByteA = aValue & 0xFFU;
    std::uint8_t aByteB = (aValue >> 8U) & 0xFFU;

    std::uint8_t aOracleA = aByteA;
    std::uint8_t aOracleB = static_cast<std::uint8_t>(((aByteB << 1U) | (aByteB >> 7U)));

    std::uint8_t aTemp = pSBoxA[(aOracleA ^ aOracleB) & 0xFFU];
    aByteB = pSBoxB[(aByteB ^ static_cast<std::uint8_t>(((aTemp << 5U) | (aTemp >> 3U)))) & 0xFFU];
    aByteA = static_cast<std::uint8_t>(aByteA + static_cast<std::uint8_t>(((aByteB << 5U) | (aByteB >> 3U))));

    return aByteA | (static_cast<std::uint16_t>(aByteB) << 8U);
}


std::uint16_t TwistMix16::Mix162(int pFunction,
                                 const std::uint16_t aValue,
                                 const std::uint8_t *pSBoxA,
                                 const std::uint8_t *pSBoxB) {
    
    switch (pFunction) {
        
        case  0: return Mix162_000(aValue, pSBoxA, pSBoxB);
        case  1: return Mix162_001(aValue, pSBoxA, pSBoxB);
        case  2: return Mix162_002(aValue, pSBoxA, pSBoxB);
        case  3: return Mix162_003(aValue, pSBoxA, pSBoxB);
        case  4: return Mix162_004(aValue, pSBoxA, pSBoxB);
        case  5: return Mix162_005(aValue, pSBoxA, pSBoxB);
        case  6: return Mix162_006(aValue, pSBoxA, pSBoxB);
        case  7: return Mix162_007(aValue, pSBoxA, pSBoxB);
        case  8: return Mix162_008(aValue, pSBoxA, pSBoxB);
        case  9: return Mix162_009(aValue, pSBoxA, pSBoxB);
        case 10: return Mix162_010(aValue, pSBoxA, pSBoxB);
        case 11: return Mix162_011(aValue, pSBoxA, pSBoxB);
        case 12: return Mix162_012(aValue, pSBoxA, pSBoxB);
        case 13: return Mix162_013(aValue, pSBoxA, pSBoxB);
        case 14: return Mix162_014(aValue, pSBoxA, pSBoxB);
        case 15: return Mix162_015(aValue, pSBoxA, pSBoxB);
        case 16: return Mix162_016(aValue, pSBoxA, pSBoxB);
        case 17: return Mix162_017(aValue, pSBoxA, pSBoxB);
        case 18: return Mix162_018(aValue, pSBoxA, pSBoxB);
        case 19: return Mix162_019(aValue, pSBoxA, pSBoxB);
        
        default:
            return Mix162_000(aValue, pSBoxA, pSBoxB);
    }
}

std::uint16_t TwistMix16::Mix161(int pFunction,
                                   const std::uint16_t aValue,
                                   const std::uint8_t *pSBox) {
    
    switch (pFunction) {
        case 0:  return Mix161_000(aValue, pSBox);
        case 1:  return Mix161_001(aValue, pSBox);
        case 2:  return Mix161_002(aValue, pSBox);
        case 3:  return Mix161_003(aValue, pSBox);
        case 4:  return Mix161_004(aValue, pSBox);
        case 5:  return Mix161_005(aValue, pSBox);
        case 6:  return Mix161_006(aValue, pSBox);
        case 7:  return Mix161_007(aValue, pSBox);
        case 8:  return Mix161_008(aValue, pSBox);
        case 9:  return Mix161_009(aValue, pSBox);
        case 10: return Mix161_010(aValue, pSBox);
        case 11: return Mix161_011(aValue, pSBox);
        default:
            return Mix161_000(aValue, pSBox);
    }
}
