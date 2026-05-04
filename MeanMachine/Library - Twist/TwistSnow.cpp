//
//  TwistSnow.cpp
//  MeanMachine
//

#include "TwistSnow.hpp"
#include "TwistFunctional.hpp"

#include <cstdint>
#include <cstddef>

static constexpr std::uint32_t SHA256_K[64] = {
    0x428A2F98U, 0x71374491U, 0xB5C0FBCFU, 0xE9B5DBA5U,
    0x3956C25BU, 0x59F111F1U, 0x923F82A4U, 0xAB1C5ED5U,
    0xD807AA98U, 0x12835B01U, 0x243185BEU, 0x550C7DC3U,
    0x72BE5D74U, 0x80DEB1FEU, 0x9BDC06A7U, 0xC19BF174U,
    0xE49B69C1U, 0xEFBE4786U, 0x0FC19DC6U, 0x240CA1CCU,
    0x2DE92C6FU, 0x4A7484AAU, 0x5CB0A9DCU, 0x76F988DAU,
    0x983E5152U, 0xA831C66DU, 0xB00327C8U, 0xBF597FC7U,
    0xC6E00BF3U, 0xD5A79147U, 0x06CA6351U, 0x14292967U,
    0x27B70A85U, 0x2E1B2138U, 0x4D2C6DFCU, 0x53380D13U,
    0x650A7354U, 0x766A0ABBU, 0x81C2C92EU, 0x92722C85U,
    0xA2BFE8A1U, 0xA81A664BU, 0xC24B8B70U, 0xC76C51A3U,
    0xD192E819U, 0xD6990624U, 0xF40E3585U, 0x106AA070U,
    0x19A4C116U, 0x1E376C08U, 0x2748774CU, 0x34B0BCB5U,
    0x391C0CB3U, 0x4ED8AA4AU, 0x5B9CCA4FU, 0x682E6FF3U,
    0x748F82EEU, 0x78A5636FU, 0x84C87814U, 0x8CC70208U,
    0x90BEFFFAU, 0xA4506CEBU, 0xBEF9A3F7U, 0xC67178F2U
};

