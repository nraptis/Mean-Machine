#include "TwistExpander_Regulus.hpp"
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

TwistExpander_Regulus::TwistExpander_Regulus()
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

void TwistExpander_Regulus::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE062E93A8D76D9A0ULL; std::uint64_t aIngress = 0xCA1F93D3EE31CD2CULL; std::uint64_t aCarry = 0xB6FD16A186E5B0C1ULL;

    std::uint64_t aWandererA = 0xBBA1C1498D8CEBA3ULL; std::uint64_t aWandererB = 0x80D79162233E9C1EULL; std::uint64_t aWandererC = 0xE0187D361618C224ULL; std::uint64_t aWandererD = 0xA0DD2A09E3EEA9F4ULL;
    std::uint64_t aWandererE = 0xF8734F5880642D84ULL; std::uint64_t aWandererF = 0xD9F410F162E5A235ULL; std::uint64_t aWandererG = 0x9449D4175C0191CFULL; std::uint64_t aWandererH = 0x8924989BA99F684CULL;
    std::uint64_t aWandererI = 0x8D234D51DF29C268ULL; std::uint64_t aWandererJ = 0xAB6642961DDDC6D2ULL; std::uint64_t aWandererK = 0xAAF2F24A92E5E1FAULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9888156045957742951U;
        aCarry = 17874077541157804798U;
        aWandererA = 16219810350450632859U;
        aWandererB = 15929984737111951341U;
        aWandererC = 10168310703430274403U;
        aWandererD = 13068325155773165286U;
        aWandererE = 12603873761500530592U;
        aWandererF = 16302899542469315290U;
        aWandererG = 10082187815358501563U;
        aWandererH = 14892733547617051205U;
        aWandererI = 14799640456368378972U;
        aWandererJ = 12890670105510144298U;
        aWandererK = 10382548256135175521U;
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
    TwistExpander_Regulus_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Regulus_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Regulus_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Regulus_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Regulus_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Regulus::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB9F51D9B650079EEULL; std::uint64_t aIngress = 0xC76B4150C0F22F1FULL; std::uint64_t aCarry = 0xD4841B4C00677FE9ULL;

    std::uint64_t aWandererA = 0xF14C51840B589633ULL; std::uint64_t aWandererB = 0xE319D01923FEE1A7ULL; std::uint64_t aWandererC = 0xFE87110AA5B8A512ULL; std::uint64_t aWandererD = 0xCEAB3A2E3A3260ABULL;
    std::uint64_t aWandererE = 0xE9778AF63F1EEFCFULL; std::uint64_t aWandererF = 0x8846F8EF1B2F7160ULL; std::uint64_t aWandererG = 0xF6F9183518211615ULL; std::uint64_t aWandererH = 0x9BC349523757373DULL;
    std::uint64_t aWandererI = 0xCABC856BD42920E4ULL; std::uint64_t aWandererJ = 0xBCEC8E8454643D8FULL; std::uint64_t aWandererK = 0xD4A5E255ECDDD4BDULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14624045243936874804U;
        aCarry = 13659873268512706609U;
        aWandererA = 13478595847110123540U;
        aWandererB = 15747540633478719736U;
        aWandererC = 14170214354172843902U;
        aWandererD = 14630231130197684563U;
        aWandererE = 15381542272941432410U;
        aWandererF = 17014699055845532383U;
        aWandererG = 18045954790230128520U;
        aWandererH = 14811174964464619511U;
        aWandererI = 9342023761531338946U;
        aWandererJ = 13037923446107463664U;
        aWandererK = 11174669286282027840U;
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
    TwistExpander_Regulus_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Regulus_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Regulus_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Regulus_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Regulus::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xF2837A466FEFDBE9ULL;
    std::uint64_t aIngress = 0x88F2FD5732948356ULL;
    std::uint64_t aCarry = 0xB924DDCE030A169DULL;

    std::uint64_t aWandererA = 0xE4ABF4283D378140ULL;
    std::uint64_t aWandererB = 0x9FAD692890E9BBE9ULL;
    std::uint64_t aWandererC = 0xF74014712A758A83ULL;
    std::uint64_t aWandererD = 0xF6B828273C532394ULL;
    std::uint64_t aWandererE = 0xC87D2179B06A3FCBULL;
    std::uint64_t aWandererF = 0xE1916C41BD37F4D3ULL;
    std::uint64_t aWandererG = 0xC28EF5B3B17E6E74ULL;
    std::uint64_t aWandererH = 0x920578E8A37DC0E1ULL;
    std::uint64_t aWandererI = 0xA3A04444A40DB19CULL;
    std::uint64_t aWandererJ = 0xBBB38515CE5DD081ULL;
    std::uint64_t aWandererK = 0xEF32A283F36D4A97ULL;

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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneD, 1);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneD, 5);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
    TwistExpander_Regulus_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Regulus_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Regulus_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 27 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 47375
void TwistExpander_Regulus::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1569U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 875U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 129U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 952U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1509U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 849U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 531U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1317U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1565U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1597U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1680U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 56U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1954U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1743U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 793U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 205U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1256U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 681U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1104U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1355U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1963U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 306U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 803U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1389U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 594U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1073U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1885U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1625U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2018U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1273U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 445U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1966U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1206U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1515U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 218U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1125U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1578U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 912U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 364U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1491U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 624U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 138U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1591U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 861U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 351U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1081U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1933U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1360U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1965U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2027U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1028U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 401U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1679U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 17U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 893U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 858U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 497U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1022U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1093U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1866U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 524U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 708U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 678U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 983U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 184U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1862U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2029U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1455U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1881U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1178U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1452U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1025U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 998U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1213U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2012U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1824U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 741U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1613U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1388U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1220U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1662U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1129U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1646U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 170U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 162U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 215U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 318U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 99U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1412U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1517U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 682U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1350U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1945U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1951U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1703U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1560U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1346U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 333U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 115U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 111U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1397U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 161U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 810U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1779U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 75U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 797U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 966U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1970U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1813U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1867U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 62U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 157U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 92U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 148U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 408U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 560U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1630U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1185U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 855U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1934U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2044U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1189U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1096U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1435U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1105U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1992U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1996U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Regulus::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x99EBABAC84B785F8ULL; std::uint64_t aIngress = 0x9050C4A8AAC659D4ULL; std::uint64_t aCarry = 0xDC71BE4A8D4AE281ULL;

    std::uint64_t aWandererA = 0xC6223AE74D8CA76CULL; std::uint64_t aWandererB = 0xC9F522FE0948F0BCULL; std::uint64_t aWandererC = 0xDB5339B998EFA340ULL; std::uint64_t aWandererD = 0xD2E57A26315590B9ULL;
    std::uint64_t aWandererE = 0xB145916238086245ULL; std::uint64_t aWandererF = 0x810CBCC4B159BDFDULL; std::uint64_t aWandererG = 0xE4081FB5AB5EEA36ULL; std::uint64_t aWandererH = 0xC6ABE433C9548BACULL;
    std::uint64_t aWandererI = 0xB6AEE29ED0F41281ULL; std::uint64_t aWandererJ = 0xEAB096C8F482F103ULL; std::uint64_t aWandererK = 0x8452A41329123D48ULL;

    // [seed]
        aPrevious = 10933202288093637102U;
        aCarry = 12044178174647758192U;
        aWandererA = 14812902218021133714U;
        aWandererB = 9301160547866691079U;
        aWandererC = 17935677667293779188U;
        aWandererD = 13135636411271334623U;
        aWandererE = 16099770395744792900U;
        aWandererF = 13888506156447581931U;
        aWandererG = 17192140201625673169U;
        aWandererH = 11287789156556113991U;
        aWandererI = 13090281305304526688U;
        aWandererJ = 17504518464076854101U;
        aWandererK = 9429564426290886255U;
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
    TwistExpander_Regulus_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Regulus_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Regulus_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 27 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 14074; nearest pair: 479 / 674
