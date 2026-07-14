#include "TwistExpander_Alkaid.hpp"
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

TwistExpander_Alkaid::TwistExpander_Alkaid()
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

void TwistExpander_Alkaid::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD6199B236A67E229ULL; std::uint64_t aIngress = 0xEBE0835E25E02AC9ULL; std::uint64_t aCarry = 0xE170100EFDAB01B5ULL;

    std::uint64_t aWandererA = 0xFDFB0CAF62A2709EULL; std::uint64_t aWandererB = 0xDDE634C345191C44ULL; std::uint64_t aWandererC = 0xC6888A3238A27A44ULL; std::uint64_t aWandererD = 0x9CC3D67155EE23DDULL;
    std::uint64_t aWandererE = 0xAB341A7B419C7FDEULL; std::uint64_t aWandererF = 0x890E92E5CAF64509ULL; std::uint64_t aWandererG = 0xA889054DAC4DF373ULL; std::uint64_t aWandererH = 0xE42E1D9F0C947C3CULL;
    std::uint64_t aWandererI = 0xFB630586070FF1A1ULL; std::uint64_t aWandererJ = 0xC010C50A3D3AF078ULL; std::uint64_t aWandererK = 0x863CA411487E53A3ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17770350050650151240U;
        aCarry = 15368336711784510861U;
        aWandererA = 16706167489838611022U;
        aWandererB = 16092455755035569835U;
        aWandererC = 16746637473649800861U;
        aWandererD = 16368348253311886695U;
        aWandererE = 12005340442115669040U;
        aWandererF = 17727858695228694599U;
        aWandererG = 12450032079131546661U;
        aWandererH = 17682839344170257202U;
        aWandererI = 14228853064547243500U;
        aWandererJ = 14940832231208359665U;
        aWandererK = 16782120994908258072U;
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
    TwistExpander_Alkaid_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alkaid::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9B13B8941B346280ULL; std::uint64_t aIngress = 0xEECE94DEAC42359BULL; std::uint64_t aCarry = 0x8F01DE61C075891DULL;

    std::uint64_t aWandererA = 0x9FBF6FD4E333C92BULL; std::uint64_t aWandererB = 0xE35BB36FD129EA93ULL; std::uint64_t aWandererC = 0xD76717D734F36177ULL; std::uint64_t aWandererD = 0xC0BD87AB88A6679EULL;
    std::uint64_t aWandererE = 0xF10B9C324CE087F5ULL; std::uint64_t aWandererF = 0xA1BE485861C727F9ULL; std::uint64_t aWandererG = 0x9F945C384FA93C7FULL; std::uint64_t aWandererH = 0xB7319D33E903D587ULL;
    std::uint64_t aWandererI = 0xEF19B31AA34AD21CULL; std::uint64_t aWandererJ = 0xB20AC88ED6BBFB46ULL; std::uint64_t aWandererK = 0xD681D30B1303EF90ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16542875844927103900U;
        aCarry = 10853968058579045303U;
        aWandererA = 16236617869842673105U;
        aWandererB = 13749500932205164678U;
        aWandererC = 10631092833613962569U;
        aWandererD = 13754509089165959343U;
        aWandererE = 14282768533912850864U;
        aWandererF = 18257767913333956046U;
        aWandererG = 10964935958479500726U;
        aWandererH = 14535956880587346137U;
        aWandererI = 10899588014373490538U;
        aWandererJ = 17962531062636378052U;
        aWandererK = 13255214347650497551U;
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
    TwistExpander_Alkaid_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alkaid::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA09883C26B549C96ULL;
    std::uint64_t aIngress = 0x9449565157CAA501ULL;
    std::uint64_t aCarry = 0xAB39CFC0A63EB918ULL;

    std::uint64_t aWandererA = 0x9D602ACCF6361FB4ULL;
    std::uint64_t aWandererB = 0xDCE9501CB3863CF3ULL;
    std::uint64_t aWandererC = 0xD56AE9372472FD64ULL;
    std::uint64_t aWandererD = 0x8A56027DF43D4D51ULL;
    std::uint64_t aWandererE = 0xE61368192C1A49F1ULL;
    std::uint64_t aWandererF = 0xC34C740A18FF921FULL;
    std::uint64_t aWandererG = 0xC4B996292A1551C1ULL;
    std::uint64_t aWandererH = 0xF39ADE5E4AF15702ULL;
    std::uint64_t aWandererI = 0x8C6B2FFE7E084A0DULL;
    std::uint64_t aWandererJ = 0xA575BA89C2EDBEC0ULL;
    std::uint64_t aWandererK = 0xF52EE766BC44DE3EULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneB, 2);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneB, 6);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
    TwistExpander_Alkaid_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 5 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1924 / 1984 (96.98%)
// Total distance from earlier candidates: 7732
void TwistExpander_Alkaid::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1243U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 548U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1920U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 684U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 608U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1307U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1331U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 591U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1468U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1439U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 633U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1939U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 89U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 855U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 423U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 491U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 848U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1595U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 717U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 876U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1621U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1669U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1002U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 300U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 862U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 469U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 708U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1379U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 390U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 86U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 104U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1020U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1613U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2042U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 589U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 197U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1107U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 732U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 949U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1081U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2031U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1448U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 835U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1408U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 784U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 963U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1717U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1377U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 926U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 944U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 852U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1477U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1861U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1816U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 16U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 213U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 531U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 326U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 332U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 727U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1414U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1475U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1120U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 856U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1351U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 342U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 3U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1832U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1641U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 8U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 910U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 84U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1406U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1720U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1127U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 292U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 723U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 159U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1940U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 695U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1309U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 744U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 391U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1409U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 947U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1156U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1631U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1947U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 696U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 394U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2005U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 956U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 582U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1152U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 616U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1150U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1357U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1766U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1432U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1189U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1271U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 374U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1356U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1072U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 606U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 605U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1954U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1370U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1380U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1233U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1202U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1761U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1471U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1452U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1967U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 984U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 689U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1794U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 766U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1780U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 151U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 307U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1663U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 280U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1508U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1030U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 452U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 858U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Alkaid::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xAE5A00DAA606FFABULL; std::uint64_t aIngress = 0x941A6B0BA48349C8ULL; std::uint64_t aCarry = 0xF42BFC9A52D98925ULL;

    std::uint64_t aWandererA = 0xA8DDDDF9BABD1BA0ULL; std::uint64_t aWandererB = 0xE9585C15FA97F9FBULL; std::uint64_t aWandererC = 0x887589FEAB0769ADULL; std::uint64_t aWandererD = 0xACA429789A77183EULL;
    std::uint64_t aWandererE = 0x8D8F35B2A138E0C3ULL; std::uint64_t aWandererF = 0xF8E9B3E44AAF0AF1ULL; std::uint64_t aWandererG = 0xC1A21AD2704B696AULL; std::uint64_t aWandererH = 0x842217CE15435FB2ULL;
    std::uint64_t aWandererI = 0xB0AC31B0EA074716ULL; std::uint64_t aWandererJ = 0xEAAA98D6F173C053ULL; std::uint64_t aWandererK = 0xB357EAB1EFADE779ULL;

    // [seed]
        aPrevious = 10900801257013435569U;
        aCarry = 11371314522848940742U;
        aWandererA = 13884842497663408301U;
        aWandererB = 15276425897939046028U;
        aWandererC = 15928565820450818025U;
        aWandererD = 18308057674834979996U;
        aWandererE = 11495610019802858494U;
        aWandererF = 10566256945382221149U;
        aWandererG = 13874936979090124359U;
        aWandererH = 9603123971256885380U;
        aWandererI = 11292392898007781770U;
        aWandererJ = 18247472617727651696U;
        aWandererK = 17281757036254874647U;
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
    TwistExpander_Alkaid_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 5 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2321; nearest pair: 533 / 674
