#include "GoldenDemo.hpp"

#include "FileIO.hpp"
#include "TwistExpander.hpp"
#include "TwistFunctional.hpp"
#include "TwistMemory.hpp"
#include "TwistMix64.hpp"
#include "TwistSnow.hpp"

#include <algorithm>
#include <cstring>
#include <filesystem>

namespace {

struct LoopState {
    std::uint64_t mValuePrevious = 0;
    std::uint64_t mInput = 0;
    std::uint64_t mSecureA = 0;
    std::uint64_t mSecureB = 0;
    std::uint64_t mCross = 0;
    std::uint64_t mScatter = 0;
    std::uint64_t mOrbitA = 0;
    std::uint64_t mOrbitB = 0;
    std::uint64_t mOrbitC = 0;
    std::uint64_t mOrbitD = 0;
    std::uint64_t mWandererA = 0;
    std::uint64_t mWandererB = 0;
    std::uint64_t mWandererC = 0;
    std::uint64_t mCarry = 0;
    std::uint64_t mPrism = 0;
};

bool HasBinExtension(const std::string &pPath) {
    std::filesystem::path aPath(pPath);
    std::string aExt = aPath.extension().string();
    std::transform(aExt.begin(), aExt.end(), aExt.begin(),
                   [](unsigned char pChar) {
                       return static_cast<char>(std::tolower(pChar));
                   });
    return aExt == ".bin";
}

} // namespace

GoldenDemo::GoldenDemo() {
    mData = nullptr;
    mSecureA = nullptr;
    mSecureB = nullptr;
    mBufferLength = 0;
}

GoldenDemo::~GoldenDemo() {
    FreeBuffers();
}

bool GoldenDemo::AllocateBuffers(int pLength) {
    if (pLength <= 0) {
        return false;
    }

    if ((mBufferLength == pLength) &&
        (mData != nullptr) &&
        (mSecureA != nullptr) &&
        (mSecureB != nullptr)) {
        std::memset(mData, 0, static_cast<std::size_t>(mBufferLength));
        std::memset(mSecureA, 0, static_cast<std::size_t>(mBufferLength));
        std::memset(mSecureB, 0, static_cast<std::size_t>(mBufferLength));
        return true;
    }

    FreeBuffers();

    mBufferLength = pLength;
    mData = new std::uint8_t[static_cast<std::size_t>(mBufferLength)];
    mSecureA = new std::uint8_t[static_cast<std::size_t>(mBufferLength)];
    mSecureB = new std::uint8_t[static_cast<std::size_t>(mBufferLength)];

    if ((mData == nullptr) || (mSecureA == nullptr) || (mSecureB == nullptr)) {
        FreeBuffers();
        return false;
    }

    std::memset(mData, 0, static_cast<std::size_t>(mBufferLength));
    std::memset(mSecureA, 0, static_cast<std::size_t>(mBufferLength));
    std::memset(mSecureB, 0, static_cast<std::size_t>(mBufferLength));
    return true;
}

void GoldenDemo::FreeBuffers() {
    delete [] mData;
    delete [] mSecureA;
    delete [] mSecureB;

    mData = nullptr;
    mSecureA = nullptr;
    mSecureB = nullptr;
    mBufferLength = 0;
}