void TwistExpander_Regulus::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4611U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6476U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2522U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6992U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6951U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6682U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5364U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5130U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2067U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3173U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1710U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8114U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5243U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3658U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2054U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4245U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2026U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1973U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1888U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1701U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1008U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1547U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 720U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 618U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 108U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 139U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 977U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 95U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1918U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 953U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1945U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1809U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1574U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 166U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 897U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 195U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 27 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 14075; nearest pair: 499 / 674
void TwistExpander_Regulus::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4419U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2750U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7974U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7062U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3395U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2555U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5046U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4402U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4129U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6877U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7508U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1683U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1355U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7885U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7796U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1745U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 215U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 558U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 956U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 227U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1413U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 442U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1380U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 204U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1606U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1439U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1600U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 538U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 625U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 514U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 362U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1591U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1707U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 958U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1255U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseASalts = {
    {
        {
            0x3821D64B8AA5230CULL, 0x61773D7C3BD7EBE2ULL, 0xDD2F235B1CCADDC8ULL, 0xC6AA811A23FB0C8DULL, 
            0x064D43BC81447A1FULL, 0xA2CE04D2DCA0D0A9ULL, 0x2C82FB020D8FC9ECULL, 0x8A54842F3F8C3526ULL, 
            0xC57ED4C3DB518312ULL, 0x60C16DEFB2AEB7BCULL, 0x0952A528B138884EULL, 0xAC0870C7305F512CULL, 
            0xB6E0A480F28C3232ULL, 0x7A66A8D7F24E6F8CULL, 0x721D51CCDBCA7043ULL, 0xA8391F425C557B30ULL, 
            0x90E342067E9AB84EULL, 0x45D1F60D724D322FULL, 0xB18927A8978C8450ULL, 0x4C411F1158A23108ULL, 
            0x34DF152C6ECF4617ULL, 0x955F91C6BACB347CULL, 0x3B9F92113AA469C6ULL, 0xC200BCCD3D3D53C0ULL, 
            0x6C2A7C44B82CFF73ULL, 0x1B7A79A76D024E9FULL, 0x29785BDCADCA3A27ULL, 0xBAC4C685E5935FD4ULL, 
            0xCC489ED19AAA7C17ULL, 0x9AAFB104576AE522ULL, 0x6E68162AFEF82DD8ULL, 0xF20FF3D1D5760AD2ULL
        },
        {
            0xED43A47C08813AE3ULL, 0x2D06F327AEA2CB78ULL, 0xE5B208FEADA8D93EULL, 0x61A60951E82A20A7ULL, 
            0x1211CA2727E2C0EAULL, 0x5ED77F381ACFFC8EULL, 0x2039EB4BF0F9E6EFULL, 0x783D8C2C3F41F9FCULL, 
            0x12718933E4C644C3ULL, 0x4680DDC4887773A3ULL, 0x620479207CC18E44ULL, 0xAAEA276AD9699231ULL, 
            0x25ACC4D69914EC82ULL, 0xAFB55C91D00B0A78ULL, 0x152E67A17538CD90ULL, 0x5C6FD5449C8C4419ULL, 
            0x762FE751ABA4C7ADULL, 0x52099BB492AB83EDULL, 0x40E542BD07D8D922ULL, 0xA7D634ED1BC1F56CULL, 
            0x41548A32852D7739ULL, 0xAE2E93084209A97BULL, 0x2B3667A235DD7CC1ULL, 0xC6F58142D352A466ULL, 
            0x364025C7A3B6231DULL, 0x948F760873D74E67ULL, 0x7A1F65921EC9E4E2ULL, 0x6B309A3037393379ULL, 
            0x07F8AA4A65ADCA8FULL, 0x7E917EA899F1524BULL, 0xF4E8A2CEF8075056ULL, 0x2C3895D2A02E7BE1ULL
        },
        {
            0x8F178CE12D4428EFULL, 0x7F33AEC180A67219ULL, 0x757A7680297EB5AEULL, 0xEA4606CED2578E0AULL, 
            0x17AE872EEE4DFA3EULL, 0x81C504583C84BA71ULL, 0x8AA98B22B3AC8DA0ULL, 0x98A068865A7BA7D2ULL, 
            0xEB52DE611B0CB1E2ULL, 0x32B77C43B72CA774ULL, 0xEE180FAA0CE6F8BCULL, 0x7DF1DD9E54885DF1ULL, 
            0x5B9285B87F329237ULL, 0xB409B2DD6623AFCAULL, 0x1D2D9F9CE4C2DE08ULL, 0xC145917CFF7C3540ULL, 
            0x09A2D6D5ACC53407ULL, 0x9E857CEE6A9831B6ULL, 0x857A2875462DCA51ULL, 0x71656A3340355448ULL, 
            0xA1A150E82987389DULL, 0xE03ADC8037824A85ULL, 0x4BED27BE5A5F595CULL, 0x1ABD7E822264F783ULL, 
            0xD43F1418A65C7F0FULL, 0xA902B00D5E3445ABULL, 0x7D3A92EFC942F9C1ULL, 0x8E46553155308DE9ULL, 
            0x13723BB77EF26181ULL, 0x7C1931F7087BED31ULL, 0xD49254218FA91BB7ULL, 0x01DB53AEE6DA3518ULL
        },
        {
            0x8841237A6385A7C6ULL, 0xDEE172A78ECDA2F4ULL, 0x2B6867A322747B93ULL, 0x131CB878AE14BB7CULL, 
            0x3D89655A0698708FULL, 0xA22D66DFBCF76FC4ULL, 0xCEAD09387FFCB20EULL, 0x2C2158344F1FDCD8ULL, 
            0xF7BACC06EAA27087ULL, 0x71BBAF5FE23A8598ULL, 0x20F73E3827F906F8ULL, 0xADACC3AFB18A7A4DULL, 
            0x078A143F749FAF7DULL, 0x2FAC9711CCC2AB81ULL, 0xD85513E97FFD95E1ULL, 0x08E46C26A63CACE8ULL, 
            0x0394E61C22081E11ULL, 0xA68F6DBDDC071948ULL, 0x1BA34C35E2F9F5DCULL, 0x10DD001573CB1E81ULL, 
            0x1DA0340D49D34074ULL, 0xAE43FA8E47C09651ULL, 0x8325190A96A2B90AULL, 0x6B4428B0E1F422FDULL, 
            0xD70230BBAC72FF0AULL, 0x24FC5B018AD2A3CBULL, 0xAFE4A5E0CDD9CAD6ULL, 0xA6A56B5E8600E505ULL, 
            0xD92B1BF7BAE72F1CULL, 0x84F702F5F82A3E0FULL, 0xAF9500F63169256EULL, 0xA3F59A7053F60D4DULL
        },
        {
            0xE46A5553F6C23B3CULL, 0x121E0F111CF8F03FULL, 0x94B7091E91BB7C15ULL, 0x9F8C98E83ECAFE99ULL, 
            0x824AC3E7E1DF9E6FULL, 0x676BF410E220FD88ULL, 0x3235801F5D738B37ULL, 0xD7EB0742440F0AEDULL, 
            0xF42A9A2AC55D69F5ULL, 0x316C1CC0202BED67ULL, 0x67AD88262664E1A9ULL, 0xA5CF0BDD66D6EC61ULL, 
            0x2DDCE9C1BE1B9A03ULL, 0xEE206C832EB26759ULL, 0x56F3582DEAA4E415ULL, 0x3C53ADD0DD6C2C50ULL, 
            0xD5B3E96D6EB7554BULL, 0xC9194E1A05E7543DULL, 0x5981ECF94D924653ULL, 0x0A7F9AE9ACDFE93BULL, 
            0x2E5E68FACE2DB82EULL, 0x3DA3B0C70B670807ULL, 0x9511114D2F4E8276ULL, 0xAA6E69DE9B09EF8AULL, 
            0x5943DB52AB0F5E46ULL, 0xF1138D37F2BB9F99ULL, 0x3B30CE13D8ED2B9BULL, 0xFB36C601CCA7CF1EULL, 
            0x617CD5A5BCE004EDULL, 0xD466237B48565A37ULL, 0x6B65DE166582904FULL, 0xDE4A1C31B19A6330ULL
        },
        {
            0x1D9E9DC27A8394EAULL, 0x9FA1EB2CCDA9A50AULL, 0x476A4087A805A504ULL, 0x78B728602881AB58ULL, 
            0x8DDBE0FA61E5C72BULL, 0xD15A43EEF582A61FULL, 0xBD072DFD47AFB583ULL, 0x9E98341A95157DA6ULL, 
            0x3F21441749D9D234ULL, 0x9E7B82206FB6AC76ULL, 0x868DD4FEA77C617EULL, 0x11771F23472158B5ULL, 
            0x7EE9E23BA0AA8696ULL, 0x3CBC1A71D0965A0CULL, 0x43E5AF39B8948545ULL, 0x71E83C6E7FB0EC6DULL, 
            0xA7DE28717055C1D5ULL, 0xACA04DE21B244F19ULL, 0xAAE6EE688E09FA08ULL, 0x03097E2C113C2C13ULL, 
            0x49F344A8DD6CDC2DULL, 0x1331BDE46959FBCCULL, 0x17F5BD141B580CD5ULL, 0x76204FC046FB48C4ULL, 
            0xACAD5E2DEFF68E0DULL, 0x9311213B4E39A081ULL, 0x7109F8C75A146D64ULL, 0x2FB9EBF09A5773E6ULL, 
            0x5E5160C28911E831ULL, 0xD71807E625379C00ULL, 0xF659FE0EB78418F0ULL, 0xAB2D028A6789BFD2ULL
        }
    },
    {
        {
            0xC63D6B572D2B0C8DULL, 0x12A92542E7BA0BAAULL, 0x7AA180172726448EULL, 0x40B0F280CD62FFD3ULL, 
            0x425F1132981A78B5ULL, 0x47A0C919EE3D8F2AULL, 0x03DECC0A4BC5E7C7ULL, 0xC2D83BC08EA19D5FULL, 
            0x5E217F2152B2A16EULL, 0x8FA2C277721AB01AULL, 0x346087FCD1C09ADCULL, 0x9B04F370F710C484ULL, 
            0xB11C5AB813C8B057ULL, 0x51E487C653E3CBCFULL, 0x209C67E43C1D81D0ULL, 0x11C6E0A6EE25819BULL, 
            0x1E77B812C52AB96FULL, 0x7A6DC02A5F7BEA49ULL, 0x10E4C4F1C320421BULL, 0xE350223BBC21F997ULL, 
            0x040F5CFB16135AE2ULL, 0x68978436B63EC553ULL, 0x9A7EB66798105DA7ULL, 0x27FA20C905B5C08EULL, 
            0x14E19A5267559E5CULL, 0x5DC8C1FDE79BBB58ULL, 0x03756B9CCB92A238ULL, 0x6FEA7B9531930E9AULL, 
            0x4A6D8DE8D73C909DULL, 0x5395679346C0B934ULL, 0x39AC1004A58CA217ULL, 0x56C2867AE6B5B136ULL
        },
        {
            0x94611B347C967E37ULL, 0x9A0F681E8D700619ULL, 0xA2E2D72EFDBDDE92ULL, 0x0D1EFA81B51A6608ULL, 
            0xA91B777DA26F4FBCULL, 0x1C00057864467BBCULL, 0x7DC5710D9D6D65ACULL, 0x4A953CAD605A0376ULL, 
            0xAE8DD081C2896D29ULL, 0x1D186E210CD684E1ULL, 0x659842499D64CDD3ULL, 0x95F9BF7DD0E6FD1BULL, 
            0x74B866E6EF14461FULL, 0xE2863DD73CD499F5ULL, 0x3E81C12745A9E85DULL, 0xAEE36860EA6A0D26ULL, 
            0x19D104BB77F85E25ULL, 0x98D096FFCEC37DB6ULL, 0xB2B130A3A86B8CE5ULL, 0x7DF40C9FD33DD288ULL, 
            0x25D24E11EE84F9E7ULL, 0x92A4D4E474E1864DULL, 0xE84BFE682F783588ULL, 0x3C96AA8EC6349231ULL, 
            0x17E2C148C9C88B2DULL, 0xD715E9D2EBD6B7D0ULL, 0xF71F1C420F72B4B3ULL, 0xBFDD7A516DCFD4BCULL, 
            0xD4F26066957A8FFEULL, 0xB22963C8264511A9ULL, 0xE14D02C5731551F3ULL, 0x372250FD298FA813ULL
        },
        {
            0x69886FD5B2D98B52ULL, 0x4C740B683A8D5769ULL, 0x37D618DAD2DA81DEULL, 0x345923DFF7DB1AA8ULL, 
            0x5EE6F4726317F191ULL, 0x5347D78F0258CFB1ULL, 0x599702FD276FC5D2ULL, 0xBEE0E90F44E588F6ULL, 
            0xF752718A60E9D87EULL, 0x5CEF379ED9E3DD80ULL, 0x5026EB77EE22CEBFULL, 0x2329D95A7E49BC71ULL, 
            0x5CC6BA200A13BF81ULL, 0x4E50215BDDF67D61ULL, 0xE4E456A2F9DB4CDEULL, 0x3272B40CBEFDFEA9ULL, 
            0xC0F87C74CC32E4F9ULL, 0x89F58E4EC7ECF0B9ULL, 0x00563CE1BE2F54BBULL, 0x0909E65CFEE6793DULL, 
            0x735176852E076E43ULL, 0xDE7811671FB43C8AULL, 0xE6092A6FAE41A77BULL, 0x99B9B74E6807E061ULL, 
            0xE45C59405777C77AULL, 0xF538D294F3CA76F1ULL, 0x086EDFFFB3FE27C9ULL, 0x6A7D34BDB2B1DF8DULL, 
            0xA936AA3E6683A313ULL, 0xA0D2505AB7978AA1ULL, 0xDBA1427C2904CAA0ULL, 0xC82C777F49353D64ULL
        },
        {
            0xAA29E38060C90B06ULL, 0x7F3DA6B937ECD14BULL, 0xCBABD7869F7C64A8ULL, 0xC056C44D1C947A19ULL, 
            0xD1E67D75C2B42428ULL, 0x17F91399C25D4818ULL, 0xAB5F5F54CBED485EULL, 0x958C1268E08674C4ULL, 
            0x3CB3390F6082C863ULL, 0x0885706F4BF567AAULL, 0xF124934A9C2FC4BEULL, 0x1A7AC8D1434D654BULL, 
            0x2A34FE771D415BDCULL, 0x35C112C902BA5301ULL, 0x7728DE33D395AC3FULL, 0xCDEDAF06E52F648FULL, 
            0x69CEF40FF4F24D1BULL, 0x1A3E91A04387F2F9ULL, 0xBC5D0E96421BA63FULL, 0x6C233D251445AA25ULL, 
            0xCC500ABB2E753AA5ULL, 0xC7060970D77F3D05ULL, 0xD4BB48B634FD3A92ULL, 0xF593BB23F1B94AD2ULL, 
            0x0CD2C8BC9E6DFE87ULL, 0x9685B1942F289956ULL, 0x04A6FCAE4CD2DE90ULL, 0x3AC0E9C2F21EE207ULL, 
            0xF1A7096EACC3B6F2ULL, 0x730F32E2CC9E15C3ULL, 0x4B59AB08BE3A998BULL, 0x692B795F09BAA300ULL
        },
        {
            0x3AB093EA475A77E5ULL, 0x9A0BCB22D156B316ULL, 0x4670C2DDD2587749ULL, 0x7582D2C19CFA90ADULL, 
            0x0A9447C0103E528AULL, 0x3E30C63CF97271BFULL, 0x6997FC648A96E43DULL, 0xF734926C8D95CF01ULL, 
            0xB8EE0CEA88C3165AULL, 0xF540FE6B594330E3ULL, 0x766BCED41F71C571ULL, 0x4CF3BDC0F4AEAD06ULL, 
            0xFE7C79118E1983F5ULL, 0x204457E9E6603898ULL, 0x1922859F3FA93C43ULL, 0x783662092ECC90A1ULL, 
            0xAC2E0272F694BB03ULL, 0xA8964B4DA72B92ECULL, 0x0ECCF24E5D61AB08ULL, 0x5FABBAC11CB866DBULL, 
            0xF9EA34622732B7BCULL, 0x03708F8FA4EABE7FULL, 0xE8A8D0ECBBA4A206ULL, 0x65B91889748AF289ULL, 
            0xCF2E8D3FE98203F0ULL, 0x709D86AF0C8D6DBEULL, 0x84DC0A05877194FEULL, 0xEC888E40C73B2D87ULL, 
            0x0126C04FC5D9D768ULL, 0x0D4407CBB613608DULL, 0x3A6AC25669CF88A8ULL, 0xD1AA11378DDDA371ULL
        },
        {
            0x7BC32A45D2C7E30AULL, 0xF96A3E950C5AAEBDULL, 0x703FC1D266B5105DULL, 0x1EAB2D140B6A24FAULL, 
            0x142DD2BFA5F88DCCULL, 0xCA7EEC1309A49B9DULL, 0xDB4BAE6BBAE62F89ULL, 0xF05BD6F4E8DCCBADULL, 
            0x02472F88851DA065ULL, 0xC17A7EA43E8F1876ULL, 0xCC5F6F76B42C6AABULL, 0x09E9A7B8AA22BA54ULL, 
            0xB13621AF977DE0C2ULL, 0xEB5E4F6D6B3C9DCAULL, 0x12374B400B677A90ULL, 0x1EC3D842F8B7F93FULL, 
            0xD061D1087E6724D3ULL, 0x7CC77780E091C763ULL, 0x0089CA95FCC8B6FCULL, 0x0CC6F6B0091F4E0DULL, 
            0xD5A3B36FCBF03544ULL, 0xCA4A1C9678EB611DULL, 0xB4D7E426A55F025AULL, 0x47E4BD714A10A202ULL, 
            0x0F0F30DACED35C83ULL, 0x21C09095F58E4812ULL, 0xA6F42D4292BAAF2DULL, 0xB1A413055DAD04CBULL, 
            0xB2AFC5B0F4E0C77AULL, 0x9B4069983440D44BULL, 0x708F0FB96C26CFA7ULL, 0x4D9DE6BF3D1382D9ULL
        }
    },
    {
        {
            0xE6C369FC7BFB220AULL, 0x27CB65914646AABAULL, 0xC81488E959F73982ULL, 0xE7A034FCC58A92F9ULL, 
            0xF480C57D39457DAEULL, 0x90150BE7021AF90CULL, 0x654FC3DA30E0DD00ULL, 0x16965D103E79E257ULL, 
            0xEC892DBF4C0B13A9ULL, 0x278918A70CBA81ACULL, 0x04C410E7B74619EDULL, 0x8D3DB46AAF6932F1ULL, 
            0xE738D41216BA0C5CULL, 0x3D0CA0D45F4F2C86ULL, 0xD91906FBB23A5629ULL, 0x255ED3A8BB31B8F6ULL, 
            0x522EE4D1AC9D262FULL, 0x33D916C9F7E1D99DULL, 0xB6052DD89FFDC0E9ULL, 0xC63B9D74B720FD68ULL, 
            0xC029B42BBAE55C51ULL, 0x9BE3807CF1C71E63ULL, 0x2401222EAE0FB6A7ULL, 0x99C9D55F2B24F3B9ULL, 
            0xB73127F8E6C87700ULL, 0xF2FF70860B2D647DULL, 0xF68193E5E734A0D8ULL, 0xF1A8553AA4A7D8DEULL, 
            0xEC1A45361E62B979ULL, 0xA46C8C1E5FFA7136ULL, 0x04E2A6779F537A8CULL, 0x8F179B2C23170974ULL
        },
        {
            0x012F82E8137AE47BULL, 0x331DE86F62F4475BULL, 0x003BE8844F2D215BULL, 0x89C826CD61EB8370ULL, 
            0x8E7CA47FC69F0E81ULL, 0x83581BABC8512788ULL, 0x311DFA90542A25E7ULL, 0x0DB0C33E975A1215ULL, 
            0xB8FC1C0A442F5F8DULL, 0x3187459982A01DC4ULL, 0xE675A20F7E3F429DULL, 0x74A5C704552CCEB5ULL, 
            0x043C3AFBFDAC4C68ULL, 0xF8636F801C1C6599ULL, 0xB6143A2E45B876BEULL, 0xF69473EC0D9E0CF0ULL, 
            0x6871D83AD063B032ULL, 0x31E561424B8B0502ULL, 0xF4A0BBE247859170ULL, 0x4038EB5F4C21466DULL, 
            0xBCAC0537B3F4C31EULL, 0x97891456F7D8B221ULL, 0xA5BB66A081BA26CEULL, 0x733D76AFA8F8EF56ULL, 
            0x3F6788B244835A4BULL, 0x88D05B8D483DE550ULL, 0xF507D40BA6F53463ULL, 0x7FF49E656239F214ULL, 
            0xA355A5354D32CFE4ULL, 0x501560910D75891DULL, 0x560DC2ECCF2BA524ULL, 0xABC915DEE3519A99ULL
        },
        {
            0xF26480685B9D6D51ULL, 0xD1C695CEC64B85FFULL, 0x75790A3B3CA13CC8ULL, 0x33923A676448DD57ULL, 
            0x9D3C3E758FC42BE5ULL, 0x19A20437CA76624BULL, 0xBEB4704A139075C7ULL, 0xCF2BF0D5C261C368ULL, 
            0x23ABCB07C7FF367DULL, 0xC20EB2A2309F124BULL, 0x3B3FF141D994DCF7ULL, 0xD8531EB6ABFAE5FEULL, 
            0x9B76CCFCA9469EBEULL, 0x51D2D4BC92B0CF15ULL, 0x09E2C643F95F0B1CULL, 0x6904613FA19B0B66ULL, 
            0x7E929C308EA85844ULL, 0x210C00173EB9E11CULL, 0x115B3F861C9477C9ULL, 0xBE69329307B1EFEEULL, 
            0x08CE8A27F321539BULL, 0x42CD5EB43D86A948ULL, 0x32A0172AF2BDB5E6ULL, 0x6B134151E7DB212BULL, 
            0x7F9B987760D08217ULL, 0x5752762A6C5CC258ULL, 0x2F22B1C42EDB2125ULL, 0xAB5254478D30C03CULL, 
            0xBFC3F3D0FBE967B1ULL, 0x7576D32D469DC8ECULL, 0xA53BAD0660DD1CB1ULL, 0xE458620B27AD70E8ULL
        },
        {
            0x1A8A42F382574C00ULL, 0xB07B5BB95DC56DD5ULL, 0xA4DB11539CB35A3FULL, 0xD92AF9AE6A6C4C12ULL, 
            0x70A761AD6AC0B533ULL, 0x334C657A94EFC202ULL, 0x89B96CDFFC67176DULL, 0xCB45D11938D3C1BDULL, 
            0x96905919619B48C6ULL, 0x2B599EAF93B5D27FULL, 0xB419DCC574FAF96FULL, 0x5C88D45FC16D63F4ULL, 
            0xECA428E53150EFE6ULL, 0x0D87C3FF71A76BB7ULL, 0xDF29D01B8FBA2251ULL, 0x62972609E5821FD9ULL, 
            0x28C7F2A8D43A56F5ULL, 0x2FF5F0C30CED9823ULL, 0x47281039F89548EFULL, 0xB11E886A7587FF8FULL, 
            0x6CE2EA13C93B06F8ULL, 0x136FB80DE2E341FDULL, 0x326FA6A40DB77815ULL, 0xE6FACBE499D605BEULL, 
            0x745195CA98A2CBC1ULL, 0x642A22B89A3404D8ULL, 0x45C6C9BC6E831273ULL, 0xBEC5BD2FE3B0A07AULL, 
            0x64D75AA1F6D57E4FULL, 0x036F0282248D260CULL, 0x1AD462ED017B053CULL, 0xCA82361685968727ULL
        },
        {
            0xA0B469A713B197D4ULL, 0x41A1FB4DB22FA697ULL, 0xC7F0CD940E4DEA7CULL, 0xD0AA62736E36AE82ULL, 
            0x3CBB180002AB8B45ULL, 0x80049588C4703701ULL, 0xA9351841F0792AC4ULL, 0x2B2682DD36712ECFULL, 
            0x591931148AC3D617ULL, 0x72E61546A60AE138ULL, 0xD159A7C4BD005790ULL, 0xCB79C5F6FC4F6E7DULL, 
            0xA99156EFAC6CD385ULL, 0x9599F14B3C2A619FULL, 0xAD7A184146F1BC8EULL, 0x12EB511272448A1CULL, 
            0x32BFAE1CAB3FB797ULL, 0xAD58A0C69C6DA566ULL, 0xA174875D49242320ULL, 0xA84DACD7B5ABBFEEULL, 
            0x08D434BABD0AEC34ULL, 0x2E98D4C3CCE7CA80ULL, 0x0B1F993DBBDB16A9ULL, 0xA541EED08D2343B4ULL, 
            0x47CFE62CE8A4F25BULL, 0x8C9E47A4EC60FAC0ULL, 0x4CB77B1FF2C15E08ULL, 0x01763F9F6BA4CF28ULL, 
            0x649D62A89FA3C623ULL, 0xE193BB8715AA3FF0ULL, 0xF94A7B7814B4E330ULL, 0xF6E9A1BC287AD2BDULL
        },
        {
            0xA8D1838CABF6C087ULL, 0x711E3D281B24D462ULL, 0xF7246733B5A1E824ULL, 0xE700C75C9EF779D5ULL, 
            0x50C746F59190B506ULL, 0xD8FD95C088607339ULL, 0x1DC3558D8E37D3DDULL, 0xFF2E95D043C49840ULL, 
            0x72A49D1808C09039ULL, 0x036E33E5885138D8ULL, 0x1D7FF65AF7AED09AULL, 0x5F8D2D2C756DA5DBULL, 
            0x7AA87E9F71BC9EFEULL, 0x0222C74A58B6AB6BULL, 0xBBB0C86327F95659ULL, 0x365706E3B48422CCULL, 
            0x735CB570CA5F34DEULL, 0x93CCD5FD253B04A5ULL, 0x3CC905EAA9F79803ULL, 0xE47A07C7D9B08886ULL, 
            0x126E1A4CE5C94B95ULL, 0x034313460B31EB9AULL, 0xF4C5722D6CC261D3ULL, 0xFA973FC9572F72ADULL, 
            0x4C49B8205276A34BULL, 0x69BBDD941E2165A8ULL, 0xBFE823E0AD74EDC5ULL, 0x3CC07C0193C3D55EULL, 
            0x42DD0DD4044F45B0ULL, 0x91B37F80EFFE70D1ULL, 0x14F33AF981DEC642ULL, 0x2BE30F36C3F98A86ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseAConstants = {
    0x841A050BECC77201ULL,
    0xEFE6D3F49E13A46FULL,
    0x8C3B9B095933E39CULL,
    0x841A050BECC77201ULL,
    0xEFE6D3F49E13A46FULL,
    0x8C3B9B095933E39CULL,
    0xA5DD976225F0E7AAULL,
    0x21938170000F0B0FULL,
    0x9B,
    0x03,
    0x06,
    0x3F,
    0x28,
    0x55,
    0xE7,
    0x37
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseBSalts = {
    {
        {
            0x95F02BBB2DB67360ULL, 0xFBA647D039C5FC41ULL, 0xF4DA27E054D92A22ULL, 0x78217E2A1B9CF82BULL, 
            0xD17D6307950CB4E1ULL, 0x2583203D79861BF4ULL, 0x4E3FB96BB108D48CULL, 0xB7599356E583ED00ULL, 
            0x11862306381AE035ULL, 0x7BAF84CB58501F70ULL, 0x38A90BE742131D3CULL, 0xD86DB5CC92065183ULL, 
            0x054A5E56B352BE6CULL, 0x5E5147768A41B8CFULL, 0x4BE0CEA619434909ULL, 0x09F4DF8E3D0057AFULL, 
            0xA9C630A260E1A7DCULL, 0x2BE26F038EB09A2FULL, 0x4D93E8B762B6B80EULL, 0x59CFE1F621B84D6EULL, 
            0x377AF44F65222690ULL, 0xD5E70D8151B343B4ULL, 0xC3C5B10C3284892BULL, 0x2BD0DE04649E8981ULL, 
            0x182FCDF3E8D03953ULL, 0xAD766F8326F3F5ABULL, 0x30A15B5AEE6DB291ULL, 0xFC66B78515D6A834ULL, 
            0x78AEEFE1776B6515ULL, 0x64037FF9E09C7C7DULL, 0xC030C056F456E7F1ULL, 0x115C5DBBF9A4C007ULL
        },
        {
            0xB419F660814A08BCULL, 0xC09AA1C0554F8085ULL, 0x82B0F975AE6C5833ULL, 0x73E3356A30087E04ULL, 
            0xB2677329CCEB0010ULL, 0x3EBCEBE18FD74D92ULL, 0x216647943D244EB3ULL, 0x4FED486E99E575B6ULL, 
            0x7A3E9A0DF4B0503DULL, 0xD168CF167760A38FULL, 0xD54A5DFC8BECAE02ULL, 0x852C378100905EECULL, 
            0x45424F9ED6A60FADULL, 0xDF54A1161FC52881ULL, 0x6BEF17C74A34036CULL, 0x85386F9EA858C264ULL, 
            0x0C06E1B467309574ULL, 0x61FB8D4BDEAB9107ULL, 0x3366EDC79874E4EFULL, 0xEE0C066BE24C4ABAULL, 
            0xB17CEDC225D56844ULL, 0x3C942AF654F08810ULL, 0xD5F9E5F3BA852AAAULL, 0xF5956276549AC4C2ULL, 
            0x00BBDD8B4BDB2CD5ULL, 0x937150391F721D15ULL, 0x83448136FD7137C2ULL, 0x880A0BF23040F065ULL, 
            0x04F1A88EBDF0EDACULL, 0xCC8B873BF63B589EULL, 0x52494E7ED1182F8BULL, 0xE80E4E0EF7F0CCFEULL
        },
        {
            0xCBE5B8C8D03B9208ULL, 0x0D8B09086197202EULL, 0x5B696E439C72E1DEULL, 0x916E21993EE8EB13ULL, 
            0x561D5C7D662A33D8ULL, 0x3124282BBF82B7AAULL, 0xD0FBB510C97B3362ULL, 0xBF38C64DAFEB13A7ULL, 
            0xB5633A01B7BF8B4FULL, 0xACCC53DA8E8BD93DULL, 0x6B872E4E3CAE4D29ULL, 0x294775777122ACA5ULL, 
            0x22C126B118933DE7ULL, 0xDF8D84560020E44BULL, 0xBAF73BC233F41B2EULL, 0x5B8EA643963D41EEULL, 
            0x4786503249F2FEFEULL, 0x9FB08427D1E075EFULL, 0xE580B793854774E7ULL, 0xE326A8AF31DFFF04ULL, 
            0x4441283BF456CC2CULL, 0xC2E2C15DE6D5403AULL, 0xE24E3C27836F15DCULL, 0x490088E2F874F977ULL, 
            0xE93C52EB778156E8ULL, 0x81F4B9702A15EDB8ULL, 0xFA6E695813A26251ULL, 0x8C5E6610BA98FFB8ULL, 
            0x950A81AADC8B75B2ULL, 0x621B3681B2331867ULL, 0xC5DD9F36DD577827ULL, 0x03AD86AD6C8D92BFULL
        },
        {
            0xE9996384478AE95FULL, 0x519850107F37F5DBULL, 0xAF9182B6213F3F78ULL, 0xAAAF7E09E1D583D3ULL, 
            0x37643C46A98476BEULL, 0xFD615508DDD9DDF2ULL, 0x34037678F78A91B6ULL, 0x462DCF3853E2B266ULL, 
            0x5B3AF6AE9DA97DC1ULL, 0x943993CBBF67296BULL, 0x81D1C37DFCCB8C87ULL, 0x25759C214D09165AULL, 
            0x7C8839F1B277F54EULL, 0x9081395FB8501C0BULL, 0xA9DC7678C7EB00B4ULL, 0xE7131927B41507EBULL, 
            0xD8654DE1B58E58E3ULL, 0xF189DE1062DA189CULL, 0x35139B8D125C139DULL, 0x10437FE389DA1313ULL, 
            0xCA612D2C3FD55C01ULL, 0x4196C51007274B50ULL, 0x4E5FD159ACED3C03ULL, 0x6B9C5F11204E7A46ULL, 
            0xF3D2642DFCD03E0DULL, 0x3AB66BB5572FF755ULL, 0x703572A2CD16ED7FULL, 0xAF4336DC72BC90A2ULL, 
            0x489C051FA76B31C5ULL, 0xAB14BEA8284A7493ULL, 0x349B080A759BD720ULL, 0x04D82CE0CD05E26AULL
        },
        {
            0xF6BE7C23B18EE8FDULL, 0xA08B1AF34A04B2E9ULL, 0xE563127776A9FF5DULL, 0xEBBFF37C741F02A4ULL, 
            0x7FA127FBF940202EULL, 0xD682300E04DD4CC6ULL, 0xB9764FAA3E426D20ULL, 0x11CB41D07324029EULL, 
            0x4E2AD42E205C03B5ULL, 0x144565CEE2D1F022ULL, 0x6BC48FCE5569689AULL, 0xFF057CF05B540036ULL, 
            0x34D089628E3F8A14ULL, 0x4B4755A79350712CULL, 0x9ECF48AA717BFF6BULL, 0x02817860CFF6CFFBULL, 
            0x81F3DC92F379E986ULL, 0x6B909D8CE381EB2EULL, 0x0B87898515D996D4ULL, 0x27BF47717149191AULL, 
            0x162F9D3112A45891ULL, 0xA498C31FE2C90E4DULL, 0x351142F47F144B85ULL, 0xC63A4592A8C47F10ULL, 
            0x820371B947564B1BULL, 0xFCFA0EC92A1BC84EULL, 0xDC11CCB22669DDA4ULL, 0x826082832E43D8ADULL, 
            0xFE79BE7D92085B8CULL, 0x1D36506633014976ULL, 0xC15004255A1E6DDBULL, 0x002B34A5064FB107ULL
        },
        {
            0x88D46FE6FDE6B6EEULL, 0x0CCA56DFBF567F25ULL, 0xBBAE9C87B65A3B13ULL, 0x2B687844650AEFD4ULL, 
            0xBF1DF658CDAB05C2ULL, 0x6ECDA725629E3571ULL, 0x4CFC6B8E50264195ULL, 0x17CCE5669E6A2BFAULL, 
            0x809D38FFB0D6958DULL, 0xDC872E4CD32A0243ULL, 0x8E720B17C44415BCULL, 0x5FA8AEFCE5922CEEULL, 
            0xB9E5B3D55FD190AFULL, 0xE34F415672FDC5DEULL, 0x2F578583E9988E5DULL, 0x5133DE19239A21CFULL, 
            0xA17435C9115260D6ULL, 0x12AA839A7A935AF5ULL, 0xEB1412D9A31EB517ULL, 0xE82C3FE30AB36A17ULL, 
            0xC242438047658690ULL, 0xEBA2059DDA65655DULL, 0x3B7B362A7B8DB442ULL, 0x00BD023CD7951196ULL, 
            0xC004450E41B8B624ULL, 0x3A08A765A513120AULL, 0x3828862E13EB4D1DULL, 0x280D891C16CC00B2ULL, 
            0xBAE0E396273B918FULL, 0xCCAEB65A501481F9ULL, 0xA2F517DC8A5A9CB4ULL, 0xCA8F3B0219E569FFULL
        }
    },
    {
        {
            0x43932CFC1F9B49F3ULL, 0x660D4B7BEC25B08CULL, 0x77B93431DCB0EF2BULL, 0x13CAC584D8413297ULL, 
            0x154DD8068C132E3AULL, 0x9A8A5376D8CC40DDULL, 0xBC5030460A4D9E19ULL, 0x99530549ECCB4061ULL, 
            0x600C3E5FA2DC73CFULL, 0x90D558C578B7713EULL, 0xB828BA1FFE6575D2ULL, 0xB226C240A91DAA53ULL, 
            0x20A022C4308B08F0ULL, 0x6BBAE493484A1453ULL, 0xC80A19052447E0E3ULL, 0xF813DC8D3647EB61ULL, 
            0x94EDC1D215EB91ADULL, 0x1B7F4D57E6306989ULL, 0xAD5C6CA475916253ULL, 0xC0681DE3021CD7E4ULL, 
            0xBD4202DB7F6A0584ULL, 0x590AA8AC4C063F29ULL, 0x76740A48F772CF04ULL, 0x650034D9691B3DCEULL, 
            0xA580B82693F05A90ULL, 0xB563497F76FF2A27ULL, 0x8F06804BFD4BC345ULL, 0xB8B9A0215159FD9FULL, 
            0x98E79F779F44FBC8ULL, 0x051BA44187A7FDA9ULL, 0xA03775E2CFF25940ULL, 0x7ED9B7527D6C079AULL
        },
        {
            0x538AAD15246D93D4ULL, 0x239A1F219FED6979ULL, 0x78CE0F13935EADE8ULL, 0x2240E5F3516EFD6BULL, 
            0x04D4095F4D1F48BCULL, 0x645B7591F82AB981ULL, 0xBF79303402824EAEULL, 0x6D05601493976A77ULL, 
            0x0D529A575AD239EDULL, 0x192F4D2159F15380ULL, 0x8F863A8CA5B4BDF6ULL, 0x64E7A4B40028EF4DULL, 
            0x60D4D2329002D05FULL, 0x8674BE76337EF661ULL, 0xF51150D582E03661ULL, 0xED680559ADD147ADULL, 
            0x65954E2365734F05ULL, 0x0D4E1725324D3E5FULL, 0xF228F0B40DF4D3C1ULL, 0x65E2FB60E3AB037BULL, 
            0x594AC1C07CC15D4AULL, 0x1D60F9818100BBF0ULL, 0xD9CDDDD448965F68ULL, 0xAD97C7A03B2261D8ULL, 
            0x3143D9875F527FE3ULL, 0x4B74885D0117D8B7ULL, 0xD24335627E70C862ULL, 0xA9F220CAD7217058ULL, 
            0x14C3CDA9189C245EULL, 0x9734DD4BD75CE40CULL, 0xBA09ADD7A29E8130ULL, 0x000D9BCF054A989DULL
        },
        {
            0xB8956EE72C440C0DULL, 0x0E4A5585BA7F14C4ULL, 0x0ED50B62E6DF3C5EULL, 0x502FAB3BD97A8FFBULL, 
            0x139506D28CFB9A27ULL, 0x930443D2D6AF43F1ULL, 0x5071D7285A4CB0A5ULL, 0x798370FEC4FD4BBEULL, 
            0x7ED70DA6A40E0E71ULL, 0xFE0F5832E451B867ULL, 0xE27FDC6A587BFFE9ULL, 0x63919244CA3F1749ULL, 
            0xD7DCDFB5F19C945BULL, 0xA3FB59916FC87848ULL, 0x2633CCBF33F77516ULL, 0x9C200A4260277EA3ULL, 
            0x66062E2797A51B2CULL, 0x82AD49E10B1CA83FULL, 0x306395A13A1890AAULL, 0xCBFB70E2053A64C8ULL, 
            0xC3D1CBF04BC53E40ULL, 0xF4B5D127D22ADB84ULL, 0xE121DEDAC8A42348ULL, 0x7D04C0D0213C228DULL, 
            0xCF952F38695F9234ULL, 0x3A87283A83B4D5CDULL, 0x768D8B2D873CB241ULL, 0xC1E1EC3BFE0EFCA6ULL, 
            0x8DEF563F047F0F06ULL, 0x79AF264FE8FA0AC1ULL, 0xF2F766113725DEA2ULL, 0xBE1FD42D861FD814ULL
        },
        {
            0x64DD4EE247F8F943ULL, 0x3F6A322DAC682FF4ULL, 0x292203E823AF14C8ULL, 0x0DE1649CA0C929B2ULL, 
            0x6616FD595F41F200ULL, 0xA1103F8AE9EA638FULL, 0xC17474710C5CDA29ULL, 0xD53EC11F8CB0FCD2ULL, 
            0xF4EB070F5B458342ULL, 0x64AD910ACF136759ULL, 0x486CEC9930D1DFF7ULL, 0xCF45BD6BC52DD0E2ULL, 
            0x703B47A4B39D9F87ULL, 0xEA7463E8FF6778E5ULL, 0x21A67BA8872CF402ULL, 0xBA51F3754DD15EC6ULL, 
            0x59044CC5109D58C4ULL, 0xB68179CCA1978F70ULL, 0x41F2A767DAB5AD44ULL, 0x185BD67F801E6D4EULL, 
            0x935DDF8FEA4EB04FULL, 0x14C894CB9135109EULL, 0x89EB9726CB8EFC6EULL, 0xDB69BD728FCF7F5FULL, 
            0xBDFBF7E054F453B9ULL, 0x2E1E17BCB7243C8BULL, 0x53D5B92FAB16BC53ULL, 0x09CC8A2B93E65734ULL, 
            0x6EAAE96DBC023DA0ULL, 0x87B3783483F54345ULL, 0xBA2341553469181BULL, 0xF24D5124A5C15E40ULL
        },
        {
            0xCCC440A5C7E4725BULL, 0xE2E5393A59D780EAULL, 0xDCFF93569666E212ULL, 0xB851DBF082DB229EULL, 
            0xAD5966D7BF22B7AEULL, 0x3A0856A0806E1111ULL, 0x5FE33A1703CDD65AULL, 0xD1AD1B35FECEE235ULL, 
            0x40BDBF14F9BF0A19ULL, 0x2EE5A57BBEA84293ULL, 0xA003A349941B0D5FULL, 0xF20560F7C4B59E8FULL, 
            0x9AD7E3BB6DD328BFULL, 0x6BD32D7C350718EAULL, 0xA6458360584142B9ULL, 0x3E66659DABE8312BULL, 
            0xF41E4E6AF806C3B6ULL, 0xD446E92A5C036B12ULL, 0xF0E11AB0CD5D3673ULL, 0x958095020B811947ULL, 
            0x3F50C607A0ECBA9AULL, 0x89F35B64ECB60FCDULL, 0x871A4B062C03FD92ULL, 0xC122003FEF810621ULL, 
            0xDC981EEE6388B411ULL, 0x3ECC1E11FA48B07EULL, 0xC5E21C48BF1B5B52ULL, 0xA7C03132586B628AULL, 
            0x7413450F44575EE7ULL, 0xE9A926DDF3D72FD6ULL, 0xC24283F8939EA28DULL, 0x8724D59466F9CD76ULL
        },
        {
            0xA4E8C1295C09BEA9ULL, 0xCCCAF80CF6583D4FULL, 0x79001E02EAF1F256ULL, 0xD7D0D81C460FDD12ULL, 
            0x4380422DBEB4286AULL, 0xF3CF70020DBBDADFULL, 0x83BEB25D5B133DBFULL, 0x69E8706C1938AD69ULL, 
            0x7339977C7D986A44ULL, 0xD044DDBE0ABBEFE8ULL, 0x3DAFFC1045FB6D90ULL, 0x181BE726C6E88D12ULL, 
            0x22608859F7DBFCCCULL, 0xB0E3912E2FDA4065ULL, 0x5ED3A21C44D30413ULL, 0x3394F3BB79535759ULL, 
            0x2360B254D4B2AC40ULL, 0x679B9709014C0240ULL, 0xF0411375A4C9F35AULL, 0x07BE780042EB24D4ULL, 
            0xE790673AC0EBF794ULL, 0x152ADC482A0BD15FULL, 0x2D2095A40478F756ULL, 0x99B4C3075BA20681ULL, 
            0xAC02D2DE9FE8B6EFULL, 0x6C4DA9467275EE04ULL, 0x9156BC43C389F20EULL, 0x3A5E453E2920FEEAULL, 
            0x158B7FAB45A19180ULL, 0xC3DF15517772D9EBULL, 0x3BE6CEB719462986ULL, 0xE93F5AD73BFA47F8ULL
        }
    },
    {
        {
            0xA42A839BDA698B18ULL, 0xF18D9889416D76E5ULL, 0xCF5FA8E2D58EFB19ULL, 0x24A61B6C88074A8DULL, 
            0x45D1530AC00C2E51ULL, 0x1EFA4FAF9436E5C9ULL, 0x64D2A589E55870F8ULL, 0x8DC2BE85E2D9CAE2ULL, 
            0xB19F84A02F2DFD7DULL, 0x497197D028C31222ULL, 0x3721E94947A2B951ULL, 0x79DD6899ECBD56B8ULL, 
            0x0DB090FE122F40F5ULL, 0x14D74BFBC1D26BEAULL, 0x1D524786E5E0BEBCULL, 0x926BADA17BA48255ULL, 
            0x83A70BD276805DACULL, 0xB0E023306F26EC02ULL, 0x7F87BB2581251CF2ULL, 0x2AC41416AFC9FD6CULL, 
            0x0FA43908EE963939ULL, 0xC78EA9D5E310E9BAULL, 0xCDC41B0AFE059868ULL, 0xCC13B6ECE90B3D2BULL, 
            0x7CCB26D9BA0E51BFULL, 0x6FC524F789CDE0C7ULL, 0x48039AD1B9100C32ULL, 0xF6F6A396ED4A8260ULL, 
            0xFFE43F2C881DD05BULL, 0x066F4BAB9A97E2B6ULL, 0xD191B4DDBF125B56ULL, 0x33EAF695EC3A4A7BULL
        },
        {
            0x81EBA59C720D4F53ULL, 0x8E4F177002B33B92ULL, 0x359861DE3CA60026ULL, 0xAB3D419F2715DD43ULL, 
            0xFAF12F6814645F03ULL, 0x123E80039306B820ULL, 0xBD2A1048C48C34F5ULL, 0x82D6978B0A70FF4AULL, 
            0x6D0E508BD5AFBE6AULL, 0x630E8A69F454F18CULL, 0x83AD28D5F846B35AULL, 0xBB2139BE068DA262ULL, 
            0x70948E1C487E74CEULL, 0xB3528EB0022E3DE0ULL, 0x0F2D5474CB34FFF4ULL, 0xC7A41EBC656B24DAULL, 
            0xF5EC84AD3755EB01ULL, 0xB0514D81A25FA246ULL, 0x9C5CDAAF5CF23ABAULL, 0x50216F3BDB9195C1ULL, 
            0xA5EF8E6ED9F85D5CULL, 0x1AFCC914712B9BFBULL, 0x67E577521AC1D63FULL, 0x88292438E9A2C099ULL, 
            0xA66089245F256BBDULL, 0x36B4F2F1119DC7F0ULL, 0x01055218B62C81E2ULL, 0x55CA45FABD56AE22ULL, 
            0x8ADEE9879EC38459ULL, 0x12FD3D706A6C29CBULL, 0xCFF92E65F1E6B0D9ULL, 0x3B37DD8D32A9530BULL
        },
        {
            0x062DC8C033B80FC5ULL, 0x93D944EABC978915ULL, 0x7064EB09263162AFULL, 0x6ECD7AF17930CBF1ULL, 
            0x6917459F4FC082BAULL, 0x2B89ADFB238AFDD2ULL, 0x4D1B55710D7BEC31ULL, 0xBEF100EE3E752B7AULL, 
            0xFCED93BB445787EBULL, 0x7BD2214A00A9F0C8ULL, 0x0B301724F70DEC86ULL, 0x701FFB900FF00CCBULL, 
            0xB9B7BE33CD4AF505ULL, 0x6E47A9934B21B95FULL, 0x244F0F40C3EC2764ULL, 0xBCAD41CC120B452DULL, 
            0x43113DAB04C3BEC1ULL, 0x784AEFA392D4D435ULL, 0xE2BCBE8027D71F10ULL, 0x354A43C54E84B6D6ULL, 
            0x106D950EDE34D783ULL, 0x1CF04972F61726BAULL, 0x0872ACB7C1425D11ULL, 0x616DE1FEF00D20E8ULL, 
            0x20A8CFC4C357D4CFULL, 0x0215A7342CCAF215ULL, 0x03F2244782375615ULL, 0xEBDE8CC0562BB12DULL, 
            0xBBD124FBE8EA908EULL, 0xE0DFE2334C78ADCCULL, 0x9AB4EA3CC8F2510BULL, 0x736D0C1AC89FBDF4ULL
        },
        {
            0x3441C6B7DC52D209ULL, 0x78DD80758E4200D4ULL, 0xB7F3AA1ED571CA6EULL, 0x0E27339417F172C7ULL, 
            0xF26414DB478CB634ULL, 0xEFBCF5EB3280EFF8ULL, 0x6C75241668B057A0ULL, 0xDF18161784757F27ULL, 
            0x702B8B622C4646B4ULL, 0x32F7AD5A069E1AFCULL, 0x9FF9CF877251D58AULL, 0xFD34042913F4AA87ULL, 
            0xF8CE7D819C0242C2ULL, 0x651222D1068F2375ULL, 0xFA844408D42A37C6ULL, 0xCC05C6F294B43B01ULL, 
            0x4724B00E06DE0503ULL, 0xEA38894018F2E696ULL, 0x1F5557D2B5ECACBCULL, 0x1F9A67F18A34D457ULL, 
            0x6FF2E2F3969BD745ULL, 0xCA83C6D55B85700CULL, 0x4F727061290F6756ULL, 0x52CDB165A472A895ULL, 
            0x8E148FFF0DA6A293ULL, 0x9521EB5A263A3B8CULL, 0x30E9DD377640D576ULL, 0x1CEF45610A2D99AAULL, 
            0x36A921C8EE2605A8ULL, 0x951F19A7BC6555A7ULL, 0x06D708B60856A391ULL, 0x01FF8AB6E9DD9A13ULL
        },
        {
            0xE57E3D56F3733092ULL, 0x513BF5A38906994EULL, 0xE1571A88EF898BEFULL, 0xD8848A3B872CA404ULL, 
            0xEB146598AA61D67EULL, 0x029E555A0AFC02EFULL, 0x053BDC2A6D68EEB5ULL, 0x60B684064D0980E5ULL, 
            0x4B32412D01C487D7ULL, 0x77B98BB9AB39AC44ULL, 0x08DD183DDABEDB0FULL, 0xF72E88EF3F27FDCAULL, 
            0x0DCE8128343DC401ULL, 0x0A5D2ADB79A8BCE4ULL, 0xAE74BC8732FD37BEULL, 0x5A5AA01B14175112ULL, 
            0xA0D7EE480C92AC7DULL, 0x52320096E0656012ULL, 0x90749F454D9DFA60ULL, 0x9BD9F23CA3B98156ULL, 
            0x1C7B56711322357FULL, 0xF0DD7BEBB36FCC11ULL, 0xD638E418B27FD9B1ULL, 0x66FC3F8F495F2868ULL, 
            0x6C5D14D74F37628BULL, 0x63BC00B85D78F73DULL, 0xA1E18AE6F5FBC635ULL, 0x83A2EF82CFAC754CULL, 
            0xFD98D7456DC02584ULL, 0xB2310A229E6AEA1CULL, 0xE357FFEA453D6394ULL, 0x015DD2785E915325ULL
        },
        {
            0x88E964FD5F4B51D1ULL, 0x6619CC6F423DB8D1ULL, 0x181BDBCF542374FBULL, 0xB81CA7B98DB23267ULL, 
            0xB8118A137D637920ULL, 0xD3155A22D6D4AF8DULL, 0x1A2DD0A4A1D56D2AULL, 0x588B48F95D5BFC8EULL, 
            0xE66F0E2EAD3B0341ULL, 0xB436E0BA65B39486ULL, 0xD3811405CB0F4CB3ULL, 0x40F53FBCC44A2EC8ULL, 
            0x098AD159A5ED65B6ULL, 0x4E88CAB6787159CAULL, 0xA02326D3EC1F0D90ULL, 0xDB660569D187C9C3ULL, 
            0x9CB7D80CCD717A31ULL, 0xA891599335ED46A1ULL, 0xD03EAB4F8B41A230ULL, 0xBE2D22FCA000B56EULL, 
            0x64B5CE5117463031ULL, 0x14DEF233A076A2A6ULL, 0x4AF2DE8B5A6999BAULL, 0x2685E8E164D1F54FULL, 
            0xB54CA7F76F3ABFEBULL, 0xAACF42AD8FEB8B7FULL, 0x615691CDFF7739B2ULL, 0x775A7638A64730CCULL, 
            0x2712E70FF226D896ULL, 0xFD11D7E9013E88CFULL, 0x04ABEEF59230BB14ULL, 0x0A92DDB0115AC447ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseBConstants = {
    0x7AB97C75E59294CEULL,
    0x9C13B2D90256C84BULL,
    0xB43E6612D6056D82ULL,
    0x7AB97C75E59294CEULL,
    0x9C13B2D90256C84BULL,
    0xB43E6612D6056D82ULL,
    0x44C305B6FBD1DC2BULL,
    0xD8D36BFA70664097ULL,
    0x58,
    0x36,
    0xAF,
    0xF6,
    0xE2,
    0xDC,
    0x22,
    0xF0
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseCSalts = {
    {
        {
            0x83FF6ADF807712F5ULL, 0x604B990A8E5311F8ULL, 0x9DFE76324349E370ULL, 0xCEB227CCF32A4337ULL, 
            0x9B397D2AE35A8380ULL, 0x37D4EC52BC1752AEULL, 0x0A4D7702E3F33BE7ULL, 0xFB7A346D5BD8BA6AULL, 
            0xFC39DE4E509D4515ULL, 0x3CBB72CCDE7B1787ULL, 0x656789D53CEF221DULL, 0x682F47C0A10B5DA4ULL, 
            0x373CCA6E43B1E19AULL, 0xD39E30CFD68A54E2ULL, 0xF00E37406F150936ULL, 0xF63088CEA94F7AEBULL, 
            0xED2692C8C590BC0CULL, 0x9DBBFAB3A72BCD78ULL, 0xB20ED164DABBDF0FULL, 0xD13299F432462A4FULL, 
            0xFAC7FEBC1D6F4C1DULL, 0xD25F88D3A9091442ULL, 0x14B0A78473C1A926ULL, 0x38119E0B15E0E88CULL, 
            0x5A26F549E403B0B5ULL, 0x5FE2353FDCD26F3CULL, 0x6FE947CC56E67633ULL, 0x98B2AAF6AF67425FULL, 
            0x5F069E67E1AE1F06ULL, 0x23A6AA4A342615EFULL, 0x1555FAF80220EACCULL, 0xF4D442749FFBECADULL
        },
        {
            0x06587BE5A0D724CCULL, 0x856BD7FBFFF3DD81ULL, 0x69F155EE23B8455CULL, 0x66B44CD6282CEB2BULL, 
            0x797B4730529E32FBULL, 0x0F5E1AD8F4881B6BULL, 0xCE77CB739ECAB064ULL, 0xCBEDC1D56158AF2DULL, 
            0x76CA62FBDF63D68CULL, 0x688CD9AECCDECD08ULL, 0xBCC1496BC0693E9BULL, 0x6865880FD2D483A0ULL, 
            0xFD5512AC2C614C94ULL, 0xA7CF6432F68C9A37ULL, 0x91D661AA05D89D55ULL, 0x5C7142E0B6FD73A7ULL, 
            0x14CF858871234A97ULL, 0x386742EDD72B6F9EULL, 0xAB74B3E51D749D9FULL, 0x942189F11EFE3B67ULL, 
            0x986C8AE7856AA331ULL, 0x14FB100BBE40E0B5ULL, 0x46D625BA299CBA42ULL, 0xCD76A9AA5E7E451FULL, 
            0x100DCD685D4D8903ULL, 0x812AE37A6E070519ULL, 0xF6B26E9A36A5C640ULL, 0x526EA1BD30A1F7BFULL, 
            0x9D984F06346AB359ULL, 0xAE6589926FAEB803ULL, 0x0A768CAF5F9FA322ULL, 0xB5296A138DFE45B3ULL
        },
        {
            0xF02BB674CF6EDC23ULL, 0x691B493230DFFDB2ULL, 0x65155A87765C43B3ULL, 0x9ECAD3D3796561FFULL, 
            0x4739C896EC22065EULL, 0x199ED7D102D78B47ULL, 0x83A2035BD3B2D1D6ULL, 0x15D7509B4C83F2F4ULL, 
            0xE6F0D180555F09D0ULL, 0xD04FCDE2E7FEE958ULL, 0xC37A0A612F5061F6ULL, 0x348F4D6E79B0A6B3ULL, 
            0xC6AC8C5642F90616ULL, 0x4D275C5582A9D264ULL, 0x154886BD8F97EAA2ULL, 0x057331A80FB8B0B4ULL, 
            0xD862160E32F704C1ULL, 0x8BC0CBBA54E72275ULL, 0xA9B0ACB89A2061E4ULL, 0xADF42433171E1C7EULL, 
            0xB08BD34B5BE409A9ULL, 0xE6DC3EC466A538E4ULL, 0x70873E63B9D85AB8ULL, 0x20C1B181E1CFA427ULL, 
            0xEC65B1607E872DFBULL, 0x882069D3CEFD3E32ULL, 0x174FABA5E1E1429FULL, 0x7D890ECD2BCC06AEULL, 
            0x10D672878FB7984CULL, 0xF403894FC561607AULL, 0x7762B49159D42D16ULL, 0xD3C88AF55B5AFF89ULL
        },
        {
            0x010669CAEB55205DULL, 0x9BE9E8A465BDEF34ULL, 0xAD836A5997A02C5EULL, 0x2B02ECE70D9B8317ULL, 
            0xA40392F35A1EF69AULL, 0x479E34F5C9AC71EAULL, 0x5C64FCAF6B5FC8F0ULL, 0x4A14CDE5FC04E972ULL, 
            0xBE1589889D335A74ULL, 0x1B9B6E43AB14D8DDULL, 0xD19AC3B0064A7491ULL, 0xEC72910654E9292BULL, 
            0x419D70AEFE9424CCULL, 0x773407A572CB1FA1ULL, 0xCE8A1258EFA1BC86ULL, 0xEEBA502BA8EC024EULL, 
            0x51D7061AD895E12AULL, 0x735548A8C1469381ULL, 0x47488A2905134470ULL, 0x546C3AA40E37265BULL, 
            0x6276A50ADB7184E5ULL, 0x4DDB199222541EF6ULL, 0xE144E74057A39809ULL, 0x8AF8F2269950D175ULL, 
            0xC085F85B511497F8ULL, 0xFC256B68FD252A00ULL, 0x24382F08764BA005ULL, 0x75BCA3AD5DC0EBBCULL, 
            0x766D342493D8269BULL, 0xF555864E6F069C77ULL, 0x3B1F954E5BA374DDULL, 0xCF3643FE29A2F264ULL
        },
        {
            0xFB69E6B64157292BULL, 0xFA4A6CD1EF268E4BULL, 0x1E3B4F6C0FF22C79ULL, 0x678A7C7336B529DDULL, 
            0xDBB9819803B19344ULL, 0xBE1A248B2DB28A5AULL, 0xD7AEBDA3746BA6EDULL, 0x80C318358FA00242ULL, 
            0xCE50E23F3B403E01ULL, 0x10D8BEED780D8953ULL, 0x56AA5194EA439A03ULL, 0xCEFDCCDFEF061C69ULL, 
            0xBE93F52FD241ABBAULL, 0x1FE33D3C9C97DAB0ULL, 0x4515FF711942F733ULL, 0x649E94126F2557C6ULL, 
            0x50E3B49F3F40910DULL, 0x26859FA1AC28D880ULL, 0x51ADCFE35544B16DULL, 0x22C267C0B438DAD5ULL, 
            0x11B9921A911CB7CBULL, 0xE86CC1C76C9C0604ULL, 0x877DF38A4DD43F80ULL, 0x31C9902BFE771D89ULL, 
            0x28B3F877F5AA80B1ULL, 0x002BF1B1C7E7C2D2ULL, 0x8E17F79C576BB623ULL, 0x0A3751841DF815D2ULL, 
            0x4B26ACD65EC0E7E4ULL, 0x2EB8D7DDF12A4C84ULL, 0x51F45F3617DC34C7ULL, 0x9DF6D916FD3F3AB0ULL
        },
        {
            0x62DB19EEF474D3A7ULL, 0xB649A75D4C935F55ULL, 0xC48A6E982CCE3D07ULL, 0xD4F4BB979CC10B1BULL, 
            0x0E9A645134E88AC9ULL, 0xC72B16A808C7AA14ULL, 0x516AE02142E958B9ULL, 0x539CF4F3057F1D6DULL, 
            0xCC7FE08B8D55F13AULL, 0x760E5E4DEA94B682ULL, 0x78C751C761F8747EULL, 0x8394416FBCE16B63ULL, 
            0x0155310F4A392B63ULL, 0xFC795FADDED6BB43ULL, 0x1B7FB497B4E65A29ULL, 0xC38F4E800E3B3DC8ULL, 
            0x17F11AF1ABD2A3D4ULL, 0xAF35D7D40B6C3CADULL, 0x4CA52561D4B21D91ULL, 0x360B5EFC166B9D69ULL, 
            0x90A30E57D6AA31FDULL, 0x594362C7A426212DULL, 0x191E6C1A226775A6ULL, 0x760C0CF325E31D14ULL, 
            0xA7DB1DFD04019CFAULL, 0xC1A88402A3706627ULL, 0x9BB343243B55C924ULL, 0xE96D83D659A2706AULL, 
            0x33C4A5CD398927D4ULL, 0xD12211933A5F44ADULL, 0x2E4F55EADCCE5F10ULL, 0x68981B4AC4040753ULL
        }
    },
    {
        {
            0xE9AD6F473B14B85AULL, 0x3C3420ED05FF8DA6ULL, 0x262A2EFE2A1C0303ULL, 0xDD0D48967E2BB76AULL, 
            0x53D1A28E225D4E95ULL, 0x570F00F540C86564ULL, 0x3B8BBB3D82F66722ULL, 0xC1184213D089C9D5ULL, 
            0xD8DB7C30FB576618ULL, 0xE1945B824BF91873ULL, 0x9662B2F863934E7DULL, 0xDBB19B8974DD92F7ULL, 
            0x43F6F17C2C8475A3ULL, 0xFF27312A70EEE212ULL, 0xB8F24069A773EE59ULL, 0x0C2416365CE0B0BDULL, 
            0xC70A9181D08E632EULL, 0xBAAF11C0C8803415ULL, 0xD79AB44DBCB69BC9ULL, 0x2B970EB1748EA821ULL, 
            0x36E004D2FA4DF2ECULL, 0xAD9A9A13842CE5B5ULL, 0x437C5D9482123622ULL, 0x127C7F39E1BBE455ULL, 
            0x684A5730E14035C3ULL, 0x3D8551A3A63C7CECULL, 0x3A0197258B7CE01BULL, 0x3CCB9FA43443A1ADULL, 
            0xD65C15742B2D3B1BULL, 0xD18B8919952CBB0AULL, 0x66DA9122DC1CC25FULL, 0x8B833BC7FC6A6B1BULL
        },
        {
            0x4A4771A71919C1A7ULL, 0x87618027F2629D56ULL, 0x35665F40E971BDB2ULL, 0x3966A156C6A3CD54ULL, 
            0x5DEB4077B7BFFC47ULL, 0xB3C359395A358FBFULL, 0x4CBC39F651AB6FEBULL, 0xBC0EBA413A94484FULL, 
            0xF40C21B302675A1BULL, 0x4E6C141943C0B974ULL, 0x96449A49CA6F9C82ULL, 0x358587CD426FD614ULL, 
            0x8754B9E3CCD708D7ULL, 0xBB9BF74C9024381AULL, 0xD65EEE9EB65A12C5ULL, 0x6884A1C1DC325A2DULL, 
            0x5B2A67873C978945ULL, 0x53396A1FF121CAA1ULL, 0x4D1BD46945D8FA26ULL, 0x36261FA29584046BULL, 
            0x6344C4B1DC7DF93EULL, 0x8429FE7956866224ULL, 0x0D6FBCF63F783035ULL, 0x4F54E8B93D643FBAULL, 
            0x6776182724D90FADULL, 0x29CF13463954E1CDULL, 0x57F848EF08DABCB7ULL, 0x93986C1151995A2EULL, 
            0x3635DA29C8897FAAULL, 0x8C051314450738B7ULL, 0x7A4CAE7B16571257ULL, 0xDB4B720F2AF71079ULL
        },
        {
            0xC35D9F6AAF562A51ULL, 0xC8C3F1D4B0F057FCULL, 0x31EC24EDD1098E2BULL, 0xF8AD584BCDD3679BULL, 
            0xD0E10DDB2FB90CEAULL, 0xAC2EA227229878AEULL, 0xF42140F97AADF2FDULL, 0xCF5396D6B26AE8C3ULL, 
            0xCEB36F948A74F636ULL, 0x2C97D9AFEFF9EAC6ULL, 0xE17E0B830E68C9E2ULL, 0x97E4838037526035ULL, 
            0xF79F5C46E98A3993ULL, 0xB30C5060DB166E24ULL, 0x31BCFB53040BB2E4ULL, 0xFC51083E350B78B3ULL, 
            0x734662C4C0C15FFAULL, 0x05083A7AF7066F28ULL, 0xCA877C8D2604A504ULL, 0xB0EBA69D8031FB34ULL, 
            0x95C99634824B7A5BULL, 0xA65038A483F267ACULL, 0x095591159B80A2A0ULL, 0x0233522CFD7CBC8FULL, 
            0x30BBDFD43C8DB60BULL, 0x5AD2439ECB28B2BFULL, 0x5B5F3D65D72EB9B8ULL, 0x2E638B125F25F8D2ULL, 
            0xFA27C05582F436AEULL, 0x213B54242B2B2624ULL, 0xF9C7F081A16B7A64ULL, 0x3CEE64977F0AE8F2ULL
        },
        {
            0x29A7B7507E67A1D3ULL, 0xE9721E9EE7B1D705ULL, 0x0516A46627408201ULL, 0xC245B28120C64052ULL, 
            0xAE3116D3AB572DCAULL, 0x9E26ABCD3906F713ULL, 0x5AEC0B61327EFFE5ULL, 0x7830602B566B8CF5ULL, 
            0xE05E0D77B1556187ULL, 0x633DF6CE1ACAF9A6ULL, 0xC9E230F2A040E539ULL, 0x65FC4544DC1A9A0DULL, 
            0x0F80913B10D47453ULL, 0xD5C3F7D26871DB6CULL, 0x1E3764055A8BDA36ULL, 0xD079B8420E749C97ULL, 
            0x764DBA0C857A5A18ULL, 0x892CF8DBD6224D9CULL, 0x059AF7A0FF6F2DC9ULL, 0xC9EBE9A76492C710ULL, 
            0x1475A37DA7775AF6ULL, 0x267794C5200EB622ULL, 0x9535C8626EBA5A21ULL, 0x2352A4118768CCBDULL, 
            0xB0EFCE54BC344C83ULL, 0xBA572CE86EA97842ULL, 0xE29F42A6EAE5AA80ULL, 0x7D0D85E5B4E0FC1CULL, 
            0x4826E453711FF307ULL, 0x9F3DF32CC88DCDDAULL, 0x042C36386441982AULL, 0xB7D1CBA14A9186E0ULL
        },
        {
            0x40EFC7F53DBBF4E5ULL, 0x5A4E9A58FFC8A199ULL, 0x4CCBF429F2A7D16BULL, 0x43B8175176F5EFC6ULL, 
            0xB7E335A2CAFA9673ULL, 0x5D41F4AA1EAD084BULL, 0x730F58A2FF82CB53ULL, 0x18271992E3E94C15ULL, 
            0x45607B0ED65BF1C3ULL, 0xD22FD91FD5911B04ULL, 0x84F7D839C327D090ULL, 0x188337B9BC90D996ULL, 
            0x0CBDEFC322C28221ULL, 0x27B67BC91738E1E1ULL, 0x302420E338AD22BAULL, 0xCD46E7720908E164ULL, 
            0x9E15227B6DEE07DFULL, 0x65F2F7742459A352ULL, 0xC587E42B532B7112ULL, 0x3DDE530DEE701F8AULL, 
            0xFB8C3906200985F7ULL, 0x3E55264B6F3192E1ULL, 0xFFF26D6D2E2FDFADULL, 0x74C097AF4F6245D4ULL, 
            0xE3BC2EFF6832D089ULL, 0x3C28A4D4708F27DCULL, 0xD40B41409FD30056ULL, 0x4738660229B33617ULL, 
            0x2306B1B3FE745EA6ULL, 0x3B543EBCE7B451BEULL, 0x55DF4FA301144036ULL, 0x35FF46A7A744B231ULL
        },
        {
            0x1679CAD28FCC0209ULL, 0xE6BBE438AF31114AULL, 0xF71B7E0A18D42743ULL, 0xB25C708A39FBB865ULL, 
            0xD2E2DB2170542AACULL, 0xFDF70FC19809C610ULL, 0xEF1A79C92127A8F6ULL, 0xACD5BEA4599D329EULL, 
            0x6A11E4C69B70718BULL, 0x4B6E8F93EB3C8E54ULL, 0x3DEF042E6DAF93AAULL, 0xD200660B5DD2162CULL, 
            0x250DCCE730BA2E89ULL, 0xD24A978399D80047ULL, 0xDC9B64E14E963F45ULL, 0xF6BFB160D0A662E4ULL, 
            0xE1C3445B99719DD7ULL, 0x02163D4006F95AECULL, 0x67F0E703EEA364EDULL, 0x615253B56A985A69ULL, 
            0xBAF722E5036E7E16ULL, 0x5AAC245E8DB92442ULL, 0xDA81BF953E9FA01EULL, 0xF78E1EA871433C97ULL, 
            0xB6078AADB5A6854AULL, 0xC2EEDE44613716FEULL, 0xE948B8D5031CA38BULL, 0xBFCCBEAF3C728A0BULL, 
            0x49A61C6BB6BD4DCDULL, 0xA12F9D8E9DB6883AULL, 0xA51292C1E8CEBD57ULL, 0x2CE85BEE6784D158ULL
        }
    },
    {
        {
            0x2BB6A8A5E43848E6ULL, 0x084616560CE3AC56ULL, 0x67DD19C9CE5FEBFEULL, 0x6BE00337A27A5692ULL, 
            0x3F96EBF718AE6597ULL, 0x6026760E19293349ULL, 0xC4CA693BD31524DAULL, 0xAB54A8B46BFB78ABULL, 
            0xD622577370AD9E10ULL, 0x4A16901367A011ECULL, 0x914536B94AFF4E03ULL, 0xB2C7878124DE0615ULL, 
            0xF3D3FBB4132D49FEULL, 0x2A3A0CCE3BD2C548ULL, 0x2959AD290061D1F0ULL, 0xDDE0454934E654C1ULL, 
            0xCA57B3EBCB148721ULL, 0x6EE4AAE90F396D38ULL, 0x9D79018F054049E7ULL, 0xF937102972A60B3CULL, 
            0x5547401BF8006699ULL, 0x2DA828168044C4D3ULL, 0xBE08E94948328B47ULL, 0x3E515AF4D336878BULL, 
            0x9222258B1C5DB4FDULL, 0x60DF776A165146F7ULL, 0xD24B762EC1C21463ULL, 0xCBBEA9641F8397EAULL, 
            0x56E554F5D8597EE7ULL, 0x12DA96BD526BB856ULL, 0xC4247CE1E1D29200ULL, 0x4A9CF3EB80619451ULL
        },
        {
            0x4C4CEDAB7EC47422ULL, 0x5B90A22CC7AA8660ULL, 0x296977E1F68F7B86ULL, 0xB6063393053B9F6EULL, 
            0x9105228C38843895ULL, 0xBA798F9552FC6FE6ULL, 0xADB6BFDBAE722BA4ULL, 0xD5365F161F7CFEFEULL, 
            0xD147A2D6DF85B699ULL, 0x7BF55276F6F9C496ULL, 0x571BEDE9E650EAFEULL, 0x3D977267C647FC5BULL, 
            0x3BC9F7446ED6455FULL, 0x4A43CA8D5192D424ULL, 0x8CCD99E1A6C5D3E1ULL, 0xAC6A904E15D74FE9ULL, 
            0x48565B8819AF6FDDULL, 0x0275144A0138571CULL, 0xE5C99DB11E31C506ULL, 0x6CA67699050BB5C2ULL, 
            0x9FA37139E83CC07FULL, 0x7E5BEE09B4A260EAULL, 0x8F7EE1C244F55F84ULL, 0x57BD7D752190AEA0ULL, 
            0xDC721E94CCC8301FULL, 0x81B98F89D09A1A81ULL, 0x48E22570DC843039ULL, 0xD9243FCD3FA6884EULL, 
            0x8B3C1BBE0B29AE9EULL, 0x3827F520F0FF8C6EULL, 0x825BB3E4734C4341ULL, 0xB6AF2DDF739AD703ULL
        },
        {
            0xC0856851FB8010CBULL, 0x4419255B3B0029DBULL, 0x5989FDDA2758B60AULL, 0x3945621A007B3118ULL, 
            0xBD3F91D505FAC177ULL, 0x34FE3FEC4C13F383ULL, 0xB86BF1440226DAC6ULL, 0x1D2297C16150B15AULL, 
            0xAAC93DB749695D1AULL, 0x11F8EC7ACDAD3026ULL, 0x5740040861FCCA3BULL, 0xEBC95A275F2C22C9ULL, 
            0x4494FCE293F61A94ULL, 0x89E2FFEB09D5C1B0ULL, 0xB1B27C42504E0824ULL, 0x063743892DC6B929ULL, 
            0x29893DD03A11A828ULL, 0x7B1D64A90302D16BULL, 0x6713153F5A2900A9ULL, 0x2FCC7F4F322FFCF2ULL, 
            0xCE36841C6BEDD51CULL, 0xF174EA0EB8ECF155ULL, 0x64F8A2BB7DA105D4ULL, 0xBA13CAD7864C7325ULL, 
            0x648705C47FBDE780ULL, 0x11D12CA7422CFB26ULL, 0xB8E648553B2E6B87ULL, 0x0E7609EB6AA20B8AULL, 
            0x2A61954FE9E2EAE5ULL, 0xDFE381FEE17D147EULL, 0x2C612B37EE49BEC8ULL, 0x88FC5958400EDF93ULL
        },
        {
            0xB7BC714E84F6B6B2ULL, 0xB3E430803012ACC6ULL, 0xE6C4AA6B45CBAC9EULL, 0x585911BF3E681887ULL, 
            0xC0AEAB4B7014A6D3ULL, 0x91DCE881147EBDD8ULL, 0xC772CE8FD9BDE592ULL, 0xD0FE663E5FB8A294ULL, 
            0xC77995C9CDF6F51AULL, 0x6C20CF93725F5D3DULL, 0x28E279B3C72437FDULL, 0x15FF327815990F9BULL, 
            0x40CAA838091E9C34ULL, 0x33ECC631C5B45EB8ULL, 0x5CE72053C7C8A98CULL, 0xD5C4E0A3F1D85BB9ULL, 
            0xF0F99C42A1075D4BULL, 0x0D068BBBD05FA786ULL, 0x01F4D29A02693057ULL, 0xF1396D88762E1FF2ULL, 
            0xB0ECFAD220B1C9A1ULL, 0x178EF5F816D171F7ULL, 0xA35DF8B1B391722DULL, 0x01485D3227798CCAULL, 
            0xBB35D1B55B9497C2ULL, 0xCEEA7C45E6DF50C3ULL, 0x29FD013B0F9F069BULL, 0x56F83696BD86106DULL, 
            0x72B5F396DA4076AFULL, 0x402548F787129BADULL, 0xA7C0824D3EDB59BEULL, 0x4DA59086702967ADULL
        },
        {
            0xAA3852C38B5AB80BULL, 0xB359FF1752E6E75FULL, 0xB5D9199C2258557DULL, 0x289197348F372D39ULL, 
            0x004D7E8F2B15CE77ULL, 0x263144B70AD65408ULL, 0xE99DFB5D9C4086CBULL, 0x03F484E091286B5FULL, 
            0x981489B2493CD980ULL, 0x2209B81F141BE1F0ULL, 0x809D2D1D195B9137ULL, 0x560A379BA19F0998ULL, 
            0x0C47E52F461AC27CULL, 0x8183FD48295A8918ULL, 0xE75ECB7C5CE513F8ULL, 0x86912FC3702FE4AAULL, 
            0x0F57E313BD3AEBE9ULL, 0x0658D569758860C0ULL, 0x028C53DBDC379119ULL, 0x27807DDA0B93FA05ULL, 
            0xB6C402E5779FC814ULL, 0x372881F9FA4EC7D1ULL, 0xD1DE317901ACA245ULL, 0x8A2F5EC0335740DCULL, 
            0x480B2F55A429DB8EULL, 0xE49C12F664068021ULL, 0x9B9DB8737D454DB0ULL, 0x37254C7C7C79F541ULL, 
            0x7C8C45ED6A043BC8ULL, 0x2056C2380E1C5727ULL, 0x64501CF3AEEF5480ULL, 0x2E3539B3A11BAADEULL
        },
        {
            0xB63E8BF40700949AULL, 0x119995245B892293ULL, 0x4C07A9C86E079DDDULL, 0x5E23366F5A006139ULL, 
            0x160339071835000DULL, 0xC116B3DDCFFDF3C4ULL, 0x3D563C7A6B583062ULL, 0xBBA9FBA4EF7FE2FDULL, 
            0xF9A15EB8C9604A01ULL, 0x2CD4367C9A4A733CULL, 0xA970CFD7DD275A49ULL, 0x608F5B415378E72BULL, 
            0x12B47C479DCBD40AULL, 0x5DD77413987E7909ULL, 0x80F8445D6D20FE63ULL, 0x171F53065363819CULL, 
            0xA933EB1D047A2568ULL, 0xF9337A6F6CAE381EULL, 0xFF00D940BC73CA1FULL, 0xB451026402E71C3CULL, 
            0x09CB2533D0517EA9ULL, 0xF74326A6F4270D07ULL, 0x824B5F35780EF8B6ULL, 0x9DEF60B3BC24C4A2ULL, 
            0xFB0293AA9E3EE8DDULL, 0x0D890F947B9A649AULL, 0x7658CEADD5A4106AULL, 0x93600C034DD9040AULL, 
            0x99102935D708165FULL, 0x397F4CCEB9C325F5ULL, 0xA13051A18284432AULL, 0x6AFDF1BD755BB0DBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseCConstants = {
    0xD4732042A9C734ADULL,
    0x575C78E99AD71B3FULL,
    0xE2855FCF923A266BULL,
    0xD4732042A9C734ADULL,
    0x575C78E99AD71B3FULL,
    0xE2855FCF923A266BULL,
    0x3B843A4CD1A5D68DULL,
    0x6952304C7A67F27BULL,
    0x40,
    0x9A,
    0xF4,
    0xC8,
    0x9B,
    0x8B,
    0xEF,
    0x5F
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseDSalts = {
    {
        {
            0x99CD03CC08E05323ULL, 0xF6E5CF16414191E0ULL, 0xC606AC619126264EULL, 0x1BAC418A47062851ULL, 
            0xB7BB7A0405C5C63BULL, 0xAE806E173E3000B1ULL, 0xFB6D2780FD179A19ULL, 0x1DF930365F0A4D9CULL, 
            0x5577CAD3A9AAADECULL, 0xC94D7E134384B324ULL, 0x0EAF92CD70D3ACEDULL, 0x371151D9A532FD88ULL, 
            0xE257DE7552E4B931ULL, 0x35DC2C406FB70364ULL, 0x79327763B5443D5BULL, 0xF8F2421DE8A92FB2ULL, 
            0xBF1D3515B7B5BCA4ULL, 0x8265FD8F75BEFA5CULL, 0x659A8A369B647B0CULL, 0x04B8927B3EEC5B8DULL, 
            0x4678DE14145C0B44ULL, 0x884EDB15A431FB00ULL, 0x312B0B46AAFFD37FULL, 0x6CEC61524F3B7770ULL, 
            0xC46A9225283AAB36ULL, 0x4F568F1A19E1F4D3ULL, 0x4A72B3393A5747C3ULL, 0x00BB878ADA57FC27ULL, 
            0x22943BBE7558B0AAULL, 0x0F82C84A7BBADB95ULL, 0xEB702B5550B99FAFULL, 0x1F7FFEE64BE53B1BULL
        },
        {
            0x905CFB8E6CB934E3ULL, 0x50241E8266E490FDULL, 0x8C50BDF290D5D2C4ULL, 0xCF6CC1DE4CB7E951ULL, 
            0x71DB05CCDC2B60DCULL, 0x5A262F8AA31CC8CBULL, 0xBB0BD7BFFF492A1DULL, 0x4485807124F03155ULL, 
            0x5C84E8AF38C030F4ULL, 0xF2B9F26C0974BECFULL, 0xBAC6BEF6CF464788ULL, 0x5C7537E366B67C36ULL, 
            0x0926351D9AF7814CULL, 0x6EA00070E798B7B9ULL, 0xB48DBC0964330934ULL, 0xE7E028460151F241ULL, 
            0xEEF395F6E7B383A1ULL, 0x9C6EBCA43A62E0B5ULL, 0xD652609637CD9CE1ULL, 0x2993A9F35EA7591BULL, 
            0xF84CCEBCA84332BAULL, 0x1ADDE6E956DC008FULL, 0x1B49F5B0BC4A0439ULL, 0xB2151B8340543059ULL, 
            0x63A06983798FD38AULL, 0x715A914693BE9C12ULL, 0x78B60986DC06ABD0ULL, 0x88C0754236AA5540ULL, 
            0x5D8EB6805A01A83BULL, 0x5C1CB21D44CA36BCULL, 0xF5F8F1593961FD5FULL, 0xFA81B5C25C1A781DULL
        },
        {
            0x0B5BD850D9F3412DULL, 0x47EC3EE681D33A5DULL, 0xDCC18379E7CB16B1ULL, 0xC3ED699FD0F83161ULL, 
            0x70B5ED4F0D6462C5ULL, 0x1245EC450E078B76ULL, 0x3F1D9837EFA22D2AULL, 0xA734896D1D40F2C6ULL, 
            0x97B9275A65CE1D3CULL, 0x5298414604903556ULL, 0x9F6573CF68473301ULL, 0x01BB7282F68FFB7CULL, 
            0xDF3581CA007A1B20ULL, 0xF7D7F4FD6138E096ULL, 0x61422DB7CBD80B10ULL, 0x61F62D71A9FBD517ULL, 
            0x602036BFEE7D3938ULL, 0x0DF9AA9D469F24DEULL, 0xECA7E1065C48F01BULL, 0xAB8256AC3966D79AULL, 
            0x4DB9D871643D6FA7ULL, 0xD9B65F1710C05951ULL, 0x50E265EB3A2317BAULL, 0x46457CE05F595C27ULL, 
            0xC1712D755A2B6441ULL, 0xC8955649B95F1088ULL, 0xE0244E3083B5AA58ULL, 0x363706D2143DF0B9ULL, 
            0x9146AF06094B2562ULL, 0xFDDE5DE64BCFAEFBULL, 0x695413B36AAD1841ULL, 0xE380B0A5AAF65145ULL
        },
        {
            0xA4E6DADC06A45428ULL, 0x3E8F583E04A0D7E0ULL, 0xCFBC49ADD63DBD2BULL, 0xB1E136346E2A1680ULL, 
            0xD1515254A0C8BED7ULL, 0xE2E1F1D662169B17ULL, 0x7487318568DB273BULL, 0x70D851C769BC07E4ULL, 
            0x34BF709A5EF5DD33ULL, 0xD6FCA4513253FBFCULL, 0x32FDEB17026F0498ULL, 0x999A31B19D8E982AULL, 
            0x77A72A35F8327E27ULL, 0xD578D91A98F9C849ULL, 0x664DF5AC22CF9F6EULL, 0x29DF5CB698CBF18CULL, 
            0x63F7F983F84D2289ULL, 0x25234480B040F78FULL, 0x25B769B07D4F673AULL, 0xFC4853341706F56EULL, 
            0x47A76CA82313F07EULL, 0xFCD2A19A9F919B89ULL, 0x42774AB73674E09CULL, 0x1A70D359840A5E18ULL, 
            0xFE7A66C4E8F53D2BULL, 0x7A43ED1E15424271ULL, 0x5B3C399F87299D79ULL, 0x173CD25D37043848ULL, 
            0xFFB739FA88F26ED9ULL, 0x1238269ED0D2E38DULL, 0x6AD880C07AA3077EULL, 0xD1CB673C91B68D7CULL
        },
        {
            0x29057D7AF79784FEULL, 0xFCF2E43EDFC3BB99ULL, 0x0E3B3FBF05D2B9ECULL, 0x7957D3A6D0D019C5ULL, 
            0xD598451A76D42A1CULL, 0x3D52262961AEA228ULL, 0xC95A2908E520C0D1ULL, 0x226353E63D2983A9ULL, 
            0x5A9C89EBDD683396ULL, 0x259706F89039A61BULL, 0xA13D9C168A059589ULL, 0x441A0FD932A378E5ULL, 
            0xB09C4358006999ECULL, 0x393C6CDE0BFF2EA2ULL, 0xDA038C006E28E21EULL, 0xD68849D186CD869AULL, 
            0xEC6767D63145B85EULL, 0xEC692E3DDFE3A655ULL, 0x3FA722A842695904ULL, 0xCDD7307F003AD477ULL, 
            0x44C215C467628906ULL, 0x09645B0BDE03B0CFULL, 0x883320A952E4E8B4ULL, 0x14341AADC3EACA65ULL, 
            0xF3328B5F4EF892E9ULL, 0xCF4061621EB3FCB0ULL, 0xC5BD5F70A229E926ULL, 0xFD5042BF3A03F2B4ULL, 
            0xE99A754D9FD035E7ULL, 0xBFECA191F3655729ULL, 0x41553CF61926AF31ULL, 0x2D17BB2816171E9EULL
        },
        {
            0x8528DB91A17A5C6AULL, 0xE751DE63683FC23BULL, 0xD36755DD6045AE62ULL, 0x0A8F10F4226216BEULL, 
            0x80EA1AED0A2E35C4ULL, 0x2E31875EAD7705CDULL, 0xB5F2E372DE9F3634ULL, 0x005EAB031D457D0CULL, 
            0x6580CCD59B50D4AEULL, 0xE300879940914EF3ULL, 0xBD670B125F7F8167ULL, 0xFCAB22CBF6FB8F31ULL, 
            0xB679BA1E10C0727BULL, 0xE040EF8F18B4B15DULL, 0x671C50001B299CFFULL, 0xD7FB2B3C41900EBFULL, 
            0x91FBEE0B1A8936A1ULL, 0x054CA24808EE95E3ULL, 0x82A65ABD38E4F227ULL, 0xB082EFDEC4A4AA0FULL, 
            0xAAAB33C151AB0ACEULL, 0xA0F9004DE6C558B7ULL, 0xD421F1EEDA6F8C1CULL, 0x0C8C9E3BB2AC9795ULL, 
            0x135D92590AD5DD63ULL, 0xD6FAF764473A25C4ULL, 0xF36CE70F39AAAC22ULL, 0x10D1900C5AB51677ULL, 
            0x47AB2C6C873328F9ULL, 0x0182F2DFCFF8AE9DULL, 0x431443BDB0EE1BADULL, 0x6B7E281D6A566894ULL
        }
    },
    {
        {
            0x951671339D61987BULL, 0xC6C692D36612315CULL, 0xBEFBA580C21C3E70ULL, 0xA9969672CCF17D86ULL, 
            0xEE73187BB17DF3B9ULL, 0xD9AAC578775B35A5ULL, 0x355BC111099392C7ULL, 0x614E2C2B377D7595ULL, 
            0x4C60286E2CFD06BEULL, 0x3C3AACE7CE8F8460ULL, 0xC8D0073E694FCDCDULL, 0x9158A18B22E42EDCULL, 
            0x52CE23DA76420008ULL, 0x5F628BA6FE6664F0ULL, 0x01CF4C9492640C0EULL, 0x6B515CE61D5DFDA8ULL, 
            0x9BFA6C16DBE35FDBULL, 0xE4FB06E6E46D8745ULL, 0x7AAF7637DA25091DULL, 0xDD4509A8B90B2D2DULL, 
            0x795B6BCD94FF70F9ULL, 0x114DBF5E51CA4885ULL, 0xA2150FC3716C5EBDULL, 0xD4097C2D905B1FAEULL, 
            0x039F4AEC9411A52AULL, 0x94EDA494131D9C04ULL, 0x1B5B631EC3B7E54CULL, 0xA8E9EB11384F11B0ULL, 
            0x24070A6BDC175F79ULL, 0x89AD5AFBEE3278D3ULL, 0x04CC0E07DFA8A43DULL, 0x866045E71F0145E2ULL
        },
        {
            0xF1BA43DBEA460050ULL, 0x99D018883DFECF15ULL, 0x2A8B5AB58A36FA42ULL, 0x14154EE7969F1307ULL, 
            0xE1F82B1CDFE36FD6ULL, 0xDD86F1A3D8B36B93ULL, 0xEBD9FBDB0FF155ECULL, 0x9C678CF48FE09F3EULL, 
            0x0BD25F172B4B2A24ULL, 0x7BE66B03DB633D74ULL, 0xE8E8AD87E50D6AAEULL, 0x8ECC58EF7A07BA19ULL, 
            0x482C80AFAD91B6EDULL, 0xB8F2385FB62B8D0DULL, 0xEA4844313DF6EFC9ULL, 0xD39F2761DF00391AULL, 
            0xDA5D25055DDE0F9AULL, 0x9A728A652B5D420BULL, 0x500DBBA5A1DCB18DULL, 0x73E8BD2A4039C80EULL, 
            0x8807B5E640322595ULL, 0xB0BEBF39F4C94B80ULL, 0x6D940151C6F6C3A2ULL, 0x473D5A06E8B4BE25ULL, 
            0x9E9D99549E035183ULL, 0x7E8663AAF97BD94EULL, 0x27CABDC4A36A6988ULL, 0xC3F13DD14F82C9C3ULL, 
            0x386B1AF4E7CD52ECULL, 0x93A10CA867A93AD8ULL, 0x96682B7DBF32E69BULL, 0x4026FB7898883216ULL
        },
        {
            0xA7FBCEE651B10BB5ULL, 0x405D74F0E67D8E63ULL, 0x267DEE3DE2BE76D5ULL, 0x97183C55A821A9D7ULL, 
            0x2D0E7F87C9D6F8B0ULL, 0xDD41392A2FCB2380ULL, 0xECD1FF6413A1AA5AULL, 0x64113F818FECD146ULL, 
            0xCCE50145B223A5FAULL, 0xE99DF0E2FC8BFD09ULL, 0xCCDD596BC5DDCDF1ULL, 0x47A70A87DD7772A8ULL, 
            0x72297F65E2D86DD0ULL, 0x6741B17BB33E0BB8ULL, 0x16D6C83C55598A5CULL, 0x19DC33BC65748370ULL, 
            0xE2E14B801B5619AEULL, 0xC4BF9C793B4E6B08ULL, 0x07A2F83697D8873BULL, 0xC12958B6F91BF32EULL, 
            0x928241E2C5E20FBAULL, 0x99C1B426AE9F9C10ULL, 0x3EF3DB682F70FD8AULL, 0xC8387716E46BD1BDULL, 
            0xFBDACC0AE3CA7D67ULL, 0x7648E2C30F6E3981ULL, 0x13DD716EC05922F2ULL, 0xB5D4D88DE3F80631ULL, 
            0x5710A4E35B37A33FULL, 0xDADB6469F4AC46ADULL, 0x8C6085951BCE060FULL, 0xCE530589DF14DFB0ULL
        },
        {
            0xE562F057719AF71DULL, 0x993E5753440941B2ULL, 0xABFF567F593E553EULL, 0x990A1D131A601D88ULL, 
            0x9069F97C818F3293ULL, 0x29D39F06E6C928C8ULL, 0xD827369141593106ULL, 0x968CFE2F3C44C704ULL, 
            0xE1FEA7C949B13333ULL, 0x32D80FF8334324EFULL, 0x83404528BA0C0DD2ULL, 0x520422D1A3BE7308ULL, 
            0x9D545DE161DB2FDDULL, 0xF6214215788029F9ULL, 0x4E43DB08DDC6477DULL, 0x8DC2E03A2B5DDC29ULL, 
            0x546EB552F3A2DFADULL, 0xF0B45A3D7EB9E41CULL, 0x8A6D5CCB24D004BDULL, 0xF02D071EF65357FFULL, 
            0x5D87EDD6DCF77398ULL, 0x094DCFE50A8453B3ULL, 0x6D5563FAEC82F753ULL, 0xAB207CFF499700BAULL, 
            0x65739E5A7552B683ULL, 0x94F7C7836173378DULL, 0xE97DD93286C284B5ULL, 0x70B7D88EDC0E682FULL, 
            0xC134171832E2F712ULL, 0xEE07DAB206550C0CULL, 0x79076FEEA7B6BF75ULL, 0xD95B13BA4B5A3E8CULL
        },
        {
            0x4FA65600E86562FDULL, 0xFA3C6C47B783C149ULL, 0xA9E2BE612DE2857AULL, 0xEF804F52F7CFD859ULL, 
            0xE13B04672AC4B6D6ULL, 0xCCE01ADF40F18EE1ULL, 0x35FB8464E7EAEAAFULL, 0xA8E2AE6BAA872C2FULL, 
            0x2DC77051B4AE4FDAULL, 0xAE8CD63499DEA77AULL, 0xF737A747D252CEEAULL, 0xF6AE81C8F4E83751ULL, 
            0x887EBCF948BA171EULL, 0x50F5098F710D40A5ULL, 0x84F06E1ADD9E5B32ULL, 0xE41DA10BC2D8B1D6ULL, 
            0x4ECF6CE7B75C6B77ULL, 0x8EF9586E0BE1480FULL, 0xBBB1EE98796EB448ULL, 0x90CF2CDC491BC201ULL, 
            0x81B89E543D25DF2DULL, 0xEB66B182C8BE0430ULL, 0x4115920D66242F90ULL, 0xF183FC32AD7E4E02ULL, 
            0xC5E001AB1B546546ULL, 0x83B529522BA17BCDULL, 0x50708E88142EC4FCULL, 0x56E38BDC2F9106B5ULL, 
            0xB64CAFB9CB777D35ULL, 0xD91D7260165C6278ULL, 0x19356F57AC97A670ULL, 0xDBF87014D99A192FULL
        },
        {
            0x4E7592EABA62D861ULL, 0x9901E06C2157E657ULL, 0xFE39D0F640551E45ULL, 0x59D24002020FDB50ULL, 
            0xAF359D306DAF7140ULL, 0x6B083B527DBE0393ULL, 0x5D3B93D1BA259D8BULL, 0xC8DD0A62B1A25099ULL, 
            0x50032696DE593E19ULL, 0xCAE765D380FA7527ULL, 0xE6E56B6EE5B39406ULL, 0xCF4467297C2AEBDDULL, 
            0x5AF7BBF5EA8522B5ULL, 0x2B2A35E60C4DC6C7ULL, 0x2DAD4B90FC38B61EULL, 0x7BDA68908B0401F2ULL, 
            0xAE9BD9FFCCC153CAULL, 0xE184F1F4B2EE5020ULL, 0x88954BFC9F01CD83ULL, 0xDFE39063754CFB35ULL, 
            0xA862EC274F746255ULL, 0x56340230C47AEDE9ULL, 0x0ACDA4AEB326BC90ULL, 0x846940C16916D0BEULL, 
            0x090FBA65165FEF86ULL, 0xBE5BAAB0A2701E57ULL, 0x0FA4743A7B1A460EULL, 0x81BA682941C3600CULL, 
            0x1EA9B8C3F8697720ULL, 0x14D88F75B0CCF465ULL, 0x4B072F0FDF058A7AULL, 0xD9B40F5BC9F45064ULL
        }
    },
    {
        {
            0x969F09C020BE5EC9ULL, 0x7B2BB1A50BE6CA14ULL, 0x9A8A6F4223F2B4DBULL, 0x1E14D710166E01DFULL, 
            0xD173C0EB725E3493ULL, 0x5DAA41627847D88DULL, 0x08C1F6DE3F18DDF5ULL, 0xC74EAF4D14D5D687ULL, 
            0x31947AE54C7A589AULL, 0x5B31CD5F039F9AD7ULL, 0xE6FC2894B8D0110FULL, 0x3C8684046850D244ULL, 
            0xBAD742F47FC41D6EULL, 0x18C9EC188C6182ADULL, 0x19688E2A6CFAB369ULL, 0x8B928AE418201676ULL, 
            0xB6050D3F1706042CULL, 0x00F4E4D466B60834ULL, 0xCB663ED6F8F5A59DULL, 0xD6CA8CBCC3C800D4ULL, 
            0xEF2EB655DFF4FFB9ULL, 0xEEC205DA4AFA21E6ULL, 0x83F155362EC352BCULL, 0xE73CD71906F9C9E9ULL, 
            0x1D68A9E73865FDCDULL, 0x0248F54C566D15ECULL, 0x9F2D70396814016BULL, 0xFA9365E389AF0250ULL, 
            0x55091CE18179D766ULL, 0x9D898B45C7915F54ULL, 0x6EB36616B21A9FF1ULL, 0x28652448D3E7F32DULL
        },
        {
            0x1EDDCC958EDF7FA7ULL, 0x8B1A8306471BC1C7ULL, 0x0E71D4EE060D62A6ULL, 0xC8C6D72A952C6CC8ULL, 
            0x9E4FCAEC57C230EBULL, 0x54B66165E51384B0ULL, 0xE4CDAD6431992B27ULL, 0xBEFD01810D44A3B3ULL, 
            0xBDB9C666CCFEF3A8ULL, 0x2466504A7EFD75C4ULL, 0x310BD89210D8D76AULL, 0x81E2A8C5C15B6D74ULL, 
            0xA9087CEC4C3EF906ULL, 0x08EAB3B428E6CC76ULL, 0xAB4D1837F0066196ULL, 0xD2980BF4555FD83EULL, 
            0x17288AC3A5AB5D4FULL, 0xBACA526631525761ULL, 0x79B77D0A2C706C63ULL, 0xF39C0D553C3C3A3FULL, 
            0x44242E9C66B1DFF2ULL, 0x5EE7E96E17EB5DA5ULL, 0xF9E3CECE31B1BF64ULL, 0x084A8A5973EE90C9ULL, 
            0xF51CCC48B1C5FCB7ULL, 0xEF5DBD36147C1F7DULL, 0xBA9C0C5F09A67EDDULL, 0x0A32173DE1A6152DULL, 
            0x628E2EBDCD402376ULL, 0x9618BDB8DDB7642CULL, 0xF78C18E64625E02CULL, 0x829340CCDDBDC34BULL
        },
        {
            0x4A864D2A6B932E58ULL, 0x8587995C3C5E2432ULL, 0xB69A3888203A955FULL, 0xF9A5CB8791A6DB00ULL, 
            0x55343E19360981E8ULL, 0xECC13FC26EA0E3A8ULL, 0xA812DFA6D6126A71ULL, 0xD3A5F2841CA48C7BULL, 
            0x25E2BB0355A6F5B8ULL, 0xF32A442BA3B81B7CULL, 0xDBB7B13C2FFD1824ULL, 0x56DF39B011ED1EFEULL, 
            0x70458B60CA8FBE86ULL, 0x864F2F899FC255F0ULL, 0xD42C2A8D896D67DCULL, 0x00E911533921B663ULL, 
            0x848A63AD3995D81EULL, 0xA89EE0EE9E745B63ULL, 0x615C7C89B21EF79AULL, 0x7D33B786C194DBC2ULL, 
            0x9E3074334A479F76ULL, 0x220230EA1306AE59ULL, 0x926FC0AA4E1C76FEULL, 0x67D73DBA40BA26CDULL, 
            0x1ECDD618062658D6ULL, 0xE44F6332E9012F12ULL, 0x590249DBA7555F81ULL, 0xAF6245D85F742A69ULL, 
            0x5C21C4C6DF136243ULL, 0x45BE118DE904D73AULL, 0x3AD4A3C2B13A4ABFULL, 0xDE440A2B5B980D2CULL
        },
        {
            0x012403D2C3CAE4D9ULL, 0x07E2B696DE6D000FULL, 0x727DF0E7CD7B9C96ULL, 0x0F4E5457335EC2ACULL, 
            0xA5C87FBF4D3BA27EULL, 0xFD240C3EABF70933ULL, 0xC3AE5F7BD7F9ADD0ULL, 0x2B253C68E2E47BECULL, 
            0xD3C1829CF47DFC69ULL, 0xCD99FB049730340FULL, 0x97D93C2786BA2AACULL, 0x366BDE7846E3BB33ULL, 
            0x05E9FA8F9C4DDFC2ULL, 0x06C22FC3CBE35FC3ULL, 0x3605935A73FE4589ULL, 0xF85F94B5C4D76EF4ULL, 
            0xC7EFFEE98269F98AULL, 0x569ABE7C0C2EF769ULL, 0x544F5C292C3D00D5ULL, 0xA965DA4E6986C29FULL, 
            0x01FF21F2806DF497ULL, 0xEAE7F1B141499872ULL, 0xB591E2735889FC0AULL, 0x137F53B8918E59A4ULL, 
            0x549D13687ECC3AE4ULL, 0x10FD6E051E25042EULL, 0x5CC2F604DD6D5B08ULL, 0xEEAAE8F011B01628ULL, 
            0x7C88686840024FA9ULL, 0x4E5DBA99004BEB66ULL, 0xD82C7D52CE48F287ULL, 0xDEA34750308B34E6ULL
        },
        {
            0xD772501798872D1FULL, 0x0E8C5D436F90B1E4ULL, 0xC2A4EE44C0412716ULL, 0x00FE25B444C4023FULL, 
            0x7A70D72451BFAE6DULL, 0x35A7C80AE7BE024AULL, 0x2D40A6401EF130A8ULL, 0x7E6C1B5390A71D23ULL, 
            0xF7C91368782B1931ULL, 0x1378C607FA3282E2ULL, 0x0F49EE798374F6C8ULL, 0x03BA9F9C53E02A21ULL, 
            0x8CC46A1E0B942DFBULL, 0xF27F6F5F50AD0FB4ULL, 0x6DE611E6DCEE6583ULL, 0x28C017033E31FB9DULL, 
            0x1726EC8B97E128F1ULL, 0x1B67405BA9234D0CULL, 0x5C78659457CB449BULL, 0x42DEA562427AFABCULL, 
            0x0285E5F960098E43ULL, 0x9884E5B04DBA7543ULL, 0xFD93A32768AE3B3EULL, 0x7221E765D9FA9C8DULL, 
            0x3D5A375ADCE26150ULL, 0xF2DB880132956E74ULL, 0xAD668993B1296CC2ULL, 0xD9FA2D2FCFC2A4B8ULL, 
            0x39AF51C28FBA6EE3ULL, 0xAB1E96174E90DC66ULL, 0x160B7F135274B171ULL, 0x144629099D68A3DBULL
        },
        {
            0xA56614DF7C02D624ULL, 0xEC82282C62CE6CEBULL, 0xE8D71F8AFC708159ULL, 0xE148E92D278FDE07ULL, 
            0x56A283F43CDF56D8ULL, 0x2A3F0ED330C90B9DULL, 0xBEB62E2AD6412971ULL, 0x6E5B0AD5B663D976ULL, 
            0x68A1CEB73ED581F3ULL, 0xB4F50351EB0B5CE0ULL, 0x49797B01A39CE1BDULL, 0x048B61CA4FBE7BB0ULL, 
            0x22A61C334FF28951ULL, 0xD7CCC2B4DB14C330ULL, 0x56D41BE4949A7FB0ULL, 0x007EDB452952D35AULL, 
            0x70D657B7BE7CC82AULL, 0xE2530A4D8117DCC8ULL, 0x8EAAF48013B0EAAFULL, 0x9C91A0DFF4C1EFF2ULL, 
            0xE0B28AE00C3A779FULL, 0xE0F43CBC048D4F86ULL, 0x75FA46C973960051ULL, 0xB8F7EE46236CFD17ULL, 
            0xC5A8BB3C6C141EF1ULL, 0x386244C7FE0B8354ULL, 0xC02EEDA1BA981BD5ULL, 0x885EC3961218E2F5ULL, 
            0x6AD1A7882348D7E1ULL, 0x7543FA16542440EBULL, 0x35002264AC573AD0ULL, 0x592A7764A3BBB882ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseDConstants = {
    0x03642CEE01365AE8ULL,
    0xD4466B1B61E64B96ULL,
    0xA0B41E53A723BA57ULL,
    0x03642CEE01365AE8ULL,
    0xD4466B1B61E64B96ULL,
    0xA0B41E53A723BA57ULL,
    0x2BB30AB0DF53AB5FULL,
    0xF98DC32499152D21ULL,
    0xD7,
    0x50,
    0xB7,
    0x8D,
    0xA6,
    0xCB,
    0x62,
    0x5A
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseESalts = {
    {
        {
            0xD192CCF20024DA85ULL, 0xAF9DAF341BF85712ULL, 0x7B5CFEACACB33A5CULL, 0x4DFADC67F76B61F6ULL, 
            0xC418F42BE27D7A97ULL, 0xB89E90922C72AA08ULL, 0xF57F974C52F99B2DULL, 0x941786ECD384937DULL, 
            0x36BFE40D2EEF57B9ULL, 0x730BD8C974AC3FF5ULL, 0x0360C17BBB9C764CULL, 0x59765D303033FC12ULL, 
            0x71C73546F685B023ULL, 0x3A2918E5B39058D9ULL, 0x26C92576E383A4EAULL, 0x926DEDF0A8FE2385ULL, 
            0xC6069087B6C275B7ULL, 0xDE5502668875343BULL, 0xF477CA34F788DA8DULL, 0xA6072B7BFB3E7FD8ULL, 
            0xC9FB08294CB02513ULL, 0x6071044B2AF70962ULL, 0x58CC9722A1964B49ULL, 0x3C0A5E015F21B452ULL, 
            0x9481A45A66EC03FFULL, 0xE7997CEF6EA0D417ULL, 0xF2641881C67EAA4DULL, 0xEE775F8525634229ULL, 
            0xCA005D4B5694D95CULL, 0x91A8AB43F4545633ULL, 0xBFF90608BCE3EF14ULL, 0xC8C8EC3FB842DC6AULL
        },
        {
            0xFCBE5F811CB7A4A3ULL, 0xF0C8926604CD58CCULL, 0xD9E9FD5CC92EEBE7ULL, 0x208FCA2A1D377EC3ULL, 
            0xE34A2D863486A2EBULL, 0x883F86AC6AA893B6ULL, 0x4A695A9D35CEDEF1ULL, 0xF7B19A0BBD38AD38ULL, 
            0x25FB34A570CFEE20ULL, 0x9599C09C3E04ACE8ULL, 0x6550B358CB737790ULL, 0x6D779073F99474E5ULL, 
            0xD7498B8D22DA69C7ULL, 0xCFCE95383C04FB83ULL, 0xD843B69615F72850ULL, 0x8057BDEECFD91264ULL, 
            0x9A7F63EFB4774E24ULL, 0x7E55E114BB9A60DDULL, 0xC9441EFD5F973B28ULL, 0xB64A0716880E0665ULL, 
            0x9D8A7E36DA6C77D1ULL, 0xEB4F4C62E1F40BBFULL, 0xFEEC11BDC84BB4B3ULL, 0x7ADE51C5E78A8FB5ULL, 
            0x42922A6ECFA8EC48ULL, 0x9F367A2D360BE81EULL, 0x1A91A5B6B85F589AULL, 0x1BE669962DD23690ULL, 
            0x47153F09A5276ED3ULL, 0x15E7CEFB6519C8E7ULL, 0x16893C87831E98E0ULL, 0x7A7BD190098581D6ULL
        },
        {
            0x7EB23B8C60519959ULL, 0xF2E0AE2B77D6024CULL, 0x7D0C99595DBBF12BULL, 0x10CDA5D5349D3B0FULL, 
            0x9626A4D17B89556EULL, 0x22CF47CD318BFEA2ULL, 0xC67B683E6AFCEA20ULL, 0x1708E0CB97266A8FULL, 
            0xE14E5A2396BD6133ULL, 0xA4AC8E227F547255ULL, 0x64584574CF058531ULL, 0x2451EC984AF65A71ULL, 
            0x73456B60830E3D12ULL, 0x8E1F7E0DE7DF53DDULL, 0xB667E41DA9A91081ULL, 0x68CF460D89D2B406ULL, 
            0x340047F4575B7F40ULL, 0xC2A6AD3FAD8BA278ULL, 0x9DC06854BE13F898ULL, 0x6868542654902ED2ULL, 
            0x7288D1A7587F764DULL, 0xEF1DD4AE58D86ED7ULL, 0xDB0BC1EC0375CE3CULL, 0x48FC367444B6F764ULL, 
            0xFE5B3C343F003CDFULL, 0x65AA0259C718A097ULL, 0x304A5F42C28E85BDULL, 0x1D89988084DBFE22ULL, 
            0xF3B67A1F2AD43872ULL, 0xFEA5044F37A3795EULL, 0x3BC60BC571E7E0F8ULL, 0x7A80FA369932359FULL
        },
        {
            0xDA0B15E65CCF3775ULL, 0x06FBA91542A0B853ULL, 0x74C44BB58C733A82ULL, 0x68D03CE3B10739A6ULL, 
            0x7B8CA417A5C37927ULL, 0x46BB0EFD1609C2A3ULL, 0x613C9E8896F1CE60ULL, 0x60E507159292A787ULL, 
            0xC1A11A3E4E2E1018ULL, 0xECF11B1A676CC5E7ULL, 0x4F30D9FB27AFF32BULL, 0xBB4267A8696CB667ULL, 
            0x4871EDFBB1F4338EULL, 0x15D490A2AD40951EULL, 0x539AB54496147B7FULL, 0xF92AF933CDA792EBULL, 
            0x8C7C26125FB0CB95ULL, 0xCF1697545C4ADF91ULL, 0x485152644DD4AF52ULL, 0x8FDA4D549E140552ULL, 
            0xD6259504A7A0A3EAULL, 0x81037B6F2D4791FEULL, 0x94C79DF0BF5CD93EULL, 0xBE7E094DEC45C98BULL, 
            0x0EB7FC391FC0826CULL, 0x7CCAC24C63E5F2F2ULL, 0xC8F058DF0A6EC378ULL, 0x2086CE9BF41A7577ULL, 
            0xFE3A322B4D6C29F5ULL, 0x462CD5858F97C37EULL, 0xF8A3554F4FA64DD0ULL, 0x78731CE8DDDCD689ULL
        },
        {
            0x2FD17AAFDA524002ULL, 0x926710FF1E5444D3ULL, 0x88FDBFB95F27E70CULL, 0xEBECD12620D8BAC0ULL, 
            0xB501D9CD924DD4BDULL, 0xC91A69DB5730E123ULL, 0xA32935FE1D4A38D5ULL, 0xA436CAF5B97273D8ULL, 
            0x54F2570BCC236316ULL, 0x2A4EB24D8BAA20E0ULL, 0x285FD01E37D82FA5ULL, 0x0AD17F47DB7C31ECULL, 
            0x16E5D77CB63DDEDEULL, 0x896CEB32C8D99DB9ULL, 0xAB2D44F3B3A8C041ULL, 0x7985035962B7EAA2ULL, 
            0xEA52DC01C7B9E2D5ULL, 0x6877A74C82514AA9ULL, 0xD48A5FE348F9331EULL, 0xFD811943138E3B80ULL, 
            0x01E33742452869DDULL, 0xECC0F210249E82FCULL, 0xF9B40FFC27990563ULL, 0x82BFE2BA361BACA1ULL, 
            0x932E2906A4661977ULL, 0x9289F3D6A9A49F8CULL, 0xB9EBB93EA1B48CD2ULL, 0x7B5FC716341CF735ULL, 
            0x439FF50780E6D0A2ULL, 0x2ACAB284BA359CBBULL, 0x07A94DD79BE74269ULL, 0xB74CF4CB2D865C0EULL
        },
        {
            0x0BF5B8A6E03CA1BFULL, 0x3B06CD420C7CB3B7ULL, 0x27F04F12A093DC45ULL, 0xCE2B445F9C4ABE5EULL, 
            0x669FD8C2FEB39ECEULL, 0xDBC313BA55EABE00ULL, 0xA300BCDD3CF79F37ULL, 0x64E19D5944749347ULL, 
            0x9CEED1AA0D46ABE2ULL, 0x104314E4BBCAB8F1ULL, 0xB43C5F40C7B9BC53ULL, 0xDEB85D3C4B7A7337ULL, 
            0xE1865A4911E98400ULL, 0xB09BF64B7967DA53ULL, 0xFA58DBBDA28ED875ULL, 0x1FD42580DF096C2BULL, 
            0x98B1F85F5F5F8118ULL, 0x6C232A44237CE887ULL, 0x0043AA2A4E78359BULL, 0x9CB728F0901750E4ULL, 
            0x6D8F9071EE86D0C7ULL, 0x3480AD457D547AF1ULL, 0x99615810AAE31E69ULL, 0x5EC78DCB5EC4BA01ULL, 
            0xD65D1E9A8C08A8A2ULL, 0x8AD1EB1064B791D4ULL, 0xAF0D8DAA7EB551C0ULL, 0x7B7165914FACB649ULL, 
            0xA7442FE31D1399CBULL, 0x2088F673938F3A66ULL, 0x8014278E0A66E9CDULL, 0x4F9D04F728A0533BULL
        }
    },
    {
        {
            0xC4FB946D4E8AC9F5ULL, 0xCF0F6F7B88858317ULL, 0x90C84CF9F272AFE4ULL, 0xB894F55123491B2CULL, 
            0x887DA9D1CB4B96ABULL, 0x48BF662112B1BA74ULL, 0x6885ED7AAB4476D0ULL, 0x1A3622687B4702EDULL, 
            0x19B5267D2375EBF2ULL, 0xF38AA79FC4F0ACEFULL, 0xF8A220F4E7082BEEULL, 0x4F97E706BB7F83BBULL, 
            0x9220B1E62EABA641ULL, 0x3A788F763C123057ULL, 0x7D625615987B63A7ULL, 0x9C304933C34C31B6ULL, 
            0xAABAA357CA47A04DULL, 0x5B81020BC444B689ULL, 0x889EFF53769A4009ULL, 0x5EFAFFE91B2C6A26ULL, 
            0x6EBC59593713CA7EULL, 0x2860CAB178FD12BDULL, 0x601DAB206ACEE060ULL, 0x040258FB82E6C515ULL, 
            0x17690A46A57D2147ULL, 0xCAA54671FF21355FULL, 0x93FC34369E1A509FULL, 0xA9A2D7D317FB4ECFULL, 
            0x3CA3F20C170531C4ULL, 0xFFEAB22AF7658397ULL, 0xC4E5981B9F0A64B9ULL, 0x913280E516752861ULL
        },
        {
            0xF1EBA5295038B754ULL, 0xB689CF18B969F141ULL, 0xBEB2EE2C77DB0D17ULL, 0x8173CD0E665BA498ULL, 
            0x06D9CA830B6FBE14ULL, 0xD3F08882954558A4ULL, 0x85F45357E508E4F8ULL, 0x8D69E56A304A04CDULL, 
            0x069DFD0DC6276FD0ULL, 0x9CCE85C659D93DFDULL, 0x0D84248CE9610A89ULL, 0x63BCCC9C0F1911B1ULL, 
            0xAF416D36BFBEF110ULL, 0x826313E56350F364ULL, 0xC6BB122E66DDF0DCULL, 0x26D548DB3404B15DULL, 
            0x1CA744BE0BDFCD48ULL, 0x50E8A84E163BB9DEULL, 0x9123B2930FBAF299ULL, 0x60749DAEC163C001ULL, 
            0x5E35032E9FFAD7EAULL, 0x53F67592E907B8BEULL, 0x579DDC3F1C9172A4ULL, 0x47365AF5160F1F46ULL, 
            0x098D84F6F3D76C4FULL, 0x4921E458573F2772ULL, 0xBA21CD11D887ADB4ULL, 0x4FE150BC97F0C689ULL, 
            0xBC1250063A186EC2ULL, 0x989F1528432626DDULL, 0x801249D9FC06BFC6ULL, 0x7AE922DC512525CAULL
        },
        {
            0x7CF36BDA0EDF2948ULL, 0x94B944BD40780974ULL, 0xA742D96768DBCE73ULL, 0xDCD35CF116AD8EBAULL, 
            0x9E87C60614C7A355ULL, 0x576422F37C7FD7A4ULL, 0x76818650A33F37B9ULL, 0xAFB21CEA66342995ULL, 
            0xA416018BE94FC2BBULL, 0x13F4D70961690CC1ULL, 0x9B3B274A771A6C85ULL, 0x2A52263B9BE022C7ULL, 
            0xE611A53C41B571BCULL, 0xF6D1227870090D0CULL, 0x1C4DE5918F57410AULL, 0xCAD9E9D7DA1CC3A2ULL, 
            0x8A460BF1060782F2ULL, 0xDB04DFF083736575ULL, 0x1A9A291D6E3CB03CULL, 0x3515488893B2D1F3ULL, 
            0xBE5159C377EA52D6ULL, 0x0C18E5DEC3E607FDULL, 0x7CB9F27A7E6328CFULL, 0x51B425422F7518E7ULL, 
            0x953CB45D2CF1CFACULL, 0x52F331BD4C21F8BDULL, 0x6C019D86EA877714ULL, 0xE789E0BD40950547ULL, 
            0xCA463366E2C51B37ULL, 0x83A273A88C606EE0ULL, 0xAD0EBC14AD930CEAULL, 0xA9CD6F864FF5529BULL
        },
        {
            0x8F4F8D3A8AFB29F0ULL, 0xB87D612BF228E0E9ULL, 0xB453867C4517FEDFULL, 0x339EAF98257485AAULL, 
            0xFAF9F5BBB7705274ULL, 0xE59BAD8E435B81A6ULL, 0xB70154769FFA1AA7ULL, 0xEB51C599DCF5D793ULL, 
            0x25369608ECBB58BAULL, 0x7650445F1B677E29ULL, 0xA34F2C8FBC424273ULL, 0xC0250BBD749E38DDULL, 
            0x1FAE9F2BEA0176CBULL, 0x3A8C4C4878C7750BULL, 0x51AF432EB42B7B57ULL, 0xA7A0B4CD6537B7B6ULL, 
            0x325E3E106327B6BFULL, 0xD4CCBD1B8331A5ECULL, 0xA74B62B9447B23F0ULL, 0xCDAD55E599599F8DULL, 
            0x56A169233A7FDD16ULL, 0x10D365D10EF98DC3ULL, 0x114B28EA85BF4F55ULL, 0x75F63618F5027735ULL, 
            0xC4AE8DD00FD84181ULL, 0x3155823085EBE081ULL, 0xFC14D37F44D115E8ULL, 0x1D86CB3AAA54826FULL, 
            0x0C94C571CFF49161ULL, 0xB7096F3D177E64F6ULL, 0xF5ED8DD07993E544ULL, 0xBE9751F2EFE44166ULL
        },
        {
            0x24A3787E60D1634CULL, 0xAB3BB0026F8BB836ULL, 0xF30C05112DD5398BULL, 0x4DFDD788BE73CDC4ULL, 
            0x4BB36035AB20C7A3ULL, 0x1E47B334BC4E142BULL, 0x89C50B24C793FA68ULL, 0x20501503FDDCE286ULL, 
            0xC1E0899EECEE8E6EULL, 0x2CB3666A96D77E45ULL, 0xC5BD46A262E770B0ULL, 0x0E9FA1278FE8E5E7ULL, 
            0xCFF30B47B5860D67ULL, 0xD1ED13FEB5493B83ULL, 0xB1404E57B5AD7F2AULL, 0xE90A6EB9EBD44976ULL, 
            0x36E3050E4C9EBC27ULL, 0x932A7B796CA22DE1ULL, 0x7E1FD578D9CE9779ULL, 0x515924AA9BD61C0AULL, 
            0xE3157807A3435220ULL, 0xA32F71F795075976ULL, 0xC8384244E93C3156ULL, 0x72189F171972AEF9ULL, 
            0x16F16D116FFE2D85ULL, 0xD75B63776CB232D9ULL, 0xC0E926A63C90D7AEULL, 0x167B6340F13D308FULL, 
            0x76FFE2F84781A0F4ULL, 0xD6EC8CA0A6529B91ULL, 0x3D84FD0D849A2878ULL, 0xB4449E177EE26054ULL
        },
        {
            0xC80CD12F4B12575DULL, 0xA7DC2036C044FBA3ULL, 0xC6113EA18EE38281ULL, 0x6FD424EF32A2286AULL, 
            0x5D3F564360E648B4ULL, 0xC304C2624E8021F2ULL, 0x52140918722992E9ULL, 0xE6C4B0F604AD152FULL, 
            0x5D5FC1088A6F6E13ULL, 0xC5A9F562DADC0696ULL, 0xD36B035BC45A6A38ULL, 0x7315015E3D532A44ULL, 
            0xD0F4B8FD8C65E23EULL, 0xFB1F961E4759A5A2ULL, 0x4BCA9AEF9241F86FULL, 0xB606478536E6A0BFULL, 
            0x1276ED8A638B39B7ULL, 0x9A41B19A2EC93B12ULL, 0x7624956159908BC0ULL, 0x8DDA4EBD3009791EULL, 
            0xF41140F09C2CE943ULL, 0xCD4211C00BB25437ULL, 0x5943CFDDCD27D4D3ULL, 0x1D7DED9560ABE301ULL, 
            0xD9E28C2276A9BE6FULL, 0xC77272A74C15A4DEULL, 0x113702D22F6309E4ULL, 0x505BFB84BD45FE38ULL, 
            0xCCF1DF2BE060A8B5ULL, 0x3BA7F56509DD4343ULL, 0x7903653E11C94C0EULL, 0x375BD5AEDDCCE53FULL
        }
    },
    {
        {
            0x7196BD5EA9BA49ABULL, 0x0DF24504A4B3C84BULL, 0xCC70D761E43BA7D3ULL, 0xB34F2F2904133567ULL, 
            0x58B97D613CABB945ULL, 0x3FAC367BC98055EEULL, 0x8487422CF4A0207AULL, 0xA0F3425F79A3EA52ULL, 
            0xDD616D1F6385E844ULL, 0xF0005601E34CA716ULL, 0x9F0D45AA3C7F6A68ULL, 0xD3F1454AB5C1D310ULL, 
            0xD5FFFAD66A1D20AFULL, 0x3CB52FF7754EA47CULL, 0xF551B8B0AFDCA298ULL, 0x8D9D442EC4AAFB08ULL, 
            0xB0BF8B2158E3C529ULL, 0x253F2E4A27E69D6BULL, 0xCF4B0D99233D04D1ULL, 0x32CD466D2EC9EAB4ULL, 
            0x1064963A2FDD483AULL, 0x7D7B722C9F2001E6ULL, 0x290246B43323EBC4ULL, 0xF31748C6CD9F4699ULL, 
            0xF3C022CBCD6AB7A3ULL, 0x840237A442BBBD41ULL, 0x49F931D58E214561ULL, 0xCA91173B8E3F567FULL, 
            0xABC785A45D8BDB85ULL, 0xBC71496127205880ULL, 0xE8F1EC83F5E1293CULL, 0x9E2B2CDC3C433B25ULL
        },
        {
            0x9AA7CCAAE253DBF0ULL, 0x2D616B06280C11A0ULL, 0xC389EA7D819685E1ULL, 0x040035910F315B08ULL, 
            0x93158BD768367D6FULL, 0x37A47C8C7E8BE9BFULL, 0x9C739EE65212771BULL, 0xAA7C264E0AB9AD82ULL, 
            0xB106A88302DFB790ULL, 0xA3893805903E8076ULL, 0x0EC007DFA04BAED3ULL, 0x9FD8E209375AEBF0ULL, 
            0xF7D81C0B635DC7A2ULL, 0x01DF6B20BECCBBFEULL, 0xB616D28D20F5DCE7ULL, 0xCAF32D38C0A30CBBULL, 
            0x9F0C4F2D90C8FA37ULL, 0x74AAFE650510EFDEULL, 0x890970A2E6A7FCB4ULL, 0x941F87121F76507CULL, 
            0xE226865C483AC9E8ULL, 0xA7256BCFA8C51072ULL, 0xFAA8952F72568C33ULL, 0xAFB869161CA3D32EULL, 
            0x956F5821AF51E3DAULL, 0x761DAC8B8F331A46ULL, 0x50890D924ACCDF10ULL, 0x9AD085DECD9E3629ULL, 
            0x5602AE5DBC8D3C56ULL, 0xCF88D7EB70B3AD36ULL, 0x58E876C22B1D01B4ULL, 0xE396E0FAD7725FD4ULL
        },
        {
            0x7AA555985E2D7C1EULL, 0xFA001A3A56202325ULL, 0xEAAA4C1EBC1305CFULL, 0x603B32828DCF96F4ULL, 
            0x3418BD00F26648C0ULL, 0x68A4A802BCB9D832ULL, 0x6988626E8129296FULL, 0x3EA3696754C2AB2BULL, 
            0x9F861A6EFD1B145FULL, 0x01E3BE6DA0BEE518ULL, 0x15C2E8BF3119DE9AULL, 0x63F1E2044D73C9DCULL, 
            0xA6A1D57C1718C2D9ULL, 0xCDF04C551855657BULL, 0xCC64641B189E6DFCULL, 0x21D376631D3CEA15ULL, 
            0xA6D9870C853D9577ULL, 0xBF68C21E9DB44FA2ULL, 0xCFB92C42A6F161D4ULL, 0x5782F6FAF2E1C8B4ULL, 
            0x7AA40A181FF74D90ULL, 0x13B231A0B2AC6DDFULL, 0xCBE270299C8C238BULL, 0xD4010C9C250139EDULL, 
            0xEC8CA9E21D407604ULL, 0x6E700F48E1A893A7ULL, 0xF82AE6CE54DF7029ULL, 0xE72871FA6FD5F26CULL, 
            0x4A91D113E4B0FF2DULL, 0x5A61590D2425E0BFULL, 0x7719FB2783955EE6ULL, 0x5BF9F890EF6384E8ULL
        },
        {
            0xE5F80B57BC9B45A7ULL, 0xE97E680D97AEB6BEULL, 0xF681D34896CBC5A5ULL, 0xF931C7363BFD88F6ULL, 
            0x9A20DFD950BCD385ULL, 0x43DAD239D6692864ULL, 0xE3D63573C0E9C61FULL, 0x1E38EE4C64AF7A20ULL, 
            0x2E611F57CE47018AULL, 0x2109B3324EBD6009ULL, 0x213DF8211B2AEF85ULL, 0x68EE1F8B46EDF125ULL, 
            0x721EA4C3DFBB6496ULL, 0x5404BFEA68CC8276ULL, 0xA14E8B193CE20B00ULL, 0x3F907E58BEA89F2BULL, 
            0x56D86F53EEEF89CDULL, 0x0838F922149850C1ULL, 0x980D00240759D6F4ULL, 0xAA57876729A72D1FULL, 
            0x2931C9FFC3BD880CULL, 0xFCE338030FD2E13BULL, 0x94E182A6613FA761ULL, 0x5016B10F40369C46ULL, 
            0x5A606311FEF0EC05ULL, 0xD6EF8E029D9B7008ULL, 0x07451D1EEF8F80C4ULL, 0x1BCE3FFBD78B82B0ULL, 
            0x25105C5E22165F09ULL, 0x15D5F86E1C81C965ULL, 0xDEE3A12AA40B3711ULL, 0xBA74907341C81D4FULL
        },
        {
            0x0E9B7C81EAFB4A80ULL, 0x74925D976F797232ULL, 0x27C04C480CEB6BF2ULL, 0x161FD718109F5F06ULL, 
            0x7ABFE1370D6F1BD9ULL, 0x6C2DE8F61ACF53A4ULL, 0x5BA950EAB72A4AF0ULL, 0x8A07E3773871D062ULL, 
            0xF5AAC64DCC97FFF8ULL, 0x050A41AEAFC8A83EULL, 0x27E9102AB034D61FULL, 0xD1198C890B6ED483ULL, 
            0x7E73A8A9F199415CULL, 0xF2AFDDDD6AA26C59ULL, 0x05CA4CCB460A94B7ULL, 0x7EBD1585EA450742ULL, 
            0x2CB8ECD9BCBDE00EULL, 0x06673E8D3FC65270ULL, 0x726DB0423A277938ULL, 0xCE794AACC498DF2FULL, 
            0x2070AFD3441B1B28ULL, 0xA94EB601D1324C5CULL, 0xFCE874B17460FA34ULL, 0x4AB131305739AB68ULL, 
            0x5E3F6D518C0981B2ULL, 0x51C886FE352E7ADFULL, 0xFE8D6046059A6AD8ULL, 0x6325E70B5D798854ULL, 
            0x9A673B7499CB5315ULL, 0xBA63A328477F3E85ULL, 0x1418B243238D8262ULL, 0x580FD8E7F421598AULL
        },
        {
            0xB174474BD43B133FULL, 0x090A699777E7B6E5ULL, 0xCE345FB16A148925ULL, 0x86DA3E9F0F0B1CB6ULL, 
            0x9794649C771A6855ULL, 0xF58063380CF62F88ULL, 0x4909A743435019DFULL, 0xDDFCB45139FAF876ULL, 
            0xD4C81353C9F4A95DULL, 0x1FFBF25375851135ULL, 0x95A889ED156573CAULL, 0xD43F10A835D71D23ULL, 
            0x043BDA86570C8324ULL, 0x9AB634FE4C37261AULL, 0x538E17EC006B10B5ULL, 0xC5A23BDE191203DDULL, 
            0xA83C41425B27B963ULL, 0x7F00C01FAD79CA93ULL, 0xA869D2665FEDBC20ULL, 0x08A1DB2D906F6D7AULL, 
            0x2655D1D49918C3BCULL, 0x11483B46102A3A97ULL, 0x2F219E389B083B65ULL, 0x10CF6BC3EAED822FULL, 
            0xAE38B0F74E776052ULL, 0xB647C3FF56DB978CULL, 0x461DC6EBEB7FCC15ULL, 0xE2E50C2BF464DAB4ULL, 
            0x8B541C1522EFB4D4ULL, 0xC3582917809873FAULL, 0x8199E8939110903FULL, 0xC92AD1E06D976DA9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseEConstants = {
    0x92A3198E7119B807ULL,
    0x7AC526EC00BAAD83ULL,
    0xC41A1BB795356459ULL,
    0x92A3198E7119B807ULL,
    0x7AC526EC00BAAD83ULL,
    0xC41A1BB795356459ULL,
    0xC9063BF0B6E25B60ULL,
    0xB73C2B5BDCDF746FULL,
    0x96,
    0xA9,
    0xAB,
    0x82,
    0x2E,
    0xED,
    0x4E,
    0x86
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseFSalts = {
    {
        {
            0x6C2F138849332F32ULL, 0xAB468B665F62751EULL, 0xFB921A34D5B8EDF1ULL, 0xF9AB7617B7820697ULL, 
            0x6FD9EDB3CD69C6D0ULL, 0x5D21A945C0387040ULL, 0x914DD6F7CB6921FBULL, 0xAB841B6603C064E0ULL, 
            0xB015831EFFACED90ULL, 0x54E97611AF5FD1D2ULL, 0x85D45358DB478864ULL, 0xADC0210341E8EC7CULL, 
            0xB59405447A66D395ULL, 0x06CA145F47FAE352ULL, 0x487C1BA3DD98B616ULL, 0xAFE16700683068CEULL, 
            0x9EE7CC5B0981EDFDULL, 0xF9687AD99DAF9455ULL, 0xA9C994A203129F20ULL, 0x7BD2109157CE36F1ULL, 
            0x342F1AD6CCD666CFULL, 0x67BF84A229D536CBULL, 0xD5B035C8B07D60D1ULL, 0x5BC231E507343F1EULL, 
            0x544392EB28122704ULL, 0x7716FB3AE6968E93ULL, 0x593F9225920192D2ULL, 0xC04C3C2E086246E0ULL, 
            0x9836E4BF9D485C25ULL, 0x55FD5DA357264EB3ULL, 0xAD524EBF8377077BULL, 0x40E1DBD721AC5DFCULL
        },
        {
            0xCEBE56EBB55B47E7ULL, 0x32D6865F0AC987F1ULL, 0xCE200603E2B24E95ULL, 0x9C0F10059B57CBA9ULL, 
            0x688A7B77E6B0270CULL, 0xE97218669DB687D2ULL, 0x1E8EC6E123B05AB7ULL, 0xA9DEA100408526A3ULL, 
            0x630184C19902CDCEULL, 0xAF4932C5CD63CED3ULL, 0x2DCA67561B7B3A2AULL, 0x4D10A503C2FE846AULL, 
            0xCB6478B9291B77C5ULL, 0x51DFF90FBE915E0DULL, 0x037C0F9207AC3116ULL, 0xAAF172F360205799ULL, 
            0xA6759B6D47CB0430ULL, 0x0F716227E620F811ULL, 0x63AA2CB5F3082CFCULL, 0x2BABCD827E7EE2DBULL, 
            0x41F81D3B2B1BFF0AULL, 0xD1DA216FDA656C2EULL, 0x61378254893472BBULL, 0xC9FD88CD5E9C8081ULL, 
            0xCFA9CB92DE7F254DULL, 0x9071D7FFFE955A10ULL, 0xCFCB2FF19EE3F7BBULL, 0x91CBA76FD309F9DDULL, 
            0x69AACCB08BF33170ULL, 0xFBF5E12C778661FDULL, 0x184458E92807B24EULL, 0xEDC0D01CFCA8E754ULL
        },
        {
            0x06540CC9FD368D2FULL, 0xF56FA84F998D941DULL, 0x35DAC2EF32BAD464ULL, 0xED2B8AB7A54628E6ULL, 
            0x67B533252030F4DBULL, 0x14696D4836C6C06BULL, 0x8E5FD778CDAF54A3ULL, 0xBF63DF9595818696ULL, 
            0x61CC66B8D0D110E9ULL, 0x62507FFCECF9196AULL, 0x41BE01030D95A4A7ULL, 0x08DFF5162F950541ULL, 
            0xFCE42FDDFFA78775ULL, 0xB2E939FC09020696ULL, 0x9A4A191915560101ULL, 0x42D7A2F66357B9BDULL, 
            0xC50B601208763EBFULL, 0x09BF8DD5EE326EF3ULL, 0x7F6995F5902C8688ULL, 0x081DAEE76B3ED6EAULL, 
            0xEABA881085309D1CULL, 0xBDFF248045CD5627ULL, 0x2FDC86004E85BD5FULL, 0xB33D8F8F14819BB0ULL, 
            0xCCB5D0F92A98853AULL, 0xBAD30871E9A6C97FULL, 0xD8D9EAA74858CA0DULL, 0x6B65966AA048E198ULL, 
            0x1B03D1A278E1069BULL, 0x468153D024735F1FULL, 0xBDE629112BAB4D48ULL, 0x2070B6016CA8F379ULL
        },
        {
            0xD9F37140FDB754B2ULL, 0x0AF63BAF8490BC94ULL, 0x3510F5680679555EULL, 0xC2DAC70DD938C975ULL, 
            0x7A8FD78E66FD6600ULL, 0xC877D10EBFD5DFC9ULL, 0x68AE9A49B437B089ULL, 0x7DDAA7DF1EF188A2ULL, 
            0x46224E448FEA4C44ULL, 0xF32214A96C9E4EECULL, 0xD634BF2206DF2015ULL, 0x7E60D671B64C4E52ULL, 
            0x532749FFB95FDEDFULL, 0xC622B37B829EFCAFULL, 0x6C60686BB43F67ABULL, 0xB12BF45872AC0B3CULL, 
            0x84EC9AD069CA961EULL, 0x8D3D113120E99D6DULL, 0x97D7D73766E43256ULL, 0x7BE6994BDFB25415ULL, 
            0x3D8DD7C21F6B27F6ULL, 0xC2C87203E4F73977ULL, 0x37329207C3BF9A2EULL, 0x624027C66C7DF269ULL, 
            0x6CA72BCA6A2CAF62ULL, 0xB9F8C7762C85927DULL, 0x9FCFB960D0E36779ULL, 0x944CE43F1311AD31ULL, 
            0x5A68C2976FC1FFEDULL, 0x19C7055B2A9C0884ULL, 0xD767DE282E02C4FAULL, 0x8A456317C7D02EB9ULL
        },
        {
            0x8DE7A9C276646FC1ULL, 0x1216A10FCCF069F8ULL, 0x1BA3DD342F04C674ULL, 0xB687F210EBF35B8AULL, 
            0x78E5505AF5F996CFULL, 0x122BF17857DA289CULL, 0x0CC050C6C720BB1AULL, 0x86BBC1F644DB2F53ULL, 
            0x5264148B941BDA3CULL, 0x6CD4FB73C00097F5ULL, 0x02D91447938B400DULL, 0x4B7153F66CD909A3ULL, 
            0xEAF2336A18C31000ULL, 0x7BBAEDF1350145E0ULL, 0x17AEFC00CA5535A6ULL, 0x4B089419B2DC8830ULL, 
            0x08DD46506F76224DULL, 0xE4C3A1E9744DFE4BULL, 0xEA41DA75D4EDF158ULL, 0xFE8EF81766FCF9E4ULL, 
            0x660B2D7839ED7500ULL, 0xCB4E4E02D479864AULL, 0x9BE152B4AECAA686ULL, 0xEAE600E536969CB2ULL, 
            0xF0DB873F5837F1E1ULL, 0x0FCE718A08B9D457ULL, 0xF5DE202916CEA35AULL, 0x1CE9E63F4D463103ULL, 
            0xEC7EE62D0F7DF5A6ULL, 0x49D68A448432174FULL, 0xE290F14A5B7193ADULL, 0xC07AC4460FC4FC17ULL
        },
        {
            0x3368E3609A3061BAULL, 0xF216BDF7EB020DFBULL, 0xF783E273855802F5ULL, 0x65586C32864C5FB6ULL, 
            0x72E86714ECBEB0B8ULL, 0xB9AD90A8C1752A73ULL, 0xDE5AD64B0E946602ULL, 0xE4F973833F222ED8ULL, 
            0x0DFE7D37D4E21CD8ULL, 0xF3038B539F4F56E4ULL, 0xE3E56DE8EFDA2A9BULL, 0xD6ABF3185AB4B28EULL, 
            0xE00A591FA2851A94ULL, 0xC297728A53C31774ULL, 0x76E9574EEBC5E4AFULL, 0xAB131892B358DB93ULL, 
            0xD886EF0EC1D69B3EULL, 0xDF6B69A94BD1432EULL, 0x17B34E7DC3FA8201ULL, 0x8C65D036AD53F1EDULL, 
            0x90F4F4DC7869607CULL, 0x8FBF73EBB0BE798DULL, 0xD6257CDD903AAA51ULL, 0x2F435CA7FF638ADEULL, 
            0x4075DAF2CFAD46AAULL, 0xF4EFC88ABD97B7B2ULL, 0x4E29F7B747DDC96EULL, 0xF32C86E94A227D1FULL, 
            0xCC6A432A6EB85642ULL, 0x776FDB4E63DD6AEDULL, 0x593A6BE0CFC288AAULL, 0xF751A035FA55C166ULL
        }
    },
    {
        {
            0xC4226FCF6F23BB51ULL, 0xD831B111A40C6F66ULL, 0x5E79B259CF0EC277ULL, 0xABFF6D8E66590CCFULL, 
            0x0FD2E3744BEF9ADAULL, 0xFBD9542176BF5D47ULL, 0x21FC65A3BFC29A06ULL, 0x9A15F9EB48120261ULL, 
            0xB311F9E4D63C6BA9ULL, 0xF0A70F1A4EEF655CULL, 0xBC37FD43F08955DEULL, 0x671539FF2EFF3F69ULL, 
            0xA44EC4813F7C91CFULL, 0xC6B58DD903A6ABD3ULL, 0xAEE582A24B90A897ULL, 0xAE134397A7FAAF56ULL, 
            0xAD7127EA7AEFD0A4ULL, 0x4EE45931F8E42BDDULL, 0x31841A676DFB25E9ULL, 0xD58416FD3D62BB81ULL, 
            0x4E3BD40777F55902ULL, 0x0F175AD09CCDB084ULL, 0x7922650AA8C5DD21ULL, 0x502C846FB9162CB8ULL, 
            0xAC9422ADB158BAC2ULL, 0xCAB9B4F332E6867EULL, 0x46A2497FA043D93CULL, 0x0CE5F1280C090D03ULL, 
            0x4F8E512CD7F44C20ULL, 0xC4862710C47F42BDULL, 0x46585E2DB1FE7650ULL, 0xE383496930D368D3ULL
        },
        {
            0x51F3576A32668C57ULL, 0x880A58C7DE50DA51ULL, 0x1BE9038483A80A74ULL, 0x5D555DBF39A63BBBULL, 
            0x75DEDE96F47C5587ULL, 0xF2FDB07DA8B4E238ULL, 0x77AA0B2F90378EFEULL, 0x2D50BAB47E856FACULL, 
            0x58E6084189D5BAC2ULL, 0x356CFDE2F7A3525BULL, 0x30DCBD33DBB10787ULL, 0xE06333E437CA484BULL, 
            0x27DE7BB042B62035ULL, 0xAEEFB623979ACCFEULL, 0x46F27CD9DDC7BA00ULL, 0x0881BE64E5E49CF3ULL, 
            0x992499376EFD628EULL, 0x1CD9A9DCE76E5525ULL, 0xBA83C7256CC7C4B2ULL, 0xB5C4A24F58D21C1EULL, 
            0x6A551CAD924B59CDULL, 0x031C571E350C1470ULL, 0x9C76C692B5EE33F5ULL, 0x1BBC2909701872B1ULL, 
            0xF269FF415AABA60CULL, 0x41A8A5737CDF74E4ULL, 0x08F836EC65CDA526ULL, 0x803A095DA805F28AULL, 
            0x7829260982E9604CULL, 0x9BADC713EC1F5D1CULL, 0xB65264E62BF7DF37ULL, 0x03FF9119821D893AULL
        },
        {
            0x39F4513BBAEA07A6ULL, 0xE85954E8EAF3A64CULL, 0x2282904C490414C0ULL, 0xCF656888882D8569ULL, 
            0x15E4FAC2EDF2339CULL, 0x3B3A5E0B0E91D123ULL, 0x86BE4D4BB0184D43ULL, 0x2FAFC7E483350AB4ULL, 
            0x2970D404E84F616BULL, 0xE39909039BA64DC1ULL, 0xB3D070190CEEA40BULL, 0x44B446327661B1A7ULL, 
            0xA2ED37FBD50C5C2CULL, 0x7C4D7FC89A0655EAULL, 0x9E54ECE38B1371EBULL, 0xDD5424E5CA972025ULL, 
            0x3A59548FF21AF05DULL, 0x9B87E34C5AC917ACULL, 0x92858CEDCA9F97BBULL, 0x4641142EA0D7F91CULL, 
            0xEADABF3CD2DDD3EDULL, 0xE31B951ADB6A785AULL, 0xBEC6E17C70562949ULL, 0x7C3DDAD6C7A7FE3BULL, 
            0x8CF40687B9D76988ULL, 0x8E11D2AE49B07D04ULL, 0x2195D73C8C5D8AA8ULL, 0x3ADE2BF385678598ULL, 
            0xE89A71F593DF9A23ULL, 0x6F34B5B2FDC41BCCULL, 0x417F411B39446343ULL, 0xE0415E80674920DDULL
        },
        {
            0x15BF7A48F1230EC6ULL, 0x2D7E9909BA05FF50ULL, 0xDDCCBA09C3B7F2D5ULL, 0x24598DE503503111ULL, 
            0x13A934CDA079D426ULL, 0xD7C1700F7F8B7047ULL, 0xC9526A9CE1B54C22ULL, 0x774A2246C00066A1ULL, 
            0xDB90B96A57CEB53DULL, 0x0D0C28696E1B9DAFULL, 0xACBBD75220FBDF8BULL, 0x30924166E43F0756ULL, 
            0x31B2BC033398DED4ULL, 0x96E1163EAFA7A7B2ULL, 0xDBD77114835DD869ULL, 0x3C71ED387F6CE53FULL, 
            0x81347F9D3F9102D5ULL, 0xF78864936CF0BE70ULL, 0xD36F2D997B1C1807ULL, 0x25E264EDCDD910D7ULL, 
            0x55897A7C547495FBULL, 0x630D41E12EC719F1ULL, 0x8A3A92FFE11BB6E9ULL, 0xB9D95C796021D82AULL, 
            0xC4BD6D88884B3E5AULL, 0xB471498447D4F537ULL, 0xAB577643ECD6BADAULL, 0xE75D0BFF0627AD74ULL, 
            0x531FC7218298078EULL, 0x4CE9C359ADD80B92ULL, 0x2FD0D096EC43F6E3ULL, 0x5355690A737CD661ULL
        },
        {
            0xA586C38C144E0932ULL, 0x0FD2CBECB9877CC9ULL, 0xDC47B5194342EBA8ULL, 0xF56188AA532D4AC3ULL, 
            0x33647DE2355AF5AAULL, 0x7EDC735FA9F192D8ULL, 0x1385AB9AE19BEEF7ULL, 0xB430ED0BED518D8FULL, 
            0xF1853EC1506B1C0AULL, 0xC611580D06B5740FULL, 0x2B233729B275D4B4ULL, 0xBF3EBEFAE756EE4EULL, 
            0xC951FF35CF26249FULL, 0x41E90EF31A8BC8E9ULL, 0x1B4E135E7913F0C0ULL, 0xB8594994C1EFC54BULL, 
            0x9D68D835E3F3DBA6ULL, 0x9A24236BDD97A320ULL, 0xEED5ECCE1FE7DE8BULL, 0x6DF2F581D0C9EA65ULL, 
            0x8B621C15897D303AULL, 0x8A0C215360FB993DULL, 0x96D0F3A351AF9790ULL, 0x060DF75DA753A5C3ULL, 
            0xC81285CF4F91FC90ULL, 0xC9D84C60A4785DCFULL, 0x947594D6517DDA88ULL, 0x3383445BF315CAFEULL, 
            0x05ADB2981A549FB9ULL, 0xC122EFFF279570B6ULL, 0xED72E22806023C4AULL, 0xDEA1D64AA3B68E81ULL
        },
        {
            0xB1712E9BF48E5241ULL, 0x8E21BC74DC6C4AE3ULL, 0x095F3AA770C582BCULL, 0x9121579AFC0B709FULL, 
            0xACF22663CA785BCEULL, 0x55E03C81297B4A19ULL, 0x80DABBA9E34F125AULL, 0x18E08B500F756D83ULL, 
            0xC32BD25DF95D52DBULL, 0x21C3BF1FAA5C32D6ULL, 0x7527A66CBE9E5C8EULL, 0xA54C5C4DEE20437BULL, 
            0xDA8238EA9404AD3AULL, 0x38BCD0077B04D31CULL, 0x0F3890D6CF30007DULL, 0x33C66A32F44D9CB9ULL, 
            0x3CFDB1FBCCD04B44ULL, 0xE1B5298F90BDFBE4ULL, 0x518B057AC9AB5E61ULL, 0x95D8C392B8BC5AC7ULL, 
            0xEE4ABBD30F10E091ULL, 0xF8136AECDE1529FFULL, 0xF1240EF5D3D672BFULL, 0x8C207B0671045C14ULL, 
            0xD5FCB6123E675536ULL, 0x609CB1C699E60F7CULL, 0xBE2F63F29BFE744AULL, 0xB6C5967734B5A49EULL, 
            0x414DF6E155EBF8F4ULL, 0x82B301D261D894E1ULL, 0x1F3C17B75796175BULL, 0x3DD8114D6E433D27ULL
        }
    },
    {
        {
            0x69FE71CDD1E3BEF2ULL, 0x12457DD04A37376FULL, 0xB3E21FDACD85C507ULL, 0xEDC465C668BDF640ULL, 
            0xA77B886E5848D40CULL, 0x3993762A5591DBF0ULL, 0x72476A4AC6CF94B5ULL, 0xEA6EB9A6B7847A73ULL, 
            0x3CDD908DE7C0676EULL, 0x83A0DF72FFDF5AC4ULL, 0xD560C4686BBBF876ULL, 0x57949E8EA9301D68ULL, 
            0xBAF5E09ABFAD2E02ULL, 0xBB8BF99379B3C5EFULL, 0x7C944F1BAC59F9EDULL, 0xB261C4FE3EF25691ULL, 
            0xF57B8BD37A2DC3BDULL, 0x394F721E7366FECEULL, 0xB11CB2C4A5397FB7ULL, 0x142CF56776CFBE98ULL, 
            0x482642CF25E1DFF0ULL, 0x8EC266165D6EC9E3ULL, 0xE685C86AEF9776C2ULL, 0x9212D8DCB7960E08ULL, 
            0xFE8C3F2B334C96FAULL, 0x9C192505E47FA9B9ULL, 0x8E1297EAF1E966BCULL, 0x3FA730BC4BC36BAAULL, 
            0x53D1E8BF58A52360ULL, 0x0E538D6D981E451FULL, 0x27F56C4215342068ULL, 0xC0A9A615534B7162ULL
        },
        {
            0x7222CDBAAD8C32B8ULL, 0x081C05370A4D4A5FULL, 0xD88F7A3EBC0A7CB4ULL, 0xE355571E8821D8BBULL, 
            0xFED2F048072F2D46ULL, 0xD80ED38A073C85F2ULL, 0x43DEFDF2A51A7314ULL, 0x4219F5373EF8169CULL, 
            0x93DD65239DB63B1EULL, 0x09CA3DE4627F4944ULL, 0x4CA05892457F8D3CULL, 0x533F1EA93C5E88DFULL, 
            0x315BF6BECF9558F5ULL, 0x1329E6D1A0D8B3DFULL, 0xAF6E5AE7B4C36B19ULL, 0x6DBF09CF2A908FF4ULL, 
            0xA552543623A87805ULL, 0xB7AB3772883C4906ULL, 0xCEE75E8657466484ULL, 0x1DECA57C981C08F5ULL, 
            0x2E97DAD99D68C44FULL, 0x8C659482DC24635BULL, 0x3CB6DC3903B122A1ULL, 0x6D162F65968317CBULL, 
            0x59815BDB8B552C7CULL, 0x334E35DFD9ABF0FBULL, 0x92F446A67F31FD64ULL, 0xF16E5C1CD7EFAEA7ULL, 
            0xCD553C0F0714061FULL, 0x4FCE7459597C24C4ULL, 0x5025A4B265786892ULL, 0x21A2BFE8308922F8ULL
        },
        {
            0x5AC09F309229488FULL, 0x83F5C629D7B712EFULL, 0x804A5D212B1AB2C7ULL, 0x174D4F620A941DF7ULL, 
            0x5C86D651EE528378ULL, 0xE601EA51E2008806ULL, 0x845371E2023321A7ULL, 0x1DB1DC68E297A282ULL, 
            0x67F50DF6E46E5EC4ULL, 0x8E6CD3BEDD4DBEE8ULL, 0x9D38F60F98529421ULL, 0x601002F3102D8AC5ULL, 
            0xA233D1A193FB598CULL, 0xD757F02B1073BDB6ULL, 0xE041E60D333747A3ULL, 0x82921F9D84C2169CULL, 
            0x049374202D9EA58BULL, 0x40F7CD66EBBE2FA7ULL, 0xF5541FC70F39D2F1ULL, 0xEF6498AFD4D34EB4ULL, 
            0x505D2C8233B1385CULL, 0xB69F8E97FE17AC62ULL, 0xF53E6A5576A17B46ULL, 0x233AD6FEC4B111E9ULL, 
            0x4D881E088C7D6932ULL, 0xBA7BA3869D433687ULL, 0x3BB99CA3AF845609ULL, 0xEE92972A8119DE64ULL, 
            0xA445543CB7487DA8ULL, 0x544E2F68B927E925ULL, 0xB34EBCD3F839A5A1ULL, 0xEE1E91910D98E69AULL
        },
        {
            0xB7775790A1202320ULL, 0x1177E31C908BE7E6ULL, 0x313118213FE668E3ULL, 0x1CE7FC42DC816760ULL, 
            0x6536E4636B80DE16ULL, 0xAE2440B03352CCB1ULL, 0x989BCBD71A0D745EULL, 0x5E91F54DEC86B426ULL, 
            0x3758DA57F72E8D7DULL, 0x7A880E087CF8D0BDULL, 0x6FF928B8F6858307ULL, 0xAE2908C1DD4DB5DBULL, 
            0x98AC1899F3F2E7E3ULL, 0x0DF24355F5C12765ULL, 0x7AE5FDED01655B4EULL, 0x969F13C23B86D0D7ULL, 
            0x342B67BACD16722EULL, 0x0A9F7C67E2563C53ULL, 0x17FBF46A0239268AULL, 0xA28C808D00990C8DULL, 
            0x405A35EA54331ECFULL, 0x010343C702BF4DBCULL, 0x10685E6D55FAB94CULL, 0x0A045C0C8B018FF7ULL, 
            0x5EA86962234D5333ULL, 0x964BB03F88EC56B2ULL, 0x0F66519FC4C09DD6ULL, 0x2E614D85C7443800ULL, 
            0x8C0B5C787C6977B7ULL, 0x66BD1B1C051A4EC0ULL, 0xF50452C01A4EA4B3ULL, 0x27329981CE486237ULL
        },
        {
            0x9BCD66FE3CD3612AULL, 0xC8461ED3781F6BD2ULL, 0x601B108FC0AC2B80ULL, 0xE29EAB6C5BE09BCEULL, 
            0x6EF2C95F00C223F3ULL, 0x66E45B0DCB110D8FULL, 0x1FBD9885B234F475ULL, 0x3DCA4E244E213A79ULL, 
            0x1034CDA985CDD68FULL, 0x304B04D5AE3554C9ULL, 0x34EC7DFA356FD3E7ULL, 0x690C0612267391E0ULL, 
            0xDF7D5F3580F60DE5ULL, 0x5505170BB7200F44ULL, 0xB14DA3EE7373C223ULL, 0x87BD998C191B7C20ULL, 
            0x3E8567DDD3D3252BULL, 0xACD54A013F8B8A9AULL, 0xEE9FE425693ECA7EULL, 0xDB03F4E862FC07C2ULL, 
            0x23402EC4D5C3799FULL, 0x944EB2B281A69A61ULL, 0xB863F8801E4DB0C9ULL, 0x450E183390955672ULL, 
            0xC5C85CC35CA18DEEULL, 0x8A0AB1A5B4FA8506ULL, 0x4558F9D1C89FAFA4ULL, 0x2336713A73B6F37AULL, 
            0x9050EF982DA4B111ULL, 0x2020C19E9DE79580ULL, 0x400F438C54A3FE69ULL, 0x81B750D81CD58647ULL
        },
        {
            0xE79549C64A973C42ULL, 0x4941EFB6B4D96C7EULL, 0xF61F9141EB5431F6ULL, 0x347685F548C4C736ULL, 
            0x40937082DF979769ULL, 0x14D1D7C040E36EE3ULL, 0x006E145181C7B16EULL, 0x264C2103BD4F24C9ULL, 
            0xB3DB473CDDDCC770ULL, 0xE58FE8C0DFA2FF8CULL, 0x1162602F83BBB823ULL, 0xD29F38B19FC27B8FULL, 
            0x39FFC74CAFFA4CD7ULL, 0xB9047DB4F0A06C77ULL, 0x0DF210B17709B85BULL, 0xC88F6AAB51A2A9B2ULL, 
            0xF1FE6DB2602D61C8ULL, 0x59D03AEE436C431DULL, 0x76BB3AF19E2E8899ULL, 0x1C701AC488C7B12AULL, 
            0xB64C7543CCAE2B9FULL, 0x2C577935449BDD1AULL, 0x5D5001EAC3AA5741ULL, 0xE74FE9F1AD23E2ADULL, 
            0x71E5142C6E1C6EC1ULL, 0xFC88168C67D9BFCEULL, 0x4CD9E0DA07510945ULL, 0x26D19DEA4F7E8410ULL, 
            0x70EF1633A6723EE7ULL, 0x960942856A0F993EULL, 0xBCF01AAA69D4E830ULL, 0xB0FB2A2B56972B8FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseFConstants = {
    0x57DBB4B2275E91BDULL,
    0x22DC7806D5154032ULL,
    0x90F666108483F3D7ULL,
    0x57DBB4B2275E91BDULL,
    0x22DC7806D5154032ULL,
    0x90F666108483F3D7ULL,
    0x06651298C3B07B83ULL,
    0xDF0230272F367AE5ULL,
    0xF3,
    0x0F,
    0x6C,
    0xEA,
    0x66,
    0x56,
    0x44,
    0xE6
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseGSalts = {
    {
        {
            0xEA091FF9F1980EE4ULL, 0x29D3DE928A9BE0AAULL, 0x0B53E3721F6D0F08ULL, 0x4EC5FA19275BF3C4ULL, 
            0xE93AC75BF96EC067ULL, 0xF1FB3FBC7E87ADBDULL, 0x6B23B53D4B531599ULL, 0xFCB205D02190CED7ULL, 
            0x0AFCA77E96486F92ULL, 0x07215A74D041A742ULL, 0xC09CADD0342DCD1BULL, 0x998417EAA286F203ULL, 
            0x57FAF16815B2558CULL, 0xE2BF8E9350718B98ULL, 0xE53006DD12E24F70ULL, 0xE3AB207BAA931916ULL, 
            0x098FD00350AF8A7AULL, 0x3CD375C4A6600E3BULL, 0x88342A0BA661D4FAULL, 0x5592FA950A7B9C7DULL, 
            0x5A21C15A48342804ULL, 0xC62C84AB7490587EULL, 0x44FE4067E6382C22ULL, 0xBDD171771A86CAA0ULL, 
            0x1B823FCD83452C9DULL, 0xC24B6A3BC85A88AFULL, 0xBA351F38D7B5DE90ULL, 0xCCAA1A20762ADE1AULL, 
            0xC287995D68C9A95CULL, 0xC0B319C17635FB38ULL, 0xD6B6801666449ACCULL, 0x80672546F5324B33ULL
        },
        {
            0xDCC4CC1CBD16EF4CULL, 0xAD416F44BBCAF692ULL, 0x3B0E12CDC830C926ULL, 0x5B9D48BF01EB053EULL, 
            0x6A6840BAC4B2A265ULL, 0x13DAD72EE805E3D9ULL, 0xCA5F4DCC2D9103F9ULL, 0x5D201256591DF09BULL, 
            0xE5EF179B10685E0DULL, 0xCE74BF893ADE75DFULL, 0xE9800FFB10D462E7ULL, 0x5D7A74C589956662ULL, 
            0x809E7ED7ED282DBFULL, 0x90C679DB1CE8C0A0ULL, 0xA6B679689E6CC194ULL, 0xE098B2EE22EF8733ULL, 
            0x641C455EB978AF9CULL, 0xA17E8F2D3A591E19ULL, 0xB91E8CFCAEB28FA7ULL, 0x9F1410ED66A93C41ULL, 
            0x6F460C288B95FA5DULL, 0x3F210BF0DD30D022ULL, 0x5DD9296DEC3F1306ULL, 0xCAF0EAA04AFC2CBBULL, 
            0x02557A317821A018ULL, 0x686B5999C256422CULL, 0xFDAB9DC5DD9C5F35ULL, 0x3C2A6BE92FBCD584ULL, 
            0xB2BE74F4C5410FBFULL, 0x1CE8A0471C58B43DULL, 0xBE22904C7BC959AAULL, 0x566191FDE880AD54ULL
        },
        {
            0x58B770EC41C8E691ULL, 0xD46563CE057FBE1FULL, 0xD07172DB0E0E7FCBULL, 0x4E23DA12A536DFCFULL, 
            0x800076F92428D0D6ULL, 0xCC14106E08EDD006ULL, 0x38A2A7AB6B6E6F3EULL, 0xD07FD8ED00CBA9D9ULL, 
            0xB38A26EDE30B13A9ULL, 0x1B92FB47CCEFF5CDULL, 0x7E26EFB8CBC8124BULL, 0x209773AE1D5B6BEAULL, 
            0xE8F26622F76FFD93ULL, 0x002FE3F7EF5E0ECCULL, 0x9F847109C90DD6BBULL, 0xA7540DB2EE047DCDULL, 
            0x20F8E452B75641B8ULL, 0xB87B14E7782A1E9DULL, 0x3CE3C16FB2309BC9ULL, 0xDE5CC62C0F57C791ULL, 
            0xB6A0327F7AC58E6EULL, 0x503BDD5CAD08DFFDULL, 0x71A75A8F1B4CC560ULL, 0x5799527C01A0B1FFULL, 
            0xCF2162F6BE524FB3ULL, 0xC179B181F8635DC3ULL, 0x2954A8FBA6571311ULL, 0x87B07055A9405840ULL, 
            0xD17E5986F504CD5EULL, 0x0A4503FA88CB3952ULL, 0xF867D7172057133EULL, 0xE0706195B7150147ULL
        },
        {
            0xBC20DFCB604EFC9BULL, 0x38492FECD55F4C24ULL, 0x433735EC014CA99FULL, 0xFDCFE074BF95DB38ULL, 
            0xC0F57CDE8F6447F6ULL, 0x3CCA9FA709145759ULL, 0xE3C546EEEABDB37BULL, 0x79403A7FAC3CD206ULL, 
            0xBA2A940DE95F6256ULL, 0x9E91B9132FA9AB08ULL, 0x982CC2F8265E3D85ULL, 0xE99BEB5D36DAE6B5ULL, 
            0x2754EF75D7277BB3ULL, 0x22284CBE1CE9D876ULL, 0x1E0770DB0EAE5555ULL, 0xB57CB2051C240633ULL, 
            0x0AA4A751A54D0E1EULL, 0xC7707EAA5F5E0BBCULL, 0xFE378E3BA79645EDULL, 0x87AB027A0C2CBF64ULL, 
            0x085E2B8DE6DB0427ULL, 0x3553F670D45C20B8ULL, 0x583CD71F6607F1D6ULL, 0xDD2851F59DB8995DULL, 
            0xC00CBB0085E2728EULL, 0xDAAFA9FC7FA44705ULL, 0xD0A80A2813E3AEF3ULL, 0x0E0EA5C80CE5B367ULL, 
            0x211237B40EF44921ULL, 0x68DC7293350DE780ULL, 0xB87B68BC7A53F21EULL, 0xC3882E1D2AA74E6DULL
        },
        {
            0xF8259D8404B06630ULL, 0x473BBB2F928E1638ULL, 0x5E2D68014EFE870DULL, 0xD91AE8E2415D194EULL, 
            0x1FD16D3D87C72AC7ULL, 0x7331690E49EFA26BULL, 0x72B34479946D3586ULL, 0xDB2619175652BA8CULL, 
            0x64F01890ED64D7BEULL, 0x66D5C64DCA7F88E6ULL, 0x15F3BD4389350AC8ULL, 0x56838E3CEE412900ULL, 
            0xB0833539E9F14E71ULL, 0x47A19F0AD57DCF9CULL, 0x9E4DD7447404816AULL, 0x766387D2B2C677C4ULL, 
            0x2525A55B4BCA8EB5ULL, 0xCB35907FA3F714FAULL, 0x0E277E801C46D5CBULL, 0xD41325323315F350ULL, 
            0x7262D22AB9A6C470ULL, 0x4A82C45916308623ULL, 0xAD243FEB00B1A115ULL, 0x5D387D9823B9752DULL, 
            0xDC63E8561F2AB313ULL, 0x9531252EFC3CB6ECULL, 0x73E288537C5B52D0ULL, 0x7D8A6B716EC9A780ULL, 
            0xE14AD29ADF22660DULL, 0x029C31644A8E1434ULL, 0xDDC3580FCD4DA785ULL, 0x26EF2DF80A7A00BAULL
        },
        {
            0x18867B3C90774AAEULL, 0x5E80F83C72918C36ULL, 0xC5EA1D2DF1BE971EULL, 0x52053DB111023256ULL, 
            0x82BDA6C4080D61C5ULL, 0x6F7C860014382270ULL, 0x73CD4B7FF1FE8FDDULL, 0xC961A94B09FA5828ULL, 
            0x1361E81F2A1294F2ULL, 0x90E06075FC1F49ECULL, 0x7B21EF26708A8BA2ULL, 0x1BFB66BE3157EAF3ULL, 
            0xA021C35B9F477DB5ULL, 0x5A4BF65855FF6B63ULL, 0xF4CF27A7F4FBE859ULL, 0x1337CC4DBCDFB4E5ULL, 
            0x0FAE183C6F34201BULL, 0x7B020AD33A6801C2ULL, 0x00480684E5D4E663ULL, 0xB44C57532FDFB3E8ULL, 
            0xA356FA19D80B71CEULL, 0x11E47ABE7AAC2905ULL, 0x4A24874F0E549E4AULL, 0x97674E10380BB0BEULL, 
            0xEEDF3D320B46F5ECULL, 0x921CCFA13B6C6B28ULL, 0x38503369E0053065ULL, 0x0D7848BEDDBA8235ULL, 
            0x210B1CAE222E0A4EULL, 0xCDB6967448451B77ULL, 0x0585B51106B78C87ULL, 0xF3A41F7DCE460B2EULL
        }
    },
    {
        {
            0x1E36B8E90FCBEBE9ULL, 0x3CE866412937C29DULL, 0xCA7B70575D30E3E7ULL, 0x878CC97887597FF5ULL, 
            0xEE9B25D08838042FULL, 0x3AA303134503C181ULL, 0x5DEB032ED56732F2ULL, 0xB1604E6557B3A65BULL, 
            0xDC6968EA68D32F1FULL, 0x4EF1E1BB4BF28824ULL, 0xFA706374E81CECDCULL, 0x17BF22F34B1932E4ULL, 
            0xDCEF908BBBC3D5E6ULL, 0x361D9355081D782EULL, 0xB4E2A4A8287221F1ULL, 0xECCD2038DF426B2BULL, 
            0xBE761D4B1D6EAA5FULL, 0x7D99D1EB9331C9B8ULL, 0xE6FEDBC09E32C629ULL, 0x3C6AE74F4E87CD5CULL, 
            0x05D11DF7B957DA24ULL, 0x775F64C2A5FA1B37ULL, 0xE3BF59B746DAE935ULL, 0xAEECBB187C7621DEULL, 
            0x678EF05ADF5A1FEBULL, 0x2CB2BB3B6AF7A9C9ULL, 0x7645F729DCBC6E05ULL, 0x2C4F78B575088E32ULL, 
            0x3476F5AC89B1E300ULL, 0xF3A6F767A76599B0ULL, 0x3F64E124C1433C1BULL, 0x4123E752044D6C5EULL
        },
        {
            0xC5FE2D4A0FF121EEULL, 0x2E0E761E98C7334DULL, 0x3A3CE65759B25383ULL, 0xD82150D233F9EE86ULL, 
            0x2E68EE376690FA78ULL, 0xCDA0EE501E6A8C1EULL, 0xEAC7F8A999575483ULL, 0x43D05697FD87A1D4ULL, 
            0x367417A3CBE563BEULL, 0xBFA0B3C2C531AB95ULL, 0xD8540231F919B1F3ULL, 0xFBB335BE81E788EDULL, 
            0x84C200E61E48CBCBULL, 0xAAF4BF808879BB65ULL, 0x2B756A0E1E747E5AULL, 0x6680C7D1FD045BDAULL, 
            0x26CB1D22E68E2801ULL, 0xAD126F1B95157699ULL, 0xA5C53298F7A37D21ULL, 0x6E5BAD3131230796ULL, 
            0x5F633656764CBBE8ULL, 0xF85923B31C4DACB8ULL, 0x47F8882EF082DB0FULL, 0x8F66240515AEF30EULL, 
            0x72762D489D7ADD2FULL, 0x9DF0C1792990D689ULL, 0x91793E0A4E6BD405ULL, 0xF612A2AF8AB6B503ULL, 
            0x207CD39932074267ULL, 0x4DE1F5FF6A5B4429ULL, 0x6278BDE2DC1EA1D7ULL, 0x655E57859E984D13ULL
        },
        {
            0x105B355713501F62ULL, 0x42D1AE78041C851AULL, 0x8EEB6B774377F696ULL, 0x963007F6D27497E2ULL, 
            0xFAF1077E0C632EDCULL, 0xDDD49DF8D728F9F7ULL, 0x95DFB0EB8DA3CBDDULL, 0x9E3BD1CE8C20287FULL, 
            0x333F61C9B40076C1ULL, 0x4C15F840B6BE7281ULL, 0xE7731B3D1144C57BULL, 0x235DB45988C260E2ULL, 
            0xF014AB32FD43A9CAULL, 0x3510AACF4A739D9DULL, 0x8556261AE99ABB21ULL, 0x06A7E12C318DA112ULL, 
            0x1BB91DBCCA1981D0ULL, 0xC3BD210F5AC350A7ULL, 0xD5FB7E6B0B77BE3EULL, 0x1C10896B8B25B886ULL, 
            0x20824C7B26C75418ULL, 0x1723241128035F10ULL, 0x0F4BD41EE1CCDFB9ULL, 0x7403C8405869B067ULL, 
            0x95E8C6181D652176ULL, 0x0DD8A963CC0B2394ULL, 0x7B948712E9B0A04CULL, 0x7086999F49E44F40ULL, 
            0x1D4BD17C1B214AE6ULL, 0x05135700ED3783B3ULL, 0x70063CAB60574363ULL, 0x5F3DAA33B7C60B8BULL
        },
        {
            0xD46666A945E1ACECULL, 0x7229F2CADC848843ULL, 0x5B908A471FC320D8ULL, 0x2365045799E3BD7EULL, 
            0x37566DD87785D14DULL, 0xFC468CB88B7E626EULL, 0xA8741F7F0E579CD7ULL, 0x9674348D54F56D53ULL, 
            0x594B18992521690EULL, 0x2CEA1E4DCE187606ULL, 0xAF1B4C36FEA00FEAULL, 0x8798DE39DBBB9B47ULL, 
            0xCDE80DA9EE699444ULL, 0x74A10A1E1F874546ULL, 0xD8FB45279654033AULL, 0x8FAD52092C656B66ULL, 
            0x4E2B50021DF41C5EULL, 0x16683EBADD275521ULL, 0xBD113E51D8296A52ULL, 0x563FFCF48675DC70ULL, 
            0x93B22C6607B171B2ULL, 0x8CACA8E57E4415E1ULL, 0xFF01E1B9791831F3ULL, 0x8641AE7D0ADFBDAAULL, 
            0x4AB8104B3255C0C9ULL, 0xD9316994179AEC39ULL, 0x4E1EA277BE3BAF58ULL, 0x9A0634FEE5983DF2ULL, 
            0xEB86E5C278BFBA2BULL, 0x390212422DBBA8D9ULL, 0xEB677BF643A90D1CULL, 0x7F342B30692E328DULL
        },
        {
            0x4CBDFA4FC1A6E86FULL, 0x6AECA5C8FD28B0E7ULL, 0x35E2AC2D8B4A1A39ULL, 0x5A8557F757C5919EULL, 
            0x91A39F734F98CD07ULL, 0x784DD47D147A29FEULL, 0x98955F30A90A1BEEULL, 0x3C00B3394499D3EBULL, 
            0xB95E3B963562E212ULL, 0xDBA777D2F774C627ULL, 0x367128071664D3B5ULL, 0x2C02B31B7CFD1C5EULL, 
            0x8154F02056B388FCULL, 0xC87C66CAE6B1787DULL, 0x08F643C6516C017CULL, 0x7183D4C1DF53D6AEULL, 
            0xACCDCD1B867F63D8ULL, 0x2FB92E6A0B343EBFULL, 0x14C29242E51BC6DEULL, 0xC957BB2FA3D2FFEAULL, 
            0x56D10547D103ED95ULL, 0x1302A5C6B0495972ULL, 0x81BCCF4B89AF6600ULL, 0x31CB13C6C7C11C11ULL, 
            0xA1337ED428A40687ULL, 0x8964D05740DA378FULL, 0x02727707C8B6413DULL, 0x270379C7F6C08137ULL, 
            0x4A5502EB78AD17C3ULL, 0xD7CC5EB5BD7167C2ULL, 0xF56D7119276B932BULL, 0x1A8733FA33FCB339ULL
        },
        {
            0x01566EB3CB50B32AULL, 0xB00DAFC910529EF4ULL, 0x5AB7D05663E62FF5ULL, 0xE6EEA892A2281569ULL, 
            0x9452C13F5681E7FFULL, 0xE5FBE80371C8BFF0ULL, 0x1970304F22247AADULL, 0x99877332F928CD9EULL, 
            0x831F6856EB8F6E35ULL, 0x70E214B3F68E48CCULL, 0x0E15C1F1467AF266ULL, 0xAB021DAC8DF35371ULL, 
            0x9941DABF994E9C87ULL, 0xA95D274BBAC6EACCULL, 0x778EA22ED68783C9ULL, 0x2FD71410E9AB6288ULL, 
            0x59972378F5D8E316ULL, 0x3E4BC97513888348ULL, 0xE9FA53F3F3CDC8A8ULL, 0x6ABCCBCF012C3535ULL, 
            0xF3FE5419A9539C24ULL, 0xB2EEF5B77FEDEC40ULL, 0xDCF95D7B639BC7C5ULL, 0xB4936D5F3CE39142ULL, 
            0x69F43DAEDDCA7BC5ULL, 0xDE48442387B8D4F2ULL, 0x1912BAB59DCBD71DULL, 0xB322E15EFED951A9ULL, 
            0xB656C55DC8E25E2DULL, 0x76CABCDB069C4A2AULL, 0x0E5AAF2627ED5CE1ULL, 0xF82B215BE300D7BBULL
        }
    },
    {
        {
            0x28477EDF54A5FE33ULL, 0x437F0D0887C4F21CULL, 0x93CAFBEB246E5270ULL, 0x8FD357D7F45A2E9FULL, 
            0x197D8DC28221BC21ULL, 0xF1DFE23083847E12ULL, 0x832A7FAF658C08F6ULL, 0xBC00234404D5D4FBULL, 
            0x809ABCC02B8E065FULL, 0x02DFDD0256F6828FULL, 0x7749CCE10CC9CA8EULL, 0x3C7E0517F02F94E1ULL, 
            0x0A79F9A330F571ABULL, 0xBDD036255A17D352ULL, 0x6E8472024F0312CAULL, 0xF78A450DCFBDFE46ULL, 
            0xD3FDF3B6AB086CD4ULL, 0x7E5BD6670FC1F75DULL, 0xFD2DD742004D8BCCULL, 0x31F0E0E9E3E82D48ULL, 
            0xEC8ADDD20A7BCB2AULL, 0x5E75E8DD725DC4EDULL, 0x4D8C023AD08FB07EULL, 0x918030477D226970ULL, 
            0xD9A61CB42EF571FBULL, 0x8053C7DEEF4CC877ULL, 0x709C07401CED4278ULL, 0xBF6880E51EBC8DF3ULL, 
            0x4969B5230981CD9FULL, 0xB99A006CFE7B6262ULL, 0xCB0758F29C03855BULL, 0xA372D0AF74C091A5ULL
        },
        {
            0x7FA98D74A62AE1ACULL, 0x9C1628A93E4A8478ULL, 0x8E33DA0BADD019B8ULL, 0xFDC478A1821FBDF5ULL, 
            0xA2D1BB06C75CBF80ULL, 0x656BFAE10522E5BFULL, 0x9F61E4D2C31DE2DAULL, 0x59091F2AEFBD2A24ULL, 
            0x49DEDC63ADD40BB2ULL, 0x5F50F7ED81EEA66FULL, 0xF591DD0A5BECBC15ULL, 0x5D61DE6D33E5F363ULL, 
            0x681A6C141183A711ULL, 0x288899D028CC8C15ULL, 0x269BAE65E2555281ULL, 0xF24F489BE64546D2ULL, 
            0x6F6CDCF6CFCE08FFULL, 0xBBDD65583ADC6214ULL, 0xB53BDB3B06A6DFB4ULL, 0xDD8E5B01B90F0E6DULL, 
            0x303A6DDD8C28C7D6ULL, 0x44AC70AF10204905ULL, 0x41165EA8CE24B08FULL, 0x5F10D96B8D0B94A2ULL, 
            0xC30BC09B800BC697ULL, 0x0679D4FCD9D3ADB2ULL, 0x4F7AD3FB7B4EADFCULL, 0xF2D113CFE2138292ULL, 
            0x5145EA48E5242DF6ULL, 0xD4DF75EF1C685870ULL, 0xF5EC107E26F15CB1ULL, 0xD34253DD7A640085ULL
        },
        {
            0x1C983889066F7423ULL, 0x652E0C1DA1080C66ULL, 0xC1D7F0E22E4252EAULL, 0xF18802F1777A6311ULL, 
            0x83C7C4FF083C5492ULL, 0x289315BB714C44F1ULL, 0xDBE803F947792DF4ULL, 0xCBB04E7F00F22558ULL, 
            0x81EC836C4D857B1EULL, 0xE3FFCB33D4555ECAULL, 0xA668FC32F9F0D335ULL, 0x777821708B3F252CULL, 
            0x8F542105F8F64B0CULL, 0x282BEABAB1090676ULL, 0x3B3D9D8DF293DEF2ULL, 0x4B864EAFA21CCA81ULL, 
            0x2722B7200121FBB9ULL, 0x62DB11EDBFF44338ULL, 0x4CADF92BEE0712C8ULL, 0xF36670D8131019C8ULL, 
            0x47D47E16CFEC58D0ULL, 0x48DABCFF813E66DAULL, 0xBF061B385E296A27ULL, 0x206354BFAAF254FCULL, 
            0x7F03A9BC33BE3587ULL, 0x0698972D72CE17FEULL, 0xD7DE768C437DD1ABULL, 0xBDC1462BB4752670ULL, 
            0x63EB32069EA818BEULL, 0xCDBD74AECA512227ULL, 0x8CF8CB43CB70E528ULL, 0xD970260599F5459AULL
        },
        {
            0x5CE40AD19DF24BF9ULL, 0x637FB6A14D4908AFULL, 0xB736520A56DA6768ULL, 0x311BB67A65A8EFA3ULL, 
            0x73A4185A75A5FFBDULL, 0x59542626B67F9544ULL, 0xA0220C6B0C5AE54EULL, 0x82D1A2B95F87A536ULL, 
            0xA69D2A64F9E0D936ULL, 0x4CA4FB636C25F5D6ULL, 0xE1D5395D7A4DB5C5ULL, 0x91E9956D7B531FA7ULL, 
            0xEB4423E724DCBC29ULL, 0x3C093F01D565F6CFULL, 0xBDE6CAB62A34713DULL, 0x7ADEE1E6AFC1ABCCULL, 
            0x5DE820DCED8C7BE0ULL, 0xD584F64EC4EFD1F8ULL, 0x3E407A68F1F6A79AULL, 0xA878496D2B52C023ULL, 
            0x3D24330CB654BCFEULL, 0x2369FADEA5AAFA6AULL, 0xDCC1CDAD26B711BAULL, 0xFE5FA62D64E04268ULL, 
            0x227D290CF77335A2ULL, 0x0AAD15D0FCD9E7F6ULL, 0x87BB8996015DF832ULL, 0xFD8CB2F9717F93D5ULL, 
            0xFAA16F89FB6B6D1EULL, 0xCB50255758228B8FULL, 0xCC17A4026ED96FD0ULL, 0x06CB0781C278E0CDULL
        },
        {
            0xE52A11805D3FA5F3ULL, 0xF1047B654AA342C1ULL, 0xB46D94530042A45DULL, 0x9FAD7F24D4E2900EULL, 
            0xAEBC4390F8C6A4EFULL, 0xD8007586F43638CAULL, 0xA91556C89D17431BULL, 0xDD6862B5C0B75986ULL, 
            0x4CE34F71982EAD73ULL, 0xED0F80D4A3AC5A74ULL, 0xA0C501CFE305F3B9ULL, 0xB34A05535C995426ULL, 
            0xF39D03E0AD9256BFULL, 0xCFAF160A7A582EB7ULL, 0x71F1A931B108AA6BULL, 0x85532E7D41609593ULL, 
            0x47397462227BF7C5ULL, 0x2020E95397BA478BULL, 0x0258684FADFEF109ULL, 0xA43C808262FB50F0ULL, 
            0x281599573930B393ULL, 0x15003AAFECC230EFULL, 0xE3874AE0D56F5A24ULL, 0xC762ED3336BA2D0BULL, 
            0x4AB489F1C4AA7FB6ULL, 0x6EC54E8CC27185B7ULL, 0x401BE29887ADF8C0ULL, 0x53902BF8870FCA11ULL, 
            0xF7697B60B6F9B2D2ULL, 0xF5B790B62FC73529ULL, 0xF816C0B5EC29FA7BULL, 0xA938640A18ECA160ULL
        },
        {
            0x0A74F5AF800437DAULL, 0x71873CAFC0013547ULL, 0x8C1F9D9CF6157ADDULL, 0x8E25BE10A6843D05ULL, 
            0xC1824494156D2DC1ULL, 0x9194A284519650ADULL, 0x46861FD257A67D5AULL, 0x044C0CD8ABE4C1F8ULL, 
            0x17F82CA7C24E18BCULL, 0x67F5103CA1ED9E67ULL, 0xC2E64537958EDA4EULL, 0x7EAD57027F4AF628ULL, 
            0x1E6FE52D814620DEULL, 0xE8BF60B1E8B9B064ULL, 0x2A47C5719063DF12ULL, 0x6ACAD06CCDC0384DULL, 
            0x783A373EDCD90C3AULL, 0x55792D2472E73127ULL, 0xDD826F5EAC053A5EULL, 0xDAC202E3A3CFA38DULL, 
            0xEAE2FF3BA8D8914EULL, 0x8396FF5A35AE78A7ULL, 0x15BA3C38018DDFF3ULL, 0x4896B0E46812A41CULL, 
            0x9B4AC007481A5A54ULL, 0x2FE3A55AF67CB6BDULL, 0xDD8290BE3B95893AULL, 0x58879BFDC5380692ULL, 
            0x7739AB3572F2D6FAULL, 0x608AABA2021F1960ULL, 0xBE3A398B13F97815ULL, 0x76E7E31D2D40CF9BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseGConstants = {
    0x5869C405DA4A1C72ULL,
    0x1A33DE5CB14F8386ULL,
    0xE09F529C6A91763BULL,
    0x5869C405DA4A1C72ULL,
    0x1A33DE5CB14F8386ULL,
    0xE09F529C6A91763BULL,
    0xCB3470623BAC60BAULL,
    0x1E4EEAA151CAFD55ULL,
    0x55,
    0x2C,
    0xF4,
    0x78,
    0x59,
    0xF0,
    0x55,
    0xF9
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseHSalts = {
    {
        {
            0x2271D963AE7B8B5BULL, 0x5B052444F35D0F39ULL, 0xE1945F8D4FC0DB5BULL, 0x47934E95342014E2ULL, 
            0x07DD986ADF0C4B68ULL, 0xACB278B7762D7744ULL, 0x7F41F00A9D95C808ULL, 0x960FD9B2D2C75E17ULL, 
            0x869429B4889D52ECULL, 0x0E261966BECF2D60ULL, 0x4411CEB00FD6F99EULL, 0xC7354E62180057AFULL, 
            0x5ECC19BA40AD1D3AULL, 0x3CBE36C7F59E8D3BULL, 0x20C30A47EF0F61F6ULL, 0x45FDCE29F44F59FFULL, 
            0xAF4E731FD5955291ULL, 0x4338F70C49D6289CULL, 0x6BBFD264F4899147ULL, 0x2E85B662ECA39FF7ULL, 
            0x596D6867BD8355CAULL, 0xDA0A7AA833CC4FCDULL, 0xF7B81CC1B054EFE2ULL, 0x0135FA55A7A29FBEULL, 
            0x04BD5FF8CF574D0FULL, 0x33A6981CE0490D1BULL, 0xDC5B916196B59D10ULL, 0x3AB36EB890179F93ULL, 
            0x1EBC55E6F7CBA8B1ULL, 0x981015D827983BDCULL, 0x8EC72097408EA00EULL, 0xEB45EA3E3D38E27CULL
        },
        {
            0x337A5352E3835F52ULL, 0xD4E315C6FE58BBADULL, 0x221020AB1B884F79ULL, 0xAD98EF815FE91798ULL, 
            0x1DB1F1272AFBABAAULL, 0x5951F534512173C2ULL, 0x7E6C3F14303E36F6ULL, 0xA5DABFAC8BA68E69ULL, 
            0xD2CB8FEB7358A8B6ULL, 0xCADFF22AE9AC5F94ULL, 0x64D21D2258DAA957ULL, 0xEDBAF27D0FD2C214ULL, 
            0x77C5C59E635A8D5EULL, 0xD3133AFD401AE678ULL, 0xAB0EB9577A28B16CULL, 0xB5D5C5C75EBA2A4BULL, 
            0x27B2D644E00B0957ULL, 0x0F8E3973DA096B6FULL, 0x4A0983285DD8EA9BULL, 0xE7BC5A6F25668ECEULL, 
            0x3DCE31142D601C13ULL, 0x83D4A6D874F75FBBULL, 0x21B857802AA4D9A1ULL, 0x9DCABE14F1DCD4C5ULL, 
            0xCE94722E3220345AULL, 0xCE4D1B2EDBAE1912ULL, 0x5A96D3C17AA16E7EULL, 0x93DF32C7E27899ADULL, 
            0xAA88CF63B96AC7F0ULL, 0xB7BF6EF42BF2D97AULL, 0x610763D2E31E102BULL, 0x9C5ACD740654CCF9ULL
        },
        {
            0xA575E8A0737324F9ULL, 0x271FA376AD9B1E9DULL, 0xFB57F4EACA6D535AULL, 0x8A29F034807ED5FAULL, 
            0x99A2289244DC056FULL, 0x566AA5316DEA5C14ULL, 0x3F9A14245CF6C9FFULL, 0x59DA796974E3A681ULL, 
            0xFBF9BDAF31DB69EDULL, 0xCC4F3EACA4DFE67FULL, 0x71E018276C6871A0ULL, 0x26264C6C9C575532ULL, 
            0x09A8F83524148DD1ULL, 0x61F0832252B0A63DULL, 0x715AA54A83685EDCULL, 0x5698D63E1CE41255ULL, 
            0x2194C2BD6048AAC9ULL, 0x0B5E4FB07A683F51ULL, 0x24B2BB178C8AA78CULL, 0xAD931FB7E82A2410ULL, 
            0x5522D6A2BD67CDB6ULL, 0x1A713E7777BD166BULL, 0x1D1F6018014AA66BULL, 0x8FFDFC7371374178ULL, 
            0x3472DDD76ED1E1ECULL, 0x54DD30BFA94B5E4FULL, 0xE4583818A0983842ULL, 0x67C1324487E66DA3ULL, 
            0x4C8A7650CCCE8F7EULL, 0x3A4E2301D683E3A3ULL, 0x69621C6013D8DF87ULL, 0x9B0425F056E2CEF4ULL
        },
        {
            0x9B1A27B8C222DEA9ULL, 0x07C8F7C4344F849EULL, 0x0D0A0571D2F31B96ULL, 0x7508FA95C3CBEDBFULL, 
            0x5421447AA3E75D9EULL, 0x438F8F9E5E3A894DULL, 0x5966449687379289ULL, 0xA4345B197020538BULL, 
            0x41EBFA0BD3A0F9BCULL, 0x7E1FF896E2CC576CULL, 0x1BB8DAFE51D71EE6ULL, 0x1B1D2E54D275CE34ULL, 
            0x3F696EEC9C6E897EULL, 0x5D531D13C8563604ULL, 0x02B95FDAC558E465ULL, 0x542272CF50F99C12ULL, 
            0x3D792748DEBB525AULL, 0x8E1C46CDE61CB006ULL, 0x6AEDA389ED01238AULL, 0xE70F0CD00D7C5079ULL, 
            0x3BBC2DA93403B00EULL, 0xEE2C0EE220429F23ULL, 0xABC637FD6BB8FAA4ULL, 0x72D51BD4B68B3317ULL, 
            0x9C39A3E5C9352D78ULL, 0x69FE6D84DF10C5C3ULL, 0x53CCE6AB675DA61BULL, 0x957804FDD6324724ULL, 
            0x714709E3D3A49F16ULL, 0xE4EFD2002478A68FULL, 0xABDF2B6F9BC1EE6EULL, 0x557420FAF376EF31ULL
        },
        {
            0x10035FE586E10E96ULL, 0x97A19073FB6AA0BCULL, 0x8FB65D4609FFC512ULL, 0xA576A72BB9893F16ULL, 
            0x18A7C26899FE0C9AULL, 0x3C4E384A7B846FC3ULL, 0x9E70CBFDE1CB9018ULL, 0xB76B3C90A3094DC6ULL, 
            0x8971954F9AFE1128ULL, 0x75B9C71C628BA05EULL, 0xF61AEFBAE976DB64ULL, 0x76BB50FF6AB635E2ULL, 
            0x78C7AA5CA996FAD5ULL, 0x803281F087B964A1ULL, 0x2D2020B0C0B94A76ULL, 0xF3ABA22467D47B67ULL, 
            0xC270B151E50B82FCULL, 0xE067ED850D9A706AULL, 0xB77AD59DD73FF0E4ULL, 0x9CC015ADEF35403CULL, 
            0xDD41F4E8D55CF3FBULL, 0x071C39DAD769EEE3ULL, 0xE4895BE89D96D740ULL, 0x743B0E492F2277A6ULL, 
            0xEE657A00DBA2D46CULL, 0x414B626E20F4009BULL, 0x4AD69984BA299361ULL, 0x16F23F63F9D07B6DULL, 
            0x32B9FCBFC4D9FBFBULL, 0xB8A90DA824E62D7FULL, 0x94B5048459FD9438ULL, 0xCE69F8B218EF92EAULL
        },
        {
            0x6D29A6DB26F7016FULL, 0x4EEFD917972AC64EULL, 0x29B93286AB71E094ULL, 0x90959084204E0CEFULL, 
            0x5B5D72264A524934ULL, 0x9166D24BC04A542BULL, 0x059BF3EEB08201DFULL, 0x72783BF64B478854ULL, 
            0x6EC583D047FA72CBULL, 0xF6245F680E2974CAULL, 0xB59A058CC53297A3ULL, 0x7DD921D1FCED9D7DULL, 
            0x404E90A230E33B13ULL, 0xEE8B932AF217350FULL, 0x39B229F4563A4413ULL, 0x49F414818773BAB8ULL, 
            0x0336668A6B320685ULL, 0x887670F3C4830501ULL, 0x59A48EDD1350AFAFULL, 0xC236A34C02967D08ULL, 
            0x98BE35628875F067ULL, 0xE81CEC67A8657011ULL, 0x768E9DF6D25563DBULL, 0xDD1FA3BC194D42BBULL, 
            0x8A7FA9CC4728DB02ULL, 0xCA53D9A9FEB2D269ULL, 0x913355FD24A28276ULL, 0x69A748F4B6B2D6D4ULL, 
            0xCB141B6CF962ED60ULL, 0xB453F6420269B941ULL, 0xACD22F5CE9C907A3ULL, 0xE6933E26A0CDD041ULL
        }
    },
    {
        {
            0x618946FA6EB03524ULL, 0x7BB860BCD529978DULL, 0x82E92EB5ED2188BCULL, 0x16475B7F3DDE9CDDULL, 
            0xC01BA1304F907C5FULL, 0x5BE6ECC5C970EBC8ULL, 0x0F4BAB63D0908AEFULL, 0x20139DF40455C196ULL, 
            0x563BD11405D27B12ULL, 0xDB7E1665823EB0ECULL, 0xD6936B79173B41E9ULL, 0x2A412AEF3C919457ULL, 
            0xE9BAA86CED3CA4E7ULL, 0x7BE4BFF001CD5900ULL, 0x5F9F3B4E6A016B83ULL, 0x10EA133916356A90ULL, 
            0xC5FD6C2A564C609AULL, 0x3A59266224E9A3E6ULL, 0x04222E7A95F2571BULL, 0xF3F952786A2FE19AULL, 
            0x9E2E18300FDABA2FULL, 0x164B9F61F725D3AFULL, 0x8D0803DEF3C791F7ULL, 0x8D22062FC45D82ADULL, 
            0x6DBF97445C2B82B6ULL, 0x520C39D5C08B5D5EULL, 0x1F319731DECC20FAULL, 0x975CE39A161104B5ULL, 
            0xF44E3BAE4883D342ULL, 0x37B571CDC1F00DEDULL, 0x361D80EAE608DBAAULL, 0xA2EB60E215709F0EULL
        },
        {
            0x0B3EC75FCEE3069BULL, 0x2DA7DD8A82FF5989ULL, 0x12C9A5EE975FA8E9ULL, 0xBC94932FDA56D7FFULL, 
            0x951B8F7E615E2F2FULL, 0x0E92805A6D44FC4EULL, 0x0763AF7BE9A5CAE2ULL, 0xCC4A33573C586F62ULL, 
            0x9E09D94CB9BC6A8EULL, 0x2ABCD4072810AF13ULL, 0xC4EB785151C9E2F2ULL, 0xD9C0ECD5DC7CDDD6ULL, 
            0xE30C843E7782E40BULL, 0x1F8E8A606868DD39ULL, 0xA47F939C4E27A97CULL, 0xAA76ABA673113B8DULL, 
            0x1502D094C30E3184ULL, 0xE9DFB3EC63A3B246ULL, 0x82E406BA8EB88A0FULL, 0x34B81BB4C1CF6F4FULL, 
            0xC30B227DDD4103D5ULL, 0x3C7D36ED1898E00EULL, 0x25280C0C5D9510B0ULL, 0x78600273EC0CAB48ULL, 
            0x4BB41EB98D46665CULL, 0x64E116E89EBE0BA2ULL, 0x4FE17307E842273AULL, 0x829B786F7D38B792ULL, 
            0xCEF1C47A337A88E0ULL, 0x59EC3AE9AB64A53DULL, 0x0D1ED8F2A11D03B0ULL, 0x7255B6329D8ED6E0ULL
        },
        {
            0xE76CFDB7B7BCCF04ULL, 0xF40AAAEF9C1513D7ULL, 0x04B0FF0160ED7700ULL, 0xD883236ECB352D2DULL, 
            0xB043E54245601C17ULL, 0x00E775DBBB7719AAULL, 0xA57D20AFAA7EC186ULL, 0x61AD7FA25144F211ULL, 
            0x1E23D9FCCACCD68CULL, 0x68240FDB0DC48ADDULL, 0x4541817E743CE4B9ULL, 0xD6103EA888BCF1C6ULL, 
            0x45046692F64E3623ULL, 0x7B09446AB6288E10ULL, 0xB72853B192C905F3ULL, 0x95FF942726723D07ULL, 
            0xC0C364CE05198432ULL, 0x6BEEF5D2ACD15288ULL, 0xD76D54213DE98571ULL, 0xD75C8830548F1AECULL, 
            0xA3891FF75CE17949ULL, 0x9D6323426C2A9126ULL, 0x5E3D9497386C41BCULL, 0x8B73FB9ED90DEE9BULL, 
            0x21B6BD242CE9252CULL, 0xE9723597850E0A65ULL, 0xF5C3B09ADACCE54FULL, 0xAD48E17D027DAAF6ULL, 
            0x9664AA4A20D1A68CULL, 0x80FE539E4423D6AAULL, 0xD013BF8F581E0951ULL, 0x4B13DA72B43CDF34ULL
        },
        {
            0xCBFF6B891029565CULL, 0x2C6D22374184D4A0ULL, 0x3C85B6ED6AF4E7A8ULL, 0xD1E974F447AB1C2FULL, 
            0xD09673326C0D42DFULL, 0xD79055AB83EE26DBULL, 0x284A348AB7508A4CULL, 0x63E473CC0185E2C2ULL, 
            0x54547A933F786124ULL, 0x32CD9C8D37C3046BULL, 0x7F86FDC90C0770B9ULL, 0x5B4E2B3992521E7BULL, 
            0x26D2E24FD9B3774CULL, 0x16CC53B04D0E9F80ULL, 0x1D03D10A33DE53FCULL, 0xEB9568F93FBCB398ULL, 
            0xDB4ACB199E983753ULL, 0xAC5F613B68186DCFULL, 0xF80E8F7ECA4EF315ULL, 0xE4A237C47D869AECULL, 
            0x0BB729F28BA03408ULL, 0x455AAFFF83E29CFCULL, 0x5D1768502074FE9FULL, 0xC84A2A1FE27DBA63ULL, 
            0x6050E527CF6FC95AULL, 0xF1C579494C55B75CULL, 0xFD9CA9605C48F871ULL, 0xE260E0F5B54CD2AFULL, 
            0x28C265C9346D091CULL, 0x4C738D1C2C2E194BULL, 0x8504654EC69803E8ULL, 0xFD6BDDAC62342361ULL
        },
        {
            0x53F9D3F1D27CCB01ULL, 0x8F319150612101B1ULL, 0x33A3D3FB9679D14EULL, 0x703AAB0B909F73E5ULL, 
            0x6D0D5C3D09423E5DULL, 0xD20C35CD0EDFFB84ULL, 0xC01F5A08B998CD17ULL, 0x58729FDF302E8638ULL, 
            0x5EDFCAFB26463E96ULL, 0x786D4E21A74AA076ULL, 0x3064AEA4FC5F4768ULL, 0x1E9CC9F74C5834B8ULL, 
            0x86756F9B6C7DCEFCULL, 0xE6DE43945F99A3D6ULL, 0x76B569405EC7296AULL, 0xC1738B03C68445C6ULL, 
            0x56DD6929A9CD82D0ULL, 0xF5E49914901803E5ULL, 0xCC012E0BACA7CDD0ULL, 0x688A157CA7A5ACE3ULL, 
            0x40BF2C105DDF8E1FULL, 0x300A96F86C994799ULL, 0x97698CA5FF039293ULL, 0x827EF5057BC660B6ULL, 
            0xCBB78735F5850FB5ULL, 0xD1452AA6307C411FULL, 0xD3DD46600C846448ULL, 0x226014F193168FAAULL, 
            0x1BD8AB6CC5462A5BULL, 0xE08AC4D161222043ULL, 0xF11109E9F4DC56C6ULL, 0x72C2F20D9E84A494ULL
        },
        {
            0x54245FD790978454ULL, 0x55A46C641D86ECEEULL, 0x962D73D27DFBA026ULL, 0xD2F19EE11A55AF4DULL, 
            0x7AB3B215F6D89031ULL, 0x05C44E2BFAE79726ULL, 0xEF39FAA3F8E30B9FULL, 0x7DD714A6B4A772FEULL, 
            0x64120C9B92B83CF6ULL, 0x0D966089877E73EFULL, 0x6059E1DCDA7C9CA9ULL, 0x4F6A28A1EADF0E97ULL, 
            0xF7A766E7175E5C18ULL, 0xA9FDC0C42E4C8DE0ULL, 0x35C3B475DCA0D77BULL, 0x282AFDD16315AEB3ULL, 
            0xC7E97AD5F8859D78ULL, 0x2E9744DEB025DC37ULL, 0xE6949A1010EB5D8DULL, 0x633B4971AF2FE3D9ULL, 
            0x4161EEF8C2C34970ULL, 0xAF38441FBC5B2222ULL, 0xF08B7DED67811114ULL, 0xAC8E781BAEB91128ULL, 
            0x3E0011EE177E959AULL, 0xF521368880831B04ULL, 0x6AA06882D39F9E85ULL, 0xEF2AF1A7051936C7ULL, 
            0xF191B4C26F670856ULL, 0xDE9138617E79D8ACULL, 0x0166999E3FAE1307ULL, 0x6A813BF494AC5F74ULL
        }
    },
    {
        {
            0xF0B792140815CDE1ULL, 0xDA9769836971C57DULL, 0x79D98AFC9928F0E7ULL, 0x30F9CBFC10177D5DULL, 
            0x2D1BE03E7777FCD7ULL, 0x59BCB27179FBE3F0ULL, 0xEB3C29F659DFF3B3ULL, 0x4B63B8956917FF3DULL, 
            0x7FB9040A1D796DE2ULL, 0x8C385763F6B9303FULL, 0xDC045A0EB5A316FCULL, 0xE8834B35A09C0578ULL, 
            0x4392C7D635ECA39FULL, 0xFC4EB7B7644CE22CULL, 0xD5BDF6D901839B79ULL, 0xE6E9165158C1FACBULL, 
            0x7D2C4F7812D3A361ULL, 0xB7ADFAE8C3F1AFEAULL, 0x5A53D6763A73BF12ULL, 0xF55B176A005E100CULL, 
            0x135F048D694111A1ULL, 0x8C1808EADA1EC560ULL, 0x93F9456BF0347979ULL, 0x8C9F1BC8D44C2DECULL, 
            0x00EEABC61A516445ULL, 0x056BD6A64C9EAC9EULL, 0x3B4D948153BFBF3CULL, 0x7D60F783FB8E7FB6ULL, 
            0xD6C3B52C5E41FFEBULL, 0x8B53AAAA8414631AULL, 0x3F23C6579BB15BA2ULL, 0x60C85636759EA5F5ULL
        },
        {
            0xB8764A5F5E0D3758ULL, 0xFBF2C17BF96FBA83ULL, 0x4F6CD70EF783F8F3ULL, 0x55DA6A394E21AE50ULL, 
            0x8533A10948A726B0ULL, 0x80C782004D84700AULL, 0x23DCF39BB4210B76ULL, 0x8171EBB203786A38ULL, 
            0xEFA33CB625C0A7B3ULL, 0x9049BF1A4D5938C3ULL, 0xB7741E1C5B67EE86ULL, 0xFFD575D099DB22FEULL, 
            0x1647389EB2FB33E5ULL, 0x7B7ED34C29FB89A1ULL, 0xBBE70CB5C382F0CDULL, 0x3DF45AF4BC86F910ULL, 
            0x8D74924134538155ULL, 0xC70A8AF43380F923ULL, 0xADDF8F4D7EADC762ULL, 0x0656D229146EFDD0ULL, 
            0x5A6DD78D73B50E91ULL, 0x8B7F3AFE443CAF6AULL, 0x7C4F26BB34B9FD34ULL, 0x59D12ADBB436BFF5ULL, 
            0x97D230A4183DC72EULL, 0xAD2CBB06BE695A8CULL, 0x17E3218378AF2D46ULL, 0xBCF7C394194160F9ULL, 
            0x871352640AE360D3ULL, 0x4AE4E3E64F5826CBULL, 0x820459DFEB1CADAEULL, 0x165EC79510CEAB08ULL
        },
        {
            0x90706DF736963FB0ULL, 0xB798D6B910E6C754ULL, 0xF249B0EFB0CA02B4ULL, 0xC2EAEC68B992CF31ULL, 
            0x6B54C59AF427F9C3ULL, 0x228157B729211740ULL, 0x92767389958E31B5ULL, 0x5C660D320299AD8DULL, 
            0x96A7A1F338A4B409ULL, 0xFC7EA074DEDDABF3ULL, 0xB2D56B1472FEF7BDULL, 0x783C6AAF3EE58BCEULL, 
            0x71E3D093A3FC36A2ULL, 0xF5061211BF66ED9AULL, 0x123C33EA3EA85429ULL, 0xEB49BBAC3BACD904ULL, 
            0x540EA52F4441726DULL, 0xFBA680508A5A7441ULL, 0x8C569449E0CF4240ULL, 0x9BBE9D6BB730BA39ULL, 
            0x31AF37FE2CEACA67ULL, 0x0C4AB22D7320C5FAULL, 0xA1C1CC1BE72053CFULL, 0xD17E21F8687AF7FAULL, 
            0xE3F149EC708DB6A6ULL, 0xC84B62BD657DF35AULL, 0xF76F2D2BEC7F43C3ULL, 0x4C68F7EA43F35283ULL, 
            0xECF9E6DED890C208ULL, 0xD73352CE6E688408ULL, 0xE566883126BD0220ULL, 0x5806FC5725FAA2EEULL
        },
        {
            0xEF4EB91432147878ULL, 0x218BD6F9C05E8A9CULL, 0xA98EE9C2ECB91962ULL, 0x7831A77A128DADFFULL, 
            0xBD8F1D320C83C047ULL, 0x3E5B1EE45019420EULL, 0x8B2DA5F5D9FA8AF6ULL, 0x0FE1672E22D4176CULL, 
            0x852BC278F60E22FDULL, 0xC0AA20DCC8390C91ULL, 0x7900E3250F7EE2F5ULL, 0x4338E04015DDABA7ULL, 
            0x908BE92FC545A069ULL, 0x5FBC076C46922C33ULL, 0x150B72CF62F6D26AULL, 0xABE4DEBB7910F969ULL, 
            0x7A81F7867125EF62ULL, 0x13DA7E5E987B2DDCULL, 0x61EE82AEA7E848E6ULL, 0xF22E2BBE0E74946FULL, 
            0xCEA0CE020AD46ECFULL, 0xB70BFF703EC8DFB5ULL, 0xC9EC4E579A93C0F7ULL, 0x163211A68645AF23ULL, 
            0x34A0C29D55FB6526ULL, 0xA59C3F6A5D0817CDULL, 0xCA1B0F33A364E7A2ULL, 0xAA68F363F861AA36ULL, 
            0x9B39D400AB85A1B8ULL, 0xD50E0AEC3BA14AA4ULL, 0xF72DC58936ACAFADULL, 0x16204EF4448C9A8DULL
        },
        {
            0xC8D02E77594A3E43ULL, 0xBF7A60A437A00BADULL, 0xD397F4B39D29A983ULL, 0xCDE8400510527BBEULL, 
            0x505346C40C652A12ULL, 0x7BE1EE6C4290C23EULL, 0x47E8E7D7C65D415FULL, 0x542FC500CCC9877EULL, 
            0x78685A34E9CB9885ULL, 0x62101E579E7A2CFCULL, 0xB95C29443307B88AULL, 0x58223B7F7F14018DULL, 
            0x6A6C350CAE7EE74BULL, 0xA86443AA39EA19CBULL, 0xB8D4F61094FFDF8AULL, 0x6A6911390F00A76AULL, 
            0x99265ECF005260C0ULL, 0x2EE9320F50916B2DULL, 0x302ED78A591F7452ULL, 0x8D9547D7A85D7995ULL, 
            0x1585626A04546CC6ULL, 0x627D7A2950CB29F6ULL, 0x29A959D84D21949DULL, 0x847F27796AE2E271ULL, 
            0xE48315D2ACA0B412ULL, 0xF9A79D98AA08B0E8ULL, 0x347BA9A0834F8280ULL, 0x5B5D456C9CFEEB33ULL, 
            0x3F91147420D296AAULL, 0x7B056F63B0F1D788ULL, 0x099763354DD09CE5ULL, 0xAC2DFE89FA8BE26CULL
        },
        {
            0x6A3AFCB1D8DE275DULL, 0xD03471416518DC22ULL, 0x4282CB73F7F38F6EULL, 0x67D984F137B23C6CULL, 
            0xB32F6E2BDE775A63ULL, 0x3B61ABFA7FBD0F77ULL, 0x529CCF68E0A6C62FULL, 0xE7C0924A523E2FAAULL, 
            0xD7161F9D8323ED37ULL, 0x46C085F8AEB9AF6BULL, 0x76E8112134FB1594ULL, 0x50FB7D1D044A361BULL, 
            0x8A18F39A4C41465EULL, 0x32DF80827D53613CULL, 0x5F5D5B3F845FCDB7ULL, 0x7FBF7530C5B46229ULL, 
            0x96EF124B9DB51E5BULL, 0xE01966A483ED8E4BULL, 0xB0B9E5B53A4A1BCDULL, 0x14E2FBDDF8278AF5ULL, 
            0x20DEAC23D1EAA988ULL, 0xD58D9AD1F25F766BULL, 0xCF362555E791B832ULL, 0xEBFBC0EA3598FC9DULL, 
            0x82F91D0F3CA79257ULL, 0x7EF35D5FDBD5CC80ULL, 0x17CF34B95D866528ULL, 0x91E8EDE9998C21D4ULL, 
            0xF7099E199D584136ULL, 0x7A6CC6509D3E4395ULL, 0xDA99224B632A7EB9ULL, 0xF990A386DF797201ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseHConstants = {
    0x64926827EDFBA681ULL,
    0x474FEEE78EC6A18AULL,
    0xC9D1CDD771BC541FULL,
    0x64926827EDFBA681ULL,
    0x474FEEE78EC6A18AULL,
    0xC9D1CDD771BC541FULL,
    0xA60F97CA984AA581ULL,
    0xC09DF065068D511AULL,
    0xD2,
    0x77,
    0xAC,
    0x2E,
    0x37,
    0x02,
    0x13,
    0x5D
};

