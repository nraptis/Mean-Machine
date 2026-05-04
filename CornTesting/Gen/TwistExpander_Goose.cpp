#include "TwistExpander_Goose.hpp"
#include "TwistFunctional.hpp"
#include "TwistMasking.hpp"
#include "TwistMix64.hpp"
#include "TwistSnow.hpp"
#include "TwistMemory.hpp"
#include "TwistCryptoGenerator.hpp"

#include <cstring>

const std::uint8_t TwistExpander_Goose::kSBoxA[S_SBOX] = {
    0x8F, 0x24, 0x3A, 0x0A, 0x39, 0x54, 0xBF, 0xE4, 0x65, 0xDC, 0x64, 0x25, 0x09, 0x35, 0x87, 0x70, 
    0x11, 0xBB, 0xD4, 0x6E, 0xE2, 0x28, 0xC9, 0xB6, 0xE3, 0xF0, 0x16, 0x6C, 0x5A, 0x72, 0x9B, 0x45, 
    0xE9, 0xCC, 0xAF, 0x5F, 0x01, 0x90, 0x98, 0x75, 0x8E, 0x38, 0x49, 0xFC, 0x5E, 0xC0, 0x2F, 0x69, 
    0x7D, 0x6B, 0xFE, 0x80, 0x13, 0x0E, 0x37, 0x3E, 0xB8, 0x47, 0x34, 0x67, 0xF6, 0x15, 0x48, 0xB5, 
    0x07, 0xF1, 0x0B, 0x9C, 0xD6, 0xF5, 0xED, 0x99, 0x36, 0x7B, 0x7F, 0x02, 0xAA, 0x2D, 0xCE, 0xDF, 
    0x7C, 0x51, 0x96, 0x92, 0x3B, 0x86, 0x8D, 0xA7, 0x1E, 0x5B, 0x78, 0xF4, 0xB3, 0xD7, 0x62, 0xB0, 
    0x1B, 0x1D, 0xCD, 0xA8, 0x22, 0x9D, 0xA0, 0x95, 0x46, 0x27, 0x19, 0xE1, 0xB9, 0x55, 0x9F, 0x42, 
    0xF3, 0x5C, 0xE7, 0xC1, 0xE5, 0x10, 0xBE, 0x17, 0xF7, 0xA3, 0x4F, 0x71, 0xC8, 0x43, 0x73, 0x94, 
    0x3F, 0xA6, 0x0D, 0xD8, 0x4C, 0x44, 0x0C, 0xE6, 0xAE, 0xB7, 0xAB, 0x1F, 0xA1, 0xC3, 0x59, 0xD1, 
    0x4A, 0x7E, 0x12, 0x2B, 0xB4, 0x6F, 0x6A, 0xEF, 0x83, 0x57, 0x1C, 0x23, 0xA4, 0x06, 0x88, 0x05, 
    0xE8, 0xEA, 0x31, 0xC2, 0x76, 0xF2, 0xD0, 0x89, 0xCA, 0xDE, 0xA9, 0xC5, 0x20, 0xCB, 0x03, 0x85, 
    0xC6, 0x9E, 0x4B, 0x30, 0x4E, 0xBA, 0x58, 0x08, 0x7A, 0xDD, 0x5D, 0xBC, 0xEB, 0x40, 0x26, 0x4D, 
    0x93, 0xCF, 0x9A, 0x84, 0xF8, 0xFD, 0x2C, 0x21, 0x33, 0x61, 0xFF, 0x3D, 0xF9, 0xBD, 0x2A, 0x60, 
    0x14, 0xDA, 0x66, 0x2E, 0x3C, 0x53, 0xD2, 0x29, 0x00, 0xC4, 0x97, 0x56, 0x50, 0x0F, 0xB2, 0xD5, 
    0xA2, 0x6D, 0xB1, 0x82, 0xDB, 0x8A, 0x8B, 0x81, 0x74, 0x77, 0x1A, 0x79, 0xFA, 0x18, 0xE0, 0xEE, 
    0x04, 0xD3, 0xA5, 0xEC, 0x32, 0x8C, 0x68, 0x91, 0xAD, 0xFB, 0x41, 0x63, 0xC7, 0x52, 0xD9, 0xAC
};

const std::uint8_t TwistExpander_Goose::kSBoxB[S_SBOX] = {
    0x33, 0xE0, 0x1C, 0x3D, 0x0C, 0xFB, 0x12, 0x60, 0x6C, 0x2E, 0xDA, 0x56, 0x2D, 0x61, 0x5C, 0xEF, 
    0x75, 0x10, 0x41, 0x13, 0xC4, 0x8D, 0xAD, 0xCB, 0x72, 0x55, 0x67, 0xB5, 0x30, 0x49, 0x06, 0x7A, 
    0xBB, 0x19, 0x25, 0x84, 0x42, 0x79, 0x16, 0x5B, 0x85, 0xBA, 0x17, 0x38, 0x32, 0x74, 0x9F, 0x01, 
    0x34, 0xA7, 0x9E, 0x4E, 0xD3, 0x3F, 0xC7, 0x1E, 0x00, 0xDC, 0xD7, 0xCA, 0xF1, 0x77, 0xA1, 0xDB, 
    0xE6, 0xE3, 0x8B, 0x14, 0xE7, 0xE1, 0xB9, 0xA0, 0x71, 0x90, 0x92, 0x52, 0x91, 0x39, 0xBF, 0x3E, 
    0x82, 0x4F, 0xDD, 0xDF, 0xAA, 0xEA, 0x95, 0x4A, 0x08, 0x86, 0x80, 0x57, 0x7F, 0x51, 0x7E, 0x6F, 
    0xBC, 0x18, 0xAF, 0x37, 0x44, 0xA2, 0x58, 0xCD, 0x6A, 0xF0, 0x1A, 0xD4, 0xB6, 0x4D, 0x04, 0x68, 
    0x45, 0x94, 0x70, 0xC2, 0xD6, 0xC3, 0xA4, 0xD1, 0x47, 0x48, 0xB3, 0x59, 0x1B, 0xDE, 0xFF, 0x7B, 
    0xA8, 0xFC, 0x2F, 0x2C, 0xA3, 0xCC, 0x99, 0xC6, 0x93, 0x7D, 0x27, 0xBE, 0xEE, 0x64, 0x20, 0xF5, 
    0x07, 0x24, 0x65, 0x9D, 0x6D, 0xA5, 0x11, 0x1F, 0x5E, 0xEB, 0xAE, 0xF2, 0x5A, 0x50, 0x21, 0x40, 
    0x0D, 0xAB, 0x63, 0xD2, 0x4B, 0xF3, 0x43, 0x97, 0xBD, 0x88, 0x81, 0xC0, 0xE2, 0x0B, 0xE4, 0xFA, 
    0xD0, 0xB2, 0xB1, 0xD5, 0x05, 0xA6, 0x96, 0x9B, 0x26, 0x98, 0x22, 0x02, 0x1D, 0xCE, 0x46, 0x15, 
    0x69, 0x09, 0xB0, 0x4C, 0x3A, 0x8E, 0x8F, 0x54, 0xC5, 0x6E, 0x28, 0x0E, 0x8C, 0xB4, 0x2B, 0xD8, 
    0xC1, 0x8A, 0x7C, 0x29, 0xB8, 0xE9, 0xE5, 0x3B, 0xF4, 0x76, 0x6B, 0x5D, 0xF9, 0x89, 0xC9, 0xF7, 
    0xFE, 0x03, 0xD9, 0xE8, 0x3C, 0x87, 0x31, 0xF8, 0xED, 0xFD, 0x0A, 0x36, 0x9C, 0xAC, 0x62, 0xA9, 
    0xF6, 0x53, 0xEC, 0x0F, 0x73, 0x23, 0xB7, 0xCF, 0x83, 0x2A, 0x78, 0xC8, 0x66, 0x5F, 0x9A, 0x35
};

