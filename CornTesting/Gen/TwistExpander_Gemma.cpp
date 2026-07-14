#include "TwistExpander_Gemma.hpp"
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

TwistExpander_Gemma::TwistExpander_Gemma()
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

void TwistExpander_Gemma::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9C3506FB1F4F12B1ULL; std::uint64_t aIngress = 0xD4222808476AA17BULL; std::uint64_t aCarry = 0xA0B920C3A54C1C7AULL;

    std::uint64_t aWandererA = 0x84A1B8405B4CA0A5ULL; std::uint64_t aWandererB = 0xD40D849CBC897F0EULL; std::uint64_t aWandererC = 0xA5B2AEC4FFBDCA94ULL; std::uint64_t aWandererD = 0xFAFBD6B8DA0E0581ULL;
    std::uint64_t aWandererE = 0x9A094C789CA5656FULL; std::uint64_t aWandererF = 0xC38174B88F7AE217ULL; std::uint64_t aWandererG = 0xD14BB03C5A815919ULL; std::uint64_t aWandererH = 0xAB455277AF281B55ULL;
    std::uint64_t aWandererI = 0x8CE42DDC9AC37800ULL; std::uint64_t aWandererJ = 0xF968ADA2D797E56AULL; std::uint64_t aWandererK = 0x920502F0BA402635ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16104842807614675184U;
        aCarry = 18391434719499534727U;
        aWandererA = 17377432271414842265U;
        aWandererB = 12024957003055658965U;
        aWandererC = 11891211165782321350U;
        aWandererD = 10697381842820974202U;
        aWandererE = 14349857358030717162U;
        aWandererF = 11000705473427746362U;
        aWandererG = 9331500044075578143U;
        aWandererH = 14414071231837361024U;
        aWandererI = 10686605528352684371U;
        aWandererJ = 9268564308938024660U;
        aWandererK = 14048704679097670267U;
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
    TwistExpander_Gemma_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Gemma::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xCD16B67789A91776ULL; std::uint64_t aIngress = 0xE988B421BD026576ULL; std::uint64_t aCarry = 0xBB8FC0147C55505AULL;

    std::uint64_t aWandererA = 0xFC7B9341C8B12FACULL; std::uint64_t aWandererB = 0x82A05385C8B4F486ULL; std::uint64_t aWandererC = 0x80864C13018079BAULL; std::uint64_t aWandererD = 0xB03054186AFA0C8AULL;
    std::uint64_t aWandererE = 0x979E6974EB68625AULL; std::uint64_t aWandererF = 0xA22CE402B62FBA75ULL; std::uint64_t aWandererG = 0xC71E864A01B7C93FULL; std::uint64_t aWandererH = 0xCC04D3B9CB6798D0ULL;
    std::uint64_t aWandererI = 0xCB3BC39A53E3034CULL; std::uint64_t aWandererJ = 0xFE0DE9DBA172C912ULL; std::uint64_t aWandererK = 0xA5782E8FD4F89CD8ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14750426199859590547U;
        aCarry = 14118455029027512685U;
        aWandererA = 17401210481387203962U;
        aWandererB = 12350358746516216131U;
        aWandererC = 12796464341844659406U;
        aWandererD = 14519533135463802881U;
        aWandererE = 10841999122602603851U;
        aWandererF = 15310483480070498486U;
        aWandererG = 13112978221256060788U;
        aWandererH = 12668311020159188204U;
        aWandererI = 13046599699653764286U;
        aWandererJ = 10683905287250467198U;
        aWandererK = 11010310638163565031U;
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
    TwistExpander_Gemma_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Gemma::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x8531DE4F8642AA0CULL;
    std::uint64_t aIngress = 0xB75EB4B58955E0F9ULL;
    std::uint64_t aCarry = 0xDDAB3ACABD232677ULL;

    std::uint64_t aWandererA = 0xC37A1A23CEA3999CULL;
    std::uint64_t aWandererB = 0xED2C5D536587FB97ULL;
    std::uint64_t aWandererC = 0xA1958E532A87D4A3ULL;
    std::uint64_t aWandererD = 0xDB3646FE576FE79DULL;
    std::uint64_t aWandererE = 0xBFA31BC7959B9FBBULL;
    std::uint64_t aWandererF = 0xEDCD4B521D88727AULL;
    std::uint64_t aWandererG = 0x95D3060951642EEDULL;
    std::uint64_t aWandererH = 0xFC6D14D387D77A16ULL;
    std::uint64_t aWandererI = 0xF4459D765DAD7EE0ULL;
    std::uint64_t aWandererJ = 0xB2E388297C80A262ULL;
    std::uint64_t aWandererK = 0xECDD35A1B676D2FEULL;

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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
    TwistExpander_Gemma_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Gemma_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Gemma_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 28 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1791 / 1984 (90.27%)
// Total distance from earlier candidates: 49088
void TwistExpander_Gemma::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 266U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1205U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1361U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1524U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 220U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 882U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1112U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 150U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 445U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 647U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 890U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1697U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 641U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1791U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 199U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1230U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1327U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1277U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1892U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 675U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 911U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1000U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1632U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 167U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 581U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1406U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 263U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1562U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1533U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 961U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1403U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 178U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 223U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1302U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1652U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1066U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 480U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1291U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2029U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 500U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 217U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 324U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 30U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1615U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 376U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 93U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 433U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 583U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 56U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1834U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 201U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 844U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 985U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2001U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1371U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1736U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1765U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 261U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1481U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 94U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 468U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1730U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1175U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 861U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1309U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1032U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 720U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1979U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1800U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 694U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1752U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 404U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1712U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1149U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 852U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1622U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 162U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1935U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 367U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 238U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 176U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 447U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1011U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 23U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1118U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1219U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 654U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1686U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 248U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1837U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1295U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1126U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1913U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1489U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 621U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 503U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1228U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 449U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1236U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 169U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1267U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1400U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 745U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1284U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1774U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 974U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2023U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 670U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 691U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1373U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 65U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2008U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 650U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 631U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1759U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 764U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 461U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 345U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 585U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 714U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 309U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1346U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 157U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1434U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1354U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2009U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 950U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 973U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Gemma::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x98574839DEFC77DEULL; std::uint64_t aIngress = 0xF0FB579F72DDBFDEULL; std::uint64_t aCarry = 0xA3323631B608D080ULL;

    std::uint64_t aWandererA = 0x99A744DB6642A2D7ULL; std::uint64_t aWandererB = 0xEF606D61C6169C7BULL; std::uint64_t aWandererC = 0xE5F5AF30646CE68CULL; std::uint64_t aWandererD = 0xF1709457F3AF6B4AULL;
    std::uint64_t aWandererE = 0xC0E55C6ED034E937ULL; std::uint64_t aWandererF = 0xB2FC59B4C0978E26ULL; std::uint64_t aWandererG = 0x84E5970EF41162A3ULL; std::uint64_t aWandererH = 0xB8D8B8FBA39A02D9ULL;
    std::uint64_t aWandererI = 0xDECBA4EDB4521CCDULL; std::uint64_t aWandererJ = 0xBA511143525B7F9BULL; std::uint64_t aWandererK = 0xDA3FFE05CA0C3643ULL;

    // [seed]
        aPrevious = 17484720645415632313U;
        aCarry = 13145676831629487506U;
        aWandererA = 17444845766646695763U;
        aWandererB = 9819733363271507339U;
        aWandererC = 13068018180531402040U;
        aWandererD = 9910614381243496177U;
        aWandererE = 13361458027358199060U;
        aWandererF = 12456051325214409894U;
        aWandererG = 10645562091234682906U;
        aWandererH = 9781568774964781497U;
        aWandererI = 18046243645827744099U;
        aWandererJ = 17163953216701466748U;
        aWandererK = 17360809313405151713U;
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
    TwistExpander_Gemma_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Gemma_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Gemma_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 28 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 14621; nearest pair: 476 / 674