namespace {

static constexpr std::uint8_t AES_SBOX[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
    0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
    0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
    0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
    0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
    0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
    0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
    0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
    0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
    0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68,
    0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

static constexpr std::uint8_t AES_INV_SBOX[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38,
    0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
    0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D,
    0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2,
    0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA,
    0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A,
    0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
    0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA,
    0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85,
    0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
    0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20,
    0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31,
    0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
    0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0,
    0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26,
    0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

static constexpr std::uint8_t AES_RCON[15] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
    0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D
};

static constexpr std::uint8_t ARIA_SB2[256] = {
    0xE2, 0x4E, 0x54, 0xFC, 0x94, 0xC2, 0x4A, 0xCC,
    0x62, 0x0D, 0x6A, 0x46, 0x3C, 0x4D, 0x8B, 0xD1,
    0x5E, 0xFA, 0x64, 0xCB, 0xB4, 0x97, 0xBE, 0x2B,
    0xBC, 0x77, 0x2E, 0x03, 0xD3, 0x19, 0x59, 0xC1,
    0x1D, 0x06, 0x41, 0x6B, 0x55, 0xF0, 0x99, 0x69,
    0xEA, 0x9C, 0x18, 0xAE, 0x63, 0xDF, 0xE7, 0xBB,
    0x00, 0x73, 0x66, 0xFB, 0x96, 0x4C, 0x85, 0xE4,
    0x3A, 0x09, 0x45, 0xAA, 0x0F, 0xEE, 0x10, 0xEB,
    0x2D, 0x7F, 0xF4, 0x29, 0xAC, 0xCF, 0xAD, 0x91,
    0x8D, 0x78, 0xC8, 0x95, 0xF9, 0x2F, 0xCE, 0xCD,
    0x08, 0x7A, 0x88, 0x38, 0x5C, 0x83, 0x2A, 0x28,
    0x47, 0xDB, 0xB8, 0xC7, 0x93, 0xA4, 0x12, 0x53,
    0xFF, 0x87, 0x0E, 0x31, 0x36, 0x21, 0x58, 0x48,
    0x01, 0x8E, 0x37, 0x74, 0x32, 0xCA, 0xE9, 0xB1,
    0xB7, 0xAB, 0x0C, 0xD7, 0xC4, 0x56, 0x42, 0x26,
    0x07, 0x98, 0x60, 0xD9, 0xB6, 0xB9, 0x11, 0x40,
    0xEC, 0x20, 0x8C, 0xBD, 0xA0, 0xC9, 0x84, 0x04,
    0x49, 0x23, 0xF1, 0x4F, 0x50, 0x1F, 0x13, 0xDC,
    0xD8, 0xC0, 0x9E, 0x57, 0xE3, 0xC3, 0x7B, 0x65,
    0x3B, 0x02, 0x8F, 0x3E, 0xE8, 0x25, 0x92, 0xE5,
    0x15, 0xDD, 0xFD, 0x17, 0xA9, 0xBF, 0xD4, 0x9A,
    0x7E, 0xC5, 0x39, 0x67, 0xFE, 0x76, 0x9D, 0x43,
    0xA7, 0xE1, 0xD0, 0xF5, 0x68, 0xF2, 0x1B, 0x34,
    0x70, 0x05, 0xA3, 0x8A, 0xD5, 0x79, 0x86, 0xA8,
    0x30, 0xC6, 0x51, 0x4B, 0x1E, 0xA6, 0x27, 0xF6,
    0x35, 0xD2, 0x6E, 0x24, 0x16, 0x82, 0x5F, 0xDA,
    0xE6, 0x75, 0xA2, 0xEF, 0x2C, 0xB2, 0x1C, 0x9F,
    0x5D, 0x6F, 0x80, 0x0A, 0x72, 0x44, 0x9B, 0x6C,
    0x90, 0x0B, 0x5B, 0x33, 0x7D, 0x5A, 0x52, 0xF3,
    0x61, 0xA1, 0xF7, 0xB0, 0xD6, 0x3F, 0x7C, 0x6D,
    0xED, 0x14, 0xE0, 0xA5, 0x3D, 0x22, 0xB3, 0xF8,
    0x89, 0xDE, 0x71, 0x1A, 0xAF, 0xBA, 0xB5, 0x81
};

static constexpr std::uint8_t ARIA_SB4[256] = {
    0x30, 0x68, 0x99, 0x1B, 0x87, 0xB9, 0x21, 0x78,
    0x50, 0x39, 0xDB, 0xE1, 0x72, 0x09, 0x62, 0x3C,
    0x3E, 0x7E, 0x5E, 0x8E, 0xF1, 0xA0, 0xCC, 0xA3,
    0x2A, 0x1D, 0xFB, 0xB6, 0xD6, 0x20, 0xC4, 0x8D,
    0x81, 0x65, 0xF5, 0x89, 0xCB, 0x9D, 0x77, 0xC6,
    0x57, 0x43, 0x56, 0x17, 0xD4, 0x40, 0x1A, 0x4D,
    0xC0, 0x63, 0x6C, 0xE3, 0xB7, 0xC8, 0x64, 0x6A,
    0x53, 0xAA, 0x38, 0x98, 0x0C, 0xF4, 0x9B, 0xED,
    0x7F, 0x22, 0x76, 0xAF, 0xDD, 0x3A, 0x0B, 0x58,
    0x67, 0x88, 0x06, 0xC3, 0x35, 0x0D, 0x01, 0x8B,
    0x8C, 0xC2, 0xE6, 0x5F, 0x02, 0x24, 0x75, 0x93,
    0x66, 0x1E, 0xE5, 0xE2, 0x54, 0xD8, 0x10, 0xCE,
    0x7A, 0xE8, 0x08, 0x2C, 0x12, 0x97, 0x32, 0xAB,
    0xB4, 0x27, 0x0A, 0x23, 0xDF, 0xEF, 0xCA, 0xD9,
    0xB8, 0xFA, 0xDC, 0x31, 0x6B, 0xD1, 0xAD, 0x19,
    0x49, 0xBD, 0x51, 0x96, 0xEE, 0xE4, 0xA8, 0x41,
    0xDA, 0xFF, 0xCD, 0x55, 0x86, 0x36, 0xBE, 0x61,
    0x52, 0xF8, 0xBB, 0x0E, 0x82, 0x48, 0x69, 0x9A,
    0xE0, 0x47, 0x9E, 0x5C, 0x04, 0x4B, 0x34, 0x15,
    0x79, 0x26, 0xA7, 0xDE, 0x29, 0xAE, 0x92, 0xD7,
    0x84, 0xE9, 0xD2, 0xBA, 0x5D, 0xF3, 0xC5, 0xB0,
    0xBF, 0xA4, 0x3B, 0x71, 0x44, 0x46, 0x2B, 0xFC,
    0xEB, 0x6F, 0xD5, 0xF6, 0x14, 0xFE, 0x7C, 0x70,
    0x5A, 0x7D, 0xFD, 0x2F, 0x18, 0x83, 0x16, 0xA5,
    0x91, 0x1F, 0x05, 0x95, 0x74, 0xA9, 0xC1, 0x5B,
    0x4A, 0x85, 0x6D, 0x13, 0x07, 0x4F, 0x4E, 0x45,
    0xB2, 0x0F, 0xC9, 0x1C, 0xA6, 0xBC, 0xEC, 0x73,
    0x90, 0x7B, 0xCF, 0x59, 0x8F, 0xA1, 0xF9, 0x2D,
    0xF2, 0xB1, 0x00, 0x94, 0x37, 0x9F, 0xD0, 0x2E,
    0x9C, 0x6E, 0x28, 0x3F, 0x80, 0xF0, 0x3D, 0xD3,
    0x25, 0x8A, 0xB5, 0xE7, 0x42, 0xB3, 0xC7, 0xEA,
    0xF7, 0x4C, 0x11, 0x33, 0x03, 0xA2, 0xAC, 0x60
};

static constexpr std::uint8_t ARIA_C1[16] = {
    0x51, 0x7C, 0xC1, 0xB7, 0x27, 0x22, 0x0A, 0x94,
    0xFE, 0x13, 0xAB, 0xE8, 0xFA, 0x9A, 0x6E, 0xE0
};

static constexpr std::uint8_t ARIA_C2[16] = {
    0x6D, 0xB1, 0x4A, 0xCC, 0x9E, 0x21, 0xC8, 0x20,
    0xFF, 0x28, 0xB1, 0xD5, 0xEF, 0x5D, 0xE2, 0xB0
};

static constexpr std::uint8_t ARIA_C3[16] = {
    0xDB, 0x92, 0x37, 0x1D, 0x21, 0x26, 0xE9, 0x70,
    0x03, 0x24, 0x97, 0x75, 0x04, 0xE8, 0xC9, 0x0E
};

inline std::uint8_t GfMul2(std::uint8_t pValue) {
    std::uint8_t aResult = static_cast<std::uint8_t>(pValue << 1);
    if ((pValue & 0x80U) != 0U) {
        aResult = static_cast<std::uint8_t>(aResult ^ 0x1BU);
    }
    return aResult;
}

inline std::uint8_t GfMul3(std::uint8_t pValue) {
    return static_cast<std::uint8_t>(GfMul2(pValue) ^ pValue);
}

inline void XorBlock16(const std::uint8_t *pA,
                       const std::uint8_t *pB,
                       std::uint8_t *pDest) {

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        pDest[aIndex] = static_cast<std::uint8_t>(pA[aIndex] ^ pB[aIndex]);
    }
}

inline void IncrementCounter128BE(std::uint8_t *pCounter) {

    for (int aIndex = 15; aIndex >= 0; aIndex--) {
        pCounter[aIndex] = static_cast<std::uint8_t>(pCounter[aIndex] + 1U);
        if (pCounter[aIndex] != 0U) {
            break;
        }
    }
}

inline std::uint32_t Load32LE(const std::uint8_t *pData) {
    return
        (static_cast<std::uint32_t>(pData[0]) << 0) |
        (static_cast<std::uint32_t>(pData[1]) << 8) |
        (static_cast<std::uint32_t>(pData[2]) << 16) |
        (static_cast<std::uint32_t>(pData[3]) << 24);
}

inline void Store32LE(std::uint8_t *pData,
                      std::uint32_t pValue) {

    pData[0] = static_cast<std::uint8_t>((pValue >> 0) & 0xFFU);
    pData[1] = static_cast<std::uint8_t>((pValue >> 8) & 0xFFU);
    pData[2] = static_cast<std::uint8_t>((pValue >> 16) & 0xFFU);
    pData[3] = static_cast<std::uint8_t>((pValue >> 24) & 0xFFU);
}

inline void AesSubBytes(std::uint8_t *pState) {
    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        pState[aIndex] = AES_SBOX[pState[aIndex]];
    }
}