const std::uint8_t TwistExpander_Goose::kSBoxC[S_SBOX] = {
    0x84, 0x53, 0x09, 0x22, 0x9B, 0x6D, 0xAF, 0xD3, 0xF4, 0x39, 0x46, 0xE1, 0xB0, 0xDB, 0x45, 0xFD, 
    0x4B, 0x2E, 0xF8, 0xA7, 0x72, 0x13, 0x30, 0xDC, 0xC0, 0x68, 0x58, 0x87, 0x0D, 0xDD, 0x3F, 0xE5, 
    0x21, 0x03, 0x95, 0x3E, 0x71, 0x6C, 0xAD, 0xCE, 0x36, 0x29, 0xA5, 0x28, 0x8C, 0x43, 0x00, 0xB4, 
    0x0F, 0x94, 0x08, 0x56, 0x6B, 0xA3, 0xFB, 0x88, 0xBC, 0xC5, 0x69, 0xD4, 0xC9, 0xCA, 0x17, 0x4E, 
    0xD0, 0xDA, 0x90, 0x2C, 0xD8, 0x5B, 0xA0, 0x1F, 0x49, 0xAE, 0x2F, 0xE3, 0xA6, 0x20, 0x23, 0xAB, 
    0xBD, 0x5E, 0xCD, 0x4C, 0xBB, 0xF7, 0xA4, 0x54, 0x99, 0xBF, 0x3C, 0xE9, 0xEF, 0x6A, 0xE7, 0x7D, 
    0xAA, 0x0B, 0xB1, 0x86, 0xF2, 0x9E, 0x47, 0x5F, 0x77, 0xC1, 0x8A, 0xE0, 0x0E, 0xDF, 0xBE, 0xF6, 
    0xFA, 0xAC, 0x41, 0xF1, 0x61, 0xF9, 0x1D, 0xEA, 0x7B, 0xD5, 0x04, 0x4F, 0x82, 0x44, 0x6F, 0xED, 
    0x3A, 0xE6, 0x31, 0xB8, 0x96, 0x57, 0x83, 0xF3, 0x27, 0x6E, 0x14, 0x2B, 0xF5, 0xD1, 0x9F, 0xCB, 
    0x37, 0x9D, 0xD9, 0x81, 0xFC, 0x15, 0x26, 0x80, 0xC4, 0xFF, 0xB9, 0x40, 0xC6, 0x62, 0x97, 0xF0, 
    0x93, 0xB3, 0x5A, 0x63, 0x5C, 0x48, 0x79, 0x25, 0xA2, 0x19, 0x34, 0x70, 0xD2, 0x10, 0x51, 0x65, 
    0xE2, 0x0C, 0x85, 0xE8, 0xB6, 0x9C, 0x2D, 0x02, 0x1C, 0x8B, 0x1E, 0x3D, 0x01, 0xD6, 0x73, 0x24, 
    0xFE, 0x91, 0x8D, 0xD7, 0xA9, 0x9A, 0x92, 0x60, 0x7A, 0x75, 0xBA, 0x1A, 0x1B, 0x8F, 0x33, 0xC7, 
    0x78, 0x98, 0x66, 0xB2, 0xA8, 0x7E, 0x59, 0xA1, 0xC3, 0xC2, 0x7F, 0x4D, 0xEC, 0x11, 0x5D, 0x4A, 
    0x67, 0x35, 0xCF, 0x76, 0x2A, 0xB7, 0x05, 0xE4, 0x7C, 0xEE, 0x18, 0x8E, 0x89, 0x38, 0x52, 0x32, 
    0x42, 0xEB, 0x74, 0x12, 0xC8, 0x16, 0x06, 0xDE, 0xB5, 0x3B, 0x64, 0x55, 0x50, 0xCC, 0x0A, 0x07
};

const std::uint8_t TwistExpander_Goose::kSBoxD[S_SBOX] = {
    0x13, 0xC0, 0x28, 0xE1, 0x8D, 0x9D, 0xDA, 0x0D, 0xD6, 0xEE, 0x54, 0x42, 0x44, 0x8E, 0x39, 0xB1, 
    0xA2, 0xF3, 0xC4, 0x59, 0x03, 0xC3, 0x89, 0x72, 0x81, 0xE8, 0x2E, 0x7E, 0xB9, 0x96, 0xF6, 0xD3, 
    0x8C, 0x22, 0x16, 0x12, 0x6E, 0x79, 0x53, 0x1A, 0x91, 0x0F, 0xD0, 0xEB, 0x90, 0x21, 0x4F, 0xD5, 
    0x30, 0xF2, 0xCC, 0xB5, 0x85, 0xC8, 0xA9, 0x01, 0x56, 0xF4, 0x0C, 0xF1, 0xE6, 0x8B, 0x52, 0xD7, 
    0x60, 0x6A, 0x63, 0x7A, 0xE3, 0x43, 0xA5, 0xD1, 0x2B, 0x3E, 0x17, 0xCB, 0xBD, 0x68, 0x05, 0x4B, 
    0xB2, 0x36, 0x77, 0x5E, 0xAA, 0xBB, 0x34, 0x3C, 0x04, 0x3B, 0x9B, 0xC1, 0xD9, 0x61, 0x5A, 0x7C, 
    0xAF, 0xA1, 0xA0, 0x9A, 0xCE, 0xF8, 0xB0, 0xD2, 0x76, 0x65, 0x88, 0xA6, 0xD4, 0x1F, 0xDF, 0x5F, 
    0x4D, 0xB7, 0xA8, 0xA3, 0x8F, 0x20, 0x58, 0xAC, 0x64, 0x15, 0xDE, 0x33, 0x0B, 0xDD, 0x14, 0x50, 
    0x83, 0xBE, 0x6D, 0xC7, 0x7B, 0x51, 0xEF, 0x2A, 0x94, 0xF0, 0x3F, 0x86, 0x32, 0x84, 0x1C, 0x6F, 
    0x75, 0x95, 0x07, 0x66, 0x55, 0xDB, 0x70, 0x82, 0x10, 0x38, 0x23, 0x4C, 0x99, 0xE2, 0x9F, 0x47, 
    0x0E, 0x29, 0xA7, 0x06, 0xBF, 0xCF, 0xED, 0x1D, 0x2C, 0xC9, 0x18, 0x8A, 0xE9, 0xAE, 0x49, 0x1E, 
    0x2F, 0x5D, 0xF7, 0x25, 0x5C, 0x71, 0x9E, 0xC6, 0xBC, 0x6C, 0x35, 0x7F, 0xAB, 0x78, 0xE7, 0xF9, 
    0xDC, 0x87, 0x74, 0x9C, 0xC2, 0x69, 0xEA, 0x6B, 0x80, 0xFF, 0x4E, 0xA4, 0x40, 0xFD, 0xE4, 0x7D, 
    0x09, 0xE0, 0x73, 0xCD, 0x26, 0x11, 0xCA, 0x41, 0xEC, 0x08, 0xF5, 0xBA, 0xB4, 0x4A, 0x5B, 0x46, 
    0x97, 0xFC, 0xFE, 0x92, 0x62, 0xB8, 0x3A, 0x37, 0x98, 0x3D, 0x2D, 0x19, 0xE5, 0x0A, 0x24, 0x00, 
    0xC5, 0x48, 0x1B, 0x27, 0x02, 0xB6, 0x57, 0xFB, 0x31, 0x67, 0xFA, 0xD8, 0xAD, 0x93, 0x45, 0xB3
};

