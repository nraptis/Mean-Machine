#include "GMoxType.hpp"

#include <sstream>

GMoxType GMoxType::Stream(GMoxStreamKind kind) {
    GMoxType result;
    result.role = GMoxRole::kStream;
    result.subkind = static_cast<std::uint8_t>(kind);
    return result;
}

GMoxType GMoxType::Secret(GMoxSecretKind kind) {
    GMoxType result;
    result.role = GMoxRole::kSecret;
    result.subkind = static_cast<std::uint8_t>(kind);
    return result;
}

GMoxType GMoxType::Carry() {
    GMoxType result;
    result.role = GMoxRole::kCarry;
    return result;
}

GMoxType GMoxType::Orbiter(std::uint8_t index) {
    GMoxType result;
    result.role = GMoxRole::kOrbiter;
    result.index = index;
    return result;
}

GMoxType GMoxType::Wanderer(std::uint8_t index) {
    GMoxType result;
    result.role = GMoxRole::kWanderer;
    result.index = index;
    return result;
}

bool GMoxType::IsValid() const {
    return role != GMoxRole::kInvalid;
}

bool GMoxType::IsOrbiter() const {
    return role == GMoxRole::kOrbiter;
}

bool GMoxType::IsWanderer() const {
    return role == GMoxRole::kWanderer;
}

bool GMoxType::IsHiddenState() const {
    return role == GMoxRole::kSecret ||
           role == GMoxRole::kCarry ||
           role == GMoxRole::kWanderer ||
           role == GMoxRole::kOrbiter;
}

bool GMoxType::IsVisiblePlugInput() const {
    if (role != GMoxRole::kStream) {
        return false;
    }

    return subkind == static_cast<std::uint8_t>(GMoxStreamKind::kCurrent) ||
           subkind == static_cast<std::uint8_t>(GMoxStreamKind::kPrevious) ||
           subkind == static_cast<std::uint8_t>(GMoxStreamKind::kScatter) ||
           subkind == static_cast<std::uint8_t>(GMoxStreamKind::kCross);
}

std::string GMoxType::Name() const {
    switch (role) {
        case GMoxRole::kStream:
            switch (static_cast<GMoxStreamKind>(subkind)) {
                case GMoxStreamKind::kCurrent: return "stream_current";
                case GMoxStreamKind::kPrevious: return "stream_previous";
                case GMoxStreamKind::kScatter: return "stream_scatter";
                case GMoxStreamKind::kCross: return "stream_cross";
                default: return "stream_invalid";
            }

        case GMoxRole::kSecret:
            switch (static_cast<GMoxSecretKind>(subkind)) {
                case GMoxSecretKind::kCurrent: return "secret_current";
                case GMoxSecretKind::kPrevious: return "secret_previous";
                case GMoxSecretKind::kScatter: return "secret_scatter";
                default: return "secret_invalid";
            }

        case GMoxRole::kCarry:
            return "carry";

        case GMoxRole::kOrbiter:
            return "orbiter_" + std::to_string(static_cast<int>(index));

        case GMoxRole::kWanderer:
            return "wanderer_" + std::to_string(static_cast<int>(index));

        case GMoxRole::kPlug:
            return "plug_" + std::to_string(static_cast<int>(index));

        case GMoxRole::kLoopSalt:
            return "loop_salt_" + std::to_string(static_cast<int>(index));

        case GMoxRole::kHotAdd:
            return "hot_add_" + std::to_string(static_cast<int>(index));

        case GMoxRole::kHotMul:
            return "hot_mul_" + std::to_string(static_cast<int>(index));

        default:
            return "invalid";
    }
}