inline void AesShiftRows(std::uint8_t *pState) {

    std::uint8_t aTemp[16];

    aTemp[0] = pState[0];
    aTemp[1] = pState[5];
    aTemp[2] = pState[10];
    aTemp[3] = pState[15];

    aTemp[4] = pState[4];
    aTemp[5] = pState[9];
    aTemp[6] = pState[14];
    aTemp[7] = pState[3];

    aTemp[8] = pState[8];
    aTemp[9] = pState[13];
    aTemp[10] = pState[2];
    aTemp[11] = pState[7];

    aTemp[12] = pState[12];
    aTemp[13] = pState[1];
    aTemp[14] = pState[6];
    aTemp[15] = pState[11];

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        pState[aIndex] = aTemp[aIndex];
    }
}

inline void AesMixColumns(std::uint8_t *pState) {

    for (std::size_t aColumn = 0; aColumn < 4; aColumn++) {

        const std::size_t aIndex = aColumn * 4;

        const std::uint8_t a0 = pState[aIndex + 0];
        const std::uint8_t a1 = pState[aIndex + 1];
        const std::uint8_t a2 = pState[aIndex + 2];
        const std::uint8_t a3 = pState[aIndex + 3];

        pState[aIndex + 0] = static_cast<std::uint8_t>(
            GfMul2(a0) ^ GfMul3(a1) ^ a2 ^ a3
        );

        pState[aIndex + 1] = static_cast<std::uint8_t>(
            a0 ^ GfMul2(a1) ^ GfMul3(a2) ^ a3
        );

        pState[aIndex + 2] = static_cast<std::uint8_t>(
            a0 ^ a1 ^ GfMul2(a2) ^ GfMul3(a3)
        );

        pState[aIndex + 3] = static_cast<std::uint8_t>(
            GfMul3(a0) ^ a1 ^ a2 ^ GfMul2(a3)
        );
    }
}

inline void AesAddRoundKey(std::uint8_t *pState,
                           const std::uint8_t *pRoundKey) {

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        pState[aIndex] = static_cast<std::uint8_t>(pState[aIndex] ^ pRoundKey[aIndex]);
    }
}

