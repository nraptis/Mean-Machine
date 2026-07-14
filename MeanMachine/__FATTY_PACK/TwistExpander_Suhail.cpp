#include "TwistExpander_Suhail.hpp"
#include "TwistDiffuse.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix32.hpp"
#include "TwistMix64.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmConstants.hpp"
#include "TwistMemory.hpp"
#include "TwistShiftBox.hpp"
#include "TwistSnow.hpp"
#include "TwistSquash.hpp"

#include <cstdint>
#include <cstring>

TwistExpander_Suhail::TwistExpander_Suhail()
: TwistExpander() {
    mDomainBundleInbuilt.mPhaseASalts = kPhaseASalts;
    mDomainBundleInbuilt.mPhaseAConstants = kPhaseAConstants;
    mDomainBundleInbuilt.mPhaseBSalts = kPhaseBSalts;
    mDomainBundleInbuilt.mPhaseBConstants = kPhaseBConstants;
    mDomainBundleInbuilt.mPhaseCSalts = kPhaseCSalts;
    mDomainBundleInbuilt.mPhaseCConstants = kPhaseCConstants;
    mDomainBundleInbuilt.mPhaseDSalts = kPhaseDSalts;
    mDomainBundleInbuilt.mPhaseDConstants = kPhaseDConstants;
    mDomainBundleInbuilt.mPhaseESalts = kPhaseESalts;
    mDomainBundleInbuilt.mPhaseEConstants = kPhaseEConstants;
    mDomainBundleInbuilt.mPhaseFSalts = kPhaseFSalts;
    mDomainBundleInbuilt.mPhaseFConstants = kPhaseFConstants;
    mDomainBundleInbuilt.mPhaseGSalts = kPhaseGSalts;
    mDomainBundleInbuilt.mPhaseGConstants = kPhaseGConstants;
    mDomainBundleInbuilt.mPhaseHSalts = kPhaseHSalts;
    mDomainBundleInbuilt.mPhaseHConstants = kPhaseHConstants;
    mDomainBundleEphemeral.Zero();
}

void TwistExpander_Suhail::KDF_A(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  std::uint8_t *pSnow,
                                  int pIndexKDF) {
    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pSnow, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr) || (pSnow == nullptr)) { return; }
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aWindLaneA = pWorkSpace->mWindLaneA;
    std::uint8_t *aWindLaneB = pWorkSpace->mWindLaneB;
    std::uint8_t *aWindLaneC = pWorkSpace->mWindLaneC;
    std::uint8_t *aWindLaneD = pWorkSpace->mWindLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xACD7E6495B6BA7A3ULL; std::uint64_t aIngress = 0xC27543A2F3CC550EULL; std::uint64_t aCarry = 0x9B46785368868199ULL;

    std::uint64_t aWandererA = 0xA4A1C29048F13EFEULL; std::uint64_t aWandererB = 0x8914189F52EFE28FULL; std::uint64_t aWandererC = 0xAE6D25AFC4D64435ULL; std::uint64_t aWandererD = 0xA2E97B7C0B639545ULL;
    std::uint64_t aWandererE = 0xB02516BC4A527F9DULL; std::uint64_t aWandererF = 0x8E02631A99D2E585ULL; std::uint64_t aWandererG = 0x84024990F06707D9ULL; std::uint64_t aWandererH = 0xDC2B94F730562B0EULL;
    std::uint64_t aWandererI = 0x976948A13A7EA394ULL; std::uint64_t aWandererJ = 0xE0E2DA6809C84FF8ULL; std::uint64_t aWandererK = 0xFBE7BE74AF2F9358ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11950100718367473785U;
        aCarry = 16957563323284804284U;
        aWandererA = 10161515830970476350U;
        aWandererB = 18317318483138424516U;
        aWandererC = 10313539883457937093U;
        aWandererD = 11170366830841125591U;
        aWandererE = 9529013412384990137U;
        aWandererF = 15437693220239703775U;
        aWandererG = 13817334787553105591U;
        aWandererH = 11055085859232733924U;
        aWandererI = 14723047186794296685U;
        aWandererJ = 11053481298280672550U;
        aWandererK = 14664760512762106283U;
    //
    // ---------------------------------------------------
    // KDF_A_A kdf_a_loop_a:
    // ---------------------------------------------------
    // read from: source, snow
    // temp storage: scrap_a, scrap_b
    // ---------------------------------------------------
    // write to: scrap_a, scrap_b, earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::KDF_A_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // KDF_A_B kdf_a_loop_b:
    // ---------------------------------------------------
    // read from: earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::KDF_A_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // KDF_A_C kdf_a_loop_c:
    // ---------------------------------------------------
    // read from: fire_a, fire_b, fire_c, fire_d
    // temp storage: earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::KDF_A_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // KDF_A_D kdf_a_loop_d:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: earth_b, earth_c, earth_d, source, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: fuse_a, fuse_b, fuse_c, fuse_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::KDF_A_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aWindLaneA, aWindLaneB, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aWindLaneC, aWindLaneD, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    //
    // ---------------------------------------------------
    // KDF_A_E kdf_a_loop_e:
    // ---------------------------------------------------
    // read from: wind_a, wind_b, wind_c, wind_d
    // temp storage: earth_a, earth_b, earth_c, earth_d, source, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: water_a, water_b, water_c, water_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::KDF_A_E(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

}

void TwistExpander_Suhail::KDF_B(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  int pIndexKDF) {
    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xB6103AF250D67B4AULL; std::uint64_t aIngress = 0xE7181CC2A450790DULL; std::uint64_t aCarry = 0xD59C349B8ADA63A2ULL;

    std::uint64_t aWandererA = 0xDC75FAE728A1BB32ULL; std::uint64_t aWandererB = 0xE4A4F8A2C80C7417ULL; std::uint64_t aWandererC = 0xEBD0034A34B4A01FULL; std::uint64_t aWandererD = 0xA265A8221EF36699ULL;
    std::uint64_t aWandererE = 0x9FFEA3831CC22562ULL; std::uint64_t aWandererF = 0xC84766622FDF4146ULL; std::uint64_t aWandererG = 0xFC934CA10E8FD7CAULL; std::uint64_t aWandererH = 0xDC488FC92E0B2522ULL;
    std::uint64_t aWandererI = 0xCA668CB6AC086AE3ULL; std::uint64_t aWandererJ = 0xAC7D1EB5EE72E172ULL; std::uint64_t aWandererK = 0xD0A09EC222C87E32ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15609507741734954294U;
        aCarry = 10677534049206400005U;
        aWandererA = 13805996902497044730U;
        aWandererB = 16467909918556247613U;
        aWandererC = 18016191955849334558U;
        aWandererD = 11843636717296187877U;
        aWandererE = 16142800483932716376U;
        aWandererF = 9412743169250675345U;
        aWandererG = 10542080169201053726U;
        aWandererH = 16081087703364091990U;
        aWandererI = 13069875485975072354U;
        aWandererJ = 16757006521899963152U;
        aWandererK = 17684025157788620647U;
    //
    // ---------------------------------------------------
    // KDF_B_A kdf_b_loop_a:
    // ---------------------------------------------------
    // read from: water_a, water_b, water_c, water_d
    // temp storage: wind_a, wind_b, wind_c, wind_d, fire_a, fire_b, fire_c, source
    // ---------------------------------------------------
    // write to: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::KDF_B_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // KDF_B_B kdf_b_loop_b:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: water_a, water_b, water_c, water_d, source, wind_a, wind_b, wind_d
    // ---------------------------------------------------
    // write to: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::KDF_B_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // KDF_B_C kdf_b_loop_c:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: expand_a, expand_b, expand_c, expand_d, earth_d, fire_d, water_d, source
    // ---------------------------------------------------
    // write to: fuse_a, fuse_b, fuse_c, fuse_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::KDF_B_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aWorkLaneA, aWorkLaneB, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aWorkLaneC, aWorkLaneD, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    //
    // ---------------------------------------------------
    // KDF_B_D kdf_b_loop_d:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // temp storage: water_a, water_b, water_c, water_d, fire_a, fire_b, fire_c, wind_c
    // ---------------------------------------------------
    // write to: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::KDF_B_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

}

