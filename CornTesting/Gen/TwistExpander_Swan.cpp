#include "TwistExpander_Swan.hpp"
#include "TwistFunctional.hpp"
#include "TwistMasking.hpp"
#include "TwistMix64.hpp"
#include "TwistSnow.hpp"
#include "TwistMemory.hpp"
#include "TwistCryptoGenerator.hpp"

#include <cstring>

const std::uint8_t TwistExpander_Swan::kSBoxA[S_SBOX] = {
    0xA3, 0x6D, 0xF0, 0x56, 0x35, 0x3D, 0x05, 0xDB, 0x19, 0x27, 0x9B, 0xEF, 0x93, 0x58, 0xF9, 0x1B, 
    0x7E, 0x32, 0x7D, 0x86, 0xAB, 0x00, 0x25, 0xDD, 0x29, 0x5B, 0x8C, 0xC1, 0x17, 0x5C, 0x23, 0x08, 
    0x34, 0x90, 0xB2, 0xA2, 0xC9, 0xBC, 0xE6, 0xAE, 0x21, 0xB7, 0x65, 0x36, 0x20, 0xFD, 0xF2, 0x74, 
    0xF4, 0x33, 0x71, 0x0B, 0x39, 0x61, 0x1F, 0xC7, 0xF7, 0x4F, 0xDA, 0x5E, 0x2B, 0x49, 0xE7, 0x18, 
    0xB9, 0xD9, 0xD4, 0xD1, 0x3A, 0xEE, 0x03, 0x64, 0x9D, 0x84, 0xB3, 0x0C, 0x07, 0xB5, 0xD7, 0xE2, 
    0x76, 0x88, 0xCC, 0xFB, 0x72, 0x7B, 0xE4, 0xE8, 0xD6, 0x95, 0x41, 0x6C, 0x68, 0xB8, 0xEB, 0xAD, 
    0x63, 0x13, 0x12, 0x40, 0x1D, 0x53, 0x1A, 0x09, 0xCD, 0xA8, 0x24, 0x6E, 0x75, 0xBF, 0x14, 0xFA, 
    0x9E, 0x67, 0x1E, 0x7F, 0x59, 0xFC, 0x87, 0x0E, 0xA9, 0xDF, 0x15, 0x99, 0xA7, 0x78, 0xDE, 0x8B, 
    0x45, 0x6A, 0xA4, 0x10, 0xD0, 0x8A, 0x26, 0x9C, 0x30, 0x5F, 0x85, 0x54, 0x98, 0x38, 0xD2, 0xC8, 
    0xA0, 0x31, 0xBB, 0xC5, 0x9A, 0x04, 0xB1, 0x44, 0xCE, 0xF8, 0x91, 0x9F, 0x2D, 0x3B, 0x51, 0xFE, 
    0xB6, 0xF1, 0x6F, 0xBA, 0x6B, 0x1C, 0x4A, 0xD3, 0xE0, 0x60, 0xC2, 0x48, 0x5A, 0x62, 0x8E, 0xBE, 
    0x8D, 0x96, 0x22, 0xED, 0x97, 0xB0, 0x50, 0x11, 0x06, 0xA5, 0xE5, 0xC0, 0x73, 0xBD, 0x2A, 0x52, 
    0x79, 0x55, 0xA1, 0x3C, 0x01, 0xB4, 0x37, 0xD8, 0x28, 0x2E, 0xF3, 0x02, 0x83, 0x42, 0x47, 0xAC, 
    0xCB, 0x57, 0xDC, 0x70, 0x80, 0xCF, 0x0D, 0x82, 0x4B, 0xCA, 0x4E, 0x7A, 0x0A, 0xE3, 0xEA, 0xFF, 
    0x5D, 0x43, 0x2F, 0x4C, 0xD5, 0x16, 0x94, 0x89, 0x2C, 0xE9, 0xE1, 0xC3, 0x46, 0xA6, 0xEC, 0xC6, 
    0x7C, 0x8F, 0xAF, 0x81, 0xAA, 0x66, 0xF6, 0x3E, 0xF5, 0xC4, 0x3F, 0x69, 0x0F, 0x4D, 0x92, 0x77
};

const std::uint8_t TwistExpander_Swan::kSBoxB[S_SBOX] = {
    0xD9, 0x36, 0xBB, 0x19, 0x3D, 0x8A, 0x7B, 0x20, 0x62, 0x29, 0x28, 0x7C, 0x9F, 0x14, 0x72, 0xC2, 
    0x5C, 0xF9, 0x82, 0x4F, 0x6E, 0x1F, 0x89, 0x9A, 0x24, 0xCA, 0x58, 0x83, 0x6F, 0x0E, 0x33, 0xA8, 
    0x43, 0x41, 0x13, 0xA7, 0x34, 0x1E, 0xB5, 0x0A, 0x93, 0x77, 0x81, 0xE3, 0xED, 0x68, 0x1B, 0x4B, 
    0xA1, 0x87, 0x2F, 0x76, 0x90, 0x9B, 0xD8, 0x39, 0x7F, 0x64, 0x5E, 0xAE, 0x84, 0xDE, 0xCB, 0x1C, 
    0x7A, 0x80, 0x53, 0x37, 0x4E, 0x02, 0xC1, 0xFF, 0x92, 0xEF, 0x6D, 0xB2, 0xDB, 0xD7, 0x8D, 0xAF, 
    0xEB, 0x42, 0x50, 0xD2, 0xF1, 0x38, 0x15, 0xB8, 0xF3, 0x25, 0x69, 0x48, 0x52, 0x04, 0x66, 0xD4, 
    0x3B, 0x75, 0x0B, 0x17, 0x78, 0x7D, 0xBC, 0xD6, 0x2E, 0xB0, 0xF7, 0xE8, 0x35, 0xC0, 0xB1, 0xAC, 
    0x4C, 0x21, 0xA6, 0x22, 0x6A, 0x16, 0x31, 0x12, 0xCE, 0x3A, 0xCF, 0x88, 0xC3, 0xE6, 0x44, 0x9C, 
    0x73, 0xF2, 0x1D, 0xAB, 0x49, 0xE2, 0x57, 0xEC, 0x59, 0xD0, 0x91, 0xB9, 0xF6, 0xEE, 0xE9, 0x4A, 
    0x07, 0x27, 0xDA, 0x99, 0x56, 0x05, 0xCD, 0x0D, 0xF0, 0x0C, 0x3F, 0x32, 0x3E, 0x30, 0xDD, 0xB6, 
    0x09, 0xC5, 0x96, 0xA4, 0x8C, 0x06, 0x00, 0x97, 0x0F, 0xE5, 0x5D, 0xA0, 0xB4, 0x45, 0xF8, 0xBE, 
    0x26, 0xFB, 0x4D, 0xDC, 0x85, 0xB3, 0xA3, 0xD5, 0xA5, 0x63, 0x6B, 0xFD, 0x8F, 0x60, 0xFA, 0x03, 
    0x98, 0xC7, 0x79, 0xF4, 0x61, 0xA9, 0x9D, 0xFE, 0x5A, 0xE0, 0x65, 0xBF, 0x2B, 0xB7, 0xD3, 0xAA, 
    0x94, 0x67, 0xE4, 0x51, 0xF5, 0x8E, 0xCC, 0x55, 0x7E, 0xEA, 0x1A, 0x46, 0x08, 0xD1, 0x18, 0xC8, 
    0x70, 0xC9, 0x9E, 0xBA, 0x2D, 0x11, 0x5B, 0x3C, 0x40, 0xC6, 0x71, 0x23, 0xAD, 0xBD, 0xA2, 0x47, 
    0xFC, 0x86, 0x74, 0x8B, 0x10, 0x5F, 0x01, 0x54, 0xDF, 0xE7, 0x2A, 0x2C, 0x6C, 0xC4, 0xE1, 0x95
};