void TwistExpander_Gemma::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7973U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2924U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1031U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4638U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 962U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 520U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 851U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 689U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5101U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1041U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 729U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4078U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4103U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 788U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 344U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8060U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 352U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1943U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 782U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 957U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 427U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 915U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1706U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 297U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 351U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1657U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1508U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1748U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 201U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 437U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 286U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1103U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 131U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1494U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 92U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 863U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 28 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 14620; nearest pair: 468 / 674
void TwistExpander_Gemma::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3911U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7349U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5784U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6131U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5550U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4001U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4143U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4471U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4017U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4553U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4279U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4244U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3122U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2765U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 710U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6109U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1267U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 43U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 548U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1818U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1143U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 666U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1890U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1124U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 63U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 373U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 732U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1029U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 779U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1275U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 607U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1869U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 250U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1210U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1997U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 891U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseASalts = {
    {
        {
            0xE863FC390A3428EFULL, 0x3CC103621FE470CBULL, 0xD9BA3B4E6C693F07ULL, 0xDFAEE50EB27F9011ULL, 
            0x69BCDEAE9A3CAEBCULL, 0x884B7344799C6A00ULL, 0x4D21B91932B2AA7EULL, 0xCC18486833EA7BDDULL, 
            0x5721719D9899F0A6ULL, 0x2B64855EF71A14D2ULL, 0x299F826CA54C1298ULL, 0xDE139C33F8EC5013ULL, 
            0x41C1C0214F6DFDDBULL, 0x08600A809F43874AULL, 0x64F037586E635842ULL, 0xD23E00B5CBC57576ULL, 
            0x48227F32B0DFC1A2ULL, 0xCFCBC5E04C96DB87ULL, 0x47A6A0CA2E14AC79ULL, 0xFCF45E21C7E282C5ULL, 
            0xAB06832CEF14EBBFULL, 0x01C7DF09DFDA597EULL, 0x70C89F09D0DD20DEULL, 0xE5D7AFBDB89A7F0DULL, 
            0x02C213B62B4A953DULL, 0xEA9E7DE6C0108600ULL, 0x6E98BC763399A36AULL, 0x8459F3A2C9FEC48BULL, 
            0x03993DA4F7D5B4BEULL, 0x4B9D15F174A30D7BULL, 0x7BCED7884579DD87ULL, 0x1C7BAE9850D0653FULL
        },
        {
            0x1172BF5D3C2A973DULL, 0x34008DB299272BC0ULL, 0xADD3ACEFAD0A9A90ULL, 0xD69B729D1463683DULL, 
            0xEB860E8CA9FC78AEULL, 0x214D201C58C7B823ULL, 0xD4362CDED09112D4ULL, 0xF52B2BF93DA32C52ULL, 
            0xA425967E828A7E8CULL, 0x2C04638FFA4A26F9ULL, 0x4838C17C887E92D7ULL, 0x0AE1150D56178F38ULL, 
            0xCE69977865EBDF1BULL, 0x65EA70D5AE35CBA4ULL, 0xC09F182DC0B228ACULL, 0x430A669BA79CC762ULL, 
            0x2D523703CDBDC8F1ULL, 0x7D97CCF85F6B703DULL, 0x3E16EA32DD0A46E4ULL, 0x8D44D690F84F97F8ULL, 
            0xA4979FC2C6E5128AULL, 0xBFA6E86AAAF2BD9FULL, 0xC69524ADF3B5FFBEULL, 0x29103699E765FBECULL, 
            0x3B3593836D176BA2ULL, 0xFE8548758A6F9061ULL, 0x71F0D429EF7F6673ULL, 0x82C934CC37BCC33CULL, 
            0xBFBAD556207DACB0ULL, 0x49016DF664BF6B3BULL, 0x2FC3068E0FE3C7A4ULL, 0xB92FC91A835DA05BULL
        },
        {
            0xAA0A539195F8B18FULL, 0x3224AAE0D5D88D57ULL, 0x74D58CE8A60549C5ULL, 0x24AA127499D087D9ULL, 
            0x7DDEBD47D4078233ULL, 0x7C9A3BABF3AF8008ULL, 0xDCF71B73B45FDB50ULL, 0x2686CAEBDE22DFD3ULL, 
            0x4EC72CDCCC7C312FULL, 0x154533C947CCDEC8ULL, 0xE72097B95749F2EAULL, 0x87C4A6D6790B9519ULL, 
            0x50E197AC2827ECD8ULL, 0xC4A4E2695A26DDE0ULL, 0x5A076A28EC95E465ULL, 0x18F381C9A1673E46ULL, 
            0x76717216AE5585E6ULL, 0xD2CD5FA296B0E955ULL, 0xC1B53605CC5D67F4ULL, 0x58AEAAB36812F9BAULL, 
            0x3748FAFFE0A5BC98ULL, 0xF47CFEC4DE7391AAULL, 0xA46051C4EE85BF73ULL, 0x7B13F97578953DCFULL, 
            0xC9A130169B0EBCF8ULL, 0x174AF47D69148688ULL, 0x00CAADDF31693D23ULL, 0x0B714D0BAB56A8E4ULL, 
            0xCF3816DB42676574ULL, 0x4AC03BD9E4F87021ULL, 0x949C900A155575F5ULL, 0x1930BA930913F4EEULL
        },
        {
            0x0EEF0B5C9CB67F6EULL, 0xED5D389B15525B90ULL, 0x7A075FD20B5B5BDEULL, 0xE1D426CFFDE6538FULL, 
            0x932EA897FA89106EULL, 0xF0E3042A7E7E5EF6ULL, 0x1046D6000A7F7FAAULL, 0xB3B5C35F4BD069E7ULL, 
            0x9DE403415E68AB6EULL, 0xE3D1E9518B6EA9E0ULL, 0x975190D7CDE41D78ULL, 0x88BDB777926B73D7ULL, 
            0x6D638BAC028FDE87ULL, 0x7F14BC591771CAF3ULL, 0x460974F679D25967ULL, 0xB948FD5DBDD310B6ULL, 
            0x9304A0879FDD25A0ULL, 0xF290810FF6418ABDULL, 0x61D2E707C765B3F2ULL, 0xA71F8BDA1E954DEDULL, 
            0x409741CBC507C880ULL, 0x9B4DC904988E1B30ULL, 0x3ADDBC206C4F8A35ULL, 0x8BB054E972D51969ULL, 
            0x2FD51EF2E7F279AFULL, 0x9B4370D0A82D499AULL, 0x6322B4E0A926EC5FULL, 0x4C726A90BBB55020ULL, 
            0x33C92DDC25CC9941ULL, 0xBE44D5A63F7C5925ULL, 0x2FC8AF7E6DA2D102ULL, 0xC65200475EDBA496ULL
        },
        {
            0x78D07165EBD0A0D9ULL, 0x7CE9FAF4643CF77DULL, 0xC2CF92D306A2995AULL, 0x45E610EE5E16CAF1ULL, 
            0x3EC245C015C11FC9ULL, 0x61515009532E92E5ULL, 0x1F2CD7573C34F610ULL, 0x7208E0C1DF3B121BULL, 
            0xC60FE09D6EBEE0F1ULL, 0x8435C959CD05763EULL, 0x6A63BD0E895CD5F4ULL, 0x929AB51A1A052AC4ULL, 
            0xE9C5CEA00081EA52ULL, 0xAC3BC39A5056984AULL, 0x016AC697969DB32BULL, 0x1D741C48F0532D6BULL, 
            0x04CB7DCC5721A41AULL, 0x8D1D242219D3DF47ULL, 0x4830C65C19B554D4ULL, 0x40332C18466B86DBULL, 
            0x9CCDBA320F896EFBULL, 0x3BAD7AFFC90DB15FULL, 0xE640D5CE9BEF47ABULL, 0x9BFA4D71194628FAULL, 
            0xC4613A351955A1EFULL, 0xDBCE872116467505ULL, 0xE0FF39F1EEC6D03DULL, 0x9A4D991CBDA5B4BBULL, 
            0x26EDE0B6E2936C19ULL, 0xAC8E2D3CA0BBE396ULL, 0x256B0600B0B62C5CULL, 0x2783346362A72ADDULL
        },
        {
            0xD0E95C5056D010A4ULL, 0x008905BD34814F36ULL, 0x66AB8225F698544EULL, 0xDE3147FEAA3EADF3ULL, 
            0xE2631AB6FB828C5CULL, 0x83B4853005587298ULL, 0x5F0FB1E6BA1B0BD6ULL, 0xE4CC8766D88D2A7DULL, 
            0xFC5F6B1B3FA5D6A7ULL, 0x335C79C35221B4FCULL, 0x72FD465ACBF3CB66ULL, 0x22A40FA50D5B40B8ULL, 
            0x4543B06AE95F1F0CULL, 0xCF4CAF175C8731E1ULL, 0x9A268FF059D373BFULL, 0x9BCD3A665ED42BF4ULL, 
            0x043483443849AA30ULL, 0x0386005E182C8C08ULL, 0xAB5ECF72F127FD8FULL, 0xB32ABC5396650112ULL, 
            0x9F991B4DFA062665ULL, 0x205C5AA1B96E48B2ULL, 0x614929EC63B5F03FULL, 0x20A09A8AD5F4CC1AULL, 
            0x82D894E2872C8E17ULL, 0xA26D4B0F9C570A7FULL, 0xCCC998E6FEC6E9CBULL, 0x0610D864316ABC02ULL, 
            0xAD2F9151C85B1BCCULL, 0x0210AA3D0583FADDULL, 0xF32D55FC71509999ULL, 0x0E62B0B9CC03410DULL
        }
    },
    {
        {
            0x825E4EF8292A7843ULL, 0x6CF495F7D8C5C61AULL, 0xCDC8A8F86394BBF1ULL, 0x2F6D339F66E04722ULL, 
            0x3CD8C316D415C3B5ULL, 0x3FAB1E4891F1CDCCULL, 0x8E3962CFA6147D24ULL, 0x65963F6C0072A31EULL, 
            0x6C734433D60786D5ULL, 0x25F0472300C79DF7ULL, 0x72533CB43C66EC72ULL, 0x3B4C945DA1546248ULL, 
            0xA4453FFD2647D284ULL, 0x5F071BB9ED430EAFULL, 0xB99FAF2AB2327FF5ULL, 0x5CA697154C82B329ULL, 
            0xDE9C64887B828D81ULL, 0x096E3E66AAC26901ULL, 0xBED55E7610DECA92ULL, 0xA86E9F85651827FFULL, 
            0xC456C2E967F61608ULL, 0x2E84370EB19BCAE6ULL, 0x38BA8B49D4258297ULL, 0x89418BE5F8AFC434ULL, 
            0xA87CD5CCB688826AULL, 0x8269894E9F9EC99FULL, 0xF68AB5D8B7625924ULL, 0x7CEAD0E5F2CCE737ULL, 
            0x745D27FB1DC92C94ULL, 0x76F3DF7592ACF735ULL, 0x6348A6E52AC15592ULL, 0x3C998B03C0E0F256ULL
        },
        {
            0x2AC71FA2FE40BBDAULL, 0xA3916131D8501619ULL, 0x52B760F8D02D9F3CULL, 0xF1669FE61217ABA6ULL, 
            0x4F00C2675DE96451ULL, 0x5A1800D1D4B05D38ULL, 0x6973C44D61443EDEULL, 0x0A6E2C9A98199B71ULL, 
            0x838BD9BD4DF25F6EULL, 0x4808EC98CAEEA2EDULL, 0x19A7E0B231D0071FULL, 0x654C313C44829A26ULL, 
            0x6AF2D081FF1FD336ULL, 0x57E8C2F63186CCCDULL, 0xE10C5A53FC2586C2ULL, 0x300CD3456F344C48ULL, 
            0x545B48F9B62562B6ULL, 0xA0C1CAACD20860D2ULL, 0x03DBA69B8DA24E9BULL, 0x943367FC1F5DC202ULL, 
            0xF4F4B96ED52F227BULL, 0x51C54C238C5D2A36ULL, 0x63E1564BDED8BB26ULL, 0xE482352760F43DDCULL, 
            0xC1B000D99BE5069DULL, 0x44C56CB009B68EFEULL, 0x06420FD7601FE7ABULL, 0x9B804C57B6D481F9ULL, 
            0x6F19CF2876971145ULL, 0xC5632272C7D733ACULL, 0x6FB5DE162DC4A406ULL, 0x5CA5C870AA278510ULL
        },
        {
            0x316C761CB0B91B36ULL, 0x2A94AB32483A6688ULL, 0x7F37DE6B55AA83C0ULL, 0xE92C61738D342C6AULL, 
            0xA12CAB23C8E66ED2ULL, 0x21A8067C25EBD9D2ULL, 0x2DF1E937C0E30117ULL, 0x3C8470A7228C6603ULL, 
            0x1BC755E02F73FAE7ULL, 0x2702D2E8E4CD3C88ULL, 0xDC5D2644EAD894D6ULL, 0x98B9F1C65DE5F7FDULL, 
            0x2EC64ABE2E9EB4CAULL, 0xB83B248D9BA7B068ULL, 0xD36F0CDC88732A4DULL, 0x6A93BC38198CF380ULL, 
            0x7CBF01277724DD33ULL, 0xF0C412756F00F800ULL, 0x03F6490A70E6D471ULL, 0x56A0BF5EBB17263DULL, 
            0xC70A7576265A3F1CULL, 0x3B48394D824A2484ULL, 0x4106C1CA4387FD8DULL, 0xC3ACFC9222127428ULL, 
            0x895BD4A533E447F2ULL, 0x052812CE162FA60DULL, 0xCCE680DE81EEC109ULL, 0x3AEA61500E3AEAC7ULL, 
            0x8B0B13B9AB97D0E2ULL, 0x7F1E29969DBE7E99ULL, 0x3593C3E31719A01BULL, 0x5188B2C0464FC314ULL
        },
        {
            0xADC513783CEFCF38ULL, 0x371634A41F4284BDULL, 0xBE310855746EFFFEULL, 0x09880EF6FB733B29ULL, 
            0x7C8EA6CF2479BAF8ULL, 0xEC531F2F83DAB50DULL, 0xAB0A85691347573CULL, 0xAB4072B3B3F94C54ULL, 
            0x4089F4C8BC9EF6EEULL, 0x3A7E0A8E649ADBDCULL, 0x941D3BA5EB63DDE8ULL, 0xA72C9B51B5746461ULL, 
            0x7C2D6F53383F03AAULL, 0x02CBEDED51FC5CEDULL, 0x6286C8D07AD72A3EULL, 0x89D14FFED46394BDULL, 
            0xF6879F8DCDB5B4A5ULL, 0x9E4EE8345446B48AULL, 0x02E02E98450A9D30ULL, 0x5AA4C111E09B8022ULL, 
            0x2FB5B22E7625A414ULL, 0xEF58D93D7A67B204ULL, 0xDCAC420B6228E07AULL, 0xBCB4C164D125CC2FULL, 
            0xAC6B2ECFC3CDC8A2ULL, 0x99F20167FA52FCB3ULL, 0x0528A0C091C138B6ULL, 0x22EF2BCCE1C45D00ULL, 
            0x09DFEB32E49463DFULL, 0x26AB4DF2B624CEC4ULL, 0x558486B913709FA0ULL, 0xFD470AA1BA1DAE18ULL
        },
        {
            0xEB96847EE3661A57ULL, 0x02107C56A19DCD54ULL, 0x9D9B97D72180A35DULL, 0x6D1E73084DE54252ULL, 
            0xADA08FC649B5616AULL, 0x58B1CE1AEFA2613BULL, 0x29CE50E6D41672CDULL, 0x8AD04A18378A41D8ULL, 
            0x6D6F07D1368A4A12ULL, 0x683258FFC5EA1342ULL, 0x86D2B614C669A42DULL, 0x0E7F99839D5AA890ULL, 
            0x0B783587A9BEBA4BULL, 0xF39922E958C3F33FULL, 0xE92313DFC5E77726ULL, 0xECB486C4B9FD995BULL, 
            0xB7D2C6908457D588ULL, 0x6A73021FF63F1BC8ULL, 0xCE06AD55212C0607ULL, 0x37F2462425A273F8ULL, 
            0x7302E88313850664ULL, 0xB6AA7FBF09EC61ECULL, 0x40CDDAA107F5589CULL, 0x3F2F6FE07A545C11ULL, 
            0xDC38E5A632083FB4ULL, 0x30ECF05D2A72D866ULL, 0x292E1467426757E8ULL, 0xDC37D07F0864506CULL, 
            0xF8467EB0DE50105DULL, 0x8DED42E3FF314CFAULL, 0x988BEDFBBD5CE715ULL, 0xCA89967D29827605ULL
        },
        {
            0x76FDA7C92C8266DCULL, 0x550FE2F0CB5E6E23ULL, 0x718AF9796ACE8BBFULL, 0x59D766EB3D7A7F30ULL, 
            0xBE93CD975106EA3EULL, 0x161A5A259F575FFCULL, 0x97CBF35536097EDAULL, 0xA49BEBB1C32963CBULL, 
            0x6129D701AD679E9FULL, 0x6C24048E3EAEA51DULL, 0x90570C550BD10BF9ULL, 0xC32F93E7F0C6CA1DULL, 
            0x7B852FE17FB9A3C4ULL, 0xA2515ABE675D6927ULL, 0x09FEC8B0EF4014E8ULL, 0x83B350DF84045351ULL, 
            0xBCA3D30C9817AC52ULL, 0x0F9A1C6F422BB6F7ULL, 0xBB23A3007913CDE9ULL, 0x886ED7CF2DC6A272ULL, 
            0x52CB76E26304B4DCULL, 0x6B8794FE76253505ULL, 0x801C5960096FD366ULL, 0x3DBE3BF975BC7EF0ULL, 
            0x762FB38F8C67950BULL, 0x1A9F42B4644634DBULL, 0x6A4A902F155EA97FULL, 0xE64E8B2D7FC2E00DULL, 
            0xEFA01190AEC18AECULL, 0xAE6C45DABF52E8C5ULL, 0x56CFA81F76AF12E3ULL, 0xAD7977B04AFFFFF0ULL
        }
    },
    {
        {
            0x7BF24C979BBA17F8ULL, 0xFDE01E1CEF41E381ULL, 0xA1806E5D3E4C05BAULL, 0xBCFCB522B0E037CCULL, 
            0x1413BCBBDE214400ULL, 0x4BDBFC0598A0B0C9ULL, 0xCA93276E8EE1589FULL, 0xCBB1DC0E994A9292ULL, 
            0xA17B790F909F61D3ULL, 0x9D5E67828C7AD674ULL, 0x2A7D77E15829A0E2ULL, 0x6D76180C7B06830BULL, 
            0xD528D4BF5D68FA66ULL, 0x69055499C4C5E4D3ULL, 0x21A05EDAA2F82B6AULL, 0x711F4C4C907A64D3ULL, 
            0x469F33ED2A533C68ULL, 0xBECDBE2A17C45C74ULL, 0x653A1458C11BEEA2ULL, 0xEB5BA18A733DFF8DULL, 
            0x1F1C86A4B3477786ULL, 0xB6A428E60699F4E2ULL, 0x0CDF98B3733A5D92ULL, 0xFF87BE6CE858C65DULL, 
            0x57F956964B0D00C0ULL, 0x03820639CF64D975ULL, 0x8A118FA8B3643F94ULL, 0x331AE215EF3A3ACCULL, 
            0x5D8E34DE9881350CULL, 0xC24D137772DA6E23ULL, 0xC96CA45C9ED3B4FCULL, 0x334726D87BF393A4ULL
        },
        {
            0xEE8DEC867395B3C8ULL, 0x7A0B10A1062274A4ULL, 0x7CCFE2562FA660B0ULL, 0x1C36F1805C4D1B3AULL, 
            0x18FD8E722395498BULL, 0x7DA606619322EED6ULL, 0x4F5CAE003FE33648ULL, 0x104A65DF066991C7ULL, 
            0xAD9A7E7BFD7D9131ULL, 0x96C2A11BC7CAED75ULL, 0xD936D3A43A1F0225ULL, 0x59E45D6B386E2C09ULL, 
            0xB482994B9547E61CULL, 0x8701A4C60A96145FULL, 0xFBC088EC7F97F525ULL, 0x13C27D551EAA58CBULL, 
            0xD7EAB37407FE08C9ULL, 0xCF88512116823CC5ULL, 0x0F78353EB31D0D78ULL, 0x75093C5A54973A6CULL, 
            0x658E3F1D080392B0ULL, 0x63E5216AE9D18D5CULL, 0x028CF127EC18D0E0ULL, 0x97B950795AB57559ULL, 
            0x01D8C4D12C07873CULL, 0x8CBBD325636C1326ULL, 0xAF003B5C29989421ULL, 0xCC28FEBB7E814EFFULL, 
            0x287A497666CD0097ULL, 0x4B006A6961C21D7BULL, 0xF032CAFE06ED249FULL, 0x670D001623BD44B4ULL
        },
        {
            0x243448501E9F34F5ULL, 0x6D765660978E235CULL, 0xE0D7E89507E14BEDULL, 0x2FBE8E2F415C440BULL, 
            0xD659E9B4A4AE2CB9ULL, 0x6AD054F5BE805144ULL, 0x7508064AB940244DULL, 0xB88649F2444DFED8ULL, 
            0x13552D2C276979E7ULL, 0xD7373E6A39457A44ULL, 0x56B680712CB07520ULL, 0x7ADEC607FB9AD2BAULL, 
            0x83EB586F7511E073ULL, 0x1E1E4295D94B4C3AULL, 0xF1F5084EA4BD5438ULL, 0xF4B4FFB2651ABDC8ULL, 
            0x87155207AA0C8BFAULL, 0xE9500014889217B5ULL, 0xF057D277D70F1694ULL, 0x3E148F2FFB46F1CFULL, 
            0x957EFA0232F5CB0AULL, 0x7A0DC4E85BF775B9ULL, 0x6CF25247315162E9ULL, 0xB871536D892032B2ULL, 
            0xB9CD5A51EF6EEC99ULL, 0x9EDB44195CE73772ULL, 0xF0458B7BE92A5EF7ULL, 0x0738AA66D4F626A8ULL, 
            0x0D254949225D4BE3ULL, 0x10767C4B7B0B9F2FULL, 0xDED402ED2A5B0B65ULL, 0x7192FAA918F9515BULL
        },
        {
            0xAAD8E3012EF62BF2ULL, 0xE632527C532C433DULL, 0x7AF9DF0C9BD0A193ULL, 0x6014EFA1A58EBC82ULL, 
            0xC6361FDE312799F2ULL, 0x9B8BD424743ED658ULL, 0x86DCAFB92CAADB03ULL, 0x75006161E7FBE21EULL, 
            0x02288B2B6D155190ULL, 0x9262136382781224ULL, 0x2EEC85007E2C95BEULL, 0x78448E73F6358780ULL, 
            0x768675539B5AFD9AULL, 0x976427556DB7A1EBULL, 0x928A1D4C5C56F65DULL, 0x2EAEF4B1B1B314E8ULL, 
            0x700B5DB69D041F49ULL, 0xB889F7861184B6D7ULL, 0x25264D4451436FE0ULL, 0xB03507FBA3C47B5FULL, 
            0x4D95AAAF71BE3126ULL, 0x47EFBBDF25D4FC98ULL, 0x50C919BFFDDFF6E4ULL, 0xE59C1760D3F07AB3ULL, 
            0x01303C68A315E916ULL, 0x5E4E2059AF90A158ULL, 0xEACD8E199E4E6B16ULL, 0x4B3E89887C88704DULL, 
            0x19F9D1822FFF34C6ULL, 0x9421AA84F55FB110ULL, 0xD44C0431E24A001BULL, 0xE7A85EBC652AF371ULL
        },
        {
            0x330043A149E055AEULL, 0x1E6D7A40B0667E5CULL, 0x319A7CAD3717DD8EULL, 0xD0EDFC570F744261ULL, 
            0x06D5754B361CA1B8ULL, 0xF552EF09D123B59DULL, 0x8FBCB477515AF40CULL, 0xC16B943A5EF8A865ULL, 
            0xD74ECA1429B1A5DFULL, 0x59B36D9F610432D8ULL, 0xBBDC4B6169F689DCULL, 0x258C7D6DE3FCA8A7ULL, 
            0x7262C4BC6ED85E6DULL, 0x875538C2CB26721FULL, 0x0893977883F206C1ULL, 0x230AF1B6CBD1577FULL, 
            0x2D24663E49A28DD6ULL, 0xD9A4E3604DCB06FBULL, 0xBFEEABE6907CC9F0ULL, 0xF5CCF031AABF8AD2ULL, 
            0xA6E247295C596205ULL, 0x4255CB664B902A71ULL, 0xE2417582E5FDC4A1ULL, 0xEE4A31E1767C8EE4ULL, 
            0xA4BBD071EDA1135DULL, 0xF00C0571D901D8B3ULL, 0x7152971F413CF273ULL, 0x5C20A57F0662278DULL, 
            0x865FA20FF6FB471AULL, 0xB97905E47D3F89DDULL, 0x61798DCCAABA5019ULL, 0xF81C23B9205988BBULL
        },
        {
            0x503BA968FEB35FACULL, 0x262F7D65ED91938DULL, 0x7282CF6CBDA5AC83ULL, 0x6866519137D6555FULL, 
            0x0A24D840C46C63AFULL, 0x29120BC0F3912D24ULL, 0x76456748A6C850EAULL, 0xBD84DA121FDAFFCAULL, 
            0x9374E7CF725EBA8BULL, 0xBAF0277A73443079ULL, 0x1A2ACA173BD1CAF9ULL, 0x5D11980DEB9A587AULL, 
            0x37D885C2759FD2E2ULL, 0x2C00CE60D1DCE1F2ULL, 0x8C169A9F09EE830EULL, 0x831878D1ED0D37FAULL, 
            0x800BD06BCE98F514ULL, 0xF8B7CBD2CA27556BULL, 0x92E84BBC36C14031ULL, 0x64E16112E28AAE14ULL, 
            0x88EEFF3335BF6298ULL, 0x40F054A3861B843DULL, 0xB466032200F942A9ULL, 0x715BBDA332467FE4ULL, 
            0x9962C61B4EB2E9A7ULL, 0x878FBC3236150A34ULL, 0xC9F04805B2F04A6EULL, 0x0E8C3EEEEF05C7F9ULL, 
            0xFB1070F24527F632ULL, 0x31C3CDFEC041A823ULL, 0xE7A70B05836B1124ULL, 0x209EB897EFD51996ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseAConstants = {
    0xE3277AD0397A3820ULL,
    0xBBF1BFBC8302A7B0ULL,
    0xF64CA4D5ECAB94E7ULL,
    0xE3277AD0397A3820ULL,
    0xBBF1BFBC8302A7B0ULL,
    0xF64CA4D5ECAB94E7ULL,
    0xAD8EEE39C58CD9ABULL,
    0xA203775F89F37367ULL,
    0xAD,
    0x37,
    0xCE,
    0x5D,
    0x3B,
    0x40,
    0xBE,
    0x68
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseBSalts = {
    {
        {
            0x18EDE0434F8555E5ULL, 0x00885CA201224562ULL, 0xD8300C215DF419ACULL, 0x5D680C5FE69FA7ADULL, 
            0xF559353B110A6CB2ULL, 0x516E0E92C810F30DULL, 0x603F90C8E3334EFEULL, 0x0589B7F9F1762968ULL, 
            0xBECA199551F7FF2CULL, 0x4322B457ECC65F94ULL, 0x7111E23739FEAE21ULL, 0x4E5C20E1E5DE3391ULL, 
            0x04AE323E22F57B3EULL, 0x8EC5B79F2E3F3914ULL, 0x460FFB3846F5ACDEULL, 0x05FB3A9CB9934C4BULL, 
            0x321777CB9F25526AULL, 0xA4B165E317EA5D20ULL, 0x8407971AF2D8DEA0ULL, 0x70B74C2197D3BFBAULL, 
            0x25FB83DB9BA45052ULL, 0x8AFF1FD7B4A6D2BFULL, 0xAA9BDF61E9B1182BULL, 0x146337A23C47D11BULL, 
            0x2FF2958926A9AD28ULL, 0x6510058479ACA72AULL, 0xBB1942F209DA412FULL, 0x9EB9D3573E4E308DULL, 
            0xA5A38D74DD7905D1ULL, 0x7A0966C54DC9947DULL, 0x95D84529DF31CAC3ULL, 0xE929C80E0A3B94A2ULL
        },
        {
            0x0CD6E3B36CB1D0BDULL, 0x821E50824C0497B9ULL, 0x0EF14A4BE8CDD801ULL, 0x952EE77896D2ECEFULL, 
            0xB35E93AB01CAE396ULL, 0xECCC30C260A91627ULL, 0xC38A1A5C9737402AULL, 0xA3683602AF861B48ULL, 
            0xD8257C83A7CE9A5FULL, 0xC3A008AB92DB705CULL, 0x18D68AA278FF29AAULL, 0x0E6E6E3B58E82080ULL, 
            0xFF554E06E056B51CULL, 0x6BD6766DAA2FFAE4ULL, 0x2F4759C3ABA9DD51ULL, 0x2A455C06B4C0B51CULL, 
            0xF4AA3EED38106CB6ULL, 0xBD9AED43F5C7F061ULL, 0xAB8845325F171D7DULL, 0x2F537FD1BAB1EF6CULL, 
            0xBF275EFE06E5C867ULL, 0x8EFBBD8CB3D6861FULL, 0xA85D6FC59A48F8ACULL, 0x289AA2FAF8ADB9B8ULL, 
            0xC698F27DCEE9C974ULL, 0xDD210D2D8DC410B1ULL, 0x474A61AE7BDF673AULL, 0xA2BE23E3FB041ECBULL, 
            0x4A1F424A86876091ULL, 0x393A4A84AFD4095BULL, 0xC40ABEB93A2F4146ULL, 0xDC13AE3E857AFB6FULL
        },
        {
            0x0897ACEC012CEA56ULL, 0xDDB8AD4089E312D7ULL, 0x67B2054294FB309AULL, 0xD76835AE1B447CD9ULL, 
            0x66A36ADF04410F58ULL, 0x8659D4301EDC3A6BULL, 0x5D422CE4A46FD12EULL, 0x8B77051B65200AF4ULL, 
            0xC28B7988D1FEBB91ULL, 0x7EA7394E9A2A5E19ULL, 0xC600850A4FD5073AULL, 0x906F734B1B5B4D68ULL, 
            0x6C9869A9A5FD32A5ULL, 0x6D17E3D22EC9D64FULL, 0x0C02007DB3B9E531ULL, 0x1D493AC36F35ED95ULL, 
            0x375EFA552FBA553EULL, 0x4BDE17EC35E6B5F7ULL, 0x7749B08E111BD914ULL, 0x3621693330884ABBULL, 
            0xAB27605411E71130ULL, 0x5BCFA83062EC7DE1ULL, 0x98175A0FC76D93D4ULL, 0xEAB0A63C8172C2B2ULL, 
            0xAA4790CCDEC5AA0CULL, 0x147FA48716B8F41BULL, 0x834DE9F8EAF1C69EULL, 0xF74AD359B32727D3ULL, 
            0x8290BD286D923214ULL, 0x02D7DC79CD8D224CULL, 0xEB0A751833AECF2CULL, 0x8708D484B4223C5EULL
        },
        {
            0x124ADB192C3C76B2ULL, 0xE58C11448CC78C8EULL, 0x3E5A4C3228C8DE49ULL, 0xCE6F1D882EB030AFULL, 
            0x7AA04CD3B4E95B61ULL, 0x67BC5347D46E6B10ULL, 0x9CA62C98BDD8219EULL, 0x30B801AFEC5BB1A6ULL, 
            0xD48A5A2D25238F19ULL, 0x3142F1F5CFFC3C2DULL, 0xE803FD57344EE2C9ULL, 0xDF7DE154238CBB7EULL, 
            0x81F13E5AF5C0290FULL, 0x57DA3113E800B3F4ULL, 0x30F08ECE3A3F5DADULL, 0x109A06AF6D08AECFULL, 
            0xFBA54F64AE8B86A8ULL, 0x7D24A8D0E14DD506ULL, 0x29BD20E1283BD3C5ULL, 0xDA561345FE0AC408ULL, 
            0x28AAF18FAE734739ULL, 0x47C611E0B62524A6ULL, 0x91D0B9A9D58AD1E0ULL, 0x21AD884947509E0EULL, 
            0x2455E2B9751FBF54ULL, 0xCB661A255D043194ULL, 0x5DEAAA972ACF757BULL, 0x60AE2A27D90884E1ULL, 
            0xAC87A6107D0D5DAEULL, 0xF111E76D05AD2539ULL, 0x0B49821A8A34B691ULL, 0xB0FC494BA62F76D3ULL
        },
        {
            0x5A458E16A51FC52BULL, 0x9540D19F4E1AB114ULL, 0x88C2D3059FAB94C4ULL, 0x8FDE947E1119F581ULL, 
            0x59BD391A33643914ULL, 0x5666124B47C44422ULL, 0x695B7E4C2F783235ULL, 0xD67A538617157FD8ULL, 
            0x6DF2CE737C196A45ULL, 0xA1364E1256523E3EULL, 0xC3004236CDCD8A8EULL, 0x4A2786ADF7A47AA5ULL, 
            0xE531662C679C3DC4ULL, 0x1E64A28486ED5982ULL, 0xD7FAF5FC987F7A9CULL, 0x7B6A9BD96CA5EB87ULL, 
            0x48ABF3D4D4EC5CBAULL, 0xCC642AB4317E6B1BULL, 0x6C6AF389E5A98073ULL, 0x31B9F440A19AA433ULL, 
            0x1D7DFFBBDD3BBE99ULL, 0x2BFC69419AF91D04ULL, 0x3A885AD43B502FC7ULL, 0x8E706538431470BCULL, 
            0xAEC3F5ED9AD1B87AULL, 0xA326379C7FEC492AULL, 0x2D0CEC0FA26F44C4ULL, 0x5C9974D2EC259099ULL, 
            0xBCCCD06BD8667666ULL, 0x437ECD0963E41CF8ULL, 0x1E729F3024739CD0ULL, 0x388AA86FC2A9FBC3ULL
        },
        {
            0x40E6386F44734C09ULL, 0xAC0B75E426F76BC3ULL, 0x86B7140059B37EE9ULL, 0x31F5B133285F4DE3ULL, 
            0xEAE863DDC6E44B45ULL, 0x2A9C26B8BF6F1658ULL, 0xD883F8087D6CE64CULL, 0xAEBDD131789D5F73ULL, 
            0xC9502AD850BAF3FDULL, 0x1B06A4A6930B31ABULL, 0xD599B84E70B5EBF9ULL, 0xC753D11B7157FB81ULL, 
            0xA52E284F87FD167EULL, 0x4DA1EBDD1311905FULL, 0xD844895D82EA93E4ULL, 0x262BE03717A15186ULL, 
            0x60CF2939741AF03AULL, 0x08969C148D8B4020ULL, 0xCFE5B049EB95D505ULL, 0x763BC82313D02DE2ULL, 
            0xCB8B383ED27A6E83ULL, 0x2BFEFE02D7186D7BULL, 0x9B154B421A8A5807ULL, 0xF3CEC4BCBEED7F91ULL, 
            0x281FA1D50C01A1C9ULL, 0x5BD72E195E4CA82FULL, 0xFB7799303BDEAE49ULL, 0xD0B2DF474D2153FFULL, 
            0x4ED30CC7FE14A038ULL, 0x041E41F0485A6A21ULL, 0x317DD092F1EA140AULL, 0xDE6F0866B59987B0ULL
        }
    },
    {
        {
            0x7B41319423B1D0E4ULL, 0x782ECEA195CAB311ULL, 0x3645D107E73CD11DULL, 0x4040873689519A00ULL, 
            0x22DC561AC7281EA8ULL, 0x037B2AFAF3D67ECDULL, 0xFFFF0566F1665ECDULL, 0x8C4B04ECF1F64C3BULL, 
            0xA58F737AA1A3CC09ULL, 0x2062E3B4C71A7526ULL, 0x0C82E3C9DD56A596ULL, 0x8389D7956738855FULL, 
            0xD21F3753CE5E868AULL, 0x18F07B1A5BE0BA4BULL, 0x1069B4777153604EULL, 0x584E748BF01F9615ULL, 
            0x439E5E44FDF28860ULL, 0xD500BC6532EFCD96ULL, 0xC08C1D548669C773ULL, 0x2A6E616160229DBFULL, 
            0x4585B4B1CC648381ULL, 0xDFE17386140F1251ULL, 0x599E3FD51F452FBAULL, 0xBE035B9B0497C88FULL, 
            0x857DDC9815DEAE14ULL, 0xFFF1415121A6DDDAULL, 0x9909127532E41587ULL, 0x30A1098216A6DF50ULL, 
            0x059889F429ADA95AULL, 0xAA2315F97718EC26ULL, 0xC77A5A349F41DBE6ULL, 0x271D632E2A1CA8EDULL
        },
        {
            0x5CE9CA7D6B48AB86ULL, 0xCDE4467FFCA1183BULL, 0x790D982FA4582577ULL, 0x822B394745BB654CULL, 
            0x85D1F85C8A7FCC7EULL, 0xE420B6F73C77931EULL, 0xD828061FAB1FF833ULL, 0x004BF37FBA9BC2ABULL, 
            0x966D6815EFE259BAULL, 0x0BB5BBF75C722291ULL, 0x148C8D5F6B6F7394ULL, 0xE6DD7D8E67E3A3CCULL, 
            0xADE90AC2C63B1E87ULL, 0x5D8CFC149B21A390ULL, 0x5DFD6DE604810558ULL, 0x1EA180A3738715EDULL, 
            0x789D4579CCFBC1B3ULL, 0x6A19AD28F4225DE3ULL, 0x89CE494BE408211AULL, 0x744D65F27FD2881EULL, 
            0x518E09C98B4E6828ULL, 0x1C21B3DCACB8F80AULL, 0x356C6021A0597556ULL, 0xD96A0AB1FDD3C1A8ULL, 
            0x7D9E2F7ED0A5A07DULL, 0x984CEF5111114F93ULL, 0x42214D08C5588A40ULL, 0xD6502AD0C9638376ULL, 
            0x3B480AAC80B6909DULL, 0x66A7DC18D58DF745ULL, 0x1E23CF3C351FE82EULL, 0xA8186D39ED5B28D6ULL
        },
        {
            0xE2CE3F9A67DB8104ULL, 0x4B73AF0A25A6E25BULL, 0x4E935115E3E29D3AULL, 0x66589C25D32FB6F7ULL, 
            0x813A9445F35F302FULL, 0x9078FAF7F7562ACDULL, 0x2544B64B62D1C7D5ULL, 0x27E0C805A1263B2AULL, 
            0xB307F3DD73B5EBA0ULL, 0x0FD44EFE7D6FD9FEULL, 0x7F4350280BC5C20EULL, 0xC2DAD7C38B48F335ULL, 
            0x9A30C1434F87DA34ULL, 0xD462F796A1663BA7ULL, 0x514BB28168E043EFULL, 0x902292BEC22E3D8DULL, 
            0x1DE737A26EFA321AULL, 0x67B9BAD6AD4415E8ULL, 0x288FADDC02D7F3A8ULL, 0x045389B241BBA5BEULL, 
            0x95F604B91B14DFB3ULL, 0x5EA1CA0E9039A307ULL, 0x21C09F1DE4800811ULL, 0xCAB5A286CD358CCCULL, 
            0x7B017AAAF4BBC2D9ULL, 0xD77B02BBAA2E29B7ULL, 0x8C6309B8F0FBAB9BULL, 0xE3E16AE8324D3492ULL, 
            0x30D5440B40F2C08BULL, 0xC0129EC3CF7A5E97ULL, 0x653DB980F42C6CE9ULL, 0x964C0EB62DF083F0ULL
        },
        {
            0x29B12C7A6D6125B7ULL, 0xFF9F12E33CE19E20ULL, 0x6034217E7FCE3F47ULL, 0xE122DD4AC15511BCULL, 
            0x06B4AFF78C8B3A94ULL, 0xB07543BE56767EB3ULL, 0xC36836FBAE16F260ULL, 0xC6C42A5A21B8F4F0ULL, 
            0x1E72ADA407A6E7E5ULL, 0xDAA373AF9D338118ULL, 0x891E2528BB041761ULL, 0x6B986D2FC7D26637ULL, 
            0x55C923008466D2A3ULL, 0x84B51C8F4747C4DFULL, 0x607B63CAB91BBDCDULL, 0x16AA4AA1B149E8E7ULL, 
            0xDED98BC730E69608ULL, 0x48D3A00664FF5EDBULL, 0x1C767BDF661CBFC5ULL, 0xCA1AEC1C39416FB3ULL, 
            0x6830181CFF8ED84AULL, 0xEA81FFAFE5E5005EULL, 0x84DB627ADE128F91ULL, 0xB048E1129DAB26CAULL, 
            0x832F938E893987A5ULL, 0x47AD99E46955046EULL, 0x72905F58FFBCA95EULL, 0x8474829CD4E05E31ULL, 
            0x4E189FD14FC879C2ULL, 0x0BCDC7A3C205EDCFULL, 0xF2859176981C8A56ULL, 0xBC746A04F30AE7BEULL
        },
        {
            0x3838C46B5CA39D8BULL, 0x049BAD1B4844E8A2ULL, 0xDB0CD4E14641781CULL, 0x8DF66E1B725F86AEULL, 
            0x901640B144044B92ULL, 0x69D9FCAC734C1E50ULL, 0x4DA5D1F2CB207F1EULL, 0x1083D9500A607414ULL, 
            0x8D3D4DB9004372C6ULL, 0xEB7987E9A7420D4EULL, 0x623CE131E7DE8F63ULL, 0xCC2AD01074C17241ULL, 
            0x93A33119E488F0BAULL, 0x3FD9B958828667D1ULL, 0x4BD7704F6283344FULL, 0x667C6EC9BEAA689FULL, 
            0x69FF9CC415D2E3ABULL, 0x4515D84F400C272AULL, 0x5F21000F3F3AA5DFULL, 0xECE9CCB333294005ULL, 
            0x5FF9EB854F57746FULL, 0x1DD9603F70FD5C17ULL, 0x543C7EFE0101F35AULL, 0xF40B8A433DF0162AULL, 
            0x5D6EA7014ABFFFB9ULL, 0x865038CE923B338EULL, 0x07F55FAAB8C3BCEEULL, 0x5E1F9713AA8FFD0DULL, 
            0x23E4DA0AB5AD7E84ULL, 0xB5C0ED1280B63A8FULL, 0x73744C2F8E9D40FFULL, 0xCF13C9A86F906E38ULL
        },
        {
            0xFFED455D00682815ULL, 0xB1287EE125A3A512ULL, 0xF1C79467534F2993ULL, 0x6367A315CA58E19AULL, 
            0x93F0C74969E470B8ULL, 0x13352319EC997333ULL, 0x76B0C04CD4A14B61ULL, 0x48E8BCA880C9CED1ULL, 
            0xCAC17785685FD70FULL, 0x674CC1E6A9C44986ULL, 0xC9F9C2EF0C7DB8C2ULL, 0xC380A2454D6C5329ULL, 
            0xD833910C8EC11B20ULL, 0x4EB29747DBEE9749ULL, 0x6D8AA42F1F754B6CULL, 0x0964C8A89DD8AC09ULL, 
            0xB74060194FF27D80ULL, 0xDD6859ED410B7BF3ULL, 0xD5AE8946BFD9A04DULL, 0x63473034834A5185ULL, 
            0x244D3972A359FC37ULL, 0x300FE2CEFBD41723ULL, 0x04C1092052ABB2CFULL, 0xD6BD560EDB9AC550ULL, 
            0x8EB97F460B3150D4ULL, 0x9DDFD3EA8765BEE8ULL, 0x3049A1BBC0F1D0EDULL, 0x1C5776BFC11B00B7ULL, 
            0x958F2A8627169382ULL, 0x49432838D903FAECULL, 0xB71098F4367A3DE3ULL, 0x72CFF3E886B77F65ULL
        }
    },
    {
        {
            0x1A4CFE0BF1E2A767ULL, 0x6A4215DB5F39A25EULL, 0x2C49F72ABEF97A80ULL, 0x48A157C634A90EBBULL, 
            0xD3004AEA9B42C745ULL, 0x75BE23958168F20AULL, 0x38370FE16B778FFFULL, 0x9A38AD68341EEF94ULL, 
            0x8B071432C390067DULL, 0xCDE6E732D534B448ULL, 0x21F444EB77E04A1BULL, 0x0B31FD3BE6FE6B77ULL, 
            0x106E2AAF35816C60ULL, 0x19B2D5069E675DBFULL, 0xA024EDD3D8D27955ULL, 0xE501E5F0B5D432D5ULL, 
            0x891C44649BEF015EULL, 0x1BC65DC21CE38269ULL, 0x72783A4FC4F600CEULL, 0xCB18D7F50BA06EA1ULL, 
            0x5842AA1675A59787ULL, 0x66CBE1F64BC5EFFCULL, 0x598F576CFFA84505ULL, 0x4C38A1471B36B95CULL, 
            0x4FE4B3787C7B18FEULL, 0xFC3DB175727EC2B2ULL, 0xED13E0AB0F1C4ABEULL, 0xDDF64F14785AC19DULL, 
            0x857F7F7DD477060BULL, 0xD1646DC053E03709ULL, 0xE56FD49AF2C04CD8ULL, 0x753ED654B1F77148ULL
        },
        {
            0x559FE9F885DF3228ULL, 0x5DEF7A899814EEC3ULL, 0x8FB6E2BE944F1BE8ULL, 0xAC94E17A376EF053ULL, 
            0xEF22AD1D521572A4ULL, 0xC0CFFA4FB4945522ULL, 0x69B9CC9C02E6B653ULL, 0xB668B736ABA0566FULL, 
            0x2A91D255B35D9475ULL, 0x7DB9DFC04418FEFDULL, 0xDB66791B05065FC7ULL, 0xA8601719A85BCFA5ULL, 
            0x2802BF030017CA7DULL, 0x4EC118588B65D36EULL, 0x4E832A3485A7BABCULL, 0xA13D2E5E81DFC0D5ULL, 
            0xB1161218B7F319FDULL, 0xF0ED5E465C6FA3EAULL, 0xB049FC32E37B5777ULL, 0xDF9CCFCF5DB5DED7ULL, 
            0xCF9A9E50A75E5780ULL, 0x2EBF908055629C4BULL, 0x14D5E9D6A5256464ULL, 0x2C574246D21B3B78ULL, 
            0x49B4044547A9B989ULL, 0x1F4A73F23BC60F9EULL, 0x927180FBCB83B4C9ULL, 0x67A6EA041D3CAFBDULL, 
            0x1D55E6C0CD37A707ULL, 0x7EC3CFE62CF2E3D2ULL, 0x4B7AEF94A79A1B95ULL, 0xDDEAB9D8A4CC9293ULL
        },
        {
            0xF16576780D050907ULL, 0x0C912CF528B72902ULL, 0xF079FD41FC376BC1ULL, 0xDBAAA8D2F81B9614ULL, 
            0xE9A2ECF9FD3BB981ULL, 0x3AE8EE98A0D65AA7ULL, 0xE86C9B7BCF5B64B2ULL, 0x22512EF861ABC560ULL, 
            0x784B5C62EABA8901ULL, 0xE11DC2CA68C798A2ULL, 0x9CF318EF382F4319ULL, 0xE52706763269D61BULL, 
            0x465727399A987B93ULL, 0x2F01C5C5A5BBF5A8ULL, 0xC36ED7F31B397F20ULL, 0xC0E74DBA3A33E1E1ULL, 
            0x5F1C8A47A70FEEF7ULL, 0x4DD6246F01AB3615ULL, 0x6B49EFAA78ADF3ACULL, 0xFA96F093DC29C316ULL, 
            0x451C628C2848F8E9ULL, 0x68E9E22DBD0895DDULL, 0x0F303AA515C155C0ULL, 0xC8E7D5030C7C8151ULL, 
            0x053527C8586702A4ULL, 0x9FDFA1BCCD680328ULL, 0xAC9B88DCA655B92DULL, 0x9843CB04BA88FA00ULL, 
            0xCE1CDDE87BB4C830ULL, 0x17A45DB907CA07F1ULL, 0x060830AFD6FB7830ULL, 0xD4AE92A3F5DF7094ULL
        },
        {
            0x99528CED04C42A08ULL, 0x8FE4E067606A1DF6ULL, 0xFC335A404AFF3682ULL, 0x50AB4D15D9597690ULL, 
            0x84203050A6CFFA81ULL, 0xB40E7D646D47A721ULL, 0x3C7C2028B171F976ULL, 0xE1BCA21A48150FCBULL, 
            0x8DD78A75A7AC1E06ULL, 0x917235B2978EE3C4ULL, 0xC2F7516B158DC306ULL, 0xFD6E52A58037333DULL, 
            0x0EFED455437B8E48ULL, 0xD524CE7B4D0EEC17ULL, 0x4EF21E8FE8740AB4ULL, 0x05A304E4F00CBC2AULL, 
            0x9DFA2AEF7C484186ULL, 0xBA988A516CD4C45EULL, 0x3F98903EE907E27DULL, 0x2F770D4C517E8824ULL, 
            0x99B8F796C7E07D96ULL, 0xC30D126E7A2FFD11ULL, 0xF1464B6429F95307ULL, 0x90080677CA393930ULL, 
            0xDC58F0143C1CB223ULL, 0xD5AF0EC31A1378E3ULL, 0x4387739B718624CEULL, 0xB66C33C3D5E95046ULL, 
            0x3EB06578CF45E4B6ULL, 0x178E534C0DFCE66EULL, 0x66B7735A4B46A641ULL, 0x40CC8CB40ABDB290ULL
        },
        {
            0x2B2D1695A3E08E11ULL, 0x37F21A6616FF2939ULL, 0x193159B5208A816EULL, 0xA6E435ADBC3AB240ULL, 
            0x2DD7E3A9CCF0BCCFULL, 0x6E4C76223B0489AEULL, 0x85517482C1CF0B83ULL, 0xE2289A85F49FC907ULL, 
            0x61F8F9F69ADDC547ULL, 0x7658617A80B825A4ULL, 0x697152CD60B9ADB2ULL, 0x29DBC3D480B43057ULL, 
            0x6FB7B0276B4DED48ULL, 0x8B7FE55768A46201ULL, 0xD64E5474BAFC694EULL, 0x0C0B34F5B4A7F59DULL, 
            0x91BE8E1E99583933ULL, 0xE98C3A3A744700A6ULL, 0x904D376B81E0E69CULL, 0x3DA7C0C855B3CC3CULL, 
            0x7D783B741CD35205ULL, 0x51E81D520285264EULL, 0xB06CC56002A5AB37ULL, 0x093BEE264D34AA43ULL, 
            0x2A9167DE9116C134ULL, 0xA810244EAE2D405AULL, 0xE21AB63D46D658FAULL, 0x747E7A96536753CBULL, 
            0xE095AEDC6A465B5BULL, 0xD2E6719342C8EC69ULL, 0xD3DE1A879F3C2E6CULL, 0xC82A5F1278774443ULL
        },
        {
            0x880B56F8AB3A65DEULL, 0xE991FC01388CFB43ULL, 0x7CB305139520BA31ULL, 0xCC800C2FEC9B7339ULL, 
            0x8EF238FF0B65C20EULL, 0x21611DD6E3391D3EULL, 0xE772F2B58DB599A3ULL, 0xF688DED30DF9D059ULL, 
            0xF8EDF93FBB8E34A8ULL, 0x0767C65E5D4512A5ULL, 0xE1362388DEF6C5EEULL, 0x7F5C8EDA8B81D6D3ULL, 
            0xFC87952B0CB11E22ULL, 0xFFCA509740A0E92FULL, 0x85BE4C3CF3C046E0ULL, 0x19CDAF936177285EULL, 
            0x19BC366B8DEE315CULL, 0x561245000302F7E4ULL, 0xAA10226FECB58742ULL, 0xE17B35C5FA46DC99ULL, 
            0x89EB7EFAB2BBD1AAULL, 0xB591FCDABF5276A6ULL, 0x03E8755D8C59208EULL, 0x89A5851571767080ULL, 
            0xC74C7F20F9D2FBA4ULL, 0x0C9AB3EE7845D62BULL, 0x8C64F46722D3EDBEULL, 0x44F12193F0DF5535ULL, 
            0xCCA30A974626DA71ULL, 0x0C44BA054A7BF3CCULL, 0xF68C753674556602ULL, 0x23918861F0EA2C5DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseBConstants = {
    0x528C896CBC6B33E1ULL,
    0xE15FBE6ECE5291ACULL,
    0x5C919244A50FF3C5ULL,
    0x528C896CBC6B33E1ULL,
    0xE15FBE6ECE5291ACULL,
    0x5C919244A50FF3C5ULL,
    0x870E6EFC60D991F3ULL,
    0x6624290EE719B96CULL,
    0x3B,
    0xB4,
    0x26,
    0xB0,
    0x65,
    0x45,
    0x4F,
    0x44
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseCSalts = {
    {
        {
            0x1A0756B7FC2E1650ULL, 0xCE7E41170165A259ULL, 0x1CE35F6B4213B610ULL, 0xAF3EF53D62F9E35AULL, 
            0x3083740F08EFFC99ULL, 0xCD86AA3F08FBA410ULL, 0xFB198EF05F73BEE5ULL, 0xA1F697B8ABBCA868ULL, 
            0x503426B15B47F8AEULL, 0x522EB6C415313BF1ULL, 0x48B7DDED3EE39259ULL, 0x3D313553D3DCD0DBULL, 
            0x0E5C3C792FC6AD2EULL, 0x0B1E8ACE36D80A45ULL, 0x83A69B4AB8F94ABAULL, 0xB6F1F9FC57602378ULL, 
            0x6783E5521CAC0D5CULL, 0x40656F4F206F5065ULL, 0x81454D45351C0EB3ULL, 0x0DECED4651834305ULL, 
            0x650CB4521AD546D9ULL, 0xC35B52CF2783C31AULL, 0x99FD74B23425C275ULL, 0x3B4F85C739183211ULL, 
            0x3BD22D3AA74156BDULL, 0xAC15019B61BE2B16ULL, 0xAEE0506CA874B02CULL, 0x77F4C2C0B5B0798EULL, 
            0xD31E2AEC05F90808ULL, 0x9A30BDA4EA5CDC1FULL, 0x3D1777C5E97AA4F8ULL, 0x6D60B3104EF1C711ULL
        },
        {
            0x40AEEF12C918A6A8ULL, 0xA622D3695B7CE54FULL, 0xE43E6206F73842F2ULL, 0xFF10194172A28A91ULL, 
            0x948CDE584ED86D15ULL, 0xFBDD0A02660B03FDULL, 0x750EC9F67B6569E7ULL, 0x65349F88878743E3ULL, 
            0x56DBFE4E3F6C6CDAULL, 0xC50F84153AECB53EULL, 0x5D3DAB4E5847D69BULL, 0x45472829D5FE2183ULL, 
            0x8CF5372F86E48DF2ULL, 0x299E9998B90E2115ULL, 0xE3F839ADFFC27B57ULL, 0xF48E9212CA987641ULL, 
            0xD6B5DDEF8F293890ULL, 0xF4F0681FFFB53E30ULL, 0x8D197CE44AA8F1B6ULL, 0x4C5BB71A9150D7D9ULL, 
            0x8EDB644AD9F0A013ULL, 0x87381A1EEB2E35DDULL, 0x0A72190992E670CEULL, 0xD66AC38C3B7A03A0ULL, 
            0xFA66FA03DD119CAAULL, 0xBC8DE8074CED09B1ULL, 0x7E8E96D79E40963FULL, 0xB556B7EEA77DF25EULL, 
            0x90F9F435167C861EULL, 0xC716EE608DDF3960ULL, 0x56A995AD307BC1C3ULL, 0xFDBD9D210FFFE314ULL
        },
        {
            0x5BE07F0400A01409ULL, 0xB0253492F0C997D3ULL, 0xD0874C74C4FA6059ULL, 0x6CB4E8CC4C84AEE3ULL, 
            0xAC0A8FEEF570771AULL, 0xD4E3442312B2F9BCULL, 0xF9B040D9E682AA0DULL, 0xCBB4B605CB817339ULL, 
            0xEE9A1B03BF718B48ULL, 0x202CAA98062A372CULL, 0x0473ED6C80BFF6C4ULL, 0xEECCF2D4EADD124CULL, 
            0x2E6E5442C5ED9844ULL, 0x5340EF230B8CA0EFULL, 0xDD32D42B37DB08DFULL, 0x4BD8FD12361D9A88ULL, 
            0x5A9B5871BE0F5277ULL, 0xFF681EFFBBA22580ULL, 0x036F6BED35E5ACD7ULL, 0xC66FA94D438B86E1ULL, 
            0xFB3CAC3AB11766E4ULL, 0xAA9551A8FFFD156EULL, 0xA3FC66C538A12CFEULL, 0x38EF711F175D507AULL, 
            0x7CD028E5FB94F49EULL, 0xE6048C2A909229DBULL, 0x40DA765048AC6538ULL, 0x76B0A98C9EB3A860ULL, 
            0x513A9E625CE2117AULL, 0xDBA76D012EDE4582ULL, 0x35FD901EE1C53280ULL, 0x3FE3316E266A5A66ULL
        },
        {
            0xE72CFD7064C33A69ULL, 0x9977A9326C5D7952ULL, 0x4A9DDFEE016B8A97ULL, 0x8EA977DB19F1A7BCULL, 
            0x61D6997890B58661ULL, 0xFF13A2E8B0D57255ULL, 0xE88673E6D91DC807ULL, 0xA98FC3E8A8292178ULL, 
            0x0C9282E7A4020351ULL, 0xA8843F676613B7DFULL, 0xE6B0C0902A47C95CULL, 0x2FB9BC3FE131FDCCULL, 
            0x34AF331C549F4B3DULL, 0xA2BEAD3104933BCAULL, 0xB3016A037477B53AULL, 0x700541F1B5B79113ULL, 
            0x4DEF651BFDE5217CULL, 0x9CB0748F9FBBE8C5ULL, 0x7B251C6756203804ULL, 0x48282766312E7BD8ULL, 
            0x1FFA791BCA05B15BULL, 0x1EDA845896ACF94FULL, 0x5D6FB0F0DC3FDE96ULL, 0x406A157D1BA93193ULL, 
            0xF8717AD8DBCB6EE4ULL, 0xA719AE055EF2FC2AULL, 0x8BED8B91C846A0F4ULL, 0x8EE20CC7429525DDULL, 
            0xCC749347841EBA60ULL, 0x3BD5C2599505C9E2ULL, 0x45908B2B4F2FC78BULL, 0xA40CD11CAAFB7B73ULL
        },
        {
            0x34888215645DBD97ULL, 0xF5DC7EE02DD27C8AULL, 0x27DBE7DFEACC172BULL, 0x4A80D2F63F5BC405ULL, 
            0xC5F8984284C04DB0ULL, 0x6515069573971ABCULL, 0x8DAB9938DEE71C44ULL, 0x4CE5DEC586145E95ULL, 
            0xAE5553C26E522B62ULL, 0xB263445F8ECE1F89ULL, 0xB8207ED11153066BULL, 0xAD0A109B2E04B2C6ULL, 
            0xD0E6636E796956ECULL, 0x92650CB268F4D2EAULL, 0xAF96546802BDFFF5ULL, 0x9B1ED57F19643B36ULL, 
            0xABF5EE219012C59FULL, 0x81065641970C4354ULL, 0x08C469213DE147E2ULL, 0x47E96DB8FA30AECCULL, 
            0x95D797BE6A2EC288ULL, 0x8C7A89D619B590C8ULL, 0x2088EE9D605847EEULL, 0x5FE574C86126F846ULL, 
            0xA9D81E8BB3FFA0C3ULL, 0xB9EDF438031463D7ULL, 0xB3C119187FD9184FULL, 0xCB28945B0A37931BULL, 
            0x3AD38D48BAAE2D7AULL, 0xD74B4C1D2CC4664AULL, 0x84DB16D4CD284BD9ULL, 0xC70E401E05E0B286ULL
        },
        {
            0xFE50E512F010F176ULL, 0x4C08E1234EDEEBA1ULL, 0x9016F7FAEC854919ULL, 0x90BB9317B4859D71ULL, 
            0x0760B93ACD656BE7ULL, 0xAF3B22C51577F879ULL, 0xDA94AA21708362D3ULL, 0x2D806B40282DF7E9ULL, 
            0x045178A19BF777C8ULL, 0x18E35386D3BCFC95ULL, 0x83C621A2507C1BD3ULL, 0x4264CD54668191D5ULL, 
            0x590B7F7CD3398083ULL, 0xA910D5C009123655ULL, 0x5F11E87385907F38ULL, 0xF4AE236490569E5CULL, 
            0x669DCB309935B9D0ULL, 0x4A673D933144EBC8ULL, 0xF775A136613766A9ULL, 0x560DAF4B40551E1AULL, 
            0x9498BD348F6A1710ULL, 0xE90C3A8BB50F96C3ULL, 0xA75CE080AB3539FDULL, 0xC3021D12D1E5CEABULL, 
            0x435A6CF9E34E7008ULL, 0xB126C944DBECC6ADULL, 0x661181B91C11E064ULL, 0x05045DDC71F13F5FULL, 
            0xB913AC39C5E1A596ULL, 0x3ADB19FDAD31F284ULL, 0x9F99B1B12F5FE3D1ULL, 0x045437867B4B01FAULL
        }
    },
    {
        {
            0xA84B6DBEAF3F7570ULL, 0x5E5BED43E343A1DEULL, 0x43BBC64E777285C6ULL, 0x6DB4BD15A3E4F570ULL, 
            0xA90A97094E581F3BULL, 0xE27B3839411CDE3BULL, 0x22924E03776E8E5CULL, 0xC5A1EF6D7AC7F172ULL, 
            0xBB78BAA00FD4B59BULL, 0xAD50F2BFA70B00BDULL, 0x6084448DD786BFCEULL, 0xC5D0EC5071E3968EULL, 
            0xA15D68BD0F8BABECULL, 0x3E89E08A0931F33CULL, 0x21DBC7A6DBDB32CEULL, 0xA8F7CD997779BD46ULL, 
            0x514A0FC9AE553BFAULL, 0xEAAB4E37EBC00A82ULL, 0x29CFE3BD9141CFE2ULL, 0x668359278B6B02D2ULL, 
            0x48574DDB0C348AE8ULL, 0xB4199734D28C29F9ULL, 0xDDEDD0BA93C1B688ULL, 0xBB4925B0D0F7FFDCULL, 
            0x147FDD3E89E3FCFFULL, 0xCBB7BBF304BE1F9FULL, 0x2C0FDE8BAAA750A6ULL, 0x1DC0B692E1709486ULL, 
            0x6D6BCD4161137FB5ULL, 0x308D25B8A832E4A4ULL, 0x04A01C9652FBB186ULL, 0x69CEF4007F99C4E1ULL
        },
        {
            0x69CCDCB83C40C8FBULL, 0x354EE90FF47A3211ULL, 0x813C0FF31D23BE3CULL, 0x7D746902F7F3EEB0ULL, 
            0xAC7CC17ADCAD5A2FULL, 0x74A59A0D8613A74AULL, 0xBF7BED4871493998ULL, 0x861A26E959C1D8A0ULL, 
            0x895239AB95DCDF1BULL, 0x76B9DC9B2FB34D9FULL, 0xFDFD8A2908AD450EULL, 0x42F33F5CAB82B58BULL, 
            0xBF8D83C9F0302BB2ULL, 0x06B87D70D3F94D1EULL, 0xF82706DF545DFAA8ULL, 0x5251851D346DB626ULL, 
            0x7496AAF96702E9CCULL, 0x43EFD3436860DB4CULL, 0xE92D728D26BAA9ADULL, 0xFBAA0DC498D9C83FULL, 
            0x6F52D014D4242C97ULL, 0x209F511269FE767EULL, 0xC1D326318F545006ULL, 0x8DEB5D4A7B635639ULL, 
            0xF0C37BA19D283FD9ULL, 0x9870533745A24866ULL, 0xC92ECF91FBC75787ULL, 0x98E0EFA50A2A9014ULL, 
            0xE90352AA8A607406ULL, 0x69D33F2C3973A5FFULL, 0x6A308D54BFB6ADBDULL, 0x14BB2271C2BF8A8DULL
        },
        {
            0x489D49AC95932BDAULL, 0xA6FDFFBE54802455ULL, 0x4A00E9B435C91567ULL, 0xD915A77623154C1EULL, 
            0xB11DBC98D1CFFDE4ULL, 0xB88F256B8E94E055ULL, 0xA360659A6550EABAULL, 0x724679EEB193ED08ULL, 
            0x95B64E90C7343F1AULL, 0xED418C0307191E89ULL, 0x17CDFAE265057B8BULL, 0x09689C9F19472780ULL, 
            0x78F15A9ED77D5F98ULL, 0x8178B950BD4C9103ULL, 0x9CB3D0E1B7BF8334ULL, 0x8796CD7314AC8994ULL, 
            0x7A26ACB34B5914BAULL, 0x12D3346265688D8AULL, 0x8656A0A2EE058FA2ULL, 0xC91E65C6F2BB3A5FULL, 
            0x8AE88E3B99316A01ULL, 0xFC51EC9BE407D7F2ULL, 0xC3029A2A5FCA5921ULL, 0x34C144D5F6524503ULL, 
            0xBE2C6FEBAAB56600ULL, 0x63ECEDFD8E02D670ULL, 0xC7E80A612333BE9EULL, 0x5D96E510FEF02038ULL, 
            0x645572A439B2E69BULL, 0x00BF47A719B6C2E5ULL, 0xAF0922A7AF6F3E99ULL, 0xE654FF5E4223CFEDULL
        },
        {
            0x92508393A4C3FCB0ULL, 0x8347E8AC06F7A3C7ULL, 0xDC0EDE6B42F4B895ULL, 0x5F8A89D8E34E8FA3ULL, 
            0xC8837C415B087D43ULL, 0x01F6E6C75FD6DCD6ULL, 0x8C5E4840181172D6ULL, 0xC499D6855D50A9B0ULL, 
            0x51AC85057F052163ULL, 0x9988D35BEA43C9C2ULL, 0x255D92F2F7CF6071ULL, 0x31314EEEB2953193ULL, 
            0x12170891D2138E91ULL, 0x100EF09B33E72522ULL, 0xF68C99098856E696ULL, 0x05F65313108524EDULL, 
            0x75697929B8EF5A25ULL, 0xD809702EEC507347ULL, 0x366419161AFE1B3BULL, 0x96507750D6F63792ULL, 
            0xA1FFAED77A8CAC55ULL, 0xD4D43AE02FDC5B59ULL, 0x30D6561A326181EEULL, 0xFC116F6D549C8D3AULL, 
            0xC469245DF87B7ACDULL, 0x88FC00F5FB56F25DULL, 0x6F0BCF3FA423FFDFULL, 0xF170E48DAE33E8B7ULL, 
            0x9FC752377D4AFE16ULL, 0xFCFEA460A10E5605ULL, 0x87C960FD2151CCF5ULL, 0xD01CD49D15686706ULL
        },
        {
            0xECBC4E6BB079E5FDULL, 0xE74451B8DB27B666ULL, 0xA5DAF1FDEEB4F0C0ULL, 0x07BB28DD0FDC1B3AULL, 
            0x9BEABA9C8AF69A38ULL, 0x922BAC6B260D648AULL, 0x7280F731040945FDULL, 0xA5C3C998377C2633ULL, 
            0xAE5F0795DCC673EFULL, 0xE209A1DDEFC470F9ULL, 0x255398EC0B65A5DBULL, 0xAE7005614E323C8FULL, 
            0x96971E7DAA49910FULL, 0x4F76ACF589BA1BCCULL, 0x4BE5EF34C53A1AF4ULL, 0xB0F60ABD2D92C925ULL, 
            0x6A7436744C784184ULL, 0x0B711C3F290FE79CULL, 0x222C2505F1D744DBULL, 0x51D27FA727209CD1ULL, 
            0xFFBE956F771F0EFBULL, 0x5FBFD2A557597A0AULL, 0x1EE2AD19D3FFB2CFULL, 0xD3DAF4332660D83EULL, 
            0x67A5C80DE0AC596AULL, 0x413B3636F6C4357DULL, 0x4304279A9D0D2655ULL, 0x307068DC394D3633ULL, 
            0x4CE71504585A37C5ULL, 0xC03FDA79D8DF6914ULL, 0xCF9AA8DC04F283FAULL, 0xBADC7C3878D16FD4ULL
        },
        {
            0x57BDD00037B990C8ULL, 0xF62EF6D04A13016FULL, 0x4A44C1E5E9099E78ULL, 0xF2FE91FE48FFBD5FULL, 
            0x3E57B71047E3A8D7ULL, 0xAE20583A39D31CA0ULL, 0x83E06BB090D5BC8BULL, 0x7C0F8BED5B3EF749ULL, 
            0xE9CC6F0D836329B7ULL, 0xE5B0E5F14C169851ULL, 0x79CC8A4CF2E71645ULL, 0xBA440C9EFFA9D053ULL, 
            0x170F28DB47887BB7ULL, 0xC3E9C8E0C4C2D645ULL, 0x4A576DD25515E33CULL, 0xE43D9970AAC7A833ULL, 
            0x3110E121876178F4ULL, 0xFB2A560915D48786ULL, 0xBF0863401B55A648ULL, 0x9A9302D4F1E77C38ULL, 
            0xE5C8E2392B8AA023ULL, 0xD5B8942795696D30ULL, 0x71F52174CBF64CE8ULL, 0x24D20C8351381C8FULL, 
            0xE14AE6147B703915ULL, 0x425E94B388EE2C77ULL, 0x54DB0C7CDECC235DULL, 0x11D3FEBFDEEB402FULL, 
            0x0AC2D454F2460C66ULL, 0x9C1AB6CBF81CC228ULL, 0x57244926CA765724ULL, 0xA56F48CCC6ECF9B1ULL
        }
    },
    {
        {
            0x1F9BDDA9B64AAB82ULL, 0x107627C0318A41CDULL, 0xDDB4D687341F9CBAULL, 0x72BFE36E122BC604ULL, 
            0x8FA69804F42FE95DULL, 0x74527CA5233797A6ULL, 0xF9AD5F5970A02135ULL, 0x508DD86A3D2E7DCDULL, 
            0xD78A80EBFA3D91F2ULL, 0xBAF181C7CB9C7F0DULL, 0xD852EB5F66EA0B32ULL, 0xA71BAD7EB9595416ULL, 
            0x87A9982A55A6D7BDULL, 0x8F5F7C467E20F446ULL, 0x5162210A31231310ULL, 0x33231609482F0442ULL, 
            0x96FDBA08656C6D5CULL, 0x642E391C5E14A7EBULL, 0x1A773D8E3336F550ULL, 0x337CF39BF4E853DEULL, 
            0xBC32F3828CFD170DULL, 0xFDDAD085A3EC636DULL, 0xD5248353B02BBA91ULL, 0xDD54CF33DA64BE5FULL, 
            0xFC0CFAAE64CE57F2ULL, 0x4046BABD3EDFCC29ULL, 0xBA309F8457B27E15ULL, 0x56CAF2966E0CC7EEULL, 
            0xE625FE50D76D7EF6ULL, 0xC24E81B71E56BD9AULL, 0x26509FF929D29729ULL, 0xB7895E4E9441F5A9ULL
        },
        {
            0x5976EE7C3F3DBBA5ULL, 0x0CAF52ABE97F215DULL, 0xF3E95060DFC2A00EULL, 0xDB9A2DCAD2DF6307ULL, 
            0xBFAD0BBA0D041374ULL, 0x8373EAAAAE6F75B6ULL, 0xB79DF817C95EF91BULL, 0x5F1F929F9A10C43DULL, 
            0x655165A935C7EE50ULL, 0xE95317D2DD677B0FULL, 0x15796837BD56B3FCULL, 0x51FFF116CF8694BCULL, 
            0x51DBB1C0E3196B4DULL, 0xF227531D52A655D5ULL, 0x24A198BACDF183C1ULL, 0xEF4C741DA5EF6131ULL, 
            0x6C42DC271A396F25ULL, 0x97C082347877418BULL, 0x85B3D510BCC9229BULL, 0x8FFEDF95B6405CEDULL, 
            0x8CFF0523239A3FBFULL, 0x62FAA31596B07DD4ULL, 0x76DC6531D3A66E38ULL, 0x55C802AFDBF31DD2ULL, 
            0x8A21F0086BBC4953ULL, 0xE5F3B7F895566C0FULL, 0xAFA8A515BDA5894CULL, 0xC2B3E233744740D0ULL, 
            0xF271652F510906D6ULL, 0xB8313C0CB948A09EULL, 0x3F5BF061F281C497ULL, 0x0C9E0AFCD5B9B975ULL
        },
        {
            0xADF46621C898FAA7ULL, 0x95BB3C328ACF329BULL, 0x0405E096F5ED6A0FULL, 0x0A49D6DA35EB284DULL, 
            0xD0C422176347AF0DULL, 0xAAEB0FC39FC5C24BULL, 0xEB53278E0EB79C99ULL, 0x4BA984DCC1B2A8CBULL, 
            0xF645CFFEC83681A6ULL, 0x7FCA0C903F94E40EULL, 0x004708CBC226C181ULL, 0x9C6C2DBE280E7BDDULL, 
            0xA8D59B87AF00171DULL, 0x40FD614F02BDD9BCULL, 0xBBCF416A89FCDE04ULL, 0xD2D87A71CEDFDCBDULL, 
            0xD1FAA4139763CFEFULL, 0x0E87DABB8F4CCC08ULL, 0xD5409B7072F2CF87ULL, 0x9AB0271E180D2048ULL, 
            0x4BD04FFE6DCD4F1FULL, 0x9511BC2E37096AF5ULL, 0x6B5169553260DBDFULL, 0xC9CEBE0270E9C378ULL, 
            0xB65B445DB4B51478ULL, 0xB009B38441C4A700ULL, 0xFBB98EBC9792687DULL, 0x36C56F590A6C81E2ULL, 
            0xBD2A7F6411A01D37ULL, 0xE19D3F8A05183D85ULL, 0xFAA69CDD1079BFE1ULL, 0xCE58B1836FA0793DULL
        },
        {
            0xACE7E2560CFCB49BULL, 0x0E5F82997CADB490ULL, 0x7CE2565F974DC14CULL, 0x2C7F7DEED132276EULL, 
            0xBBCA060C870B9A5CULL, 0x0F0818EAA2771B1EULL, 0x27A0492F6FC4CF9FULL, 0x7D46743ED2A6BEC4ULL, 
            0xF472C801F4B55127ULL, 0x715BD46182EEE0CFULL, 0x44B4E59CF82E6844ULL, 0x47394C28389F464EULL, 
            0x3A15FBFE1B912BEBULL, 0x92E8BC0C8E0ECCFDULL, 0xDF161B211309103AULL, 0xAA20921AA3054DA7ULL, 
            0x61430D341BE5E646ULL, 0x0C25595E67107AFCULL, 0xB28455D74B5C223AULL, 0x78B5521E68EDC5C0ULL, 
            0x3851000E6A838F53ULL, 0x57D7F46784E0A9ECULL, 0xC52E9D967E8CF4C6ULL, 0xFE6B4A3417AEDA3AULL, 
            0xC574B0CD2856E5B7ULL, 0x8B75CB0799D7E04FULL, 0xF47ACCA4CBE1B279ULL, 0x633C8E2EEAD76779ULL, 
            0x899B9625FDB4F334ULL, 0xD8D4CD9168FDDD92ULL, 0x934C0144D05F43B6ULL, 0xA75BD118C15F7F10ULL
        },
        {
            0x4E644DDEFFA06752ULL, 0x19174547EEC1447EULL, 0x4B7368A6483B388AULL, 0x9C91C9AE914EB175ULL, 
            0x36EA7BD049C35C02ULL, 0x36A2F29A489FF876ULL, 0x88D089D2C8B313B1ULL, 0xCE2FCCD5F5E7AF3EULL, 
            0x03C976BA6F045B87ULL, 0xEE8B7768FBBBD6C0ULL, 0xFB50F2305204D378ULL, 0x97D681C283CABDB0ULL, 
            0x2D555A23C64D01AAULL, 0x6B5472CA473B4E41ULL, 0x1BA93F4331E21344ULL, 0x15A038F9D13EF6E9ULL, 
            0xD9F50DF4C2FE32A1ULL, 0x532B5E0991909F00ULL, 0x28CF47F11FB2382DULL, 0xBC8596C297CC88EFULL, 
            0x5B6B07C5E0E71350ULL, 0x087C20CCCFA64626ULL, 0xD31857C4261CF36FULL, 0x5FA46D8EE7B0A4C7ULL, 
            0x9E5F477B72AAC2C0ULL, 0x73F155DFCD9A4005ULL, 0x3B0D831D28A0BD4AULL, 0x19B04FAC9BBDA4B2ULL, 
            0xEE10D7A8DBC12B85ULL, 0xBA839F41FBA7A8A8ULL, 0x2DB37858B16F79DEULL, 0x35EC061D45CCAAFDULL
        },
        {
            0x9B4BC7E5331ECF8EULL, 0x6959767FD2AAE1D7ULL, 0x6074F0BBF4EB1B0EULL, 0xE5478BB4AF9D2264ULL, 
            0xE5AFD15F9041DD67ULL, 0xB7E9CB7594B987FDULL, 0xC08A99CC347F42AFULL, 0x6B203B03E2AE858BULL, 
            0x4313A13D0B38800DULL, 0x16E23C76A85E369EULL, 0xC67AC5177C59A2C4ULL, 0x122589B98C89655DULL, 
            0x28202E39BB2D2F33ULL, 0xCD397055447DD8CFULL, 0x72042AAAC893CBB1ULL, 0x3304FEA4EEA8C72CULL, 
            0xDBD9251C1E6AC959ULL, 0xEC842F4F4F0B5201ULL, 0xB05D0FED76CA4060ULL, 0xA3C542F52E0D2A99ULL, 
            0x9F796CC992A9000DULL, 0x7DAC369B83366688ULL, 0x867D433A96F14934ULL, 0x8A1AA7110956301EULL, 
            0x1A2EC379C7DC4898ULL, 0x637335765BAC632BULL, 0x9F532A7FED34EE17ULL, 0x0D5E76F2E524A2B2ULL, 
            0x2C6B0DB9D99E7CF5ULL, 0x0322FC3938428BA1ULL, 0x5B76A3EAB1DBB866ULL, 0x99FAD6AE5E4899EBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseCConstants = {
    0x4567854F98B2CE0AULL,
    0x6B45C9040070BCEFULL,
    0x2AF5355FE79F0E4EULL,
    0x4567854F98B2CE0AULL,
    0x6B45C9040070BCEFULL,
    0x2AF5355FE79F0E4EULL,
    0xB68F553560872210ULL,
    0xB70157055662CB86ULL,
    0x1D,
    0x0A,
    0x02,
    0xCF,
    0x5F,
    0x8D,
    0x4F,
    0xCE
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseDSalts = {
    {
        {
            0x013DEF4D923DBD04ULL, 0x0F8BF1AC65CB51EAULL, 0xC11D27E307319615ULL, 0xBCB46EA41E06955CULL, 
            0xA6C607F8F743A1CCULL, 0x6F8C0063FC6A9462ULL, 0xC0B02F70D5C9A3EEULL, 0xCCC537196B490108ULL, 
            0x2170CACD5EDA9726ULL, 0xEE07E52642033001ULL, 0xCEFF8BBA3796B1D2ULL, 0x24A376F5AE0FFCD7ULL, 
            0x8EC97E573C4FC726ULL, 0x2C7CD73BDE910FC9ULL, 0xBF21441811E84AECULL, 0x478425156129DDC3ULL, 
            0xDAB4509BBD34D34BULL, 0x07D15E3DAFD97F40ULL, 0xC3F647762456754EULL, 0xFEBA3E77AA083606ULL, 
            0x77AEE084C04A50EEULL, 0x328CED39874ED916ULL, 0xAA056D10C1709CC5ULL, 0x7646D17A07D45206ULL, 
            0xC022FEEDC70C2236ULL, 0x3CC5EE5174707D3DULL, 0x4D14FB13906338FAULL, 0xB6C6899EBD677A51ULL, 
            0x0D921D19CC94B4BBULL, 0x966D27384FC00F51ULL, 0x487F93E83C730923ULL, 0x8D5F41EDC83B5B9EULL
        },
        {
            0x8DD522ADE3F4BA09ULL, 0x10B294AA1B33EE39ULL, 0xBBE2CC8B9A068AE8ULL, 0x312518148E024D0DULL, 
            0x9445191BBD14F73CULL, 0x3DF7F3B6C2FD4731ULL, 0x431C081BD2E7E8EBULL, 0xA3AD2538F6E564E6ULL, 
            0x660B3C15E128E760ULL, 0x3EA4449314EE81FDULL, 0x601CFFE8989C3B17ULL, 0xBE7472C9148D53A7ULL, 
            0xB32EE377293247E0ULL, 0xEE46A5730D39BD3FULL, 0x7D870C6F93B2C0E5ULL, 0xF088E119C6499CD3ULL, 
            0x17897A5DE420C057ULL, 0xB63608CD7FFE5B69ULL, 0x843B243A5AB3B820ULL, 0x8C9BF2F1871912E8ULL, 
            0x69732DF230FD9EE3ULL, 0x94BD2F40DFFB5E6EULL, 0xC2CDB3412103FBD4ULL, 0x33CD73A8A0CF87EAULL, 
            0x29B67976FBA020ADULL, 0x16DAFF711F56E74AULL, 0xF5AF882728E7E016ULL, 0x5426CB0A73E841EAULL, 
            0x62CEABFD77FF44AEULL, 0x6770502FC6263695ULL, 0xDD60EC0541F905F5ULL, 0xAD25D22167F7E823ULL
        },
        {
            0xEDE6076AD7DED488ULL, 0x0780294C55114732ULL, 0x0CDA2E1A28FA6FBFULL, 0x5C104453F668110CULL, 
            0x78C1E7ACE6760767ULL, 0xCEB8F0267005BA1EULL, 0x8F4697A3C36FBDAEULL, 0xF28F569A2076AFF2ULL, 
            0x0071D7C97307B08AULL, 0x1DCDFC920BCC4F31ULL, 0xB604A25BC2712357ULL, 0x4DBB91A40FF547B7ULL, 
            0x96E27DB06ADE6FF4ULL, 0x0F76B4DC70C8C020ULL, 0x317DFCC1576DAD55ULL, 0x899D345CE2C681C0ULL, 
            0x9D598C668ACF82EBULL, 0x27D6FDDA68EF746FULL, 0x15A6A5A1692E1100ULL, 0x5F032A9886C7CB38ULL, 
            0x7F4B4A33A4358140ULL, 0x3D4196AA78B14D7AULL, 0xF17173D9750CE956ULL, 0x0B09D2142BD67032ULL, 
            0x9FA4D697AA601C7AULL, 0x4E28A1BE22B44117ULL, 0xC73996D32BBB6D75ULL, 0x60D21EDE3D62ACA3ULL, 
            0x1D97BBA0F5BD057FULL, 0xF305EFC302344084ULL, 0x38D7275C69D5512CULL, 0xF9A7C7ED91710B30ULL
        },
        {
            0xB83F9FF8537A4EE1ULL, 0x6B70743DA5B35566ULL, 0x666864800716E518ULL, 0x4A529CF6BB426ED2ULL, 
            0x2F95121C0FAC78C5ULL, 0xFD5A05F28CEDA57FULL, 0x48E699CA407AB85BULL, 0x23CFFC71C586940EULL, 
            0xB12FC26DD15E4BF7ULL, 0x9EA122D2A6EB326CULL, 0xCD30EACBAA0C7B8CULL, 0xEED2E5C5D9B7F64BULL, 
            0xA73A88912B8722EBULL, 0x379D122B5C228F16ULL, 0x7FE8C843E41AF576ULL, 0x3018A230621991A5ULL, 
            0x94E58DCBD2629EE8ULL, 0x751B111660BB26C0ULL, 0x535DFC827E75C544ULL, 0xF044308CF1E85E2BULL, 
            0xC59C84867B10C696ULL, 0x3873BA4973994CB6ULL, 0xCBCD7DC0AF53EEDCULL, 0xB9FF6E5C77CA5BD0ULL, 
            0x223456BACE75824BULL, 0x75B85E268BABF230ULL, 0x45C0BA0ADB1FABB4ULL, 0x33DF13309A5F6540ULL, 
            0xE889AFF969268D2EULL, 0xB01FF1D53EFF872FULL, 0x0244CD2EB90F5A53ULL, 0xC0434A87509C5407ULL
        },
        {
            0x6484F71083F8CBB5ULL, 0xFC7F1932FBD38C3CULL, 0x7E71689EC4AB208CULL, 0x9D0263EC9C6E11BEULL, 
            0x491E17F1F14FA42FULL, 0x4E66536341910C9DULL, 0x2330A5FE0AE00B5CULL, 0x19F01CC3651461AFULL, 
            0x8C44DF24F3CF03C2ULL, 0xAB093F2BBF40D02BULL, 0x1FBB591DD2FF3501ULL, 0xFE506D7F25662AC1ULL, 
            0x246F1DBF2FBBCABBULL, 0xFEFB512BF943E5F0ULL, 0xBCC8BABA0ABBEF81ULL, 0x6135DE963ED9CC3CULL, 
            0x36A9A14F0278C4A5ULL, 0xAB061587381D7173ULL, 0x7FF5340E435EAA9EULL, 0x911B41923967B332ULL, 
            0x520A0A4F53787AB7ULL, 0x69584A53026CE771ULL, 0x89365EB909CE2D73ULL, 0xBC9EFB6CB167E0C6ULL, 
            0x1D9400A8C53CE2B8ULL, 0xCD083A4B69815EB9ULL, 0x7BB84D7E69D51E8FULL, 0xD2E047836C5A3C55ULL, 
            0x85CF3CDBAB2A4FABULL, 0x567B9B6631BAF5DEULL, 0x22C08622928DC389ULL, 0xE7E9242463269D2AULL
        },
        {
            0xF30FEA9833D2E20CULL, 0xC95800CFC691E4A5ULL, 0xCFBEC87963B3D0F9ULL, 0x92C88801964CA734ULL, 
            0x1DB7DC407F3D78ADULL, 0x7E5BFD4D4A198A66ULL, 0x3EBCB7990BCAD7CBULL, 0x87F8E0018DFEEBE1ULL, 
            0xC0F66D9EDE5915E0ULL, 0x53EC3226533825FFULL, 0xC54DFD19DD6BCD07ULL, 0xC07DC0D18D4411CDULL, 
            0x473E8A996F641AB3ULL, 0xF891926918205627ULL, 0x41229E383DBCC3E3ULL, 0x4DD6583D7AF3951BULL, 
            0x502AC736F5E163D5ULL, 0xC9D53882D6B9987BULL, 0x25B2978089D070DFULL, 0xE346C3A21B9AE052ULL, 
            0x8741A01500696C60ULL, 0x9CFF15E733D43CD6ULL, 0xC42239B4660B0E84ULL, 0xC8B3BACF38BB89A8ULL, 
            0x14B4D3A65465067EULL, 0x69413FBF3C17345FULL, 0x2A058F48466F00F6ULL, 0x68BDC34FA67B2496ULL, 
            0xA898F4EDBDDE353AULL, 0xD760A2F3A2130FBEULL, 0xB6FF14A2D245EC62ULL, 0x946073359AFBAE4CULL
        }
    },
    {
        {
            0x007B49366A71D6B4ULL, 0xD555B27876439801ULL, 0xA3070328341C1F27ULL, 0x9A1C8092ADD95C8DULL, 
            0xAC9C98B58C930D8CULL, 0x62C16F448CE3673DULL, 0x2727ECDE5114AAD2ULL, 0xF8C27D1B27F66C41ULL, 
            0x220DDDC7224E6695ULL, 0xACB667368660CC81ULL, 0xBFE91BF1F48B3AE4ULL, 0xD4B254119A724320ULL, 
            0x497AB7A70FBF090AULL, 0xE19A9D630FA63BB5ULL, 0x8DCD4660305144A2ULL, 0x67B69FC208094CF6ULL, 
            0x6BC169314E03C0E4ULL, 0xCFD6F2C17854FFB0ULL, 0xFEE7CE5965106909ULL, 0x989D2B76A54A26D9ULL, 
            0x75F2D9A1BBCD260EULL, 0x9F0880F0501F916DULL, 0x550BFFF14001EBBFULL, 0xB2D7FDA287C4D2B4ULL, 
            0x853BDE0547DF87E0ULL, 0xBF7C0D9066A3D22CULL, 0xBD55AE534EF254D6ULL, 0xCA487B5E729A005EULL, 
            0xF16F379F4FCC0E2AULL, 0xE49A51645B147757ULL, 0x7970A64ADC966E88ULL, 0x92262F865F8EFA6FULL
        },
        {
            0x62B37D6CDA43645FULL, 0xD638FD96E6F439AAULL, 0x204DC31DEB49E2C4ULL, 0xEFD9CF28D86F0C24ULL, 
            0xF258DEDB6E3D5AE2ULL, 0xA18C7FA9E53E9724ULL, 0x17FB9B0C9B2DF6F9ULL, 0x5A2A7BB3B1CBA7B0ULL, 
            0x89AFE74A7931CA76ULL, 0xE47618BEB4CF4C70ULL, 0x675B9D93EC83C558ULL, 0x3A4212710133321AULL, 
            0x10F39FB1B5F48167ULL, 0x6DA37EF0CF0F06EDULL, 0x5D0C263A9F2CAE9DULL, 0x2BC8B71AD0B97565ULL, 
            0x65934CE36EAC939EULL, 0x326C47303200B900ULL, 0x28DC8594F8688CF8ULL, 0x60B68B8B9D2EBD78ULL, 
            0xE8AF66951BC465A5ULL, 0x7BC381366FFA3893ULL, 0xD77624AC6835DA54ULL, 0x37A186E0BF189AA2ULL, 
            0x09CA98BF1E32BACEULL, 0xD69B6B195CCBCC48ULL, 0xAF1C7877C4C64D26ULL, 0x3B4BEBFD5EC008C6ULL, 
            0xA54861DAB528429DULL, 0x6799DE1767A4B4E7ULL, 0xF7B14317E137B1C3ULL, 0x66B6C79DD54DA87FULL
        },
        {
            0x93109A5F3AEFEFE3ULL, 0xD105AF77A207CAD6ULL, 0x108435D51086D526ULL, 0x0411D5C2F6A3DB27ULL, 
            0x02FE56A87C34F16AULL, 0x03E636CE71CB2B69ULL, 0xDFAAE80E6BB193FBULL, 0x123D8FCD08865CC9ULL, 
            0x2A6D4DDB4AC9C062ULL, 0x7DC118C6E7B31F3AULL, 0xF6730C2CF0E2A8C6ULL, 0x802BC66ACA839BA8ULL, 
            0x94B2757B27722BD3ULL, 0xBD1AEB2611DD2581ULL, 0x856FC338BEF126FFULL, 0xB248C2D391C92256ULL, 
            0x749DF70C71F18B24ULL, 0x1E0E6DC9BCFA849BULL, 0x8A2849702F1753CFULL, 0x9170BF19CBD529CEULL, 
            0xA159A12FE5B5F46EULL, 0xAAD42B41D7957EF6ULL, 0xB83C2399353560C7ULL, 0xB1A27F2CD9DE57D4ULL, 
            0xE534D1F4DFAFA6F4ULL, 0x946AA2F2F2CDC1CCULL, 0x4B3B89EEC6B70E57ULL, 0xFFFCFD321ED437D5ULL, 
            0x051CB8343BB230D9ULL, 0x1DEDF32E8E3A33DFULL, 0x0BD8A7DCA8D1C197ULL, 0x9A36FDC8C6842B6DULL
        },
        {
            0xEB40FD8BA19CF332ULL, 0x560E03A3323A97AEULL, 0x0C6E20A755389AF5ULL, 0xCE9F9194A3DD6A85ULL, 
            0x1859DA1A11A30435ULL, 0x58C1AD45651E5FF8ULL, 0xF727125CCCDFDC1CULL, 0xE9BDA277FC689AC1ULL, 
            0x149AA716C058421FULL, 0x86E5E31865626B07ULL, 0x462A0CC381BBA8B8ULL, 0x92DA3EC735A5A30CULL, 
            0xE1D78BF1FF4FA723ULL, 0x56C6346C5F48B4D7ULL, 0xE5A53B1E5826AEFDULL, 0x583B610301BA8019ULL, 
            0x5C1A18D427EE1443ULL, 0x3A7EAF6C5E26A5E3ULL, 0x343810C61507B31EULL, 0x35405F69073AD410ULL, 
            0x72C9477459AF1452ULL, 0x89A8F5CCB2602232ULL, 0xF51A9F9908A0E929ULL, 0x6A713AFCCC24DAF9ULL, 
            0x1E3B0EA8DE2B6F57ULL, 0xE1C95BEB231967DCULL, 0x4F88433632E48506ULL, 0x9CE491DFEEE92ABFULL, 
            0xD64DA1CB63215756ULL, 0xF2B4F4F592EACFE1ULL, 0xA62A813B02B3E698ULL, 0x4409E4AD2FCC7BDEULL
        },
        {
            0xB2462E1494919FB7ULL, 0x85D74745976D8B2BULL, 0xAB01FDE983926061ULL, 0x2C799E087FFCA238ULL, 
            0x4DC9215F06233A3DULL, 0xAFA4945DEB7833B7ULL, 0x9BFDF431DA8C0D17ULL, 0x9A7ABCAE2A99B2D0ULL, 
            0xDCDB3AA8CAE9321AULL, 0x0C3F442C9B455E5FULL, 0xFFFE2FBB7FDD6E50ULL, 0x379E42EEDF8FFC3DULL, 
            0x8F07C837DB351E51ULL, 0xB6E82E6701023645ULL, 0x5AEC6F761851926BULL, 0x8BDB9742A0A8DE4CULL, 
            0xB16B3B76305AF2F8ULL, 0x1767C4162C573B4BULL, 0xF4F7A246A698A6A1ULL, 0x15234E7172551FF5ULL, 
            0x12A2A9CFC6CD782FULL, 0xAFA70E05B88464BDULL, 0x3CAEC357C16A01EFULL, 0x3BC83E1CAC73015FULL, 
            0x86C031E730FD7341ULL, 0xFF2932017F5999CBULL, 0x9051E449B6CD85B6ULL, 0x33B83EF33C461F3CULL, 
            0xD0B741CB27296299ULL, 0x3BA386EF3F21DFD4ULL, 0xB81D7AF56B17A399ULL, 0xCEAE2EB13C948344ULL
        },
        {
            0xDB98245D40343D5BULL, 0x78A578788B12DAB5ULL, 0x381B1B13E27E9EF7ULL, 0xDD3B64965DF2C0A9ULL, 
            0x2E6C167C9A40CC75ULL, 0x5C11FAF7E23C03DEULL, 0xEBE3E9F0883A0CB9ULL, 0x2BC77F9869415567ULL, 
            0xF60C2D236F70D21FULL, 0xE0BA53FF850CD7B6ULL, 0x9F38E1A737DDC004ULL, 0x3D2A64D761F9D6FAULL, 
            0x89D220C4471DCFC0ULL, 0x8FC177430377BEBDULL, 0x791C082F5A0421F9ULL, 0x7CBF545A2CB0FA21ULL, 
            0x3D994DEB5581712AULL, 0x09F4558D861ACB70ULL, 0xA1D90AFC4C5E484FULL, 0x3ACBA75E73CAD430ULL, 
            0x8C5762D80FD2969BULL, 0x792C4AEE3047CB43ULL, 0xBF972F2826F748BEULL, 0xBB0B2807A01E574EULL, 
            0x9C91AE2DFA82D384ULL, 0xC559B9A589141782ULL, 0x5042C6ED7B5867B9ULL, 0xDA4558E60B32C506ULL, 
            0xB7A60AA084F34730ULL, 0x30700DC86E13A5FEULL, 0xE31368A869131BB6ULL, 0x0560F4F797D4B7DBULL
        }
    },
    {
        {
            0x997BD1A0543DDF52ULL, 0x72A530E5BD3D55B8ULL, 0xEE733FAB8385FC9DULL, 0x867D198E6A5479EEULL, 
            0x448F8C81F9BAE448ULL, 0x62AA002AB1B3E1F2ULL, 0x1714FEA5DA550322ULL, 0x564FC52655AC3DB3ULL, 
            0x1565DE9577C5BEF1ULL, 0x15BAC67871312A15ULL, 0x1F1DB39456B8B892ULL, 0x3ACB87C89F24A17BULL, 
            0xB063A49F560D0B72ULL, 0x242BFE7C5AA4C6E4ULL, 0x44D746CD33392CCDULL, 0xA56938C2767B27A9ULL, 
            0xCB3D66E145AC1E4CULL, 0x7F580D72EDD62C05ULL, 0x7B9F794E40EF685EULL, 0xEFE25490CE98BC99ULL, 
            0x037D17204A6CF0FEULL, 0xCEC4F36284129C85ULL, 0xAAB1A3E621232D34ULL, 0xF7CEE9F91502BD8EULL, 
            0xA7679D0D4F32E902ULL, 0xBA285551F9FFCFD6ULL, 0x16727BECF9A78615ULL, 0x55FD9684F59ACC6BULL, 
            0x36125159D34182EBULL, 0x002DD27E14BE048FULL, 0x0A62FDD83D4A1F74ULL, 0xE79F7241E62DF042ULL
        },
        {
            0x6F4DB34682D457ACULL, 0xE5074B4527F81476ULL, 0x712CC16F60C74D44ULL, 0x182E1A29D97DEBA2ULL, 
            0xE5BC10B4022EC8B9ULL, 0x59B484F95900292CULL, 0xA1A63AED4C1D53BAULL, 0x38AC05A27640B1CCULL, 
            0x830FCB9FD91144F7ULL, 0x47112BB8AE7B3A2CULL, 0x9E9BAFA7C6D4CC72ULL, 0x280B967EACDA5DCEULL, 
            0x315B4E6D46A28466ULL, 0xB687C0511EE15FC4ULL, 0x60DBC0123D1CCD93ULL, 0x59C1656DE6510BA2ULL, 
            0x0F060B1311CE124AULL, 0xC8238BC672CAB942ULL, 0xB046A668545A456AULL, 0x9C9560B8F58AAC0FULL, 
            0x0F3EE263B86D7D00ULL, 0x540D5E76D470A83DULL, 0x9A99B0F2594A78F9ULL, 0x6749AB2C81EDC36BULL, 
            0x6B18E4501D5F33E0ULL, 0x681B22B3BF52CB63ULL, 0x0C23E5EEE42CD23EULL, 0x3A25D89AF6BC76B1ULL, 
            0x59C8D129ACE15166ULL, 0x8A77EBD777FA54D6ULL, 0x13DD7C333B7CBA8CULL, 0x2E784748BA810EF1ULL
        },
        {
            0xBB5138811ADBB6A4ULL, 0xFCFE0484B1B1142BULL, 0x79FF1FA177ABCF57ULL, 0xE2037C44C34CD499ULL, 
            0x71E3F999F28FD662ULL, 0x488713ACD7BB2E76ULL, 0x18F8DF3662D5C4F8ULL, 0x00D686952DF1A29DULL, 
            0x4D1C1E83D7FBC200ULL, 0x191AE68E918C9ED6ULL, 0x686348CEC16EFDC1ULL, 0xB805791372E0E5E0ULL, 
            0xFB1A4503FAFE776FULL, 0x98D2E82EBBA518AFULL, 0xF56EE2A971CD7690ULL, 0x90822D6535CF1FE6ULL, 
            0x2E309E8D959F0EFCULL, 0x2DC0AA92D5032181ULL, 0xD25C7D748B9A1FC3ULL, 0x47EB78CB49F61256ULL, 
            0xF071745194384CA2ULL, 0x39A2641B2F2834CAULL, 0xF08AF5039A0DDAE7ULL, 0xE84E08D41460691EULL, 
            0xE985AF43E527324AULL, 0x7C128B45CAC19C01ULL, 0x10E21640ED91E4F7ULL, 0xEDBA94232C949D7FULL, 
            0xC9D3AB1A853C7A6DULL, 0x867A2E4CC938060CULL, 0xC5A263A1DEC67DF3ULL, 0x8E7850923CB0F461ULL
        },
        {
            0x3AA18A2A9EA19A0EULL, 0xD9882CCB60B8F5EFULL, 0xB9CFB908B8C8B6CAULL, 0x0653CCE107D0902DULL, 
            0x1C464C6E1639637FULL, 0xC07AB2E8435AE660ULL, 0x194566C6ED1051D6ULL, 0x4BA9C1FC59B96683ULL, 
            0x24D639946BCF0187ULL, 0x699420138BDAD714ULL, 0x4FE7CB2A6DF98567ULL, 0xA66B002B681214B4ULL, 
            0xE4FBA3F330CA7949ULL, 0xEF402227D190B077ULL, 0x273A8BB1EE33607AULL, 0x98A122A3C4FA81F6ULL, 
            0x8B0A276CE7B475A4ULL, 0x25357DF7192A3AD3ULL, 0xCB3FD9BB54AA5D9FULL, 0x82873FF5CE2C4F70ULL, 
            0xFE86E4B2520D6FBDULL, 0x298C7CEF6E6A5505ULL, 0xB87F64206F7C1209ULL, 0xA31E2891118614B3ULL, 
            0x3082C514147C7897ULL, 0x674A8EA5DEEDDB4BULL, 0x8532E6A7113D17C3ULL, 0xBE73BA54052E87CDULL, 
            0x38AA354498D685E8ULL, 0x61E39C7F4F88DD45ULL, 0xD505839C21EE15F2ULL, 0xE21634DF5E207F60ULL
        },
        {
            0x3A01A375C338C390ULL, 0xFB4D4A7C620EA250ULL, 0xC6E95E965DED0817ULL, 0x1B625A0425D93265ULL, 
            0x20FCCF1B79A7E6D4ULL, 0x23003709D74E2AAAULL, 0xFA19C52C5BDD48E6ULL, 0x0BE2E0C2748A8DCDULL, 
            0x6B33F04640A1CEDCULL, 0xC3EE944E66251FB8ULL, 0xDE3C6C86DD81A853ULL, 0xE8D82E5FF41665CCULL, 
            0xAD625823BBC2DE8CULL, 0x62FC796BFD441956ULL, 0x45E8F27E0CD66977ULL, 0x2C18915E5A23D445ULL, 
            0xC056AD0EDBC058CEULL, 0xD4B0DCBA5E4AB2A6ULL, 0xD8BBF31D1AA0AE85ULL, 0x3A59FFF993ED3BF9ULL, 
            0x320866A57E8D5DE5ULL, 0x4FE73E4E7E3A926DULL, 0x215DA9977A17FB09ULL, 0xA041C03502901107ULL, 
            0x65A3551C80E3C5CFULL, 0xB260D56CD6CEA0D9ULL, 0xC702DD7624EF77DEULL, 0xB34436A91E78C6FBULL, 
            0xE8B4F533DF1A9730ULL, 0x233B4B5815BAF408ULL, 0x71EB2953419E5342ULL, 0x5F3D96F7B86B3EB1ULL
        },
        {
            0x22FDC1F42CA9D318ULL, 0x7B1DA8E7AF6518B6ULL, 0x222B0331517C73A9ULL, 0xB36FEEA894DBA38EULL, 
            0x133DC4B489C3D8BAULL, 0x7D51B65C80321DD7ULL, 0x71DF7AE6ECFCD615ULL, 0xB044C5FBEA4D3FC5ULL, 
            0x3DCEC0F5E5A073F6ULL, 0xEA3C673DD961F126ULL, 0xE97C85E6943D037FULL, 0xAC1A70CD40AFD750ULL, 
            0x1104BC32A5A12F4FULL, 0x58B31A5490864050ULL, 0xD202F4FE763502E4ULL, 0x6A96600B323C8DAEULL, 
            0xA4EB3E0F419ACA5FULL, 0xDE3F99960732A59CULL, 0x77A2C6859BF96960ULL, 0x9A801BEC92B09E0BULL, 
            0xCFF9035FB01231ECULL, 0x20C9690226FB2142ULL, 0x5BECD5D9FEBA2A0BULL, 0xB5BF68F90EFB6D4EULL, 
            0xB2EC96D9BC2398D1ULL, 0x962C4DBFF12BAAFEULL, 0x3309CF8BA1F5B5E7ULL, 0x65E87A55E40A2780ULL, 
            0x07ACBA83B42FF779ULL, 0x2C1734F4B6368693ULL, 0x7A7727910BEB3B9FULL, 0x25BEC5D7304C08BBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseDConstants = {
    0xF9A7FE5DCD522BFAULL,
    0xB555C3B51504CBD3ULL,
    0x10657A97237572B9ULL,
    0xF9A7FE5DCD522BFAULL,
    0xB555C3B51504CBD3ULL,
    0x10657A97237572B9ULL,
    0xF38BDD4F035CA706ULL,
    0x2C0D677992230BA9ULL,
    0xAB,
    0x8C,
    0x53,
    0x83,
    0xF0,
    0xC0,
    0xE3,
    0x5F
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseESalts = {
    {
        {
            0x603BE5B073E4BA3FULL, 0x0634CD764374D45FULL, 0xC7EBF497D8CD540BULL, 0x8AA9E5F504C7B315ULL, 
            0xB7C3C446F695C1E1ULL, 0xEB36537F737A69EEULL, 0x3A9CE92DDB1C6B3FULL, 0x30CD5A9E74F2EB42ULL, 
            0xA7E9DF84A2DCD1D5ULL, 0xE6FA715A07F269E6ULL, 0x91D6C33C37726E88ULL, 0xC3195B4FE75264F6ULL, 
            0xF55FDC17DB2851DEULL, 0xD542A915ACA1F499ULL, 0x22F6D34E5CCC9D09ULL, 0xA718BBFD2C23EF25ULL, 
            0x27C1869826390C7CULL, 0x55EE85DB28633C4BULL, 0x7185AC60663DE46AULL, 0x0C8E23097DC19057ULL, 
            0x6279E681BF639F47ULL, 0x5B0BC0CD48014C2FULL, 0x5ADAF3D0A4B21356ULL, 0xE1456540C7B95E99ULL, 
            0x91E29B63B01B8A05ULL, 0x8615D1740C59BF2AULL, 0x7B815B5DA2ADBD63ULL, 0xD8F0FAAD2C207DE8ULL, 
            0x277760C836D32E42ULL, 0x37B3F421EBC68240ULL, 0x33730C8BB8A34BE5ULL, 0x3F480A24F701DEF5ULL
        },
        {
            0xB221EFBB30DD15F3ULL, 0x1B4E9DE7C4BA183BULL, 0xB3871A67180C76E1ULL, 0xEADC78AA542461F2ULL, 
            0xF30D0601FA7EFD93ULL, 0x7A0D407632432131ULL, 0xF95E82737489F04CULL, 0x2581A83FBF59133FULL, 
            0xB93A471591EC4FBFULL, 0x84B8322AE8B451F7ULL, 0x60E49F322BACC98DULL, 0x75403AF0E04192B6ULL, 
            0x260316980522FDD0ULL, 0xDCE7F1F3D40AD39DULL, 0xE524191CDF2F4C55ULL, 0x99F8349AC9440DA7ULL, 
            0x00B7F2CB51F030BFULL, 0xABF4F51CD37D87CFULL, 0x99325A3D95DBB0C6ULL, 0xA2239A53613456BAULL, 
            0x21564A84A9B671ADULL, 0xA4F4B4FCE8A82F5CULL, 0x8A046071E2A01618ULL, 0x3F392994BA0FFD72ULL, 
            0x6F6C84EC5F5C3AE7ULL, 0xF23A52E874611B41ULL, 0xA18F7C67832F4A85ULL, 0x356BE948D2118138ULL, 
            0x2F199A07E2B32CC2ULL, 0x66307559FE69C440ULL, 0x20D24D60CD6FB682ULL, 0x2376F8E54531D8D8ULL
        },
        {
            0x0775234656B86D90ULL, 0xD009AAA745483A9BULL, 0xA4E6E17E5BA0BD14ULL, 0x970056FC316652D7ULL, 
            0x75E9C0C22987D52EULL, 0x204635A5C74DD974ULL, 0xC41D752424C3F469ULL, 0xEAD88C879FEE544CULL, 
            0xE8CC32E0935C8C96ULL, 0xF40DDC2403CD6587ULL, 0x0B263C0795CEFEE8ULL, 0xDA1FD5A4C68F56A8ULL, 
            0x89EF5C18D75EB4A4ULL, 0x5A43116C9A6E4C6EULL, 0x716214637DB172EAULL, 0xCC7E339E9A438B4FULL, 
            0xFF34508F3E7E8239ULL, 0x04DA60145CAD6CA2ULL, 0xDD411E019C0C3CEAULL, 0xC575F3D73D9698F5ULL, 
            0x7B117EEE994202AEULL, 0x6FC403B6EDCF9B59ULL, 0x8A228A8F11072A7BULL, 0xA90B347E7C3AD209ULL, 
            0xDD1711DE91DE27F7ULL, 0xBC8C6025F1BEA961ULL, 0xF3F640020336682BULL, 0xFFC60F00A1C8E48CULL, 
            0xAF31C281448A4485ULL, 0x331886460C9BC91BULL, 0xBB972A3605EE5E3BULL, 0xDDC9002156256E83ULL
        },
        {
            0x5DB4DF8DD99A7617ULL, 0x47F3250AE65DD19CULL, 0xAA3F3F2CD90BDFFBULL, 0x7193BC946211240DULL, 
            0xC335D2A9E5F212E4ULL, 0xF11E6459001D05F0ULL, 0x2FC569B6BB97DD5BULL, 0x5CAE3C71645B78FCULL, 
            0x17B7B9EB11DF0367ULL, 0x851512EBC30BE24DULL, 0x3AD111CAE0B9EEF7ULL, 0xABE84275DB1ECD92ULL, 
            0x3AF94DAC2C616705ULL, 0x69159B9A836B4F98ULL, 0xDD634909F259EC78ULL, 0x846003D797533E3AULL, 
            0xD34F9EFFA6D8E2ADULL, 0xD6B8BACF514D56FBULL, 0x155620E67830D9FCULL, 0xA55599BEE327AFF5ULL, 
            0x0E997EB55790C2E7ULL, 0x01E284C41DF10D21ULL, 0x0E819D324BAB206AULL, 0x3AEF19600E0055D3ULL, 
            0xF3D66B111EC552AEULL, 0xF71DED4AAD2DD13EULL, 0x7D8A22D1C4660787ULL, 0xE19173A429D7E54AULL, 
            0x6275EED3A3DDFCD3ULL, 0x74A2F4ED72D0B689ULL, 0xCD7137FE1B7DABCEULL, 0x940B70A9F9225BBBULL
        },
        {
            0x249575520DE12AABULL, 0xE251B5C1A42770E6ULL, 0x76B1FB98E8A034FDULL, 0xD8C31E7ECBDFAC94ULL, 
            0x6D09FFBC5E5D9B1DULL, 0xAA24427163677F31ULL, 0x265A5DDD0CC5B9BBULL, 0x85EBF5F73DA0FE82ULL, 
            0x2CB0EAB21DACFB11ULL, 0x8C2C1657623A89B4ULL, 0xD7C52A65699D2641ULL, 0x9814945A0B9569D0ULL, 
            0xE9BA444B082CD52FULL, 0x725123A70949DD19ULL, 0x71E812EB99CF1524ULL, 0x9B45305C0C988035ULL, 
            0x57888E1E3F5B3F8FULL, 0x8423C56A445F6703ULL, 0x7B7B209AFD20750CULL, 0xB8A0AC7C66881B65ULL, 
            0x0E460CA143241DCDULL, 0xA515FC2963A4D7A1ULL, 0x3778C74DC848E644ULL, 0x2DDC3DE89DB023C0ULL, 
            0x128C4AA27F6DABE1ULL, 0xEA70520C4FB6F102ULL, 0xA655C05B5E4B86B8ULL, 0xC4EDE38A181EDB41ULL, 
            0xAF0DFF484E9971E8ULL, 0x475A100253B388E0ULL, 0x68B569ACFD07DBFEULL, 0xFCDB46B395CA2C59ULL
        },
        {
            0x902758627D55E3CFULL, 0x293A6CC6A6A4C574ULL, 0x573B685F55B42ADCULL, 0x6DCEAA05DC040488ULL, 
            0x4B55FD39DE6E6D46ULL, 0x2865D9CA15E2ECB3ULL, 0x0F3527BB9009C7FBULL, 0xF56F545B452FECB9ULL, 
            0x7D417C5B74194E60ULL, 0xD13880BCADCF4A78ULL, 0xCA9462ED7AE997EFULL, 0x6E1FFC7B2604AB36ULL, 
            0xF0991E1E054FEBB7ULL, 0xDC1CD22CFCB5B4D2ULL, 0x01B9DB6A70888A0FULL, 0x5E9672600F4A1728ULL, 
            0xD3A627B8CC776A22ULL, 0x803361E4D6940254ULL, 0x16BC6D54F343E235ULL, 0x4DAA69396D1F13D8ULL, 
            0xBDAA3EE4F90DF3F5ULL, 0x3F057F7CCE4E6A47ULL, 0xED2BD32D31750681ULL, 0x84A69C3B4CF408B6ULL, 
            0xBB49BD9A0FB1D95EULL, 0xE093FFD7A6DD89FEULL, 0xA0A6A0953E6A40FDULL, 0x013EBCA4EE7D29ECULL, 
            0xDB4E4E7FF24B24A6ULL, 0xC73B94A28D013C71ULL, 0xC9E07AAFDB0D871DULL, 0x18842431062F8645ULL
        }
    },
    {
        {
            0xC5D1623122F51C4FULL, 0x3F6608577672BFB1ULL, 0xB6FBF063F090FB65ULL, 0xA88145C0000CE637ULL, 
            0x921B10880BFDE686ULL, 0xB72D99CF268A5F9FULL, 0x611F52E05B6A263DULL, 0x70320C82EA0CBB2FULL, 
            0x540694ED88C33300ULL, 0x9CE3A4A334324D6EULL, 0x2B9CC05CE7DB35DEULL, 0x324C19B253DC145FULL, 
            0x43E43C70807CE290ULL, 0xA4A7B4785CE1D970ULL, 0x19436C2F03A2ACE1ULL, 0x03277189EE936521ULL, 
            0xBE37B44BD888712EULL, 0x96BA23AB7D03CFE8ULL, 0xA575D47F48436460ULL, 0xAA7FCE8F46418B9DULL, 
            0x26BDE646980CA778ULL, 0x6890FAD4412B3524ULL, 0x66E75B4C68FDBF79ULL, 0xEAA35ECBEBD67437ULL, 
            0x3D64F34E42D30AB8ULL, 0x662D5F9BC5DF7CA1ULL, 0x53AA6705E09CF1D3ULL, 0x6DE0D5FE6D0CE80DULL, 
            0x300813EAC27448FFULL, 0x8543E2E56F26868EULL, 0x28A139CE5B2EE984ULL, 0xBEE61EBE193EF077ULL
        },
        {
            0xE3201639EDAC00B3ULL, 0xD7CA59644A21F076ULL, 0xBBF824743F542A6BULL, 0x8212399DC91401ECULL, 
            0x5362B1DFC3AE3094ULL, 0xD2F93C77B182F476ULL, 0x198F261B3D8C66F6ULL, 0x1DE8BCDF179F2B7FULL, 
            0x6E4DF432F16186D7ULL, 0xF9126511C0355998ULL, 0xF7880355FBE11D69ULL, 0x62E7D746B707B2A8ULL, 
            0x53E9038F1BB5265BULL, 0x1BCCCDB485F4E4DAULL, 0x856CCE2E1C290724ULL, 0xC99E249830C04A7FULL, 
            0xC61624EF35EB7989ULL, 0xD6AA90D2E6652B50ULL, 0x847B9D3D9E37E58CULL, 0xCDB0E1C065E4A07AULL, 
            0xA3D7A3236048A323ULL, 0xC4E6E304B6E15D3DULL, 0x5FF85B3D590B3F62ULL, 0xD63656E6CA96F438ULL, 
            0x28F8D1E724A191E9ULL, 0x6AFF887FE19A7719ULL, 0x37C247426CC9FEA8ULL, 0xDF82A5F3CB874AA9ULL, 
            0x03742D39B5D98E78ULL, 0xF1938CF9651283C2ULL, 0x6E6D641E23877938ULL, 0x976B99C905185D0AULL
        },
        {
            0x8642F015AA5BEB46ULL, 0x52CEB88821713A7CULL, 0x14498142C0233ECBULL, 0x7145DCEDBE5809FAULL, 
            0x543B1DE7D670D77EULL, 0x6A64AFB920F2FFDDULL, 0x38407BA151D0B76EULL, 0xB6252D7F368D4EB1ULL, 
            0x43FF102260EEBA98ULL, 0x56C757A89B891DB8ULL, 0xA110C47930E5FAAFULL, 0xA0612B8B31B84AA8ULL, 
            0x249C57C0BFCF8B50ULL, 0x94499B6296C770E0ULL, 0xEF75A1C98073348EULL, 0xFF62A2E6D4A41949ULL, 
            0x4A193E1532C16DEFULL, 0x744B34B4DA514140ULL, 0x7DF59DA4BDE23645ULL, 0xCA7CF7D90C4490ADULL, 
            0x7F458B8823CBEDFDULL, 0x04A9333B127623B4ULL, 0xB576D5918D8B9623ULL, 0xF53E8804523CB0EFULL, 
            0xB6837298B95F3548ULL, 0xD27679E496E2BD4AULL, 0x7D2039419E240274ULL, 0xC4F44DF2DF6E248EULL, 
            0x6A69F8BDBF35F173ULL, 0xAC02BC9C332431C9ULL, 0x36479596DA1580C2ULL, 0xE8AF24A7DA0A3F26ULL
        },
        {
            0xCC41772A494FBD5BULL, 0xF475DC2418890C8CULL, 0xD743A1066D1E7400ULL, 0x7801F74F219AAEF1ULL, 
            0xC321C52DC381FCE4ULL, 0x83D4CFD7AF94C265ULL, 0x8222688B475FA627ULL, 0xB1CEAEC3312C38F1ULL, 
            0x4842389F58584749ULL, 0xE6DAD4D4E6AC41E8ULL, 0x9454C3C32A690821ULL, 0xAB0650A688352FB2ULL, 
            0xFE024E436E053A39ULL, 0x32B1EC8FBC8CBBF1ULL, 0x7CD6721FDD522E5BULL, 0xA083A7F06E5EA273ULL, 
            0x0AC79C32DB2571A9ULL, 0x5712D3FDDEF2271FULL, 0x5578EEE4E98F7F26ULL, 0xCEA2B1F728DB6F88ULL, 
            0x573DBB1F17890849ULL, 0xCE055A119514E3EDULL, 0x42B827DFB09EBFD2ULL, 0xFD29079C697D00C2ULL, 
            0x5DD10FFDD20FDB85ULL, 0x99B0EEC71BED51E7ULL, 0x206D67F68FBEF3F1ULL, 0xE815685112DD9072ULL, 
            0x5FE8EF4A63EC1CC6ULL, 0x55DBFC80FA16A8ABULL, 0xF468529170170B39ULL, 0x94EC62CE35DB7CAFULL
        },
        {
            0xDE15B78789EE2C06ULL, 0xB542B06143267911ULL, 0xA6E159FBCE0F5D1BULL, 0x75E2839CEA507E2BULL, 
            0x8F43617A65EFA03DULL, 0x9CC4483EE655B130ULL, 0x2C7628CBADA14C47ULL, 0x91CFF3046B89DA4CULL, 
            0x07DF6C4FE0860B44ULL, 0x7D3B6586B74A75A6ULL, 0x67C8F2834DD391E8ULL, 0x1D5CF9D4765CC4D2ULL, 
            0x14904165887364AEULL, 0x4DA3F77C14051446ULL, 0x539A22625D5577CFULL, 0x4386FEB1ED25879CULL, 
            0x59F92777F105E50EULL, 0x59CA09620A8B02ACULL, 0xDE2B263FE2A72BD7ULL, 0xB3BB0AF996AC20B0ULL, 
            0xAE3E0286132DD9C9ULL, 0x44213A81DD540A1CULL, 0x8F4697679BF04980ULL, 0x92C53059C8C5FFFDULL, 
            0xF8C10522883E2693ULL, 0x528D53816BA802E2ULL, 0xCE06BAFE73525F66ULL, 0x5EDCE2DBE36CA018ULL, 
            0x5DC6EFDED579FA39ULL, 0x9912BB7BB9232E95ULL, 0x1D050CFFC1F0B2D6ULL, 0xF64CF9CEB80CE08CULL
        },
        {
            0xE7E4E8E40282A375ULL, 0x651F865609260A30ULL, 0x1B9E59C6165BF53CULL, 0xC9A8723AC789DA3FULL, 
            0x9ACE4E1A81A72232ULL, 0xFE0876A5165FCBE5ULL, 0x8F687615A1D3C0DBULL, 0x1ED9D7860F059EB0ULL, 
            0x2152CA4DD0852A60ULL, 0xF88D3D95AC0A152AULL, 0xB47409F2917F8978ULL, 0x558861A0DECA8D91ULL, 
            0xB7A260A74E2655FFULL, 0xD545E9E9ECBFC518ULL, 0x679201F5C9AA9C67ULL, 0xBA285897C17F3187ULL, 
            0x4CCDA3F46CA1A691ULL, 0x89F13B1BDCAC2AEEULL, 0x85E750A76DA8EAF0ULL, 0x29C8237B1708F963ULL, 
            0x1B28E149F7B52BCFULL, 0x8D347DE0BBB7E5AFULL, 0x5D61737D0FE45CA7ULL, 0xA5027CB2AB155555ULL, 
            0x3D2CFE2F9979186FULL, 0x0C074C5A5FCC10EEULL, 0xB4DBECC1CE4436ECULL, 0x4CFC00547108ED4BULL, 
            0xC81B1BB8506CA386ULL, 0x3E6DA1D46A69AE69ULL, 0x36AD0F52C3B2381BULL, 0xB52544FE8764BCEBULL
        }
    },
    {
        {
            0x6B2200F1CF905AC0ULL, 0x86B9DE2BECFC40E7ULL, 0x478605098D0BCC2EULL, 0x3031F7257FBB141FULL, 
            0xB57D874318D104E3ULL, 0x93D30E92045FC9A5ULL, 0xE5FCB6759AC894F7ULL, 0x1FB8C98029F69BF3ULL, 
            0x775B2CCC81EB7E65ULL, 0x2BFF495F1BF3415BULL, 0xAE08F921EB1053ACULL, 0x44F3995EBCE60F4DULL, 
            0xD95B0D361F48BEFAULL, 0xC76726BC0BF4E1C0ULL, 0x7288CF587C599E01ULL, 0x3F2AC793C8AF15A7ULL, 
            0x198CC7A6DA03EB4EULL, 0x75E56954B2C7EC17ULL, 0x406BE2DA7F6C48FBULL, 0x7F6137AEAD9810D0ULL, 
            0x331DC22BE61E5EA2ULL, 0x1792ADF7EA58D7ECULL, 0x8FE82B3D72B6F984ULL, 0xC5D8D8614A8B89CFULL, 
            0x56B19FD20678D627ULL, 0x5F6DD3EC5CD1DD30ULL, 0x13AB67D9F3D8BF00ULL, 0xBC1D588F888A6C10ULL, 
            0x561DC29EF5833891ULL, 0xA69A206B6FB042DDULL, 0x4AB28C331FA06CA2ULL, 0x62706DFA53F0059EULL
        },
        {
            0xAFE5AB45BBA80F94ULL, 0x88CA1BEE39A17A42ULL, 0x2C443B544E1314ACULL, 0x4BDB54FD5FC271FFULL, 
            0x4900FEDCAC1205A1ULL, 0x2F520F54A7725FFDULL, 0x56B33341EE2A89EFULL, 0xD86DB0C3833F4E22ULL, 
            0x299F4523E6F7F297ULL, 0x49F43535F6E5199EULL, 0x4EF45E0528D95350ULL, 0xFE94BD4784B327CDULL, 
            0xC71C59464A804ABCULL, 0x94F44B58368D7438ULL, 0xA556031298BBE513ULL, 0x191848608FC177F4ULL, 
            0xFB6892C90179FC55ULL, 0x5511B44A0F189F3EULL, 0x25037DD3D9B98424ULL, 0x011382AE0809A47EULL, 
            0xC11C8D96BD0B6CBDULL, 0x3CF6DFBDF7396763ULL, 0xF608A9229032FF03ULL, 0x25D833A3865184A7ULL, 
            0x1B98718584F3D71BULL, 0xC2C7D845AE251EC1ULL, 0x6312BCD255DDB056ULL, 0x1D10F2E0A343B906ULL, 
            0xD68F4430303A61EDULL, 0x977117FA105370F5ULL, 0x6D0394316F1A75BDULL, 0xC75D31B2DF5F0736ULL
        },
        {
            0x34AE2BB6110F19BBULL, 0x3DB0E1A33F40D577ULL, 0xE09B1795F9DD8BADULL, 0x10BE1096E4401E4CULL, 
            0x3121DFB1AA317204ULL, 0x9D50DFAFA01697FFULL, 0xE134DBB88B10049FULL, 0xEE178A1C5F0D4D8DULL, 
            0x5B20A5DF7C24E9B4ULL, 0x5F69300CF8FF2AF7ULL, 0x7B707F9C948177E5ULL, 0x11256DD081FC75E9ULL, 
            0xAA8361B2EC01C3AFULL, 0x6EBE59C0DF5F5202ULL, 0xABBE633B4F9DD695ULL, 0xBA961FF0E2C9CFA0ULL, 
            0x821976502BF79054ULL, 0x8E2A044833A0E5A6ULL, 0x15C5E43013619348ULL, 0xC777BC40E4AF6BCBULL, 
            0xC440B006E8455A3DULL, 0x6BC5A5E819DE4F7DULL, 0x4BA2F098E0B109E5ULL, 0x8589AE451E5161CDULL, 
            0xC48E4C96908CED7DULL, 0x32E8FF32FB714880ULL, 0xAED1E510ECBCA2E4ULL, 0x12D70E38EC0C366FULL, 
            0xDDE19A89A9EE897EULL, 0x27046BD4B75CB357ULL, 0xF655A428152C0E08ULL, 0xB557225C97B99729ULL
        },
        {
            0xA44217209B1D40D3ULL, 0xFF22C423B529290BULL, 0x5BC77A579F915076ULL, 0xAD74C0305F735970ULL, 
            0xE097F2E3B161890CULL, 0xA931B104E95D50F8ULL, 0x8791FE6E069C97D3ULL, 0x04159D9E22F361B6ULL, 
            0xB7C8CCC0398FEAFDULL, 0xDC0AA09507C8EDEEULL, 0x13B8827240C1BC6AULL, 0xDE66FCE618BC3E6BULL, 
            0xBC08DE2C3D882112ULL, 0x13D6A4E46E4A8E3CULL, 0xC76403E30B339FF2ULL, 0x2262853EA405DC5BULL, 
            0x4D27A530532C75BDULL, 0x00302937379AF22FULL, 0x2AF0D5D84988EB61ULL, 0x7B6450A5FD9E0139ULL, 
            0xA04BECAC6C77B536ULL, 0x2E8C3FD082A4A79CULL, 0x1CDFBBD0094E52D5ULL, 0xDCAE14BE53281CF4ULL, 
            0xF86289E8DCC85006ULL, 0x1925B884355F487FULL, 0xECAE48E7FAF6E81FULL, 0x2AF51B325B5DE0C9ULL, 
            0x5A98EC64BD6BC1F4ULL, 0xB836C5A73FA6224CULL, 0xDFC2BA5FC3F7364DULL, 0xBC3D02799AA60EB0ULL
        },
        {
            0x1334C42A1D6EEBC2ULL, 0xF79872C9DC312277ULL, 0x54D32DA05D9525B3ULL, 0xB1F5E72FAC9A593AULL, 
            0xFB92E89E46523765ULL, 0xCA136E7B707CC720ULL, 0xA17843BD09EA42CDULL, 0x1D914B79D4C8F397ULL, 
            0xED81AB9BAD1DC282ULL, 0x5BB0984A0B22D574ULL, 0x853C6300DCE2EA95ULL, 0x080FBF0D19435690ULL, 
            0xD7688DC57CB14194ULL, 0xC42792A1EC7CF21BULL, 0xA757BC30944E8415ULL, 0x1990CECEA9B2C5E5ULL, 
            0x8686FF03B41BC56CULL, 0x95EF7DC8874959D8ULL, 0x12640B33CF754A3DULL, 0xA7743CC8E1EFD800ULL, 
            0xAD1974307ED07BFCULL, 0x0913DC357AF1C04BULL, 0xED31F482AB9C32B4ULL, 0x5ADC9C61CD146747ULL, 
            0x1FC73B95E34962FCULL, 0x6F9E6269C4F2658EULL, 0x582F0403CFDADF40ULL, 0xD4E94EE1BCAFE595ULL, 
            0x5D05280C0DFE4ACDULL, 0xBAE0A1EBB64C6F9BULL, 0xC34EF1A7688E3141ULL, 0x014A84735D120B5DULL
        },
        {
            0x17F139B6259A7811ULL, 0x8B347496F3F97A9DULL, 0xE0061369D55B5816ULL, 0xF64C9A1858B4834CULL, 
            0xC89F6DE98DDC9814ULL, 0x31F0597AFD19FDD8ULL, 0x09537E9A549A117FULL, 0x9BB36CCCB9BB53C8ULL, 
            0x8D18BCFF74B5C37EULL, 0x710E66552DC8B856ULL, 0x0E97B644CAA5723CULL, 0x3C29E9A42EA74F03ULL, 
            0x898F93F3C3B4DEACULL, 0x5DE892872D56760DULL, 0xC623BAA7DE0B25F8ULL, 0x0F119A4A45F8A1C1ULL, 
            0x75EF590E810B965BULL, 0x5DC5124505F03A1FULL, 0x3D76360C3F906138ULL, 0x40033FEBE3A535DBULL, 
            0x522D9A67EBE1ED77ULL, 0xCF24565AB4C9C764ULL, 0xB17A473566C4532CULL, 0x49528E1742C17DCEULL, 
            0xAE5F84E6C099A9C4ULL, 0x141919A517FFECCAULL, 0x8102E58C0EAF1CD9ULL, 0x5CE810840C018BA9ULL, 
            0x4181DF6BF67807D3ULL, 0x0B6B722FD048755CULL, 0x953447318136B678ULL, 0x408BE6ED8794DE80ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseEConstants = {
    0xD49EE83227C5AA66ULL,
    0x858F9F4F3D124BE1ULL,
    0xDD74412E39ED6A12ULL,
    0xD49EE83227C5AA66ULL,
    0x858F9F4F3D124BE1ULL,
    0xDD74412E39ED6A12ULL,
    0x4B62014B24BC4449ULL,
    0x0F658D0105A2A35BULL,
    0x45,
    0xF2,
    0x60,
    0x61,
    0x06,
    0x9A,
    0x9D,
    0x14
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseFSalts = {
    {
        {
            0xB515082A8DA2DC55ULL, 0x149CE73C9E4B85B5ULL, 0x73B326892C49B766ULL, 0x49E6C78DB3A13196ULL, 
            0x70EE3C5C51AA06F5ULL, 0x525179C1DC898880ULL, 0xF21B6A82942F5A11ULL, 0x2F917C076D35ECF6ULL, 
            0xF958967DC615385DULL, 0x47EF6A48B1133ED8ULL, 0xA94671F3A1A1332EULL, 0x371B0ACD405336EAULL, 
            0x46831BA10A15B198ULL, 0xD292E9E287A490BFULL, 0xA2BE4F7369247BA9ULL, 0xDFE74E5585F82EBCULL, 
            0x9B50BD57E323FDC8ULL, 0xB3443C54E0665AC1ULL, 0xDD9849B9BAB2E19EULL, 0xB9A5037245FC4ADFULL, 
            0xF947B0561B1E25A3ULL, 0x100AB003B92F8639ULL, 0x1DE7ADCDFF257922ULL, 0xE41588C49FE91C5FULL, 
            0x9425C017A098F379ULL, 0xF39F7EBFA56F76BBULL, 0xE72B3DA7C4EAC28FULL, 0x9092B30B2A4B52C5ULL, 
            0x7FDB8049BBE88FECULL, 0xE9F9DAD961574AAEULL, 0x81A609800F20F25BULL, 0x8E80CB1A2533D064ULL
        },
        {
            0xD15D69CB8B513077ULL, 0x6F416E21DCF20E89ULL, 0xC07E289568A1775DULL, 0xCA77BA4DB3E27E9DULL, 
            0x044E6176119584A8ULL, 0xD8C4CF056D1B11E7ULL, 0x43ADBA6155F1C65EULL, 0xFA3669173C11DDA5ULL, 
            0x3A6ACB35135BDCEBULL, 0x9436754729804188ULL, 0x1DF6A741AF760ACDULL, 0x0D30F28F52A2F7C4ULL, 
            0x57B2A3F9E9FC7EBBULL, 0xF280F63E23C789D3ULL, 0xE0761509CCF86211ULL, 0x661ACB7FD465A3A1ULL, 
            0x1DF5B58CCA8F49F8ULL, 0xBBEEADAB036BEBFBULL, 0x2ED44B21512B8D54ULL, 0x441487818E232CA3ULL, 
            0xD55B64537295AA17ULL, 0x16FC33999539705EULL, 0x45AD71E50818450FULL, 0x32D274F3153D2C31ULL, 
            0xC96DDF3162841D55ULL, 0x190416A873C4F71FULL, 0x067F333E8027CD28ULL, 0x44226F821FD6501DULL, 
            0xFF34BF4922A469A2ULL, 0xDA5C1C450E329C67ULL, 0x769433BB6C02F841ULL, 0xBA450CC03318F65FULL
        },
        {
            0x2939A3840AAC7D6BULL, 0x284A1BFCAFA38652ULL, 0x041880DC13EDB1DAULL, 0x6BE2EF6FE0FC79F3ULL, 
            0x95BF2E3F73B805EFULL, 0xE83B9EB6551D0293ULL, 0x4FA1E69E9C959D7CULL, 0xE9BA5090F4ED9B30ULL, 
            0x1197BFC3295CA204ULL, 0xBA30D23F5293ED41ULL, 0x4035385EA692D38DULL, 0xEF6FFC7754EC0627ULL, 
            0x8C9FB723C9D6F9CBULL, 0x25C19973E38C0081ULL, 0x05CFCD89DE88CF0FULL, 0x300572E7B566C2ECULL, 
            0x60FB1C1E34E22485ULL, 0x594B736854EE0392ULL, 0x8D27BB98311918C4ULL, 0x5426F1A286B15523ULL, 
            0xBBECE7A3F4A8378CULL, 0x221921E8D44CE817ULL, 0xC284BEF4E8A61973ULL, 0x5F2E7C1086954448ULL, 
            0x59B94724096C301DULL, 0x4CF8D5E150165109ULL, 0x5FA4E4BF0FD3AC19ULL, 0x773AFF55D6A0424AULL, 
            0xD2CDFAE39BA551F5ULL, 0x9905C06C7A1C2778ULL, 0xED91CE87B545AD35ULL, 0xF3564B9508C877BAULL
        },
        {
            0xA28FB789EAD5ADDDULL, 0x3037A03833F7284AULL, 0x2F740E6602B9E8B9ULL, 0xA1F4C9EE1F416698ULL, 
            0xAE93A6CC08725589ULL, 0x036A30BF70A7FECDULL, 0x4927F553C18533F5ULL, 0x99AA9AEBCF9FA3B0ULL, 
            0xD838BCDD9E73179BULL, 0x59979DFD510BBEE5ULL, 0xF3EE465A29F50BF3ULL, 0x20D4B7FB5F22CEE5ULL, 
            0x6ABE0444DAE34A99ULL, 0xFE7F68F390C45576ULL, 0xCA991F4D4342A791ULL, 0x09D3B0ED6F2DE922ULL, 
            0x4AC8D33610A2EE13ULL, 0xBB5A8B66F7E17587ULL, 0x3950E3ED695BEED7ULL, 0x0DDBE11794F96AAFULL, 
            0xA992C7ECE3CD51D5ULL, 0x096A52CB349671C4ULL, 0x942A069D3A7D84DEULL, 0x04C296CA98A2E31DULL, 
            0xAE681AC487358871ULL, 0xB69A2A650FF4366CULL, 0xADB3A3475501EFF8ULL, 0x0E323F5B75ED3F49ULL, 
            0x8CC1E4A1A93753E5ULL, 0xC5516DB907F71D07ULL, 0xB62F6E8C8A71D76FULL, 0xFD410CF66F64A5F6ULL
        },
        {
            0xDD28B7A334A32C75ULL, 0x41C7455B2C0B346CULL, 0x15A96C9438E2D3D6ULL, 0x1EF0CBDE7A03E1BDULL, 
            0x26D79D13BC29D9D7ULL, 0xA73819B134A15FE2ULL, 0xADFD8D8A2A572956ULL, 0x91425D22FAAB50CFULL, 
            0x28F6B850172FDCC9ULL, 0xC5FD0057442BACA3ULL, 0xC0217DDA34CAF7A5ULL, 0xFA9F543089F05A7FULL, 
            0x27D9E32369D891A0ULL, 0x2C8DEB13E9D56F7FULL, 0xA40546C5E2A4B365ULL, 0xF6C4EDA93B5FD502ULL, 
            0x275A79BD9A010656ULL, 0x6BE39332B4CF134CULL, 0x67480FF44430CE64ULL, 0x4997F7A324A902B6ULL, 
            0x224DCF3532AF86E7ULL, 0xC4BE7C169A42A558ULL, 0x5421A13CFF14198AULL, 0x82D3ADBD391EA7CEULL, 
            0x1531B53ABC681696ULL, 0xF968F6A23948BEFFULL, 0x6402863F62B92691ULL, 0xEAEC93E5E95058D3ULL, 
            0x19EB74EEBB5E06E3ULL, 0xD92B609E118E08AFULL, 0xC6EF9B5231951E5BULL, 0x8F0ED9BA23188850ULL
        },
        {
            0x55F44CC0D1E0F283ULL, 0xE5ED46C26485B34FULL, 0x5AE50CA24913A591ULL, 0x489BD90C718B4B20ULL, 
            0x737032122BE16206ULL, 0x38381BE1F025BCAFULL, 0x76C6B5999A6BBD3EULL, 0x95D6335D351270FCULL, 
            0xA2DF89213219EA8BULL, 0xF441713FC0593094ULL, 0x0183E75AEBF09BA4ULL, 0xE3E601E0D00DEC8CULL, 
            0xD00E0839A7F06E13ULL, 0xCCFD8C738C04540DULL, 0x23F3F490D9A76AB4ULL, 0xA364CE5ACDD8872EULL, 
            0x8E3BBB2D3D2F8EB2ULL, 0x4A80F26A3E9E8B4DULL, 0x9C5642CCCA8BDDD9ULL, 0x7A41D2D2F5AD6D5FULL, 
            0x70843329F2E759C7ULL, 0x93FE8A1407E02F0FULL, 0xAD85C132CC844A7FULL, 0x78E0416728FC4639ULL, 
            0x3747D8D5562D4381ULL, 0xBBB55136CDFF3BAEULL, 0xA9D4E8EE0DB009D4ULL, 0x137B487FF359C20BULL, 
            0xF66F14744A46F9F9ULL, 0x54799968A78D9BAEULL, 0xF35E7330FC77EF43ULL, 0x2B7EB4EF5B2CCDF2ULL
        }
    },
    {
        {
            0x6DF1760B64DB5ABFULL, 0x3EBCBBAB2E6C88D9ULL, 0x61F996C80EE9042BULL, 0x9CB3369B02455291ULL, 
            0x810A9DCAAF3B6AC2ULL, 0xAE1F65276D443033ULL, 0x728201F81F790F7EULL, 0xA3E83DD4667F3D38ULL, 
            0xE72E13D5987F8DDEULL, 0xAD1787E764D31263ULL, 0x1A32CCD126537E76ULL, 0x5A2660F8514FD5A9ULL, 
            0x28AA90223C54A0B7ULL, 0x50146E9FF1D9D68AULL, 0x202A2063F7012BBDULL, 0x60BBCD23DEE2DAE3ULL, 
            0x9D975AD51CBB2601ULL, 0x45FB69E5519A539CULL, 0x51FB2041FED99989ULL, 0x967783FCE1593FCCULL, 
            0x035044413E6486FDULL, 0xCA8A0DB76083C70CULL, 0xB6B64841BC0FBF6AULL, 0x6A5C98F5E62B2CEBULL, 
            0xD393857AB3C74884ULL, 0x3961F45FAB74F507ULL, 0x33AAFB1EB61EB1F3ULL, 0xF98160CEB1B2ABD2ULL, 
            0x9A7B10D2199737C4ULL, 0xCF1BA5A94D157316ULL, 0x02FBB31E43982D31ULL, 0x592ECE774FD8587AULL
        },
        {
            0xBAA518AB8E7C68EBULL, 0x78CC08CE45BFCF00ULL, 0x5A9D8502929EC695ULL, 0xB4AB7AAA1A5CC106ULL, 
            0x74644DF2DE207E34ULL, 0x5B23A13F903695ADULL, 0x6E76209CBA33DDE1ULL, 0x2B08DC780F19D4F3ULL, 
            0x5495FB0CB841D5B2ULL, 0xCC7408BD693AE111ULL, 0xA8AB952BF4EA50DAULL, 0x27B273B0FC9BC44FULL, 
            0x6A72035FCB728957ULL, 0xE028CE1410988C8CULL, 0x31D24E47FDF0BF5CULL, 0x4C29A4D169D61AD6ULL, 
            0xFE5992FEDAB12BE6ULL, 0xEFB6E72ECE4B1971ULL, 0x67574E2A69502F91ULL, 0xFCA4CD1BB5F12921ULL, 
            0x4E68873D204172CCULL, 0xD43C8056AA43049AULL, 0x616C9F75728E8BF8ULL, 0x893873FCA305351BULL, 
            0x8EA9D0C4449035BBULL, 0x28649EE5CDEBFE0BULL, 0x884D3AFC8442AABAULL, 0x3004A289832A7FFDULL, 
            0x017CBA97D65FF247ULL, 0x0D9DAAC21F46C19AULL, 0x1BC4BF8345F717C9ULL, 0x320CA9B1C7575C91ULL
        },
        {
            0x43F8737FFF98C719ULL, 0xE6D11F6E2C7E1F54ULL, 0x0B36E1C4151C6FCBULL, 0x9121499FC95AFBEBULL, 
            0x6F350D80F21E74CDULL, 0x3F068DC7426D8164ULL, 0x60FE953949E471F7ULL, 0x375F144256E67431ULL, 
            0x61F86BE13D22CEC2ULL, 0x0267792B9922C2F9ULL, 0x02519E4172A09407ULL, 0x68DB7BFC7EC85979ULL, 
            0xC62DE311B4AF6A20ULL, 0x8EE10DCF7CE62C2DULL, 0xE2AC498AC37BB43FULL, 0x69370B68BBA8A282ULL, 
            0x4EA9664C44416904ULL, 0x6C3EED62F21B7C01ULL, 0x3E7507419301B279ULL, 0x193D2F09FF369970ULL, 
            0xBD4567B531E50699ULL, 0x99684FC7E66174D4ULL, 0x6395E2E569EA0A5CULL, 0x72BC3F665E4D5FFAULL, 
            0x851E4F3B255C600FULL, 0xBEC73B491C081025ULL, 0x655A337CE9ECFA02ULL, 0x80185A5880536486ULL, 
            0x22AAD5A29C797F6DULL, 0xC4E06D321C584589ULL, 0xE2245BC98A2A91CCULL, 0x03CCD399760D3B17ULL
        },
        {
            0x9502502CD5BE35D8ULL, 0x435746ED3E44A5DFULL, 0x88552DE344388BB2ULL, 0x2CAC93AA93646049ULL, 
            0x0F663833413566EAULL, 0x590B5393BB130AC3ULL, 0x1C695178AD0DA6E3ULL, 0xD297835600E31109ULL, 
            0x21A8287E61A89D4FULL, 0xC6F6EE81699788B7ULL, 0x1B3AA900DEB70DD3ULL, 0x99EBF50362A02AF5ULL, 
            0x6FE7139B2F5AE69AULL, 0xD534F367A5AFC73FULL, 0xC9E210FA44616FDBULL, 0x5AAB83596B0C3DCBULL, 
            0x764254EF876ACBB1ULL, 0xAF4C7139E9EBDA42ULL, 0xD9B4547C21734DE5ULL, 0x65D797968F7416BDULL, 
            0x673A9390903382B7ULL, 0xB69BC262119B4CCDULL, 0x64076AA0DC7C039AULL, 0xE9DABDA64DAADFD0ULL, 
            0x0BDCFB0305D73E2DULL, 0xB2FA21EF93C258D7ULL, 0x97D81F776A087B9BULL, 0x286D2E938227A9A0ULL, 
            0x1B7D888B38353AEAULL, 0xEC716425B34915EEULL, 0x58F604D87CC37D82ULL, 0xAF183887EE831C57ULL
        },
        {
            0xDFE7598E93E33136ULL, 0x1D3F650D033BCB18ULL, 0xCE92BF21E9794622ULL, 0xE7A9B87ED00E648BULL, 
            0x46AC65A28291596FULL, 0x43480439441681D1ULL, 0x8C1480E6D308BE06ULL, 0xF1187B55EA3DE804ULL, 
            0x9006D8D199EE822BULL, 0x23BBA21AA6A5C0ACULL, 0x332D9DC92AEAF9EFULL, 0xE3063678BDE5BAD6ULL, 
            0xB302E91B10D512F4ULL, 0x3EA98B6854F36AC3ULL, 0xFF9B2DE9916DDACEULL, 0x930A4D44FAF50A1DULL, 
            0xAD17B619356BF016ULL, 0x00A02FDF4871AE0CULL, 0x25C64A765BB170A1ULL, 0xE59E567039FF1E59ULL, 
            0x3C4CCBF82EFB1DEBULL, 0xEA94D17ED035E774ULL, 0xBE42495F4BBD0C2BULL, 0xC6125AEAADC3C0A8ULL, 
            0x3F1B46C8BE5E6D38ULL, 0xD74E48DAB6885A99ULL, 0xAE0B409F29E8F5C0ULL, 0x82396FA2004B143FULL, 
            0xD5CF302EA7FDC4A7ULL, 0xBFAAF2C3D680A09BULL, 0x3A01A4CBE1D0F246ULL, 0x3FD8288D4D24B033ULL
        },
        {
            0xD33CFAA8DC384D58ULL, 0x9168F3DF3B7B4610ULL, 0x72D080724AB2779CULL, 0x9E723064A0FB9971ULL, 
            0x0AEA70077A238CB2ULL, 0x2EA1033098377628ULL, 0x6566B3F5AD4EA389ULL, 0xF69698DC97D6B169ULL, 
            0xB81615C3227E21F4ULL, 0x768E458460E4E74DULL, 0x47465BD2ECC75EF5ULL, 0x6562500CFAA646E5ULL, 
            0x4B8732A07E1B5481ULL, 0xF3B2FD86E6381854ULL, 0x072BEE8CFD67B142ULL, 0x4B0F9495D212E190ULL, 
            0x3E44FFA9F65F64D9ULL, 0x1916743AA265669AULL, 0x4DAF38428968B020ULL, 0xF4FD5EF3FD2D9823ULL, 
            0x210E1562573F0B0BULL, 0xB410088DBBF36502ULL, 0x4284CB0A0595CA56ULL, 0xE4D735FBB459E5A2ULL, 
            0xFE2E29D6775EA51FULL, 0x078E73177E5AE83EULL, 0x18CD1E91D546392FULL, 0x8FF8A7762F062C45ULL, 
            0x8636A3659B3AB02FULL, 0xD32B593AC938ED7DULL, 0xC438E046294110A0ULL, 0xBA9302A21260B077ULL
        }
    },
    {
        {
            0x17BC3721F4D1DDE0ULL, 0x7FBF433D5BC83513ULL, 0x600F8B2049A14D52ULL, 0x51D8EAE96F0EDDA6ULL, 
            0x40129C4942FF5E60ULL, 0x5F68716DEE41D20DULL, 0x21093ADFA3C7020BULL, 0x6B8EF25D2DDFC1EEULL, 
            0x6677414F44E7EFCCULL, 0xCF85F4B78D04AE2AULL, 0x28F006E915521069ULL, 0xEF0309CB0CC9D7A5ULL, 
            0xDB7885634A4A7635ULL, 0x38647B0A95F63490ULL, 0xD159286E36FA6471ULL, 0x030FA2C6EEBF3C46ULL, 
            0xAF6B3500C86F0F45ULL, 0x73DFEC5BF231C129ULL, 0x4D52DD055CE9BA07ULL, 0xC936B4197B080702ULL, 
            0x4FC712990F75ED20ULL, 0x9924421E1414E73DULL, 0xF08792E37D8978A3ULL, 0x750AD48FEA9D6EBEULL, 
            0x66C6CC286B505D32ULL, 0x1A23267778FB8A2DULL, 0x8AE3ECBEC4CCF369ULL, 0x3E14954B94E21D7CULL, 
            0x74273E22CEAB6913ULL, 0x203F59FEB504FC0AULL, 0x95608445336DE538ULL, 0xA10FEC96778018DCULL
        },
        {
            0x740FD9DE4A5F2C64ULL, 0x335EA3B05767B4BAULL, 0x94805F7F5A52C75CULL, 0x67C842286B4B8F9EULL, 
            0x4A201795A7834A2FULL, 0xBA61562A3E8B1D34ULL, 0x0597DF3E15F5DA2CULL, 0xA0097BC70F2F023BULL, 
            0x0E5613CD1C2429D4ULL, 0x37802EB2C0C790D2ULL, 0x0EC8A890C56F098EULL, 0xF8BBB8DEA90BCFEBULL, 
            0x3E63E04D190F0620ULL, 0xED68D8749E904897ULL, 0x6E2961F87AD6095BULL, 0x90F467FD4DF16CCFULL, 
            0xB8A3E10EFD7A5D0AULL, 0xEF90DAD34AF7A92DULL, 0xEFDE4CE564C91122ULL, 0x6136C3F9979BD429ULL, 
            0xF3DE9468DFC660D1ULL, 0x4BF218D0440C64A9ULL, 0xB0BA30973E810E6FULL, 0x54DA57BAA2513FA4ULL, 
            0x43F0117531E28A88ULL, 0x7E4C38A21E9D7462ULL, 0xBEA9EC8F98646CC4ULL, 0x98BB8028BC79F459ULL, 
            0xF4BA46917473917FULL, 0xDF532CE52F9E88FAULL, 0x3375EE6CEA1ED73AULL, 0x2DEBCFC2ABF21265ULL
        },
        {
            0x703399B302F5BD95ULL, 0xCD8AF1172B6FB659ULL, 0x03271C3494C18DB7ULL, 0xBC119E48217C7B87ULL, 
            0x8FB33A6138743E83ULL, 0x229213AD4413AF88ULL, 0x7A4725FC7CEC2350ULL, 0xFB077C99B6368C11ULL, 
            0x8ABC871FBAC80D72ULL, 0xC35C1F5E262988C5ULL, 0x00AA8E4176AE56BCULL, 0xD2EF86ACA782B9F3ULL, 
            0x7971CFEC4A8F8C0CULL, 0x366AA2E013B05B2EULL, 0x5BDEFBD37FF13B82ULL, 0x59ED55477F871C06ULL, 
            0x489B4D6D8044A30DULL, 0x7FFE7B9D18902E8AULL, 0x1B6EFF11C860E437ULL, 0x4C7CE0724150C1DEULL, 
            0x7F934EBCFEC94D6EULL, 0x295A8C365414A410ULL, 0x0828178840D2D85DULL, 0x4714A5ED1B7E53AAULL, 
            0xC4BF261A9C87202DULL, 0xF8DC18F9BDE00592ULL, 0xBBAE4A72A5DE8CBBULL, 0xF263313D48426179ULL, 
            0xB4209AF77959E90EULL, 0xFB26BAB29A91FD99ULL, 0x5FB169335F56342BULL, 0x21E26FFC3ADA306FULL
        },
        {
            0x3FEB881F46E8A23BULL, 0x9EFA924941812CE3ULL, 0xEA7B596AB1011E75ULL, 0x87FFBF5A62F1F944ULL, 
            0x20A7BA9D420602D8ULL, 0x589ECCF98A7A26B1ULL, 0x30BB14567B4636A1ULL, 0x68FABC6E8823BC47ULL, 
            0xE8CCE3E6F66D1D52ULL, 0x19D3E3C6623B8CC7ULL, 0x22000B01494553C1ULL, 0x320647F6D74FDF3AULL, 
            0x2446DDE0C94DD5F6ULL, 0x62F12AF98F0D2E20ULL, 0x4255BCAC4E5EC8B5ULL, 0x1343B076A00BF1CAULL, 
            0x4242AF8798DB913EULL, 0xD8C2B8AFE46290F4ULL, 0xC722551DB5DFA969ULL, 0xF2B3BAC143534171ULL, 
            0xAA905E67297D6E3DULL, 0xCD7E11674CD2ABA5ULL, 0x0ADB928986258218ULL, 0x88548436904AE087ULL, 
            0x2C7C953B40B9E0EBULL, 0x2CCA9A0BE915D31AULL, 0x9344D23872CE96FAULL, 0x9CAB57C32B01B5ABULL, 
            0xE09268659AA70A23ULL, 0x87088C29B00CCAF1ULL, 0x3BC8FC2E7709B896ULL, 0xB658FB13F63CD3DAULL
        },
        {
            0x0D297C9FBE64F7EEULL, 0x9A506B22D63E3ED7ULL, 0x10BD3C665ACA7E17ULL, 0xC43E5CC3B11C0BB4ULL, 
            0xF9924449D80BB2DEULL, 0x7ECC95BFE8CAE774ULL, 0x65054720EA2DE442ULL, 0xCA411F662FF32A01ULL, 
            0x932C4C9958E3FDF9ULL, 0x7D86B57C58E09B7AULL, 0x6727BEEAC7DD46A5ULL, 0x80B6F6DBBCC91568ULL, 
            0x59C7947A1C7CF4B7ULL, 0xFB1BF85FE31D86DDULL, 0xDF8D42EEAF484416ULL, 0x1F9DD176C9C7282DULL, 
            0xA470532D70DD6B1FULL, 0x844570A6026DC2B8ULL, 0x8F57D4B1889E72CEULL, 0x495D6BFD1C1A953DULL, 
            0xEBC63DCB044F19BAULL, 0xAD2214CDA7894571ULL, 0x6DE8E2AFFDF15698ULL, 0x610CF3AF40A838D2ULL, 
            0xDF65DE942D9B7A8DULL, 0x687A0B4BB05DB1D0ULL, 0x168BD5A70BB5E1A5ULL, 0x1A335CB61F0B881CULL, 
            0xA878E5E7D7E27576ULL, 0x791A1E45A9691FC2ULL, 0xB5E7FB8086E84913ULL, 0xED8593CE3E698AF6ULL
        },
        {
            0xCE4CF025D5E242A0ULL, 0x5583E1AC8F0D2F69ULL, 0xEDD16D524A570E52ULL, 0x4D76806B682EF894ULL, 
            0x262ECC6372435A44ULL, 0xE8083F99CD15C099ULL, 0x06E86D6B3034A9A6ULL, 0x2DCC6478462D7711ULL, 
            0xD9EEFDD4E5D22792ULL, 0xAD9DD127CDB6A7D3ULL, 0xD69E44168937CB95ULL, 0x7A234BD6A224EAF0ULL, 
            0xC15FB1B00CB02044ULL, 0xEBEDB7CD0C7B6300ULL, 0x2BB35352625C9E88ULL, 0xAF2CE6ECD829F249ULL, 
            0xC528FC76909F001EULL, 0x1F28007773AD97DEULL, 0x526D0C9628BE53FAULL, 0xE774C4AE87AB83A0ULL, 
            0x0C4D734940B7EFADULL, 0x48B28A49B05248C1ULL, 0xF8E62F9795A4C3B7ULL, 0xC30EDBEA1A71661BULL, 
            0x1C64016CA6F32BF9ULL, 0x35EF2871F61BD564ULL, 0x2CD9901947CBA7F9ULL, 0xC3081FC25128055CULL, 
            0xDACC69D45DEAE111ULL, 0xCA6B5BB2146A6587ULL, 0x74C6F3AF8477F5A2ULL, 0x3286AA1BFF82CBDCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseFConstants = {
    0x223F79B381A5B22EULL,
    0xDFF05A062799616AULL,
    0x18C055859110F3C3ULL,
    0x223F79B381A5B22EULL,
    0xDFF05A062799616AULL,
    0x18C055859110F3C3ULL,
    0xFBFC2F0370DBDE9FULL,
    0xD64EF307F2249A0AULL,
    0x5C,
    0xF5,
    0x1F,
    0x72,
    0x5B,
    0x4E,
    0xDC,
    0xAA
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseGSalts = {
    {
        {
            0x68FA1CDCCED8637EULL, 0x523662982F843366ULL, 0x46D6164B842BDBE3ULL, 0x61D95F2178A8ABB8ULL, 
            0x2E266033EAC590CDULL, 0xAE7D47BBAFC9C5CAULL, 0xD865FABAC8DE487AULL, 0x588CF1E92FA2215EULL, 
            0x95FD5413ED13EAF2ULL, 0x81BCEED923475215ULL, 0xD43E391E8149A5F0ULL, 0x79D6BFD674132CD4ULL, 
            0xB3F6A309CFB7810CULL, 0x7361AF98ECDFA591ULL, 0xDC5C23DFDB7ADEEDULL, 0x30FD84A8C4142520ULL, 
            0x4C723D25E37AAE96ULL, 0x199E10592E33F4E5ULL, 0x62CF086BA76BAB67ULL, 0xA5BC86CA3E81B8F8ULL, 
            0x5082F6101C5E1450ULL, 0x9020D7745DBC8DBAULL, 0xC766961D27D4CBF0ULL, 0x5CBF199BCB971B79ULL, 
            0x7720302C32963076ULL, 0xD356631970129DF7ULL, 0x23AE607F836079F3ULL, 0x9225245A90028542ULL, 
            0x877682AD239C9A7EULL, 0x168371C4C8DEE9CAULL, 0xE3B0E7EDF89588FEULL, 0xDF807DA048C0CFF1ULL
        },
        {
            0x113E999E6C6F74CFULL, 0xA63533998B84C8B7ULL, 0x1F3D2F1F8AD16F65ULL, 0xB0EA321953D65320ULL, 
            0x96FC4148BE97DC47ULL, 0x5D5A0C64C089AFFEULL, 0x48A311D8C1D79A59ULL, 0x18A034C88405B7DFULL, 
            0x0EDE8CB59C7D1C70ULL, 0xF1470B095BA6A57EULL, 0x9953D39942E4C5B0ULL, 0xAB5ECFB30EFF3C96ULL, 
            0x102D7D667249F710ULL, 0xA47DD7690AA00A79ULL, 0xBD01C9F16186DA67ULL, 0x8DFF34F384EB7276ULL, 
            0x451FD2119D24AD75ULL, 0x8BC623691760CEE8ULL, 0x105710A79D874D69ULL, 0x8CC2865AE5A3DA97ULL, 
            0x2A387E9559C47EA1ULL, 0x8DC0AE483622FCF4ULL, 0xB7A28C71EEE1348BULL, 0x20C0BE61A067E7DDULL, 
            0xBF8FFE07E40F9521ULL, 0x67A4D165725727D7ULL, 0x51DE445F6474DCEDULL, 0x4D9C342D060F54D1ULL, 
            0xE3440FF3AC9F81EDULL, 0x199D6D77392D0110ULL, 0xD297DB52029F7D33ULL, 0xC7217EED5FB5FE2FULL
        },
        {
            0x58A911C2CDE171E1ULL, 0xD6EFA80E3AAAA4D1ULL, 0xE0C2088BFF26CD31ULL, 0x9313CDD10324FD25ULL, 
            0x48E3F130C7971EE4ULL, 0x2A918367589B5BE0ULL, 0x327B04D0AD9B7D05ULL, 0xBCC9B8FE5E63EE66ULL, 
            0x2C13ACDE27250967ULL, 0x4BF786B371D43045ULL, 0x004D504C402515D0ULL, 0x3914AAA865D66875ULL, 
            0x993F8E6607EBFEA8ULL, 0x1BCEFDA255ECD290ULL, 0x9509E7F153A16992ULL, 0x49873960786874A4ULL, 
            0x8FDDEE0FB53CE0E0ULL, 0x8D3FD9825A1183E2ULL, 0x70C6F0075E21D746ULL, 0x121DD7A30FEAB9F3ULL, 
            0x06A05EB3EBC7AA8CULL, 0x44D31CAA745EC4F1ULL, 0x8ECE396FF8EEEC85ULL, 0xCD702B9E9D9DEF09ULL, 
            0x1AB8933D4E81E64CULL, 0x743A5BEAB32D47FCULL, 0xA6042AB4DA6BF510ULL, 0xBE376114DB372842ULL, 
            0xA5C84002F5D46014ULL, 0xDE226BD34BA18AE3ULL, 0xD67E258E6AA4187FULL, 0x160FC741698AD55CULL
        },
        {
            0x1BA52539E41AC746ULL, 0x9F5CD5FCD50C413BULL, 0x601100036782E967ULL, 0x83CA7AE7B9FC0F19ULL, 
            0xAAC77EDFD22FE78EULL, 0x95D5BBEDFDFE8E2DULL, 0x4681D962E231B657ULL, 0xBCAB71488BE5E9A5ULL, 
            0xA4D729B0FD616B9DULL, 0x7D688679C5A651E4ULL, 0x5AF61C4C22AEF65BULL, 0xAE06186097326C57ULL, 
            0xCC967E4235008B34ULL, 0xFEF1BA3EE54E0B22ULL, 0x203BC3FE4F27EA3FULL, 0xF42808C25A7A6DE2ULL, 
            0x466C519CC0831CB9ULL, 0xF985FA8C710D844DULL, 0xB6956CA3A782784BULL, 0x398B3376C315A60BULL, 
            0xD8A2702CAFF09887ULL, 0x92E2EA4A5E30F227ULL, 0x476AA351B99F1C00ULL, 0x83528561D7E219EBULL, 
            0x072AB3E68E49EE63ULL, 0x34AD101F2FE1EA1BULL, 0x5F6157F7026B891BULL, 0xCF983B4CC6C23A70ULL, 
            0xE113F9F4F56CF449ULL, 0xADF3A3473D5735CFULL, 0x93D60F6923170375ULL, 0xE7868F75DD66F32EULL
        },
        {
            0x3A9B8B968CBDD885ULL, 0x084DE51E11FCF8CFULL, 0xC7B75B8531652B96ULL, 0x675546AA349D5F8EULL, 
            0xA151216DFC126C77ULL, 0x2664C143C412C1FFULL, 0xBF9E43769AD0ECB2ULL, 0xB4CBB6D1D5652427ULL, 
            0x7FD99647010D396AULL, 0x54161732EFE897B0ULL, 0x51E91552E87BC7BBULL, 0x7B3B84CA50C5B0DCULL, 
            0x2D766D6F938A072CULL, 0x86798A1CF0ED5E81ULL, 0x7BBFFD777D67E01AULL, 0xACF85FE897673206ULL, 
            0x0AB21D73A00E6D41ULL, 0xA0CFB6D918D0D446ULL, 0xC06CD31CCFE1C9FAULL, 0x4E22C68DF4878EB1ULL, 
            0xAEF324460101CA0CULL, 0x654C152D4BBADAE2ULL, 0xC02C565BA6BE8A60ULL, 0xB9D798291C29A505ULL, 
            0x646250DA40D2390AULL, 0xD26E437DF4C16D7BULL, 0x0F94FFF7564BDED5ULL, 0x31B3642891C1E0AFULL, 
            0xB8C1A5653E1743AAULL, 0x66688F7F2D992240ULL, 0xD6E811C81E437865ULL, 0xDB8069767DFFF93CULL
        },
        {
            0x019969B13CEF53DEULL, 0xCE09CE9BABE2382CULL, 0x00AA989D62811BCCULL, 0x4A3C6C15F65706C0ULL, 
            0x9CB2710E26B5AB26ULL, 0xEC1C278CA6D38073ULL, 0xB9B7FBBDAA6035C2ULL, 0xBC2BC43EF5F8A6AFULL, 
            0x2D3EAA3E060E2868ULL, 0x6FAB9158C42DD3DFULL, 0x5298E3B1240440C6ULL, 0x7FBC9E7F48FA4BC9ULL, 
            0x47C6E05AD94A22C2ULL, 0x540B5D9BD6C71945ULL, 0xE3A534E0DC05931DULL, 0xD5B09DB4D1E4F733ULL, 
            0x73F86BFD137EC1DEULL, 0x225772CB385756B3ULL, 0xAE51DA9880C711E2ULL, 0x1D92FFC689612BDDULL, 
            0x48E1486032DE8EECULL, 0xD9253B268A231574ULL, 0xC7E5C1CFB86A2693ULL, 0xDED22243590D9DE9ULL, 
            0x932F05A8BACF7E59ULL, 0x41F4ED7FD06DDEACULL, 0x75B58EC326D185C6ULL, 0x607FC7414A8A60F2ULL, 
            0x44C7B3D40BACF451ULL, 0x6F20C06C353242AAULL, 0x3C3890CD43008117ULL, 0x9B25EDD9D9EEB4D4ULL
        }
    },
    {
        {
            0x8E421A674451A17AULL, 0x6F1BBE9DD98A93C5ULL, 0xA452C36B0E917A76ULL, 0x1BCE1A19380D837DULL, 
            0x46F7A0A82486A5BEULL, 0x78E07B0011099508ULL, 0xABC744F9B7F46F99ULL, 0x822CCE62DE7EB333ULL, 
            0x50ABDA80CCDD72A8ULL, 0xB0D25B7EA86E6BB6ULL, 0xD0714F478760FA5BULL, 0xC8ADD4067E76A342ULL, 
            0x00102304A83C6E5BULL, 0xF27FBEC9BEBD894CULL, 0x7CE200A7A3E0BED6ULL, 0x9489EF8F2160C3CDULL, 
            0x7CA2DD5254E144E4ULL, 0xD6911F1B4B1FF232ULL, 0x8DC877ED413E92DBULL, 0x7432BE3C15DC8497ULL, 
            0x8CCBE0B9C6D68859ULL, 0xDBF62BF86D24C36CULL, 0x766082010D341119ULL, 0x665AC34A48D960D5ULL, 
            0xF90243718E44BB4CULL, 0x84759F389E00D86DULL, 0x2D4FAE77FADA6E68ULL, 0x308E9516A0986FD8ULL, 
            0x7607A14F691A0C2DULL, 0xE0F306E2C68A8EB3ULL, 0xDC2001BF9C911D12ULL, 0xAAC6146756469D98ULL
        },
        {
            0xE5BF1CC64CFC3EFBULL, 0x6AC49548C5509D07ULL, 0x5249A581C90C299DULL, 0xCB27358746AAA213ULL, 
            0x2EBA47DBC123247CULL, 0x3ABAF8A31E2B9E8AULL, 0xD26CAB7A046578D6ULL, 0x070F2249A00FD044ULL, 
            0xF9A063B90953E60EULL, 0x9B36180B528B64E6ULL, 0x86585C071E1FE0B9ULL, 0x0F97FFA4BC261CB2ULL, 
            0x86F12B07417D876DULL, 0x7AB38FB2907424F9ULL, 0x54FC9A28936E3FB4ULL, 0x16031FCA9AFB9FC4ULL, 
            0xE7FD0DA1837EE82FULL, 0x08B002C07B09B319ULL, 0xEF04567ED74EC496ULL, 0x769ED41AE44DA9BCULL, 
            0x385EFEE7E7B34A3FULL, 0x1CD057BAB3F1E950ULL, 0xA9BE278D84AF5B62ULL, 0xA764B1329CFD43E5ULL, 
            0x5C1B5DE389A905D2ULL, 0x995BF85F30EBC1BDULL, 0x3540907D6288C25BULL, 0x4B58EF4CA564E8CEULL, 
            0x380531AB7634CF26ULL, 0xA6D95FFE8D992CF0ULL, 0xA2A9E0FADED7F526ULL, 0x99574294F43A0090ULL
        },
        {
            0x2577B109BDA32373ULL, 0x7802311F34E3619CULL, 0x6C74C655344234C2ULL, 0x218CA2FDADB3552DULL, 
            0x1586DDB0B1782136ULL, 0xC3E4F539D04A2F2AULL, 0xB61DD883DBF6D637ULL, 0x5778D00F7BE2C2B3ULL, 
            0x962FD319EAC40E4CULL, 0xA90356942F562D17ULL, 0xE8EB44FDAC526359ULL, 0xDC4B709810329825ULL, 
            0xC6F747FD3337B9C7ULL, 0x9412E5BBBFE49A71ULL, 0xADC4EE0032CC486FULL, 0xB770CCC4DD848BAFULL, 
            0x46A3599AAD861B29ULL, 0xFDB5C10ADB22B111ULL, 0x27B6449736CC3E44ULL, 0x813E591F12877105ULL, 
            0x7664828F2C73B659ULL, 0x0A96D09F0FEFD448ULL, 0x80512D3F43AE5901ULL, 0xE95CF5875DBDEE54ULL, 
            0x6293B575B1A05927ULL, 0xD7BA89DEF30F58E9ULL, 0x223CF721E56E1ABEULL, 0x5A665FF26E5E8AAAULL, 
            0xBEFBACCEDD63020DULL, 0x241792A705CDE54CULL, 0x29A2297B79466D9BULL, 0x8B7430BE12E802D3ULL
        },
        {
            0xC2DA63FD2CC10AFEULL, 0xCF8236017EE6DA2EULL, 0x185D029A7A223AE3ULL, 0x1E92033EFDAA12B7ULL, 
            0xB76522D2FFB666EDULL, 0x97B2C793610F7F2BULL, 0xF68DCB4DE47BC698ULL, 0x5D2CD3A0A6E923F6ULL, 
            0xD7C3B348F6DEC112ULL, 0xBC5274A07F957BE6ULL, 0xB703E357C179F918ULL, 0x7DB2EABDC1C8D8ADULL, 
            0xF72C92426CA6CED5ULL, 0x308443198EC8B664ULL, 0x2E7AC78A840CBDACULL, 0x0862363AC4EFB429ULL, 
            0xD6E70D76D712CEA6ULL, 0x6C4F14CC21C426F4ULL, 0xA43016F734B07C9BULL, 0xF71396B64772E91EULL, 
            0x18292735B720A003ULL, 0x08950583402DCDE9ULL, 0x14755179AE93B132ULL, 0x165687BBF295380BULL, 
            0x2A938E0DB1A7F1EFULL, 0x9FD08ECB45FAC19CULL, 0xC4D577E6452903FAULL, 0xB1ECAED9BA461735ULL, 
            0x1D0E152EB6D6EAC6ULL, 0x7476D2042AB1FE9CULL, 0x324F4CA4C55FC3C3ULL, 0xE94D5F8123348158ULL
        },
        {
            0x5700E758E8F3476BULL, 0x4DCA81D1A8F32152ULL, 0x533ABDC886D0C062ULL, 0x0733EFEB46AFF804ULL, 
            0x65CB7551DF6F5658ULL, 0x73584EA0CBB8F77CULL, 0x2A86D382C678E014ULL, 0xBB8E24DD665E9DFEULL, 
            0x6C56658E8E8FC790ULL, 0x107075A58ED89A77ULL, 0x0B15C526F9A58089ULL, 0x8DA159D296156293ULL, 
            0x88667399FB2F6732ULL, 0xB7A4F3C15AE08C66ULL, 0x5F1BDBBE1E67B8E1ULL, 0x9F173B97265331CDULL, 
            0x5315DA4161BB745EULL, 0xA6E4E6369A4F40CEULL, 0x43D583DE7275BEEFULL, 0x071716F3228544D4ULL, 
            0xCCB90351A0E8B33BULL, 0x3E8819F15FFC89B9ULL, 0x506BEA349DD2D4A9ULL, 0xC8B757077F0CD0CCULL, 
            0xD8709D5898DCCF52ULL, 0x00FBEC77815AE956ULL, 0xF89674F375BC7C1FULL, 0xC27BB155975F5A57ULL, 
            0x2469AD763A34B48FULL, 0xCCE055C736369EBFULL, 0x30C7C940CBC8E580ULL, 0x1AF063EA651BEE5BULL
        },
        {
            0x4D9E549478D1D494ULL, 0x35D3CB5183587F57ULL, 0x839EE66766D2121DULL, 0x6D7F0F1429D73248ULL, 
            0xFC6843A93C69D3BAULL, 0xA12015268C1CB090ULL, 0xD9E5B275D95E18DAULL, 0x45255A7A1A19A927ULL, 
            0xDCFB779E68E69E59ULL, 0xACC79CC283D7915EULL, 0xC33E605629CAA37EULL, 0x502717854E941834ULL, 
            0x60F65AF93F40216AULL, 0xBAA6F40844CA236EULL, 0xC101207511AF553AULL, 0x0E9E868DC48E4CB7ULL, 
            0xE95DB1C557C8D7F4ULL, 0x5A5ABFF20A0EB4ACULL, 0x85F20601D835D1C9ULL, 0xD57CDB6A41BFA199ULL, 
            0x266334C18E3B8B84ULL, 0x979DC03F202CB59EULL, 0x1AD3AF2982F151D6ULL, 0xF379674962607140ULL, 
            0x877958527D2ECE0DULL, 0x9FB08B76DE1A09CBULL, 0xE9B0E2164226B737ULL, 0x83580F28FE6CD5D8ULL, 
            0x6A728742F82CD3D5ULL, 0xE5D78D7FAF744AE7ULL, 0x6109DD896DCE815AULL, 0x833E0057D8F632E2ULL
        }
    },
    {
        {
            0x17A8BC7F906B56ECULL, 0xDF1967DAC623D1E6ULL, 0x7272749476CEAD47ULL, 0x15B313C4C1C26C90ULL, 
            0x03A5E7066812DAF2ULL, 0x829083485854B065ULL, 0x531AC2F635F44B3BULL, 0x9FE8B60087B35F66ULL, 
            0x9759DC8BA1D9A849ULL, 0x80CC7B36CC42A956ULL, 0xE34E7EC02ED96B1BULL, 0xC6330EEF329C57E9ULL, 
            0xF2C6BE7A1EC6FBCEULL, 0xCD4FBC4086F812E2ULL, 0xB090B0EB5059CA8FULL, 0x346FBA316E37E84BULL, 
            0xC85213F7AF661AA0ULL, 0x92CE0325FB0B6547ULL, 0x96CD6C4B72387D30ULL, 0xBCF4CE2F62426065ULL, 
            0xA4FC2A864B03FF20ULL, 0xB61CF4D8C2E40981ULL, 0xEB2A064276C08CEBULL, 0xD612636CF529DA4AULL, 
            0xC965B242792BD3A9ULL, 0x9A9BB855664112C9ULL, 0xF8AE922D893DBB01ULL, 0x08E355E0E1DB0007ULL, 
            0x28C121BDC2CEA506ULL, 0x1DFE92DDD66E4759ULL, 0x8C3B4AADA1892143ULL, 0x4FA9076A40FD733CULL
        },
        {
            0xD06D0A9A4A718F30ULL, 0xBCB7BC3BD801CCEEULL, 0x40FD9245320090E6ULL, 0x8F84CD5A4D1A00BDULL, 
            0x27E65E32C335A045ULL, 0xCDF25A0FA86C4506ULL, 0xD6042FF01DC1FA03ULL, 0xF36BA8135A059E15ULL, 
            0x24597C84C19025A9ULL, 0x66871398AE57AEBEULL, 0x52C36C9C3B846398ULL, 0x9E82C09C9085DEB3ULL, 
            0xEC0563A01C4E9A32ULL, 0x64AD66849F4C64EDULL, 0xDCA24F0F5CFF94A5ULL, 0xAB751A8AC65DF551ULL, 
            0x48A782BDE853CC3EULL, 0xAB6E831F50DB5AF4ULL, 0x67B4F315C3651058ULL, 0xE11D4AAB29956884ULL, 
            0xE618380DA841D335ULL, 0xB9455EA4485CCFF6ULL, 0xA5CABA1F4D05576FULL, 0x55EE0C30E042333CULL, 
            0xCB40D06F3623F963ULL, 0x3178D3763CA3A3EDULL, 0xBCE46C38C3475C92ULL, 0xBEC24C026728FB4AULL, 
            0x3C951DBA9E092B23ULL, 0x37FA553298BDE946ULL, 0x66098EE6F23A0891ULL, 0x44E5A6CB442D2102ULL
        },
        {
            0xD482E2ACC8B8D321ULL, 0x8F9CE80CF3FF7525ULL, 0xCDEA1D7E8261DFBEULL, 0x25B7E3029FCC7588ULL, 
            0xAD17FCA730DAEDECULL, 0xE783E711DACB6F50ULL, 0x24A22F7684D556CAULL, 0x45DB8385446C968EULL, 
            0xDF5D7200AB133512ULL, 0x35332B643C44B068ULL, 0x753B64F66D1DC11AULL, 0x8CAFF93A103D5B13ULL, 
            0xC8787A117D605CBCULL, 0x6941D8C75904A0E9ULL, 0x09C3840D1CB36890ULL, 0x1E1E0A137DA48FD1ULL, 
            0x72DAE73780255F08ULL, 0xA171D5E2D654CBDBULL, 0xD556953137CB3C35ULL, 0x81F921ACAE12CF3CULL, 
            0x0180859236EA5EE3ULL, 0x57D90689F05368E1ULL, 0x98BAA044F6B3919CULL, 0x7DBB69FAAA0E3A68ULL, 
            0x3A15910B7FDC4DA9ULL, 0x0F5A1A40382E2228ULL, 0xF2712A62EB0B31B3ULL, 0x3A521A29CE540EC4ULL, 
            0xC9EF18E3E9458668ULL, 0xB49271F0C1D4668DULL, 0x76DB0D288E6D86AEULL, 0xA6270BA1E84DD3C8ULL
        },
        {
            0x2525CEB67F411238ULL, 0xF2C50A13A07C1E33ULL, 0x7ED802DAFD78C7C8ULL, 0x7747622FFF9153B8ULL, 
            0x457A3705D6CD33E8ULL, 0xA322B1D0D0E0186FULL, 0xE78F8FA3E31236C5ULL, 0x5566906297CB5054ULL, 
            0x125425CF9F10A899ULL, 0x34F045A00BD50809ULL, 0x6986F0FE407D5D3CULL, 0x915D06FE5A40B0D6ULL, 
            0xB5C9755468EF573EULL, 0xF3CA2B2B9FC5A94CULL, 0x1DD0A7070772C8D2ULL, 0x23D7DF6EA302331AULL, 
            0x39F9CC56D6F18B4BULL, 0x1525184E0A54C581ULL, 0xC36E9CA731BC2971ULL, 0xC2BB6F908D24A348ULL, 
            0x44906FDFA6897464ULL, 0x853A55F9F6C6DFB9ULL, 0x2EF5BCF4AFA8455FULL, 0x055C4D70A0A5121FULL, 
            0x134E523E7F464442ULL, 0xE789423EA5F8AD98ULL, 0xF9FEEFE8EC982F4BULL, 0xAB6CDF956F8F1612ULL, 
            0xD4343C1FFD3BBE1CULL, 0x0E3C13967C5B46F2ULL, 0xCEDE2368341AAA0FULL, 0xAEF92A8AB48EB871ULL
        },
        {
            0xA0A2382ACB792DABULL, 0x43CC0E90E84A0FCAULL, 0xED464157984B60D7ULL, 0x31CFB5CBE7C79D77ULL, 
            0x4DFADEFDD0775231ULL, 0xDACACE6D31D94BE6ULL, 0x726E8BE1084A1666ULL, 0xEB0412CC09802535ULL, 
            0x07BDCE75E0069426ULL, 0x10E4D040DB336CB0ULL, 0x193A9675243480A1ULL, 0x78C78DA91602ABADULL, 
            0xCF32F454598FA888ULL, 0x701D94B297048216ULL, 0xAB3917C101F9DC24ULL, 0xEE06AEB16DA291CEULL, 
            0xFFAF55E51111DC1CULL, 0x2F6E8C7D2A1A4622ULL, 0xC10AA204978CB8FEULL, 0xA9C0B3DF0F2591DBULL, 
            0xCA64C7673C5DDC25ULL, 0xBA30CB99A96DDE6AULL, 0xC3BD8E984CAF1E3CULL, 0x4E010211739E06BBULL, 
            0xB7379231AB0EE7DBULL, 0xBADC319CAFA42B19ULL, 0x4B6D71D8305403D1ULL, 0x81555E34583A2C04ULL, 
            0x1EC9E97AB57F8562ULL, 0x13F64B2C4510ED26ULL, 0x8509B4A1DE64390EULL, 0xBF256F8209B3AFEEULL
        },
        {
            0x4310BF91D34F8245ULL, 0xB9F7E72E02BCBFA0ULL, 0x2355C042456A509FULL, 0x8F86299A42D2BEC0ULL, 
            0x051954DF9A84E486ULL, 0x8E130167322B808FULL, 0xA45F4BB9963BF8EEULL, 0x0B5AC2E94AC5B5F4ULL, 
            0xFE94C02278DD8F97ULL, 0x6195C0FE6FAA85F3ULL, 0x3AFF14CC66D741CAULL, 0x37EF87943C29B816ULL, 
            0x90DBD8E3AC29A34CULL, 0x52494E3728F37DFAULL, 0x3252C2AFF809AA9FULL, 0x247B63A0DE1EC5A7ULL, 
            0x33CC5BA888E23C7AULL, 0xB31E435C160DFB95ULL, 0x1CE139502FB6790AULL, 0xD14F4ABDDF5BD6B2ULL, 
            0x8E819B534B3E0870ULL, 0x7B42638DCFEEDC99ULL, 0xF1A5C0D3CCAC9F1DULL, 0xF98409CA74149D06ULL, 
            0xA592ECBF0368D406ULL, 0x4ED25E6FBC064E7FULL, 0xD1F4CF0DE3C90041ULL, 0xA1B8E69214EE856CULL, 
            0x77EBA25507CAE5C4ULL, 0xB305EDE06B9A6A14ULL, 0x1F7E359AF1811DB7ULL, 0xD8E260905BD9354CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseGConstants = {
    0x4BE1DAE598D84975ULL,
    0x54C271DEE0EA206CULL,
    0x1BE3466E561F31EFULL,
    0x4BE1DAE598D84975ULL,
    0x54C271DEE0EA206CULL,
    0x1BE3466E561F31EFULL,
    0x9E8BAE86ADB308B5ULL,
    0xBF48BA7CAD630E69ULL,
    0x85,
    0xF7,
    0x57,
    0xC2,
    0x02,
    0xBE,
    0x47,
    0x3B
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseHSalts = {
    {
        {
            0x36A30E36BE126976ULL, 0x4B3369FAE167A12EULL, 0x9C809872AFDE58F7ULL, 0x66FE300848A140DBULL, 
            0xBA91FFE4644C6433ULL, 0xC6AAF9E256D04FCDULL, 0x74C15D3C3FBF0101ULL, 0x43270EC3C3408FABULL, 
            0x7166A10252F41BE4ULL, 0xB90EF7D1CFE43BBBULL, 0x3435996223E4DB13ULL, 0x9C358FB9B699C56BULL, 
            0x959C51D51D42E494ULL, 0xBD9C75DECCC57D2BULL, 0x5C077DF3E19CC6BEULL, 0xEC5D81A1ED50416FULL, 
            0x60826989CD1DD77CULL, 0x412FC5C002BF4AACULL, 0x1905645CD1436B93ULL, 0x2CF55903A3CB4E15ULL, 
            0xF3AC3328549C1087ULL, 0xFC946718A4A5482BULL, 0xF533105D7DD8DC78ULL, 0xA161A0A21FFF2BDCULL, 
            0x11F450CE9BE7DBC3ULL, 0x3F2B809F0C1BB728ULL, 0xEA0400A49C086D4AULL, 0xAC1CCC9BFFF0AD9FULL, 
            0x2DF4B3798632BFDFULL, 0xBF2037EFFB9294FFULL, 0xE9785D4590567C79ULL, 0x097E22EE304FABC9ULL
        },
        {
            0x502AD11278E98786ULL, 0x5DDF3798E94C2FF2ULL, 0x2D39A13B58FC8077ULL, 0xFB08B3A079ACE8E5ULL, 
            0x578E1F120F156C08ULL, 0x6239CFC392437D2FULL, 0xDA141D66E5AF1D3FULL, 0xDA03F10C7BD77E94ULL, 
            0xB4BFCC1073F771BBULL, 0x65D5405C0B5577FFULL, 0xFE36E8690BE46629ULL, 0x995CEE91A1CEAA4DULL, 
            0xC5FAF8D9002900C7ULL, 0xDF57EA824D461869ULL, 0xA66EFCEE5E18C0F7ULL, 0xCCC5EFD3851AFCECULL, 
            0xF43AF007C2D22D5FULL, 0x4CA2B156F2739E52ULL, 0x053DD59495B97993ULL, 0xF3ED99967DD27EAAULL, 
            0xFB01A6FDF84C273DULL, 0x441BAB2D1D4F707AULL, 0x74CB1122717044EBULL, 0xCBF2190A1DD67C86ULL, 
            0x10553D5B2B83FEA7ULL, 0x9AE67992B111F0C2ULL, 0x0B4A91C350A28ACFULL, 0xF0692F5599776E3CULL, 
            0x2D6E86D125E4C570ULL, 0xA27CFCB3631BCBCFULL, 0x6E5DDA8652B4EBB0ULL, 0xE30B4745CC496D51ULL
        },
        {
            0x6043C60F876CBF2CULL, 0xE26CD9800BDD3EC4ULL, 0x76777B0675BD7B15ULL, 0x60A084080DB422A0ULL, 
            0xF55D08FA814DA26FULL, 0xD6664E80A8C730A9ULL, 0x728D61C2FBA348F5ULL, 0xA430103F5AE98E57ULL, 
            0x79E8980A09923A11ULL, 0xD85DBD92803FF8C4ULL, 0x628FB1D8F71A3AC8ULL, 0x64DACCE51407F591ULL, 
            0xC412846840426C5FULL, 0x9C0ACF6C13F059BDULL, 0xF1D0CE36EED3BC16ULL, 0xD54E10BE41FBAD0CULL, 
            0x8F381DE47BA50E68ULL, 0x0658BBAB9AE9A897ULL, 0xB140510698B3A52FULL, 0x4A500F9F7405A4D1ULL, 
            0xBBA7EC5727ACD4A5ULL, 0xD2A46C8EA6483D6DULL, 0xF2EDEDDCBA23C0FEULL, 0x56D3F8B513B4DD42ULL, 
            0x1F1BB84F94772702ULL, 0x2F1C3864E5D291C2ULL, 0x49FC8EDCCE74E456ULL, 0x121489B38F080D6EULL, 
            0xFDD53471D89D18B1ULL, 0x1380143AD53A5FCBULL, 0x026B521157E97D5EULL, 0x660F9B2534319A5BULL
        },
        {
            0xB6C149C21F534572ULL, 0xE7D23FB37F8FCA63ULL, 0xD41F913AD098B72FULL, 0x49E10A30E4E349F0ULL, 
            0xA7460D31546D1A53ULL, 0x6F28E9FBE2A3541BULL, 0x75B50185615494E8ULL, 0x3F2EE0871620EC6EULL, 
            0x10F42B8E28990DD0ULL, 0x404C4A1C0ABC7B73ULL, 0xB6A0723588EB3098ULL, 0xB60502EF6BC17713ULL, 
            0x77A43A520EABEC3BULL, 0xF8C47C297CAD80CBULL, 0x1685A1DBC4643287ULL, 0xE9BA491ABBF414AEULL, 
            0x22C7B2626A7A3B6CULL, 0x50E538D6774EF0F3ULL, 0x068223F29F7CE9CBULL, 0xB988A370CFC33167ULL, 
            0x6A3D4855FE26D083ULL, 0xDC64850CB9FB7CBDULL, 0x3143B94DB11ED49AULL, 0x78A0F103BBC445BBULL, 
            0x0A4B1A2F2FE55C6FULL, 0xB61F32E65E012D28ULL, 0xAED78E90ABF06CFDULL, 0xC0942989165D10F8ULL, 
            0x7C908308AC3D9478ULL, 0x116F76AFA65B799AULL, 0x0A2B9F2792B9D667ULL, 0x7139267B25996F8CULL
        },
        {
            0x292B27FA00F00277ULL, 0x187F395EFF49EECAULL, 0x5013D9BE803BD29DULL, 0x81AE91D3A8193CEDULL, 
            0xA8B83D577F4504AAULL, 0x930EA19F5D2D81E8ULL, 0xD31B94AB7545584AULL, 0x06F33C4A041F9314ULL, 
            0x0EB369AAFE3FCC08ULL, 0x36D402D63B87B7EBULL, 0xEE65232F250FBDF2ULL, 0x4DC8B734A9707197ULL, 
            0xFFABB4108BAA4DB0ULL, 0x971968EB92C26EAAULL, 0xA84D7D740C5BAFCAULL, 0xE8A48DF86F8525F2ULL, 
            0x2D5F378F3CCFCF01ULL, 0x55A1A32CF72528DCULL, 0x371D9A29B078FE7FULL, 0xA0440AEF545ACE4AULL, 
            0xFDCD86D39AB65342ULL, 0x66A3AD798F1B7289ULL, 0xD30B25957B8558B0ULL, 0x6619E3E90412ABA9ULL, 
            0xDB75F3929767258CULL, 0xA618D285F4769685ULL, 0x5789A9A15B2E961DULL, 0x959BD0469E106441ULL, 
            0x7F7C16BAA3BCDACEULL, 0xD79CB0DC73EFF529ULL, 0x6F49DFAA502D6C6BULL, 0x2CCA141444554E10ULL
        },
        {
            0x73F2ADF019A68EAFULL, 0x65AC7C83D98FDCA5ULL, 0x87951ED649A75A29ULL, 0xBBC0B790745299F2ULL, 
            0xB25DCC9DBE193C0CULL, 0x40097AB0F145B0DCULL, 0x0176B2AB2A9AFB27ULL, 0x3DD8B1D44AB38D26ULL, 
            0xE8C3CDD0C496F68CULL, 0x7BE599AFEB7FD53CULL, 0xA4DE9B4D32042676ULL, 0x34BBDF908706C54CULL, 
            0x04CC7CF468A226E5ULL, 0x08C4A00577860290ULL, 0xEC65DB94A36D8D2BULL, 0xE1C84A2C5969BBBEULL, 
            0x225C3953641F14EBULL, 0x451CEBA4094B75E3ULL, 0xEA4EA01C349E1E76ULL, 0x0E4B7F94C12B8E60ULL, 
            0x91763F1B52BB8626ULL, 0x8B41A4D6D9EE8FFCULL, 0xAE287DA64001BEFEULL, 0xAD3D2FD1E7ECAA56ULL, 
            0xD2516A5FF8F381A0ULL, 0x787349482ABB50F6ULL, 0x31D1D67240375F1FULL, 0x888CE1740546A834ULL, 
            0x35999BD57D87B5C6ULL, 0xB7409CAA65F46153ULL, 0xC7B54234D851692FULL, 0x7710768FE6B492AAULL
        }
    },
    {
        {
            0xA1B79D6C5B87F654ULL, 0x26A629EBF34135CFULL, 0xE798089D8CAFCC88ULL, 0x0D59DDB1BFEA2B20ULL, 
            0x50C9EBFC79C29456ULL, 0x1D7EDBCB6B492B99ULL, 0x36F1FEF2E8914924ULL, 0x3448461CDFE3E50FULL, 
            0xDDACF448A7595218ULL, 0xB029452584F0609AULL, 0x63B94C98A5594700ULL, 0xCE4DD8928A919659ULL, 
            0xB4D0AA094A7CC2E0ULL, 0xDEA9170D743AB229ULL, 0x7F6D3BA371CA2020ULL, 0x4A2BC796017CDEC5ULL, 
            0x352839CA0A61C256ULL, 0x1919087681BAF7B6ULL, 0x98485885E9F611CCULL, 0x1AC9B1A74D5381F4ULL, 
            0x3BBD9BE96CF4DA43ULL, 0xF648F5594B0D2C21ULL, 0xD3461EFED4C45B11ULL, 0xB75B2EB09DC1250AULL, 
            0xCA438B8ED5C38A10ULL, 0x22F2986C67F2352DULL, 0x7055B1D188573FBFULL, 0x3D21255E6E5F1D46ULL, 
            0x021AD8E148E242C9ULL, 0xB548B64495F9A7D9ULL, 0x397CBCE3248C88D8ULL, 0xDB0C1598A6A04BECULL
        },
        {
            0xCE48EE7BC130B9C1ULL, 0xEEC8699F5D8D914FULL, 0xF1184AD0040760D7ULL, 0x1B489451B4CC609CULL, 
            0x9A981C270DAA2985ULL, 0x767C408C4E62F3EEULL, 0xA333399AAFD390EBULL, 0x09618141F67208EDULL, 
            0xF844BB2F47727CE9ULL, 0xEA30D71DCF07F270ULL, 0xFE1F2F835AAE98D9ULL, 0x631DC0D9026E1A34ULL, 
            0x5D86E2A84DCFC33FULL, 0x940C529C3A2D460AULL, 0x16351927B91FEA72ULL, 0xB5490700F9E0BEA8ULL, 
            0xB4AC414283CE2334ULL, 0xD405CE367C78EF71ULL, 0x00C50B419262E16FULL, 0x1E0D6BA6F9EE2E18ULL, 
            0x8C809FD9FACB61DEULL, 0x3D0A8F08EA22163CULL, 0xC59EF33D703B43DBULL, 0xCFA58A1C49B729EAULL, 
            0xC56358DDAF294226ULL, 0x02AEEC3B0B4E0879ULL, 0x71ED199EFC74457FULL, 0xFECDF4590B5B1A71ULL, 
            0x857F260EDCBA24A2ULL, 0x11D911B4649CA74BULL, 0x07FEC843E704D564ULL, 0x34B4B1864888A5F0ULL
        },
        {
            0x0704A2AE0073A29FULL, 0xF75E92BB31350E49ULL, 0x1DCEE0CB4C606397ULL, 0x1A3EDD3A3593E894ULL, 
            0x5C8B5528AE31BC7EULL, 0xD33F648FCBEE8E4CULL, 0x0C1425D8D250DCECULL, 0x68C166CF2C983067ULL, 
            0xE74D84E8ABE4C630ULL, 0xCB79F265D451DDF4ULL, 0x2B7DEE23CA70E112ULL, 0x05C65B346DB4827FULL, 
            0xF0905E25837A7AF5ULL, 0xB5E983A7A6327AA1ULL, 0xE94A9A08E279BFC6ULL, 0xDFFBBF454A6E1B34ULL, 
            0x58F7A357E5BD34BCULL, 0x5A2A911A9FC9FA7BULL, 0x464B788754FFB517ULL, 0xA86C325B9C923244ULL, 
            0xDD7557BFA02D3827ULL, 0x420F1D02DAA63E29ULL, 0x0051DB4B6076CCF5ULL, 0x71D8DC4CF0C2567DULL, 
            0xB05E4F14ECEFF614ULL, 0x3FE559BD1D758F21ULL, 0x75952BA7908F8471ULL, 0x33A615B848B20CE1ULL, 
            0x234AD7007007AE2DULL, 0xA9E4AB453BCE4BF9ULL, 0xC90D1BAA0C7BA18EULL, 0x91A0810B6AE1956AULL
        },
        {
            0x057263F5A76229F3ULL, 0xC60EA18C761F5B7CULL, 0xAEE02B60653B9D9AULL, 0xF249842E0A23D5D4ULL, 
            0x7E4EA9BC92646425ULL, 0xED135835A6A9A98AULL, 0x8C7FA18F6BCD7E0DULL, 0x3D462D823853D93CULL, 
            0x4C35F95A05EA8B38ULL, 0x5C5C2C1E44341CD9ULL, 0xAA6B3ED49A1E4CC0ULL, 0x949D3D4260AB4FE5ULL, 
            0x5F6BA3C546D1B286ULL, 0x3108CE1BA465D1EEULL, 0x26CC3A75632C22E2ULL, 0xB0A4008A2BDAB756ULL, 
            0x4961D01CE0D8DB96ULL, 0x8237386AEB510242ULL, 0x254E53679D6B97A0ULL, 0xDB329A496A597011ULL, 
            0x68934E936F8CBFE6ULL, 0x434C5D90E9E03F11ULL, 0xEE6B918D6B207FB8ULL, 0x20DAE86498D653B5ULL, 
            0xC361AE9626ECFC28ULL, 0x1771F5FC6D69111AULL, 0x78F2D669A9F51201ULL, 0x33E10327BB79B65CULL, 
            0xA23AF796AA0A46F3ULL, 0xEE1EE5ABF091AFA1ULL, 0x42D34FC183EA548AULL, 0x34E44438A6CCB11AULL
        },
        {
            0xC41F7BD9D374296FULL, 0x4B639B3CB9B897CCULL, 0x10ED4AC1C22EC98EULL, 0xEEFE4DAE87D81CD9ULL, 
            0x798F73F7B949007AULL, 0xDE101DEC83E5E271ULL, 0x406F0D130429D701ULL, 0xF02C40C54A13CFA2ULL, 
            0x9BA7FBB8884666CDULL, 0x26E089E8694474BFULL, 0x654882E9F47D5A10ULL, 0x6FA6F73DD40716E1ULL, 
            0x9298693C59060A09ULL, 0xF9A50BF39BD83620ULL, 0xF09C661242B2DE49ULL, 0x0DB50B51E3791A7BULL, 
            0xC6B1F5043E10979BULL, 0x5CA79C697F6FF0FEULL, 0x00F3B50F25375CF9ULL, 0x89DEEF3BDBF1B6FFULL, 
            0x43804ECD79BF3EF1ULL, 0xD0CE9CAC2B0D5307ULL, 0xA0F89927C39B60F9ULL, 0xF1D9A6E72081C9D9ULL, 
            0xBB55499CCD95B907ULL, 0x529AD2CFE4BE0266ULL, 0x8A076EBE63BEFF67ULL, 0x8722BF4B1F9DE755ULL, 
            0x82D030100D365192ULL, 0xB5C15D028708587DULL, 0x932695700B7A6ECAULL, 0xB4E73829C5A5E09DULL
        },
        {
            0x5CD9F4019A1B8263ULL, 0xE5528BB89424398EULL, 0xEADE5B2D5150F92AULL, 0x3F69BF07A5343560ULL, 
            0x2D6F56E238EACED5ULL, 0x2C8999EC9227E41DULL, 0x931C0A291EBC129EULL, 0xE752816E514DBBA4ULL, 
            0x970EFEF9332E4370ULL, 0xA8069F7365194E19ULL, 0x6188ADBA30FE3BB9ULL, 0x563DF4F929D57E46ULL, 
            0x6872BDD80E1A0567ULL, 0xA58A59ECBC00D4B3ULL, 0xF36D1CBA83D067DDULL, 0x9BFFEA1ACAEE3640ULL, 
            0x967491421A51B97EULL, 0x12909DDEB6CA27F6ULL, 0xBD25A7FAB0FE5054ULL, 0xB413FE2F5E2AB3E4ULL, 
            0x386C0FC1C114BB76ULL, 0x4E4BE8F2A4A4C9D8ULL, 0x0FA852667E619C95ULL, 0xCD497BBB8DCBBB41ULL, 
            0x10AB60795663289AULL, 0xA03CB8A6D74DAC63ULL, 0xD45EFEB90C7FF33CULL, 0xD48181403F94157DULL, 
            0xE31850847F52773BULL, 0x613A2DF1B34ABB2AULL, 0x82AC8248278E960FULL, 0xB25124B4E0D3D4B8ULL
        }
    },
    {
        {
            0xE38240D21CAF2BC3ULL, 0x5DA262F8C85D43B8ULL, 0xFF31F9AB4FD75695ULL, 0xE520EA1997575D15ULL, 
            0x839D8772F49C7332ULL, 0x33CBF29E3C963B58ULL, 0x68057B2C2B3E9904ULL, 0xEB4325C66127F1B2ULL, 
            0x2F08EB4184DE3EDCULL, 0x3F0C3EA70B671462ULL, 0xEEA2FA8B52F943ACULL, 0x07DB07FAA590277DULL, 
            0x48E6D3959D0E08EFULL, 0xF657B089EC1086B2ULL, 0xAC551A5F4F38177CULL, 0x9B0A4B0F847D665CULL, 
            0xE1434E921839FF02ULL, 0x4A5AC273A6AFE849ULL, 0xB7CE753FB19B2D85ULL, 0xDCA2FA50277FFAC3ULL, 
            0x125BE1106A7D09ADULL, 0xFC96BC297F819DE1ULL, 0xDCF0EF9BB9F51570ULL, 0x6A43EA099EEE632CULL, 
            0x621B3D6A87EDEE66ULL, 0x23E71D8CD2E38824ULL, 0xA41343BC118826DBULL, 0x061E2915A450EF19ULL, 
            0x3DF2335DA02777BBULL, 0x24E9CA865C4E3088ULL, 0xAA9BDE9983BF381DULL, 0xA19D4FE9FA23B297ULL
        },
        {
            0x8E2AE8A0B9799C0AULL, 0x4AB20DDD91701066ULL, 0x2938507A11B3B726ULL, 0x83B1040CC1A400F4ULL, 
            0xF644FA557759AF34ULL, 0xA608C4498254CB46ULL, 0xF54F28533E4086C3ULL, 0xE2F9FC343209D868ULL, 
            0xE8CDF2589D7B56F3ULL, 0xDD1E249A5C5D0B2FULL, 0x576AE6F8915E330DULL, 0x418AB9E2F481C53CULL, 
            0x79D2492BC79D4B8BULL, 0xA469CA4235C44181ULL, 0x11784153B680D03EULL, 0x45B1423689F33732ULL, 
            0xBA5FD022944A7D3BULL, 0x36D5D9DDE6A2EAFCULL, 0x49C2D97569A046F3ULL, 0x3A8CC9FEAEAD257FULL, 
            0xAE41C10AFE39B9FFULL, 0xDFD85F2EB66BE196ULL, 0x5067F821AF4D2A96ULL, 0x56082821CD38EF8DULL, 
            0xD02D437A28BC3DFBULL, 0xA86BC39F9336A3E0ULL, 0x89FAB3C2C3C721EEULL, 0xF16AB274D62AA6FBULL, 
            0x8D18EE56017D833BULL, 0x61253D031D0249E5ULL, 0xA8A342D90B26EFA6ULL, 0x67BE5E9A84BEF388ULL
        },
        {
            0x93576D54ECD03433ULL, 0xE25609A5692E11BFULL, 0x07A4FBE7FAA47AF9ULL, 0xED232C8709EB7B10ULL, 
            0xEB3C10E45ADECC5BULL, 0x9159DF797B55EFEDULL, 0xA6280B3E74039F13ULL, 0x1FD3B10AE39EFC75ULL, 
            0x85E6388C80CF855FULL, 0x67A8041C71EB2252ULL, 0x3AE3C056C96E4040ULL, 0x2D4733929C110BE9ULL, 
            0xC73F6052FFBA1728ULL, 0x5C53CCAC0C2E8A8EULL, 0xAB9A9F6B015EC1A5ULL, 0x95143FE0CB33988DULL, 
            0x36C99CD05A1D2783ULL, 0x890E8701A1051B0CULL, 0xBF4CDB9F40D4D8D5ULL, 0xBF22E36D5B429DDCULL, 
            0x879B53468EEE45BFULL, 0xBDE5703AF5166B4CULL, 0x5C47EED16493D5E6ULL, 0x1847B02B1D411CFAULL, 
            0xAB3EF04B10126C8CULL, 0x984D7EBE3C1CBB91ULL, 0x166F9F8877BCFC2CULL, 0x3FA695B9AD8B8A47ULL, 
            0xC3400527F03B9235ULL, 0x3896069888B2AB29ULL, 0x5BC166F215E9A1A4ULL, 0x486E952BE315715AULL
        },
        {
            0x1565D16FA3175C89ULL, 0x67AE0B7B6D8161AFULL, 0x3027803B7A6B3B86ULL, 0xD17034B8EC936ECEULL, 
            0xB582865694C8B66EULL, 0xBD6E480A881F5FAEULL, 0x05973AC99B050EFCULL, 0x64BB2672CC79082FULL, 
            0xB0E76BA61F7E83D9ULL, 0x79E59B4DCC7C5FA3ULL, 0x02B3EFB8EFE01CD6ULL, 0x77567542211AF04EULL, 
            0xA3A1E2B23DCF2C0CULL, 0xFE832088335A98F4ULL, 0x73BF523E311D6ED4ULL, 0x21298C37868F28EEULL, 
            0x02C699168ED7C964ULL, 0x24C556A0D77EFAFCULL, 0xE2FA9BC0D73CF5C7ULL, 0xD7902774268CA886ULL, 
            0xF60A490350A42CB9ULL, 0xE0D062199FB2170DULL, 0x6F1B36CE19A611AFULL, 0xB09A8D9B46EB0721ULL, 
            0x667295CDC9A494BAULL, 0xDE311B7BA9D04E10ULL, 0xDBE8F536BC79D282ULL, 0x701FB4A57F744A54ULL, 
            0xD5BC62CDD1B143DFULL, 0xD633DD307F0B3349ULL, 0xE3D3E343483C0F6AULL, 0xED5ADE77539710ECULL
        },
        {
            0x56C113FD9DEDD8F3ULL, 0x3CBF3FDBF67CCAADULL, 0xBEB6203530490558ULL, 0x768028EFF3701F24ULL, 
            0x59C671F0CA17F8B3ULL, 0x6C6263909BAABF53ULL, 0xD8DA0038C1C61B7CULL, 0xD581CC6C1CED1F0DULL, 
            0xB8BFB77F15862C78ULL, 0x97C5A4F9E969E382ULL, 0x9C55C8C1AF4237F3ULL, 0x38D5B6A1F218FA43ULL, 
            0x6F4B1EBED791FFABULL, 0x53DADB9A52BD6945ULL, 0xAF5281BBD931F94AULL, 0x36246B57CFF65DBAULL, 
            0x2DC8B21AEFC509F5ULL, 0xA5BC397D08E6FC96ULL, 0xCEB15A11FB3D69C6ULL, 0x8128909142604221ULL, 
            0x04A19BE5C7B6F57FULL, 0x1EE0D0016A001904ULL, 0x641494D822A1E100ULL, 0xD43045C42270B673ULL, 
            0x71A8853E48D55B65ULL, 0x77B0B70022FEB178ULL, 0xC5C4A8BEFE54561EULL, 0x6BB83F1C3F157232ULL, 
            0xC9E46AA1FF519CE2ULL, 0x550EE11C724CEA93ULL, 0x58D19630F04E492AULL, 0xD92503AF0C958712ULL
        },
        {
            0x3ED5C649B913C5F9ULL, 0xA9701D6604983134ULL, 0xB54E585041CF5D84ULL, 0x2AB7F0B5865CBEC9ULL, 
            0xB6F8332340C24EBBULL, 0x67ED415B7B6131C4ULL, 0x1ABACDAABE3F32C1ULL, 0xC7DD9FCAB66D5C29ULL, 
            0x24FB7041688EAF3CULL, 0x6300938FB72CB764ULL, 0x22884401F2EF46C0ULL, 0x474AE6FA69CDD155ULL, 
            0x144EB48E3924BC1EULL, 0xA7F9AFCC7BDFB245ULL, 0x51A48B4E8C1FD42DULL, 0xDCE551AB95A40E87ULL, 
            0x2423ECF5091AA0DFULL, 0x12E4E12078AA291EULL, 0xC4A0B66C8F821CD4ULL, 0x0E3ABAB31CD66958ULL, 
            0x8909DBF8F95947EFULL, 0x8F1B0C0632510E99ULL, 0x1484BA12CA5EE6E6ULL, 0x715A915232C18B3DULL, 
            0x5CC2CA1063EF84FAULL, 0xC7166F4A85A283D5ULL, 0x886F1E4C07362D01ULL, 0xDB31171BD8178210ULL, 
            0x17183C16FB75EC46ULL, 0xF934454814DC2F42ULL, 0x50303C63A7B833A2ULL, 0x11EBB433248FBD65ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseHConstants = {
    0xD6817A9FDF8C828AULL,
    0xED69E9C26AD9C597ULL,
    0x851DE47F47D9607DULL,
    0xD6817A9FDF8C828AULL,
    0xED69E9C26AD9C597ULL,
    0x851DE47F47D9607DULL,
    0xFC19DBF91684BBBBULL,
    0x6AED6B1BAB522853ULL,
    0x0F,
    0xD5,
    0x76,
    0xAA,
    0x3F,
    0x42,
    0xFE,
    0x32
};