const std::uint8_t TwistExpander_Goose::kSaltA[S_SALT] = {
    0x1C, 0x38, 0x2D, 0x11, 0xF6, 0x0A, 0x07, 0x03, 0x10, 0x0C, 0x81, 0x15, 0x1A, 0x3E, 0x2B, 0xE7, 
    0x04, 0xE0, 0x35, 0x39, 0x5E, 0x52, 0x4F, 0x4B, 0x58, 0xD4, 0xE9, 0xFD, 0x02, 0xE6, 0xB3, 0xAF, 
    0xAC, 0x88, 0x7D, 0xA1, 0xC6, 0x9A, 0x97, 0x93, 0xA0, 0x9C, 0xD1, 0xA5, 0xAA, 0x8E, 0x7B, 0xB7, 
    0xD4, 0xF0, 0x05, 0x09, 0xEE, 0xE2, 0x5F, 0x5B, 0x68, 0x64, 0x79, 0x4D, 0x52, 0xF6, 0x03, 0xFF, 
    0x3C, 0x58, 0x4D, 0x31, 0x96, 0x2A, 0x27, 0x23, 0x30, 0x2C, 0x21, 0x35, 0x3A, 0x5E, 0x4B, 0x87, 
    0xA4, 0x80, 0x55, 0x59, 0xFE, 0xF2, 0xEF, 0xEB, 0xF8, 0x74, 0x89, 0x9D, 0xA2, 0x86, 0xD3, 0xCF, 
    0xCC, 0x28, 0x1D, 0xC1, 0xE6, 0xBA, 0xB7, 0xB3, 0xC0, 0xBC, 0xF1, 0xC5, 0xCA, 0x2E, 0x1B, 0xD7, 
    0xF4, 0x90, 0xA5, 0xA9, 0x8E, 0x82, 0xFF, 0xFB, 0x08, 0x04, 0x19, 0x6D, 0x72, 0x96, 0xA3, 0x9F
};

const std::uint8_t TwistExpander_Goose::kSaltB[S_SALT] = {
    0xAF, 0xA3, 0x78, 0x9C, 0xC1, 0x9D, 0xFA, 0xA6, 0xB3, 0x77, 0x4C, 0x40, 0xE5, 0x01, 0x2E, 0x3A, 
    0x17, 0x0B, 0x40, 0x24, 0x09, 0xE5, 0x42, 0x4E, 0x5B, 0xBF, 0xB4, 0x08, 0xAD, 0xC9, 0x96, 0x82, 
    0xBF, 0xB3, 0x08, 0xEC, 0x51, 0x6D, 0x8A, 0x36, 0x43, 0x07, 0x1C, 0x50, 0x35, 0x91, 0x3E, 0x4A, 
    0xE7, 0xDB, 0xD0, 0x74, 0x99, 0xB5, 0xD2, 0x9E, 0xAB, 0xCF, 0xC4, 0x98, 0x7D, 0xD9, 0xE6, 0x12, 
    0x4F, 0x43, 0x98, 0x3C, 0x61, 0x3D, 0x1A, 0x46, 0x53, 0x97, 0x6C, 0xE0, 0x05, 0x21, 0xCE, 0xDA, 
    0xB7, 0xAB, 0xE0, 0xC4, 0x29, 0x05, 0xE2, 0x6E, 0x7B, 0x5F, 0x54, 0x28, 0x4D, 0x69, 0x36, 0xA2, 
    0x5F, 0x53, 0x28, 0x0C, 0xF1, 0x8D, 0xAA, 0xD6, 0xE3, 0x27, 0xBC, 0xF0, 0xD5, 0xB1, 0xDE, 0xEA, 
    0x07, 0xFB, 0x70, 0x94, 0xB9, 0x55, 0x72, 0x3E, 0x4B, 0x6F, 0x64, 0xB8, 0x9D, 0x79, 0x06, 0x32
};

const std::uint8_t TwistExpander_Goose::kSaltC[S_SALT] = {
    0x96, 0x82, 0xFB, 0x8F, 0xA0, 0xA4, 0xBD, 0x59, 0x5A, 0x46, 0x4F, 0x63, 0x34, 0x28, 0x31, 0x1D, 
    0xFE, 0x0A, 0x23, 0x17, 0x48, 0x2C, 0x65, 0x81, 0x82, 0x4E, 0x57, 0xCB, 0xBC, 0xF0, 0xF9, 0x05, 
    0xA6, 0x92, 0xCB, 0x9F, 0xB0, 0x74, 0x8D, 0x69, 0x6A, 0x56, 0xDF, 0xF3, 0x04, 0xF8, 0x01, 0x2D, 
    0x4E, 0x1A, 0x33, 0x27, 0x98, 0x7C, 0x75, 0x51, 0x52, 0xDE, 0xE7, 0x1B, 0x0C, 0xC0, 0xC9, 0xD5, 
    0xB6, 0xA2, 0x9B, 0xAF, 0xC0, 0xC4, 0xDD, 0xF9, 0xFA, 0xE6, 0xEF, 0x03, 0x54, 0x48, 0x51, 0x3D, 
    0x9E, 0x2A, 0x43, 0x37, 0x68, 0x4C, 0x05, 0x21, 0x22, 0xEE, 0xF7, 0xEB, 0xDC, 0x90, 0x99, 0xA5, 
    0xC6, 0xB2, 0xEB, 0xBF, 0xD0, 0x14, 0x2D, 0x09, 0x0A, 0xF6, 0x7F, 0x93, 0xA4, 0x98, 0xA1, 0x4D, 
    0x6E, 0x3A, 0x53, 0x47, 0x38, 0x1C, 0x15, 0x71, 0x72, 0x7E, 0x87, 0xBB, 0xAC, 0xE0, 0xE9, 0xF5
};

