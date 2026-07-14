#include "TwistExpander_Vega.hpp"
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

TwistExpander_Vega::TwistExpander_Vega()
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

void TwistExpander_Vega::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xCB623305F55444BBULL; std::uint64_t aIngress = 0xD32F758076C93F7CULL; std::uint64_t aCarry = 0x9363B08D182E98ADULL;

    std::uint64_t aWandererA = 0x8ED0B7C43870808BULL; std::uint64_t aWandererB = 0xE6C87F401CEFD238ULL; std::uint64_t aWandererC = 0xD1402283531AB2DDULL; std::uint64_t aWandererD = 0x88BA69E778F09B0CULL;
    std::uint64_t aWandererE = 0xF5565BAC52E3619BULL; std::uint64_t aWandererF = 0xAD568B5B8CDA411DULL; std::uint64_t aWandererG = 0x9E0488F37187AC24ULL; std::uint64_t aWandererH = 0xC280A7FB6F28B851ULL;
    std::uint64_t aWandererI = 0xE9A597FD5592E48EULL; std::uint64_t aWandererJ = 0xC4D3DFE93BE4C978ULL; std::uint64_t aWandererK = 0x90778365840CA373ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17712454452125437276U;
        aCarry = 11073756144670663542U;
        aWandererA = 13930960494861264144U;
        aWandererB = 17452471224486892208U;
        aWandererC = 12164936373815180447U;
        aWandererD = 16159009815660024660U;
        aWandererE = 14810583078545583008U;
        aWandererF = 9434010653118364930U;
        aWandererG = 10024947873531868976U;
        aWandererH = 12348944249703216661U;
        aWandererI = 15721592318844808676U;
        aWandererJ = 17467868597170111166U;
        aWandererK = 10070272023634207233U;
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
    TwistExpander_Vega_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Vega_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Vega_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Vega_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Vega_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Vega::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x8957653570A22C01ULL; std::uint64_t aIngress = 0xD8AECFA94AB07006ULL; std::uint64_t aCarry = 0xF297A965A66F2337ULL;

    std::uint64_t aWandererA = 0xEEA76CDDA8A1B84CULL; std::uint64_t aWandererB = 0xF49D4E56CF9377C4ULL; std::uint64_t aWandererC = 0x9831D12CADE3037BULL; std::uint64_t aWandererD = 0xCA9A5E85B3B32B53ULL;
    std::uint64_t aWandererE = 0xF50403B314A193E4ULL; std::uint64_t aWandererF = 0xBF51BDC80E1DD48EULL; std::uint64_t aWandererG = 0x8B13E10E17BFE962ULL; std::uint64_t aWandererH = 0xB4D5D6392596BF13ULL;
    std::uint64_t aWandererI = 0xD49B696F552C3E46ULL; std::uint64_t aWandererJ = 0xE4F3A13B313A67DBULL; std::uint64_t aWandererK = 0xEB99CCB2ED031866ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16943224404961306913U;
        aCarry = 16627898701527540074U;
        aWandererA = 11369068973772916656U;
        aWandererB = 17543184772951224472U;
        aWandererC = 11438035289631885844U;
        aWandererD = 12345403437566409430U;
        aWandererE = 14740518121511819568U;
        aWandererF = 15652191271733956102U;
        aWandererG = 15404888527196138705U;
        aWandererH = 13496376464900432582U;
        aWandererI = 14595380614286318412U;
        aWandererJ = 13921406583547801246U;
        aWandererK = 15754671623469265669U;
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
    TwistExpander_Vega_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Vega_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Vega_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Vega_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Vega::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE7BE76817EC5D994ULL;
    std::uint64_t aIngress = 0xCE4C308D57A3FA5CULL;
    std::uint64_t aCarry = 0xC0D4390B5A4EF921ULL;

    std::uint64_t aWandererA = 0xCF1B250C07852EC6ULL;
    std::uint64_t aWandererB = 0xE06F10AFA681AD58ULL;
    std::uint64_t aWandererC = 0xEBE76DA99317D3AEULL;
    std::uint64_t aWandererD = 0xB9F8AAF027B4B885ULL;
    std::uint64_t aWandererE = 0xD3D3093F74F193B2ULL;
    std::uint64_t aWandererF = 0xD105FBF6FA246CDBULL;
    std::uint64_t aWandererG = 0x8B684F2E89DE08ECULL;
    std::uint64_t aWandererH = 0xB16E1FB5E7CDCA62ULL;
    std::uint64_t aWandererI = 0x86A4F17C5B3189A2ULL;
    std::uint64_t aWandererJ = 0xBC5FB13C9CE0D9EDULL;
    std::uint64_t aWandererK = 0xFEAC9BCE3BAF503DULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
    TwistExpander_Vega_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Vega_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Vega_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 33 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1785 / 1984 (89.97%)
// Total distance from earlier candidates: 58165
void TwistExpander_Vega::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1842U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 345U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1238U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1350U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1018U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 856U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 295U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 636U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 868U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1149U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1860U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1253U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 77U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1851U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1526U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 733U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1761U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 944U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1614U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 165U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 482U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 118U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 95U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 183U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 723U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1631U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 310U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 202U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 991U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 167U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 121U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 26U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 455U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1421U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1000U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1572U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1021U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 113U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 141U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 139U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1077U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1534U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 83U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1099U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 960U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 737U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 413U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1845U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 779U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1606U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 51U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 561U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1045U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 259U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 241U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2047U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1015U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 974U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 840U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 777U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1695U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2027U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1902U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 20U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 486U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1883U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 88U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1022U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1756U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1908U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 536U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1150U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1564U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1956U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2026U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 496U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1479U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1112U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 147U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 282U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 93U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 336U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1139U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1733U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1649U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1095U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1402U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1671U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1219U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1749U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1365U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 866U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1673U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 705U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 946U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1105U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1009U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1855U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1579U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 363U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1049U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1080U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 255U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 758U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 432U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 33U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1615U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1235U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1404U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 220U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 393U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 791U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1550U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1837U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1383U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 982U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 587U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 7U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1074U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 14U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1998U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1538U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 435U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1474U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 411U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 119U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 375U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 606U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Vega::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x99345E8385F37E68ULL; std::uint64_t aIngress = 0x89FA985A2B03001FULL; std::uint64_t aCarry = 0xD42BAF4707220AA9ULL;

    std::uint64_t aWandererA = 0xFBA30EA3F4644EDCULL; std::uint64_t aWandererB = 0xEBD5EE0210618F07ULL; std::uint64_t aWandererC = 0x9D0E0C0F316D2469ULL; std::uint64_t aWandererD = 0x914A31E595F32705ULL;
    std::uint64_t aWandererE = 0xF02D09426DDAD35AULL; std::uint64_t aWandererF = 0xCBC0123BF375DA0EULL; std::uint64_t aWandererG = 0xBCFBBDABE903B56DULL; std::uint64_t aWandererH = 0xB38663792A728FEEULL;
    std::uint64_t aWandererI = 0xBE26869161C6D836ULL; std::uint64_t aWandererJ = 0x97A9E4675267A791ULL; std::uint64_t aWandererK = 0xE7CC8E1162DA96A3ULL;

    // [seed]
        aPrevious = 11287296995267747789U;
        aCarry = 13069338149772522477U;
        aWandererA = 12710042860371677514U;
        aWandererB = 15518627096015509122U;
        aWandererC = 13364563199892703773U;
        aWandererD = 16326422953665583006U;
        aWandererE = 17527414883610847929U;
        aWandererF = 13259630939967227907U;
        aWandererG = 11193894127494056940U;
        aWandererH = 14663493433977430275U;
        aWandererI = 15831071597177439779U;
        aWandererJ = 17052902189477293345U;
        aWandererK = 14532704385433958286U;
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
    TwistExpander_Vega_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Vega_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Vega_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Vega_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Vega_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Vega_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Vega_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 33 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 17281; nearest pair: 447 / 674