void TwistExpander_Alkaid::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6121U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4939U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7910U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1439U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 759U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2844U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7512U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6357U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 352U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 810U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5766U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2165U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2697U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1513U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6718U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2381U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1890U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 629U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1049U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1314U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 741U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1078U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 811U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 973U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 390U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1022U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 577U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 265U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2036U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 733U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 192U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 230U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 649U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 73U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 23U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 261U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 5 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2321; nearest pair: 540 / 674
void TwistExpander_Alkaid::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 812U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6682U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 43U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5906U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7889U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5405U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1822U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7722U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6003U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7254U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3418U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5369U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3631U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7618U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4224U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5697U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 115U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 744U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 947U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1724U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1965U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 44U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1429U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 108U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1023U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1114U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 721U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1302U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 798U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1544U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 192U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 500U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 973U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1834U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 260U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 806U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseASalts = {
    {
        {
            0x9232688C0990489AULL, 0xA382C53023CC5A0CULL, 0xD2B802159C8D59E7ULL, 0xE84887699F0CC11DULL, 
            0xC7F82B1840F94DC1ULL, 0xF9EE01B95B83A690ULL, 0xECE8F6A7A226C6D1ULL, 0xB489D36C40859D0BULL, 
            0x982E7A5DA49600D7ULL, 0x9ECC033AB2F639F7ULL, 0x07F371E6059C2946ULL, 0x88465A137F7E7BFBULL, 
            0xF9C5E5CC72E3CB1BULL, 0x2A62375430BA9539ULL, 0x6DA6DC265A6462F8ULL, 0xFC51D97D5400E8B8ULL, 
            0x5B9D5D341751CC48ULL, 0x52671E155FFF3922ULL, 0x9874031D7FBF8672ULL, 0x220FF737E1C8C399ULL, 
            0x598A21EBDC577A03ULL, 0x0229357248C622F4ULL, 0x3C3EBADE08FFBEE4ULL, 0x160D7D16DFE2901DULL, 
            0x4995A5AE2C594357ULL, 0xBD10C4D670CF2E61ULL, 0x7B0E38813C3CF4DAULL, 0x590D36BE1BCC3FD8ULL, 
            0x83ED7A5B20A3C581ULL, 0x6EC4424B4A52E725ULL, 0x894BA8302A3AE667ULL, 0xFEBF34DED553EEA9ULL
        },
        {
            0x86239EBA328EE135ULL, 0x3B4F99B8F320EB94ULL, 0x85009B9BB435726EULL, 0x6317C934FB0DBE6EULL, 
            0xBA71FE35BE66EE2FULL, 0x6C6EC1AE343C8B88ULL, 0xFEC7B35DE29F1E8AULL, 0xF6B818E79A87FBCDULL, 
            0x20995E28D9D0F350ULL, 0xB0F41B475718CD97ULL, 0x4506F8E254470FEFULL, 0x702742AEB8537046ULL, 
            0x154EB11F06C01860ULL, 0x8D20F51AD17CA66DULL, 0x8BDB45A72664FA65ULL, 0x832C9CC043F903D3ULL, 
            0x1223AE2BA6318B2FULL, 0x8DE6D70C63E48752ULL, 0x9E702BC8F73E4944ULL, 0xDB64A86FBDDEDCF8ULL, 
            0xF4EF11DC4939D5F4ULL, 0x40AB980078073118ULL, 0x053E5B401834D707ULL, 0x5F25ABC8E1472876ULL, 
            0xC479C749B7810026ULL, 0xAE306F31A7C625CAULL, 0x0F525445328BAB38ULL, 0xC1BE7AEF72A0FBFEULL, 
            0xA7A2ADCB6359205CULL, 0x3335519F72BDC8DBULL, 0xD3EA49E5E7628606ULL, 0xAC69D80BF3686AFDULL
        },
        {
            0x73BCC9687438828CULL, 0x84BD4C8C45A4ACE7ULL, 0x468C33B855917BBDULL, 0xC6ACD764AA1333C6ULL, 
            0x06B7AD799CD1E662ULL, 0x0ADB1CBAE8BAF4BAULL, 0xD5718D9C5F4ABDC3ULL, 0x6A9832463FA73B3DULL, 
            0x2569117A17075563ULL, 0x4378CDED07561AE8ULL, 0x186FA9FE2E0D15E3ULL, 0xABD1663D64785B22ULL, 
            0xD2626B9DED7D9205ULL, 0x18AF70B6E0C7BCE5ULL, 0x9879FF4AA6935739ULL, 0xE99CF3B706A8B014ULL, 
            0x821E7FC2DBFC16A3ULL, 0x3F23AE0A3486D48AULL, 0x44370721A21A3D1CULL, 0x91C144E03237610EULL, 
            0x950969F1AF1C76F0ULL, 0x1A56A4DEEB05E42EULL, 0xD5EE0FA5D6A92699ULL, 0x4B914BDDF23B26EDULL, 
            0x46CD9C84F0F13654ULL, 0xA4AF771257589B1AULL, 0xE76556EEBDE3EA33ULL, 0xA5FC482ACD5D6E18ULL, 
            0xEA8E9C780AE38412ULL, 0xAC95913C1B60EB6CULL, 0x0CC1082184E96A56ULL, 0x52B0307F1D72D7D9ULL
        },
        {
            0xC79D3F65B33ED6EFULL, 0x3A36C68F6B777629ULL, 0x874B727FF635D4E5ULL, 0x4F413C24EC3EB578ULL, 
            0xBA633DB22BA1F919ULL, 0x864F6FB9F1B31880ULL, 0xCDD237C505B8C092ULL, 0xFC7E8CF115519346ULL, 
            0xDCC02F3A3D1423ACULL, 0xCD7D5B889297C4FAULL, 0x98E465D731D636CEULL, 0xC937D0DF565FE4FEULL, 
            0x4ECA23FD382248F1ULL, 0x926989375532AB2FULL, 0xD545D99940118590ULL, 0x0FEC40601129E5D5ULL, 
            0x52E32910F0CF624EULL, 0x3D889F4D842E5320ULL, 0xE22040E41FFF06CAULL, 0xA996F80F1AFAB515ULL, 
            0xC2B4CF9E9E5B7F13ULL, 0x224AADACDF7E09B1ULL, 0x198666EDDB73767AULL, 0x95F4D689F8B61F0CULL, 
            0x11675A89981D9C5AULL, 0x3E00DA8946AB2CFDULL, 0x63F8B04035B09D5FULL, 0xCB5E631976EB96C1ULL, 
            0xCD915460935377FAULL, 0x98C2E259F1329AC2ULL, 0xD96601B56D55D3B6ULL, 0xBC9A068413D5FE2CULL
        },
        {
            0xC02FFFC199A55FD9ULL, 0xF14FC05F6C3AAC1EULL, 0x13A43CA37CD74B15ULL, 0xBE88855B6CA04CDBULL, 
            0x065DDD814DBB21E4ULL, 0x74425353F4B5BF3BULL, 0xB301AF37F64D2DE8ULL, 0x1542C1CDA08AC4C6ULL, 
            0x6089CB115F189B2AULL, 0xB4CAE92A4F28B43DULL, 0xCB3B068B84318A9DULL, 0xF8D48EACAF1DF5C0ULL, 
            0xA548F1C7394CBA8EULL, 0x9468A65DF4ABC97BULL, 0x53CD1064B845CD93ULL, 0xC0EC07EEE67250B9ULL, 
            0xD289EF8869E03C0AULL, 0x80D1576DEBB52E7DULL, 0xD07E7EE7326F0AEEULL, 0x5EBF257451CF2F84ULL, 
            0x0194F9073E47D802ULL, 0xFC427DC1833F931CULL, 0x082D21F5571F2A36ULL, 0xDC5EE56789454698ULL, 
            0xA635DEA28A5D3E05ULL, 0x9E69E9EA7759C69DULL, 0x2629368ED86835CBULL, 0xA3158E8BBD1A0196ULL, 
            0x5F98F1B695E8D969ULL, 0xD372059F9D7C9C3BULL, 0x49CC298E5D6D2A3FULL, 0xBFBA8662FEE8E465ULL
        },
        {
            0x35E562A64E11423EULL, 0x17BAA86EB22ABC47ULL, 0xBEE44BBA87A78669ULL, 0x220C5ECC573A5074ULL, 
            0xD2C03C35BB1DF85BULL, 0xFAD726552A489FC7ULL, 0x40BEFB6FB6EAFA37ULL, 0x9A6626EA69F17485ULL, 
            0xD13B2E89B5E30707ULL, 0x5A6C51414990AF71ULL, 0xA788833D11FE5194ULL, 0xC7B18B4FFEECDB07ULL, 
            0xC330590E66EFBE44ULL, 0x086B22CF3328B9D2ULL, 0x781E7076D559F0EBULL, 0x9078875F211EE098ULL, 
            0x490FE9EC57C96145ULL, 0x8F16A6383A5E4315ULL, 0x7A2E975552F6F0BDULL, 0x8C610A913189A5A4ULL, 
            0x3646D829CBF25206ULL, 0x50FCF7DFA3CFB6CDULL, 0x9619C7EF689A70C8ULL, 0xA422098231539183ULL, 
            0x2E60DBC35305F30BULL, 0x664907BF9B4FA0C1ULL, 0xFBC8E0DBF785EC4AULL, 0xF06E7A9B1ABBD408ULL, 
            0xA9C3CA605B29C2AAULL, 0x8B96CB331C840EC9ULL, 0x907E4D4E352C0A2CULL, 0x9B8CDC03D5199BEEULL
        }
    },
    {
        {
            0xD50BEC239280EE0BULL, 0x2D8EF0CBC1E76726ULL, 0xC821EB1534AF6A17ULL, 0x6A67341139A32E09ULL, 
            0xCE8C4CCC5D8AF994ULL, 0xC63CC3245F3657FFULL, 0xCE3512454652F1BAULL, 0xFFCD1B82C2482FBBULL, 
            0x1458DD7F17FC5CACULL, 0xDE824222C3F7BC6BULL, 0x017EAE7A060232E6ULL, 0x8AD63BF564691FB7ULL, 
            0x0C814C49FC141B27ULL, 0x3E1F0B949FF56795ULL, 0x750BA03FA29A0225ULL, 0x37C834B90BA0EEA8ULL, 
            0x6B2C87F0083E3424ULL, 0xD42B8BEA60111BCDULL, 0x490B3BF6C6387BE9ULL, 0xA33A021D9B3BEEBAULL, 
            0x7BFAFF4D74CA10E4ULL, 0x509806495DD16C4DULL, 0x072B927480C0F25DULL, 0x6ED37FD57B20BB44ULL, 
            0xA3CD30C902592CB9ULL, 0xEE77A888AA83D8EAULL, 0x02ABAD1EF6974786ULL, 0xC46635D54153E69FULL, 
            0x0FE3B8EFAB8A1561ULL, 0xA4C7AD18F6B1DC9CULL, 0xAE6C3AE18B6EE18BULL, 0xB4401563BE2A22E7ULL
        },
        {
            0x982BBC71BF7AAA01ULL, 0x3DDF0DFDD0DF9019ULL, 0x85F17C9936765073ULL, 0x8338FF15AC5EE6EFULL, 
            0xA08A08ABF0DFE3CAULL, 0x6A8D6B4D61D1C111ULL, 0x7031DA0E6ED5AA7AULL, 0x21C3FDA350C77AD0ULL, 
            0x593514EA345A32B9ULL, 0x20968ADE88515759ULL, 0x96FCB1F1E918AC4EULL, 0x1504E9505C692387ULL, 
            0xD9910FC4CBD4E9B7ULL, 0x47799B3BC5344D78ULL, 0x0FDA1B271759D4F5ULL, 0x90F7EAE42435AA64ULL, 
            0x3D8FBC847711E5A6ULL, 0xAB9A14C51460F788ULL, 0x59755AE5E2CB8D3DULL, 0xABB1AFF758EBEC0DULL, 
            0xE774FA02C239C963ULL, 0x93B884B7996D1607ULL, 0xCAE88350D5F0176EULL, 0x60B1A6075B50D92DULL, 
            0x3AD08889081238AFULL, 0x15E621E6BE0AC45DULL, 0x2232E000B68C346BULL, 0x29AE0E2F1EED399DULL, 
            0x49D604CE4011D0D3ULL, 0x98A59DF471321B40ULL, 0x2A3FABED52E07B5DULL, 0xA5900F2113425AB8ULL
        },
        {
            0xF00FC98CBA03786CULL, 0xF3083D59E4913FDAULL, 0xAD7B22CCFD0970DDULL, 0xA791780BB4A1DB7AULL, 
            0xA66498EA67EC857BULL, 0x2DB5255EE314FC09ULL, 0xA5D011BC9203F467ULL, 0x4EF6DC3F5DA06658ULL, 
            0xE99D3D8A8CB61BE1ULL, 0xE5A66A0285395E44ULL, 0x38D7D8ABAB2730BAULL, 0x3F3A2B935C494DA8ULL, 
            0x4BF7B04184F27E89ULL, 0x303FDE41F5E2DD78ULL, 0x8B078F3B8D02E949ULL, 0x8FEA4BFD4EFADD71ULL, 
            0x4BF5860E0D7CCDCFULL, 0x02069C1C619BB31AULL, 0xB2AEF0C1DBD6696BULL, 0x663CFBE871C7FDE9ULL, 
            0x5404084AD1E3057CULL, 0x20762DEEB962C142ULL, 0x199CE185C0778C9CULL, 0xF4FD9AABA2BE8355ULL, 
            0x89F1B235490D096AULL, 0xF2F0174607C0B1FFULL, 0x8F73E6DA22A15103ULL, 0x48A9C384FFEBFAB4ULL, 
            0xEEF0BED5C863B90AULL, 0x6CDD975CCB3D61B5ULL, 0x7F5A3E90F5CDD848ULL, 0xF857C9A85C54B580ULL
        },
        {
            0xB1999DC19ABF245FULL, 0x8EBE076EC397AB80ULL, 0x71205668FD60765DULL, 0xF0A0E2D4DAC0994BULL, 
            0x451E619B24BDE52BULL, 0xD80AA9E4D96A1E74ULL, 0x06AA3751B758F8E1ULL, 0x9E6A12847EF8586EULL, 
            0x04219B7CA1395517ULL, 0xAB8B041E41195584ULL, 0xE98EF5EBE9B1EBC3ULL, 0xA0BE792D13ADDA5EULL, 
            0x7ABE3993E7629EC4ULL, 0x50D6BC1E4B5DA669ULL, 0x1774DC91EB353D07ULL, 0x05F88C18E62B216BULL, 
            0x52E9A5BD9DBB8228ULL, 0x684936CFD0DC0173ULL, 0x8B34434B4630B42CULL, 0x64C3E583EE49BA3AULL, 
            0x5ACB14B609E8CC38ULL, 0x2D0F17B21A25917FULL, 0x8837F588DAA2CCE4ULL, 0x2215EB2160D027BEULL, 
            0x59BC36D7D1151686ULL, 0xD588F30C20FF7037ULL, 0xBB3877D7910F175AULL, 0xBDB3DEE729001B03ULL, 
            0xE94F3B79180178D4ULL, 0x3F6ACEE051ECF509ULL, 0x16235C4DE749BECBULL, 0x54ED1AC0D14BC42AULL
        },
        {
            0x551F5CF311D107DBULL, 0xE1A49129BDC843E5ULL, 0x9BA61CB5B263DEB8ULL, 0x7421FD032BF9173FULL, 
            0xE4C99F091A8EEEFBULL, 0x9F1ADA111DA3EBD8ULL, 0xFE9129960FEAFF20ULL, 0x1B7B64F87CDCCF05ULL, 
            0x02A9A06EC6F880B3ULL, 0x7C8EEA1E9112523BULL, 0xF7F8EE0B4709EEF2ULL, 0x489311B5E4FD9BDFULL, 
            0x788391B328572E60ULL, 0x73EB39577D1C5367ULL, 0xC7FF48B9D2111DC9ULL, 0x0C54A0479C5792D5ULL, 
            0xCB433D8286526041ULL, 0x124703442C588426ULL, 0x7E623B99D94DB532ULL, 0xE7AC8AAC5E08C32DULL, 
            0x4B8AE9B5A04B4F67ULL, 0x02B6F0B923B5CAACULL, 0xDF2EB48A3DB32161ULL, 0xB602B8D900491C01ULL, 
            0x0AAAD6AE4FD5C585ULL, 0xEE82A12BC0F4CA48ULL, 0x092493F64C2BBD3AULL, 0x1917B835887F8E0CULL, 
            0x966D454A9DC33DC2ULL, 0x6CA983F468F895AAULL, 0x3B69D3255816B5B1ULL, 0x2D3EB15A33D82A87ULL
        },
        {
            0x720445225BE5589AULL, 0x7AE2B32289D59F56ULL, 0x9B12AAD2E8F7EF53ULL, 0xCE60E7E88BBD875AULL, 
            0x55A228502E332DAFULL, 0x769239EC6FBC8393ULL, 0x98BECB72DF7B99D2ULL, 0xCEA93F85B3843C28ULL, 
            0x9CB4AACB63478305ULL, 0x9A1654369E7E904EULL, 0xA268CAFCD49F7786ULL, 0x95D99CB0CA92A8ADULL, 
            0x5002DF8B186E5724ULL, 0x2B5FA33B7FAEFC8AULL, 0x5230643663B1CEE0ULL, 0xA05FD284BD946AB5ULL, 
            0xE3744670050E6052ULL, 0xE4BE2FA596DC3563ULL, 0xD6829F9DC05AB581ULL, 0xE87EC891BA0F2DD8ULL, 
            0xD08FD6564CFDD52EULL, 0x6FCBAFDE75604B04ULL, 0x3AA51B2DBC554774ULL, 0x022175E8194D57C0ULL, 
            0x88DA0A7F0B2D613FULL, 0x7DA8737717F747FAULL, 0x76A7C2AB2E25D669ULL, 0x00DE20D0D6CE469DULL, 
            0xB10375E266A0AA4EULL, 0xA4E3D0958053427CULL, 0xCC42B62A7ED463A7ULL, 0xB8E9522475BE12A4ULL
        }
    },
    {
        {
            0x89324B29300146A9ULL, 0x4E8279565D303AD5ULL, 0x2A92B8FAE93E774FULL, 0xF832B96D6D050713ULL, 
            0xF8E29D7D0246AF5EULL, 0x1FD5D176AB1A37C0ULL, 0x6694E22561B3D639ULL, 0x52D53ABF4D463DF9ULL, 
            0xE6DCFCE76FF7DB51ULL, 0x0D71CAD2C58EE772ULL, 0xD9651C3B2AB6A827ULL, 0x77F84A7C08C62C08ULL, 
            0x0926B841FAE25DD3ULL, 0x1060644AEBEFB223ULL, 0xA4A5CF79357E1572ULL, 0x368D9B594F8E64A5ULL, 
            0x6DD5F94E7F7BA2ADULL, 0xD99883B4A6C251F4ULL, 0xA7D69E9098C53AC0ULL, 0x02F28987867E25F8ULL, 
            0x678882093E2CD3A6ULL, 0x9D50A15DFE9511B7ULL, 0x45298D512CCEC373ULL, 0x111AFE3D831BD00AULL, 
            0xEFE8EF0CAC4773C0ULL, 0x42F9CEB9DCEECCCAULL, 0x7F922F573F720808ULL, 0x27269D04D1FE684CULL, 
            0xD9AACC48E3776600ULL, 0x2E4179520D557530ULL, 0x97F2782CE8DDD269ULL, 0x204F0F8D0739F0FCULL
        },
        {
            0x0652BB2D8ECA366FULL, 0xF10B88EFE331A167ULL, 0x88A5548C6FF72CF0ULL, 0x7AF2BEFB2AB582DBULL, 
            0xE8EA0DDF010819CEULL, 0x1C9BF14C10F5D4F4ULL, 0x647A80B672B9BA77ULL, 0xEBCC6AA732E5B004ULL, 
            0x64A8BB1F23DD9EB0ULL, 0x25576913140D3B39ULL, 0x09B73B5234C8F19AULL, 0xB7DAE7605DB6FD5EULL, 
            0xF869E6AEECAB038DULL, 0x22A5D094D941B5BFULL, 0x3967EFB6FC06C34CULL, 0xD1A53FA8BBA57FE3ULL, 
            0xC1E786EE8EADD022ULL, 0xC31B6CDEC6117C2DULL, 0xDDCFC770C0D53BEAULL, 0x815B5792037E6D56ULL, 
            0x123DD1A2608FA723ULL, 0x7EA0199E22772B55ULL, 0x799EC33F9608D8A0ULL, 0xECD1F0ED488DEBA0ULL, 
            0x6B7309A48254AD6EULL, 0x2263B2D5EBA586B8ULL, 0x84DDFE84A1622EF5ULL, 0x06B285E43700B1A2ULL, 
            0x66FCC9A9E0FCD502ULL, 0x855F2C6312561AC2ULL, 0x4CE66CB89C8F6F3CULL, 0x31E99FC4E5CF4B23ULL
        },
        {
            0x87EB9FB294F25DAAULL, 0x050CF99B8BE80F37ULL, 0x1519A320E1E92E7AULL, 0xCE4B6118AA4073D5ULL, 
            0x9640BF52622D9D1DULL, 0x239FCABCB9B21C86ULL, 0xF0F8F5490054FABBULL, 0xFE459A9A01E9B683ULL, 
            0x2A866DC56390CEE8ULL, 0x98E059FD4DA6CBC9ULL, 0xE3E4094672850DF9ULL, 0xCCF35BE1C6B211E7ULL, 
            0x2BDF34D62A3555C1ULL, 0x29F889E1B8B74047ULL, 0xCBB9A8B0A3E76D53ULL, 0x6146AFD6A08C318AULL, 
            0x6AB4F97937AF4DFDULL, 0x0F93E859C106A3E6ULL, 0x9156DA68A2B8BF22ULL, 0xE0E5C6ED669A4B36ULL, 
            0x1463EB47B080B234ULL, 0x2E810DF826E09214ULL, 0x7135DFF6E6F8DBCEULL, 0x476826F94E270201ULL, 
            0x4256083840793DF6ULL, 0xD5082E3CC5255355ULL, 0xAEAF5B0195CDE001ULL, 0xDEDBBCA0AE6D3F45ULL, 
            0xD2D8143D628F3A16ULL, 0x34E54239C82687EFULL, 0x9D903E993248B0BBULL, 0xBDB19595C480A801ULL
        },
        {
            0xC598EF3DA85FD8A8ULL, 0x9C5A35F144582D9AULL, 0xC9D1FE254882A5CEULL, 0x812CCEC24E957588ULL, 
            0x807E9B380E721848ULL, 0x1A1895F6FEC21160ULL, 0x333EA135572433C8ULL, 0xACD4CC533D02B43CULL, 
            0x07221396B175DF4EULL, 0x499845F0C3650C70ULL, 0x80F8CD47E5DB10FAULL, 0x6C9BDE407AF06190ULL, 
            0xE2FC6C5E60CAB93DULL, 0x7ECF6B84D36ED0B1ULL, 0x69997055EF6F33FAULL, 0x33EB4E1A765696BDULL, 
            0x67F78041115BA45EULL, 0x18DA6CB358EA121AULL, 0x6767E5B69B70AB48ULL, 0xFE1E59D545B1EE3AULL, 
            0x1E229AEEAA8C3DEDULL, 0x8D587343A55C87E3ULL, 0x3CB6300636052029ULL, 0xD98EF8797D88487EULL, 
            0xD8DD955554FE9878ULL, 0x38FDA506FD7BA548ULL, 0xAFD54E3115D646CCULL, 0x2264470A21C2117FULL, 
            0xAAD05E868B32C1BCULL, 0x0005049F1951946CULL, 0x28E8415589D3ED35ULL, 0x476D0992CE896E0AULL
        },
        {
            0x795C9F121088CFE1ULL, 0x7773FCB148CD9687ULL, 0xBC2390BE5731374EULL, 0xD74F44B1AB2AC65DULL, 
            0xD6327D3CF5AD730DULL, 0xE06EC440A665FD4AULL, 0x2E78A71B85E3BC75ULL, 0x8266CB5B75161E49ULL, 
            0x7C7EA4E638901F30ULL, 0x819477B8B8B7D1F5ULL, 0xB8A7355122F13E4BULL, 0x75A6F5A20D18B291ULL, 
            0x0356264CCB10BBDDULL, 0xCF03286F1F2D63EBULL, 0x71CFA1388670E2D9ULL, 0xCF089B8C855CFA14ULL, 
            0x3CBC8E4A6B072ACDULL, 0xD34E81C03DAA494BULL, 0x0C2D37FA494276E2ULL, 0x55DB39574E0D019EULL, 
            0x65B15006C3A7C89DULL, 0xAE6BD8A5CD286776ULL, 0x12295BEBF853827BULL, 0x2834D9B938F3FEF4ULL, 
            0x05C05C9AA40ACF44ULL, 0x21501122AFC7ABD6ULL, 0x266ACADDB5A43EE8ULL, 0xAFC6F7372E9A86A4ULL, 
            0x4E8D74CAA170B4F5ULL, 0x24A9AA0930C608E3ULL, 0x0896A435DDC0C37EULL, 0xEFC9BD40A45F690BULL
        },
        {
            0xA3C94CE07D59B329ULL, 0xEE18E7E0A281C022ULL, 0x3ECEBD34E75F2ACCULL, 0xA6F520779B5D8B79ULL, 
            0xB569AA061CC0CF88ULL, 0x83D74C98D27F3640ULL, 0x0D999F0B3F2A3F8DULL, 0x980A79D46B4CC56AULL, 
            0xDF499B8BD1CC8B78ULL, 0x616F12EEC4D5B6E6ULL, 0xE1D7CBA0E4885853ULL, 0xEF26724E302AB728ULL, 
            0xCA837037364D782DULL, 0x5D30A79EB4D70A12ULL, 0xA621EECC74DBE7B2ULL, 0xF02FCD5FF6391747ULL, 
            0x23BEDE1270B61007ULL, 0x72DAA59B28112F5DULL, 0xFE20954559D1EB10ULL, 0x62955A3B866E2427ULL, 
            0xF798CFFB47A957E3ULL, 0xCF40B1EC85C15459ULL, 0x65805AD078B3BD49ULL, 0x2D5D3D6C655068AEULL, 
            0x63D36BF74C0AC01DULL, 0xD0C9FA2C427AFC91ULL, 0xB31972574A8AB6B4ULL, 0xF6601B6B5D587556ULL, 
            0x8A22B53E60A53384ULL, 0xB1E4EE4D288D5305ULL, 0x30B246DB05116E52ULL, 0xB694B104A78002A7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseAConstants = {
    0x4A1BDCBE2CF9ADA4ULL,
    0xB62FF236CA67E89BULL,
    0x7C120D706ACF307EULL,
    0x4A1BDCBE2CF9ADA4ULL,
    0xB62FF236CA67E89BULL,
    0x7C120D706ACF307EULL,
    0x1777110C9AF92C9FULL,
    0xBC50DEEDC9344E86ULL,
    0x2B,
    0x5E,
    0x52,
    0x7C,
    0x32,
    0x2E,
    0xDB,
    0x44
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseBSalts = {
    {
        {
            0x8BCEA532B0A36BC3ULL, 0x3FC533ABBA05580AULL, 0x8C74D297A6994C84ULL, 0x5CA076AC783ACA1BULL, 
            0x5EE22491AA1F1EC5ULL, 0xCB814C5B206A5C50ULL, 0x345F251F5C10997CULL, 0x9246A7FFD56BAEFBULL, 
            0x73A45E0C810A1BFFULL, 0xC7F15A2359E7CDF3ULL, 0x6FE95384D911AB47ULL, 0xE4FF1F5E5F427C96ULL, 
            0x921368563A03B6E2ULL, 0xA770B29EDD254544ULL, 0x6EC9835B68308217ULL, 0x830D9C2C366C6D32ULL, 
            0xFE7BD66040F3614AULL, 0xA0F59F1F5954D2B7ULL, 0x69471CDE8049AFF8ULL, 0xAF12AB133E0AABF0ULL, 
            0xE890C01E29784795ULL, 0x75D172D516F5809CULL, 0xCB3F60AC424762C0ULL, 0xE5835BAAC9A63A30ULL, 
            0xCD5297D8DC5D5B1DULL, 0x9F20A512650E0BE9ULL, 0xED7C4B5638299584ULL, 0x94FF353C2BDB7B67ULL, 
            0xD98E15F8403F59C2ULL, 0xCA67519C5C5BAD48ULL, 0xA98C848E969CFC4CULL, 0x561D754DDE1CD092ULL
        },
        {
            0x7D8EB7CF903A40E4ULL, 0xD2B43CF11AC829E7ULL, 0xF52CDC7746578A4EULL, 0x94CF5B9906034435ULL, 
            0x3BCE6267A93DD039ULL, 0x80ABA6EAF34F4069ULL, 0x6452D7B7FDD82756ULL, 0xAA9639F63F584ED0ULL, 
            0xA1935AE66DC02BB2ULL, 0x58D982E4D17E2862ULL, 0x9E9A8DAAD7AD95ABULL, 0xFF4D8E588ED4444FULL, 
            0x9440863B9361137AULL, 0x5CD1FA3F96161B37ULL, 0x139CEAB01035BE09ULL, 0xE6F48C9D437CAB97ULL, 
            0x81A582A4DE96F82AULL, 0x5FE8F0C2A52DD1B5ULL, 0xD849454E4526CDE3ULL, 0xC4D05E28EF8BC822ULL, 
            0x6C3757CC1078D071ULL, 0x9FE4D5CDA2865980ULL, 0x36724EAE7BDA7871ULL, 0x28BB19E71F973C22ULL, 
            0xE593C3F14D9C5C79ULL, 0x359C98A2B075C21DULL, 0xC183E0BD380B1F36ULL, 0x3B9BBBB24D895728ULL, 
            0xF2954AD67CE380AEULL, 0x53EA65D2DE266381ULL, 0xC9358802FC5E39DEULL, 0x9100E128C1A47EE1ULL
        },
        {
            0xCBC64F9D73F8F88DULL, 0x9A7E1A42CC4CDA79ULL, 0x0C5C0CF0C6B24DA9ULL, 0x403A1DF2CFA970AFULL, 
            0x3DF2F6EA6A694191ULL, 0x71832089AD0CBE1CULL, 0x86F690E34835A456ULL, 0x499B9E4E6F42DE8BULL, 
            0x2A9BC40762B8926BULL, 0x8E31EFF8410970A0ULL, 0x3E8958F5DC848299ULL, 0x0500EC384D1DBD4BULL, 
            0xF83662075CC5F575ULL, 0xBD84EE1B6C3F32B2ULL, 0x9926046A833C23A9ULL, 0xCE5D36B7520C118EULL, 
            0x8B7C193EED00DF62ULL, 0x53454F28FFDA3935ULL, 0xF6DEA8CAEA99E043ULL, 0x159565FEAF204741ULL, 
            0xAD924A61D29B4F31ULL, 0x2CBB79DC7D03150CULL, 0x6D9199118C69231BULL, 0x5D7E7D336CA5444FULL, 
            0x50A19BA3BD289309ULL, 0xFF92DF1E3F58EAC1ULL, 0xCF94195F167A3D21ULL, 0xFEC707667ADAFDB8ULL, 
            0x65B83FCD344B94E9ULL, 0xEC8A17E6452B2168ULL, 0x2BA041443B03CCB6ULL, 0x10C47FCAC35CBC7EULL
        },
        {
            0x789C185A0C4372F0ULL, 0x02F664AF0750F105ULL, 0x4621DBB17C94D57FULL, 0x0E7465BBB7947205ULL, 
            0x69C5730D28A5B72AULL, 0x8CF224ABB5057F62ULL, 0x650304CDF6169F77ULL, 0x207ABC4AE6577ECCULL, 
            0x41222728F354433EULL, 0xBA278BA79FF37B9EULL, 0x4CD453FEDA4D3D3CULL, 0x44F3C3C16593B84AULL, 
            0xA6BA7C9D6DA49178ULL, 0xBA430CB3C050BAA0ULL, 0xA1B6E93170223FD2ULL, 0x56D23E6E4AAA198FULL, 
            0xEEEB5891BB2A1232ULL, 0x1B6EBF8F30997233ULL, 0x0C107B99B865BF51ULL, 0xA53DF60EDCB1F05AULL, 
            0x1BB47642D42758A9ULL, 0x627D34AC3E9E4188ULL, 0x4312034777BDB1A0ULL, 0xC6922BE1CEDF902CULL, 
            0x04ACC4744E9DEF70ULL, 0x85225A5046C8348DULL, 0x8F024D21611547F7ULL, 0xAC086E9CC7774B5CULL, 
            0xCE017F40E0B8BC50ULL, 0x23FCBF4950F1324EULL, 0xAE7C34D28C0DCD14ULL, 0x3971BA00DD3F4B1FULL
        },
        {
            0x3BAC0BDBF5D784B6ULL, 0x4C0910A98FDB0772ULL, 0xD21C8AAF698B3237ULL, 0x9DFE8CF54A5161A9ULL, 
            0x811FD7C9E0952A18ULL, 0x0D12D9C42FB3E0C7ULL, 0x82052C8CAC7045B9ULL, 0x9C2812FA848F7AACULL, 
            0x48A6532D1F92B0C7ULL, 0xD69DB2881B88AAB9ULL, 0x2051CCEBAC0C2D98ULL, 0xE3D4A44FF5AC34A7ULL, 
            0x56C7301CB99B352EULL, 0x18D1D970C7BC4FC8ULL, 0x97AD1A60134FE671ULL, 0x1A71F9DD5C39C362ULL, 
            0xCCFF94C07B541C39ULL, 0xD60229122DF4B9DCULL, 0xAD23499AB0944446ULL, 0x0DA0A29E19BF1E93ULL, 
            0x1E446CE128FE7726ULL, 0x20E958B7E58B4785ULL, 0x02DD762F6225AE97ULL, 0xDADD2BB2249F8A39ULL, 
            0x1F58FA2FA2F64BEAULL, 0xBCA4F4A33D5C9068ULL, 0xB8BD057A82D7F154ULL, 0x9DCC8CA156954AF8ULL, 
            0xA57623C5346853D0ULL, 0x82EAE39328883A9EULL, 0xD512D040A3AF0496ULL, 0x94A9B47977B03130ULL
        },
        {
            0x411160F7E9B9877EULL, 0xE420970AC4C4521CULL, 0xAEAE9A19364BADE2ULL, 0x0E9BBB9442010A5CULL, 
            0xE2C72E645B76BF18ULL, 0x3AE261D30975B702ULL, 0x05BFB2658CD7AD2CULL, 0xFEBE2C81EDE9A12AULL, 
            0x1ADA3CC7A7333305ULL, 0xF622CE0E51E0E2E1ULL, 0x781454896151E5CAULL, 0xDE99DE1D69070ECEULL, 
            0xCE3ABCC05CB55675ULL, 0x38A7EFC3950458CFULL, 0x25E9E5D5B1363405ULL, 0x3680B6E58F6F5AA3ULL, 
            0xBFCE0EE8A44D3689ULL, 0x974A3E0E71392093ULL, 0x7A304E02C4EA930AULL, 0x80FE9C2F7336E445ULL, 
            0x5494C77694AABA07ULL, 0xEE9850C545FD3268ULL, 0x852D38A497CFC3B3ULL, 0x906C985502B83312ULL, 
            0x958CBC5EAB87BD22ULL, 0x4EE1EEAE0EA153C9ULL, 0x23F3200D7350E9F4ULL, 0x257FD5B73B7F0D39ULL, 
            0x5154A87773EA874FULL, 0x88832EE68762F788ULL, 0x84F8D8EAC362AC3FULL, 0xD40162C1F93E2E5EULL
        }
    },
    {
        {
            0xEBD8E49D41E2F5D7ULL, 0x3ABA1B68E4C34DD2ULL, 0xF511B093C2673AF3ULL, 0x8A36293388E6B350ULL, 
            0x0169F32E7B24348DULL, 0x291DA111393A0E0AULL, 0x817343F7DA1AE6FAULL, 0xAB113B2FB0E92A36ULL, 
            0xF388824C8739C0A0ULL, 0xEF33873B32763A2BULL, 0xA9996B059C43F57CULL, 0x91510924CD24354FULL, 
            0xFCAD83E8F60A084DULL, 0x550A2021E9DFE2F0ULL, 0x2ED45724FFA0524EULL, 0x92E3A12918B8B219ULL, 
            0x51672259A0E219C3ULL, 0xDDF06EB6197E371FULL, 0xD392CB2F14ECAAF7ULL, 0xE07B8650E5935980ULL, 
            0x9C8C66086D903DB9ULL, 0x458DB7B27658A928ULL, 0x272E2037C10B604EULL, 0xDE3ED10A09F91955ULL, 
            0xF7C28B94BBD67928ULL, 0x000AC917C68890AAULL, 0x7692269F91A33F2FULL, 0xD23AAF2DD226EB34ULL, 
            0x691A32C075644A03ULL, 0x90CE837CD71EE6FCULL, 0x4F5E90A8179B1A6CULL, 0x963636949F4DC8EFULL
        },
        {
            0xCFA3543015903BC6ULL, 0xB6812E34FA7FA7B6ULL, 0x7BEA0F88E8D47A9BULL, 0x5E924139CA7E4287ULL, 
            0x263EA856A32B2A03ULL, 0x45BA9B6C99FDC4C1ULL, 0x4B1BE832C1B94C0CULL, 0x20C8A5B319EBB93DULL, 
            0x287D9F5B7FC73D4EULL, 0x0B6F0F98F72A0E2EULL, 0x51DA1188450D3A93ULL, 0x91D843F3F4EB9125ULL, 
            0x5F4AFCF53B8BEA41ULL, 0xC117D583922F0E86ULL, 0x5353595D399909FEULL, 0x19A8A6ADBB79BAE5ULL, 
            0x5DB9DD144AEE6FB0ULL, 0xDAF8F3D95B081B9EULL, 0x41EB49777D19E864ULL, 0x889D73AD202E6924ULL, 
            0x1730B5C6D0856351ULL, 0xF545D046B1CC0902ULL, 0x539F1D191E9436AFULL, 0xCE35165104AAD5B0ULL, 
            0x3BE30198E7CF185EULL, 0xD60D3BF3539413E5ULL, 0x01544CB17878CB69ULL, 0x31B4F9CAEFF66D5CULL, 
            0xEB6C5AF78C3125C1ULL, 0x995FF641C7D2C771ULL, 0x56B5E7E5A955EF8BULL, 0x0A5D22812666F9BFULL
        },
        {
            0x3F39AE3AE4836D44ULL, 0xC8C35FED211FE592ULL, 0x18FF60621B90EBE9ULL, 0xF62D33FDF8E98272ULL, 
            0xDBE391CD11F5E334ULL, 0x96CC58CD5EF16661ULL, 0x0DE5CE0A9EC76DFBULL, 0x5833191B5CE68108ULL, 
            0x506A1A901CAF5EE7ULL, 0x53793DFD9D21831AULL, 0x9AD883697662C535ULL, 0xDF3F40AD41A1A17BULL, 
            0x8664C4EF7705A079ULL, 0x947EED2D4C446787ULL, 0x8E4C7792BBAB2B35ULL, 0x2FEE7A4BD45C1BEAULL, 
            0x0EB4019351524F57ULL, 0x895C5C699539423AULL, 0xDD3380466BB31989ULL, 0xDA053E5E06B4F60BULL, 
            0x176BD8A647DEF785ULL, 0xD8AA188910BE0B0CULL, 0x62852492CDB45034ULL, 0xF2FF4CBDB9EE96A4ULL, 
            0xB5C094A8B37D37BDULL, 0x3DE9C6B25F8A055DULL, 0xE4691D231129B542ULL, 0xD133485D664EE614ULL, 
            0x876F7E71BBB0C895ULL, 0x96A86FEC6B033F28ULL, 0x395A860DDF12A9ABULL, 0x9F4494D792FD9002ULL
        },
        {
            0x24A7A6E40B6CB479ULL, 0x1BAF9D07D5CEE2DBULL, 0x45DD268BF43012C3ULL, 0xC2E4E792955EEB7AULL, 
            0x34082CF94F5C5218ULL, 0xE037E9E2A56AD81AULL, 0x144FD439D0D96BB1ULL, 0xBE16B97F1DB7355EULL, 
            0xDAAD05DDEA0076DAULL, 0x97C0A72BE8F4EFADULL, 0x1E4BBF3527D9FD64ULL, 0x4946C2C3F4292AC1ULL, 
            0x5FDF164A42D59D32ULL, 0x23036F18B70755F5ULL, 0x1E42B6F64C924D20ULL, 0xFF3939CEC3FFB4A4ULL, 
            0xC98641C46F69DF04ULL, 0xE56F8B1F6913FED5ULL, 0x99FF2892E841C822ULL, 0x7A1021743206D01FULL, 
            0xD5C9790E6EFFC429ULL, 0x52F40A4F90CF5B65ULL, 0x088E5E6AB1117CDAULL, 0x4040F0FC82721D29ULL, 
            0x1CC055B9E7A15D86ULL, 0xAA5D2A1787F47EF6ULL, 0xEEB1ED40FE350F6DULL, 0x9FE5F3C93835CA0EULL, 
            0x62BA706C8A4451CCULL, 0xAFF1089DB9310FB0ULL, 0x058F87FFA852170FULL, 0xA24114D5F3E2F0F7ULL
        },
        {
            0x6D8D30C6DBBBA777ULL, 0x60DE7707BB3727BCULL, 0x8A285127E44369FCULL, 0xC8A8BD5BEF2167F1ULL, 
            0x39FB6D1BF53E69E8ULL, 0x0CBAA959710966C6ULL, 0x42AE8AB09F1B97E9ULL, 0x9C02CC5E8A3D092EULL, 
            0x4D373D46B05C14C8ULL, 0x425B0E94FAFDBF23ULL, 0x6D1AF59F8F68FFC7ULL, 0xDC419D6AB08AFC68ULL, 
            0x9C731BD90B365D50ULL, 0xFE7FDCA1B0D9CDA6ULL, 0x7A832DF62B35101CULL, 0x251508C8BDA05976ULL, 
            0xE2C2240D66FCD7DBULL, 0x8D428B57B0AA8A82ULL, 0x0C2A009CDD020028ULL, 0x034378C318607373ULL, 
            0x3C914CBF06E439F2ULL, 0x9D06906399718A05ULL, 0xABB1AD75B6E089C6ULL, 0xE40AC0C1E5DF4B7EULL, 
            0x7259B7010C8F15A5ULL, 0x223D1AB275EC0575ULL, 0x6E171042256DD87EULL, 0x956F658C28D6002DULL, 
            0x5A4EEABBE329BF67ULL, 0xCA7ADF4122564DD4ULL, 0x95FCA0E2215930B2ULL, 0xDB16873A77E28105ULL
        },
        {
            0x169EA01C2607195EULL, 0x0F6700E3CE575BCBULL, 0x8CA0014AF22C0D94ULL, 0xC22CE43320D084E1ULL, 
            0x970C0E4C83FF4CACULL, 0x5D551C513A14F509ULL, 0x0DBFC246556A1F9CULL, 0x7C6FB56A56370D98ULL, 
            0xC3898E8E1E0A9821ULL, 0x2071CABF55A9AB7EULL, 0x4CAB306342924407ULL, 0x053C2ADEC107C0FDULL, 
            0x42AEBD8B6AA35B41ULL, 0x24D4BEF0B60BCC53ULL, 0x73EBD643777BCF65ULL, 0x0E104EC387E25057ULL, 
            0xA032AC453653DF58ULL, 0x891484EB413AD6F1ULL, 0x64AAC81DCCC7CB8FULL, 0xE405B481F0F10D90ULL, 
            0x3BDC8703FF2BBD81ULL, 0x098386329244AC3CULL, 0x140F791A7A8D0441ULL, 0xDB8596DF45D35DE7ULL, 
            0xB13F95408262D835ULL, 0x0FE60FA59548B5C2ULL, 0x5FACAC2EA9DB89D6ULL, 0x734F299B23FD8038ULL, 
            0xA3758F1533009165ULL, 0x7C515A93395B0FA1ULL, 0x8C053CB93B2B6FA0ULL, 0x445E5FF4E1311807ULL
        }
    },
    {
        {
            0xE6978C3DE70B1105ULL, 0x3CEB1F094C0B2A2FULL, 0x608FF15C3989DD70ULL, 0x9471C54B82022E08ULL, 
            0x30251C82CFF41F25ULL, 0x334C673A09110B9EULL, 0x80117EAC895FAA88ULL, 0x36C98DB620DA048AULL, 
            0x677FCCD99AB45B22ULL, 0x1746BB35F1D75DEBULL, 0xF75BA9D5B8292C16ULL, 0x4F35F7B2A4C799FBULL, 
            0xDFC5FB23FD920C05ULL, 0xB9A35AEA5310DE02ULL, 0xAECD46A28AEAA7BEULL, 0x89D0D3396C6A39ACULL, 
            0x8EC3C1D33D43488BULL, 0x79AC7C2E20B75FDFULL, 0xC972725840D3EFA3ULL, 0xB3A4E15BEB117D93ULL, 
            0xDDBE3568761D2BE8ULL, 0xB95594CE36C3C34AULL, 0xDB2298F1A0D65408ULL, 0x7B4089DE8F4BD632ULL, 
            0x8C3E4978D8EFA011ULL, 0xAF67B0C8B1D8B7B3ULL, 0x40B0BBCE22B05720ULL, 0xEF096583B9EE25DAULL, 
            0xED6C07055D61D395ULL, 0xB6AB369B64260828ULL, 0xE66ED1576732F591ULL, 0xD6AA3D573520B49FULL
        },
        {
            0xA7FE905944A8D94CULL, 0xCAB992006EEBDA15ULL, 0xDC9394B87778A5CFULL, 0x2E91BBC9D84CB0B6ULL, 
            0xE09D62A3A25E05EAULL, 0x948264035CBE2DC7ULL, 0xCC73DA5150C4B5CCULL, 0xA9DEE7FA6BAC2D17ULL, 
            0xF21D938BB216FAD1ULL, 0x96D65069FDF44335ULL, 0xDE40EE8C1D49E236ULL, 0x64A4C6A9B304104FULL, 
            0x7D5B4FCFBF306397ULL, 0xAC99B029EB1AA269ULL, 0x273D65EB4FC48926ULL, 0x7621AA20A71AC669ULL, 
            0x6ECA8EBC7CD669D8ULL, 0x97278DC9A5FF864CULL, 0xD0B3C566D2597C1EULL, 0x98C83455E8BDAE9FULL, 
            0xB38F54AC397B2F52ULL, 0x972426ACA5F090BCULL, 0x55E3D6F4F2EADD15ULL, 0xC91138F4CB44434AULL, 
            0x7A9CF75F4FAC8BBAULL, 0xD39A61FC7CBA77C4ULL, 0x22E0DC8429962759ULL, 0xDEB39599C5922590ULL, 
            0x6003FE3BA4BA9941ULL, 0xD97046FE1621A5E9ULL, 0x8DBED016BD4A0EDEULL, 0xC37BD2F0AC0BBFAEULL
        },
        {
            0x2691CAD8B8BF0CF9ULL, 0x62306A2BFE73DBE2ULL, 0x8BC3E948D579C87DULL, 0xBEAA2B884DCE6FBEULL, 
            0x0FFA0A860770929FULL, 0x70FB73391F752F6DULL, 0x4AA9D1E9061EF155ULL, 0x39BEECC5A71CAE28ULL, 
            0x07434184BE6E7F17ULL, 0xFA0C73643BC766F4ULL, 0xAB10C184718AE7B1ULL, 0x06B2077E7F84A41AULL, 
            0x4D0A3861036A1F12ULL, 0x9FEF917A13EE2E1FULL, 0x4752000D75E59DEFULL, 0xCB528EE5625984EEULL, 
            0x39DEAB48CDFC74DCULL, 0x18049838E1E77E5CULL, 0xC47A88E31244CDADULL, 0xC0444F7B92E2E830ULL, 
            0xDEE5A9A787F8D51EULL, 0xF7A308E6DE4D5DA4ULL, 0x250A1B3034374D26ULL, 0xDBF4AF1E2273D2BCULL, 
            0x3B70CF5E53A1BC12ULL, 0x4AAF7FB668C88C5CULL, 0x7AEA7A40FBE56B79ULL, 0x6DEC1B4A4F0C8654ULL, 
            0x9480000EA37B6B79ULL, 0x70DA6F33F9D297DFULL, 0x2F3BEB5DD703A3D3ULL, 0x13CA8A94BCB10D04ULL
        },
        {
            0xCFACEE6EFF6252BBULL, 0x5B64F70E469EB0BBULL, 0x5D62707B7656B7E8ULL, 0x177B0930CB3C6F39ULL, 
            0xDAE7D1B3D1CBADA3ULL, 0x1A5F67C7805D7150ULL, 0x9F19E8358FC19A6CULL, 0xE2F1B9B1D5CB6B17ULL, 
            0xC83B07C37FE9EE4BULL, 0x93AC887218A74FFAULL, 0x560840AEE305F5EDULL, 0x3B10638C155C2F4DULL, 
            0x064FC9B40DC8F18AULL, 0xA4C2E2222D7142EAULL, 0xCBA24EF2A6888079ULL, 0x92110F8A9ECBF98FULL, 
            0x0EC71C9125600300ULL, 0x7330915B6BF53750ULL, 0x28B5971C8D31225DULL, 0x286161212249DE46ULL, 
            0xC4E9B911126F24CFULL, 0xEDC93A40D7F649CFULL, 0xB79BD4706F416550ULL, 0x4D3760EACCB24BC8ULL, 
            0x9C7C664E22D53E20ULL, 0xD620C7C884BF53C2ULL, 0x40BA0B5A3C239727ULL, 0xE6B327B00C01466FULL, 
            0xBECA34DFB15D5B9FULL, 0x4A43F2E68E5DC6ECULL, 0x0A97C5ED9AED9D67ULL, 0x1EFBAD34D8BFDFF8ULL
        },
        {
            0x92C34E7803BC1341ULL, 0xDADD681527B65D2BULL, 0xA50EEB8E158CACC4ULL, 0xE2E55B499149B39CULL, 
            0x4C265ED6F1FE129EULL, 0x12E89078D3443E38ULL, 0xA25322FC1E9EE04EULL, 0xA2D3A2C638327483ULL, 
            0x37704C5D3C9F3712ULL, 0x0B80E779AB61DA9CULL, 0x61EF38034390707CULL, 0xAE489613CE574652ULL, 
            0x83C72209DE70ECB7ULL, 0x964331A813D7A64FULL, 0xA42725B8EFC6F98BULL, 0xCF4A2CA3967F7515ULL, 
            0x15E8E3E91D4126A7ULL, 0x07F32D04CA598ACDULL, 0xB4440F9E5AE1CF4CULL, 0xEB9159A96D483C8EULL, 
            0xCE4B1A44B64AE50CULL, 0x588786FE87F6A87DULL, 0xCF2C04520B185B4FULL, 0x50607CC650E6A87DULL, 
            0x40B6BB0BABF1C61AULL, 0xAC209CA74741799EULL, 0xB70B9E04426E74EFULL, 0xC25D95D5B760DEC9ULL, 
            0x2F7C9D174C066EC7ULL, 0xF76DC8126FE9E863ULL, 0xCB5916EDE4445BDEULL, 0x29485922C69287B1ULL
        },
        {
            0x66E20BB2E0D37D41ULL, 0x8DAF91FC10CD2E57ULL, 0x31DFFB7F9FD647FEULL, 0x5C5DA71575F2F0A1ULL, 
            0xB3A6A7EDF9ADBF34ULL, 0x1E086ADE5E3F3767ULL, 0x7F83DCAC4E81A67DULL, 0x8623C1EF40660076ULL, 
            0xF78B186B855E3C2BULL, 0xB63595970B3F16A1ULL, 0x37A72BFAB1852ED3ULL, 0x300C6402F91AF692ULL, 
            0x90ADDCFFA1F0EFF2ULL, 0x2CFD5EAF5BD3CE10ULL, 0x3A1DE98DC00D36F4ULL, 0x0375C4612ECD18D0ULL, 
            0x0C17AFADD25542E4ULL, 0x2072BD041525ED5AULL, 0x444240155C644B53ULL, 0xC9CF9D75537CC291ULL, 
            0xAB93B5133928C908ULL, 0x77BE02EA7E55B89DULL, 0x6719848745BA3235ULL, 0xD719255BADC4F91AULL, 
            0xE202F9A975129361ULL, 0xAD9FD26FEC4B19D0ULL, 0x8AD0A7B8EDEB7604ULL, 0xC674EA20F86AF99AULL, 
            0xD84A892A21FABD91ULL, 0xDB901F6FE50A4872ULL, 0xEEEBC47B4F3D5B9EULL, 0x38C15F5F904EF0F3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseBConstants = {
    0xDE0B9CF9D27D8380ULL,
    0x0C38302BAFB67793ULL,
    0x981D4DDB13BC10DAULL,
    0xDE0B9CF9D27D8380ULL,
    0x0C38302BAFB67793ULL,
    0x981D4DDB13BC10DAULL,
    0x296F921F5C16FC6EULL,
    0xC00CE00970AEE267ULL,
    0x63,
    0x6F,
    0x87,
    0x07,
    0x9A,
    0x13,
    0x84,
    0xD8
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseCSalts = {
    {
        {
            0xD2DAE327EB021C0FULL, 0xDEEA2139E7678228ULL, 0xD54547EB94A0AC3CULL, 0xD21BCB7A6ADA12D5ULL, 
            0x7EA04E171A3A329EULL, 0xAC3414922F1D27D6ULL, 0x0CA9F80FDA9BFA4BULL, 0x17824265EB50A33CULL, 
            0x9BBF870D40A636D3ULL, 0x390A453AEB718EF4ULL, 0x1592E51431D57386ULL, 0x1DA559902FD17AA4ULL, 
            0xD84CDC6FD28B284AULL, 0xF24A7817EB1E43D4ULL, 0xC7BADCCDA97B0533ULL, 0x3DA8010F9D2E029AULL, 
            0x79BEB9D706836848ULL, 0x35D4B401AB8F8C37ULL, 0x850A192A09DDD4E9ULL, 0xFA2C74331F641A71ULL, 
            0x1BBB7747922CD0C4ULL, 0x51400D4C8700D068ULL, 0x7206324DE0E7BC42ULL, 0xEE4688CA9E3AD2D2ULL, 
            0x4C36D44AB64982B7ULL, 0x30C3CE6AC6A9F2D4ULL, 0x6575A2EF94B7A115ULL, 0x98F063C53B5201ABULL, 
            0x9FAE5AA85D15E9CFULL, 0x661456E99F10EA70ULL, 0x3515252BB9B72AC3ULL, 0x6BBB70ACC1A6A7A6ULL
        },
        {
            0x870346DFBC0CD43BULL, 0xE15E1DFBC9E66AC3ULL, 0xFD663BCB98F1B87BULL, 0x4A4090DD5B6E762BULL, 
            0x4AEB0B0DA7795950ULL, 0xFEE0785C9B8EB731ULL, 0xDB6E198A0B965C86ULL, 0xF6C6124A9C5B8ED0ULL, 
            0x0D4CFED287124942ULL, 0xA58704828ECD6D1AULL, 0x291C9A51662416AAULL, 0x67A808D693A04C91ULL, 
            0xEF2EB89A028FFF86ULL, 0xBE4F8B74C4C4A7DCULL, 0x683290161DB9AE89ULL, 0xCDCBA508A586037AULL, 
            0xA06DC28A202FB51AULL, 0x5EFA19DEC8B0D04AULL, 0x127F5C113D56FFEFULL, 0x2DECE889CB6CDE60ULL, 
            0xA7A9C8FD84096A6CULL, 0x7AE2BEDF270F4FEDULL, 0xBD958E3B28ADBBB1ULL, 0xB058B3BFE5A4BD74ULL, 
            0xCE3B671EE6EAA007ULL, 0x2560E98A0B2C7127ULL, 0x8EC486C8A7570980ULL, 0x0ED8DD028949EFF2ULL, 
            0x9988069F84510D9BULL, 0x749F7F95B71158FCULL, 0xF2533EBCD7FA8BB2ULL, 0xBE1BF3DFD8F070CAULL
        },
        {
            0x47C37A19BD2FB30AULL, 0x04855458279F38D7ULL, 0x5F82DFC30F624A62ULL, 0x64719C58F0AC6D8BULL, 
            0x6E455E596723DD6AULL, 0xD93FA9338B845740ULL, 0xD3400BF154DAA4ECULL, 0xDD197BDC3E63E43CULL, 
            0x44B9A694983C8FD4ULL, 0x7B130F1BF97866BCULL, 0x5304A344FC59D4C7ULL, 0x1EBDCC47FFBB9FF9ULL, 
            0x513F90766D495EBCULL, 0xD0443F9383C03B85ULL, 0x24944B558C520868ULL, 0x4EFF60BD04F8E09FULL, 
            0xF0CEA3676BD16C27ULL, 0xE5CCE2C8D8557376ULL, 0x884F05F3F091A836ULL, 0x413281A2F0FCF369ULL, 
            0x9D258F855C21AA56ULL, 0x2323ACB09CE7742CULL, 0x2D3B00B4D4BF92CFULL, 0x19CC3A265A47D782ULL, 
            0x91E9846A96A5E4BBULL, 0xC31919DCE6BAFF6FULL, 0xEF0254C3A4349C5BULL, 0x0C07CBF7CEE5045DULL, 
            0x4B4599F7B378AA7AULL, 0xB53D603167E1AABCULL, 0x8BA963F08DAC3E66ULL, 0xC95C81C539A14BA2ULL
        },
        {
            0xAB36A33D30EB0F70ULL, 0x836384B31DAF2D82ULL, 0xDB1786BFC499F745ULL, 0x03CA123EA19866A9ULL, 
            0xE86D368BDDAE39C4ULL, 0x10C2A2C3B02DDB9AULL, 0xC92FD6BB5A794646ULL, 0x30BD2755CD00C0BEULL, 
            0xBD1E2A6921C9DEA7ULL, 0x3B5651661182EEC7ULL, 0x373BC17003F2619AULL, 0x52CB6B68416A0D80ULL, 
            0xEC0008496DF678E8ULL, 0xF48069148AD90122ULL, 0x30860AD9C18701A1ULL, 0x1F5560A025DF982AULL, 
            0xA493BCD92DE77CF7ULL, 0x3F72B76AFF732DBAULL, 0xCF5BFA489A049DD5ULL, 0x9F3A7028ED070CD2ULL, 
            0x301DCE371E270135ULL, 0x5860E40ACB8E9899ULL, 0xB78B73FC544760B7ULL, 0x43EDD53B533DBE7BULL, 
            0x631DE6357C88EE70ULL, 0x054F61A5E7EEC203ULL, 0xD184E6C0E21D8CB0ULL, 0xAE58998A29785219ULL, 
            0xB595D0B7395D8CC4ULL, 0xC42966DECFECC52CULL, 0x293C90739A8A214AULL, 0x1DBC1E2C92355721ULL
        },
        {
            0x4A3D6A05D9ECDFE5ULL, 0xFAA55FAEFD0D4C8DULL, 0x6CD509A0CADF5E4FULL, 0x3DCFE7FB248AB872ULL, 
            0xFE97540E303233FFULL, 0x2DFEAD10DFB06F91ULL, 0x4C52225EE1B0B85DULL, 0xA2F5C83E7A947A32ULL, 
            0x988BE25363E3B5BEULL, 0xB4BCA85388FF5A94ULL, 0x0A4DD5F304884E46ULL, 0x02CE1E49AB7343ADULL, 
            0x2846751210BFAC2FULL, 0x92E524ADEC52F933ULL, 0x4336692E2B4F7997ULL, 0x97F3587DB94CB280ULL, 
            0x9322274E656E27C1ULL, 0x9687D3A2CC3E2DC5ULL, 0x3E8636F96FA921F7ULL, 0x2E8462CE04AED439ULL, 
            0x7A701CDF0D0A992AULL, 0xFD6E7E76DBE18ADAULL, 0x9206464B5B02FDDCULL, 0x8E8B8FEAE4B20B56ULL, 
            0x84585C0DE50920E1ULL, 0xF30F0E353DAB859AULL, 0xB397095567F9EE4DULL, 0x3908F5EF5C18268CULL, 
            0x807387E30706979EULL, 0x08E00244DB45FA62ULL, 0x8CE57709E8F302FEULL, 0x2437CE82FE4E6819ULL
        },
        {
            0xD1F25ADA742D6099ULL, 0xCB2826DF83E72249ULL, 0xB48D34AA67B99BC0ULL, 0x875399A820AA343CULL, 
            0x946957CA86CEBC89ULL, 0xFF6E52FC7D829A57ULL, 0xDF499BD479FBFED0ULL, 0x9707BA75FF08A028ULL, 
            0xDEBEF4E9866956FDULL, 0xFDB468A939A7A1EEULL, 0xE1C1AD3BB749FDFCULL, 0xBB7BBD0685A3A07CULL, 
            0x3F43CD27C9EC93ECULL, 0x1A2CFB21A05FAE84ULL, 0x61C3543E14E44366ULL, 0x77EAFBD915F0D975ULL, 
            0xF5FF4D529BB38A4DULL, 0xD9F827DB2A9B2C85ULL, 0x0ED257B7E66FB3A2ULL, 0x7A0BE628E6B7B721ULL, 
            0x5A1D995D3FF0DD42ULL, 0xAAFEF4354D48CC58ULL, 0x84AAB34F73FCE5F6ULL, 0xB531AB444F8FFF1CULL, 
            0xD62BDF6CFD19F6AAULL, 0x8D2102ECE7B925BCULL, 0x118D2613CAD5DEBDULL, 0x0340273B08E7308CULL, 
            0x93244E653C251DEDULL, 0xB2BD76CDA3221BC1ULL, 0x74AFCEEBBC3F501EULL, 0x86912670A66BF093ULL
        }
    },
    {
        {
            0x5FF04DE42CF7CDECULL, 0x03BAF6E91E9E993DULL, 0xF6115DBB9531FBD2ULL, 0x5B2874EAAC23F99EULL, 
            0x5AA261F4B79F6503ULL, 0xE3AE1BCA503E0062ULL, 0x76B1458B96CB9159ULL, 0x421BC853C84B25EEULL, 
            0x5D02BE144D4CE1C5ULL, 0x8C80CEC1913B5D70ULL, 0x681701224A33674EULL, 0x2DB0228B6D21DE59ULL, 
            0x064D42B0F246E405ULL, 0x99273D2B986CA00CULL, 0x9C4565919203CF29ULL, 0xC018E482B821AC1BULL, 
            0xE4DAF9A55C6BF021ULL, 0x99D01D17EB894AC8ULL, 0x38486D0920B80F3BULL, 0x6FFB231471717C45ULL, 
            0x229D38AB68B0DB10ULL, 0x5289A41D58B94A67ULL, 0xA11BD744D356A6BAULL, 0x8F63BDAEB40F3F86ULL, 
            0x83E7894985BF8406ULL, 0xB91CD61ACC8857A3ULL, 0x7684534CDF9D6419ULL, 0xFA36D455D4FDBF08ULL, 
            0xE87FDB3C3F0D4EFCULL, 0x4C0AD7D3C83061DDULL, 0xB59F56520B616B73ULL, 0xDBF6C66B41D438D6ULL
        },
        {
            0x73CF83D36CA53E68ULL, 0x354A9577C8FF5582ULL, 0xBE3A71052DF19603ULL, 0x34703EB1328C2B39ULL, 
            0xF6BB5A051086FA43ULL, 0x6C9EFAAEF8940F7AULL, 0x837647E70877FBAAULL, 0x402C304E47DA2210ULL, 
            0x2C784FA4A6898BAEULL, 0x38DE60EA62C7E3E1ULL, 0x78CBE4D7FAD4E9E9ULL, 0x775D0808AC52557CULL, 
            0x4EBB367ECAB70DC4ULL, 0x287CAFEE0A240891ULL, 0x38C9B06CAD59BE70ULL, 0xD11A43A26C178C91ULL, 
            0x7DC1F16BA7870421ULL, 0x1B6B3FF0B74DE27DULL, 0x7645BC61AE47AE16ULL, 0x225D9FEAA1B77098ULL, 
            0x690C99BCEDAE80EDULL, 0x20A2FA8459E4CDA6ULL, 0x4343DB9ADD08962EULL, 0x8CAABCDF03681CBDULL, 
            0x9DE32F94E09462A7ULL, 0xA602C40A764C0644ULL, 0x0A10950F721A26EBULL, 0x54041958E66DF4A6ULL, 
            0xF79452D0945772CDULL, 0xF8BD6CF25AFED64FULL, 0x6053F6511887EF85ULL, 0x0F659F58203D17F9ULL
        },
        {
            0x5E2C176FE959296CULL, 0x5C5732ECD221F49AULL, 0x7A6B2D6C91C8CA1EULL, 0xD3FF3B4477232887ULL, 
            0xE48306E6AF68C8FAULL, 0x83DA2B811ACCB379ULL, 0x7C22DA8D47C4B148ULL, 0xF99B994141DE9C10ULL, 
            0xDA7A691A54555FD2ULL, 0xC175A99D90F3AF64ULL, 0x5D480BAFA4BA366AULL, 0x4237E87CB74793F8ULL, 
            0x0C76CA0A035DFDF5ULL, 0xC48AA4988D2F297CULL, 0x8635A1F514562620ULL, 0x881762E6065739D2ULL, 
            0x196FFD08DB226487ULL, 0xA38D8D302992B124ULL, 0x3895C90112F15A8FULL, 0x38F2D5703C6C3139ULL, 
            0x101BC33066FC8353ULL, 0xC57D02F20A073B81ULL, 0x132CD7F106270028ULL, 0xFB73191F1CADFADAULL, 
            0x31928AFE38231BC9ULL, 0x30323430887A6876ULL, 0xC21F5F6E00A9277CULL, 0x3C4BE956E173B2BCULL, 
            0x748605090C18C513ULL, 0xFFEF21FFB2100230ULL, 0x033D23E58D9C5A9EULL, 0x5AC8A72673F93EA8ULL
        },
        {
            0xE6701EE42DC50EEEULL, 0x075DC103D73DAB40ULL, 0x16980441AB8056FDULL, 0x0F2826D90839E413ULL, 
            0xD89F09762686AB09ULL, 0x14C000F60BBED2DDULL, 0x8F41297BBD51E160ULL, 0x75F11AFCC96CB6ABULL, 
            0xCC8594DBB6C1DFBFULL, 0x1DA04BD19E4E1187ULL, 0x5F5B01911672F520ULL, 0x1FB4AC464A269D20ULL, 
            0xCCA58A7CEA32FF53ULL, 0x95CDFD297CB43C3AULL, 0x0A2E3053ECBC7AABULL, 0xA0A2C9A62F0AD87EULL, 
            0xCFC72341BC97E405ULL, 0x7D1818C356B27590ULL, 0xD4A561D482133273ULL, 0x3794C4738D846A2EULL, 
            0xC6BC47746E5A0F3FULL, 0x418B31AF2F27018DULL, 0xF23D8A692345B360ULL, 0x0FE009401EE450ACULL, 
            0xE81EDD3F102BEC24ULL, 0x4EF2944C0A3899E9ULL, 0x4CEA51BB5329CE5AULL, 0x26061E57B1810D81ULL, 
            0xAB21C48B5F5FEE6CULL, 0xEFE15B3A98FCBDEAULL, 0x4DC44756833F0DE8ULL, 0xA1528FD27C54C713ULL
        },
        {
            0x06CBD4F7EAD0DA9CULL, 0x619E6A05C57DBD4FULL, 0x068BC9CD7BD09F26ULL, 0x4F9896D86D958585ULL, 
            0xEA89133273DCE6B3ULL, 0xB87DD0D792EB6DCFULL, 0xAA637919D98448E0ULL, 0x8C05F8D2B0D6EEEAULL, 
            0x53300EB9D906BCE1ULL, 0xD8605B8636CABD89ULL, 0x250BBBB1AC752D93ULL, 0xA542ABAB56077C6BULL, 
            0x393AAF882E797556ULL, 0x04A8DA2A9D8167E0ULL, 0x237BDCC09C7339BCULL, 0x2059EE4AD772C3D8ULL, 
            0x4694FF18808E747AULL, 0x4340137B68C27594ULL, 0x30EF8E986F081E20ULL, 0xC0C81EFCA5EA98B4ULL, 
            0xD252D65F079AE92DULL, 0x31D2AEDF557A042DULL, 0xA2C339189178A870ULL, 0x64A19073A5332370ULL, 
            0x870F8A10BD25C332ULL, 0x1CFCAE1B84A5E384ULL, 0x2353822E3595C095ULL, 0x730A9B9CEF362DDCULL, 
            0x6D29D959F5023A18ULL, 0x09F72566580E4BCCULL, 0xD7C23E160ABCC6B6ULL, 0x433C7EA12F7BE840ULL
        },
        {
            0x12274EA7CCE68563ULL, 0x8C3CEC57E82C9E63ULL, 0xCF7B85680812555AULL, 0x252A6A1BC2CDEE8EULL, 
            0x04BCF4F8035708DDULL, 0x1D90B8AFDC586EF1ULL, 0x7FF1F21985ACF8D5ULL, 0xFEBB7F3981262114ULL, 
            0x1254A6B50243EC16ULL, 0xCF3BBFC172309F01ULL, 0x2FBBAABDDB154D25ULL, 0x1D2EABB6CA83A236ULL, 
            0xBFB7B74943F75962ULL, 0x274FED96D10FB5A2ULL, 0xECEEC7B5EA382E6EULL, 0xD57BBAC036066E98ULL, 
            0x84DC494065C08228ULL, 0x39F5D7C4BBB3EF32ULL, 0x10D75049E7E87C31ULL, 0xCD4CF64CFC810896ULL, 
            0x9C9F13B150F61AA2ULL, 0x06EF40DB0D6F1854ULL, 0xC9059A86689FDAEBULL, 0x6FA565E8807B358AULL, 
            0xA18DE39EA8767088ULL, 0xB9033133DDBDA849ULL, 0xDF0B0E2E768BCD73ULL, 0x9A47E924BBFFB6C0ULL, 
            0xC341C0B43A8F69FCULL, 0x6877E0D9FEA63EF2ULL, 0xD8736B0D90826172ULL, 0x0C040314C8269D0CULL
        }
    },
    {
        {
            0x00957FDAA32AE5B4ULL, 0xD709140931CD6496ULL, 0x020C8EA4C59599CFULL, 0x0A58927D6004B14DULL, 
            0x938659F1FF1B50C1ULL, 0xCDED46524CCDA16DULL, 0x543FB4965273208AULL, 0x2A5295919FA5EAF7ULL, 
            0x32937CB7BC7BB105ULL, 0x0630CB63B1FD6838ULL, 0xD4032DAE53B3BB0AULL, 0x5126553732870F3EULL, 
            0x5CF59498AA405275ULL, 0x98BC8D8D2AF4C990ULL, 0x2B5BD49BBCA52A19ULL, 0x9F8BC659AFA4772EULL, 
            0xF91A1423B72E8AC5ULL, 0xC84402D31388F25FULL, 0x2B096641249754F8ULL, 0x4820550C87B99873ULL, 
            0x6AAF66024D0016A2ULL, 0x6091E22B50895933ULL, 0xD8851F21373D5AABULL, 0x1F415B079308AE31ULL, 
            0xAD58443703D8A4BAULL, 0xC9AF801F11139960ULL, 0xDFD4E3E1F2FCEDC0ULL, 0xFEDACF3CA218AB21ULL, 
            0x2156D59DBBEFCE3DULL, 0x9C1E25E168DA7C3AULL, 0xAEEEE1F2796C0603ULL, 0x44E37BFF6443F314ULL
        },
        {
            0xEB20CB0D6216D24CULL, 0xB7F0C0049E4A93CCULL, 0x88A39B92F08E47B0ULL, 0x9DEFD6001BC94C7FULL, 
            0x5FF3001495F63F38ULL, 0x03819FFC24137585ULL, 0x98A0B4847832C3A1ULL, 0x2D6724811D8E51A9ULL, 
            0x2A0F693FFCEE8FF8ULL, 0x7A868C2F6C3A57DBULL, 0xBDCCF3568BDBE0C6ULL, 0x9D026629DC49BA8BULL, 
            0x0F5B7E3FDD851D0DULL, 0x061D86F1F6467922ULL, 0xC5A5E1CA9F2714E3ULL, 0x6DC3867ACA2F538AULL, 
            0xCEBA8C5AC19EC539ULL, 0x60591FCAC2C57917ULL, 0x87A7763279D07689ULL, 0x56233BD3F625FB19ULL, 
            0x9A8D3EDE47DBDFE6ULL, 0x6B71CFABD4E3A720ULL, 0x6A8B33F74404216BULL, 0x5F6B6061261BD006ULL, 
            0x7D9E4D94580F5155ULL, 0xC790C85BC000A595ULL, 0xE8D2C433A1926259ULL, 0x87230B49597BE545ULL, 
            0x171FAAF718F0632AULL, 0x9DF80522E1F271D4ULL, 0x27105A6129433C75ULL, 0x2411DA719EB6F351ULL
        },
        {
            0xAB51B33933E70E84ULL, 0x944B6EE94200BCBEULL, 0xB698EB67AA3AF32DULL, 0xF218887AB44DA4B4ULL, 
            0xEFC904DC9F953A88ULL, 0xDC2D1C6A0A23DCB1ULL, 0xB7BE9C621440779BULL, 0x4F24A501623B0772ULL, 
            0xB64CB71560744FBEULL, 0x3E556F064FC210B3ULL, 0x6D0D6DE826803F17ULL, 0x9E8BBB380ACE1CA0ULL, 
            0xB5052A93E057E372ULL, 0xE9CD748509CFBCBFULL, 0x80A69F2DEE10CCDFULL, 0xB90EBB980F8F5026ULL, 
            0xCA4432ECEB921505ULL, 0xD25D98DC1881B309ULL, 0x224E5DCBC9623496ULL, 0x31658EF0B372F951ULL, 
            0xE9E9EB47C5F91BC5ULL, 0x406D033EF62A2136ULL, 0x3CF6DEA4682F12C8ULL, 0xCC5EB860F3CA894DULL, 
            0xEEB1CBCA7F4EDB7CULL, 0x57E5CE18213080EAULL, 0x0796BEC8D505E167ULL, 0x9B5EF4FE7CD07260ULL, 
            0x1B16A1D10BEE013CULL, 0x3F520BEA8F5E96F2ULL, 0x912E5919A211B25FULL, 0xFC469DA7974FCFA7ULL
        },
        {
            0x798E6F14BFE51928ULL, 0x19D06EBA86FB581CULL, 0x54FDF2EB349CD7F6ULL, 0xA6AA64ACBEA39E53ULL, 
            0xA3BB2735D51F4185ULL, 0x0C092B799AACBD63ULL, 0x5F33FDF732988199ULL, 0x81D2E7DAC7D0296DULL, 
            0xA3D9BA89445BB411ULL, 0xF314771767EF39F1ULL, 0x7FA2158A96310157ULL, 0x1E21B572D5AD3FF6ULL, 
            0x9C835C9CC109F05FULL, 0x40F53BC3917EC116ULL, 0xF74FCFAAC7847F49ULL, 0x8F8071D5C614F631ULL, 
            0x598C61F3D93ADF9BULL, 0xE2D40D1D06D0FA8EULL, 0xB4CF36F48ADC86A4ULL, 0x7385DEF9CBA2465AULL, 
            0x46802D3035078E1BULL, 0xE643E7C4AF61F602ULL, 0x9228F1F3CD24116AULL, 0x4D92E22F5A0B7E95ULL, 
            0x07C60DB2BFE5A3E5ULL, 0x170EDF75DBA29973ULL, 0x3765F3D33B3DF4A7ULL, 0x4E812FE0F648C779ULL, 
            0x42DE84675E7F79FCULL, 0x62B06C08862CBFB1ULL, 0xBCEF968A188C0306ULL, 0x44C2420FB3D0DC02ULL
        },
        {
            0xF9EB6DB026DB136FULL, 0xB2D5D1C30E424F00ULL, 0x57D2867CCBB97995ULL, 0xF29F65C2CEF0FCE3ULL, 
            0xEB3952D41047A87EULL, 0x05B31259E550A672ULL, 0x3BC085D7E00EF307ULL, 0x17B32811AF78A678ULL, 
            0xA0FFE2B631078AB3ULL, 0x9ED633ECBAB9176BULL, 0xDDEFC12EF9BA41D0ULL, 0x3C3632D7A35EBEEDULL, 
            0x733BD5DDFE3F65BCULL, 0x8C7B69D1E164194CULL, 0xFC9E658BA5B0827BULL, 0x72AEABF75B5BD1AFULL, 
            0x3BA0153701CE3874ULL, 0x1D6A8C0CE9E64B8FULL, 0xE5385106F7997CC6ULL, 0x401AC47D74880993ULL, 
            0xD438BC34C177CE67ULL, 0x5F1541F312FF942EULL, 0x564B9EC206C809DCULL, 0x1862B646CC09FE33ULL, 
            0x1D820F41DB5E2B09ULL, 0x6A3EF15DA260E9F6ULL, 0x70C142D421B9165AULL, 0xED076EEDA132857FULL, 
            0x62971D2273CD23BEULL, 0xE250DE7B371D2BD0ULL, 0x14A63885301693CEULL, 0xA8D40EF258A7B375ULL
        },
        {
            0x9213588246584B28ULL, 0xD675F11A3ADFDB3FULL, 0xC8C81831DC6CED85ULL, 0xDCA96B8A1F4C44E3ULL, 
            0xA06D632323ED4D1CULL, 0x980C50E3AEE3CF26ULL, 0xB86FB3DCD979E6BFULL, 0xB232220B0DEC354CULL, 
            0x9CCE2D83CF7FC800ULL, 0xE91AA7EA79B5D2A8ULL, 0xF5FB8693726B8952ULL, 0x905EC5DA389979C7ULL, 
            0x30667FFFB21E43F6ULL, 0x9F7A394FA3337B51ULL, 0x5DB8E1B4EE63C1A1ULL, 0xDC5D827ECCCDC464ULL, 
            0xB1B909024CAF6A30ULL, 0x91D8DDCF5489792FULL, 0x683780DE516F7173ULL, 0x48A097B1A60FC5A6ULL, 
            0xA033698D39FF7258ULL, 0x583A86F944C7702BULL, 0xEDF3337B10ACB9ADULL, 0x5475F73B3B856DCBULL, 
            0xA28808AF48E49C08ULL, 0xF521C54FF3FC5E9FULL, 0x1A566D804A3BAF5AULL, 0x66B9E410460E6678ULL, 
            0x28EA02915DAED185ULL, 0xA2621810F7C53B02ULL, 0x06B3232ACD1A366EULL, 0x2DE6BFE442C1DF23ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseCConstants = {
    0x042BE2492B0039CEULL,
    0xE898F0C1523D4BAAULL,
    0x5EC92412B97B7B1CULL,
    0x042BE2492B0039CEULL,
    0xE898F0C1523D4BAAULL,
    0x5EC92412B97B7B1CULL,
    0x5F28BB756BB4824FULL,
    0x72CCAD61EAE76D16ULL,
    0x1A,
    0x9D,
    0x1B,
    0x64,
    0x14,
    0xC3,
    0xA7,
    0xAC
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseDSalts = {
    {
        {
            0x5D5E0E70C862F789ULL, 0xAF255139086F8B34ULL, 0x20277E22CF297237ULL, 0xF79A33052B592509ULL, 
            0xA938D36C2203DA67ULL, 0xE32F2B527BCAB09CULL, 0x7F3ADD6C5453275CULL, 0x6CDDB41DD7E82777ULL, 
            0x346A83481A0EC396ULL, 0x8897882085B46DEEULL, 0xAA1D05C0DC7223DDULL, 0x9CE2ECB3B6D0F4F2ULL, 
            0x9E67DFA41BDECCD9ULL, 0x327F2759DBE8E847ULL, 0xF2AF0E84A2338F48ULL, 0xF215C99FFC1D62C4ULL, 
            0x9C7B74248649DF82ULL, 0xF0366E510CE26AEBULL, 0x4D012C13E8FB99A9ULL, 0x3F4D7E23A5460F7DULL, 
            0x039961DFF259DDAFULL, 0x3634DFD45149F8EEULL, 0x7ABC1563B9D23EF2ULL, 0x3B964EB5C7BB5EE9ULL, 
            0x611355459B1F0E9EULL, 0x9B0B3E818625903BULL, 0xA8144A893D731D69ULL, 0x1A64D5F5D02216D2ULL, 
            0x6DB9494B50A83F13ULL, 0x6695499532D4D755ULL, 0x2BA057E80318777DULL, 0x016EE0995FD120DFULL
        },
        {
            0x4234A76C7424BDC0ULL, 0xA8C042C5019EA946ULL, 0x8D5F617A5E7590FAULL, 0x99202E8A0817450FULL, 
            0xE0D052AF59B2224EULL, 0xEF7D741E80CD33D5ULL, 0xC04F9AFD5A659385ULL, 0x38032C40A4DAFB4BULL, 
            0x19DFE8E59B2ADCD0ULL, 0x06D15833890D2368ULL, 0x22892A58A725C9C0ULL, 0x8C437EDA2D85CC12ULL, 
            0x27311ADD25345AEDULL, 0x7E0B9CD1F71E9AE4ULL, 0xFE537AF43C80D4B9ULL, 0x98B7B91555E16CE5ULL, 
            0x5A6CC73AD870D2EBULL, 0x8381A60286B1DC3FULL, 0x74F4A6D5E1378312ULL, 0xCACA7B42884C7560ULL, 
            0x97704E43F96E2300ULL, 0xF872CB3CD70222CAULL, 0xF1B01339B7FB8BECULL, 0x5664D1DCFE498188ULL, 
            0x07E208840797744BULL, 0x25AE0F19196858EAULL, 0xFD5CB3908AAA54D8ULL, 0x38D425B10498EBAEULL, 
            0x625F58E363A319BEULL, 0x010EDF5E3D9E0B63ULL, 0xA9DF58FB6B4DAB89ULL, 0xE52AA4257D01A1C8ULL
        },
        {
            0xA06EDFA930568E93ULL, 0xF923939CE0DD67EFULL, 0xA0CC073FA368A8CDULL, 0x9E425347658EAA98ULL, 
            0x8A9F9C72963E82CAULL, 0x562FC776A06D8363ULL, 0x6B181FCCB44192B3ULL, 0x91E98A0559293F0BULL, 
            0x50EAB3AA005F4133ULL, 0x4B218D26C3B87201ULL, 0x9444E66D032A8B6DULL, 0x9F191AFA516F6167ULL, 
            0xFC7ABE841C4EEEBEULL, 0x100F19EFEE1F6D0CULL, 0xB4C8A457FF82ADFBULL, 0x185BAED73B5C32D5ULL, 
            0x84783369E74E7AAAULL, 0x8D2A199D5547B7DCULL, 0x824D19835E9E4329ULL, 0xEE0752D4B980375DULL, 
            0x6657F13A52CDDB72ULL, 0x9938D3D9C50E22E8ULL, 0xE63945A33237399EULL, 0x5396237E8C04CBD8ULL, 
            0xB91B09AC547F7A9CULL, 0xA15E79240778DCCFULL, 0xCCA7AFE27D157BAEULL, 0xE61EECB05E6C74F2ULL, 
            0x7FCCDE43236695B0ULL, 0xC02828529FB655FFULL, 0xA8D3EF1AC5D8A521ULL, 0x8EB9ABDCCCE5B212ULL
        },
        {
            0x15ED41DB3458776AULL, 0xCEB21BD941E7929EULL, 0x26929625460986F7ULL, 0x74AEF2F070E45DD3ULL, 
            0x022E39D284B92D09ULL, 0xFDBB911AFB8DA2C6ULL, 0xB34E90E218EF7678ULL, 0x5D8A1C389E53746CULL, 
            0x4377632DE4AE0B79ULL, 0x4CEFD8B2D817A225ULL, 0x470AD817D88EEA15ULL, 0x0D5CE01879FF0DE9ULL, 
            0xB09CA79E336FB891ULL, 0x2036201BD1C5CF19ULL, 0x8A03279206218002ULL, 0x3C97D6B6C6E934E7ULL, 
            0x473FFDD8A237D664ULL, 0xF5E60193C0DE0568ULL, 0x7790D18591EF4B1EULL, 0x07B4FFD76843F306ULL, 
            0x53067A9705936951ULL, 0x2779335D2E6A254AULL, 0x76FAC43A0DF8E23CULL, 0x952861ACE93D8E4BULL, 
            0x8C278CA2D302ED9AULL, 0x0902A8188E2D6AF1ULL, 0x38342FB19B24A0E9ULL, 0x5C0CFE18F285B35EULL, 
            0xDD709544B41B62D5ULL, 0x939EABB0BE1996D4ULL, 0xDC5AFF870969F376ULL, 0x67202EDDC3336E57ULL
        },
        {
            0xF0477460464BE71AULL, 0x4037A9EA3EB429FBULL, 0xD8A1E2CB2568B6F1ULL, 0x3255703A7B04AD03ULL, 
            0xD4E5C6AE25B35DAAULL, 0x2CFCCCB982DF3FEDULL, 0xDD64C170589360F7ULL, 0xCE78C7CAD4AA3695ULL, 
            0xD033E1A555F078A3ULL, 0xD72122D9C71324AFULL, 0x6C05EB6DFE98DCB1ULL, 0xB4B3B33ED3998D53ULL, 
            0x58521B424886D1F7ULL, 0xDEF53D83269C1AD7ULL, 0x4EAEC406279FE81CULL, 0x3A1491633E3AF574ULL, 
            0xECFC1EBA92DC4678ULL, 0xC3CFB51FBC08A46AULL, 0xFF8E4C0730153ED7ULL, 0x60BE8F67D195C1F5ULL, 
            0x1EF0D9CA9A52F7EDULL, 0x99D7707F1ED0E62BULL, 0xFCEBA291B36AF670ULL, 0x0FEC77121FAD7451ULL, 
            0x4A2DE39749CC502EULL, 0x9687CBBD522187B1ULL, 0x4FB619C44D21F59AULL, 0x381D20CC9F8E9E8FULL, 
            0x2F6CA0612B86841EULL, 0x010ACD923C0069A0ULL, 0x8524FC0B7C9E346FULL, 0x16AFF6425BDC7E7AULL
        },
        {
            0x58997BF517D3296BULL, 0x25F3F47267501479ULL, 0x1F71FFE6CE96B34FULL, 0x21D8254EF7133413ULL, 
            0xA34ECB014D5E07FEULL, 0x51C3E5FA3BFDE101ULL, 0xBF096AE5C66E6B95ULL, 0xA327DDF587F4E960ULL, 
            0x0A8632C4771B4619ULL, 0x382707FB2FC27C92ULL, 0x9A85502F1AB685CBULL, 0xAFA9664E4C082D5BULL, 
            0xCA2E17AC51707F0DULL, 0x4D0BE66E985272F7ULL, 0xBEE5261F0E31C27AULL, 0x42044BB3A220E48DULL, 
            0xB4B5A587EDF452E8ULL, 0x3C819C7471065AEAULL, 0x6107DC3845A86C80ULL, 0x2304EF8277E26D9BULL, 
            0x95FD6B2A7DB7B49CULL, 0xEA61CEC49DFD148AULL, 0xAB2C7B74257A4FE7ULL, 0x336B33BE37423A23ULL, 
            0x9DD0E0231C6777AAULL, 0x09A29D1A45256D7CULL, 0x3855B2C427825831ULL, 0x359EA7FFCB986ED5ULL, 
            0xF4701AB5697F221AULL, 0x822057A4706C05A3ULL, 0x7B65B667344396C3ULL, 0x14A623B8DEB3E591ULL
        }
    },
    {
        {
            0x4FF4C1A2CF94EF3CULL, 0x02541355AE3A8CA9ULL, 0x21D1CE35F5B8A343ULL, 0xA9251C86E91A0B94ULL, 
            0x510CADAC4D0DB0B0ULL, 0xF33B3F2E323CCD42ULL, 0x06DC676E6F97EA9BULL, 0x0214E62ECA87F16BULL, 
            0x28C1FD1116898C0CULL, 0xC59754E19FB2DE84ULL, 0x206CEFC558C89186ULL, 0xB0F8DAE285BBB557ULL, 
            0xB0035B150DBD64A3ULL, 0x8A34F5527260A36FULL, 0x1501B8827C0D4496ULL, 0x9C824E3280C1932DULL, 
            0x3DD630D8D888387FULL, 0xE0831DCD221F9CFFULL, 0x9C6554971EC496FAULL, 0x72E8BFAE3CD84506ULL, 
            0x60EEE31B16A56A9CULL, 0x34D9D19D52D08047ULL, 0x891E42EF8F41EA2CULL, 0x6385CA9149A137CCULL, 
            0x1D0F3EA4557B55B5ULL, 0xA231E970FF8A0F4EULL, 0x5204B4DD0717D3D9ULL, 0x07C4E3ADDFA6AB07ULL, 
            0x8EB7EB74081EFC23ULL, 0x1326FBC6264F2E01ULL, 0x668719F46CB3E57AULL, 0x94C94A4FB8D94224ULL
        },
        {
            0x5E2E4B078A087F2AULL, 0xC18E6CC5B56ABA65ULL, 0x0159DB04B3BD7ECDULL, 0x4937AE02A5B4AAACULL, 
            0xA72F4F81F8EFE6F7ULL, 0x938FA29C11DCC624ULL, 0xAF7181C20E4CB0FFULL, 0xACA45AAE741B1094ULL, 
            0x6F3BD9FEF7249706ULL, 0x1290B0CDFF641ECBULL, 0xB3DDEE42EF2D6C72ULL, 0xEC4CC96D49BA9C4EULL, 
            0xF14D4544A36F8BD0ULL, 0xD5086C4C9C7B821DULL, 0x4882E9D80D056E73ULL, 0x65A5D330DDA32D6BULL, 
            0xC31FF4A96DFAEC6FULL, 0xC9A68120D185BDADULL, 0x080B6A3324929CE4ULL, 0x5B498723C4E048ABULL, 
            0xD7AE96DFC5CCBFE5ULL, 0xD98A2DFFF9DE59F8ULL, 0x4AD382552B3C8B07ULL, 0x77D2421A3BF30487ULL, 
            0xCF7BEFEA1639F72DULL, 0x3D29A7120DE475F3ULL, 0x76DE7E37E8410798ULL, 0xF28816F07DAF6F2CULL, 
            0xCD655D261030C3F6ULL, 0xD4B158E02BD588F9ULL, 0x7BB49E17E69D5703ULL, 0x1910713F227D1697ULL
        },
        {
            0x3C4E11F52B137F14ULL, 0x5D5C7C86BBAECF8FULL, 0x6A24A61F6EBE908DULL, 0x36D076FAAA0ECC89ULL, 
            0x170427E96990E8EDULL, 0xE5F79AD87DEDDCA2ULL, 0x2402D61A6EBED2F0ULL, 0x2A97878B4B470536ULL, 
            0x21AF6E6E79FC5842ULL, 0xD7956E17404F847AULL, 0x1FF00325BBBE980AULL, 0x9C754DF9BFB2FCA0ULL, 
            0x11B19706D1538655ULL, 0x17F94547E82FEED4ULL, 0xAD9EEBFE0C00B111ULL, 0xD39467EA7C35EE2BULL, 
            0xA5D626E4A21320F0ULL, 0x7B569428DE3121BDULL, 0x063669025C12ECCFULL, 0xD7CA51D2C61E08B5ULL, 
            0xFE6269DB885FFCFBULL, 0x4B36F2DAE24B656FULL, 0xE55CB4F9EE0AA806ULL, 0xBC24784A7D38755BULL, 
            0x15934416F0FEE155ULL, 0x6A1B1A87F359BB7DULL, 0x6D8A7CC80F1F90C7ULL, 0xEA0DA52C3354BFAFULL, 
            0xD5E61DA1B879C912ULL, 0x82642A54A6AFF4F6ULL, 0x14492256F4F7BFE2ULL, 0xF1B202E7265F23EDULL
        },
        {
            0x346D635936D95F90ULL, 0x7644E6AC25CD675CULL, 0x43760840CEB0FEA3ULL, 0x440A91604EB5A684ULL, 
            0xEA1C38A326982048ULL, 0x27F957423A14090CULL, 0x911AEE8BCA767BF4ULL, 0xA2B07146CD61E753ULL, 
            0x29F4FF81018C5DEFULL, 0xDD2864D3ED1552C0ULL, 0xFB79EF1AF7B4948BULL, 0xFB983B5EDBD17F0BULL, 
            0xA4D4E7DC26035314ULL, 0x2E3C7860B5990D2AULL, 0xBD61F0FCAD990A6CULL, 0xE48BDFFECDB1D17AULL, 
            0xB8795898B0FDFBC9ULL, 0xF38F24A44391F3AFULL, 0xEF9A095DEB30C5CBULL, 0xC0433476B8BDB3EBULL, 
            0xF16E6A24C22E7524ULL, 0x073AAC813356F349ULL, 0x88B916313AB0CEE4ULL, 0xF4013984C0355055ULL, 
            0x445929C0D52290B5ULL, 0x040FA48266C0E913ULL, 0x31298FFAC5F00872ULL, 0xC872C646A48EBB04ULL, 
            0x26438765F6251988ULL, 0x1CD8F28484EDEA00ULL, 0x26CDC58012FE0628ULL, 0x8525279920303D6CULL
        },
        {
            0xD0120B370739F901ULL, 0x127B2A8BD1E5A6D8ULL, 0x7D533479DE13C045ULL, 0x3CB5DE5725DB81F6ULL, 
            0x184CAC24A8E58C51ULL, 0x312CF73AA605E2C8ULL, 0x046B3A1EB46F0A7DULL, 0x9AB6F888B1184FFDULL, 
            0x2A3B89D5410BAC46ULL, 0x149DDDC633A37853ULL, 0x59BE7DA5ADE83A77ULL, 0x76E1DF5990630ACBULL, 
            0xEFAA296B8D6FB4C7ULL, 0x4341EBB0F4710F2DULL, 0x8252DFF218FA79C3ULL, 0x58B6D83F05470B2CULL, 
            0x729E504A18969C76ULL, 0xC1A836FCF2A376E4ULL, 0x15A6368BD9F9E2F1ULL, 0x7106C374B9D34F32ULL, 
            0x86E98861E08A0903ULL, 0x9A8AF3CD5D335D74ULL, 0xCE218BC98FA92CA9ULL, 0xD99450A367C32223ULL, 
            0x4D9608029EAE1363ULL, 0x9FA4DCE1ACD5EDFBULL, 0xC78115E2C938AB7EULL, 0xB8EAE9FA47944382ULL, 
            0x1E6F54F8E094037CULL, 0x57E8FAEFF10694EEULL, 0xC208AB548FE8B4F5ULL, 0x7BAF59EAB20151ADULL
        },
        {
            0x6C33DF818E57D53AULL, 0x852551AD82E8D0F9ULL, 0x9569DDBAA397D3C3ULL, 0x4ED60035FAE83617ULL, 
            0x974EA8AF6FB5D64BULL, 0x60061B865DCF1BA6ULL, 0xFA1A60BEA95E42DBULL, 0xFA386A8AD51C3C56ULL, 
            0xF573B5C8AC325104ULL, 0x2828DD7C54DEC774ULL, 0x63436B5FF394D377ULL, 0xF286A2126645F953ULL, 
            0x539895F2D6C6D326ULL, 0xDF71E0956B9C94CDULL, 0xEF91E3FB1B762B11ULL, 0x93FA97EC7E39B8F8ULL, 
            0x89FE6695AEE38029ULL, 0xC5CDAAD752FDAB14ULL, 0x70DB9B1A98D14734ULL, 0xC731A896A5B5C0D8ULL, 
            0x1AC2D46C992E1E79ULL, 0xEBA192B8C788F346ULL, 0x6801DE2450F2E92CULL, 0xE3BD702BFB02B946ULL, 
            0x02F05DFB336C2AB8ULL, 0x4E812DD4AF0B6297ULL, 0xF368112C3AA4B5CFULL, 0xDBA6721925C0AEB6ULL, 
            0x1984AF3BCF744F7EULL, 0x49DD53813F791E63ULL, 0xE2D169C000FB3160ULL, 0x08E1FB0F56B6F1AEULL
        }
    },
    {
        {
            0x95CC5C52884D70ACULL, 0xC370D9DF75AE8C6EULL, 0x4EC68202F7445700ULL, 0xBC5CAB7C16027EF6ULL, 
            0x7BAF72E1CDC1031BULL, 0x12EED32D59B11E27ULL, 0x16E171657AAC75C8ULL, 0x4A3FA8369F248694ULL, 
            0xD65282D0780EF897ULL, 0x2DF7AE9DAE0A987BULL, 0xF2FC3DB4AF03C81BULL, 0x4C4B1733C65E3A73ULL, 
            0x2FCB49D71576EE6BULL, 0xEAF911B3E96F5A6CULL, 0x9201300520716592ULL, 0xD649661C0813250AULL, 
            0x1CFAF112B5B56D74ULL, 0x2FDCC9A49C462B85ULL, 0x376DE5A87AA4C8C5ULL, 0xE64206F9FC2867D6ULL, 
            0x914AA0295CA52757ULL, 0xEC9C817D6FA55E4DULL, 0xAD4A515E49D3EC13ULL, 0xDB7DE9900C214E9CULL, 
            0x71A30C4FC44AB238ULL, 0x064CA50E4F69E30EULL, 0xC61F615AD7D8B182ULL, 0x618B02DB022491EAULL, 
            0x307BA11150F5A6FEULL, 0xF93464BEB6C87B8DULL, 0xE7CAE898BE5A72C9ULL, 0xD5D13A3618E84026ULL
        },
        {
            0xAB2257FB1F0C4EFDULL, 0xBEDA62E70BB52D4BULL, 0xFEDAAF5BF6674A5EULL, 0xBBF521D84BB58E96ULL, 
            0x1BDBCF2AFFC0BB2DULL, 0x899652754B148F36ULL, 0xCE703CD065F7B0BAULL, 0x403DC7AF8750483FULL, 
            0xF5F8E498E3E193DBULL, 0x65153D686AA71E08ULL, 0x5446BCAE9DEBCA02ULL, 0x8DE1B924FC3F3B1AULL, 
            0xEF5F8AA0E8ED7CE4ULL, 0x2F64E0E5C8403B0EULL, 0x3BE72512B70057DFULL, 0x55F70F5BA7FF0BF3ULL, 
            0x5DEA6DF57B274932ULL, 0xE5C75605511D1D95ULL, 0xA505FA5CFAF58F09ULL, 0x1A7F792D853E1ED4ULL, 
            0x568F693DD960F96BULL, 0x22E3C156E3AF079DULL, 0x08D1061812A82A78ULL, 0xE28AB647A241F469ULL, 
            0x748BCB7944DEEDE9ULL, 0x37059566CFD4E0E6ULL, 0xC1E7C673BAC98964ULL, 0xA31D46F2990124E0ULL, 
            0xA9251D289C977A4BULL, 0x74E146FF6F4B2AC9ULL, 0x8E8786B9036F5500ULL, 0xBC6E26BD501CD0C1ULL
        },
        {
            0x0BB11E7670A4A518ULL, 0x0C5E8B52EE9860A9ULL, 0xF67C908CC245B77AULL, 0x79E18FD268D1AB8BULL, 
            0xFE60F282F1EC79A8ULL, 0xEAAD58DCED0099E3ULL, 0x3663F033E6E2F7FDULL, 0xC366B81401F46A38ULL, 
            0xF90A5891450C838CULL, 0x4AC4A9AFD4246C95ULL, 0x3C10141144CAD118ULL, 0xA83F961826BAA032ULL, 
            0xA946E09D5F97E41AULL, 0xAA61C7B3FA4B77A1ULL, 0x7397E6EB19E15078ULL, 0x8E9926EB1BFD6ED4ULL, 
            0x2E439965C659AC88ULL, 0x1B7E368E4A56A104ULL, 0x8C824EDB80A8FE4EULL, 0x6269F5F9977E375FULL, 
            0x990940716347BC20ULL, 0xCF98151F124C3391ULL, 0x2C023B9E3E1E220EULL, 0x8F0647318B797F11ULL, 
            0x503C19559D490615ULL, 0x4B3B7D6BB6D690BBULL, 0xC330B46F4A67D147ULL, 0x26A3A324A19BB1E9ULL, 
            0x9FD97FBC5AC8EB51ULL, 0x5291EDDE1818D30AULL, 0x729C51CC2978BE1BULL, 0x85969E46D64E7BABULL
        },
        {
            0xC50ACFC2AA63BE59ULL, 0x82775EC524FE4827ULL, 0x64810B6338E5724CULL, 0x5360F61594B84E92ULL, 
            0x552C9044A5296D78ULL, 0x56B75BE864E2AD21ULL, 0x2B468AA71DDB8919ULL, 0x91DD3CDF5CD4DEEEULL, 
            0x3964212C34816E12ULL, 0xEC2CDD34D4F0A310ULL, 0x3384A05061BAF747ULL, 0x76EDDBD63B290755ULL, 
            0xA59B6D1F4BA9A9DBULL, 0xD5F1A63991DFB6A3ULL, 0xA854406F8426816CULL, 0x60809F2C9944B744ULL, 
            0x324818039C3FF3FCULL, 0x3CAD64D3717DC105ULL, 0xE7198E856CDA34D2ULL, 0xB433D32AFF8A626DULL, 
            0x57F4D566B8CDE39AULL, 0x1EE58FB82A221198ULL, 0xB8C1D5D36D3A33E1ULL, 0x1DD8E8E227D64EC6ULL, 
            0x547EEA1634CF6F98ULL, 0xB77B1DB62192C2F7ULL, 0xDA82768B38C7FB61ULL, 0x5C2CBBC8D03FBAFEULL, 
            0x38B58553CE44E386ULL, 0x189714DF3124CAB5ULL, 0x8A7DB99A8DA8EE6DULL, 0x5EEBB32FEF8F9274ULL
        },
        {
            0x84C1494F8DF7F9E4ULL, 0xEAE736A4D7AAFFE7ULL, 0x4D0C1F47F3231265ULL, 0xC01CFA6E2B321BD1ULL, 
            0xBE43F15326773B4AULL, 0xBF188B3712D6EB04ULL, 0x6062E49EB6D3679FULL, 0x612333E46B0FB1F9ULL, 
            0x39334F3DC29393D5ULL, 0xB749F4E80EF73B4DULL, 0xBA73C83AEC4BF926ULL, 0x025FDD57A001C9FBULL, 
            0x424985AB317A16BEULL, 0x154951359F91F32EULL, 0x5323E6746401BEA9ULL, 0xB19CB76A71E0BE96ULL, 
            0xA16E5C1B801F47E3ULL, 0x01624776C6DEE3FCULL, 0xA7DC219A544B0A59ULL, 0x6A39244286174FA3ULL, 
            0xBB5B3202DE199830ULL, 0x2C9B06A39B19C15CULL, 0x152E537BA5E3360BULL, 0x39371E08857CB44EULL, 
            0x39466BCFD101DAE8ULL, 0x0747EA410E6C8642ULL, 0xE783EB0E655A9B5CULL, 0x7366D338031A5703ULL, 
            0x2E3305D55B02E6D2ULL, 0x9DFAA251E9AD652EULL, 0x414D34A48654945CULL, 0x8FE4C3C1DBEA3C5BULL
        },
        {
            0x2862FBB095F5DFCCULL, 0xDDEB01CB813BDF78ULL, 0xCBCD8191A569AAE8ULL, 0xA20666848B1891DAULL, 
            0xAE7361434DE88C6CULL, 0x9E1F26DA9417E4D8ULL, 0x1C9BBC1BE7E0399EULL, 0xD587273172476606ULL, 
            0xA69402261245C0B2ULL, 0x3B495B79C5CE9D7CULL, 0x9A3C898185A0BCDAULL, 0x307F6165A74A7490ULL, 
            0xD4B36B9B0FDB3248ULL, 0xEB2558BF21FE0635ULL, 0x8CBA0A8D307AF18CULL, 0xF64699FFA4E4C303ULL, 
            0x8F48BEE0B90A7140ULL, 0x237DAA5D35E70E78ULL, 0xAC186992F7B626BBULL, 0x359D41EFDF5EBE36ULL, 
            0x41E3A059DBFCE341ULL, 0x4DA980F67FAD759BULL, 0x56BF24D00498A9DEULL, 0xF561A874BBD66C3CULL, 
            0x17B60FBADC7FE251ULL, 0x3A31D6832039768AULL, 0x0A19AC8673D4A8C3ULL, 0xCB6561F04F13552EULL, 
            0x85D4A45A5460E27BULL, 0xF8D7DD7286A73205ULL, 0x5BA1D4F302094A70ULL, 0x0858F140A8253F52ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseDConstants = {
    0x2E84C3C6F73C90FDULL,
    0xFB4973948861CBFAULL,
    0x822BA2F0DAB10375ULL,
    0x2E84C3C6F73C90FDULL,
    0xFB4973948861CBFAULL,
    0x822BA2F0DAB10375ULL,
    0x7B333C69508807AEULL,
    0x511649EC3181686FULL,
    0x67,
    0xFA,
    0xC7,
    0xD1,
    0x9A,
    0x46,
    0x21,
    0xFB
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseESalts = {
    {
        {
            0x4AACCE52EE7893F6ULL, 0x707B8F72685DED4DULL, 0x26AB5D4BAF599FB6ULL, 0xEE7E784A24B7B860ULL, 
            0xB05B501F356D25ADULL, 0xBAF33B6B473BE54BULL, 0x76D62B0BED28C4B0ULL, 0xF457F7A54E029BF7ULL, 
            0xA0C880C993ABE468ULL, 0x3307F01AE2E168B1ULL, 0xF4277EB338D59106ULL, 0xB5EA797509733509ULL, 
            0xB8A0D67BCBF03E45ULL, 0x5C42FA2B39FC1B8DULL, 0x24CFB9827C821C8EULL, 0x854AC5B08E1F6C65ULL, 
            0xF0859D3DFCBF2E3AULL, 0xC7A5E6D0D15A5079ULL, 0x3C30FC4E5FD56075ULL, 0x8DC275873027102DULL, 
            0x98993E335B247F3EULL, 0xBF76F97EE246701AULL, 0x800D1A5B8DA9B219ULL, 0xAE7DD999C7C3E3E1ULL, 
            0x2C21008416CA60A6ULL, 0x076AE1E13D68370DULL, 0x549BCB822FF8DFC4ULL, 0x2DB22EA2B37B6A06ULL, 
            0xC17B23D15659FA85ULL, 0x7046133E63780F8CULL, 0x5157B2EA4B8A2E3EULL, 0x39532237687D93D0ULL
        },
        {
            0xB8F59CC1F68ECFEDULL, 0xCF87EEA733FFECD9ULL, 0x6CBD1FC76C81842DULL, 0x717D5CFA6E1EBFE2ULL, 
            0xECDD177E87239792ULL, 0x96464B4976A6F690ULL, 0x34CE8765D79BFA8BULL, 0x9CCBD5260949CF0FULL, 
            0x68F9C64F0DE33D0FULL, 0x1530F19443481AEBULL, 0xC63A45EB13B05803ULL, 0x72CF8DC9D0B12B4AULL, 
            0x7EA1397451111CF5ULL, 0x623C6C8F25684BC8ULL, 0x212379B79F439F6DULL, 0x93E8294B96DCC3B6ULL, 
            0x638852CFFCB19AE7ULL, 0xF7678675E1D80CCEULL, 0x05605851E21E2BCAULL, 0x4AC85C1D9853BCB6ULL, 
            0x115647441088B594ULL, 0x1AFF3ECB4511776BULL, 0x2F9BEF4643476FFCULL, 0xD65BB1B2130D76EBULL, 
            0x87C55FC2D1E05D84ULL, 0xB035C7D1BBC2C4BCULL, 0xE7730262B0425AA9ULL, 0x01876728A84AB75CULL, 
            0xB49929BB1CE4888FULL, 0x2EA5DBE5A45A6DADULL, 0x8189525E2AB505CEULL, 0xE974B80F3B1D4F50ULL
        },
        {
            0x9BEB54EDD5513B11ULL, 0x9C22AFF14EBED6DAULL, 0xA986521C8010B8DDULL, 0x88D99D7E30258130ULL, 
            0x834B9371F978E10AULL, 0x352CAB7B6AFAAA2DULL, 0x2E56831D2A367A91ULL, 0x3F2FB79690305A96ULL, 
            0x491E626DD7CE3015ULL, 0xC6682A55763636F3ULL, 0xF43A808C6AB1163DULL, 0x241D33F5F8DC80EFULL, 
            0xFD8023DEAB3E83E4ULL, 0xDB63EE2AFE29A67BULL, 0x7356F956C1A6560AULL, 0x73860F228D40398BULL, 
            0xAB65E55567FE1650ULL, 0x67A0CA3FA956ED2BULL, 0x5110915125DC54E4ULL, 0x58E9A2B919B9389BULL, 
            0xE5929D2CC9103BE6ULL, 0xBF9477880E752BB0ULL, 0x33EC4C223A1FDFBBULL, 0xAC11677BE9556FC3ULL, 
            0xEA820502F466E3A3ULL, 0x6C0B71F84C660B46ULL, 0x962859996F8ED502ULL, 0xB58064D9C9142C03ULL, 
            0x3EE003345737E3EBULL, 0x48AB6E358F320E79ULL, 0x00255655C53264FEULL, 0xC22C20F0A0903F0EULL
        },
        {
            0xF46ED1D8B9E6992CULL, 0x8719014866C56849ULL, 0x78473BBF5C778C6FULL, 0xE0C2B4E5348F2704ULL, 
            0xDA21D148F0D848BDULL, 0xD54B6AB5619CBCFBULL, 0x66673508993019D2ULL, 0x35E32A45775ADD13ULL, 
            0xD62350F4E7F1CF78ULL, 0xCEBE62E96D4E10FAULL, 0xD6CA839E08F7B76EULL, 0xE17F41A712B0D96CULL, 
            0x6CF5321EA820C12FULL, 0x2DEB44D5FEA2314BULL, 0x5659FC178FDAFB49ULL, 0x956A1745C4FAE851ULL, 
            0x7ECE7974E5398024ULL, 0xBD0EE3492031F0E8ULL, 0x10E70F21E50547A5ULL, 0x6F82B1F11FAA4E2DULL, 
            0x33E92C6A41E3100DULL, 0xBA079F5E9D7BE64FULL, 0x804C63CA227C60D0ULL, 0x469C079E30CB5A89ULL, 
            0x0894DA4B850F636AULL, 0xD4FB993F865DEE99ULL, 0xDBAFB452EE3A5D0FULL, 0xD6A30DFD6A906E9CULL, 
            0x3B70E85BCB788FC1ULL, 0xE4FB26F007803946ULL, 0x88FB9206BAC3ADEAULL, 0x2F23F60A0AEE630EULL
        },
        {
            0xE96AFAD4CEC7CE72ULL, 0x970B17D8FAF042EBULL, 0xE26EF060B7D2BFEFULL, 0x73C157A8683211DBULL, 
            0xF329683FFD869E53ULL, 0x6212EC9A868E3EAEULL, 0xA62F091B50BDB25FULL, 0xDA2E37ECBF2FA12CULL, 
            0x00BB26DCAF33B8EBULL, 0xF9700DC5D8A4D0DCULL, 0x7D308B8F2EA5522AULL, 0xD3B52D8075565DFEULL, 
            0x6560D6EA9D4B614EULL, 0xCB8249D54205C20AULL, 0xA01B977EEE83BCF7ULL, 0x48681ACC08FFFAF6ULL, 
            0xF978F0D7F28D1E96ULL, 0x7BFE3C3E6BC3DC98ULL, 0x5A8FE68FBBCA9D31ULL, 0x9CC8498D6FC08593ULL, 
            0xD92D4766D239C763ULL, 0xA79B1526D1ECE909ULL, 0x1F9A511FE9AF5DCDULL, 0x3D7EE2B283BAA032ULL, 
            0xC3CEDAFE3C7FEA46ULL, 0x272CC634CACAE3A4ULL, 0x069504BCB47A01FCULL, 0x303EB8124CC44E91ULL, 
            0x617C90DD4FD1B7F5ULL, 0x0ACDC0FB3CD3EC26ULL, 0x9D86E1176B6BF779ULL, 0x8439D1832ECC99DAULL
        },
        {
            0xB4A1EA801D6220C6ULL, 0x62D3A1710892B989ULL, 0xB4AC76495A9775B0ULL, 0x500540987AF506DCULL, 
            0x2E8B4E586AEA3AA5ULL, 0x94685A6C57EC769EULL, 0xE0A224D135858301ULL, 0xA64CEDC1D1DA384EULL, 
            0x87D5D17268F70531ULL, 0xDEBFF96709AE2B5DULL, 0x860ECB5C37AF7A6DULL, 0xC12758AC284F18CEULL, 
            0xB3FC32ADBE3B1267ULL, 0x90BCF699FE5F5D3AULL, 0x71379415C25758C0ULL, 0x5F81F6CC3F32F70CULL, 
            0x36DA02F80EF7E1EDULL, 0x7C049C348AD265C9ULL, 0x8D214163B33BB224ULL, 0xEAE06114A15AE6FFULL, 
            0xE2318A0E7060E8DFULL, 0x61663485BC491FF7ULL, 0x7EE8EE5DE1DEFDA7ULL, 0xAD47EB928DE7E551ULL, 
            0x5B9FC2DFA899A856ULL, 0xB3F1F38D21CFAAC8ULL, 0x645FC7EBDA730BACULL, 0xFB4274DB503C1E1DULL, 
            0x472E6E1426434047ULL, 0x4E8CB676EDD90DE0ULL, 0x1BFB98348F0A4E8FULL, 0x1227526BF438EA54ULL
        }
    },
    {
        {
            0x4E06A3E19BC8D8F2ULL, 0xF0A0AA6D518D317FULL, 0x8A213B0627F2E6EEULL, 0x1B7ECDEEFBE554EFULL, 
            0xEF7CDB89AE47B52EULL, 0x26419AA96CF9FD64ULL, 0x6A4B8279881AD4F9ULL, 0xF3FC3004459A21CEULL, 
            0xD8C5E526CE5E7EF8ULL, 0xFE08FDACADC04BF4ULL, 0x3CE34EDF7C1584E9ULL, 0xDB63046099371F01ULL, 
            0xECEACD3A1123EBECULL, 0xFE8A4ACDE812CD2FULL, 0x2D2118C1D464CE04ULL, 0xAD56C11DB09D676FULL, 
            0x202C987A6E997341ULL, 0x61CF732D74E182F6ULL, 0x3573B39C3EB67ED0ULL, 0xCAA6FD0C440D571EULL, 
            0xC83199FC987F9E9CULL, 0xFBDD60048AB63AFBULL, 0x15FDDAF73DA63684ULL, 0x1A493FD0547AE595ULL, 
            0xA9BD930DCCA1DF4FULL, 0x23D062B7EF7E54B0ULL, 0x0372842B84655716ULL, 0xE860DE607F1D6345ULL, 
            0x849879D8F78A3D3DULL, 0x2A1FDC451D54ED9FULL, 0xBB484F4E0872BB0AULL, 0x69876567FA1AA563ULL
        },
        {
            0x82A9297284F9A577ULL, 0x7C7201BEB7F16357ULL, 0x37750A4AF3446CCDULL, 0xACC5EECD0B0FE216ULL, 
            0xA43B176ECE15C8DAULL, 0x32282ECED43DF981ULL, 0xFEDEFC3D5A628112ULL, 0x322817D42DA39E60ULL, 
            0xAFA441CA9514ED50ULL, 0x297277FEFEC566B1ULL, 0xC2E41B78FD2C6E96ULL, 0x96EA746F28A76ED5ULL, 
            0x4F2B3F879570C1FFULL, 0x00195B7B08CA6A36ULL, 0xE1AA4B040D13F696ULL, 0x0235F5F34E1FBF40ULL, 
            0x21F70EAC2317F8F5ULL, 0xCC9F123AAA1B83A0ULL, 0x7526D7B0073CB7B7ULL, 0x324E11DF24FB0A7CULL, 
            0xA27EDBCF4B20536FULL, 0x827B102877368959ULL, 0xD9361979EA5A68ECULL, 0x249F443D029F6282ULL, 
            0x48865DB200788B77ULL, 0x30ACBB8D3E02028DULL, 0x7560BD7DB60DAC55ULL, 0x5A9846A9FBA389B2ULL, 
            0xAE96040E062F2C4FULL, 0xFF8D8C18E19EF34EULL, 0x3568C7C23F918FE4ULL, 0x9A8EEF90CBB2DF10ULL
        },
        {
            0x8E189ED975CF64D5ULL, 0x8046B381A43FAB83ULL, 0x19E65A7C42F0CE1FULL, 0x2F3C973613DFE3A7ULL, 
            0x16A0839F84E86FD8ULL, 0xD1A07475A000DF4BULL, 0xA3ECE824C42E6917ULL, 0xBB91209548AB9E3FULL, 
            0x52398BAA9A687C88ULL, 0xD8A27C30413C65A0ULL, 0x68FDE284849B4F7BULL, 0xA49A385116D0BB87ULL, 
            0x6B1C924019905CE2ULL, 0x8017401955BFEBBAULL, 0x6622D82BE9B95A2FULL, 0xACDEEDC68821F7BBULL, 
            0x20AA9C45728F6B0CULL, 0x23B3FDCAD17AAE7BULL, 0x73A16C9C99D5A153ULL, 0xACE78BD76C540831ULL, 
            0x6BC632C08AD6C629ULL, 0x676988D7ADD20BD9ULL, 0x49984BE4A89A5989ULL, 0x565BC6915A0D53FDULL, 
            0xD9925D7AD6755982ULL, 0x438A943528008BA8ULL, 0xC2EADFF888B0E9AAULL, 0x48C09288CD9659A5ULL, 
            0x21DBD84C328370F0ULL, 0x583CB65619A9C130ULL, 0x8D9368DE81E9E14EULL, 0x504727F80C93ABFFULL
        },
        {
            0x6B1269633FDDF795ULL, 0xDF90C477E3223413ULL, 0xDBA657A48B703B06ULL, 0xF713254FC63FF0CAULL, 
            0xE704E92B0C996CC6ULL, 0xA40A02BBB65FC3A2ULL, 0x61651F1751B80D44ULL, 0x14B532ABD13191EDULL, 
            0xB08517F01588924DULL, 0xB9C69F58B1A925AFULL, 0x1F256FA61A1D81E4ULL, 0xA6A79E37339DC748ULL, 
            0x84D4B61F3F23BE12ULL, 0x8997E99A6FC5B1C6ULL, 0x8DE3F64CB5594F93ULL, 0x4B792D49085619D8ULL, 
            0x37AD61A25743DE96ULL, 0xAE35312666C2092EULL, 0x361518C2FB5A4724ULL, 0x7CCEC44A5A01E35FULL, 
            0x28FF74C8D9380A9FULL, 0x166B226C9D9A2B10ULL, 0x997B0968E75A42E6ULL, 0xFE0BC9EAF9A5018CULL, 
            0x93A66D740ED2AA4AULL, 0x0CEFE513393151D0ULL, 0x31112DCB8757B006ULL, 0xA9D7B1CF58D73292ULL, 
            0xB95A3A0793EAA71EULL, 0xFB47CFA54D689C59ULL, 0xB4CFC61AE2398901ULL, 0x3F54053C3CAD14DAULL
        },
        {
            0xA4346788824D1CA3ULL, 0xFDD1E03CF4CF25D6ULL, 0xDF591059C5082400ULL, 0xEE488CAC04580649ULL, 
            0xEDF2E988B27927A4ULL, 0x96090E30CC40491FULL, 0xFC6AE21B48BB6325ULL, 0x652910FC4DB50644ULL, 
            0x392C35E02AB3E2CBULL, 0x9942DA00907CB71FULL, 0xBBC0E38F2EE487DAULL, 0xA92267B7236DDFF6ULL, 
            0xEBC290E349F24E6DULL, 0x1F9BF546C6B0074BULL, 0x131F00F0FEFA1C1FULL, 0xE46B41EE823353B1ULL, 
            0x95F95EF7EAB77BDFULL, 0x63585D0DA9DD9BC9ULL, 0x9FE83EE99D4D7A2EULL, 0xA50EE39CC960D9BEULL, 
            0x1A4C5D2021FF6A53ULL, 0xD630E9BE97A26310ULL, 0xD66E8826E398E874ULL, 0x13FC3F169646123CULL, 
            0x72D19A8DDC6795E8ULL, 0x6E5DA8E9D5DE82E6ULL, 0x97782728B33425ACULL, 0x2BA880CFFC9B16A3ULL, 
            0xE2A43B86FBBDB78DULL, 0x73E211E7316346A4ULL, 0xE2724BBEDBF8B17EULL, 0x4884F0E073F02E45ULL
        },
        {
            0x2E64204146358C20ULL, 0x68FB7EE8D8312C1BULL, 0xD9EE375B00EB83DDULL, 0x9CB43522CA81CF90ULL, 
            0x48B40B5A48DDFA9AULL, 0x0628138BDD2B389DULL, 0x9C1AF56486B5B432ULL, 0x547F7D5095DEB1D0ULL, 
            0xBFA37E52CBE522A4ULL, 0xF16F349BF1C3170CULL, 0x51A49A48FEF66081ULL, 0x694EE3AA638CB91BULL, 
            0xC1A2C3187AA58643ULL, 0xCB65C9C3FE3AEB5FULL, 0x65AB1F012AE84E6BULL, 0xC91E18B22EF0C022ULL, 
            0xF97C2BB616F28CBAULL, 0x6F03562227D210C8ULL, 0xB8C3D18F3CF6CC6CULL, 0x04DA5C83275BB83CULL, 
            0xA23600A459BFDFCEULL, 0x2C00E55934AADFB5ULL, 0x425A1DD0D957ADE2ULL, 0x90664B709E880425ULL, 
            0x7FD969F354AB938DULL, 0xFD730FDA89572A6CULL, 0x71B67FF260221F25ULL, 0xC8196A34562AD090ULL, 
            0x9DD0FD8CE1D7697FULL, 0xDFD71F70E91EC930ULL, 0x7D040442E971BECBULL, 0x0D55E41238E69C14ULL
        }
    },
    {
        {
            0x72F09D154EC9292FULL, 0xA6B03A5131EA7CA3ULL, 0x31C9934C35492A1FULL, 0x10C69379D73381ABULL, 
            0x67E931327F19CE33ULL, 0x228B312F2A58574AULL, 0x5B1D29C4BAC9D36FULL, 0x6E98914264326556ULL, 
            0x3A1AA5819BB7F5AEULL, 0xF0151FFC10F0267DULL, 0xEB7591111E95A2A3ULL, 0x04CD825C7DA91266ULL, 
            0x5C0F4D47898E80BAULL, 0x8480F3569C257E9BULL, 0x50F9EE78781629A8ULL, 0x4541969B6CDE07CEULL, 
            0x23A369BE407ABDD5ULL, 0x8972579F8CD92459ULL, 0x7FED1E95452ABA89ULL, 0x1E207EE081018521ULL, 
            0xF7CBCB32FAA0E415ULL, 0xC6941731801F7975ULL, 0x254E007CD8B417BEULL, 0x431A0D82FDE234F5ULL, 
            0xFF6135F816192001ULL, 0xC9F9AB31B20A61CAULL, 0x879409AAA17F0FF4ULL, 0xCA838F5206E904AFULL, 
            0x26D93975FC022FACULL, 0x53FE0AFAB817F3F7ULL, 0xCF3431E1B56174B2ULL, 0x05A391DD35AE66B2ULL
        },
        {
            0xE085515F43DC2004ULL, 0x4C58900743317B17ULL, 0xDE3D9EA87440C773ULL, 0xB07D6FEF74275B16ULL, 
            0x8323B7776F07F637ULL, 0x45212E8CCFD24571ULL, 0x9D755B844618B20CULL, 0x4877CB17F2B42672ULL, 
            0xF4884DDC2E7B8FF2ULL, 0xC9654FE03552CD47ULL, 0x36A2128288468374ULL, 0x9A10E6AACF7DEF21ULL, 
            0x1D7501378FDEED3EULL, 0x7A5284D426D8D430ULL, 0xAFDB01CA5F28D338ULL, 0xB1C773E2B95A03C9ULL, 
            0xBE4CF2D79EECE7EFULL, 0x0A0FAB97FB41E1C6ULL, 0xF1BF8A62B6DAF887ULL, 0xAF50B29126391951ULL, 
            0x366194003B5194F5ULL, 0xA3C7D0FE3ED7CE48ULL, 0xA67D2A256FD236ECULL, 0x85D8A7A5B9C3DDBDULL, 
            0x3238B5865A4840A6ULL, 0x9632E4B27452C844ULL, 0x59E36401CB3ED2F3ULL, 0x596EF32DFC1D2519ULL, 
            0x7DA6ABEF772E6714ULL, 0xA00B01B8AA2651FAULL, 0xA053C00C7486D70FULL, 0x5066B0BE08AA0A02ULL
        },
        {
            0x94A72BE5AD5A32AAULL, 0xD0CAB03D1B951186ULL, 0x5C1254443DE3F071ULL, 0xE4AA1C3285D7B024ULL, 
            0xCFB73A840F0BCFBFULL, 0xCB81A8FB3F368F44ULL, 0xB57E692EB0E3CC25ULL, 0x702779094E85290AULL, 
            0x4ABCC1FF32702528ULL, 0xAB6A2BC8999AF125ULL, 0xC28F5DFD3F7CC3ABULL, 0xD29E77357165805FULL, 
            0x2355210DFC89FC44ULL, 0xBA176D92A0BFB644ULL, 0xD361E8184DDDE13AULL, 0x87AD891E78942653ULL, 
            0x035AAA028DF27225ULL, 0x7B7BA54A0C0F92CEULL, 0x3898E144E3D6BAC5ULL, 0x83B09DCB30708A40ULL, 
            0xF27AEDDB169ED5C2ULL, 0x01D730937336BDB3ULL, 0x4010CC5E005E4252ULL, 0x9A884BFEC1841F91ULL, 
            0x590A473BE82594C1ULL, 0xCD26666285A2FE43ULL, 0x9F5D3F594120209CULL, 0xD63B60D6D25E9818ULL, 
            0xBE6B13DF35FB5433ULL, 0xAF7DEE085DA94F67ULL, 0x7A25808FAF43C5E7ULL, 0xEE65F82245F03E5FULL
        },
        {
            0xC40B32393059EA2DULL, 0x6B7B34FC9EF65781ULL, 0x13CA4863252DDF38ULL, 0x5A7DF0C1B8FEA2DBULL, 
            0x54117F0CE2846DA3ULL, 0x377B417CFEF17D6EULL, 0xFA1EC672268CE65DULL, 0x6B143789EF230A8DULL, 
            0x72D07460D7568055ULL, 0x2D593BECDFB7F956ULL, 0x225C1C738A0DBB60ULL, 0x6CD81BA73A63D4A2ULL, 
            0x5E21C647A7CAFF6FULL, 0xA9EF34DDEA1726B4ULL, 0x432E0D9AED781D35ULL, 0x9294C7C44C90E0B7ULL, 
            0xEB4017E214ADFD26ULL, 0xFCE888742A3A3FAEULL, 0x2D9FE9B73D660038ULL, 0xB49106367C6E6ACCULL, 
            0x658D08C887929544ULL, 0x3CC940161625B094ULL, 0xCE9410C1F3D52156ULL, 0xFAF5DF54028B7E5DULL, 
            0xF71B72711C2B5614ULL, 0xB7F2BEF304FC37C0ULL, 0x4D12AFC87C938DA8ULL, 0x76EEBE18B229736AULL, 
            0xF1A3292B7438676CULL, 0xBABBD5FB6C1C7C66ULL, 0x4A0572E227DF0CBCULL, 0xCCE04383F12178DDULL
        },
        {
            0x7344DEB3A699F84BULL, 0x7EA8003C839FFCF5ULL, 0x9E19FDD058FABDDEULL, 0x37BF7ADEC31B8496ULL, 
            0x0EBEE1891B1061BEULL, 0x866AFB6294D81137ULL, 0x0666A16ADF3BE8E6ULL, 0x65F89B672D66BFA9ULL, 
            0xADF3A1845B3C3764ULL, 0xA25366DD7431A491ULL, 0xE6D24EB9123E70BBULL, 0xB7A08BBEACC7A380ULL, 
            0xBC6F0C339455017EULL, 0xDA673186A8F12685ULL, 0x4B4E669B82E17396ULL, 0xF41B65EF96B8C517ULL, 
            0x5B9B1171188BE86BULL, 0x7F3DFFD05152C8B5ULL, 0x3BC35D17B433048FULL, 0x77B8D011651B7064ULL, 
            0x8DAD664BFF7DE8A1ULL, 0x776271C80A1F158EULL, 0xAD13AD592554AD17ULL, 0x7A9C82721EB96A39ULL, 
            0xACBC7847905A88A5ULL, 0x978E7C49351BDEFDULL, 0x631BE2CD6D339115ULL, 0x79769409FB2C979FULL, 
            0xEF45BA9223AE6F2BULL, 0xDA5D9B77309DF7C3ULL, 0xB07045660B2AF031ULL, 0xEA48BC68A0D03340ULL
        },
        {
            0xB9D631994010250CULL, 0x47656A6DABA1FDF7ULL, 0xF4FD5E8DC7E137A8ULL, 0xD0811477E5D82829ULL, 
            0x269015F96E2F8DAEULL, 0x5D6BFD8B3F8B14E9ULL, 0x3420FB4A1FB0EC28ULL, 0xB965FD73C6AB460BULL, 
            0x8416F2280327ADE2ULL, 0x6A8C29ADE2733C3DULL, 0x42004AB060DC255FULL, 0x066F7A188F7495EFULL, 
            0x3EF26391AE13D377ULL, 0x5D7E042664F02E66ULL, 0x31EC1692BB8F6605ULL, 0xD708DFE5D5FE32CCULL, 
            0xF3C22B5FEDE75838ULL, 0xD0C9EC2A3B03F56DULL, 0xFFDB264583B76B7FULL, 0xB69CD8BC2CA8E24FULL, 
            0xEBA61D8E76F93DCAULL, 0xA3B2FEED2F40C058ULL, 0x73C7294DBF44979EULL, 0x8F444BC0B246A174ULL, 
            0xA1FE19950F61F4D2ULL, 0xDF7DE3420E3E2F40ULL, 0xA7038F25B4471696ULL, 0x6117E1F520306F49ULL, 
            0x34BDBA429D8739E1ULL, 0xB04473F94AE05422ULL, 0x0C47C07DBC1A6D9DULL, 0x7781C7FD7F502D02ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseEConstants = {
    0x1293BD6A5DC747B6ULL,
    0x752527BDB5057979ULL,
    0x0D80A10E85569B34ULL,
    0x1293BD6A5DC747B6ULL,
    0x752527BDB5057979ULL,
    0x0D80A10E85569B34ULL,
    0xDDD4DB159B65695BULL,
    0x323F8514851C76A5ULL,
    0x66,
    0x16,
    0x0B,
    0x33,
    0x6F,
    0x62,
    0x1C,
    0x60
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseFSalts = {
    {
        {
            0x3143921B1B6328B1ULL, 0x210CB6424F36B461ULL, 0xA86BE853BE60B8DEULL, 0x5A8EFBDAA6B48AA3ULL, 
            0xDC0796E11E7A0142ULL, 0xEFE2B05A4165FCEDULL, 0xC940E9C7FE206E4EULL, 0x1EB3367E2FF47B20ULL, 
            0x7A2E5EB0CBD6743EULL, 0x4D8F3322A7B868F5ULL, 0x6A7CEA225434D201ULL, 0x526B256EAD390926ULL, 
            0xDDCC551DF742E24DULL, 0xAA9ED57CA41D4CCBULL, 0x0C5116823C5A809DULL, 0xCE06C18DC453E31DULL, 
            0x997ECDA9059ACB00ULL, 0x408C8ECF974479F4ULL, 0x9B8B55396AF001FBULL, 0x242C668782828EEFULL, 
            0x585FE846F4A6DAAAULL, 0x08EF236B93753132ULL, 0x3F051D04C24236CBULL, 0x1E43B677AD43C86AULL, 
            0x1ACC25024740BDA3ULL, 0xAEE430809C12C5CAULL, 0x9F477DC84782823AULL, 0xC1FD90E7DC44BFE7ULL, 
            0xFB1817FDCFDAA7A0ULL, 0x0A0E52C14F51E8A5ULL, 0x40DE320E42685721ULL, 0x7D8D09F993A99885ULL
        },
        {
            0x2406D54CE8DB85F3ULL, 0x095771610437A364ULL, 0xECF707FFDB249EC1ULL, 0x39477D0288A67107ULL, 
            0xA166E99B74DA2B74ULL, 0x9A38808F65079467ULL, 0x079FE880334368E8ULL, 0x118456266BEC51DFULL, 
            0x49A5CD95B5AB3862ULL, 0xE9C37BCA470D053FULL, 0xBC14228322C6A8C6ULL, 0x8D08856247789924ULL, 
            0xD8B954AECF2D5F2AULL, 0x002410FCC4C6294AULL, 0x294E9174B2369612ULL, 0x380A7C8E33D0E0F3ULL, 
            0x3C1EC7B18EFBFA41ULL, 0xB7619FB1B9A058FBULL, 0x807025CF766A830EULL, 0x7DB4BC8140BD890DULL, 
            0x2EA5FD761BB5091EULL, 0xCEC6B9FA66A6EC92ULL, 0xB91F3E6C156F0F59ULL, 0x0D63467609E3F282ULL, 
            0x40DE3806388364DEULL, 0x65A364939AC7A6F6ULL, 0x4072E5FFEDEB5975ULL, 0xBBB7CD2717FFBB4FULL, 
            0x5970CFDC62C0C17EULL, 0x1CF4F77046C9DAACULL, 0xECDFDCCE3C0074E0ULL, 0x82124EBE5EB405F8ULL
        },
        {
            0x8CA2A95CD3AF199FULL, 0x07A9346E560FFF51ULL, 0x8B6A7BAB97953F63ULL, 0xF7EA675D61B24AB4ULL, 
            0x40F41063E6A3ACFFULL, 0x6E143E6EF9D92BEEULL, 0xDAB2AA2DB6D056DDULL, 0x7D5D938427C9ADBFULL, 
            0x9F4089213B1D9B8BULL, 0x54F50933A014D57FULL, 0xFD2E719862D265ABULL, 0x90E9308C1ACCEAE0ULL, 
            0xA38BF45D6A39375EULL, 0x468FD915C4174DA5ULL, 0xDA71E96F86B7FA5FULL, 0x13AD5075CCC949FCULL, 
            0x01B3E2AB63C7238AULL, 0xBB3A2603E0F1909CULL, 0x164C75A7CB9EE037ULL, 0x706E4A93B82A8040ULL, 
            0x9C430409FDD71AC4ULL, 0x4E1CACE50B24E268ULL, 0xCD41A28937F39032ULL, 0x1D2DF165B732D4C7ULL, 
            0x87623DB1322B6810ULL, 0x81692411A87B82EBULL, 0x98A7AC91F6D52C4CULL, 0x0C78C05EBBFF7A36ULL, 
            0x7436DCFFF9E8910DULL, 0x1B1DE2770EA21E72ULL, 0x7887AEAFFA78B5C3ULL, 0x0760F343364B277EULL
        },
        {
            0xF6AF6CC5349F06ACULL, 0xED35A78A573D5946ULL, 0x5073C12145D4135DULL, 0xD22A976C6B81CCEEULL, 
            0x72187C7E56DE5B61ULL, 0x9B1101D5A0FC9681ULL, 0xB4937043C0F668E7ULL, 0x145AF85C3CEB915CULL, 
            0xE9D4DC811670ED38ULL, 0x886A2D60FA0D142FULL, 0x8EFB17E9F70D42CAULL, 0x95808743D661B175ULL, 
            0x105EAB13149B4508ULL, 0x553CB7500C74495BULL, 0xD7339DB5953ADA20ULL, 0x93CA8850B08A13BCULL, 
            0x6B73AB0B6CB14F02ULL, 0x20C75D1BB0372ECDULL, 0xA9A14103E87772E3ULL, 0xD09D57831F7FA487ULL, 
            0xC2FA78BE2DF6E4DEULL, 0xF262C7E5EDC9900EULL, 0xF617F26491846695ULL, 0xC33EA2F93B0E0D83ULL, 
            0x8E65C43210ACCF2EULL, 0x9711AC11EBF7046AULL, 0x7539CDEC7F6114E9ULL, 0x0A9D26B20C869CBBULL, 
            0x7486541DB397977BULL, 0x3E6E7D69D0F045C1ULL, 0xCE6643C4750F6744ULL, 0x55394ABAF88C6095ULL
        },
        {
            0x526D40E97A1CD470ULL, 0x9791E424D4625564ULL, 0xFB9B79C7D9BB0C9EULL, 0xD4A03B13C917EFA7ULL, 
            0x8B6D855A04F28BC3ULL, 0xDD97054A5BB36254ULL, 0x49260E8A9A89466CULL, 0xE014B0E8CD69E287ULL, 
            0xB162AEF2D12B8576ULL, 0x118B4A3A4ECE1727ULL, 0xB63668A548199BDAULL, 0x5C171C302CDDA0AAULL, 
            0x7E536C3A522A6F1EULL, 0x5F0118FA2FD2C8CBULL, 0x32B0A4ACD84F9193ULL, 0x0416AC02594979A5ULL, 
            0xF1F174AC1A153F66ULL, 0x64E1D21633688052ULL, 0x12E30BA50BC4C94AULL, 0x5B9AF7572058C484ULL, 
            0xD5C52AD8915AA99EULL, 0x296EBF658BEBE4B2ULL, 0x093F2EB5429F7D77ULL, 0xC7BEAD35DF6873B6ULL, 
            0xA294F27CB0063BAEULL, 0x1F4852CB417E7CC7ULL, 0xFCAC85024DC8F78AULL, 0x230F03A6E318F33BULL, 
            0xE6CE6761C3D7FBEDULL, 0xDA456291713FC1C8ULL, 0xFBE4BDB041A2F63EULL, 0x67C46D2C189F2A65ULL
        },
        {
            0x3E6E007437636AF6ULL, 0xE98A29A4DF5F1F79ULL, 0xABDBF95B279406FFULL, 0xC707BB233CE51EADULL, 
            0x0F0E9DB6D1E4CA41ULL, 0x55EC3AB379BCB1B4ULL, 0x746B6F188A965D10ULL, 0x2ADBDAE2FA167112ULL, 
            0xF3778DFA729A202BULL, 0x92758256AB8EA1B4ULL, 0x6EA0FB1F5390276DULL, 0x48C4C8C960219951ULL, 
            0x5002BA2E7F8F0327ULL, 0xBD95D282DF5D276EULL, 0x4CDCDE5ED68A539AULL, 0x26FDB1B16D2E5601ULL, 
            0x301B675D4043C6A6ULL, 0x380BDC72C2EB7692ULL, 0xFB0A2A353AD378E9ULL, 0xFFBB1BCA04535385ULL, 
            0xA64F8890CF0C00FFULL, 0x2736497215D8279FULL, 0xD81F7EBD29121E3FULL, 0x078D2849B2A4D0D2ULL, 
            0x720B1000E9E31D11ULL, 0x0CA1ACDF20E1E606ULL, 0x62BEF43979E53274ULL, 0x554563B500ED3C12ULL, 
            0xC00529B63FE93009ULL, 0xABFF21E4E070CCD6ULL, 0x092FC782FC353045ULL, 0xF289A0DBCB9D6665ULL
        }
    },
    {
        {
            0x078EA88033ECF310ULL, 0x7A54B34BB626C7C1ULL, 0x804DE6E3B7CE9BC1ULL, 0x37EEAA5D59276A9CULL, 
            0x6E5752D5EFFE4B42ULL, 0xD5F7A5C8038B286BULL, 0x57769B4B3320A52BULL, 0x4C1775FC2617FBB5ULL, 
            0xC643A85F217DA865ULL, 0x55739BB217E05369ULL, 0x042572DDAE167D72ULL, 0x9A2D2799B191B958ULL, 
            0xABE1A1B641C3785DULL, 0x30A12D3A54847FC3ULL, 0x64BAB693FFF11A62ULL, 0x1DDE5C228F828F10ULL, 
            0x301EADF4F4D44A81ULL, 0x88B4C6F7E3D8E350ULL, 0x7CB5AA7600D6F516ULL, 0xE0EE857062BC62D3ULL, 
            0x7480A514F9AC7DDEULL, 0x2ECC6074B06D6DC8ULL, 0x3F2E830917912D29ULL, 0xAE9DD76338D2D3C8ULL, 
            0x20D1C59632C42738ULL, 0xF6EDA3EF60C1D4E8ULL, 0x820A813FA1BBB746ULL, 0xB8BE99C48C398454ULL, 
            0xDD05BE0BFDEDC95BULL, 0x0CC01488DF6E6459ULL, 0x172C48634A001E3DULL, 0xBE380011076DB6C9ULL
        },
        {
            0x528FA1195B5E03AAULL, 0x51B78DE02889DA28ULL, 0x322A76792B917F79ULL, 0xC58B2F2EC75E704CULL, 
            0x135F7B5E335B842CULL, 0xDF5B4F6D9A26B0EFULL, 0xD4F7BD1E0B0ED710ULL, 0x153C16641CA28860ULL, 
            0x725BEC217172502EULL, 0xD49B6CDB1BAEA0A5ULL, 0x5E56FDA9B76BE719ULL, 0xE25C9620CEBF7612ULL, 
            0x6D413A55B6834DEFULL, 0x6668BC946EF26EC4ULL, 0x3B1BC23BDC5AB9C3ULL, 0x0B88DCD81000C8BFULL, 
            0x95A8DF139B30D544ULL, 0xB7A92312A3667FF8ULL, 0x83875C975C94409AULL, 0x056EBB3D3EDFEA8CULL, 
            0xD868A584EAA3B8BEULL, 0x9AADCB238BFEA38CULL, 0x9985AED57CECBA71ULL, 0xC6257B8AAF0D3C3DULL, 
            0x8325DFE9B12E0215ULL, 0xC19E46B0B94E24DEULL, 0xFD90BAF2DFBD4212ULL, 0x6198C42A6C029C14ULL, 
            0xC254A1AC8C319891ULL, 0xB54B1F3F3E9AD090ULL, 0x1FB2FAA548209C04ULL, 0xD9788C6197CCF874ULL
        },
        {
            0x5010E6466D96CAD2ULL, 0x4CA24CD6F4094554ULL, 0xF9E2D0F91EF4759BULL, 0x5A36F7B2F5C7780AULL, 
            0x99AD1AB4AF271B41ULL, 0xAF87EF440B0824B4ULL, 0xFECACD2C8514D157ULL, 0xD11E83DC3CE7B6A0ULL, 
            0xD749A4DC320FFD26ULL, 0x7BA497D568030337ULL, 0x6797AE5F8E3272F7ULL, 0xBF0A3D275078A8E8ULL, 
            0xDEFD810A2C0089F3ULL, 0x618212B9BAAA0373ULL, 0xF1FBF70CA2F49B69ULL, 0x58C0B3BD8E703516ULL, 
            0x2D61AEF85D9E8F33ULL, 0xEA994E99E43D363CULL, 0x7FF5663784044A39ULL, 0xC7DC04534426B028ULL, 
            0x4571F03FF673A84EULL, 0x0C136C97EBABBAFCULL, 0xC23A19A4CA003DEEULL, 0x78F2BFE745A33178ULL, 
            0x928C64B0008C5478ULL, 0x2A4D398A9FE625ABULL, 0x67BF7CB76C71253FULL, 0x53021044C7053CD8ULL, 
            0xB19EA73F36017389ULL, 0xC5C34D5270D97B8BULL, 0xC5081634D2A79CE8ULL, 0x3F3D8EA74DCB437BULL
        },
        {
            0xCAB05E7326DCF9ECULL, 0x0EDFAD0111A85D38ULL, 0x724DF324AF657EF0ULL, 0xA00B3C81E1AC5144ULL, 
            0x100D2CCC0F2B6E96ULL, 0x66DC977A598DC375ULL, 0xCE7CD2EBFF94E9BAULL, 0x421CDB4D34F3753AULL, 
            0x4F3C0A67D23D6A8FULL, 0xCFD85833F0DE2A65ULL, 0x37343A8C937F85ADULL, 0xC8EE267AD77C25A2ULL, 
            0x82D2FA361E92772CULL, 0x8F67145A06A7CFA9ULL, 0xF74D6ACB542D16F1ULL, 0x32D07F6104AA0DF7ULL, 
            0xBE0EA945B8484E2CULL, 0xA8765EEDE4811852ULL, 0x1C048FE6682F50D9ULL, 0x278FDB2691C65E71ULL, 
            0x440795858ED1CE77ULL, 0xC41898EE6FC151CDULL, 0x2C1573A2B0FC3FEAULL, 0x8BF82B2F89641F34ULL, 
            0x8DBBD57CB71AA108ULL, 0x48A0192AE44AC01CULL, 0x73E7AEBAE73DCF2EULL, 0xA2A56743327BEC04ULL, 
            0xD15048F74B2E6616ULL, 0xD64E29D8F332993FULL, 0x569F528C3F616C98ULL, 0xF7790C59C9BDAA3AULL
        },
        {
            0x38613EC05BCBD29EULL, 0x89824CD1164B764DULL, 0x472194F0CE3727F6ULL, 0x0923B6451762076CULL, 
            0xC96813B1ED261A26ULL, 0x677247DD393F6FB3ULL, 0x3D00F951AA09A96DULL, 0x5348501FE2371B03ULL, 
            0xC03B84339BBAC47EULL, 0x78D598DEF025C4A7ULL, 0x0B91CB66F7DD9F8EULL, 0x27E76E2EB7D7B74FULL, 
            0xAA70A5312F834C16ULL, 0xA05A18FAF58B6083ULL, 0x6DCA8814F977F657ULL, 0x595BC68A582E443FULL, 
            0xEF773683B72DFADBULL, 0xD23EAF654722D374ULL, 0xDCC1A7AB2D759D9BULL, 0x3DF6EC6D3C5C0B89ULL, 
            0x5FAC6CB213037AC3ULL, 0xFC87D6B4A75C06A2ULL, 0x5E8EF2B5B515EEB3ULL, 0xD9B94E946E7242D6ULL, 
            0xF4FEFF1223698DDAULL, 0x66D9D34291424E4AULL, 0xB7BD6BB01A5EE3BEULL, 0xFBE14F18DA4217CAULL, 
            0x6000087FFE29FD89ULL, 0x672B11EF0810288FULL, 0x1847C7F9CC24A649ULL, 0x733E65F7E085E4CDULL
        },
        {
            0xFE6663B207ABCCEFULL, 0x786857196CDC5288ULL, 0xC3BD267C11EB1BD1ULL, 0x1B1DD8027F4BA83AULL, 
            0x2094AE527B575D15ULL, 0x41D43880D15F564FULL, 0x75F5352AD059B8EDULL, 0x886AB4D1801312A4ULL, 
            0xE887196603EB0CB5ULL, 0xE5742CD8432DE88EULL, 0x7A27C94359D4C51FULL, 0xDC76553C6DCD7CE8ULL, 
            0xEDA68B6CB46BAF5BULL, 0x5F5215A440F96031ULL, 0xAF4B75F0329E4E25ULL, 0x8CD1E4A291B25C73ULL, 
            0xB0EA59997539DAB2ULL, 0xA35EE695657D0D62ULL, 0xF3B925715FC7B520ULL, 0x124C2914AE0085FEULL, 
            0xCD923C711B1BCE85ULL, 0x68F6BA53AA9A5990ULL, 0xCEDB627B26CB52AFULL, 0x0361FCCFC82FC695ULL, 
            0xA7D2D9C85EACE55EULL, 0xDC80926D951B2F20ULL, 0xF6B13FCA520ACE41ULL, 0x8DF36D15BEC5D781ULL, 
            0xCA0A698DFE1EB7A3ULL, 0xDE158AEBE02031DCULL, 0x9E39EE9CEFAAAD50ULL, 0xE1621A6F3F937B4EULL
        }
    },
    {
        {
            0xF3BD8A1E309B5644ULL, 0xC3219668CC24D28FULL, 0x5A9E9FFFFEA1DCBAULL, 0x77CDECCE572C3C4BULL, 
            0xF4BCD2C5E92DC88EULL, 0x2DB2D17C2EA9BF4FULL, 0x754C10F33423B680ULL, 0x2D5A0886875B8022ULL, 
            0x4759B4CC79C7449BULL, 0xA45F6714C54544B3ULL, 0x437653AB18544097ULL, 0x720C0C0AE49F54B3ULL, 
            0x0086E6EAB4D9D230ULL, 0xB660F857F43657B8ULL, 0x19172F22DEA4E137ULL, 0xB272333D7B8DE333ULL, 
            0x0DDD582BCC529D51ULL, 0x7F06DA4A90E1D985ULL, 0x4F4DCF025D98E4F0ULL, 0xF5ED44BDBB0EC312ULL, 
            0xCF529A6A7F3A9ED9ULL, 0xFA2957D42D9F69FAULL, 0xD6D7BD9304AB9D6FULL, 0xC47C9C4346EE663BULL, 
            0x731F1CFF8706DDAAULL, 0xA957DFEC43DFBEB4ULL, 0x4F64E1A337A04ED3ULL, 0x63109405BF4937C9ULL, 
            0x040E707C179F7CD9ULL, 0xD137D5FEBB570086ULL, 0x39F0BEFFD9CD948FULL, 0xA71368C5EC3ECCD3ULL
        },
        {
            0xC2C53DA22EBDED12ULL, 0x9D4BE2D43B910363ULL, 0x893CE7E4FAB10FFAULL, 0x228436D875BC7A5DULL, 
            0x6F81F389401648F9ULL, 0x53F9EFCCCC672B19ULL, 0xB4DCE9EFB1966524ULL, 0x8FF57F66C6091365ULL, 
            0xD38255EB480CE4C0ULL, 0x71E07FA5E0F0D2F7ULL, 0xC75D1BCDAA3B97D1ULL, 0x87755D30F38613B4ULL, 
            0x6C66404C63F89BA7ULL, 0x958DE2F65DA34656ULL, 0x36CED877D4D8A9E3ULL, 0xF29EB641E4822DD0ULL, 
            0xC796296CD25B6A37ULL, 0x4B7E6AB9F3963B31ULL, 0x5A45085120A3D5B5ULL, 0xFB79DDACF2310459ULL, 
            0x443D5F61DA303FE2ULL, 0x5366897C39E36438ULL, 0x95499B152E99E6C9ULL, 0x81846E8131DA77A5ULL, 
            0xC10E7C49AECB4CCFULL, 0x8B0117ECE4BC6D3FULL, 0x32C60C175E63ED69ULL, 0xEFD680505EA6B611ULL, 
            0x5AC136D0FA44C142ULL, 0x5BA5E963238E36C4ULL, 0x5E9191C569EF5C8BULL, 0x6DF6A9BA4E424657ULL
        },
        {
            0xA41957480D8FE795ULL, 0xBBF1A65BE1B120F9ULL, 0x7153B945C5CE794DULL, 0xF6F01BAE970C849AULL, 
            0x2C6E74783D8484D0ULL, 0x9D79523DF9C05AB2ULL, 0x9CC21A0E3D966CEAULL, 0x6FF97C34A468EB1DULL, 
            0x9A07653BC6AE9576ULL, 0x021E0BFC3BEFA242ULL, 0x063B04865CC3C71CULL, 0x5441540686FE32DAULL, 
            0x23B2F6F64F984144ULL, 0xEB64612FF214ABB0ULL, 0xB0003694ACA397A7ULL, 0xBBBE87198F6DA474ULL, 
            0x0C7FEA3B08F4B406ULL, 0x442ED6C42999CDC1ULL, 0x37C993FE16E3AAF2ULL, 0x282961AAFB65AF79ULL, 
            0xBD0ED1E16690ADADULL, 0x0DAE2824887B6DE0ULL, 0xB51A8197C60A3C2BULL, 0x2B081B39FD816B6EULL, 
            0xEC958778F3D6F405ULL, 0xFB47EE3B7C2CCFE9ULL, 0x90D6A05031024AF7ULL, 0xBDC4E98FF5F5369AULL, 
            0x9705700E65AEE175ULL, 0x7564A0F5EB564024ULL, 0xC34516FB90C4637DULL, 0x2F6C3B69CA2C90CAULL
        },
        {
            0x0802870203D0E587ULL, 0xCA5E954305FE9FC8ULL, 0xA54251844D76D33FULL, 0xD5321D39B1658B0AULL, 
            0x245AA5A5AEB3065EULL, 0x29D88E598B22E940ULL, 0x0A68C5AF1D413E22ULL, 0xADBD37EC7D2CCD8DULL, 
            0x40711360B5234BCAULL, 0x267414FFC525D743ULL, 0x12A674D45FEB0D16ULL, 0x7027E19FFF411F0FULL, 
            0x7B71873F5005EEDAULL, 0x23BC501B778FDA89ULL, 0x051D1C6ED0988743ULL, 0x43E7AD7D3C06F7B5ULL, 
            0x012BFD15E404D1C1ULL, 0x0E7B98E36B394B9DULL, 0xEFF810722275593EULL, 0xDD930573FAB124A5ULL, 
            0x681C2F05CA40AB52ULL, 0xED0FB15856AF36A9ULL, 0xCE8B3FDF45051B6FULL, 0x7DBABBE090D5AA28ULL, 
            0x56E00ECDAEF755CCULL, 0x83DF863430EA1722ULL, 0xE40E843C15D7ECC4ULL, 0x74331FEA19A24019ULL, 
            0xFBDE8978F4FE9C75ULL, 0x7FB3B1F54C58521FULL, 0xE8E1157EA7F10699ULL, 0x10907E7287DDC8A7ULL
        },
        {
            0x63D48ECB135C3979ULL, 0x61EA30CFB1D7497DULL, 0x20EF9E0E5A1D5AD1ULL, 0xF5DE1F232AE10CB0ULL, 
            0xFFCC08CF5F68BB43ULL, 0xC83054957B31734AULL, 0x7DC8812D0496E36AULL, 0x6891713CEAAAA6A6ULL, 
            0x64A0487CC3561E77ULL, 0x07B74BAEB4C7573FULL, 0x22EED130190E075EULL, 0x5F825B4378F84EDCULL, 
            0x96E622C77D1FDA6FULL, 0x26BF1B0860BF4759ULL, 0x5ACB47ED3070837DULL, 0xFAB3CF526628C7D9ULL, 
            0xB33112CF09CEA9B4ULL, 0x76A1CDE2D0325942ULL, 0xD26B6C59A5A70868ULL, 0xEB4218F9ED0F3DB3ULL, 
            0x1C01DF9654E798FDULL, 0x177BED6704D87F53ULL, 0x37A42A23122D3800ULL, 0x3A2DDD01BCFEB4E3ULL, 
            0xC9F67272CFCE77F5ULL, 0xBC03BC26BE3BF026ULL, 0xBBA2FCE3BF7F436BULL, 0x0FCED308B1CF7854ULL, 
            0x3466B8C927BFEB6DULL, 0x57A68928F547F71AULL, 0x4CEDB0974FF9F30FULL, 0xAB2F1207F3FAD786ULL
        },
        {
            0x339E1E24FF6D9BC0ULL, 0x7C439D509D555B57ULL, 0x311A6DE725069114ULL, 0x4823DB3FBD8497C6ULL, 
            0x5751CC97A2A1EFF5ULL, 0x4AFCF9CED77A84E3ULL, 0x052F77A7D65E01F0ULL, 0x636A30FC615959E0ULL, 
            0x279C56AA01E102D1ULL, 0x040181EBAF241204ULL, 0x0CF34ABB0566FE06ULL, 0x7B5D718BCA7AE110ULL, 
            0xF5B4801FEB1A4780ULL, 0xB8BFC0BE01CC1B62ULL, 0x3EA408107CE03F79ULL, 0xBF85127EC9018645ULL, 
            0x8ED16C14F3C05759ULL, 0x30235F0E928A1D16ULL, 0x5C5574DFAEAFB936ULL, 0xFEF2677F29F6B6F2ULL, 
            0x3C0014BDEE054501ULL, 0x3DE781FF0C8AF419ULL, 0x513C19AE3303D835ULL, 0x2541765F2FC8EBB3ULL, 
            0xEE0C812CF411C8EEULL, 0xAC7B3877F74C0E24ULL, 0x0A284A106E5676B8ULL, 0x11327AF74D12A625ULL, 
            0xCE24C6308F79B856ULL, 0x39DDEAB971B97722ULL, 0xA5B6EDD1C1FEEEDAULL, 0xB97BAB7F8E74A249ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseFConstants = {
    0x24BBAFE73052B9BEULL,
    0x6B2DCA4C3432FC18ULL,
    0xF8B0BF413D94BC62ULL,
    0x24BBAFE73052B9BEULL,
    0x6B2DCA4C3432FC18ULL,
    0xF8B0BF413D94BC62ULL,
    0xADF2BC4F3D7028F1ULL,
    0x43D4AA64D2895AD6ULL,
    0x69,
    0xFA,
    0xE7,
    0xD1,
    0xF0,
    0xCB,
    0xE6,
    0x67
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseGSalts = {
    {
        {
            0x17425D1A28C67B39ULL, 0x27EC860E2CF6D22EULL, 0xF82CD84D87C9A7C1ULL, 0x1F9159C149AA9A67ULL, 
            0x3FC971DFC0DE46A4ULL, 0x20DA1FCB88423D00ULL, 0xDC6D2B0E313358A4ULL, 0x9963B555D893F25AULL, 
            0xF42D945E4070847CULL, 0xB5A0062B871A517EULL, 0xDE3752FFEFE1BF44ULL, 0xACFE0C942EEED773ULL, 
            0xB78B89DCE8BE4643ULL, 0xBF89BDC7F9BDE525ULL, 0x2BAC5C819547B35EULL, 0x09A64661A81B7AE5ULL, 
            0xFC5B228D5431928AULL, 0x6C12411540B6ABFDULL, 0xF648291A61F5B70CULL, 0xA6FB1F4D1CB469BCULL, 
            0x9FF3C8BA8E24642BULL, 0x7CFDA3529E690791ULL, 0x8C3D130BCD3AD76BULL, 0x383343CDF0A9F05BULL, 
            0x00825C7FD275951AULL, 0x785A86239A82E861ULL, 0x89266FAFF94780ADULL, 0xDDEDEDE887F3C9F0ULL, 
            0x909658963BDF3027ULL, 0x676F09C32EC9B548ULL, 0x045C4598C1DCD6C6ULL, 0xA7A6E3D99F1E7A64ULL
        },
        {
            0xA7690E06A2000514ULL, 0x19E9D3A30B49E901ULL, 0xFBC86A21071A131EULL, 0xD632C3BE7FB06FCAULL, 
            0xA2B942DE24815F88ULL, 0xA37BE41DD43B878AULL, 0xD5FC73613A51E2E7ULL, 0x7898F337BF423306ULL, 
            0x277EA871F2D9DF4EULL, 0x4DECDC57FC4A2E5BULL, 0x8BA43A9F2EA4428FULL, 0x46EB1FE961377ADEULL, 
            0x0306E749A30BE46BULL, 0x7DE41B81E08F9BD4ULL, 0xA95350FC527FF340ULL, 0x5E0B96D76BDB581CULL, 
            0x038E98105E4175CCULL, 0xCC224C1C22EF85A2ULL, 0x321D715A9A014BDFULL, 0x03E8957256FCE244ULL, 
            0x8D52026FE15A5B39ULL, 0x78B9DC3704C578B9ULL, 0x56E5547D65127BEBULL, 0x4E2F277D8733A20CULL, 
            0x6DAD6139B4EDA83EULL, 0x241724931EFE2D7DULL, 0x1DE05749B31E00E1ULL, 0xFAC439CFC53EC218ULL, 
            0xCDF8043FAEC8F669ULL, 0x7417A8F2492797CDULL, 0x80510925805889D6ULL, 0x3FB12235BCE50D04ULL
        },
        {
            0x19243C60CED4F460ULL, 0x4812E07253CCC1A3ULL, 0x5B720A7D35DEAF27ULL, 0x5A4A62A94F5B526BULL, 
            0x28DB5CD4B5AF20A5ULL, 0x08172182CD411AAAULL, 0xF64880F2966173F4ULL, 0xA5707592CE5CC6B4ULL, 
            0x5D231A39B9A171A4ULL, 0x41428AC20933423EULL, 0x3214DDF2C32CB384ULL, 0x7C2736A85BB3C294ULL, 
            0xA966E78122010D66ULL, 0x146746DB13B41A2BULL, 0xAE6B5A893560791DULL, 0xB1719F55D35C25FDULL, 
            0xE4DC5BEC51FABB56ULL, 0xA709EB9FFE6D819BULL, 0x63B77581CEAD73EDULL, 0x895A95D25E96D0C2ULL, 
            0xE9F60E9CCC69D6BCULL, 0x00A3777E23F8EA2FULL, 0x8A7B66B0F4C48DC1ULL, 0x9F3F375DED28B9B7ULL, 
            0x3672601DEE07FCABULL, 0x05ED738904DCEF6FULL, 0x5CB6CAC58C9217C8ULL, 0x3E4694CAEDAAE397ULL, 
            0x9181AA4BF055CD0CULL, 0xF3FF44F9E2AA77B3ULL, 0x21B580E1D47EE61DULL, 0xCC408D5D4443B18AULL
        },
        {
            0x541D1A1FED413AA6ULL, 0xC339BABA5E393F16ULL, 0xDB9665C996117FD9ULL, 0xF621DAFBC32255CAULL, 
            0x72BC63ACDD6A3309ULL, 0x33056ACD8CB840E4ULL, 0xA6A3CAAF0945E5E8ULL, 0xF019EC89727F3793ULL, 
            0x40A9F6F8823E0693ULL, 0xDF91329DD11D6970ULL, 0xF44E671241297B46ULL, 0x5D4E5DC359F9630FULL, 
            0x74F96B8D4972D443ULL, 0x66FFCC99E6F7ED5AULL, 0x0015FB7BC11BC61EULL, 0x81549A88CC0131F9ULL, 
            0xD49E5DB95C8B9F78ULL, 0xBCD2C2F4E5B6174DULL, 0x9FBE775DC45D551DULL, 0x2BE4B15A2EEF1D47ULL, 
            0xA8B2DC86FC22A703ULL, 0x59FD1E5C5774D9EAULL, 0x5F9F8F096A894011ULL, 0x71C9D2194E7F4B3DULL, 
            0x05EE0751B0D3ACCBULL, 0xB292524DF72EE678ULL, 0x6DE8A85D2831BC6AULL, 0x4769DB3970653C16ULL, 
            0xFA381B96EA898F7FULL, 0x2A4BADDFE44FC773ULL, 0x11B853B79ED869CFULL, 0xDC51A24216E9F6E8ULL
        },
        {
            0xC05AD816CE50722AULL, 0xFE53D0B941757BABULL, 0x2EEDD1A189C984A2ULL, 0x5CC7970AE176D1CAULL, 
            0x0742353AC5798E34ULL, 0xB64755E67202589AULL, 0xA1C81E3366E1ACB5ULL, 0xEAB0A732693596A8ULL, 
            0x496F67CA77CFA091ULL, 0xE9CB253CCA14CA6EULL, 0x2BE5623774EA8A5BULL, 0xA50D258E2B12AF92ULL, 
            0x6E3FF2240278351AULL, 0xAEAD9F538AE02A69ULL, 0x7C9351FEFDF6692BULL, 0xFD0470D41840BB3BULL, 
            0xAB564949A44DA9D8ULL, 0xB317E2DCA76E0132ULL, 0x56AF6077AC829595ULL, 0x50D9384AC8AD5E11ULL, 
            0xD6D27763479D91E0ULL, 0xF0028C0466A1C0ABULL, 0x9EC1E3CA02D3A64EULL, 0xCB55AB64A6C0A9F0ULL, 
            0xB88B424813F45AE0ULL, 0xFAA8AC0347FC7D41ULL, 0xB07771530D171BA5ULL, 0xFEBEDFBC43CC36F2ULL, 
            0x317CEA9A3B1C3EABULL, 0xC9A4904B0D8FDEB4ULL, 0xDACF3DE824A727EBULL, 0x47DD496C2174EB85ULL
        },
        {
            0xB288795B83BE3D82ULL, 0xEDFB837219895CD9ULL, 0x0D099AA85A86F14CULL, 0xCBDBF921C5D7CBD0ULL, 
            0x739A53E509578DA0ULL, 0xD811CAAE8D52CE2CULL, 0x11D36AE0D8F4104CULL, 0x55D0D74FC2473987ULL, 
            0xA440525628FD1C42ULL, 0x284B4AF6478560A8ULL, 0x7335B96C10F09363ULL, 0xD385BDBFCFB524B0ULL, 
            0x595AD9E7163EFC9FULL, 0xC7B57A57796B6CABULL, 0xED49CE94263B66B4ULL, 0x5F256BD0B6CF97C3ULL, 
            0x836C75FF0503672CULL, 0x3D9ABDF93C666FE7ULL, 0xDC92C8A499F86E9DULL, 0x04E6729E1FEBAB54ULL, 
            0x8EA3B4DE7CAB2FBDULL, 0x10536FEC39CCBA7FULL, 0xDA63E38B9873F358ULL, 0x4691049BD2807958ULL, 
            0x4DB83D618F3EF828ULL, 0x276AED1F7BB46C70ULL, 0x0623822F07F56FC3ULL, 0x89984C56A58F92A5ULL, 
            0xE66DBFE19FC35068ULL, 0x24B0B902B0D16E06ULL, 0x3E40C26481FA2193ULL, 0xEEDBB2818CAAB307ULL
        }
    },
    {
        {
            0x41DFC50FBEC8971BULL, 0xCBFD0322115B9341ULL, 0xD47B63E1EDA1C983ULL, 0xCD9A8EC05957D790ULL, 
            0xD81B3F90DBEF6CB8ULL, 0xD4F59D3FEE9CCFC8ULL, 0x5D5F1B0BECF1424CULL, 0xE384B2BDABBDCC6BULL, 
            0xA41107B549E449F2ULL, 0x623C7DB757969DD5ULL, 0xCE2E135E1DDFD3D8ULL, 0xB9528AB2F5C15419ULL, 
            0x934D8A2CFE25111AULL, 0xDDDC06605A6C431BULL, 0xECFFBAB2F0BA2A40ULL, 0x4AF5CD85F7AD391BULL, 
            0x488C2947D777358EULL, 0xBA57EF857FAD32CBULL, 0xB174D10851A15856ULL, 0x70BED67DC10A8635ULL, 
            0x6510B2B818BE440CULL, 0x8F133E81A2A72D8FULL, 0x08E9ACDB82BE44FBULL, 0xE9B94EFEC1F8B66BULL, 
            0x1A79D6C0A2ED598BULL, 0x19684EE6720E9680ULL, 0x07A1B1FAAC0AE516ULL, 0x131EF993FFEC602EULL, 
            0x92866FD292F9068DULL, 0x8CF83C53A1E8FD64ULL, 0x72BD97C3AB59A370ULL, 0x807F6E80814095D6ULL
        },
        {
            0xCE373BF92BD60330ULL, 0x301164C68D143E1FULL, 0xB11FAD4FA9721D61ULL, 0xD1BE6005141F6AD1ULL, 
            0xB9C68DEB0C1FCD31ULL, 0xCF830E89AD2F4033ULL, 0x3C58DE5BDE442F06ULL, 0xCC67A4A98EF2C3D6ULL, 
            0xD7C99EA45EE09DEFULL, 0xC2CA0DECE0EA497AULL, 0xCB2AA9032F6833F0ULL, 0x938B43894D7D7D71ULL, 
            0x6FC6EE0C2379DACFULL, 0xF1DFB95110D68297ULL, 0x6B6D5847264976D7ULL, 0xFB3F9FB8F5C9DEA1ULL, 
            0x06CE0DED1F3164A9ULL, 0xD65E4C62A107B5B8ULL, 0xBD871CA032207F3DULL, 0xEDD3AC525CC5E846ULL, 
            0x02396864A86D555CULL, 0x7973CBC7A270C267ULL, 0x4F6D162FDAB61673ULL, 0x18C043ADCA360C8CULL, 
            0x41736C516CF21AB8ULL, 0xEE3E681F3FF5850EULL, 0x7388EA365C7BC2D0ULL, 0x9CFFA021A2A873CBULL, 
            0x72779594BC80D937ULL, 0x1892104AFA2E8FFFULL, 0x2DB4CBE0684B35F3ULL, 0x68938C227739051BULL
        },
        {
            0x9480511ADE58EA7DULL, 0xD27EE61A6535AD04ULL, 0xF60454AD693317CCULL, 0x3A815E9B65AA5E17ULL, 
            0x1E49A80F37C1D4E1ULL, 0x07A82CF160D04247ULL, 0xD503E51C06704988ULL, 0x621144A4827895CBULL, 
            0x89FE795A0935E4FCULL, 0xA448945607232FECULL, 0xF83FD8107FDA8A81ULL, 0x1977B5D17FB908CEULL, 
            0xE552EB5EDB4FA610ULL, 0x994B2624A5ACDAE1ULL, 0x0C5F5CECA814737AULL, 0x35841A703AFC76ECULL, 
            0x20CE52C04562B49EULL, 0x77EB83BB6FFBB607ULL, 0x6AE00CE9889E9C19ULL, 0x71297A39144C7E3DULL, 
            0xFB6307557F300EDFULL, 0x8A790AE6D4BCAD6EULL, 0x1AF4028D17B79B36ULL, 0xA0AF1E7C8B454B94ULL, 
            0x7FA37A432C9EF7A7ULL, 0xDC546C843FB9BF8CULL, 0x9C9568E5A0AB0659ULL, 0xB26A99F6AF905C85ULL, 
            0x6BBAE6155FBCED47ULL, 0x63F10FA6DDDC33C6ULL, 0x7D14CD24393DBC10ULL, 0x70CBBBC7818FCD00ULL
        },
        {
            0x62F4BEBC136F5963ULL, 0xFFAB10D91DD8B386ULL, 0x2B7BD5DDB2DB2207ULL, 0x1C98C51145343DDEULL, 
            0x364138ED449FB5CEULL, 0x41A347F941971175ULL, 0x29E7DE50BBDB9C9CULL, 0x62C3D2B861A200B0ULL, 
            0xB1230B64B5DE993EULL, 0x822301C5C2D12C40ULL, 0x4F4F4A6D4AA6DE25ULL, 0xE6A8C791AC5E1B12ULL, 
            0x6D81182DA4BA63A8ULL, 0xA2CCF1F6AAC503E1ULL, 0x28958EEFE50F94D8ULL, 0xADA9D1A441588BBBULL, 
            0xDBC1FE5F0C111577ULL, 0x954030A41B1A3F10ULL, 0xA0B4FF94C6BE72A3ULL, 0x2221DFC813799DF8ULL, 
            0x8BA7A94DDF050469ULL, 0x4C8A27C6F266C8ECULL, 0x6E3C16DB8FE30092ULL, 0xB86B4B0ACF510A1AULL, 
            0x26BCC24527B12481ULL, 0x16346F3BD1A6B37FULL, 0x57E1746EABA87EFAULL, 0x2562AD8D0D4E4568ULL, 
            0x67C82EAD604BA1B0ULL, 0xDCE344594D0DA0E3ULL, 0xF11E276A32B26EB7ULL, 0xCD40B75C4C29E6D5ULL
        },
        {
            0x71DA39D149813619ULL, 0x8C8B4ED29C93C749ULL, 0xFD10B4B858B11416ULL, 0xCCC5FCD8A36A3805ULL, 
            0xC366B5DA41887B34ULL, 0xC6E433665A8570B4ULL, 0x9759C3EF6C61C341ULL, 0x30618F40C8C99A5CULL, 
            0xC79CE6F0B0BAFAB2ULL, 0x3AA65566CED5FFA4ULL, 0xBE5203CE8F72FBE9ULL, 0xC33EFFCDB97D0456ULL, 
            0x6B725847F8B2FA9FULL, 0x07CBE2A45048579CULL, 0x2CA3DECA2B0763C1ULL, 0x8ED1CCCAE2335CF3ULL, 
            0x311844A006EF416AULL, 0x7209D2ECD5F8B079ULL, 0x5F24BDF1809EBEE2ULL, 0xD28B38C02CA4AE06ULL, 
            0x90FA93E918D42BA3ULL, 0xC47CBA122BA3BAE1ULL, 0x33086260F7715623ULL, 0x62FE3F28F24340E5ULL, 
            0x07A8A6F5A927E943ULL, 0xFF53EEB74F3C4A72ULL, 0xC4C219AADA1E2C63ULL, 0x214D302629572B46ULL, 
            0xB31FA6D7761AD390ULL, 0xC78AD7118CAEFD38ULL, 0xD2EF932435B9E1EFULL, 0xA75D59CC553BDAC1ULL
        },
        {
            0xA08452AC9B4FC2FAULL, 0x182128E152EB9081ULL, 0xE19F60BE4881565EULL, 0x9C4C7C5C085FF931ULL, 
            0x74853215AB55FFF9ULL, 0x236C2D57C877C51BULL, 0xD1E2FA98661ABB4AULL, 0x5FDA6ED2D997C41AULL, 
            0x7D2A79B85306E58CULL, 0xF03B3C05462AFBEAULL, 0x1172ACBD8654EDA1ULL, 0x26EBBBA49DC7F571ULL, 
            0x752C6A46B145FBEDULL, 0x96E897034F24EC57ULL, 0xC4C58F0262200F4CULL, 0x3FECD77B080EE2CAULL, 
            0x1231E0E019139872ULL, 0x20571F0D8BFB1924ULL, 0x9F312649B228D518ULL, 0x142220A510A22338ULL, 
            0x1BFA7D591DC42CABULL, 0xD935049B42DBABD2ULL, 0x4D7BE552B9CBD7CFULL, 0x868EF568243CE82EULL, 
            0x4605918A229D5F64ULL, 0xDD5C9AC67412BB3DULL, 0x318656778A1337D9ULL, 0x56BCD94844B425F3ULL, 
            0x90CD2063F0C5FB13ULL, 0x8D8B2CA6F6292366ULL, 0xEEB0AEB29C47A989ULL, 0xF099BF8538BCB128ULL
        }
    },
    {
        {
            0x1ECE0C317EA34721ULL, 0x9DBF60D7893D961CULL, 0x2E7FE6C4B67B0096ULL, 0x946FD90A67C47D78ULL, 
            0x5757E06381F3C1E9ULL, 0x49B76BE93DDF4DD2ULL, 0x7EF29B70A16CD867ULL, 0xC0A1CF13ECA1932DULL, 
            0x318D3F3E50061874ULL, 0xC56382AFFA2E6B76ULL, 0x82535E92CABE7843ULL, 0x1A2FD3D187BC2D77ULL, 
            0x67DD4FAEB2A880D3ULL, 0x509EE9CE1C44F53EULL, 0x4F02189BD10F6492ULL, 0xFE0CA7563538247FULL, 
            0x3671F72C3F20DB08ULL, 0xFA75ECD5CBA7C3AAULL, 0xFF524514ED674543ULL, 0xEDD00DD6AF6FFAA5ULL, 
            0x0F9021A8E9D4F279ULL, 0x0401098E276BB770ULL, 0xA8A523D82C167163ULL, 0xF684EA61B1BC3086ULL, 
            0x948A2D2A76B85CAAULL, 0x334BE7F8A74BE042ULL, 0xAE3CA5A1C7E57583ULL, 0x6F8A6161994140EEULL, 
            0x9137BA0D9747E075ULL, 0x4A2414D3D3D9DEAEULL, 0x0C2B7460204CD27BULL, 0x46338962C25FE7F4ULL
        },
        {
            0xD0AD9CD41F39A4FDULL, 0x31CB4C76B8A4D181ULL, 0x67B9412BF571D5DCULL, 0xBC4FFB30D3558836ULL, 
            0x76536E9EC8737EB6ULL, 0xCFF8C11C57D86402ULL, 0x27704CFE5B4AF744ULL, 0xFDFA982270F00734ULL, 
            0xAF81D50671583E26ULL, 0x2A3378BB3B339CA3ULL, 0xE1490D00FE0933F4ULL, 0x38F21F18C60ADDDAULL, 
            0x439F7F3E031E2C33ULL, 0xAC67C0AD0295DFECULL, 0xE4334A122A164211ULL, 0x8B1EBCE756C2E34BULL, 
            0x5578914AB2ABD009ULL, 0x39267F3D6626414FULL, 0x593D48556AAE55B8ULL, 0xF25B856FCAC7D310ULL, 
            0x140A0302077C8431ULL, 0x0218F741750B75CAULL, 0xDD10F3C39B7277EFULL, 0xA28B212D6389B443ULL, 
            0xBC1C7DD90CF78CE7ULL, 0xC1A280161AEC6C6DULL, 0x4408DDA4F2DC52A3ULL, 0xF3240E986FBBEF41ULL, 
            0xF0EF9008E30C2D17ULL, 0xEF894FB293EC117BULL, 0xFFEE26374D971DEEULL, 0xE5CC872D576A55A6ULL
        },
        {
            0x6B58BE286EC83430ULL, 0x3E3FD4EB94273816ULL, 0xFA8963C6000F1CCEULL, 0x55C23757A2D4D047ULL, 
            0x3ECCEFB3CCC1BCFBULL, 0x9B31A558A4B69B28ULL, 0xF77FD9157E95BCB1ULL, 0xAFE1F09C84C410B9ULL, 
            0x07A18A989A2AD407ULL, 0x1C1472A7AA6D40C4ULL, 0x0566E868B74016F7ULL, 0xDF42B1BAC955C901ULL, 
            0x7F854DFA9B44ED23ULL, 0x11DFD926E017A539ULL, 0x0B772437D2265E1CULL, 0xDDC4D32D6BDF7ABAULL, 
            0x8639F9DA2502F75FULL, 0xC0A441866D608C43ULL, 0xB30FDBDD11879E61ULL, 0x931C0E144632C19FULL, 
            0x3665E6B4D5E5DB68ULL, 0xFC2CF12392893C21ULL, 0x5D3D998D4A2B45E0ULL, 0xC4633CEA33224FD8ULL, 
            0x5921B05DEA1E599BULL, 0x1E43EEC4F714C168ULL, 0xB8EE7F39C17EF4C3ULL, 0xCA69AC9F85409622ULL, 
            0x89789A77A6255017ULL, 0xC0857FD5705CAD89ULL, 0x4C3E76F624C8A148ULL, 0x0765D16570F5527BULL
        },
        {
            0x80C8EE47948B83ACULL, 0xDB6E225109BF7557ULL, 0xB4AD6D48416A8E1DULL, 0xE0D27A52ECFC3B3DULL, 
            0x59E17F89D7F78AA0ULL, 0xBC464B157DCA8232ULL, 0x894BE534F99441DDULL, 0x5EECE065EB379228ULL, 
            0x42A05DE81DCB7534ULL, 0xB7BCC8E55C5D9536ULL, 0xA83031C076964BE1ULL, 0x6AF7581608F24AD2ULL, 
            0x753CDAD95C75AF65ULL, 0x3715DB4982DE6935ULL, 0x68CC828CF4D7ED00ULL, 0x43F7B39703805B69ULL, 
            0x0F171F755A4F27C7ULL, 0x0E40A62CCD7A65A0ULL, 0x3D3F5929D300A5BCULL, 0x4A59F7C830D002AAULL, 
            0x03EC64F05DF8B7F6ULL, 0xE6F2D60DD3BFA8E0ULL, 0x73904EB1272F1C2DULL, 0x38B4924D6BB939BBULL, 
            0xA60C4280FD323646ULL, 0x43B5F3739B150664ULL, 0x832804A96675DB8EULL, 0x3E7682AB2F30BE50ULL, 
            0xBA411399CC8B9AF1ULL, 0x112E9CFAFCB87976ULL, 0xEA7C437C8B4D1EF4ULL, 0x2A0746AEB62EF59BULL
        },
        {
            0x733511D3E3B12EE7ULL, 0xDF081F772526CDEBULL, 0xC5DCC5BE405F30D1ULL, 0x203994ADC1CFE191ULL, 
            0x33BE5E97F44B532AULL, 0x4B1275427F8DB7B4ULL, 0x5A0CC3837F3C4B4BULL, 0x1511457397EC9361ULL, 
            0x2B5A6B0108E0F7AEULL, 0x46755BD69D32B078ULL, 0x0C663C808F0BB6DAULL, 0x03F42CA645CCB5ECULL, 
            0x6207BCF7BADDF0F4ULL, 0x194F235DB8ED92F8ULL, 0xB8746F4AC14BE9D4ULL, 0xD3C35A2E4997D84BULL, 
            0x079880032829CEA6ULL, 0xF1CA91F053579BB4ULL, 0xBD6348E79CAD16F2ULL, 0x68469D189B9F1EE3ULL, 
            0xFA8CB124EF8FCB51ULL, 0x0420922A1F641564ULL, 0x80FDF12187683F43ULL, 0x97A90116D79C66EDULL, 
            0x7DBD0E429F43DB48ULL, 0xB69DC4FE25FEC067ULL, 0x7D810DB65125BAC7ULL, 0xB3AEC00E948AAD3DULL, 
            0xA1AF54B003B9C61DULL, 0xB3C76225E65FE7C0ULL, 0x901A01FA6C2A7E75ULL, 0xA74932AC65EC358BULL
        },
        {
            0xB85E75B3AAC37862ULL, 0x3D1E64658CA70973ULL, 0x20666EEE4CB6CDE5ULL, 0x3C560AF64D411D2DULL, 
            0x2D709E06CDBD09F0ULL, 0xE8E20E6BA1D8C1C8ULL, 0xC78264A4F816B1FAULL, 0xD2FC7C3B47A275B8ULL, 
            0x8A6FAE49AE1460EFULL, 0x8B8C361E6126A475ULL, 0xDDAC8C9741C481E4ULL, 0x6ECFC04E9E7C0191ULL, 
            0xFD8EAE2ED81A99EFULL, 0x324F0A3E844A8FB8ULL, 0xE3B64CDBF0851060ULL, 0xBCECEDF51CD9FE9FULL, 
            0x34A5F82BA15E475BULL, 0x6AF04E30BCE4212DULL, 0x010DC53192F3FD0FULL, 0x219E87FA59545C8EULL, 
            0xF1E730946FDED27FULL, 0x8C1D134EC550C168ULL, 0x7B4E94D3C7A356E8ULL, 0x888C90A250184E34ULL, 
            0x83795B7362B4D55BULL, 0x108B434A3321B406ULL, 0xAA9C2616E0CDB305ULL, 0xE43232F16A9B38BBULL, 
            0x778216A9F52F38F0ULL, 0x6E7E435E6632DF2DULL, 0x1E24B564DA6DA3D6ULL, 0x4CC218DFFC4B2245ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseGConstants = {
    0x4459603AEFA7EAECULL,
    0xCD944F07F9EB515EULL,
    0x18350B2DA631BA80ULL,
    0x4459603AEFA7EAECULL,
    0xCD944F07F9EB515EULL,
    0x18350B2DA631BA80ULL,
    0x1896864A434A5A9BULL,
    0xBEF8EDE20EFC74FDULL,
    0xE0,
    0x82,
    0x9A,
    0x72,
    0xF2,
    0x80,
    0x6D,
    0x4B
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseHSalts = {
    {
        {
            0x02B728B4CDB5731CULL, 0x0823AF1A6F115030ULL, 0x82EE6552B7FF9668ULL, 0x7E3FAAE20E635144ULL, 
            0xAC050FFCC6BE2250ULL, 0x57085CCE8F02A8D6ULL, 0x56144716A457CC10ULL, 0x276F010292BAB43FULL, 
            0x13C8576F4393709AULL, 0x45C1820B8E899996ULL, 0xC9103C2486C34505ULL, 0xF6287B9A1826C20BULL, 
            0x31C43C8A3795DE0FULL, 0x014DEC99CAB3BCBDULL, 0x125D4D908E370DE8ULL, 0xE465257E7167BEF8ULL, 
            0x67869C37983ECF7AULL, 0x410730D5BB2A7BD9ULL, 0x01CEA604119001E4ULL, 0xEC291421B74543F7ULL, 
            0xCA8AEDC2C9C1D0E2ULL, 0xDE03ED2149178E75ULL, 0xF1F1C5264048BBCCULL, 0x6BE92BB640176F97ULL, 
            0x709D98D9B3D054AEULL, 0x3A8B283D7C3A7038ULL, 0x53D89D4EDA289AD7ULL, 0xF9E23E45672E6C0FULL, 
            0xEE09CB4BDAAEEB6BULL, 0xAEA4C19358E1AA58ULL, 0x98BB180447FAC675ULL, 0x324624BEA51605A3ULL
        },
        {
            0x2416DCA2B4EC1932ULL, 0xF7EB29261DA070ACULL, 0x0374F601E21D6792ULL, 0x3518263371EF7F51ULL, 
            0x2A0B829CD17C3826ULL, 0xDDEE80A7213B8003ULL, 0x4D408372D9ABD5E2ULL, 0xD1165C85C6276598ULL, 
            0xD536C1B03412FAF2ULL, 0x374E74D17541C73BULL, 0x4F13D56F6319B8E6ULL, 0x6BBACEF6A91318D1ULL, 
            0xD86F78322D758A87ULL, 0x5DFAEA73D2500EC2ULL, 0x854F3FA1E7E80872ULL, 0x7E146D5C5BE51565ULL, 
            0x7F1280C3D48DD52EULL, 0xE68065481B623A68ULL, 0x1135D83062346E73ULL, 0xEC5FE45F54CC2624ULL, 
            0x35D23082F5A05EA1ULL, 0x4DF945039C2DE4D4ULL, 0xC69D4C2B85EB759DULL, 0x2E1CFF1B5A4B99DAULL, 
            0x9D15E0AE27CAEFF7ULL, 0x7C5DE2D72AFFAC24ULL, 0x3BD7350E20748CDEULL, 0x2E5290A615755B79ULL, 
            0x7D62563EF38D7564ULL, 0x35618FC81D1AC494ULL, 0x5B052859DA1EB774ULL, 0x37531CDE03AAA7CEULL
        },
        {
            0xEF74DBD0F2804E6CULL, 0x8DDE90E869D832BAULL, 0xEED18D10AE48DEF6ULL, 0xECEF4A328D94157FULL, 
            0x7D9C4D5B936840ADULL, 0xC82441595ABF323FULL, 0x8A1C382797A26D52ULL, 0xCA46D3A6A390142EULL, 
            0xEF15A432670F0F7CULL, 0x930410307522EA42ULL, 0x31DEB1546313AE2CULL, 0xF4FCB20997965A6BULL, 
            0xA648F0DD63D74EC2ULL, 0x784C126776499250ULL, 0x87C99504E1AB4F85ULL, 0xFFA8065CDA7369D6ULL, 
            0x9C2537F3E4AA4653ULL, 0x53AB74E8ABEB3E15ULL, 0xD556EECEE355280AULL, 0xC1EAA91DF1EDA37CULL, 
            0xEFE92BC26BA29205ULL, 0x99B965E5BCD9A2BBULL, 0xC9DE318B353CBAC2ULL, 0x27664836741E0358ULL, 
            0x3BEDE99D093A6B5BULL, 0xB4119D0230DCBB1CULL, 0x374B27B1D6EE9A10ULL, 0x971D7B0351E8F428ULL, 
            0xF5433D0F8A1D9BF0ULL, 0xD05F4D6F423A9218ULL, 0x9C268067B1E44B89ULL, 0x4B9316CDC25DC08EULL
        },
        {
            0x567FA62987D0614FULL, 0xB4C7F4BD7100A902ULL, 0x463664F6BA1A52A5ULL, 0x71F30737F52DFBCDULL, 
            0xC90175D8E4E64503ULL, 0x7D71E8F712C75D52ULL, 0xADB2734591E0BB1DULL, 0x680F4191BB46547DULL, 
            0x1B7CDC9DDBB5EE36ULL, 0xAD299E76BD033F4BULL, 0x844AC608DE8F5666ULL, 0x2BDB202D7F5DE0C2ULL, 
            0xD3AE563C411C307EULL, 0xFAA9DE95B733D4F7ULL, 0x87A36BE408FF8C01ULL, 0x61D9A42A995A19ADULL, 
            0x8280F9572815B6E8ULL, 0xA23435D2C3F3E652ULL, 0xD201C4BB720E2003ULL, 0x23D2DC03FE5B8CC7ULL, 
            0xFF0DD08BE5AAE6BCULL, 0x912864D774EB6580ULL, 0xDBC814CFB318E01EULL, 0xAC3D25FD9666157EULL, 
            0x247641A7314787EFULL, 0x77BB188515B56C85ULL, 0xBBAEC4C825DA9CFFULL, 0xC8E59DD06DFAE6A5ULL, 
            0xA454DB6187940A0EULL, 0xEBDBB3F82E2C305AULL, 0xF2AC4F6908EECDD3ULL, 0xAAD94618FA789A49ULL
        },
        {
            0xD6FB5794E8D1F17FULL, 0x7CCD5191A2518CC4ULL, 0xB5A3640908B62CBDULL, 0x0F6E2528EAE36DB7ULL, 
            0xB118059C4CADE347ULL, 0x24C8DE80EDA18019ULL, 0x739244E05BAA9348ULL, 0x902D168BBCEB4931ULL, 
            0x342D4824539DAB3FULL, 0x319F2CADC6C19DB8ULL, 0xE0478035A2019655ULL, 0x9A4128E386021219ULL, 
            0x2D067C63EB772AA8ULL, 0xC2A37CE6EC028E7AULL, 0xF8E241ED8837981BULL, 0xAA590D0225D0F827ULL, 
            0x70C0966020D2858BULL, 0x892381EB1243E2EAULL, 0xE57AE0A245095E02ULL, 0x37B73BDE5170411FULL, 
            0xEDAC10096839B4D1ULL, 0x47CB75A8E4C596A0ULL, 0xB07C6840BA51A4C8ULL, 0xF9D64842DE019A99ULL, 
            0x794B62BDA049614BULL, 0xC399022B972C8C7BULL, 0x74EDF3B54E580C69ULL, 0x9848027FACD15F02ULL, 
            0x91CA6D2930A044D4ULL, 0xDC55DD5284A5B91BULL, 0xDE370D86549FEE54ULL, 0xF120AE89538C0009ULL
        },
        {
            0x1874E9B6801ABB38ULL, 0x10388FD5272FA54AULL, 0xB564E69820DC4AEAULL, 0x8F68D4BA3E608074ULL, 
            0xDDEF80BC1873DB67ULL, 0xD010159B72DA0813ULL, 0xF4D24196164BE43DULL, 0x5A4BC9983778102AULL, 
            0x86F110CFDC21C532ULL, 0xA3F26F1C2425D8A6ULL, 0x2C8E1C36D24D01DEULL, 0xDBF13809A91DC49EULL, 
            0xC326E1B59C530CA3ULL, 0x35756AA8C3485C23ULL, 0xD628A60C4BED6A48ULL, 0x2E5A07A0AE41C5BFULL, 
            0xA5CB573534E48E84ULL, 0xE9B5E95FAEF59441ULL, 0x541A30F859EBF543ULL, 0x2EB1FF1DF316F036ULL, 
            0x604D7122D95FF20AULL, 0xA4FD5E89DA96A2C0ULL, 0xB13E90CEF92479EEULL, 0xD9E755538908823CULL, 
            0x2486990C2CF8E6ACULL, 0x8955A6ED5E48E7B7ULL, 0x4362839BA382573AULL, 0xA47B8E3A28E8CAE5ULL, 
            0x320B171558A93E8BULL, 0xB398B647EDB17E8BULL, 0x9DC1B7FA4654C30EULL, 0xDC3F77133DAC474CULL
        }
    },
    {
        {
            0x95AF7778F1739FD9ULL, 0xA78252C1459BF69BULL, 0xD18CCFE6755FC730ULL, 0x5BF4BF50DE472F9DULL, 
            0xB5732AEC9AB05B97ULL, 0x550399F2B6EEDC22ULL, 0x86512846CCDA5F05ULL, 0x481AA3A73253B4C6ULL, 
            0xE294D152236BA9AFULL, 0x9B4B3C9C7FAAF4B1ULL, 0xCA0BED269E75C82FULL, 0xAD7072DFDFFB2D6EULL, 
            0x05923E282C52A6E8ULL, 0xF209BBE6EB6B8E82ULL, 0xCDE7D8F4D5462B65ULL, 0xB7936CF0490E3005ULL, 
            0x42C650DB263CDAD5ULL, 0x19FAF44E74FD0948ULL, 0xC96925920F48CB19ULL, 0x43EDADEABAC11897ULL, 
            0xC9F0FF80C496BBADULL, 0x8AC685A9AA9BABAEULL, 0xDF187EE9C8E1A6D9ULL, 0x8F5CAFD7B8A1A529ULL, 
            0xA3B5979126C7477BULL, 0x22FC5626C54241D9ULL, 0x5E59514D448A395FULL, 0x17465FFA257705F2ULL, 
            0x8A3E4C26F061D112ULL, 0x9E2907D9C4E2E6AEULL, 0x98E652686B5F5EB7ULL, 0x7F04F0924391B08AULL
        },
        {
            0x68BB6B28AEF5CB8FULL, 0xBF77E65DF45EE55FULL, 0xCAF76B9A8E70B93CULL, 0xE961126EE9191BCFULL, 
            0x8C86202B63FA3E76ULL, 0x9E5EDDD20E2AFE83ULL, 0x2462939E3CCCB03BULL, 0x081CE0458EBE05DCULL, 
            0xB6CF53CE01583E0CULL, 0x648409AD442AF88FULL, 0x0007A7F4544588C5ULL, 0xDE2F11A6CC0DBFC2ULL, 
            0xA2F6022FF20441B1ULL, 0xE373E77088438FEBULL, 0x350C6A09B5C3370FULL, 0x43F82F41CDA77390ULL, 
            0xC1E8325F2DD10756ULL, 0x8760EE213592E2ACULL, 0x84E9A1FD3DE7FF97ULL, 0xF25C14A927D2E562ULL, 
            0x446C2A6E37330410ULL, 0xF84B84F82C1FBEB6ULL, 0x2C2373AB2069F07BULL, 0x862EAE70F69C5631ULL, 
            0x05A24A3223F995EDULL, 0x151E9F4ACAA3A4D7ULL, 0xF8D77CAA07676341ULL, 0x4DCAA31DE099BF6CULL, 
            0x8F945100D2A8720BULL, 0x841C36850DE9D89EULL, 0x1F8F9B1A90AEA406ULL, 0x89EBDD93897A45E3ULL
        },
        {
            0x8711DB6491E30B4DULL, 0xF685101D71A4EE93ULL, 0x6A8122F0199B64ACULL, 0x2B7DDC59537E9C4BULL, 
            0xAC96273B85C7D6C2ULL, 0xD8C06D15E61BB388ULL, 0xB41448435EF22E72ULL, 0x1D98169C139F5D4CULL, 
            0x95BF68CD51FD27D3ULL, 0xB1EE67957FB65366ULL, 0xB2702973013E9182ULL, 0x2E9F6AF4828001EDULL, 
            0x6FB127C30A297AD9ULL, 0x967A1B0A346B052EULL, 0x31B68AF65D4358BEULL, 0xC4358D95C8E35F87ULL, 
            0x0BBFAB0DCCFD54CDULL, 0x831596DF3FCF63ABULL, 0xE59FBFED6076F618ULL, 0xA5127CC26AEDD310ULL, 
            0xB033A22E39CEF129ULL, 0xC1993B5D0794D780ULL, 0x3304BEC86328CEAFULL, 0x90BA99F5CA2ABA8CULL, 
            0xE6E5E89A23DFE30DULL, 0x820C5DDC990C2FA6ULL, 0x8C3987F1A050A206ULL, 0xFD3100A6EFB52D87ULL, 
            0xBF78F5CAFD7A21B5ULL, 0x4FD61B4D1145CC85ULL, 0x656A1C3B71898754ULL, 0x6758D4543F4A82E6ULL
        },
        {
            0xC04735B8FD53A2D9ULL, 0xB22123BF5F8D4DEDULL, 0x4F746E4379896E5EULL, 0x26C6650775E7E725ULL, 
            0xB5BB7F047EA5FD94ULL, 0x96C7645457BAA53FULL, 0x67F064B86B07D00DULL, 0x670B86283FB20876ULL, 
            0x56FEF77B4203DC3FULL, 0xBAE9F231DCB3711AULL, 0x656ABD959C3F332BULL, 0x902EFA40887041E9ULL, 
            0x840C4EAE2CBC6172ULL, 0x8B3DD4543965B522ULL, 0xAFD1323B86D07115ULL, 0x748961145511266AULL, 
            0xB3D42ACB299B4C03ULL, 0x0684086F97C0E939ULL, 0x086946D92B05DDFEULL, 0xD598B4255F101363ULL, 
            0x74F4D4E8A2C60ECBULL, 0x310EC589C17B48B0ULL, 0x3C8718B81DBFF125ULL, 0xC8E5B00E130ABDBDULL, 
            0xB829145EA525DC62ULL, 0x7F3CC1917CF60BC1ULL, 0x4C099DF11AA40ED3ULL, 0x35C17F1F0969B3D1ULL, 
            0x437858B42EBAAF6BULL, 0x51C2246451230A81ULL, 0xABFDE71936E6FC82ULL, 0x5B6A748F8AD96575ULL
        },
        {
            0x801A74883E3C49B5ULL, 0x14D6EABD5E5DD015ULL, 0x4050FB767EECF085ULL, 0xFA3C481EEDA538C7ULL, 
            0x651D7468373E696FULL, 0x8F11EA688683E6ABULL, 0x30F1A1358F6E6C88ULL, 0x8CDED42C627C3F44ULL, 
            0x40791C06E6073198ULL, 0x4AC1F59821FDF0ADULL, 0x0818B9E1AFF4BB94ULL, 0x277DD2B90364DCE2ULL, 
            0x5BB80335F9D2B09AULL, 0x6F52F7400E28BD88ULL, 0xC886D961F0053664ULL, 0xE66D00E0BB5CF9D1ULL, 
            0x49690B43F8B24D4BULL, 0xB0597ACBD94F2D56ULL, 0x50F691471E91473BULL, 0x61F069B8A0036689ULL, 
            0x03F4A257EF495864ULL, 0x6B82646D6E929543ULL, 0x811C67A762545DFAULL, 0x086767710D4D84BEULL, 
            0x2B9CEAA444CDEEACULL, 0x5F9ADE0540C95BCCULL, 0x0D0BD9EDB086CE62ULL, 0x8FA96FA4E9E6CF31ULL, 
            0x0900D56B08AD08E4ULL, 0x1C570715D127B2E6ULL, 0x006C9D35CEF736E4ULL, 0xDAC983DCD388BC6EULL
        },
        {
            0xF1227F9F72D7F9F0ULL, 0x40CB2939E8CAADC6ULL, 0xABABD17F47625D92ULL, 0x16B970CFDFB1DA53ULL, 
            0x837A4E52A8D04B76ULL, 0x08A7C7A2C7332CDCULL, 0x409CD6A53039034CULL, 0x3A35ECCD435C7A7EULL, 
            0x4D8C3714C33D498EULL, 0xD4E6472DFD70F94AULL, 0x90B8727016B58843ULL, 0x3F7D4808E84A5602ULL, 
            0x71AA78322B097D8BULL, 0x0066C57E9EFE9A43ULL, 0x014AA7DFAAFA92D5ULL, 0x7480D4D22C12FD48ULL, 
            0x906DD64C16226453ULL, 0xBEB75AE353F53ED0ULL, 0xCB2A6B1C170F0636ULL, 0x74A2B81F5813E1ECULL, 
            0xE35D97F94F9A5F7DULL, 0x12606EF30C869071ULL, 0x53A9389D27C098A5ULL, 0xA9C34B84F4DC45F8ULL, 
            0x3B1424F41BC01AFBULL, 0xB4753ECA78B353FFULL, 0x8ACF5CD6548B19E2ULL, 0x9E45ACB2C38AA4B5ULL, 
            0xD94AC6316F8C2023ULL, 0x330B022106B423D3ULL, 0xE633D11BAFFF331BULL, 0xC2A79E3F35D4C2D6ULL
        }
    },
    {
        {
            0x97FEE219D4C19B79ULL, 0x717E924BAAA32154ULL, 0x0F9A50EA0500B89EULL, 0xD5A984F16B65BEEFULL, 
            0x3E75B30B310E131EULL, 0x2FCEAFC2832E0F17ULL, 0x2B45470F2B4883C0ULL, 0x35CDEBA0BF7929FCULL, 
            0x8551F00B9F2E9ADBULL, 0x4F36BFD6DD08A4FFULL, 0xB38791E51CFCE610ULL, 0xE7E5EB50AAA66A36ULL, 
            0x3B1720FF8AF4D803ULL, 0x6FCABB8A6D7F8F00ULL, 0xDAD8F7C90D26A391ULL, 0xD452E1C770ACCCB5ULL, 
            0x538BE0BD26194BAAULL, 0xBB031B416DDD5BCEULL, 0x5EA33B920B2A73FBULL, 0x5C22915A90A03033ULL, 
            0x035F2A27144B5C7FULL, 0x096B95148D5ECFFEULL, 0x2A66336492B1F432ULL, 0x6CD8C1BC85EA5BFFULL, 
            0x1DE81298256A0B5FULL, 0x64FAC237743BA96FULL, 0x780037F889C0BBF8ULL, 0x9BE01C0B8E10BDA0ULL, 
            0x414215EB89D6DD73ULL, 0xACE6A087B630223BULL, 0x4587038A93B74D8AULL, 0x7B0FAC6B95B09DFBULL
        },
        {
            0xD5B02523ACC78257ULL, 0x7C6B909F09495D1CULL, 0x00729ADF0032B05BULL, 0x1F49B593C8AB0706ULL, 
            0x8E978822D1031665ULL, 0x2BA65986A4D83309ULL, 0xF95D56CA69C9ECDEULL, 0x38EBA068CF08BED9ULL, 
            0x5137E3D7AD5D413FULL, 0x18AB6E6233584B19ULL, 0x882636EB1C521893ULL, 0x99A352553E52D267ULL, 
            0x06091361FB2CC9FBULL, 0x52C2ED4A7B15F331ULL, 0x0D5AB2438682F2CFULL, 0xA628F81F093FB36CULL, 
            0x7695BD6ADF3D91E1ULL, 0xCD9F2C813BCF47DAULL, 0x481BE874363ED1FCULL, 0x3DD188789C164E44ULL, 
            0xDAF8319721EEF839ULL, 0xA948AB7C75B499E7ULL, 0xC6A88D0F22C14FA2ULL, 0x0F000FB897BAA165ULL, 
            0xA3397D6FBC9DD172ULL, 0x292B475E8B225F98ULL, 0xF005B14E05A08E03ULL, 0x00E3252AC7BBD660ULL, 
            0x6F69930842751EDBULL, 0xF8CC6E8C3776C444ULL, 0x25E2D214219AB8F1ULL, 0x55FF60760AD075DFULL
        },
        {
            0xAF1699C6401932C7ULL, 0x6E304D3A8950C137ULL, 0xDFFE30F6EF8F5E13ULL, 0x6B14C57D9B4AFCE4ULL, 
            0xE2F41D267AEEFD5EULL, 0xEE77323841798E04ULL, 0xA96B4D944EC342E2ULL, 0xC4C3D88CCBA3C27BULL, 
            0x0D0FC2C99D1510ACULL, 0xED44213FA6FF6209ULL, 0x2228F7224C123E22ULL, 0xD6AB2B5106F8FD67ULL, 
            0x3C3854009737B6CAULL, 0xA1083B9910A98603ULL, 0xB5596A9AA9B27680ULL, 0xED9742A8153DEB12ULL, 
            0x12DFF65D8117B368ULL, 0x224F19BC17464CDDULL, 0x6579BA0F61EDD5BEULL, 0x1378AA1AE6FC0B89ULL, 
            0xB5757D1123B0DF40ULL, 0xF6D99C268532A167ULL, 0x9340DB13B4E3547FULL, 0x43C85A8002E6E92BULL, 
            0xF4EF05EB3A884109ULL, 0x2659CF920C211A20ULL, 0x02B981C2B4250E4DULL, 0x05B27AD9B60950C5ULL, 
            0x78C2F54A9A276C7AULL, 0xF3BC8AFE25A2E548ULL, 0xD87EF1B01AB62C82ULL, 0xA1CB9793F13109C6ULL
        },
        {
            0x7652AA2000DABDF4ULL, 0x015C6F7D4765434DULL, 0xEB4C6603FA2931ECULL, 0xC07342939C7D272EULL, 
            0xCE3F6296A28B7FD6ULL, 0x871FEB20A02CD5A7ULL, 0x6EFD14393DB0E1A1ULL, 0x14DA5F72FB79F1B9ULL, 
            0xF5BB6F973CD9D9B7ULL, 0xB737238B4A1CC755ULL, 0x8014BA73ED4D9603ULL, 0x4800B67008C990B0ULL, 
            0xF3C7DA7AF6C7EA31ULL, 0xCACA5021C7496625ULL, 0x0B0EB8F9EBA6BE72ULL, 0xCAB9AD7F2F71E711ULL, 
            0x12E6CBF32374CF17ULL, 0x85016E5E40C78446ULL, 0xA67B2A21180A464BULL, 0x0C4BD1A87CD05FB6ULL, 
            0x31A46D024D86405EULL, 0xCC465448A4D08067ULL, 0xB14491D01BE3DBAFULL, 0x7E2BFC34092FFAFAULL, 
            0x78A0268D428DF1D2ULL, 0x32D60E837C3A8212ULL, 0x8913B3F1BD839752ULL, 0x9F633DC44DAAD490ULL, 
            0xBA1A4BD62E8F75BDULL, 0x4F93BB068BE7F591ULL, 0x763F6049BEEB6E2DULL, 0x20B2798BE183D468ULL
        },
        {
            0x2A7FE9CF35CC6823ULL, 0x2CE0470C290B923AULL, 0x320D82DACE7FB667ULL, 0x8C57C432E77C5815ULL, 
            0x53BB8BB34814F291ULL, 0x135D09A778D12675ULL, 0x5E6C6C459193871DULL, 0x468C3FACAEC00D91ULL, 
            0x7761788685A9B518ULL, 0xBE21FD1404B2B065ULL, 0x509296BBE261CF47ULL, 0x92E2569A47A2C376ULL, 
            0x2B60193C401523EFULL, 0x14FE0B6C165F7322ULL, 0xAE62036DD926AB81ULL, 0x61DDA85A7FAD275CULL, 
            0x6C2F97515556C1E4ULL, 0x096F2B18EE610256ULL, 0x327924DB7F3926E7ULL, 0x81915A00361C725EULL, 
            0x9ABC7171F6E762C8ULL, 0x6F4F5E0C37EFA8C9ULL, 0x90AE9C32F19A3AD7ULL, 0xE34635B78806C32DULL, 
            0xB6E73E228AAB7ABAULL, 0xC3EC6C573F7CA17EULL, 0x41724A3A36118000ULL, 0xC30230E1C58D7C39ULL, 
            0xBFACC760B00FDA64ULL, 0xF36B680A21A15356ULL, 0x889DDE8EADF5B57EULL, 0x5FCDED85A63D874CULL
        },
        {
            0x24E62EC7A6190CA5ULL, 0xBFCF8061D75F48B4ULL, 0x96A4CEA8ED1197DDULL, 0x3410340D21C2F0FFULL, 
            0xE3C361460F07DC64ULL, 0xB2599C224D196320ULL, 0x59925A612075B5FAULL, 0x0B9397653BD115C5ULL, 
            0x8A3D97F975E5F672ULL, 0xF386A8353082337CULL, 0xBB64C244B4D1C9A6ULL, 0x6E25379069FBF8E9ULL, 
            0x0235F7FB920444DAULL, 0x6D0F80EAB4BFCA0EULL, 0xE3BF1E7C41C10936ULL, 0x8B07136AF9F6E993ULL, 
            0xB70E1BA54DC4B46EULL, 0xACF79FCFBF423AC2ULL, 0xA2E2F86ABC0D5FBEULL, 0xDF2ED754D693858DULL, 
            0xB6D61FB849C1DDC8ULL, 0xF922FA631D517D98ULL, 0x9025A6696829A1FDULL, 0x034AEB7752B0A1B1ULL, 
            0x52A546A99953AEEFULL, 0x1552913E2F705463ULL, 0x0FA1A8700D698B52ULL, 0x0B16B601391A0954ULL, 
            0x85D3516B75CDA2A6ULL, 0x631AEADB2D7BFCB5ULL, 0x669CB7A519BBFC25ULL, 0x32D550D46694D938ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseHConstants = {
    0x8E723896CFDAF808ULL,
    0x1225606DCC292C53ULL,
    0xF4D873F472A93DDCULL,
    0x8E723896CFDAF808ULL,
    0x1225606DCC292C53ULL,
    0xF4D873F472A93DDCULL,
    0x02724A45894ACB1DULL,
    0x7DE76FFCEBEB9AEEULL,
    0xB0,
    0x9E,
    0x1D,
    0x5E,
    0x08,
    0x67,
    0x9F,
    0x08
};

