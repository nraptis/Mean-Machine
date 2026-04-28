#include "TwistExpander_FrodoShire.hpp"
#include "TwistFunctional.hpp"

#include <cstring>

const std::uint8_t TwistExpander_FrodoShire::kSBoxA[S_SBOX] = {
    0x9E, 0x28, 0x4B, 0x94, 0x19, 0x91, 0x41, 0x5E, 0x74, 0x49, 0x4E, 0x12, 0xC6, 0xF1, 0x56, 0x8D, 
    0xED, 0x61, 0x81, 0xEE, 0x16, 0xC0, 0xB0, 0xB3, 0x2C, 0x9D, 0x9F, 0x86, 0x11, 0xE5, 0x5D, 0x48, 
    0x8C, 0xAA, 0xA2, 0x0B, 0x0E, 0xC7, 0x0F, 0x97, 0xA4, 0x23, 0xA0, 0x75, 0x31, 0x42, 0xB2, 0x9C, 
    0x5F, 0xF4, 0x1D, 0x24, 0x85, 0xB4, 0x99, 0x6B, 0x33, 0x20, 0xCB, 0x1C, 0xD5, 0xCD, 0x9A, 0xE1, 
    0x46, 0xA7, 0xAE, 0x2F, 0xE9, 0x87, 0xAC, 0x35, 0xA3, 0x17, 0x37, 0x5C, 0xB8, 0xDA, 0xC2, 0x1B, 
    0x65, 0x8B, 0x8F, 0xAF, 0x71, 0x6C, 0xF6, 0x6A, 0x57, 0x2B, 0x45, 0xBD, 0xA9, 0xD3, 0x06, 0xFB, 
    0x4D, 0x05, 0x90, 0xD0, 0x60, 0x15, 0x18, 0xDD, 0x1A, 0x7A, 0x25, 0x44, 0x09, 0xAB, 0x7D, 0x3A, 
    0xCF, 0x59, 0x0C, 0x78, 0x64, 0xD7, 0x7B, 0xA5, 0xEF, 0x4A, 0xE8, 0xB7, 0x8A, 0x00, 0xDF, 0xE7, 
    0x51, 0x50, 0xE6, 0x69, 0xBA, 0x72, 0xDC, 0x36, 0x98, 0x89, 0x82, 0x6D, 0x22, 0x10, 0x43, 0x9B, 
    0xF2, 0x0D, 0xBF, 0x92, 0xDB, 0xD4, 0xCE, 0xC4, 0x76, 0xC3, 0x3F, 0x5A, 0x38, 0x7C, 0xEC, 0x2E, 
    0xB6, 0xDE, 0xD1, 0x2A, 0xC5, 0xF5, 0xA1, 0xD6, 0xE2, 0x21, 0xEA, 0x58, 0x08, 0xD8, 0x66, 0x3E, 
    0x0A, 0x47, 0xC8, 0xEB, 0xD2, 0x5B, 0x79, 0xFC, 0x2D, 0x73, 0x63, 0x13, 0xE4, 0x52, 0x40, 0x80, 
    0x95, 0xF8, 0x67, 0x04, 0x55, 0x4F, 0xE0, 0x32, 0xB9, 0x54, 0x27, 0x39, 0x6F, 0x29, 0xA8, 0x6E, 
    0xF7, 0x01, 0x26, 0x88, 0x03, 0xE3, 0xC9, 0xFA, 0x34, 0x62, 0xB5, 0xF9, 0xB1, 0x8E, 0x93, 0xBB, 
    0x70, 0xBC, 0xC1, 0x4C, 0x3B, 0x84, 0xBE, 0x1E, 0xAD, 0xFF, 0x77, 0x7F, 0x3D, 0x1F, 0x7E, 0xFE, 
    0x14, 0xF3, 0x02, 0x96, 0x83, 0xCC, 0xA6, 0xFD, 0xCA, 0x07, 0x68, 0x3C, 0x30, 0xD9, 0x53, 0xF0
};

const std::uint8_t TwistExpander_FrodoShire::kSBoxB[S_SBOX] = {
    0x7A, 0xD9, 0x39, 0x3A, 0x68, 0x8C, 0x79, 0x8E, 0xB5, 0x66, 0x8F, 0xE3, 0x6B, 0xF8, 0x91, 0xEF, 
    0x9B, 0x02, 0x8D, 0x0F, 0x9E, 0x49, 0x3C, 0xA8, 0xA4, 0xEE, 0xB1, 0x64, 0x77, 0x84, 0x1A, 0xAD, 
    0x24, 0x7D, 0x62, 0x36, 0x80, 0xA0, 0x4B, 0xAE, 0x40, 0x52, 0x3D, 0x7E, 0x0C, 0xED, 0x63, 0x25, 
    0x45, 0x4E, 0x15, 0xBB, 0xF0, 0x41, 0x93, 0x42, 0x53, 0xC6, 0xC2, 0xDE, 0xFE, 0xE0, 0x07, 0xF9, 
    0x90, 0xD4, 0x00, 0x30, 0xE6, 0xAF, 0x5F, 0x71, 0xA9, 0x55, 0x2E, 0xD1, 0x23, 0x08, 0x16, 0x37, 
    0x7F, 0xCD, 0xB0, 0xCB, 0x03, 0xAB, 0x11, 0x89, 0x5A, 0x4D, 0x04, 0x95, 0xE9, 0xDC, 0x9F, 0xB8, 
    0x1B, 0x0B, 0x47, 0x48, 0xC9, 0x0A, 0xA3, 0xE1, 0xFC, 0x88, 0x70, 0xCF, 0x69, 0xB6, 0x61, 0x87, 
    0xBF, 0x67, 0xDF, 0xD7, 0xB4, 0xA1, 0x43, 0x8B, 0xC4, 0xF2, 0x2D, 0xD5, 0x06, 0xBD, 0xBE, 0xDB, 
    0x78, 0xB3, 0x10, 0x1D, 0x7C, 0x97, 0x2A, 0xE5, 0x58, 0x92, 0x19, 0x60, 0x99, 0xBC, 0x26, 0xCC, 
    0x6C, 0x14, 0xCA, 0x18, 0xC3, 0x35, 0x74, 0x34, 0xEA, 0xDD, 0x31, 0xF3, 0xD8, 0xAA, 0x50, 0xFB, 
    0x1E, 0x75, 0x83, 0x86, 0xFF, 0x85, 0xF6, 0x6A, 0x6D, 0x0D, 0x72, 0xAC, 0xA2, 0x57, 0xEB, 0xFA, 
    0xFD, 0x5B, 0x56, 0xB9, 0x17, 0x38, 0x1C, 0x51, 0x6F, 0x5C, 0x5D, 0x28, 0x4F, 0xEC, 0xB2, 0x46, 
    0xF1, 0x2C, 0x20, 0xC0, 0x05, 0x44, 0x32, 0x98, 0xE8, 0xCE, 0x2F, 0x13, 0x3F, 0x12, 0x22, 0xF4, 
    0xDA, 0x76, 0xE4, 0x59, 0x29, 0xA6, 0x9D, 0x73, 0xBA, 0x96, 0x8A, 0xE7, 0xF7, 0x7B, 0xD3, 0xB7, 
    0xC8, 0x5E, 0x82, 0xD0, 0x4C, 0x3B, 0x01, 0x81, 0x94, 0xC5, 0x21, 0x3E, 0x6E, 0x4A, 0xF5, 0x0E, 
    0xC1, 0xA7, 0xE2, 0x65, 0xD2, 0x2B, 0x1F, 0x9A, 0x09, 0x54, 0xD6, 0xA5, 0xC7, 0x9C, 0x27, 0x33
};