const std::uint8_t TwistExpander_Swan::kSBoxC[S_SBOX] = {
    0x85, 0xE8, 0xA6, 0xF2, 0x61, 0x7C, 0xD1, 0x09, 0x68, 0xC1, 0x28, 0xA8, 0x35, 0xEB, 0x19, 0x7D, 
    0xEA, 0xC7, 0x5D, 0x33, 0x98, 0x62, 0xD4, 0x0D, 0xD8, 0x5C, 0x3B, 0xB4, 0x71, 0xFA, 0xD0, 0x7F, 
    0xC3, 0x82, 0x92, 0x27, 0xA9, 0x8B, 0x17, 0x2B, 0xC5, 0x21, 0xF5, 0xD6, 0x67, 0x08, 0xB3, 0xE2, 
    0xB7, 0x65, 0x51, 0xC8, 0x6D, 0xE4, 0x6C, 0xB0, 0x00, 0xF8, 0xAB, 0xEF, 0xCD, 0xFC, 0xB5, 0xCA, 
    0x38, 0x1C, 0xB2, 0x01, 0xDA, 0x0A, 0xD5, 0x57, 0x2C, 0x26, 0x30, 0x6E, 0xC4, 0x34, 0x05, 0x06, 
    0xF7, 0x2A, 0x1A, 0x0C, 0xE6, 0x59, 0x02, 0x0E, 0xA7, 0x31, 0xE1, 0x4A, 0x5B, 0x9A, 0xB9, 0x9C, 
    0xF1, 0x60, 0xC2, 0x43, 0x79, 0x41, 0xDF, 0xDD, 0xB8, 0x2F, 0x76, 0x5F, 0x40, 0x3C, 0xC6, 0xAE, 
    0x9B, 0xE0, 0xCE, 0x48, 0x49, 0xAA, 0x91, 0x7B, 0x8D, 0x18, 0x64, 0x3D, 0x94, 0xEE, 0xBA, 0x9D, 
    0xF0, 0x4E, 0x23, 0xD7, 0xA3, 0x3F, 0x63, 0x8E, 0xD2, 0x4D, 0x84, 0xE7, 0x9F, 0xCF, 0xB6, 0x0B, 
    0x32, 0x70, 0x2D, 0xA5, 0x8A, 0x73, 0x25, 0x52, 0x0F, 0xBB, 0x20, 0x39, 0xC9, 0x78, 0x54, 0xBF, 
    0x83, 0x04, 0xFD, 0x8F, 0xEC, 0xDB, 0x4B, 0x14, 0x13, 0x46, 0x03, 0x5E, 0xFE, 0x53, 0x2E, 0x9E, 
    0x99, 0x86, 0x72, 0xBD, 0x24, 0x87, 0xF6, 0x75, 0x66, 0x81, 0xA0, 0x16, 0x44, 0x29, 0x6F, 0xE3, 
    0x4C, 0x45, 0x90, 0xDE, 0xC0, 0x96, 0x74, 0xBE, 0x7A, 0x7E, 0x11, 0x77, 0x80, 0x56, 0xE5, 0x3E, 
    0xBC, 0x50, 0xAF, 0xF3, 0x37, 0xAD, 0xCC, 0x22, 0xE9, 0x1E, 0x5A, 0xFB, 0x6A, 0xA4, 0x1B, 0x1D, 
    0x58, 0xF4, 0xDC, 0x4F, 0x10, 0xD3, 0x93, 0x88, 0x6B, 0xAC, 0xB1, 0xA1, 0x47, 0x36, 0x1F, 0x12, 
    0xFF, 0x8C, 0x89, 0x95, 0x3A, 0x42, 0xA2, 0xCB, 0x15, 0x07, 0x69, 0xF9, 0xD9, 0xED, 0x97, 0x55
};

const std::uint8_t TwistExpander_Swan::kSBoxD[S_SBOX] = {
    0x42, 0xA5, 0x3F, 0x66, 0x3A, 0x39, 0x1B, 0xE4, 0xE5, 0x0E, 0x60, 0x20, 0x63, 0xAC, 0xF1, 0xC9, 
    0x5C, 0x3E, 0xBD, 0x53, 0x41, 0x33, 0x22, 0x2D, 0xC4, 0x4D, 0x7C, 0xD3, 0x2F, 0x49, 0xEB, 0x30, 
    0xF7, 0x82, 0x97, 0x8F, 0xD0, 0x5D, 0xEE, 0x69, 0xC7, 0xBF, 0xA6, 0xDB, 0x0A, 0x14, 0x13, 0x73, 
    0xDA, 0xF3, 0x5B, 0xD1, 0xDC, 0x43, 0x2C, 0x1A, 0x3B, 0xB0, 0x29, 0x65, 0xE8, 0x79, 0x23, 0x28, 
    0x75, 0xC8, 0xE3, 0xCB, 0x3D, 0xED, 0xD2, 0x6B, 0xA9, 0x7F, 0x5A, 0xD5, 0x37, 0x93, 0x02, 0x0B, 
    0x5F, 0x99, 0xF8, 0xDD, 0xBA, 0x74, 0xC2, 0x24, 0xCF, 0xAA, 0x7A, 0x68, 0x8D, 0xB8, 0xC5, 0x88, 
    0x6F, 0xCA, 0x07, 0xB7, 0x00, 0x4E, 0x04, 0xFD, 0x35, 0xA0, 0xEF, 0x44, 0xBE, 0xBC, 0xCE, 0x10, 
    0x48, 0x8A, 0xE1, 0x91, 0x61, 0xD9, 0x9E, 0xF9, 0x6D, 0x01, 0x03, 0x4C, 0xA7, 0x95, 0xCC, 0x78, 
    0x9F, 0xA1, 0x46, 0x2B, 0x06, 0xB5, 0xC3, 0x64, 0x12, 0xA8, 0xB2, 0x4A, 0x81, 0x11, 0x2A, 0x1D, 
    0xA3, 0xDF, 0x59, 0x36, 0xAD, 0xD6, 0x76, 0x52, 0xD4, 0x3C, 0x4F, 0x85, 0x21, 0xF0, 0x62, 0xF5, 
    0x72, 0xF2, 0x89, 0x94, 0x6C, 0xCD, 0x98, 0xE7, 0x27, 0x8E, 0x32, 0xB4, 0x80, 0xA2, 0x50, 0x71, 
    0xB1, 0x4B, 0x26, 0x0C, 0x86, 0xBB, 0xAF, 0xE6, 0xFA, 0x8B, 0x0F, 0x1E, 0x77, 0x90, 0x25, 0x83, 
    0x58, 0x87, 0x6E, 0xF4, 0xFE, 0x5E, 0x16, 0x05, 0x09, 0xC0, 0xDE, 0x1F, 0x7B, 0x9B, 0xB3, 0x45, 
    0xFC, 0xAB, 0xE0, 0x96, 0x9A, 0x19, 0x18, 0xB6, 0x55, 0x31, 0x7D, 0xB9, 0x1C, 0xC6, 0x08, 0x38, 
    0x84, 0x56, 0x0D, 0x51, 0x2E, 0xE2, 0x67, 0x54, 0xEC, 0xE9, 0xEA, 0xFF, 0x7E, 0x6A, 0xC1, 0xD7, 
    0x70, 0x9D, 0xA4, 0x57, 0x8C, 0x47, 0xF6, 0xD8, 0x17, 0xFB, 0x15, 0x40, 0x34, 0x9C, 0xAE, 0x92
};

