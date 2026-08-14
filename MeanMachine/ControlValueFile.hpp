#ifndef ControlValueFile_hpp
#define ControlValueFile_hpp

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace ControlValueFile {

enum class Kind : std::uint32_t {
    kGrowA = 1U,
    kGrowB = 2U,
    kLaneSplit = 3U,
    kKeyFork = 4U,
    kKeyLane = 5U,
    kResidualKDF = 6U,
};

// Values are serialized as explicit little-endian uint64 fields. This keeps
// the on-disk format independent of compiler padding and native struct layout.
bool Save(const std::string &pPath,
          Kind pKind,
          const std::vector<std::uint64_t> &pValues,
          std::string *pErrorMessage = nullptr);

// Control assets are executable-generation inputs, so loading is exact:
// missing files, incompatible headers, truncated values, and trailing values
// are all errors. No zero-substitution path is provided.
bool Load(const std::string &pPath,
          Kind pExpectedKind,
          std::size_t pExpectedValueCount,
          std::vector<std::uint64_t> *pValues,
          std::string *pErrorMessage = nullptr);

} // namespace ControlValueFile

#endif /* ControlValueFile_hpp */
