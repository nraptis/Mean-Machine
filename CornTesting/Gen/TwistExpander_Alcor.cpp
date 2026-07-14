#include "TwistExpander_Alcor.hpp"
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

TwistExpander_Alcor::TwistExpander_Alcor()
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

void TwistExpander_Alcor::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC86E0C90C1A083B6ULL; std::uint64_t aIngress = 0x880C7124E75EEAC0ULL; std::uint64_t aCarry = 0x8CD7796C63D65FA7ULL;

    std::uint64_t aWandererA = 0xDB881F4B5604C754ULL; std::uint64_t aWandererB = 0xA74DAD49B830306DULL; std::uint64_t aWandererC = 0xCEDCE2233B278AF7ULL; std::uint64_t aWandererD = 0xA5F99388AB9CF31AULL;
    std::uint64_t aWandererE = 0xE72F418DE914DB94ULL; std::uint64_t aWandererF = 0xE453B0D153E779F6ULL; std::uint64_t aWandererG = 0x9DDCECEFBF1641D2ULL; std::uint64_t aWandererH = 0xCC30341454CD9710ULL;
    std::uint64_t aWandererI = 0xA67B578EB8E1CCFEULL; std::uint64_t aWandererJ = 0xA18B2F9ED6C4BD80ULL; std::uint64_t aWandererK = 0xE67842CFCD06E2B7ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15753709089402989060U;
        aCarry = 10627991808644215202U;
        aWandererA = 13135424592644804365U;
        aWandererB = 10067389170649792703U;
        aWandererC = 14020512894893260714U;
        aWandererD = 12392482917785683018U;
        aWandererE = 16949905874437450603U;
        aWandererF = 9998585357532662167U;
        aWandererG = 14607947719319309779U;
        aWandererH = 10473378226516415734U;
        aWandererI = 14095448830876328506U;
        aWandererJ = 9961284270910569924U;
        aWandererK = 9448866900439543172U;
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
    TwistExpander_Alcor_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alcor::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE1C02A71E9F1590AULL; std::uint64_t aIngress = 0xC3F93B04044E89F2ULL; std::uint64_t aCarry = 0xDEF1B56540A7EDB1ULL;

    std::uint64_t aWandererA = 0x9A677AE1548743ABULL; std::uint64_t aWandererB = 0xD468C8C8683724B6ULL; std::uint64_t aWandererC = 0xADB10854B8C7A135ULL; std::uint64_t aWandererD = 0x8C4D989F24853D65ULL;
    std::uint64_t aWandererE = 0xD3CB557C4568EF9EULL; std::uint64_t aWandererF = 0xAF136F3202272686ULL; std::uint64_t aWandererG = 0xD4540C128C404A63ULL; std::uint64_t aWandererH = 0xB799EDEF19FC1CFDULL;
    std::uint64_t aWandererI = 0x84F2E67FF03BAA92ULL; std::uint64_t aWandererJ = 0xBFDB314B50156765ULL; std::uint64_t aWandererK = 0xADD1C4E9C697A414ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16940846286379047915U;
        aCarry = 12186521323967361825U;
        aWandererA = 9818075346675628622U;
        aWandererB = 12505439612311406852U;
        aWandererC = 14968174015618833990U;
        aWandererD = 10929982687762087450U;
        aWandererE = 17583117558238226385U;
        aWandererF = 12917469492075000492U;
        aWandererG = 13033475897856971168U;
        aWandererH = 15462483131381184336U;
        aWandererI = 18350777105739544349U;
        aWandererJ = 12424728123403825554U;
        aWandererK = 12271811748831437861U;
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
    TwistExpander_Alcor_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alcor::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA97D9C27D67DDD33ULL;
    std::uint64_t aIngress = 0xD0CF3A9485430782ULL;
    std::uint64_t aCarry = 0x934C04BBD24E9B86ULL;

    std::uint64_t aWandererA = 0xBF71C546A626F2DFULL;
    std::uint64_t aWandererB = 0xE9AE46F475787DDFULL;
    std::uint64_t aWandererC = 0xCE15FAC62A33B271ULL;
    std::uint64_t aWandererD = 0xF2F300BDCE058471ULL;
    std::uint64_t aWandererE = 0xB8256A7B416689F9ULL;
    std::uint64_t aWandererF = 0x80EAF2B62611310DULL;
    std::uint64_t aWandererG = 0xA4788511E2683BE6ULL;
    std::uint64_t aWandererH = 0xAB31C344A605BF28ULL;
    std::uint64_t aWandererI = 0xD724E2551CB9295EULL;
    std::uint64_t aWandererJ = 0x8F7D69B7B2BC44EAULL;
    std::uint64_t aWandererK = 0xE01A0885E8616728ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneA, 0);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneA, 4);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    TwistExpander_Alcor_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alcor_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Alcor_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 2 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1984 / 1984 (100.00%)
// Total distance from earlier candidates: 1984
void TwistExpander_Alcor::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 537U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1767U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1861U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1189U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 737U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1700U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 259U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1200U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 265U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 963U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1737U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 886U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1525U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1204U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 659U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 258U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1962U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 881U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2019U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 151U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 364U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 443U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1671U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 382U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1479U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 70U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1640U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1560U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 189U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1156U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 353U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 216U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1256U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 207U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 252U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 964U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1509U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 127U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1511U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 106U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1718U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1046U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1845U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 110U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1183U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1148U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1555U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1457U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1045U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1322U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2001U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 310U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 182U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 552U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1279U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 149U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 621U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1764U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 371U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 892U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 904U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 300U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1092U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2007U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1919U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1871U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1102U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1518U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1190U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1401U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1644U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1543U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 268U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2012U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 487U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1463U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 667U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1386U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1281U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 405U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 358U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1661U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1307U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 308U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 475U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1503U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1813U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1465U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 379U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 617U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 742U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1427U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 84U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 646U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 453U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 430U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 256U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1215U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 501U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 681U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1416U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 247U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1645U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1321U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1989U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 772U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1730U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 120U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 288U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1227U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 735U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 434U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 188U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 875U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1313U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1449U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 424U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1488U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1562U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1612U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1990U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1170U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2044U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1029U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 826U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 20U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 952U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 73U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Alcor::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x9EDFB342C075AC2BULL; std::uint64_t aIngress = 0xFA2B0F641F33035EULL; std::uint64_t aCarry = 0xC81E839B4E274E6FULL;

    std::uint64_t aWandererA = 0xF2D38BC5C1F444ECULL; std::uint64_t aWandererB = 0xB0DEC407824F4BA4ULL; std::uint64_t aWandererC = 0xA8F49EBACAA04C4FULL; std::uint64_t aWandererD = 0xE17899CAEF764D80ULL;
    std::uint64_t aWandererE = 0xF0B4521C0F473A75ULL; std::uint64_t aWandererF = 0x8197159AC26D26BFULL; std::uint64_t aWandererG = 0xD9CAA61F3AAF769EULL; std::uint64_t aWandererH = 0xBD6EF60F07238B22ULL;
    std::uint64_t aWandererI = 0xA996F5AB1643E77FULL; std::uint64_t aWandererJ = 0xEF74AD2AACB72D53ULL; std::uint64_t aWandererK = 0xCEB4625FBA4FFCC0ULL;

    // [seed]
        aPrevious = 18084057926459150088U;
        aCarry = 11181796771103212195U;
        aWandererA = 14288380072005408891U;
        aWandererB = 17121769493097574637U;
        aWandererC = 12125672534095646401U;
        aWandererD = 10597467662618513830U;
        aWandererE = 15356235068953724432U;
        aWandererF = 13627809173234651624U;
        aWandererG = 14308677517620030473U;
        aWandererH = 11354236306046862452U;
        aWandererI = 10183884789589622435U;
        aWandererJ = 18304998639830623397U;
        aWandererK = 18385001720298254986U;
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
    TwistExpander_Alcor_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Alcor_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Alcor_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 2 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 668; nearest pair: 668 / 674
