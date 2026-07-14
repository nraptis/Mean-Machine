//
//  MaginNumberLoader.hpp
//  Soccer
//
//  Created by Codex on 7/9/26.
//

#ifndef MaginNumberLoader_hpp
#define MaginNumberLoader_hpp

#include <string>
#include <vector>

struct GHotPack;

class MaginNumberLoader {
public:
    static bool Load(const std::string &pOutputFolder,
                     std::vector<GHotPack> &pHotPacks,
                     std::string *pErrorMessage = nullptr);
};

#endif /* MaginNumberLoader_hpp */