const std::uint8_t TwistExpander_FrodoShire::kSBoxC[S_SBOX] = {
    0x64, 0x36, 0x56, 0x6C, 0xCE, 0xCD, 0x5E, 0xF3, 0xA3, 0xD7, 0xF7, 0x62, 0xF4, 0x88, 0x7A, 0x45, 
    0x00, 0x06, 0xC9, 0x25, 0x67, 0x70, 0x31, 0x14, 0x33, 0x41, 0xC0, 0xE9, 0x47, 0x89, 0xD6, 0x73, 
    0xE1, 0x3D, 0xB4, 0x4B, 0xEA, 0x50, 0x4E, 0x49, 0x30, 0x9A, 0x35, 0x07, 0x1F, 0x7B, 0xB0, 0xE5, 
    0x57, 0x29, 0xCB, 0xBA, 0xCC, 0x34, 0x44, 0x0E, 0x9E, 0xBF, 0xDC, 0x6F, 0xD5, 0x58, 0x61, 0x8C, 
    0x7E, 0x15, 0x38, 0x16, 0x05, 0x4D, 0xB9, 0x1A, 0x10, 0xC3, 0x9B, 0x72, 0xB8, 0x7C, 0xF1, 0x4F, 
    0x03, 0xC1, 0xC4, 0x9C, 0x02, 0x2E, 0xA8, 0xAA, 0xDE, 0x13, 0x5B, 0x19, 0x18, 0x51, 0x63, 0x80, 
    0xD2, 0x46, 0x69, 0x74, 0xA2, 0x42, 0x6A, 0x5C, 0xEB, 0xAE, 0x1E, 0xFF, 0xCA, 0x99, 0x8E, 0xB3, 
    0xD9, 0xD3, 0x6B, 0x2F, 0xA7, 0x54, 0x0A, 0x94, 0x81, 0xF2, 0xA1, 0x11, 0x65, 0xE7, 0xDD, 0x08, 
    0x5A, 0xFE, 0xAC, 0x8F, 0x39, 0x27, 0xF8, 0x3F, 0xE0, 0x40, 0xEC, 0x8A, 0x3E, 0xE3, 0xDF, 0xC5, 
    0xAD, 0xCF, 0x98, 0xE8, 0xD8, 0x71, 0x7D, 0x75, 0x22, 0x55, 0x12, 0xF6, 0x32, 0x2A, 0xA4, 0xB2, 
    0xB5, 0x79, 0xD0, 0xB7, 0xD1, 0x8D, 0x91, 0xF0, 0xA9, 0x1B, 0x20, 0x77, 0x6E, 0xFD, 0x26, 0xB6, 
    0xEF, 0xDA, 0xF9, 0x84, 0xF5, 0x52, 0x8B, 0xA0, 0x97, 0x83, 0x87, 0xC6, 0x2D, 0x7F, 0xFA, 0x6D, 
    0xC8, 0xA5, 0x82, 0xE2, 0x5F, 0x53, 0x28, 0x3A, 0x1C, 0xFB, 0x9F, 0x96, 0x0B, 0x92, 0xBC, 0xAF, 
    0x0C, 0x43, 0x3B, 0xE4, 0xC2, 0x0D, 0x5D, 0x24, 0xBE, 0x23, 0x90, 0x01, 0x95, 0x60, 0x4C, 0x9D, 
    0xA6, 0xBD, 0xD4, 0x76, 0x17, 0x68, 0x3C, 0xEE, 0x1D, 0x85, 0x86, 0x0F, 0x93, 0x4A, 0xAB, 0x21, 
    0xE6, 0x09, 0x66, 0xED, 0x48, 0xFC, 0xB1, 0x04, 0x78, 0xC7, 0x2B, 0x37, 0xBB, 0x59, 0xDB, 0x2C
};

