#ifndef GMoxPresets_hpp
#define GMoxPresets_hpp

#include <vector>

#include "GMoxModel.hpp"

class GMoxPresets {
public:
    static GMoxModel FourCompact();
    static GMoxModel SixBalanced();
    static GMoxModel SevenAsymmetric();
    static GMoxModel NineWideCross();
    static GMoxModel ElevenHeavyHidden();

    static std::vector<GMoxModel> CandidateModels();
    static std::vector<GMoxModel> RecommendedFourFlavors();
};

#endif /* GMoxPresets_hpp */