const std::uint8_t TwistExpander_Goose::kSaltD[S_SALT] = {
    0x9F, 0xB9, 0x94, 0xF2, 0x99, 0x8B, 0x86, 0x84, 0x93, 0x8D, 0xB8, 0x96, 0xFD, 0x9F, 0xAA, 0x68, 
    0x87, 0x61, 0xBC, 0xDA, 0x01, 0xD3, 0xCE, 0x4C, 0x5B, 0x55, 0x60, 0x3E, 0xE5, 0x07, 0x32, 0x30, 
    0x2F, 0x89, 0x24, 0x42, 0x29, 0x1B, 0x16, 0x14, 0x23, 0x1D, 0x88, 0x26, 0x4D, 0x2F, 0xFA, 0x38, 
    0x57, 0x71, 0x8C, 0x6A, 0x51, 0xE3, 0xDE, 0xDC, 0xEB, 0x65, 0x70, 0x8E, 0x75, 0xD7, 0x02, 0x00, 
    0xBF, 0xD9, 0xB4, 0x92, 0xB9, 0xAB, 0xA6, 0xA4, 0xB3, 0xAD, 0xD8, 0xB6, 0x9D, 0xBF, 0xCA, 0x08, 
    0x27, 0x01, 0xDC, 0x7A, 0xA1, 0x73, 0x6E, 0xEC, 0xFB, 0xF5, 0x00, 0x5E, 0x85, 0xA7, 0x52, 0x50, 
    0x4F, 0x29, 0x44, 0x62, 0x49, 0x3B, 0x36, 0x34, 0x43, 0x3D, 0x28, 0x46, 0x6D, 0x4F, 0x9A, 0x58, 
    0x77, 0x11, 0x2C, 0x0A, 0x71, 0x83, 0x7E, 0x7C, 0x8B, 0x05, 0x10, 0x2E, 0x15, 0xF7, 0xA2, 0xA0
};

TwistExpander_Goose::TwistExpander_Goose()
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