const std::uint8_t TwistExpander_FrodoShire::kSBoxD[S_SBOX] = {
    0x48, 0x94, 0xE1, 0xD1, 0xDB, 0x74, 0x78, 0xFE, 0x54, 0x9A, 0x44, 0x84, 0xEB, 0xBC, 0x1C, 0x4F, 
    0x87, 0x4B, 0xCE, 0x3A, 0xE7, 0xF3, 0x81, 0x3C, 0xF7, 0xF5, 0x8E, 0x10, 0x39, 0x65, 0x43, 0x5C, 
    0x89, 0xA2, 0x40, 0x1A, 0xBF, 0x2D, 0x79, 0x6C, 0x58, 0xCB, 0x3B, 0x92, 0x0A, 0xC5, 0xFA, 0x33, 
    0x38, 0x19, 0xB8, 0x15, 0xAD, 0xE2, 0x96, 0xD2, 0x71, 0x76, 0xAC, 0x7E, 0xEC, 0xB4, 0x2B, 0x06, 
    0xA6, 0xE5, 0xC1, 0x4A, 0xE4, 0xD6, 0xBA, 0x69, 0x86, 0x21, 0x12, 0x85, 0x63, 0xD0, 0x88, 0xA0, 
    0x28, 0x57, 0x34, 0x07, 0xF1, 0x0C, 0x62, 0x14, 0xDA, 0x29, 0x1B, 0xC6, 0x1F, 0xF4, 0x5D, 0x25, 
    0xF9, 0xE0, 0xB2, 0x49, 0x8D, 0x5A, 0x1D, 0x0E, 0x66, 0xAE, 0xD3, 0xDD, 0x61, 0x64, 0x70, 0x55, 
    0xCF, 0x20, 0xC4, 0xD5, 0xEE, 0x97, 0x68, 0x9E, 0xFC, 0x27, 0x22, 0x5F, 0x91, 0x45, 0x75, 0x1E, 
    0xC2, 0x04, 0xD8, 0xA9, 0x18, 0x4C, 0xC8, 0xD4, 0x50, 0x2C, 0x73, 0xCA, 0x0D, 0xFF, 0x03, 0xED, 
    0x01, 0x02, 0xBD, 0xC9, 0x16, 0x2A, 0x09, 0x90, 0x2F, 0x4E, 0xF0, 0x9D, 0x2E, 0xB6, 0x41, 0x8C, 
    0x99, 0xB3, 0x8F, 0xEF, 0x56, 0xDF, 0xFD, 0x51, 0xBB, 0xB0, 0x59, 0xE6, 0xA7, 0xAB, 0x95, 0x36, 
    0xDC, 0x60, 0x11, 0x9F, 0x32, 0x5B, 0x13, 0xFB, 0x31, 0x8A, 0x30, 0x42, 0xA3, 0x7F, 0xBE, 0x08, 
    0x17, 0x98, 0x53, 0x26, 0xA1, 0x82, 0xC0, 0xB7, 0xA5, 0x67, 0xA8, 0xE8, 0xB1, 0x52, 0xD9, 0x77, 
    0xA4, 0x83, 0x6E, 0xEA, 0xF8, 0x7D, 0xD7, 0xE3, 0xAF, 0xF6, 0x24, 0x5E, 0x47, 0xF2, 0x0F, 0xDE, 
    0x37, 0x00, 0x35, 0x3F, 0x93, 0x6B, 0x7B, 0x05, 0x7C, 0x46, 0xE9, 0x0B, 0x8B, 0xC3, 0xCD, 0x80, 
    0x9C, 0xC7, 0x3E, 0xAA, 0xB5, 0x72, 0x23, 0x3D, 0x6A, 0x9B, 0x6F, 0x4D, 0xCC, 0x6D, 0xB9, 0x7A
};

const std::uint8_t TwistExpander_FrodoShire::kSaltA[S_SALT] = {
    0x45, 0x65, 0xC5, 0xCA, 0x7F, 0xFA, 0xC0, 0x44, 0xE6, 0x94, 0xF7, 0xE3, 0x90, 0x72, 0xF0, 0x4F, 
    0x07, 0x74, 0x0B, 0xCE, 0xA1, 0x55, 0x5B, 0x26, 0xDA, 0xEC, 0x67, 0x1B, 0xEC, 0xE0, 0xF4, 0x49, 
    0x5D, 0x36, 0x99, 0xA3, 0x9A, 0x55, 0x54, 0xB8, 0xD7, 0xC7, 0x06, 0x98, 0xA9, 0x18, 0x58, 0xD8, 
    0x5E, 0x94, 0xB3, 0xCB, 0x3C, 0x3A, 0x83, 0xBF, 0xAD, 0x6A, 0xBF, 0xE8, 0x29, 0xCF, 0x75, 0xF8, 
    0x1B, 0x50, 0x90, 0xB6, 0x90, 0xE8, 0xA3, 0x0A, 0xAE, 0x00, 0x51, 0xD7, 0x8B, 0xEE, 0x49, 0x0B, 
    0xD8, 0x00, 0x85, 0x67, 0x4A, 0xDC, 0x48, 0xF8, 0x8E, 0xAF, 0xAE, 0xE6, 0xD0, 0x4D, 0x44, 0xBF, 
    0xB2, 0x6F, 0xEB, 0x68, 0xE7, 0x52, 0x1E, 0xEC, 0x78, 0xBD, 0x9E, 0xE4, 0x77, 0x36, 0xE9, 0x3F, 
    0x2A, 0xC1, 0x12, 0x02, 0xB3, 0xE3, 0xA4, 0xBE, 0xAF, 0xD4, 0x57, 0x32, 0x05, 0xF8, 0x8F, 0x2D
};

const std::uint8_t TwistExpander_FrodoShire::kSaltB[S_SALT] = {
    0x1C, 0x5A, 0x7D, 0x8C, 0xE6, 0x3B, 0x59, 0xAF, 0x80, 0x87, 0x60, 0xA2, 0x4C, 0x34, 0xB4, 0xC8, 
    0x18, 0xCF, 0x64, 0xB3, 0xE5, 0xE9, 0x95, 0x99, 0x96, 0xC0, 0x07, 0xF7, 0xCF, 0xD8, 0x22, 0x0D, 
    0xDE, 0x36, 0x32, 0xC9, 0xC1, 0x1D, 0xFB, 0x72, 0xFD, 0x3F, 0x76, 0xEC, 0x75, 0xAA, 0x65, 0x9C, 
    0x23, 0x89, 0xA3, 0x1A, 0x3B, 0xB6, 0x45, 0x49, 0x64, 0x28, 0x50, 0x6A, 0x25, 0x15, 0x5A, 0xB9, 
    0x6A, 0xA4, 0x53, 0x1F, 0x3A, 0xD9, 0x2A, 0x76, 0x13, 0x0E, 0xD8, 0x0E, 0xB2, 0x49, 0x6C, 0xA7, 
    0x78, 0x9F, 0x6D, 0xD3, 0xC8, 0x8B, 0xFA, 0xB4, 0x00, 0xB2, 0x11, 0xDB, 0xDD, 0xB0, 0x77, 0x4C, 
    0xCC, 0x14, 0x09, 0xF3, 0x47, 0x07, 0x19, 0x84, 0x74, 0x60, 0x56, 0x5B, 0xEF, 0xCD, 0xD3, 0xC7, 
    0x7C, 0x09, 0x7D, 0x99, 0xFE, 0x7F, 0x1D, 0x28, 0x13, 0xFE, 0x8D, 0x1B, 0xC0, 0x84, 0x00, 0x2A
};

