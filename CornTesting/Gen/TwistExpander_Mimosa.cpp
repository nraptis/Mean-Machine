#include "TwistExpander_Mimosa.hpp"
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

TwistExpander_Mimosa::TwistExpander_Mimosa()
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

void TwistExpander_Mimosa::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xBCC2CE888F218C64ULL; std::uint64_t aIngress = 0x911FB4DAFF01B680ULL; std::uint64_t aCarry = 0xF6C39238B90D2B05ULL;

    std::uint64_t aWandererA = 0xD7FDDD851867C839ULL; std::uint64_t aWandererB = 0xBF64C7CF72D8FC61ULL; std::uint64_t aWandererC = 0xC7D2B6983BA490D0ULL; std::uint64_t aWandererD = 0xEFAED7ED6EEAC523ULL;
    std::uint64_t aWandererE = 0x9D3F5B017D7EB03FULL; std::uint64_t aWandererF = 0xD779590F360913D9ULL; std::uint64_t aWandererG = 0x8AB880372A0792A0ULL; std::uint64_t aWandererH = 0xED75747ED86481B5ULL;
    std::uint64_t aWandererI = 0xCE49675683DAF52CULL; std::uint64_t aWandererJ = 0x8EABE4A29DE56655ULL; std::uint64_t aWandererK = 0xC9B74239AC2D030AULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12928305513145848292U;
        aCarry = 12959091153460225906U;
        aWandererA = 13456238307699800942U;
        aWandererB = 12565815892802692378U;
        aWandererC = 16064559253332957756U;
        aWandererD = 15984764906225766725U;
        aWandererE = 16943381110361394156U;
        aWandererF = 13643760596382329444U;
        aWandererG = 11686700367705493126U;
        aWandererH = 13761494913527600223U;
        aWandererI = 17957924055855760822U;
        aWandererJ = 10200906195885855584U;
        aWandererK = 9970044657009486523U;
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
    TwistExpander_Mimosa_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mimosa::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x815482E909CD4364ULL; std::uint64_t aIngress = 0x888A640692F7712BULL; std::uint64_t aCarry = 0xB2B4A4354FC469D1ULL;

    std::uint64_t aWandererA = 0x9B176EE9DFF64C48ULL; std::uint64_t aWandererB = 0xF2D0970DB6E3ADE3ULL; std::uint64_t aWandererC = 0x80EC2ED37FBC93BBULL; std::uint64_t aWandererD = 0x8F8E988A532F33B1ULL;
    std::uint64_t aWandererE = 0xD8C162AE765F717CULL; std::uint64_t aWandererF = 0xF00CC7DB688FBFC0ULL; std::uint64_t aWandererG = 0xF9AEE34E06CED5F3ULL; std::uint64_t aWandererH = 0xB80A0E9BC1CEDF53ULL;
    std::uint64_t aWandererI = 0xCA075618BC8D415CULL; std::uint64_t aWandererJ = 0xDFA95C24D8814D43ULL; std::uint64_t aWandererK = 0xD3969B794A8D42E9ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13343438303860307423U;
        aCarry = 12610377144744706493U;
        aWandererA = 11636606397524825256U;
        aWandererB = 17564829217943504107U;
        aWandererC = 13388546239654078844U;
        aWandererD = 11675679575049298994U;
        aWandererE = 17872548137868469499U;
        aWandererF = 14651195771368865258U;
        aWandererG = 13637153148182731767U;
        aWandererH = 12050517589196471902U;
        aWandererI = 11290000698467190364U;
        aWandererJ = 17709536900783417844U;
        aWandererK = 12174251989754026135U;
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
    TwistExpander_Mimosa_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mimosa::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xBFCF1ACB35F9B4E9ULL;
    std::uint64_t aIngress = 0xFE556802DAC9DC9DULL;
    std::uint64_t aCarry = 0xA7967C762B2BCEECULL;

    std::uint64_t aWandererA = 0xFB8B0B04F0454D5EULL;
    std::uint64_t aWandererB = 0xA68DAA3C4AF0643FULL;
    std::uint64_t aWandererC = 0xD6DCE15998CFD8E7ULL;
    std::uint64_t aWandererD = 0xBB3B3C202A135E12ULL;
    std::uint64_t aWandererE = 0xAF218C1416BA1E38ULL;
    std::uint64_t aWandererF = 0x92860613A8EDC663ULL;
    std::uint64_t aWandererG = 0xBF5D09AA304C2D66ULL;
    std::uint64_t aWandererH = 0x8FDA025DF9D7E1BAULL;
    std::uint64_t aWandererI = 0xCFE4D657C8AFA699ULL;
    std::uint64_t aWandererJ = 0x82B81713800024A6ULL;
    std::uint64_t aWandererK = 0x9DC2ACB9F7DBB018ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneA, 1);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneC, 2);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneA, 5);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneC, 6);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    TwistExpander_Mimosa_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 19 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1794 / 1984 (90.42%)
// Total distance from earlier candidates: 32722
void TwistExpander_Mimosa::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1511U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 973U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 447U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1565U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1310U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1993U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 590U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1510U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 378U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1652U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 928U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 395U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 875U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 358U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1574U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1115U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 481U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1127U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 276U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 635U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 478U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 200U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 163U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 936U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1405U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 113U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 787U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 44U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 485U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 659U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1273U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 902U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1515U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1282U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1343U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1689U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1712U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1855U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 138U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1278U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 719U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1371U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1711U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 632U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1076U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1829U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 729U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1145U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1355U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 624U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 643U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 778U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1631U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1747U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1500U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 147U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 89U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2026U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 353U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 982U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 300U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 683U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 487U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1093U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 556U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 647U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 95U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 925U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 611U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 233U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 929U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 482U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 322U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 107U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1550U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 926U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 185U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 75U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1925U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 193U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1232U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 139U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1675U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1820U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1863U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1473U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 604U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 992U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 90U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 403U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 145U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1544U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1876U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 463U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1116U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1769U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 448U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1206U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1430U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1385U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1774U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1176U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2015U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1193U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1275U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 910U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1258U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 473U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 786U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 170U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 327U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 660U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1337U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 204U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 918U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1920U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 699U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1676U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1471U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1982U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 267U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 741U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1923U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 944U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1311U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1381U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 978U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 35U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Mimosa::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x9A8F175D0C2F160EULL; std::uint64_t aIngress = 0x9E835587F72DD843ULL; std::uint64_t aCarry = 0x80D9ED29D6BD7E19ULL;

    std::uint64_t aWandererA = 0xD7A458F9497809DCULL; std::uint64_t aWandererB = 0xBC69CAD86A0C5EB5ULL; std::uint64_t aWandererC = 0xCEADA56D12FE73E3ULL; std::uint64_t aWandererD = 0xBE1BDAE8F0B4EEF7ULL;
    std::uint64_t aWandererE = 0xDFCCAB168E7869A7ULL; std::uint64_t aWandererF = 0xCA9B78226619C98EULL; std::uint64_t aWandererG = 0xAA228662468C7379ULL; std::uint64_t aWandererH = 0xBD2A0B6CCED963C6ULL;
    std::uint64_t aWandererI = 0xAE43E46D032640FCULL; std::uint64_t aWandererJ = 0xE77BB6E787811599ULL; std::uint64_t aWandererK = 0xA27C56F176387413ULL;

    // [seed]
        aPrevious = 12187082470340791238U;
        aCarry = 18310257930029669024U;
        aWandererA = 14393987432244072672U;
        aWandererB = 15380275587390756408U;
        aWandererC = 18164286055812054365U;
        aWandererD = 14141922549799409544U;
        aWandererE = 18081362572013389043U;
        aWandererF = 12338764840419356390U;
        aWandererG = 11643312048246803143U;
        aWandererH = 10577457896844086445U;
        aWandererI = 18284416078029186867U;
        aWandererJ = 15502530329799175098U;
        aWandererK = 12224953827791017475U;
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
    TwistExpander_Mimosa_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 19 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9815; nearest pair: 487 / 674