void Aes256ExpandKey(const std::uint8_t *pKey,
                     std::uint8_t *pRoundKeys) {

    for (std::size_t aIndex = 0; aIndex < 32; aIndex++) {
        pRoundKeys[aIndex] = pKey[aIndex];
    }

    std::size_t aBytesGenerated = 32;
    std::size_t aRconIndex = 1;
    std::uint8_t aTemp[4];

    while (aBytesGenerated < 240) {

        for (std::size_t aIndex = 0; aIndex < 4; aIndex++) {
            aTemp[aIndex] = pRoundKeys[aBytesGenerated - 4 + aIndex];
        }

        if ((aBytesGenerated % 32) == 0U) {

            const std::uint8_t aSwap = aTemp[0];
            aTemp[0] = aTemp[1];
            aTemp[1] = aTemp[2];
            aTemp[2] = aTemp[3];
            aTemp[3] = aSwap;

            aTemp[0] = AES_SBOX[aTemp[0]];
            aTemp[1] = AES_SBOX[aTemp[1]];
            aTemp[2] = AES_SBOX[aTemp[2]];
            aTemp[3] = AES_SBOX[aTemp[3]];

            aTemp[0] = static_cast<std::uint8_t>(aTemp[0] ^ AES_RCON[aRconIndex]);
            aRconIndex += 1;

        } else if ((aBytesGenerated % 32) == 16U) {

            aTemp[0] = AES_SBOX[aTemp[0]];
            aTemp[1] = AES_SBOX[aTemp[1]];
            aTemp[2] = AES_SBOX[aTemp[2]];
            aTemp[3] = AES_SBOX[aTemp[3]];
        }

        for (std::size_t aIndex = 0; aIndex < 4; aIndex++) {
            pRoundKeys[aBytesGenerated] = static_cast<std::uint8_t>(
                pRoundKeys[aBytesGenerated - 32] ^ aTemp[aIndex]
            );
            aBytesGenerated += 1;
        }
    }
}

void Aes256EncryptBlock(const std::uint8_t *pRoundKeys,
                        const std::uint8_t *pSource,
                        std::uint8_t *pDest) {

    std::uint8_t aState[16];

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        aState[aIndex] = pSource[aIndex];
    }

    AesAddRoundKey(aState, pRoundKeys);

    for (std::size_t aRound = 1; aRound < 14; aRound++) {
        AesSubBytes(aState);
        AesShiftRows(aState);
        AesMixColumns(aState);
        AesAddRoundKey(aState, pRoundKeys + (aRound * 16));
    }

    AesSubBytes(aState);
    AesShiftRows(aState);
    AesAddRoundKey(aState, pRoundKeys + (14 * 16));

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        pDest[aIndex] = aState[aIndex];
    }
}

inline void ChaChaQuarterRound(std::uint32_t &pA,
                               std::uint32_t &pB,
                               std::uint32_t &pC,
                               std::uint32_t &pD) {

    pA += pB;
    pD ^= pA;
    pD = RotL32(pD, 16);

    pC += pD;
    pB ^= pC;
    pB = RotL32(pB, 12);

    pA += pB;
    pD ^= pA;
    pD = RotL32(pD, 8);

    pC += pD;
    pB ^= pC;
    pB = RotL32(pB, 7);
}

void ChaCha20Block(const std::uint8_t *pKey,
                   std::uint32_t pCounter,
                   const std::uint8_t *pNonce,
                   std::uint8_t *pDest) {

    std::uint32_t aState[16];

    aState[0] = 0x61707865U;
    aState[1] = 0x3320646EU;
    aState[2] = 0x79622D32U;
    aState[3] = 0x6B206574U;

    for (std::size_t aIndex = 0; aIndex < 8; aIndex++) {
        aState[4 + aIndex] = Load32LE(pKey + (aIndex * 4));
    }

    aState[12] = pCounter;
    aState[13] = Load32LE(pNonce + 0);
    aState[14] = Load32LE(pNonce + 4);
    aState[15] = Load32LE(pNonce + 8);

    std::uint32_t aWork[16];

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        aWork[aIndex] = aState[aIndex];
    }

    for (int aRound = 0; aRound < 10; aRound++) {

        ChaChaQuarterRound(aWork[0], aWork[4], aWork[8], aWork[12]);
        ChaChaQuarterRound(aWork[1], aWork[5], aWork[9], aWork[13]);
        ChaChaQuarterRound(aWork[2], aWork[6], aWork[10], aWork[14]);
        ChaChaQuarterRound(aWork[3], aWork[7], aWork[11], aWork[15]);

        ChaChaQuarterRound(aWork[0], aWork[5], aWork[10], aWork[15]);
        ChaChaQuarterRound(aWork[1], aWork[6], aWork[11], aWork[12]);
        ChaChaQuarterRound(aWork[2], aWork[7], aWork[8], aWork[13]);
        ChaChaQuarterRound(aWork[3], aWork[4], aWork[9], aWork[14]);
    }

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        aWork[aIndex] += aState[aIndex];
    }

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        Store32LE(pDest + (aIndex * 4), aWork[aIndex]);
    }
}

inline void AriaSubLayer1(std::uint8_t *pState) {

    pState[0] = AES_SBOX[pState[0]];
    pState[1] = ARIA_SB2[pState[1]];
    pState[2] = AES_INV_SBOX[pState[2]];
    pState[3] = ARIA_SB4[pState[3]];

    pState[4] = AES_SBOX[pState[4]];
    pState[5] = ARIA_SB2[pState[5]];
    pState[6] = AES_INV_SBOX[pState[6]];
    pState[7] = ARIA_SB4[pState[7]];

    pState[8] = AES_SBOX[pState[8]];
    pState[9] = ARIA_SB2[pState[9]];
    pState[10] = AES_INV_SBOX[pState[10]];
    pState[11] = ARIA_SB4[pState[11]];

    pState[12] = AES_SBOX[pState[12]];
    pState[13] = ARIA_SB2[pState[13]];
    pState[14] = AES_INV_SBOX[pState[14]];
    pState[15] = ARIA_SB4[pState[15]];
}

