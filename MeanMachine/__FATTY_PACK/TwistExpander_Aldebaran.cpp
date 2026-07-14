#include "TwistExpander_Aldebaran.hpp"
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

TwistExpander_Aldebaran::TwistExpander_Aldebaran()
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

void TwistExpander_Aldebaran::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9B351D19144A70AAULL; std::uint64_t aIngress = 0x9F739849B3A14586ULL; std::uint64_t aCarry = 0xF5AE37D1FFBF7FDEULL;

    std::uint64_t aWandererA = 0xEB578A54F01EEDCAULL; std::uint64_t aWandererB = 0xEA57E9E1E5B7AD0AULL; std::uint64_t aWandererC = 0xF628FFA325848B7BULL; std::uint64_t aWandererD = 0xE4082D1C04FB29EEULL;
    std::uint64_t aWandererE = 0xB0E265EF88EFE3EBULL; std::uint64_t aWandererF = 0xC01A363744F51F45ULL; std::uint64_t aWandererG = 0xD91CFEE0A18F8EC3ULL; std::uint64_t aWandererH = 0xB6FA6895E92437D3ULL;
    std::uint64_t aWandererI = 0xFD4CD624BC9CA634ULL; std::uint64_t aWandererJ = 0xD8F83D6445A9708FULL; std::uint64_t aWandererK = 0xB0EF7D0A579CC406ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12074838270174931998U;
        aCarry = 13450667579991768950U;
        aWandererA = 14721520930747344535U;
        aWandererB = 16881389476945105199U;
        aWandererC = 11469376733976619404U;
        aWandererD = 16737321899956311403U;
        aWandererE = 18203034592918090663U;
        aWandererF = 9262589914522531146U;
        aWandererG = 17336655139234394822U;
        aWandererH = 15421668206450246247U;
        aWandererI = 11860462393940370977U;
        aWandererJ = 17767154908734012380U;
        aWandererK = 10170252964242232277U;
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
    TwistExpander_Aldebaran_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Aldebaran::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xCDB34C4108B399FCULL; std::uint64_t aIngress = 0xE52AE5725430450EULL; std::uint64_t aCarry = 0xF5D114B14643A945ULL;

    std::uint64_t aWandererA = 0xA16D2C539ADC3422ULL; std::uint64_t aWandererB = 0xB60817189C11F52AULL; std::uint64_t aWandererC = 0xED1E3767751BEACFULL; std::uint64_t aWandererD = 0xAEB6A8D23B96CB3AULL;
    std::uint64_t aWandererE = 0xFB98D01E808EB3A1ULL; std::uint64_t aWandererF = 0xD226736690A2777FULL; std::uint64_t aWandererG = 0xB9619C969FCF81B4ULL; std::uint64_t aWandererH = 0xD7C7A6DA8618CC2CULL;
    std::uint64_t aWandererI = 0xC4065FC1486559D0ULL; std::uint64_t aWandererJ = 0xB51619B2BECF65AEULL; std::uint64_t aWandererK = 0x968E0DD4DFFC0EC4ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13434257790352990300U;
        aCarry = 15977197233067402388U;
        aWandererA = 13850760484553094027U;
        aWandererB = 17411882460797539986U;
        aWandererC = 17637157009094847202U;
        aWandererD = 15411826092003515333U;
        aWandererE = 13695492562853526707U;
        aWandererF = 11684765765126297130U;
        aWandererG = 10899564928760793699U;
        aWandererH = 12640680308536656338U;
        aWandererI = 9906540133420447789U;
        aWandererJ = 14856829396895673635U;
        aWandererK = 11661519988425232469U;
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
    TwistExpander_Aldebaran_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Aldebaran::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x919B71724EE35AB1ULL;
    std::uint64_t aIngress = 0xFADC1E8463BE18C3ULL;
    std::uint64_t aCarry = 0xAB2215744EEE3EA4ULL;

    std::uint64_t aWandererA = 0xB3D3126F861BE5DCULL;
    std::uint64_t aWandererB = 0x8617D6B8C26F48BDULL;
    std::uint64_t aWandererC = 0xF1EC792908BC5E87ULL;
    std::uint64_t aWandererD = 0x83FD4B911876954CULL;
    std::uint64_t aWandererE = 0xA7A25240A9F3FA4AULL;
    std::uint64_t aWandererF = 0xF83743E2D932C601ULL;
    std::uint64_t aWandererG = 0x9E864E65B21B8B36ULL;
    std::uint64_t aWandererH = 0xB5CFDF3E509CD8B4ULL;
    std::uint64_t aWandererI = 0x84D1D8AD25DDB858ULL;
    std::uint64_t aWandererJ = 0xB74711CD94038C9DULL;
    std::uint64_t aWandererK = 0xC3AE8D6EEC3E9A25ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneC, 1);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneB, 3);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneC, 5);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneB, 7);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
    TwistExpander_Aldebaran_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 3 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1972 / 1984 (99.40%)
