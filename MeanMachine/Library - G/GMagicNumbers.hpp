//
//  GMagicNumbers.hpp
//  MeanMachine
//
//  Created by Xenegos of the Revel on 5/2/26.
//

#ifndef GMagicNumbers_hpp
#define GMagicNumbers_hpp

#include <array>
#include <cstdio>
#include <cstdint>
#include <set>
#include <string>
#include <vector>
#include "Random.hpp"
#include "../MaginNumberLoader.hpp"

#define G_HOT_PACK_SIZE 36

struct GHotPair {
public:
    std::uint64_t mAdd;
    std::uint64_t mMul;
};

struct GHotPack {
public:
    std::array<GHotPair, G_HOT_PACK_SIZE> mPair;
};

class GHotPacks {
private:
    static const std::vector<GHotPack> &Packs() {
        static const std::vector<GHotPack> sPacks = [] {
            std::vector<GHotPack> aPacks;
            std::string aErrorMessage;
            if (!MaginNumberLoader::Load("Assets/hot_packs", aPacks, &aErrorMessage)) {
                std::printf("%s\n", aErrorMessage.c_str());
            }
            return aPacks;
        }();
        return sPacks;
    }

public:
    class PackCollection {
    public:
        std::size_t size() const {
            return GHotPacks::Packs().size();
        }

        bool empty() const {
            return GHotPacks::Packs().empty();
        }

        const GHotPack &operator[](std::size_t pIndex) const {
            return GHotPacks::Packs()[pIndex];
        }
    };

    inline static constexpr PackCollection sPack{};
    
    static GHotPack Get(std::uint16_t pIndex) {
        if (sPack.empty()) {
            return {};
        }
        return sPack[static_cast<std::size_t>(pIndex) % sPack.size()];
    }
    
};

class GMagicNumbers {
public:
    
    static std::vector<GHotPack> GetHotPacks(int pCount) {
        static std::set<int> sFetchedIndices;

        std::vector<GHotPack> aResult;
        if (pCount <= 0) {
            return aResult;
        }

        std::set<int> aFetchedThisCall;
        while ((aResult.size() < static_cast<std::size_t>(pCount)) &&
               (aFetchedThisCall.size() < GHotPacks::sPack.size())) {
            std::vector<int> aAvailableIndices;
            for (int i = 0; i < static_cast<int>(GHotPacks::sPack.size()); i++) {
                if ((sFetchedIndices.find(i) == sFetchedIndices.end()) &&
                    (aFetchedThisCall.find(i) == aFetchedThisCall.end())) {
                    aAvailableIndices.push_back(i);
                }
            }

            if (aAvailableIndices.empty()) {
                sFetchedIndices.clear();
                for (const int aIndex : aFetchedThisCall) {
                    sFetchedIndices.insert(aIndex);
                }
                continue;
            }

            Random::Shuffle(&aAvailableIndices);
            for (const int aIndex : aAvailableIndices) {
                if (aResult.size() >= static_cast<std::size_t>(pCount)) {
                    break;
                }
                aResult.push_back(GHotPacks::sPack[static_cast<std::size_t>(aIndex)]);
                sFetchedIndices.insert(aIndex);
                aFetchedThisCall.insert(aIndex);
            }
        }
        
        // printf("now fetched total of %d magic nums\n", (int)sFetchedIndices.size());
        
        return aResult;
    }
    
};

#endif /* GMagicNumbers_hpp */