const std::uint8_t TwistExpander_FrodoShire::kSaltC[S_SALT] = {
    0xFA, 0x0E, 0xD6, 0x06, 0x0C, 0x0C, 0xF7, 0x6A, 0xF7, 0x0F, 0xD9, 0xB5, 0xEA, 0x1A, 0xE2, 0x0A, 
    0xCC, 0xF0, 0x12, 0xA9, 0x21, 0x8B, 0x0C, 0xB9, 0x7A, 0xEA, 0x7A, 0x64, 0x0B, 0x25, 0x83, 0xDD, 
    0x95, 0xFB, 0x7F, 0xD2, 0xFA, 0x1D, 0xAC, 0xEB, 0x8E, 0x3C, 0x58, 0x91, 0xA7, 0x46, 0x0C, 0x5D, 
    0x02, 0x44, 0x86, 0x7E, 0x63, 0xF4, 0xF2, 0x3C, 0x1D, 0x03, 0x77, 0x8A, 0x33, 0x71, 0x4F, 0xE2, 
    0x70, 0x6F, 0xC1, 0x65, 0xAB, 0xDA, 0x20, 0x1F, 0xFD, 0x8B, 0x70, 0x3C, 0xF0, 0x89, 0xC3, 0x0C, 
    0xC0, 0x7D, 0xA6, 0x0C, 0x33, 0x82, 0x11, 0x5C, 0xD1, 0x98, 0xD0, 0x2D, 0xE5, 0x07, 0x5A, 0xA3, 
    0xD9, 0xC5, 0xD2, 0x07, 0x53, 0xEC, 0x78, 0xA5, 0xA6, 0x21, 0xCE, 0x37, 0x1A, 0x61, 0xAB, 0x58, 
    0x93, 0x00, 0x37, 0x2A, 0xAC, 0x22, 0xE1, 0x57, 0xCE, 0x89, 0x13, 0xC7, 0xAC, 0xBE, 0x28, 0xFD
};

const std::uint8_t TwistExpander_FrodoShire::kSaltD[S_SALT] = {
    0x41, 0x80, 0x79, 0xF1, 0x14, 0xE7, 0xEF, 0x9E, 0x72, 0xF2, 0x13, 0xAF, 0x59, 0xE1, 0xDE, 0xCC, 
    0x99, 0xBF, 0x1D, 0x9E, 0xF4, 0x81, 0x9C, 0x17, 0xD9, 0x1F, 0xBA, 0x29, 0xC4, 0x3E, 0x95, 0x05, 
    0x48, 0x03, 0xAF, 0x77, 0x5C, 0x08, 0x10, 0x1E, 0x1E, 0x00, 0x69, 0x4E, 0x4C, 0xCF, 0x83, 0x7B, 
    0xA5, 0xE8, 0x12, 0x17, 0x7B, 0x5E, 0x8F, 0xB0, 0x90, 0x1F, 0xAA, 0x3E, 0xEF, 0xCD, 0xC7, 0x43, 
    0x1C, 0xCC, 0x4D, 0x70, 0x53, 0xDC, 0x65, 0xD2, 0x5B, 0x8B, 0x0F, 0x16, 0x9B, 0x4A, 0xB5, 0x1F, 
    0xB1, 0x9F, 0xE9, 0x5B, 0xEC, 0x84, 0x97, 0xD1, 0x4E, 0xEA, 0xBC, 0xAD, 0xE8, 0x99, 0x6B, 0x11, 
    0xE2, 0xD6, 0x86, 0x5B, 0x97, 0x25, 0xF3, 0x82, 0x2D, 0x73, 0x2B, 0xBA, 0x55, 0xEC, 0x19, 0x16, 
    0x1A, 0xE8, 0x48, 0xC6, 0x6C, 0x79, 0x83, 0x95, 0x99, 0x33, 0xB7, 0x94, 0x0C, 0xFC, 0x7A, 0x0E
};

TwistExpander_FrodoShire::TwistExpander_FrodoShire()
: TwistExpander() {
    mSBoxA = const_cast<std::uint8_t*>(kSBoxA);
    mSBoxB = const_cast<std::uint8_t*>(kSBoxB);
    mSBoxC = const_cast<std::uint8_t*>(kSBoxC);
    mSBoxD = const_cast<std::uint8_t*>(kSBoxD);
    mSaltA = const_cast<std::uint8_t*>(kSaltA);
    mSaltB = const_cast<std::uint8_t*>(kSaltB);
    mSaltC = const_cast<std::uint8_t*>(kSaltC);
    mSaltD = const_cast<std::uint8_t*>(kSaltD);
}