const std::uint8_t TwistExpander_Swan::kSaltA[S_SALT] = {
    0xAE, 0x72, 0xBF, 0x7E, 0x78, 0x4C, 0x8C, 0x51, 0xDC, 0xC9, 0xD9, 0xB4, 0x3A, 0xB7, 0x04, 0x8F, 
    0xD7, 0xC3, 0xE4, 0x03, 0xBE, 0xE6, 0x20, 0x65, 0x12, 0xA5, 0xBA, 0x5D, 0x5D, 0x85, 0x4F, 0xA8, 
    0x94, 0xDE, 0xDB, 0x9A, 0xB3, 0x5B, 0xFF, 0xAB, 0xE3, 0xB7, 0xFD, 0x70, 0x20, 0x4F, 0xAB, 0x34, 
    0x7A, 0xB2, 0xF4, 0x85, 0x7E, 0x76, 0x6F, 0xD5, 0xD2, 0x0D, 0x5F, 0x59, 0xEE, 0xFB, 0x8C, 0x1C, 
    0x61, 0x67, 0x17, 0x1C, 0x8B, 0xFE, 0x21, 0xE4, 0x64, 0x6D, 0x0C, 0x03, 0x9F, 0xE6, 0xB6, 0x88, 
    0x5C, 0xB7, 0x2D, 0xD6, 0xD7, 0xE0, 0x30, 0x59, 0xA6, 0x38, 0x13, 0xA5, 0x23, 0xF9, 0x9D, 0xF2, 
    0x31, 0xAF, 0xCD, 0x56, 0x7E, 0x92, 0xF0, 0x38, 0x91, 0xFD, 0xAA, 0x0D, 0xAC, 0xD5, 0x7B, 0x58, 
    0x04, 0x74, 0x82, 0x8C, 0xC6, 0x54, 0x12, 0xE8, 0xBB, 0x8E, 0xA0, 0xEF, 0x97, 0x65, 0xAC, 0xBB
};

const std::uint8_t TwistExpander_Swan::kSaltB[S_SALT] = {
    0xBF, 0x76, 0x16, 0x59, 0x59, 0x34, 0x00, 0x87, 0x85, 0xDD, 0x5E, 0x75, 0xE9, 0x41, 0x97, 0x65, 
    0x24, 0xC9, 0xD2, 0x67, 0x40, 0x6B, 0x04, 0xD2, 0xA6, 0x39, 0xBB, 0xDD, 0xDE, 0xB0, 0xE2, 0xBE, 
    0x03, 0x73, 0x90, 0xEC, 0x3E, 0xD5, 0xDA, 0xCE, 0xBF, 0x25, 0x2A, 0x38, 0x31, 0xA1, 0x46, 0x01, 
    0x84, 0x30, 0xA4, 0x45, 0xD1, 0xDA, 0xCD, 0x9A, 0xA2, 0x8C, 0x14, 0x2E, 0x73, 0xEC, 0x19, 0x4E, 
    0xDD, 0xE0, 0xCE, 0x65, 0xA0, 0x03, 0x82, 0x15, 0x80, 0xC6, 0xC3, 0x8B, 0x40, 0x29, 0x4C, 0x7E, 
    0xC6, 0xD0, 0x91, 0xA2, 0x50, 0xB3, 0x94, 0x8C, 0xEC, 0x82, 0xDD, 0xC6, 0x0D, 0xDB, 0xD4, 0x29, 
    0x75, 0x84, 0x21, 0x19, 0x1A, 0xAD, 0xF8, 0x40, 0xC9, 0xFE, 0xE3, 0x8B, 0x4B, 0x9F, 0xEA, 0xE4, 
    0x52, 0x9C, 0x64, 0xC2, 0xD5, 0x37, 0x0D, 0xE2, 0x25, 0x7A, 0x7D, 0x0D, 0x08, 0xCE, 0xE4, 0x5D
};

const std::uint8_t TwistExpander_Swan::kSaltC[S_SALT] = {
    0xC2, 0x0D, 0xA5, 0xAF, 0x81, 0x6F, 0xF3, 0x38, 0x0D, 0x8C, 0xB9, 0x8B, 0x69, 0x93, 0x1D, 0x13, 
    0xDA, 0x04, 0x51, 0xA6, 0xC8, 0x43, 0x72, 0x13, 0x86, 0x93, 0xBE, 0x6A, 0x7D, 0x3D, 0xA9, 0x4A, 
    0x22, 0x85, 0x25, 0xE5, 0x0B, 0x88, 0x83, 0xE5, 0xC6, 0x6E, 0x89, 0x8A, 0x4A, 0x56, 0x7F, 0x25, 
    0x79, 0x0C, 0xE8, 0xDA, 0x61, 0x07, 0x72, 0x0A, 0x3B, 0x5F, 0xC8, 0x70, 0xF3, 0x5B, 0x6B, 0x38, 
    0x39, 0x21, 0xDA, 0xBD, 0xDD, 0xBD, 0x41, 0xE3, 0xAF, 0x0E, 0x14, 0x25, 0xD0, 0x55, 0x27, 0x01, 
    0x84, 0xBC, 0xEE, 0x92, 0xAE, 0x6B, 0x4C, 0x52, 0xAD, 0x89, 0x5E, 0xEF, 0x6E, 0x30, 0x18, 0xD8, 
    0x14, 0x65, 0x2C, 0x05, 0x02, 0xDA, 0x32, 0xD8, 0x17, 0x0D, 0xEE, 0x90, 0xDA, 0x6D, 0xD8, 0xC3, 
    0x9C, 0xC1, 0x86, 0x97, 0x72, 0x2A, 0x00, 0xAC, 0x00, 0xC4, 0xA9, 0x67, 0x56, 0xD8, 0x91, 0x9D
};

