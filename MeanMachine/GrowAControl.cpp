#include "GrowAControl.hpp"

#include "GrowFoldControlCore.hpp"

namespace {

using GrowAFoldControl =
    GrowFoldControlCore::Control<
        GrowFoldControlCore::Family::kGrowA>;

}

void GrowAControl::Reset(const std::uint64_t pSeed) {
    GrowAFoldControl::Reset(pSeed);
}

std::string GrowAControl::Generate(
    const std::uint64_t pExplorationCases) {
    return GrowAFoldControl::Generate(pExplorationCases);
}

std::string GrowAControl::RenderCandidate(
    const std::size_t pCandidateIndex) {
    return GrowAFoldControl::RenderCandidate(pCandidateIndex);
}

void GrowAControl::Print() {
    GrowAFoldControl::Print();
}

bool GrowAControl::SaveValues(const std::string &pFolder,
                              std::string *pErrorMessage) {
    return GrowAFoldControl::SaveValues(pFolder, pErrorMessage);
}

bool GrowAControl::LoadValues(const std::string &pFolder,
                              std::string *pErrorMessage) {
    return GrowAFoldControl::LoadValues(pFolder, pErrorMessage);
}

bool GrowAControl::ValidateCandidate(
    const std::size_t pCandidateIndex,
    std::string *pErrorMessage) {
    return GrowAFoldControl::ValidateCandidate(
        pCandidateIndex,
        pErrorMessage
    );
}

std::size_t GrowAControl::GeneratedCount() {
    return GrowAFoldControl::GeneratedCount();
}
