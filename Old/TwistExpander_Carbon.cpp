#include "TwistExpander_Carbon.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix64.hpp"

#include <cstring>

const std::uint8_t TwistExpander_Carbon::kSBoxA[S_SBOX] = {
    0x52, 0x4D, 0x7F, 0xD0, 0x55, 0x81, 0xFD, 0x8D, 0x24, 0xBC, 0x2E, 0x47, 0xFA, 0xE0, 0xCC, 0xA2, 
    0xC3, 0xD6, 0x22, 0x90, 0x86, 0xF8, 0x3A, 0x69, 0x8C, 0x01, 0xC2, 0xB0, 0x14, 0x82, 0xDE, 0x2C, 
    0x32, 0x1B, 0x5A, 0x35, 0x64, 0x6A, 0xF4, 0x83, 0x58, 0x5F, 0x99, 0xB4, 0x3F, 0xAE, 0xF9, 0x91, 
    0x1D, 0xB1, 0x94, 0xCD, 0xE3, 0xFB, 0xC0, 0x54, 0xFC, 0x0C, 0xEA, 0x04, 0x0A, 0xE8, 0x93, 0x43, 
    0x6F, 0x0B, 0xDA, 0xDF, 0x02, 0x20, 0x19, 0xFE, 0xCA, 0x16, 0x3D, 0x4E, 0x7B, 0xD9, 0x3B, 0x96, 
    0x17, 0xA0, 0x61, 0x4A, 0x75, 0xC6, 0x72, 0xC4, 0x5C, 0x1E, 0x3C, 0x2A, 0x48, 0x08, 0x25, 0x62, 
    0x7D, 0x76, 0x11, 0x5B, 0x46, 0xD5, 0xC5, 0x4B, 0x06, 0x67, 0x5D, 0xAC, 0xF6, 0x8B, 0xF5, 0x2D, 
    0x2B, 0x1F, 0xA7, 0xA4, 0x87, 0xC9, 0xF7, 0xC8, 0x00, 0xEF, 0x92, 0xA8, 0x30, 0x27, 0x88, 0x41, 
    0x5E, 0xCE, 0xD1, 0x97, 0xB8, 0x26, 0xDB, 0xAD, 0x50, 0x63, 0x71, 0x56, 0xCF, 0x84, 0x3E, 0x03, 
    0xB3, 0x37, 0xE9, 0xD2, 0x49, 0x9A, 0xBB, 0x39, 0xE7, 0xAB, 0x7C, 0x4C, 0xEE, 0x65, 0x53, 0x4F, 
    0x38, 0x18, 0xCB, 0x8E, 0xA9, 0x21, 0x09, 0x59, 0x10, 0x9C, 0x51, 0x8F, 0x66, 0x1A, 0x44, 0xEC, 
    0xA5, 0xFF, 0xB9, 0xC1, 0x98, 0xDC, 0x34, 0xF0, 0x1C, 0xB6, 0x15, 0xD7, 0x12, 0x0D, 0x6D, 0xB2, 
    0x40, 0x31, 0xD4, 0xE6, 0x9F, 0xBE, 0xD3, 0x6C, 0xEB, 0x0F, 0x9E, 0x7E, 0x95, 0xDD, 0xD8, 0x05, 
    0xE2, 0xB7, 0x0E, 0xF3, 0x74, 0x80, 0x29, 0xF2, 0x6E, 0x85, 0x6B, 0xA1, 0xAA, 0xF1, 0x42, 0x28, 
    0xE5, 0xBA, 0x68, 0xED, 0xBD, 0x73, 0x79, 0xC7, 0x89, 0xA3, 0x77, 0x36, 0xBF, 0x57, 0xA6, 0x33, 
    0x45, 0x23, 0xE4, 0x13, 0xE1, 0x78, 0x9B, 0x60, 0x7A, 0xB5, 0x07, 0x2F, 0xAF, 0x8A, 0x9D, 0x70
};

const std::uint8_t TwistExpander_Carbon::kSBoxB[S_SBOX] = {
    0x03, 0xF9, 0x68, 0x61, 0x7E, 0xEE, 0x0A, 0x9D, 0xB1, 0x18, 0xE7, 0xAF, 0x77, 0xBC, 0x8F, 0xBA, 
    0xE8, 0x44, 0x94, 0x2B, 0x93, 0x3B, 0x13, 0xD0, 0xC5, 0xC0, 0xB0, 0x6B, 0x6C, 0xFA, 0x5E, 0xAB, 
    0x09, 0x0B, 0x19, 0x74, 0xFB, 0xC4, 0x48, 0xA2, 0x55, 0x28, 0x69, 0x02, 0x22, 0xC9, 0x63, 0x73, 
    0x2E, 0x33, 0x42, 0xD7, 0xA8, 0x2F, 0xFC, 0x26, 0x52, 0xEB, 0xEA, 0xF1, 0xCE, 0xA6, 0x3F, 0xC6, 
    0xF5, 0x96, 0x37, 0x06, 0xD4, 0xD8, 0x47, 0x1E, 0xAA, 0x20, 0x6E, 0xED, 0x01, 0x23, 0x4B, 0x0E, 
    0x78, 0xF6, 0xCA, 0x84, 0x3E, 0xD9, 0x43, 0x95, 0x3C, 0x3A, 0x36, 0x8E, 0xC8, 0x82, 0xE9, 0xDE, 
    0x24, 0x2A, 0x5D, 0x41, 0xF7, 0x50, 0xCD, 0xDC, 0xBD, 0xEF, 0x64, 0x85, 0x04, 0xB8, 0x10, 0xF3, 
    0xD6, 0x62, 0x8B, 0x9F, 0xCB, 0xBE, 0x5C, 0xE6, 0x98, 0xDB, 0x67, 0xEC, 0x45, 0xA5, 0xAC, 0x8A, 
    0x70, 0xC3, 0x39, 0x56, 0x71, 0xFD, 0x6F, 0xDD, 0x4F, 0x86, 0x57, 0x6A, 0x9B, 0xDF, 0x7A, 0x8C, 
    0x7F, 0x38, 0xFE, 0x2D, 0x90, 0x7D, 0x65, 0x07, 0xC1, 0xF8, 0x7C, 0xA1, 0x83, 0xA3, 0x5B, 0xB5, 
    0x5F, 0x1F, 0xF2, 0x89, 0xB4, 0x80, 0xDA, 0x0D, 0x05, 0x58, 0x17, 0xD1, 0xB7, 0x53, 0xBB, 0xCF, 
    0xC7, 0x46, 0x29, 0xA4, 0x31, 0x12, 0x2C, 0x21, 0x76, 0x4E, 0x34, 0x1C, 0x49, 0xB3, 0xB9, 0x27, 
    0xD2, 0x1D, 0x08, 0x99, 0x4C, 0x54, 0x75, 0xE1, 0xB2, 0xFF, 0x14, 0x30, 0x1A, 0x4A, 0x7B, 0xA9, 
    0xF0, 0x16, 0xA7, 0x35, 0x66, 0xB6, 0x9A, 0x6D, 0xAD, 0x87, 0x9C, 0xAE, 0xA0, 0x79, 0x9E, 0xC2, 
    0x8D, 0x3D, 0x88, 0x97, 0x40, 0x1B, 0x4D, 0x81, 0xF4, 0xE2, 0x72, 0x60, 0x0C, 0x32, 0xD3, 0x51, 
    0xE3, 0xCC, 0xD5, 0x11, 0xE4, 0x15, 0x25, 0x92, 0x59, 0x5A, 0xE5, 0xBF, 0x91, 0xE0, 0x00, 0x0F
};

const std::uint8_t TwistExpander_Carbon::kSBoxC[S_SBOX] = {
    0x34, 0x98, 0x97, 0x4A, 0x7F, 0xA1, 0xE9, 0x1F, 0xE1, 0x79, 0x7C, 0x05, 0xA2, 0x44, 0x8F, 0xBD, 
    0x58, 0x69, 0xC2, 0xB2, 0xEA, 0xA3, 0x25, 0xCF, 0x77, 0xDE, 0x30, 0xC7, 0xEF, 0xC8, 0xF5, 0x7D, 
    0xB9, 0x38, 0xA8, 0xF2, 0x19, 0xA6, 0x1D, 0xA0, 0xA9, 0xE2, 0x46, 0xE5, 0x6F, 0x03, 0xCB, 0xDA, 
    0x1B, 0xAF, 0x90, 0xE7, 0x2D, 0xCA, 0x31, 0x17, 0x81, 0x08, 0xD9, 0x94, 0x2B, 0xD8, 0xDB, 0x27, 
    0xEC, 0x43, 0xD7, 0x9D, 0xB7, 0xC3, 0x39, 0x80, 0xAC, 0xEE, 0x6E, 0xF1, 0xB5, 0xBE, 0x4D, 0x91, 
    0x86, 0xBC, 0x53, 0xD3, 0x0A, 0x12, 0x41, 0x13, 0x8B, 0x72, 0x06, 0x5E, 0xD2, 0x2A, 0x89, 0x3A, 
    0x96, 0x63, 0xA5, 0xC0, 0x6D, 0x00, 0x7B, 0xBB, 0x95, 0x70, 0xE3, 0x02, 0x1C, 0x3C, 0x75, 0x15, 
    0x36, 0x1A, 0xF7, 0x9E, 0x82, 0xC5, 0x74, 0xAD, 0xB6, 0x93, 0xB3, 0x20, 0xB8, 0x88, 0x55, 0x26, 
    0x8A, 0x8E, 0x22, 0xF9, 0x5B, 0xE0, 0xBF, 0x6A, 0x35, 0x52, 0x28, 0x16, 0xE6, 0xEB, 0x07, 0xDF, 
    0xAE, 0xF3, 0xB0, 0x4B, 0xBA, 0x2F, 0x32, 0x4C, 0x0F, 0x49, 0xFE, 0xF0, 0xFB, 0x71, 0x5C, 0x99, 
    0x24, 0x51, 0xC4, 0x76, 0x48, 0xAB, 0x42, 0xC1, 0xCD, 0x0C, 0x5D, 0x1E, 0x18, 0x50, 0x6C, 0xFA, 
    0xF6, 0xE8, 0x33, 0x59, 0x2E, 0xF4, 0x9A, 0x3F, 0x73, 0xE4, 0x87, 0x01, 0xCC, 0x60, 0xED, 0xC6, 
    0x4E, 0xD0, 0x68, 0x67, 0x65, 0x78, 0x23, 0x85, 0xB1, 0x61, 0x0D, 0xFF, 0xF8, 0x9C, 0xD6, 0xFC, 
    0x45, 0x8C, 0x09, 0x56, 0x62, 0xC9, 0x37, 0x3E, 0x84, 0x83, 0xCE, 0xD4, 0x21, 0x57, 0x4F, 0x5F, 
    0x0E, 0x5A, 0xA7, 0x92, 0x11, 0x29, 0xB4, 0x7A, 0x3D, 0xD5, 0x0B, 0x9B, 0x10, 0x7E, 0x9F, 0xD1, 
    0x04, 0xAA, 0x66, 0xA4, 0x2C, 0xDC, 0x47, 0x3B, 0xDD, 0x8D, 0xFD, 0x14, 0x6B, 0x54, 0x64, 0x40
};