const std::uint8_t TwistExpander_Swan::kSaltD[S_SALT] = {
    0x0C, 0xE1, 0x11, 0xD3, 0x42, 0xDF, 0x10, 0xA8, 0xB4, 0x29, 0xAB, 0xC7, 0x97, 0x4F, 0xA6, 0xFB, 
    0xE6, 0xF6, 0xC8, 0x48, 0xC8, 0xF4, 0xD4, 0x24, 0x6F, 0x06, 0x6A, 0x0F, 0x87, 0x86, 0xF0, 0x93, 
    0x4A, 0x66, 0x6A, 0x48, 0x43, 0x76, 0x98, 0x12, 0xAC, 0x3D, 0xB7, 0x7A, 0xAC, 0x29, 0xAC, 0xE5, 
    0x07, 0xA7, 0x15, 0xD8, 0xAF, 0x86, 0xEF, 0x37, 0xFD, 0x0D, 0x9C, 0x0F, 0xC3, 0x22, 0x4E, 0xF4, 
    0xD3, 0xB6, 0x96, 0x66, 0x77, 0xB9, 0x1E, 0x1F, 0x90, 0x6B, 0x49, 0xF0, 0xEA, 0xC9, 0x20, 0x2A, 
    0x1C, 0xC2, 0x2F, 0xE6, 0x74, 0xA8, 0xC5, 0xBF, 0x68, 0xC8, 0x52, 0x0E, 0xD8, 0xE8, 0xC6, 0x84, 
    0x37, 0x8C, 0x5B, 0xD9, 0xFD, 0xBB, 0xBE, 0x11, 0x3C, 0x9C, 0xCF, 0xD8, 0x7D, 0x6E, 0x6B, 0x5F, 
    0x50, 0x64, 0x86, 0x06, 0xCB, 0x15, 0x1A, 0xF3, 0x05, 0x7A, 0xCB, 0x23, 0xCB, 0x94, 0x0B, 0xAF
};

TwistExpander_Swan::TwistExpander_Swan()
: TwistExpander() {
    std::memcpy(mSBoxA, kSBoxA, sizeof(mSBoxA));
    std::memcpy(mSBoxB, kSBoxB, sizeof(mSBoxB));
    std::memcpy(mSBoxC, kSBoxC, sizeof(mSBoxC));
    std::memcpy(mSBoxD, kSBoxD, sizeof(mSBoxD));
    std::memcpy(mSaltA, kSaltA, sizeof(mSaltA));
    std::memcpy(mSaltB, kSaltB, sizeof(mSaltB));
    std::memcpy(mSaltC, kSaltC, sizeof(mSaltC));
    std::memcpy(mSaltD, kSaltD, sizeof(mSaltD));
}

