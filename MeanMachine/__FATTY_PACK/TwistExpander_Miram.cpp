#include "TwistExpander_Miram.hpp"
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

TwistExpander_Miram::TwistExpander_Miram()
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

void TwistExpander_Miram::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x8AAEA200C37362ACULL; std::uint64_t aIngress = 0xA4B885268D9360FAULL; std::uint64_t aCarry = 0xF21C6B7BB6C0E074ULL;

    std::uint64_t aWandererA = 0x885A442E69350766ULL; std::uint64_t aWandererB = 0x8232038B9E35163EULL; std::uint64_t aWandererC = 0xA72FCF9B0EEEC2FCULL; std::uint64_t aWandererD = 0x9CC27DB8288CA4ADULL;
    std::uint64_t aWandererE = 0xC2FCD9A52D99602BULL; std::uint64_t aWandererF = 0xAAE7C6280FA35564ULL; std::uint64_t aWandererG = 0x840FAE85E8F8D740ULL; std::uint64_t aWandererH = 0xADCEB890A0035BE6ULL;
    std::uint64_t aWandererI = 0xBDEFDCBA0AAD2235ULL; std::uint64_t aWandererJ = 0xDA2E3BC291B16CCAULL; std::uint64_t aWandererK = 0x831920094F2E171FULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17863217254155607243U;
        aCarry = 11821837910373833429U;
        aWandererA = 13132075027455725766U;
        aWandererB = 11261932561449662878U;
        aWandererC = 16671813869837946263U;
        aWandererD = 10426290215777819905U;
        aWandererE = 17270995602495626787U;
        aWandererF = 10006905826405967470U;
        aWandererG = 18046028228168842410U;
        aWandererH = 14241382408525367084U;
        aWandererI = 15170512808565152211U;
        aWandererJ = 12148921422692697288U;
        aWandererK = 11891826562428046163U;
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
    TwistExpander_Miram_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Miram_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Miram_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Miram_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Miram_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Miram::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC9BE58A0AF8DC4B7ULL; std::uint64_t aIngress = 0xE572DFD8036F7209ULL; std::uint64_t aCarry = 0xB938A7FCFDF16DFBULL;

    std::uint64_t aWandererA = 0xC1CAB8EAE3CBA71AULL; std::uint64_t aWandererB = 0xD7CA41437C36DE82ULL; std::uint64_t aWandererC = 0xAE6DF1462BE169F6ULL; std::uint64_t aWandererD = 0x88899AB4DC3910C8ULL;
    std::uint64_t aWandererE = 0x9B10DFC6A6FE0D9FULL; std::uint64_t aWandererF = 0xB8C520981F9716FBULL; std::uint64_t aWandererG = 0xE7530FC7806F0535ULL; std::uint64_t aWandererH = 0xFF9672D14D4936B2ULL;
    std::uint64_t aWandererI = 0xB1A0AA6AF9BAED3AULL; std::uint64_t aWandererJ = 0xD106B36DD0823379ULL; std::uint64_t aWandererK = 0xE2B90423CB331EEEULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10019970166752058075U;
        aCarry = 17478686873589234572U;
        aWandererA = 15232914091678012221U;
        aWandererB = 17226321267581407100U;
        aWandererC = 17082771055156459131U;
        aWandererD = 15555527347650295841U;
        aWandererE = 15488654440347784198U;
        aWandererF = 13779091443095285423U;
        aWandererG = 13437046824740291882U;
        aWandererH = 15362283059940302985U;
        aWandererI = 17569744974021763631U;
        aWandererJ = 12999486313721119804U;
        aWandererK = 9763457544041098093U;
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
    TwistExpander_Miram_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Miram_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Miram_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Miram_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Miram::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE98AD8798D6A33D8ULL;
    std::uint64_t aIngress = 0xC1E5AB0D6467B5D3ULL;
    std::uint64_t aCarry = 0x8ADF10A6E695CFC0ULL;

    std::uint64_t aWandererA = 0x89CD6F9AF0A0C499ULL;
    std::uint64_t aWandererB = 0x96C3BFD36D7A7592ULL;
    std::uint64_t aWandererC = 0xC0FCAB8C2BB2CFEDULL;
    std::uint64_t aWandererD = 0x8A1CDAA3AEF1A67CULL;
    std::uint64_t aWandererE = 0xC0432C015C011E43ULL;
    std::uint64_t aWandererF = 0x83C78FF911E906C8ULL;
    std::uint64_t aWandererG = 0xAA6AB99A37DB338FULL;
    std::uint64_t aWandererH = 0xE132E52CA5823723ULL;
    std::uint64_t aWandererI = 0xB38B2194F30EB9AEULL;
    std::uint64_t aWandererJ = 0x8195F243EDB01507ULL;
    std::uint64_t aWandererK = 0x942D9A3FD305E0FEULL;

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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
    TwistExpander_Miram_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Miram_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Miram_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 20 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1797 / 1984 (90.57%)
// Total distance from earlier candidates: 34426
void TwistExpander_Miram::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 579U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 311U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 0U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 360U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 348U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2002U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 340U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1287U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1594U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 379U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 924U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1866U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1009U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 111U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1721U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1077U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2013U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1700U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1858U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1515U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1339U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1925U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1187U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2036U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1820U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 196U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1955U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 854U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1011U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 872U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 795U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 85U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1439U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 946U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1172U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2006U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1240U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 413U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 828U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 701U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 190U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 912U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1532U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 13U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1130U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1857U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 412U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1604U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1125U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 44U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 480U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1884U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1166U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1182U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 183U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 499U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 276U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1253U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1569U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 665U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 503U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 376U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1218U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 387U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1365U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 609U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 52U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1988U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 941U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1361U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1460U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1421U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 761U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1219U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 978U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2037U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 834U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 357U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1538U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1704U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 515U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 69U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 240U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1153U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2032U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 36U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1101U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1471U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 225U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 262U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 114U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1654U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 934U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1249U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 745U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 657U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 929U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 364U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1220U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 523U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1827U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1879U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1241U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1634U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1747U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 683U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1137U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1427U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 124U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 421U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1456U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 398U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 67U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 20U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1526U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1035U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1150U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 595U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 992U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1841U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 760U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 890U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1022U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 775U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1342U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 200U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1551U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 234U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Miram::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x98B52420CBEE885EULL; std::uint64_t aIngress = 0xEE21EEFCDA316960ULL; std::uint64_t aCarry = 0x8B17BF800EFE796DULL;

    std::uint64_t aWandererA = 0xA696D16C5B5330D4ULL; std::uint64_t aWandererB = 0x9EEC6DA5A2416A10ULL; std::uint64_t aWandererC = 0x9699B1521AB4F401ULL; std::uint64_t aWandererD = 0x92D462A374C5AA1AULL;
    std::uint64_t aWandererE = 0xCDC26E6656D93F95ULL; std::uint64_t aWandererF = 0x8C281FCEF96BEE31ULL; std::uint64_t aWandererG = 0x854283368374DB0EULL; std::uint64_t aWandererH = 0xA76FEA3ADED7FC7FULL;
    std::uint64_t aWandererI = 0x97A139E2763A76DDULL; std::uint64_t aWandererJ = 0xD5B8AAAEEC4D6E20ULL; std::uint64_t aWandererK = 0xA6512466DA8FE7DFULL;

    // [seed]
        aPrevious = 10508678516320658143U;
        aCarry = 9956536349422342824U;
        aWandererA = 17517239657513757539U;
        aWandererB = 12483447227901373346U;
        aWandererC = 13687005906091275422U;
        aWandererD = 10729354526492112856U;
        aWandererE = 17868072540341014071U;
        aWandererF = 13098745114911290033U;
        aWandererG = 12050983742630178925U;
        aWandererH = 12865868488279975984U;
        aWandererI = 17841881344785044684U;
        aWandererJ = 9758599479374950611U;
        aWandererK = 10825414489099376589U;
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
    TwistExpander_Miram_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Miram_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Miram_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Miram_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Miram_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Miram_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Miram_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 20 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10373; nearest pair: 507 / 674