void TwistExpander_Vega::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1786U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3425U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 738U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3328U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6165U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 158U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1071U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 600U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5750U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3821U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 743U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4840U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5389U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8111U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7429U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6886U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 902U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1250U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 934U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1328U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 466U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 837U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 257U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 483U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1254U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1934U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1697U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 489U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 641U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 714U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1795U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1382U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1642U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 575U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1463U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1654U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 33 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 17279; nearest pair: 474 / 674
void TwistExpander_Vega::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6904U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6303U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2031U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2161U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2873U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3629U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3678U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3664U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 8128U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7390U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1912U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1355U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6413U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2151U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4133U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2095U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 214U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1894U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1087U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1807U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 547U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1941U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1110U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 942U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 938U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 816U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 252U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1867U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 254U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1061U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 203U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 567U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 2024U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 935U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 411U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1970U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Vega::kPhaseASalts = {
    {
        {
            0x365FA1152BC05A8CULL, 0x75C52FA025A64DEBULL, 0x4E9C86440C820F07ULL, 0x452C1A59B3684D6FULL, 
            0xDB92D29B0E9A5EA2ULL, 0x6E8D89BF7686D7EBULL, 0x7B7F059614FB7D64ULL, 0x677B920513121B55ULL, 
            0x9EFBA88B25A88AF9ULL, 0xFE8F024C8F7B92B9ULL, 0xB1B052A79FEDA863ULL, 0x6051429BCD18B0E6ULL, 
            0xAB96FA76292999B5ULL, 0x38D9D15F11ECFA00ULL, 0xE4B30933FCEDE7DEULL, 0xAD9CA29F1E7F55ACULL, 
            0xF89043B64D9EC3ABULL, 0x843B67640F6EB7E2ULL, 0x91F4A9688B378BE9ULL, 0xCA67E8417C8BEA1DULL, 
            0x8F3123D0060B7070ULL, 0x3A52C6AEE26D4CD3ULL, 0x17AFC23338EE7196ULL, 0x7EBC05512FE64919ULL, 
            0x9E8E8B75A70827F6ULL, 0x88DBA24303430940ULL, 0x5BD9F0CB62E97452ULL, 0x7439B1B2C45366B1ULL, 
            0x1BA0E4A30844FF5AULL, 0x4BA557E4975D838AULL, 0x3EE17B402521ED6BULL, 0x40CF5B445008F8E7ULL
        },
        {
            0xE4B1D257DB5884A1ULL, 0x150B8539656EABC8ULL, 0x22B567F3DA557F5DULL, 0x539386CEDBFB6AF8ULL, 
            0xC6F04048074A89CFULL, 0xE489532AAF6C9194ULL, 0xB8B01A36E58AA7E0ULL, 0xF328CF656E01275DULL, 
            0x88DBEB4BECCFE9CBULL, 0x6E8F30704EEAA7B1ULL, 0x38CC43B428AA516DULL, 0x60046F02C5998E2EULL, 
            0xD4BA1D470E5C295DULL, 0x25BB123B6F2B85EEULL, 0xA6FE70D3E10549EFULL, 0x73FAC5A0AC4E8ECDULL, 
            0xC3801F5A39804251ULL, 0xF1753823C06463DCULL, 0xD6CCE80AA3A82F1EULL, 0x3484DB6A44C2EFD0ULL, 
            0x4CD237F796B3BB45ULL, 0x47F736C3DEDBAF37ULL, 0x526CF2CE51704132ULL, 0xB8E149160B40D2E0ULL, 
            0x030ED572A999DDF9ULL, 0xB42CE4C2CA3BB2BAULL, 0xD453631851CD9B78ULL, 0xBDCC580977E32937ULL, 
            0x371660DC9CD85304ULL, 0x57FF149FD91AD83EULL, 0xADE677F6D2912E1AULL, 0xF80E3302CA858C7EULL
        },
        {
            0xB776B01BA856CFB9ULL, 0x6D03BBF8D9230452ULL, 0x65145C1E99CCC36EULL, 0x02CCEAB30D39DA68ULL, 
            0xB400C94CB7081219ULL, 0xCEEAE74245E3ECF6ULL, 0x831EE2AACCD14B94ULL, 0xF57A2889F3A4215AULL, 
            0xDB5E4D5A63C7FE65ULL, 0x81C9D0F1C181E677ULL, 0x9C6C35FB9DE5CDD4ULL, 0xD97067478FDB78E4ULL, 
            0xDCBFC2C0DC01D76FULL, 0x61EC3598F54C4B96ULL, 0x0B4EF724C370B897ULL, 0x0700FDB50E07C574ULL, 
            0x8138E50BDBAC2024ULL, 0xFCE0C75F03B21690ULL, 0x257C41336D8D4FDAULL, 0x18F70291F4FD2A81ULL, 
            0x165C603D140A9D32ULL, 0x102D3BF8ED630948ULL, 0x3ED863B86EB08DC8ULL, 0x9C46D037358CC101ULL, 
            0x42811C4D79410900ULL, 0xC762CE528672DB4BULL, 0x0E5AB6915D2DC62EULL, 0x26097A03648E3C7FULL, 
            0xED768AFB2DB5FD52ULL, 0x03B79FD6A9DD6CF6ULL, 0xD4A945C2430B6379ULL, 0x43C005E5DA542168ULL
        },
        {
            0x34B10BFDC26C9186ULL, 0x48CC9D7942A2CFCCULL, 0xCAD7B65D19CD79DBULL, 0x9756CAAC379DC267ULL, 
            0xB5FE23125FF6C191ULL, 0x276D0E78AFF95B2FULL, 0xCE491ED5E38A7D86ULL, 0xB13D895807C1A5B6ULL, 
            0xCD91E1DE7943050FULL, 0xCF4DF1C9EBD1A974ULL, 0x614716DDF115DBADULL, 0x72E4FC179090E28EULL, 
            0x29FDE22E946EEA55ULL, 0xA7FCEC8D1F30BA4CULL, 0x2A6B1D7F4EF6CCE8ULL, 0xABF86B49A5BFC2E6ULL, 
            0xE9F4E17B051E21CBULL, 0x8FFADDD38094B595ULL, 0xFD6178D8E12BF4E1ULL, 0x56634AD9ED5EE719ULL, 
            0x98E9D1E99140C633ULL, 0x2E859057D6920E15ULL, 0x69C41D50ECA52944ULL, 0xBB9805E34CA46BACULL, 
            0x7440A35E9FBE4093ULL, 0xBF2D8C7719606CFFULL, 0x513A00A7CDF0C46EULL, 0x828A68EBEA1C6CDEULL, 
            0x0E19243BDC089A41ULL, 0x39DDA42020F0BE01ULL, 0x111661BF439E5A5AULL, 0x32E1E3CB1B393319ULL
        },
        {
            0x5CA662D45A2B5FFFULL, 0xC627BC5C88B14DC1ULL, 0xBA7093AB4D1A495BULL, 0xC5142C12336025E8ULL, 
            0x13F4BE28CCCDF066ULL, 0x0C3EB829C9E3E39BULL, 0xB696BF00D23FB311ULL, 0x7B395D7677251D03ULL, 
            0x6F5796B98CA76D0AULL, 0xC4FC532FCA460BC5ULL, 0x215440FCCE6BB852ULL, 0xB7700F4B4AF78A58ULL, 
            0x0E91D761A91B57F2ULL, 0x3F0B7AD6CEFEA67CULL, 0xD04C5FB42F3C4B45ULL, 0xC520FE01456F66AAULL, 
            0x592246BA7A404AB4ULL, 0xF79B345B8E3DD563ULL, 0x248FC797D1179966ULL, 0x53B901A2DD8C60ADULL, 
            0x2001613B3A2502F8ULL, 0x5C8F1861EE51B841ULL, 0x08E5C4DB22D33D71ULL, 0x014B6BA4493C2356ULL, 
            0x00A7FD3A5B74229FULL, 0x326F15891B51DE49ULL, 0x8BD5D2BB789BD73EULL, 0x18C6D17B0A383520ULL, 
            0x00DD2DF52970792EULL, 0xE0E1EB57E3182310ULL, 0xC4006DB6DCE4227AULL, 0x0A3E0DC2792E6999ULL
        },
        {
            0x3D2EA40DD9296324ULL, 0x6A19FD62406FA7FEULL, 0x2766C8E961787E23ULL, 0x856C357AF5AC222DULL, 
            0xF45296575EE85383ULL, 0x9FB14D5FCB4A9411ULL, 0xF8F9BCDE9476A035ULL, 0xDC18D28FF9B75838ULL, 
            0x7833C857D948D2D9ULL, 0xCB44436D441510EAULL, 0x37983D4FA0833954ULL, 0x278E66D4C78F1D94ULL, 
            0xB1B7B18370DFF093ULL, 0x29DD70284644C9D1ULL, 0xDFA7A7D381DEAA97ULL, 0xC8F47F96FCD75B64ULL, 
            0xDA42A9841A515753ULL, 0xCA071AA80A8CB121ULL, 0xCC2DF947E5DF339BULL, 0x5B5281E918A81232ULL, 
            0x672F5D0E721AADC6ULL, 0x948F2A015183A03AULL, 0x5BA566D8E500CD56ULL, 0xA6A08E220E137325ULL, 
            0x1C190691CCC5BAC6ULL, 0xF14B9926C6901E22ULL, 0xDAE6B79826D95F87ULL, 0x21CEDA60D744C6D1ULL, 
            0xD9A75FD430D02253ULL, 0xC9BEC718DE84E34FULL, 0xB1A8980CB6D7D71EULL, 0xAEF565EB26FDCE02ULL
        }
    },
    {
        {
            0xA46EB4982DEB1997ULL, 0xDF2B34FB6CE7E0F2ULL, 0x53E9C087FED3D6DCULL, 0xF52201133731D985ULL, 
            0xC176B71DA1729BB5ULL, 0xC86EA2E7AF938449ULL, 0x105E758394E35303ULL, 0xE8975A3476CEE3B5ULL, 
            0x3D30D4EE1E1A241BULL, 0xF56E2B8911D15A36ULL, 0x10B5CD210843AB3BULL, 0x9726A494E7494306ULL, 
            0x40DD59A3CF65D6BAULL, 0x9B59B8E0B01EAC4CULL, 0x7E96E61A4B96D52DULL, 0x07738749486256CDULL, 
            0x4651AFA4000723F7ULL, 0x47BFA3813EC1DE62ULL, 0xE4588A559C97B5C0ULL, 0xA5492B39627BFBF6ULL, 
            0xCAFE7D07040079D8ULL, 0x0B3404B53BD574B0ULL, 0xA098390F724F43B7ULL, 0x9269F47B7FB92240ULL, 
            0xCC4CB2F035949306ULL, 0x88F66CFD6534A15DULL, 0xFA8CF4983C77CF14ULL, 0xCF03458CF3847E79ULL, 
            0x448F2FA90C9E5621ULL, 0x47894F0F57D96E29ULL, 0x44955DB91D57DBBCULL, 0x216CAB804ED5FDF8ULL
        },
        {
            0x6DF0ED2C4485E593ULL, 0x9D84565D31978E45ULL, 0x56AE39CBE66E3265ULL, 0xA57F73C4F5FFBFEBULL, 
            0x9F31DBBE29801BB8ULL, 0x351F18D9C907FC26ULL, 0x55F3ED370D6A2A49ULL, 0xCFEFE00A0F45DD85ULL, 
            0x53920B4D3D45A390ULL, 0xE57FE363ED7D5ED1ULL, 0x46FF43274FFF5F5AULL, 0xD1A09B2190831B4DULL, 
            0xE6DF05989C135FBDULL, 0x0B3220714AEBC650ULL, 0x7E39D2B344AF01D5ULL, 0xEA93B25D0802921FULL, 
            0xEBC13C1F7C49FA23ULL, 0x6EF95EB02CE6412EULL, 0x6129B553FC04CF8DULL, 0x77DAF864E8A06288ULL, 
            0xA8ED20D7074DD10EULL, 0x33A628C158814DC5ULL, 0xA4C3F1C1978C65C0ULL, 0xC06BD568701486DEULL, 
            0x2824180072964E78ULL, 0xFAF6712AC1E98385ULL, 0xCFB27772AE7121A9ULL, 0x8A0BEA9595912C57ULL, 
            0x464FA650229928BEULL, 0x6500154F5E1C1299ULL, 0x33B55915D967B5C9ULL, 0x4314C037365971B7ULL
        },
        {
            0x90D4005A22083312ULL, 0xEF19928E9A7535BBULL, 0x2E21C474F56960C1ULL, 0x365180E914B079C6ULL, 
            0xF6EEA257D14F2955ULL, 0x644CD3786D927AA3ULL, 0xF41C70D6EBB69AB5ULL, 0x87082F13878E1D5DULL, 
            0x2DAE32A8265A569AULL, 0xEAF8AC03AA14C4AAULL, 0xE4387019759B34BDULL, 0xB0EECCA518E8BE8AULL, 
            0xFDC36BCB2F5BE2AAULL, 0x1A250829B7D8B804ULL, 0xED2BE88C3AA2886EULL, 0xE43E84F06328AB96ULL, 
            0xED174997CAE51C34ULL, 0xD70A1C3E32C404F6ULL, 0x4592B76BEB7A3ACFULL, 0x6B6D72E87DB7011EULL, 
            0xD489BF561A0B42C2ULL, 0xCECB9AA066D269FEULL, 0xBC799C56C2A668C8ULL, 0x8752A65687D0CF1BULL, 
            0x43AC058029173F62ULL, 0x5B16A17491E7A74CULL, 0x1AF8F54BAD817314ULL, 0x089CE249EBAC1678ULL, 
            0x2AAF7AFDCC2FD2D2ULL, 0xF6F3DCC9C21D7C02ULL, 0x266AF896154517BAULL, 0x34C730B44AC1DD02ULL
        },
        {
            0x00F91E24EEC59A42ULL, 0x3E260E8164B74BDCULL, 0xE64759F5A72A1250ULL, 0x76790EB6FBE966E8ULL, 
            0x7BF6A8DFA116DBB2ULL, 0xE22F1A033978378BULL, 0xF96035416CF45C88ULL, 0x0F62737DC1E9BF18ULL, 
            0x36152F812C6DB864ULL, 0x8A1C377276D225BAULL, 0x5B9AFFD2590E240DULL, 0x8150BFB174C5A3B5ULL, 
            0xF80B07F11BC8E218ULL, 0xB081DA9CD2782EB1ULL, 0xB4D588A6468748A7ULL, 0xA65F28EF1A62CA93ULL, 
            0x06703D12F05918C0ULL, 0x782D35FA3A84988EULL, 0x6686441FF5F215FCULL, 0x5D9889274947E12DULL, 
            0x910E2444DB1F5E07ULL, 0x6C7366CAC19D89A8ULL, 0xB9D1C22FE45B825CULL, 0x13D80224EE5501CFULL, 
            0xF6366E8361D2F7B8ULL, 0x683A6F46ED0F471CULL, 0xC45293AE12B1B8ABULL, 0x925E09F648A66707ULL, 
            0xE72009517FF10D21ULL, 0x3D9517507270453AULL, 0x079536DEADD13EF8ULL, 0x212A6253BE8867C6ULL
        },
        {
            0x23482834FED61046ULL, 0x417703ACDA2064C9ULL, 0xADCF47D0755CD886ULL, 0xFDFFEF724AFB37A2ULL, 
            0x736DD30F0A1529D6ULL, 0x076BBD57C36984B9ULL, 0xA09F09CA19764FFAULL, 0x1BAEAFF45FC19E27ULL, 
            0xC94DBA3F8A882BD8ULL, 0xEE6F64CA63AEBE7BULL, 0xB6A3D95ACEB679BAULL, 0x0291052B652749B9ULL, 
            0x010B0D1B5ED67D5BULL, 0x897D5AA7EA43DEA9ULL, 0xF64E0EE93CE22ACFULL, 0xB6BDB6E751655793ULL, 
            0x0F6A30CDA201488FULL, 0xB81678262165F808ULL, 0xBA8F5D6FA41503ECULL, 0x5821089B6DC0BEF9ULL, 
            0x07BF38EEEB0D26E3ULL, 0x3CFA301E5C99E478ULL, 0xFE8612B63A046B54ULL, 0xE1FE3E388839BBFBULL, 
            0x0D88C460839E80D0ULL, 0x054047B284A4E33AULL, 0x804A12579110B41CULL, 0x4BC928E054A6F8AEULL, 
            0x4C96DEDA1A0B5D09ULL, 0x50C343FA85809C59ULL, 0x0E507F9B5526FAACULL, 0x2D86A65C3ADDB98CULL
        },
        {
            0xDDC84B3BF0F5CF34ULL, 0x20C63C69CF03D618ULL, 0xB0258193DBAAEE2DULL, 0x00FCE018780F3B57ULL, 
            0x5EA1F2FB58ABDC84ULL, 0x0B9ECBE7FA7B4295ULL, 0x445D1BA98D0FA859ULL, 0xC2774409A1F9DBAFULL, 
            0xAC2CDA9AFB42206BULL, 0x364424C2C3A44C7AULL, 0x6D07097DD70AB603ULL, 0x5532CCBB88088838ULL, 
            0x29090D30C93609B2ULL, 0x08DACA9B18484EACULL, 0x1B03379CC9176A25ULL, 0xB7C92530733DB705ULL, 
            0x3776F9BC23EBA53EULL, 0xAB5F194E0B0A0BA6ULL, 0x84D1C7B54620F8EBULL, 0x4CE5A68D7A91B3BFULL, 
            0x4FF866EC9E04BF7BULL, 0xB724968BA91B18CFULL, 0xED56FDF04D118103ULL, 0x38C1F624DE25C8A8ULL, 
            0xA231E15F29F107DEULL, 0xA7284940218FD1DBULL, 0xBA9703E7979DC9FFULL, 0x9B4442C46CCDC3A9ULL, 
            0xFCE34AA45B045885ULL, 0x84460316783A7BD2ULL, 0x0A16E79B1E7DF80EULL, 0x89EFD7FF707143EFULL
        }
    },
    {
        {
            0x88A882FB02385188ULL, 0x1B829C4B9C03D2C1ULL, 0x6E2DEFEE8F37FE50ULL, 0x4E80110D90E0211EULL, 
            0x6474851808C08453ULL, 0xB73521C6D24C46ABULL, 0x527B79AEF7B561B2ULL, 0xB9835A21DF1C973DULL, 
            0xB62292A0FB6F7511ULL, 0x18767C7F4767F0D6ULL, 0x71349B9EB92969F5ULL, 0xCB7D9C3A1CFD0DB0ULL, 
            0x62F7D6C0AB1E876CULL, 0xD3AF47ECE8CE7C23ULL, 0x055F2DEE7F8B3C2CULL, 0x63228B402513188AULL, 
            0x4F17A7A18A991FD7ULL, 0xE021E60A0067BB65ULL, 0xCDB9EC8886F762C8ULL, 0x7D9F8E220568EB2EULL, 
            0x57EE7D514AFBBFADULL, 0x3BAAEF8FB539F537ULL, 0xFD0A583D1480F464ULL, 0xE7C8AEAE2214A605ULL, 
            0x687570E9D7440F9AULL, 0xE534A29C88D85599ULL, 0x131D4A33BBD3246CULL, 0x4B5C544301B53DF8ULL, 
            0xE42ED90A0208818DULL, 0x1FCC6EE12B222846ULL, 0xA2ED066CB8F020A3ULL, 0x62CD278B80FC3339ULL
        },
        {
            0xBDD4E73003D4CF3EULL, 0x0DBD087B637E71BAULL, 0xB6D9A57AD6100061ULL, 0x8A36029FDD608E21ULL, 
            0x5147B52EC0FC77F0ULL, 0xDA0F91FB75EB432DULL, 0x1CA31D1ED76F4DE8ULL, 0x43AC23EF8F2A3743ULL, 
            0xABA62FCED5DE42E3ULL, 0xE6818B1B91A7F5E6ULL, 0x2BED9D6B719285A8ULL, 0x820DA3DF666D905BULL, 
            0xCAF43B0F1DE2EA6DULL, 0x9993FC2B40D55564ULL, 0x75DF34A0CCDA3194ULL, 0x7EF76717661B22DFULL, 
            0xE9C909A47B95D049ULL, 0x6D4EC5855A48E386ULL, 0xF99168A6B6F4F7D4ULL, 0xB5D4699FFFED9C76ULL, 
            0x3F88BE531D2F92F1ULL, 0x213F958D728678A1ULL, 0xF7FEE829D70E111EULL, 0x04A6205BEF176E0CULL, 
            0x7C0897BB7D2CF0B7ULL, 0x7EC20C5B25956833ULL, 0xF4ABCB63EE8700CFULL, 0x0A641A6A1602615FULL, 
            0x0C6EFEB57B17A966ULL, 0x5C2F766005947244ULL, 0x54D394DD0FF2453CULL, 0xB4F7A9CF243FB30FULL
        },
        {
            0x4BFBFCCAFA915ACDULL, 0xCCEFB7E73DE3C535ULL, 0x577BEF2FA7E275EDULL, 0xB8388C17F99FA309ULL, 
            0xBDFCC746F20724D7ULL, 0x5DD8039B28C65E82ULL, 0x8094A2A107F89BA3ULL, 0x4307B63657DE366BULL, 
            0xF70E29789A92EB15ULL, 0xAA3F554E66822020ULL, 0x76BAE483E8F2BBDBULL, 0xC24B9E199EEE88F3ULL, 
            0xA27617A839C5DD15ULL, 0xB0AD91211D06E664ULL, 0x499DE2727644BF41ULL, 0x7175E61266BC2BB3ULL, 
            0xE438BC7B80C204F0ULL, 0x4E95DD6255987B73ULL, 0xC5178D9EB941DC16ULL, 0x2943EEABBE3ED990ULL, 
            0x3E5E4B2E5FF0D852ULL, 0x6EB9F0A55981622BULL, 0x287E75AC515D2A5AULL, 0xDCB0B403BC8F9E2EULL, 
            0x7D2698D89F92D8E5ULL, 0x90FD0745EF171FE3ULL, 0x7E796CC1DD1ABC70ULL, 0x05FF1A638D36F1D6ULL, 
            0x50BFDFFA27F476ADULL, 0x6D095923581B0670ULL, 0x57206CAB0149AB8CULL, 0xD7050FD71CA44578ULL
        },
        {
            0x3FD3A8195FF38649ULL, 0x88305065C87145A2ULL, 0x6D0A722604BBDCA5ULL, 0x034AA80C6BBFFC9FULL, 
            0x0E17EEC83B93EE5BULL, 0xB57E282237C37CBDULL, 0x2227CCF15896C4CEULL, 0xFFD3B345B6AD9DE7ULL, 
            0x4BCE566B2B18DA2FULL, 0x136690E95BCF2B88ULL, 0x1435400BC7AA2AFBULL, 0x702522E0AC189524ULL, 
            0x5BE1C06F216F6516ULL, 0xD51C659FBDA81B0AULL, 0xDC666D101E353FD7ULL, 0xDE23C5A78AE18C95ULL, 
            0xBC96529F5113B553ULL, 0x0E8C7B203EB2D6B6ULL, 0xBC23789C22EAF88EULL, 0x427A3C3130CCE2F3ULL, 
            0x80C00D9B60C65539ULL, 0x78F1F1C93DEA428BULL, 0x22276DA1EC2578F1ULL, 0x16257409CF4D2665ULL, 
            0x1162138B476CCBD5ULL, 0x4D756907EE5DAAD7ULL, 0x81099C373F84C65AULL, 0x1FC3F9D4FAF492ACULL, 
            0x6626FCA388CB70C0ULL, 0xA9B296FFC892438DULL, 0x0F6E070DA84E031DULL, 0x4B9CF61E31E632C1ULL
        },
        {
            0xEEB2D6F524AA83AAULL, 0x2C552C709F2B2E55ULL, 0xAFCBAB31EF29062FULL, 0x7E66AF4C7EE5AA19ULL, 
            0x19100F310E5E2F12ULL, 0x0145866EDD7092C7ULL, 0xD0DE4F1011C13CD9ULL, 0xBF707DED90A856FAULL, 
            0x2D65565AB237CF80ULL, 0x095AD6393704AE9AULL, 0x78FF3237B8E4CF4EULL, 0x131FDE1DD779F3CBULL, 
            0xB53BDDF27EB71993ULL, 0x12CC438001E3CBFAULL, 0xE07D922F62B2C37EULL, 0x3A11EE633668F69BULL, 
            0x624782A0E3BA9F26ULL, 0x990D184683BF4759ULL, 0xE30BC68DBF4628DEULL, 0xC3C4F4D3861BF7D8ULL, 
            0x3C3A2C528B767842ULL, 0x9073BE43E9DEC407ULL, 0xB27F680941090CA7ULL, 0x71440C1C5B38BD87ULL, 
            0x822B93FAF5914D5EULL, 0x6A872C13A330C112ULL, 0xF5C7D25F221F903DULL, 0x6981F12B61964959ULL, 
            0x52185481F5B7C9E8ULL, 0xE42AE2420EE48384ULL, 0x664346C9BC9E77EFULL, 0x4406115FE8356942ULL
        },
        {
            0x138159524B7DDAC8ULL, 0xE153D028038DE579ULL, 0x2D6A5A41885883F2ULL, 0x8614E2E55EAA4E7CULL, 
            0xDB94F22D0B6B5178ULL, 0x27FD5B15CE047E02ULL, 0x8C662A49D490B68DULL, 0x6F006FEE104B2D9EULL, 
            0xF341AE2B38791358ULL, 0xB5C49ADA9823A1BAULL, 0x57083ACD6C0689CEULL, 0xE7BABD728912429DULL, 
            0x82A36C982444D19DULL, 0xA5324380FE37A9ECULL, 0x36A930029C4460D5ULL, 0xD396699F5D8585FCULL, 
            0xC15DC22956EC66E1ULL, 0xE6A47FF6718E5C4DULL, 0x713B1616161E6D11ULL, 0xDDCDAF947FDAFF98ULL, 
            0x77A5DE21D7B4E85EULL, 0xFDC6C9E3999F14BDULL, 0x5AD6CF31256D61EBULL, 0x2B01FB202A0180E2ULL, 
            0x47E7FA9961B90E1CULL, 0x57B077783C465594ULL, 0x97B80A58E092692CULL, 0xACA5BDEF7B2465CCULL, 
            0x39DC457D9875878EULL, 0xBDC62598FEAAE16FULL, 0xEF5E6D3B6891778DULL, 0xFF0B9410FCED2C5CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseAConstants = {
    0x29EC666DB80E7357ULL,
    0xB029E1C86173DDC2ULL,
    0x9CF77E7C6D7FC421ULL,
    0x29EC666DB80E7357ULL,
    0xB029E1C86173DDC2ULL,
    0x9CF77E7C6D7FC421ULL,
    0x89D66B2ACED0CC9EULL,
    0x9A50276D4503F5BAULL,
    0x04,
    0xAB,
    0x90,
    0x74,
    0xA2,
    0xD2,
    0x8F,
    0xF3
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseBSalts = {
    {
        {
            0x807EAEA2FE44624DULL, 0xC8655D9C41417DD6ULL, 0x94744A439D2F0463ULL, 0x48E11A4D792C314DULL, 
            0xA1904844C71E834BULL, 0xD49E5AA27B61632DULL, 0xC22F4E39A36CFE26ULL, 0xF79CAA399F6568CCULL, 
            0x2D099DE80ACCD0F2ULL, 0x38ECE6C3EE5EF8ACULL, 0x9CB4AB68A8B9D5D1ULL, 0xE77B85A2CD2EC94AULL, 
            0xDD62AF32CCC34F7FULL, 0xD8FC13F55BEB6611ULL, 0x7F0D701752BC7AFBULL, 0xAE37A532DA21BF98ULL, 
            0x9CBBEFCF3F832595ULL, 0xC702E595BBD35C8BULL, 0x903F81B7195E9E85ULL, 0xD22F182C1FF4FC76ULL, 
            0x686D07B0BECF5A85ULL, 0x8D7443157C662E71ULL, 0xA7A84BE832786E37ULL, 0xC967BB2F9157DCDDULL, 
            0xB16ED06A81D6304AULL, 0xB376B41C83BEA47DULL, 0x4250AEE147E3C016ULL, 0x30164A2F24B80E00ULL, 
            0xC59B5168CE765C5CULL, 0xD4DD2FD57C9133F4ULL, 0x09B5A14B99F41060ULL, 0xF48FA140D11965D5ULL
        },
        {
            0x12756B175D92FD1DULL, 0xF8380421B86CE01AULL, 0x25CD92D83E7D9AD0ULL, 0x688295797794D1A6ULL, 
            0x38647FE402BA48FFULL, 0xCB9444A5A39C8C1DULL, 0x016A4E374C090365ULL, 0x3919B9E0A6B33FDFULL, 
            0xFAC5EA9607875CE7ULL, 0x4C8BF9AB1235B9D3ULL, 0x2C5AB3E198416FD7ULL, 0x7BD558134F508DFFULL, 
            0xFE0EC98D30CA6C2FULL, 0xAA7B9EF9B79F0728ULL, 0x24918A55D98CC652ULL, 0xC71856A1B509E7CCULL, 
            0x616504E81C417B3CULL, 0x683C74F9264A64FAULL, 0x48E85AD338BA2F71ULL, 0xAD7E0505C52FD997ULL, 
            0x4765FCF3D0D0EB4AULL, 0xDB8AEAC7FA2311E0ULL, 0x5225DC480D31C382ULL, 0x48EEB8CEAC80C09AULL, 
            0xD3ABE8B23EC30560ULL, 0x6AE70908E4CBF01EULL, 0xDF5DF3CE672DD68AULL, 0x50B004F673279F62ULL, 
            0xBEEDF9FD4C64C18DULL, 0x4C050BC7EB5E882FULL, 0x2B06AEFB774CDA2EULL, 0x2D942FAB5CF33DF2ULL
        },
        {
            0x0F41B5528804201FULL, 0xD624518373990958ULL, 0xF322E7D1F215684CULL, 0x971C0315DB445093ULL, 
            0xF901D8247433E77AULL, 0x545C9B1E9402DA55ULL, 0xBBC28EA056345020ULL, 0xC00B3F650D2BE41CULL, 
            0x44F51146752F608AULL, 0x886B9BAAC95A68EAULL, 0x5A6F8C44308D3B43ULL, 0xDF09E82A81941B11ULL, 
            0x719CAC40E7943B65ULL, 0xD7FC33CCC8439C41ULL, 0xE352B34E0BA9D104ULL, 0xDEE3EDBE2F6FCEF1ULL, 
            0x8CF7514FCC4E566CULL, 0x0F15217987D59D90ULL, 0xE7AACFA4F0584B77ULL, 0x4439347E7F2AF950ULL, 
            0x8FBD84D44A88FFB7ULL, 0x40D2E10B39F08DABULL, 0x93DED5DA665CF2A7ULL, 0x3C6886B33E50AAC8ULL, 
            0xE691E0E93AB30957ULL, 0x7B131068403FAFA3ULL, 0x322E66420B54AF8CULL, 0x5D398DE878839F17ULL, 
            0x0D378AC0635DFA5EULL, 0x92B55338F7D7F63AULL, 0xA69D29F79FF146F8ULL, 0xF3404DA0EF656C39ULL
        },
        {
            0xD00A2F5F0980A3E9ULL, 0xC779FC033D867E56ULL, 0x3CE194C2C42178CDULL, 0xA61A46E2792EAA7DULL, 
            0x852D061DA4443DFDULL, 0x3F9A57C1B7AD2AC4ULL, 0xE041FB24A212FE47ULL, 0xCCEBBB6B3771C7DFULL, 
            0x2EE78A432520B5EAULL, 0x1E1B57A11F0B4909ULL, 0xD490CD130BE3C261ULL, 0x655051FBE9DA0874ULL, 
            0x6B299FB56F97C9F0ULL, 0x037050DDA34936ECULL, 0x118FF96C0384E8FAULL, 0x519EC9D43E9D555FULL, 
            0x4CA9366BB820256CULL, 0xD9586794A1EC8F96ULL, 0x0C950A42463DB554ULL, 0x65F98075B29EF7ACULL, 
            0x95755B282F03895BULL, 0x5E19857EE2A270BAULL, 0x66E3661BEF23157CULL, 0x93EAC1413656C784ULL, 
            0xC9774504362B9B03ULL, 0x833C282DF0C7C37FULL, 0xB9B1D5F3C2A17C00ULL, 0x335C915A4495313FULL, 
            0x7AB8B0C861930D39ULL, 0xF7176FE6A0E0D8A2ULL, 0xAA2716327E9981F8ULL, 0x3EFD25E5CEE51161ULL
        },
        {
            0x5E3630B8B1DA0C28ULL, 0xB4C9973C43A8A581ULL, 0x4B18B9BC3C8BF2D3ULL, 0xB6B60216DFE09FBBULL, 
            0xAD7AE4D3310C1442ULL, 0x971F4420E408FF20ULL, 0x6EB2DC98EE90F978ULL, 0xD7EEBD434E957E75ULL, 
            0xCB2E6FCB9C2FC00EULL, 0x1B1F406032BD137EULL, 0x2FFA0261D67C5C4FULL, 0x940C5F79262001D2ULL, 
            0x6FA530334EE14A9BULL, 0x81D50E6B2BDD6FA2ULL, 0x13842B6FA55A8927ULL, 0xB023990AE10E3FB9ULL, 
            0xD1ACD77D237BC3FEULL, 0xF2304DE36398099AULL, 0xD14044E4520E9ADCULL, 0x906F1384C0A68F86ULL, 
            0xE79FE2C1AA97AA42ULL, 0xEB09FBF33A263E6AULL, 0x9E56A587EDDB35A1ULL, 0x2C6DFA91B6C17295ULL, 
            0xC81A769D27F374CCULL, 0x3376AB7390B24C95ULL, 0xAE852865024330EBULL, 0xA392DA21C49ABB5FULL, 
            0x86F67E1CE7A915FFULL, 0xDF0ADFECF77B5623ULL, 0xCB00C23E7AA62F29ULL, 0xB8F04DA5500D5B02ULL
        },
        {
            0x684319F21D3A744CULL, 0x980631340797AE35ULL, 0x0E9AEC8867EA9B15ULL, 0xECA1E425F0A7AC84ULL, 
            0xCB39ED95D97CC90AULL, 0xA301A87ECE5A8DBCULL, 0xE2E7ADDECBF38790ULL, 0x07F03405AA6A0BFEULL, 
            0x9E0FBAF90AF2C0B8ULL, 0xECF278DB1DE81B24ULL, 0x8EE69A305BE27D11ULL, 0x6D239FA2258BBF97ULL, 
            0x7DF192AE0D254187ULL, 0x8CFFE3F3402961E0ULL, 0x6AE6A57E6AD40039ULL, 0x80ECABF6F3DEE983ULL, 
            0x6137D69565B567D1ULL, 0xBC2770C1F9A6F666ULL, 0x1A290E4F1F4602B6ULL, 0x3903A9B4D4B94EFDULL, 
            0x159D1C7530C60169ULL, 0x7C678B44F7AD1585ULL, 0x599DB3D7AA50A45AULL, 0xB5D10339F8A4E7DEULL, 
            0x4DAA71D5561D4AF3ULL, 0x5B5B32C24930FF9CULL, 0x2631E87D3BD91624ULL, 0x4313D87FA4060A92ULL, 
            0x3C647259E6999103ULL, 0x7E64464E5A70733FULL, 0x2F59865072CB3A9BULL, 0xD69EFA047F5074AFULL
        }
    },
    {
        {
            0x70BCFD7D17DE16D1ULL, 0x15154AADDE727B85ULL, 0xE0FC7C46266C8C7AULL, 0x8D84CA8C75D92DECULL, 
            0x371FF29D52A0D456ULL, 0x61CC4C82B21DDCAEULL, 0xD3D48BFEEE5F074BULL, 0xB5B6703FD9E6B3B8ULL, 
            0x948475EDF67335E1ULL, 0x4A87241B8B4AEF10ULL, 0x90B5FFCA91815EA3ULL, 0x96E97030612D55BFULL, 
            0x9C94F66C8B26B44FULL, 0x208DE4C6CF671D69ULL, 0xA6FD7B4FC3195B5AULL, 0x17E3B26C28E3106AULL, 
            0x46B2B2E62ACCC977ULL, 0xC2B3AEFF9A06BE9EULL, 0x44FFD007A0C7984DULL, 0x6A081D9C45A5E01CULL, 
            0x780FDA2D67405C32ULL, 0x5E7FDD159142D0CEULL, 0x7C062D02BE09F651ULL, 0x4E3CE52CE941498DULL, 
            0x302B5513E8C15593ULL, 0x78FDAA026A3DC323ULL, 0xE67BC5F5ABD1B6CDULL, 0x2C7024CC5204CEAFULL, 
            0x2F97B0C38E373802ULL, 0xD86DEE87CF050E3AULL, 0x7D209B913780006EULL, 0x5890AF0EEBD70A1FULL
        },
        {
            0x33C926FE55D4F024ULL, 0x88AEA0BA36D8BC8FULL, 0x2DCD61298667B02FULL, 0xD3E708F15F71F305ULL, 
            0xA8BF781376E30B00ULL, 0x32D2655860408DDCULL, 0x0DE6D361B7557735ULL, 0x959CA1AEF434FC92ULL, 
            0xAEE3F3D875B3B0E9ULL, 0xC0BE6AE4348454E7ULL, 0x7DD247915CD6F2E6ULL, 0x8BCE091213DFBE27ULL, 
            0x4394512C0C8780A6ULL, 0x08AF369D61328F89ULL, 0x5CC559A5141FF136ULL, 0x27B01498AE82C80EULL, 
            0xA72FAA6D95B6BC67ULL, 0x6EC2E871FD4E3F10ULL, 0xF224EF4311346F32ULL, 0x471F602186CD7719ULL, 
            0x9EFB43BA11A8F49EULL, 0x10C869DFD79148CAULL, 0x2DBE2FB5E4CC7026ULL, 0xAEA1A3CF8F279A55ULL, 
            0x78962A9746AF142EULL, 0xDEEE86810939F319ULL, 0xF2532D774D0D4BBEULL, 0xE20B51EC1FF6F8F1ULL, 
            0xD53D971F2370FAADULL, 0x2E1A6B8EA61070DBULL, 0xE4D23273F4D16415ULL, 0xDAA70D141B71AEA1ULL
        },
        {
            0x42B71BD8FD97F271ULL, 0x3CA3C85CB6A460CAULL, 0xECFCD0B7C005EAC5ULL, 0x33217425A7768525ULL, 
            0x25D141E71379B5C6ULL, 0x0F59BBAB7BF73A42ULL, 0x5F012A29B51ED0D7ULL, 0xAA8916A9DF12B033ULL, 
            0x406FDA4C7759FCE5ULL, 0xE9056865A8CC9123ULL, 0xBDF3CACA296382B6ULL, 0x63D1316DC581C3C7ULL, 
            0x4EA17D04691CF538ULL, 0x0FA80C4A3893783EULL, 0xEC1595C801EF91F2ULL, 0x981281AAC88EB31DULL, 
            0x73565E021C54984BULL, 0x66C275B9D28BA4A5ULL, 0x37DD74B4AD4A0696ULL, 0x74DBF77526361FC2ULL, 
            0x2D3C8341248CE018ULL, 0x1EC1166D5216F7E6ULL, 0x2F3107467ABB4C5AULL, 0xC5E4A44A4FE610F8ULL, 
            0xD7EE7FB3A8564185ULL, 0xC4E172DF688854D3ULL, 0xE22E74264CC0CF3EULL, 0x6FB71CFBDCDE0E9BULL, 
            0xFFFA6E29ED382163ULL, 0xF776EDF9BC57D6F1ULL, 0x1956FA646A47B9ABULL, 0x0970D013BED43BD8ULL
        },
        {
            0xDAE9A21F21FAD2C2ULL, 0xE8B26FCB4ED83044ULL, 0x95489725D0D7EF63ULL, 0x99678127EA6A8C30ULL, 
            0xB939D55D67CFE733ULL, 0x46F94F607040B5AFULL, 0xF894549132490888ULL, 0x960E0E8C13902A23ULL, 
            0x29B22BBB7AF3A23BULL, 0xBFF76B9664C7AF10ULL, 0x55FC449EEAD4DCD6ULL, 0x737A3B421672CBA3ULL, 
            0x2F1CA37B3305AC75ULL, 0xF78A2B990DDC1428ULL, 0x86AFA5444DA50B47ULL, 0xAB8A5E197DAFB7F6ULL, 
            0xD44F1FF22DE790E4ULL, 0x9758773EDE0A3ACDULL, 0x96BB42EDBF1A04CDULL, 0x669033B0F92E6055ULL, 
            0xEEEC9CA2CCA57FD5ULL, 0x0CAEC3433B312897ULL, 0xA295A66AF5E42CC9ULL, 0x86B35F5472864AA5ULL, 
            0x512A03A95B94598BULL, 0x694719D852BB9631ULL, 0xCD079FC55CE3D50CULL, 0x1D84D089B01E4B0DULL, 
            0x5EDC0B774EFB5BAAULL, 0x6884484F81C1D37CULL, 0x2EC63ABEFC7BECD8ULL, 0x85E4507C067E3307ULL
        },
        {
            0x1551DA309FDF2EF3ULL, 0x694617B650840A3DULL, 0x7ADFD9C2A4DAF8BBULL, 0x83DA3EB11C07CC2CULL, 
            0xF68D94D78B73FB31ULL, 0x1BC85A78F1453A75ULL, 0xCEB0F83BA24F6398ULL, 0x0FBC1125103C63B4ULL, 
            0x570F8DEC13F49536ULL, 0x62C9C13BAF5A202DULL, 0x4E79B31D91C9FE96ULL, 0x15CB6F75FFD1AE68ULL, 
            0xF699BADB2B2CAC4AULL, 0x68F44364516B11B3ULL, 0x6E94255D2382E6EFULL, 0x1BA9C6183C41EE2DULL, 
            0x391B54863D67A5F8ULL, 0x719184D4F096DC72ULL, 0x3A1C14DEF195B34CULL, 0x8C3C553E7333276EULL, 
            0x84F72A267CD26C77ULL, 0x4C8A41C67DB29E39ULL, 0x3D6CE58DD5D409EDULL, 0x05FBD4DB111A092CULL, 
            0x3F554B5C07335D54ULL, 0x0067E26DB70AFF2CULL, 0xC82A2572FF18F8DCULL, 0xC4571E77753C07AEULL, 
            0x8C8B793852320297ULL, 0xC0D958C3DCA07C30ULL, 0xAA412B0C186B37CBULL, 0x4FB587EB0F17C092ULL
        },
        {
            0x2AF933C0B5603A01ULL, 0x6927067BEC4959F7ULL, 0x818BD3C6A908711EULL, 0x6A5C3DAFF5138F53ULL, 
            0xF0F608C930DF3445ULL, 0xADDFC610FD282B63ULL, 0x30BCE437AF66C022ULL, 0x70EEE5E0E55FE398ULL, 
            0xC1E05C9A7F88C89CULL, 0xB03CE036C45378E5ULL, 0x949B490B3CEC938DULL, 0x0DFF5B563C252D43ULL, 
            0x699C6F14370941FEULL, 0xBD47A74B4A92D1A2ULL, 0x28DA50AA89825919ULL, 0x6CE29500819A5500ULL, 
            0x2A8C5799FD714052ULL, 0x707F7EA24DC3389FULL, 0x792B266487032EB7ULL, 0x26EF06C606F45F0CULL, 
            0x703EE237D7082C68ULL, 0x220D2F149F6A9673ULL, 0x147F15C8AB64D194ULL, 0x275886506FC490BAULL, 
            0xC5CEDAC47D05199CULL, 0xE9E96FA2958D1FD3ULL, 0xBD7631C25FB4415DULL, 0xFF9470122F1605B8ULL, 
            0x94387126A95685A4ULL, 0x1125CE91C9E31444ULL, 0xD0F140AE69E9B884ULL, 0xC628D1714969A9D0ULL
        }
    },
    {
        {
            0xE4B700E24234DAEBULL, 0xCAD565B47DE7FB3BULL, 0xEC71CF82CE74DA58ULL, 0xEB53AF9BD4572629ULL, 
            0x2F4CA3E938F22BF4ULL, 0x80A2A7136DFBE172ULL, 0x661DA7E5F04BC933ULL, 0x646DCB5376DED12EULL, 
            0xA4E0DCC7586BC6AAULL, 0x516F4241BAF77B5EULL, 0x12D81F22CD69E883ULL, 0x878024F4C1986632ULL, 
            0x59CD09DB08242BD1ULL, 0xB52E2C2BA716725CULL, 0x880253347D02BBA0ULL, 0xF40429DA1F640F5DULL, 
            0xFB57FA8C11E0D5C6ULL, 0x0EDFF07551B1927AULL, 0xE6948223B310E18FULL, 0x715954A41EE8EBBEULL, 
            0x1E9D02AD247799F4ULL, 0x10BB7221CE0A5F84ULL, 0x8A00B1795251887BULL, 0x320337F2BCC01AA7ULL, 
            0xB474278D5A67E385ULL, 0x5D3643791DDB0F8EULL, 0xD08DF7E05C4D144FULL, 0xF533B2337A5D71E0ULL, 
            0x9A20546D76E16AF1ULL, 0x5E42CD8A860B97A1ULL, 0x9EC88E4530C781F7ULL, 0x1D2E14162E479F28ULL
        },
        {
            0xEF86091D508AD14DULL, 0xC3D36219B7F9952CULL, 0x2F38824BBA0C7C9AULL, 0xBA143D921024F0C3ULL, 
            0x559769D0B75C9FABULL, 0xC8740EBCDA5A15E3ULL, 0x25CD05FB5B2E8F8AULL, 0xB79D200F46D0120BULL, 
            0xDB27B68BFA13DAE8ULL, 0xF86CAA186F8A8B3CULL, 0xCF5828BA56BDA156ULL, 0x747EC391E03A5B6BULL, 
            0x601483A1F14BD1ECULL, 0x570DC5904463AF76ULL, 0xA374F9860CFE25FEULL, 0x93DEBB926F83E730ULL, 
            0xC46DC02B6CBD1CA4ULL, 0x4AF38FCA5C03A7BEULL, 0x286252561415903FULL, 0x2F7632ECC7590DEFULL, 
            0xFBA4F28060C812D8ULL, 0xEB98FCEAFFBB9A67ULL, 0xD340431C56E06C84ULL, 0xB76B15C06FC23E91ULL, 
            0xB776D8AAD0BCF794ULL, 0xDDCEDCED20B8095FULL, 0x7182C734035230F1ULL, 0x7BAC6C5AE8C6D3D8ULL, 
            0x2E11F87ACA61EF5EULL, 0xA1E59B62D4F9E333ULL, 0x9B4785264A8ABCD4ULL, 0x712560A9FC9B4DEDULL
        },
        {
            0x8CB29FF19B4F427AULL, 0x190ACBF63867A123ULL, 0x8113AAFDCE3A7BFDULL, 0xA0D56892A390B23FULL, 
            0x5384B5ED194AC123ULL, 0x13B2C72A3B884974ULL, 0xAEE3C640440F734EULL, 0xDB69ADB0659CD31AULL, 
            0x19FCC9A1B7E495B6ULL, 0xE1CD7D501EB5F0F0ULL, 0x2005B84C3D677904ULL, 0x1223EDD04A5EA0DEULL, 
            0xFCC0F8395160C1B9ULL, 0xEBE1B8342C2FD639ULL, 0x599C8172F681BAB0ULL, 0xBF01067C2A06F1B9ULL, 
            0xE1EE0AF6341F2573ULL, 0x845A20D9D52BE20BULL, 0x2206590EE3B0601EULL, 0xD5A050110429F19CULL, 
            0x344D1162A60252AEULL, 0xB44B16A6F3D28AE1ULL, 0xA61769A509AAC9FBULL, 0xF70249B6EF80BF54ULL, 
            0xB34D76081FEE39FDULL, 0x8A74A2DE4FF99C79ULL, 0x8AE7EFA6D673A4B8ULL, 0x00941D4456B29541ULL, 
            0xDB021BE77CE0C012ULL, 0x8F4B7498039529F0ULL, 0x99879FE0A9C0973CULL, 0x989977CC1FB3FBADULL
        },
        {
            0xE5ED7B93046A68CBULL, 0xD2CA113C90853B9FULL, 0xAAD67390F04A95F8ULL, 0xC3BF76308C7743C7ULL, 
            0x3A7F534BAD17789AULL, 0xC2C18454B93E5F67ULL, 0xD2F93DD9A1F6B6B9ULL, 0x9BA0E8EDE60A707FULL, 
            0x63456707A9174ED9ULL, 0x996CA5C04514CEE0ULL, 0xFE98F122BA3587A5ULL, 0x3A6F666F235A4E37ULL, 
            0x4F426800E7621432ULL, 0x394FB5E9A99648D3ULL, 0xB9A069AAF4BA28ACULL, 0x55FE46568DF3E393ULL, 
            0x8525C4C3E8060396ULL, 0xEE3EE8DA3323421FULL, 0x713C9AB4C8C7FAFEULL, 0x20EEEECFBF77D141ULL, 
            0x63FC48DCE1265DF2ULL, 0xFA4A99203338FFB3ULL, 0x3C71C3B0ECEE96D1ULL, 0xE3CACBD7CA081C18ULL, 
            0xFF678D7163946B7FULL, 0x5DAE37BBFCF058D2ULL, 0xEC839A620A125DCBULL, 0xD59EE7A955463235ULL, 
            0xDF9290DE81AED538ULL, 0xFD04515A3B0CFE17ULL, 0x3BF716330CBBC606ULL, 0x92D760A32E0A6A41ULL
        },
        {
            0x2A579BCF590F0050ULL, 0x15D71875F531518DULL, 0x4271D7D91A435A66ULL, 0x4812AD6A8A61D595ULL, 
            0x5B080DE05DF32C1DULL, 0x536B5B75685D1F7CULL, 0xFBF3DEBDF86243C1ULL, 0xDA06E500B0D42042ULL, 
            0x2F3BB13CF7E50793ULL, 0x6464C68C20ACFFC1ULL, 0x74F9EEDB7AA465A5ULL, 0x8B012FAC75017C93ULL, 
            0xA0FCCA47674B542BULL, 0xDB83A273CD627564ULL, 0xE3D9DD49ECBD8813ULL, 0x727BD8A5C5AAAF73ULL, 
            0x3AFD0AF7119C32FEULL, 0xB12DAD5A234E11E9ULL, 0x4BA2C79CF68C88F1ULL, 0xA2DFBA5A68F5CEE7ULL, 
            0x0C3093C5ACCF0B72ULL, 0x1B64548B9110E331ULL, 0x819AA045F488B253ULL, 0x26869AABF5F7A733ULL, 
            0xBB0419611F8AE32DULL, 0x34265A53346B7BE2ULL, 0x21D2CACA335E5EADULL, 0xF6D1AE189D1EDDAFULL, 
            0xE506E59465E9F0D7ULL, 0x4EDDAB2C67E6A094ULL, 0x6D392FAAD30F2749ULL, 0x303731A53AA5882DULL
        },
        {
            0x0ACE35574972E948ULL, 0xA99A50B0868F6F2BULL, 0xCD6F011C4B27F111ULL, 0xC28253C827381297ULL, 
            0x4CF8F57B30A7ABEFULL, 0x2486EBD437F16412ULL, 0x39A61D54B622940DULL, 0x3D0A8529549CFAEBULL, 
            0x7A98AE40957BDAEDULL, 0xAF1AC4A7B0C234B3ULL, 0x26974ECA4A161E5FULL, 0x4E84B3646040148AULL, 
            0x6958DD28B3D5823EULL, 0x713E7121A3B296A4ULL, 0x1E639D009E6AA313ULL, 0xD133B0A6F03DCEB0ULL, 
            0x57D38389A462A787ULL, 0x17E61F4B14F9B0D4ULL, 0x053FB6444C8A01F2ULL, 0xAAB6187101A1C6EDULL, 
            0xE48586188A28024EULL, 0x47801F477ACA8035ULL, 0x6E158414C92B8C68ULL, 0xA1981A20F51185ECULL, 
            0xDC6EF481837A7D83ULL, 0x3E510E9E209437B0ULL, 0x5962D3C46953F9CBULL, 0x4D3BDEE027BC5A94ULL, 
            0x7E55D177FC068DE9ULL, 0xCC73AC74135FBB82ULL, 0x68C0049F2C5DBAEFULL, 0xB3AC046A751FC391ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseBConstants = {
    0x672C91E442C34475ULL,
    0x576F1697F0BA18BFULL,
    0x9E62136E95729D45ULL,
    0x672C91E442C34475ULL,
    0x576F1697F0BA18BFULL,
    0x9E62136E95729D45ULL,
    0x80C20717A112EB1EULL,
    0xAEC3C17B48B65D5FULL,
    0x52,
    0x2D,
    0xC7,
    0xA7,
    0x4B,
    0x62,
    0x5B,
    0x26
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseCSalts = {
    {
        {
            0x0722C179CBFB414DULL, 0xB3DE9373D22B780AULL, 0x8B4C9411D2ECAD91ULL, 0x7777A47F069783A9ULL, 
            0xFAEA6582ED1BFA8BULL, 0x20E77CD666094106ULL, 0x5A887A3335EFDDCDULL, 0xD7C12A869C14B332ULL, 
            0x09A5366F34507B00ULL, 0x583A7F871F800A93ULL, 0xAF063CA46E9F32ECULL, 0xA9A6F0BFFE08A446ULL, 
            0x924598105ED2E2EDULL, 0xBF75D75219F57561ULL, 0x8AE34D1BAADD9444ULL, 0x81DC98CE8F1603A0ULL, 
            0x28156CB84F191987ULL, 0x647CA93CC8220984ULL, 0xF6D2FC57218E2F37ULL, 0x36DAC3F69C5007B2ULL, 
            0x28572782ED927769ULL, 0xA8261EC77B8B635AULL, 0xEAE5EBAA8A444667ULL, 0xDE1CCAE34228352FULL, 
            0x9327B7F32C6C87A9ULL, 0x206E4EEEB109752CULL, 0x7B223BE9856D76EFULL, 0xFA34A1EF9F376DFDULL, 
            0x88A805B58FB9CB39ULL, 0x1B08423716B3D2A3ULL, 0x45471E6EA7D3F127ULL, 0x3AC287B68891A7A8ULL
        },
        {
            0xF605918092550DA1ULL, 0x75098A3A613CCCB8ULL, 0xCEF9E1B0CC3C7D3FULL, 0x8B961D3C241D201EULL, 
            0xB0387907ABF9D880ULL, 0x9698E6946B74F487ULL, 0x6E6539F631A51913ULL, 0xA918B6CAFB8DEC45ULL, 
            0xE1DCC6530455B1B0ULL, 0x1F883F528C67B774ULL, 0x4320CA67D07B420FULL, 0x3CBB1954C6D3F18FULL, 
            0x7C9CF9CDBE03ECE2ULL, 0xD767FA65A2B11935ULL, 0x8C8B6B28A9455C0BULL, 0x23E115B1DBBDD11AULL, 
            0x79510DF0D4D46D5AULL, 0xB8ACC8D5CBF1A277ULL, 0x00A0FF1E08ED9210ULL, 0xF981E6A31C52F12DULL, 
            0x384513D5CCE786B3ULL, 0xBE450A6AF15AC2FDULL, 0xD7BAD629852FCC06ULL, 0x4A73D947A32E2920ULL, 
            0x6DC80A1C1914A2A0ULL, 0xCE58575CD7392D30ULL, 0xAABB1C26CBBA6ABAULL, 0xBFD4582B7A6B1456ULL, 
            0xB6714AB18E63CD16ULL, 0xA9C05D101C9F0D8CULL, 0x4EB18735B9EE5561ULL, 0xC54A41E223AEF84CULL
        },
        {
            0x5D21004C428F77E5ULL, 0xD724B94B0090141FULL, 0x8D964D8AA491BBB2ULL, 0xA0502A38FA6F4C08ULL, 
            0x8E92F220528DB283ULL, 0x457819D3FB7C0CDCULL, 0xA08D39A389DD9C80ULL, 0x188A047A57CB1E89ULL, 
            0x9EBC767362D16375ULL, 0x6FAB7DE67507518EULL, 0x964522AD816BC781ULL, 0x19B23B72A2948BA9ULL, 
            0x5DD6F4C21662053EULL, 0x1FA6CB2F09FC0AD6ULL, 0x0817FCAA36590399ULL, 0xA6A0A5EA355237D4ULL, 
            0x8BA966DE0076D705ULL, 0x720239AEEAB62FD4ULL, 0x8247AFF21577EA60ULL, 0x697D7875E1EBF3FEULL, 
            0xCE6ED6E309906BC5ULL, 0x172D7035ED6C91F1ULL, 0xD58A4D908A404CAFULL, 0xA740B37C597F583CULL, 
            0x2BD8477CD239F6E9ULL, 0xF59E09CFE2B3305FULL, 0xD7F7B5CC9B4C8B22ULL, 0x0BF21F7991C9B0DBULL, 
            0x69EAC61278178CDBULL, 0x38C0BAEF82EA94DAULL, 0x0F129075296BA5B8ULL, 0x158649F23ACDE2F2ULL
        },
        {
            0xE99C9CA3EC280601ULL, 0x080C8EF5E9CE6267ULL, 0xD7B11207E9414736ULL, 0x0B4927FA36178578ULL, 
            0xC713E728F923DE86ULL, 0x34232D2E037DE7F8ULL, 0x53E47F90C30E27ABULL, 0xA2DE6CB3DFDD23B7ULL, 
            0x735522086BF6B1BDULL, 0x50AEDAE8B8BAF1FAULL, 0x75C16DDC2D01EA7DULL, 0x157F9198A819CE77ULL, 
            0xEF0909D8DA12CF5DULL, 0xFB2356A3E5320341ULL, 0xC9F5B5FFE606B210ULL, 0x3A8635A7C4763EEFULL, 
            0xFCAFD233460384F2ULL, 0x0F104B0E22B1DB45ULL, 0x26756219700686C0ULL, 0xB897126FE2D9BE3FULL, 
            0x0DA8F343CE04B9C3ULL, 0x97FA7C87830322E7ULL, 0xA37E7A95F85E068AULL, 0xC0B60692EA8332D9ULL, 
            0x949194827C916287ULL, 0x0D862695EEE75D4BULL, 0x9B4E8411E394055BULL, 0x226051D9031A0384ULL, 
            0x534EA9CAF12B664FULL, 0xCE230847C26F6C15ULL, 0xE06870AB0709F157ULL, 0x69AA706680E4E9DDULL
        },
        {
            0x694EFA80549C10D3ULL, 0xD2CEAC5F43D354EDULL, 0xCD6FD9A5A60A377EULL, 0xA952043C56087515ULL, 
            0x7CB328487B0B0044ULL, 0xA29E3C46751C037BULL, 0xFC5257AB07C8207DULL, 0xD1F9BB73A58206CFULL, 
            0x96DC50BC47DF4796ULL, 0x488DF63BC390CF27ULL, 0x964A1E18E991C79DULL, 0x9459DE75A36E7AAAULL, 
            0x54DDC93B15443CAAULL, 0xA1D06972510AEDF6ULL, 0xBFF312F4E9DCFB6EULL, 0x30061603D492C934ULL, 
            0x18F9A76562F8E19AULL, 0x95A30BAA8D85882AULL, 0x6A99670E2A2931B3ULL, 0xF40FB93F658BE779ULL, 
            0x92DB1444090FD19AULL, 0x139D1760896B6751ULL, 0x661CC54F6B75BB18ULL, 0xE4D04B5DC8E8CC8EULL, 
            0xC3F0B3B743901333ULL, 0xD0850A463F82D0DEULL, 0xDE14B69468B180AAULL, 0xA2CEAF2CC47D1DECULL, 
            0x390E2397948BF32EULL, 0x6BDDA57BC6822372ULL, 0x16903B8C530AE5C0ULL, 0x21D8F20BDD736920ULL
        },
        {
            0x21A0A754EB0A8CD0ULL, 0x17D0244B37191144ULL, 0x059C6CEB0DFDF8F0ULL, 0x1FAFD7433A11B740ULL, 
            0xFC4F562B9011BBBBULL, 0x54E72A296DB96C70ULL, 0xE27A89C3566F9676ULL, 0xB475D1333FC81718ULL, 
            0x08D941D409AC3626ULL, 0x5C2D3796424E8665ULL, 0x7FAC8A3BD063AFA0ULL, 0xE20D6DDDC20B0313ULL, 
            0x6F87793AB51B62BEULL, 0x009894AE8D2127FEULL, 0xBF34C9896450C2E8ULL, 0x9D2BACAE6C2978CCULL, 
            0x89D908897C31DB88ULL, 0x925594D7BF1B71D4ULL, 0xF789F0B59FA9C24EULL, 0xCA3557959B27F5F1ULL, 
            0xD30A87867FC43857ULL, 0xC195FE594FECCB3CULL, 0x90C0327EA397C0B8ULL, 0xBE7500DBDDC2E91CULL, 
            0x30A91976B9485BE2ULL, 0xD76131388EE92D0EULL, 0x3064C4F63ACA5E3FULL, 0x1CD5A331F6564E4CULL, 
            0xD5919CE4D55DDF75ULL, 0xFF6356C3095BC5F5ULL, 0xDE47A07C58768CB4ULL, 0x03F528F0FB350DE9ULL
        }
    },
    {
        {
            0x457A7695060A3927ULL, 0x8CC2C0AFE67FB3DDULL, 0xDEE077CC36CD00E0ULL, 0x74D89451C22214BDULL, 
            0x57D519F9EAA3A614ULL, 0x2E1AAFEA7C1BDE1AULL, 0x2B35D73836AD1296ULL, 0x2A9CE5D3CE16A568ULL, 
            0x434BC81D6411DDCCULL, 0x6D2C3876D4404D82ULL, 0xBF1F68FCBFD05104ULL, 0x2FE8A8BCA25F23A2ULL, 
            0x7A95A44D4180C750ULL, 0x60635FCE7E44CFFFULL, 0x22C97825B2DE4ABEULL, 0x219E78B00FC3EF37ULL, 
            0xDCE5DCB1DDEA3108ULL, 0xA12D73D44ED4988EULL, 0xA5D8E4C5CA5F6E6BULL, 0x29747E42DD10019AULL, 
            0xE0D1643451A1BA54ULL, 0x217F2716DD280C05ULL, 0x784C9402F025CC10ULL, 0x8DC01700ECF1D5FBULL, 
            0xC19BA43AA581C3DEULL, 0x74DCCC6B6F6DC495ULL, 0xB4759058F5D132D5ULL, 0x8F4592D4D77964ADULL, 
            0xAA6206A9BC0D7767ULL, 0xA799B89D1FF03E75ULL, 0xE0053C29068CA83DULL, 0xCF58B30D5E7EA066ULL
        },
        {
            0x78CCF49D06D7D0D4ULL, 0xBE06189665335DC9ULL, 0xD1D73094F8052A72ULL, 0xCCBD6E8F6C07D232ULL, 
            0xE57484B59162A529ULL, 0xF4693B50AE78281AULL, 0xB0D8774A9CCF6BD3ULL, 0x2710D57E27D96C32ULL, 
            0x5BB6E3F862842569ULL, 0xB0C795B6DE976CA0ULL, 0x3511D36A29066F9FULL, 0x409825635DAA11E3ULL, 
            0xFBF555AECB8F1729ULL, 0x31C530C756813106ULL, 0x1E5F602E7D966E61ULL, 0xE1F05F0C35EEB2CCULL, 
            0x09894E9BE0493018ULL, 0x75B06B3F8B3B8068ULL, 0x1C633442383E0AB0ULL, 0x2A9411F1E649BDD9ULL, 
            0x66527F34A80A6107ULL, 0x944EC67A405DF1DFULL, 0xDD1F6D9D998831DEULL, 0x908E9C2F5B685664ULL, 
            0x7136859FD42464F3ULL, 0x845928DB9F129371ULL, 0x61E7BADAEB788E5FULL, 0x2C622CD3D4E028DBULL, 
            0x4469E54E7FD8948DULL, 0x36BED3F4E6CDF570ULL, 0x23B0244677CB9C7FULL, 0x46C334CC2EEFC762ULL
        },
        {
            0x1CD9B9DE6A07F087ULL, 0x9D2369BB1BA13191ULL, 0x11123AC2360F5BECULL, 0x778F6FDDBFC7D0C0ULL, 
            0xDC9A58D4E577F7C1ULL, 0x4D1EFD9D0EEF616DULL, 0x339417DDE84F06B8ULL, 0x732CD8F83D054087ULL, 
            0xA9A335EB41F4BD08ULL, 0x129D33C45BD5D826ULL, 0x64D111256E6F8CF3ULL, 0xDD6D33ED84202A10ULL, 
            0x737A868656601ABFULL, 0x133781D99E02E878ULL, 0xE99DAD9EB78C95A1ULL, 0x6CC3985834CBDB34ULL, 
            0x43EA8347309856AEULL, 0xB71818B24537DD98ULL, 0x293D367AB85DA861ULL, 0x9DD4193493E82BFBULL, 
            0x69EEBD491F2EC188ULL, 0xC0BEB92B666A1517ULL, 0x5681DD9064C96C1FULL, 0x26A0E62101BFB27FULL, 
            0x27683879C0ABC3BDULL, 0xE0EEB663E866F3F0ULL, 0x9C9A8C926F8ADAC8ULL, 0x81E0B01D85631979ULL, 
            0x54489FE6313154B0ULL, 0x421858FF21817A4CULL, 0x087A3AADAE249336ULL, 0xF7CD00B7E8747B15ULL
        },
        {
            0x1BD96735C449B43BULL, 0x15744869DE570907ULL, 0x64BC9E647FD50576ULL, 0xF3F7306686B69A56ULL, 
            0x6ECD33C85797F30CULL, 0x1C18D5911F74F285ULL, 0x060D242F876C48DBULL, 0x49EC8FBDE7B7FEE9ULL, 
            0xDC9DCE3E9A552ABCULL, 0x51B92006883BD35AULL, 0x021DDCD84D1BC7B5ULL, 0x9D7D3D4F3E672B24ULL, 
            0x269AF9CEC01E4CE7ULL, 0xFD0A9CFC78DDF438ULL, 0x3F5C05EE6109B160ULL, 0x642E0DE00BE872BFULL, 
            0x2020C63014A7E7C3ULL, 0x71706A71AD804983ULL, 0x0C8FE1BB5A13B808ULL, 0x4EE51FAC4DF78E5FULL, 
            0x6970D130B7565E8FULL, 0xF775DD847D0B927BULL, 0x37EE1F53E1789F74ULL, 0x3DB9C6FB4C66AC61ULL, 
            0x9B1D77B3B951D4E1ULL, 0x3C359133459F8323ULL, 0x09585A0E8B5644ECULL, 0xB5C03C436B96D971ULL, 
            0x3F63B364A36AFB86ULL, 0xF5A46E149BFE364AULL, 0x74FFE08A127B75ACULL, 0xAF6C8D094F2BA0FCULL
        },
        {
            0x27D9EE1B534CD253ULL, 0x75896798612EF70AULL, 0xB7530E3ED7A5385EULL, 0x6171D75EC5A21695ULL, 
            0x9E631784AF4217B6ULL, 0x3515AFF35416775EULL, 0x48D6DCC221061C02ULL, 0x4AD542EEE0BE64C9ULL, 
            0x2D82394700A139E5ULL, 0x60A0793EA732BC54ULL, 0xE796300B1137DAA4ULL, 0x1734534129108914ULL, 
            0xD44908B681E858CDULL, 0x90B0F764C657A2C9ULL, 0xDB40078DDDFFB715ULL, 0x50B99FCFEAD64D76ULL, 
            0x6DEB99CD332FBE12ULL, 0x98EE2D5A5E8D9B28ULL, 0x8034B3EB2C65ADD0ULL, 0x6748E3CA3036265FULL, 
            0x343BE6FF19D25F1FULL, 0x5758FFD483D0C8E6ULL, 0xC37E69F78822446DULL, 0xED53CAC94D06DEA7ULL, 
            0xD24FBA7F2F62404AULL, 0xD3C611113381E9D9ULL, 0x2EE62B1E6FBE9392ULL, 0x830F6C4D36FE0D16ULL, 
            0x1F25E497B54C3522ULL, 0xA51CDC5621CECCF7ULL, 0x4FD1D300B332FE73ULL, 0x5674D237D8DB17FDULL
        },
        {
            0xAB81F2014B61B572ULL, 0x7F47928B0FE6E4DDULL, 0x13C6F84B2E953C1FULL, 0x4720DA3429D40004ULL, 
            0x6EB562D3266708E7ULL, 0xBAE5B71E49CE9E6FULL, 0xECE2EEDA7460C35CULL, 0x436BB718BDDC6BD4ULL, 
            0x38105D36158522ABULL, 0x2328F2A7E9C66143ULL, 0xA5FC4FA91400777DULL, 0x5EE1F8240461299DULL, 
            0xF99341D2FDBB58F3ULL, 0xCA46AED8859F0DAFULL, 0xA2691A21671F08C1ULL, 0x788CB77AA15C28C6ULL, 
            0x32643ABBE41EB662ULL, 0x8C540723DAD5911DULL, 0x3A5F806814C22AE8ULL, 0x6AC1BF6D50DD56D0ULL, 
            0x061EA44E5B7B1420ULL, 0x19B63A86EE6B1F14ULL, 0x7138349A50132341ULL, 0xAE9B1B7E6704BC5FULL, 
            0xFFB5CF3C3F3D9001ULL, 0xAFEF8F3D9EE5D682ULL, 0x6B13197165EF1275ULL, 0x0E23FCC0C14FBE96ULL, 
            0x6D0B7DC2FE865FCCULL, 0xCEFAC552655193FBULL, 0xFF370BE6135C6207ULL, 0x7C6F946A4D339C25ULL
        }
    },
    {
        {
            0xE3F9F041D24704C6ULL, 0x8B3F8C5749FA03C0ULL, 0x65E5B158DC67C080ULL, 0x229D14434B37E16AULL, 
            0x1E875CC7B6E8B10FULL, 0xDCC6ABC199FB6E35ULL, 0x50AF003F535D0CACULL, 0xF920C098F80B6403ULL, 
            0xF8D8F98350162271ULL, 0xF19245CCB2423425ULL, 0x762EAED0493FF96BULL, 0x195701E4FD1E771AULL, 
            0x8B134827C5DB553BULL, 0xC9C54C7F1C3F6EE3ULL, 0xDE68615DFA15C97EULL, 0xE6419C9176929D55ULL, 
            0x824CF973B14EB72CULL, 0xDF61B581AD933B5FULL, 0x194F8273E7314099ULL, 0x9FCB41FBB469F1DBULL, 
            0xC8B3C214E377CDC0ULL, 0x2F1900F798AF2CA2ULL, 0x2092F45EEFB9A7D1ULL, 0x674AAE953D64B2C7ULL, 
            0x31AB24446F8BC96AULL, 0x8D1D10D8C9BA5BABULL, 0xBD5E73AE90E13362ULL, 0x1F8851BC552B9628ULL, 
            0x2B2AFCE6D4F2730FULL, 0xE9DE2E1A177DD22BULL, 0x380A18E269847FCBULL, 0xBEA49ADDA2EA6CF3ULL
        },
        {
            0x084C21908A627231ULL, 0x6D00A3F9BB74567AULL, 0x54B578899D844CB5ULL, 0x047963CF463085EFULL, 
            0x5EEA1039611A32C3ULL, 0x2ED7B57E3DC6B3B4ULL, 0x14546BE2C86A3E06ULL, 0x8E55278960705D77ULL, 
            0xADE90DB59254D886ULL, 0xDA263CAC5ED585E4ULL, 0x98AF097CB23CD357ULL, 0xF39D0BE15FA197A3ULL, 
            0xFD65261F19295D4DULL, 0xA204388607C11934ULL, 0x69A24AD3B106DFFFULL, 0x00EDC12A2273055AULL, 
            0xF5E173DBBAB7ADA4ULL, 0x2462CC0D72924B24ULL, 0xDF0BB5142623E63BULL, 0xEA9E3310993BB5D7ULL, 
            0x3980E43625F79993ULL, 0x591648E299BC6F15ULL, 0x0DB4C7F2491464D3ULL, 0x18D20CCE68FEE3A4ULL, 
            0xBFB7ED5277339C23ULL, 0xC8B2B2BD71FB292EULL, 0x1E70DDDB1D76ADC6ULL, 0x42243517BDBF0A5EULL, 
            0x0AD277C40155A088ULL, 0x472C4282C62FAE17ULL, 0xD06877787029893FULL, 0x345A6D4068773280ULL
        },
        {
            0x496271B27FB6548DULL, 0xF5EFB77BF85E6DD2ULL, 0xDC863536F156B25FULL, 0x89B0D0F0B2E76252ULL, 
            0x58F56E6545B01580ULL, 0x8A8644AAB5E53FF7ULL, 0x0BC742A0F4D46642ULL, 0x9998CB50CFAB6575ULL, 
            0xB618F870BE40B65FULL, 0x3841AD82E13EBEC1ULL, 0x7282CA5BB0B826AFULL, 0xFAB41A773DC9F8F3ULL, 
            0xCF407286DBBB1565ULL, 0x1CE613E21D728105ULL, 0x331CA933C7C8826CULL, 0xB608E1674281EED1ULL, 
            0x288E424540E034EEULL, 0x82C018B169A9FCE3ULL, 0x302657814C8742D8ULL, 0x6D3E01D89A8DDCD6ULL, 
            0x3BE087A2C81365F4ULL, 0xAE91DD296DC50F01ULL, 0xF7A0D0581F895264ULL, 0xFFC72069A8940C4EULL, 
            0xEE952395D875A868ULL, 0xC71CD054D060D33DULL, 0x08D786049D7845CFULL, 0x294ECE584BAAAA68ULL, 
            0x9030FCB062F300A8ULL, 0xF9947DEA9D4ACFE3ULL, 0x75931701D0BC877FULL, 0xBDC4D9C0B4170B6EULL
        },
        {
            0x73D7F280AEBC59E0ULL, 0x0A0B4A3ABFDEA64AULL, 0x974851FBD51FB37FULL, 0x62292FEBE1351A96ULL, 
            0xDE39A2D436653007ULL, 0x39E5EACE347A8943ULL, 0x567CCA43623D3910ULL, 0xDF8AC6A62E81D752ULL, 
            0xBDADC5624CB22B8EULL, 0x0B6D2DE6DBBE0D59ULL, 0x52403A0E78974091ULL, 0xC5BF56D7FE766AFEULL, 
            0xF3A8B73319EC00D6ULL, 0x7E787205CB4449B5ULL, 0x3AF53942A2C9645FULL, 0x6450D96BB9B7BB93ULL, 
            0xDE539D4A13EC4445ULL, 0x610DCCFA9737A964ULL, 0xF0581A3129971F94ULL, 0xC6F3B07C1CA362B0ULL, 
            0x8C25937FD409F8EEULL, 0xD87D5D02BF712C24ULL, 0xFCAA3B11F7EA12AEULL, 0x579DFBEA54EBCF10ULL, 
            0x97469DB8BF48BD8AULL, 0x1D70198048144372ULL, 0x7B12517A5D14AC6AULL, 0x2816B658B5CC3D03ULL, 
            0x1768BD8065F8F65EULL, 0xC349603F8BB5AEC4ULL, 0x4B6652499746968AULL, 0xB538F85A21F0F52AULL
        },
        {
            0x9174A3C7BDE2E53CULL, 0xA09650C29FECFA59ULL, 0x7E07100FBEBEF305ULL, 0xCD66860DFC345978ULL, 
            0x9DA40486724693D9ULL, 0x16A4B10B5FE5FF27ULL, 0x9E874722FEC2A947ULL, 0xC78FCE2125DAB42DULL, 
            0xA91893E5E164EF18ULL, 0x43552313B4E639BAULL, 0x58506499AAFCC418ULL, 0x722D5BB9BC5597B9ULL, 
            0x711903A28E95B29BULL, 0x3E13419662B0ABD5ULL, 0x36849797D6C0AABDULL, 0xAF4DABD6ABF93A61ULL, 
            0x177B756AC21BFE5FULL, 0xAFC958E5B5D37273ULL, 0x447B6EA06B5CC50BULL, 0xBB6DE8705726B4DBULL, 
            0x33C7BA21ED4A98D8ULL, 0x1B5B0971A5555D06ULL, 0x5ABA5D2AD909E20EULL, 0x86E8FBA389A3A0EEULL, 
            0x7BCA6BEFD33A2BD5ULL, 0x21139F2C93CDD589ULL, 0x1C15510243E3758AULL, 0x2297A36B987C48AFULL, 
            0x23046E711A1F28E8ULL, 0x5433010B4D0137B1ULL, 0x7E4B3B18C723DF76ULL, 0xCF0CC75DAF1CE74DULL
        },
        {
            0x7754FD55D4E8BBBBULL, 0x93279E90B4814637ULL, 0x8DF51185AA0E76F8ULL, 0xCBB2AC012470C004ULL, 
            0x91E64F393614C40CULL, 0x12F0A880ECB54764ULL, 0x928B20C2D1E30150ULL, 0x887DDC30AC6213A5ULL, 
            0x47AA0F79B57D88D9ULL, 0x9DB34ED950A70C2DULL, 0xBE8B59F8F7745D49ULL, 0xFD7D1E554321F78FULL, 
            0x706BEA78A31EED5DULL, 0x87E92AC204593DBAULL, 0x0784F6E4D7C191B4ULL, 0x151A5AECF9326CF3ULL, 
            0x7C0DA8787A35A165ULL, 0x7B2B389D32646C3CULL, 0xA1233F91967DE558ULL, 0x732C817DBB08BA62ULL, 
            0x35F06FE318BB69F6ULL, 0x42BD049266DA75BDULL, 0x50226D7273E938D7ULL, 0xBF21C3F6E89B633AULL, 
            0x62E10AC52CF47FACULL, 0x4ECBC293EB2D38F1ULL, 0x4334DE4EC0743091ULL, 0x673A11D9FE9F000BULL, 
            0x9932DEAAA43420F0ULL, 0x2EEEB594A29DE1F4ULL, 0xDC9C3F20923D94C0ULL, 0x38EDB4C034189337ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseCConstants = {
    0x749B2A9684C9DE49ULL,
    0x5FE4642113815FB4ULL,
    0x394B4481E2744944ULL,
    0x749B2A9684C9DE49ULL,
    0x5FE4642113815FB4ULL,
    0x394B4481E2744944ULL,
    0x84017321F28DBC1DULL,
    0xE1B2685AC811F0B4ULL,
    0x8F,
    0xB2,
    0x22,
    0x81,
    0x79,
    0x4B,
    0x4F,
    0x52
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseDSalts = {
    {
        {
            0x4BB7048564804A3CULL, 0x602822A4A5F28286ULL, 0xE5840FECB99ACC8DULL, 0xCB7CEFF179201382ULL, 
            0x84E7E681F14671E3ULL, 0x91B266A6E985DC8EULL, 0xA89E02DCC6864A08ULL, 0xDD00C6D7CB69EC3BULL, 
            0x3E6542AFDE1B8277ULL, 0x4C9339BABD0A1683ULL, 0x6B8C6BF74E0F75FEULL, 0x11B53AD36A0E67C9ULL, 
            0xB843356E23536FD5ULL, 0x507252C67F66CD73ULL, 0xF87DC7DA4DAAE74AULL, 0x88D9F7B53699EBDEULL, 
            0x71D16BA1D434FE23ULL, 0x68034FF18CC6204AULL, 0x75FF388DDD0D7B4AULL, 0x6626808C78FE98D3ULL, 
            0xFD0C89ABAFF7B5E9ULL, 0xD3DA1D0D9C9D80B8ULL, 0xA5557BBB40848C5EULL, 0xDF384E45675B6434ULL, 
            0x9C0E1AF1F3CA8B7BULL, 0x30F2747916599067ULL, 0xF1E711E94C1A5CF0ULL, 0x54FDBA7B40B8CE35ULL, 
            0x0956DD5397369847ULL, 0x4D5D76529332F942ULL, 0x6E712F295AC6DF83ULL, 0xF276217E445BD806ULL
        },
        {
            0xE59B09BFD87A5861ULL, 0x3F731BC0FBCDB4A5ULL, 0xDC95065D3F0EA334ULL, 0xA38EEB364D5D3525ULL, 
            0x90F7DC9812C8E97AULL, 0x351CBCC10918D5D8ULL, 0x0A463A092554B90CULL, 0x13D0974C437D76EBULL, 
            0xC0CF1279C25D2ECEULL, 0x13863F63DE92FF53ULL, 0x963C7EFB2646D800ULL, 0xA1B86EF160779AD6ULL, 
            0x1755FB141573C14FULL, 0x6FD7ABE7A8704B56ULL, 0xD0D192496FEBFD64ULL, 0x60A2528C69DAA054ULL, 
            0x5140A9918A6664D2ULL, 0x16EAEBA115861D02ULL, 0x946B581AAF04DA75ULL, 0x9D216D0684C0C985ULL, 
            0xF0CD03F28F78770DULL, 0x053D7C090D07E98CULL, 0xFDBC1369BA56A62BULL, 0x65A232F35086BBBDULL, 
            0x3E0E9E2F80EC44A1ULL, 0x7CD231D80800529AULL, 0xB41E8E48640BE05BULL, 0x2CF0A82B63809A90ULL, 
            0xED9FD1E2A84DAC63ULL, 0x3131D6C7FBFD00E1ULL, 0xBC8148AACFA2AA4CULL, 0x48CD6B9E098DF659ULL
        },
        {
            0x84FB0555AB7367E5ULL, 0x17F4CC470A9BF4C9ULL, 0x35E459F1203F74C4ULL, 0x781C5C10F60B56BCULL, 
            0x24994310682DE6C6ULL, 0x1D7B4A7FD5F8230FULL, 0x689047F2581735F9ULL, 0x0AE15DA045294615ULL, 
            0xD7DF103E68F12C72ULL, 0xFDC7ECE9FA14BD42ULL, 0x2C87883A2919B3F6ULL, 0x721A1419078C5326ULL, 
            0x3289C67E83978091ULL, 0xC574B09C75578212ULL, 0xA25C09DBC8E9010AULL, 0xF578717AF2AD44A1ULL, 
            0x8E34EDAD65C6BAAAULL, 0xD55465565BDE343AULL, 0x0929ADFECFF659AFULL, 0x9AF79A6C76B169E9ULL, 
            0xDADB4A4B2AFA3782ULL, 0x6BD2F65F385BBAF0ULL, 0x4F5F39572D0F5585ULL, 0x888257545B5F180EULL, 
            0x679CDDB72C7B138CULL, 0xE7993F70304C70FFULL, 0x598D4CAFF0318FF2ULL, 0xDF5B7BFAD96CCE9AULL, 
            0x7A39C4CAB195CC5BULL, 0x807C920DAC05BCF2ULL, 0xDB0C024EE600BDAEULL, 0x4340C8779B591FF8ULL
        },
        {
            0x2504F01558724D59ULL, 0x609D00CD39166ACAULL, 0xE7B5FE48CBE2B42BULL, 0x8A9EB85ECDF9B6E0ULL, 
            0xD96477DA8481058BULL, 0x8B1AEC41840D5D33ULL, 0x696821F6EB2868E8ULL, 0xBBE13F408EEA19E4ULL, 
            0x371375E9067EA68CULL, 0x0D64D66EDF875125ULL, 0x5B4C140984F7793AULL, 0xF9A1458E4CFA77CDULL, 
            0xA70508BAA901E49BULL, 0x885D75FF6F2E7E73ULL, 0xB484E0D8C2CD2C1DULL, 0xCC41CE9D022ECA05ULL, 
            0x2AEFE5BCE6D79F45ULL, 0xFDE8ACA9E8DC4730ULL, 0xD1E6B2781402F9A4ULL, 0xDA13A8ADB779C935ULL, 
            0x87F66EE1FF06FE21ULL, 0x9702D48D2C422985ULL, 0x6464E52272AE5E34ULL, 0x6887189146CB0ABFULL, 
            0x109806F2C7A1AE58ULL, 0xF63FA214C4EFDF2CULL, 0xB810FC51B9703122ULL, 0xFD204A301DB6872BULL, 
            0xF58B73AD1AE82397ULL, 0x494ABC375228FDBEULL, 0x06B96716B5797826ULL, 0x191B0D0C18522A28ULL
        },
        {
            0x9E5AA9E0EC0455E5ULL, 0x99FDB663C0DA3EF8ULL, 0xFD61412CA2C55154ULL, 0x439BC0FE49306729ULL, 
            0xECEC462BE8C4F43FULL, 0x37A09DE76912059FULL, 0xD953CFA32B63B553ULL, 0x37B54EF12939C4A1ULL, 
            0x9FD06BDB50E5DC8AULL, 0xD86E6342CFDE7E60ULL, 0xECD3AB09EF82CEDFULL, 0xEE6F0233A0C032F9ULL, 
            0x063D21A735FA61E1ULL, 0xDE3B6BE3E3D82A92ULL, 0x05C7B22C426DE15CULL, 0x0720472B701057ECULL, 
            0x948D1AF78690EA8AULL, 0x7ED0B769B94F0AA3ULL, 0xD7B9EBF41977C935ULL, 0x9DB54CFE50C4BA97ULL, 
            0x532F0FFD1B343FB6ULL, 0x1E3FB4F5F93F182DULL, 0xD172AAB7C3C49714ULL, 0xEDAED448F46EBB26ULL, 
            0x51F2DE5E3AD26474ULL, 0xA40EFF98284868ADULL, 0xDA439D91D1C8C940ULL, 0x41A578D9239CCF2AULL, 
            0xB2284DC453AC5F31ULL, 0x04BDBEA631A6A2D6ULL, 0x3DB91368939614AFULL, 0xDC6FB291331147FBULL
        },
        {
            0x968DC7F8CF523D70ULL, 0xBC962BBEC0E0CDD6ULL, 0xB14CD7A29F31926CULL, 0xC248EE8FC171101EULL, 
            0xADB7D46D71911363ULL, 0x9AFC722DD442EA06ULL, 0xA4DA9EE26850D995ULL, 0x6C5C80B5EB8F18AEULL, 
            0x687FDB8B2AB69288ULL, 0xF1FE56B988FDE236ULL, 0x276D257F6A0FA5D2ULL, 0x89D1ABC609CA8CCAULL, 
            0xF41721C69C8D0D15ULL, 0x1E170BB5B526F128ULL, 0x6E192A2E471E1467ULL, 0x0657C2E99470C245ULL, 
            0x015690B23124F216ULL, 0x4BE212E877BF8D80ULL, 0x596D7DB7857F71ACULL, 0x49A8465905F1C287ULL, 
            0x5CCABD3F56CB1F8FULL, 0x1C4A44F4D414B2BDULL, 0xD709BA88B6517E0AULL, 0xB5378AF9D9CC2B3AULL, 
            0x34EC926F1710EC55ULL, 0x24565FF7B2E97984ULL, 0xAB4873DD43053574ULL, 0x50949A2BD480E28CULL, 
            0xF9CDD4D64B010BA7ULL, 0x147FB82E27401345ULL, 0xFC32EDEA8CA0049FULL, 0x568B4CC5CD8043CAULL
        }
    },
    {
        {
            0x123B78B0F5C236E6ULL, 0x85C975765842EA12ULL, 0xDDE928C17787F1F2ULL, 0x16A5B17A621251CEULL, 
            0x9C3BB11AF85F6F87ULL, 0x0247644F7CC39BD5ULL, 0x9A1A6F94F30DE037ULL, 0x4855DC9AFBE01FAEULL, 
            0x8D43B228437ABA6BULL, 0x1D1D804DEB76AD32ULL, 0x8B5D9A9DDC579C14ULL, 0x22CCFA024414D21DULL, 
            0x25EE9322AF91874CULL, 0x3E063A2346FCD251ULL, 0x8ED36D85A3F0E60BULL, 0x222573DAC6693D94ULL, 
            0x2FC7FCC8B1B21BE6ULL, 0x485D452351DC5D45ULL, 0xF29D2B2BDE7BF72EULL, 0xBBBEF34863C5AF6EULL, 
            0xDC4D098E65BC718CULL, 0x62B6F98712A5CD66ULL, 0x389D1639199A170CULL, 0xA70340B6FE821DD4ULL, 
            0x86641161BC470280ULL, 0xEFF07680FC513807ULL, 0x95AFA9385480C6CAULL, 0x32AD9FA1444BF54FULL, 
            0xDB16C13EDCB4347BULL, 0x63DD00B9C3863ABAULL, 0xBFA528F36D92A723ULL, 0x138D41B0D57E5549ULL
        },
        {
            0xFD9276FB4359A1BFULL, 0x27280C1B12F6AC30ULL, 0x259AC3FF4CE3BB24ULL, 0x5586312F8B9FFF28ULL, 
            0xECF58201939AD73BULL, 0x2BA9184356940C22ULL, 0x5E6F64E9D2A1BAE4ULL, 0xA4FB59FDE4AA1FE2ULL, 
            0xE209C0810377B350ULL, 0xDCC7723DF2623654ULL, 0x5FD9B174C9EFE867ULL, 0x2E3F738589DE60DEULL, 
            0x8009F2CD2D902D60ULL, 0xAFD4568C863E9027ULL, 0xA01C41E9DD283750ULL, 0xAAEF118F47ADAB8EULL, 
            0x7F583BC386755C80ULL, 0xDE3090BBA04298F6ULL, 0xE96A7711EE97F97CULL, 0x5FBE9B5A976C54EDULL, 
            0x46F416814EA1314BULL, 0x42C5C86FC91579E2ULL, 0x027D87DEC27062F5ULL, 0xE9028427B6634944ULL, 
            0x511AEE08AE734811ULL, 0x6E8B30819D8F697BULL, 0x1E914BF6CD75460AULL, 0xEA6243CD1DF1A0DBULL, 
            0xB0F402450881A88CULL, 0x2D2E393E3733E8FFULL, 0x39CEC075D926612FULL, 0xD77A962B5B736166ULL
        },
        {
            0x419F3128E6DC49FCULL, 0xE8841556DCCD9CC1ULL, 0xD5AA15482523C99EULL, 0xDB0AA98FA6910E83ULL, 
            0xF216FF151546B0B6ULL, 0xC18A8601E743BF12ULL, 0x37723D1D74EA59F2ULL, 0x523F014413634C74ULL, 
            0xBD81F542CEF87073ULL, 0xAA09F2C9004A6094ULL, 0xEC052308E506BDC4ULL, 0x5803A7AE86A371F0ULL, 
            0x644337CCA42AA246ULL, 0x943794C8662A89D8ULL, 0x4C50C2C97501F040ULL, 0x4E5F6603C1066077ULL, 
            0xF8303E3505B574B9ULL, 0x860E34E28316B789ULL, 0x121F2870F7EFF1B4ULL, 0xE74BA8517FB7913BULL, 
            0x57E494D9F6F979A8ULL, 0x53B1CD3CA4B46EA6ULL, 0x9FB82D6341315CE2ULL, 0xE6A92AAFE479B21BULL, 
            0x0D7FBDE60CAF24B2ULL, 0x4650C828E4BED92EULL, 0xD43F25DC3ABA56C8ULL, 0x6E8C6E3B9DC47C18ULL, 
            0xBF76C96B3559D195ULL, 0xDCC3355AAEC93F0DULL, 0xEA4A96CAFD51B51AULL, 0x61114330EE0C665DULL
        },
        {
            0xFAE3AD371F789291ULL, 0x6E583A889C4D8B34ULL, 0x053F3CED595A316FULL, 0xB9B4FC4918077B0FULL, 
            0x5228351DABA0722AULL, 0x59F0F672286D8C02ULL, 0x678225FFF7FB9845ULL, 0x879150A9DE5A555FULL, 
            0x15F0EF9F7C89945EULL, 0x70247D98B66295F3ULL, 0x15045766F51056A7ULL, 0xE14235A79EADD00BULL, 
            0x8A19980B8BAA3645ULL, 0x757F97352AED0997ULL, 0x8571691E3EB57786ULL, 0x16BE846AD2B2AD91ULL, 
            0x263A6DF2E8A4BC57ULL, 0x9A1CF07334CD1BB0ULL, 0x2BEA24AF3C2D2F49ULL, 0xA73D5DB3A94D28E1ULL, 
            0xA7D90D9554826AFCULL, 0x549188997EFE5C78ULL, 0x41E2BB595D23F0DDULL, 0xE4F9C9DCC6961D4DULL, 
            0x3B7D394326ABAF68ULL, 0xECEF087A90DF02A6ULL, 0xF45634546644C8B4ULL, 0x039CA5E01731D44EULL, 
            0x8A813F5BAE406FCAULL, 0x573527CF7987BC8AULL, 0xCCA574ECB9803B98ULL, 0xABB67826324D11A3ULL
        },
        {
            0x29B22A5264E89FC1ULL, 0xA04B28C91910270AULL, 0xE1809E3D368BEAAFULL, 0xA4C6746357B7B8D8ULL, 
            0x4BE27D454B04CA0BULL, 0x4A8530448604AFE1ULL, 0xD5688B0EE3C72FC5ULL, 0x3746C9E217775C1DULL, 
            0x4AC95E09E11F785DULL, 0xB97AA1D67119344DULL, 0x0CC517AE6B29A637ULL, 0x8918120E898F860DULL, 
            0x29DA8B756DE51E29ULL, 0xCF5487740A15F01EULL, 0x21077F9D4CF76BDAULL, 0xE2F3E65E5C0DCE6DULL, 
            0x240C359DE74F0C8AULL, 0xD2EF45594D79A5D8ULL, 0xCD7DFF9E3E15B994ULL, 0x98FAE6CCCDBFB4B2ULL, 
            0xF99A372C9ACD46BEULL, 0xD4F97007BAC6375AULL, 0xB059BCEF5EBFB0C8ULL, 0x15A32EAD4BD789C8ULL, 
            0x4511FCFCFF64E61AULL, 0xDD904FF3E80FE417ULL, 0x4605AA3918951882ULL, 0x66B6069F6EF8CF4DULL, 
            0xC191B8094C8E5210ULL, 0xDDD7B99491A05F27ULL, 0x39F5CFE7F50018D7ULL, 0xD87FFCFFD920D4CEULL
        },
        {
            0x420FCED14608C87AULL, 0x7F7BB22980A6511EULL, 0xA3D44D24BA8EF6A5ULL, 0xD17832E37076ED71ULL, 
            0xF59975589BBABAD6ULL, 0x446B5E94CDF25A61ULL, 0xB5344F3D9DAEB631ULL, 0xE4755BDEA70FD3D1ULL, 
            0x9F5D951A7F4692F0ULL, 0xC5D96EC4E3AE4215ULL, 0x85CC48A2E7F7D624ULL, 0x9239E66F57A72633ULL, 
            0x341D56EB725A9B70ULL, 0x941CDAED2FC4A9D1ULL, 0x2A85FF7C5E04CB84ULL, 0x8A02F2251E8B11E6ULL, 
            0x935E9945C20FCC82ULL, 0xF800A63250199347ULL, 0x4034222E1F66C93CULL, 0x15D2BDE19D697A75ULL, 
            0xE84F8B069E680904ULL, 0x7D19F517BD52203AULL, 0xBDA986E7D06D2F70ULL, 0x1849382D26FA9D10ULL, 
            0xF2F220E27AE7A6C3ULL, 0xA09B910DDA0D159BULL, 0x5F12AE74F97903F3ULL, 0x5919989AB16AD08CULL, 
            0x04E2A8121DD05DC7ULL, 0x10994AB85FE77566ULL, 0x28DA8DE3BF261843ULL, 0xE37F4EB734A83943ULL
        }
    },
    {
        {
            0x72EF5757D3C5D878ULL, 0x82D895E07456FB47ULL, 0x317B1AB50CA71BB9ULL, 0x9608ED04323DB03FULL, 
            0x72B3173B57A52D26ULL, 0x61A8D6B5BE63C2C7ULL, 0xD70D246E36E4A49AULL, 0xF04220EC6538686EULL, 
            0x4ABF39002477F741ULL, 0x23D747E10D58A282ULL, 0x42E0204BF926828DULL, 0xFE7FE9F962450C73ULL, 
            0xEBC6493C1FA4224FULL, 0x90578F08D2A1186FULL, 0xD640064C59AB389CULL, 0x3B4085DEE64E84BDULL, 
            0x6F03F88C2493FFA4ULL, 0xB067F3F491313593ULL, 0xA9AFC9D08802C51FULL, 0x88A853B89C0B12AFULL, 
            0xCCBA5BC4A36E03DFULL, 0xC1B14AF67E0BD55CULL, 0xB70B0456A4232972ULL, 0x8B3914A9262D9D5BULL, 
            0x63610FE68FBCC7C5ULL, 0x08743756D27F2CB2ULL, 0x73B5EC25C734D026ULL, 0x99DF80F8E7DFF2D3ULL, 
            0xF29709E680FD2B60ULL, 0x4FD6B9E89DDCE19FULL, 0xA2FEB3A7253D7203ULL, 0x52F29F4E7DEB0EDCULL
        },
        {
            0x7A38A87EBC5D014AULL, 0xB1A9E4CC3897B224ULL, 0x4A20AB1D21A65DFDULL, 0xDFF061C267DDD0A8ULL, 
            0x94C4A5BE5C943035ULL, 0x6E22C62B5A6CF25FULL, 0x68D9FCCAE8BC1A47ULL, 0xCAC7035D9A5883F6ULL, 
            0x4C8141571FD84F1EULL, 0x317118F390CEFD10ULL, 0x62FD316F07EAABA6ULL, 0x962E3BBB298814D1ULL, 
            0x10BF4DEFC45C357DULL, 0x3D287A86B1E6F2C5ULL, 0x80034E932733C6CAULL, 0xF9461B5A3994DA2FULL, 
            0x03C1517468D7FF5BULL, 0x8CC4EBD4D5ECED0EULL, 0x01A48A9163606BC2ULL, 0x86CE2DE78B4AF209ULL, 
            0xFBEA53E743774F8BULL, 0xABC86893F5982C37ULL, 0x8DFA44CBA8F3B018ULL, 0x13CA73C46425C273ULL, 
            0x93D73016BAFB1DE5ULL, 0xF766E6B968540BAEULL, 0x0D518E6B55DABA0FULL, 0x7899FEF8E2D01CBBULL, 
            0x586C72C721A060D0ULL, 0xAC38B5DC84259C17ULL, 0x76361F6BEE3D3E09ULL, 0xBF63442C89B84361ULL
        },
        {
            0x81297092B79E90DBULL, 0x23B798A455CFD156ULL, 0x52BF9EC88F6089E3ULL, 0x09184793BF06C5F7ULL, 
            0xB87E43606EEA453DULL, 0x5994BC3EECD0B52BULL, 0x510A55B6477BCACEULL, 0xAB46305EF8D970B4ULL, 
            0x502CD11BA70417EDULL, 0xBB7C2A1C6B524AABULL, 0xB8B3E60EC105FE24ULL, 0xBDD248261842F196ULL, 
            0xD89B96E8FEAE5A81ULL, 0x1DF8ED58651AB946ULL, 0x08F87FB368104B41ULL, 0x7B7194C854871FA7ULL, 
            0x3A502DA2251CAD40ULL, 0x0E7C120B12DFDF77ULL, 0x84783F12F8FFE6B5ULL, 0xF4318412326EA448ULL, 
            0x803744890A7147A2ULL, 0x073AFFAAFE680B13ULL, 0xA5E38DB85C7FCEADULL, 0x8BC0067B796212B9ULL, 
            0xC4B3F52BDD9E5F84ULL, 0x04E93284DDE37AA4ULL, 0x00B735C632922243ULL, 0xD6F7405CD300D6C8ULL, 
            0x38054D96E2E40D10ULL, 0x723A905216160CA2ULL, 0x69CDEFE207F56B84ULL, 0xA86A809D1DEFF956ULL
        },
        {
            0x359701FB135FBBC3ULL, 0x576390D950EC6CF0ULL, 0xF197717430A67E5FULL, 0xCA07BC54B3EBCFD9ULL, 
            0xA71001B6DF5F3AFFULL, 0x4F498EE90980FE85ULL, 0xFFAF712D904443BDULL, 0xE9F298376813BCCEULL, 
            0xD06697F77611FEEAULL, 0xF5C8E050DFF5A3DDULL, 0xDA70F86A062B87BFULL, 0xF73B8D6FBFC0AB59ULL, 
            0xA8F95503E8C6869AULL, 0x02A83E1A06D5DFB7ULL, 0x823C80F687FDE799ULL, 0x2712D7E84E543175ULL, 
            0x7D61ADE2A8471655ULL, 0xD7BEF0E2CCF72FF9ULL, 0x64FFABF166F45C43ULL, 0x3C231D705148C852ULL, 
            0x0BAFC968F2859A76ULL, 0x89800B214784D901ULL, 0x0136A567A4FE2D47ULL, 0xC2AFEDCF28457F96ULL, 
            0x4925E0645D729E27ULL, 0xF48F1FB6E895E2C4ULL, 0x74CE6612DBC3B2A5ULL, 0xBD5D3C3AEB54199DULL, 
            0x564A164F3FA20CF6ULL, 0x56FF65E855E72604ULL, 0x6A52B7B1E075F155ULL, 0x7E2D8CA2F8423E53ULL
        },
        {
            0x69BB8CB01902F899ULL, 0x50449D20E95B3814ULL, 0xAA2AD7419CB07A8DULL, 0x1CAFFCFF43A3BF7BULL, 
            0xE7506664930446CFULL, 0x2246C9636AA9541EULL, 0x4EB99D5A2CC25780ULL, 0xDADC6A9E934423F5ULL, 
            0x196EC514FE621776ULL, 0x3370F28F0C31678FULL, 0x5D6E13080C4DA0B5ULL, 0x867B9333F1D97E97ULL, 
            0xF0D46610B7731A9BULL, 0xF9AB79C37852CFE4ULL, 0x0432B258043442D5ULL, 0xD9945D8D850A464AULL, 
            0x7BC7D13AB94851BAULL, 0x6B6D7895481F999DULL, 0xEFB5AA54A8DDC294ULL, 0x493F5A86CF8DC1B8ULL, 
            0xD89E2371B59276E5ULL, 0x61305295C951AF25ULL, 0x97F9757466B7F1AAULL, 0x129E0050D0E023A4ULL, 
            0x69403C236F8B12E6ULL, 0x1DE04D52AF777ED4ULL, 0xD79E1F2C51A044E3ULL, 0x40A98DC77F0D717EULL, 
            0xC870409737DDC2EAULL, 0x33D4E12E26935C00ULL, 0xA1474CCFB39D4716ULL, 0x6E0F019932AFB380ULL
        },
        {
            0x7C68FA620A135B0AULL, 0xA3A2AF2B5C7EB993ULL, 0x132594842EC55775ULL, 0x8C0670CC387CBCDFULL, 
            0x334EF411BC599F13ULL, 0x901830887E64DE7FULL, 0xA9025A61CFCC331EULL, 0x9B7E47975812B7F9ULL, 
            0x5748F24E6EA76116ULL, 0x7348277243C48134ULL, 0x8BED571165A1AE45ULL, 0x975AEBFC9CFFF72AULL, 
            0x4A8BE228F8F454A5ULL, 0x6962DC551A74230BULL, 0x35F9E9B4CF014CBAULL, 0x1FB571F8A0E3D05CULL, 
            0xAD65F83C2352A42FULL, 0xFDEA72A6A9817548ULL, 0x37B752F5BF8C3194ULL, 0xA6AB2734D0789E25ULL, 
            0x33C9779BCB279720ULL, 0xABB0094DA9A4D752ULL, 0x2B767437E79A75E0ULL, 0x8E00E23EB071CD4CULL, 
            0x8E29F3ED3DF40DF0ULL, 0xF76E80FE787A173DULL, 0x8E5ED84E8B30CB9AULL, 0x2F4EF2E1F7F9A7FBULL, 
            0x479FBA1D8E1E4F4FULL, 0x40A36FCCE6227EA8ULL, 0xB6760D29C3133472ULL, 0xC6F6849FC6DFAACCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseDConstants = {
    0x0C35640B40957D93ULL,
    0xB9F683BC5946DDFBULL,
    0x023A677C8132150CULL,
    0x0C35640B40957D93ULL,
    0xB9F683BC5946DDFBULL,
    0x023A677C8132150CULL,
    0x62D10E5C00970DC5ULL,
    0x23117AFF50E1DF47ULL,
    0x40,
    0xD8,
    0xC5,
    0x22,
    0xF5,
    0xCA,
    0xD2,
    0xC9
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseESalts = {
    {
        {
            0xF8B2B39EF7D21FB0ULL, 0xDF27E9F783FE07EEULL, 0x27E249D0990FED69ULL, 0xC57804506CC2F7CAULL, 
            0xD43470A8246B4FF5ULL, 0x5062A223DCEC7856ULL, 0xABB9056FA9DA6BE8ULL, 0x3F063A2A93125E44ULL, 
            0xE37A7A5282BE8515ULL, 0x1C0C376F1CE1135AULL, 0x1A91D9177D183F26ULL, 0xCD81EBFD93728877ULL, 
            0x534D561D0B1C51A1ULL, 0x613868F51CC9C7A7ULL, 0xCA9805E337BB1DBDULL, 0x9F719B39D0A8E5F0ULL, 
            0x1156AEF0CFB597B7ULL, 0xFB33519474783BF2ULL, 0x16D9493F6EC0510EULL, 0x5D06E7869514D15EULL, 
            0x69E782645AD73C38ULL, 0xC2CCA05D9E21898BULL, 0x28ABF563549F7C42ULL, 0x7F47C5EC22D0E3ACULL, 
            0xD69FD92E163D7203ULL, 0xFE9A95A3B07ED2A7ULL, 0x54EBAE596EF9B686ULL, 0x39577C8854091AA0ULL, 
            0x69038DD93AB1FA8AULL, 0x03234F5D0AE79D85ULL, 0x614A35C174799CB5ULL, 0xA4E8352A71954BF1ULL
        },
        {
            0xD4A11734B6D29D5CULL, 0xF5183927C2874B37ULL, 0x4154424527C08078ULL, 0x6CB9773480E5195CULL, 
            0x226DA30C292E7275ULL, 0xE890FC658C680B61ULL, 0xB2FDA2425BD76B4AULL, 0x278D2510EE8CDB3BULL, 
            0x4FA41D5E2F14779EULL, 0xEB038206B184BD3DULL, 0x539F9AC5D119A459ULL, 0xFCC56004BE168C1FULL, 
            0xFD10C4113E88E215ULL, 0x5CC0598C4D41D7C8ULL, 0x9BD61946D5177BAAULL, 0x43F8548036A2EB3BULL, 
            0x84E665FFA4ABBB30ULL, 0x1F47463D0BC81364ULL, 0x79A18FE48EC55744ULL, 0x638676312CF92189ULL, 
            0x9A5C2D1C0A644689ULL, 0x8FB62E1B9EFE3BF2ULL, 0xEB6C559051EB219FULL, 0x6D37157238109C09ULL, 
            0x09FB7383EEC0B32FULL, 0x06E7ABDA51F28418ULL, 0xE04EB23A7C56E9DEULL, 0x7E9164AE311252CFULL, 
            0x29EAC8E59846939AULL, 0x9D6D1906077E636CULL, 0x877EFC3B51C65E5FULL, 0xB12538052C0D55A9ULL
        },
        {
            0x0724997235DF4398ULL, 0x5A03CF929151E419ULL, 0xE1133DD36FABFA35ULL, 0x2F36B35229D19F14ULL, 
            0x7171759DD663F7F4ULL, 0xEF16DC6CFD54FFBAULL, 0x7E702B8697518ED3ULL, 0xD40B663589D464EFULL, 
            0x5835218287118FEFULL, 0x999B8A9DB32520C0ULL, 0x314D8257E1F685CBULL, 0x4EF7BF5545C17D9EULL, 
            0xD61828557272CBFCULL, 0x488188EAB7C1AF67ULL, 0x4D71513948EAB94AULL, 0x89E4E03534436446ULL, 
            0x475C54F28EBFD7ABULL, 0xDECF83DDBA7C641BULL, 0x0388F68706B9DD8CULL, 0x541F8DBD51B926FCULL, 
            0x8884920BED83A1C4ULL, 0xF33E92B4A5FB1803ULL, 0x3757933C3C175AD5ULL, 0xE78231586B403912ULL, 
            0x5974E46584C556BCULL, 0x28BDF832A1FF9750ULL, 0xECC9A2D6E151C220ULL, 0xBBA8D16B02980481ULL, 
            0x51C42E109B3639E2ULL, 0x51EAD1BC43B9C151ULL, 0xCBD5FBAC76B0ECD6ULL, 0xCB4E05745EE8F786ULL
        },
        {
            0x533A0A3E5EE8F358ULL, 0x13133540B7587FD9ULL, 0x52992B859CF669B4ULL, 0x8CB11C1D89B78B1DULL, 
            0x624EF3C774934687ULL, 0x62509C5E6D016488ULL, 0x841C0F62FBF171EBULL, 0xA40B355B34ED2F20ULL, 
            0x6EBB9B8FC7A58ACAULL, 0x0C3E0511D38BEBEDULL, 0x88B1005AA73882BEULL, 0x02F18604BA55B7E1ULL, 
            0x1E24FB965A325CDCULL, 0x604870A69A333E55ULL, 0xC31915EE40069C81ULL, 0x3CBE10E749C11620ULL, 
            0xF0B40F44371F5FA1ULL, 0x2441231F5A155553ULL, 0x08174E2017658B25ULL, 0xCCF500774921DADEULL, 
            0x1A9CDC61869CBBECULL, 0x20445F1B80C44235ULL, 0xF4857FD8148128CCULL, 0x4B88CB7EF0F8735FULL, 
            0xA8B3086118F1C045ULL, 0x1A299EEA886A45E1ULL, 0xAC8E82F754625911ULL, 0x5598BA35AAE7532CULL, 
            0x9FE6F06D1D49FFB5ULL, 0x1958DAC496D942EBULL, 0x6CCAFCF3B14B9009ULL, 0x8AFE226AE5A124DCULL
        },
        {
            0xF1FDDF1A79C75434ULL, 0xD2E22F2EE51807DBULL, 0xB1679CF368B53C84ULL, 0x89D8FECB2CBAA87BULL, 
            0xD930B680BF98995FULL, 0xDC933D8A4579945CULL, 0x30272A06D98CABF2ULL, 0x05E108BB1AF38637ULL, 
            0x8DFB753B4D69EA3EULL, 0xCAC73B425608564AULL, 0x78B1EE3D3BDED8C1ULL, 0x0C37CFCF8B6EC0A0ULL, 
            0xBBC0214AC7FD293FULL, 0xF0EC49B44895F3B7ULL, 0x86CBD03A56F42466ULL, 0x588BE3521F97935DULL, 
            0x003FFB95ADEEBE5CULL, 0x7264B78DA062EEFCULL, 0xE3305BAC92DF54ECULL, 0xC30FF55EA1979EB1ULL, 
            0x457BFB5ED4503858ULL, 0x6F39D1933BFFDA3EULL, 0xA89044C8B9D3D570ULL, 0xAB83C4593C5D257DULL, 
            0x43717498E98A7740ULL, 0x7B480214CBCD17DBULL, 0x0288095E7D18E2DAULL, 0xE863E0E4CADC64F4ULL, 
            0x8ECC6F6070727253ULL, 0xAB629922A7F26D11ULL, 0x1B15CEA4D2A2C05EULL, 0xAFE7B3C6D7ADFCAFULL
        },
        {
            0x73C56E614106E9A0ULL, 0x7EB4FAD5C5B934D7ULL, 0x71D04267084F1628ULL, 0x510B27028DCF24FCULL, 
            0xFAC68CD24F28BDC5ULL, 0x360EFCF50E86A9A9ULL, 0xB23605B394140EBAULL, 0x3A3E78823BF4670EULL, 
            0x19A1A7BBA0A032ECULL, 0xEEF031D4523FA193ULL, 0xA73994ACC66C6C72ULL, 0xC925F630BF145185ULL, 
            0xF2CC0A687A1E8381ULL, 0x53B1B443465DC41AULL, 0x107B324E3EEE4023ULL, 0x8DFA63572681A4F3ULL, 
            0xA670C3552A5E2E1CULL, 0x9F8B3755108DDD85ULL, 0xE2FA96333F85782AULL, 0x6D28EC035A08FDFAULL, 
            0x96F765DAF1E1C637ULL, 0x6D005416A317EFBBULL, 0x8BAB1BEF3BE2C313ULL, 0xBA27B5AF3C1639F8ULL, 
            0x720E00FF7656330FULL, 0x76BE9E2278C7F6F4ULL, 0x009A4756DA80278DULL, 0x38605B814C270718ULL, 
            0xDBD01ED899EE23C5ULL, 0x1460FE55D2055AAEULL, 0xEF324B741948A10DULL, 0xFDCE9E9066628959ULL
        }
    },
    {
        {
            0xB3F14B55020B9E00ULL, 0x035678912CF3E474ULL, 0x4F2F2DE34D5CFAABULL, 0x570EFE2C5B70C839ULL, 
            0xB12639B3BDD8D720ULL, 0x8B1D305137AA427DULL, 0x9B634EBF85BE4657ULL, 0x383D61AA167289CCULL, 
            0x4C16C50FA4FF5845ULL, 0x5923726392C17590ULL, 0xD26CCB1E930D83C7ULL, 0xA137825786FE1554ULL, 
            0x9F49D800EB94385AULL, 0xA11F7BD967660792ULL, 0x649B8731E73EE587ULL, 0x4B9838C0414679E9ULL, 
            0xD2148D8677A42EBEULL, 0x7778954AFCA4D78CULL, 0x4EEBDF96FA9C6C70ULL, 0xB1B19550CC361BCDULL, 
            0xF34EA7153553E33BULL, 0xD4EFEDD267961B68ULL, 0x88371D8ACB4D9681ULL, 0xEAFC09ED4C14BDF4ULL, 
            0x265E7C982C1EE57AULL, 0x410E63D7960E99C3ULL, 0x1EAE04CC56B6EDF2ULL, 0xE70E26F3C3CF1E55ULL, 
            0x9243D1528363E1CFULL, 0x86BCA2D2B9DB34D9ULL, 0x7C9A2D3DB3FF3D20ULL, 0x5F17D0487D82CF12ULL
        },
        {
            0x0F5FC01A4BE9AFFEULL, 0xDE1562D3D5FB2697ULL, 0x900BCEF46036DE4AULL, 0x055FD0F5456C41EEULL, 
            0x23DCB0D226552525ULL, 0xB00E53C755639495ULL, 0x23C34388AE9E68BEULL, 0xDC462F23FC2427E0ULL, 
            0x9D8C60EE77D7FF5AULL, 0xEA0D7F3BEED4B9BDULL, 0x4056B9C6A291803DULL, 0x6C8C919FFAEB735DULL, 
            0x47554E6AE5428FC1ULL, 0x6A3C02CE0C44543FULL, 0x8ED4DB3D600289C6ULL, 0x34C2B46BA6710BA3ULL, 
            0x0F30EA00F2771DF5ULL, 0x12717507555A946FULL, 0xFF755F91609D24BCULL, 0x1F9B34FF68C10D33ULL, 
            0x45D33F3975EC0808ULL, 0x4DC72D94B1EA8A05ULL, 0x334AA13AF5088B2BULL, 0xC492C7670A118C14ULL, 
            0x02C53263BB695E87ULL, 0xCB0621A3D97EAA42ULL, 0x4A293A118331CD3DULL, 0xD45FABECA32EB17EULL, 
            0x435E9BD3758A64F3ULL, 0x7A8A5EAEAD91057CULL, 0x06A45740830EF106ULL, 0x106F3266990B90D4ULL
        },
        {
            0x4F97815609CAB38DULL, 0x642534278C6EF210ULL, 0xD293C41AAE103147ULL, 0xC489B4C3BFDDB6A3ULL, 
            0x2D5B4FE607EAC1A1ULL, 0x0AE5DC654FA543B2ULL, 0x57199DEC015DA331ULL, 0xC8A550D7725E71AAULL, 
            0x1756D50DE84FFD2CULL, 0x95EFF8A770B5662DULL, 0x784BEEB295D759F1ULL, 0xAD0D80D38B0517FDULL, 
            0x40C788CED7B15757ULL, 0x5AB705FC2DEB4B59ULL, 0xAF7E2E77BEAD4D86ULL, 0x37ED5DF50B265CF4ULL, 
            0x8AE7B446B78612B9ULL, 0x0E087759A35AEDC6ULL, 0x610C3DC52166E671ULL, 0x1B6B3F8050210E52ULL, 
            0x69B235E50D63387FULL, 0xC9C05C3193F248AAULL, 0x9C83CB5C41D2CA26ULL, 0xEAE955D96452011BULL, 
            0xBE6D4AEC2F56607FULL, 0x88EC89F15C221454ULL, 0x1BD994E1565CF7EEULL, 0x1D4F89255BEB24AFULL, 
            0x946934C7FD50260AULL, 0xA25906748206ACD4ULL, 0x6D14AE171D6868A7ULL, 0xC38B375D24AA4A0EULL
        },
        {
            0xD5DC65BF94C3B003ULL, 0xEF14789886817EFEULL, 0x87C90BFB3129B849ULL, 0x932C319FEB79CD77ULL, 
            0x94275312FE048FA5ULL, 0x50E353DAEDEBBEABULL, 0xE561D4F596C881ABULL, 0x63821B94572AB78BULL, 
            0xD30115E415691F56ULL, 0xFFBB4E0E7E131728ULL, 0xA09881AFA70C217DULL, 0xED5CD5F460031CB7ULL, 
            0x5B4C743FF35079ABULL, 0x80FCD67C60413EC9ULL, 0x42E27F1BFED03A35ULL, 0x75BF1815D961BE6AULL, 
            0x6941B5DE56871289ULL, 0x3BCD25D0DD1B57E5ULL, 0xC5BD2D2428521E32ULL, 0xA56C082CEF6ACFF4ULL, 
            0x1795BD526E93A745ULL, 0x647A69E6AAE809F2ULL, 0x60C326C81360A3B9ULL, 0x0BA96F1B39BB588FULL, 
            0x4A19607CCCDBAE31ULL, 0xDC8E033197701A84ULL, 0xC2E999F590FF9E92ULL, 0xF355FEE096FECC11ULL, 
            0x1A3A1B104A660533ULL, 0x8B5B9AB310E5C3F9ULL, 0x07023FB191ED90C8ULL, 0x4FA39F60A4EBAFBDULL
        },
        {
            0xA5F2388EE54E7F90ULL, 0xC6A5C41D3579988AULL, 0x7D7D3A5579B9B0B3ULL, 0x575308B96DE3C5CBULL, 
            0x446266A1619A4613ULL, 0x4FF978B358211116ULL, 0x231C3A3FC2FD1DF0ULL, 0xF1288396D6D8628CULL, 
            0xA3664D3C7C1A0FC9ULL, 0xA3C9A4244767474EULL, 0xB9CEDD2939A8933EULL, 0x7224D3829C0240AFULL, 
            0x90ADC583A7CEAFA4ULL, 0xE0DF3082C60A41AEULL, 0x462DE43005885FE8ULL, 0xB90DC0247B1FEAE3ULL, 
            0x6FD179DE759C0EDBULL, 0xE1585DB766A07D52ULL, 0x1FCAEDFADF7BCF6BULL, 0xB58BCA8F474E1F91ULL, 
            0xF7D7ED41983F41B5ULL, 0xE77093A015B03F3AULL, 0xB02D770CAA621A6BULL, 0xCA4ADDCC82432D61ULL, 
            0xA01284A21D4A7691ULL, 0x0D39A3EA8EF8881AULL, 0x1A664956D64C760CULL, 0x989B0957C56C1036ULL, 
            0x66345A1DEEB34A5CULL, 0x03744D08F3E291DBULL, 0x3CFC2D8C5CF5D765ULL, 0x82BD62E6B89AC6B1ULL
        },
        {
            0x97E7DB1663D66232ULL, 0x06511E4BC45C60F0ULL, 0xC54587CF03094EC4ULL, 0xF4D1FEEE701AF9C4ULL, 
            0x1D2BEC34EDDE83AEULL, 0x24CBF0AD64545B9EULL, 0x0203F6C00DDAD6FCULL, 0xACDCD449B80C8DD7ULL, 
            0x89824A469BC231B7ULL, 0xF34A308F08F05A74ULL, 0x142CC6F22CB24EA7ULL, 0x007964C7310687A2ULL, 
            0x5E326C949230FB90ULL, 0xF525F97F9C7D2D8DULL, 0x90F054215CD8CF79ULL, 0x969C9109714493C3ULL, 
            0x1D4A71A9F697403DULL, 0xD0DF2BDB796F1D6BULL, 0x38F1974D86518AFDULL, 0x20B1275AC8792E59ULL, 
            0x41FC891276439708ULL, 0x274BF322F0B00E38ULL, 0x97BD48C8EB5240ECULL, 0xEF5BDAE5C1D6B0A1ULL, 
            0xD3306370FDD59BEAULL, 0xA6B82F141F36DAC2ULL, 0x8F8BAD34241B5121ULL, 0x945B908E9A679807ULL, 
            0xFB467D773D36DFD5ULL, 0xED7EBC43DD9E22E1ULL, 0xA7073AFDAF52E0CEULL, 0x50123A10309E7437ULL
        }
    },
    {
        {
            0x785B150C0AE0A3DBULL, 0xA5CBC9400773786AULL, 0x34A1EE0326C673BBULL, 0xFE3C66C964684CC4ULL, 
            0x036C39BD59A23456ULL, 0x408B98FD9B1404E1ULL, 0x8F56EF8C4DEC5919ULL, 0x882475C1F6B714EAULL, 
            0xEEDCE99283D38BDEULL, 0x4865795E4D0236FAULL, 0x960633F2E47F90C3ULL, 0xE81123896CAB04A9ULL, 
            0x43655CF092E7BF13ULL, 0x4AA856B8713CD18AULL, 0x457F755B3FA2910BULL, 0x3E48CEC34913ED13ULL, 
            0xCDF3965384CE0413ULL, 0x3BDDF81BEA4A6CE4ULL, 0x1BB32C682AC1670AULL, 0x82C16DA83C2FF742ULL, 
            0x0AFE76EBB76B518CULL, 0x1767A91240CEEE58ULL, 0xBFED4194F4E22B44ULL, 0xC6F5C5DEB6EAE8CBULL, 
            0x4991E23D6C3B96B0ULL, 0x8CC10BB54555E01AULL, 0xF07F54B5A0183002ULL, 0xA9E79E6CDB10AE56ULL, 
            0x194EBE2BFE119F4FULL, 0xFB9312DA7C454EFDULL, 0x43A1881811382417ULL, 0x05F31AD95C6210EEULL
        },
        {
            0x264C633E50CC5FDAULL, 0x3E2F7B4A3519B88AULL, 0xF2D90AA6449D2BC5ULL, 0xD173B341AEB59793ULL, 
            0xEDA509FD29E177BBULL, 0xD00DB19E7E380D5BULL, 0x5A24CFEE631670DDULL, 0xD9F160A55BDB7A5BULL, 
            0x4994B5F4036ACD63ULL, 0x05A9BA8EED6956F3ULL, 0x9E36CC73FB496AC4ULL, 0x06D9678DD48B6E21ULL, 
            0xE8085C9B6AE9024DULL, 0xD777FDC449F5CF3CULL, 0xC9E1FC703CC50AC4ULL, 0x32A99EBE7A8FAAC0ULL, 
            0x39F82EC07B1D2C1AULL, 0xE3F96C9BAEBBFE4DULL, 0xF61FAB944C9DFB50ULL, 0x95C7DFA91CB0EC96ULL, 
            0x788B59E3AB50337FULL, 0x7272D50AEED2C6F3ULL, 0x56BD8C030E90B109ULL, 0x53229E6A42493DEFULL, 
            0x8428D4302191E1DFULL, 0x5B72B3D6748758DCULL, 0x42E4BFAE4A6AC30CULL, 0xB3994453F238B995ULL, 
            0xEF60FA50F68D40C1ULL, 0x53D96FD8A3404C7BULL, 0xC94C4857E7FD43BBULL, 0x08CAC56A4B8A73F8ULL
        },
        {
            0x3F2D3AC28E8B22AEULL, 0x8EB63EFAC1D974F6ULL, 0x21405FE608DB77FAULL, 0xFB2FA20D56DF1962ULL, 
            0xCC9FB6B59B4A87D5ULL, 0x20102B3AFF21E634ULL, 0x701CC4E5C5B29EEDULL, 0xE7C9470AD803BEE5ULL, 
            0xC104BEC2196580F9ULL, 0xF4A05BDB1F59F407ULL, 0x1A2189C886BBE488ULL, 0x8FAE548763E4D813ULL, 
            0xBEBC4A98CBE5E2E5ULL, 0x39D6738930E3CC28ULL, 0xCA3B4F60F1E2FA1BULL, 0x94CE5A4519B982BFULL, 
            0xEAF3DA1060BDA1DAULL, 0xDFBF1C7515274A47ULL, 0x902BEFA4B45A37C7ULL, 0x05C3C1E3785133BFULL, 
            0xBE7AB93450A6AE5FULL, 0x23178232D4730B07ULL, 0x299D1E67E5322899ULL, 0xADC636EA392D0ACFULL, 
            0xB84497BE1E93A207ULL, 0x3C3FE2BD4E11B69AULL, 0x1D3FD00A34A5D111ULL, 0x1F462668736FA5D8ULL, 
            0xA3B0C6A1986C3966ULL, 0xF6780BBC88EECED4ULL, 0x3A5A2509A61D2EEEULL, 0x9362FABEAD2BA654ULL
        },
        {
            0x0AD2F9C9D7D39351ULL, 0x8FB7F308E70F6A29ULL, 0x34E41FC9FE8DD43AULL, 0xC4E69E65B98D904EULL, 
            0x81AF303EDC168B2EULL, 0xB6E108686E048658ULL, 0x9F9B3FC42EED12E3ULL, 0x26DEB53BDE43937DULL, 
            0x59B040933DC523D4ULL, 0x4D90775C25A5DCFBULL, 0x4348EDEBF46D3306ULL, 0x5874218692BB1A45ULL, 
            0x342B305E3D1E9F6DULL, 0x47EE871E1F3174F3ULL, 0xAD86AD12F17C205BULL, 0x678207794F2E1AB2ULL, 
            0x5EED9E8F6EAA51B1ULL, 0xA8DF5E25193F8A61ULL, 0x77CAFB4C0EB60C43ULL, 0xC8AD82284FAB14FAULL, 
            0xB552469392A811E1ULL, 0x1975BD806EF83C8BULL, 0x75B5F026EF3FDA82ULL, 0x5D90D3A079AF47F9ULL, 
            0xFC84774F8823D692ULL, 0x56EFBC6371671B85ULL, 0x40F89E5F2C368E6CULL, 0xE8B2534510D83283ULL, 
            0x76DC16B2A839CA83ULL, 0x41E0DCE90871F8B5ULL, 0x1F26B125D659A953ULL, 0xF73E09DB11A4F590ULL
        },
        {
            0x1D2F0CF95AE3A0EBULL, 0x2456DAD6C278C2E0ULL, 0x2C2A7733D4C3B9F9ULL, 0x74709DA38CB51D9FULL, 
            0xF6EAC6006A921A98ULL, 0x7546252E5DCF2DD5ULL, 0x4162761408C37183ULL, 0xA4D09551457B6C8BULL, 
            0x436548EA2A6770E0ULL, 0xBA7120B619D8F2ECULL, 0x068918F11178803FULL, 0x964D38647D1FC863ULL, 
            0xA56222D58691E806ULL, 0xF7753D156870B9B6ULL, 0x10B130EC2A3250E1ULL, 0x462139AF68FFB642ULL, 
            0x9E62B4D8D2CA813CULL, 0xAD2674ABE632B210ULL, 0x77E86E7B7F4A4917ULL, 0xBD301E9F98D46214ULL, 
            0x58E38B1518C0B4DBULL, 0x4A22F54A0770E0FEULL, 0xC3437B4AE26C26CCULL, 0xA97AA83AFCDA84AFULL, 
            0xF768F89FEF276F73ULL, 0x55E354D7C7A3C775ULL, 0xC67339CD1B5704C7ULL, 0x2873BB243295D454ULL, 
            0x375AE0186F603145ULL, 0x2679C5788045D118ULL, 0x85909006401A2435ULL, 0xC07B1EE0AA2198A4ULL
        },
        {
            0x4B4AADC7735FE059ULL, 0x6186660D7D3BDE60ULL, 0xDD0C1D487674A558ULL, 0xB731C7B8B4A1D08AULL, 
            0x8DC1A07551300458ULL, 0x57B6D78210C8D1C8ULL, 0x61ED9ADB8B228FCEULL, 0x7BFE95787774C701ULL, 
            0x1AE91236C9A500E4ULL, 0x4F335038EE3DBCE4ULL, 0xE73E8DEF10003E8CULL, 0x795E39ED8396A68AULL, 
            0x747096C838D3A9B2ULL, 0x48E67B9984E64C42ULL, 0xE0781D1CB01133B2ULL, 0x01C9E9522D8E6AE8ULL, 
            0xC4C7601A3F166690ULL, 0x04BEC2725CD7097AULL, 0x636DA349057D7103ULL, 0x410EF8077AF7D027ULL, 
            0xB9541993C6BAE31DULL, 0x51348725F1327D47ULL, 0xEE8CE1775DDC6D34ULL, 0xB33FD8AC9BD55216ULL, 
            0x65060F0809EF4A50ULL, 0xAF77985D5646B551ULL, 0x630D560925EEEDBCULL, 0x6017A620E1BF7469ULL, 
            0xAECE97765706F110ULL, 0x11303BA8CC037935ULL, 0x3FDE292C5C0DBC72ULL, 0x400EEF2BDD6DD2B1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseEConstants = {
    0x488F5DAC12299B7FULL,
    0x4FE7A37A48FD291CULL,
    0xDF49E6B39C40355BULL,
    0x488F5DAC12299B7FULL,
    0x4FE7A37A48FD291CULL,
    0xDF49E6B39C40355BULL,
    0x71DDA1FA2FD21590ULL,
    0xA708CF873572FC06ULL,
    0x38,
    0x6C,
    0xBF,
    0x9F,
    0x2B,
    0x90,
    0x86,
    0x2B
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseFSalts = {
    {
        {
            0x2E46CB8D9CBA504CULL, 0x3DAFDA6EFF8E86F8ULL, 0x777C85C1BF53846DULL, 0x40CF7F34DF574CA2ULL, 
            0x48C3D63CD3809FF2ULL, 0xF8CEED138997BA10ULL, 0x5512AE97F1030EA9ULL, 0x6CF53F25E88F9ADAULL, 
            0xADCDE2D6F9048586ULL, 0xB17B466A9F1DF40AULL, 0x3ADF05030516302DULL, 0x69638206A5F32D79ULL, 
            0x5417C19EDCC4185DULL, 0x5ED6D6426327BE68ULL, 0x9A2DD82D11BA3B76ULL, 0xC91C7A4735B22968ULL, 
            0x90C1FFD712657A26ULL, 0x006B9EE0573DA8F1ULL, 0xDBD5552D211C3C44ULL, 0xCA7510E4F03BFF6CULL, 
            0x1568EC4587E6C7D8ULL, 0x8735F19488B6CFF1ULL, 0x068187AD700FABE2ULL, 0x38400DDE2F316F9BULL, 
            0xE58573CBD44DD7E8ULL, 0xD0F6B639ED6EFBD0ULL, 0x6C915AC5CB3184AFULL, 0x4F89899059459DA9ULL, 
            0x8BD7DE2AE96464A3ULL, 0x72A541FD7D536AF2ULL, 0xC0BB5B1EF4A2EC9DULL, 0x5DF955FBA5C60E8FULL
        },
        {
            0x204ACD5C0C8535CEULL, 0xBC7AAEFFA3FECD84ULL, 0x16A83C537F66640DULL, 0x028080150EBBC554ULL, 
            0x1C4B34DADAC2D565ULL, 0x7254FE9E7EB6CD12ULL, 0x075D6AE6C8E2A7DFULL, 0xAAF9338ACE09F439ULL, 
            0xD63A801F1659049EULL, 0x312E12861125928EULL, 0x2EB515757DB1A91CULL, 0x884D289413841AE8ULL, 
            0x4F77A3A23FD92344ULL, 0x46348DC997D9059EULL, 0x2AF32D7287A08993ULL, 0xB05F5B6660BBF142ULL, 
            0x7A88B0D75B9D5427ULL, 0xCDFFFE42A4C0E0CFULL, 0xF770B912193EE597ULL, 0x08530126908C000DULL, 
            0xA341FBC3032F8A57ULL, 0x4D476224A0E31B7DULL, 0xF7D8EBF41157B1CDULL, 0x0DEC757A27B2E800ULL, 
            0xF9ECF03FC5F3F450ULL, 0xBDBCEB13DD23FA3EULL, 0xC55E9957123C1F5CULL, 0x737DEA5FEBDCA0A3ULL, 
            0x1FE1FAB2DE4A4CC3ULL, 0x5E7304536935C4F0ULL, 0x4C94BACA5F02D56BULL, 0xB526A5613B5B0F60ULL
        },
        {
            0xA28F0E2DEE892A15ULL, 0x8724A1065D5EDC84ULL, 0xA894EB17BB6D1A98ULL, 0x6A6881B13C0070B0ULL, 
            0xF265B03515FC3CDCULL, 0xBB34B3AC902917DBULL, 0xAA12A7D668B363ABULL, 0x4D996975F069C69EULL, 
            0x1D6EE3885ED65763ULL, 0xABC93617AB1FD843ULL, 0x4703CEB4CF685D50ULL, 0xB73CC48E75A8B0A8ULL, 
            0xA8F6F7102A2C2F00ULL, 0x1DCC52343828B3D2ULL, 0x738D5BE84C230612ULL, 0x74693BF0D597D843ULL, 
            0xFB90946DA82029BAULL, 0xDAE2C998682ED5ADULL, 0x0BB397ECF703ED0CULL, 0xF146608E225A5A3BULL, 
            0x0CF45008FEF996AEULL, 0xDE9953CAFEDEA47EULL, 0xD5EF643E817377E8ULL, 0x641A8CF986A3A712ULL, 
            0xEDE6984D8AEA483FULL, 0x8C82B1DC15572F1BULL, 0xFB3A0CD10B36C6FBULL, 0x9164C6BDAAB310A5ULL, 
            0xF058CCBA593776B3ULL, 0x9C3CF070037759D1ULL, 0x19C3C551327894FCULL, 0x6B3F9ECD894CCB93ULL
        },
        {
            0x05890A3FBE39DA82ULL, 0x17C5A0E8B4219487ULL, 0x3FADE672B04F2BA3ULL, 0x2448B2D0608A3F6FULL, 
            0x5E0C6320AE19B697ULL, 0xBB4797654B8B646FULL, 0x62954BB10803EB29ULL, 0xCE07190AC7135C42ULL, 
            0xDF190722C1536283ULL, 0x07BA44AD889EEE0CULL, 0xBF22407E7355664FULL, 0x0287B3816D901DB8ULL, 
            0x5F611D8E06C8F400ULL, 0xF4AA55D68EEB5616ULL, 0xE314F624FA66C483ULL, 0x6274B4AB50F8047EULL, 
            0xC2887968CFD4C3F6ULL, 0xA520F6C9772E435BULL, 0x28DE0FCC1E89B9DFULL, 0x3F2856B0FD54A86EULL, 
            0xDE016544236376F0ULL, 0x5BA3E68A442F7FDCULL, 0xF104C601857B1F24ULL, 0x836E7095255D3D6CULL, 
            0xA4D47A6BD62AE047ULL, 0xA0A6AB0BBE04A8B3ULL, 0x188A5BE13754517BULL, 0xDA4161C0E4524695ULL, 
            0x08062EE55E9C2E36ULL, 0x2C9A330720C4C94BULL, 0xEED310A99D18FAA6ULL, 0xA1BD5D248FE373C0ULL
        },
        {
            0x0FAC52882E00C453ULL, 0x256C3DCD840656B3ULL, 0xE7BEA70E2801713CULL, 0xEC9BE97401BD4332ULL, 
            0xCFB06BF7FFDC022BULL, 0x71AFF737F81E1E34ULL, 0x11969885F8D3BF29ULL, 0xD7E45F940F2BBAD9ULL, 
            0x2D356C87B20484A8ULL, 0xA5790950B32CF8C4ULL, 0x029AC0BACB872A66ULL, 0x376FDC81270AC165ULL, 
            0x52085F5FDAC144F4ULL, 0xE980CF0B405061B1ULL, 0xC147CD7FAE5DE1C3ULL, 0x8B24F377603ADB43ULL, 
            0xDA69B7F3DF7FCA6BULL, 0x24608CEBD355141BULL, 0x41894C02DE5F7BE3ULL, 0xF5874C70B84561ABULL, 
            0xAC81BB0056919E16ULL, 0x9882B46FBB93F0EBULL, 0xED25EF45896713C3ULL, 0x4446636EE2B5DF9DULL, 
            0xFCAB744C3936CE7BULL, 0x5ED2436376C4679FULL, 0x416904AAA4BD5F23ULL, 0x5E655EBE95D53713ULL, 
            0xD7CF9272CC3F604BULL, 0x188D3F3832950E30ULL, 0x25BB6DFA617653CEULL, 0xF0EE9D25705A4740ULL
        },
        {
            0x8F1F732DBC35842CULL, 0xEC4B6219F9A5296BULL, 0xB6D5074DDBEC141FULL, 0xED4D31E5657F1A24ULL, 
            0x40202BECECFE0E8BULL, 0x6B3AA174E6BBA4CFULL, 0x35592B6F243E6946ULL, 0x2E6FAD754B8AC44BULL, 
            0x93C70B15EDDF0942ULL, 0x434A4D709FE8E7E4ULL, 0x55382012095AEC9AULL, 0x0D63F468C25C5858ULL, 
            0xA21FB0966FA8844FULL, 0xF0A4ED9F616A0511ULL, 0xD8900BF4AD2CBCDBULL, 0xC795BCA960521219ULL, 
            0x91EFEA8FCC2FEE4CULL, 0xDCFA1252B6F7C710ULL, 0x23EF3C8E3A5997AAULL, 0x7CBCA8C13C1C62EDULL, 
            0xDF09B5F12D4C213FULL, 0xA7A9A65CDB0C6622ULL, 0xCB0C9F76F5787A33ULL, 0x99FD594C03632D6FULL, 
            0xC6F382C4D8E860B5ULL, 0x8F1E7CE4036413E1ULL, 0xAD8AF5A74FD01984ULL, 0xCEFADFB1900A5FDFULL, 
            0x8F1B489CA41E7753ULL, 0xA9048714BE1B0802ULL, 0x835DF045842A91D3ULL, 0x193D9C288D12EDA5ULL
        }
    },
    {
        {
            0x159404421C0B231CULL, 0x5D70CFC086D5DBC6ULL, 0x1FC6985850CCE3DAULL, 0x0725AD6193A6B7D9ULL, 
            0xED908E109FA1739CULL, 0xA08D9F655330D5F8ULL, 0x839DAE710C7CCCF3ULL, 0x88ACF89FD7BD8647ULL, 
            0x0BDEF2C99BDA4BB4ULL, 0x823685F84AC7CA94ULL, 0x936419D2FB18EA34ULL, 0x3F06BD7846CCA66CULL, 
            0x7A2E8D1E8E4363ACULL, 0x6DE143D65DBA2A15ULL, 0x7B0D559208FECEC9ULL, 0xAD179BC33C32DFCFULL, 
            0x1D0A414BAB0A826BULL, 0xF1C53B0B6C40A6E8ULL, 0xE7B84D542649ACF8ULL, 0xA8059107B6F7C250ULL, 
            0xCB6B8ACD5301E410ULL, 0x9DDC0F974DF5BB21ULL, 0xFB667B5FE8A63C06ULL, 0x0A96847EA1519D56ULL, 
            0x73A18D4771ED9B9AULL, 0x417993D858E7BCC0ULL, 0x56A8E80DA5BC631EULL, 0xA300EEFE4CC42C1AULL, 
            0xFCC701CFBA4A61E9ULL, 0x7409235FFA4916ADULL, 0x1A521888BE6B06F4ULL, 0x4F637D6D7098BED0ULL
        },
        {
            0x58FD21E9A2B72651ULL, 0xAFC8048C215A64DAULL, 0x48E2557B35CD2DA7ULL, 0x07F79F1C30555EBDULL, 
            0x46E16062F55DDA62ULL, 0xDE334C80969CF35BULL, 0x69D28FECC690B2E6ULL, 0x52EF49F623DB80E8ULL, 
            0x61E2E7DCEDDAABDEULL, 0x4E9A3F9763F09917ULL, 0xB3A1A83363A66355ULL, 0x3C2AC51B7EF39E34ULL, 
            0x94066A9D0F830295ULL, 0xA4ADA84E8DD5A7CFULL, 0x665EC01E75B0D20AULL, 0x1BD86DC4A88A2032ULL, 
            0xE9C06FB0DDB48B39ULL, 0x0F9900BE35A83EACULL, 0xC16D8A41217C2CCFULL, 0xA5615EF34A880C46ULL, 
            0x88B42A0D0771BC76ULL, 0x91C4AB3A300D3E9CULL, 0x109D3EC0A84E7EAEULL, 0xB1918B36CC54F498ULL, 
            0x863E2C1C9F60FA15ULL, 0x91FD0C2933A18C9CULL, 0x3180B02592E3A4D9ULL, 0x8A3CEC87966467ECULL, 
            0xB984725A0DF21AB9ULL, 0xD85AFC0996EE71E3ULL, 0x4CAB4AD5C4B00E96ULL, 0x7392C96666339D2BULL
        },
        {
            0xA9A97DACD8749F72ULL, 0xB6B1CD82E7B2CAFFULL, 0xBD179B9A3732A8B2ULL, 0x708009496985255DULL, 
            0xB0188C446742A1FFULL, 0x34793EB427CF8369ULL, 0xD29DA41E3958864EULL, 0x1B7541E8F5841AADULL, 
            0x74E758A03D322869ULL, 0xEC178EEA6ED9D6D6ULL, 0xC51478D81DA4F931ULL, 0x8FAA0E2DC1128611ULL, 
            0x703DE0C22D58F528ULL, 0x39D507E26F0552A6ULL, 0x4CC53D4EFDD5B559ULL, 0x0CF60AD00E632783ULL, 
            0x70170A4D2588F32EULL, 0xAC5AE6CB4732715EULL, 0xEC8E1BCC17533908ULL, 0x4BFF67481E5159E0ULL, 
            0x397A0DB3E31B024DULL, 0x0FE4687E55B53226ULL, 0x37C9F9E76861620DULL, 0xF9021CEBDA2467D3ULL, 
            0x7153EB2578C32D1DULL, 0x368AB09318E46C8CULL, 0x844D4B7A993B5A20ULL, 0x83B30DDEA77F4D72ULL, 
            0xB509957D69D33E51ULL, 0xDE148FDFD8EDBBD0ULL, 0x0FBDC05D9D33C99BULL, 0x60223003F683D7D5ULL
        },
        {
            0x345EC1DC1CB6E383ULL, 0x5C6345A5DF08DFDCULL, 0xA7640B5E9BE09CBBULL, 0xEACE0821F26D67AEULL, 
            0xEA10907ED9357513ULL, 0x01F6EEAD6F36B4E0ULL, 0x62D8E5B7212D429DULL, 0x43A7961596FE8B79ULL, 
            0xBBDC4A9BC6D08EE6ULL, 0x596DBD9543A6F2E9ULL, 0xCFD9CEF4742D12B4ULL, 0xBAF255C6E4FBB099ULL, 
            0x06850C1F38278AF0ULL, 0x3BAAFC807440F0CBULL, 0x571E48372CD69440ULL, 0xF5C9A3D331178BBEULL, 
            0xBCAB3DE6C69A1127ULL, 0x305CDD0EA5067D72ULL, 0xA066E95FC27A3E22ULL, 0x06753C6CA047A25EULL, 
            0xC45E623987BAD4FEULL, 0x001D98AA4EEAA449ULL, 0xAFD34256AEFBA24FULL, 0x9AC1DD45DB94E2A2ULL, 
            0x6F1C0D6A0A56680EULL, 0xE47B3CDC82F34DE7ULL, 0x373B393EAC093ECDULL, 0x5C4D7D70D738FD40ULL, 
            0x66A8C7A88745359DULL, 0x8AFAE040B4080867ULL, 0x8069EA2A5AFC4F93ULL, 0x848D358A500BB08AULL
        },
        {
            0x88D97FA7D1A559C5ULL, 0x7097FE4A9886F479ULL, 0xEF0CBBFB4DB73703ULL, 0x68CFE709357816AAULL, 
            0x42470912CA57E9B7ULL, 0xD2AD9B5AE92BED24ULL, 0x087BC3B6086A99F3ULL, 0x8029B290185417C7ULL, 
            0x703501FB5022F482ULL, 0x7F1973FD4A3F3CABULL, 0x78A0B291F155089FULL, 0x3776F0CA380EC5B6ULL, 
            0xF33B29844581D602ULL, 0x4BA30D295F49E5CEULL, 0xAA499303E48F814DULL, 0xD48521FF3719C39CULL, 
            0xAD17CFFDD9209E95ULL, 0x4E354E829E3FDFCAULL, 0xD04C02D4FB5088CFULL, 0xBE8C337464959A01ULL, 
            0x8651A30301985605ULL, 0x085CB1A81C66AF04ULL, 0x64DA2808E4A61DCBULL, 0xD39BC4855EED0E89ULL, 
            0x9F17D16C3CDF77E7ULL, 0x65DB385DF0EF4BEEULL, 0x4822263492C2EB5FULL, 0xA541C48AE5D31C62ULL, 
            0x0D2F1443B2D887B8ULL, 0x77C6EFC6B5CE5EF6ULL, 0x948E36FDBF4E0C9FULL, 0xD78E53281ABC88C1ULL
        },
        {
            0xD9F0E5D8F4951EDEULL, 0x3EA43BC2D4E95579ULL, 0x5DE3C48623CC719BULL, 0x3D78482A4AA4BC8CULL, 
            0xF13ABEC5E5A113A4ULL, 0xD887D21C8CAFD45AULL, 0x88A79E71DE20BF8EULL, 0x7E9B6687D24ECDF5ULL, 
            0xFCB03107DD52BA1CULL, 0xB6386AC800AE7254ULL, 0x97DA5BEF1CEC7008ULL, 0xA542118B6ACA6DACULL, 
            0x72E4B017BC7357A5ULL, 0xF96A330248FCB8CDULL, 0x4C6A7ED660636F37ULL, 0x6FB8F04263100DB7ULL, 
            0x8C92551CB880EA69ULL, 0xDC69C71D3618FD3DULL, 0x2B2A744B44297BA0ULL, 0x905D04103D7FA426ULL, 
            0xBA0D144954472860ULL, 0x180E905E633E5D25ULL, 0xE73A9C0F7066513AULL, 0x1C613143485A638AULL, 
            0x8BB272E6C3AB7D3AULL, 0x0C95B41CA63384B6ULL, 0xD0B54DC6BD26623CULL, 0x88F67478E436FD74ULL, 
            0x23A836D58E8136C6ULL, 0xD57188C32FD819A0ULL, 0x4905D8703A7F09C1ULL, 0x06AC174FA9FB9629ULL
        }
    },
    {
        {
            0x6684A021262F9C74ULL, 0xEF3D2BC9BC954E99ULL, 0xB8000C48E6457C3CULL, 0xE66A0DE04B6499EDULL, 
            0x43B2D1D7B0806896ULL, 0x1D3DEB0063AF397BULL, 0xF8B7C7C0CFB73F5FULL, 0x9A21239F9E6A9D5BULL, 
            0x575482072BA0BB96ULL, 0x014FC095645A21FDULL, 0x8CF638B80306C3ABULL, 0x2972E1060C085EC2ULL, 
            0xCFA2EC21F3D37675ULL, 0x46EA85E562A4EE02ULL, 0x8951C0D14F81A3E7ULL, 0x6FEAA3D1FD58436AULL, 
            0x415ACB929F11DC04ULL, 0x670AFC8A2A84419EULL, 0x9511159FA5FCC3EDULL, 0xBC226892EAACB2E9ULL, 
            0xE0509ECE8BF74DB2ULL, 0x0386D8D1B2FC4969ULL, 0x2EBE4B67159E8AEBULL, 0x9A72B7E5F76C026CULL, 
            0x1642EBBD3E9A3427ULL, 0xE10AE6C3502222DBULL, 0x61E9E1F387998A98ULL, 0x97A3348497411A9EULL, 
            0x2D10A303EF89CA65ULL, 0x45ADC4B91A7F9EE2ULL, 0xB5B3A30E492343A4ULL, 0xE6BF2F3EA9CC168FULL
        },
        {
            0xFDF2C1E2087ECC87ULL, 0x53C7D644F245C845ULL, 0x3F7FD1DE967DD1FDULL, 0xCF3823D59DC1E7FAULL, 
            0x6743FF1841C39C25ULL, 0x2DEF09438F2F7667ULL, 0xE2A96C910029EC30ULL, 0xA802FE1427E78D77ULL, 
            0x5326425AACE2D429ULL, 0x383A653DEE0689A4ULL, 0x6F06D6FA92E61F8FULL, 0x1B7D5A45116CA126ULL, 
            0x6E98C9FE61283C17ULL, 0x93A4C1DE45AEE67FULL, 0x20109C3CA7B49E9CULL, 0xE3869E1BCE09E68FULL, 
            0x436C4EAAE1F8F4A7ULL, 0xC21726C5D54E29B9ULL, 0x674B42E5978173C5ULL, 0xE73643D4A8966928ULL, 
            0x485C968B41F869BFULL, 0xDF6DE9648EC6272BULL, 0x6BDBDCF4F8930E25ULL, 0x4257BD94ED47A7F4ULL, 
            0x18DB37DB31994757ULL, 0x2CA63DB11FEB5732ULL, 0x442B8C9E0F042383ULL, 0x9A5C532B689ECA84ULL, 
            0x1C229CDA6C9555E5ULL, 0x82C9945219A558BFULL, 0x44111C027355E96DULL, 0xCB8B9C69569A60F6ULL
        },
        {
            0xCE9CC6D3910C3B9BULL, 0x5C1653647A0CE4BFULL, 0xAC1C3A754CF19391ULL, 0x47D508CEF3DE1FBBULL, 
            0xFBD78FF78BD4E8DDULL, 0x9AE4B3BE0A33096FULL, 0xB9B516F6DB681E02ULL, 0xAFB0C9F0AA4A6421ULL, 
            0xAA0A61374CC891E9ULL, 0xDEC0823213276827ULL, 0xCA1F958488025D4FULL, 0x87E9B8048A144B93ULL, 
            0xE20D82CC8039ABFCULL, 0xF4928B86B7BBF5F9ULL, 0x63F25ABD4592CF0EULL, 0xBEE8B9B3F6DFEAB9ULL, 
            0xE6C5CEF0E68D9686ULL, 0x37CF19E35D541F4FULL, 0xCB81AA88B078EC0EULL, 0xD9872405252CB84EULL, 
            0x72E27E4FFDEF4AC6ULL, 0x5229E911EF3122BDULL, 0xB0B627BBEF48BCCDULL, 0x4259FBADED87C908ULL, 
            0xA2E439787F335DB4ULL, 0x6046F7C7C87B7A90ULL, 0xF369D1DA7F66084EULL, 0x524EC0DF4AFC4507ULL, 
            0xF4745D639ADBC3FBULL, 0xEA832997304B97DCULL, 0x2CCD087929831001ULL, 0x578DCBEBB14F230FULL
        },
        {
            0x1F913C111BD699CAULL, 0x1DBB33848757A7B9ULL, 0xF0FB09090CA34C52ULL, 0xA417DBB2B18A2E6DULL, 
            0x68B060F0911E7F81ULL, 0x5751D21E9BCF7E25ULL, 0xB930298E05DA2499ULL, 0x476A1EB44759062EULL, 
            0x8C856DEB9FFAF784ULL, 0xD721C63FE4F1A9BAULL, 0x1CCACEE48E5F7825ULL, 0xCFA30932666B6C8DULL, 
            0x75841CEDB5640C9FULL, 0xE275A92D72F976D4ULL, 0xC3B92917233E4F1EULL, 0xD6B4BAF54A314718ULL, 
            0xF326BB9B91A5DCAAULL, 0xB38CF7E1A66EDF74ULL, 0xFAB732D930D50817ULL, 0x62EF02FB8117083CULL, 
            0x678A6858F38BDB21ULL, 0xCABF517B82971ABAULL, 0xFE28A53D002C0D14ULL, 0x1C3065DBBE70376CULL, 
            0xCE5E89409BE0CADCULL, 0xAAB5B92BFB102A8FULL, 0x64EE0E6AC68DABC4ULL, 0x54A2FCF03797D721ULL, 
            0x330E18C1942B7176ULL, 0x94AD8182E4068F3EULL, 0x66D8497117F654AEULL, 0x8FE050CA66B4D110ULL
        },
        {
            0x65892A99EF8D5EE3ULL, 0x0975A309C6CEF610ULL, 0x63F48E16984F584DULL, 0x090DBDCBF2B64F8FULL, 
            0x9D152896CEA2DD9BULL, 0xCF866B7ADF798225ULL, 0x9A765D7C01AA3125ULL, 0x78B8E77CCDAFECC5ULL, 
            0xB8312DC53179B86EULL, 0x2A006DF89C9B68ACULL, 0x31B4994DA554E250ULL, 0xFD8F12B348C6643FULL, 
            0x66F61AFF636B28C2ULL, 0xCC8982A24FC6C7E9ULL, 0x3B7766712CA9DCF7ULL, 0xC88D31177B4645B0ULL, 
            0x13FC93E7B39AD7ACULL, 0xAA2D3B3DF9D95358ULL, 0xF3D521C4371218C2ULL, 0x4B907051C143D3CCULL, 
            0xB81ACC683B114C31ULL, 0x75E5D2BC397DFD77ULL, 0xE1B38E0E29867BB0ULL, 0xD478057DDBA8D6F3ULL, 
            0xE5BB2FE2D3DF2441ULL, 0x7994E4AE948103EDULL, 0x6CCE24B915D2CB33ULL, 0xAE42D0A854D12E51ULL, 
            0xD9945178766C3150ULL, 0x02310BDCE396D48EULL, 0xAF4B78504F9C7B09ULL, 0xBBCBB173C6A32CD5ULL
        },
        {
            0xE5D499C02A0BA01FULL, 0x10DEACB30EE83654ULL, 0xF1249255C9E6414EULL, 0x741C40E97C1BAA55ULL, 
            0x01CA87BC37E29ACAULL, 0xFBF1E7A2C564124FULL, 0xBCAD6D1CFA1B4E35ULL, 0x7D3CF60B8A90E4F7ULL, 
            0x5E8B360D5D5EEC57ULL, 0x9FCCC39ABFEF8019ULL, 0xE0E104278BE0FF94ULL, 0xFA9C3E3F33FB3F4BULL, 
            0x0E2E785202814EB9ULL, 0x5FDDABD6E72FA554ULL, 0xDB40232E00451436ULL, 0x17BF2F2B03A740B9ULL, 
            0x464A2820814E63A6ULL, 0x6DAB833344B5B942ULL, 0x49DD03808F80691EULL, 0xDEDEE08F0B697EF9ULL, 
            0x1A76570FB6735B21ULL, 0x46642ED7E08AF9D1ULL, 0xB323568CA109D5F0ULL, 0xF608364BAAB518B5ULL, 
            0x090BCD3D601BFC72ULL, 0x87628303DAC890C4ULL, 0xAD6DFB5CF6F5E363ULL, 0x3EE9C4216439BEA1ULL, 
            0x8B05865FCB8B0548ULL, 0xA9AE0B1C895B81F5ULL, 0xD43D8D4EAD823534ULL, 0x490F32BF7A82AC2DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseFConstants = {
    0x113059A97AE4BA82ULL,
    0x389BB183A387D037ULL,
    0xE89186C35F7CB98AULL,
    0x113059A97AE4BA82ULL,
    0x389BB183A387D037ULL,
    0xE89186C35F7CB98AULL,
    0x4BBB4714F4CF601AULL,
    0x1D4C987992D9329FULL,
    0xCE,
    0xF6,
    0x38,
    0x58,
    0x4D,
    0xFC,
    0xE4,
    0x5D
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseGSalts = {
    {
        {
            0x0452970793D83B10ULL, 0x5264E53AA8A0CB4DULL, 0x8276513E74FACBDFULL, 0xAD06D6AC12F7ED73ULL, 
            0x6F3B934EE0CBE706ULL, 0x705476F41E05DE51ULL, 0x8990E12D046CE93EULL, 0x2D71C94C8EB0B1CCULL, 
            0x626E5E807AF437D4ULL, 0x17B1C898B61F3BC2ULL, 0x5FB9EA342E217B08ULL, 0x7525A4FEE771E9CAULL, 
            0x7D5A632AFCDAC4CBULL, 0x60CDA4CAF044F7C7ULL, 0x97DC626E3846338BULL, 0x5867BE656838CE27ULL, 
            0x35ABE213B65BAAC6ULL, 0xB90E83C8DBC7A5EAULL, 0x2FB5260F6E6778EBULL, 0x45E3A8DBE0042ED4ULL, 
            0x6CCBE5C315C5970AULL, 0xF26B3A86397BA8FBULL, 0x0F21B8DFED0640D7ULL, 0xEC5825030653A9B6ULL, 
            0x5F7177136D6BDA09ULL, 0xCE00A29B170B10D9ULL, 0x4B81D9F30F8AA050ULL, 0xE653FC9562BCEF25ULL, 
            0xA1D32DEFCF3C8052ULL, 0x7937876B7930C585ULL, 0xCFE3E3B5357C19E2ULL, 0xBDC1270B9859C0D0ULL
        },
        {
            0x74CA9C7DA05BD86DULL, 0x2F36FC6946D6F7DEULL, 0x1DFBA88D7B520D02ULL, 0x3513904A2888A643ULL, 
            0x8CF4F3E296D90D52ULL, 0xC0AFC1B84B1718F7ULL, 0x0B88E54DBF5C8B25ULL, 0x30605CDF1D28C194ULL, 
            0xB0F60F271BC9C6B3ULL, 0x98A3273BAAED1FC2ULL, 0xAC4DBECFE0C5CBC6ULL, 0xAF55F08DB9138F50ULL, 
            0xCFD001F278155F2EULL, 0xF6877084BF97AC0EULL, 0xD2E163A7FDAE9FF1ULL, 0x836EC0E1E08BD0B9ULL, 
            0x95F65A6FB2D87173ULL, 0xC67043365F3A61E5ULL, 0x42F8BE1AAD09C1DFULL, 0x0E62C92E1931802CULL, 
            0x7664C3BC3A9D3445ULL, 0x74FB4FAECCDA20B2ULL, 0x5C83F550C10FE282ULL, 0x0F656294AC8EBD8FULL, 
            0x6E256E37B7ABB792ULL, 0xA9DA26459E8FF1ADULL, 0x37DFBB1463AB5674ULL, 0xD18FF793E998E472ULL, 
            0xC3D34C4D614BF2A6ULL, 0xAFE898A4E190AE30ULL, 0x9E39028FC6476E0FULL, 0x07B1E4662A96396FULL
        },
        {
            0x79BBF6E791A24DE1ULL, 0xF3E97E3B8219CE74ULL, 0xAFD29B0DCCDA3F60ULL, 0x2EDB2605EA98D3DAULL, 
            0xDE84D78D22B68746ULL, 0x3A9E1DAD4764FEDBULL, 0x0DEBD535B9F77FD0ULL, 0xAA1FF8A6E60C6838ULL, 
            0xDF54A61275244D81ULL, 0x5286943518F57DA4ULL, 0x03EDEFB671FD7F33ULL, 0x636FECD6B192298FULL, 
            0xD7C0DEB9FFA102F0ULL, 0x023F0F83BA573C92ULL, 0x26B5B942C9020FE6ULL, 0xB6D64AEA8F30052AULL, 
            0x3862AE00B8B44C96ULL, 0xC0860018BCAD7804ULL, 0x6EF7BBA621BBFFFEULL, 0x5D978AC8247663C7ULL, 
            0xBD9B4CCD80A9BF3EULL, 0x142F3BA83080B1EFULL, 0x30A68A490C1F32CEULL, 0x27D1AE06DDE83F2AULL, 
            0x8DFCDA3A37235516ULL, 0x2D3284DF7170CC51ULL, 0x71A75FB257FD7FF5ULL, 0x557F005437D08C41ULL, 
            0x4A7F3A524A88DB29ULL, 0xCDBFA11B66B4140AULL, 0x3935F075A423A617ULL, 0xB528768AD5D6AC55ULL
        },
        {
            0x0C9872160F0BFA30ULL, 0x1C76964032D35233ULL, 0xB6383725FF8EA39DULL, 0x7823FD93A0DE9734ULL, 
            0x8C58D0EAB4101D4DULL, 0xC456AF5E09173E10ULL, 0xBD7DE5F850CD8233ULL, 0x115E06A3AD2033C3ULL, 
            0x23736DD6272540F1ULL, 0xC3987D7BD1A419C9ULL, 0x59BA8984B9182465ULL, 0xBDAF893B0C0F748FULL, 
            0xAD219A06A3BFD882ULL, 0xC3CE1B758C3F94D6ULL, 0x11B87127B42C0B8CULL, 0xAF067B9C4950689EULL, 
            0x07B8F4A044A48C3CULL, 0xC333603291FC8AC3ULL, 0xA68DB97684244ECAULL, 0x9684AA8001DEE2B8ULL, 
            0x20D20E3B26CD4E80ULL, 0xF56F69559F10C31FULL, 0x966ED8207F25E6A1ULL, 0x91392EA648B93B5FULL, 
            0xA9F9979A5DE48C54ULL, 0xFDC2C886D71AE782ULL, 0x4BCA544E159CF54AULL, 0x31D93C8B2201CC48ULL, 
            0x32BA2004A7C52892ULL, 0x7A73E3C7949A219EULL, 0x02630856F1C73634ULL, 0xDB51DEA678436ED0ULL
        },
        {
            0x21B9F35666DF35CEULL, 0x764BED6218D22470ULL, 0xFA29F3CBB3D93DD9ULL, 0x28C3E3562726AE9FULL, 
            0xC820532BED63FFD6ULL, 0x172F7244FBCD45AFULL, 0x0B689BCB96B26319ULL, 0xD62B1E47A43A3657ULL, 
            0x5295DEBD2FD26ADEULL, 0x150AE189B85C4895ULL, 0x378014D0F246DAF5ULL, 0xF87ACED60FAA69EDULL, 
            0xB009DB37621D07E7ULL, 0x6C77E5D3EBF315E2ULL, 0x8CE9C8A9EEB120B3ULL, 0xC5B8ED61A5D3DBB0ULL, 
            0xCE15A9BFA70E0356ULL, 0x4F20B1BFB1F91FE1ULL, 0xEE180DDB66E36668ULL, 0x0008C2876F41FE90ULL, 
            0x0D626D6D795C308BULL, 0xCFFFAF6D1D7A721EULL, 0xC65F06C89C513D0CULL, 0x97130FB8B2D3BA6EULL, 
            0x1E73FA9BB1FA9F40ULL, 0x22DE1F47D00529EFULL, 0xE8E6F7CF34DC5844ULL, 0xF121EC7DF9AF6A5AULL, 
            0xC1F85B105B894BDFULL, 0x8585DF84C6A8C79DULL, 0x3F097F2E88350D98ULL, 0xB222C076E8AC12CEULL
        },
        {
            0xCA223B821A6839B2ULL, 0x47CBF8F586E75064ULL, 0x990EAA57E3B1C19BULL, 0xC6DEA1DD56066588ULL, 
            0x6622E9CC16015EE9ULL, 0x4535B98CB39A4232ULL, 0x58A62A79CA000100ULL, 0xCAEAEF9390FF360FULL, 
            0xADD8AFAA3DE69095ULL, 0x8F15E0DFB284A5BFULL, 0x9F74C983E9D7533CULL, 0xB58163CED79CF0BFULL, 
            0x281E3B9805F3100EULL, 0x376A9909D9AC4B2FULL, 0x0E45DADAF618978FULL, 0x5AAE3B59E1F3F237ULL, 
            0x670187770B9A9798ULL, 0x1355465A52BD3CCAULL, 0x9D43AB5F8BCD8ED0ULL, 0x81FCB2C02CCB0F00ULL, 
            0x58AF65B91B80B249ULL, 0x07B9FB57F008FFBCULL, 0x0870B961E29D8D85ULL, 0x2A3E002A8A65EFFCULL, 
            0xC5145B05DC5E10E5ULL, 0xF14ACF43C1E39D80ULL, 0x239DF427019BE56AULL, 0x56B419783DBFDF4BULL, 
            0xA6EBABE58330106AULL, 0x2C4E8EE2C70A6ED9ULL, 0xF14369E61600BD67ULL, 0x915E1B417623B812ULL
        }
    },
    {
        {
            0xCC08498E3F8787B8ULL, 0x413A21B5C1EEC35DULL, 0x03083FB23D250529ULL, 0xF44850C6C34F881FULL, 
            0xC1548AE38385558DULL, 0xFAA616D73EFBE9FDULL, 0xDCAD19311245C832ULL, 0xCADDE7594710D984ULL, 
            0x5C0C7485B680F14FULL, 0x30C07DF75818CDF8ULL, 0x4C395278F0586F10ULL, 0xE540E55907103DFBULL, 
            0x97756B958304B766ULL, 0xEE9C7ED1426893CAULL, 0x18E8E4C46110795BULL, 0x9E21D66B1026A2C2ULL, 
            0x24A25BED54CD894EULL, 0x8695FD7C12C45995ULL, 0x2A6EE1A60882EDE5ULL, 0x133382A7C9EB433CULL, 
            0x0F939B96DFEAD292ULL, 0xDA6B63D04404798FULL, 0x8D6BA312707E2774ULL, 0x9767C561DB1630BEULL, 
            0x5F0DE3AAD06B50ABULL, 0xC59344B9695FE6A5ULL, 0x14C722C0F336DDE5ULL, 0xC6823BB5C9E975DCULL, 
            0xE1D543F222CC49CEULL, 0xE626141B63C8EBC1ULL, 0x060388C0487E7759ULL, 0x1056040F3706B666ULL
        },
        {
            0xB9DC4BAE05DD7EDEULL, 0xEF850302A1B8F9CCULL, 0x88E6A16AF088B503ULL, 0x611839A5087C777BULL, 
            0x82F88FE252F5403FULL, 0x7BF85B8634D30FBCULL, 0xF8429829DD8A3903ULL, 0x4DF2D94A10D102BAULL, 
            0x151EDE016BBF16F1ULL, 0x588329A1A6A20722ULL, 0xBB5F29EE3B65B283ULL, 0x03D132860436A85CULL, 
            0xF3BF16A4A56DD194ULL, 0x399DD9B726FE83A3ULL, 0x5DB93C81C9000390ULL, 0xFA7B51C8843BDDE4ULL, 
            0x9FE88B6995F61A27ULL, 0xC7CB07A3823A4472ULL, 0xA5CB7E22E52E8CB4ULL, 0x04CE2BE8169E9F88ULL, 
            0x202F0E3393C3304FULL, 0x8B02272D06A860E5ULL, 0xD36C2B2327A45613ULL, 0x1FE591D511BE3448ULL, 
            0xC6A3F85A6DEB43D8ULL, 0xA581A611F2AC6311ULL, 0x267690F08E79BBEBULL, 0xC5EA04348B44AD77ULL, 
            0x0B9B35122F521F87ULL, 0xFA584342D5E88F77ULL, 0x159EA7D418912686ULL, 0xB8E5B69582A9A913ULL
        },
        {
            0x2B4336AE6F09848AULL, 0x16000208B272C50FULL, 0x570EE9757A4864F3ULL, 0xD7E011871889DC49ULL, 
            0x981EBB13261DD16CULL, 0xDD146224876E27C4ULL, 0xC55185AF564B0E9AULL, 0xB5A0F2DFB4F88EEAULL, 
            0x6B46203C7AF1C509ULL, 0x10E27D61E0461A5AULL, 0xCB559FF3A2E6AFFDULL, 0xAB985B937261C14EULL, 
            0x76492930E796260BULL, 0xD2B33F6AD2168C37ULL, 0xFE379AC27335827FULL, 0x7C0DBD6B39AFBC47ULL, 
            0xFB4635545A79F249ULL, 0xD5EA90BEA6F6DBE4ULL, 0x5DC6BEBC9F482A57ULL, 0x0C356BA5FF28C74DULL, 
            0x4BFD39198328E63BULL, 0xAC8AD10EC0761C3BULL, 0xAD02B0DD4663AAEFULL, 0x0F825B31EFFA99B0ULL, 
            0xEE56AC7C605E178AULL, 0xF3B02422EC2251AEULL, 0x0DB0CDF8B0364244ULL, 0xE31E7F463CF70C81ULL, 
            0xAC60D3DB5275F16BULL, 0x21E4D1451EDE8111ULL, 0x2D8616A39D1F1DC5ULL, 0x2F8A8450D8473A95ULL
        },
        {
            0x9217CA79763772B7ULL, 0x8A0260986B769516ULL, 0x4331391E90A0D5C4ULL, 0x90EDA2F444AE7B7FULL, 
            0x018C2D3A23C7A82FULL, 0x1DA066B300481028ULL, 0x0A6FA9617121B58DULL, 0xF14BF75DCEEF73B8ULL, 
            0xC2DB92738B24E088ULL, 0x9B114C0410C73282ULL, 0x684C227DBB202D2CULL, 0x496A92F46B7C9FCDULL, 
            0x82556848594099D8ULL, 0xC7551DAEA8A99FC7ULL, 0x072EF96A1C77CE24ULL, 0x5056DED36EFFF55CULL, 
            0xD8FD9B278B574DB2ULL, 0x5CDBD4285B90823FULL, 0x4F521CC525CB54CAULL, 0xE6F99090B77805C5ULL, 
            0x8716A9FB1FC22220ULL, 0x941FE8FC7F28BECDULL, 0x39170A996C912389ULL, 0xDE56B517E30A6346ULL, 
            0xC8FD1A24B61DB3E9ULL, 0x64990B1082C46B79ULL, 0x08FA1DE16DF0B75CULL, 0x894B1FA2D2DEC8EFULL, 
            0x496DDB2E5EAD2AE4ULL, 0x1C00CA9138E58212ULL, 0xE68F211DB88F5739ULL, 0x69ECF94624376364ULL
        },
        {
            0x14FA9DE98717848BULL, 0x0E1C2E2A04040BDFULL, 0xC60C2205B791D1A5ULL, 0xBF3E10083CD205C4ULL, 
            0xC2B7A53020CE4D39ULL, 0x4F23A44655AE5BAFULL, 0x6DD5FD9C83299F9DULL, 0xC234E4E38460485EULL, 
            0xD571C01C32B17611ULL, 0x5DD9C728AF7CE603ULL, 0x55B82D9A59BB9A57ULL, 0x97C596FFDED8793EULL, 
            0xBF34C517FFA65CF0ULL, 0x6AD9305CDEECE092ULL, 0xC719556C94781D92ULL, 0x77C233F874437E8AULL, 
            0x7523F1A6E7CFCDE8ULL, 0xE2585841B68C4B33ULL, 0x0142B46CC7B7E308ULL, 0x79810A2DFAA3954DULL, 
            0xBFAEDAE756C214B6ULL, 0x346D5ED13068715EULL, 0xE62F09659EBD2057ULL, 0x70E0E006CA1B6C5EULL, 
            0xEEAF48C6B89D8E8DULL, 0xE6A275098B9E092BULL, 0x78BFF5E0C6088B09ULL, 0x4B91D6FEC97A3CC9ULL, 
            0x569DECD2BC987816ULL, 0xE358611A941C6A24ULL, 0x455650D9FC11F70AULL, 0x3836BAA4A9039460ULL
        },
        {
            0xDC0590F05D08197CULL, 0x13CBA2BB5AF977DFULL, 0xBFFE3CA965FFB086ULL, 0x1036E0AD20919251ULL, 
            0xAE8A10678521771BULL, 0xA64FE636AA433056ULL, 0xD5F685F7BB03EA3EULL, 0x646D3E98CE276418ULL, 
            0xA8A83ED8625B1084ULL, 0x4D646D95E64840A7ULL, 0x6913B2D97EB678A7ULL, 0x333DCC1A7DC9DCF5ULL, 
            0x6200DA5C6426E18EULL, 0xC3C6EF6037F83DEDULL, 0x27A1BF547673C27DULL, 0x28939DA3499ABEA2ULL, 
            0x47FB3AAB661562F9ULL, 0x866DE9D1DD470653ULL, 0x8A074D744527D24EULL, 0xA0415C223771A8B3ULL, 
            0x09CCE888F8FB16FDULL, 0x7993DDB4878B41C4ULL, 0xD45040358C3E4D3EULL, 0x150DA986378790A4ULL, 
            0x2261E1A77238BD1BULL, 0xDE8BCD3267805C5CULL, 0xB535C58CF8B171ADULL, 0x86321A6D86CE2F7EULL, 
            0x4A12389EE74BA492ULL, 0x0ACF103F3C353FDAULL, 0xC243069813F13CB9ULL, 0x018688F2B966B18BULL
        }
    },
    {
        {
            0x9391497D2788A046ULL, 0xA2CFECD33339A25EULL, 0x2CD50581367CA92BULL, 0x11CC096CF490F3D6ULL, 
            0xCF73373B9C17BA28ULL, 0xC9ED003C74E50B67ULL, 0xFB48703BB1DFBB87ULL, 0x813443BB1DC5B5C6ULL, 
            0x9BDC9E6988BA2A83ULL, 0xA22462CF8C90EE8DULL, 0x1F9D47AEE2F5DED3ULL, 0x182266EFF86163C6ULL, 
            0xBDD8B12EDB339686ULL, 0xE091C43025C8A14BULL, 0x4455264603497B3EULL, 0x76A7258E192F5146ULL, 
            0xD961F7457A59551DULL, 0x7D9AC5CDC591E68DULL, 0x497BF165131E2394ULL, 0x40CE0E78926D6838ULL, 
            0xAB87E5540C1EE4C0ULL, 0xBAB71A0A03BF0419ULL, 0x11D3DF8625336C11ULL, 0x89B08D64F7C20057ULL, 
            0xDF419855FBE343E5ULL, 0x358AD690EC3D4D69ULL, 0x3B28A77E2B6169FCULL, 0xD8F159992954A216ULL, 
            0x159138D7FFDB2E8AULL, 0x9EBA1941F42C2D18ULL, 0x247D21A0367485B9ULL, 0xB9ED6A66848700B5ULL
        },
        {
            0x91BDED291DF1D5D6ULL, 0x515B1E78E64F6C54ULL, 0xBB50E1E3BDAFF365ULL, 0x36F714701B599B09ULL, 
            0x0A24E71259916ED4ULL, 0x2DA35597307C2B19ULL, 0xC382BFA3290C7A1AULL, 0xE85830AADA1F3D74ULL, 
            0x416C47210CB10434ULL, 0x72F88559A0624773ULL, 0x12CE6CFFC9670467ULL, 0x02A73BDF66177CCEULL, 
            0xC1AF5CA3AFDE96F3ULL, 0xB9EDA313F348ACE3ULL, 0xFDBE630F69CC77CAULL, 0x8F7DAED4CAC8DE84ULL, 
            0xAEEAD29030653B9DULL, 0xCD0B85BBEE6AE4E3ULL, 0xE18D2D4F6D24091FULL, 0xE74AD6881CC624B7ULL, 
            0x91B81C116677402CULL, 0x92119CDB3D48E650ULL, 0x44ED6D6CC090C917ULL, 0x7F0A6B178B6F2728ULL, 
            0x4974F8B8322D5ADFULL, 0xDF8A3395AB5549D4ULL, 0xA9BB30B3F28A8BB8ULL, 0x7E3D406182A64C98ULL, 
            0x922908706312AB05ULL, 0xF2E348D55A1BDD63ULL, 0x419CFEED66EFF049ULL, 0xCF303F8BEAEC71F9ULL
        },
        {
            0xE08858A8056F6DF1ULL, 0xB0813C5E755D7F3CULL, 0xC7FC7284AC149E19ULL, 0x206FD9E5C02E0F77ULL, 
            0x1B0167C8A5CC9D22ULL, 0x83218E56166BD700ULL, 0xC9B813D70A64D948ULL, 0x6836FA4A0696184FULL, 
            0x7787100FCB715821ULL, 0x6B67AD0976BD386BULL, 0xBD772569AD65F39DULL, 0x0079D8DB69086D72ULL, 
            0x1F267F117B00FBA6ULL, 0x6065683740475C50ULL, 0xAD9994E2EDB67400ULL, 0x9C60C7CC1020563DULL, 
            0x5E5CBAE327DD009EULL, 0x4F8AB398F8BDBDDAULL, 0xBFE8821851AD351CULL, 0x12B294DC38134A81ULL, 
            0xFA324271C7921B3AULL, 0x1AA7859F7923042FULL, 0xF22D1DA077D2F50BULL, 0x8A8F9B64A474CA93ULL, 
            0xCB5C93AC5542765BULL, 0x78B6308C01A5F332ULL, 0x8B984C1295962D80ULL, 0xBF8917D31827D454ULL, 
            0x47F7E6D8B21C409EULL, 0x876C477501237519ULL, 0x4A1AAE12497AAD0FULL, 0x64092653BA072318ULL
        },
        {
            0x1176DCF8A61C039AULL, 0x9DA9A30A3FA7D2E3ULL, 0x46EF310E3A62BD1EULL, 0x266D2FF300149269ULL, 
            0x007980F1AACE9084ULL, 0xC866CF7C900AFE1DULL, 0xBCF1AA2FD53F29ACULL, 0xC8AB31409CCB67F1ULL, 
            0xEAAE601B41440B4DULL, 0xD164EBD4DE19D2F5ULL, 0x6B71E91C0E58B5F2ULL, 0xFCA65A97231A9BD2ULL, 
            0x8FF50CFB655FBAB8ULL, 0x0AA7B44D3BE6AB56ULL, 0x6C2AC32448B9D2BDULL, 0x96E046CB46F52820ULL, 
            0x5CF7F9A002F54A99ULL, 0xCFA9E1779264ED9FULL, 0x391221AEB502776DULL, 0xB30D6716986C19EAULL, 
            0x7BB7E6F18A12C5C9ULL, 0xB3AEE7D242187E81ULL, 0x8EBFCB89AACCD1CDULL, 0x59B9333CFAAF7B58ULL, 
            0x88B4EE0D32474BE2ULL, 0xE29A5A16BF9EA8C9ULL, 0x4CD789E1761F668BULL, 0x30A13015F62732B1ULL, 
            0xFEB0C22BCF2DE8C4ULL, 0xBA0E62FECA0EA594ULL, 0x63D784048AD43F61ULL, 0xD70FDACEA628E63FULL
        },
        {
            0x6AEDFECBE6F8FAB8ULL, 0x8311E659122638C1ULL, 0x7DD3B1B9494F81C9ULL, 0x563CBB538421D36DULL, 
            0x06CA22AA5DE9AB6BULL, 0xFC403AFC69C9B3AAULL, 0xEC1C7E3CBA4C75A7ULL, 0x4EB2D1DDB6FB877BULL, 
            0x0131EDB5249720E4ULL, 0xD7E6D889212168C4ULL, 0x966E7DDD902EC06AULL, 0x6AA7A22FF7D596F4ULL, 
            0xA8B84A55B51C1531ULL, 0xADCB1792F22CB38AULL, 0xD9A666543221FE04ULL, 0xD0D24E9FFF5C6349ULL, 
            0x17863B3E3C631C89ULL, 0x96325F0F435B9EF5ULL, 0xC3FA851FCC3D1599ULL, 0x67C8C34EC9C39B83ULL, 
            0x0782A73642FB9207ULL, 0xDC584F1FF908E9D6ULL, 0x7E911382103D2EA2ULL, 0xDFA71C70E6B85173ULL, 
            0x4F484E543D36E517ULL, 0x96A9DA975052F496ULL, 0x7738BCD8BC43CBADULL, 0x4F624192DB1E382FULL, 
            0xF41C2B6E56778940ULL, 0x00C4AE7ED545A3BAULL, 0x26849C01B8806F6CULL, 0x4862910E9B47DCE6ULL
        },
        {
            0x8DDD485F61A85E1EULL, 0x5CD9011734C4CAE1ULL, 0x3AD6BC0640F41582ULL, 0x18AEE9A067F31E6BULL, 
            0xFD79A0D174A4AAA9ULL, 0x646B9DE096F7F17DULL, 0x21D7A8877468E0A0ULL, 0xD1752DA203AC406AULL, 
            0xAA8EAA25E3B55AA4ULL, 0x13B6157694510286ULL, 0xA43E31460E54E768ULL, 0xC9D4382FC2265FC7ULL, 
            0x4C71BABB404FC35FULL, 0x5E1F20E10150A1E8ULL, 0xE5A9234977A51B6CULL, 0x01F539563B04B790ULL, 
            0xC5510671C4BDE317ULL, 0x7EF6B0260E3AEBE1ULL, 0xFB3EE5AF89EFEE4CULL, 0x94BFF41B77FD0EF0ULL, 
            0xB14156C90B5E6A47ULL, 0x9C053134357A1EBFULL, 0x3E3DF224874DC29EULL, 0x58DD543BCF9E3D40ULL, 
            0xDCE9D17B6D5C2251ULL, 0x7813F40EF8E056D3ULL, 0xD3B64C1C266659ACULL, 0xCC402AD0C7005198ULL, 
            0x98B0F9F3D96E8295ULL, 0xAEFF34CB2C0CEED0ULL, 0xF3472B345E43AC47ULL, 0xBB976A9B5BE6DC9BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseGConstants = {
    0x17757F5BA97C1C5EULL,
    0x04F2E07B6C3575AAULL,
    0x85853D3F5CD65ABCULL,
    0x17757F5BA97C1C5EULL,
    0x04F2E07B6C3575AAULL,
    0x85853D3F5CD65ABCULL,
    0x553939322B5A6432ULL,
    0xA2C8369AD763FDF4ULL,
    0x4C,
    0x13,
    0x4F,
    0x4A,
    0xEC,
    0x06,
    0xC9,
    0xB2
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseHSalts = {
    {
        {
            0xA4C58AF935107D58ULL, 0x4E8678F9FF78FA3BULL, 0xE271378A9AE40D72ULL, 0xD354C7D7B3CF0223ULL, 
            0x22AFA8FC3038C19FULL, 0x1C72DEF292B1C848ULL, 0x7EF919584ACE312DULL, 0x4395C0C485D8A700ULL, 
            0x7AA6B95FD18AC28CULL, 0x8ED186559C0C7CD2ULL, 0x1DF343B2EDA53CAAULL, 0x75207EE486D5949CULL, 
            0x96FD888E19570FF9ULL, 0x3C95ACB477C4F42BULL, 0x77EF910D3ED4BE57ULL, 0x1E3ADFD24290C63AULL, 
            0x41B168937FFF1E6FULL, 0x4872A3CAF11638AAULL, 0x5F2C574D6FAF2901ULL, 0xAFBCE4AAAB663731ULL, 
            0xF48544E68831833CULL, 0x3742341D3E3DC106ULL, 0x9FBBA02223D41534ULL, 0x931B361FB6066E67ULL, 
            0xADCA41B9ABFBD630ULL, 0xC6A504937C947282ULL, 0x9BCB14BB7988A6DEULL, 0x826620EDA15D740BULL, 
            0xFB0C1AEF096DFAD2ULL, 0x2FE39BB896CFB553ULL, 0x91CE3FAA862B7DB4ULL, 0x027719C3A9F759CFULL
        },
        {
            0xAEDCED77EE5C5714ULL, 0xB45B3C565ED05256ULL, 0xFD13C7F74DD1581EULL, 0xDB4E3B8FB058D851ULL, 
            0x8C82F947D1E4FFB8ULL, 0x2E70AC9AFA6FBCA8ULL, 0xDC9BC990ED1FA780ULL, 0xC14224B7929BE3ECULL, 
            0x227F4E58E5644954ULL, 0xBAD842732C51477EULL, 0x47F4B0B8CADB899DULL, 0x1B449C9808247631ULL, 
            0x40280DCDD1527103ULL, 0xB1A385C3E2B2E1B6ULL, 0xF260EA588ABEC79CULL, 0xD3DD3F35B4F2CFEFULL, 
            0x90B28B97CA6D71C2ULL, 0x4A35B19ECB2A333AULL, 0x2191445592A63A07ULL, 0x776EDB595B975691ULL, 
            0x7DD1DC3B978CAB9DULL, 0x14354130862E4E0AULL, 0xDA10C9EC4C2748E4ULL, 0x01C5B3CAAC000695ULL, 
            0xD140D5690EE143EDULL, 0xA65A32F16B19DEC1ULL, 0x3D5C1C208DC1A0EDULL, 0xD2E607ABA7D64B8CULL, 
            0xF96EF8120EC0F998ULL, 0x37A778D7C0E5B045ULL, 0x01713F49FC2D58C4ULL, 0x35DC413C6C07DAEDULL
        },
        {
            0xC10628858B8E7DEFULL, 0x214357D4C6C73523ULL, 0x862BD6F895CB20BBULL, 0x52CE22B3D14C96CEULL, 
            0x014660B087986C59ULL, 0x4E4C530C0B819A3EULL, 0x24383540EAEEC62EULL, 0x8F034A2408940B73ULL, 
            0x7170205657747714ULL, 0x0FEBFD33AC449EB8ULL, 0x8C252C1570687991ULL, 0xE6027DE2B317E996ULL, 
            0xFD343C773CA384C6ULL, 0x1D5E59AF32C40605ULL, 0x6C3EA2715C2D190DULL, 0xFD52CCBF4FCED8D3ULL, 
            0x24EBF445CED0500BULL, 0xEE184D6F384D85E7ULL, 0xAA25E8E23158C165ULL, 0x8D491214B3286207ULL, 
            0x5CAF4A39D93D2BBAULL, 0x77B7916CB5E6E02CULL, 0x40A4F0610690C980ULL, 0x266B86CF6F95C748ULL, 
            0xCD15A07ABA1D9193ULL, 0x59196B9C655BBA2DULL, 0x61238DDF6C435879ULL, 0x5ECA03657E6D3F9FULL, 
            0xC8C5B9F46BFF1627ULL, 0xBAC5B2733D87A48AULL, 0x7FB03E606F574892ULL, 0xE8ADAC54EBC9ACCFULL
        },
        {
            0x7ABCBDA60CEE582CULL, 0xDCDBF16F94ABBE44ULL, 0x01410015B7EF1C43ULL, 0xF369711C7D9AE360ULL, 
            0x00A0125C318C8A96ULL, 0xE50F5D918873084DULL, 0x5239CC7CD946A274ULL, 0x94BE21251A5F2B6FULL, 
            0x3223727BCF4EB62DULL, 0xA669350E1C800C08ULL, 0x3E12EDAF0B978733ULL, 0xEE23D938E1171087ULL, 
            0xFAD01AAC09D988C6ULL, 0x42C4FC591258549CULL, 0x229301269460F2CBULL, 0xC78BF9E41585487DULL, 
            0x0C75AE8833718E77ULL, 0xE412196BCAD54A4BULL, 0x3C94A7DDC1E3DF49ULL, 0x9127320E080F0D69ULL, 
            0x844C0B41D9DEC18AULL, 0xB0C539F5912D878BULL, 0xED6BBAE9F8B38931ULL, 0xBFB86CA6E8FA79EEULL, 
            0xF473465E46559082ULL, 0x2E79B9E846661119ULL, 0x632974BB5D332CB3ULL, 0x92719A87214F4D25ULL, 
            0x6D2316BDF905AF36ULL, 0xC3A48B16C1756F94ULL, 0x13B11377B36C650EULL, 0x74BDE71778F73EE1ULL
        },
        {
            0xBD20272C842B32DFULL, 0x3DA3A1EC334DB4CAULL, 0x266909322F6EB7A8ULL, 0x62EC351BCF85F48FULL, 
            0x72183C2612976056ULL, 0xB940D7DAC529D187ULL, 0x12C57BD9346F6F73ULL, 0x4442C6CABC2783E2ULL, 
            0x6FBC370A2B351874ULL, 0xB01FA2C89382454AULL, 0xF4D6E714E724D832ULL, 0x9BA5F5CB73EA381FULL, 
            0xE50542AF1B40650AULL, 0x4F86D8D79AAB934AULL, 0xB9E68FA470BB52CEULL, 0xC447E5769E4FFE0AULL, 
            0x22D7D84349672152ULL, 0xAB07EC9971718387ULL, 0x4A5667577A3867C8ULL, 0xBEA1CC584669726AULL, 
            0xB8AF0B9FA4870437ULL, 0x2564FF2E0DBA10BBULL, 0xB377385FF7162649ULL, 0xD6571B46F2DD54B1ULL, 
            0x30F4CC9258D50503ULL, 0xA9F0F73BBF8B5ED2ULL, 0x4E9EDC3C45BCCD62ULL, 0x61D0E4CD1ED19014ULL, 
            0x83F8CFCC1BA71906ULL, 0x17D6EEE5BC8EA0D2ULL, 0xF179A9C9B6743C5FULL, 0x99C1D93A1B94DAABULL
        },
        {
            0xB63D2776C14C425FULL, 0x4F97BCECA79B4120ULL, 0xF986AF0E8A67B099ULL, 0x3AB61F97F78375F9ULL, 
            0x1D8C438556E94FCFULL, 0x75C50BB4E6F38CDAULL, 0xEECE7BFB2619FD59ULL, 0x6DE7EC45CACE2BD6ULL, 
            0x21053846EEA9A36BULL, 0x981744B1BB9AB8ECULL, 0x9BB0EB3F5798C2B3ULL, 0x3F0566F2E323C1EBULL, 
            0xAEE3A81011277757ULL, 0x2D036FCF641D428CULL, 0xF11E6CF453B8280EULL, 0xDD40AE229BBF93DAULL, 
            0x6EC3DBD1568F5516ULL, 0x12D0DAF663FEF6C2ULL, 0x056D1052F3C4E148ULL, 0x6C95E26BC474FD32ULL, 
            0x50AE266E53E05D33ULL, 0x1D1E72F20F82A472ULL, 0xE1A7CA6279648D99ULL, 0xAB8CE6AD82B38848ULL, 
            0x779EE51D1D750458ULL, 0xE69A12BA302B2526ULL, 0xDBE87180F473D572ULL, 0x57EA395208CABCC1ULL, 
            0x8B47C2A033A6BB99ULL, 0xA86B6D7EE83ACB2DULL, 0xF5CEF7222D2453BBULL, 0xBC5CAA194404E7EDULL
        }
    },
    {
        {
            0xFEBCFA8CEF4E7CF4ULL, 0x2F12C52CE6FAAD36ULL, 0xB4771AEB0BE3FF4BULL, 0x1087BCA42B4E5744ULL, 
            0x48538951251C6134ULL, 0x55AF49B05F4AB78DULL, 0xB749735942528B00ULL, 0xBA4BFC23EEDD25B9ULL, 
            0x7FC204BF43610BC4ULL, 0x9103B652D0C89704ULL, 0x1A386BA79D416AE2ULL, 0x3340A4594C3BBE1CULL, 
            0x91B8BDABD1C26BE0ULL, 0xCE8363FD0618B82CULL, 0x311DCA9DC4FD179FULL, 0x9FE01D034B3D5C79ULL, 
            0x03D3B0D34559793FULL, 0x0DA4959AD97BA877ULL, 0x172BC7B1E8D08CE3ULL, 0x482440CFF62A9776ULL, 
            0x4F836EA99F74EA15ULL, 0xF8D6512948B319FAULL, 0x6575B4EF4866CAA9ULL, 0x2808918E210F0506ULL, 
            0xD2067857D86E7D23ULL, 0x970641C80DFA8BABULL, 0x7397B258BBB79A87ULL, 0x8779C71808D35254ULL, 
            0xA2AA5CF0651118D6ULL, 0xB8398FB83CBB1BC6ULL, 0x078C8E0818E0E7F1ULL, 0x7A660BD5E9603697ULL
        },
        {
            0xA435016F504A9A9AULL, 0xAC4F0FAC52410C27ULL, 0x23FB37C5505D4512ULL, 0x39A8663287662F24ULL, 
            0xC9AAB6B6653DBBF6ULL, 0x79DF91C68A9CD864ULL, 0x9ADA20E75E89CD34ULL, 0x0831A8117FE51EA6ULL, 
            0xE01F67D087804E29ULL, 0x62E1C3BCA43EC012ULL, 0x5931A498F50D3247ULL, 0x6B4E9567F5FCD7A9ULL, 
            0x5C3C5E7CA1CD4576ULL, 0x61FEA914590A5719ULL, 0xB00EEFC79120690AULL, 0xB40D3AAF467CC4AAULL, 
            0x7A60C2F20A560660ULL, 0x91D4B3A40B55F68FULL, 0xB1E1C8A6A46D8954ULL, 0x5FC52B613CA64A6AULL, 
            0x9A5DE643CFA2B704ULL, 0x02D29D4D01EE46FEULL, 0xCDE568CC678208A7ULL, 0xAAE4650C70FACE45ULL, 
            0xE7F4C1CF2A8F0A43ULL, 0x6C678483E22413FEULL, 0x091A8EFB6B9884F9ULL, 0xD02CD3633C77B367ULL, 
            0xBECA45E7AA9B4658ULL, 0xF95C1F6B8BA6D9A9ULL, 0x6E8DB3D1728A6736ULL, 0xB9319821AC88B952ULL
        },
        {
            0xA78975688A958664ULL, 0x54FD824511AE0316ULL, 0x3ADFC82F1EC49385ULL, 0x40D17420702B0422ULL, 
            0xC578A187A391203BULL, 0x72EE737CF304D63CULL, 0xCDDD78C2FAF0FE5AULL, 0x068B0D0D2E62F8B0ULL, 
            0x7B31E48C678CD847ULL, 0x04033ECD0BE4535DULL, 0x162CB5B51EAA52C6ULL, 0x4BD1D8ECA224ADA6ULL, 
            0x8A8CCB800C77ADC1ULL, 0x373EC3DEE25B906FULL, 0x9C1134318FD9854FULL, 0x23F92F54C8513B11ULL, 
            0x638E9A11249BCD72ULL, 0x824C9219969A9161ULL, 0xDB5E9AD26AE1A575ULL, 0x19107825CFE9911AULL, 
            0xE182EE0379CB15ABULL, 0x3BCF1082103031E6ULL, 0x1623421E30274B83ULL, 0xBE8145F3B26F5A07ULL, 
            0xEF844D3C014F8943ULL, 0x8E99E2AC3D79B1E5ULL, 0x78BBEAA472F21651ULL, 0xFAE3225D55E9B6CCULL, 
            0x6E7BC0B245E5844BULL, 0xBBF0E738A4E121CEULL, 0x6443B12B5110CE79ULL, 0x1A0AAA3BAEBF9778ULL
        },
        {
            0x0C00D33CBAA4B47BULL, 0xC752C44B677FF871ULL, 0xCF412A39B22F1AC0ULL, 0x140F142F350F697FULL, 
            0x19F9A111FFF51C2AULL, 0x2D287D35C1FD14AEULL, 0xF044804FE557CDA2ULL, 0x505CE8CA8A46FED5ULL, 
            0xAC13E510C32A6418ULL, 0x3F940A3894532479ULL, 0x664EFAC8E650ECCCULL, 0x853E91C611D8D7A2ULL, 
            0x04F3DC3E024FAA92ULL, 0x4582DB376F479F5BULL, 0x091BD6C94E3F0D7EULL, 0x9D8128A5D3ACB0E1ULL, 
            0x3B3784E091485FA0ULL, 0xC2575425FC10BC9DULL, 0xBE3B83B21F23B3C3ULL, 0x6CD12256E019E1A6ULL, 
            0x0850F5897D00BA1FULL, 0x014EC9D5C981AB6EULL, 0x9E8A5561F24EE045ULL, 0xB0C064EDEB9F97B9ULL, 
            0x91ECD3950EE1B58FULL, 0xD22047CDFA952131ULL, 0x52EBFE6044E94F23ULL, 0x8799CEC30997A7CFULL, 
            0x3335709DC56C82BDULL, 0xADD440E7680D07D3ULL, 0x0B67FDD6B10BD08EULL, 0x1241B8723ECDA5B5ULL
        },
        {
            0xBB95B372189F0DFEULL, 0xDFC0CCC76A8BEAAAULL, 0x563DC79B0E4F7FC6ULL, 0xC02398F56FF5DA7FULL, 
            0xA6AF6B8E72DA8224ULL, 0xBE404FD902A009C0ULL, 0x3CCA2326C0F3361FULL, 0xC4A726AA0713F9BCULL, 
            0xFF6D6390EA9F18ECULL, 0x8F496144159A8081ULL, 0x844F6BB3EF6F5122ULL, 0xC8E971A60D4816FDULL, 
            0xEBDFB3E7EBAF36F1ULL, 0xB765EB4688A91241ULL, 0x0F604D577D859DCDULL, 0xDB86970BAD2A863EULL, 
            0xFCFF2053B50E2DA0ULL, 0x09C8BEB07491AA6CULL, 0xB1CFFC8772338C64ULL, 0xE1C26A4D0E4F56E2ULL, 
            0xEFC3F9EB87969D28ULL, 0x30F7E7A0A5DAFC00ULL, 0x54B60D25B8EB5171ULL, 0xAE8B3CC785F44176ULL, 
            0xD7DFA842AF4DCDBDULL, 0x4D9AF55FEC92727FULL, 0x006920F0B513A245ULL, 0x7FA041A4A2D4A050ULL, 
            0x33F9BA71F16219F3ULL, 0xA184820F4B9D4A05ULL, 0x5F7A88A77E35B01FULL, 0x998D0025A33AB79BULL
        },
        {
            0x8851D7FF1BE11873ULL, 0xF35D63F10DC5AE4AULL, 0x1195C5FFDC79CFA0ULL, 0x89144BCFC291A43BULL, 
            0x4EA33C5EEDA45E6AULL, 0xC750DD4222F2D41FULL, 0xAA7DF83279121824ULL, 0x8293B688CE0DA2EDULL, 
            0x0D27F01D5BD9009EULL, 0xEFDD4416CAE1062BULL, 0x5D9D376983F31068ULL, 0x97F0373BB5EA6F9FULL, 
            0x31F932E715994122ULL, 0x51814254FCA4B542ULL, 0x69A42CAD10848FFCULL, 0x8DE5CBA9580F2280ULL, 
            0x17F6F9C4C5E189A6ULL, 0xE12FF466C5462EA9ULL, 0xFB6B5AB507E540B4ULL, 0x61329EA4235BDB44ULL, 
            0xC850FF1EA1471022ULL, 0x802DAA10793060D2ULL, 0xA154F28B0C163A68ULL, 0xA682D9BB575F6A80ULL, 
            0x8B455FD8742C4AEFULL, 0xF2B2361178FDC6BDULL, 0xD3FA32F1108890A3ULL, 0x614617718E7C09A3ULL, 
            0xD553ED0161C78FFCULL, 0xBA9F7AB69D633AD9ULL, 0x4FC77CA418DE9EC7ULL, 0x9A89F5AB04CEBF10ULL
        }
    },
    {
        {
            0x6CC990A0448787B2ULL, 0x77499E8CB1302E89ULL, 0xF419BFD5EBF82489ULL, 0x8FB12E177A789761ULL, 
            0xB5E7D82B32517E07ULL, 0x265C939667A89C74ULL, 0x5342E290F0451672ULL, 0x9E90257575806419ULL, 
            0xC741A3E1EA451E85ULL, 0xF0F8392D0FC14250ULL, 0xA4C150191EEF1B04ULL, 0x6DE3CC0F5DE516B3ULL, 
            0x8A7AB6AB529FC654ULL, 0x621C89766F488468ULL, 0xC1A8C4724B683387ULL, 0xBC3600C63FE15E79ULL, 
            0x3A60EC1501A0C473ULL, 0x3AB5612F22E22798ULL, 0x9F1E008FD0A58177ULL, 0x149484AD43653964ULL, 
            0xB253C6A6186895EDULL, 0x2E491C6D7F039C1AULL, 0x5E0ECB5EF4BA1CD9ULL, 0x6533FB2A6F2CFA3BULL, 
            0x18A98AC506F7515DULL, 0x851CF7FF5612AFACULL, 0xC00476A4472D44B9ULL, 0x3284FCF72610D628ULL, 
            0x9256CE6351B2DAD7ULL, 0xE4F8457F51AC5C87ULL, 0x9265312115E525C6ULL, 0xBC9F0212D57D7065ULL
        },
        {
            0x3C7A2BA79E9000DFULL, 0x58164A3F2881E5BDULL, 0x71873B1F7EA3E957ULL, 0x74CB7462047A5C8DULL, 
            0x0B49939D83030C1DULL, 0xBE202A20800243A4ULL, 0x9C6CC2B626FAFF8EULL, 0xD665DDE0DBB1F038ULL, 
            0x65DE5DA1AF98E415ULL, 0x5A32D2696F7BCB8EULL, 0x9383F66831BADCD0ULL, 0xEA64A386CA6AA23DULL, 
            0x19A4AABA3FABB0ADULL, 0xCC80A9E6FE4C3626ULL, 0x557FFF864EAFF508ULL, 0x5776A3E8ADA4A406ULL, 
            0x5E71117F3C543B0BULL, 0x2DBE82737CD963FBULL, 0x46577A97C64C3330ULL, 0xAE30C31808710356ULL, 
            0x04327F7DA1D1031DULL, 0x071A680A6B60042FULL, 0xFBBF048A642E81AEULL, 0x656FECF22664D1DBULL, 
            0xB5BF156B4E72E149ULL, 0x901F912B7013F791ULL, 0x118F37512D0E7301ULL, 0xC42EBE67D66E40BBULL, 
            0x5C2E1A382AC4369BULL, 0xA5CE7D367710914DULL, 0x04ADD934FCE1D338ULL, 0x1BE126930B1B6A48ULL
        },
        {
            0xBB4FB00800067301ULL, 0xD413BA3F7DA4BC3DULL, 0xC587D6744C4191EDULL, 0x9925A8D2C006E86EULL, 
            0xB4319F07C0743B0FULL, 0x6EB9D700CDDB3845ULL, 0x51932863C0BC4D63ULL, 0x2620F17FE420598EULL, 
            0xF5434E266699626FULL, 0xDDE5196C75CBECD3ULL, 0xCEFF29F54EDADE41ULL, 0x16EA7FEDEDDDD4FAULL, 
            0x1F44F5220B371AD5ULL, 0x42B88F2B740D1BEBULL, 0xD69AC5F9FC89441CULL, 0xF7ED7F744677C1B1ULL, 
            0x903FD8680E3996FEULL, 0xEAC742734B457264ULL, 0x3EE9C79DF389DD50ULL, 0xFD83D83607675B80ULL, 
            0xFA369C5D4E330EA5ULL, 0xC10C8C0AE8F42E25ULL, 0xB4C16F1E75CDCA25ULL, 0xD4F9D0A833C2BC2EULL, 
            0x8A7FA3BFD2AB0B95ULL, 0xD42D1680ABEC75ACULL, 0x7CDF63202394CEF8ULL, 0xCC283ED31A5894E3ULL, 
            0xEF03E310B4AD0035ULL, 0x9C51A619C081A011ULL, 0x556AE6728BDF1503ULL, 0xD36683E70050F710ULL
        },
        {
            0x591FFB585DAB4C9DULL, 0x24BC2138536E581BULL, 0xB679B998ED7A9E7AULL, 0x44AC51E86010E1A8ULL, 
            0xBD5CB1B8D2E3E300ULL, 0x8AD3D691715E0FD1ULL, 0x7DFE02B31DC4E783ULL, 0x54B459723449BCCFULL, 
            0xB85CE88FC993ACE0ULL, 0x75887951B671104BULL, 0xB95E001284C903B5ULL, 0x0E1B462101EC20FDULL, 
            0x9A0E81D990912E76ULL, 0xD762FBE285BB1E65ULL, 0x290587A60864C73BULL, 0x335FE8D708910D48ULL, 
            0xE56E4D4563878D33ULL, 0xBB11E6904236E9E2ULL, 0x517DE542A76D553CULL, 0x92249747F00102A6ULL, 
            0x787E1E7109407128ULL, 0xF8FA746C19E44317ULL, 0x204C6335872D28ECULL, 0x79DFE069E8F1180DULL, 
            0xF4F86DFA911F1E3DULL, 0x7791C12DEAB2C8AAULL, 0xCC76C4ADA69550E8ULL, 0x6600B5997406766FULL, 
            0x183C44FD2BEBB5A9ULL, 0xC62F07BA012CEAF0ULL, 0x31B1C47DB2100F95ULL, 0xCF777347CBF13508ULL
        },
        {
            0x3EF93C6CC5BDDF90ULL, 0x39AFBE732ED81A8BULL, 0x29A025584BE5E7AFULL, 0xE4823BD0CA9600DBULL, 
            0x73887375278EEF4AULL, 0xAE048A6BA79AE42EULL, 0x826C927850D29173ULL, 0xE62BCF2988BE6E41ULL, 
            0x5D2F17084C1E3B26ULL, 0x8B590CB454962337ULL, 0xD851595992936239ULL, 0xCB38C2F449A95803ULL, 
            0xB59147CFE3095C30ULL, 0x37CFCB84FF938C30ULL, 0x7A2DCB8F8CB4A660ULL, 0x261167DB6F983B22ULL, 
            0x9C19523598787365ULL, 0x950F7C03E7021195ULL, 0xB2D7D1B5E486E164ULL, 0x133B46CB1A47F91EULL, 
            0x0A474475BA71270DULL, 0x9ABDC8D70F0AF7FBULL, 0x67ED159B19B79E34ULL, 0x1199FC7712F2DD69ULL, 
            0x73980CBD0FAB98B0ULL, 0x6604584399E2551CULL, 0x697C8C48875BD881ULL, 0xF72370A78084656BULL, 
            0x277710052A4DE136ULL, 0x9EB9B934B2604C8EULL, 0x9E25B1E7EB70792AULL, 0xE6A846290323BBEEULL
        },
        {
            0x0A68D17EA19AC77CULL, 0x7ABEFD82683E6A4CULL, 0x1C1CA4C2FC2A3929ULL, 0xFA8FAD0500ED0BE3ULL, 
            0xADBA145F1D396A06ULL, 0xE31F8CE544502091ULL, 0x1B242B22A79E6AA3ULL, 0x85770F60421C90F0ULL, 
            0x50C16442F77A2383ULL, 0xA69B61BAB6D3C15EULL, 0x149188D94E9497D2ULL, 0x5DC58AA0E8F372ACULL, 
            0x3965235DF953BA3FULL, 0x876427408EC02022ULL, 0xB25386499C332244ULL, 0x2C02839D1C715A7BULL, 
            0xDB89F08250613420ULL, 0xD91117354EAA4933ULL, 0x6DA205023F84A0C3ULL, 0x9E771312EBADF2B0ULL, 
            0x39E16FFAF6499BA1ULL, 0x6EAFC9DC18F349C5ULL, 0x6390F9B008276914ULL, 0x39943AC67EB9B2ECULL, 
            0xB855A49714F4D3DAULL, 0x405BB863DA6B8CF6ULL, 0x2941EBEEC840BCB0ULL, 0x340AF43C2170A5F6ULL, 
            0xEB29F5A48E56D6BDULL, 0xAA88F6905E314A0FULL, 0x94DE80F8E97F7D5AULL, 0x6E3184E12DD8DBFFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseHConstants = {
    0x44235DEF1BF59EF8ULL,
    0x415AFCD198E9AB72ULL,
    0xFDAD5C0ED2FAA702ULL,
    0x44235DEF1BF59EF8ULL,
    0x415AFCD198E9AB72ULL,
    0xFDAD5C0ED2FAA702ULL,
    0x365113AA55D768F5ULL,
    0x6ABE8A7E2086F34FULL,
    0xA2,
    0x66,
    0x1D,
    0xE9,
    0x58,
    0xDC,
    0xEA,
    0x8A
};

