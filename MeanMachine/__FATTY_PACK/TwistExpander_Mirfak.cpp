#include "TwistExpander_Mirfak.hpp"
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

TwistExpander_Mirfak::TwistExpander_Mirfak()
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

void TwistExpander_Mirfak::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xF1A92281B7D4E320ULL; std::uint64_t aIngress = 0x9D2B93BE4C52CEB4ULL; std::uint64_t aCarry = 0xE540A6E23D570A54ULL;

    std::uint64_t aWandererA = 0x8FE20CD3B4E09FC8ULL; std::uint64_t aWandererB = 0xB3F12C08B49E1633ULL; std::uint64_t aWandererC = 0xF4EAC24C74C43C6AULL; std::uint64_t aWandererD = 0xDD2B0F66036319A6ULL;
    std::uint64_t aWandererE = 0xB7A961806A01965EULL; std::uint64_t aWandererF = 0xF56D9E5D59428D9FULL; std::uint64_t aWandererG = 0xC71583C2CFB5DF34ULL; std::uint64_t aWandererH = 0xC6CC7C9F814DD10AULL;
    std::uint64_t aWandererI = 0xCDFDFABC385603AFULL; std::uint64_t aWandererJ = 0xC18A88420344ADDBULL; std::uint64_t aWandererK = 0x8939FCF2E5C59D26ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16539782924459748144U;
        aCarry = 17789443066011603521U;
        aWandererA = 10339269700531029774U;
        aWandererB = 12581491507197662228U;
        aWandererC = 13591233767253891797U;
        aWandererD = 16784932640453071641U;
        aWandererE = 17203554240265691173U;
        aWandererF = 13794465698052252830U;
        aWandererG = 12862815688397677175U;
        aWandererH = 12232072557065544282U;
        aWandererI = 15727374735322648666U;
        aWandererJ = 13342760520464560999U;
        aWandererK = 13288026034797959446U;
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
    TwistExpander_Mirfak_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mirfak::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x91C41A0E4F977519ULL; std::uint64_t aIngress = 0xD8E2E153E397B52CULL; std::uint64_t aCarry = 0x99F750EF161FEA26ULL;

    std::uint64_t aWandererA = 0x8DBA7452EA733750ULL; std::uint64_t aWandererB = 0x8E2D29073A9CAB6CULL; std::uint64_t aWandererC = 0x9114371FD00463D4ULL; std::uint64_t aWandererD = 0xDD9C9F65A8782951ULL;
    std::uint64_t aWandererE = 0xE6183844D0FC6AD1ULL; std::uint64_t aWandererF = 0x82D707779F440ABAULL; std::uint64_t aWandererG = 0xAEFFBB1C6AA3D90EULL; std::uint64_t aWandererH = 0x9B295FB5135BAE76ULL;
    std::uint64_t aWandererI = 0x9B2A6298B0145374ULL; std::uint64_t aWandererJ = 0xEB30C5FB577BE07FULL; std::uint64_t aWandererK = 0xBE0CC925521B0C98ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14726258935746122598U;
        aCarry = 18356805423122474306U;
        aWandererA = 12005242122722075910U;
        aWandererB = 16465580843918695524U;
        aWandererC = 11354061199412101145U;
        aWandererD = 9594726507149750245U;
        aWandererE = 12435740547375086313U;
        aWandererF = 11309982253625506429U;
        aWandererG = 15269549605399434566U;
        aWandererH = 14015245299829223972U;
        aWandererI = 15391041320553607899U;
        aWandererJ = 9982109555177220225U;
        aWandererK = 15819463161486990452U;
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
    TwistExpander_Mirfak_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mirfak::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC1D053C41D59BECAULL;
    std::uint64_t aIngress = 0xDD44237C0C0A9498ULL;
    std::uint64_t aCarry = 0x970A920197CF4DD7ULL;

    std::uint64_t aWandererA = 0xBA79B0FBFCBA6DE3ULL;
    std::uint64_t aWandererB = 0xD718CBE7D39F2A5FULL;
    std::uint64_t aWandererC = 0xB78636B2372A8AFCULL;
    std::uint64_t aWandererD = 0xD3EF9B5320BBD081ULL;
    std::uint64_t aWandererE = 0xB7F8927CA379ECC6ULL;
    std::uint64_t aWandererF = 0xE528D472B2E90216ULL;
    std::uint64_t aWandererG = 0xB8B77D8E62B81D44ULL;
    std::uint64_t aWandererH = 0xCBA302BB4763E7E8ULL;
    std::uint64_t aWandererI = 0xA9FC686B8CD0D2B6ULL;
    std::uint64_t aWandererJ = 0xE02D478DD408C075ULL;
    std::uint64_t aWandererK = 0xFAC055FCC4D07B3EULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneC, 0);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneD, 3);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneC, 4);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneD, 7);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
    TwistExpander_Mirfak_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 21 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1798 / 1984 (90.62%)
// Total distance from earlier candidates: 36343
void TwistExpander_Mirfak::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 944U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1911U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1515U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1836U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1223U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1426U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 729U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1037U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1888U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 221U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1253U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1395U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1400U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1446U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 467U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 310U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1820U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 905U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 619U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 97U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 418U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1745U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1140U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1076U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2017U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1141U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 865U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 317U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1876U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1377U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 202U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 572U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 873U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1581U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 481U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 698U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1473U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1207U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1128U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1886U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1176U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 997U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 294U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 27U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 428U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 592U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 36U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1633U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 427U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 260U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1520U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1992U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1238U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 413U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 995U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 914U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1375U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1743U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1151U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 899U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1721U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1208U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1610U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 402U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 492U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1511U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 455U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1756U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1362U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1747U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 626U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 457U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 681U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 262U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1152U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1182U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1704U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 240U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1272U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1053U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1123U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 87U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1889U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 269U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1539U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1498U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1587U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 192U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 144U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1179U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1145U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 911U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1999U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1019U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 963U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 759U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 458U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1264U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 94U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1247U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1826U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1482U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1726U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1624U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1732U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1120U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 883U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1246U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 996U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1317U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1590U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1927U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 737U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1441U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1599U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 781U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 225U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1941U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1026U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1399U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 633U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1486U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1525U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 757U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1064U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1640U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 15U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 582U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Mirfak::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xAC8EF0D47C439501ULL; std::uint64_t aIngress = 0x8CEABED79D0A6C0CULL; std::uint64_t aCarry = 0x9850CF608F43A24FULL;

    std::uint64_t aWandererA = 0xEB9BB6F131F6CFF8ULL; std::uint64_t aWandererB = 0xFDF2EB07B4E7170CULL; std::uint64_t aWandererC = 0xD9CE2B95DCD4929AULL; std::uint64_t aWandererD = 0x85641530C9259070ULL;
    std::uint64_t aWandererE = 0xB0E7A4BD9816E510ULL; std::uint64_t aWandererF = 0xA89AC33B99E84878ULL; std::uint64_t aWandererG = 0xED7C24CC9018875BULL; std::uint64_t aWandererH = 0xE050E0016930107CULL;
    std::uint64_t aWandererI = 0xC35741BF9BC4D4D0ULL; std::uint64_t aWandererJ = 0xC6757B0A9B223C5AULL; std::uint64_t aWandererK = 0xAD96539A7725BEDCULL;

    // [seed]
        aPrevious = 10343791310748114813U;
        aCarry = 14245538045283566626U;
        aWandererA = 10535282971543918076U;
        aWandererB = 14592655010403893495U;
        aWandererC = 10268953789064690356U;
        aWandererD = 14282852008904062538U;
        aWandererE = 17211716721126180444U;
        aWandererF = 10427536454264943306U;
        aWandererG = 13090187016924256771U;
        aWandererH = 9452500436469468181U;
        aWandererI = 12793081645216090955U;
        aWandererJ = 15827259966067939067U;
        aWandererK = 11535431369256818482U;
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
    TwistExpander_Mirfak_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 21 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10868; nearest pair: 482 / 674