void TwistExpander_Swan::Seed(TwistWorkSpace *pWorkspace,
                                 TwistCryptoGenerator *pCryptoGenerator,
                                 std::uint8_t *pSource,
                                 std::uint8_t *pPassword,
                                 unsigned int pPasswordByteLength) {
    TwistExpander::Seed(pWorkspace, pCryptoGenerator, pSource, pPassword, pPasswordByteLength);
    if ((pWorkspace == nullptr) || (pCryptoGenerator == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aDerivedSaltA = pWorkspace->mDerivedSaltA;
    [[maybe_unused]] std::uint8_t *aDerivedSaltB = pWorkspace->mDerivedSaltB;
    [[maybe_unused]] std::uint8_t *aDerivedSaltC = pWorkspace->mDerivedSaltC;
    [[maybe_unused]] std::uint8_t *aDerivedSaltD = pWorkspace->mDerivedSaltD;
    [[maybe_unused]] std::uint8_t *aDerivedSBoxA = pWorkspace->mDerivedSBoxA;
    [[maybe_unused]] std::uint8_t *aDerivedSBoxB = pWorkspace->mDerivedSBoxB;
    [[maybe_unused]] std::uint8_t *aDerivedSBoxC = pWorkspace->mDerivedSBoxC;
    [[maybe_unused]] std::uint8_t *aDerivedSBoxD = pWorkspace->mDerivedSBoxD;
    [[maybe_unused]] std::uint8_t *aDerivedSBoxE = pWorkspace->mDerivedSBoxE;
    [[maybe_unused]] std::uint8_t *aDerivedSBoxF = pWorkspace->mDerivedSBoxF;
    [[maybe_unused]] std::uint8_t *aDerivedSBoxG = pWorkspace->mDerivedSBoxG;
    [[maybe_unused]] std::uint8_t *aDerivedSBoxH = pWorkspace->mDerivedSBoxH;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkspace->mExpandLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aMaskLaneA = pWorkspace->mMaskLaneA;
    [[maybe_unused]] std::uint8_t *aMaskLaneB = pWorkspace->mMaskLaneB;
    std::uint64_t aPrevious = 0;
    std::uint64_t aCurrent = 0;
    std::uint64_t aCross = 0;
    std::uint64_t aScatter = 0;
    std::uint64_t aOrbitA = 0;
    std::uint64_t aWandererD = 0;
    std::uint64_t aOrbitD = 0;
    std::uint64_t aWandererC = 0;
    std::uint64_t aOrbitB = 0;
    std::uint64_t aWandererA = 0;
    std::uint64_t aOrbitC = 0;
    std::uint64_t aCarry = 0;
    std::uint64_t aPrism = 0;
    std::uint64_t aWandererB = 0;

    // Making snow counter: sha 256

    TwistSnow::Sha256Counter(pSource, aExpandLaneA);

    TwistMemory::GrowA(mScratchSaltC, mSaltD, 128U);
    TwistMemory::GrowB(mScratchSaltD, mSaltA, 128U);
    TwistMemory::GrowA(mScratchSaltB, mSaltB, 128U);
    TwistMemory::GrowB(mScratchSaltA, mSaltC, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = pSource[aIndex] ^ ShiftL64(aExpandLaneA[aIndex], 32U);
        aCross = pSource[S_BLOCK1 - aIndex];
        // __START_CSPRNG
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // scatter = mix(secure_a, secure_b, previous)
        //
        aScatter = TwistMix64::DiffuseA(ShiftL64(aCurrent, 32U) ^ aCross ^ RotL64(aPrevious, 27U));
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = s0 + rot(e) + hot.add + plug[+];
        // b = s1 ^ rot(previous) ^ hot.add ^ plug[^];
        // c = s2 + rot(cross) + fixedSalt[i/~i] + scratchSalt[~i/i];
        // d = rot(carry) ^ rot(e) ^ fixedSalt[i/~i] ^ scratchSalt[~i/i];
        // prism = e;
        //
        aOrbitA = aWandererD + RotL64(aCurrent, 21U) + 11485895248911681988ULL + mScratchSaltA[((RotL64(aOrbitD, 19U) ^ aScatter) & 0x7FU)];
        aOrbitD = aWandererC ^ RotL64(aPrevious, 11U) ^ 14920038357032574275ULL ^ mScratchSaltD[((RotL64(aScatter, 29U)) & 0x7FU)];
        aOrbitB = aWandererA + RotL64(aCross, 43U) + mSaltA[((127U - aIndex + 88U) & 0x7FU)] + mScratchSaltC[((aIndex + 69U) & 0x7FU)];
        aOrbitC = RotL64(aCarry, 35U) ^ RotL64(aCurrent, 13U) ^ mSaltC[((127U - aIndex + 119U) & 0x7FU)] ^ mScratchSaltB[((aIndex) & 0x7FU)];
        aPrism = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(c) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitD + 10838585322428158401ULL + mScratchSaltA[((RotL64(aCarry, 27U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitA ^ 5567189662769751117ULL ^ mScratchSaltD[((RotL64(aOrbitB, 21U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 13208232816597414417ULL, 53U);
        aPrism = (aPrism ^ aOrbitB ^ 1361080143828896873ULL) * 16790423471438019125ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b);
        // prism = (prism OP mix(a) OP hot.add) * hot.mul;
        //
        aOrbitB = aOrbitB + aOrbitC + 2464501967500236940ULL + mScratchSaltC[((aOrbitA ^ RotL64(aWandererC, 19U)) & 0x7FU)];
        aOrbitD = aOrbitD ^ aOrbitB ^ 5263557667919325332ULL ^ mScratchSaltA[((RotL64(aCross, 11U) ^ aPrevious) & 0x7FU)];
        aOrbitD = RotL64(aOrbitD, 37U);
        aPrism = (aPrism + RotL64(aOrbitA, 1U) + 9175443209581358167ULL) * 17548486783204565571ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(b) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitD + 11485895248911681988ULL + mScratchSaltB[((aWandererA + RotL64(aOrbitC, 29U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitA ^ 14920038357032574275ULL ^ mScratchSaltD[((aScatter ^ RotL64(aOrbitD, 13U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 9380192890223988127ULL, 27U);
        aPrism = (aPrism ^ aOrbitD ^ 10838585322428158401ULL) * 12168220390803441485ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b * hot.mul);
        // prism = (prism OP mix(d) OP hot.add) * hot.mul;
        //
        aOrbitB = aOrbitB + aOrbitC + 5567189662769751117ULL + mScratchSaltC[((aWandererD ^ RotL64(aCarry, 21U)) & 0x7FU)];
        aOrbitD = aOrbitD ^ aOrbitB ^ 1361080143828896873ULL ^ mScratchSaltA[((RotL64(aScatter, 19U) ^ aOrbitA) & 0x7FU)];
        aOrbitD = RotL64(aOrbitD * 16790423471438019125ULL, 45U);
        aPrism = (aPrism + (aOrbitC ^ RotL64(aCarry, 3U)) + 2464501967500236940ULL) * 9851805212166163257ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // e = mix(a, b, c, d)
        // e = diffuse(e OP scatter)
        // dest[i] = e
        //
        aCurrent = (aOrbitA ^ RotL64(aOrbitC, 11U)) + (RotL64(aOrbitD, 29U) ^ aOrbitB);
        aCurrent = TwistMix64::DiffuseB(aCurrent + aScatter);
        aWorkLaneA[aIndex] = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseC(aPrism);
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseB(aPrism);
        if ((aPrism & 0x34U) > 23) {
        	aCurrent = TwistMix64::GateTurnA_4_8(aCurrent, 7ULL, mSBoxA, mSBoxC, mSBoxD, mSBoxB);
        } else {
        	aCurrent = TwistMix64::GateTurnB_4_8(aCurrent, 5ULL, mSBoxA, mSBoxC, mSBoxD, mSBoxB);
        }
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s0 = s0 + (e ^ previous ^ d);
        // s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);
        //
        aWandererD = aWandererD + (RotL64(aCurrent, 13U) ^ aPrevious ^ aOrbitC);
        aWandererD = RotL64((aWandererD + mSaltB[((aIndex + 110U) & 0x7FU)]) * 6871340666482597557ULL, 51U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s1 = s1 ^ (e + cross + a);
        // s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);
        //
        aWandererC = aWandererC ^ (RotL64(aCurrent, 43U) + aCross + aOrbitA);
        aWandererC = RotL64((aWandererC ^ mSaltD[((127U - aIndex + 64U) & 0x7FU)]) * 16994723286938789903ULL, 37U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s2 = s2 + (b ^ c ^ loopSalt[i/~i]);
        // s2 = rot(s2 * hot.mul);
        //
        aWandererA = aWandererA + (RotL64(aOrbitD, 27U) ^ aOrbitB ^ mSaltB[((127U - aIndex + 6U) & 0x7FU)]);
        aWandererA = RotL64(aWandererA * 9380192890223988127ULL, 53U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // carry = carry + (s0 ^ s1 ^ s2 ^ e);
        // carry = rot(carry * hot.mul);
        // carry = carry ^ (carry >> rshift);
        //
        aCarry = aCarry + (aWandererD ^ aWandererC ^ RotL64(aWandererA, 19U) ^ aCurrent);
        aCarry = RotL64(aCarry * 12168220390803441485ULL, 45U);
        aCarry = aCarry ^ ShiftR64(aCarry, 43U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        // __END_CSPRNG
    }

    // Secure zero on crypto buffer.

    TwistMemory::ZeroBlock(aExpandLaneA);

    pCryptoGenerator->Make(aWorkLaneA, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);
    // Making snow counter: aes 256

    TwistSnow::AES256Counter(pSource, aExpandLaneA);

    TwistMemory::GrowB(mScratchSaltB, aDerivedSBoxA, 256U);
    TwistMemory::GrowA(mScratchSaltA, aDerivedSBoxB, 256U);
    TwistMemory::GrowB(mScratchSaltC, aDerivedSBoxC, 256U);
    TwistMemory::GrowA(mScratchSaltD, aDerivedSBoxD, 256U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = aWorkLaneA[aIndex] ^ ShiftL64(aExpandLaneA[S_BLOCK1 - aIndex], 32U);
        aCross = pSource[aIndex];
        // __START_CSPRNG
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // scatter = mix(secure_a, secure_b, previous)
        //
        aScatter = TwistMix64::DiffuseA(aCurrent ^ ShiftL64(aCross, 32U) ^ RotL64(aPrevious, 19U));
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = s0 + rot(e) + hot.add + plug[+];
        // b = s1 ^ rot(previous) ^ hot.add ^ plug[^];
        // c = s2 + rot(cross) + fixedSalt[i/~i] + scratchSalt[~i/i];
        // d = rot(carry) ^ rot(e) ^ fixedSalt[i/~i] ^ scratchSalt[~i/i];
        // prism = e;
        //
        aOrbitA = aWandererA + RotL64(aCurrent, 27U) + 15521246415914331641ULL + mScratchSaltC[((RotL64(aCross, 13U)) & 0x7FU)];
        aOrbitC = aWandererC ^ RotL64(aPrevious, 51U) ^ 5419666458866705453ULL ^ mScratchSaltD[((RotL64(aOrbitA, 29U) + aOrbitD) & 0x7FU)];
        aOrbitD = aWandererD + RotL64(aCross, 21U) + mSaltD[((aIndex + 109U) & 0x7FU)] + mScratchSaltA[((127U - aIndex + 6U) & 0x7FU)];
        aOrbitB = RotL64(aCarry, 11U) ^ RotL64(aCurrent, 5U) ^ mSaltA[((127U - aIndex + 50U) & 0x7FU)] ^ mScratchSaltB[((aIndex + 10U) & 0x7FU)];
        aPrism = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(c) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitC + 11007704106911101577ULL + mScratchSaltC[((aOrbitB ^ RotL64(aPrevious, 19U)) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitA ^ 4094306849101610053ULL ^ mScratchSaltD[((aOrbitC + RotL64(aScatter, 27U)) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB * 15483605997867887605ULL, 53U);
        aPrism = (aPrism + RotL64(aOrbitD, 45U) + 17210233854567752279ULL) * 16892981289298724341ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b);
        // prism = (prism OP mix(a) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitB + 5774814730118353471ULL + mScratchSaltB[((aCarry ^ RotL64(aWandererA, 13U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitD ^ 4219401995832199663ULL ^ mScratchSaltA[((aCross + RotL64(aWandererD, 29U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC, 37U);
        aPrism = (aPrism ^ aOrbitA ^ 8259104953656517472ULL) * 3040552910329273561ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(b) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitC + 15521246415914331641ULL + mScratchSaltD[((RotL64(aScatter, 21U)) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitA ^ 5419666458866705453ULL ^ mScratchSaltC[((RotL64(aOrbitD, 11U)) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB * 15174173875872039267ULL, 19U);
        aPrism = (aPrism + aOrbitC + 11007704106911101577ULL) * 13272062006997598213ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b * hot.mul);
        // prism = (prism OP mix(d) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitB + 4094306849101610053ULL + mScratchSaltA[((aOrbitB ^ RotL64(aPrevious, 27U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitD ^ 17210233854567752279ULL ^ mScratchSaltB[((RotL64(aScatter, 13U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 16892981289298724341ULL, 43U);
        aPrism = (aPrism ^ aOrbitB ^ RotL64(aCarry, 7U) ^ 5774814730118353471ULL) * 651810445117766863ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // e = mix(a, b, c, d)
        // e = diffuse(e OP scatter)
        // dest[~i] = e
        //
        aCurrent = (aOrbitA ^ RotL64(aOrbitC, 29U)) + (RotL64(aOrbitD, 21U) ^ aOrbitB);
        aCurrent = TwistMix64::DiffuseB(aCurrent + aScatter);
        aWorkLaneB[S_BLOCK1 - aIndex] = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseB(aPrism);
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseB(aPrism);
        if ((aPrism & 0x16U) > 14) {
        	aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 35ULL, mSBoxA, aDerivedSBoxC, mSBoxC, aDerivedSBoxB, aDerivedSBoxD, aDerivedSBoxA, mSBoxB, mSBoxD);
        } else {
        	aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 3ULL, mSBoxA, aDerivedSBoxC, mSBoxC, aDerivedSBoxB, aDerivedSBoxD, aDerivedSBoxA, mSBoxB, mSBoxD);
        }
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s0 = s0 + (e ^ previous ^ d);
        // s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);
        //
        aWandererA = aWandererA + (aCurrent ^ RotL64(aPrevious, 11U) ^ aOrbitB);
        aWandererA = RotL64((aWandererA + mSaltC[((aIndex + 62U) & 0x7FU)]) * 6627252959972762187ULL, 51U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s1 = s1 ^ (e + cross + a);
        // s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);
        //
        aWandererC = aWandererC ^ (aCurrent + aCross + RotL64(aOrbitA, 45U));
        aWandererC = RotL64((aWandererC ^ mScratchSaltC[((aIndex + 56U) & 0x7FU)]) * 7823708137943621333ULL, 19U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s2 = s2 + (b ^ c ^ loopSalt[i/~i]);
        // s2 = rot(s2 * hot.mul);
        //
        aWandererD = aWandererD + (RotL64(aOrbitC, 53U) ^ aOrbitD ^ mScratchSaltD[((127U - aIndex + 65U) & 0x7FU)]);
        aWandererD = RotL64(aWandererD * 15174173875872039267ULL, 37U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // carry = carry + (s0 ^ s1 ^ s2 ^ e);
        // carry = rot(carry * hot.mul);
        // carry = carry ^ (carry >> rshift);
        //
        aCarry = aCarry + (aWandererA ^ RotL64(aWandererC, 1U) ^ aWandererD ^ aCurrent);
        aCarry = RotL64(aCarry * 13272062006997598213ULL, 27U);
        aCarry = aCarry ^ ShiftR64(aCarry, 37U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        // __END_CSPRNG
    }

    // Secure zero on crypto buffer.

    TwistMemory::ZeroBlock(aExpandLaneA);

    pCryptoGenerator->Salt(aWorkLaneB, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);
    // Making snow counter: cha cha 20

    TwistSnow::ChaCha20Counter(pSource, aExpandLaneA);

    TwistMemory::GrowA(mScratchSaltA, aDerivedSaltA, 128U);
    TwistMemory::GrowB(mScratchSaltC, aDerivedSaltB, 128U);
    TwistMemory::GrowA(mScratchSaltD, aDerivedSaltC, 128U);
    TwistMemory::GrowB(mScratchSaltB, aDerivedSaltD, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = aWorkLaneB[aIndex] ^ ShiftL64(aExpandLaneA[aIndex], 32U);
        aCross = aWorkLaneA[S_BLOCK1 - aIndex];
        // __START_CSPRNG
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // scatter = mix(secure_a, secure_b, previous)
        //
        aScatter = TwistMix64::DiffuseA(ShiftL64(aCurrent, 32U) ^ aCross ^ RotL64(aPrevious, 21U));
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = s0 + rot(e) + hot.add + plug[+];
        // b = s1 ^ rot(previous) ^ hot.add ^ plug[^];
        // c = s2 + rot(cross) + fixedSalt[i/~i] + scratchSalt[~i/i];
        // d = rot(carry) ^ rot(e) ^ fixedSalt[i/~i] ^ scratchSalt[~i/i];
        // prism = e;
        //
        aOrbitB = aWandererD + RotL64(aCurrent, 3U) + 6297736036819237238ULL + mScratchSaltB[((RotL64(aWandererC, 29U) + aWandererD) & 0x7FU)];
        aOrbitC = aWandererA ^ RotL64(aPrevious, 51U) ^ 6569825217175163526ULL ^ mScratchSaltC[((RotL64(aCarry, 19U)) & 0x7FU)];
        aOrbitD = aWandererC + RotL64(aCross, 43U) + aDerivedSaltD[((aIndex + 119U) & 0x7FU)] + mScratchSaltD[((127U - aIndex + 88U) & 0x7FU)];
        aOrbitA = RotL64(aCarry, 27U) ^ RotL64(aCurrent, 1U) ^ aDerivedSaltC[((aIndex + 21U) & 0x7FU)] ^ mScratchSaltA[((127U - aIndex + 66U) & 0x7FU)];
        aPrism = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(c) OP hot.add) * hot.mul;
        //
        aOrbitB = aOrbitB + aOrbitC + 4363216530256765144ULL + mScratchSaltC[((RotL64(aScatter, 13U) ^ aOrbitD) & 0x7FU)];
        aOrbitA = aOrbitA ^ aOrbitB ^ 8183299255648069712ULL ^ mScratchSaltB[((RotL64(aOrbitC, 11U)) & 0x7FU)];
        aOrbitA = RotL64(aOrbitA * 3604562571283486829ULL, 37U);
        aPrism = (aPrism ^ aOrbitD ^ 16410565495498644945ULL) * 14240780823652392381ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b);
        // prism = (prism OP mix(a) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitA + 7182652738966653225ULL + mScratchSaltD[((RotL64(aPrevious, 21U) ^ aOrbitB) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitD ^ 13873529907755399973ULL ^ mScratchSaltC[((RotL64(aWandererA, 29U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC, 45U);
        aPrism = (aPrism + (aOrbitB ^ RotL64(aCarry, 19U)) + 10607304991049255929ULL) * 16359373880257451463ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(b) OP hot.add) * hot.mul;
        //
        aOrbitB = aOrbitB + aOrbitC + 6297736036819237238ULL + mScratchSaltA[((RotL64(aWandererC, 27U) ^ aCross) & 0x7FU)];
        aOrbitA = aOrbitA ^ aOrbitB ^ 6569825217175163526ULL ^ mScratchSaltB[((RotL64(aWandererD, 13U)) & 0x7FU)];
        aOrbitA = RotL64(aOrbitA * 8064031199531702623ULL, 11U);
        aPrism = (aPrism ^ aOrbitC ^ 4363216530256765144ULL) * 4740549916134502575ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b * hot.mul);
        // prism = (prism OP mix(d) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitA + 8183299255648069712ULL + mScratchSaltD[((aScatter ^ RotL64(aCarry, 21U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitD ^ 16410565495498644945ULL ^ mScratchSaltC[((RotL64(aOrbitC, 29U) ^ aScatter) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 14240780823652392381ULL, 19U);
        aPrism = (aPrism + aOrbitA + 7182652738966653225ULL) * 14336822579912584529ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // e = mix(a, b, c, d)
        // e = diffuse(e OP scatter)
        // dest[i] = e
        //
        aCurrent = (RotL64(aOrbitB, 27U) ^ aOrbitC) + (RotL64(aOrbitD, 13U) ^ aOrbitA);
        aCurrent = TwistMix64::DiffuseB(aCurrent ^ aScatter);
        aWorkLaneC[aIndex] = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseC(aPrism);
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseA(aPrism);
        if ((aPrism & 0x0CU) > 6) {
        	if ((aPrism & 0x0CU) > 11) {
        		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 5ULL, aDerivedSBoxE, aDerivedSBoxC, aDerivedSBoxF, aDerivedSBoxB, aDerivedSBoxD, aDerivedSBoxG, aDerivedSBoxH, aDerivedSBoxA);
        	} else {
        		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 53ULL, aDerivedSBoxE, aDerivedSBoxC, aDerivedSBoxF, aDerivedSBoxB, aDerivedSBoxD, aDerivedSBoxG, aDerivedSBoxH, aDerivedSBoxA);
        	}
        } else {
        	if ((aPrism & 0x0CU) > 3) {
        		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 7ULL, aDerivedSBoxE, aDerivedSBoxC, aDerivedSBoxF, aDerivedSBoxB, aDerivedSBoxD, aDerivedSBoxG, aDerivedSBoxH, aDerivedSBoxA);
        	} else {
        		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, aDerivedSBoxE, aDerivedSBoxC, aDerivedSBoxF, aDerivedSBoxB, aDerivedSBoxD, aDerivedSBoxG, aDerivedSBoxH, aDerivedSBoxA);
        	}
        }
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s0 = s0 + (e ^ previous ^ d);
        // s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);
        //
        aWandererD = aWandererD + (aCurrent ^ aPrevious ^ RotL64(aOrbitA, 11U));
        aWandererD = RotL64((aWandererD + mSaltB[((aIndex + 126U) & 0x7FU)]) * 10671123761497897607ULL, 43U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s1 = s1 ^ (e + cross + a);
        // s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);
        //
        aWandererA = aWandererA ^ (aCurrent + aCross + RotL64(aOrbitB, 35U));
        aWandererA = RotL64((aWandererA ^ mScratchSaltA[((127U - aIndex + 60U) & 0x7FU)]) * 12350789942653520395ULL, 37U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s2 = s2 + (b ^ c ^ loopSalt[i/~i]);
        // s2 = rot(s2 * hot.mul);
        //
        aWandererC = aWandererC + (RotL64(aOrbitC, 51U) ^ aOrbitD ^ aDerivedSaltB[((127U - aIndex + 96U) & 0x7FU)]);
        aWandererC = RotL64(aWandererC * 8064031199531702623ULL, 29U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // carry = carry + (s0 ^ s1 ^ s2 ^ e);
        // carry = rot(carry * hot.mul);
        // carry = carry ^ (carry >> rshift);
        //
        aCarry = aCarry + (aWandererD ^ aWandererA ^ aWandererC ^ RotL64(aCurrent, 21U));
        aCarry = RotL64(aCarry * 4740549916134502575ULL, 19U);
        aCarry = aCarry ^ ShiftR64(aCarry, 37U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        // __END_CSPRNG
    }

    // Secure zero on crypto buffer.

    TwistMemory::ZeroBlock(aExpandLaneA);

    pCryptoGenerator->Salt(aWorkLaneC, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);
    // Making snow counter: aria 256

    TwistSnow::Aria256Counter(pSource, aExpandLaneA);

    TwistMemory::GrowB(mScratchSaltD, aDerivedSaltC, 128U);
    TwistMemory::GrowA(mScratchSaltB, mSaltB, 128U);
    TwistMemory::GrowB(mScratchSaltA, aDerivedSaltA, 128U);
    TwistMemory::GrowA(mScratchSaltC, aDerivedSaltC, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = aWorkLaneC[aIndex] ^ ShiftL64(aExpandLaneA[S_BLOCK1 - aIndex], 32U);
        aCross = aWorkLaneB[aIndex];
        // __START_CSPRNG
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // scatter = mix(secure_a, secure_b, previous)
        //
        aScatter = TwistMix64::DiffuseA(aCurrent ^ ShiftL64(aCross, 32U) ^ RotL64(aPrevious, 19U));
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = s0 + rot(e) + hot.add + plug[+];
        // b = s1 ^ rot(previous) ^ hot.add ^ plug[^];
        // c = s2 + rot(cross) + fixedSalt[i/~i] + scratchSalt[~i/i];
        // d = rot(carry) ^ rot(e) ^ fixedSalt[i/~i] ^ scratchSalt[~i/i];
        // prism = e;
        //
        aOrbitA = aWandererB + RotL64(aCurrent, 11U) + 5466424098337353378ULL + mScratchSaltC[((aOrbitA ^ RotL64(aOrbitB, 13U)) & 0x7FU)];
        aOrbitB = aWandererC ^ RotL64(aPrevious, 37U) ^ 17657336452829808209ULL ^ mScratchSaltB[((RotL64(aWandererB, 29U) + aOrbitC) & 0x7FU)];
        aOrbitD = aWandererA + RotL64(aCross, 27U) + mSaltC[((127U - aIndex + 125U) & 0x7FU)] + mScratchSaltA[((aIndex + 35U) & 0x7FU)];
        aOrbitC = RotL64(aCarry, 21U) ^ RotL64(aCurrent, 11U) ^ aDerivedSaltB[((aIndex + 11U) & 0x7FU)] ^ mScratchSaltD[((127U - aIndex + 38U) & 0x7FU)];
        aPrism = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(c) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitB + 13231907140188103277ULL + mScratchSaltB[((RotL64(aScatter, 19U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitA ^ 13774297313820760758ULL ^ mScratchSaltC[((RotL64(aCarry, 29U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 6103500182191258709ULL, 43U);
        aPrism = (aPrism + aOrbitD + 301182755099123951ULL) * 8547507606843732559ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b);
        // prism = (prism OP mix(a) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitC + 12348383357717244290ULL + mScratchSaltA[((aPrevious + RotL64(aCross, 13U)) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitD ^ 11442816451910736431ULL ^ mScratchSaltB[((RotL64(aScatter, 21U)) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB, 35U);
        aPrism = (aPrism ^ RotL64(aOrbitA, 19U) ^ 13824820778327553033ULL) * 15821320118147575661ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(b) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitB + 5466424098337353378ULL + mScratchSaltD[((RotL64(aWandererA, 11U) + aWandererC) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitA ^ 17657336452829808209ULL ^ mScratchSaltC[((RotL64(aOrbitB, 13U) + aOrbitD) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 12961813546653753825ULL, 29U);
        aPrism = (aPrism + (aOrbitB ^ RotL64(aCarry, 5U)) + 13231907140188103277ULL) * 3050432468924973435ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b * hot.mul);
        // prism = (prism OP mix(d) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitC + 13774297313820760758ULL + mScratchSaltB[((aWandererB + RotL64(aScatter, 21U)) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitD ^ 301182755099123951ULL ^ mScratchSaltA[((RotL64(aPrevious, 19U) + aOrbitC) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB * 8547507606843732559ULL, 7U);
        aPrism = (aPrism ^ aOrbitC ^ RotL64(aCarry, 1U) ^ 12348383357717244290ULL) * 17274464350135635459ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // e = mix(a, b, c, d)
        // e = diffuse(e OP scatter)
        // dest[~i] = e
        //
        aCurrent = (aOrbitA ^ RotL64(aOrbitB, 13U)) + (RotL64(aOrbitD, 11U) ^ aOrbitC);
        aCurrent = TwistMix64::DiffuseB(aCurrent + aScatter);
        aWorkLaneD[S_BLOCK1 - aIndex] = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseC(aPrism);
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseB(aPrism);
        if ((aPrism & 0x0CU) > 6) {
        	if ((aPrism & 0x0CU) > 8) {
        		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, aDerivedSBoxD, aDerivedSBoxG, aDerivedSBoxC, aDerivedSBoxE, aDerivedSBoxB, aDerivedSBoxF, aDerivedSBoxH, aDerivedSBoxA);
        	} else {
        		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 45ULL, aDerivedSBoxD, aDerivedSBoxG, aDerivedSBoxC, aDerivedSBoxE, aDerivedSBoxB, aDerivedSBoxF, aDerivedSBoxH, aDerivedSBoxA);
        	}
        } else {
        	if ((aPrism & 0x0CU) > 2) {
        		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 3ULL, aDerivedSBoxD, aDerivedSBoxG, aDerivedSBoxC, aDerivedSBoxE, aDerivedSBoxB, aDerivedSBoxF, aDerivedSBoxH, aDerivedSBoxA);
        	} else {
        		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 51ULL, aDerivedSBoxD, aDerivedSBoxG, aDerivedSBoxC, aDerivedSBoxE, aDerivedSBoxB, aDerivedSBoxF, aDerivedSBoxH, aDerivedSBoxA);
        	}
        }
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s0 = s0 + (e ^ previous ^ d);
        // s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);
        //
        aWandererB = aWandererB + (aCurrent ^ aPrevious ^ RotL64(aOrbitC, 5U));
        aWandererB = RotL64((aWandererB + mScratchSaltD[((127U - aIndex + 24U) & 0x7FU)]) * 1359559118340095529ULL, 53U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s1 = s1 ^ (e + cross + a);
        // s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);
        //
        aWandererC = aWandererC ^ (aCurrent + aCross + RotL64(aOrbitA, 43U));
        aWandererC = RotL64((aWandererC ^ mScratchSaltB[((aIndex + 106U) & 0x7FU)]) * 8012826765067614405ULL, 21U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s2 = s2 + (b ^ c ^ loopSalt[i/~i]);
        // s2 = rot(s2 * hot.mul);
        //
        aWandererA = aWandererA + (aOrbitB ^ RotL64(aOrbitD, 51U) ^ mSaltA[((127U - aIndex + 43U) & 0x7FU)]);
        aWandererA = RotL64(aWandererA * 12961813546653753825ULL, 37U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // carry = carry + (s0 ^ s1 ^ s2 ^ e);
        // carry = rot(carry * hot.mul);
        // carry = carry ^ (carry >> rshift);
        //
        aCarry = aCarry + (RotL64(aWandererB, 29U) ^ aWandererC ^ aWandererA ^ aCurrent);
        aCarry = RotL64(aCarry * 3050432468924973435ULL, 19U);
        aCarry = aCarry ^ ShiftR64(aCarry, 27U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        // __END_CSPRNG
    }

    // Secure zero on crypto buffer.

    TwistMemory::ZeroBlock(aExpandLaneA);

    pCryptoGenerator->Salt(aWorkLaneD, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);
    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aMaskLaneA[aIndex] = aWorkLaneA[aIndex] ^ aDerivedSaltA[((aIndex) & 0x7FU)];
    }

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aMaskLaneA[aIndex] = aWorkLaneA[aIndex] ^ aDerivedSaltA[((aIndex) & 0x7FU)];
    }

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aMaskLaneA[aIndex] = aWorkLaneA[aIndex] ^ aDerivedSaltA[((aIndex) & 0x7FU)];
    }

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aMaskLaneA[aIndex] = aWorkLaneA[aIndex] ^ aDerivedSaltA[((aIndex) & 0x7FU)];
    }

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aMaskLaneB[aIndex] = aDerivedSBoxD[((aWorkLaneB[aIndex]) & 0xFFU)];
    }

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aMaskLaneB[aIndex] = aDerivedSBoxD[((aWorkLaneB[aIndex]) & 0xFFU)];
    }

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aMaskLaneB[aIndex] = aDerivedSBoxD[((aWorkLaneB[aIndex]) & 0xFFU)];
    }

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aMaskLaneB[aIndex] = aDerivedSBoxD[((aWorkLaneB[aIndex]) & 0xFFU)];
    }

}

void TwistExpander_Swan::TwistBlock(TwistWorkSpace *pWorkspace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkspace, pSource, pDestination);
    if ((pWorkspace == nullptr) || (pDestination == nullptr)) { return; }
    std::memcpy(pDestination, pWorkspace->mWorkLaneD, S_BLOCK);
}
