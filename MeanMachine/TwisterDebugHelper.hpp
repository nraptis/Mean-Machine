//
//  TwisterDebugHelper.hpp
//  MeanMachine
//

#ifndef TwisterDebugHelper_hpp
#define TwisterDebugHelper_hpp

#include "TwistWorkSpace.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>

class TwisterDebugHelper {
public:
    static void PrintKeyBoxes(const char *pLabel,
                              TwistWorkSpace *pWorkSpace) {
        if ((pLabel == nullptr) || (pWorkSpace == nullptr)) { return; }

        std::printf("%s:\n", pLabel);
        PrintKeyBox("key_a", &(pWorkSpace->mKeyBoxA[0][0]));
        PrintKeyBox("key_b", &(pWorkSpace->mKeyBoxB[0][0]));
        std::printf("------------\n");
    }

    static void PrintTwistBlockKeyBoxes(std::size_t pBlockIndex,
                                        TwistWorkSpace *pWorkSpace) {
        char aLabel[64];
        std::snprintf(aLabel, sizeof(aLabel), "TwistBlock (%zu)", pBlockIndex);
        PrintKeyBoxes(aLabel, pWorkSpace);
    }

    static void PrintKeyRows(const char *pLabel,
                             TwistWorkSpace *pWorkSpace) {
        if ((pLabel == nullptr) || (pWorkSpace == nullptr)) { return; }

        std::printf("%s:\n", pLabel);
        PrintKeyRow("key_a", H_KEY - 1, &(pWorkSpace->mKeyBoxA[H_KEY - 1][0]));
        PrintKeyRow("key_b", H_KEY - 1, &(pWorkSpace->mKeyBoxB[H_KEY - 1][0]));
        std::printf("------------\n");
    }

    static void PrintTwistAKeyRows(std::size_t pBlockIndex,
                                   TwistWorkSpace *pWorkSpace) {
        char aLabel[64];
        std::snprintf(aLabel, sizeof(aLabel), "Twist_A key rows (%zu)", pBlockIndex);
        PrintKeyRows(aLabel, pWorkSpace);
    }

private:
    static void PrintKeyBox(const char *pName,
                            std::uint8_t *pKeyBox) {
        for (int aRow = 0; aRow < H_KEY; aRow += 1) {
            std::uint8_t *aRowBytes = pKeyBox + (static_cast<std::size_t>(aRow) * static_cast<std::size_t>(W_KEY));
            PrintKeyRow(pName, aRow, aRowBytes);
        }
    }

    static void PrintKeyRow(const char *pName,
                            int pRow,
                            std::uint8_t *pRowBytes) {
        std::printf("[%s row_%d: ", pName, pRow);
        for (int aIndex = 0; aIndex < 64; aIndex += 1) {
            std::printf("%02X", static_cast<unsigned int>(pRowBytes[aIndex]));
        }
        std::printf("]\n");
    }
};

#endif /* TwisterDebugHelper_hpp */