inline void AriaSubLayer2(std::uint8_t *pState) {

    pState[0] = AES_INV_SBOX[pState[0]];
    pState[1] = ARIA_SB4[pState[1]];
    pState[2] = AES_SBOX[pState[2]];
    pState[3] = ARIA_SB2[pState[3]];

    pState[4] = AES_INV_SBOX[pState[4]];
    pState[5] = ARIA_SB4[pState[5]];
    pState[6] = AES_SBOX[pState[6]];
    pState[7] = ARIA_SB2[pState[7]];

    pState[8] = AES_INV_SBOX[pState[8]];
    pState[9] = ARIA_SB4[pState[9]];
    pState[10] = AES_SBOX[pState[10]];
    pState[11] = ARIA_SB2[pState[11]];

    pState[12] = AES_INV_SBOX[pState[12]];
    pState[13] = ARIA_SB4[pState[13]];
    pState[14] = AES_SBOX[pState[14]];
    pState[15] = ARIA_SB2[pState[15]];
}

inline void AriaDiffuseA(std::uint8_t *pState) {

    std::uint8_t aTemp[16];

    aTemp[0] = static_cast<std::uint8_t>(pState[3] ^ pState[4] ^ pState[6] ^ pState[8] ^ pState[9] ^ pState[13] ^ pState[14]);
    aTemp[1] = static_cast<std::uint8_t>(pState[2] ^ pState[5] ^ pState[7] ^ pState[8] ^ pState[9] ^ pState[12] ^ pState[15]);
    aTemp[2] = static_cast<std::uint8_t>(pState[1] ^ pState[4] ^ pState[6] ^ pState[10] ^ pState[11] ^ pState[12] ^ pState[15]);
    aTemp[3] = static_cast<std::uint8_t>(pState[0] ^ pState[5] ^ pState[7] ^ pState[10] ^ pState[11] ^ pState[13] ^ pState[14]);
    aTemp[4] = static_cast<std::uint8_t>(pState[0] ^ pState[2] ^ pState[5] ^ pState[8] ^ pState[11] ^ pState[14] ^ pState[15]);
    aTemp[5] = static_cast<std::uint8_t>(pState[1] ^ pState[3] ^ pState[4] ^ pState[9] ^ pState[10] ^ pState[14] ^ pState[15]);
    aTemp[6] = static_cast<std::uint8_t>(pState[0] ^ pState[2] ^ pState[7] ^ pState[9] ^ pState[10] ^ pState[12] ^ pState[13]);
    aTemp[7] = static_cast<std::uint8_t>(pState[1] ^ pState[3] ^ pState[6] ^ pState[8] ^ pState[11] ^ pState[12] ^ pState[13]);
    aTemp[8] = static_cast<std::uint8_t>(pState[0] ^ pState[1] ^ pState[4] ^ pState[7] ^ pState[10] ^ pState[13] ^ pState[15]);
    aTemp[9] = static_cast<std::uint8_t>(pState[0] ^ pState[1] ^ pState[5] ^ pState[6] ^ pState[11] ^ pState[12] ^ pState[14]);
    aTemp[10] = static_cast<std::uint8_t>(pState[2] ^ pState[3] ^ pState[5] ^ pState[6] ^ pState[8] ^ pState[13] ^ pState[15]);
    aTemp[11] = static_cast<std::uint8_t>(pState[2] ^ pState[3] ^ pState[4] ^ pState[7] ^ pState[9] ^ pState[12] ^ pState[14]);
    aTemp[12] = static_cast<std::uint8_t>(pState[1] ^ pState[2] ^ pState[6] ^ pState[7] ^ pState[9] ^ pState[11] ^ pState[12]);
    aTemp[13] = static_cast<std::uint8_t>(pState[0] ^ pState[3] ^ pState[6] ^ pState[7] ^ pState[8] ^ pState[10] ^ pState[13]);
    aTemp[14] = static_cast<std::uint8_t>(pState[0] ^ pState[3] ^ pState[4] ^ pState[5] ^ pState[9] ^ pState[11] ^ pState[14]);
    aTemp[15] = static_cast<std::uint8_t>(pState[1] ^ pState[2] ^ pState[4] ^ pState[5] ^ pState[8] ^ pState[10] ^ pState[15]);

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        pState[aIndex] = aTemp[aIndex];
    }
}

inline void AriaFO(const std::uint8_t *pInput,
                   const std::uint8_t *pRoundKey,
                   std::uint8_t *pOutput) {

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        pOutput[aIndex] = static_cast<std::uint8_t>(pInput[aIndex] ^ pRoundKey[aIndex]);
    }

    AriaSubLayer1(pOutput);
    AriaDiffuseA(pOutput);
}

inline void AriaFE(const std::uint8_t *pInput,
                   const std::uint8_t *pRoundKey,
                   std::uint8_t *pOutput) {

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        pOutput[aIndex] = static_cast<std::uint8_t>(pInput[aIndex] ^ pRoundKey[aIndex]);
    }

    AriaSubLayer2(pOutput);
    AriaDiffuseA(pOutput);
}

