#include "TwistExpander_PractRandCandidate.hpp"

#include <algorithm>
#include <array>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

namespace {

constexpr std::uint64_t kDefaultSeed = 0x9E3779B97F4A7C15ULL;
constexpr std::uint64_t kDefaultBlocks = 32ULL;

struct Options {
    std::uint64_t byte_count = kDefaultBlocks * static_cast<std::uint64_t>(S_BLOCK);
    std::uint64_t seed = kDefaultSeed;
    std::string password_text = "a";
    bool output_bits = false;
    bool count_only = false;
    std::string output_path;
};

[[noreturn]] void Usage(const char *argv0) {
    std::cerr
        << "usage: " << argv0
        << " [--bytes COUNT] [--seed N | --password-text TEXT] [--bits] [--output PATH] [--count-only]\n"
        << "  defaults: --password-text a --bytes " << (kDefaultBlocks * static_cast<std::uint64_t>(S_BLOCK)) << "\n";
    std::exit(1);
}

bool ParseUnsigned(const char *pText,
                   std::uint64_t &pValue) {
    if ((pText == nullptr) || (pText[0] == '\0')) {
        return false;
    }

    errno = 0;
    char *aEnd = nullptr;
    const unsigned long long aParsed = std::strtoull(pText, &aEnd, 10);
    if ((errno != 0) || (aEnd == pText) || (*aEnd != '\0')) {
        return false;
    }

    pValue = static_cast<std::uint64_t>(aParsed);
    return true;
}

Options ParseArgs(int argc,
                  char **argv) {
    Options aOptions;

    for (int i = 1; i < argc; ++i) {
        const std::string aArg(argv[i]);
        auto NeedValue = [&](const char *pFlag) -> const char * {
            if ((i + 1) >= argc) {
                std::cerr << "missing value for " << pFlag << "\n";
                Usage(argv[0]);
            }
            return argv[++i];
        };

        if (aArg == "--bytes") {
            if (!ParseUnsigned(NeedValue("--bytes"), aOptions.byte_count)) {
                Usage(argv[0]);
            }
        } else if (aArg == "--seed") {
            if (!ParseUnsigned(NeedValue("--seed"), aOptions.seed)) {
                Usage(argv[0]);
            }
            aOptions.password_text.clear();
        } else if (aArg == "--password-text") {
            aOptions.password_text = NeedValue("--password-text");
        } else if (aArg == "--bits") {
            aOptions.output_bits = true;
        } else if (aArg == "--output") {
            aOptions.output_path = NeedValue("--output");
        } else if (aArg == "--count-only") {
            aOptions.count_only = true;
        } else {
            Usage(argv[0]);
        }
    }

    return aOptions;
}

void FillInitialSource(std::uint64_t pSeed,
                       std::uint8_t *pSource) {
    std::uint64_t aState = pSeed;
    for (std::size_t i = 0; i < static_cast<std::size_t>(S_BLOCK); ++i) {
        aState ^= (aState >> 12U);
        aState ^= (aState << 25U);
        aState ^= (aState >> 27U);
        aState *= 2685821657736338717ULL;
        pSource[i] = static_cast<std::uint8_t>(aState & 0xFFU);
    }
}

void FillPasswordSource(const std::string &pPassword,
                        std::uint8_t *pSource) {
    std::memset(pSource, 0, static_cast<std::size_t>(S_BLOCK));

    if (pPassword.empty()) {
        return;
    }

    std::size_t aInitialCopy = std::min<std::size_t>(pPassword.size(), static_cast<std::size_t>(S_BLOCK));
    std::memcpy(pSource, pPassword.data(), aInitialCopy);

    if (aInitialCopy < static_cast<std::size_t>(S_BLOCK)) {
        pSource[aInitialCopy++] = 0U;
    }
    if (aInitialCopy < static_cast<std::size_t>(S_BLOCK)) {
        pSource[aInitialCopy++] = 0U;
    }

    std::size_t aFilled = aInitialCopy;
    while (aFilled < static_cast<std::size_t>(S_BLOCK)) {
        std::size_t aChunk = aFilled;
        if ((aFilled + aChunk) > static_cast<std::size_t>(S_BLOCK)) {
            aChunk = static_cast<std::size_t>(S_BLOCK) - aFilled;
        }
        std::memcpy(pSource + aFilled, pSource, aChunk);
        aFilled += aChunk;
    }
}

void WriteBinary(std::ostream &pOutput,
                 const std::uint8_t *pBytes,
                 std::size_t pCount) {
    pOutput.write(reinterpret_cast<const char *>(pBytes), static_cast<std::streamsize>(pCount));
}

void WriteBits(std::ostream &pOutput,
               const std::uint8_t *pBytes,
               std::size_t pCount) {
    for (std::size_t i = 0; i < pCount; ++i) {
        const std::uint8_t aValue = pBytes[i];
        for (int aBit = 7; aBit >= 0; --aBit) {
            pOutput.put(((aValue >> aBit) & 1U) ? '1' : '0');
        }
    }
}

} // namespace

int main(int argc,
         char **argv) {
    const Options aOptions = ParseArgs(argc, argv);

    if (aOptions.count_only) {
        std::cout << 1 << '\n';
        return 0;
    }

    std::ostream *aOutput = &std::cout;
    std::unique_ptr<std::ofstream> aFileOutput;
    if (!aOptions.output_path.empty()) {
        aFileOutput = std::make_unique<std::ofstream>(
            aOptions.output_path,
            aOptions.output_bits ? std::ios::out : (std::ios::out | std::ios::binary));
        if (!aFileOutput->is_open()) {
            std::cerr << "failed to open output: " << aOptions.output_path << "\n";
            return 1;
        }
        aOutput = aFileOutput.get();
    } else if (!aOptions.output_bits) {
        std::ios::sync_with_stdio(false);
    }

    std::array<std::uint8_t, S_BLOCK> aState{};
    std::array<std::uint8_t, S_BLOCK> aBlock{};

    if (!aOptions.password_text.empty()) {
        FillPasswordSource(aOptions.password_text, aState.data());
    } else {
        FillInitialSource(aOptions.seed, aState.data());
    }

    TwistWorkSpace aWorkspace;
    TwistExpander_PractRandCandidate aExpander;

    const bool aStreamForever = (aOptions.byte_count == 0U);
    std::uint64_t aRemaining = aOptions.byte_count;

    while (aStreamForever || (aRemaining > 0U)) {
        aExpander.Seed(&aWorkspace, aState.data(), aState.data(), static_cast<unsigned int>(S_BLOCK));
        aExpander.TwistBlock(&aWorkspace, aState.data(), aBlock.data());

        const std::size_t aChunkBytes = static_cast<std::size_t>(
            aStreamForever
                ? static_cast<std::uint64_t>(S_BLOCK)
                : std::min<std::uint64_t>(aRemaining, static_cast<std::uint64_t>(S_BLOCK)));

        if (aOptions.output_bits) {
            WriteBits(*aOutput, aBlock.data(), aChunkBytes);
        } else {
            WriteBinary(*aOutput, aBlock.data(), aChunkBytes);
        }

        aState = aBlock;
        if (!aStreamForever) {
            aRemaining -= static_cast<std::uint64_t>(aChunkBytes);
        }
    }

    aOutput->flush();
    return aOutput->good() ? 0 : 1;
}