const std::uint8_t TwistExpander_Carbon::kSBoxD[S_SBOX] = {
    0x7A, 0xF7, 0xE0, 0x28, 0x26, 0xB5, 0xB2, 0x7F, 0xDF, 0x14, 0x7D, 0x55, 0xEE, 0x77, 0xD9, 0xAD, 
    0x6F, 0x40, 0xB7, 0xBA, 0xE9, 0xA6, 0x66, 0xB3, 0x4B, 0xAF, 0x5B, 0xDE, 0x80, 0xC9, 0xAA, 0x35, 
    0x8C, 0x36, 0x90, 0xD0, 0x4D, 0xCF, 0x6C, 0xFD, 0xD8, 0x84, 0x64, 0xFE, 0x72, 0x67, 0x92, 0x8E, 
    0x5E, 0xEA, 0x9A, 0xED, 0x0B, 0xDA, 0x13, 0x12, 0x86, 0x51, 0xD5, 0xBB, 0x39, 0x9D, 0xC6, 0x75, 
    0xDB, 0x0D, 0x8A, 0x9E, 0xD3, 0xFF, 0x7E, 0xCE, 0xB1, 0xC8, 0x3A, 0x8B, 0xC0, 0xF6, 0x52, 0xD2, 
    0xFC, 0xE5, 0x59, 0xAB, 0x42, 0x7B, 0x1E, 0x33, 0xF8, 0x22, 0x0E, 0x5D, 0xE3, 0x71, 0xEB, 0x25, 
    0xA8, 0x3E, 0x94, 0xA4, 0x61, 0x3C, 0x07, 0x9F, 0xF3, 0x31, 0xCC, 0x2F, 0x24, 0x17, 0x58, 0x01, 
    0x69, 0x16, 0xB9, 0xC5, 0xDD, 0xCD, 0x10, 0xF9, 0x9B, 0xC1, 0xF2, 0x0F, 0xC4, 0xA3, 0x6B, 0x3D, 
    0xB0, 0x91, 0x1C, 0xE6, 0x34, 0x97, 0xBE, 0x1B, 0x32, 0x11, 0x62, 0x5A, 0xA5, 0xA1, 0x46, 0xE7, 
    0xA2, 0x98, 0xA9, 0x60, 0xD7, 0x18, 0x48, 0x1A, 0x2B, 0x73, 0x9C, 0xC3, 0xF5, 0x79, 0x4E, 0xBF, 
    0x2E, 0x4A, 0x85, 0x03, 0x3B, 0xCB, 0x45, 0xEC, 0xA0, 0x70, 0x06, 0x37, 0x05, 0x02, 0x29, 0xBD, 
    0xF1, 0xFA, 0x00, 0x27, 0x50, 0xE2, 0xE4, 0x4C, 0x6A, 0xB6, 0xB4, 0x74, 0xE8, 0x65, 0x93, 0x96, 
    0x09, 0xF0, 0x08, 0x1F, 0x0C, 0x5C, 0x54, 0xA7, 0xE1, 0x2D, 0x38, 0xD4, 0xAE, 0xD6, 0xC2, 0x8F, 
    0x3F, 0x82, 0x19, 0x30, 0x76, 0x81, 0x21, 0x04, 0xEF, 0x95, 0xFB, 0xD1, 0x47, 0x78, 0x41, 0x15, 
    0x63, 0x7C, 0x87, 0x89, 0x20, 0x2A, 0x88, 0x4F, 0x5F, 0x99, 0x0A, 0xAC, 0x68, 0x6E, 0x8D, 0xB8, 
    0x1D, 0x83, 0x57, 0xDC, 0x43, 0xBC, 0x2C, 0x6D, 0xF4, 0xCA, 0xC7, 0x49, 0x53, 0x23, 0x44, 0x56
};

const std::uint8_t TwistExpander_Carbon::kSBoxE[S_SBOX] = {
    0x7A, 0x6D, 0x19, 0x88, 0x6B, 0x27, 0xEB, 0x34, 0x64, 0x82, 0xB6, 0xBF, 0xFA, 0xEE, 0x5D, 0x45, 
    0x8C, 0x49, 0xA5, 0x31, 0x36, 0xE8, 0xA3, 0x1E, 0xE4, 0xC7, 0x5C, 0x91, 0x02, 0xE5, 0x89, 0xA4, 
    0x63, 0xD3, 0xBA, 0x72, 0xDD, 0xDC, 0xFB, 0x35, 0xA8, 0xB9, 0x21, 0x42, 0xA0, 0x56, 0x38, 0xE1, 
    0x12, 0x41, 0xE2, 0x8D, 0x2C, 0x2A, 0x4E, 0xBB, 0x3B, 0x04, 0x3C, 0xC4, 0xC5, 0x2E, 0xF3, 0x6C, 
    0xDF, 0x15, 0x5A, 0x59, 0x05, 0xB7, 0xC1, 0x29, 0x9C, 0x10, 0xB2, 0xAF, 0xCA, 0x98, 0x73, 0xF0, 
    0xC0, 0x57, 0xDE, 0x7C, 0xCB, 0x8F, 0xDA, 0x9D, 0x7B, 0xD0, 0x62, 0x65, 0x6E, 0xD7, 0xB4, 0x1C, 
    0x0B, 0x09, 0x01, 0x6A, 0x6F, 0x8B, 0x4D, 0xAC, 0xD6, 0x1F, 0xAB, 0x44, 0xE9, 0xF5, 0x2B, 0x74, 
    0xB5, 0x00, 0x46, 0x84, 0xE6, 0x5E, 0x39, 0x8E, 0x17, 0x3F, 0x23, 0x97, 0x71, 0xA6, 0x37, 0x7E, 
    0x69, 0x4F, 0x58, 0x20, 0x51, 0x76, 0x8A, 0x94, 0x68, 0xCC, 0x18, 0xA9, 0x9F, 0x24, 0x70, 0xD5, 
    0x53, 0x60, 0xFE, 0x9A, 0xBE, 0xE3, 0x93, 0x61, 0xFF, 0x55, 0xDB, 0xBD, 0xEF, 0x0D, 0xAA, 0x7F, 
    0xB1, 0x11, 0x4C, 0xF6, 0x47, 0x67, 0x07, 0x78, 0xD1, 0x22, 0xB8, 0x26, 0xCF, 0x03, 0x7D, 0xFD, 
    0x54, 0xF9, 0x81, 0x9E, 0xF1, 0x9B, 0xA2, 0x28, 0xC2, 0x50, 0xD2, 0x99, 0xC3, 0xD4, 0xCD, 0x83, 
    0xAE, 0xA1, 0x5B, 0x2F, 0xE0, 0x90, 0x4A, 0x1D, 0xEC, 0xC6, 0x30, 0xC9, 0x32, 0x4B, 0x48, 0x14, 
    0xFC, 0x80, 0x16, 0xEA, 0x1B, 0xF7, 0xA7, 0x3A, 0x0F, 0xF4, 0x0C, 0x87, 0x85, 0xF8, 0xBC, 0x77, 
    0xED, 0x43, 0xCE, 0x2D, 0x52, 0x0A, 0xD8, 0x5F, 0xE7, 0x95, 0xD9, 0xB0, 0x40, 0x79, 0x96, 0xB3, 
    0xAD, 0x75, 0x3D, 0x13, 0x3E, 0x08, 0x33, 0x0E, 0x1A, 0x92, 0x06, 0x66, 0x86, 0x25, 0xF2, 0xC8
};

const std::uint8_t TwistExpander_Carbon::kSBoxF[S_SBOX] = {
    0x2E, 0x11, 0xDC, 0x1E, 0xDD, 0x62, 0xEC, 0x97, 0xB3, 0x4B, 0xA0, 0x02, 0x1F, 0xD7, 0x30, 0x61, 
    0xD4, 0xF8, 0x55, 0xAC, 0x91, 0x1B, 0x99, 0xE1, 0x82, 0x56, 0xC1, 0xBE, 0x7A, 0x73, 0xEF, 0xA4, 
    0x8E, 0x9E, 0x39, 0x7D, 0x01, 0xF0, 0xEE, 0x66, 0x3D, 0xCE, 0xAE, 0x5C, 0x6E, 0x94, 0x0E, 0xB9, 
    0x78, 0xAB, 0x4E, 0x25, 0xC6, 0x0A, 0xC5, 0xC8, 0xF9, 0xB6, 0xC4, 0xA1, 0x50, 0xC0, 0xBD, 0xE0, 
    0x07, 0x45, 0x0D, 0xFA, 0x47, 0x51, 0x9A, 0xFD, 0xD6, 0x7E, 0x6A, 0x00, 0x3E, 0x1C, 0x8C, 0x4A, 
    0x6B, 0x65, 0xF6, 0xE2, 0xCF, 0x23, 0x3C, 0x27, 0xDF, 0x69, 0x7F, 0x42, 0xE6, 0x54, 0xA6, 0xE7, 
    0xD8, 0xDE, 0x8D, 0x2C, 0x17, 0xE9, 0x32, 0xF7, 0xA5, 0x10, 0xCA, 0x90, 0xEA, 0x71, 0xFB, 0xB1, 
    0x57, 0x7C, 0x96, 0x87, 0x84, 0xC7, 0xFF, 0xD2, 0x43, 0x33, 0xA8, 0x72, 0x8A, 0xA2, 0x60, 0xE4, 
    0xDB, 0x34, 0x0B, 0x5F, 0xA9, 0xB7, 0x18, 0x85, 0x2A, 0xF2, 0x2D, 0xCC, 0x21, 0x95, 0x7B, 0x52, 
    0xAF, 0x79, 0xD5, 0x1A, 0xF3, 0xBF, 0xB8, 0x88, 0x24, 0x63, 0xCD, 0x04, 0x26, 0x14, 0x3B, 0x15, 
    0x9D, 0x8F, 0xC3, 0x86, 0x67, 0x44, 0x41, 0x28, 0x98, 0x59, 0x3F, 0x93, 0x05, 0x8B, 0x13, 0x22, 
    0x92, 0xE8, 0xBC, 0xD0, 0xBB, 0xEB, 0x68, 0x0C, 0x6D, 0x58, 0x6F, 0xED, 0x9C, 0xA3, 0x03, 0xBA, 
    0xF1, 0x9F, 0xFC, 0x31, 0x48, 0x4F, 0x0F, 0x16, 0xD1, 0xA7, 0x5D, 0xC9, 0x5B, 0xFE, 0x09, 0xB4, 
    0xD3, 0x4D, 0xB2, 0x1D, 0xDA, 0x77, 0x53, 0x08, 0x12, 0x80, 0xE5, 0x70, 0x76, 0x19, 0xF5, 0x46, 
    0x20, 0xAD, 0xF4, 0x37, 0x5E, 0x29, 0x3A, 0x36, 0x75, 0x74, 0xCB, 0x6C, 0x5A, 0xD9, 0x83, 0x9B, 
    0x06, 0x40, 0x35, 0x89, 0xC2, 0x2F, 0xAA, 0xE3, 0x2B, 0x49, 0xB0, 0xB5, 0x81, 0x64, 0x4C, 0x38
};