void TwistExpander_Mimosa::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3698U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5865U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2451U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4319U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4191U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8144U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8040U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1584U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5829U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 499U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7167U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4508U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 8015U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8138U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1148U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 301U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1958U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 342U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1718U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 593U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 604U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 897U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 395U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 407U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1459U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 652U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1997U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1983U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1526U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1907U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 900U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 248U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1822U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1591U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 92U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1734U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 19 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9794; nearest pair: 451 / 674
void TwistExpander_Mimosa::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6848U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1786U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2103U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3997U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6525U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2927U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1476U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2547U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5580U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7580U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5153U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5893U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6167U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1477U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1668U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1519U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 425U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 755U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 147U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1869U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1516U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 914U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1842U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1186U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 785U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 595U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 10U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1057U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1797U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1043U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1001U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1368U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1334U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 7U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 860U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1721U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseASalts = {
    {
        {
            0x2A44248EF372DC9DULL, 0x6E806AA3E5AEA3FBULL, 0x99593CCAA6DF093EULL, 0x83EDC48289D35710ULL, 
            0x099C593F72B7C035ULL, 0x726CBF694F15EED6ULL, 0xFF39824DCAA07ACCULL, 0x600CAE2293A1E497ULL, 
            0x3F72E0A972E8BEE8ULL, 0x92F2F429CF9A7CC8ULL, 0xC0235F6CC8009F80ULL, 0x9A9ECD40045C02DEULL, 
            0x8AE1B00AB08E6164ULL, 0x8E1C95F8A0FA7DCBULL, 0x8B93BDC6E6B4474DULL, 0x103F5FD6B0886925ULL, 
            0xF31F701C740A52D0ULL, 0x14F21E1F972B3B84ULL, 0xABCA32B15CEACA47ULL, 0xD66F892B1DAD23D7ULL, 
            0x922191111BCF187BULL, 0xC2B2C1D90AB4B5ECULL, 0x780D548CD7C6D4C2ULL, 0x8C140AC9587FB848ULL, 
            0xEBD22052F53FBA0CULL, 0x806C1B0B61C87093ULL, 0x72265C924D976086ULL, 0xF00A2400399D2FD5ULL, 
            0x125D36CC7E3DF6D3ULL, 0xBAAAD2A0556BF7BDULL, 0xD303C754377BAA2EULL, 0x29E9241BB1AA21DBULL
        },
        {
            0xA3B069F3A979982CULL, 0x6166E1E7A5DCE6F8ULL, 0xAD21A1075C7279F7ULL, 0x4678152F91BA8968ULL, 
            0x63C14CD4E55B5337ULL, 0xE8B5E5678F2077A6ULL, 0x6C31679F126A9761ULL, 0x00C087B0E8A51B60ULL, 
            0x67F8FC7719519CECULL, 0x147F12FAC3F8E490ULL, 0xCBA843A0BAAC95D2ULL, 0x381948E8248CA69EULL, 
            0xEA29F19ECE8BB410ULL, 0x67B360FCEE4CEB06ULL, 0xE379ACE84BF41EEFULL, 0xEADAB4526D34095CULL, 
            0x5310FDABAE4D68C8ULL, 0xEBDF089AC6DB25B2ULL, 0xE771316379DA5943ULL, 0xAB77068DE88EEF82ULL, 
            0x0BBA8D2BFD12009AULL, 0xA224C298026D1444ULL, 0xD0608E04268F4DA4ULL, 0xEBD271E01EAE0FD0ULL, 
            0xBFBFD80FB40FAB64ULL, 0x79A6161AB39F4340ULL, 0x0B728C048777CFDEULL, 0x7723C1DD6C26C42FULL, 
            0x2A449827C582C70EULL, 0x336342D76AA76B11ULL, 0x024B283422A212E2ULL, 0x956E7645303F1EC9ULL
        },
        {
            0x3DE27C96CE25CDFDULL, 0xB0332A9EFA258C74ULL, 0x66B47E90278725B9ULL, 0xF849CC901EAA40DEULL, 
            0xF7A7684C695C5A1CULL, 0x9DD89191F14A9154ULL, 0x377C9DAF4FEB0E1DULL, 0x170DE4597F6E3ECBULL, 
            0x70A4CFE0C61F107EULL, 0xD2E4E5ABFCCD0872ULL, 0x11252F4378D4D69EULL, 0xB408412B5CB2E5AEULL, 
            0xDCD4F75D1AFF84B6ULL, 0x9D51B0204719ABEEULL, 0x8AE7899C2CDDCB32ULL, 0x78373A4C2CE509B2ULL, 
            0x150B4EEFF6686685ULL, 0x82C995B72BF56ED0ULL, 0x684B42CE7C33151AULL, 0xFE920C5ECA165A04ULL, 
            0x13FE164F61290A5AULL, 0x7305E91E813E2F17ULL, 0x2F8FB0361838DFCCULL, 0xC1FA5AE50298984CULL, 
            0x95FFFA5A249637BDULL, 0xD371AB88C485CABEULL, 0x1C4C603703B28CAFULL, 0x9E5EF9E77ADE8B99ULL, 
            0x80E6367AA0BB5D54ULL, 0x26A672AB12CE83A8ULL, 0x9B9763B6EE171644ULL, 0x12B375946A3F8C96ULL
        },
        {
            0x63DE98D6C9FBEEB6ULL, 0x73FC783E2EF5D2DAULL, 0x57CEEA3B9890A60CULL, 0xCAECE266DF054D0FULL, 
            0xAC5545DE60FF21B0ULL, 0xFA6146DAB804B66DULL, 0x0E6AD2CA4A4052EDULL, 0xE0545F773C9D7A54ULL, 
            0x1285BAD94E086CFBULL, 0x5FF02E534AD9F61BULL, 0xF5AA710A0013CEABULL, 0x8C86BF84BE66FBB8ULL, 
            0xBD18BACC75BC8E8DULL, 0x2BB79705BA9A9ED6ULL, 0x22A4A21F590E8348ULL, 0xFE47F28502BBCB2AULL, 
            0xCFD4CAD4D4ACDA00ULL, 0x59CD824E00D5ECF2ULL, 0xA4DC5DAA3BB99B5CULL, 0x08C69C8079E24066ULL, 
            0x0AAC00009DFE4FD3ULL, 0xA9E0DF3CF5FF35D5ULL, 0x938EFB62D9BF1151ULL, 0x36D3383E0C728C0BULL, 
            0xB951C55F7C9404D1ULL, 0xEAF180D0F75ACCDCULL, 0xD9E1A6B0BC9EAFC9ULL, 0xD7ADD087940433F2ULL, 
            0x3DA8097DAC5638E0ULL, 0xBCD0B50FD93EC8F8ULL, 0x8E1AFCFFE19749D1ULL, 0x523DDDEB40F7E188ULL
        },
        {
            0x0369FCD47FE3B6EBULL, 0xC5A3CE86766B131BULL, 0xFB4A7F31AB423F1DULL, 0xEEC365E659BD7C93ULL, 
            0xE039DE22E9E13A8BULL, 0x6D1A9D49D7038444ULL, 0x61FB5DE9A7C2A3CEULL, 0xE4BCD71988E5E637ULL, 
            0x113C1C17251BBABCULL, 0xDC9388499224FAEFULL, 0xDACC296348BDB59AULL, 0x3857BD95908A7189ULL, 
            0x28A62FA75CB5DBA3ULL, 0x2B29EA1BDBCD70ADULL, 0x979E4C86F00BEE80ULL, 0x66397055A1CFA52FULL, 
            0x55C8A0D4B8CB0B04ULL, 0x54E45552A7164978ULL, 0xB37F5863E1F86E4AULL, 0xEAA2A057DDFBE521ULL, 
            0x2DD3DEB4889C4722ULL, 0xE42CC61B05A188E9ULL, 0xE8599613FBF95BF6ULL, 0x0D0C49F9A5E44D42ULL, 
            0xA3019C6B4348FA04ULL, 0xEEE18864E3C9F0C3ULL, 0x8B22B0EC61AE8292ULL, 0x55657A3B5FF03988ULL, 
            0x79AAB285763160E8ULL, 0xBE96C267FD9348DBULL, 0xBCF83219AF6806FAULL, 0xC37446A0BF4416A1ULL
        },
        {
            0x1ECAE0211FB8ADFAULL, 0xAC1589620B33E15CULL, 0x553006F2E12A1B39ULL, 0xF2210AE92B1BBDCDULL, 
            0xF9D5AD5AF7D68802ULL, 0xF03DE28AE5B4898DULL, 0xD4EBE756F1A61610ULL, 0x6961E56C8F6CE05EULL, 
            0xAED92519CBE8EC1CULL, 0xD9270C7EDCB33768ULL, 0xA6AA8B84C081CD51ULL, 0x031F14F50363DD39ULL, 
            0x3EDCE664D8435A95ULL, 0xA7A2A68FF0CE9036ULL, 0x05AED4681E4DBACBULL, 0x9159292C2CB3C441ULL, 
            0x8287C7CF26C4CD21ULL, 0x199D0AF6D422B1C6ULL, 0x3FC1903083EB22C8ULL, 0xF122A2D4228823C4ULL, 
            0x7E83037F93ACC5EFULL, 0x74CE9D64A2B56647ULL, 0xC5943306F20E94A5ULL, 0xBB2D848E4E7E3A6EULL, 
            0xD9C1687A22A18D53ULL, 0x66D513DB70DE0292ULL, 0x4193AF5AC9D3BB22ULL, 0xBC073C37B7673C74ULL, 
            0x4452286111B64E31ULL, 0x512EAF8CF2F72C05ULL, 0x50C68ECED22F54A1ULL, 0x3DCFCEFE8D397C94ULL
        }
    },
    {
        {
            0x714E2B524CA798B4ULL, 0x0480EA77316A30B4ULL, 0x9B626FEF51F14AC1ULL, 0xE2640E0542E89ADBULL, 
            0xE4959341D1958466ULL, 0x06FFB49AE91A494CULL, 0x60E0B86FB5615E58ULL, 0xA3AC19ABF13E1409ULL, 
            0x55F2193C1BDE7F2EULL, 0x14FEE98552491437ULL, 0x03930CADDF904DC7ULL, 0x460CEC9C93201591ULL, 
            0xAEDD8475A9D0CFE1ULL, 0x0F38C5BF8D7B4909ULL, 0x1D1AD214E25FC22FULL, 0x0765047EE2BB1184ULL, 
            0xA6B14C85ABE5B9ADULL, 0xA2CEBBA853EFFF56ULL, 0xC500964762EF2FE9ULL, 0xBA5CBEB0AF12E169ULL, 
            0x0E85EED1E73DDC86ULL, 0x0E3350CFFA8AD433ULL, 0xB1FB28C25E43F7ABULL, 0x838A1CF75E836A3EULL, 
            0x096136E18E5471ADULL, 0x072EBA10CF7C3D83ULL, 0x379F67980693A688ULL, 0x73438BF797CFF1AEULL, 
            0xB6E970AEFB3CE76AULL, 0x9DEF0F74E1E85760ULL, 0x33376F9AD071B56BULL, 0xD53F089DE1360C95ULL
        },
        {
            0x8199FED60299D0F3ULL, 0x3179A78CD69E6210ULL, 0x53FE7EF7DDB82A41ULL, 0x3118394DE482990BULL, 
            0x4CCAF159DD30EC40ULL, 0x8601FCFAF21C1A95ULL, 0x4A66DB62E9096B6CULL, 0x38D32754A1945E12ULL, 
            0x91C944A091864F51ULL, 0x741E9B0D32C18448ULL, 0x2E81A7075B7A3D9BULL, 0xE5FD5D12340789E6ULL, 
            0x708E638BA35BB798ULL, 0x0A81D6AE95A34B4AULL, 0x3AD546CD3DD3A710ULL, 0x3C10C17DB1A2AF99ULL, 
            0x155EB5AA839B2AEAULL, 0xBA08D2004B3E7374ULL, 0xF43E5643219F94EEULL, 0xDD2C4B9DB9AFD728ULL, 
            0xD6F2E8C91669F8BFULL, 0xAD7846AC5550E734ULL, 0x52CB4C3CF5703B08ULL, 0x7BFC787615FBD32BULL, 
            0x46CCC28EF58E01EDULL, 0x63A7A01BA9C78D89ULL, 0x77ECD32D59E42CDDULL, 0xF41923B88CFE7C50ULL, 
            0xE212390F21E1C373ULL, 0x05615CAB787A2BCAULL, 0xED6B3B4FC18B6FE3ULL, 0x677F28686BEC1817ULL
        },
        {
            0xA6287442EE6D2918ULL, 0xD0E71442A5D1A4BBULL, 0x7259C2B4D1855B4EULL, 0x465D380B5879DDFEULL, 
            0xA708EC6EAFCC8EFCULL, 0xE3C2FCC97F93FB5AULL, 0x3A39DDFB4ACFE47BULL, 0x92FA2C267C1954CDULL, 
            0x75716106086B90F2ULL, 0xEF0E1716610D06D6ULL, 0xDB4E2FDD6A3D1797ULL, 0x769CFDEF7AFD35F6ULL, 
            0x3E4A63525EFC4021ULL, 0x00F48470D6E56867ULL, 0x53CE80016E8F5A41ULL, 0x05CB1C2155F402CFULL, 
            0x8AF56AADD01B90F0ULL, 0xB61639D637C1CC30ULL, 0x33F9DF07F5BF0838ULL, 0x2CC7274A9EF72D50ULL, 
            0x5B209B9E7051A313ULL, 0x7CC0A7EB5FCD46ABULL, 0x1BEAC69DDD6B6DD7ULL, 0x4A770835D06FD0E5ULL, 
            0x8E988C87545A06BBULL, 0xC17F7F4B4BD0D5D1ULL, 0xBD511901335ACB89ULL, 0x7705819E1574CC7FULL, 
            0x7831A1B05F672AE7ULL, 0xD5739A12215E98CAULL, 0x3DF27F9DEC633640ULL, 0xDD0CEA1E24A787A4ULL
        },
        {
            0x6F8C23D0C6C5D30CULL, 0xFD67D7CF81810584ULL, 0xFC79BFC2C6F90673ULL, 0xC0B1F8A7F82E9564ULL, 
            0x077FC24549F23FA6ULL, 0x54DD93B9AF96A282ULL, 0x0AA4C5E7051BA695ULL, 0x32E83CAEA2C52924ULL, 
            0x37A8CF06D3470CB1ULL, 0xF49A3073A3AB1D95ULL, 0xFAC7D54BD24A4658ULL, 0xB0CD138D3BF0958FULL, 
            0x7CBC1C081BED50FBULL, 0xB2C81F02DCA2277DULL, 0x8A7CBAD386B0875CULL, 0x365B25DE622587EFULL, 
            0x585222422B73B956ULL, 0x2A9C1DFCFBD2CBDBULL, 0x5C6CC0A0EAACC041ULL, 0x098206A06013C526ULL, 
            0xA207452FE502CDA5ULL, 0xB2AD7C6880FAC157ULL, 0x67771D20D60402BFULL, 0x31D9B829D62D96B2ULL, 
            0x457663B2B6170B8DULL, 0x067A3C0898FCA3ADULL, 0x4778569C94C9822FULL, 0xE54F41A0B3B2E613ULL, 
            0xD04F3221E273032CULL, 0x5C9B888C6BAA2711ULL, 0xD0BF217D57E11B88ULL, 0x03EF57C19445E4B6ULL
        },
        {
            0x2358DBD485887F6DULL, 0x02EBFC5251AE8E35ULL, 0x8FF8E8222AD892E6ULL, 0x71C7EBAD3D558932ULL, 
            0xDD480F52451BE475ULL, 0x0B3FBF08E87B1DA7ULL, 0xF9D6C5BA43337604ULL, 0xE23B82D3A658339AULL, 
            0xAB36178C6311A486ULL, 0x4D6B85F8BEE8817CULL, 0xD0D9183979CD6BBAULL, 0xAFF2A20BABD815A3ULL, 
            0x0B9BFCCBECEB2862ULL, 0x4D5B5079117118BEULL, 0x341F27AFF1576F5CULL, 0x200E21B855D20F3BULL, 
            0x68ED3AF206CCF2FFULL, 0x01D94318D31CC4ACULL, 0xAB03032EEFBB340EULL, 0x0E6D139C29D58C08ULL, 
            0xD80AA40E7183FBD2ULL, 0x9376678632721E27ULL, 0xE2572F1631E5D44DULL, 0xBAF7C45FEC614627ULL, 
            0xB363DD3F2EF1A245ULL, 0x902529F993B7C2D9ULL, 0x2F73D79F66E735A4ULL, 0x58E9A5D1A94A91D7ULL, 
            0x008E10A3B9EFD686ULL, 0x5A564147CC211EA4ULL, 0x059966964AC54DF4ULL, 0x77D5249BC21A1EB9ULL
        },
        {
            0x29ADE8DCEBE36A61ULL, 0x81CD31F921D58408ULL, 0x2BB2B6AA3951F88CULL, 0x41013A69C2DFAD84ULL, 
            0x2F7B4461D51CE133ULL, 0x491F9F95EF0CE168ULL, 0x819CAF5C9CC2E895ULL, 0x2E0E67BC5E48B84BULL, 
            0x6D7E340C266AD521ULL, 0x614539762DE18BF1ULL, 0xB0D58E1CDF3F1473ULL, 0xE0B83B325AE4A9AFULL, 
            0x9D9BF7C14828F3C9ULL, 0x9F3B883948F34F4CULL, 0x446F775A08350C43ULL, 0xC54E20AC3ABB8768ULL, 
            0x54F357C7ADE17127ULL, 0x45E06555890CB79FULL, 0x52C24CA685C16165ULL, 0x7D5BD7988518EF22ULL, 
            0xA502A2B51AABE729ULL, 0xDB0712C2316BD4E9ULL, 0x3DF0A62AEBBA4019ULL, 0x528585F053CD02D3ULL, 
            0xDD9769352E84C6D9ULL, 0x61F71BA7568F6A0BULL, 0xFBC7A9E8B3CF7679ULL, 0x0F5149D6E0C0ABB4ULL, 
            0x69DE92A5F4DF9E01ULL, 0x14483FA978E0053BULL, 0x788FEF680B90179DULL, 0x2D951C0F1E84A2D0ULL
        }
    },
    {
        {
            0xF6DCBA70FBE4F3F2ULL, 0xF66233A1E6E775ADULL, 0x8DCB64F94B6D865AULL, 0x12D003A99A78C334ULL, 
            0x22731F0717799582ULL, 0x1DEB6493EDFB8EB5ULL, 0x48C6E8095487BF35ULL, 0xB7FDC2F52D40AFEAULL, 
            0x521C72F476F105A6ULL, 0x8C789D112206DC78ULL, 0x56DD7A928AB812D3ULL, 0x22612D6E2BA5750BULL, 
            0xC2B4A5A138D20962ULL, 0x1BAE2A99ABF7161CULL, 0xC03309B452632262ULL, 0x65695FFF06A09F1CULL, 
            0x4045CCDEEC473EC1ULL, 0x6CE6D9AB99A98FEAULL, 0xD4DC404FD98B2471ULL, 0x0222033D4271144EULL, 
            0x048FB34E98FF378DULL, 0xB496DE75207E7102ULL, 0xCC3DC771FF47EC58ULL, 0xD8C6233A79A0F996ULL, 
            0xC80D21133233EC9EULL, 0xE5D82635AD5A55D6ULL, 0xEDC6AE8604676B6AULL, 0xBC115BFC874E2C88ULL, 
            0x3DFA67562724C083ULL, 0xAE4FC53BC37797E4ULL, 0xAFFC29D151B5B1ABULL, 0xDE01EC0F7A62CB3FULL
        },
        {
            0x91CA22EA99FF3DC2ULL, 0x7DBC68FE92D8DB12ULL, 0x33FB9C743B145690ULL, 0xC5D0E596EA6A2202ULL, 
            0x2E73C044F79D2F85ULL, 0x86172DABA7043AECULL, 0xF0C80E4E28C62742ULL, 0xA805F73F61C3FF82ULL, 
            0xA90348622D3619F0ULL, 0x344BD7987CD09E0AULL, 0x604046DE9B68F27AULL, 0xF02A6E807EB3E4E2ULL, 
            0x986030C81C62E642ULL, 0x735CD0DB009CF2C1ULL, 0xC51E3B3DE1EFE147ULL, 0x6B9CBA1ECBD610B0ULL, 
            0xF4FDD2DB14A79BCEULL, 0x3D1ED7F7089CB161ULL, 0xE9EEEE6511B5502FULL, 0x71698677742B4356ULL, 
            0x1A51F008F46614B5ULL, 0x9CD2224060DCE05CULL, 0x38022DC127E7951BULL, 0x7231CFF5B4A368BDULL, 
            0xD3FF55C694FE5D38ULL, 0x29B1B66304359A2DULL, 0x23595BF5556E0CA7ULL, 0xD3298F42930BE49CULL, 
            0x332F52495BD7C456ULL, 0xB6A97F1483A860CBULL, 0x122EDB585CCBDC87ULL, 0x5415BF510D19C303ULL
        },
        {
            0xF8D725A586C45D93ULL, 0x46A3E899F913CE68ULL, 0xDBC5603BD3DCA881ULL, 0x638CCDA2A0363E4FULL, 
            0xC93C66502B5A1EA7ULL, 0x496AF1A49B1C9B11ULL, 0xFF0F1C49C9638B84ULL, 0x7DC3B21298607672ULL, 
            0x3E710FD13B37E51EULL, 0x7A2A613BEF2E6471ULL, 0xB378E2F9AA8D47C8ULL, 0xF8B14E541185FA81ULL, 
            0x6BA20E1991061F4AULL, 0xE6E7B590BE536583ULL, 0x2795FC5A6D8F851CULL, 0xC27703BC0A4ABF58ULL, 
            0x34B1D36D7363107AULL, 0x41368CACDA1214ABULL, 0xC1B6ABE1A297CC44ULL, 0x22392A215963A99CULL, 
            0x459E968CD7B2D06AULL, 0xAD276861195E8E27ULL, 0x2A2095A1090DE6E3ULL, 0x1FD0D4D8F064E8EFULL, 
            0xF5284AC87F61C303ULL, 0xD408DB659473F3BEULL, 0x1FFCD776FDFFE421ULL, 0xF20433CDEC215A18ULL, 
            0x8B7AC53446A322A1ULL, 0xC9CA6B4A49E8FA91ULL, 0xB05305D356AA4192ULL, 0x3144B8A4172F58E1ULL
        },
        {
            0x6FE0C245B2D8522DULL, 0xAB6B2C7121C55F26ULL, 0xAAB56E1CB5E31DC9ULL, 0xC28A63747552368CULL, 
            0x1334F60CA9BD2985ULL, 0xE84EE26578DF7086ULL, 0xA30F16C6AB9329B8ULL, 0xD9C93C601A1A529EULL, 
            0xBEB40EEBAEA24765ULL, 0xCCFCD696598C7083ULL, 0x8CC3D5323B31356BULL, 0x2993CCA8B277F3AEULL, 
            0x1846005ADEC549A9ULL, 0x5C80E5FC6E887303ULL, 0xEE121E35CD185A8BULL, 0xA49A0A2B6B1FE348ULL, 
            0xD9A96B87E9AE0DA7ULL, 0xDB670405D2171033ULL, 0xDE2FD57FE5B74A09ULL, 0x397B11495EC255F2ULL, 
            0xB7182D78A2E835F1ULL, 0x16DA2C669FDA67D3ULL, 0x0D782F6A851D5D02ULL, 0x7BA191A499644EAFULL, 
            0x20EE2C79E24D7F10ULL, 0x927D8ABD3E771FC7ULL, 0x6DF357A9BBDFCF7CULL, 0xE1A5A6B74FBC80ECULL, 
            0xC7E817EB4819E7A7ULL, 0xFFCFBC6D47511158ULL, 0x3566327D506212AEULL, 0x45AA950F8AB7C722ULL
        },
        {
            0x7C491FF998144773ULL, 0x3E19D6BD80419546ULL, 0x61BE6BAF8D91822AULL, 0x8AB1CED21F48006CULL, 
            0xFDB33D31830D8257ULL, 0x8EAD98E3170DB9A1ULL, 0x0CB1AFF8D682AD05ULL, 0xBF4CF42F9166CA73ULL, 
            0x89D444A731E71E8FULL, 0x329224AEF5C53ADAULL, 0xD528D8397FDB6AF2ULL, 0x009945D164C61D47ULL, 
            0x93787BA317D2E135ULL, 0xE5944455DCFA257DULL, 0xB1D45CA0BB8216ECULL, 0x6D8B9DDA397C7F04ULL, 
            0x30B517E5493BACFFULL, 0xD2B0AD7920050117ULL, 0xA8C4BEAD23288A51ULL, 0x96E2A1AA41766135ULL, 
            0x07DBD01170C56457ULL, 0x6BF9A2E1E436530FULL, 0x5D8022170BF7229BULL, 0x5316CC89459F7C49ULL, 
            0x956AED3963633011ULL, 0x6CDA720A5EE6BF61ULL, 0x6965901BA8BA9FE7ULL, 0xCACC112F61EAC4FBULL, 
            0x7C5061CC3F44B778ULL, 0x10C4504581610794ULL, 0x622E1D076AD8444BULL, 0xED0BA28C62CE8DBEULL
        },
        {
            0x003134E5C053A9E2ULL, 0x816D6346CE06E0E0ULL, 0x25948F1D51A99288ULL, 0xD6667D7A9D7C4848ULL, 
            0x9CF74D40A3F86959ULL, 0x1456A78F0FD998AEULL, 0xAAB32BB5F9739DB4ULL, 0xD336784C7F55EE92ULL, 
            0xA3F65E1602366062ULL, 0x01A545224A11077BULL, 0xD73E948139BCA2A5ULL, 0xA89838F38783B402ULL, 
            0x7009046C231F9EE6ULL, 0x34BCD1C58769829FULL, 0xE7C51DD46129A911ULL, 0xEAFCCC4F2908F272ULL, 
            0x8BBD9AFE459EB159ULL, 0xF00CFA339C3205AAULL, 0x9008FD6068C07A2AULL, 0x5D4251103FBA965DULL, 
            0x975C27A0928A4BB8ULL, 0xED2394C42B203D7BULL, 0x37F3169B130CDD8AULL, 0x109F4E6C10202DCFULL, 
            0x1C6D2955026BED8FULL, 0x1DC2DAE273062497ULL, 0xEC5B5FFB2F1A1083ULL, 0xBBB6BDEFAE51C646ULL, 
            0xEFE6EF7B98552B8EULL, 0x77EFEFEF7A86094EULL, 0xA64EB92B2FFA91B4ULL, 0xB6B84CD89AA073FFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseAConstants = {
    0x8C31B24A16E52959ULL,
    0x57CF6D6961E7EC1FULL,
    0x5296A99DA2FFCA41ULL,
    0x8C31B24A16E52959ULL,
    0x57CF6D6961E7EC1FULL,
    0x5296A99DA2FFCA41ULL,
    0x305E403C9F663F5DULL,
    0x18EB0862718B6A33ULL,
    0xA3,
    0xE6,
    0x05,
    0x73,
    0xD1,
    0xD8,
    0x9D,
    0xAE
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseBSalts = {
    {
        {
            0x3A0A2C1B8D73997BULL, 0xA827B2E7C2EEE174ULL, 0x6A40AF64665B92DBULL, 0xD3172947C44DC0B1ULL, 
            0x78A21C05B3E883EAULL, 0xDA2CF9B5DBEF070FULL, 0x107728B5F55ABC90ULL, 0xFB39CEB7921F1AB6ULL, 
            0xC9CE0D75AD5CD7B4ULL, 0x10FE040CEEC0DD77ULL, 0x0B3B13E1A963CBABULL, 0x50F88641CCD8E7C2ULL, 
            0x06C5A98C8E1BA04EULL, 0xD4CDDF8C9111E734ULL, 0x46CF1509FFDA5967ULL, 0x08629A8B0821BBFDULL, 
            0x4C0D904389C5AFA1ULL, 0xED0DD2D6A54F8DFEULL, 0x628752DAE59F6215ULL, 0xBB7E8FBB0B624639ULL, 
            0x145C8C4487806369ULL, 0x3163052C4B6A0904ULL, 0x56D49141A1336DE6ULL, 0xA0CFC6764A12127BULL, 
            0x0E5E6F90F22BC1CBULL, 0x5A89DF8190730C14ULL, 0x67AED98C8A6CF0F3ULL, 0x2F9711AD36FB5412ULL, 
            0x9892EC8D89834F60ULL, 0xBB25CC68FAF1BFA9ULL, 0xBDCFD1B4259C52BCULL, 0xD7E708080BCB6CA8ULL
        },
        {
            0x5426772D531FA682ULL, 0x61D3AD612E40A16FULL, 0xB2CF3C96523BB292ULL, 0xB0937DFB3A842100ULL, 
            0xEA51B73E57C1684FULL, 0x9D80C911A9ADF851ULL, 0xF2C5B96D72809AAAULL, 0xDD383A0502786763ULL, 
            0x7BEF71C812974CB0ULL, 0x1D55C9933D659300ULL, 0x54B618A775977610ULL, 0x4862C3893E51F203ULL, 
            0x5BD0618275157A96ULL, 0xF1C72D0A145D4131ULL, 0xB767D47B14758E70ULL, 0x28E128D6B81425F7ULL, 
            0x53105489F8C7228EULL, 0x7FB5BF5DED40A749ULL, 0xFE1C5EB9680A23A0ULL, 0x0BA968B182D9EFD1ULL, 
            0xA1EAE5F651190092ULL, 0x3882AEFB2C33B525ULL, 0x19E36527D764B71DULL, 0x0A86DA0896FBF905ULL, 
            0x0090E227B786047AULL, 0xD804580E66B953DFULL, 0xAE0693F0F757BFA9ULL, 0x24F9B9A09EBB79A2ULL, 
            0xFD4F961C7080D742ULL, 0xF18DC5290D0A5C62ULL, 0xE1F2CA70572CE9EEULL, 0xF84D3401C64C25EBULL
        },
        {
            0x5B729C744B7D7647ULL, 0xF648D9E37059B109ULL, 0x08A88D294108BFFAULL, 0xA52DA27A362B74C8ULL, 
            0x15C3552302D333A7ULL, 0x28BD71E17FD0A74CULL, 0xB45DFC6C1FD4D42EULL, 0x8C3D2DAD7F794673ULL, 
            0xC90B178834B131C0ULL, 0xB5D5C0F944AAB72BULL, 0x98B071FD408C55DCULL, 0x7B8A69F6FE8B6E6AULL, 
            0xCB3443FA76770223ULL, 0xD63A130705A5861AULL, 0x26B5D996D07BB37EULL, 0xD0D2824A4D4E4397ULL, 
            0x6D62525943C7735BULL, 0xD8AA04001BC9F730ULL, 0x92EB562544FEE550ULL, 0x79AF8DAB0A132B3CULL, 
            0xE7C77DF685EA111EULL, 0xB7C1597C8F91EB5FULL, 0x86DE2F61298621E6ULL, 0x9A46260D6D93D2E9ULL, 
            0xB285F394EE1F76FBULL, 0xE6B5A268E12D0712ULL, 0xE80E54DCF8F89051ULL, 0x0F4BC5CED39E3E79ULL, 
            0x0FDE65DF36FB8EDFULL, 0x6267158230937741ULL, 0xCFBCF5FC81616402ULL, 0xCB34D92FBA21CC82ULL
        },
        {
            0x7D62BD1C14714CF8ULL, 0x23F54AC1D13EB1B0ULL, 0x2CB5C09339F24C08ULL, 0x669A1B00A2DA9DBCULL, 
            0xB9E5453A1D2FC0BAULL, 0x90210DFF20B70F29ULL, 0xE50CF98E21B5F6DFULL, 0x589DF13B66580E8DULL, 
            0xE92CFB464F5DD64FULL, 0x5EB4A698F24F77CFULL, 0x2168E45A9DA9C155ULL, 0xD62E45ABE461D0E2ULL, 
            0x68E1325D5482AA7DULL, 0xDB517A8665CB9109ULL, 0x40D1127C1400C522ULL, 0xE6FCD836FBF19DA4ULL, 
            0xAF2DC5AAEBF4CCF6ULL, 0x6FB56CC453E02CA5ULL, 0xE1F30DD21578E6FDULL, 0x656E851FE2A874E2ULL, 
            0xA9BD4F674AAB78E2ULL, 0x553B398EFC009C88ULL, 0x992AF8C73CB1A4F7ULL, 0x713BF868A6132A32ULL, 
            0x8BF0BB4FBBE027BDULL, 0xD103607733CAC31BULL, 0xD1980BCE75A3C392ULL, 0x8010B3DBEEA5D8BCULL, 
            0x15F0548A3EC578EDULL, 0xC7AF8CF4F8AEEB53ULL, 0xF1EF16427B439BEAULL, 0xDBC1722B2265EBC0ULL
        },
        {
            0xCDF81BE0039F2D8DULL, 0x1BC248B3364AF1AAULL, 0x05AABAC59D531684ULL, 0xA8C9C4226E01B2B7ULL, 
            0x65DC24599A922863ULL, 0x6A5241A897FFEA26ULL, 0xFB2404CD83B211F6ULL, 0x4D2FD10863C612BFULL, 
            0x07258150814BB196ULL, 0x6082022ECFBEC10BULL, 0x7677AE431AA4EA42ULL, 0x3007EDE24A5068DEULL, 
            0xDCED9D28E6770149ULL, 0x573B0BA871F14A9AULL, 0xDF9F93F2F6C61DF3ULL, 0xF77525116FD5C86EULL, 
            0x2996166F9F768B52ULL, 0x195B4957DF25A56AULL, 0xD82D9856C3A419BFULL, 0x2FD2BCF1397C6AE6ULL, 
            0x8A12DB79EED25B61ULL, 0xD3F0884B094F2F66ULL, 0x1FE2824B8765D766ULL, 0xBAC096FF63E9BFCBULL, 
            0xDE65A4C07BA8D642ULL, 0xEA762800EFF44E09ULL, 0xB57C1E5E0CCE5C05ULL, 0x904A14EE328258B6ULL, 
            0x804FE808CF0B3CD1ULL, 0xFCA7E0827F073928ULL, 0xE81FC1031FF86452ULL, 0x0DE862919129C711ULL
        },
        {
            0x7E15119A7F3A52BDULL, 0x67E13E7161BFFDA1ULL, 0xC19E9E9090BE6837ULL, 0xBA2C1FF69B2120F9ULL, 
            0x4692A1ECD9BDDE6CULL, 0x7B93AE3F9FA09B62ULL, 0x751BAC6FD6C89BBBULL, 0xB2B652AB19D7DEFBULL, 
            0x493E9DFF051E5FA7ULL, 0x3E90CDCE1CB057D9ULL, 0xB369A644ADC3E46DULL, 0xCBBB0F0690DA3405ULL, 
            0xAD215C57DB0F4F2CULL, 0x9DB1CE6D2B72A821ULL, 0xDF0C4DDC413BB052ULL, 0xA5AAC3EC21522A88ULL, 
            0x8FFDCBAEB86ABB7BULL, 0x0850F625EA585E87ULL, 0xA167F63EBDD02E84ULL, 0xEF9AE22C472B7D7EULL, 
            0x4BB68C1F791EFB25ULL, 0x87DF772F7E9E8F0FULL, 0xEF3878090709921EULL, 0x4E0D5E47A80B7FD3ULL, 
            0xBF4CD5E859ACE9E3ULL, 0x1B7A129F3FB6550BULL, 0xD856FECE475F5CE4ULL, 0x8FAF4031B6ED9945ULL, 
            0xA8FFC17E99DC2BBCULL, 0xB390F4DA258D6F0FULL, 0xD1CE72B3DC5FCBBCULL, 0x3AC6BD187009B0F8ULL
        }
    },
    {
        {
            0xBFE61EBD0A6EADC5ULL, 0x39362C15C2DFA5D1ULL, 0x558F5CC855BFCFA6ULL, 0x542F43E0C9480D8EULL, 
            0xC32FBF567D020EAFULL, 0x804511978416B2FFULL, 0xF732FDFE8BEA5510ULL, 0xEB7FB83E573931E3ULL, 
            0x2D65DDA1A7A40215ULL, 0x89A2A4052D96F8AFULL, 0x753F5185AF940BDDULL, 0xC1C8F24C9E72DD80ULL, 
            0xB80CB92E62D58CD2ULL, 0xC0003A2B0B5A7CACULL, 0x69BEA2E6FBDD0DF2ULL, 0x386AFE26B2349863ULL, 
            0xC9D9909B775DC5A1ULL, 0x17C236A6431B9AF2ULL, 0xC19EA9EF7344E6A9ULL, 0xBD89F18690D1C066ULL, 
            0x998D7C740F80A74BULL, 0x3E3208B63FDBA7FBULL, 0x603FBCC9BF8E80EBULL, 0x78278454539B85F3ULL, 
            0xC45CB2F1F91241CAULL, 0x0C6679EB55D347A3ULL, 0x488226D308CA5BD4ULL, 0xE6E0435C7876383FULL, 
            0x57004C40755834BDULL, 0x9E49FDA5D55E06E1ULL, 0xA052F06CA3B584BDULL, 0x1342AF3F49229610ULL
        },
        {
            0xC901C42CCA733173ULL, 0x58462D3FFC242E6CULL, 0xC0AC79F3E1653375ULL, 0xFF257020D7B862C4ULL, 
            0xC0E1051A89872AF7ULL, 0x174A77395E86160BULL, 0xE5C71B21304ABBE4ULL, 0x96213CC1050F8134ULL, 
            0x9D65E169E68406E8ULL, 0x975D888AC05C1748ULL, 0x79E6B1BA24F908C0ULL, 0x25E503A96605A1E3ULL, 
            0xB33A2846AAC76951ULL, 0x30FBC3AFADCDC135ULL, 0x4D2DA0C5CFC61891ULL, 0x95724349B4F7F91AULL, 
            0x716A3E9C98F18730ULL, 0x9635B8914708CA6FULL, 0xADD0F6E4A26D4DCBULL, 0xB23BCF101C652E87ULL, 
            0x7A4D327CC22E61E6ULL, 0xFD3160C30E861453ULL, 0xD3DF56AF1654C289ULL, 0xA123CCB39DBA1B81ULL, 
            0xCDE24B4E082F86E8ULL, 0xCCDC7854443AC5DCULL, 0x34829D621BBD901FULL, 0x90CA4962D6C22E13ULL, 
            0xB852C3B216FBC6B2ULL, 0x981FEEDED6476226ULL, 0x3F13C83D8F03FC42ULL, 0x671C513FA2CB6ADCULL
        },
        {
            0xD8EEF48A5AA71E6DULL, 0x516CC8B6485EF697ULL, 0xE1027CDBEC007473ULL, 0x65EB11BBB34552B0ULL, 
            0xB6A93D9A9803B23BULL, 0x718562F14E59E8DBULL, 0x7165F5816F8361C6ULL, 0x4BF4EA8D8594B497ULL, 
            0x657CEB16AA657EACULL, 0x5F41D108C35DA9CCULL, 0xC798966DF9805C05ULL, 0xBF72AD9C6DB08494ULL, 
            0x04019853DB4EE8D6ULL, 0x02073B2667A3D9A7ULL, 0xE78E0539B472E7FCULL, 0xB3C0F89DE2080FFDULL, 
            0xC0E3D676345E057CULL, 0x9453286A2D29E731ULL, 0xECA9794A30A3D8C4ULL, 0xC8C3A780605E72BFULL, 
            0xE35330BF7521ADE4ULL, 0x9441FD00C4FFAE97ULL, 0x2AA7D1198AA3DDBCULL, 0xC15145CD7D06BAE8ULL, 
            0xEABABC89483C98EEULL, 0x09558A445A4DC6A0ULL, 0x3313976495B2B3ABULL, 0x349B42CF32F621D0ULL, 
            0x4F63D044A3AA59F1ULL, 0xC806B6C153BB71CDULL, 0xD65958A4A2D46259ULL, 0x5B2ADAC97245B498ULL
        },
        {
            0x63465189AFD0A106ULL, 0x5AD8C4CE5FBFA3AEULL, 0xBCFE11FBB3B3961EULL, 0xEFB9EE92A2784D72ULL, 
            0x5E053D1449926F38ULL, 0xD2EEB191EC291F48ULL, 0xB272D1BF0FBE4F3FULL, 0x9F47FCB85188BD2EULL, 
            0x3D9369ED9C735F23ULL, 0x3D3FEB9157E0B0E3ULL, 0x86C18A24BBC62F26ULL, 0x4F5BA206FD27477FULL, 
            0x7069D5EFA7543A9BULL, 0x2BE3A119F651484AULL, 0x99162E117958FC0CULL, 0x35C264E2C7036B8CULL, 
            0x7E89B50CA8666256ULL, 0x7E89B00FD6B06B16ULL, 0xAA36433A48D387ABULL, 0xF4DC3585C28062AEULL, 
            0x84EC96C01317DAADULL, 0xEB6E28FB75820FF2ULL, 0xB6A5DC727447A6B4ULL, 0xDEEF18AD00F8EE91ULL, 
            0xF04667E0C511AAECULL, 0x9F8BA59DB91A5FF1ULL, 0xDFBA715BB040D898ULL, 0x27CF61D049EFD0EAULL, 
            0x5ABA439290B07871ULL, 0xB3EDD7B00385300DULL, 0xA8396E152448CB52ULL, 0xA85E757497CC984BULL
        },
        {
            0x9188EC95DFD32C1FULL, 0xDF44B9FDD2EF16E7ULL, 0x8C9D723B9B59FFB0ULL, 0x342E7B9C4D327988ULL, 
            0x86ED3B3986025776ULL, 0x98EFD8B67E387D4AULL, 0x4FDD377C2871B3F1ULL, 0x6027184743B46349ULL, 
            0x6B55C24784D70023ULL, 0xA079047BC8E91F03ULL, 0x30E952B6FC045600ULL, 0x325F47B24DF7D73EULL, 
            0xF4EA32C682BE9E6EULL, 0xD1A003085B7B9BE4ULL, 0x3ADC3EA793069000ULL, 0xA4BE84A4A484D75AULL, 
            0x537D8485229B0001ULL, 0x969F7B91A21804E1ULL, 0xA4D3F79F82712F46ULL, 0x21AE7CA6F7BEEAAEULL, 
            0x3F7DD313D550DBB2ULL, 0xDFF9CF76AD3C1FF2ULL, 0xA22EB43F4C1876D3ULL, 0xFAE81B187FD02A63ULL, 
            0xA50035CD2381B82EULL, 0x9BB62EE12F57E813ULL, 0xE3118300B77D52C0ULL, 0xB247313D1EA40021ULL, 
            0x61E49F7F06925E52ULL, 0x38B6F8EDE3973560ULL, 0x70EE641B052B1C54ULL, 0xEBA2565A1FDC1418ULL
        },
        {
            0xC27BA3BAE89B4BA7ULL, 0xF897F143FCB17BBFULL, 0x1143E6EB4F5477A8ULL, 0xDC138C768A61D576ULL, 
            0x79CB6DC2AF2B6C74ULL, 0xA4F9607CF918CEEFULL, 0xA0E2530B774908D2ULL, 0x0FE73D9554AA3D90ULL, 
            0x354F0EF021FDA64CULL, 0xAEC1DA968462361CULL, 0xC2CCEEC9B66ADCDFULL, 0x16086BFD02131FE7ULL, 
            0x192376E30EC8F205ULL, 0x5A0B7A00816C6789ULL, 0xF01FE7387258EC7AULL, 0x53A7D29CB7A43E00ULL, 
            0x2559A76CF64757ACULL, 0xDD8FEE145DE12793ULL, 0x1393D94902CD6406ULL, 0xE764162B8B04667DULL, 
            0x229A88E49D0F6FA7ULL, 0xEDC8E6295CC8C366ULL, 0xD9651E33F7F6F1AEULL, 0x60041EF145BDB25AULL, 
            0x611753D999138CA2ULL, 0xA7743BAED04FA1D6ULL, 0x88F10396FE048165ULL, 0xEEC14E5DF600957AULL, 
            0xA802C38D8AC0C29EULL, 0x3D4827453A96828EULL, 0x9CEBC8A4FBD55B91ULL, 0xA3667CF2F2BF1700ULL
        }
    },
    {
        {
            0x52050DB60D179689ULL, 0x431C6EF5704EE22CULL, 0x275A42FF27128F48ULL, 0x0A4AC0BB4368D03EULL, 
            0x839434FEA613EA0DULL, 0xF5E948EF99CF93E5ULL, 0xC534714BA11C66E4ULL, 0xA52B37F4675B1B80ULL, 
            0xD3A93B577A4AE333ULL, 0x056AE858690DDF2BULL, 0xF496C2CB2249169AULL, 0x5B3845BBE1152E8FULL, 
            0x60499FC65C14A3D8ULL, 0x2BCFEB8FC63DC8DBULL, 0x9EDE63E0876A5B1EULL, 0x9F0335B61AD87296ULL, 
            0x0E21D9FCF77ABE75ULL, 0x4E4B409A8C92EA70ULL, 0xF5416DC30A0B8EEDULL, 0x2DE4E4CDFDC8DEEDULL, 
            0x3B6A77BB9CDC9794ULL, 0xFBC81FA887929817ULL, 0x72B3F961328C2B03ULL, 0xA5B39F3054270BCEULL, 
            0x53A3AB973CCE3A1DULL, 0x5B3AE586312EAE30ULL, 0x0E5105277A861E57ULL, 0x31198128FEDB6529ULL, 
            0xC3B7BF08B9872374ULL, 0xFE3567999D47FE08ULL, 0xBC552580E37E80C4ULL, 0x01ADB3810B601589ULL
        },
        {
            0xE049CF76FAFA5EB5ULL, 0x9C55644299BE703AULL, 0x3E8026E12FD95F36ULL, 0xBE3E677007CAA656ULL, 
            0x2CB34864EEF5FF72ULL, 0xDA714B7662FCB171ULL, 0xC9A5577A329B3B0AULL, 0x6B6FA23CEDA22854ULL, 
            0x20D543366172F057ULL, 0x9E2F90D2428A5F11ULL, 0xED69AA81E0B0046FULL, 0x003903840FE92367ULL, 
            0x64335B1F861FF296ULL, 0x0E5CB92614B7CD6FULL, 0x7B8BF1D93E37A1A5ULL, 0x800951C6F49AB3D2ULL, 
            0x56A3FB53710435CAULL, 0xB2186B6F3210C343ULL, 0x4B652D89566CB26FULL, 0x4DB9F1B9289977ABULL, 
            0x728A85F55945489BULL, 0x4AEE34DB205FA02EULL, 0x866DB84D9075FE45ULL, 0xA8EFE5435A152F75ULL, 
            0xD64835CBCFE69F93ULL, 0xAB32C7B3D514A92BULL, 0xD9DD4B0A926F8BB2ULL, 0xD65825418E22BC9AULL, 
            0x09F3D99384C51F50ULL, 0x90B2D8FAF631F820ULL, 0x500692ABC702DE03ULL, 0xB3BD560CA2143423ULL
        },
        {
            0x3272BFF3FBDD4C7BULL, 0xC4D1059E0CC18D75ULL, 0xC4B439079F413940ULL, 0xEA0E87D7F664C0B3ULL, 
            0x08F340ACEAEC2D7AULL, 0x65DAEA56EF8D09B0ULL, 0x5DB1187082631B65ULL, 0xE050CCFD459C9239ULL, 
            0xCE2F06244883CF38ULL, 0x1FFB306D3C117BD2ULL, 0xCDC858BA6566E0C4ULL, 0xDAF83210C85631D0ULL, 
            0x4CD31C60FFA5A9A8ULL, 0xF86D440C47C35680ULL, 0xC1563B7E48F5E2D8ULL, 0x491D8E4DA001AC3EULL, 
            0xE2BBFF57BFDAC0D7ULL, 0x9A156A12C566F03AULL, 0x93BEC9BDA242062BULL, 0xEB1D10D73B2DE286ULL, 
            0x7CCB449C0DA2E3E6ULL, 0x4A88056F84A19FB1ULL, 0x389815E11F46CDD7ULL, 0xBC2CD25601A14ED6ULL, 
            0x6ED83ABC4B10E790ULL, 0x119D4BDF45024D60ULL, 0xE948E8E1E6931B24ULL, 0x1B087D69640BEB3EULL, 
            0x263D21099BF7645EULL, 0x61F5F716ED40D71DULL, 0x330BF5F428377CE8ULL, 0x0CDAC04BCC1CA780ULL
        },
        {
            0xB93C644F216AA47DULL, 0x5C3CAE35BAF38C2CULL, 0x1F4228ABCFE8B081ULL, 0x8127CE10F9811C3DULL, 
            0xAF58DD28BBBE6DEDULL, 0xF2C4F850086462DDULL, 0x0A913CD1DD73419EULL, 0x42F9FBD3DE8329D4ULL, 
            0x8715F5F6B0928B08ULL, 0x813E97B15BDBFAB6ULL, 0x78FD0CA6CC3163C2ULL, 0x8A5FAEE7AD06C2F6ULL, 
            0x7BACBD702AE0856CULL, 0x164386FFD1441307ULL, 0xA78F13A44AA3206FULL, 0x00D0926858015B2EULL, 
            0xB0A482E94B44DAB5ULL, 0xC0D993D576A58CDEULL, 0xE8E5FD0B39865AD5ULL, 0xD0D2E0680356B47FULL, 
            0xEE025D936B03DB6FULL, 0xBE0AA34424C03F6DULL, 0x41124ABB2D3F2FEBULL, 0x412320D9A1834B6CULL, 
            0xF49D5B5E0054BB06ULL, 0xB3AC3E57FC9B5215ULL, 0x90BE57322A7C0FA0ULL, 0xC71420C48995B5A1ULL, 
            0xCBFC72B05B4971E5ULL, 0x937895228690A99AULL, 0xEAE8A338822AFDE7ULL, 0x3E02050D8003CD04ULL
        },
        {
            0xA40BE5873AB81A76ULL, 0xC0EA45C897B6B7BAULL, 0xCA6742C9F1A121FEULL, 0x855C932000BA60C6ULL, 
            0x6345CE01D2D10D8CULL, 0x37F52A6AFC12B0A9ULL, 0xCC26FA3BBF051F22ULL, 0xEBB8740BFABE6230ULL, 
            0xC3A36997120FE4E1ULL, 0x5838749260D9440FULL, 0x8071D0ABBCEBA819ULL, 0x02C8983AAC1CC444ULL, 
            0x5F80A53768D192F0ULL, 0x456C166F44C0D645ULL, 0xDA64FC5844969EECULL, 0xEA1E4D9D3AAEC02FULL, 
            0x4A96449E26CC6685ULL, 0x6ADD679BD820356CULL, 0xF8FE7BB78ACE3473ULL, 0x5BF505D275D58F77ULL, 
            0x58DC842C18DBB38EULL, 0xCE7477ADCC56A2D0ULL, 0xCDB8F9D77ADB392DULL, 0xFC2BF896E6DCF77FULL, 
            0xE91E79544A204EB0ULL, 0x898F642AD790775EULL, 0x99AFDC95BDAC1D7AULL, 0xA1CA50EF50A35F23ULL, 
            0xBF50BFE12F0C2300ULL, 0xFFD75B5E05C355F5ULL, 0xEA89E0D13CD632AFULL, 0xD81CF723FC7BE879ULL
        },
        {
            0x8ED1C157AE69EFA7ULL, 0x41CBCD296113CEB1ULL, 0x3746437E286A8676ULL, 0xC96A0DE01387611EULL, 
            0xFA81CB9B5E080555ULL, 0x688FDE2944B5DC51ULL, 0x94C0B73668EF4CC0ULL, 0x86D42737D05EEE9FULL, 
            0x59DF90EA64CDCAB0ULL, 0x890F22E761A6FA27ULL, 0x495938C9FDD4763DULL, 0xDA96F6116CF5ED24ULL, 
            0xAC68FB25D64C3CD4ULL, 0x30FF60798B978C76ULL, 0xF881FA0118B66120ULL, 0xBC9817E5158716D1ULL, 
            0xB1B2EAC0178A1E1AULL, 0x342F16DA6BBA0169ULL, 0x51A0BB11C42EF9ADULL, 0xF9832C539903A847ULL, 
            0x6E13592ABE74DC83ULL, 0xF6CFAEA4FDD61BDEULL, 0xBD2271064CF2E9ACULL, 0xE5BF1AD345C0184FULL, 
            0x35D91AFA32B9813AULL, 0xBD0B693184BC5A4AULL, 0x289863ADFFCD579CULL, 0x83807A58C83FDAD6ULL, 
            0xB2DAC19D76F53FDCULL, 0x7A4604D6EE110642ULL, 0xE468E3400DA91FA5ULL, 0x74DBF7B5DD9291E6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseBConstants = {
    0xBB710C1AD7DC99E5ULL,
    0xDEEDF4DA647C053DULL,
    0x2496215645F84002ULL,
    0xBB710C1AD7DC99E5ULL,
    0xDEEDF4DA647C053DULL,
    0x2496215645F84002ULL,
    0xC3277D06793EC141ULL,
    0x2D5C0E5785B0A926ULL,
    0x1D,
    0xC2,
    0x92,
    0x4D,
    0xEB,
    0x91,
    0xF0,
    0x2D
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseCSalts = {
    {
        {
            0x57D6871D5F556674ULL, 0xA26AC8AB08F59C5DULL, 0x63BBE58B35D9A248ULL, 0x1AB8C895356D2409ULL, 
            0x1EA479636B57ECF6ULL, 0x0BD115A286C3E285ULL, 0x5A6D2037AC1E956DULL, 0xEF168CDB3C99C738ULL, 
            0xE7DA1348C5B36A99ULL, 0xA51C3D27E63BACBBULL, 0x653B1F597D4E04A1ULL, 0xC79C0F7B19A6B8F5ULL, 
            0x02F3D426E2C196A6ULL, 0xDB279F17C5BAF5C3ULL, 0xE7222D4D2F8615EEULL, 0x67B0943CE0256FAFULL, 
            0xDC92F882F7997B27ULL, 0xCDA62E3B7E50FAADULL, 0xC2F5BE38EADBF9C4ULL, 0x77657B24A83DDA13ULL, 
            0x458CB18FE97FC2D3ULL, 0x32696EDB099ED7C0ULL, 0xC6868E60E8E01F63ULL, 0xCDBF7E7A58A0F2F5ULL, 
            0xAE6B346CFC1CAA07ULL, 0xD8686A557BC5AD30ULL, 0x099F1CB8AF6B63F3ULL, 0x3C5E636990706DF7ULL, 
            0xF9A51185FCD03EBEULL, 0x883DF9989CF089DEULL, 0xEACADB26F5E60AC3ULL, 0x4E2551A0D2E76376ULL
        },
        {
            0x7B2E2CDF1B202ECFULL, 0x5B020DE4A9A49C69ULL, 0x0E8AAA8126480B8DULL, 0x65A98692CF34DA46ULL, 
            0x99B08B6E2C0EBD53ULL, 0xE3376D991C28B43FULL, 0x3E5810945523AA4CULL, 0x7DB8CD5454F0ACD0ULL, 
            0x5EB0148DD1EB38E0ULL, 0x6C5C7780741C1472ULL, 0x0238B8D91147BC89ULL, 0x94F344B06ED928ADULL, 
            0x698B644858E9770DULL, 0xDC0D907775DC2DA6ULL, 0x42AEC6F9E3FDDD85ULL, 0x7D7AEF88C100A848ULL, 
            0x68A1B19D24140787ULL, 0x629971DABDE232C0ULL, 0x09CA3621151A8E08ULL, 0x14CB941209446B68ULL, 
            0x8F01C6A1C039D4D3ULL, 0xD21BF76F81F3B08BULL, 0xD135D05F1DD9AF77ULL, 0x9C7BCB793FD421C7ULL, 
            0x3505AD96F04B7992ULL, 0xE0099C5BA4A33B59ULL, 0x5098BE617AF44FAAULL, 0x8F77A2BE55300B1BULL, 
            0x07FE702E61447211ULL, 0x2A028901C48DB7E8ULL, 0x8D6B5FC869E9C63AULL, 0xCDC2A956A738D5FBULL
        },
        {
            0xD2D91585C83A6412ULL, 0xA642335766AC1704ULL, 0x32070CE10472D1E7ULL, 0x98C47E09C64EC3B6ULL, 
            0x92781800093A3594ULL, 0x733913B840D1E107ULL, 0xE6E1600C998F0F39ULL, 0x6A3CB7FDC1B79937ULL, 
            0x162ACD744172CB70ULL, 0x6AE79A258259FAD8ULL, 0x5303BB19F12C8F20ULL, 0xA634A325BF37161BULL, 
            0xCC1889F3678DCE22ULL, 0x44629CA51676E472ULL, 0x142E4275CC574DBDULL, 0xC4EDAB2D48B7FCF2ULL, 
            0x4CDDE24343AF8366ULL, 0x0459DAE3DDA805DCULL, 0x2B68788D394B53E9ULL, 0xC450D745CD8AAE2AULL, 
            0xB060C4A4A43E2CE0ULL, 0xF43F51E36896797DULL, 0xA4F27A21093E1767ULL, 0x6AD1EF64CBF6D244ULL, 
            0xB79FAAF8E8714639ULL, 0x4FE5506CE48BB36CULL, 0xD3C5BAED0EB5EF8DULL, 0x517B6E17FAF54B68ULL, 
            0x718A696DFFAEEDAAULL, 0x41C193F72E0CC71DULL, 0x96AC5388E8C6E361ULL, 0xB27ACF60563DC3F2ULL
        },
        {
            0x49A7E22AA382BB7AULL, 0x2EBF60BD50171C73ULL, 0x93F82EED88F531BCULL, 0x66EF043DE9E65920ULL, 
            0xA52E7C2434AABCA1ULL, 0xCE0DB2C87F3426A6ULL, 0xF3CBCFC10AF6B0EBULL, 0x4EA8BD75F03EFCAFULL, 
            0xB351182AB1FAEA16ULL, 0x62F415E04C0F15A8ULL, 0x054217E1FF7EC51CULL, 0xDC371F767EA836E2ULL, 
            0xEC471379D5E4429DULL, 0x891E2A584C4D848DULL, 0x391C16A4CCE66629ULL, 0x0AC6496BD183D710ULL, 
            0x17BD74BAB1D34D10ULL, 0x2EACD235EFE654FDULL, 0x933EEE2D61CBB4E7ULL, 0x0D494C761E942D86ULL, 
            0x6CD0A706F1CD9434ULL, 0x77F60B596783A239ULL, 0x30C33A952013B223ULL, 0xDB05024093E8C5A4ULL, 
            0x1FEA92F8587D071CULL, 0x84DB2A37067550DDULL, 0x60655F61BA491411ULL, 0x2AD63E561DB95A98ULL, 
            0x218A950AB9D676C5ULL, 0x2107A0E3712CBF06ULL, 0x169CD1351CAB4492ULL, 0xBD4B73F5F07DF5D9ULL
        },
        {
            0x22B2342BA5E73379ULL, 0x666FBD3549F39CBEULL, 0x26186DD6D0607308ULL, 0x1720078A6BD47D01ULL, 
            0xE72F2F9D96901E8BULL, 0x8A8BE1C7361364B0ULL, 0x319B43103EDDA9B4ULL, 0x11034EE551582D60ULL, 
            0xAC498B3A7F57311CULL, 0xF0339C52E21AB2D5ULL, 0x5CB6E12024490A25ULL, 0xB8CDC91FF65F5267ULL, 
            0x6088D676FA22FBEDULL, 0x83E3F5B14A8637EAULL, 0x477FF3A12407321FULL, 0x301A2D5F3034B711ULL, 
            0xFA9BDABE46220D70ULL, 0x48DC8E7D0CDEDAA6ULL, 0x7B7BF91930E020A8ULL, 0xB687DB831D8ECB1AULL, 
            0xB4D6A45DA706C2A1ULL, 0x7EB83489C8802F27ULL, 0xEE611BF315B833D0ULL, 0x7E34C5074A38B1A8ULL, 
            0xA46B9C9B499E1F30ULL, 0x4DA8A96AD19A9295ULL, 0x77D41451802FE88CULL, 0x823FB907CFBC26EBULL, 
            0x1BAA32A8E7AD5F8BULL, 0xBEB43A92B3E99996ULL, 0x5E0DA604F61C40B6ULL, 0xA088D7372826F42AULL
        },
        {
            0xC68FBDCBDDAB9A2FULL, 0xA645882FEF017397ULL, 0x2E6781724F2788E8ULL, 0xEE3BA4F44B3440C4ULL, 
            0xB56BF6ADC39B4F73ULL, 0xCE8BBF9AB8865D8DULL, 0x2BB64FD9B239E048ULL, 0x56833F8762C943FFULL, 
            0x5C172F00F917D516ULL, 0x35049E12B43CA226ULL, 0xBC3E1CCC3EE3F140ULL, 0x6F83122BA3A05AD2ULL, 
            0x83FEB3B061E0494CULL, 0xE2064E2053108446ULL, 0x7CD94924D1A57C24ULL, 0xDC9A0FEB4678D21AULL, 
            0x0FF4638735CD8809ULL, 0xB4B1348EAFD67E95ULL, 0xA6FA1AC042D2D733ULL, 0xEF7FB26C25A5D4AEULL, 
            0xF01D93A90460FF67ULL, 0x0B7EDB63311E2CECULL, 0x632C31733D4501E6ULL, 0x4AD942B6833A23D1ULL, 
            0x34700C125DEF1439ULL, 0xB74D924CAB40482EULL, 0xD4336F97330E348FULL, 0xF54EF9D87035703AULL, 
            0x28B2419C905F9BC9ULL, 0x788F72C19A81256DULL, 0xAC32BB9B7436CA34ULL, 0x94A09FD49D0EA092ULL
        }
    },
    {
        {
            0x142C465639A1FBB5ULL, 0x5404708BD2EC62D9ULL, 0xB5FAA72B528E7B98ULL, 0xDE98EA58ACA7E44AULL, 
            0xA55559FAA4D616DBULL, 0x1B7C91E53ECCEE78ULL, 0xDBD81E5BF974469FULL, 0xE798234064B45435ULL, 
            0x5E003719DF24AE87ULL, 0x0E50F4115FFD7DD3ULL, 0x8C0FC4C51E477E78ULL, 0xA60BBB3C9C019C95ULL, 
            0x7E95A20700C62632ULL, 0x0876F86DFA8912E9ULL, 0x3765E097E83ADD28ULL, 0xB3DCAAE659BD351EULL, 
            0xF5EA8B62BD0623EDULL, 0xE6145CD811EEBB9FULL, 0x17155FFD6597E350ULL, 0x696451050CD257DEULL, 
            0x2C86426D03C560F4ULL, 0xC363E2A89249432FULL, 0x199563662010F88AULL, 0x6FE87A12E4CAA536ULL, 
            0xA9DD09F5B127DBFCULL, 0xDA1C962EDEE01FBCULL, 0xFAA08CDE58101907ULL, 0x815401C033090269ULL, 
            0x6513FB2DE049E9DCULL, 0xFEACCAD3F71E99C4ULL, 0xE744A1A300052995ULL, 0x73E7A57D7282C6A6ULL
        },
        {
            0x5E83960330C453D0ULL, 0x3405798EF3FA1430ULL, 0xBCFAF33E882571F0ULL, 0xA5845C9CD0262A95ULL, 
            0xDF8B79E638990560ULL, 0x99CA5EA1F41A7B40ULL, 0xE3245A68DA38B026ULL, 0xD68B33BABEFEBA7BULL, 
            0xC3AEEE12D257D521ULL, 0xA77838F7F93D3E98ULL, 0xF544D6A2802CAFB5ULL, 0x28A03094FAF1A902ULL, 
            0xC21BB40F34F22DAFULL, 0xF2DD0C9AD106DE9AULL, 0xADD4AA43246D3E15ULL, 0x8BA577DD8D622666ULL, 
            0xD46D7A9EC55E9BCFULL, 0xB895CE5A1F2A35BDULL, 0x2BE6671FE8CDE3F0ULL, 0x9634F55CA9483E64ULL, 
            0x4442E7B69C938210ULL, 0x3702E5E809351CC1ULL, 0x9E4B943EE8F6CD7FULL, 0xDE8CED29D9B1D62AULL, 
            0x58977E99493B429DULL, 0x774BE878F8CB5FEDULL, 0x4D7B20874D880A3EULL, 0xE56E8EFE4B71BD79ULL, 
            0x479EEA03337FC1EDULL, 0x5AA2352F1BACB2D9ULL, 0xA7B2915C6956D8DEULL, 0xA87044E5BECF40E1ULL
        },
        {
            0xE04B427A01A14341ULL, 0x66027C0865A57683ULL, 0xE6966B4C1A6853FFULL, 0xDEABED24945B4A2EULL, 
            0x68B5AC6C49A38C28ULL, 0x350E1EFA196EB984ULL, 0x3CC4C20E5BEC3A93ULL, 0xF2DA1E39973AAF1BULL, 
            0x6893A9F6FA74CF8DULL, 0xCB83DFC142D39148ULL, 0x2261402078EB39B3ULL, 0x61D1FAF61D30FCC3ULL, 
            0x6964D86320F20584ULL, 0x56482BF00E4E71E3ULL, 0x6A8F9C9410CA8343ULL, 0x08ACFFB4820C71E0ULL, 
            0xD5296FE3B6D126FBULL, 0x0C19D860F67F8742ULL, 0x6B01C34EDE5B340BULL, 0x44CB966B289FFD83ULL, 
            0xB518E4AD8CF1FD31ULL, 0xDBA4558EEE44F30BULL, 0x8DD8ACD7DE5ABCE9ULL, 0x7EC9C5D9C3045DB0ULL, 
            0x0409AA7411A06EA1ULL, 0x0EE78618F3BF3043ULL, 0x82EC6F0A4724B6C7ULL, 0x3FA67E6421A65316ULL, 
            0x544783C9DB208941ULL, 0x82BCDEC6FE5DB614ULL, 0x332FEEAD16A12520ULL, 0x301E9E8E1ED26E10ULL
        },
        {
            0xA54D114EE4C9BC03ULL, 0xE8D11AADE62EEC07ULL, 0x085433B324511D3FULL, 0x8F12D91281BE7396ULL, 
            0xB707A66F4E328EACULL, 0xB957C4CA04D25CBDULL, 0x17F2BE5701807C2FULL, 0x28442E872CA7888BULL, 
            0xA42D81F58E4B3B24ULL, 0xA724860ECF2A0377ULL, 0x55747548FD7786DAULL, 0xF1C92A3AA8A882F4ULL, 
            0xDBC12CF35CE7D0F3ULL, 0x4271DAD7A8DE76DFULL, 0x71F4089ADA849737ULL, 0x9E46EEEB952972DDULL, 
            0xB7E6550F6BFA77F7ULL, 0x3C2D7F1F81BB470CULL, 0xD36381E621EA1648ULL, 0xBE35BF8DC2368CDDULL, 
            0xA834BF17AF0E48B7ULL, 0x01406E38F0B256FDULL, 0xF99196C2EF1669A9ULL, 0x3C3024204B22FFC8ULL, 
            0xB455D3884EC70531ULL, 0x83D86C74709F98F0ULL, 0xFE6A19C264A0AD3CULL, 0xCDA0DE9A468D6D3CULL, 
            0x748206C5845B7102ULL, 0xFFEE435EDFFA1F4EULL, 0xAF6E68C5E51E912BULL, 0x4BEF7B46AEFB1B0DULL
        },
        {
            0xA8B928B31086EFD5ULL, 0xB6351440880535DFULL, 0xF67272B57ECEA320ULL, 0x97500D7889C221DCULL, 
            0x0F77D75908980C48ULL, 0xF556AA1CF393AE50ULL, 0x909DEB0804165D2CULL, 0xA3A7E1740C1B2A16ULL, 
            0x70712EB033BED672ULL, 0xD17397811A1095C9ULL, 0x26531549CCAA9896ULL, 0x3EB647D5468B292CULL, 
            0x02656B60A6507B1BULL, 0x50EFAD6B650709C6ULL, 0x991B65C35146C7B8ULL, 0x9C316C38FA6F4671ULL, 
            0xCEC7B0D282D045F0ULL, 0x679429EEA3A17709ULL, 0xEDFA720356838BD4ULL, 0x5D6AC51004A5836CULL, 
            0x268F4333BB1C0657ULL, 0xD30674A5F741A9B7ULL, 0x8CF66A183EEB3B8EULL, 0x429585C574E9909BULL, 
            0x603F46C97890255CULL, 0x6DC9D148666AE0F6ULL, 0x1476B4E48095D688ULL, 0xCA466054FAAA12CFULL, 
            0x65788BE07AD65E6FULL, 0xC8C3A95132317FC9ULL, 0x9325C593E1372245ULL, 0x58AE37F5DE2047C4ULL
        },
        {
            0xE5D1329504152148ULL, 0x3E29A5B38A13825DULL, 0x37F738D1E8415EA9ULL, 0xE717BF5A68F63DF0ULL, 
            0xE778698EF0CEC877ULL, 0x8A911488B356A82DULL, 0x5E659C9418310B52ULL, 0x7FDAC9C85C435FE3ULL, 
            0x08100AC43F2FEF96ULL, 0xA2E051A93DE79081ULL, 0x5147A40249495367ULL, 0x970DE1E611935A78ULL, 
            0x2051377D1B80357BULL, 0x336EBDAE21C285D9ULL, 0xF75357FB2FE2E54FULL, 0x605147A97629E86AULL, 
            0x09693BE64C8CBBB1ULL, 0x6825BB14D75A004DULL, 0x85BE7DD711610703ULL, 0x4BB65682311E6B99ULL, 
            0x75004CBB2AFC4B23ULL, 0xBA93246F912DE9D5ULL, 0x08D2B659C4BDA3C5ULL, 0xE86815676DD43B1FULL, 
            0x2406FF02C03ABC3FULL, 0x705081934C4F9618ULL, 0x7510D7EF8B2D3EA5ULL, 0xA5C67BEC440DE14DULL, 
            0xDED05333758DAF4BULL, 0xF9FA9C6439EA64C3ULL, 0x211CF8A31DDC9B20ULL, 0xE4B457965D4FB532ULL
        }
    },
    {
        {
            0x2553F20AA3E5394CULL, 0xE04F91C105383FEFULL, 0xD94ED794243E512AULL, 0x517ED9F19FCF9F7FULL, 
            0x67715F8FC351B8CFULL, 0xE4E23493AEFAB574ULL, 0x75A7D2AEA27A8AF1ULL, 0x89AF22BC6AB28D2FULL, 
            0x1053523772FFE380ULL, 0xA0CA674F817B3784ULL, 0x97E509CDCC7F0C0EULL, 0x31E1902350D67D95ULL, 
            0x2AA5A689E4EE7E79ULL, 0x1D3BB53168A6F254ULL, 0x5BE1D151AAF99F4DULL, 0x67AB2CAF3A963BC9ULL, 
            0xCBB9AC75B31C417EULL, 0x857A1EAD6475523DULL, 0x25216234287EE8ECULL, 0x341630556A1C2F1CULL, 
            0xF6D038F7DA7F9AB6ULL, 0x2CC05633167BEB57ULL, 0xF859EA54AB0B611DULL, 0x6DD041579C48C4D6ULL, 
            0xC0660C697274C707ULL, 0x116807A539FAE2F5ULL, 0x577F693B3BEDB1DFULL, 0x750FC2C1496D2A21ULL, 
            0x89D7A0EC1FCF3C42ULL, 0x876B2127A86ABDA8ULL, 0xF1E5C317295D9EF3ULL, 0x59C6EED0049CCC67ULL
        },
        {
            0xCE347FF96E80C860ULL, 0x914E082397C9DDBFULL, 0xDC0A9A1AEC2D5AC8ULL, 0x9269CC97A8C26D24ULL, 
            0x1AE09E32E18576E2ULL, 0xECB98F364C71D968ULL, 0xCB6B68B6DF7A25D3ULL, 0x20D50DA88D655F2CULL, 
            0x144898AB5D83BC36ULL, 0x15C538799EF303D1ULL, 0x9AA741B695443C3EULL, 0x39BBDECDD370B167ULL, 
            0x2440E62C73CDA649ULL, 0x2E895B9EADB64D8BULL, 0x073368A131320554ULL, 0x3F2579A15EA8CF6BULL, 
            0x04A9E21F497D9D87ULL, 0x2CC736F456AD27F8ULL, 0x2E5D7FC9D5181AAEULL, 0x06325E117CC9632DULL, 
            0x54C9AF35CB5FF51BULL, 0x1908A3E049F9E69DULL, 0x98EFBAD411E66ADDULL, 0x1C46270A1CEE28FEULL, 
            0xE1FA10D2C04D4A55ULL, 0x3A9E424E4F914FD6ULL, 0xBB0E1BD792BF87C3ULL, 0x54DBA6C73BE2ABCBULL, 
            0x7682217765E573FDULL, 0x05DC18190FCAFB25ULL, 0x55EBBB7FA9169919ULL, 0x99D28F5D9714A454ULL
        },
        {
            0x4CB1EE0941AFC3E3ULL, 0x88E77C86C5AF0656ULL, 0x2BD331DFEE404D9FULL, 0xD1EE46BFCAF0AC25ULL, 
            0xDEF4F15412B6AB44ULL, 0x05D4C6D10BF722D3ULL, 0x9E2562D00020C385ULL, 0x7E2C0BFB1E05B5ADULL, 
            0xA6A35170452AD412ULL, 0x89E7B1607BA4E066ULL, 0x4818B9F999729E6FULL, 0xAC7DE7F5507EBCCEULL, 
            0x10B007B171C06FD3ULL, 0x448C98181B8DB61CULL, 0x2E53C83CF03D2208ULL, 0xE644CA0BBDCA7FA2ULL, 
            0x13108667FCF6B922ULL, 0xD109D88CF8AF6666ULL, 0x71711581971DA16FULL, 0x0B5A002BD902C505ULL, 
            0x1B19D7A9645A9AB5ULL, 0xEACCACA8E27D25ACULL, 0x81A46B48A5440F99ULL, 0xB3F77F3263A046F5ULL, 
            0x65C1C8715B98ACFCULL, 0xA41D33FA84A04F90ULL, 0x029A5CBD05B38B17ULL, 0x118A41C110B16E50ULL, 
            0x5A6E7BBFE36ECF50ULL, 0xE532F964AE0E369EULL, 0xAAF81D3BC78F92D9ULL, 0xC9B8656E051E4422ULL
        },
        {
            0xAE94D56D63251514ULL, 0x82083C4C89BAD666ULL, 0xC341949B3D6E0619ULL, 0x78AAB53DCB9C673EULL, 
            0xA33CF96E69DEFDB4ULL, 0xE43A120686516E41ULL, 0xD8762C3B2E6F4F70ULL, 0xD3301896F21D6386ULL, 
            0x139EC70496F2F65AULL, 0x951211C57A9E70A6ULL, 0xC6831818204091F7ULL, 0x140B6F3EAD62893CULL, 
            0x7E82911C771B356DULL, 0xB75F0E77AE16E58BULL, 0xADDBF6278FB79AFCULL, 0x5D5B45250AD682F2ULL, 
            0x2F6D2839BBC7623EULL, 0x7D9A4C8FC7559F26ULL, 0xBEB6971F72564378ULL, 0xED272CC4D232F6C6ULL, 
            0x213E37358C7B2B3EULL, 0x4008C859562C29DFULL, 0xA6034F82FB3069F3ULL, 0x18DF633BD9AC83A5ULL, 
            0x71E7173A096C126CULL, 0x9C65045C41B7EC85ULL, 0x7A209B13AE9FE9E1ULL, 0xE575ADF86D0F89F8ULL, 
            0x90487317CDE3CB9CULL, 0x8CEA6936AAED94B8ULL, 0x584A147F9FCA1316ULL, 0xBABE798DEF001B8FULL
        },
        {
            0x4CC1B0AAB43C60E3ULL, 0x407789F79E03FEFAULL, 0xF880DF9750E4CC34ULL, 0x2AAD5CBC4C6EE0D4ULL, 
            0x1FDB8DA79874C662ULL, 0xD30406F3C6D93A36ULL, 0x773FC0E9DA9C86B2ULL, 0x3D2E9CA83B73FF29ULL, 
            0xAA872095D454FCCAULL, 0x19BECA156EB98251ULL, 0x0D5E8050141424B2ULL, 0xA856EC301093DF78ULL, 
            0x92388477BE07D084ULL, 0x5D974A578545437DULL, 0xC9C3AE9E781F9895ULL, 0xDFD2F1724DB54523ULL, 
            0xC5F2B821A573FBFCULL, 0x397D730539C938C7ULL, 0xADBCF4FE6FD229D7ULL, 0xE9D21213B489429EULL, 
            0xD9973F9C6564DAB6ULL, 0x1A93F647279E5AEFULL, 0x9710C308912B62EFULL, 0x2932C944464D46A3ULL, 
            0xFEAAB5F42979C2EFULL, 0x6CE94474EA75B4BBULL, 0xF0299B41DB69B6A7ULL, 0xAD8FCE42B99446E9ULL, 
            0xEB1F0FF2D68C01ECULL, 0x37A0F4B43D6BE432ULL, 0x4731BB3C97BAA6CCULL, 0x012EFBB839C063D1ULL
        },
        {
            0xC5AA3E5A95B13819ULL, 0xC14ADE2D09CEC6B1ULL, 0x0E3852C36463BEF4ULL, 0x8A2F33E4490E2AECULL, 
            0xB163D56D394134DDULL, 0xE9CE4937C4268592ULL, 0x6EC56ABC877E6F18ULL, 0x3132013B2E8454A3ULL, 
            0xCFD403941A87B2E1ULL, 0xEB037F968CF39A2DULL, 0xD342FCD0F3CB56E7ULL, 0x09EB640413C1D895ULL, 
            0xAC2EE17BD2E6E036ULL, 0x0EB403C214731E3FULL, 0x8269C88A226A3890ULL, 0xCB56A8195E84309FULL, 
            0x153360CB02B9332DULL, 0x74E5F5CB867F7FA0ULL, 0xA6CFB09436427978ULL, 0x83EE1F444ED4913CULL, 
            0x14B51214C18BC22BULL, 0x29A944AE3576CEC1ULL, 0x5DF64ACE943AF30CULL, 0xA29F16B5C6A34CBDULL, 
            0xA719E7D79C0EA266ULL, 0x3E26A643CA2A9A62ULL, 0x86EF1401426ADFB1ULL, 0xEDEB3A5CBC7C3825ULL, 
            0xC9542D72E0FDFB86ULL, 0xEF19746FD74AF62DULL, 0xB62448E8FC128035ULL, 0x347D191526808F4FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseCConstants = {
    0xA9B55E3DE6D7C640ULL,
    0xA9684A24E62959C3ULL,
    0xF8D823C9E1ED305CULL,
    0xA9B55E3DE6D7C640ULL,
    0xA9684A24E62959C3ULL,
    0xF8D823C9E1ED305CULL,
    0xAA5AA4743BFE07EDULL,
    0x8435DAB644C80E1CULL,
    0xA6,
    0x92,
    0x3B,
    0xD4,
    0xD5,
    0x6C,
    0x70,
    0x0C
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseDSalts = {
    {
        {
            0x5A9A75A7B7FDEDEEULL, 0xB83984CA1057C904ULL, 0x67A305A54A31C2BAULL, 0x73E02D10C14526B1ULL, 
            0x01A0378C870C0181ULL, 0xFE9DD80D30C94055ULL, 0x501F25CA6D94239DULL, 0x70429607E176C026ULL, 
            0x73603CE9F7147221ULL, 0x4D0DA4778E941388ULL, 0xB572420577D53A39ULL, 0xF82D80C3793FFD11ULL, 
            0xB109154F44F3A3ACULL, 0xD6380F1E419ADED5ULL, 0xDC6DC34C93531AE7ULL, 0x452C495F293715C3ULL, 
            0x42146F2AE5DB3024ULL, 0xE9A691BDAB7606A5ULL, 0x5C1BC0C2A8BD5F4DULL, 0x971648C1486655E9ULL, 
            0x10B301F1B4345158ULL, 0x5E1BF05860ACC6A2ULL, 0x69FBB1E22722847FULL, 0x61374A7E8D1FD945ULL, 
            0xB510E1BAA1FFE584ULL, 0xFC1A1C9E1DCE2D8DULL, 0x5B1D2274FAB861BFULL, 0x40C1C59C33BCFCEFULL, 
            0xC3D7A90F0D65C2C6ULL, 0xFD3A9D66FAD5CDDCULL, 0x6BFECB74F5A33C44ULL, 0x730FEE17BFCD21ACULL
        },
        {
            0xA644D2D06AFB1FA8ULL, 0x59BBE381C0922A81ULL, 0xFD1410E6E206ED58ULL, 0xA6C9FD0AE8C5D118ULL, 
            0x204DFC060A749B38ULL, 0xB87A033FD009C612ULL, 0x902C46C9BE508BE5ULL, 0x3C026257E512B859ULL, 
            0xB740CE53341FC8D5ULL, 0x796C447B8F45F42DULL, 0xA0338813DEC28492ULL, 0x2D89EC86360D8CA0ULL, 
            0x56054D4A1FA48A8FULL, 0xF719B093DD3AB829ULL, 0x7A405F953E8A43EDULL, 0x2DC42FCAD64E7E0AULL, 
            0xC4D088DB9B000534ULL, 0x6787B3655C83C5D3ULL, 0x8869988E9C5AA3E5ULL, 0xEFD1E6C59D7BA4E1ULL, 
            0xF58F63903503E9E8ULL, 0x177A10AAB9E0E50FULL, 0x0333BB8BFA4DF568ULL, 0xED70C2EAC4C70AE2ULL, 
            0xA5FA116D34303EBEULL, 0x224CABAE315F5CD6ULL, 0x60950CA0B8C25976ULL, 0xE7E55D1A13FE0741ULL, 
            0x51132BB4AF06E825ULL, 0x9862946C861EFDD4ULL, 0xF4A033153AC50F2DULL, 0xD11113D0F784F6CBULL
        },
        {
            0x2C539D9A0DCB82B7ULL, 0x2FB2008BBAF19EA6ULL, 0x3F32C1C1854767C7ULL, 0x274C1A2CCCDFF473ULL, 
            0xA9D065B2419D7FD9ULL, 0x86CA0FF09D74FF31ULL, 0x5F41C6726DB347B7ULL, 0xAA4590591F4960AEULL, 
            0x147D38D2436763B7ULL, 0xE037092CAA3D4CABULL, 0x50C6978CF01B9BB7ULL, 0xE6798326023CC410ULL, 
            0xD28134E1AEAEBDD2ULL, 0xB766309CEE748C9DULL, 0x7FA15778CB397F66ULL, 0x431B06CA78DD5A8BULL, 
            0x6B1F9DF87BFDCFA2ULL, 0x683612DAAA5ADEFCULL, 0xC72418B2ADDB417AULL, 0xE0D1A69B631F5388ULL, 
            0xD3026AF4FDA00EB4ULL, 0x6A2C2093767B057CULL, 0x155D9B4CCF2AE830ULL, 0xDAA484BAAF36B11EULL, 
            0xA3CA9ADD3AF2E044ULL, 0xE3CDF53E21A344A8ULL, 0x70AC86285D2AA28CULL, 0x09E07CAFC03FC1BEULL, 
            0xB6F8F79DDEA47CB2ULL, 0x9DBD6A8233904621ULL, 0x3D76262887A4D73FULL, 0x285D16A35F7A4BB8ULL
        },
        {
            0xC8566E0F39FE5301ULL, 0x6A6A73BD48233D1BULL, 0xF949A7B6ADAEB4DDULL, 0x216A05583188F425ULL, 
            0x15825F375F200409ULL, 0x5C769772BE6BA7B3ULL, 0xEC4CA2D90A2A34A7ULL, 0xD28BAB0C21CB8903ULL, 
            0xDA73050FECB4BDDBULL, 0x31C7721239ABE260ULL, 0x7F17818EDDAFD035ULL, 0x28CBD976802A3DDDULL, 
            0xF64DDA4D0C4856F9ULL, 0xF173460132B30397ULL, 0x899228084E614017ULL, 0xF88E5C4A24156DE6ULL, 
            0xE5922496DF7ECF44ULL, 0xD7C432C8CC27BEEDULL, 0x6EF213BD8A615767ULL, 0x26C4522E82515708ULL, 
            0xE0C026E22BFB16F3ULL, 0xB75F48F406C09583ULL, 0x3160C8F68E4747CDULL, 0x36C3981BA14DFC95ULL, 
            0xE08F3C2D94EA8D56ULL, 0x6AE14FB441BFBE41ULL, 0x1398277306ADA8C3ULL, 0x0D59BD461221C1ADULL, 
            0xEC5C1DEB6E9291E2ULL, 0xD86BDFCF0BE2242EULL, 0x2DBC239E9E6D9C42ULL, 0x7DD911156D14F00BULL
        },
        {
            0x79D58922BB12006CULL, 0xAA1ACB99457B8034ULL, 0xB0337847B855265CULL, 0x4A77EC7AA6FB0FF6ULL, 
            0x64F81D29880C95C6ULL, 0xA01CB197C8D5F1F9ULL, 0x30A2743F36F9D684ULL, 0xC5A11416EE7A8B15ULL, 
            0x78CBC14083795CAFULL, 0xAE6D60C9BF370D28ULL, 0xDF3CE4AF719A1572ULL, 0xD725844CB37BD776ULL, 
            0xA626D11B47B20DA4ULL, 0xA40DF88531754554ULL, 0xE4EC163AF7F31464ULL, 0xEAD4EB06B95C0630ULL, 
            0xF60189D8AAEFE476ULL, 0xCC7FFB7F6B01554DULL, 0x3E926C412D4DB953ULL, 0x8F8812487BC42A75ULL, 
            0x74277AF7CBB55489ULL, 0x72D12CF77EDC8D57ULL, 0xB0C5BBC037287E7BULL, 0x6F4CEDD28449858BULL, 
            0x040115576F2C396DULL, 0x08CC0FD986CF671DULL, 0x77A64756BFCDE863ULL, 0x424C7959118D1828ULL, 
            0x2201E0F7A16B1888ULL, 0xC3A77F0CCCD6D7FBULL, 0xE7C315B725CDB67BULL, 0x12E4B881D63285CFULL
        },
        {
            0x66C25EF50225F27CULL, 0xB9E9DD301090A707ULL, 0x139941CD70EC9E78ULL, 0x221C567A5561F087ULL, 
            0x0104754CDA6F2D7FULL, 0x51AE54C87EE80E59ULL, 0x2D43B6F4622F8012ULL, 0xAE78F34947031754ULL, 
            0x7E5169EDCF0566F0ULL, 0xEE3699FE7B7BAAF8ULL, 0x2AA2AFAA4E45DE4CULL, 0x3A339B14F8D962F6ULL, 
            0x57E3D30F96AF78A2ULL, 0x31093675E5B8A16EULL, 0x9597CCC5E79D5C3EULL, 0x4AFA9876B25C19BEULL, 
            0x81A1067C41EA277FULL, 0x74501F2208FFB40FULL, 0x335D1AA8C52F43F7ULL, 0x1268E6C4B4B948D2ULL, 
            0x2F98B6B475B4E3BCULL, 0x2FB81FB7B21EE406ULL, 0x4D4D5C975136B338ULL, 0xF467C139D7711E06ULL, 
            0x522C8EDE978AB855ULL, 0xE76F92FF5F389597ULL, 0xA862033654D6546FULL, 0x379061D8865BC071ULL, 
            0x8DC089E0C989D604ULL, 0xB0BBA937D4F15D46ULL, 0xD8A3F2B13995656EULL, 0x7AAEC4296BE4DC84ULL
        }
    },
    {
        {
            0x423B4C7ECCA78425ULL, 0xB75A2D07D3F6BC0FULL, 0x7EBB74C38343A983ULL, 0xAC4D200211A8D1C0ULL, 
            0xD4F3EFFB5AE47835ULL, 0x01A9D83C4E4AD3C3ULL, 0xD80123DEAA191BD0ULL, 0xF3741B0175D041CEULL, 
            0x114BDC0AAF152D1FULL, 0x1DA63C3FFA49CDC5ULL, 0x9636112E5152FB78ULL, 0x5621BC3F3A47C541ULL, 
            0xD4537DD8F9AD7A85ULL, 0xCAB3C784393D89D8ULL, 0x0BA9A6C122E42336ULL, 0xC4E9137B750FA602ULL, 
            0x311A374BB62197E7ULL, 0xC4E2E61CB6500151ULL, 0x61BB0F1DB9D309F2ULL, 0x52AA6AC34804640BULL, 
            0x84C9169B23AD6C7BULL, 0x7A06289DBA13F526ULL, 0x115EFF7ED6C7F33CULL, 0x8B7C60CD3D2227F2ULL, 
            0xD424B9DB37F16C35ULL, 0xCADA97E08BC6409EULL, 0x6841C336416B7C6CULL, 0x5EC11105D0AC4DB2ULL, 
            0x870D634CD1B09217ULL, 0x05CCAA079315BBA9ULL, 0xB50AF65ACAEB3561ULL, 0xA30F2A057D7E314EULL
        },
        {
            0xE64DB82CB34D57B9ULL, 0x6F350B6947716E13ULL, 0xBAEEDB00D761AFDCULL, 0x11A24EECC8C01C3AULL, 
            0xECEE44F9E1AB94A3ULL, 0x0C0B9E6A6AD55E09ULL, 0x00714EA09DD760FCULL, 0x10BDF1356D5A6A7DULL, 
            0x7FBCD6BBE5EE1EE8ULL, 0x48B108977725E5CDULL, 0x58075C6E956C697FULL, 0xA6F1F202EF7E72C8ULL, 
            0xC6113F3AC508F96CULL, 0xA6ECDA0F66F25F33ULL, 0x157617ED2F13B4C0ULL, 0x51D2DC72C2907EE5ULL, 
            0x4628A1E9356307EFULL, 0xFE2347F897150D80ULL, 0x725E32129ABF107EULL, 0x795E34EFC661EB34ULL, 
            0x54A0D1CFE894BF3EULL, 0x40AC89F4EA791980ULL, 0x1871E46BAB1CA46FULL, 0x5D614A079BFE734EULL, 
            0x451C9D319BC7057CULL, 0xB1CA7414DD25586DULL, 0xD9EE03F84BFF117DULL, 0xCEEEE23057E53DBBULL, 
            0x6388E50E901AC1F1ULL, 0x5389F7925F9F32A7ULL, 0xFEBBD29557B2354CULL, 0x85FE388E87985B7EULL
        },
        {
            0xF9274CC1D2C5C68AULL, 0x87EB33D5EDD60FAFULL, 0x224E0E0E46164F4DULL, 0xE25E1582E173DE52ULL, 
            0x8F44ABE30CA0E223ULL, 0xA0243E2F98DA500CULL, 0x9B9243785570ADE5ULL, 0xD9260DC5637AAC18ULL, 
            0x500376B5F8C99067ULL, 0x079CC6E59B614F9FULL, 0xC49180DBF5F55D74ULL, 0xA70357FC21EF58A2ULL, 
            0xD0ACD20B917F8BBFULL, 0x2147B30F7DD1A035ULL, 0xC6EC4D526BCA7CA5ULL, 0x322211F9A15BF9FEULL, 
            0xFA3DD7EA83AEA473ULL, 0xA5C22C8DE024A2E9ULL, 0x92F0CFF018F8A6AEULL, 0x6E3CDBDA3188DCF9ULL, 
            0x6B8FF2CE6C638B6CULL, 0xC15AEFB2B70FCD37ULL, 0x21BEEB03B42BC356ULL, 0x25D54F352CFCB249ULL, 
            0xCF96B695E87D62F8ULL, 0x55664A4084857EC9ULL, 0x7866E664D950FC2EULL, 0xBC6A847EEBD95DE8ULL, 
            0xBAB31F0EE57B8734ULL, 0xF383A4AF14443E5BULL, 0x6A4FBFA7A98729A2ULL, 0x0FBD8CB5C0B01AFDULL
        },
        {
            0x686A523D89D4E568ULL, 0xAE4FF052903E9906ULL, 0x1EFB34BB8CED4874ULL, 0xB492E2BF71AEE299ULL, 
            0x4EE47574658CD51CULL, 0x5BF1E60A323621E0ULL, 0xC63FB167C51CD39FULL, 0x2BF56F94406D26B4ULL, 
            0x8C3E5ECEE8E28F27ULL, 0xB924A83352F5BA3EULL, 0x978319B23C4AAEA4ULL, 0x166EE59E7BEB31EAULL, 
            0x058ABC2988B838A7ULL, 0x26469FBB59D87142ULL, 0xC723B2281CD2B7A6ULL, 0xB39BB91DAC9CFED5ULL, 
            0x7BDB6E03F0B9CFD5ULL, 0x1BE2BC87739E989BULL, 0xEAF38AA558535C00ULL, 0x94414868AE91C4E8ULL, 
            0xFE71D5BD0EF0A591ULL, 0xA894DB6A2A5C6E11ULL, 0xCE280FA7DB0A8130ULL, 0xC69E52A672603805ULL, 
            0x75D8AB9F9A2AD7ABULL, 0x0B4451F79AACB6DAULL, 0xEE22AE23138CED16ULL, 0x26F1F7B8264D8397ULL, 
            0xE28941E65B066658ULL, 0x7F249306E636DEADULL, 0x98744D0645E2D0EEULL, 0x5D192F80B361BD5BULL
        },
        {
            0xDC74EEC50FF28304ULL, 0x93933131F99F6A90ULL, 0xAE6F7ED90DFBFB2FULL, 0xBE2A05ED678B2D04ULL, 
            0xE5CB91424DE526DCULL, 0x023866811F8698A8ULL, 0x8F6D37EABAC261EBULL, 0x360B836BC929A967ULL, 
            0x61176F557243DEB1ULL, 0xF1E288DA491BB93EULL, 0x1B6DF54168595C8BULL, 0x98200AA7662D93CCULL, 
            0x8E874D838E7355EBULL, 0xD8ABF2BBDDAE780EULL, 0xB96E1FBC907DEADBULL, 0x1DD9FD881484C744ULL, 
            0xFDF261AA1E2D7CC6ULL, 0x350B7AF0F3CFE341ULL, 0xA24EEC7B4BC4D53CULL, 0x25916C10E7F5378AULL, 
            0xBFE8321792FA3F1AULL, 0xF3E9A9270D704ED8ULL, 0xE0538BA99D781F3AULL, 0x54200A09C975F7CCULL, 
            0x31B7BEC78C689A56ULL, 0x96A23718F5F0E90DULL, 0x55E87DE4B0353FBCULL, 0x42656D944A2644CFULL, 
            0xF016620250023308ULL, 0x9FC2E04E3D39F0E0ULL, 0xD54B236629432D46ULL, 0xDDF750172A46560BULL
        },
        {
            0xCDE92180F2E5DADFULL, 0x31A44658DF2A540FULL, 0xC05BE458AC9A0787ULL, 0x2E1DBAA827BC0563ULL, 
            0x517C8C311D978C38ULL, 0x1BCB78A66CA4527AULL, 0x1713B906F8A04E8FULL, 0x498B0FFC1064FBDDULL, 
            0x0148AC07B11A2AFFULL, 0xC7A7C91AE9935819ULL, 0x476D932B9E523EEEULL, 0xC56C0F14B1624487ULL, 
            0x3A9811214C754C27ULL, 0x7FC9B8A1FD7D083BULL, 0x18C6BDF76ABF4A93ULL, 0x562F304886AEE49CULL, 
            0x5AEB5C09B76716C6ULL, 0x0D5C02EF7E5ABA28ULL, 0x77AF54C26E0D87F4ULL, 0x055BAD6DCEDAB954ULL, 
            0xDA66ED3CBD12A442ULL, 0x1BFF5ED4116C9A8DULL, 0x56A3D3D8A5CAB793ULL, 0xE80585370471B44AULL, 
            0x3CEBCD470E8717BBULL, 0x84EF3D0B95F55F0BULL, 0xB36239D093B82ED7ULL, 0x2278A4AD8A06352DULL, 
            0x579433912B77D16BULL, 0xE263B723D74FF546ULL, 0xC7216D534056FF40ULL, 0x11937F6216A1D9E2ULL
        }
    },
    {
        {
            0xAE101816024D82FAULL, 0xBF0C31730FC14DBCULL, 0xDA5941C6EA500114ULL, 0xD0328EA8CE9E86FFULL, 
            0x802497B4D341588DULL, 0xED5393A739CF5263ULL, 0x4BE5D475B1B46367ULL, 0x1E5FC9F8FF8D1E7CULL, 
            0x219B99DBB94518BCULL, 0x66FA5367482F0A89ULL, 0x20850A1F546956CBULL, 0x7C3DF816ADBF9DB9ULL, 
            0xAA7AC064F1D26501ULL, 0x6074C38085FA424BULL, 0xDA6DB500FAFF8BE0ULL, 0xD1B8B84DA6CACB96ULL, 
            0x37620BEFD86AA12BULL, 0xD2505AE6EC970844ULL, 0xD488BE32236DB1F9ULL, 0x89D5385F06D55438ULL, 
            0xDEED94CBC574D8FCULL, 0xC1FD5F84A3EE8B3FULL, 0x523CF3200CFEC56CULL, 0x0EFFE0559CF7063BULL, 
            0x2D18A191773338B7ULL, 0x59BCE5A31A65FF0FULL, 0xD8FD2B80A048510CULL, 0x8E8E83ED25057C5BULL, 
            0xDFA50AE694B3C960ULL, 0x2C451652676E7564ULL, 0x862313A54AEB02B4ULL, 0x9A2E3D1356CCEEB6ULL
        },
        {
            0x178BAA730CB9D5DBULL, 0xAFA1EC90F4D950C1ULL, 0xE4086A6462649EBCULL, 0x0847136FBBD2A08EULL, 
            0x9A0F1A447DA13B26ULL, 0x3A2B3D6C66B72F2FULL, 0x6F8DC148C5EA64EDULL, 0x6CC76E4599E68EF7ULL, 
            0xB09A487DC1E9564CULL, 0x3D31E1AEF71E96D9ULL, 0xB14CD2DB9F3E9803ULL, 0x8762D2F891471FBAULL, 
            0x6DE9345079992B86ULL, 0x999093317B119FC6ULL, 0xE6950B12922720CFULL, 0xF39BC258048AFBCFULL, 
            0x5023D4F83871295CULL, 0x6810B4448E95F127ULL, 0x83F5D6029C049AC1ULL, 0xC31B8AF944DA0B05ULL, 
            0x70009E4D3C55D53BULL, 0xCFD352FF24004AFAULL, 0x5F4B6BE0061FA14AULL, 0xD4CD29EE807AAA35ULL, 
            0x4DE6A131E4ED8BF5ULL, 0xBF7AD473F781321AULL, 0xDD219B278DDFABE7ULL, 0xCDD671B592AEEA6AULL, 
            0x9836B2D0FE2F2546ULL, 0x703304E142C4DCB2ULL, 0xB2A96057241C246EULL, 0x44E31E40E2312E37ULL
        },
        {
            0xD3662C79835C2FB6ULL, 0xB9BD393C999AC263ULL, 0xB3EBA2EC923498DAULL, 0xD8C43914EDBC32C9ULL, 
            0xF4CE5C775FED72F1ULL, 0x72E657D064EB12A3ULL, 0x3D36F286A222FB71ULL, 0x69F8249687243D14ULL, 
            0xCA14EE8FF2D4A838ULL, 0x0D2D109D8CAF0059ULL, 0xCF8C81B75A776366ULL, 0x8C1B189812E199D5ULL, 
            0x4F16230FE71439DBULL, 0x51778082F45F67E2ULL, 0xDF9710546AC5F2D1ULL, 0x57672C8A226A26DEULL, 
            0xA9E8628C0E672A1BULL, 0x15303A2C4200E2F4ULL, 0xFA76610B70C2089DULL, 0x44DAB42F41069660ULL, 
            0x07396A9EFC0E631BULL, 0xA916D70C791293C4ULL, 0x5D89A053093A7140ULL, 0xABDAA498716C7342ULL, 
            0xDD678226AA37BFC7ULL, 0x41C7F53E1A727995ULL, 0xA2BE37756F364E6DULL, 0x2D7B2B3F05ECFDD0ULL, 
            0xB8EFC49618C9DBB6ULL, 0x1AFD4DDB25D17E0BULL, 0xE6383DFEE098769EULL, 0x6343469963F10257ULL
        },
        {
            0x3C34183F2059F56BULL, 0x0310D5324572F25CULL, 0xD6F1AF6EC468F872ULL, 0x210DDC928249A1A7ULL, 
            0x69933ACF4BDFE78BULL, 0xD5274C3CF7705D5DULL, 0x1670BA3A2F0A4F98ULL, 0xDACD56453EBEB844ULL, 
            0xBBA165AE71A9709CULL, 0xB0A6CF18B9DAB323ULL, 0xDA2C27ECB18655B5ULL, 0xC1CEB7B0120068DEULL, 
            0xAC610B191B9CD8D5ULL, 0xD2613BBFFA746E42ULL, 0xEAFE4B338E19E0CEULL, 0x163BAF35C420E02FULL, 
            0x328005BA0FB11EE8ULL, 0xF6AF3D60F7F86C7FULL, 0xE257C1070F4FBB7CULL, 0xD5568CEA8252AEABULL, 
            0x88C2A48215DE1C01ULL, 0xF2A6A743B6EE595BULL, 0xD20CEAF2CBEC373CULL, 0xFFB35072A6172125ULL, 
            0xFAC97DF0D0AE0E38ULL, 0x975244427CFAF1CCULL, 0x7B48CC18E29C7E97ULL, 0x121FBC34AA97E96AULL, 
            0xF0E34BA96726719CULL, 0x73BA64379A07A7D6ULL, 0xF774AE4595E9CABCULL, 0x66F761FCBF60CA04ULL
        },
        {
            0x74259E817BB9A886ULL, 0xF046058BCB96797CULL, 0x179132FB16C6BF73ULL, 0x485036CF6B1BDE0CULL, 
            0xF4C43BBA33235759ULL, 0x7C8145E723EE3CF9ULL, 0xE352B385611FB476ULL, 0x9B47DD8027FF3135ULL, 
            0xC2343AF5F0639321ULL, 0x1A8E74AA055CBB73ULL, 0x8FDC8E682EB3E877ULL, 0xC8621313B9D73A31ULL, 
            0xE120620A26C9A535ULL, 0xD6ECC02CA0636443ULL, 0xE8A8FA81577D46E8ULL, 0x4CAFFECD34107366ULL, 
            0x20A0C97226CBB096ULL, 0xB7A86CCF2C29331DULL, 0xF828D11D5F5DCD68ULL, 0xBD734CCDB5D69CDFULL, 
            0x2B5DB931EE8D3017ULL, 0x3C803FBB0E50AD49ULL, 0x6A2C2950FE839465ULL, 0x5548D03595F761DFULL, 
            0x7377B2E0AC7035B7ULL, 0xE62538B21191060CULL, 0x15681B8AE76BC7ECULL, 0x17966A5C220DBB35ULL, 
            0xE7B447D77FC7EAF8ULL, 0x76A9FF9539694634ULL, 0x0FFF193322C206DFULL, 0xA21590AE42F14B6DULL
        },
        {
            0xC353EEDA15DD6D3BULL, 0x6AD303231DECD7E1ULL, 0xE53A75E8CFBD91E5ULL, 0x44296E21B39ACFBFULL, 
            0xE58CA711D718649CULL, 0x8BBE36212D974586ULL, 0xE730ACEF0051B885ULL, 0xB2484A795F28C321ULL, 
            0xB0CA7B0FE63E4D97ULL, 0xEBFE9FEF9D9CE1B1ULL, 0xACFD65D03CBDD429ULL, 0x6A00D092590B78F6ULL, 
            0x33CCE2C4F137DB90ULL, 0x5A359DDDF4FBF1D5ULL, 0x8B6EC21A2AEBEB49ULL, 0x39A7350E6B590F9FULL, 
            0x8C6C096ED2EC9446ULL, 0x0679A307572782CBULL, 0x6A17C65CE1305710ULL, 0x54086F989B412156ULL, 
            0xAFCFA14DA7974D13ULL, 0x45D8AB51C888C739ULL, 0xB994CF525DF9A2DAULL, 0x06836A5BAB9CB168ULL, 
            0xFBA5ABF96A5D4945ULL, 0xB805633B9D175A9DULL, 0x5FE901155B6FBB7DULL, 0xD75C58A1A0CE73A4ULL, 
            0xAD82A07231F6A517ULL, 0x3563B16F2E39A3ADULL, 0x1199196186C124BDULL, 0x449C566E28F3166DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseDConstants = {
    0xDC01F207A2F46B08ULL,
    0x972B4F99C9963A6FULL,
    0xDAE04DDA96FCCF75ULL,
    0xDC01F207A2F46B08ULL,
    0x972B4F99C9963A6FULL,
    0xDAE04DDA96FCCF75ULL,
    0xCABEBAAC63C392DDULL,
    0x1D44D98B53BF3604ULL,
    0x26,
    0x8B,
    0xB4,
    0x6C,
    0xAE,
    0xA0,
    0xA0,
    0xC2
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseESalts = {
    {
        {
            0xEE77FC5198D26CB4ULL, 0xB43A9C3F9FF11A0BULL, 0xC7526F949C163018ULL, 0xD2B79490F42D1912ULL, 
            0x50DE7C4CD7C398A0ULL, 0x2C5C6B6A60109F70ULL, 0x51A13364425AC595ULL, 0xE6315CFB79986DBBULL, 
            0xAA7942FA771CE1E1ULL, 0x3DFD9E5623D93E20ULL, 0xE3139216A8AD1A75ULL, 0xC7F326B6A4A0EDD0ULL, 
            0xBA2BBDF269706CAEULL, 0xE28348D8720A818AULL, 0x2791431EB7460DFFULL, 0x3AB2709BAAF7B2B2ULL, 
            0x34DB846E332BBC1DULL, 0x59A723CCE0682AD6ULL, 0x7F51ED742734FF58ULL, 0x76AB8A8864E6ACD8ULL, 
            0x3B08CF69AE55427CULL, 0x51745E8D8D7206DCULL, 0xFF8020CDEACC0851ULL, 0x9DA689E53FA30BABULL, 
            0x2F8C55CA60E55B67ULL, 0x611DAA19E95D606DULL, 0xB38199209794819FULL, 0x0C0085F11D343C82ULL, 
            0x5DF67AAC2B69983AULL, 0xEAB80CCBDB368998ULL, 0x818419434BDB4059ULL, 0x86AAE64E43C1EB68ULL
        },
        {
            0x198E16CA0379E4BFULL, 0x63E050FE9662CFA5ULL, 0x0812F9CB235AA80BULL, 0xD1E61B23652A3362ULL, 
            0xD55E702993152195ULL, 0x9454F4D3CB4661CAULL, 0x470FCDDC2946641CULL, 0xE328316D758D6A1FULL, 
            0xB9C0AFCBED375438ULL, 0x5FE02064C0D362F0ULL, 0xE4A205E6CCBC4D8FULL, 0x4D6CF1529CFBDB7EULL, 
            0x71E4A1CE7F7E0114ULL, 0x8EDD9EA63B1797BDULL, 0x711532D099095506ULL, 0x1B7C2938D44C6297ULL, 
            0x357AC6647906E19DULL, 0x2665A58A69FA9160ULL, 0xC78001899751A04FULL, 0x1132FA91DC8017A3ULL, 
            0x088E7C46E7B3AF26ULL, 0xA49077B0FCFCD2AEULL, 0xFB3F7582D825D240ULL, 0x288E6744687C07E3ULL, 
            0x7B673C670753D0D2ULL, 0x93A8343AFCFF0AB8ULL, 0x2184F0BA4DE0AD39ULL, 0x255584B4030BE0C0ULL, 
            0xFFB4CB9B432CD51DULL, 0x9F57F3792C622F19ULL, 0x11E785CA9EA4EA86ULL, 0x2DF65562FAD0F8A4ULL
        },
        {
            0x39F10AEB71B0B8BBULL, 0x711089A499F861AAULL, 0xDE8202A69327A020ULL, 0x01A88A236B8D9F63ULL, 
            0xE6D7C8BD8E6234B3ULL, 0xE9FCB273C569B30BULL, 0xF88378F816F261BBULL, 0x790EB9C4B79FAAD5ULL, 
            0x10EB2C85A5AA87FBULL, 0xBF85695C7EBAC7F9ULL, 0xCCF1E87315983858ULL, 0xE61A2EDC92FBB051ULL, 
            0xB84F663F7B01FB6EULL, 0xEAA19960DDB09A85ULL, 0xDF318E9207F30A88ULL, 0x45588745E50A8D3AULL, 
            0xCAFDA752F42ACF09ULL, 0xF31B4FA25B2F5607ULL, 0xA335929932C4531EULL, 0x8F019E49D4CE8F3EULL, 
            0x83A25697FE0EC7E7ULL, 0x267019F5A1DD6344ULL, 0xE5B69BCDEFBFEF34ULL, 0xDAD7073B9498F420ULL, 
            0xECEAF6D02A0C3FE0ULL, 0xB7925DFF9D691312ULL, 0x7F454E6119DF0A4CULL, 0x82A99D29CFCF48C3ULL, 
            0x136AEB8EF19E9952ULL, 0xA6692581658D6A56ULL, 0x09875BED35598A89ULL, 0x2186060A6EACEFEEULL
        },
        {
            0x00510D8E1D1C7E41ULL, 0xC1C37240A2B0B378ULL, 0x14B52FF4ECBD4F91ULL, 0xAE6CEF2C43583AE2ULL, 
            0xE0F59AF58264CB40ULL, 0x1E37412334A5FD33ULL, 0xEB48860CB86B812CULL, 0x5F59369FB4015114ULL, 
            0x6C384569806005ABULL, 0xA184771B2965DF14ULL, 0xD982E2BEB35F6F90ULL, 0xBBE0AFC1A0487DCEULL, 
            0x50A3A5261B02822DULL, 0xCDDAEFAEA814F008ULL, 0xB8246844319148DFULL, 0x4E46FE1B66F027A5ULL, 
            0x18A943AE7454D924ULL, 0x355373DADF0AF98FULL, 0x2E5DCE5F5A4B8F1DULL, 0x0B48F70521334626ULL, 
            0x04816A4963858933ULL, 0x4286BD71AD8C2EDDULL, 0xEB8D431C16B015DDULL, 0x56833E073FE3C598ULL, 
            0xE3552C3DFEB28919ULL, 0x94EE00D461D72B59ULL, 0x6B66C132F58B374DULL, 0x88ED27F094F8B9BEULL, 
            0xAA1B3A3D37077D6CULL, 0x738B57D986469C07ULL, 0xCBA15E1A56E01E86ULL, 0x09B16FA57271F388ULL
        },
        {
            0x30F7C7D8E08CA8BCULL, 0x264443B98F7310E1ULL, 0x95F44644F8FEE329ULL, 0xA9E2F24B7908C697ULL, 
            0xB3B3D2083AD15024ULL, 0xFBF5E3DB328FDE50ULL, 0x6CD9D15ACFB074B4ULL, 0x29372DFD001A3861ULL, 
            0xE743765D14E5445BULL, 0xFC75CEB9DFD469DEULL, 0x5DBF7FEB7BF94749ULL, 0x76F95C3E13473C63ULL, 
            0xC0401F39947B892EULL, 0x608484F937916588ULL, 0x87F5ADB05D9829BFULL, 0xBCD93985BBA63F9EULL, 
            0xE0DA253E1706C726ULL, 0x88E3BCD65EC7C4C9ULL, 0x9B126C0CA1796044ULL, 0xCB76AA62D1EBB4C8ULL, 
            0x7037DCCFD827DE85ULL, 0x4F41CFC7710836D3ULL, 0x91E547A694EA37B6ULL, 0xDB9A331C9819C490ULL, 
            0xC106DC1501E44C16ULL, 0x3E2769DB5725C856ULL, 0xEE4695663DE5C196ULL, 0x4C07D88F361B87FAULL, 
            0x37DD733FAE13766EULL, 0xAA71901CFAC5D3D4ULL, 0xF88BCE04FBD8DBAAULL, 0xB56B651E0A01F1CEULL
        },
        {
            0x231E57B74213D844ULL, 0xB8A3A17EBC11F2C0ULL, 0x21B41F93AECE6FB0ULL, 0xD5F3EDD433700D8FULL, 
            0x80BCE026C0E93109ULL, 0x53B72F0902DF006FULL, 0xD9E4A547927BA70CULL, 0x376CBF384D92B0ECULL, 
            0x525F645234630D04ULL, 0x2284084199533955ULL, 0x9590BE8654680CFDULL, 0x1B3BAE62CADA87E3ULL, 
            0xD056A07B67787588ULL, 0x889FB9B8AE8E6C4DULL, 0xBCBCFDCE4AB762CBULL, 0xAF4EE644877CC171ULL, 
            0x088003D179862420ULL, 0xEB7D2D42867FFFAAULL, 0xB11B31342050C1D2ULL, 0xB6B5A9CF7F8453BEULL, 
            0x6DE0E8B4C733BFA5ULL, 0xAB958653ACCA3634ULL, 0x31D0891DB1254569ULL, 0xA500ABF1A647CDF8ULL, 
            0xB3043E4D4E13C8A6ULL, 0xC8B1F7C652D93AA0ULL, 0xA0DE34CB9FC7C09AULL, 0x54DEFB8828349A42ULL, 
            0x3F258B3CBEEF2F19ULL, 0xD0D652EC3EF14590ULL, 0x45D05B766D0C66AAULL, 0x916600427BD3C841ULL
        }
    },
    {
        {
            0xAD5072C7290F9631ULL, 0x22516C8C597D3D15ULL, 0x1AF25711EEA73E81ULL, 0x392B561B13196F72ULL, 
            0xD747A79A7263398CULL, 0x3D11C3CDBABED85AULL, 0xA13F917C52F91E1DULL, 0x811EC72DDCF7FC0CULL, 
            0x6CE688ABFAFC03E3ULL, 0x9C8847DB15199735ULL, 0xB694DB1787647977ULL, 0x060DC97655197490ULL, 
            0xBE8A5A530B59B2D2ULL, 0x3C71B528A0EAE8CAULL, 0xCC59A1ACE00A3DF0ULL, 0xC91FD9D6821B46A1ULL, 
            0xEB140FA3D17363F0ULL, 0x9F28EC74B95A7847ULL, 0xE78F7219CA0ABCEBULL, 0x45301D9565AE1D96ULL, 
            0xE42E5A52555E4939ULL, 0x9132F7B9307528C5ULL, 0x75F27494AADC11D1ULL, 0x89B82931D257655BULL, 
            0x033082C99B12EBCCULL, 0xDE40C2FED9ED5EF2ULL, 0x465766DCC112D911ULL, 0x21644E535173ABCCULL, 
            0xDCDDB832CE1C1E8AULL, 0x64CA566DB7ADDD2BULL, 0x3D51A2ED115E60C4ULL, 0xDFC9B21E5359734AULL
        },
        {
            0x05FC1AC73DCAC1B7ULL, 0xA31FFF6E6F8ED7F0ULL, 0xAAE9A59E6147BD44ULL, 0xDD11E4A5C8A2A7BBULL, 
            0x388D3188A93119EDULL, 0xEFF3CE81488852DCULL, 0xD729389417C0730EULL, 0x84305A951DFF6857ULL, 
            0x0DB1BBBEEA0322CEULL, 0xCAD77F2A2927751CULL, 0x91A57F92904A40C4ULL, 0xE33F4CD2B03BDE3CULL, 
            0x74FE482A2D7E301BULL, 0xBB538544F5CF4269ULL, 0x3F1D94F9E551CB3EULL, 0x0C6DB100740CC9A8ULL, 
            0x7E49C6FA273F39FCULL, 0xBE13CC4443F37000ULL, 0x593DB3F255C2331BULL, 0x89FBDEAB970EFCBFULL, 
            0xEA4C9BE38F00413BULL, 0xCA89F12E9E84CB66ULL, 0x31B40F283103581BULL, 0x2E82E96481F154A8ULL, 
            0x102C8E5A5C218837ULL, 0x2FFF79DA46B3DA8DULL, 0x5D2A359752ED346FULL, 0x111A9000C64E2C1DULL, 
            0x225D6D60CF022D57ULL, 0xCA86CBFA7BCB140EULL, 0x2EF86BA0758D9D96ULL, 0x1F6511B5A79F4972ULL
        },
        {
            0x3008F46185A74325ULL, 0x28ECEF09BDF5437AULL, 0xDE4BB2DD982D4561ULL, 0x75016BADB45DAEA6ULL, 
            0xC87B5BCF5E5841CEULL, 0xCE7CB736F6A8F0F5ULL, 0x601CAC11177BEF9CULL, 0xC9F99D747491D53BULL, 
            0x743D83BD0BF04E72ULL, 0xEF665F27CA3BF82FULL, 0x9201BDB12743F1BFULL, 0xD64D5ED71856E883ULL, 
            0x049B8A010F0BF3E1ULL, 0xF531DB7F945EB7AEULL, 0x1E29E70322B88DB5ULL, 0x8EC13DCE3B2857B5ULL, 
            0xA9EF39BE71EA4608ULL, 0xCA48C87FA3620AE4ULL, 0xAFCCB0FA62B84C66ULL, 0xB889FBF0DF6B23BBULL, 
            0xF8B768555A5AC56BULL, 0x00B0A6D5A80F4088ULL, 0xE97236AC75513437ULL, 0x6D1BCA2F05AA7C3CULL, 
            0x5606767660670848ULL, 0x97C4B6ED6F887B8FULL, 0xEA3D108DDFA44FAAULL, 0xDD29EC83A41B472FULL, 
            0xDFB0790918B4B452ULL, 0x5A4F20F06531DD0BULL, 0x2792A77652CA5552ULL, 0x04479D0B649A0361ULL
        },
        {
            0x444490EB4AC9D7A2ULL, 0x964F0CA4302C9593ULL, 0x7234D588DF0A901EULL, 0x4647052631E47ED2ULL, 
            0xD90AD04E6FB4DD9DULL, 0x104E8C99EC3AD9EEULL, 0xB12B281B65FA6F2CULL, 0x32C018FB5249F9E3ULL, 
            0x60C03D28AF33DBACULL, 0x6B9A906F4BD11DA9ULL, 0x4AB7D2459460741EULL, 0x274CDE49427706E2ULL, 
            0x04023C30319975DFULL, 0x613969EA4D08FED3ULL, 0x77233B3ED2C800B3ULL, 0x915384D49EE08C0FULL, 
            0x0EB66C008D6FCF99ULL, 0x7DD1A7512A688B73ULL, 0x6F9D963558981600ULL, 0x8EC7293B7D9AF44DULL, 
            0x4055E867EA1E91A2ULL, 0xBF594240EC30F06BULL, 0x7345F3C44DB3E449ULL, 0x1B116653D24B4093ULL, 
            0x1B634B742AF26D4AULL, 0x23148782CC2F44A4ULL, 0x14014D314A54947BULL, 0x59F7724157DA4FC8ULL, 
            0xC765E998F246B3D1ULL, 0x7EC52CC37F0B6550ULL, 0x773F79026AD7BFC5ULL, 0x4F6417029686FB98ULL
        },
        {
            0x4475992A2BADE557ULL, 0x6764CBE34C2A175BULL, 0x6E7F541B4CD85CDEULL, 0xEF753A1084D3DF25ULL, 
            0x409E0F087B755560ULL, 0x4C6D9168921F1D07ULL, 0x51248FB818EB5ADCULL, 0x08DE96FA0EEC3268ULL, 
            0x791653F5133379BEULL, 0x73029F6E55BC07A0ULL, 0x4B18AD18B24A8951ULL, 0xA45466A41EB793B1ULL, 
            0x39CAA7032B00A72DULL, 0xC5103CA154E158CDULL, 0x2D06931ED21CF3F6ULL, 0x1D1CAEEE866CB28BULL, 
            0x7C5B3323E49FC1A5ULL, 0x8A4703AB3BF2B915ULL, 0xAB5A42C4CB25A474ULL, 0x4A4355F4B2D0DB0FULL, 
            0xA277A5D398117104ULL, 0x2456E6ADC1C59A21ULL, 0x2D0F4102F411CC8BULL, 0xD72DAB530CC65D65ULL, 
            0x2E79D27A55F22824ULL, 0x7F189589444AE41AULL, 0x5620294E5309F241ULL, 0xBA3D35CF9CB21093ULL, 
            0xF36F6086D9ED0CDCULL, 0xD5D6219C71BF0427ULL, 0xE03D65BD830A7342ULL, 0x4481E2DEB51BFAA7ULL
        },
        {
            0x0AD426E60C87ACFCULL, 0x75CCC12B1AE09A0BULL, 0x7A8B938D0984B760ULL, 0x5B4C22ACA4B77150ULL, 
            0xF94333CC0C8A69D6ULL, 0x038D41E2B768ED09ULL, 0x4FE7EF44FC793BC3ULL, 0x8AF7C88012676BBEULL, 
            0xD9760508CC552C5CULL, 0x0A418925B4098D82ULL, 0xE2A91E2A03CF0A69ULL, 0x7AB416FDE699F4A2ULL, 
            0xF7E408FC776F6674ULL, 0xCE2CEE10A1931ED8ULL, 0x093FC868177C397BULL, 0xCEF3CA26C0845472ULL, 
            0x9CB163133BD327F6ULL, 0x6EEF63E4CD0CCC56ULL, 0x299867AA9A3BFA52ULL, 0x7B2F8BC3254E1041ULL, 
            0x433EA7D4324EFDB7ULL, 0xC796CACE075B9B39ULL, 0x7F81050B7CA6E29AULL, 0x0D6CE8F8F515BB2AULL, 
            0xF53EE71E91F0E4A8ULL, 0xA43AD5398E4C62C7ULL, 0x5EBA9921FBA050ADULL, 0x7B17F32B41264E05ULL, 
            0xB936A89986805F14ULL, 0x2F8AF8D80CE9C47FULL, 0x8411A7652315A224ULL, 0x78C26CDB06BDB1DBULL
        }
    },
    {
        {
            0x4D23693A558DF1B5ULL, 0x3CC1AE9BD65DBC8EULL, 0x35BD9F04817EE6C6ULL, 0xA71A86DD58C04546ULL, 
            0xD7A19527535746D0ULL, 0x7D3EA2900D61C93EULL, 0x5DA335680A8E6845ULL, 0x9F4803F5340FE012ULL, 
            0xDDA890ACB13E9D7AULL, 0x3D44B55B299F686AULL, 0x5C9C53D16FDE0847ULL, 0xBAD18AFA3F9E6580ULL, 
            0xE3520651360B2777ULL, 0xFC54C73A0B1DA8E5ULL, 0xB5BE429F6002051BULL, 0x8D9CD23CBD584C9AULL, 
            0x005532DA6C434164ULL, 0x664219FE39E6DD8DULL, 0xFDC797366B419AF9ULL, 0x428DBC0D7DFF39F9ULL, 
            0x37024CFA14407623ULL, 0xBF0E5FB8ADFB4D23ULL, 0x9DC0FEBCDD246C57ULL, 0xA503B61C7C43A1B9ULL, 
            0x8661E3C2F86F6496ULL, 0xCD76C92B35A87A8CULL, 0x46D26415A7A62DFCULL, 0xC46266DF009D8ACBULL, 
            0x19D7738F36B69F98ULL, 0xEEBAD8CB683AA3B0ULL, 0xE95E138E13A8C259ULL, 0xA194C8133C5A12A3ULL
        },
        {
            0x7FA7685D5391416BULL, 0xA97794031D4906B8ULL, 0x48AF35E840DDA8EDULL, 0x999B51BEF4DBEE99ULL, 
            0x014F55043EE89766ULL, 0x8778F7E602B12557ULL, 0xC05FC419893C6CC1ULL, 0x6AC74818959B96D8ULL, 
            0x217C721F84698687ULL, 0x5BB915DF299DD3ECULL, 0xF244EBC6B49CDE13ULL, 0xD4FAADE763622F5DULL, 
            0x708E3706BC44F411ULL, 0x5314AD06856A7541ULL, 0x7A373CE86A377615ULL, 0x440A5379386B20FDULL, 
            0x76A8F1FAE29648E2ULL, 0xC310CBA857AC2FBAULL, 0xB06C354A0CFAE7B5ULL, 0xC5F9FA4E5A6627ACULL, 
            0x895198E9BF8D5FBCULL, 0x61408F58A033D9F0ULL, 0x565934B1485C1C66ULL, 0x8461F70BCF18A770ULL, 
            0x024C2353D1ED39B4ULL, 0x2CA4BC79C553F600ULL, 0xBAA3EA0AF3A4C735ULL, 0x255FA96D60373E03ULL, 
            0x59EDA4541814079BULL, 0xB22DBC5A23026AFDULL, 0x7C6FF38A224DCC9AULL, 0xDA99C29DD2C6DEC5ULL
        },
        {
            0x0A1DCF1904300420ULL, 0xAC012BC3020A9F8BULL, 0x5C0CD813E41ADC52ULL, 0x450A0E8A47CB5012ULL, 
            0xC735243907F24C29ULL, 0x7F04316EE4D6DD15ULL, 0x85F227457EC8C3A6ULL, 0x7AED45732A10D047ULL, 
            0xF2F5004FD3B5453FULL, 0x1C248BF90394E176ULL, 0x3BEDA0EFB30BCBEDULL, 0xE556E67B3B575495ULL, 
            0x1D979B8C6A385CB5ULL, 0xA1DF28ABBBC9E09AULL, 0x6AF97C103032F51FULL, 0x4C9479EC0C382C2AULL, 
            0xF565A39AE8BFA6FEULL, 0xB6B547864F2A5DCEULL, 0xB1929461B6BB5C57ULL, 0xF03015CA5D89FC81ULL, 
            0x1D7C1D119190C506ULL, 0xCD685E0BD0D8506EULL, 0x72DC35EDC3C264D4ULL, 0x6D0E57F024DF6B25ULL, 
            0xDC81284A07E4E867ULL, 0x0C8702074963FD02ULL, 0x3A1DC1DFFD11859BULL, 0x48A80A2706DD855EULL, 
            0x0C0988FCE7613F31ULL, 0x7E2E7DA7A20152AFULL, 0x6442AA9A687E66A3ULL, 0xBCAF482ECAE2FE29ULL
        },
        {
            0x14270A9CF702BC29ULL, 0x6011718CBB7B4A52ULL, 0x2BFBEE7BECFD287FULL, 0xEB0A9ABAD5CA9A9FULL, 
            0x9ED87611BCB205A4ULL, 0xE0F19E42D78AA56AULL, 0xF6938899222136F1ULL, 0xD057081EE211B309ULL, 
            0x307052FDC285E18AULL, 0xDD2FE8CCF804A42DULL, 0xC61F8695789DD05CULL, 0xC019F0E89054ED41ULL, 
            0x86604EC14076A5F2ULL, 0x2B5417ECA50ABF9BULL, 0xF251900F1BAF3ABFULL, 0xD9D00B5FE1C6971DULL, 
            0xD231B558AE5D9507ULL, 0xC98F50A9C6194D9FULL, 0x75189E8E0CE2D607ULL, 0x416841530CFF364FULL, 
            0xB9BC1B8434075F6CULL, 0x2AB8613AF2D3A851ULL, 0x6B25A94E0762C87DULL, 0xD9D2B376FD659075ULL, 
            0x50D720DA7C3D2F51ULL, 0xA447D7EEDB99F8C6ULL, 0xBB59F96D8755905CULL, 0xE11E962CCFDF2061ULL, 
            0x7ACF73240B61A891ULL, 0xD7EF20068EFD6F2BULL, 0x28D6CC9C1155CD23ULL, 0xD836AA35EE851EBBULL
        },
        {
            0x8B9A7CA4E26A875AULL, 0x93F56AA1C9C35E11ULL, 0x25BB0F96BBC21F53ULL, 0xC6004A87BF7251EFULL, 
            0x7582FBD91E71CF4DULL, 0x7DC600640227451EULL, 0x62778BC984E4E145ULL, 0x008E661ACA6C2F9BULL, 
            0xD66870306A8D049EULL, 0x198F5E1774FFA9A3ULL, 0xDEAA6FAD29E0CFD4ULL, 0xD4808CE3C4491B57ULL, 
            0x885B62C537712E6AULL, 0xECFAEC54FD1E4110ULL, 0xDF1DA42C5A30E0FDULL, 0x159E0F9597697747ULL, 
            0x182E9EAE875F96F5ULL, 0x8EA55DC7938064B3ULL, 0x81E1D5F894117B48ULL, 0x8D72C0E5DCC95FDAULL, 
            0xBA09AF8E51B83340ULL, 0x2C66C6DEB8078580ULL, 0x92933FD7A0FA48DDULL, 0xFBDCCB413D84A0D8ULL, 
            0x88C68BFAC6F99FB1ULL, 0xB93DA607B33AF60BULL, 0xBAD753C912D57FECULL, 0xB38C96588A1D1186ULL, 
            0xBEDC6DA45C6554FAULL, 0xE7BA922DD92BA33DULL, 0xA5C47230AD50AD1FULL, 0xC45153EFE9AFCA76ULL
        },
        {
            0x4C3965718DA0F732ULL, 0xEEFB389A5ACCEDDDULL, 0xD1AB1838FF2EDBDBULL, 0xFDB919C050CBA18AULL, 
            0x4FD57F6F6CF5F630ULL, 0x19A8E162F5178DF2ULL, 0xE959F6CEEB5FBDB6ULL, 0xE5BFD12BB7D42A1FULL, 
            0x80D387A3BF0D2BB2ULL, 0x1720ADF4FBF8F7A7ULL, 0x48E3EE5A837EC4BEULL, 0xA99007F0CDCE3CC3ULL, 
            0xA2D7D1B384F86E27ULL, 0xC2DC9103DD351B4FULL, 0x09D97F149FB1F94AULL, 0x8735B46388A5CA7FULL, 
            0xE039B01C75B0339AULL, 0x1826F6B65626C563ULL, 0x75600D06E792544CULL, 0xC6F72CDF0B2D5159ULL, 
            0x8E3EB9B38D5D52C0ULL, 0xA2A90150A480E8B4ULL, 0x878EC9FB057CEE07ULL, 0xD67A635AF11DE22DULL, 
            0xA50936FC78EE016DULL, 0xD2EEAE4DD10D12FCULL, 0xCE20AE082CD49069ULL, 0xE0D9A587BC3A152BULL, 
            0x42A1FD55FC9641DBULL, 0xC2A43C5DBE395464ULL, 0x48C77E55E0533225ULL, 0x9C4A2F98EB383436ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseEConstants = {
    0x1A88894CA3C75B67ULL,
    0xE33151718E2D44FCULL,
    0x0B4875DD7A7C1FBBULL,
    0x1A88894CA3C75B67ULL,
    0xE33151718E2D44FCULL,
    0x0B4875DD7A7C1FBBULL,
    0x20B1FC39409B1256ULL,
    0xE6A510E0DCAA15C8ULL,
    0x35,
    0x6B,
    0xF3,
    0x8C,
    0xB2,
    0x22,
    0xE5,
    0xF2
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseFSalts = {
    {
        {
            0x35CA4F43C7C2BA40ULL, 0x6C88B5F088A261E9ULL, 0x8C866A435F47EE2DULL, 0x2DA7922AF069721EULL, 
            0x03AB74BB50E4E78BULL, 0xA5CD8A07DF996FFBULL, 0xB726D2994FCA2C0BULL, 0x09E638DE7C3522C0ULL, 
            0xD7FF4325CAAC0589ULL, 0x949FB93ADC59A968ULL, 0xFFB034690583B675ULL, 0x0B99F9B3004F2C65ULL, 
            0xFA3930C1F71B04F1ULL, 0xDFCF984907A8B937ULL, 0x916986520CEC5767ULL, 0x244FB2F4DF0F8A53ULL, 
            0xDBDA928785B3099AULL, 0x295F7269A394B85FULL, 0x986C892575E7ADFDULL, 0x09E4407C16B8B31EULL, 
            0x2447A04547158B9AULL, 0x4B64D7E9317D2A1AULL, 0x35C56FCF67682B19ULL, 0x770F885AC5C02FCBULL, 
            0x64F97ABF76E23F6BULL, 0x3CDD8403E964B510ULL, 0xFF394F1C11B75464ULL, 0x77BE99A8196998E4ULL, 
            0x24586B5E644F14BAULL, 0xDA85C5805496104BULL, 0xF5C7D1365050F560ULL, 0x20E5A243D143D8B9ULL
        },
        {
            0x61803BE7199119DAULL, 0x1B2905D7D0579173ULL, 0x7771B8412911984DULL, 0x38AE82786C1C7D1AULL, 
            0x29EBD576B2AAABB3ULL, 0x28FEDDEEB6933B1FULL, 0xA08A935E6448EBC8ULL, 0xEE4A161A511038BCULL, 
            0xECDDA75023E2AD00ULL, 0x283F7178E39C8F15ULL, 0xE4D6362A9EE3B75BULL, 0x33E9D83F4BD79254ULL, 
            0xBE27D822580D36F8ULL, 0xEDC318CB01CCF6F2ULL, 0x8E5E05CFF2E933EFULL, 0x2C6CFC64C8EF7798ULL, 
            0x340A03AF151D93D5ULL, 0x586AA5D9A9D229A3ULL, 0x6F3B728380D7B7A3ULL, 0x9794B1A95D9080F3ULL, 
            0x7DCF352099591491ULL, 0x63BC77E3A7B8B019ULL, 0x75ECBD7BA1F22A4BULL, 0x389309F3B0BFB4E4ULL, 
            0x45758855F800ED5DULL, 0xDDEEBE3ED70A8C29ULL, 0x404EFB6120204803ULL, 0x8151A483200BCF0FULL, 
            0x3D2A4BF3824533F4ULL, 0x8CE28F6805739119ULL, 0xCE8B363F84048A82ULL, 0x47D75BC59ABC0AC9ULL
        },
        {
            0xF59DC47A2F60FDE9ULL, 0x079EB3062FD28CB8ULL, 0xB46BD56945C3EA40ULL, 0xE97AB010C85BB681ULL, 
            0x593568D3A5977BD8ULL, 0xDFDFAA4E9C23E173ULL, 0x6FD11724527EAF83ULL, 0x15EF191142079DC3ULL, 
            0xC2012AEB93B20FB2ULL, 0xE0E50507D2FD36A9ULL, 0x0C51ED620E8B4D29ULL, 0x710BBE271922404BULL, 
            0x156E14C7BB30A55FULL, 0xA34F8654049903CEULL, 0xFC7210124B7A96D6ULL, 0x4C54446D100BD4AEULL, 
            0xD61A49503860BC9DULL, 0x17F4FFA637430F01ULL, 0xE27C92CF47818203ULL, 0x9D6F8D294AB6CC28ULL, 
            0x6BCE36C762904A51ULL, 0x4F2865B28F8D2F9FULL, 0x19B79F8DD6AB79A6ULL, 0xFF72654D49F098A3ULL, 
            0x8D9CF87327CCC612ULL, 0x29E129245EF16B39ULL, 0x3768786FD942A986ULL, 0x620A8EA94A57E878ULL, 
            0x1878096DA88FCACBULL, 0x6EB84F37FF717C1FULL, 0x354BD96D7F297245ULL, 0x9FCACF2B94C01EEBULL
        },
        {
            0xF6EA15EDD4505943ULL, 0xC0BFA64AEEC12FBBULL, 0x692779F22CBE0DA9ULL, 0xB431FD3D4EB6B319ULL, 
            0x4EEBFDD6262D7ED2ULL, 0x7930379A0C71E465ULL, 0x46CC70CCEA113EE0ULL, 0x35E83A67F81FF25CULL, 
            0xAE26F669F4BA771FULL, 0xD1EC879F878677CBULL, 0x4D26B9EF7DAA3754ULL, 0x40AB0A9D317E0E5FULL, 
            0xD97B25E3A00E2F05ULL, 0xCCE20F14054D53DCULL, 0x8D0629C46651429FULL, 0x81C0D59DCDF197CCULL, 
            0x033A94AA17F55039ULL, 0x9A787F863E811C07ULL, 0x0E13F84F4CD8F2F2ULL, 0xAA95137A69C9EA6DULL, 
            0x606112FA272FBD54ULL, 0x3817BB41A3573923ULL, 0xD5FDAE909C1125E3ULL, 0x22CD6212BED09D1EULL, 
            0xD503FA126785A3D0ULL, 0xE9D322AB2FB18A44ULL, 0x53F4DDF5F46BBEDBULL, 0x712AB6F65B3C16AEULL, 
            0x0AC7F976E8AD88D0ULL, 0x4ED19D3108FC78CFULL, 0xACBF8ED3F46204ECULL, 0x4DC6E93D39B1329CULL
        },
        {
            0x27C50B65730E5715ULL, 0xF97F5839C48242F0ULL, 0x90C944119BBC8B3EULL, 0x245F848269853D1BULL, 
            0xC4CED6C3F032FE98ULL, 0x729BE7FDA59746D1ULL, 0xB2E614B749B1020CULL, 0xD46A067899AF250FULL, 
            0x02DCF511BB64F319ULL, 0x87C65C059930780EULL, 0xEBCE795E0B990E06ULL, 0x564F54A84F43B537ULL, 
            0x7D23147BA4CE94B8ULL, 0x0228E5AE49742F0AULL, 0x204B46473A2334DFULL, 0xE479AACC09330291ULL, 
            0x6ECE5C1B57674C43ULL, 0x3F8F4C4F77D7A579ULL, 0x8CDAAAE21CF8F263ULL, 0x499AFD40C0D5A9CCULL, 
            0x0ED8550AF307387CULL, 0xEC8092EAE7837D7FULL, 0x09CE9048066C9544ULL, 0xA508AD73CC41BBEDULL, 
            0x8A9D4E851446767DULL, 0xE5CE6D4966DD0E07ULL, 0x92C822086C6DAF5EULL, 0xF5B017DAD1E13ECDULL, 
            0xDCBB6C7D0A454B0EULL, 0x41342A05BB3C841BULL, 0x1C49EA357E9C6FEDULL, 0xF66CB2DCFEF1BC26ULL
        },
        {
            0xBE528CDC5E3704C2ULL, 0x48084B7AE1A72A30ULL, 0xB109DD8D3DFFCA5EULL, 0x2A8A51F0A989C8D7ULL, 
            0x518B07E373A3511AULL, 0x925BAB992E32EE6AULL, 0xE71882F98C7F7E63ULL, 0xFD48DDD8AF1EABE2ULL, 
            0x091E31184388710DULL, 0x17DD79F2A401F0D5ULL, 0x7667F1728C104BEAULL, 0x1E4A3207EF3226FCULL, 
            0x513214B8ACAF25FBULL, 0xF37989CE238145D9ULL, 0xD24E6B3A79FB0F7DULL, 0x7BD84102F0E96176ULL, 
            0x3F92A1456ED69CE0ULL, 0x1385656119B32944ULL, 0x2FA05BE59D9F99BBULL, 0x6941C4C160CF44E7ULL, 
            0xEB75B4A4E596926AULL, 0x9B49CD4A860B1244ULL, 0x22E12801FE194C26ULL, 0x902FAC9F2173AF9AULL, 
            0xBB1258E8C60BF304ULL, 0x6288E220E0904422ULL, 0x35B1E14FD75C0603ULL, 0x68D571DAA1C5A418ULL, 
            0x9F87DFA86B775400ULL, 0x1871CD19367F45AEULL, 0xC6A2E2253A58B43EULL, 0xA354E35F31CB859FULL
        }
    },
    {
        {
            0xC2994941101F31A5ULL, 0xD75D1F66B9E63B6EULL, 0xEF37F0027FE40476ULL, 0x85B43ACC20C3F60EULL, 
            0xD65ACB9D09ADDF41ULL, 0x301F7B255ADE8881ULL, 0x3925FB7F00BD3350ULL, 0x73D3EFDDA8DFB25DULL, 
            0xEA1ADC00F04F19DBULL, 0xF1C00BF3076AD9DDULL, 0x1B4E940F19113F46ULL, 0xFDFAA25D1DDF5A1BULL, 
            0xB059E2945ACD40E8ULL, 0x74AE185D46E37FEAULL, 0x22A09B0602008C07ULL, 0x04288FA418A9CB3AULL, 
            0xD5C73BC4ABD930C7ULL, 0x3A22302070A59618ULL, 0x7AB9553301AD9CADULL, 0xE96FB5A4A4D1B591ULL, 
            0xC17B93B37FABDCAAULL, 0x5DB316F72717E8CEULL, 0x027363003B2DB92DULL, 0xAF240DF35D52E431ULL, 
            0x91C0A0189CE73824ULL, 0x5B70D6A8ECB7A3A3ULL, 0x51E78D48140B2E6AULL, 0xFAA4AE3617A9A324ULL, 
            0xD48F56D476277F50ULL, 0x0E8CBC2B22EC9004ULL, 0xF2D6C42EA2B7F4B6ULL, 0x1E4F5A2E011B5E33ULL
        },
        {
            0xE11B929E1D94D173ULL, 0xA9787FB6D84BAAB4ULL, 0xBDE88A1D588F1E24ULL, 0x97980C0A15865348ULL, 
            0x49D084C78EC733DDULL, 0x9EEABC035B350793ULL, 0x2282B24B6DF8FA4BULL, 0x382AA0BFFB4B7F90ULL, 
            0xDC8B649BB787D790ULL, 0x78778DE5AB5A4C9FULL, 0x3A640F90099FD37DULL, 0xAD58F6FBB068365DULL, 
            0xC1408208D5CB224DULL, 0x7ABD6DDC4AA35CBDULL, 0x8ACB467316770780ULL, 0x8BF9B4C449B8DF39ULL, 
            0x3489156080EC464EULL, 0x4999CD17B00440E7ULL, 0xF78E308C4EC1A9DFULL, 0x2DA52E3D50CDDFECULL, 
            0x00B662C82754D17AULL, 0x7E25CB263854C65CULL, 0x489D3141B5A02E19ULL, 0xF2ABE736D2A71882ULL, 
            0x8823AA38AD747E04ULL, 0xD2EC05697962E66EULL, 0x14F916E099586031ULL, 0x8F0C56809DBD34B4ULL, 
            0xFE88B99333F27877ULL, 0xFD1C7B7B3776AE90ULL, 0x620B3C3F63022B96ULL, 0xCB41435528D72368ULL
        },
        {
            0xC68179DD504EE709ULL, 0xE51294C225BF2520ULL, 0x8CAD125C171F444BULL, 0xC6AC73C221C125A3ULL, 
            0xC517B82894A79FD0ULL, 0x355EEA3E5FC07ED6ULL, 0x7ED1CE17D5D6E2DBULL, 0xD9F0A13DA611AA05ULL, 
            0x674E37A43E5826C8ULL, 0x03D595E717692A47ULL, 0xE22BC6508E39C160ULL, 0xDC07731B1555A5F6ULL, 
            0xCD83C44ECFE26C54ULL, 0xD1019DEE9D34B11BULL, 0x2D74670FFEE9E367ULL, 0xC317CF32013EC020ULL, 
            0xE096CB813CFC950CULL, 0x978FDF58B0D3892FULL, 0x13760E95DA8F6043ULL, 0xF9A7D238497E58A9ULL, 
            0x2900589DF6FCEBD1ULL, 0xF4C8A4DEB98459B8ULL, 0x15C25388278252BBULL, 0x7BC86E439CEAAF7CULL, 
            0xEBD7A1DE8153C95DULL, 0x241FEC69C71AEAACULL, 0x2E6B2DA75C0442B3ULL, 0x5A4766838B596C81ULL, 
            0xD87EF3C067AD33B4ULL, 0xF6F84BDD7B0DC3EBULL, 0x3CF3351B02F7453AULL, 0x5AA6F4CA763ADE7FULL
        },
        {
            0x9AF6A62E237C6C95ULL, 0xBC4139A048C96F7EULL, 0x1FA2503AC8CEA927ULL, 0x0977368AA22DA24BULL, 
            0x625F8F647F8B2797ULL, 0xA3059D207E5777ACULL, 0xD0CEAA25937D5ED3ULL, 0x0EAB4764B60C5497ULL, 
            0x2ECD0C2D6A878BBEULL, 0xC862E293D83C7FC6ULL, 0xECAD1228EE467800ULL, 0xA29A1C2E011CD6DEULL, 
            0x08AA6ABFCDAE99B4ULL, 0xE91A125FDBEE724DULL, 0xEB87C84D8B6D30DAULL, 0xCEF568262C4C4568ULL, 
            0xEDE16A725C72975EULL, 0xD93685DA88DFF371ULL, 0x9893520834564CE1ULL, 0x9D93D44DC47F6C40ULL, 
            0x291A0F65FEBC9508ULL, 0x912010AD5A5E6DDDULL, 0x6F9B38C74162AD9FULL, 0xD067FB2773F9D965ULL, 
            0x87DFD2434BF439BAULL, 0x63FCE38B701927ACULL, 0xBCA1D74102765E6AULL, 0xCDF565A87B10D814ULL, 
            0x3FC9F6D4EDA5B1CAULL, 0xF7B6B642B7CA88E7ULL, 0xD164E3F5C1399BC2ULL, 0x206EE2532243E573ULL
        },
        {
            0x609685419A6D2152ULL, 0xE298D592BC4A52EDULL, 0x76219B74B0E81325ULL, 0xAA45DFC3A5842B3EULL, 
            0xF72A4107C955C942ULL, 0x813B88B1AB7B27C0ULL, 0x878E944504D03D80ULL, 0x7B3E7124457E98EAULL, 
            0x0C33FC4CE1E31DBEULL, 0xCFA3EA45513D6643ULL, 0x73863E002F6CE331ULL, 0xBD7F3B7727091E51ULL, 
            0x90F95A86CE8EE752ULL, 0x36FED846113DE658ULL, 0x537A8DF85A8E536AULL, 0xFE6DB8DBDC97ABF9ULL, 
            0x75AE458EC15C481EULL, 0x52E21918566136F7ULL, 0xE86BAA66CA745474ULL, 0xB39C67E0F8B5C1FBULL, 
            0x68B1B593D4874BB6ULL, 0x1F06A195190512CAULL, 0x2D5BC51D8B0E4236ULL, 0x481D540092A7AB5AULL, 
            0xCF40A3AA945020CFULL, 0x9ED457630F39D5F6ULL, 0x77723FE2626C147FULL, 0xE56732E194AA8809ULL, 
            0xD94267DE6E3B3E97ULL, 0x8A7CB90BFD7DFA54ULL, 0x80211429BB9DFC1EULL, 0xDEFEC44948F0603EULL
        },
        {
            0x0B51B1BF5CEDD294ULL, 0x7B81FA99692457E5ULL, 0x22E8B88306F320A6ULL, 0xE36D87A3F12919CBULL, 
            0x4AAF7517ED12F235ULL, 0x5E37BA4499C383D7ULL, 0x96438593094DAA72ULL, 0x44399D4D47013C03ULL, 
            0xEF9DB3A5ED6F1EBDULL, 0x820F92F55BC819F5ULL, 0xFBB9A9BB79C00706ULL, 0xF3FAEA7911D492BBULL, 
            0x233CABA81EFC38E9ULL, 0xBADF1D6C910D5F15ULL, 0x47CA7F7B94CA2A8EULL, 0x7B1276C0CCB4AF8AULL, 
            0x6EA0AE5A8E6B974BULL, 0x0F1722C6FA556BEFULL, 0xD14AFB2C2A1C50F5ULL, 0x40551A2F9CBBAF5BULL, 
            0x92898FD186C03978ULL, 0x38AC994A4E0F73C8ULL, 0x26196CA8F17ABD2BULL, 0xEF6C317943020BFEULL, 
            0xBC667B425A0F2903ULL, 0xD9E3C2A4A7475969ULL, 0x35212823F23DDB7CULL, 0x2EAD74383CA845A4ULL, 
            0x4BAC461CDF7B5D3BULL, 0xD58AE928A036FF29ULL, 0xC4268EC282C01B05ULL, 0x2CFAF0405FA62513ULL
        }
    },
    {
        {
            0x7B4FF8F47AD271D5ULL, 0x23135D164F50835DULL, 0x1BBDCB4DB928630EULL, 0xD628A0AEDDBB3B7FULL, 
            0x7BEEE524F3096EE7ULL, 0xDA82C6F9A24D8C96ULL, 0x045F5642EBA86ACEULL, 0x17A9E5B0F28BF681ULL, 
            0x65956986D0230765ULL, 0xD9B81CFCA13EA9CCULL, 0x20CF04378181017CULL, 0xDCD83F5A64C42E01ULL, 
            0x6101ECCB99596CF1ULL, 0xC7F1E078595C1BD8ULL, 0xA80831AA6B64C59DULL, 0x8804E30E51D6DEA3ULL, 
            0xB43FB89E3DB33963ULL, 0x22DA2DECD8E27FC6ULL, 0xFA38863CF2DC48FAULL, 0xBBB5B682F73D2697ULL, 
            0x82FF0733E8CD10D0ULL, 0x2A41FF8A4E149C40ULL, 0x974E9E79D125869DULL, 0x65CDBAFD647CF522ULL, 
            0x308AD6673378803CULL, 0x2DCA9E7ADA58DFBBULL, 0x8C619BEFFF951D60ULL, 0x62C9935DA105E667ULL, 
            0xC35A72BACB9699E0ULL, 0x066FE0137AC2BA75ULL, 0xB9013C814C0B10A7ULL, 0xCCBD417AFCBDA27FULL
        },
        {
            0x8511357D487907A7ULL, 0x7476E74720BBDCB7ULL, 0xBD5064299F3F4352ULL, 0xEFE9021EE0E16ED9ULL, 
            0xBB1A0C2603B2A227ULL, 0xE3C55F42E6EB16E5ULL, 0xBDA97FE76CAFADDBULL, 0x0C067DA63DC943FDULL, 
            0x1FA03FABE0D0CA47ULL, 0xBDED3100328DA44CULL, 0x732F90368A42663DULL, 0x0B0171BEE6058AA2ULL, 
            0xD5E85DA1B546D3EDULL, 0x08011FEEEC1DF780ULL, 0xBB815D673584996AULL, 0xCE99A582C0DAC03EULL, 
            0x5F004750DD3E458DULL, 0x064C4C1D5B26923DULL, 0x439184B347B7C633ULL, 0x145C65895CA775FDULL, 
            0x74A879D7FC50ED5BULL, 0x6094664CE1E27B89ULL, 0x269BEA19909F1360ULL, 0x7AB66A547B884385ULL, 
            0x3AA374973AB95CC3ULL, 0xC4F6AA1236AD4F64ULL, 0xF1C15DCFAD351F51ULL, 0xB1DE1257781ACB87ULL, 
            0xEB47591DD1D1114FULL, 0xAE444A84008B87B2ULL, 0xFE6C57D459BA937FULL, 0x5CDC17E962834886ULL
        },
        {
            0xA021A1EE5D547D7AULL, 0xCF83C4DFCC2BA4BEULL, 0x1D56BC002746D352ULL, 0x41665D75F801CCA0ULL, 
            0x449C126F82B2F6C1ULL, 0x54353481E01C43A0ULL, 0x7B694CD72AF9E393ULL, 0x2549BC22AD2D831CULL, 
            0xEC5E1BA12C7D8634ULL, 0x79245E50904EC54FULL, 0x2DD6816E7455828CULL, 0xC403A4E56520D015ULL, 
            0x272A2BDDB039CB45ULL, 0x88AE2B2821EE4BACULL, 0xEF04FA2FDF53F844ULL, 0x3C76347308D4A972ULL, 
            0x8A02BBFF434853C3ULL, 0x0B366746B71789C0ULL, 0x24764D907BF55D03ULL, 0x51FA22F0B4CD8F3DULL, 
            0x75B39F3B53A1675DULL, 0x3C157E48A5214B0CULL, 0x16DEBBCA29A59D18ULL, 0x6DD92B3E9828471BULL, 
            0x568E7A94289AC83EULL, 0x4C730AD4CC067565ULL, 0x0E5AEBE95922E3E0ULL, 0xF270BFB3FDC79611ULL, 
            0xDFCBC3F556E049CCULL, 0x99AECE180D920A54ULL, 0x346540FF34714219ULL, 0x7304E6ED7FABDE51ULL
        },
        {
            0xD6C2FC05D8C95BDFULL, 0x94CF2279D1E752A4ULL, 0xC75380B0CCF28331ULL, 0x0D468416A4C59364ULL, 
            0xAE285867C7EF0412ULL, 0xE701388EFA4ADFDDULL, 0x9841938928A228A1ULL, 0x04ABBDE111501B71ULL, 
            0xF8C4CEF08F27C0B4ULL, 0xB36ED58B6104AF15ULL, 0xD292A05CB4865DB0ULL, 0x37C05D1ADE9E91CCULL, 
            0x7871B63F59F9EB16ULL, 0x2E6735ACA9834701ULL, 0xC1567544C6941A1FULL, 0x2A4BA4BBCF3AA2B5ULL, 
            0xDC4A48FE1488DFFAULL, 0x60B78AAB877ACB73ULL, 0x576AA236E66A31B4ULL, 0x179D9880821FCA5FULL, 
            0x5A1DF1E812D64A82ULL, 0x0740876BE2782D03ULL, 0xC82AA0FAD9276605ULL, 0x81E5B8504ACD748FULL, 
            0xFE3B28138937A08CULL, 0x884F3E5A35B0405AULL, 0xA036C261D27129F4ULL, 0x6F5C1246E6A87CE1ULL, 
            0x62F24A58C7F14325ULL, 0x42D4363B2DE1CC02ULL, 0x97C4D968783B2178ULL, 0xAD385F56DFC5FBCBULL
        },
        {
            0xAC3ABCB3375B6E96ULL, 0x50EB9FD5F799A4B0ULL, 0x924C45B7ACAE334BULL, 0x945EB55AED462A02ULL, 
            0xF5E7D3CAEDD590CCULL, 0x02E61D7FB3DE43EFULL, 0xEEDAC3479FB15477ULL, 0xB37B260C4A37A7EBULL, 
            0x60FFC5B7B60723A6ULL, 0x5366075F3C7A3B00ULL, 0x0D630DB6847B41B7ULL, 0xBC795F0EAFC7E6C1ULL, 
            0x567B9FF78B3278FEULL, 0x7659507BC36F6CF8ULL, 0x58EB895EA5651A40ULL, 0xC9A454F689C9285FULL, 
            0x542D75FAD6E90392ULL, 0xDC0D0594468BB7F5ULL, 0xA157A53BEA7B2FBDULL, 0x11699DAA6F9AE7C5ULL, 
            0x7C231D97EC7B5D5BULL, 0x0F90B342F749A268ULL, 0x0EBBB11FDA48A3FFULL, 0x17DF19EF061E6E9EULL, 
            0xA1BB6F2907C07699ULL, 0x44592621E253AB99ULL, 0xB0B1C441325D0EBFULL, 0x9C6CC1708E1E0C48ULL, 
            0x808902E97355AAB4ULL, 0x3142D45814B8D8F0ULL, 0x68EF1A7A106AF7B8ULL, 0x55E19F697201B5C0ULL
        },
        {
            0xE1449C25A3744F9DULL, 0xC308856087E5C371ULL, 0x6833858D5E9C1575ULL, 0xFB20831158200694ULL, 
            0x40985F73DA8BBFDFULL, 0x03C8809A3522B341ULL, 0x7AEB006515C11B49ULL, 0xAF14D08DA59E719BULL, 
            0x3DD8CDF089F3D9E6ULL, 0xC7670ADE8E921FC0ULL, 0x8AC2B6BA9AC79467ULL, 0x959AB86DE4405B77ULL, 
            0xD891EF970F7B75BFULL, 0x479E12F7485D4780ULL, 0xCA2A334E8E587359ULL, 0xE8FC88AFEE96DCE7ULL, 
            0x178AF90BBC0807D4ULL, 0x79C5B5838D206647ULL, 0xD761E570735F6DD9ULL, 0xA610B57A2F74D0C6ULL, 
            0x8FC75EAB37AB42A1ULL, 0x2B033A61D23A1DFDULL, 0xD1A99A61B69E6365ULL, 0x0DBDACAF4C656221ULL, 
            0xEA880FE5A111EA85ULL, 0x2D57A8A55648F19BULL, 0xD013261D86EE344AULL, 0xB6952482EB0FFC04ULL, 
            0x4E789B061F7BC58DULL, 0x5A55A7BE11A688FCULL, 0xD84CA7F6BE3D1E21ULL, 0x24AA5476761F810DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseFConstants = {
    0x3539EC69B9DD66F4ULL,
    0x2528087347F9E0E7ULL,
    0xBB89E02BDC82BBADULL,
    0x3539EC69B9DD66F4ULL,
    0x2528087347F9E0E7ULL,
    0xBB89E02BDC82BBADULL,
    0xF96D3B05AECC95B3ULL,
    0x021E35529D154431ULL,
    0xA4,
    0x9D,
    0x15,
    0x3E,
    0xC9,
    0xA3,
    0x93,
    0x99
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseGSalts = {
    {
        {
            0xC75E28FEC251FA28ULL, 0x5D8168A4C9EAA54FULL, 0xDF72B3766BCFCDA8ULL, 0xBE122ED7974B0C5FULL, 
            0xF446EB098411B6C8ULL, 0x4CFC8AC5ED69CFBCULL, 0x777ED0B17157EC27ULL, 0x85C258D024C35214ULL, 
            0xC349CC36162E1480ULL, 0xB494249288BDE594ULL, 0xD7F38AA10F096640ULL, 0xA4D3365038577202ULL, 
            0x720324AEB8981D8FULL, 0x79F6018359429BB1ULL, 0x9858621CC468463BULL, 0x12FA464B8E53D3A3ULL, 
            0xAFF735EBE53F1EE9ULL, 0xA467EE79D2539BAEULL, 0x25DC054DCE445EB1ULL, 0xEDD915CDCE522E7BULL, 
            0x459DD1E708121FD3ULL, 0xEFC517BD2DB83A6DULL, 0x257832AD11D98DD4ULL, 0x3B71ACD8A0D81309ULL, 
            0x58001C1A697F1152ULL, 0xCB8190C0A0B9E822ULL, 0x07532764666A7611ULL, 0x16F6D670F8C41EC8ULL, 
            0x28802FACEB3B7AA8ULL, 0x6E6B93F3A78799BAULL, 0x74B7B034A60471FEULL, 0xF18AD7372D6D8501ULL
        },
        {
            0x64E06F84127E9229ULL, 0x55B5250F6C3C2B4FULL, 0xB69CE85CA57EF70FULL, 0xEBE8BF41AD6EA98BULL, 
            0x714208088D992B09ULL, 0x33107BE20ED26513ULL, 0x4EEB1B1E61A79E93ULL, 0xEB1A4790766F7FD2ULL, 
            0xDCF5CB31DD09850BULL, 0x029B052EFF27BE82ULL, 0x01519450608B0F63ULL, 0x35E28A012EDEDA01ULL, 
            0xCA34B7F569A474EDULL, 0x16FA403BC9413865ULL, 0x9F7DE701047EE0F0ULL, 0x5B3A32BC4A67198DULL, 
            0x26B1224171C56208ULL, 0x98BD3CBD4FECD5C5ULL, 0xF53112DB1585BF94ULL, 0x9FDB8F14CBE8E721ULL, 
            0xBF38FEA2E265A03FULL, 0xF9D96688D3E50244ULL, 0x532122863465C2D1ULL, 0x0A62E91D3DDD301BULL, 
            0x3A3BF0ECB1FB2D01ULL, 0x66E507E13C608C07ULL, 0x966F8DC3FAF2354FULL, 0xB855108186AAB8D6ULL, 
            0x021A31396863C18AULL, 0x36D149969858F2D9ULL, 0xE02EAFFB6ADBF6CCULL, 0x5E94EC8369EB9E5CULL
        },
        {
            0xBB24B9BF82A0B3CDULL, 0x07836E2B935A54B8ULL, 0x1FB9451A5A42B18CULL, 0x6401E3765A3542E4ULL, 
            0xC21922D0F31E7E21ULL, 0x4E888B120B0FE644ULL, 0x66A1B48F92185F62ULL, 0xBC26623DA316EF1AULL, 
            0x9F05751CF4976B9EULL, 0x6EBCEE34D5DB3354ULL, 0xA405E8AD64814AD7ULL, 0xACB5CA3DDC04C7A6ULL, 
            0x989D674DC57AEA5BULL, 0x6BA9191B204C887BULL, 0xEAA778C43C6AE1F6ULL, 0x021C0015D154CD93ULL, 
            0x02F1B33A68F4ECD3ULL, 0x83449A8E16C1530BULL, 0xE8CFD4CF97DD8250ULL, 0x112F342F5E999E7CULL, 
            0xC661A5BFD814AB04ULL, 0x71F98853305D37DCULL, 0x1E845A0DEDA090ECULL, 0xAEBCA6AF593BB13BULL, 
            0xB54FCEA9E8070040ULL, 0xA36F843BCDAFF6A5ULL, 0xAED5968A4D7DA251ULL, 0xF556FA12671CD1ECULL, 
            0x789E7575D037CFFBULL, 0x4C799CEA282F87B6ULL, 0xD275322F1344F9A7ULL, 0x8EEC1EE51F4EFF66ULL
        },
        {
            0x4821434EC469AD0AULL, 0x4EBFB3B89878FBC8ULL, 0x19DC0CF9C0B17F94ULL, 0x28DC53A902E4FD47ULL, 
            0x5A55FEEB1A9EB2EEULL, 0x917A65BF2E87BAFBULL, 0xA9DA8AD04DFE43DBULL, 0x86B46AED52C04A12ULL, 
            0x0C80AF788E98826AULL, 0x9BBEA27E75D188AFULL, 0xADB214CBADDCD800ULL, 0xFE566C35F2A241FEULL, 
            0xF5F5BAF7945C068BULL, 0xAD4A6CB028C449C4ULL, 0xE630E3F1D8A773EAULL, 0x66A8FC73F1696646ULL, 
            0x8F0198495E601F1DULL, 0x90861B502A87F183ULL, 0x153971F4CAE666BCULL, 0xEE581D0CD52BDCBEULL, 
            0xA6DE9621F0C0C902ULL, 0x1EE00D06D47707D0ULL, 0xFBD4FB868144DB8CULL, 0x8B9A4397DA059ACAULL, 
            0xAF7809E678BC4FCAULL, 0xF8A4C00D8AB5A711ULL, 0xF2CD2C606B68B055ULL, 0x7B7CD5FC015A8411ULL, 
            0xAC06163504C16165ULL, 0xBC37F06EE6EB71C4ULL, 0x579AD180589DB007ULL, 0xC133B7667492B724ULL
        },
        {
            0x7FFDAB9C16C77EF8ULL, 0x3048E8F552EB2624ULL, 0xAF769423A3E6DD22ULL, 0xCDB5E0C52157A795ULL, 
            0x5F465C775377D257ULL, 0x4CB495E13326E137ULL, 0x1457FF9ECB5715C7ULL, 0xB17594F67C0FD488ULL, 
            0xE77506740CB02B2AULL, 0x847512607A37C22BULL, 0x2A2B94A1EAAD1DA5ULL, 0x02063FA6D0F8EE89ULL, 
            0xAC7B49F52E2340BAULL, 0xFE6ED20627356678ULL, 0x782811A669E574BAULL, 0xA8E9C57FE488D781ULL, 
            0x404D6A96A625605AULL, 0x2E0EC8A48DC5697DULL, 0x7ADAC42B56FADFB3ULL, 0x1BB347C991DBE6A8ULL, 
            0xC55D4DAD5C2CE808ULL, 0x91305A447619FD81ULL, 0xC44C01DA928CC5DEULL, 0x07B09AB356AF44DDULL, 
            0x6D2CB58FE84AEC16ULL, 0x99341DDE524333C1ULL, 0xA308BFF7CC5FD96EULL, 0x75AEA4B8D4EB8C6CULL, 
            0x6D1F0905BD978AF9ULL, 0x786E404693EC83A3ULL, 0x15A53473236E106AULL, 0xD7F9C0B95AA5ED5AULL
        },
        {
            0x955EC2A02DC78D63ULL, 0x63B6C84FAB4654E2ULL, 0xBD0E43982120C15AULL, 0x871F44ED43ADF0F4ULL, 
            0x90BAB726B35BDBABULL, 0x0F0F4F87BC0436FCULL, 0xC2403FA66D68CC22ULL, 0x171D19BDF0192462ULL, 
            0x07C32D19F459D72CULL, 0xB49E6B22024D0399ULL, 0xD612A4993EA8B3E9ULL, 0xB0BD80B24C80D874ULL, 
            0xAAAE58DD1C67491FULL, 0x5F0825ED15169A0DULL, 0xA7FA1A79D5D497DDULL, 0x9DC0F6702259ADB6ULL, 
            0x230695D3464321E0ULL, 0xB42ADF5F385A0F4DULL, 0xB566E47BC656B0D7ULL, 0xD08E0BBB2B7B3072ULL, 
            0x0BD6FCCBB49334B2ULL, 0xAD13CBFC47D0F042ULL, 0x3E8A411F31C7A2C5ULL, 0x91C0F0A401B6C470ULL, 
            0xEC671B68F6F315AFULL, 0x960A5446A9114C9AULL, 0x14D8E9C507BA654AULL, 0xBD240C48FF2B0679ULL, 
            0x6A5C18F71DD830CBULL, 0xAE5B245BEF3FD52DULL, 0xE5AD07C520EF4B1CULL, 0xEDC88CF4D39ED062ULL
        }
    },
    {
        {
            0xEE92DC25C5121DAEULL, 0x2CF8B3E373C37B37ULL, 0x74E0D09E1E603F63ULL, 0xC4CAEF108C7613F4ULL, 
            0x80DDB845F906C5EAULL, 0xFA56C6BDEBB26376ULL, 0x7CC56FC6122BE362ULL, 0x5FD86333AF37268FULL, 
            0x14A89B576C2C85B3ULL, 0x4E5D5B6158561F4FULL, 0xD211A5552B8CE5E2ULL, 0x53B1A5AEC47C4E37ULL, 
            0xE5D7788941ED6242ULL, 0xB7066BB55FB157E5ULL, 0xD2E70B74E5AC3DC0ULL, 0x5A37D5EEE262078BULL, 
            0x55C94F415AC9CCF1ULL, 0x58E624E69465100FULL, 0xC4909FD3F5D97769ULL, 0x762D494F6521BEC3ULL, 
            0xE242EC53DE3E75E2ULL, 0xEDD57690D29D1A43ULL, 0x9FFE2E5B74084AC9ULL, 0xFB1E9D4617C86B42ULL, 
            0x03CE7E852E2679D4ULL, 0x41267EBA176353B6ULL, 0x829C36375A108A27ULL, 0x6BFCDFEB8FB8146CULL, 
            0x36C6043FA118CCDBULL, 0x02AB55D4BE002BA7ULL, 0x9FA30D0C4ABE6652ULL, 0x0697DFF0F75F64A3ULL
        },
        {
            0x1186F949C3F5C977ULL, 0x3BFEECE32169FB9BULL, 0xF45CA9BAB3533C02ULL, 0xC82AA5D6865A83B5ULL, 
            0xCEC4FBD3BA4C446BULL, 0x616C1337B8D15788ULL, 0x5135C14B4C503A8EULL, 0x2C4F162146B2DEA7ULL, 
            0xF23CCEF76359AC4EULL, 0x1A21B6239882901FULL, 0x72BF64FCB3865DDAULL, 0x0BBD59CD05B09A20ULL, 
            0xCE8F1DF867E01BDEULL, 0x73D8C0473FC82FF4ULL, 0x0806FC58F330587BULL, 0xF723F4076725618AULL, 
            0x72C9ABF56BDD79ADULL, 0xA0C0CAA0BF5118C6ULL, 0x34302C60195F5267ULL, 0xAC4746C859E6DEDEULL, 
            0xC6193C7A80ECF4B4ULL, 0x79E068931AFFD035ULL, 0x66CF38BDEF8619A4ULL, 0x269478733557AD4DULL, 
            0x1EFDF19808FC8A51ULL, 0x1E85C0A3B509D4B3ULL, 0x0A62CDD736E7747DULL, 0xE76D3C07DA2CB666ULL, 
            0xA268D851B91EDFF9ULL, 0xC09035723833458CULL, 0xE9643244AC09F0F8ULL, 0x6175E73FAD24BE46ULL
        },
        {
            0x22A0ECD0B75A17BDULL, 0xC22D974F7F1BCA82ULL, 0x5BB2FD7684FF5FF1ULL, 0xAE069E57052EAE08ULL, 
            0x53DFBC55F1B7CF78ULL, 0xB5A603425879B566ULL, 0x94244702CAE69921ULL, 0x87C5EAF074AFE399ULL, 
            0x03FD1C15B1291747ULL, 0x662D762E9667D70FULL, 0x1AEBAFCB7F60AA55ULL, 0x02D0353383867E2DULL, 
            0x1511BA3DAC07819DULL, 0x3AA3A965842D7913ULL, 0xC25B7450A5B6B4C7ULL, 0xD06A994EACE7C037ULL, 
            0x5DFDF1348C87870FULL, 0x79B104B966006A95ULL, 0xC59FAD3CF4ED3BE4ULL, 0xB6B524B951822467ULL, 
            0x091C6C84825BC03BULL, 0x77B1747680E2E6FFULL, 0x4CA1E743ECF13E70ULL, 0xCEC3460C049E26C1ULL, 
            0xA442E4D653A00457ULL, 0xB1026599DA156558ULL, 0x3482D871A6415D64ULL, 0xC3BD41439A44EFB3ULL, 
            0x59D5D81042607327ULL, 0xAD0EDAB6D501767FULL, 0x645A738768517CABULL, 0x484D16C0D6F50CC9ULL
        },
        {
            0xE08B19906627C7B3ULL, 0xFC766DA6137CE573ULL, 0x5198BCEA41BADD3DULL, 0x4DC286AD86DA484EULL, 
            0x8FEB0C696E6BC30FULL, 0xFF73DF6EBAF2A5D4ULL, 0xD710F970EEC6A0B3ULL, 0xB443AF7F7803B759ULL, 
            0xB55DCF428C09AF02ULL, 0x4DEFA5A21B938001ULL, 0x492D0D9391E1393DULL, 0x16838969E34ED830ULL, 
            0xFAD26BD5F5E41672ULL, 0xD70796DC4187A50BULL, 0x3A7CB1C4514E777FULL, 0xAA1C976E0E98BAA6ULL, 
            0xFB3BE70B8B5F7D69ULL, 0x152D596DA7167E44ULL, 0x1773899B0E78604CULL, 0x69E6F1BA9C3D8AB4ULL, 
            0x430F386AA5703CBFULL, 0x0FAE28DA3BE1BCA2ULL, 0x4227569B84CAE5ECULL, 0x428A7965FADDF09EULL, 
            0xEFBF0C555508C94EULL, 0xC9CF19B5C908420FULL, 0x3923CFDC0C3B9124ULL, 0xE37CB65D726DE927ULL, 
            0x4E47574BD95F2DCAULL, 0x52B577FD8F524142ULL, 0xC4F7AB1AF37DDD22ULL, 0xE0D829D8682F8314ULL
        },
        {
            0x74522DBFE31D0BC7ULL, 0x2FD47C3F82765BEDULL, 0x4A4F32E63C6DC6AAULL, 0x86DFE216FAADABD3ULL, 
            0x6B740A40DDD74E96ULL, 0xCAC69BABB7356039ULL, 0x53CB56831DEDB4CBULL, 0xE550A54FB316CEABULL, 
            0xB2997562A9CD8587ULL, 0xAFC0D33E5CC23698ULL, 0x8414472B0C22D30EULL, 0xC6E42CABC94615AAULL, 
            0x48E0BBBA9B646318ULL, 0xDB68DF8178C2D63CULL, 0x0CB5BAFA7D3485BEULL, 0x9E9951207FE75BFDULL, 
            0xFB3C0CD313900F1CULL, 0x8687B922278BDD9CULL, 0x7F9382A88016AB77ULL, 0x60F0C2E4357995C4ULL, 
            0xB508A41D79AC5426ULL, 0x9CBFD9BFB3EB37BFULL, 0x1361BE27642FB604ULL, 0x9DDD1E169B7316CFULL, 
            0xE9445365B9E5955DULL, 0x078B1F08FE1AA628ULL, 0xEA7C481D868348FAULL, 0x15D6C8151D8419ECULL, 
            0xAB0AFB2B7D6B8302ULL, 0x2BD87C5336E8AE00ULL, 0x1817D7E940F455EEULL, 0xC492D9350058B6F2ULL
        },
        {
            0xE489C4CC0FF7549BULL, 0x8DD8C17AF51F0AA9ULL, 0xCAD7BFC7D281EA52ULL, 0xB9B0E04A02F4B659ULL, 
            0xA08934CCD3DE98F9ULL, 0x713333F388B55A0DULL, 0x449AE349949B67C6ULL, 0x5049B3597757EEBAULL, 
            0x3DBCC53D5FA5B5B0ULL, 0x4D0ABCB74CC5E86FULL, 0xB9ED25489EC6E6A8ULL, 0x6B11ABB6076481E0ULL, 
            0xE80F7D27B52B84C8ULL, 0x95A20160F6BF504FULL, 0xC14C9956DA1C0F9BULL, 0x3CF741FE8ED41714ULL, 
            0x78B60C4093026F8EULL, 0xF7777A24D7027231ULL, 0x2C6466415DB953B3ULL, 0x5C519E6FAA291973ULL, 
            0x2DF5D0D8423DB178ULL, 0x2CB2ED08297CD099ULL, 0xAD15C281E313CA69ULL, 0x7B1FBC16B5E16651ULL, 
            0x322D48281FD53D58ULL, 0x94BA4BB30ADF1402ULL, 0xAC5BC62988C44D9FULL, 0x4B13CB644EDAD52DULL, 
            0x8C5B3FA0AEA47C35ULL, 0xAC4FDD985F9F95B2ULL, 0x5F833CC807EDD476ULL, 0x11FD05F3C076D121ULL
        }
    },
    {
        {
            0x057D082511DD3C05ULL, 0x1889C01B05F7A182ULL, 0x482EF667D2BB32F5ULL, 0x485F5221A29A3031ULL, 
            0xB9FE30C1E42E4E41ULL, 0x0AFF1E831D0A8C5BULL, 0xC7202FF513B1BC97ULL, 0x214296E3AE471F19ULL, 
            0x2F4CAACC7334A0CAULL, 0xA072EE4395477380ULL, 0xF70A1691FDD720D5ULL, 0xC115E12C3A67BB87ULL, 
            0x1FF2755DF14F8883ULL, 0x322FB2BA1D23161FULL, 0x5DF56D2E7FCB61F7ULL, 0x3FC5AA8B1A72F015ULL, 
            0x386DE9F30D235C52ULL, 0xCE4C6249971E45E5ULL, 0xB29A2C363120337EULL, 0x48FB429BF1AC3781ULL, 
            0x351753371A25D674ULL, 0x967B5654B16B6E8FULL, 0xEEF0243500A74D1CULL, 0xB2824AF340598B46ULL, 
            0xDE53A4ED3C4AA879ULL, 0x512E84A6C1701D09ULL, 0x06D85D66BAC497B4ULL, 0xAD9E52C543E18A48ULL, 
            0xFC16E3675CC535B9ULL, 0x6138E4A7504A5420ULL, 0x9AEE7168DC94B65DULL, 0x3963ED74FAF9784BULL
        },
        {
            0xFC8C43ABAB44AFD4ULL, 0x48D2DBB87B40E4BBULL, 0x2ECAF18BE6A3C331ULL, 0x85873DCD05C7DC22ULL, 
            0x69DB94EEC89C83E7ULL, 0x7EAEC6AFE6748CC6ULL, 0x5D7DC42C6E6A6D77ULL, 0x9BA1F5B5B9D9AE45ULL, 
            0x4C1F81EB2C50224CULL, 0xAA02BD4652D46ACBULL, 0xEC77E009D634192AULL, 0xE4E6A6507DE57BA6ULL, 
            0xA6B37B878CADF70BULL, 0xFF22CFFC91371899ULL, 0x1B2D1BE33D5E1987ULL, 0x9B9DB4033392F911ULL, 
            0xB3869E9EC00A9F42ULL, 0x4C7DE2AC8345DB08ULL, 0x5E64D3E28EB74C07ULL, 0xD947CA8B320F350EULL, 
            0x316B0EC66F411EBEULL, 0x7E8968ABCCEA144AULL, 0x6A09874610A297D8ULL, 0x6E577CFA28970B2FULL, 
            0x49129D040272249CULL, 0x8569CB5208F6735EULL, 0xE77039CAFE14EE49ULL, 0x3A40C504FF9A48C8ULL, 
            0xAA945BABA8C19D4CULL, 0x1E92527BCD3CA89FULL, 0x6E68039463430DECULL, 0xCBD66F4F475FF254ULL
        },
        {
            0x1794BD1840A1356DULL, 0xEA12BAAB6B5B7118ULL, 0x7AA2EE7C572A2C93ULL, 0xBA0D0FB9BF3347F6ULL, 
            0x9F21C5EAF3C4B28DULL, 0xB5AD73E143B7EB67ULL, 0xC805CCB6E97BB596ULL, 0x60084CD5000F93B4ULL, 
            0xC4BD4ADDE0FA7FD9ULL, 0x086F017768A3C3AEULL, 0x3E8FEFBE82BD267AULL, 0xFE2A85072E3EA02BULL, 
            0xBD6C60C5F53E842CULL, 0xDBB0A75797AEA7C0ULL, 0xA2A0AD4F1079FF3BULL, 0x399FB7029F94194CULL, 
            0x053191E23916AFA2ULL, 0x77D2946782B230FAULL, 0x20C06B959C685128ULL, 0xFF67E7BD3744205BULL, 
            0xA357FD0FE3322CF4ULL, 0xC715184529495B08ULL, 0xE398BCD2E114111CULL, 0x792A7CDD0756692AULL, 
            0xBC102D94278614D3ULL, 0x9B983047DAD814D2ULL, 0x1C9DEA1AE12D16AAULL, 0xE4E3F8B61DC08A4BULL, 
            0x1DD0ADA4C213AD17ULL, 0x9B5BC7E35D2C6BB3ULL, 0x7C5065FB9E091AEAULL, 0xE15884913314F95CULL
        },
        {
            0x6CF76F9F9DAB2B72ULL, 0x7E10D50118DD6FFCULL, 0xAC3AFDFFA2F59A17ULL, 0xE6C54385EBA7572CULL, 
            0x29BB39F15E001EB1ULL, 0xE8B43133E8A4E1D1ULL, 0xA12B12BA9650AFD7ULL, 0x4D7403105724FCD2ULL, 
            0xB1123C5B35F48B10ULL, 0x6CE32A380C1FFA8BULL, 0x52EE5B6B3D924DCCULL, 0x3756331E41040486ULL, 
            0x8ACBAF91A4FE60F3ULL, 0x1392257682C583CEULL, 0x46224D77176E0A2CULL, 0xA57013B0625CD5E8ULL, 
            0xA8496C5BA9EB5BA0ULL, 0xB96E08B6D7CE950FULL, 0xCE740E340C913759ULL, 0xCE49EE5E256C13D8ULL, 
            0x81807948FD4013ACULL, 0xCE5EF75217D5FBE6ULL, 0x1BF70E457CCFC337ULL, 0x9A950466658A7D60ULL, 
            0xD265EBEBAA756D3BULL, 0xCC263C6F047EB3BEULL, 0x06B4795858223040ULL, 0x60D63D2CAE6D7E49ULL, 
            0xA957A25418E027E1ULL, 0xF55F6A886B854F72ULL, 0x582F100D4E8EFEA5ULL, 0x9F8A0C688563E42AULL
        },
        {
            0xE1BD2CC4AF541F62ULL, 0x8B55A0624D4DFBF8ULL, 0xE96F591E9E1EA327ULL, 0x5BB19C69645984A0ULL, 
            0xCFCFA170278A97BBULL, 0xAD9E8FDEC1BA38C5ULL, 0x07487876EDADB639ULL, 0x1EC59607A0BFD469ULL, 
            0x2FFD91E80AF5DEF6ULL, 0x944012761BA021C9ULL, 0x674E0F68EE669A04ULL, 0x091595A9284D211EULL, 
            0xE90E6BB98A58CC2AULL, 0xCCFC3AF8C8D36F71ULL, 0xB7FC15563F6B01B3ULL, 0x8A6D32299FB2B425ULL, 
            0xC3FA918106D56F09ULL, 0x5ABF12BCFEFB6A1AULL, 0x366B63EACE221D96ULL, 0xF2FB18D46A60E11FULL, 
            0x5DE2B4ADEF341E12ULL, 0x13A8FF9C8C780D22ULL, 0x72BBF092250046AAULL, 0x3824E9836BFEA110ULL, 
            0xD3828972C432C0FEULL, 0x2AE5C49A5E783232ULL, 0x10C5569A3D7836A6ULL, 0xB8095815B9CE762FULL, 
            0x0EDC38757498AED9ULL, 0x0EB51B1ECD43371FULL, 0xA26A07DD6DE6CFA0ULL, 0x3F08164581339026ULL
        },
        {
            0x12D0321A36367A64ULL, 0xE45F6ABEA011B5D9ULL, 0x4B028ECFD2B477D3ULL, 0xE1B05EE346E8C3AAULL, 
            0xA3F03DA459A72875ULL, 0x558F60AA7B81F102ULL, 0xBAED4CD758DE0ABEULL, 0x7051A1E1A4B92295ULL, 
            0x66823F84D78ABDABULL, 0x8DE27978CDA3C960ULL, 0x6E971BA0B9CA8BDCULL, 0x4F11F629E926111FULL, 
            0x30A9CD002595BBCFULL, 0x83080B7DDCA4B614ULL, 0xAE1F71BA47C53B95ULL, 0xAA3A5E683D6411DFULL, 
            0x20AA90ED25177B15ULL, 0x3E1C2E09980D1379ULL, 0xFC9CB6F2EE75E87AULL, 0xE86363DE8EE034AAULL, 
            0x7667396D7DDD58E6ULL, 0xB923A0B24BE0AD72ULL, 0x79CF466667D6BFB3ULL, 0x718A9D27E047DC22ULL, 
            0xEC7400236571D437ULL, 0xD9680CC989B5EF48ULL, 0xD9BB5096FFB5E137ULL, 0xFCDD4FA9FAA70AFBULL, 
            0xB93FE0B185E34DC0ULL, 0x744FB7CCFCBDB0E0ULL, 0xB44B054A8B470BD6ULL, 0x6EBA0CC9646D12DCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseGConstants = {
    0xF41D275F22C78F81ULL,
    0x795FDD4ED7017048ULL,
    0x1EDCB61823A0CA54ULL,
    0xF41D275F22C78F81ULL,
    0x795FDD4ED7017048ULL,
    0x1EDCB61823A0CA54ULL,
    0x92398FBBA7DDDEF1ULL,
    0xBC9CA437BA17CEE5ULL,
    0x46,
    0x95,
    0x76,
    0x75,
    0xB9,
    0x71,
    0xF5,
    0xED
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseHSalts = {
    {
        {
            0x44EFE5AFCA1DF9A6ULL, 0xC6987D7D95CB636DULL, 0x129A5BD5BA19ADD4ULL, 0x3AA27018DF22E798ULL, 
            0x73720D07A5A31842ULL, 0xCC92AAF76AF78805ULL, 0xE7FA77479B2712C3ULL, 0x3367E12D35BDA1FEULL, 
            0xF7F6B4FB9DE71135ULL, 0x38DCB2A69C3E570AULL, 0xEA7E29E402616D35ULL, 0xAE4287229EFC13A5ULL, 
            0xBD262DD5D91A7C5CULL, 0xCC1EF3737EE24141ULL, 0x4B88CBCB1E481486ULL, 0x72F2AFC408D97B29ULL, 
            0x5520C91397C24669ULL, 0x82F6B32E6AE9A293ULL, 0x41B4F1B95D0954ECULL, 0xCB7DBE56316C9E23ULL, 
            0x5FC4CB7599F07EC2ULL, 0x394642719FA04498ULL, 0x17990EFE607961BEULL, 0x13D344A7AB21F22EULL, 
            0x1232925F039C16FAULL, 0xEB74FE78E12C254DULL, 0xB2E67A8A66F06478ULL, 0x416155275992681BULL, 
            0x9068F2D52F8D9589ULL, 0xCCCD7480B4A07538ULL, 0x052E7208482FFE4FULL, 0x0D8EDDC0E740640FULL
        },
        {
            0xDE1527722D01E0B9ULL, 0xEC6EF27CA840BA78ULL, 0x2E599EF52D2F81EFULL, 0x56CC662A66A1DCF2ULL, 
            0x8B3B68575BDF7AC7ULL, 0x6A536292FE08CEA4ULL, 0x87AF0FA7041EDD2FULL, 0x4743F3CBC69399DDULL, 
            0x78086ECE1E8693E3ULL, 0x75AE3770F9530891ULL, 0x133FE20F7282D556ULL, 0x13746E689C8D1B1DULL, 
            0x98B75596731521D7ULL, 0xFA740DFA978E88CAULL, 0x56C10B4AC2D77E8AULL, 0x15DFA810963993E1ULL, 
            0x91C2FEB0276949E7ULL, 0xF992636E22AE4FA1ULL, 0x76F93491B41046DEULL, 0x6486F45F464FD60AULL, 
            0xE510BAD896B40CFDULL, 0xBC0F9503489086D3ULL, 0xAAE2043DA0BF2C60ULL, 0xA699036C17B95EDAULL, 
            0x67CE6EC80D7F0D5CULL, 0x59552E7275C02406ULL, 0xA7D8CD2CD796EF0FULL, 0x5B7CE5CAB51CCA99ULL, 
            0xDC67367C0E1120CDULL, 0x4F9E304011C8C43EULL, 0x9B1E5925C11AD417ULL, 0x99253E9E52EA7364ULL
        },
        {
            0xC9BA0323F965A82DULL, 0xC779D3D2266216CDULL, 0x7F8F0B8739084FDFULL, 0x7459C7644619D480ULL, 
            0x5F271F06C31759FBULL, 0xAE77047507668A43ULL, 0xE89CE6A98C23A3C7ULL, 0xD93376599E495259ULL, 
            0xB5F2AF8BF6BD3269ULL, 0x3F307D57D5C6D4BBULL, 0xB4AC7663784F9F83ULL, 0x9EAA8C6F778DF458ULL, 
            0x76809479102E4109ULL, 0x183CF205591211C3ULL, 0x0C8E32EA13EE8D20ULL, 0x1BAF4657A9924E0BULL, 
            0x59BD0F5461B77CF2ULL, 0xC03F14CBBC41A074ULL, 0xED85BB0F228AACCFULL, 0xFDADE247096C4F0CULL, 
            0xFB9619B8FD39DFD7ULL, 0x7FED7059BD5ED670ULL, 0x02080BF179246300ULL, 0x42F46D526A43925FULL, 
            0xBCCECEF098F70A4BULL, 0xD6B8389D0D68C470ULL, 0x3DF1429C7E16D67FULL, 0x8892D0D9C669BD17ULL, 
            0xA9E368B7F673A76BULL, 0x73D54FFF2C55D82CULL, 0xCAB9F03C87314479ULL, 0x08EFFE59E8B28EDBULL
        },
        {
            0x8B279156BC97F1D3ULL, 0xC924E04464305232ULL, 0x5D45B12CD0E59519ULL, 0x4B782CEEE1AEED8AULL, 
            0x30FB2198CE9A2216ULL, 0x39155FD3BAFAB0F4ULL, 0xDF80E4909B9DC955ULL, 0xBCAB54CA2EFDC218ULL, 
            0x8D6F635EFCA5D7EEULL, 0xA32D457112C82F06ULL, 0x2C8B1A38CF818C23ULL, 0xBBCC3728C615619EULL, 
            0x67803DE3BB5A3B10ULL, 0xC151722B6E4DFC41ULL, 0x563FC32F6451839CULL, 0x591345BF77F17F00ULL, 
            0x47B6316950540046ULL, 0x12572CCA36D7AA5DULL, 0x9FBA803130C4CCC8ULL, 0x5415E91B85D7551AULL, 
            0xDB7BAE662E5D0F6AULL, 0x6FD88A4E371BD889ULL, 0x5D4C0CA01F33C8C1ULL, 0x0A86B68B6230B9EEULL, 
            0xC2E72185F4657E58ULL, 0xFEF3D294B880972DULL, 0x575CB907C4E04C42ULL, 0x2A966D45127457ADULL, 
            0x8E08FEBD2C63872AULL, 0x7C9094318BEEFF5FULL, 0x65295F52A03B4AD1ULL, 0x989ACE454BC82FA6ULL
        },
        {
            0x96D5BE1A2AB315B2ULL, 0x7577865B6A8FEE39ULL, 0xF17005C47CD55B03ULL, 0x83E00A2C46FA32D1ULL, 
            0x1939DC3F109273D5ULL, 0xBF4D8E555ED1776FULL, 0xD572C87B103E8F3BULL, 0x2A9AB8C2D7C70B72ULL, 
            0xF67BDBD74C0BA40FULL, 0x818B198EC48BFEB2ULL, 0xBF3A23E2D1C39551ULL, 0xC8D6CAF7662469DBULL, 
            0xEC7CD772D371E69BULL, 0x1320B219EF07E56CULL, 0x06A2E5007FA4430CULL, 0x0194B7C4C173B1B9ULL, 
            0x2CDB048DED9DCB40ULL, 0xF801257F40C6A4C1ULL, 0x54F43C576CFE5A74ULL, 0x392378CCC5D1CE90ULL, 
            0x4E22EAE58943D02CULL, 0x2C7CF8F3BE03B789ULL, 0x9A50A923A48ACC43ULL, 0xE3BEEF5EF2A8B644ULL, 
            0x0997CF2665A00B87ULL, 0x6CCE40AB1649342FULL, 0x8D5F3E3F4297A591ULL, 0x7AA64834474F5045ULL, 
            0xAF86C91FF72EEDEFULL, 0xF0C64C0A9D321BA1ULL, 0x44714039D71D4223ULL, 0x9668443FFF2CE981ULL
        },
        {
            0x7E2AA870540F5D53ULL, 0xC567E438C52E53D0ULL, 0x833665889AD177B3ULL, 0x973881D2A563AF74ULL, 
            0x9412B4DF49C93FABULL, 0x28603724812D5336ULL, 0xE66476CE679D33B4ULL, 0x86A43F5435040225ULL, 
            0x3B973709FD38BD7AULL, 0x1D55D90EAB2C364FULL, 0x94D219AFEE9CC1E0ULL, 0x67E5355F11F5F8F9ULL, 
            0x7091845438D393EFULL, 0x37FEE6EE4C85EEDDULL, 0x3D80F6CC96EDAEE4ULL, 0xCB076408AB09A35FULL, 
            0x7D981BDDD6DA0B7EULL, 0x22A96460A238F9DDULL, 0xB7B80F987897ECA2ULL, 0xC83651E4C822B193ULL, 
            0x422AACDF75FDDC25ULL, 0x90D5AD5A30B5F664ULL, 0xBEEE1D62A11235D6ULL, 0xA9E1901846FF0684ULL, 
            0x0BD81ACBD4512733ULL, 0x3A2545D561109200ULL, 0xCE4FCBBD98094066ULL, 0x5319D26F4496318DULL, 
            0xD8A5EE61CFD0D4D4ULL, 0x6D82F2E9269F489BULL, 0x104D3744C28555F0ULL, 0x9E309DAD2FAE826CULL
        }
    },
    {
        {
            0x3D93533C81828050ULL, 0xE0A5CB5FFEFEBAC5ULL, 0xB42E1DA649332FECULL, 0x84876B2CC3BC31BCULL, 
            0x9C2A9D9670A6F94DULL, 0x264B1FD714E61AE5ULL, 0xC08B3B8BB4A83CF5ULL, 0x2DD5E8A0677CC30CULL, 
            0x4806B71421EE1003ULL, 0x6B8B807A25B0B0DFULL, 0xEF868A65A6A04D83ULL, 0xAC17E7FDE8696E10ULL, 
            0x6B982283FA646186ULL, 0x03470DE82BED04C3ULL, 0x39A93B1DBCF05D3CULL, 0xA300936BA0AB98E3ULL, 
            0x4721842AB62C5D06ULL, 0xFD08005A36B994B0ULL, 0xDAC262D03A68E10BULL, 0x83E8385FD72EFDE2ULL, 
            0x4EE13F2113172289ULL, 0xFD72CC1D35E584E2ULL, 0xC83C41834E4661BDULL, 0xC8143E077D4428FCULL, 
            0xB39138016E36A078ULL, 0x11CE529F27FF5E49ULL, 0x816A8789D3E77088ULL, 0x7B8024B95BFE1F17ULL, 
            0x9D240D23DC78FA0DULL, 0xAAF465B40F94DBD2ULL, 0xEE961DBFE17FA76BULL, 0x08009D54C0CD8EF4ULL
        },
        {
            0x451C1787FC3253B4ULL, 0x543871D24ADA2436ULL, 0xB0335333BF3A02FDULL, 0x4109286D90B0A74FULL, 
            0xF3E0161C0F1AC4C9ULL, 0xFCC602F3B0A709F0ULL, 0xC27BDD54F22F3ED0ULL, 0x21B785B2CFC9A360ULL, 
            0x9FCBB5A2F7C182B4ULL, 0xE5F296463E7626C6ULL, 0x3C2DB58F1A5A5DABULL, 0x2E51F2614BCA31B6ULL, 
            0xC020BFF5988A40C1ULL, 0x08A21C59E6C989A7ULL, 0xAA93082E6547AF2EULL, 0x5EE2158A1548BBC6ULL, 
            0xF47B3E28C861602FULL, 0x01F68917E6603C6EULL, 0x355A433B7BF19B88ULL, 0xB05EC3D3AD0BB7B5ULL, 
            0xAFDD35B84EE1EB97ULL, 0xD1ADDCD826301BEBULL, 0xFDF0A739B0D406BFULL, 0xABAF64242FFF0A22ULL, 
            0xE98AA55F69CADA3DULL, 0x14B074CEF68D83B9ULL, 0x6787DCC716A8C0ABULL, 0x3F0E85127FB69539ULL, 
            0xAAB427BB57346878ULL, 0x687DA94692EE79BBULL, 0xAE0D56C2E01E23CDULL, 0x8FEDFF20C2CDB253ULL
        },
        {
            0x141A61AE84FB7E18ULL, 0xC7DAC884C043902BULL, 0x2C5B86273FB55E25ULL, 0xED0E17A847E6B6FFULL, 
            0xB60929CF79DF525DULL, 0x5C8B5EFEDACDF845ULL, 0x5DBF22D8175BD0D3ULL, 0x85BC6F09CFB2A371ULL, 
            0x5A48F27F6FAFCE03ULL, 0x1EA5808E91B7646CULL, 0x396DE8B8041FE8CDULL, 0x2D7A1C0DA7B78D32ULL, 
            0x5F03080D89BA8DE4ULL, 0x0876CBB1A949C39DULL, 0xCF44763E878120CCULL, 0xB5BC8AC6CA4ADD8AULL, 
            0xDAE351CB2662F5D2ULL, 0x1A8A7BA5A7ABF7CAULL, 0x8AE5BD77F0496181ULL, 0x062844592CC50766ULL, 
            0x853297B95DDC52F6ULL, 0x9434D79E1D102BAEULL, 0xEACB716F4D9F95F1ULL, 0x09BAABB2729DFB71ULL, 
            0xAE3BB4B96CCA3B44ULL, 0x2665B8EDF82A1EBEULL, 0xE3BA362CBDBE393DULL, 0xC69E70A060D2F1F4ULL, 
            0x8FD002902556BFB2ULL, 0x17BB4163E736DFBBULL, 0x8F79768203D45841ULL, 0x2217633D7B70EB90ULL
        },
        {
            0x8AFE1FB3FC99DCE4ULL, 0xEF6A99BB2A014533ULL, 0x678057FF463C3598ULL, 0xFB5C252DD25DE3D6ULL, 
            0xCC4464A7BB77077CULL, 0x29E2BFB724FAEAD7ULL, 0x3B04272DD1EBAA85ULL, 0xB23808DA1C5B8773ULL, 
            0x81D79247ED2A706BULL, 0x74EBBAE6D102601FULL, 0xAA9CB6A887FE7E6AULL, 0x57E3633D06F05F4BULL, 
            0x7AF28E0F2B0185ABULL, 0x9DF86133C11B5D07ULL, 0x9721A8ADC97D78A7ULL, 0xB20425EDA1CA9E39ULL, 
            0x6FDA1017827F03EAULL, 0x99F023667B86A033ULL, 0xA351BC34E7AE6FC7ULL, 0x05E7C3454A8EB44AULL, 
            0x4FB9E2AF0AA8ADFEULL, 0x797C7A262EE8EF76ULL, 0xF652BD57F1F2D920ULL, 0x3B61C03717F56663ULL, 
            0xAB56979207713757ULL, 0x92E48BE127D07147ULL, 0x9D3F69212A41979FULL, 0xF7F6B7D4467F2A86ULL, 
            0xE788D448FE53A3F8ULL, 0x0FE9F9CC6550E459ULL, 0x00F74113EF80980EULL, 0x13B0A0F60F2C5101ULL
        },
        {
            0x23481045D62A7CEDULL, 0xB24CC9EAE7082806ULL, 0xFAC7A204BD8B30ECULL, 0xFA58B2FF36AA44FDULL, 
            0xFA4431C189EA446EULL, 0x36A254C5173032C0ULL, 0x359B17BB62897C83ULL, 0xFE126679F8D66F5EULL, 
            0x324647A3A87861BEULL, 0xECB5A47CCDC4A02AULL, 0xF40E88A843E032DAULL, 0x9CF6B42DE656EC1CULL, 
            0xFFF784DA32520C71ULL, 0x043B727E4A7016F1ULL, 0x9AD27DE9D5C23C1BULL, 0x819DAE2E1A25CF78ULL, 
            0x5434DC0A7C666CDEULL, 0x6F4B0540BCD8D571ULL, 0x5FB5C607946B92A2ULL, 0xD2F0E4A167DBEAE5ULL, 
            0xF3C8DC578059684EULL, 0x547E57D5F3E6979CULL, 0x97366998D09268F5ULL, 0x1A669BF9E9E92E96ULL, 
            0x3397F6309BA327F3ULL, 0xD2127BE85DDB7B8DULL, 0xE1F5812134D62DE4ULL, 0xA6D57D2E384E6C93ULL, 
            0x722BCDEDBC4C202EULL, 0xE9C548E5A084F112ULL, 0xD1DDF199A2DF7B10ULL, 0x67C214FD0FD08B8CULL
        },
        {
            0x229C6C82DC7B170DULL, 0xC69A5A9776AC060BULL, 0x1FB38E5EE57FB1CBULL, 0x7376CB51E228A1AFULL, 
            0x67009A5E2EFD9B97ULL, 0x2A162829E8F61683ULL, 0x53EFAAA019E57B6AULL, 0xE32F27CC34931A65ULL, 
            0xEE2B43F9A6CDBC52ULL, 0xB32CBE9B83DF77C6ULL, 0x94873294D13746E1ULL, 0xE6DCB740E5FD1F5FULL, 
            0x456306241B5B34F2ULL, 0xE05CBA855D0AFE46ULL, 0x1E599DA968181D50ULL, 0x5B83B4E8629DC040ULL, 
            0x2C2FFADD72254522ULL, 0x99031A2291835707ULL, 0x6003C408BC88CFADULL, 0x38319EBC344A693EULL, 
            0x5C9728069DCC1A87ULL, 0x23D3B590267F4A93ULL, 0xB8A83CCC2DEC8EFBULL, 0x443E8883E5AF9EB4ULL, 
            0x6A4AA0E6113886F9ULL, 0x5F63D0611A04513DULL, 0x9D7BF447060D0140ULL, 0xA9FC2883BC15AF3EULL, 
            0x367FECD06EA28C3FULL, 0x70F9BC5DBAD0FF2FULL, 0x950C635406DEA6C1ULL, 0x0C1F587A14FC2BF6ULL
        }
    },
    {
        {
            0xC8CAB7C05E7D2DCDULL, 0xC93C116CB0F291CEULL, 0xA02918A44BBE1D42ULL, 0x4B5E0F16688D1340ULL, 
            0x4E087D2898247A8AULL, 0xDD0F9D76F771928BULL, 0xAF3A06E9FDA01DEEULL, 0x3D4D3A7B4A920798ULL, 
            0xF49454F15FFAE84EULL, 0x57A4663CD8BACEE3ULL, 0x198D083F85CD9CB7ULL, 0x394E33436559992DULL, 
            0x4AF4225F02BA9353ULL, 0x9DE21F2B07E9463DULL, 0x81415CAD751D66C3ULL, 0x6E614A881606A4A3ULL, 
            0x8D8F06B977D11956ULL, 0xB453A0B0475D5C36ULL, 0xB1C256B05EB40A09ULL, 0xF88EA0FC26CE69FEULL, 
            0xCFDFE5132FF6D0BCULL, 0xF329CE4CAFF63B19ULL, 0x34563F187F278739ULL, 0x1F6CF5E2EF1FA59AULL, 
            0xA76A68288442D8F1ULL, 0xB19D1ACCFC9A5AA3ULL, 0xA7F5E5DEC4BDD4B1ULL, 0x0D7E703D83802394ULL, 
            0xF41B2CE59DF2C867ULL, 0x647246AABCFDE8BAULL, 0x0A8A28A6CAEB40C7ULL, 0x9819BE9C2F72D3B5ULL
        },
        {
            0x29232DEF85DEB46BULL, 0x5F3E23364165D9C0ULL, 0x0FA2CAF0F564646EULL, 0x5A7ACCED53DD057DULL, 
            0x329EEEE7F375D2ADULL, 0x846C9621B46D4C20ULL, 0xF67F7A1E3592B95BULL, 0x9E34DFC5A37066FBULL, 
            0xC32F03463D40E4FEULL, 0xC15173270BBD2A3AULL, 0x19E5ADADAF45F76BULL, 0x8D4AAAAAE8F92777ULL, 
            0xB84D38F88A69E3B1ULL, 0x39D879E7B143379DULL, 0x457FB67A330DAD27ULL, 0xCD1C1E0B853E90C7ULL, 
            0xF1AB4CF0D21AC74DULL, 0xFEB1C7E608F0F35FULL, 0xAEB152631DE9FEEEULL, 0xDF256C523D8DEF36ULL, 
            0x1850A14A7823D7F4ULL, 0xBD787CD193B00265ULL, 0x36128047677D1E8DULL, 0x1ED76243B3E40BF8ULL, 
            0xAD4BC1D668EA83E8ULL, 0xAF56DB330CDE3E07ULL, 0x3D4C77B2DAA1FAA7ULL, 0xA6E0D00783F6A138ULL, 
            0x953EB841F8728B88ULL, 0xE3744400AF80F4AAULL, 0x99785037872DBF44ULL, 0x82F4CB19ACDF92B6ULL
        },
        {
            0x1138D371DE611A53ULL, 0x00E80C2083C9E648ULL, 0x1F52FF06812BD1ECULL, 0x95E306BBA849EEEFULL, 
            0xE613B37C1170C2ECULL, 0x95868CB2C5A215A8ULL, 0x3EC70A4351770B49ULL, 0xB46FC28555B6F158ULL, 
            0xE8405A6CA461759EULL, 0x60A0558F1C93AA24ULL, 0x082806A0556325C1ULL, 0x7FA364DBF9AC0180ULL, 
            0x0BF3D655B0BB8D80ULL, 0xC7599BF15428479AULL, 0x1D893B3BDC372F21ULL, 0x469E73ED7BD59DEAULL, 
            0x63E22B94389893DBULL, 0xA6C35D99941188C9ULL, 0xA8A34A05B10FB659ULL, 0xA314C12CE22410BDULL, 
            0x9E9683DA53372ADCULL, 0x4F29412F7B2E5104ULL, 0xE66650D73ADCE14DULL, 0x8524F7FFCCB11C28ULL, 
            0x8ADCD190D3F2C97DULL, 0x28BA696DE32B7AACULL, 0x59AB2F81473883A2ULL, 0x1EBACBB4E62746B9ULL, 
            0x8FD0336141E9B48EULL, 0x29C632AEB7262D90ULL, 0x0F8B18153B83DD64ULL, 0x9767B03EDE3F5499ULL
        },
        {
            0x10D4CBC5D4388FFBULL, 0xFDE568503D887DBDULL, 0xF43726D908FD6662ULL, 0x545387FF23B9BAE7ULL, 
            0x6E08259ECE4B45DFULL, 0xE87867E064710F01ULL, 0x142FFBF4AC0ECC8DULL, 0xAFEABD470C305D4AULL, 
            0x47917B87AE2B8306ULL, 0xF899317121516116ULL, 0x5A74D9E3A21DA971ULL, 0x58734BAE63B6495DULL, 
            0x114EACE689B3956DULL, 0x2DD8DFA7E910049FULL, 0x6E2AD0A033ED76C3ULL, 0xB4FBA38CBF774499ULL, 
            0xFE36F97618A3BCD7ULL, 0x13A29C420997181FULL, 0xAC4930F84D23E46DULL, 0x67E07F8690A59947ULL, 
            0x1262A996DD6D5B5FULL, 0xC3C2FE5FE68A30E7ULL, 0x685D0208A863EB49ULL, 0x22084C5BE698D3D9ULL, 
            0xAE78FC3AE817ED58ULL, 0x8B05D37738634D55ULL, 0xEAC62BEC5061E071ULL, 0xDFCF155C8CDB4B04ULL, 
            0xB5622E38F45BB038ULL, 0x8627F67FFD5ED4C2ULL, 0x3FB14A216C2ECAC8ULL, 0x7AF287A278667AE3ULL
        },
        {
            0x0AB0BFC7A4EC5D27ULL, 0x12D7ACC04AAE8A1EULL, 0x921D1B1EB907DF0BULL, 0x6FC613F6111C5D10ULL, 
            0x38EB345ED134149FULL, 0xDFA6D03EE227AD44ULL, 0x46113ACE306635BAULL, 0x47E06B9F8416B60FULL, 
            0x5F2AD0ED79236B63ULL, 0x0C3C088FEF6B5BFEULL, 0xF75E327C671679FFULL, 0x22F229D8FCDE00B1ULL, 
            0x6C9B71314DE2AB0EULL, 0xA555290CFDA885E1ULL, 0x717E7E3934A84B7CULL, 0x8007E709C038B782ULL, 
            0x75DA4AA6AA6DAACFULL, 0xA60D142867DB797CULL, 0xEDC0A52AE89BCC32ULL, 0x6D31B0E6AD253EA3ULL, 
            0x944B92AF0DB1116DULL, 0xD21D6FBBF2090798ULL, 0x12DFAC030B7D7FAAULL, 0x8DE6953B58ACF14FULL, 
            0x02BA1E6769356362ULL, 0xE3DA718322E9BD6BULL, 0xD3DD15759D4E3B73ULL, 0x6D9FB82EC000DC0FULL, 
            0xE9BD31E0DC660A58ULL, 0x3414E0F0C5B6EE3DULL, 0xB798750C82A262F6ULL, 0x67DA1E939EA9FFA6ULL
        },
        {
            0x40DBD14FD023D3EFULL, 0xAA033104E1760F3FULL, 0xBAD10CB05D1AADD4ULL, 0xCA45F0452EBA0CC5ULL, 
            0x07AFAD68BCF28DAFULL, 0x7B1434EF8A4C951DULL, 0x8FDA2344E0AF5FE2ULL, 0xEA2139B3BD590982ULL, 
            0x8259FB46BB885414ULL, 0xB871350632FBFC1AULL, 0x3228D2899ACE3FC6ULL, 0x27690A30BF81D765ULL, 
            0xC28B5735CBB91E42ULL, 0x73C77AA1CE6997ADULL, 0x55B08CC26D2C551EULL, 0x95337133A8159689ULL, 
            0xB8CFD63888AFE030ULL, 0x398F3D0292F6E5F7ULL, 0x8526CDD9B837DA45ULL, 0x88F4CD3568531EACULL, 
            0x443BDAEF0DFB5DE2ULL, 0xE064B10A3409D70AULL, 0xAF3ED1E22B5ACE45ULL, 0x8039C91B8E2CC8E6ULL, 
            0xAEC1E5424CB2513EULL, 0xC66CAE1D8F4B119DULL, 0xFCD488686886CFA4ULL, 0x4022148EF063A8CFULL, 
            0x007C4094656FC18EULL, 0x4E19F4CFC7977873ULL, 0x5A30A575B6C80E46ULL, 0x6AD449BF7DF00C6CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseHConstants = {
    0x8F5ED24E892E08B2ULL,
    0x1373CA9D6F4C0B65ULL,
    0x3BADB330B738E9B7ULL,
    0x8F5ED24E892E08B2ULL,
    0x1373CA9D6F4C0B65ULL,
    0x3BADB330B738E9B7ULL,
    0xB8F5AB07B85769A7ULL,
    0xD390113E68F9498DULL,
    0x24,
    0x74,
    0x20,
    0x1B,
    0x24,
    0xDE,
    0x9D,
    0x6A
};

