#include "FoldTwistControl.hpp"

#include "FoldControlCore.hpp"

void FoldTwistControl::Reset(const std::uint64_t pSeed) {
    FoldControlCore::Reset(FoldControlCore::Flavor::kTwist, pSeed);
}

std::string FoldTwistControl::Generate(const std::uint64_t pExplorationCases) {
    return FoldControlCore::Generate(FoldControlCore::Flavor::kTwist,
                                     pExplorationCases);
}

std::string FoldTwistControl::RenderCandidate(
    const std::size_t pCandidateIndex,
    const std::string &pClassName) {
    return FoldControlCore::RenderCandidate(FoldControlCore::Flavor::kTwist,
                                            pCandidateIndex,
                                            pClassName);
}

void FoldTwistControl::Print() {
    FoldControlCore::Print(FoldControlCore::Flavor::kTwist);
}

bool FoldTwistControl::SaveValues(const std::string &pFolder,
                                  std::string *pErrorMessage) {
    return FoldControlCore::SaveValues(FoldControlCore::Flavor::kTwist,
                                       pFolder,
                                       pErrorMessage);
}

bool FoldTwistControl::LoadValues(const std::string &pFolder,
                                  std::string *pErrorMessage) {
    return FoldControlCore::LoadValues(FoldControlCore::Flavor::kTwist,
                                       pFolder,
                                       pErrorMessage);
}

bool FoldTwistControl::ValidateCandidate(const std::size_t pCandidateIndex,
                                         std::string *pErrorMessage) {
    return FoldControlCore::ValidateCandidate(FoldControlCore::Flavor::kTwist,
                                              pCandidateIndex,
                                              pErrorMessage);
}

std::size_t FoldTwistControl::GeneratedCount() {
    return FoldControlCore::GeneratedCount(FoldControlCore::Flavor::kTwist);
}
