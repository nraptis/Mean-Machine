//
//  GMagicNumbers.hpp
//  MeanMachine
//
//  Created by Dragon on 5/2/26.
//

#ifndef GMagicNumbers_hpp
#define GMagicNumbers_hpp

#include <array>
#include <cstdint>
#include "Random.hpp"

#define G_HOT_PACK_COUNT 4
#define G_HOT_PACK_SIZE 8

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
public:
    
    

    inline static constexpr std::array<GHotPack, G_HOT_PACK_COUNT> sPack = {{
            GHotPack{{
                GHotPair{ 0x416C6525853ABB39ULL, 0x6154AB6B5134D9ADULL },
                GHotPair{ 0xB085B7D8F6565307ULL, 0x3D9CAC71BEA1E5DDULL },
                GHotPair{ 0xDE9E2F34795E3972ULL, 0x0F2A7FC9A4929977ULL },
                GHotPair{ 0xF992A86ADF59773DULL, 0xDA3884A5ACE6FD5BULL },
                GHotPair{ 0x8912EA87F5E58B03ULL, 0xCF9061CCB033F5F9ULL },
                GHotPair{ 0x92784669BAB8DB31ULL, 0x3BB18BC584A5ABFBULL },
                GHotPair{ 0x1F0B4441117D2B9AULL, 0x76A10C0EF31A46C1ULL },
                GHotPair{ 0x8EF338CD26FB865EULL, 0x04A4F2EC485370BDULL }
            }}, // pack 0, total=4.9852, full=3.5422, byte=1.4430
            GHotPack{{
                GHotPair{ 0x3F9499F829D73FA5ULL, 0x1446136F55D56DCBULL },
                GHotPair{ 0x626E883735BB370EULL, 0xE84961871FA2DBF7ULL },
                GHotPair{ 0x43F2576EC1154A8EULL, 0x73C47333681C2993ULL },
                GHotPair{ 0x4B05B039B3D90836ULL, 0x825A563216BE21EBULL },
                GHotPair{ 0x62182226FAABF182ULL, 0x67AEE3543072389FULL },
                GHotPair{ 0xFD8FC4899E73697DULL, 0x2F5AFDCEE9280F1DULL },
                GHotPair{ 0x6BA267BBF2DECF53ULL, 0xE411541D4E2B766DULL },
                GHotPair{ 0x9E41A73974DC83D7ULL, 0xD8CC1C45A5BF228FULL }
            }}, // pack 1, total=4.7914, full=3.4875, byte=1.3039
            GHotPack{{
                GHotPair{ 0xA93262C7816A2497ULL, 0x91ADE977D1AF1E55ULL },
                GHotPair{ 0x01D37952B1BC13E7ULL, 0x50A364AC662732C3ULL },
                GHotPair{ 0xD8705F3FF408D712ULL, 0x4187133554CABA63ULL },
                GHotPair{ 0x2A63C3F137FE067DULL, 0x0D145CB6C055718DULL },
                GHotPair{ 0xD2A350FA915B92DFULL, 0xF9F87CC5F10B6EF1ULL },
                GHotPair{ 0xDEBA085FA39638EAULL, 0xBE29A48A51A0AF81ULL },
                GHotPair{ 0xB8305CCD271F3178ULL, 0x9525A1A13B771E31ULL },
                GHotPair{ 0xDC1E5D767CB1B4CBULL, 0x384F4CC2C620610DULL }
            }}, // pack 2, total=5.3078, full=3.7477, byte=1.5602
            GHotPack{{
                GHotPair{ 0x64CF1C572935BA29ULL, 0x6B25E551F8943C11ULL },
                GHotPair{ 0x28F151820D6A2624ULL, 0x62681C94E3C76EADULL },
                GHotPair{ 0xB9EEC66F9F09EEDAULL, 0x4AD4BC75329C99A7ULL },
                GHotPair{ 0x61159A9C2861B4FDULL, 0xDA30971B0E12753DULL },
                GHotPair{ 0x2EA1F89BC997E0DEULL, 0xCF4EF6849AA24361ULL },
                GHotPair{ 0x6FC90B7CBDC7ADB5ULL, 0xF6A605805C2FA2D5ULL },
                GHotPair{ 0x87E92D34241FF854ULL, 0xACFCA6BF71F6E55BULL },
                GHotPair{ 0x499CBD95D33D8221ULL, 0x3BE9E898F940A225ULL }
            }} // pack 3, total=4.9852, full=3.5109, byte=1.4742
        }};

    static constexpr GHotPack Get(std::uint16_t pIndex) {
        return sPack[pIndex & 0x007FU];
    }

};

class GMagicNumbers {
public:

    static std::vector<GHotPack> GetHotPacks(int pCount) {
        
        
        std::vector<GHotPack> aPool;
        for (int i=0;i<GHotPacks::sPack.size();i++) {
            aPool.push_back(GHotPacks::sPack[i]);
        }
        
        Random::Shuffle(&aPool);
        std::vector<GHotPack> aResult;
        for (int i=0; i<pCount; i++) {
            if (i < aPool.size()) {
                aResult.push_back(aPool[i]);
            }
        }
        return aResult;
    }
    
};


#endif /* GMagicNumbers_hpp */