void TwistExpander_Suhail::Seed(TwistWorkSpace *pWorkSpace,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint64_t pNonce,
                                 std::uint8_t *pPassword,
                                 std::size_t pPasswordByteLength,
                                 std::uint8_t *pDestination) {
    TwistExpander::Seed(pWorkSpace, pFarmSalt, pNonce, pPassword, pPasswordByteLength, pDestination);
    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr)) { return; }
    std::uint8_t *aSource = pWorkSpace->mSource;
    std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    std::uint8_t *aSnowLaneC = pWorkSpace->mSnowLaneC;
    std::uint8_t *aSnowLaneD = pWorkSpace->mSnowLaneD;
    std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint8_t *aWaterLaneA = pWorkSpace->mWaterLaneA;
    std::uint8_t *aWaterLaneB = pWorkSpace->mWaterLaneB;
    std::uint8_t *aWaterLaneC = pWorkSpace->mWaterLaneC;
    std::uint8_t *aWaterLaneD = pWorkSpace->mWaterLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    std::uint8_t *aInvestLaneE = pWorkSpace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = pWorkSpace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = pWorkSpace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = pWorkSpace->mInvestLaneH;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0x9D90EC178E9E49DEULL;
    std::uint64_t aIngress = 0x9F27E9530D81396AULL;
    std::uint64_t aCarry = 0xD663AFE136874005ULL;

    std::uint64_t aWandererA = 0xE2760AAE7CCBFFCDULL;
    std::uint64_t aWandererB = 0xDC04CACD47CFDF08ULL;
    std::uint64_t aWandererC = 0x92EDB28640006A64ULL;
    std::uint64_t aWandererD = 0xE03A2A9ED9EE6D9FULL;
    std::uint64_t aWandererE = 0xC048195BCEA1F87BULL;
    std::uint64_t aWandererF = 0xEE93CED650B02AB5ULL;
    std::uint64_t aWandererG = 0x89E624FC5BC6F2F1ULL;
    std::uint64_t aWandererH = 0xCF99FB266E9A40C0ULL;
    std::uint64_t aWandererI = 0xCCDB941B64CAE3CFULL;
    std::uint64_t aWandererJ = 0x91571152FAD5CB26ULL;
    std::uint64_t aWandererK = 0x828CE0255917B1B0ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneD, 0);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseAConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseAConstants), &(mDomainBundleEphemeral.mPhaseASalts), 0);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseAConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase B
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneB, 1);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseBConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseBConstants), &(mDomainBundleEphemeral.mPhaseBSalts), 1);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseBConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase C
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneA, 2);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseCConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseCConstants), &(mDomainBundleEphemeral.mPhaseCSalts), 2);
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseCConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase D
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneC, 3);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseDConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseDConstants), &(mDomainBundleEphemeral.mPhaseDSalts), 3);
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseDConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase E
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneD, 4);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseEConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseEConstants), &(mDomainBundleEphemeral.mPhaseESalts), 4);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseEConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase F
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneB, 5);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseFConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseFConstants), &(mDomainBundleEphemeral.mPhaseFSalts), 5);
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseFConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase G
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneA, 6);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseGConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseGConstants), &(mDomainBundleEphemeral.mPhaseGSalts), 6);
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseGConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase H
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneC, 7);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseHConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseHConstants), &(mDomainBundleEphemeral.mPhaseHSalts), 7);
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseHConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    // GSquashInvestToKeyBoxes (start)
    SquashInvestToKeyBoxes();
    // GSquashInvestToKeyBoxes (end)
    //
    //
    // ---------------------------------------------------
    // GSeedRunSeed_A seed_loop_a:
    // ---------------------------------------------------
    // read from: source, key_row_read_a, key_row_read_b
    // temp storage: water_a, water_b
    // ---------------------------------------------------
    // write to: water_a, water_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Seed_A(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GSeedRunSeed_B seed_loop_a:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d, earth_a, earth_b
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Seed_B(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GSeedRunSeed_C seed_loop_b:
    // ---------------------------------------------------
    // read from: work_c, work_d, earth_a, earth_b
    // temp storage: work_a, work_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: earth_c, earth_d, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Seed_C(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GSeedRunSeed_D seed_loop_b:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: work_a, work_b, work_c, work_d, earth_a, earth_b, expand_a, expand_b
    // ---------------------------------------------------
    // write to: snow_a, snow_b, fuse_a, fuse_b, fuse_c, fuse_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Seed_D(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aFireLaneA, aFireLaneB, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aFireLaneC, aFireLaneD, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    //
    // ---------------------------------------------------
    // GSeedRunSeed_E seed_loop_c:
    // ---------------------------------------------------
    // read from: fire_a, fire_b, fire_c, fire_d
    // temp storage: key_row_read_a, key_row_read_b, snow_a, snow_b, expand_a, expand_b, expand_c, expand_d, earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: water_c, water_d, invest_a, invest_b, invest_c, invest_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Seed_E(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GSeedRunSeed_F seed_loop_c:
    // ---------------------------------------------------
    // read from: invest_a, invest_b, invest_c, invest_d
    // temp storage: snow_a, snow_b, water_c, water_d, earth_a, earth_b, earth_c, earth_d, fire_a, fire_b, source, key_row_read_a
    // ---------------------------------------------------
    // write to: snow_c, snow_d, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Seed_F(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GSeedRunSeed_G seed_loop_d:
    // ---------------------------------------------------
    // read from: wind_a, wind_b, wind_c, wind_d
    // temp storage: snow_c, snow_d, source, key_row_read_b, invest_a, invest_b, invest_c, invest_d, snow_a, snow_b, water_c, water_d
    // ---------------------------------------------------
    // write to: water_a, water_b, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Seed_G(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GSeedRunSeed_H seed_loop_e:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: fire_c, fire_d, source, key_row_read_a, snow_c, snow_d, expand_c, expand_d, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fuse_a, fuse_b, fuse_c, fuse_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Seed_H(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgD;
    //
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aInvestLaneE, aInvestLaneF, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aInvestLaneG, aInvestLaneH, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    //
    // ---------------------------------------------------
    // GSeedRunSeed_I seed_loop_f:
    // ---------------------------------------------------
    // read from: invest_e, invest_f, invest_g, invest_h
    // temp storage: key_row_read_a, key_row_read_b, fire_a, fire_b, expand_a, expand_b, snow_a, snow_b, water_a, water_b, water_c, water_d
    // ---------------------------------------------------
    // write to: fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Seed_I(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

        TwistSquash::SquashC(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    //
    // ---------------------------------------------------
    // GROW_A grow_key_a:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // temp storage: scrap_a, scrap_b, water_a, water_b, water_c, water_d, invest_a, invest_b, invest_c, invest_d, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: scrap_a, scrap_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    GrowKeyA(pWorkSpace);
    //
    // ---------------------------------------------------
    // GROW_B grow_key_b:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: scrap_c, scrap_d, earth_a, earth_b, earth_c, earth_d, wind_a, wind_b, wind_c, wind_d, invest_e, invest_f, invest_g, invest_h
    // ---------------------------------------------------
    // write to: scrap_c, scrap_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    GrowKeyB(pWorkSpace);
    Zero_PostSeed();
}

// SmartSquash candidate 32 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1788 / 1984 (90.12%)
// Total distance from earlier candidates: 56284
void TwistExpander_Suhail::SquashInvestToKeyBoxes() {
    static_assert((S_BLOCK / W_KEY) == 16, "SquashInvestToKeyBoxes expects 16 invest fragments.");
    static_assert(H_KEY == 8, "SquashInvestToKeyBoxes expects 8 key rows per box.");
    if (mWorkspace == nullptr) { return; }
    std::uint8_t *aInvestLaneA = mWorkspace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = mWorkspace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = mWorkspace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = mWorkspace->mInvestLaneD;
    std::uint8_t *aInvestLaneE = mWorkspace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = mWorkspace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = mWorkspace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = mWorkspace->mInvestLaneH;

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 192U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1025U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 205U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2014U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1828U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1491U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 996U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1889U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1368U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1922U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 247U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 213U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1182U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1847U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1028U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1334U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1628U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 832U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 687U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1281U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1726U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 284U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 639U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 295U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1571U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1698U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1363U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1985U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1303U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 708U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 254U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 51U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 573U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1947U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 365U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 942U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1962U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1762U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 691U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 332U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 903U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 572U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1793U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1518U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 629U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 755U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1262U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1195U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 527U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 74U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1737U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1790U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 292U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 831U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1878U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 965U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1888U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1733U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1864U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 214U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 13U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 119U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1249U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 776U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 709U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1037U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1078U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 396U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 677U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1805U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 600U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1348U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 419U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 713U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 61U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1188U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1986U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1014U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 842U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1297U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 16U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 241U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1574U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 699U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1955U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1551U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 797U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 193U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 700U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 829U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1512U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1288U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1013U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 469U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1419U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 561U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 988U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1857U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2046U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1029U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1353U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1124U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 455U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 506U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1362U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 551U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 420U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1407U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 408U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 595U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1659U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 884U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1192U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1522U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 824U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1009U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1378U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1787U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1106U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 625U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1506U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 462U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 412U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1113U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1389U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1783U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1654U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 154U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Suhail::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xD33A2268DE507818ULL; std::uint64_t aIngress = 0xDEE29ABE81CBE88BULL; std::uint64_t aCarry = 0xFC0BE84E01F6CE14ULL;

    std::uint64_t aWandererA = 0xFBA203CEB0C5817DULL; std::uint64_t aWandererB = 0xDF74FA83166FAFC4ULL; std::uint64_t aWandererC = 0xF04516AD8717915AULL; std::uint64_t aWandererD = 0xE1CD6D8C01A1BC84ULL;
    std::uint64_t aWandererE = 0xEBCCFEF4F9FA8BAFULL; std::uint64_t aWandererF = 0xCB7B9CB708A7AFA7ULL; std::uint64_t aWandererG = 0xC12145EB37E11D5FULL; std::uint64_t aWandererH = 0x8BC2E5161CF89417ULL;
    std::uint64_t aWandererI = 0xF1F79C6F48CBBF4EULL; std::uint64_t aWandererJ = 0xF46D47302394AE6EULL; std::uint64_t aWandererK = 0x923922824C018AEEULL;

    // [seed]
        aPrevious = 12825173922262972678U;
        aCarry = 12068094146685199294U;
        aWandererA = 15962287816475939085U;
        aWandererB = 11327968469823268206U;
        aWandererC = 10875463259540706794U;
        aWandererD = 17796250354754763383U;
        aWandererE = 17688171371646265634U;
        aWandererF = 16358678363313385640U;
        aWandererG = 14206467783350904322U;
        aWandererH = 9833902046076230040U;
        aWandererI = 11374124763189498223U;
        aWandererJ = 11192341192951273042U;
        aWandererK = 11146011921810133827U;
    //
    // ---------------------------------------------------
    // GTwistRunTwist_A twist_loop_a:
    // ---------------------------------------------------
    // read from: source, key_row_read_a, key_row_read_b
    // temp storage: scrap_a, scrap_b
    // ---------------------------------------------------
    // write to: scrap_a, scrap_b, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Twist_A(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GTwistRunTwist_B twist_loop_b:
    // ---------------------------------------------------
    // read from: wind_a, wind_b, wind_c, wind_d
    // temp storage: scrap_a, scrap_b
    // ---------------------------------------------------
    // write to: water_c, water_d, snow_a, snow_b, snow_c, snow_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Twist_B(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GTwistRunTwist_C twist_loop_c:
    // ---------------------------------------------------
    // read from: snow_a, snow_b, snow_c, snow_d
    // temp storage: water_c, water_d, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    // write to: water_a, water_b, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Twist_C(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GTwistRunTwist_D twist_loop_d:
    // ---------------------------------------------------
    // read from: fire_a, fire_b, fire_c, fire_d
    // temp storage: water_a, water_b, water_c, water_d, wind_a, wind_b, wind_c, wind_d, snow_a, snow_b, snow_c, snow_d
    // ---------------------------------------------------
    // write to: invest_a, invest_b, invest_c, invest_d, earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Twist_D(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
    // ---------------------------------------------------
    // GTwistRunTwist_E twist_loop_e:
    // ---------------------------------------------------
    // read from: earth_a, earth_b, earth_c, earth_d
    // temp storage: invest_a, invest_b, invest_c, invest_d, water_a, water_b, snow_a, snow_b, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: invest_e, invest_f, invest_g, invest_h, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::Twist_E(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
        TwistSquash::SquashA(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    //
    // ---------------------------------------------------
    // GROW_A grow_key_a:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // temp storage: scrap_a, scrap_b, water_a, water_b, water_c, water_d, invest_a, invest_b, invest_c, invest_d, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: scrap_a, scrap_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    GrowKeyA(pWorkSpace);
    //
    // ---------------------------------------------------
    // GROW_B grow_key_b:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: scrap_c, scrap_d, earth_a, earth_b, earth_c, earth_d, wind_a, wind_b, wind_c, wind_d, invest_e, invest_f, invest_g, invest_h
    // ---------------------------------------------------
    // write to: scrap_c, scrap_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Suhail_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    GrowKeyB(pWorkSpace);
}

// GrowA candidate 32 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 16750; nearest pair: 453 / 674
void TwistExpander_Suhail::GrowKeyA(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) { return; }
    std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    std::uint8_t *aScrapLaneA = pWorkSpace->mScrapLaneA;
    std::uint8_t *aScrapLaneB = pWorkSpace->mScrapLaneB;
    std::uint8_t *aScrapLaneC = pWorkSpace->mScrapLaneC;
    std::uint8_t *aScrapLaneD = pWorkSpace->mScrapLaneD;
    std::uint8_t *aMergeLaneA = pWorkSpace->mMergeLaneA;
    std::uint8_t *aMergeLaneB = pWorkSpace->mMergeLaneB;
    std::uint8_t *aMergeLaneC = pWorkSpace->mMergeLaneC;
    std::uint8_t *aMergeLaneD = pWorkSpace->mMergeLaneD;
    std::uint8_t *aKeyRowWriteA = &(pWorkSpace->mKeyBoxA[0][0]);
    static_assert((S_BLOCK / S_QUARTER) == 4, "GrowKeyA expects four expansion-lane quarters.");
    static_assert((S_QUARTER / W_KEY) == 4, "GrowKeyA expects four key chunks per quarter.");
    TwistShiftBox::ShiftKeyBoxA(pWorkSpace);
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4148U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7040U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3256U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 504U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4613U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5116U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1974U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2936U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7352U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5066U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6857U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6624U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6682U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 877U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 886U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1408U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 658U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 902U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 680U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 464U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1496U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1845U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 697U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1320U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1255U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 957U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1020U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1554U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 588U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 626U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 707U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 118U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1772U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 782U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 692U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 32 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 16743; nearest pair: 448 / 674
void TwistExpander_Suhail::GrowKeyB(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aScrapLaneA = pWorkSpace->mScrapLaneA;
    std::uint8_t *aScrapLaneB = pWorkSpace->mScrapLaneB;
    std::uint8_t *aScrapLaneC = pWorkSpace->mScrapLaneC;
    std::uint8_t *aScrapLaneD = pWorkSpace->mScrapLaneD;
    std::uint8_t *aMergeLaneA = pWorkSpace->mMergeLaneA;
    std::uint8_t *aMergeLaneB = pWorkSpace->mMergeLaneB;
    std::uint8_t *aMergeLaneC = pWorkSpace->mMergeLaneC;
    std::uint8_t *aMergeLaneD = pWorkSpace->mMergeLaneD;
    std::uint8_t *aKeyRowWriteB = &(pWorkSpace->mKeyBoxB[0][0]);
    static_assert((S_BLOCK / S_QUARTER) == 4, "GrowKeyB expects four work-lane quarters.");
    static_assert((S_QUARTER / W_KEY) == 4, "GrowKeyB expects four key chunks per quarter.");
    TwistShiftBox::ShiftKeyBoxB(pWorkSpace);
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4141U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3104U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4273U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2904U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6560U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6805U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5209U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 919U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5692U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 872U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5560U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2024U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3702U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2800U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7663U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7910U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1800U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 230U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1528U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 809U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 187U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1987U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1735U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 979U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1261U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1248U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1137U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1540U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 296U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1496U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1212U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 469U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1164U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 927U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1298U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 685U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseASalts = {
    {
        {
            0x5787AEAE1AE176F3ULL, 0x2692073726D51BD5ULL, 0xC13C44ED7A6D70DFULL, 0x2D459829D02C7FDCULL, 
            0x1021EBFC9F659215ULL, 0x682E33C65AAAE2C3ULL, 0x6E4000F35F3FF38CULL, 0x34C4D444B83CC5BBULL, 
            0x0D57BF5017C8B631ULL, 0x0199C438EEAA46B5ULL, 0x01FAA87866D62B60ULL, 0x09DB466A6BFB14FFULL, 
            0xF580E25F2667B6D9ULL, 0xA1364C573499B3CCULL, 0xD5AA042EE2ED8BA6ULL, 0x16CE62474DB8F6D0ULL, 
            0x21B3711B58D4EC81ULL, 0xE21F02CB90D01515ULL, 0x936EA5B8685EF6DCULL, 0xE9AFD5C77C83AE2BULL, 
            0x089125EB9EECE3B2ULL, 0x61C21405D4B0B129ULL, 0x144D9762557761B2ULL, 0x37520982EC754516ULL, 
            0x80ADD93CB9A165D2ULL, 0xCEB24E0B345E1784ULL, 0xBF6F993ACA880B95ULL, 0xFB9AEB04C572FEAFULL, 
            0xE21E18DFEAB6242AULL, 0xBA561D4921E0ECDDULL, 0xD28577AF1ADFB244ULL, 0x120837B4411EF605ULL
        },
        {
            0x047ACE05D26FC9B3ULL, 0xD57F4A5868D6D61BULL, 0x8A5C238F6E440A6CULL, 0x7AC98C7EB9EF3591ULL, 
            0x23C3AC21E563A020ULL, 0x2B52C7733983B517ULL, 0x80A3BD22A7CB766CULL, 0x3928706A0174D390ULL, 
            0xE497C4DCF87D135DULL, 0x0D7E6E0351C875B9ULL, 0x48BBFD35423E9CE4ULL, 0x8DDCACE7C977AFBCULL, 
            0x7C6DA327BF7572E9ULL, 0x5C0585CA11A1FDABULL, 0x39120447260D228BULL, 0x57ED17A8A376B938ULL, 
            0x6F8DD57A433DFFB1ULL, 0xE891C20B400A8763ULL, 0xF7BEFB7D0E8FD6DCULL, 0x405972D2C487F638ULL, 
            0xB723DDDADFE244FCULL, 0x1A0FE0B503633C1AULL, 0x93F13654EA9BA804ULL, 0x7AC9A9A8877D9C13ULL, 
            0xCF29A839632D3F2BULL, 0x72BBEEF7AF62A2DCULL, 0xAECA4FDAAD3016B7ULL, 0x6FC83B0035EC0163ULL, 
            0x21461669767BE74DULL, 0xE2E0F21FB43CC2FCULL, 0xA7A03E5A5D5E9575ULL, 0x7AF437E9ED4AF2A3ULL
        },
        {
            0x3BE2FDFAB54667AFULL, 0x464D1E921387196FULL, 0x833F14F55769C9ADULL, 0x6F83585C3025FDBDULL, 
            0x62D8CD1D1E0DB44EULL, 0x9B8A42E282121E45ULL, 0xB2A7FAB0F6698B32ULL, 0x2F008C5A98EFA932ULL, 
            0x8FFE3FF684534937ULL, 0xB83AA97EE95AAF81ULL, 0x00AA6D3A616E67FDULL, 0x6C3C96E593E2829FULL, 
            0x8F75CD7314948B3BULL, 0x0042FC73DDFC0172ULL, 0x21FA3FF7F60FBB63ULL, 0x605DE104C7E120FFULL, 
            0x44D8B4ECE597A974ULL, 0x97C5711BCEF33111ULL, 0x4B078A94AF6FF171ULL, 0xEC9526DFF06553C5ULL, 
            0xADB9B333CC26C2DDULL, 0x98D216216837FAF0ULL, 0x812DA71FECF3FBC5ULL, 0x6FD103EBBFAE3997ULL, 
            0x5CFEB7E1700901B9ULL, 0x1EF6F2C98805A606ULL, 0x48F57EF384087AD6ULL, 0xE47B1FCB7443A0C5ULL, 
            0x22ACAADAB4972D3CULL, 0xD89A059C03BEDBC5ULL, 0xADCB10851329D09AULL, 0x111A7E3CA25569DFULL
        },
        {
            0xF4027FA5CFF032ECULL, 0xD327FF481222E871ULL, 0x71E47629267BD4AFULL, 0xA1A75F5F9D8D5116ULL, 
            0x7529BE57409B71BFULL, 0x96BD89811A7A280FULL, 0x7DFC6EEE09400486ULL, 0xB0E39DABF411B0C9ULL, 
            0xD686E24005BB40E1ULL, 0xDA964AF24CD48751ULL, 0x3EFD0F1AF3000088ULL, 0x31A9019F6A3B9DA9ULL, 
            0xA818F216962CEBB4ULL, 0xB1441796475ADE67ULL, 0xBE21D7BFDF80997AULL, 0x497093CA3A984DF4ULL, 
            0x6CEF90085B34F147ULL, 0x6F7143D755EA000FULL, 0x3F02ECAECEC62E47ULL, 0x6AF475AB3421F38BULL, 
            0x9B2C3BA8D458899DULL, 0xBFD21A3A13ADC18AULL, 0xAF65A8326E2D8E55ULL, 0x9CC0440B50230084ULL, 
            0xD86D48D7854F3978ULL, 0x63C50FE9893AF076ULL, 0x4A8C5E994430B6DFULL, 0x53DD92DFFAF4E9DDULL, 
            0x6F2AAAF292A844B3ULL, 0x39E82574020865F3ULL, 0x295FC4DDF66416A5ULL, 0x782AD89DB3BA932FULL
        },
        {
            0xF6E3AB1AAE35A70DULL, 0x50148AF9F4A94566ULL, 0x8A51BB1BF9B1F156ULL, 0x95C1094E60A11FD8ULL, 
            0x58230CC60DF9E293ULL, 0x68AEE4BA928A6E57ULL, 0x2BB9852E2E41E8EAULL, 0x21BF05E06677D074ULL, 
            0x00D92AAE79335B43ULL, 0xB6551805AF9FDD9AULL, 0xCD5E216C9CDC21E4ULL, 0x9D01021D3ECC7FC4ULL, 
            0xAE7669AA64AD7885ULL, 0x8B43FF3B408CD47DULL, 0x87694A3C9BCB6851ULL, 0xFBB549655CE62C1EULL, 
            0x855CE146F12A710CULL, 0xC3E3BCACF78DA04CULL, 0xCD0D3E447290B3CEULL, 0x24155EABBC9C4DDAULL, 
            0x3135172FDDD19FFDULL, 0xB37994E25DFF7430ULL, 0x85DB9D151D5C205CULL, 0x8BCBF0950FE6C721ULL, 
            0x30A9171474309173ULL, 0x6724CDE18DEA1903ULL, 0xFACDC87A0D2A84AFULL, 0x24F22E9E3D70A3A9ULL, 
            0x60EE9D0A22C26FE7ULL, 0xB998BC274B1230F8ULL, 0x7AFF3DBCCAD62062ULL, 0xE499A64B1F969E54ULL
        },
        {
            0xB357A11164B86FE5ULL, 0x44C96C8F3ED6AD71ULL, 0xC87808665A31BD15ULL, 0x785CDB6DDF74DFCFULL, 
            0x3C59FA2A05CE17B1ULL, 0x4220105568657894ULL, 0x2A7FD18EA2B864BEULL, 0x45E461648859DE00ULL, 
            0x5168191E5EE2BEF5ULL, 0xE8FD33329B9B60FEULL, 0x2598A70D28393F4AULL, 0x27EF7DA31E2183F9ULL, 
            0x2ABFDBCA17D65B32ULL, 0x2A6190739DC29CBEULL, 0x44FE4F39674EAFECULL, 0x9E6012D0DBEAC88FULL, 
            0x7B1302B574F467DEULL, 0xC5438DFF57A4079DULL, 0x9C8402F1E7CBD75BULL, 0xC271BC055C228873ULL, 
            0xCE2CF481C8E4FA7DULL, 0xF62C12DFD5BE117DULL, 0x408CA5FF8F2B4C3CULL, 0x1D398FA0BE7780B7ULL, 
            0x86428DD6D4849682ULL, 0xE0F7EC48D85772D2ULL, 0xAE7644AFE46437B9ULL, 0xC394E2E4EBBCDD9CULL, 
            0x74A8B418E441112AULL, 0x3EC8C920A8F0264EULL, 0xD388479810716072ULL, 0x3094773C4E94B190ULL
        }
    },
    {
        {
            0x282432A6297A5E03ULL, 0xA09877095422F651ULL, 0xCDF9F0E9386CC422ULL, 0x22CDF742D1479987ULL, 
            0xD8259395CF50061EULL, 0x1A0768E6822169DAULL, 0xB5755AF4E2FA105EULL, 0x3B47624504DAD58DULL, 
            0xC6A95D8F2EFDCD1AULL, 0x906A8F055A7B79AFULL, 0xC152E3FEA96129A3ULL, 0xD00520DF9F44484CULL, 
            0x5E7B6B277F831E57ULL, 0xC8284926529F200DULL, 0x2905C836275C688EULL, 0x6665F17503F593ECULL, 
            0x71B855CB2CBBD1B6ULL, 0xA485735A47895024ULL, 0x50489DA88B3FD860ULL, 0x779EF842DB33E5E2ULL, 
            0xAEBDE36EDDC6DDC5ULL, 0xEDE3D94E53579C75ULL, 0x980C8B0D071B1484ULL, 0x4BE7B2C31058140EULL, 
            0xF19DB2C7ADDD1E08ULL, 0x0ADD59CF12F1AF47ULL, 0x1C6D7B47505B5787ULL, 0x8CF14FE02435E166ULL, 
            0x3C14019F7086E96AULL, 0x7755A23A7668F489ULL, 0x84C02575055759B3ULL, 0xABDA9211B8C76B5BULL
        },
        {
            0x276ECC24F9B9C45DULL, 0xEB219748644109DEULL, 0x7798F7895EEDBF0EULL, 0xC711CC7665DCACB5ULL, 
            0xE5A42B6108478A5BULL, 0x01738D05A7225947ULL, 0xC1E1C9A420E9DA2FULL, 0x75093BD7C44377AAULL, 
            0x4498EA12443E00EDULL, 0xCBDF627FB0FF5DCDULL, 0x63C698121F7F30FBULL, 0xCEF974C8EDDBFCA2ULL, 
            0x8EFE19EDA7959186ULL, 0x1796A216918B1365ULL, 0x71C92F93A9CCB28CULL, 0xFECDE45F214D28F8ULL, 
            0x90126710D28346A0ULL, 0x804D5EF288F9EEB9ULL, 0x3918D6CB10099DA9ULL, 0x3271ADDB765B6882ULL, 
            0x5299A1FDE78B5C1BULL, 0x10EDE7E03ACFC035ULL, 0x9907A77FC525B5E4ULL, 0x22E4F13274775169ULL, 
            0xDA49CD750337F9BCULL, 0x9B2FE9A7286E875EULL, 0x69C100BA14D7B371ULL, 0xD883571E9EFEA725ULL, 
            0x534C844D04F0AC50ULL, 0xD4FAFA1E796B3512ULL, 0x6970FFBB41D0C32FULL, 0x37BD2552F5398A8DULL
        },
        {
            0x1679317B87A7FAA5ULL, 0x50843EC219C3ED5EULL, 0xA40BF51D4F8D9D91ULL, 0x22FA4DC8873A9119ULL, 
            0x92E0319DD15AEAD8ULL, 0x2A2C86E94D43EB9EULL, 0x4323B132C4FB8233ULL, 0xE398DF2F7EF4ECEFULL, 
            0x71EE63B221E655D0ULL, 0x9ADF5BB66E9FB1F4ULL, 0x564E10EC0918EA7BULL, 0x227D59DDBA59838BULL, 
            0xD89A59BE7CFE9DF9ULL, 0x7BA6A053392FFA81ULL, 0x5107164965635C91ULL, 0xC43F17B6D22AB2E1ULL, 
            0xAB2AA8E42D5686E8ULL, 0xA43B3BE5F9B16C18ULL, 0x50AE8AF408CDECCCULL, 0x13C5D8A00ECAC271ULL, 
            0x3AB65EBF7414B3BFULL, 0x026EDCCD62AB8B53ULL, 0x7B3E7A6AD05F2429ULL, 0x797AE66D2D71181DULL, 
            0xFC6DE07F7EF2E2A0ULL, 0x990585732B6C5BD4ULL, 0x68C4F808000C0249ULL, 0x3E12FD13145B8824ULL, 
            0x6DB1F0B1D15F7079ULL, 0x7095F4C58AADD5D8ULL, 0xA20D0655798DFB98ULL, 0xE5FC6762C49547E6ULL
        },
        {
            0x19C79E43713DE78CULL, 0xA0F9A4974B83D878ULL, 0x2241D703F5E9168CULL, 0xFEF8582928C99933ULL, 
            0x37269832E8DE46BCULL, 0xF92713762AB84C9AULL, 0xE7142A0CAA2ECCEEULL, 0xD3244EEB96776E6BULL, 
            0x74514F0756DB5D00ULL, 0xEAEE4F83079E35D4ULL, 0x5883BCD01286A40FULL, 0xA0F9B123C287C0C0ULL, 
            0x70706B5A58DE1120ULL, 0x0D1532B82D233A7EULL, 0x6CA135C628960B4DULL, 0x01BAF50F2387495BULL, 
            0x988035544D651DDAULL, 0x80F13C78DD80A063ULL, 0xF6D4D9274174DFE5ULL, 0xCF6CC46B4AAAB674ULL, 
            0x4910A8B937DF0338ULL, 0xAA008772C90321A4ULL, 0xDAA3E576776CF5C3ULL, 0x8D7F3CCF50122F39ULL, 
            0x1B96DA555E3BC05CULL, 0x6477C8A2B43D7CD9ULL, 0xD00143A1B4D2E451ULL, 0x7CB0AE73EE265174ULL, 
            0x3F2BD6F20EBF716DULL, 0x2F9C83CFDF9E5C21ULL, 0x827EC666AFEDCAACULL, 0x8B2E40DC79D6E985ULL
        },
        {
            0xCD674F49A3A2B5C3ULL, 0x35FDBE5F5A9AB6D3ULL, 0xFE936F56BB8E9602ULL, 0x29B8DD8D7BDD9C81ULL, 
            0x03037EB762D6BD7FULL, 0xBFAA4C49409E5B5AULL, 0x3AA6E68EA296DE65ULL, 0x129EAAB4C4D72368ULL, 
            0x7E8ABA1E2A2703D5ULL, 0xE4EA0A0EC48D5514ULL, 0x3E697B59DC5BEEA2ULL, 0x70D60A59F80CA1C9ULL, 
            0x6A509BAAF6B3BA6AULL, 0xB3A98851132BD824ULL, 0x3399FB150423316BULL, 0x6B42FE4498807976ULL, 
            0xAF327CD68AF17DF1ULL, 0xDA93FAB26F98BE79ULL, 0x2B76AF4B7D514929ULL, 0xFC55749ADB46EAC2ULL, 
            0x129729F6F98BA8B2ULL, 0x1BC66D3CB9AF45F8ULL, 0x348A7F9975E7DB39ULL, 0x3578D93F1087BF2AULL, 
            0xC9EDCCFAD6B41D78ULL, 0x697B8CA028EEA711ULL, 0xD015934A4AA0E2C3ULL, 0xBD9392AA7EBF9414ULL, 
            0x60E84D6ACC9E2C96ULL, 0x634C834BA2723F15ULL, 0x9EC4F0835D7574F6ULL, 0x56775251DEA237BFULL
        },
        {
            0xFEEB9067D0C20BE4ULL, 0xFBB056180B9D6DA2ULL, 0xFD3771A39E588186ULL, 0xD8CD2F96DF389079ULL, 
            0x6E15E17ACC9E0558ULL, 0xE7E96752E7068C95ULL, 0xE84EB9AFDE05583BULL, 0xA521CC300956EA3FULL, 
            0xEC22CDE5717596D7ULL, 0xEAC00F6232516EBBULL, 0xC2ACF2D820FE148BULL, 0xFF9E0FFABE74246FULL, 
            0xAFF9ADB32F6FEC89ULL, 0x6D879D50663182B4ULL, 0xC8F37EFAA5AC1549ULL, 0x3567A3F1A28FFD22ULL, 
            0x23BB4E7329E7261CULL, 0x1CAF19BD93E81042ULL, 0xC6F0401B1AE53067ULL, 0x4E5135748ECD581AULL, 
            0xB6253E5802B3AF9FULL, 0xBF8A91ACECC0402AULL, 0xCABC35002CDE9530ULL, 0x19A03DE16FAAFD60ULL, 
            0x4774CF65DBED8167ULL, 0x99688212F40883ABULL, 0xF29300DA78E85914ULL, 0xBF0449C1A56CBB5CULL, 
            0xFC5E9252725CDC0BULL, 0xDF94C287593DBC94ULL, 0xC006EBE655B455CEULL, 0x567A906722CDCFC2ULL
        }
    },
    {
        {
            0x4D8405881B4387F1ULL, 0x52636BE5DC467F84ULL, 0x5E0EAC05EDD94784ULL, 0x43F301210BDFF417ULL, 
            0x798A0AF655FBCA6BULL, 0x8A8859BA6B76FA8EULL, 0x1C69FADF67F8C7B1ULL, 0x2AD89DCB30091EB2ULL, 
            0xB0FF3AE02F502C74ULL, 0x5BBE214FC3A5B100ULL, 0x63A0CAB3C7686536ULL, 0x2C6596D198EB00D3ULL, 
            0x4EFB68178D6A6698ULL, 0xFB41BC97A147495CULL, 0xE507B43135DD7877ULL, 0x1587E13D0F7C4250ULL, 
            0xCD6384116415979EULL, 0x1935D9F56EE9D39EULL, 0x9C65FEAA5AC7C252ULL, 0x5E5828A441780287ULL, 
            0x076DCBDC973CEAD3ULL, 0xC202FCE417DA0C2AULL, 0x1BCDE19CD99CE846ULL, 0xB9C360E30AD54CE3ULL, 
            0xE0EB61F2FE4A07BCULL, 0x216AA85FA692531EULL, 0x3F3CDCFAB54941D7ULL, 0xEC02C4C2DBC87D63ULL, 
            0xC50D9F78DD53DB3DULL, 0xECBF94703844390AULL, 0xD46C67AEEF0F57E0ULL, 0x0C507FE7D4BE96F0ULL
        },
        {
            0x88C44503433BF345ULL, 0x650A0B277646E8E0ULL, 0xFE09005FCD4A910EULL, 0x819E00B666201D8AULL, 
            0xA4D0CB942674E776ULL, 0xDEC0C8657192D756ULL, 0xD40E83499366BEF1ULL, 0x4FB9248241AFFCB8ULL, 
            0xA818999FC4E50BE7ULL, 0xA52A8827496673D3ULL, 0x183302BBA3B329E7ULL, 0x1515990AC92C6ED7ULL, 
            0xEB135FC41EEFC5A3ULL, 0xD2E8A9C173E966B7ULL, 0x0D01941E1AE580B3ULL, 0xD7567CDFB133430DULL, 
            0xCFFD8BC4872C8E9EULL, 0x358E7F10B098C8A3ULL, 0xFC7891D0B5CB9012ULL, 0xE6C8575B274AB57BULL, 
            0x432B38CB1927F9ADULL, 0xE8F85C7DD33BEDB9ULL, 0x144D34AD4626504BULL, 0xE043F3FB0F2BFBD4ULL, 
            0x9A016E5500E4EB03ULL, 0x3A2DE8F21C73CA03ULL, 0x973DE58950942CC6ULL, 0xD4F7D8E88C9DF93BULL, 
            0x70F5B17CB847C664ULL, 0x4B44D4DA3DE4CEB8ULL, 0x0E43A7F6C4963B0BULL, 0x1C7A435438BB809BULL
        },
        {
            0x1131AA7A643A8733ULL, 0xC52C4FC11AE562B5ULL, 0xBA737118F7D472F6ULL, 0x4276720967CB3041ULL, 
            0x47E9038921C8B0B2ULL, 0xBCCF2120F7E6A85CULL, 0xED739B913A4C0F7BULL, 0x92C53A8158CCF0BEULL, 
            0x1759A8878F10C8AAULL, 0x5917048833AEF024ULL, 0x49A13BCF1125B894ULL, 0x049BD261FEC3078AULL, 
            0x9FED50281810446DULL, 0xBA82F58020812133ULL, 0x7445B9338A195BFCULL, 0x2905C1B55CC945CBULL, 
            0x7F97175FAC422D19ULL, 0xF3D2DC76B5AFB0C4ULL, 0x99A4A94A7A099052ULL, 0x9B5D0BEC2AA36787ULL, 
            0x8E6B4D58A455AA9BULL, 0x510D47D43F5D6E71ULL, 0xF073D1E9DD424B5AULL, 0x6F05DE474ABE0AAEULL, 
            0x33893137FCBBD7F0ULL, 0x7D32685A04A48461ULL, 0xDFC83F2C4687B6E7ULL, 0x2026662A41B39800ULL, 
            0x8F5EAFEA469C42B4ULL, 0x8192F99FD595EC65ULL, 0x559225B3E5B5C2BDULL, 0x1C9EC717BC50CDE8ULL
        },
        {
            0x1CDCAAB643FABB88ULL, 0x4B9395C8FD35AE90ULL, 0x5AC61861AB749ABAULL, 0x784A414FEB4ACB18ULL, 
            0x04C77B59A1E91C73ULL, 0xC83CD3B06FD7400CULL, 0xF871513572F235A6ULL, 0xE447E63E1C3FF2E0ULL, 
            0x54B49669CC5F1A69ULL, 0x1DEB3BC6D6AF492DULL, 0x49AD22EC1761C8C6ULL, 0xE801AEF56D260CA7ULL, 
            0xF5B804A7E14F28EBULL, 0xFFE660516C468659ULL, 0xFA92D208FD5C64C2ULL, 0x14CE5C51BF13E87EULL, 
            0x29F985EB9355A841ULL, 0xC47776598089D3EFULL, 0x99B965D333D50CEEULL, 0x261F7CC468D81811ULL, 
            0x2438AC5113FF5F8FULL, 0x3134BD7659FB2E39ULL, 0xCC858C5A6D4D39C5ULL, 0xAF79E05923095353ULL, 
            0x0BFB1F5347C5F55DULL, 0xFD1CFFB6FCF8A66FULL, 0x63A58B10C02E390FULL, 0x68BA1915826731FDULL, 
            0xDCDF712EDB659D16ULL, 0x548825D15BCD4027ULL, 0x775703F29DD274FCULL, 0x4AFB3885E56562DCULL
        },
        {
            0xAD078C4A55BE6798ULL, 0xFE36B090879A63EBULL, 0x507149C3D64DAE86ULL, 0xB330AADFC9901720ULL, 
            0x48ADB0B625F9798AULL, 0x4447E7592AA87791ULL, 0xF2250DFF59290867ULL, 0xEEC222BE64D8D02FULL, 
            0x37BC1DAA25856EBDULL, 0x2D91DD169C892CE0ULL, 0x9004DEA059B8C05CULL, 0x16444C290327555DULL, 
            0x2FBE5ECCD4F1A99FULL, 0x1D11EB14C11DD026ULL, 0x7838F288468BBEFDULL, 0x8E974E80C65439EEULL, 
            0xDB7E84881215C173ULL, 0xBA58807E0D0E636DULL, 0x2399645EF0416269ULL, 0x3413221D85A511C7ULL, 
            0x31F2A5389D4BC7A5ULL, 0x1BABD83CA4769A18ULL, 0x7EB26F58B099BA0FULL, 0xE537255DFC5AD742ULL, 
            0x6CB20C281E6ED2E8ULL, 0x141F257B221A86A7ULL, 0x7702B1FD2B3BC6E6ULL, 0x0E1A4F3DCAEE76FBULL, 
            0xFFB6D3C83BC874C4ULL, 0x48BFB3157EB7CC71ULL, 0xA922600E7417A9BFULL, 0x44689F73E346A7FBULL
        },
        {
            0xBFE1C3796B7814B6ULL, 0x1C4A0BB8312819B3ULL, 0x806A805C9AFB8CC5ULL, 0xC89B79CD63CC2776ULL, 
            0x9C77FE6CFB6E0DB0ULL, 0x15EEB9A1A01BA6EAULL, 0xF715C05478620B77ULL, 0x10883CBBBEDA62F0ULL, 
            0x312ED4E847455C77ULL, 0x51F9A1426288A3E8ULL, 0x73FF308BB8764EF0ULL, 0xD841B164354B6859ULL, 
            0x49C62CB58189FAAEULL, 0xCB006B53EE1A0F0DULL, 0x02AC75E12C9BC126ULL, 0x7EA2F7E504F25CD1ULL, 
            0x8DFCD226F57B77BBULL, 0x93278859089CCC6BULL, 0xBFAB1A0437C3E287ULL, 0xE42BC992777A9EFFULL, 
            0xA00BAF4B3934E3E4ULL, 0x6269F8D9F9FBABECULL, 0x3963E22CCABDFB44ULL, 0x5AA79EEF1C25F70FULL, 
            0xD58C205132FC6405ULL, 0x1A13B3ABA8CA25B1ULL, 0x39113C3E210438D4ULL, 0x4A48E116DE71C284ULL, 
            0x48F0ED50A27083C3ULL, 0xADF6E810E5242F73ULL, 0xF93F963A09B68FE1ULL, 0xB3C0757168416471ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseAConstants = {
    0x727BFD016C56DA9BULL,
    0x5869BE74FCF5AD3BULL,
    0xE3D6918CECF34200ULL,
    0x727BFD016C56DA9BULL,
    0x5869BE74FCF5AD3BULL,
    0xE3D6918CECF34200ULL,
    0xE62599A4224D4028ULL,
    0x043F417962C1438FULL,
    0xF2,
    0xA4,
    0xBD,
    0x16,
    0x3D,
    0xB3,
    0xB4,
    0x10
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseBSalts = {
    {
        {
            0x46ED6915938308F2ULL, 0x35DB12B35FD0C5BEULL, 0xF41319D989F24C96ULL, 0x7C17976671963241ULL, 
            0x8B0EE46031EA48ECULL, 0x249B34EB2BDD230AULL, 0xA9ED7E5E5D53A5C8ULL, 0x549C5B7C533F4C43ULL, 
            0x283C245A0FA40B93ULL, 0xF8D2FC161D92A690ULL, 0xE8A4E3FD40D3AFB5ULL, 0x50E80BB7D2853924ULL, 
            0x624C350C15244144ULL, 0xA41486A9A0067E10ULL, 0xDBFD59C7745485DEULL, 0x7A70C0911C4222CBULL, 
            0x9BF6B6252B43D77EULL, 0x42FDDE513A16376EULL, 0x7167FCA384ABA2B2ULL, 0x1B861B1BA838DCC6ULL, 
            0x36C0BCD35308FE80ULL, 0x14FB9D5AACB85CE2ULL, 0x098BF737F670B2C5ULL, 0x18E63BB4F5808204ULL, 
            0xBA2C8B00CA0E53F5ULL, 0xB2EEF51A9E1C6684ULL, 0xFFA94F300C7AC732ULL, 0x1DEE0D69E0422041ULL, 
            0xF84655B287577B88ULL, 0x9FB393CAC0F237ACULL, 0x9AF3D50923B05D48ULL, 0x624BE814B61B8758ULL
        },
        {
            0x6E3060D79EB4C520ULL, 0x240275C53E5EA472ULL, 0xB52E9A67A2E67ED5ULL, 0xDFED8A3F00BE0119ULL, 
            0xE8A2FF8023912208ULL, 0xC768C2F147871504ULL, 0x83677103C9C6914FULL, 0xFE21E013D7F391C9ULL, 
            0xA807961CB7B616ACULL, 0x3A4B79E2CDB3483EULL, 0x2A1CE4AF98A3FD33ULL, 0xE5122DF45428E527ULL, 
            0xCC867E062500F2DAULL, 0x15FD23C73CCEC780ULL, 0xE9D46224CFE2CDC8ULL, 0xFE5476A3986AD330ULL, 
            0x1752600A1047AD31ULL, 0x183DEFF2B6AA0CF1ULL, 0xEAECC86D744A22FAULL, 0xCE40FF511B365499ULL, 
            0x8309A192E63C10F0ULL, 0xCF9C08167A155446ULL, 0x3D4612A9EE143E24ULL, 0x92045096637455F8ULL, 
            0x5B11FF833511B5B6ULL, 0xCC76C757E53172F4ULL, 0xBFC7296BC147722DULL, 0xE3571944EEDEF2CCULL, 
            0xBA8526E538C1E9BDULL, 0x004A7E3594A25976ULL, 0xB90869846D8E7BF7ULL, 0xA2A69D7DFDDC7125ULL
        },
        {
            0xEAA6C3AC7B5C77B6ULL, 0x0007CA8878E05366ULL, 0x30A568B60E592C8BULL, 0x7997AAF40BE39061ULL, 
            0x17E6E0BA24006234ULL, 0x1DDED9A4ADAE6F78ULL, 0x126C87C9FCD35725ULL, 0xCDF3E3FAE040DF12ULL, 
            0x4A94C83C010C911EULL, 0x41B194E00FE41751ULL, 0xF9B5EE99472E9E3FULL, 0x792AF12F4637CFD3ULL, 
            0x6DB939AE39F12A2EULL, 0xF81CDA8A6BDA6421ULL, 0xE6C2BBB9D8F8F3EAULL, 0xCE010248D1F96394ULL, 
            0x303B72C14653532AULL, 0x9BFA16B7A099C5FDULL, 0xEA8B7F1CDCEFC0A7ULL, 0x8C56A3FE1F2B858DULL, 
            0xC7FB468D74804016ULL, 0x134E0171E643BF27ULL, 0xF320F7C66D1265D5ULL, 0xBD562361AE949415ULL, 
            0x204A7CF5B0E7A643ULL, 0x60E4E67515B44B30ULL, 0x6F506BA3EDA68FD6ULL, 0xA2E83659BDE5945BULL, 
            0xA4D760FB4AF70530ULL, 0xACB4C2BC736971ABULL, 0x352DD12D7F9A19F1ULL, 0xA42D2D50186A0DF6ULL
        },
        {
            0xE44DDEEC9A7CFB24ULL, 0xA8DFB38A60F3F48DULL, 0x336DBC5C81CFFC31ULL, 0xC5A1D00A44F8B64CULL, 
            0x56074E5414078C7DULL, 0x2484A1F7014E0444ULL, 0x16B9C18017209E15ULL, 0x3A6B535EF8C3F353ULL, 
            0xB88EF8090B7BA7A3ULL, 0xC642B3F55E229448ULL, 0xBC07C608E3C5FD02ULL, 0xB163941DD368B638ULL, 
            0xB2D9DFEF8025A873ULL, 0xD211ED8D796EE8EEULL, 0x4436B64FAB8CE11FULL, 0x267B944CDB9C1C13ULL, 
            0x50B0D9E6BA77A3D6ULL, 0x12F15FBF2C3BBFC3ULL, 0x560A7C655868787EULL, 0xAFF231514856132AULL, 
            0x83A1BF58FADA3007ULL, 0xF7ECF20DAC5F416CULL, 0xED77A1810E0C4DCAULL, 0xE662174AF23C2DB6ULL, 
            0x71E78F74D6B85964ULL, 0xE78980F251FB6DE4ULL, 0xAEA4A408181F7807ULL, 0xD5BB3216ECD738BAULL, 
            0x6227D8E164965BD2ULL, 0x4D65579AB17DF15CULL, 0x04E9BA3C8F552ACAULL, 0xE9DCB698414A59F1ULL
        },
        {
            0xCF63412D4ABDECF8ULL, 0x5BD5D8DA695253DFULL, 0x6523B32B5618F394ULL, 0xA4ECBD8B9890F7A5ULL, 
            0x564874039EF39928ULL, 0x4CDBA1DED5A43A56ULL, 0x07DC32887BE45E65ULL, 0x5A59C4FF1FCF4E09ULL, 
            0x47DFC66DAF7B4227ULL, 0xC7B5D8C9D9EA777EULL, 0x1B3ADDA7D5C04B26ULL, 0xBB9C4D11A77AC838ULL, 
            0x7B49B1731DDE625CULL, 0x492D96191F5C3793ULL, 0x111E8E340EAE8C1FULL, 0xC3E6301115B8D74CULL, 
            0x808CF6972922DD3AULL, 0xA2907D53C6FC8C97ULL, 0xCA06CCFC41DFF48AULL, 0xB369B143EAB7F532ULL, 
            0xC6ABFCD0C7E2196AULL, 0x2C7F6697E58344CEULL, 0x998C894B85776B59ULL, 0x1C51D099783A6341ULL, 
            0x3C2A571DFC9C50EAULL, 0x540FD70A2CA81C20ULL, 0x6A828EF93BE270C2ULL, 0x7A585375F96174B7ULL, 
            0xAA670D45368D3066ULL, 0x16EBE0B1B25C9D05ULL, 0xDD0653CBDC2460B4ULL, 0x92902BAF06DC2E22ULL
        },
        {
            0x9352760607A0C929ULL, 0xAB5D557868C38F77ULL, 0xCFD41A070A24F46FULL, 0x5A07C185A3E8CE31ULL, 
            0xE42BA268E7F19413ULL, 0xA4745F26FCE52C2DULL, 0x889C5D5051E530D4ULL, 0x4B52A0B005C0E874ULL, 
            0xE58280C4789BB481ULL, 0x9ED36A1F1DADF29FULL, 0x0363C6A1C838719AULL, 0x3C2F5B5C5567F284ULL, 
            0xB9E32FE8EB69E800ULL, 0xA2CAA6146A7355B2ULL, 0x5FBD3D118468C2B9ULL, 0x989A46F8BFD97EE0ULL, 
            0x3D3D48C934C4F6EBULL, 0xF4E1DB919E2509BBULL, 0xB182F1AB1F59DF0EULL, 0x7CF810E22E1C20C8ULL, 
            0xD518DD7E0E0A339DULL, 0xA42FE82AF96B655CULL, 0xC3F60EA1330DEB37ULL, 0x0ECB0B0587434313ULL, 
            0x6A93D81C66A5DC44ULL, 0x03D3BB20E6F58D0CULL, 0x17AD16A2435DFA5CULL, 0x61525C8A40C4CF21ULL, 
            0x418858679C1B21BCULL, 0xE31EE93B753C43C0ULL, 0xAB0261194442EEE4ULL, 0x73A4238FE4339CA3ULL
        }
    },
    {
        {
            0x3F8B4911DB1DB41EULL, 0x36A05B8821BD054AULL, 0xAA7F6885C959FE9FULL, 0x5DBFC3389F14C441ULL, 
            0xF95685E57BB17A38ULL, 0x7EA82E0637CD664BULL, 0x37CBC84D983CD4F0ULL, 0xB3E20E551E38676EULL, 
            0x4E1724513F972977ULL, 0x95AF72F786F43D56ULL, 0xD5847947EA0945A9ULL, 0x9B1A26B3F046A90AULL, 
            0x6F6FC42462CCFE4BULL, 0xAFB964A682D9CBE0ULL, 0x267B9DB1A3DB087BULL, 0xEDDAB043F2ECC611ULL, 
            0x25A5D8F18A72218FULL, 0x1F6AC7A49E634A0EULL, 0x72BC805B0BAD4810ULL, 0xE0A3B5F9BC907118ULL, 
            0x90B94CA701CC7A90ULL, 0x8B7AA5DF83446B44ULL, 0xEF7A0F61571F8F3FULL, 0x1178B13766120CF0ULL, 
            0x12323D0CAF66832AULL, 0xFB43BAFAF7F11277ULL, 0x054A66B26267C31AULL, 0x03FD2C3918969BA5ULL, 
            0xB88C57165A13A002ULL, 0x5941807EE04ED1EAULL, 0x0FF4F68BD1B261B2ULL, 0x80323B694EE59E5AULL
        },
        {
            0x46A0BF7F89D94F14ULL, 0x92CC16777F4E6BA6ULL, 0xF1D4065FE0C8EA91ULL, 0x39D420C0AFF15F2FULL, 
            0xD4BDFCEE39538769ULL, 0x29B19099A1167F57ULL, 0x58FE96672A9EBBEDULL, 0xDD3C7B5F73B1DAFBULL, 
            0x1839AE669769E702ULL, 0xC2C5A8BCA46A986DULL, 0x74410C1A9C8412D3ULL, 0x1B00CC555142B5D1ULL, 
            0x8DD9FFBA8CDBE553ULL, 0x60313BBB97E53727ULL, 0x380975EF5282D692ULL, 0x2D9C7EC56744DF0BULL, 
            0xE5FF7E77871CDC85ULL, 0xD6BE6D85D324D1A5ULL, 0xD937A0EB97587040ULL, 0xD6E5B9751811D1CCULL, 
            0x3CCEFF6EDFBFF333ULL, 0x9672FE5158F4286AULL, 0xB8A479053D69269DULL, 0xE02FA81E0B07ED5DULL, 
            0xFAE5C24D10B124DAULL, 0x6EFDD6701122D44EULL, 0xD7919DC4A0109BB9ULL, 0x6DFC5A38CD3E8777ULL, 
            0x706826B7914BF88BULL, 0x6317AB0556232126ULL, 0xD1CFAA6E2234971BULL, 0x92AE2F8BF949B4A6ULL
        },
        {
            0xAD7887464CAAF21FULL, 0x1ECF16B0FFF608B8ULL, 0x0F1F5B0375C84572ULL, 0x025E075551FC69FEULL, 
            0x15F21D82E4AF19A2ULL, 0xB1BFE6A956F116D2ULL, 0x5FEF956F217A7A92ULL, 0xA1DC0FCED32CD9CCULL, 
            0x81F728A325F43B14ULL, 0x64B5F37F1D869CD5ULL, 0x408BE5331AB6FEB3ULL, 0x05005D41D4069BF1ULL, 
            0x4BDD429DA9BF09FEULL, 0x53C1611C5B221DE1ULL, 0x090B38436C709A81ULL, 0xA8AB10C7FF750810ULL, 
            0x745DB0F444C4604DULL, 0x59F8759498C1ADE4ULL, 0x9DB91468F871E3A0ULL, 0x433DF5A184749AE4ULL, 
            0xACF971004314928EULL, 0x1D71147827145567ULL, 0xE8AE398EB351A67FULL, 0x14EE9D3EF8BD0C2AULL, 
            0x90C235537E84E32FULL, 0xC92837A23B1F7F38ULL, 0x425814E633513720ULL, 0x9CFF2429FEEE964DULL, 
            0x8057AD71A0C3567CULL, 0x934E487E72C377C1ULL, 0xB70A7CE8A4B52075ULL, 0xAA0A1832B0781E68ULL
        },
        {
            0x1B90C4F1D61DAC14ULL, 0xFA3F34DF25BC4D41ULL, 0xE218F57274AFE6D2ULL, 0xD672FA9E92263087ULL, 
            0xAD23BC0B817653FEULL, 0x44620BD2BF809FB2ULL, 0x1B9893E539CD444CULL, 0x387DA92A9DE23C68ULL, 
            0x5466A84F812652CEULL, 0xEE21C0FA04C410B2ULL, 0xCA8731A8F4CFB41BULL, 0x79D8C97AAA4AC18DULL, 
            0x921C885746DADE1EULL, 0x0C0A5A15E1FDD158ULL, 0x2CFF78207EE6C52DULL, 0x755016F0462EB4EAULL, 
            0xEB8C7654530976F5ULL, 0x4E755AD4CE0B9813ULL, 0xBE5D318D6E22CD8DULL, 0xC4328B4F6A58013DULL, 
            0x6159775252213B14ULL, 0x34B2DF7CEBB3DB84ULL, 0x4155DB08D0AC7B77ULL, 0xA5C89E1DADA907E0ULL, 
            0x9F34D5A9A868E9CEULL, 0xCED5BB971801CEFFULL, 0x6741D9D42572281DULL, 0x3905B9C37E205079ULL, 
            0xFB77047521C54ED8ULL, 0xAA73559A85E6F4FFULL, 0xC90208698C9CAD95ULL, 0xDD2A0A5437E9B85EULL
        },
        {
            0xB5035C275E7493C8ULL, 0xD27EF87440535C6BULL, 0x5AA426FAFD98C62BULL, 0xDB302B9D6844E948ULL, 
            0xEC33BF9ED7364848ULL, 0xE8CE53830900BA64ULL, 0x88C3FA3B90AF5EC5ULL, 0xF67B93E0ED53AFC5ULL, 
            0xF184A66EC368162BULL, 0xC7F0310EB2BA66ADULL, 0x4645531F44A77CA3ULL, 0xD28088F1981F948BULL, 
            0xA53CEA5B659AF996ULL, 0xF116335F3DD4F3F8ULL, 0x2CA8C764592FB59EULL, 0x04A01AF597C2E629ULL, 
            0x4FEC31A8D587874EULL, 0xA20CA8D5C0517EEEULL, 0xCCFACA2E0A652F3AULL, 0x5C17B7C3C19F3BA7ULL, 
            0xD350C0A4CDAFC32CULL, 0x0A04F16E64A16490ULL, 0xD568492F234AB1EDULL, 0x8F2109D132A0D36EULL, 
            0xF90C89A0F75E5A34ULL, 0x83CA0E52F721EF35ULL, 0x9CECC9B60A57F595ULL, 0x2ADD122CD62F794AULL, 
            0xADDF5FE46A7EDC1DULL, 0x10CABA1AE78A9E46ULL, 0xAD77ECCB42784BEFULL, 0xA27FA683D809636EULL
        },
        {
            0x96E2410CC2DAED53ULL, 0xAC72388C2CB058ECULL, 0x64623B76698BD6D3ULL, 0x304A10A985669E13ULL, 
            0xF212E88C89DD743DULL, 0x20CFDD93B51B9767ULL, 0x6958E5916238C969ULL, 0x30D1E93B09AA2079ULL, 
            0xBA618C7523B982A6ULL, 0x8188C0BBEE167C14ULL, 0x5385EDAEAF54F29FULL, 0x96FBFC6046AFC13DULL, 
            0xA25FFBEE1AFFACF2ULL, 0x6156C7ADF02121ABULL, 0x0AAEFEB852D58200ULL, 0xE64281B0457BF174ULL, 
            0x79A4E7EF74D31168ULL, 0x0F53A26136D65E5BULL, 0x9AA968BE63638DB1ULL, 0x7683314257FCA501ULL, 
            0x4A89134E5895E17BULL, 0x747F6B778E64DF9FULL, 0xCB5A037947B66B7AULL, 0xEA429EED3E41BFB2ULL, 
            0xE82B0C68AE5344E1ULL, 0x1DE4BEBD6D529764ULL, 0xCCD635F37A1E23E0ULL, 0x278690BA79A1489AULL, 
            0x26BB76875384175CULL, 0x79213B7A5B8294D0ULL, 0x2F9DDEFB524752D1ULL, 0x7840F1A43BD60674ULL
        }
    },
    {
        {
            0xF0645871DE764F30ULL, 0x8F1A1356D599B8C7ULL, 0x7DF0FAC968F3C722ULL, 0x84A5AF70E3E0B4B9ULL, 
            0xB60407716137D200ULL, 0xD0633E1A7A6B473CULL, 0x10F2F89A2C3C5B0BULL, 0xFA30306580EC10FEULL, 
            0x7C72AD5A4D5C7EC6ULL, 0x03F26C216EF6D596ULL, 0xF645C06E2F65C371ULL, 0x1BDA15022F800C9EULL, 
            0xFA88E7787B177B12ULL, 0xFD291F40FB99335AULL, 0x11DD8250CF4D08CDULL, 0x884EDA2847256F27ULL, 
            0x70CA9F8525F5B50AULL, 0xDFDBBF2F54875258ULL, 0x88F89261F414C93FULL, 0x66D85CAFBA76AAFFULL, 
            0x1D749301DE19A1C2ULL, 0xCD6F6D69711E0FD4ULL, 0xFBA8A1BF597E4868ULL, 0x3681173EBB14B975ULL, 
            0x9A31FBE8CCA89775ULL, 0x49EB9B127380CF90ULL, 0xE61C947CFA52F533ULL, 0x07506FD6FDCC5CF3ULL, 
            0x382042022133F185ULL, 0xCB63EC3C54FB6265ULL, 0x0D06AAC1C72E7F05ULL, 0x421FFD0326A1181FULL
        },
        {
            0xB96D8B4DD245F341ULL, 0x683A0EFFAE3FD27BULL, 0xA45B1A59E3C75294ULL, 0xDF75EF2F261FB352ULL, 
            0xCFE8C10CC903FA86ULL, 0x1898228DB56F5324ULL, 0x222451F9857CFEC6ULL, 0xD55DC501A0994CB7ULL, 
            0x4E03D8C16CBF3A12ULL, 0x1A4305A90BC4000DULL, 0x4F1E4D9BA64B9860ULL, 0xD693E79EB9609F9CULL, 
            0x316D52E9BBAF0276ULL, 0x1EE7427BAB7EAEEEULL, 0xD7E845B6880DCFE5ULL, 0xB2DDBF3CC800A6C2ULL, 
            0xE4E333580D790A8CULL, 0x1AF8B5560A89DF91ULL, 0x4198C1D86DF34B17ULL, 0xB0B90FE7B92B8C77ULL, 
            0xBE0BF8A989C69BC3ULL, 0xE37D2FB9C3061819ULL, 0x62FFE98A95B57AE9ULL, 0x76B7AC5B39D7D099ULL, 
            0x35BA09B2959B8437ULL, 0xE3427A4C9455BA85ULL, 0x5E80A834204E27A5ULL, 0x02ED05B12A45E5BCULL, 
            0x3A595186E94B91C8ULL, 0xCBF9964432F2AEC1ULL, 0x8BFF62D01E5A6FA9ULL, 0xF55E0E0EAA53B8A5ULL
        },
        {
            0xF3AD5B93674D617BULL, 0x76F460963CF0B018ULL, 0x5D303F958B0D4822ULL, 0x6CCE19230EFD52D5ULL, 
            0x6E46121EFAD85B25ULL, 0x33C18371E089445AULL, 0xB19D6D5E2ABDCE2FULL, 0x7329C5456D8C87FCULL, 
            0x5FA4A2810308B387ULL, 0xE102EC97371278CFULL, 0x86E73C0BA951B2C2ULL, 0x61CAE1938E219EEDULL, 
            0x2FCD3D7228B882D9ULL, 0xBD380A289EEB8873ULL, 0x6F61E8AAC1270799ULL, 0xC00EA35DC77C0223ULL, 
            0x1A13A2C7C902D048ULL, 0x9F08BC6479704D52ULL, 0xDB25EB7B5ED925DCULL, 0x6EF878CEB6DFFD9AULL, 
            0xD6B7E81208252882ULL, 0xFE173B0B2652A881ULL, 0x76F92748B2E7935FULL, 0xFD0D939BA33964A4ULL, 
            0xBC97F702D35CCA84ULL, 0x77D477BC0CEE09EAULL, 0x8548399A31223D31ULL, 0x5B20B6D33D10C6BEULL, 
            0xA88AC1171DB2313FULL, 0xE2D0B83BD68EB841ULL, 0xE91ED1B274A71399ULL, 0x35E9ACA095A933D1ULL
        },
        {
            0xD4E8334434B156FEULL, 0x70EE2262C8F683FDULL, 0x1615B9A6472E07F3ULL, 0x0D7E15B6214AE515ULL, 
            0xA9B64D477E5CC61CULL, 0x0303064EF72D3F4AULL, 0x867CDA5CE7980F2AULL, 0x8452D643EC7504DEULL, 
            0xD7A8705F9C9CE713ULL, 0x3CFA3A888CB4D921ULL, 0x8A1C4E3317FB831CULL, 0xC9667458006B45F8ULL, 
            0xEC0A20782201492FULL, 0x1C00B78FF7D75562ULL, 0x11F47BC38A74B4AFULL, 0x8BCFB6E48DC3CF24ULL, 
            0xF1D0E3992151C4BFULL, 0xB1AD12B309F9E94BULL, 0xD4A72D8EF8B30CC6ULL, 0x0241B12905389565ULL, 
            0x3682CC4BF9EEB405ULL, 0x0F6957D3416FA4A2ULL, 0xA5E0C909B9CD4CFFULL, 0x526EFF2B04A40B66ULL, 
            0xED043977B65F487BULL, 0xBEA1BBE151B5EC9BULL, 0x2D38CB5E630BCEB8ULL, 0xBAE6682B08D9FDD1ULL, 
            0x7EAA8FFE7C7B3E46ULL, 0x3E1CFF3508BBD608ULL, 0xF82CBCE1099248F2ULL, 0x587247BF88B839BCULL
        },
        {
            0x049905116C30B17FULL, 0x3392E45BA54E9853ULL, 0x3E4B417509C1E508ULL, 0xC62B83155D56A9A4ULL, 
            0xCFD4DBB9E182C52EULL, 0xAF14F12452E6C4DEULL, 0x89F81134E621DDBFULL, 0x112B02DBCA90811AULL, 
            0x223896201795C7B2ULL, 0xBE0BB17B181003FBULL, 0x77D9F6849ECF2FDAULL, 0xE15BEA1401246F0FULL, 
            0x724CAFAD7E8E208FULL, 0x46DB1DC7EB2AD6AEULL, 0xA49852182C6431ABULL, 0x941E984722EAF0C2ULL, 
            0x36FDB28B7D5B19CBULL, 0x3386F2B831C1B303ULL, 0x6174025EE42593CCULL, 0x69273D8CB56EEF40ULL, 
            0x963576CE334443BDULL, 0xEF66DCB8C709CB58ULL, 0xCD84001A1C23D2FFULL, 0x0D5BFFBD5B859D24ULL, 
            0x91A0CFFA8567E4CCULL, 0x25E28E5DA8F64C03ULL, 0x17D0F30521A72501ULL, 0x4C0EE7ADB989C5EFULL, 
            0x9F1A3B3D23CD88BDULL, 0x4D88C26FDC8D71CEULL, 0xBB4A09129C3C8BA9ULL, 0x682222F76C0ED496ULL
        },
        {
            0x79681A0BD01D4C84ULL, 0x67AF43E8FA14C781ULL, 0x8AC987151C800282ULL, 0x05A8C0A827DE3FBDULL, 
            0xBBDEB5C4A63016B9ULL, 0x2DCE210A7FDDB6E0ULL, 0xB5902650BF7CEFD5ULL, 0x692B79CE1D94D639ULL, 
            0x9362E4161CC4DBF2ULL, 0xF44E43E715BF9826ULL, 0x26DEEF5AB5A6443AULL, 0x73EBD6141F5E08E6ULL, 
            0xE42A207E28981357ULL, 0xF35B4C6F3FF8DA8CULL, 0x314956BC53788F28ULL, 0xF4B90C63E1791520ULL, 
            0x536D719119C97455ULL, 0x799D25032E63935EULL, 0x0DBD857589B46493ULL, 0x60FA603408C397DCULL, 
            0x877B620E08C78793ULL, 0x997B14E0C76CEE2AULL, 0x4CD3F121B2A78064ULL, 0x086122AD12F4DB17ULL, 
            0x2693083E5FF9ABF2ULL, 0x15887AFBD8E83CDEULL, 0xC9801E9B4E7AB21EULL, 0x247D78EAC550B535ULL, 
            0x8494EA3A7279621AULL, 0xE47B9C287A33B85FULL, 0x8911FE47033756F3ULL, 0xA930E3185FC768A8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseBConstants = {
    0xBF528AF7B6110238ULL,
    0x41BFF4D5BF768B24ULL,
    0xB0A8B017612A0F85ULL,
    0xBF528AF7B6110238ULL,
    0x41BFF4D5BF768B24ULL,
    0xB0A8B017612A0F85ULL,
    0xB030B9B96FA437CCULL,
    0x4F8B80A8AB16386EULL,
    0xE1,
    0xFD,
    0x20,
    0xEB,
    0xB3,
    0xE1,
    0xB1,
    0x46
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseCSalts = {
    {
        {
            0x9DE5009EFA340AEBULL, 0x08F2B6CE95947B0AULL, 0x618125BA481158E0ULL, 0xB3C414776C9624B5ULL, 
            0x092A8EC2A814AA49ULL, 0x0E294A6529BE7D0EULL, 0x5F0B45756E9CDEF2ULL, 0x2D30276DA85B45AEULL, 
            0xACAB1970F569F2CBULL, 0x9B665E8C401BDAF9ULL, 0x69B7E14E3F894B30ULL, 0x9DAF53D89B91CDFBULL, 
            0xA415202BF28E1C1FULL, 0x52C445CF649543C0ULL, 0xAC9BECDF45551A21ULL, 0x87410C0F4E3CE005ULL, 
            0xC7D36977F5C4C69AULL, 0x163A3B0FCF85736AULL, 0x8C3FB6BF2C6DA7F7ULL, 0x76662C2214E0B81AULL, 
            0x2BE8E20E44D65DB2ULL, 0x808A440049FF8AFDULL, 0x39162011904D96BBULL, 0xC762BE3E5416FCC2ULL, 
            0x2906830A8EC7E8FFULL, 0xE233E26FCDA0AE58ULL, 0x2A7E5C0F32538BEBULL, 0x139A6C73057F6C79ULL, 
            0x194D9B9FC512B6E3ULL, 0x1DF958D2D4454F04ULL, 0x7D08115F33ECA926ULL, 0xEA5C775F75557845ULL
        },
        {
            0x62A695F721D1ECE9ULL, 0x68135643628220F8ULL, 0x8836BC19CF910F76ULL, 0x4E97852ABDCA5552ULL, 
            0x1752416B4E9147D5ULL, 0x0ECBD08B0FC0B507ULL, 0x2D862BC3A9D13A03ULL, 0x9BA38D85436D04E9ULL, 
            0xBFEF7E4F3D994BA5ULL, 0x6E51A8EB20B506E4ULL, 0x1804FBDBD1D92D23ULL, 0x358012EBF14ADFD9ULL, 
            0x1ED870E7FF53E325ULL, 0x510F23FA7714888AULL, 0xBA534B9877293EB7ULL, 0xA5B244931F988ABEULL, 
            0x620B98C70290F85FULL, 0x558E126B23AF95D4ULL, 0x369CBAF4A3993633ULL, 0x7E99AE082106AACAULL, 
            0xB839601274407C0FULL, 0x12D7BA73E688B58EULL, 0x3EACFC81B521282BULL, 0xB6E050FE2621FBF9ULL, 
            0x470559CFA81FF000ULL, 0x0F1C5CBFE2AB6FEBULL, 0x2D204EC6163E6025ULL, 0xE4F63C74E0FC8A90ULL, 
            0xA08A3FCC1E19C117ULL, 0x4684E5381F96F7A6ULL, 0xCA5EC3AF9ECCF5D7ULL, 0x0232ED6F293EFC2AULL
        },
        {
            0xB98A8771D7B689FBULL, 0x7F2388290D00B736ULL, 0x6A9986B81CB83150ULL, 0x1F5A4E44841FDF53ULL, 
            0x9FFA71EE7748D3B0ULL, 0x60F8DB0D6B4C029CULL, 0xE5F7A211B5756500ULL, 0x1603228BA8B8361DULL, 
            0x6DED21E86A7127CCULL, 0x00A0EF409AD2F101ULL, 0xF5EF1E1F5B33BD89ULL, 0xFD183046905E18B0ULL, 
            0x5C0D20965FF32D33ULL, 0x5AC17B79C2E0E5E1ULL, 0x15E0B9034AC70BE7ULL, 0x083789D10B6426BFULL, 
            0xDB92A575850EF319ULL, 0x4FE5EAB72F150FF6ULL, 0x0D60D058EBBF58CBULL, 0xB131999167C88C71ULL, 
            0xA93BF2188E57EF5BULL, 0xDF415DE33A9BFA75ULL, 0xA28143FC460FC945ULL, 0x37B84C13F9E9C005ULL, 
            0x2077A24753A01511ULL, 0x798068BBCEAA32BAULL, 0x29A9255A7B37E771ULL, 0x3A2BA9A9EEA04547ULL, 
            0xA474BAB0C25BD448ULL, 0x574E51386DC3E7B9ULL, 0x64839A8CC9157A23ULL, 0x3479FF3E67D18142ULL
        },
        {
            0xB50BFAB873F37C2EULL, 0xDDA0CBDDB0DF49CFULL, 0xF98EF9F75635D352ULL, 0xD80A9806E3577907ULL, 
            0xD470C41D1E8E836BULL, 0x6B81BDE89535C4A2ULL, 0x22211660DE7E8323ULL, 0x68FBB3C61A8E8A9CULL, 
            0x70D4A2681CA40486ULL, 0x3B12ACACB2FAC0F1ULL, 0x810356FFC5C02429ULL, 0xA48449BE70C26172ULL, 
            0xE973881045B94109ULL, 0x223728B0629A9F4EULL, 0xF5F774AFE81C116BULL, 0xABB016EACC639143ULL, 
            0x1AD72964BF7D60D5ULL, 0x8243C7CD6ADE7A52ULL, 0x608BBD2C971BED1FULL, 0x187974975D9508B9ULL, 
            0x480BE23BCBDC7CBFULL, 0xD59B2861EB97AF94ULL, 0x768DFF593E67A625ULL, 0xC29120DDE36763A2ULL, 
            0x09451C36CD890E04ULL, 0x7DF5918F1BA51242ULL, 0xAC7DA3B4618AE37BULL, 0x959AED0C6DB6901FULL, 
            0x0E721DE3E6EB39C9ULL, 0x745B45AB9617E45DULL, 0xCF1041079B6235F9ULL, 0x781EA30DEFCD617CULL
        },
        {
            0xE36E687B4E7BD430ULL, 0xCF44B8CC1AFEE3B0ULL, 0x7CA2A00F12B6244AULL, 0xD7FB0CE44CA30A01ULL, 
            0xCDB1ECDDA670C90DULL, 0x462DCEDA204CC630ULL, 0x1EFC6D48C42FCF6FULL, 0xB101275C30C9FF8EULL, 
            0x7BC67E6770918B33ULL, 0x1E07F52D61E028D2ULL, 0xF932E8BA8D2FEFA7ULL, 0x29CD0DC73C43C7E0ULL, 
            0x57F56F684BFC21E0ULL, 0xC2E53BFFC358E352ULL, 0xEB4E6BDE719DBDF3ULL, 0xC912F5488A27EF86ULL, 
            0x81EEF45A0CB7B20CULL, 0x36D7718E94C0A541ULL, 0xDD4683CCE94DD688ULL, 0xFBAE2C36FE8F24E1ULL, 
            0x8343E2BBE957EA52ULL, 0x1D606834E0084C12ULL, 0x0560D9D13D32D5B4ULL, 0x7DFDC0A6B49B8410ULL, 
            0x390EFBE251EB8709ULL, 0x136CB24AAF91519EULL, 0x4FEDA49196CA3D0BULL, 0x4572D9EF7ACB79F9ULL, 
            0x6093988627EA4586ULL, 0xDD3CFA19EA2869AAULL, 0x6066CE6ED06BD0C5ULL, 0x720EA8FFE5914D6CULL
        },
        {
            0x8888840F1D8651B0ULL, 0xB0C2501E34254D8AULL, 0x2A52A1A4C8208CA4ULL, 0xF78394418ECC451CULL, 
            0xB6E516B0E57472CBULL, 0x90D8749712FA081BULL, 0xD46B386EFC07E104ULL, 0xCAA214F4822154EBULL, 
            0x6346920B78D138A3ULL, 0x7C5A0CAFAF50CBECULL, 0x996671D0B999AED5ULL, 0x8E3B4237876B643DULL, 
            0xC29858EDB38F6D18ULL, 0x19D76BF89FE95442ULL, 0x0A5EA7CBD568A655ULL, 0x2D3CF53A514370A4ULL, 
            0x874FB39BBF8E337CULL, 0xC6D34D6EED774955ULL, 0xFFC7E51B92F8670BULL, 0xA379674A22C2C5E7ULL, 
            0x4925DB2DAEDBB620ULL, 0x64D5D789624468E6ULL, 0xE3D94B306115C6B1ULL, 0xE2F43B571679ED58ULL, 
            0x09361DD2043B4DAFULL, 0x45D4BA05249062D8ULL, 0x665EF74B75387692ULL, 0x24735B058DC07FDFULL, 
            0x5C82157047F4CF39ULL, 0x83FD7E9899889C35ULL, 0x9D06A0F2EAD38FD3ULL, 0x1E5B0E67D6D986DFULL
        }
    },
    {
        {
            0xE21BB9F0BB7EA786ULL, 0x8BFAB92BC43AB1DDULL, 0x88ACC267C200BFFAULL, 0x2067D951A1F1A7BBULL, 
            0x2ABEE5F4CFA5E97FULL, 0xD18335A20E02B61FULL, 0x35C158B381B2C7ECULL, 0x51884782CA97A273ULL, 
            0x9ACE32D9CFB16FADULL, 0x5D46341A626F0C70ULL, 0x9FE1E9F679FEC96DULL, 0x9D014CF7403A4B9BULL, 
            0xB055C15C276C9B8EULL, 0x6231A2E862CEF58BULL, 0xC040454D26ABC114ULL, 0x58CE27BE8AD3A948ULL, 
            0x546B691CF42F7306ULL, 0xC015F8EDF85FB85CULL, 0x6AF8EA6E86EC650BULL, 0xAC6FDF6CB8B12BEAULL, 
            0xBC693246834BC2DFULL, 0x852390E4D55BFCC2ULL, 0x6E59CCA607838CD2ULL, 0x62A46F008F3F8026ULL, 
            0xD6B7355442F304C7ULL, 0x5A692B24E7F0DB6DULL, 0x250F75DBE65B753DULL, 0x912BC425C06879D7ULL, 
            0x1B6E00DB2013A5CFULL, 0x8C9867A7A09084ECULL, 0x8EE748264CED7B99ULL, 0xE2A8785D10B6BFC4ULL
        },
        {
            0xDF3941162FC86265ULL, 0x9FD128E5DA8AAE5FULL, 0xCBE6E697ECEC90EEULL, 0x2A3B011B901C4857ULL, 
            0x5A2A00ED614FC10CULL, 0xB7C8E2194ED4DC93ULL, 0x8F77614C7CD6BA86ULL, 0xAED72103D08C705EULL, 
            0x203D5407778DE1A5ULL, 0x702D2D0F4BC4081AULL, 0xAAA635181D1BE1E8ULL, 0xE526F0625AADAB55ULL, 
            0x50EBABCFD7BA8ABCULL, 0xFCE5C312AB72D16AULL, 0xA4FF13C428A7FC73ULL, 0xC2DA23051A6140C3ULL, 
            0x052DA7A175CECADAULL, 0xD1558DE5456215ABULL, 0xEFB230A7A84227C2ULL, 0xFCDA623D9867F577ULL, 
            0x2CED2503E120D22DULL, 0x868B086634C23200ULL, 0x88BB41BC60311A17ULL, 0x0B651DCEBCA83027ULL, 
            0x37EF5C42CE4F8D7BULL, 0x63623C0AC386C78AULL, 0xD437F1641759E015ULL, 0xCA895B5D2B24C0DCULL, 
            0xBDAFDE7C17A1C97FULL, 0x1E9178BE8783EDC0ULL, 0x87F195A9FDE343E8ULL, 0x534E9B0D93DA6DFCULL
        },
        {
            0xF6F57CD757403050ULL, 0x2E8F811C2A1A6328ULL, 0x35869DF6C9650A7AULL, 0xBCBB898BD64FE779ULL, 
            0x4DDD09C9F31375CBULL, 0xEE62434917BEFD7CULL, 0x27268457499521C5ULL, 0x5D0549BD1D2C64F2ULL, 
            0x44763F7327749A1CULL, 0x88EAE57C72BAE029ULL, 0x7602F0D8FCA4D5A9ULL, 0x7432D7D7E8D31C55ULL, 
            0x6C7459AD249BC418ULL, 0xE98843813FFE542FULL, 0xB59F8ACCF2102169ULL, 0x01DF4E40FB120958ULL, 
            0xA129A62DDB64E6B0ULL, 0x78F0F13EC2274B7CULL, 0xC3437C28D46A1312ULL, 0x66725F1B2F2FF23AULL, 
            0x222480A46F0B8E55ULL, 0x441903CB802ABD11ULL, 0x0B901E7FE65DEF83ULL, 0xA9828878516E53AFULL, 
            0x9D36F8EBCEC66173ULL, 0x7FF7134477977C57ULL, 0x8D39A945C9BD46ABULL, 0x62953050F4055E64ULL, 
            0xE740F7828FAEF5D4ULL, 0x3B6A29CD14B9FB36ULL, 0x42A9E481078A7FCDULL, 0x9B6E752CC267A6A6ULL
        },
        {
            0x79CDFA69DDBF419AULL, 0x7C1085B80A4F9D4BULL, 0x9A2DC775686F8EF7ULL, 0x656EB926F4C0E136ULL, 
            0x8D07D3BB11B8FC20ULL, 0x32E464EF4A88FCDCULL, 0xF0CA703EF5E9C464ULL, 0x3C85653B5F889088ULL, 
            0x9B207009555C0FF4ULL, 0xABAD5D173933FDDDULL, 0x49AED8F73BBD2CC3ULL, 0x4F457F15D0D71FC5ULL, 
            0x7D24C2EE005BDD3FULL, 0x276DA4A4642DC162ULL, 0xE2A2A6CF8F0F49A0ULL, 0xD5BC8E1FF38AE3AFULL, 
            0x040E91487C950AFCULL, 0x98FDD92352EE73DFULL, 0x374CE9847CF1921FULL, 0xF8B12FCD2EE7DE76ULL, 
            0x6B3AEAA8146A8002ULL, 0x99F72D8279F76DB6ULL, 0x2479D82310365B40ULL, 0x9BC3D1DE26E898C9ULL, 
            0xD99BC78899AC2FA0ULL, 0xF7AE1E30F884B3AEULL, 0x133D893AFE9C1352ULL, 0xEDB3B5013F6612E2ULL, 
            0xD0109A87B6C271BDULL, 0x5104CF687EAFB872ULL, 0xAB898BB772A446DEULL, 0x340C94CC7FACA819ULL
        },
        {
            0xE8EF4E9CCD0F6443ULL, 0x470EF36403C003D8ULL, 0x5FC01BA0EDCCB102ULL, 0x03BB14AC778CB1E0ULL, 
            0xCDC8DFAE99127F8FULL, 0xA0AF31B514D26405ULL, 0x10F0DFC052899559ULL, 0x20174C1567227F7FULL, 
            0x6613EE9C1BF42FD0ULL, 0x1554CE25509FE488ULL, 0x424A995176C18E16ULL, 0x676FAFBB85666906ULL, 
            0x74876CAC27206CBCULL, 0xE60C00277B405A78ULL, 0x1A0EF4CBA43717B5ULL, 0xFAF5C83981AC022AULL, 
            0x598DB5A7BBDAE62EULL, 0x4BE1344A5B2BE550ULL, 0x5A5A87147658F048ULL, 0xF25F03AE15998135ULL, 
            0xADCBBEDBA0072067ULL, 0x493D0752B6B68B3FULL, 0x4F609B2324849E74ULL, 0x22CCA0439D970210ULL, 
            0xB762EE8C58553781ULL, 0xC07D8531140E36D2ULL, 0x655E96BA39B25012ULL, 0x038B3228143F9674ULL, 
            0x4E3ED5FF1CAF27DCULL, 0xE0DBAAC67FA1E22AULL, 0x99F505D760921D79ULL, 0x767C181AB718FC11ULL
        },
        {
            0x435B47531AF165B7ULL, 0x0B6443A459CEF521ULL, 0x9D5F7DB60251C28DULL, 0x12402D35E8E4BF8AULL, 
            0xE13BBDCDAF1CF351ULL, 0x250FDCEDD5A4B210ULL, 0x39BB8FF3BE3DB454ULL, 0xF398A11C423A3434ULL, 
            0xDCB19FC82D6B0F32ULL, 0x090FD89952E44002ULL, 0xB49102F6A5A0015AULL, 0x18997680096E7A3EULL, 
            0x7D885A79B4C9EF19ULL, 0x08B416E37AADE7F1ULL, 0xD97C960B04ED3A5FULL, 0x39E9BCB04FEEB008ULL, 
            0xBD1169852009E4ABULL, 0x76EA6F4A783D2540ULL, 0x602947DADFAF13C2ULL, 0xAE117E5820234381ULL, 
            0xB0B6F12932E0EDA7ULL, 0xF8F49C7B27BC97E5ULL, 0xE075277AEB2402F1ULL, 0x6CF45230902443A8ULL, 
            0xD5B70A707FB0B70FULL, 0x6313BF413DF86CA2ULL, 0x7990D2E45D2FFE81ULL, 0x32211A2D81F88752ULL, 
            0xAF8FA91010F3B5A8ULL, 0x2BA75673F1806FE2ULL, 0x333BC899E74F7E75ULL, 0xDD0C0C386FA6B0B2ULL
        }
    },
    {
        {
            0xD9141F7B69E48F84ULL, 0x3B99C082A4AFA20CULL, 0x88010795534180CDULL, 0x5D069C88FA8B38A2ULL, 
            0x8136198D30EC65C7ULL, 0x97DF1E7EDB19136FULL, 0xA56EDD10575C6BB7ULL, 0x6D3233F1E25D3C8FULL, 
            0x1E8A621C810EBB9EULL, 0xDFA4CA65917C1083ULL, 0xFED03A81759A3129ULL, 0x1AADF790F7957132ULL, 
            0x90F8B6F86BDF8FAAULL, 0xCF11C9CD7A7AC400ULL, 0x9AAF158DCE5C09A9ULL, 0x0F3F37DC08D63E6EULL, 
            0xA22519B6E4350604ULL, 0x9964FFFD6A2A3807ULL, 0xA23092B292A3889EULL, 0xD9476DA341DD50A8ULL, 
            0x5B530889CE921309ULL, 0x95C4794741662CDAULL, 0xC0DD589E9F63348EULL, 0xD047C90A73C1E63EULL, 
            0x673F999FF7A87E1BULL, 0x1DC893C4EB2391EDULL, 0x766405EBE1954205ULL, 0x4576C8054980A89DULL, 
            0x48D3B526D6FF1C9CULL, 0xF7A19F61B4F75C13ULL, 0xA356BAD15DFDE7C6ULL, 0x786B2DCAD9C0B30AULL
        },
        {
            0x42469C7E218A99FCULL, 0x7621EE0BACA9041CULL, 0xBB75D7541ADD86A2ULL, 0x237DB8A042628D0AULL, 
            0xD92E0F2D499EBB41ULL, 0xAA66624C6FFE786EULL, 0x5BB99A543C05F810ULL, 0x9B98CB3EBB790553ULL, 
            0xA170FCD2616F708DULL, 0x718EC53D0128D497ULL, 0x147E2CA24123DD76ULL, 0x86C87867D91A88DAULL, 
            0x6913B82C58E7B92EULL, 0x45299B5B1BDD0C56ULL, 0xED8FAB80EA627A13ULL, 0xBCA5901CF1E89BB5ULL, 
            0x1AE3F08980EBB311ULL, 0x3A6571D73125CBDFULL, 0x77D0E58B16761B71ULL, 0x89449FA7E96D1536ULL, 
            0x0F3B03AEF4EEACA6ULL, 0x202517026054D029ULL, 0xF5665388E60490DAULL, 0xB4D757AEE9815349ULL, 
            0xF43D56895EFF5170ULL, 0xB80D9866316E65ADULL, 0x17D0AD7E3EA99CB3ULL, 0xCBB92726C2C44E06ULL, 
            0x1CD6E66CD5F54F97ULL, 0xD6A2FBF796C490FBULL, 0xCDB5AA31B95520B1ULL, 0xD4C6CDD927CD9B98ULL
        },
        {
            0x9F2A7EDBA402C947ULL, 0x0B4122D69C57A4DAULL, 0x683CFAA47CE075BDULL, 0xAF4087942A9F37AAULL, 
            0x037339C5D2A7457EULL, 0xECBAE45D182E813CULL, 0x71A10ED1F1AA9BEEULL, 0x0CA8DD628260B6D1ULL, 
            0x0B9533C98BAAD666ULL, 0x079D9302814708A9ULL, 0xEBA0B823372BDB7FULL, 0x822B1BCB753BCF89ULL, 
            0x8D2D1CBDDA215271ULL, 0x5D7E853C9458B37DULL, 0xC6678C888A706C7CULL, 0x3DEA5C460348B69EULL, 
            0x77646B43D3D8EC76ULL, 0x64676C12310C9D9AULL, 0x932D4E4F3A42AC41ULL, 0x19BB827BF5A30352ULL, 
            0xCB7273D58D213220ULL, 0xEACCEEC5DD502E36ULL, 0x7FB4EE1DAFA58D5EULL, 0x472896C5D81FAF02ULL, 
            0xCBEE6382344BA764ULL, 0xEFD7CB5A420DABAEULL, 0xE744BE541A3444D3ULL, 0xD65A4E22D611E607ULL, 
            0x0510F83368F65322ULL, 0xEF1F192A2E720997ULL, 0xB8AA2F0E67CC58CBULL, 0x19D793BFF3896367ULL
        },
        {
            0x31DA868E590662A9ULL, 0x76ADA5AB58B40D72ULL, 0xF671E19B3B0DE101ULL, 0xAB16635C1999B803ULL, 
            0xCE6573058A542021ULL, 0x39D0F53CD33BAE75ULL, 0x0F9788D1A9F0C62AULL, 0xA9053DC0D7B25221ULL, 
            0x3373033D45E08A0AULL, 0xCCA9FFA495ED58B7ULL, 0x25E0135629A2F2D4ULL, 0x053536BEC19ED14DULL, 
            0x03E2C4BB724F5C5EULL, 0xD16C2B7740BA3AA2ULL, 0xC519E0492DB38E9EULL, 0xD0EA7C86CAF70F96ULL, 
            0x638B44221C17E93FULL, 0xC5DB3099BF90C783ULL, 0x51EB5DC610C3E5CBULL, 0xDA86429F2B9691A7ULL, 
            0xE74EDE551BFB5E8AULL, 0xE6094EAA678D997DULL, 0x8058884342710384ULL, 0x142EEC894D45C76AULL, 
            0x012868C4FF017E7CULL, 0x5A439B822722D19FULL, 0x4AE7AD660FC6350AULL, 0x761A479C2C1E781EULL, 
            0x2AF64891BCAA7912ULL, 0x4E8480BC5888848FULL, 0x3DC16B8E8F9EC9D2ULL, 0x64983975ADCE03A2ULL
        },
        {
            0x2B7D6B8CABD28F1FULL, 0x53F86138165EF243ULL, 0xB43E96B7BE7A6357ULL, 0x55017C1745E25051ULL, 
            0xEC93C6C3E5DD3C82ULL, 0xAC1CF34934CC64EEULL, 0xCB756C5F307B5BA3ULL, 0xCCD676C92207879BULL, 
            0xC9DE705702848343ULL, 0x62654DE3CAA8CF1DULL, 0x589CD454A07E8C84ULL, 0x3AD2BA98465B58DEULL, 
            0xBFC9422DF92B1B20ULL, 0x7A9ED41C012507ACULL, 0x6BD1B3F2863F3EADULL, 0x813A91AF1D0C3091ULL, 
            0x650BB5CC5F6D3C82ULL, 0xA12F075D2098EAB2ULL, 0x4C980774B4D1BF59ULL, 0x7D5617957B0DB57AULL, 
            0x038A07810BFAC932ULL, 0x1C61F58BAF3A405FULL, 0x2A8C9E3F48B98240ULL, 0x47744CAC9283FE84ULL, 
            0x330EC872C87A0C6CULL, 0xFBC5E19266276375ULL, 0xBF11107D498C94C2ULL, 0xA77F0BCE1B88218DULL, 
            0x7A0B3970D38A9429ULL, 0x3F1F420460E09112ULL, 0xD69862A7DEF4F8A2ULL, 0x8D05F9164E13B345ULL
        },
        {
            0x37B0DCAF39AB556BULL, 0x9753A7A3CF2F5E50ULL, 0x95A9D7D6B75C4D70ULL, 0x3B9752DC6A98B44CULL, 
            0x81B33F58E0E958A7ULL, 0xA2B3B101E378BCAAULL, 0x0F51A37F6FD871BBULL, 0x3F7E79242192A7A0ULL, 
            0xC320040D9CE5B12EULL, 0x2A62232392417F89ULL, 0x126A560B4285212CULL, 0xCFFD23D6DB415C35ULL, 
            0xC4B85FC4D2639DD8ULL, 0x7FE68D9314C76462ULL, 0x9E3AAA69E6EB64BBULL, 0xF18C55F263317D71ULL, 
            0xB3751B53E25867C6ULL, 0x443D6D320476D4F8ULL, 0xACC4E54DC7149362ULL, 0x6A2FCB7A90970B28ULL, 
            0x79EBF6F05A876427ULL, 0xC26C93131FCC006EULL, 0x088C0A7C4F5A1957ULL, 0x58EA0865F10616C0ULL, 
            0xEC2DEBDEE64DC62EULL, 0x9DC1B1A258899248ULL, 0xC933EA2FE9D67F1CULL, 0xF1C0856E7BFDA04AULL, 
            0xB957716091B7F235ULL, 0x84FE01E3C28E8C87ULL, 0xC8987A9FCDD295DCULL, 0xC85934687B82CDC0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseCConstants = {
    0x828E973B7CFA9719ULL,
    0x288568509778499DULL,
    0x32AFE38DCD64747BULL,
    0x828E973B7CFA9719ULL,
    0x288568509778499DULL,
    0x32AFE38DCD64747BULL,
    0x3C08EAFD39C4AEE2ULL,
    0xB7E19729CEDDE422ULL,
    0x69,
    0xD0,
    0xFB,
    0x36,
    0x73,
    0xF8,
    0x1D,
    0x04
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseDSalts = {
    {
        {
            0x0787E9885932A360ULL, 0x2A9FD93A87E3817AULL, 0xEE94504AA1770C41ULL, 0xAAB750E1F07D7067ULL, 
            0x8E371ACF94F02EE0ULL, 0x83BC3EFD117E5CB7ULL, 0xA58EB967B32B2142ULL, 0x64AF0ECA50A96728ULL, 
            0x9B3C7954D9DACE5CULL, 0xFB59ED7CFB4BE36FULL, 0x876911ADEA245072ULL, 0x663AABB253B3FD67ULL, 
            0x4957C037CE222F4FULL, 0xED74A660903D7D15ULL, 0x4E1EE28D967D7917ULL, 0x721D3A5E7AEB8A99ULL, 
            0x52461206EDAEDF98ULL, 0x1E36A7D882E722B7ULL, 0x86635D132C2DB714ULL, 0x09553B8B444F24EBULL, 
            0xD9175F6D752C689AULL, 0x7794592278F234D8ULL, 0xFC2CEBBAB031B073ULL, 0x3F5B42D2D45AA8F3ULL, 
            0x92BF42A9BF5C9678ULL, 0x4F941967FCA9BA0EULL, 0xB9D3914FFB00BA52ULL, 0xD31BF72198FF53A5ULL, 
            0x48177AD16A35DBE6ULL, 0x05688CE371AFBD0DULL, 0x3BED37326275D595ULL, 0xEF55ED99EA458EB1ULL
        },
        {
            0xB1FF5C0A278B49DCULL, 0xBD1D0B9BF72DAF4DULL, 0x56F8191EBAD338E8ULL, 0x371C1ED92F1C5BFAULL, 
            0x0961FC381371BCA9ULL, 0xAF331A0D7AFFCD36ULL, 0xA3CECEDB47AAE7D3ULL, 0xF7975CEE96AEEE3EULL, 
            0x6D186963AAF3A7A9ULL, 0xCA319C0BBB848704ULL, 0x9C5AB2B9745CDE0BULL, 0xAB45B8AB457EC0F9ULL, 
            0x238FC7E66898A9DBULL, 0xB0863AB8211B4A5AULL, 0xCBA796296E532A84ULL, 0x53334F8F6D1F1324ULL, 
            0x0FA19BEF48D65BC8ULL, 0x18B719A933CE7297ULL, 0x1975253C25CFF306ULL, 0x43F67259CFDD75A5ULL, 
            0xAA7DB999FA10784AULL, 0x72A323D20C5BB6BBULL, 0x35AC9F3838D1DAC5ULL, 0xD97D1E2129DB2360ULL, 
            0x2E8085889B7434A7ULL, 0x5360BD677C59D47DULL, 0x27DF561CEBC629C1ULL, 0x2838EFC03887C445ULL, 
            0x4402DC2E1FA8ED79ULL, 0xFE23AAC28B141129ULL, 0xCF536C1E61F49983ULL, 0x34EAD4DBCD487FE6ULL
        },
        {
            0xC723D3DBB53F385AULL, 0x854709B6573605D8ULL, 0x4611063C15D13356ULL, 0xF48DE07F3AEB59F5ULL, 
            0xB0BB9CE0B2A34B52ULL, 0x970DD1C606769E1FULL, 0x43F931DB19AB7D85ULL, 0x86190453CCFA016CULL, 
            0xA6040C5556E9DF97ULL, 0x2CB14CE965B558A9ULL, 0x430E19F0FFF972F2ULL, 0xE710C3EF40843E11ULL, 
            0x9E03E8BF5A49174AULL, 0x09B335C3BCC58D34ULL, 0x21D20741E37A75EBULL, 0xAD7D80155B12D304ULL, 
            0xCF0627A34E5CA1A0ULL, 0xBFF92F24A6881F80ULL, 0x79A47D5586EB89D7ULL, 0x31ACECBC589CCEFBULL, 
            0xD621C700767AD92CULL, 0xB6AE650DF15EAFB1ULL, 0x11A0A358D1FA0D72ULL, 0x7B5E7883F6AD3405ULL, 
            0x3174DF88530687D0ULL, 0x12C1F5F1C12A9288ULL, 0x872EF950344F11A6ULL, 0xCBCB80870EBCBF35ULL, 
            0x61413361C2689AFDULL, 0xD3D408E85CA253B7ULL, 0x7EBE8D4744FC3BD2ULL, 0xEE225240DB197251ULL
        },
        {
            0x331EBC9949CBC9D6ULL, 0x6C567C9786FE048EULL, 0xF6A250C18F4AD1DFULL, 0x525F3C388427A071ULL, 
            0x41746EE36F5E7AC9ULL, 0x3885FAE14C94DC3CULL, 0x0611A22045275D30ULL, 0x682393449C4A5EA6ULL, 
            0xB7E5DF2B18A142C7ULL, 0xA1B45552B6793495ULL, 0xD7091C5C8E2ADBE9ULL, 0x030C475915B0F06AULL, 
            0x9F2A8EF17D2484BFULL, 0x9DBB7D3AAE97F020ULL, 0x5C8BD19AE00FD1C6ULL, 0xC2058EA3E69E272DULL, 
            0xFFEE49BCA2A466D3ULL, 0x365E6361FA4D18DFULL, 0xDE6A091C47F3AE15ULL, 0xEFF9249F3D1E124FULL, 
            0x1F2CA07679BFBC91ULL, 0x3FEDB9D9AD3267F5ULL, 0x7029CADA63B781F4ULL, 0xD8DA43B8B3DB9C0BULL, 
            0x1B177EA4739B00F1ULL, 0xCC66EFA88550D511ULL, 0x9E86F7F567F8BE18ULL, 0xDC9E851FA7634D40ULL, 
            0xE30689BE1010F588ULL, 0x3B1BC62534CDF271ULL, 0x594F365F27EFED93ULL, 0xCB0ACDCAA261B273ULL
        },
        {
            0xB4B9EEFC263A2AD1ULL, 0x2CF3E47EC0336905ULL, 0xA0D6F31731B7A1E3ULL, 0x46EC1BAFED6A4F8FULL, 
            0x3981A5E1175CB11DULL, 0x756B43827378B79AULL, 0xA630ACEFBE7124B2ULL, 0x3C8011CEBD06D62FULL, 
            0x877BEB4111BB92ADULL, 0x996B0F5073631062ULL, 0x9907C9B13FCD110EULL, 0xEBD3E9400501B66FULL, 
            0xDBCCE1BB014E2284ULL, 0x5877BAB2C7265427ULL, 0x4D1D77F96F9AB3E1ULL, 0x17B6EC1CCAAE36FFULL, 
            0x0EF4A3314973283AULL, 0xACC3EEE33FE7C5EAULL, 0xD3A83F7956A14BFAULL, 0x7006D26EA67B5C26ULL, 
            0x953E68D8E268BD5DULL, 0x65121BBA25681CB3ULL, 0xCA9E904841127427ULL, 0x3C81E4774328C9B5ULL, 
            0xA036CE6B67112FD2ULL, 0x63D556504AE2A859ULL, 0x99C999D307738B4BULL, 0x0B49EC90F8832FACULL, 
            0xE1537D1C8F88E7D8ULL, 0x1B7F7C5E0CD87A51ULL, 0xCF0A08F206ED7C95ULL, 0x78705C9780A9070BULL
        },
        {
            0xD3F442BD50FB9B37ULL, 0x0FFA7C53F384BFB9ULL, 0x2DDAC80445A01B90ULL, 0x841933C6C819C9FAULL, 
            0xB4F30926115A1D44ULL, 0x01575CC3C5356478ULL, 0x0995775B9B5F6FDBULL, 0x28723E60EA9F70C9ULL, 
            0xBC9B4FE91C12065CULL, 0xEE7CD05E828A4798ULL, 0x07BA16D855FD6653ULL, 0xF206A52C2DE2CF9AULL, 
            0x831AFE8F2F597039ULL, 0xCEB708DEE791D6E3ULL, 0xABB11894A431BE64ULL, 0x2AE8F6C18DE4B154ULL, 
            0x0DF8236895CF010FULL, 0x36CCF1EF19BBE417ULL, 0xDDDF49044B959C32ULL, 0x6B4641D277E4518EULL, 
            0x2CFD8C3B15777718ULL, 0x7D340EC173F521DAULL, 0xDC1BD4238CAC414EULL, 0x5014DF6A940AEADDULL, 
            0x519F792ECD90D817ULL, 0xC72C5C3CD1D155BAULL, 0x30E0A5F9DF625E28ULL, 0x8B8CD1F8E862FA95ULL, 
            0x97B740056F422706ULL, 0x81E07A616368A896ULL, 0x76C8DC9B6B6EDFFBULL, 0xBD5B8C5CD7014763ULL
        }
    },
    {
        {
            0x38FA3966D971A272ULL, 0x9ABA071E910668A7ULL, 0x3EBE092E7DFEE11DULL, 0xB6769EA608780522ULL, 
            0xB63F0D34FC4A59B1ULL, 0xFA67AD0F7C90C78CULL, 0xD2C008752E905B6FULL, 0x9DC42AA49EA13806ULL, 
            0x42C3B642D211497AULL, 0xAEA5E670B76F02A0ULL, 0x17F69EB1E47B307FULL, 0x6E6B79E87BC6898CULL, 
            0x56B6FD3D716730BAULL, 0x2922699FD71AE8D9ULL, 0x509DD6716A61EE2BULL, 0x4C312061FDCB44CAULL, 
            0xEB213D0853C6A4C3ULL, 0xE0C3545B9DABBF9DULL, 0x7EF67DCDDB59D2FCULL, 0x7FA9FF6B95638FBCULL, 
            0x867945082D303B4CULL, 0x6ABA411F3663FF32ULL, 0x634414E7F5613397ULL, 0x95FBD92B7D55F3B2ULL, 
            0x8156D186F3A1D2E0ULL, 0x7AB729150C063962ULL, 0x372691BBAA04F67CULL, 0x79D1F0B8F079EFDDULL, 
            0x627765DFB4A933E1ULL, 0x4522AE45CD94F6F0ULL, 0x08E528D88B68A38EULL, 0x3557CCFB4144D909ULL
        },
        {
            0x70272AC63584580BULL, 0x365467107A825A11ULL, 0xDCB2CDB51B7299A9ULL, 0x701CDE9B53AB2867ULL, 
            0xA4EF83E94F488F4CULL, 0x2FAF815A651CF1B9ULL, 0x873A8C08045456FDULL, 0x3BEFE7FDC9EC2C4FULL, 
            0x48B7C2250458BD27ULL, 0x00BFFB373151331AULL, 0xA17E70A3A53C4E07ULL, 0xA213D916E7027E7DULL, 
            0x552E761FD88144F4ULL, 0x2AF3EF96995D4F36ULL, 0x6FD6D0BF386AF2AEULL, 0x1151B792D711D07AULL, 
            0xFA10FE0803093F96ULL, 0x58D63C87318B7B9FULL, 0xBDDDFAF7749B5842ULL, 0xDFB450037A25B018ULL, 
            0x6E58B63F09802AC9ULL, 0x526CA13DAE247BA8ULL, 0x8EC3C33769CD031FULL, 0x34BC133144FE21C3ULL, 
            0xA643C35DD3B8B45EULL, 0x94A86B8A1BE5FA27ULL, 0x715F9DFC0EE98FD7ULL, 0xF9B91C78FE6D6016ULL, 
            0x710436CEEBA1ADE9ULL, 0x615114EEC9A47353ULL, 0xA792482BD75DF902ULL, 0x41349754122DD35AULL
        },
        {
            0x585E4B9B6201C01BULL, 0xAB13A5E6401AB73DULL, 0x791FF4D842FC34BAULL, 0xEBA18856F6F2C96FULL, 
            0xD57B1CF4BB1E3D74ULL, 0x7E3A2F17CB7FD9C8ULL, 0xA35E9C4A6E1D066DULL, 0xAA5D99EDB66C0ED6ULL, 
            0x107656956735A22AULL, 0x753BE79E8382E58DULL, 0x7D37C6B393D2181CULL, 0xACC9AB31BB6FC82EULL, 
            0x4089D5AD0F5280D5ULL, 0x8A232C784AA38A67ULL, 0x3B2E59687E76710BULL, 0x4E69B2D3FAC765E4ULL, 
            0xA295A319B7CE608AULL, 0x216EBB2AB6432993ULL, 0x314CF87A8C1A6C9AULL, 0xF5DFA47B4B784EBFULL, 
            0x41E9E93AB57F0DE7ULL, 0xE5E62F50A7CEB5DEULL, 0x7C462E6B1C84FB15ULL, 0x6ABE978987345AE0ULL, 
            0x6DE171205CADF4A8ULL, 0x6083CDF4EA58096FULL, 0x28707C95545E4240ULL, 0xA3B210F04A2998F4ULL, 
            0x1A50BE225253C326ULL, 0xA7BD0FC7A1A47F73ULL, 0x58419C85B9ECCC96ULL, 0x929F46B2287997D5ULL
        },
        {
            0xC123A0619F297208ULL, 0x10C801E7B50F3635ULL, 0x8445F363EE8BEC1DULL, 0xF2F54EB5434DE66EULL, 
            0x93642B9E4991E46BULL, 0x398B1EA6A1895F52ULL, 0xDF71B6209010E63DULL, 0x89A67E81D7E034DEULL, 
            0x53712AA05B272E5CULL, 0x04D50D9EADDC99E3ULL, 0xC8E1AFD0087A7DF6ULL, 0x4253F6AD7A9FFE28ULL, 
            0xABBE77500DBE533FULL, 0x49C993AD4895AAF3ULL, 0x452D4DC0A284ABBBULL, 0x79583CA1D0514F34ULL, 
            0x9B938632E020DACEULL, 0x0BBB1ACFCE0EBAC6ULL, 0x1035243517C2CB7CULL, 0x29093A01148BE4E2ULL, 
            0x06067E1671FECC7EULL, 0x6D5EF2FA4237A333ULL, 0x93226529FC4635FEULL, 0x9540143C4D79D5DDULL, 
            0x02BD0E8A793E96EAULL, 0x7D495DE4E64B6586ULL, 0xBC643E2026271932ULL, 0xA9CFE91EB5F9C659ULL, 
            0xE334391374B0B62DULL, 0xA37ED8532E039CC2ULL, 0x21219E45C5AFE23FULL, 0x1E050CC7DAEA3BB3ULL
        },
        {
            0x0FD439FB5148B821ULL, 0x0FC99A6CD9A7F29EULL, 0xA5DF64746AE29B3DULL, 0x37BBDF58F07074A5ULL, 
            0xD0B7667D2BE631B3ULL, 0x0E1F25CF0E945F94ULL, 0xEBA97F4FB19DA2D3ULL, 0xA320152ECD497079ULL, 
            0x4E085DC267C7C535ULL, 0x82281FFAE009580CULL, 0x7353DCDBA92D4B0BULL, 0xF82E090954CD8CB2ULL, 
            0xC04A5C9C7A9760DBULL, 0x61474220177C0620ULL, 0xD502DAE78B945411ULL, 0x2AE28AF23B9750FFULL, 
            0x88B2418DA967122EULL, 0x5A60565E90180FA0ULL, 0xC3A5ACFCA245B816ULL, 0x84E5ACF675D05026ULL, 
            0xF66735CEC0E36509ULL, 0x6452630D0DF41EE0ULL, 0xDA79CA9591417483ULL, 0xB86F5C4076DFF263ULL, 
            0xC0AAA2319BE9DF6EULL, 0xDFF6DED6936987DAULL, 0x130E62D613BDAFFCULL, 0x531D1DA9A2EA1540ULL, 
            0x3316DC5B38AB140EULL, 0xCC3BBFC1674730C9ULL, 0xB0402C6C5C4F26F5ULL, 0xA78A9CEA43B4BEE5ULL
        },
        {
            0x02CA0414BAA719EEULL, 0xAC3B4488F0FABEF8ULL, 0x366E1C2074AACF7AULL, 0x825C71CB662C3F9FULL, 
            0x5FD429A077F69D37ULL, 0x7B0ADBD228974A0DULL, 0x827D027884C67C2FULL, 0x133A1974B1572A27ULL, 
            0x57D2849B3C408643ULL, 0x693F02891CAD2D1EULL, 0x248FDB1318B12EBEULL, 0x0A164C24A77FCCE0ULL, 
            0x2607FD6AAA9B13DEULL, 0x55584B73F74DF9CFULL, 0xDD5F9AF0A63F1D93ULL, 0x3D2D0B9B056FF460ULL, 
            0xA594A5481CC6FF0FULL, 0x40B78E40A97DFB65ULL, 0x532556E72660D534ULL, 0x186EBF9A563D5E87ULL, 
            0x1AEB8453B6098A4DULL, 0xDC65AB55A8031455ULL, 0x0C4E538DB84ADDC9ULL, 0x7800A40BD7A95BCCULL, 
            0x6E13A10F77CE1539ULL, 0xE95743E64B458663ULL, 0xB016558B44430617ULL, 0x69670360724B58C4ULL, 
            0xBA62099473D60346ULL, 0x63F6D75223A12CEBULL, 0x49099995FB63EC21ULL, 0x7718F357BA033FF3ULL
        }
    },
    {
        {
            0x6401C144281579A9ULL, 0xE698829BAEC0CDCEULL, 0x644B6837C8582CFFULL, 0x7B591A1D94E128CAULL, 
            0x82B6E7E6E29E25DAULL, 0x993BA52181EFF7D1ULL, 0x190D6DA68BCD22ECULL, 0x81F017B5A52CC24AULL, 
            0x0EE7F924DB4406B9ULL, 0x450D2B6FF23573D6ULL, 0xF22FC0DA5A375152ULL, 0xDBC19E99CE037BD3ULL, 
            0x01971D84D1C96136ULL, 0x5CD5A91635E004D5ULL, 0x7FE88D521CCC3641ULL, 0xEF268E5FF0410D84ULL, 
            0x160A4AC66D4894DEULL, 0x84D7D582B8D00033ULL, 0x5C11DADD9BBA6750ULL, 0xEB996A4CF7D0976EULL, 
            0x9E9297CF634DA3F0ULL, 0x51B21B58BF2558B4ULL, 0x9CE5834198A6908DULL, 0x6F7125F37FA7AB4EULL, 
            0x860027C4B0C073CEULL, 0x9311EE050D39E73EULL, 0x6D8804E4E2DF1197ULL, 0x555B1C3574D0F449ULL, 
            0xB9315558F6EC3244ULL, 0x9747D471F19EF365ULL, 0x1C07B1736B1E58DAULL, 0xE0EA88647D0CAB57ULL
        },
        {
            0x9A5CAFF5C3C4303BULL, 0x8B02032064C3D748ULL, 0x75C4EC5CD842457DULL, 0x3557F28736E4242DULL, 
            0x97894209283F87A9ULL, 0x446257617ED7B6DFULL, 0xE35A3BC330400E09ULL, 0x2EAC8AAC18D41E2DULL, 
            0xC7414546E5F3F491ULL, 0x419250B72868262EULL, 0xCC0CC4AE3F87D4FCULL, 0x32C926EA892A8C0FULL, 
            0xB9496D59B31780D3ULL, 0x62586CCB49A22D94ULL, 0x6CED8484C5D7B162ULL, 0x923763C46305E3D5ULL, 
            0x6D05979DC2C8635EULL, 0xC3168391D22D92D7ULL, 0x4D179879AB26FE80ULL, 0x3A18C8DDA19CEB42ULL, 
            0xE0902EB085F1317DULL, 0x920984E6D5EDC353ULL, 0xA5E1E921835BABF6ULL, 0x3C57DE9985ED9BC2ULL, 
            0xA15BC1E9F9C7773BULL, 0xCA7EEFF166B58AFBULL, 0x58B9D39C2B863920ULL, 0xBACC8CA9CDEE0941ULL, 
            0xB4347750B7539743ULL, 0x34064B4C7E937A46ULL, 0x02E1C78286BEDC43ULL, 0xE7236B91E60DBE77ULL
        },
        {
            0x84CD211B5CEBF169ULL, 0x2E97F4F566560485ULL, 0x304E15195351EED7ULL, 0xF4820FF1CB079B0FULL, 
            0x4777078C250A4A73ULL, 0x6855179E7865F135ULL, 0x92EF617431671F14ULL, 0xD5DC6728DEF0A157ULL, 
            0x5710A3CC7E53A9EAULL, 0x605CD19D26904D63ULL, 0x14B4BBDFA3F94FB3ULL, 0x9F6E47834AD3F6EDULL, 
            0x09D689427CB156A5ULL, 0x0D5963A3A52BAC58ULL, 0xAD322420D551D049ULL, 0x9281AD71F04A3CEEULL, 
            0xCD40BD893195F918ULL, 0x9A9FE1E2348DC89CULL, 0xD89A59B3E74B74C4ULL, 0x4D5941584DA32092ULL, 
            0x19333F2AFAEF1E9CULL, 0x31222366151830A9ULL, 0x3CDEE7BEC457A4C0ULL, 0xC9D8151F85116F88ULL, 
            0x160B7BC1AAB3D707ULL, 0x209B8EC3D48AB130ULL, 0xEA9B73C7D8EBE76CULL, 0x780D2FAE9E22D290ULL, 
            0x996F4EC265462603ULL, 0x91059C5BFAC44294ULL, 0x0FE7895E33754562ULL, 0xEB0B94630CAD0EE9ULL
        },
        {
            0x901FC7185EF47482ULL, 0x0B2D8A9DF8520EFDULL, 0x52047D3E87B0F300ULL, 0x64650A59C3423FC6ULL, 
            0x696AF70F3C5C76B9ULL, 0xADF9E4F1052B2058ULL, 0x1F2C6BAAF5D63C14ULL, 0xA4ED680501BBB703ULL, 
            0x8419E8A0E0D30EC0ULL, 0x5F486E69253A6546ULL, 0x3C72DE743E86A4F8ULL, 0x9C1B79D4E672674BULL, 
            0x3F4DEFD176F3B5CBULL, 0x1287B8FB6452D634ULL, 0x4576939885E5A622ULL, 0x9DCEA04887AB66BFULL, 
            0xF8F6356438630D0BULL, 0x83FFED69114B464EULL, 0xCA0D5B95BEAE9232ULL, 0xFF7CFB176B3806F4ULL, 
            0xFE9E6731ABC30804ULL, 0x9A56F6C2A43399DEULL, 0x0C710A8C4A8CD035ULL, 0xD8F1C915A8D50BD1ULL, 
            0x9656C53411FC9F2CULL, 0x986E29BB315DB318ULL, 0xD3C8108BE8C4590FULL, 0x4184156F7A6F13EBULL, 
            0xD3E2962D1F5456E4ULL, 0x4F51BFC3DE671427ULL, 0xAA5AD62EC37A1D3EULL, 0xAB224D04B4FB6202ULL
        },
        {
            0x7893B90ED722D52CULL, 0x58A88918F2188CE3ULL, 0x344F285A3530A443ULL, 0xBD57CC98EEA17F84ULL, 
            0xAA310278F322515EULL, 0x8F1F46F4EF6A04C3ULL, 0x770E3631B232D279ULL, 0xC87DE4EF48108545ULL, 
            0xD95CE7D125BA12A0ULL, 0x2B26628E91E6F3F3ULL, 0x08F8D01D6B0A0638ULL, 0xC36B14CD7A8F2086ULL, 
            0x0172CD3D3CFA4C4AULL, 0xEC41BE12ABFF2C1AULL, 0x8BDE4258735F2E65ULL, 0x3E4C8FEA8F6B40F9ULL, 
            0xBE76DB3237FE2E68ULL, 0x20E3ECF0684888C6ULL, 0x05D000BF4518924FULL, 0xF810A9A2114B6F11ULL, 
            0xC326787CA6F637C5ULL, 0x5FB9BFA3640E790EULL, 0x0B293BA9CF977B05ULL, 0x8FA47351DDE3BFDEULL, 
            0x8A8865F5C2B627BAULL, 0x6BC90460B5BDBA22ULL, 0x300FE6FED4F4AE0FULL, 0xF602E68D43BC94A7ULL, 
            0xC1F4C62835353165ULL, 0x02A64399A28B8276ULL, 0xD00C45B75424F51BULL, 0x0A056DE86C07ECDFULL
        },
        {
            0x7C3742585B7EDEA1ULL, 0x25957ED836C1D18CULL, 0x4AC2651D12E2509FULL, 0x84554FFDA1051DE1ULL, 
            0x1581F65A08FD7A9EULL, 0x98918ED5444F4036ULL, 0x1924487013A55FF9ULL, 0x5FE94EB59E5A8CF5ULL, 
            0x56963DDE7275830DULL, 0x471D0E5CD404C43CULL, 0xDD198221F0B2A556ULL, 0xC9D832795D1CD560ULL, 
            0x794A4A3ED41E6649ULL, 0xE392D78B85C91E54ULL, 0xBD86C8E7329B9DA4ULL, 0x6B2B023C08506D24ULL, 
            0xB45384873AFF80AFULL, 0x5338550C41CA57F2ULL, 0x78207DC08B9AD39CULL, 0xA189507FE2B3D0BDULL, 
            0x0FCDD393855C0BFFULL, 0x36BE5DF12C7A2F90ULL, 0xA1AFF0AA2A8F27DAULL, 0x8D0FD288BE00F391ULL, 
            0xFFE15CACE3BD8097ULL, 0x3D2FE2BF8107C4CDULL, 0x00C0BB5AEECEDBD7ULL, 0x9B0EBA531C2996ABULL, 
            0xEC30A9D69F597B9AULL, 0x875B5F0E45E65B53ULL, 0xFC2F31DC9602B25BULL, 0xA4696057230DDC00ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseDConstants = {
    0x55A192E2A1575F38ULL,
    0xA23C8F0E1FD162D6ULL,
    0x1268F4E1688E9235ULL,
    0x55A192E2A1575F38ULL,
    0xA23C8F0E1FD162D6ULL,
    0x1268F4E1688E9235ULL,
    0x326D25BD727B841FULL,
    0x37C206E030E9DB21ULL,
    0xEA,
    0x5C,
    0xFB,
    0x91,
    0x26,
    0x32,
    0x3A,
    0x73
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseESalts = {
    {
        {
            0x898D3EFEF46A986DULL, 0x63C634F3A6357872ULL, 0x3714F1AD08FD81A2ULL, 0x719A72789FFB01FDULL, 
            0xA020040FA6F25B52ULL, 0x7F006FDAE33B97CEULL, 0xB9B66086CD03447FULL, 0xC782F72CA96FCBF8ULL, 
            0x8655CCE4C2D22449ULL, 0xD9B05FE4E14AB70AULL, 0xFD327CA6664F19E7ULL, 0xCEE7EB6C80A4CE1BULL, 
            0x9CECE967733F8233ULL, 0xE3A1187D6C513C80ULL, 0xC6CFA182DBEA56A9ULL, 0x7B5854112A526ACEULL, 
            0x21A653EBC11A29ABULL, 0x6C7F4C0D33A25315ULL, 0xB77C6E698759E49DULL, 0xBB1F5BE97155E1E5ULL, 
            0x6D2498E2CF43D0C4ULL, 0xBEC46CE8F11C3121ULL, 0xC2ED6256DE6A15A5ULL, 0x010EDCAFF7BA5B5BULL, 
            0x84651F9C8ACA1BFEULL, 0xB7DBEFA0E3B61747ULL, 0xC61AAFB0F42CAE71ULL, 0xDEA34F407EAC038BULL, 
            0xE36C11E0ABD820EBULL, 0xB8C168CA7EF669BBULL, 0xEFB53443C38A8E6EULL, 0x9A066EE39ABB7956ULL
        },
        {
            0x80E8E3599F9E6044ULL, 0x2F1CE524FFC4B757ULL, 0x35284418DD09EBEAULL, 0x83F27F2593A2607FULL, 
            0xAA5DE3958E572470ULL, 0x4548453E704F1EEFULL, 0xD29308CABDFFB621ULL, 0x873E6D581309C8E4ULL, 
            0x6ED40862A4D95EF3ULL, 0x50754A6A185AD7C8ULL, 0xB3B7E82F6137B767ULL, 0xCB0C356EE24F31A5ULL, 
            0x44F91B6FD4A5CDE8ULL, 0x2479F9EC452EF2C8ULL, 0xA3C457431BF29742ULL, 0x7B2238205239DB25ULL, 
            0x4491CF3A81B9722AULL, 0x172B13D534C365F7ULL, 0x49980CBDC9F7F922ULL, 0xC3252969E28D5C21ULL, 
            0x29E19113217C79E0ULL, 0x395F261E39BF53B5ULL, 0x2519CDE97A58D2CCULL, 0x44BDE173044B91FAULL, 
            0xB9F698F20D9DC447ULL, 0x608AA4CBE81CCA5FULL, 0xB3DF8650C09354B5ULL, 0x36B03187A2DCC93BULL, 
            0x3112156947E6A395ULL, 0x678F59BD848B3E60ULL, 0xE406232164C7F290ULL, 0xB1CC6C103B0886CFULL
        },
        {
            0xF96164B22E0A5158ULL, 0xD7A72B62C4550C60ULL, 0xF4F7D4AC1190B7FFULL, 0x136F0A2CA26ECE14ULL, 
            0x42BB53E1973403F0ULL, 0xCC079867D3B9F393ULL, 0x9D7BD55060AE19F5ULL, 0x798D07C8CBC87A60ULL, 
            0xE2B87F4D5F5783EAULL, 0xF772F6D37A37FEA1ULL, 0xF1777BEBEB9B01F7ULL, 0xB630D51E4FFA3A0FULL, 
            0xD935E3272D2093ADULL, 0x98A3102A9A946B02ULL, 0x822DBAEC94820D41ULL, 0x5891D7D6042225D6ULL, 
            0x8E7E0A43E827E2EEULL, 0x8BAABCA4BA4BA9BCULL, 0xCBF84208E5998F6CULL, 0x27B2278ACBADBF4EULL, 
            0x587F0B5D73B7FC42ULL, 0xDE78AF3FD06B963DULL, 0x33C031BE6858FBDCULL, 0x58E0EE094A039A4BULL, 
            0xA7E5A8D75A8DED9BULL, 0xF56C171EE973550AULL, 0x1592C79CFAA0C988ULL, 0x00C9DDB5C04C1F14ULL, 
            0x8424A6157D61BECFULL, 0xF63EB758FB995549ULL, 0xD21DEE4E50212EB1ULL, 0x1F859411592B0CB4ULL
        },
        {
            0x7AA91BBFE9E646D6ULL, 0x7E5CFD561A5C1EF5ULL, 0xD1AC757002BF3DF5ULL, 0x8B5D0299FAED11AAULL, 
            0x50F723C9AA58E5D6ULL, 0x64706EFD65FB974EULL, 0xFA444CF24A86901AULL, 0xC58D3AD720DE97C8ULL, 
            0xE292A0932B0C4C67ULL, 0xE785A0A864F91CEBULL, 0x1E43F65AB7A6B74CULL, 0x5DA3F41CFA78CE29ULL, 
            0x2DD2120B3C2AA675ULL, 0x9B3DABC61A59B551ULL, 0xFC55B1ECFE36FD94ULL, 0xA2C0BE9802EBB9BCULL, 
            0x4404E6F83866D5F7ULL, 0x8E6BCC2589746502ULL, 0xD427263ABC109951ULL, 0x5FD2ABA916A2C15AULL, 
            0xD30C3380AFE87E85ULL, 0xCC6563E0A97DDF0DULL, 0x1757A17A5FEB31A2ULL, 0xA9F18B094A725AB0ULL, 
            0x655E8F86C61D53BCULL, 0x4E91A3E33D76A057ULL, 0x302DA647CE027985ULL, 0xE96B653EE37755ACULL, 
            0x0CE2DD33AF2EC3C8ULL, 0x76640056275DEFAFULL, 0xD271C7D7D466824CULL, 0x87899087CFB12DF6ULL
        },
        {
            0x9C6CAA1C609FF92CULL, 0x80C7A76C7B5BCD9CULL, 0xF6DB684CFFA8C436ULL, 0xD2478A5505D15EF7ULL, 
            0x9915D14F0F64F820ULL, 0xE634FFD0745480DAULL, 0x629029FFB68EE540ULL, 0x49A5F445F61291DBULL, 
            0x92512C7F8CCAECA3ULL, 0xF0C7C08B686989C1ULL, 0xB024867F680531DEULL, 0xE7679380B3D3B4E9ULL, 
            0xC0B249326E73B08DULL, 0xE8AA2E324A2A3943ULL, 0xB6CBA9A40B44E11CULL, 0x48823B6A872E703AULL, 
            0x0696F1AC80078300ULL, 0x4049ACB5897B89D8ULL, 0x38318D5DEE737057ULL, 0x237E870FB4533477ULL, 
            0xB9FC6037E6FF425BULL, 0xDEDDA82CEFD29B43ULL, 0x72289E5F66D13510ULL, 0x558131BA2243B38DULL, 
            0xA629F9B42B8D9756ULL, 0xDC238484539FE005ULL, 0x91C8626F833BB801ULL, 0x422C77674FAA45A3ULL, 
            0x685B8FA738F5F91DULL, 0x3ACF99CBD7FABFD7ULL, 0x1BE51B3D5CA3768FULL, 0x5959E2DFBFAAF22AULL
        },
        {
            0xB8BB108916ED8CD8ULL, 0xFEF3468B561D0A86ULL, 0x2535A2324E1F3161ULL, 0xB8D5F0069F4388E5ULL, 
            0xBCE4D1432A482295ULL, 0x986B1EE38A3FB301ULL, 0x5A1A9BFB450C634BULL, 0xB09B44629D9AEC83ULL, 
            0xFCDB01EFB5AC2749ULL, 0x524E305C544E5C6DULL, 0x4AA230BA24E9E74DULL, 0x02AE474DEB98B2DCULL, 
            0xA893ECCA16DD9667ULL, 0xD02DA491F9A9AA27ULL, 0xAC4A7B2FE8627EB4ULL, 0x7B98ED62A6893B0DULL, 
            0xC4B27F30FD780D66ULL, 0x6E62481AA5DF0034ULL, 0xEF9E7B3465735AC9ULL, 0x07A1D40A0BB05E92ULL, 
            0x602D0655BD0E2AD8ULL, 0x11DF61B3EE750587ULL, 0x00D74BDE177FAF8FULL, 0x30796E7CBF8BD447ULL, 
            0x411875ADB54BFF4EULL, 0xF1C8154007C1E9ADULL, 0xCF160F1684F41CECULL, 0x4F2D1566BF1BA825ULL, 
            0xE84A5E041E8B9FC4ULL, 0x5FBFE9F8E3595DF7ULL, 0x615B5CEADDDB54F9ULL, 0x288351714E523D09ULL
        }
    },
    {
        {
            0xA773DDFD81CEED12ULL, 0xA1F59EAF56C41A1DULL, 0xEBFF2B3A58FA34B1ULL, 0xF89E49B69378A784ULL, 
            0x7DDA9473A67A4AD0ULL, 0x14587F77E53E3DDAULL, 0x9AB5DCFF13BEF26CULL, 0xA89AAAE442E25630ULL, 
            0x9A8AD3F4FDE0BC6FULL, 0x4C51AA772787890CULL, 0xAFC60030E4B24A88ULL, 0xEF10877915DE50CCULL, 
            0x648C1A6DBE64137FULL, 0x303C76A2C9EA9D5DULL, 0xE5C2C1EA410C2344ULL, 0xC8605167DFB2D5CAULL, 
            0x228455D461774090ULL, 0xCC7C323FFF1B77BEULL, 0xAFEC5ACC279E2371ULL, 0xCB020F1B367C6EA6ULL, 
            0x03D68086FA2EFFF7ULL, 0xFFA5602A05F72CADULL, 0x4E1BB00122163CF3ULL, 0x77716EB2CAF84DB0ULL, 
            0x6F4D02813BFFDD45ULL, 0x181EE01A5265F4A4ULL, 0x90C09971A0CA212FULL, 0xFA5AB424F2934711ULL, 
            0x916B443FBAB3131EULL, 0xB1F6487D32E53A5FULL, 0xC93EE4DA467BFEE4ULL, 0x8EF7199445C3FC3EULL
        },
        {
            0xCEE5AF5D6831B862ULL, 0x2435F0E787C2F7D4ULL, 0x86802D7F9933B87AULL, 0xD54092FD0A78F825ULL, 
            0xA163C86CED2572D3ULL, 0x9918A5C3D9F2FD2FULL, 0x161040931DE62590ULL, 0x8E732950FD9E4268ULL, 
            0x39F1B86D81A6C485ULL, 0xF428F121C5D5B503ULL, 0xCCF9BF55833E363FULL, 0x2AC817B92DFB595EULL, 
            0xAD00464506BF7D42ULL, 0xF50C5D49D94304B5ULL, 0xE9815C9545C01C81ULL, 0xBEDC38791E049D6EULL, 
            0xE67B7C6F589F8858ULL, 0x88B06DF70DB7BB24ULL, 0x3A9B287AA58B2C87ULL, 0x4F9A0F3835061A2AULL, 
            0xBE9AE43AD695BD79ULL, 0x6D2891AF6FF9EBDBULL, 0x4BF65B331F1C476EULL, 0x5ED1F1F351BEA602ULL, 
            0x4DE8856B96179EBFULL, 0xD45A674C6A86C0FAULL, 0xC1066CF96C2FC4E5ULL, 0x44A612722DA68043ULL, 
            0xC8B354394AF1F303ULL, 0x2A7A0118FFE4E323ULL, 0xB633A954A9ACF639ULL, 0x81F7D0A7652E2CB7ULL
        },
        {
            0x716814E6099154C1ULL, 0x92CAE35AD2E69AC5ULL, 0x1BA8C8D20A9CE19FULL, 0xD3F7EE79C80BD19FULL, 
            0xD1EAEFD53EF0DFCFULL, 0x9E761584D9F6DCCFULL, 0x6025CA93E3F78BA2ULL, 0x84BD1DC94808EBADULL, 
            0xCC12274B095C0E3FULL, 0xA5386542F4FE4E99ULL, 0x0F3341CC6CFEEC63ULL, 0xA0BAA77EFCB64472ULL, 
            0x08D9A8A6057AB697ULL, 0xCF3210F695D2805EULL, 0xC494A1C8AB179039ULL, 0x9F095DA1F0BF977FULL, 
            0x4FAEA0A5B0125FBEULL, 0xB78B1D9738E0B44CULL, 0xD3FCE31A0DFEDBE7ULL, 0x84CFFFDB98556DAEULL, 
            0xA292F3A65B6BE01FULL, 0x1B7FC3FE251F2037ULL, 0x76CE82205C898610ULL, 0x4DAD36628ABE7479ULL, 
            0xBD92A69624F431E3ULL, 0x0320B66A51D40E23ULL, 0x789301815CFC1D7FULL, 0xFBFDF21F58CAF3DDULL, 
            0x3F056E4DE349DBF6ULL, 0x21581D249364C965ULL, 0x0735A192CDA251A5ULL, 0x4FB270972C13FA4CULL
        },
        {
            0x70F4D761A3D97D0FULL, 0x2F580C0FBA78D219ULL, 0xDE84E08C07EE7A69ULL, 0x035C29C41F14A8E3ULL, 
            0x68500231394F3568ULL, 0x718D980384E9EB8BULL, 0x6D4AAE4D14E31918ULL, 0x3905A50BDA3A45B1ULL, 
            0xDB1216DB49D4F1CAULL, 0x9B676C28535979DAULL, 0xA2519DCE9CA29EADULL, 0x2E2E2895AC25611CULL, 
            0x459FB391B8A5883AULL, 0xC814A0D646D85253ULL, 0x24DC2EBAE570300FULL, 0xA961028E4F40CDA7ULL, 
            0x7941C36E05C63659ULL, 0x737F3ED7202DB392ULL, 0xCE061EC0579F93EBULL, 0xB402982AB449B3B8ULL, 
            0x69CBA4BE4C6EBE43ULL, 0x8FED06D798ABDF40ULL, 0x55A00064258CB2B1ULL, 0x1F9D6E54D585C0F8ULL, 
            0x8657D3FAF24F3A84ULL, 0x9DFDA85900947BD7ULL, 0xAF4A3BDC421E2B3EULL, 0x8513EE73AC6B3C8DULL, 
            0xCDEBBE3DBFDA0FCEULL, 0x544FACB5C3DB839BULL, 0x7C9A71752F3993D2ULL, 0xB68021EF2F6B4429ULL
        },
        {
            0x691DF70847CE6F67ULL, 0x088277A5B6DACD1DULL, 0xF4AB52FCD302A805ULL, 0x4C7F4E7463CDD247ULL, 
            0xAB3D73E0956D92E5ULL, 0x930C5BC22AF3C057ULL, 0x0F6B649B16F38A68ULL, 0xAF4091CACFBD4FEDULL, 
            0x0F817D143BDA544AULL, 0x2B3C650B5A2E2731ULL, 0x7CC8299036AD28F5ULL, 0xC52664A064BD12CBULL, 
            0x3B36D3555F5BE7E8ULL, 0x43660C51E93A4188ULL, 0x671B76AF38294F8CULL, 0xCB073CD480FA3E3CULL, 
            0x097CC8DA3021CA5BULL, 0xF2234C799771E321ULL, 0x700DF4ADC26DDAC3ULL, 0xCF9D3339076D2190ULL, 
            0xD05B9C6ED28FFAEDULL, 0xC50200686E65AD27ULL, 0xECF814DF633918CFULL, 0x38A280A54054265AULL, 
            0xDB1A6AB28FCF2A9FULL, 0xE8B6B16F93BA6932ULL, 0x1945B76867D744ABULL, 0xDBA12A4AA36CD610ULL, 
            0xF7D41C1CB91115FFULL, 0xEEA63BC56E681BF6ULL, 0x41EFF60CF997F6BDULL, 0x10C334DACE6D5D56ULL
        },
        {
            0x840861367890BD2CULL, 0x4B8098DAC2C04503ULL, 0x36D44636A4731E70ULL, 0x5ABE01820295236BULL, 
            0x80B101F13B42A482ULL, 0xACE1348B767B46CFULL, 0x788A366430882FE7ULL, 0x467397AD776342DEULL, 
            0x0A121BF6B8173CE3ULL, 0xA213C84AD9FC13D6ULL, 0x78092C57C2567751ULL, 0x8D5BCE4DD72F403BULL, 
            0xFA620F2064DCDC11ULL, 0xE6B9B072A98881C9ULL, 0x82C93FE1C44AA161ULL, 0xFF5AF294B72CF706ULL, 
            0x771522E2A083A133ULL, 0xAB4D8CE2D3FB4125ULL, 0xA4A4766D8DDA5856ULL, 0x0AD5272F490062A5ULL, 
            0xD92A2543B845EA2DULL, 0xEDBE7ECDAE131811ULL, 0xA1C0A8EFF6734409ULL, 0xBF3F9312C8BAA607ULL, 
            0xD654AA3C8A54410AULL, 0x8001E612B2595416ULL, 0xF896DEFECFC9517FULL, 0x7C39B5E23274A1EBULL, 
            0xE04BDE1DA25846A7ULL, 0x8ED09CF9E638DDDEULL, 0x841B990AFCE34C2AULL, 0xCC7B870DF3E17F87ULL
        }
    },
    {
        {
            0xA1D5003ED8EE86E7ULL, 0x0EBD970F5B3EC907ULL, 0x8EA5F877DF14E6DFULL, 0xD89AD9179BB2ABCBULL, 
            0x9F3F73B497B62058ULL, 0x57E7997C65EB4624ULL, 0x541DF75367405CC9ULL, 0x2223E0E52A157FA4ULL, 
            0x1E314FD69B126D7AULL, 0xED47BE937CF8F8DAULL, 0xB884AA2E8D8922DFULL, 0x3A5F570C5A1F6DB1ULL, 
            0x7B0AD6E32798B72BULL, 0x6311F605A740E0EFULL, 0x2E70DE4BD59366CAULL, 0x7E61445C80F8581FULL, 
            0x18CCC2B5E140FB65ULL, 0xE4DF53394A52451DULL, 0x3BE529F3958B719DULL, 0x3DDE6BE0324B8C58ULL, 
            0xFD03E6010396D208ULL, 0xB7A823BB247D7FA7ULL, 0xB3C39F924EEFFF1EULL, 0xC4CB659084FC34BAULL, 
            0xB80B77AEB687BA03ULL, 0x5F66EBD69759F9D7ULL, 0x3F0B5F67E8824B1CULL, 0x8577419E871148FAULL, 
            0xD7F86DD643D51719ULL, 0x3DECFD3F461CFA00ULL, 0x14B61F109CA9E1E6ULL, 0x78BDC9AF98893368ULL
        },
        {
            0xB16FC1847FD77F05ULL, 0x86B4DAECD915F504ULL, 0xCFCCAD493D9F827CULL, 0xC6667E57622EA54BULL, 
            0x857C0A4F4A624C78ULL, 0x6EFE9F50CBF9D680ULL, 0x525FD2F10C9BC23FULL, 0x23B1217F5874CF00ULL, 
            0x03EB7ABA407F7477ULL, 0xA371ED7F2AEF6A9DULL, 0xCBB2EDA699FBC151ULL, 0x0F747FD2451BEDDDULL, 
            0x95D32C54DF9DF7E3ULL, 0xC681E14B54702892ULL, 0x8DC8CF90D9F588DEULL, 0xAE958F244FB844B6ULL, 
            0x8720B5A21AD8D6C9ULL, 0x7E86C3C4E61A95BCULL, 0x67CE43070FDBE2D5ULL, 0x3C7C48484F289C5FULL, 
            0x0827E24D9731A6A9ULL, 0x29E2014EB56AF90AULL, 0x809104B1A8F1AAC3ULL, 0x3E2996B9E1D03731ULL, 
            0x94107F77A6C75EFAULL, 0x8C44005A9840E817ULL, 0xBCBD6B0D99F923F2ULL, 0x5A09F38973DF929DULL, 
            0x0990ED4C77950D7EULL, 0x19FFFEA6542C8EA6ULL, 0x070AB75227320310ULL, 0x6E51062BCE1BDFF6ULL
        },
        {
            0x30B244FEF45ED292ULL, 0x8A8D4D492D5FE8E9ULL, 0x3BD30498F6061FAEULL, 0x157D71E21ABAFB13ULL, 
            0x6DCB1CFED29F6A8EULL, 0x87C45562544F67F9ULL, 0x5D74B3775211A16CULL, 0xB85D7E49A3F9CEC4ULL, 
            0xB01D5A32C47B7EDFULL, 0x6F218ABC83E0B3F2ULL, 0x6D9316A5FF4A36BCULL, 0xEA52116B6BCBB4D5ULL, 
            0xDA6787368C75ABAAULL, 0x7FF0980F7163D0FFULL, 0xF12C333F9D998826ULL, 0x319D8F84B7525425ULL, 
            0xE2951B8512FB3E75ULL, 0xB508A49318E0DC0DULL, 0x96043C011BA5164CULL, 0x87C4D3679A0836B1ULL, 
            0x94BC0556E319AFC0ULL, 0xBD2A0F1EE769777AULL, 0x9EBD33DD3E733754ULL, 0x1C93F7724B15D057ULL, 
            0x79AC0C507E11749CULL, 0x4DC56A0F48EDBB54ULL, 0x3C97A4855CFCDD9AULL, 0xCFCC957376392896ULL, 
            0xC3A2EFD7A1CF5EECULL, 0x5BC45D4CC8951F48ULL, 0x8E2224CF3140DA98ULL, 0x7DF796561648CA6CULL
        },
        {
            0xE24BB20B40258741ULL, 0xCF10139B6849BA99ULL, 0xBE1A378AA9F873C2ULL, 0x4CB445D6B309D0E7ULL, 
            0x911920D305B35233ULL, 0xE507F6DCD7E3AFCCULL, 0x726745B4A9224D23ULL, 0x99F8A68CA30817CCULL, 
            0x9379328ED7B03164ULL, 0x30FB6E55F17957E2ULL, 0x9365015F52F0EF19ULL, 0x02178711981B5C82ULL, 
            0xD4E0C0C72706FE08ULL, 0xBADEF7959E928DF7ULL, 0xD260A4C9A4073EC9ULL, 0x74FFA68AA75E65F6ULL, 
            0x0770B151989D99D3ULL, 0x5C1603779B3621C1ULL, 0xD3738C67CC9A996DULL, 0xD9C80CA43BFDE188ULL, 
            0x04BE462CEE9D1CB4ULL, 0x04073C7CD0BC57F6ULL, 0x61206DA374D153CEULL, 0x1CFA1C31D8BBE6B2ULL, 
            0x397658B28113E10DULL, 0xE606651AADF72D38ULL, 0x0EF5B458CC39545FULL, 0x106D86855A2518B1ULL, 
            0x9FFBD6F0C7729437ULL, 0xE01108F64D20BD9DULL, 0x2889B365AF6AA704ULL, 0x50BB3800BC4B8D21ULL
        },
        {
            0xF7C798DA9688A3BBULL, 0x594BCED3B1297305ULL, 0x4AA84E802792206CULL, 0xC66A75936BA14430ULL, 
            0x1AE2CA479AD416BEULL, 0xDFA650C3DB4B242FULL, 0x76D9510036D07D54ULL, 0xEB6A083B795D9A8DULL, 
            0x06CB9BCD2AC046B9ULL, 0x06AC1B42452F85BBULL, 0x4EC8744C49DB62E7ULL, 0x3A6780AB0CFD57E1ULL, 
            0x5B605BAC283040E5ULL, 0x0CDB4502EABDA2E9ULL, 0xD6E0E1C8F8E9E80DULL, 0x1B7218D851383D58ULL, 
            0x2C0D63C9512AA3BFULL, 0x4F16006B0F8CF0F7ULL, 0x1A12908A9C1A796FULL, 0x76DCBD07EDB3A6C9ULL, 
            0x3D030DECB24C3F65ULL, 0x59ADFD1D84DE1719ULL, 0xBD6A027663D00AF1ULL, 0x7D976BBDED370C30ULL, 
            0x6C549C402026E98EULL, 0xC1248A85CC53F692ULL, 0x7321FAD8C95FEE47ULL, 0x65D91390EB42979BULL, 
            0xB8992EFD876DF8BFULL, 0x835EDA3FF2FA02AAULL, 0x1C65A016ED26348AULL, 0x19AA5058ED43213EULL
        },
        {
            0x5A3563E8CB39284CULL, 0x1313949043B2755BULL, 0xE105E72FAABFE78CULL, 0x79CE20F1F1BB02F6ULL, 
            0x01E1261FCD8298AEULL, 0x0B8E99A59277192CULL, 0xD921A0CF2093E94DULL, 0xCB5CB3D420E25069ULL, 
            0x872DB6BF7F813270ULL, 0x56B9AADF66ACDDC5ULL, 0x45711C812AF7C922ULL, 0x98AD9CA4DC5C5DBAULL, 
            0x93232802DE8DB21FULL, 0xFBB6410EDC6011DEULL, 0xB0D556F9F6CD88A2ULL, 0x9397A3E3603403FCULL, 
            0xF9AC9ECB0B3A8EE3ULL, 0xADDCB6F171534D0EULL, 0x43626532D5933878ULL, 0xB573810C49F3CA7EULL, 
            0x5032D9193DF80F69ULL, 0xE57384E0983747A0ULL, 0x06E1E8B51477FC8DULL, 0xB8D80AB1523253E6ULL, 
            0xF84B8283FEC5E9B8ULL, 0x68F252C0843843FFULL, 0x00CA895E86281878ULL, 0xD46A8DC430717929ULL, 
            0x1839D7FC1BC4FA09ULL, 0x3DA9962A6EF3A292ULL, 0x0733BB65092D608FULL, 0x13B31693CA65E8EFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseEConstants = {
    0x564B8F6E43597F64ULL,
    0xDEEDECA76066CD6FULL,
    0x458242E1263D7C53ULL,
    0x564B8F6E43597F64ULL,
    0xDEEDECA76066CD6FULL,
    0x458242E1263D7C53ULL,
    0x447E06F85B43D455ULL,
    0x2761C52DDE49972FULL,
    0xD3,
    0xA3,
    0xC8,
    0x32,
    0xF5,
    0x64,
    0xD8,
    0xC0
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseFSalts = {
    {
        {
            0x8416E1186B42F68AULL, 0xAFE5E322C277C7D6ULL, 0x09A257342046017EULL, 0xFECBB2ABDDF0E1C6ULL, 
            0x51BADDC2724D5EBAULL, 0xBD70D17852AF1FBFULL, 0x2FE46ED4F22BC3D8ULL, 0x3CEB6D5A088D9523ULL, 
            0xE2B044E854A87137ULL, 0x4B1B08389FE464F8ULL, 0x033A6A0F3BC16D8EULL, 0xFBB0BDEFAD620954ULL, 
            0xEE4E95FBACA857E5ULL, 0x89F79F12E53B33B1ULL, 0x84906C402D46B451ULL, 0x8CA3E635AE1A7B46ULL, 
            0x2DB3BA159FBD086CULL, 0xEE3BED0BE54B7BABULL, 0xC134D65F25B638DBULL, 0x5C05A0950E1BC282ULL, 
            0xA28DCD6E99C4DFBCULL, 0x7CE94429A54DE59CULL, 0x7C2EE4F42B5FA2FAULL, 0x680867C8A2CA72CFULL, 
            0x2C07D464D7B84B1AULL, 0x3BA9B760C76F64C3ULL, 0x02454583B9CFFE6EULL, 0xDC034A891B88D470ULL, 
            0xF34B1198F0AF9AA3ULL, 0xCD6E89CF14BBFD27ULL, 0xA8C26F3FD3ECF31FULL, 0x11671231A2D5888AULL
        },
        {
            0x2AC63F4367AD4381ULL, 0x13A7A2392A3201A0ULL, 0xADBDBDDF46BF0D1BULL, 0xE5D46F1C61F362B8ULL, 
            0x16D70EA211EF86A4ULL, 0x634F700633DA9C46ULL, 0x98072A891CCE849AULL, 0x20AAC6829F612F1AULL, 
            0xD16F8A4C6819CFA1ULL, 0xEA8C6E78B0DC19B4ULL, 0x4058F6DBE1AF8FECULL, 0x0F654AF812ED1A67ULL, 
            0x17729D2AA34A7CA9ULL, 0x13AE70B199EFCE94ULL, 0x0D5B84FF109B37F1ULL, 0xBF626DA24D2FC7B8ULL, 
            0xABCBF0FA97D8098EULL, 0x4EE8691AAC2A5659ULL, 0xE2C747D0B4D18736ULL, 0xC1DE400BFB95CD89ULL, 
            0x90255E462F955A1EULL, 0x32B0F635E58635E8ULL, 0x0EA16AB34EB85101ULL, 0x08E3FAA580714255ULL, 
            0xEFF1E0ACD42C02B7ULL, 0x5F3AA0AFA9F503DDULL, 0xB475A1F96E092E73ULL, 0x9FF7DA8BA7B2E612ULL, 
            0xE316085877F47FADULL, 0xF02B60C8749EA63BULL, 0x0FC0A375A102BF19ULL, 0xB134481499B9D190ULL
        },
        {
            0xF74C3247FF502891ULL, 0x082F53D63737C957ULL, 0x08D5A01BA2C033F5ULL, 0xE2FDD5AB47CA38A4ULL, 
            0xA5306C53EB04DD2FULL, 0x32C76C44EBF1F0E7ULL, 0x613DCC81B22CE1C8ULL, 0x341041F41719B1E2ULL, 
            0x2A641BE221AB8C1CULL, 0x6E649943B81A8957ULL, 0x7A257EEFDF227D93ULL, 0x7E745D92E7EBD0E8ULL, 
            0x46EC480A7B7C3202ULL, 0x9DEF2BF36C5C21C9ULL, 0xC020287205D03667ULL, 0x48462CF49730BC87ULL, 
            0x4E5620D2CED4A394ULL, 0xE12EDDBEF77DD372ULL, 0x0FD8B31BD1A4F642ULL, 0xA8F0EC4AEE2B1669ULL, 
            0xBD8C0A714E52F0A3ULL, 0xFEB0005493A7A8D2ULL, 0xE4F567B8912F649DULL, 0x786FA518F76F7690ULL, 
            0xB5C858D03EE77642ULL, 0x4D5CD84C1230CE4EULL, 0x4691674AB3EAD385ULL, 0x77E365DCD9D27BECULL, 
            0x0243CFD88E3E204BULL, 0xCB1D3504E634F6EDULL, 0x82B0EDD85952EBD6ULL, 0xDEF50492D22C07CAULL
        },
        {
            0x1081992F6BAED442ULL, 0xE82D1418F2C94CB3ULL, 0x2D4E824B549099CCULL, 0xF199C61ABAC580A5ULL, 
            0x70B6FF5007AC53CFULL, 0x451085CB652A4AE8ULL, 0xB58977835DB250E3ULL, 0x8F085B754EEE35FEULL, 
            0xC2277E577166C06BULL, 0xB8673988FA3846F8ULL, 0x54B87651DBE2A4DBULL, 0xCC2E910153485063ULL, 
            0x13B142CC57667B3DULL, 0xC8397D6AE29C22E0ULL, 0x99FE865C737403D8ULL, 0x43B2385811316CE6ULL, 
            0x62A836372FED5940ULL, 0x30A3B25BC1624EA8ULL, 0x3CE63CB1389BD630ULL, 0x7488515A5D61B88AULL, 
            0x2ACFA86AE3BA62F8ULL, 0x8158FE0E7F16B954ULL, 0x9E4E034A8EC1F282ULL, 0xF3F4226E5913A6D8ULL, 
            0x5A7F86E5BA85B69CULL, 0xA8ABFEFE95F9D132ULL, 0x18F3C355E2610C71ULL, 0xD57E79839C86C4D7ULL, 
            0xA61F9E79A583EA1CULL, 0xFCE108DB09CC0295ULL, 0x73ADED8827B6D576ULL, 0xF60685BC38D82338ULL
        },
        {
            0x7BC9F0453FFE3A4EULL, 0xEFBBF1EF47D7A599ULL, 0xFA8D4A0079E70763ULL, 0x704E8A771F5FA6DBULL, 
            0xB910F233A4415D1DULL, 0x00D180E5F0F20041ULL, 0xE05F5F39FE96BC7AULL, 0x2D658619712C67E9ULL, 
            0xC8FE6E9EEFE3D1F1ULL, 0xF336594BCCB637B2ULL, 0x3264A4C28436718AULL, 0xE6BF663717CB799DULL, 
            0x4613929BB1B39EEEULL, 0xE23F73FCBD313CC0ULL, 0x930490CC2E5EB57EULL, 0xC458A6F6865F64EFULL, 
            0xC7A0702C2BA4A581ULL, 0x487918DD3AF46A95ULL, 0xCFD7C694CA831481ULL, 0xD551E827705387C7ULL, 
            0x990790A0E880A477ULL, 0x993A3C2D748E7F87ULL, 0x76743C7599936906ULL, 0x26442E989814813DULL, 
            0x6A63BC8FE0E37B60ULL, 0xF531C44C78F19FB9ULL, 0x8BBC2511E189CB93ULL, 0x4B456362262FFC7EULL, 
            0xBB5F01D6A982E17CULL, 0x483847B938FC9441ULL, 0x970EF3999539317AULL, 0xA454A7BF50A334D9ULL
        },
        {
            0x0389DB3B6535D186ULL, 0x52C6A724D9462043ULL, 0x572E5EFD1F11E317ULL, 0x05D75FBB83F71D76ULL, 
            0x3A11CC3D1A628CEFULL, 0x09D01D1C38A2DBAFULL, 0xFB3A1A05AAC11A3DULL, 0x2CB8158C626EA201ULL, 
            0xC9031470A3465587ULL, 0x3F0687A9DAAC02A7ULL, 0x064D0615F1E5D3B6ULL, 0x2A17A5B31016215DULL, 
            0xDC5E940613CF2E0EULL, 0x8D7D3D43C2AEEF3EULL, 0x2682429F584A8062ULL, 0xE887556F22A2E1B6ULL, 
            0x2A036D64D8CA6EA3ULL, 0x14693BB72FB14081ULL, 0xE526E82AB67B7630ULL, 0xB1888C48509D8063ULL, 
            0x84466E5022D6F2F1ULL, 0x106E9A5CA63CEF41ULL, 0x0E2ABE4ED99DB614ULL, 0x3E39DFDF1AC26E0EULL, 
            0x176BCCB884C5EBE7ULL, 0xE8A7D1BA0F2EFBE2ULL, 0x8A9C919161AF21BCULL, 0xD1D939E4F951CEB1ULL, 
            0x365954E1A10EBD6EULL, 0x4E8B4F69311311E8ULL, 0xED214A973BDD7B4FULL, 0x66CE4602EAB0C4DDULL
        }
    },
    {
        {
            0x0824375757DA5568ULL, 0xAA5CD3B605EEC2F0ULL, 0x234CBFA2746E886BULL, 0xDF254D29A01EF118ULL, 
            0xC04A082EAC0654CAULL, 0x07A185CD240F6D0CULL, 0x149B1A3CA4356E46ULL, 0x4EB23E45EE430D0EULL, 
            0x1A62CF7D92BBE32BULL, 0x7FCFD0B6FE75801FULL, 0xA9A1F79EF370C7FCULL, 0x4687A727854E845CULL, 
            0xD22F2BB310F1E64CULL, 0x9E024BEE72EE5885ULL, 0xFE3487D1A94F38A8ULL, 0x58A6509AAE418BEDULL, 
            0x62C7EFA4291AAFF1ULL, 0xD1EC683461583FD9ULL, 0x13EE19FA234334F1ULL, 0x737EC7132274640BULL, 
            0xC58F2ADC4C84931DULL, 0xC7AF1242B8DA9087ULL, 0x0B35148E737C7265ULL, 0x66A61CADFAC4948BULL, 
            0x0494D9266121690AULL, 0xFAC6F127237BAC5FULL, 0xB268B31A6C592E6EULL, 0x91D373FA0C275A10ULL, 
            0x2BB46F516BE6BD13ULL, 0x5BF75AD070AE8174ULL, 0xEC97385175873A57ULL, 0x767D2A107DDB4665ULL
        },
        {
            0xDC75BAD999D54D71ULL, 0x6D1FF4B34864FA45ULL, 0x650B59BF0ACF416FULL, 0x28399AB6AE385544ULL, 
            0xDC86886648247111ULL, 0xE6CB00BC9C12EF18ULL, 0x916A610499D85AB3ULL, 0x689D157EA1FB5056ULL, 
            0x2D2FB4F7751887E0ULL, 0x66F8C597361B6966ULL, 0xDE2F9F88E9054DBCULL, 0x43555769865DCA79ULL, 
            0xAB90195A968482D3ULL, 0x5A09655D685F9EA7ULL, 0x100CA5E114CEEBDEULL, 0x646A5B85A9411451ULL, 
            0xEE2BB1F3EA2822B2ULL, 0x8730313DDB6D936DULL, 0x87534F4A15DBBD26ULL, 0xBEAFD0491BE27BA4ULL, 
            0xA8A8C32C160FF9ABULL, 0x10988A67FE6FF015ULL, 0x9E0249B9B6EA0644ULL, 0xA4CBB1B819B628A9ULL, 
            0x8CA4CB101907F378ULL, 0xC7D699DB5AA7508CULL, 0xD4F33C0CCAF82EF0ULL, 0x16BBC0C532002666ULL, 
            0xF82A908ED2DDA035ULL, 0x924DA0B5EC632BCEULL, 0x17F06B84ABDC8AF7ULL, 0x922E1619C8594EE2ULL
        },
        {
            0xDDB82C3DAE587F48ULL, 0xFEDE0BF4F825742DULL, 0x233AFC6CDDEB09EFULL, 0x5437A4F5E50BA68AULL, 
            0xC42CE649C5965FBEULL, 0xD4989B1D80810876ULL, 0x84438A147E66349BULL, 0xFFC0EFC748BB9D3CULL, 
            0xB2B95F8235597B1EULL, 0x00FBB0EB6D44F0CDULL, 0x645CE29EB0ECBEAEULL, 0xF6C47E1CC86DFE0DULL, 
            0xA73E3308A62B872AULL, 0xBD7BDA91023860AFULL, 0x751199CD8ED77AFAULL, 0x56B3EA18B85FC7BFULL, 
            0x0B60062736E691E4ULL, 0xE23BA0BAD6BFAF0AULL, 0xEDF1024C95DB32DFULL, 0xAA5B826AF1BBDD5FULL, 
            0xAF604553EB4B0219ULL, 0xC35D5E915D0C3277ULL, 0xBA1EA47D46A43467ULL, 0x27BDCB0179936BB3ULL, 
            0xC4A98BF2F709E5C0ULL, 0x8EDD3526F69570B8ULL, 0xB4A74C329CDF10A7ULL, 0x3779D9637B44C808ULL, 
            0x9FCBC8FEF46725F9ULL, 0xE018DB1089DEFBF8ULL, 0xB76E251E1AA7C157ULL, 0x66CD0E046FE8BD01ULL
        },
        {
            0x0166F246AE382082ULL, 0x25A83B00ABF398D9ULL, 0xABBD05277E45AC37ULL, 0xAFF065C4410C7329ULL, 
            0x91285A6A48523D94ULL, 0x01A93DF474EABF33ULL, 0xFD1401660D594106ULL, 0x1BA3F471D7CB61FCULL, 
            0x2EB54FCE05BBE9E5ULL, 0x8EECB0891E45E757ULL, 0x0A17C46A5DFD4181ULL, 0x7E25A7DE1DABAE39ULL, 
            0x9A00E3ED57292F28ULL, 0x9EBCF406FE756C05ULL, 0x60838DBB39B7D154ULL, 0x38846DB223A4FADCULL, 
            0x879BCF69E379E24EULL, 0x3EF9FF7E8E8C19CFULL, 0x0E4D534ED184093DULL, 0x352D1D5AD239F6A9ULL, 
            0x2EAC7A0724C48780ULL, 0x6DC8D313FAD6DC6DULL, 0xD2530CDBD921287BULL, 0xDE73F5E645447AE2ULL, 
            0x35A998F9F25FF07BULL, 0xE7FAC40589224FDDULL, 0x144EF7DC1F30C9C0ULL, 0xA802D50FCE566BEAULL, 
            0x3660126A623EFC87ULL, 0x0ACD9F8622C48CAFULL, 0x256D5A5735FEAAF0ULL, 0x0025696A45817699ULL
        },
        {
            0x0B16FE16F62313D2ULL, 0x57DC7957785BF5BEULL, 0x0FEDE9F67F2899AEULL, 0xDFAACD43742895B1ULL, 
            0x6D106162C629C5B6ULL, 0x1C15D8BE8D8C257EULL, 0xCDA62E84E85716E3ULL, 0x6F6FE118F26A5A3FULL, 
            0xA5516D015C31DE1AULL, 0xA021312C3C14C497ULL, 0x8E0690D4A9385D27ULL, 0xB3E8DC844E346ECEULL, 
            0x883F5800BADAA14FULL, 0x369A29F1D477E895ULL, 0x081AA0A8E2D6544BULL, 0x20BB8198FF2E9074ULL, 
            0xBCDDCAF45557C4B0ULL, 0x2874554283738E1DULL, 0x90F944A618570CD6ULL, 0x89876D5285174B4CULL, 
            0xCE5FD958BBFD2F8DULL, 0xCFFF8F4AB71007B5ULL, 0x174C177980C2D0C2ULL, 0xE0668C5D80F7ABEDULL, 
            0x8691181A0F2505F4ULL, 0xDF7E97C14F6677FBULL, 0x1966A443F3308BECULL, 0xA60A2E1543F0547AULL, 
            0xB7FC3C291A28AE2DULL, 0xFD239B24BA9DE7CCULL, 0xB7A922CEA9FE5E78ULL, 0xC277249CF2B3F04CULL
        },
        {
            0xE951CF427E60DD97ULL, 0xA2C8AA2055E09BB0ULL, 0x782444738A15E65AULL, 0xFF7F92F0E4039B16ULL, 
            0x0F66E0EDCED3BBEBULL, 0xA76B6AF55D542576ULL, 0xEA5A089D30289FEDULL, 0x7CC6D9C57582D3DEULL, 
            0x89349B7D920F0EE2ULL, 0x4C7772ACB27D8DB7ULL, 0x4FDBF87E12EC65F6ULL, 0x1C3BA3FA0743EA62ULL, 
            0x4F20611D92FCBA40ULL, 0x25C13052F0B20C91ULL, 0x26A4CE216C93DFCCULL, 0x14107659DD6F7B8FULL, 
            0x9185081F3E1A30E4ULL, 0x723E633E24670E14ULL, 0x5879076CCC31B6BAULL, 0xC6C44BDF6AEB52F9ULL, 
            0x770839A5DCDE7D24ULL, 0x512A7EED0C1C1052ULL, 0xDA6BC7BC0DEF715FULL, 0x2E8B19294079C367ULL, 
            0x54150B76D9046E53ULL, 0xB37A0F237DCE6E86ULL, 0x67ADA0F6251516AFULL, 0xBD8A71B28A971ADAULL, 
            0x50BE8577140491F6ULL, 0x85EA481C3275833AULL, 0x6A8A3916A28C48A3ULL, 0x38A534A7143CAC5EULL
        }
    },
    {
        {
            0x84BE968D191908A8ULL, 0x5112F54703B5DCF0ULL, 0xF0B2ECC7038FBC71ULL, 0x2F398C11DB7E6E0CULL, 
            0x1F5670264FF56EC3ULL, 0x3FFF575E1628E30CULL, 0x6702BC8C8FA0AE0CULL, 0x8BC6CFE4DFB74F22ULL, 
            0x40B3C0CD1BB3D9DEULL, 0x2B3A50A91692D6B2ULL, 0x2B01DC38ED1A8632ULL, 0xBB0FB991D72FF1EFULL, 
            0x69D711FECC0DA6A0ULL, 0xF2A5CC97A97D457AULL, 0x36D28019707CBD03ULL, 0xBD0BB2AC89DF994DULL, 
            0x856EEA9A83150AE4ULL, 0x43B289BE15147396ULL, 0xA392D84BBC2990E7ULL, 0x2E68CC1D40DBB412ULL, 
            0x586357CF62B94EA6ULL, 0x6711B24EA5E99BE9ULL, 0x4F81F7EFD1927C39ULL, 0x38D1FB30CA42D00DULL, 
            0x97F80458132CB4ADULL, 0x2E6D1D3F885F222AULL, 0xB8B62E873ABA2953ULL, 0xF62ABC0F898F082FULL, 
            0x44BCD0631FFF7E03ULL, 0xC67CD32FD68849D4ULL, 0x3C75650952BA643AULL, 0x126E4FF66D772513ULL
        },
        {
            0xE6EB901E82214ED7ULL, 0xE7430DC0891AA75DULL, 0xB0D6E6A15A2868E2ULL, 0xB1FBD6E88C5D3F54ULL, 
            0xDCC2A1B55730A9C1ULL, 0xA7E41D1B8C1BB446ULL, 0x94EBB92DF860DB7BULL, 0xBCDD6C35D711ACB0ULL, 
            0x4041D2C8E978340CULL, 0x8EAD7371D9A4A405ULL, 0x4430F0DE68C07A49ULL, 0x144422E12A15F1D2ULL, 
            0x0DF7887F8C8457DCULL, 0xC7F6F7DC32C3FDEDULL, 0x8D426228DBA60325ULL, 0xD3E137281DE7C099ULL, 
            0xDBC0DB238B5893D5ULL, 0xFC748F45207DF980ULL, 0x5AED0596451D6722ULL, 0xB9430F99B0C4CDAEULL, 
            0x429C3009A809BB75ULL, 0x176DE84FC7066F3AULL, 0x95F62FBC19E559E6ULL, 0x26E3D71A5298AA67ULL, 
            0x8FD5CE8CB208DB14ULL, 0xA02413E581EEA5BCULL, 0x54C3C34EEC93C3C7ULL, 0x39FC78F3E237E6D3ULL, 
            0xB8B8FA19F51239F5ULL, 0x609D927B3A7E5DC4ULL, 0x6CE4FB9448A69908ULL, 0x9B1980F6A56D717EULL
        },
        {
            0xB64826289F9A2A15ULL, 0xCF3CFB0367FFA3D2ULL, 0x9E23E19832A25A91ULL, 0x9A01DFA230CEBD44ULL, 
            0x24A7AB5D8794CE4BULL, 0xDB39BD87CA1D0884ULL, 0xC757C0207A3D7094ULL, 0x1B2B07D996EDB265ULL, 
            0x4F7B3834DA1A2337ULL, 0x5AAE6BC9F677855CULL, 0x6E80644A3A32ADE2ULL, 0x61968AE84680B9B1ULL, 
            0x94C78B19E68C8E2FULL, 0x2A5AAA887DE34FEBULL, 0x4ECD3749CF02BA69ULL, 0x44C267BAE31921CCULL, 
            0x32937E35B47C8DBCULL, 0xDCB68B026C93309DULL, 0xB5422BE7E05E8C57ULL, 0xABA1681AFFA17742ULL, 
            0x6995A4C8A37790A9ULL, 0xB6A7DFA2D5C46BA2ULL, 0xEDAC43C13C42B721ULL, 0x5F21BED50E6FF46DULL, 
            0x5CDF321D646F1564ULL, 0x29342B99FD7C8AA7ULL, 0x6312F7CEC40AC445ULL, 0x66421057A2AC5D94ULL, 
            0x512122C5C8F73A41ULL, 0xF71D7D095C08E5A2ULL, 0x93FC287BE0C9658EULL, 0x2A91FEFD4EFF1197ULL
        },
        {
            0xB0D2B38EDBFC7FF3ULL, 0x113685EF62B1528CULL, 0x865905684E00E46BULL, 0x4691D7A3E0F11436ULL, 
            0xB6BDEC7C8DB329C9ULL, 0x4CBA0347AC6C825FULL, 0xC9627F9BDFF31E09ULL, 0x79EBED8CF35A257FULL, 
            0xF6F4271D77DF521AULL, 0x4A5BB9E663B29066ULL, 0xC201E9FDD8144F9EULL, 0x882A31B7A4FDE58FULL, 
            0x4803E8B68553F712ULL, 0x6AD3C650246EF4EFULL, 0x35007CF79FA3060FULL, 0xFB980C4866007154ULL, 
            0x3EA8D72353D425C8ULL, 0x0BF07AF3C5CCE5E8ULL, 0x26BD232E1936BA71ULL, 0xC4D8DCBF71EEE1F3ULL, 
            0x24E90D5FE70DDDFDULL, 0x505D4A3B5FD23A79ULL, 0xC1ACACEB90CEECABULL, 0xFC36DEC8F4F07AF8ULL, 
            0x9A4F2E1A1E2745E4ULL, 0xDC51F536AD4C2DB3ULL, 0x1D579FB681022F5AULL, 0x08F78159DDC98BDDULL, 
            0xA7900CACDBCF74C4ULL, 0x76401B91FA6743DEULL, 0xEE3A9C3179B7763DULL, 0xE413B0D58B98E5EBULL
        },
        {
            0x6AB1A05CE651F752ULL, 0xAF25078B457E9EC5ULL, 0xDF70BC233989A8E8ULL, 0x29661E1EE0DC2C01ULL, 
            0x4CED4CFD6129F585ULL, 0xA6F75F3C49F10763ULL, 0xEEFB445D2A73D944ULL, 0xF639CF776CA30F06ULL, 
            0xD7F28E7B86216471ULL, 0xC9A87FBC7569E5F4ULL, 0x828E5C6563161F71ULL, 0x6FDB3B16F2948097ULL, 
            0x872E62D0580D46EDULL, 0x2331BE0042E70E0EULL, 0x626282C39033A3C4ULL, 0xD989B8D15F23E1BFULL, 
            0x9FF869859FF557E3ULL, 0x03686FACF031CD6EULL, 0x7A9FF2C17AB2BF10ULL, 0x7D6BEE11856C43CBULL, 
            0x742C47D32361C902ULL, 0x915B7AF41F1E00DAULL, 0xE24E6539B25186C1ULL, 0x82B628FDF63A7D69ULL, 
            0x38539DD06C3C2A67ULL, 0xC55C0B2BAF33CF7FULL, 0xB5856DC212E593C8ULL, 0x53645626DAAD97D1ULL, 
            0xC9B77A213EBFBF8DULL, 0x1BEDBCA98C24753DULL, 0x20E7B10B21D266C4ULL, 0xCFF882F6AF7FECB4ULL
        },
        {
            0x5CE43A6F8B59C4E6ULL, 0x1E6F20CC25C99EC3ULL, 0x089DB23382845CD7ULL, 0x4BECB37DC02D6168ULL, 
            0xF5AE00B1F98434A1ULL, 0x816A4B2229725D34ULL, 0x870E6D02918FFE94ULL, 0x3F3CE077E72A08E6ULL, 
            0xCDE60B3D62CB2751ULL, 0xCE8C51263B5EF767ULL, 0x2465995411AE6EC4ULL, 0xEA404DF283551A9CULL, 
            0x54BE9C43D5074CDEULL, 0xEF96E591C09055BEULL, 0x2501F134419D9979ULL, 0x6335E2A9C18BF628ULL, 
            0xCACA6986837DDF80ULL, 0x92EE5B701EE41E5FULL, 0xB2BFFC30C1D7A458ULL, 0x773FB8416A398D9EULL, 
            0xF466E83C11D31AD1ULL, 0xAA4BC4DFF346CC40ULL, 0xAE13BA5AE1490AADULL, 0x2117B487EB7180A8ULL, 
            0xDBC18D5C6E10C45CULL, 0xF6E01903E72CF7A7ULL, 0x444A88FB54101B1AULL, 0xE9E6E71FF46619BEULL, 
            0x98ACE3DC869E5B64ULL, 0x364B80D4C205CB28ULL, 0x68C30C2E64BE8B20ULL, 0xDD19B6DD9071BBEFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseFConstants = {
    0x8C54C96BF2FDC7C5ULL,
    0x8F8085643A358259ULL,
    0x7B6313CEF0C67F69ULL,
    0x8C54C96BF2FDC7C5ULL,
    0x8F8085643A358259ULL,
    0x7B6313CEF0C67F69ULL,
    0xCE8222C0B755BE01ULL,
    0xF899BC7A81D66CB3ULL,
    0xBD,
    0x28,
    0x8C,
    0x6A,
    0x80,
    0x6D,
    0xD0,
    0x62
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseGSalts = {
    {
        {
            0x5C216874F76DC9A7ULL, 0x938146BB97E0729AULL, 0xF94097F9AB621282ULL, 0xF84A3602A828C175ULL, 
            0x61263AF589523444ULL, 0x3D484CB37BC3B9E0ULL, 0xFD572208ED2B9EC6ULL, 0xBA2741B590FAE9A1ULL, 
            0x9808406300159337ULL, 0x4DE29765A94BA7CCULL, 0x2F5C8DA05607802CULL, 0xBC85BE8614846D9EULL, 
            0xE9788C67230399A2ULL, 0x3B88F8896E4FC1A3ULL, 0x763843880463162CULL, 0xB80F3171D1E993F0ULL, 
            0x6C93509E3E7BA5C4ULL, 0xE64BECEC0C86CDF7ULL, 0xD39BB2F1CFF38B04ULL, 0xED3361CAF43F343AULL, 
            0xEB113A0F80C9515DULL, 0x1F6012117B34D0F3ULL, 0xF35FF32D841C63CFULL, 0x40F5F18747432F41ULL, 
            0xE97DA7425199D5ECULL, 0x562EC030BE566C24ULL, 0x9F105255A6177847ULL, 0xA39EBC1C971F0FD2ULL, 
            0xCE22401A9CE691B8ULL, 0xA315C6F9A7CCC0E5ULL, 0xD3D8D0C714529B40ULL, 0x5D59A0CC0F0FC0B0ULL
        },
        {
            0xE6F450A9C6D28BEFULL, 0x05FEAC047B2291E2ULL, 0x934ABD5E58DD78DFULL, 0x15A97FB6FAE24660ULL, 
            0x8F7CFF7AD1680507ULL, 0xF48D28B954BAB6E4ULL, 0x46E9DDFD7EF5F891ULL, 0x71B4674BB390517AULL, 
            0x3C5DBC67C582B089ULL, 0x2E0E9426077A58FCULL, 0xFB1F648D08DCED7FULL, 0xBC37FB5EBAACD016ULL, 
            0x00E3824EDDFC7D5FULL, 0x81247A81BB2CF6CAULL, 0xC44153B7984BE200ULL, 0x8C6F51286430ADB1ULL, 
            0xA2775F51F2F01317ULL, 0x639353B44C5FA8A5ULL, 0xE74A8A245395B8BBULL, 0xE2BCF54CF01F4E19ULL, 
            0x7070349CF4732B3AULL, 0x252D0ADD74D1186FULL, 0x95699EADD60F4084ULL, 0xB20B1B5E9C665ADAULL, 
            0x0D91BCC26030F3E1ULL, 0x1708B1E8C886754AULL, 0x750DAE3224918B5FULL, 0xBCB589BF52839867ULL, 
            0x6B1DDF4680F51001ULL, 0x47A7851DDE336A74ULL, 0xF319727AF0324E9BULL, 0x038E55862F46D001ULL
        },
        {
            0xD6324222E6371222ULL, 0x20E12F508D285A21ULL, 0x15CFA467FCA0B73AULL, 0xF343C06B777F0AA3ULL, 
            0xC30BA914E86564A7ULL, 0x8C5E5ACC9E9E574DULL, 0xCDF5BE7A711E14D0ULL, 0x024CA5792D58BD77ULL, 
            0x88AE824F39AF3699ULL, 0xE6D340E778D220B7ULL, 0xC2BD9D448821C83CULL, 0x01A1D0D79B24FD33ULL, 
            0x0A2FC828A569A06FULL, 0xA71978ACA20F5A5FULL, 0x92281BD9D5117568ULL, 0xA0E1A03BEA684D83ULL, 
            0x2CB3638B71BAF5E2ULL, 0xAEC1C5A7B2F2493FULL, 0xF7316D65E3D538C4ULL, 0xA8836A7DE68AC056ULL, 
            0x5933A7B7090438B2ULL, 0x1CE53F069F4004C7ULL, 0x1D8B1CDBB59C5160ULL, 0xAEEB2FA95E63824CULL, 
            0x173A4CDBC17BECECULL, 0xC44CBE6B63821D62ULL, 0x0BBAB0A9F21FD8B0ULL, 0x7DC8B3C6A01C1CC3ULL, 
            0xF87F25229AFACAA9ULL, 0xDE4F39A8798F2436ULL, 0xE5A27ED99A69105EULL, 0x594CA4F3B3CF56F8ULL
        },
        {
            0xE7D6236B77FB7CB5ULL, 0xB51200B813A268ADULL, 0x68067D1D792E9A6DULL, 0xC7CC46E11895EBBDULL, 
            0x067FCA430875CA79ULL, 0x2DABC1D85C7B8E51ULL, 0x7885227215F14261ULL, 0xE5FD37D75D3A6631ULL, 
            0xC405B7564224F854ULL, 0x4E8905B1152CB5F5ULL, 0x8085D69FF2C140E0ULL, 0x8EEB2CBAB8101FF6ULL, 
            0xA1857403F1096A99ULL, 0xEA1AF2CF27495138ULL, 0xC9EC89059E24A7A4ULL, 0x82AD2DD678D2D338ULL, 
            0x45BFC0C99E9AA187ULL, 0xBF127BDC2E9CA92EULL, 0xCB400BF957A5E33FULL, 0x1183ED8CB1632883ULL, 
            0xCD1EC34089E2FA1BULL, 0xF9AD1E3DAB0394EDULL, 0x4D6DB7F952B1B8BCULL, 0xB621045B27D0C7ACULL, 
            0x080A429F36FFB799ULL, 0x9D7F02006428A4F1ULL, 0x3D716A3860E8E0F6ULL, 0xD31FE31431CECC0AULL, 
            0xB506F1C546A3F5CBULL, 0x0902CA3D58777F06ULL, 0x94D589FB74D46F3AULL, 0x68E1E758316E29C8ULL
        },
        {
            0x8711BFD32A6F0D9DULL, 0xD881417F10D3C962ULL, 0x78B0CFFB2F619981ULL, 0x33AF7D2B070E604DULL, 
            0x6399A8AE257F0326ULL, 0x8F316A2AF76AEB58ULL, 0xDE0D0B2A37B6BB99ULL, 0x426DC375EB5452B4ULL, 
            0x5251DEEC07C0474AULL, 0xB5283C52CAB81922ULL, 0xF2B6BA2C7E28A7F3ULL, 0x2765468BEB4E9FF4ULL, 
            0x1E9F4DDCE3BFF957ULL, 0x4BC515FCD93C8E02ULL, 0x621CA1D9AD763563ULL, 0xA6C2E1292C7CB587ULL, 
            0xD7B827104E3E5F20ULL, 0xFF2A7A98B371ED1CULL, 0x55FDE4CF875CB645ULL, 0xE806F19533E22300ULL, 
            0x0D9364CC1BA2FE88ULL, 0xEE27E6E77A075E51ULL, 0x8DC611839DFCF3B4ULL, 0x176B44A435B62822ULL, 
            0x5CB6F9F593FDE233ULL, 0xD038C93ED1D6A801ULL, 0x6145FB8A277549D2ULL, 0x72E2E5E925B6ED43ULL, 
            0x27EB86D0459F6705ULL, 0x7C9399334E1D101BULL, 0xA967B49DE628F116ULL, 0x5AEA8609487D50D7ULL
        },
        {
            0x56CFF64FB0E75F27ULL, 0x383FFD5785D45D8AULL, 0x943E651118F7F14EULL, 0xB830E0769C2C6D17ULL, 
            0xA23BC83210C8B8E3ULL, 0xBA9B7805837C4383ULL, 0x30E9A146228D5A5FULL, 0x7CC82E11B903C9A4ULL, 
            0x4EF7F237146B83F5ULL, 0x0B1D7953F5230158ULL, 0x157783D4E9C795B5ULL, 0xE758775406DC5386ULL, 
            0x432F5778D1A43BC8ULL, 0xAE57F87B5FA89CDDULL, 0x584762AA865206A7ULL, 0xE3B552BBF8FD7D57ULL, 
            0x817DFA3CEEA9A889ULL, 0xADAD93B867C07A41ULL, 0xB8C246EAF51ED347ULL, 0x9B653A3E2EE77BE4ULL, 
            0xACDB4BD08C5D078CULL, 0xE48604A3C7D14CEFULL, 0xB862F724445B58A6ULL, 0xE1342E01BB399DC0ULL, 
            0xD732110D79E47E21ULL, 0x7B73A2BD7E4F9B4BULL, 0xEEEB1CD4A9731A12ULL, 0x6AE548C6327300B5ULL, 
            0x30CAD9ABE54DA294ULL, 0x21E8ED69B58EE645ULL, 0x1006594583317B54ULL, 0x9DA880715A710893ULL
        }
    },
    {
        {
            0x83257929834B20A9ULL, 0x0F190F44DF96C531ULL, 0xE37085F3D6650B07ULL, 0x1B87A8A7B4EA97E2ULL, 
            0xC5575F1E91251F4AULL, 0x5A0137C44EB05DDEULL, 0xFF6834FE4403F2ABULL, 0xA4355C4D0221CAD8ULL, 
            0x179EC8D6D8B9655DULL, 0x26A2249E36F2029AULL, 0xB1EC532BFF3494D7ULL, 0x4512AC51E539625DULL, 
            0xC1C0EA1E964F40CEULL, 0x43024A693E71B111ULL, 0xE9A13E0EB5D188CCULL, 0x8DE60F708BE634B0ULL, 
            0x745E4BF5AD75DB4AULL, 0x4C5ADBF2A87FAC1CULL, 0x26EF056CA88541E3ULL, 0x9954FDB093CD221CULL, 
            0xFFBB985F12106C6AULL, 0x5745D10AF5DC7683ULL, 0x2635483274A5D8EAULL, 0xB85ABCB94BF8C9E5ULL, 
            0x4755A3B8D8D0B904ULL, 0xF3F3B17516D64030ULL, 0x19C60F862A1DBAF9ULL, 0xDB59FD9F142B79F3ULL, 
            0x7B9E0DA2CA2264C7ULL, 0x4BBB53DF28E8A1FEULL, 0x5E9F090E09F48B31ULL, 0x7379788F3592CDB7ULL
        },
        {
            0xBE9C141723945592ULL, 0xD97C13FB4B728338ULL, 0xF9625C8F2E058B03ULL, 0x6967038E0A2F2B30ULL, 
            0x3F544819BAB4D317ULL, 0x2586BB2B565A75CCULL, 0xC289F3FD0B989C28ULL, 0xD2A55A146B2AA9AFULL, 
            0x48897E1F342C887BULL, 0x85AEF2FB86F0140FULL, 0x56A78224E8448225ULL, 0x3BE5C0EE8EDA2A6AULL, 
            0x038C44116C4958EBULL, 0x224FCF9C79BBC238ULL, 0xB083CCB58F6403FDULL, 0xFD4563B69D78D64AULL, 
            0xCAB9D66AABBF16CBULL, 0x381C58BA97D4D096ULL, 0x2695ECF046A1F851ULL, 0xA13226821A18CA2CULL, 
            0x0874190F751D20A7ULL, 0xAE744C1F95F8CDE4ULL, 0x054EB2079294A02FULL, 0x48A39CFF1919AF6FULL, 
            0x298F3B148A99A5FCULL, 0x6AA04DE4A126939CULL, 0x351BA63264940270ULL, 0xFD3681CD8FF6E159ULL, 
            0x5480876D790A1A7DULL, 0x164A08BED9BB8651ULL, 0xAF816BC0DB03E315ULL, 0xBB0DD933B8E4EE61ULL
        },
        {
            0xC5306DFF8C8F1D06ULL, 0x9CA2C38125D596B9ULL, 0x6839C696EC408B0DULL, 0xC36FCED631A11A1AULL, 
            0xE3FF25D8E18E9297ULL, 0x4BD3692A95764186ULL, 0x12DFDC3A92230503ULL, 0x34D0ABA3A08F0FDEULL, 
            0xFB7EABEFD3368FE7ULL, 0x77FB2009402E5626ULL, 0x0A9349929BE9457DULL, 0x099D2F8933E782E0ULL, 
            0xE9C61BAE429ADF61ULL, 0x029F3B34938FEEF3ULL, 0x57F6CDFB76EE0D18ULL, 0x34FA7B8BB228C3E4ULL, 
            0x9EB7194388F10288ULL, 0xF09D0B895F981C61ULL, 0x1C490D6F1F35AE54ULL, 0x45E97B2E271AD2A2ULL, 
            0xC881E5C0AEA606DDULL, 0x0323CBF29156A184ULL, 0x1993027ABD5E3B30ULL, 0x1A9C0724A1478D09ULL, 
            0x939A37EE48EF4F43ULL, 0x76B021C93E6D404FULL, 0xEB1A225CBAB6E510ULL, 0x3C55A0389609D146ULL, 
            0xDF8A21BD1BFAEAFDULL, 0xE1AFE252CCEAE728ULL, 0xBCA2169865AE859DULL, 0xEB3DBB3A987EC2A0ULL
        },
        {
            0x6240947BF3165D82ULL, 0xDBA19615FE9457B7ULL, 0x96C770030525AB0FULL, 0x2F11E2A83DB50470ULL, 
            0x902A13BBDF5766ECULL, 0xD5810203BC117AA8ULL, 0xAEB9FD9B83204096ULL, 0xA6C04FC126764ABEULL, 
            0xFD473D5E619E4252ULL, 0xADAB35FBE0EF6CEEULL, 0x0712A7F159E5A39CULL, 0x5BCD5334426F1397ULL, 
            0x204E454ED889700FULL, 0x2713E1EDDDD7CFF0ULL, 0xE7A7649591ABD3C0ULL, 0x667CE4B2885214DDULL, 
            0x0CCB298E5AAE1009ULL, 0x3215910E442A7B47ULL, 0x7FD0E924A5A41F0EULL, 0x40AE212B31573FC3ULL, 
            0xECC964C7B4D6D128ULL, 0x962A86DB66C6DF78ULL, 0x65809DFB437D910EULL, 0x15DCC0651C2BBDF5ULL, 
            0x1E6795F8FC1E2856ULL, 0xCB40138F800AF1FFULL, 0xDBF49BAB37468FADULL, 0x31F112167C3A9734ULL, 
            0xB655E57E36740CA0ULL, 0xD29147B8FF54BFF9ULL, 0xCAE29E1F437DC83EULL, 0x14CAC62BAB3A22AFULL
        },
        {
            0x7E0974101A40F358ULL, 0x947DB29127310B82ULL, 0x132D972B18602DDEULL, 0xD3486CDDE2D58130ULL, 
            0x5255F33EC0D04FC9ULL, 0xADA995D70EE9A5A1ULL, 0x0595BEAA08CB6E0AULL, 0xBA6E0459D41CD5B7ULL, 
            0x9476DD95654A44AAULL, 0xC7987C7B7C5B9BF8ULL, 0x642360D9C38666B0ULL, 0x76E4CDB79290D3CCULL, 
            0x918FEC3422713A89ULL, 0xB1B0F18664CC4603ULL, 0xB6294312629DA1ECULL, 0x307594CC7FD447C3ULL, 
            0xA6A57E38DD957A97ULL, 0x1416BA95EE8818B0ULL, 0x249C124094D37232ULL, 0xBB1B650DFE0276B5ULL, 
            0xE761B260858F8143ULL, 0x276125624081AB16ULL, 0x3C8DF3937DC833A0ULL, 0x114812CB61944780ULL, 
            0xA8A965FCE81212CBULL, 0x8F7CFF770AF817D4ULL, 0xB56CF9D9F6F88FB7ULL, 0xF0896271A0CAF664ULL, 
            0xC0CD39A79A27C21FULL, 0xCDE98764D7FDBD3DULL, 0xB821D06F451E97FFULL, 0x9BF36B44C79E9DCBULL
        },
        {
            0x48427D825BD99798ULL, 0xACD6CF42A2FB767DULL, 0xF66B5301F9E0FFEFULL, 0x0B651E08A2337DF0ULL, 
            0x84D9EC91F4A9B8F2ULL, 0xB2A4A515CE01EEA3ULL, 0xD68F762BC81F0C06ULL, 0x242ED93A3485977EULL, 
            0xC0BFE1169F142683ULL, 0xAB17D2C7B8821302ULL, 0x9D192D65D67CC035ULL, 0xABEC5995087D1C35ULL, 
            0x891A5093469DC588ULL, 0x12277971FCF7A12FULL, 0x094187AD81D8A9B1ULL, 0xFAFEAC2DE131C554ULL, 
            0x470C96CBE1EED309ULL, 0x295262CD33D82772ULL, 0xEAB895869D3FD859ULL, 0xC3BDCA962C97DA6BULL, 
            0x8242C2FA094F4573ULL, 0xDD3F0B86E2696D93ULL, 0xE6BACCA9844E2830ULL, 0x3CC9A96E3320A770ULL, 
            0xEE8CBD36A17ADF67ULL, 0x8832A35C1302887BULL, 0x4342A36D4C90D96CULL, 0xE653D626EF80D102ULL, 
            0x0BEB2B6DB8994827ULL, 0x274987FA350DB582ULL, 0x7E46387D357CED6AULL, 0xD03117CF19F260BAULL
        }
    },
    {
        {
            0xD293E191671BEA35ULL, 0xA5978C73843205B0ULL, 0xC67ACCE04D18A9CEULL, 0x4466B7046A80918EULL, 
            0x3AA953BE41922CF2ULL, 0x080654A7D63559E1ULL, 0x1FA9A5798AFA3C02ULL, 0x3835BEFF4A1F00AAULL, 
            0xFFAA6B6E6D4019D7ULL, 0x6D4AE9390D89EA1DULL, 0xA8936E29F6188A12ULL, 0xF4B10EDDCB92A461ULL, 
            0x26031E1A838C2825ULL, 0xE0EA90F253EE1A47ULL, 0x02EDE850CF4073CEULL, 0x237BEEFE8DFA42D3ULL, 
            0x3AD551601C4BB1B7ULL, 0x69BE557A83A56ED8ULL, 0x00DFC1589BCD13FEULL, 0x44278A805431DE74ULL, 
            0x0B41CCCEE16EF286ULL, 0x074F5A0F33D0A940ULL, 0x8ABDC41B9A401D6BULL, 0x997BDD74B93EA226ULL, 
            0x32F4B901A67106A0ULL, 0xCB37889AF913F8EEULL, 0x7CE257768D5E0CE8ULL, 0x38D2108E3C92FEF9ULL, 
            0x92B553BA121F1C08ULL, 0x694391B04400D529ULL, 0x74CE65E27E047D8AULL, 0xFBCBDD238C07B35CULL
        },
        {
            0x9296573EFCE2924FULL, 0x1F0B5C6898BE6BE2ULL, 0x3F963EE1F1B7319DULL, 0x8720F743F9504172ULL, 
            0x321BC9331CF3CCF0ULL, 0x42DF1DCCCC272FC2ULL, 0xBFD4A9960D3CC2FDULL, 0x6E33CB6D0F195845ULL, 
            0x3E4E2446FE5B28D8ULL, 0xC4FBD7425CEB63BEULL, 0x675638F6C5E12278ULL, 0x4113A54ACE689323ULL, 
            0x49556C23F25639A3ULL, 0x2F3B91081EA8C736ULL, 0x9E7CBF7981C03920ULL, 0xC6EECDD964E987E9ULL, 
            0x2C30617CE9218A5BULL, 0xB2D75C055DACC351ULL, 0xF697337DF709D681ULL, 0x52BF687393A1FFB7ULL, 
            0x88A58895B1DAC5ADULL, 0x4CF291BDB69FC1D7ULL, 0xC76EFE261EB6473CULL, 0x62C2983491DA3F73ULL, 
            0x31C804C52E4B7DD8ULL, 0xD7B9F32C82739978ULL, 0xC72CD572B05DE499ULL, 0x9106FD31104EF164ULL, 
            0xA5C55EF5E26927F6ULL, 0x7B18D61D2CC64628ULL, 0xFF179C7547C00157ULL, 0x43712B73AF95353AULL
        },
        {
            0x43214C9E4CE3F014ULL, 0xC1B81CD91E9904CDULL, 0xA171D0AC2B2B9F52ULL, 0xD1F88F4F9BCD22E8ULL, 
            0x1BF93C5D70D88F4AULL, 0xEC91299E24A1ACCFULL, 0xCB01C4A49B185FC5ULL, 0xB9708CE3D81DBF55ULL, 
            0x353F63D4FA91BB50ULL, 0x35DCC025988800A0ULL, 0x8C1C8A5FCA7F9A8BULL, 0x6F68562502556826ULL, 
            0xF21639BBAF796AF3ULL, 0xADF38BD21CF1470EULL, 0x92278D5346EDD5F9ULL, 0x06E21357C46813CCULL, 
            0xBEED0EC9C5717F21ULL, 0x237315F33E400901ULL, 0xE9E4737ADA17DF45ULL, 0x40132B77E294DDD5ULL, 
            0x444693CC61A1BBC5ULL, 0xC9C97AA0B591E5AFULL, 0x6AA15BC129DE243AULL, 0x1E0FAEABC2C43276ULL, 
            0xA4AD592B2915962FULL, 0x12B0E61C9E4EE40CULL, 0xCD532473B7AD86DFULL, 0xF566ACA7A0A236F6ULL, 
            0xBE2BFE28488C4C10ULL, 0x30E7868D031AB13FULL, 0x223BFD340B3922A3ULL, 0x7F7481B06BC0AA25ULL
        },
        {
            0xEE893796009CF3EDULL, 0x3D13A67DCFD8AAC5ULL, 0xFDE19B7D2ACAA3EEULL, 0x7C5D7EFB5D1EF35EULL, 
            0xED01BFB57270617FULL, 0xF3CE4C235FC59A40ULL, 0x70BCFCEAA99455E4ULL, 0x5DDEDA48CDC888C8ULL, 
            0x81DF19A0939AE9CEULL, 0xD4758609B918EA6CULL, 0x28E8FBFF2C89B6FBULL, 0x9A92440FF2838BBAULL, 
            0x923E669E7F800460ULL, 0x810B6D3D291B2B0EULL, 0x9F1DB43ADD757861ULL, 0x8DFAB0A489C14CB2ULL, 
            0x946B283E22C42B65ULL, 0xAD28786EFDF1E832ULL, 0x858365F1B421DB97ULL, 0x2AAFE0979EED52E6ULL, 
            0x31116E338E30B3C6ULL, 0xEA8FB387C9F58134ULL, 0x7A3C7104FF102AD4ULL, 0x167AF4679F600356ULL, 
            0x6BDC4C2E011E1DEDULL, 0x876AF2DA8464F3C6ULL, 0xDAF4DC3D0548FA4EULL, 0xC464F83744A34F6CULL, 
            0x615E6C6D01B240CAULL, 0xBFD6E843A3136000ULL, 0x254EB52613C0E4C7ULL, 0x35B01BEBBA407502ULL
        },
        {
            0x8B3EAF038C639793ULL, 0xAEA3BE28559A8CE3ULL, 0x9EEBECB21AE58F1AULL, 0xB313E699B3976A40ULL, 
            0x0D3C1B25C5FB37B0ULL, 0x6F3C0F8B3578C393ULL, 0xB134C6999E527A71ULL, 0x9052D591DF9D4C60ULL, 
            0x0A6134633A0FE2DAULL, 0xCA3E055D3B8C33EDULL, 0xCBEB5DB8556B04FEULL, 0x8F4D3A3B5D577261ULL, 
            0x52ED5B33F1D68F40ULL, 0x53F220A33CA9D610ULL, 0xCFA02F31EAA6FA08ULL, 0x0DD438334244B923ULL, 
            0xA94436EF80209DBAULL, 0xE6E23B2970BCA93CULL, 0x2375ED85C4C8CA11ULL, 0xB2A1ABAEF5A0510DULL, 
            0x495CDAF732F7DB5AULL, 0xD8A068D316A25A1FULL, 0x87FC7F0F3E5C4827ULL, 0x5784113FA60AC441ULL, 
            0xE5343407FB39D1ADULL, 0x2C0A7BEE2B19ECF9ULL, 0x16DF6D1B577B03D1ULL, 0x1DBDA0CC4C00004DULL, 
            0xA008D9D21B7C4841ULL, 0x3636E650AC21E91BULL, 0xEB2E89B91A69D7BCULL, 0xEE56F6273D3BD0C3ULL
        },
        {
            0x2F7F77F2DEF5B2F7ULL, 0x4E3B2BC69FA84755ULL, 0x8520A085C62A3121ULL, 0xEA3AEDF9CAF57C47ULL, 
            0xD1E54F45C18B6382ULL, 0xB34C51E07EAB346CULL, 0xC55ACD23046CAA6CULL, 0xCFCA8CB12CEF300DULL, 
            0x9754D7895AD199ECULL, 0x201FB5B97845731CULL, 0xC963B116AD7D1C6DULL, 0x9494BA3F893C40D3ULL, 
            0xBE410A6F0014D2C6ULL, 0x76726920E44EF6A1ULL, 0xD2C35736B2B902A9ULL, 0x5D76DBFCF2CF41C5ULL, 
            0x4A79EA1801B8FB74ULL, 0x46C451DDB95292A6ULL, 0xA9251288C033216AULL, 0x304F07F11735376FULL, 
            0xD9DAB22CD6E46B8DULL, 0x2D9724B4689E8A8EULL, 0x516950CA396AEE9AULL, 0x3E0F86D68B282E87ULL, 
            0xD2BC87701105623AULL, 0x06FBCF20E2C5F89BULL, 0xF11CB16ADA22EEB0ULL, 0x283D1F5FECD2EE90ULL, 
            0x7BA6D44613B1C96EULL, 0x704ACAFCEC7C75C9ULL, 0x52636FF25C86D0B3ULL, 0xADFB2755D4512046ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseGConstants = {
    0xD7613ADC39A052B2ULL,
    0x598AD91E1E8C6FBDULL,
    0xD831A03ACB1A566CULL,
    0xD7613ADC39A052B2ULL,
    0x598AD91E1E8C6FBDULL,
    0xD831A03ACB1A566CULL,
    0x4CB185DB38C79E62ULL,
    0x85AFCBDA3DA2CCB5ULL,
    0x75,
    0xE3,
    0x3A,
    0x10,
    0xA2,
    0x28,
    0x6B,
    0xE4
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseHSalts = {
    {
        {
            0x863C6EC7643260E5ULL, 0x397114464B688D35ULL, 0x1D477CDA1455EEB5ULL, 0x456A42197FCA75B4ULL, 
            0xBF445F435C72D3F6ULL, 0x8B2279C9EA9CC1F9ULL, 0xD7D199BDC0830912ULL, 0x41317CFBBE8C771CULL, 
            0xB091F48B9909BB4DULL, 0x51826A7D2CAA60B5ULL, 0x83A68CAAC80CE947ULL, 0x1C8691D966FD42D8ULL, 
            0x59348C62325EA9FAULL, 0xBE049E1284AEE190ULL, 0x5E19DD83E38DC9DFULL, 0x214ABEF2B3FCF3E4ULL, 
            0xDBF12F1AF11146D4ULL, 0x65EA7CCEFD38D023ULL, 0x0E3219BD709B1C9BULL, 0x88F41DEA523EAD0EULL, 
            0x447346C12F7748BAULL, 0x9D800588E5CBA021ULL, 0x84547DB1ABD16228ULL, 0xEEC325F72E56028EULL, 
            0xDCEF4770D81F46DCULL, 0xB68CE666F323D7DDULL, 0x15824063463A21ACULL, 0x643011BAF5B31873ULL, 
            0x3D9BAC8458A113A2ULL, 0xFE33FF39B4903F35ULL, 0xC4FC6848DB658574ULL, 0x2D4D832985364A9CULL
        },
        {
            0x4F9B8A1F9A696DEAULL, 0x8838A6A8EA0142ECULL, 0xFAD34AC7E5FC8C39ULL, 0x02601FDABB506F0AULL, 
            0xD20D0041B271A35AULL, 0x99AF24935CD87DB7ULL, 0x6A646BF87362B845ULL, 0xF865076860DCBCDDULL, 
            0x2B5F9D2FEBDD09DFULL, 0x173422655505D3FCULL, 0x0B94968AA3F0E43EULL, 0x8DBA4709D3D6E5F7ULL, 
            0xB48C2062143CE62FULL, 0xB19FC7C86D38E40BULL, 0x9220F97B230E5068ULL, 0x0B6CEAD7BF1A5687ULL, 
            0xC26D5B9657C18083ULL, 0xE397B86C09E0972FULL, 0x0540832B499A7278ULL, 0x44C0A0025E015E13ULL, 
            0x93B24ABBFB970464ULL, 0xD48B64E1B5CB17AAULL, 0x0F7485221C79247CULL, 0x03CCE5FAEFFEF0B7ULL, 
            0xFC557B01D0CA891AULL, 0xCBB72DA16C760EDCULL, 0xB8792CB0B0C5AB34ULL, 0x648044E4797F29D2ULL, 
            0x0EFA7DF4707F07A0ULL, 0xAEFB5442750A5DBBULL, 0x5AA00C0B4689AEE2ULL, 0xD952F509213A4C5CULL
        },
        {
            0x9037273D21795723ULL, 0x983C1628EC8D7FC1ULL, 0xD6AC76971D9C6EF4ULL, 0xE5D202A1B09A0822ULL, 
            0x57E62FFF85C78C6CULL, 0xD706F933A9E9573DULL, 0x2A9A698E9ADB7FD9ULL, 0x15C96B1CA726E5DDULL, 
            0x387B9ABB3B3CF437ULL, 0xE1E8BA4A639619CAULL, 0xA6C39AACBB3ADD4DULL, 0xDFDC74387B7E5739ULL, 
            0x65C444A3F7CFBC4FULL, 0xEA746A92627D1322ULL, 0x0EDF85D16DC167F4ULL, 0x72A91DCC2AD47FAFULL, 
            0x80D41EA3FFE7D9A3ULL, 0xE114BAC29C3E6670ULL, 0x52DECEA1F4303B4AULL, 0xDC5133DB1DB01026ULL, 
            0xB1274F387CAD5A34ULL, 0x12D711A0CB197D4EULL, 0xEFAA4F36813B51E5ULL, 0x75A186D920BE507EULL, 
            0x0BA569FFD33B8CB4ULL, 0xB72B9AECBEAD4410ULL, 0xB4405A8DB41B3ED4ULL, 0x33B84B3FF1C325FBULL, 
            0xB2E163DB67725836ULL, 0x8A67F061B27812F0ULL, 0xCD2E43CACF532FC5ULL, 0xEB8E938758D85DC9ULL
        },
        {
            0x788A94B25C9D0D35ULL, 0x22D2B53278DB021AULL, 0xC85E4BFBFB28284BULL, 0x02EA812CCC5C39BCULL, 
            0xC34E1C668DD3EF8AULL, 0x135659864B5DBE3FULL, 0x72EAAAE7F67CD29DULL, 0x863B3CFF5F2F6A78ULL, 
            0xEDE38B876901BCBEULL, 0xDDF351D4FBCC45BDULL, 0xEA70B91D7E4B74E2ULL, 0x078AFEEB3F59F988ULL, 
            0x025425F286CF13E7ULL, 0x9675DB3568F8ED10ULL, 0xA3B95B0AC365CE8EULL, 0xBD4E7A036E9B5BADULL, 
            0x21DEA05EC569BED4ULL, 0x6657E05EA8C4190BULL, 0xFD1969CE2AFC4133ULL, 0x0A79ED444434DDDCULL, 
            0x3B406DF6CB4CC06FULL, 0x029D1CFA40C63E3FULL, 0xFE49844F9D8F8A38ULL, 0xB0872B3EF3CDBAD0ULL, 
            0x227A599C4B79D168ULL, 0x547A7F6844862FCFULL, 0x0601B7859D896B99ULL, 0xAF46594FFD86D2D9ULL, 
            0xD608E29EA0E7CB72ULL, 0x934C68724469D7D8ULL, 0x3B29FE97F2438189ULL, 0xD88BF9046F851BB5ULL
        },
        {
            0xB2B7377E61584DCAULL, 0xB70955F443628B32ULL, 0x8017F9439BB5F6AEULL, 0xE7FE45A768E93B49ULL, 
            0xDECA3DC064093A88ULL, 0xD184358E8A4073F6ULL, 0x9FDF5F60CB5140A4ULL, 0x24521EF0F57B1C45ULL, 
            0x84EEB961E668C2F4ULL, 0x6A902E48A473F034ULL, 0x2DCFF06CBC2D30D1ULL, 0x338BC2E73D3D77B6ULL, 
            0xF2AFC25A300BC3B8ULL, 0xE2C93D69742B90E2ULL, 0xC2B12B88429A74B2ULL, 0x13808873E9927B4DULL, 
            0xBDD200D7AD5DABB7ULL, 0xD76D4EB1DF970984ULL, 0xE36FA56EE88939A7ULL, 0xABB372B53CE46A19ULL, 
            0xFF142CF1D2AAD124ULL, 0xE0755E2654ED120DULL, 0x53AAEF7315B1DBA4ULL, 0x3FF4FD09978165E5ULL, 
            0x93EAB71FB755C8A1ULL, 0x6C13E8624319DB44ULL, 0x7797AD837BC3D9CFULL, 0xB5C62B93D554C6BFULL, 
            0x292CE23D15D6625EULL, 0x476D7BC6B4733E10ULL, 0x8429014D5A8DBB8AULL, 0xD236F11C5C177AFBULL
        },
        {
            0xA32A93919971CE6AULL, 0xF75CDD5E90AD94E5ULL, 0x3FDC232D62A8A9A5ULL, 0xF6B96D1452CB399FULL, 
            0x0DEE74908F735408ULL, 0x45AE04E11A0964A7ULL, 0x8ED442CB88B80FB6ULL, 0x4CC9C072DFD48222ULL, 
            0x4ED825A15E4AFBD7ULL, 0xAE6D50C1CFD86FB9ULL, 0x6A2D0FC5399BBCBAULL, 0xB453BA0138ED887EULL, 
            0xF6A7EF1706F3934EULL, 0xDC8CC92B7934A415ULL, 0xA3DA45E3A1A8D7E8ULL, 0xB01EC957967D334AULL, 
            0xF3EEA8D3E11DFC0DULL, 0xEA6DE94EE2A4703AULL, 0x40EB6952D3C4FA98ULL, 0x8A84EAAE2C41A033ULL, 
            0x46D2251781794BC4ULL, 0x8B6B0F7D428F07F1ULL, 0xFBEA20C714838883ULL, 0x82EFC4ED3922543BULL, 
            0xF59EB3857C938BE1ULL, 0x58AC14091753DF64ULL, 0x55AC0EF530BA1C81ULL, 0x2C35BC8587D59059ULL, 
            0x0701B74E932EA925ULL, 0x30A49B45857DE9AAULL, 0xC71C1F74ABA8ED82ULL, 0xDB1007CCB1F237E7ULL
        }
    },
    {
        {
            0x7546BECA200F8E0FULL, 0x1AC7561E1A4ADE4BULL, 0x5B440856CD281F41ULL, 0x25C0EE4DF7408ECBULL, 
            0x119ACE4D38DD2F70ULL, 0xAE99905317110484ULL, 0xC9A90EB8535CC93FULL, 0x5B63DD19F4C91E75ULL, 
            0x622D543E40954978ULL, 0x98E0DD3F3B728F13ULL, 0x2E880913203B3F1AULL, 0x648486F9FA20F707ULL, 
            0xFD95E796FEDC1D19ULL, 0x14E8E6A56C8D6A49ULL, 0xA9178DA49F0C1FB0ULL, 0x36A0E2744732D3D5ULL, 
            0x1E52C8B16D3BA7A8ULL, 0xF8CD7E5B4073015EULL, 0x00C8504304B4ABFBULL, 0xC1A1FF16FCFB06BDULL, 
            0xE3FC3D6F854B4803ULL, 0x029B22C64AF0087DULL, 0x1B3009E35BC10FF5ULL, 0x3BEFD88157C15800ULL, 
            0x125F4985F68598CEULL, 0x510A06CCE138EFAFULL, 0x4E56A4804A2EB3ECULL, 0xB9522CEC7DA6D7ADULL, 
            0xCFD1A2048AE7B250ULL, 0xAB44492F40F2458DULL, 0x4CCBD84118314645ULL, 0xEEAC7AD08ACE08F9ULL
        },
        {
            0xD53A946487939892ULL, 0x9D4C8538BB3E9D6FULL, 0xD3B1944E5A6CCB64ULL, 0xA110F16BF30DE8F8ULL, 
            0x8C3301B5653AD993ULL, 0x57D557972B68E496ULL, 0x30086247718B4055ULL, 0xC7119127D82D98CBULL, 
            0x921DDF1FF9B3EA1FULL, 0xB5C546E6D50797E4ULL, 0xBED3A553DFE9A001ULL, 0xF3CB2D294407F5BAULL, 
            0x42FBD9F5BBC27CD4ULL, 0x3990AF2696A48FA5ULL, 0xFF8C648F3301BCD3ULL, 0xE0154087E11617C0ULL, 
            0x41370E9DA0DC7CAEULL, 0x341819F83FA145C9ULL, 0x52F957E65F405FBDULL, 0xEE4CC8788E4B0BE3ULL, 
            0xF9D5186E98789CB0ULL, 0x29CD71177CE9C773ULL, 0x74FDE60653F3BB0FULL, 0xEDF50595652BB230ULL, 
            0x532889FF4A7AB52FULL, 0x3B3AAA7362A939DFULL, 0x6205DFAF4E700A2BULL, 0x98F91D5645EF0B0CULL, 
            0xE34F4D24B5A58E8AULL, 0xF3DFA31C50CB93B5ULL, 0x582384A59089F209ULL, 0xE41CE2410BA3FCC5ULL
        },
        {
            0x590041E0D17E4450ULL, 0x8F7202A892BB5C4CULL, 0xB1167C2F8A2DF9EFULL, 0xF12DDCBA9709BEE0ULL, 
            0x736A1FCAAA31AE7FULL, 0x58939466C196A45AULL, 0xC208FC55A357CC70ULL, 0xFF3D211D3A5F2BF8ULL, 
            0x884AA104451C3C49ULL, 0x975145239B49CD11ULL, 0x85B22C54E5C4397FULL, 0xBFDD7EFF3F7B6FACULL, 
            0xBD9C7C2104F5876AULL, 0xBCB8997362446629ULL, 0x352D0C6BD81E0C5CULL, 0xD8563F12CC7C9A9AULL, 
            0x3D0B060BEA39D909ULL, 0xC53344E01F836504ULL, 0xD90F9AF3079AFFF0ULL, 0x8ECB098ABC67B6DAULL, 
            0x4253442B3FB4C1F8ULL, 0xB06D1428447CAA19ULL, 0x926F8784CB8441CFULL, 0x8537A2FF61D957BAULL, 
            0x7CA56693FECA3913ULL, 0x22E8AFE53CFCCCA7ULL, 0x48EA5EB31013B7D7ULL, 0x2F29669C333629C9ULL, 
            0xD4D20B7E9B58FFB5ULL, 0x6661F9AA4762D03CULL, 0x31B66ECACC590719ULL, 0x7B02E1E10841E288ULL
        },
        {
            0xCE9E800A1C06867AULL, 0x6E2CF360822DF0B4ULL, 0xC6B0448319D4DA7CULL, 0x6BBBC966125E04DFULL, 
            0x2EE55078F6B9780CULL, 0x3FAE328BAA7821FDULL, 0xE7E017FCD8C3F6FAULL, 0xE098CD30ED30AEE1ULL, 
            0xE5C4AC0465E992DCULL, 0xA73D659571A18353ULL, 0x4402682529725B5BULL, 0x7126416306061876ULL, 
            0x87DD9150AC70D161ULL, 0x25F1B7FA6B665052ULL, 0x28FCB24087504780ULL, 0xCDDD19E4DB27EAC3ULL, 
            0xEDEFD751132E4024ULL, 0x6D0FD71CA8247F5FULL, 0xA689F77B532703EEULL, 0x40E2ECD46EA0F633ULL, 
            0x9E60209A49B4A512ULL, 0x09BC04CF9B8C3A1DULL, 0x345CB41522990F8CULL, 0xFCDB2AE27CF14D80ULL, 
            0x185D6849F6815F15ULL, 0xA40C938A6FBBD9BFULL, 0xF555BE8BD3770B40ULL, 0x9B2438975E93663FULL, 
            0x0CBC6350631638B7ULL, 0x9AD859C24D179EEDULL, 0x850BB2CE031B9281ULL, 0x866F3B9AD43A0ABBULL
        },
        {
            0xD5658A2334483B31ULL, 0x2054B05A7DD0AE6BULL, 0x7CC5B35C6BBA2006ULL, 0x5E84ECA026844B6FULL, 
            0x6E8868D70610116EULL, 0xE2D7FF876F712781ULL, 0xB39F391BB8D516CBULL, 0x71A8EAA3D7D13853ULL, 
            0xE356E6D6D6E2FD61ULL, 0xCF0ACAA06D0AEAF7ULL, 0xFABBE4CE4E3F4159ULL, 0xC606A14DF271F9F6ULL, 
            0xB0F6C6F0B255D129ULL, 0xA73FA6B8D455314FULL, 0xEF1154EA6BC45E97ULL, 0x28458174F6A3A02DULL, 
            0x41BFB420392B71A5ULL, 0xA1EA4286985BC941ULL, 0x8501A9307414B680ULL, 0x3DC2B9977DA8A5CFULL, 
            0x8EA019F3F576D092ULL, 0x597CD78B8B481901ULL, 0x557D4A28CE6FA2CBULL, 0xB1538EC884C95E29ULL, 
            0xF926D26CEA38B85DULL, 0x93E7794EC7306600ULL, 0xC55AE70C756B7AD8ULL, 0x837D728A7CE404C2ULL, 
            0x8FEF19D2AFFE258EULL, 0xE499573977F35DB0ULL, 0xDFCD34387DC93E54ULL, 0x1B161CFB99DC803CULL
        },
        {
            0xDC7A7A738B37304AULL, 0x16BD50AAE9C9074FULL, 0x7077B0FD345C0228ULL, 0x8D02A9DB71FC1630ULL, 
            0xD96A760C0A3B13B9ULL, 0x785E18A4E0F49158ULL, 0x65337FE20F907C16ULL, 0xFC6B7B4760C857E6ULL, 
            0x3C0485249A1C3D46ULL, 0x820A5D65BF902ECCULL, 0x13B050CB93A84BECULL, 0xA9A1DDE53EADFDB9ULL, 
            0x9AA2232C337BECF6ULL, 0x3248338DD440D094ULL, 0x9F20D8465A0ED8F3ULL, 0x69E89D8A3C7CBF8FULL, 
            0x573BB0B44E4298B3ULL, 0x4DD34BD9594F00B0ULL, 0x537A90C0EE72C4B0ULL, 0xAF734E9B9EC5FE28ULL, 
            0x571099DF4BC59A8FULL, 0x52810BC26B18B4E0ULL, 0xD9E4C26C24B70540ULL, 0xA3BAD29C6A9F045CULL, 
            0x1262311ABE0032F6ULL, 0xDA4DDAA714D91116ULL, 0x730686DAE68C99E3ULL, 0x5DC5F874773DC6A0ULL, 
            0x677E992803717608ULL, 0xFAA31DE1827D2B8AULL, 0x5D6E590D33A16557ULL, 0x9AB136A4E87B4A00ULL
        }
    },
    {
        {
            0xB109008C6B1D37C8ULL, 0x3E9CAEBF03762D2BULL, 0x90B37EF44EDB1CB3ULL, 0xE5246E3CEC37CC01ULL, 
            0x4F9F60D84A33ABC1ULL, 0xC42CECB25489DC03ULL, 0xD2AC753887974755ULL, 0x8A54CC777FFDAC83ULL, 
            0x6147B0DA968E1660ULL, 0xEFE0C5FC698132C3ULL, 0x1E6B60269BB5A278ULL, 0xEF4ABD91DB3B62E9ULL, 
            0xA2F21BEC2839E713ULL, 0xD2BF9536FAC3EA75ULL, 0x366203C043E1C2A8ULL, 0x690CC96CA26A05F2ULL, 
            0x35A40C60614EC3DAULL, 0x05F45917370D2FBCULL, 0xEA7564FEDC2E5A4FULL, 0x46914BC9426C7113ULL, 
            0xEFB839B59FD5E48CULL, 0x225176B77C6F76D1ULL, 0x7040E9028FC28EABULL, 0x764D912809284DDDULL, 
            0x1765855DA9F6DEF6ULL, 0xCCE9083AF60F6F9DULL, 0x92383BFF2F09BFEEULL, 0x17005011C18020F9ULL, 
            0x19F436A23B3631D8ULL, 0x90EF82A26B1E97F0ULL, 0x22030CC016D3DE71ULL, 0xC9D810532961D416ULL
        },
        {
            0x1CDC8DD1709C3AF6ULL, 0xF3E6F5E688B4667FULL, 0x033FA3F5026FEA8AULL, 0x17E5E94CD2D6B706ULL, 
            0x07DA4F584F86AEF8ULL, 0x221CDE6470B33DE6ULL, 0xDB14589AF1AECD63ULL, 0x27F0514594BEB189ULL, 
            0x6DDEAEF5CB922A8CULL, 0x82FFDAB2B5EC91D7ULL, 0xBBA8F58D7B809397ULL, 0x0C7043CA1ECE61FFULL, 
            0x3891990E67BA760FULL, 0x0158DB62845D61ACULL, 0xC3E602914F66A6C6ULL, 0xD313AC34B9C99143ULL, 
            0xA494BFC49004F5F5ULL, 0x8455AA411C8761CBULL, 0xF094E59BF418C69FULL, 0x499A73092AB79F49ULL, 
            0x4ADA7FEDA4744AC4ULL, 0xEADC81DB61B0A7D7ULL, 0x1AEDB1D9F4C5C96DULL, 0x41A379CA722C6FBEULL, 
            0x931CABAE38EE64BBULL, 0x65E8AC831AFBF6AAULL, 0x7687421BC62197A3ULL, 0x977AA78F941D62F8ULL, 
            0x43E1FB0A771AC512ULL, 0x9FD805332FF78F96ULL, 0x251A57D3CBA0A82DULL, 0xF338B93AE123623EULL
        },
        {
            0x18F4807FA57ECA04ULL, 0x72BCDCCE2E3AFBF7ULL, 0x1959B3B7E6218967ULL, 0x89D75ACCD89458D4ULL, 
            0xC632391EC0C6B159ULL, 0x0043D0795CD0A479ULL, 0x22AB15F11BDB83CDULL, 0x5922F8CE9C3FBFFAULL, 
            0xE7666F4EF21F0E7EULL, 0x676A10F863A26AE2ULL, 0x64E9FA4C668E47F5ULL, 0x2823513DE0240469ULL, 
            0xECA9EFA085FBF0BAULL, 0x6100F346A3995A93ULL, 0xDBD8E1BD4683368FULL, 0xDD1A831BF4CE416EULL, 
            0x0FCA9A70DC15D988ULL, 0x20684DA8638B8855ULL, 0xC478E3B8E6CD54ABULL, 0x8B9A4A7B508C3849ULL, 
            0x79F0E56763651927ULL, 0x6F1386722A7D89D3ULL, 0x673F53F54C6F87D4ULL, 0xF0429D55E630F587ULL, 
            0xF358B0D50828A3AFULL, 0xFDCBB050D9CF0751ULL, 0x2077E75A07C86EBBULL, 0x8319AEED144C1520ULL, 
            0x5107C5C3650A84CEULL, 0x9CC2DD82DE67F6FDULL, 0x8BCAA71491608D84ULL, 0x8D849C028E806553ULL
        },
        {
            0xAD7D7048AB51EACAULL, 0x44E1BE95CEA342CBULL, 0xF6066C8CB084992AULL, 0xFB263A6ECD04AEF1ULL, 
            0x6CE9991B5AED2573ULL, 0x02868D8A590B0A92ULL, 0xA742CFCE945E2644ULL, 0x454506290B0903A3ULL, 
            0xE3BD8584180CEEECULL, 0x0873219C6D831066ULL, 0xFDA7D43E0877C92DULL, 0x404E9D1E2B2132FFULL, 
            0xC4C19637801D7756ULL, 0x60A6D8FB11002097ULL, 0x4122482A02C22A9BULL, 0x2EC92157775DF3A9ULL, 
            0x9FDA7CC647696047ULL, 0x80F9FB4E588B79A3ULL, 0x35B3104232038CBBULL, 0x466EA0D3E5C49E42ULL, 
            0x8EED1C519DC8D064ULL, 0x89B8854B99EE1216ULL, 0x861565DF0E94B8B3ULL, 0x110941CAF4DE88FBULL, 
            0x6AFFF9BCDBE4EFD7ULL, 0xB9DD7836A0775AD2ULL, 0xD0C8DEB982C3E12FULL, 0xBBC5624B598F091FULL, 
            0xF3BCFAE272C71A7AULL, 0xD3F8CA3FB33E063EULL, 0x397F5F6511538D13ULL, 0xF3D7F2BD9731E30AULL
        },
        {
            0x7902BE8F25B7A977ULL, 0x57A40279BED845CCULL, 0xB162F5E02BB6BEFCULL, 0x1ED086D9650413AEULL, 
            0x8B383F2472A174A2ULL, 0x34D982E55CD33905ULL, 0xD93DBA350B4354ADULL, 0x720AC42FADE782D1ULL, 
            0x3BDBFFE327F4D005ULL, 0x18FF0ECA793C6EB4ULL, 0x5F4020B7348262A5ULL, 0x508D3D6C1A96D335ULL, 
            0xC2F06CFD8071F1E5ULL, 0x79D89AA2DD461BCDULL, 0x77A59C449877FD4DULL, 0x9F73B5424E24BE44ULL, 
            0x79B140233C7A3ECEULL, 0x202A4E94B6F48988ULL, 0xF65C3A2BCA170A9DULL, 0x59FA5E63770B8A60ULL, 
            0x4566BE10FFECBA51ULL, 0x27752326CF91C4F4ULL, 0x5EEBD11F7FC6E0DFULL, 0x62362AF42BF7F552ULL, 
            0xF54EB5D1BB4B16ACULL, 0x0D135A0AEF4C4AE4ULL, 0xF018E6F58FBF68F1ULL, 0x74A8747A003D0D68ULL, 
            0x43533F79E60C889EULL, 0xFE7D6B910596BC5EULL, 0x4B5CB5F947FFBDDBULL, 0x43EDF4E91429FF68ULL
        },
        {
            0x2C199181963970CCULL, 0x6304B6026E4EDCAFULL, 0x4A4A9E7C4A47F02AULL, 0xDC9FED8FD712079FULL, 
            0x2F49B75C2850F4C8ULL, 0x7C9B4F1BF356ED91ULL, 0x7EA3C50E7DACC98FULL, 0x1B4E848C58B251BFULL, 
            0x729EE70ACD6737C6ULL, 0x302651086E0BB029ULL, 0xBFE251450E405057ULL, 0x20957AE83BE17783ULL, 
            0x6D9618E28FACE8E5ULL, 0x09269900F972717BULL, 0xBA1CB872D8DC5C9CULL, 0x06703D519E909C2CULL, 
            0x68FAE8855824E4B8ULL, 0x0167CA5D4B840C67ULL, 0xA63D33A020257220ULL, 0x8E5F3109350F1CDEULL, 
            0xE944FB7DB497B14DULL, 0xA28A7FC1F8080EAEULL, 0xF2BDA74AC5012027ULL, 0x71A27EEC388FF10BULL, 
            0x23397D69062F866EULL, 0xC168F8F5F3E4A32CULL, 0xFBDFF3328D986A11ULL, 0x3ABE5A57B7BDF180ULL, 
            0x5BA357D8C720C24CULL, 0xA8D15CD22C8769F4ULL, 0x22BCE1B3817757AAULL, 0xA28FEEDC306C0160ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseHConstants = {
    0x8D3283E35108AA1FULL,
    0x48FE0DC45A3E148FULL,
    0xE206C6D7D2D81400ULL,
    0x8D3283E35108AA1FULL,
    0x48FE0DC45A3E148FULL,
    0xE206C6D7D2D81400ULL,
    0xC2BEAD49FF0A0E30ULL,
    0x62FD10F5BB641DB3ULL,
    0x26,
    0x55,
    0xBC,
    0xDF,
    0x5B,
    0xBD,
    0x84,
    0x91
};