void TwistExpander_FrodoShire::Seed(TwistWorkSpace *pWorkspace,
                                 std::uint8_t *pSource,
                                 std::uint8_t *pPassword,
                                 unsigned int pPasswordByteLength) {
    TwistExpander::Seed(pWorkspace, pSource, pPassword, pPasswordByteLength);
    if (pWorkspace == nullptr) { return; }
    std::uint8_t *aSource = pSource;
    [[maybe_unused]] std::uint8_t *aSaltA = pWorkspace->mSaltA;
    [[maybe_unused]] std::uint8_t *aSaltB = pWorkspace->mSaltB;
    [[maybe_unused]] std::uint8_t *aSaltC = pWorkspace->mSaltC;
    [[maybe_unused]] std::uint8_t *aSaltD = pWorkspace->mSaltD;
    [[maybe_unused]] std::uint8_t *aSBoxA = pWorkspace->mSBoxA;
    [[maybe_unused]] std::uint8_t *aSBoxB = pWorkspace->mSBoxB;
    [[maybe_unused]] std::uint8_t *aSBoxC = pWorkspace->mSBoxC;
    [[maybe_unused]] std::uint8_t *aSBoxD = pWorkspace->mSBoxD;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkspace->mExpandLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkspace->mExpandLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkspace->mExpandLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkspace->mExpandLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkspace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkspace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aMaskLaneA = pWorkspace->mMaskLaneA;
    [[maybe_unused]] std::uint8_t *aMaskLaneB = pWorkspace->mMaskLaneB;
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
    std::uint32_t aValueByteA = 0;
    std::uint8_t aSourceByteA = 0;
    std::uint32_t aSourceKeyA = 0;
    std::uint32_t aSaltCKeyA = 0;
    std::uint8_t aValueNibbleA = 0;
    std::uint8_t aValueNibbleB = 0;
    std::uint8_t aValueNibbleC = 0;
    std::uint8_t aValueNibbleD = 0;
    std::uint32_t aCarryByteA = 0;
    std::uint32_t aPermuteByteA = 0;
    std::uint32_t aSaltBKeyA = 0;
    std::uint32_t aSBoxAKeyA = 0;
    std::uint32_t aSaltDKeyA = 0;
    std::uint32_t aWorkLaneAKeyA = 0;
    std::uint8_t aWorkLaneAByteA = 0;
    std::uint32_t aWorkLaneAKeyB = 0;
    std::uint32_t aSBoxBKeyA = 0;
    std::uint32_t aSaltAKeyA = 0;
    std::uint32_t aWorkLaneBKeyA = 0;
    std::uint32_t aWorkLaneCKeyA = 0;
    std::uint32_t aSBoxDKeyA = 0;
    std::uint8_t aWorkLaneDByteA = 0;
    std::uint32_t aWorkLaneDKeyA = 0;
    std::uint32_t aSBoxCKeyA = 0;
    std::uint32_t aSourceKeyB = 0;
    std::uint8_t aWorkLaneBByteA = 0;
    std::uint32_t aWorkLaneBKeyB = 0;

    std::uint32_t aValue = 0x43;
    std::uint32_t aCarry = 0xDF;
    std::uint32_t aPermute = 0xB0;

    {
            for (std::uint32_t aLoopIndex = 0U; aLoopIndex < S_BLOCK; aLoopIndex += 1U) {
                aValueByteA = aValue - 17U;
                aSourceKeyA = aLoopIndex + 5008U;
                if (aSourceKeyA >= S_BLOCK) { aSourceKeyA -= S_BLOCK; }
                aSourceByteA = RotL8(aSource[aSourceKeyA], 4U);
                aSaltCKeyA = aCarry + 76U;
                aValue = (aValueByteA ^ aSourceByteA) + aSaltC[aSaltCKeyA & 0x7FU];
                aValueNibbleA = aValue & 255U;
                aValueNibbleB = (aValue >> 8U) & 255U;
                aValueNibbleC = (aValue >> 16U) & 255U;
                aValueNibbleD = (aValue >> 24U) & 255U;
                aValueNibbleC = aSBoxC[(aValueNibbleC ^ aValueNibbleB) & 0xFFU];
                aValueNibbleD = aSBoxD[(aValueNibbleD ^ aValueNibbleA) & 0xFFU];
                aValueNibbleB = aSBoxA[(aValueNibbleB ^ aValueNibbleD) & 0xFFU];
                aValueNibbleA = aSBoxB[(aValueNibbleA ^ aValueNibbleC) & 0xFFU];
                aValue = aValueNibbleA |
        		static_cast<std::uint32_t>(aValueNibbleB) << 8U |
        		static_cast<std::uint32_t>(aValueNibbleC) << 16U |
        		static_cast<std::uint32_t>(aValueNibbleD) << 24U;
                aCarryByteA = aCarry ^ 194U;
                aValue = aValue + aCarryByteA;
                aPermuteByteA = aPermute - 9U;
                aSourceKeyA = aLoopIndex + 2894U;
                if (aSourceKeyA >= S_BLOCK) { aSourceKeyA -= S_BLOCK; }
                aSaltBKeyA = aSource[aSourceKeyA] + 111U;
                aPermute = aPermuteByteA + aSaltB[aSaltBKeyA & 0x7FU];
                aPermute = aSBoxC[aPermute & 0xFFU] | (static_cast<std::uint32_t>(aPermute) << 8U);
                aPermute = RotL32(aPermute, 2U);
                aValueByteA = aValue - 14U;
                aPermute = (aPermute + aValueByteA) ^ aCarry;
                aValue = RotL32(aValue, aPermute);
                aCarryByteA = aCarry + 19U;
                aSBoxAKeyA = aLoopIndex + 149U;
                aSaltDKeyA = aValue + 62U;
                aCarry = ((aCarryByteA + aValue) + aSBoxA[aSBoxAKeyA & 0xFFU]) + aSaltD[aSaltDKeyA & 0x7FU];
                aWorkLaneA[aLoopIndex] = aValue;
            }
        
            for (std::uint32_t aLoopIndex = 0U; aLoopIndex < S_BLOCK; aLoopIndex += 1U) {
                aWorkLaneAKeyA = aLoopIndex + 7194U;
                if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }
                aSaltDKeyA = aWorkLaneA[aWorkLaneAKeyA] + 25U;
                aValue = (aValue ^ aCarry) ^ aSaltD[aSaltDKeyA & 0x7FU];
                aValueNibbleA = aValue & 255U;
                aValueNibbleB = (aValue >> 8U) & 255U;
                aValueNibbleC = (aValue >> 16U) & 255U;
                aValueNibbleD = (aValue >> 24U) & 255U;
                aValueNibbleC = aSBoxA[(aValueNibbleC ^ aValueNibbleB) & 0xFFU];
                aValueNibbleD = aSBoxC[(aValueNibbleD + aValueNibbleA) & 0xFFU];
                aValueNibbleB = aSBoxD[(aValueNibbleB ^ aValueNibbleD) & 0xFFU];
                aValueNibbleA = aSBoxB[(aValueNibbleA ^ aValueNibbleC) & 0xFFU];
                aValue = aValueNibbleA |
        		static_cast<std::uint32_t>(aValueNibbleB) << 8U |
        		static_cast<std::uint32_t>(aValueNibbleC) << 16U |
        		static_cast<std::uint32_t>(aValueNibbleD) << 24U;
                aWorkLaneAKeyB = aLoopIndex + 5937U;
                if (aWorkLaneAKeyB >= S_BLOCK) { aWorkLaneAKeyB -= S_BLOCK; }
                aWorkLaneAByteA = aWorkLaneA[aWorkLaneAKeyB] - 2U;
                aValue = aValue + aWorkLaneAByteA;
                aCarryByteA = aCarry + 21U;
                aSBoxBKeyA = aLoopIndex + 56U;
                aValueByteA = RotL8(aValue, 5U);
                aSaltAKeyA = aValue + 84U;
                aCarry = ((aCarryByteA ^ aSBoxB[aSBoxBKeyA & 0xFFU]) ^ aValueByteA) + aSaltA[aSaltAKeyA & 0x7FU];
                aPermute = aPermute ^ aValue;
                aPermute = aSBoxD[aPermute & 0xFFU] | (static_cast<std::uint32_t>(aPermute) << 8U);
                aPermute = RotL32(aPermute, 3U);
                aSaltCKeyA = aLoopIndex + 42U;
                aPermute = aPermute ^ aSaltC[aSaltCKeyA & 0x7FU];
                aValue = RotL32(aValue, aPermute);
                aWorkLaneB[((S_BLOCK - 1) - aLoopIndex)] = aValue;
            }
        
            for (std::uint32_t aLoopIndex = 0U; aLoopIndex < S_BLOCK; aLoopIndex += 1U) {
                aValue = aValue;
                aValueNibbleA = aValue & 255U;
                aValueNibbleB = (aValue >> 8U) & 255U;
                aValueNibbleC = (aValue >> 16U) & 255U;
                aValueNibbleD = (aValue >> 24U) & 255U;
                aValueNibbleC = aSBoxD[(aValueNibbleC ^ aValueNibbleB) & 0xFFU];
                aValueNibbleD = aSBoxC[(aValueNibbleD + aValueNibbleA) & 0xFFU];
                aValueNibbleB = aSBoxA[(aValueNibbleB + aValueNibbleD) & 0xFFU];
                aValueNibbleA = aSBoxB[(aValueNibbleA ^ aValueNibbleC) & 0xFFU];
                aValue = aValueNibbleA |
        		static_cast<std::uint32_t>(aValueNibbleB) << 8U |
        		static_cast<std::uint32_t>(aValueNibbleC) << 16U |
        		static_cast<std::uint32_t>(aValueNibbleD) << 24U;
                aWorkLaneAKeyA = aLoopIndex + 5751U;
                if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }
                aWorkLaneAByteA = RotL8(aWorkLaneA[aWorkLaneAKeyA], 3U);
                aWorkLaneAKeyB = aLoopIndex + 4929U;
                if (aWorkLaneAKeyB >= S_BLOCK) { aWorkLaneAKeyB -= S_BLOCK; }
                aSaltAKeyA = aWorkLaneA[aWorkLaneAKeyB] + 85U;
                aWorkLaneBKeyA = aLoopIndex + 296U;
                if (aWorkLaneBKeyA >= S_BLOCK) { aWorkLaneBKeyA -= S_BLOCK; }
                aValue = ((aValue + aWorkLaneB[aWorkLaneBKeyA]) ^ aWorkLaneAByteA) + aSaltA[aSaltAKeyA & 0x7FU];
                aPermuteByteA = aPermute + 26U;
                aSaltAKeyA = aValue + 116U;
                aSBoxAKeyA = aLoopIndex + 193U;
                aPermute = (aPermuteByteA ^ aSaltA[aSaltAKeyA & 0x7FU]) + aSBoxA[aSBoxAKeyA & 0xFFU];
                aPermute = aSBoxC[aPermute & 0xFFU] | (static_cast<std::uint32_t>(aPermute) << 8U);
                aPermute = RotL32(aPermute, 2U);
                aValueByteA = aValue ^ 80U;
                aPermute = aPermute + aValueByteA;
                aValue = RotL32(aValue, aPermute);
                aWorkLaneC[aLoopIndex] = aValue;
            }
        
            for (std::uint32_t aLoopIndex = 0U; aLoopIndex < S_BLOCK; aLoopIndex += 1U) {
                aValue = aValue + aCarry;
                aValueNibbleA = aValue & 255U;
                aValueNibbleB = (aValue >> 8U) & 255U;
                aValueNibbleC = (aValue >> 16U) & 255U;
                aValueNibbleD = (aValue >> 24U) & 255U;
                aValueNibbleC = aSBoxB[(aValueNibbleC ^ aValueNibbleB) & 0xFFU];
                aValueNibbleD = aSBoxA[(aValueNibbleD ^ aValueNibbleA) & 0xFFU];
                aValueNibbleB = aSBoxC[(aValueNibbleB ^ aValueNibbleD) & 0xFFU];
                aValueNibbleA = aSBoxD[(aValueNibbleA + aValueNibbleC) & 0xFFU];
                aValue = aValueNibbleA |
        		static_cast<std::uint32_t>(aValueNibbleB) << 8U |
        		static_cast<std::uint32_t>(aValueNibbleC) << 16U |
        		static_cast<std::uint32_t>(aValueNibbleD) << 24U;
                aSaltBKeyA = aCarry + 63U;
                aWorkLaneCKeyA = aLoopIndex + 1567U;
                if (aWorkLaneCKeyA >= S_BLOCK) { aWorkLaneCKeyA -= S_BLOCK; }
                aValue = (aValue ^ aWorkLaneC[aWorkLaneCKeyA]) + aSaltB[aSaltBKeyA & 0x7FU];
                aPermuteByteA = aPermute ^ 5U;
                aCarryByteA = RotL8(aCarry, 6U);
                aSourceKeyA = aLoopIndex + 882U;
                if (aSourceKeyA >= S_BLOCK) { aSourceKeyA -= S_BLOCK; }
                aPermute = (aPermuteByteA + aCarryByteA) + aSource[aSourceKeyA];
                aPermute = aSBoxB[aPermute & 0xFFU] | (static_cast<std::uint32_t>(aPermute) << 8U);
                aPermute = RotL32(aPermute, 1U);
                aValueByteA = RotL8(aValue, 4U);
                aWorkLaneCKeyA = aLoopIndex + 2624U;
                if (aWorkLaneCKeyA >= S_BLOCK) { aWorkLaneCKeyA -= S_BLOCK; }
                aSaltCKeyA = aWorkLaneC[aWorkLaneCKeyA] + 91U;
                aPermute = (aPermute + aValueByteA) ^ aSaltC[aSaltCKeyA & 0x7FU];
                aValue = RotL32(aValue, aPermute);
                aCarryByteA = RotL8(aCarry, 2U);
                aSourceKeyA = aLoopIndex + 1251U;
                if (aSourceKeyA >= S_BLOCK) { aSourceKeyA -= S_BLOCK; }
                aSaltBKeyA = aSource[aSourceKeyA] + 16U;
                aSBoxDKeyA = aLoopIndex + 91U;
                aValueByteA = aValue + 12U;
                aCarry = ((aCarryByteA + aSaltB[aSaltBKeyA & 0x7FU]) ^ aSBoxD[aSBoxDKeyA & 0xFFU]) + aValueByteA;
                aWorkLaneD[((S_BLOCK - 1) - aLoopIndex)] = aValue;
            }
    }
    {
            for (std::uint32_t aLoopIndex = 0U; aLoopIndex < S_BLOCK; aLoopIndex += 1U) {
                aValue = aValue;
                aValueNibbleA = aValue & 255U;
                aValueNibbleB = (aValue >> 8U) & 255U;
                aValueNibbleC = (aValue >> 16U) & 255U;
                aValueNibbleD = (aValue >> 24U) & 255U;
                aValueNibbleC = aSBoxC[(aValueNibbleC ^ aValueNibbleB) & 0xFFU];
                aValueNibbleD = aSBoxB[(aValueNibbleD ^ aValueNibbleA) & 0xFFU];
                aValueNibbleB = aSBoxA[(aValueNibbleB ^ aValueNibbleD) & 0xFFU];
                aValueNibbleA = aSBoxD[(aValueNibbleA ^ aValueNibbleC) & 0xFFU];
                aValue = aValueNibbleA |
        		static_cast<std::uint32_t>(aValueNibbleB) << 8U |
        		static_cast<std::uint32_t>(aValueNibbleC) << 16U |
        		static_cast<std::uint32_t>(aValueNibbleD) << 24U;
                aWorkLaneDKeyA = aLoopIndex + 7188U;
                if (aWorkLaneDKeyA >= S_BLOCK) { aWorkLaneDKeyA -= S_BLOCK; }
                aWorkLaneDByteA = aWorkLaneD[aWorkLaneDKeyA] ^ 38U;
                aCarryByteA = aCarry + 7U;
                aSaltBKeyA = aLoopIndex + 93U;
                aValue = ((aValue ^ aWorkLaneDByteA) ^ aCarryByteA) ^ aSaltB[aSaltBKeyA & 0x7FU];
                aCarryByteA = aCarry - 11U;
                aSBoxCKeyA = aLoopIndex + 25U;
                aWorkLaneDKeyA = aLoopIndex + 296U;
                if (aWorkLaneDKeyA >= S_BLOCK) { aWorkLaneDKeyA -= S_BLOCK; }
                aSaltDKeyA = aWorkLaneD[aWorkLaneDKeyA] + 88U;
                aSourceKeyA = aLoopIndex + 3148U;
                if (aSourceKeyA >= S_BLOCK) { aSourceKeyA -= S_BLOCK; }
                aCarry = (((aCarryByteA + aSBoxC[aSBoxCKeyA & 0xFFU]) ^ aValue) ^ aSource[aSourceKeyA]) + aSaltD[aSaltDKeyA & 0x7FU];
                aCarryByteA = aCarry ^ 207U;
                aPermute = aPermute + aCarryByteA;
                aPermute = aSBoxD[aPermute & 0xFFU] | (static_cast<std::uint32_t>(aPermute) << 8U);
                aPermute = RotL32(aPermute, 2U);
                aValueByteA = RotL8(aValue, 5U);
                aSaltDKeyA = aValue + 13U;
                aPermute = (aPermute + aValueByteA) + aSaltD[aSaltDKeyA & 0x7FU];
                aValue = RotL32(aValue, aPermute);
                aWorkLaneA[((S_BLOCK - 1) - aLoopIndex)] = aValue;
            }
        
            for (std::uint32_t aLoopIndex = 0U; aLoopIndex < S_BLOCK; aLoopIndex += 1U) {
                aValueByteA = RotL8(aValue, 7U);
                aSourceKeyB = aLoopIndex + 1768U;
                if (aSourceKeyB >= S_BLOCK) { aSourceKeyB -= S_BLOCK; }
                aSaltCKeyA = aSource[aSourceKeyB] + 76U;
                aSourceKeyA = aLoopIndex + 5158U;
                if (aSourceKeyA >= S_BLOCK) { aSourceKeyA -= S_BLOCK; }
                aValue = ((aValueByteA ^ aSource[aSourceKeyA]) ^ aCarry) ^ aSaltC[aSaltCKeyA & 0x7FU];
                aValueNibbleA = aValue & 255U;
                aValueNibbleB = (aValue >> 8U) & 255U;
                aValueNibbleC = (aValue >> 16U) & 255U;
                aValueNibbleD = (aValue >> 24U) & 255U;
                aValueNibbleC = aSBoxC[(aValueNibbleC ^ aValueNibbleB) & 0xFFU];
                aValueNibbleD = aSBoxA[(aValueNibbleD + aValueNibbleA) & 0xFFU];
                aValueNibbleB = aSBoxD[(aValueNibbleB + aValueNibbleD) & 0xFFU];
                aValueNibbleA = aSBoxB[(aValueNibbleA ^ aValueNibbleC) & 0xFFU];
                aValue = aValueNibbleA |
        		static_cast<std::uint32_t>(aValueNibbleB) << 8U |
        		static_cast<std::uint32_t>(aValueNibbleC) << 16U |
        		static_cast<std::uint32_t>(aValueNibbleD) << 24U;
                aWorkLaneAKeyA = aLoopIndex + 1470U;
                if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }
                aWorkLaneAByteA = aWorkLaneA[aWorkLaneAKeyA] * 19U;
                aValue = aValue ^ aWorkLaneAByteA;
                aCarryByteA = RotL8(aCarry, 5U);
                aSBoxDKeyA = aLoopIndex + 86U;
                aWorkLaneAKeyA = aLoopIndex + 4416U;
                if (aWorkLaneAKeyA >= S_BLOCK) { aWorkLaneAKeyA -= S_BLOCK; }
                aSaltAKeyA = aWorkLaneA[aWorkLaneAKeyA] + 90U;
                aCarry = ((aCarryByteA + aSBoxD[aSBoxDKeyA & 0xFFU]) ^ aValue) + aSaltA[aSaltAKeyA & 0x7FU];
                aWorkLaneB[aLoopIndex] = aValue;
            }
        
            for (std::uint32_t aLoopIndex = 0U; aLoopIndex < S_BLOCK; aLoopIndex += 1U) {
                aValueByteA = aValue ^ 164U;
                aValue = aValueByteA ^ aCarry;
                aValueNibbleA = aValue & 255U;
                aValueNibbleB = (aValue >> 8U) & 255U;
                aValueNibbleC = (aValue >> 16U) & 255U;
                aValueNibbleD = (aValue >> 24U) & 255U;
                aValueNibbleC = aSBoxC[(aValueNibbleC ^ aValueNibbleB) & 0xFFU];
                aValueNibbleD = aSBoxB[(aValueNibbleD ^ aValueNibbleA) & 0xFFU];
                aValueNibbleB = aSBoxA[(aValueNibbleB + aValueNibbleD) & 0xFFU];
                aValueNibbleA = aSBoxD[(aValueNibbleA + aValueNibbleC) & 0xFFU];
                aValue = aValueNibbleA |
        		static_cast<std::uint32_t>(aValueNibbleB) << 8U |
        		static_cast<std::uint32_t>(aValueNibbleC) << 16U |
        		static_cast<std::uint32_t>(aValueNibbleD) << 24U;
                aWorkLaneBKeyA = aLoopIndex + 1145U;
                if (aWorkLaneBKeyA >= S_BLOCK) { aWorkLaneBKeyA -= S_BLOCK; }
                aWorkLaneBByteA = aWorkLaneB[aWorkLaneBKeyA] ^ 78U;
                aWorkLaneBKeyB = aLoopIndex + 5250U;
                if (aWorkLaneBKeyB >= S_BLOCK) { aWorkLaneBKeyB -= S_BLOCK; }
                aSaltDKeyA = aWorkLaneB[aWorkLaneBKeyB] + 20U;
                aValue = (aValue + aWorkLaneBByteA) + aSaltD[aSaltDKeyA & 0x7FU];
                aCarryByteA = aCarry - 14U;
                aSaltCKeyA = aLoopIndex + 96U;
                aCarry = (aCarryByteA + aValue) + aSaltC[aSaltCKeyA & 0x7FU];
                aSaltAKeyA = aCarry + 113U;
                aSBoxBKeyA = aLoopIndex + 171U;
                aPermute = (aPermute ^ aSaltA[aSaltAKeyA & 0x7FU]) + aSBoxB[aSBoxBKeyA & 0xFFU];
                aPermute = aSBoxB[aPermute & 0xFFU] | (static_cast<std::uint32_t>(aPermute) << 8U);
                aPermute = RotL32(aPermute, 4U);
                aValueByteA = aValue ^ 136U;
                aPermute = aPermute + aValueByteA;
                aValue = RotL32(aValue, aPermute);
                aWorkLaneC[((S_BLOCK - 1) - aLoopIndex)] = aValue;
            }
        
            for (std::uint32_t aLoopIndex = 0U; aLoopIndex < S_BLOCK; aLoopIndex += 1U) {
                aWorkLaneBKeyA = aLoopIndex + 7475U;
                if (aWorkLaneBKeyA >= S_BLOCK) { aWorkLaneBKeyA -= S_BLOCK; }
                aWorkLaneBByteA = aWorkLaneB[aWorkLaneBKeyA] ^ 70U;
                aValue = (aValue ^ aWorkLaneBByteA) + aSaltA[aLoopIndex & 0x7FU];
                aValueNibbleA = aValue & 255U;
                aValueNibbleB = (aValue >> 8U) & 255U;
                aValueNibbleC = (aValue >> 16U) & 255U;
                aValueNibbleD = (aValue >> 24U) & 255U;
                aValueNibbleC = aSBoxD[(aValueNibbleC ^ aValueNibbleB) & 0xFFU];
                aValueNibbleD = aSBoxC[(aValueNibbleD + aValueNibbleA) & 0xFFU];
                aValueNibbleB = aSBoxB[(aValueNibbleB + aValueNibbleD) & 0xFFU];
                aValueNibbleA = aSBoxA[(aValueNibbleA + aValueNibbleC) & 0xFFU];
                aValue = aValueNibbleA |
        		static_cast<std::uint32_t>(aValueNibbleB) << 8U |
        		static_cast<std::uint32_t>(aValueNibbleC) << 16U |
        		static_cast<std::uint32_t>(aValueNibbleD) << 24U;
                aWorkLaneCKeyA = aLoopIndex + 149U;
                if (aWorkLaneCKeyA >= S_BLOCK) { aWorkLaneCKeyA -= S_BLOCK; }
                aValue = aValue + aWorkLaneC[aWorkLaneCKeyA];
                aPermuteByteA = aPermute - 5U;
                aWorkLaneCKeyA = aLoopIndex + 4563U;
                if (aWorkLaneCKeyA >= S_BLOCK) { aWorkLaneCKeyA -= S_BLOCK; }
                aSaltBKeyA = aWorkLaneC[aWorkLaneCKeyA] + 55U;
                aSBoxCKeyA = aLoopIndex + 131U;
                aPermute = (aPermuteByteA ^ aSaltB[aSaltBKeyA & 0x7FU]) + aSBoxC[aSBoxCKeyA & 0xFFU];
                aPermute = aSBoxA[aPermute & 0xFFU] | (static_cast<std::uint32_t>(aPermute) << 8U);
                aPermute = RotL32(aPermute, 2U);
                aPermute = aPermute + aValue;
                aValue = RotL32(aValue, aPermute);
                aWorkLaneD[aLoopIndex] = aValue;
            }
    }
}