const std::uint8_t TwistExpander_Carbon::kSBoxG[S_SBOX] = {
    0x36, 0xCD, 0xE9, 0x23, 0x7D, 0x3E, 0xFC, 0x4D, 0xD5, 0x94, 0xF4, 0xEC, 0xB7, 0xE3, 0x25, 0x76, 
    0xAB, 0x71, 0x87, 0x52, 0x75, 0x53, 0x37, 0xCE, 0x54, 0xCF, 0xB2, 0xE7, 0x15, 0xC3, 0xB4, 0x10, 
    0xF2, 0x9B, 0xF3, 0xB9, 0xA4, 0x33, 0x20, 0xDA, 0x17, 0x5C, 0x8E, 0x51, 0x98, 0x05, 0x4A, 0x4B, 
    0xC9, 0xFE, 0xE4, 0x3C, 0x1E, 0xAE, 0x56, 0x64, 0xE5, 0xA5, 0xC2, 0x60, 0xF7, 0x26, 0xAF, 0x5A, 
    0x9C, 0xEE, 0x02, 0xAD, 0x32, 0x63, 0x7F, 0x01, 0x77, 0xF1, 0x7C, 0x30, 0x5F, 0xFF, 0x2E, 0x00, 
    0xE8, 0x92, 0x0B, 0x86, 0xC8, 0x04, 0x83, 0xE0, 0xA1, 0x34, 0x65, 0x42, 0x62, 0x13, 0xCC, 0xF6, 
    0x0D, 0x35, 0xBA, 0xEA, 0xF5, 0x8C, 0xF9, 0x9F, 0x84, 0x59, 0xB8, 0xE1, 0xC4, 0x1F, 0x39, 0x09, 
    0x5B, 0x2D, 0xD9, 0x24, 0x6C, 0x8A, 0xDD, 0x93, 0xD6, 0x6D, 0xB6, 0x57, 0x16, 0x28, 0xE2, 0xBE, 
    0x45, 0xC1, 0x3A, 0x19, 0x22, 0x31, 0x1B, 0xF8, 0xD2, 0xEF, 0x7E, 0x80, 0xD8, 0x91, 0x81, 0x2B, 
    0x1A, 0x5D, 0x3F, 0xC7, 0x7B, 0x73, 0xDF, 0xCA, 0xA8, 0xAA, 0x14, 0xD4, 0x74, 0xBD, 0x2F, 0x29, 
    0xD3, 0x66, 0x6E, 0xB0, 0x4E, 0x7A, 0x0A, 0x0E, 0xA3, 0x21, 0xCB, 0xA9, 0x40, 0x82, 0x11, 0x90, 
    0x3D, 0x18, 0x3B, 0x4F, 0x97, 0x50, 0xA0, 0x96, 0xD0, 0xB5, 0x0C, 0x68, 0x47, 0xBC, 0x78, 0x03, 
    0xA7, 0x0F, 0x95, 0xB1, 0xDC, 0x70, 0xDE, 0x61, 0xDB, 0x58, 0xC5, 0xF0, 0xFD, 0x49, 0xE6, 0x79, 
    0x07, 0xAC, 0x41, 0x6B, 0xD1, 0x27, 0xBF, 0x72, 0x85, 0x88, 0x2A, 0x8B, 0xB3, 0x8F, 0x43, 0xA6, 
    0x4C, 0xC6, 0xD7, 0x89, 0x8D, 0x9A, 0xBB, 0x1D, 0xFB, 0x6F, 0x2C, 0x44, 0x69, 0x99, 0xC0, 0xEB, 
    0x08, 0x9E, 0x55, 0x5E, 0xFA, 0xA2, 0x6A, 0x12, 0x46, 0x48, 0x9D, 0xED, 0x1C, 0x06, 0x38, 0x67
};

const std::uint8_t TwistExpander_Carbon::kSBoxH[S_SBOX] = {
    0xF4, 0x9A, 0x66, 0xFB, 0xCA, 0x21, 0x69, 0xBE, 0x35, 0xEA, 0xBC, 0x13, 0x57, 0x87, 0x3D, 0xAC, 
    0x0A, 0xED, 0x23, 0x50, 0x1F, 0xD7, 0x73, 0x29, 0x96, 0xAE, 0x22, 0x75, 0x49, 0x89, 0xE4, 0x3C, 
    0x7A, 0x7E, 0xFD, 0x44, 0x9E, 0x81, 0x48, 0xA1, 0x7D, 0x43, 0x71, 0xE3, 0xCD, 0x33, 0xFF, 0x78, 
    0x68, 0x5D, 0xC6, 0x15, 0x2F, 0x7F, 0xA2, 0xE2, 0x41, 0x19, 0x0E, 0x10, 0x0F, 0x8E, 0xF8, 0x85, 
    0x3F, 0x27, 0x72, 0xCC, 0x06, 0xA3, 0xFE, 0xC1, 0x2B, 0xC9, 0x4D, 0x32, 0xF0, 0xDA, 0x5B, 0x46, 
    0xE1, 0x2C, 0x20, 0xA4, 0xEF, 0xB4, 0xD1, 0x34, 0xEB, 0xC0, 0x65, 0x2A, 0x24, 0x8F, 0x1D, 0x88, 
    0xE6, 0x47, 0xF7, 0xD5, 0x3B, 0x45, 0x1C, 0x8C, 0x90, 0x36, 0xC3, 0xB3, 0xC8, 0xA8, 0x60, 0x14, 
    0x02, 0xE8, 0x12, 0xBA, 0x37, 0x83, 0xE0, 0xAB, 0x86, 0xB0, 0xD0, 0x25, 0xFA, 0x9D, 0x00, 0x05, 
    0x6B, 0xBD, 0xD3, 0x6E, 0x7C, 0xB5, 0x5A, 0x9B, 0x74, 0xA0, 0x79, 0x62, 0x95, 0x9F, 0xE5, 0x2E, 
    0xDD, 0xC4, 0xA6, 0x7B, 0x0C, 0xD9, 0xD4, 0xDB, 0xB9, 0x8D, 0xCE, 0xB2, 0x98, 0xB6, 0xDC, 0x1A, 
    0xF3, 0xD6, 0x03, 0x16, 0x0D, 0x8B, 0xA7, 0x55, 0xDF, 0xCF, 0x5C, 0x3E, 0x1E, 0x56, 0xBB, 0x18, 
    0x92, 0xE9, 0x54, 0x8A, 0x59, 0x64, 0x6C, 0xDE, 0x40, 0x63, 0x61, 0xC5, 0x5F, 0x31, 0xBF, 0xF5, 
    0x2D, 0xD2, 0x6D, 0x91, 0x67, 0x6A, 0x53, 0x97, 0x26, 0xB1, 0x4F, 0x4E, 0xEE, 0x4C, 0xF2, 0x38, 
    0x07, 0x4B, 0x99, 0x76, 0xC7, 0x09, 0x82, 0x5E, 0x17, 0xB7, 0xA9, 0x04, 0xA5, 0xF6, 0xAD, 0xAA, 
    0x39, 0xFC, 0x01, 0x30, 0xC2, 0xF9, 0x70, 0x9C, 0x28, 0x84, 0x6F, 0xEC, 0x42, 0x4A, 0x3A, 0x52, 
    0x93, 0x0B, 0x11, 0x77, 0xAF, 0x58, 0xF1, 0x08, 0xD8, 0xCB, 0xB8, 0x94, 0x1B, 0x80, 0xE7, 0x51
};

TwistExpander_Carbon::TwistExpander_Carbon()
: TwistExpander() {
    std::memcpy(mSBoxA, kSBoxA, S_SBOX);
    std::memcpy(mSBoxB, kSBoxB, S_SBOX);
    std::memcpy(mSBoxC, kSBoxC, S_SBOX);
    std::memcpy(mSBoxD, kSBoxD, S_SBOX);
    std::memcpy(mSBoxE, kSBoxE, S_SBOX);
    std::memcpy(mSBoxF, kSBoxF, S_SBOX);
    std::memcpy(mSBoxG, kSBoxG, S_SBOX);
    std::memcpy(mSBoxH, kSBoxH, S_SBOX);
    SyncDomainBundleInbuiltFromLegacy();
}