void TwistExpander_Miram::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 459U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3778U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3132U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7710U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5247U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7730U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7814U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4157U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7441U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 659U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7317U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 316U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4876U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5706U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4063U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3595U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1158U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2023U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1249U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1164U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 795U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1777U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 62U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 408U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2027U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 415U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1259U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 524U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1402U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 529U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 275U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1834U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1630U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 605U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1466U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1216U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 20 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10358; nearest pair: 481 / 674
void TwistExpander_Miram::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 751U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2393U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 290U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6840U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6623U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3622U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8078U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3549U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7063U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2450U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1266U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1285U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 701U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3023U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5761U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4537U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 897U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 241U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1408U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1811U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 357U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1164U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 740U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 150U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 48U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1816U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 599U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 730U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 520U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 18U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 437U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1071U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1663U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1192U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 643U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1511U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Miram::kPhaseASalts = {
    {
        {
            0xFB8164F7B411A172ULL, 0xDD4A594EB934D7D5ULL, 0xA3AA1D87EFA83707ULL, 0x21F52E0300E68109ULL, 
            0x1F72103F7EB6869CULL, 0x9AED236D7B5F65B9ULL, 0x3FFAE6FD13D88CE2ULL, 0xB3CB88CEA136128CULL, 
            0xCCA1B09D912B3556ULL, 0xD47F03568EBB0C77ULL, 0x390019D9AFEC42A2ULL, 0x5756A6A334B909FDULL, 
            0x7B5983494E36CB57ULL, 0xE0707B32A56FFB92ULL, 0x871E6D4798B1163AULL, 0xCC32195DE654B3A9ULL, 
            0x8E180F0380FBFFBFULL, 0x89EF1E921A5C7AF5ULL, 0x314BB120A0DE202FULL, 0x6C05C3A8DE4348F7ULL, 
            0xECDDF041B4179C18ULL, 0xEC4887D8B79FCFEEULL, 0xDF9AF730572932B2ULL, 0x23AC9F2F4FAD53C6ULL, 
            0x8631F263A8FE812FULL, 0x21E7A0D2E824947FULL, 0xB8AD6DAEE01E56C1ULL, 0xB9B6E38DB49470DAULL, 
            0x6C56FD09EACCE6ECULL, 0xDA80C36A7B91402AULL, 0x2D0D5B94BD845ABDULL, 0x679D64F081103F22ULL
        },
        {
            0x37C5128FCD0FA13AULL, 0xFE78F96883338D75ULL, 0x2C2B42BFD166BC4EULL, 0xF351C0C42DB56434ULL, 
            0x7DE62BE10F015836ULL, 0x7041BCCC021B069FULL, 0xC8207DDABDBC69BEULL, 0x5E761A35DC02CEA5ULL, 
            0x5908A03105358320ULL, 0x0C3514A5AEDE8095ULL, 0x1A478B4EB46429DFULL, 0x2191A9E30B243B03ULL, 
            0x7E40160837D15BD7ULL, 0x89FA195AD143325AULL, 0x072DCF40F1289394ULL, 0x160887217C051212ULL, 
            0xA3E0EEE578292D8AULL, 0x742E0C06CDEDA98CULL, 0x09047D01D238A91CULL, 0x84F51517799241BFULL, 
            0xFB6AF3DEFAA532B8ULL, 0xB9A66B4F14833602ULL, 0xC89080656C14D38AULL, 0x7DD6D3DDF48E9825ULL, 
            0x023DDFB38E1873D0ULL, 0x2938123A937D1895ULL, 0xD87699C1A221ECEBULL, 0x0E3EF52AC1B627A9ULL, 
            0x233E9233D1A55742ULL, 0x4671E7FCEC70B3BFULL, 0xCE9C6A6162C7CD42ULL, 0x1C10F8BA2A6D65F6ULL
        },
        {
            0xF8DDB526FDF1B228ULL, 0x9EAC21AB4E21D543ULL, 0x8ABA42A1CC0285FFULL, 0x01A8B65525AC7CDCULL, 
            0x0D5B9D1C14ABDF30ULL, 0x44B0118C50CEE8A6ULL, 0x86D27B23F8693AD0ULL, 0x0E8C0CC76A637122ULL, 
            0x08C974A2A004C75FULL, 0x480A2A6BA1B83279ULL, 0x1278E2FB6EFB3391ULL, 0x438BEE07562F2FA4ULL, 
            0xE1C3CD451A602606ULL, 0x0C7D52BBF488A598ULL, 0xAC90C894AC758170ULL, 0xB7C29D21ACEAB193ULL, 
            0x8117DB7B96219CBEULL, 0xE04D35EF008D9FB1ULL, 0xA4A1B3E5060D2F5DULL, 0x91A7552B7F57FADAULL, 
            0x547976BA6643C897ULL, 0x9F3C6C1D5D755C6CULL, 0xB38AAF97C0461F41ULL, 0xE01BD070D7F1E1BDULL, 
            0xC36401073E600A26ULL, 0xFCEF6274E25CFC90ULL, 0xDBA7F2D275B66103ULL, 0x4ACDCAE7695A8556ULL, 
            0xFCE85CF5A94F36F0ULL, 0x1B62304DE8081FD0ULL, 0x5154A1648221C2D0ULL, 0xB7D3DAD5D5C13F42ULL
        },
        {
            0x408225CBF98D1951ULL, 0x822D04C21D5EB37CULL, 0x0EEEE67D39AF162FULL, 0x3DBE945043140D34ULL, 
            0xE301D3CB21CB500FULL, 0xA4A7F65D42EE96D1ULL, 0x27FFEC54569A0116ULL, 0x905C3315B2D6CD60ULL, 
            0x2592324B71B03E28ULL, 0x9EE4E1C4CBCD4D30ULL, 0xB15AA8831E17AA53ULL, 0xB5D595D3662D675BULL, 
            0x2412B537662D4E6AULL, 0x8F1D3447624D7D99ULL, 0x385E6BFF20505C90ULL, 0x7CA279654E155CFFULL, 
            0x4CD07BFB9A67293EULL, 0x92190A6CC64F13B0ULL, 0xBAD07B4961188511ULL, 0xA95B663B1A27DFFEULL, 
            0x57546E8AD5CF3CDDULL, 0x8BF0DD1C934CF050ULL, 0x245B57CFFAB700A3ULL, 0xD70A6A5183FB7BE3ULL, 
            0x668B48D7B1F8B648ULL, 0x489DEE61B83A236EULL, 0x884B9CB47A4791E3ULL, 0xDB3348308AEA2147ULL, 
            0x3EE7BA58B09902A0ULL, 0xACC7BC57F7822446ULL, 0xFA9CC2FA07FAA914ULL, 0x60485AC70257E94CULL
        },
        {
            0xAF8D0DB486361BB5ULL, 0x8C8856FEE08B1330ULL, 0xA51D37F1E90B9F37ULL, 0x207B3443990DA283ULL, 
            0x8788895BF6E778B2ULL, 0xB490F9CD8C67F72DULL, 0xEB7DCE4EE78FBBF9ULL, 0xED26E8AB97DF5FDFULL, 
            0x12306747BCFFB62EULL, 0x09F4F652EC597FECULL, 0xC13FFF83DB568438ULL, 0xC0AC9C6548B27278ULL, 
            0x1FC9C2A952231190ULL, 0xA905EEC36242BEC4ULL, 0x0F6B85D5313D83BCULL, 0xD5C334F5F633426AULL, 
            0xB00564C7C3A9618BULL, 0x30B0C3D1D8167E0AULL, 0x0A976416C4D0C88AULL, 0xE47E99C28257AEC4ULL, 
            0xB29D3029F41D4443ULL, 0x83F9EA9C562B98C8ULL, 0x54FF113F599D5871ULL, 0x483D9A16409609CAULL, 
            0x4F386CC924858E3AULL, 0xF3D41000230E7BEEULL, 0x07F9D37BDCA5F8E1ULL, 0x3B45E8B263583F11ULL, 
            0x65E5393020EFF01AULL, 0xEBEB7A0353F0A226ULL, 0xBC9EBB14649F2D17ULL, 0x68F6E9E355FE4DEBULL
        },
        {
            0x08FCD3E55EBDB8DAULL, 0x7E83F4D4089ECDDBULL, 0x850804BAC5B985D3ULL, 0x9AE2BB6716709395ULL, 
            0x2A0890C034DA0B29ULL, 0x9A5C8FB6B0BE1067ULL, 0x36DE51B30FB4688AULL, 0x23254EB757646FA9ULL, 
            0x0AB4658756ECB7D9ULL, 0xB75815EE3989142FULL, 0xA815EBEA444A345CULL, 0x1B5065F648894A99ULL, 
            0xC96C00783880788BULL, 0x69666F0E9120BD02ULL, 0x6949D34EDEE2732FULL, 0xCF21FAFB2793E863ULL, 
            0xA15C8CED5CF5AB4DULL, 0xF44653C51F5C06CFULL, 0x142AB14BCFD443C3ULL, 0x142F471EADD6BEABULL, 
            0x0B11DF821C3FB850ULL, 0xACEFAA816977EC9EULL, 0x71092DFE133513B0ULL, 0xA102BE6B0575DB1AULL, 
            0x1C06036C1B0869F6ULL, 0xC8DF9114750F5343ULL, 0x557997DD63A893C2ULL, 0xD0323D6637C381BBULL, 
            0xA9D80EC5418C68AEULL, 0x09CB661FF9710917ULL, 0xE22182D1EDD6B03EULL, 0x0726BC56A45CEC32ULL
        }
    },
    {
        {
            0x9D9CB0F7B4E37619ULL, 0xBE2CD8BBCE68641DULL, 0x136E1214AD1B1A14ULL, 0x7E26A8C772B35DF5ULL, 
            0x6ADF43B163C5555FULL, 0x1FAF379F47826D1BULL, 0x81B78C53F1482FC6ULL, 0x5037D013D2AA8F82ULL, 
            0x98F0836D59C111B3ULL, 0x8C7589F5AE17ED4DULL, 0x7A397DF0DA82A9B3ULL, 0xE82457534B1E34C2ULL, 
            0x75AD1AFB463969D7ULL, 0xC9FE9B26F387D365ULL, 0x62480FFAD7678DDDULL, 0x2272445E4D58EEB4ULL, 
            0xB99C1854ABF77719ULL, 0x18BCF9299C2D194FULL, 0x0056686D26DE12C2ULL, 0x624DACADDE3313DEULL, 
            0x67D2BD2858D7967EULL, 0x03A5E33B22A6B6ADULL, 0xB355995A97F48608ULL, 0x11877CCB9D5B9462ULL, 
            0xCC20493B7743FEEEULL, 0xF05E3F9075B406EBULL, 0xC9D782D83CE679F0ULL, 0x20AC27F1846C7B0CULL, 
            0x443299DAB98391C3ULL, 0x58F38EAF2905F41AULL, 0x606923D1A5407AA0ULL, 0xB18BE36428840C4DULL
        },
        {
            0x459163ABB9E59114ULL, 0x8E5B7C80AD9BD5D6ULL, 0xA6CBF27E2286FCCCULL, 0x0097D56CE67BB90DULL, 
            0x4D3439276538A9D9ULL, 0x6205CA2358403B0BULL, 0x130CB9683A996FD7ULL, 0x2E14D9569B4DFD39ULL, 
            0x53D657CA83CDC7BEULL, 0x7ABC6520A54F2080ULL, 0xAF5EA709D2697408ULL, 0x9E416F58AF9ED35DULL, 
            0x598B2A5944BFB93CULL, 0x6FBEF0B5D7578F93ULL, 0x092E6169519D8B27ULL, 0xB4089949F1B8FCE4ULL, 
            0xEA56765D19C251C4ULL, 0xA36DD6D1DB1B33FAULL, 0x25EEC583837D22F4ULL, 0xD23658B948EFCF25ULL, 
            0x0F77C46EF909A9D1ULL, 0xE6B9BE70D976C8EAULL, 0x61B611BDEFB5BC34ULL, 0x542AB72F423F6C27ULL, 
            0xAE0E8B692FB50B1EULL, 0x39B57235A8E951A6ULL, 0x4F0D1E7B8CF16B3CULL, 0x8A3183FE291E51CEULL, 
            0x8F382016FFFA6572ULL, 0xA6CBE5C86A5253E2ULL, 0xBE6F5F3994AE3023ULL, 0x843492B68BE63960ULL
        },
        {
            0xB0AFB143717371FAULL, 0x6198262D48F1898BULL, 0x0A80B4E4BC661835ULL, 0xAF41E29D4387D88EULL, 
            0xE893517CC2699B62ULL, 0xB68DD4DEEA273ABAULL, 0x9ABB93342E8E9F38ULL, 0x22B92DC169D7F5F7ULL, 
            0xD82A2EF19F8463D1ULL, 0xF916DAC42295C994ULL, 0xE3C81E3811B828FCULL, 0x589E523BE1CC8664ULL, 
            0x7A1786F954C3CC70ULL, 0xCF6CD4BDD0918EC6ULL, 0x85F7A442B44F681CULL, 0x591151FB6BF5706CULL, 
            0x7DC6D31A237CB4E1ULL, 0xB5D3ED65057CF317ULL, 0x4176D20A44B9CAE0ULL, 0x28855EADDFEEFD07ULL, 
            0x7ABB179E844178E3ULL, 0xC46FF0BDAB374146ULL, 0xD4FFEAD5A3F449C5ULL, 0x906ECACE0FDE0813ULL, 
            0x2BBECC75856D9A20ULL, 0xEC2403C3514C64F9ULL, 0xC4650F260B921A5FULL, 0xF583F171E16ECCDCULL, 
            0x3F869A82F0C5A52EULL, 0x28A5748F9B300FA3ULL, 0xD0CADECA786E8C77ULL, 0x318C1EDED0E6C091ULL
        },
        {
            0x9AD57012398045C8ULL, 0x30DAD0D5029B0FF2ULL, 0xD30973AFDA44763AULL, 0xBE9D8149B897D9C8ULL, 
            0xC8975ABF0F7BD771ULL, 0xD55B6DC0768119D4ULL, 0x2B8E12B0DA42142AULL, 0xFAA72808357EBA0CULL, 
            0x4EF3681D89DF4E7AULL, 0x1A85CE2C10AF094FULL, 0x06971E91C4813412ULL, 0x8FB54C13E8EFAF87ULL, 
            0xB2E6ED3912038373ULL, 0x3A329E6110AA4AFEULL, 0x8D6E99F1B2A8C8BEULL, 0xF50B626D68BD455EULL, 
            0x40ADF64B4279E01CULL, 0x9E10CFC4A90F6316ULL, 0xC140A121D64A8502ULL, 0x6C51CB1E2FEC897AULL, 
            0x59FAC090AD1E775DULL, 0xC7F3FA7E0DFD4023ULL, 0x1645679610DA65F1ULL, 0x55A04176963F2314ULL, 
            0x9B7B6B77760EDD05ULL, 0x06E9CB91EE70BF80ULL, 0x09B24C8D39A612A1ULL, 0x750839515327E72CULL, 
            0xAED555D39FF2A24CULL, 0xC3E22FE1B04F44C6ULL, 0x617BBD61C250087DULL, 0x139B0CF524F3F283ULL
        },
        {
            0xE9BC3D91297A388FULL, 0x6B36C87C2161AE90ULL, 0x0BD443E1FEE570CBULL, 0x0A78CBC025E70C73ULL, 
            0x3F2AE93A7E01CD73ULL, 0xA39D7CF6DEC075F0ULL, 0x25CFA4E21339C636ULL, 0x4FEC6972F33EBAF5ULL, 
            0x164DFB1AA12C922BULL, 0x470ABA36DF687C7CULL, 0xE77111097FA5F04FULL, 0xA64E9C090DD8CD51ULL, 
            0xEBD1DBB622C53102ULL, 0xE77AEBC7BF0C5287ULL, 0x1F9BBA246E71B850ULL, 0xFB5B5E926CB387F7ULL, 
            0x3954CD070FA2AEF6ULL, 0xD596DD6864E894CFULL, 0x0E7890445A7AC462ULL, 0x82DE17B83C2F317AULL, 
            0x483B6B372998C270ULL, 0xB3DACE4F187710A6ULL, 0x8E6893E1770EA9B2ULL, 0xC965393B59152B03ULL, 
            0x2A2548C8C6C367DBULL, 0x631AFD76DEC42944ULL, 0x46C26E5B19AE455AULL, 0x77093AECDC1CB015ULL, 
            0x661AFB0DEFE82E9DULL, 0x6B92BDFCDF7976E3ULL, 0x10088AAF5F72700CULL, 0x3B70749DA961F034ULL
        },
        {
            0x9CA41A0447C7C511ULL, 0xAC413F8776F5322EULL, 0xC318573478972C07ULL, 0xFAC996C14CF6C479ULL, 
            0xE9772A88A66C2B49ULL, 0xC56736FCD7EDB11DULL, 0x2C0E091B49DF3776ULL, 0xFC0AE48FA2EEA0EBULL, 
            0x9832DBECCB945C34ULL, 0xEA7C1C8B8EB6BDB1ULL, 0x258620698EFBB687ULL, 0x3F2215AEF38E0671ULL, 
            0xF2CC708A509BFFA3ULL, 0x97EBED80200451C1ULL, 0x072548D080788D2AULL, 0x36192E98474479EDULL, 
            0x8F2E70481D731E64ULL, 0xB0F6CE3E31372634ULL, 0xB428C524F5EC1956ULL, 0xFFC0A3FD59624138ULL, 
            0xF674CA0A415D70B4ULL, 0xE762252026E269C6ULL, 0x0F4CB74733AF7046ULL, 0xC637789F5091B8CEULL, 
            0xFF8D150575463004ULL, 0x2E3409DE03448B14ULL, 0x4BB48FA848E4F47AULL, 0xA67EEA5917310EC7ULL, 
            0x74EA8EA58950E706ULL, 0xB0AA394DB740E9A2ULL, 0x65022E72A02072C0ULL, 0xE090F50B105BC051ULL
        }
    },
    {
        {
            0xDF2990618AD05AA4ULL, 0xF20FB653C5DC8AC0ULL, 0xE1B019D9C7E221E8ULL, 0xC9F73E5C5B00EFC3ULL, 
            0x45A0CD7FCA9B56DCULL, 0x4F741D883EBEC1DAULL, 0x1794485F3A52F511ULL, 0x571D9DED37DBD865ULL, 
            0x15AA4E2F88BBEE60ULL, 0x88FFAA288CDD9022ULL, 0x9ABC09E18E52BEE4ULL, 0x9FF7D29C9215CCC9ULL, 
            0x454A0F4D00D201C2ULL, 0xA6153C270DF4A26BULL, 0x3CA380D49EEC1193ULL, 0x91AF0F90C4248F68ULL, 
            0x2E483109BBB454BFULL, 0xA65F732E68DDFA2AULL, 0x286E315A3833EAE1ULL, 0x3BF58EC52A5148AFULL, 
            0x75E670580D8AD99FULL, 0xE1795E67BC885194ULL, 0xF1BDB9FC92A92D99ULL, 0xDD8BF9E7D74A7A37ULL, 
            0xEE5B27D69ED5D6C5ULL, 0xF0EC3A110E4673B1ULL, 0x427FA93E06AC8707ULL, 0xFB9D857199AEBF09ULL, 
            0xA93626A2A8293963ULL, 0xC5A832B09B713492ULL, 0x98DAD229974763F2ULL, 0xEC3ECEE2C23E3881ULL
        },
        {
            0x1D47817E5C2E4165ULL, 0x6C73288F8D4362B5ULL, 0xF1A98D0CFB36747BULL, 0xAE9071B801E0ADB4ULL, 
            0xC162CAD1F30AB5D3ULL, 0x266A76C83EF9B7E0ULL, 0xC4F532024E54380CULL, 0xD784F5DD30ADA978ULL, 
            0xD25698A2A0347BEBULL, 0xD5FEB7D5CF53586AULL, 0xA820541D7E56F48FULL, 0x5416C653BF6BFE49ULL, 
            0x760712D54F8DE1E3ULL, 0x98AEFBCB7A147DC5ULL, 0xA8EA3A3E9A57EF08ULL, 0xC073878BB5E82E75ULL, 
            0xF9514B53B3110524ULL, 0x7B6EA3386EF0BA95ULL, 0xB7A3A4C7EBBC212EULL, 0xA5207CF157D4D1C3ULL, 
            0x3261E02AA956E42CULL, 0x38CA6C308EC00C09ULL, 0xBDC71FDD39F7D5C9ULL, 0x41B245EFE089C2F8ULL, 
            0x0CF5BE154459A1DBULL, 0x0043E2E430B9A978ULL, 0xCF1152668E6C1001ULL, 0x6452E9230C08E21CULL, 
            0x2D637EF11752BDCDULL, 0x31AAD0D6981FBAA4ULL, 0xFFA6C06CF88CD3A5ULL, 0x9D4439FE01E8735EULL
        },
        {
            0x29E8F9AC3FC7B3A9ULL, 0x3FDB21B8A49F14ACULL, 0xACBE3B85BB59CAFDULL, 0x8E934DD14D029D34ULL, 
            0x8EC91D3206FA9324ULL, 0xA60F61EC9300DECAULL, 0xA3885AF8B31094ACULL, 0x0021D72F9624F615ULL, 
            0x5BD49C91F413CF39ULL, 0x2E3EC5503058002BULL, 0x05F705F568F7D880ULL, 0x7633FF3519121CBEULL, 
            0x58614BE254D7AD54ULL, 0x90E79EA368D18F34ULL, 0x447CB8A68EC84CADULL, 0xF9168D67E0FC87F4ULL, 
            0xB730F8FB2C33B1A9ULL, 0xAAE7416B99B23968ULL, 0x3E15C816E6E021D9ULL, 0x3D19723DC39FF442ULL, 
            0xD22F24BB20A7DA68ULL, 0xB92414C63764D244ULL, 0xE7CC5B83F428517CULL, 0xAF30CD8548EF0726ULL, 
            0xB16D072A7D5F50FBULL, 0xFA9482A25CCFA565ULL, 0x87E684611184F013ULL, 0x884D06AB78F39679ULL, 
            0xFB56AC44F4C5D023ULL, 0xF1D039B2584ECB4FULL, 0x01E0F20F40C3FDDCULL, 0x2FA3A58921996827ULL
        },
        {
            0xBC166F4F5DEAF665ULL, 0x58CFED55C09D0574ULL, 0xF785F694CC745BC1ULL, 0xB84426D83329E204ULL, 
            0x29C537B9DF73E49CULL, 0x2DF154D461B75932ULL, 0x0CCAB885563973AEULL, 0xF2EFD45252CC0306ULL, 
            0x7665FF421127A7F7ULL, 0xA5F825371D044520ULL, 0x8B1F6EDFC9DA6D32ULL, 0x4AE270E748923024ULL, 
            0xBAE5F6D8B869B1A7ULL, 0x6901F68080C66EBAULL, 0x4CD480AF87F9A8E7ULL, 0x472699C7FD29C16FULL, 
            0x75B98B39AEE8B300ULL, 0x01F1470D8672D1BEULL, 0xEC1313D78275DDE3ULL, 0xA8289EBFD864D245ULL, 
            0x672ACCA6FBC5B49FULL, 0xCDFE2BFA63DBF41EULL, 0x4931F253B6638666ULL, 0x359A35B3C8415D60ULL, 
            0xF7B9CF661CF739B5ULL, 0x39CA8CB73199BDC7ULL, 0xAD34277256B0F5D1ULL, 0x4FD4ADF673AAFC43ULL, 
            0x3AE525CA0AE04D9DULL, 0x8781420897D9DED9ULL, 0x1EAC1FE08D9B140CULL, 0x3CAE1B5E917A0445ULL
        },
        {
            0xE91A0883E87767B1ULL, 0xCFD3E1889F5666E0ULL, 0x8066D24DF1876608ULL, 0x073E9D7B276BABD1ULL, 
            0xAB0D89E21BC9915BULL, 0x1AD4820BE8E7F53DULL, 0xAF219E169BDF33F3ULL, 0x86568DF020A138E8ULL, 
            0x8E93D0D06A3C6AFCULL, 0x1534EA59158A29D0ULL, 0x624C224C9D8524FBULL, 0x99E0CF15F12D61EEULL, 
            0x8D677B7E73ECE529ULL, 0x97075492FD032B5CULL, 0x07F4330386ED93A9ULL, 0xF9E9D57CACF68970ULL, 
            0x7E1B3E94F0800812ULL, 0x0D483F8A179DC898ULL, 0x7AFA78D7ADC9A415ULL, 0xA4083CC1987005FDULL, 
            0x47B9B6E85DB6E489ULL, 0x9A3715B7DA95330EULL, 0x90A2144CA4E8FCC7ULL, 0x2BF126A9675C5AB1ULL, 
            0x9ABCE72A5B7DE204ULL, 0xBD6B31416299FE64ULL, 0xA1C2354F9F66B2C2ULL, 0x5AEDF13821201038ULL, 
            0x595F15EED482220DULL, 0x6F5859828597EA37ULL, 0xFB7DA49022FCC6E5ULL, 0xD86843B4ABE956F4ULL
        },
        {
            0x0BF2585C2950F7FBULL, 0xF7442A3E3A788611ULL, 0xF5573234B1843D52ULL, 0xD1FBFC850D73745FULL, 
            0xD2186CBCCDFD02C2ULL, 0x5F615653CEE7E829ULL, 0xE2AFF6A61F1D0EFDULL, 0x9297BBC272D9A1E6ULL, 
            0xB51397D0468C417DULL, 0x438A96A73A1356BCULL, 0x01B2DC472781FADEULL, 0xF7C78477A609034FULL, 
            0x44E1C40135049E4BULL, 0x819534333CC88C9AULL, 0x55B6B56E71C493B6ULL, 0xE95981661B151F8EULL, 
            0x7EF5035152A48065ULL, 0x5B63734F9BFF3B69ULL, 0xD34CE765B798B4EAULL, 0xF987DE8AA89A5BF5ULL, 
            0x95D855090D59A615ULL, 0xC5C3F878171D5A94ULL, 0x1C9F67763E5A2C20ULL, 0x84091F18BF7E4249ULL, 
            0xD9FF671519698D26ULL, 0x6DD91280F14BA5BBULL, 0x0608101B36A33D2EULL, 0xCFA4C30FA07A7836ULL, 
            0xC3768D911298C81BULL, 0x8BADCF531999352CULL, 0x136BA45C02267422ULL, 0xB34B30F7174B57E3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseAConstants = {
    0xD3AD3FB446E9DBA4ULL,
    0xEC62343F2CACD50AULL,
    0xE9D2D255F8EFA60EULL,
    0xD3AD3FB446E9DBA4ULL,
    0xEC62343F2CACD50AULL,
    0xE9D2D255F8EFA60EULL,
    0xA7C55BC2DCA2A228ULL,
    0x000B0682B6E7D794ULL,
    0xE7,
    0xB6,
    0x33,
    0xE7,
    0xCD,
    0xD9,
    0x22,
    0x81
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseBSalts = {
    {
        {
            0x77CD17746923E408ULL, 0x25B8DD359DC328F4ULL, 0x99F0C317C0628FA5ULL, 0x80C6C3B47A62C5EFULL, 
            0xE6B823694E886010ULL, 0xB7D61BDCDC43922AULL, 0xB7A0FF5AFD6FBEFDULL, 0x751DB151F8919D4AULL, 
            0x5FB8A2222A2AF92AULL, 0x01EE372C358AF0D9ULL, 0x1D9A349968C055DAULL, 0x6C6CC71B7BCE8274ULL, 
            0xE83A10D2F80C8435ULL, 0x6AD2236E98D19EB6ULL, 0xEA8D8BE82C2FA8F4ULL, 0x37F1E6A2B409CF2CULL, 
            0x93A7E19935BB7EFCULL, 0xCBAE0B0BA4A10E90ULL, 0x016937BDDE535511ULL, 0x4628F2FE8DCEEC50ULL, 
            0x98AE60054E6FA15FULL, 0x7C545DA7C56A988AULL, 0xF85350D59A05FF0FULL, 0x1B7BE5485D277ECBULL, 
            0x2F690D15643C4F89ULL, 0xB1ED9D2D926D1D9BULL, 0xF405739D1A68FFFFULL, 0x9B2BEE91157D4FB3ULL, 
            0x91B91227ADFC204BULL, 0xA994272DA4F39549ULL, 0x6E07B6321D1C0285ULL, 0x8041CA7ADDB50014ULL
        },
        {
            0xC6EC34B215994B8CULL, 0xE3B4C55F77E23BA5ULL, 0x01D92EB8E11C6F91ULL, 0xDF5834758F77CBF7ULL, 
            0x5A0B3A26E658AEE6ULL, 0x97C155FC87FD3B99ULL, 0xF1303819D95EA203ULL, 0x0CA4FD100B95F02EULL, 
            0xB045519F620FF169ULL, 0x36400E498DA84A5FULL, 0x417E245F382AF579ULL, 0x6906245541B96BC2ULL, 
            0x0D1E0B2E79A6DF41ULL, 0x756F41951A2F67BEULL, 0x2F98E2AACAF986EDULL, 0xA7B46689F85C6EECULL, 
            0x0B4FB913B16A1BACULL, 0x69C3E9596C10710DULL, 0x18EF43C1244E5B4AULL, 0xA33B7227AB374400ULL, 
            0x08447040C92B3994ULL, 0x2F5DE13DC2ACAD76ULL, 0xBC29DADD4296B3A5ULL, 0x9004257C36A2EC55ULL, 
            0x34BBCB42516ED65DULL, 0xB0BA27038BA7814CULL, 0xD117195890E479C5ULL, 0xA6615165CF06A59BULL, 
            0x7BD4A3BF5427A23FULL, 0x998EB65C0663C49EULL, 0x5D86C66BFDAFA484ULL, 0x98699125AF810657ULL
        },
        {
            0x2F1EEF5A1F468461ULL, 0xF0839D18BE414CF6ULL, 0xABA984DD40B632A1ULL, 0x4F4C2DFB30B10632ULL, 
            0xF4FD6518B17A9D58ULL, 0x67FCA04F11CA3958ULL, 0xF747449BDD347E52ULL, 0xC16DB7472A7BB85DULL, 
            0x8DC6F047CDF1F0EDULL, 0x8280EC97132F755CULL, 0x5AB240B16EC52997ULL, 0x6E8E5994C016D538ULL, 
            0x8AAFD128CB892B1DULL, 0x470D11333E809697ULL, 0x49237A8EE845F275ULL, 0x182DE5431A6D7A69ULL, 
            0x78B2B1E8DE69FB45ULL, 0xAB5DEB3D0A75DE70ULL, 0x6E2E918F81CC4884ULL, 0xB0CAE56268B804D1ULL, 
            0xE5D5105A1A6E5E90ULL, 0xE0B1C179A8249F06ULL, 0x284720434A3187CBULL, 0x85CC315FF7760810ULL, 
            0xC26CCA9427827935ULL, 0xE53879F67EC748EFULL, 0x302EBB8FB89E363EULL, 0x9FA83A9BAE2014A4ULL, 
            0xC7A0CC6FF8CFBC08ULL, 0x88BE0A712DFAFD10ULL, 0x28A376305F66F37FULL, 0x46CBCA4D38A3249CULL
        },
        {
            0x77016281812E4207ULL, 0x1C64E21FCE1C59E5ULL, 0xC2FEF83251DE24E8ULL, 0xEE825FC54797C528ULL, 
            0xF3BD51F7151E8C65ULL, 0xFB4D9C7E373A1C34ULL, 0x02EBABED85E1ECC2ULL, 0xE6968D5589168D22ULL, 
            0xC2A4CC3926D9D86AULL, 0x6A970D5B35269595ULL, 0x2834547C15A98AFEULL, 0x47E26890B9468D13ULL, 
            0xDB9491BB4D094C23ULL, 0x69D48E28D1706C35ULL, 0x4BDFF90D6BB93366ULL, 0x542DD050733CEDC9ULL, 
            0xC287AF1266463105ULL, 0xA14F43FE251BCA56ULL, 0x7EA9A6EBC888A972ULL, 0x74B53674C3ABF5D6ULL, 
            0x1866B502EFC0A7E9ULL, 0xF1B2580619475814ULL, 0xC2ED1E99027A61E2ULL, 0x171F326E54DA2E4CULL, 
            0x2E76DADDD814EB73ULL, 0x66066470C0869BC7ULL, 0x1D870BBBC170E439ULL, 0xCA59291DE28922EFULL, 
            0x66ED65B6831B44C6ULL, 0xF6641B13C9E02B3CULL, 0x5C3C4DA0E96A6956ULL, 0x6BCEECB11BF3605AULL
        },
        {
            0xA94335601B164FC3ULL, 0x8698B071E16E71C5ULL, 0x698CE6A7A18A4010ULL, 0x203211E5F27A66F4ULL, 
            0xB477304EAFB5502DULL, 0x510003F64A9DF5DFULL, 0x11B846CE46C9FA0FULL, 0x332C9991545AA593ULL, 
            0xB262DD189C1E53E2ULL, 0xDCFE96D16B1E00BEULL, 0xB4B821CA4B4B9A11ULL, 0xBFB74E52B4369B61ULL, 
            0xC68992BF3D776A0EULL, 0xB71883AF035F52A7ULL, 0xB5640F9833020F64ULL, 0x177E70D9473CE7F3ULL, 
            0x721012B745F1BCB0ULL, 0x7046EACE14D9A04FULL, 0xA7463D0C0C5815D3ULL, 0xF10FEA844BD0EBFEULL, 
            0x3BC242C40F34315AULL, 0xBD8B4AF3106E827FULL, 0x41BEE8CD9E5B111FULL, 0xDFD6C106CA0D0600ULL, 
            0xFE5E314EF6C95E20ULL, 0xC5A7C0DBEAC82440ULL, 0x09C207759D87A17AULL, 0xFEC14482A4BDA176ULL, 
            0xD78F2CAD531FDC6EULL, 0x823A3A69E34A2852ULL, 0xB258207B91D5BDA1ULL, 0xF46E3A77D4D64513ULL
        },
        {
            0x7975CCCE3B62F56BULL, 0x05FD7800DAF6034EULL, 0xBC6F3AC1A3010EA8ULL, 0x44F06BA0D95E52A3ULL, 
            0xDB9F97858775618DULL, 0xE54559C94A1D92AFULL, 0x8BDB05CFB8CE8911ULL, 0x8BB8431D37163734ULL, 
            0xC7E3572F63465A92ULL, 0x22511E3AEAD8FBC5ULL, 0xF8F4B55236CCF95FULL, 0xAF98D6CBE1E3DDFFULL, 
            0x926CFC052D88D77BULL, 0x061B09828532C82DULL, 0x65C7EB9B5362F8C5ULL, 0x57641CD16959881BULL, 
            0x56F73EDBA159CA6AULL, 0xF6E40096F187559FULL, 0x567430CAEA5363DEULL, 0x086F7F736036583DULL, 
            0x566FFE35E508CD53ULL, 0x498488BDC9CE9BCDULL, 0x9933A131364E0530ULL, 0x97A9E49C097767CCULL, 
            0xE61C4D5E397BC342ULL, 0x0D396CD7EA0D001DULL, 0x2D236AF234E538DCULL, 0x566242827A649B7AULL, 
            0x6F29AC08EBBD0852ULL, 0x1D8EF0E257FB5A84ULL, 0xC10D4E01CDA03FD7ULL, 0xFF6F3AFD7D1EBADCULL
        }
    },
    {
        {
            0x78D8F37494F38620ULL, 0xFA3EB72AAAD31C8BULL, 0x6491EEE0D30F7EE6ULL, 0x4FD9685004E05B9AULL, 
            0xA1155CB23AB193C6ULL, 0x1F21407C6993DB28ULL, 0x786BA2973695C61EULL, 0x52DE8A3A49B927B1ULL, 
            0xF79E5AC8EAEF7C32ULL, 0x840836EF8D258A69ULL, 0x21CD2D8B7E93A86AULL, 0xBE92D64F71EFA90FULL, 
            0x3C3085AE8F109A7AULL, 0xDDE59798782B4C0CULL, 0xAB7CBB3DDF91F088ULL, 0xF7BB58987E9C7035ULL, 
            0xEB75B20CFD99812DULL, 0x9019F04F3A4217EBULL, 0x92D52DFC0C35AFE1ULL, 0xC5017FFF5312D53AULL, 
            0x34480D95A2BA5C05ULL, 0x62D040DAE05DBEE1ULL, 0xCB58DA837C489B65ULL, 0x0ECCE2A3DC40A426ULL, 
            0x10D62D93A0312A88ULL, 0x484348948A36DE1FULL, 0xDC8BCB6A658DDA1BULL, 0x798564ECEEC3D84BULL, 
            0xFB6254AF612157C8ULL, 0xEBC4A9AEF3D680E1ULL, 0xC79D6139B0201CFBULL, 0xB2130E5E6722E70DULL
        },
        {
            0x0DDCC7AA660AE1C1ULL, 0x43751DA7B3EE903CULL, 0x2F46AA7EB2203139ULL, 0x722AFFB6B832C43FULL, 
            0xBD2517B9C8CDB5EAULL, 0xBD0A492966435A00ULL, 0x4A88D46D11886A88ULL, 0x983658D8CCA811DEULL, 
            0x6BD7E2828717B4C4ULL, 0xC4C2FDD67EA0BE0DULL, 0x0DF1BA23E2241990ULL, 0x05128A08790AF182ULL, 
            0x769E61E493E68186ULL, 0xB24384B54107066DULL, 0x30235C89F0FF37EEULL, 0x3AC8880128493383ULL, 
            0x60B3C2695D7D4086ULL, 0x138D8DEB1602698DULL, 0x58837CD39FE84ADAULL, 0x81D14094F041AE42ULL, 
            0xF877F7418DA04D32ULL, 0x6C79929484EE322AULL, 0x50266FFF1EBA3345ULL, 0xA5BC103844041642ULL, 
            0xF7FB5662D42580EBULL, 0x31EC24785237EA28ULL, 0x267C5C51C26AA323ULL, 0xD68AFF318950078CULL, 
            0xC98C7C7E4976FA4EULL, 0xEF7184B6C9ABCC3BULL, 0x11C6EB69B3775446ULL, 0x0E1053F1ED0D4D7BULL
        },
        {
            0xE1668F465D705773ULL, 0x289BCCC1DD9BDB18ULL, 0x5FEC81D79BFF2758ULL, 0x3D24465AE9CD7888ULL, 
            0x5F7C1B7E5D5EA7B9ULL, 0xBCE4B0A3C6993CACULL, 0xA98BED1B01CC9CFCULL, 0xE646356AD4FA1523ULL, 
            0x63798AEE548F4435ULL, 0xA0FF0BB21A88ADC9ULL, 0x6983EB761F448F87ULL, 0xC8E054468421CDCBULL, 
            0xBB46D7F8D4358B90ULL, 0x74DBE44BCAF68FEEULL, 0xD0643C48EB7FD562ULL, 0x1109CF1A6EF2FB78ULL, 
            0xE28CC2AA87BA96B5ULL, 0x99976EA8A975EFD7ULL, 0x5401A0296442CF14ULL, 0x79876C26C5F9E7CEULL, 
            0xFC80C19EDC092620ULL, 0xB0EDFC709117AD51ULL, 0x87D3D48F9AC225CAULL, 0xB83BB28E30817177ULL, 
            0x98AD5F09044D6CCEULL, 0x54D9B704714D20EBULL, 0x48B18E10E303054AULL, 0xBEED4E70FC7B6B57ULL, 
            0xC9804EA40928B9C2ULL, 0x2C6733BC65DD6538ULL, 0xCD053335E8FA096FULL, 0xDD43DB78912AA3CFULL
        },
        {
            0xD967D002DB406DDAULL, 0x6EFD0B64B211993FULL, 0x7795AD036367D1CBULL, 0xA67071FEA103B4DAULL, 
            0x28AE80D689101D0EULL, 0xA32D12B0759393B0ULL, 0xA971C13B06758B78ULL, 0xD0ADF9DD9A61EADFULL, 
            0x0B8643B690A64ABAULL, 0x72D6DEEAAD7F4F16ULL, 0xC133EC3D5E38993AULL, 0xB628123D8DFBCF03ULL, 
            0x8295A3E77D34FC72ULL, 0xFBEBF409D7757391ULL, 0x98ADF2CD3DFE25A6ULL, 0x7BE6B7A1792B1275ULL, 
            0xF836FE98AD8EB97DULL, 0x34765D46AF049263ULL, 0xD7E76E69340CF379ULL, 0x697CF7CC968CA77AULL, 
            0x8FF56A2C3F738D4AULL, 0x81369BE701708948ULL, 0xD80AAEEDBF49681BULL, 0xFAB0B1ABFAA2D061ULL, 
            0x9673DBC4DE1EF71BULL, 0x12A43255698348E8ULL, 0x7B5860442FA0CB21ULL, 0xB0A90BAB3801C066ULL, 
            0x9154114A55632D78ULL, 0x927411376247739AULL, 0x3CF3D7F6354CE47AULL, 0x569CCF768F421174ULL
        },
        {
            0x573DAA8FFE1EC3AAULL, 0x60F7F9FD036C5D3AULL, 0xFE6C5430341FB374ULL, 0xE290570D2911C06DULL, 
            0x84C4DAEAD0A58187ULL, 0x86F1502BBFC18F37ULL, 0xD2B4031D3B0E510BULL, 0xE272DAF7F2F22F96ULL, 
            0xB50E99F02D2F4C6CULL, 0xF0B6B3A499EE371CULL, 0xD690A2B691E6E5C9ULL, 0x281AD64C3C862B8EULL, 
            0x9BA22389E7C8A2B0ULL, 0x9A593F7F5CECDFFDULL, 0xD4389F01B5B2A69AULL, 0xA04C7C4549AECD24ULL, 
            0x2A5DB7D75C4C2AFDULL, 0x4BE19C932DDCE074ULL, 0xABDDA7E27502CC47ULL, 0xA82C5A4B495848ABULL, 
            0x2A7B149673A5D502ULL, 0xF86712C63867ED26ULL, 0xF587CC86ADDCC011ULL, 0x9638EF43A7F084A8ULL, 
            0x083D72E9221B2416ULL, 0x25C3C0872E7689F0ULL, 0x4F1FC30BEB5F8DE1ULL, 0xA9287881EA73D459ULL, 
            0x569A528E0C73D12FULL, 0x0C60D37C8436BCC9ULL, 0xEF9A0175D8AE4FC5ULL, 0xF0EB8340D0816B2DULL
        },
        {
            0xC45A33811B40699CULL, 0x26E37287F0A648E7ULL, 0x36799BB840A932EAULL, 0xD1F1A3D295C7EDDEULL, 
            0xF8875CC3BF147187ULL, 0xC6B2431B34564135ULL, 0xEB82EA1BD3F2708AULL, 0xC4D3C458934637F4ULL, 
            0xBA9D00DD03037A0BULL, 0x5879D4F19F115BD9ULL, 0x4AFA4D7BECF913F6ULL, 0xA080D04E1187120DULL, 
            0xD76FD33BD11EC59DULL, 0x407B2CDA407AB11DULL, 0x9448767039702CC1ULL, 0x09CBE934879237B3ULL, 
            0x8C698B8DF185D6E0ULL, 0x3A9901536C16058AULL, 0x5EDFF9A0B811AB0EULL, 0x25F29B66FC44FDFBULL, 
            0x304B3EBEE0B36244ULL, 0x53BA3295406AFE97ULL, 0x02C5FCB7EAA56C62ULL, 0x0323A5509A05A477ULL, 
            0x499AADEC98EF4665ULL, 0x976361B3AD70069DULL, 0x7FB0C4775B510AC8ULL, 0xEE6C07FF8F29BC65ULL, 
            0x96FBDD7777FEFA1AULL, 0x7F513B44EDDCCB32ULL, 0x851575B7ACB181E3ULL, 0x8A39DCA3FBE768DAULL
        }
    },
    {
        {
            0x83739BE15829EA61ULL, 0xB00AEDC7FDD7BE22ULL, 0xF18C9354493DDD1DULL, 0x5C3A6ED226B559CAULL, 
            0x13B9B52D8D10B316ULL, 0x313A2AC0063C4C42ULL, 0x111D527FF995EAC4ULL, 0x898F91A59399B9E2ULL, 
            0xD747344BF8331563ULL, 0x993D6A7B98FFBF21ULL, 0xEB0A7A87292B582DULL, 0x91EA3165AEFF0764ULL, 
            0x5662FC984958E525ULL, 0xE0661087CA68D746ULL, 0x19EDCF95017E783DULL, 0x2A559BB92DAF3EB7ULL, 
            0xDA45759C1494AA3EULL, 0x368B27124E7304E3ULL, 0x290FAA04C1530DD4ULL, 0x777B1D0FFA005742ULL, 
            0x347BF24C5CA456B8ULL, 0x0BD785AFC1062CDFULL, 0xD2F5745BA29D3402ULL, 0xF5731ED9823023E2ULL, 
            0xAA32561871885063ULL, 0x861EEDCF8D5ECF1CULL, 0x6385E335BD32BA62ULL, 0x2B1E881A2A6F54CBULL, 
            0x5EDDC6C66A1042DAULL, 0xA65032A4CB4A91FBULL, 0xAACA2D9D2385A0D5ULL, 0xDEB6CC7437B584B0ULL
        },
        {
            0x859D9B01EE483B3DULL, 0xBAC193779CA7EDF8ULL, 0xBD19C426007D6BFCULL, 0x95C5DA94414FBF10ULL, 
            0x55A9CB0F6809CF10ULL, 0x83E9B232BB254A1EULL, 0xB269DC6BD80B95F8ULL, 0xA7EC0C63CD9375D9ULL, 
            0xD56CDC41D31AD7A5ULL, 0x1AFFB3F7D66BA556ULL, 0xE3E5FA9E34F631D7ULL, 0xDB27555B6FA3C082ULL, 
            0xE6252EDAEBFB25EDULL, 0x37E5F0C0102E4B95ULL, 0x43DE7834F356C4D2ULL, 0xAA14AF1F9ADD313BULL, 
            0x50E91E54E3881821ULL, 0xD6A5712DD5B2B176ULL, 0xC50FF4E6D45CBEB8ULL, 0xA48B8218CA1F901EULL, 
            0xA99A2902C0753850ULL, 0xC81F114D8323A294ULL, 0x7543C5CB31D9F4CBULL, 0x4284F3FAB150E24EULL, 
            0x3939F41FF682FA85ULL, 0x93275D58529D38A1ULL, 0x00C96366C6F71E58ULL, 0x9C01795CD5D77F10ULL, 
            0x039F57A8EFE8B07BULL, 0x57E263E34BD820C2ULL, 0x45716DD5E9702A8CULL, 0xFD2D4B35F04C9FFEULL
        },
        {
            0xB23496AA5F0B67ABULL, 0xD480C8E7D957DA38ULL, 0x3240B51EF702A8D5ULL, 0xE3840149BEBD0E78ULL, 
            0xDA2D06C7AD5BA93CULL, 0xAC2DA39DE23C8D2BULL, 0x9FA55CDD20CEAAC2ULL, 0x27A48E7EB9034AA3ULL, 
            0xD08D93C6B540A6ADULL, 0x9BD2D5F8F457E0EEULL, 0x7F1DAC1E48D99B29ULL, 0xDD2E3BECD1E40C6CULL, 
            0x1FF4587E1F7F2E3EULL, 0x062811EF8501E77AULL, 0x2C5B8129ABADDE72ULL, 0xEBCFE0AE13FA4A81ULL, 
            0x832C4556EA0230FBULL, 0x9D0EDCDE0F91B1ECULL, 0x4B1A916D10E39CCCULL, 0x72D3B52291334325ULL, 
            0x1D66BAE62B26887FULL, 0x2118926F6306AAEAULL, 0xE223D105A8A48D72ULL, 0x3154B10C7C55FCE5ULL, 
            0x4CF3DB48D6786FA0ULL, 0x3A94D6B6E3288E59ULL, 0x061804693C35DD6DULL, 0xCE3EDC7814782B65ULL, 
            0x389455BF39656A91ULL, 0xD6199A2AE8BF4314ULL, 0x8FF72A103C43EB17ULL, 0xD160E0907237CB07ULL
        },
        {
            0xF696B2C504DFB16CULL, 0xBCDEB8B8B993D698ULL, 0xB01F1EA4FA6238E2ULL, 0x729224D648590CB1ULL, 
            0x94C6D7FE6E0EB479ULL, 0xEED58E69F0ACC65BULL, 0xFFC9AA86639F3024ULL, 0x669DE09E0DD848B9ULL, 
            0xBF10867E6AF2FF8FULL, 0x56E4C7BAABFB5E3FULL, 0x0229439AF33092D1ULL, 0xA3EF8FBA18B90EFFULL, 
            0xF9BD74295C9F0178ULL, 0x16F732B05DD3D74DULL, 0x6B97E55CD9BC31FDULL, 0xB18FFBFC57648FC3ULL, 
            0x40CA3B98BA73DDA6ULL, 0xE06D2AC36D441D51ULL, 0xF34A0672E426D5DEULL, 0xBD0340BA3DFC6355ULL, 
            0x8556186E2E23F114ULL, 0xB080828CF2E49DCBULL, 0x04C133603BECE3F5ULL, 0x5CB2B3379F75283EULL, 
            0xC5D913B8839EBE6BULL, 0xA0A9AB7DE20D3790ULL, 0x04BCDD7EA462EC14ULL, 0x5A8C7F8164411AB0ULL, 
            0x2B53354BF0ECAB2BULL, 0xAFBED92E554A9572ULL, 0x4499B7863475A35EULL, 0x650863F4625B815EULL
        },
        {
            0x3C1054F11C0278B5ULL, 0x48A71C37DABC623DULL, 0x9E65F3A4D4C3BCBDULL, 0x217DB2F9BB5CBB0DULL, 
            0xD8BBA491190BCD50ULL, 0x1CF23EF88910D245ULL, 0x67437A44DDE2F69EULL, 0x47DC2A17A94BEEF3ULL, 
            0x278C2AFC23096C7BULL, 0x9582E87D7B04067AULL, 0x6206F770498202F9ULL, 0x9C2A02CDC6A472C2ULL, 
            0x4EF116068A854FCEULL, 0xBC3BDAA9562F013CULL, 0x6FF2E460A68A0D55ULL, 0x3F8E1DA8821AFE12ULL, 
            0x8306D63C4FDE5E3BULL, 0xD0CBF9C589CF4E44ULL, 0xB790CBD4833C2EFBULL, 0xDBF652B2A9E4CA4AULL, 
            0xDA00640CDE26AF6EULL, 0x97593D30F9350956ULL, 0xAE2921AA9E0CB7B2ULL, 0x0E40F8EF4ABF9769ULL, 
            0x26E6CCCAC1515E1CULL, 0x8F2225A907BA45A8ULL, 0x3C57BC7696EA8329ULL, 0x7593C5C9473DCD8CULL, 
            0x726AD01BD87BD2F8ULL, 0xCC29C23D1A36B994ULL, 0x222B8D41B6E3017AULL, 0xD674BD74979C2E74ULL
        },
        {
            0xBEAFB14F8D8FAC73ULL, 0xE3147DB45B51C00AULL, 0x25178645EDC691AEULL, 0xF64CB6B805395645ULL, 
            0xDCFBECE5006F2DACULL, 0xAB86FAB6A34647B9ULL, 0x0399E38659CB8766ULL, 0x28E2C8F8B418F1CDULL, 
            0x89E49F2BD031BDAEULL, 0xDBD81A0291778A58ULL, 0x85650F0CEA89AB36ULL, 0x48A01D1073E99773ULL, 
            0xE0942CC8C174B70EULL, 0x54810DD92F8D9323ULL, 0x8539D27DF25F0C0CULL, 0xA47A49CB58AE534BULL, 
            0x8100050BB25D7D8AULL, 0xDF1F50BED9F5CD4EULL, 0x5A582E7E92E5EA71ULL, 0x6B6DB10CB6731133ULL, 
            0x2854FFE225AFAA00ULL, 0x9958DB2178FD3BB6ULL, 0xBC022759F108F958ULL, 0x69F798CD4E7A3D7FULL, 
            0xD425BE38FA767296ULL, 0xFB06C5C77521C47AULL, 0xF635D48E1FA53A15ULL, 0x0FCA2CD6BA36D81CULL, 
            0x9E8B7830E6C1926DULL, 0xAE18766F015DB865ULL, 0x43A873055B4D9AA2ULL, 0x6D5E3139666ED023ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseBConstants = {
    0xAA91B75AB142DD59ULL,
    0x57ABA30D1241C7BAULL,
    0x0A7F1D869C161C88ULL,
    0xAA91B75AB142DD59ULL,
    0x57ABA30D1241C7BAULL,
    0x0A7F1D869C161C88ULL,
    0x643D317852A46E20ULL,
    0xAEC504D1CB4B0201ULL,
    0xDB,
    0xC9,
    0xA7,
    0xB2,
    0x24,
    0xDC,
    0xF0,
    0x11
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseCSalts = {
    {
        {
            0x73520BCCBCC6F594ULL, 0xF054CB419B5D34EAULL, 0xB17902174060289BULL, 0xDB21CD38F7D1D0A8ULL, 
            0x59C9FDAF6AE26C2DULL, 0x779765B7B36FD218ULL, 0x187976CEAAE41C7EULL, 0xD7F70C1163D70ECBULL, 
            0xBDB9CB36F8F26D36ULL, 0xFE00C0A839606E3BULL, 0x83E8080D03286357ULL, 0xF40EDFE7DBE0B502ULL, 
            0x4B04A7E705B58FB3ULL, 0x551C0E7B224C65A6ULL, 0x441BBF24279C9012ULL, 0xF28FB28D1B07539FULL, 
            0x62003C8C6BC0E8E0ULL, 0x662034BC938DD0A2ULL, 0xDAF5DAD2C3173E7AULL, 0x611271428A3E958FULL, 
            0x046F249D083603ABULL, 0xC4F3BA4320E32031ULL, 0x317AEC21DAB7890FULL, 0xED06347E989C578EULL, 
            0x10496EBF8EC6CC6FULL, 0xF78C9EC5EFFDD831ULL, 0xCB6A3B5D840D4AB5ULL, 0x0B95DE68C7AEA87FULL, 
            0xC530C117ECDA5A1AULL, 0xF0BAEBC91122A279ULL, 0x1832D68038535877ULL, 0xD9CB8007527121FDULL
        },
        {
            0x76F4484542AEA7B0ULL, 0xC327473BAD0441F5ULL, 0x9712B3B4CD6155E8ULL, 0x4359A27C0F2CF43EULL, 
            0x07125FA934111E5FULL, 0x61D3B63E46C8E3D8ULL, 0xACEF08D4B498E585ULL, 0xDD043D0A7C592DEFULL, 
            0x229E97B9A4572672ULL, 0xCDDC1483EADF472DULL, 0x35CCF3C1D027A1EEULL, 0x523FD2F61F2AD17FULL, 
            0x0183275557C3058CULL, 0x5149BB71BF5C34DBULL, 0x0B470B7B1695DCABULL, 0x799D6FA1E5053496ULL, 
            0x42E0F4A49AA9D894ULL, 0x1E879F98EC5275D6ULL, 0xDC7DBA3B01395226ULL, 0xBAB5F422B7C67264ULL, 
            0xC856B10E9719D875ULL, 0xDF652F285E1F0CD5ULL, 0x9C76DF6732546E0EULL, 0x5E226A9D01106AFCULL, 
            0x2E143039C93880EBULL, 0x9209E6E7C0A3A2DFULL, 0xA8D381F9F5B4B7A0ULL, 0xB6D86DF396AB336CULL, 
            0x9CE16CE042A86F1EULL, 0x3F173E9766C8C3D9ULL, 0xA16B200C1825E184ULL, 0x12934B0BFAB08449ULL
        },
        {
            0xF312BC2AEE6C15BDULL, 0xEBC4D247C1353B50ULL, 0x192919B5DE055939ULL, 0x187E02E12B710CAFULL, 
            0xDB40BDA03016AFB2ULL, 0x0E67EC7579504761ULL, 0x66C0BBD17ECA73E9ULL, 0xCB45422F8C7ADD1BULL, 
            0xB220744B60161188ULL, 0x1FECF18217A08A1BULL, 0x78BF7D3A2E36B59AULL, 0x99F48173B657E3D2ULL, 
            0x8AF1DF2F96E00447ULL, 0xDD2885010E8CDAE6ULL, 0x8CC2CCBFFA059EE9ULL, 0x8241F07673D08BDEULL, 
            0xD42249D3C5AA87B9ULL, 0xB23ACBF76687B063ULL, 0x0E06601C1A5B77B3ULL, 0x5B38F8861FB4AE93ULL, 
            0x47353CBC6AE6BCEFULL, 0x781257169D48DF05ULL, 0xCDE802827E6BE7F7ULL, 0xE6E798BB12F57640ULL, 
            0xFE16C0B9EE88226EULL, 0xFB316103DC45F678ULL, 0xB5D608BE71EB8C9FULL, 0xFF2D1CA12022DC81ULL, 
            0x1AB99A42244F84D5ULL, 0x772D265084A29EF2ULL, 0x6E33FB73F7FA71B8ULL, 0x9D1CE1668CA230F0ULL
        },
        {
            0x9777DB1DAEE2727BULL, 0x47C5170065B52A15ULL, 0x29C749B38D836A72ULL, 0xC01CF62C76874E2CULL, 
            0xD326E680EC504788ULL, 0xA5995014B6354770ULL, 0x0F16037AF8143142ULL, 0x7706C91C1CF3195AULL, 
            0xDBFF42489A74BF7EULL, 0x4ED6D511279BAD04ULL, 0x1F13147B1A545FBBULL, 0x39415C5A30A8EB28ULL, 
            0x7EA6F9064C0B11E9ULL, 0x135ECB295D9B6C11ULL, 0x059C9F73B226231BULL, 0x0D48EEE14D27A90CULL, 
            0x50D83AA386FA3089ULL, 0x9EE2CF39E61F54ECULL, 0xD2352A67203E512AULL, 0x87AA0C09D17A2998ULL, 
            0x4F217AAE973D38FFULL, 0xC11C69EFBA62B770ULL, 0xA44E4A8243EA06BAULL, 0x35E9A800C238A6FEULL, 
            0xC9A8A06937967CF0ULL, 0x1C9C718BA55F9F3DULL, 0xA16DF2AC5DA8EF25ULL, 0x632257BBFA5A434DULL, 
            0xDDD555860FAE1ED3ULL, 0x854ED58EA8AF9EAAULL, 0x18D30AE30677E2ADULL, 0x80A33EBD63FB5E33ULL
        },
        {
            0x04DFFEAC7BA35FCAULL, 0xD71BCE2B729DC43EULL, 0xE872D483B52E3BABULL, 0x3FD0BF3525109561ULL, 
            0xCBBD47745F969132ULL, 0xF31BFE34F2954703ULL, 0xB4D793F763142929ULL, 0x2334D7C0D8FA5B80ULL, 
            0x8030AF7BE93DF845ULL, 0x2524F805AFA0EEC2ULL, 0xE8F558DF3484FA3FULL, 0xFF2D18FE94CBFDABULL, 
            0x2214FADD6B85FD2CULL, 0x62F9B5C7E0C9E379ULL, 0x6560C93BDC3CA11EULL, 0xBE84B8D34212707EULL, 
            0xB660EC747B2131FBULL, 0x38A78A29F72392ECULL, 0xB820B5D3A2EA2DD2ULL, 0x4AD0CD70A7FCFC0CULL, 
            0xF8D3C3BB2318929DULL, 0xED24277FE2C834E4ULL, 0xDD4164987B35E839ULL, 0x69F8681FCE9C3A24ULL, 
            0x3B37F3EDE2C67D2DULL, 0x527857B13ECA7800ULL, 0xE95337B6C4079C0BULL, 0xE54005337A44D04DULL, 
            0x3158EF330BF4D245ULL, 0x93A83E0E191E0AF1ULL, 0xF68861BF23010C68ULL, 0x9D0D01BE500B0F3FULL
        },
        {
            0x9C32E8B43344A604ULL, 0x08CD68668D86C65BULL, 0xF2BB0E587CBAB9EFULL, 0xB8B2A640EB2DF3F5ULL, 
            0x256EA039E616E2FCULL, 0x4C0C9566BEE2A4D4ULL, 0x40E5BE02AE7C81DCULL, 0x834E0CD5181FD875ULL, 
            0x413269218B6EDF7BULL, 0xAAA1D3AFC1A3D95CULL, 0xAB242FCE246B6A1FULL, 0x73A8E78109834F98ULL, 
            0x73BE005D1D6787EBULL, 0x29EF49CAA8CE6E0EULL, 0x870A0E068889BB0DULL, 0x1367BF80CE2DFF44ULL, 
            0x4D6C2002F60C8617ULL, 0xD36C34F3D2D9831DULL, 0x38A9E34459141273ULL, 0x2A43BB086813C426ULL, 
            0x0CE2B62BC4910D1BULL, 0xA248FEB825FFC04DULL, 0x98379582216CF292ULL, 0x660C189B159B35AAULL, 
            0xFDF2ECDEF9C4D908ULL, 0x8671ED82C1ED4485ULL, 0x46B4E40E50426D58ULL, 0x67A5500B3EEA727FULL, 
            0x91EFE269D2ADDB1BULL, 0xA2308D9114E5C40AULL, 0x4941BA80C77C602EULL, 0x2A7E0D1A8437E577ULL
        }
    },
    {
        {
            0x1AC59F02D491D400ULL, 0x29782CD8D67C7C12ULL, 0xB469580CF9687C1CULL, 0x488E029EFC301EBAULL, 
            0xDB9ABD9EA2ED5E0FULL, 0xBA90061A91933F53ULL, 0x91CA17AA574D2406ULL, 0xA84015F84389C8A6ULL, 
            0xB79EA9C3597D8588ULL, 0x128C03C8331CEDCDULL, 0xF5E361A5098D9BC1ULL, 0x2D9AF499AC982D75ULL, 
            0xD055B099EB6FF389ULL, 0x5EC93090DDD6FC85ULL, 0x2BADEFBE07F2A622ULL, 0x59D2283E0AFB62DDULL, 
            0x6A2AFC7FF06433DFULL, 0x78B5BFDD759B3286ULL, 0x3EEF309A5293356FULL, 0xD55A9C8952E63EEAULL, 
            0xDF5AC90326A86EC5ULL, 0xECFF8D1637393625ULL, 0x195BB7EC5ABF69FDULL, 0x2990FAFBD86DA13BULL, 
            0x6BE218D792D258D9ULL, 0x1E4F41C7A72422DCULL, 0x1FEF8DE4B51F928CULL, 0x2EACC1E32784BEE6ULL, 
            0x9F55CA34E0E60105ULL, 0x397F29BE695B271FULL, 0x6D79BA9D6109A1F5ULL, 0xFFCF24CEE60371A0ULL
        },
        {
            0xA58A3F2CC62D4CBEULL, 0xC21C28999EBDE150ULL, 0x8776C35C8650A30DULL, 0x4CC31A48E7341C12ULL, 
            0xD68C1D0708F342A1ULL, 0x53C493A7D35C0F16ULL, 0xDE04A5D187A5B62BULL, 0xBD935371A277512FULL, 
            0xC6A297E6A22DAC72ULL, 0xC5757A0A6A92857DULL, 0x2148740E45FF88BFULL, 0x099CD5E7993C5C10ULL, 
            0xC906BCEA7D34E2C6ULL, 0xBD704D3C92A5A517ULL, 0x516DFC3965DC953FULL, 0xEA23BAA0269AF770ULL, 
            0x1EF0071B3E747E19ULL, 0xCC639922EDB754FEULL, 0xFD244AEE999573FDULL, 0xBE803B58274E037AULL, 
            0x800020CBF45D8983ULL, 0x53BE664DD90C4717ULL, 0xCCEE9D1FB06B7A2EULL, 0xB202AC233E59F04CULL, 
            0xB36BD9BDE61170F6ULL, 0x8F4CF93B2802850DULL, 0x2AD4FD4D2A9EFBC6ULL, 0x61BC0ACE857CC445ULL, 
            0x843887574E88DBEBULL, 0xFEBA3DB13F433067ULL, 0xE4AF450C7DFDC7D9ULL, 0xF63ED9C0885F7A04ULL
        },
        {
            0xE9CCB5BE94FBE5D7ULL, 0xAF39959495D5CA92ULL, 0x66E85A10ED25CC9BULL, 0x194A56EAAF2359F9ULL, 
            0x60E4CA7113F82505ULL, 0x74150CAB9ABC14A2ULL, 0xF66AC738B57E0429ULL, 0x1ECA7EE15BAB3917ULL, 
            0x731083C27900C39DULL, 0x7E5009078783F106ULL, 0x9D43D78607BCEBF8ULL, 0x26434D1260745827ULL, 
            0xC50211A45F4D4147ULL, 0x72FCE427A041AA38ULL, 0x705D59208A1E96EBULL, 0xCB2C1AFF0A8F0152ULL, 
            0xE48BBE967376319FULL, 0x3CBC0DB4DC453B26ULL, 0xD5D8E3712B1E8D9EULL, 0xE33590540AD8EA6AULL, 
            0x518DE3BB020CE10BULL, 0x0BAA6562134FB576ULL, 0x7A5F30AC22A61781ULL, 0x3794C0D1A68A44ACULL, 
            0x697047E07C6D403EULL, 0xFD5280B861055E08ULL, 0xA1546E835F55864BULL, 0x59BF082EC7ADFDC5ULL, 
            0xAB21E8170A99E2C8ULL, 0x2A443EE272D24B0DULL, 0x0239965D9D73DA03ULL, 0x54F46D0E5328F372ULL
        },
        {
            0x3A3A48C9CBF4DDA3ULL, 0xB5FFCF41250A6D8EULL, 0x3FA07E91A21362A5ULL, 0x54C9164ACF29B80AULL, 
            0xEAD92BCD0C2872CDULL, 0x1A0D43FA58FAE0EDULL, 0x257C9B1F28C6879BULL, 0xBE0F815B0982F8ECULL, 
            0x19803FBCB3F8932DULL, 0x5FE65D3EF3D03E14ULL, 0xC002F9F8C0661F11ULL, 0x28E134B5EFD4B171ULL, 
            0x7DD01F3EAC497CCCULL, 0x3583ED1FCED6251DULL, 0x70C6A1762D0A432AULL, 0x780A5D000ECFAA80ULL, 
            0x1C62F17D56EEE7B8ULL, 0xC85EB5114322FA1EULL, 0x7F31AC9239A80987ULL, 0xF27157CF56916DE2ULL, 
            0x32D6FED43548AB24ULL, 0x9B252D4399593285ULL, 0x3640ACE3FED8B22AULL, 0x8F200A3D841D40F4ULL, 
            0xF51ABAED3499A105ULL, 0x4DF8809AA7414EB9ULL, 0xB86127A4343DC0B4ULL, 0xA59A3BF674AE75C3ULL, 
            0x7534FC50BEDCF8B4ULL, 0xC9BDB530EBC04BC1ULL, 0x1C9D9398246BD833ULL, 0xD41ED296F489AC10ULL
        },
        {
            0x21893E6B5077A1E3ULL, 0x7E67479714B1DE20ULL, 0x2BBEE7454A7E3AA8ULL, 0xB69CE2EDCE817982ULL, 
            0xE894F794BD4567B0ULL, 0xF7FD44B544800B91ULL, 0xC0472E43D35CA4D5ULL, 0x2933A7A730FF06C8ULL, 
            0x15043B39CAFA6434ULL, 0xBF5DB0A73DA2CAD2ULL, 0xA9D615F04DB034D4ULL, 0x04DBC2553A3060AAULL, 
            0x77BA30AA976D5E47ULL, 0x7F164FE03065AEF8ULL, 0x459AE7B29DF988DBULL, 0x7CEC1C3839460ECCULL, 
            0x455D1EC74B230F68ULL, 0x8749AA9881901597ULL, 0xA5DEF099B4CDF734ULL, 0x1200489B6104BE6DULL, 
            0x947168ABD7087CEBULL, 0x153B9EA769758579ULL, 0x717868895CEC0B01ULL, 0x6F2B8D910360CC13ULL, 
            0x1863B74E69D2955DULL, 0xAE50432EA699EBF1ULL, 0xC954F2FBF814F940ULL, 0x3B123C2E49D7601EULL, 
            0xFC39FD1C8E6068C2ULL, 0xE1A489D989ED3EE6ULL, 0x9564FBC4541BBD31ULL, 0x7AB688557ED65906ULL
        },
        {
            0x1D40EE75EAC3E40CULL, 0x015AFBABA59BED15ULL, 0x9A84506A2F0C59CDULL, 0xFD0670D366464804ULL, 
            0xF8E54D659E96B1F2ULL, 0xAC7F29A15C3751C0ULL, 0xF3C87C7CBBB18DECULL, 0x5E475077609A0D9FULL, 
            0xDC31767F55115273ULL, 0xEFAFB735EA84F0E8ULL, 0x27143DC75CE3A618ULL, 0x1ED3E48139979BAEULL, 
            0x47A1F22D6FC29785ULL, 0x033853D751733E8DULL, 0x303A576EED2C726AULL, 0x0F1EEB3098CAFAD0ULL, 
            0x6623E40A35C926A5ULL, 0x941C4849F9B7D039ULL, 0x9B22FADCCF82D960ULL, 0x66E0AEEC0B6E458DULL, 
            0xA0F3F19EF7B5EB29ULL, 0x0A5B8EF059ED840CULL, 0x8CBF3CBEE0D4CE36ULL, 0x966E4DF97AD7F015ULL, 
            0xAF1022A0899B0554ULL, 0x12BBEE21E90ED3BCULL, 0xAAE0B4F61E7D365FULL, 0xF8E6A5D55830F3DDULL, 
            0x7BC6A2F0707C3267ULL, 0x996A7FBEC0AEB73BULL, 0x3BC5E6EE66B60220ULL, 0x7D596520EF95A25BULL
        }
    },
    {
        {
            0xAA33AF05AED965C2ULL, 0xE2715E2A4944E00BULL, 0x3A6839136B8B89B5ULL, 0x0FE9F33BCA10E89DULL, 
            0xC0F6D354ADD0E97EULL, 0xF46E490266145F5DULL, 0xFDB07FDDEB6F862AULL, 0xFD2D9FA107C23A87ULL, 
            0x1E34F9D3E0BDCFDBULL, 0x96884F81B294AF1EULL, 0xDCB24FBBA167B190ULL, 0x096743CED5C45E94ULL, 
            0x683910C54AEE3FD8ULL, 0xEE71CE00766F4289ULL, 0x4EA481D594FAA244ULL, 0xD997B89B59BE5A7BULL, 
            0x114FD11504356C37ULL, 0x1DC9A75DA0628675ULL, 0x7DDB6095CC4305D7ULL, 0x49C4B79E756C591BULL, 
            0xE659A875FFCF1611ULL, 0x15F0C5CDBA327784ULL, 0x1EE7F22AD8D76A35ULL, 0x19EA9716C983F9D6ULL, 
            0x69B76D615DF58A9CULL, 0xE5976E1137422624ULL, 0xD5A285A772CD2D0BULL, 0x5B2186082967C6C8ULL, 
            0x02A2CAEF3D5C5873ULL, 0xD03949F94816DA7DULL, 0xD030C3E4F4F11374ULL, 0x0AA2A85E219428DFULL
        },
        {
            0xC28A27441F95D0BAULL, 0x277A4233DBF30DE2ULL, 0x2E45CE9757F504C6ULL, 0x89360AEC4889CA93ULL, 
            0x0B210EB6288D397AULL, 0x60621D146518CE32ULL, 0x7F9E56357F6D39B9ULL, 0x1F639BE526540B34ULL, 
            0x7502D5EAB8022B77ULL, 0x724DCFAE07CDBC7BULL, 0x6E68C27EED4D82ABULL, 0xC45E51EA03D77324ULL, 
            0xD88C099D84BEE643ULL, 0x46CEA7DFC79D2A4BULL, 0x855E8450B4AB6095ULL, 0x338D3D42FABF1388ULL, 
            0x8F6FF55277A54A24ULL, 0x096B078D2DD5A7CFULL, 0x0CB07FD628A8A31EULL, 0x62C8059EC2ECBDA3ULL, 
            0x17F6AEC44D9FB983ULL, 0xF7FD9F7968BCDFF6ULL, 0x7B7CD3711699B01EULL, 0xCBD420AD6B393CC0ULL, 
            0xA12B957D22FDCD73ULL, 0xDAF8EF46A6B9B722ULL, 0x84F508CF20B20C46ULL, 0xCA2F9AD8E563857FULL, 
            0x6FDD3411811A35CBULL, 0x3B992E4B19AADDEFULL, 0x9809C3C15137238BULL, 0x6A1B01A1F897B851ULL
        },
        {
            0x53F491560F6344FBULL, 0xB8D580819CE2F71EULL, 0x74902FA456794AC5ULL, 0x3E31098A1AE59889ULL, 
            0x50556A39C28CA9F4ULL, 0x74FB2BF360EE29E7ULL, 0xA3227623EFEA4B63ULL, 0x2F12767E721D2C73ULL, 
            0xEADD0B8345274EC7ULL, 0xDD8653771C116B9EULL, 0x58B969A8DB93E912ULL, 0xA136FC071E79F5E0ULL, 
            0x8B856C3BDB8AB27BULL, 0x55337B3685643559ULL, 0x70E78A92BAC16E86ULL, 0xC3807AFFE77E3825ULL, 
            0xBB91864F1BAA262FULL, 0x40F2D7A95A181A66ULL, 0xEF360108BDE3F84BULL, 0x6C85DF84AB02ECA4ULL, 
            0xD642A3A0EFFDD6ABULL, 0x78414707884C708DULL, 0x39C64C6A802CF9CBULL, 0x160F0DD908EBD7E3ULL, 
            0x90D15C6E4463B94CULL, 0x42627B0584993595ULL, 0xCFAD793602F8333CULL, 0x7B735117ED62B61BULL, 
            0x271A8F406081F809ULL, 0x56D9E7A6BDD0F064ULL, 0xA5593DEA7F94A35DULL, 0x9D407C86EBFCFAC4ULL
        },
        {
            0x12CE987F459397D7ULL, 0xCA2DC7692EAD7EA3ULL, 0xAFB51F74CA8F4D2CULL, 0xCFD17F8473546455ULL, 
            0x9FDA80EAF8297E5AULL, 0x30790F100C600289ULL, 0xFAE07B7BA661C1E5ULL, 0x7B5F3DC362DC64C7ULL, 
            0x034101002ACF89D6ULL, 0x8A3B9F8E93578AC0ULL, 0x3BE236D7FC77D4E2ULL, 0x80C934F5126AF0BDULL, 
            0x5F3E8504F2532D9AULL, 0xF51EB49DB73E25D7ULL, 0x5BDAD77F0BC00CF8ULL, 0xD28C33DADA48E3C7ULL, 
            0x8246490054B246CFULL, 0xC87D68DA20B6365EULL, 0x7194A49BA4145DE9ULL, 0xD201CE596254AC09ULL, 
            0x9796EB0CA35C3FA5ULL, 0x5553BBE54EF3B8E5ULL, 0xECC2C05E82CA2EF4ULL, 0xB77C2D9839F4BD37ULL, 
            0x6FB52450708EFC20ULL, 0xE0B2592276511758ULL, 0x709B5194D842F0F3ULL, 0x6D30A633461977B6ULL, 
            0xB05A1D91CE5CF5B7ULL, 0xCA368C5793EBE451ULL, 0xE28981B74ABE94BEULL, 0xE9997332A2548AE6ULL
        },
        {
            0xB977F4B6C2010661ULL, 0x819C8979CF6823C6ULL, 0x97C13BA6B7AA6F6FULL, 0x93A62EDB2D97DA99ULL, 
            0x32D04A7270D8989BULL, 0x204ADD203DEBFC27ULL, 0x4F590E48827DE5A1ULL, 0xBC7DEE72C8C9360DULL, 
            0x0D00E3F34EF2B00BULL, 0x493D086BCA63C0C6ULL, 0x510E6C0CBF3B5022ULL, 0x98A934225121E76FULL, 
            0x0E3DB9EDBD3BBD90ULL, 0x44495147E4F2B277ULL, 0x2AA736320D33EB7BULL, 0x13CFBA55A4505400ULL, 
            0xAC7C0CD24364451CULL, 0x6BA02F730B513903ULL, 0x969F85D61BCA8CE8ULL, 0x0EE3E862D69A0517ULL, 
            0xD722EA2F6FCCBF3BULL, 0x2B7DE59BCF923F68ULL, 0x73CB657392833CE1ULL, 0x088C3B4921B4934AULL, 
            0xE2D5C8602B657210ULL, 0xC5E36C07C4BD517FULL, 0x7FA5B5EB6DE97128ULL, 0xA49131EB20AEE084ULL, 
            0xD15289A49183801DULL, 0xCD2BB01841CBEAF2ULL, 0x88F07BD75A6F620BULL, 0xAD7A5C840B5DC545ULL
        },
        {
            0x1CC39017A39D643FULL, 0xF8B9B04F7D3A355AULL, 0xB42EBB27DCB4B29FULL, 0xA029AEA2A274E73FULL, 
            0x3023D2BA77BF77BDULL, 0x454B95342A68B927ULL, 0xDB07636E4032D3C8ULL, 0xA8435355EE431EBCULL, 
            0x2EC4580E017022DCULL, 0x5FCA2E4648D396A1ULL, 0x642FC1A50212D9C3ULL, 0x7FE84A1E2271E9A2ULL, 
            0x73C27EBD1825C687ULL, 0x0BCC46E2F51BEAC1ULL, 0x6A6F48989FFF0E08ULL, 0x02CBCA22BCC134E8ULL, 
            0x5DDEE846E6A0A0A0ULL, 0x12A66317E2DFE62EULL, 0xD604D058B3A3EE69ULL, 0x6E4EB1DDA315529BULL, 
            0x539B6C2E02C8ABEBULL, 0xC5AF4C4339C8C10FULL, 0x80A118914BDD47C5ULL, 0xFDD828B0AE496583ULL, 
            0xF3673721E99AEA15ULL, 0x98C6D451717B60A1ULL, 0x5EBB948342A033D7ULL, 0xE56701A023191F31ULL, 
            0x7A4C18BAF3859B9EULL, 0x89BDA087FBE669F0ULL, 0x7B029A7EEA19EB1AULL, 0xA2B4BB39C7667533ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseCConstants = {
    0x45A9EE829667949FULL,
    0x6D6596F8E6A82A12ULL,
    0xBDDDE4D0F9AC4727ULL,
    0x45A9EE829667949FULL,
    0x6D6596F8E6A82A12ULL,
    0xBDDDE4D0F9AC4727ULL,
    0x40072F7260B4C18AULL,
    0x9CF441E94A5BD380ULL,
    0x74,
    0xF2,
    0x34,
    0x52,
    0xA0,
    0xAA,
    0x97,
    0x6D
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseDSalts = {
    {
        {
            0x230E02F4D9D40E1CULL, 0x675606FDF9131B6DULL, 0x5112AEE4D62DBA16ULL, 0x410904AE83C4BCF6ULL, 
            0xC2EF02DD7CADFF2DULL, 0x1F4900F4354438FDULL, 0xA2AC416F2FD21925ULL, 0x5037F926B380F29AULL, 
            0xD9EDD36FBDC67329ULL, 0x579A93C9EEC0EEFAULL, 0x5D1984E357A3619EULL, 0xBDE16400E184C4B3ULL, 
            0x5FD66EDEFAE26D1CULL, 0x86068C9D2157BB74ULL, 0xFAB637FD7FA317E3ULL, 0x5F4D3AC076FB3D6CULL, 
            0xB46449209FBD0C18ULL, 0x46B9C169D6839A83ULL, 0xF5D89DDAB25721C4ULL, 0x7F64DF7A6620D7B0ULL, 
            0x2A44AEC2BB58E224ULL, 0xBD798AF06B212C8CULL, 0xC04A7AC897A6E1CFULL, 0xED327DAD0333E2E0ULL, 
            0xDD8B00A6EA1D6FC4ULL, 0x1B36DE535BAB7987ULL, 0x12DEAE03D0F23674ULL, 0x7BDA254BD5452F11ULL, 
            0x25A46773A26E8C43ULL, 0xF0340DC616E187E3ULL, 0x18F74A5B7C312AAAULL, 0x09577B689F31A5C9ULL
        },
        {
            0x22E0FBE710DF7284ULL, 0x9A343ACCEDEA1402ULL, 0x5487CC448CD7073DULL, 0xFF534AC99EC9619CULL, 
            0xFE7CCA192AB73B78ULL, 0xA6F3ECB91DDBB929ULL, 0xE712B5822BCAA6BCULL, 0xEC31251EC8D03B2BULL, 
            0xAC573CF54B1489F5ULL, 0x5157E35E0BEC8BD2ULL, 0xE868012FD45AB911ULL, 0x1D466F8727F76A12ULL, 
            0x65CF8E12D875BD4EULL, 0x72F27B3E5CD6029DULL, 0xCD30BB246F095DA2ULL, 0x5E5057670306B78FULL, 
            0x40F60A5EA031AE5BULL, 0x1E318ED2AD046843ULL, 0xD77C1C7E3723A18AULL, 0xCB6D56E89A577C67ULL, 
            0x90621D87C68DA6C9ULL, 0xB0D39FB5CD694980ULL, 0x420651E570AB938EULL, 0x6A1430B2F2EB94BFULL, 
            0x9F80B88A3AEAB8E9ULL, 0x132F57B0D3E13CAFULL, 0xC640466D93B5A060ULL, 0x92BAF184346027D5ULL, 
            0x4279C6FE72333E5FULL, 0xF174FA7F30334785ULL, 0x71A7FF4C4D0A0A38ULL, 0x75AA4138C164E3CFULL
        },
        {
            0xFA13AF41ECCF7457ULL, 0x30B7DE35D780F9CFULL, 0x848010359616756CULL, 0xC9F7101868374702ULL, 
            0x4E165B1229766616ULL, 0x1B44992752199CE9ULL, 0x23811C2001B11E81ULL, 0x66698BE560F73863ULL, 
            0x68794B9C4984DCD9ULL, 0x7E2B01213A08E353ULL, 0x5E9217BD0719DAC0ULL, 0x411CC288AB831DAEULL, 
            0x49074A8E403E41C9ULL, 0xD4CEA8E4433F4E55ULL, 0x6D5870350283E640ULL, 0x9D61A34C5B633BEDULL, 
            0xF7CCE82051673F50ULL, 0x468FAA7925EADF0FULL, 0xE9EB4265DA76865AULL, 0xB92815E6566542C3ULL, 
            0xF7880CF5E84CE491ULL, 0x83AC35F6FCEB222AULL, 0xAB937CA81FBC2463ULL, 0x11706C6B770A6804ULL, 
            0x419FB9E4338D45ACULL, 0x34A04B7FAF878301ULL, 0xED6D4C35D293E079ULL, 0xE398A4BA3ABD6AECULL, 
            0x6EBBD3AD0E9CB145ULL, 0x3F02C5B87FD3CB14ULL, 0xF45CAF58A8440FEEULL, 0x86711275E2477E30ULL
        },
        {
            0xFBB4DCF9D32C7E68ULL, 0x195774FC7DB28A48ULL, 0x72410D5519B8D4D3ULL, 0x7F7526769826B627ULL, 
            0xBD94ECE31893FA6AULL, 0x2412855813DDA2C6ULL, 0x5C83A0F517CAC010ULL, 0xDB9B7282E8B29070ULL, 
            0xBE64F6506E56F3AFULL, 0xBBB128F111B63FEAULL, 0x8B24085F31AC8583ULL, 0x3292B60AE691B4B3ULL, 
            0x533C424FE7620284ULL, 0xF81F48956558062DULL, 0xA2A6D3A22B967939ULL, 0xF152EF17C4CD8D7CULL, 
            0xCF6AEFBA55AE697DULL, 0xBBD69014C470F076ULL, 0xFC410EF6E2D79843ULL, 0x3D6DF4102C418511ULL, 
            0x621D123DB6BDD9F3ULL, 0x4567406E598C81B9ULL, 0xBC63C422E7847574ULL, 0xD8259EA786DE23B3ULL, 
            0x45C2F40590DF0612ULL, 0x052D69DC8D5B0A09ULL, 0xB8D11F0055C1A216ULL, 0x77D484A857BE9391ULL, 
            0x00B7733AF9652934ULL, 0xD895A085EAB63E1AULL, 0xC5EDBBC2CED389F6ULL, 0xC14511727D97ABB8ULL
        },
        {
            0xEB46F654D6B0F0EAULL, 0x90989595520FD54FULL, 0x2499AE759FDAF27AULL, 0xEAC954D4F1C13B17ULL, 
            0xEB9FA4580085C4A4ULL, 0x21CCC3646794B77EULL, 0x3974F4D9467EBB26ULL, 0x8AB1C2B8D7A20980ULL, 
            0xCC3D1A7E4628ADF5ULL, 0xEEEAE283312D836CULL, 0x62FA350D39E5ECD8ULL, 0xA6D39DFF39B7D06AULL, 
            0xC39F7C5EC95B37F5ULL, 0x1AB03BA4E213A7A3ULL, 0x6C65CA7E036335DBULL, 0x51A7F613E066B3D5ULL, 
            0xB840B1F17A59120DULL, 0x01D420802320A0EEULL, 0x59DDB29653027657ULL, 0x77977BAF40E78683ULL, 
            0x170533B8A3AF2638ULL, 0x53F0FD7572225146ULL, 0xD42F908294562418ULL, 0x3659F89E79DC8985ULL, 
            0xCC0B47A57B7F8BE8ULL, 0x878CF170965C9138ULL, 0x6E2F1987233B6929ULL, 0xE1671FB0D354A408ULL, 
            0x250EEC301C051D38ULL, 0x03C0AB9EB676594AULL, 0x9DBC3DA48D548BD1ULL, 0x36AAEE2C9CE818A1ULL
        },
        {
            0x017372CC9B5EDDDAULL, 0x34831FF824E97C7AULL, 0x1B000F1472D23D9DULL, 0x76A21DB310C36CF0ULL, 
            0x251EDE7BCDEF80C3ULL, 0xB7B6F1A62EE8A29BULL, 0x1200735988931F56ULL, 0xDE426014200729F6ULL, 
            0xFC2B98B149271E8BULL, 0x4BA43081C078B2FDULL, 0xD89CA243A9CA2590ULL, 0x1A889648D8C844E5ULL, 
            0x57C45F5101C54E2BULL, 0x48509C56D7D1837DULL, 0xAEC885F21A5A84B2ULL, 0xEC99502743AC99D8ULL, 
            0xD7409B43D296BB61ULL, 0x47CA8FB6FAEEE324ULL, 0x54EC8F5AF38F2B9AULL, 0x2602227DF9CCDC01ULL, 
            0x25558CE3AD1E83DEULL, 0xC5A926D9526C5A2EULL, 0xE013CDCD8CD8DD2EULL, 0xD2DB694835547CB9ULL, 
            0x5D50860196DE29CDULL, 0x51B54A4206BEE6ECULL, 0x6421194EEEE2B117ULL, 0xF3DFB064A9F049F9ULL, 
            0xB390F13DE98E607BULL, 0xDCFA7DF43F75778EULL, 0xC6D90F783971EB58ULL, 0x4C1946C1B024C890ULL
        }
    },
    {
        {
            0xC69EAF27DEBB19A3ULL, 0x528E5140CD23DDAEULL, 0x8AA05AE8AB532286ULL, 0x4A3910D3786B3757ULL, 
            0x1226EDC16D9C1648ULL, 0xA098175BB534BDCCULL, 0xDBDEA89325188695ULL, 0x125307339F925C78ULL, 
            0xA4845FAA41CCB615ULL, 0x969FA68D34866C0CULL, 0x3C3082C21B87A66BULL, 0x6AEC4615A5969F38ULL, 
            0xDFB4C3DF25A1C0E4ULL, 0x26219F3796E8B95DULL, 0x69D36DB925F37BEAULL, 0xFD1D9066893F3F63ULL, 
            0x78D3A83B83F8167BULL, 0x4786CAF8ED57E629ULL, 0x842BF669352676D4ULL, 0xF3555B4BF12B7120ULL, 
            0x7EDD8B9EED959CA0ULL, 0xD96AEE06FEAEE2DFULL, 0x678EFD5837F8F10CULL, 0x57EC40132CFB5E58ULL, 
            0x7560BBE7F3DD2986ULL, 0x57BD8C5FBF9C7F94ULL, 0xD72B3149929C02CDULL, 0xD9C3176B4AF68ECBULL, 
            0xFB9979E61CBBAD82ULL, 0x0AC40194B9945E53ULL, 0x6892E8F6AEB07E68ULL, 0x4B4C0FB329EFBE51ULL
        },
        {
            0x8BB993A907DCB2A9ULL, 0xA4CF258582CEC796ULL, 0x236063E7C0DA4A6BULL, 0xF175476D51D1CCDEULL, 
            0xB9B27CFDEDF77F06ULL, 0x4C98B80C213242EFULL, 0x007D090A7328831EULL, 0xE536E4508047C87FULL, 
            0x01BC461F7A74ECCAULL, 0xA910208CFE4F5C11ULL, 0xCEADB0FCFB6D0949ULL, 0xA37F59CE9D52012AULL, 
            0xE206F39A0B8F1B05ULL, 0xE93687B290B32F06ULL, 0x47F3D96FB0FA2063ULL, 0xF24F78A757342851ULL, 
            0x842FB0137C3A6646ULL, 0x75D534F11B20B45DULL, 0xD8B2782350F15C08ULL, 0x73DEE56F52EBFFCFULL, 
            0xC8BA39833D68B1ADULL, 0xAEF2964C6E07CAE9ULL, 0x5D861C030C43D747ULL, 0xDEDCB9D91D4D7C23ULL, 
            0x7A3F2875FFD63851ULL, 0xC02A1A421FDE48D2ULL, 0x15C88ABDC613E133ULL, 0x969CAD8565E29A36ULL, 
            0x8B99794A12F02CFDULL, 0xA11F603C2ECEAB57ULL, 0x1306A466217B13DEULL, 0x496CA16AC5B53902ULL
        },
        {
            0xE2159EF0FC9A769CULL, 0x4998BB0CC49CBDDCULL, 0x63A226C2BD7F42C0ULL, 0x97EBABB1DF6F64C2ULL, 
            0x55D69E619517F17EULL, 0x4E778E8189863647ULL, 0x0828A9344C8FEFFEULL, 0xE3F819E9C40107E1ULL, 
            0x6AC7873AE0A532AAULL, 0x692ED6D31E70DFC7ULL, 0xB0CAF1CB6F6D352FULL, 0xFA1885689F04B433ULL, 
            0x47854A3D2AADF085ULL, 0xA5188090D0843F98ULL, 0x42FF62BE8DA4CF08ULL, 0xA3BAA23C81C42672ULL, 
            0x9C87DDC81E856876ULL, 0xCDADC27AFA56D154ULL, 0xDA672071561561A2ULL, 0x375F4AE09C1F9319ULL, 
            0x5AA74FD303FDDEF0ULL, 0x59044455EA2BE42EULL, 0xA991AAF405A4897DULL, 0x8E9E4FC73CE2BE27ULL, 
            0xB48B87EE2EA131ECULL, 0x78A2BB0E80AF76B1ULL, 0x2C2AA372BBAD3B6FULL, 0x15CDC5050C67D69EULL, 
            0x4F46BF55CCCBFF2AULL, 0x8A4E6549C581CB5EULL, 0x4D50A3AD3B9B06DAULL, 0xDF382668D378ABCAULL
        },
        {
            0x8394C4548FBF6560ULL, 0x5114F56BFFE1BA29ULL, 0x0A12B4616BC47E70ULL, 0xBBA862FB2FBCDBECULL, 
            0x903A055A1FD72285ULL, 0x3E9068DB0937FC49ULL, 0xECA1D16D26750A20ULL, 0x811FA7072932370DULL, 
            0x0C1F66301D2275ABULL, 0x52AB2903F83A7BB0ULL, 0xB71660998481FC99ULL, 0x257DD44B511E8957ULL, 
            0x901A2687AA14829EULL, 0x5307529B0DDBB3D1ULL, 0xA0AC7637AEC23064ULL, 0x906900559654315CULL, 
            0x60655590FF5997D1ULL, 0x22C29BFA366EC7F2ULL, 0x59726BD22743653AULL, 0x6F8E954E1275E193ULL, 
            0xB820A369430F6C9FULL, 0x52FBAFC7FD4C6361ULL, 0x20D2D148459B7F33ULL, 0x4F21E8DA2D92D3C4ULL, 
            0xFADA5DA6FD56C406ULL, 0x292C5DD6C6ABA34CULL, 0x4FF69EDC0F367930ULL, 0x791A926886008ED4ULL, 
            0x9920B3B140DF0BE1ULL, 0x2FA4EFCCE80A4206ULL, 0xC32551FC95AFD600ULL, 0xA3706BE6E63937A9ULL
        },
        {
            0xDB1D04FB6B956D1AULL, 0xD94C883725306B00ULL, 0x2863792D61790072ULL, 0x526545B28A607100ULL, 
            0x1A6143353CB96766ULL, 0x60ECBBEF28DFC76CULL, 0x567285C7F2A49F29ULL, 0xE81CB1788FEC7DB2ULL, 
            0x5EB6840ED3486CDAULL, 0xAEDC1FD8C6D019F3ULL, 0x11341BE40753947FULL, 0xF9E5A37BE3FB8DB2ULL, 
            0x6AE7C6A6BEA78FF9ULL, 0xB1DF65B2E0045EA6ULL, 0x17CACA83B6B33912ULL, 0xA5830487ABF6A2EFULL, 
            0xB48F66E7ED96FEB9ULL, 0xCC6F80BF9C14A45FULL, 0x40CEDA2B0D119047ULL, 0x0FBC21B1F20519FAULL, 
            0xB6F608AFF6B1B55BULL, 0x370CBBE307C90854ULL, 0xD259E9BE7E9E40B4ULL, 0x63C59BF90D4877F1ULL, 
            0x25D53C69F5CFAF6BULL, 0x7F7A15B77D6F4D35ULL, 0xBEBC8EDCEAE5D013ULL, 0xB3E27E68B9E2D56CULL, 
            0x11FFFE061E469C08ULL, 0x9E32A412D4C667B9ULL, 0x9CB2B2FEB4440275ULL, 0xE46ECFF2EF31CE37ULL
        },
        {
            0x341888B5DA30880AULL, 0x77F934206CDCAE8CULL, 0xBA6DF0F2B852DFCFULL, 0x08E010DF15A4216FULL, 
            0x8597BD9627CB0DC4ULL, 0x1C500B59287E7F2BULL, 0x0809E1EE4DFF77D4ULL, 0x46FB4E3AEF7FDD4AULL, 
            0xA69C073D2F2BD15BULL, 0xB4E796BC820C0468ULL, 0x3DB1E36E1745489BULL, 0x46AF9D15A72D8E18ULL, 
            0xAB34F912E271E6DCULL, 0x0130B245B1B29B15ULL, 0xD3A810228D2E4608ULL, 0x7FD285EFAEA70361ULL, 
            0xE067DA666120DFACULL, 0x3FDBFE691337BE3BULL, 0xE600EC2CB8962EB7ULL, 0x1474BD983FFCDDB3ULL, 
            0x66EE1CBBE05299D7ULL, 0x903E1E8EE5E62197ULL, 0xEE184D4D05B234EDULL, 0xF8F409DABE7C810CULL, 
            0x95FD463124DD1893ULL, 0x366A108749B75F91ULL, 0x1BFE4C60674C373EULL, 0xA445AADE4FC7A4B1ULL, 
            0x20AC1151D1F47C77ULL, 0x7B7E55F3BE0103D3ULL, 0xED511CF09C465022ULL, 0x33A2BA72CA57A76FULL
        }
    },
    {
        {
            0x5D56ADAE3AA07C47ULL, 0xA206EF49182CFA27ULL, 0xD30563327A33134DULL, 0x2E3CA4CC52E739C5ULL, 
            0xADBC00B3BFF9F5E6ULL, 0x1BDC59A5D9526A9CULL, 0x417CB1E110B1C272ULL, 0x3E4F54BED5E5D074ULL, 
            0x51FC25F6F5EB2D43ULL, 0x9228BB5A9C37FA27ULL, 0x3568CFC9BC23D366ULL, 0xD09DF8ABE40F912DULL, 
            0xD734AF126DFE7FD4ULL, 0x8D9B58FCBA5704C5ULL, 0x1F95E4C694A0D46CULL, 0x78C4AA30D2759E49ULL, 
            0xECC045BDB1717F46ULL, 0x992B37965E97EE94ULL, 0xE95990C2A7B3A9C8ULL, 0xA3B0390A075396AEULL, 
            0x18142A83B93049AFULL, 0x4960BA68956B8BE8ULL, 0x384625E0F9E03730ULL, 0xFE3F9AAD82162D9EULL, 
            0xD070E5F4ECDFF2AAULL, 0x28A023F08E25E784ULL, 0x9B6F57FE4FD4D3ACULL, 0x6215B05E178B839BULL, 
            0x97B314CD9C5A8F96ULL, 0x87A1F1BDAA2B0633ULL, 0x9D39A7A7582B9FC9ULL, 0xA632E9669BA3B424ULL
        },
        {
            0xC95560A2B225C413ULL, 0x9C1795A5986A2CB9ULL, 0x33F2E1040E6928D2ULL, 0xCD072E5597BEB248ULL, 
            0xB95B1CADA90583EEULL, 0x341B84308A8690FAULL, 0xE2ECF5C1DC29673BULL, 0xAB04ADBAEBD10FDFULL, 
            0x8182A034625E0335ULL, 0xC828DF27974945BCULL, 0x67C7908A4A0A635EULL, 0xAA35812E9E60DA52ULL, 
            0xCAF89554E7C6EE79ULL, 0x61DC5EDB955F054DULL, 0x5E6A85DCB901B8CEULL, 0xA5276F9B6E4315EEULL, 
            0xABAB9A7C9243D1D9ULL, 0x6BFF2FE17ACA7FC2ULL, 0xFBAE1C84B1C733A5ULL, 0xD420D506406C6BF4ULL, 
            0xF80835F2897492F5ULL, 0x83D712713E28803DULL, 0x09DDB27E11F6A26AULL, 0x6270593FDFAF0EAAULL, 
            0xF8D03AA7662D0524ULL, 0x624227BC6F343C6DULL, 0x139B15FDFBBC43C1ULL, 0xC2715C8848D52DC3ULL, 
            0x6C778B8C711E961DULL, 0x9AC5DE4E13320C2CULL, 0x9D8694508839D4F6ULL, 0x11D14451328D3846ULL
        },
        {
            0x21EAF645387F6E67ULL, 0x040E13E78A879055ULL, 0x45252C02BE0DAF47ULL, 0x44B2EA3003F330A0ULL, 
            0x64AB381F2574CDFBULL, 0x32924B8484FF99EFULL, 0x0B5D976919266B01ULL, 0x8CF304E0A53FBEADULL, 
            0x2DD2906E98D66C51ULL, 0x133B2524AA1AF330ULL, 0x5DAC61A1FC98F688ULL, 0xD24EFAA315FD6EA2ULL, 
            0x6B429428EB44399EULL, 0x7A222DDFF870F6DEULL, 0xF5415AA61449B66CULL, 0x455527A20BFE5607ULL, 
            0x0EAFB69922F1F220ULL, 0xDA7DB2AD889E3CADULL, 0xFE9B966C37B9BA47ULL, 0x4CCF5B6A90D35FE3ULL, 
            0xBE1BA0AD060CA47BULL, 0x075283ED81A0177BULL, 0xF6540998E421078AULL, 0xC9F18D59A5CB2524ULL, 
            0xEC02F26FF77E28B8ULL, 0x96029EC138331D2AULL, 0x23695FDD33B69F1DULL, 0xCC72148033D956F9ULL, 
            0xC270ADDFEE657513ULL, 0xABF847DADF733360ULL, 0x00B7AFD4429E095DULL, 0x2E878CC5643F2E18ULL
        },
        {
            0x7D98F8998971D527ULL, 0xCF480C61DFC40744ULL, 0x81FA9F70BA1840AEULL, 0x34B1604C6225E296ULL, 
            0xF1D5986F04C3F2BDULL, 0x96FB314B66681C23ULL, 0x44047365094F009DULL, 0xA541D0777062363FULL, 
            0x512CC6DFF8FC60DDULL, 0x659B3FCF8FC7949BULL, 0x3A7C2B6920BDE95FULL, 0x8B9F36814158C8E3ULL, 
            0x8DCAE5CFD114B881ULL, 0x3BD81CF21A9506ADULL, 0xA5D40FECFFD61A22ULL, 0x311B365F6F64EEB7ULL, 
            0xEF32436A4CD3D85AULL, 0x8A6C848DFAA27E61ULL, 0x60A1DA9EB14EEA38ULL, 0xC15CA76EE534E9A3ULL, 
            0x569705669E8150BAULL, 0x5033A2DC0FBCFC16ULL, 0x991FB896388B2B91ULL, 0x3EBD6E7DAAF8617DULL, 
            0xEBAB5CE4E2D177CDULL, 0x200CCB4F5A6B4CEBULL, 0x727A3165A049DADFULL, 0xB29032D21CCD9BF7ULL, 
            0xFB0BE9DA11FC3D4DULL, 0x5919D7CBDA21CE4CULL, 0x73A0B261BC9D771DULL, 0x9864DF47BBA5BB42ULL
        },
        {
            0xB13C1A81EBEFA801ULL, 0x085328A7CAE0172EULL, 0x56068B71CDCE538AULL, 0xF8E725B1279913C8ULL, 
            0x836DD45FAE2E97D1ULL, 0x2E0FCF23CE1A7F62ULL, 0x15CD3C48D8A48A24ULL, 0xF9A48140563E4212ULL, 
            0x92C95AFE39990AF6ULL, 0x775F88C387EC1FC5ULL, 0x7B3AC4123B5323ADULL, 0x63FA509D637C0839ULL, 
            0x1F63C1CA8ABFD6CCULL, 0xA3C7D3EC6A57E6BFULL, 0x7F635304321463C5ULL, 0xA5CFC691875874F1ULL, 
            0xB620C23265479D54ULL, 0x862C37B9D94AE711ULL, 0xCA0BF148313006F1ULL, 0xD99DC9F8FCD29421ULL, 
            0xECB8149AEA01EE5AULL, 0x1B306263404236DDULL, 0x647B1926A395BCC4ULL, 0x98F77BF623EA4970ULL, 
            0x747962F345D80B46ULL, 0x9DEBC8CA330E96D3ULL, 0xC1FB523BB817C885ULL, 0xF00333DDF8300D60ULL, 
            0x0511147745D87639ULL, 0x0FC30DF9361E5365ULL, 0x55E1FCE8CA08F158ULL, 0x86CF91C2B0042BD1ULL
        },
        {
            0x5E4D6A6DCE700F21ULL, 0x9E8BF1BE38D1C20CULL, 0x58EA069AB5557787ULL, 0xD4DEB9B7E9E1C62CULL, 
            0xF2972AF2E66A79A6ULL, 0xDB2C5701E10CDC08ULL, 0x3B88CF26B9715564ULL, 0x6011CAA89B4E6D18ULL, 
            0x0A8471759699F3F2ULL, 0x4ECB962DF4537852ULL, 0x2B24CC133559EC77ULL, 0x12429297929D0E67ULL, 
            0x4120E0B016363C61ULL, 0x6AFA0F3EA749CEF6ULL, 0xBDDFACF2092DD996ULL, 0x70F515DA339D005EULL, 
            0x7CF10F73A8C03932ULL, 0x3AFA0E858B7513D3ULL, 0xD4C7A22F74EF9749ULL, 0x2E2022F4DADBE0A9ULL, 
            0x384513837F5E92B4ULL, 0x20F9417C7AF91043ULL, 0x695E0D5A6ED27D43ULL, 0x0E7BF0D1E1458B36ULL, 
            0x9E47B8F6EBC90CB1ULL, 0x84E1D6930F392558ULL, 0x5C913DBE74EE70D1ULL, 0x00BE0326D46CF809ULL, 
            0x0B3C8A1718331A06ULL, 0x1CBD13DD35D4C99BULL, 0x236A061E0BF3BB42ULL, 0x49917840D88ECE9DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseDConstants = {
    0xD294E525A0E917D3ULL,
    0xE20B711AC929048BULL,
    0x7131A7B5B198B984ULL,
    0xD294E525A0E917D3ULL,
    0xE20B711AC929048BULL,
    0x7131A7B5B198B984ULL,
    0x624E8A928D955D9CULL,
    0x2E5ED58A661C05E0ULL,
    0xC7,
    0xA9,
    0xB4,
    0xCF,
    0x20,
    0xBB,
    0xA0,
    0xE0
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseESalts = {
    {
        {
            0x8E373004F324C349ULL, 0x22806E31A8B3AC38ULL, 0x81B0D7BC9252C87EULL, 0x2D5FD34F320A963BULL, 
            0xB7A116FC4190EBA0ULL, 0x761428316AC9C47EULL, 0x9D32FAD7A16514FEULL, 0xA19C2634E8B25C50ULL, 
            0x0EDB07B08B44485AULL, 0xA4CAA046BC9FB7DFULL, 0x2C8634D5F52F543EULL, 0x3D2F34D375DFFCA7ULL, 
            0x3196315CD13DDCE0ULL, 0x4BD434718C769395ULL, 0xFD92F76196E9E052ULL, 0xCB514A9CDB7ED9BAULL, 
            0xCBCB50D21A218CC6ULL, 0x5C2BCDFDDC7FCDD7ULL, 0xF28C155405EBC3D9ULL, 0x9677E37D4AEC3B40ULL, 
            0xDC19816E3AA18CF5ULL, 0x14E23AC6914256D1ULL, 0x857D9682A1290D33ULL, 0xF1ACA8B0BD7172CAULL, 
            0x597758E843AFBD66ULL, 0x76B5FD18E67DFB1DULL, 0x6005E259534D2B2EULL, 0x4E2D3809132A341FULL, 
            0x1DF223034FBE84EEULL, 0x3D52B0D19A093D8BULL, 0x59CBAFA8993E288FULL, 0x090B94DE421C9450ULL
        },
        {
            0x576DFAFE04398DEFULL, 0x7D348022B2F9572FULL, 0x7504FBADCAA0205CULL, 0xC22C69FA5E137CB0ULL, 
            0x48F66A5D60A8E9F6ULL, 0xE78ED1B9792735E3ULL, 0x5328C9B13636F150ULL, 0x9A51CD6698866986ULL, 
            0x2EE652EC8F9F5591ULL, 0xC13CD1B62EF7266DULL, 0x18D80B3BD4E81A8FULL, 0x55C3B95E61184664ULL, 
            0x65D2C4CDF05B513FULL, 0xD74B2FE5E142AF03ULL, 0x0C5376C29FCB6138ULL, 0x232F8256675E1DDBULL, 
            0xB7390B029DB93213ULL, 0x72DAE592CC714A2FULL, 0x9737AC481E59ECCCULL, 0x5CADACBA6CAD6C78ULL, 
            0xE6C8DDBF0A386E4FULL, 0x0DB4DA5016FFFF91ULL, 0x13775C5E62082372ULL, 0x32E3DA51577F8529ULL, 
            0xB8D69B27F0225523ULL, 0xACE58EEEB59B232FULL, 0xD2080C2BA21D8B58ULL, 0xEE98AF6DC800AF98ULL, 
            0x4B1448194F26B578ULL, 0x4C381AE68EF9C44EULL, 0x10745D21ABD92A1DULL, 0xA8104213E6B9ADA0ULL
        },
        {
            0xEE8C5A6872201CACULL, 0x50EF0BC12226FD71ULL, 0x61AFD861E644C7A2ULL, 0x5043E9AD983097FEULL, 
            0xA059F28D035AC749ULL, 0xB570C8A643C6412CULL, 0xC3362189F377AAB8ULL, 0xE024AC5FC23A1103ULL, 
            0x99648B438B58AB20ULL, 0xAC98C28D1DD94910ULL, 0x76ABDA89E5266CE1ULL, 0xA9E30E490EFE23BDULL, 
            0x3B472FE6D2DE68E2ULL, 0x429CEBA2BAA5511BULL, 0x02154B71E256C4F8ULL, 0x76B3B99A865D5F87ULL, 
            0x1155ABB573982CD8ULL, 0xD4CFC12BCCB7252FULL, 0x84A1E65E75015DF7ULL, 0x749A7CDEEE55E8A2ULL, 
            0x4D3FFE414B54F760ULL, 0x4A93B490D0D95A62ULL, 0xDE35F937AB549B22ULL, 0x94A88061C8C27884ULL, 
            0xCBD05877BBF5A5D9ULL, 0xF42B3EAFF06440DAULL, 0x158BE9B8DC166799ULL, 0x2FC0C8436CE52C5EULL, 
            0x4131BCAD8C1994E8ULL, 0x94C4EE632AE67766ULL, 0xF579C2B02830EA0BULL, 0x003C5EAFD205597AULL
        },
        {
            0x10FAA76961AD7B03ULL, 0x33AC43FD44D77A60ULL, 0xAE0B14FBE6EE8115ULL, 0x5D94CE1CC1FF281FULL, 
            0x95B040443E012496ULL, 0x4A2652EDE7594B64ULL, 0xBE461989945D41EBULL, 0x15DB2CBF4ECEDDABULL, 
            0x656D05E5582C1855ULL, 0xB923B5B7F1A2C31FULL, 0x5F4B6EEEA79459EFULL, 0x9071ECC85DA8C582ULL, 
            0x21173BDD2F9A136CULL, 0x8FCE1BF4F8236483ULL, 0xF4E6059AC98CD62BULL, 0xCE3DBD220FB74146ULL, 
            0xB79158CE22B47A58ULL, 0x63A7D8AAE7F403ACULL, 0xB21D617D85E3B0ACULL, 0x8A841EE3D42B9830ULL, 
            0x2DD7671C692632A2ULL, 0x2972E51E44DE6541ULL, 0xF94956AA6EF695F2ULL, 0x2C51E6B21683CA03ULL, 
            0x2F97CA6F991D5ACDULL, 0x8BA6A58285140BFEULL, 0x20074917EED793A9ULL, 0xC0644C872D6F46BCULL, 
            0x5B6D669ECE078263ULL, 0x212E29006795F64AULL, 0xEAB365042AF0B602ULL, 0xFB7E02CEFE6812A2ULL
        },
        {
            0x9A6E275724D7D84DULL, 0x71020898B94059E7ULL, 0xAA7A064D57C04359ULL, 0x706B3067E249F3CBULL, 
            0x23182AB76BF457F8ULL, 0x6F5CC4C938176B30ULL, 0xAF5756A1B023AEEDULL, 0xF9B9107F81D6E6FAULL, 
            0x999A0CCDD3DE1279ULL, 0xFBBBCC04B5FAF738ULL, 0xCCA3103D9A07D126ULL, 0xB85852CD01A4FE99ULL, 
            0x9B44DC968082A00FULL, 0xA532585E1FB61A00ULL, 0xA4B6B22F5D269B54ULL, 0x31EDFAE17DE1FE85ULL, 
            0x76C5DA9D2330F990ULL, 0x822EDB3AE9480A5FULL, 0xC5F529FDE69926F4ULL, 0x01759CBD0E09821AULL, 
            0xA859C75AC1F22EF5ULL, 0x105B041C31D77A9BULL, 0xDCDE859AEFF7BFFBULL, 0x74D383AD62886343ULL, 
            0x63199F60D75BCF68ULL, 0x1594F272607927D3ULL, 0x4B0C169026F2591BULL, 0x40F76CA460D14BC2ULL, 
            0x1DD1C0B6D924943CULL, 0xF138932EF925C5C0ULL, 0x81B6BE480BF2E544ULL, 0x9431ED45ECA777A2ULL
        },
        {
            0x488611847E302DF7ULL, 0x081CFA485D329581ULL, 0x520B271A272FEDBCULL, 0x2932CE0A1D8A466FULL, 
            0xB7FFB6865DB3540EULL, 0x573BD8A1D7682FF0ULL, 0x4B6B4658BE710E08ULL, 0x2AD4729914606E3EULL, 
            0xD4B3E5009F8FF6AFULL, 0xF7AE318AC923E036ULL, 0xEB1DAB8F20F83A8CULL, 0x6CF9C4A3FD2F300DULL, 
            0xD9B0446C5D60C4EDULL, 0xF7C2DA1EB803C114ULL, 0xC3D7A5FFC0AD726EULL, 0xEA2C707913C69188ULL, 
            0x44D89EE18F585731ULL, 0x59F37D0B2551D111ULL, 0x2120B6AE605BA1FBULL, 0xD2826E4FAFF9C5ECULL, 
            0x68DB3C099F869CCEULL, 0x82B816094A96E8F8ULL, 0x734201399A21DB50ULL, 0x9CC6662DFDF25B19ULL, 
            0x103EB8E2EDB24989ULL, 0xE293075BDA2995AAULL, 0x1A0C4E38C76C0289ULL, 0x29DCDFE523B837B8ULL, 
            0x300D2D6078B1E3ACULL, 0xB0F3C6203548F559ULL, 0x144B3F509C37DBB1ULL, 0xECD9441FB28E9C1EULL
        }
    },
    {
        {
            0xF303BCDCC0FFF4CFULL, 0x689878D87BB407D4ULL, 0xA817BB430B3BA292ULL, 0x1A08415B2086188EULL, 
            0x2474415AFDA46350ULL, 0x05AE22740825507AULL, 0x78578BA24AA6EB33ULL, 0xBF88C74A6D047E2CULL, 
            0x8A35B1B67E806048ULL, 0x037B52224CC600D2ULL, 0xA48E97A95F656DA9ULL, 0x47F0848A8DA1F792ULL, 
            0x037B6EFFEB3D85F7ULL, 0x058020C495271B96ULL, 0xEBB47D47C4B0D0AFULL, 0x51D612AC0BE8F692ULL, 
            0xBDED3CC9DA6C3BE2ULL, 0x8424D497961AC7F2ULL, 0x44CB95EC9ECFDDD3ULL, 0xCB2E22FCBA829077ULL, 
            0xCBF65ED945193596ULL, 0xFFDE529F04E34CFBULL, 0x9CDA65F83461CB84ULL, 0x6DC21BB69F6CF4B3ULL, 
            0x3D4E4F3D69C8A363ULL, 0xF67754116A775BEEULL, 0x1F81BFBF16DAE5E5ULL, 0x70579031F2920637ULL, 
            0xE59C635493A52DF8ULL, 0x64B984C0A07869ACULL, 0x5AC2FE984366DDF9ULL, 0x4CF334674D428277ULL
        },
        {
            0xEB6A1B8F4D9088D9ULL, 0x3A29086D15573C86ULL, 0x84A397FC69B5D795ULL, 0x86EA0B047A42111CULL, 
            0x9289F791CFF52A92ULL, 0x1BCC43CDC3B212B5ULL, 0x2050F6EC6112870AULL, 0xA1E92BA8D8DD2443ULL, 
            0x05369A882CE59392ULL, 0x6ADC083B643F46D4ULL, 0x82CFE6B3A7DA8414ULL, 0xE2B73173E07E1950ULL, 
            0xE870BCFF5D4D5A84ULL, 0x67DE3C50D8A4D7F3ULL, 0x861AD330E93FEAA0ULL, 0x497B4D053AFC4B56ULL, 
            0x18D072D7ED832D4FULL, 0xE2E951D1B0233757ULL, 0xD8B89E0DBED6C9BBULL, 0x7235583193D050BBULL, 
            0xF7FC8F955F52D645ULL, 0x3250BEBDEA01D99BULL, 0x929A432249B5CAACULL, 0x6A5FCAAFBD5D563EULL, 
            0x9EDD832D3DF5150BULL, 0x8E032FD27526C007ULL, 0x1C38B3DCF463D88AULL, 0x10CA6F18AB018D2DULL, 
            0xCED7FB906B9B047BULL, 0x7966806AF843337AULL, 0x32FEA8EBE4218D02ULL, 0xE3FF9A4B6CDBDF9BULL
        },
        {
            0x72567E87B9ADC02CULL, 0x2955C89DD57B926EULL, 0xD9ED0ED7001E8FFFULL, 0xE909EF6299BBC945ULL, 
            0x0F8B8B3876346640ULL, 0xF19D38B5647F4271ULL, 0x11A5EFBEF94ACBC0ULL, 0xE0046BA76112FF17ULL, 
            0x533031C9764CC383ULL, 0x6171C839A024D51FULL, 0xCB28E6E5B7E6330DULL, 0xE21A98171720EFA1ULL, 
            0x245FF0E89BFD8560ULL, 0xE0C9AE32A7D96918ULL, 0x46764C9218385C6DULL, 0x75637CFE9B6881D3ULL, 
            0x942C96EB4247F66BULL, 0x54C93DE96C93D2ECULL, 0x8F4B6F2653E3FB4AULL, 0x97D908DE7D7689D2ULL, 
            0x55E1A97CA00748E5ULL, 0xE12F6CC21006CB2EULL, 0xB58A793F3F988CADULL, 0x5BB1552DF5230A03ULL, 
            0xF6B191BCCB029AB5ULL, 0xF9D2F6A9E8B34E68ULL, 0xC8BF7BE8F0C82453ULL, 0xDC6BDF4C8CE0EC9CULL, 
            0x93D89C9670505FC5ULL, 0x676087AEC98D644AULL, 0x313404BF55B72B9BULL, 0xAE107C8A1465E8A3ULL
        },
        {
            0xC00E52B3CDE0394DULL, 0x5C460CD330F1D991ULL, 0x1B30A4EAA8BF91A3ULL, 0x79AC18DE813F7B0FULL, 
            0x3958F68D06EAF4C2ULL, 0xE79E39D5C00C90F8ULL, 0xE1F1D4A4BC2377E2ULL, 0x78ECBF3FAF05EF68ULL, 
            0xBA8D7E959329DE18ULL, 0x7E9BAA991CEB7F4BULL, 0xD810E8E0CE33E227ULL, 0x06C0225A80775F2EULL, 
            0x7C203064B929A019ULL, 0xF6102984B2661100ULL, 0x8E5F4D6AC86BC8C8ULL, 0xFFD1D68A601EF2F3ULL, 
            0xA2687DB26A61273DULL, 0x1ACADC6C6735806FULL, 0x7E400A96D951DD43ULL, 0xF87A22A0E79FFA5DULL, 
            0x1C1D1AD1EEB518ECULL, 0x9C337ED4DB54ABA6ULL, 0xC1BF8C9AA927BB66ULL, 0x51E5A9F48A6B3E80ULL, 
            0x4F66F5B32D5C2AF7ULL, 0x4341BFB06B03B0FCULL, 0x3B6EEEE0863DC026ULL, 0x1FF641B61913CB07ULL, 
            0xFC3C2224DD497864ULL, 0x3AB68F731878A23FULL, 0x5EC75B7A22105507ULL, 0x83C9A8CCA2316960ULL
        },
        {
            0xDA71987DD5050CCFULL, 0x5868E2089684F2ACULL, 0xAF16D6895393DBA8ULL, 0x4DDA512BD81BB5F9ULL, 
            0x060985D93B7220B9ULL, 0x364790C11D1A5145ULL, 0x2E8DB3A24F07D6CFULL, 0x6401546FBBBE5BDEULL, 
            0x222BBC521223C97FULL, 0x087342CF4EF08E99ULL, 0x333FAE5B774D1DBAULL, 0x6529F80EF696CCCDULL, 
            0xE08CA3295043C025ULL, 0x6819B076B6D083C2ULL, 0x7606D6839D4BE503ULL, 0x7DE69A8FF3074B07ULL, 
            0x748AC85331963C4AULL, 0x5BE27F2F9B1739FCULL, 0x15BFC3BE58637401ULL, 0x789C39500D42E1CDULL, 
            0x073BAB65D06CA134ULL, 0x018E2BB9C33FA574ULL, 0x3119CA245B962B51ULL, 0x78CA5AB4954568CCULL, 
            0xE76E0AA65B3ADCFEULL, 0x084230959D21A981ULL, 0xB195CBC997EFF59CULL, 0x5769F6CBE35B3AE3ULL, 
            0xB6D5E0B8D699749FULL, 0x604848AA3C267F52ULL, 0x4F9F5A6A8E294882ULL, 0xDE98E409646370DFULL
        },
        {
            0x3C825DE986F2F4E9ULL, 0xFBE00638A444EDCFULL, 0x15159E2125A5A24BULL, 0x29F73AAE8FDE38B9ULL, 
            0x3A6D5FB52BFDCFAAULL, 0x86ED55F540A85DADULL, 0x1BAA37546C3CA96BULL, 0x5684F0348CF72475ULL, 
            0x3D7314ADD7082ABEULL, 0xB5264A7213ED680CULL, 0xD99F1A90994D3E3AULL, 0x4233831F48C949F8ULL, 
            0x437736C948984038ULL, 0x44E4536201B77473ULL, 0x029782F25B213D91ULL, 0x14BE5B29A451258CULL, 
            0xD324055BC2BE04DDULL, 0xBF544ECD525444FBULL, 0x93D583DAE8660568ULL, 0xECF054192F74E18BULL, 
            0xFABE213CCADF8AB9ULL, 0x900D42B37DFD2F65ULL, 0xB78353CC650855CFULL, 0xF81F6D15DA58DA47ULL, 
            0x4DA2210448E05317ULL, 0x8AE59C00D86A6932ULL, 0xFFBF8ED89C7B4CFBULL, 0xE8FCBFBFAAB2EC1FULL, 
            0x54058AB4BC5C3793ULL, 0x1A30BDD9F1B56883ULL, 0xBAAB6EE26AEFD862ULL, 0xD837691945E3C09CULL
        }
    },
    {
        {
            0x166F41C2183B9B84ULL, 0x48D8C600384DCB32ULL, 0x2DE522FD838DCC16ULL, 0x61133DB77F81AD19ULL, 
            0x4E1880B45A0C42ABULL, 0xD8A5AB1A720DF2F9ULL, 0x99B6DB9C0727F45DULL, 0x122D95A11DE6B54FULL, 
            0xC85B6FC010810C0EULL, 0xFB523F02DD460AA2ULL, 0x4E38A983A861559AULL, 0x3F35781D86DD52AFULL, 
            0x4BDD096234B1C6C2ULL, 0x0018B86D91C91100ULL, 0xF41485E89A50073BULL, 0xD2F9AE8331FD2E53ULL, 
            0xB2C5A4322E2C8178ULL, 0x93BBC4EFB2E52781ULL, 0x526350D302932A30ULL, 0x31AF7EC25E3F3717ULL, 
            0x863D1AFEB5D1E46FULL, 0x95765F17BFFC0897ULL, 0x21E0320FCAB7B42FULL, 0x3C02E56CAC1E8590ULL, 
            0xA57CE33D5305EB9BULL, 0xF267CB866F5A8B8BULL, 0xFF4B6547A04748A8ULL, 0xE4AC1BBF1243EEDFULL, 
            0x2A209CE8AE23A93FULL, 0xDC4352189684D7C6ULL, 0xDEBF2B3F473F24C0ULL, 0x619D64C74D598B8AULL
        },
        {
            0x41E63FFC3DADE90AULL, 0xC441B4DED4150CAEULL, 0xD39EC90D4C733FEEULL, 0x5DF7B2732A40C5EEULL, 
            0x3A03B8782DBD06D1ULL, 0x5B7A1A2E53B8FD4FULL, 0xCA917B22CDA7CE43ULL, 0x08A520B12B53D69DULL, 
            0xCB9CC617EC885B9DULL, 0x6C39332128F5DB3CULL, 0x6CABC7F7F6C75A2EULL, 0x4CBF8E7AB574307BULL, 
            0x950611F8BCC4B692ULL, 0xF9CFAE24EB578A5AULL, 0x228160727AE5990AULL, 0x5B83DF574A861315ULL, 
            0xF99F30A155CA8DE0ULL, 0x55FB22DBF60F3B3CULL, 0xB6E6A6DDC136BAB7ULL, 0x329458EBDD52F324ULL, 
            0x6A9424B388B359C4ULL, 0x06C6BC8F2374C270ULL, 0x73F93E8B521D2087ULL, 0x9F011F379B9C7198ULL, 
            0x4683A66B794E8D90ULL, 0x02574F8636853C20ULL, 0x0BDF1B476528AD31ULL, 0xEEDE73BFD6F42984ULL, 
            0x1E542E41C831B8FFULL, 0x550E94C403BA7B5FULL, 0x4B798CDCF0C106F0ULL, 0x009FE82A5B33A8F2ULL
        },
        {
            0xD2E231ED2F97125CULL, 0xD524353F90C3E9C6ULL, 0x837471C0C1C10633ULL, 0x68371045AC871233ULL, 
            0x4E717CBDA477735CULL, 0x80050E5D340D2DF0ULL, 0x5B7CCE977F75C08EULL, 0xE99C9BCC1617ED00ULL, 
            0x443293F98C2F8C4AULL, 0xC938824A3205F5BAULL, 0xFAEF1B681C90E18CULL, 0x1B2F9B5E7C10E23AULL, 
            0x855739E9F4F98383ULL, 0xB4906859EA7FD934ULL, 0x33783D25569A82B5ULL, 0xFC292287F3D1E258ULL, 
            0x0BB81C78898E0D81ULL, 0xD720FE35D1592730ULL, 0xDEE53A7AD826F501ULL, 0xF96401B3222DCCF6ULL, 
            0x59A450723FA1DF95ULL, 0xEA93015DC8770FB5ULL, 0x18998BA1E0532BDFULL, 0x791EC98CCD0168C0ULL, 
            0x1772DEE62EA5E075ULL, 0xC925EB2E979A4932ULL, 0x813A18AF09AAD836ULL, 0x99C257B20FC749C3ULL, 
            0xB516F9A4C00253B3ULL, 0x8DABEBACEE1503C0ULL, 0x2F8AE48F6141B59AULL, 0xEFF71FAB1B9FAAF8ULL
        },
        {
            0x0855BAF7C4F946D4ULL, 0xD86E01E953FA2F79ULL, 0x350D677A71391AA9ULL, 0x1673F9DC1AB52CFBULL, 
            0xF82576FB8101B7D3ULL, 0xE35E558B0AE01540ULL, 0xC68F0E6113A90198ULL, 0x172C2CEAD37BB332ULL, 
            0xE93B9A9E43A2FA40ULL, 0xC349D17B91E70DC3ULL, 0x8348197AE65A50A1ULL, 0xFEA03938B7F3481DULL, 
            0x0E288F8425D95C67ULL, 0x1B10F5033D0380FDULL, 0xB34E4DC9FA6EB125ULL, 0xD58330EDA8B9BA4DULL, 
            0x640FA7A0A5E0D0C5ULL, 0x4998516119C30B0FULL, 0xC409ED4AE08A6664ULL, 0xAF2ECFA9DE2B2F1CULL, 
            0x5D878FFD3A4734CBULL, 0xAABA1C1D2205EC01ULL, 0x776D9091F020D04AULL, 0xDEB6DAC09246C7E8ULL, 
            0x8F5F27F2BA84100DULL, 0xC926BEAF4A767FC7ULL, 0xF3454AAE44D9AA1EULL, 0x9CC5D7B5820D01C3ULL, 
            0xC45F7329C3A8F8D5ULL, 0xD545D5AA2E355F7CULL, 0xBBA175D158C3969BULL, 0x324FF7CDA83834FBULL
        },
        {
            0x80D73A89DA1E17DFULL, 0x0FE3687D824B0A93ULL, 0xF64D3BD04865444EULL, 0x2D2EE3D135AA1DD3ULL, 
            0x0A7C8713E8836467ULL, 0xAFADC36A1611C956ULL, 0xCDDE9221D3FDBD9DULL, 0x4CEE20A001BDD1F7ULL, 
            0xF7A7B203411D306DULL, 0xB145F2E552E66E2DULL, 0x67F2A81A123F151EULL, 0x5F803829280C2E49ULL, 
            0x474F65111B0B5476ULL, 0xD42A7ED070405E21ULL, 0x1E7B54AA7AD8C78EULL, 0x050CF1611F0CD54BULL, 
            0x6F324BB310FAAC14ULL, 0x1634C3454834F233ULL, 0xBB978F0A7324FB4CULL, 0x1881174EC7279A70ULL, 
            0xB84C69211BA1F1BFULL, 0xAAB3934D4B469798ULL, 0xA2A8785B25266EB5ULL, 0x80E3D0B87636E236ULL, 
            0xB0E63020E53AA189ULL, 0xAA66BF6DB6FC904EULL, 0xFB53BD9F7541EC45ULL, 0x9B4CB82A72C663B5ULL, 
            0x05A4FA20EBB853A6ULL, 0x414A289CEB8DDB91ULL, 0x0A141E775F62BE0CULL, 0x5A6CC8846F078A45ULL
        },
        {
            0x5946E5040E58E002ULL, 0xEBF1F67004A36753ULL, 0xB3D0616899C7697EULL, 0x66339BBEE1E24DD2ULL, 
            0x2D5D1CF8D1FE7C70ULL, 0xB5C3D3D35136BFF3ULL, 0xDF7BAF0400BF44B8ULL, 0xF32BF035B8CA3279ULL, 
            0x0DCD3536264C6943ULL, 0x3B7D6BBE056D57EFULL, 0xDDF63EEE1C22C8E8ULL, 0x7B5CB0977FC688BEULL, 
            0xD175CD199D1FCEB3ULL, 0x6256428D632B26ECULL, 0x362C05B3C43119A0ULL, 0xCCAA83D236B75FBEULL, 
            0xFF7343610AA9AF55ULL, 0x582B9609C4AD958EULL, 0x98F827D8B603F2CFULL, 0x9F72634026FB07B5ULL, 
            0xE7DEFE78FF22E0F5ULL, 0x9116700D74C306DFULL, 0xE5993762FBE5FCECULL, 0x0A83CB176C1B5300ULL, 
            0x45C55D6DDB98E6D2ULL, 0x1F1A50A9A0B90080ULL, 0x8ECCBE8A420B78C4ULL, 0xC71C2F3FD1C394DDULL, 
            0xB53739CEE9844EC8ULL, 0x401E62E4FFCDDB0CULL, 0x05E1D8CB71BC3206ULL, 0x3C65558A9668FE12ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseEConstants = {
    0x54EB1F4649ED7991ULL,
    0x8C445C41FBEA3A47ULL,
    0xEE17570FCFC95572ULL,
    0x54EB1F4649ED7991ULL,
    0x8C445C41FBEA3A47ULL,
    0xEE17570FCFC95572ULL,
    0x660D5AFEAF2C8D3DULL,
    0x596424101359C4B5ULL,
    0xF4,
    0x58,
    0x45,
    0xDE,
    0xD9,
    0x7E,
    0xB5,
    0xBE
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseFSalts = {
    {
        {
            0x12EF847558D48707ULL, 0xCA340BDA2665C79BULL, 0xE4C596FE29026D45ULL, 0x5AC2904F7C80F55CULL, 
            0xBF5ACD61B1EA8459ULL, 0xD104A8FF440E0FBFULL, 0xD1D3363C729077CDULL, 0x8982B7DD7C76A984ULL, 
            0x628A006512711AADULL, 0xABFF1511F272D6A6ULL, 0xB6844F500FE699B1ULL, 0xE6C3B31BB7DB5B4CULL, 
            0xA0C724DFD31DE404ULL, 0x8D9F20C1EB5BB5D7ULL, 0x902EAB72CF551778ULL, 0xE4588B6DE9383FE9ULL, 
            0x45A65C2A3307A305ULL, 0x1FC639BDF1D4AD10ULL, 0xDA83D088065D1B33ULL, 0x969AC1958734E39CULL, 
            0x253D102E3601BF69ULL, 0x4B48B9D17597B47BULL, 0xEF2F682D29CF3E5EULL, 0xD4772BA7AFB9440FULL, 
            0x3806B0992D287A9CULL, 0x618D845714D58EECULL, 0x22CEBDA131D2E6CBULL, 0xDF9D50B74595E620ULL, 
            0x7827CF39B0AC6D43ULL, 0xE8E8EFE640788003ULL, 0x990E25C76E4249D8ULL, 0x6A7F0A6F87CAEFD2ULL
        },
        {
            0xE0F3CDBC1238BE73ULL, 0x40A00B67DDC9D160ULL, 0x91C810652FF02B97ULL, 0xE6D78053892EC1B6ULL, 
            0xD4E52C65848F258CULL, 0x983691093EE5934AULL, 0xB76E73D5B2192A31ULL, 0xCCFBBB6E14A625BBULL, 
            0x487E7E94ECAA367FULL, 0x5AAC440FDE2E841CULL, 0x233563BF98E55E94ULL, 0x1E7F56B898952091ULL, 
            0xACA7C4EDB88DBB9CULL, 0x13F8C064579ECB8BULL, 0x79BC181A8C9B3E13ULL, 0x1808A69E711AB16FULL, 
            0xE5C7F50D805F3D57ULL, 0x834DB087E7968F3AULL, 0x9D1D19311D1CE14CULL, 0x463F026C4C9D9202ULL, 
            0x0F1938C4F2323C87ULL, 0xB2CB2A1869AE5112ULL, 0x0ADF44F53B731892ULL, 0xD1D2F4B54E7B1009ULL, 
            0xB70B0A424E094B32ULL, 0x415312ED395DA14EULL, 0x5C17EEFA616BD0D9ULL, 0x5D9C3803E7DD225DULL, 
            0x8B155590BB228F77ULL, 0xFA7E66297CD87508ULL, 0xA253782AC0E19C18ULL, 0xEC11CDF8344CD0F0ULL
        },
        {
            0x30B084A8E9ACB0E3ULL, 0x88414F653DE1C1A8ULL, 0xE774BFB85AD97F9BULL, 0xB4132F6A1BE43318ULL, 
            0xF4F3589A99E3A05FULL, 0x4898675A751BB4EDULL, 0xA3D67A36FCA6DEA5ULL, 0x2552F293FE924FEDULL, 
            0xE457D5EBC3FD9712ULL, 0xE7D7EF8233963D6EULL, 0x56C1D83A65210116ULL, 0xE7B785482D2B6FBFULL, 
            0x3339FADF1367D114ULL, 0xE11BF93F12275746ULL, 0xBA0F091433A457BBULL, 0x4FFAEFB542D236A8ULL, 
            0x8045D6A4F2932CC7ULL, 0xCC28E582AD490623ULL, 0x87FAE959160D15A3ULL, 0xE8237768FFB57CBDULL, 
            0x73EC0A8EFEFF372AULL, 0xD51DAE4BD3D951ABULL, 0x451E1D19D68861E5ULL, 0x27EEC191229DAD70ULL, 
            0x4F0DC73CAA37F50BULL, 0x9C423EE80B5B6911ULL, 0xF0F0C5AC8E9B7F62ULL, 0x587162F29A94397DULL, 
            0x2754E3B3BE7F77B3ULL, 0x2D205588EA9A6122ULL, 0x659BF10535DD6A6FULL, 0x64287919583FB84DULL
        },
        {
            0x013CFFCD08651F95ULL, 0x01409C1B67A867CAULL, 0x6CD2716123621456ULL, 0x3F99B35E272F9DA9ULL, 
            0xB5620ECEC419866EULL, 0x9A350B31FA8288F0ULL, 0x4D129A750D8A24B3ULL, 0x3EB51C3B68D4AE1BULL, 
            0x5F0C34C57B8AE265ULL, 0x6FF1B22D10F0E05FULL, 0xD49F7694156B8F00ULL, 0x75D58B1FFD27020CULL, 
            0xA043EA0BF44A340AULL, 0x740D9762E216711FULL, 0x2476C6235DA24AB9ULL, 0xD82C49EED125BC03ULL, 
            0x39A045E85CA67BD1ULL, 0x2147357F00A667CAULL, 0x281C219E71667D93ULL, 0xAB22D8B7B753B247ULL, 
            0xB19892228DE13C38ULL, 0x694FC242CA5FB0E7ULL, 0x04682E5BEE03B4ECULL, 0x0F4805C5F62939A1ULL, 
            0x1EC8B1330E514D69ULL, 0x9332469FA5AA41F0ULL, 0x785A8179102E89F9ULL, 0x3C431415ED33FAF1ULL, 
            0x0970CA335EE54EFAULL, 0xBA92241DE3F4EEBCULL, 0x730BD455AB00D681ULL, 0x1714181ECA882D6EULL
        },
        {
            0x88603CD4D2BA01B4ULL, 0x7B433029DBCCBE70ULL, 0xA133E278060DA428ULL, 0x0F740A80E2B9B457ULL, 
            0xB90D843D2F0CF285ULL, 0x763ABE6702EC5285ULL, 0x5808752286CE7B15ULL, 0xE5293574E75502DFULL, 
            0x11B9DC805FC1488BULL, 0x792195B0D50E857BULL, 0x583BB0A1390D98E7ULL, 0xB7CAEB44257184CDULL, 
            0x88A2ABB1882DBF47ULL, 0x36FFBC2A50BA8459ULL, 0x0FBFA94AF7FA08FEULL, 0xE3DDC777ACA604E1ULL, 
            0xF2AF885B72468C4BULL, 0xF7CC4B2C49F17196ULL, 0x3A256AF87FF388B0ULL, 0x2CE06352230A1FB6ULL, 
            0xCE4AEE0F23C180B2ULL, 0x9D78D14E070C4B7CULL, 0x8876A9D9F9C66CF9ULL, 0xFAF33C3A3C849183ULL, 
            0x8BCD0C22A32F318AULL, 0x21DA35806E664671ULL, 0xF5C0BFBEDA4A35E5ULL, 0xB9CE775E5175EB3DULL, 
            0xA2A1702B66E85131ULL, 0xB0FA0122CD47C34EULL, 0x9A9B0DE2FD85E2FCULL, 0x03A2BE68D8DBD6FFULL
        },
        {
            0xAEBA30B4F5F5F432ULL, 0xC4F9A1930CF75D36ULL, 0x3BFC908CB646669DULL, 0x5B7A56C535636F07ULL, 
            0xE25F6DC8BFF76D3FULL, 0xF4B0A4A44A446B34ULL, 0x551703B5C97438A3ULL, 0xDCA5426A3B9CDCC4ULL, 
            0x88784CDCCBA23C3FULL, 0x147AD3D813CED8C6ULL, 0x0D7138DEDA0425D0ULL, 0x89ABD0C8EFBA0942ULL, 
            0xE829FF3B7E0734A2ULL, 0x1D6CEAA7B9BA83F4ULL, 0x8522738FCA5F374BULL, 0x9179F79195674033ULL, 
            0xD655BC807DD5F378ULL, 0xD3E1D13FB274485DULL, 0xC8AE8E136B58587AULL, 0x9B4C415A50122C3DULL, 
            0x922AAA6FE4ADA362ULL, 0xE3D9D4DD6BBF2C8AULL, 0xDAB68F391C9C7CCFULL, 0xD8C812C825DCC428ULL, 
            0x794FCEAA5EEE0371ULL, 0x262963DF3FFE5F12ULL, 0x11A067D1EE7D231DULL, 0x0E5119042B913369ULL, 
            0xFDC94C2307E0F9C7ULL, 0x2769C4D65231E0AFULL, 0x26B7A418DE7CACD9ULL, 0xF6C6AC8B40030C86ULL
        }
    },
    {
        {
            0x35F3BB6D47199ADDULL, 0xCF01F47BF09C3F17ULL, 0xDB95584755A0F617ULL, 0x4294573D9B665716ULL, 
            0xBD00DCC0117D2E91ULL, 0x4CCEA6ADEE25D19DULL, 0xC96031B5D93132B4ULL, 0xD40592040A911DA3ULL, 
            0x49196C9CDD2D6023ULL, 0x79EC103CE6E3E39CULL, 0x6B14142511ADC03FULL, 0x0D47BE798BCDE7EDULL, 
            0x9518A1DF57B8EDF7ULL, 0x95AD759CB4DE0E58ULL, 0x067A1AAE345986BCULL, 0xC767DEFC49BAD981ULL, 
            0x8DB95173A56B30EFULL, 0x3DAF540DD5C96B67ULL, 0xBF794DB320BE8FDDULL, 0xAC31242E7E9C7E11ULL, 
            0x33780E064B9F34B6ULL, 0x8EF472C4EBB765D2ULL, 0xCA9DA860E0DD1DEDULL, 0xF13BE627352373F7ULL, 
            0x889DF95D9E3E6EF4ULL, 0x6326837DEDA085B6ULL, 0xC844E485EE8C578EULL, 0x6E5B05BFA260EB8EULL, 
            0xD12B860624417867ULL, 0x98C6F700C6E00F19ULL, 0x3BD6000891EEDFF0ULL, 0xC2976F1282624A70ULL
        },
        {
            0xB79D8C5E3B100ECEULL, 0x3B5BEE84BD4F2825ULL, 0xAE961AEAAEE1C38EULL, 0x12344B586598AF6FULL, 
            0xDFD2FDCEA11C776CULL, 0xEB49206EE6809984ULL, 0xCE4339B701DE3FCEULL, 0xF8A231FD10DD8655ULL, 
            0x051C4D11EF520D38ULL, 0xDCF4A2074319CF3FULL, 0x68B02B095F92216FULL, 0x0E11916C9B9BDC72ULL, 
            0xA2122070CB46A36CULL, 0x49DD76EE4E9EE1EEULL, 0xD382C5C068887623ULL, 0x97674CD2921C2AB4ULL, 
            0xE7A382438E247F91ULL, 0x47131D5162D6B5A1ULL, 0xF491D61E70A76B58ULL, 0x830A357D2E705BC9ULL, 
            0x49B75D57FED9FFDCULL, 0x4B82145B32B7881DULL, 0x47AC6B9B6F203897ULL, 0xA4BD49FC45F3CFC2ULL, 
            0x323B419E1305610BULL, 0xDBAB6061054CF352ULL, 0x6D2C449155EC90D3ULL, 0xC310625366509E1BULL, 
            0xC5E146CE3A86FD75ULL, 0xC612698B164C992AULL, 0x442C55D6070A023FULL, 0xDAF175818DC8C4BBULL
        },
        {
            0x6D1DB9F9CBBD5023ULL, 0xEB5015B08C95CFE5ULL, 0x73AD9642D5375F62ULL, 0xF53008DC6418DDF3ULL, 
            0x1F90C4F1B06D197EULL, 0x22D426586F465D25ULL, 0xE771C253ABAD792EULL, 0xCD73D3B86C9D89EAULL, 
            0x867EDE0F1C5F2D42ULL, 0x5F24BA3D125AAAB2ULL, 0x9752AD684E93E838ULL, 0xC80FA6DCD9D5A2F5ULL, 
            0xDAD72B5E14FF2E48ULL, 0xC85D9BC5A58CBE7DULL, 0xB9FCFB2D74E3ED73ULL, 0x401A4A1BDE986F15ULL, 
            0xC8D425F75574A3AAULL, 0x06E8762A1C4F38BEULL, 0xDC038204CBDF6B6BULL, 0x0FF8EE0CAF041728ULL, 
            0xBF39B575C7D7F728ULL, 0xA6F7E8C1690B5854ULL, 0x86359F8BEFE7D345ULL, 0x1327D757CC452FD9ULL, 
            0x5D184BB5A79C720BULL, 0x0375C9DBC360B231ULL, 0xE8E1F5C0F4966FABULL, 0x0891FDE20435EDA8ULL, 
            0x0A5DD9CCE70462FDULL, 0x740709DA6A14DB9CULL, 0x5CF91514954DB857ULL, 0x9C8B8DC02A376E15ULL
        },
        {
            0x19DB365FF5B85CF9ULL, 0xD322E81CB6B16CDFULL, 0x582A012A53C6BB27ULL, 0xAB2AE5E7B4452E4EULL, 
            0x7665F6A73AA5ADA9ULL, 0x842B61F6EDB8B3A9ULL, 0x699198ACF4D7A9D8ULL, 0xC30587FF6ECCB89BULL, 
            0x36D37172FE571577ULL, 0x7DB1D581C47677C0ULL, 0xA0A45053797764DCULL, 0x0B0BA9F8CA2EF24BULL, 
            0xE244A80BBB30108EULL, 0x8E78295E5FA04B4FULL, 0xCA56323963FAEBA6ULL, 0xB4FA89E760E997C1ULL, 
            0x25996D39A0FCDBD8ULL, 0xFF0DAD969519AEB6ULL, 0x4A67BCCA18E59077ULL, 0xA460ED0591F2C7BFULL, 
            0xC5D611C657D0834DULL, 0xBEAC9B80ACA4E822ULL, 0xA23186FCD3A313E1ULL, 0x73E6459DE4B8F82EULL, 
            0x4065E1C0E4D87A96ULL, 0x00AE6B07D8319D7AULL, 0xFCAF438D522F3E03ULL, 0x660F543141771F29ULL, 
            0x1DE4F74FA2A83BC0ULL, 0xBCADDFEC0E977AA9ULL, 0xE3C1690F02BF0E9DULL, 0x82C793C59AB40A8CULL
        },
        {
            0xD7D42036A36EEC30ULL, 0xD67E0364691AEFFCULL, 0x0330BEB0488D8CD9ULL, 0xC94CB303819674AFULL, 
            0x786524D579E0A7F7ULL, 0x2A26ECD78418699BULL, 0xF034426962DC4EFDULL, 0x03C6BE21D4E08D3DULL, 
            0xE9C63129E14F5327ULL, 0xB012DAB85E3E7290ULL, 0x0DDB08071AF9A1F6ULL, 0x69F972C179AD9FA4ULL, 
            0x831EC56422C2594AULL, 0x2B7FACEFAA45710DULL, 0x459ABBB41F4798AEULL, 0x2FC1CE17EE14D414ULL, 
            0x7B4CB79960DAB8B2ULL, 0x4B16F36045A009C0ULL, 0xC38F816EEE5F0985ULL, 0xC2D6CF1446BF302DULL, 
            0x418F40363C1AD085ULL, 0x986FC6D96CF13454ULL, 0x0D14312DBD9CFB22ULL, 0x0765EAA3AE598722ULL, 
            0x136F0A1E434D0213ULL, 0x15A4B8B0BC7578FFULL, 0xA11D24C469A1DA85ULL, 0x15FD1C45B171903EULL, 
            0xE6C1FBD70E3BA13BULL, 0x2B12E95634C8F490ULL, 0x86DBF7DCA40F4FA9ULL, 0x321717A99759FE35ULL
        },
        {
            0xF5373ADA1EA76610ULL, 0x67FA3AB8C06E0D05ULL, 0xB2D825E7F434F0AEULL, 0x91AA34F4396B27C3ULL, 
            0xCB2ADECDC29CBE66ULL, 0xA277C9FEDC853A59ULL, 0x3BE47913168CF0DBULL, 0xCE60CBFF0483327FULL, 
            0xF03DD70947D4930DULL, 0xCC489F44F44604BDULL, 0x6420EA54A3E3EBEAULL, 0x47DE861E3BD9AC24ULL, 
            0xDAC652A0B33D796DULL, 0xE5EB8C483F4050B9ULL, 0x6BA1A1071BF16AF2ULL, 0x26F36B42D9BC1EDEULL, 
            0x262904751163B730ULL, 0xFDBE583303EBD70BULL, 0x4DF76A42DBDF69CAULL, 0xDFA3DFE312AF83D5ULL, 
            0x476993AB521F2A30ULL, 0x88104CE43E9259C4ULL, 0x793001F7B1F5DEE0ULL, 0x86DB420793174347ULL, 
            0x55E4FBC7590E6719ULL, 0x392A1D85B5640AF2ULL, 0x696DA9DE93ECB7E1ULL, 0x356F6E96BBE9CF2DULL, 
            0x558C0956A0DED412ULL, 0x9ABE34AEC8264F60ULL, 0xC506E23DA26362EEULL, 0x8753AC2FA0D96159ULL
        }
    },
    {
        {
            0xCCA638DE80B2BB0BULL, 0xDC962BF0E9854CE0ULL, 0xD8124DFC7853DE92ULL, 0x5B0B742ED1DABFB0ULL, 
            0x1BB36CEA830794C5ULL, 0x1637D5C0CF15B530ULL, 0x07B30D382F86E40FULL, 0x67D91D4737EC847EULL, 
            0x45C718170500B5ADULL, 0x635F882EC3C731A6ULL, 0x16F8E256765CE010ULL, 0x0F160633EFC8F353ULL, 
            0x819E1AD8B842870EULL, 0xB52EB2B3EEC7FDCEULL, 0x7A838C586ADC79DCULL, 0x29A8D642B32D15ECULL, 
            0x398D157CFF9C4705ULL, 0x6BD9763773B9FEE0ULL, 0xCDF5252F8FDA5B2BULL, 0x4BF4D31A40B618BDULL, 
            0xFF976F4DD38BEC9DULL, 0x7E018621D3DD48DCULL, 0x60419F439629A791ULL, 0xC287B1CC6030F32AULL, 
            0x659EAF06007D3E5DULL, 0xB5ED4EB251404D40ULL, 0xD8EB0EA9975CA805ULL, 0xB9B83F49630C46F5ULL, 
            0xB6F6EEC3B7DA276BULL, 0x09C5E46CC402C049ULL, 0x394C29823B23D22EULL, 0xAE3186D804026115ULL
        },
        {
            0x45ED193457D4CC1EULL, 0x68738F9966CB07A9ULL, 0x13EACDEFDB1574FFULL, 0xD1F235BE3A3E905CULL, 
            0xDFD1B330882AFB79ULL, 0x6CCCE5E050F1AF0DULL, 0xCBBFE546EC18E247ULL, 0x06FBD66FE137CE3FULL, 
            0xF4F4E6BEBA71C872ULL, 0xBF42E623A2343ADAULL, 0x22363E4E28774601ULL, 0x4A04317320F9A69BULL, 
            0x4CDB61CEC7151451ULL, 0x2A45CDF078404088ULL, 0x9C8484C2C2E5FA03ULL, 0x62D57CCED8BA97D8ULL, 
            0xDAA6361E24B7FBB3ULL, 0xDD06C3ADA17BEFC1ULL, 0xCB103622309F611BULL, 0x1AEB1858F0A589EDULL, 
            0x05740582AFC0E3FEULL, 0x724155FABB6DF2FDULL, 0x8546F6A72C432101ULL, 0x493C924CA569850BULL, 
            0x3E5303FA4463F4E6ULL, 0xA86A5584FE0D81B7ULL, 0x16004A40BF8E24F4ULL, 0x96B0B0108C98F9C7ULL, 
            0x7C031605A7794BBDULL, 0x961A5AA783EF7C7CULL, 0xA7F42CFC9E1DD67CULL, 0x4841555F9AE7C8C6ULL
        },
        {
            0x61B950A6EA7E543FULL, 0x2BD957DF252E6647ULL, 0x2F37E7B216094FF2ULL, 0x3086129EE09219C8ULL, 
            0xA2FDF4240A6742E8ULL, 0xC55D277167E36041ULL, 0x16A2D760B0989A3EULL, 0x7787D52AD51A2D04ULL, 
            0x01E5206861F2017BULL, 0x669EAB735FAABC85ULL, 0x0A69FCE6C4DD8556ULL, 0x85925F41A781FA2CULL, 
            0xB3587F1F22376AE2ULL, 0xB2EED6A22E6F3561ULL, 0x3BD1B9EFA7421A54ULL, 0xC0071ED0A5E65EA6ULL, 
            0xC88A882D44F09CD4ULL, 0x17470441C881B092ULL, 0x202CD135B451E0D0ULL, 0xCBF2359A544B97EAULL, 
            0x10D6483F8573D502ULL, 0x6B8DA132468F4602ULL, 0xB49F1C2E19D6A733ULL, 0x61F0C8A2E4533669ULL, 
            0x906AE2B2D4A61B88ULL, 0x1D87D6184C6BF8BAULL, 0x1893D3F1BEA2E04FULL, 0x02086E19129371E1ULL, 
            0x771475E1F9D1250AULL, 0xEFF392C81DD27013ULL, 0x11820EBB7090635CULL, 0xB50E5A8EACA70EB2ULL
        },
        {
            0xCC833BD15A196557ULL, 0x7A4BD9223F72305EULL, 0x10ACCADEC87DA2C4ULL, 0x86D340E21834DCEEULL, 
            0xAA7743029551431DULL, 0x2D0EF88D8A83324CULL, 0xF1786467DF7094A4ULL, 0x7885B058595C2D90ULL, 
            0x0D2291248E7821ADULL, 0x309F70A287F979FCULL, 0x130B791C537CDB08ULL, 0x9F9B6F8450D0CBD9ULL, 
            0x849264EAF539E4A6ULL, 0x7EAF1DA74C1808C8ULL, 0xDE35119F9782FC89ULL, 0x3EE9AE2DBC439A00ULL, 
            0xB98C3C1D238B4016ULL, 0x455973454CEC4170ULL, 0xF09BD3736AAE6710ULL, 0xB492FEC0ED3A7136ULL, 
            0xEFC9B2E8133F4C79ULL, 0xEA6371510A4718EEULL, 0x15BFC1041F4D2BBBULL, 0xFF9CCC792127A1C3ULL, 
            0x2F1EF79BEF68260DULL, 0xF754A2C324C3C1EBULL, 0xB9063F2AF95C11F3ULL, 0xDE32D77C391D92CDULL, 
            0x9AF9D290D90FCEC7ULL, 0xB792B063E766733DULL, 0xAE807C356BA9119FULL, 0x574CCA013AE743FAULL
        },
        {
            0xAA06656267D89EB5ULL, 0x0826EB1293DCD428ULL, 0x92220A21AE55F1F1ULL, 0xA82754AD11779210ULL, 
            0xD8361797FB83CD0FULL, 0x5479CCD71E4BC1EFULL, 0x05C00E115C00E652ULL, 0x823E2648AC40B571ULL, 
            0x1CABA022A022CC4FULL, 0x2352DFDC83086C42ULL, 0xD8F41FF1616475C7ULL, 0x95E88BC17E15553BULL, 
            0x92B1714C50509517ULL, 0x8557719F6EB42655ULL, 0x4EE89CFE416E728AULL, 0xB804DB0CAD314A1FULL, 
            0xCF10D85065F21608ULL, 0x8F53F6351652D543ULL, 0x401CCAB99FAF8BB5ULL, 0x1308EC506BEBB032ULL, 
            0x0C64286D6F0F3201ULL, 0xDEB4470E18153A4CULL, 0xF2EE6D0FE00DEB1CULL, 0x5F87C1DB79DCB596ULL, 
            0x9F5BE6AF376A3182ULL, 0xB6B2EDF1D1907383ULL, 0x0A94100CF3C8C3BEULL, 0x7AE4D1C4E6970AA5ULL, 
            0xD626CC2075C022F1ULL, 0x21BABEF9D7AC65FDULL, 0x1708E527282900B8ULL, 0x7D2DB9B57676FA30ULL
        },
        {
            0xA28D9EB02E475C26ULL, 0x2F11000462411074ULL, 0x5A97C98800CCE27FULL, 0xA15301095FA13158ULL, 
            0xD3D7D54693513DF9ULL, 0x4C45621CDDD2D271ULL, 0x804725FDD249C8E2ULL, 0xE04378D2818280A0ULL, 
            0xC9FA06CCB117316DULL, 0xEF020B5C067F4965ULL, 0x73BC003C83AC2C84ULL, 0x6C090D30FA63CE2FULL, 
            0xD8FDFF251A98DDBFULL, 0x6A73C5DB4BB9A25FULL, 0x92919F151E016E96ULL, 0xD519D272AEB9B1B0ULL, 
            0x45EB2C203155F73DULL, 0xB8594114D49C6897ULL, 0xB24E80E18625A060ULL, 0x2024A5F4306799E9ULL, 
            0xD5AE74D2CBD33DC9ULL, 0xF857EEBD780B69F6ULL, 0xB22A8C0039841223ULL, 0xDB557ED7EAC433A1ULL, 
            0xD17D1C10AF2C7D85ULL, 0x03A97CF33CA3B2FFULL, 0xF45B1BC3A0509F2BULL, 0xD070AD63727DABF2ULL, 
            0xDDA25738CD687B31ULL, 0x7ACE880A22DFF332ULL, 0x20760EEC704E59DBULL, 0x03C2BBF389E6060DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseFConstants = {
    0x47ECD432D565C808ULL,
    0x5622BA1E0B68CEBCULL,
    0xE940C2C9D189CF92ULL,
    0x47ECD432D565C808ULL,
    0x5622BA1E0B68CEBCULL,
    0xE940C2C9D189CF92ULL,
    0xAA40448CB222D97FULL,
    0xF6C35CC0D76A6E05ULL,
    0x45,
    0x7C,
    0x52,
    0x34,
    0x32,
    0x0A,
    0xC2,
    0x11
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseGSalts = {
    {
        {
            0x84ADE96FEF98DD9EULL, 0xADB87074FF48C87FULL, 0xBD6C0F1305C1BA52ULL, 0x8D41B0391D1745FEULL, 
            0x0DC0C8E4DD4743ACULL, 0x9AC37D2502C5A25CULL, 0x3F81AF648BADBA2DULL, 0xD31C76E309FF1341ULL, 
            0x4FE695235DB2835FULL, 0x98EA22ABFCC8FEE9ULL, 0xECCBC58C055BD07EULL, 0x54C4976F5433D4F5ULL, 
            0x1AE2C3A5C5886D6AULL, 0x318F648D8C7F36EBULL, 0x0C0FC04BF7D4BBCCULL, 0x5DEE99EC4853C620ULL, 
            0x65EFA24168B7DFB7ULL, 0xD640240D87CF9B6DULL, 0x97E5F38D53BD0970ULL, 0xE8899AD796879EC1ULL, 
            0x6FABD687E9AEA933ULL, 0xF05EA3E2EA43E428ULL, 0xD316CAE65A6AC14EULL, 0xB0F4460EB171142CULL, 
            0xB3706B534C6A8F53ULL, 0x709B3B9B598D3F1BULL, 0x019B080505EA1CCDULL, 0x33D7F5E46D5605E2ULL, 
            0x25FAC43DFA10AF08ULL, 0xFCB6741CE78B7B5EULL, 0xD52D5684BC3EBC4FULL, 0x1E8CC321C74C7601ULL
        },
        {
            0x2E9FC4E41A4F2886ULL, 0x35B13AF789881238ULL, 0xD734C6842B0933CDULL, 0xB59AD0D2233AD486ULL, 
            0x97A673651974CA14ULL, 0x5C379321A764B1DDULL, 0x3611CA6C14B88CE4ULL, 0x1EA83B60158695C1ULL, 
            0xA573416F7C520987ULL, 0x41EAC9F876E9A0D6ULL, 0x65943CE9B10C7C5DULL, 0xAC5DEA170F87313CULL, 
            0xA92BC8FF07273A77ULL, 0xDE3413A65A925BC1ULL, 0xE07E046DBB87FC63ULL, 0x06AC24EAEA9D8560ULL, 
            0x3108011F2320FB29ULL, 0x1B2BB1AEF8B186DDULL, 0xFF3A7E729A1CE058ULL, 0x9486A9C690DDD15AULL, 
            0x06A7714954335B18ULL, 0xA5596A1A9D15D02BULL, 0x21B483E28A397923ULL, 0x1C70A641ED627A6BULL, 
            0x4C3FB3861E55B970ULL, 0x3E3B46B8557C3694ULL, 0x125C799A3D8F7DC4ULL, 0x27B3F46E98E373C8ULL, 
            0x6A0175BD196A5489ULL, 0xC5873BFED09E517BULL, 0x697013DD0971458FULL, 0xDB4BD682EBC82F53ULL
        },
        {
            0xB866A8A785C67113ULL, 0x66D8F02B9D5C91B0ULL, 0xF50AAF2F5B6C2218ULL, 0xBBBCD4CFEDA7D6DFULL, 
            0xB345CB8AD02867A5ULL, 0xCE546B33230736DEULL, 0xA97CB2DA8F3BD849ULL, 0x0065C60FB40A8144ULL, 
            0xC1FDEB82D27A230EULL, 0x780194C520A274E6ULL, 0x86C1584042CF6FA5ULL, 0x797A093DBB4D1D8AULL, 
            0x2D83647E8EF97C1EULL, 0x23C166FC12314452ULL, 0xF7AE54B48A000D0BULL, 0x861AC7D63604837EULL, 
            0x14B01173BFB0DACAULL, 0xC4B82FB4764B087DULL, 0x33AD28D7D97307B5ULL, 0x7BE91AF3BCB6B192ULL, 
            0xF92D21221263ABE1ULL, 0x67F14B72CE3C75EDULL, 0xC3E592A7D843342EULL, 0xAED64DA1C74C0B26ULL, 
            0xC2F1617705E54E18ULL, 0x618A61A71FAE6DF3ULL, 0xA2038DEEA4156478ULL, 0xF9AEB4011ABC67DCULL, 
            0x3C3200D595C42A21ULL, 0x0D23747D8DFBC5C5ULL, 0xD7D63467D3140B6DULL, 0xB1602111452145A4ULL
        },
        {
            0x258342A3292A2563ULL, 0x4525CE19A203B34DULL, 0xCD29E0A92DC5B2A7ULL, 0xAC812BF8546250D0ULL, 
            0xD9BE36B2B0183474ULL, 0x94570D66A2645341ULL, 0xFE74951DA74F8BB7ULL, 0xED2AAE871B58B9C2ULL, 
            0x1ED7C1384FC4B9DFULL, 0x03299AD9C9FD7058ULL, 0x89843BEF2AE3A066ULL, 0x0BC295FD203966C3ULL, 
            0x090EB0B4C225EBB0ULL, 0x2700FD3DE38C24DCULL, 0x7FC5527F3C78291DULL, 0xA14D289F87F378DFULL, 
            0xE9F3C589A6C7B3C7ULL, 0x50FE107CAD2F172EULL, 0x5713EC4743AD09E9ULL, 0xFDF434A840891BA4ULL, 
            0x666AAC65C501A30DULL, 0x489AA236B4FB1BD3ULL, 0x26338B5C5AAF4DBAULL, 0x5F423A47CC78E004ULL, 
            0x4E1210B3928DFA59ULL, 0xEFDE994E027B0521ULL, 0xFAB90BE8C05ECF90ULL, 0x30D045FE084C51DEULL, 
            0x388098774D24C3F1ULL, 0x16069420EFE6DE47ULL, 0xFDD0B6ECA1EAB24AULL, 0x67029FF26B3DBBEBULL
        },
        {
            0x4B8B205F5F21F2A1ULL, 0x2875738FE4737288ULL, 0xBDFD03557742C2C8ULL, 0xF748BC03ACBF9D73ULL, 
            0x263667A92DD789C6ULL, 0x8871392B59522E38ULL, 0xDD8236A01B03CCFBULL, 0x86591C54BD21399DULL, 
            0x7F0AE18ED0F1F19CULL, 0xC7615F82C075B04CULL, 0xCFC8A09B09970B42ULL, 0xA3F53EE0D2C688CCULL, 
            0xE96CA4EED25A4D7DULL, 0x6A45CF16D1B584E3ULL, 0x0B1484C9956EDA8BULL, 0xC7702CA073834CDBULL, 
            0xFDA30B9A5B4CD1CEULL, 0x7E71B13B3AFB5DA9ULL, 0xBB138F11DC3BC1D7ULL, 0xF059BE7CEC7D2348ULL, 
            0x13AB459CF78BFEE9ULL, 0x1757E211D6CF9F57ULL, 0xF7B696D62647EED3ULL, 0xC595FE5316ED5DD7ULL, 
            0x57B41F69F5F7DDEFULL, 0xDB47A1737A599E4BULL, 0xBEA846CF57383A9CULL, 0x72235F1E6147C573ULL, 
            0xC11C1931FDE47991ULL, 0x62301CC86700DBDBULL, 0x4978D58FB1373B06ULL, 0xB007FC46789325EEULL
        },
        {
            0x757F97DD5977B946ULL, 0x5D13F4EDCF45AC78ULL, 0x0917F0B4A1AAC923ULL, 0x0BDB3B3E3D3C56BAULL, 
            0xB15091AC2D42E5EBULL, 0x4530AC8E270936D0ULL, 0x9F9E2271E13FD451ULL, 0x0E9BE8EA6F6FD4C7ULL, 
            0xFDE42FC215C5F657ULL, 0xFA5EBD6574764C0BULL, 0x779C7CD484D51A49ULL, 0x6CB9DE8D846CD76DULL, 
            0x05019F88AB1AB9F8ULL, 0x335B2375DE874F01ULL, 0x285C88E36E315883ULL, 0x7CF9339F755FD351ULL, 
            0x990E2A2BDB266862ULL, 0x23AA6676B1077AFBULL, 0x522B16CD8706798CULL, 0x59CE255E2547128CULL, 
            0x735537A4FE20E40BULL, 0x1A07BB4B130820A9ULL, 0x6BB120BED06D32A6ULL, 0x1101D2E2AF35C00AULL, 
            0xEC2A559256AF8732ULL, 0x1836C7DEF20277BCULL, 0xBD3C3F87412ED37BULL, 0x2E1631E8E576FDD1ULL, 
            0x1EF4F19FB0B7BE5DULL, 0xA77AF499899BF98CULL, 0x1059C677662F502FULL, 0x3263F305E22E4527ULL
        }
    },
    {
        {
            0x5194EF7DEB27C335ULL, 0x09683FFD43A44CFBULL, 0x56C397EEAA3F62C4ULL, 0x8EB2D7174B098BFEULL, 
            0x5209D887B05FE083ULL, 0x83BD32E45ACDD037ULL, 0x4140FD653739EA31ULL, 0x06A6420D097EB939ULL, 
            0xE2DD722AC4D31FE3ULL, 0xFD8065BDBDDFEA2CULL, 0xFEE2180C894A3960ULL, 0x98272EC977761060ULL, 
            0x95C924C3E571D52FULL, 0xA8746B7B15FF5B6EULL, 0x9251AF6E5E8F5861ULL, 0x5830E44F8D4A0F89ULL, 
            0xEE5668F302DAA769ULL, 0xA8B012903C8C1B5AULL, 0x07C12FC236D749C9ULL, 0x7D26707E3EF5BB88ULL, 
            0xD64C87B4C11CC89DULL, 0x426C24F35CEAB0A6ULL, 0x726E4F45FD0A8468ULL, 0x02EA2413C0B930C4ULL, 
            0x2C2F917613D6CAB7ULL, 0xE4D304749E4353BDULL, 0xD7EADEC6AB93AF3BULL, 0xA0A19E997ED56C9CULL, 
            0x6F89C2465EF7E832ULL, 0xC05CE56EC3ED9D1CULL, 0x752F92F0A2075F52ULL, 0x760547528AE666CDULL
        },
        {
            0xD4B9F34B36DD0EBEULL, 0xC775ACAF56E81BFAULL, 0x38BB0D3374BBE754ULL, 0x0E8ABF63F1F2E494ULL, 
            0x5C212D361247BCA0ULL, 0x81E2C292615FE7FEULL, 0x577FD868286504DDULL, 0x6071DF3A7FFA52F4ULL, 
            0x6EEFBABB27C38400ULL, 0x6FB575B70C657F01ULL, 0x04474E672B19830DULL, 0x3FAA6C3104528B9AULL, 
            0x8EF491CC9518A018ULL, 0x0F361DD65997E6D2ULL, 0x75E6632912E5A595ULL, 0x05BD38D428323EADULL, 
            0x6AA5821D0976AAB5ULL, 0xD443F85E63FCA409ULL, 0x339EC9511C45955EULL, 0x15AD7E9804BB4167ULL, 
            0x684682F60437F7D9ULL, 0xCA2D0441945013AAULL, 0x1615213F8ACAE4ABULL, 0x9A18A48E893E3504ULL, 
            0xC857408D5DB7CC02ULL, 0x1F923E3401D1C0F9ULL, 0x9E6CBFD282B75803ULL, 0xBFEEE801277DC1DBULL, 
            0x54B188406F430096ULL, 0xF8F837B75C8A1E89ULL, 0x76A8B496ABD95827ULL, 0xA17F338001A2E88CULL
        },
        {
            0xD39CDD0AF7753268ULL, 0x967E721C2EB7769BULL, 0xE8E0EE56FB3A6A19ULL, 0x79CC6C9267D4E089ULL, 
            0x0A47A19E3D7A56BCULL, 0x2CD2C9E1F1FD02E6ULL, 0xF6F884DB8E48D264ULL, 0x0D721DCD9EAF9E8FULL, 
            0xC8FF95E9D13AF3CCULL, 0x270756C841F6A700ULL, 0xABA0FF763A7235D4ULL, 0xD2A920AE7A87D87EULL, 
            0xF2BD34123044087CULL, 0x7D990A337B928A42ULL, 0x7284548E4A9CAC86ULL, 0xC6B80D596E5162FFULL, 
            0xB3E5E4936B02CE7CULL, 0xB1AA792385144A32ULL, 0x81BA296C4C213AEAULL, 0x7303E098FA3ACCD7ULL, 
            0xACE2226BFFA3F81EULL, 0xD4270F893D935578ULL, 0x483D925B2CC1801EULL, 0x63230CC51AD1FD01ULL, 
            0x74025F85CA0D4880ULL, 0x972AA731D5090C19ULL, 0x1935F09EEC8C8CC2ULL, 0x9835E3D8711D05BEULL, 
            0x359B1A2180D8AA0AULL, 0xED9782E66EB5E9F0ULL, 0x921180D59FBF23EAULL, 0xE6E3F0125C932896ULL
        },
        {
            0x21D6685FE9282FBCULL, 0x8B2608A215646CC0ULL, 0x2585987DFA9B11EDULL, 0x231D991020BB74AEULL, 
            0x568102749B0DD0EFULL, 0xFEF243F5D41CE6B0ULL, 0xCA584AD950C216AAULL, 0xCBF1AAF660F82948ULL, 
            0x48FB0D425BB9CEE1ULL, 0x55E37B8C9A747F32ULL, 0x87B9F2AF817509A8ULL, 0xE22C33FE57FC2A8BULL, 
            0x6A13DF53CD32C618ULL, 0xFD74F6352F782EC7ULL, 0x6A2606527E56F767ULL, 0x52AA376AE192D45DULL, 
            0x4690F0E1D3C56D1FULL, 0x05032E21DAA5313AULL, 0x3C5B0FEE9BAF044BULL, 0x6013728EC242731AULL, 
            0xF82469CF643F4D80ULL, 0xFB47DC7D4A62AB70ULL, 0xEF0D4CD870BA62D3ULL, 0x50C949C9E4F12E24ULL, 
            0xA4B2C874E3FAECF0ULL, 0x0B0EA7E0E997594BULL, 0xF565E6CC3E72367FULL, 0xE50D04FF7A943EE6ULL, 
            0xD33CB96B69A8F504ULL, 0x3C76DFBAB57FEE75ULL, 0x7CA90752606E7E79ULL, 0x20804F9826A28A5FULL
        },
        {
            0x38A4474DB6198188ULL, 0x9BA8099A514D24CBULL, 0xDA525F30C8877CC2ULL, 0x4731C9C9015DB765ULL, 
            0x43D15881EE76D30AULL, 0xD13F40623E9F12AFULL, 0x14140B0EE4B4E8C4ULL, 0x2767EC2F9F2F4C70ULL, 
            0xE06B64E0E794A02AULL, 0xA101E39B9F3BDDB3ULL, 0x81EBB6BD051B716BULL, 0x6BCDDF8596FAC2B6ULL, 
            0x38C7CAC300A5A433ULL, 0x90B4764A7E12477FULL, 0xC05B69D3F545B32DULL, 0x3A217346C5AF15EFULL, 
            0xFF15B369F9ED89F4ULL, 0xDEDB902A9EABC1ACULL, 0xBFCF23BE0CD095C3ULL, 0x869E4D44CD3E08A1ULL, 
            0x01E7481145474E74ULL, 0xD5FFA6D58C2F728CULL, 0xD1C10D3311FF20D1ULL, 0xC322112A12D41FE2ULL, 
            0x7400597BE9E18A9CULL, 0xF89565CE8CD09DD6ULL, 0xD0B7B31752923AE1ULL, 0x63089C8D00D7B606ULL, 
            0x61C76BB17BC553A9ULL, 0xC636C64109E7EEB1ULL, 0x24FA191A744F3062ULL, 0x63F673A10BB1AB09ULL
        },
        {
            0xACB40ECAED9B6117ULL, 0x9ABF8C664FEF59B1ULL, 0x1691C4A423FC3035ULL, 0xD97CE8F873FBB3D5ULL, 
            0x20D370944E5A682DULL, 0x21442B5938DC5766ULL, 0x79253D6D7FAD9DAAULL, 0xEC08EAD742CB4AFBULL, 
            0x96EB2FC4E3D295E2ULL, 0x98A405E4D0B3B6B2ULL, 0x1FF3BC96FE667664ULL, 0xC4E2FA9E59C9E0AFULL, 
            0x1DF717138DBA4989ULL, 0xC2D59D5A95F04F58ULL, 0x5DA7F837B45624F5ULL, 0x1736978A80542F3CULL, 
            0x3A11E94143F160BAULL, 0x45557CF1A9B86B36ULL, 0x94BCA546D294C1D1ULL, 0x05F723DAD3EA7E6AULL, 
            0x17714A4E34045BC3ULL, 0x997333C6D4D3038AULL, 0xAA61B801A042E944ULL, 0x4EC9E70B07852B17ULL, 
            0xCAF46C2A1D6B1803ULL, 0x6B262448BE4D6844ULL, 0xB62A64342BC9EC9CULL, 0xC0F0C759A9013D40ULL, 
            0x375538AFAB322EF9ULL, 0x89E4D258439F838BULL, 0x86C74E59298684BCULL, 0xF73711FB0E3E2FE3ULL
        }
    },
    {
        {
            0x9F64E2E4701C8F15ULL, 0xF82B71A4C8B9446EULL, 0x67E040837417020BULL, 0x078BB98FDA5C7AB7ULL, 
            0xE4C2C1F46BE305CCULL, 0x1765F1AA4A6ED318ULL, 0x9359F60A2B47C884ULL, 0xB521A5CD16D0E740ULL, 
            0x9B9020C9414CD1E6ULL, 0xA7B353845585F2FFULL, 0x0977306971B09FE2ULL, 0x0861DAEB2C7BE429ULL, 
            0x198C3CBAD4CF615FULL, 0x148A262CB17A9528ULL, 0x61C5DE287B59F1BAULL, 0x5442704393151E83ULL, 
            0xBA36F4B5BF9B84C1ULL, 0xB0A18F35642BE191ULL, 0xDAAAB5734DA79287ULL, 0xD3EC125BE01092D9ULL, 
            0xA175ABF511E7DAE2ULL, 0x3266AD2EEEE2EE7DULL, 0x1C0867FA1C75C3E1ULL, 0x4BD7A60F1C3DE59DULL, 
            0x97E4DD22EB0B9ECBULL, 0x2C2A9DCC52FC3BA2ULL, 0x4841D39C0DD87A01ULL, 0xE98472F0D571E607ULL, 
            0xFA25406B3489354AULL, 0x155BF20FCAD0ED22ULL, 0x6CBBB02F43E15E67ULL, 0x89AF91E6290AB6DEULL
        },
        {
            0xDBEEC01E37DCEC1AULL, 0xD85CE82653300181ULL, 0x579D64C810FC5C86ULL, 0x81BC5068F39C1329ULL, 
            0xFCEE2645C948D924ULL, 0xC189AC14A79FA502ULL, 0x51949488CFDFC264ULL, 0x850D56BF8DD01E31ULL, 
            0x0AD621417F54953AULL, 0x07CC55622B99E935ULL, 0xF697376297D31D31ULL, 0x372B32DB1A3D8DB1ULL, 
            0x70E8C49683830393ULL, 0x2050ED76DFB27FD3ULL, 0x4E201D233C7F4F3DULL, 0xDA64EEB7010AC3B6ULL, 
            0x8447DE73DE83C2CEULL, 0x6CEB8681AB6F5B40ULL, 0x367398400EAE3A6CULL, 0xC432A1DA35593493ULL, 
            0xA5049F90BF11D2BAULL, 0x8739ED7D74F377D1ULL, 0xFFA98F49D7512C25ULL, 0xCD9B8586BD3D3C4BULL, 
            0x3508779316007310ULL, 0x7D94393700CBB747ULL, 0x962384AEC4BAFC05ULL, 0xBFABB748CB8F9370ULL, 
            0xF6AB6324A1642017ULL, 0xE39CCAE30D3D7A71ULL, 0x78F97F1DDA33119EULL, 0x02171D4D2DCD2F9AULL
        },
        {
            0x4B6E763D572CAAEFULL, 0x8E320088133C4CC4ULL, 0x07237A4BC65F818FULL, 0xF0DE0E103F6FFC20ULL, 
            0x7BE15FBEB7402DB4ULL, 0x21E3643BE3E50D54ULL, 0x4F042B433C8A42A2ULL, 0xA40C949E98DFD446ULL, 
            0x7FC7C2D67D06AAB6ULL, 0x0B7855EC473D4D3DULL, 0x584418B46669FA54ULL, 0xC32C5D42E9818057ULL, 
            0x7351768C21AC0278ULL, 0x173B6FBE26E7C4B2ULL, 0xA61122AB85021D09ULL, 0x90FBBC4DFDEE0971ULL, 
            0x886EEDA01925D222ULL, 0xD8F5AA948C5F505EULL, 0x9B17A657D9DA2346ULL, 0x6F8F5AA103F1D1ABULL, 
            0x84005EF799E2F9C2ULL, 0x0E04C3A883FB42A9ULL, 0x03D802DE1E576BF0ULL, 0x9248BBAD2BC5DEF2ULL, 
            0xC60A885D744335A6ULL, 0xC19697DDDC279780ULL, 0xE1BCE467B57AB93DULL, 0x2409285D67FAC2F5ULL, 
            0x20FAA4C645667333ULL, 0xE256993A687224BBULL, 0x13F7FAE0A0AB6C98ULL, 0x4CDB329D84BCD749ULL
        },
        {
            0x828C9D14C2333348ULL, 0x0088AAC51293C7DBULL, 0x6F28D8734A68CF2CULL, 0xA50CB8D82CB3A9F1ULL, 
            0x8B2B2F2903AF8913ULL, 0x3F80B49026AA8414ULL, 0x492FAC80C881202FULL, 0x951195967A642687ULL, 
            0xB9B2E90E7FA46319ULL, 0xCB19A86D9129177AULL, 0x848F192F748DFB3BULL, 0xD13C5663B327F58EULL, 
            0xD57562D1C2431B5AULL, 0xD03848789410A545ULL, 0xE30EF0E32C99786AULL, 0xD62D0DE635BE71A6ULL, 
            0x1CF3CCB6EA717A3BULL, 0x5308319B4DED5C15ULL, 0xBA0B0FABA8315156ULL, 0x94ECBF6BB1F20EBFULL, 
            0x258F19A14EBB7A31ULL, 0x3086EB81D0EADE8CULL, 0x95B747B15F44720CULL, 0x594C07C039079F36ULL, 
            0x6ECECFB84AE2BAA0ULL, 0x5637A2D51899AB7FULL, 0x731A72A507464246ULL, 0xB57414A58F44FF51ULL, 
            0x6267B9DEDCC560CAULL, 0xC4BCDA437563E37FULL, 0x8907004F31348AE7ULL, 0xF752A2C9E8878558ULL
        },
        {
            0x42A13FDD1DED0026ULL, 0xAD76E6917E80F369ULL, 0x4F9DFAC53C1007C2ULL, 0x59354CA5C61070C2ULL, 
            0xD9F2D8EFEE90A689ULL, 0x048FE005D2FA9E1DULL, 0xDCE45637F1A61D91ULL, 0xBD7CBD94EAA0A77BULL, 
            0xEF87A3E3995E4D9DULL, 0x206E514FDB1D0CCEULL, 0xBCB281423735D25AULL, 0x1E53F6C95FABC728ULL, 
            0x174991917E57A692ULL, 0x557E7420738BAB5BULL, 0x8E728C593ADE45C8ULL, 0xC892DDB05873DCB7ULL, 
            0xC5813D0F4A21C077ULL, 0xA2FC397777624B7AULL, 0x20FCEBAAF49ACBEDULL, 0xF39E7C0AB5DB7BDCULL, 
            0xD3AF775E8E2C869CULL, 0xB1351685030A7962ULL, 0xCCB1C6CC6667A1EBULL, 0xB38A8418BE93C320ULL, 
            0xC466924E840BC5ABULL, 0x5C30FE3641619859ULL, 0xDBBD93F155543B43ULL, 0xB31FA3336248EB4FULL, 
            0xBBF43A53E624DFB7ULL, 0x09A1C8380ED3EA93ULL, 0x8A29B7EC1024ABBEULL, 0x1D1CA59677A373FCULL
        },
        {
            0x9BDDEFE5C6ADE035ULL, 0x7BEFF1FFB724626FULL, 0x56BC3BE7B1063944ULL, 0x17E76DDEB90F7E4AULL, 
            0x428F3962EECD15C0ULL, 0x2A92A431F90BEBB9ULL, 0xEE7C01A032E2A595ULL, 0x0F332BA99CD5168AULL, 
            0x3C25320F405B7595ULL, 0xB2407DF8CB63C201ULL, 0x404946FF3277C414ULL, 0xC7F6DB0A029DD5D6ULL, 
            0x38C207374AC65E65ULL, 0xCB2E3E61F1B0D977ULL, 0xCE22006FD32B6C85ULL, 0x5C0FE96967F8C35CULL, 
            0xC5CC704FDF087B60ULL, 0xD12EFD9437F7457CULL, 0x4945546FA4AA38CCULL, 0x78F2BA18C32249B3ULL, 
            0x7D2C2A58C0ECD5BDULL, 0xF132B3EEAE214E17ULL, 0xC7EA4AFA23AB901FULL, 0x439BFDCA1A9156CFULL, 
            0x503DE1A764429C4AULL, 0x48EF0E84114CD8DCULL, 0xEDDFCFB460E03E7EULL, 0x2173623E53F6A0AFULL, 
            0xCCBB809C577459F9ULL, 0x2B1A4839CEF78358ULL, 0x779F62E0DD1A8133ULL, 0xE2805102AA7C8987ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseGConstants = {
    0x3FC4D98603EFEE70ULL,
    0x19AB5879990560BDULL,
    0x8044A14C5E595B93ULL,
    0x3FC4D98603EFEE70ULL,
    0x19AB5879990560BDULL,
    0x8044A14C5E595B93ULL,
    0xFFF61A86EFA7ECC8ULL,
    0x789C8106AAC57F2AULL,
    0xCB,
    0x51,
    0x62,
    0xA3,
    0xF0,
    0xCC,
    0x7E,
    0x5B
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseHSalts = {
    {
        {
            0x742178EF8643A407ULL, 0xA3E12B321EA5A548ULL, 0x6167D1640C744262ULL, 0xE4FD3A9FCFB667A9ULL, 
            0xF3EC59F55BEE2285ULL, 0xC6AE8A9894E420A6ULL, 0xF592C655DC576510ULL, 0x253A9EB2271DC1CDULL, 
            0x7CBE72337501E690ULL, 0x00AD63924CAB908DULL, 0xAEB055D402B15C1DULL, 0x793E706B709F1A65ULL, 
            0x8F6422965426E6AAULL, 0x6A7A5138D561EF55ULL, 0x82E540DBC724DD00ULL, 0xBAD7FC918D709B7BULL, 
            0x131E24190B1ACCFAULL, 0x83D671A6399609FCULL, 0xBCCF160C682CC001ULL, 0xFD3A671CDC3A80F3ULL, 
            0xAAAD5DD4AA0ADBB6ULL, 0x747EAFF86C41F567ULL, 0xA4BD7880D7674225ULL, 0xB4E10C9ECEA650CFULL, 
            0x3E8E771AB8BAB051ULL, 0x246FF71E70B7DEDCULL, 0x1BFECBB07C35B830ULL, 0xD08C0E6E29CB11DCULL, 
            0x41AFD6E80C5AEDC7ULL, 0xAB881BCA108611C7ULL, 0x91D1F0A3D6F4BCA6ULL, 0x7507135A0B46FA8CULL
        },
        {
            0x3C00BF95156D6267ULL, 0x805ADA87D67B52AAULL, 0x55F9A3AED192184DULL, 0xA86235EAABDB37B8ULL, 
            0xB09C4206E18B7DFDULL, 0x981587A418699B30ULL, 0x037347483EBEA771ULL, 0xB82A8DC4B6EF2102ULL, 
            0x048CB7D577AD5A8BULL, 0x406CCB3D2AFA12FEULL, 0x73D6231F14CB1E98ULL, 0xA71877F188A7ABB8ULL, 
            0x2D733160820873AEULL, 0x07DE4A1849F265FBULL, 0x9AE7BF3A8C1A340BULL, 0x863ECA4B294D4035ULL, 
            0x35FD3EACB1AF2024ULL, 0xB17B27E9E1815000ULL, 0x592D697744B32643ULL, 0xAABFDA63E331A6DCULL, 
            0x783D8D55DB28E606ULL, 0xA3E3F5C8820B3095ULL, 0x90F3E7C112B2F336ULL, 0xB4B436734C185F8DULL, 
            0xCF69137C50766A85ULL, 0xB47DE4C04F4BA4DDULL, 0x8645272BB58F3318ULL, 0xE47C82F2AD1E234BULL, 
            0xCCA8EA28B9E5DB5FULL, 0x6615519318788CB2ULL, 0xD539AE241928393AULL, 0x8018B34F42498AECULL
        },
        {
            0x9DBC27C2246AFADAULL, 0xF3150A63C26B35C7ULL, 0x7DDDA01296B11A51ULL, 0x6B4DF1C82A643AC4ULL, 
            0x339302B9C92D3759ULL, 0x3761AE0C8B655032ULL, 0x69F831E690405DE3ULL, 0x5DD87951980A888AULL, 
            0x21EF3BAD1590400FULL, 0xC974FCCBE74F4B7AULL, 0xBB815430A7E81BD3ULL, 0x1C5770B72EEA01F0ULL, 
            0xE5C9E4C9D218A2B5ULL, 0xCD5368109A4AD409ULL, 0x338877EAE1817099ULL, 0xED66731DF490E455ULL, 
            0x3090954AB8B8E636ULL, 0x877F1E504B7D93BDULL, 0x6B26102783B9D93BULL, 0xEA533EC8594F10AAULL, 
            0x053AA5DF91A46783ULL, 0x5BE68597105A8883ULL, 0x3B556E88D0552B5FULL, 0xC4B233A12D52A42AULL, 
            0x723FBF473F2EEF81ULL, 0x78B5C225286C52CEULL, 0x057AAEA71F3E6B49ULL, 0x8AA8132B64423411ULL, 
            0x2DA31E2377C73328ULL, 0x002406165ABD3C56ULL, 0x6ACDE4B5C9CF8649ULL, 0xAD03CAB10A40F936ULL
        },
        {
            0x44E9C306C144FF8DULL, 0x5FD20ABB64BC73B4ULL, 0x927EB0403E4558D4ULL, 0x6F9FFEAD4B5246ABULL, 
            0x18B13E7AF80CB75BULL, 0x8B18419C7EE00CD9ULL, 0x02DBF846972A4883ULL, 0x5C0833D93192B15AULL, 
            0xB3383F8DC7CB0A74ULL, 0xE80E080F11E307AFULL, 0xA7AE17CD5B4FE8BFULL, 0x3C93B30B89258203ULL, 
            0x1B9EFC973B65A326ULL, 0xAD122E83DA3DDDF5ULL, 0x2BF160D327086BEEULL, 0xA12D48578FEBC480ULL, 
            0x38C57C20F2B7C1D5ULL, 0x0CF8B30A2F9F2753ULL, 0xF03535555268E8FFULL, 0x8019056AFF5B0C7FULL, 
            0x16B6745791A3B50CULL, 0xCDC588E5DF10AEBFULL, 0xEE374F4160C84681ULL, 0xAD082C48FAEB8703ULL, 
            0x042D222F8F23F640ULL, 0xD0DAEFEEF18731FFULL, 0xE6FCA5E46A78F1E0ULL, 0x74E47F09C07DDAE8ULL, 
            0x56783EC029447BEAULL, 0x9ABF9A3D6882EB0BULL, 0xA47EF1AA3B17F051ULL, 0xDC0BEA6289A19CD6ULL
        },
        {
            0xD1F2D8E733D01FCEULL, 0xB73F5D3E61778B4EULL, 0x72E5C07411CE0358ULL, 0xA9D84BDA1B4BA813ULL, 
            0x02D45D33C5B1D2EBULL, 0xFFEE7ABFBB555B5AULL, 0x53A7B36C72B38887ULL, 0xF3F9493B5F922370ULL, 
            0xD821CE1ABF9E4D2DULL, 0xB7775501B9E79DAEULL, 0x9AED2695EBB1EB56ULL, 0x41129E345CC1E504ULL, 
            0xCA1AD336A7B672C8ULL, 0xB5CFC486D4AED785ULL, 0x5B9E39DAB87E8063ULL, 0x0340A05C084D61B7ULL, 
            0x82B0CA02E6910D6DULL, 0xB4FF97DF2D14DD2AULL, 0xA04C0958381CFE70ULL, 0xAABE4B8DCED630ADULL, 
            0x75B29A50A8491792ULL, 0x090A3801DE3CE44BULL, 0x4BD977D2966A4B7EULL, 0x06F505960D3F9713ULL, 
            0x54244965CA904C33ULL, 0x78C1F4A1D2FDC0CFULL, 0x1496E88AA1A32398ULL, 0x0970099E6AF20B94ULL, 
            0x849F8ECB8CE14069ULL, 0x1792948DCBC64BCBULL, 0x59E0D3F8110EFE17ULL, 0x161E03430423C951ULL
        },
        {
            0x716C969CE8352260ULL, 0xA596246A599C2355ULL, 0x6EE88BEA956B4728ULL, 0x5A74C2D2C3A33C7FULL, 
            0xDAFDE862792EC77DULL, 0xD228773C553E02E0ULL, 0x9FB68BAD58DD4BC0ULL, 0x715835DD4F0453A6ULL, 
            0x2B158AAB81BFB10BULL, 0x067B9AE8FDC2AF53ULL, 0xD3C1DF9B11EFD6DDULL, 0x38C6905C5D7CA6BAULL, 
            0xAB748A3286D44662ULL, 0xA7042C221B720FB1ULL, 0xAC7B29F01EF89419ULL, 0x927AD0E8F6BD1AF1ULL, 
            0x9F8DD634EF65036DULL, 0xBC385990FB91D39EULL, 0x0F9FFA709637F097ULL, 0x3292F7AE18F4FD64ULL, 
            0xD0DC2B93E9C89113ULL, 0x1E719420B514ED3FULL, 0xDAC5BD3827BC9714ULL, 0x995E1C661D0306BDULL, 
            0x0B4301ACC39CCAFFULL, 0xFDB5AE55ECB08CFFULL, 0x0FB47289B965DC9BULL, 0xC4E2A262EE46693AULL, 
            0x34C57D00E5BA801EULL, 0x26EEB8146CB6DFC4ULL, 0x11B22312298E965EULL, 0x0DE228F6BDE358F1ULL
        }
    },
    {
        {
            0x6E4098E08BADB5AFULL, 0xA1A57EEF5E0E357AULL, 0x1340D3B962F127DAULL, 0x17693F74F3D1500BULL, 
            0x520334DE0FDA9A25ULL, 0xD7DD9B8B33AA6EC9ULL, 0x44A30ADC3DAD4677ULL, 0xCA4602AA60202F91ULL, 
            0x28E0426CD5507D85ULL, 0x3DD71B27A0CDD54AULL, 0x3C7AC42F81745F1AULL, 0x265F49024B7BFB48ULL, 
            0x7BC9F3AE5EC6B3DEULL, 0x93246B59FC508334ULL, 0x88E0414CC644CC6CULL, 0xA4EEB5440EFE9363ULL, 
            0x0F4DFAABC7B46B11ULL, 0xBE5A415EBAB952E9ULL, 0xBE378475400289B6ULL, 0xA06E6C21E73FF25AULL, 
            0x8B7DBB1826E4D36FULL, 0x7B15CE41044A87DCULL, 0x4E58BD1F2742D34FULL, 0xDDFB06B1173B3F2BULL, 
            0xDDB2CEF80C22B465ULL, 0xE36543B56829025BULL, 0x3B82F0FE57EB3152ULL, 0xC5A64B412C413642ULL, 
            0xCCE0CD8F6860187EULL, 0xAD9BAC98AD96DE77ULL, 0xF2C7C5BC0B3E7584ULL, 0xB3FA003FE1959EF3ULL
        },
        {
            0x101D600BA6A5944CULL, 0x96AAEA663AB3B11DULL, 0xB5A46900BEC2346BULL, 0x7C4B02926536FE7DULL, 
            0x2B22C8F38C507004ULL, 0x75503A50CF2EF6E0ULL, 0xCD02F47E54C516F8ULL, 0x50F8116C014C957EULL, 
            0x83D0609599987449ULL, 0x3E9D8FF6541004EAULL, 0xBE0F433DD7B6048EULL, 0xA9CDCF7254DB3A16ULL, 
            0x5364048B85975F80ULL, 0xF3503F081C659828ULL, 0x8B62796A2E9A8B0EULL, 0xB32BCE1761C308CAULL, 
            0x28A5331ED044F2BFULL, 0x2F15BCA0CDCB9007ULL, 0xD7F6F5716CA94652ULL, 0x1DEF374D3809141DULL, 
            0x561415743B964C30ULL, 0x169486465BBA3CEEULL, 0xC8B29BED30C91CE6ULL, 0x1E22FFBCAD39D7CBULL, 
            0xF538022F8DD7EF92ULL, 0x7107842750ECD81FULL, 0xFB23302E5887074BULL, 0x1C1503AEE2CD38D7ULL, 
            0x3E5297C70601DDB5ULL, 0x4F35AD5D4FC7E2A2ULL, 0x06ACEE3BD4E065EAULL, 0xF792B8F02EC7CB83ULL
        },
        {
            0x44B40ADED78760CCULL, 0xE21CB38C9D13F6BAULL, 0x579D0001DED86B72ULL, 0xA82AA13759BB5A0FULL, 
            0x099B7BA828CF4B4AULL, 0x87519D6854CD55ACULL, 0xD6D46A20F71D0909ULL, 0x755A7EEC7D5B6840ULL, 
            0x138494D95891F990ULL, 0x0B381B2F45FDBB37ULL, 0x21C1AB4DD3878D9DULL, 0x8554131437E32BE4ULL, 
            0xAFE715EDE4DD6F40ULL, 0x25C10798CE77DCA9ULL, 0x80C00C234A7A6829ULL, 0x8FE49D37F231F214ULL, 
            0x688F2CE681B1DAA2ULL, 0xE72573D7AAEB134DULL, 0x84B2835F80DD232EULL, 0x76066A49218EFA34ULL, 
            0x2C5BA273954DE1E7ULL, 0x09B7BA3F7F8A5DA7ULL, 0x2E429E9C6AEF164BULL, 0x5167A933D47AFA3DULL, 
            0x1FBBBBD5E3986B89ULL, 0x72EA004C7B286730ULL, 0xBFAEC67BA70F5F4CULL, 0xC4A8BC54513128B4ULL, 
            0x845818388FE545C2ULL, 0xD563F95D131BF2DEULL, 0xD1D091FC18E08B0CULL, 0x664D3126AE4212CBULL
        },
        {
            0xFEAE95A9943102FEULL, 0x1D5FF26B8B22C332ULL, 0x4D7309FFDADAA01AULL, 0x4821F26B9403BCB5ULL, 
            0xE589D1FBB5091D02ULL, 0xD57A54448A95385DULL, 0xD6B85DD3505F72A9ULL, 0x68EBFBA54B638649ULL, 
            0x77EAE490689C0CC0ULL, 0xB64DEFE40FEFFEBEULL, 0x263598BA95F44D21ULL, 0x6D35F82311950B5FULL, 
            0xEDC1C0F477C5B381ULL, 0xDFB13B7A8DEC661FULL, 0xDD2E066B23FF62B0ULL, 0x6B0A89414B78D38CULL, 
            0xBA0CADCD05F1CF62ULL, 0x5C46635ECEFA0683ULL, 0xAB8629B98CD92306ULL, 0xB49FC2148361FDF6ULL, 
            0x6B2D4237DD9ED1DFULL, 0xF18114D3FEA1994CULL, 0x88E4F95277772CD7ULL, 0xD190D0ACA788EF44ULL, 
            0x6DDC7D22526C45D2ULL, 0xA6901C4C448AF9F9ULL, 0x3DC5BD1DF42D2056ULL, 0x24A605F3BA725577ULL, 
            0xB810CBC13C944B82ULL, 0xF29CE21976B2F431ULL, 0x3138B3BB931250EEULL, 0xB0F2C8661594E70CULL
        },
        {
            0xBA0FCA12D433DBA6ULL, 0xE97AC9ABB6E9F0FAULL, 0xAE9EF569FA970E32ULL, 0x15A7EA4A28743C37ULL, 
            0xB90D5189D8C8620BULL, 0x987B321D5D68A3B1ULL, 0xF86C2AB0DB1A6EC0ULL, 0x7D7E98EE30CFAF5FULL, 
            0xE1FB8F560E157F03ULL, 0x11790490B0D153AAULL, 0x0019633F4F4FD12AULL, 0xED4F44A8895A9FC5ULL, 
            0x1341EC45648797FEULL, 0x2A0B4BB72D51BA05ULL, 0xC050610870B0E227ULL, 0x9CA26E078E311BDBULL, 
            0x05446B3A34DC2050ULL, 0x3BFCE3169288E5C4ULL, 0xCB7823CFBE6F8D37ULL, 0x75727A090CA91032ULL, 
            0xDDB2CBD22E452F85ULL, 0xF1C5602B087BAC27ULL, 0x94E8D99411CAF830ULL, 0x558A12B29830FA34ULL, 
            0x218C24656D25F157ULL, 0x3D16DB599E5F6C66ULL, 0xFFCF52FCEF6935B9ULL, 0x5019E354223BA821ULL, 
            0xE2161B5C010558D0ULL, 0xEE103A81C9169094ULL, 0x03E5DACB2B413A1FULL, 0x7A99AE1F115BF58AULL
        },
        {
            0x67A29907D450CF77ULL, 0xB50FF6927A1C1B61ULL, 0x31807BA905415F9BULL, 0x597F3719E5AF799CULL, 
            0x4A5150B5A0605507ULL, 0x3FFF1357F4A001E3ULL, 0xEAAB692BF1AAA421ULL, 0x077901577E166AD1ULL, 
            0xAD1145D59A705CB6ULL, 0xA88D3203083AC314ULL, 0x35DEDDCE25013639ULL, 0xDE93C02E86D78B33ULL, 
            0x009F4A1E3BE4FF0DULL, 0x2825A48E06C00C95ULL, 0xFE97454035E8AC8FULL, 0x7DD914D3B1D13343ULL, 
            0xAEF3D6CD444ADF83ULL, 0x69FE250ED74D7822ULL, 0x2C036BE8B560E636ULL, 0xE2097A76E7A99BC1ULL, 
            0x34BCA6F1FCCA167EULL, 0xB432AAEC89928431ULL, 0x0F918183EF4CF3CBULL, 0x7A23AFAD790B98DFULL, 
            0x394BE6150B36620BULL, 0x8059E216A8D6936FULL, 0xB9D1B078C3A68094ULL, 0xA6FA8E023D1CE090ULL, 
            0xB1DCFAA98B7D8C79ULL, 0x716E3A44FE6E1040ULL, 0x4D62C07D0C4A760CULL, 0x1E7AD17719B5D1C0ULL
        }
    },
    {
        {
            0xA690BFBC77C807BFULL, 0x8D33A843BED4FCFCULL, 0xF1562D7F6BE25977ULL, 0xC9EAB576EC35A901ULL, 
            0x7E51781EA1AF5ED2ULL, 0xBBD1730A998C7D7EULL, 0x39D4C4518D951320ULL, 0x913E98C5112C92D9ULL, 
            0xBB9B7747FC0FB666ULL, 0x99CB8D2ED3BD046FULL, 0xA94CF4886EA91DA9ULL, 0x6299CF4E6BE1F4DDULL, 
            0x677614D19B84029CULL, 0xF9FA3E5C5588D5E6ULL, 0x7A92C14A37A053DCULL, 0x55E84CA6EFDD14AAULL, 
            0x75203663813AA06FULL, 0xFF55BC9882B63926ULL, 0xFB906DA630CAD0BDULL, 0x03E09D57BDB4D482ULL, 
            0x43B47B84A5B6E909ULL, 0x1EF1C7F4C7BAE6A4ULL, 0x2A64C1A7F81AA0E5ULL, 0x348F286CABA1242AULL, 
            0xE45586AD03B93CAAULL, 0xB775C8D3C6C4E29EULL, 0x73D6612B660C52FAULL, 0xF80047AF4A790ED2ULL, 
            0x367ABBC71D225D31ULL, 0x11A7E7B648632D3BULL, 0x16E22D4E51BE99F5ULL, 0x0F2D72C4EAF4B84FULL
        },
        {
            0xCF6F6829C49D1E2DULL, 0xFE0E6DC08DB65D2DULL, 0x7E76EA9E941E4AF9ULL, 0xFA62AEBF9020E97BULL, 
            0x75DEFE744CB2ACEAULL, 0x66ADC1A3B64B12DBULL, 0x6122891F229FE33AULL, 0xC54A970EB7B4A35DULL, 
            0x1E5C27791BE996E3ULL, 0x712800AC142FBE94ULL, 0x093699563F6A3F75ULL, 0x9A55F72D2148513AULL, 
            0x12CBD17394E69494ULL, 0x797F8433FE85DC9AULL, 0x4D83E7F370A44D4CULL, 0x3E7D22AA608C6479ULL, 
            0x1B6AC88D4E7C2E8CULL, 0x14022D3567A4BACFULL, 0xECC329A9B7C47337ULL, 0x1FFDB5AFD59F3455ULL, 
            0x35170AF5BDDA1C0DULL, 0x2BFD6845158A01B9ULL, 0x8E0502498897E2D9ULL, 0xC58E238654103F0FULL, 
            0x7BE2A7E5012F5824ULL, 0x1BDAEDA2C4636134ULL, 0x909BABC324A40D4DULL, 0x4628D94594970B8DULL, 
            0x9F43762F4A723DBAULL, 0xB9A41CEFD3651036ULL, 0xE279AE44EC6DE87DULL, 0x7585641D1B0B08B4ULL
        },
        {
            0x1C307AD3825535F5ULL, 0x37C5D20A0826550CULL, 0xE8EFDEA151DF855AULL, 0xFB405DCFE68C333DULL, 
            0x55C75B7EB2BCCB19ULL, 0xA82A9BEFA437CC3FULL, 0xE67273908A373760ULL, 0x7CA6691BC67B5425ULL, 
            0x31F537BAD8A243A0ULL, 0x207037A0E27C20DAULL, 0xDC14D8E21ABC1AB8ULL, 0x07CC198E01457055ULL, 
            0x6FE170CAE460BC32ULL, 0xB38FF0C9C0E6BD9FULL, 0x24FF9138A1B803B0ULL, 0x3F1C2AAEBE71658BULL, 
            0xF42C5B7DF4121B10ULL, 0x41C5788AA67DBA4AULL, 0xB5A91E48DE3AB307ULL, 0x88374213604E3A8FULL, 
            0xEFA8757A72CFA73EULL, 0xCB4189BAD3E1A8BDULL, 0x6E8F3114F09E9B79ULL, 0xBCB7F20027021238ULL, 
            0x06CBDE8B8AF106C3ULL, 0x5A06C3E2D6C8EB57ULL, 0xE3C520ED45AC4872ULL, 0xE031D9E58D740A6DULL, 
            0x8868E73BA0B42B99ULL, 0x57954F9FB46BC947ULL, 0x1B25BB76283F9111ULL, 0xEB26A8E3FDB3CA91ULL
        },
        {
            0x5220B06CC653860FULL, 0xCF87D41B62A2652FULL, 0xD3288C482A81F48BULL, 0xC1596A13ED12F396ULL, 
            0x22DAD0FAECFEBAEFULL, 0x6AC0BB7639C5ACF3ULL, 0xFCC8100FABD9C72DULL, 0x27FE234CB848A665ULL, 
            0x1C0D34344DCBF7D4ULL, 0x8FAAF910F7353582ULL, 0x75052618FB407AF2ULL, 0x74C318A712943D7AULL, 
            0x05A068BC4C9FD8A2ULL, 0xB72BD9B3AC60E2D6ULL, 0x5CE39FBD5DA02F1CULL, 0x64F8AE3ACAD980F2ULL, 
            0xFD2EE092F7DE3E40ULL, 0x05AE19EDF84A77FBULL, 0xAFE669A1A64000D6ULL, 0x9E316F558E0FC462ULL, 
            0xE7F41BBE7B1042D3ULL, 0x377D7012D3AE0586ULL, 0x0D9DA44739C820AAULL, 0x84BB3A6C6F5D329AULL, 
            0x106C3652D57A9039ULL, 0xF8D28BF1DDB94A5CULL, 0x5D6602B5490C2348ULL, 0xF9086BEB21998386ULL, 
            0xCC9D7B40A8BA2728ULL, 0xA377C8ED3081772FULL, 0x8C95C6BE0EE3C640ULL, 0x19A569570ACEF7F3ULL
        },
        {
            0x027A62F42C19319CULL, 0x9D3E61BA76B14FD3ULL, 0x5319A79F6AC6DC1BULL, 0xE8F448CC6AD66142ULL, 
            0x1A9D0D96C91A86B9ULL, 0x541986555381B779ULL, 0x125AA31F75D53F3CULL, 0x97F641D6082B7CE3ULL, 
            0x4A6A61FD87E1BD8FULL, 0x8B4FB90B092DEC8DULL, 0x9208621EF8AB0631ULL, 0x940C22D908D8ABACULL, 
            0x205D71475536C504ULL, 0x3C027028272B1FC0ULL, 0x8C2E03A156A35C28ULL, 0xF9F4D02E51E24363ULL, 
            0x3A14B5675AE94DC8ULL, 0xB1A565C78221D792ULL, 0xEB0E789BBBE1D707ULL, 0x933857885481AC0DULL, 
            0x2402D9BAECF6B349ULL, 0x2D863E8C07405D18ULL, 0xE4918F71CEB51545ULL, 0x5D48E3F81E819272ULL, 
            0x63A7E7ADBB5BAAF1ULL, 0x6D700202CC0E22E1ULL, 0x4C8C9B11E413D25AULL, 0x69D8985733886D49ULL, 
            0xA2A1C6FF430B42B8ULL, 0xBCBB452191AD6BC9ULL, 0xE597BEB66B9ADBD0ULL, 0xFF42489002498E27ULL
        },
        {
            0x80FC2F59BD2AC056ULL, 0x7625F49B304F00FCULL, 0x9F552D058D07EAE0ULL, 0xA31ABE6234CC1196ULL, 
            0x9C685AB553064B74ULL, 0x26E1DE08DC362423ULL, 0xA3EAB1F05AEF5761ULL, 0x6B9BBC180B675E62ULL, 
            0xF28753A1FFE2345EULL, 0xCCE72A6FC53BB7BFULL, 0x64CC41C8FF9BFB52ULL, 0xB587B3926FC9F99AULL, 
            0xACCBABA0B9C5513FULL, 0xDE1581C95BB1D8EAULL, 0x5F744D81143F5F1EULL, 0xB12406074D9420F6ULL, 
            0x74FD8BA60D2CBDFDULL, 0xAD5F1A0F237700A6ULL, 0xD0ED035DB475D540ULL, 0xF0495DF20E5ECDE0ULL, 
            0x5EF47FDBC83BF193ULL, 0x3743CC23E7616AE8ULL, 0x98DFEA7B0D9AE94CULL, 0xF81755A4CE09E89CULL, 
            0x998705FF02FF225AULL, 0x001F2A110E651CDAULL, 0x442F9C79FB9BC034ULL, 0x8A7CB001497153E7ULL, 
            0x7066C5C6883C263CULL, 0x72CDADDCAB62C8C9ULL, 0x17160A0F503B3621ULL, 0xDED757DFDE1B88F5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseHConstants = {
    0x8178FB4BFBAB54D4ULL,
    0x6E09430196A6EA3BULL,
    0x55058FEBA19E2FCDULL,
    0x8178FB4BFBAB54D4ULL,
    0x6E09430196A6EA3BULL,
    0x55058FEBA19E2FCDULL,
    0x2C4FE67E77F026ABULL,
    0x4502594FC73A5F24ULL,
    0xDB,
    0x39,
    0xDD,
    0x5C,
    0x93,
    0xAF,
    0x4D,
    0x89
};