void AriaRotateRight128(const std::uint8_t *pInput,
                        std::size_t pBits,
                        std::uint8_t *pOutput) {

    const std::size_t aBits = pBits & 127U;

    if (aBits == 0U) {
        for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
            pOutput[aIndex] = pInput[aIndex];
        }
        return;
    }

    const std::size_t aByteShift = aBits / 8U;
    const std::size_t aBitShift = aBits % 8U;

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {

        const std::size_t aLowerIndex = (aIndex + 16U - aByteShift) & 15U;

        if (aBitShift == 0U) {
            pOutput[aIndex] = pInput[aLowerIndex];
            continue;
        }

        const std::size_t aUpperIndex = (aLowerIndex + 15U) & 15U;

        pOutput[aIndex] = static_cast<std::uint8_t>(
            (pInput[aLowerIndex] >> aBitShift) |
            (pInput[aUpperIndex] << (8U - aBitShift))
        );
    }
}

void AriaRotateLeft128(const std::uint8_t *pInput,
                       std::size_t pBits,
                       std::uint8_t *pOutput) {

    const std::size_t aBits = pBits & 127U;
    if (aBits == 0U) {
        for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
            pOutput[aIndex] = pInput[aIndex];
        }
        return;
    }

    AriaRotateRight128(pInput, 128U - aBits, pOutput);
}

void AriaBuildRoundKeys256(const std::uint8_t *pKey,
                           std::uint8_t pRoundKeys[17][16]) {

    std::uint8_t aW0[16];
    std::uint8_t aW1[16];
    std::uint8_t aW2[16];
    std::uint8_t aW3[16];

    std::uint8_t aKL[16];
    std::uint8_t aKR[16];

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        aKL[aIndex] = pKey[aIndex];
        aKR[aIndex] = pKey[16 + aIndex];
        aW0[aIndex] = aKL[aIndex];
    }

    AriaFO(aW0, ARIA_C3, aW1);
    XorBlock16(aW1, aKR, aW1);

    AriaFE(aW1, ARIA_C1, aW2);
    XorBlock16(aW2, aW0, aW2);

    AriaFO(aW2, ARIA_C2, aW3);
    XorBlock16(aW3, aW1, aW3);

    std::uint8_t aRot[16];

    AriaRotateRight128(aW1, 19U, aRot);
    XorBlock16(aW0, aRot, pRoundKeys[0]);

    AriaRotateRight128(aW2, 19U, aRot);
    XorBlock16(aW1, aRot, pRoundKeys[1]);

    AriaRotateRight128(aW3, 19U, aRot);
    XorBlock16(aW2, aRot, pRoundKeys[2]);

    AriaRotateRight128(aW0, 19U, aRot);
    XorBlock16(aRot, aW3, pRoundKeys[3]);

    AriaRotateRight128(aW1, 31U, aRot);
    XorBlock16(aW0, aRot, pRoundKeys[4]);

    AriaRotateRight128(aW2, 31U, aRot);
    XorBlock16(aW1, aRot, pRoundKeys[5]);

    AriaRotateRight128(aW3, 31U, aRot);
    XorBlock16(aW2, aRot, pRoundKeys[6]);

    AriaRotateRight128(aW0, 31U, aRot);
    XorBlock16(aRot, aW3, pRoundKeys[7]);

    AriaRotateLeft128(aW1, 61U, aRot);
    XorBlock16(aW0, aRot, pRoundKeys[8]);

    AriaRotateLeft128(aW2, 61U, aRot);
    XorBlock16(aW1, aRot, pRoundKeys[9]);

    AriaRotateLeft128(aW3, 61U, aRot);
    XorBlock16(aW2, aRot, pRoundKeys[10]);

    AriaRotateLeft128(aW0, 61U, aRot);
    XorBlock16(aRot, aW3, pRoundKeys[11]);

    AriaRotateLeft128(aW1, 31U, aRot);
    XorBlock16(aW0, aRot, pRoundKeys[12]);

    AriaRotateLeft128(aW2, 31U, aRot);
    XorBlock16(aW1, aRot, pRoundKeys[13]);

    AriaRotateLeft128(aW3, 31U, aRot);
    XorBlock16(aW2, aRot, pRoundKeys[14]);

    AriaRotateLeft128(aW0, 31U, aRot);
    XorBlock16(aRot, aW3, pRoundKeys[15]);

    AriaRotateLeft128(aW1, 19U, aRot);
    XorBlock16(aW0, aRot, pRoundKeys[16]);
}

void AriaEncryptBlock256(const std::uint8_t pRoundKeys[17][16],
                         const std::uint8_t *pSource,
                         std::uint8_t *pDest) {

    std::uint8_t aState[16];
    std::uint8_t aWork[16];

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        aState[aIndex] = pSource[aIndex];
    }

    for (int aRound = 0; aRound < 15; aRound++) {

        if ((aRound & 1) == 0) {
            AriaFO(aState, pRoundKeys[aRound], aWork);
        } else {
            AriaFE(aState, pRoundKeys[aRound], aWork);
        }

        for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
            aState[aIndex] = aWork[aIndex];
        }
    }

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        aState[aIndex] = static_cast<std::uint8_t>(aState[aIndex] ^ pRoundKeys[15][aIndex]);
    }

    AriaSubLayer2(aState);

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        pDest[aIndex] = static_cast<std::uint8_t>(aState[aIndex] ^ pRoundKeys[16][aIndex]);
    }
}

} // namespace