void TwistExpander_Carbon::KDF(std::uint64_t pNonce,
                                std::uint8_t *pInput,
                                std::uint8_t *pOutput,
                                TwistDomainConstants *pConstants,
                                TwistDomainSaltSet *pDomainSaltSet,
                                TwistDomainSBoxSet *pDomainSBoxSet) {
    TwistExpander::KDF(pNonce, pInput, pOutput, pConstants, pDomainSaltSet, pDomainSBoxSet);
    TwistWorkSpace *pWorkspace = mWorkspace;
    if ((pWorkspace == nullptr) || (pInput == nullptr) || (pOutput == nullptr) ||
        (pConstants == nullptr) || (pDomainSaltSet == nullptr) || (pDomainSBoxSet == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *pSource = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(0));
    [[maybe_unused]] std::uint8_t *pDestination = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(1));
    [[maybe_unused]] std::uint64_t *aOrbiterSaltA = pDomainSaltSet->mOrbiter.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltB = pDomainSaltSet->mOrbiter.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltC = pDomainSaltSet->mOrbiter.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltD = pDomainSaltSet->mOrbiter.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltE = pDomainSaltSet->mOrbiter.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltF = pDomainSaltSet->mOrbiter.mSaltF;
    [[maybe_unused]] std::uint64_t *aUnwindSaltA = pDomainSaltSet->mUnwind.mSaltA;
    [[maybe_unused]] std::uint64_t *aUnwindSaltB = pDomainSaltSet->mUnwind.mSaltB;
    [[maybe_unused]] std::uint64_t *aUnwindSaltC = pDomainSaltSet->mUnwind.mSaltC;
    [[maybe_unused]] std::uint64_t *aUnwindSaltD = pDomainSaltSet->mUnwind.mSaltD;
    [[maybe_unused]] std::uint64_t *aUnwindSaltE = pDomainSaltSet->mUnwind.mSaltE;
    [[maybe_unused]] std::uint64_t *aUnwindSaltF = pDomainSaltSet->mUnwind.mSaltF;
    [[maybe_unused]] std::uint8_t *mSBoxA = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(30));
    [[maybe_unused]] std::uint8_t *mSBoxB = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(31));
    [[maybe_unused]] std::uint8_t *mSBoxC = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(32));
    [[maybe_unused]] std::uint8_t *mSBoxD = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(33));
    [[maybe_unused]] std::uint8_t *mSBoxE = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(34));
    [[maybe_unused]] std::uint8_t *mSBoxF = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(35));
    [[maybe_unused]] std::uint8_t *mSBoxG = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(36));
    [[maybe_unused]] std::uint8_t *mSBoxH = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(37));
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkspace->mListExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkspace->mListExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkspace->mListExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkspace->mListExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aExpandLaneE = pWorkspace->mListExpansionLaneE;
    [[maybe_unused]] std::uint8_t *aExpandLaneF = pWorkspace->mListExpansionLaneF;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneE = pWorkspace->mWorkLaneE;
    [[maybe_unused]] std::uint8_t *aWorkLaneF = pWorkspace->mWorkLaneF;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkspace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkspace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkspace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkspace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneE = pWorkspace->mOperationLaneE;
    [[maybe_unused]] std::uint8_t *aOperationLaneF = pWorkspace->mOperationLaneF;
    [[maybe_unused]] std::uint8_t *aMaskLaneA = pWorkspace->mMaskLaneA;
    [[maybe_unused]] std::uint8_t *aMaskLaneB = pWorkspace->mMaskLaneB;
    [[maybe_unused]] std::size_t *aIndexList256A = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(190)));
    [[maybe_unused]] std::size_t *aIndexList256B = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(191)));
    [[maybe_unused]] std::size_t *aIndexList256C = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(192)));
    [[maybe_unused]] std::size_t *aIndexList256D = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(193)));
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledB = &(pWorkspace->mMaskBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadA = &(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadB = &(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteB = &(pWorkspace->mMaskBoxB[0][0]);
    std::uint8_t aPublicPrevious = 0;
    std::uint8_t aPublicIngress = 0;
    std::uint8_t aPrivatePrevious = 0;
    std::uint8_t aPrivateIngress = 0;
    std::uint8_t aPublicIngressDomainWord = 0;
    std::uint8_t aPrivateIngressDomainWord = 0;
    std::uint8_t aCrossIngress = 0;
    std::uint8_t aCrossIngressDomainWord = 0;
    std::uint8_t aPublicScatter = 0;
    std::uint8_t aPrivateScatter = 0;
    std::uint8_t aCarry = 0;
    std::uint8_t aOrbitA = 0;
    std::uint8_t aUnwindF = 0;
    std::uint8_t aOrbitB = 0;
    std::uint8_t aUnwindA = 0;
    std::uint8_t aOrbitC = 0;
    std::uint8_t aUnwindE = 0;
    std::uint8_t aOrbitD = 0;
    std::uint8_t aUnwindD = 0;
    std::uint8_t aOrbitE = 0;
    std::uint8_t aUnwindB = 0;
    std::uint8_t aOrbitF = 0;
    std::uint8_t aUnwindC = 0;
    std::uint8_t aMatrixOperationIndex = 0;
    std::uint8_t aMatrixWriteIndex = 0;
    std::uint8_t aMatrixSlotA = 0;
    std::uint8_t aMatrixSlotB = 0;
    std::uint8_t aMatrixLoadIndexA = 0;
    std::uint8_t aMatrixLoadIndexB = 0;
    std::uint8_t aMatrixArgA = 0;
    std::uint8_t aMatrixArgB = 0;
    std::uint8_t aMatrixArgC = 0;
    std::uint8_t aMatrixArgD = 0;
    std::uint8_t aMatrixKindA = 0;
    std::uint8_t aMatrixKindB = 0;
    std::uint8_t aMatrixStoreIndexA = 0;
    std::uint8_t aMatrixStoreIndexB = 0;
    std::uint8_t aMatrixDiffusionSelect = 0;

    {
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                TwistIndexShuffle::Execute256(aIndexList256A, aOperationLaneC);
            }
        
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                TwistIndexShuffle::Execute256(aIndexList256A, aOperationLaneC);
                TwistIndexShuffle::Execute256(aIndexList256B, aOperationLaneD);
            }
        
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                aPublicIngressDomainWord = pConstants->mDomainConstantPublicIngress;
                aPrivateIngressDomainWord = pConstants->mDomainConstantPrivateIngress;
                aCrossIngressDomainWord = pConstants->mDomainConstantCrossIngress;
            }
        
            for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
                aPublicPrevious = aPublicIngress;
                aPrivatePrevious = aPrivateIngress;
                aPublicIngress = RotL64(pSource[aIndex], 7U) ^ RotL64(pSource[((aIndex + 1U)) & S_BLOCK1], 49U);
                aPublicIngress = aPublicIngress + (RotL64(pSource[((aIndex + 17U)) & S_BLOCK1], 31U) ^ RotL64(pSource[S_BLOCK1 - aIndex], 21U));
                aPublicIngress = aPublicIngress ^ aPublicIngressDomainWord;
                aPublicIngress = TwistMix64::DiffuseA(aPublicIngress);
                aPrivateIngress = RotL64(pSource[((aIndex + 3U)) & S_BLOCK1], 7U) ^ RotL64(pSource[((aIndex + 29U)) & S_BLOCK1], 41U);
                aPrivateIngress = aPrivateIngress + (RotL64(pSource[((S_BLOCK1 - aIndex + 7U)) & S_BLOCK1], 49U) ^ RotL64(pSource[((S_BLOCK1 - aIndex + 23U)) & S_BLOCK1], 29U));
                aPrivateIngress = aPrivateIngress ^ aPrivateIngressDomainWord;
                aPrivateIngress = TwistMix64::DiffuseB(aPrivateIngress);
                aCrossIngress = RotL64(pSource[S_BLOCK1 - aIndex], 13U) ^ RotL64(pSource[((S_BLOCK1 - aIndex + 1U)) & S_BLOCK1], 53U);
                aCrossIngress = aCrossIngress + (RotL64(pSource[((aIndex + 11U)) & S_BLOCK1], 27U) ^ RotL64(pSource[((S_BLOCK1 - aIndex + 31U)) & S_BLOCK1], 41U));
                aCrossIngress = aCrossIngress ^ aCrossIngressDomainWord;
                aCrossIngress = TwistMix64::DiffuseC(aCrossIngress);
                //
                aPublicScatter = TwistMix64::DiffuseC(((RotL64(aPublicIngress, 43U) ^ RotL64(aPublicPrevious, 29U)) + (RotL64(aCrossIngress, 11U) ^ RotL64(aPublicIngress, 57U))));
                aPrivateScatter = TwistMix64::DiffuseB(((RotL64(aPrivateIngress, 7U) ^ RotL64(aPrivatePrevious, 37U)) + (RotL64(aCrossIngress, 19U) ^ RotL64(aCarry, 47U))));
                //
                aOrbitA = (aUnwindF + RotL64(aPrivateIngress, 35U)) + 9107326720193244489U;
                aOrbitB = (aUnwindA + RotL64(aPrivatePrevious, 51U)) + 10868585484401664145U;
                aOrbitC = ((aUnwindE + RotL64(aPrivateScatter, 23U)) + 13637736741437846622U) + aOrbiterSaltA[((aIndex + 23U)) & S_BLOCK1];
                aOrbitD = ((aUnwindD + RotL64(aCarry, 17U)) + 6130725216183918844U) + aOrbiterSaltB[((aIndex + 5U)) & S_BLOCK1];
                aOrbitE = (aUnwindB + RotL64(aPrivateIngress, 37U)) + 2063834478521338187U;
                aOrbitF = (aUnwindC + RotL64(aPrivateScatter, 13U)) + 8564870627911949158U;
                //
                aOrbitA = ((aOrbitA + aOrbitB) + 6524015751064086390U) + aOrbiterSaltC[((aIndex + 2U)) & S_SALT1];
                aOrbitD = ((aOrbitD + aOrbitA) + 9874937766875388236U) + aOrbiterSaltD[((aIndex + 10U)) & S_SALT1];
                aOrbitD = RotL64((aOrbitD * 13742951923184859549U), 43U);
                //
                aOrbitB = ((aOrbitB + aOrbitC) + 14723718409522680894U) + aOrbiterSaltD[((aIndex + 29U)) & S_SALT1];
                aOrbitE = ((aOrbitE + aOrbitB) + 13767059954741528279U) + aOrbiterSaltC[((aIndex + 4U)) & S_SALT1];
                aOrbitE = RotL64((aOrbitE * 12318545698100436481U), 63U);
                //
                aOrbitC = ((aOrbitC + aOrbitD) + 6387608251033722169U) + aOrbiterSaltC[((aIndex + 17U)) & S_SALT1];
                aOrbitF = ((aOrbitF + aOrbitC) + 5391425980008431000U) + aOrbiterSaltD[((aIndex + 18U)) & S_SALT1];
                aOrbitF = RotL64((aOrbitF * 14391393108371604739U), 21U);
                //
                aOrbitD = ((aOrbitD + aOrbitE) + 11524218415655093779U) + aOrbiterSaltD[((aIndex + 15U)) & S_SALT1];
                aOrbitA = ((aOrbitA + aOrbitD) + 155510463350385905U) + aOrbiterSaltC[((aIndex + 8U)) & S_SALT1];
                aOrbitA = RotL64((aOrbitA * 858242090800309519U), 29U);
                //
                aOrbitE = ((aOrbitE + aOrbitF) + 10554591788433641311U) + aOrbiterSaltC[((aIndex + 16U)) & S_SALT1];
                aOrbitB = ((aOrbitB + aOrbitE) + 8662160162966241542U) + aOrbiterSaltD[((aIndex + 12U)) & S_SALT1];
                aOrbitB = RotL64((aOrbitB * 16716332750823704427U), 16U);
                //
                aOrbitF = ((aOrbitF + aOrbitA) + 5092555636369853727U) + aOrbiterSaltD[((aIndex + 19U)) & S_SALT1];
                aOrbitC = ((aOrbitC + aOrbitF) + 7163345798448796101U) + aOrbiterSaltC[((aIndex + 20U)) & S_SALT1];
                aOrbitC = RotL64((aOrbitC * 3366076406086492349U), 32U);
                //
                aPrivateIngress = TwistMix64::DiffuseC((((((RotL64(aOrbitA, 19U) ^ aOrbitB) + (RotL64(aOrbitC, 57U) ^ aOrbitD)) + (RotL64(aOrbitE, 29U) ^ aOrbitF)) + aPrivateScatter) + aCarry));
                aWorkLaneA[aIndex] = aPrivateIngress;
                //
                aUnwindA = (((aUnwindA + RotL64(aPrivateIngress, 17U)) + RotL64(aPrivatePrevious, 23U)) + aOrbitC) + aUnwindSaltE[((aIndex + 1U)) & S_SALT1];
                aUnwindB = ((aUnwindB + RotL64(aPrivateIngress, 19U)) + RotL64(aPrivateScatter, 41U)) + aOrbitE;
                aUnwindC = (aUnwindC + aOrbitD) + aOrbitF;
                aUnwindD = (((aUnwindD + RotL64(aPrivateIngress, 43U)) + RotL64(aPrivatePrevious, 53U)) + aOrbitD) + aUnwindSaltF[((aIndex + 7U)) & S_SALT1];
                aUnwindE = ((aUnwindE + RotL64(aPrivateIngress, 51U)) + RotL64(aPrivateScatter, 11U)) + aOrbitF;
                aUnwindF = (aUnwindF + aOrbitF) + aOrbitA;
                //
                aCarry = (((aCarry + (RotL64(aUnwindA, 41U) ^ aUnwindD)) + (aUnwindB ^ RotL64(aUnwindE, 11U))) + (aUnwindC ^ RotL64(aUnwindF, 51U))) + RotL64(aPrivateIngress, 13U);
                aCarry = RotL64((aCarry * 1341678482929213405U), 19U);
                aCarry = aCarry ^ (aCarry >> 29U);
            }
        
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                aPublicIngressDomainWord = pConstants->mDomainConstantPublicIngress;
                aPrivateIngressDomainWord = pConstants->mDomainConstantPrivateIngress;
                aCrossIngressDomainWord = pConstants->mDomainConstantCrossIngress;
            }
        
            for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {

                // Salts, kOrbiterAssign
                aOrbitA = (aUnwindA + RotL64(aPrivateIngress, 23U)) + 9107326720193244489U;
                aOrbitB = (aUnwindE + RotL64(aPrivatePrevious, 35U)) + 10868585484401664145U;
                aOrbitC = ((aUnwindC + RotL64(aPrivateScatter, 13U)) + 13637736741437846622U) + aOrbiterSaltA[((aIndex + 13U)) & S_BLOCK1];
                aOrbitD = ((aUnwindB + RotL64(aCarry, 43U)) + 6130725216183918844U) + aOrbiterSaltB[((aIndex + 1U)) & S_BLOCK1];
                aOrbitE = (aUnwindF + RotL64(aPrivateIngress, 53U)) + 2063834478521338187U;
                aOrbitF = (aUnwindD + RotL64(aPrivateScatter, 41U)) + 8564870627911949158U;
                
                
                // Salts, kOrbiterUpdate
                aOrbitA = ((aOrbitA + aOrbitB) + 6524015751064086390U) + aOrbiterSaltD[((aIndex + 15U)) & S_SALT1];
                aOrbitD = ((aOrbitD + aOrbitA) + 9874937766875388236U) + aOrbiterSaltC[((aIndex + 23U)) & S_SALT1];
                aOrbitD = RotL64((aOrbitD * 13742951923184859549U), 7U);
                //
                aOrbitC = ((aOrbitC + aOrbitD) + 14723718409522680894U) + aOrbiterSaltC[((aIndex + 18U)) & S_SALT1];
                aOrbitF = ((aOrbitF + aOrbitC) + 13767059954741528279U) + aOrbiterSaltD[((aIndex + 2U)) & S_SALT1];
                aOrbitF = RotL64((aOrbitF * 12318545698100436481U), 24U);
                //
                aOrbitE = ((aOrbitE + aOrbitF) + 6387608251033722169U) + aOrbiterSaltD[((aIndex + 12U)) & S_SALT1];
                aOrbitB = ((aOrbitB + aOrbitE) + 5391425980008431000U) + aOrbiterSaltC[((aIndex + 21U)) & S_SALT1];
                aOrbitB = RotL64((aOrbitB * 14391393108371604739U), 16U);
                //
                aOrbitB = ((aOrbitB + aOrbitC) + 11524218415655093779U) + aOrbiterSaltC[((aIndex + 19U)) & S_SALT1];
                aOrbitE = ((aOrbitE + aOrbitB) + 155510463350385905U) + aOrbiterSaltD[((aIndex + 10U)) & S_SALT1];
                aOrbitE = RotL64((aOrbitE * 858242090800309519U), 48U);
                //
                aOrbitD = ((aOrbitD + aOrbitE) + 10554591788433641311U) + aOrbiterSaltD[((aIndex + 11U)) & S_SALT1];
                aOrbitA = ((aOrbitA + aOrbitD) + 8662160162966241542U) + aOrbiterSaltC[((aIndex + 3U)) & S_SALT1];
                aOrbitA = RotL64((aOrbitA * 16716332750823704427U), 40U);
                //
                aOrbitF = ((aOrbitF + aOrbitA) + 5092555636369853727U) + aOrbiterSaltC[((aIndex + 9U)) & S_SALT1];
                aOrbitC = ((aOrbitC + aOrbitF) + 7163345798448796101U) + aOrbiterSaltD[((aIndex + 29U)) & S_SALT1];
                aOrbitC = RotL64((aOrbitC * 3366076406086492349U), 43U);
                
                
                // Salts, kIngressUpdate?
                aPrivateIngress = TwistMix64::DiffuseC((((((aOrbitA ^ RotL64(aOrbitD, 41U)) + (aOrbitB ^ RotL64(aOrbitE, 11U))) + (RotL64(aOrbitC, 57U) ^ aOrbitF)) + aPrivateScatter) + aCarry));
                aWorkLaneB[aIndex] = aPrivateIngress;
                
                
                // Salts, kUnwindUpdate
                aUnwindA = (((aUnwindA + RotL64(aPrivateIngress, 51U)) + RotL64(aPrivatePrevious, 45U)) + aOrbitF) + aUnwindSaltE[((aIndex + 16U)) & S_SALT1];
                aUnwindB = ((aUnwindB + RotL64(aPrivateIngress, 53U)) + RotL64(aPrivateScatter, 43U)) + aOrbitD;
                aUnwindC = (aUnwindC + aOrbitF) + aOrbitB;
                aUnwindD = (((aUnwindD + RotL64(aPrivateIngress, 29U)) + RotL64(aPrivatePrevious, 7U)) + aOrbitC) + aUnwindSaltF[((aIndex + 6U)) & S_SALT1];
                aUnwindE = ((aUnwindE + RotL64(aPrivateIngress, 23U)) + RotL64(aPrivateScatter, 41U)) + aOrbitA;
                aUnwindF = (aUnwindF + aOrbitF) + aOrbitA;
                
                
                // Salts, kCarryUpdate
                aCarry = (((aCarry + (RotL64(aUnwindA, 31U) ^ aUnwindE)) + (RotL64(aUnwindB, 17U) ^ aUnwindF)) + (aUnwindC ^ RotL64(aUnwindD, 13U))) + RotL64(aPrivateIngress, 19U);
                aCarry = RotL64((aCarry * 1341678482929213405U), 43U);
                aCarry = aCarry ^ (aCarry >> 41U);
            }
        
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                aPublicIngressDomainWord = pConstants->mDomainConstantPublicIngress;
                aPrivateIngressDomainWord = pConstants->mDomainConstantPrivateIngress;
                aCrossIngressDomainWord = pConstants->mDomainConstantCrossIngress;
            }
        
            for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
                aPublicPrevious = aPublicIngress;
                aPrivatePrevious = aPrivateIngress;
                aPublicIngress = RotL64(aWorkLaneA[aIndex], 5U) ^ RotL64(aWorkLaneA[((aIndex + 1U)) & S_BLOCK1], 47U);
                aPublicIngress = aPublicIngress + (RotL64(aWorkLaneA[((aIndex + 17U)) & S_BLOCK1], 41U) ^ RotL64(aWorkLaneA[S_BLOCK1 - aIndex], 27U));
                aPublicIngress = aPublicIngress ^ aPublicIngressDomainWord;
                aPublicIngress = TwistMix64::DiffuseA(aPublicIngress);
                aPrivateIngress = RotL64(aWorkLaneA[((aIndex + 3U)) & S_BLOCK1], 35U) ^ RotL64(aWorkLaneA[((aIndex + 29U)) & S_BLOCK1], 19U);
                aPrivateIngress = aPrivateIngress + (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 7U)) & S_BLOCK1], 13U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 23U)) & S_BLOCK1], 51U));
                aPrivateIngress = aPrivateIngress ^ aPrivateIngressDomainWord;
                aPrivateIngress = TwistMix64::DiffuseB(aPrivateIngress);
                aCrossIngress = RotL64(aWorkLaneA[S_BLOCK1 - aIndex], 35U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 1U)) & S_BLOCK1], 13U);
                aCrossIngress = aCrossIngress + (RotL64(aWorkLaneA[((aIndex + 11U)) & S_BLOCK1], 19U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 31U)) & S_BLOCK1], 53U));
                aCrossIngress = aCrossIngress ^ aCrossIngressDomainWord;
                aCrossIngress = TwistMix64::DiffuseC(aCrossIngress);
                //
                aPublicScatter = TwistMix64::DiffuseC(((RotL64(aPublicIngress, 35U) ^ RotL64(aPublicPrevious, 19U)) + (RotL64(aCrossIngress, 5U) ^ RotL64(aPublicIngress, 53U))));
                aPrivateScatter = TwistMix64::DiffuseA(((RotL64(aPrivateIngress, 49U) ^ RotL64(aPrivatePrevious, 41U)) + (RotL64(aCrossIngress, 21U) ^ RotL64(aCarry, 5U))));
                //
                aOrbitA = (aUnwindF + RotL64(aPrivateIngress, 13U)) + 9107326720193244489U;
                aOrbitB = (aUnwindC + RotL64(aPrivatePrevious, 53U)) + 10868585484401664145U;
                aOrbitC = ((aUnwindE + RotL64(aPrivateScatter, 19U)) + 13637736741437846622U) + aOrbiterSaltA[((aIndex + 16U)) & S_BLOCK1];
                aOrbitD = ((aUnwindA + RotL64(aCarry, 41U)) + 6130725216183918844U) + aOrbiterSaltB[((aIndex + 1U)) & S_BLOCK1];
                aOrbitE = (aUnwindB + RotL64(aPrivateIngress, 11U)) + 2063834478521338187U;
                aOrbitF = (aUnwindD + RotL64(aPrivateScatter, 51U)) + 8564870627911949158U;
                //
                aOrbitA = ((aOrbitA + aOrbitF) + 6524015751064086390U) + aOrbiterSaltC[((aIndex + 9U)) & S_SALT1];
                aOrbitD = ((aOrbitD + aOrbitA) + 9874937766875388236U) + aOrbiterSaltD[((aIndex + 14U)) & S_SALT1];
                aOrbitD = RotL64((aOrbitD * 13742951923184859549U), 51U);
                //
                aOrbitF = ((aOrbitF + aOrbitE) + 14723718409522680894U) + aOrbiterSaltD[((aIndex + 23U)) & S_SALT1];
                aOrbitC = ((aOrbitC + aOrbitF) + 13767059954741528279U) + aOrbiterSaltC[((aIndex + 2U)) & S_SALT1];
                aOrbitC = RotL64((aOrbitC * 12318545698100436481U), 43U);
                //
                aOrbitE = ((aOrbitE + aOrbitD) + 6387608251033722169U) + aOrbiterSaltC[((aIndex + 19U)) & S_SALT1];
                aOrbitB = ((aOrbitB + aOrbitE) + 5391425980008431000U) + aOrbiterSaltD[((aIndex + 7U)) & S_SALT1];
                aOrbitB = RotL64((aOrbitB * 14391393108371604739U), 48U);
                //
                aOrbitD = ((aOrbitD + aOrbitC) + 11524218415655093779U) + aOrbiterSaltD[((aIndex + 4U)) & S_SALT1];
                aOrbitA = ((aOrbitA + aOrbitD) + 155510463350385905U) + aOrbiterSaltC[((aIndex + 17U)) & S_SALT1];
                aOrbitA = RotL64((aOrbitA * 858242090800309519U), 16U);
                //
                aOrbitC = ((aOrbitC + aOrbitB) + 10554591788433641311U) + aOrbiterSaltC[((aIndex + 6U)) & S_SALT1];
                aOrbitF = ((aOrbitF + aOrbitC) + 8662160162966241542U) + aOrbiterSaltD[((aIndex + 18U)) & S_SALT1];
                aOrbitF = RotL64((aOrbitF * 16716332750823704427U), 24U);
                //
                aOrbitB = ((aOrbitB + aOrbitA) + 5092555636369853727U) + aOrbiterSaltD[((aIndex + 8U)) & S_SALT1];
                aOrbitE = ((aOrbitE + aOrbitB) + 7163345798448796101U) + aOrbiterSaltC[((aIndex + 10U)) & S_SALT1];
                aOrbitE = RotL64((aOrbitE * 3366076406086492349U), 21U);
                //
                aPrivateIngress = TwistMix64::DiffuseC((((((RotL64(aOrbitA, 19U) ^ aOrbitE) + (RotL64(aOrbitB, 57U) ^ aOrbitF)) + (aOrbitC ^ RotL64(aOrbitD, 47U))) + aPrivateScatter) + aCarry));
                aWorkLaneC[aIndex] = aPrivateIngress;
                //
                aUnwindA = (((aUnwindA + RotL64(aPrivateIngress, 57U)) + RotL64(aPrivatePrevious, 43U)) + aOrbitD) + aUnwindSaltE[((aIndex + 15U)) & S_SALT1];
                aUnwindB = ((aUnwindB + RotL64(aPrivateIngress, 11U)) + RotL64(aPrivateScatter, 53U)) + aOrbitC;
                aUnwindC = (aUnwindC + aOrbitD) + aOrbitB;
                aUnwindD = (((aUnwindD + RotL64(aPrivateIngress, 29U)) + RotL64(aPrivatePrevious, 37U)) + aOrbitF) + aUnwindSaltF[((aIndex + 12U)) & S_SALT1];
                aUnwindE = ((aUnwindE + RotL64(aPrivateIngress, 13U)) + RotL64(aPrivateScatter, 51U)) + aOrbitB;
                aUnwindF = (aUnwindF + aOrbitB) + aOrbitA;
                //
                aCarry = (((aCarry + (aUnwindA ^ RotL64(aUnwindF, 43U))) + (aUnwindB ^ RotL64(aUnwindD, 17U))) + (aUnwindC ^ RotL64(aUnwindE, 37U))) + RotL64(aPrivateIngress, 11U);
                aCarry = RotL64((aCarry * 1341678482929213405U), 13U);
                aCarry = aCarry ^ (aCarry >> 31U);
            }
        
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                aPublicIngressDomainWord = pConstants->mDomainConstantPublicIngress;
                aPrivateIngressDomainWord = pConstants->mDomainConstantPrivateIngress;
                aCrossIngressDomainWord = pConstants->mDomainConstantCrossIngress;
            }
        
            for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
                aPublicPrevious = aPublicIngress;
                aPrivatePrevious = aPrivateIngress;
                aPublicIngress = RotL64(aWorkLaneB[aIndex], 9U) ^ RotL64(aWorkLaneB[((aIndex + 1U)) & S_BLOCK1], 49U);
                aPublicIngress = aPublicIngress + (RotL64(aWorkLaneB[((aIndex + 17U)) & S_BLOCK1], 35U) ^ RotL64(aWorkLaneB[S_BLOCK1 - aIndex], 19U));
                aPublicIngress = aPublicIngress ^ aPublicIngressDomainWord;
                aPublicIngress = TwistMix64::DiffuseA(aPublicIngress);
                aPrivateIngress = RotL64(aWorkLaneB[((aIndex + 3U)) & S_BLOCK1], 47U) ^ RotL64(aWorkLaneB[((aIndex + 29U)) & S_BLOCK1], 27U);
                aPrivateIngress = aPrivateIngress + (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 7U)) & S_BLOCK1], 43U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 23U)) & S_BLOCK1], 5U));
                aPrivateIngress = aPrivateIngress ^ aPrivateIngressDomainWord;
                aPrivateIngress = TwistMix64::DiffuseB(aPrivateIngress);
                aCrossIngress = RotL64(aWorkLaneB[S_BLOCK1 - aIndex], 43U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 1U)) & S_BLOCK1], 27U);
                aCrossIngress = aCrossIngress + (RotL64(aWorkLaneB[((aIndex + 11U)) & S_BLOCK1], 53U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 31U)) & S_BLOCK1], 11U));
                aCrossIngress = aCrossIngress ^ aCrossIngressDomainWord;
                aCrossIngress = TwistMix64::DiffuseC(aCrossIngress);
                //
                aPublicScatter = TwistMix64::DiffuseB(((RotL64(aPublicIngress, 27U) ^ RotL64(aPublicPrevious, 13U)) + (RotL64(aCrossIngress, 41U) ^ RotL64(aPublicIngress, 49U))));
                aPrivateScatter = TwistMix64::DiffuseC(((RotL64(aPrivateIngress, 7U) ^ RotL64(aPrivatePrevious, 51U)) + (RotL64(aCrossIngress, 31U) ^ RotL64(aCarry, 23U))));
                //
                aOrbitA = (aUnwindF + RotL64(aPrivateIngress, 53U)) + 9107326720193244489U;
                aOrbitB = (aUnwindB + RotL64(aPrivateScatter, 57U)) + 10868585484401664145U;
                aOrbitC = ((aUnwindD + RotL64(aCarry, 27U)) + 13637736741437846622U) + aOrbiterSaltA[((aIndex + 12U)) & S_BLOCK1];
                aOrbitD = ((aUnwindE + RotL64(aPrivateIngress, 51U)) + 6130725216183918844U) + aOrbiterSaltB[((aIndex + 11U)) & S_BLOCK1];
                aOrbitE = (aUnwindC + RotL64(aPrivateScatter, 41U)) + 2063834478521338187U;
                aOrbitF = (aUnwindA + RotL64(aPrivatePrevious, 43U)) + 8564870627911949158U;
                //
                aOrbitA = ((aOrbitA + aOrbitD) + 6524015751064086390U) + aOrbiterSaltD[((aIndex + 6U)) & S_SALT1];
                aOrbitF = ((aOrbitF + aOrbitA) + 9874937766875388236U) + aOrbiterSaltC[((aIndex + 18U)) & S_SALT1];
                aOrbitF = RotL64((aOrbitF * 13742951923184859549U), 16U);
                //
                aOrbitB = ((aOrbitB + aOrbitE) + 14723718409522680894U) + aOrbiterSaltC[((aIndex + 4U)) & S_SALT1];
                aOrbitA = ((aOrbitA + aOrbitB) + 13767059954741528279U) + aOrbiterSaltD[((aIndex + 1U)) & S_SALT1];
                aOrbitA = RotL64((aOrbitA * 12318545698100436481U), 21U);
                //
                aOrbitC = ((aOrbitC + aOrbitF) + 6387608251033722169U) + aOrbiterSaltD[((aIndex + 8U)) & S_SALT1];
                aOrbitB = ((aOrbitB + aOrbitC) + 5391425980008431000U) + aOrbiterSaltC[((aIndex + 15U)) & S_SALT1];
                aOrbitB = RotL64((aOrbitB * 14391393108371604739U), 32U);
                //
                aOrbitD = ((aOrbitD + aOrbitA) + 11524218415655093779U) + aOrbiterSaltC[((aIndex + 10U)) & S_SALT1];
                aOrbitC = ((aOrbitC + aOrbitD) + 155510463350385905U) + aOrbiterSaltD[((aIndex + 25U)) & S_SALT1];
                aOrbitC = RotL64((aOrbitC * 858242090800309519U), 24U);
                //
                aOrbitE = ((aOrbitE + aOrbitB) + 10554591788433641311U) + aOrbiterSaltD[((aIndex + 14U)) & S_SALT1];
                aOrbitD = ((aOrbitD + aOrbitE) + 8662160162966241542U) + aOrbiterSaltC[((aIndex + 7U)) & S_SALT1];
                aOrbitD = RotL64((aOrbitD * 16716332750823704427U), 57U);
                //
                aOrbitF = ((aOrbitF + aOrbitC) + 5092555636369853727U) + aOrbiterSaltC[((aIndex + 20U)) & S_SALT1];
                aOrbitE = ((aOrbitE + aOrbitF) + 7163345798448796101U) + aOrbiterSaltD[((aIndex + 2U)) & S_SALT1];
                aOrbitE = RotL64((aOrbitE * 3366076406086492349U), 40U);
                //
                aPrivateIngress = TwistMix64::DiffuseC((((((aOrbitA ^ RotL64(aOrbitF, 23U)) + (RotL64(aOrbitB, 11U) ^ aOrbitD)) + (aOrbitC ^ RotL64(aOrbitE, 37U))) + aPrivateScatter) + aCarry));
                aWorkLaneD[aIndex] = aPrivateIngress;
                //
                aUnwindA = (((aUnwindA + RotL64(aPrivateIngress, 45U)) + RotL64(aPrivatePrevious, 11U)) + aOrbitC) + aUnwindSaltE[((aIndex + 17U)) & S_SALT1];
                aUnwindB = ((aUnwindB + RotL64(aPrivateIngress, 7U)) + RotL64(aPrivateScatter, 31U)) + aOrbitE;
                aUnwindC = (aUnwindC + aOrbitF) + aOrbitB;
                aUnwindD = (((aUnwindD + RotL64(aPrivateIngress, 17U)) + RotL64(aPrivatePrevious, 41U)) + aOrbitB) + aUnwindSaltF[((aIndex + 29U)) & S_SALT1];
                aUnwindE = ((aUnwindE + RotL64(aPrivateIngress, 13U)) + RotL64(aPrivateScatter, 53U)) + aOrbitF;
                aUnwindF = (aUnwindF + aOrbitF) + aOrbitC;
                //
                aCarry = (((aCarry + (aUnwindA ^ RotL64(aUnwindB, 57U))) + (aUnwindC ^ RotL64(aUnwindD, 43U))) + (aUnwindE ^ RotL64(aUnwindF, 41U))) + RotL64(aPrivateIngress, 11U);
                aCarry = RotL64((aCarry * 1341678482929213405U), 29U);
                aCarry = aCarry ^ (aCarry >> 37U);
            }
        
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                TwistIndexShuffle::Execute256(aIndexList256A, aIndexList256A);
                TwistIndexShuffle::Execute256(aIndexList256B, aIndexList256B);
                TwistIndexShuffle::Execute256(aIndexList256C, aIndexList256C);
                TwistIndexShuffle::Execute256(aIndexList256D, aIndexList256D);
                aMatrixOperationIndex = 0U;
                aMatrixWriteIndex = 0U;
            }
        
            for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
                aMatrixSlotA = aIndexList256A[(aMatrixDiffusionIndex) & S_BLOCK1];
                aMatrixSlotB = aIndexList256B[(aMatrixDiffusionIndex) & S_BLOCK1];
                aMatrixLoadIndexA = aMatrixSlotA * 128U;
                aMatrixLoadIndexB = (aMatrixSlotB * 128U) + 64U;
                mMatrixA.LoadAndReset(aWorkLaneA + aMatrixLoadIndexA);
                mMatrixB.LoadAndReset(aWorkLaneB + aMatrixLoadIndexB);
                aOrbitE = aOperationLaneA[(aMatrixOperationIndex) & S_BLOCK1];
                switch (aOrbitE % 3U) {
                	case 0U: {
                		mMatrixA.RotateLeft(0U, 0U);
                		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapRows(aMatrixArgA, aMatrixArgB);
                		mMatrixB.RotateLeft(0U, 0U);
                		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapRows(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex;
                		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
                		mMatrixA.Store(aWorkLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aWorkLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                	case 1U: {
                		mMatrixA.RotateLeft(0U, 0U);
                		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapCols(aMatrixArgA, aMatrixArgB);
                		mMatrixB.RotateRight(0U, 0U);
                		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapColsOdd(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex;
                		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
                		mMatrixA.Store(aWorkLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aWorkLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                	case 2U: {
                		mMatrixA.TransposeMainDiagonal(0U, 0U);
                		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapRowsEven(aMatrixArgA, aMatrixArgB);
                		mMatrixB.FlipVertical(0U, 0U);
                		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapRowsOdd(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex;
                		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
                		mMatrixA.Store(aWorkLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aWorkLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                }
            }
        
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                aMatrixOperationIndex = 0U;
                aMatrixWriteIndex = 0U;
            }
        
            for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
                aMatrixSlotA = aIndexList256C[(aMatrixDiffusionIndex) & S_BLOCK1];
                aMatrixSlotB = aIndexList256D[(aMatrixDiffusionIndex) & S_BLOCK1];
                aMatrixLoadIndexA = (aMatrixSlotA * 128U) + 64U;
                aMatrixLoadIndexB = aMatrixSlotB * 128U;
                mMatrixA.LoadAndReset(aWorkLaneA + aMatrixLoadIndexA);
                mMatrixB.LoadAndReset(aWorkLaneB + aMatrixLoadIndexB);
                aOrbitE = aOperationLaneB[(aMatrixOperationIndex) & S_BLOCK1];
                switch (aOrbitE % 3U) {
                	case 0U: {
                		mMatrixA.RotateLeft(0U, 0U);
                		aMatrixArgA = aOperationLaneB[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneB[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapRows(aMatrixArgA, aMatrixArgB);
                		mMatrixB.RotateLeft(0U, 0U);
                		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneB[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapRows(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneB[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneB[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
                		aMatrixStoreIndexB = aMatrixWriteIndex;
                		mMatrixA.Store(aOperationLaneB + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aOperationLaneB + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                	case 1U: {
                		mMatrixA.RotateLeft(0U, 0U);
                		aMatrixArgA = aOperationLaneB[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneB[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapCols(aMatrixArgA, aMatrixArgB);
                		mMatrixB.RotateRight(0U, 0U);
                		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneB[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapColsOdd(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneB[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneB[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
                		aMatrixStoreIndexB = aMatrixWriteIndex;
                		mMatrixA.Store(aOperationLaneB + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aOperationLaneB + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                	case 2U: {
                		mMatrixA.TransposeMainDiagonal(0U, 0U);
                		aMatrixArgA = aOperationLaneB[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneB[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapRowsEven(aMatrixArgA, aMatrixArgB);
                		mMatrixB.FlipVertical(0U, 0U);
                		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneB[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapRowsOdd(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneB[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneB[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
                		aMatrixStoreIndexB = aMatrixWriteIndex;
                		mMatrixA.Store(aOperationLaneB + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aOperationLaneB + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                }
            }
    }
    {
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                // seed-matrix-diffusion: workA/workC -> maskA/maskB
            }
        
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                TwistIndexShuffle::Execute256(aIndexList256A, aIndexList256A);
                TwistIndexShuffle::Execute256(aIndexList256B, aIndexList256A);
                TwistIndexShuffle::Execute256(aIndexList256C, aIndexList256A);
                TwistIndexShuffle::Execute256(aIndexList256D, aIndexList256A);
                aMatrixOperationIndex = 0U;
                aMatrixWriteIndex = 0U;
            }
        
            for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
                aMatrixSlotA = aIndexList256A[(aMatrixDiffusionIndex) & S_BLOCK1];
                aMatrixSlotB = aIndexList256B[(aMatrixDiffusionIndex) & S_BLOCK1];
                aMatrixLoadIndexA = aMatrixSlotA * 128U;
                aMatrixLoadIndexB = (aMatrixSlotB * 128U) + 64U;
                mMatrixA.LoadAndReset(aWorkLaneA + aMatrixLoadIndexA);
                mMatrixB.LoadAndReset(aWorkLaneA + aMatrixLoadIndexB);
                aMatrixDiffusionSelect = aOperationLaneA[(aMatrixOperationIndex) & S_BLOCK1];
                switch (aMatrixDiffusionSelect % 3U) {
                	case 0U: {
                		mMatrixA.RotateLeft(0U, 0U);
                		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapRows(aMatrixArgA, aMatrixArgB);
                		mMatrixB.RotateLeft(0U, 0U);
                		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapRows(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex;
                		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
                		mMatrixA.Store(aWorkLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aWorkLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                	case 1U: {
                		mMatrixA.RotateLeft(0U, 0U);
                		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapCols(aMatrixArgA, aMatrixArgB);
                		mMatrixB.RotateRight(0U, 0U);
                		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapColsOdd(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex;
                		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
                		mMatrixA.Store(aWorkLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aWorkLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                	case 2U: {
                		mMatrixA.TransposeMainDiagonal(0U, 0U);
                		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapRowsEven(aMatrixArgA, aMatrixArgB);
                		mMatrixB.FlipVertical(0U, 0U);
                		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapRowsOdd(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex;
                		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
                		mMatrixA.Store(aWorkLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aWorkLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                }
            }
        
            for (std::size_t i = 0U; i < static_cast<std::size_t>(S_BLOCK); i += 1U) {
                aMatrixOperationIndex = 0U;
                aMatrixWriteIndex = 0U;
            }
        
            for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
                aMatrixSlotA = aIndexList256C[(aMatrixDiffusionIndex) & S_BLOCK1];
                aMatrixSlotB = aIndexList256D[(aMatrixDiffusionIndex) & S_BLOCK1];
                aMatrixLoadIndexA = (aMatrixSlotA * 128U) + 64U;
                aMatrixLoadIndexB = aMatrixSlotB * 128U;
                mMatrixA.LoadAndReset(aWorkLaneA + aMatrixLoadIndexA);
                mMatrixB.LoadAndReset(aWorkLaneA + aMatrixLoadIndexB);
                aMatrixDiffusionSelect = aOperationLaneA[(aMatrixOperationIndex) & S_BLOCK1];
                switch (aMatrixDiffusionSelect % 3U) {
                	case 0U: {
                		mMatrixA.RotateLeft(0U, 0U);
                		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapRows(aMatrixArgA, aMatrixArgB);
                		mMatrixB.RotateLeft(0U, 0U);
                		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapRows(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
                		aMatrixStoreIndexB = aMatrixWriteIndex;
                		mMatrixA.Store(aWorkLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aWorkLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                	case 1U: {
                		mMatrixA.RotateLeft(0U, 0U);
                		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapCols(aMatrixArgA, aMatrixArgB);
                		mMatrixB.RotateRight(0U, 0U);
                		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapColsOdd(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
                		aMatrixStoreIndexB = aMatrixWriteIndex;
                		mMatrixA.Store(aWorkLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aWorkLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                	case 2U: {
                		mMatrixA.TransposeMainDiagonal(0U, 0U);
                		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1];
                		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1];
                		mMatrixA.SwapRowsEven(aMatrixArgA, aMatrixArgB);
                		mMatrixB.FlipVertical(0U, 0U);
                		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1];
                		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1];
                		mMatrixB.SwapRowsOdd(aMatrixArgC, aMatrixArgD);
                		aMatrixKindA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1];
                		aMatrixKindB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1];
                		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
                		aMatrixStoreIndexB = aMatrixWriteIndex;
                		mMatrixA.Store(aWorkLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixKindA);
                		mMatrixB.Store(aWorkLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixKindB);
                		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
                		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
                		break;
                	}
                }
            }
    }
}

void TwistExpander_Carbon::Seed(TwistWorkSpace *pWorkspace,
                                 TwistFarmSBox *pFarmSBox,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint64_t pNonce,
                                 std::uint8_t *pSourceInput,
                                 std::uint8_t *pPassword,
                                 unsigned int pPasswordByteLength) {
    TwistExpander::Seed(pWorkspace, pFarmSBox, pFarmSalt, pNonce, pSourceInput, pPassword, pPasswordByteLength);
    if (pWorkspace == nullptr) { return; }
    [[maybe_unused]] std::uint8_t *pSource = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(0));
    [[maybe_unused]] std::uint8_t *pDestination = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(1));
    [[maybe_unused]] std::uint64_t *aOrbiterSaltA = pDomainSaltSet->mOrbiter.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltB = pDomainSaltSet->mOrbiter.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltC = pDomainSaltSet->mOrbiter.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltD = pDomainSaltSet->mOrbiter.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltE = pDomainSaltSet->mOrbiter.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltF = pDomainSaltSet->mOrbiter.mSaltF;
    [[maybe_unused]] std::uint64_t *aUnwindSaltA = pDomainSaltSet->mUnwind.mSaltA;
    [[maybe_unused]] std::uint64_t *aUnwindSaltB = pDomainSaltSet->mUnwind.mSaltB;
    [[maybe_unused]] std::uint64_t *aUnwindSaltC = pDomainSaltSet->mUnwind.mSaltC;
    [[maybe_unused]] std::uint64_t *aUnwindSaltD = pDomainSaltSet->mUnwind.mSaltD;
    [[maybe_unused]] std::uint64_t *aUnwindSaltE = pDomainSaltSet->mUnwind.mSaltE;
    [[maybe_unused]] std::uint64_t *aUnwindSaltF = pDomainSaltSet->mUnwind.mSaltF;
    [[maybe_unused]] std::uint8_t *mSBoxA = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(30));
    [[maybe_unused]] std::uint8_t *mSBoxB = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(31));
    [[maybe_unused]] std::uint8_t *mSBoxC = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(32));
    [[maybe_unused]] std::uint8_t *mSBoxD = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(33));
    [[maybe_unused]] std::uint8_t *mSBoxE = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(34));
    [[maybe_unused]] std::uint8_t *mSBoxF = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(35));
    [[maybe_unused]] std::uint8_t *mSBoxG = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(36));
    [[maybe_unused]] std::uint8_t *mSBoxH = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(37));
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkspace->mListExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkspace->mListExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkspace->mListExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkspace->mListExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aExpandLaneE = pWorkspace->mListExpansionLaneE;
    [[maybe_unused]] std::uint8_t *aExpandLaneF = pWorkspace->mListExpansionLaneF;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneE = pWorkspace->mWorkLaneE;
    [[maybe_unused]] std::uint8_t *aWorkLaneF = pWorkspace->mWorkLaneF;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkspace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkspace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkspace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkspace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneE = pWorkspace->mOperationLaneE;
    [[maybe_unused]] std::uint8_t *aOperationLaneF = pWorkspace->mOperationLaneF;
    [[maybe_unused]] std::uint8_t *aMaskLaneA = pWorkspace->mMaskLaneA;
    [[maybe_unused]] std::uint8_t *aMaskLaneB = pWorkspace->mMaskLaneB;
    [[maybe_unused]] std::size_t *aIndexList256A = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(190)));
    [[maybe_unused]] std::size_t *aIndexList256B = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(191)));
    [[maybe_unused]] std::size_t *aIndexList256C = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(192)));
    [[maybe_unused]] std::size_t *aIndexList256D = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(193)));
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledB = &(pWorkspace->mMaskBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadA = &(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadB = &(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteB = &(pWorkspace->mMaskBoxB[0][0]);

    // [phase ii]

}

void TwistExpander_Carbon::TwistBlock(TwistWorkSpace *pWorkspace,
                                       std::uint64_t pNonce,
                                       std::uint8_t *pSourceInput,
                                       std::uint8_t *pDestinationOutput) {
    TwistExpander::TwistBlock(pWorkspace, pNonce, pSourceInput, pDestinationOutput);
    if ((pWorkspace == nullptr) || (pDestinationOutput == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *pSource = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(0));
    [[maybe_unused]] std::uint8_t *pDestination = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(1));
    [[maybe_unused]] std::uint64_t *aOrbiterSaltA = pDomainSaltSet->mOrbiter.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltB = pDomainSaltSet->mOrbiter.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltC = pDomainSaltSet->mOrbiter.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltD = pDomainSaltSet->mOrbiter.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltE = pDomainSaltSet->mOrbiter.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterSaltF = pDomainSaltSet->mOrbiter.mSaltF;
    [[maybe_unused]] std::uint64_t *aUnwindSaltA = pDomainSaltSet->mUnwind.mSaltA;
    [[maybe_unused]] std::uint64_t *aUnwindSaltB = pDomainSaltSet->mUnwind.mSaltB;
    [[maybe_unused]] std::uint64_t *aUnwindSaltC = pDomainSaltSet->mUnwind.mSaltC;
    [[maybe_unused]] std::uint64_t *aUnwindSaltD = pDomainSaltSet->mUnwind.mSaltD;
    [[maybe_unused]] std::uint64_t *aUnwindSaltE = pDomainSaltSet->mUnwind.mSaltE;
    [[maybe_unused]] std::uint64_t *aUnwindSaltF = pDomainSaltSet->mUnwind.mSaltF;
    [[maybe_unused]] std::uint8_t *mSBoxA = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(30));
    [[maybe_unused]] std::uint8_t *mSBoxB = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(31));
    [[maybe_unused]] std::uint8_t *mSBoxC = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(32));
    [[maybe_unused]] std::uint8_t *mSBoxD = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(33));
    [[maybe_unused]] std::uint8_t *mSBoxE = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(34));
    [[maybe_unused]] std::uint8_t *mSBoxF = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(35));
    [[maybe_unused]] std::uint8_t *mSBoxG = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(36));
    [[maybe_unused]] std::uint8_t *mSBoxH = TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(37));
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkspace->mListExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkspace->mListExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkspace->mListExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkspace->mListExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aExpandLaneE = pWorkspace->mListExpansionLaneE;
    [[maybe_unused]] std::uint8_t *aExpandLaneF = pWorkspace->mListExpansionLaneF;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneE = pWorkspace->mWorkLaneE;
    [[maybe_unused]] std::uint8_t *aWorkLaneF = pWorkspace->mWorkLaneF;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkspace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkspace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkspace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkspace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneE = pWorkspace->mOperationLaneE;
    [[maybe_unused]] std::uint8_t *aOperationLaneF = pWorkspace->mOperationLaneF;
    [[maybe_unused]] std::uint8_t *aMaskLaneA = pWorkspace->mMaskLaneA;
    [[maybe_unused]] std::uint8_t *aMaskLaneB = pWorkspace->mMaskLaneB;
    [[maybe_unused]] std::size_t *aIndexList256A = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(190)));
    [[maybe_unused]] std::size_t *aIndexList256B = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(191)));
    [[maybe_unused]] std::size_t *aIndexList256C = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(192)));
    [[maybe_unused]] std::size_t *aIndexList256D = reinterpret_cast<std::size_t *>(TwistWorkSpace::GetBuffer(pWorkspace, this, static_cast<TwistWorkSpaceSlot>(193)));
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkspace->mKeyBoxA[H_KEY_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkspace->mKeyBoxB[H_KEY_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteA = &(pWorkspace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteB = &(pWorkspace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledB = &(pWorkspace->mMaskBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadA = &(pWorkspace->mMaskBoxA[H_MASK_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadB = &(pWorkspace->mMaskBoxB[H_MASK_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteA = &(pWorkspace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteB = &(pWorkspace->mMaskBoxB[0][0]);

    std::memcpy(pDestinationOutput, pWorkspace->mWorkLaneD, S_BLOCK);
}
