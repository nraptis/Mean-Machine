#include "ControlValueFile.hpp"

#include "FileIO.hpp"

#include <algorithm>
#include <array>
#include <limits>

namespace {

constexpr std::array<std::uint8_t, 8> kMagic = {
    'M', 'M', 'C', 'V', 'B', 'I', 'N', '1',
};
constexpr std::uint32_t kVersion = 1U;
constexpr std::size_t kHeaderByteCount = 24U;

void SetText(std::string *pText,
             const std::string &pValue) {
    if (pText != nullptr) {
        *pText = pValue;
    }
}

void Append32(std::vector<std::uint8_t> *pBytes,
              const std::uint32_t pValue) {
    for (unsigned i = 0U; i < 4U; ++i) {
        pBytes->push_back(
            static_cast<std::uint8_t>((pValue >> (i * 8U)) & 0xFFU)
        );
    }
}

void Append64(std::vector<std::uint8_t> *pBytes,
              const std::uint64_t pValue) {
    for (unsigned i = 0U; i < 8U; ++i) {
        pBytes->push_back(
            static_cast<std::uint8_t>((pValue >> (i * 8U)) & 0xFFULL)
        );
    }
}

bool Read32(const std::vector<std::uint8_t> &pBytes,
            const std::size_t pOffset,
            std::uint32_t *pValue) {
    if ((pValue == nullptr) || ((pOffset + 4U) > pBytes.size())) {
        return false;
    }
    std::uint32_t aValue = 0U;
    for (unsigned i = 0U; i < 4U; ++i) {
        aValue |= static_cast<std::uint32_t>(pBytes[pOffset + i])
                  << (i * 8U);
    }
    *pValue = aValue;
    return true;
}

bool Read64(const std::vector<std::uint8_t> &pBytes,
            const std::size_t pOffset,
            std::uint64_t *pValue) {
    if ((pValue == nullptr) || ((pOffset + 8U) > pBytes.size())) {
        return false;
    }
    std::uint64_t aValue = 0ULL;
    for (unsigned i = 0U; i < 8U; ++i) {
        aValue |= static_cast<std::uint64_t>(pBytes[pOffset + i])
                  << (i * 8U);
    }
    *pValue = aValue;
    return true;
}

} // namespace

bool ControlValueFile::Save(
    const std::string &pPath,
    const Kind pKind,
    const std::vector<std::uint64_t> &pValues,
    std::string *pErrorMessage) {
    if (pValues.size() >
        static_cast<std::size_t>(std::numeric_limits<std::uint64_t>::max())) {
        SetText(pErrorMessage,
                "Control value count could not be represented.");
        return false;
    }

    std::vector<std::uint8_t> aBytes;
    aBytes.reserve(kHeaderByteCount + (pValues.size() * 8U));
    aBytes.insert(aBytes.end(), kMagic.begin(), kMagic.end());
    Append32(&aBytes, kVersion);
    Append32(&aBytes, static_cast<std::uint32_t>(pKind));
    Append64(&aBytes, static_cast<std::uint64_t>(pValues.size()));
    for (const std::uint64_t aValue : pValues) {
        Append64(&aBytes, aValue);
    }

    if (!FileIO::Save(pPath, aBytes)) {
        SetText(pErrorMessage,
                "Failed to save control value file " + pPath);
        return false;
    }
    SetText(pErrorMessage, "");
    return true;
}

bool ControlValueFile::Load(
    const std::string &pPath,
    const Kind pExpectedKind,
    const std::size_t pExpectedValueCount,
    std::vector<std::uint64_t> *pValues,
    std::string *pErrorMessage) {
    if (pValues == nullptr) {
        SetText(pErrorMessage,
                "Control value destination was null.");
        return false;
    }

    pValues->clear();
    SetText(pErrorMessage, "");

    std::vector<std::uint8_t> aBytes;
    if (!FileIO::Load(pPath, aBytes)) {
        SetText(pErrorMessage,
                "Required control value file could not be loaded: " +
                pPath);
        return false;
    }
    if ((aBytes.size() < kHeaderByteCount) ||
        !std::equal(kMagic.begin(), kMagic.end(), aBytes.begin())) {
        SetText(pErrorMessage,
                "Required control value file had an invalid header: " +
                pPath);
        return false;
    }

    std::uint32_t aVersion = 0U;
    std::uint32_t aKind = 0U;
    std::uint64_t aDeclaredValueCount = 0ULL;
    if (!Read32(aBytes, 8U, &aVersion) ||
        !Read32(aBytes, 12U, &aKind) ||
        !Read64(aBytes, 16U, &aDeclaredValueCount) ||
        (aVersion != kVersion) ||
        (aKind != static_cast<std::uint32_t>(pExpectedKind))) {
        SetText(pErrorMessage,
                "Required control value file had an incompatible header: " +
                pPath);
        return false;
    }

    const std::size_t aAvailableValueCount =
        (aBytes.size() - kHeaderByteCount) / 8U;
    const std::size_t aExpectedByteCount =
        kHeaderByteCount + (pExpectedValueCount * 8U);
    if ((aDeclaredValueCount != pExpectedValueCount) ||
        (aAvailableValueCount != pExpectedValueCount) ||
        (aBytes.size() != aExpectedByteCount)) {
        SetText(
            pErrorMessage,
            "Required control value file had the wrong exact value count: " +
            pPath
        );
        return false;
    }

    pValues->resize(pExpectedValueCount);
    for (std::size_t i = 0U; i < pExpectedValueCount; ++i) {
        if (!Read64(aBytes,
                    kHeaderByteCount + (i * 8U),
                    &(*pValues)[i])) {
            pValues->clear();
            SetText(pErrorMessage,
                    "Required control value file was truncated: " + pPath);
            return false;
        }
    }
    SetText(pErrorMessage, "");
    return true;
}