void TwistExpander_Alcor::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1356U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4136U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5634U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2086U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5543U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2646U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 556U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 244U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3214U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2349U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1621U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2369U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3220U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 513U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 751U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2491U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 549U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 988U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 570U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1687U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1717U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 370U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1520U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1588U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1526U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1058U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 351U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1352U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1922U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 965U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 77U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 704U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 310U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 566U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1569U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 839U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 2 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 667; nearest pair: 667 / 674
void TwistExpander_Alcor::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3519U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4364U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 307U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3755U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3395U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7722U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6033U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2085U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6548U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 347U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5988U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6233U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6958U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1234U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 497U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3976U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1024U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 243U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 435U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1282U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 148U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 258U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 665U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1097U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 142U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 424U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1387U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1337U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 611U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1609U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 195U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1836U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1116U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 906U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1894U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 781U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseASalts = {
    {
        {
            0x1B50B5CB6462042DULL, 0x055F7616BACA31D3ULL, 0x1B136D691B47A675ULL, 0xE036FAFD98772FD0ULL, 
            0xAA57A1605B699023ULL, 0xF5E4F489C52AAF72ULL, 0xCA14BBA8430BAC60ULL, 0xD7A2B1F6BBB71C18ULL, 
            0x3CF67C0DE29C2F54ULL, 0x605DCAD4484D84BBULL, 0xCC61E15A561CC9F8ULL, 0x8F942451A5271B20ULL, 
            0xD32D6139113FC642ULL, 0x843E154EDC9AD265ULL, 0x193B5C6107044DD3ULL, 0xC8FC3BBF1CFBEBC7ULL, 
            0x87916F476044F42DULL, 0x96C0AB11C4AC85E1ULL, 0x6E2AFF303AEB279CULL, 0x3635BF867DC23FA1ULL, 
            0x0CA0B3F9E8AE39FCULL, 0xB303E016F00CC221ULL, 0x9E1A5E811A77E422ULL, 0x484431DC53DD62ADULL, 
            0x505C73FD799DE325ULL, 0x8779B8BD8E130314ULL, 0x16DDEE037D7A6627ULL, 0x0E466AC0391E49F5ULL, 
            0x4C87020BF47A5C1EULL, 0x0EE2EE1255BBEDC5ULL, 0x4928AE14340365FAULL, 0x3837DE02F46EECA4ULL
        },
        {
            0xFB10E2525089876AULL, 0x10D55AA020A1ABA1ULL, 0xD999233CA206E04FULL, 0x687597E62DF76284ULL, 
            0x1050EB2F737E7B7AULL, 0x1BFD9DC20297AA79ULL, 0xEE11E42AC265E7F7ULL, 0xC168C23C6C3135C2ULL, 
            0xB62C2A3F758E515AULL, 0xBA2D2AFD6658AF45ULL, 0xD21B69A4EEF5F59FULL, 0xEEFABAC9E972E62FULL, 
            0x5E09766E8B88817EULL, 0x2B87D38EC0FA20BDULL, 0xA32E1B268D12D1A2ULL, 0xCF470656384E610FULL, 
            0x3DD61FB878290E6BULL, 0x4722EC106D365C6BULL, 0x8B9AB89986253FDAULL, 0x63B344B5918F3CA7ULL, 
            0x3CDBB0A2B8B0B365ULL, 0x496721FF4BC682CDULL, 0x7D5685370BAF0C94ULL, 0x1D2943C845DF46BFULL, 
            0xB34E88BE2D8DFE54ULL, 0xF1BB4CA5394AD567ULL, 0x90D74F2F784E1CECULL, 0x9D432745E18B6A93ULL, 
            0xBEE780F481C91926ULL, 0x1C20EA59EB44570AULL, 0x23DEEEDC7085B7D2ULL, 0xA836C2E6568121F9ULL
        },
        {
            0xFFE94B2249F99F53ULL, 0x14032BA889C74776ULL, 0x73C81F5408C38AB1ULL, 0x03AF40029F4CDB11ULL, 
            0x5EFBB882450EC348ULL, 0xE613ADC5807BAE28ULL, 0x3E1588F71C05E9AEULL, 0xAD0ADB7401C60895ULL, 
            0x94E40B7C380C5226ULL, 0x1379AE5A48D80CBDULL, 0x760FD0D095883774ULL, 0xCEFF37587BDC9EC5ULL, 
            0xD2341A8209DC2A28ULL, 0xB5F6609E1372001CULL, 0xEEEE33354A083EF6ULL, 0xD2FCF41121926EE0ULL, 
            0xB7519939ACF8518CULL, 0x773FCE9F5657ABE3ULL, 0x2AFDF0104F6A3E0BULL, 0xA6026F4302EE5790ULL, 
            0x10054D5D61982E54ULL, 0xA22B6B58785EBB3CULL, 0x96D93FC37CA19E47ULL, 0x3FC31D271270C7B4ULL, 
            0xE7AD2BD9C72041BAULL, 0xDCE34416BCAF1AA9ULL, 0x7EAF6B3E5EB59614ULL, 0x73C3AF9AA3F7E2A1ULL, 
            0x379631327016ECDBULL, 0xAD18E3D0A5626A0DULL, 0x82B16EAD32D12F1FULL, 0xEEA5B2B7269D56B2ULL
        },
        {
            0x0ABBB64A9BAE652EULL, 0x40ED3D258CF98609ULL, 0xAC49599E3DD42D3BULL, 0xC9F6884CEF60F843ULL, 
            0xED85C4909C7B5EB1ULL, 0xCCE2CB6B9EDD7D3FULL, 0x31AA4DCB80E7CF37ULL, 0x977E66A64BD16F2FULL, 
            0x63E23F758044E63EULL, 0x8039AE69472DFC36ULL, 0x39ED04DF7AC58DD0ULL, 0xFF6D17E76CE4686FULL, 
            0xC33CF546D0863074ULL, 0x03AF3A5D05DF2CA6ULL, 0xB3DC8A5905EA7D3BULL, 0xF08443E12C25A205ULL, 
            0x2B9EECA86EDCB73BULL, 0x7D46781767D63FD9ULL, 0x6D41B1124B7AE377ULL, 0x8423AC83764FEFB5ULL, 
            0x3569174D0870E5F2ULL, 0xB557BD3F2D1B687DULL, 0x9E8AC1E057004BBCULL, 0x36D1A4D0C93ADFB5ULL, 
            0x08D011E502BC238DULL, 0x629A2B93538CC63AULL, 0x89D16A784ED0EB07ULL, 0xE106316DF034D296ULL, 
            0xD6CA088326686EA7ULL, 0x0218FCD1C2986439ULL, 0x5BB0009042517B90ULL, 0x19C165C13ED8B0A1ULL
        },
        {
            0x52E840A230E12303ULL, 0xF2E48267909FFCF4ULL, 0xCACDB8CD32C9C453ULL, 0xD698B50694F38659ULL, 
            0x206C9E379F5C2C37ULL, 0x34FE9235B6F329B2ULL, 0xF8A7F75E5B307CE5ULL, 0x2C6064D6BBC0F56CULL, 
            0xE97CB4F4B726488BULL, 0x40350CAC12E11410ULL, 0x46B5A7653EEB2BBAULL, 0xB959B3B5E71B8EA7ULL, 
            0x5F6BBD8B01A6EC63ULL, 0xB3AFDCC4D973799BULL, 0x2CEB99B6637A780EULL, 0xCAACDB1BC10DEF29ULL, 
            0xDB091C267049A0BAULL, 0xF26FB82F9968EA07ULL, 0x3044227F8D673591ULL, 0x3056E05806BD95D6ULL, 
            0xC3D737FDD637EC04ULL, 0x47AFC84949FCDE02ULL, 0xC5A639EA0A5C5985ULL, 0xBAC5E778A9B7CFB0ULL, 
            0xDFE32037D5892E3FULL, 0x967A6EEDEF7337E9ULL, 0x7F06D5F182F836DFULL, 0x545AE90F5B701FA8ULL, 
            0x3E0045B69E0FFFBBULL, 0x8685093317953905ULL, 0x78BD85B676D458F9ULL, 0xAD54502CB35398F0ULL
        },
        {
            0x6078AE2F76E1F760ULL, 0x12F6D34FF450AEC5ULL, 0xC361C477707E17C6ULL, 0xFA105506D75E178FULL, 
            0x5351701A226D8AD6ULL, 0x246BF9D97E32AE47ULL, 0xDF93A2707307DD25ULL, 0xE6441B56F372F064ULL, 
            0xD841F494AE4A1653ULL, 0xF7403DB4E783E9D5ULL, 0x4DCA36DE7403416EULL, 0x71A7BB6B0CF32EE4ULL, 
            0x1231888A1CBED640ULL, 0xC42E51163DC3129EULL, 0xF488318EC849C7E8ULL, 0xED8B5B3E8A591471ULL, 
            0x64D0EC319BE1413CULL, 0x61F3578058BD69FCULL, 0x2B10BB8B1E466672ULL, 0xD6947F8DBD146F15ULL, 
            0x676560C8274845E8ULL, 0x88E333BD888901A5ULL, 0x453DFF48BBF04FF8ULL, 0x596543A54B018DCDULL, 
            0x01EC96B91EDEA867ULL, 0xFEE3B6D50268B862ULL, 0xAEB5ECEE0EE5D6EFULL, 0x005BEB1EC91783DDULL, 
            0xBB8D91F5957E27E6ULL, 0x92B8AD72D353E9B2ULL, 0x03D1F30662F67963ULL, 0x24383C4400FE4A2AULL
        }
    },
    {
        {
            0x2A45176A09EB11ABULL, 0x7F9E4A5A20C0B7BCULL, 0x90663AE5DCDFEAD5ULL, 0x06A171FBE49E9073ULL, 
            0x9AF019B7550A7126ULL, 0xA8E07E62C7686BF9ULL, 0x3B78081090A8A6B3ULL, 0xDE2BC22AB96EF8A7ULL, 
            0x80A1C6EAAA893E5FULL, 0x2996EF0AEB7B387CULL, 0x123670CDAB9CBAE8ULL, 0x0B232981C376FAE3ULL, 
            0x3048250A2B56FEC0ULL, 0x2604E9390739DE93ULL, 0x21809733BC2C1224ULL, 0x5D418EE197F8B74FULL, 
            0xDB7B17617B1C53CEULL, 0x890DAD834B43B843ULL, 0x7957214C9D9A90E4ULL, 0xB40F7DC8AEAE267EULL, 
            0xFEC2F477BE02EA76ULL, 0x3A80B5B1D7FE48D8ULL, 0x1AA21F6F82513177ULL, 0xED7825F382A2BC66ULL, 
            0xD90E3CC94A87C49FULL, 0xA58D35B01118673AULL, 0x41E566F86FD14EB1ULL, 0x1509F16532BAB867ULL, 
            0xB2645727F6B7F59EULL, 0xCEC9ADDFC15526ABULL, 0x3234B0B061EF7E92ULL, 0x118605FC2367A4E7ULL
        },
        {
            0xCBCB9B6E20B08589ULL, 0x6A0BA4B27A0093FAULL, 0x687736FD51C815B5ULL, 0x1CA3E2EF9137E2E0ULL, 
            0xE4BCEE0AF49DD55BULL, 0x7D26F5A254EE7A10ULL, 0xB9313E4D4D2ABEACULL, 0xDD6895D3ED9E0D2BULL, 
            0x17C44036D536738FULL, 0xAEC978CA54B1667DULL, 0x7FBEBB7728636386ULL, 0x6D563111329CFDC3ULL, 
            0x45CD3B787C4B2AABULL, 0x8CDBDB3CB5AA7A16ULL, 0xB4C30BCC5211E1D5ULL, 0x4F55D627B594A2A9ULL, 
            0xD38D84F46433EE9AULL, 0xB15E45AE6BCE9A87ULL, 0xADE10010FBA4F71DULL, 0x23E314F1C1B88FA6ULL, 
            0x290D2599C4454331ULL, 0xD1E58E76A8822CB9ULL, 0x8E6AC25ED7ED7E14ULL, 0x449A605926EF5082ULL, 
            0xE5EBCEE8F56ED92EULL, 0x2C0F3CADFC75EDFFULL, 0x88BC93AC7029BEB4ULL, 0x954CDDEB6B06C9BAULL, 
            0xFD2D8F42CD5B7D23ULL, 0x7FA388AD96383776ULL, 0xC4031B78B34DB545ULL, 0xBB30B5F4C6279089ULL
        },
        {
            0x3398EF19764B1E15ULL, 0x99142AA83B89CF8BULL, 0xAAA1E748F19EA990ULL, 0x7F6036E73F740928ULL, 
            0xEC09705B12C09BF7ULL, 0xFF47F04111CE4255ULL, 0x01E1ED8637AF557BULL, 0xAD540AA941C4A8DFULL, 
            0x46719E229959EE08ULL, 0xA6D2B696F3C154FFULL, 0x9B6CC88FE8958C62ULL, 0x754CB750C7D9075CULL, 
            0xCA155C220E83E7B4ULL, 0x374BD50C72C23ABBULL, 0x633280374764F537ULL, 0x055D7BA126CE09EFULL, 
            0x92B137C821519A10ULL, 0x337A1EB2EB95D497ULL, 0x9A1C2814567BF2EFULL, 0xE886051209CE02F3ULL, 
            0x5F40E553BB2DBE19ULL, 0x170479AFEEFD1C99ULL, 0x86D9999B7D913293ULL, 0xABDFAD7BDC12FC43ULL, 
            0x729F75A6AD348918ULL, 0x30465E94F954A1A8ULL, 0xEBF6C188E645C8EEULL, 0x51FF70D4C42954FAULL, 
            0x6DC3C6D496B8CE7DULL, 0xCAC854D8E3CF48C8ULL, 0xDD581202F15CAD35ULL, 0xA8CCD5E9963AB244ULL
        },
        {
            0x432A77E683FC1A9FULL, 0x5C1595225C839E17ULL, 0x61AA7F14D72A8142ULL, 0x74F2EC672B968B31ULL, 
            0x7C00F861EB47ECBCULL, 0xCB180D7A8C488338ULL, 0x45E6D50A65271529ULL, 0xEF2D595CCC3277A8ULL, 
            0x8F3A839EF8916FCEULL, 0x2FD461963791FF28ULL, 0xAAF3DD6EE40E0BE8ULL, 0xEB0C7CC4836EC3FEULL, 
            0x40416567537B484AULL, 0x5297CB41D151BD81ULL, 0x9343C809D436B73AULL, 0xCF053041ADF0D043ULL, 
            0x9A413A3076D0ED51ULL, 0xC06D69F3937F12E5ULL, 0x36F0C7E5236426E3ULL, 0x97FD99B04F6D9F8EULL, 
            0xAE2E4FCEA09373A9ULL, 0x79E5C9F9731F21C2ULL, 0x84135638560AD151ULL, 0x2DEE2898A2C25F18ULL, 
            0x7F522B3DF290C371ULL, 0xF8EB754C6D8727F5ULL, 0x59EFCB3BE4D15A83ULL, 0x6A19233EEC6E0DA8ULL, 
            0xFC7D37FAD7B4A482ULL, 0x546464EABE44402DULL, 0xCD8A1BF7BB13F860ULL, 0xE54C3120FBD5918FULL
        },
        {
            0x812835DC2B2D5FC0ULL, 0xD0A09496A7837EA4ULL, 0x8B06247A51FB130EULL, 0xF34FE76AC808BC56ULL, 
            0x7267B300FCF06A4BULL, 0x335B12E5D76853C8ULL, 0x5CBC8B72BA15A243ULL, 0xD0FFBE2723124BD9ULL, 
            0xE1E805C75290C1F2ULL, 0x2F50CC5F1B8C706EULL, 0x4EB3C1A687ADE493ULL, 0xC4846DF8C7AB2CC2ULL, 
            0x7AB6EB6139933019ULL, 0xDD816FFBA6819FF5ULL, 0x010DAAB713209FDAULL, 0x84415877DFF16F9BULL, 
            0x710FAA5412AA9738ULL, 0x55174A9277FBC442ULL, 0x55F110F532EEEF0DULL, 0x2FAB173D73A06C15ULL, 
            0x8FA016A0F87AE1E1ULL, 0xD12BD495E43A1AA3ULL, 0x850C5FC814589CD3ULL, 0x97F9F42D1569C719ULL, 
            0x377780EC5F88287BULL, 0x658A2C01F403F1D6ULL, 0x9E230CC07DF3F5BFULL, 0x57270B4B39572980ULL, 
            0x19A4EB2B8F777524ULL, 0x4A59EC032DF2E958ULL, 0x38BD01F704002D6AULL, 0xC09BCF4C76EA63CFULL
        },
        {
            0xA4E0D27AADD22DEEULL, 0x2F5A6DD6F7FF8565ULL, 0xE5AB3CFCD69BA39FULL, 0xFA0BD56293D1C02DULL, 
            0x37DDC084BE82C8B7ULL, 0xF4B0B6DF2DF21CFAULL, 0xD1F3CC9BF35B72DBULL, 0xA66F867F5DEAFECCULL, 
            0x4E84C921E17164CCULL, 0x2498EACAE2D9F9A6ULL, 0x42DA7B8674C7FCA9ULL, 0x6492F814468FEA24ULL, 
            0x2604218354127DBDULL, 0xC1445E574D1756D5ULL, 0x7D7379D3151C3C12ULL, 0x653D328AF48ED704ULL, 
            0x9AC9FEDDC2249EECULL, 0x7530B355AE235478ULL, 0x08D5271648ECD542ULL, 0x0FC2025465F01DE3ULL, 
            0x6F4C19C359861B2DULL, 0xF4560B33C35DF264ULL, 0x6F1255670C722352ULL, 0x33BECE5197E6B0C3ULL, 
            0xFFB68836CFC5183FULL, 0xCD8F82D2EC2A14A1ULL, 0x8B57A8DB290C1E8FULL, 0x39D795E8BE878DE1ULL, 
            0xE8585236CDAB923BULL, 0x60BB3E31C5007C6EULL, 0xD937DBAC79522C84ULL, 0x3BC021AA087BB196ULL
        }
    },
    {
        {
            0xF31D58270963F426ULL, 0xECC0D86E1E43CA90ULL, 0x9462637ED08DA49AULL, 0xEBDDCABFBBBAFC09ULL, 
            0xEBA23AA8E446390AULL, 0xD896374C99FB1CCBULL, 0xF84D72A4EBE018D9ULL, 0x2F78C459BD0BFF17ULL, 
            0x48AFC2A43B5EF681ULL, 0x69B3044F8D50050BULL, 0xF6E3E5D83DED4EB9ULL, 0x849C5264D8A59138ULL, 
            0x8F13CB49038A030CULL, 0x89DA6E443A6F7C80ULL, 0x58526696F19C6968ULL, 0x56290F2DA85C98A5ULL, 
            0x0EE4AAE30CF03AA2ULL, 0x4A2719EDCE9A3831ULL, 0xDD88321BDE4F80A8ULL, 0xA0EA72B465A32C7CULL, 
            0x09AD069FEE1A3315ULL, 0xEE16871210733A07ULL, 0x70561FF9D85D2078ULL, 0x9A25120972811AD4ULL, 
            0x14EE37AA61A8FD2CULL, 0xA2B0BF50DE34782CULL, 0x519DC282F7A0CDE7ULL, 0x2B0227816D8EA5AEULL, 
            0x73D4941E1043F50CULL, 0xF49860BFB2A38D6EULL, 0x1DC766AD6FF0A68DULL, 0x9EB1076A01724B4AULL
        },
        {
            0x80A1E97167D2F9A9ULL, 0x493BFC602A4EEE77ULL, 0x5CA50C98E79C57F1ULL, 0xEFE2D5AC6B9A5D0FULL, 
            0xD0102E72783F4060ULL, 0xC0280CE08AE47A93ULL, 0x0EA52873CB6B432EULL, 0x04BA01FBC2A2E90AULL, 
            0x73B7966103462195ULL, 0x1C85C70A1E9CEC08ULL, 0x4DF84165721172FBULL, 0x3B8001ED8F544142ULL, 
            0x3124F3193347A42CULL, 0xF972402359D38376ULL, 0xB0BFE2272A611982ULL, 0xA89AAD1AFCB65509ULL, 
            0xF19C44F9E1F07BDCULL, 0x00BC3C1D177823F0ULL, 0xF1CE32E2D17FF176ULL, 0xA6B14F51DC5B064DULL, 
            0x905AB90C92828EF5ULL, 0xA066CFA926B4C8E4ULL, 0xC76E1D0CCFE9A478ULL, 0xB38609012654EAD2ULL, 
            0x63B1D507BF172543ULL, 0x869141AC9ABA6730ULL, 0x6869267AE152FE15ULL, 0x210C0D0BFE36C86AULL, 
            0x68B0048AB26D731FULL, 0x0C4C2F6629632F9EULL, 0xC9C7AB21EC2C5013ULL, 0x66695C37F7760179ULL
        },
        {
            0x1E5E234C55236227ULL, 0xA2E98119FAD81C95ULL, 0x4095C0CB8AD0E523ULL, 0xB38798A9CBDDF8E7ULL, 
            0x497B934D121A857EULL, 0xB34425043F5A94D2ULL, 0x4C5FA2D3B655E90BULL, 0x8000C80002CF755CULL, 
            0xA12CFA1A3505F839ULL, 0x26B1252D4AB7E24EULL, 0xB07739C84B43737EULL, 0xCD87A0FFE55BE861ULL, 
            0xA0A19F24B746421FULL, 0x0FB8197E7BCFA85BULL, 0xF6FB386EE42ED5BAULL, 0x253F6A93D96B3510ULL, 
            0x48CB95A959A39126ULL, 0x70EEABF6881C2176ULL, 0x7BABAD3519CC7E30ULL, 0x6AA748AE662B3C52ULL, 
            0xEF3AA9D2E1CA1BBEULL, 0xC42B74035F0F4D1AULL, 0xB85AD21EF0F309D4ULL, 0xA539B0976CC3444FULL, 
            0x671DE510D0EA75DDULL, 0x707C41EC3673B1ABULL, 0xF0B3B1752754F557ULL, 0xF570A76941D072CBULL, 
            0xB04889065F2B72CDULL, 0xAD677DF42E5F5DF2ULL, 0x54C10939DC728C6AULL, 0x80FD2DB64B0B0D9CULL
        },
        {
            0x370A205CAF8CDFFBULL, 0xA82EEB35FE344D9AULL, 0xA490D21E6FCAF7DDULL, 0x6F34FD68D6B0B8BCULL, 
            0xDCE2F8CE2F2AB1E2ULL, 0x43F07EF434848B3AULL, 0x93A5B62D85CE8B40ULL, 0x57EF4384C8C505EAULL, 
            0x73A6B4D572E2E014ULL, 0xF5A80D4517586A11ULL, 0xF0AA7D45BD75F622ULL, 0xEEAFCF0FF6AC3139ULL, 
            0x5625705811FF40A2ULL, 0x16956E62ACD39CE8ULL, 0xC9FFBFFE91478A7DULL, 0x7CB07F93F28359EFULL, 
            0xFB5CFB462812A5A2ULL, 0x5D1256861168161FULL, 0x4F92515B28D0FA7AULL, 0x43357251943D1AEEULL, 
            0x28F1C7181A08D68AULL, 0x0833FC776856F943ULL, 0xE5FAF4DB2F1CA9BDULL, 0x515A4D64BDA9D722ULL, 
            0x1DD3A32736D33B18ULL, 0xDF18C58A5C779FC0ULL, 0xDDEDC2E07EB336E2ULL, 0xF1900C599AF0670BULL, 
            0x4199960FA68C2224ULL, 0x1E163CF9E4B0A7ADULL, 0x32880835FFB19715ULL, 0x6289F59762DE0ABEULL
        },
        {
            0x25C359A23A8EA7F0ULL, 0x12E6A1EDBCA072CBULL, 0x8F12885732AEC669ULL, 0xDFB024053520FB48ULL, 
            0xB135445DF0737DCBULL, 0x4D06DBC3440D4AE9ULL, 0x9419F9916514ACAEULL, 0x1BE269C2997CFF57ULL, 
            0x39BAC114A0C43DFCULL, 0x202DA9829A5134ABULL, 0xC5CDC0BF3FF2BF4BULL, 0xC2F5DB38F09D91EDULL, 
            0x89DB215606C73316ULL, 0x4CE6B813FE3E0C22ULL, 0xAB7FD6224EB0F7CBULL, 0x2AB7494CEFAB19DEULL, 
            0xA986002C34EB365EULL, 0xF569052F7CDE3722ULL, 0x92726CD651FABD60ULL, 0xC11067636F3D6D9AULL, 
            0xE98F6BE7D43A1078ULL, 0x3977832D6CA03D3AULL, 0xBCAE2A766289640EULL, 0xE80E74071A086EB6ULL, 
            0x02184E7F4C8BAC73ULL, 0xBAD06D25C7905947ULL, 0x3B0747AA4A7D12EEULL, 0x1286245E24F20EC9ULL, 
            0xE9FDE46F7B0FA4F9ULL, 0x974A1C0763D44E55ULL, 0xDDEA263D1CC5D86FULL, 0x2BD732CB18EDB118ULL
        },
        {
            0x0B1A3C807E22678AULL, 0x37D1A9C85E5C2FD1ULL, 0x8802CA75F743D587ULL, 0xA34D36C77EFD02A0ULL, 
            0x993544C577004FA3ULL, 0xB153631D7620A5E2ULL, 0xBDA428E72CB28B9FULL, 0xF43BC4CE46AB28A7ULL, 
            0xC87B8E8521220EF9ULL, 0x31DA1BEE5555BAE2ULL, 0x7AEAA06C18AB1BE4ULL, 0x3189456991D8DBF2ULL, 
            0xD945FC80BA6F742DULL, 0x51A2D46133621C29ULL, 0xF62D06AB027F534CULL, 0x7C89BD34C716FB62ULL, 
            0xB561D410A0E041A6ULL, 0x292FDD8ED4274821ULL, 0x1CB3A26507E4CC7AULL, 0x9B12779627B0F04EULL, 
            0x81C1BDD587794FE2ULL, 0x76B446D29E84D030ULL, 0xC95490CE88869285ULL, 0x54286280B95B25E9ULL, 
            0x20B413C82A328950ULL, 0x377DFC944D157595ULL, 0x744F26E39DD1C05BULL, 0xEA3454B1AFA3CDC7ULL, 
            0xD557BA5BBA8F797BULL, 0x9FADEB63DAE8ED40ULL, 0x34059ECBB2219DE7ULL, 0x652344F611A59D47ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseAConstants = {
    0x8C11F35C8366577DULL,
    0xF3EC22320B3E6B6BULL,
    0x14586B7C5F01D6D4ULL,
    0x8C11F35C8366577DULL,
    0xF3EC22320B3E6B6BULL,
    0x14586B7C5F01D6D4ULL,
    0xC06302D318F67790ULL,
    0x5B43AE4F66FD0B33ULL,
    0x53,
    0x58,
    0x84,
    0x16,
    0x14,
    0xF9,
    0x39,
    0xF4
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseBSalts = {
    {
        {
            0x850F4E394FE3E915ULL, 0xCFFDF0A1F8406A48ULL, 0x23FB232CFBFDB641ULL, 0x5591531C876B6247ULL, 
            0xF3C9296E25A4AE85ULL, 0x3387AA9C51FED7AFULL, 0xDFCB1137FA90611AULL, 0x1FBC940EDDE1EB41ULL, 
            0xA6C8F6368CE13E3EULL, 0xB2FCD148CF03B940ULL, 0x7D0D44670A4AABAAULL, 0x780511CCF54AB083ULL, 
            0xFA95D1821E4E7F3CULL, 0xB77FD0C34B122F87ULL, 0x483E786BB5EED28DULL, 0x117D72E4181CDAE0ULL, 
            0x48E7DC12159FFECBULL, 0xD97722B8DDB82037ULL, 0x8520C5CC7DC96E8BULL, 0xA98386F7A760D2D8ULL, 
            0x1B3106A3A9C25BF9ULL, 0x22AD1D8CACBF590BULL, 0xFD50706132FD5424ULL, 0x93F621885024D358ULL, 
            0x502116F6E3603546ULL, 0x3F7145051EED0ACEULL, 0x9C19E464948BE9E6ULL, 0x06D4B6F3BA81EB61ULL, 
            0x1F19E91583F9DCC6ULL, 0x5D0FFEDCB9C87C32ULL, 0xED0A58DEC2AE0E8EULL, 0x79C11FC8972D28DEULL
        },
        {
            0x10646FD1EE717D66ULL, 0x195166462F5249ECULL, 0x775B8E1F6FED30A1ULL, 0x97D60982229475C0ULL, 
            0x9B682D9A65BF5381ULL, 0x033F1FBA950EC87AULL, 0x5104EABA132E9C1AULL, 0x82EEF603DA351779ULL, 
            0xC14B71CB21EE879FULL, 0xCEE25411C3BBBF23ULL, 0x4847EED03E397BECULL, 0xD3AF2069529C1F86ULL, 
            0x0B71C54872B1D60BULL, 0xB96A137738769A0EULL, 0x32F78FC436FDF7C9ULL, 0x3AABE24C3EC6C75DULL, 
            0x8C8D27F44DB24B27ULL, 0x0CADEABBD3D94037ULL, 0xF676D78A110305F0ULL, 0x8E4930CAE3FCEE8EULL, 
            0x1E31577CF44D553AULL, 0x6861E26C7B3ABCB6ULL, 0xE73426D81E0588F8ULL, 0xA94F0CEB6FECEBB0ULL, 
            0xABD3B93DB0CC7005ULL, 0xB9CE03D785D371A2ULL, 0x709F37694E20EA9CULL, 0x08653B3C8D9F8E92ULL, 
            0x6887C02078E13EF0ULL, 0xE834EF15CC545930ULL, 0x31343D916762B355ULL, 0x9C4437287A3EE0BCULL
        },
        {
            0x3C57E1513051ECA3ULL, 0x4CC07007DCCD2B06ULL, 0x5401FB9C0FBF93E4ULL, 0xA332B3EB5A957BDBULL, 
            0xF04DE718AC9880C8ULL, 0x5C372939F52910D3ULL, 0xC1992D52C49A989DULL, 0xDE3015AD23AC498EULL, 
            0x5BDE4E2D8426D5DAULL, 0xFA589848A144E264ULL, 0xA90C22A62D57C59FULL, 0xEDA3CD11DAB64B85ULL, 
            0xA279159E8EE19F08ULL, 0x853898A2C1942AD6ULL, 0x23BE25BEA96A4EEDULL, 0x23A06A18B0A6EE55ULL, 
            0xDAA4364169E3EE7EULL, 0x108D79E144B115A0ULL, 0x5D932D5B735E3AA1ULL, 0xADF215CE8CE71C0CULL, 
            0x46DEAB143F3D3846ULL, 0x3F620E54D7910F57ULL, 0x89228BF11FAFC19EULL, 0x8A4E9DBAAC6A2782ULL, 
            0xDEA68C94DB9F63B8ULL, 0x00EE72F112D704CBULL, 0x359BA0D17F6704E9ULL, 0xC0F6533C64A9CF60ULL, 
            0xC875DF6A96C9FB3DULL, 0x0D867D2D7A586ACFULL, 0x5174AF0187653F17ULL, 0x312C6C5C96EDF19AULL
        },
        {
            0x1A8873DC8ED13AC2ULL, 0xCCBF14D4F13FBF90ULL, 0xB87DEF96AA5872FBULL, 0xCC7527F9AEF2FE0AULL, 
            0x0424B7ABF3851B47ULL, 0xC6895B6517F2E5E7ULL, 0x9F39D8898590D1DAULL, 0x0D3606844328089EULL, 
            0x949A8AE82880199EULL, 0xC7019927CF59BE79ULL, 0xC98CBEA217C7878CULL, 0x12821FA5A7705F97ULL, 
            0x952E76E258202A7AULL, 0x0BB5434FC05D3434ULL, 0x056F2518B433BA07ULL, 0x3F294B569F19DDD4ULL, 
            0xA5E48E75584A1298ULL, 0xF7F887767B84FC85ULL, 0xB05BD8277D4531BEULL, 0xD5155045F85B289FULL, 
            0x8B5CA6DD938EDD84ULL, 0x35D7C9DB90C16D62ULL, 0xE07FF7706B033B29ULL, 0x35862D633CCE187BULL, 
            0x4E5F1B96F79B63A6ULL, 0xDA64CB614D4117D8ULL, 0x87CB5928BB05BAB0ULL, 0x68A05AD2A0703D5BULL, 
            0xA17B74157184870AULL, 0x2E42659534A22C50ULL, 0xA4BB53543E726A95ULL, 0xE5928FECEE970972ULL
        },
        {
            0xA6F74330848F0E21ULL, 0x08143B592E8074ADULL, 0x4EBD002A76663605ULL, 0xC8E022D252CD9FE1ULL, 
            0xC2DE46ABD05D784BULL, 0x95B89E416350583FULL, 0x36E0C952BB8BF9E8ULL, 0xE1F285F1218976ECULL, 
            0xBA4084135FB9EC5DULL, 0xA1E7357F5816DC6AULL, 0x1B22B1F0E2E38361ULL, 0xF105975F6CCB095FULL, 
            0xA904367E16518B81ULL, 0xB3243427210A9803ULL, 0x1D02448410154639ULL, 0x08A122F4E9993595ULL, 
            0xBDA37E2563961AB8ULL, 0xE3BFCC27409E6882ULL, 0x3236455FC102E05AULL, 0x065076FF12C605A0ULL, 
            0x7EA45A2D55853CCDULL, 0x5DFF8ED625BDD0BDULL, 0x978494792AAF269AULL, 0xEE7966E62422DFFBULL, 
            0xE05D7FB88D29324AULL, 0xABA6E8B30EEA96F9ULL, 0x8D99B399104E5856ULL, 0x67F76D1ECFE2978FULL, 
            0x09A7B80F416D262CULL, 0xED775C63A5138851ULL, 0xF88F5715E5D5240EULL, 0xAA187473EF9EDC9CULL
        },
        {
            0xB854812F89FCF5EEULL, 0x615A46F1478605F6ULL, 0x8E4DF6377905452FULL, 0xCD23F1A44182E5DBULL, 
            0x9B42EB4616CE2CC9ULL, 0xFF9F5B93B54E0EF8ULL, 0x1C56A3114783D61FULL, 0x5D94F1FB8F1D3052ULL, 
            0xBA4774C1BF8F9AA1ULL, 0x867D38D08CAC8420ULL, 0xAA00361DF2A82E8FULL, 0x6A4E6F0FB900305BULL, 
            0xAA87E579479809FAULL, 0x931628A98DDFF792ULL, 0x746A5A8FB93EFC35ULL, 0x7CC069719DF24D05ULL, 
            0xA52D750A653B5BE2ULL, 0x515A067A2956FE80ULL, 0x8A03249BCA2AF6A1ULL, 0x2586B65141209416ULL, 
            0x0236D138215C2D1BULL, 0xC10632C321840EFAULL, 0x71173AD61405490CULL, 0x4EA562F64E5D9659ULL, 
            0x8B8330F951B52DA7ULL, 0x2FECFCF5CFF2401FULL, 0x0815C51CEDC81019ULL, 0xA4B7C153C58AAE6EULL, 
            0x3080CA8772315BEBULL, 0xEF81889FDC705E73ULL, 0xB37E90CB12A94966ULL, 0xEF44212783DFEA87ULL
        }
    },
    {
        {
            0xA51964B7A1CE9E82ULL, 0x4D974F98E9C11F53ULL, 0x030CBB25B2EB6714ULL, 0x9E9A68A6C036AEBAULL, 
            0xE2AB606134D462FCULL, 0xE123073674943C9BULL, 0xB5B0D6855429C99EULL, 0xB4C43FD6F22DD9DAULL, 
            0xD7714001FD417619ULL, 0x29BD9A4E601E25FAULL, 0xD035C2847D09AEF6ULL, 0x5D9E73DD59C3211FULL, 
            0x6C60E7EAD63B1305ULL, 0x92193E526556B235ULL, 0xD85351002C45347AULL, 0x922C28BDE2A6FEC6ULL, 
            0x4EBAA1F4CD9E93FCULL, 0xA643FDD5628BEA8DULL, 0x297CF52D047E372EULL, 0xB79D788B23CA5002ULL, 
            0x32D51741C820C31BULL, 0x3BE35E499DD5464EULL, 0x85396D802190113DULL, 0xA1504EE0A55570BBULL, 
            0x99B7B3C87E5B32DFULL, 0x7AEF498BC6CEDB20ULL, 0x09DC7B2D9C3BD6D4ULL, 0xE4A26D8C373FF971ULL, 
            0x568EC08DDA41C14DULL, 0x110014D4321DC923ULL, 0xF18BB45CEE86B8E8ULL, 0xDD038C06DED533A9ULL
        },
        {
            0xAD8ACEDFF1028C98ULL, 0xEF9ECA6828135B2EULL, 0x348F3ACDD64A36E3ULL, 0x9843CF0B35289D2BULL, 
            0x7313C4F92D70CD86ULL, 0x4A902B09DF811358ULL, 0x972DC5E3CEDDC134ULL, 0x733D9A8A1F63E3D8ULL, 
            0x43D1FA7861A0D5F3ULL, 0x9105D8583EBE0759ULL, 0xBB9AB9074FD4609CULL, 0xCB4E75938DAC0D23ULL, 
            0x531CA5D111975851ULL, 0xBADDADFE1B7FD4CBULL, 0x3AE7C77789D4A7B4ULL, 0x078FAE07FDC341EEULL, 
            0xCAF5CB41CAF68464ULL, 0x907B56FF1CAD4F5DULL, 0x57BBF6898401D3F1ULL, 0x3B5CAC9323AECE6BULL, 
            0x793DF107AF0A7271ULL, 0xA80B7F3DE39F733DULL, 0xC5B8FA4088E1FBBBULL, 0x4143577FCB5FE38EULL, 
            0xFB611D2961EA4B33ULL, 0x46EA63F80C5510EDULL, 0x1419A722006434B8ULL, 0x971D0A95A8EBA098ULL, 
            0xA3424DBC43557DC4ULL, 0xE4114405F5597F01ULL, 0xE753BF7761634B65ULL, 0x6BC0C40F5F8015E9ULL
        },
        {
            0x942601449CC57066ULL, 0xCD4F0EB69612E231ULL, 0x4B922FAD54FD32E6ULL, 0x98924804C959F75EULL, 
            0xEDAAEC06F9F6A182ULL, 0xC86026E00E28A225ULL, 0xDDE321D974CC43BFULL, 0xED19B6898360BE35ULL, 
            0x9C6A480E2703F895ULL, 0x2E37301F28190ADCULL, 0x229E31BD661CA574ULL, 0xE37F976D5CA51A60ULL, 
            0x7592029650F6872BULL, 0x811444E2FE97F9D3ULL, 0x9A128DF4F33F078AULL, 0xE47A246826996D1FULL, 
            0xD999BCC4E571B4C2ULL, 0xA7E643BFC1DA3771ULL, 0xE882F624DC4BE06BULL, 0x89123CB79F79FA66ULL, 
            0xC06A9ED3D16B81D3ULL, 0xF366BD1C4EFDBC53ULL, 0x4608F0B3BB509EFEULL, 0x0C2FE2D6E511EF09ULL, 
            0x8E3924A22CEF4868ULL, 0xB36D5F10EE360DF8ULL, 0x20D89AB4D166CC1DULL, 0x5BB5061268E55047ULL, 
            0x1E033BB87C75CA5CULL, 0x77B7889EF0224141ULL, 0x9328818D9203D0C3ULL, 0x2426C6DCC6754444ULL
        },
        {
            0xAD684C6C1BD3097DULL, 0xAF2959A910DD2E74ULL, 0xBAFB5CB9843596C3ULL, 0xF418212FD43E49D5ULL, 
            0x7A9D1536C084D8C1ULL, 0x40E7C666F61C20F4ULL, 0xEBC8E20B081310CBULL, 0xB62DBF42D07C7346ULL, 
            0x25DE6D4FF8A45CC3ULL, 0x99D2373D264CD9B2ULL, 0xBB221D7406C8B986ULL, 0xF3865F816C3E6712ULL, 
            0xC8AAD04854223CCDULL, 0xC3DCC98EB4D02002ULL, 0xD8B1BEC07E994425ULL, 0xAD1AD6EC61F9714AULL, 
            0x9D5C82DB15243EDDULL, 0x779C232134B93E48ULL, 0xF38AEFEACE2A3145ULL, 0x031167D0A2266215ULL, 
            0xA8D197F5B20961EEULL, 0x3FAABC2B8F63A020ULL, 0xCA98F023173F9E4BULL, 0x236FCCF874E5781FULL, 
            0x38A420B4C1EE4446ULL, 0xEFD0A17D6E2AF62BULL, 0x192E01DAD216AFD8ULL, 0xB6A0F51C93EF4038ULL, 
            0xEECD9CA3261CA03BULL, 0xC91996C548A8B44CULL, 0xE42C0A73172E748DULL, 0x314502BE8964E4A2ULL
        },
        {
            0x5733A850C1D722DCULL, 0xB4B67456DEB2204AULL, 0x0765B0EBAE604EA9ULL, 0x795016EB1B09BC40ULL, 
            0xBA070AA9ACF8FC2EULL, 0x0D941BD2E8225520ULL, 0x95CCFC7B775277A5ULL, 0xEA11459DB46AEED5ULL, 
            0x08A1BD80FB322DD0ULL, 0x72A26E62954249FCULL, 0x2164C8177B3E3C40ULL, 0x277F1BD37976F884ULL, 
            0x1CD0012963F79FDBULL, 0xED2A1EB405F4A727ULL, 0xDF10790392F147F4ULL, 0x8D4C4746F4A25D82ULL, 
            0xDACD869A45B2785DULL, 0x9B75A63AAD537732ULL, 0xBA069AEBA94B5DEDULL, 0x10A45DD1139ACDDEULL, 
            0x7373812BEC8382B0ULL, 0x561C898FACAEFCAEULL, 0x020F5FD82E2E28C1ULL, 0x200E7BE96BD8AB85ULL, 
            0xFE2CD20AFD0594A3ULL, 0x56FD64A95CB7C415ULL, 0xA999DAD0D329B53DULL, 0xDB1DEE020BED1F80ULL, 
            0x17BF30C2D70F7B53ULL, 0x5E391AFC45C65313ULL, 0xC72BD89BF3976194ULL, 0x3625C287C38A03FFULL
        },
        {
            0x710173D93BFA67B0ULL, 0xE86C98D6B54F2221ULL, 0x36744966C1A5A92DULL, 0x4980EB3F28198FA4ULL, 
            0xB8B8B70FB2D78985ULL, 0xF49DC78135437EDAULL, 0xF232253527981DBBULL, 0x1A49D375A35A22FAULL, 
            0xFFD421723F77CFDDULL, 0x010A6408BB8C4A70ULL, 0x5A9E49F574CA8BB0ULL, 0xE40CC1913DEF7B94ULL, 
            0x271BE167F0073150ULL, 0x3404B58D053CAF72ULL, 0xE95979AB36A902E1ULL, 0x78C665B518C9FF79ULL, 
            0x0E91D6BEF14FAE92ULL, 0xF71E61D34B2AEF38ULL, 0x79B6489517C5ADF5ULL, 0xC8DE1ACF288C8734ULL, 
            0x09D587A2D3F22AE7ULL, 0xF4170AA7EE25B054ULL, 0x4CE5ECB545DDF20CULL, 0x1834665AEACE5437ULL, 
            0x6931E26ABBCF80C9ULL, 0x1B294942653EB1A5ULL, 0xEA64CA530259713DULL, 0x8974051034BF8195ULL, 
            0x4F31CD778127FE6BULL, 0xACB13BAC7086BE86ULL, 0xBD76F543429494A5ULL, 0x471CF00037615A41ULL
        }
    },
    {
        {
            0xB92B95088DBBD510ULL, 0x47A76B9C5BA6E57DULL, 0xD01353781776DD3BULL, 0x6ABE4FEF70DDFB79ULL, 
            0x9DB965AA527A3098ULL, 0x3C4DC463D7570464ULL, 0x9BE4EB6D1E646B7FULL, 0x387197CF43103703ULL, 
            0xC81F2F826962FA30ULL, 0xAFEE1CB808CDF872ULL, 0xA8D36906DF78F680ULL, 0xDF33DFE2DE5B9A26ULL, 
            0xBCFE51411F954612ULL, 0x04C1CA006D291E99ULL, 0xB276B763F122BA02ULL, 0xB14158BBFB320A40ULL, 
            0x5D9A9B9979F3D38BULL, 0xB039D2AC4DFEF164ULL, 0x734E2AD77A58396AULL, 0x0188ABDAE7E05E8DULL, 
            0x2935B84A967DDAEBULL, 0xE8F417A537481413ULL, 0x5AA59822082E0C15ULL, 0x1F88656146FB1295ULL, 
            0x6CBCA50B381FCA7EULL, 0xEF6F4CC11550F093ULL, 0xEADDC61CD55E7FF4ULL, 0x2BD09C45857D9ECDULL, 
            0xE2BB7E93E124B427ULL, 0x6642D8559E330FA0ULL, 0xB33CFFE69D7A5813ULL, 0x3B3BF94451EE04F8ULL
        },
        {
            0xAE67A2E9BCC0990CULL, 0xAA8E5B5DB829560CULL, 0xFA57BC3E6DBC2A79ULL, 0xC11FEDA0189F7095ULL, 
            0xCB45FB9BA74E06A3ULL, 0xE5044E5B4CFFA567ULL, 0x8907560F643D0A51ULL, 0x117F8D7F5C4B7CCFULL, 
            0xFC637F106EA964FAULL, 0xEA4015AC47F1A560ULL, 0x63945F58B40C8AAAULL, 0xB1B905BC1DA4581DULL, 
            0x48DFEDB9B1E5E179ULL, 0xEDF531AF3E034C8EULL, 0x05F9094476085D7BULL, 0xCAF4750A0C315EA1ULL, 
            0x75FBFC27535E631FULL, 0x836E1BCD2D735BBEULL, 0x0FC5413A8C63497EULL, 0x9A4083225D6C87F4ULL, 
            0x08E47B6B4406521FULL, 0x87C0B5DE7E13DD08ULL, 0xC96B30763A8FC32DULL, 0x9CF7641DB56DF92BULL, 
            0xC46192FF9E2B5A18ULL, 0x5202ED4EDB03A9F6ULL, 0x19C0D6633D78FBEEULL, 0x203B8BF1F7F3D1DDULL, 
            0xFAD1B6B6B25356E4ULL, 0x56DCA3DFE6FD07AEULL, 0xE5C61C8946E8FB46ULL, 0xF78B41179BAA3EE8ULL
        },
        {
            0xB9E2D918E19D21FAULL, 0xE6B0CD1A193A9A5FULL, 0x4ECE1A147901D399ULL, 0xA303422FB46E2842ULL, 
            0x88C139577D54B228ULL, 0x4C4998B145C90FC4ULL, 0x411CC0E35C16202AULL, 0x5AA8755532EB2E1AULL, 
            0x323EC3BBC6B9325EULL, 0xC83EDB76D01813C2ULL, 0x80D898BEE5CD419AULL, 0xC52B6945B96E292FULL, 
            0xBEB57AD11B16511BULL, 0xFB7717BA9FF7EA94ULL, 0xBE2120958BEEA987ULL, 0x29758890BDB32135ULL, 
            0x96E9CB18C39326DCULL, 0x81F44869B3369C2CULL, 0xB7109D7CEB29CA78ULL, 0x777808AE09C5662DULL, 
            0xFD2613208A03D40CULL, 0xC99BD278C17442F3ULL, 0x0690B1C95B8F89D0ULL, 0xC680070BBD7A0AD5ULL, 
            0x063B6424EFF96857ULL, 0x7AF5DF5E68FD21C8ULL, 0xD2FC16F7557C66C0ULL, 0xEFEAFFA3995C1721ULL, 
            0x932EC80E8EBBA9D4ULL, 0x842036DC183697ACULL, 0x1040C93DEF1E4D4BULL, 0x09A33A76BDBE025BULL
        },
        {
            0x9FCDB22D1CC667A4ULL, 0x1CD4EBE6BBED7130ULL, 0x13D2E7FC8CDD36E4ULL, 0xF1C4228001DEF7F1ULL, 
            0x63DB7A1757B8971EULL, 0x45F218892F587DB7ULL, 0xD467418DB806989DULL, 0x89079085D6EBF949ULL, 
            0x3360795A8F97D934ULL, 0xE91BBE8FE0A48C9DULL, 0xD4F8A3AD461F4C8CULL, 0x2FDAB2869DCCE6A6ULL, 
            0x7AFBD2CD546B6C57ULL, 0x6FD216A6ADE3B833ULL, 0x8F599549B0E6394FULL, 0x1B98AA7B616BF341ULL, 
            0x3D59799132C44842ULL, 0x1D908C8A61B25AC6ULL, 0x4A4F8F2559600C74ULL, 0xE06232D1179C1D81ULL, 
            0x0C4B24E217356F96ULL, 0x4CE337F4316A8B54ULL, 0x1116B2B03337E26DULL, 0x0CB0D028CE8F1DA8ULL, 
            0x9F1E8499F99B0C9FULL, 0x06D6B4F2DEC6FD45ULL, 0xF665DC9FE7344E3FULL, 0xC7BC3BC6A45CC577ULL, 
            0x2C0910AEA44BBA51ULL, 0xB6E4D6558A6F5230ULL, 0x6F44B9A681D491BEULL, 0xC9868799E27EECCAULL
        },
        {
            0xEA177404F82AC3D7ULL, 0x0BD13836A5B2A4B7ULL, 0xEBCF7FFBE68147F5ULL, 0x5879DE883BDDD1FDULL, 
            0x96E55D240D5EA07AULL, 0xB9327AA682190C3FULL, 0x684A9BB77F4823DDULL, 0x58135FC44EEE5E6CULL, 
            0x6D49C47666D2B452ULL, 0x711BED9222F1200DULL, 0x319F676ED3DAFA9BULL, 0xA25400A4989320A3ULL, 
            0xF6612ED5703D9BBCULL, 0xF83A96C97757B3BBULL, 0xE3B6B7B080E04D8EULL, 0xA942B34CF60B411EULL, 
            0x3D54218C2736C34EULL, 0x611D4C2BEDCEA6E5ULL, 0x0FD51FD5EDA6482FULL, 0x44E77BF2275BD3DAULL, 
            0xE50EE1EC6DC1A914ULL, 0x43A4F09B6A7BA433ULL, 0xA260F2C823EE605AULL, 0xA93A49CE2E08E035ULL, 
            0xFA5BA5DB18B39B5AULL, 0x14B0615D706BAF40ULL, 0x217E8E4AF01DA6B7ULL, 0x7AF0F51F94E836B5ULL, 
            0x0D8CB6AFD8D647E5ULL, 0x7658C50F42627E08ULL, 0xCDAB1BF334552875ULL, 0x5549D42D7B0BF8E5ULL
        },
        {
            0x3D588A7841DC5DB1ULL, 0x3026AE84D33E59D7ULL, 0x269D1607ECB40949ULL, 0x62D326D14D6B91F7ULL, 
            0x74C21CDC06A2CFF5ULL, 0x98D06C6E56987458ULL, 0x509101EB35AEF6BAULL, 0x6B005012BD7CCAD7ULL, 
            0x45CF22D0631D0107ULL, 0xCD73F618B10DBD9BULL, 0xF8AC880CDF0787DEULL, 0xC62AE0A69374BA20ULL, 
            0x61F7C0ADC555F5F3ULL, 0x63162988CA82DD1DULL, 0x1F565686C143827DULL, 0x7E5592B119A75B14ULL, 
            0x19903C99B190CA03ULL, 0xF54AC93E312187EFULL, 0xD3CED9829AEEEF9AULL, 0xCF8469F739F4CF2FULL, 
            0x4B8F41E19C512C25ULL, 0x3852145A999C47FBULL, 0x2F22975A0A511617ULL, 0x2CBA39F904493181ULL, 
            0x30BE799F0768411CULL, 0x88C522D2653FB69CULL, 0x01702B6EAA737450ULL, 0xA2D29773AE9458D0ULL, 
            0x1D98EABD0DBDC98FULL, 0xB4D7C6004E7DE199ULL, 0x1ACEEFF0DAA32DE0ULL, 0xD31947B049E96F67ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseBConstants = {
    0x26B54BC72B11A41DULL,
    0xFE60E47D5AB11A33ULL,
    0x786B99963908D726ULL,
    0x26B54BC72B11A41DULL,
    0xFE60E47D5AB11A33ULL,
    0x786B99963908D726ULL,
    0x7EFFA4284595E04EULL,
    0x11A0489518B8F5E7ULL,
    0x3A,
    0xE1,
    0x5C,
    0xEA,
    0x08,
    0x14,
    0x06,
    0x98
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseCSalts = {
    {
        {
            0x698B6243B6707538ULL, 0xD390881E077EC307ULL, 0x7C4BBEE2E922B267ULL, 0x6464DEC749D975B9ULL, 
            0x8189B96F1D58BA9FULL, 0x84507709E57E1728ULL, 0x8B1B01AD58A6060EULL, 0xBB494A1071468023ULL, 
            0xA6FDBAA9915F1B09ULL, 0x30C71681F693E650ULL, 0x80319D92A7E0F029ULL, 0x2E3B41AB450D6E95ULL, 
            0xC1E752C09CE328B7ULL, 0xF2D7DEB429D7B3EBULL, 0x247C5779B77CE031ULL, 0xED7B4F401CD5800FULL, 
            0x4485D1E583185F49ULL, 0xDF05BA4501D8DBF0ULL, 0x8E81B9B96C2133ACULL, 0x12DBE45E430A67F4ULL, 
            0xFFB154FED4ED2D49ULL, 0xCBBFDDE3A9E47D1EULL, 0x7D266445439E6C4FULL, 0x1E65A94FAF6CBED7ULL, 
            0x8AE604E843C0A0A0ULL, 0x032F8E1D31EB988DULL, 0x960584F990018D39ULL, 0x000981B1E8AC5A6AULL, 
            0x7990775D559485B7ULL, 0xF225995D049E84B8ULL, 0x2CD963DC8A9D4E3CULL, 0xFB9039CBCD88306FULL
        },
        {
            0x605AC5E6EE84F00EULL, 0x5F469B48FB938785ULL, 0x5EBE90BEEC9B17D5ULL, 0x09A84CE047BC8848ULL, 
            0xEC140BD867B1A402ULL, 0x789071C808D0ACE1ULL, 0x78A69DEFA4A3539DULL, 0x7A0041A223365FF1ULL, 
            0xF82EF62831CDC6A2ULL, 0x0E498336C76D587FULL, 0x20AEC46D39BAAC92ULL, 0xBDB5991126BC25F6ULL, 
            0xE8EC9F05620A7B43ULL, 0x5B79FF1116DC2330ULL, 0x98DBE743F2F322A6ULL, 0x6F8C0CAD9A3591A4ULL, 
            0x8D8C8923FE827229ULL, 0x26DE51D220CDF2A0ULL, 0x1647FA69086B9839ULL, 0x796F8DB485DFD684ULL, 
            0x91FDC828A2AFD6F1ULL, 0x380B6B236B356DEAULL, 0x66E31A0A36961EBFULL, 0x938DC7CCAF5FA7C9ULL, 
            0x1955876FF00C8CB7ULL, 0x22985D4876D340A5ULL, 0x3AAF39F4D60D1E76ULL, 0xFE21ED516D44CD97ULL, 
            0x4C7D1A394D9BEC96ULL, 0x2677E4B1F08427B3ULL, 0xDCCC7AB93C910DA1ULL, 0xE2C62F146AE5F8E0ULL
        },
        {
            0xF254D921D2940659ULL, 0xB69672E738E67EA7ULL, 0x03D977F044B2BCD7ULL, 0x99E7C97393263B08ULL, 
            0xD7E9E3739CBEDA3FULL, 0x3EEFAB19BA25F138ULL, 0x25556A2F92BA71CCULL, 0xD8699CC8C792AEBEULL, 
            0xFFD6735F6B6A6AD8ULL, 0xF8CA759AE590E503ULL, 0xCD45EFEB27D847F4ULL, 0x3A7400F9A266BC60ULL, 
            0xA83BB3E77C853B93ULL, 0x3E947DE6247F0778ULL, 0xE5927EAF7BB05828ULL, 0xD26A5E60B91A0C2BULL, 
            0x9DB77976AE256DFBULL, 0x1A96E4368FA0A4D7ULL, 0x8D29E1F760B32EABULL, 0xD0A665E47E303C9FULL, 
            0x7C31EF789A6AAD86ULL, 0x51D77B92DBC8657AULL, 0x68E5409D9733C871ULL, 0xE0836C54F4BDB968ULL, 
            0x8E286371CFF11F61ULL, 0x2B4FF4E9FC8A2242ULL, 0x71D44D7FE017AD8AULL, 0xC6EE3C7E11F7E82DULL, 
            0x1B3D1F78F495B31BULL, 0xD2186A818ADC1D18ULL, 0x802935E1C66AC449ULL, 0x6E0E328BC5781F84ULL
        },
        {
            0x3BCB6920CF5B596CULL, 0x8F43BD4BE58DECE9ULL, 0xEE40A4A0FD57987AULL, 0xE3B53522DA4991F5ULL, 
            0x0FAD41964374AD57ULL, 0xEA57FF8091B9B9CFULL, 0x5247E13B6B9BEE2BULL, 0x5C983673E0F4A1E6ULL, 
            0x1E8BB4875B9389A7ULL, 0x9ABC0397AE383FE7ULL, 0xF421DA9AEFCD2092ULL, 0xE5D14B8A3D2ADBA5ULL, 
            0xDC2697370CB2FC88ULL, 0x22893DB6EBCB6B00ULL, 0x176CA2D78B626C3FULL, 0x92FFDA7F7A689B88ULL, 
            0xD238E67CE75D7A78ULL, 0x7C5AA483D2A219DCULL, 0xBFB1749591E3DA0AULL, 0x8637EA5EA0B6FD01ULL, 
            0x0A44B7DB66CE21ECULL, 0x2D68CB58455F5E5BULL, 0x7E78CD48AD999817ULL, 0x2D99E35FB2876FDDULL, 
            0xB73ECE74D3F56881ULL, 0x8EC2240A930DC6CBULL, 0xA2F72C5BE50DEF72ULL, 0xF479B61F4B1C84A2ULL, 
            0xAF64363AB078AD0AULL, 0xE787B6A60A4816CBULL, 0x9C48E1DC5E3B5AF2ULL, 0xAEABA19C91D8E2C9ULL
        },
        {
            0xAE3F2EAA0A45B220ULL, 0xD5B4447195AE13A2ULL, 0x4024296BC28DE060ULL, 0xCCC277675E805D14ULL, 
            0x1B9F887E3BD1DBF1ULL, 0x9DF6C24D6A6A7079ULL, 0x29C67C6364EAA8E0ULL, 0xCB1962989824A0E8ULL, 
            0xE86EC2F4B297B8FCULL, 0x5F9D324F08C1C496ULL, 0xE5A88FE3AF6083FFULL, 0x407EC698BDD1B953ULL, 
            0x259070D214AB8F1CULL, 0xEC5C41819B7E84B7ULL, 0x3AE287E27B57C0B4ULL, 0xEDB59D8366CF7379ULL, 
            0x79C2B95DAB3D449BULL, 0x0AE84A5EACD7B99FULL, 0x4CD204B95C247E52ULL, 0x7ACC6EA5C4433698ULL, 
            0x1498AE03095C0942ULL, 0xE57DA00EF028C3C5ULL, 0xEC830C09B5CF0779ULL, 0xE2EA43AB4075A3D4ULL, 
            0x325A2CFBC03CAD03ULL, 0xB20DC1E18A8D307DULL, 0x930541ACA65345C7ULL, 0xCBA58B541D0158F6ULL, 
            0xBDDE2AE4EF466C5BULL, 0xE22ED182F0384C69ULL, 0x63129033F6D3154DULL, 0x924A49CE1886F1D6ULL
        },
        {
            0x094CD8C6F29A4687ULL, 0xED299AE16D67C58DULL, 0x61131A169BEF57F3ULL, 0x569E025B324C6916ULL, 
            0x3AD645246829CA2DULL, 0x2A529965E96DC91CULL, 0x95A0813A48A71EDFULL, 0x71F9934B65C9DC81ULL, 
            0x041D24B7BE2567E2ULL, 0x8660402D3E03CDF0ULL, 0x31C8542DB232650BULL, 0x8DBED5EEBF475CBCULL, 
            0xC14EA7CA4BECE84CULL, 0x5809B21B5C98494AULL, 0xF7CB27129777A276ULL, 0xDF1B47555FAE9FC4ULL, 
            0x77C4AF957700FFFEULL, 0x3F242FFE550DE545ULL, 0x12A1364869E1B9E8ULL, 0x1E3507155031ED4DULL, 
            0xAAACA77E0F54628FULL, 0x05B685C367980951ULL, 0xFD988B0264E8DB09ULL, 0x7578EACA54BE0770ULL, 
            0xEC29AE9D40377BB3ULL, 0x38BB5B73546B35B8ULL, 0xD6D9D528FDD19A87ULL, 0xC8B45895E91827E6ULL, 
            0x1A2AE7799A078EAEULL, 0x85D2F10D3E17DEE3ULL, 0x514545D1527F680DULL, 0xF48F30F8950D68EBULL
        }
    },
    {
        {
            0xE5BBB1441CA7FEA2ULL, 0x5E8A326B0B6DB902ULL, 0x7FF783AF50813E0FULL, 0xFB6C4E10AD2A0E6CULL, 
            0x597FFD3FCF89D38DULL, 0xDCDACFDBE82E6E1BULL, 0x0D86728313948977ULL, 0xDD2C23AA0724F414ULL, 
            0x72209755D81F4100ULL, 0xC18337E45E147D03ULL, 0xCF3CFAABB3D15B05ULL, 0xF546AA6CFED64477ULL, 
            0x1486BD6A95169003ULL, 0x36065223BF9B2535ULL, 0x98FCEA9C15B2F97BULL, 0xAC0EF0CAE0377899ULL, 
            0xA04EF0F6BE68EA51ULL, 0x60A4DFF64FF5A036ULL, 0xA87519B6FDBB0320ULL, 0x3D984B131328684DULL, 
            0xCC3E37CE9D45791CULL, 0xA31E798CA495B735ULL, 0x204BB1BF18BD9B15ULL, 0x2B52D333F073BC10ULL, 
            0x4D873EB8DA23A38FULL, 0xD1829F17D5B15677ULL, 0xE69033B10B390FAEULL, 0x4726FCA5D1DBE31FULL, 
            0x73499BD87383D421ULL, 0x2637D3F2CD664FF7ULL, 0xD63B0510577C431FULL, 0x9C798DAA36996E5BULL
        },
        {
            0x7F58915E7EA51FE4ULL, 0x04A1B96B9340693AULL, 0x7BDAC0EE24FAF406ULL, 0xF4FFE7E0EFF68735ULL, 
            0x8B7CC96CC362F076ULL, 0xCAB4684A78C360AEULL, 0x9F5BFF01DCC2B322ULL, 0xE47C91C576221222ULL, 
            0x463C1014499082AEULL, 0x7673076A9435B40DULL, 0xE31823FBB549301CULL, 0xCE1FD050A6B9B3F8ULL, 
            0x8D3D24A93D5E1149ULL, 0xAFCB20F5EE77D0FDULL, 0x9153701DDB8BC1DBULL, 0xF451C7D2EFD1B546ULL, 
            0x818241A27938E9D3ULL, 0x589BEFD07654A3CAULL, 0x8B8B984B5592341EULL, 0x773F10707660F1B2ULL, 
            0x7F85C02D1A7EACA1ULL, 0x493EB2865E2430E4ULL, 0x3B0F0362EE44E9C0ULL, 0xD58F8BFC0B3554FDULL, 
            0xC46386130A3DFAB6ULL, 0xE4441BD96697F42DULL, 0x14173A48A222DED8ULL, 0x9E15ECCBB9D24686ULL, 
            0xB97EBD60AD4D8E7FULL, 0x494743040D254BADULL, 0xEB02DECC5A4FC1A0ULL, 0x2C2CCDC7DCBAE8C2ULL
        },
        {
            0xF76135BB008FD41CULL, 0x16A179E63855C372ULL, 0x8B33C0B2F9A254A9ULL, 0x931E08F3A945B511ULL, 
            0xA60AA1C973C3E6EBULL, 0x08363D29D056F5FAULL, 0x9B2336167F3FB61DULL, 0x571FE43C0E6C575AULL, 
            0xE9DEE5A14E955B7AULL, 0xA6781D64C0CF0FF6ULL, 0x65D5313769A73DBFULL, 0x7DED18A27F87CAE2ULL, 
            0xC3077BCC868D56A3ULL, 0x4F1AF89638F1CB2AULL, 0x18264A1CE050DADBULL, 0x245F074175B312C3ULL, 
            0xAA460D23C319C205ULL, 0x3AFE59ADA8A2CC30ULL, 0x09F8C07A1C42678FULL, 0x7F0DA8D092A1E931ULL, 
            0x2AC0E9C7EF4BC83EULL, 0xDB38D403EC213276ULL, 0x09827AF24FDF3A8FULL, 0x092B3074300316A2ULL, 
            0x24EFB79F02496282ULL, 0xFD6E281E38C5A2DBULL, 0xE46D2384022C5189ULL, 0xEC61363356B45E94ULL, 
            0xDAD48795E7619A0EULL, 0x0DA5F04F5F9C17E7ULL, 0xE1A148343E72802EULL, 0x8F6D0AA2F3DEDD09ULL
        },
        {
            0x22FBA524DDF994EDULL, 0x9FD1AAB71E034973ULL, 0x679CEBC8513CBC29ULL, 0x1EC21847DB758356ULL, 
            0x5139BCAE57C4A707ULL, 0x8EF3B810E97B6B38ULL, 0x59C5443078C77FFAULL, 0x808A0DE2EF495FA8ULL, 
            0x4EA93B0E19DB6B19ULL, 0x92E37E0736B17311ULL, 0x2118A2A7606DFEFEULL, 0x73288860720068C6ULL, 
            0xE8F491FF84E1B65DULL, 0x651EC922F3C6E75DULL, 0x2C80DC4D041A96F3ULL, 0xDA20F99C5787173CULL, 
            0xCE58A714CDECC32CULL, 0xA4442877843A096DULL, 0x5FA4F479FDBE5AB2ULL, 0xFD64DC501E206B15ULL, 
            0x568C49CFF5AAD174ULL, 0x82FC3E58E1782C36ULL, 0xB97CD1645C9B928BULL, 0x76CEF368B0CB3565ULL, 
            0x5CC92F1E2B3E9BECULL, 0xFE972776F0062771ULL, 0xC3F288B41FCA2AF3ULL, 0xCAD4D7622C699568ULL, 
            0x9E486928B4FD7086ULL, 0x49596B55DC4F9BC5ULL, 0x4C16E6F00F3DDF7CULL, 0x7E95A1BFA05CA132ULL
        },
        {
            0x6FE70DBEBB9631FAULL, 0xD5003554C18B3122ULL, 0x39C2C8288EC0F4F0ULL, 0xD2BC7799C3ACDF27ULL, 
            0x2A38A06B30E9CB60ULL, 0x5F1C254E3F22757CULL, 0xFC7876EAF8982A39ULL, 0x1895B55E21D73EF0ULL, 
            0x2AF6CDF4DD793925ULL, 0x5365E0445BEA13C7ULL, 0xF35F75481BAAC2E4ULL, 0x3547F86889C74C94ULL, 
            0x96BB4BBFC8291EDBULL, 0x9008870A96AB43DEULL, 0xED36A3782FDC5362ULL, 0xE2232893496BF785ULL, 
            0xC158FCF7110937B3ULL, 0x6FFF565CC7A65D68ULL, 0x04AB8F42F2D5A458ULL, 0x08EAEF04BBB523E0ULL, 
            0xDE2293B3847D7B32ULL, 0x844C2B2DE9BDF29CULL, 0x73530B4ADD2FB2FEULL, 0x6007808470B5AD2AULL, 
            0x282A83AB4F08EE7CULL, 0xFF86EFA9D2ECD6CFULL, 0xDF0EBA497F0D77B6ULL, 0x42A76787585E51E1ULL, 
            0x0C2B6DFEFD6D62C3ULL, 0xB0DD926A8350D70DULL, 0x048811A2F0C59DF5ULL, 0x26E83A26236A6796ULL
        },
        {
            0x966E5173922F8BBBULL, 0x8A8A3630E5FA5432ULL, 0xAE647E09D02DE71FULL, 0xF2B8A228CDD27795ULL, 
            0x099B16D5071B51F0ULL, 0xF5B701259A785C84ULL, 0xBAB95EF27ED5E337ULL, 0x09B3E6E8213C3F7CULL, 
            0x632AACECF7060810ULL, 0x4082E41C1235F4F4ULL, 0x6E9A8F78FE9A8E96ULL, 0x7A79ACFB56F1D37DULL, 
            0x22E40A2AC2464DB5ULL, 0xB68BEFEF11535E81ULL, 0x55F04D229FB238A6ULL, 0x279EEA21E164A5F2ULL, 
            0x3DA6A6A0F6B2302CULL, 0x6FF654591E250DD2ULL, 0x06A5D81C6181B6ECULL, 0x74E5820A9986DD19ULL, 
            0x65836B06D5C1F5F4ULL, 0xF66F05489A131CEAULL, 0x6AAC6B19A311002AULL, 0x2F7882427E9CB071ULL, 
            0x708E0D05EF42F15FULL, 0x8D0644474C18061FULL, 0x5939520695612319ULL, 0xC4F5F2DE1B6A7EA8ULL, 
            0x0D3581AA0D85DFA4ULL, 0xABC64BE3BCD51F04ULL, 0x87D84139F872A07EULL, 0x0EB2B12476F25FD2ULL
        }
    },
    {
        {
            0x26976C3E63E81FB0ULL, 0x7997573EB267A95FULL, 0xBD2CB4EFAA559C7CULL, 0xF51ECFC8DD99A7BBULL, 
            0x3D767EBA5D6E2D8BULL, 0xC3D317F2AB7224ABULL, 0x5B7DCA76741CBF8CULL, 0x4216A0C6F49585D1ULL, 
            0xEE0351D1F64CDD6BULL, 0x6E256327FAAB0F55ULL, 0x94F2BF7DBBAA9A2AULL, 0xDC0B45CC7AD6307DULL, 
            0xD26684906C07470BULL, 0x655074154C6D2147ULL, 0x865FB5A9DDCB6050ULL, 0x168D50B46B1695EAULL, 
            0x5945535BADBB3129ULL, 0x13CBF56C2BB7D181ULL, 0x587DB43576DDF650ULL, 0xE70596BAD6B2C0C8ULL, 
            0x6CC9A7564A0C974CULL, 0xE4F59B4BD8FEB9BEULL, 0x349322DB1F80EE3BULL, 0xE036149304481B43ULL, 
            0x0E6402E7BAA8E245ULL, 0x6D9268BEE070696FULL, 0x8E7748E5B9E819CAULL, 0x5D5FF6597CF1C52EULL, 
            0x91050C1F20998A7BULL, 0x52C01178CAF28EE4ULL, 0xA7F33526C55A2916ULL, 0x7F8C531ABE8EA119ULL
        },
        {
            0xB4B807AC59D7BB36ULL, 0xADB4416CA59D5309ULL, 0x86C72E96631D3A12ULL, 0x264F77951B67AE11ULL, 
            0xC95AE61573CA73D6ULL, 0x867B78D83E8E1ED8ULL, 0x3D61619B058204CAULL, 0xE55E95841454E60AULL, 
            0x3DB7664944172049ULL, 0xABDC1719C2FFEF4EULL, 0x6928F89F30B20587ULL, 0xB51D9238F92AD172ULL, 
            0x4A115A738E4AE022ULL, 0xA5E8C1BEFD663E35ULL, 0x1DAF2B4D9E0C6159ULL, 0x8E3C052E65468587ULL, 
            0x79FC4B684FF9BABBULL, 0xD34E5C10D91B9657ULL, 0x4DAB86A0F1980A4DULL, 0xA833FE3A4347F6B5ULL, 
            0x1FA7135F9CFC27DBULL, 0x56CC52828DD4B8D0ULL, 0x0872A51979CBF92DULL, 0x55D5B601F28D0661ULL, 
            0x866E5D4BB56F45ACULL, 0x8084D79417238F24ULL, 0x2326A683315D0A41ULL, 0x28280240C54EA925ULL, 
            0xECC443F9334D6AC8ULL, 0x83FF4744738C1E07ULL, 0x5682A0A865A990A3ULL, 0x9B2C1158A3B16D30ULL
        },
        {
            0x668A2012D94433F7ULL, 0xFF22B0CE8D52DCF1ULL, 0x5ED8EF1223D041C1ULL, 0x88F865B5CE019476ULL, 
            0x524105AA6D14F485ULL, 0xC336346B3216895EULL, 0x6FD0472464C97906ULL, 0x59237282BA24599CULL, 
            0x974ACBE30B31E974ULL, 0xCB50432B9EDBD4F9ULL, 0x74441F0E91B10C6FULL, 0x7F803143EE34CC4BULL, 
            0xDD3BE1417ABDD2EEULL, 0x87F5343B933EE557ULL, 0x4AE02D9243B63294ULL, 0xD407F6C8BD4CBDF5ULL, 
            0x8BA64BB86BB0A1DBULL, 0x6EBFF3218F996475ULL, 0xE41C04B6E1448A5BULL, 0x9F47CB570954A8EEULL, 
            0x5518BEBB616D2519ULL, 0xC658893BC60866C4ULL, 0x25BFB62C24FD5636ULL, 0xE6BCAA3E8BE819C9ULL, 
            0xB83F8D20E6A1AD60ULL, 0x5E5DCA273C9F1162ULL, 0x4227C40127F73400ULL, 0x1F17EDEB41DC530AULL, 
            0xF9FB140200A391E4ULL, 0xC7EAC209FD1B740DULL, 0x89E6205D3BE09EE7ULL, 0x5A352E9034D0E6B4ULL
        },
        {
            0xB6133CD2339827AFULL, 0xB4AA7995E742EC3EULL, 0xDBA29BFE57F8A0BDULL, 0x3EB61DAD23A58CB9ULL, 
            0xD219FAC71F126008ULL, 0x1BF4B44A31714252ULL, 0xBE680CE74FF5E5EEULL, 0x7F8EFB0D2B855473ULL, 
            0xE83CFFAC392BBEF4ULL, 0xE08F5AAF7DAAE454ULL, 0x902ADA2623069C09ULL, 0x3EB63E47FE10947DULL, 
            0x050766460C80E9B0ULL, 0xBB94AC7E1B3515BFULL, 0x05476AEAD49C334CULL, 0x1111BEBA5328BF4DULL, 
            0x1793C47F85FA04C8ULL, 0x692A73CF82396A50ULL, 0xFD9B722F62CD71B1ULL, 0x948437ABAAF23A0EULL, 
            0x0E82240D2201015BULL, 0x9DC2479FF8E0F2BAULL, 0x0B89D97E4470D989ULL, 0x08BAD55DE452D41DULL, 
            0x672CBF72F445988DULL, 0x2BE8E18CAE163550ULL, 0x96745D46E972BF46ULL, 0xC66D64D7B189DC92ULL, 
            0xEA1A0D03FC6703EFULL, 0x7F20BF80AE9101D1ULL, 0xB705FA915CF37735ULL, 0xF6A2DC59254C29F2ULL
        },
        {
            0x2A02B78CF661605EULL, 0xDA2B603DAFF77F87ULL, 0x6FD35851F072A465ULL, 0xB2AA26927E82DAB8ULL, 
            0x0E4D84419073F966ULL, 0xB1E8BC65EBDE534FULL, 0x704155B9B91E7A83ULL, 0xD255793E22FA6C64ULL, 
            0x24835CB45A9A53B3ULL, 0xCDCF37264307437AULL, 0xB59CEAB611C3AF98ULL, 0x7989BC5AE82B42ACULL, 
            0xE943CD23CE530E7DULL, 0x04713055883809ECULL, 0x61F01232CE4F31A5ULL, 0x9FDD67B9D178120FULL, 
            0x1C24FFC40EF0B466ULL, 0x45607E4D4BC37021ULL, 0x628B3906A131E7DEULL, 0x13C211A71B2B3CE7ULL, 
            0xBFF770760854FA63ULL, 0x1F762B4A899EEDD5ULL, 0x4F3A1E39832AC005ULL, 0xC4CC5E8B09D2ACF4ULL, 
            0x009A0BE35FDFD0D5ULL, 0xCB003C217739C767ULL, 0xE2BFEA62DD10C419ULL, 0xE5DE131031C2D212ULL, 
            0x7F9D9DD861277CEAULL, 0xF231E37ECEB2D122ULL, 0x95828D2C710D5E57ULL, 0xAE66381534727691ULL
        },
        {
            0x771A3F1088ECC653ULL, 0x3AA7207E96AB3335ULL, 0x8CFC6139128A2195ULL, 0x7A1AE991D8924B1CULL, 
            0x84DF482917ACBB4AULL, 0x59F40B1B304455A1ULL, 0x83309DEB8FA6AD1EULL, 0xD37AAF9BB434AF5BULL, 
            0xDEF4284130534E66ULL, 0x11B2AEF33C494154ULL, 0xC51E93153ADF651AULL, 0x4C703FF2E6238601ULL, 
            0x8D719937A70DC517ULL, 0x563EF0228CAE9A5BULL, 0x5A6911A926EE508DULL, 0x1F2545963134E113ULL, 
            0xA9BFF7CB16E1D027ULL, 0xCF65A7211ABEBE58ULL, 0x0DC3F8F10EF4FCF2ULL, 0x1E5EE4B3EFC68243ULL, 
            0xE7CAD2343B939A8DULL, 0x6BFEE17EF9069107ULL, 0x86712323030547B2ULL, 0x44EEC985114FC334ULL, 
            0x1A303937A30C4173ULL, 0xB2E566FC076294F0ULL, 0xB5B41B63BB7E6E5CULL, 0xC06C037A39813B10ULL, 
            0x67C777E891A87541ULL, 0x80EA8E923B403C87ULL, 0x768A57882741F965ULL, 0xDF5DE6D9E13C08BCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseCConstants = {
    0x2F3D5061959C22F4ULL,
    0x7C6709477D5C653FULL,
    0x49472F41BC4C7B49ULL,
    0x2F3D5061959C22F4ULL,
    0x7C6709477D5C653FULL,
    0x49472F41BC4C7B49ULL,
    0xFA837BDE169DAC61ULL,
    0xB2AFD6B899229128ULL,
    0x79,
    0x0C,
    0x07,
    0x56,
    0xD2,
    0x62,
    0x4C,
    0xC5
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseDSalts = {
    {
        {
            0x2F180912BFE72A81ULL, 0xF186DC00BB65B107ULL, 0x2ADE1B9CA5F9A405ULL, 0x91F26C7D91FA4622ULL, 
            0xC9C6E9857CBBA01EULL, 0x9A52D6AD820A5056ULL, 0x23B7B47F04A5B798ULL, 0xA97A31BA4814AB4EULL, 
            0xDE110F30A76363CBULL, 0xF203006FAAA753B6ULL, 0xE0873C6FF5EEABDDULL, 0x6D5FD17FDE0B2A25ULL, 
            0x6DC6E79C337E0153ULL, 0xACA7D4142A7C4272ULL, 0xB58F462809E93E52ULL, 0x77E68C96E075032CULL, 
            0x328249F366419475ULL, 0xBB7A5D2AFB8B1159ULL, 0x035C0E9130D3F40BULL, 0x1AAD7C82BB55E835ULL, 
            0xC9853DC2F343B6B4ULL, 0x676F076B16FDCF3BULL, 0x967E14B62D6BCFC0ULL, 0xB95293637099A489ULL, 
            0xB9B5137A9AF63EDBULL, 0xD12ED01C2E5EF917ULL, 0x449A92C5A18DFC02ULL, 0x78997A0791D3BD47ULL, 
            0x11285A73BCD91BA0ULL, 0xBFF7D2A6F793773CULL, 0xCBB2219B707903BAULL, 0xA6AEB1169A9440C7ULL
        },
        {
            0xFDA8C5B2FF3E3E8EULL, 0x6D4406FD68FE06CDULL, 0xD68BFF77CE4DD6FDULL, 0xDEE0B8C0E992113EULL, 
            0xE40C2A723170E3CEULL, 0x3AD10A4B642EEFF9ULL, 0x2212BAE5533C0624ULL, 0x09362DD833D14263ULL, 
            0x2494178E1238890EULL, 0x161E8F7B38C7ECCEULL, 0x2EC862B115AFC778ULL, 0x9B70C64041B4A80FULL, 
            0x161DD72CF2BFC5D7ULL, 0xACB9D22B5AC1E059ULL, 0xDACEC29183F6726DULL, 0x538E3A907EB6B712ULL, 
            0xB55ED5AF29542F2AULL, 0x141A7C991005E098ULL, 0xC67BB2AA111A87F6ULL, 0x3EC3011D86B25336ULL, 
            0x8B58A234B5E4A1C4ULL, 0xF8C7F0AA19863D61ULL, 0x3B4559AB110AF6CAULL, 0xA7E7AA35066314DDULL, 
            0x4615F8B80FB6900AULL, 0xD28157865C4FBE72ULL, 0x57E2F65317431C05ULL, 0x930509F72774E744ULL, 
            0x1B6BA0305850AA9CULL, 0x1FD0A7181535293DULL, 0xC9C0C903967EDCA9ULL, 0x783C4EB598A02DA2ULL
        },
        {
            0xB271DBEDC2207B3CULL, 0xA3776552C572F77FULL, 0xA9FEEC569DFFDC05ULL, 0x44EFAB5FB4D75F2FULL, 
            0xABBCA490E242D99FULL, 0xD303A5323F62BCC2ULL, 0xBF049A9EB499E5C6ULL, 0xD4742B2D07DBC513ULL, 
            0xDB6700DF84C6AFCEULL, 0xF57C07DF0AACA2DBULL, 0x5D37AD2C73C0539FULL, 0x6B367FFB90B5566CULL, 
            0xB65D114D6546D4F0ULL, 0xC9F591E8FF7F4C6FULL, 0xD19ED0F985B0C381ULL, 0x6FF51B0D05EF6194ULL, 
            0xB527E2B1F0E23AC6ULL, 0xDE8AA8DC955192EFULL, 0xA3C3D94094BC3E7FULL, 0x27FD51BFB0891FC3ULL, 
            0x56A4D39985EFE34CULL, 0xAA20A63EF6C39650ULL, 0xAB5DF839B5F28346ULL, 0xDFBEAFFB92774A14ULL, 
            0x29B6439384F11140ULL, 0x74E22E8131FC2E07ULL, 0x351EE2C5E5163D67ULL, 0x317F563B8D63BA30ULL, 
            0x990A13690A8894EAULL, 0xB346849E4B6C8D81ULL, 0x6D01E3EC7C4173A6ULL, 0xB081DEE9E8E87F43ULL
        },
        {
            0x7FA48E22337F0BE1ULL, 0xE6007EBD97F06D0AULL, 0x80F2C91D32462068ULL, 0x0D5A453DC6BDFFB8ULL, 
            0x61DDEA2F1F9D700CULL, 0xFCDE35EFE67DCC34ULL, 0x76C4B303F440CAF6ULL, 0x3232E1DA08265ACCULL, 
            0x233791A8B945420CULL, 0xFECBACA163F6B96EULL, 0x039584E8B588A19CULL, 0xB07BF0E2B36A5F0BULL, 
            0xC8D45579C3AD9BB6ULL, 0x2DE9C3EA4952AEE7ULL, 0x7854FBF26A495FF9ULL, 0x5C8FEFAC6A3B5AF4ULL, 
            0x07623AAF8D2261A9ULL, 0x72DAA26BA4D8ADCBULL, 0xFF25C778EC3F153CULL, 0x5640B67B05AD632AULL, 
            0x25B04E7186B70F30ULL, 0xC3631B225420DDECULL, 0x12B8E77243A889ABULL, 0x13F68C82F68045E2ULL, 
            0xAC28FC660F260C08ULL, 0x556191760278380FULL, 0x7D40B52186779AA3ULL, 0xBBC91049D09C4294ULL, 
            0xDBA977CD697F2654ULL, 0x0FB19662746926F4ULL, 0x8114A2A67F030A6BULL, 0x18F76BEDDD565D9AULL
        },
        {
            0x244A1DBA08E5E998ULL, 0x29E6E52B0F21FA42ULL, 0xC514B04AD9FB44FDULL, 0x9B401A1CAA6D5294ULL, 
            0x49578B8DD047A17DULL, 0x7C3DF9258F975F93ULL, 0xF19281FA81976A3BULL, 0xA892F7509CF224BEULL, 
            0xD1791E2A150D5952ULL, 0xC1955BF0A35FB494ULL, 0x1F3E29883D570BAEULL, 0x0299954B7EC2ABBFULL, 
            0xE1AFAC27092C9122ULL, 0x693977BA4775460EULL, 0x5C91D55061B2BAEBULL, 0x86327F704F9FF8DBULL, 
            0xDCE20594F762B6B8ULL, 0xEF8799260B52B249ULL, 0x2CC82A0C4E857741ULL, 0x7464F6CE910C3CA6ULL, 
            0x74FD0D1A690DFA2AULL, 0x4AF0DB577DDF140AULL, 0x4D4D1352F6390D09ULL, 0xA1747AD192EFBB7CULL, 
            0x818CD0A9AA3B8155ULL, 0x98049A843DFF7557ULL, 0xB5A792FABF7F16C8ULL, 0x5DF8F6086778EFFCULL, 
            0xCC91E186883D9D32ULL, 0x3C24C1A8F0F7421AULL, 0x189D70A3DA147B00ULL, 0xE2AD01BD203571A9ULL
        },
        {
            0xD96905F8B809DBB5ULL, 0x98A2824067CC5DFFULL, 0xB0FEF62986760F4DULL, 0x3087FF01039E9D61ULL, 
            0x09DA8FCF196B3DAFULL, 0x5DE2D15277A48AF5ULL, 0x9D0561F196D48B20ULL, 0xBA16A28FCAFA6054ULL, 
            0x3B27D2BB5824FD31ULL, 0x2777A897F7D649CFULL, 0x9F26D59A19206725ULL, 0x572A929854DED1D1ULL, 
            0x5D3E6BF4B62AD465ULL, 0xED3ADA6DF6B6C66CULL, 0xEBC62CDD703DED34ULL, 0x8F8ECA204189BD91ULL, 
            0x2786C14E5AFFC57CULL, 0x0735E65C935B1329ULL, 0x3D4EC6CA03C4E321ULL, 0xC88921DD5EC085B2ULL, 
            0xDFB8094CB47D3E43ULL, 0x450B08D04B522C53ULL, 0x83E41D6981B968AAULL, 0xAA3FCC9314794D9FULL, 
            0x0EA150EBE3980C1DULL, 0x78C7C02D84008324ULL, 0x37481F65AFE6BC2DULL, 0x50B1C1F2B10F07C6ULL, 
            0xDF3B2497467DFCDFULL, 0xFA340A73A4C7EDA1ULL, 0x09180B0ADBF29A23ULL, 0x1DB2E70A3C5C6F2CULL
        }
    },
    {
        {
            0x896D2CB283F33879ULL, 0xC48389DA12652DB6ULL, 0xA3D84551FFC14927ULL, 0x7B0456B43D9B33AFULL, 
            0x7DC9D4E2C7F296B9ULL, 0x79C4A81B603CD868ULL, 0xD308128252CE8067ULL, 0x02A3ACCE6D4A0900ULL, 
            0xCE0FF2A828143822ULL, 0xDCE0C704A2ADC7E6ULL, 0x976BA902E46BC55BULL, 0x8B982A4D94FC707EULL, 
            0xEF277EC42859FA0CULL, 0x3E6E156FF1445A41ULL, 0xF165F12399EDDC0DULL, 0x522AB51C9C8E24B4ULL, 
            0x138708D947CFEF14ULL, 0x89C411F174827CEDULL, 0xCADA72984896C7A1ULL, 0xCC29638A3D6B16C7ULL, 
            0x8A287BAE095B55A0ULL, 0xD6C203C94A5FEBE5ULL, 0xF42713A8975DF68BULL, 0x6DE599306E33B91EULL, 
            0x12E26A468AF65EAFULL, 0xB98E1B1025F0405CULL, 0xCB768B2901F96DE7ULL, 0xD0A6B7FFBAE4AE34ULL, 
            0x6BBFB7A04CA0EA29ULL, 0xBE8BF1FF217DE37EULL, 0x6F53513E4579479DULL, 0x8C8557C55A855E1EULL
        },
        {
            0xEE1DAFBC66260BD1ULL, 0x574D5135D0B6B9CCULL, 0xF732A8B3ED1C7B7BULL, 0xCA14F0204A297089ULL, 
            0xF9E1D6F9859C33F9ULL, 0x2619DB911D9F7692ULL, 0x20C4F03EA912023FULL, 0xB40DF42495C870F0ULL, 
            0x7B110806A7ADBDB1ULL, 0x186C49190999744CULL, 0xF5AE6656EEF4B3C4ULL, 0xBF05151798778CF0ULL, 
            0xEECD1241CB703128ULL, 0x8DB1427D4AC6AAF0ULL, 0x5E569870CC682CACULL, 0xE5EE651EEC9CC41FULL, 
            0x843020A3EB4BBE6AULL, 0xB1335DE4FCA401C0ULL, 0x647AF28F9D354772ULL, 0x1723B81295158A08ULL, 
            0x2D664EA187EDC311ULL, 0x4EBAC8DC9E56ED77ULL, 0xBC4F87F9FA561EB1ULL, 0x6F50795393A389EEULL, 
            0xDDC4E58B1E8259F3ULL, 0xCDCBF38E738FC5C3ULL, 0xE798E02B128459CBULL, 0x73E7EC855B4F4E54ULL, 
            0x75B4AA6C329B2B4BULL, 0x556EC63F2B49C98BULL, 0x8EE28A4F8B25E441ULL, 0x26D00DE426C412B7ULL
        },
        {
            0xBF6BFF26E2652668ULL, 0x764C602C27E69F4EULL, 0x439D9E72AEA866FFULL, 0x516792A8D536D4B0ULL, 
            0xDE24D87B18247AA6ULL, 0x2DF5CA447932C759ULL, 0x02B9113A855EF2D5ULL, 0x552E3BA92FEE7BB8ULL, 
            0xA7401AD70C1C35CAULL, 0x2E7212F7F698883CULL, 0x69E1328FB166F65BULL, 0x4A500DE857655672ULL, 
            0xCC316BC451551C7FULL, 0xEE921F28075D3E5AULL, 0x8A708A8BB0DA6A3EULL, 0xEBB7339BEAF85130ULL, 
            0x5A511A0E24EE0A22ULL, 0xF8FD368F67DBFD27ULL, 0x17D2D0F8944AE82CULL, 0x9C9E2F6DE19C802BULL, 
            0xD1853DDFE5B34AEFULL, 0x7AD9418C0F823FA9ULL, 0x583EAC0EEAFA4526ULL, 0xE8B4E6A37D59A3C3ULL, 
            0xF6714DEF2563ED51ULL, 0xF360C2BE1AC64BF1ULL, 0x02A04B569DD0A70AULL, 0xBB39C5971C83A0B4ULL, 
            0x90BEF4BF1995E770ULL, 0x4997853AE21FC347ULL, 0x9529F92CCD69D2BDULL, 0xBC500A0BE1A858BFULL
        },
        {
            0xA6E4097D1D1020D1ULL, 0x3AC0A2E687EE9D05ULL, 0x5CEE6DDA782A5A39ULL, 0xB117E4812948B821ULL, 
            0x92FE2C91B7923483ULL, 0x2A1EC686EDA762FAULL, 0xC03009E539B418EDULL, 0x21529A483B29E4B2ULL, 
            0xB4DAA47080C26A41ULL, 0x943BC1054E1227F4ULL, 0xDA6680B9F53D0963ULL, 0xDCAB971B3D93BD33ULL, 
            0xB744C849C761DA25ULL, 0xFF8C830BA1C8854EULL, 0xAB098F27B0FA2A49ULL, 0x56C1C4708A9335FDULL, 
            0x5F23CE0E3D69192AULL, 0x542FC0954D57A621ULL, 0x5D95B9669A881014ULL, 0x32E66F565B8837C4ULL, 
            0x63B25D97969ABCB6ULL, 0x21DD135EA1779CA1ULL, 0x4EAB00CB675911C2ULL, 0x489D6375CFB2E1AAULL, 
            0x80F12DF2AFA8CB24ULL, 0xFF2ECA4E23B2E6DDULL, 0x9AF6BBD869D7402EULL, 0x698A1A43E9CA7A6FULL, 
            0xB6E54823F6F0A951ULL, 0x45645E114EA8981BULL, 0xDC35F3D9AF5C1E6AULL, 0xF03E4374BA0F0E9FULL
        },
        {
            0x766A22BB44125BD1ULL, 0xBE0BE8AD60BEECFDULL, 0xD578F66196C929EBULL, 0x70E3C02AED94EF0FULL, 
            0x29B91601C87E8A3AULL, 0xDD7F8B56254E4429ULL, 0x35D65CD612260789ULL, 0xE5DFCF08D6195218ULL, 
            0x0949DA2361FB3239ULL, 0x720E1ADA1AED7F8EULL, 0x058601D7F12710BEULL, 0x1E7700ECC44C093BULL, 
            0xD91D161E6E65FEB8ULL, 0x1F70D3B161369330ULL, 0x326C740C47DC61ABULL, 0xFD117CE102B1F332ULL, 
            0x00911BB979342C9EULL, 0x2C5023EAA749FD89ULL, 0x8C1EAF059C0446F2ULL, 0x3E1874076DB25A50ULL, 
            0x573DFA283ED8199CULL, 0x33FDE3F3D6FDD60EULL, 0xD9077913E7EABD02ULL, 0x9F31193B44646C57ULL, 
            0x021DE9A7E868E296ULL, 0x83C9ED21535B3926ULL, 0x17061DA94450E3FDULL, 0xEFBBA59C853581D9ULL, 
            0xF3EDB0EDB8DA89FAULL, 0x1B6AE22D57A52EA0ULL, 0xA1481EECA8D10886ULL, 0xF0E8880A9199D970ULL
        },
        {
            0x1B9B9B6334DB7517ULL, 0x2EBADED712D593DAULL, 0x3FF8A4E5CCCF2A76ULL, 0x2CEF31C0F9CCECD4ULL, 
            0xB366388843071B7DULL, 0xAA70487285BFA711ULL, 0xFE7A3F43CF15749FULL, 0xA174FCFC36A4F728ULL, 
            0x2CEE709812FF8F34ULL, 0xCD80624B38E929B3ULL, 0xC0A760EB2E2C91B7ULL, 0xE474BA4A3EF9A724ULL, 
            0x275165511D8BCEA0ULL, 0x3F417AA9530B2D77ULL, 0xB31ACC6292D0CE2EULL, 0x1CD0BD18A7D8C02FULL, 
            0xA41C98657BB90984ULL, 0x03BB663B0768E002ULL, 0xAC2D93BD7D88EB91ULL, 0x9752BF33B89FD610ULL, 
            0xB8C715CC08C72B1AULL, 0x9E51821291C5D988ULL, 0xFEF579E9B615F355ULL, 0x3D0060A328E1526EULL, 
            0xE53D08EACDC02182ULL, 0x8FB6A50663CC203FULL, 0xE48928DCA2FC4848ULL, 0xA75518CDCF138CC4ULL, 
            0x392F819D72E468B5ULL, 0xE1BEF84D47DFE83EULL, 0xBF8DE2DC91D6C3EEULL, 0x4E145B9BE8C2AB4EULL
        }
    },
    {
        {
            0x7142A35C9FFA6AE1ULL, 0xA7D5FC34C478B257ULL, 0xF12A6305231F1493ULL, 0x13BA46AA7D520AE0ULL, 
            0x798F3AD9DE686E24ULL, 0x9F73764E5FE86D71ULL, 0x8D268E5BBEB57929ULL, 0x6EECF7A1C9B6E7A0ULL, 
            0x7D56A13ADDC2BEAFULL, 0x7BDDE472D721CCDCULL, 0x127C31F01EDC2614ULL, 0x6E4C6E7C124379AFULL, 
            0xDAFFB15557FFA47FULL, 0x14E61F83A1B2B54DULL, 0x0BF51BF46EE6419CULL, 0x36ED7B76A3DC310EULL, 
            0xED46014165E9A4F6ULL, 0xEC46550D443D1C8BULL, 0x40DC53C3EC257350ULL, 0xC3EBC387FECF51E4ULL, 
            0x1370995349C3AE93ULL, 0x4B372124CF28FFDDULL, 0x27ED869ADC27C8E9ULL, 0x9C7D12A0519E79A1ULL, 
            0x3F026BF107747411ULL, 0x849E785B73C14388ULL, 0x4A4B05910CA9D3A8ULL, 0x7D3D089AEC3BEF90ULL, 
            0xE78A556B1D37CE6CULL, 0xC2FA19DB2A538975ULL, 0xDFC3D000F998A429ULL, 0xFFC57B279D65EC1AULL
        },
        {
            0x6DE24EA1EE25B8EFULL, 0x6937796509383008ULL, 0x7C36FF00629A06F7ULL, 0xC2859B9BDC83B117ULL, 
            0x06B3B6F1E26E283AULL, 0x8F684600FEAD8ABDULL, 0x197846E354169E07ULL, 0x8D5EACBC0ACEDCB5ULL, 
            0x9D8999B9A44E08D2ULL, 0x62DC44E386870882ULL, 0x9A67A7DBE1022115ULL, 0xC7D578E72EB55DCCULL, 
            0xA131B6DAE82566E0ULL, 0xE4B9227CA20F2C27ULL, 0x34AB19B48D7DF6A7ULL, 0x67CC76B19CD04019ULL, 
            0x7685EF4B6BB8B212ULL, 0x98DACF8BF018AA2DULL, 0xA20EA497AEA8B2A7ULL, 0x7F37EB5007F7347DULL, 
            0xDEC88A00F972A169ULL, 0x4E9740ED5A1FEA12ULL, 0xE67F0C4426647CB9ULL, 0x3DB0131126F8B737ULL, 
            0x55E19854D5C0BC7DULL, 0x2DD19D64B85D6C3BULL, 0xCB227889D3B4A349ULL, 0x4C0CE0DA6CB3F7ECULL, 
            0x368641E81C3C56EBULL, 0x5BE8A22DB79534E0ULL, 0x5260BB4CE3128CD1ULL, 0xB81C14EBCAF431FDULL
        },
        {
            0xD31ACA376DF498C9ULL, 0x1E64035B691F2118ULL, 0x82E9B68D33E6CCFAULL, 0xEEF98EAB90F7260BULL, 
            0xEB66EF823470FCF8ULL, 0x7EE5BEFC1916CFFBULL, 0x493229332C112983ULL, 0x13EA1A1ECA916C22ULL, 
            0x91B3E2FC2BD0CF6BULL, 0xB2B7361E9090090BULL, 0xF1065B93EF741A80ULL, 0xBD35245620FE2891ULL, 
            0x4580FD991D2259F4ULL, 0x238386D59DFEEBE1ULL, 0xA416C60498AC6E67ULL, 0x5A06FEB4CD94E296ULL, 
            0xC088ECEBE5881FDCULL, 0x0D1475BD9A2791E2ULL, 0x9ABC999DC6C3DB10ULL, 0xABBD96FA852C2E12ULL, 
            0x2204A7202AFA7415ULL, 0x5441EE839DFDC4D1ULL, 0x42953D9A3FE0857FULL, 0x2E9F238F7E7A8FE4ULL, 
            0x26DB0A73E3802E71ULL, 0xB86AF5C2EEF57AFFULL, 0x5B4AAD6DFF66D85EULL, 0xFA2FAB92CFD86961ULL, 
            0x8AC6D9E15AF1BD50ULL, 0x819949836F28B7CEULL, 0xACE2E8A30C495EE5ULL, 0xF8DD2CE9ED2A29FBULL
        },
        {
            0xF7690F14E9AC14F5ULL, 0x29E4725C85638686ULL, 0x2F399FF9E8B8A6B0ULL, 0x7969B337C938F340ULL, 
            0xD8C3D2F2EF0F072AULL, 0x3CAE99442C0A3A09ULL, 0x01D6C00F36FF260CULL, 0x0D6BA9CEE790E4A1ULL, 
            0x2B55950125F8C00FULL, 0xA9B3677DEFA3C003ULL, 0x4C5792367997BB6CULL, 0x9F3B615BC69C7070ULL, 
            0xAD52D52B3FD6E7B3ULL, 0xF5707643FC24FCFBULL, 0x2A9A34CD0F4AAC37ULL, 0xA8DB5AFE46B5442AULL, 
            0x9788D41622F79952ULL, 0x8618AB3705944F5EULL, 0x9984B859A9BB26ACULL, 0xAE239E6114FD80F2ULL, 
            0x14466B4073541B13ULL, 0x2940CC8F100ED08BULL, 0xE4245FCEAFA550B8ULL, 0x5533AC587BCE2ADBULL, 
            0x970498E43523C0B4ULL, 0xD7C2F19CDA037809ULL, 0x731A533A139C66F7ULL, 0x38EFE6FFB67734F0ULL, 
            0xB5EB47C2DF7692A6ULL, 0x1F174C56C44EA619ULL, 0x20F4373145EBB403ULL, 0xA0461FD6FC266263ULL
        },
        {
            0x858E8A5203A89F91ULL, 0xE33B45CF419A3C3EULL, 0xAA6915BF303AF2ADULL, 0xCCF45C0D2372790AULL, 
            0xA04B9135432D48B8ULL, 0xC8EA52EE61DFE0ADULL, 0xFE410BB87CB37551ULL, 0xEBE325D455C82041ULL, 
            0xC786D27138F85F26ULL, 0xB307C3A5B4D01A6DULL, 0x5E95E2D01875C827ULL, 0x2622E2AF6177B972ULL, 
            0xD408C79654AE4974ULL, 0xAE68E3E214FA8B2DULL, 0xBDAD1D07C45A79D9ULL, 0x84FDCDF8ED225344ULL, 
            0xEC1E11AAF88D6123ULL, 0x96F334FDC9876D8CULL, 0xA7608EEDF0E9591AULL, 0xD2D83AA038167CB8ULL, 
            0x08F13BCFB28A6AF0ULL, 0x2206BE753EEBDFF5ULL, 0xA5CB23ACF2C73CABULL, 0x557910E7BBF8E7A2ULL, 
            0xD1F290663D49111DULL, 0x07900C96039C5B76ULL, 0x2B7A168616019FFBULL, 0x390774F310B79417ULL, 
            0x976FEAA209E729F0ULL, 0xED2A59839C80D9E6ULL, 0x3CD21E1061E2F688ULL, 0x62721A576B6B937EULL
        },
        {
            0x046808EA6B693155ULL, 0xDF7F2029F3681520ULL, 0xCCB8EBB01CF07FC7ULL, 0xD0863E1E6B123B74ULL, 
            0x2B88BE1F66120AB6ULL, 0x7E42D61ED2BC7A3AULL, 0x5D4B1A7269343EEAULL, 0xA9567A2AB4DE55ABULL, 
            0xDB8BCB372B7DD8F7ULL, 0xE56A7C9271FDE5D2ULL, 0x90975B4CD35EA1FAULL, 0x4F97E2BECF8C7ADDULL, 
            0xE27112DFE8A00404ULL, 0x828487B6923616F4ULL, 0x2DB0FFB2FC2D38CAULL, 0x38DEEB8ABDB6B3F7ULL, 
            0xA1E03801BFD2BB5AULL, 0xD6D37B6A6C216259ULL, 0x509F375C4A282325ULL, 0x1960C78E2517AED2ULL, 
            0x8103635713894CF8ULL, 0xBE0E823C2145B12BULL, 0x1189E11D52697C36ULL, 0x9B870AB07F9DBB2EULL, 
            0xF314D7528421FA13ULL, 0x0EA377BB4E0EE5DDULL, 0x2E4D3F9E678F7BFCULL, 0xA871E93474638BA1ULL, 
            0xC8B0CAECAB565318ULL, 0xA6C2AE76ACE48E9BULL, 0x0CE2FF8C910EA3C2ULL, 0x016CA1CCDEE500C3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseDConstants = {
    0xDD03AFF6605A8863ULL,
    0x93EDEA97182426D2ULL,
    0xDEDA91F091EB0BC4ULL,
    0xDD03AFF6605A8863ULL,
    0x93EDEA97182426D2ULL,
    0xDEDA91F091EB0BC4ULL,
    0xA8E74FB34F53BBC5ULL,
    0x9EDE36B6B5D8D041ULL,
    0x32,
    0xD4,
    0x33,
    0x81,
    0x83,
    0x9B,
    0x6C,
    0xE7
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseESalts = {
    {
        {
            0x33C6FDFFD79B984EULL, 0x59F711AE14FF9C2EULL, 0x13CBA5129C03E19DULL, 0xF1C996770F11F9B1ULL, 
            0xE1E47A5DCE5272D4ULL, 0x3F1807B35DB6052DULL, 0xC709B1CE6F9B826EULL, 0x4278521F9EA89942ULL, 
            0x6BA1260017CCFBB1ULL, 0x5E94F74D56B35158ULL, 0x34A0EB9AAFCE7261ULL, 0x60062BFFD321AD4AULL, 
            0x7AC71B25CE0934FDULL, 0x88BCD64E4386195AULL, 0xECB05B065E4F441FULL, 0xD95CD7AE4F150BB3ULL, 
            0x3C267A3AC7836E72ULL, 0xE532A5B648C382A6ULL, 0x4AA7801B8AF5795BULL, 0xE2A156B5CE1FE1B7ULL, 
            0xC83E271FC6015671ULL, 0x1D1BE51ECD6754B3ULL, 0x4669958BAF460E64ULL, 0x761FA34964C5DB6DULL, 
            0x90A1D3862A165592ULL, 0xEC5FC30FE5DD5BC5ULL, 0xB1DAFCCE4FE7CDE5ULL, 0x7B5B2F53E866B5FCULL, 
            0xE2EF302818987BDCULL, 0x3D3B0999E05ABBB3ULL, 0x658918BF0E532419ULL, 0x91EEFF1E5D1F9824ULL
        },
        {
            0xB537E185ACF3D9ADULL, 0xDD8409161B2AE25BULL, 0x3C179D10A7DFD8C7ULL, 0xBA6B0D2CAF21AF8FULL, 
            0xF50D051AC3ABC29FULL, 0x7215389559A168D3ULL, 0xD59CE63372543AD0ULL, 0x3F3666947C5B53AFULL, 
            0xE2621CEACD5C6174ULL, 0xE979D7A987BC80CDULL, 0x3FB8C941ACB2706AULL, 0x2CEACF8FCB3515E6ULL, 
            0xC5D74FC4EEA37626ULL, 0x8937FD0A27D79A24ULL, 0xD732A25A6DCCB398ULL, 0x7E043A3957F84CBFULL, 
            0x6744E4713FD593F3ULL, 0xBC8792CD755BBA52ULL, 0x511FAC482F65DF15ULL, 0xCA583134C43BF2EAULL, 
            0xA820668128FFB129ULL, 0x79E75A6BAF80B5DDULL, 0xB97E32A83B7350F6ULL, 0xC90A44EE83AC352DULL, 
            0x801EBDAF0C516F8CULL, 0xE502B86E584F4A95ULL, 0xC480CB80233203C9ULL, 0x8F4E3DCF8D2A56CBULL, 
            0x7116E8640C8BB70AULL, 0xDACFEDEDA7873F07ULL, 0x9E0E8D6A41ABD42DULL, 0xE2D7CEB46473458BULL
        },
        {
            0x899361EA332AD389ULL, 0x51DC71F502184766ULL, 0xFAFA779BC8CF0A37ULL, 0xFB97832A2A4E4D1EULL, 
            0x1EF725926273BB6EULL, 0xC94920BDC3E80FFAULL, 0xFA86D4CEC2CD1B5CULL, 0x0AC8B8C1A351CBB6ULL, 
            0xFEB0B062A78FA365ULL, 0x7F447F097ABC794EULL, 0x0CED9228C2B60924ULL, 0xF9EDF9F8A3EB3DA8ULL, 
            0xB29EF7A7414D3F40ULL, 0x574A6496D7E44B68ULL, 0xF8D4DD89E629D448ULL, 0x9DBDF75D851374D3ULL, 
            0xC55A614D00A9D0F3ULL, 0xD50F302BC3552076ULL, 0x38375820CC27B963ULL, 0x55359A57CE224B19ULL, 
            0xB506A087F7EA015DULL, 0x6E0CBA540B76475EULL, 0x49253E6B55EB585DULL, 0xF9DEDB59BB83588AULL, 
            0x7DFE55E2E9A69332ULL, 0x8E17E721CEE43B86ULL, 0xA9F0CC87BDF4FF3EULL, 0xA6A82E9B1E97A6AFULL, 
            0x0539955B1AB44B34ULL, 0xC90C5EAEB7C2F176ULL, 0x46B9BB261100D898ULL, 0x9111C5DC148141FCULL
        },
        {
            0x64A1F412C62400F4ULL, 0x41BC60D61A8C68EFULL, 0xE5CBC57FC22511C5ULL, 0x6B29BEE91A739CE9ULL, 
            0x0FD678C9C3991A87ULL, 0xDCC68F9BDB46F2ABULL, 0xF18E2689F31844AAULL, 0xF462E5585A9DC105ULL, 
            0xFFF79639819F8199ULL, 0x0C3D069754D44C6BULL, 0x3D8013733B6517E0ULL, 0x2F82ECB80E912F6FULL, 
            0x207E30BB4443E3A5ULL, 0x17E7070EC3EA43D4ULL, 0x46763467446BE375ULL, 0x2386F8A92B70C8FEULL, 
            0x3EE7DC2AAD97C01EULL, 0xC612EAAA82DB60D5ULL, 0x65ACCA8ECA2A2DC4ULL, 0xE435032D664BE4B3ULL, 
            0x3AE4A88ABA159EEFULL, 0xC6C78D04B401A33EULL, 0x83F6B3EC138B4DC7ULL, 0xBFA9249F3572DF9CULL, 
            0x64C08ECBCA001993ULL, 0x8E05A3A282E9521AULL, 0x5960DF4E021E028CULL, 0x683DA5713F23FC67ULL, 
            0x2D72FF5CCC4EA223ULL, 0x390D441C7DBD187AULL, 0x09A72E29DF2C72D0ULL, 0x29C8B753C02957E9ULL
        },
        {
            0xA50805154F2E76E7ULL, 0x2037015B01960194ULL, 0x0820A333AEF36F6BULL, 0x629DB424DC4E0222ULL, 
            0x8FDF04FE65E78059ULL, 0x09E63762A3A86FABULL, 0x0A65E28F4CE9A1D9ULL, 0xC4DCA8353BE09A71ULL, 
            0xE0E4E6E2511A4887ULL, 0x94E37A14EE475866ULL, 0x5C355655F923E444ULL, 0xC6FD3ABDBC435A4BULL, 
            0x8757104746F2EA8AULL, 0xC267F094762DEB23ULL, 0x078C39699D82AC19ULL, 0xD5884A95902A1285ULL, 
            0x189935B2E73F8D05ULL, 0xA329AA6481D58AA8ULL, 0x89B091505753CC78ULL, 0x4340E9CF12214227ULL, 
            0x4EE55A8973AE2CD7ULL, 0xA1896E286742B48DULL, 0xDEA610FD8AB47ECEULL, 0xC69D93278DA294C1ULL, 
            0xB2ED51AFC9FBC96EULL, 0xFACA9873ED3C137DULL, 0x6DE04D134CFE5C84ULL, 0x75CE14B14ADDA9E7ULL, 
            0x4C812A0DE78C0B3FULL, 0x54EF8763549D860EULL, 0xEC1F433A1A4E88B6ULL, 0xACEFD16AE4C071E2ULL
        },
        {
            0xD83C58A2CC0A0E4EULL, 0xB76CA01A08EEEEE5ULL, 0xE10B13D4070A518EULL, 0x680D1A783920824AULL, 
            0x1F3617201E510E63ULL, 0x41F21B76C159A168ULL, 0x618DF275AFB4CCCCULL, 0x83AE6A9FB945B1CCULL, 
            0x733DB25F1C858B26ULL, 0x4BB7DD67C4000532ULL, 0x1F823E028D62AD77ULL, 0x5F5948AF586C236AULL, 
            0xF8C934D8295031C8ULL, 0x1A5883D2F3E65B7FULL, 0xDA34DA928EE84083ULL, 0xB59351F98D75ABFAULL, 
            0xDF3C8930C971FD50ULL, 0xFA1DE83F4EFB0EE4ULL, 0x52E63DABE14DC829ULL, 0xEFF24E77B58D85EEULL, 
            0x3DFC319967B7A454ULL, 0x47223B700C68549DULL, 0xD956524DD9C03307ULL, 0xBA88DF68ADEB7450ULL, 
            0xED11B8D54CCF0629ULL, 0xD0A7500C66163C3FULL, 0x57D5BBFB2597C104ULL, 0x521421D4F15945A9ULL, 
            0x5096C509650F481AULL, 0xD94C7A0132B43BCEULL, 0x3A91668F6C8CF807ULL, 0x9E77A042F6303E3AULL
        }
    },
    {
        {
            0x11DA8564D8482F23ULL, 0x5EA4877AD87270D5ULL, 0xB5EBBB9F60DB6E69ULL, 0x1A6CDAFF1AF8E47CULL, 
            0x201BE886DC59489CULL, 0x4F4F83284BC9AC14ULL, 0x76393290D1B73F00ULL, 0x637FE1FBAC18E450ULL, 
            0xEFC67B5D2EF4C0B1ULL, 0xD8E8277166EEFB41ULL, 0xB919C0377CB76271ULL, 0x863A11172FB44EBAULL, 
            0xFABDA6C86F30476AULL, 0xA9DA3384FAE7757CULL, 0xCB9621A96F47A1C7ULL, 0xF43E0143CDFC31A9ULL, 
            0x54876F9F273F0C49ULL, 0xC2B9DF1670B203E6ULL, 0x60199A923C7F67D4ULL, 0x931A21903428D0E8ULL, 
            0x64C6A533BF48BA6FULL, 0x70DE80BD51B7A6E9ULL, 0x10E9250397282615ULL, 0x00F362300EACA46AULL, 
            0xF0318D5D7C334A2DULL, 0x0F63F6D45D1E0530ULL, 0x79D7FE55761D6AFAULL, 0xF23DEF84CDD5240FULL, 
            0x5AACC8E6963938F0ULL, 0x2961D5270725E639ULL, 0x039DCFFF0451375BULL, 0xD6E1A827131DC69EULL
        },
        {
            0x225C168429D182D5ULL, 0xA7CF66BDF318CFBEULL, 0x65B005BFAE6318F8ULL, 0x26BD4A1823B677D0ULL, 
            0x1F86A3E7BDC6BD86ULL, 0x90B4C2625AF4886BULL, 0x15CABA4C43C53D72ULL, 0x2054D7C7AEC05AB9ULL, 
            0xC65181E48163A9CFULL, 0xAB830952C9A2D062ULL, 0xC9BFA4CBD12C3512ULL, 0xAF6A5C3C9700DD4FULL, 
            0xE2A0E9CCA55D5575ULL, 0x938BE7E8681AD73CULL, 0x7B1C651D9E16B382ULL, 0x3E621BE743E5E854ULL, 
            0x6E94C1DC57DD69F7ULL, 0xF5E274AE467FBE08ULL, 0xBF60198EFF75710EULL, 0xE24A3F671B7277CBULL, 
            0xF3BC44D973E15A4AULL, 0x110B312943281EE4ULL, 0x6D809B3671AC35B2ULL, 0xD642F831B07029B6ULL, 
            0x682ED5EF87503C01ULL, 0x1C52A8B4C78AB8F4ULL, 0xA282D1696573C818ULL, 0x19C3E9557FF62E6CULL, 
            0x2966DF7B92C3E1DBULL, 0xFE086FC1F17A2749ULL, 0xE4D0EB2695A2ABABULL, 0x0B27BEA0A0573531ULL
        },
        {
            0x7E89C5B309B765F8ULL, 0x64C7A7D8790A1204ULL, 0xDC90D30612863A30ULL, 0x1CA434E95B030F54ULL, 
            0xCE2E20B4E62E16FBULL, 0x389361EB97A2DB8BULL, 0xF52A91884DA8441EULL, 0xF82A4F495DEB4E28ULL, 
            0xF832FD5673776F4BULL, 0x49D6C0DC396605AFULL, 0xDCEB218667FFDCC7ULL, 0x2F876C8C44D664A8ULL, 
            0xB7F1E71BFD275233ULL, 0x8E2A7F9D247B6A56ULL, 0xC70609BDA7C5B91FULL, 0xC76E8B00EEBB235BULL, 
            0x4705CC9799585C5CULL, 0x44B9362F07DF1AA8ULL, 0xE536B57C25AA4EFAULL, 0xBFD26EF8E864187EULL, 
            0x24DFA6D30084BC24ULL, 0x9BB9DECA2F2A2946ULL, 0x1F31C1DA7CE9C2F8ULL, 0x9FA1EBE2C85B1509ULL, 
            0xC4A88A1E180F3D2BULL, 0xE7190FDA810CBDF1ULL, 0xE789BE7E800A6E4DULL, 0x127E877B4C029485ULL, 
            0x94EE0DC5961A5E6BULL, 0x513830CFC78B48D7ULL, 0x1D7E81F20EA8153AULL, 0xAD1E6D4AF9E1A9F0ULL
        },
        {
            0x5334DA875FA57752ULL, 0x3C5F153D900C8544ULL, 0xCDD79C4399251D19ULL, 0x733D22F0750DBA67ULL, 
            0x965223F02390D69BULL, 0xE26FDACC585DDC05ULL, 0x197A32D3E40A9126ULL, 0xBAB98284AF6A6809ULL, 
            0xBF04BBFB60556BA5ULL, 0x967DC4BA1E0B0F61ULL, 0xFE5AAB2F89FE74A7ULL, 0x1EB0F35D1010B83DULL, 
            0xC5AA306BD029E714ULL, 0x8AD40983488C3F51ULL, 0xAF4F4621D192C4C9ULL, 0x75DD9ADE13716C35ULL, 
            0x89B5844A4D602739ULL, 0x1CD519C4DA8B7549ULL, 0x5C49EF74E6F9651AULL, 0x742F514BF1DFE0C1ULL, 
            0x2B49D89F7C645498ULL, 0x8CFFE6633CEFE8F4ULL, 0x3AEB1D2042225534ULL, 0x901E1F039D2BC5B8ULL, 
            0x4135315670BA0DA9ULL, 0x14864C2AF38E4DE3ULL, 0xD2578068FD65777BULL, 0x57ECFE0D74A45F4DULL, 
            0x131305DFCFE1337AULL, 0x03B8C08538D14F01ULL, 0x476FD1FF1853E5E1ULL, 0xCA2FD0D6850524E6ULL
        },
        {
            0xE9D41C17B0B98D37ULL, 0xD6BB8CA9617E7205ULL, 0x804B4E6FB627696DULL, 0x9CD67DE254775BEBULL, 
            0xF18A3977BA38468BULL, 0x7F6422390E5C6F4CULL, 0xA6022FDEBE20BE08ULL, 0xF319034C79A97C91ULL, 
            0x3DD920C45A7B085EULL, 0x52B3FD5BE2FCD859ULL, 0x06F389E51A8CE5D6ULL, 0x966E4AE8CCCD7D8EULL, 
            0x482FEBE9C46732FAULL, 0x254B0E3D18D65176ULL, 0xA553415ADA11CB06ULL, 0x2F7C56EF21EBAD9BULL, 
            0xC74B2BFBE671D887ULL, 0x7B8CFDD107E4B6BCULL, 0xFAAACE018BDA9A9BULL, 0x0EFB6B49B10F4DD0ULL, 
            0x809271C6D2F7F210ULL, 0x1A982D3422DF8152ULL, 0xED6293D72BEFFCFEULL, 0x2D6948C472FA2EA9ULL, 
            0xF2A97A789E79061FULL, 0x38CE9277AE6B87FAULL, 0x45327DF9801B662DULL, 0xAFADD493EC48EDFBULL, 
            0x0E08C0C4188EB39FULL, 0xAF4548A081A53D54ULL, 0xAAD2ED2C76CAA498ULL, 0x5513B127386CEB93ULL
        },
        {
            0xF6A682FF05240AB9ULL, 0x448BBA07C8F62B5BULL, 0x8964CDF7F39C3AE2ULL, 0xD8E84415CE11CD5FULL, 
            0xD32E563C87C43DCDULL, 0x33FE37E22866284CULL, 0xE46D46A48365E295ULL, 0xF518B17EB87552F2ULL, 
            0x4A4FB074D35D787FULL, 0x4F1FA7C7CCB27DACULL, 0x4E092DCAF9E94413ULL, 0xDCDFCEB257A7AEDAULL, 
            0xF0E09816CE34CD58ULL, 0x89B189BFCF979E0DULL, 0x51954C6EEFF48B04ULL, 0x3C350D74F70AC45BULL, 
            0x68E9B55A121F5612ULL, 0xD6D078E0BD9DEA8AULL, 0x0445680FFA8F694DULL, 0xDC8850CAB3DC674FULL, 
            0x0266657661F73B75ULL, 0x24C0A187FCF8423CULL, 0x7208627E41DB58ADULL, 0xB5A8A7D7CE6B4C91ULL, 
            0xBA66435005E453D4ULL, 0x7C3F5475B34C862EULL, 0x7BED01B14C2B8CE0ULL, 0x2DA7E11FB1FA6B5FULL, 
            0xB0FC2B9266A1F872ULL, 0x363408870DC80FF9ULL, 0x5CA7E77CF98201E0ULL, 0x66161C7AE62A7B19ULL
        }
    },
    {
        {
            0x5106D47B64779639ULL, 0xB2C3105285F9A0ADULL, 0xE8826ECEFDE30146ULL, 0x6BB8ADD2BFE8852DULL, 
            0xE6E8E02170B8FDB6ULL, 0x1C7331146230354CULL, 0x1C6A307A89B9FE9EULL, 0x9A62026D6221193EULL, 
            0xFBEB41FB11A9EA36ULL, 0xEC43808F0F333B63ULL, 0x05E19A4804C1C5ABULL, 0x1D0186CDEB5ED897ULL, 
            0xB4A0B0A2287957ABULL, 0xB01B35B8C20E5176ULL, 0xDB9A8D486C0370E3ULL, 0x79037E8E5A60A839ULL, 
            0x5D151314C08C5424ULL, 0xA9DC049CC500175AULL, 0x9B1FC6B7C96A712CULL, 0x2CC87E2C6679C766ULL, 
            0xD7C109D5B20B93D9ULL, 0x889AEFBB870DCDDAULL, 0xE9AAEDA6E0CE4032ULL, 0x3C19DB159BEA663FULL, 
            0x3B6D0A62C76D98D1ULL, 0xBC90D60DD9DFC263ULL, 0xD6691FD91CD7F526ULL, 0xE60111607146B8ABULL, 
            0x56FE0A1946E86E2AULL, 0x080F9D509AB2597DULL, 0x3043834310BBBDD8ULL, 0xE4386B6C89CAA778ULL
        },
        {
            0x528B1B3834C1BA67ULL, 0x905B810D597B08CEULL, 0x0A6CD2F35C6A299BULL, 0x7842C6540CAA6373ULL, 
            0x80D8DA0EDF6268F7ULL, 0xF5A0941535715858ULL, 0xC926F98386ABCE6EULL, 0xE0F648A966F4F45DULL, 
            0xAD11A7C38B90D025ULL, 0xA632D2B081717052ULL, 0x5B63D6F57603359DULL, 0x736E199FF10A027DULL, 
            0xAA41AA6128D30121ULL, 0x11E068E700B1EC35ULL, 0x42F6800E99B71ABCULL, 0xDA0EB0F30F063060ULL, 
            0x4CAD03A1F05E0750ULL, 0x653AF97D028413E7ULL, 0xC4925AF4A861C45FULL, 0xE836C65512A3DFF5ULL, 
            0xC9037F66CC898A49ULL, 0xCCBFF47832F37DBFULL, 0xACDDAF418330DDE7ULL, 0x9F3128E330B4ED4BULL, 
            0xBAC4BD6BD8F491F7ULL, 0x9ECCF49AEC881DBFULL, 0xEE2401130E182F64ULL, 0xA5496149442D9171ULL, 
            0x73B5CABFEBED9DB5ULL, 0x35D6227471C9052CULL, 0xD93914D978760B9FULL, 0x7B5670BEE39BE2AEULL
        },
        {
            0x12CF1C6CAC2CEA17ULL, 0xBCC23D902680255FULL, 0x506DE57214B5F3EEULL, 0x5A9800806AA40B50ULL, 
            0xF2E1C8BBF0C821C6ULL, 0x077442E5884EE266ULL, 0x7382BA96026B4867ULL, 0xA5277D9462991955ULL, 
            0xC6F64909F76A6747ULL, 0x1F1E702EDAFA06A1ULL, 0xC4F123683C6AF2FDULL, 0x516EB699AE3A6CEBULL, 
            0x2C80FEF36AF7BE70ULL, 0x5F8C7E014C20BB76ULL, 0x4E562F861F3CA5BCULL, 0x2F0776A55C1E39A2ULL, 
            0x96554AF017EB343DULL, 0x46F2F541BC56F2B5ULL, 0xC3C747AAC9C34068ULL, 0xBF91E627D7C4BF72ULL, 
            0xE7A7E0747DF6E574ULL, 0x365ADC1F8FCF9E35ULL, 0x77B9AF5C10CB7C91ULL, 0x6299BC2C5F01E027ULL, 
            0x2E502289D2D64B45ULL, 0x9CD35FD98D305A47ULL, 0x5DA17B03D00B97C2ULL, 0x29CF37C003C8B634ULL, 
            0x8B9885F624836BB5ULL, 0xD745B6ED6B6E85F3ULL, 0xC343C13181DE3749ULL, 0x8D8026922B0F8F47ULL
        },
        {
            0x6A300CE2203F18C6ULL, 0x04F17D2C7B1E1BDFULL, 0xE60116675171068AULL, 0xDBD7C9962ECF87F9ULL, 
            0x161E199398EE5418ULL, 0x9E1AE0955C85179CULL, 0x03B10FACECE13703ULL, 0xD8BD2744044D8C35ULL, 
            0x637D1D32E0049092ULL, 0xDB95719DAF7637B3ULL, 0xACFE8B18D62D9CB9ULL, 0x9BAE73A04D4BE658ULL, 
            0xB9B978CAB9FB60FDULL, 0x6BB7B10545B42A80ULL, 0xBBC620979714BEF9ULL, 0x9DF53F9A9561693AULL, 
            0x347F361F2E6F8FF5ULL, 0x18193EC082FA1766ULL, 0x1ABD583C0B45D322ULL, 0x95D8DA403E1F02F0ULL, 
            0x3D5E26576A61AD7AULL, 0x282B0EFF55A49FAEULL, 0xA614EC0DE0301F20ULL, 0xA2D0F8DB39915F37ULL, 
            0xDF2232C952B292B6ULL, 0x404C9F48939ABF6CULL, 0x25D227CB84B1704CULL, 0x62F539C618E94C12ULL, 
            0xBA6F92C56854ED63ULL, 0x196F119669FC4849ULL, 0xDB18F4B2B47C6829ULL, 0x3170837042384A67ULL
        },
        {
            0x0DDD94EE139A6938ULL, 0x6E8FA27DFA88BB87ULL, 0x0064FA06AAA7E643ULL, 0xB3BBD2795CCAA026ULL, 
            0xBFAF69E53EF76433ULL, 0xA5134EDB87F16D19ULL, 0x21F91D063B9707E2ULL, 0x1B2B63AB7A8B3F2AULL, 
            0xCECD6894E7C8E505ULL, 0x05159293781D946BULL, 0xFAB2BAD84A045FC8ULL, 0x9A7630121137BA74ULL, 
            0xC88491192BC8419BULL, 0x1384B7C8EDD3764EULL, 0x5D0A448AEF1BFBA4ULL, 0xD3049FC3850D0FF1ULL, 
            0xD4A5D6D0C8D11DE6ULL, 0x2DC4A01FB00D91F2ULL, 0xD12AAC86734F9AA7ULL, 0x0377B83CC0C85C3FULL, 
            0x7393FDC97CD1EAF7ULL, 0x8DBAA4F2F1559492ULL, 0xC2D76F49057C1C5AULL, 0x04C984650AAF9B28ULL, 
            0x951D9E85072173F9ULL, 0xD4F1F3B13CC31FDFULL, 0xD080A91876C335E8ULL, 0x84FAB26418CF7FC8ULL, 
            0x1A3553609B49E30EULL, 0x0CFCDE73FE61A874ULL, 0x012D8028697139F5ULL, 0x7269864D1B1D5FE6ULL
        },
        {
            0x429645F5B96B5BB3ULL, 0x24AA6BAFAE92F2D2ULL, 0x831AD3D5B5661E39ULL, 0x6EDC537210336701ULL, 
            0xEB9DC5F831CDABCDULL, 0x0F7DBFAB8E47EE0DULL, 0x3EEEF24DD3117E2DULL, 0x27043D79F77D18E2ULL, 
            0x7B8CA956F2A68DBBULL, 0xD364088500CDD954ULL, 0xEDCF39C8F42F1C7CULL, 0x5D224B9422A3AF07ULL, 
            0x2B7CD9C32A80A33EULL, 0xFD764DEB508D7496ULL, 0xD9DA3724072D5EF4ULL, 0xD7B5B6A9DF400A94ULL, 
            0x129624AE9C521452ULL, 0x1A2B1410CF9826F6ULL, 0x0A11A0899FC9A995ULL, 0x1C81FB54ABD133CDULL, 
            0x005C57C4C1EA7E22ULL, 0x93F622E850D546CFULL, 0xAA814ADC0E706CBFULL, 0x7511D5C318F58ED9ULL, 
            0x9FB3722C7950C7F4ULL, 0xA8BA8EE9B1B41494ULL, 0x060725DBEAA0D094ULL, 0x08054383DBB3FBA0ULL, 
            0xD264DAB9DCB05EF8ULL, 0xA412C84D7F11231EULL, 0x4762B7D7F15B78F2ULL, 0x4CEE3B6570B09B14ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseEConstants = {
    0xF1D84004AA5CDCC2ULL,
    0x37E4A2AA442F81ECULL,
    0xE2306F9422E9D113ULL,
    0xF1D84004AA5CDCC2ULL,
    0x37E4A2AA442F81ECULL,
    0xE2306F9422E9D113ULL,
    0x97D88CFCFC3285C8ULL,
    0x9039B8237651FE71ULL,
    0xE9,
    0xEE,
    0x96,
    0xB7,
    0x7F,
    0x83,
    0xB9,
    0x6D
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseFSalts = {
    {
        {
            0x4E5AA24EEEB8803AULL, 0x701468200DCEA455ULL, 0x986FEFCCD018945CULL, 0x1D751EDA74708D34ULL, 
            0x1E1A879A0456C2E6ULL, 0xD5740268103F2C96ULL, 0x87DEBFC246DFC2ACULL, 0x7553A6033E2AA940ULL, 
            0xCE7CF0C6F6C0016FULL, 0x40173E16A2333F42ULL, 0xE3DDC08B2C98CCB4ULL, 0x55DCBE2AE2F0F196ULL, 
            0x54D671F43B164CC5ULL, 0xA2F1BB7D3E944BEDULL, 0x339F5900AA0EB511ULL, 0xD411ECB97FE483EEULL, 
            0xF82896B349E2DED1ULL, 0x25E1621F8662E6C9ULL, 0x82A942CD924E40D8ULL, 0xD6A8D6AFA0B35001ULL, 
            0x01723D1665DF17A8ULL, 0xDF33BEFB6C1E8920ULL, 0xA9659C5D226CDEE9ULL, 0x72F834655D394248ULL, 
            0xC2F072C8D2589F3DULL, 0x569B63E306A8E625ULL, 0x763949F5ECFC6652ULL, 0x9B2D751CEEDE00D8ULL, 
            0xF929B0371BDF2E8AULL, 0xC8A1012EB497D2B5ULL, 0x17DFBA2621EF0A21ULL, 0x28D07C8F8FAD858BULL
        },
        {
            0x989947930E17AC84ULL, 0x3705CCD09488937DULL, 0xD67DD12941B3C657ULL, 0xBB7189D8248752C3ULL, 
            0xB99BC865C9A51800ULL, 0xE0DF106C4EFFF751ULL, 0x9FA1B71DFEA82ED4ULL, 0x29A97650CD3663FDULL, 
            0x2A4FCFC73AAEBFB7ULL, 0x03187352F1EBBEDFULL, 0xD4A277B36785BD38ULL, 0x22004614341D941AULL, 
            0xE5EC6C3833948861ULL, 0xEBD8675D5126B05BULL, 0x72C2502C93B10D50ULL, 0xAE1ECFAEEE89E888ULL, 
            0xA487FC216A5635CCULL, 0x8EB01609EBC94FCDULL, 0x10D71BEE0E0BDDA6ULL, 0x61822A69496900B5ULL, 
            0x528540D870411024ULL, 0xA9DECC964EA7A9F2ULL, 0xC886EA07D582175DULL, 0xA162E2B6B4DAFE0DULL, 
            0x06E63F092B613277ULL, 0x290BEFDDDAA3095FULL, 0xA5AA5CBD2F5DF315ULL, 0x560094D533EE7011ULL, 
            0x5D3C101D5F6FA0E2ULL, 0x4B48255C8E1754E2ULL, 0xD513B25055D3A864ULL, 0x1286B65521C6187AULL
        },
        {
            0x033DAA0A3839A99FULL, 0xE6641B92C641EACEULL, 0x4E59FC8D45A31DD3ULL, 0x2BE7DFEF714B2C9FULL, 
            0x8D6CB45AE9E7E6B2ULL, 0x8F276F00BAB69E32ULL, 0x6C03BD2CCCB944E2ULL, 0xAC6C15BB29859F8BULL, 
            0x7954DE42286B7ED3ULL, 0x192B49D8488B3067ULL, 0x7404D7E075D1035AULL, 0x3AB7ABAD4BC66704ULL, 
            0xB84FB9E9D072C30FULL, 0xB65AB97577678E9BULL, 0xA30220A02AC9186FULL, 0x25726C5796290B95ULL, 
            0x52B7EDAF65390BD1ULL, 0x9603734FCD632231ULL, 0xEEFC4F930D798466ULL, 0x453454B31615FC36ULL, 
            0x4FE4168180E92F06ULL, 0xC26ACCA4A624C4C1ULL, 0x14FC4BA8A1B37E48ULL, 0xC8CD53A09F046658ULL, 
            0xA7BB8FBE794B4D58ULL, 0x4B9C762CA5DF321FULL, 0x71B24EC86081061FULL, 0xC3767EE09D1CAC3EULL, 
            0x084F2196C3A4BEABULL, 0x4AB16914BDB5743EULL, 0xCE41921C0A4638CAULL, 0x04CE75439B8AC0E5ULL
        },
        {
            0xE63800721692CB65ULL, 0xE930D189582565D3ULL, 0x610136FCFD938563ULL, 0x77C53CF0731DC393ULL, 
            0xD6F2F5150B9DF175ULL, 0x89127345B6920055ULL, 0x4034521AAB445D85ULL, 0xC67D12FA19A46C6CULL, 
            0xFE5A316ED35B79D6ULL, 0x185B456511A1564BULL, 0xDA95B1BC296EAB75ULL, 0xC1E493CBDEA3C5A8ULL, 
            0x5F4C15BE4ECA15BEULL, 0xAEA2C1784A1588FFULL, 0xE8685B5FCA1BC011ULL, 0xCFC436DB094CC299ULL, 
            0x37CAD9B5A71072ABULL, 0x6412808A9A2B921DULL, 0xDF0DA6F4B2D6D8D3ULL, 0x329E8F04E851E96EULL, 
            0x4785E237A3E96C90ULL, 0x75604BF1C4069DC6ULL, 0x3578C01ECFCA3A22ULL, 0x8D2569D01D28A605ULL, 
            0x7BA0E4B37F2E8F21ULL, 0x3330666E56023510ULL, 0x5801F1B9CDA048D5ULL, 0x0BAF19581E7328C1ULL, 
            0x634B56FE07C12279ULL, 0x2C34DA93A7C484CCULL, 0xC9171D6C790F6255ULL, 0x18094E44FB491516ULL
        },
        {
            0xEC1787AB0EB45A73ULL, 0x6598B9B6B776F853ULL, 0xA606E8E654A80743ULL, 0xB94BB11F450E2DD8ULL, 
            0x0EB28E325401FDBFULL, 0x8185978F672F7838ULL, 0x67410414F211C8F0ULL, 0xF220AD1E706C8763ULL, 
            0xC0F77138E3DDAAC6ULL, 0x36E10775CDBC985FULL, 0x7D0A8F0FCD18A77BULL, 0xD6A51F8428BF3B4DULL, 
            0xCD847971902C1D6CULL, 0x2A5D55484EC73E97ULL, 0x38B663D33FFB4867ULL, 0x719768D32D76ADFEULL, 
            0xEE88BFAB8FAD4BBFULL, 0x25F1E4A944F39B00ULL, 0x90EAA06879FE391DULL, 0xA5EDC9ECB63FA218ULL, 
            0x3486D6BDF8D3F789ULL, 0x44D27096F3019215ULL, 0x7B556CFC04FEAEA7ULL, 0xC32888166262C457ULL, 
            0x976E17E078C7957EULL, 0x7A088F566843A995ULL, 0x8342E01C208B78B4ULL, 0xD80C46257A5F148CULL, 
            0x8A39AE0215AE41CEULL, 0x9A71BBAAA12EF8CBULL, 0xC927DABE6A3C87DEULL, 0x708B8496F12E67BAULL
        },
        {
            0x0671EA71B41CE5AEULL, 0xA59AD0738AD19EF3ULL, 0x8AE76784E20987B0ULL, 0x7B0ACB775D47DD89ULL, 
            0xB2FF76D310221405ULL, 0xCEDD2FBDBF44EB20ULL, 0x953A57E7F701A204ULL, 0x5F995D7DDC512E31ULL, 
            0x072E36117A8295E8ULL, 0x53B3A3ADAD41E29BULL, 0x06117F548609A2B6ULL, 0x496BD296D7D8881BULL, 
            0xD7387969FC97AA3BULL, 0xFD9424A5C68CE98AULL, 0xD0F5EB26F5FBA4DDULL, 0x957E11FEC1C490ADULL, 
            0xC68EE68827B14CB1ULL, 0xB6C46B770047B8B4ULL, 0xA1B65F33C521555EULL, 0x2B7B18A47E2B2604ULL, 
            0x51303E102FC1BC84ULL, 0xDC198C94F1FD4F98ULL, 0x0E3866A460451663ULL, 0x0481B376813029B4ULL, 
            0xC96323B445011DA3ULL, 0xF2AA3258CF865E7DULL, 0xBF70D6128DA2F765ULL, 0x4804B1FC7A71B5D9ULL, 
            0x9B903BF048E8C1D9ULL, 0xA9003F9050012E38ULL, 0xA8560890C1AF7144ULL, 0xB20D66B9F1A2D0A1ULL
        }
    },
    {
        {
            0x42006B54279D43ABULL, 0x7E3344EB432FC13CULL, 0xEDD75F114BFC372FULL, 0xDD74D4F7855B1500ULL, 
            0xA5C03F44223D1D67ULL, 0x9486F188A18E26CCULL, 0xE5B363854A9235B9ULL, 0x2A3B516C9E02A15DULL, 
            0x7A189A8FF476F283ULL, 0x5A26F7E68162420EULL, 0xC2BC65F2A3068071ULL, 0xCCED1E2110A7A464ULL, 
            0x76E93826FFEB37F1ULL, 0xFBA6DCD2D6D6F4BAULL, 0x01AC37F713BB6E3AULL, 0x3AFD91F096BC033BULL, 
            0x52BF9DADCE7518F4ULL, 0x31F0744AA2BCBA1BULL, 0xFF4B72036126A3DAULL, 0x682583D309A85CDAULL, 
            0xD64F49D71D0FFADEULL, 0x8E54C09BD896CEF7ULL, 0x514A0C82000DCD76ULL, 0x3514B4DA08E86FDFULL, 
            0xF9C66754F1557787ULL, 0x7AE3B555C3A8EFA8ULL, 0xE70C00AC08C2C318ULL, 0xEDE0BF9267157310ULL, 
            0x8C1897490EACD215ULL, 0x2642DDFB45493C17ULL, 0xD5E42F539708D518ULL, 0xCCA5568D00DA68F0ULL
        },
        {
            0x6FD174D9975DC59EULL, 0x563C0BDEBE119343ULL, 0x42A77C9288F7129CULL, 0x4158D81A1AD75A9BULL, 
            0x009F0F972A896DDCULL, 0x0C28752B0975ABE2ULL, 0x223EDC16792D7C2BULL, 0x583B86FBCB622CF3ULL, 
            0x715C0978A2BEC5E4ULL, 0xCBE34B011DBEB2DCULL, 0x4FC88A32E33AEB2BULL, 0xEB649C28CD965502ULL, 
            0xAA8D0BE6D47C7763ULL, 0x7127999DAB670A9EULL, 0xC94ED1EFD660BA4EULL, 0x922C87A301429568ULL, 
            0x1CD47B6FEB0E0C13ULL, 0x70E214E06CFF20C3ULL, 0xC66F673DA936812BULL, 0x3FE95860E85048EEULL, 
            0xAE7DAA5A528B14E5ULL, 0x9EC1740094985535ULL, 0xCE8B7C1E5BF6EE47ULL, 0xDC9F4D103E2275A9ULL, 
            0x122B6E986AF2164BULL, 0x391FC8BDBDCECA4AULL, 0xE8A41AD86D52B61AULL, 0x0496C10C14050E92ULL, 
            0xDEDEC9BC779E8CFDULL, 0x7B1BC0CC818112E9ULL, 0x880C804D4B7F46F7ULL, 0x2B1CB24F472590E8ULL
        },
        {
            0x3BB902313748DD55ULL, 0xDCD7B799F1D8F48DULL, 0x8300DF65432C21B4ULL, 0x062619802725A0A8ULL, 
            0x5078CF835DFA8333ULL, 0xBC5ABC7D81DDCCE6ULL, 0x88C0201EB5B7B7D3ULL, 0xF9A93769D599BFABULL, 
            0x3F48ED85CB3F9B02ULL, 0xBC7038CED18A384FULL, 0xB50E093985305708ULL, 0x000265AD3926A0B5ULL, 
            0xFD8CAF03F64AF0C1ULL, 0xF62BD450B62C6AEBULL, 0x65A710973CBEE650ULL, 0xEA38E4B41C0AE580ULL, 
            0xBFB3033029BEF0D2ULL, 0x4920020B157DDE81ULL, 0xF45C767F46052F4EULL, 0xAA762E5BBA872B28ULL, 
            0x6CD182C781212389ULL, 0xAD2DB7C9BC9012EBULL, 0x92BBB2DA732122E1ULL, 0xEC62CC4BDFF133A7ULL, 
            0x5AD5C2827E059633ULL, 0x01504A713794E291ULL, 0xD46A7E33AB580064ULL, 0x369983A18466CFBBULL, 
            0xE7344468E358190FULL, 0x3F1C4DBD5F811296ULL, 0x18C59878C1C7D3A4ULL, 0x47DD4DD2B136FBA3ULL
        },
        {
            0x21B8C0DCA305AB49ULL, 0x34E6E2C755F32519ULL, 0xEE75F3BA6AD203E2ULL, 0x56C52BF46248B8CDULL, 
            0x22F3F6FF72597F1EULL, 0x2878A08943431528ULL, 0x51B34CB57A49706CULL, 0xAAF18E961926E7DCULL, 
            0x88ADB6B67AC60BBFULL, 0x37A2FE1F7AB6F4BCULL, 0xD777B1FDF744E8D6ULL, 0x30BF0C6941E73BFEULL, 
            0x66AC4DA2A72AFFC5ULL, 0xD9DFE57CAE94C963ULL, 0x5D7C5C38E5EF79ABULL, 0x950A5755B4A8EEBDULL, 
            0x4FE696E90423295CULL, 0x7C7B4B5CC883ED85ULL, 0x632DFE810FB8DE49ULL, 0x516ECF6EBB4EFB75ULL, 
            0xF4CF0C51011E2E3CULL, 0x962FB211C1F4D0D5ULL, 0xA49CF3BAA0102CC7ULL, 0x3A8D6C7217FB8804ULL, 
            0x94C4ABA33F6067F0ULL, 0x964A9420D702F868ULL, 0x089972FA6A6F8EEEULL, 0xD54DBD8FE55591D1ULL, 
            0xE84B268C7DD12DA4ULL, 0x37E504033027C7BCULL, 0x09EB1A09B259846BULL, 0x4DF1F78F67343080ULL
        },
        {
            0xD0F76816D305FA1CULL, 0xC63C381C90617257ULL, 0x84545B3278DCF969ULL, 0xD2EF654733F4A9CDULL, 
            0x564A03571A087861ULL, 0xFB96C91FCE0131D0ULL, 0xE15C8A30006EADB0ULL, 0x6838D528E7C065B4ULL, 
            0x94B0BFAFBDC32D2FULL, 0x703F208078976B68ULL, 0x8CE7BFA9B2C493C4ULL, 0x9EAAD18D717859DBULL, 
            0xC77DE4BA0CEB1FF3ULL, 0x24743DE791D5CE53ULL, 0x2950ACA90E8A3B92ULL, 0x2B4A86D7A2B3C5D1ULL, 
            0x1DE10D620DC7AC35ULL, 0x6DF895446880858AULL, 0xECCC35707F48B396ULL, 0x3631C05683232759ULL, 
            0x250CE4625039ABC6ULL, 0x86E07DB26A25A4E7ULL, 0x6D0C1291DF082C45ULL, 0x163295A8F685BA82ULL, 
            0xB59D1F09CD791F30ULL, 0xBC2222441A844775ULL, 0x8C14F87C1E738B4FULL, 0x5559821CB9A277D6ULL, 
            0x687580D23E4E9288ULL, 0xAD665AFE2C94FCA7ULL, 0xB1728221373334ABULL, 0xEB23D2DC2253B0ACULL
        },
        {
            0xD57F96DFFBF53B2DULL, 0x3A9B87FF990F619CULL, 0x0B5DDEC07DF50082ULL, 0x32EA2E11CEE6274BULL, 
            0x7AFB1933639BB956ULL, 0xE0B04CDB95B52098ULL, 0x966200ED15EE321DULL, 0x367C0A6E9B6FDC7AULL, 
            0xF1E5B23661832EDFULL, 0xE7C0583125697622ULL, 0xB7E729FEF9574D22ULL, 0x69EE782211663420ULL, 
            0x4A204140BF29874FULL, 0x370B938CD7BD45BBULL, 0x19C0F8746BA805DFULL, 0x22ADF75C80FCFD38ULL, 
            0x47B8E85994FBD093ULL, 0xBAB443AFCF575DF0ULL, 0x472C9E19E169A5E0ULL, 0x2A23A108DEB83FE6ULL, 
            0xA056C38F74AFAA18ULL, 0xFE6786C3411033BEULL, 0xD51EB59ACD663600ULL, 0x4A3B0EB0959212FBULL, 
            0xD4A51DA6D2DCACB3ULL, 0xE0DEB1F95546E72DULL, 0x9E6E790FBE815776ULL, 0xF5D5769FE0E0BBD3ULL, 
            0x9D8DF2976DA19446ULL, 0x92546A673B22E7EEULL, 0xBB60814274241561ULL, 0x62635377B0B6F562ULL
        }
    },
    {
        {
            0x524798D009296AA5ULL, 0xF2893B552892EF6FULL, 0x98169464F7B3EDD0ULL, 0x1D3B38C42436A468ULL, 
            0x97B7BB8E8E25F083ULL, 0x5CCD63CE541D690AULL, 0xDA18DB61FE3B17C5ULL, 0x2994A7B1BB740FC5ULL, 
            0x9A579F054B595946ULL, 0x264819EB0206FE4DULL, 0x79A7C7287097D4B8ULL, 0x2B49829B4C2D4973ULL, 
            0x42995B36FFFEDCAAULL, 0xB47E015C04C558ABULL, 0xAC0057AB8B0D6BCCULL, 0x3C26040878CD6E51ULL, 
            0x3625CC7D9336C015ULL, 0xF575033C0B179527ULL, 0x66A3C2558DE09F21ULL, 0xB07AFC1CFFA771EFULL, 
            0xDBBBDC7A98E535E6ULL, 0x68BF4FF09DD80337ULL, 0x04CACC37D9C13EE2ULL, 0x059D56D7D9CC0F4AULL, 
            0xEA1CE08E0E8FDF7CULL, 0xC70C95B0292A49EFULL, 0x7217A15DFE7A7D09ULL, 0xFF9F55DFFE00BD75ULL, 
            0x822BD2243AD9D74DULL, 0x67C35D59C7C5681EULL, 0x939DEC88E8226373ULL, 0xDE6E60A6B8AD2B6FULL
        },
        {
            0x9BE4D8C24B0765C9ULL, 0x65B741E73AB5BF12ULL, 0x0BBD19DFED4BFA17ULL, 0xDD01C7F27028FD40ULL, 
            0xB7A09C41FC03E35EULL, 0x86E0237298F97322ULL, 0x4B719539D2CE5961ULL, 0xB596E21F4F15CFF7ULL, 
            0x41AFB55F5E404DB5ULL, 0xC18D7EF49D88FA94ULL, 0x66A3571E18D478B6ULL, 0xED64FB5504ABE0A8ULL, 
            0x85578F8BBE399F7CULL, 0xC6B9F698ACB9715AULL, 0x86F2EECD28C249F1ULL, 0xF364821557E41822ULL, 
            0xF7BF93392A05146FULL, 0x47C99076B3EE711DULL, 0x0F4AED3532B15587ULL, 0xA68E927C55CEB002ULL, 
            0x5CFB7CE56A72D6D0ULL, 0x2878FD6F15BA6BD7ULL, 0xEEA85A0340BBF57AULL, 0x903E47349CC460A0ULL, 
            0xF2C4494AB8D6B148ULL, 0x3115F94331CA4A7DULL, 0x0D854F7397F4CBE4ULL, 0xF8323DA4EBDAC616ULL, 
            0xA6784D14E5F8E211ULL, 0xA6306D6128FA5983ULL, 0x52BFA3F25C7A9B76ULL, 0x7BA6A979CBCB64BDULL
        },
        {
            0x02B876EE445FB5A4ULL, 0x4AB7FEFE0881E12EULL, 0xEB8C32E0EFD319EDULL, 0x6AAB1B7F4C40CFE2ULL, 
            0xF7E6A4A741FBEAACULL, 0x1E22C7081E8548B7ULL, 0x813CA3529D5108C0ULL, 0x479A97CC8A1D83DBULL, 
            0x20F37DDFAE4D82AAULL, 0x8E95E0A2B34166B4ULL, 0x0458DC8C4D49839AULL, 0xA64E85669883462CULL, 
            0x10B60E3B5E70DE16ULL, 0xAA862D589CB41110ULL, 0xA72EAA6F5E7F92A5ULL, 0x557F71F96553D5AFULL, 
            0x9665D3EA086765FCULL, 0x8810F3E8E5D52F11ULL, 0xFE1299545C2FF767ULL, 0xE5755394726DCD5AULL, 
            0x3114C602A16746B8ULL, 0xDCA7E5BEA97BD8CAULL, 0xF999592D995CC4AAULL, 0x8D5C699E9327FFB4ULL, 
            0x4B1001D5E8353B5FULL, 0x96FC9787B35CB5B5ULL, 0xD34984E08F773A94ULL, 0x3588DA06C577199DULL, 
            0xD0126F44F83E930DULL, 0xDE96D64DBAB55216ULL, 0x088657C9349A8C1FULL, 0xFE42F6496D581211ULL
        },
        {
            0x8B36B7C59ACE195CULL, 0x97631937D9FEB979ULL, 0xC877814D2756A396ULL, 0xD9F4A4CB61D84833ULL, 
            0x734179CEF3947C61ULL, 0x8FCAED86E5919642ULL, 0x5DDB21B3AB63E067ULL, 0xE4A20869920EC7A4ULL, 
            0x106E676EAD8E5245ULL, 0xFFE17ECA54CF97BEULL, 0x208F3FD9936B83DDULL, 0xE949AD7519966F73ULL, 
            0x40BF5A1FB7BFCF5BULL, 0x5B07B1AAE3CC1A96ULL, 0xC068E0955F2F59B6ULL, 0x5BC33141F4A6563DULL, 
            0xFE002F0F2C7AC275ULL, 0xECF178AB2D9E2B48ULL, 0xD7CDF64972A2531CULL, 0x24DAC972FF92A5ECULL, 
            0xD4F38D9D6DBCF7D6ULL, 0x32EAB304835DE4EDULL, 0x7EBF3AF066B86558ULL, 0x038A9ABF293F0409ULL, 
            0xDABB9A5D6D09D8E5ULL, 0x4C82343F27F1A720ULL, 0x9BCC9DB4DFAF4243ULL, 0x8D7734533AD90442ULL, 
            0xA3D77702D5F0901BULL, 0xD8613578B9A3D266ULL, 0x9F217110ACA76C24ULL, 0x74A10907978378E9ULL
        },
        {
            0xD3D47DDD68319A25ULL, 0x124279DE57956E49ULL, 0xEE653C5AFAD23689ULL, 0xF6104CDD90B216BCULL, 
            0x6B2EFA098A447E5FULL, 0x23664600610B8D71ULL, 0x4198ACA91732A0A3ULL, 0x654B8911B8BBA174ULL, 
            0xB08CAD2E7E404D7CULL, 0x0B98193CE354025BULL, 0x6F9DDA69B0620042ULL, 0xB3D9C8DF6FB11D3AULL, 
            0x883B558071924247ULL, 0x558A4A5C8B5C17F9ULL, 0x71F52BA5A9F31755ULL, 0x0D10738BAAB08809ULL, 
            0x2C39D3984A2DC060ULL, 0x955AE99D653C9E98ULL, 0xA89C124D0E17D17CULL, 0x75C39BD27FD2EAF5ULL, 
            0xD4FA97600EFC48E7ULL, 0xD900EC7A81717F3AULL, 0x42AEE77881E333F5ULL, 0xC358FFBB4C4AEB0EULL, 
            0x0CC1AD93F03656C3ULL, 0x23F69E8092707B98ULL, 0xE2B11F7C54D4A0BDULL, 0x9279A51979544181ULL, 
            0xAA77846CF8E6CA4BULL, 0x62898FBEEAAE7F0CULL, 0x7DA431D7EF6ED480ULL, 0xD5609AA1DFD34FFDULL
        },
        {
            0xFF63D4A672B4CCA0ULL, 0x135F1B64FDD4241DULL, 0x3760EB988C6DA482ULL, 0xAC7292ECBF6B0F63ULL, 
            0xFBCC22512C8F8313ULL, 0x4A8B1F5222A3AE4FULL, 0xF4A0F32278CE9052ULL, 0x6933F57290109D6EULL, 
            0xEED492842042491EULL, 0x0D85E94439D764A7ULL, 0x3D2FF8C971E0C8B7ULL, 0xEC78A600FDF5A7BDULL, 
            0x31DF1225C5AE1130ULL, 0xC58C663F55856E33ULL, 0xE0E4E487F2C5BFD7ULL, 0x3E659E2FD0A38C4AULL, 
            0x0CC041795FD0C3DFULL, 0xD96D4B616095EBA3ULL, 0x255F8E706F0F43BDULL, 0x00C12A06F446FE8BULL, 
            0xBAC066336C103EB2ULL, 0xE2A4B006B82DA906ULL, 0x8FE1F94A7607345AULL, 0xC5E596FDA1461009ULL, 
            0xDDB668760D5686A5ULL, 0x9A900373713CA408ULL, 0x86E637F62410F8E1ULL, 0x4648E21CD28A229FULL, 
            0x92DB7F73FC654CD8ULL, 0x94832F9936B3FB4FULL, 0x5ED94E576C556CEAULL, 0xDF7DFFC0F855D35DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseFConstants = {
    0xD8D992C93BAA080DULL,
    0x407D637CD40D6CE7ULL,
    0x94B3F36F03026155ULL,
    0xD8D992C93BAA080DULL,
    0x407D637CD40D6CE7ULL,
    0x94B3F36F03026155ULL,
    0xED90C3D43932D69FULL,
    0x1DCA378A6422AA88ULL,
    0x26,
    0xE8,
    0xB4,
    0xB8,
    0xA8,
    0xAF,
    0x22,
    0x59
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseGSalts = {
    {
        {
            0x2BEA70046E58F60CULL, 0x66148ACA00982245ULL, 0x7B40F09A34A74C42ULL, 0x24B3BFFD1325AF0BULL, 
            0x3625009B7CCBAF28ULL, 0xBA20481757B2EDEFULL, 0x82C0747A88342164ULL, 0x2280CAC5C1CB51CCULL, 
            0x301EB1190E9B099BULL, 0x233F74AE8D241D9FULL, 0x24DEF8C942958DFEULL, 0xEDCB1ED03C69D965ULL, 
            0xD3D7CE91749D2261ULL, 0xBBD23057FDE3B1A4ULL, 0x1839BCA984B3FAB4ULL, 0x4EBB1096530DD61AULL, 
            0x2DF3B92C64900DA4ULL, 0xA20DAE8580750AD6ULL, 0x3658E89E0F5ACB7AULL, 0x77C7F346B09DA874ULL, 
            0x28F21C22D70BD1E4ULL, 0x778692793FF20E30ULL, 0x9FD4E9B72AF5A559ULL, 0xF8291CF0501BE6BDULL, 
            0xE7C7F67C2917DEB3ULL, 0xE729C2101860255CULL, 0x7F0CA5BF2F2D1367ULL, 0xFA626F0A37A65D60ULL, 
            0x01033EBA0E34EC55ULL, 0x5267E1801FA4EB79ULL, 0x04543F8203776C78ULL, 0xD2BEA5E8B5A1A917ULL
        },
        {
            0x88AA5B2D4943F051ULL, 0xAFCE0E6C04A7C6BDULL, 0x0ABE140BA3C56107ULL, 0x72C4F7CFBCEF0647ULL, 
            0x161D3C5A0D467EE7ULL, 0x5225FBBDB2E639B3ULL, 0xE94D8932DBE18427ULL, 0xFEBD5F88B73F5C2AULL, 
            0x6C1105E8D7505DD9ULL, 0x7F56083057F28991ULL, 0x06C27CCE94A5628DULL, 0x8B8AABDC9907C0A7ULL, 
            0xC58D112EEE66F48AULL, 0x0F69D0C57E5CBF7CULL, 0x1CDC195B132C7B3DULL, 0x3D840D605221B4FDULL, 
            0x0BB498A2B893275BULL, 0xBA7D6CB511E3414CULL, 0xF098E66815242D0FULL, 0x0A1D7FEAF7BC383FULL, 
            0x0A2FA383B147A3DCULL, 0x545F1568FBA4FC6FULL, 0x08657CBBBAC93BF4ULL, 0x191D55B799D27C15ULL, 
            0x1218C3A862899F6BULL, 0xA7EA714970135DBBULL, 0xF79699E43C30568AULL, 0x67A5944ADC0C9970ULL, 
            0x3DFB6D492F4B9842ULL, 0x933273D1D9E7EABFULL, 0x0E83572765000EB8ULL, 0xC9623C299BA1E5D1ULL
        },
        {
            0x722F7A16A8C60737ULL, 0x3837BA59056534B8ULL, 0x8F42F3D07C43E1C1ULL, 0x08CAA80758BCEAA1ULL, 
            0x691D080259EFADF7ULL, 0xB0DBEF1EAFC750E8ULL, 0x7BEA734C67601D97ULL, 0x52A3E34766880AE6ULL, 
            0x34E1CBE75C097D8CULL, 0xF2878C999F15151DULL, 0x1230C3CAE61090DCULL, 0x309A765571A3CB31ULL, 
            0x56CF3DA404C947A9ULL, 0x5C6CE97A76F93364ULL, 0xD5A6B9CDE11B8E52ULL, 0x25356FA726957DDBULL, 
            0x8FCFA82F3064131DULL, 0x187BF3E059DB520FULL, 0x67859B9BC93EBC21ULL, 0xCD95E84EAE084533ULL, 
            0x1B1BEDA72B412327ULL, 0x6D93FFD4D0507577ULL, 0x7A13E1F3F55C34E6ULL, 0xEE0157C1E372EBA7ULL, 
            0x5EB540B58D9B4958ULL, 0xB60E0C2B76B22844ULL, 0xF21BCDE561D0ECDFULL, 0xF94E7DE574AB77E4ULL, 
            0x728C8593D5655110ULL, 0x480130956B352C76ULL, 0xCC1DABD7CCDE75EAULL, 0xC00A314329AE9180ULL
        },
        {
            0x1B6329DE7655C2E8ULL, 0x4AF4768420749C96ULL, 0xCD56D64EE519AFD1ULL, 0x044F23264C53B919ULL, 
            0xAED336FCBE2510DDULL, 0x632D644433145A6AULL, 0xA2D24F8A35F216CBULL, 0x96BCE8AF9F8552F4ULL, 
            0xAF3EC75D6A18DC6FULL, 0xE63D8A9B03AB8E40ULL, 0xA3B9CA30142FEC8BULL, 0x10F7B2E7071F7E71ULL, 
            0x139ECD1A4031CB82ULL, 0xE7934C87E00B7318ULL, 0xD4A0CF917BC9EC31ULL, 0x7E0A1C311C2D4526ULL, 
            0xAA0D67DE4030D5E3ULL, 0x0C426A8CBF21EA60ULL, 0xEB87907C887CD929ULL, 0x25BD15D1C4A982E4ULL, 
            0xF6B1D37826821859ULL, 0xA410DCE8CB797D57ULL, 0x5607858251CB6441ULL, 0xB580A3DB1BC8AD2DULL, 
            0xE4EA0B092681529FULL, 0x1831BD66B57E5A6FULL, 0x943A28B2FF01A3FEULL, 0xC75AD992CF1A5CBBULL, 
            0x0831456DC978046EULL, 0x03726DB022B7DC09ULL, 0x979C45927102904FULL, 0xBDA570F551381A0AULL
        },
        {
            0x7DC958C022B08804ULL, 0xEDE4027AF32FE06FULL, 0x941B49FD6A8050ADULL, 0x679681AF27C7A401ULL, 
            0xEB000BC5A5396E65ULL, 0xE3ECC879A50C23D4ULL, 0x901BC03CE7C0E712ULL, 0x849E9C6D89B81620ULL, 
            0xC0EC423D87ADABB6ULL, 0x0719A4932BB58926ULL, 0x9DD00214112F6F5BULL, 0x112D1C744658893AULL, 
            0xE4B5BBC930DFC720ULL, 0x437C54B65B0443AEULL, 0x56CCD974183B9A93ULL, 0xC04357E41285B953ULL, 
            0x157EAA8789C056CEULL, 0x18CFEA77BABC2F3CULL, 0x89D96C20A5393B93ULL, 0x196D4315E3B12A4BULL, 
            0x77EB5DEF29A3BCCBULL, 0xFB9088D4FA5F2D2FULL, 0x6A9FAC7351BCFDA2ULL, 0x6558641DACDAC9DBULL, 
            0x391C5C07EB191992ULL, 0x9FC81635795EF90CULL, 0x34BB9E24D3967DDDULL, 0xE16E3BBF46F4C350ULL, 
            0x214AAC38D7DD8FC4ULL, 0x641CA0E77893F0A0ULL, 0x0A9A0910D25A3C25ULL, 0x6A7BE48D1CAB8D31ULL
        },
        {
            0x0EB4F6ACF0A8607BULL, 0xFCB06B4AFBF0FB36ULL, 0x0CB2D077BB0163C6ULL, 0x480036DA86025961ULL, 
            0xD0147C7506F9AB82ULL, 0xE869F53072F1FAFEULL, 0xC5C607057A1BC68DULL, 0x943C3D10A35E7347ULL, 
            0xA9E9522C711A5D71ULL, 0x48EE17B03BF991F6ULL, 0xC598D19E82C8BBBCULL, 0xDFB76674DA052E31ULL, 
            0x9CC0B6BEA8D8889EULL, 0x3B00AEC3F6FF9379ULL, 0x9EC02DDD89DB3857ULL, 0xBF698B3EC10258B1ULL, 
            0x835684E34DBCC734ULL, 0x8B55F68BF2BED72EULL, 0x984B01B831F09B6DULL, 0x83FF1D96EE837974ULL, 
            0x3794CB87F5D8DB77ULL, 0x5E5494613811A11FULL, 0x832E68223D9F1E1EULL, 0xE60AD9F3BFFADA5DULL, 
            0xCE9BC9793957E684ULL, 0xA0774BC0F01457B5ULL, 0x692E815E2970CA51ULL, 0xCFA5E09E51CD7CE9ULL, 
            0x52BF1A88BA750937ULL, 0x43851E144E3B4670ULL, 0x1E70C5F770A637ACULL, 0x73EAB0921EAA0285ULL
        }
    },
    {
        {
            0x0FE0DD1D60A4B940ULL, 0x8DED2B09E26151DCULL, 0x0FCD3B8C3B251DC2ULL, 0x1CEA67AEA3904DD8ULL, 
            0x50E0D1AB7FEA0443ULL, 0x8F5997A1A997A638ULL, 0x0889B11EA6E9D475ULL, 0x364D92EFFBFAE469ULL, 
            0x43A76A4FA1FE7FC7ULL, 0xB86F5C3B8583DF6EULL, 0x08FA91D2314600F6ULL, 0x6D18E702D5ACA651ULL, 
            0x27C8645F9285BAD8ULL, 0x250EDB3F828A6466ULL, 0x761E6F5960C28822ULL, 0xB7BF7406B4D73F7EULL, 
            0xD97AD9E682F0305EULL, 0x95751D3DB63762ABULL, 0x0D095670AE75EBF4ULL, 0x7475366B903728DFULL, 
            0x34596B7BD5BA93D7ULL, 0x735B47297C60994EULL, 0xA206D6081926A93BULL, 0xCB95E34D765695E9ULL, 
            0x49B0979AC198948DULL, 0xD8BCE36FB9B96EBAULL, 0x7DA324AFEEACBB4DULL, 0xF1DCD536327A8FF6ULL, 
            0x55653D26B7F55034ULL, 0xFE24531D9F4643C9ULL, 0x3BEDF273A3553678ULL, 0x13AC970028CC145FULL
        },
        {
            0x0CF061124CEB87A2ULL, 0x92902D39A0EA74A4ULL, 0x56D45ED78B255B86ULL, 0xB9EE98156F9BF657ULL, 
            0x4E6612F7B03E9BCEULL, 0xD59D71799A239C82ULL, 0xF37A6D4792B64E08ULL, 0xD1CC20AECA693FAAULL, 
            0xA87D830652152465ULL, 0x9D1BB01F74B7EFEDULL, 0xD398DD62868DB94DULL, 0x31B05F7435DF6F40ULL, 
            0x2587F169A2D26696ULL, 0xB3C9D001A2B4A6C1ULL, 0x6A481F27E10CBCD5ULL, 0xAA9775F75B712DFAULL, 
            0x224AD2C1DBDD9830ULL, 0xB747CFCB8C3C7A99ULL, 0xD38D8D3392EDB6CEULL, 0xD17FE71C8CA99BCFULL, 
            0xDDF91B81FDBD7575ULL, 0xCCF1F299C3557623ULL, 0xBAB6325E8C34920FULL, 0xE1936D186645D065ULL, 
            0xD2F1E2563641D51CULL, 0x0F808133E7B2A8B3ULL, 0x953C653BE8FCCAAFULL, 0xBC07F3F420D5D4ABULL, 
            0xEEAAA962042F0F33ULL, 0x82BB1B2DF808D13DULL, 0x2C792FCB86FEC476ULL, 0x3F900D3C7DC10839ULL
        },
        {
            0x289EBA6CBD8D2B6CULL, 0xAB2D0EE755F262ABULL, 0xB73510D0E873DDBBULL, 0xBA99FA8DB7456694ULL, 
            0xEEE17D7CAD13B7F1ULL, 0x653A12A607F9A220ULL, 0xAED6491B69994EF5ULL, 0xF086CE0C689661F6ULL, 
            0xF99643F112DD2B93ULL, 0x49BDE19ADD4ADB3CULL, 0x60E5D321B1406A72ULL, 0xF5B0489720080FE5ULL, 
            0x76EBF2D85EBDB23AULL, 0x0907A4EDE6F0991AULL, 0x3B7E7F4C277683ECULL, 0x9ED384DD9F4EF584ULL, 
            0xA86D28A1BA5B60F4ULL, 0x22BEEE59D7CECEF1ULL, 0xDF5DFCB2883F9A13ULL, 0xC27A19B8202084C6ULL, 
            0x86FEFF4D5B35631EULL, 0x4905CF2C1ABD9C11ULL, 0x8E56704D5972673EULL, 0x6AD8F96D07FC7BA7ULL, 
            0x9DF625055797C449ULL, 0x70B9013D5DC8F410ULL, 0x3B75FE7609284AE8ULL, 0x0EA301C717B52055ULL, 
            0x692F6622296375D4ULL, 0x678CD969EBC8943BULL, 0x0D1F8ED42C6ABE0AULL, 0x8E1FAE0A9FC345EEULL
        },
        {
            0xEDB4FFC60E48D7CAULL, 0x7BC7DEF239508219ULL, 0x6BADFCE94395739AULL, 0x72585ED6B8371B51ULL, 
            0xEE0EC7A529BA6D1BULL, 0xBF0822DEF8D7236DULL, 0xFA3F63AF15D3DAFCULL, 0x942D4334958BBA8DULL, 
            0x7DFA717C44D917D5ULL, 0x1495742CCFA5C773ULL, 0x59A9D276C5401A78ULL, 0xBF309EE302C8B33AULL, 
            0xA826FD464315F8B8ULL, 0x17DE92B0F8EDA66AULL, 0x4AC1B8FD1268F94DULL, 0x4882EC5380FF64BCULL, 
            0x26E02A36A1E26DBFULL, 0x3E95F2CB60BA988EULL, 0x2A5148E7C98CA16BULL, 0xD7AC1771DB40A2B7ULL, 
            0x17A35A57649FD488ULL, 0xFEBF6B1AE4AEB52BULL, 0x99B11929269237B7ULL, 0x725B013990F1766BULL, 
            0xAEC44710E8ED8470ULL, 0xCC3FE2E5674EDFD7ULL, 0x03C679904E8D9C79ULL, 0x17D5BF3A442FC9AEULL, 
            0x887960B87B85D905ULL, 0xE5DD83A112FA7C71ULL, 0xF13BC18568112C97ULL, 0x3F1448DBC4A0CD43ULL
        },
        {
            0x72F4167FB6E4E7BCULL, 0x5E25C636BF3DCEC4ULL, 0xBB11659AD2CF8A47ULL, 0x445F5C759CAEA199ULL, 
            0x7D71AED30D2B704CULL, 0xC1230231295D0639ULL, 0x6BEFFA70BA92B761ULL, 0xD0DA05B2FF660229ULL, 
            0xCC56453CAFF384BFULL, 0xF47880F42BA97358ULL, 0xEFE4F03ACB940520ULL, 0xFAA2BB793D6DB4AAULL, 
            0xDFAF81FCDDBB698EULL, 0xB1C3E56B51B7FAA5ULL, 0x85ADAD10E2584D5BULL, 0x01970EB5C8CB8101ULL, 
            0xD716140C0FD0F263ULL, 0x01914C6A6FBD8333ULL, 0xD688CD20B006E154ULL, 0x7853ACD74965941EULL, 
            0x753BE3F93526F0E5ULL, 0xE0D42AD90726179AULL, 0xCE2F38328CA6F2A9ULL, 0x7B954C302AFF8E89ULL, 
            0x8FF619BB9DE1A4D9ULL, 0x369CA582ADF998BDULL, 0x83F8543E2005E91FULL, 0x16F47B5620771221ULL, 
            0xE5D351A72C29470BULL, 0x565041573D62792CULL, 0x3BD4036E51E28603ULL, 0x15A4D88F8825D4B4ULL
        },
        {
            0xA522B6344EF199B0ULL, 0x26CA423A41851992ULL, 0x000CD32538EEE7EAULL, 0x45FB8EED03215C0AULL, 
            0x61F3C4E9CB19A654ULL, 0xE00D7FC76B489364ULL, 0x396D06F03B9637C5ULL, 0x31430093E1A1DD14ULL, 
            0x35CC39E4B03AB586ULL, 0xF7BFC34D1FA7C793ULL, 0xA6FD480B6B0983ABULL, 0x570B7163A8C840C6ULL, 
            0xB87200D6664B56ABULL, 0xBE983A0C46A6AFDCULL, 0x39AEC7F6960FA15BULL, 0x307D6A1601864994ULL, 
            0xA03D70DE8D4BF8CDULL, 0x982BBD4D18C2408DULL, 0x4CFC54FFFE6E725BULL, 0x40C902D4EDA55F01ULL, 
            0x6F67FA8E2546099BULL, 0x5EEC8F096801B597ULL, 0xBBFB449ED48B1961ULL, 0x057C03BBD3ED6935ULL, 
            0xF39DA0A487A6A0AEULL, 0x6FFDE2C3A017BB6AULL, 0x9DC04CBD02415860ULL, 0xF31AE8663330AE03ULL, 
            0xFEDAD03A5066AB7CULL, 0x46C46F46EC1AEFFBULL, 0xB114078AA8329C82ULL, 0x31F95A0839C560F4ULL
        }
    },
    {
        {
            0x1C9D772722B4C29DULL, 0x376BE592FC6EF51EULL, 0xFA3C64274300582CULL, 0x31D684BCA665414EULL, 
            0x430DC028DDD161E6ULL, 0x08AEAE769E375F7CULL, 0xADC2F023350D8E38ULL, 0x85D706AA02622C69ULL, 
            0x66F951722A2875D6ULL, 0xB4532250BB3B508FULL, 0xC1C35CD48736EDA5ULL, 0xD9CE5D3FF36EC33FULL, 
            0x3E57B206B351B7A8ULL, 0xDF590BF50CC8B855ULL, 0x47C0CA3DB854F115ULL, 0x5A6EA143A0F3FC15ULL, 
            0x2FF683E79A3E193DULL, 0x7D2CD4D6D1630A7FULL, 0xE9039DD234121CC4ULL, 0x9D9CCB4AF44EABD4ULL, 
            0x12D2BC7566D5B7E7ULL, 0x27CF5421DED2C23AULL, 0xCE765C163CB40393ULL, 0x0E505488D8B29541ULL, 
            0xFB5C36C3EC3D331EULL, 0xC2D2476E14C1F659ULL, 0x241BB464561F6F7EULL, 0x8070EA5345473573ULL, 
            0x7080D28719D9415FULL, 0x1941D0AE55583BECULL, 0xEFB76D8CDD055679ULL, 0x6D34F090AA954B3EULL
        },
        {
            0x85D9FF2A68C030E6ULL, 0x774AEF2D773E15F4ULL, 0xE53C3A6E43BB887DULL, 0xAF27476F138F1ECCULL, 
            0xF764D918BF8DD815ULL, 0x56A69780E341D6D7ULL, 0xEDBEBF53623063DAULL, 0x08C130A9DB07E63AULL, 
            0xB60FF202BE14CE0CULL, 0x05280087E91ECC00ULL, 0x3497AB6308812F97ULL, 0x1331BD817E0A0748ULL, 
            0x94589CC2746D0502ULL, 0xCAC91AE5C5BBD278ULL, 0x665B83FED066CC12ULL, 0x474E7110CC45551AULL, 
            0x78F08385F268E749ULL, 0xDE6FED310CF5661EULL, 0xF098D8E23AADA972ULL, 0xB4E7202FBA45BAE8ULL, 
            0xC23907B131EC2EB1ULL, 0x6FDB2D2A0E12A3FAULL, 0xB0E5EA092271FC5FULL, 0xDBABC7D956A7C1B8ULL, 
            0xF822A9A2A401AE77ULL, 0xA3D2EF5E57B72A53ULL, 0x5818E754C45A2DB1ULL, 0x86B90BB281215112ULL, 
            0xA7C9955C11B09761ULL, 0xD92F53388A5BBBCFULL, 0x2909FD085D9FCCB1ULL, 0xA26EA811774548EAULL
        },
        {
            0x4099E170E80ECD4BULL, 0xB5A0233F465199E7ULL, 0xED6678BDAC329D91ULL, 0x533F8FB98AB3F2B3ULL, 
            0x5CC61047B6F96CAAULL, 0x59D0B5AF41A43762ULL, 0x14303DBB6DD5638BULL, 0x087CB7FF6BB73A41ULL, 
            0xA5900D0C56EC5D6EULL, 0x782C0ED49BC981FFULL, 0x58DF5BE78428A052ULL, 0xDF8C9CC676D6A561ULL, 
            0xF8A2E2997F963610ULL, 0x9B1BD52223B28187ULL, 0x3892C19E174790E3ULL, 0x7F2EA3AC1EE498F7ULL, 
            0xE97CC301DF6651E3ULL, 0xC6301F9882554C0AULL, 0xBB71299E3A018B9EULL, 0xBEB72685F335D954ULL, 
            0x464612C10DE76315ULL, 0xECEE45ED25962379ULL, 0x234FF26E80AA9FC5ULL, 0x08983D7ED01CA19BULL, 
            0x100C840219561BF2ULL, 0x1AE33BD14A8BA932ULL, 0xD39FE2D822786D16ULL, 0xBCE584603BA5A16EULL, 
            0x5EDD937A308E30C3ULL, 0x4BEE2767899D3B10ULL, 0x5B39D4246EF452FAULL, 0x97E07B408368FF4CULL
        },
        {
            0xD979689A0347EF07ULL, 0x8C56AA2B33A68161ULL, 0xA28B45609D32453AULL, 0xC54A87CFE4E2DE9DULL, 
            0xFDF2F814D719D6AAULL, 0xE8E0F92FF4169722ULL, 0x0BA23CEE6CE9DDE7ULL, 0x4A5D8D9C17D3A116ULL, 
            0x9C934A582F34BEF3ULL, 0x2E429ABE875139A8ULL, 0x2272D7CE3B021CC3ULL, 0xD0578834D4138A7FULL, 
            0x01C1630B9B4190D1ULL, 0xB5170A64A3523EBFULL, 0xA1AE22FBCFAAFFEFULL, 0xAC7A12A6CC334648ULL, 
            0x93BA188D040485F3ULL, 0x174AFC3367972F6AULL, 0x5B8AB0D9708774ACULL, 0x8AAD54595518002DULL, 
            0x1C2FEF4B594A1C1AULL, 0x553FABC34976C9CBULL, 0xF7D986EE297DFE21ULL, 0xC76309FB0067F3FDULL, 
            0x28D3BFD7E19F27C2ULL, 0x5CE943D6F33A1E67ULL, 0x04E4AA98378EAB68ULL, 0x1CB3A7E12FCC0C5AULL, 
            0x901E1F188142881DULL, 0xA220FD22EA6EA61DULL, 0x8B7880D285DA809DULL, 0x4A3B136A2E5D34D3ULL
        },
        {
            0x9B771BA496A8FCA8ULL, 0xBD9AB251007B8E58ULL, 0xF3C3DF713CC7BF4CULL, 0x56B564F2197DEE10ULL, 
            0x43376815AFD4FFB4ULL, 0xF388E0223972E75BULL, 0xC9342F0BD460958DULL, 0xB2507B8E57D2DCA6ULL, 
            0xAD716FC363C8A295ULL, 0x0DD89426F08F5494ULL, 0x18831C6067B0630DULL, 0x93BFA44270A0438AULL, 
            0x27215130841EF7EAULL, 0xFF4F91FB581BA178ULL, 0xAD61137A90F719F4ULL, 0x44A20930BE933DFFULL, 
            0xDA20FD73482C647BULL, 0x2967743BF548FF8BULL, 0xBC0F04FB6D8B2A4FULL, 0xAF62D8FC6C6901F7ULL, 
            0xC0E92C19AACED4D6ULL, 0x108DCAA6F640ABD7ULL, 0x4F60DA2E7089D877ULL, 0x44882AA0E38FB4EAULL, 
            0x7EAAA961A4F9E8DDULL, 0x3D44E9BF7BB644B4ULL, 0x84AE7534268E101CULL, 0x0C7E0D334D8AD179ULL, 
            0x224E9006F50663C4ULL, 0xD022B78C6311F7B9ULL, 0xD9F8A6AB9661D685ULL, 0x7233E20C2C1FC21CULL
        },
        {
            0x3C98405D52556052ULL, 0x988806F112D4E27BULL, 0xA7EA86975C351CB5ULL, 0x2087401DAE42B906ULL, 
            0x82E9EDB4D0A5294BULL, 0xD9BCE0D412949AC3ULL, 0xBEA086D8582D73E9ULL, 0x680AB91BACAD71E5ULL, 
            0xC0137C122F3D4918ULL, 0x07C186986100E2BDULL, 0x33D4A5661C870547ULL, 0x3E92CA6EC7D13E78ULL, 
            0xE5DB59E8C342689CULL, 0x00A6770C31C229ADULL, 0x21CBF290B416A6E5ULL, 0xAB713046EB23B33EULL, 
            0x47CDF51668F09415ULL, 0xD92A92C9B0653F8CULL, 0x9E2D7E104D49097DULL, 0x9CB8A6CF2EDA0046ULL, 
            0x365F2D2BFF801FCBULL, 0x25E19FDA5129A365ULL, 0xD6A303F7C5A9BE70ULL, 0xB0EEBD083A4906D2ULL, 
            0x9D685715F890E060ULL, 0x8C067393DB550864ULL, 0x1F41647ACBB38CA4ULL, 0xB15F50F9A14373D7ULL, 
            0xE5D0C24A6CA2481FULL, 0x80D41566554BAC5EULL, 0x073470F66166DB15ULL, 0xE0585AFF266DD434ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseGConstants = {
    0xB94CAC8D49926077ULL,
    0x84D3A64E5F8E6647ULL,
    0x0F3A1BFD0256BD1AULL,
    0xB94CAC8D49926077ULL,
    0x84D3A64E5F8E6647ULL,
    0x0F3A1BFD0256BD1AULL,
    0xC41CAF38D7E361E8ULL,
    0xC343D713C74BED72ULL,
    0x3F,
    0x77,
    0x81,
    0x1C,
    0x42,
    0x34,
    0x2E,
    0x7B
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseHSalts = {
    {
        {
            0xAFF950D50D968860ULL, 0xCCA538FCD705977AULL, 0x05EDDFF01174DCF7ULL, 0x94AB05516A79BAD0ULL, 
            0x3F61E187F4B404CAULL, 0x355359B0C75C7F5AULL, 0xFC772F6A466A719EULL, 0xE0FA1FF6B490650DULL, 
            0xA6CF5174BFFEAF46ULL, 0x21D00E636FE55344ULL, 0xCCE1B89458A12B65ULL, 0x81355CA2F6FA466DULL, 
            0x53F040E7346592D2ULL, 0xC56AD0EB92B632D0ULL, 0x16761C7704F2079DULL, 0x49F2091EBCCE0C5FULL, 
            0x1D66DE30FEF1B3A2ULL, 0x8D8515055C0E6B18ULL, 0xDD8C3694F20CC90AULL, 0x4A02A318E62B3CDEULL, 
            0xF90142D4F7F7D4ECULL, 0xCBE7BB95E784BB61ULL, 0xF8DAC97B7EB10802ULL, 0xFC526105CD73C803ULL, 
            0x05AE7AB66994FE31ULL, 0x6A2D7FE51C06C412ULL, 0xBD1EB5B79DEC00CFULL, 0x4F2B9B965BD701EAULL, 
            0x8455A02B4D031A86ULL, 0x455867997464901FULL, 0xF16522B449D1F9FCULL, 0x6C3A3AD4491880A6ULL
        },
        {
            0x303D6721B7611C37ULL, 0x9CB6C9A4FE3CAE26ULL, 0xC567557A8609FB6FULL, 0x9E265B8458D2856DULL, 
            0x296137CE1203254CULL, 0xE837FBE3B9052F49ULL, 0xA1F4BFAACE0BF0F9ULL, 0x05096B0C67E87819ULL, 
            0x3A631CE90E09C2F1ULL, 0x248ACAEEAF7DFBB4ULL, 0x866C8F13B6061285ULL, 0x846EB3AE04F59E4BULL, 
            0xD130004319DDC8D3ULL, 0x6F3C43CF7D7B36D0ULL, 0xB466A7D24D4258FFULL, 0x0A2D73AE8B200219ULL, 
            0xADCC443A39427008ULL, 0xAFC2653FB041AB5EULL, 0xACB5B802177056B4ULL, 0x59ECE4DB7C57944BULL, 
            0x5BC21234BE6B9F29ULL, 0xDA908C5527489E39ULL, 0xB2C5FAB44A451F64ULL, 0x7CFE5E930A46FF7AULL, 
            0x617702B89C1CCE5EULL, 0x50EDF8F327054395ULL, 0x918D0C223A674A79ULL, 0xA1B30A28A97E51EAULL, 
            0x204D6395D97334FDULL, 0xE83A98C2829BA784ULL, 0xDAEF46AD47228A44ULL, 0x0098F860CC531466ULL
        },
        {
            0x03106348B825523DULL, 0x33C2D594934CC769ULL, 0x44A3233C8306EB63ULL, 0x29EEAFA0390241A4ULL, 
            0x2294178857DDE6D0ULL, 0x9E876541723645C3ULL, 0xA95EADFBEB17DF3DULL, 0xA28ACC00CCA695DCULL, 
            0x5BB40046F905B08EULL, 0xA5E02B53EB9486C8ULL, 0xEFBA6208C9D64592ULL, 0xE2F8236CE81C31D3ULL, 
            0xFA4C39691ACDB533ULL, 0x54EBB1DCC89148BCULL, 0xF23F6CD145838137ULL, 0xCCE76A3CA4814CDCULL, 
            0x4D04F1F684E93DAFULL, 0x12621809C858CEBBULL, 0xA531DB680955A8A1ULL, 0xB6C9E15EA4B4F724ULL, 
            0x1A61F2C5CC2C03D1ULL, 0xA5CD4E2D047C9742ULL, 0xF47DA208270073DAULL, 0xDB28AE33243451B5ULL, 
            0x30E3C2FC3F159BE7ULL, 0xF1B80A3F4730EA83ULL, 0xA260F65A90127BEDULL, 0xDDC5C0361D458441ULL, 
            0xB3B8496D605774D0ULL, 0x36E91A67A32F1CF6ULL, 0xF64A9FBB52D4BF74ULL, 0x5DE1518DF4B02F22ULL
        },
        {
            0xDECF69E24F99C6A0ULL, 0x38A51D8FFEDAEE76ULL, 0x7D976B40CD34DF84ULL, 0xF0F3F6E0299D9563ULL, 
            0x76326E5BB6860F98ULL, 0xD85C69B6D0B9DF53ULL, 0x0E7A1E89DB81403DULL, 0xA246A997E35F77F6ULL, 
            0xD0960408F097EC99ULL, 0xA2F72BA45DCF7643ULL, 0xF35898F0EE9096CCULL, 0xBE0CCE5633C2246CULL, 
            0x80A458B01C301AF3ULL, 0xA75E9A93562517C6ULL, 0xA17267ECE0326E2BULL, 0x50BD36705F584435ULL, 
            0x96A7E9D17E2EE232ULL, 0x6C8B2FE0504BCEDFULL, 0x07FD70CFDEE588BCULL, 0x794761FED9EF3E1BULL, 
            0x49BB97CB4B827E1CULL, 0xB7EBB230A2B58CFDULL, 0x809C79BF4DB81DC6ULL, 0x3FA07B15894D09E8ULL, 
            0xFBB79AF86B8DD8F3ULL, 0xD814A43D41768518ULL, 0xB57FC04220AB7BA1ULL, 0xE764D9109570F4A9ULL, 
            0xEF875B14F2FE6F11ULL, 0xED9C7A8D73EEB850ULL, 0xA209DF2271A94D87ULL, 0x2383222765D11FB1ULL
        },
        {
            0x8070FE0D8963056AULL, 0x67378D1A47F2B1B3ULL, 0x0DCDC47DC6DD2DE3ULL, 0xD966957C0999DA12ULL, 
            0x3D0DCF0E88BEAA99ULL, 0x63AEA7C195C291CAULL, 0x06BAB1E94DD3AAF8ULL, 0xA5796F5875D8675FULL, 
            0x8641748C6A666436ULL, 0xD1E75C2405285D7AULL, 0xD8D4E26B6562F6E2ULL, 0xDC62A048699AD08CULL, 
            0x68D8A7C4ACC1C63CULL, 0x76A9D5C06EA51E53ULL, 0xBAA6E537C027CBA1ULL, 0xC6B5DD5783A1BE11ULL, 
            0x547F708E23FEF6EEULL, 0x17767C4E480019BEULL, 0x0C7F5A5810026039ULL, 0x5D866B8DC624B892ULL, 
            0x61FBD800EEC2CDEDULL, 0x66652BC29EEAF480ULL, 0xBDBA85A9CC52CB93ULL, 0xAAB4EDDA670F3446ULL, 
            0x463AA958CA963DE8ULL, 0xAB5602D2566576D9ULL, 0x4055803F2FFAF313ULL, 0x2B4AF09B7029196FULL, 
            0x1454BF92A170CA29ULL, 0x25BB5BBF581A76EDULL, 0x2D57A8ED41D3992BULL, 0x37A62BB45014F6E7ULL
        },
        {
            0xBC51B154E5B6A829ULL, 0xC4F9884FE0BB5D04ULL, 0x3E5A6C7CC8B81008ULL, 0x2FEA5F9CE8289433ULL, 
            0x581869E480A75DCDULL, 0x5D61F3D9A2FBC50AULL, 0x38B09CCA5FEDA874ULL, 0x574D8FA1FC04BDE0ULL, 
            0xEBE955DC519AAE81ULL, 0x69C8256DC546219FULL, 0x509F88DD3230D125ULL, 0xB209B867B08F9C1EULL, 
            0xDFA833DA4A00CF41ULL, 0x4163234C41446B6AULL, 0xB61BB62F30C28D31ULL, 0xDDC9D444301954BCULL, 
            0xF3732DC9FCDCD8FFULL, 0x127C54A92ACFBCEAULL, 0x74EBC368DD8963F2ULL, 0xFE9A66BC1A89179DULL, 
            0x99ECB61D76194F32ULL, 0x24F884ED0835DB50ULL, 0x8A13BDC8547EBA1AULL, 0x5BE91FCAB4ECFB91ULL, 
            0xF1110209C7E3DE4DULL, 0x3754F8A0A1D57CBCULL, 0xBD1A452B8522017BULL, 0xA376A570624B524AULL, 
            0x274308FF27CED4A8ULL, 0x6A734586431A7D8BULL, 0x01702833672ADA21ULL, 0x86CB3C32D0B2D880ULL
        }
    },
    {
        {
            0x2AFD7324F9B75A2EULL, 0xA56CD49FE47A17B8ULL, 0x3D0231D85B9CB263ULL, 0x1BA3B33432EB4CC3ULL, 
            0xB0BD198B75A27C22ULL, 0x5F9CD74C31D0D9EAULL, 0xBCFC2BD1369D9EEEULL, 0x2C6CEC7589EBE60BULL, 
            0x6130FC89B0AE1F16ULL, 0x59774C5FD4BD0D36ULL, 0x16F6AD734B2B1967ULL, 0x963686F39AC3998DULL, 
            0x74B835CB5FD9DE3BULL, 0x0A04ABB7213DF8A3ULL, 0x7895F712E6181F57ULL, 0x31526B557F67CD3FULL, 
            0xC4732453FF6596D0ULL, 0x90DDDBE71EC33F0EULL, 0x4C3395DD51ED6E0CULL, 0xD2F8C81CDACD6AF1ULL, 
            0x9DC09A1337D336A2ULL, 0xDF6656BCA66C7029ULL, 0x5DFD04C8636C3F76ULL, 0xE954DFF6880783F1ULL, 
            0x968F3F58CD2B5C7CULL, 0xAA20688CEBCC9F39ULL, 0xB2A19B0958814046ULL, 0x1EF2D7A3AB19F24EULL, 
            0x02B4EF8108576954ULL, 0x4944A4E92E464B4BULL, 0x0D8B38FDE788BAF1ULL, 0x304633D944A99256ULL
        },
        {
            0xC81CE662B3EF47EAULL, 0x1BC992FEED2A82ADULL, 0x6DE0310A07AFF905ULL, 0x1456CA4E25010BF3ULL, 
            0xEE4AF530394EBEE2ULL, 0x91A41705A42C4810ULL, 0xCD2EE922424511EEULL, 0xEF6BC68FB923D668ULL, 
            0x6550FC41A6FAD3C0ULL, 0xDFB1D66FA67B469EULL, 0x0888C4D539D68AA1ULL, 0x1988BF66D4A4005BULL, 
            0x3F09E66354D01CADULL, 0x2143E4CAD595008FULL, 0x1A8D27E55ECDCA39ULL, 0xFA506EF85AA1D6D6ULL, 
            0x3CD2ABCACD0E3EADULL, 0x6BF574F834607FD6ULL, 0x651E39D2D58E2435ULL, 0x52256B5725BA7033ULL, 
            0x9A68B6D26F05111CULL, 0x78345D943EA98539ULL, 0x720E8C00821D1349ULL, 0x9DC1338CCFCBA44EULL, 
            0x87243F271A32AA80ULL, 0x2B26095C6B2A8701ULL, 0xC42862C0AA922C4AULL, 0x7012930C60A5CDE0ULL, 
            0x724349EE8F251E45ULL, 0x1F79702050CC05D1ULL, 0xBCCD9CAAC8246FB3ULL, 0x1A5379EE3D7EC71EULL
        },
        {
            0x5836E26F8FD8ACC6ULL, 0xB09555525BED90D4ULL, 0x02256FD921B522C3ULL, 0xAB29862DE25E54FCULL, 
            0x05A778A58A9BDFB7ULL, 0x8EB4DCEED43204C4ULL, 0x5184CD45DC2BC440ULL, 0x4CBABD56506F5C3FULL, 
            0xBBF89705DD11AC53ULL, 0xE1F544A1BA395CEDULL, 0xAB235BBF581D91A0ULL, 0xC17CA39CF23AAECBULL, 
            0x0984453897162C34ULL, 0xA466B9D91D6A3CDAULL, 0x4B42A2538B5F7987ULL, 0xCB3E66F7B3A9B099ULL, 
            0xFEBBB2994CB0FA19ULL, 0xEB34FA753020643BULL, 0x676162B78FC47E93ULL, 0xF5DA37DB5E7B86AFULL, 
            0x03368B3E03329754ULL, 0xCD004E8A39EC30B5ULL, 0x6CFDFA9558C9AD53ULL, 0x384A7A344CA79719ULL, 
            0x3FE097ED582DEECCULL, 0xFCC37F25AC6CE176ULL, 0xB043E89A6A0DD926ULL, 0x97371F84FF43A5ECULL, 
            0xB1FCC5EB825B20CDULL, 0x64E882B503E40DF5ULL, 0xC558E48B895A2F8BULL, 0x4FDE1DFD9D964B41ULL
        },
        {
            0xF23C17E263174268ULL, 0x30C78B80FE372690ULL, 0xB2FEE9D22628BB7BULL, 0x752E5967DCBE1412ULL, 
            0xA20208C934D85138ULL, 0x1803C0624D26BE4EULL, 0xE95DA21C8F015873ULL, 0x451788C28B82B7F0ULL, 
            0x319492D2A2A0AC9EULL, 0xD0E5E204AD9829EEULL, 0xFF46E8BCDBA5C54EULL, 0xE79F050A47AA680CULL, 
            0xF2DA8B2B65016EA3ULL, 0x9B64DAEB35A15EBAULL, 0xA511F36E7BEE4D31ULL, 0x835BEE70871FC4EEULL, 
            0x5797EFCF437743FFULL, 0x565D0780DE731A88ULL, 0x4FC438740C58EDAEULL, 0x2B0A221EBD0D061FULL, 
            0x43BC956D58259A09ULL, 0x1C4E9C095DC9231AULL, 0xC397B4B4704573E3ULL, 0x3156389C319C26FDULL, 
            0x46EAC2F9E5A5BA4CULL, 0x3571C25E33430D7AULL, 0x0B0000CB5A18FF6BULL, 0xA1CF882110B0A41BULL, 
            0x6CA90C6B761299C7ULL, 0x94B14BC421F7A8E0ULL, 0x1CEC5A80C24D3246ULL, 0xAE769E88CFFE231FULL
        },
        {
            0x79327D1CFA02DE4EULL, 0xA21887008D49398DULL, 0x6D1C3DB691C472DDULL, 0xC0289704F83873E4ULL, 
            0x0459BE3604047FBDULL, 0x4DE78D725D746D5FULL, 0xA7EB84A2C5EF1EB9ULL, 0xF3DA82159458117AULL, 
            0x023843C1D779FBC6ULL, 0xB1683722ABBE67AFULL, 0x3B29210EBB032138ULL, 0x9D6D40DCF64939E8ULL, 
            0x4A5E09C09317436BULL, 0xC24207F379239A99ULL, 0x943A862C7BABA408ULL, 0xA30C15A64973B4E4ULL, 
            0x6B174819EC9645F9ULL, 0x35888D221BD9C2F7ULL, 0x29D76A3F388BA364ULL, 0xE104573618877C4DULL, 
            0x050744DACCD19EC7ULL, 0xD3B4FE9590138E52ULL, 0x9B046478C1F18558ULL, 0x81F37BC051DB9C19ULL, 
            0xD3F3AC8FA14C96A6ULL, 0x82950E5C895846FAULL, 0x086859AF808B028FULL, 0x1EA4EA6E582E6CD1ULL, 
            0x42D57D57A44492EAULL, 0xB54E23E6AB25740BULL, 0x6A47F7EEA9896462ULL, 0xC842CBC87853EEBBULL
        },
        {
            0x553785765C8E2F21ULL, 0xB52247E0A809C92EULL, 0x7CABDC9611BA55A7ULL, 0x8137148797D431D8ULL, 
            0xAC71A8AF1CC07C2AULL, 0xE489F0DE2A56082DULL, 0x9349FB9A57108E61ULL, 0x7E816FFA750F6822ULL, 
            0xABD38A2662E725F6ULL, 0xB68BB62E0E5A0DC5ULL, 0xCE66C4023EFE866FULL, 0xB6FF97B6F2CDE0C3ULL, 
            0x9A21B061879BEC2AULL, 0xBA9E5E0F6417AD5DULL, 0x8792FA41DE12C500ULL, 0x6B49988B8656F92EULL, 
            0x10EDC94A107A30E4ULL, 0x45C84D891BF7AF15ULL, 0xCAF6F0E40B7464C2ULL, 0x6557E2134A364DE5ULL, 
            0x48EF01F289F1536EULL, 0xD53180B33D75B030ULL, 0x22ADD1544175A133ULL, 0xE7B17213444469F3ULL, 
            0xEB3DF934D73D9863ULL, 0x2377490AD88CD434ULL, 0x14BA5EA0FFC60874ULL, 0x4F64363982B92252ULL, 
            0xDEAD13EAF0FC36C9ULL, 0xD276BF7E4AB18369ULL, 0x99B393A4DE5EC609ULL, 0x08FF0892A55F13FDULL
        }
    },
    {
        {
            0xC383E5F791709DCBULL, 0x91EEA3973128BDFDULL, 0x0A3B546EC5F294E0ULL, 0x96A47FC426C63A6BULL, 
            0x758DA1140C46FC04ULL, 0x992ED3DFE79332E5ULL, 0x8BEC7BC6F325D290ULL, 0x47D373FFEE969D8BULL, 
            0x5A9753772A23F43BULL, 0xE5629F3EDEE968C1ULL, 0x688F3B12F3615086ULL, 0x54E398775DFA892BULL, 
            0xF8E8F066A998AD19ULL, 0x62E17591C722FA81ULL, 0xA9137622F4A204F5ULL, 0x2128C7325306EE50ULL, 
            0x821066D63D27AE73ULL, 0xB7FB3CA600410561ULL, 0x82890C8FC896EA35ULL, 0x77E08C0B3D28B3F9ULL, 
            0x7913FED85CB171F7ULL, 0x89DE11AA66820044ULL, 0xC84E95D5EAC90271ULL, 0x4F118FF2B9C578EBULL, 
            0x26770A2A4713D715ULL, 0xDAD3E3D929AC815AULL, 0x3168CA1E8F2CF53BULL, 0x28E83F29D43D7A8EULL, 
            0x5219D00384FDBD9CULL, 0x4B4E1AA2DDA77D03ULL, 0x935F15B1B1AFEFE1ULL, 0xE33CD686CB91EE4AULL
        },
        {
            0xCF2047C266C756A8ULL, 0x9CC826138F38A233ULL, 0xAE6DFB746C40B159ULL, 0xCE6E118E1AC39165ULL, 
            0x28CF268C2D0C92B8ULL, 0x0CCA428D11B6D87BULL, 0x80E0A317643D4930ULL, 0xE7A82D8E55134055ULL, 
            0xDBED84B674913D36ULL, 0x5D63DBAF460C026BULL, 0xB902E7B0EDFD3643ULL, 0x3A0BFA0C74A7EDFEULL, 
            0xDA32E2644052E9E5ULL, 0x1176B288AA3EB983ULL, 0xF9AAEE2509C5D139ULL, 0x481CDDE41817DF7DULL, 
            0x715A43B132446BC8ULL, 0xA15269ABECB0AE58ULL, 0x6AED972150D331D9ULL, 0x435C88EE2E9EB7FCULL, 
            0xDCAE41F0B581CCAFULL, 0xCF8E16851C75CD49ULL, 0x8772495913D5E1D8ULL, 0xE348316C78E837B6ULL, 
            0x33843FAC6B251491ULL, 0xB5568D3AD51DBD00ULL, 0x54C37CF39567829AULL, 0x61B8A4F12725BF0DULL, 
            0xA70A8893001A792EULL, 0xBC647456EC7AE772ULL, 0x971DC9B41CC4916BULL, 0x6BEB39F5C458D748ULL
        },
        {
            0xF8411E26194FF5CEULL, 0xFD76AF415B0AB84DULL, 0xE62EF4302F3EC251ULL, 0x25D13252C31D9485ULL, 
            0xE9CB8592E2A24554ULL, 0x18AFF2607A6423A8ULL, 0xD3B401CDB807CC3EULL, 0x342DC01DC7808F29ULL, 
            0x7ACFF28E82D71FEBULL, 0xC3B33B8F32D8F3D0ULL, 0x17473570F2CCBD2AULL, 0xB4A6BD134AF0B2CBULL, 
            0x870C7AB844DD75B9ULL, 0xD244ED436B5B2A23ULL, 0xE1971305E1436A81ULL, 0x90832DAD0A7084C1ULL, 
            0x2B0A091967A15787ULL, 0xD7FE6C01FE620CC3ULL, 0xF828C34AA2220934ULL, 0x2CDC42237CE42500ULL, 
            0x509997696CD5B0EAULL, 0xE2EC18925DF3A890ULL, 0xF5D7224D7489F36FULL, 0xE05E4582EDB96EE0ULL, 
            0x552E673C13340D77ULL, 0x9469C6FD576AF114ULL, 0x11D2D1D9480422E7ULL, 0xAE00ED2D3D1FFD39ULL, 
            0xB568756D9230BAD7ULL, 0xC586265B75F89AE0ULL, 0x2104B444F31056F3ULL, 0x27CCFB039F2A8FBBULL
        },
        {
            0x0A0F8E3CC497CC52ULL, 0xFFE8799E239FBCD7ULL, 0x04DF4BCDF5A58CD8ULL, 0x2B1CA92F8C755BD5ULL, 
            0x29F2072191E62EBDULL, 0x889E2F9D01352B77ULL, 0x4D653C23309587FFULL, 0x2B999CCEEFE2E844ULL, 
            0xCE7EA3B4D2E24E3DULL, 0xC27AB05768BC7C6AULL, 0x0324D38EBBCB8B47ULL, 0x14EF7C021173F093ULL, 
            0x89FF810260DA0A48ULL, 0x3353AE9E922A7FCBULL, 0xA003CE6D34779252ULL, 0x2906E42374D41DF7ULL, 
            0x1D86C0163061E1D1ULL, 0xAFF65B70FB2A2BFDULL, 0x7903E655C902C861ULL, 0xF8046864322DC80EULL, 
            0x135ECBB60D1E51BBULL, 0x62A168BE1194EC8AULL, 0x8CD89A27455CA90DULL, 0xD4E755E815B8F8DCULL, 
            0x93009A5E1BA21823ULL, 0x354CD5B4C24323D7ULL, 0xF9AB55660D105B4BULL, 0x2411B88F02233201ULL, 
            0x33C2CE14F9DC191CULL, 0xF97B6221A4A91488ULL, 0x48FF324265195ADCULL, 0x44B37C7FB959AFB1ULL
        },
        {
            0x75A7089A1F56669BULL, 0x70648E253CDD0B5AULL, 0x58E61B8920FCD8DCULL, 0x307CD3DF22F1338BULL, 
            0x5D1FAF51087D01E7ULL, 0xB56E51FAE2C6D48CULL, 0x69500DD970761F70ULL, 0x059BE63A647B6E71ULL, 
            0x45AC443EE85435B5ULL, 0x91172DE2876ACD48ULL, 0x3D563ACD9635F71EULL, 0xCD6F4FF863931785ULL, 
            0x9C71064CA6FB5A9CULL, 0xEE4C8F8E531B9C61ULL, 0xDC994D1F930909D0ULL, 0x6A1B80A88C7D86E6ULL, 
            0x2792A8C8BF1E29FDULL, 0xA26B474E9F0EE6D2ULL, 0xA05836B9027737F5ULL, 0x866F456FD9ECE3FDULL, 
            0x32F2C5CFE04ACE8BULL, 0xE1C6FFC3F10745DDULL, 0xCBDC31530921011FULL, 0x8924DE199F74BC40ULL, 
            0xB5DFD7CEA3BE7022ULL, 0x7A6AD2797D34EB85ULL, 0xCC68C5EFD0675B7FULL, 0xCC98A6CB603EDFE4ULL, 
            0xE6C1C9B6652F87F5ULL, 0xC1BF1A714D9BAC85ULL, 0xFD42929F5E45BBF9ULL, 0xAC4B43EEE6F7AF54ULL
        },
        {
            0x35BD124AF53C18B0ULL, 0x208C43A50A274F00ULL, 0xAB9DB3AA6D58801FULL, 0xFEF7C04A8A02B41CULL, 
            0x54DA318BBB7E66F3ULL, 0x9EDFADD90684DF7CULL, 0x8A5FFD2DB72D7C52ULL, 0x80F461B04E3ACC67ULL, 
            0xBAB134C99E969374ULL, 0x27444A3DECB296B3ULL, 0x80295D0AAF4E0BD6ULL, 0xA84242BD09ADC6C7ULL, 
            0xFD519670180D7F29ULL, 0xA8963E39DF3F4EE3ULL, 0xD3A95CAC4C412DBEULL, 0x3D433B88156FA301ULL, 
            0x710367F3D207686FULL, 0x7D58E712130AAC1EULL, 0xDC2CA1DCD494B987ULL, 0x5D08441417FE1908ULL, 
            0xD3F063F22DA821CAULL, 0x172CD0B2BEED27EBULL, 0xAEC8DCA563D62B43ULL, 0xE125275D28BD6484ULL, 
            0xD12E70C8F7196929ULL, 0x10E50CA87045D38BULL, 0xC71E9CAC94AA2B17ULL, 0xFFFCCAAB40089AD7ULL, 
            0xD471606F95BDFAADULL, 0xD326472825CE4DCBULL, 0x2AC0754218FA596FULL, 0x7379D70C226B56FEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseHConstants = {
    0xF06F953D2DF9BDCBULL,
    0x79BB2FBFBC92B761ULL,
    0x86EB3DB5592F75D2ULL,
    0xF06F953D2DF9BDCBULL,
    0x79BB2FBFBC92B761ULL,
    0x86EB3DB5592F75D2ULL,
    0x893F85DF01D79655ULL,
    0x8E2F9B725C834A2DULL,
    0x99,
    0xF9,
    0x9B,
    0x3C,
    0xBF,
    0xEC,
    0xEA,
    0xFB
};