inline std::uint32_t TwistSnow::Load32BE(const std::uint8_t *pData) {

    return
        (static_cast<std::uint32_t>(pData[0]) << 24) |
        (static_cast<std::uint32_t>(pData[1]) << 16) |
        (static_cast<std::uint32_t>(pData[2]) << 8)  |
        (static_cast<std::uint32_t>(pData[3]) << 0);
}

inline void TwistSnow::Store32BE(std::uint8_t *pData,
                                 std::uint32_t pValue) {

    pData[0] = static_cast<std::uint8_t>((pValue >> 24) & 0xFFU);
    pData[1] = static_cast<std::uint8_t>((pValue >> 16) & 0xFFU);
    pData[2] = static_cast<std::uint8_t>((pValue >> 8)  & 0xFFU);
    pData[3] = static_cast<std::uint8_t>((pValue >> 0)  & 0xFFU);
}

void TwistSnow::DigestSingleBlockSHA256(const std::uint8_t *pBlock,
                                        std::uint8_t *pDest) {

    std::uint32_t aW[64];

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        aW[aIndex] = Load32BE(pBlock + (aIndex * 4));
    }

    for (std::size_t aIndex = 16; aIndex < 64; aIndex++) {

        std::uint32_t aS0 =
        RotR32(aW[aIndex - 15], 7) ^
        RotR32(aW[aIndex - 15], 18) ^
            (aW[aIndex - 15] >> 3);

        std::uint32_t aS1 =
        RotR32(aW[aIndex - 2], 17) ^
        RotR32(aW[aIndex - 2], 19) ^
            (aW[aIndex - 2] >> 10);

        aW[aIndex] = aW[aIndex - 16] + aS0 + aW[aIndex - 7] + aS1;
    }

    std::uint32_t aA = 0x6A09E667U;
    std::uint32_t aB = 0xBB67AE85U;
    std::uint32_t aC = 0x3C6EF372U;
    std::uint32_t aD = 0xA54FF53AU;
    std::uint32_t aE = 0x510E527FU;
    std::uint32_t aF = 0x9B05688CU;
    std::uint32_t aG = 0x1F83D9ABU;
    std::uint32_t aH = 0x5BE0CD19U;

    for (std::size_t aIndex = 0; aIndex < 64; aIndex++) {

        std::uint32_t aS1 =
        RotR32(aE, 6) ^
        RotR32(aE, 11) ^
        RotR32(aE, 25);

        std::uint32_t aCh = (aE & aF) ^ ((~aE) & aG);

        std::uint32_t aTemp1 =
            aH + aS1 + aCh + SHA256_K[aIndex] + aW[aIndex];

        std::uint32_t aS0 =
        RotR32(aA, 2) ^
        RotR32(aA, 13) ^
        RotR32(aA, 22);

        std::uint32_t aMaj = (aA & aB) ^ (aA & aC) ^ (aB & aC);

        std::uint32_t aTemp2 = aS0 + aMaj;

        aH = aG;
        aG = aF;
        aF = aE;
        aE = aD + aTemp1;
        aD = aC;
        aC = aB;
        aB = aA;
        aA = aTemp1 + aTemp2;
    }

    aA += 0x6A09E667U;
    aB += 0xBB67AE85U;
    aC += 0x3C6EF372U;
    aD += 0xA54FF53AU;
    aE += 0x510E527FU;
    aF += 0x9B05688CU;
    aG += 0x1F83D9ABU;
    aH += 0x5BE0CD19U;

    Store32BE(pDest + 0,  aA);
    Store32BE(pDest + 4,  aB);
    Store32BE(pDest + 8,  aC);
    Store32BE(pDest + 12, aD);
    Store32BE(pDest + 16, aE);
    Store32BE(pDest + 20, aF);
    Store32BE(pDest + 24, aG);
    Store32BE(pDest + 28, aH);
}