void TwistExpander_Goose::Seed(TwistWorkSpace *pWorkspace,
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
    std::uint64_t aPrevious = 0;
    std::uint64_t aCurrent = 0;
    std::uint64_t aCross = 0;
    std::uint64_t aScatter = 0;
    std::uint64_t aOrbitC = 0;
    std::uint64_t aWandererA = 0;
    std::uint64_t aWandererB = 0;
    std::uint64_t aOrbitD = 0;
    std::uint64_t aOrbitA = 0;
    std::uint64_t aWandererC = 0;
    std::uint64_t aOrbitB = 0;
    std::uint64_t aCarry = 0;
    std::uint64_t aPrism = 0;
    std::uint64_t aWandererD = 0;

    // Making snow counter: cha cha 20

    TwistSnow::ChaCha20Counter(pSource, aExpandLaneA);

    TwistMemory::GrowA(mScratchSaltC, mSaltA, 128U);
    TwistMemory::GrowB(mScratchSaltD, mSaltB, 128U);
    TwistMemory::GrowA(mScratchSaltA, mSaltD, 128U);
    TwistMemory::GrowB(mScratchSaltB, mSaltC, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = pSource[aIndex] ^ ShiftL64(aExpandLaneA[S_BLOCK1 - aIndex], 32U);
        aCross = pSource[S_BLOCK1 - aIndex];
        // __START_CSPRNG
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // scatter = mix(secure_a, secure_b, previous)
        //
        aScatter = TwistMix64::DiffuseA(aCurrent ^ ShiftL64(aCross, 32U) ^ RotL64(aPrevious, 29U));
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = s0 + rot(e) + hot.add + plug[+];
        // b = s1 ^ rot(previous) ^ hot.add ^ plug[^];
        // c = s2 + rot(cross) + fixedSalt[i/~i] + scratchSalt[~i/i];
        // d = rot(carry) ^ rot(e) ^ fixedSalt[i/~i] ^ scratchSalt[~i/i];
        // prism = e;
        //
        aOrbitC = aWandererA + RotL64(aCurrent, 3U) + 3649838893872127637ULL + mScratchSaltD[((RotL64(aScatter, 11U) + aWandererB) & 0x7FU)];
        aOrbitD = aWandererB ^ RotL64(aPrevious, 27U) ^ 1059372836866329930ULL ^ mScratchSaltB[((RotL64(aOrbitA, 21U) ^ aWandererA) & 0x7FU)];
        aOrbitA = aWandererC + RotL64(aCross, 53U) + mSaltC[((127U - aIndex + 95U) & 0x7FU)] + mScratchSaltA[((aIndex + 126U) & 0x7FU)];
        aOrbitB = RotL64(aCarry, 37U) ^ RotL64(aCurrent, 19U) ^ mSaltB[((aIndex + 87U) & 0x7FU)] ^ mScratchSaltC[((127U - aIndex + 72U) & 0x7FU)];
        aPrism = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(c) OP hot.add) * hot.mul;
        //
        aOrbitC = aOrbitC + aOrbitD + 553311327429535653ULL + mScratchSaltB[((aWandererC ^ RotL64(aOrbitB, 13U)) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitC ^ 9359193688116610064ULL ^ mScratchSaltD[((RotL64(aOrbitC, 29U)) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB * 10162070780037794691ULL, 51U);
        aPrism = (aPrism ^ aOrbitA ^ RotL64(aCarry, 7U) ^ 725719098283885994ULL) * 13506266611049043615ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b);
        // prism = (prism OP mix(a) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitB + 16470178670330770040ULL + mScratchSaltC[((RotL64(aCarry, 11U) + aOrbitD) & 0x7FU)];
        aOrbitD = aOrbitD ^ aOrbitA ^ 15273254628597241745ULL ^ mScratchSaltA[((RotL64(aPrevious, 27U)) & 0x7FU)];
        aOrbitD = RotL64(aOrbitD, 21U);
        aPrism = (aPrism + aOrbitC + 5138525288831553203ULL) * 14835811651754334545ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(b) OP hot.add) * hot.mul;
        //
        aOrbitC = aOrbitC + aOrbitD + 3649838893872127637ULL + mScratchSaltD[((RotL64(aWandererB, 19U)) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitC ^ 1059372836866329930ULL ^ mScratchSaltB[((aOrbitA ^ RotL64(aScatter, 13U)) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB * 13657416044466041211ULL, 35U);
        aPrism = (aPrism ^ aOrbitD ^ RotL64(aCarry, 29U) ^ 553311327429535653ULL) * 13806054323065233879ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b * hot.mul);
        // prism = (prism OP mix(d) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitB + 9359193688116610064ULL + mScratchSaltA[((aWandererA ^ RotL64(aScatter, 11U)) & 0x7FU)];
        aOrbitD = aOrbitD ^ aOrbitA ^ 725719098283885994ULL ^ mScratchSaltC[((RotL64(aOrbitC, 21U)) & 0x7FU)];
        aOrbitD = RotL64(aOrbitD * 13506266611049043615ULL, 27U);
        aPrism = (aPrism + (aOrbitB ^ RotL64(aCarry, 19U)) + 16470178670330770040ULL) * 9209661592696827243ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // e = mix(a, b, c, d)
        // e = diffuse(e OP scatter)
        // dest[i] = e
        //
        aCurrent = (RotL64(aOrbitC, 11U) ^ aOrbitB) + (RotL64(aOrbitD, 13U) ^ aOrbitA);
        aCurrent = TwistMix64::DiffuseA(aCurrent ^ aScatter);
        aWorkLaneA[aIndex] = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseA(aPrism);
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseB(aPrism);
        if ((aPrism & 0x7CU) > 62) {
        	aCurrent = TwistMix64::GateTurnC_4_8(aCurrent, 45ULL, mSBoxA, mSBoxD, mSBoxC, mSBoxB);
        } else {
        	aCurrent = TwistMix64::GateRollA_4_8(aCurrent, 1ULL, mSBoxA, mSBoxD, mSBoxC, mSBoxB);
        }
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s0 = s0 + (e ^ previous ^ d);
        // s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);
        //
        aWandererA = aWandererA + (aCurrent ^ aPrevious ^ RotL64(aOrbitB, 43U));
        aWandererA = RotL64((aWandererA + mScratchSaltD[((aIndex + 27U) & 0x7FU)]) * 13934549263016961593ULL, 53U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s1 = s1 ^ (e + cross + a);
        // s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);
        //
        aWandererB = aWandererB ^ (RotL64(aCurrent, 5U) + aCross + aOrbitC);
        aWandererB = RotL64((aWandererB ^ mScratchSaltB[((127U - aIndex + 52U) & 0x7FU)]) * 12778641489669333085ULL, 27U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s2 = s2 + (b ^ c ^ loopSalt[i/~i]);
        // s2 = rot(s2 * hot.mul);
        //
        aWandererC = aWandererC + (RotL64(aOrbitD, 51U) ^ aOrbitA ^ mSaltA[((aIndex + 22U) & 0x7FU)]);
        aWandererC = RotL64(aWandererC * 13657416044466041211ULL, 21U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // carry = carry + (s0 ^ s1 ^ s2 ^ e);
        // carry = rot(carry * hot.mul);
        // carry = carry ^ (carry >> rshift);
        //
        aCarry = aCarry + (RotL64(aWandererA, 3U) ^ aWandererB ^ aWandererC ^ aCurrent);
        aCarry = RotL64(aCarry * 13806054323065233879ULL, 19U);
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

    TwistMemory::GrowB(mScratchSaltA, aDerivedSBoxA, 256U);
    TwistMemory::GrowA(mScratchSaltB, aDerivedSBoxB, 256U);
    TwistMemory::GrowB(mScratchSaltC, aDerivedSBoxC, 256U);
    TwistMemory::GrowA(mScratchSaltD, aDerivedSBoxD, 256U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = aWorkLaneA[aIndex] ^ ShiftL64(aExpandLaneA[aIndex], 32U);
        aCross = pSource[aIndex];
        // __START_CSPRNG
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // scatter = mix(secure_a, secure_b, previous)
        //
        aScatter = TwistMix64::DiffuseA(ShiftL64(aCurrent, 32U) ^ aCross ^ RotL64(aPrevious, 19U));
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = s0 + rot(e) + hot.add + plug[+];
        // b = s1 ^ rot(previous) ^ hot.add ^ plug[^];
        // c = s2 + rot(cross) + fixedSalt[i/~i] + scratchSalt[~i/i];
        // d = rot(carry) ^ rot(e) ^ fixedSalt[i/~i] ^ scratchSalt[~i/i];
        // prism = e;
        //
        aOrbitD = aWandererD + RotL64(aCurrent, 29U) + 11824646353050788126ULL + mScratchSaltB[((RotL64(aWandererD, 21U)) & 0x7FU)];
        aOrbitC = aWandererA ^ RotL64(aPrevious, 13U) ^ 11514918350134927062ULL ^ mScratchSaltA[((aOrbitD ^ RotL64(aScatter, 27U)) & 0x7FU)];
        aOrbitA = aWandererB + RotL64(aCross, 45U) + mSaltD[((aIndex + 42U) & 0x7FU)] + mScratchSaltC[((127U - aIndex + 55U) & 0x7FU)];
        aOrbitB = RotL64(aCarry, 51U) ^ RotL64(aCurrent, 5U) ^ mSaltB[((127U - aIndex + 50U) & 0x7FU)] ^ mScratchSaltD[((aIndex + 26U) & 0x7FU)];
        aPrism = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(c) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitC + 17149132441113471552ULL + mScratchSaltB[((RotL64(aOrbitC, 11U) ^ aScatter) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitD ^ 13629262313164744500ULL ^ mScratchSaltA[((RotL64(aWandererB, 21U)) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB * 4046587771798686415ULL, 35U);
        aPrism = (aPrism ^ RotL64(aOrbitA, 19U) ^ 3986063663209452955ULL) * 100443085565158387ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b);
        // prism = (prism OP mix(a) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitB + 15005949813639515379ULL + mScratchSaltD[((RotL64(aWandererA, 13U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitA ^ 4922044076279663769ULL ^ mScratchSaltC[((RotL64(aOrbitB, 27U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC, 37U);
        aPrism = (aPrism + RotL64(aOrbitD, 11U) + 1398825023862269597ULL) * 16381055742657568667ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(b) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitC + 11824646353050788126ULL + mScratchSaltB[((RotL64(aCross, 21U)) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitD ^ 11514918350134927062ULL ^ mScratchSaltA[((aCarry + RotL64(aWandererD, 13U)) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB * 13649492134883219963ULL, 43U);
        aPrism = (aPrism ^ RotL64(aOrbitC, 27U) ^ 17149132441113471552ULL) * 9313997004846686517ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b * hot.mul);
        // prism = (prism OP mix(d) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitB + 13629262313164744500ULL + mScratchSaltC[((RotL64(aPrevious, 11U) + aScatter) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitA ^ 3986063663209452955ULL ^ mScratchSaltD[((RotL64(aScatter, 21U) ^ aOrbitC) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 100443085565158387ULL, 53U);
        aPrism = (aPrism + RotL64(aOrbitB, 29U) + 15005949813639515379ULL) * 5776305957154416141ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // e = mix(a, b, c, d)
        // e = diffuse(e OP scatter)
        // dest[~i] = e
        //
        aCurrent = (RotL64(aOrbitD, 27U) ^ aOrbitB) + (aOrbitC ^ RotL64(aOrbitA, 13U));
        aCurrent = TwistMix64::DiffuseA(aCurrent + aScatter);
        aWorkLaneC[S_BLOCK1 - aIndex] = aCurrent;
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
        if ((aPrism & 0x44U) > 31) {
        	if ((aPrism & 0x44U) > 66) {
        		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 5ULL, aDerivedSBoxB, aDerivedSBoxC, mSBoxB, mSBoxD, aDerivedSBoxA, aDerivedSBoxD, mSBoxA, mSBoxC);
        	} else {
        		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 3ULL, aDerivedSBoxB, aDerivedSBoxC, mSBoxB, mSBoxD, aDerivedSBoxA, aDerivedSBoxD, mSBoxA, mSBoxC);
        	}
        } else {
        	if ((aPrism & 0x44U) > 1) {
        		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, aDerivedSBoxB, aDerivedSBoxC, mSBoxB, mSBoxD, aDerivedSBoxA, aDerivedSBoxD, mSBoxA, mSBoxC);
        	} else {
        		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 1ULL, aDerivedSBoxB, aDerivedSBoxC, mSBoxB, mSBoxD, aDerivedSBoxA, aDerivedSBoxD, mSBoxA, mSBoxC);
        	}
        }
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s0 = s0 + (e ^ previous ^ d);
        // s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);
        //
        aWandererD = aWandererD + (aCurrent ^ aPrevious ^ RotL64(aOrbitB, 19U));
        aWandererD = RotL64((aWandererD + mSaltA[((127U - aIndex + 16U) & 0x7FU)]) * 15300375190273489537ULL, 53U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s1 = s1 ^ (e + cross + a);
        // s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);
        //
        aWandererA = aWandererA ^ (RotL64(aCurrent, 45U) + aCross + aOrbitD);
        aWandererA = RotL64((aWandererA ^ mSaltC[((127U - aIndex + 10U) & 0x7FU)]) * 16074532613685973791ULL, 11U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s2 = s2 + (b ^ c ^ loopSalt[i/~i]);
        // s2 = rot(s2 * hot.mul);
        //
        aWandererB = aWandererB + (aOrbitC ^ RotL64(aOrbitA, 51U) ^ mSaltD[((127U - aIndex + 58U) & 0x7FU)]);
        aWandererB = RotL64(aWandererB * 13649492134883219963ULL, 35U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // carry = carry + (s0 ^ s1 ^ s2 ^ e);
        // carry = rot(carry * hot.mul);
        // carry = carry ^ (carry >> rshift);
        //
        aCarry = aCarry + (aWandererD ^ RotL64(aWandererA, 7U) ^ aWandererB ^ aCurrent);
        aCarry = RotL64(aCarry * 9313997004846686517ULL, 37U);
        aCarry = aCarry ^ ShiftR64(aCarry, 33U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        // __END_CSPRNG
    }

    // Secure zero on crypto buffer.

    TwistMemory::ZeroBlock(aExpandLaneA);

    pCryptoGenerator->Salt(aWorkLaneC, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);
    // Making snow counter: sha 256

    TwistSnow::Sha256Counter(pSource, aExpandLaneA);

    TwistMemory::GrowA(mScratchSaltD, aDerivedSaltA, 128U);
    TwistMemory::GrowB(mScratchSaltA, aDerivedSaltB, 128U);
    TwistMemory::GrowA(mScratchSaltB, aDerivedSaltC, 128U);
    TwistMemory::GrowB(mScratchSaltC, aDerivedSaltD, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = aWorkLaneC[aIndex] ^ ShiftL64(aExpandLaneA[S_BLOCK1 - aIndex], 32U);
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
        aOrbitB = aWandererD + RotL64(aCurrent, 11U) + 17074759125205506664ULL + mScratchSaltA[((RotL64(aScatter, 29U)) & 0x7FU)];
        aOrbitD = aWandererC ^ RotL64(aPrevious, 53U) ^ 16005736661622283626ULL ^ mScratchSaltB[((aWandererC ^ RotL64(aWandererD, 13U)) & 0x7FU)];
        aOrbitA = aWandererB + RotL64(aCross, 27U) + mSaltD[((127U - aIndex + 48U) & 0x7FU)] + mScratchSaltD[((aIndex + 105U) & 0x7FU)];
        aOrbitC = RotL64(aCarry, 19U) ^ RotL64(aCurrent, 21U) ^ aDerivedSaltA[((127U - aIndex + 126U) & 0x7FU)] ^ mScratchSaltC[((aIndex + 36U) & 0x7FU)];
        aPrism = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(c) OP hot.add) * hot.mul;
        //
        aOrbitB = aOrbitB + aOrbitD + 12021371933181799200ULL + mScratchSaltB[((aCross ^ RotL64(aOrbitD, 11U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitB ^ 18009961152681437352ULL ^ mScratchSaltA[((aOrbitB ^ RotL64(aWandererB, 29U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 3840180102105858685ULL, 13U);
        aPrism = (aPrism + aOrbitA + 16470251490332617077ULL) * 8621901400590366247ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b);
        // prism = (prism OP mix(a) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitC + 5204038104288494420ULL + mScratchSaltD[((RotL64(aCarry, 27U)) & 0x7FU)];
        aOrbitD = aOrbitD ^ aOrbitA ^ 17731276074303303793ULL ^ mScratchSaltC[((RotL64(aPrevious, 19U)) & 0x7FU)];
        aOrbitD = RotL64(aOrbitD, 51U);
        aPrism = (aPrism ^ aOrbitB ^ 4084472148082095814ULL) * 2749367408541544149ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(b) OP hot.add) * hot.mul;
        //
        aOrbitB = aOrbitB + aOrbitD + 17074759125205506664ULL + mScratchSaltB[((RotL64(aScatter, 21U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitB ^ 16005736661622283626ULL ^ mScratchSaltD[((RotL64(aScatter, 11U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 8434741120220886235ULL, 29U);
        aPrism = (aPrism + RotL64(aOrbitD, 13U) + 12021371933181799200ULL) * 5937244912172485557ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b * hot.mul);
        // prism = (prism OP mix(d) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitC + 18009961152681437352ULL + mScratchSaltA[((aWandererC ^ RotL64(aOrbitC, 27U)) & 0x7FU)];
        aOrbitD = aOrbitD ^ aOrbitA ^ 16470251490332617077ULL ^ mScratchSaltC[((RotL64(aOrbitD, 19U) + aWandererD) & 0x7FU)];
        aOrbitD = RotL64(aOrbitD * 8621901400590366247ULL, 11U);
        aPrism = (aPrism ^ RotL64(aOrbitC, 21U) ^ 5204038104288494420ULL) * 3063072455474467829ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // e = mix(a, b, c, d)
        // e = diffuse(e OP scatter)
        // dest[i] = e
        //
        aCurrent = (aOrbitB ^ RotL64(aOrbitD, 29U)) + (aOrbitA ^ RotL64(aOrbitC, 27U));
        aCurrent = TwistMix64::DiffuseA(aCurrent + aScatter);
        aWorkLaneB[aIndex] = aCurrent;
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
        if ((aPrism & 0x22U) > 19) {
        	if ((aPrism & 0x22U) > 32) {
        		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, aDerivedSBoxA, aDerivedSBoxD, aDerivedSBoxE, aDerivedSBoxG, aDerivedSBoxC, aDerivedSBoxH, aDerivedSBoxB, aDerivedSBoxF);
        	} else {
        		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 37ULL, aDerivedSBoxA, aDerivedSBoxD, aDerivedSBoxE, aDerivedSBoxG, aDerivedSBoxC, aDerivedSBoxH, aDerivedSBoxB, aDerivedSBoxF);
        	}
        } else {
        	if ((aPrism & 0x22U) > 0) {
        		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, aDerivedSBoxA, aDerivedSBoxD, aDerivedSBoxE, aDerivedSBoxG, aDerivedSBoxC, aDerivedSBoxH, aDerivedSBoxB, aDerivedSBoxF);
        	} else {
        		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 1ULL, aDerivedSBoxA, aDerivedSBoxD, aDerivedSBoxE, aDerivedSBoxG, aDerivedSBoxC, aDerivedSBoxH, aDerivedSBoxB, aDerivedSBoxF);
        	}
        }
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s0 = s0 + (e ^ previous ^ d);
        // s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);
        //
        aWandererD = aWandererD + (aCurrent ^ aPrevious ^ RotL64(aOrbitC, 51U));
        aWandererD = RotL64((aWandererD + mScratchSaltB[((127U - aIndex + 63U) & 0x7FU)]) * 5787839862338755591ULL, 35U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s1 = s1 ^ (e + cross + a);
        // s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);
        //
        aWandererC = aWandererC ^ (aCurrent + aCross + RotL64(aOrbitB, 43U));
        aWandererC = RotL64((aWandererC ^ mScratchSaltA[((aIndex + 16U) & 0x7FU)]) * 13907420933814945003ULL, 45U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s2 = s2 + (b ^ c ^ loopSalt[i/~i]);
        // s2 = rot(s2 * hot.mul);
        //
        aWandererB = aWandererB + (aOrbitD ^ RotL64(aOrbitA, 13U) ^ mScratchSaltD[((127U - aIndex + 21U) & 0x7FU)]);
        aWandererB = RotL64(aWandererB * 8434741120220886235ULL, 21U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // carry = carry + (s0 ^ s1 ^ s2 ^ e);
        // carry = rot(carry * hot.mul);
        // carry = carry ^ (carry >> rshift);
        //
        aCarry = aCarry + (aWandererD ^ aWandererC ^ RotL64(aWandererB, 7U) ^ aCurrent);
        aCarry = RotL64(aCarry * 5937244912172485557ULL, 53U);
        aCarry = aCarry ^ ShiftR64(aCarry, 23U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        // __END_CSPRNG
    }

    // Secure zero on crypto buffer.

    TwistMemory::ZeroBlock(aExpandLaneA);

    pCryptoGenerator->Salt(aWorkLaneB, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);
    // Making snow counter: aria 256

    TwistSnow::Aria256Counter(pSource, aExpandLaneA);

    TwistMemory::GrowB(mScratchSaltB, aDerivedSaltC, 128U);
    TwistMemory::GrowA(mScratchSaltC, aDerivedSaltB, 128U);
    TwistMemory::GrowB(mScratchSaltD, aDerivedSaltA, 128U);
    TwistMemory::GrowA(mScratchSaltA, mSaltD, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aPrevious = aCurrent;
        aCurrent = aWorkLaneB[aIndex] ^ ShiftL64(aExpandLaneA[aIndex], 32U);
        aCross = aWorkLaneC[aIndex];
        // __START_CSPRNG
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // scatter = mix(secure_a, secure_b, previous)
        //
        aScatter = TwistMix64::DiffuseA(ShiftL64(aCurrent, 32U) ^ aCross ^ RotL64(aPrevious, 19U));
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = s0 + rot(e) + hot.add + plug[+];
        // b = s1 ^ rot(previous) ^ hot.add ^ plug[^];
        // c = s2 + rot(cross) + fixedSalt[i/~i] + scratchSalt[~i/i];
        // d = rot(carry) ^ rot(e) ^ fixedSalt[i/~i] ^ scratchSalt[~i/i];
        // prism = e;
        //
        aOrbitA = aWandererB + RotL64(aCurrent, 13U) + 7246008453559932802ULL + mScratchSaltA[((RotL64(aWandererB, 21U) ^ aOrbitB) & 0x7FU)];
        aOrbitB = aWandererD ^ RotL64(aPrevious, 11U) ^ 1641784324028557666ULL ^ mScratchSaltC[((aOrbitC + RotL64(aPrevious, 29U)) & 0x7FU)];
        aOrbitD = aWandererA + RotL64(aCross, 35U) + aDerivedSaltD[((aIndex + 124U) & 0x7FU)] + mScratchSaltB[((127U - aIndex + 78U) & 0x7FU)];
        aOrbitC = RotL64(aCarry, 37U) ^ RotL64(aCurrent, 27U) ^ aDerivedSaltB[((127U - aIndex + 90U) & 0x7FU)] ^ mScratchSaltD[((aIndex + 60U) & 0x7FU)];
        aPrism = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(c) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitB + 1456765845398311662ULL + mScratchSaltA[((aOrbitD + RotL64(aCross, 19U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitA ^ 13044209747458802960ULL ^ mScratchSaltC[((aCarry + RotL64(aWandererD, 13U)) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 12057796655271550625ULL, 53U);
        aPrism = (aPrism ^ aOrbitD ^ RotL64(aCarry, 11U) ^ 9720842938350340739ULL) * 4279556427703418523ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b);
        // prism = (prism OP mix(a) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitC + 7509277871636604158ULL + mScratchSaltB[((RotL64(aWandererA, 21U)) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitD ^ 15139593990703794534ULL ^ mScratchSaltD[((RotL64(aOrbitA, 19U)) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB, 51U);
        aPrism = (aPrism + (aOrbitA ^ RotL64(aCarry, 1U)) + 13552303260211204217ULL) * 5144134835293601509ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // a = a + b + hot.add + plug[+];
        // d = d ^ a ^ hot.add ^ plug[^];
        // d = rot(d * hot.mul);
        // prism = (prism OP mix(b) OP hot.add) * hot.mul;
        //
        aOrbitA = aOrbitA + aOrbitB + 7246008453559932802ULL + mScratchSaltC[((aOrbitB ^ RotL64(aScatter, 29U)) & 0x7FU)];
        aOrbitC = aOrbitC ^ aOrbitA ^ 1641784324028557666ULL ^ mScratchSaltA[((RotL64(aOrbitC, 13U) ^ aWandererB) & 0x7FU)];
        aOrbitC = RotL64(aOrbitC * 7079640241103073353ULL, 11U);
        aPrism = (aPrism ^ aOrbitB ^ 1456765845398311662ULL) * 17502805861687839283ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // c = c + d + hot.add + plug[+];
        // b = b ^ c ^ hot.add ^ plug[^];
        // b = rot(b * hot.mul);
        // prism = (prism OP mix(d) OP hot.add) * hot.mul;
        //
        aOrbitD = aOrbitD + aOrbitC + 13044209747458802960ULL + mScratchSaltD[((RotL64(aOrbitD, 21U) + aScatter) & 0x7FU)];
        aOrbitB = aOrbitB ^ aOrbitD ^ 9720842938350340739ULL ^ mScratchSaltB[((aPrevious + RotL64(aCarry, 19U)) & 0x7FU)];
        aOrbitB = RotL64(aOrbitB * 4279556427703418523ULL, 45U);
        aPrism = (aPrism + (aOrbitC ^ RotL64(aCarry, 5U)) + 7509277871636604158ULL) * 8398764142244882037ULL;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // e = mix(a, b, c, d)
        // e = diffuse(e OP scatter)
        // dest[~i] = e
        //
        aCurrent = (RotL64(aOrbitA, 29U) ^ aOrbitC) + (aOrbitB ^ RotL64(aOrbitD, 11U));
        aCurrent = TwistMix64::DiffuseC(aCurrent ^ aScatter);
        aWorkLaneD[S_BLOCK1 - aIndex] = aCurrent;
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseA(aPrism);
        //
        // prism = diffuse(prism)
        // feedback gate: e = gate(e, prism)
        //
        aPrism = TwistMix64::DiffuseB(aPrism);
        if ((aPrism & 0x24U) > 18) {
        	if ((aPrism & 0x24U) > 35) {
        		aCurrent = TwistMix64::GateRoll_8_8(aCurrent, 13ULL, aDerivedSBoxB, aDerivedSBoxG, aDerivedSBoxE, aDerivedSBoxH, aDerivedSBoxD, aDerivedSBoxA, aDerivedSBoxF, aDerivedSBoxC);
        	} else {
        		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 35ULL, aDerivedSBoxB, aDerivedSBoxG, aDerivedSBoxE, aDerivedSBoxH, aDerivedSBoxD, aDerivedSBoxA, aDerivedSBoxF, aDerivedSBoxC);
        	}
        } else {
        	if ((aPrism & 0x24U) > 0) {
        		aCurrent = TwistMix64::GateTurn_8_8(aCurrent, 7ULL, aDerivedSBoxB, aDerivedSBoxG, aDerivedSBoxE, aDerivedSBoxH, aDerivedSBoxD, aDerivedSBoxA, aDerivedSBoxF, aDerivedSBoxC);
        	} else {
        		aCurrent = TwistMix64::GatePrism_8_8(aCurrent, aDerivedSBoxB, aDerivedSBoxG, aDerivedSBoxE, aDerivedSBoxH, aDerivedSBoxD, aDerivedSBoxA, aDerivedSBoxF, aDerivedSBoxC);
        	}
        }
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s0 = s0 + (e ^ previous ^ d);
        // s0 = rot((s0 + loopSalt[i/~i]) * hot.mul);
        //
        aWandererB = aWandererB + (aCurrent ^ aPrevious ^ RotL64(aOrbitC, 27U));
        aWandererB = RotL64((aWandererB + mSaltC[((aIndex + 32U) & 0x7FU)]) * 4890825653776994427ULL, 45U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s1 = s1 ^ (e + cross + a);
        // s1 = rot((s1 ^ loopSalt[i/~i]) * hot.mul);
        //
        aWandererD = aWandererD ^ (aCurrent + RotL64(aCross, 21U) + aOrbitA);
        aWandererD = RotL64((aWandererD ^ aDerivedSaltC[((127U - aIndex + 67U) & 0x7FU)]) * 5376333057228888275ULL, 43U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // s2 = s2 + (b ^ c ^ loopSalt[i/~i]);
        // s2 = rot(s2 * hot.mul);
        //
        aWandererA = aWandererA + (RotL64(aOrbitB, 37U) ^ aOrbitD ^ mSaltD[((aIndex + 101U) & 0x7FU)]);
        aWandererA = RotL64(aWandererA * 7079640241103073353ULL, 51U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        //
        // carry = carry + (s0 ^ s1 ^ s2 ^ e);
        // carry = rot(carry * hot.mul);
        // carry = carry ^ (carry >> rshift);
        //
        aCarry = aCarry + (aWandererB ^ aWandererD ^ RotL64(aWandererA, 19U) ^ aCurrent);
        aCarry = RotL64(aCarry * 17502805861687839283ULL, 11U);
        aCarry = aCarry ^ ShiftR64(aCarry, 33U);
        //
        // >>>>>>>>>>>>>>>>>>>>>>>>[ BUILD THE BEAST ]<<<<<<<<<<<<<<<<<<<<<<<<
        // __END_CSPRNG
    }

    // Secure zero on crypto buffer.

    TwistMemory::ZeroBlock(aExpandLaneA);

    pCryptoGenerator->Salt(aWorkLaneD, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSaltA, pWorkspace->mDerivedSaltB, pWorkspace->mDerivedSaltC, pWorkspace->mDerivedSaltD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD, pWorkspace->mDerivedSBoxA, pWorkspace->mDerivedSBoxB, pWorkspace->mDerivedSBoxC, pWorkspace->mDerivedSBoxD);
}

void TwistExpander_Goose::TwistBlock(TwistWorkSpace *pWorkspace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkspace, pSource, pDestination);
    if ((pWorkspace == nullptr) || (pDestination == nullptr)) { return; }
    std::memcpy(pDestination, pWorkspace->mWorkLaneD, S_BLOCK);
}