// Total distance from earlier candidates: 3944
void TwistExpander_Aldebaran::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 834U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1388U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1207U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1376U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1275U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1674U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1678U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1593U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 841U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 916U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1186U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 637U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1431U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 216U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1910U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1211U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 118U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 256U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1410U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1319U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 721U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1626U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 676U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 476U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 720U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1072U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 280U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1358U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1532U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1832U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1725U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2017U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1306U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 659U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 890U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1394U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 288U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 92U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1089U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 786U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 307U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1544U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 24U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 525U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1065U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 572U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 800U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 264U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 826U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 384U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1624U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 814U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 671U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 673U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 840U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1383U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1259U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1281U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1770U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 809U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2006U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1822U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 508U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 870U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1463U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1892U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2028U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 820U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 550U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 166U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 717U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1330U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1514U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 956U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1823U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1884U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1125U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 972U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 451U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1831U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 670U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 388U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1716U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 276U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1262U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1865U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1918U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 767U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 942U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 587U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1115U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1642U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 186U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 817U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 142U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1806U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1913U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1702U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1078U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 793U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2007U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1807U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 458U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 798U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1857U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1174U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 643U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1922U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 638U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1861U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1480U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1401U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2014U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1212U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 930U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 401U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1345U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 35U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1978U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 91U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1500U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1097U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 159U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1782U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 194U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1183U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1943U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1355U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Aldebaran::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xEC96B188F4A0DDA8ULL; std::uint64_t aIngress = 0xA5379C52E7265B67ULL; std::uint64_t aCarry = 0xA6422550A2AA81BFULL;

    std::uint64_t aWandererA = 0xE346818ACC416A7CULL; std::uint64_t aWandererB = 0xC423287B28C0FAABULL; std::uint64_t aWandererC = 0xE2505BA712EC346DULL; std::uint64_t aWandererD = 0xAC5B53C0BAC69ADCULL;
    std::uint64_t aWandererE = 0x8F06CE563638EB28ULL; std::uint64_t aWandererF = 0xAC54B997DA6C0CCEULL; std::uint64_t aWandererG = 0xAF4D4C30BE11D00CULL; std::uint64_t aWandererH = 0xEE24BC4A6B1EE10DULL;
    std::uint64_t aWandererI = 0xF6CA48ADCAA7305CULL; std::uint64_t aWandererJ = 0xA6968F428635FC24ULL; std::uint64_t aWandererK = 0xAFA86F01388B81F6ULL;

    // [seed]
        aPrevious = 12721775289048804650U;
        aCarry = 13869410344603598352U;
        aWandererA = 17155975168924374257U;
        aWandererB = 13505924774669610299U;
        aWandererC = 9810226259744637688U;
        aWandererD = 9345259708584129894U;
        aWandererE = 14704833201039377653U;
        aWandererF = 17281462529277363785U;
        aWandererG = 11542092937185831859U;
        aWandererH = 18265562478394269164U;
        aWandererI = 15567318975793295140U;
        aWandererJ = 16762742764227515591U;
        aWandererK = 11639335657985871522U;
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
    TwistExpander_Aldebaran_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Twist_E(pWorkSpace,
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
        TwistSquash::SquashB(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
    TwistExpander_Aldebaran_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 3 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 1249; nearest pair: 621 / 674
void TwistExpander_Aldebaran::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6151U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5385U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2269U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7480U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2933U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1918U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 115U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1389U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4992U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2319U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1744U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1261U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6179U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2642U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3980U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2861U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 171U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1833U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1809U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 396U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1786U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1881U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 412U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 325U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 417U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1663U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1736U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 311U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1455U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 991U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1516U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 482U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1165U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1619U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1975U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1090U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 3 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 1264; nearest pair: 625 / 674
void TwistExpander_Aldebaran::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7379U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5386U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5488U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3742U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3373U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1706U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3008U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2680U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3365U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2183U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5087U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2746U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7724U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5297U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6966U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 695U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 690U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1082U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1057U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1307U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1352U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1851U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 817U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1887U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 33U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1102U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1598U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 423U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1159U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1187U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1696U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 356U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 2036U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 250U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1176U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1497U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseASalts = {
    {
        {
            0x9B916846C17391E5ULL, 0x682A69AD7FF7DBBBULL, 0xB1438E796A5D0381ULL, 0xC1BEA1EE949FE079ULL, 
            0x506EC99A4829CB21ULL, 0xBAF000CDFD3EAE1DULL, 0xDA5F6BD74B88F1EEULL, 0x0577E22BD62773B8ULL, 
            0x11E93A22D57381E5ULL, 0x8D09D0FF1FA4BEB4ULL, 0x2AD775F2BDAFE173ULL, 0xD7E3ECBEE53F9E31ULL, 
            0xBD2D81C0AEE92830ULL, 0x7574C5BF585D1D42ULL, 0x81260D66CB03A43FULL, 0x3FBF8F39B026297FULL, 
            0xD7D33AF889871B2AULL, 0xC440738A7B7A8F1AULL, 0x86E15BA16B9A3F14ULL, 0xE4D5329776621836ULL, 
            0x89AA44C4E9BB76FDULL, 0x928E31B2DFB2CA91ULL, 0xEEC5EF1D73593B28ULL, 0xA3BDC3179AED60D6ULL, 
            0x3561E458881FE612ULL, 0x9C33818A0068352EULL, 0x1DD59FF568D71A5CULL, 0x315E9344C40B5551ULL, 
            0xA7B6F2367265F5B4ULL, 0x3AA9856F26C2B0EAULL, 0xBB1A7868F7187F60ULL, 0x09CD16B9BFA61551ULL
        },
        {
            0xC2B04174A92BB9C5ULL, 0xE56A66E6E9B66978ULL, 0x64DD1EA5348E6A15ULL, 0xE17C47EF194F6BB5ULL, 
            0x072AEEAED86D87E3ULL, 0xC1FE7BBC789D34C0ULL, 0x1FB4E384910C5B18ULL, 0x2E64CF8E6618B276ULL, 
            0x3D13F13E37FFBFA5ULL, 0x5E01FB6217F03316ULL, 0xB4A9D7533C63DB71ULL, 0x9D0B6D326CA854E5ULL, 
            0x0BC3BEAF8CBF8B1BULL, 0x327BF33FECE7DE71ULL, 0xD92EB4F7E2383E8AULL, 0xF3C4608BFE6214CAULL, 
            0x2606C05894FFD2F7ULL, 0x48856164E793E4D5ULL, 0xA0B2B41043AAB2E0ULL, 0x562D6C8646C147E5ULL, 
            0x6C0F606714FA1A54ULL, 0xBE5F0B9C54564DB4ULL, 0x4B97CE3D31FD9E66ULL, 0x2C6460383C873AADULL, 
            0x0DD63CCAA88CD906ULL, 0x88F2668B7B5FC319ULL, 0x554EA4EA1F46A01EULL, 0xECA6BBDFB63A277AULL, 
            0x4BD31C3CB039AA4BULL, 0xE518FBB1CF2C56DDULL, 0x24CA699118C832DFULL, 0xD10BFDF294BD8583ULL
        },
        {
            0xE4E506D7A9E17609ULL, 0x05003AFAD4E2FB85ULL, 0xDF0565DBAB040E27ULL, 0x99656BE1006AC5C3ULL, 
            0x2C68AF9FB56400D8ULL, 0x4E562F7E3E4930FFULL, 0x36E923C846FA9199ULL, 0x74E1EA844A1561E6ULL, 
            0xFCE6F7CB4677A739ULL, 0x20CA861201C86CB5ULL, 0x2A6596A1202C2382ULL, 0xD8F5A09B6DD90939ULL, 
            0x743EF573ADF6999EULL, 0x542A9F85BA21F781ULL, 0x44F93E8F982014B5ULL, 0x9DCE0B6BBDD57559ULL, 
            0xB8631CBB95569B58ULL, 0x87A274C9DF522AFEULL, 0xC22067A40E27E962ULL, 0xEB4EDAA7152B6FE4ULL, 
            0x441469BDD39445F4ULL, 0xE3AFC4A66BF7A30BULL, 0xDDB11F8BBA7313A0ULL, 0x802C29DCD693FC7CULL, 
            0x6BC10B8E3E191AEAULL, 0xEC1497A591B42ACAULL, 0xEAF40DE458EF12CEULL, 0x8F119C3DB97E181AULL, 
            0xC2CA826BA6943695ULL, 0x79D68E31AF2C31FDULL, 0xAA04E1E47B0F336BULL, 0x12E034B6D6FCB87EULL
        },
        {
            0xBFCCD4F1E207CD6FULL, 0xF262134C324D8FFBULL, 0xE6656F3DC1A469DBULL, 0xFF17C7A777E5CC88ULL, 
            0x5E53103F7A7D98DCULL, 0x420C8C559F1171F4ULL, 0x650B6DD3B78DC7E8ULL, 0x73A0EAFC4EC3A858ULL, 
            0x17BC6004670F1CE7ULL, 0xA77FAF39897E3CB9ULL, 0x8EF7DBB9177BD51CULL, 0xC8D40CCD495F1AE8ULL, 
            0xF828807870A7EF0AULL, 0x4900C8BD84391BDEULL, 0xF43241384F0F7BFFULL, 0x4422C02541F04AB0ULL, 
            0x376190771530A516ULL, 0x6A05E1FFEDD734C8ULL, 0xFFAF254F4FBCD6B0ULL, 0xBC743509B6FAA938ULL, 
            0x9CBA3CAA4A4289CEULL, 0x166D4699A0B8D4C8ULL, 0x7A05AB8B39196811ULL, 0x06F5F12F14A97EB4ULL, 
            0xB0B388200B1C86C5ULL, 0x522EDD8CA4B39DD4ULL, 0x1FE296036B364A9AULL, 0x533D9D5036309BC6ULL, 
            0x00D7C93112D85407ULL, 0x08DBE5B97EDC3A5CULL, 0x463478BE8FE2BA85ULL, 0xA69793B03DCDFDBFULL
        },
        {
            0x6502E3FCE5B87BADULL, 0x5B38C231F27F618CULL, 0xF5A3F3A2F0D0CDB5ULL, 0x1B2B7E2F69FFCF3FULL, 
            0x2C990F434D832D19ULL, 0xA0319E44C3CE5F82ULL, 0x6B986F624A203D9CULL, 0xD4C5AF09897F14FDULL, 
            0xCC14A9E2F4BAD2F6ULL, 0x2952848C58C0E5CDULL, 0xE7F9FA2624D32EB9ULL, 0xC4D93ECC6C502738ULL, 
            0xC3E0E63E1A7638D3ULL, 0xDD092CE5DF015277ULL, 0x0759CDF31518BECDULL, 0x9736E041DB3C2774ULL, 
            0x4F8998A459192788ULL, 0x3A1F51BE3E5CB9B7ULL, 0x6689A7C0B866B0FBULL, 0xBBED31AB6C7D587EULL, 
            0x71DBCC16C021FA94ULL, 0x78C6DAC4F10B8EC7ULL, 0x97C7DC5B34620B58ULL, 0xD0979B4487F8FFC2ULL, 
            0xF33B402818C54CA5ULL, 0xCAE4B7F45AF0CBB2ULL, 0xFCA3D4A3DEE1C423ULL, 0x3412B2D0A63BE9CAULL, 
            0x5E77AEC818F9FEC1ULL, 0x387CBD90B14C7EA6ULL, 0x89CC5EED3254B492ULL, 0xA47996CE46944B0FULL
        },
        {
            0x9FDAB595CE464BF0ULL, 0x54232B7A3360E78BULL, 0x66FFBB415425566CULL, 0xDE35110DFEA7346DULL, 
            0x5EC2C4E42BB17EFBULL, 0xAB0D781C2259D49CULL, 0xC36BB02257D23E67ULL, 0x67224BFA706A8C13ULL, 
            0xE892EDF708A6333DULL, 0x2FED2DF7CAAE277EULL, 0x91B260D6D823AFB1ULL, 0x8E23405E325945FCULL, 
            0x01A6502E7596574EULL, 0x7C68DA7BB11C4250ULL, 0x2C7553AFE196FE37ULL, 0x7260F6814AF244FFULL, 
            0x7A7A3F2D6D5AB416ULL, 0xB7D61D56BD88F6B9ULL, 0x109976C59DE2D14EULL, 0x927211374EBD1930ULL, 
            0x57E32DEBA9FE51BBULL, 0x3B00340CC921A86CULL, 0x4E51CC263CAA72F0ULL, 0x2C5F271CA7662FA7ULL, 
            0xC59F601CDF2DEFDFULL, 0x84FE9B87A8B4361FULL, 0xB5942E6186A1042FULL, 0x63D9733D9277D709ULL, 
            0x62649152B28D5838ULL, 0x9C9099048C1A6FF4ULL, 0x65C27BD4EE828A2EULL, 0x17FF515AA55232C2ULL
        }
    },
    {
        {
            0x78FA2A72B59ED6E4ULL, 0xB5367DE878FA92C2ULL, 0x16DD25E582DA2DDFULL, 0xACE3D06911CDEDCCULL, 
            0x9D1467A9AF76E93CULL, 0x67F7B12E31392005ULL, 0xE7CF70D823C59B97ULL, 0x70C21B10DFDC4BF5ULL, 
            0xD961D57CF8340213ULL, 0x433F4E30B48E5B03ULL, 0x4E88CFCDAE23570AULL, 0xC213CA8703AF4F80ULL, 
            0x012974038FEFC990ULL, 0x1E9D377D83400534ULL, 0xAAE27E41DFED368CULL, 0x99CC42E45D6AC4DBULL, 
            0x3B4278879A3A43C9ULL, 0xFF6109EFF19A1A8DULL, 0xF07D42602B88FC21ULL, 0xC2D91C674D447D34ULL, 
            0x10628D4142F438E4ULL, 0xE48BDBFC07DD214BULL, 0x10A63D5565A35EF3ULL, 0xC1146EEB69793BFFULL, 
            0x8E9AC493D178F3AFULL, 0xE8E78DECC6878AC1ULL, 0xD15AE494B3863968ULL, 0x9548490D17DE4187ULL, 
            0xA665B5571CB91522ULL, 0x93121F0AB7503F22ULL, 0x4C0A8A639F16FF56ULL, 0x059BAF4DAEFDBD04ULL
        },
        {
            0x935C874DAC141D0EULL, 0x53448598B470BBA0ULL, 0xF481AAB9714FD558ULL, 0xB14263F34C72F241ULL, 
            0x14BA9E26B3D03995ULL, 0x0AECFC7C88293112ULL, 0x5E35953B466633FDULL, 0x76EADB08A2C4CD8EULL, 
            0xEC83B51BBCA35D88ULL, 0xA18AA83D446AF1EFULL, 0x40AD3616510D2717ULL, 0x43651AC0B8F3F30FULL, 
            0xA77ACF4FD7DA1575ULL, 0x45E38D62A4F26447ULL, 0x99DAE14D6ACE9277ULL, 0x5073C10FCA77C761ULL, 
            0xB7B6EB03943BFCBBULL, 0x8E722D8CC73DB538ULL, 0xF674D74C45FE82EDULL, 0x8AE745565FBA71F3ULL, 
            0x7231DE5D770A5F05ULL, 0x2724F78FF946EEE0ULL, 0xEEE10FDFCCB4A060ULL, 0x5E230130B279AACAULL, 
            0xA7683958AFF962C7ULL, 0xED40EF6F6165DCCFULL, 0x942BF3508CBC9B7FULL, 0xBF84A64C463FEB13ULL, 
            0xEFD8B37BCC29AB05ULL, 0x72D29366872268E6ULL, 0xB40E454D4166813EULL, 0x23428997CC000F85ULL
        },
        {
            0x11C0379532526CBAULL, 0xEAC5636056F8BD7DULL, 0xEA98E17624ED9088ULL, 0xBB5B3B58BFEBC60FULL, 
            0x4843440B0EF71461ULL, 0x6B9720934E14A861ULL, 0x619D6E007B8E1322ULL, 0xCF8C8C0E4B3D5AA1ULL, 
            0x181D223F2D1226ADULL, 0x25657B95460E918BULL, 0xD6725EAE3D38921BULL, 0xFBA8F88D28470CEAULL, 
            0x6EB922839BB7FD99ULL, 0x17254E6D70897504ULL, 0x260B947E7EE92614ULL, 0xF1BAA1E77B9832A2ULL, 
            0xC08F6E6450B6E253ULL, 0xD7675738BC8498AFULL, 0xF39CA221FAF15500ULL, 0x7619BEB989843E9DULL, 
            0x2BF91766C3463F02ULL, 0x98A32DAA778E7C29ULL, 0xB995C6244D4DFFEEULL, 0xCC06E064B2CAFFBFULL, 
            0x6863A272FAE89F54ULL, 0x8CAEF3D906521F30ULL, 0xED0C3F524750FCD1ULL, 0xF117771E06824860ULL, 
            0xF89EA74F6BF94DAEULL, 0xD48F3FDE0690FC39ULL, 0x272F8B860FAA6CA7ULL, 0x06AA04EEF55CEEB1ULL
        },
        {
            0x0403050576CF27F3ULL, 0xD789BFE4009F63FDULL, 0x4945877D0E822496ULL, 0x5A7F115F26DFBD7FULL, 
            0x15387E0310056F69ULL, 0x3982947DC45FFCD6ULL, 0xF2D8D23873A13AE7ULL, 0x9F6CF2C4098169C6ULL, 
            0x609DB887F72BCBB6ULL, 0x006189AF9452066BULL, 0x567DD186A2570FC0ULL, 0x1A423CBA787DA2A1ULL, 
            0x115791BFDC3FE773ULL, 0x94AD8B50913FEEE8ULL, 0xE6DCB848470ACCA1ULL, 0xA0F598F073C63F5FULL, 
            0xFB13AB020CF782D0ULL, 0x7A4394ECB11F86FEULL, 0x0FEEC8F158B6C8B9ULL, 0x07CECECDDB6BA763ULL, 
            0x584D94CBD97D89DFULL, 0x9F5100E52B94B158ULL, 0x424E398D0587747DULL, 0xF26B4E70D3CD9728ULL, 
            0xC7362360E7835E23ULL, 0x7647E3D40531C39DULL, 0xBE944A11B567BD1CULL, 0xFCB7EE28C195C966ULL, 
            0x15B742981DE656EBULL, 0x5D07FD04CA7C02A6ULL, 0xCE84BC8AF4FBAAC9ULL, 0x1BC6693C6FFD1AB2ULL
        },
        {
            0xC1DEF7CE8B0457EFULL, 0xBFD0CCB72F6ABE9AULL, 0xE20493029108596AULL, 0x3DA9C0E4BB3E0839ULL, 
            0xD7F1B062B0ED467BULL, 0xAB7E0BAD7127D962ULL, 0x35806210A9EB105AULL, 0x875DDD9DD5D7DDAAULL, 
            0xDB12C465663166E6ULL, 0xDBA24447AF713C0BULL, 0x09A5275BB21B637DULL, 0x8E3364D052C8462DULL, 
            0x819ED9694685E1B2ULL, 0x5FA5FB5104C8F538ULL, 0x536542B96E0DE976ULL, 0xBE0025FBCD13B488ULL, 
            0x489A17D8C7D8BAD4ULL, 0xC7DB0C03C4164D72ULL, 0x33A75C81F66A82FEULL, 0xF63782407A44E771ULL, 
            0x3D581F11C1E90F5FULL, 0x105620472334B25EULL, 0x19DCD7061743C205ULL, 0xB6F3FB4C4189559CULL, 
            0x863E669D5EB187F4ULL, 0xDFFB2B1F932BC140ULL, 0x4C78051425C5FFBAULL, 0x49D2B89FC5DDAECFULL, 
            0x7A8C6DD40167E221ULL, 0xAAE343AF5656D404ULL, 0x066DF075DE96F675ULL, 0xF418D6A8858B58D5ULL
        },
        {
            0xCBFCD73401029967ULL, 0xAC46959F94ED15A2ULL, 0xB82B8695005CB459ULL, 0xB969843CF0381CD6ULL, 
            0x9EDC3848E38D2C2DULL, 0xF7EB34D4C12E9235ULL, 0x974A9CB2D23D24D7ULL, 0xB6E53BE687F44170ULL, 
            0x5A6B82E4874DD372ULL, 0xC52AD037D804E510ULL, 0x8227575A82AF6016ULL, 0x79A548F89E1EB47BULL, 
            0xDBF62A04D0E33831ULL, 0x2B82F6B8CFB9C50DULL, 0xF8E6F4DD89F07D89ULL, 0x8F9CC9F31EC63825ULL, 
            0x3A61EE0D213B12D9ULL, 0x3A68D716E9534C2CULL, 0x71D032EFB5175392ULL, 0x380BD67DF762EF80ULL, 
            0xB44F924BDE7B708FULL, 0xBAC479CB2FFEDB96ULL, 0x93731E795047A472ULL, 0xC110EBEE63235BD6ULL, 
            0xB33240DEE90E199DULL, 0x5DB42A7A15309772ULL, 0x10CC63585B81578CULL, 0x36293C7C339540C3ULL, 
            0xA223E6C5911A1594ULL, 0xF8A53A4EDCEAE42FULL, 0xA7F45820DD233753ULL, 0x2DCF0DB310A23D4DULL
        }
    },
    {
        {
            0x3BE1234806644F11ULL, 0xEA4958455A7D9763ULL, 0x1DA6F23BF8E0C9B7ULL, 0xE6F79AB0F14BE789ULL, 
            0xFA127CFB3E8A1683ULL, 0x15A95B38E415EEC1ULL, 0x2DC721290DE6892BULL, 0xF792A75F76DF9CD1ULL, 
            0xF83827311EA89407ULL, 0x0A6349701FD01BC5ULL, 0x45DD3707370E3C67ULL, 0x48FD265054C3F6CEULL, 
            0x87970097FD249CADULL, 0x0A7B5C964D5A2B09ULL, 0x8E88FBBBF432CDB4ULL, 0x3CDE84A6E0B5034CULL, 
            0x0BAABAFB70E83EB3ULL, 0xD28F09A804A0BE45ULL, 0xCBD9DCE5EF691470ULL, 0xF4C007CF0CE3B415ULL, 
            0x37D0C9CC0B7BAA89ULL, 0xDFBED67A8D66D371ULL, 0x9DD21AA736B43D83ULL, 0x238B9CF1D834A3D7ULL, 
            0xA7C243F0E565E618ULL, 0x739338696146D226ULL, 0x69F03690FD14616EULL, 0xC7FB3F22831E4327ULL, 
            0xC278BD18D89E0821ULL, 0x55F87DED62E766D4ULL, 0x92FEC0396D7CEC23ULL, 0xFDEC9DBE25145931ULL
        },
        {
            0x6EDCE435BE8C28A7ULL, 0x02BC7CE75A3BC2DEULL, 0x3B5A76C44B4C5D4FULL, 0x3D9BF815F37CAFFCULL, 
            0x38ACEE9C06E2492EULL, 0xCB7F7A30596F4193ULL, 0xC3DCC1414FF6BE28ULL, 0x671D93EA7568644EULL, 
            0x826D1CDACA9AD6FBULL, 0xF65F24C6CE56150EULL, 0x825EAAA3778CD517ULL, 0x46584228E321517AULL, 
            0xE5FECD40B6E9FA7AULL, 0x32E00F7CB481E533ULL, 0x3D46C947217BC729ULL, 0x312146D0E2F43CBAULL, 
            0x8FABF8D4A7676355ULL, 0x3BB48064F54153BBULL, 0x0641BF078EABBAF4ULL, 0xC14927FBFEF0E6D0ULL, 
            0xE92DB5597B7C9B40ULL, 0x27BCD4547C4D6874ULL, 0xB4DCED55A1D3D9BEULL, 0x78481665BA36BF89ULL, 
            0xFBE392C2BF5A2279ULL, 0x258A01C1BDC8836EULL, 0x4D6283FB97DAEE44ULL, 0xA613D118378482AAULL, 
            0x30A653E47B9BC447ULL, 0x3646A9BFE76CC632ULL, 0xC85E220BDE67BF81ULL, 0x0B56459D64B2FEE1ULL
        },
        {
            0x0B37015227EDCE68ULL, 0x0EBEE8398B484495ULL, 0x4581C42A423777B0ULL, 0xE00E15B091862F26ULL, 
            0xBB2761ADEC580574ULL, 0x0A1B55DEAF1615AFULL, 0x9193FC085C24EBCEULL, 0x4BC4F2AE374C8744ULL, 
            0xD55572DA842C7B8AULL, 0x78F6EACCFFEFE174ULL, 0x8BABE690ACE48712ULL, 0xC10660ADFB4C3792ULL, 
            0x9F07A3A87D21A13AULL, 0xC013E7DACC550127ULL, 0x1F91FE404321B8D9ULL, 0xCD2451D252B0FB6DULL, 
            0x71492EE4E1B2BB8BULL, 0xC0EEBB15C44DA241ULL, 0x9D121E96699977CAULL, 0x398D86F8740B5608ULL, 
            0xC3DC00A5B9E307EAULL, 0xDFF1C06719D2C60BULL, 0x5A3C3BBBBE0823B8ULL, 0xFBDBF90965C58434ULL, 
            0x85E5CFF7A3B80B10ULL, 0x30A2C8137561C6E0ULL, 0x59B2E75E8A3D2B34ULL, 0x2D44562600A9113CULL, 
            0xECCF45F51E902164ULL, 0x5B937C5009D8B170ULL, 0xF5EF039F48066776ULL, 0xAAE4A62542DB4D6EULL
        },
        {
            0xE1093E89CF0D6156ULL, 0x4F4EDD319411F56CULL, 0x3476EDBF0314794AULL, 0xB64969F67F2AE792ULL, 
            0xE4051F843682F43BULL, 0x35A50830214D667AULL, 0x861B89C093BEA138ULL, 0x69D2653F5276F6E0ULL, 
            0x443B7878E20E840EULL, 0xED7A75072B566BDDULL, 0xDA8BCDD154D37990ULL, 0x9001E519331E942FULL, 
            0x577EAFCFDCB15C84ULL, 0xFD903D95ACC7CBE4ULL, 0x2062BD69A5EB35BDULL, 0x47C319BDD3BFA7D3ULL, 
            0x9C1EE708A1AA19EAULL, 0x8F77EE0C741637BEULL, 0xF32E072E0A92A957ULL, 0x29CACBE7FF0E2137ULL, 
            0xAAC134DEC6C1586DULL, 0xDEA9CC6BAFD5692AULL, 0x2A964ABDF9DB17D6ULL, 0xCF7BF7C0AA24BC99ULL, 
            0x4C3426BBE1ECF9F2ULL, 0x6234D3E0A151F4F5ULL, 0x9EC52764B6C7F8D8ULL, 0x959008CC6CD1788FULL, 
            0xF1B94309A20D4201ULL, 0x80B6732066459946ULL, 0x17B33BA3F5DC76DDULL, 0xDC8264ABE70891F7ULL
        },
        {
            0xFA6173A131B93BC6ULL, 0x9C5A6E33A7E74E4BULL, 0x86B5234240DDBAB4ULL, 0x149A866DB1724515ULL, 
            0xCD826CD1FCEC7AE8ULL, 0x05F37E47950FE47CULL, 0x34EC8C89CF6DE8E9ULL, 0x7626AC2B38B25391ULL, 
            0xFDDB7989394DF73FULL, 0x570C095C3FEBFD99ULL, 0xB14446F27F11EA17ULL, 0xA756143E55005B81ULL, 
            0xBDC7B967934DCCA9ULL, 0x3B8F047C2F6F17C8ULL, 0x318321CD7A43C809ULL, 0xA9EF8EF56DC54F6FULL, 
            0x749C940E87CBCD8AULL, 0x49A6AF3F85CE602CULL, 0xC804ED4523AF4215ULL, 0x72CC2377C19FC09FULL, 
            0x044B14385C34F1A7ULL, 0xCECFA59C3D5B33A7ULL, 0xE1DC62D8F9BD3F04ULL, 0xD6336C717915929BULL, 
            0x456A86ECB72400E8ULL, 0xBB5A4ECFDE78521CULL, 0x9789351B5371E3ACULL, 0xCEB959CC679F146EULL, 
            0x8747A14E7A942779ULL, 0x93C4CFDE9792FB1BULL, 0x1D2CD69B0F7F37CFULL, 0x7DA14734B22D5B37ULL
        },
        {
            0x9CB7380C5C091B6EULL, 0x75A8059096CF68C3ULL, 0xEF8C8ADD641C3400ULL, 0x1175B3DAA282F2B7ULL, 
            0xF206E17DA2BA6072ULL, 0x6CAB19795C981D34ULL, 0x62FE1874CF475F94ULL, 0xA04EA5BB45E081BEULL, 
            0x63CCE3E4FDC3336AULL, 0x97046E1EC41DBD6FULL, 0xC02E98FF74530C42ULL, 0x25EB17E520A30DA3ULL, 
            0x0CF273D682639A14ULL, 0xF648FA80487D9494ULL, 0x84017686B6F515B3ULL, 0xF820353C2E008403ULL, 
            0x7AA1F7A4B6F4D047ULL, 0xA1BF5209953C65FDULL, 0x6155C3A0BA7A6074ULL, 0xB757B202697973DCULL, 
            0x2ADB6B57E3E26EF9ULL, 0xA73F81A06906D016ULL, 0x7AFCE85AAE97624EULL, 0x8DDC0AF7F51C8366ULL, 
            0xB6D83938F9A11AF5ULL, 0xBB82B2DBF242B2BFULL, 0x0548DFBA7D703D1DULL, 0xAA8BCB9F21594EEBULL, 
            0x0BCCEB0173A4573EULL, 0x129631CBC28DBA24ULL, 0xC3900C90A58EB03FULL, 0x08A555FF352FA859ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseAConstants = {
    0x649530F2BE4936F8ULL,
    0xDE7E1D0B8A741691ULL,
    0xD82939A17859273AULL,
    0x649530F2BE4936F8ULL,
    0xDE7E1D0B8A741691ULL,
    0xD82939A17859273AULL,
    0x9BFA93A062A86212ULL,
    0x216390902FCD6EE1ULL,
    0xE1,
    0x54,
    0x6D,
    0xD0,
    0x0B,
    0x43,
    0x55,
    0xFC
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseBSalts = {
    {
        {
            0xAB59EE17C4E2A615ULL, 0xD92A720FC5FD7A0EULL, 0x5834EEA39A456D4EULL, 0xB615054DBB0458EBULL, 
            0x0A7C5C206AE884C8ULL, 0x50235F6DB270322EULL, 0x9CC1E59EC782389BULL, 0x73260202744D2623ULL, 
            0x8041F962F5622BECULL, 0x6B80B496430793AEULL, 0x1D58302D483A9660ULL, 0xF4C76968D04C5527ULL, 
            0x07211EB18E78B12AULL, 0x981C6B1296BC69CBULL, 0x012CF0B40E0351FFULL, 0x83CF44AC1830B5FBULL, 
            0x315B06FF125CBAEBULL, 0x7A9BDAAE63DC1F5CULL, 0x151B698813CE13F7ULL, 0x04EDA9F72F02D61EULL, 
            0x517302332CF11FD7ULL, 0xF45DA83675370BE8ULL, 0x7FADB6BF2092E640ULL, 0x877C051B4B2ED2F0ULL, 
            0xE42441F384D69259ULL, 0x03264DE33CA7517DULL, 0x182340E338118B22ULL, 0x42A11D425FC01F0DULL, 
            0xB73E2B187EC4512CULL, 0x59E5BB62199E4856ULL, 0xCE823F4B7FFC9B6CULL, 0xA43810B0EAAB6B75ULL
        },
        {
            0x0A0729C9A0F5BD92ULL, 0x171315F4B19127E1ULL, 0x2CBF145D0844DBEFULL, 0xCB681CAA06BD4C07ULL, 
            0x1869677EE06168E8ULL, 0xA591E210A239FA34ULL, 0x76509072FDED9D90ULL, 0x5EA636952D38E63DULL, 
            0x19448B0E14EA28ABULL, 0xFA7D1B6F17F2BAA7ULL, 0x130AD45313B3F046ULL, 0x26A2BCBCD5FAC7B2ULL, 
            0xCC69FF46FBAF13B5ULL, 0x18E87C72AAFFB258ULL, 0x5CEC3D01457E0B52ULL, 0x577713196340BA73ULL, 
            0x39BE83A57B8BE2ECULL, 0x5100B1601A435F00ULL, 0x0E8310EF8518E756ULL, 0x7B9FAF55090217F1ULL, 
            0xA199CA0795C2E893ULL, 0xC835AE1258AD6F65ULL, 0x963FEF3DC11DE9EDULL, 0x410D77301C211623ULL, 
            0x1B6EB6F9A8B9657FULL, 0x9090A5FDF46BCDAFULL, 0x2FA8449E59886417ULL, 0x2CEF3BCA3DFF487FULL, 
            0x3A34FD752A1B1C9DULL, 0xDC1FF2FC581CF491ULL, 0x64CDF5A88CD6CE4FULL, 0xDEAF1C9B299CD90BULL
        },
        {
            0x03B499BB52EE6961ULL, 0x7EB5DC8CE24FF3B5ULL, 0xA0BF77481A2D731AULL, 0x2E17B38BC41D6363ULL, 
            0xAB75395AE333AEAAULL, 0x46DEB3F88EAD0AB8ULL, 0xBF986F50881F2441ULL, 0x0E1C92E6D638E2B5ULL, 
            0x9B9100CE7D66B870ULL, 0x683A5446EB7CB693ULL, 0x33CD8770787C882BULL, 0x79FBA68A8A8BB340ULL, 
            0xD39ACCFDCA798827ULL, 0xBFCBAD079A7152C8ULL, 0x931E36B00910005EULL, 0x1F8A1023AD7DDF5FULL, 
            0xEEC128FD90A17E69ULL, 0x33201385AD7C45BFULL, 0x2B382F2FED86CE16ULL, 0x840DAD821401B862ULL, 
            0x61E3476CD3CF9D3BULL, 0x45781FB231765471ULL, 0xE26B56BA60B0908CULL, 0x261D9364ED92030FULL, 
            0x5E9BF1B008B50504ULL, 0xF5AACC0E1B022DA2ULL, 0x067FE6EAD4AD39DCULL, 0xAE1E18C8393891A4ULL, 
            0xDD02D2956C9B0B71ULL, 0xC7518DFBFE0470E3ULL, 0x0ADF5FC521DE4011ULL, 0xB18003C8333B129BULL
        },
        {
            0x38A3BDF510A6EF23ULL, 0x4E335DFA1FFE32FAULL, 0x8BFCE84E8BD02136ULL, 0x03247C42423075CBULL, 
            0x8E3CF7A8D35B2E62ULL, 0xE32E431FBC103155ULL, 0x48D28D6D67356215ULL, 0x6F5D98C03AE30401ULL, 
            0x615028BB26CB3B61ULL, 0xE236507922FB217DULL, 0xAFD61E438B4258D5ULL, 0x40C66275E8491DACULL, 
            0xEED6DC54A8596A5BULL, 0xFFC1410503C40F2BULL, 0x11CB0F5830F19B7DULL, 0xE1FD97C73695385EULL, 
            0xBB1AE8D90621E1B4ULL, 0xBE92F7ADDA352F3EULL, 0x851D6B9CB51B2A60ULL, 0xE63B4FF6DEC1D3BDULL, 
            0x95331B428E7724D2ULL, 0xF160852F78A4E639ULL, 0x1AE87EBF0486F0C3ULL, 0xAE3BA3CD2A5476DAULL, 
            0xF19B2A1FF01ADBABULL, 0x5F684FA47ECEE11AULL, 0xC941D7C0B226365BULL, 0x77324BFDC76A5F30ULL, 
            0x13EB81E371475CDEULL, 0x79AAE1415309FC9AULL, 0x6D190B203E8FA52BULL, 0x51E7CD8D301B6D7EULL
        },
        {
            0x7660131E519085B6ULL, 0xAFF71104B6711D2BULL, 0xBCBBDA27E9EC6F4FULL, 0x6612244EBDFCA16BULL, 
            0x2DE91180AD23B4BCULL, 0x7FF1131C26F41E12ULL, 0xE8EF52C6FA7E811BULL, 0x4AD789497C6311D6ULL, 
            0x36DF9264349B64E3ULL, 0x052CDDA2A6DE6380ULL, 0xCD8DEB557381F3B9ULL, 0xB36252EF27357A63ULL, 
            0x3921B3CA5777E02DULL, 0x1B508DD1D6F89A7CULL, 0x5EF44CB062FF70DAULL, 0xB1361548CA0129F1ULL, 
            0x97592CF4D6EC7190ULL, 0xB40E98FD0846D5F9ULL, 0xEE7997B39E9C2108ULL, 0xB6DBEB28FD2DBB23ULL, 
            0x87D44F7F661A47A5ULL, 0x3D8EC43B81F9A97BULL, 0x5DF44D85ACE13FDFULL, 0x8983FEF93FC1F3A5ULL, 
            0x792C1D6F61210BCDULL, 0xB2E55C646DD69AE6ULL, 0xAC290003CD14A76DULL, 0x426F1555428176E7ULL, 
            0xEE962B876F805AB3ULL, 0x96F4973DF448A223ULL, 0x7138811619CCEF02ULL, 0x44026A0232F52A79ULL
        },
        {
            0x7D3B79E56FDA3EEBULL, 0x9EC2482FDBD78E34ULL, 0xA22D4C5BD0B83EDBULL, 0x8646B2691203F91BULL, 
            0xA96456D0D6E7D243ULL, 0x8A8839D39D0C2B6EULL, 0xA58B0A05224C864AULL, 0x8B70F43151949FEBULL, 
            0x39CF39DBD6161E8FULL, 0xF86A45D9048F38DAULL, 0x88BD7FC8A9285C4CULL, 0x0283C455E62A8E09ULL, 
            0xBC14557237C620B8ULL, 0x92EB5B36E5DC4AD8ULL, 0xF8B118EE3382A5C4ULL, 0x58E0AFD0A5FED8E7ULL, 
            0x89DFDA359998E4E1ULL, 0x677AB94D0082F36FULL, 0x36CDE8411729AA2CULL, 0x5E17CF89C827A1D5ULL, 
            0x821447E7F9CAC870ULL, 0xAD84999DC0A62891ULL, 0xD86996A773DF14F1ULL, 0xD809F9691D0BD0FEULL, 
            0xB4AC048151EAF756ULL, 0xDE783F4F6A7C9AD7ULL, 0x64CC390A7D17E1BDULL, 0xF308C4C52E264E60ULL, 
            0xB05EC207DA4A8E3FULL, 0x46CE2FFF9CFD4D77ULL, 0xCD09EAA594DD1E8DULL, 0x7CF7B2750B802AD3ULL
        }
    },
    {
        {
            0x77E07C756F522A31ULL, 0x1D4C7EBC5D4B1ED8ULL, 0xC20833D82422124DULL, 0xD3CAB7A2B0AAD052ULL, 
            0x70A07B616FF3F2E9ULL, 0x0CF6F39A951CFF14ULL, 0xB4301A66A3EF3586ULL, 0x8FE58B74B1B27052ULL, 
            0xB46544064E01D901ULL, 0xF1C2516E19FF3370ULL, 0x83B22689C8D5CEDBULL, 0xE204C71270D8F9EDULL, 
            0x14BA7588C5F9FFE0ULL, 0x4B4CCB5D1C32CFC2ULL, 0x8AF98BFBE713FEBBULL, 0x89DAE6C6C632890CULL, 
            0x5E624B248C6CF235ULL, 0xFAED7F85542E95A2ULL, 0xB3B0DD28EF546EF2ULL, 0x1E278B4D4D285756ULL, 
            0x4ED35ED800EAF332ULL, 0xC41A3B1074EBC060ULL, 0x3B783467E03DF0C1ULL, 0xC9EB9CEF7859A573ULL, 
            0x9FEC8B37DF71704CULL, 0x1EC539B1CB0E27C0ULL, 0x94EBBC723B2FFCE4ULL, 0x551900FBF13B9529ULL, 
            0x23FA618A160CACCAULL, 0xCC483CE57906B314ULL, 0x18EDEAD7C1A71834ULL, 0xD090C4B29BDEE7CAULL
        },
        {
            0x8CF886FA59F30F80ULL, 0x7875002DF73B649BULL, 0xD58137F4486A4577ULL, 0x177A7E63624EC5F0ULL, 
            0x2088E3D365244A77ULL, 0x856DE04A65C891B9ULL, 0x78E7C5805BF0E157ULL, 0x38D88BFA2AB77EB5ULL, 
            0xF21E6627C620076AULL, 0x1B4058B57BA1DEB1ULL, 0xB59D293D3044FA1DULL, 0x03A2AF9BB6FA9DD3ULL, 
            0x874F5BEF105EC70CULL, 0xD76B746862728AEEULL, 0xC9AB9408D8BD1569ULL, 0x0F862541B291C729ULL, 
            0x8BD9F232B27CAD9DULL, 0xBA780EBDBFCB616BULL, 0x27B5E92868073804ULL, 0xCC336A3726308E3DULL, 
            0x1A1ED495C011B50DULL, 0x8F8ED5CB0E5F6816ULL, 0x21AD3B33593E4768ULL, 0x1CD998DCF3C27285ULL, 
            0xC4A4FCE02149194DULL, 0x5B7EDCCB551936DDULL, 0xC995A8FD74BB1676ULL, 0x7E0344ED574BAEFDULL, 
            0xA3C37247DFB4F123ULL, 0x43348BEDABFEB672ULL, 0x43F0F8F7EDB5295DULL, 0x9FFDB05029FB72B3ULL
        },
        {
            0x1FCC36D42BD78A32ULL, 0x58950FAFE00DF217ULL, 0xC7798E26989981C2ULL, 0x0F45A6BC0CF55DE1ULL, 
            0xCFD57F90F4C9B905ULL, 0x2652102FAD8B88C4ULL, 0x5144F6BBFBA7B907ULL, 0x353187500A348085ULL, 
            0xF66905E4737F55EFULL, 0x914BBAF22DBF992CULL, 0xB7B4FFFF4671BAA9ULL, 0xD059F77D9C222069ULL, 
            0x2312B74D5E9B338EULL, 0x87DC2319F32D4648ULL, 0x79E110C03140036CULL, 0xB8A6273237F41951ULL, 
            0x10155F558E310135ULL, 0x2A6609B0625E576DULL, 0x9E9DFB46404D1BA7ULL, 0x0D598E5D54A8C770ULL, 
            0x9CF8CF5C3C775EB0ULL, 0xF379DBCF9AAF853BULL, 0x67408D73DEE9D01CULL, 0xBC8EC4C77DB722D2ULL, 
            0xD7D4E1A6299F59FBULL, 0x859C75BABF961B24ULL, 0x14D08FB141F19CF2ULL, 0x35A17EF56413BDE1ULL, 
            0xB5F3410449C285F9ULL, 0x9F5323DBCACEEEDFULL, 0xF22531E67F1B7B62ULL, 0xB7CDCF6ACF320060ULL
        },
        {
            0x613C02CAF8C9B33CULL, 0xA4C79D7A319CE0E3ULL, 0xDB7EE0E675FCF081ULL, 0x33C23CB37DABB602ULL, 
            0xF44DC3374176D86DULL, 0x878777B656BE95E7ULL, 0x5E26C65839781B46ULL, 0x0737F6F52025FF35ULL, 
            0xB4E8A3772E0D8A90ULL, 0x2B2BC802F5C2506FULL, 0xE29EF16BB6F4B78DULL, 0xB52C14B5FF0D845CULL, 
            0xC90285D9A9A81098ULL, 0xF915863FE1CFA94CULL, 0x7171AC12EBCB5877ULL, 0xB11FE1190150BD82ULL, 
            0x224EC9E86A6D7CB8ULL, 0x490AA229A28AC1B8ULL, 0xF87D661BC82FA4A3ULL, 0xB19D34151E50783DULL, 
            0x2997CAB9A4B60360ULL, 0xAB7F4B9C6814F646ULL, 0x3A5EFF6CDE19100CULL, 0x52F0A324A29648BBULL, 
            0x735E0EB54648EC49ULL, 0x439D4D4EBB938E90ULL, 0xE2D306BA57FF3CD0ULL, 0x0B2633EBB5996ED8ULL, 
            0x90FE79F72382612CULL, 0x4F15A2E13C9A05C0ULL, 0xD041DA536623CBE5ULL, 0xD4D1E9C0F759F86BULL
        },
        {
            0x42FE05854AD29016ULL, 0x08DFA5A45C1349E4ULL, 0xB98AF9A6ADB8C0EBULL, 0xF4B41CCAC439CA9EULL, 
            0xFC7D7F020102D45EULL, 0x25D5A4C4D468E882ULL, 0x82C784460A0E1643ULL, 0x74E5F9C7FC477AC1ULL, 
            0xEA97937D3DB653ABULL, 0x6557C5D6B20F0655ULL, 0xAAE35DDFBF7D28BDULL, 0xB30BB1E27C3DF311ULL, 
            0xA25E4B5333A55570ULL, 0x6E1C3EDCB05E31B5ULL, 0x32B569669690FA36ULL, 0x14F42C2C6B4EFD0BULL, 
            0x0736C481666287DFULL, 0x531B8C33380A28ABULL, 0x2E3D638335AE4D86ULL, 0xCD51C984BC1E10C1ULL, 
            0x9AA0C39A12620CCDULL, 0x299CFF32F6163783ULL, 0x83BD3C54BA76DD1AULL, 0x8E41699BBD95D6D6ULL, 
            0xE9D1020F3BD3F02FULL, 0x49FF0B476035CB2DULL, 0x6327211CFDF1F7C1ULL, 0x9BD9651CC327C11DULL, 
            0x45C461735FB8C051ULL, 0x1E7F736264219816ULL, 0x2418CAA7F184DBFBULL, 0xA1765F37ABBD370FULL
        },
        {
            0xD827EA19E90E3B6CULL, 0x80EF71EA75E194D3ULL, 0x85C694A01CCAE5D9ULL, 0xA7D1BE44971B56B6ULL, 
            0x54734A37D5018258ULL, 0x891F1B2A54C37319ULL, 0x711E88F601BF752BULL, 0x9B3B3C42E2F4CCEDULL, 
            0xD0EE5D99E53FA713ULL, 0x70A654573B41BA6BULL, 0x762244C302141D04ULL, 0x5A677053446AE1A2ULL, 
            0xA3E2ADCC9576C4E7ULL, 0xA85CA6E8FFC46A23ULL, 0x2EE4B9C490B1E403ULL, 0xB11F815EDCCE4715ULL, 
            0xB0D66BD34B3E73C6ULL, 0xAFF11CE3BF52E8BFULL, 0x33227CA0A270770EULL, 0xF823D271BF900CA8ULL, 
            0xB8DC514054704969ULL, 0x4578744E18533F35ULL, 0xE89580470624904FULL, 0xA15CFCDDFE948F8CULL, 
            0x404CD8EF6FC16F9BULL, 0x7716D805733AC01DULL, 0x5758A38C88F999C2ULL, 0xED19BC1F6676987EULL, 
            0x2A276493D4DEE1C5ULL, 0xE0266238FF248685ULL, 0xB676C98DD699C052ULL, 0x12E4D4E480AB5E78ULL
        }
    },
    {
        {
            0xF37EF1C09B628DC6ULL, 0x25654C7678DA6F6FULL, 0xBE976CC3D6355EE4ULL, 0x1F960368B68A2C7AULL, 
            0x812C8D822AD17128ULL, 0x6C295B95F97A30B6ULL, 0x3B4A903E6C47AF0CULL, 0xBC9C6D74A51E12B4ULL, 
            0x083E8F182549745AULL, 0xD4C981340EE1BF79ULL, 0x807675711673AF84ULL, 0x76BCBBC605891D01ULL, 
            0x22ED6A91CFAA9B93ULL, 0xC4F60C83A4B0E65CULL, 0x77466451C149CDABULL, 0xB1ED4BBFD3C0674DULL, 
            0x444035A1C0D66777ULL, 0xF8D998BF95F110D6ULL, 0x32C8770991615399ULL, 0x1EA70735AB1B28DFULL, 
            0x6F8B8671F0DE510AULL, 0xB41706EF9B159F00ULL, 0x20688F91FF3682F3ULL, 0x93E66EFF8491D7E0ULL, 
            0xCDA3C265543559A1ULL, 0xA365AA3C60BD886DULL, 0x7C70BFB1D5181BD2ULL, 0x049F666B0D8AC858ULL, 
            0xD79304C1EBCBC14FULL, 0x68861AA39598FDD7ULL, 0xE29E23FDA6124B03ULL, 0xE90860DE9EAEB6CFULL
        },
        {
            0x6E3C7E9AB4B9C2CFULL, 0xC24471F54B0D59C5ULL, 0x5581F0E0E06E02D8ULL, 0xBED9192BAAA25B24ULL, 
            0x32A49D389413B5F4ULL, 0xDE52C5FF83881213ULL, 0x5EBF9FF074843E56ULL, 0x02533032B0ED9467ULL, 
            0x60C9F1ECD6D4D1D3ULL, 0xF8254540844F0373ULL, 0x40607472F59B6ABBULL, 0x5D29B19CDB1CAACCULL, 
            0x478441FE55C1BDCBULL, 0x3E7F0555FE34BC70ULL, 0x71820448CC4F7BC1ULL, 0xEA48B2BD22B0D730ULL, 
            0xDE96270F19A92D87ULL, 0x00A3395424C20AB6ULL, 0xA60E7F7578E8B9C1ULL, 0x9518E4D509518076ULL, 
            0x6C79246A5574BF21ULL, 0xE4A776927A2B5E61ULL, 0x7CEC243502746F04ULL, 0xF9B93BE77AAEC457ULL, 
            0x953E9FBEAEA0CA47ULL, 0xE68D1B3932D35D73ULL, 0xE581B7ADFDFABE9CULL, 0xE9B25A8AEFCA0B4AULL, 
            0x01FD62BF9278D7AFULL, 0x039A94685BFBBFCEULL, 0xF0046E31EABE8AFFULL, 0x0753382101CE828BULL
        },
        {
            0x25431D6EDA24CC2AULL, 0x22C53348CDB27B4AULL, 0x4154748C6E90E5D0ULL, 0xFF893D9B653AD003ULL, 
            0x75942E2DF10AC8A7ULL, 0xE6ECE600490F2D07ULL, 0xD942D51D749C5029ULL, 0x7DC5A8108CC7A9E8ULL, 
            0x6993CD4BB395525EULL, 0x9168FE9320918147ULL, 0x255C5BBAD31D81EFULL, 0xD09A7C750C594245ULL, 
            0xEB8506CC667588FAULL, 0x2264603B54144D42ULL, 0x66759B94B9FCA4D8ULL, 0x28684D61D26733ABULL, 
            0x522A949285E15D3EULL, 0x61D5286F69541B44ULL, 0x7AC9CD8AA6B05C41ULL, 0x3603E8D460EBFCBBULL, 
            0xB79B25DC15BD7895ULL, 0x7DE2B38F59F9C3EEULL, 0x143851F2B4BCCE1EULL, 0x02D1F939224EA825ULL, 
            0x11F23B313B4A5AFBULL, 0xBB95F1D6BE8E8654ULL, 0xD16A4A155F12C60AULL, 0x2B2AA0DEFDA08936ULL, 
            0x56566EDF558ACF07ULL, 0xB677E39C6369E6CBULL, 0xFCEAFAACE7D33B94ULL, 0xD858827C49E3DBEFULL
        },
        {
            0x2DF812A8A7F85F9FULL, 0x822115C9210CC60BULL, 0x13D33F60C90557E4ULL, 0x8AC930F89D1DEC10ULL, 
            0x37E90EF4146D8E6DULL, 0x9B2AA7AC0312841CULL, 0x4FC690AE745F702AULL, 0x60695CA898A92268ULL, 
            0x28483C6ADF3D9679ULL, 0x2F91676BDC000D08ULL, 0x3BAC29C2EF3E68D7ULL, 0x8417E60D3CBF5DE0ULL, 
            0xED97DB4E2FE24D5BULL, 0x859B1E991956D9C4ULL, 0xF54F89CDA6F175E7ULL, 0x3A8FDC85D44622B8ULL, 
            0x0D4BE37EAFBABF12ULL, 0xC4919202973A694FULL, 0xA000CE6CE09EBB10ULL, 0xF1D23ABB83E5AD86ULL, 
            0x94F4152FA448D78BULL, 0x1FD22998E6FA3C72ULL, 0xE593F8B623410FE5ULL, 0xE3C20B862BD71740ULL, 
            0xBE0B47CCBE5CB1ABULL, 0xF6E665A226721A84ULL, 0x5C20334AE89EFFE1ULL, 0xF08EB13C701CA543ULL, 
            0x75EBE26B62A8BDCFULL, 0x41F39F4118C9234BULL, 0x1B5B9D7552FA0D4AULL, 0x73A669DC1FD0EDCAULL
        },
        {
            0x63F981382843A37EULL, 0x3E842FD3CEAA3C78ULL, 0x2BA565DD4225B602ULL, 0x301F2088B9E8E127ULL, 
            0x2B8B8D4B3E1D2A63ULL, 0xF56F4EA0C68E70DCULL, 0x40A3136B62F3A744ULL, 0xDAD5348F3F436E41ULL, 
            0x00109891BC2522DFULL, 0xDE2438801A151113ULL, 0xAC6F409A5EAB1BD9ULL, 0xC58506A085B87AF7ULL, 
            0x9623D93032A3A99EULL, 0x943384342A1BB5E6ULL, 0x79F39E0A615E77E0ULL, 0xE78F94A7983CE894ULL, 
            0x3DA805DE6D1D05EEULL, 0x91B10BDC9A4B1C1AULL, 0xB78DF81771EA0277ULL, 0x74AF5EDECB71DD9FULL, 
            0x9D7583E51FB18A5FULL, 0x4BB5332AF7CDE8EEULL, 0x540EA558B45202EAULL, 0x6F1FFC493EB9EFDFULL, 
            0x56665005D47E82F7ULL, 0x3D2E98658D05EA5DULL, 0x9AA1FC3F19BBB1B1ULL, 0x19941284F16260D5ULL, 
            0x436DD7A196A460E7ULL, 0x57ECCFF87E3A7478ULL, 0x21DA63526BDB7C72ULL, 0x838D370C0AAB12D7ULL
        },
        {
            0x36C7681215939C48ULL, 0xA3E5602A8BDA78CEULL, 0xA92509CF35396EFAULL, 0x284B8E752E39DD5EULL, 
            0xC137B8E7FAEDEDB4ULL, 0x6674CB0DE58C9C3BULL, 0xDF43821903926429ULL, 0x4C7145F6ABA885A8ULL, 
            0xCD2452B8DBD2E4D3ULL, 0x5A20D744A0521469ULL, 0x9E7D6B505689C83BULL, 0x875D6A8C2BE971D7ULL, 
            0x008CD19C7C3DA562ULL, 0xB7630316F52AA9D4ULL, 0x2EAEE9CE926F73DAULL, 0xB56587B8D4AFE4ACULL, 
            0x7CF07F31F63BBA07ULL, 0x24E497259FFAEC97ULL, 0xA6B7B49B8ABB199BULL, 0x42C79F1FC17D16A0ULL, 
            0xCBDA13C3B4B4F5D9ULL, 0xDB0091B6C250B933ULL, 0x9C1ED6CC301E93C8ULL, 0xCB8545EC19FACECAULL, 
            0x9593A4B8EDD5C80AULL, 0xB0616D8BA54680B4ULL, 0xFC9ED8E9D1896C76ULL, 0x6CA8B7F5172011E2ULL, 
            0xF9F647B64501D563ULL, 0x447AAAF31331CB9CULL, 0xC7A00EB26E2A1187ULL, 0x7582FDD843F0DFB8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseBConstants = {
    0xCA0A7A0C848839A5ULL,
    0x769FEBA8251BB230ULL,
    0xF362387C86F03D14ULL,
    0xCA0A7A0C848839A5ULL,
    0x769FEBA8251BB230ULL,
    0xF362387C86F03D14ULL,
    0xB41BD67A733D568FULL,
    0x4CA2AE70A60168B6ULL,
    0xA6,
    0x70,
    0xE4,
    0x8A,
    0xF6,
    0x16,
    0x33,
    0x1B
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseCSalts = {
    {
        {
            0xA8DD7802310EB1A8ULL, 0x9D2AA84617F8BC6FULL, 0xCA8BEF463BF332D5ULL, 0xF86F3D0A00BC71F1ULL, 
            0xDAA7A4103E5AF86FULL, 0x4E55790233DB52B8ULL, 0xBEFFBA2D7A9F5588ULL, 0x00D394D047442698ULL, 
            0x0EA5AB089178C904ULL, 0xBB1DB206F5D75CFEULL, 0x0941EDA41E51BD42ULL, 0x433E0AAC191AC9ADULL, 
            0xC490410C44E0EC53ULL, 0x2C2CB30C9E2DD70CULL, 0xF4B4DE6E04FA0861ULL, 0x501D0CA7D3CA976FULL, 
            0xC88255D1DA335B73ULL, 0x2B33E9DE38F08014ULL, 0x8642D3C629DEAE7AULL, 0xC9115A8265DE8E05ULL, 
            0x7608874C83EC9A8CULL, 0x61A293F1F0EF1DDAULL, 0x6D3F6948F737D8C7ULL, 0x689D3FAEF26B0668ULL, 
            0xC96C09F2AFD64D56ULL, 0x417ADAF69D3E5E51ULL, 0x6A2136B1AD60F693ULL, 0xB694716082C4D433ULL, 
            0x075E92653900089CULL, 0xAA77453910148846ULL, 0x6225E6A5AB7B51B1ULL, 0x07421E3604EDBC47ULL
        },
        {
            0x998E052A67FBD701ULL, 0xEC7C8CD0EECBF928ULL, 0x85AD70DE818217AEULL, 0xFF0B3164ADF67789ULL, 
            0x56316BA6F2B51793ULL, 0x9476E5FF0D467A4AULL, 0xF85B71AB35A7B8BCULL, 0x94259159BA478441ULL, 
            0x2A4960BD6C671F0EULL, 0x4147176F746ABE00ULL, 0xDD3C19DDE14B4900ULL, 0xB8238BFD187D80A3ULL, 
            0x6CEC5BBE814F7F21ULL, 0x108FC9649444BCCBULL, 0xC70AD0D0029D007EULL, 0x2F5D69CE0FFBF7AFULL, 
            0x9364BD01D80373DDULL, 0x54C66747CB3E9DA0ULL, 0x09F392017E2885FCULL, 0x51B1C0F3E443E2BFULL, 
            0x0164532F4A23FDECULL, 0x97453A4ED0AB5C68ULL, 0xA5BF1D3D7EA3D21CULL, 0x6EBF4A0302BC39E6ULL, 
            0xE6BA3BA60D2B8FB0ULL, 0xE5EA675782D20858ULL, 0x74AC4660FBC78BE8ULL, 0xCB003BD7B3BE598AULL, 
            0x939C37D2CC16964EULL, 0x27859169AA75EF16ULL, 0x4FF4DA4F65C1C03BULL, 0xA275A26BF775AF31ULL
        },
        {
            0x07B54653A9AF91A5ULL, 0x55D5EE36A6ADB4CDULL, 0xCB997EAF8BA77A87ULL, 0x3D9B4E079C1426D3ULL, 
            0x9CA561CAD954FC9BULL, 0x950450CC0692ECECULL, 0x9561F6264D39F65DULL, 0xF931CB5CBB5AE80EULL, 
            0xE1019019B4E1FE6BULL, 0xCE0B9B7B136B5B7CULL, 0x7B5D4F7274D6BF0FULL, 0x652237E9AE65CBB6ULL, 
            0x3D627FCCC09CC271ULL, 0xDF2E485EABCDA853ULL, 0x3772D214F3FAC606ULL, 0x1FB7D659CEF8AC61ULL, 
            0xA0511914E4978625ULL, 0x6071717169E27D0EULL, 0x915DC46B49DD0CF3ULL, 0x093FECD15EE571A4ULL, 
            0xC3EB1A2451176DE2ULL, 0xC8B6D9346A681830ULL, 0x9725F7E75E099DA5ULL, 0x9E67434C751A3366ULL, 
            0x2A383087BBAFF5E1ULL, 0x9FB07E6EE8E519B5ULL, 0x605705E95CD70BD1ULL, 0x7BE877EA27608E77ULL, 
            0x6002DA06CD02A77CULL, 0xB1F323CDA5A58A4DULL, 0xE3B66D6BE51A724CULL, 0x8DC9C420B37461F5ULL
        },
        {
            0x98AA59D29DFD5749ULL, 0xF0C6EDB37848E414ULL, 0x1B8C6982D5198B3CULL, 0xBE85E7808D884EC1ULL, 
            0xFBEDCCCC8BB1211FULL, 0xA116F6ED18250251ULL, 0x61107FBE6FCF25DEULL, 0x4315CA4AD5741562ULL, 
            0x8327AF036AC98126ULL, 0x20B0BDD1BA788229ULL, 0x3393F82F035C29AAULL, 0xAC7E5449CAC0664CULL, 
            0x9119B2CDB89D1F58ULL, 0xF7E5B7600B23AFD4ULL, 0x4BC7CAEAA4438220ULL, 0x03830D76673456D6ULL, 
            0x958379BBD6FB146BULL, 0x5CFCA39AF4273B8BULL, 0x75D67F3CB2689689ULL, 0x49CF9FAC006373A7ULL, 
            0xE8EB66869D4C2874ULL, 0x86E303630C1B1519ULL, 0xEC17229699BB771EULL, 0xCDC82A5059A3177AULL, 
            0x36EA0CBB2ED4FBFDULL, 0x23E9EB983DDB8AC8ULL, 0x774AF5E1DCBD45E7ULL, 0xBF914B65C4755A10ULL, 
            0x87F54D8FB25F0543ULL, 0x02E92898B9A264C5ULL, 0xBAEC85EB317A2E35ULL, 0xFC477AAD5EADBF54ULL
        },
        {
            0x8031F19499CBCBCCULL, 0xED930B257681D29FULL, 0x0CDBC3BE0658AB9BULL, 0x5D4EFF99B5540C46ULL, 
            0xF66B0E38FD08CD1BULL, 0xD6DE2DB7A423B0ABULL, 0x76E48F65ADD7575AULL, 0xB46603D26F75F4CAULL, 
            0x96F14701C8ADC6EBULL, 0x55ED49BEADDDDCB6ULL, 0xF7D48D31747CDB27ULL, 0x3297350836C7B004ULL, 
            0x370A5C25BE327F73ULL, 0x50B148F661E448E7ULL, 0x497833F3B5C728CAULL, 0xEFEAC8EE7B56DD89ULL, 
            0x6FA3A2950FFBDE7EULL, 0x16A385EA25A8FC20ULL, 0x28ED45FB3CF2CF45ULL, 0x165371EB51D58112ULL, 
            0x95D8FA6B7744ABC5ULL, 0x93EB798B5F47D92BULL, 0x0126663655A884B0ULL, 0xEC912F8A58E7AD45ULL, 
            0x607FF2DD2D30FA67ULL, 0x1DEDFE9FB0273870ULL, 0x48A9AAA94C4AF278ULL, 0x35749098DF28D446ULL, 
            0xA1F03DD80AAA64D4ULL, 0x1A504BA4AA90B900ULL, 0x4DDEBF0F109340DEULL, 0x7FD7772C01AC16CCULL
        },
        {
            0x15281CD3449C9A4AULL, 0x26D01DFF58F70EA8ULL, 0xA777B66A2FEFBFE7ULL, 0x5566485A97DB082BULL, 
            0x22F9B65790C4F516ULL, 0x5951321179EB3CB2ULL, 0x3FB6B019EA99493BULL, 0x3366F67DF62B7108ULL, 
            0x9A128A1414DC1017ULL, 0xA01A586771AC92FCULL, 0x76583FF84D3BA223ULL, 0xF5572DCFEF2886C6ULL, 
            0x5D77DAC315D93B32ULL, 0x07BE6BD1F25D7147ULL, 0x3A9B9BBCF479692AULL, 0x3FA42B6D28983D04ULL, 
            0x05F94CF93550E415ULL, 0x3D521774082BD256ULL, 0x4A97C94C01F9E8EEULL, 0x0A8C9F5725657D13ULL, 
            0x1A5674F0FD75198CULL, 0x804F78DDC430D3C8ULL, 0xC624BFDD547BB697ULL, 0x349DE170018ED996ULL, 
            0x87738DBA784C1E63ULL, 0xD806287A3B7241CDULL, 0xF6613927368C054FULL, 0x399F7456E69C5E90ULL, 
            0xDE9E172EA7933EB9ULL, 0xC1E9483D6CBFC798ULL, 0xE06537667B1C2294ULL, 0x6F545F99CDBBC129ULL
        }
    },
    {
        {
            0x1B1E254EA060B27CULL, 0x4BC2E26AF97FA6E8ULL, 0x1DD4556112A7B509ULL, 0xEF083012E720F51FULL, 
            0x6144748B32E4D6B8ULL, 0x7C57B696D4FCBB42ULL, 0x71CF6A9B1685A1EEULL, 0x94384E7BF1899AECULL, 
            0x5DFBD3FDC5B5EC2AULL, 0x9575F5E6E1677ED2ULL, 0x3AE1B7ADEDEB481BULL, 0xB1B80E68D75CC364ULL, 
            0xF92AB9E55EF2C0AAULL, 0xCA5B46194BF06203ULL, 0xC6F160333D08CAF7ULL, 0xF8A9DBF83ED483AAULL, 
            0xA7E1A58FB1357656ULL, 0x7206272FEB637343ULL, 0x658C2D2F839804BAULL, 0x54F88CDF50B24BFBULL, 
            0x46B4DF897A09D07EULL, 0xD218FA1AA4C7E34CULL, 0x11A324ABC9A3B180ULL, 0x0B0250B4F68304A5ULL, 
            0x42E70BF05160B98CULL, 0x2DB274E808180FA7ULL, 0x8ADE90757CF8805BULL, 0x02D23445D493911DULL, 
            0x599A4241020147F4ULL, 0xC45999DCCBD496FFULL, 0x89555FB460E81B3DULL, 0x9F45995D8840181AULL
        },
        {
            0xEC35E1A05321F09CULL, 0x22D8B07D0C8DA8FFULL, 0x8841DA9241643411ULL, 0x314846DB9C28C5D1ULL, 
            0x739575E866AD1379ULL, 0x34821DFC8BAF6F7CULL, 0xBBD938AB0B686DF7ULL, 0xEB5DAAE72E03991AULL, 
            0x58C664E9601EFF75ULL, 0x7169828C86CD4F95ULL, 0x1C3B6C5FF36A7E58ULL, 0xB973B6CEB3ECF22AULL, 
            0xAB424C21C2626E0AULL, 0x3DE9477B99FEBE58ULL, 0x80245CFFF4CAC618ULL, 0xE9C2EAF85F1A22E4ULL, 
            0xB1ED7CE4EDC73D47ULL, 0x413035AC8CC9CDC1ULL, 0x286FE28E714DFF06ULL, 0x471B756CD236F124ULL, 
            0xB65B7EB3E2DDFA72ULL, 0xD6229FFEF6A4AB29ULL, 0x00A9FD7A97A17E7FULL, 0xF52AA0767FD7144FULL, 
            0xE3676A4BC80BA7DBULL, 0x46255C15B16387C7ULL, 0xA4FB174310B549ADULL, 0x76B2F96EFAA719DDULL, 
            0x772EB500B818AC41ULL, 0xF4340D24B690F922ULL, 0xED86864EB2BA7A28ULL, 0x1AC33806F470DC54ULL
        },
        {
            0x13019B4D7B2CB41BULL, 0x0FA4921560E8649CULL, 0x55A4E6DCD79EA594ULL, 0xB20995B71BB1152FULL, 
            0x0AEB0CCD9278B56EULL, 0xB0372DE06D74AF5AULL, 0x831A097589BC0A3BULL, 0x3797475DA5FBDBFEULL, 
            0x3BD0CC734026A417ULL, 0x71CA329DDF601F84ULL, 0x45C457F8B9F53F8BULL, 0x372AC34F7177073FULL, 
            0x3AD7E9AAF96599A2ULL, 0x7DFD2DF45D81B941ULL, 0xC8CDDAAE677F11E2ULL, 0x17C8A22A3CBB7470ULL, 
            0x33C52065B80CE118ULL, 0xE05EE08D50FCC978ULL, 0x2D7D3FDBB120A388ULL, 0x618070A101C4E4EFULL, 
            0x6D805E2D9191F87EULL, 0x29A8CC6101F34CEAULL, 0x791BE3CE066FD200ULL, 0xF309B11F54A6B90DULL, 
            0x1B89664F02CA8F5CULL, 0x457031E73719876BULL, 0x5B8E2EC6CBCDB89BULL, 0x750708B88668A329ULL, 
            0x6F482B44FDC45D83ULL, 0x36C6C05F3C17A94CULL, 0x790FB5897F3C5B37ULL, 0xACCF2A3361E91348ULL
        },
        {
            0x4CE6E00DC95AF1EEULL, 0xDFB2677F8C7C3F75ULL, 0x08DC7D77730AAD7CULL, 0x3AF8A16389592EC1ULL, 
            0x48A7B43A504C478AULL, 0xC48329C8640A5637ULL, 0xD801EB8AB8358609ULL, 0x7CF9A441B61B9ED3ULL, 
            0x4587DD2F99866AC4ULL, 0xCE1333EC3AA2F45FULL, 0xF8D0157425D32CB8ULL, 0xE5190650921BAAAEULL, 
            0x7F8794127E3CD5D2ULL, 0x04564F18809526E9ULL, 0x0E2CAD53F44CA8FDULL, 0xF9D29544C440FC51ULL, 
            0x5458BA314A3E44E8ULL, 0x18818E3B8198EA6EULL, 0x1412C455B86791CBULL, 0x572B81AD86F039B8ULL, 
            0x19EFADFD8BF9FB44ULL, 0xA33A38F588B5C2C3ULL, 0x0BF8219E102339DBULL, 0x1CE8EEDAA1B6A195ULL, 
            0xA2EA37D5E9F770E9ULL, 0x4BC5702F2ACC88CEULL, 0xE34A6ACB3BBB497CULL, 0xEC707286870E6F4EULL, 
            0xB640ADFF74D8E4A7ULL, 0x51270A608578524EULL, 0xCE7C6D53BEE864DCULL, 0x8AB372A94C1F4DC3ULL
        },
        {
            0xD8404E5B4ED89383ULL, 0x5A8E07B76F71CA2BULL, 0xDBD77B7F35C55005ULL, 0xC90A0F6288A28622ULL, 
            0x0DEF17BCFE126385ULL, 0x2D33E4B07554EC62ULL, 0xAAA58A74463C7444ULL, 0x6EFD65365C4B1277ULL, 
            0x31C718C7FC031487ULL, 0x1C604EAE47502C55ULL, 0xF850F41652A47D79ULL, 0xFDBD52C53112A2AFULL, 
            0xA2883BD46567C077ULL, 0x69F4ACB677D54D3BULL, 0xA401648944781377ULL, 0xE6154A7D4256A70AULL, 
            0x635DAB18F678E791ULL, 0xD39EA1193B35CD8FULL, 0x8488D1165905633CULL, 0xD37CA738C86703CBULL, 
            0x44B8B59C687861AFULL, 0x71CF3ECFC4FD3C2DULL, 0x84E3DF8CBA4E300AULL, 0x2C50A1E64969DA16ULL, 
            0x8C4DEC78EF92F654ULL, 0xE010735E5EEBA6D6ULL, 0x8CB45BAD9AAAF3CBULL, 0x416FB6291286A959ULL, 
            0x427D3AA0F8763DD7ULL, 0xBC8E2ED91B3144F5ULL, 0x679932293C44B8E4ULL, 0x96855F1798E5870BULL
        },
        {
            0x00062B49AB71EA4DULL, 0x773900BF93C89716ULL, 0x7B2BDACC6C026CE6ULL, 0x201ADE0C0BA0851BULL, 
            0x8DB8E7D0EC2577AAULL, 0xEF6ED46BFB6BFB20ULL, 0x0D8F6DEE45CCA602ULL, 0x8F22ACF8164E05AAULL, 
            0x7CC52F88564BC124ULL, 0x1563033005FFA792ULL, 0xC00E1C6693576C2FULL, 0x1B4996B12AC1C8B8ULL, 
            0x8AA1FE5446CE0CC1ULL, 0x8B42B66131476DB9ULL, 0xB58F0F75F227C919ULL, 0x78F2825D059948A2ULL, 
            0x89AFE682E98D8631ULL, 0xD5F86D04CAF53957ULL, 0x36321688EC4CFCFBULL, 0xDA981E67813F67A3ULL, 
            0xF201C31E3AFCDEFBULL, 0x4EF027C83FEB3AE9ULL, 0xBE7721031B2BBB65ULL, 0xA7DF4AEEDF3D25F0ULL, 
            0xA96152FAF7E94722ULL, 0x5565E69A40513103ULL, 0x0659810D705F80E9ULL, 0x16C750972212F8B4ULL, 
            0x8B4BD3BED581A510ULL, 0x3F8F915E62B99386ULL, 0x8193E08C72BC84FEULL, 0x2CC3A5E7B995AE82ULL
        }
    },
    {
        {
            0x3F3D0FB4AEA3BA64ULL, 0x6EF99A03B0B1978BULL, 0xC686EF9A1AD28F25ULL, 0x025BC73E615F4B74ULL, 
            0xE89851845EA60461ULL, 0x566225A27BD90B98ULL, 0x55AABCA1C9FB7862ULL, 0xD1100B08939463F3ULL, 
            0x3E9FAA1E52FFB18FULL, 0x2293AA7A1038F824ULL, 0xB5B1AD6FC7850E6BULL, 0x7878FEEA95C35663ULL, 
            0xDE70EBCF5D87D6ADULL, 0x52ED282982A15509ULL, 0x2AD77C90660B6084ULL, 0xA68B1341267982CBULL, 
            0xC1A804B2C71C0FDCULL, 0x2D28698006B1775BULL, 0xE214FEA45C5BFC53ULL, 0xB5C105CEFAEF6DF1ULL, 
            0xCF66FCF20E19A4AFULL, 0xDD3228016BFA3466ULL, 0x65C256C304A082BBULL, 0x7555B522FB779636ULL, 
            0x0429B5D3F29D4FB9ULL, 0x97B5004AF0872CD9ULL, 0xF354A5AB8D6C9E87ULL, 0xA42BA82F185A1A1CULL, 
            0x5FBDD9B4ED72CBCEULL, 0x0FFBEAAB90E9B7A1ULL, 0x603E8C4874950FB3ULL, 0xAAD0AB9DCAA67750ULL
        },
        {
            0xCBC1B9AA4EC70065ULL, 0x4D2F26A0C0B36283ULL, 0x9AC7F7B00A16A0D9ULL, 0x81DFC0E01525B321ULL, 
            0x344D8A79BEF8B940ULL, 0x61B314BE6DD5E62BULL, 0x4F15B1244EBA7948ULL, 0x80C9125826C72CB5ULL, 
            0x56FAE1AB5A6D391FULL, 0xF1DC1456EE66C170ULL, 0xC1EE2A1B7459E01FULL, 0xA9A4416A13BC5C1DULL, 
            0xE60E4B4EFAC82633ULL, 0xBA7CCC14AC1F5F2DULL, 0xE16B8F2D62E14305ULL, 0x97FC87A99E4CCD7CULL, 
            0x6E94CFDF59F08780ULL, 0x1279F44191BAEE8EULL, 0xD99D2AACD57856B1ULL, 0x163C714E7C295100ULL, 
            0x206E25B05D03BE04ULL, 0x6FF6880D77307A24ULL, 0x0CEAF5E5DD162C3DULL, 0xC6B36DBE1E0B45AEULL, 
            0x2076549EBCD3287CULL, 0x84D088B45FBA09E8ULL, 0x3519EF2B48B65063ULL, 0x0017D907979BC69AULL, 
            0xEBEA4ABABDE485A5ULL, 0xE10CA1CB33A6B223ULL, 0x13A2B4399DA051C0ULL, 0xC102D070BB73BEF1ULL
        },
        {
            0x00F307ABE39E1B80ULL, 0x33F71091B31CB59BULL, 0x4A8B277913E09FE9ULL, 0x574B0768A60349B3ULL, 
            0x04AF9CEED0DF0219ULL, 0x5AC45163948A1FF9ULL, 0x0F3F58C5C29E63BDULL, 0x3F67FCF1A11F895EULL, 
            0x0BCAFEE31045B166ULL, 0xA0AF270BBF944148ULL, 0x39F71545CFF68F95ULL, 0x46ACD93EF07B9B49ULL, 
            0xA6C68C9380ADDB4BULL, 0xBF9A31E23BC24B5BULL, 0xC986F5C04C37FFA2ULL, 0xB3B4794909231DEEULL, 
            0x49E23DD291F63290ULL, 0x7911269551354F2AULL, 0xEF2855EFBACC41E2ULL, 0x9A972BB5D46BF873ULL, 
            0x9D42402B11E92595ULL, 0x3D344B2304CD093CULL, 0x7CD6C57864D13E1DULL, 0x9E82027C2EB9972DULL, 
            0x94774BABF4E14F7EULL, 0x3B642DE142DF003EULL, 0xDF10600DF7013E1FULL, 0x7DF1B22B1AC43C96ULL, 
            0xDFE580DAF372DD9BULL, 0x5ADF816C4403E94CULL, 0xA9D423F0452444CFULL, 0x04EE269BAA0FC247ULL
        },
        {
            0xDC24347EE07F36DBULL, 0x4F70D78422E9C4D4ULL, 0x7FF1C957CFE29E9FULL, 0x80F5C208237B0672ULL, 
            0x62A9809791524E0AULL, 0x1DFC5F1DDBCAA3F1ULL, 0x787BA8CA5A34CA85ULL, 0xF13925FF1AB46423ULL, 
            0x2B3C324FE9FB3647ULL, 0xA4CA168A791684F0ULL, 0x2D9F1BB74CE70337ULL, 0xF91C11077BEAA6B4ULL, 
            0x721FED9745E7F28FULL, 0xAEFE0A35F3040B94ULL, 0x4D0329AD7AB6FDC0ULL, 0x671B3C212999A38FULL, 
            0x840C57ECDE34A3D1ULL, 0x0C649E7ED441DDA9ULL, 0xE763294F489CB185ULL, 0x2C5811D055E87060ULL, 
            0xB06F33512075E13FULL, 0xC6949562A098AB35ULL, 0x46D5C425B545A23DULL, 0x77247CE69ED1B704ULL, 
            0x4487C28C147C2DADULL, 0x268BB770D8D7815CULL, 0xBE982BE5C31F8272ULL, 0xC690D6097B56335AULL, 
            0xD3495059D32B0BE0ULL, 0xB1B4126E7BF1E735ULL, 0x2055A027582D5138ULL, 0x5F5E28B0ECD8F92DULL
        },
        {
            0x52DE25D3BC938E04ULL, 0x4B902F638789B7F6ULL, 0xFC8CAD33CA6FC94BULL, 0x03F01C944EE17AD0ULL, 
            0x1B8FD1E9DFB15BFFULL, 0x6B995E5104D9EE0DULL, 0x75845FB9F4040A97ULL, 0xA6D5BB2B9F039CDEULL, 
            0x38E07BA43C0EF9E7ULL, 0x44FF6A10A6F876CAULL, 0xEB4F05D44B552B1EULL, 0x2322508DB6C9AFBDULL, 
            0x2FD27DE0F8D74EB1ULL, 0x495C28FF25D3E0D7ULL, 0x139EB3958918F301ULL, 0xCF2C0B13DCF24EADULL, 
            0xF4ADA7533F46A30DULL, 0x62485DDCD5007937ULL, 0x17D994D015800501ULL, 0xF4B3BD4B026FB8C5ULL, 
            0x49C39803B4B9E5E1ULL, 0x3A816E23D6D1FD03ULL, 0x4800F66AEC4ACD2AULL, 0x738EACE90D0C38E8ULL, 
            0xBA1389352C604328ULL, 0x23EE211D5A56B66FULL, 0x15963E5E0FB2825EULL, 0xF1203F57B5400501ULL, 
            0x41D3241D4243A16FULL, 0xE2B68B56D46580C3ULL, 0x1025ECEA06E185ACULL, 0xAF349E2940AA47A6ULL
        },
        {
            0x74165ECBCF6CBA95ULL, 0xC72D06B2220921D3ULL, 0xEBB3F669AC225E4EULL, 0xBFBB54F22B0BFC59ULL, 
            0x02E96DDD0AF7697BULL, 0xF665040EC40EBC86ULL, 0xD579C74763EB627FULL, 0x4C6479BDA90FAC39ULL, 
            0xFDE24C2CC4AE37DDULL, 0x344DAFCCE42BFB85ULL, 0x640732F5A5F0BC0AULL, 0x824FF69F5516E75AULL, 
            0x9C140738FE41FAD1ULL, 0x1520D771556C03CDULL, 0x593EF970679BAF62ULL, 0xC7D4536439198A95ULL, 
            0x53932E4D48F8E907ULL, 0x41102B15F9D442B1ULL, 0x069B9EE49A5843A8ULL, 0x8994AAC7FE2CFAB5ULL, 
            0xC20D39ACE5C345B2ULL, 0xE1F23A82B7BAA4E6ULL, 0x8359D51CE29BCF70ULL, 0xA2F2CAEE470242F8ULL, 
            0x60C2DDFD491AC97AULL, 0x30307341F42DE046ULL, 0x3BF499EF8C6D37D6ULL, 0x3F98EB53D0C4325BULL, 
            0xBBEEB1D8F6DAF1C8ULL, 0xA7A7EB93C888BBB7ULL, 0xA12CADE7E0CFCB39ULL, 0xD4767D555CED9159ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseCConstants = {
    0x268D9F97ED963F41ULL,
    0x8BE1BBA2AD35DA3DULL,
    0x583F8AE953B23337ULL,
    0x268D9F97ED963F41ULL,
    0x8BE1BBA2AD35DA3DULL,
    0x583F8AE953B23337ULL,
    0x9C5D1E052B4ABD40ULL,
    0xAEB757D807CF4B3EULL,
    0x6F,
    0x2C,
    0x01,
    0x8F,
    0xCB,
    0xA2,
    0x3F,
    0x08
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseDSalts = {
    {
        {
            0x2395AB584ABE9B79ULL, 0x9FE88B8F5583A7CBULL, 0xA9D803E599F36EC6ULL, 0x1749BADED6BF4B97ULL, 
            0xA5EBEC14CA040493ULL, 0x367A66F0D9E5B4F1ULL, 0xC41274FA7C2DB5FEULL, 0x1A9AA37216862F09ULL, 
            0xE07DCF69E2B01A3AULL, 0xCDEAD3304FF71480ULL, 0x38DD6436DDADC0E7ULL, 0xB856609CCBE4E06BULL, 
            0xBF2A4F8344FF365DULL, 0xA1FB0477BE680E5DULL, 0x4059E5C09C818AF1ULL, 0x326652138E98674DULL, 
            0x93F6480BA9ACB2D9ULL, 0xD0FD246DE11818FEULL, 0x75D2F79BA88F9F22ULL, 0xA3404C15489D053DULL, 
            0xAED34DBD1DF3B1F4ULL, 0x681687DC0680CC60ULL, 0xBC46CD9120493D9DULL, 0x62B2B16FE80E8F82ULL, 
            0x6817BE6CF8318C05ULL, 0xAFACD7B353B56254ULL, 0xD4B164A6D6A76217ULL, 0x0265A5B99CB15BE5ULL, 
            0xADF6536EB7884891ULL, 0xEBEF66F6D1E8C425ULL, 0x87ADA42719DE2ACBULL, 0x8A79F7209A76EBD7ULL
        },
        {
            0x2EC1BB0B08E100F7ULL, 0xA207280BDCC69A6CULL, 0xCEE104552CF35898ULL, 0x4DA3E3F32EDEA9F5ULL, 
            0xC5B46D67C35DBD64ULL, 0x879267E4EBBA3F94ULL, 0x361D90838B9AEBDAULL, 0x9EDD7020AFA827AFULL, 
            0xBB10715DC53573B7ULL, 0x2AE54B4626C142EAULL, 0x396AEBE79843D8E4ULL, 0xDE74FAB7C922F5B5ULL, 
            0x55D4EACEC1635013ULL, 0x9FA8C70960EFC376ULL, 0xC753596B3135A38DULL, 0xE9C468F1D3BF90CFULL, 
            0xA5BB4F0A43BA2816ULL, 0x3059BD8EBEC7D6E0ULL, 0x4B45CE16CCC87BAEULL, 0x312355EB4E6A7E45ULL, 
            0x16741506182524D7ULL, 0x6E442E26FD940FBDULL, 0x070C585BC11B2A57ULL, 0x93BCFDAA8B9A046DULL, 
            0x806A06570D9CB0BEULL, 0x81D630A69FC58233ULL, 0x125281DF7089F676ULL, 0xD8156AE17404F469ULL, 
            0x8B3A83492625CC26ULL, 0xFAA7B842A63EBBDBULL, 0x2AF41443B573BCF9ULL, 0x0380C2A15B0A45F3ULL
        },
        {
            0xF02D765B35A13D73ULL, 0x91CC60558604AC04ULL, 0x799B5A2E55122D40ULL, 0xC71B484F67C24E84ULL, 
            0xFFDEDBD87874956DULL, 0x5D59CE440229E43CULL, 0xA7C82216313BD679ULL, 0x37EFDCD49F5734EDULL, 
            0xE408448C1178C0C5ULL, 0x6F518D67720CB7A6ULL, 0x70B8BB53614F5B04ULL, 0x7C2377618CCD47D3ULL, 
            0xC8ED64891B6209AFULL, 0x71436233A920F430ULL, 0x62DBA4BC1B7B246AULL, 0x5C000DF190219275ULL, 
            0x63897110150F9F4DULL, 0xEFE82B58FCFCDEE3ULL, 0xAE6DCBA5A2B0394AULL, 0x0C96D95D3E0BBB99ULL, 
            0x1ED6FF0957BA9277ULL, 0xB0A1814ADC62770CULL, 0xD4F578C9A3AFC9A6ULL, 0xEA4EFEA2625EDB6FULL, 
            0x965F93E47237AD00ULL, 0x999C83A63071CD37ULL, 0x09A823A3F5A8B30AULL, 0x7FD97E63634FDA56ULL, 
            0x87E4B809A7570327ULL, 0x59BB670099330F8DULL, 0xBBC4799CB688BE1EULL, 0x5FC7EA938CC2AFD9ULL
        },
        {
            0xB0FCFC725DEAA6B9ULL, 0x058398D9B22A7CC9ULL, 0x3A066C02BC150AF5ULL, 0x1F7ECF0462395F4EULL, 
            0x2FE0E5F2DB849513ULL, 0xB365DA71E5606980ULL, 0x1580388A2327B41DULL, 0xBE54AB961EB72325ULL, 
            0x7AF1CC5C0863977FULL, 0x34AAB2C0F7D1FE39ULL, 0x273178B6784D3AFCULL, 0x4A20DB40C4DDF340ULL, 
            0x003F3723A15C5C74ULL, 0x05ED53FC69586820ULL, 0x0DD597DD008103D6ULL, 0x9869788CC5BCECC8ULL, 
            0x3736C7AE2EC07FBFULL, 0x7CBE834696B96B22ULL, 0xF90ED8F7032B9B5DULL, 0x0238B3A0AC4EDCFBULL, 
            0xD178107C49C10ADAULL, 0x3B92516A621DA473ULL, 0x772B0C6904EE48D7ULL, 0xAD48A83C8B6FE2EFULL, 
            0xC86D0F9B254FD26FULL, 0x4DF245990DC25D97ULL, 0xD2911BDEFEBEDC9CULL, 0x05537B0B434F3FDFULL, 
            0x64A9C9047A6DF517ULL, 0x3CDDAF40C44267D0ULL, 0xB98CFAC64B015E5EULL, 0x459FD23989AB1E46ULL
        },
        {
            0x5D2F64BFE5155306ULL, 0x4F1A16BA189B8B8EULL, 0xB5A5B1A226E707EEULL, 0xBB9074BD81B144BAULL, 
            0xD06D46E249213C88ULL, 0xBF32BE81D34F5012ULL, 0xF827DEE2E3106F3CULL, 0x58F3437780A1FF33ULL, 
            0x3F18031E201D2CC0ULL, 0xA25BD11DE3022711ULL, 0x6017FFE5E1BE0687ULL, 0xD04C74DCB1AE122BULL, 
            0xE308CF3E935EFCCCULL, 0xB81EDA08DE63DBB7ULL, 0x5ADDE81683DCDD66ULL, 0xC8F6094B46906305ULL, 
            0x8E33419C928EC109ULL, 0xBCD52CA106F292BAULL, 0xDEE89087C6B1B079ULL, 0xD32EE5D9FE00B6EAULL, 
            0x06CA1E738066DC22ULL, 0x666736A9C1B3D584ULL, 0x6BDE04BBAE5E6202ULL, 0x79AA5216C9D0B39EULL, 
            0x7F11FCF8211882CEULL, 0x4F0257CEA002E0ADULL, 0xAC7AD55139DA731AULL, 0x80B8ED173A5D6874ULL, 
            0x690B48803604EEB9ULL, 0xF32DC3DE11BE0725ULL, 0xB9776E46FB87B65AULL, 0xE23400828AE875EBULL
        },
        {
            0x2AF044FF5E2A588CULL, 0x2F1653FC1245A1AAULL, 0x92E63164FAF772D4ULL, 0xDA919DC0D79B51ADULL, 
            0xC44565680757AE39ULL, 0x5E758D44ACE3C950ULL, 0x0C860F8CEEA2C971ULL, 0x8D57E7401BBBAB04ULL, 
            0x4E105B7D4990F469ULL, 0x6907CAFEF52B61DEULL, 0xDC25314DB1E16044ULL, 0x6934FCD17B72EA74ULL, 
            0x59282A810EE5C3C8ULL, 0x37B16A1DE36A0217ULL, 0xA0E3EDC8DD99B232ULL, 0x33849F4DDF31E824ULL, 
            0xFBF3FEBE640C755CULL, 0xD8E32DECA2CCA53EULL, 0xFE9D973CC5B03F3DULL, 0xD36786A86CB84A9BULL, 
            0x49ACBE2BCC3D415DULL, 0xB2AB9DDF982922E1ULL, 0x9E7B2E1DDDB67065ULL, 0xD491B3E35A43DA2EULL, 
            0x5BDF9BCD3E513B8EULL, 0xF3594EEEDD77233CULL, 0x17535F9FEA70618EULL, 0x9F9B3521E0B11B5EULL, 
            0xEBD658E11DCF2ADAULL, 0x2EF60244E1453711ULL, 0x02CBB7098C37CDE9ULL, 0x07213C244157FAE2ULL
        }
    },
    {
        {
            0x301B143C427AB9AAULL, 0x413E79526471B1D9ULL, 0xD3D3BAF9E6B88ABAULL, 0xA2611DBE667E091DULL, 
            0xD74A79B1109D4F33ULL, 0xB6DB12A428FD0B7DULL, 0x09C7A43EDA2692AEULL, 0x141D1D4163FFE24FULL, 
            0x3EB12FE8194C7D0EULL, 0xAA454C58F9CF3246ULL, 0x0355BB48F214D80FULL, 0xD50922AECA928E42ULL, 
            0xC14CDB3F81FC1377ULL, 0x201D8E6AB2D5AC37ULL, 0xE15430270559E850ULL, 0xAB931C8105F77F3DULL, 
            0x9CD7FC24350E7AA0ULL, 0xAF96201023A2CDFAULL, 0xEA775DE8E7FE6892ULL, 0x7BDCDAC968AA067AULL, 
            0x547F2D842DFABC76ULL, 0xC72F88062FE1ADDAULL, 0x5D2C9C75F471DEDFULL, 0xC4F3ADFA5ADF61EAULL, 
            0x5CBC997F1D874104ULL, 0xF0EA3359FB26AE6BULL, 0xE841F4FF51180B8CULL, 0x13EFF65410358FFDULL, 
            0x3915F83E234EE55FULL, 0xC227DFDB316FF283ULL, 0x99B5A4C386FF63DEULL, 0x591605C9FCB7D507ULL
        },
        {
            0x0E1D5CC112837C80ULL, 0x8160AD465773A86BULL, 0xB37B46E3E95EE968ULL, 0x8A935F73D4BA1FB4ULL, 
            0x2FC4F70D50D0AD40ULL, 0x1148047DC69EB943ULL, 0x4C58152CD501E8CDULL, 0xCE29E4CB6202D8B9ULL, 
            0x4A2734CA60444B53ULL, 0xC45C55D8AA6518E3ULL, 0x29247D30D379D5FEULL, 0xDB9E03DC0325C633ULL, 
            0x6BFD52B1B86EF431ULL, 0x71744381D0EAD564ULL, 0x98F0BC32D265E91CULL, 0xE8158A8EA17C615CULL, 
            0x97E0EE75721C4507ULL, 0x68317A1F46272CF8ULL, 0x8BF3CC71AAA45F63ULL, 0x69622CF1DCE92EB6ULL, 
            0xFEB0BBD8230B9DC7ULL, 0xFB84B2AA4BC1A32EULL, 0x2220BE9AFA294C0DULL, 0x20A4DE79F9ED9AA7ULL, 
            0x4789B34B8A9024CCULL, 0x104BE21A95F23242ULL, 0x403B3A92AED21224ULL, 0x37B8800CACD91A6FULL, 
            0xEB25FDB1701D7D96ULL, 0x7FBF07307889F59EULL, 0x99D123054C47438EULL, 0xD49EBE60FEFBBF70ULL
        },
        {
            0xC616AB98CEE81E62ULL, 0xC8E8B25D9BC1DF3CULL, 0x36A0F9F969EDB5CCULL, 0x9635D61798D95A85ULL, 
            0x77B3604495DC40B7ULL, 0x145ED1ADF1CCA84CULL, 0xED34E08F48579F9DULL, 0x833498592279CD05ULL, 
            0x957CAE7FF5CD72EEULL, 0x951BD666A8C10B23ULL, 0x47FFFA983E1A0648ULL, 0x02D62D12F3F5F969ULL, 
            0x3FB7DF2D5858628BULL, 0x59A7C0DAD5373EE9ULL, 0x27DD88C6767B7452ULL, 0x524A1EFA9AC16C60ULL, 
            0xBD59B0493EB1A1F8ULL, 0xA94FE0C6B32B0983ULL, 0x4D8AFAE728FD51A6ULL, 0xCF647DA5C4D30C46ULL, 
            0xDFEF3C641DCFCEE9ULL, 0x9C2B137E13F2C036ULL, 0x32E54797DCF063BEULL, 0x90399828A332074CULL, 
            0x36763B546EE53FC8ULL, 0xE9D7E414C918D509ULL, 0x7DF03E918A21F81DULL, 0x1A0D1D1E47074D0BULL, 
            0xD77520CB36338561ULL, 0x97CF8AE0192EF89EULL, 0x16F1FE422736B6CCULL, 0x8AFA95270AD9C805ULL
        },
        {
            0x98A180A612028982ULL, 0xA372EA982D67A213ULL, 0x238CF374ED655D49ULL, 0x63460677FF41036FULL, 
            0x98AE86421B793E7EULL, 0xA289D9474425D3B7ULL, 0x8114513EE2CA6B52ULL, 0x554DC978687080DBULL, 
            0xB541E6FB8590A617ULL, 0xB0116495E5DE105EULL, 0xD45E5CC17CA31974ULL, 0xD74FB8C0CC980EE5ULL, 
            0xC50F7DAA133C04EDULL, 0x4A0D2C19741D9200ULL, 0x3A9B2970A511152EULL, 0x1107C63084CC39A9ULL, 
            0xF3E29DDFC2676258ULL, 0xE77C76E8261A70E7ULL, 0x6E3448508BB11763ULL, 0xE809DBE20DA30374ULL, 
            0x62F474B530E07EABULL, 0x2C177C8EA422D94CULL, 0x4AECD1CA2C22C6D8ULL, 0xE48260DCF3F5874AULL, 
            0x2370125421F346F6ULL, 0xF4B803598B7DE9A2ULL, 0x35DC3B1FEA5A230CULL, 0x9A18FA66F870269CULL, 
            0xB403F8DFC85FDAFCULL, 0xB697E4477B67F7BAULL, 0x38438DEE9D9777C2ULL, 0x6595D96636B6ACB5ULL
        },
        {
            0xB29562F6902DF246ULL, 0xE44E82674B3D2EC8ULL, 0x863F57E4223A81ADULL, 0x2901F86412D34D79ULL, 
            0x728B22487E630006ULL, 0x19FB9A234383FDA7ULL, 0x1BBD451060A1E909ULL, 0x7DF2FBE0DFA4A03EULL, 
            0xEDB8C4C4A04BAB66ULL, 0x0D9FC5386AA0960BULL, 0x4BABFE8B0E5898FFULL, 0x3FBA86B323FFA11FULL, 
            0x724E783CA338FF4BULL, 0x10FD8166F8CF20A5ULL, 0x558BBACE8A060DA4ULL, 0xCC0D1A07BA94333AULL, 
            0x802B062F0409E1FBULL, 0xDDEB1B7ED18A41CEULL, 0xDD8110466E74867EULL, 0x64F7AE362B8DF914ULL, 
            0x73271E42C6F0B51DULL, 0x82FA6036B34876EEULL, 0x7890ABF05C3EBDFBULL, 0xE0C014C141DE5AD3ULL, 
            0x66E4D48395A45155ULL, 0x34C2494EA1F93EB9ULL, 0xE8D2B0F038F280FAULL, 0xC730ACC3D44B4E2DULL, 
            0x3113191FB407498BULL, 0x412A84E63EBE8A99ULL, 0x20FB0281AD2FF50EULL, 0xECF540379ED2298DULL
        },
        {
            0x3C25C40E4061E5B6ULL, 0x03494FFC3AD47D12ULL, 0xB93A0D6E73DD7B9BULL, 0x0D5056E4C7FDC857ULL, 
            0x313243193944373CULL, 0xE00AA198E0367E2EULL, 0x71EB5369D563404CULL, 0x905F2984F56CBF12ULL, 
            0xA7C3B2CB6E333C25ULL, 0x8E5C751111C44815ULL, 0x3C0B3B8E3CD65FC6ULL, 0xDC72F2A50DDD0C3EULL, 
            0xFAA8B2DD5360EF8DULL, 0xFD18D774B9BA59D0ULL, 0x1BD3F49C197B2804ULL, 0xEE6A6DF2AB1C04B5ULL, 
            0x7F11AC1C7C8B3B27ULL, 0xDF35199DBAE7C31FULL, 0x16A73BFA73454762ULL, 0x938FC4264261CC73ULL, 
            0x79DF20750DF6063BULL, 0x6CCCDC87050CDFF9ULL, 0xD616D3A2D0852D14ULL, 0xDA8DE2ED06EEBC77ULL, 
            0x65926169E472DC9FULL, 0x37E2BF8C4066D7CCULL, 0x52B1724F2BD37263ULL, 0x629BAC761418327AULL, 
            0xDDCD335DC2CCFA78ULL, 0x1E752A3004003868ULL, 0xF0B02889A066C2D1ULL, 0x906FBC52B6906870ULL
        }
    },
    {
        {
            0xC3C353EA4B759301ULL, 0x107E1B942E3AFFA5ULL, 0x45AD6DD8DB57CC0EULL, 0x7B5FFCBC4BF937A8ULL, 
            0x5E5B5B9BB6F59AA0ULL, 0x1031145272BF780AULL, 0x8F701CEAFC367B47ULL, 0x35358F2B1456A22BULL, 
            0x7A28E6400DC5A1B0ULL, 0xE1EB93ACB6D38E79ULL, 0xD43AB1D1C174D8B0ULL, 0xEB1EED8F542FE44BULL, 
            0xFFE31FDFB6942A3EULL, 0x779AE9F18AEFD18CULL, 0x2F956E1C16B89729ULL, 0xDE0207F6A8D3759DULL, 
            0x183018A0906FC7BEULL, 0xD2966FA3A604560AULL, 0xC87FD98A8C4B9ADFULL, 0x7EB477B15E63E5F7ULL, 
            0x89E08B8D7C5FDECCULL, 0x93B56FAAE9750D7DULL, 0x0BD6BFA483792AD8ULL, 0xBA56610021260058ULL, 
            0xFD7A5C033E66AF6DULL, 0x10615546EC003A15ULL, 0xAB0E36B74E1DFAC0ULL, 0x28C5D4CEF42FCADBULL, 
            0x4626EDA7FC74136FULL, 0x7CB4850650150AC8ULL, 0x555BB61BBC9BBE0BULL, 0x7611F802CEDEE335ULL
        },
        {
            0x9C1A2EE9859C753FULL, 0xD8C47C95DAB7A79BULL, 0x701A55FA738550CBULL, 0x399EAC782AFC7AADULL, 
            0x485C308F144CD456ULL, 0x62C19AEE20B70709ULL, 0x8F5BE82693066C82ULL, 0x071618F9FB2C8F9DULL, 
            0xE0DA308F9A9D669BULL, 0x33020593EE864162ULL, 0xB088C173BB99838AULL, 0x52CA1D8D4BF25992ULL, 
            0x8109D0381D6992ECULL, 0x5490BE18BBED7F69ULL, 0x8A84B2DB5E8CF1CDULL, 0x3F46E9C4F4B6AA2AULL, 
            0xCF9F85D31CB715D7ULL, 0x93115B522E97A17DULL, 0x6E15BF7517110EA3ULL, 0x14754AC24E53BA23ULL, 
            0x6969CC6D87732FA3ULL, 0xABBD669CB8CCD846ULL, 0x6B6FA761F92B5B11ULL, 0x12417A8BD7D654BDULL, 
            0x0482D6A71D931D1EULL, 0xE5657BA38B898485ULL, 0xA8EB7D888317661CULL, 0xB3FC9495A573020CULL, 
            0x9E2A740D526319A2ULL, 0x332803CA9E721FC6ULL, 0x104B6A5213EC5901ULL, 0xBC69455BC98ADC4AULL
        },
        {
            0x6978AECDC3CB0768ULL, 0x644A7B981BBEBEA4ULL, 0x1508B6DD9414B015ULL, 0xB7FF455D9CB58E12ULL, 
            0x1F9CB9ACD3F8427DULL, 0x1ED86433C9088CEDULL, 0x0AF38D24DD12361BULL, 0x901158195485B7F0ULL, 
            0xC73350862CBECE4DULL, 0x0BDA02E59A04BC60ULL, 0x925E2FA1A21F4FA2ULL, 0x6A5F6BF3702AB1E5ULL, 
            0xBF0CAFC2C0ABA2F0ULL, 0x9C0D6F7990BDD84AULL, 0xC87DFB8033E8C7DEULL, 0x1D0D2D9C4367AA77ULL, 
            0x04D2880B634F6933ULL, 0x44D2B2CA82DCF4DEULL, 0x13662C3888B5B378ULL, 0x51EBAF630DE68201ULL, 
            0x37AD422625B8FD39ULL, 0x3A567DC6BCFE5E5AULL, 0x8E3919A01BEE162DULL, 0xD364A0085077B989ULL, 
            0x718FB5FC7761BBB4ULL, 0xF0B40660ADFE3C8CULL, 0xECD928BCF6AA7398ULL, 0x50188F0094B0E4E5ULL, 
            0xA84D80EC7E97D052ULL, 0xF94B03F2937E1FE6ULL, 0xAAD4383EFDD5A011ULL, 0xE7169C7619613560ULL
        },
        {
            0x125C6F1AAC46C840ULL, 0xD3F4555A828350AEULL, 0x614B6D9F59CB98B6ULL, 0xA24E6EAC29C85B6FULL, 
            0xF6AC454123BECCF7ULL, 0x25FF4515534363D9ULL, 0x3D86DD7C43295DA8ULL, 0xCA26D35E27F546F5ULL, 
            0xB3A98C9A76B0028DULL, 0xECC30A573A6170D0ULL, 0x1466E59C19BFFD9BULL, 0xE554444FCA8EDA6AULL, 
            0x221E5A1AA45A20B8ULL, 0x6BDFA5D04916B04CULL, 0x2044E569E87E104BULL, 0xD950ED96F6C4F1CDULL, 
            0x0AD971FDC43CAB9BULL, 0x330F320B15546E1EULL, 0x217F3DC23DC78FE6ULL, 0xF2ACD9BF2CE147E7ULL, 
            0x1E6ACEBEC1A81202ULL, 0xDB47560FF6F7CCCCULL, 0x7189B6BD14FB11C8ULL, 0x9E0D01D85BDA9463ULL, 
            0xD01201B1173CA69AULL, 0x7CF52ADCB67F2527ULL, 0x7FF1708F13A55FA4ULL, 0x23D337BD519453A3ULL, 
            0x7D4B5BFA63CF5B54ULL, 0x5D6182F7FB69AFF1ULL, 0x01D81C0B81701D2DULL, 0x0B2F1D2CC9293954ULL
        },
        {
            0xB6B5418595A26A1BULL, 0xE625E57A8A079BD5ULL, 0xB920F348CDCE7323ULL, 0x835441A6CEEAAD09ULL, 
            0xAEAB26D6F467B58DULL, 0xFEE87FCED20D34B5ULL, 0x01AA924295FC59D5ULL, 0x94448D7EFB227D4DULL, 
            0xC1FD7FA5633C1646ULL, 0x8B1993E8CCF898EEULL, 0x6C937FD77AC90A5CULL, 0x036C06D93C1BE919ULL, 
            0x7AD36EE2738A3859ULL, 0x908C623BE5B3D5DBULL, 0xFDE792A5995C1E36ULL, 0xD6A3F8E0D4A0C006ULL, 
            0xCFBFB4FACBAE143FULL, 0xF8CA566E0631BA12ULL, 0x3B5BFF9CB87F88A4ULL, 0x97E74534D4216A86ULL, 
            0x20F1732FE26F8796ULL, 0xCA7A6AC2BF3295E8ULL, 0x9A9507B9F58F2575ULL, 0x53607DFD5ABD2236ULL, 
            0x1FC179896C93F6D2ULL, 0xCAFE56F0562BFBA6ULL, 0x2FA2FB7CF4243AD9ULL, 0x8D13EC9739609073ULL, 
            0x8BFF1323F3CA0A82ULL, 0xCCDDF7D728D3E782ULL, 0x9C2CF6AA4EC33395ULL, 0x8411859EF3D2C5DAULL
        },
        {
            0x8E141B135F42348EULL, 0x5CCEC6B81D7C5526ULL, 0x817C9263FA99D933ULL, 0x342710E1E0653489ULL, 
            0xEC0DF975E03F3E2AULL, 0xE20A9208B843B538ULL, 0xF7317E163C27ACDCULL, 0xB8186233867B55B6ULL, 
            0x30EE463A44A24EB8ULL, 0xA06609EC26C1E047ULL, 0xB430D94703966DB2ULL, 0x240820133E92179AULL, 
            0x6BA61DD92E9519A9ULL, 0xBB7D3A003C31BFE0ULL, 0x25D36E88C84B412CULL, 0x0332E3BA57E7B10BULL, 
            0x3F582EF27DF67EFEULL, 0xAE8937C97B804591ULL, 0xEAAD6F7C58F4C933ULL, 0xFED20CE93FAF2B9DULL, 
            0x5D3E79C82493E7FDULL, 0x850EF858E653FCB1ULL, 0xEEE532A9C11218BFULL, 0xF3A4ED46135B7885ULL, 
            0x1F809E8329D14470ULL, 0x31E46B83D1A3ED25ULL, 0x0E569A8A25924CC2ULL, 0x11F1C0815FEC927EULL, 
            0x48569626F202B043ULL, 0x5C6AF4FF7D7157BEULL, 0x85FD7FB14088A835ULL, 0xA37F144B2AB95E7FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseDConstants = {
    0x6EAA34F3C9E68F8EULL,
    0xF2666357C11183C5ULL,
    0x59DA6A28C08F4AA1ULL,
    0x6EAA34F3C9E68F8EULL,
    0xF2666357C11183C5ULL,
    0x59DA6A28C08F4AA1ULL,
    0x00FCFB34FD28264EULL,
    0xFD0CB3233A4DB85CULL,
    0x83,
    0xB0,
    0xAC,
    0x3E,
    0x9F,
    0x88,
    0x85,
    0xB3
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseESalts = {
    {
        {
            0xCA8FCF478ADE79C4ULL, 0xBE1ECC87ED15EF8FULL, 0xBA25EED6B81A2762ULL, 0xA101B4AB4CA556D3ULL, 
            0x8826B1189B16A419ULL, 0xF8995F8F407D7F75ULL, 0x11893E829CE28130ULL, 0x06CB00FA7A29093DULL, 
            0x3231DC29B7ACE965ULL, 0x247554E0F2F49521ULL, 0x8A6CA4696FB4FFD0ULL, 0x564D368B1A2D928CULL, 
            0x0CA5FF04243C640EULL, 0xDC2A9E737A675D0BULL, 0xA044A25DDE855468ULL, 0xF7217746A91A8240ULL, 
            0x87A27159C7619200ULL, 0x11E69DB2642DD79BULL, 0x25A03BD2AA6BD442ULL, 0x552A10D5F064936FULL, 
            0xF54989DE8527ED05ULL, 0xB37480D57E967E31ULL, 0x8A7E31D3AF50B308ULL, 0xF3CE4F4D306FBF2EULL, 
            0xDDD42B84B9A494FEULL, 0x30A8EF1698236BD1ULL, 0x6DE454C08DA3C6CAULL, 0x16CE62D26A6DC9A0ULL, 
            0xFD703D2EF9243183ULL, 0x3C87503810B78A47ULL, 0x3FE8AEFD99E62509ULL, 0x7BBAB58E9EC8B73FULL
        },
        {
            0x217D8D45DA85F074ULL, 0x7E78DCD20698A08EULL, 0x3264C7CC1F457114ULL, 0x2AE125208255B719ULL, 
            0xD62DDDE1169A3571ULL, 0xD9D90DC034A98C62ULL, 0xE05A1C2BD1C33A94ULL, 0x314A6B621C09A6CFULL, 
            0x8B47907B9D121B2DULL, 0x39CD3C43256396D0ULL, 0x5975224C2B575BA4ULL, 0x992F8462BB7D4166ULL, 
            0x06FEB811C860D40BULL, 0x4A9A92CD51B3990FULL, 0x1F3523343F7786C5ULL, 0x58DF5803A2C69578ULL, 
            0x32A2A2FB0B0FCDFEULL, 0xF31C1587026C0D03ULL, 0x888CDC17035CE836ULL, 0x917CD4AB290677E0ULL, 
            0xC8F4008D52C61068ULL, 0x5E4FA8C3096AB14BULL, 0x850FD6E6A01D1A16ULL, 0x7D04433EC57E1E8AULL, 
            0x918113E7BB7E8E07ULL, 0x7C0F272DD638D32DULL, 0x8CE31B045CF5FD45ULL, 0x333CEAEB192BC2ECULL, 
            0x5A0934D8257A4018ULL, 0x051A27ECE66C866FULL, 0x34F63C318C926D6CULL, 0x14DC68491FDB9674ULL
        },
        {
            0x4C67DBEB62B5FA88ULL, 0xA1948613FEBC9EF0ULL, 0x401B6D0E39FB7E23ULL, 0xDFBD4D46E519129DULL, 
            0xDD5E9B8F7292D837ULL, 0x9C2E37E3BAF5FBF0ULL, 0x7A0FD72ED47555E4ULL, 0xFBD64900490A755BULL, 
            0xBA3267E08471D02CULL, 0xE3110A92476642BEULL, 0xEB9E8C0EBDD524EFULL, 0xFF3F13D1FE72F559ULL, 
            0x660CA5BA73BB49E7ULL, 0xED2CE6ED49BEE510ULL, 0x595B4273D321DEDFULL, 0xC84BED678236829FULL, 
            0xC1408B0B30DAA716ULL, 0x6497DB511A0370C1ULL, 0x14D4E363B77BB34DULL, 0xACC6A974F9FA018AULL, 
            0xFA4B8CD9909F1312ULL, 0xE1F132992EDEEB32ULL, 0x7A02116382D1651AULL, 0x1AC0CFF075D0A6DAULL, 
            0x16CB816146E3889FULL, 0x445ACEFB931945A9ULL, 0x3810883B8BDC807CULL, 0x8DB515487085523DULL, 
            0x07BBAA5E6F80BD44ULL, 0x97CFC653342567E5ULL, 0xC8B604403D558C48ULL, 0x78D076F9BABBD0A4ULL
        },
        {
            0xD3427E030745A2B5ULL, 0xFD58897960FBCBFCULL, 0x4F0202E64F1DD649ULL, 0x544A313AF933891FULL, 
            0xEA7B16FD55441AC9ULL, 0xCC0C670580CB865DULL, 0xA9F19D3895B96FE1ULL, 0x00D6842AD3330232ULL, 
            0x4BFB959A48FE5C3CULL, 0xACD175D0597A3DDCULL, 0xCF0FAF1878B09E76ULL, 0xB42475FDCBA8122DULL, 
            0x0BB4E8D1DA50C2B2ULL, 0x6A4081F314E19724ULL, 0x8E648485B43C8138ULL, 0x3CD32693D952AEC8ULL, 
            0xB0A654788216C667ULL, 0x5DBDCC5FE4902B28ULL, 0xFF3E155F522DBB62ULL, 0x8CFA2C90CFE7565FULL, 
            0xB721A9CA27B621A9ULL, 0xD0922D33F3AE04DAULL, 0xF9A74D278E27E77AULL, 0xF1B39027A6D195C2ULL, 
            0x4B8AA633D859D3B9ULL, 0x11E0F92302F5DAFAULL, 0xAD39DB780BD02575ULL, 0xDF80010A9D934C64ULL, 
            0xF684FF2214DBB443ULL, 0x510AACB1E0982246ULL, 0x39A4F1629A0D556EULL, 0xBBB1B5E65D1EBFA6ULL
        },
        {
            0xB78E52E5E5216188ULL, 0x34C4B25F3D06D127ULL, 0x156B5C8765983D04ULL, 0x65BE534F5F1B5FDDULL, 
            0x3CDEA1609C20C975ULL, 0x0D755D7318B04595ULL, 0x1A3FD9B88DB750FBULL, 0x7574E4A3EBBD43C4ULL, 
            0x3BDBA87C8AEB6CA8ULL, 0xBE5CC1E52E633C3EULL, 0xCDD6DBC708F82D8FULL, 0x839B6DAE03802946ULL, 
            0xC536F6AFE7A43E36ULL, 0xE59B62D9C822B01FULL, 0x6BA8E14BC7A03197ULL, 0xAB98BC21D1A74B8CULL, 
            0x4F1749827B93E3EEULL, 0x801A7DB52013F0F6ULL, 0xABEA08265A55CBF7ULL, 0x54A3935239716C09ULL, 
            0x22038F7A6707F129ULL, 0x57B5E5C763AFBC76ULL, 0x0A03164D538AF590ULL, 0x9189666EC61657B8ULL, 
            0xAD5DB5449D9AA7F3ULL, 0xC499A06562FD7E45ULL, 0x8FF0DAA222E99A2FULL, 0xC28935B8DF4BC427ULL, 
            0x8B7A6F558B8FF49EULL, 0x698A10ADC6521499ULL, 0x599C906CCC4AE90BULL, 0xB595532912237DB8ULL
        },
        {
            0xA0C3A04663E123E3ULL, 0x7FF0D949F1D81E2FULL, 0xB02609ECB4379587ULL, 0x6AFE5F03F9533B95ULL, 
            0x9B02E4C84E94794DULL, 0xB826009C6AFF5FCAULL, 0xB07D15D4858A0A84ULL, 0x8B6C77AA00D89AF6ULL, 
            0x440A8A551075E0CAULL, 0x0F87DDF6061ADD4DULL, 0x938E6F5F7B002BAEULL, 0xDAA2CBAD824A82FEULL, 
            0xC6B6991A66F12CE6ULL, 0x20F080EB8CDDBB16ULL, 0x0CEB0E896DD272C7ULL, 0x40E3A9B0232D8164ULL, 
            0x7E34A9A79C95C3F0ULL, 0x4B89975DC2DC3624ULL, 0xAE96D354C3FAD6C3ULL, 0x45F14D2F8649886FULL, 
            0x3D2D81D5BF41FCB9ULL, 0x56035B5EC2A66D52ULL, 0xFF087D83366C944AULL, 0x5B9AA0F0B87316A7ULL, 
            0xDC8EAA596E7591D3ULL, 0xAFD6C8C3270345E8ULL, 0x8CD8B87F5580D79AULL, 0xAF8BDD0EA987C64DULL, 
            0x1F9E532316B4DD14ULL, 0x534EABA7BF69969EULL, 0xC7FD2E3CBC624E0CULL, 0x6AA60AFBDB85886AULL
        }
    },
    {
        {
            0x3199E0E1C6DCF39BULL, 0x9A145B18ECAC1AF7ULL, 0x1023402996E926FBULL, 0x061262891EA347B2ULL, 
            0x11DB61A75FCEC2E7ULL, 0xA6677206BD8BAFE6ULL, 0x7C249FF3D81CFC5CULL, 0xBE8A2D55D1CF08EEULL, 
            0xE9B30675304DBE46ULL, 0xACD558CAE3461864ULL, 0x27320BC53E7574F7ULL, 0xD1FAFA4CE111ED53ULL, 
            0xEAFCC392ECC0CF8EULL, 0x9ADC6C52E2151DE1ULL, 0x2EDD4684DA83F62AULL, 0x8559F7079D58A452ULL, 
            0xADCC6EFB62B564E2ULL, 0x7894C3658DDCB66FULL, 0x70B2EE3219A0E400ULL, 0x330A27E9191B540FULL, 
            0xCDAB5EE7186A0E99ULL, 0xCB16B6CF30CA58B8ULL, 0xF8E4D385F1F7352BULL, 0xE483B1DD0EF4ACBDULL, 
            0x00E0266DA0E10383ULL, 0xE2F5302440CCCDF7ULL, 0x7EAAEB626576F868ULL, 0x7A167C383D9EF8D9ULL, 
            0xA939259BBEE3512DULL, 0xEC08FDC2E3C94970ULL, 0xDD450C660B4E9F7EULL, 0xAC8892B1394A93E3ULL
        },
        {
            0xB77DEB325B1367C8ULL, 0x7DF6B4841E8589A7ULL, 0xD9371F76DAEBF9C0ULL, 0xF0073CAD5D234AB5ULL, 
            0x0CDFAE26EB89DEF7ULL, 0x7900CD7DF39F7893ULL, 0x68A10695323DE9ADULL, 0x3A9E53AFEBC3CE25ULL, 
            0x0D1875F70648FD59ULL, 0xDDBDE136F24007D0ULL, 0x9C5C12A086310B96ULL, 0xDE5E294532F287EDULL, 
            0x2E3B0B9B865C15C0ULL, 0xB0EEA0D8886DDDF5ULL, 0xBD37E6D0CD0B96B4ULL, 0xE96E8631BFF0984DULL, 
            0xE440D301C505A236ULL, 0x1B1CD1125FC9FFA9ULL, 0x4456525C1C9BC6B5ULL, 0x142CABF3C4CC9241ULL, 
            0x3EEE3027FD4D1E76ULL, 0xBF13F5BBC735ABBDULL, 0x3406BC28B7BE9BA9ULL, 0xB9D5F019878444A4ULL, 
            0x144141B9986391B2ULL, 0xAC5251AC4B4C5487ULL, 0xF6240CFFB1830B0EULL, 0xDBF96DEB664D4859ULL, 
            0x7E065ADA9FAC569CULL, 0x6AC6727C2758C7B3ULL, 0xD91600024D21D3FFULL, 0x3291DBF9481A6021ULL
        },
        {
            0x57B892735A1973C0ULL, 0x1D3FD79BC93CFB51ULL, 0x5CC9CC06FB87B81EULL, 0x76F09AF0D3085F78ULL, 
            0xD97EBF79B69A16A7ULL, 0x01E3A30DFC5B63E0ULL, 0x0BEDC8D2AFD1AC42ULL, 0x202CDF99B7A2C219ULL, 
            0x2A07F2EEEF0B1B30ULL, 0x0094DE32E103ABCDULL, 0x2DA7A75FC7E2102CULL, 0x72C54E8F470771ADULL, 
            0xBAE1D9D4064B46FBULL, 0x6B421F2F0E9F7904ULL, 0x9815AAF42E5B8A00ULL, 0x9D93D0877F7E033FULL, 
            0x42D374A85847D015ULL, 0x6216F3E6AADFE543ULL, 0xF369C037F47C4453ULL, 0xE0F342B11A07DF4BULL, 
            0xBC3821CF07625796ULL, 0xF8022F297803257DULL, 0xF49886A4E04BF115ULL, 0xD8FA8D7A8E03ED40ULL, 
            0x2EF4A428C0376629ULL, 0x7FB4924236DA6CEAULL, 0x778185926E7BDDA8ULL, 0x82E4DD853BA6B84FULL, 
            0x0F29860A37FF098AULL, 0xB2CD4BD014F4D0FCULL, 0xFBE378FF09F075D0ULL, 0xA7C8558866810D9BULL
        },
        {
            0xEADD1E87A7BF46F7ULL, 0x8C554B438B470E6FULL, 0xED909CAD6FA5BCEDULL, 0xE268DD8EEABFC1D3ULL, 
            0x0351B23A04A018AAULL, 0x1391E28B1FEF8F3DULL, 0x3351A5AA832E5FC4ULL, 0xB663B1DADD86B631ULL, 
            0xE50DFFE29676C362ULL, 0xECF162221538905BULL, 0xE2013E97903D391CULL, 0x7D621D9824F93BF9ULL, 
            0xB05EE67BE9997BE3ULL, 0xA888F557FEE48D34ULL, 0xDE9B1CD74E315194ULL, 0x7080F3ED80B6310DULL, 
            0x10A22DA0200F2115ULL, 0x6B09924BEA0E5FC2ULL, 0x314CE8C5F02C4001ULL, 0x809E5B8B74F4A193ULL, 
            0x634761941A65BE9AULL, 0xD1E18D3714A4599FULL, 0x88218200DFCC1C97ULL, 0x349826DA769155DBULL, 
            0xC67B95B31D2AC801ULL, 0xE35C8EE65F726092ULL, 0x2AFB34C44FDE6776ULL, 0xF9341B25479092B3ULL, 
            0xD0708BD372E70DB4ULL, 0xB8BD40633FAACB0AULL, 0xBB798C77CAA1C7EAULL, 0x047C99CB293D1298ULL
        },
        {
            0x9F82C13C12982151ULL, 0x7F976752CDA52B96ULL, 0x07A356F2BA57A9B2ULL, 0xC3F3298E0317680FULL, 
            0x335B25C8B1A0C056ULL, 0xC8FB548750D250E7ULL, 0x917FFB0B86F9E3CEULL, 0x8F88E4D98354BE8BULL, 
            0x909AB9165A5ECEFEULL, 0xDB3770507BF42C48ULL, 0xDAC681186E7CC732ULL, 0xB776C2BCD12A6A12ULL, 
            0xD1A42ACF0241A9B2ULL, 0x84E17ED9D4147CD1ULL, 0x4B9F06E279B7F54EULL, 0xD07370A779AC9582ULL, 
            0x07CE4FE4F5383F10ULL, 0x7806368F63AACF8CULL, 0xA9A5A6375CFE23F1ULL, 0x785070D87CB60E20ULL, 
            0x25C3A6074661B780ULL, 0x5C703BC70AC295BFULL, 0x1C1439C04B18235BULL, 0xDCD1E359C795CAE7ULL, 
            0xEC44924109D54434ULL, 0xD9C2AE43A377F819ULL, 0x187A05FD5A6C40A7ULL, 0x6C6330D4ACDC19BBULL, 
            0x18E2CE565B18B008ULL, 0x25740FED8DD79A0AULL, 0x3DC3BB7CB288B9B3ULL, 0x0644AEEE6C426ADDULL
        },
        {
            0x89D8BF82A3FB9F34ULL, 0x41477A2422D9EA3CULL, 0xD00FA54D06A436F8ULL, 0x1C5FD6398DB8252FULL, 
            0x98B41CDBFAAF3BA4ULL, 0xD6DFE6CB2601AB46ULL, 0x0812285E1358AEA7ULL, 0x224B507F03656A1AULL, 
            0x5C7AD61E316CD840ULL, 0x8B66CA14988FE50EULL, 0xE619D0E9293F6BA3ULL, 0xE8294E6368B242B3ULL, 
            0x53C69DA47DBF9B60ULL, 0x673F0BA47414560CULL, 0xEE7814A37271B0DEULL, 0x1AA528A5A4D2744FULL, 
            0xFEEF07915516349AULL, 0xE23A6BFFAD0309FCULL, 0xCA8DB38F1FA8BD3FULL, 0xF6B84F02EF4FAA03ULL, 
            0x790E5E6C778B0F35ULL, 0x141022AE02637820ULL, 0xC1B50E1EE04CF5EBULL, 0xD5CAA3512D8A8B1FULL, 
            0x8E6A5B66E4D30366ULL, 0x524F4C84C4EBB72EULL, 0xBD7EAA04FF1FC983ULL, 0x298B5E75CF713A1EULL, 
            0x80B2C963614CD9F9ULL, 0xB6BE3E536EDE3E9BULL, 0x51001FD97324C6F5ULL, 0xD584FC41F24514FFULL
        }
    },
    {
        {
            0xBA85C37270A5D1DDULL, 0xD788F158DC557955ULL, 0xFFEFBABFF974B7A0ULL, 0xA1F422416BFF3B86ULL, 
            0xEDC8E12FD17EEE17ULL, 0xF224A35AC82FDE20ULL, 0xE69FB2EF772E0E63ULL, 0x05E7B01A2D076F20ULL, 
            0x3EC33E92C91A43C5ULL, 0xD8E39141B84C7BEDULL, 0x680E2BD0EB3F5047ULL, 0x35B486CB68F6FDBEULL, 
            0x7B18D01C3BBBBEDBULL, 0xEFB7050D0A4905FBULL, 0x6F5E8862C5860750ULL, 0xE6A24D1966DEE136ULL, 
            0x35E5F3EA0F801B43ULL, 0xE8C6AF9A8C226A16ULL, 0x3793C6007888BBE3ULL, 0xA85D3FD25F9E0126ULL, 
            0xB8EA624BE66E2BD5ULL, 0x954E43E25C439D17ULL, 0x2C170DAF0B27E7F7ULL, 0xE93C811E4436F7B4ULL, 
            0x4DB54F48613AFA6CULL, 0x9B3B21873B61DF5FULL, 0x674D5B42D484662BULL, 0x8E95C35A584D5660ULL, 
            0xC10B2842846A1B65ULL, 0xBE894C352FBBDD9FULL, 0x32CFAF762B853C1BULL, 0xF90BFCFF7A5A173AULL
        },
        {
            0x1385889D3DBDC383ULL, 0xB36EAF69FEFA6326ULL, 0x26CAA40368A0C015ULL, 0xD49E00A5B4ABD45BULL, 
            0xBA31EFB51686FC60ULL, 0xAA23CDE3800AD9D3ULL, 0x078BEFFB85FCED05ULL, 0x6C3A9831B0F549BBULL, 
            0x4C27F250E7F2ECB2ULL, 0xA84DF82A3732D51CULL, 0x5EC1308481C024DEULL, 0x8C3C1B8B38B1AFE1ULL, 
            0x7528B8BCC2027358ULL, 0xA1487D76AD4EBC26ULL, 0x6D39EA9C89B23D91ULL, 0xA4A14C090044BF35ULL, 
            0x18CEDBB4DAA91F39ULL, 0x53E7AA5A127BD50FULL, 0x7541C615344D88A2ULL, 0x9E0CC8678947A364ULL, 
            0xDC6FAF91EC915AD2ULL, 0xCB0BD0B509FFCCDFULL, 0x36B098E2EFED89C7ULL, 0x4B762048A9225950ULL, 
            0x7E4987BA40D95D92ULL, 0x55C2A6A0EEB36C57ULL, 0xF58CF677A110BDA5ULL, 0xAECBC6899B0038A3ULL, 
            0x4ACD9B172F7CA45BULL, 0xFF116796A06934F4ULL, 0xF94A5C01036BDFD1ULL, 0x3C0766FA2E45F9E8ULL
        },
        {
            0xD39192FE95FA3A05ULL, 0xEB5A9CE27452253CULL, 0x47FDFC171BA4976EULL, 0x59200329F0DF3F12ULL, 
            0x6313928F5544EA7DULL, 0x4F490044ED21622FULL, 0xF4DD8D4011C2C871ULL, 0xF304AA1E6140E19BULL, 
            0x3EBF7AD035FF7A90ULL, 0x40A286496C940025ULL, 0x7C3882B786D6CD9FULL, 0x01A40072F0B4FC89ULL, 
            0xE99CDFAFE7C2A105ULL, 0x2625381B5B0C5673ULL, 0xCFC6BF119C386A41ULL, 0x07FDA54BF2DFE1EEULL, 
            0x85EC3A0F7CE6F8DEULL, 0xD128DFE34BC9C8C2ULL, 0x7690D214FDD74C38ULL, 0xE1E3C1779262CC4DULL, 
            0x9949FE4EF8CB8396ULL, 0x5058A48E00A02EE3ULL, 0xA5FDEB0854F63E57ULL, 0x86664D164611A043ULL, 
            0x4FD284DE9E4FFF90ULL, 0x50DD429B10FDA488ULL, 0x5B0AE8385703A791ULL, 0x7617147D851CFE6EULL, 
            0xB56CE455ACAD02F3ULL, 0xD328DBB7A0FF0DAFULL, 0x9B93444A26F2BB4AULL, 0xF14896829EA32A7CULL
        },
        {
            0x35DED465C0D69B49ULL, 0x4566FC12AB5E76F7ULL, 0x06A4822B5F1A573FULL, 0x3359CC9C49276DB1ULL, 
            0x680B834E1C277977ULL, 0x46FF517C41DA832AULL, 0x8AD15EB2B788B006ULL, 0xB33975EFC59298B2ULL, 
            0xB54A5053230813F2ULL, 0xE89D997883512E19ULL, 0x0D42972EE7682809ULL, 0x003C48A8A42336C8ULL, 
            0x9108F47982C715D5ULL, 0x0F0A4BBEFCDE1D9BULL, 0x11AE3E29793EA568ULL, 0x5ECD65FB2CF7017CULL, 
            0x8DB81F5682727F1EULL, 0x86ED4CDF7AC25A26ULL, 0x11BD519DC4B5279CULL, 0x2A868A3496A5904CULL, 
            0x05F46E35B8E1A7F0ULL, 0x003FFCB81E685DF4ULL, 0x871A99B45E37CBBEULL, 0xBF9C03937E8C86EBULL, 
            0xDFC2B25E254882FDULL, 0xA0881B13FDE706CAULL, 0xA07268CF42FB2F1EULL, 0xF52C540CDA8043C5ULL, 
            0xE3E4D2E8B24977C7ULL, 0x9A3469DBAB974809ULL, 0x64A926795BBD9C32ULL, 0x147EC8EBA18D21C5ULL
        },
        {
            0x2CD3B22DD7C1BCB9ULL, 0xE3C7B99A101AFD61ULL, 0xEA02DD634F604964ULL, 0x03CF442FD5C6811CULL, 
            0x066C0CA334860E2DULL, 0x4980E780E02EBF00ULL, 0x95B7BB44B9475721ULL, 0xFFE88342FD39C3A3ULL, 
            0xC8592058AA1BAB4FULL, 0xD83D28EA24FC7CDAULL, 0xE6BFE55915AF760FULL, 0x859CD2AF16896467ULL, 
            0xA3AE13CCD5B60F94ULL, 0x13EC86CC9FBDA756ULL, 0x421F671782F68C8FULL, 0x4405C7D6C6992D9EULL, 
            0x0300DE532A000159ULL, 0xB6B1FC389E77F12AULL, 0x65F14026A41A56BAULL, 0xCC22D4F2586CB9A7ULL, 
            0xCDEAE96EC1E04066ULL, 0xBE66809FEDCF9F14ULL, 0x116B369A5021B90AULL, 0x4ED72D869FFCDA81ULL, 
            0xCCB86ADD47C8335BULL, 0x0C7FC3750EE5DBCBULL, 0x36B614FA86E75489ULL, 0x9C5790310A4E2F23ULL, 
            0x1BB1932A273F2E7AULL, 0xF5059B0A2CA4BD53ULL, 0x90DC2D6D2C68CD80ULL, 0xA6352F8663A10955ULL
        },
        {
            0xE6DB137DE95A4012ULL, 0xC90CD00FA11D90DAULL, 0x1E63C40478CC0BF9ULL, 0x400003CC5A1214F4ULL, 
            0x12F48047644A21F4ULL, 0x63262B22A15A9D5AULL, 0xC8EB0391C5DCC9A7ULL, 0x07970937763221CCULL, 
            0xB8F59D40D9591DA1ULL, 0xF7B7B4C9179BFF02ULL, 0x37AA6F2A193F6646ULL, 0xB90C95229D003727ULL, 
            0xC0914C53083FE99AULL, 0xFAFE719D8ABE48C9ULL, 0x75E365B1AA68080AULL, 0x07EDD170B3CBA0A1ULL, 
            0x05D7ED051E39195CULL, 0x03A42F84E061B09CULL, 0x2B736D269566A9DCULL, 0xCE9EAD9E073EF2C7ULL, 
            0x663DA4EC6027FCFBULL, 0xA73212E6AA2AA446ULL, 0x74224D0CDEB2E036ULL, 0xAE6669CD11B01C3DULL, 
            0x1FEBE2BE5CAC03B9ULL, 0x40765FCB53C8E190ULL, 0xD9B92080C95FF903ULL, 0xB5E5A340785EDF0BULL, 
            0x07AEA4B0061E7C20ULL, 0x1A39ACB1679A16E3ULL, 0xD66935A5CF7A4537ULL, 0x4BB8B240F0BC14B8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseEConstants = {
    0xB0942CA8FAEC6E7CULL,
    0xF6ED9DB007E9F1D0ULL,
    0xFE29C189EEA08AB3ULL,
    0xB0942CA8FAEC6E7CULL,
    0xF6ED9DB007E9F1D0ULL,
    0xFE29C189EEA08AB3ULL,
    0x0F9998F07A224F1BULL,
    0x8A6A9A4738FF50A9ULL,
    0x4C,
    0xD0,
    0x6F,
    0x8D,
    0xF5,
    0x74,
    0x69,
    0x44
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseFSalts = {
    {
        {
            0xA65836434C7D4242ULL, 0xBAF3385EAA3B224BULL, 0xCE29709D98238D95ULL, 0xC8189126BA69E3CFULL, 
            0xB56050CC091DBA4FULL, 0xDC98BF297149502BULL, 0x5D8BCB2C62F1C9A9ULL, 0x8B6BA52CEBAE6615ULL, 
            0x46AF0999282C292CULL, 0x892272DABA545CC0ULL, 0xBA4C6C928998C448ULL, 0xEC5A154D02516E36ULL, 
            0x5B3F3E63AD0014C1ULL, 0x013011BC356CEADEULL, 0xC337F3693DCEE3BAULL, 0xE28A50B77E9D1FC6ULL, 
            0x4CB222306A988285ULL, 0x886A23B7956CFA49ULL, 0x7D39FF1297BAA640ULL, 0x27FBAF4AC4EBE414ULL, 
            0xABBAA1C7FD5F058AULL, 0x5FB5179232360825ULL, 0xBA72B7EE84E32B9FULL, 0xCA23A1A668149D67ULL, 
            0x79413FFA7152DDBEULL, 0x2B9034B5428031CEULL, 0x295604C36498128DULL, 0x13C439D9870BE278ULL, 
            0xC1B4D376848709D2ULL, 0x3C56921B301B35F1ULL, 0x8D3692379F07BBFBULL, 0x10D918D066EBCF84ULL
        },
        {
            0x1B35B00654329323ULL, 0xFA1542A9FEC0C3D5ULL, 0x6BB18AB67E2D74CCULL, 0xA23A32E20F9D62AFULL, 
            0x72CB5CADC4CF87A3ULL, 0x4C9716315B067C59ULL, 0x3A3D2B1DCE1CE68DULL, 0x6C326743C4D64B3AULL, 
            0x5224EBC74098EC9AULL, 0xC124F62E379DCA59ULL, 0x2736D77A778C5E26ULL, 0xADD245A7E6E51EBCULL, 
            0x866982C718A94609ULL, 0x24EE91546FCBC862ULL, 0x551D3B5589E52923ULL, 0x3FCD7BDF536241A7ULL, 
            0x6E0B2E1C4BEAEC2DULL, 0x2C7BF676F54F4D81ULL, 0x4415A2C409D2EF1FULL, 0x294130905FE53435ULL, 
            0x49669B53A2D68517ULL, 0x1530907039384483ULL, 0x1B06D3083850A976ULL, 0x0C69E59931B0B6FEULL, 
            0x8BFFBBD37AA2B734ULL, 0x23DA060C78B6D37BULL, 0x620AC1847675CCABULL, 0xEEE1582B399C3A1BULL, 
            0xE90854DB898DF071ULL, 0xDDAF1B2CDC86BEC9ULL, 0xC3D947D6150E29A8ULL, 0x5EB5A2F44B08D562ULL
        },
        {
            0x13C0BCDFC40D87E9ULL, 0x1EAD3D2497E840BDULL, 0x1A661E7D423062C8ULL, 0x9538CF5C0663CE05ULL, 
            0xDE65A4F210A4E368ULL, 0x965BDB360DB23216ULL, 0x50F25B99751CFE1AULL, 0x1534E3D7B7685676ULL, 
            0x62F4AA365BF1CF16ULL, 0xE88DDFF07C249C35ULL, 0x0AE0B12BB555E0C7ULL, 0x4FD2EE1406CDA08DULL, 
            0x8CC008454B3671EAULL, 0x465FAA8AFDF8D386ULL, 0xDFD68EC1C87ABBC9ULL, 0xD24A208276AF4858ULL, 
            0xB930617DF38F78D4ULL, 0x2C5B8130236EA656ULL, 0x528C17D0A4BADECFULL, 0x6D72645BFB97F4E9ULL, 
            0x36EC557131FB7D7EULL, 0x796D39866CCB10C8ULL, 0x9F9C9803BCBCD7C5ULL, 0xD5C425B40F6F911EULL, 
            0xC4752C01F9A524EAULL, 0xAE3538EEB32D4EABULL, 0x2724872F6D4ACCB3ULL, 0x1598B0B4D5EDFFEFULL, 
            0x3DC0559B6C5A5390ULL, 0x26148AD701FC48F7ULL, 0x0C2DC64F6C8261F4ULL, 0xC43D4E6FDBD4EEB6ULL
        },
        {
            0x10F76BE6712AFA26ULL, 0x97D43CB4A5237035ULL, 0x00E04F5715991096ULL, 0x4B51E21408AA7B73ULL, 
            0xE143E24301AF6E8EULL, 0xF081DEDA53B95091ULL, 0x628268F0001D5F7DULL, 0x12FECF0DC45CA0E8ULL, 
            0x70A02D659F1B888AULL, 0x12BFF541AE3DD6A2ULL, 0x0FF88D89BC0CC4D1ULL, 0x0ACFB348C5964EE5ULL, 
            0x3563D2F38DAA00D0ULL, 0xA6DE88E6CBE5525FULL, 0xC699829DF5001C93ULL, 0x5AD940AF2F5AE8D3ULL, 
            0xC34A0B7BA308314DULL, 0xB2CC7B5CE04E618BULL, 0xDAADAACCA4512266ULL, 0x2ADD203D0E810FE7ULL, 
            0x528E42C112076217ULL, 0xD012C835071AA880ULL, 0x657697A957A36563ULL, 0x906FD123075AB6DAULL, 
            0x7E8950465D43DE50ULL, 0xBB8DD599E17B86FEULL, 0x01C0419598C21D1FULL, 0x9974762BF79F93C3ULL, 
            0x2EA604DFF69F37D8ULL, 0xCF484DE004ACC99CULL, 0x73A611E2EB2585ACULL, 0x84731168A8CD2020ULL
        },
        {
            0xCDD9560FCE294303ULL, 0x9F1CF08AA2610EF7ULL, 0x510AABCF3EF9713BULL, 0x1BCBE302981BABECULL, 
            0x28BD41F5A8DE6048ULL, 0x1AB275B895085E04ULL, 0x69925FDD5A53616BULL, 0x6AD9577E5A397056ULL, 
            0x0D5C47EC96CB622BULL, 0x768380BA5A43F6B2ULL, 0xA37E78188E22A59DULL, 0x42C989C87EBBE416ULL, 
            0x469F5812D003998BULL, 0xF8ACBC53CD519925ULL, 0xB0421DE3A7978AE4ULL, 0x074C3BCA7B0619EAULL, 
            0x8660CC003D2775F0ULL, 0xB89BD24E56CCE0F4ULL, 0x7C47CE329D8624FBULL, 0x25D566D31B137E25ULL, 
            0x46D60AFC4E54A66DULL, 0xDD96E983CD81A588ULL, 0xC05C65DC884CB960ULL, 0x7CB8FC728085168FULL, 
            0x6697C74B82731B34ULL, 0xB4A1C7EBCD8B6BCBULL, 0xD403DDA884CAE5FBULL, 0xAD41095C92C15A0BULL, 
            0x283C80ACEFC216B5ULL, 0xEE71C290F6841A5AULL, 0x84D323A356569CAEULL, 0xDF3959F485B3F803ULL
        },
        {
            0xC0D64C03572F1D4CULL, 0xF7B1A177E8763DF3ULL, 0x7707ECE7BA0B2792ULL, 0xF4751CC24CF360BDULL, 
            0x738047259A3249AAULL, 0xCAFFBA90F271146CULL, 0xF3A71BAAC1FD23A5ULL, 0x66A6010F28F587C6ULL, 
            0x3CCB004A6ABB89FAULL, 0x3EA5C53BBEB407AAULL, 0x202DF3A15353D305ULL, 0x8BCA9DEA32F5CA6FULL, 
            0x26BA1ADBA8A3BFC4ULL, 0x0131420AE4471C26ULL, 0x8691791C6F53FF98ULL, 0xF33ABC27680534D1ULL, 
            0x4A4EA811E7FC5BE3ULL, 0x6DE882823F209B5BULL, 0x3D2C119C9551057EULL, 0x7D5350E851C69383ULL, 
            0x7FCB59EACC986A18ULL, 0xB6EA86BC763D6196ULL, 0x63FF39A8F971284DULL, 0x3B97EBFCCB89F6B8ULL, 
            0xC2000A2545A712CCULL, 0x5A734A7D9EE71604ULL, 0x94043B53F4FB1D7CULL, 0x84CCE59CC059D74EULL, 
            0x20B16C071027659AULL, 0xC45C896532E63661ULL, 0x28408BB1DF6EE5DFULL, 0x458CFC2CF006730FULL
        }
    },
    {
        {
            0x2FA35A69835F4341ULL, 0xC08C34C9A9833F22ULL, 0x83BA080CC977C6A7ULL, 0xF3C744D3F113D83AULL, 
            0xB9521A62213A3FF4ULL, 0x22119292D6CB76EFULL, 0x35B9A2518A90373DULL, 0x442DEAA7A5338281ULL, 
            0x0DFE8642F7D5B41CULL, 0x8BDB18F1DC69F3BBULL, 0x95DC8E6AEE79FD93ULL, 0x8D43B6930D8A0CD4ULL, 
            0x3D2DDCB2DD9865D3ULL, 0xBF76400917A9BDD7ULL, 0x9D03FC04CB6E0471ULL, 0x018DC0C7869C398CULL, 
            0x97153115B2B50FABULL, 0xD6CD0C028E75CE0AULL, 0x9C966C67AA212A70ULL, 0xBBA3A3F1B5BDD4BEULL, 
            0xE704D4B2B5AAEAA8ULL, 0x456F6B2BBC018D93ULL, 0x2D24AC31D115C230ULL, 0x29BCFCB76040D5A6ULL, 
            0xA7CA104DF85C6A08ULL, 0x37D85CEA8502CD44ULL, 0xFC1F23643CAD7D2FULL, 0x6BB9BA8D148E729DULL, 
            0x4211DF4521FB34EBULL, 0x5132099D47C687E5ULL, 0x8AFF4C3F8E337C57ULL, 0x1F2B6C3F1D274D5FULL
        },
        {
            0xC82885E4F7C3EF15ULL, 0x72B513C47D017123ULL, 0x2CBF50BC4790BF84ULL, 0x775572FE81C72CA8ULL, 
            0xCD22EB2EB6150891ULL, 0x458990132BA2CD77ULL, 0xEE713D8C4A61F9A0ULL, 0x8C30FDE5F836B9BDULL, 
            0xDB68CF31CBB26EF7ULL, 0x7C859DCBDBFF5DF9ULL, 0xDB2AF25A84EBF045ULL, 0xA209169A08021430ULL, 
            0x34C992E39D2ED1BAULL, 0xF252BA4EA6BCAAE4ULL, 0x831EBD8216562E4DULL, 0xEFE1A966A4BF6667ULL, 
            0xA63E53058184D1C6ULL, 0xE5272AF79ECEF86EULL, 0xA480E7499C94BFC3ULL, 0x3EBC1439AD9B2CFDULL, 
            0xBD4C1A2203B204E7ULL, 0x97ADAE22FC210C2DULL, 0x7A915D1D5DA382BDULL, 0xCB46FB1E1F3DDC4CULL, 
            0x99D6E3D2D4D241B7ULL, 0xB53BB04E43996BA8ULL, 0x3D1EE1657DDEDA92ULL, 0x8FCEC69111320DA9ULL, 
            0x5970E4911287F68EULL, 0xF32B5302AB6F7B5DULL, 0x1D6699D67C433A56ULL, 0x6E9096666B0B896CULL
        },
        {
            0x4A6D2C5011BF1115ULL, 0xC15C0959C180BF6EULL, 0x2559CD50B2065CBEULL, 0x954DF2BC8F850EE7ULL, 
            0xA30FDE5461A1A33FULL, 0x3D6DFE0904A6D765ULL, 0x09C02FB1533E7965ULL, 0x14248EB8F740E746ULL, 
            0x0004DC80562C86B6ULL, 0xEA78D669F475AD97ULL, 0x7D062606DBA401CEULL, 0x7C3CE09A5E6777BEULL, 
            0xD65545E0C22343C5ULL, 0xD9A919918311B258ULL, 0x6843926A46543412ULL, 0x81F7C3FC96C1E9A9ULL, 
            0x1D3FF25FBCD92C87ULL, 0x07A3A60E152CF391ULL, 0x69755617448F5B45ULL, 0x0CD3A45B5D3996C5ULL, 
            0xEDE3DC07F65E4648ULL, 0x4940CC78FB5FE4C6ULL, 0xEE474BCD3AFD023BULL, 0x51C29E03A49DBB05ULL, 
            0xE8BAD4C8285BD0F2ULL, 0x02B833F36EF128D2ULL, 0xBF7E886442BC624AULL, 0x6F1C266F02BBB0CCULL, 
            0xB74DFE995E794E8CULL, 0x640B300DB36B10DDULL, 0x06A45919E8E8CE38ULL, 0x87F2FFB9D0201C67ULL
        },
        {
            0x6E5C2920ED5B2554ULL, 0xAB694461B5AA6093ULL, 0x099AB6F55D5F5D41ULL, 0xAD17FFF90CC76C28ULL, 
            0x225CA44376E4E4C0ULL, 0xAE34A050683671DEULL, 0xF820A12F8551DD56ULL, 0xF339AA160E1FAC2CULL, 
            0x5EFDD682FFC41430ULL, 0x192073A36C3CCFEDULL, 0xCAFA158E7552135AULL, 0x560603D27BB5BBE3ULL, 
            0xF35A48191BE3AD3AULL, 0x809609CE4E9C3173ULL, 0xC249EA7EB4916B30ULL, 0x000BF5C21A4797E6ULL, 
            0x1E7320B91D3D659CULL, 0xD5CE4CF96A4F8964ULL, 0x61D344BAD239633FULL, 0x68231EB8B42E342FULL, 
            0xB6AE0292C584BD3FULL, 0xD0655B2785460218ULL, 0x1FC0CFB763653A78ULL, 0xAF8177B2A2DF5EB8ULL, 
            0x00127CB3AD7BBF60ULL, 0x45999AF5E81A45E9ULL, 0xE263E2B70C9A4DC6ULL, 0x7A7BA25D78959B7CULL, 
            0x5867B0E24DF7FCDEULL, 0xF1F8C176C529A664ULL, 0x4DCB9B26694E2395ULL, 0x3069523227C71961ULL
        },
        {
            0x55C31A5271FFA478ULL, 0x5CAB3151FA4AC090ULL, 0x3B4A3EE9F4447775ULL, 0xB77111764DC21126ULL, 
            0x6A930A8C67D92828ULL, 0xEC596B9808CF0740ULL, 0xFE4512ECED0C88E8ULL, 0x5B7C47DCEB4E682EULL, 
            0x75D260912CCC90ACULL, 0x2F27D39F66334808ULL, 0x6856DF3AC9838913ULL, 0x93BF20D80A7686BDULL, 
            0x2DB593A1D05730CFULL, 0x1E2FF362EE73DA08ULL, 0x8D7800EFC1374E5FULL, 0xB3FAECB930BD97D4ULL, 
            0xD8CBD81A4C3245F1ULL, 0x3FBD6127F990D05EULL, 0x6C2B5BDBDF7F3EF0ULL, 0x4C0733FA275CD295ULL, 
            0x08572863719DCBB2ULL, 0x684197DBB65C449DULL, 0xA1135F536F24AF4FULL, 0x60EF8541FA3D79EAULL, 
            0x58BD6738EA35DF06ULL, 0x4DD88BFB573145D6ULL, 0xF06EAA063EE1EEF8ULL, 0xD9D8D3B191ADF2BDULL, 
            0xC1F53C10A1C6A017ULL, 0x485DA334E59A3042ULL, 0x4679D44A0B1914C9ULL, 0x98D365652DBD10B5ULL
        },
        {
            0x5EE1C01C8440FCF6ULL, 0x2FE86B4F2C21BD82ULL, 0x73B54B7E543BA189ULL, 0x813EB16898712E93ULL, 
            0x956DFDCDADE2B3D9ULL, 0x8EC12AD08DC4F841ULL, 0x605D3AB3FCB58DAFULL, 0x063CCC47D0FB6868ULL, 
            0x3B0EDB8B68495E16ULL, 0x032365F1054F6614ULL, 0xF6875CC7E6854F3FULL, 0x024175ACAFD6504AULL, 
            0xE4828CFFCC36BD2EULL, 0x80EC64331DD84ED8ULL, 0xBD22596124B25C2AULL, 0xBE1BC58997CD6EB5ULL, 
            0x055D7D3562075FFFULL, 0xAE877C033D053A9CULL, 0x8797C1F3A497BE8BULL, 0x023170B76BDC1C73ULL, 
            0xA9283286FA57F574ULL, 0x000AB03901BF6FE3ULL, 0xE6DBB138324EB98DULL, 0x36384CED49622BC4ULL, 
            0x04DF1DF2EC38D203ULL, 0xADCE893328DF7558ULL, 0x19F54CDAAE94F49CULL, 0x93C7A2967DC66AC5ULL, 
            0xC87C19E99D962BD6ULL, 0x787B9856B2309FC6ULL, 0x58C9B0B107D41CC7ULL, 0x4A741311B77F782BULL
        }
    },
    {
        {
            0xC141137345CFE625ULL, 0x19B2AF1CDB98BDEFULL, 0x808AC86DDE2E77F6ULL, 0x9D392EE528C5A705ULL, 
            0xB9828B143460D5CCULL, 0x71F5796C3ABF81F4ULL, 0xF64C87106CE713C8ULL, 0xCEA54306FB690622ULL, 
            0x19A7C9CFE9B6A9B2ULL, 0x1864CC8A433E9327ULL, 0x4B35C4B58410E6FFULL, 0x25D46EA18045CFD0ULL, 
            0xDCDAE605C2109DC8ULL, 0x46290393AAAF7CB6ULL, 0xBED5BC5890E43CB3ULL, 0xB72C9FE0626DA83AULL, 
            0x5EEE14255386935CULL, 0x9A207B4DD26449DFULL, 0x313A1F9480762556ULL, 0xF6C28410ACBF9937ULL, 
            0x477F05D1750E7260ULL, 0xBFFE4C4929A2DBC3ULL, 0xB38068D3B1E8AAD9ULL, 0xF50F3EE715A420FFULL, 
            0x37B398A21B8C783AULL, 0xCBBA8CEB73AC5187ULL, 0xC4A25B27C70F18A1ULL, 0x2AF0616EB254DF8FULL, 
            0x1002A584D8422098ULL, 0xE408D4C8BB9D8A87ULL, 0xD1CCF47F35D13456ULL, 0xED7DBBC041D97260ULL
        },
        {
            0xF77EFEAF15BA9BEBULL, 0x9EC0937CA82A8F25ULL, 0xBEE77E67EBEED3B8ULL, 0x373A00E4E0DF1D73ULL, 
            0xA88267336554FCEEULL, 0x374B32BF9430C4EFULL, 0xF9B2EE90AB5ED84BULL, 0x47717C3E2CB11522ULL, 
            0x67CBD24A279C7573ULL, 0x649357C4B9B0D3D5ULL, 0x73D9CB6A1D76D303ULL, 0x728EF12D331C8C0AULL, 
            0x9CF48F8A51111E4CULL, 0x09802AE895A1B71DULL, 0x6F59F03693A8BC18ULL, 0x4A7729548EFD5CABULL, 
            0x2A39E62ABFDBFA9EULL, 0x71767D49B40B69DEULL, 0x0EC783E378803B4DULL, 0xB255D0A293B31535ULL, 
            0x8FC1C1562BD474BEULL, 0xAE58AB2468E04F02ULL, 0x0A4DCD8B9D15E26CULL, 0x1D82BEAD121AF28FULL, 
            0xE63A5FC8B7FF2E42ULL, 0xBFC9A2803662F476ULL, 0x19E5DF4BDF31689FULL, 0x6DC7D19EAFCF322AULL, 
            0x1BE0CF93BFD440EFULL, 0x3B3889C086C11E18ULL, 0x30E8240475C3D0B8ULL, 0x458B92D970AAADEEULL
        },
        {
            0xF9449823067A88D3ULL, 0x7AF6E184D3F7E966ULL, 0x9BE6DB24EE315655ULL, 0x4132F80FF3BE03FAULL, 
            0x88D0C8447D4537D7ULL, 0x5570B6712BCD9E04ULL, 0x004ED488A533C8C2ULL, 0xE69C417D660FD3D1ULL, 
            0x780F604CAEF0DB10ULL, 0x8A64AD62C7AC2AA8ULL, 0xA0EC865035D92FE6ULL, 0xC9A4B653AA163043ULL, 
            0x9C1221E29C0E8839ULL, 0x2E2054728323F64AULL, 0x7782274ABF51A3CEULL, 0x44C6BE1E2E908ACFULL, 
            0x6AF68EE633B65A53ULL, 0xF6AE8E1D1D329A5EULL, 0xE5C36D0EBEBC49B0ULL, 0xF5BE7E5479E3BA81ULL, 
            0xC0CC10F7271A5626ULL, 0x576CA8099F9E4327ULL, 0x413094206C38AC82ULL, 0xABE86A92D7DA990AULL, 
            0x6955BDAA600C6531ULL, 0xAACCC4DB5E193153ULL, 0x08CC1998AE43D79EULL, 0xAB3E8FB5151F2CADULL, 
            0x2BB72C5128B55D4EULL, 0x1F6433F180A35914ULL, 0xCDDCBAFA66B008A6ULL, 0x18B7208DC680C6EDULL
        },
        {
            0x82ECF1304D0CEFA0ULL, 0x55B46DA39CC87247ULL, 0xD18F0805E1F3B852ULL, 0xACBAA4BDBB27D803ULL, 
            0xE16E60E3E9C9080FULL, 0xBB7BF6FF2AF65101ULL, 0x590A7B58F4FC5991ULL, 0xDABC183FEAD8D0AFULL, 
            0x3B233DEA2E1E2893ULL, 0xDB3F8BE4453F67AAULL, 0xACF329DAD7E61065ULL, 0x0F4BD9A0D8AA0E75ULL, 
            0xFA8696E2EC6B4338ULL, 0x7C837EED5467DD1DULL, 0x755D17B6C315B4DAULL, 0xC1B068D6C6E0D739ULL, 
            0x6562C3224E7D3702ULL, 0xF9A93290ECD6CA44ULL, 0x1C6486BF2F0A88F5ULL, 0x048C9C90AF4CBD68ULL, 
            0x6C183B5BE819F5EAULL, 0xAF03BD0A2ED024EDULL, 0xA695C29F9CDC634DULL, 0x056C372ABDD2E1BEULL, 
            0xEE168E897739B4A7ULL, 0x3A9795577BE480CBULL, 0x765170BF982B72B6ULL, 0x1F509A94E60FE469ULL, 
            0xE5316059643C3E9DULL, 0xEE4E47A073BB556FULL, 0x0093E8B931A521B9ULL, 0x45A25B223ABFD07EULL
        },
        {
            0x29858518E6A42685ULL, 0x0AB432FD00372357ULL, 0x5331ACA5A39435A8ULL, 0xB7E23CB0460CCEF6ULL, 
            0xF7C92ACED2532384ULL, 0xFEDEED2B5BF92C5CULL, 0x2D3ACBA6DF90A806ULL, 0x051290DA95CC652CULL, 
            0x3A3C8712C56F076EULL, 0xA64EDE172F6B5A23ULL, 0xD75A52D325DC96FBULL, 0x49C94BC950DB5BF7ULL, 
            0xE80BBFCBBA5F2034ULL, 0x4112E60DE2EBDF33ULL, 0x8D8571F007C565C7ULL, 0x2F051E201DEA06FBULL, 
            0x19741AE64584B700ULL, 0x6897AAE667814284ULL, 0x256B16E31E3C1AA2ULL, 0x0E68EDB537DECD4FULL, 
            0xC1457476FBF31D73ULL, 0xAF861D7389E741F0ULL, 0x413E127A0D98D237ULL, 0xA566C72A792E3F8FULL, 
            0xFDC652442D4100B6ULL, 0x046EE1056827B22EULL, 0x8D5FD0A57651F0EAULL, 0x5A0DAC7FF7DC1FFFULL, 
            0xDA5F20D902A92435ULL, 0xE16A2FFB4478D79BULL, 0x0138642C52FFB1CFULL, 0x56B2672AC2873B70ULL
        },
        {
            0x6E5E40D207E03824ULL, 0x6E5DDE1B74888E93ULL, 0x71B2E6CAE7F6E35CULL, 0x9E09CA748F6AA865ULL, 
            0x4FA60005E5179BB6ULL, 0x22F5A7969C373684ULL, 0xA23B6A31C59188F4ULL, 0x5719E6823D261753ULL, 
            0xB0B2F1FEC34CDF2FULL, 0x2E9DBA099E6B76A4ULL, 0x0C8C012DC2AD2D93ULL, 0xE35B27E58FDFDD4CULL, 
            0x3D8C6C8940998170ULL, 0x5ED0D890350B01DFULL, 0xE57CBC1563E9AC12ULL, 0x66232494288F7047ULL, 
            0xC32210BF3271A07BULL, 0x6DD10EC952205E15ULL, 0xD21E4CED87476E64ULL, 0x3B3400F4E35E5209ULL, 
            0x43EB49934432A712ULL, 0x45E1BF411528F921ULL, 0x1304B77D02D96F9BULL, 0x133F7B1094A975F6ULL, 
            0x0987931C0F2B6103ULL, 0xE7558A2F33EC2AD7ULL, 0xB4A363AD97095DB1ULL, 0x317F1E4C3440844DULL, 
            0xC38AB95618A98B44ULL, 0x5E2C6B3221A4A87EULL, 0x09E59A2CF1570D49ULL, 0xAD863901A50D8B13ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseFConstants = {
    0x9DCC29A4CCBAD5B5ULL,
    0x0125CAA6DF9819B4ULL,
    0x9EAA6EF53408C634ULL,
    0x9DCC29A4CCBAD5B5ULL,
    0x0125CAA6DF9819B4ULL,
    0x9EAA6EF53408C634ULL,
    0x1B1C78B751A906A4ULL,
    0xEA4C1272C536D7DDULL,
    0x61,
    0x62,
    0xBF,
    0x07,
    0xF2,
    0xFD,
    0x94,
    0x6F
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseGSalts = {
    {
        {
            0x63F4251EF136DFC5ULL, 0x279D4466D4F6F53CULL, 0x25F76A334D99F634ULL, 0x93C07A391DA9BC01ULL, 
            0x5C01F3A2AB6EA116ULL, 0xC3FCA7AD6D9CA968ULL, 0x0870C39EC4E3174AULL, 0xC22C634552FBFA9CULL, 
            0x8EB174BFCF337465ULL, 0x8FD2C8CF12B005F5ULL, 0x4050A132B6D355C4ULL, 0xF267BC6C60AF0ED9ULL, 
            0xE78F174FABFBDF2BULL, 0x48B613720C1DA943ULL, 0x3AB2EB9008CEEA1FULL, 0x4CF12015EDB6D2C2ULL, 
            0x9DDD317DCF458182ULL, 0xA597836984FF4A6FULL, 0xBE75D6E28F5FE1F6ULL, 0x2525E5D3602C6D54ULL, 
            0xB31CFB777A870660ULL, 0x62BFE8D26CB6F7CAULL, 0x8C6BA155AA4F3423ULL, 0x7A39AFA49E1253F8ULL, 
            0x6F46975E27FF105FULL, 0xDB4B37C6AE1C940FULL, 0x6560286C8F8AE92EULL, 0xC59B283F4D5199F0ULL, 
            0xE88391466E31A435ULL, 0x865E4671F169825EULL, 0x7749BE01D0957B0DULL, 0x835DD8104BD7853BULL
        },
        {
            0x277FD5D9A8565D4BULL, 0x28E48B2DF01D8E6BULL, 0xAC2085272527AFBBULL, 0x86D71778A05C3368ULL, 
            0x895A730E368D7EF5ULL, 0xCA39426D6B871290ULL, 0x104A56A47E3763F4ULL, 0x24F29FCE11CD1F89ULL, 
            0x453DA23215204E74ULL, 0xA064F2CE3256843EULL, 0x35313FA0D427FEB3ULL, 0xF35E7BBA88FF3BB5ULL, 
            0x2F45C94E11DAB6F1ULL, 0x8D4B9B2A04F8C137ULL, 0xA1873C5BDF5AA60EULL, 0x8412E33FC800C264ULL, 
            0xE5C4B03EE6589774ULL, 0xF484B5BC5228F6EFULL, 0xCCFDEAFFA974AB6AULL, 0x21BBC0A5E0D36158ULL, 
            0xDDC94DF387256724ULL, 0xC827CB12AE6F9E9BULL, 0xF861AC8C570FB79FULL, 0x85D32C8055B247E7ULL, 
            0xD13A13EF8E398947ULL, 0x99526F475C9D4C80ULL, 0x59ED55CBE04C8BE3ULL, 0xD55DDBC2C41190B0ULL, 
            0xD6BBD55984C7DBB7ULL, 0x544B1E553464EF1CULL, 0xE6BE2042CAFF77AAULL, 0x10300161A9ED0B27ULL
        },
        {
            0x0FAB121A32BCB36BULL, 0x499B568588F8F5E7ULL, 0xD3690B29334EC2DDULL, 0xC224647308A1F6C2ULL, 
            0xAD454B1EA1C515C7ULL, 0xBBDCDC8981BD1102ULL, 0x44FE09DC9E7E041FULL, 0x800CE2C8A64725ECULL, 
            0x72BCCA9DCE2B020EULL, 0xC674963B65439D20ULL, 0x09D8C98364A90568ULL, 0x5D4F9FC091664996ULL, 
            0x218C77DD153C59AEULL, 0x509DE09431ABD343ULL, 0x3617B664764ADF44ULL, 0x09516440E550B6C9ULL, 
            0x9A436CEE2C879D20ULL, 0x57205F59DF1FB678ULL, 0x4001136E6C955C1DULL, 0xF79DEE83105C9545ULL, 
            0x45ABCD22E26ADED3ULL, 0x85AE7896E3BF659EULL, 0x2BC95428C7BCC623ULL, 0x80257F758ED3A566ULL, 
            0x415CE1E88A9C65B6ULL, 0xE2914A1F993003B5ULL, 0x2C66A6DDA96259B4ULL, 0xFCCCB5596A56DDC6ULL, 
            0x43B1CA2E7F764FEDULL, 0x243607AA847CA39DULL, 0x4D1E58B8DB1B5F1FULL, 0x653121F8F936070FULL
        },
        {
            0x2444352EB06B1946ULL, 0x8858E003067463ACULL, 0xCC907AB948025C4AULL, 0xCA4FBCCED3DB2556ULL, 
            0xA513D2867A530B28ULL, 0xC31320DBF9329FD8ULL, 0xA25F0BF8A723F693ULL, 0x650FB9CA6443866BULL, 
            0xB5ED2EC81E5CEDF9ULL, 0x9EB50721A4168E79ULL, 0x8D41463429B76E5EULL, 0x9D511609ABF34D74ULL, 
            0x097AB467BDDD46BEULL, 0xA792752886362D2CULL, 0xCCB60C4ACBE3238FULL, 0x9F19F80CE530C831ULL, 
            0x66C99CD6FB4CCA21ULL, 0xF0A10E8D79084B1CULL, 0xB4972CC731BABAF3ULL, 0x75C92B638ED3D79DULL, 
            0x28EA00898775A6A8ULL, 0xD4E68D5450CE38E3ULL, 0xA2EE76053C7D4F39ULL, 0xAE4FD13A78825A34ULL, 
            0x814648212DA01B8EULL, 0x01E96655964A03C0ULL, 0x74B19B02E27B15E7ULL, 0x0C6D327ED9BC79CCULL, 
            0xA07E9C54352BA46EULL, 0xC2EAC47CA249E71BULL, 0xE270C1C2BAA0B4D3ULL, 0xBE81202F0B0DAC9BULL
        },
        {
            0xE8A8630E16C32F8AULL, 0x59877EC6439D1E79ULL, 0x739D24E181F92489ULL, 0x5090905CB4FE0A63ULL, 
            0x0F8FB3648DDC7DDEULL, 0x4DBA10E7A371AD81ULL, 0xF1F333A729E807D1ULL, 0xECE40A29ADC254F2ULL, 
            0xF06D5A79814B349EULL, 0x642397911C742DC0ULL, 0x8B58245C1755F1E2ULL, 0x8E141E29F98B1A5FULL, 
            0x6E6F8F9401B7E9ECULL, 0x7437D552876E61EDULL, 0xE5E32B511A12782FULL, 0x1552A63FD4A47F9EULL, 
            0x059574762F1FED85ULL, 0xA53DF0EF7E248C70ULL, 0x302A3F3E2361F536ULL, 0x9D79466BB047246DULL, 
            0x16A8D2EBE82607F0ULL, 0xB1B8989D403A37E9ULL, 0x51DDDDB9DC7BF629ULL, 0x076805F034BD1786ULL, 
            0x0B846E5F638BD99CULL, 0x985A22D17C4FD96EULL, 0xB42DBA2BE5F80C49ULL, 0x8C0E505DFD180C0CULL, 
            0x92051CE6E72C5842ULL, 0x735C268438ACF0F5ULL, 0x1B6699B11F69F1C0ULL, 0xB78C7D5150B46D2BULL
        },
        {
            0xBC8599B1022CDFECULL, 0x760BD09578475A20ULL, 0x3803993D67F0152DULL, 0x24A818DD3CF2227CULL, 
            0xFA9C1B6E5F161DC3ULL, 0xE17F2EE6FE543A11ULL, 0x1A6A9BAAD81FB528ULL, 0x2D9C60B73BD3E7BEULL, 
            0x3A0B345C2E201EF1ULL, 0xB49CC783858AC5CEULL, 0xEEE44D8485ABEC1BULL, 0xD0C4D3910F487162ULL, 
            0xE73A126D8DBCD05FULL, 0xD3B3031E30FC30F0ULL, 0x03C8438BD0EFE4C9ULL, 0x9902493602C538E8ULL, 
            0x9DA0ED7D518BE663ULL, 0x4B8B15507F2DC560ULL, 0xAD93F15987F19EB7ULL, 0x76504367B3D9DC56ULL, 
            0x0AB55229CC1E5FBAULL, 0xF6E616865E728872ULL, 0xC23927AB7DCC24CFULL, 0x096F8A92C4169808ULL, 
            0x01E7546FA1AE2309ULL, 0xA3E244DCA8D172EFULL, 0x1E2F5BE2933F0252ULL, 0x295476F3ACDD96F2ULL, 
            0x82F3F22A9E9EA363ULL, 0x797C2886FBBCF372ULL, 0xB28D5D765EB96105ULL, 0x809F96E46979B45AULL
        }
    },
    {
        {
            0x880183C62DF0ACB6ULL, 0x0A882C5B3AF644BEULL, 0xA05D8C088FD3589CULL, 0xFE64CE1560BF6DC3ULL, 
            0xBD52CC7E5A8F891EULL, 0xD5D63105BBFDE764ULL, 0x8E4BD7F9E34A0FEFULL, 0xF1F1F33BEFACE467ULL, 
            0xE84FE02FE1ED83A0ULL, 0x14DFDE0C7F899BBFULL, 0x8DA8210F06FA9288ULL, 0x32B470356944F220ULL, 
            0x7BD75B963186D76EULL, 0x72C40BF44CE88C3EULL, 0x87227776BED1D7EAULL, 0x30F1E3D5A9C3FE62ULL, 
            0xDFD246DCD4546AD6ULL, 0x3D93FF34DAE1481FULL, 0x4D5FE032127BE2DDULL, 0xD5A4A50EBF858B89ULL, 
            0xE73B6976A7F14216ULL, 0x86B5807B1552E89EULL, 0x335FB0639DFD03FBULL, 0x16FCC36D333150F1ULL, 
            0xC9634C8EE89DD95BULL, 0x4CB640E77E16ED37ULL, 0x3A740B85C939448CULL, 0x449845A07AFEF42CULL, 
            0xFCA50D2B38F9C825ULL, 0x0FFB1CEEE7B3458FULL, 0x7A93CC12B3A6B087ULL, 0x57CF5EEB4FAB23F0ULL
        },
        {
            0xB735D79F4BE8D619ULL, 0x8F91D5682634C248ULL, 0x253D0B6AB29D2B81ULL, 0x2E25DFCDB4DF1F5AULL, 
            0xE39E9F13C4F7F3C3ULL, 0x868A6BB90F868168ULL, 0xB932FD63E0300EDCULL, 0x607931D2FAEBAF69ULL, 
            0x0706BB4324BCE6EAULL, 0xD4A66DD50853F708ULL, 0xD3D74F2DEF74B02CULL, 0x80579493951D467DULL, 
            0x2660DE38F6B617B6ULL, 0xAB678198337787B5ULL, 0x9AC03950244DFB5FULL, 0xFE71BCAF0C72B0F6ULL, 
            0x57D3CDD13ACFE5F3ULL, 0xCBF3D92C272924F4ULL, 0x1BD69D6BEF263F93ULL, 0xEB4E2A867FFF658BULL, 
            0xE74D2063FE0369D0ULL, 0x821629C5D0657E80ULL, 0x534C993110397753ULL, 0xD6F5121CA8136CDBULL, 
            0x022C75F7B9379FFAULL, 0xB15AC0164B5C5C75ULL, 0xC48E0BEE8813B370ULL, 0xC3F9BF7EA7E48BE6ULL, 
            0xFD52669B20E5A1FFULL, 0x530D957833EF3802ULL, 0x0BFF81CB497376C6ULL, 0xBC26AEE246C14FE0ULL
        },
        {
            0x067E9FFD58A4F27DULL, 0x41AD22C5A8A53572ULL, 0x9612832BD6A7ED52ULL, 0x7FEDA013A575A732ULL, 
            0x65C68827F3A43C68ULL, 0xBA875015F88D43F6ULL, 0x848E8E6226DB2A2EULL, 0x9983459239B539DEULL, 
            0xFFF2BAD6A3E1D69CULL, 0x4F831BB8F480A48AULL, 0xC3D92376D0E31A9DULL, 0xBE98D8EAB6CD35F9ULL, 
            0xFE38DD4797EC502EULL, 0xE54769C69FB31C5AULL, 0x021DD2FC7F535EADULL, 0x14511F53BF442B08ULL, 
            0x66D9163E35F285F4ULL, 0x8C96EA1F70094D97ULL, 0x0FF597A37CA8B7E4ULL, 0xE55577BDAF08D4F5ULL, 
            0x60295738ED98532BULL, 0x218EB95D820C4FDCULL, 0xDA720E22E220AF16ULL, 0x24EEE36732645E0EULL, 
            0x9AB3D8983ADD2786ULL, 0x576E2EE6A4E7BC0BULL, 0xF4AD6FA2EAD6E804ULL, 0xF46A659A1616A13FULL, 
            0x6B47FD8083B15D2EULL, 0xDF7020DBB5241E03ULL, 0x95837B98B514AFCEULL, 0xBBCC99EE13CF6820ULL
        },
        {
            0x6E2F9F8458DA61D7ULL, 0x2B355DDC939DCCBEULL, 0x30D045351D941D29ULL, 0x46A5FDAB127A5960ULL, 
            0x1BD144C38BEBDB25ULL, 0xC75A28D21B8AF930ULL, 0x253C31DDE3595019ULL, 0xA9D0BDE0A08BB1B8ULL, 
            0x2B338C878CC0E72BULL, 0x3677C05B99B5BF5CULL, 0x510554D72DFA2C74ULL, 0xF1623E25289BAF07ULL, 
            0x94BE78343E3B62D1ULL, 0xB623E7FA2A14D8AEULL, 0xBB7D4906E22FBA3CULL, 0x2104A163CEADDD97ULL, 
            0x968840A558398F0EULL, 0x9832E8FAD437C7B6ULL, 0xE9054691D1E2E11BULL, 0xD3B30D2583CBC10AULL, 
            0x5809D8E39C30F338ULL, 0x50BB5863F987A8D2ULL, 0x7B8789D0AB20EAE9ULL, 0x1A1AF859BF0514CEULL, 
            0x664865870767A5DCULL, 0x712D05EA35EF7149ULL, 0xD544AA095EA6393AULL, 0xEF18F7FB12F8FEB5ULL, 
            0x5ED8F17D9EF277E4ULL, 0xC41B31257CCF163BULL, 0xDD339EBDD5336B28ULL, 0x13A5670671AFC625ULL
        },
        {
            0xBA050A5C3375288CULL, 0x30D0AC289C97BD9EULL, 0xF9488EF03A3D5D67ULL, 0xDD3607D1D843A98AULL, 
            0xDF4754D00C107459ULL, 0x38C0727E07B53C21ULL, 0x659F8CA42DB33C87ULL, 0x9B5DABF802702FB6ULL, 
            0x98F70FA5E0E74DE3ULL, 0x31E65DC831D1FB61ULL, 0x32ACD48323C4434FULL, 0x5CD1C122A017515FULL, 
            0x7D2F6097CA603360ULL, 0x5A19EE86225A13ECULL, 0xED926CB4C0F458DFULL, 0x60C6A8AAA1F33AFBULL, 
            0xE7B4E3EE71077AA2ULL, 0x1F6BEE2AA813FCA0ULL, 0x131FED1AB30773F2ULL, 0xAAB0BCA17D04917DULL, 
            0x23A10A503263B824ULL, 0xAB11BA1BA3F04365ULL, 0x54509D6BDAD66C4EULL, 0x3711AAC5383002E4ULL, 
            0x6A7C98905A314CA2ULL, 0x40CAB1B969D7B989ULL, 0x66EBBFC4122DE46BULL, 0xF5ACB8B975754E4FULL, 
            0xF0910C4DAF9A1190ULL, 0x003BD9D074991CA9ULL, 0x2E946B3D26344750ULL, 0x65952319F4471B84ULL
        },
        {
            0x469C53F4BAC40395ULL, 0xF96F4468CB66CE9DULL, 0xB04A13B24E8AFDBDULL, 0x2F1A5639DB944568ULL, 
            0x78A99512080C29A0ULL, 0x9C6104678C7CBA19ULL, 0x2B340141D3033B31ULL, 0x32C4E16D4B591B06ULL, 
            0x918282C1B8E8ABCDULL, 0xE8319819470013C1ULL, 0x06A24459C594BC36ULL, 0xDE92DB51FA4AD63DULL, 
            0xEF3279AB94742D46ULL, 0x29389D78AA2DB426ULL, 0xC43BD6DDA48A3D64ULL, 0xA40CA31EB75828B8ULL, 
            0xC34EEFD1E3C26859ULL, 0xC3EBD27DD4487B28ULL, 0x142B4B1EE3365751ULL, 0xBF2EF601E811346DULL, 
            0x77E6B3FF0BA4DA6FULL, 0x525AAE11A71CA17DULL, 0x3C2E9FF3E5CCDC8FULL, 0x93F4E82CAF4F984DULL, 
            0x278ECE26BA5FAD7CULL, 0x75D59ABF2AECAF55ULL, 0xCA480E7B00F49C43ULL, 0x35160C78857BC44FULL, 
            0x03FD8C71F87C7A9DULL, 0xB388B33DA7E62F52ULL, 0xAD97334784D72AF4ULL, 0xF72CD39B0099DB93ULL
        }
    },
    {
        {
            0x82BD62A48A972FABULL, 0x66DAE9019FB97E71ULL, 0xD9ADBBF2FFD25FDDULL, 0x21C6AF27492A9E85ULL, 
            0xA5FBF6F87FA0F2FEULL, 0x92335AC99EA93280ULL, 0x21FC6B0E75E0383BULL, 0xABFE54927EC440FFULL, 
            0x7D47FA071026A954ULL, 0xE11804CC5C180830ULL, 0xD49978C13EB7DE47ULL, 0xA74BDD7B895D1001ULL, 
            0x89E8ED7601AA9C5BULL, 0x61331EB8AA50B607ULL, 0x161EBBC868BA8F4FULL, 0x45F95C66F583C815ULL, 
            0xEA3A715B4FE799F1ULL, 0xC4EFF9D8274C936EULL, 0x10205D511E727355ULL, 0xE24603B88C32221AULL, 
            0xEF072711F821EE29ULL, 0xE9C62D65FC3A3A95ULL, 0x673EC377F014C128ULL, 0x6E020328299033FFULL, 
            0x02B59DAEDDD8463FULL, 0xA174B30256BB99F7ULL, 0x53F266B348D7D2F3ULL, 0x7F4541AB2B39E3A2ULL, 
            0x8082C5E995179838ULL, 0x435EF3106F5836A9ULL, 0x3FE1E3B81D34F5A9ULL, 0xEAF5E1D6CB5383CDULL
        },
        {
            0x9CA728078E5386F4ULL, 0xFEDD621141645E11ULL, 0xDEB18CE2583C18D1ULL, 0xBA4B16E30D9D83F4ULL, 
            0xC3D38C0F830D3590ULL, 0xD7739E04C70E31C7ULL, 0xD156605E4315D985ULL, 0xA9D9668DA38E116BULL, 
            0x3A92D32BCCF64DB2ULL, 0x7CAA0404BCF239EBULL, 0x0342F9391CD485DFULL, 0x04B361D9AFC26DF3ULL, 
            0x02CDF4EDCD7E996EULL, 0x8D509D00789B2A35ULL, 0xE43EA0B81AE92797ULL, 0xF71D23EEC2292C7AULL, 
            0x94A6CEE8F5C1EF13ULL, 0x54FA06F1C3964836ULL, 0x4C373426D68EC264ULL, 0x89DA19D8E29DC62CULL, 
            0x4C95EF6DB9CABCB2ULL, 0x60F48F2ECD9A9A23ULL, 0x0E33D6E89F58A5C4ULL, 0xFB645B4C4FAD25BBULL, 
            0x22AB452220AE162EULL, 0x583845D1201A3EA0ULL, 0x115769D2AC309962ULL, 0xB2B1B10AF140EDE5ULL, 
            0x74C99ACBDEDEF370ULL, 0x43B9C5E695C8FD09ULL, 0x3C8DE0B43DB8C08EULL, 0x51C43411B9ADB97DULL
        },
        {
            0x2A966A4EBED8EF2CULL, 0x4176248D2E5EB42AULL, 0xE4BFE06CD6AC982FULL, 0x685D980D9360460AULL, 
            0xFD0E27A89C799BBBULL, 0x2247E7AC12B809D9ULL, 0x9E2F5E6C809CAD4CULL, 0x07C6C181D03D6F73ULL, 
            0x3049F58D85508971ULL, 0xD1986ED227361B1CULL, 0x527BFD625D7EE8D5ULL, 0xE0E421484124207EULL, 
            0x2E6A1C61B37FC0B3ULL, 0xB5DFC1AD81BF7927ULL, 0x3CF996176CA3F60AULL, 0x4E60A5FB0A2E9C1AULL, 
            0x70625C3EB5E6ECC1ULL, 0x1F13B757AA69F107ULL, 0xCBE3BB3FACE9F346ULL, 0x02A178C171EF4557ULL, 
            0x4B2E6E14322942AAULL, 0xA8D7D800EDFD8BE0ULL, 0xC57C941811DB6BACULL, 0x636DBD2311476A9FULL, 
            0x62AFEEBA2BD8482AULL, 0x3EE77123658BBFF7ULL, 0x33797CCC93CE7795ULL, 0xE1C5722064FEF000ULL, 
            0x09CC4D3842D16503ULL, 0x40925EC99FD20A5AULL, 0xFC2A656934ED8141ULL, 0x8C00202E82E1C902ULL
        },
        {
            0x6FF9D0CF897818BFULL, 0x7B4CE26F60CA97EBULL, 0xD8D0058123750CC0ULL, 0x8FBE00B211760CD4ULL, 
            0x93A324B898400524ULL, 0xF9ABC405BE7426B5ULL, 0x45B0D28138D8B7FAULL, 0xEDC82D756CA09E82ULL, 
            0x0CF7CBB36996C7B4ULL, 0xCE789B46B83BFCC6ULL, 0xD3DFD76BBC895281ULL, 0x743C87FBEE87CB89ULL, 
            0x582DCBC98E63A040ULL, 0x8954090702EF2272ULL, 0x73F706EB01DF3D31ULL, 0xE1D1637F7B63D520ULL, 
            0x512BC83CF33E14CCULL, 0x91FE5214464FE2FAULL, 0x4F705FB3CB27618EULL, 0x772A0DC5652AC8DEULL, 
            0x83706289CFBF6D55ULL, 0x5DEACE139CA2009FULL, 0x55AD6E5452A339DAULL, 0x8AC174C89504B213ULL, 
            0xF33A12A9655545AEULL, 0xBC3725EAE81E9F14ULL, 0xCE57DD0C1D2917B8ULL, 0xDF8143E9DB1FF4D9ULL, 
            0xB0D947BDAB3E8F98ULL, 0x371A90886E2CFD96ULL, 0x7077E3A9576654FEULL, 0x62F3B4C23CEC59E1ULL
        },
        {
            0x6FD472B296F044F5ULL, 0x82B9AFE4A8D3B680ULL, 0xD9176B9D356C3F12ULL, 0xA3C24CE57466AED7ULL, 
            0xFEDA15874F7861F4ULL, 0x118FC9D65D56C459ULL, 0x7F07232B001B14A5ULL, 0xB9848D06CCBC1BF0ULL, 
            0xC32CDF591C39E90DULL, 0x59441922F6A9699FULL, 0x2913533FE9BB8221ULL, 0xE0965F894928EF47ULL, 
            0x3C4BC39746B47B37ULL, 0x14F5970312AD8861ULL, 0x1C8678B73416F1F3ULL, 0x5944FD55F4637679ULL, 
            0x2C17BA349D6F6A6EULL, 0x4D0EB1B3C8E8456BULL, 0x2059D018B5C59020ULL, 0x81532D15FBECBC16ULL, 
            0x146EE0C5791FBACEULL, 0xA81B6CE6DCD7F82AULL, 0x6208180145446BFFULL, 0x83A2FBA46AAFE295ULL, 
            0x1CDA7255451938DDULL, 0x4D9FB318363E4B89ULL, 0xEDD0FE9B9B25EF6BULL, 0x3E6351E1AD95C584ULL, 
            0x048AA1D216B840F9ULL, 0xC2F7382B4FFC869FULL, 0x014E547A63882397ULL, 0xB3913593BD4B3DB6ULL
        },
        {
            0x7D684A8E01375639ULL, 0xA3496E82200B40B0ULL, 0xF90ED9E97BEB9AD1ULL, 0x4A032B95FEC18A81ULL, 
            0x71C4E827F9614088ULL, 0x50E4B83C6DD9E5B0ULL, 0x21F046ABFCD83F23ULL, 0xB3B007D3BD6AE915ULL, 
            0xECADB84A9C1418C5ULL, 0x9C2BAEEC720DEBAEULL, 0x587A97C1942FE6E8ULL, 0x49829088C3B07AE4ULL, 
            0x182DCFE1685BA2ADULL, 0xA7664620894812FAULL, 0x3AEF94C47613C537ULL, 0xC8A20C75BCC3FA14ULL, 
            0x923A723999275B81ULL, 0x4F8D8FB49819575CULL, 0x2A9544B02E345E87ULL, 0x42A5383E0CADBDADULL, 
            0xA5725B09ECD6BD57ULL, 0x8EE473E3A7571F9CULL, 0xC5DAE82CA40E3324ULL, 0xB5C7963D588E93C5ULL, 
            0x1FC449D29810C4A0ULL, 0xA0EBCDFE157C1B42ULL, 0x650C07B9E268198CULL, 0xFA2872D889792C56ULL, 
            0x7549CFC0F160FED5ULL, 0x347EB022DD274862ULL, 0x94C27492047D7F3DULL, 0x1EC7A1F431A34596ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseGConstants = {
    0x221062E070FFF3CCULL,
    0x648C31CE05C602B9ULL,
    0xD96A5F94F297513CULL,
    0x221062E070FFF3CCULL,
    0x648C31CE05C602B9ULL,
    0xD96A5F94F297513CULL,
    0x24127279C01A656EULL,
    0xB1BE189B89C46050ULL,
    0x46,
    0x16,
    0x66,
    0x2F,
    0xA6,
    0xE9,
    0x89,
    0xCB
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseHSalts = {
    {
        {
            0x419D5C586ABD9CB8ULL, 0x28418EF60B06A29DULL, 0xAF5196187233E232ULL, 0xC5E0DAB0A36FE337ULL, 
            0x0686D0DBF3F2572BULL, 0xEC9B1AC477361640ULL, 0x5E694AD52BE4F0DCULL, 0xE1058BCA29D56206ULL, 
            0x7F704F273FD6213BULL, 0xAE860F04322E1C27ULL, 0xC4D1BB8110F7BD8DULL, 0x3AA512CE483D5E8AULL, 
            0x5D15C5B79E3DF646ULL, 0x99451B14C775F61CULL, 0x4F76CE43541B684FULL, 0x93CBB09437224B78ULL, 
            0x7671DF0CED29002AULL, 0x958397B8FF0147A4ULL, 0x5693CEC1122D1C0EULL, 0x7CF048397690B07EULL, 
            0x6BFD8BC77B9FFB91ULL, 0x077664BFA252A64BULL, 0xF8BD38575784058CULL, 0x51D8DA67BF51AAB1ULL, 
            0x7DB33973A5560146ULL, 0x72166A952907D4D1ULL, 0x9AAE0856219DCD21ULL, 0x4B978B7AF24212DAULL, 
            0xD5261852B9FD286DULL, 0x18821DCBA37AFF69ULL, 0x9EA2B31994C9F378ULL, 0x296203C78962195BULL
        },
        {
            0xEB8C3836404D3F4EULL, 0x7C0E06D8341D82A0ULL, 0x76AFF52B8FF3ADC3ULL, 0x7A48DC7DAA96A580ULL, 
            0x3A59E1AF84256C05ULL, 0x5D709D2AE7834552ULL, 0x1F54C00B5B74B5C7ULL, 0x56DD963AC47F5E31ULL, 
            0x1A7FE5064701377BULL, 0xA75E4D0882AD0E55ULL, 0xBD1A153322C5F0A4ULL, 0xEA822C2BD6283B27ULL, 
            0x155FE42BC6B185B1ULL, 0xE3776DFEFA183ABCULL, 0xDBA16F36B767B1C6ULL, 0xF374855D89D92375ULL, 
            0x4600A043A9B6A208ULL, 0x0024F3136E5D1DDBULL, 0xB691F783B4E4FB34ULL, 0xB8BDA82A20277B8BULL, 
            0xF90730D6A2DC893FULL, 0xEDE4AB41DC4A9D54ULL, 0x099A0C5ECCF40932ULL, 0x1A42A7016429A850ULL, 
            0xB8BFE32834692312ULL, 0x975E1CA75FC159B6ULL, 0xB4DC6E3A3838DFBFULL, 0x05488DE584AFD120ULL, 
            0xD057E3405BCB7558ULL, 0xB96BB93626D55FE4ULL, 0x11B2C6AB41971085ULL, 0xBB67158BB6A02E5EULL
        },
        {
            0x5FEF802C91EF0AEDULL, 0x711CF6ACB0CA9A23ULL, 0x2CFB04CF60EFCB10ULL, 0xB8F234D415D91AA3ULL, 
            0x4E8D7537C899738DULL, 0x3A0A1B96483E83C9ULL, 0x1F96262DD05E3FDEULL, 0x345AB37F15A236E5ULL, 
            0xB14D03F8DFBA546EULL, 0x945458778193AB8AULL, 0x31619012B5371CBBULL, 0xBE2CE0EC44BEC0E5ULL, 
            0xED4B81AEC1BE327EULL, 0x375637595086A710ULL, 0x88DD3B3FB78A39EBULL, 0xB804E60FF543A6E9ULL, 
            0x4C5978640301AE81ULL, 0xADBB557A5F1D6A27ULL, 0xAEE23956FC5E5753ULL, 0x24E948EB3E76BEE6ULL, 
            0x6EF848D477DBB43FULL, 0x0F16DD984D174DB8ULL, 0x8ECFE50CBC43F2ECULL, 0x27EA14AD3BD1E3D5ULL, 
            0xBF293E27A8D13FD8ULL, 0xDE2AF16E6802D788ULL, 0x89D8E8602567F182ULL, 0x94460F4748274C7AULL, 
            0x20C1A322D91FAAE0ULL, 0xB459EE84F3037282ULL, 0xB5DEBAE06829193DULL, 0xCB6C3B9AFCD55A37ULL
        },
        {
            0x9D0F13BF6D132200ULL, 0x75414CAAEEE4AAC8ULL, 0x873EAA3778EE75D1ULL, 0x40FA78D289C397D1ULL, 
            0x48490507F8CA6A35ULL, 0x2DB8DA5AFF1FB804ULL, 0xCCAED994E5BFF6F0ULL, 0x415C89C4DCAF3CF1ULL, 
            0x08796926FFB009B5ULL, 0x6F45487755BC132EULL, 0x8DB56B23D981A594ULL, 0xC025D018F3967F63ULL, 
            0x2DF12186B432A5FBULL, 0x24C5614338F02597ULL, 0xA0EE28A24E5A2FEEULL, 0xC2A33B978CE1EC8EULL, 
            0x3FA76F5BAB32B4BFULL, 0x6C18DFE2CF48847CULL, 0xDCC2CC2B9660705AULL, 0x5953C7E917875CDCULL, 
            0xF5F77214F525C7D3ULL, 0x9A3201F9756DDC86ULL, 0xE2E7D05790787D11ULL, 0xBCC7C0E28788DC39ULL, 
            0x0827D7B1E8FC6F0AULL, 0x8DB2F12EAB0C79F4ULL, 0x9302D13DB52FCFCBULL, 0xAE9F4DDEE9D3A67DULL, 
            0xED727314459387F0ULL, 0x39B79EAD8149B0F7ULL, 0x6DAA94CE19D4CC57ULL, 0xB4522F7F79978FEEULL
        },
        {
            0x0D4F46436036D735ULL, 0x6BE996EF7FB9CAF1ULL, 0x607D5D11AD534BFCULL, 0x23E6BB49ECF1FF9EULL, 
            0x6B968223296AFA15ULL, 0x5CF47A57CD81ED33ULL, 0x2A14523F9356D487ULL, 0x7260B31A5916A222ULL, 
            0xD7F60A7D946639C0ULL, 0x66CC9A19F17311DDULL, 0xDD0215F50983CAF0ULL, 0x2EE67D07C42ACD05ULL, 
            0xCD0DA012A741B75FULL, 0x2E78822CEA31AA9FULL, 0x0277CC77579D9B37ULL, 0x6DA03CDC6FD55AE5ULL, 
            0x51DA4D387A874A19ULL, 0x1AF53A6EFB52A02EULL, 0x0EBE96AF9A1F0A1EULL, 0x1C0721D23ABC1DE2ULL, 
            0xDB69F80CDAB5D8A6ULL, 0x8B07889D36F2189FULL, 0xB1243FAE12FCE160ULL, 0xB2458EB3C1402DB1ULL, 
            0x88EA9AB18C2AA7AEULL, 0xD856FAA7A87ECBB0ULL, 0x16A5003ED3A57203ULL, 0x7F8D71AB6C15A130ULL, 
            0xA42EAC5DF79B1B79ULL, 0x021F9E1DB1F2C1F6ULL, 0x044D864B29DFB546ULL, 0xE6DB6CAD144186FDULL
        },
        {
            0xC08C72F05A0233C6ULL, 0x7C92E6997FD38A7CULL, 0x425711D3AAD01713ULL, 0x54E90E67D93B78E0ULL, 
            0x05528384259B789DULL, 0x010B25F1D0AA26EBULL, 0x1BF60C3011B77A7FULL, 0xD1D0805968FFCF68ULL, 
            0x2E84C041F88E9BAEULL, 0xCA5FF6533EBD4249ULL, 0x28E1C01F5F429C21ULL, 0xD94B6AEF3B6C0274ULL, 
            0x0845074ECE2E17AEULL, 0x7BC1B2A064B67F51ULL, 0xB813B6E8E49F85E3ULL, 0xD301727E6436310BULL, 
            0x924D6A6A954FD132ULL, 0x1D299590FFB2A286ULL, 0x8B323E4721C9377FULL, 0xDFF7ACA30D4A2F63ULL, 
            0x0EA85C1C133D4B0CULL, 0x9F6E3C56D084577CULL, 0x5BB7EF910D5D990FULL, 0x15D440D49F4EA1D6ULL, 
            0x8D7872649CA31B60ULL, 0x07EDFC9924EF08F7ULL, 0x70E64CF8CC1FB857ULL, 0xECE395AAE2324C98ULL, 
            0x164E31600300FE4CULL, 0x9CED2BE0CD5F6C35ULL, 0x42E7F415EA0B45CDULL, 0xABA574D1CB799695ULL
        }
    },
    {
        {
            0x7A9DC7A18797847DULL, 0x1D0C0BC95B992678ULL, 0xAEC4F2A710F91433ULL, 0x710A116E4BF27A51ULL, 
            0xEA3F17433C99D7ACULL, 0xDE9FB3D12788CEEBULL, 0x8B4219ABF5FF226CULL, 0x89AB3E1A46A9DEC3ULL, 
            0x741DEC822D91063AULL, 0xCAB67EB92AA4978DULL, 0x41847FF074406724ULL, 0x13EEE90BC38221BCULL, 
            0x9460AEB68CC47858ULL, 0x042597E79F21538EULL, 0x4AE7D60FBCB41EB4ULL, 0x0B20F4101614B537ULL, 
            0x67DB2B638CBCB56DULL, 0x18E91F40C13AFCB0ULL, 0xE8312BA886A66F17ULL, 0x5F81E2C1F791C3C9ULL, 
            0x7822AD06433200DEULL, 0xA9DEC2577E78B14CULL, 0xFD750B00E9018652ULL, 0x74450C2DC44C146CULL, 
            0xA266C8B37648C71BULL, 0xFA849F64E1755497ULL, 0x0187845325AC576CULL, 0x487555E19CD360B9ULL, 
            0x3F478ECF9DCA7609ULL, 0xDB42032493D9AAE6ULL, 0x2F5BD91488606686ULL, 0x92D27ACA889ED277ULL
        },
        {
            0x7E2004B00C6FBD69ULL, 0x38934B9A6690B93AULL, 0x4E8318368ACF2BDAULL, 0x0D3366161636F8F1ULL, 
            0xCDBAC11341B68F7BULL, 0x42A4F8A8CD65E59DULL, 0xC702306183ABB98FULL, 0x1D6C5BBBD1C68A72ULL, 
            0xA57574B80A6E330AULL, 0x7495F69930CDD329ULL, 0x5820B3209856E6C8ULL, 0xD6ED3D056138E055ULL, 
            0x1935B4E0F8109DBAULL, 0x1B92931393D73947ULL, 0x9D22BFD645ADD949ULL, 0x4C8A0C284A16C78CULL, 
            0x1428ECBD05827DD8ULL, 0x9F6ABD79F4936834ULL, 0x90F1FCD829587904ULL, 0xBDDC2F834FB0DE84ULL, 
            0x4864E35A82E1A058ULL, 0x74471A64686C0D1DULL, 0x6B6CB9BAB8F9DDC4ULL, 0x35C0BBB10B58BD82ULL, 
            0x1BBA4C3306B6C274ULL, 0x99274D56BA6F5A69ULL, 0xE182621108DB0B4BULL, 0xD16C73542C19706DULL, 
            0xA35DE61220970813ULL, 0x1E77DBFF72AA844EULL, 0x9A85CEC757CB08B4ULL, 0x002E820E04EC7107ULL
        },
        {
            0xB34D0DB77C3BB5A3ULL, 0xB09087BCF7D805B0ULL, 0x101F386CBD8179C2ULL, 0xCAFC698C4221660DULL, 
            0x1D9B12BF182EE16CULL, 0x9D27F14255AFED1CULL, 0xDF818AA06A6C68D6ULL, 0x2464DAB5F7950D66ULL, 
            0x6D77808EC08A00FDULL, 0x294A5D1ECEF6F971ULL, 0xDC311C9D9A910F4EULL, 0x9B5E653A53649DA9ULL, 
            0x0B7A6F8D895342AFULL, 0xC3D2DF24D41B97DEULL, 0x0D162B5E20CEEB46ULL, 0xCC365B422ACF42C8ULL, 
            0xB3AD89603F8410C3ULL, 0xF2D8C2DD6E6EBAEAULL, 0x92AA799CC71B074EULL, 0xBF4851E4B1BDE82EULL, 
            0x4ED36951D8DEBAB6ULL, 0xC6351BBB9645FF39ULL, 0x46D0C5C6FEF605A6ULL, 0x1E1A90038F82F758ULL, 
            0xE3D203643FC50170ULL, 0x4729B6D85E76A33CULL, 0xDCD5F928C9634024ULL, 0x0EA273CE76081502ULL, 
            0xAEAC4923757AD6C6ULL, 0x7CF08ABBA72AD7F5ULL, 0x7313D10D6052272AULL, 0xB066867D0419E68CULL
        },
        {
            0x705D484F0EAB230BULL, 0xC5DA4F604B09A3B5ULL, 0x927B4C57E43AA3DCULL, 0x927EBEC7F585D429ULL, 
            0x344BDDE23D0F3157ULL, 0x363181257B9C5F43ULL, 0x127AE89193285F06ULL, 0x0CAE5555911ABF65ULL, 
            0xFAD21FEC8CCCC89BULL, 0x2918656516DC630AULL, 0x62071AD3C7209C26ULL, 0x82074B8E4DF30838ULL, 
            0x1DB35DBB8F0E54C9ULL, 0x931BA6A401160FB6ULL, 0x7C43B81AEBD601A5ULL, 0x0A6E65E0345448D4ULL, 
            0x8A10DAB38ECEC9A9ULL, 0xD44AA8CF91C788E4ULL, 0x0DED727026DCDCD3ULL, 0xFFBA12F41F4DEE70ULL, 
            0x9E337459E37FB7F0ULL, 0x527CF7C7926D34F2ULL, 0x4B3C167B6BE36674ULL, 0xACBD8C9B0D543558ULL, 
            0x32CC8E4A222CA074ULL, 0x6D487D4D3A713B21ULL, 0xD8DA3D16C6E92204ULL, 0x3BB18CA4CF5FE84FULL, 
            0x182BDD10559D1433ULL, 0xA47B33E407C3780DULL, 0xED7B2AEEE0D1275BULL, 0xE4D67B5F54633C23ULL
        },
        {
            0xB57AA176C9AE056DULL, 0x70F2B6A3D85ED39FULL, 0x26495B5959AFC826ULL, 0x5DA57AE0C92BAA80ULL, 
            0x20B8872DB55CC12EULL, 0x2D2B9A7ED1822791ULL, 0xD57F39975F198333ULL, 0xC62531726FC3D829ULL, 
            0x236D92D7F7D1ECB6ULL, 0xF4395A0C7596610DULL, 0x32AE80A39915F509ULL, 0xE9B73D06889E589EULL, 
            0x93659633B36A0E69ULL, 0x29CEED6F8A7BFB91ULL, 0x07ACE6EE67590431ULL, 0x682AE540EEC562C4ULL, 
            0x5A15F9BD7EB46EEAULL, 0xEE2BBC30AFE78B1FULL, 0xBB1397BD271A5031ULL, 0xEAF0D6743F7B6E59ULL, 
            0xB5FB8E2914B037D9ULL, 0x02090E750F5DC04DULL, 0xF436A9F7A272647CULL, 0x3C870D1681C9A72AULL, 
            0x3A373E85A267FC54ULL, 0x4890326F15192498ULL, 0xC2643C5B8B8A9BDCULL, 0x2B54AB4EA94F7CCDULL, 
            0x96A0C615382BCD88ULL, 0xA85DE6326242B21BULL, 0x7D4FCB590192568CULL, 0x05FD32EDA03E736FULL
        },
        {
            0x532BF00568DDE818ULL, 0x598B3E3D03C6DB7EULL, 0x98989128829EF729ULL, 0x89C998B283CD43E8ULL, 
            0xD32C0EB0ADF39D8DULL, 0x7CBB289CA9E971F4ULL, 0x9278F5A63669DBC1ULL, 0xC92C54ADC749FB26ULL, 
            0x007EF87045FEC22CULL, 0x1BD637DA444F2AB0ULL, 0xD682DF1258AE5E92ULL, 0xC7E283384D798CB5ULL, 
            0xBC44C06B5739AA8EULL, 0xC7941F31493A61A2ULL, 0x93944C1E61DDA5F8ULL, 0x6784EB97AABC42C3ULL, 
            0x90960391EB51C897ULL, 0x5E5845F06E81324BULL, 0x371841B9AD818809ULL, 0xC982E95CEE1A06FFULL, 
            0x09A4F7D64EEC0967ULL, 0x66DCCCBD3AA82861ULL, 0xA6FB9E92EB611203ULL, 0xFA7096BC3FB0DEBDULL, 
            0xFF90E55D7D181921ULL, 0x33A433024CAA0B09ULL, 0xD16A62EF8F502CE1ULL, 0x6090B1C30CFE55B4ULL, 
            0xF12F1D4CCC8764B2ULL, 0x9EF739693AE95683ULL, 0xACAE9F0C5AD94896ULL, 0xDE57A906AFACD4BBULL
        }
    },
    {
        {
            0xF9E86A940D2435AAULL, 0x49A5FEB2FC16FA36ULL, 0x1B6B42220A36A900ULL, 0x9B7C8582F4F61C1CULL, 
            0x7E32D9432808E0B8ULL, 0xAFE879853B685DCDULL, 0xF936B5AD242C3138ULL, 0xB4FDD7DCC9647177ULL, 
            0xB1E5239F9E165648ULL, 0x0AE36AF512379FD0ULL, 0x20477C83F88B9FE7ULL, 0xFE6471AC5D26388AULL, 
            0xD5AD88A3A8D3BCC6ULL, 0x833DF2DB72E1DDBCULL, 0x95BBA1FE7333EDB2ULL, 0x18D3286F32229E9DULL, 
            0x3F2BA08074DCAD82ULL, 0x6F8FBEF0C98ABFF5ULL, 0xDBF023E0FDC204A6ULL, 0xC0962EDBA5BD7A9CULL, 
            0x314E6B113A0513B3ULL, 0xDD79E82E293B3EE2ULL, 0xB03FC8BA9EA973DEULL, 0x9095843E003498D0ULL, 
            0x1FE8CE48E4801B68ULL, 0xD75C94193ECAABCEULL, 0xAA89430943C2F842ULL, 0x07CD9D611B1D2BD3ULL, 
            0xF650E7377AF669A1ULL, 0x3FCCBFFF4F3019E1ULL, 0xE78250A93538F0CCULL, 0x34F01471D835D60FULL
        },
        {
            0x289818DF37975B99ULL, 0x96A865CD01EA4B93ULL, 0x2AA728D2D872A27EULL, 0x759AE70FFE00FB29ULL, 
            0xEE95D39E3D1C8878ULL, 0x00D5B8F0567D057FULL, 0x2EADA37911A1734BULL, 0xA2AF0A221BB93D9AULL, 
            0x81D2173D6CE2305AULL, 0x70A982C8177163FBULL, 0x6D23D1E3A1CE8135ULL, 0x355DD83359E88E09ULL, 
            0x1D38F7511DE3D17BULL, 0x5CB24045C2953D02ULL, 0x0FF148A4F52EAC2FULL, 0x82327BF42CE0A097ULL, 
            0x576FC389BA3242A6ULL, 0xEE804B0264AC52C8ULL, 0xF4E085102758BBACULL, 0x13CECB5693B43CF2ULL, 
            0xE014F2FD550AFC54ULL, 0xA852A9C8850111C0ULL, 0x548DF7FBAC6A62EFULL, 0xF5763B34355686C3ULL, 
            0xD3FF90E660C1C0EDULL, 0x9FE1FBBBC7C5484BULL, 0xD0ED78979DA2E242ULL, 0x14C43770049773B6ULL, 
            0xDAE597F46D3E8ED2ULL, 0x6D28FB2B8D16177FULL, 0xD1F1CE884B808A29ULL, 0x45B2723A78D832A9ULL
        },
        {
            0x90DAE508B6BF1022ULL, 0x5594A40BC9A0AC01ULL, 0x31D557B9E1CA80C4ULL, 0x604A4BCF5006DC20ULL, 
            0x90794DF2BE878239ULL, 0xD7BA3E3956F42A7DULL, 0x4E4699BD20CE1EC3ULL, 0x10961CFE91A55B3AULL, 
            0x2379D933524CCC99ULL, 0xCC0BC3E00BE2AA95ULL, 0x024D80CA35722D54ULL, 0x29D3FC6BE3B3622CULL, 
            0xD5CF4E2A0EF95CBBULL, 0x92655D171F09A2C6ULL, 0xAA0657DB601B0D1DULL, 0x2FAF818DA4FB4E66ULL, 
            0x7629BEB80064D7F7ULL, 0x3690551342FC01FCULL, 0x86C3A8E5F6D8CFD8ULL, 0xEDEA27981530ED30ULL, 
            0x839E107BC3B0E3B3ULL, 0xB8989F0D8D946415ULL, 0xD6234C3954203A85ULL, 0xABA268C90AC50B13ULL, 
            0x2984D4E5BDBD8865ULL, 0x5A9EEF96B25883C1ULL, 0xC848F0E82239FAFEULL, 0x0176592C69408351ULL, 
            0xE500D528D5D39346ULL, 0x1A6CF85C580C53C7ULL, 0x9DC557E2023CA6F1ULL, 0x842A74FDCEB3CBF5ULL
        },
        {
            0x866403BC6A9F7709ULL, 0x08CF345147644D0CULL, 0x3B9846CE9E48C7C2ULL, 0x81A723537102209EULL, 
            0x36EFBFC8F075C318ULL, 0x841EA5BDB113659BULL, 0xF1FC7870DF3AFB08ULL, 0x9CE049E15D9101C6ULL, 
            0x98BC18F143ADB0CAULL, 0x9C95B2376F3CACECULL, 0x8F503BFFE8E1E74FULL, 0x262035E902C942A0ULL, 
            0x5406EBF6AE88E888ULL, 0xF6638C04678E1AF0ULL, 0x0C6238A7A22F62DFULL, 0x9932C175AD3AF4D7ULL, 
            0x4434C041CD341FD5ULL, 0x9EB6A6AC7B5A6024ULL, 0xC5FEDF1425483D6AULL, 0xB481B1A9EC307FC0ULL, 
            0x8E10DBCDBB249E4AULL, 0xBB2E72FFB386CCBDULL, 0x1ACD74483BDD800EULL, 0xF698E772117CF6DDULL, 
            0xAC73669B1599D8BBULL, 0x21A0AE45E15FFFACULL, 0xCC19FBC046D3E853ULL, 0xC61D55EFE6542E58ULL, 
            0x0468F67E3106FCE9ULL, 0x11759B5E11B9E51BULL, 0xEC641BC62590D4E2ULL, 0xF52ACA49B7E1E5D5ULL
        },
        {
            0x15741452EC3938E0ULL, 0x15E7F85ADC52A412ULL, 0xDE1C2BD1ABA9E542ULL, 0x4072F998E80E1CB1ULL, 
            0xD35130D26A2BA3F2ULL, 0x3A5FC7EE3B5FC9A7ULL, 0x0C736C819D8DE211ULL, 0xAA9EEC36A4A9532BULL, 
            0xE62B61D246CBE24EULL, 0xC5B0AD30CA2FD05CULL, 0x8013374F20E1A7D1ULL, 0xE71E9FC280730A5BULL, 
            0x1C33474CC798927DULL, 0xB0AC37FCABF103B3ULL, 0x354D107B8654E300ULL, 0xD3C754D753F50A14ULL, 
            0x1B97D37BBD1E89A4ULL, 0x572CAA2294022944ULL, 0xE452EAFA4B9DFC7DULL, 0x61ABB9238A12CFD8ULL, 
            0xA6BCE9D42E585D7CULL, 0x93C92EA7FAD3F490ULL, 0x9C7FBDCBCBA69105ULL, 0x778F84DD72E079F0ULL, 
            0xCF6DE7D81215F789ULL, 0x40570AC7C7ABA595ULL, 0x3BE65B76707175C0ULL, 0x0CDB98765411FF3CULL, 
            0x205D7C1AE21FF0D5ULL, 0xEF086275952F8EFAULL, 0x3E9181CDC9905125ULL, 0xDCF26E7DC8F32C4AULL
        },
        {
            0xA00140A4F47D5E1CULL, 0xFFB38E27532B60FAULL, 0x19375C32244AAA58ULL, 0xD7D5AE16E693A145ULL, 
            0x93863ED6ACEC9757ULL, 0x5860580FC75C1362ULL, 0x474DD10E50CE03F9ULL, 0xBC8EA54311E5C1D0ULL, 
            0xC3DC923DFFE571A9ULL, 0x2F2716914FE220ADULL, 0x6D52A3A9A777F398ULL, 0xA417C1B0C64A65E8ULL, 
            0xED3511D587049533ULL, 0x6B31021D89E8928FULL, 0xA519C695F9249C91ULL, 0x2C1B8AA4491FA7D0ULL, 
            0xEB3A9070445355F3ULL, 0x9EB54C82F5F21FABULL, 0x7A88DF00B8326A8DULL, 0x695751B7E73778DCULL, 
            0xDAFA48E7653FA4BBULL, 0x82E642428F216502ULL, 0x98D72A4E8FEF8D91ULL, 0x1DCB2F96488F381DULL, 
            0x28C8629119020EE1ULL, 0xB0D09FD985324CF7ULL, 0xDD1181C1B657EA95ULL, 0xDC7A2678CF76139EULL, 
            0x9230A2FE5C7F3696ULL, 0xBEA96E9B66B89F40ULL, 0x3C8DEE174D019DBDULL, 0x3195E5E29D7BFD82ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseHConstants = {
    0xCAC71B4867D03EF8ULL,
    0x2E6B942E5762D170ULL,
    0xA6ECE8D1C92CF71CULL,
    0xCAC71B4867D03EF8ULL,
    0x2E6B942E5762D170ULL,
    0xA6ECE8D1C92CF71CULL,
    0x9BEB67BEFB6CBC86ULL,
    0x16DC60EF965181D4ULL,
    0x58,
    0xE0,
    0xC4,
    0xA1,
    0xFE,
    0x4F,
    0x77,
    0xC7
};