void TwistExpander_Mirfak::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2553U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1836U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4145U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4513U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7248U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5185U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 819U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2799U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3860U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1280U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7836U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5141U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4808U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1462U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2625U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5887U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1870U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 719U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 59U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 476U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1509U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1590U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 604U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1561U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 529U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1029U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 464U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1997U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 926U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2022U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1352U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1437U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1006U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 671U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1926U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1933U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 21 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10863; nearest pair: 495 / 674
void TwistExpander_Mirfak::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4511U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 126U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8102U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4504U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2569U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 687U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 535U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3238U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2515U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 801U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 821U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3585U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3004U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4255U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 64U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7069U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2011U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1840U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1298U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1810U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 174U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1370U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 766U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 845U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2028U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 59U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 650U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1336U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 872U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 553U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1787U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2004U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1204U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 501U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1909U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 537U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseASalts = {
    {
        {
            0xAA74C5C5E430B1AEULL, 0x522D35CD6FC20047ULL, 0x01910C6F7B564DF8ULL, 0xA78A4F65A6D47BC0ULL, 
            0x9F2012396E202ADEULL, 0xAB475B2C9D58268DULL, 0x91A750659DCE292BULL, 0xEA142F84BA34B620ULL, 
            0xD2AF0CF25CE9ACCBULL, 0x60E8B3E529611ED3ULL, 0x2E2793921D6D51F7ULL, 0x8182587FECB43668ULL, 
            0x8D9A450B12F0AF58ULL, 0x817FBC6DBF7FC8FCULL, 0x2A4CF9BB52C5E876ULL, 0x781A151860AF2DBDULL, 
            0xB4CF94337381F2C0ULL, 0xB184C4C82C2CFB30ULL, 0x3EFB1E91A198BE39ULL, 0x7B83761D4CEC80D5ULL, 
            0x2550E6FD7F5275A4ULL, 0x602195C53C3C24CAULL, 0xBEF04A043559F263ULL, 0x9AE7F95B6A8BA853ULL, 
            0xF5453DE49DCFF636ULL, 0x94D564DA5163AA89ULL, 0xE39CED886027A3C1ULL, 0xD36390D61981182DULL, 
            0xD6D0F59EDB0C503EULL, 0xFC1CCB88D0A160FEULL, 0x6C9690DF362A7D55ULL, 0x857CF74DD7027141ULL
        },
        {
            0x5570A9D8401BE723ULL, 0x3FF45126B4973836ULL, 0x00BDE90027B943E2ULL, 0xA0F4E11ECEBD26C8ULL, 
            0x75B3AB6F2BC66E32ULL, 0x9A8DB8399A5FD42CULL, 0xDCDDEAC342DDDF78ULL, 0x46E7617E789EA188ULL, 
            0xECF28B2C9C1609C1ULL, 0x8F85204FC634564CULL, 0x047835702419F556ULL, 0xCE3E72793B8B6360ULL, 
            0xD4BD7603C239DC77ULL, 0xDCA0DE8AF3C93844ULL, 0xAB3E03ECA534913DULL, 0xB9C773891D187436ULL, 
            0xB8704D02AC18CE67ULL, 0xB8D0FEB441F5D548ULL, 0x704A85F9322C9BF5ULL, 0xBE36CBE42862C99CULL, 
            0x640314A815248606ULL, 0x18223DAD7F17AA44ULL, 0xA821C4C477D2F765ULL, 0xF0B247C8803D59E3ULL, 
            0x6FA882C6FBC40F64ULL, 0xFB84C9A2C53FDC7BULL, 0xE80EEEE7D1CFF9CEULL, 0xA1681193767F0497ULL, 
            0x87FF6C5C262AEB56ULL, 0xBCB17856055C76ACULL, 0x7909FF74FA92927CULL, 0x8A3BC4021F2035B4ULL
        },
        {
            0xEA9D1ECB99156BF6ULL, 0x54FDBC70CD6E2036ULL, 0xE9A892B0F06FC79CULL, 0x2276F181C8692C15ULL, 
            0x419770F4BFEB9D14ULL, 0x2AEA3854C8926BF3ULL, 0x4F8C654F198B9A8EULL, 0xCF002E88733D991EULL, 
            0xC6C34D7A3432CA62ULL, 0x1CA1B2F2FC770548ULL, 0x7BE72ADF2251E9DFULL, 0xC04CF6495BCF924CULL, 
            0xD466B5AB11F0AC76ULL, 0x9F3214AA4E9EA651ULL, 0xBCC1650836F90F42ULL, 0xC9089503DB4FEC97ULL, 
            0x9C096C51B54C4059ULL, 0xC953A7B9B5B4706DULL, 0x7DC4ABAC45B6945EULL, 0xD58491CAE06C3E4EULL, 
            0x80A7961D275EBBF7ULL, 0xA15A4311E5B272BCULL, 0x11BA1D24A6EC049EULL, 0x4323B2E0E1EE1827ULL, 
            0xCA736D7E77030DF7ULL, 0x101344D092AD2B0CULL, 0x43DBD95528190037ULL, 0x831837EE5A40CBB2ULL, 
            0x9226116A4D0A59B1ULL, 0x14259B82AD852429ULL, 0xD066905945C77669ULL, 0x0C2C373162646F37ULL
        },
        {
            0xA519FE8AA984DE96ULL, 0x2F635244C491D967ULL, 0xA09D9D2C5AF889B8ULL, 0x80BA293444C092A4ULL, 
            0x557D1EA98CEB64F2ULL, 0xABA444B2D8D26A10ULL, 0x7738D7F91A69F92EULL, 0xAE3E5111ED886C6AULL, 
            0x9F8689F620BB1916ULL, 0x15E0700A1F182F4FULL, 0xE66708B634A9426BULL, 0xD7F2D2F5D0185D42ULL, 
            0xE152BDC8473E9370ULL, 0x598B080951820CEEULL, 0x49989B42AC377A23ULL, 0x8A4EBA7F2262E84CULL, 
            0x948FF22F10DB8A9BULL, 0xC228A4DD09EB1463ULL, 0x458212982DC54044ULL, 0x99A0A57642195C30ULL, 
            0x4DC0A0BE5232610EULL, 0x9AAEB5789359E813ULL, 0xDCBE0719AB672461ULL, 0xE85C4A7379806F33ULL, 
            0xA3BE7AB96C1544DEULL, 0x27AC3CEBBFB3E5E5ULL, 0x2982222380C3238BULL, 0x0510079652F57E26ULL, 
            0x7567464BE9C95BEAULL, 0x36B18FF61E7D5F8BULL, 0xBDB1346FA629F44FULL, 0x77E5656B1B5F807EULL
        },
        {
            0x8AE7D8671867C486ULL, 0x4AADFD608DE9C308ULL, 0xA1053A581EB25B1EULL, 0xD397222874926853ULL, 
            0x87EE6751B389C214ULL, 0xC4573AEB3DD4E4A6ULL, 0x6142B34051B98174ULL, 0x5D02A9F71804FCB9ULL, 
            0x07A0860CBC4984DDULL, 0x939F24D197A5E674ULL, 0x85AA786C6DA77AD8ULL, 0x0AC2F1C29A48522EULL, 
            0xBD1D993FB5AB4D0AULL, 0x050C40A0F47F3CA1ULL, 0xC14ED373C84D5DF4ULL, 0x1B40C933E8370A0AULL, 
            0xBA15F0D02372984DULL, 0x91F412C0128F404BULL, 0x1A0CC0B4F32635CAULL, 0xFACCE4BD6E93C6E7ULL, 
            0xFCFDD56A839E5E04ULL, 0x3700424F9A0A81FCULL, 0x578D9A475B309F40ULL, 0xF28AC6499D302596ULL, 
            0x07232E8FA31F2E88ULL, 0x3AE0B5D8D4104400ULL, 0x19B50FABE590EACCULL, 0x59146877689E13C2ULL, 
            0xEA689B594C28697EULL, 0x8593EC041ED353F4ULL, 0xE31AA1ECAD8D1562ULL, 0x34123E768BB1F667ULL
        },
        {
            0xA056F08C806FD6C8ULL, 0x319155292AA82666ULL, 0x37C94A3911153AAFULL, 0xC9D78646373E8904ULL, 
            0xDDAAF85448368497ULL, 0x4A73590F245CB635ULL, 0x43C88E5102EC850EULL, 0x44F03892CA2456BDULL, 
            0x9428FDA48276B63DULL, 0xC949A666F0DD4AC8ULL, 0xC86E9262F4DE68E4ULL, 0xA574798FAF1F1128ULL, 
            0xDE51E347AC97A419ULL, 0x8E6845B50F496F78ULL, 0xFD0DB000982F8025ULL, 0xB7EF7EB647F5EAF3ULL, 
            0xA7A8ADEDE3A47AA4ULL, 0x688A9BD71EDA4B73ULL, 0xF094731DD992132CULL, 0xBD250F34A554D120ULL, 
            0xC6B1834FD1DE832BULL, 0x66568C6B47522DF4ULL, 0xE335D14141886BB0ULL, 0x8BF76FC8C5554381ULL, 
            0x286ABFE367B5B706ULL, 0xA4D1EB56154C57AFULL, 0x3973B5391E9B7527ULL, 0xE9E54FD87EBEDF17ULL, 
            0x3A912DED6E0FCDE2ULL, 0x5140B6F4AD5A5A8EULL, 0x1C2EC0E97B406A4DULL, 0x71D0A542ADAAE273ULL
        }
    },
    {
        {
            0x86A7F3FF578A7956ULL, 0xF9917584232DDFE8ULL, 0x5B8EB334DB41C965ULL, 0x6D98326863D22E80ULL, 
            0x27A1530D70EE4582ULL, 0x440531650B3DE617ULL, 0x525DE956AD87D3A6ULL, 0x808384EF3C5343AAULL, 
            0x32AE87ECD303B5A8ULL, 0x7E0974D21B154444ULL, 0x3A6221400371DA5AULL, 0xF13FB5E5AC3F9E2AULL, 
            0xE2725EF090479A49ULL, 0xC827815C163FDF3CULL, 0x40B5F1D64177CBF4ULL, 0xD4193A8C068BCD79ULL, 
            0xA873B0F1CEDB1C94ULL, 0xE34AA077A7A183B3ULL, 0x3C5021FCE118491DULL, 0x4311FF88228B7A81ULL, 
            0x5CFFC04B49611A71ULL, 0xE5961A4434729FEAULL, 0x5162519B35B3D9ABULL, 0xAD6711C35005D361ULL, 
            0x7284117D8D86664FULL, 0x8CC3E8E78A4B1BAEULL, 0x8BCB8AC3D7CA0B40ULL, 0xBC853542CA6407F9ULL, 
            0x6658B977110AB9EBULL, 0x8FB81CCF56C4EB8DULL, 0xC2285F45F07C793FULL, 0x614FED622C2F0B6FULL
        },
        {
            0xC55F615E7A5C823BULL, 0x6AD12DA89EB136A5ULL, 0xBBF22B2A01C14990ULL, 0x42875760A78A95C6ULL, 
            0x791FB8B034CC9291ULL, 0x9F9A9C0B30B8BB5AULL, 0x8D841A3A52E896B9ULL, 0x49BB5DDEF31F8291ULL, 
            0x053A5F11AFEF067BULL, 0x1DA36919D12931BCULL, 0xE7FE0DE68450D95DULL, 0x0F46D0DD82919B19ULL, 
            0x1AB2EDB604199BABULL, 0xEC5C12AF553C8A7FULL, 0x39CB35ADBC5F98DFULL, 0xF97769AEC93BAD99ULL, 
            0xE7941F8603E54B2DULL, 0xA3FB620F65FDF7A6ULL, 0xF37E20F0D3988D39ULL, 0x486F2E008C33B8C5ULL, 
            0xDD22CE20197591DDULL, 0x781B2E3F2AA48726ULL, 0xD5444CBF02742F85ULL, 0x39C51F11642DDA13ULL, 
            0x8DE7EEB35C379D52ULL, 0x95D311FBCA43632EULL, 0xF4598431085F5676ULL, 0x64B5041918E46415ULL, 
            0x7AA31DA194F4E245ULL, 0x43BE040782B875A8ULL, 0x1322D920DAA632D2ULL, 0xF3308C53382FF4B4ULL
        },
        {
            0xF04A7BDF459626F4ULL, 0x246DEC6B2C6A1CECULL, 0xDFF6DEDAC0EEF03CULL, 0xC42A248C927CC554ULL, 
            0x2B400B013F85D6D2ULL, 0x7A1DB0C810EFFE73ULL, 0xF31F5AE701B265BBULL, 0xB6E79119C210BD55ULL, 
            0xF45532BFC72BCB81ULL, 0x121593895AA79BC3ULL, 0x9D9F3C1578F3AF8AULL, 0x71B228BF39BC2643ULL, 
            0x8A88A0DD05B8D289ULL, 0xEA102297137552D3ULL, 0x43A32FB77627E482ULL, 0x2A4C8E3F0A7C1CBBULL, 
            0x4F9662104FC0F353ULL, 0x4E03DDCF8B239451ULL, 0xFBC4388019774EB3ULL, 0x3F801ACE15E3A2B4ULL, 
            0x0EBC5EF704423E00ULL, 0xD9C072B7FF72CEB6ULL, 0x06A84D8BB660C646ULL, 0xA557748106E3E3E1ULL, 
            0xE7AA3732C96A0BEFULL, 0xFA0D982844BF2381ULL, 0x107315705C354EC9ULL, 0xC7A66204657A2740ULL, 
            0x649168DEA3E9A036ULL, 0x52E634CDF5D08170ULL, 0xDA08FE7E51DF4EDFULL, 0x596AF241EEBE6DEDULL
        },
        {
            0x4970D0D4173A3B7CULL, 0x66936B51106CFF16ULL, 0xBFA1982804C1088CULL, 0x9D55CDBEDE509040ULL, 
            0x96F53535E0FF0546ULL, 0xE9452D63542963EAULL, 0x97F4E9CA0AF234C1ULL, 0x9BAE6A41C0D6BF00ULL, 
            0x5FD39D35BEBEF437ULL, 0x9BC13ACB832417A1ULL, 0xC6305EA1EAFDE19BULL, 0xF0FC7482624E7B47ULL, 
            0xD9FB06651B2BD2F5ULL, 0x7BF8513ACCE01F80ULL, 0x7B6858B29F8B871FULL, 0x6D4BCDAA3C27BBF8ULL, 
            0x49971FA8D0337501ULL, 0xDCFD57A4E8F9BBEFULL, 0xDA3EEC724D662ECDULL, 0xA35347194BE9ED60ULL, 
            0x4256AFC73AE26900ULL, 0xD3F3144A5BAB178BULL, 0x9CB9440D7A3AB823ULL, 0xECE5C8E26F8E3932ULL, 
            0xA2B2E6812FE86149ULL, 0x15073C40C40334B3ULL, 0x554417E5EDA197FAULL, 0x1ADA022FC871667CULL, 
            0x1BCF97A57C6F9E47ULL, 0x68A33C174E5D0DFDULL, 0xBE51EC2A6F4912CCULL, 0x2114AE8A31DC2C2EULL
        },
        {
            0xBE9A4619939152F0ULL, 0x61233F2E9C6525E4ULL, 0x1DE0FC97EB8EEA2AULL, 0xE11453395DC94F85ULL, 
            0xFA1028B74D621EA2ULL, 0x65601F2C2BB21C35ULL, 0xB82E059FBF9D04F7ULL, 0xAF2851B6990F5FC6ULL, 
            0x129DE1756A8B35AAULL, 0x496AF7F0B8D16692ULL, 0x2C394F2D61BC6BA9ULL, 0x5FE77D6D76EF5984ULL, 
            0xFAE22885FFEEC807ULL, 0xB3623809F932E73BULL, 0x8E7C9892315303A5ULL, 0xC33162E669D06DFAULL, 
            0xC7793F93CE7AC279ULL, 0x8ACBC1C4E548C6F3ULL, 0x6230D84856BC9B80ULL, 0x6E15807BE0D08D15ULL, 
            0x758A98CD2B6FBCF8ULL, 0x04E4EB12B24FD737ULL, 0x7166DB9C0E4D87C5ULL, 0x13356E6120F0DD42ULL, 
            0x460D687DA591AA30ULL, 0xCD536BA75EF515E8ULL, 0xC93CCF6E9CA819F7ULL, 0x2C3160751C5C12C3ULL, 
            0xA01AD38F2BE531B7ULL, 0xDD1DA9BD4B7A4B20ULL, 0xF4EE8443EE1F1521ULL, 0xBB4130DFFEEC04B0ULL
        },
        {
            0xBA2BFC2B5A8C77BFULL, 0x924EB333F63B8180ULL, 0x9B221A0A28FD6743ULL, 0xCFEC899F8CC8FE41ULL, 
            0xFE4B5BECE9911FC2ULL, 0x33C5B41FA1647552ULL, 0x64C248F3511272FBULL, 0x63DFADC732F094A6ULL, 
            0x543F01C6D0B914DBULL, 0x2F14B9EAD88B65FBULL, 0x4E52A30F00BC71FEULL, 0xE513108880271ED6ULL, 
            0x6590A0732A42411DULL, 0x8C8120DC3E6B8860ULL, 0x29D80907CAD28153ULL, 0xF166CA09D8C2AB45ULL, 
            0x0FF617245108115BULL, 0x220875A497A4D52DULL, 0x3D83F0AAB665D556ULL, 0xCADB772C5652DFEEULL, 
            0x60F94799A7BBD03AULL, 0x004ABA5AE2F8BDE7ULL, 0x004694EE69E6564BULL, 0x854B055C0641CAFBULL, 
            0x8D55B1E330433664ULL, 0x903C51D8B8DAFBA5ULL, 0x925F66313D6E6465ULL, 0x168A01B309B5E121ULL, 
            0xE28F64E244AB6DC6ULL, 0x3951C08253180BFEULL, 0x5F78C29440707AF4ULL, 0x14F0CFDA12A65C05ULL
        }
    },
    {
        {
            0x6C9443B074AF0E47ULL, 0xF6BDBFA3B262D4FAULL, 0x01DCC76F7C96B64AULL, 0x14A7CF1CEE2409CCULL, 
            0xF0CB72F408749FC4ULL, 0xA72B956A9F53B042ULL, 0xE413CAE59EBDBDB6ULL, 0x76F6FF6E4540C395ULL, 
            0xAFAC67DACFAA7E70ULL, 0xCAA62B966C91E636ULL, 0x106272A470D1EC6AULL, 0x4572825484A2C2A7ULL, 
            0x627A180C58F74805ULL, 0x500FF9E13AB4A614ULL, 0xE4038E210A4A11B7ULL, 0x0174539F58BEBA61ULL, 
            0x430A14C1FFF5B7BEULL, 0x79F96845C999A2CCULL, 0x96A9E28888693957ULL, 0xD37A2D73A3FD0397ULL, 
            0xE9B1B46B9018CD2FULL, 0x2F84435239A42740ULL, 0xFBC289B6F090D267ULL, 0x1A7639CF15C995DBULL, 
            0x008897CEE8E5A982ULL, 0x5A7809B13C40CFF8ULL, 0x47E81379280C04A8ULL, 0x4C1C5E47357BEDB7ULL, 
            0xD83BD111CBF25F87ULL, 0x06CBD643B5CB00D1ULL, 0x93F9CD046DA9FB66ULL, 0x6309B3D43202CEC5ULL
        },
        {
            0xC7D8A17967E53DA9ULL, 0x73E25344B1711606ULL, 0x4ED643AE6B3FD0A6ULL, 0xD91B485FEB81E0EBULL, 
            0x40765DB6E6B9B33FULL, 0x5D474C7C24FE212FULL, 0x8B371157C4F4AA4FULL, 0x2744D239FA73154EULL, 
            0xB42D7B2E84FEF942ULL, 0xD80358926C8A552CULL, 0xCEE5C41AA8F85771ULL, 0x1456C17822C8F757ULL, 
            0xB1E87E4FB2695ED2ULL, 0xA93DF545292443BEULL, 0x2D9BCC1CC991ACC9ULL, 0x9FCAB3C6CC0458F6ULL, 
            0x7CC64AE5D7F6CCE1ULL, 0x8A7C3189C2558D71ULL, 0x54BD9F196DCFC7FBULL, 0x07D1215AF28154D2ULL, 
            0xE730056DF1BF63E1ULL, 0x6913CEEFFEB664EAULL, 0xF0F37165D86FBEC2ULL, 0xA6626607029AEFADULL, 
            0x56867115C950DB2AULL, 0x1B6F3E5B802B2912ULL, 0xEB2B807DC7469ABCULL, 0x4F956D352CE43B21ULL, 
            0x25782C6302A32D16ULL, 0x7B2E407B371DE1F8ULL, 0x94D3E7FFD773A66AULL, 0xAB9C1B86B7B7A828ULL
        },
        {
            0x01796362514C7613ULL, 0xA25F9351BE59270AULL, 0x8CC89C7911FEB9C6ULL, 0xEC07F0A2E64A73D6ULL, 
            0x3F75E9E8932D9C9AULL, 0x06F9B9D34F0408B3ULL, 0xD96513B6BA82C2FAULL, 0xB457FD9EEFC34957ULL, 
            0xC4488D4A37097C2EULL, 0xEA70EC9A2142A1B4ULL, 0x4E9636EDEC7A3548ULL, 0x3AE11EC185323EF9ULL, 
            0x8A667372AEDC3F22ULL, 0x42B0422CEA22E019ULL, 0x87D09185ACC490DFULL, 0x812713A011B838A5ULL, 
            0xD9B80AD2578D37D9ULL, 0x17C226FD460FB0E2ULL, 0x1F3B12F44E51AA62ULL, 0xBBD68985933AEF99ULL, 
            0x624C387B5412CE82ULL, 0x8088E4E007136B18ULL, 0x84E1A13ED9504CD9ULL, 0x3C3D4F61CF3768BDULL, 
            0x43BCEDEFB2926755ULL, 0xD7006FB799CD6580ULL, 0x9302B3766C57B70DULL, 0xE1EC14D67D0F509BULL, 
            0xF9F51C2B789FE4C9ULL, 0xD85C4C9078DE6951ULL, 0xD9B06243DEB74898ULL, 0xA14CEEA787D53690ULL
        },
        {
            0xA7B29A479554D9CCULL, 0x6A90558D1E2E895AULL, 0x844D85C4E4431EE9ULL, 0xB88D7D6E1DEFD491ULL, 
            0x46EFB59EB5903A39ULL, 0xF6EB5E67985AA0FAULL, 0xAD7F7CD8F5DC304DULL, 0x88B0F813EF7EB199ULL, 
            0x15E661A5DE625938ULL, 0x01737DBCFF91EC1BULL, 0x933E49782C58F895ULL, 0x23A3A37F3EB79DF1ULL, 
            0xC2FE0F16585D7B81ULL, 0x82F2715570DF663FULL, 0x97F980ACC3B7F9BCULL, 0xFC3941759CB283ECULL, 
            0xAB381725D325BD01ULL, 0x7D0B47F2687C8395ULL, 0x6DB513CDA5F9FF47ULL, 0x756AEE043559DEC3ULL, 
            0xAD74656BAD0F6A8AULL, 0xACC56C3316469F35ULL, 0xB86E0F886BC61332ULL, 0xF0E40D73D7CDABFEULL, 
            0xC46C022FD95841F5ULL, 0x274E7229985311F1ULL, 0xA9BB1DCA4F0DFF8DULL, 0xB70B5DA03EF0C210ULL, 
            0x8EEA8CF096441574ULL, 0xCD21DD6E83F6BFEBULL, 0x76837581AF13F742ULL, 0x45A5A5B4FABE2492ULL
        },
        {
            0xE1FE2124E1F1EA13ULL, 0xC283F89FF7EFAFF7ULL, 0x95FD56803EDDA108ULL, 0xC9D41F03A0D2FFF0ULL, 
            0xCF465B9EF0924508ULL, 0x5E07153DA8A5B1C5ULL, 0xFB8B702D9F1FB1C4ULL, 0x3A0C18BB7F79B069ULL, 
            0x166ECF14B4314FC6ULL, 0x053E6D52B44F8B36ULL, 0x11EA020395B72D73ULL, 0x2BF8D2310790BD58ULL, 
            0x32C145775A006FC7ULL, 0x2CBD0A25DA4D400CULL, 0xDB2255BA21E1A688ULL, 0x8601048DB5EEBF49ULL, 
            0xA2912720118D8917ULL, 0x24A052A525BCD9E3ULL, 0x74CDF88A72A2273EULL, 0x3CA40B18B47C3338ULL, 
            0xFFDB69FA36C9BC5CULL, 0x615280CA4C05F03CULL, 0xEA2F7F8FDC9EF9AAULL, 0x770E513EF80337C1ULL, 
            0xFD31F35C4AFF2715ULL, 0xAF6F1D690AFB7968ULL, 0xAEE8FDCEC04E6D2AULL, 0x23A9A5BACB1A0A63ULL, 
            0x1E1B9B8E80B3B785ULL, 0xFF966BB4B472D7E4ULL, 0x559EC2B88F963F49ULL, 0x5E89B3E4FF985139ULL
        },
        {
            0x36371C4DED7AD293ULL, 0x7C53F1CD8DE41D1BULL, 0x153C57C7E136D1D7ULL, 0x682CF964769888B1ULL, 
            0x16DF67AEA6D3083BULL, 0x3C4B3544E0DD1982ULL, 0x5123E8F1989F2EFBULL, 0xC0B73814B5355801ULL, 
            0xB26605C557BBD234ULL, 0x1504364BD1B9607AULL, 0x6157DE66C6AE43B4ULL, 0x57DAC261C66FF7D9ULL, 
            0x1476CCB73D722380ULL, 0x0D6F49457DFDB729ULL, 0xA950C531001B2853ULL, 0x60735D90FE2F8A5FULL, 
            0xEE7B8AEE8BE64631ULL, 0xB2239A7B592F2DC5ULL, 0x577DCB70948F1330ULL, 0xB0D88C7EE5173894ULL, 
            0xF11AACA810A30149ULL, 0x350E1E72386949ECULL, 0x8958DA31FE823B4FULL, 0xE962BA0DD6F53B54ULL, 
            0x269A3ADE3949FA40ULL, 0xFFF009E19983082FULL, 0x6FFB9B5FC1C989EAULL, 0x5F99ADF3FF175BC8ULL, 
            0xDEE6388EC1587B0CULL, 0xEA7648855FC98777ULL, 0x83920A1253B8685FULL, 0xAC2CB97D4C9CE606ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseAConstants = {
    0x2B61B5793CBEEB74ULL,
    0x1F079213F87DD241ULL,
    0x53165D6340265488ULL,
    0x2B61B5793CBEEB74ULL,
    0x1F079213F87DD241ULL,
    0x53165D6340265488ULL,
    0x0E079DA2DBF9309BULL,
    0xB75464776ED0F4D0ULL,
    0x9F,
    0xF8,
    0x9B,
    0xF9,
    0x8B,
    0xD9,
    0xBA,
    0x76
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseBSalts = {
    {
        {
            0xA80D54AB2C218EADULL, 0xE8DAAB7F37C6C4BCULL, 0x9F9B2D55AD59903BULL, 0x96429E52C936C446ULL, 
            0xEABDC59AC38CF1DDULL, 0xBC69F912BCC0DEE4ULL, 0x5CBEF7790A64920BULL, 0xF54C2882371A1317ULL, 
            0x2E78EB136ED7CEFFULL, 0xC0747F3D036462ACULL, 0xCA4A3BA93F77032CULL, 0x56137BBC3E00CFCAULL, 
            0xADE7A11BD5D8D49BULL, 0x9B2B116359738F15ULL, 0x10F705612851DC18ULL, 0x281D99A0F649EEDEULL, 
            0x5BA0AB0416C68C69ULL, 0x96D8CC478C91CBDDULL, 0xBFE832D364C75836ULL, 0xE46C4E80F4333707ULL, 
            0x0FE7B90202A8FE62ULL, 0xA9D183AFED89FCB1ULL, 0xCF9EBF4921B71474ULL, 0x819E8E453413A357ULL, 
            0xEE75346A0BF8D8E4ULL, 0xEC678F7E0E0B9D85ULL, 0x4AA60E558809B195ULL, 0x361A12CDDE52EFCDULL, 
            0x67CFC4EBD87260ABULL, 0x1F76BD094886CCA4ULL, 0x97FBA3F4AB11F838ULL, 0xFE1C5B1C9EF014B1ULL
        },
        {
            0x319FFAEFFE6CE950ULL, 0x2D978E78AC3CC2ABULL, 0xB74BBD440EB7B085ULL, 0x677A256AA2DEDE9AULL, 
            0x451FFB519E7E13DAULL, 0xFD3C4C627D840473ULL, 0xC527D4B7E0548514ULL, 0x750202FC438D5907ULL, 
            0xD42646FC58A5FD1DULL, 0xE9270FE9338161DBULL, 0x5EC559A930940535ULL, 0xE724724698C70032ULL, 
            0x716F8C8082BD9D71ULL, 0x7810EE88C9784034ULL, 0xE8C36E5177ABAFFDULL, 0x813A78A1EE4C8076ULL, 
            0xCFABCB45B2D32B75ULL, 0xCE3087A5A4AA363EULL, 0xF945EF875572F04BULL, 0xEB1BB2F79BE7475CULL, 
            0xF3062D69D8A871E0ULL, 0xB730CAAFEB8A12DCULL, 0x4E38FB456978E9F5ULL, 0x7426CF7FC6E1BAE9ULL, 
            0x76B5EBFCE049A071ULL, 0x2A85F918DF9E9C8BULL, 0x07190D0EF656EB7EULL, 0x84D39F12ADD3CDCBULL, 
            0x4E6A6131BF94E4BEULL, 0x8B5899DC48809F63ULL, 0x0C2F783A62CE2727ULL, 0x83EE437C1257BF8BULL
        },
        {
            0x9B457F8488959E74ULL, 0x4A5583D34BE6F78BULL, 0x70E45CCA0CE78A13ULL, 0xC2F7DB7248A6073EULL, 
            0x434CB84977EC50E9ULL, 0x8761A171ABC22165ULL, 0x13DBCEC38F743038ULL, 0xDEF880D1C214E348ULL, 
            0x671D478A21485108ULL, 0x029D3B6892695A64ULL, 0x1CB8FF557FA22F62ULL, 0xF243F142E536EA95ULL, 
            0xF7069FF1E902781BULL, 0x6D18E218E2AB6835ULL, 0x8710B8CE1F9B1ADDULL, 0x0AB6E4A974AE5BC6ULL, 
            0x9A897FB835B761F3ULL, 0xE0D0AC94FD324A87ULL, 0x22D27C8C1283F8C0ULL, 0xD7182092BCBBCFFFULL, 
            0x8F1A6B87CE137A9EULL, 0xEBDAB6621B92D6F6ULL, 0xE01FA535D5AA6A80ULL, 0x08E1F9B90CF63F64ULL, 
            0xCCC8A4DCF5BA4F59ULL, 0x481965EBD623BB75ULL, 0xCF06D7047F9A778EULL, 0xB244DC79AD585FACULL, 
            0xCBBC977F7B433D43ULL, 0xB64CE8086AF9B177ULL, 0xC17AB061D6991EAFULL, 0xC4CDA0511A0BD001ULL
        },
        {
            0xCB47FF8984FA96FFULL, 0x9E4AA4C937441B2BULL, 0x129154BE303E8EFCULL, 0x1EFC532E2A1766A9ULL, 
            0x869099D65645E294ULL, 0xB0760E77271C770BULL, 0x761598217F6A7931ULL, 0x8C15E91D39D59E8FULL, 
            0xBA805B3BB7AC4EA8ULL, 0xCC03482BD726CCC1ULL, 0x5EE02A867375442AULL, 0xA318A07A33C449A4ULL, 
            0x4A5993BC917609A0ULL, 0x59B15B6447021B5EULL, 0x8FAA54A8836AAB43ULL, 0x0B09EF1F28A7C36FULL, 
            0x8CA620DCDA2AE437ULL, 0x9F37C5DAD890F750ULL, 0xD5B339AADF364DE6ULL, 0x87D8BCBA593E3637ULL, 
            0xF31C113048E750CEULL, 0x98DCFA22CF795AD2ULL, 0x2BB8A863603148E2ULL, 0xD7BC687DB4A45ECDULL, 
            0x91D02B46EB8685CEULL, 0xB9429CDC1CD71875ULL, 0xAB13AEEA2C8D0025ULL, 0xEC618CB614C4B6F1ULL, 
            0x8C663574D91E674CULL, 0x799948A71075BBC6ULL, 0xBA3AB74700A69CD7ULL, 0xE626ABDC6C3A2C4DULL
        },
        {
            0x0C9D5743EFC394C6ULL, 0x8D0CEFF63987C025ULL, 0x6110D34FB56BDF63ULL, 0xCF7BBD3E2D754B3BULL, 
            0xF4B3DDF99B12AFD3ULL, 0xB95CEEA2D5C795BDULL, 0xE9B99FF908B529F7ULL, 0x3AEF61AABE8CCC83ULL, 
            0x04DC260A9DE2619CULL, 0xD2E08C6B464A315EULL, 0x17BF1692F214417CULL, 0xB9AEA33F5EFD9CDFULL, 
            0xB651606FF04F9AA5ULL, 0xCBFC56FB83A238AAULL, 0x392FE8E678A69978ULL, 0xD5500868BDF24E0AULL, 
            0x34D1610EC850BB69ULL, 0xDF0BD0C593AB7328ULL, 0x59B119C9D581C143ULL, 0x582C13C07BAD4784ULL, 
            0x4E9E2DA44856B2D7ULL, 0xC7FA2F344A0DB722ULL, 0xB6F9F84F2EB18427ULL, 0x1BC1D8923AA30E94ULL, 
            0x87866AE2B26F2689ULL, 0x4D76D377628A27B8ULL, 0xF05DCB492AF6642BULL, 0x963AFF26DADA3046ULL, 
            0xC25771396AC3EA88ULL, 0x3572F34C0A5AD699ULL, 0x2C37C8C0969E64DCULL, 0x2FD73FB519E2BE8AULL
        },
        {
            0xB0EC6984ECBE9F50ULL, 0xB5DA6AFF9CEF14E1ULL, 0xA6434C67BA59D3EBULL, 0xB3C2E126A0BE5ED9ULL, 
            0x77ABD2F5DE1EF7DBULL, 0x0900D35B9D0F2FA0ULL, 0xD0765B934EA36E19ULL, 0x076947127E281F3BULL, 
            0x4468ADA0BA0253A3ULL, 0x827B94FC1D7B590BULL, 0xEC9553CE0E02847DULL, 0xA2BF937B268EE8B9ULL, 
            0x03C32C2176C6425FULL, 0xFCF986AE86CA53F0ULL, 0x1B8C12EA0E5503FCULL, 0x7B0582C55C27556EULL, 
            0x0F584EB4F9112808ULL, 0x398C6617EFAA44A0ULL, 0x791ADFA10D2929E7ULL, 0x06C85BA6E327B340ULL, 
            0x4C5A599B25B644D1ULL, 0xE94B3296F596512EULL, 0x159CEA14494B2628ULL, 0xED9E49A00A5A0F18ULL, 
            0x919837AF36E9D3E1ULL, 0x35F14EB7452EA4C6ULL, 0x9033C4776A0A35E8ULL, 0x86BC82AD7D33A05DULL, 
            0x5F8D604B5BD46673ULL, 0x22A253350D0DEC0CULL, 0xFC1BD031092350C4ULL, 0x2BEE1305D2CC56F1ULL
        }
    },
    {
        {
            0x01634CE1926DDAE5ULL, 0x08471FF56E21CB27ULL, 0x0A0B400E7777C247ULL, 0xE96CF2F76D8C8779ULL, 
            0x8687C064BA14E13EULL, 0xBE725E57862EC277ULL, 0xBEB680B92C4B9010ULL, 0x219E44BE10280F0EULL, 
            0x3D1040FF55F8E197ULL, 0x0DBFFAD200D6E7A1ULL, 0x2540EC0058904F62ULL, 0x4F56B32279C274AEULL, 
            0xA8E2B1591F0C1D3BULL, 0x616560214EF66724ULL, 0x0A2AFFCF55B5655AULL, 0xE9B90608CE95809BULL, 
            0x1718CA4ACEB82F11ULL, 0xCDDDE5481957684CULL, 0xF9E065B9F83FDAA4ULL, 0xBE2D52B66A3A7FA9ULL, 
            0x66BF41FDB2228687ULL, 0xE1FA000652B2E9E5ULL, 0x2A7E88D838E69CD2ULL, 0xE53086876209C2A3ULL, 
            0x9EA06147EE613E2FULL, 0x2268B9419929691AULL, 0x775FB5DEEFC60E02ULL, 0xEDB2964E95114A04ULL, 
            0xC16704CEF43DB2EDULL, 0x0316567C24DA458FULL, 0x35A885FA0E0382E5ULL, 0xCC027D1C9F66FE31ULL
        },
        {
            0xFBDA141F9B235ACCULL, 0x43EEDED4681EA948ULL, 0x738BCC2012E3CB8DULL, 0x3F3002CC186D2C6CULL, 
            0xFE596EBA5F82392EULL, 0xC699C4E6D48F7130ULL, 0x1B79FED82A96A6AEULL, 0xBC896B3029FF97F6ULL, 
            0x8026341CBE9DB91AULL, 0xB0F34B813FDD004EULL, 0x38D5122D378E4FFEULL, 0xDCD784FB1EC4CD68ULL, 
            0x6AA129C91151E6C4ULL, 0xF567C90B95449FCDULL, 0xBEA6BD8E3BDE9DE3ULL, 0xD1A7EE2F5E15345EULL, 
            0x5EA122374E39E4E6ULL, 0x1CCD4038548B7C96ULL, 0x17807A58F0ECFECEULL, 0x309151F57A12228EULL, 
            0x1C8B24BE44C59646ULL, 0x37E3175D1DCFCE64ULL, 0xE2A68AC2B954FCA8ULL, 0x63BF170D759D7D28ULL, 
            0x1A2D3F1184BCA36EULL, 0x99B7E6924B8906E9ULL, 0xBC9FA689DEEA46C7ULL, 0x6CCA6E6234E01520ULL, 
            0x233AA6ADD5075207ULL, 0x904D02FFD7682767ULL, 0xA936EEB53A9DAAF7ULL, 0x328C4EE53E4992DDULL
        },
        {
            0x46053CDE01E7C8E1ULL, 0x32A6927AC5AC020BULL, 0x689F5460F9DCAF1EULL, 0xBFF8BC8CBBF309CCULL, 
            0x7BD8B2CA77572DAFULL, 0x68C4543926CC87DDULL, 0xE16F5A8EE838A146ULL, 0x3D1633E0E93392BDULL, 
            0xB50C947AE3158686ULL, 0x2F2F7D02CCBB2870ULL, 0x3396EE3810421EEFULL, 0xE54EBBDB96B9818EULL, 
            0x06E1E42AD824A07BULL, 0x2C4B8ED235CC95D5ULL, 0xAEB7E3823ED919C9ULL, 0x216A9E513DCA5537ULL, 
            0xA1615B4A0476E317ULL, 0xBF32F27BD3A2898DULL, 0x4B685DAF09483A3FULL, 0x5E220DC70EE89687ULL, 
            0x655C98E4F4B44260ULL, 0x9349E6D78B8276EFULL, 0x117B6C38D5A4850CULL, 0x291201ADF1865B3FULL, 
            0xF0AD34255F9B9B9CULL, 0x22BFC6DF02BECF69ULL, 0xDC9A9E3DBB20506EULL, 0xB95FFD7F79EC7864ULL, 
            0xF2ABFFE7B9877F4AULL, 0x97526D8C764D2D2FULL, 0x5A3F8669E37A0460ULL, 0x1AFDE22438A7D881ULL
        },
        {
            0x03D8A6879B56E808ULL, 0x8C3FEE978D3BC38AULL, 0x9C55DD797D2C189CULL, 0x4E136195EB431CB3ULL, 
            0x118A53D6846788A2ULL, 0xD1106F65BE21311EULL, 0xA710A4D59AB766B0ULL, 0xDEA44372869C964AULL, 
            0xBDF4DCEE451CB967ULL, 0x77596546B215ADDBULL, 0x64537DEB8865A018ULL, 0x36B241274DAEC3DFULL, 
            0x887B55CEA8174984ULL, 0x8C579E8C4A6444F9ULL, 0xB71835CD7D8B7B1FULL, 0x8E213C84EB2D2553ULL, 
            0x6844618C6440B8EEULL, 0xEB4AB78C97372BB7ULL, 0xA8DE39BB8D1C079DULL, 0xE12B2394C2BDA900ULL, 
            0x5753732F103A79E1ULL, 0xAC941FDFBF931A04ULL, 0xDED8FAC16D15ED2BULL, 0xBBC165ACC816F6DFULL, 
            0x9424FDC4CCBEF4CFULL, 0xE4A355EE120E8567ULL, 0x5331195A994AA4BFULL, 0x80887A4BB664E64DULL, 
            0x535BE50A0A950E75ULL, 0xF987F40DB9A300C6ULL, 0x786D64560B78ED6FULL, 0x9797DB3FF9873D33ULL
        },
        {
            0x007A257C98B23134ULL, 0x298454193DFCD8DAULL, 0xFD49B684142808E1ULL, 0xC3569086147D38EDULL, 
            0xFA7347962301C21FULL, 0xA7E6C77C0AAC1173ULL, 0x802917840A1E4A83ULL, 0x6E45A80DD9D68B1DULL, 
            0x94B6F401016B2A17ULL, 0x57F7A4FD3BF4287CULL, 0x2BF2BECD6B678E3BULL, 0x79889965AF5849F8ULL, 
            0x3DCB0F383893F48FULL, 0x846B933A28B45384ULL, 0x582BD66BED80476EULL, 0xB70410183E248C7BULL, 
            0xC93FF25F9AECACACULL, 0x6E9797C79B265DABULL, 0xC0601483458C0B9DULL, 0x89C0C7B6489E32FBULL, 
            0xE7086E3EF2046BF6ULL, 0x9EE202C1BB7C9651ULL, 0x929D3213EF02A306ULL, 0x09FA0456F8D6E73EULL, 
            0x1D46038222CFEE23ULL, 0xC86572DFC48B8CD5ULL, 0x85C39531BACD4EC4ULL, 0x6D2E8C6F0F2CF981ULL, 
            0xF2DD66D110C8DDE3ULL, 0x3FEAC264B9AD3908ULL, 0xCEB26FABDEB9BFFEULL, 0x7630A924A1CF878CULL
        },
        {
            0xC0CD35962266A321ULL, 0xAB86451C114EC0B8ULL, 0x99D84E47BEE22D3CULL, 0x1B618008609C9C95ULL, 
            0x9BE4FA2BC7007C80ULL, 0xA4CDFAFEDD3D59E4ULL, 0x2F7F306C986149FDULL, 0x6DD0531663B582EFULL, 
            0xBEE85DAD562389AFULL, 0xC7C83A9128D6332DULL, 0x79D2E36164583137ULL, 0xF6728DA555060FCDULL, 
            0x110A58011BED1D67ULL, 0xC19D83548C3A8AC8ULL, 0x698D4A48160D53F8ULL, 0xA97C6DA67093CA2EULL, 
            0xCF2966EA266A57E9ULL, 0x742DB0744289085CULL, 0x1DD0C61C4F645143ULL, 0x9620956C4783072EULL, 
            0xC3E8D8D380768912ULL, 0x071D7ED3C864C787ULL, 0xEA243841D1D69611ULL, 0xC9DB559D51607595ULL, 
            0xC3D9ACDE5909323AULL, 0x392CFF3F01C4E616ULL, 0x3F34196EF4CA8668ULL, 0x571DFBA4BE7C9675ULL, 
            0x270B9C2FC89670EEULL, 0x0FAC5BE9D794A618ULL, 0xC903F7722711D377ULL, 0x294A3529DB1C1E37ULL
        }
    },
    {
        {
            0x587CCFA08FCD0200ULL, 0x53EEBBA1B569BB1FULL, 0xD3D3AB36A1585A26ULL, 0x514E1B6F15C8BD27ULL, 
            0x884D6E181A29B1CAULL, 0x40CEEC5C33FAF667ULL, 0x09BD39497E1AA6FAULL, 0x7A6D10633100F756ULL, 
            0xE73957D7A6CDE15AULL, 0xA70754E585ECD9BBULL, 0x9259B4692B016DD6ULL, 0xD4D349CB624BCDA4ULL, 
            0x91F0D47FD39882BDULL, 0x273886C8CE350A34ULL, 0x5BBAC175D974CC8FULL, 0x36F64185BF44078FULL, 
            0x05FE3318F0EEFD61ULL, 0x9FFCCB65C4AEE429ULL, 0xD9AA1EC5D5F159A4ULL, 0x403C4E0E4CB35153ULL, 
            0x5C5D490558A9C38DULL, 0xDB345F88C014AB0AULL, 0x559347A6C886C536ULL, 0xEDE43BF0D0C10334ULL, 
            0xB0C8EA8287E0DD2DULL, 0x099324048DD90FE6ULL, 0x02306B496A3894B7ULL, 0x13E4B97FD58F5BB3ULL, 
            0xF9B2D81D8142906AULL, 0xA37A68D757B41A8AULL, 0xEA184C1E82C740EEULL, 0xD908BBD604F2A247ULL
        },
        {
            0x9FECF313AE949510ULL, 0x21E02E7D42ABA720ULL, 0x3600B92B82F04C97ULL, 0x0768F6752BF4B30CULL, 
            0x7A41F811D4DAA737ULL, 0x1DC5229BEA9577B1ULL, 0xFF64BA6E6BBF9106ULL, 0x6B2121817F7138F4ULL, 
            0x3057EA7CB1FBB433ULL, 0xDD8D120DC0DEA3C5ULL, 0xB264810FE7BB63DFULL, 0x6CDC249BC7DF5DFAULL, 
            0x5ECF93E7C540D284ULL, 0xAA947D512F1CA35BULL, 0xC4B59ABEDCD6B031ULL, 0x64C36AC250FBF3A2ULL, 
            0x1CCDEC532325C412ULL, 0x8166BB16E6E4ACC5ULL, 0xDCC84B9DCBC8AB3FULL, 0xB28373535330C4F1ULL, 
            0xB475A308C82EDA05ULL, 0x19B0DA82D2A704D4ULL, 0x8D560041E9337A4FULL, 0xE25AA7A6E45BB8B3ULL, 
            0x1E0CCA2AA412E826ULL, 0x0F33D79EE48EDA0AULL, 0xF7FDF9F87C8D04AAULL, 0x0D5F995BF953E0F2ULL, 
            0xA16A9B3356329703ULL, 0x4CE3E7304F6A7D18ULL, 0xE9B7375DED8DA7E0ULL, 0x8FDEA4479D80809DULL
        },
        {
            0xA08D0EB4DD23CA46ULL, 0xA160C6F1E21FF0C8ULL, 0xD2255A53FC6E8918ULL, 0xE3BCF39DBE7E3740ULL, 
            0xD9C8C4037C3F081AULL, 0x4FA1038448C82726ULL, 0xDACEFC745D12157DULL, 0x501DA04A7CA55DD0ULL, 
            0x089BD276A8307BA1ULL, 0xA73E4B9CE356A43BULL, 0x9790C65D72E50B49ULL, 0xDD48C1B94193CF41ULL, 
            0x0E0F0602C8A7E260ULL, 0x646350060E2BD2D0ULL, 0xAEA4B9719A46EF38ULL, 0x132C2EF76D59E02EULL, 
            0xB32A9E2BB2DADC2CULL, 0x2A87BC45A31401C7ULL, 0x19579956B20DFAD4ULL, 0x8BC063669C12E3D9ULL, 
            0x6B45A3EC0BC1D99BULL, 0x7C292915CBDC9AC9ULL, 0xAF11BC68F66BD9B2ULL, 0xE9F2A6B835B5D7A3ULL, 
            0xAAF7368617C851A9ULL, 0x004B858CB714E131ULL, 0x02F1E7FCF14301FCULL, 0xFE52D9BBBFF694D7ULL, 
            0xA042B1FA6D3E7C81ULL, 0xF4709FFAA44745FBULL, 0xF9EDA2FD3A8DED15ULL, 0x182CDA87104A9B19ULL
        },
        {
            0x6493BCCD3B525044ULL, 0x83D1FE3A7B893177ULL, 0xD48A069D42986BCEULL, 0x7DEC60198840EACBULL, 
            0x990D35DCDFFACADEULL, 0x8AF33177688D1298ULL, 0x19BF1938748D57CCULL, 0x56872BF1FCFAB77BULL, 
            0xC7B67BAD94BAEDBEULL, 0x5344BA428B0FA546ULL, 0x6804BBA3764DA234ULL, 0xFCD35E8E29ABE35FULL, 
            0x06847325747D9DE7ULL, 0xEDCC4AE58ABBF40CULL, 0x895EB3CC4D3DA48EULL, 0x1D23C923C16B1873ULL, 
            0x9EC042153E3D10AEULL, 0x5A2B27EFDFDD0C20ULL, 0x5DEB23B26BD9EA8CULL, 0xB84976A72B721C70ULL, 
            0xAC74BA785A356FC4ULL, 0xE3F4C736D29D98FAULL, 0xADFF4C3B28C3BC0CULL, 0x1FC5D7424AEF0246ULL, 
            0x6540E02E168BF7E1ULL, 0x182D11DCFDDFCB87ULL, 0x6BA57EFBC3211B7BULL, 0xFF0CD08DBCBBD423ULL, 
            0x9F20909A2219CFDAULL, 0x9FAA6610C725C603ULL, 0xC1F141D9864ECC0CULL, 0xBF5D30BDF8E1B851ULL
        },
        {
            0x7278CDBD8EE077C0ULL, 0x44F4F828F721E282ULL, 0x35B76939992A3B11ULL, 0x187DE653B882E284ULL, 
            0xAD8CA36391F342C7ULL, 0xE222B64F70EEF0BBULL, 0xC1B8A4D3CE2ABD66ULL, 0x07BE2B86F00835EFULL, 
            0x341D9DD569C084FBULL, 0xF923CA286DD3B447ULL, 0x1B9B60A782A7257BULL, 0xEEDF7DCF3EEFC26EULL, 
            0xA64DCF0D4CB0FF57ULL, 0x4DEF14B6988F59A2ULL, 0x08FAE94F72DAC233ULL, 0x66EEFAFEB5F54E15ULL, 
            0x6A57AFB851F19CA1ULL, 0xE000847E6C24D164ULL, 0xEBDA0AC8BFDFBAAFULL, 0xD9A22DC01FDC8456ULL, 
            0xAC86F4B3BC129A64ULL, 0x4061652D9F596FE1ULL, 0x13A51BC81EAAD13AULL, 0xC32010F4F85D7E58ULL, 
            0x257C8E38BA75950CULL, 0xB6F162F880E41866ULL, 0x4B246518FEF10077ULL, 0xD70DABCB8D212939ULL, 
            0xD283EE269605213FULL, 0x812DFFB59CDA3293ULL, 0xF8D5E4DCE406F2DEULL, 0x341A9CE68F638ED9ULL
        },
        {
            0x7951F41B3C556D90ULL, 0x15BAC0AC5EC8F775ULL, 0xFBDAD5D8D894F775ULL, 0x868EE82D423ECB62ULL, 
            0xDBFC531B522EAF02ULL, 0xC6801AABBADB1B70ULL, 0x9B0701A198C0F650ULL, 0xAD28BB7B984FBAFFULL, 
            0x5A65FCAF898FF1A1ULL, 0xC790DB20ADEDFF3FULL, 0x8049073058963D65ULL, 0x1ECB1687AE668FE4ULL, 
            0x6F8A110941D36FE3ULL, 0x186DCB00EE07AB5FULL, 0x5EA7DD5326E05EC0ULL, 0x3E1B154962AA6CB1ULL, 
            0xE701A0F7BAADC30AULL, 0x3AD90BF3DB32D5E8ULL, 0xAFA130E01BB80FA8ULL, 0xE308EE7ED57658D3ULL, 
            0x0F351A278B3A4A13ULL, 0x25DCE416A73B3E7EULL, 0x4BBFCA8D3F0B0F90ULL, 0x5EADE5A9914ACFE1ULL, 
            0xC9D1C0C10B5BF5BEULL, 0x1A81A622CEA58997ULL, 0x250BFCEC8390867EULL, 0x1C57AD2F6F1996E5ULL, 
            0xED526F94B077D99AULL, 0x3F2E183C328FA360ULL, 0xBDB5BA82808EEADDULL, 0x3F2374945C24D4CDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseBConstants = {
    0x7E2CE820333A7B05ULL,
    0x46E297328FC5D6DEULL,
    0x22F8442B11886B93ULL,
    0x7E2CE820333A7B05ULL,
    0x46E297328FC5D6DEULL,
    0x22F8442B11886B93ULL,
    0x4F7DE5B7E114CD3BULL,
    0xBD07160DDCB4430FULL,
    0xDD,
    0x33,
    0x95,
    0x6F,
    0xEF,
    0xB9,
    0x67,
    0xCD
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseCSalts = {
    {
        {
            0x1C613359F29FCD50ULL, 0xF3CC46FD710AA93EULL, 0x57C52C7C283FE272ULL, 0xAFADB8266A1739F4ULL, 
            0x4841D4E29EF6DB9CULL, 0xEF697601F29E4986ULL, 0xF3374644F4941326ULL, 0xDC5A9F851683F80EULL, 
            0x13F4FF7F5D8C3C78ULL, 0xE1AE038A3DA6AC06ULL, 0xB19C5C81324FA9DDULL, 0xB0375564F32ACA99ULL, 
            0xD93D6CA7ACC6652DULL, 0x1E1B74055822DEA7ULL, 0x629A37A9D8E71D15ULL, 0xA4B0B2EE64C31FC5ULL, 
            0x44A6E400767DC89EULL, 0x2BFF04165A6DA342ULL, 0xE9C7490D3C9875D8ULL, 0x7C28751B50A6DBA4ULL, 
            0x46787C89365F6121ULL, 0xE71DB290644CB882ULL, 0x56769F311E9B02A1ULL, 0x9CE9A3792C245A64ULL, 
            0xF5FF5E2F337B68CAULL, 0xBAC05F8D43D22EBDULL, 0xDAE9640C55B0F634ULL, 0x100117B6E2277144ULL, 
            0x436E69B983837946ULL, 0x584A476463BF28F7ULL, 0xB6649CD1CDEF7B51ULL, 0x2C93A5DDD1940C36ULL
        },
        {
            0xA8EC3E996D293DA2ULL, 0xC26AF464C26F077AULL, 0xB05D032DF9C363B3ULL, 0xB6964157C2E8DD60ULL, 
            0x5EC17BA554EF3905ULL, 0x428426A8DEA03B3FULL, 0x0389B203432E96E9ULL, 0x60ECC22CBCFAAE7EULL, 
            0x3FF562241B857226ULL, 0xF10398163E6718D0ULL, 0xE923833A405841DFULL, 0x95E4B25787DE7A17ULL, 
            0xFC4DC864C32A20A5ULL, 0xB952DFF1D97834A4ULL, 0x921CE5C4678A8A37ULL, 0x3832798A5ED5E474ULL, 
            0x81F011BC6961D7F7ULL, 0x7E147461FD124D9EULL, 0x1EEF6D1AB7955CB4ULL, 0xFD587C7E1EFE4CECULL, 
            0x6BD08BE91F5C5008ULL, 0xBF81B7F7E1A69980ULL, 0x434D9CB8DB2007BFULL, 0xE894EFB25B750742ULL, 
            0x6DD80B4136E31C8AULL, 0x129A22081B57F8E9ULL, 0xDFBFB8A37B1B8FA6ULL, 0x6A3CF5ADFF5BFC10ULL, 
            0xF4886113438C77C0ULL, 0xE4495B8B83EEBD32ULL, 0x13406DC573569880ULL, 0xAEFED9615AE2A5D6ULL
        },
        {
            0x68138057BFF0946FULL, 0xE7860F711D80237AULL, 0xAABE8F57F8C561E1ULL, 0xE394CE1C9685A575ULL, 
            0x685608620CF1DE75ULL, 0xA90540CF397D9138ULL, 0x8273A65F2BC9DA9DULL, 0x9262958DE198CC2FULL, 
            0x52A96AF77B08A22CULL, 0x4633C86FE7F86382ULL, 0xF5A787E2A76D842CULL, 0xCAD9EEF5A0622B4AULL, 
            0xFC69DD78AE2C680DULL, 0x714A28DD3FEE6294ULL, 0x1A36DDBF22E16D21ULL, 0x3F37B39FA7845069ULL, 
            0xDE265A6A356D7796ULL, 0xBDD323D933ADE148ULL, 0xE198DE1EBB4CC7D8ULL, 0x6E82212441322AFEULL, 
            0x6B057FB16BE95F32ULL, 0x7E12D8DCD1510D8FULL, 0x2F92679D6BEE4240ULL, 0x785CD4932B259310ULL, 
            0x509918D6269E2F3BULL, 0x68C4A45938CD7E93ULL, 0x3C2FC0FE3D023CA2ULL, 0x2EA09A07AFFDA0E4ULL, 
            0x9DBCC17577A61832ULL, 0xDB5BDACFCEC79A40ULL, 0x2D2FA334F1DEFED5ULL, 0x6B009E2F9A8E2FAFULL
        },
        {
            0x899833444B238AF0ULL, 0xAD73DDF3821A4AF7ULL, 0xD3493C7E72F176ABULL, 0xF9D965396593340EULL, 
            0x0531952DC3B1B233ULL, 0x0FA4CABF85ABC1A5ULL, 0x3EEB08C92DD7C379ULL, 0xDAD3A130EA1A89DFULL, 
            0x1E94D30837CAFA5FULL, 0xDA51D13EAFEBEAFEULL, 0x741BCA282A3B7067ULL, 0x05816CD836D5CEDBULL, 
            0x0A77BA129D68B53AULL, 0xB82E98DC1B0B81A5ULL, 0xC556872FC75E1EF3ULL, 0x61A2837B2C9F2DD0ULL, 
            0xB688D910381C0B70ULL, 0xD7E60E6C7813516BULL, 0xA2EE8F3413EFF180ULL, 0x5B26541D41B7F907ULL, 
            0xD2C5E6451D140CA2ULL, 0x4371E724F876E5EFULL, 0xFC0380521B09FB4AULL, 0x76AE688C6BB5D577ULL, 
            0xBBBF3B933FC23A81ULL, 0x82301241079B8737ULL, 0xBDD7645F6E304529ULL, 0xEB0945AA40DF8147ULL, 
            0x6103722A19F4DCE7ULL, 0x1312FA7EFD4FF414ULL, 0xE77AA24FF16B8318ULL, 0x6EABA15931648D19ULL
        },
        {
            0x84D3ADD7F3684669ULL, 0x124C774E89CABDF1ULL, 0xA1C72F10AA30490FULL, 0x4C1A8722209756C2ULL, 
            0x993234F1B2BFA577ULL, 0x87856CB98116304FULL, 0xA9CC9C7925335596ULL, 0x4B01C10CE0DB4446ULL, 
            0xEF6E6D7882B9DF56ULL, 0xDEB953EA2AAE2D74ULL, 0xA7B43242D34DBFE9ULL, 0x02A5B226BDE776F9ULL, 
            0x7DD96B62E04DCA08ULL, 0x6DE77019DBCC908AULL, 0x4B8A86DEAE723764ULL, 0x7C098B5BDAF7BE46ULL, 
            0x08B4E52915C8E96BULL, 0x948BEC0BC96879F1ULL, 0x0F4027613D61C580ULL, 0x640DB17B1D4B04B2ULL, 
            0x88A3AEA49AE9E75FULL, 0x484A99C589F1DCA3ULL, 0xE101F5D687E42A59ULL, 0x40C5688EA7753456ULL, 
            0x27A9D4F5304CE75BULL, 0x8F047D8791C3AE41ULL, 0xA2184D3302D0E64DULL, 0x7215E9537BA40B2CULL, 
            0x4C8A07B58DB460C4ULL, 0x28381686B04B7625ULL, 0xBD72F5240169AC69ULL, 0xC170FCB96BDC3D8AULL
        },
        {
            0xA1A27411ABE2671DULL, 0x10B484F881B33E16ULL, 0x3FCC9AE98EFC2CBCULL, 0xD48547B702055852ULL, 
            0xD42C4F21D3DC503CULL, 0x96CA1121D03D4CF4ULL, 0x219A65A71ED4DCD3ULL, 0xB52A2CABF40630B1ULL, 
            0x21A582EA9ACF561AULL, 0x23DBB9498055BBA7ULL, 0x9D95791E5B2107E0ULL, 0xFE54BDDF0E878BA1ULL, 
            0x4AD9A3958C325B67ULL, 0x5ECA6C06C37C29F4ULL, 0xF145BC21AF29032AULL, 0x179C487CEB117293ULL, 
            0x9E283D19636131E4ULL, 0x9D46E01FE3591D0BULL, 0x3C132D2F9BFAADB0ULL, 0x71ABA1618A7067ADULL, 
            0x4FEEC807E6F9A999ULL, 0xE4E535914135CD85ULL, 0x586892681A9EEBA7ULL, 0xF11C4EDD6E6A08CBULL, 
            0xEAF11E51B9D51374ULL, 0x04870A72CCA0E2A5ULL, 0x210EA922175565D4ULL, 0xB69CBC190872011CULL, 
            0x7D9011438C0AD079ULL, 0x3F8607A168FB777DULL, 0x51A94901592584C9ULL, 0x1AE64595EE5398FFULL
        }
    },
    {
        {
            0xE7120959587AA13FULL, 0xE960E7D44A20344FULL, 0x1423E80CFB61F36EULL, 0x6E436D340E9FABD0ULL, 
            0xD01C2802091FCACDULL, 0xC8134FA9B933FE2FULL, 0x5F78E942BCF4CE7AULL, 0x3FBF73BAFE3BC242ULL, 
            0x0D11B732E04E035BULL, 0xDBD00B06D12CCDFEULL, 0xB9E6B85932957920ULL, 0x3AF596FAAFC86F51ULL, 
            0x83FE3155ACCB2B42ULL, 0x642B286515B9AE28ULL, 0xEB54B9C46A7872DAULL, 0x1F1CE9ADA7CA3FC5ULL, 
            0xB7F62591B9EF70A2ULL, 0x6DA8FEC9E60F8955ULL, 0x363560116F1970E9ULL, 0x90575D5FC49E28DFULL, 
            0x652383FCDC71C9A9ULL, 0xE89CBE5FAA3E1794ULL, 0xBE216C96BE454471ULL, 0xC9C91EBA5D0C6A94ULL, 
            0x19A7B6E86000EB47ULL, 0x57DB2E8FCFBABB1DULL, 0xA3D04641CD58433AULL, 0x7DD5A14BC85BB38CULL, 
            0x8F805CEA6EF525E9ULL, 0x47C8E807311BF4E7ULL, 0x2CDA9BAA8045E429ULL, 0x4964B19C25ECA69FULL
        },
        {
            0x5CC94AE141B040C1ULL, 0x85E6083EBDD24E32ULL, 0x275FFACD34159E8EULL, 0x9530D4E4CA1EFF2CULL, 
            0x47D45ABFA9C536A0ULL, 0x67927A6F7793F7E0ULL, 0x71271A68C644C45EULL, 0x70FDAC6A97E78C9FULL, 
            0x96D3CFBBCEE1F004ULL, 0xA1187CD7FDCCED4DULL, 0x14D287C22465CCAFULL, 0x272DD6691E531D92ULL, 
            0x6BCAD0BA0BFDC0E3ULL, 0x8DEC7BE2FC315A2DULL, 0xF267F2AF47CE7851ULL, 0x8A8287D17A41EE17ULL, 
            0x242AD1BF88A9D1BEULL, 0x9DF6FAD08AD063A8ULL, 0x126269465D03FEA2ULL, 0xE551EEE83CAA3B83ULL, 
            0x1015F2DF1AAFB097ULL, 0x9273B417F77D5EF4ULL, 0x736822B5C18062C7ULL, 0xD7F2F132DC13255FULL, 
            0xDB5CB1CA76BCC27EULL, 0xA294FFE9C96A6F33ULL, 0x5EAE9C7F0513CFF2ULL, 0xCA95426DD9F44F16ULL, 
            0xE02F415701AF22B8ULL, 0x91BEAE2DE86EE31EULL, 0xBC574748EE56602AULL, 0xEC22E84A9B69BA39ULL
        },
        {
            0xC90D74DD05992F1EULL, 0x1D2D914324DF1781ULL, 0x8A2889914BD474EEULL, 0xBC48A34023A95849ULL, 
            0x8CE9DA62C4CBF2CEULL, 0xBF3B277689E2708DULL, 0x8CF99912444AC211ULL, 0xE92DFEBA5D362561ULL, 
            0xB9C91F950B8ADEB1ULL, 0xE9798196F433CA20ULL, 0xEF65390C5840152EULL, 0xD2C9CBA09F057FB6ULL, 
            0xC60FA45309D1D21CULL, 0x0141091ECA4796C5ULL, 0x1CE062962274BF61ULL, 0x3DFE0DC60C5791BDULL, 
            0x5A294E1BD00473DEULL, 0x77BEAC9EDDD0BF29ULL, 0xB66126431FEA1CD2ULL, 0x5F5AC925B5DEC043ULL, 
            0xE6DBD7C76EDD384BULL, 0x47CFF289D4DF6C49ULL, 0x7BF1139F6C7527A3ULL, 0x5426D0EA46F32050ULL, 
            0x65CEA7040614ED6BULL, 0xC66BECADAFC9DF2BULL, 0xF26C71EABA678A7DULL, 0x9B330EF39FDF8F02ULL, 
            0x99032A0F7402CC41ULL, 0x502BD7A111B047C4ULL, 0x85F0BE417347F319ULL, 0x35050D1E5D5CB1A0ULL
        },
        {
            0x9620350C985A9A7CULL, 0x1AABDB680D98E7C4ULL, 0x0D2ADC81CC516FFFULL, 0x08520C7AB828A96DULL, 
            0x9A58ADF7B76E8061ULL, 0x45B018F77AC8187BULL, 0x5980B1279ED1503AULL, 0xA54651FAB4335E59ULL, 
            0x3DED39849D7DACB3ULL, 0xDF9EB831D28793B5ULL, 0xD08BE173DB150E1AULL, 0x1E97B2A5E9B7CC79ULL, 
            0x46196ED5C4D069F6ULL, 0x398F6F17C6585368ULL, 0x2E6424CFD393CF15ULL, 0x46CDA0EE02E23256ULL, 
            0x99E500733EADF4D3ULL, 0x4D3B5FE284A4F670ULL, 0xD064602333FF2E87ULL, 0x17ABF0B20985F069ULL, 
            0x7D1145C34C9E94E3ULL, 0xCD7C3CBDA7CF8B47ULL, 0x0F836E34352E8D0EULL, 0x5B11CD17965C88ADULL, 
            0xE815C1F261A5264EULL, 0x9155328C131E9087ULL, 0x375D95D7EFA799A7ULL, 0xBEEAECCA60EF3635ULL, 
            0x9B8417D974CEB6FCULL, 0x99A118462DC11DA4ULL, 0xCB9C86D2318CACB7ULL, 0x7B651C4857C21F95ULL
        },
        {
            0x1E371B4CCE799D2BULL, 0xCC7EA6A570933DB8ULL, 0x080ABE0FE4402831ULL, 0x71A8F2FE72FABBFDULL, 
            0xF2724CE81D4D1C85ULL, 0x1B97C5758AC66EADULL, 0xAFEB1CD82D0D68A3ULL, 0xB46A04DE0E48E5CDULL, 
            0x71EF163CADB449CCULL, 0xBD41F29F698975FEULL, 0xEF0BB545F241BFC4ULL, 0x9DDB52D735AAF5C1ULL, 
            0xA5B44B6A10B0DA61ULL, 0xCC14F53A3D71F007ULL, 0xD4BCD6D2C011DAF1ULL, 0x4A7DB9BAA826ADE9ULL, 
            0x2BC1C6E3FB85E6D6ULL, 0x5F8BB0A6866C5283ULL, 0xCEC69DC46D3B6625ULL, 0xBF7D1E2231D8B4ECULL, 
            0xAF1A15B8F2998A08ULL, 0xFB44F8A5E282FCC9ULL, 0x93ADEFE746E60FA6ULL, 0xCE09948B317DC15BULL, 
            0x315AB1041AC998F8ULL, 0x1FB77D71CFCD0188ULL, 0xD309CB9E1AAEF199ULL, 0x429AE2573F072F95ULL, 
            0x062BAE3FA061A6B4ULL, 0x07A77C0E79C9726AULL, 0x38DDFC05F35B8F97ULL, 0xFA53FF4B91D23D10ULL
        },
        {
            0x2CB009BA48778924ULL, 0xDAEC673A03679DC0ULL, 0xE46343308A0E0C67ULL, 0x897864EF4133250CULL, 
            0xB5FEA9F82E1CA703ULL, 0xEDE91034B22DE177ULL, 0x75E76DEC8B6F3BE2ULL, 0x9796BFAAB2A3EB9AULL, 
            0x581BE1BF35F2F79BULL, 0x257E891FF3B0A1CFULL, 0x2F5BF80A2DF1F74CULL, 0x3644A2759AF5CBF5ULL, 
            0x98EEA45348B53297ULL, 0xBC36602B23B32B15ULL, 0x2910FA04F637DD20ULL, 0xB4F4C6140B3A5C61ULL, 
            0x8ECF4C3BC1A17C48ULL, 0xD5CC9899FF7E841BULL, 0xE9782E35D62DF315ULL, 0x3E154982308860F6ULL, 
            0x06C8F620A9F0E128ULL, 0x72BC7356EE834168ULL, 0x1190B47604D392A6ULL, 0xF2C367C62820D7FBULL, 
            0xC6DA494A1216A97DULL, 0xF5D002B505493097ULL, 0xF8E2ADFDF9B5CDA8ULL, 0xCE25C786737183B1ULL, 
            0xC0506E36DFA5E3C6ULL, 0x8592607F656278EDULL, 0x7F5F171B115E9A2DULL, 0x6FB50F74643ADE2EULL
        }
    },
    {
        {
            0x85E6699D6743E66FULL, 0x6D9556D005A43396ULL, 0x22508D2241774F4DULL, 0xE966C8ADBD360CECULL, 
            0x4DD2A29A68A96FC4ULL, 0x1B93BB16FEBF042EULL, 0xA071C5F85DC18428ULL, 0x868F215CE6A0D724ULL, 
            0xB8C241703FF57C75ULL, 0x6B870DAA91EEF84AULL, 0x3E1D756C60542942ULL, 0x46CB949D786A84A4ULL, 
            0xB4AE85FF9569296AULL, 0x13EBB68C4708F820ULL, 0x26EAB3468BDE09C9ULL, 0x038EFC75121C9545ULL, 
            0x0AF4BE9C16EF7A0EULL, 0x4095C22471989D28ULL, 0xA8C830A917B2EDA0ULL, 0xFF3530649D1AA42FULL, 
            0xB193F9D645D8DDBEULL, 0xFB1E8159CAA23839ULL, 0x25F898B8860B2FF6ULL, 0x28943A1A1CE2639AULL, 
            0x1289F4400A3A2344ULL, 0xA94CAD3F71E2F96DULL, 0x193E971C96B99AD6ULL, 0x641EA847597B1A01ULL, 
            0x34A31694BAF13559ULL, 0x2729B705781D6837ULL, 0xF799B7C33ED56BEAULL, 0xD574FA0A8297C8BEULL
        },
        {
            0xDC2C4973FC1EA11DULL, 0xE1C961DE1F5365A4ULL, 0x087FD8BDE45BA005ULL, 0xC471EA9FDA7DAE1FULL, 
            0xFB0F7D2BE07A59F3ULL, 0x763B96D7DA0B95A1ULL, 0xCDAA167205CADDC3ULL, 0x4883F65AF6743A48ULL, 
            0xB1F7C1E3B2FC5DACULL, 0xEE388AB1B0F6930FULL, 0x5C971598C89819D9ULL, 0x65018398AEEB77D3ULL, 
            0xA203DA2202B4D505ULL, 0x72BDD07B1BD29999ULL, 0xE1489AE5FBFFE665ULL, 0x5D31AF8A6D92D929ULL, 
            0x76AE6E5CAA6B3FDCULL, 0xF8F94C14D95DC034ULL, 0x6C5942D67E247083ULL, 0x0C4E5D032BC12E70ULL, 
            0xD5431B50BC3FB5ECULL, 0xDCD3DC6DC61F2F5AULL, 0xE02DD9A94480C996ULL, 0x970F44DE768B868FULL, 
            0x5DE24A0993CAC000ULL, 0x1C058FB44074264FULL, 0x2F9F8C7D98DC7872ULL, 0x7A4D9BE712D4D5FDULL, 
            0x1FF7707F71C75B4FULL, 0x7BC70099A25233E3ULL, 0x7564016E1D56BE32ULL, 0x3268790F4D4FE33BULL
        },
        {
            0x6BC15FD2D3CBAF78ULL, 0x2AFFA51ACB7AB1AEULL, 0x867D1B10977BF65FULL, 0x3200BB9897683CD9ULL, 
            0xA9ACED54282023D7ULL, 0xBAF70F609F2B2B26ULL, 0x4E0FF6DC4F41A557ULL, 0x3307BED8D35B19A1ULL, 
            0xA021E93DAE59FC90ULL, 0x8AB6A730990EBD9CULL, 0xB3A51F84D39C580DULL, 0x11C8013284FC633BULL, 
            0x6B9E39B97CE7DDDDULL, 0x4F621E1F465E05D6ULL, 0x4CE4703C1FC2AE34ULL, 0xEFFF2460251C0AB5ULL, 
            0x1641B0829E42EA8BULL, 0xB8A77B6FAD1E33D0ULL, 0x250B0161ACF564BDULL, 0x8B14DFE5911B7AE5ULL, 
            0x5112A2512CE69AA0ULL, 0x143B2F48C0FDF339ULL, 0x461DDFC84B18283BULL, 0x580BF35DAD3DF039ULL, 
            0x7381BE7A30C6D16BULL, 0x25712E0061597EEAULL, 0x23BA0795B9434447ULL, 0x46F796C114AD5555ULL, 
            0x33A92145BBBF2701ULL, 0xBCA7CD52E8C89EADULL, 0x09EB999B10355FD1ULL, 0xA15AE2C920393CFBULL
        },
        {
            0x16AC70367EE5B741ULL, 0x53D750CB656E4D09ULL, 0x69416D14316EE40EULL, 0x4AF74978E75083A4ULL, 
            0xF2AA095578F969A4ULL, 0xB38103416EE9341DULL, 0x1E9A779F4E1E7546ULL, 0x79F01009A45A0E4DULL, 
            0x6D8A430E4E066F71ULL, 0xDA200F32E8D8087DULL, 0x217C4685AC393A89ULL, 0xB64569B20D82C859ULL, 
            0xF8286C7083CF327DULL, 0xD1D4130F2021887DULL, 0x0E07A65A4C0136A3ULL, 0x1E8EE5C737254DF2ULL, 
            0x66B7FCC980045CE6ULL, 0xC2DC877C7CDE3274ULL, 0x0B9FB22FA5573274ULL, 0xC3215AAE2C05259DULL, 
            0x84F0FF7A5DDEA1BDULL, 0xE15B810700F5FD68ULL, 0x760892DE9F474F55ULL, 0xA900BE4955F754A3ULL, 
            0x242BD38699F26732ULL, 0x2F7BF37DBABA1407ULL, 0xBB6A38C23254EE13ULL, 0xCFD31CFCB6CF9AB9ULL, 
            0x4CA1C042E3714019ULL, 0xFF8B702626DBD14CULL, 0x34811D5DC2C3BD29ULL, 0xC90E272E1821C979ULL
        },
        {
            0xE16AE80BDE58F5FEULL, 0xBC3F3F61949303F9ULL, 0x6226751CF70B6E83ULL, 0xC48DDA5F17BECBA0ULL, 
            0x0E83224ACBC28D9FULL, 0x738A79F9788ABD47ULL, 0xD7CCA504235F3C15ULL, 0x8BABA7ECF1242487ULL, 
            0xEE134FC3E91A49C7ULL, 0xB77B14805E1CA18CULL, 0x06638ACE9798C9A9ULL, 0x49A9F6BBAFD95DD1ULL, 
            0xF585A3966B7707B0ULL, 0x4EFF91E7F17E0942ULL, 0x09FDD721729352F5ULL, 0xD05D85F51D1CBECEULL, 
            0x65E003D2D3D96AECULL, 0xCA110634AF7B1538ULL, 0xEAE8AE8CC63A14D5ULL, 0x5A1E7B7F3715FD88ULL, 
            0xABDB7A8098233947ULL, 0x0395D4BE93129BE7ULL, 0x821A9A1FE642F42DULL, 0x90BFE7A05C48A94DULL, 
            0x094785F8AB6E8570ULL, 0x674DA6ED3D162716ULL, 0x777A419E86492587ULL, 0x1DDCA6E02EB13564ULL, 
            0x673F7B3A3C3625D8ULL, 0x3E060EA9CD404A2AULL, 0x4C975783C97831ABULL, 0xEF5028177780F60CULL
        },
        {
            0xC8FA479BE30BA403ULL, 0xF40E89F020A3F51AULL, 0xD6FF9FE72829780FULL, 0xDB74548F845DB6CBULL, 
            0xFAA3489AC5413631ULL, 0x71639CD01FB1FD08ULL, 0x08FE12BFEB37C884ULL, 0xFEA2CA9BB550F19EULL, 
            0x2EF735FE18EE127CULL, 0xFD6435581CFBD5D0ULL, 0xD151EFAB2DCBF194ULL, 0x07EEA7EF706AA55DULL, 
            0xB46185DDB5854723ULL, 0x748FE5F67986A841ULL, 0xF4A35C8D8CA2A410ULL, 0x9F91989C697CC1C9ULL, 
            0xE20A3C6BCFC08FFCULL, 0x5545B25F5569A1D5ULL, 0x419E51A5CB1D9C87ULL, 0xDB88527D40FCFB22ULL, 
            0x46AD776127C5A762ULL, 0x5742E297C3AE292FULL, 0x528E3F70253B3A3EULL, 0x486199926386F509ULL, 
            0xD46EFFABD26E8282ULL, 0x1811B0ACBCDD81E9ULL, 0x2F8CBC784EF27651ULL, 0x364A5DC03EC03576ULL, 
            0x294550970286004FULL, 0xE716E6B51CD71EA5ULL, 0x29F43A3576497193ULL, 0xDAAE105387C5017FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseCConstants = {
    0x6F21426B29969F21ULL,
    0x635AF832A28E4ED3ULL,
    0x346E64DEC8BD0BEAULL,
    0x6F21426B29969F21ULL,
    0x635AF832A28E4ED3ULL,
    0x346E64DEC8BD0BEAULL,
    0x0FB383D09476697BULL,
    0x6D6AF51741B9C4C5ULL,
    0x29,
    0x9F,
    0x7E,
    0xF5,
    0x72,
    0x76,
    0x3F,
    0xE9
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseDSalts = {
    {
        {
            0x7F1CA30723EB0349ULL, 0xF19959556797466DULL, 0x2993D8E795322C1CULL, 0x4BB3D11889A1ECB7ULL, 
            0xE97E5DA764D4C4E0ULL, 0xDEF58B1DF88BF315ULL, 0xFBE6C68FA800353BULL, 0x5981B67D04D36EDEULL, 
            0x30F90193430024FAULL, 0x187571A9F3E69BE8ULL, 0xDB09116F363D4385ULL, 0x0AEAA09066B5D3CCULL, 
            0x80CE034A4A45A70AULL, 0x217520D7F08A6E01ULL, 0x0B2AAB49A257EEBBULL, 0x1BDFFC3FBE4E6A40ULL, 
            0x06563DC97036D248ULL, 0x2A255F3FF035CC1DULL, 0xFB2086922AE08A09ULL, 0xD5165FACB966275BULL, 
            0x27553ECF48310FE6ULL, 0xB3CD44A1CBD20B50ULL, 0x778A9535AE860392ULL, 0x1C5005B797B9FCDBULL, 
            0x07BF6C639FC773E6ULL, 0xB78DBBBFD01701D6ULL, 0x4B7526EC8E5C2629ULL, 0x6101D9117866BD9DULL, 
            0x15CCADBC84C6380FULL, 0x39FE600F95DEE350ULL, 0xB91C29FDC5DA0FFDULL, 0x98DD7FE9277BF45EULL
        },
        {
            0x06263C1BEE34133AULL, 0x7F867E20E00C7827ULL, 0xF85DF037C0420020ULL, 0xF798FB48C50D987EULL, 
            0xF3CACD4C85C1C0D2ULL, 0xCF29567E99F43BC9ULL, 0x74A26BCA360DDA93ULL, 0xD3137D93A9950515ULL, 
            0xE17EEF5514F32E6AULL, 0x57961D7A96D84432ULL, 0xE2C52DF29DD8771BULL, 0x7ACEA4003F180206ULL, 
            0xD80F1BB40980DCFDULL, 0x61FA578F8AA6CF56ULL, 0x5C1A0CBC613117D1ULL, 0xC6132DA38FFEB452ULL, 
            0x50F253383F61C602ULL, 0xD76369EAB4E8D4F2ULL, 0xCF943AF8BAD54FBDULL, 0x5C0FBB67141843E3ULL, 
            0x8FC381A231BB2908ULL, 0xBA3FF878963329E9ULL, 0xD661B435F9345267ULL, 0x905CA3367D35F813ULL, 
            0x56A5DEF29781097DULL, 0x2C8819027E1CB179ULL, 0xEE2164E072AA7393ULL, 0x08A8AA5B1B16E295ULL, 
            0x37A8FE0B09ACD737ULL, 0x0D801D6BF099A2B0ULL, 0xF9E8CC2792F46085ULL, 0x74D1144E1C84CE49ULL
        },
        {
            0x00B77B4A9C13A68CULL, 0x6D305B2A7813C6C8ULL, 0x4A084B3054F802B2ULL, 0x25469F37AD105C26ULL, 
            0x49BBD6B781406E4EULL, 0xBF5A193A45BF6A5BULL, 0xF958000E99220093ULL, 0x6EC3BD63D381A1A8ULL, 
            0x547506C73D4BA390ULL, 0xD6FAE9B978FA53ACULL, 0x3E5AE4FBF2CE89F7ULL, 0xA997D95218F2E0F4ULL, 
            0xD69BC285DF98E9FCULL, 0x62F53803395BCE8FULL, 0x9A59ED74CB651DF8ULL, 0xA3290EFAFF8D8DE8ULL, 
            0x801ED99A16C196ECULL, 0xA076C8A7F75E2CDAULL, 0x85FD70DA6F613FCFULL, 0xBCA6CBB5B3ABCB65ULL, 
            0xD767D233F364A665ULL, 0xA25C50FC7685B6A0ULL, 0x297BE4A1BD7A7610ULL, 0xF52819A621280DABULL, 
            0x078868924E45B158ULL, 0xDBF2FD5B48005947ULL, 0x5CEF5F779BA948D7ULL, 0x0611FAD6B9582737ULL, 
            0xF4F04AC352FD50ECULL, 0xFCE9FBAB70891C4EULL, 0xB8473AB4DBE77BE3ULL, 0xDE93E9277B6550EEULL
        },
        {
            0x9663064E5A44E03CULL, 0x7216CE913000F4ECULL, 0xFCEE7468C8B2EFB2ULL, 0x45EE62F64152DBDFULL, 
            0x1A96555B97D3C71FULL, 0xC10EF593468719C1ULL, 0xD5D3F841B1C26689ULL, 0x8AB49B3952E6B927ULL, 
            0xE809B484A33986ECULL, 0x698DB86C2E032BE6ULL, 0x996396766FC60F7BULL, 0x4F90555339CA78C1ULL, 
            0x0F89271245980A6CULL, 0xABAA3BAC10CAC922ULL, 0x4D06C68BE7EB9543ULL, 0xCB66B237014B9224ULL, 
            0x7C0D854064F8319CULL, 0x70A5750260F7C652ULL, 0xD2C72B2D8F0B7756ULL, 0xBFA7528B3DC5D87DULL, 
            0xF7FED4FE636AC98FULL, 0x851E9871A2DF2C9DULL, 0xD3AD7B5AF15618A1ULL, 0xEFAAC5DCC7035DE0ULL, 
            0x2139ADF5B7C997E6ULL, 0xF14C538B515E9975ULL, 0x92A26ECD225EAEEEULL, 0x83A907D313C5DE95ULL, 
            0x2165373C2C86059FULL, 0x499B9FEAE5476123ULL, 0xB53283609CA9D8F4ULL, 0x931811A99F7C249BULL
        },
        {
            0x65A3688C31B02458ULL, 0x07D9A4D3E1625DC2ULL, 0xAFC951661974FFFCULL, 0x7C7BCB07CDF3DA4CULL, 
            0x2CBC945FABBCA7C0ULL, 0x57C8E4AFB0601687ULL, 0xEF9A301DFCA2BA28ULL, 0xD5E76A22AED1FC3AULL, 
            0x77BE5F98AFCEF1B5ULL, 0x7ABA15FEFF3B747EULL, 0xE064479DC6F297D1ULL, 0x5CFB9A400DFF6F62ULL, 
            0x6D65FDB2A50406FEULL, 0xD4DA90FF136197F2ULL, 0xDE74D4A37F74538BULL, 0xF3F2DB0CE3E86AE7ULL, 
            0x88278EA830F4EA3CULL, 0x49856728E556A17DULL, 0xB6E042E218AC707EULL, 0xDB294009FDD53ECFULL, 
            0x5D8D13FE65562202ULL, 0x484AB21F91457EEFULL, 0xE5B8C7F4253BFC71ULL, 0x04527407F7A76E0EULL, 
            0x662133A72774C101ULL, 0x43BE5A7BF98A80FFULL, 0xBABF34ED89757996ULL, 0x8233DE483DDFA595ULL, 
            0x666971711A54E15BULL, 0x2F0C173A0E9359CCULL, 0xC972CBB8D42F9CC3ULL, 0xA5993DF33DCEDA1EULL
        },
        {
            0x9B84E1AFEEC1E7FDULL, 0x3B016B3E8D9EF0F5ULL, 0x4B6A568B98CC0FCCULL, 0xD3EBF054B47A4A21ULL, 
            0xAC6DC09CE5049CD3ULL, 0x1348F9D0F6717A39ULL, 0x22848E97CF00D60EULL, 0x98CB82C2528FBB02ULL, 
            0x62CDB0A5C2EE649FULL, 0x251FB4C103DBA344ULL, 0x4061278B947EBB69ULL, 0x136DCE0006034421ULL, 
            0xF2A28CDABECABFE8ULL, 0x142F684AAEBE795BULL, 0xECBD29ABE3F434DCULL, 0x3AB2A6E9C5A0DF75ULL, 
            0x6DDCC3CAEE7FE8D2ULL, 0x8674603B4E9249D4ULL, 0x4836390D964BA35CULL, 0x93B333576424139FULL, 
            0xA3E1C65F271EA34EULL, 0x0A431E6CD8F1ECD8ULL, 0x8704BC104A2469CEULL, 0x90265F7BD484A708ULL, 
            0x805C8173C98912E2ULL, 0xEDF359B91223644AULL, 0x1322EA6FDE26B486ULL, 0x60364B1C91C0FE7BULL, 
            0xF5E4B57CC9A5B436ULL, 0xE580537ADDA8B51BULL, 0x6F79CCB47165932EULL, 0xB5732E489BD9F327ULL
        }
    },
    {
        {
            0x26A30420DCE4D489ULL, 0xB035E651035E1E9BULL, 0x94F26F8CFAB1DC96ULL, 0xA36CC35B6AC7F1EAULL, 
            0x87569FE23CFEFE86ULL, 0x087DB27A50423097ULL, 0x4E7205F115897EE4ULL, 0x97AB311C2FC47D7BULL, 
            0xB7331D229FB78E08ULL, 0xB6C7FFDF6440FB4CULL, 0x308C2370183F8DDEULL, 0xB654C8824DBBFDF8ULL, 
            0x21EA1B9939B30795ULL, 0x278AA176588EBBBBULL, 0xF6F9C65790AAD55EULL, 0xBEBE8520C3153C91ULL, 
            0xA952F001B0593EE7ULL, 0xCA84F70ED2C1C4C2ULL, 0x0937E2E52B91557EULL, 0xABB9465833BF018EULL, 
            0xDFD1CAB9F86B9893ULL, 0x25BFE30D609DFCB1ULL, 0xEB8498DE11762977ULL, 0x7ECC44C868650180ULL, 
            0xE33D3B3941955441ULL, 0x6002A334E4DB8DE3ULL, 0x2BB3B7DEE1BC5D80ULL, 0x772F77A261FB6849ULL, 
            0x47A06B5423C2AC5EULL, 0x67853B5D8B97D6B0ULL, 0x535DCFCD37181A89ULL, 0x10EFF0C31F0C63C8ULL
        },
        {
            0x11502EFAF325264DULL, 0xA3C08790116DBDEDULL, 0xEA3E6C89B7A40027ULL, 0x4ABF720D7093C8FCULL, 
            0x55412EE4001CABA3ULL, 0xF4C80A2C366AF5F2ULL, 0xAC298F4E7D21C23BULL, 0x71BA1126C15B11F1ULL, 
            0xEBC98570777316AFULL, 0x315EC4E70C9B2A66ULL, 0x50022BB5797FD8FCULL, 0xF1DE1C59E08E7AE7ULL, 
            0x28BF64108660D19AULL, 0x509645FEDA1FB697ULL, 0x0664220EA9F81370ULL, 0xC49C37486FD1E56EULL, 
            0x81C48A9D34EBB56EULL, 0x6FDCDA442F64B8C2ULL, 0x5E5EEB8E9AB0A641ULL, 0x79C94BF673F8BED4ULL, 
            0xFDFF4FB0238499EFULL, 0x52031E4E722B02F0ULL, 0x80BCE75486833666ULL, 0xB2BCA0E1F9B44C48ULL, 
            0x4DCDA38A9A17F3E0ULL, 0x86FF2C0E3994C96CULL, 0xACAD146E86A55242ULL, 0x17FE1F8D172ABCACULL, 
            0xCE32B7C4DADC4F0AULL, 0xEA0218E9820790D5ULL, 0x78CCAC1621671C23ULL, 0x5043C84FB2704C20ULL
        },
        {
            0xB4E60B7E08FECD38ULL, 0x108229BF6C6CC626ULL, 0x603E1498208B109FULL, 0xA768C91A3336A4C4ULL, 
            0xE5394516E0DA48EAULL, 0xC3EAD72215F33079ULL, 0x3193BDB54C599569ULL, 0xA95D8C88F5E3AAEAULL, 
            0x53D535FD0597B8F2ULL, 0x1621F3842BC1E97DULL, 0xBDB2F7188027413AULL, 0xD1602AD89F50F533ULL, 
            0x1BCBB852DFFF3744ULL, 0x51633B67977B96F0ULL, 0x8184826DB5BF89ABULL, 0x285DA05B7747F18BULL, 
            0x581FB0F2EEDF1FB2ULL, 0x24EAEB8E1AB4BCA9ULL, 0x61360FB6E592A8ACULL, 0x2A919F0F0F1BAACAULL, 
            0xB0A2A8844EF1CD5CULL, 0x9283D2954804F6C9ULL, 0x211AA14895C8D2A6ULL, 0x8B7A8066A60C9E8EULL, 
            0xFB79C5668C24E45DULL, 0xA0A3287086F33A50ULL, 0x5E3C6DC9D50CCA18ULL, 0xEA784BFA366F1123ULL, 
            0x24CCB80BCF5A4E3FULL, 0x8D2B0BE2C9E5FB36ULL, 0x6418A78B1F5260A4ULL, 0x827A9260B55C7E4CULL
        },
        {
            0xD77CCFBD2F793B4DULL, 0x5B2E523FB7B1B839ULL, 0x4C1A3F2C0BF7BD96ULL, 0xD83E1D172F9DD8BFULL, 
            0x33AC15A66574D6CBULL, 0x15CAD10E589422E2ULL, 0x32983B9DBE0F3D1CULL, 0x82361DBC69625A45ULL, 
            0xD5945AF72F15DF87ULL, 0x18242062695BAB69ULL, 0x2DE3EE1D50E6B7CCULL, 0x82E6975B9A024F92ULL, 
            0x70489D3A132ABF13ULL, 0x51EE612B5AE52A6BULL, 0x2139AB20A5B3EA6DULL, 0x2537F3001A9F272AULL, 
            0x50B76A3704A6E1FAULL, 0xBFA372135DA1CC29ULL, 0x2E170F5B9E73CA9CULL, 0x284A4C561D585ECCULL, 
            0xA6CE54242F44EA85ULL, 0xA7D974D2AA244FF6ULL, 0x377F5D4892144104ULL, 0x2B9F7317BC728296ULL, 
            0xA223C129199FCD14ULL, 0x7036CDA34E166657ULL, 0x8C21CD98AC317B90ULL, 0xEA085C7B4081C4BFULL, 
            0x0129B648D8A7E945ULL, 0x04D9B13CADA746E8ULL, 0xF1B10074488B6434ULL, 0x32EFFE59ABC3E969ULL
        },
        {
            0xC3B4FAB60FCAAA2DULL, 0x0775FA9D1B2E86ACULL, 0x595415B7376262F3ULL, 0xA0FBC922468C4BCCULL, 
            0xC2818548E2C386D5ULL, 0xC4B5044FEF1EF79FULL, 0xD8D3BC63AA475562ULL, 0x806E8FD8529E47B3ULL, 
            0x5565ECFABCD1808FULL, 0x0D6F0D9DCB79BB49ULL, 0x665DAF9173CAD084ULL, 0xE13EA80C20DF1D92ULL, 
            0xFAD03EBEB1C216EDULL, 0xA866FCE099FAFE45ULL, 0xB19EC8B28598E785ULL, 0x80EC49D7FB8B1350ULL, 
            0xB4CFA3976E676095ULL, 0x1E1237A4939695DBULL, 0x1BD3F5869E0EC0F7ULL, 0xE4858434AC69C57EULL, 
            0x7F30DE10FA9664FBULL, 0xD3790B7B94A5AD56ULL, 0xFC0E730E1DD95CDDULL, 0x1CB2DA170BA7BCE7ULL, 
            0x4E6E31CABEB36B3AULL, 0xB10899E033968DB8ULL, 0x3BA548536C9F9DFAULL, 0x43D78D2EA398C245ULL, 
            0x5C14FD56DD3CE49FULL, 0x12A42820BC4829E6ULL, 0x4F3897F91F59A356ULL, 0xB77A62EBCC3B2D34ULL
        },
        {
            0xA657E5CAAA85D7BFULL, 0xBD7B45995266AC8EULL, 0x42D17157F3191433ULL, 0x7BAEF91B4B28C405ULL, 
            0x8502814C8501F08EULL, 0x2FA6191F4ABE8BE6ULL, 0xE36F0E755F3985A2ULL, 0x24848ECF0C256148ULL, 
            0xF616BD8093700507ULL, 0x944482B61655522BULL, 0xC85C5A140C6786B4ULL, 0xE9E2E2CEE858379AULL, 
            0xE2B6375CAD26AA90ULL, 0xA1FC1B427C9A75E3ULL, 0x1F2B251695C9C766ULL, 0x1DC51DAAA1C4FB81ULL, 
            0x6A7044C39C08D1D1ULL, 0x5FDA86D632210606ULL, 0x9E511F56179B68D0ULL, 0xB0249C5E8B30E497ULL, 
            0x72C667C5D50A90A0ULL, 0xD8312960CDEB277FULL, 0xCDAA66D2388EA944ULL, 0x0C90357882925A79ULL, 
            0xDC89ACADEF87B585ULL, 0x46689B7E8391A4FAULL, 0x853B7C27B0082BD2ULL, 0xAC532C3B773A6111ULL, 
            0x599AE20C83340DBEULL, 0x8AFA2B359AF1F74BULL, 0xEBF59B95F6DED66EULL, 0xB84B4A689F07EEA3ULL
        }
    },
    {
        {
            0x6EB3D0DAD9A70751ULL, 0x9C4EFAC9570B276AULL, 0x5A45F8E6D676DC49ULL, 0x20F634D82FEA28E4ULL, 
            0xA7FD3CFC447BDF92ULL, 0x001F7F757749E4ACULL, 0x76E10499E04B76F2ULL, 0x04C0EE65620405F2ULL, 
            0x173C2CA5D9ADE026ULL, 0xC3717900A5213343ULL, 0x3028D004DCE0C6A4ULL, 0x389DBD0BC1033F4EULL, 
            0xB99F03795254ECA0ULL, 0xE6E592A95FC2582AULL, 0xD79D03BF0079C283ULL, 0xE489524D47759D8EULL, 
            0xAF727ACF963B369BULL, 0x0D046E51A3A7AB8EULL, 0xE3E3E5FB0659921AULL, 0x40D691CDD8C941BFULL, 
            0xB4511778DCE1F255ULL, 0x297810402374BFAEULL, 0xB035D7245985A39FULL, 0xAED936797CD87BF4ULL, 
            0x4F0FE7390C76F917ULL, 0xCAB488AA64DC95E4ULL, 0x6A93C098AE99E4B9ULL, 0xC1069F5BDDC74457ULL, 
            0xA652144D1ABD6E90ULL, 0x2ED1160D8C9648AEULL, 0x397379C50984EA27ULL, 0x9D21B394DC5A2B0DULL
        },
        {
            0x35DFED5A5F2D4DBEULL, 0x50ED047B6D847AD2ULL, 0xE236F80B8A5F040EULL, 0x69424594A25840C2ULL, 
            0x8AA2D9F10C27F4CBULL, 0x359546CE866AFE46ULL, 0x59812EC094317E28ULL, 0x0A27F605FC1D26FDULL, 
            0xE3DF65EF56DE7649ULL, 0x232E868BBBD67BD7ULL, 0xC7279EF78F3F137BULL, 0x6F3014023B1981E0ULL, 
            0x3A04D4C10933DDF8ULL, 0x0546A3020FA90DA4ULL, 0xA0CAE8CDBCC29CC0ULL, 0x0FAB29B638F814D0ULL, 
            0xECC2C8CC57F1E707ULL, 0x75F7664A89E692E2ULL, 0xD20710B3A1E382A4ULL, 0xB320991EB059DAC8ULL, 
            0xBEA93FEBF4E98819ULL, 0x4C1ED8B7B8E9342DULL, 0x7079F2D383BA857EULL, 0x774EDEDEC63A4988ULL, 
            0xEDBA7ED2E88FB708ULL, 0x51FE0CA0758FE0A9ULL, 0xA363D5E41A277B39ULL, 0xF61AFC04F85C1892ULL, 
            0x0B9C8CDC26931902ULL, 0xD4DA964C19FD9B5DULL, 0x3C8E04CF0FED1C15ULL, 0x13B771FF29D71F4EULL
        },
        {
            0x1CBEFBCB335FA692ULL, 0x430706BC9EF13FD8ULL, 0x87F8BBF9CCF296CDULL, 0xEC3AB5836D7BDD06ULL, 
            0x6BFCAB11AE82400EULL, 0xC8D765808AEB1F0BULL, 0xB7B3FFF962F1B5ECULL, 0xE0095651B585610FULL, 
            0x5BE2D1AEBA302BA7ULL, 0x3110C8D5285DA659ULL, 0x25926FA2FA0AE0A9ULL, 0xD65F6EF209B1A9ACULL, 
            0x5ACDC753368DD048ULL, 0x2F6BDCF6B369AECAULL, 0x5086897FC29BFA1BULL, 0x73D6AC686A6C1C8FULL, 
            0xC0680C171B8C881CULL, 0xF6FA13AFE2544027ULL, 0xEFE57DD17905A5AFULL, 0x4CF07A7632571C63ULL, 
            0x92809CC4641FA26AULL, 0x7F1C52194FCB63FBULL, 0x699262AA34E43F18ULL, 0x830608B8FF7661BBULL, 
            0x9BEDE235D3D6A9DAULL, 0x37B4E0048C829AAEULL, 0xD2B7E06C463BE043ULL, 0x8490DD92F39963FDULL, 
            0xA721D26D3BDD2CFDULL, 0xDCAE3434D2BECE40ULL, 0x697689AF6B3CA0B4ULL, 0xA2C15BF9D3CBEBAFULL
        },
        {
            0x796AC99F071FB19EULL, 0xB9F9DF60CF3DF36EULL, 0x64EA0C7D74141712ULL, 0xFFE7826F5215A761ULL, 
            0xEFF69FA8EC9A88BDULL, 0xB3C85ED6DA2346D9ULL, 0xFE34F44E2DF58ECEULL, 0x2120A88E46F0333BULL, 
            0xF1AA8A13BCAE4942ULL, 0x56A7AFF012FEBB3EULL, 0x6AF41B66AC34A120ULL, 0xC2FC22C536F73B65ULL, 
            0xAB28F0F7F04807BCULL, 0x3A0F95C1438065DFULL, 0xC724F30CDB31828AULL, 0x8618978011EC83C0ULL, 
            0xDBBF3C49133D690DULL, 0x80191DE075939A7FULL, 0x462CEB5F5954D2B3ULL, 0x089236E5C1352D3CULL, 
            0x0BA59B2D78E9A4D0ULL, 0xA2862F456530A74FULL, 0xD06B181B986F01DDULL, 0x822B357834739B1FULL, 
            0x0E58C6273B048947ULL, 0x929A4FE5B0F54049ULL, 0xBA1F5F70D8D95B60ULL, 0x35A4E07E076E3D98ULL, 
            0x7CED1B425351E6B8ULL, 0xEBF165DF19D9D7A4ULL, 0x7F79171BF1CAE013ULL, 0x41EF78691042509BULL
        },
        {
            0x9E891F884E483B97ULL, 0xED2E77E977237565ULL, 0x2648FCB1016C7A2BULL, 0xB953396881ED198FULL, 
            0x34F0CEF97CFA35B3ULL, 0x08931E2ABAAA3476ULL, 0xF5CBA59545725578ULL, 0xE5125A330092B42CULL, 
            0x563FE4AF032FB7A4ULL, 0x825083115FDCBC5FULL, 0xADFA62F8B72BEBC4ULL, 0x7DE7B48CF7186962ULL, 
            0x1B0F7CF8670F0BB0ULL, 0xAAA7AB117D694969ULL, 0xA86B8DC711418EC9ULL, 0x1861D23479963DD5ULL, 
            0x4383A276796AF10EULL, 0x4CE77290E99CBB9EULL, 0xE5358B843C5898AAULL, 0x5D1F689AC1E16BF8ULL, 
            0x02AED130856426C9ULL, 0x2B1FD8702D5AFF7FULL, 0x50B601FBEF4ECA1BULL, 0x98A3790D2F99805AULL, 
            0xE6A2572FAE83713CULL, 0xE982A04109AAD087ULL, 0x431AE1704D7BBF13ULL, 0x2F8CE896A6FF5BDDULL, 
            0xEC313952B59083EAULL, 0x663B79EC732300C5ULL, 0x7F3BC307AEE01B7DULL, 0x2B16E38888B0CEE2ULL
        },
        {
            0x29E223321A582E9AULL, 0x1D10715B606DA893ULL, 0x5CD896CE6897EC55ULL, 0xC0EA90A42FCB4679ULL, 
            0x43535BDBCA71AE0DULL, 0xB0ED39F7629A4930ULL, 0x5FF91971DA109BB3ULL, 0x901A646360C06D54ULL, 
            0x805C18686E35DA90ULL, 0x9E49AE80F0B259B5ULL, 0xC9C84206EA13D8A0ULL, 0x6330F1C084E092ECULL, 
            0x8BDF5C10C0037573ULL, 0xD52D22AE6D9A031BULL, 0x298EC61ED4E40920ULL, 0x313FC91F5C2C31D6ULL, 
            0x5C37B460E85EA1EBULL, 0x442CF2EA69B023E5ULL, 0x3EDDE36A8FDC1FE2ULL, 0xC9CC95374F9F6BEEULL, 
            0xFE6263424810C7C7ULL, 0x903C2E632092B915ULL, 0x447DB507D523188EULL, 0x94A51394CC2A9CE5ULL, 
            0xB0D3DF6BF1802885ULL, 0x62303209FD7A89C4ULL, 0xABA44B3BA8AD09A6ULL, 0xAB49621B94EE8393ULL, 
            0xA5D0282856CC0A89ULL, 0xF53786DEB41F1E31ULL, 0xFF12CB5CFB6A2349ULL, 0x03E0EEE6D3589039ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseDConstants = {
    0x083B640259FF4997ULL,
    0xF76CFA0A75885919ULL,
    0x593CA3C1CD8AA0F6ULL,
    0x083B640259FF4997ULL,
    0xF76CFA0A75885919ULL,
    0x593CA3C1CD8AA0F6ULL,
    0xFDD373F3951C2E71ULL,
    0xAD2B8F58ACF7B515ULL,
    0x5F,
    0x8A,
    0x58,
    0x07,
    0xD4,
    0xE2,
    0xBB,
    0xF0
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseESalts = {
    {
        {
            0x768684BC54040E36ULL, 0x8FB6F66E667D1EFDULL, 0xAE8B5FA6A2F751ADULL, 0x2FB6F39983A302E9ULL, 
            0xD272C4E2EB955EF8ULL, 0x50957272BE9F7A1DULL, 0xC5F30D767607DB0EULL, 0x8B4DCDE1004F0838ULL, 
            0x8C8D6D26E9EDF7BCULL, 0x43E104EDC48D4331ULL, 0x273A3FC874DB07D0ULL, 0x7468B10A1E66A3E8ULL, 
            0xEC76C27A1A8D283FULL, 0xE3F09B237B006133ULL, 0x4508CF882D24D640ULL, 0x8B46C9665C299790ULL, 
            0xB865F8C12789A8E0ULL, 0xEC12AB939F709119ULL, 0x4CAE7BA709658008ULL, 0x0E084547B094973AULL, 
            0x813C4664678315F5ULL, 0x7BACCA2CBBCC5098ULL, 0x51918F4C07E32F5DULL, 0xC154D39DFD89F94EULL, 
            0x80326A6E87598AD1ULL, 0xC84E155717FC7BB6ULL, 0xF19DA99A892AF323ULL, 0x7617F18072F7C885ULL, 
            0x840161C83010CC36ULL, 0x8ED88A7C20D0FB50ULL, 0x4A4C62AD7EF02661ULL, 0xE07AEB9C6A662B1CULL
        },
        {
            0x8AEE910BC33C2FA7ULL, 0xF74A1C1575A97B75ULL, 0x0711AA111051F8A1ULL, 0xA53EFA98D1611FE4ULL, 
            0xE198F4B1BD2FF078ULL, 0xA16E542B10AD4950ULL, 0xEBEB5229D288F34FULL, 0xF23C04B15234CE67ULL, 
            0x46E39E98938E71E2ULL, 0xE3982DF8B99A1FF0ULL, 0xB714ADF2B8402656ULL, 0x2B9F734A70B6D51BULL, 
            0x01E88464F40F5ED5ULL, 0xC9EC63C3E2C5F743ULL, 0x37657622C955C545ULL, 0xD5CD824EA439D115ULL, 
            0xF01C8528C1C46416ULL, 0x5D2C7710AEB10B96ULL, 0xA8840B9B45F6C2D9ULL, 0xE4249C447902A142ULL, 
            0x0B5B412A8ED45ACEULL, 0xC183D13A98215D60ULL, 0xC7CFC07EE5C407FDULL, 0x53F3D0F1E85536F4ULL, 
            0x14AF844C24CF2687ULL, 0xAFED8B1458B67094ULL, 0x714F4CECC95986A4ULL, 0xC5B98A13EB7AA335ULL, 
            0x645D7A98A5EF3223ULL, 0x431233D227F8FE14ULL, 0x951D1EBA48151173ULL, 0x4CCDEBA195D47A54ULL
        },
        {
            0x57FF5FB62A5CD146ULL, 0x2C619952C7E2C6A7ULL, 0x5D4E8221638A69B3ULL, 0xEB482DA435BF592CULL, 
            0x7A35780D349B2832ULL, 0x58E21A3E210208CBULL, 0xC16E5713E769948AULL, 0x7692649DB34FF215ULL, 
            0x3E6F517E5668E133ULL, 0xB606F8A3B663A44CULL, 0xF910003EAC314CF3ULL, 0x3AB5691D21F428F9ULL, 
            0xA2569FC5609DADFAULL, 0x238A8000D09E13C4ULL, 0xD14B15584499C415ULL, 0xCD136A806D2E9BD7ULL, 
            0x5793071FDD1AF41BULL, 0x447EC9F45A796B29ULL, 0x283FEF933043BA41ULL, 0x03AA7EF04BC34E72ULL, 
            0xEF43E4161704A99FULL, 0x9B041BB57A08E2B4ULL, 0xF1D02EB5BC3C1863ULL, 0xCC3CA4711705BAD2ULL, 
            0xC3CD308486CB6A25ULL, 0x50A7BF7E45DBC88DULL, 0x321CBA4D0C593F01ULL, 0xB515BA0D10B33486ULL, 
            0x2111DE421C879FF1ULL, 0x728520990EA86565ULL, 0xBCE51830E0C2E4A4ULL, 0x740855B4FE407E49ULL
        },
        {
            0x62F066FAD91F7AD5ULL, 0x8F748523DE45995CULL, 0x25D8EF1FC05E0E4FULL, 0xBA230761423655ADULL, 
            0xE5F0EB62CCA8B6D0ULL, 0xD9D05E7DE6AD29EDULL, 0xD03BA676DE4E679BULL, 0x924545DAFBD202F5ULL, 
            0x844F00207D563BF0ULL, 0xEAEE4D97F574EDDEULL, 0x3FD7240839F556FAULL, 0x19C8992FD227B745ULL, 
            0x629EA96F4EC70775ULL, 0x38438C07AB9A65C1ULL, 0x2694DED00D827332ULL, 0x8E1A7BF9D2F35C23ULL, 
            0xA0FA4D5654A1E165ULL, 0x5AE293498AA51616ULL, 0xFFFFEA0E82DD0692ULL, 0xC1EA7E7A2E01BE1BULL, 
            0x2B351B85CE67540FULL, 0x2BC199FE3FD9F3CDULL, 0xA20CB3A6B8244795ULL, 0x23B428E60B036800ULL, 
            0x79C171D340FF0824ULL, 0x64986C7C012BEAA8ULL, 0x864820C0D0C8C0B4ULL, 0x7EAED7A95A7ECBD6ULL, 
            0x062FFFC09CDA69D9ULL, 0x2CFA82726C73179BULL, 0xAE4D22DDF2EA5970ULL, 0x24BA8F3227A0DD71ULL
        },
        {
            0xCE559163E8BC80CEULL, 0x12D383D34DA6B2B8ULL, 0x18847614B98F7DB1ULL, 0x25F169C78D8D34D2ULL, 
            0x8FACCA835F103E96ULL, 0x86C171D536D6FD8FULL, 0x338095B592AE971AULL, 0xC8A124BB2B9A56A1ULL, 
            0x959C044159A25120ULL, 0xE6845616079C398CULL, 0x14D57562A20D904AULL, 0xF6349011EF0C21B3ULL, 
            0xCC940684CBAEDDB6ULL, 0x479FD1905B0FD6EBULL, 0x8C2E2ED1D9865632ULL, 0x95DBF36F952B38D5ULL, 
            0xBC2C7208EC0C1154ULL, 0x8B8DFA771DA877E6ULL, 0x03FF1209295BECB8ULL, 0xEB99E43AD62ED38EULL, 
            0x2FEFA19181CB09A0ULL, 0xF040642E13124619ULL, 0xEC53D532B70F57B0ULL, 0xFC235C65FA6391C9ULL, 
            0xE1BA37A8A1E3D75FULL, 0xE53CFEC20A4FDCD1ULL, 0x3D0603DACDE1CBDDULL, 0x15C28C986A9D331EULL, 
            0xC20863AC5A3B092BULL, 0x083D1FBB232C77FEULL, 0x77273F1573085809ULL, 0xB16D56C617F72BADULL
        },
        {
            0x452B7BED7B311936ULL, 0x94F2AD210642757BULL, 0x63BD1A08AA58F4DBULL, 0x269026A8F9EA0EA7ULL, 
            0x4B527E5D7948C3B2ULL, 0x03A88E51D588F7CEULL, 0xABB49CA30CC27484ULL, 0xC239F9D7F7D78EFBULL, 
            0xAC2E0F6CF5A26806ULL, 0xB5B9E7E243367FC6ULL, 0x461FDA99C9693297ULL, 0xA705B143028FEA1AULL, 
            0x16C3602CA82B4948ULL, 0xEFE536E9A69517D3ULL, 0x76358667AA1C5BD6ULL, 0xFE7254C8575DDA60ULL, 
            0x145115294D98B611ULL, 0x7100098FEC5A0F6EULL, 0x1097DD01D7384A0AULL, 0x68F5874F65E8703FULL, 
            0x72F88615FFC60FD7ULL, 0x279B00E4F6C14022ULL, 0x63830BC90D155033ULL, 0x1C959274BAC1A0BFULL, 
            0xF2DA605305424FEEULL, 0x9B17E9C884293C51ULL, 0xF1D441247381AF5DULL, 0xE3D802F5B8D0BA7FULL, 
            0x3DFC9A0D68297637ULL, 0xEBB139CE2EDAD170ULL, 0xA60FC3B8575FC959ULL, 0xDF352416A01AD256ULL
        }
    },
    {
        {
            0x5E9C00D2234E4265ULL, 0x6D4E69D359D5F800ULL, 0xAB5019FFE86F16A6ULL, 0xC5FD26D6124259BAULL, 
            0x1918775B50E60AC8ULL, 0x9CA312F1CA327348ULL, 0xD0AACDFEDC5A118EULL, 0x4D6A77ECE03312ADULL, 
            0xE7CD37510C224BC0ULL, 0xE500C1F83B8D22B7ULL, 0xF6C618551357820EULL, 0xC2FF95D16E7DB830ULL, 
            0x9BCCB873C779C5ADULL, 0x1B9AF3EA3943F82BULL, 0x368BE5F16ED79407ULL, 0xB436E2038DFFE758ULL, 
            0xB78448BFA9FCE89BULL, 0xBA3F8DC596665589ULL, 0x391883CBB4CB75FAULL, 0xA2D63E1EF1503E3CULL, 
            0xEF5A18D48CE3BB4BULL, 0x180E66858726FCBDULL, 0x9D67915CAD4475C1ULL, 0x981C5653B70BC3E7ULL, 
            0x12BA670039172A03ULL, 0xC630A6D5C1B47E9DULL, 0x7943EF1476EE73B8ULL, 0x7A1D5ABAF5DC3B00ULL, 
            0x68BB458D9EF4F2E5ULL, 0x3AC7D55E2B8AF6A3ULL, 0x402DBE9963F4B565ULL, 0x89966515596C4E74ULL
        },
        {
            0x60B6D5A6AFBEB020ULL, 0xB66F7083506A5143ULL, 0xACD47A34F5C05CA2ULL, 0x48B1DE56C1AFED9FULL, 
            0x5E2C87863D31CFFEULL, 0xA7A0E342E3283AB6ULL, 0x6CBC61154A440EDEULL, 0x272E153E1CF1F37EULL, 
            0x14DF748A286FA7D2ULL, 0x5052A4C9DE6E5078ULL, 0x47A0A6E991FF93A0ULL, 0xFCB27D685DBFE07AULL, 
            0xE38A6CD7A4013281ULL, 0x160622D52EA1B6C6ULL, 0x81ADFBCA654B68F1ULL, 0xE4D03A6FEF40F2DDULL, 
            0xDAC667A8D100EAE5ULL, 0x8636BB52179D24FBULL, 0x53762A3C0645D88BULL, 0x28923778EB8C3224ULL, 
            0xDD0A0D7CA93234C6ULL, 0xABDD6C0075A269F2ULL, 0x5F30D4B4E39B4884ULL, 0x08A1A28846A37799ULL, 
            0x382BE9D07372D627ULL, 0xDF68B6D33EE54208ULL, 0xD7E8A5812F99EDF2ULL, 0x395B26E8F7067C84ULL, 
            0xFAA81775C19741DBULL, 0xEE5D671F21184AD6ULL, 0xA8CE1A5A63861B9AULL, 0x1CB0B06BDBF41889ULL
        },
        {
            0xA376F33E6E790F0FULL, 0x8A8D33F8D58C813EULL, 0xE185597CFB89F93EULL, 0x418D40B4A9623AD8ULL, 
            0x761D9AB19E74B0FDULL, 0x8C3ED028213B3DCAULL, 0x529C66A455099E1FULL, 0xA1F7E218C2AF67EAULL, 
            0x776369B626C4BECDULL, 0x87C538F96EF13E07ULL, 0xEE2EEE4403C27106ULL, 0xA6E0BC93BA9448A5ULL, 
            0x03EA1EE6B9C10684ULL, 0x6F0AB14DFB872FBCULL, 0xAFC00FE9B3C902F8ULL, 0x330A268D2772B010ULL, 
            0xC502A1C9A7B4F4ABULL, 0x42EDE37E58A678B4ULL, 0x010991D104DFB847ULL, 0x640DAD9A03F20E7CULL, 
            0xE958958C2DDD8F8DULL, 0xD1FD1C190A3C0A47ULL, 0x82EE2ABDC5EB4026ULL, 0xD740940714AD4BCFULL, 
            0x19006771ECCA7D42ULL, 0x6BA7CDA2259BD6A3ULL, 0x8F4034035886FA7FULL, 0xC6E87D07F0D7E19CULL, 
            0x65A100172FC1D123ULL, 0x746F6F031D9869CCULL, 0x0040A9A2CEEEA02EULL, 0x227D59A736B38A29ULL
        },
        {
            0xCE095733764BCFA6ULL, 0x2E32AF0710D46410ULL, 0x456A1B68166F0554ULL, 0x5D81E09EA58F6C1DULL, 
            0x3AC4EF29C99A7735ULL, 0x1B5DA3EE84486469ULL, 0xB58AFCE90BB4198FULL, 0x70FD5C6E6F910B4EULL, 
            0x220DF212E7F7FE8DULL, 0xD4F8754AE34ACD81ULL, 0x9C1CF1B4C45FF780ULL, 0x79A1A66EC9D7676DULL, 
            0x701C029FDDC1305BULL, 0x3E6C35118D703B80ULL, 0xB06621B3C550FF17ULL, 0x047521C03AD766C7ULL, 
            0xD6F9848BD267CF52ULL, 0x30BAC808945FFF18ULL, 0x8CC53C4DF6836544ULL, 0x34E951B19853E095ULL, 
            0xA0DA657D5D500CBDULL, 0x96B7747BFE51A9A9ULL, 0x6080244BDB496791ULL, 0x3298AC9C8776D8F4ULL, 
            0xE7761E5A823AB873ULL, 0xF9239B594DB63212ULL, 0xC2F6B38B1AB89681ULL, 0x71C5972A1403EB01ULL, 
            0xBED4D3E81CF40FC9ULL, 0x3D5C8B7AE8347A61ULL, 0xC476B005E0D8E081ULL, 0xDCEE7EFC6596DFE6ULL
        },
        {
            0xA2A3043FAAE2663BULL, 0x70F97A589C29FB73ULL, 0x4373CA83145D4E65ULL, 0x1B66651CF0E8A8E8ULL, 
            0x27BB258FA30D90F7ULL, 0x41245A9B53C90B9FULL, 0x7AB52D7F9C203773ULL, 0x3D79A906F1CF21CDULL, 
            0xA1B462DF0568B6C9ULL, 0x5F5E117D30B2768BULL, 0xCD46F68C59DF0CF3ULL, 0xE2FC0E2F5F17606BULL, 
            0xF6BD557BE135A02EULL, 0x7D869C02BB6C277AULL, 0x4B356EB753F03529ULL, 0x4AA5EE8CD9D61878ULL, 
            0x7152A1F0BB763F96ULL, 0xF602F7B0F835B387ULL, 0xF9F14091D5B957E0ULL, 0xEC70E421D0EF000BULL, 
            0xC9B7392821802070ULL, 0xDBA0397EB467AEE2ULL, 0xA5A9BCEF62A0F42DULL, 0xCB860D06E6A94F1DULL, 
            0xF846DBA57761C6DEULL, 0x2707A2998320C2DEULL, 0xCC16571230D1839FULL, 0x09D6FD9A236B17D5ULL, 
            0x2098DFBC5087D034ULL, 0x1B00A6B0FF94E16AULL, 0x12A945604C90B4BAULL, 0x215DDAB43B5AA554ULL
        },
        {
            0x984A96C3FFB1D164ULL, 0xA735EE383342B965ULL, 0xD4B194A6F8621C41ULL, 0xA941FD4BAF7DA9B3ULL, 
            0x6EDE5330A8B0D6D6ULL, 0xE98125564D15DCD1ULL, 0xF7013A5F1CAB8CCCULL, 0x04AEC23823AC8C56ULL, 
            0x609CB54ED6A0FF38ULL, 0xC01A8860A24AF8AAULL, 0x299A38B1D6990686ULL, 0x7BB2BD828046E8AEULL, 
            0x6D0ED1C5E6995F3AULL, 0x67A969EACD0FE596ULL, 0xF13CAF6C9EF9F51CULL, 0x75A779ABBAE7392FULL, 
            0x9DD524790FE9899BULL, 0xD20636762501CFE7ULL, 0xE1ADACC0E459F139ULL, 0x21C91F71D82844A2ULL, 
            0xD91D6A7EE9EB5BF7ULL, 0x9F9C041E8EDF31C0ULL, 0x9E7805CAF5CF7323ULL, 0xD67BE1400985F727ULL, 
            0x0B3955EC501A65D8ULL, 0x3F3B71BDCE768BFCULL, 0x0689C12631C56563ULL, 0x690053BCC97B0DECULL, 
            0xCCC0C6F13D58EB82ULL, 0x5BFAE64C4FF6B765ULL, 0x80EA38EF88A78AE6ULL, 0x2E29C0382C99DF9FULL
        }
    },
    {
        {
            0x82DA2F78B82FAAFEULL, 0x0A02D501F935F498ULL, 0xC60290931B53D711ULL, 0x10F118B175ACE588ULL, 
            0xFD501C1B2A9314C2ULL, 0xC8379475699AD77FULL, 0xAA4F220EE92E1B73ULL, 0x2AC9C64B7B86E853ULL, 
            0xBA256E85DB8F4EF2ULL, 0x674691E0F62AE6DEULL, 0xEEE9B4650AE96BBFULL, 0x1D0DDBF814F72D44ULL, 
            0x63D63DB65BFA0A4CULL, 0x26A97B21CBBC1664ULL, 0xB51C6FC591CB61AEULL, 0x4C7397D4AD82AF00ULL, 
            0x4908C47207A71D5BULL, 0xDEB29F6BA97CDC6EULL, 0xC1799B17FF073FB6ULL, 0xBAE17559FF060E55ULL, 
            0x771C4F4601595F08ULL, 0xCA4B4CE9B7CACC91ULL, 0xED6A8D5858BC6CEEULL, 0x9CDC1168ADABE719ULL, 
            0x0061EA97450ACA9DULL, 0x1F25D8092BC3C2C6ULL, 0x2C242DC7E7764BCAULL, 0x6B9DC32410E524BFULL, 
            0x2A7DB287D4691FF8ULL, 0xE0DBBE7904B2C17EULL, 0x410F70AC713E703CULL, 0x6EA2A6728F19BCDEULL
        },
        {
            0xC141B2FB8C2D74E4ULL, 0x2EBC9A0D66523F0AULL, 0xC79177B872BF08D6ULL, 0x3F5D8F80A4074404ULL, 
            0x9C792A6B2FE15C63ULL, 0xC5BA0935525BF2F8ULL, 0x1E22BF2B1E692021ULL, 0xE6E3C6E0F56B33E1ULL, 
            0xB9B3F364058C3132ULL, 0xB2547C6D73850484ULL, 0x832D7FF25BB65A17ULL, 0xB5FB1E28D1974781ULL, 
            0xCF326C48CE540D9CULL, 0xE2EBEDD6FC2FBD28ULL, 0x341B43E1DE788B45ULL, 0xEB6E79596C6C9B94ULL, 
            0xEFA9266FEC957CF3ULL, 0xFA628BBDC9602712ULL, 0x56E20CE1414F6DEBULL, 0x053043A564032A0AULL, 
            0x73F27E2FB3182450ULL, 0x579D628832478233ULL, 0x8D63977E71A8EB96ULL, 0x2363C5B1625ABCB1ULL, 
            0x335CBBD99EBCC92DULL, 0xE7F069ED0A69034EULL, 0x4DA4DB8B74153B71ULL, 0x62F1DB66E0E6E62DULL, 
            0xBAABCC1CFDAE2424ULL, 0xD71C49116C32CAEAULL, 0x51D1A998E763CB47ULL, 0x3299403BB76CCC36ULL
        },
        {
            0xBB66BE5644244EC4ULL, 0xFAA09F0FF6E91659ULL, 0x617CE0555B4D43A3ULL, 0x7B8101DDBCD11833ULL, 
            0x14400FB4CD56462CULL, 0xEC01533BD3BB5370ULL, 0xC7225CDAC95B6416ULL, 0x8C03C19807FCE8DAULL, 
            0xC17A3FFA03CE8497ULL, 0x4A89224E765EDCFAULL, 0xAC62F09A7BC7EAD1ULL, 0xB3273FA2A67E9B66ULL, 
            0x7C6588F09F04E269ULL, 0x6FAD5AB9DF857C51ULL, 0x8DCF9428FA69AFBFULL, 0xB4B21433D55D35FCULL, 
            0xDFF01D45F66A4A41ULL, 0xED9AFD012C3A6E01ULL, 0x96C6ECAB1B4DA948ULL, 0x892B27E74CEE080EULL, 
            0x0D4C8B39F6B34E5DULL, 0x2E1C90BD81E7702BULL, 0x6DA7A938C1987EF1ULL, 0x2DD4F292D0AFEBBEULL, 
            0xCB636558087081C3ULL, 0x501ECBE5D3090279ULL, 0xDF127BD9E7C58B82ULL, 0xC137DD2A15C18969ULL, 
            0x340E31A941400A89ULL, 0x24CB0F7CC1A805F8ULL, 0x624AEA0518D0E955ULL, 0x2726A3BD82B453FBULL
        },
        {
            0xF96563719B5F39B8ULL, 0xB9382A544C8B58F6ULL, 0x035CF663DB81AAF1ULL, 0xEC83DD045B7A3DF3ULL, 
            0xE0CDA2368EDC4E03ULL, 0x43D3E1483394873EULL, 0x7B983A7BB11CC1E3ULL, 0x4E99B35547217632ULL, 
            0x53E6446C2489F2E0ULL, 0xCBF6085558B9E593ULL, 0xB2F433E437319AABULL, 0x1597BBDF676D9D2CULL, 
            0x7445A504B7108AFAULL, 0xC63DD3248B30BCF2ULL, 0xCD03DEFFC13B591BULL, 0x58F0BD4BD5049443ULL, 
            0x0D9BC86DC3F9EF0FULL, 0x1770E37568BA379FULL, 0x89515D094258E334ULL, 0x5A7824D94D8D5CA7ULL, 
            0x11648046D89B88D3ULL, 0xEF576825FEA98878ULL, 0x01A4ED6CC71E7A9BULL, 0x6197D2C3B6594571ULL, 
            0xE70BE55056FEE966ULL, 0x9245F3294F1FDAF5ULL, 0xA8195583CF1DF156ULL, 0x418048836BFC2F62ULL, 
            0x2B2BB4625560C2C6ULL, 0x525FB7B6845235C9ULL, 0x84E48946F3DED7B3ULL, 0xCBC4A36DDE85EB24ULL
        },
        {
            0x377F5ED8BDC9DF65ULL, 0xBC3CECA24460853EULL, 0x954C4B4011E1AD9DULL, 0x8D4676FE57B854D4ULL, 
            0x87982FD4A93A17DAULL, 0x76E827492DE2C9AEULL, 0xF61807A8CA5FC21AULL, 0x5B477DCC98E4C344ULL, 
            0xAF8B5524F9816C56ULL, 0x531521AA9F222C86ULL, 0xACF01A5193CC8EBAULL, 0xD547438AD5DC861CULL, 
            0xFB44186BE121111CULL, 0x22362A67EF4C8226ULL, 0xC864AC27144A4573ULL, 0xEE02082FC0680726ULL, 
            0xF2C3F3521CAD0CCEULL, 0xB5A3206EC4495BAEULL, 0x0EE11757F8633B98ULL, 0x08E15AD0594CB2F8ULL, 
            0x6B1279B4B173B1CAULL, 0xBD80E884729F0B42ULL, 0x26B5027589EBEF17ULL, 0x01571916E92E38C6ULL, 
            0x5AB504715F8BC889ULL, 0x51F312C70C2A47C6ULL, 0xC9076EC923E59553ULL, 0xC3E6BF6DF7D4479FULL, 
            0xC5DB3621EDFAC99EULL, 0xEACF5E384FF4F5C3ULL, 0xD9F172B9E8E33A0DULL, 0x45BD30E5D5465391ULL
        },
        {
            0x9C826A763C7490E8ULL, 0x02F5838587A0A230ULL, 0xF324E29C4D7D2F4CULL, 0xB0B20D67CA70A2F9ULL, 
            0x8C634F70502DA5F8ULL, 0x842E15FB90A2F8F4ULL, 0x01C6F096E4D82B7AULL, 0xE152748A06BD851BULL, 
            0xE525128A9C837226ULL, 0xD9E85909977CEE9CULL, 0x8A153FCC2A48C2C7ULL, 0xDCA8FB22CDA28E27ULL, 
            0xCFF0144DA01EC113ULL, 0x7B276128B83DE59BULL, 0xE6A1D0BA522838F7ULL, 0x631C1033CDEA593FULL, 
            0x4B15FF8F8AEE9B2EULL, 0xF27E2D2D4CD11AB4ULL, 0xA45D0B5AFB87EC8DULL, 0xA3FC0590E9906AA6ULL, 
            0x9B2944EEDBE51C2DULL, 0xECFBB6245217B9EBULL, 0xFE78239A553FA8D5ULL, 0x0449A09E3A4A2F16ULL, 
            0x2A67A73149593947ULL, 0x5435EF0100B23582ULL, 0xAA9F8EA653D5FD74ULL, 0x20DEB6CAB8A504F0ULL, 
            0xC1C1088CD36172FBULL, 0x1CCD8960D9398C8DULL, 0xFAF7AC154FD73B4BULL, 0x5A958E84FAB73832ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseEConstants = {
    0x6BCCD164AF48C37AULL,
    0xDC6DF066DD6FBCECULL,
    0x3C5F1F7DA72E2B62ULL,
    0x6BCCD164AF48C37AULL,
    0xDC6DF066DD6FBCECULL,
    0x3C5F1F7DA72E2B62ULL,
    0x2EAF1DD92A7BA21BULL,
    0x9492AF3271BA7468ULL,
    0x92,
    0x7A,
    0x1A,
    0x0F,
    0x9B,
    0x8E,
    0xD1,
    0xF5
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseFSalts = {
    {
        {
            0xF7F9155A73DF2792ULL, 0xD9F2CE24BB636C41ULL, 0x21C0360193198B63ULL, 0xD85AF23773C5C791ULL, 
            0x460FB771B1EA5194ULL, 0xF11164D84618285AULL, 0x9E0B502C96AB20FDULL, 0x6D3788947FEF7520ULL, 
            0x9740D5222C8E1846ULL, 0x7622B5142CFF1D2FULL, 0x08A5927266488B12ULL, 0xA2552B14BA2D9572ULL, 
            0x6738701C7A6A4850ULL, 0x58A72A93DF2C6A48ULL, 0xA96AA2112EC2907FULL, 0xBA27D4CFA8EECC5CULL, 
            0x4CF142FDF8DB70E0ULL, 0x7C7FC0379C969DB8ULL, 0xF965FAEC699A73A0ULL, 0x76368A0E0CBA84C3ULL, 
            0xEA53E410EF6963F2ULL, 0xD529FC1481531C2FULL, 0x6400B9EF575C3096ULL, 0x8CDC460CF4212F97ULL, 
            0x75369B7146827945ULL, 0x267DA95C6F3E644EULL, 0xFA7E479DDA83550AULL, 0xC02883EC1C9B8922ULL, 
            0x92B27AE481F77DFCULL, 0x5261D466AD279F56ULL, 0xE8A8EBDAE5D4B5A6ULL, 0xB64DDAAEF9140005ULL
        },
        {
            0xA72E2B413672A1D6ULL, 0x2623BEE523A77C53ULL, 0x426DF59A89F02F36ULL, 0xFE4E0AB99052D760ULL, 
            0x6C2FE2BC9AE11995ULL, 0xC0CA982470D30082ULL, 0x23900FB2968AF60BULL, 0xB96B63E046A70693ULL, 
            0x4026DBEE9591B6BAULL, 0xA122A6C57331B5CDULL, 0x95E30F33A892D5E4ULL, 0xB3FA3EE990A16240ULL, 
            0xB2140D32FF4622AEULL, 0xF69A0A0368994316ULL, 0xA6FA7DE16BC8C4C0ULL, 0xB6D20584AED75411ULL, 
            0x879458628DF5B3EDULL, 0x946A6E4BA32D3E3CULL, 0x40C1A3BEAEE60476ULL, 0xED8CD968BE745291ULL, 
            0x478027412384B0FDULL, 0x32F8A925D67679DEULL, 0x57521EEE7807E65BULL, 0xF8D26D5412ED0528ULL, 
            0x9EC811883F4D1828ULL, 0xEA12959F1C0F953FULL, 0xCEF80B5695E77A81ULL, 0x92522D0B9910DC99ULL, 
            0x2B45168F3FAE5FF6ULL, 0x2C0AC5F7D1496785ULL, 0x71421FB94A5410BFULL, 0x151BAFBAF2F4F9A0ULL
        },
        {
            0x628D516B968BB2F2ULL, 0x5ABF44E90E654B4AULL, 0x7F44BB18F2C81CBEULL, 0xA1650C9D263AB045ULL, 
            0xD38EF89724F6598CULL, 0x83EBBA324AB89ECFULL, 0x7A9D0FCE6B3783A0ULL, 0xBE9C995696094F4CULL, 
            0x6E6513F90F9CC228ULL, 0x93994BC66F2DFF36ULL, 0x50001ABE76F3B934ULL, 0x00B25A61B315305BULL, 
            0xB34C9142EA0B03A3ULL, 0x0008CE52A50FDB76ULL, 0xA07F9F167AC86791ULL, 0x25010719D50B5E41ULL, 
            0x77882A5942CBE065ULL, 0xAC9BDE8C1EBA4629ULL, 0x27E0A7A8C1B7D4E3ULL, 0xDF20327E0B0F0774ULL, 
            0xDA2C324103834A6EULL, 0x6B1DCE082B424752ULL, 0x87191168D2D82400ULL, 0x2DEC8964BAD8909CULL, 
            0x9D07EBB71414CCCEULL, 0x9CDB507F591CCBA1ULL, 0x4829B9FF5E14A490ULL, 0x9278B10F1F16F48DULL, 
            0xB0EA79E51D0A7AA2ULL, 0x7902A14B327FBA71ULL, 0x871CDE21D3B8B413ULL, 0xC21BB160205A9BF4ULL
        },
        {
            0xA7850E312638F8AEULL, 0x38956901703C57C0ULL, 0x1B90BEE2A2280062ULL, 0x98A56AD2B45E1402ULL, 
            0x6D6FD5DFB439B8C0ULL, 0x353787A9B7385F83ULL, 0x20F8A365609898CFULL, 0x9C4CB42E608DF07EULL, 
            0x7D86E10DE2CCDFF0ULL, 0x4D91674E2526D89DULL, 0xDC7B88E44949B6F4ULL, 0x73DABBEB9089F35EULL, 
            0x189B4EE09F4B83D7ULL, 0x844383D2F1BF18B2ULL, 0x9C43B0E12AFD27DBULL, 0xB99EDF1E08B2F140ULL, 
            0xBB41EF6FFAB62FA8ULL, 0xC7E909F83A3E0CA5ULL, 0x48FEE2200367D22FULL, 0x2B84D5517EA083C9ULL, 
            0x44553E781EFC6475ULL, 0x698F414303DAFDC1ULL, 0xB730BC198037D317ULL, 0x98905EAE112BD3C7ULL, 
            0x7797F01B182E556CULL, 0xD4EDBD7164FD07F4ULL, 0xF005E872E5B2153FULL, 0xCCCEFA337F2FDC0FULL, 
            0xB19B2C8999E32FAEULL, 0xE59272D4F0120A34ULL, 0xF5DD73251152C250ULL, 0xEFA7600050F62C29ULL
        },
        {
            0xCB04AFB6723F80D8ULL, 0x37CD0520A992ACD8ULL, 0x1549AEB223B298CAULL, 0x34E8DA01D6ABCDBEULL, 
            0xCC8DC5D9576D39A0ULL, 0xDBEBA623C7382F5BULL, 0x61C0BE9084DDAE3BULL, 0x0B436D875C2F22A8ULL, 
            0x7F24A12E30A851A9ULL, 0x3F724A002395B8E5ULL, 0x9C9B653BC98029E7ULL, 0x0C3A7FACA80D21A5ULL, 
            0x129051961ADE6AC0ULL, 0xA7CE973876FC1A0FULL, 0x74676DB3842A278EULL, 0xF183CB8FF0A59BB5ULL, 
            0xC14C9CC9529930BBULL, 0x93590C47F6D04998ULL, 0x22972E75ADA7BFE4ULL, 0xA9E5E6BC882FC216ULL, 
            0x0F64C03216555A8DULL, 0x430F3091611526ECULL, 0x90DF63328A50EF32ULL, 0x709D98B9EDA88B8FULL, 
            0xDC9D351B2D59A106ULL, 0x7AA784A3471EC9AFULL, 0xD96438B30F026109ULL, 0xFE1C7AEE3ECA9A95ULL, 
            0xDE6BBC5051833384ULL, 0x59261047A750116BULL, 0xA3698ACAC2B50B75ULL, 0xF5B24510A3307781ULL
        },
        {
            0x1E1AFD751A6DB6C1ULL, 0x3A3E7A485287B943ULL, 0x3147E270AA95629CULL, 0x1FD3BEA20D006C86ULL, 
            0xC42EF5638F2877ACULL, 0x1D84D6957298CF46ULL, 0x55DFC31440E538F0ULL, 0x04579425695B187EULL, 
            0xA748F9312566A38AULL, 0x5B7AA8A0B909EDFAULL, 0x806107BC6A07526AULL, 0x3A23A0BE87F6DEDBULL, 
            0x44DBED44305CE105ULL, 0xDDC054CFEEEC4518ULL, 0xB86CFD5291D3EB65ULL, 0x79B2BC5306F8E108ULL, 
            0x9E997C6CBC6142E8ULL, 0xCE8952A588089305ULL, 0xE1AFB19FD6185B46ULL, 0xDF55A094169657EBULL, 
            0x6929530430CB018AULL, 0x6503B05D2D898AFEULL, 0x9BDB1F96E128D11AULL, 0x6DFA1B662D4A66ABULL, 
            0xFE157CBCCB8A83B5ULL, 0xE6F9E9600A39BAC3ULL, 0x51569F04C697551BULL, 0x58D7DB0D200595ADULL, 
            0xAD4EE96F4813AD9CULL, 0x1071576B9B18778BULL, 0xF53B9925F8C09627ULL, 0x6F96BC9F93020D48ULL
        }
    },
    {
        {
            0x4B9944F384AD0A92ULL, 0x7276CF7D5092E8FFULL, 0x525C373665427095ULL, 0xEFB5BC811B386260ULL, 
            0x335ACC205FCE8F04ULL, 0x2E19DB256FCE3DF8ULL, 0x24E335D181BC5AB2ULL, 0x53816CB3C23AC814ULL, 
            0x146FA48C649813D4ULL, 0x162D8AC873BDBFE2ULL, 0x37202967269334D6ULL, 0x3E434E27533AA866ULL, 
            0x6D69BA341686D353ULL, 0x9DB460E0FCC6CFA6ULL, 0x0F3CEC843AAF71EBULL, 0xD04011B583453696ULL, 
            0xE2194B4D104E74D1ULL, 0x79E4FADC86DA24CAULL, 0x0EE312E5A9D95464ULL, 0xA8D3BEFBBE3705E6ULL, 
            0xBC8D8292539BF2CEULL, 0x06FDAD03962C3073ULL, 0x1AAC9B952919D583ULL, 0x783977CA9471EBD5ULL, 
            0xC355719FF693114EULL, 0x1AE8DE89FEAD6119ULL, 0xE7E34E685518FC5BULL, 0x5515B987422EF5CBULL, 
            0xC6607F373C232563ULL, 0x656100807E1AFB95ULL, 0x597A222EA4F9DF38ULL, 0x407E5A17B715F49AULL
        },
        {
            0x3FC286C02ED81E1FULL, 0x1F684544CCBC8CB8ULL, 0x5EA3CBFC13D739C6ULL, 0x828242D731E7F5FEULL, 
            0xE6374F475969CAD1ULL, 0x4D331B7529A65D5BULL, 0x34D11342B7A91985ULL, 0x0D69D5062A3507AFULL, 
            0x26E8E886C200602DULL, 0x98DC312AA3143D3DULL, 0x7682C48D771DB70BULL, 0x3971B46DB3F52906ULL, 
            0x4AE558C525A41A61ULL, 0xC24930B847D95EBBULL, 0x81DCBF2F961AB8F0ULL, 0x219C39CEA641BBDEULL, 
            0x57280D7ED3496E8FULL, 0xCF7A80507D5B05CEULL, 0x72B38D39B047B0FFULL, 0x7B8B1013663162CAULL, 
            0x275CB4F06A7F94F0ULL, 0x807950E75B40C1C8ULL, 0x4D713DEDEF58FB15ULL, 0x4B01112B7D8874C1ULL, 
            0xED0A993A2D05A75BULL, 0xC9A11BBE4EFB734EULL, 0x19F2FA429CBD660AULL, 0x80C3A3C5A086FEF0ULL, 
            0x926B35AC18382050ULL, 0x7568069833A97E76ULL, 0xC767E091C22C218DULL, 0x657F81384E807BB3ULL
        },
        {
            0xA9C695590B6A3BB5ULL, 0x826A7D582F8287BFULL, 0x293BE43AC13692C0ULL, 0xE79795C1F641C158ULL, 
            0x45DDC44F35F56849ULL, 0x99241E9AB477048CULL, 0x8F92A8BEED7B50AEULL, 0x8723E45412AD762FULL, 
            0xE84289C4D6260D3DULL, 0x249772B9DC9A0D1DULL, 0x5DF26557741703F4ULL, 0x7EB30EC9D408BB6BULL, 
            0xCBABA1B30F0A6C4DULL, 0x326D12499067DE43ULL, 0xC655A4760E890530ULL, 0x425E165A43741A81ULL, 
            0x0699411152809BBAULL, 0x4921AC7D367D793FULL, 0x41C3B1A3E7D86BB7ULL, 0x34A4DA79EA70EA15ULL, 
            0x81BFE95C44E664C8ULL, 0xDF832163A4B7AF1FULL, 0x8A1A69DD84B04A08ULL, 0x9BD58FAFD4BE03A0ULL, 
            0x252B9C8081B7921FULL, 0x4B4D59C841891347ULL, 0x9B56A73431A64C71ULL, 0x8BA72F174E3DA235ULL, 
            0x209F0ECE96B30532ULL, 0xBFA380034E3B976AULL, 0x78BAE64557E6377DULL, 0x5562EEF9F9CB8CAEULL
        },
        {
            0xE21565EF0D73EBCDULL, 0xF055B626352E73D4ULL, 0x35103574810BB472ULL, 0xA86F20E2270D431CULL, 
            0x64045159AD596F22ULL, 0xC63B5DDA37EECE7EULL, 0xA58B13BA2EFDA145ULL, 0xF2E0AF797C5F968FULL, 
            0xA249DB6412AF4E12ULL, 0xA898BE4FC657268DULL, 0x4260C9049600BA49ULL, 0xA98E332D3CFFCE1BULL, 
            0x5F3ECD22B194DBF7ULL, 0x68B8ED52B309B90AULL, 0x867507B7088F6CDEULL, 0x8BDC37948C60BBC7ULL, 
            0xA023A19762916E01ULL, 0x24759FFE38A68D91ULL, 0xC7CD137F042BF9B0ULL, 0x9A239807162CC417ULL, 
            0x8797ED9E84E5A66AULL, 0xEDF1940ACED799D7ULL, 0xE6511ED95A083210ULL, 0x06595394AC66FCB1ULL, 
            0x5F3EB9D7CD931863ULL, 0xCA832A925696F5B2ULL, 0x160A5E5C7A1B2612ULL, 0x024F2C7534FB191AULL, 
            0x9BAECCD44E883D3AULL, 0x7F1466025E4850A8ULL, 0x05A5E4A03FD3175CULL, 0x8F3389685908EE4DULL
        },
        {
            0xE89ECD3249CB0AFEULL, 0x8E2078D558A7331FULL, 0xEBFAB9BE4270D692ULL, 0xA74612247A7F2039ULL, 
            0xCDC8B15EFACF8964ULL, 0x362B453CCED77587ULL, 0xB55E8209F350A1D8ULL, 0xE2760C00734BAC42ULL, 
            0x09CA626E927F3607ULL, 0x16F256935866C3A0ULL, 0x70AD32305B63E662ULL, 0x798904ECDCEA2A2CULL, 
            0x8A0737E921ABBB2EULL, 0xF9D704B2B82984DDULL, 0x275B82D4A856D898ULL, 0x3E229992905FA95DULL, 
            0x2A9471DCFFD65D7DULL, 0x517C160025FC325FULL, 0x60ADE49CD610F90FULL, 0x47B75AA9D263E8A4ULL, 
            0xCC00C5A3A88BB0E3ULL, 0x249B1C4760A4A77BULL, 0x6FCE0EA41B9CF7DCULL, 0xAD67484FFFAE9CF1ULL, 
            0x650134A7D52F258DULL, 0x1B9C6510C70865B9ULL, 0xD7754307FD8010C9ULL, 0x03FBDED9F22B126AULL, 
            0xFD01E1BCE0DCB678ULL, 0x7D63B3A11702FC47ULL, 0xCC069807B7DF47AFULL, 0xC4D54877F91BB129ULL
        },
        {
            0x81AFAA4F9D1A7AA9ULL, 0x3DD4E65CE7967212ULL, 0x566D6A8ACF549C72ULL, 0xAF7B0D03BDFCF42AULL, 
            0xFE074FE4792151A7ULL, 0xFC6980F971AA85F5ULL, 0x7ED4E7921D6C4432ULL, 0x2FD8482C10F98B40ULL, 
            0x678BAB8249E9322FULL, 0x01304A0BE6D584FBULL, 0x0A1293A6DF7323BDULL, 0xC1C0B3AE7E7D9DA2ULL, 
            0xB9DA155DC4A0AF21ULL, 0xCA1CF3F0A9268052ULL, 0x1885D90DC36EE2EEULL, 0x021BBFFC29AF88DDULL, 
            0xA72520C8E43E203CULL, 0x808EF2A160409E5DULL, 0xDCA88F981F8D981EULL, 0x11A79130B89DD674ULL, 
            0xEC5DEC503269ECDDULL, 0xC91323412BD8240AULL, 0xEA7F7EC8D87D2DB8ULL, 0x30296D70CBF47EC6ULL, 
            0xDAC82F0030A2B8F6ULL, 0xC76D99B2E297AA49ULL, 0x47F7F9143F73506FULL, 0x87B943820FA8637EULL, 
            0xC5CFA60B0FBF0DB5ULL, 0x729AB2E7035EF398ULL, 0x25D649A6A38CF193ULL, 0xE4BECBA499383CC1ULL
        }
    },
    {
        {
            0x4950F2C7E36C7F00ULL, 0x5239233190CCEA18ULL, 0xB1B88C6D5068B458ULL, 0xF12561B4B5195EC8ULL, 
            0x73AC195785221E6CULL, 0xDE2CC4FBD63C623EULL, 0x619F45984145B433ULL, 0x7EDE5C1CC5AB51F0ULL, 
            0xD6F6DBA925B1A612ULL, 0x465862BA47DA6994ULL, 0x18EAF3B36799D0B7ULL, 0x560B4433852D1AB2ULL, 
            0xF9F2027F0FE6FEB7ULL, 0xE81CA84988B5966FULL, 0x04D904BA8EB504E8ULL, 0x5C19B958715EEED8ULL, 
            0xD214C0C2F8FF87E8ULL, 0x06D904D2C5430499ULL, 0x4314A124FA1FA486ULL, 0x4DAC324FF91BEE37ULL, 
            0x34326201A165C757ULL, 0x635125615F39D781ULL, 0x1214CC6D59B8B920ULL, 0xA791605A5CAEE7F5ULL, 
            0x10F28617607F50A8ULL, 0xA559B9131268D3AFULL, 0xE1DC4109D850A0ADULL, 0xCFB02F43B5C5EFEBULL, 
            0x9D92DAF5F358174CULL, 0x92458C42BAF0ED2AULL, 0x95E2AFF1BF509A97ULL, 0x27730F39B8C501E4ULL
        },
        {
            0x95D5E723EF293B45ULL, 0x3601653532F67C0BULL, 0xB0082FE47C4B7763ULL, 0xFC1681CC33A00553ULL, 
            0x60C34926D4D369D4ULL, 0x7891C4A28C8C6473ULL, 0xCA8503D53D1AEB3FULL, 0xEDFEEFB3856AA3F0ULL, 
            0x6D011CA28D315CBBULL, 0x0B0877C5C45CE677ULL, 0x88D18D20A7EF5ACFULL, 0x4E5F49CCBB33FCA5ULL, 
            0xEB53998571E47322ULL, 0x16E045F07818FC03ULL, 0x894EBF93F7FCD5FAULL, 0x2814909153A057E3ULL, 
            0x08CB7084E99D40A1ULL, 0xE0097F3F274B1B3AULL, 0x68DFB07B0D5C0610ULL, 0x699FEDB5E9A5017DULL, 
            0x6214746873AA7C42ULL, 0xBBDA14482EFF4FB4ULL, 0x1EAAE540B0B2E88CULL, 0x28177431D2CA3C96ULL, 
            0x973A7CF090CEADECULL, 0xAC073BDF67C5B944ULL, 0xA67436AC0157A8C9ULL, 0x16B1CE3FBEDF75F9ULL, 
            0x38069293C75152C4ULL, 0xD1595E83F3212ADEULL, 0x3F88406D8FC5E3F2ULL, 0xEFDC156CA62D8767ULL
        },
        {
            0x0A97F71A707AE458ULL, 0xCFD4DB86D472B0F3ULL, 0xD4E9C8A34FBEA1F1ULL, 0x060A21EB73D52E3BULL, 
            0xD99613F5753E551FULL, 0xA58C047ACF11BD79ULL, 0xE81A1406484B88DDULL, 0x30BA5FB55B1E6C86ULL, 
            0x46E23E0AD2EB7736ULL, 0x6D03DEEF37D4C086ULL, 0xD1020A0B015AE746ULL, 0x573AE0ABD4AD2734ULL, 
            0xD801261E99A67375ULL, 0xEC1BB333AAEA21B8ULL, 0x406EAD85881ED7C4ULL, 0x17325EB778A39AEEULL, 
            0xA1DF3FEBF457C455ULL, 0x2F839766F6514D81ULL, 0x03FAA6E601492101ULL, 0x59D731308664D41AULL, 
            0x6C60A45A83EEAB48ULL, 0xD2B96D944FC6A2AFULL, 0xC8DF32C39B84F475ULL, 0x4C19F7365F617375ULL, 
            0xE56D4415533F1E76ULL, 0x45587E5A55681567ULL, 0x9C8E7B92F308FCC0ULL, 0xF3B9E93EEB087591ULL, 
            0x8AF27E4D283AA3CFULL, 0x05D605B8718F7F6EULL, 0x97D405E7C7D5F14EULL, 0x95B489CCB2945348ULL
        },
        {
            0xFE7799A6294D4A31ULL, 0xF099554FDA1B34DBULL, 0x257BD74FF9F0C490ULL, 0x1C5DD7A842D5E46CULL, 
            0x2FFA4F7C429CFE1AULL, 0x6ED3ABBDE44DCE17ULL, 0xC8A4B1B7B6737BA1ULL, 0x1EB96BE1F781FA8EULL, 
            0x7A6186B113720820ULL, 0x15F1B0EAD07C8ABDULL, 0x024B04850F8B5B44ULL, 0x3301832B231F6B60ULL, 
            0x61F35477B7E50E85ULL, 0x2DFFDDA31B3809C9ULL, 0x7D888DCA462ABC7FULL, 0xFEDF81AA77EFF5F8ULL, 
            0x16A2C0309AA5ADBFULL, 0x717BBA9BAEF192BCULL, 0x4D9D5B3F75B0CBA3ULL, 0x967FC3A9834D4FECULL, 
            0xC914A1BFFA8B023CULL, 0x0A0179A9B1630099ULL, 0x779D94D7003D4120ULL, 0x49A63DB758AECC96ULL, 
            0x6DA28C1D0D13145DULL, 0x31AC880DF63F8177ULL, 0x8D4C41D69D581509ULL, 0xE17C1D6C6E064311ULL, 
            0x3042C4352CAAEF3CULL, 0x984EBF4C8D3526EBULL, 0xD32EBDB55257CD33ULL, 0x08362BFE62EF9B4AULL
        },
        {
            0x408EA6FF541E4155ULL, 0x23A0552AA757F6D3ULL, 0xCFB4D9D0F128AEF1ULL, 0x2C1880F00236294EULL, 
            0x5E81EA850B773CC1ULL, 0xD847B85A09EA06E8ULL, 0x632359D7BCA60AC9ULL, 0x515DF83586F89DA9ULL, 
            0x259B3DE02DB878E6ULL, 0x4542A278F3D88F76ULL, 0xC4D68164D7E79A6EULL, 0x530C880A26A74D9AULL, 
            0x8875FEFA0AC57018ULL, 0x2461BF1ACF0C7ED1ULL, 0xFB88B2925DBBF5F3ULL, 0x340EEF064CA99E7AULL, 
            0x9FFC877EDB42A5F4ULL, 0xF6EFEE39472D47D7ULL, 0x0DC9272BF4205550ULL, 0xEFEC46CAB3DB48A0ULL, 
            0x49C23BAFBB1B47F7ULL, 0x730EAAAD56189BEFULL, 0x1920F21F890E4B6CULL, 0xFBA052D21A118AAFULL, 
            0x5ADEFAA913F3CD3BULL, 0xFD3E60A0717FF112ULL, 0xF106DBF74DD88461ULL, 0x23E6BA641B691FE6ULL, 
            0xC161DE970A643474ULL, 0x31CF04378CF2647DULL, 0x39E2EFC2A8C34CA5ULL, 0xEB5BA1C2D9E61D59ULL
        },
        {
            0x859A365F4ABFEFB5ULL, 0x69C2655CDE3330D1ULL, 0x5A35294C66C04A01ULL, 0x37E81CA17F40EFC8ULL, 
            0x79366BAB17867E35ULL, 0x2B7F887AFB61D582ULL, 0xB370B55C086A2AE5ULL, 0xEBB594C7524FFF4EULL, 
            0x32DF6E1CC5779D77ULL, 0xE108DE4CA2485D39ULL, 0xAE15230B15C8CD33ULL, 0xD4907D6A43D3AC72ULL, 
            0x74F70DFE45A047D7ULL, 0x80D5877AED18F3DEULL, 0xB6F513BB8E196B93ULL, 0x971956CCC5DEFAD0ULL, 
            0xCF5C29A80DC5F8EDULL, 0x8005C19266DB6599ULL, 0x4024934CB59A9C5FULL, 0x1397A8F73DA1F917ULL, 
            0x4474610E51527807ULL, 0x3CAF9D0A51585685ULL, 0xDF82653F009BED8BULL, 0x724F06C8511C7A96ULL, 
            0x7439F6E5387B1468ULL, 0x3FE366D50E49EDC5ULL, 0xC307739936EDC436ULL, 0x21D03A5FC626AF4CULL, 
            0x467D9D8A27092365ULL, 0x125AF4B5BBA0A2C4ULL, 0x41F9555FFCAA9B13ULL, 0x5F3C9D9BCC33D2FBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseFConstants = {
    0x7BB4CE2D5137923DULL,
    0x14283A284A3C607EULL,
    0xCEE4F91EF61A0FBDULL,
    0x7BB4CE2D5137923DULL,
    0x14283A284A3C607EULL,
    0xCEE4F91EF61A0FBDULL,
    0x8D6B806D51556D35ULL,
    0x0A10E0FFE4399BBDULL,
    0x41,
    0x47,
    0x25,
    0x2E,
    0x32,
    0x60,
    0x19,
    0x2C
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseGSalts = {
    {
        {
            0x3B1615D4ED60C511ULL, 0xA93CAFF897FA3DC4ULL, 0xD2E5D6353679AEFAULL, 0x023EF64347FC397CULL, 
            0xFBFC823EEF4AB070ULL, 0x0CBDB237CF9D515CULL, 0xA7CEEC54ABBF57E3ULL, 0x9335CF0F1AFAF7B2ULL, 
            0x8359374D2C099ECBULL, 0xF0C3339B3C9CF42FULL, 0x892257004475AC10ULL, 0x9E655FDF082959A9ULL, 
            0xEB66732182E46635ULL, 0xE8D20504BE1CF213ULL, 0xB9B79393D5AF918DULL, 0xEEA1CC2A26011A00ULL, 
            0x6AA0999A82C5FDF5ULL, 0x86FE709FB64B4C39ULL, 0xC8381CD9B891E7C0ULL, 0xB8C7046868471591ULL, 
            0xD937FBEF4E347F24ULL, 0x442CCAB154586458ULL, 0x48CFB3BEA6F9E993ULL, 0xE83704A73784C243ULL, 
            0xA05D330F01F651E8ULL, 0xA650403DA68652C3ULL, 0x42A59FA1FE7CA335ULL, 0xC0C0D4F02816176AULL, 
            0x3FB0685206FB8780ULL, 0x684B4DBF68C01214ULL, 0x396DBB5A65651CCEULL, 0x7004E3D300CA7F91ULL
        },
        {
            0x9FEEE811DE094B3FULL, 0x2CE9E187378F4F45ULL, 0xC84EB16E66C8C751ULL, 0x85AA86DFC10A93FBULL, 
            0x1CF4EE0ECBA2B8F6ULL, 0xE730A2D3699A8074ULL, 0xF87813E147B04543ULL, 0xF915F3306ED9B982ULL, 
            0x512D35E9A57C0D79ULL, 0x05EA1635710FB0EAULL, 0x92FB301500556464ULL, 0x6907EC14E80FC3A0ULL, 
            0x1F4E323EDFC39C52ULL, 0xB06091FD5E08890BULL, 0xC6E077BDA6B12151ULL, 0xA14A3C29ED912D22ULL, 
            0x5C96968EF6D90496ULL, 0xD6585D6479BAFA65ULL, 0x470E38A6C0FD7D0AULL, 0x72A4CB0844D8158DULL, 
            0x557783B33A4D4001ULL, 0x084DF72C579A5179ULL, 0x53275199508F7E2DULL, 0x8F02356512D78EBDULL, 
            0xAAB84CF660336D7DULL, 0x3CD997E4130E7BA9ULL, 0x207AFBF117F67306ULL, 0xA9465595DFFD633AULL, 
            0x4AD9CD22DD7C9CEFULL, 0x89920599F41CF056ULL, 0x2BEA8B27791AA1DBULL, 0x0BD5630FDE659798ULL
        },
        {
            0x6DC188744A35C319ULL, 0x0EB8C802980A0529ULL, 0x8B5F1FD21B674C1AULL, 0x59D7BB6670CB82E1ULL, 
            0xD06E298056389D40ULL, 0x83617156695CF01EULL, 0x94A407E4B4DABB11ULL, 0x273A328F698E622AULL, 
            0x7A3B71A7764DEAA8ULL, 0x0FC391C657FFE34EULL, 0x26EA6A1E1C71961CULL, 0xB3992EEF0C706363ULL, 
            0xF7B5FF4C26CA34CAULL, 0x5F56E9F4E424674AULL, 0xB38E923422A84372ULL, 0x2DAB1316163C38AFULL, 
            0x7D6EEE1A4E2937C0ULL, 0x415D7E0E2A9B3152ULL, 0xDADEB94299770D21ULL, 0xBDAD5CD0D1622D8BULL, 
            0xF01FCBDB59A6CE7FULL, 0x23BDADFA27BC2E85ULL, 0x053B046A710CAD16ULL, 0x17877A589D126FBCULL, 
            0x7CE7B3AB16F9A593ULL, 0x450CE265AA47868EULL, 0x5FA1168035411ED4ULL, 0x2BF9B31F3FB72B22ULL, 
            0xC779652E68888A06ULL, 0xDFBA58D2A03089B0ULL, 0xDA05E06B01CB439AULL, 0xBAC2D3DDDF5F86F6ULL
        },
        {
            0x6C4BFE466B7ED98EULL, 0xCFFC9CE60D0A5039ULL, 0x3A1DD08586921DFBULL, 0xCE386C803D3EB097ULL, 
            0xF8AD12D07FF7B4A9ULL, 0x6639BAAD8AECD449ULL, 0x269EAC9067B234C0ULL, 0xA7D5723DEA4E60D9ULL, 
            0x1AF44019623EF173ULL, 0x26B3BFC6071435DEULL, 0xC90C39AA3BFA155CULL, 0xA73D74FBFE61C2F1ULL, 
            0x1137B7EBD0173B0DULL, 0x53C8BB49FB8B7924ULL, 0xFC2C371DEE5049B4ULL, 0x1F5DF8069DCE30BFULL, 
            0x7F3346CB9F6B2208ULL, 0xBEFE6E29CA2193F4ULL, 0x7FA498A2D8190D1AULL, 0x84478FBD67BAF849ULL, 
            0x0FE1A31FCC68D626ULL, 0x11B2685728B60FD1ULL, 0xCBF751BAB181D30DULL, 0x33C620B77DD0AFD4ULL, 
            0xB2713FC06872DB88ULL, 0x27BFC1DBE29365AFULL, 0xE0C491530869E888ULL, 0xAFE1467F4368A93BULL, 
            0x6D661F6D621B74C5ULL, 0x96007C9934FC5853ULL, 0xE76B1C555F7454F7ULL, 0x2CC1CBB326FBBCA7ULL
        },
        {
            0x5621F25E3A23215FULL, 0x0110F8208EAB620AULL, 0xA06B09BF1A994E4BULL, 0x6F14026BB537AEBBULL, 
            0x2625626A1A70FDD1ULL, 0xA1DE124BA6BB5AF5ULL, 0xC956FEA758FB0EF1ULL, 0x8337AE1F94A71528ULL, 
            0xEE7DBCAF6C983899ULL, 0x13533C82EC1DA0F8ULL, 0x66CB031CE7096FF1ULL, 0x6C427C0FF4DEE44EULL, 
            0xFF3D54A305335A99ULL, 0x76DCD32AA1AD0F5FULL, 0xBCB10FCFBC253BAFULL, 0x264D189691887487ULL, 
            0x4AC2F96D852DAEFAULL, 0xC50BB3191990D87BULL, 0x411110EC7272327FULL, 0x2B8CA2E7C74AABC9ULL, 
            0x3528BCBB5D66289FULL, 0x0F7998A9384785FCULL, 0x6F823996847C054DULL, 0x52224D3566357295ULL, 
            0x9052EC8E6F5D1428ULL, 0xD817480A92139F2CULL, 0xACD54150B9FC03CBULL, 0xD7D9869222590F62ULL, 
            0xF1600DAF3BFBEC67ULL, 0x056232DEA4C24134ULL, 0x026C1981AD779550ULL, 0x7106D6E7A93187CBULL
        },
        {
            0xD1C7A6DFEE49AE91ULL, 0x4B79877B56FCDD10ULL, 0x9F8AFC4E696464FBULL, 0x28556E667471A1F0ULL, 
            0xD72B1B9EF9C74F1FULL, 0xBAE92DAA068A85BEULL, 0x3B033B2EBBC63EAEULL, 0xF35F64CD003A947AULL, 
            0xC7CE8AC06ADBAFB6ULL, 0xD607F6488C55940FULL, 0xD53C0E3108CC7A58ULL, 0x0D50277D5D032547ULL, 
            0x76F24DD24452B6C3ULL, 0x24B25E3C0E149A34ULL, 0x3EB8A4483427B25AULL, 0xCF5E18647C34E75CULL, 
            0xC429914766400D74ULL, 0x1EAED8A053979B91ULL, 0xA6C2E53F5B324AB9ULL, 0xB771CE65B3D66277ULL, 
            0x227EC22D4E37FAF5ULL, 0x4F53BEB4280A5DB1ULL, 0x8C8A7DA53112B926ULL, 0xBA45CFD11602AD2EULL, 
            0x0C0A77232BBE2C32ULL, 0x4351523C04C44088ULL, 0xFC786828B36CF528ULL, 0x015B55E63C505746ULL, 
            0xAA5AA32AC0BB2736ULL, 0x6BC44550990C7C39ULL, 0x78E5786DBBE9D6FBULL, 0xF66E74DE2C9D5D6CULL
        }
    },
    {
        {
            0x805B4B3DEE4D7DB0ULL, 0xC8AC0A6F982F96D9ULL, 0xB85FCD6F9607E70DULL, 0xA733568B892EC029ULL, 
            0x3D27EC05B26BA511ULL, 0x499357100AFFCA28ULL, 0xB2690C0C8DEB646CULL, 0xD172A3636E29F3E7ULL, 
            0xCF3ED0F9F084D94DULL, 0x2B3BBA3D84BA94BEULL, 0xE7E962AE646A491EULL, 0x79C740582BD8D7BEULL, 
            0xCD555BF5CA59D6A0ULL, 0x9B03B2281C2B0364ULL, 0x57C7C937CA5BAA76ULL, 0xD270DE967AF58FE6ULL, 
            0xAD6E9DBD05161847ULL, 0xD812B033813512D9ULL, 0x36F7A3CEBE87AFB0ULL, 0xB2F7961EC19996A1ULL, 
            0x9F472A8396FB87D9ULL, 0xC64EB998B1A2C56DULL, 0x3ED97DE01119B46BULL, 0xE1BEEEB54E9F42F3ULL, 
            0x1EC6FD811C705723ULL, 0xF5AA43D93926A521ULL, 0x41A997318A60FF28ULL, 0x743107F8E5753B44ULL, 
            0xE0EB0BAF7BA5FDEFULL, 0xDD9F82445AE39FB5ULL, 0x425AE3C585BA1BE7ULL, 0xEE82A0CC94940CE5ULL
        },
        {
            0x36B7809AFC137EC7ULL, 0xDAF7CF02594C022AULL, 0xFD336BC6F67EDDC5ULL, 0x070E204CBB6DDCACULL, 
            0x6D7E012D310D7EF6ULL, 0x872CE8A3C4DAA5A1ULL, 0x44AA4095700A213BULL, 0xA97B7CB156C610F1ULL, 
            0xBA76B8EF5CF62AA1ULL, 0x0C0BF46DF5CEC492ULL, 0x97B3DC80EC72658BULL, 0xE0FD0BD1286E7695ULL, 
            0x8F6301F5EFA1EDD9ULL, 0x03C7087B5DAC94E4ULL, 0xF6C509FD33344AD5ULL, 0x24A0979330B0F258ULL, 
            0xDADDC843080C3C08ULL, 0x774B9F6996A59E69ULL, 0x87F9D7CA0483E7AFULL, 0x5DC9088256C38E4CULL, 
            0x0FCFB3E69EFAD813ULL, 0x1FD6C9E1CBE73592ULL, 0x811E62E603D383FEULL, 0x1D1BAF648E13DF7EULL, 
            0x8350B1EBF8E0D6B6ULL, 0x96F87EA657306CF5ULL, 0x8F753006C9D909B4ULL, 0x45E0238DDEFB3D31ULL, 
            0x5A9DFDC0044FAC70ULL, 0x5E7BA305386B9137ULL, 0x69B97A940933FEAEULL, 0x2F36BAA68CE72758ULL
        },
        {
            0xB621C8F30C620711ULL, 0x07A0CFCECD8CCA0DULL, 0xA2F0012A7BD7477BULL, 0xE0040181961FB3AEULL, 
            0x702F683E0F285955ULL, 0x216A85F48076F0BBULL, 0x3D5897D7105E24CFULL, 0xFE6BE3BC4070D1B8ULL, 
            0x5710864CA8CA256DULL, 0x0E7309D8305602C0ULL, 0xD150462F9230C015ULL, 0x20832AA377EBC76AULL, 
            0x445DBB974A81B186ULL, 0xD44BD2387A1D0531ULL, 0xEE546F00654533C8ULL, 0xEDCB64AE1ED57575ULL, 
            0xFC2DC7F4FD9A7841ULL, 0xFEFC31B4ED2784F2ULL, 0x3B95C12D5F68F800ULL, 0xC1E284BB83463AD1ULL, 
            0x3F76ECEFF86A0FF7ULL, 0xE36DA0C7D9798985ULL, 0xB52331D1C3DE9D90ULL, 0x246D4CD3F4A2957FULL, 
            0x830C9298EF6C1E76ULL, 0xF705AAAEA5248DD8ULL, 0x319BDCE1B8100C07ULL, 0x853219648FA95C6AULL, 
            0xECB1E860D371973FULL, 0x627AB38AF6B0DBF5ULL, 0x530DFB07E1EB8B4EULL, 0x470393516BF90DB4ULL
        },
        {
            0xBE3C6E773EEAE599ULL, 0x2A7BD9CA5B59F376ULL, 0x8664968C3FDEA793ULL, 0x8F19B7AA6E079F34ULL, 
            0x9B364EC018E3572AULL, 0xAF0A0AD7C233B4F7ULL, 0x28478FDE7B5F3FBCULL, 0x5827618025B737C3ULL, 
            0xDDC15D385252D7FCULL, 0x2646755919E04683ULL, 0x4786543F091A9568ULL, 0x12C5A534958604DDULL, 
            0x0A765CE9950A1725ULL, 0xF84052893E5071E9ULL, 0x0911C1E733E53A62ULL, 0x8D94ABA4BAEBCDDBULL, 
            0x03F6AD1BD496143BULL, 0x58A488CA0B6A0455ULL, 0xA1D8EDB8C6CE375DULL, 0x93118666299AD934ULL, 
            0x07FAE3180CF2BF77ULL, 0x05F9F2420B81BDB2ULL, 0x1DC3DB01D7C944F1ULL, 0x66B81919553B6C49ULL, 
            0xB5C488C25A121B49ULL, 0x4E13FF73DBB20988ULL, 0x1AA9A5918E721499ULL, 0x61320DC53B0178AEULL, 
            0xF62B609796F37094ULL, 0x91FBF081933CE5D4ULL, 0x207D550413DF9DD6ULL, 0x4F1E2A24A7559B79ULL
        },
        {
            0x3CAAF270358B74A5ULL, 0xFA8E9D594C05C57DULL, 0x493A6E4154C47F52ULL, 0x0F3A7B67822D3DA0ULL, 
            0x7FE3EA7DAE484D3EULL, 0x46A3AC87A77C5145ULL, 0x4EB8A0E7EE926ECAULL, 0x7C6AD80AA93CFAC0ULL, 
            0x559FC385B2486463ULL, 0xEFF336D973AFF642ULL, 0x684D55AFA96D10F1ULL, 0x4D0C0D4C40509B9CULL, 
            0xD0B999D7BD95B20DULL, 0xC3B279BD3EA547D8ULL, 0x02E0F304B6ED8A01ULL, 0xCFD6F9F3C44DB92AULL, 
            0xDA2C99D5392F436DULL, 0xC8CAFB5766E1B9B0ULL, 0xBA30EC941FCF001CULL, 0x9E422F217170E3A8ULL, 
            0x4C670C7F146CA2FAULL, 0xD6D8398FC0A6651AULL, 0x126C7051B64F34D7ULL, 0x4777F3571E279C45ULL, 
            0x2ABFA212150A2E53ULL, 0x266C92ECCB639BEEULL, 0x23956E738188E364ULL, 0x372AE0C1E4DB17DAULL, 
            0xBF14EAF110B15742ULL, 0x4964CF9226EB4878ULL, 0xF4CBEF643D5E2338ULL, 0x7835FC5556BBE39CULL
        },
        {
            0x2A544BB830B74959ULL, 0x2C3BA6D580D96401ULL, 0x9C5B6F65585A5F16ULL, 0xA5CF09397CA47712ULL, 
            0x85A571E8E99A4C54ULL, 0x44560DB631930A7FULL, 0xCEE7353B514775AAULL, 0x5006BCC63AF74D83ULL, 
            0x9F12E529AD7379C9ULL, 0x5DD8273B9BAE22D3ULL, 0x3DA3DA2D43633EF2ULL, 0x4C1D0AEE7F8A9D2DULL, 
            0x1358D3A19FD61E24ULL, 0x7E74AB9CB6B6F968ULL, 0xF6C6BB3BDDC99751ULL, 0x2B8E3AD521339BB3ULL, 
            0xC686609D527252D7ULL, 0x34C3C886C3C6E9FFULL, 0x2766EFE2EC5D47BAULL, 0x1472DAC790BE8B75ULL, 
            0xE6A5F09F1F1D11A6ULL, 0x527E6286D7137DF7ULL, 0x97FA98E9A90AA53AULL, 0xCC0E5E58655AA3B7ULL, 
            0xC906E445DCED1BC4ULL, 0xB6DE932E23F9D7ACULL, 0x7618332F253CB89DULL, 0xF162F6933BE3E5F8ULL, 
            0xB58EBC15977DBD94ULL, 0x6DAD0F089EC93B0EULL, 0xFE26FF4836C651EFULL, 0x01406C00BE21ED13ULL
        }
    },
    {
        {
            0x3C4FAB736BC9F6A6ULL, 0x880227BEB1418A3CULL, 0x8F30C77B601F907FULL, 0x7F0352C4092F62E0ULL, 
            0xECEA74C0ABCC7166ULL, 0x824B75FEBF406D59ULL, 0xE08ED9CDB3FB5F87ULL, 0xD5CF3844A69DEE7FULL, 
            0x754B319E3EB16B60ULL, 0x7D86E9E879176E49ULL, 0x7530639CBF888BD7ULL, 0x5F491368203DF72CULL, 
            0xDDB116C306537FA7ULL, 0x2DA7D684CABCED1EULL, 0xC48F2547EBB89669ULL, 0x4F7873A1E914CFF2ULL, 
            0xE58AA09A495D286AULL, 0x592F38093661B95BULL, 0x36A5E7D66C5EBBB9ULL, 0x39B28B7E003A54D8ULL, 
            0x797085F53D9A67F6ULL, 0x70AC43AD7A965603ULL, 0xDA80A4B60E67EA5FULL, 0x3D7E148A0CADA8C6ULL, 
            0xDA34B4A267FA617EULL, 0x186E7F48B3BF961FULL, 0x55F95882242486D0ULL, 0xE0A233ACCF28E956ULL, 
            0xC0D6D45487FD9A77ULL, 0x5BB51F536A5B48B1ULL, 0xD1777180FA65B71AULL, 0x29A05ED6C51282A6ULL
        },
        {
            0x1E88299531E27DFDULL, 0x504EDEDF624897E2ULL, 0xFA8DF59E80717485ULL, 0x3D99F118F80FA7B0ULL, 
            0x54AFB9FB0E82A13FULL, 0x0C82E3503BF0A421ULL, 0x0276084AC56631CCULL, 0xCC8FE6B34B329059ULL, 
            0xDB43C12FC11D2012ULL, 0xC2B78516535A8EEFULL, 0x4A57BC41E533BB73ULL, 0x13E8335A6436DA28ULL, 
            0xE23875AB1D13CE66ULL, 0x567BB25CDBB1C3B1ULL, 0x1146D85554E76F03ULL, 0xDEABDE4C900DB6C0ULL, 
            0xBE1AFAB1C8C37AE3ULL, 0xE00A231F012B0171ULL, 0xB0AAC86117A17E94ULL, 0x09A88BF787AB77B4ULL, 
            0x842A1786EEDFC3D6ULL, 0x5D5A6DD3C9E9B08EULL, 0x98FBA07E2B946C40ULL, 0x06DEA2AAB02A8B16ULL, 
            0x965611EDD213B101ULL, 0x9ABCFEED081A48B9ULL, 0x685E8753B9850CFCULL, 0x1B13E17A608B644CULL, 
            0xB17916F7BE41A210ULL, 0x9D73643BEE9293A4ULL, 0xF87250EB4B9B14BBULL, 0x078942616E5D40E1ULL
        },
        {
            0xDBB9006B8290E729ULL, 0x7E9637C458F3C9EDULL, 0x255D2007A0677C43ULL, 0xB5BF778D06A7B547ULL, 
            0x0270AD4264C7D328ULL, 0x609FD1EDE4C8A821ULL, 0x306796A52639FD23ULL, 0xE0160ED708AC22FEULL, 
            0xBD6D590929D5C378ULL, 0xE9F56A9D84669653ULL, 0x8FCBC93B6F039010ULL, 0x91B0A23112FC11D9ULL, 
            0xD5BB0E8687FAF958ULL, 0x6E145699A5B13841ULL, 0xBA3896ABA73DC6CDULL, 0xFCF4665E4AC67ED4ULL, 
            0x51A92449FC781512ULL, 0xCC9971951E4332A4ULL, 0xA956975C77E8875BULL, 0x29FBB612A158F172ULL, 
            0xFC1E7FB4390686E3ULL, 0xA4EA6DC03C236B0FULL, 0x310FB28E945E30F4ULL, 0x3CF1676B4BCE7052ULL, 
            0xE4810046B803B760ULL, 0xEC450F24E0BB76E1ULL, 0xF32026BDEAC2EBBEULL, 0x1904E95D223FB87BULL, 
            0xD8369B85DD817E3AULL, 0x5074EDEDB06188A2ULL, 0x6106408B1581BD68ULL, 0x3CD83CE9B2A5189EULL
        },
        {
            0xC65630A671CC34F8ULL, 0xD7A56C3700456FEFULL, 0x0EA711A636494AC9ULL, 0x1542A3CA777848F7ULL, 
            0x827FC5E886FA6258ULL, 0xED4ACCBB363FC390ULL, 0xFE3D258BF3159EC5ULL, 0x6B007FB72750DE81ULL, 
            0x1DF88C44C3808B8CULL, 0x0A37C1264D4D0031ULL, 0xA51BBA761ADE0EF4ULL, 0x0907E83F6068DB16ULL, 
            0x1A8F1240CED36A79ULL, 0x78159C31B0330D70ULL, 0x63EDC27564519D4BULL, 0xF14C7C005B283E97ULL, 
            0x2D20669D6FFBF97EULL, 0xC5717197AE39AD93ULL, 0x3D892812714FDD16ULL, 0x99257331EFB287DDULL, 
            0xE080695F882BE3B9ULL, 0x7DA05280F765C477ULL, 0xD68BFF2644BF6D32ULL, 0x3452A6B31741BF05ULL, 
            0x9BF2C8CDE475C84DULL, 0xB845830B7D1FDBDCULL, 0x88FAFF5AFEA5F2FCULL, 0x55DB1E008ECFA7BEULL, 
            0x37C08A3AD3A654A9ULL, 0x78D7F0D90B03A523ULL, 0x7181551FD036EBE4ULL, 0x8471678B29908BA6ULL
        },
        {
            0x269AD26E2455E7C0ULL, 0x545BFD508D9BE2C5ULL, 0xEF01C33D3766DDDAULL, 0x4C4F934452AD7189ULL, 
            0xD9C261A40D6CC988ULL, 0xF99417382F1FA54DULL, 0x69427F5DD8520031ULL, 0x9AE6A107E42B22A2ULL, 
            0x26C9A86FB7B0AADCULL, 0x595995F1C3C5B823ULL, 0x255BF0F20535B481ULL, 0xAC608532BB7CF2EFULL, 
            0x614C03787B2FB047ULL, 0x63E807AF742C100CULL, 0xDB5FAA528D27645AULL, 0x79E135BDCC265EB2ULL, 
            0xDE476BE860090848ULL, 0x14A52488568CC54BULL, 0xA4DB13DA31986A84ULL, 0xC3C990F1BC3877A1ULL, 
            0xEFBB66CD8F29E291ULL, 0xA52119A8DA650501ULL, 0xD341FE51E2475F8BULL, 0x9A5F7094CADFF5B6ULL, 
            0x61213EBAFA68009EULL, 0xF1039496E13E4087ULL, 0xAF24DFC2C68168ECULL, 0x2C9EB2702418DBCFULL, 
            0x5DA528BF430087EEULL, 0x32E9AD711CC32DFEULL, 0xABCCB7C016245D8EULL, 0xF32F91281A800524ULL
        },
        {
            0x3529C94446AF84EFULL, 0x5A1DB6F37F591C4AULL, 0x580C8F35C7D9D2B7ULL, 0xA06F240586611DEEULL, 
            0x7C1DCEAE00E1A76CULL, 0x226437B4AC841C26ULL, 0xF8EC8FCE3D25085BULL, 0xE910D7E758165D5AULL, 
            0x9D7CB11C84BB5770ULL, 0x02CD4DFA5AE4912DULL, 0xAD2AB3E42B73A281ULL, 0xF15237DACD860991ULL, 
            0x2E04B5332881CA4EULL, 0x2BCF528C60A5008FULL, 0x1D1956F9881344F6ULL, 0x4820D90998A2E479ULL, 
            0xAF2F9847844859D0ULL, 0xBA5D64364E2FBC6AULL, 0xFF73779F6031EC79ULL, 0x2ED5FC81861CB244ULL, 
            0x391E07D5560752D7ULL, 0xF10B4E0AEDF95FA4ULL, 0xCA587E141EAE099AULL, 0x1A5A6FD7C37F3C70ULL, 
            0xE9A584A0E083FE2AULL, 0x05F40195D4963BBEULL, 0x08D0C11C3973A0EBULL, 0x21D0CD23C7B40365ULL, 
            0x0F0740ADDB445034ULL, 0x571ACB84FD24E24DULL, 0x177DBF5C73069305ULL, 0x7660C6BE38A645EDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseGConstants = {
    0x512E9E582F945947ULL,
    0xE7BF77BAFEA38333ULL,
    0x26BE5B9245FAEA7AULL,
    0x512E9E582F945947ULL,
    0xE7BF77BAFEA38333ULL,
    0x26BE5B9245FAEA7AULL,
    0x8CE925E514A3457BULL,
    0x519B3E5BA652AF03ULL,
    0xB7,
    0xB4,
    0x64,
    0x7E,
    0x65,
    0xF2,
    0xB2,
    0xDA
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseHSalts = {
    {
        {
            0xD390E680DE01D44BULL, 0xF6259562D8267C84ULL, 0x2C4C1FC9782082C8ULL, 0x97659C01AC3ADE89ULL, 
            0x9E9035BA386F747BULL, 0xA705FDC021C82415ULL, 0xEA4E23E8EAB23D7BULL, 0x971516DD8420833FULL, 
            0xBF632121F82B3FAAULL, 0x3C64D18093B403E8ULL, 0xFB3304601541C1B7ULL, 0xBCF44A6B8DFA65DFULL, 
            0x7ACD152136E65217ULL, 0xAD17317DE1AD7F3BULL, 0x4A1E352EF56CA7D8ULL, 0x8D0B464890D8B2DCULL, 
            0x7BB4A5CAD9E82C7FULL, 0x0720AB55015152E8ULL, 0xB080C31699313F5DULL, 0x30A0DB34A5B2BBF8ULL, 
            0x53FF6C3E60CDDF9DULL, 0x83939E8C21FAD317ULL, 0xECFDD81173611441ULL, 0xF3F01B3D668E9784ULL, 
            0x0E144A15ACCF581EULL, 0x3B003C10944E6DC1ULL, 0xA9C78598B76ABDADULL, 0xEF97D009B5B9FEDAULL, 
            0x80907C5CCE32AAD5ULL, 0x3CC7B63409EAF4D2ULL, 0xDC779CBDEBD26604ULL, 0x8F91A4C3B7877E24ULL
        },
        {
            0x922C3FB184FF7A72ULL, 0xE1E3512C159AF09BULL, 0xD6597BD5E8CFBCBEULL, 0x51C30E37F0369959ULL, 
            0x6EEADA2B839B6CECULL, 0x36F7E96A59319AA5ULL, 0xE120BD2D7A5E4D05ULL, 0xAF6F52432DA4407AULL, 
            0xB447F3CDB0201AC3ULL, 0x498ECAD0BA39A98FULL, 0xBF18CD23FC323FA2ULL, 0x0CF55E3543AAB503ULL, 
            0xC79CC8D15E05BBC6ULL, 0x1453BD320B618DF7ULL, 0x51F94E983BE9D4CCULL, 0x063BBB891714CAE8ULL, 
            0x211CDC54DE6985D5ULL, 0xB6153644F0E4C3CAULL, 0xCB995FAA6555C643ULL, 0xDA563025E399E46CULL, 
            0xD052B0DC8155C092ULL, 0xAFF1C1F960D735F4ULL, 0xE37DEEFD35BC4197ULL, 0x4749A99664FA6CFCULL, 
            0xA39BB7C3C3C42818ULL, 0x8ECADE9ED15032C1ULL, 0xD98CEB3E353E2239ULL, 0x5E6ED6775A555B56ULL, 
            0x587BDF19F475346AULL, 0x5213E7CD4F335578ULL, 0x3CCE7FADBD80ABC3ULL, 0x42149F21BCF3CC50ULL
        },
        {
            0x2B73188700D509E6ULL, 0x35987FB86695AB1AULL, 0x8587377D9B67EC94ULL, 0x20EA07EEEA206F3CULL, 
            0x787C5032AB46A8CAULL, 0xCD80565BF20693A6ULL, 0x8FDE74359F94D727ULL, 0x6CAF91CE7FD9BCE3ULL, 
            0x4EEC2A393818EE4EULL, 0xFF90F4CCF074F780ULL, 0x1792F363B527F390ULL, 0xFCF49200B46C957AULL, 
            0x2C7EB56AC745DC35ULL, 0x781A85E47E397219ULL, 0x24BB70BCB255D93DULL, 0xF09FFB2FB92F901CULL, 
            0x3F3173D95127471FULL, 0xB64C10632AB8DF4EULL, 0xEE78538F0E0EDDCBULL, 0xC22344E017F7A50DULL, 
            0x2CE0180E23BC7F52ULL, 0xE8898EAD888E00EBULL, 0xDAF9D1BF5BBDB191ULL, 0x4DF8C395631830EDULL, 
            0xA0D4C48B1B0A5A11ULL, 0x784C6325EF46D2A2ULL, 0x999117C1B6D1D911ULL, 0x47AFEA3CAC3A4227ULL, 
            0x6F09BF52C80609A1ULL, 0x295C88E303260BBBULL, 0xB44F0245B3401E25ULL, 0x6B071FC145EBF6A9ULL
        },
        {
            0x000C78975344A0A8ULL, 0xF26B61CAD2B92076ULL, 0x886ED5F0257D897CULL, 0xB37EEB5EF1F3EBB5ULL, 
            0xCA855D31E9B134C4ULL, 0xB6A2507190F75515ULL, 0xECA8129A401AB7F4ULL, 0x2A6113E8C3715202ULL, 
            0xCE55AAB4C3867E87ULL, 0xDD7BF889E342EC1FULL, 0x78C8E7DDC3B176A1ULL, 0xFFA92BBBAD43E944ULL, 
            0x15FB012A24E52E00ULL, 0x5715DD12BE1F3831ULL, 0x7157ADF585BFE241ULL, 0x7308746015670523ULL, 
            0x7EDA1427262BC348ULL, 0xC65540F1B80E47CDULL, 0xCBC1D02C35CC72A1ULL, 0x7A5E93626B16A81EULL, 
            0xB144B37358170326ULL, 0xE44715ED82C833ACULL, 0x5E6AA94198AFB79BULL, 0xC1EB11C86C193EA9ULL, 
            0xD5A5139B97F56158ULL, 0xCB30E7095FDBCCCFULL, 0x80C672047E062894ULL, 0x34CE93F406231D1BULL, 
            0x8C633C780AC4CBE7ULL, 0x8AA47FEC45370809ULL, 0xC7B13DAB181BA370ULL, 0x3B5147FA952E7BDFULL
        },
        {
            0xFC136AA8465BA0D2ULL, 0x18C250FB52C65769ULL, 0xC0F0B13397EB28A1ULL, 0x359AEDAF9FDE6377ULL, 
            0xBD6F55301345C3FAULL, 0xF1A5E009EC5B4AC0ULL, 0x6F730FC827A9D0BCULL, 0xC030FCAF345DB867ULL, 
            0x52A915A48B9A164BULL, 0x2A13F9B6C66A9459ULL, 0xB2F9BE7DCEB8637BULL, 0xDEB9530D99D78B16ULL, 
            0xA358490A6023A5B9ULL, 0x4E132DB4C437E208ULL, 0x214E98487EE7A6C9ULL, 0xC5394525988F0A71ULL, 
            0x4A83FF25DBC3F795ULL, 0xA43E6EED7E4589C5ULL, 0x5CEB242C0F615FC4ULL, 0xF0CD252C2ECB81BDULL, 
            0x7A4299B8D2CF6EFCULL, 0x081EF32EB02CCF56ULL, 0xEBECECD8D0FFCB10ULL, 0xF67BA3D8FB3E4762ULL, 
            0x5EC37921253B2F60ULL, 0x44D9C69B01DC19E4ULL, 0x76E69C60371807ADULL, 0x15AD047D42E6BC36ULL, 
            0xD747F8EBC5EF76F1ULL, 0x9B639826FFD4E671ULL, 0x8383C9049218C54BULL, 0xA047CFE213B8EFBDULL
        },
        {
            0xC7235BE4442CAC28ULL, 0x518A28F129938A89ULL, 0x5CDD8FC8AA0452F5ULL, 0x7C30A01EA1C93E5FULL, 
            0xD519D129BECBDEE7ULL, 0x754F1B4CFE143DEAULL, 0x3FEA40C3DB49C756ULL, 0x4E968324DA96AF6FULL, 
            0xD3E0C880ED4419A3ULL, 0xC060EF27C7B744CAULL, 0x27A9D3E0110272ECULL, 0x7ABCAFE69821F648ULL, 
            0x8011CF6B923B5033ULL, 0x83332F9D7ADCE32FULL, 0xF424D63922659DBBULL, 0xD50B5B09C3247355ULL, 
            0xA64BDEA6D2ABB068ULL, 0x6469037F366D3542ULL, 0x6B4120A3F466831BULL, 0x6C9EEC1A44316BB3ULL, 
            0xF40FC3D31DFFFF9CULL, 0xE8159DA2E462553FULL, 0x89CA15CE4FBD9D4AULL, 0xA6338A7C144C68B1ULL, 
            0xEF6C4990B8D91B32ULL, 0xBF1AABDCC68C9B21ULL, 0xB6188B7A234F3028ULL, 0xC1A0B5F70EF2B708ULL, 
            0x85FDFEBCB436F7EDULL, 0xA0558A8712B5B482ULL, 0xDAECB83E13C0BF03ULL, 0xC79575095F121887ULL
        }
    },
    {
        {
            0xD0B5567E2C7443BDULL, 0x54A35A8737B432B7ULL, 0x742AAE8D20A80D56ULL, 0x6469B8A9C26BDC85ULL, 
            0x8467F18E1C64CDE5ULL, 0x82FD89BD666C1A47ULL, 0x441E09AFE2CF8B63ULL, 0xD8E7B77363A1B0D0ULL, 
            0x77DE1842EF19E1D0ULL, 0xA7B6C77D18F4B072ULL, 0xBEB9C7D70C5EE06FULL, 0x643256247CAE5F6DULL, 
            0x9971CA38A2E0C43DULL, 0x2DB01007C1EF6161ULL, 0xCDD18CC1AA262304ULL, 0xC80C012AD956D67FULL, 
            0x4027D73AF6980684ULL, 0x3B4EA47FC1C5850CULL, 0x580FFCF1EE8FABC8ULL, 0x36664A3136544185ULL, 
            0xF5C8521E47EE5777ULL, 0x5757C135A4087811ULL, 0x2AC8F6C30C715D27ULL, 0x96BC148EEBEFFF9EULL, 
            0xE98BF556ADF76800ULL, 0x25278BBC6ABCF1E6ULL, 0x1F1B9D0373AE316AULL, 0xEAF5C80B084B95E3ULL, 
            0x57E4EC26BA9D2FBFULL, 0xDF209BDA299C9D18ULL, 0x568321F65D030BB7ULL, 0x000AFE7C2450E0C0ULL
        },
        {
            0x90B0DF477508C68FULL, 0x6DE1511978EBAEB3ULL, 0x1162A9EDA5D14BDEULL, 0x2C8C342771DD0A11ULL, 
            0x9F38B6707824F381ULL, 0xC820A1BB1C88069AULL, 0x8B7DF152B66B1CD0ULL, 0x09BB220F6533CD2BULL, 
            0x4B039C0B8A8E53A0ULL, 0xFB1E79DD6786B188ULL, 0x6DEAF02FD7750291ULL, 0x587B780B1A81C81BULL, 
            0x1E47F43F48241F63ULL, 0xA74690F6918C83D7ULL, 0xB40EF6C75EE8618BULL, 0xC139C7C470E744B9ULL, 
            0x888E431723D28685ULL, 0x4EE9630DA2AEAF76ULL, 0x90E9D763A5ECE5D4ULL, 0x14F0DC4E5FE84BD2ULL, 
            0x7845BB235EBFA7DEULL, 0x23A6FAC7F5C78AFEULL, 0xD88034F0103F3A74ULL, 0x8E4730114F2AE5CDULL, 
            0x2333857350D51BB5ULL, 0x37B28A774D4E325BULL, 0x3BDE02A17A91C00AULL, 0xB0C03D6D7E8EFEA1ULL, 
            0xA6AA2751C5AFA8EAULL, 0xB884276D3AEF2B6AULL, 0xE009E345403A7DECULL, 0xC73F14BF27ECAF6EULL
        },
        {
            0x1272814302F3880DULL, 0xF331161FF0B3A417ULL, 0xDFDEC6130E4DD527ULL, 0xCD2B7C2A1CC796F0ULL, 
            0x6AC87CA141E2F204ULL, 0x4ADB1C1A1B18A5A3ULL, 0xD9237859705D96CAULL, 0x25D36A897DF82F72ULL, 
            0xA5BFF318ECC035B4ULL, 0xFF6D8692236A1603ULL, 0x72D15E5B93B56A92ULL, 0x594CAB72CD870FAFULL, 
            0xCFD3D67FF5D438CDULL, 0xA1D09D3F4CBD267DULL, 0xBD8E15CFBF151121ULL, 0xDB32375CDFEA40BAULL, 
            0x4C50A398C570B46BULL, 0x4F771523CCE7DD5FULL, 0x8248346FB568CA38ULL, 0x7DC0F42A5049DB10ULL, 
            0xA36F58B7650357E3ULL, 0x947A72263389B23CULL, 0xB9F142E9E33626D6ULL, 0x3428F5977906E1F8ULL, 
            0xD54857D4A159B692ULL, 0x78B7D283C292028FULL, 0xE166CC34D7709E0BULL, 0xF0E8F1D0A46C50C4ULL, 
            0xFD88F386E6550E64ULL, 0x645D2729DF274D25ULL, 0x211D675C5658097DULL, 0x252EA5CA32203400ULL
        },
        {
            0xF5BEF550298FE2A5ULL, 0x28E7A3D1452D49F0ULL, 0x854AB11BDF496BABULL, 0x3402B2C981273C7EULL, 
            0x3FEAEFEEBAC5C460ULL, 0xB2485FDF084CF0E5ULL, 0xAE5258D4BF872E55ULL, 0x145C44598E3029D2ULL, 
            0xF9141F9C98EFFC87ULL, 0xD219BF416E046EE5ULL, 0xC4422100861B155DULL, 0x9585307D6218B2C8ULL, 
            0xBD9EFFE21F1C3BF9ULL, 0x1E760B4CA725CBC9ULL, 0x4E458447526D9E6CULL, 0x086F6A847159BA4CULL, 
            0xA1BCA7F22C798318ULL, 0x00635912D2F33980ULL, 0x5A8F4DDA85EBEC0FULL, 0x5B2EF60FE4A43918ULL, 
            0xB83520FBDF87816BULL, 0xE30592929244F675ULL, 0x0C9A9C36989D5A56ULL, 0xDD71F2654CB05C5AULL, 
            0x2E2973E844DF06FCULL, 0x6A6FFD2B649F20DAULL, 0xB92D035EE0F0B2ACULL, 0x410EDA240F0BE680ULL, 
            0xEB575F82D982B514ULL, 0x7A3DC9242C3FA96FULL, 0x2397E78022E8E6DFULL, 0x8E779A47E71F2A4BULL
        },
        {
            0xFDAB5BD325E2D163ULL, 0x0F075E712C6041DBULL, 0xF7B9E7774878B1B6ULL, 0xDB2AE27569F71586ULL, 
            0x535202F5C249CF39ULL, 0x64E90DDEEC449D57ULL, 0x001673A768B73FAFULL, 0xC1F6BA94428C60ABULL, 
            0xF9830828418A27A0ULL, 0x677559A370FA0DBDULL, 0x40924EF084A1B15CULL, 0x9A940FA0522AE4FAULL, 
            0x42088BCC5D442063ULL, 0x2571DD95FA027B47ULL, 0x95400BA70E266B51ULL, 0xECB8B3041AEE487FULL, 
            0x1FA548AAF6755C62ULL, 0x29B635ED6C959252ULL, 0x90934F7E0041827BULL, 0xFED52426B5E32FBFULL, 
            0x5331CD5B0F7A8467ULL, 0x87B7D6A215A21204ULL, 0xABD2E404CE584A18ULL, 0x500227B41F3C8474ULL, 
            0x20CD66BA89D1F9E1ULL, 0x966D04AACBFB52ACULL, 0xFCD4BEB00FCBAB66ULL, 0x1B0086CB838A2CF2ULL, 
            0x14B1916B96FB6427ULL, 0x72BC82D42B682809ULL, 0x75502707FF65F0D5ULL, 0x9FCA78E71FCD7420ULL
        },
        {
            0x47946A2D07E9AB5EULL, 0x5362C806AD0A4E87ULL, 0xCED0A84CE0822057ULL, 0x396E1C057DC823BEULL, 
            0xF59D07CB97F60FEEULL, 0x5DE3D08C1D26380FULL, 0x596226B118512875ULL, 0x741BF25E7FE1AADCULL, 
            0xCF128838F9A92543ULL, 0xB4B506BD02DA4788ULL, 0x5702EB05B76331CAULL, 0xE3AB48F7289A405DULL, 
            0x9766B42761F3DD89ULL, 0x86F20D886DBB1986ULL, 0x75065138800965B2ULL, 0xEA449DA831B15D17ULL, 
            0x4BA1DABDC9C3E67CULL, 0xA977CD21935B1D13ULL, 0x68BE118EF338E7AEULL, 0x027118C02686D908ULL, 
            0xAAC3FE00E961AF0BULL, 0x0418D3E768897B6DULL, 0xE65C2DAB58961AD6ULL, 0xC5CD03B2393D41E0ULL, 
            0xE98F631EC4E63900ULL, 0x71FBAF89422DD315ULL, 0xC96A51B271CBF730ULL, 0x13CB60E6DB747081ULL, 
            0x5CF72CEC9CA9A5B5ULL, 0x1E5B0C5A032A053AULL, 0x1321775A9F614B01ULL, 0xE880C6843C87FCD4ULL
        }
    },
    {
        {
            0x4F8486986649B5B9ULL, 0x31E778C3ABAED63BULL, 0x099A351A23FDCFAEULL, 0xD4C10E6EE05C70ECULL, 
            0xC6DF4B97AE3FD05AULL, 0x90EB1FE493EAA136ULL, 0xA2D30A3A0310FA84ULL, 0x515A1CCFF1022774ULL, 
            0x3076418548E005BCULL, 0x0C7196BCD1135B39ULL, 0x8D644D030C8324B9ULL, 0x809F5A9F85602C56ULL, 
            0x5F4DCEC89983BCBEULL, 0x957CD7F1264167F9ULL, 0xB18D678727ABBBEAULL, 0x02A2C8FF6B5BA0E0ULL, 
            0x10BE5063E4BA9EBFULL, 0xF91E3545C6ECC952ULL, 0xC20377E582F77C49ULL, 0x2DF9C4E78ABDC0D7ULL, 
            0xB7919FC909216836ULL, 0x20CE43C06321BF6CULL, 0x3E941E633DD40E79ULL, 0x55E990EF3E4967C8ULL, 
            0xD5F22E8571F49C6FULL, 0x518642D028857D44ULL, 0x0B4D3CE2F1468E40ULL, 0x3D12C3B77BF9D02CULL, 
            0xDB433321CC3D5DA5ULL, 0xF98107329F87394AULL, 0x28DFF1A8E86E8D85ULL, 0x4A1F1C446423E9FFULL
        },
        {
            0x133D7BD5D705E055ULL, 0xCA540A1953D686A8ULL, 0x57A43D773E569A4BULL, 0x1C9018EC9BA90345ULL, 
            0xD76B56842D50C761ULL, 0x5DAD9915036F07D3ULL, 0x42C6CAAC860D1847ULL, 0x9FBBEA4959F5838DULL, 
            0x62171A5CE0C8D319ULL, 0x99CDE84D596FCE4FULL, 0x31AA95C2D98795E6ULL, 0x8D594EF23F0C0D0AULL, 
            0xFA733656A7736441ULL, 0x0309A26CF19D2C2AULL, 0xB81E7EDA99080644ULL, 0x97AE07FB4DE7CE78ULL, 
            0xFE66329973AF6317ULL, 0xB7AD52C39A963396ULL, 0x2C7EABC9E5C3F001ULL, 0x1D12B4DB717269BFULL, 
            0x7CDC505FF88BE120ULL, 0x573EDFDC036BE058ULL, 0xA7F4FA687913ACC8ULL, 0x0ADEEA3A826460BCULL, 
            0x25828A3BC39F8464ULL, 0xAE6BB2B8915F4BDCULL, 0x0F44D6A9691759B8ULL, 0x6E426D8200C5789BULL, 
            0x0E51A8FEFD752D91ULL, 0xF4ACA5ECF4E834A9ULL, 0x6C9AEF216DE6343FULL, 0xDE431718F53A83EDULL
        },
        {
            0xE5E3E649817066D2ULL, 0xCCDE14F10EE09A82ULL, 0x1C0EFCA350E3BD99ULL, 0x030C642C7474C4F9ULL, 
            0x5FA9BADADB43C50AULL, 0x4D76AE28A473C1B1ULL, 0x255C08EF5DF16AF0ULL, 0x6346BDA60ED05EF4ULL, 
            0xB1EDD06D052D31C4ULL, 0x20A25FABCFCAF22DULL, 0xB8A5905E1BEBFC7BULL, 0xF8F3E400B8183F89ULL, 
            0x1D47F7EC9A645953ULL, 0x33B190C369BFAD0EULL, 0xF5B0CC1D991C3AF0ULL, 0x69B89D8EBDD87A80ULL, 
            0xD65CB47C97E28D2CULL, 0xC778CD65B29BE64BULL, 0x907998C5C76B4B63ULL, 0xE74C12A1E232BBCEULL, 
            0x9CAA6827DB8D11B5ULL, 0xA9D39EFABEED6D5EULL, 0x2569FD4AC5D0BF71ULL, 0xD8EFAB554BA47804ULL, 
            0xD3BB9BF10BEBC9ECULL, 0xDAF17B6C1104845CULL, 0x2504DA8A61473120ULL, 0x085B64D5EA11D71BULL, 
            0xE6E6C4CFCA3D1159ULL, 0x7C12F05F15F0094EULL, 0x1627B6DAA6C943DBULL, 0x840554B4BA825FE0ULL
        },
        {
            0x15B9AECF66315B30ULL, 0xD20ABDB9F34E52EEULL, 0x85BF5EE5E822A7BEULL, 0x8FE58BBC7F054A09ULL, 
            0xE1A83D543D4F698DULL, 0xB162654EB1E5D1BAULL, 0xDDCC948103BDD7DAULL, 0x21EC72332FF25A11ULL, 
            0x69203907A9DC75C5ULL, 0xF640DA314553ABC8ULL, 0x9B0640DCDB80D201ULL, 0x8994ED2BE0ADD897ULL, 
            0x47EADD2FF1FB44FEULL, 0xCAD6896EA2D110F8ULL, 0xDCB53ABAB37A473EULL, 0xD0A39526D6009D93ULL, 
            0xE9E1B1D5A784F616ULL, 0x68FED20F8C9379A0ULL, 0x918B901BDF0F5547ULL, 0x6D9DE7BDAC4833CDULL, 
            0xEB54C3BFEC46D0CCULL, 0x953638893E6A1462ULL, 0x11123B7FC7A72D0DULL, 0x97E68EA3F2845935ULL, 
            0xA4BEA406662817F2ULL, 0x596450F8DA91523FULL, 0xD446A08671A45726ULL, 0xEC67A5F9A3C4FEC7ULL, 
            0x10DC07EEF1DE6967ULL, 0xDB1C789C0B52A21BULL, 0x33BEAA700DADFB2BULL, 0xDEFAF8FD80A72374ULL
        },
        {
            0x5611188368DE263FULL, 0x17C9C173634061C9ULL, 0xF11E91734D722D34ULL, 0x9F756596DC97974DULL, 
            0x974F52512ABAD410ULL, 0x362CB3EC0FE8676EULL, 0xD4F7901DA0449F2DULL, 0xA2945DE7C7F8AAE2ULL, 
            0xAFAF94F31338AFC0ULL, 0x67104AB1AECD95AFULL, 0x2B80FC60826C3006ULL, 0x862F9CEE359C6284ULL, 
            0x75632F82EC57944EULL, 0xBF7F5A5C17572D9CULL, 0xC6C032827CE727BBULL, 0x815C5C6BE10B27CEULL, 
            0x07753EF3FE96927BULL, 0x309EDC334A863E32ULL, 0xF556D9BF138CE61CULL, 0xCADC452CB53CFC0BULL, 
            0x226F4DFEB07CC0B0ULL, 0xB44BDB23E35333B9ULL, 0x81C49EC263C3EF5AULL, 0x1249D60AD10A0BD8ULL, 
            0x65822DE4D0056F6CULL, 0xF4B9907C87E30503ULL, 0x354012306C64D8BCULL, 0xB22E2846BFFB7DCCULL, 
            0xC9AAF47500A66C5FULL, 0x3CB3FDBBAF4D2505ULL, 0xF889D75F897C23C8ULL, 0xB2434F43CAC8A1BAULL
        },
        {
            0xDAFDA0363C9A6B31ULL, 0x4CC943CED4E5BEB8ULL, 0xD3B71F1EF34AF53EULL, 0x66DB8F300C2178DAULL, 
            0xB9A74A21E1F7661BULL, 0x2CDC25CB4B003013ULL, 0x2263F1A030A2B7C2ULL, 0xC9438DCF2D5B29BEULL, 
            0x57A6CA9F728CA044ULL, 0xAB0B14F9C94ECF13ULL, 0xE6BFC7DBFD8ED6FAULL, 0x8C98F77AF8C265DCULL, 
            0xA099E477E5C0D052ULL, 0xF567F7B80E609D92ULL, 0x3D071D02E2280020ULL, 0x9DEBDFD35679B6F7ULL, 
            0x1FF0FE192CDD3561ULL, 0xFED355E6C2C45648ULL, 0x1BB6C087F4F810E5ULL, 0xBF8ABC474970738FULL, 
            0x1941341605321B2AULL, 0x2EAAC6F199A3C2EEULL, 0x4E3A54F732BBA22FULL, 0x2F5FF507BF92F03DULL, 
            0x9AA0CFE098E5172CULL, 0x2A96BBE956A0302EULL, 0x9A874A7330475C1EULL, 0xD50C9F8BDEF56B63ULL, 
            0x04FB7D05DFF96C08ULL, 0x6F09E281F1C3F7E0ULL, 0xDE57DA0D18E731D5ULL, 0x71DE5CCD4B6E1875ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseHConstants = {
    0xEC9F244DCC13B856ULL,
    0xE543D5A6EBDC56F6ULL,
    0x3466873723E42A26ULL,
    0xEC9F244DCC13B856ULL,
    0xE543D5A6EBDC56F6ULL,
    0x3466873723E42A26ULL,
    0x4FAFD1EF288EBC5EULL,
    0xDA704082B023F850ULL,
    0x2F,
    0x23,
    0x40,
    0xB6,
    0x97,
    0x63,
    0x58,
    0x37
};

