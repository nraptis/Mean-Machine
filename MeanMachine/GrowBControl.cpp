#include "GrowBControl.hpp"

#include "GrowFoldControlCore.hpp"

namespace {

using GrowBFoldControl =
    GrowFoldControlCore::Control<
        GrowFoldControlCore::Family::kGrowB>;

}

void GrowBControl::Reset(const std::uint64_t pSeed) {
    GrowBFoldControl::Reset(pSeed);
}

std::string GrowBControl::Generate(
    const std::uint64_t pExplorationCases) {
    return GrowBFoldControl::Generate(pExplorationCases);
}

std::string GrowBControl::RenderCandidate(
    const std::size_t pCandidateIndex) {
    return GrowBFoldControl::RenderCandidate(pCandidateIndex);
}

void GrowBControl::Print() {
    GrowBFoldControl::Print();
}

bool GrowBControl::SaveValues(const std::string &pFolder,
                              std::string *pErrorMessage) {
    return GrowBFoldControl::SaveValues(pFolder, pErrorMessage);
}

bool GrowBControl::LoadValues(const std::string &pFolder,
                              std::string *pErrorMessage) {
    return GrowBFoldControl::LoadValues(pFolder, pErrorMessage);
}

bool GrowBControl::ValidateCandidate(
    const std::size_t pCandidateIndex,
    std::string *pErrorMessage) {
    return GrowBFoldControl::ValidateCandidate(
        pCandidateIndex,
        pErrorMessage
    );
}

std::size_t GrowBControl::GeneratedCount() {
    return GrowBFoldControl::GeneratedCount();
}
