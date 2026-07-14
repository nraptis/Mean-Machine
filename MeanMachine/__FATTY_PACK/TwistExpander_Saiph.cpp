#include "TwistExpander_Saiph.hpp"
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

TwistExpander_Saiph::TwistExpander_Saiph()
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

void TwistExpander_Saiph::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xEA7DB320BE2D4B70ULL; std::uint64_t aIngress = 0xA65322B074FEDE9AULL; std::uint64_t aCarry = 0xFC05E8C8D294D4E7ULL;

    std::uint64_t aWandererA = 0x8456DA36CED1791CULL; std::uint64_t aWandererB = 0xCB4E9692AABF07AEULL; std::uint64_t aWandererC = 0x9A336C7EF8794968ULL; std::uint64_t aWandererD = 0xE36FD7D4FA679892ULL;
    std::uint64_t aWandererE = 0xF0B9710F1D3A0411ULL; std::uint64_t aWandererF = 0xADAF4298FEE2F6C4ULL; std::uint64_t aWandererG = 0xC6CC6BC419189090ULL; std::uint64_t aWandererH = 0xB8427DA9739A2E07ULL;
    std::uint64_t aWandererI = 0xAB74925062F6A323ULL; std::uint64_t aWandererJ = 0xD55C10FD2E066604ULL; std::uint64_t aWandererK = 0xEAAF63D9A9C96E62ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10437452655165385013U;
        aCarry = 12019984028336746294U;
        aWandererA = 12050486041269519803U;
        aWandererB = 13238557330836493509U;
        aWandererC = 15167431150778429157U;
        aWandererD = 10642460097356264010U;
        aWandererE = 9794337731915085260U;
        aWandererF = 12624315332087955978U;
        aWandererG = 12871134444129356646U;
        aWandererH = 9617299689807731389U;
        aWandererI = 10178049559849439807U;
        aWandererJ = 14613191643258466813U;
        aWandererK = 9499813410100224001U;
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
    TwistExpander_Saiph_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Saiph::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x8ACE6DDEBFCE18C5ULL; std::uint64_t aIngress = 0xAFF6F9E0B1B2489BULL; std::uint64_t aCarry = 0xE6217C9E97ED818EULL;

    std::uint64_t aWandererA = 0x93B3E8959ECA88D5ULL; std::uint64_t aWandererB = 0x8BEDED9F5AFE8D39ULL; std::uint64_t aWandererC = 0xB1E68C765F98FBFCULL; std::uint64_t aWandererD = 0x9DD8D5C742BC99D0ULL;
    std::uint64_t aWandererE = 0x8867C7E4255BA738ULL; std::uint64_t aWandererF = 0xFA50DD2F7FBC1A2CULL; std::uint64_t aWandererG = 0x9E00A91EF18A71BAULL; std::uint64_t aWandererH = 0xDE3888A568AF17D8ULL;
    std::uint64_t aWandererI = 0x917974E840255553ULL; std::uint64_t aWandererJ = 0xBA671910D8C180B1ULL; std::uint64_t aWandererK = 0xEC4BC077A4790AD3ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10417066178199820005U;
        aCarry = 12264161113020815702U;
        aWandererA = 9365400204287504010U;
        aWandererB = 11285219445223733242U;
        aWandererC = 13812633470669250199U;
        aWandererD = 14427737414488946540U;
        aWandererE = 11798937971465983801U;
        aWandererF = 9304938180285674350U;
        aWandererG = 16960502058497829232U;
        aWandererH = 14573965523584743791U;
        aWandererI = 16711036283741311082U;
        aWandererJ = 15850396282892716748U;
        aWandererK = 11055180095643377608U;
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
    TwistExpander_Saiph_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Saiph::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA2680BA4C5018AEEULL;
    std::uint64_t aIngress = 0xBB210513B43DA64CULL;
    std::uint64_t aCarry = 0x90139D1525BD9C9CULL;

    std::uint64_t aWandererA = 0xBAAEBC3F21662355ULL;
    std::uint64_t aWandererB = 0xD00968A633B5C830ULL;
    std::uint64_t aWandererC = 0xC7F968C020B09D13ULL;
    std::uint64_t aWandererD = 0xBF38836174C71BA7ULL;
    std::uint64_t aWandererE = 0x8AC20D8E6BBF2095ULL;
    std::uint64_t aWandererF = 0x8F2196C4180DF432ULL;
    std::uint64_t aWandererG = 0xFC98B95040BF3350ULL;
    std::uint64_t aWandererH = 0xC73FA4302D45E9CBULL;
    std::uint64_t aWandererI = 0xED35E8312CA68B9CULL;
    std::uint64_t aWandererJ = 0xFABAA5AE9B3B2449ULL;
    std::uint64_t aWandererK = 0xA347B1D750B9FA15ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneD, 2);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneA, 3);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneD, 6);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneA, 7);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    TwistExpander_Saiph_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Saiph_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Saiph_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 30 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1782 / 1984 (89.82%)
// Total distance from earlier candidates: 52654
void TwistExpander_Saiph::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1064U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 573U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 405U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1781U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2040U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 35U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 39U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 867U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 597U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 142U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1873U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1803U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 269U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1755U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1140U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 609U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 234U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 50U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1713U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 711U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1088U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1733U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1784U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1558U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1715U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 774U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 122U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1632U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1018U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 588U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1654U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 495U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 260U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 22U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 997U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1182U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2029U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 656U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 567U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1875U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 978U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 308U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 505U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1772U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1474U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1334U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1637U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1242U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1025U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1515U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 783U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1495U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1665U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 539U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1255U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1436U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1961U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 520U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1499U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1097U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 54U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1096U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1382U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1508U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 954U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1533U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1331U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 270U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1764U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 551U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1308U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 759U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1037U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 896U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1583U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1073U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1013U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1817U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 714U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 671U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 76U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 379U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1345U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1186U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 979U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 502U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1036U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1830U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 974U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 771U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 453U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 932U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 791U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 289U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1403U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 393U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 295U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 69U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1463U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 326U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 988U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1925U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1045U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1903U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1298U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1880U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 629U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1167U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2024U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 818U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 737U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 279U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1205U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1628U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 703U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1643U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 433U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1027U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1641U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 904U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1919U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 186U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1051U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1117U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1540U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 240U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1615U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1207U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Saiph::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xD6415270325A578FULL; std::uint64_t aIngress = 0xBDDDBD6AB44EBE49ULL; std::uint64_t aCarry = 0xA67A0F552FA1F79CULL;

    std::uint64_t aWandererA = 0x8A9FC36FE1ACA624ULL; std::uint64_t aWandererB = 0xBCDEEC544B37334FULL; std::uint64_t aWandererC = 0xB54EAD3D07831398ULL; std::uint64_t aWandererD = 0xAE87EA458BDFDA99ULL;
    std::uint64_t aWandererE = 0xF9F1576AB095172DULL; std::uint64_t aWandererF = 0xC2CFDE21915B1691ULL; std::uint64_t aWandererG = 0x8545C480D4A82F2AULL; std::uint64_t aWandererH = 0x90F93A8B5EB54397ULL;
    std::uint64_t aWandererI = 0xF607010F0BD9AAA6ULL; std::uint64_t aWandererJ = 0x956A9746F1C6B18AULL; std::uint64_t aWandererK = 0x845AD146EF7A0180ULL;

    // [seed]
        aPrevious = 14752844057734342802U;
        aCarry = 11601162626980277580U;
        aWandererA = 17690126352411058647U;
        aWandererB = 14451651042242166044U;
        aWandererC = 9448940238380237608U;
        aWandererD = 15925840258031803212U;
        aWandererE = 14375947622069380518U;
        aWandererF = 11588947208502018275U;
        aWandererG = 10121813085440529758U;
        aWandererH = 16336361030786164211U;
        aWandererI = 18425488807593888845U;
        aWandererJ = 13330934966148154025U;
        aWandererK = 10904114899584831069U;
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
    TwistExpander_Saiph_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Saiph_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Saiph_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 30 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15681; nearest pair: 498 / 674
