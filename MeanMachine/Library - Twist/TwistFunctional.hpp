//
//  TwistWrap.hpp
//  Gorgon
//
//  Created by Codex on 4/15/26.
//

#ifndef TwistWrap_hpp
#define TwistWrap_hpp

#include "TwistWorkSpace.hpp"
#include <cstddef>
#include <cstdint>

inline std::uint8_t RotL8(std::uint8_t pValue, std::uint8_t pAmount) {
    std::uint8_t aAmount = static_cast<std::uint8_t>(pAmount & 7U);
    if (aAmount == 0U) { return pValue; }
    return static_cast<std::uint8_t>((pValue << aAmount) | (pValue >> (8U - aAmount)));
}

inline std::uint16_t RotL16(std::uint16_t pValue, std::uint16_t pAmount) {
    std::uint16_t aAmount = static_cast<std::uint16_t>(pAmount & 15U);
    if (aAmount == 0U) { return pValue; }
    return static_cast<std::uint16_t>((pValue << aAmount) | (pValue >> (16U - aAmount)));
}

inline std::uint32_t RotL32(std::uint32_t pValue, std::uint32_t pAmount) {
    std::uint32_t aAmount = pAmount & 31U;
    if (aAmount == 0U) { return pValue; }
    return static_cast<std::uint32_t>((pValue << aAmount) | (pValue >> (32U - aAmount)));
}

inline std::uint64_t RotL64(std::uint64_t pValue, std::uint64_t pAmount) {
    std::uint64_t aAmount = pAmount & 63ULL;
    if (aAmount == 0ULL) { return pValue; }
    return static_cast<std::uint64_t>((pValue << aAmount) | (pValue >> (64ULL - aAmount)));
}

inline std::uint64_t ShiftL64(std::uint64_t pValue, std::uint64_t pAmount) {
    const std::uint64_t aAmount = pAmount & 63ULL;
    return static_cast<std::uint64_t>(pValue << aAmount);
}

inline std::uint64_t ShiftR64(std::uint64_t pValue, std::uint64_t pAmount) {
    const std::uint64_t aAmount = pAmount & 63ULL;
    return static_cast<std::uint64_t>(pValue >> aAmount);
}

inline std::uint8_t RotR8(std::uint8_t pValue, std::uint8_t pAmount) {
    std::uint8_t aAmount = static_cast<std::uint8_t>(pAmount & 7U);
    if (aAmount == 0U) { return pValue; }
    return static_cast<std::uint8_t>((pValue >> aAmount) | (pValue << (8U - aAmount)));
}

inline std::uint16_t RotR16(std::uint16_t pValue, std::uint16_t pAmount) {
    std::uint16_t aAmount = static_cast<std::uint16_t>(pAmount & 15U);
    if (aAmount == 0U) { return pValue; }
    return static_cast<std::uint16_t>((pValue >> aAmount) | (pValue << (16U - aAmount)));
}

inline std::uint32_t RotR32(std::uint32_t pValue, std::uint32_t pAmount) {
    std::uint32_t aAmount = pAmount & 31U;
    if (aAmount == 0U) { return pValue; }
    return static_cast<std::uint32_t>((pValue >> aAmount) | (pValue << (32U - aAmount)));
}

inline std::uint64_t RotR64(std::uint64_t pValue, std::uint64_t pAmount) {
    std::uint64_t aAmount = pAmount & 63ULL;
    if (aAmount == 0ULL) { return pValue; }
    return static_cast<std::uint64_t>((pValue >> aAmount) | (pValue << (64ULL - aAmount)));
}

#endif /* TwistWrap_hpp */