void TwistSnow::Sha256Counter(std::uint8_t *pSource,
                              std::uint8_t *pDest) {

    std::uint8_t aBlock[64];
    std::uint8_t aDigest[32];

    for (std::size_t aIndex = 0; aIndex < 64; aIndex++) {
        aBlock[aIndex] = 0;
    }

    // Fixed message prefix: first 48 bytes of the repeated source.
    for (std::size_t aIndex = 0; aIndex < 48; aIndex++) {
        aBlock[aIndex] = pSource[aIndex];
    }

    // Message is exactly:
    // source[0..47] || counter64
    //
    // 48 + 8 = 56 bytes.
    // Padding starts at byte 56.
    aBlock[56] = 0x80U;

    // SHA-256 bit length = 56 bytes * 8 = 448 bits.
    aBlock[57] = 0;
    aBlock[58] = 0;
    aBlock[59] = 0;
    aBlock[60] = 0;
    aBlock[61] = 0;
    aBlock[62] = 1;
    aBlock[63] = 0xC0U;

    std::uint64_t aCounter = 0;
    std::size_t aDestIndex = 0;

    while (aDestIndex < S_BLOCK) {

        // Counter goes in bytes 48..55, big endian.
        aBlock[48] = static_cast<std::uint8_t>((aCounter >> 56) & 0xFFU);
        aBlock[49] = static_cast<std::uint8_t>((aCounter >> 48) & 0xFFU);
        aBlock[50] = static_cast<std::uint8_t>((aCounter >> 40) & 0xFFU);
        aBlock[51] = static_cast<std::uint8_t>((aCounter >> 32) & 0xFFU);
        aBlock[52] = static_cast<std::uint8_t>((aCounter >> 24) & 0xFFU);
        aBlock[53] = static_cast<std::uint8_t>((aCounter >> 16) & 0xFFU);
        aBlock[54] = static_cast<std::uint8_t>((aCounter >> 8)  & 0xFFU);
        aBlock[55] = static_cast<std::uint8_t>((aCounter >> 0)  & 0xFFU);

        DigestSingleBlockSHA256(aBlock, aDigest);

        std::size_t aCopyCount = S_BLOCK - aDestIndex;

        if (aCopyCount > 32) {
            aCopyCount = 32;
        }

        for (std::size_t aIndex = 0; aIndex < aCopyCount; aIndex++) {
            pDest[aDestIndex + aIndex] = aDigest[aIndex];
        }

        aDestIndex += aCopyCount;
        aCounter += 1;
    }
}

void TwistSnow::AES256Counter(std::uint8_t *pSource,
                              std::uint8_t *pDest) {

    std::uint8_t aRoundKeys[240];
    Aes256ExpandKey(pSource, aRoundKeys);

    std::uint8_t aCounter[16];
    std::uint8_t aStream[16];

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        aCounter[aIndex] = pSource[32 + aIndex];
    }

    std::size_t aDestIndex = 0;

    while (aDestIndex < S_BLOCK) {

        Aes256EncryptBlock(aRoundKeys, aCounter, aStream);

        std::size_t aCopyCount = S_BLOCK - aDestIndex;
        if (aCopyCount > 16U) {
            aCopyCount = 16U;
        }

        for (std::size_t aIndex = 0; aIndex < aCopyCount; aIndex++) {
            pDest[aDestIndex + aIndex] = aStream[aIndex];
        }

        aDestIndex += aCopyCount;
        IncrementCounter128BE(aCounter);
    }
}

void TwistSnow::ChaCha20Counter(std::uint8_t *pSource,
                                std::uint8_t *pDest) {

    const std::uint8_t *aKey = pSource;
    std::uint32_t aCounter = Load32LE(pSource + 32);
    const std::uint8_t *aNonce = pSource + 36;

    std::uint8_t aStream[64];
    std::size_t aDestIndex = 0;

    while (aDestIndex < S_BLOCK) {

        ChaCha20Block(aKey, aCounter, aNonce, aStream);

        std::size_t aCopyCount = S_BLOCK - aDestIndex;
        if (aCopyCount > 64U) {
            aCopyCount = 64U;
        }

        for (std::size_t aIndex = 0; aIndex < aCopyCount; aIndex++) {
            pDest[aDestIndex + aIndex] = aStream[aIndex];
        }

        aDestIndex += aCopyCount;
        aCounter += 1U;
    }
}

void TwistSnow::Aria256Counter(std::uint8_t *pSource,
                               std::uint8_t *pDest) {

    std::uint8_t aRoundKeys[17][16];
    AriaBuildRoundKeys256(pSource, aRoundKeys);

    std::uint8_t aCounter[16];
    std::uint8_t aStream[16];

    for (std::size_t aIndex = 0; aIndex < 16; aIndex++) {
        aCounter[aIndex] = pSource[32 + aIndex];
    }

    std::size_t aDestIndex = 0;

    while (aDestIndex < S_BLOCK) {

        AriaEncryptBlock256(aRoundKeys, aCounter, aStream);

        std::size_t aCopyCount = S_BLOCK - aDestIndex;
        if (aCopyCount > 16U) {
            aCopyCount = 16U;
        }

        for (std::size_t aIndex = 0; aIndex < aCopyCount; aIndex++) {
            pDest[aDestIndex + aIndex] = aStream[aIndex];
        }

        aDestIndex += aCopyCount;
        IncrementCounter128BE(aCounter);
    }
}

void TwistSnow::MurmurHash(std::uint8_t *pSource,
                           std::uint8_t *pDest) {

    std::uint64_t aState = 5381;

    for (int aIndex = 0; aIndex < S_BLOCK; aIndex++) {

        std::uint64_t aChar = pSource[aIndex];

        aState ^= aChar + 0x9E3779B97F4A7C15ULL + (aState << 6) + (aState >> 2);
        aState *= 0xD6E8FEB86659FD93ULL;
        aState = (aState << 27) | (aState >> 37);

        std::uint64_t aMixed = aState + static_cast<std::uint64_t>(aIndex);

        aMixed ^= aMixed >> 30;
        aMixed *= 0xBF58476D1CE4E5B9ULL;
        aMixed ^= aMixed >> 27;
        aMixed *= 0x94D049BB133111EBULL;
        aMixed ^= aMixed >> 31;

        pDest[aIndex] = static_cast<std::uint8_t>(aMixed >> 56);
    }
}
