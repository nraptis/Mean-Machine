#include "FoldSeedControl.hpp"

#include "FoldControlCore.hpp"

void FoldSeedControl::Reset(const std::uint64_t pSeed) {
    FoldControlCore::Reset(FoldControlCore::Flavor::kSeed, pSeed);
}

std::string FoldSeedControl::Generate(const std::uint64_t pExplorationCases) {
    return FoldControlCore::Generate(FoldControlCore::Flavor::kSeed,
                                     pExplorationCases);
}

std::string FoldSeedControl::RenderCandidate(
    const std::size_t pCandidateIndex,
    const std::string &pClassName) {
    return FoldControlCore::RenderCandidate(FoldControlCore::Flavor::kSeed,
                                            pCandidateIndex,
                                            pClassName);
}

void FoldSeedControl::Print() {
    FoldControlCore::Print(FoldControlCore::Flavor::kSeed);
}

bool FoldSeedControl::SaveValues(const std::string &pFolder,
                                 std::string *pErrorMessage) {
    return FoldControlCore::SaveValues(FoldControlCore::Flavor::kSeed,
                                       pFolder,
                                       pErrorMessage);
}

bool FoldSeedControl::LoadValues(const std::string &pFolder,
                                 std::string *pErrorMessage) {
    return FoldControlCore::LoadValues(FoldControlCore::Flavor::kSeed,
                                       pFolder,
                                       pErrorMessage);
}

bool FoldSeedControl::ValidateCandidate(const std::size_t pCandidateIndex,
                                        std::string *pErrorMessage) {
    return FoldControlCore::ValidateCandidate(FoldControlCore::Flavor::kSeed,
                                              pCandidateIndex,
                                              pErrorMessage);
}

std::size_t FoldSeedControl::GeneratedCount() {
    return FoldControlCore::GeneratedCount(FoldControlCore::Flavor::kSeed);
}
