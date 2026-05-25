//
//  CSPRNGV2.hpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/18/26.
//

#ifndef CSPRNGV2_hpp
#define CSPRNGV2_hpp

#include "GMagicNumbers.hpp"
#include "GQuick.hpp"
#include "GMagicNumbers.hpp"
#include "GAXSK.hpp"
#include "GAXPL.hpp"
#include "GCache.hpp"

/*
for (std::uint16_t aIndex = 0U; aIndex < S_BLOCK; aIndex += 1U) {
    aPrevious = aCurrent;
    aCurrent = aWorkLaneA[aIndex] ^ ShiftL64(aExpandLaneA[S_BLOCK1 - aIndex], 32U);
    aCross = aWorkLaneA[S_BLOCK1 - aIndex];

    aScatter = TwistMix64::DiffuseA(
        aCurrent ^
        ShiftL64(aCross, 32U) ^
        RotL64(aPrevious, 13U)
    );

    // Orbit assign.
    aOrbitA = aWandererC + RotL64(aCross, 51U);
    aOrbitB = aWandererD + RotL64(aCurrent, 27U);
    aOrbitC = aWandererA ^ RotL64(aPrevious, 37U);
    aOrbitD = RotL64(aCarry, 45U) ^ RotL64(aCurrent, 11U);

    // Orbit update round 0.
    aOrbitB = aOrbitB + aOrbitC;
    aOrbitD = aOrbitD ^ aOrbitB;
    aOrbitD = RotL64(aOrbitD * C0, 35U);

    // Orbit update round 1.
    aOrbitA = aOrbitA + aOrbitD;
    aOrbitC = aOrbitC ^ aOrbitA;
    aOrbitC = RotL64(aOrbitC, 11U);

    // Orbit update round 2.
    aOrbitB = aOrbitB + aOrbitC;
    aOrbitD = aOrbitD ^ aOrbitB;
    aOrbitD = RotL64(aOrbitD * C1, 53U);

    // Orbit update round 3.
    aOrbitA = aOrbitA + aOrbitD;
    aOrbitC = aOrbitC ^ aOrbitA;
    aOrbitC = RotL64(aOrbitC * C2, 45U);

    // Ingress / current update.
    aCurrent =
        (RotL64(aOrbitB, 13U) ^ aOrbitC) +
        (RotL64(aOrbitA, 27U) ^ aOrbitD);

    aCurrent = TwistMix64::DiffuseA(aCurrent + aScatter);
    aExpandLaneB[aIndex] = aCurrent;

    // Wanderer update.
    aWandererD = aWandererD + (aCurrent ^ RotL64(aPrevious, 11U) ^ aOrbitD);
    aWandererD = RotL64(aWandererD * C3, 35U);

    aWandererA = aWandererA ^ (aCurrent + RotL64(aCross, 37U) + aOrbitB);
    aWandererA = RotL64(aWandererA * C4, 43U);

    aWandererC = aWandererC + (aOrbitC ^ RotL64(aOrbitA, 19U));
    aWandererC = RotL64(aWandererC * C5, 13U);

    // Carry update.
    aCarry =
        aCarry +
        (aWandererD ^ aWandererA ^ aWandererC ^ RotL64(aCurrent, 3U));

    aCarry = RotL64(aCarry * C6, 51U);
    aCarry = aCarry ^ ShiftR64(aCarry, 29U);
}
*/

struct CSPRNGV2Slice {
    
    // These are set by kdf:
    GAXSKSkeleton               mARXSkeleton;
    GSymbol                     mDest;
    bool                        mDestWriteInverted;
    std::vector<GSymbol>        mSources;
    GHotPack                    mHotPack;
    
    // These are not set by kdf:
    GAXPLSaltBag                mSaltBag;
    std::vector<GSymbol>        mNonceBytes;
    
    std::vector<GSymbol>        mOrbiters;
    std::vector<GSymbol>        mWanderers;
    
};

class CSPRNGV2 {
public:
    static bool Bake(std::vector<CSPRNGV2Slice> &pSlices,
                     const std::vector<GSymbol> &pSaltsOrbiterAssign,
                     const std::vector<GSymbol> &pSaltsOrbiterUpdate,
                     const std::vector<GSymbol> &pSaltsWandererUpdate,
                     std::vector<GLoop> *pLoops,
                     std::string *pErrorMessage);
    
};

#endif /* CSPRNGV2_hpp */