void TwistExpander_Saiph::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5534U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5398U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5835U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5454U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3810U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7516U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 455U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6060U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1172U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1672U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 24U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1560U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3110U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6262U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 984U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3950U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1560U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1443U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 842U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1635U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2042U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1722U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1282U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 12U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 960U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1681U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1504U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1999U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1482U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 818U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1118U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1473U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 816U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 374U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1040U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1744U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 30 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15681; nearest pair: 467 / 674
void TwistExpander_Saiph::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3799U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3536U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1063U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6927U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4310U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6914U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6575U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7084U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1055U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5404U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2267U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 968U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5474U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1384U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3857U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7376U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1564U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1377U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1847U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 631U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 805U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 998U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2021U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 988U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 259U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1909U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 55U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 63U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1980U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 224U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 525U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 625U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1688U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1204U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1277U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1035U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseASalts = {
    {
        {
            0x1B010BD55B2C8094ULL, 0x1FE7C7A8A6646327ULL, 0x191A8631909E0C10ULL, 0x01C6A12F3005FA7BULL, 
            0x444A74A9F396A84CULL, 0x54A63A68C6434250ULL, 0xCE9A15E22E311CA1ULL, 0x0AAF049902CF0749ULL, 
            0xB9377A5507BE3A01ULL, 0xCD16AA6FA12A7A19ULL, 0xDE010B1D715384B8ULL, 0xCB9AE856D867DB8BULL, 
            0x3CCCD53970161B2CULL, 0xE4BEA295B26ACEB0ULL, 0x6C1D4F2C08DCBD3AULL, 0x8F31D69E76654C31ULL, 
            0xAC7D049F1F40993CULL, 0x3D129DC2A6B1228FULL, 0xD631C51BB324A0CBULL, 0xF3772E9C28C8725FULL, 
            0xBDF94234C6500012ULL, 0x9DA889AC6AABC58EULL, 0xEB608DA7F1DE6FAFULL, 0xD3D422E1B03CE311ULL, 
            0xEF3A75AA2FB12C88ULL, 0x289FE8104087D087ULL, 0xF4C64099F63E1FCCULL, 0x867F035F55A6D475ULL, 
            0x3389F3E1E297C66BULL, 0xF5D736B9B0742FD7ULL, 0x7C4E8546FF6F346DULL, 0x1ED6EAC9A3DB207BULL
        },
        {
            0x112E9CCB1CDD9B39ULL, 0xB5FE948452C471A7ULL, 0x0DEB02C5287637FDULL, 0xC5A7870E03BB4381ULL, 
            0x5CF0A5450D09E8A5ULL, 0xA8D4527E04C74A19ULL, 0x69599586D0DAE22EULL, 0x8E4979004E821DC8ULL, 
            0xD15F054472E15A09ULL, 0x04F83D02B554FDB9ULL, 0x09FFC14EB495BB61ULL, 0x82EA3FDF8D059E0DULL, 
            0xE22C3A7D7B9B4944ULL, 0x87A73E37DB380944ULL, 0xBA6EA4109A275C0DULL, 0x3192DEE26C04E122ULL, 
            0xFF5764B97C6E2BBFULL, 0xE3F302A0B90FDCB1ULL, 0xE207B79C446AFDEDULL, 0xD829D58A0ECC5C85ULL, 
            0x5D3D99724DE6437DULL, 0x3EDDB6EBB7367A85ULL, 0x06871CB971A25EB3ULL, 0xED0E4062142F591CULL, 
            0x6936E7056D92E2BFULL, 0x5C3F41EF4292B44FULL, 0x5C7E925FCA891160ULL, 0x2A16AC36FF641297ULL, 
            0x0D41DB8F4389B6A0ULL, 0x0BFD931C30749406ULL, 0xA53EFDECC2688896ULL, 0xDC677A7435A242D7ULL
        },
        {
            0xFDFA8AA0343EB432ULL, 0xBAF003F60A304425ULL, 0xACF324C48D1920B9ULL, 0x2E03EE01493D5404ULL, 
            0x34DF1F24007A390FULL, 0x7C9EBDDD20518E01ULL, 0x79874260F455E9D3ULL, 0xB4A629FEE780F3E8ULL, 
            0x6DA6171CB5D6D0FEULL, 0x3D5F9B0F28CA52CAULL, 0x7DBD4D48C69F74A5ULL, 0x631045822413B050ULL, 
            0xE5EAEB2F02F3709CULL, 0xB7E032F4D5C291C3ULL, 0x08B5E48F7854FC2CULL, 0x5047B7D4A8D2E2EBULL, 
            0x7A80A50DF31FEC09ULL, 0x2E7B33E3D1A2DABDULL, 0x6EC890F17E0E0CD2ULL, 0xF8256FEE7F6EC67DULL, 
            0xF2FFD8A140742964ULL, 0x3571AA5D9D60A88AULL, 0xE5CE0B211CA06FFEULL, 0xE88A7CC1949B975BULL, 
            0x04A99DCD1D670CAAULL, 0x6FAF28FDCCC15DB2ULL, 0xDDDC181A0064CBAEULL, 0x26CF41607DCF5D07ULL, 
            0x121FC63365038DB6ULL, 0xD8B8327E5067A2F4ULL, 0x1B73B7C4974875C8ULL, 0x75DD45C716528240ULL
        },
        {
            0x51C8B4B3FEBC3A72ULL, 0x47A42EBE808DF508ULL, 0xB85C0A6791FB0D56ULL, 0x84501F2FE7EDFA02ULL, 
            0x4139115059E45E7BULL, 0xB2A69DFE8532D5A5ULL, 0xA1C92F4BE04A0ED7ULL, 0xBBBC48A443704434ULL, 
            0x05F73F41F2AC8CFCULL, 0x3EC4927ED6104419ULL, 0x0207D29A11CCE0E6ULL, 0x2371A0BC3AB396CBULL, 
            0xEEE1872756E9253AULL, 0xBB9ABF0B27685FDEULL, 0xD5D90837A8C80EA0ULL, 0xB76C98E1BF99BB37ULL, 
            0x270A095A27BE1F0DULL, 0x604D1750C73E6C2FULL, 0x849ED9175214AAA0ULL, 0xAC7F7977D890932FULL, 
            0xE50BBBF483972FA3ULL, 0x0584B971791B4DB1ULL, 0x864B43F0759C4220ULL, 0x9FD6D2F0FC66EA38ULL, 
            0x282077F9ECE7ACD6ULL, 0xB6412ED6003D806EULL, 0xED6771233544E5D0ULL, 0x4F89ED1ED36134F9ULL, 
            0x30531CF4C3FE9455ULL, 0xEB7DB221224B6D71ULL, 0xB8C5045AD77746A3ULL, 0x019610273F273B09ULL
        },
        {
            0xF5A5F3C8B75883E6ULL, 0x370A0632CFCE995DULL, 0x1DFA82D84C312454ULL, 0x0D8610A94F35627FULL, 
            0x4E9E02C368D09AE8ULL, 0x536F3D4AD70C6B35ULL, 0xF69ACEC5C6866BC2ULL, 0x3578AC2B74907BA3ULL, 
            0x81C2F5EA612409B4ULL, 0x2C18655B021BF5D2ULL, 0x4A9FD325A7CBA9DEULL, 0x1A958A44EFE5B4F3ULL, 
            0x948BFC8DCB0B5B7DULL, 0xD855D93E8425B901ULL, 0x91FF3F7359A86A37ULL, 0xCB9F8CE15716E94EULL, 
            0x559DB5D3E4BDF5C0ULL, 0x47A5BCFD932882CAULL, 0x9F5A6C5F3288D8CDULL, 0x394BF0095D6B469EULL, 
            0xFE1FFE508F58B25FULL, 0x9247694EC404F664ULL, 0xB4446B45E3D9EFA3ULL, 0x44C5FED570965E29ULL, 
            0x6F25A0F44A3CF93AULL, 0x68DABECEFCB6CBDFULL, 0xB61E9A474C1CF65FULL, 0x4E3F476B59A47467ULL, 
            0x384A78EAD1966016ULL, 0xF8BCEDDD75145AC6ULL, 0xABE7031C1D619E4FULL, 0x26B0D8A39608E314ULL
        },
        {
            0xE844979B45868B6DULL, 0x24213CACC94385BEULL, 0xFAFFC82CEE51BEC8ULL, 0xC26D15E862CDD8B1ULL, 
            0x1521301D2B9B647EULL, 0x28AE0EA6011DB098ULL, 0xCF416D340435DD7DULL, 0xCF4646FE46D06916ULL, 
            0xDEB4225F3CA580F9ULL, 0x8A20F6DDC7962ED4ULL, 0x6039BDA7DFCB9C0AULL, 0xF69C51A18870E0CBULL, 
            0x1027CAFA0D545826ULL, 0xA0C5809E294F2AF4ULL, 0x00F18371410FF8AAULL, 0x5E5B1F514F4F5E99ULL, 
            0x1B88692C299351D6ULL, 0x517B1E493FA44071ULL, 0x9626BF9FCDC063EDULL, 0xBAC44EC8E8738D39ULL, 
            0xBE26D8363DE8BFC4ULL, 0xA19C442F48FBE7BFULL, 0x165321F54ED95B3EULL, 0x7B6761675502C152ULL, 
            0x55092179D3D308B0ULL, 0x306B86AE27A087DCULL, 0x4BD7E4E7EEE8767BULL, 0xC1203212072D554AULL, 
            0x27BD1B358FD890A7ULL, 0xD0AC19F7D2D59F90ULL, 0x9A30E45737F27FB4ULL, 0x07CBC618FFA2E33DULL
        }
    },
    {
        {
            0x41B5D46BB0EFA4A9ULL, 0xBC1ACE8560633183ULL, 0xA2BA8EB99EF7E370ULL, 0xD297B60114473732ULL, 
            0x2D42D57B68EDAD2DULL, 0xAEF5DC94230E6A90ULL, 0x0509A5771F5F60B6ULL, 0x5353B26EAE3FACFDULL, 
            0x4B8A0F5D5FB78696ULL, 0xC912DDA839E027F6ULL, 0x5B4376E6C210A53EULL, 0xDF07F781EF95DE7BULL, 
            0xAD92205912227F25ULL, 0xFEA856A2F572A485ULL, 0x54409DBA780E0354ULL, 0xD8BE1CDD968280F8ULL, 
            0x86266B45D67EAC79ULL, 0xC6C2CB4BCDA9F889ULL, 0x6D207DC597C44466ULL, 0xFE5344473EF4BFADULL, 
            0xDD4BBBF1FDEC9FC6ULL, 0x42FE738571CAA9B3ULL, 0x117DBA234241167AULL, 0x6DF10ACC114CEBB5ULL, 
            0x69A88C9E04AA8A6BULL, 0xB9D33055F31A2ECDULL, 0xC2394FE2FA7A40E9ULL, 0x6D526FEEA4F0E340ULL, 
            0x7614AE2014ECE76FULL, 0x5E631136499AA933ULL, 0xDCA5D8A86B326B24ULL, 0x31DD597B5E79F76DULL
        },
        {
            0x714F31D76DF451D7ULL, 0x5971D23A99869ADCULL, 0xD71F4F7A4128D0BCULL, 0x80273E751C28A7C8ULL, 
            0x8DAC1348F5BA3128ULL, 0x744B92F2079EF4CEULL, 0x0F2E377D5AF56FD2ULL, 0x1797FC6464A440D9ULL, 
            0x5EC74B3E46F4ED46ULL, 0x7A7F5721CCBDB617ULL, 0xE66A75423008BE0CULL, 0xB28C51E9C2E607DDULL, 
            0xEEE435084E46986FULL, 0xE34CA4673392210EULL, 0xD1F782E3BCF80B5AULL, 0xC92B0962C885953CULL, 
            0xC8E1F1ECC5956590ULL, 0x1C0F234C92D15CC9ULL, 0x687B4874A53E1D7FULL, 0x4C975363870EF616ULL, 
            0xF35AF507FB247EFEULL, 0x7A7B700A5C19F0B5ULL, 0x32A2A76BC9822162ULL, 0x0FE9BC2379BEC9B0ULL, 
            0x3E0FD8D1F5D137D3ULL, 0x605E143DD64630EAULL, 0x3B0DBC68818359C6ULL, 0x6AFB284B2223FBCAULL, 
            0x385196AC9CAE12D7ULL, 0x227765BEC5D40A02ULL, 0x3B61B91C58E573B3ULL, 0x0067148596230E8FULL
        },
        {
            0x09820E48D60C7E92ULL, 0x5DABEA160C8B5A22ULL, 0x0583FCB64BC7B9E7ULL, 0x81AE846E0C2FC946ULL, 
            0xFFDDC99208794C6FULL, 0x358410647D289451ULL, 0xF986648B4C5369D8ULL, 0x83DB62736766BD53ULL, 
            0x7FAAF4F0D0F0D3CCULL, 0xE86FC16A5C3E46DFULL, 0x621AC4C5E0861828ULL, 0xF55BDE88E8068671ULL, 
            0xAC8A25EF334368D6ULL, 0x8F7DB83FED0B22BCULL, 0xDFA7A3C42F55833EULL, 0xCA47C124E2B7C208ULL, 
            0x08D0A846E2CA0E87ULL, 0x70B1639124BD8A1AULL, 0xC2DFB02D14544F73ULL, 0x04BED3DDC72BAF5EULL, 
            0xD517CF22C2A65557ULL, 0x2C4377004F7B4CCFULL, 0x9EA0A4E380597444ULL, 0x8858C2BE057104A1ULL, 
            0x04302499984EC33EULL, 0x48DF772C833D3386ULL, 0x69624B53413FF7E5ULL, 0x85F398EFFAAB5CFAULL, 
            0xB66F3517E6A1B757ULL, 0x9C7548BA83838251ULL, 0x8D7124DDBCF67079ULL, 0xFD1C5C52F4FFBD14ULL
        },
        {
            0x719D99F80AEF16BAULL, 0x13F8AC6994291551ULL, 0xBCD2DC7E06D6E1D0ULL, 0xEC92555807A5998CULL, 
            0x56CD5A979272CD71ULL, 0x21F63ED0671533B6ULL, 0x8C6F28BDF4F4CA89ULL, 0x60E4C9204536EB65ULL, 
            0x7FE65442927E9656ULL, 0x7603747FA0A944F7ULL, 0xAEE7D226BA66F873ULL, 0xCD72F1D04B9FF747ULL, 
            0x9AB389C02FEA4F9EULL, 0xBE1FBD0D0EBB6114ULL, 0xA005F94168F2AE41ULL, 0xB24B6E92001463AFULL, 
            0x1EC9C3C9F224E3F7ULL, 0xC5A7DF2123467FC3ULL, 0x288E4C09E4397744ULL, 0xC10F90D3A246F4FEULL, 
            0x7F1658BE2BCB986EULL, 0x1AB54A1BBCB6C323ULL, 0x10C7B3D1A25EB2C0ULL, 0x74084ACDAA2037B5ULL, 
            0x128D59A970F1C0C0ULL, 0x394FBE110B5AACE1ULL, 0xA1DF3921683718ABULL, 0x7FEA3F36A0C501F8ULL, 
            0x0BB2CFCB68DB2BC8ULL, 0xCC95C24F3A703717ULL, 0xAA2EECE67210E06AULL, 0x41FC35D4F4F1F92BULL
        },
        {
            0xF1814AC6BE752D63ULL, 0xD6E2D90E1872D252ULL, 0xBABE48E09FEEDAF3ULL, 0x2B5ACBD5FAB57B20ULL, 
            0x8FDE7A4B34FF1879ULL, 0x9057F7FE94B33C9DULL, 0x0DCD2B21C42B597CULL, 0x1D31E0012A896A24ULL, 
            0x7580533818120ECDULL, 0xC93A96C61D8ED1CDULL, 0x315D9A7549D1E494ULL, 0x77E2EC5CD7038A3FULL, 
            0xEAE7B8962DBABE9EULL, 0xCB606136CC652296ULL, 0xFAE12F01AAB61122ULL, 0x3B0BD2BBFE55C035ULL, 
            0xD1CECBF4FE310BB1ULL, 0x5C1CCEFF72033E3FULL, 0x7153AB57121EE8C4ULL, 0x05CFD7C213C8F531ULL, 
            0x99AEB3D99B220394ULL, 0x93C6082B9E945588ULL, 0x63D633543797F6DFULL, 0x3602B0F0FF2CAD79ULL, 
            0xDF15BA229E7166B6ULL, 0x86AB1CF5D5C57581ULL, 0x364E1EE5AA06D6BCULL, 0xC5FD95C5A2ACB113ULL, 
            0x52790327C6EB5A52ULL, 0xAF5E755D1B224811ULL, 0x0066647F0C61BDE2ULL, 0xA95D191AEBC543E7ULL
        },
        {
            0x2C96DADF598EE62DULL, 0xFAEDE5971FE07C25ULL, 0x99487D281B8A9A77ULL, 0xD92788DCBD8819A4ULL, 
            0x76DAF28D711F1973ULL, 0xEE90867C9DA1636DULL, 0x8E55D01F49D8707BULL, 0x9986C97F4ED30F8DULL, 
            0xF265138E0A0D8C9CULL, 0x3DC10D3F36FC0833ULL, 0x93B0238FD9E3CE74ULL, 0x009C2E105785C88FULL, 
            0xF53C843343004775ULL, 0xB3E53E33C0D2576BULL, 0xC544C5C3BF714830ULL, 0x61CB04484E1B3348ULL, 
            0xB8DD14D74CB96FDEULL, 0xD8D0407B04BF3A2DULL, 0xD2EF4BEC6BA212CFULL, 0xD0583BCBBB0A8023ULL, 
            0x54BE05508A06474BULL, 0x025EFFA6B629F8B4ULL, 0x2E1E66732A5E86ACULL, 0xFD5833988A32D72EULL, 
            0x623EFE7D0D390D69ULL, 0x4FC533BD80A3BFD7ULL, 0xC2927FBE3CAE46C6ULL, 0xE2C828F9C0F249A6ULL, 
            0x2CCC06FED707F141ULL, 0xC253AB3C1515B3CAULL, 0x1BDDB3BDD65F8E5EULL, 0x4623AAB64AAC228DULL
        }
    },
    {
        {
            0x15B7CC434B82A0BAULL, 0x209695C5860BEC46ULL, 0x9E289E81A3E4C71EULL, 0x390FB98834371A7BULL, 
            0x2E1B4867463E8F1CULL, 0xF6B31EA342F4BC65ULL, 0xC5BA94CA1D15A1BBULL, 0xD22670070C8F428EULL, 
            0x38DF820A2FF9781EULL, 0x56AF0EB3900B5707ULL, 0x12D68A27CA48C90FULL, 0xBCFD274F00A4B3DAULL, 
            0x41BE8ECAC8A0610EULL, 0x4B36F6DF9B311592ULL, 0x3DF12F397DCCEF10ULL, 0x6F80475E924D9A25ULL, 
            0xA93B1B485005E4DDULL, 0x73A2D0277DA8D161ULL, 0x0A1160788A8AD93BULL, 0x79F078AA3BCB78CEULL, 
            0x6125543AB5BF544AULL, 0x6280E6B4A16AD8A1ULL, 0x21F8521615BE7382ULL, 0xB66392FAFF1DC669ULL, 
            0x65A195E8C5DC186AULL, 0x665A4B8C1BC9AEEBULL, 0x32D06F3F3D2E5F99ULL, 0x787799702CF239EDULL, 
            0x8A3114914803D12FULL, 0x8CB2B6203399AE27ULL, 0xBDD2872E8DD498D5ULL, 0x6BCF4605873442FBULL
        },
        {
            0x20027982969F4FC9ULL, 0x355734DAA603F2F1ULL, 0x5B596066D841D091ULL, 0x6D8F5136281DC090ULL, 
            0x4BA48F7F5EF4799FULL, 0x83452D922828FE21ULL, 0x2404CF419CF9EF83ULL, 0x57E92C12924D9EDEULL, 
            0x0F7AD9C027E7CEB4ULL, 0x5535B0B9A8E8BA8DULL, 0xBA8967C092C613AAULL, 0x1DA9670DBCAAA567ULL, 
            0x056054807739DDB2ULL, 0xBD7E5C8ECE764EBCULL, 0xF5F41750A24A2461ULL, 0x5E31AD1C8BFFF7FCULL, 
            0xBEEC0F837ACDB5E1ULL, 0xA3E772745E1D3DDFULL, 0xEE16FDA482763655ULL, 0xEA29EF4D7A3CBCDCULL, 
            0x734CE9ED25AF255FULL, 0xFCB92FB77DE96E98ULL, 0x3AAED0B3101E9685ULL, 0x9B6D4F306F8BC710ULL, 
            0xCF347C3B904CCCF2ULL, 0x7B43996CC474EC6FULL, 0x9F562EB1FA365C50ULL, 0xB8D97C7396543474ULL, 
            0xB85AA613E015415FULL, 0xD64AFD058295515DULL, 0x22CA15DBA4DF3B70ULL, 0xCF40074948514980ULL
        },
        {
            0xCFD2448C562C9148ULL, 0x3D1C4420AFE5F778ULL, 0x6A7C107CFA1592EFULL, 0xD3B0D50CD413CEADULL, 
            0x4950EF26A96D63C6ULL, 0x71507615E39BCA86ULL, 0x16BDF7000960F671ULL, 0x0F92022E01ECDE5DULL, 
            0x4D682D7E2D0FD87AULL, 0xCD96CB7E51DFE3B3ULL, 0xCABF26314F6DADDDULL, 0x9B8AF2B20D362075ULL, 
            0x3E57CCEC18B70430ULL, 0xE0E55AF62BE03326ULL, 0x7303B32533A9A4F4ULL, 0xCD4401AF49B32490ULL, 
            0xB8B9259D463AFA42ULL, 0xB6B22A5B9C94F9E2ULL, 0x6DB9FE6771D59068ULL, 0x5FDA1D24197049C8ULL, 
            0xE5D164AA6945C31CULL, 0x877DE171B306988BULL, 0xADBFD9877C02629CULL, 0x5AEC1492EF1A0A81ULL, 
            0x1BF55DDCCFD27B79ULL, 0xD853788A4BA12D0FULL, 0x4C9CC2C6090948D3ULL, 0xE8A6CE6226D66EF3ULL, 
            0xFB66894ADA2CB522ULL, 0x23C684839AB06DA4ULL, 0xE75B19576C31417BULL, 0xD02B732A23D1F0EFULL
        },
        {
            0x78BDBDB463BEC578ULL, 0x1FA376E373AB5271ULL, 0x8C5A09F3B76D1879ULL, 0x9422C2AA34288BBDULL, 
            0xD402E95340D07D42ULL, 0xE5E3F07E6CEBBA20ULL, 0xD6F9B001E30F043FULL, 0x257BD39877B2DDD8ULL, 
            0x1ECF643E8BF365DDULL, 0xBAB16D058CD773F9ULL, 0xAED6684DDCC08A75ULL, 0xB95A0305D16CFAE2ULL, 
            0x371DC001A4727DA0ULL, 0x6A0FC95EE0F2C7F3ULL, 0xAACB578DDC558D4BULL, 0xF92024757C44A838ULL, 
            0x0A66D9730F5673AFULL, 0x1A31FC9DD6B3D6E9ULL, 0x753ABD9E282AA4DFULL, 0xE277F9CCE0FB70D6ULL, 
            0xD2193FC06E7A3A14ULL, 0x8ED8C43442A3ACC1ULL, 0x8A45A832517B38BBULL, 0xD3FA2A49BE744432ULL, 
            0x9EDD9866598DC771ULL, 0xA396B863FC358C4BULL, 0x2E8954B575707444ULL, 0x275BC8645C08A601ULL, 
            0x42DE0AD8005BCB83ULL, 0xC40AB3BFDDB4663DULL, 0x92EC82FCC1BF342BULL, 0x2715063BCFF677BCULL
        },
        {
            0xE2D51080B5AC4C11ULL, 0x75F2A846BDBBD4D5ULL, 0xBCE3E259D9425C2AULL, 0x7D677C439446DD24ULL, 
            0x36F6BA7CA058463BULL, 0x5F8AD3F44F8EB2CCULL, 0x03D91E0241C838D7ULL, 0x94B8018F53A5F827ULL, 
            0x1B84CF2BCF662FB2ULL, 0x8865BA30B8A26C74ULL, 0x8D1100F2052CEA5CULL, 0xB05954A9252F423CULL, 
            0x03F7685AB07CDF68ULL, 0x3202A37CA3EBACF5ULL, 0x53A5E860B9A56B89ULL, 0xB3562C7D3B14C3D9ULL, 
            0x1EE388D18ECE7BECULL, 0xEF2AF6BBBC5315AFULL, 0xA5EE9562B626AFFFULL, 0xBCE4FE715271414CULL, 
            0x9524A57A199FEAD5ULL, 0x1B5A6A8097C13F5CULL, 0x4BEF633F7B34DCFAULL, 0x1D5A7935A193DDB8ULL, 
            0xF4D53624F74A7052ULL, 0x0CCB87AFEDB60C30ULL, 0x8578C421F9AA8196ULL, 0x3763EB1BF42C9311ULL, 
            0xBE7B5DE689C33353ULL, 0x0876DA3572843FF8ULL, 0x6FF77C51CB8C7A94ULL, 0x2EE1EC7832EB8028ULL
        },
        {
            0x3DC6BD0A1760BAD7ULL, 0x851CE947CC3FFB0AULL, 0xA10E2A4AC03A53D9ULL, 0x1EE0AE393CF03ABFULL, 
            0x272631D9A3D68950ULL, 0xC0D6384AD6FDE9B6ULL, 0xD98069C93D363840ULL, 0x3F2197ECBAB6EA2BULL, 
            0x92D465EE5C0BBB64ULL, 0x86EF18C4E32ED1FCULL, 0x46C3EC62CA2F5BACULL, 0xD4896CF760550FC9ULL, 
            0x92CB0D97ABF26AB8ULL, 0x5B6FBD72B73C8B23ULL, 0xF757F12E228186F9ULL, 0x6025D59DA4B11D16ULL, 
            0x8629DBF1C77EB0C9ULL, 0x9CB15C4E04C95FBAULL, 0xDF7F7914F665B72EULL, 0x6505FAF864EE6980ULL, 
            0xD0F97D03F8759860ULL, 0xCE1FA68DE0947467ULL, 0x53CA84EC64362550ULL, 0xACCC5F5F45DECF76ULL, 
            0x209A7689F66182A4ULL, 0xA148C62562147A25ULL, 0x1A4E6C1D6E4EB7BCULL, 0xB0C3BE742CA2377FULL, 
            0xD8BCBB1F8C36667AULL, 0xA96678D66C7405FEULL, 0x771CF139B51F0C0CULL, 0x34BF60D2F5AA0E69ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseAConstants = {
    0xD96373CA9028DFA4ULL,
    0xFCB884B6C0D63035ULL,
    0x5C473C9BB5FD1645ULL,
    0xD96373CA9028DFA4ULL,
    0xFCB884B6C0D63035ULL,
    0x5C473C9BB5FD1645ULL,
    0xD1F2315C6A128E97ULL,
    0xB0269AE3D37BF76FULL,
    0x18,
    0x77,
    0xE7,
    0x53,
    0x29,
    0xEE,
    0xF1,
    0x4F
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseBSalts = {
    {
        {
            0x384D92FB3989104BULL, 0x398ECCB2A3FBDC25ULL, 0xB91B9CBFC30D4A27ULL, 0x757CD0B0797DB31BULL, 
            0x8EDE2F03FA41FD96ULL, 0xD02AFAE093B41CB0ULL, 0x488FE5577B082D2EULL, 0xF3408C77512674A4ULL, 
            0xC1594655AC883DBBULL, 0xA4FDE97872609F30ULL, 0xBBAD40CAE6C1A73BULL, 0x3FA3A999711C9EC3ULL, 
            0x535F4A60F06E4AAEULL, 0x1E43762E2F9186ECULL, 0xF447807F126D3061ULL, 0x78183F2A4B75C949ULL, 
            0xF0FEF97C3389F7B9ULL, 0x5DE928FCC5C1E778ULL, 0xEF3C6133AAEF21FCULL, 0xF4375F6D1ED7A702ULL, 
            0xE7F0B6D7BF81D8D3ULL, 0x50291CDEF497CF94ULL, 0xC839678972CA94C7ULL, 0x9C151BC7CA45104DULL, 
            0x8E666963B1AEC4A3ULL, 0xDE53E5CAFA4BB631ULL, 0xFBE42E2F9C69FA87ULL, 0x853E19708A8AFE00ULL, 
            0xDC89F9A92AB65E0AULL, 0x4A7B853A3DB5CB67ULL, 0x6A0229C595E7B9DEULL, 0x3A60B0CCBCA5CCAFULL
        },
        {
            0x37630008542D84BFULL, 0xB993C79EEEC65D06ULL, 0xD7D00497965F65EAULL, 0x52F431594F60E93AULL, 
            0xD8C9CD061DB0931EULL, 0xF950ECB933DDB547ULL, 0x262E009C5AB471F6ULL, 0xDE4E8E0E620B2B51ULL, 
            0xACF5864E358A0E95ULL, 0xD7426CB1E5FC7831ULL, 0xBE0A9C404D9C41D4ULL, 0x48A4956C3F7A1945ULL, 
            0xD43427AFC3883B0CULL, 0x0FB5004A36115046ULL, 0x695D292DA57FD1ABULL, 0x0F8CC5E9015C9C75ULL, 
            0xA42399A2790EC72DULL, 0xE21B221621C4F9D1ULL, 0xA187A21C37CFC675ULL, 0xA5B6C8627E42B335ULL, 
            0x73CFFF105875984DULL, 0xB70E9FCD3639CF70ULL, 0xF629FC162B4750ABULL, 0x24AFE331B4644854ULL, 
            0x2347AEAD99C843E8ULL, 0x5762A96ABF33888FULL, 0x38A2F95A5C4B416AULL, 0xB4A374B26CAC9FFAULL, 
            0x3DEA94E61467C514ULL, 0x6815053F7EC18E2FULL, 0x63CF32180367C414ULL, 0x878C2C60F54B3413ULL
        },
        {
            0xB065B331F5EEBD68ULL, 0x9F36E6E1845185DBULL, 0xB826EFB754B26010ULL, 0x8AD69918972EC971ULL, 
            0x4C1CF4B8BBE54BABULL, 0x285F9B1C2121E413ULL, 0x8C3183D12B1C28EDULL, 0x46AB7FE01D3D232FULL, 
            0x1096F7A0354A8ADCULL, 0xAB7F1A6A376CC4C8ULL, 0x2CDBDCA8945DCE5CULL, 0x9C3C7AED7360668EULL, 
            0xF55329050D07ACBCULL, 0x40574EEEDEB44B67ULL, 0x3B20784D67B3362EULL, 0xE234019B76F28FE9ULL, 
            0x89D17EDD59ED60C3ULL, 0x96882CBAEF270476ULL, 0x6876E4577F839B63ULL, 0x1E8426C5E92CFB3AULL, 
            0x087069EFE923FF9DULL, 0x1AE7D375A03C6140ULL, 0xCD71F2ACCDE3D5D5ULL, 0xB180473C2C942EEEULL, 
            0x503152E98A005F41ULL, 0xBCF2584AF49C6A72ULL, 0x57E77ABDA234A7C9ULL, 0x9C3634B7F06BC84DULL, 
            0xDCD74E99F67274FCULL, 0xCEFD59A6E2461CA4ULL, 0xF1F93162585F3B13ULL, 0x56D388411840E4CCULL
        },
        {
            0x73D304ED51214DB0ULL, 0x5835D6D6E4AB067FULL, 0xF4FA45FC10D8C26EULL, 0x84ED725CFDC82E44ULL, 
            0xA269C1BBB66FD7A1ULL, 0x2188BCD80A8931D6ULL, 0xDE9A3874A6ED7D2FULL, 0x91E5D73CF276EF9CULL, 
            0x34C4808F1E3BC716ULL, 0x512CC2FC0A546A79ULL, 0x5EA9BA93749EECD4ULL, 0xDEA653D960DA12B2ULL, 
            0x5290DB6E26730E76ULL, 0x41388827921D81E1ULL, 0x63F6990ADC72E745ULL, 0x642ACBFFDAB6E7C5ULL, 
            0x59644B3A6EDF2A6CULL, 0xD0BDF2EB3CC4988AULL, 0x2753862AC640CCDBULL, 0x0E78558028C45D4EULL, 
            0x4B6733F5A37B73B3ULL, 0xBCBEEF80B70E175AULL, 0xBD0699D770B6AEA4ULL, 0xC7D42107BBF19952ULL, 
            0xD420481C0764F31EULL, 0xFB1258529DD67132ULL, 0x697A98186D6BC55DULL, 0xA45DE24E09A58787ULL, 
            0xC25F7CBCD05DBF4AULL, 0xB439F715D657CAC9ULL, 0x40D65467CE133194ULL, 0x0838972AC9009F18ULL
        },
        {
            0xAA68BA881FE3AADFULL, 0x8B0E8E4F8EF0630FULL, 0x46B9E71232998900ULL, 0x50180FFF5C03C3A3ULL, 
            0x23ECBB84A9FC8596ULL, 0xFE01BDBF7E019AE4ULL, 0xCAD566E99521ACD7ULL, 0xD55DC06E5B2D4CABULL, 
            0xA0FB242EB732E781ULL, 0xF2C7F7E4E5CEB81DULL, 0x1F6ACD53981899EDULL, 0xF2599F09A5E3ECE0ULL, 
            0x055EF7C70FFE0FFCULL, 0xB51018CAE8CFF982ULL, 0x450374C2FBF59EA5ULL, 0xDC365D4A97DC4903ULL, 
            0xC58A6EFC02B4087DULL, 0xB418FA2567343351ULL, 0x683E921A1BFBAE8BULL, 0xE6CF90B74F80D10FULL, 
            0xFAAFD0874EC26721ULL, 0x61B5CE79A7BAE2ABULL, 0x364A27D33B01DC1CULL, 0xD9D2C98B62E14E21ULL, 
            0x3C2242CDF98DA480ULL, 0xA03B6F947FDEA2DCULL, 0x809D84360672D714ULL, 0xD24A43DB383E83F2ULL, 
            0x80D676FFE8BBC1EBULL, 0xB8D93AAA1FDA58D9ULL, 0xC8873EBA22DD596AULL, 0xE428DFC7C09608F3ULL
        },
        {
            0x781F0093A42AB1BDULL, 0xD8A4118473FDBDF4ULL, 0xFEB63BB9ECD4FE30ULL, 0x09A1AFA9A0078828ULL, 
            0x9E8DF5312969CFFAULL, 0x41D6E639CABC2917ULL, 0x721C9B8B194291C0ULL, 0x864F77F1623BFE76ULL, 
            0x5CAC2FDE74B1DF09ULL, 0x602C5A61AE55F376ULL, 0x9BFED77F1B4BB0BDULL, 0xFE61FAEE31477528ULL, 
            0x490F523D03676D16ULL, 0x905E14B604FC18E2ULL, 0x6FD235FBF4EBD8C3ULL, 0x312A358327B60D43ULL, 
            0x0B0B4990E5541B67ULL, 0x1E74F6E16F987A53ULL, 0x900DF6E7D6E09431ULL, 0x151D195095A037FDULL, 
            0x41A3CE9C9284136FULL, 0x44C796B4598E767BULL, 0x941EC123FBB537DEULL, 0x4716904E478AA925ULL, 
            0xEB43DF23B1A3080FULL, 0xC303F887071F9892ULL, 0x1D67029CD7644CE9ULL, 0xE0002BA06F629D3DULL, 
            0xE9326609960E8B34ULL, 0x36C3E7533033CD4AULL, 0x773C3E2C5155AEDFULL, 0x299D5166E0AAD793ULL
        }
    },
    {
        {
            0xF8AE360FED4361A1ULL, 0x489A0C57EA8D3FF5ULL, 0x3EC9841907EB18B9ULL, 0x7F1733320A88E7FCULL, 
            0x254671B2B0A03225ULL, 0x47B05AE1E43C0CB6ULL, 0xA5DCE1F87B1C444BULL, 0x3E70AF76DB29D13EULL, 
            0x30A044759F3940BCULL, 0x10BB13CC154A05FCULL, 0xC00D9001E4C71035ULL, 0x011A9D40D63C3BFCULL, 
            0x940EB2576646E55BULL, 0x009E6C06DA0827CCULL, 0x78795466B18437D2ULL, 0xF1DC5E96FA63CE07ULL, 
            0x6409786D4E3D2EE0ULL, 0x82696F07CF0661BDULL, 0x572AEE6315E862E8ULL, 0x46899EDA72EEB2E0ULL, 
            0x7FBA2CF0B23BDF62ULL, 0x49F3B97018A0B4D9ULL, 0xB994459D4841ADC0ULL, 0x856C3BC0B0294670ULL, 
            0x0063AFE9FC0B80C7ULL, 0xAE975FE89F31514EULL, 0x80A3D96A05E8FF61ULL, 0x94A6D1A039D34836ULL, 
            0xF4A674A3FCC4A585ULL, 0x20B644587CC6BCC3ULL, 0x0A8789BEC61B835EULL, 0xD9ED08E540DB7837ULL
        },
        {
            0x2C6F4C0908945557ULL, 0x000A014763E09BDEULL, 0x1245E2740450BE39ULL, 0x2DD8A55FEBFDD3FEULL, 
            0xAEE80171B954D13EULL, 0xCBCC480D440BC977ULL, 0x7665569C0BD11429ULL, 0xE11D51AF3CD1E326ULL, 
            0x1359DFA27121E203ULL, 0x8A988F1D0E2A5EA1ULL, 0x19E18E5B8FF8447AULL, 0x23CD2C45DBA93CE3ULL, 
            0x760E23A8AA47E2C2ULL, 0x8156E2D1F7F19186ULL, 0x297633AC2B2E6107ULL, 0x550FD98B27906074ULL, 
            0xECC62CBBA5BDB646ULL, 0x83008AAE7316AD0CULL, 0xA05064A26A7FD5B7ULL, 0x74711027676F297DULL, 
            0x603E62EED758D949ULL, 0x2D74C8EA19E7118EULL, 0x039F37671E08636EULL, 0x0C7E44732F5B795BULL, 
            0x5A05ECE64877F900ULL, 0x93925D92D34B9204ULL, 0xE0DF198731E250D5ULL, 0x2C8E4CC1728E8311ULL, 
            0x6676E18F5B4AA240ULL, 0x4DC4D811747EE50FULL, 0x7F0B14CA2E2256ACULL, 0x5A168A7B582172DAULL
        },
        {
            0xC68E0298A842FAD1ULL, 0x1A0AD045B4D19B3DULL, 0x03A3DBECEA1363B8ULL, 0x9D8FEEDB194E1926ULL, 
            0xE64CFA7F28FB3C57ULL, 0x0C0533C8429DD9A1ULL, 0xE5395C3E6D919FA5ULL, 0x4CB08B46AB2F60FDULL, 
            0x8867A830EE249BC6ULL, 0xC8497C7C00C581A2ULL, 0x730981CA273ECFA6ULL, 0x43E0C8B57A1D9F44ULL, 
            0x449D87514725E6DEULL, 0xA67442D096D4C613ULL, 0xAD9B8501F7C65296ULL, 0xF7C5D03D7D2A7FC3ULL, 
            0xEEA0B9102B95209DULL, 0x79A8941E6F4252DFULL, 0x385E00EE81C84C8EULL, 0x0C6CCB00A16F7C65ULL, 
            0x343BB20084F21D33ULL, 0xBF136C6C750B7994ULL, 0x450F6D1492796EBBULL, 0xC2DBCDC32A1C896FULL, 
            0xAE2FB597B76A4A46ULL, 0xF364F35C12F6A221ULL, 0x35F57647A6095120ULL, 0xD27A51220B7E740EULL, 
            0x8576301115D401C9ULL, 0xEFE2F93444806E1DULL, 0x90118B79CA7FF6BCULL, 0xE7C2DF715C8C5107ULL
        },
        {
            0x248992B90DF6626CULL, 0xA474679827F2BFF7ULL, 0xC9119F07F546DE68ULL, 0x18BA23F29333F19CULL, 
            0x8819AD231F37C6F7ULL, 0x689FDC24B01FE938ULL, 0x46FAE51F82E7C826ULL, 0x4C4D205885ED275FULL, 
            0x450E613D37CDAD85ULL, 0xE0EBD16D6D7ADCFCULL, 0x8885328DF87E9786ULL, 0x348C5CE63CD3CDCEULL, 
            0x370CE9DDDF02CA77ULL, 0xF2C7BFB901057704ULL, 0xF191FFC264E81324ULL, 0x38D2A2988E380483ULL, 
            0x5AD1D6074E4686C3ULL, 0xE42EFEA6989B5224ULL, 0xDCA452AE7F96B29AULL, 0x631A712B20C325E0ULL, 
            0xAAA795D3749E721CULL, 0x38061785A9EE19E4ULL, 0x4D84DAFFADB5ACB2ULL, 0xCE5C57121E02179BULL, 
            0xAC79D040CAD07ACBULL, 0x6A19FBD15D263C94ULL, 0x2EC823E164A2862EULL, 0xDE5E3DDCC363EC7AULL, 
            0x91F3182B9D045C86ULL, 0xD641680BA17598FFULL, 0x59B6568760D9A0A3ULL, 0x87EDBD199924DC63ULL
        },
        {
            0x24586E255B276D01ULL, 0xB1363E4D41A62966ULL, 0x57CC8316522C7596ULL, 0xAE1B390749C39410ULL, 
            0x15BB5E919DC37064ULL, 0x5CC5C7EA65D89AA7ULL, 0x29918C05917D630AULL, 0x67072F1EA58158FCULL, 
            0x3C1FB085B00BB19BULL, 0x53DCBECD828B3F48ULL, 0xB146B6BD6A26AC02ULL, 0x215A072FCEA66E42ULL, 
            0x46F5D95D35611F5DULL, 0xBEEE7FB72AEBA128ULL, 0x203F298A5BA5CC6DULL, 0xA07EECDB3E69D72BULL, 
            0xD259FDDCA02200B3ULL, 0x9210B8DC962565BEULL, 0xF4B1811EFC399607ULL, 0x6AC30F6C1181748EULL, 
            0x45486FF44CCEF613ULL, 0x215CAFF38403D4A4ULL, 0xF5B5BA897AB30BD1ULL, 0x0E147B3EE97D3F99ULL, 
            0xC0048684AA262850ULL, 0x34FDDE30E14E55BFULL, 0x1CE330256F37FF18ULL, 0x54AAA60F60751300ULL, 
            0x70829E0AAD17726EULL, 0x87AE9948D35896D8ULL, 0xFAE51A694DD35737ULL, 0xC2388F1E97A61104ULL
        },
        {
            0x09B8F2D7CD1DF647ULL, 0x3C78DC0826E5D95AULL, 0x7218DDE37179A422ULL, 0xD274CF83031C8BF9ULL, 
            0x319685BF797F15B3ULL, 0x3F89CF44406F8008ULL, 0xADA4314E6FCBB990ULL, 0x398F4ADEEA1FEF4DULL, 
            0x45488565A1E70610ULL, 0x5DB4BEFD9B5BA92EULL, 0x6477F1DEB4EF289FULL, 0x405D63D0BCC03C12ULL, 
            0x0A74B837E0A80FEDULL, 0xECFC350C0B3B13D6ULL, 0xB89678F81A7877CBULL, 0x699AA92B48DA651FULL, 
            0x134EF73EA4A8AA92ULL, 0x96B0DD9CDBB3A5C5ULL, 0x2EED20D859E11829ULL, 0x4F60DA012B288124ULL, 
            0xF9CD3BA0B8817685ULL, 0xB828D60F33CD6641ULL, 0xCB360FA793701092ULL, 0xAF2D42F5A295D4D4ULL, 
            0x4F4D522346DFC356ULL, 0x3B5A2E19B3F0CA60ULL, 0xE649CC0C720CFCE6ULL, 0xBE0D1B5CFCDADCECULL, 
            0xE4F83F7C26F976D1ULL, 0x8F65CAAC1D662450ULL, 0x4AF42A74AAC66CF4ULL, 0x3DE3962CE8AF01C0ULL
        }
    },
    {
        {
            0x7807003EE4767B49ULL, 0xC7B9029D2F377149ULL, 0x4125638A25288E60ULL, 0x890087AB405B5B8EULL, 
            0xDD92DE4A4C08CF81ULL, 0xCE29E196CB31B5E1ULL, 0x094360593D79474FULL, 0x0F66AE4C83E1CF29ULL, 
            0x4BB0AA36AA834B5DULL, 0xC623EBA33E1B570FULL, 0x0B0C95C1C0AC6148ULL, 0x2A3DF66243818CA6ULL, 
            0xEBD4C04D4147AB2CULL, 0x1A19D4FFB33AF54DULL, 0xDCD5BB72D3C32821ULL, 0x2D73D241B45D8AFBULL, 
            0xF441F8BC59A6DF47ULL, 0xA61EEA6B8FD0E615ULL, 0x99EDF2D2CAD8BD2DULL, 0x6DBEB1BFEB33AB2FULL, 
            0x69740B7C30076AAEULL, 0x56AB092516B3D269ULL, 0x3D08581E431F3804ULL, 0x32ADCA770E7DE821ULL, 
            0x268AEFEA5FA5422DULL, 0xEDD27863755B5A96ULL, 0x6DC6A5473C223E1FULL, 0x6A5267255B6EDC2BULL, 
            0xDEBAC330A584B148ULL, 0x803EA98E31F18690ULL, 0x3433DD546F9EC57EULL, 0x36B13C4FFB5BFEC5ULL
        },
        {
            0xB0FC31C3A57D357AULL, 0xE60D482430C85334ULL, 0xE40F9EAAC31C1FC9ULL, 0x8FAD07BD49F76212ULL, 
            0xE27A0AE379A3F327ULL, 0x96E0D7174F3F443CULL, 0xCE7A772EFC73C31EULL, 0xC026466A468AE8EDULL, 
            0x13D964EBD5960B43ULL, 0xBB25A70F03D11BE3ULL, 0x04C62B577EC80E6DULL, 0xC50C745D0D634BAEULL, 
            0x098E84D2E2177687ULL, 0x97103571D05EBC78ULL, 0x371EE767A35E231FULL, 0xF46CB104DF687EBCULL, 
            0xE4FBBC4DDEA25666ULL, 0x851627FB9A404F1EULL, 0xDA5790DD06DC38D5ULL, 0x8D3C33A8E01D7AF7ULL, 
            0xD617717F80103F47ULL, 0x4F3E1292554E5025ULL, 0x1A14C352891E23F9ULL, 0xA2BD75F9D7E6E2EDULL, 
            0x59ED6B11F035B80EULL, 0x2D2219335D842799ULL, 0xD7CCC20F16C413EAULL, 0x21F4CF5864983578ULL, 
            0x5078E188978A4777ULL, 0xB324E0406379F4A4ULL, 0xE7AA70AA7C76E307ULL, 0x5DB750CC9A42E324ULL
        },
        {
            0x3B8C635EE1B93BAAULL, 0x5EE8F359461E9825ULL, 0x23CCA98CDE4E2419ULL, 0x5668A203843840D3ULL, 
            0xC3749E9C3FB992D8ULL, 0xC808E31C8638969AULL, 0xE7A745822FEDFFB1ULL, 0xA75E3F31864903A7ULL, 
            0xB80791CE8ABE2386ULL, 0xFB04D7DB2DE4B995ULL, 0xD2A1FF5B30E23132ULL, 0x5ECE22660AB2E990ULL, 
            0xAA405747C07E1EE3ULL, 0xAFB5707CAD280A61ULL, 0x3CA28416AE06ABDBULL, 0xCDA3F195A564F44FULL, 
            0xAB7F4E4A38F08F6AULL, 0xE6C90D0600F56803ULL, 0xB723A3CFC800DDB7ULL, 0x324E4696E7317A95ULL, 
            0x4A824C5AFECF953AULL, 0x4C8B20C407AF87D8ULL, 0x51CBD1439511B5F5ULL, 0x209D67FC1D2066B6ULL, 
            0xF621642B78DBFF3CULL, 0x7AB504FDAB132785ULL, 0xE017894D247B41AAULL, 0x5B2C120C8A82D5B1ULL, 
            0x9B1D9A2020D142F6ULL, 0xB93F74A7BC994C8EULL, 0x85B7B7880119AC0CULL, 0x7E9C19B2F27397FAULL
        },
        {
            0x191BEE5A82D825D7ULL, 0x8317103AA264E63BULL, 0x1CA22C4B785DBA4DULL, 0x9B01A6F8EF50BF33ULL, 
            0x94C98B8EA8E199D1ULL, 0x253E8D71AA885167ULL, 0xA5A342BBF90D66DBULL, 0xE862AB907A9951AAULL, 
            0xAE40AB1568C777C2ULL, 0x021B688B20E72F8DULL, 0xCD7E9193D28316F9ULL, 0xFB892A35EF81C9A3ULL, 
            0x97AA18D58EFB7948ULL, 0x0899FEEE31BD6C6AULL, 0x91DDFAD42E1970D0ULL, 0xA439F9ABDFF6EACAULL, 
            0xEFBBB5169D642DA9ULL, 0xB82BD0120E3452B0ULL, 0x50775F92F6893F7DULL, 0xA73E281DD2186E1BULL, 
            0x6C9AE0D389FBCB50ULL, 0x7EB050DF935415DBULL, 0x1E78110CC8260971ULL, 0xF4F9E104F06B26F1ULL, 
            0x97235C4E8782F17FULL, 0x1F790A847D810495ULL, 0x1B5619D691954EE3ULL, 0xA01EEFE52F9EC1C1ULL, 
            0x33E41CFDA8BEBD07ULL, 0x5490B22BF0AFF941ULL, 0xF74748C215FFCE19ULL, 0x10C736F78EFDC6CDULL
        },
        {
            0x7E8A13E6F34111F5ULL, 0x13BBE82D36C235C6ULL, 0x46A13E1F72A21ADEULL, 0xD6E86FCA4E144DCDULL, 
            0x856690E8310F12D5ULL, 0x41FBF3D4ADB8EBCFULL, 0x34883729D4B62814ULL, 0x8CA755B73B1F5BFCULL, 
            0x47149791491610C7ULL, 0x5664063DD452EA47ULL, 0x96B2B108A74D6C20ULL, 0x01B8BA9ACF4734F7ULL, 
            0x47FCACF0F0A9AE64ULL, 0xF67863497FAA194EULL, 0x2035CDFEAC3A21F4ULL, 0x1CB61E514FAC9FE3ULL, 
            0x81599C5873DE3B2AULL, 0x61C6FAD40524BBB5ULL, 0xA8EFFA1016FB6BB4ULL, 0x4E46D3047029695EULL, 
            0x7370A7E47BC64DE8ULL, 0x671765577E2106A6ULL, 0x083C8A193C7FE1F2ULL, 0x1D3ED7DD485F2876ULL, 
            0xF1EA9DB4A22371EDULL, 0xF6FE06833469EEBBULL, 0x09DBC94918388E34ULL, 0x46EC2BE5E4A6B6F3ULL, 
            0x7E69935A0A06882EULL, 0x7B6CD8B0A0C18BFCULL, 0x7570F69CF55E5E13ULL, 0xC669AB01CFC6E0B7ULL
        },
        {
            0xD31F704ECE39419EULL, 0xD1D7B4045E6ADB19ULL, 0x5A1625E0C1511E71ULL, 0xD621D3E43E677A22ULL, 
            0x762DF9B8A62EBCB8ULL, 0x15CC07082A0C11E9ULL, 0xEC6B9216079B21CEULL, 0x5CB73461FE39929CULL, 
            0xE196ECDB15FA765AULL, 0x96C0496049980541ULL, 0x13B6E7020A8E8F96ULL, 0xCCF33956B691CB75ULL, 
            0x65B71759D86D2149ULL, 0x24C70B86BC762E0DULL, 0x9834374B51868D13ULL, 0x5F64B370BE8F9A95ULL, 
            0x238AA5A2971D1D76ULL, 0xE73E8601D1502629ULL, 0xE619E3CB39DBC10FULL, 0x49FAAAC84713143DULL, 
            0x8DCC838E6233067DULL, 0xCD61924CB4635EE9ULL, 0x412161AC12AAC2F7ULL, 0xAAABEFE8DDDC4EC7ULL, 
            0x901102A8E170B4E0ULL, 0x5AC068E8E2043093ULL, 0x7A594D6D9E27FC91ULL, 0x7A0BCEFCFA991BDBULL, 
            0xF8176FD08A2DF110ULL, 0x006EAE4DDA0E648AULL, 0x30FFBA6A7BE29685ULL, 0x118D8F5CF15AB30FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseBConstants = {
    0x29EA13163B86DFE0ULL,
    0x892A5250EB8F36EBULL,
    0x59D78A2C4D7DD8F0ULL,
    0x29EA13163B86DFE0ULL,
    0x892A5250EB8F36EBULL,
    0x59D78A2C4D7DD8F0ULL,
    0xD9626A19CCD40482ULL,
    0x3AAC0944274B1986ULL,
    0x91,
    0x71,
    0x40,
    0x56,
    0x99,
    0x91,
    0x44,
    0x12
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseCSalts = {
    {
        {
            0x3878AF2AA2E2D0B0ULL, 0x448F0882E94CFF1EULL, 0xE029C0C70CB37CA9ULL, 0x494FA5D2A589BA29ULL, 
            0xBB19D9C81911AACCULL, 0x8D17C729AE9DFDE8ULL, 0xB83405FCEE37CACDULL, 0xEFE159851D60FF95ULL, 
            0x03B85040345947F1ULL, 0xB81EE1146130630EULL, 0xDCEC49D6C13EEAC4ULL, 0x43CEB9863384462AULL, 
            0x49A62946A1B9869DULL, 0xD744378DA1019A2EULL, 0xC065DE206DB6C702ULL, 0x689791214C5A13E4ULL, 
            0xBAF538773EC4B97CULL, 0xD6722B0C1F2D7DB5ULL, 0x3CF882741E0C39ADULL, 0xE2C928148AA6AC86ULL, 
            0x2C1A920C17C50DEEULL, 0xD060B460F84F78D7ULL, 0x09115401E0444A8AULL, 0xB9A1B815FEE30038ULL, 
            0x8B2CA34F11BAA2EDULL, 0xC87BFE4D3CE7517CULL, 0xBDC5692B6D95E18FULL, 0x729E71963DB051C8ULL, 
            0xBDABC2E127C7B1F2ULL, 0xDE6CA224CB02E069ULL, 0xFC7C599EED30D083ULL, 0x84E5F98DECFE2357ULL
        },
        {
            0x22E1FAA0805A14A2ULL, 0xBBD69A9D08D89CF6ULL, 0xF90914777EBA48A1ULL, 0xA94B4B6051770731ULL, 
            0x1ADD7222399D1CFFULL, 0xBA8355A455954516ULL, 0x4A8F77AED8496DFFULL, 0x859349548B56EDCCULL, 
            0xE43E8440ED014704ULL, 0x59E0EDC240F9F8B5ULL, 0x1A941E12E115CD49ULL, 0xAF077DA002D0140FULL, 
            0x2239AEB29DF8940EULL, 0x0599C5BA5A54F8F4ULL, 0x51EF3C265592675AULL, 0xCCBF1C8C730229ACULL, 
            0x35C9B19ADDACD037ULL, 0x87CA095736A8896FULL, 0x94FB3421979B100EULL, 0x98CE0B5A3C32C2DBULL, 
            0xE2BC2D579F9A0D42ULL, 0xCD97B68BE8A94B33ULL, 0x7913DD30B5F27D5EULL, 0x669B847DCD4F6FA1ULL, 
            0x3511CCA25DF375C5ULL, 0x51A81DA8664778F6ULL, 0x5649116864BF3710ULL, 0x688567DFDB097424ULL, 
            0x22600F94237B6FE5ULL, 0x7D1573A4E6E3311DULL, 0x796A8F3D657B018CULL, 0xA5E7433F7C2B129BULL
        },
        {
            0xEB0FCD0D5D103C11ULL, 0x49E0D95C20A899ADULL, 0x096B0255BE856A56ULL, 0xF939A8FD7803D70AULL, 
            0x18EDA77E39B35079ULL, 0xEFD5C71E1FEAF3F2ULL, 0x3BA3B1F8DF2E5176ULL, 0x761B316992EB11DCULL, 
            0x21CDCE879A55CF60ULL, 0x32354250E4EDF1E2ULL, 0x644BE4A05BC61919ULL, 0x0CDAA721EBE07B05ULL, 
            0xA6A052293E8B7F09ULL, 0x2E41E60362AACA20ULL, 0x76C2F703BD454680ULL, 0x9AB7F42225CD9655ULL, 
            0xBC36350EE098F3AFULL, 0xA3B729C0BDBABAA5ULL, 0xA69BDCA25D35C470ULL, 0x20C719A55BF69F7EULL, 
            0x551FDB6CDC7CC542ULL, 0x964C669F6B4B9B09ULL, 0x961A2320320A6569ULL, 0xFE2B55DF1A0136AAULL, 
            0x870782F808D0AF2AULL, 0x302E8AC62E7E1960ULL, 0xC4AB08F7E3E42090ULL, 0x7EC5EB0A16AFA06EULL, 
            0x91FF244D999A083FULL, 0xAE93ECF440A3FAE1ULL, 0xC15FBB72A9619301ULL, 0x05A99E00DD79B1E9ULL
        },
        {
            0x0F94DC6B29AD3D52ULL, 0xFAF45118130968BDULL, 0x347E0BB1E077C14DULL, 0x5E022D9A5B8ED47FULL, 
            0x3679E081C46F33D0ULL, 0x4F26E1CB4FEF6A35ULL, 0x02EDA7CFA4D3CDBBULL, 0x1735774430B6C83EULL, 
            0xB6B587D8CA528A41ULL, 0x5AFFBA4B5F4935EEULL, 0x6E5E4749990783F3ULL, 0x7E805D1FD2ED7D3EULL, 
            0xE2088DEDDCE75AD2ULL, 0x71B2BCDE42A7477EULL, 0xBC4198E0AFFD68F6ULL, 0x11ECA69A01BCE088ULL, 
            0xBB27DC66FA0E780EULL, 0xF7CA642877EE14FBULL, 0xCE0AEACE3EA1ED94ULL, 0x37463B60D52E0EB9ULL, 
            0x05950961F4436B36ULL, 0xD6A44FAEE64B96F1ULL, 0x60AE3D1C71837443ULL, 0xB40717196B68FAD5ULL, 
            0x06C79ABB0A9003FEULL, 0x46D04801662E5CB8ULL, 0xC764357673FE68B2ULL, 0x4959A225AAD688FEULL, 
            0x8B4DC72DB9F8B815ULL, 0xFF373C44A52DE635ULL, 0xE12F3F1F102B0D61ULL, 0xC4BCE21F351638E3ULL
        },
        {
            0x15CC4BE020F9A9E1ULL, 0xA4875D5D3BB59CB8ULL, 0x99C06A8C1E6CBDCBULL, 0xFAA57CECC8261039ULL, 
            0xD7F047BEF2821F48ULL, 0x4FB7BBE562420D7FULL, 0x2761C1DD8519E4D8ULL, 0x3C5FE0AA30F83913ULL, 
            0x01F586CB26D97887ULL, 0x1EAF4A51C182A73EULL, 0xA5C16CF344127144ULL, 0x5B263D2D09BB8CEBULL, 
            0x6FE573C63B76FA80ULL, 0xFE9632CA30221873ULL, 0xDC73293C785F53C3ULL, 0x1C359C3EE67462B7ULL, 
            0x12BCAAFA2EBB1CCEULL, 0x654C8C88095D94E7ULL, 0x3B1736D5FC29E59DULL, 0x0DC8DEA72B4FE34FULL, 
            0xD72F5A5ED5A57301ULL, 0x06D8D2F0D1EE6A16ULL, 0x455F4C090AC37BDEULL, 0x064E97FA0E570E47ULL, 
            0x8885B69896C88E68ULL, 0xBFEA974A4689D049ULL, 0xD26AEBC1D47B8316ULL, 0x3571819D1C83815FULL, 
            0xD2906D5D021AAF7AULL, 0x829E35B674C71EB5ULL, 0x0D9B0E5739FB85B1ULL, 0x2823E65DD77A5003ULL
        },
        {
            0xAA346051BDDDE22CULL, 0xDFE1BE9968EA7E09ULL, 0x6B0EF2B8C71D5F93ULL, 0x62E985D921BEBEDCULL, 
            0x9E3BA544E62FA05AULL, 0xD55C086C035E2269ULL, 0x4E82B28F14E559F1ULL, 0x99F6C45723093BBAULL, 
            0xE4058CB2E4ADB1F0ULL, 0x9F6274EBD48B1FB2ULL, 0x27B2847A038C0313ULL, 0x797D2FAC9FC4100EULL, 
            0x7A05982D3AB087DAULL, 0x199EB2D4408084BDULL, 0x87B28705BBE2A8B0ULL, 0xD71BE12B72D5FAC9ULL, 
            0x1E088F2B6315348FULL, 0x92D64FA8FF0081EBULL, 0xB4758DDEF4682CCBULL, 0x16C8BA46C88AAAF6ULL, 
            0xE97280B2D50F1B4DULL, 0x90711F905FECB4DCULL, 0x4FD3FB506EE80936ULL, 0x3EB081E0148203E1ULL, 
            0x1A4D6E0292D614DEULL, 0xC2794B223F77B27FULL, 0x64123B4CFC9A40EBULL, 0x8722BFECC8896CE9ULL, 
            0xF20C8E429B675DAAULL, 0xA5B8547B71AF412FULL, 0x01A7C64D768A2E28ULL, 0xA46E018F3EDE033BULL
        }
    },
    {
        {
            0x0BBE32107CCEBF17ULL, 0xEEE92AEEE554306BULL, 0x616A8575B0AD5330ULL, 0xAAE86E9D3D8907D3ULL, 
            0x25B5B4D9B7AD620BULL, 0x5145CEF7826D98E2ULL, 0xE3A7BB3196F9A380ULL, 0x1C2C15D10C5F13A9ULL, 
            0x34884DC13DE99344ULL, 0x731AA5402C500CDAULL, 0xA1F00010391D2AC7ULL, 0xB044545F46DE4219ULL, 
            0xC7AA79F4DCAAAEC0ULL, 0xD2D7A967A44F6CBBULL, 0xEC6EFE1DE6AC33CEULL, 0x426D5BD9D1EBC3DCULL, 
            0x037971BD83E08F53ULL, 0x8F9F1FEF20739977ULL, 0x39085C366D3DD11AULL, 0xBE6720DDA55FC354ULL, 
            0x413F78AC08A41F80ULL, 0x22D1EEE3F1DD7B15ULL, 0x9C56D7B537212894ULL, 0x92D9923554368A95ULL, 
            0x0B23563B3658983FULL, 0xEB46877756CDB260ULL, 0x6047B994F41CA354ULL, 0x51F1B5A8CBBFA046ULL, 
            0xF814F763007BE5EEULL, 0xEFC6A4002EB10DABULL, 0x22CF58AB6B6B5FEEULL, 0xA0A6245FCEF67127ULL
        },
        {
            0x0B03A0F6617E86A8ULL, 0x9800C7A77424D6FEULL, 0x4D753483E94D4AFEULL, 0xF0CD4D11B5F38348ULL, 
            0xFD8C4F13F010DC33ULL, 0xBE2DC3EEA3E731A0ULL, 0x885814F59BD5039FULL, 0x98E928EE0518BD7EULL, 
            0x07C4B327C75ED302ULL, 0x01621383384CE874ULL, 0xAC465880680ED5A9ULL, 0xF7DB4E7A7D45391EULL, 
            0xC6818082EA322C1EULL, 0x62238080D4637BDCULL, 0x947E18036EE9218EULL, 0xCB24ABC18E074361ULL, 
            0x23E799015EF09D91ULL, 0xEBCE14964D3104EFULL, 0xF9034D58F46A6DA8ULL, 0x103FF5EA53ABD875ULL, 
            0x3FC46996E17C1126ULL, 0x382E11A1A596A605ULL, 0x320DD4562542DB27ULL, 0x5CFCFC3EB7CA39C7ULL, 
            0xB5F15C9B8F04D6C2ULL, 0x0A16351B585C35C1ULL, 0x1207FE7174238866ULL, 0x1859EB4EFA7C0AFFULL, 
            0xEAE47B0F97A93B65ULL, 0x7A077F3BCBE3D2B6ULL, 0x873C9BDD29382C49ULL, 0xBC99E21B2979C262ULL
        },
        {
            0xAECD85E0E2A150B5ULL, 0x1A63CBF596D72803ULL, 0xAA8C8B62F10F2678ULL, 0xE5FDBD0C2320DF6DULL, 
            0x2548EBC59702541DULL, 0x38D9960EABDA1E80ULL, 0x0EE23747B879BBF6ULL, 0x834A3068B67AF298ULL, 
            0x333BADB3FD09DB7EULL, 0x8161B2AF28C8F7EEULL, 0xE761369CA7C81737ULL, 0x95B880834FBEDE78ULL, 
            0x1372693DC156C9A9ULL, 0xDA908EE73779280CULL, 0xFD8061A80FFD96F6ULL, 0x7B2A636AEE83943EULL, 
            0x47EBCDA92EE28E78ULL, 0xD8C8AB4374475F14ULL, 0x4A908AC3AF2332C6ULL, 0x9F90B65A33794D30ULL, 
            0xBF45A4CC55A24A41ULL, 0xE026DAFF8C980DD9ULL, 0x3917F45A4BC86E25ULL, 0xD125D3C9091C6697ULL, 
            0x1F001F8E5FA4076EULL, 0xFA69E332C48A21F8ULL, 0x5BEE66DA393C13E1ULL, 0x7F77865D2BE5396CULL, 
            0x34BAAEAEECB7F9A4ULL, 0x46E14633E101D71EULL, 0x8C449199469E170AULL, 0xAC6D840E21831635ULL
        },
        {
            0x67201BEEA1331DA5ULL, 0xFC5320796C3D5896ULL, 0x8BA8AE6C2B0F4759ULL, 0x430FAFB1DCE2B5FEULL, 
            0x0E2BCFFDE8D51DD9ULL, 0x00F3773AC3145715ULL, 0x58B03EC8A9F4BAF1ULL, 0x5BE20E29455F7473ULL, 
            0x715FED60AB3AE749ULL, 0xEC408269DD680362ULL, 0x73CE0A45B6B825C3ULL, 0x1835509AB140AC56ULL, 
            0x18A27E12AF61C892ULL, 0xD2C4ACBEDAD5B8CDULL, 0x3AADEF9303DA890BULL, 0xA62895ACC7E85821ULL, 
            0xF9636BE1A78DE7F8ULL, 0xEACE13358BA35853ULL, 0x9735AFBB1E1F16B5ULL, 0x191E9C2A0E180E64ULL, 
            0x96507623D4E01E8BULL, 0xAEB4CE11174719B1ULL, 0xD0D8F42F66FEE945ULL, 0x4A322B641174191BULL, 
            0xE6DB7D647066545BULL, 0x5B0DFAE0FC1C812BULL, 0xF9AC27B277301021ULL, 0xFA76F48460761B41ULL, 
            0x8F2241138D7D14CAULL, 0x4E33AAC215227D1AULL, 0x03128A12B30AEA4BULL, 0x57DCC2C99B423F47ULL
        },
        {
            0x9EECA6539989DD5DULL, 0xF698962C049C5622ULL, 0xE7E1DAB95E80C67AULL, 0x8314EC2470B189F2ULL, 
            0x46CAB2032B68E39EULL, 0x33B8B8C602E2872EULL, 0x1013EA86A9ACC8EDULL, 0x539BE57C4595B18AULL, 
            0x3C045687CBAD4E2BULL, 0xBA5C1D8ABC67955BULL, 0x950196A5C8DBF29CULL, 0xDE3F65FB9D29E29FULL, 
            0xB161B9C408CD3C1DULL, 0x3AD7D64ED5E04949ULL, 0x29C9DE61A41372BAULL, 0x40FBFE86BFEE938AULL, 
            0xA6F0D88278BF871CULL, 0xABD726684F5F911BULL, 0xC53D84AE2C3ADE62ULL, 0x274A72F235D8FC51ULL, 
            0x1B1BE1678FE52A8FULL, 0xF65A2AA139F78DECULL, 0x5EAD40FBB336C63AULL, 0x534016021C3E3CFBULL, 
            0x239016B014F9A4F9ULL, 0x21FB9BD94F93F7D1ULL, 0xEF3532DF9A7AC3D2ULL, 0x5B474B04957FCF1EULL, 
            0xFE5F6651D1E4064BULL, 0x331BB0F9888D4E22ULL, 0x3B9C4946707B8970ULL, 0xBF6E03781521D24DULL
        },
        {
            0xC9A24EA926B5ADD8ULL, 0x4E38405046B07BC2ULL, 0xBC7B0772D0E7F7CEULL, 0x43EC629DDF2CE962ULL, 
            0x709C19EBC736F906ULL, 0x6DB112837AB5B8EFULL, 0xACC893E401ECDD81ULL, 0x66E5ECA6D44232CDULL, 
            0x746CF55D411D625FULL, 0xC7EBB7E3D5820DA0ULL, 0xA3520F6C6A9FD262ULL, 0x9AC965E94249E569ULL, 
            0x0A16EA89C5B10E0EULL, 0xAAAD118BA193734EULL, 0x7544B18B73C3EC52ULL, 0xB697965C77F84AADULL, 
            0x8FA1067E36D4EDE4ULL, 0xF8A33875560A8A96ULL, 0x1D00E2042D08B587ULL, 0x74EFE001DEF4C5F6ULL, 
            0x216DF8F50A744FE0ULL, 0xBFDE98C5E9DEAEFAULL, 0xC11E19AE8400E505ULL, 0x70896F08A0CADD16ULL, 
            0x401751A15F132802ULL, 0x449EF643F02207EDULL, 0x213F6160A73F5BB2ULL, 0x4A8A8474285F7C7CULL, 
            0x5902641D8C8CBDA8ULL, 0xCABDB1564216EF43ULL, 0x5A0F018D7BD5B2E6ULL, 0x162753AAD15C720EULL
        }
    },
    {
        {
            0x57452AB02AC8E3BEULL, 0xAD9B4AD3511D940EULL, 0x679D8E92C437E191ULL, 0x8F99CE07B3C0C836ULL, 
            0x3D9E53AB771A8D27ULL, 0x0390C06E153C4092ULL, 0xDA279B95FCF93585ULL, 0x5C8D9B8AC38B70DFULL, 
            0x14E34CC09D877D9DULL, 0x141D0BAD7E3F4553ULL, 0xB00EB6F158C7DBBFULL, 0xB0997CFAFC893DB7ULL, 
            0xECAA52F5BB5AE77AULL, 0x95AE33DFE18C401BULL, 0x02F19774E846A9FBULL, 0x5C1A0173892AAEB3ULL, 
            0xB51BF41AD94B7EE7ULL, 0xD1522F0E887D5C31ULL, 0x92DE43A1AD9C7CA6ULL, 0xB5BB1F3BA431E75EULL, 
            0xBCDCB9FFFA6B3F12ULL, 0xAFE9DDEC13DA2835ULL, 0x2263ADF226762BA8ULL, 0x36B1DB7A376D42FCULL, 
            0xD30A9EB73A5E353DULL, 0x2ED6A0BFA949E4C8ULL, 0xBB67038DDCE67473ULL, 0xA81CE715B0467E8FULL, 
            0x32FBD52901E6EA95ULL, 0xEB2046F2D2B4F142ULL, 0xF56C8E1D90DDFF4AULL, 0xFCED7A98ABE90646ULL
        },
        {
            0x4AFF76FAF91AE452ULL, 0x98A3A1B90F116BFFULL, 0x3453D4A2399B9484ULL, 0x393B62B54476843AULL, 
            0x02ADE1F7608A6C96ULL, 0xD091AA2E4D2F70E2ULL, 0x05B816E068986B82ULL, 0xDCD09EF6A0B3666BULL, 
            0xEAFF77864CF6040BULL, 0xB7DAEF170E3CF4C6ULL, 0x8B5481D11CA3D97AULL, 0x9504E7CDE5B7546BULL, 
            0x905DC2F9753D28ABULL, 0xF9721798EF029B55ULL, 0x3D1BF41AC9A7CB19ULL, 0xED417B3A67446583ULL, 
            0x6925BC8DC0A4F02CULL, 0x2A15029DE938BE05ULL, 0xF4D6089FC12D7EE3ULL, 0x733C0E5BF66CFDBEULL, 
            0xFAD7758E727F3C7CULL, 0x2C337A45662059A3ULL, 0xA8866A9CA7F92B5BULL, 0x4E5987210CCD7A4AULL, 
            0x624DC0FBE1885101ULL, 0xF6D84A153DD6AFBBULL, 0x5B3434720A971DE5ULL, 0x8E311F01A14B434EULL, 
            0xA1DA81B41A6A6E8AULL, 0x95549A15B707FF26ULL, 0x9E639ACB98485AB3ULL, 0x0AB463DA2D7365D8ULL
        },
        {
            0x6AADE7B49AA57992ULL, 0x2A38EC94B3CE15D2ULL, 0x39120F43E9B36E1AULL, 0x4A01963DD13F7D83ULL, 
            0x99F967A41FC9F954ULL, 0x19C69E493EA70D6FULL, 0x179AA783C36FB822ULL, 0xEB663AA8E92D8F28ULL, 
            0xFD84D16AF8F8A6C3ULL, 0x145E856EB049C7ADULL, 0x550E2170B3547123ULL, 0x469A5F5509C8101AULL, 
            0xD1A7421539B39F73ULL, 0xA6C8DD9394034524ULL, 0x64F37D800109810FULL, 0xB0CA4828B04DCD18ULL, 
            0xB08918B254C3F6B5ULL, 0x17B225B0EB975356ULL, 0xCD10AFF78EAB664CULL, 0xF321B1E6CE709E33ULL, 
            0xAE5002238FE6B2E2ULL, 0x9C0998D3C4EF319DULL, 0x41E0663A81ABD196ULL, 0x5737201D8175CF28ULL, 
            0x6AFE63C567C43486ULL, 0x7D077B9A0E306728ULL, 0x192CEF20180349DCULL, 0x6E30C34224CD5B6BULL, 
            0x33F6BAEED9379531ULL, 0x10704EDAA4D868C5ULL, 0xED2A6F6BDE8D0FF1ULL, 0x19228F03A418C058ULL
        },
        {
            0x4B870A7B529E00C8ULL, 0xCE1520520F0DD057ULL, 0x5913D54E050B7892ULL, 0xC99F10DA2D1FC99EULL, 
            0x05E7142A1E552821ULL, 0xAAAE3AC9DC5CD917ULL, 0xEEAE8CEE90BD8791ULL, 0x0DE4F71290AAD928ULL, 
            0x9398730044C27F46ULL, 0xBEB5057735EA6BFBULL, 0xE23B2FF235940320ULL, 0x86865C77AD69C856ULL, 
            0x1175D2B53549C67BULL, 0xF3C61A9F7D719448ULL, 0x7C42E2E1DE772BF4ULL, 0x1368786D43C60A51ULL, 
            0xCDDBECC0E73575A8ULL, 0x7D02CE40F228D24BULL, 0x28EFE288497C5A8AULL, 0xD555342F09871D86ULL, 
            0x82F0E98498DBB9C5ULL, 0x0CE44124378E498AULL, 0xB0DEEC60613ADCF2ULL, 0xA3D0BA2171DC0D7FULL, 
            0x86109FA67666D835ULL, 0x481B3F65C7638B8FULL, 0x0F62A166963A789FULL, 0xE1EF7C1A5E1A2064ULL, 
            0x5412BE860E606A8FULL, 0xB66AABEDEB03F399ULL, 0x868F5A82AD3A5CC7ULL, 0xA5BAA2F7D8B52687ULL
        },
        {
            0x25D89393B62FB1C0ULL, 0x32398D714EF8A463ULL, 0x8ABFCB0B7AC302C4ULL, 0xC84F1C35A9455315ULL, 
            0x17BFA8ACE50BF3EFULL, 0xA0A77A96D2AEAAD0ULL, 0xA46A178D26B8A233ULL, 0x82CF1BEFC91855D2ULL, 
            0x27CEF8A4C1DA6968ULL, 0x6467CA5068FD6EDCULL, 0x0BF019D07026F5A4ULL, 0xC0FE340C0093F05DULL, 
            0xDF024E84314D3746ULL, 0xF6A4BE5E57AB644CULL, 0xD080DE6DA935CBD1ULL, 0xF89C45422CC7D059ULL, 
            0x8426E57D738883AFULL, 0xA72E8AA4CA12B3E5ULL, 0x625267BFD35A578EULL, 0x1A0533A16D079423ULL, 
            0xDBC32DA071A0EE06ULL, 0x61D1F5AADF33D50EULL, 0x0828765AFCABA808ULL, 0xA70AC728B2A26CEDULL, 
            0x3AA4EA2E571AA429ULL, 0x2FFF77607B9129D5ULL, 0x97A8CFAE760A7B5CULL, 0x5521C125851D251EULL, 
            0x7DD655896573E060ULL, 0x931C13EF8D64E1A0ULL, 0x87BFCC429BA6CD27ULL, 0x570B2443831A32ECULL
        },
        {
            0xF8372C52F5273119ULL, 0xA5E6A3B6618C7272ULL, 0x1C391300B72C2658ULL, 0x464CABCCF456EF75ULL, 
            0x3FB8EE8DD50213FBULL, 0x6A2CC0A0224E0D24ULL, 0xE4702B55A172889EULL, 0x28035BAF99CDFFCCULL, 
            0x8B57EF11E6D2FB20ULL, 0x82107E1F065FD12CULL, 0x98C6D46E7CB1A984ULL, 0x6A045A90CFFBC795ULL, 
            0xBFE2B1F7666A70A5ULL, 0x60C103B99B38856AULL, 0x443B1CBC90DB34C2ULL, 0xCF06D68588F04ACEULL, 
            0xA4B1C8C865539414ULL, 0x38A7D329A0F620A6ULL, 0x142EAFFC4627A86EULL, 0x2D65D14E45A1B4A0ULL, 
            0xAD5FFF78BA83424CULL, 0x103C3FA9BE18F61CULL, 0x378E3F9CE37A6029ULL, 0xC12AAC9C278F6092ULL, 
            0x1FA847E51B357651ULL, 0xE9C05E3EF6DC4281ULL, 0x3F91D416386088C6ULL, 0x5BFC4DA7A8CC41DFULL, 
            0x1BC8C837FA114362ULL, 0x5053712D6036C4EEULL, 0x8B6EDC7C58E94427ULL, 0x840138BDEA30D7C4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseCConstants = {
    0xCEAAD0EC98C623C2ULL,
    0x223D6E1D27DA85C2ULL,
    0x1B974B66B03148C1ULL,
    0xCEAAD0EC98C623C2ULL,
    0x223D6E1D27DA85C2ULL,
    0x1B974B66B03148C1ULL,
    0xFFE0CA2CF7664FB7ULL,
    0xCB767434AE4ED595ULL,
    0xF3,
    0xB1,
    0x77,
    0x23,
    0x9C,
    0x0F,
    0x6D,
    0x32
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseDSalts = {
    {
        {
            0x116FD68F6DED7184ULL, 0x08DE0D5C7A490CE3ULL, 0x3D0D74FA6D69A11EULL, 0xD58338730EAC18DFULL, 
            0x4DC8C19CEF71F2A1ULL, 0x34E8BC868E035166ULL, 0xB89DB6820091EB94ULL, 0x2DB0DF629021551BULL, 
            0x926BD8B04EB75DD1ULL, 0x2319A24DD8A1D2FBULL, 0x0E8CA0EA69EDFA0BULL, 0x70F527EE75C35F72ULL, 
            0x034F2DAC7D6569CDULL, 0x2C87BA37C39FA7F7ULL, 0x321C2AA3261488D3ULL, 0x44C2621FA5FC2726ULL, 
            0x45E8764D118EE1C7ULL, 0x3C1CFF9F3075139AULL, 0x143A8D7A42C68A02ULL, 0x07515F4C94990CDBULL, 
            0x3770B99379477FE1ULL, 0x408AE0DBBFD41D74ULL, 0x27B20583414666C3ULL, 0xAF0518FC973B515AULL, 
            0x0C878A4D3D342724ULL, 0x7740A846769BAB18ULL, 0x410CC1A516B1219CULL, 0x2E366A28B33D232EULL, 
            0xF25DCDD307EB39C0ULL, 0x4D1B24F98CF81CCCULL, 0x2B12EE719FAA56B5ULL, 0x8A0B8901C6B1F9EFULL
        },
        {
            0xEBEB23A244517E9FULL, 0x0FDA977A0CF0D424ULL, 0xB2A8E90E2505AC0DULL, 0x6A74953B4AF5B235ULL, 
            0x88CF36E6FCD57E47ULL, 0x3A0FB2F0B7F85B68ULL, 0x0F0C6986486011D4ULL, 0x5138E2C30977E08FULL, 
            0xE69EB6B91D73044CULL, 0xFDE36BAB0BDB3802ULL, 0x344C0FBC579604D8ULL, 0xD8FDD628DAA17F76ULL, 
            0x9DA05114E3B5562FULL, 0x4D87FEF0588F81E5ULL, 0x0B997E0EF2575626ULL, 0x034D86C1F2E7F037ULL, 
            0x3B34D1D9659CF3F7ULL, 0xFB8F0F028BC3A462ULL, 0x0FA4876C4F11A8E3ULL, 0x39808934B66CC48AULL, 
            0x9A3D4B1FA18D7C87ULL, 0x388B8D34E657E5B2ULL, 0x93D9A93EF6C6ADEAULL, 0x87C34C5F125495F1ULL, 
            0x23BB14AE52ADAE54ULL, 0xDF4A983C2677DA12ULL, 0x5A16734336FFA13DULL, 0x5D56E41F492BFD7EULL, 
            0x19ED200336BC58BAULL, 0x8621FCA865000C58ULL, 0xE31C8AF011083FC0ULL, 0x5D6FCEA6A84823A9ULL
        },
        {
            0x58466F722C91E918ULL, 0xE74517C5619F67C6ULL, 0x8CBF29C337A2F07CULL, 0xCD39430B1AD52927ULL, 
            0xFDF766A796319FFCULL, 0xD0B5EB03D24778ABULL, 0x753F762046EF4C49ULL, 0x302153A0B029C77DULL, 
            0xED7D0B1AA46EC53CULL, 0x739F98BF49E5CE38ULL, 0x0BB0489D054CD77AULL, 0x2E5F607FF91C3507ULL, 
            0x8F3ED8D19A1213A5ULL, 0xB94EA81146F4B263ULL, 0xB97D8E907EE20CE0ULL, 0x6412A9020840F024ULL, 
            0x656F9E95285B2760ULL, 0x118902E2AB492E11ULL, 0x124E352680817757ULL, 0xEC51446207D98830ULL, 
            0xC651E484C49AFB4EULL, 0xEA038A7BD2BCF2BAULL, 0xEA13246B2E326392ULL, 0x8EBD4B534768E94CULL, 
            0x19793692E0957C6BULL, 0x98CA95AC751BB7B4ULL, 0xECD4C827515CD15FULL, 0x4D485617E12EF396ULL, 
            0xE07F294CC8D319BDULL, 0x62BA0F6617962981ULL, 0xEC10949A65DD94F1ULL, 0xD4F568EE848243EEULL
        },
        {
            0xAF3C893BD484C2FCULL, 0x2C44D279111863D2ULL, 0x4FF1C7D41118FE80ULL, 0x0742438799D9B3F0ULL, 
            0x09583174A4F0AAEEULL, 0x14EB3E2DE4AEDFDEULL, 0x9A86390EBD96D1CBULL, 0x3FC4477ADA1D9C81ULL, 
            0x95C541559DCACDE8ULL, 0x4C9F7608A17E3849ULL, 0xAC5398120A6F9390ULL, 0x17230AC708A4F645ULL, 
            0x4AD5C717291320FCULL, 0x9BB206026A5060DFULL, 0xB33A58957E85C5F4ULL, 0xF6444CE6D1765263ULL, 
            0xBEB6FC360CA7DE2EULL, 0x8A63B82BF9415C1DULL, 0x65643C38D38D94E3ULL, 0x3B5F270F5E08FBAFULL, 
            0x0F87990EEABB4877ULL, 0xFA8D99449B13E1EBULL, 0x7938E796F71B6205ULL, 0xE11081C4598CD3A2ULL, 
            0x14F4D47A3EB32534ULL, 0x14EC4008F7502637ULL, 0x4143C769EAD597CAULL, 0x9C6EE568D11DE717ULL, 
            0xBDAFEA803F33AE8EULL, 0x73FB32236204674CULL, 0x646D03FC613EC1D9ULL, 0xC2F8C08E30F68980ULL
        },
        {
            0x0BB3C8774A545724ULL, 0xCAED037754D69375ULL, 0x89EFFE0488B9A171ULL, 0x5A8BF6F7778F075DULL, 
            0xF3FB2F2574DD076DULL, 0x9694657A88753D15ULL, 0xD8CD3EC47D3D3170ULL, 0x3983B51A99754AC2ULL, 
            0x6C85E9C9899B8126ULL, 0x5515A0CC2F19EE2EULL, 0xD7D16D580F61E3E9ULL, 0x02BAA031E7CB7247ULL, 
            0xAF2C3788E266ABE2ULL, 0xDFFB1C6F1A74F100ULL, 0x4AC675B534ED4B87ULL, 0xCBB4281364E4B3BEULL, 
            0x6056E9BFD23EA321ULL, 0xC55F7FB28D97C8FAULL, 0x321C0BEC9D972AD5ULL, 0xBC6BFA58525DA168ULL, 
            0xA39F5197CA542A94ULL, 0xD447E86C53948777ULL, 0xE687966B7C17D6A7ULL, 0x085C90B7AADA8251ULL, 
            0xD8A7269E20923CC4ULL, 0x2AE6804D139A9221ULL, 0x1ECA5E4C31186E7AULL, 0x73AA4C3A4B78A356ULL, 
            0xA1CDE64A7C382994ULL, 0x7EFAA4C6289339A8ULL, 0xA922D9D165FB8846ULL, 0x819AD96179919494ULL
        },
        {
            0x6E002880B792EEB2ULL, 0x33DB9660520B0EE8ULL, 0x164FE06A682006FCULL, 0xE484038091F71470ULL, 
            0xF461C523840B68CDULL, 0xA636ECE111C47A60ULL, 0xAB0AE712602272A5ULL, 0xD200ADF43EAA1D89ULL, 
            0xDF902469E462297AULL, 0x68DF06638A23B32EULL, 0xF322C7B80E70F24CULL, 0xE4EF00B0066237ABULL, 
            0xEBA634524071CEE9ULL, 0x83395CD80F796317ULL, 0x140AA7020E29578FULL, 0xF59672F10373805EULL, 
            0x2D93085DD3D9B91FULL, 0xBDA33BC7E063A330ULL, 0xDA60AD44B69B5FCAULL, 0x5CCC45DECDC6D2BCULL, 
            0xEDBF5BBE714C969BULL, 0x0B1A75B023F2A088ULL, 0xC481AC8344B19AD1ULL, 0xE2670FFB82120D91ULL, 
            0xDDE06139332F696BULL, 0xFCC82EB6E5ECC85FULL, 0xCC47C17D39D9D7B4ULL, 0x8792FA640EB8921FULL, 
            0x717DE7FCB958DF4BULL, 0xECDF352DA8A22599ULL, 0x93446021E4869C6EULL, 0xC981447F0E7D2E62ULL
        }
    },
    {
        {
            0xE0C18F0987A5D208ULL, 0xE7905303B01926B6ULL, 0x789BDE6289E9B4EEULL, 0x2B92F0032572173DULL, 
            0x05FD8C8C429FE0F4ULL, 0xEFE5C0CEFC639FECULL, 0xAE07CDC9477ABC5DULL, 0x8E390B62DE9443DBULL, 
            0x5907CBC86A920178ULL, 0xCFAB9581A8A3E33DULL, 0x04F60D1F7175FF65ULL, 0x3E80ADE5A4F402BFULL, 
            0xF7764C1FB4BF8E24ULL, 0xE4C347F8687C4C7FULL, 0x2B8043F216A74A3FULL, 0xBCD3A19F14458CBDULL, 
            0xDE10FAB2DE4F1F65ULL, 0xC3E011E9F1B27F3BULL, 0xBF18CCB4F3C93E71ULL, 0x210B2833B09C2DA4ULL, 
            0x0A88F7725738FC3EULL, 0x88CFAFFD02FEBD47ULL, 0xC461EB5C0ACF76C4ULL, 0xA44AFF96A396A2CBULL, 
            0xFE8612D233258816ULL, 0x6860080439FD7102ULL, 0xFC2B28F78FD4E7F7ULL, 0xD2952327194B492EULL, 
            0xFDDF398BFF24ED0BULL, 0x1D3375EDCFB84745ULL, 0xFBA22D1CFC8D13E0ULL, 0xAAF742F3EDDA48B5ULL
        },
        {
            0x34C0E4170D3BB44BULL, 0x9AF92EFF675B6504ULL, 0x2775E6F8AEEB0012ULL, 0x7332CF698D02A3E7ULL, 
            0x0C177B7091A21B4EULL, 0x228D98C11F256587ULL, 0x396B72024DDE5562ULL, 0x9B877E4EB65AE29DULL, 
            0x4CEC215B3A978BF9ULL, 0x2629FCD292217D49ULL, 0x299EB465D1F15619ULL, 0x4D0102ABE2D07C24ULL, 
            0x7C0B75B198A6079EULL, 0x70F44FCB4252BA27ULL, 0x6A02B9B8B7C64075ULL, 0x669326B24C669CD7ULL, 
            0xEDE9102419E64351ULL, 0x1EC7A1D820F07716ULL, 0x8198C40264629656ULL, 0x62D84BF872854E06ULL, 
            0xCA33D18BC575D4C7ULL, 0xCF1007151FCA1185ULL, 0xFAADB2FE40FFD974ULL, 0x6B2CE9541378E652ULL, 
            0xDE683861EFB2FC01ULL, 0x15AAE502E3EA2F78ULL, 0x0D1149C9166B1606ULL, 0xC6D7563FC66844E6ULL, 
            0x79188CA4B72D1EB9ULL, 0xEE239BEC4605EEEDULL, 0x15502544F174C5FBULL, 0x881B4F3DB7348D8AULL
        },
        {
            0xB9798F19D41E945FULL, 0x2B2C7D78C582A8BFULL, 0x6CA12DD82C839CCFULL, 0x2BEDE1871CD0A6BCULL, 
            0xF070DF2E89F8C3E6ULL, 0xE829D22B5ACFEFEAULL, 0xAF040545A1DA2414ULL, 0x11996DE581542004ULL, 
            0x57751695912F1818ULL, 0x1E8CF4F0A3B0B80AULL, 0xA1C170D66D32BD24ULL, 0xE7AEE35E35DE73C9ULL, 
            0xD61F590C493DC000ULL, 0x023F682A10847B27ULL, 0xCEA8E78027310D5FULL, 0xA2079552C8BEF28CULL, 
            0x5B2CF61879FA1559ULL, 0xBC9CA214A89D8C31ULL, 0x38DB45ADAAA8F033ULL, 0x0F9D1F3539912EE6ULL, 
            0x03DA145B21FDCC09ULL, 0x913773AEC02CA36CULL, 0xB91167FD0F6064D5ULL, 0xB9D96EE362BE4ADFULL, 
            0xF65852F83782F29BULL, 0xBC919172FF9A6B54ULL, 0x4E1ADA3B9CBAA4C5ULL, 0x26A84A1B1ABC07E5ULL, 
            0xC01B06DFC86BD5D4ULL, 0xF5517F334233CFBDULL, 0x58F6107143CE2B29ULL, 0x2109F3A68B6B39C0ULL
        },
        {
            0x2968E9E498181A76ULL, 0x25D0FEE53CA0CD6FULL, 0x5922F633812C7EAEULL, 0x59F378DDDD8BD5EFULL, 
            0x00E7DD5315DF8F5DULL, 0xE927B8367340A766ULL, 0xDEAD1643235E066AULL, 0x60ED3A5FEBFEE3A7ULL, 
            0xAF9E75568564E660ULL, 0x07B0CBBA6F2309BBULL, 0x0DFACB6E195E63B2ULL, 0x977169CAEF29EC37ULL, 
            0x9E5557C6AF0DFEDAULL, 0xFB2782FEF4ECF819ULL, 0x894F134970588E70ULL, 0xF0D87BA2BC4F2F3EULL, 
            0xE432BFB06BAB49FDULL, 0x00C956F1A8033E39ULL, 0x740C30F7B5A82927ULL, 0xF1D9A98390C46517ULL, 
            0x54B4EB1AAE53E26EULL, 0xA05C71EFA56F5A7EULL, 0xA1613DE409D99F9AULL, 0x9DBFA4C8E5022838ULL, 
            0x727927FE54F557B4ULL, 0x5532C7107F78F6C3ULL, 0x2724B08587FC25DAULL, 0xC9097A6F2F38FD06ULL, 
            0x18DD7C481E51F3FFULL, 0x1C06FA17AA2CB312ULL, 0x1F35215A8A14F555ULL, 0xFA48D7CBC199B972ULL
        },
        {
            0xCD6FA4653C28BE40ULL, 0x41A0C141583E5D89ULL, 0xDE6AFC2416B35B25ULL, 0xC81D82EAA5B32C78ULL, 
            0xD71DD6A7C8C5685EULL, 0x8D81960852F553AEULL, 0x85B0FDD8E36EC776ULL, 0x159970FE72889A0EULL, 
            0xD4DFF7028AD5EC84ULL, 0xDCFEE5ADE352403CULL, 0x2BEDAC1B91B9F915ULL, 0x9BB5CCCEE4A6B2A4ULL, 
            0x5B5479559F841B8FULL, 0x7F7F366F8537CE8FULL, 0xC216159B12DC05D4ULL, 0x77664397B339262FULL, 
            0x621939C3876D27F6ULL, 0x72DDB3A53BF6702BULL, 0x1B33D984E99EABEBULL, 0x0941EF586F0A14CCULL, 
            0x2CC78ED2E1FCCA29ULL, 0x7D31A6117E8A5ABAULL, 0x3F176794058A4D21ULL, 0x6D09B63A9A5933A7ULL, 
            0x419B23A4C1974A40ULL, 0x7A9AA947455B6D6AULL, 0x635DAA5197542132ULL, 0x436301810A2FADDDULL, 
            0x7E49FAFF516D51E6ULL, 0x22989CD5232C0E66ULL, 0x1DF9786D52EA0A19ULL, 0xFA41612DA553F3AFULL
        },
        {
            0x8B724F80273270ACULL, 0x28B1E97D748E9E48ULL, 0xD36E5A45315FD064ULL, 0x2C6049BCBEBFB99BULL, 
            0xC71D5D2069A4AB44ULL, 0x26312832F49AA852ULL, 0xD13B96D03671E401ULL, 0xC9C70555EC2C6698ULL, 
            0x56A15A15A91626AAULL, 0x507EC2A4F8F84BC5ULL, 0x9AA50C5160DA5D73ULL, 0xDF567AE0500B13A2ULL, 
            0x2F3CD2AF146C4CE2ULL, 0x9EB1956CE34618E2ULL, 0x10D7CE42BFD0BE05ULL, 0x1DEDF250E5F50B69ULL, 
            0x1289059DBDDC6920ULL, 0x2F9D92E931CDC979ULL, 0xE909127412F30DE7ULL, 0x0F0512FA16AD5B9AULL, 
            0xB00F4A771AB51162ULL, 0x08C5692171770351ULL, 0x623D6EE56D1E78A0ULL, 0x10043D62DD7FF11BULL, 
            0x06D524A25B8C62F5ULL, 0x3FB947722754CC37ULL, 0x2EE8CC3A57E8BC20ULL, 0xC22CC66D529E4D07ULL, 
            0xAAF3922A4E03E1FCULL, 0x3BB8CE643414DFD6ULL, 0x383BDC3DC8688A14ULL, 0x656FE4D5E1114799ULL
        }
    },
    {
        {
            0x3721304802C6CEDEULL, 0xC7FA35E3D7A542A8ULL, 0x3A55D84A1ACD42B8ULL, 0x949652EB37C3FEC5ULL, 
            0x60085D4E56C296F5ULL, 0xFE2D00A7A07C3292ULL, 0x24AD1EB975009476ULL, 0x59FC0B997374049DULL, 
            0x98756F4E368BA73FULL, 0x86C94887B99B1E71ULL, 0x1CA173CE0D540580ULL, 0x799BDD5E5A2A79CDULL, 
            0x0B2320126DBBAAEFULL, 0x4891330158C61E98ULL, 0xEDB8227DEEA8913AULL, 0xDC45CEAEE3F9E716ULL, 
            0x620FEB170F1710CDULL, 0xA0325B8071111278ULL, 0x96C43090C6C883CCULL, 0x55DB959CB33776BFULL, 
            0x8606F1BF387205CAULL, 0x29102387DFF41AE4ULL, 0x5EEF2822166512F1ULL, 0xE093BB594A15C3B2ULL, 
            0x0F59D351868D4E02ULL, 0xC351DAB83AF441CFULL, 0x1461BA46117327A8ULL, 0xFAB3795EEB0BB650ULL, 
            0x35B458922C1B4AB7ULL, 0xFDB25B5312DCA8E3ULL, 0x2C59FED5A2F53412ULL, 0x68B9BF17FE8BEF09ULL
        },
        {
            0x6924EE256B463A14ULL, 0x91EBFE8C805CAB69ULL, 0xE10CEBAB874E056AULL, 0x39E9FDDA10B51809ULL, 
            0x93B9059A4AB8AE8AULL, 0x70F36209B9DBBCB6ULL, 0x178E7960606A6E87ULL, 0xE6F0F7236C083100ULL, 
            0xB6BDF55A07D10682ULL, 0x7063EEF0431D6DA9ULL, 0x42CF0E42D1973C84ULL, 0xBBDE270D85A9D759ULL, 
            0x1D4741821C373C39ULL, 0x70182E9CEE2BDC6BULL, 0xBFF6FC8CBB910B35ULL, 0x5CF29EDDFDED9769ULL, 
            0x899F18BB0CEBAAA9ULL, 0x67BB0B4ABE55D52CULL, 0x3ED8A0E2805F6DFCULL, 0x67180D4F7545D13CULL, 
            0xEF7C46E296B02D6BULL, 0xCADF21E4B56EE970ULL, 0x2F8673261273C34CULL, 0xF6DDB4EBCE96C19FULL, 
            0x8DFDEB69609102AFULL, 0xAEE0788AAF741ABCULL, 0x06A249C0CA551E3CULL, 0x4CAB119321C4C3DBULL, 
            0x885506096AE3C671ULL, 0xB1706E9DCF238A93ULL, 0x305CE2B3DA3E6CA3ULL, 0x63EB3A6FD904D703ULL
        },
        {
            0xFF9C8F4599CA3A84ULL, 0xD7D2F83637E49686ULL, 0x3BCAE9E3BA827B6AULL, 0x53F8F1C66D3AFABDULL, 
            0x48CA778356725065ULL, 0xD0B51BAAE00D6446ULL, 0x48761BA48D9DB0A3ULL, 0x7306D0300EE11B98ULL, 
            0x3FAC13B251E615BCULL, 0x1AE0F06170FB0AC5ULL, 0x4746BCA7BD2F7E5FULL, 0x930A4AE8AE2559E4ULL, 
            0xDEBCC96C4AB6EB3AULL, 0x982FC3393F6FDFFEULL, 0x653D946A3B1BC336ULL, 0x8A1786BAC34F6644ULL, 
            0x3A22FF0000055DADULL, 0x8A0E4ED532A9DD6AULL, 0x70BC2E775680BC00ULL, 0xDDC61B4E75675FE9ULL, 
            0x264BB5D422E4AEC1ULL, 0x64390ECB1E54F490ULL, 0xFEE65A2643A8056DULL, 0x514C926B2EA5A9B3ULL, 
            0xA9D7E6907F6D9E74ULL, 0xA2B8FD8E4A4DF03AULL, 0x401BE576A5350115ULL, 0xDBC58423210C9DF3ULL, 
            0xC1B64E17358766CDULL, 0x8461DC4958CFB8B7ULL, 0x45CA88A9110A2D08ULL, 0xEABE45FB41BE6F50ULL
        },
        {
            0xD38666D8919C834FULL, 0x98977B6E549BBE13ULL, 0x9DF26DC15D1A0FDAULL, 0x3AB276C473C0C79DULL, 
            0xB54F76A3E6713198ULL, 0xF8EDA30833CDED52ULL, 0x733B362E1068B83EULL, 0xB977CB57773D7894ULL, 
            0x4E65441333AC9E8BULL, 0xBE988DD6741FA5E8ULL, 0xF8F7351B87FB9B60ULL, 0x06906D6868D83FA8ULL, 
            0xA7E8697B463741A4ULL, 0x78AB1656EDA047F5ULL, 0x035E0F1E5A788AC9ULL, 0x57EBF656C5D600C1ULL, 
            0x7B3031FA42F80A94ULL, 0x02B1260A4A039C56ULL, 0xFA1B6CBA1F5563B8ULL, 0x3973B4A2600FF8FBULL, 
            0x230EB4B5C81A442CULL, 0x82AD9B497046CF36ULL, 0xC595A0BA851C506EULL, 0xA5ABA7DB9D425A99ULL, 
            0x0A3A1A7548A77C73ULL, 0xEAB7389BBEB442D2ULL, 0x86E577BF1CF70CE3ULL, 0xEC99D4C5F9760E0EULL, 
            0x589A244A0DCC364BULL, 0x2EBEB37525B02C6BULL, 0x62590FC77A3F25A6ULL, 0x07FC40E4FB2DB4A6ULL
        },
        {
            0x2074B49DA5EFA8FDULL, 0xE35A1D92019B6D13ULL, 0x135095E071EDE6A9ULL, 0x3D79524D88F1D80AULL, 
            0x8BAEDCDB6A8B4245ULL, 0x3759F46D2633D2F9ULL, 0x8C5DBFA8F9B3DCC9ULL, 0xCE1A5BB362975F70ULL, 
            0x4DD6DB7649F105DFULL, 0x53F13C084667FE21ULL, 0x3D4001B111A0AB35ULL, 0xEE86BA84EA967EDBULL, 
            0x44262417F97402E2ULL, 0xED3C8B3B017A8CF4ULL, 0xE568670008200807ULL, 0x118CF1DA5EB681F4ULL, 
            0x6F91519228B550B4ULL, 0x5CCA1377D07A82A1ULL, 0x4B7F47944B164B46ULL, 0x318366E31A065FEDULL, 
            0xFA718F2520962B23ULL, 0x222E634C712DD623ULL, 0x08D46499EB6ED0E2ULL, 0x09ED85392EFCDEC2ULL, 
            0x2501276C23DF5354ULL, 0x4C391223770DF83EULL, 0x885FC7BEE2C49A9EULL, 0x8293086C576A60DCULL, 
            0x83B046E9494FE533ULL, 0xFD25804BC6657CC2ULL, 0x5066BEA15EA8A651ULL, 0x11390664CD3727A9ULL
        },
        {
            0x8CDD1765DEF32B63ULL, 0x4DF55C7B8370380AULL, 0x94BD98297682E92BULL, 0x9D8B8A80E7E2B8A9ULL, 
            0x12BA65DD4F201D1EULL, 0x4468832321D3040BULL, 0xA97B24834C97A82CULL, 0xB89E8FD03EEAEC1DULL, 
            0xBAAC44B47550084CULL, 0xA63790F426A23ADCULL, 0x1A0981095CC21962ULL, 0x7CD9FFD5B7AB6993ULL, 
            0x97310BE0AA918BD9ULL, 0xF98C838CC32D19E2ULL, 0x5B4119351B4E9358ULL, 0x31CDF75228CD9B67ULL, 
            0x31B29460F1A1EAC7ULL, 0x1CF2AC7D3C3219C6ULL, 0x53CC2B079DDB9126ULL, 0x4732DEE0DB2B913BULL, 
            0x6BCB38ABEF444A10ULL, 0x0E208CA621977AFEULL, 0xAEB77C295D22E537ULL, 0x53E044D413D1672DULL, 
            0xBCCB56688B83E413ULL, 0x51642BDFC05DD517ULL, 0x381E443414C0B012ULL, 0xA67A63991D3AF6DEULL, 
            0x5CB435C4EABDBCC1ULL, 0x1A5AE180EBB6CE3BULL, 0xF690176E38506AF0ULL, 0x478AE106EECFAB05ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseDConstants = {
    0x6CFC66B3440B103CULL,
    0x1B329ADB5CBF99DDULL,
    0x52E25D306BEBFF6EULL,
    0x6CFC66B3440B103CULL,
    0x1B329ADB5CBF99DDULL,
    0x52E25D306BEBFF6EULL,
    0xB0C744F5466A6A05ULL,
    0x55FEC3CCA54584B8ULL,
    0xA6,
    0xBE,
    0xB0,
    0xBE,
    0xF5,
    0xFF,
    0x92,
    0xA6
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseESalts = {
    {
        {
            0x6D4656C0CFD02E88ULL, 0x3D266C85A4E8BC5CULL, 0xD3E377CBEE88ECB2ULL, 0x2DC48E17A206E96BULL, 
            0x8B8C0D088E7851F6ULL, 0xA17235461AF6DB61ULL, 0xCC0363FA8EF54685ULL, 0xD8E70825F0ED6921ULL, 
            0xD49E6DEC75B3304DULL, 0xC9BFF8FAD12AAE6CULL, 0xCB830A2460619616ULL, 0xEEE879661C52257BULL, 
            0x343E0F296C05264AULL, 0x559B7C28A666F0CBULL, 0x6D118D94ABA9138CULL, 0x9089BDA3330AE3CFULL, 
            0x78713F86622AF306ULL, 0x76387E691BE5C453ULL, 0x54AD2C7CE562BE57ULL, 0x0F3CB2A960BAF76BULL, 
            0x11BB9634259E9CDCULL, 0x04D56D3272864657ULL, 0xB7039BB27DEC8732ULL, 0xFCC4257A47518C5AULL, 
            0xB969D639BF22D532ULL, 0x55F95AFA67D1FED1ULL, 0x5984A502EBD8598DULL, 0x8AF9197B4882B7E9ULL, 
            0xE8A2848B3691FCB0ULL, 0x1E452AB587007846ULL, 0xD09F0A0D30833391ULL, 0xABCEAC762D249888ULL
        },
        {
            0x96CDD22710AED3FFULL, 0x6E2A199FF25E8424ULL, 0x5F3EE8E870095875ULL, 0x3337BE30258A73E1ULL, 
            0x9CB950E7D4E20AE2ULL, 0xEE8EF3544B02DAF1ULL, 0x1C334156D07F504AULL, 0x3024EBCB79A040DEULL, 
            0x6E8D63C7156ED4C9ULL, 0xC2FE41CDB9AC6F3FULL, 0x10B47691E1F584BBULL, 0x23804B6CA3C8ABC9ULL, 
            0x9FED0CE583D3FFAFULL, 0x17AE0AC1E18FD5A2ULL, 0xAF3461452942B4AFULL, 0x49826C75C56480A8ULL, 
            0x050397EDD23B6F85ULL, 0x1DECDFC3315C3F19ULL, 0xEFF4B43B6D2563B4ULL, 0xA545E4DC392C3763ULL, 
            0xD8F2550A79B2B43CULL, 0xD0CF74448DE99DBAULL, 0x1FCD45B3DB7BCFBFULL, 0xEC873D9806CAC169ULL, 
            0x9DC7EF84457E80D6ULL, 0xB33952CB93C14A92ULL, 0x052C5366F42C9D79ULL, 0x98040A7106DF0081ULL, 
            0x5E0C2F8CF1E76A0BULL, 0x7DCB13AF4C814D59ULL, 0xAF17F3AF0A80BF1FULL, 0x2748A2F839B4C11EULL
        },
        {
            0x52BAFF9A2C312224ULL, 0xE81C939BB0F15D75ULL, 0x815392EA1EA06051ULL, 0xF7F8513A8A9C9417ULL, 
            0x0CF8CADC1F89B3E6ULL, 0x58C5A5454382BDB4ULL, 0xA475D02D94C09944ULL, 0x45FE691124A96552ULL, 
            0x2332764B287BBFD3ULL, 0xB6C375A98B97C06EULL, 0x6E096776E9A45B25ULL, 0x552D690A11505D36ULL, 
            0xC5A67EB624C77AC4ULL, 0xBEC7675B4F17F723ULL, 0x4515F10F751F06F5ULL, 0x1A1A11D62FC651B4ULL, 
            0x486A4AED1852498DULL, 0x1F1FFF11C0DA1086ULL, 0xD39676BA7DFE1596ULL, 0xDBB3635C59B976F0ULL, 
            0x3015B3D81954FB34ULL, 0xB911C89694EEEB59ULL, 0x68032C29160EAE6EULL, 0x9053B28809D2A3E9ULL, 
            0xDF53CD72C54AF96BULL, 0x3ED3A1050FBBB474ULL, 0xD51808E2177963DAULL, 0x664746E3950899BFULL, 
            0x7335E829929C1313ULL, 0xE626ADC0F4A9B1DBULL, 0x87B8047444E1F8B0ULL, 0x3FCFCA3CFAA196F1ULL
        },
        {
            0x1EE6A47C99F55A60ULL, 0xC6EE4A480FDCB905ULL, 0xE46F07DDBD9461DEULL, 0x59BAAB82FFB43686ULL, 
            0xF53BB25549928091ULL, 0x84DE0D3F918BFDE1ULL, 0x724B368AD26DD4D1ULL, 0x8B1F3E9D52856DC5ULL, 
            0x31B4234C755B3340ULL, 0x5E1B4F257091F951ULL, 0xA313DF62801B741DULL, 0xD9A088A5201124DFULL, 
            0xFEF140A2E66A51E1ULL, 0x56D7495AF71AE3AAULL, 0x3FED819FAD42C96EULL, 0x5FC396CC0C7A9220ULL, 
            0xC1005E164834EA7EULL, 0x56EF5A67BA0661ADULL, 0x1A04BA1E2254716EULL, 0xBE028F2C3E6B5C91ULL, 
            0xF0FBA9D111DC76A9ULL, 0x0D394CBBAFD2790EULL, 0xF5A0775F1B1C6420ULL, 0x8513131E3DC1DA52ULL, 
            0xC6807D819848D5AFULL, 0x82ED19F981C2EDD0ULL, 0xAE691A5CAF31F605ULL, 0x1EC637F7FEBD611AULL, 
            0xB0AFE17E657DDA10ULL, 0x4B8EF7B3D5AA7B3BULL, 0x7C7E4A0D696746D8ULL, 0x740710330C68F406ULL
        },
        {
            0xEAF74603C4EF5673ULL, 0x6823637EB5C4D73DULL, 0x2E718102CA5F21D7ULL, 0x1318BED7203B493AULL, 
            0x5808E5AFEA8DED6AULL, 0x4122D1A37DB1A7B7ULL, 0xDF6E625B1667D572ULL, 0x22E72BA25AD1115EULL, 
            0x8D774BADB2199509ULL, 0x74B3F5DEB531BDA4ULL, 0x328FDE38153D9768ULL, 0x89613633CBEF25D1ULL, 
            0x846A58609331F7AFULL, 0x42293A2C3F8E20F8ULL, 0x299838D7EF904E1BULL, 0xD6947D64CEA7789AULL, 
            0x53A051F4CF147855ULL, 0x02650D8A37C2E54DULL, 0xF453CFA02EDC20DFULL, 0x9CD2047FBDB7B15CULL, 
            0xCF7CC92101888DCDULL, 0xD0EC16BCDBD66EFEULL, 0xC70C2927B7948A02ULL, 0xE01BD6B55DFB29F2ULL, 
            0x8BB6613750486CBDULL, 0x2B1F0F51EF30AFCEULL, 0x8DF55836BBCD1781ULL, 0xA1E650B62629DA7AULL, 
            0xAFC6BE8FA68BB640ULL, 0x0FED200FEF885DB7ULL, 0xC94906E5A6A06AACULL, 0x14CEF6F5FDE81344ULL
        },
        {
            0x4C7674EE6D7A4187ULL, 0x0D79FAA7F7E16BA1ULL, 0xF69C5088E68E85A7ULL, 0x7513DF3546C6777BULL, 
            0xA3F25E761E357D53ULL, 0x7170FE0BEC68B976ULL, 0x16F682EB67E7828AULL, 0xD815C05569B8F204ULL, 
            0xDD383CBCAE16603CULL, 0xE9436A5F08727521ULL, 0x56386ABE562EEC46ULL, 0x3CF2E7BF0F7709ABULL, 
            0xD627593F5C39AF15ULL, 0xCBDD1E440C686E43ULL, 0xD65FD99E9AAD7C4BULL, 0xFC8BF0E9BDD88AF6ULL, 
            0x525A375BF3639F22ULL, 0xAE2B2CEFEAFEB18BULL, 0xC9EFEA191F6ADACCULL, 0x9179087D17440151ULL, 
            0xB87E64D3FE08DDA5ULL, 0x1BC86B77638622DAULL, 0x8FC2FC47A60E55FEULL, 0x5A875F7D06A6C620ULL, 
            0x6780CEED03CF5A1DULL, 0x3BDCF06D4D68FCE3ULL, 0x56DF94DB1B4F2A37ULL, 0x30A97A4380D5B6EEULL, 
            0xDE2D55CE885D604DULL, 0x951CF47916FCBB58ULL, 0x5D846DB409BE4F3DULL, 0x5E5D6C15B6E01E71ULL
        }
    },
    {
        {
            0x352FAF0CAEB0DB07ULL, 0x796B67C0C683F1EEULL, 0x1AAFE123346BE005ULL, 0x1F1CA6A9937236EBULL, 
            0x44A38E4604F483C9ULL, 0xC43CB4C697850E6AULL, 0x97B24FF39371390AULL, 0x061B2D1CD2208F28ULL, 
            0x698AF615FE5A3128ULL, 0xE84483D19EDCAFB7ULL, 0xEAA475318606137BULL, 0xD695BD9248BEAEDAULL, 
            0x1C267459C8E7F9E9ULL, 0x7DCFA0A5A5B716F0ULL, 0x27A1152CD2EBB855ULL, 0xA07CFBE97E1E110BULL, 
            0x872C9BC1CA136E24ULL, 0x8D4EB4B007539BA8ULL, 0x20D5760098A3D181ULL, 0xAB3CE2479EC3EDD8ULL, 
            0x5079BBB6552002E0ULL, 0x74869023F72204AEULL, 0xF15746D718B16830ULL, 0x2C421641409302EAULL, 
            0x113851A00106753AULL, 0x8AACF72EEFA96C7DULL, 0x6E55D683800D6830ULL, 0x5F8B718BDDFA903BULL, 
            0xF42761EA69136603ULL, 0x5EABC125C4ACEAB8ULL, 0x2ED60303B18EA722ULL, 0xBB86875BDC293470ULL
        },
        {
            0xF767F29961AA71F2ULL, 0xDF5C99135525E9EAULL, 0xBDF648DF8264EE35ULL, 0xFA9809F507DE2EFFULL, 
            0x184D514F32D5DB4EULL, 0x3DF2041C281C088FULL, 0x59AA5EEFB2C2A1EBULL, 0x1D2B4CD5C7D6456DULL, 
            0x601478DBBBC2FB21ULL, 0xFFD5837AA3D004CCULL, 0xF18D3341D104A4EFULL, 0x4949FDFC471545BAULL, 
            0xBC37F4200CC5A57EULL, 0x53692777F20FB7E0ULL, 0xB5147C3D8CDDAB9AULL, 0x7AE30F68CAF47587ULL, 
            0xBE723A573509E242ULL, 0xC9DB794A43B16F50ULL, 0x34B13226C9C487A9ULL, 0xBD1807E5FCD2FF57ULL, 
            0x9BCD533EDCBA0389ULL, 0xFA7884E447FEE562ULL, 0xDA578277F8A06694ULL, 0x4607EFBF7DE89612ULL, 
            0x83EA3C2C42781272ULL, 0xF17B030615FDA5D3ULL, 0x523D84AC396CE52EULL, 0x5566CDE653B6F069ULL, 
            0xF262B372DF165BD0ULL, 0xEED5D959A6085BF7ULL, 0xAF2D7D19A199C947ULL, 0x22E7489FFB6CE202ULL
        },
        {
            0xD68C4091122FCEB8ULL, 0xE0042B6DAB8A5CEDULL, 0x52B6A095F5707521ULL, 0x20DF57DA27C6D55EULL, 
            0x25451CCA85F4C4E4ULL, 0x56C26574AB767EE8ULL, 0x72DF52F88DD8424EULL, 0x8F3C03E5BA90613FULL, 
            0x96730C82EE2C4DD5ULL, 0xA555569F2A42AE8BULL, 0x370BFA69B9FAAD57ULL, 0xDEBFD99E66D281F6ULL, 
            0x7A233DC93A6AB97BULL, 0xDF8F4FCD71DBDF02ULL, 0x01445C054027125BULL, 0x2F47C7D9D6528DBDULL, 
            0xB642E1281C0F8373ULL, 0x9BB0FB81FAC9D9E3ULL, 0x92D59D5DF33F3634ULL, 0x3293C5D61DA69652ULL, 
            0x010713C4056A22E4ULL, 0xBF90B41839F69BAFULL, 0xB1EECCDA22BE2889ULL, 0x28AC6DF959019D00ULL, 
            0xFA8C2AF5BB316032ULL, 0xE3E74B78A6B70203ULL, 0x0703CEB969305058ULL, 0x82F74F4E9111B065ULL, 
            0xE583484A73DC816EULL, 0x76CC1F0273F4BA9BULL, 0x1128D2EFD38020FEULL, 0x7A5397CFF466DDEAULL
        },
        {
            0x5D57B4CADACDB9BEULL, 0x22FFB207CD6E751FULL, 0x72CD53779504A0E1ULL, 0x171385E4343BBE06ULL, 
            0x368FEA69D384E8CBULL, 0xB6804098D3C1C4ABULL, 0xB36CE312EC9F91FDULL, 0xDDD966FE9A2BE20BULL, 
            0x5192BDC789504033ULL, 0xBC65CD73F5118164ULL, 0x1C93C97A14A8308AULL, 0x0738A50AC6B4F99DULL, 
            0x3532B988DAFA565CULL, 0x6D66A0900FD23C76ULL, 0x6D85E041170512FAULL, 0xFE0B38D9248DB4FCULL, 
            0x5B88C0B980359104ULL, 0xDC4BB4C930900B8AULL, 0x2D64330F2D1B1DF2ULL, 0xF3252B4A3C8C7569ULL, 
            0xC8BFABAF9F0C04D0ULL, 0x1F06C4E517156ADFULL, 0xDFCEAC73B9881753ULL, 0x071CFA936DDFECB7ULL, 
            0xAB56214B72956C31ULL, 0x80D0EC4410FF3DF8ULL, 0xFC00061A64B1C730ULL, 0x22A7C7AA17B6B920ULL, 
            0xC3F053E37A61CBF9ULL, 0xD80ADBF7F2F53E0BULL, 0x442587D9B2C121B3ULL, 0x291A1ADEE7811422ULL
        },
        {
            0x210DFA3EA99CCFC5ULL, 0x02C2C8A9969FDCDDULL, 0xED195FA53C0697C6ULL, 0xD27C0F8E1D49F2F0ULL, 
            0x091DCF4B67303D63ULL, 0x3926434D8B5F9B12ULL, 0xFD44DCDE39A9F15CULL, 0x6BC0D433CDBAC429ULL, 
            0xEBF13A5657C0F225ULL, 0x88E6D3AE285B34FBULL, 0x800A8D05D0A70A9EULL, 0xFC32E8A13DCA530FULL, 
            0xC452012E8D0D8476ULL, 0x3C18732CEC77B6AEULL, 0x7940B8FA968759C3ULL, 0x2617DD4B9407804BULL, 
            0x54A06E69FD0B2994ULL, 0x9802CF2747FCADB1ULL, 0xE00164609C3ADDB1ULL, 0x3515B950DDB02073ULL, 
            0x41AAFE8134B57D6DULL, 0x291D52DC8223C3DBULL, 0x54E9E8AF32354510ULL, 0xE50560D292DB2171ULL, 
            0x337F48A72D45D92CULL, 0x6D9F202AB66D9395ULL, 0xF83CF7234045E329ULL, 0x2AB26F2865427FDEULL, 
            0xFCBC8D3F47C8FE13ULL, 0x00DED93C3D661C14ULL, 0x04437CC56D00D09BULL, 0x24BE5616CDDC0968ULL
        },
        {
            0xE4E2DDC5B16FB193ULL, 0x43472002AACEE4C2ULL, 0x5BB3CB3689603BBDULL, 0x3CBDC225E98CA724ULL, 
            0xC24D199981E88EBFULL, 0x77D1404202CAB51CULL, 0x709A6FEFF6B6060BULL, 0x9926DE0445143EA7ULL, 
            0x7D0EE8FD1D5464ACULL, 0x0A4FAD1F1B14D293ULL, 0x86F5AB295F1384BEULL, 0x4ACB5DA8E72197D0ULL, 
            0x378DE265C856122FULL, 0xB0FDACCF860EDA04ULL, 0xF532D2AEB46FF074ULL, 0x35EB397BD871B177ULL, 
            0xEF55EC3930BAE5B1ULL, 0xF403826E593E4B88ULL, 0xCF8F76ADC5BA7320ULL, 0x4C1BFBAB2AFF1FA6ULL, 
            0xC6002CC7018489BCULL, 0x2AF648916431CE5FULL, 0x5866CBEDDAC7A8FAULL, 0x53466FEC301CA676ULL, 
            0x37B57A5B04338638ULL, 0xCA1951BD90AE5937ULL, 0xFEA831C488871966ULL, 0xF7CF4FF946622556ULL, 
            0xE60D1B0032C0DDD3ULL, 0x7538A4EFC5DB91A7ULL, 0xCD974BE2452A82E7ULL, 0xD84C9807C94A5397ULL
        }
    },
    {
        {
            0x215018BE36423509ULL, 0x951C92496D907AD5ULL, 0x39ED8908B83E51E6ULL, 0xF79B6386537EDBB3ULL, 
            0xA36A11D6359F646DULL, 0x3CC1082C5868827FULL, 0xAF702555FFB592F4ULL, 0x18FA134D89309BF9ULL, 
            0x5B4A2D2251FA1C1CULL, 0x2FEBA9CED7AF1386ULL, 0xBE82546C8AB7F8F0ULL, 0x6FB52E48DE70C863ULL, 
            0xB9082CC87A14CCCCULL, 0x59B8C28C12750EA8ULL, 0xC88339BBAE2F56D2ULL, 0x6EA44DD27409A03FULL, 
            0x42E11D09601A81C6ULL, 0x26180624DE2FF848ULL, 0x6DC17EE4244ACB4DULL, 0xD9551C6DD374C7B1ULL, 
            0x6286B39FBEE4D522ULL, 0x87A21532A2CA8F06ULL, 0xF6D31189AEC7FB37ULL, 0xB9C3E9663B138D9EULL, 
            0x031BC49A6B7BE036ULL, 0x97914FD6B4C3C9CEULL, 0xE97C8C535C8FC03CULL, 0x16898D552C402AA4ULL, 
            0xC38364DEB8AF2A18ULL, 0x914618E0C1A46862ULL, 0x29DE7AE3240736AFULL, 0xA757501E037D59FFULL
        },
        {
            0xB096E6C55E2C92D3ULL, 0x500C6E89A1364DC7ULL, 0x7529A88BB825E58BULL, 0x58B980F7936EE8E4ULL, 
            0xD44EB45776DA695CULL, 0x0ED1532D7AD77ABEULL, 0xF6351FEF4F5A87E5ULL, 0x20B52A1CD63EA558ULL, 
            0x514C59176CEEAA61ULL, 0x899F6F7384FCE060ULL, 0x7F4922B0E0D26322ULL, 0x0D2F4DF68018E265ULL, 
            0x9F033CE534772DD2ULL, 0xCA83C84CCAA8E8FDULL, 0x7A77FDD5BDE54E1BULL, 0x8F8DE9FFEAAADC22ULL, 
            0x8A1C77EB84F97963ULL, 0x9613DB04B6F3A65FULL, 0x1F7E3E0D57BF0C0CULL, 0x41607C0A2F6EA219ULL, 
            0xAC1A20BC0BE5D0C2ULL, 0xAA6718BAACD48B16ULL, 0xBCFC554DC1A48BE5ULL, 0x6C4D87F38DC053ACULL, 
            0x2266C41AD904C658ULL, 0x783995744D443B4EULL, 0xDB606679AE30CF8FULL, 0x3DED5A3AE3C5D569ULL, 
            0x6109C7C18BB9D3F9ULL, 0x56B4E790B3475735ULL, 0x1C69D2FF62F50517ULL, 0x689C3A5961793ED3ULL
        },
        {
            0xB7E3144820B18464ULL, 0x86466F63CEB91F59ULL, 0x993116FFDCA071E8ULL, 0x21E5CCF8AA54E5B1ULL, 
            0x7F1660E43617036FULL, 0x765D92FD452A02D6ULL, 0xFC8B60D379F5B994ULL, 0x0EEF5739D66B087EULL, 
            0xBCFB771B003F8177ULL, 0xD57BB79CFB8D3DDBULL, 0xDDCF73266935B91FULL, 0xE0E53FE7283B82D0ULL, 
            0xDD30383C30F98444ULL, 0x0105F3DB50B9A51DULL, 0x424373B2FA4CC58AULL, 0x56507A888B1FEA61ULL, 
            0x0951C05BD69D8C20ULL, 0x4D4CDCC469541368ULL, 0xA630C8D1A26B5353ULL, 0x2ABFABCC86E609D7ULL, 
            0xAC64E29028891D0AULL, 0xA6F6491B72CC07A4ULL, 0x3CABBBDA96C4F261ULL, 0x7E1A440ED20732EAULL, 
            0xCCDF80CBDF6FBD95ULL, 0x85F44ABE67DCE6AEULL, 0xA89A284C0F03BFE2ULL, 0x18ECFC0953106049ULL, 
            0x4D3A2E50F860DB30ULL, 0x3FAF5A4AD21C1D7DULL, 0x67C30530A45B3B5FULL, 0xDCFC5EA5C638EF61ULL
        },
        {
            0x87A0D1C9AB0DCC64ULL, 0xB271063089B412ABULL, 0xEFE9B3E981595D68ULL, 0x5C4910EBBA83BE06ULL, 
            0x7B801820F6DB60F7ULL, 0x6E9988E42E8FB23CULL, 0xF671D941346261B0ULL, 0xDDB8CF20352AD1C2ULL, 
            0xA7A9A3C61B2F2150ULL, 0xED164DACF487FEACULL, 0x339766AB466F55C8ULL, 0xBBD297615BA11245ULL, 
            0xE797F98111CD2504ULL, 0xB09608E56E2BD836ULL, 0x644ECA84BADFF140ULL, 0x734EFD480708A8D0ULL, 
            0x6AA24F70517BBBC5ULL, 0x2EFB588FD3C2679AULL, 0x0E288B0758AC2CA8ULL, 0xB8AFED8E720BECE5ULL, 
            0xCFFA2D3B81AF3E29ULL, 0x7C805253E166CCFCULL, 0x99663E7B5F83C30CULL, 0x74CFFCD034DEFAF1ULL, 
            0x0457A9EB70E1348EULL, 0x55708ED1EAAF5668ULL, 0x609752BCEAC6E5D5ULL, 0x70AFD2BEBAA4BE14ULL, 
            0xA6F955881DD5A653ULL, 0x0B9408DBCE00D0ABULL, 0xA56F478833A189E6ULL, 0x1EAAF27D83454496ULL
        },
        {
            0x6682D9B87E53D967ULL, 0x95DCDEDB923FDC87ULL, 0x8181F8B313EEB1D0ULL, 0x501EC1C8673F3DD6ULL, 
            0x00BE28CB523E1A49ULL, 0x887CB6083109E617ULL, 0xF3ACBDDD93428662ULL, 0xE5BCEF1898033D6FULL, 
            0xC802FA6BBBC0FA64ULL, 0x2BF41361B1D6EFD5ULL, 0xE3E81EEF217CB568ULL, 0x73C8DC0ACA2D3151ULL, 
            0x3F199AF292C14C59ULL, 0xDDAFB3D2D2C4A5F6ULL, 0x90CE5B9B4C0C75E1ULL, 0xC69F4E51F4EAEBBFULL, 
            0x806D951296243105ULL, 0xE47786EACADB0940ULL, 0x7E290927472E5ABFULL, 0xBA00149228A11D07ULL, 
            0x761EC4175F6B1F48ULL, 0x0A9172CE704C2993ULL, 0x9F8B050A3809E43AULL, 0xF0C3400571D0DDD3ULL, 
            0x7978000CA6CF35FCULL, 0x6A0B62F65C262606ULL, 0xFF57BEF0D611CFACULL, 0xCE4ABEDC41AFC767ULL, 
            0x1DF0BA389AC7C6C7ULL, 0xED678D7A8ECC6CEBULL, 0xFE61A7228988A1B2ULL, 0xDD11F86080A9EB1AULL
        },
        {
            0xF4AD53B44806B99DULL, 0x3CB17BFDDCE8DDE5ULL, 0x143F881819CAA3C1ULL, 0x37A5D95865FFAAABULL, 
            0x759F163DA7F5D7A6ULL, 0x427848612A73F9DCULL, 0x9A7DE2632440E3CFULL, 0xB6B12A139B9C587DULL, 
            0xF4D1DAE1D55761F1ULL, 0x8746E7A234F4A152ULL, 0x80C82B2200B2227AULL, 0x55804C3E7D58708EULL, 
            0xE61F25B1924EC45AULL, 0xEE443DAF20A3FD4AULL, 0x4F673A3D3C328823ULL, 0x1C1ADA9C98E07419ULL, 
            0x476BDCDD4ED10123ULL, 0x24B32E4694973564ULL, 0xF53C0F548711EE31ULL, 0x31A1641713E50DE4ULL, 
            0x5BB76280C94859DAULL, 0xF8F7F139FC237F7BULL, 0x3ECB810AB4237366ULL, 0x2ABEC35FBF95514AULL, 
            0x6BE7669B29EBD415ULL, 0xBD9E649FC4842F4EULL, 0x6DE6EF03682AC469ULL, 0xBE524AF898A1A186ULL, 
            0xAB1D0AA68960EC85ULL, 0xE2DD62E01C760F16ULL, 0x534123E4B41D226CULL, 0x1D5C73F8B410D640ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseEConstants = {
    0xD64FED67E1C80087ULL,
    0xEDA2D2653FE8F780ULL,
    0xB2A7C6463493FED4ULL,
    0xD64FED67E1C80087ULL,
    0xEDA2D2653FE8F780ULL,
    0xB2A7C6463493FED4ULL,
    0xB3337F84E21E45FBULL,
    0x1EF4A63E934828EFULL,
    0x9D,
    0x45,
    0x48,
    0xE1,
    0x7F,
    0xC4,
    0x83,
    0x07
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseFSalts = {
    {
        {
            0x494F9D0236CB33C9ULL, 0x6EB658674C09E197ULL, 0xED5772EA33424E55ULL, 0x8CA0A2DCDD83AF78ULL, 
            0xED025E81647D66A2ULL, 0xFDD773385A1BD0B5ULL, 0xAACC82B1059E31DDULL, 0xF444E41400231191ULL, 
            0xD29988EE6309E375ULL, 0xD6E25E0201DF3B41ULL, 0xBC6F6403B713F773ULL, 0x9EA82C8F3808EE52ULL, 
            0xDF5FA06D981EA006ULL, 0x4A2613CBC8320FD1ULL, 0x8CF9353BA9C33F12ULL, 0x5285A70C6602AB8EULL, 
            0xD40B13824D6064CDULL, 0xCDAFA93BE48DF64FULL, 0xFC973F3E2E2FA3DDULL, 0x43E1D802DE9B4BA5ULL, 
            0x8A31BEEB13220E27ULL, 0xD5A76803A201A564ULL, 0xA5B6A60978435BD4ULL, 0xF9888F13D1324C37ULL, 
            0xB0EF17128259AF4EULL, 0x30DAB1CBCF91E0FCULL, 0x60CCC4CD20521FFFULL, 0xC23E32E5B04DCEE2ULL, 
            0xAE45B0247474D28FULL, 0x935624756EC3E253ULL, 0x4AF5F52006537EF4ULL, 0x1C6878A515982C21ULL
        },
        {
            0xBAE9052F8C41A900ULL, 0x9CE6FAA657A50597ULL, 0x620F5953934F4264ULL, 0x6DB52080B5D29D93ULL, 
            0xD1B6791458C7C4DAULL, 0x346E80193C716408ULL, 0x1A3C27E580EA0207ULL, 0x16C1BEDE2B6F1A92ULL, 
            0x9D55EAB41A1249B8ULL, 0x8F12995B09B89A6DULL, 0xFC9F448BD5A066A5ULL, 0x4025D09ED31A1A85ULL, 
            0x00E181F3DC683AB2ULL, 0xD8485AAB7CA88F4FULL, 0x9CF081B40F465ACAULL, 0x7B594D35C7CDEAB5ULL, 
            0xD77E3EE0BF80D7E1ULL, 0x209F1D282FB1A6A2ULL, 0x3F1158DD3FD53EE0ULL, 0xBA4BC46F48F93CB5ULL, 
            0xA1B0ED4D7422A3ECULL, 0x14EECD08A5BDF5EEULL, 0x6157A2FDE11860B6ULL, 0x18A7A48B5D2EA212ULL, 
            0x481AF40C4F96FCB6ULL, 0xF37F9C5B347292B3ULL, 0xAA3C11D6AFDE51A5ULL, 0x2C34A3BE6E93CE91ULL, 
            0x57B3E4FF52447EC5ULL, 0x28CC8682C6AEF1B4ULL, 0x173D7B03AA00ED30ULL, 0xD315222F4527631AULL
        },
        {
            0xDEE91231C470035FULL, 0x27741C35CBA5360DULL, 0xA11A1B02C67D55C7ULL, 0x016B70F88A0792DAULL, 
            0xAAFF7EC121D8EED9ULL, 0x76B7567AF4C87E4EULL, 0x1F7836636D6DFD46ULL, 0xA3CD8E9655EE7929ULL, 
            0x93343831B2BFE2A4ULL, 0x658D53FE6B850A47ULL, 0x08971E91F01A282EULL, 0x8A7431DB9351AADFULL, 
            0xCE9A947B58498AEAULL, 0x0F052870428985EBULL, 0x908DBD71A00E86F7ULL, 0x15002D67950F7175ULL, 
            0xAA8AC7D98F7C9F51ULL, 0x2734AF66838A47ABULL, 0xDF4CF11B47FAC784ULL, 0xA26EBD6C0E117D77ULL, 
            0x43F0C66A902CE4C5ULL, 0xF73ED923161AA7BFULL, 0x63152EFE3C4A07E8ULL, 0x3CA5F82F65433008ULL, 
            0x6841212E2870DFD6ULL, 0x4B0ADA943D745775ULL, 0x8BAF6E92579703FDULL, 0x08CDF86684C285D3ULL, 
            0x711D6EF751CA1BA3ULL, 0xA6AF1F314615FAECULL, 0x341136FC08D59A81ULL, 0x957E84CE71E998DBULL
        },
        {
            0x8FCE2B006C8B1176ULL, 0xB9EB739F5347C7D4ULL, 0x89AE71FC184B7E98ULL, 0x69B3D3B715E1D99DULL, 
            0xFC786A623ADCC1B3ULL, 0x95EB0134A1071A47ULL, 0x0C0816F42869B8FDULL, 0x6E7B00E411E58CFFULL, 
            0xF6AB5B4170516F06ULL, 0x074F4A1237E7C54CULL, 0x7C49077E7B0A25B2ULL, 0xD6526B3ECFB29633ULL, 
            0x1FFE13C05B82062BULL, 0x883F50BB48EC4578ULL, 0xBC634050C5339E27ULL, 0x623F717979AFA35DULL, 
            0x9AB7203558DC7A1DULL, 0xEED10BF818DD4B11ULL, 0xE899CD4CC3EC119BULL, 0x75D927DCF6A943DAULL, 
            0xE469A47FE574F142ULL, 0x6DD3BBEC35837906ULL, 0x543E9CF2545F6DCBULL, 0x41C805A8A944B535ULL, 
            0x769F7AE535885F64ULL, 0x24454436A14CE5A4ULL, 0xFA3D5E60C3AE9690ULL, 0x4D7528ABF50F2BF7ULL, 
            0xF6ECE951D3544334ULL, 0x727A0BC1A6B9AC23ULL, 0x722E237E0CA2E91CULL, 0x24DCF042F377036DULL
        },
        {
            0xE2F78685E4ED8A66ULL, 0xB66F8147690EEB79ULL, 0x51EFFA7E0B9E7348ULL, 0xB6196A47F3C3F434ULL, 
            0x118A1C464133109EULL, 0x3B8D0ABAAE72B8D1ULL, 0x4711B5AE99CA857AULL, 0x8DF1BB09148C9AABULL, 
            0xC4394B90E16B2F91ULL, 0xBA68BA171891AA0EULL, 0x9DC460A541FB5499ULL, 0x482B87EF630AB531ULL, 
            0xCA60913C55F278DFULL, 0x00D3ADC99E11BA83ULL, 0xE992DEE7EBC2FB10ULL, 0x84441D2A8EBAEAAFULL, 
            0x7FF4D4BBBE4EC990ULL, 0x1E8B4F4F6524CCD7ULL, 0xE915A139C76BA8DEULL, 0xF3981C1255AB0674ULL, 
            0x3D98F409058734F2ULL, 0x47267FE02D31687AULL, 0xF54444E4F1163671ULL, 0x59D6A808FFF4663AULL, 
            0xDBF56DB4356FBCB2ULL, 0xBBD664487052C238ULL, 0x0B0DDFA78B7740A7ULL, 0x7E0896817C28271BULL, 
            0xBFBB637BC924721AULL, 0x7BA0D64F0985D152ULL, 0x5C51A08C3E4DDBD1ULL, 0x796C9A16DEFF5275ULL
        },
        {
            0xD37738F8DF598FB6ULL, 0xF1EEF05DD43A70AEULL, 0x8C5E1C6E6E18CE6DULL, 0x848B43F5B2CAA569ULL, 
            0x5A0C81499E1C7D60ULL, 0x2E9B0F5140FA7F58ULL, 0x788D66F07BEAF86DULL, 0x3EF8D0E9D91D68A3ULL, 
            0xB05618F4D53676CEULL, 0xEBCF748D99459B2DULL, 0x23157B5A84092698ULL, 0x61FA25ED61C12BE7ULL, 
            0x0B7DF9DB748FEB64ULL, 0xFC9311FED712AC67ULL, 0x270AB6CEC0ED604AULL, 0x069DEFB4D261276BULL, 
            0x64812C885C809CB6ULL, 0x57C81E4DE3E07605ULL, 0x848DE75222209E15ULL, 0xDEFE67CD90EF400EULL, 
            0x86C24969945C35EAULL, 0x973B23D6F2C95759ULL, 0xB5DE9F9674117FBDULL, 0x54CE962C51C98387ULL, 
            0x540275735E7FE984ULL, 0x254143BBFFF7D863ULL, 0xF2BA21F99D8E4C24ULL, 0x53D476273A50D2BCULL, 
            0x0C43069D52871801ULL, 0x8B02F55B70C1B392ULL, 0x94ED78CAB3B12C25ULL, 0x16FD887CB2C5DCF5ULL
        }
    },
    {
        {
            0x4927743564F04A5DULL, 0xBEA0D6AC405FD4F2ULL, 0x2866E594515247C4ULL, 0xB09E933640F80A61ULL, 
            0x6B613E8E6C45D543ULL, 0x5BF02849B544235EULL, 0x4C37B67FB59B7280ULL, 0xBE886B0610787829ULL, 
            0x0C98CFDD34A16A32ULL, 0xA5E16E475090C1BCULL, 0xD121A97F669DD2E0ULL, 0xFF0091BC99A8190FULL, 
            0x7BC000E852F06CF3ULL, 0xD7DA0C7FEA8DDFFDULL, 0x84360A2A237A2C54ULL, 0xB560838A88B27A99ULL, 
            0x5150CAF4FF21824AULL, 0x72E179AC57E13331ULL, 0x1752625917EDEFECULL, 0xC267470A7FCA54EEULL, 
            0xD7F8D14768B3A3CDULL, 0xD6E9B057D1237216ULL, 0xE30D7B051B08A030ULL, 0x37869A45A087F770ULL, 
            0x8B71D7DAD0381598ULL, 0xC969496A85202D51ULL, 0x75DF4474B51298D4ULL, 0x185A010526C2EB1CULL, 
            0xE36E1CDA71B56FBBULL, 0xB2B9711AD3C7990CULL, 0xCE6D843AA1D204A0ULL, 0x4AF4B9334C06B30DULL
        },
        {
            0x16BC816977C92315ULL, 0xC26AE371FF46C779ULL, 0xBC61EB33CD746E9CULL, 0x9AC56DADBB419D8EULL, 
            0x233C73D680D56530ULL, 0x34E8C2B8E3E9171AULL, 0x55D23FB75AB9E4A1ULL, 0x1415F9129AA77A3BULL, 
            0x253849C4A2FC3E8AULL, 0x75EB25C3701CE2A5ULL, 0xD956043CC501BDD8ULL, 0xF6DB3A42128DB525ULL, 
            0x96F059553FC31818ULL, 0x7B492078360AC602ULL, 0xB9210076533A24B3ULL, 0x71CA6166271BE8A8ULL, 
            0x297DBF8E23F1A7F7ULL, 0xB686080E7863D6DDULL, 0xCBC1D306791DCD9BULL, 0xEF0741C2B1499FACULL, 
            0x45F27FFA24D12D89ULL, 0xD20FD48DB920C02CULL, 0x2E5D6D3A93190E9DULL, 0xC431FA15BF7BDBE1ULL, 
            0x6E54673FC069829EULL, 0x40651285B157C43AULL, 0x82A6A126DE20DF24ULL, 0xBDB3909FD7BB2358ULL, 
            0x5CEE1725FC0CFF56ULL, 0xB2DA56F71C0A6B8BULL, 0x78151CE13FA6AF44ULL, 0x483063F469DA06B7ULL
        },
        {
            0xF4C7ED51046EA15FULL, 0xDCB69929451AC2D5ULL, 0xF9DA156B08485C0BULL, 0xB1761530DC240AFEULL, 
            0x14A632C96E5831F3ULL, 0x42763215AA5135F3ULL, 0xC0DD1B3BC87E2638ULL, 0xF214D457EA7F456BULL, 
            0xEDE55F9A4BE4A6B0ULL, 0x442FECFE86C9843BULL, 0x07279CEC34601E41ULL, 0xB299E77AF9425390ULL, 
            0xF39D1C043F477BDBULL, 0xC6B802C8A675DB3DULL, 0xB501EF5C9B771BB6ULL, 0xD2EEB0F051D23966ULL, 
            0x4B5659B69BE5B6A2ULL, 0x4D1E324FB44BB68DULL, 0x9DF0BD16F9FD8AF8ULL, 0xE46E2F5D5BD2A2C4ULL, 
            0x6E69951168782F8BULL, 0x5AF5C513380F9E5DULL, 0xD17CF5C3E2DB6B22ULL, 0x4A772A9C984D8011ULL, 
            0x813CA0673122E37FULL, 0x1E78E794A1C05E92ULL, 0xF10742FCC152FB3AULL, 0xD8606E39393BE2F4ULL, 
            0x961481C28237741CULL, 0xF3B5FA201E7C1C1BULL, 0x9B8A1EB84C3C963FULL, 0xF4F8CB0374848423ULL
        },
        {
            0xB5405A4AE7BA4E29ULL, 0x421354E975E915AAULL, 0x7F9A3D1B238A657BULL, 0xE0A0B93AFDBDF000ULL, 
            0x87F5705538DD2303ULL, 0x9E827F3085F2BBEEULL, 0x219458E2C22B9C71ULL, 0x12FEF223BA96497FULL, 
            0x3E6D92CA41E9A59CULL, 0xF3A13A85B2FBA626ULL, 0x5FE64FE476B2ECF8ULL, 0xF60EE54111D58E54ULL, 
            0x004F6742CBB3AD0EULL, 0x1AD25AC79960271AULL, 0xE3B34BC2DD0CB5FAULL, 0x8DE740DAFBB8BA04ULL, 
            0xDAAD39855733CEF3ULL, 0x82444BD752A3194EULL, 0xE4FB62884DD56542ULL, 0xD8038679043F4F11ULL, 
            0x42F3BC3E9AD65908ULL, 0xA2EE162982C4C556ULL, 0x307FD3462C5EEB4EULL, 0xA34D0D7A05C26848ULL, 
            0xBA26B7EC694C475AULL, 0xF7B6141232342A9FULL, 0x27C068B6093874E3ULL, 0x7F72DDE0996675F6ULL, 
            0x92FEBA46BFDBB049ULL, 0x03336A3833EB85DEULL, 0x0B756986B92FB740ULL, 0xE13431112670F6DBULL
        },
        {
            0x57DFED474E67A831ULL, 0x0B941FB577576722ULL, 0xEEED382C1BA025D0ULL, 0xC458A8936C885B8AULL, 
            0x94CC685E02580BA1ULL, 0x04997573ACA2F1E8ULL, 0x974AD17240E90C41ULL, 0x1042D653BAA6093BULL, 
            0x4D3D931328CAD963ULL, 0x54C56C12344C35A9ULL, 0xEB4754E701A3B60AULL, 0xF70016C31348A894ULL, 
            0xEC4B068C831C276BULL, 0x5D0BC8C4D040F6ADULL, 0x48FA580605F351E4ULL, 0xA67B0EA3EB8E74A6ULL, 
            0x973325024205559EULL, 0x0DD6EDE4CD93B053ULL, 0xDAE4AFBA98A10EA6ULL, 0x1B60A1A97B48395EULL, 
            0xD57213895A4D1418ULL, 0x1D6E437F646770A8ULL, 0xCAD8B17F5C926B7BULL, 0xFE900823677389E1ULL, 
            0x0A1F87EA4E98E5A8ULL, 0xAEF4BEDB11E9AA80ULL, 0x43E2024BF8F3BAD5ULL, 0x5BB67154F932C1D2ULL, 
            0xF81507EDE3CF76DEULL, 0x07F770F16B8F70A1ULL, 0x6E79CAB7FE781EDCULL, 0x159A45CABBD4A0BBULL
        },
        {
            0x19DC64A03152584AULL, 0x6E732996CC05631FULL, 0xA621F8D90D3F46E5ULL, 0xFCE2E44DAE378D35ULL, 
            0x83E02D2FEBC26E0CULL, 0x5BBB8344107E1AE7ULL, 0x37074383ACBEE02FULL, 0xE3D3E6938ABE9C1CULL, 
            0xAC811881387EDF94ULL, 0xB55CE70578D63CD3ULL, 0xF72F0D2A3343B84EULL, 0xFDD9167F447DA8D3ULL, 
            0x988A1B52C87945CCULL, 0xFC57785E4B1706BCULL, 0x2FAB7724130B4125ULL, 0x99D760C5AC8C7399ULL, 
            0x8898F6529E5C6198ULL, 0x83BE4D1F24B74C36ULL, 0xB5517E903471DF84ULL, 0x661CDC62FC8AC0A9ULL, 
            0x029260DCA83B6A18ULL, 0xB0FBFFAA423BD1CBULL, 0xA96FA9C547305ADBULL, 0x3F8461C7703864ABULL, 
            0x71B02AFFC3D9F4BEULL, 0xD85D2221CECDA63FULL, 0xA793B89ADC8F7FC6ULL, 0x47F3F99D1E6045D4ULL, 
            0x53CDEB0333650BD0ULL, 0x3D6AAAE5D56260EFULL, 0x4980C91C39FD8DD4ULL, 0xCF8313956D20A79AULL
        }
    },
    {
        {
            0xCC5C58C85414239FULL, 0x067308154EDF718BULL, 0xD9CE7052B1370E58ULL, 0x1E33E716DDA891C2ULL, 
            0xC2441F8F2E6E2FFEULL, 0x81847921A72FA54DULL, 0x9FF06A987702B231ULL, 0xCC300DA78DA103A8ULL, 
            0x89035217C74B79A0ULL, 0x44B0C9E7A05F99CDULL, 0x3CBB6BE0EE42F7E9ULL, 0xE5FE1BEB86B8577CULL, 
            0xE739C7DBDEF862FFULL, 0x1D7AC5B9779F0902ULL, 0x1F2FA4AD3D6B900AULL, 0x795428A9C8380E04ULL, 
            0x984A4CCA8F1A8AEFULL, 0x3D8313490A565573ULL, 0x36E84CCA5A596010ULL, 0x970FEBC447C25A75ULL, 
            0xFE09035CA51356F4ULL, 0x6FE69E8F68F239E0ULL, 0xB9F0B4706A512727ULL, 0x0BDA60A02C23263DULL, 
            0x8F32A1E713AF9E23ULL, 0x32BE80907466179FULL, 0x6C30D862083E8B81ULL, 0x4471BFEC96A2EE03ULL, 
            0x98D8992204BA655AULL, 0x9CA8B9CA9D84ACABULL, 0x7AA3DA9071D1A6ACULL, 0x32D376BE95246BFBULL
        },
        {
            0x50926EC80CE7E58DULL, 0xEB657531B4773921ULL, 0x8530925A3A0CB00AULL, 0x95CE53B4F0675CD4ULL, 
            0x66996C6FFEC2116AULL, 0xA4D10C7523E8416BULL, 0x6D6D279E163C3863ULL, 0x7FC020E5DF60D9A2ULL, 
            0x178645FC5225F4BAULL, 0x64D14D0F7A4FF01DULL, 0x131C5449500486CBULL, 0x2ED5A275C287EBF2ULL, 
            0xB487F438CC7618B1ULL, 0xC27D2C6EEF0771A4ULL, 0xA676579A2943B4CDULL, 0x2CC77414FAC7F93CULL, 
            0xE8A278FEA6B3623FULL, 0x079D3414F36CA07EULL, 0x1DA790E8047062E7ULL, 0x52328B7925FF2BEFULL, 
            0x6D002E4AA62A65EDULL, 0xA6669D1E55C68CC1ULL, 0xBE5148AF35E1CCB9ULL, 0xE81A3C33FB05C21CULL, 
            0xF8999005B527B6BBULL, 0xEB854E52669A4D29ULL, 0xDC993DD88FC3E35BULL, 0x7C561F3E8FD7E797ULL, 
            0x4D1568070A208459ULL, 0x07791814E7607457ULL, 0xB0DD8B1C5C90491EULL, 0x71158227D7AF3EEBULL
        },
        {
            0xC5AEB991ADCE8ED5ULL, 0x7934187C7C4BBA98ULL, 0x6CF459688ABEF336ULL, 0xAC3DD05479EE55BFULL, 
            0xE21ACDC92A8C87DFULL, 0xF0F922BF98523E84ULL, 0x446536CC99605642ULL, 0xC4C753F5F7C874B2ULL, 
            0x23551781F4631948ULL, 0x36353C8F7706723FULL, 0xA1C7C066FC4714E6ULL, 0x3B8C693B7BFA620DULL, 
            0x92BF6E0509F14427ULL, 0xC72FAF077B27D5BAULL, 0xB584F3E870443CD8ULL, 0xCBB0FD10F9628DBFULL, 
            0x6ABD83011D440BB6ULL, 0xC0FB52DA7FD97854ULL, 0x964412379440895CULL, 0x542E46EE283796AAULL, 
            0xCDC592CD79ECD6D9ULL, 0x3C5262FA38F47DB9ULL, 0x519E4657FACCD2C3ULL, 0x5DFB28B6823CCEEEULL, 
            0xF7CEA9D12EC86854ULL, 0x9B105CBD9BCBE22FULL, 0xFF150000018223A9ULL, 0x2C6AB855677231B0ULL, 
            0xC0E1B0DD3D2EBB13ULL, 0x033BFA6D6C9B2E34ULL, 0x2C2A2B6B5C1EB33DULL, 0x5F37B47C67F21CA5ULL
        },
        {
            0x70EB8DB98ED8FD6AULL, 0x10D03222394E0066ULL, 0x8E236DFA5D4BC567ULL, 0xEF087248D3815182ULL, 
            0xBF177D716EF3158DULL, 0xB78C5B3BAD1A5E46ULL, 0x0213D97E28CADA6DULL, 0x92657D3C5880D9B0ULL, 
            0xDF4C113668BA96D7ULL, 0x7D64B4A262025BF0ULL, 0xCD5615D0141195DBULL, 0xEE8058779AB1272DULL, 
            0xDDE45277B7F72D2DULL, 0xAF7F38BBB44F861AULL, 0x7846F67FFB8DAF6BULL, 0x0DB8513D90DF900DULL, 
            0xC2BD219565FF3A64ULL, 0xA44D562D83151B1EULL, 0xAF89F41F60F3A71CULL, 0x113250ED414A9393ULL, 
            0x8809E2588738E34DULL, 0x0BFD15710634F098ULL, 0x8082865A27C6AC29ULL, 0xC6DDEA91515CF9B5ULL, 
            0x1C7F93FDCB43A705ULL, 0x753D6C234078E6FCULL, 0xB742FE9857846B78ULL, 0x62113C668C8ECD1AULL, 
            0x897F03FF54589A8CULL, 0x6A38669EBEE60EA9ULL, 0xDDE56A11A0E7393DULL, 0xDF510BF242FAC21FULL
        },
        {
            0xBAB81A2541B34251ULL, 0x2F475C7E79B860EEULL, 0x18A9B52BAA2E8243ULL, 0x134712202D958AE4ULL, 
            0xC22642000BA8F0D9ULL, 0x597C99B7D4CA12C8ULL, 0x8B67A4D1625E27C6ULL, 0xEECDB7E030CA144BULL, 
            0x4AB025DA3DEA96E1ULL, 0x98A660BCDE1D3C0DULL, 0x855D6096FF0B1454ULL, 0x19D822C8A4983979ULL, 
            0x3B841DAF78550146ULL, 0xDD735ACEC5EA582DULL, 0x244444C8DFA85D3BULL, 0x1205F4924EEDBEA3ULL, 
            0x065132E549A94818ULL, 0x7F79FF30A041F5CDULL, 0x8844D99BF288260CULL, 0x1872304411843B43ULL, 
            0x6A5105ED4EB64AC8ULL, 0x0D9886F4AB8D18CFULL, 0x137DA92681443474ULL, 0x297C7DF766E5C1CFULL, 
            0x131B29E19723FE3BULL, 0x1AE884885361A9CBULL, 0x0FD8E264CC100012ULL, 0x70653FB8C43C5410ULL, 
            0x95FA5C95912E7828ULL, 0xFC78808DB95BD18EULL, 0xB47BE64307189220ULL, 0x8780F9B2B4FBD329ULL
        },
        {
            0xA62922A61A7570B1ULL, 0x52CDCAE0732C53A3ULL, 0x08789EE5096EDEBFULL, 0x7520016F6AD2D20AULL, 
            0x730746F6E909C582ULL, 0xE4E9D61875C71B57ULL, 0x0D96641FF1890ECEULL, 0x39AE4449BDB9554DULL, 
            0xC9F2144F80546758ULL, 0x644068A4AB5B3F13ULL, 0xB4F5CA358122E574ULL, 0xCFDAFB98CAD5CFC9ULL, 
            0x45B2BBF9C3BE65A0ULL, 0x1F5BA7F2EAEE28C5ULL, 0xCBAF1F13C58F6878ULL, 0x3515221046BB5DD8ULL, 
            0x5DF18E3BEE8EF0D2ULL, 0x2885C0B9FC00F6C3ULL, 0xD2B7EE598DB1C1C8ULL, 0x94B8C31707B1F97BULL, 
            0x5D76226E7251C08BULL, 0x8231FB2354B24693ULL, 0x5914BF8177E4468BULL, 0x97117AA6A7C9DF9BULL, 
            0x420A4E989A54722EULL, 0x5601B96ECA748EE5ULL, 0x5D2597BB95367306ULL, 0x3D0651FE71033F2BULL, 
            0x5FECE9886DF17EDCULL, 0x85E287EB2FD22772ULL, 0x551481F42025F487ULL, 0xFC543216ED4C4CA1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseFConstants = {
    0xCC5BBFE757A8D762ULL,
    0x0834906E455C262CULL,
    0x533AE7A6F1D7C76BULL,
    0xCC5BBFE757A8D762ULL,
    0x0834906E455C262CULL,
    0x533AE7A6F1D7C76BULL,
    0xF6F1DA0FBF1819E0ULL,
    0x327053389DFC5CF2ULL,
    0x99,
    0x0B,
    0xE3,
    0xC4,
    0x76,
    0x4D,
    0x94,
    0xE8
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseGSalts = {
    {
        {
            0xF93746BDD0D353B5ULL, 0xCC0AD5FBF382E455ULL, 0xDF55009F85E2542AULL, 0x02839A599BF60F35ULL, 
            0x3676ABE75C5A8640ULL, 0x84C2B25F07AE8554ULL, 0x94F790CC7B708C5AULL, 0xCCBD275C8EBD1DA3ULL, 
            0x9682D16DDB283F24ULL, 0x36E880D0A816191EULL, 0xEC94ADD672706E14ULL, 0x481474D9E5C4F4E4ULL, 
            0x27D3F96E0C88118AULL, 0xBC077334A3052502ULL, 0x5AFB23630DB9F5ACULL, 0x5AED5CFA626E4236ULL, 
            0xE4A462E7607A9D1FULL, 0xBB39B98D3C775B84ULL, 0x588C930324F71564ULL, 0x474F3FF3D6D8F0C7ULL, 
            0xDBB35C6FF1F36218ULL, 0x08BF270BBD019D7EULL, 0xB9367A2EDFF7B557ULL, 0x32BA930A2D3C63BEULL, 
            0x9CBDDC9D0CC323B9ULL, 0x2C13C45CDC86E844ULL, 0xF8C1DCB4DE76F943ULL, 0x45FB70A1E8FB3B93ULL, 
            0x01DA08AF72605403ULL, 0x441F1F62DDE60563ULL, 0x26BA01971D6DC986ULL, 0xA8C35712A4C5C6A1ULL
        },
        {
            0x53CB05633BF747FFULL, 0xA4D02E1142D7F1DAULL, 0xEB1295F5937884CFULL, 0xE9055A647962E447ULL, 
            0xFF35C2E855CA7FBFULL, 0xE308E19736FC5AE7ULL, 0x58C3A1F9DB1F1E3AULL, 0x81C0F3BD93B02622ULL, 
            0x695EC7EAB591FB95ULL, 0xF8EE577A654CF7B7ULL, 0x70BA49533B5A2BDEULL, 0x8B162ADF8E16DC9DULL, 
            0xA6AE9F1C4F17C3E3ULL, 0x9D5BFD01F7C60A9BULL, 0x3DA2F2BD67296990ULL, 0xA14F185ABA273F77ULL, 
            0x674FDE6BDED676EBULL, 0x0402DC330B029223ULL, 0x9AF53EBCE40870EAULL, 0x5E1CBCD3D4045C41ULL, 
            0x7CDBF0B35189C05AULL, 0xBCC7A7DDC3710B90ULL, 0xE872E1B9D7776B90ULL, 0x9AC85490C2980B0AULL, 
            0x6435C4437408293FULL, 0x2BF562EFD3A68DE9ULL, 0x34EF55402E3B4621ULL, 0x2DD3D5050A778E99ULL, 
            0x28F5AD7C6138E2CCULL, 0xF7C9678EAC00C4BEULL, 0x031889D422220FB5ULL, 0x4F6F2313CF604E14ULL
        },
        {
            0xBF970B1BC8227D0AULL, 0x449389C579A16E16ULL, 0x891E1BB840D29847ULL, 0xF82D703170772C31ULL, 
            0x5177B2FC5C1D22CFULL, 0xC25A586112D04E4DULL, 0x9306E8565E8FAA9FULL, 0xE48268EBC74FB780ULL, 
            0xF9AAC00F5AB62FD3ULL, 0x5EB87DF1E544D3B4ULL, 0xC6F5C286E126D732ULL, 0x968CE0616225A5CCULL, 
            0xAC1FEFBB33C666ACULL, 0x3CBAAB566288A257ULL, 0x55DFC90DD2335855ULL, 0xDC0BDEA296C633B1ULL, 
            0x529F801FFD918F18ULL, 0x99DFB3606F495BF7ULL, 0x33EF8A7C2B816D0FULL, 0x2179BBE9467ED782ULL, 
            0x8388AF2C47299230ULL, 0xED175A89B56AEB3AULL, 0x07182B800D2802DAULL, 0x11CB0CA5E289BD22ULL, 
            0xD012CAF49671D16BULL, 0xDE743DF33890F568ULL, 0xEA5E0052C69EF1A8ULL, 0xFC597F9869F7F6EAULL, 
            0x0A0F79AFC659FA64ULL, 0x91082D3525DE5267ULL, 0x3311B38E59C7887BULL, 0xF96D4CCCB9F2E01CULL
        },
        {
            0x373D05FC9363CBABULL, 0xCE2C2652DAABC396ULL, 0xA8C2463F66E861D9ULL, 0x9EDC2A7B4D6D9302ULL, 
            0xF83015316AA9E137ULL, 0x3717C8A4AF56CD64ULL, 0xFB80FF3A9C92385BULL, 0x3B12AD924DB571C7ULL, 
            0x5C2DEB754B5B03C3ULL, 0xB1EF93A00B6147D7ULL, 0x5F02C4F37547EB2CULL, 0x7172DFC1CE2E5D39ULL, 
            0x5477DE53BC0D5C7CULL, 0x3F6B38FEB85996CDULL, 0xA349425B46E4DDFAULL, 0x2338E96BDAE8E03AULL, 
            0x0B30443B325BCFA0ULL, 0xE31CBA4B0777EB6CULL, 0x14E993AEAA25B1F0ULL, 0xB3C33F92518EBFE2ULL, 
            0x5CDBD3E8E2416A9CULL, 0xBE5C752C58C416D1ULL, 0xFFC3234603400841ULL, 0xE655B4B90AFED77FULL, 
            0x737CD5B991E505FDULL, 0x4048BCCB34653BC5ULL, 0xF23C6C5B1EA781CCULL, 0xFB368A192C470E8EULL, 
            0x58863C77A42F066CULL, 0x2969553DDA32475CULL, 0x129BF900475D16CCULL, 0x074DBF8139CD3C64ULL
        },
        {
            0xD3E7EFF75563C69CULL, 0xEBA39B812B01BE77ULL, 0x666C548275F8482CULL, 0x99278A12ECB52410ULL, 
            0xA49B822B5A888F7AULL, 0x83B2EE18C7FA737CULL, 0x4E9BB85B960754B3ULL, 0x020A4762A6E2C16FULL, 
            0xB23C8FACA5F7E543ULL, 0xB202ABF9EF9B325CULL, 0xFFBCAA323E3D7263ULL, 0x4097A62B1E0AD4E3ULL, 
            0xD6293FFB241FEB59ULL, 0xBBEACAD727212B91ULL, 0xAC68E4C5008262F4ULL, 0xC0659A9955A4E2B2ULL, 
            0x894D50A04E1DCE84ULL, 0x4DA528025A09621BULL, 0xF5B3310621031DF2ULL, 0x1D5E5232AAE6FE94ULL, 
            0x6EC710D2300420F9ULL, 0xAB4364BAB886A31AULL, 0xD2E9662EAE382993ULL, 0x8AAFB1C56EB1A925ULL, 
            0xE10114CE0DD61F9EULL, 0x3E0CA50EEA4817C6ULL, 0x19957CF45C89E5B2ULL, 0xC4553655F7DC151CULL, 
            0x1740241E238C11EDULL, 0xB7D3B14BEC76D6BDULL, 0x41F478A91D5C3474ULL, 0xAD94F2CD949B4CB8ULL
        },
        {
            0x45AFDC97DA122ACBULL, 0x2DA876E18E33A26FULL, 0x573043F3190CD1CBULL, 0x492944553CE4E9CCULL, 
            0x0C7668FD5B999629ULL, 0x982C61EAF2A404F1ULL, 0x5D2C24D988F46DDBULL, 0x925DB16D35D45450ULL, 
            0xF87082CBA1BAE571ULL, 0x668730B9DFB7CC9BULL, 0x1ACF03E4B262ED0AULL, 0x7E7400D8D2FCA317ULL, 
            0x9D1F687AA49CD732ULL, 0x48FB9AEE0B56E114ULL, 0x493E0CA39CA16F4CULL, 0xF30B0C4A66D8FC00ULL, 
            0x54EFFC14225FAEF8ULL, 0x27DE663DEE45C12FULL, 0x76FAD72E05572C90ULL, 0x548B575FA4DEA53DULL, 
            0xAA56907A755F398EULL, 0x8332069DC8843EA1ULL, 0xA3E3F64B9549CF48ULL, 0x6A66CD7FDB6CE871ULL, 
            0x4822B76BB6C37E9BULL, 0x6AD5E77A671DA499ULL, 0xF96769812C19DA87ULL, 0x4A21ED7386128DE4ULL, 
            0x1AA59928E282F01CULL, 0x69E3445D4A0E6DAEULL, 0xD67B5E4135B3B49DULL, 0xDAB7D03A66491065ULL
        }
    },
    {
        {
            0x1DE7E8560A00B6E4ULL, 0x2FA2E2FEB2C4B668ULL, 0xC3F2EC7BD7A303EAULL, 0x23F4AD033B2F8CBBULL, 
            0x806E7F8D75B6641FULL, 0xF3872D7E3027EB05ULL, 0x8C1894AC6F3D2741ULL, 0x94D0E88B5130676BULL, 
            0x5F79C317D744881BULL, 0xA18AB186F931783BULL, 0x209CE68A47CB1D7CULL, 0x3DC99BE3F9838D55ULL, 
            0x22307B72045E6B6DULL, 0x167B2BAE4403ACE4ULL, 0x279E82860F1DD3A1ULL, 0xEDA86E9D171F9952ULL, 
            0x2ED69E43856857F3ULL, 0xA5F64BE59FDBCA20ULL, 0xB486A19D4B3485E0ULL, 0x55B3B5B6DF1F094DULL, 
            0x23E165BAA6667080ULL, 0x0EA3B22EA6E2AEF1ULL, 0x6A1F0B991A38A909ULL, 0xA76293F046B2D2D2ULL, 
            0xF0B45E5853A2A562ULL, 0x702333456FA90D95ULL, 0x95B9E6C2E9A21B59ULL, 0x94B841EB972A2059ULL, 
            0xC67832D105C0A097ULL, 0xEBF59864135014DBULL, 0xDA89282D2232AB08ULL, 0x7A7B63ACF71ADC13ULL
        },
        {
            0xAEFC1DB883A64907ULL, 0xAFAC096F4CEC5F2CULL, 0x7E5F28AADE134D42ULL, 0xA618F1F403BA4126ULL, 
            0xE1DDE9EB98BA0BDAULL, 0x2A439E21C933251EULL, 0x356E4FB4A02B7DD7ULL, 0x1FE8425B8205FBA7ULL, 
            0x11A0B0ACF85346E7ULL, 0x4D389A8B4CD9AC80ULL, 0x0AF77A235108B1C3ULL, 0x343B297160481BAEULL, 
            0x44A2FDC3EBB902C1ULL, 0x207065EC1442188BULL, 0x96F064100BA1E13FULL, 0xA2543BF18EC96DF6ULL, 
            0x0D4703AB16DEAFD9ULL, 0x53398EA655BCF219ULL, 0xDEEAF1D452C45B7DULL, 0xF97FE5828E9BAD42ULL, 
            0x6F739EFF8ECD0757ULL, 0xAEA2F9E0BEE94364ULL, 0x9F5545CF14CBFECFULL, 0xB22FD3F900CA5814ULL, 
            0x2AB8C098B3F0D98EULL, 0xCD5F892A1AC7B9B9ULL, 0xB23ECE200FF3F05AULL, 0x20B39C5CDEF2C508ULL, 
            0x773C96CEF9DC2CC4ULL, 0x51C01F4A295D164BULL, 0xD47CE5C87F140A04ULL, 0xE901F9F10C8EA9FCULL
        },
        {
            0x96251A0E7C765FFEULL, 0xF0428060092C872DULL, 0x9D43E2371499831FULL, 0x30D87C0B69F24032ULL, 
            0x2F784C37E9DFF024ULL, 0xF7C9A9BB6A88500AULL, 0x4A115BC5A0D65AEBULL, 0x5704A1C9592C694AULL, 
            0x2E6F2DBA236EB458ULL, 0x58664582DA4E889EULL, 0x2694B94871E482D0ULL, 0xCA4AF486DD6124D3ULL, 
            0xB3A7330D7376B508ULL, 0x77C30B21C690E40CULL, 0x6C77DDF88F6D5DEFULL, 0x7EB4E9C1DE10B08EULL, 
            0x3AA9B9B94E11863CULL, 0x2B6720A1779AFC67ULL, 0x22566A429E8E57D8ULL, 0x542B5CD0688850A4ULL, 
            0x9EA6EC980DD079DFULL, 0xF8F80E10AFF201D9ULL, 0x2F04AB75B479C748ULL, 0x9C0D496630C30DD0ULL, 
            0xF4824B3DB15EDCBBULL, 0x16CFFA8CB1826BA9ULL, 0xFF1BA75FA2699BF5ULL, 0x384BA2B74A31A1B5ULL, 
            0xBB81ABF99829226BULL, 0x31A6E03C6458ED60ULL, 0xE8C11E36F13E53D1ULL, 0xA6CA04BD14AC9697ULL
        },
        {
            0x81DF4E434CF39A28ULL, 0xD6D12C86A93BD6F0ULL, 0x7BDD008D3ECC4681ULL, 0x0DFF8E9211CF5E2FULL, 
            0xA0ACA30024CE29DFULL, 0x7CAE2D38891EDD64ULL, 0xD1B744CDAB7CF9D3ULL, 0xAC67BF35B21ABFA3ULL, 
            0x380F374674C47E15ULL, 0xD4358FE2F8D92E0FULL, 0x69A231A0D6320B30ULL, 0xEAFDBCDDF9A7651EULL, 
            0x2110660E28A00242ULL, 0x894C48FB7BBB23F5ULL, 0xA96588400A0E3A95ULL, 0x13B408E8139E6D95ULL, 
            0x6BEBFBC2722AA0E2ULL, 0xAAC571371215C798ULL, 0xDBAB00E0782163FCULL, 0x137DBF0FB9738688ULL, 
            0x4140794934733FC5ULL, 0xB09CBAD35BD7A06FULL, 0x4671C24E2F68B40CULL, 0x2A1E3B8B11634D7FULL, 
            0xAA2FD87B5B3AD0EFULL, 0x28994962B806BB3CULL, 0x7A8C630937E7298FULL, 0xB755512897C4F206ULL, 
            0xB7D290AED1844D6AULL, 0x877658DD78113878ULL, 0x1B9C0C15F505E7D8ULL, 0xAEAF58F109EBC8FAULL
        },
        {
            0xE75FB8D4CB0167FDULL, 0xE2B7FE2FFBAF8D95ULL, 0xA0F54F586A1F495FULL, 0x7D3A6F978E9BC158ULL, 
            0x670E546023959BEEULL, 0x25B40E9C190087AAULL, 0xA3D1C7E7D671FBBFULL, 0xB42800B621C65051ULL, 
            0xE4BB2DA9EB812683ULL, 0x1C29799E51E7D8FDULL, 0xEB87F6BD04BD4025ULL, 0x8A437A168D84A542ULL, 
            0x05F613E3B5A47301ULL, 0x19E868DE28E4871EULL, 0x586646C066190286ULL, 0x9BB45FA0E166EBA0ULL, 
            0xE5D2BA7A3DB1989DULL, 0xA49EE52B56A5ABEAULL, 0x23ED8660053C7209ULL, 0xD7C666CD849D6620ULL, 
            0xF372E1E811660B15ULL, 0x94D5AF937CFD3DE2ULL, 0xA970CEF7605BF250ULL, 0x1835E48753919995ULL, 
            0xEC0C38F44EFD4157ULL, 0x87B58DEF57FDC73EULL, 0x1C9ACAC39DE6206CULL, 0xC41E3B37EF64E05BULL, 
            0x94DEC5A2098ABD54ULL, 0x7BF1E65606371DBBULL, 0x04305F79E454AB42ULL, 0xE3A90405CB4EF907ULL
        },
        {
            0xDFCF85E89FAF710CULL, 0x3D7FA761CC5E09ACULL, 0xDE9EDDA7AD73ED1DULL, 0xA65E2AF9AB0C7ED9ULL, 
            0x3EADD4F5E0574362ULL, 0xDF95865949415BA9ULL, 0xB0B8FFEBB46CD0FFULL, 0x91BF02EDEDDEF8B5ULL, 
            0x0977EE2DDC71DDD8ULL, 0x3F5366184235D644ULL, 0x3D1CAE27E2296EA0ULL, 0x997B45CEBCBBAF50ULL, 
            0xC83C0516C7C5BDC6ULL, 0xC647E9B94CE6F0A1ULL, 0xED236CCFB122D3C7ULL, 0x30865E01021C73E6ULL, 
            0x44387990CB1E2284ULL, 0xD3604F35C4EFED48ULL, 0x940A72F22A472F1EULL, 0x91C80783305164BBULL, 
            0x3DAA55CCB789EAAEULL, 0x8BFB16FEA4FCB3D4ULL, 0xE9BBA5CB8FAA4BB4ULL, 0x45BAD25B72CD0E31ULL, 
            0x3DD089C9227023A6ULL, 0x498AA2A47D45B493ULL, 0x74F4E17B4EE26794ULL, 0x743C84AD3979FF8BULL, 
            0x3495552E2260FCDBULL, 0x81B67F9F6E1D193BULL, 0x32D2110D04FB350EULL, 0x36E06808F639AEA8ULL
        }
    },
    {
        {
            0xA9E1A708ECA25FFAULL, 0xA6F1F7254B271035ULL, 0x737F77D162AC6703ULL, 0xBFBD9A4672D482DBULL, 
            0x2958738393BBF675ULL, 0x00E1F46A1617702BULL, 0x47EF1625701F0F1DULL, 0x0929D1012F96B0E5ULL, 
            0xB46C2FD2B6D2F3E1ULL, 0x7BE2050CD1F43E94ULL, 0x7F34CAFB879E9274ULL, 0x5E0AF11D1F379F1FULL, 
            0xC2070A95D91E224CULL, 0x3AB3517F72ECBDF6ULL, 0xE698F1B5E24DE00FULL, 0xF6196DD780D21624ULL, 
            0x8D0EE480E7F44DDCULL, 0x0CF7290D87A2CC48ULL, 0xCD35ECFED700AC88ULL, 0xF66CF3232B58D228ULL, 
            0xA171F473AB5FCBACULL, 0x7ED5E23D2699B13AULL, 0x2F8CFBDCA94F5FC8ULL, 0x4262CFED1C1F58C4ULL, 
            0xB6AE9FBF6A11433EULL, 0x03FCFDC363E2564DULL, 0xC388C54CC5B9B597ULL, 0x8E68D6864EB1E3DCULL, 
            0x3CAE38B20305B279ULL, 0xA69F3CEBC5F679C6ULL, 0x0EFF50F8970C301EULL, 0x51594AD5A6EC6CFAULL
        },
        {
            0x4D262F1B5366CE4CULL, 0xD2C7803EE171066CULL, 0x2759B67C0E9BB6AEULL, 0x5F4A524D1BC9693CULL, 
            0x045135970781CDD1ULL, 0xE0EFE453BBD2BB92ULL, 0x71C8DD73C2E8E130ULL, 0x44CCD2BD5DA6F7DFULL, 
            0xDFB6A21A20200EEDULL, 0xB99A532B2FB95A13ULL, 0xB1A79E2FB13D20B2ULL, 0x76AB853F3ED8FE0CULL, 
            0x86F6E117A836411FULL, 0xAD18435FCAC216D3ULL, 0x6F9C8A3D1E0349DCULL, 0x8AE8535DE9FAF203ULL, 
            0xBF677865993BD68CULL, 0x7B1F536ACC7F3A4CULL, 0xA7AEF0324A31E402ULL, 0x501C3EBE3F6BF410ULL, 
            0x3C498DEBA0FD50B7ULL, 0x50485FCB3DC1928DULL, 0xA9EFBD6083856F8CULL, 0xE075017F4F996791ULL, 
            0x8564F5A77336E441ULL, 0x4F3B6C0A15D1D9E7ULL, 0x4944E82BF52B95E2ULL, 0x2C61538B33EB4A3CULL, 
            0xE709F44A3C245812ULL, 0x60951D3D7D0C650EULL, 0x13DE9A3C07353CDBULL, 0x4A2D07F6EA055FD5ULL
        },
        {
            0x311D29530E80FC59ULL, 0x238256CF1BD62591ULL, 0x89EE939DE6ED0607ULL, 0x307A1203FA890951ULL, 
            0x1FFE48246410803AULL, 0x0CCAE551F65C9064ULL, 0x199B7B931327242EULL, 0x6EE74DB773BF3FB5ULL, 
            0xC7BC86666CD69F1BULL, 0xEAF5142907A88677ULL, 0x9E27A88CC8910BE6ULL, 0x2FA10DF9CF35AACBULL, 
            0xB5CBAC79822D44BEULL, 0x06BCEAF92C3BA8FBULL, 0xDA0B28D403EFCC6DULL, 0x2E9E685D664236C0ULL, 
            0x4FAE761DF4C229ADULL, 0x9B1C80DF43949C06ULL, 0x85A8D1B526523B29ULL, 0xB50450C8B06FE800ULL, 
            0x0F21CE91E58A7E96ULL, 0x78023FFCA5264334ULL, 0xE36D315BF2F8781FULL, 0x3DFB1FD090C3ED26ULL, 
            0xC7A289140D6BA4B3ULL, 0x51198A4BE73D2AB5ULL, 0xC7AB316C51EA90C7ULL, 0x7CA6ED573B173E14ULL, 
            0xD6859C217D7889C0ULL, 0x011C25ED770ABE55ULL, 0x60B40CD874C0FB6FULL, 0x3A2C8275FE07A41DULL
        },
        {
            0x487B681C69653BD8ULL, 0xAD47F0DD2C2E2BC3ULL, 0x6A5B0EE36F66693CULL, 0xA8B5F7F7355AF9C9ULL, 
            0xA5201DE1D0E85304ULL, 0x8539F52A4BE95439ULL, 0x72C8E32848D161BFULL, 0x7DD56858C2BE5968ULL, 
            0x70D3CB4C88C18585ULL, 0xD0C15E1CBCB3847FULL, 0x4D3AD3D23F974BA8ULL, 0x55B90D531C7B7A83ULL, 
            0xD6ED4D0E79B0F732ULL, 0xF35AEA6AFCC58D4BULL, 0xAF6496FCBF515F2CULL, 0x4B63E12FE6C40BA8ULL, 
            0x199A398177976834ULL, 0xC01CBE50E14CD0DBULL, 0xC10DCA375B890CD3ULL, 0xBC716CD5BB613EE6ULL, 
            0xD9F05E299DECE256ULL, 0x9DBA4651F94D5B66ULL, 0x8CD002417E19351AULL, 0xB4B9EF5C476200B7ULL, 
            0x0E51D1172A042A8AULL, 0x603F71EE313F9935ULL, 0x01BF949875D798ECULL, 0xFA5BCE4DAD1E1FB5ULL, 
            0xFAFAC190E962B1DFULL, 0x035A1D5C86FE01C9ULL, 0x04EE77B924A6D5B1ULL, 0x851E10A98F685DFFULL
        },
        {
            0x61D429F843C8D764ULL, 0x3BF12E831E9D50C7ULL, 0xE710F3D75326969AULL, 0xD3B63F74136AB5E0ULL, 
            0x0D5F928C172FFB22ULL, 0xDF386197B95EF4A8ULL, 0x5B97DEC739A3D2DEULL, 0x21F8F44A10DE3502ULL, 
            0xF3EF4CCD16546778ULL, 0x93B227AFE1B0D315ULL, 0x745D698156C45B58ULL, 0xD5AE4FC1998A0C67ULL, 
            0xA37171F511CB12CEULL, 0x28DDA60485C79E72ULL, 0x6FB884188AEB863AULL, 0x221C3DD68D0B802CULL, 
            0xFE4254E71F30DC79ULL, 0x78EB8A82B4E6CBFBULL, 0xA2B9F9832433B7B5ULL, 0x279FA0B3F3B5D936ULL, 
            0x97472A8AB4FB8E53ULL, 0x3AD591461A6DE1E5ULL, 0x9778FE0DA3DF5BA7ULL, 0x6B5537D1415A176BULL, 
            0x1249384F8A055987ULL, 0x820ECF959F4E33EEULL, 0xA925B17021048A6CULL, 0xCB42C34E9D6E6CE8ULL, 
            0x0083E9BC49F2FF2EULL, 0x01C43B9BA6AFB856ULL, 0x4CF0A29FBCF1BEECULL, 0x7352B335077D9D67ULL
        },
        {
            0x13D185A1AA1410FFULL, 0x24AFB2BCA84CE24DULL, 0xC858737AEADA777BULL, 0xC8B8CCF0006A63FAULL, 
            0xB5DE02096F932A5AULL, 0xB514E477CA0CB46BULL, 0x71E149597CB781D7ULL, 0xB806DE7E691A15AEULL, 
            0xCC4C5DA3108899BCULL, 0x5EE6D5C3C98700A6ULL, 0xA578295706D0457AULL, 0x1EA88C705AA26655ULL, 
            0x5B25831C90AADDFAULL, 0x33F51468F6F5E67BULL, 0xEDAE986A46DA6F69ULL, 0xC3870AEB60BB1F69ULL, 
            0x8F308EC41D5E7F69ULL, 0xFE75BE03932AA398ULL, 0x037CBA08BE347149ULL, 0xF1E00A51224092D5ULL, 
            0x54B9735FA5A30F5FULL, 0x34591E4FE2AD76D2ULL, 0x5E606050C4A5CA85ULL, 0x9676EFB1F3F85586ULL, 
            0xB97906DAB44B7955ULL, 0xF289FC28A78F7822ULL, 0x3770C9E13BDF1320ULL, 0x5EB0F0609E0B7F4AULL, 
            0x4335E313410CF9B6ULL, 0x7EA27F5EF70D8AB6ULL, 0x75216032EA068CA7ULL, 0xAFC73356C0160BA0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseGConstants = {
    0x3AEE794B969D881AULL,
    0xF470E8ABD926C905ULL,
    0x4A97B3EF5CFA3082ULL,
    0x3AEE794B969D881AULL,
    0xF470E8ABD926C905ULL,
    0x4A97B3EF5CFA3082ULL,
    0xE328D9B24F72437DULL,
    0x78B97CC88A901AF5ULL,
    0x12,
    0x55,
    0x03,
    0xF8,
    0x2A,
    0x78,
    0xFB,
    0x0F
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseHSalts = {
    {
        {
            0xEC4809642C8F9388ULL, 0xFD322F7F8363AC03ULL, 0x13D8B2181D77BFFCULL, 0x87A9A7A58D8B85E4ULL, 
            0xEF12233FC945CF33ULL, 0x08C4A6E74F5E1AC5ULL, 0xEEB8E00776C77D12ULL, 0x3C75F75F281F9812ULL, 
            0x26F0ECA852337F7BULL, 0x9F32356CF4439555ULL, 0x2F41B9C7AEA0C292ULL, 0x90C25486C8E72F0DULL, 
            0xAB767270EFA6EF5DULL, 0x4BFB6ED6FDF83FFCULL, 0x5965E2251A3CCDC6ULL, 0x0421F19ECBF552F2ULL, 
            0x07C6E7845F60A280ULL, 0x40A560EF577B6962ULL, 0x659BC61608F89A63ULL, 0xD27B7C1E46153102ULL, 
            0xFC0BFEBFF358BD1FULL, 0x62681C2913A250CBULL, 0x746499531E139AC0ULL, 0x98A1BF1A766698F5ULL, 
            0xB041A1D722A4B276ULL, 0xD641D877EF732A45ULL, 0xAD27918002C49E62ULL, 0x64DD9EBEEE0B83DBULL, 
            0xCB28619F524DC544ULL, 0x0B5EEA792764ACE7ULL, 0x53B4B8A6D3688653ULL, 0x6BFBFB32B0B333D1ULL
        },
        {
            0x054E53C5671E51F5ULL, 0xC697B5FAB6D380F0ULL, 0xA1CF4E36D227ABD2ULL, 0x26F8D64E01D506DCULL, 
            0x9425A5E8FE151273ULL, 0x1EF8238BB239B096ULL, 0x7F886FFED81326EDULL, 0x16F3F7932C2DC89AULL, 
            0xEADA352DA0FE778EULL, 0x6329F27B3BE9C115ULL, 0x484765041729BC9AULL, 0xFD1F7204503CE66AULL, 
            0xBEE9812F8E1B28ADULL, 0x99C1E2DCC1E3F640ULL, 0x6B282B3C65ED4F58ULL, 0x11370E007344130FULL, 
            0xD43D2819F3529604ULL, 0x0BD51696B22958E4ULL, 0x4562CE16EF69BBAAULL, 0xC28756D923ACD973ULL, 
            0x49C481595912A1BEULL, 0x85BA31895346971CULL, 0x55F1AFE3DAC8983BULL, 0x5D128191E55A5E43ULL, 
            0x8A578AA681F0A946ULL, 0xBB6168716C5A0EEFULL, 0xF5897D1B8FAA19CBULL, 0x311DEB4D8B7F9344ULL, 
            0xC9E698C9B8C4EAC0ULL, 0x2E491BF0C0850509ULL, 0x62CFA7E1620FA9F8ULL, 0x7BECF60677F46B6EULL
        },
        {
            0x9C1CD657EBB491F0ULL, 0x581A951E5F28F17FULL, 0x61ABA0DB918676EBULL, 0x8D1B0C9DBED1CF9EULL, 
            0xEF64E6EA7825BE7BULL, 0xC084CC4938543ED4ULL, 0xA33154CD3197EA9FULL, 0xD8941D3165370800ULL, 
            0x1E06EF5B3242E44CULL, 0x8F8F9B6E2374B4C5ULL, 0xA71B42ED5E2E6DA6ULL, 0x5B132C3252E4D588ULL, 
            0x1B59E8FD669DA6A1ULL, 0xD83EFB22A587BE6EULL, 0x5A1B257D0FAA97D6ULL, 0x9E906BB690132FB9ULL, 
            0xEE80944A50242B74ULL, 0xF070588848FBB158ULL, 0x4681DD1D70955831ULL, 0xBBE4B14A18083EC0ULL, 
            0xF44FD26083E7671FULL, 0x6DB6CD547E41024BULL, 0xD936B7417E7141A1ULL, 0x82ED71618CEF7749ULL, 
            0x8193CD9D21BBE026ULL, 0x370ADDF98E9CB4B8ULL, 0x33BAC25673B5F08BULL, 0x5CD8347CFA95BF27ULL, 
            0x07A59459762D86B5ULL, 0xCD3036BBDA1D0BEDULL, 0x5D7F6C268416D6A3ULL, 0x8169021E6BA7494FULL
        },
        {
            0xA2DAE75C43E07BCBULL, 0x7F13BECC58546E05ULL, 0xC19B6274C0CC7800ULL, 0x3D24A81967FA8ED5ULL, 
            0x8A6F23F81F47E554ULL, 0xA3BA754B9539E819ULL, 0x31D39C71B4962E58ULL, 0x486CAC65AACBD6DFULL, 
            0x726F641571F11EBDULL, 0x9B02E660DD0B4125ULL, 0xD062D4CAC2324601ULL, 0xF12C4264D7688D51ULL, 
            0xFFAF4C0CFE20A998ULL, 0x6F0A7F4F4A359098ULL, 0xB83C0C57825B480AULL, 0x3205D1931E6E71D5ULL, 
            0x55481A071C15436EULL, 0x4543C6D50A92B990ULL, 0xEC13DE34CDE413F0ULL, 0x134F8E615B373767ULL, 
            0x230FA199F361E14BULL, 0x45CC91B127DCBD29ULL, 0x2BAB786E98E86203ULL, 0xE9C8307F34D70B0DULL, 
            0x6C2A287B72CA15A8ULL, 0x95F2DEA05594B553ULL, 0x72F84B013B272CA3ULL, 0x61A6EC821532F1C2ULL, 
            0xB8536C1F250465C0ULL, 0x2F490394E275E6F2ULL, 0xFA44F37DF7F817E1ULL, 0xD492D7375F5FF4DBULL
        },
        {
            0x4ECBADA7A3C58A83ULL, 0xEA38CF0270BB7FE1ULL, 0x76A586968E3765B8ULL, 0x06399B0927733FC8ULL, 
            0x1C177D48FCF295D2ULL, 0xCB327AFBA14F3F8AULL, 0xB7651D78B480DC9AULL, 0x22F3F73410319807ULL, 
            0xD2C889BAB9A7B934ULL, 0xDBB3B5459F5C9A80ULL, 0x0EF7E46AEC17F597ULL, 0xEAF115AE84EE23D1ULL, 
            0xCF8C8B682F72ACF2ULL, 0x75532F065E4D231DULL, 0x7F380E147C69BF17ULL, 0x37DF1FB6C48DA092ULL, 
            0x0B3853D21B24E6CDULL, 0x6B0D8D9A96BBAD33ULL, 0x86E45DED78F2735BULL, 0x9D9D3C161747B3E6ULL, 
            0x73FD07F6E99D6259ULL, 0xAE1114054FB3F2B6ULL, 0x14F1C5F9B423133EULL, 0x2180875093A02063ULL, 
            0xD4C133198D19A31BULL, 0x1376138C82EB270EULL, 0xAB22F22AAE93278AULL, 0xCE202F977F7E407DULL, 
            0xC6017A6F2DFC3546ULL, 0x20655DE0D8F82FC1ULL, 0xFF7461B85A9C87D6ULL, 0xF45B19A2489AFD13ULL
        },
        {
            0xBB07FFD3970AA2CBULL, 0xAC2EB9FC757CCC8BULL, 0xB5385EA5287C5CB8ULL, 0xCE0FCC926CF36054ULL, 
            0xE39D066620DAE523ULL, 0xBB021146761A3346ULL, 0x73EA8E621ADF08E5ULL, 0xB4D7D017A0194677ULL, 
            0x852954F5E678788AULL, 0xF19F154AF5917011ULL, 0x1B03FC548CAAD3A3ULL, 0xE22708FE4E176469ULL, 
            0x923BAA9FFC65AEA6ULL, 0x72CACD3286CE8D1BULL, 0xBE3B22155B40C266ULL, 0xDB4D5F185E203E4CULL, 
            0x218F6F0345F731EEULL, 0x8694FDBA9384F27CULL, 0xED076617CC341621ULL, 0xB04B4EAC7F85020FULL, 
            0xF10418BF0B6F3935ULL, 0x74173ACD1A39FF28ULL, 0xABD1C596E0B3F215ULL, 0x9D0EE5FD130D772BULL, 
            0xE508FA840B950EFAULL, 0x0E757A1BF9A54F20ULL, 0x71371221F51F041AULL, 0xC0806CB0755EB384ULL, 
            0x91F6FD96E63D3708ULL, 0x6DA58710E72427D6ULL, 0xB916BFDAC2CA9F1CULL, 0x6E8CC842C21A1ACEULL
        }
    },
    {
        {
            0xA5866932908E93BDULL, 0xC49B662746740F82ULL, 0xCDBE97C3D54E841CULL, 0x461200F6F5CAEAA2ULL, 
            0x7CAA72E07119B90FULL, 0xB34D90AAD0A12516ULL, 0x4A846EC3A811BC5FULL, 0x0FCA2C798D908361ULL, 
            0xCC5C2E663FC8DA3CULL, 0xF5ED95C86D28D4CEULL, 0x6F5B10B38B98A895ULL, 0xA70CE79B5CB98D4BULL, 
            0x51ECF7F00AEBAE92ULL, 0x12962D962328B531ULL, 0xA275C3D3188DC3D6ULL, 0xACF8434D81474708ULL, 
            0xE9D2E3624D2A71C4ULL, 0xC199AB7C3D7CAE83ULL, 0xAAE44A8A48FD457EULL, 0x56DE8DB8A14BDC5BULL, 
            0x4696B9C48A9DAABCULL, 0x74BAF4FD7009CA9BULL, 0x12DD5F37AE0B0031ULL, 0x39F2C8D50161378FULL, 
            0x22E8CADBB28E7A24ULL, 0xB92E0ACB7DC3A874ULL, 0xCFDBDD857327E11AULL, 0x0F874A67502A000DULL, 
            0x0B1366DC2481388CULL, 0xD7CEB033B681E1CBULL, 0x5CBA8E32767772C5ULL, 0x217992640431D7ECULL
        },
        {
            0x1A331E548F0AA224ULL, 0x7BF4E5D1D854D475ULL, 0x563492B09DD02ADFULL, 0x3C8833822D3FD0F6ULL, 
            0xF1E54A1C4A1BC0A0ULL, 0xBB8DBCF9CA90ACBCULL, 0x343BEF4631D0BCDBULL, 0x0474FCC9D038CB3CULL, 
            0x5B2E06C6FF7C108BULL, 0x3AE23B04F775DB3FULL, 0x54140B7D066D244EULL, 0x5B1B9100C3D656F0ULL, 
            0x153E3BA29BD2EC15ULL, 0xDDEC153891F42E37ULL, 0x095635769731061AULL, 0x0CD99D80DAA1A690ULL, 
            0xCDE7108A9E8646EAULL, 0x2A3AFB8B103A6AACULL, 0xF8ED7DF4016823FBULL, 0x5F4C99B9709F8347ULL, 
            0x9EC571F086867DADULL, 0x7221F3EA0237D1EDULL, 0x1228137515D238C0ULL, 0xCD49A387EB9F01E1ULL, 
            0x3B2E3446F947207AULL, 0x255DE864F7C16AB0ULL, 0x4E075E8733E78C56ULL, 0x7FE05188EBC44F36ULL, 
            0x918977238E409E3AULL, 0x8D7E52078A216854ULL, 0x2C68FE2B15353CBDULL, 0xDD07E1D049F9CC5FULL
        },
        {
            0xE1B78076304004C9ULL, 0x5DE3D3AD8AB2925FULL, 0xDED6CA45F9671F0CULL, 0x2A89015C6607A6FDULL, 
            0xFFF7C12D88A9EBE4ULL, 0x350FFF237E3CC27AULL, 0x90C805D5F1FAB9D1ULL, 0x64347B819C734042ULL, 
            0x526CEFEE9CAB985CULL, 0x3B4C248AEB527583ULL, 0x902228BE129B765FULL, 0xCD7BC194D3D39F70ULL, 
            0xDFAE04635AE4671BULL, 0x29393F7E2657AFB4ULL, 0x2938917E54E61915ULL, 0xE1FA1BD4AA15770FULL, 
            0xDDEF05B3FF66AF18ULL, 0x484BDB67C361F03CULL, 0xB3E41DF8D2FCE4D8ULL, 0x3D54866C8CAB5180ULL, 
            0xB9E6D77BED2204D8ULL, 0x450B78A63BBF23B0ULL, 0xBCFDA3EDDB619ABCULL, 0x03D01892BD2B4C77ULL, 
            0x9250237D1FF479ECULL, 0xA02AA5720E062CBEULL, 0xF36C1BBC96414803ULL, 0x7E6F81640AA154DAULL, 
            0xCE9E07933CA6B1ECULL, 0xDAEB13B65DA15E0BULL, 0xE65F30D07C9B5945ULL, 0x605032EE741F8DE5ULL
        },
        {
            0x69A6B811E05ED097ULL, 0x2F321E31FDEBF3C1ULL, 0x480A98C45F09640DULL, 0x9E6B06DBDA87C8BAULL, 
            0x2BB2E30D14CD1D85ULL, 0x8E7B745A49A9B7C9ULL, 0xE9DD6A58CF67AFCBULL, 0x97F4AC6B97CDC063ULL, 
            0xA810B8A0A45C98EFULL, 0x9E08DF5E27F71EBCULL, 0x1A7EB6057BB40A71ULL, 0x4D5F898A65F8472AULL, 
            0x4F35B53353F085BBULL, 0xABE8B13B006B56ABULL, 0xDF70193AAD4F1149ULL, 0x7A874B01BB545CD1ULL, 
            0xBF01D0F52C72898FULL, 0xD3AD7AA876FDF297ULL, 0x579EF6BE6646C8E8ULL, 0x2BB4D12EB95D3B05ULL, 
            0x3A69BA7395F0F266ULL, 0x2D96E0D1046B04C7ULL, 0x935B4F540635FB96ULL, 0xBF8A7682A8967D77ULL, 
            0x651C41EF8313E770ULL, 0xF4303BD543522C13ULL, 0x3CC669D4D850EDF0ULL, 0xA21757147A34ECFBULL, 
            0xDC18C5FFF6439693ULL, 0x4511734EF1F83019ULL, 0xDE1E961D5C305B0CULL, 0x5412516ADC2F1A0CULL
        },
        {
            0x99BCF405D4A15DCDULL, 0xA33829A9E740B972ULL, 0x10B5836460164496ULL, 0x7F6F1A877F41FC3FULL, 
            0x02422416882EC29AULL, 0x782E2B533947C6CBULL, 0x77370641E1889E1FULL, 0x95086BBE5DAABB3CULL, 
            0x4B2C64AB21C72DC1ULL, 0x5991A690ECDB71DBULL, 0x0422F04B8D8151D8ULL, 0xEB255D55E24C1ABAULL, 
            0xD2A11818F804F0F8ULL, 0xEA8D25D45181BB0AULL, 0x5BF37F733C16D878ULL, 0x9F42C8194FE7EE19ULL, 
            0x7FD9B42BC8718A33ULL, 0xA444F32E897F794BULL, 0x155C78BBD854E04EULL, 0xD94667884BF98857ULL, 
            0x7CED74FB8371C0FFULL, 0x210A4E0911A2E923ULL, 0xC4DA8C0BD38641FEULL, 0x532FC8C144DB25C6ULL, 
            0x8AFDC8B74EE5B545ULL, 0x2248E77E497BCF2CULL, 0x9CD9DC6AF2881947ULL, 0xA4B40F47BBF3DFE7ULL, 
            0x5B091B8085A4A6A9ULL, 0x0242D1D36A723F76ULL, 0x505AC49DFD94A123ULL, 0xD82619D347E3E751ULL
        },
        {
            0x0931D37F9081EB67ULL, 0xC0D402E908F1E700ULL, 0x2D9E5A335F77567BULL, 0x288AE3FABA6E5BA1ULL, 
            0x89DD7E7F1D048755ULL, 0x65C7378CB42CCA74ULL, 0xC765AC7176EA8E28ULL, 0x2AADDEB3EDE94DBEULL, 
            0xE817F4776CCD5943ULL, 0xE54011207D05D94FULL, 0xDBF4734293E1EBF9ULL, 0x9D080B2B766E17E6ULL, 
            0xFB3A6E530D03EA88ULL, 0x683438FBB6E13BE8ULL, 0xC8E1F385581F5E0AULL, 0xEEE105704F70235EULL, 
            0x79BE8C1E3788E5ADULL, 0x958E6091A7D19001ULL, 0xC45A2249C4C29F4AULL, 0x8D24C52C6CD6A699ULL, 
            0x52EDF7B371D6615BULL, 0x1E26F3B261A7D0B5ULL, 0xED763036C311794CULL, 0xECD408421226FFC7ULL, 
            0x2C265A8A02EEA53EULL, 0x1E662A13784894A3ULL, 0x1205DE3311A8EE1EULL, 0xC913E5133311A6C9ULL, 
            0x761509A511ED0FE5ULL, 0x63079D45D89699E4ULL, 0x188F49ACE8D5928FULL, 0x2424CDAA2A197B68ULL
        }
    },
    {
        {
            0x30C0DE6BB3B501F2ULL, 0x77035230836EAB8FULL, 0x919D586AA7F446BEULL, 0x85C765919B133412ULL, 
            0x3A0C2861742DFC7EULL, 0xCD76C4F8C7E063DCULL, 0xB71B45C865501E30ULL, 0x54992C1181B334D0ULL, 
            0xEC77F1884DA4ABF8ULL, 0x7C4ABE13D7C2B1CCULL, 0x2BFF10804719976DULL, 0x61FFF235018EFCD3ULL, 
            0x6480568EED45967AULL, 0x4BB54D28FCD9AB07ULL, 0xD7196EB6BBE36815ULL, 0x584AED898DD16525ULL, 
            0x9BF71A10CB2F3B83ULL, 0x6D3A8FBEFC5DDD1BULL, 0xD7826C44F6D0F978ULL, 0x9FE059372EF9CBE8ULL, 
            0x8A1D0FC1642622ECULL, 0x65054390A8F4B1FAULL, 0xAC4DD9727870649FULL, 0x303C52D85F35BF52ULL, 
            0x85669EF02E5C69C4ULL, 0x42BB97A0B3CDE591ULL, 0x065A0C949501D04AULL, 0xDBF586F402E3DA85ULL, 
            0x01B1D5859402B69FULL, 0x4B4B36192797E0ACULL, 0x5634C132CA0C8CC4ULL, 0x2684011BE0558B54ULL
        },
        {
            0x5200D451A41053E0ULL, 0x951B442263BE3D31ULL, 0xC4B8E048AF3AE3C0ULL, 0x1E61681532EF6168ULL, 
            0xBF454D3452788093ULL, 0x3DD1A443B1EBEDFAULL, 0x5D6A0A1E976A03F2ULL, 0x7C5ECF916A178740ULL, 
            0x4468D2DA013C8EBFULL, 0x574952B435522B6AULL, 0xABF81386C78B00CAULL, 0xC14A3F1AC1BE51EBULL, 
            0x8B1F6E63E2AEE609ULL, 0xD96C6F6B5FFA4EB0ULL, 0x4E995ABC9A278818ULL, 0x27015665FF158530ULL, 
            0x4252A37EC41156EFULL, 0x90C1D3D016467A0AULL, 0x7E7122D085F32EF5ULL, 0x61830312EA6A45D7ULL, 
            0xE2C80A9BB5097B11ULL, 0x0A9B0E0C9E46D11EULL, 0x1309445951DEFBAAULL, 0x73E9834FF6571D4BULL, 
            0x4E3005C60FFE5875ULL, 0x4DC29A819F252200ULL, 0x675E69397A8B305AULL, 0x9089C850D967161CULL, 
            0x14584B001A5D7E78ULL, 0x4C8600A2CE7F15BDULL, 0x1C0B915A9B7E3F28ULL, 0x3FEFC68DF38FB195ULL
        },
        {
            0x1F5D68954FCC3687ULL, 0x6C5158670CB750C0ULL, 0xDAA389EA78E3FEBEULL, 0x05F7AE06199C36AFULL, 
            0x49DD930B2D0B9D08ULL, 0xBAAB53D896AAEF7EULL, 0xEAD9798DF2137C49ULL, 0xDBB0C077D5DFF7F7ULL, 
            0xE15EC9042B77B4ACULL, 0x033501BA28E7A738ULL, 0x061558548E4E1B1AULL, 0x5841162095AAD388ULL, 
            0x1B31223132815608ULL, 0xBB7644FC67234D99ULL, 0x9422088ADB2C6E0EULL, 0xE63A6427AB2F9987ULL, 
            0xB897CA352FBA7B1BULL, 0x9A124CED225651FBULL, 0xB33A653DEC97398BULL, 0x4852CC9FF1F7C578ULL, 
            0xE7F9449B45EFCE41ULL, 0x37651492B2A00A81ULL, 0x50E8FF520501E37EULL, 0x36717C0B2FCE5844ULL, 
            0x58C1F375B35A58BEULL, 0xD1560FF6670BF1DEULL, 0xA7974185849FBFC1ULL, 0x35B72B004716A4ECULL, 
            0x2578377B35CB9162ULL, 0xAB9FBDDA5DE01E02ULL, 0x305A8C03FD13BABDULL, 0x2F7AD8997BC8B03EULL
        },
        {
            0xE5E07EE273C0DE7AULL, 0x8B572F30E7D50C8AULL, 0x24173394A34FC624ULL, 0xD1D2329BE74914B0ULL, 
            0xEDB7181E6693E3B1ULL, 0x64B86500B4D2AB1BULL, 0x9A950A330B96012EULL, 0x34BBCFEC189DAC94ULL, 
            0xF401DCB292AEEAE6ULL, 0x07EA250FF44E542BULL, 0x4BA02B8599DC63BDULL, 0xC00C73F5B5F4CEECULL, 
            0x02273B552F53B422ULL, 0xF677ECB1CCBAFC48ULL, 0xE45D891EF2E7A65CULL, 0xB655CE1ADE34E530ULL, 
            0x4BEFFB15F9F29B6FULL, 0x77F266ACF67218B9ULL, 0xA9845C9A936C2F49ULL, 0xD7695532C343A3DDULL, 
            0x0EFDCB41D86A451FULL, 0x139211F602839A4DULL, 0x754543A231B8C213ULL, 0x0979B534C6462BA4ULL, 
            0x79185CD1749F33D6ULL, 0xA3072BA4DDCFA5B0ULL, 0x6C08DCC5C46EDFE3ULL, 0x4D6CC796911CC78BULL, 
            0x942E61D2E724A5AAULL, 0xC50C28F559363F27ULL, 0x100F6791D6902E55ULL, 0x2BD7475DCDE85395ULL
        },
        {
            0x7841D88F6271D764ULL, 0xBFF35F84152F8275ULL, 0x035287F7CBF188FCULL, 0x8FAF3A5FCA0E58BEULL, 
            0x694CA071A8E45F7FULL, 0xBB9A7D665893BF41ULL, 0x1C65820FBF0D2E48ULL, 0x8FB851B386CEC489ULL, 
            0x1B33BC7C91D2AC39ULL, 0xE7031E9F2599449CULL, 0xB703669DD8224332ULL, 0xF3D34AACA3286734ULL, 
            0xBB2777085D177EC2ULL, 0xA57F4EE57C37F81EULL, 0xD524F87E8AF310F3ULL, 0x350B145FE5FD2134ULL, 
            0x8203AC41B2102965ULL, 0x61A4DF0C2E810686ULL, 0xBB0D88A08F99EA6CULL, 0xE18AEEA7513C1833ULL, 
            0x7AF49E767EB25547ULL, 0x6D44F6F11B75EE83ULL, 0x3E6290155B0DF087ULL, 0x946A40E5419099CDULL, 
            0x59F6DEF3CA5CAFD6ULL, 0xBC50EFA0AE828A90ULL, 0xB6907371984CB17DULL, 0x8576BA35633A3217ULL, 
            0x4C1D92BE776030FFULL, 0xBB94AE088F36C6C4ULL, 0x8C95651B00ED8D94ULL, 0xEA865683F2E8EB5CULL
        },
        {
            0x9E10B3AE2F57F928ULL, 0x14F681C4D59E2BADULL, 0xE8DB59FF1566F5D3ULL, 0x4C505D5965BE6FE5ULL, 
            0xE3DEDCC2E516DAB4ULL, 0x6CB910627810F058ULL, 0xBCBAD83360B9251DULL, 0x077D0249014B90D7ULL, 
            0xB12B6C9D15314A83ULL, 0x0B30A27574E2B3EEULL, 0xA7A8BC47606E640CULL, 0x68A6D07CBD858729ULL, 
            0x8DADC16C901AABF6ULL, 0x82341DDF4E92FBB5ULL, 0xE51CE70C52DE1B25ULL, 0x7D6D68CAAEC66D46ULL, 
            0xCF3C6FDC98D04F50ULL, 0x8502313C41D5DE8CULL, 0x7AB32893C920D63BULL, 0x0034FE503A604FC5ULL, 
            0xA9B3635EB8537960ULL, 0x3EC9B8B359FA6083ULL, 0x729512CB790069ADULL, 0x6933C7FE324172CBULL, 
            0x58B37549E6D88D4CULL, 0xA847F3309B46D18FULL, 0xE599BC2DDB4C435FULL, 0x1025AD6177FAC961ULL, 
            0x4CD4CF22E487E335ULL, 0xB96CCA37E324B7EDULL, 0x7A424CE193AFB5BAULL, 0xD7E5A4F5DAC07D49ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseHConstants = {
    0x40C99C5EFC4FB061ULL,
    0x12E26DE22DFB16BAULL,
    0x785B9BFB4290E654ULL,
    0x40C99C5EFC4FB061ULL,
    0x12E26DE22DFB16BAULL,
    0x785B9BFB4290E654ULL,
    0x9ED9F8534B935186ULL,
    0xB74F3F8A5AC57D9FULL,
    0x38,
    0xDA,
    0xA0,
    0x63,
    0x05,
    0xDF,
    0x80,
    0x0A
};