void TwistExpander_FrodoShire::TwistBlock(TwistWorkSpace *pWorkspace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkspace, pSource, pDestination);
    if ((pWorkspace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aSource = pSource;
    std::uint8_t *aDestination = pDestination;
    [[maybe_unused]] std::uint8_t *aSaltA = pWorkspace->mSaltA;
    [[maybe_unused]] std::uint8_t *aSaltB = pWorkspace->mSaltB;
    [[maybe_unused]] std::uint8_t *aSaltC = pWorkspace->mSaltC;
    [[maybe_unused]] std::uint8_t *aSaltD = pWorkspace->mSaltD;
    [[maybe_unused]] std::uint8_t *aSBoxA = pWorkspace->mSBoxA;
    [[maybe_unused]] std::uint8_t *aSBoxB = pWorkspace->mSBoxB;
    [[maybe_unused]] std::uint8_t *aSBoxC = pWorkspace->mSBoxC;
    [[maybe_unused]] std::uint8_t *aSBoxD = pWorkspace->mSBoxD;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkspace->mExpandLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkspace->mExpandLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkspace->mExpandLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkspace->mExpandLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkspace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkspace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkspace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkspace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkspace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkspace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aMaskLaneA = pWorkspace->mMaskLaneA;
    [[maybe_unused]] std::uint8_t *aMaskLaneB = pWorkspace->mMaskLaneB;
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

    std::memcpy(pDestination, pWorkspace->mWorkLaneD, S_BLOCK);
}