bool GoldenDemo::RunBlock(const std::uint8_t *pInputBlock,
                          std::uint8_t *pOutputBlock,
                          std::uint8_t *pSecureBlockA,
                          std::uint8_t *pSecureBlockB,
                          LoopMode pLoopMode) const {
    if ((pInputBlock == nullptr) ||
        (pOutputBlock == nullptr) ||
        (pSecureBlockA == nullptr) ||
        (pSecureBlockB == nullptr)) {
        return false;
    }

    std::uint8_t aCounterSource[S_BLOCK];
    std::memcpy(aCounterSource, pInputBlock, static_cast<std::size_t>(S_BLOCK));

    // Flood secure lanes with ARIA/AES counter streams.
    TwistSnow::Aria256Counter(aCounterSource, pSecureBlockA);
    TwistSnow::AES256Counter(aCounterSource, pSecureBlockB);
    TwistSnow::AES256Counter(pSecureBlockA, pSecureBlockB);
    TwistSnow::Aria256Counter(pSecureBlockB, pSecureBlockA);

    // Derive demo salts directly from the secure lanes.
    std::uint8_t aSaltA[S_SALT];
    std::uint8_t aSaltB[S_SALT];
    std::uint8_t aSaltC[S_SALT];
    std::uint8_t aSaltD[S_SALT];

    for (std::uint32_t aIndex = 0U; aIndex < S_SALT; ++aIndex) {
        aSaltA[aIndex] = pSecureBlockA[aIndex +   0U];
        aSaltB[aIndex] = pSecureBlockB[aIndex +   0U];
        aSaltC[aIndex] = pSecureBlockA[aIndex + 128U];
        aSaltD[aIndex] = pSecureBlockB[aIndex + 128U];
    }

    const std::uint8_t *aSBoxA = pSecureBlockA + 256U;
    const std::uint8_t *aSBoxB = pSecureBlockB + 256U;
    const std::uint8_t *aSBoxC = pSecureBlockA + 512U;
    const std::uint8_t *aSBoxD = pSecureBlockB + 512U;

    std::uint64_t aScratchSaltA[S_SALT];
    std::uint64_t aScratchSaltB[S_SALT];
    std::uint64_t aScratchSaltC[S_SALT];
    std::uint64_t aScratchSaltD[S_SALT];

    std::uint8_t aWorkLaneA[S_BLOCK];
    std::uint8_t aWorkLaneB[S_BLOCK];
    std::uint8_t aWorkLaneC[S_BLOCK];
    std::uint8_t aWorkLaneD[S_BLOCK];

    LoopState aState;

    // Loop A
    TwistMemory::Grow(aScratchSaltD, aSaltD, 128U);
    TwistMemory::Grow(aScratchSaltA, aSaltC, 128U);
    TwistMemory::Grow(aScratchSaltC, aSaltA, 128U);
    TwistMemory::Grow(aScratchSaltB, aSaltB, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aState.mValuePrevious = aState.mInput;
        aState.mSecureA = pSecureBlockB[aIndex];
        aState.mSecureB = pSecureBlockA[aIndex];
        aState.mCross = pSecureBlockB[S_BLOCK1 - aIndex];
        aState.mInput = aState.mSecureA;

        aState.mScatter = TwistMix64::DiffuseA(ShiftL64(aState.mSecureA, 32U) ^
                                               aState.mSecureB ^
                                               RotL64(aState.mValuePrevious, 11U));

        aState.mOrbitA = aState.mWandererA + RotL64(aState.mInput, 29U) +
                         1863055947018026782ULL +
                         aScratchSaltD[((aState.mCross + RotL64(aState.mValuePrevious, 19U)) & 0x7FU)];
        aState.mOrbitB = aState.mWandererB ^ RotL64(aState.mValuePrevious, 37U) ^
                         1729963678461545545ULL ^
                         aScratchSaltC[((RotL64(aState.mOrbitA, 27U) + aState.mScatter) & 0x7FU)];
        aState.mOrbitC = aState.mWandererC + RotL64(aState.mCross, 51U) +
                         aSaltC[((127U - aIndex + 100U) & 0x7FU)] +
                         aScratchSaltA[((aIndex + 42U) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mCarry, 43U) ^ RotL64(aState.mInput, 21U) ^
                         aSaltD[((127U - aIndex + 100U) & 0x7FU)] ^
                         aScratchSaltB[((aIndex + 52U) & 0x7FU)];
        aState.mPrism = aState.mInput;

        aState.mOrbitA = aState.mOrbitA + aState.mOrbitB + 16145280331526471558ULL +
                         aScratchSaltD[((aState.mCarry ^ RotL64(aState.mOrbitC, 13U)) & 0x7FU)];
        aState.mOrbitD = aState.mOrbitD ^ aState.mOrbitA ^ 9543457973864807442ULL ^
                         aScratchSaltA[((RotL64(aState.mOrbitB, 11U) ^ aState.mWandererC) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mOrbitD * 17046011257803120553ULL, 53U);
        aState.mPrism = (aState.mPrism ^ aState.mOrbitC ^ RotL64(aState.mCarry, 29U) ^
                         5205223130063799541ULL) * 316374805787132145ULL;

        aState.mOrbitC = aState.mOrbitC + aState.mOrbitD + 11836353804089605978ULL +
                         aScratchSaltC[((RotL64(aState.mWandererA, 19U) ^ aState.mSecureB) & 0x7FU)];
        aState.mOrbitB = aState.mOrbitB ^ aState.mOrbitC ^ 15172304219631271622ULL ^
                         aScratchSaltD[((aState.mValuePrevious + RotL64(aState.mSecureA, 27U)) & 0x7FU)];
        aState.mOrbitB = RotL64(aState.mOrbitB, 45U);
        aState.mPrism = (aState.mPrism + RotL64(aState.mOrbitA, 35U) +
                         13413723197385533499ULL) * 830393899849853643ULL;

        aState.mOrbitA = aState.mOrbitA + aState.mOrbitB + 1863055947018026782ULL +
                         aScratchSaltB[((aState.mOrbitD + RotL64(aState.mOrbitA, 21U)) & 0x7FU)];
        aState.mOrbitD = aState.mOrbitD ^ aState.mOrbitA ^ 1729963678461545545ULL ^
                         aScratchSaltA[((aState.mCarry + RotL64(aState.mCross, 13U)) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mOrbitD * 13653242509885625043ULL, 51U);
        aState.mPrism = (aState.mPrism ^ aState.mOrbitB ^ 16145280331526471558ULL) *
                        16598347947591579017ULL;

        aState.mOrbitC = aState.mOrbitC + aState.mOrbitD + 9543457973864807442ULL +
                         aScratchSaltD[((RotL64(aState.mWandererB, 11U) ^ aState.mWandererC) & 0x7FU)];
        aState.mOrbitB = aState.mOrbitB ^ aState.mOrbitC ^ 5205223130063799541ULL ^
                         aScratchSaltC[((RotL64(aState.mSecureB, 29U)) & 0x7FU)];
        aState.mOrbitB = RotL64(aState.mOrbitB * 316374805787132145ULL, 19U);
        aState.mPrism = (aState.mPrism + RotL64(aState.mOrbitD, 7U) +
                         11836353804089605978ULL) * 151893455101192353ULL;

        aState.mInput = (aState.mOrbitA ^ RotL64(aState.mOrbitD, 27U)) +
                        (RotL64(aState.mOrbitB, 21U) ^ aState.mOrbitC);
        aState.mInput = TwistMix64::DiffuseA(aState.mInput ^ aState.mScatter);
        aWorkLaneA[aIndex] = static_cast<std::uint8_t>(aState.mInput);

        aState.mPrism = TwistMix64::DiffuseA(aState.mPrism);
        if ((aState.mPrism & 0x14U) > 5) {
            if ((aState.mPrism & 0x14U) > 16) {
                aState.mInput = TwistMix64::GateRollA_4_8(aState.mInput, 45ULL, aSBoxC, aSBoxB, aSBoxD, aSBoxA);
            } else {
                aState.mInput = TwistMix64::GateTurnA_4_8(aState.mInput, 1ULL, aSBoxC, aSBoxB, aSBoxD, aSBoxA);
            }
        } else {
            if ((aState.mPrism & 0x14U) > 0) {
                aState.mInput = TwistMix64::GateTurnB_4_8(aState.mInput, 3ULL, aSBoxC, aSBoxB, aSBoxD, aSBoxA);
            } else {
                aState.mInput = TwistMix64::GateRollC_4_8(aState.mInput, 13ULL, aSBoxC, aSBoxB, aSBoxD, aSBoxA);
            }
        }

        aState.mWandererA = aState.mWandererA + (aState.mInput ^ aState.mValuePrevious ^ RotL64(aState.mOrbitD, 35U));
        aState.mWandererA = RotL64((aState.mWandererA + aScratchSaltB[((127U - aIndex + 122U) & 0x7FU)]) *
                                   1087872607580760301ULL, 29U);

        aState.mWandererB = aState.mWandererB ^ (RotL64(aState.mInput, 53U) + aState.mCross + aState.mOrbitA);
        aState.mWandererB = RotL64((aState.mWandererB ^ aScratchSaltA[((aIndex + 18U) & 0x7FU)]) *
                                   8437239482832422931ULL, 11U);

        aState.mWandererC = aState.mWandererC + (RotL64(aState.mOrbitB, 27U) ^ aState.mOrbitC ^
                                                 aSaltA[((127U - aIndex + 100U) & 0x7FU)]);
        aState.mWandererC = RotL64(aState.mWandererC * 13653242509885625043ULL, 19U);

        aState.mCarry = aState.mCarry + (RotL64(aState.mWandererA, 5U) ^ aState.mWandererB ^
                                         aState.mWandererC ^ aState.mInput);
        aState.mCarry = RotL64(aState.mCarry * 16598347947591579017ULL, 37U);
        aState.mCarry = aState.mCarry ^ ShiftR64(aState.mCarry, 27U);
    }

    // Loop B
    TwistMemory::Grow(aScratchSaltB, aSaltB, 128U);
    TwistMemory::Grow(aScratchSaltD, aSaltD, 128U);
    TwistMemory::Grow(aScratchSaltA, aSaltC, 128U);
    TwistMemory::Grow(aScratchSaltC, aSaltA, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aState.mValuePrevious = aState.mInput;
        aState.mSecureA = pSecureBlockA[aIndex];
        aState.mSecureB = pSecureBlockB[aIndex];
        aState.mCross = pSecureBlockB[S_BLOCK1 - aIndex];
        aState.mInput = aState.mSecureB;

        aState.mScatter = TwistMix64::DiffuseA(aState.mSecureA ^ ShiftL64(aState.mSecureB, 32U) ^
                                               RotL64(aState.mValuePrevious, 27U));

        aState.mOrbitA = aState.mWandererA + RotL64(aState.mInput, 13U) + 723470163040281385ULL +
                         aScratchSaltC[((aState.mScatter ^ RotL64(aState.mCarry, 21U)) & 0x7FU)];
        aState.mOrbitB = aState.mWandererB ^ RotL64(aState.mValuePrevious, 37U) ^ 164144251673580347ULL ^
                         aScratchSaltA[((aState.mOrbitC ^ RotL64(aState.mOrbitB, 29U)) & 0x7FU)];
        aState.mOrbitC = aState.mWandererC + RotL64(aState.mCross, 11U) +
                         aSaltA[((aIndex + 21U) & 0x7FU)] +
                         aScratchSaltB[((127U - aIndex + 38U) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mCarry, 19U) ^ RotL64(aState.mInput, 7U) ^
                         aSaltC[((aIndex + 121U) & 0x7FU)] ^
                         aScratchSaltD[((127U - aIndex + 109U) & 0x7FU)];
        aState.mPrism = aState.mInput;

        aState.mOrbitA = aState.mOrbitA + aState.mOrbitB + 7453085908731080949ULL +
                         aScratchSaltA[((RotL64(aState.mSecureA, 21U) ^ aState.mValuePrevious) & 0x7FU)];
        aState.mOrbitD = aState.mOrbitD ^ aState.mOrbitA ^ 8267737971662416572ULL ^
                         aScratchSaltC[((aState.mOrbitD ^ RotL64(aState.mWandererC, 27U)) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mOrbitD * 17387767752623742655ULL, 29U);
        aState.mPrism = (aState.mPrism ^ aState.mOrbitC ^ RotL64(aState.mCarry, 11U) ^
                         15715179617732109632ULL) * 12623991755930980029ULL;

        aState.mOrbitC = aState.mOrbitC + aState.mOrbitD + 11235182160061921253ULL +
                         aScratchSaltD[((aState.mOrbitA ^ RotL64(aState.mSecureB, 19U)) & 0x7FU)];
        aState.mOrbitB = aState.mOrbitB ^ aState.mOrbitC ^ 8598806383077600059ULL ^
                         aScratchSaltB[((RotL64(aState.mCross, 21U) + aState.mWandererB) & 0x7FU)];
        aState.mOrbitB = RotL64(aState.mOrbitB, 29U);
        aState.mPrism = (aState.mPrism + RotL64(aState.mOrbitA, 27U) + 4651246947821410674ULL) *
                        14748738896893897469ULL;

        aState.mOrbitA = aState.mOrbitA + aState.mOrbitB + 723470163040281385ULL +
                         aScratchSaltC[((aState.mWandererA ^ RotL64(aState.mOrbitB, 19U)) & 0x7FU)];
        aState.mOrbitD = aState.mOrbitD ^ aState.mOrbitA ^ 164144251673580347ULL ^
                         aScratchSaltA[((aState.mOrbitC + RotL64(aState.mSecureA, 11U)) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mOrbitD * 3044842249584632821ULL, 35U);
        aState.mPrism = (aState.mPrism ^ RotL64(aState.mOrbitB, 29U) ^ 7453085908731080949ULL) *
                        4350523880203148201ULL;

        aState.mOrbitC = aState.mOrbitC + aState.mOrbitD + 8267737971662416572ULL +
                         aScratchSaltD[((aState.mCarry + RotL64(aState.mScatter, 21U)) & 0x7FU)];
        aState.mOrbitB = aState.mOrbitB ^ aState.mOrbitC ^ 15715179617732109632ULL ^
                         aScratchSaltC[((RotL64(aState.mSecureB, 27U)) & 0x7FU)];
        aState.mOrbitB = RotL64(aState.mOrbitB * 12623991755930980029ULL, 3U);
        aState.mPrism = (aState.mPrism + aState.mOrbitD + 11235182160061921253ULL) *
                        17450294827257518445ULL;

        aState.mInput = (RotL64(aState.mOrbitA, 19U) ^ aState.mOrbitB) +
                        (RotL64(aState.mOrbitC, 29U) ^ aState.mOrbitD);
        aState.mInput = TwistMix64::DiffuseB(aState.mInput + aState.mScatter);
        aWorkLaneB[S_BLOCK1 - aIndex] = static_cast<std::uint8_t>(aState.mInput);

        aState.mPrism = TwistMix64::DiffuseC(aState.mPrism);
        if ((aState.mPrism & 0x0CU) > 5) {
            if ((aState.mPrism & 0x0CU) > 9) {
                aState.mInput = TwistMix64::GateTurnB_4_8(aState.mInput, 11ULL, aSBoxD, aSBoxB, aSBoxA, aSBoxC);
            } else {
                aState.mInput = TwistMix64::GateRollC_4_8(aState.mInput, 53ULL, aSBoxD, aSBoxB, aSBoxA, aSBoxC);
            }
        } else {
            if ((aState.mPrism & 0x0CU) > 2) {
                aState.mInput = TwistMix64::GateTurnC_4_8(aState.mInput, 51ULL, aSBoxD, aSBoxB, aSBoxA, aSBoxC);
            } else {
                aState.mInput = TwistMix64::GateTurnA_4_8(aState.mInput, 43ULL, aSBoxD, aSBoxB, aSBoxA, aSBoxC);
            }
        }

        aState.mWandererA = aState.mWandererA + (RotL64(aState.mInput, 5U) ^ aState.mValuePrevious ^ aState.mOrbitD);
        aState.mWandererA = RotL64((aState.mWandererA + aSaltB[((aIndex + 36U) & 0x7FU)]) *
                                   12686926614563335501ULL, 45U);

        aState.mWandererB = aState.mWandererB ^ (aState.mInput + aState.mCross + RotL64(aState.mOrbitA, 51U));
        aState.mWandererB = RotL64((aState.mWandererB ^ aSaltD[((aIndex + 77U) & 0x7FU)]) *
                                   3881672373554374853ULL, 43U);

        aState.mWandererC = aState.mWandererC + (aState.mOrbitB ^ RotL64(aState.mOrbitC, 35U) ^
                                                 aScratchSaltB[((aIndex + 7U) & 0x7FU)]);
        aState.mWandererC = RotL64(aState.mWandererC * 3044842249584632821ULL, 37U);

        aState.mCarry = aState.mCarry + (aState.mWandererA ^ aState.mWandererB ^ aState.mWandererC ^
                                         RotL64(aState.mInput, 3U));
        aState.mCarry = RotL64(aState.mCarry * 4350523880203148201ULL, 13U);
        aState.mCarry = aState.mCarry ^ ShiftR64(aState.mCarry, 23U);
    }

    // Loop C
    TwistMemory::Grow(aScratchSaltA, aSaltA, 128U);
    TwistMemory::Grow(aScratchSaltC, aSaltB, 128U);
    TwistMemory::Grow(aScratchSaltB, aSaltD, 128U);
    TwistMemory::Grow(aScratchSaltD, aSaltC, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aState.mValuePrevious = aState.mInput;
        aState.mSecureA = pSecureBlockA[S_BLOCK1 - aIndex];
        aState.mSecureB = pSecureBlockB[S_BLOCK1 - aIndex];
        aState.mCross = pSecureBlockA[aIndex];
        aState.mInput = aState.mSecureA;

        aState.mScatter = TwistMix64::DiffuseA(aState.mSecureA ^ ShiftL64(aState.mSecureB, 32U) ^
                                               RotL64(aState.mValuePrevious, 21U));

        aState.mOrbitA = aState.mWandererA + RotL64(aState.mInput, 37U) + 2764812075390153081ULL +
                         aScratchSaltC[((aState.mOrbitB + RotL64(aState.mOrbitD, 27U)) & 0x7FU)];
        aState.mOrbitB = aState.mWandererB ^ RotL64(aState.mValuePrevious, 35U) ^ 10420305799720609483ULL ^
                         aScratchSaltB[((RotL64(aState.mWandererA, 13U)) & 0x7FU)];
        aState.mOrbitC = aState.mWandererC + RotL64(aState.mCross, 53U) +
                         aSaltC[((aIndex + 42U) & 0x7FU)] +
                         aScratchSaltA[((127U - aIndex + 62U) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mCarry, 43U) ^ RotL64(aState.mInput, 7U) ^
                         aSaltB[((aIndex + 70U) & 0x7FU)] ^
                         aScratchSaltD[((127U - aIndex + 23U) & 0x7FU)];
        aState.mPrism = aState.mInput;

        aState.mOrbitA = aState.mOrbitA + aState.mOrbitB + 17294320580371979140ULL +
                         aScratchSaltC[((aState.mValuePrevious + RotL64(aState.mOrbitA, 11U)) & 0x7FU)];
        aState.mOrbitD = aState.mOrbitD ^ aState.mOrbitA ^ 11850726035982549370ULL ^
                         aScratchSaltB[((aState.mOrbitC + RotL64(aState.mCarry, 29U)) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mOrbitD * 17454285669682295549ULL, 45U);
        aState.mPrism = (aState.mPrism + aState.mOrbitC + 10976066243792779873ULL) *
                        9339155365641927215ULL;

        aState.mOrbitC = aState.mOrbitC + aState.mOrbitD + 5240591489933860071ULL +
                         aScratchSaltA[((aState.mScatter + RotL64(aState.mWandererB, 19U)) & 0x7FU)];
        aState.mOrbitB = aState.mOrbitB ^ aState.mOrbitC ^ 14210549133045161103ULL ^
                         aScratchSaltD[((RotL64(aState.mCross, 21U)) & 0x7FU)];
        aState.mOrbitB = RotL64(aState.mOrbitB, 27U);
        aState.mPrism = (aState.mPrism ^ aState.mOrbitA ^ 11505058787018800543ULL) *
                        2694776146665126303ULL;

        aState.mOrbitA = aState.mOrbitA + aState.mOrbitB + 2764812075390153081ULL +
                         aScratchSaltB[((RotL64(aState.mSecureA, 13U)) & 0x7FU)];
        aState.mOrbitD = aState.mOrbitD ^ aState.mOrbitA ^ 10420305799720609483ULL ^
                         aScratchSaltC[((RotL64(aState.mWandererA, 11U) ^ aState.mWandererC) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mOrbitD * 17236363657553557919ULL, 29U);
        aState.mPrism = (aState.mPrism + RotL64(aState.mOrbitB, 19U) +
                         17294320580371979140ULL) * 804986467963418095ULL;

        aState.mOrbitC = aState.mOrbitC + aState.mOrbitD + 11850726035982549370ULL +
                         aScratchSaltA[((aState.mOrbitD + RotL64(aState.mSecureB, 21U)) & 0x7FU)];
        aState.mOrbitB = aState.mOrbitB ^ aState.mOrbitC ^ 10976066243792779873ULL ^
                         aScratchSaltB[((aState.mOrbitA + RotL64(aState.mOrbitB, 27U)) & 0x7FU)];
        aState.mOrbitB = RotL64(aState.mOrbitB * 9339155365641927215ULL, 11U);
        aState.mPrism = (aState.mPrism ^ aState.mOrbitD ^ 5240591489933860071ULL) *
                        3958319486932777199ULL;

        aState.mInput = (aState.mOrbitA ^ RotL64(aState.mOrbitD, 13U)) +
                        (RotL64(aState.mOrbitB, 21U) ^ aState.mOrbitC);
        aState.mInput = TwistMix64::DiffuseC(aState.mInput + aState.mScatter);
        aWorkLaneC[aIndex] = static_cast<std::uint8_t>(aState.mInput);

        aState.mPrism = TwistMix64::DiffuseC(aState.mPrism);
        if ((aState.mPrism & 0x2EU) > 27) {
            aState.mInput = TwistMix64::GateRollC_4_8(aState.mInput, 5ULL, aSBoxA, aSBoxB, aSBoxD, aSBoxC);
        } else {
            aState.mInput = TwistMix64::GateRollB_4_8(aState.mInput, 51ULL, aSBoxA, aSBoxB, aSBoxD, aSBoxC);
        }

        aState.mWandererA = aState.mWandererA + (aState.mInput ^ RotL64(aState.mValuePrevious, 3U) ^ aState.mOrbitD);
        aState.mWandererA = RotL64((aState.mWandererA + aScratchSaltD[((aIndex + 40U) & 0x7FU)]) *
                                   12337804040854982787ULL, 43U);

        aState.mWandererB = aState.mWandererB ^ (aState.mInput + RotL64(aState.mCross, 1U) + aState.mOrbitA);
        aState.mWandererB = RotL64((aState.mWandererB ^ aSaltD[((127U - aIndex + 94U) & 0x7FU)]) *
                                   9299568553973520991ULL, 37U);

        aState.mWandererC = aState.mWandererC + (RotL64(aState.mOrbitB, 19U) ^ aState.mOrbitC ^
                                                 aSaltA[((127U - aIndex + 85U) & 0x7FU)]);
        aState.mWandererC = RotL64(aState.mWandererC * 17236363657553557919ULL, 53U);

        aState.mCarry = aState.mCarry + (aState.mWandererA ^ aState.mWandererB ^ aState.mWandererC ^
                                         RotL64(aState.mInput, 7U));
        aState.mCarry = RotL64(aState.mCarry * 804986467963418095ULL, 29U);
        aState.mCarry = aState.mCarry ^ ShiftR64(aState.mCarry, 41U);
    }

    // Loop D
    TwistMemory::Grow(aScratchSaltC, aSaltC, 128U);
    TwistMemory::Grow(aScratchSaltB, aSaltA, 128U);
    TwistMemory::Grow(aScratchSaltD, aSaltB, 128U);
    TwistMemory::Grow(aScratchSaltA, aSaltD, 128U);

    for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
        aState.mValuePrevious = aState.mInput;
        aState.mSecureA = pSecureBlockB[aIndex];
        aState.mSecureB = pSecureBlockA[S_BLOCK1 - aIndex];
        aState.mCross = pSecureBlockB[S_BLOCK1 - aIndex];
        aState.mInput = aState.mSecureA;

        aState.mScatter = TwistMix64::DiffuseA(aState.mSecureA ^ ShiftL64(aState.mSecureB, 32U) ^
                                               RotL64(aState.mValuePrevious, 27U));

        aState.mOrbitA = aState.mWandererA + RotL64(aState.mInput, 1U) + 6749178098990208953ULL +
                         aScratchSaltA[((RotL64(aState.mScatter, 19U)) & 0x7FU)];
        aState.mOrbitB = aState.mWandererB ^ RotL64(aState.mValuePrevious, 45U) ^ 4269284451600718604ULL ^
                         aScratchSaltB[((aState.mWandererB + RotL64(aState.mWandererA, 11U)) & 0x7FU)];
        aState.mOrbitC = aState.mWandererC + RotL64(aState.mCross, 37U) +
                         aSaltA[((aIndex + 27U) & 0x7FU)] +
                         aScratchSaltC[((127U - aIndex + 106U) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mCarry, 29U) ^ RotL64(aState.mInput, 13U) ^
                         aSaltC[((aIndex + 53U) & 0x7FU)] ^
                         aScratchSaltD[((127U - aIndex + 106U) & 0x7FU)];
        aState.mPrism = aState.mInput;

        aState.mOrbitA = aState.mOrbitA + aState.mOrbitB + 1969005361932396569ULL +
                         aScratchSaltB[((RotL64(aState.mCarry, 21U)) & 0x7FU)];
        aState.mOrbitD = aState.mOrbitD ^ aState.mOrbitA ^ 9866505691198744720ULL ^
                         aScratchSaltA[((RotL64(aState.mValuePrevious, 27U)) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mOrbitD * 13792733379970157421ULL, 19U);
        aState.mPrism = (aState.mPrism + RotL64(aState.mOrbitC, 7U) + 1289290601817642279ULL) *
                        1904705842663043447ULL;

        aState.mOrbitC = aState.mOrbitC + aState.mOrbitD + 11146322387440508631ULL +
                         aScratchSaltD[((RotL64(aState.mOrbitA, 11U)) & 0x7FU)];
        aState.mOrbitB = aState.mOrbitB ^ aState.mOrbitC ^ 18344063872910207878ULL ^
                         aScratchSaltC[((RotL64(aState.mWandererC, 29U)) & 0x7FU)];
        aState.mOrbitB = RotL64(aState.mOrbitB, 13U);
        aState.mPrism = (aState.mPrism ^ RotL64(aState.mOrbitA, 21U) ^ 11133441594229311310ULL) *
                        14318682078117499803ULL;

        aState.mOrbitA = aState.mOrbitA + aState.mOrbitB + 6749178098990208953ULL +
                         aScratchSaltB[((RotL64(aState.mCross, 27U)) & 0x7FU)];
        aState.mOrbitD = aState.mOrbitD ^ aState.mOrbitA ^ 4269284451600718604ULL ^
                         aScratchSaltD[((RotL64(aState.mOrbitD, 19U)) & 0x7FU)];
        aState.mOrbitD = RotL64(aState.mOrbitD * 6794795477260232619ULL, 11U);
        aState.mPrism = (aState.mPrism + RotL64(aState.mOrbitB, 29U) + 1969005361932396569ULL) *
                        16055110937839282307ULL;

        aState.mOrbitC = aState.mOrbitC + aState.mOrbitD + 9866505691198744720ULL +
                         aScratchSaltA[((RotL64(aState.mOrbitC, 13U) + aState.mScatter) & 0x7FU)];
        aState.mOrbitB = aState.mOrbitB ^ aState.mOrbitC ^ 1289290601817642279ULL ^
                         aScratchSaltC[((RotL64(aState.mSecureB, 21U)) & 0x7FU)];
        aState.mOrbitB = RotL64(aState.mOrbitB * 1904705842663043447ULL, 35U);
        aState.mPrism = (aState.mPrism ^ aState.mOrbitD ^ 11146322387440508631ULL) *
                        13000117013167711093ULL;

        aState.mInput = (aState.mOrbitA ^ RotL64(aState.mOrbitB, 27U)) +
                        (aState.mOrbitC ^ RotL64(aState.mOrbitD, 19U));
        aState.mInput = TwistMix64::DiffuseA(aState.mInput ^ aState.mScatter);
        aWorkLaneD[S_BLOCK1 - aIndex] = static_cast<std::uint8_t>(aState.mInput);

        aState.mPrism = TwistMix64::DiffuseC(aState.mPrism);
        if ((aState.mPrism & 0x44U) > 52) {
            if ((aState.mPrism & 0x44U) > 67) {
                aState.mInput = TwistMix64::GateRollB_4_8(aState.mInput, 11ULL, aSBoxC, aSBoxB, aSBoxD, aSBoxA);
            } else {
                aState.mInput = TwistMix64::GateRollA_4_8(aState.mInput, 53ULL, aSBoxC, aSBoxB, aSBoxD, aSBoxA);
            }
        } else {
            if ((aState.mPrism & 0x44U) > 1) {
                aState.mInput = TwistMix64::GateTurnC_4_8(aState.mInput, 3ULL, aSBoxC, aSBoxB, aSBoxD, aSBoxA);
            } else {
                aState.mInput = TwistMix64::GateTurnA_4_8(aState.mInput, 51ULL, aSBoxC, aSBoxB, aSBoxD, aSBoxA);
            }
        }

        aState.mWandererA = aState.mWandererA + (aState.mInput ^ aState.mValuePrevious ^ RotL64(aState.mOrbitD, 13U));
        aState.mWandererA = RotL64((aState.mWandererA + aSaltB[((aIndex + 25U) & 0x7FU)]) *
                                   9229680772086911307ULL, 43U);

        aState.mWandererB = aState.mWandererB ^ (RotL64(aState.mInput, 35U) + aState.mCross + aState.mOrbitA);
        aState.mWandererB = RotL64((aState.mWandererB ^ aScratchSaltB[((aIndex + 113U) & 0x7FU)]) *
                                   15144028757380560645ULL, 45U);

        aState.mWandererC = aState.mWandererC + (aState.mOrbitB ^ RotL64(aState.mOrbitC, 37U) ^
                                                 aSaltD[((127U - aIndex + 6U) & 0x7FU)]);
        aState.mWandererC = RotL64(aState.mWandererC * 6794795477260232619ULL, 43U);

        aState.mCarry = aState.mCarry + (aState.mWandererA ^ aState.mWandererB ^ aState.mWandererC ^
                                         RotL64(aState.mInput, 29U));
        aState.mCarry = RotL64(aState.mCarry * 16055110937839282307ULL, 27U);
        aState.mCarry = aState.mCarry ^ ShiftR64(aState.mCarry, 33U);
    }

    switch (pLoopMode) {
        case LoopMode::kLoopA:
            std::memcpy(pOutputBlock, aWorkLaneA, static_cast<std::size_t>(S_BLOCK));
            break;
        case LoopMode::kLoopB:
            std::memcpy(pOutputBlock, aWorkLaneB, static_cast<std::size_t>(S_BLOCK));
            break;
        case LoopMode::kLoopC:
            std::memcpy(pOutputBlock, aWorkLaneC, static_cast<std::size_t>(S_BLOCK));
            break;
        case LoopMode::kLoopD:
        default:
            std::memcpy(pOutputBlock, aWorkLaneD, static_cast<std::size_t>(S_BLOCK));
            break;
    }

    return true;
}

bool GoldenDemo::RollOut(std::uint8_t *pPassword,
                         int pPasswordByteLength,
                         int pOutputByteLength) {
    return RollOut(pPassword, pPasswordByteLength, pOutputByteLength, LoopMode::kLoopD);
}

bool GoldenDemo::RollOut(std::uint8_t *pPassword,
                         int pPasswordByteLength,
                         int pOutputByteLength,
                         LoopMode pLoopMode) {
    if (pOutputByteLength <= 0) {
        return false;
    }

    if (!AllocateBuffers(pOutputByteLength)) {
        return false;
    }

    const unsigned int aPasswordLength =
        (pPasswordByteLength <= 0) ? 0U : static_cast<unsigned int>(pPasswordByteLength);

    std::uint8_t aInputBlock[S_BLOCK];
    std::uint8_t aOutputBlock[S_BLOCK];
    std::uint8_t aSecureBlockA[S_BLOCK];
    std::uint8_t aSecureBlockB[S_BLOCK];

    TwistExpander::UnrollPasswordToSource(aInputBlock, pPassword, aPasswordLength);

    int aWriteOffset = 0;
    while (aWriteOffset < mBufferLength) {
        if (!RunBlock(aInputBlock,
                      aOutputBlock,
                      aSecureBlockA,
                      aSecureBlockB,
                      pLoopMode)) {
            return false;
        }

        const int aBytesRemaining = mBufferLength - aWriteOffset;
        const int aBytesToWrite = (aBytesRemaining >= S_BLOCK) ? S_BLOCK : aBytesRemaining;

        std::memcpy(mData + aWriteOffset,
                    aOutputBlock,
                    static_cast<std::size_t>(aBytesToWrite));

        std::memcpy(mSecureA + aWriteOffset,
                    aSecureBlockA,
                    static_cast<std::size_t>(aBytesToWrite));

        std::memcpy(mSecureB + aWriteOffset,
                    aSecureBlockB,
                    static_cast<std::size_t>(aBytesToWrite));

        // After the first 8192-byte block, next input is prior round output.
        std::memcpy(aInputBlock, aOutputBlock, static_cast<std::size_t>(S_BLOCK));

        aWriteOffset += aBytesToWrite;
    }

    TwistMemory::ZeroBlock(aInputBlock);
    TwistMemory::ZeroBlock(aOutputBlock);
    TwistMemory::ZeroBlock(aSecureBlockA);
    TwistMemory::ZeroBlock(aSecureBlockB);

    return true;
}

bool GoldenDemo::ExportByteStream(const std::string &pPath) const {
    if ((mData == nullptr) || (mBufferLength <= 0) || pPath.empty()) {
        return false;
    }

    return FileIO::Save(pPath,
                        const_cast<std::uint8_t *>(mData),
                        mBufferLength);
}

std::string GoldenDemo::EnsureBinExtension(const std::string &pPath) {
    if (pPath.empty()) {
        return "golden_demo.bin";
    }

    if (HasBinExtension(pPath)) {
        return pPath;
    }

    return pPath + ".bin";
}

bool GoldenDemo::ExportByteStreamProjectRoot(const std::string &pPath) const {
    if ((mData == nullptr) || (mBufferLength <= 0)) {
        return false;
    }

    const std::string aRelativePath = EnsureBinExtension(pPath);
    std::filesystem::path aPath(aRelativePath);

    std::string aResolvedPath;
    if (aPath.is_absolute()) {
        aResolvedPath = aPath.lexically_normal().generic_string();
    } else {
        aResolvedPath = FileIO::ProjectRoot(aRelativePath);
    }

    return FileIO::Save(aResolvedPath,
                        const_cast<std::uint8_t *>(mData),
                        mBufferLength);
}
