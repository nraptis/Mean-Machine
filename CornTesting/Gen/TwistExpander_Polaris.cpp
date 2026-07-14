#include "TwistExpander_Polaris.hpp"
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

TwistExpander_Polaris::TwistExpander_Polaris()
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

void TwistExpander_Polaris::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xDA7CB4E840103866ULL; std::uint64_t aIngress = 0x97D2F9AF8915627BULL; std::uint64_t aCarry = 0xE0EC94ED19F12D1AULL;

    std::uint64_t aWandererA = 0xE593099C38C30A30ULL; std::uint64_t aWandererB = 0xAA9FE6ACF09330E4ULL; std::uint64_t aWandererC = 0xBE6E20171BC67B36ULL; std::uint64_t aWandererD = 0xE050299E660E309CULL;
    std::uint64_t aWandererE = 0x8E31D0BA7C8637E5ULL; std::uint64_t aWandererF = 0xF0389D4E79F269ABULL; std::uint64_t aWandererG = 0x8B74273D41B6D523ULL; std::uint64_t aWandererH = 0x9666B2F5B9E84A4BULL;
    std::uint64_t aWandererI = 0xF4031578FEE3A9DBULL; std::uint64_t aWandererJ = 0xB1B48F919DFAFB02ULL; std::uint64_t aWandererK = 0xDE2CB09BD9A2F947ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15860260677637588009U;
        aCarry = 11730049280699970110U;
        aWandererA = 12144477116111208252U;
        aWandererB = 12204218615630162992U;
        aWandererC = 12024566318182279899U;
        aWandererD = 13762065000299891429U;
        aWandererE = 10702214603438030739U;
        aWandererF = 13906446251578876758U;
        aWandererG = 15536085049974421507U;
        aWandererH = 16738670446658760014U;
        aWandererI = 16522983172751388833U;
        aWandererJ = 17444555889328117045U;
        aWandererK = 18081166340947294382U;
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
    TwistExpander_Polaris_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Polaris_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Polaris_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Polaris_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Polaris_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Polaris::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB30E6E19A6147C74ULL; std::uint64_t aIngress = 0x8BE4F49BE1B061D9ULL; std::uint64_t aCarry = 0xEF45A2C810C2B493ULL;

    std::uint64_t aWandererA = 0xAC5718AB759DE2BDULL; std::uint64_t aWandererB = 0xA7FE84B1BAB3F55EULL; std::uint64_t aWandererC = 0x9722FFC1EB6D2354ULL; std::uint64_t aWandererD = 0xC8462F7E8EE61233ULL;
    std::uint64_t aWandererE = 0xA3D05DB0C2CD7CBCULL; std::uint64_t aWandererF = 0xD5811171D5B74EFAULL; std::uint64_t aWandererG = 0x86855C238D29B830ULL; std::uint64_t aWandererH = 0xE4E63E9B1C7C3453ULL;
    std::uint64_t aWandererI = 0x9A1FCA7F7EB6EF63ULL; std::uint64_t aWandererJ = 0xC57B1BF642973049ULL; std::uint64_t aWandererK = 0xD88679B7F207E637ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16250834202396677586U;
        aCarry = 15209519839235722588U;
        aWandererA = 14171205333461919122U;
        aWandererB = 12245907702381693708U;
        aWandererC = 14705154197087898613U;
        aWandererD = 9785723122915165370U;
        aWandererE = 14895445918140460273U;
        aWandererF = 18375129737830438266U;
        aWandererG = 11338152397656209702U;
        aWandererH = 12147811544677291889U;
        aWandererI = 17076406504422465538U;
        aWandererJ = 13686291486465709697U;
        aWandererK = 14692021740267283444U;
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
    TwistExpander_Polaris_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Polaris_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Polaris_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Polaris_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Polaris::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xD27DF9A48B0150EFULL;
    std::uint64_t aIngress = 0xF444BC56075B5062ULL;
    std::uint64_t aCarry = 0xBE5228DB01393CA1ULL;

    std::uint64_t aWandererA = 0x88C3F7D4009CDB5BULL;
    std::uint64_t aWandererB = 0xD353868594A6C9CBULL;
    std::uint64_t aWandererC = 0xBC9E81CD6B642482ULL;
    std::uint64_t aWandererD = 0xDFA88D7D7A36FCFEULL;
    std::uint64_t aWandererE = 0xC5793A3AD4BA6E44ULL;
    std::uint64_t aWandererF = 0xC80469335EBC1554ULL;
    std::uint64_t aWandererG = 0xB3F9261CB838162AULL;
    std::uint64_t aWandererH = 0xAC12A46B6F238A08ULL;
    std::uint64_t aWandererI = 0xEFC3243D5791A0BCULL;
    std::uint64_t aWandererJ = 0x879A97356D44837AULL;
    std::uint64_t aWandererK = 0xF7D7664858548FF4ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    TwistExpander_Polaris_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Polaris_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Polaris_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 24 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1797 / 1984 (90.57%)
// Total distance from earlier candidates: 41917
void TwistExpander_Polaris::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1808U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1784U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 623U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 150U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 55U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1453U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1248U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 223U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 96U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1503U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1006U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1840U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 987U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1160U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 856U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1841U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1490U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1839U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1057U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1332U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 428U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1040U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1732U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1065U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 604U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1626U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 249U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 391U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 602U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1072U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 903U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 864U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 110U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1760U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 823U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 585U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1789U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1786U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1452U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1356U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1417U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1662U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 912U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1673U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 685U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 134U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1881U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1103U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 141U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1900U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1089U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1445U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 752U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1134U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1326U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1785U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1552U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 649U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 50U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 343U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 932U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 105U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1515U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1776U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 835U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1175U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1435U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 943U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1002U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 37U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1740U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1337U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1773U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1754U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 59U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1207U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1652U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 577U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 802U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1208U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 704U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1525U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 341U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 999U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1385U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1656U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 434U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1718U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1766U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 751U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 863U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 282U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1595U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1292U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1602U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 502U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1867U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 989U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 840U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1847U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1947U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 709U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 841U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 195U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1338U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1457U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1030U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1961U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 957U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1560U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1333U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1657U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2047U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 837U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1140U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1700U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1196U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1423U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 166U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1170U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 389U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 799U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 839U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1205U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 797U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 440U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1168U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 315U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Polaris::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xB5F76246D9ABC212ULL; std::uint64_t aIngress = 0xCC422E997666E032ULL; std::uint64_t aCarry = 0xC32694BDF7A2C003ULL;

    std::uint64_t aWandererA = 0x8E0EB3C47B006A11ULL; std::uint64_t aWandererB = 0xD29DBB233B3D7EEAULL; std::uint64_t aWandererC = 0x8A169DC61927D00CULL; std::uint64_t aWandererD = 0xD0B1BBC8C7420464ULL;
    std::uint64_t aWandererE = 0xF530CA8641D6C2E8ULL; std::uint64_t aWandererF = 0xF1A1D74E155CC7F0ULL; std::uint64_t aWandererG = 0x8940C657D9337804ULL; std::uint64_t aWandererH = 0x9F9F2860BAC7F575ULL;
    std::uint64_t aWandererI = 0xD929CC59A65424ACULL; std::uint64_t aWandererJ = 0xACA9DA0BDDC485F1ULL; std::uint64_t aWandererK = 0xD636ABFB57188A88ULL;

    // [seed]
        aPrevious = 16113551307862247717U;
        aCarry = 13863261574473425105U;
        aWandererA = 15333524609582491143U;
        aWandererB = 16519222417531642997U;
        aWandererC = 10813068884670143907U;
        aWandererD = 10857648745061869045U;
        aWandererE = 16859217747416964780U;
        aWandererF = 12542430827180098200U;
        aWandererG = 13953774802782832281U;
        aWandererH = 16972559228325559050U;
        aWandererI = 18192511807795933874U;
        aWandererJ = 11706475794682289033U;
        aWandererK = 14139769911167681322U;
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
    TwistExpander_Polaris_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Polaris_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Polaris_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 24 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 12498; nearest pair: 474 / 674
void TwistExpander_Polaris::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1803U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4376U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4602U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 462U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2968U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5048U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2559U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5192U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4766U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4205U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5272U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8076U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 306U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3495U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1050U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3502U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1154U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 993U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 29U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 988U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2013U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 375U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1503U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1517U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1317U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 620U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1533U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1309U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1607U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1551U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 786U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1420U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1123U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1224U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1686U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1596U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 24 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 12495; nearest pair: 469 / 674
void TwistExpander_Polaris::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4173U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1024U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4771U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3566U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7873U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3249U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4819U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7525U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7900U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4253U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2349U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4450U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3629U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 580U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 434U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 988U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1840U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 699U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 180U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 812U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1668U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1662U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 0U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1479U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 566U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 156U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1429U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1973U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 136U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 626U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1130U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1971U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 440U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 50U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1715U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 260U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseASalts = {
    {
        {
            0x51B98F1AD5E0AFF1ULL, 0x7A62C27E2EB46423ULL, 0x27CAD2E126804C6DULL, 0xEC757333E982108FULL, 
            0x8F88248E826EC259ULL, 0x350AB9A2D2428D44ULL, 0x951119B36C17FEF1ULL, 0x17A02CD80FAAC39EULL, 
            0x7E06C51D304ABC9CULL, 0xC9206AB0DB89A645ULL, 0x7DAFE82C4260BE43ULL, 0x154F95F60B9BED4CULL, 
            0x2329E6395A547D1BULL, 0x84AF8A96ABE196D8ULL, 0xAA70692862E5F6DFULL, 0xA5A736D1C6D34663ULL, 
            0xC49BCCB3D0D15C9EULL, 0xA350F477CBE335DBULL, 0x2A86D9108839A987ULL, 0xDAC0F0F53529CA2EULL, 
            0x99E2367BFE2D9A46ULL, 0xF1B0A5E46C53D81AULL, 0xB872C66B13AC10EAULL, 0xC3F81BFF41AA8FCBULL, 
            0x352ECEBE3F7E5C48ULL, 0x9279F7F9E7326E84ULL, 0xFB50285D784FF949ULL, 0x409D3C136EA4556BULL, 
            0xA7C2C75A3E7C8F66ULL, 0xD9CA39F9776136E5ULL, 0xB74402B47F186718ULL, 0xE44F740736FAE24BULL
        },
        {
            0x5C03254D69B651FCULL, 0xB32ADBB6BB9A3A60ULL, 0x04BDBB58BE0D6B7BULL, 0xDBBED8CE94311B44ULL, 
            0x703F83E879749FAEULL, 0x42ECDEE589F43D29ULL, 0xAC789E87DB43F7E8ULL, 0x15250D0C1AF0D53EULL, 
            0xAE3FB01731E5643BULL, 0xE8E72C7A8E6D8588ULL, 0xA40399908CA7E0C0ULL, 0x9B2FAA101F22610AULL, 
            0x4A7033895F1B2822ULL, 0x405984428F251308ULL, 0x8219381405B5AB9EULL, 0x2DC253BA049105E1ULL, 
            0x4F879F6C94F08D52ULL, 0xCED496CCAB5313DCULL, 0xA0A2544FD15440C5ULL, 0xCA27855D06106920ULL, 
            0xDBB07B3EEA04FDA8ULL, 0x6741A7225D64057AULL, 0xFA5C6599CF681E84ULL, 0x86A77129A75BE546ULL, 
            0x0E0D28163EA680A8ULL, 0x84E4BAD71CFCA10BULL, 0x1C820107AC818770ULL, 0x28D2EE6C6DECCD73ULL, 
            0xD904615B9E9EFB99ULL, 0x3604F5E0E959A006ULL, 0x66B8DB1F890F5EDEULL, 0xD8DAD1E1131D5A02ULL
        },
        {
            0xCB4E1468EB92BF00ULL, 0x99733EED1AE4F20EULL, 0xC70BD18895E805E9ULL, 0xBFAC6C0E60C26A3DULL, 
            0x617AA55F2D94EFFDULL, 0x3B1A9FFC4BBF5AE1ULL, 0x7F63A14356D1B30BULL, 0x624D62996E24801AULL, 
            0xB1B3F08105E1EBFBULL, 0x9C98004F4E49A121ULL, 0xE927D23CBE0DD73EULL, 0xB27A2540C4763932ULL, 
            0x0BEAF27F3ED30BE1ULL, 0xBEFF6BC86AA011FBULL, 0x8EF51B907CFDEE46ULL, 0xFCBA2F2412524DB3ULL, 
            0xA7327A0D3610590DULL, 0xB78D0513A1C05897ULL, 0xD8A320A65E4E5DC7ULL, 0x62EE567D33DF24E1ULL, 
            0x115B2C42430031B7ULL, 0x13E349144C4FE908ULL, 0x8FE3105DD6EEA072ULL, 0x779F584D06D33A10ULL, 
            0x540805C3AC1F493AULL, 0xA2DB2A07C98BF90EULL, 0xD5BB8B1866DF16B8ULL, 0x0E29B98A83EA3CC9ULL, 
            0x0DE88B4D964F9B95ULL, 0x144BA2A742D1AA24ULL, 0x12F1B9FAB4F6A57CULL, 0xB1F92EC9C0653947ULL
        },
        {
            0x8768EF442FEEAE58ULL, 0x8B01E68841F81CD5ULL, 0x5F0C5FFBA1C6EF92ULL, 0x63BDEA73FCEE457DULL, 
            0xD46821CB123EB05DULL, 0x9850B64E0AAB8CF6ULL, 0xAECCA581A0899BBEULL, 0xCF4E92AF9D7F8ACBULL, 
            0x5C23864FE331E847ULL, 0xAD186EC0C5FB4CD5ULL, 0xFACFD16E76B4636FULL, 0x325C0ED7F3ABA8F5ULL, 
            0x482AB06549539FA5ULL, 0x8CEDE37B08BEC6C7ULL, 0x74EF512CC97BE0F0ULL, 0xF44CAD546216C819ULL, 
            0x8B6B3C51A9E6AADAULL, 0x4317427F6B84BF41ULL, 0x0ED8F1AED41229D7ULL, 0x366C61AD7F3E3340ULL, 
            0x21EF186C8672F907ULL, 0xCB326E170C12E622ULL, 0xAFAB10DD2C993C55ULL, 0x2685203D89C4ED16ULL, 
            0x83DDB03E1F41397CULL, 0xF804D014E4ED7FF2ULL, 0x328332757CD542F0ULL, 0x37B33BF24FF78402ULL, 
            0xCA797EF52BF8D5DEULL, 0xEDF94B15F7B732F6ULL, 0x369F9FB3D3F72EDDULL, 0x9F41D9DA4E308367ULL
        },
        {
            0x38DF194274BD67DAULL, 0x162DF0DA21BA1689ULL, 0xE8532CB3A356D7A1ULL, 0x51279CE4629D05F1ULL, 
            0xD62D315878172357ULL, 0xC205E4ABF0B69DEDULL, 0x3F8782D748F425B7ULL, 0x6D63F1811B0E78C2ULL, 
            0x15C88573FD898420ULL, 0xD21A6511EC1BE95AULL, 0xA66F972BFDC94FA7ULL, 0x3506E2706EC2A8FEULL, 
            0xD78CD2075D18EF57ULL, 0x8586DB10FBDEFA45ULL, 0xFE571EE631905DF7ULL, 0x8381A45641D8C7D2ULL, 
            0x4FCE285EFC7B4C31ULL, 0x98E6E3304A6D192FULL, 0x2421BD0807C8BB04ULL, 0xCF612B3B0EEF455DULL, 
            0xFE268F0A703D98A4ULL, 0xC6E8207C86FEF152ULL, 0x008814AB6BF4176FULL, 0xFEA5973BE8EC60DCULL, 
            0xF1440662982CE4BAULL, 0x235ACA1373237650ULL, 0xF2CA4DF9C045DCE8ULL, 0xA0487DCB4F1C84E2ULL, 
            0xA9F79F57F8BC7E44ULL, 0xFB6ECAEA8DB597E9ULL, 0x62216633E34C5EC5ULL, 0xDC7B87B18FA2BEECULL
        },
        {
            0x746A4CD0D05B1BF3ULL, 0x1DD36325C516559CULL, 0xA0FA157096B4FDE5ULL, 0xC15D73A4FAF450FDULL, 
            0xB376DF6DAA96CD3FULL, 0x188686367EA94DECULL, 0x5557FBD8AF5046D8ULL, 0x58F5958D3EF9CDD5ULL, 
            0x6C7D746A7E5A0B29ULL, 0x6E477F08692B450CULL, 0x3E65ACBBF749D5F6ULL, 0x039D6E7621308B2AULL, 
            0x37DAB7D1E5FA8A06ULL, 0x01358F1BCBE8320EULL, 0x92E3FBBCA4C10850ULL, 0xD846F74747996E31ULL, 
            0x4A0EB960494FF467ULL, 0xF2C9BB7F3BDC3099ULL, 0x401E5714BF50030BULL, 0x3D35398A6A5EBCB6ULL, 
            0x3D3172E665A62BFBULL, 0x9DF5FC062FDA53FCULL, 0x89A38C915B1CAD30ULL, 0x6877F0F938C9A8E1ULL, 
            0x6B0B8B2F28018369ULL, 0x88D43E6C3668FB35ULL, 0x457EE56859BE119FULL, 0x2AD38251A44C58C5ULL, 
            0x4837042E9DAA525EULL, 0xA71BFD4A4704C499ULL, 0x036C84D90C036862ULL, 0x08E1603F32BD3EBCULL
        }
    },
    {
        {
            0xE5A184110EE2EAFDULL, 0x6ECF85650A8CF0D5ULL, 0xC9DF0ABD2D9556EEULL, 0xC3AF8246EB08F148ULL, 
            0xE2CC1885E8637F28ULL, 0x8B96E5B4259CA0FDULL, 0xB4406690059B91B6ULL, 0xB44DEC7CF13A6261ULL, 
            0xA2FE8C5623EE45C3ULL, 0x782C8913B40B59D8ULL, 0x43E101996543F2A9ULL, 0xA4EC959996F1EB54ULL, 
            0xDE4CA70CFBC2076BULL, 0xDCD84ABEBC0A029CULL, 0xCDE4454D15743BE3ULL, 0x3F4AD4B68D8CC092ULL, 
            0x869B2F915005F94EULL, 0xAFC47F158106E8FFULL, 0x5D8F9188734DB219ULL, 0x601CB562C1C7F147ULL, 
            0x04125BE06E9C4B10ULL, 0xDB5B24CBB1E32D4EULL, 0x94331A5B0863302BULL, 0x79EAAC2F08CE9D8CULL, 
            0x516D76108B6B10EEULL, 0x8D83AC0307C4E5CEULL, 0x0BF2296346FEE5E7ULL, 0x86636DD070B8199FULL, 
            0xC02A2B307AF2F04AULL, 0x040BAA363BBC8663ULL, 0x183EDD7AF7CBBBD0ULL, 0x3F4A97559DBFA638ULL
        },
        {
            0xB3845F9D586471E3ULL, 0x2D91AF4428C8C647ULL, 0x65A9EF54D15F75B5ULL, 0x5A2616BAB9FC7A23ULL, 
            0x348231BA7941D13BULL, 0x69DAD4E12043409AULL, 0x5E286546D208D70FULL, 0x4F1B3439633A3909ULL, 
            0xF10D387172BC602FULL, 0x0CB482018E4B6D4EULL, 0x7F85D024F79DEE8FULL, 0x868D3F90A14C2A9EULL, 
            0x0BA41B0AAFDB583EULL, 0x7CA731F401BF600DULL, 0xBF09BFF6C251031FULL, 0xBC6978A95885C574ULL, 
            0x3EEBA1E5FF4C59F3ULL, 0x52F098B136A0C772ULL, 0x5F0F2DC593B6CBB3ULL, 0x4144C4C2501EB6DAULL, 
            0x125B75097182299AULL, 0x11562D5DF1D895F2ULL, 0xADE99C4766E92230ULL, 0x1DAD0A990E1C2354ULL, 
            0x3BD10A935F39FEB8ULL, 0x2CDCFE708C52286CULL, 0x070F03EF2272EB44ULL, 0x0C35D7000453DE78ULL, 
            0x10EDB61025599B4CULL, 0x5FAAEDF48B5A63F7ULL, 0x1AFEE877CD73C8CBULL, 0xF343FBB1A8202C18ULL
        },
        {
            0x537509ED1783E4C4ULL, 0xC37FFBD2F8D24372ULL, 0xD71C2EF87C4374A5ULL, 0xB4CFB6774390C799ULL, 
            0xC5A32E7A186DAB2AULL, 0x2AF2FA37C60AAB48ULL, 0x9D30EBCECF99371DULL, 0xF59BB938A763017EULL, 
            0xB8F023514BA93DA7ULL, 0x5E89B2B8EA0CF131ULL, 0x33DA9A273A5DAB9AULL, 0xC8DCA9B894AAAD3DULL, 
            0xF4276C5850DD8961ULL, 0xFA771E3365E9E4DAULL, 0xEEDCEC786723B572ULL, 0x656B338E98D64001ULL, 
            0x63A4C92DB17E816AULL, 0x60D5014DA9F20D70ULL, 0x7D385140EEC1499FULL, 0x36852B89A8DE8920ULL, 
            0x9AB3A677222E1636ULL, 0x4D97394AF55E8E5AULL, 0x08E622DC1F7A032FULL, 0x5332AD73B4543237ULL, 
            0xBC50E10C4A6920C1ULL, 0xA1E39E7A1707A818ULL, 0xCD56131202D8E16AULL, 0x0F62F36515960A6CULL, 
            0x953624A3D4870267ULL, 0x0240FA84CBB32FA9ULL, 0xCA1446785535A1F8ULL, 0x1CFADD38367EEEA9ULL
        },
        {
            0x2156E0EAF721266DULL, 0x9A6FB6CBCBA126BBULL, 0x7D8475B970C40FCFULL, 0x00C2D97E06843363ULL, 
            0x3349D9144BD8BE75ULL, 0x481E4953FD7E51ECULL, 0xCE265C64E857BE46ULL, 0x2D61341889CC3388ULL, 
            0x34C9919C3875EE7AULL, 0x2245F85DC2FC3ADCULL, 0x6043989BF8689C16ULL, 0xBD16A9825027C8F6ULL, 
            0xFF5781B4F699E633ULL, 0x558015D2F517AFC7ULL, 0xF046DE87E5538F41ULL, 0x28E9E9B742FCCB86ULL, 
            0xDE77B5C09B274B03ULL, 0x5A0E1C28FC74BB53ULL, 0x765023DD50CB4308ULL, 0x39C60153A18A7EA0ULL, 
            0x17400D580E45AEA9ULL, 0x96698FA633B83BAAULL, 0x0B2A46AE3F1E1E90ULL, 0x6482385E7EE2E0B4ULL, 
            0x94D56ABE377ACC4EULL, 0xB0EF4943E64A4DC6ULL, 0xEBB2883AEF67E58CULL, 0xB51EA1FB5C9DCD9FULL, 
            0xBA78D0E9F8449AE3ULL, 0x7337287D87D02A21ULL, 0x264A70451720F51AULL, 0x898C1D6E88DE930AULL
        },
        {
            0xE2B048754E64C5B7ULL, 0x3DAC8C4163377B3DULL, 0x7C5B10AA84AAD44AULL, 0xD153571D9FB0048BULL, 
            0xAF368500836EF700ULL, 0xD776D608FE9EF520ULL, 0x87ED073ADFAF007EULL, 0xD88495C38518CD6CULL, 
            0x4DBAF0FAF3D7B18EULL, 0x605434F99EEE49C9ULL, 0xB513CAC92CCBB690ULL, 0x30B91EF25CDB0621ULL, 
            0x23D82E32EC577056ULL, 0xBD8536A51896397FULL, 0xBE9AA399BC92A349ULL, 0xC06A0E6940E61BF6ULL, 
            0x9F749286E4A2EBACULL, 0x86C8E81449121D60ULL, 0x34DF8A93B2EFC579ULL, 0x258DFBF41F8E7B03ULL, 
            0x1B4945DEE8C1DB3AULL, 0xA0798EB289F968ABULL, 0x925AA90904EE60BFULL, 0xD24AC70BE62572CDULL, 
            0x379D85728EFF999CULL, 0x16DFB43050FAE0FEULL, 0x550D01C79DA660D0ULL, 0xC01576F85B9F227FULL, 
            0x31A7CE73D777F725ULL, 0xFDF1A504054B0B7AULL, 0xAFBAC7D6D4DB4615ULL, 0xA4A82B5C2C459EDFULL
        },
        {
            0xF84CF59B0EDF35A4ULL, 0x0030956D92DAF331ULL, 0x5B10C87E1C3EB14BULL, 0x7134684CE384947DULL, 
            0x98B58C3556215652ULL, 0xE83ED80FF3CA6F4CULL, 0xC8B00602C3688F74ULL, 0x9E2A2759F5B944BDULL, 
            0xDF7C5604B40405A1ULL, 0x9BB9CAF253FCF056ULL, 0xD460C3C6BDA87377ULL, 0xBFB11D09FA1C80E6ULL, 
            0x30B44DE638EE5C94ULL, 0x6192DE8E79D8FCEFULL, 0xCFE92EAB0DB644B9ULL, 0x9F1BA5C516C972F0ULL, 
            0xD88F9643B723B51FULL, 0x2BF127FFF53084F3ULL, 0xA014EA1DB7F41240ULL, 0x78CBDB909A2E6CB3ULL, 
            0x88009089AD02DAFFULL, 0x3094697CBA3C4A61ULL, 0x4A0F944F2F841B6BULL, 0xC59DD44C7FB06512ULL, 
            0x0C72493BAE9CFDF5ULL, 0xBEDDC43C2CF8F6AFULL, 0x02C988CD4BF4F1B5ULL, 0xAFFC6960B5997717ULL, 
            0x95B736767634FD72ULL, 0x797E7B34E072D06EULL, 0x8F9FB29AF69FB8AFULL, 0x85EFDA9AE1FE593FULL
        }
    },
    {
        {
            0xE45EE9B98F0BDB41ULL, 0x0C2638D19A2B5D87ULL, 0x525C4D8CBD73E7A7ULL, 0x7726223FFC9AEBCBULL, 
            0x9590565F73F45FFAULL, 0xBAFD281522A95267ULL, 0x085316F5BC537AE0ULL, 0x28C74471AA231796ULL, 
            0x48A213194A58018FULL, 0xE537AB36E655372DULL, 0xEB5679B8EA137B12ULL, 0x7B8CB7D16A51EF59ULL, 
            0xB8B49145AFA9800FULL, 0x696B4A33D88FBB7EULL, 0xFE7BDCDD932D11F6ULL, 0xF09F7A1E1BD119B7ULL, 
            0x10A7F79B5B603024ULL, 0xAFC4CFE6EF0FABC3ULL, 0x1163F0B23F03DFFCULL, 0x51805B60DB9D2412ULL, 
            0x9540E21B4456EE1CULL, 0x8BD150EC8204588BULL, 0x4F9911E2573A7468ULL, 0x76ACA4808159D3D9ULL, 
            0x3BA6130D2C415EDEULL, 0xC4520539BF3B0D6AULL, 0x5AA89D371883E948ULL, 0x2D9F59EE9761A503ULL, 
            0xF0E04F4530D1CB2AULL, 0xB6F5218B95A65CB7ULL, 0x00CFCE7B00CB750BULL, 0xFF80F5E898E0B29CULL
        },
        {
            0xCB5E858D7C5F5F74ULL, 0xA134A095D6C74051ULL, 0x2390C34DF71FC66FULL, 0x2FB8DC796057D221ULL, 
            0xFEEA5125B5457621ULL, 0x585908688F359407ULL, 0x91FA4D077348D800ULL, 0xCD13CE59FE5DFBC4ULL, 
            0x0642876EC8A92DC0ULL, 0x9E19249E7D0934F3ULL, 0x108DB54938A39ADAULL, 0xE1BFDEE65924417EULL, 
            0x4E88BE54AC5986B4ULL, 0xCDFC15568B2F30E0ULL, 0x7AB4911EA6CC58A3ULL, 0xA3A3AB4ACEF365BEULL, 
            0x4FF6AB594D218522ULL, 0xC9FBACFBE1E02122ULL, 0x3FD8184B31CDBCB9ULL, 0x0E66D470D762E34CULL, 
            0x24B9FA1189955082ULL, 0xC7957BEDCFF47192ULL, 0xCBCEF4D92EDF1FF5ULL, 0x176A8E4C9EB8B435ULL, 
            0x3489D37AB501734EULL, 0xA115BDEB1B4BE615ULL, 0xC314FF059B72073AULL, 0x210E2D7A80C84D0DULL, 
            0xBEEA1E03B10CDA55ULL, 0xC3C5243824DC7F97ULL, 0xB71A8DBAD60D157EULL, 0x9F9088365F1348A4ULL
        },
        {
            0x1688701BFF0B563AULL, 0xAFEC888D04C24344ULL, 0xD4D260DAE1318407ULL, 0x97EA4FF4D372CD32ULL, 
            0xA1E3E20BB1B3C6FAULL, 0x48EF9749016EA1FCULL, 0x0263BD1E58AACDD5ULL, 0x041CD26F9D632293ULL, 
            0xF2D3CEC213A54C9CULL, 0xD96C7F6BC6A104B7ULL, 0x042D0E68CCF59958ULL, 0x2E22E83F289A4DA3ULL, 
            0xEC4AEFE8D9904ABAULL, 0xC6034322C7ED56D7ULL, 0x5DAA7FA9E7E70463ULL, 0x2ED7B8CF49B8C0F3ULL, 
            0x35C545F79259A234ULL, 0x31222ADD9222C354ULL, 0x1480F78ECB063895ULL, 0x61D2038B9430E453ULL, 
            0x46E158CB07B6413EULL, 0x0F59389CBAE21BE6ULL, 0xF6768DC669EB2C05ULL, 0xF95A8124BAE85D35ULL, 
            0x232005EF447442ABULL, 0x67D8F7FA528C75A6ULL, 0x4C1CAA69ADCF629BULL, 0xE65EDC8A19D464CEULL, 
            0xC77238A5B320F500ULL, 0xE548890080B5D678ULL, 0x84725769C9AFA7BAULL, 0x4DDF6989F5A247FDULL
        },
        {
            0xC0573DFDA67CE92EULL, 0xD2489FBE90B77D97ULL, 0xE5A8E4283ACEECECULL, 0x9AD237CF30C552A1ULL, 
            0x3504F4241402DBFEULL, 0x5957295009D711A1ULL, 0xA609CAAAA71E03DCULL, 0x57FFA2A01C9A0023ULL, 
            0x71FA60F54CDC73A5ULL, 0xBDDA90E9F4487286ULL, 0xEAB6E65A21612532ULL, 0x9670306778A5A203ULL, 
            0xD18C9C24AB106254ULL, 0x54137269E58B24EAULL, 0x3603CF781AF55BBCULL, 0x7BC7A2038E0099C5ULL, 
            0x533ECD27C0DC2714ULL, 0x62EBB1885903E864ULL, 0x7A0D707CDF67805CULL, 0xB62D851A6F4A0BF7ULL, 
            0x621A488FA94D69E4ULL, 0xE6EB1CE9A9F44102ULL, 0x657238126F96D1CFULL, 0x54E5899FADE21FC9ULL, 
            0x1C357883690E1537ULL, 0x8B4923076F9D5D1BULL, 0x412A5EB9B917C3FCULL, 0x66AAE880E400C428ULL, 
            0xAAEBBA994BD55F62ULL, 0x71DE666AEF1990DAULL, 0xFB23C7D195372192ULL, 0x2AF4B1015CDF53DEULL
        },
        {
            0x6169C1E11393E60FULL, 0xA007361683692C7DULL, 0xA3415361273BA09DULL, 0x5AAA03B3AC05F612ULL, 
            0xF32E36BCC4D4B4C6ULL, 0xC599251C8CD9AED8ULL, 0x294E899260DCDF7DULL, 0x059A384FC024A77EULL, 
            0x03BF3D16FF4A0857ULL, 0xC4F3188CB02D5B71ULL, 0x5734BDB195141B6AULL, 0x0B8F46B410F614E9ULL, 
            0x8144778389E80F89ULL, 0xF9301E7427C04494ULL, 0xF74254C4AFE3CA8DULL, 0xF63B6BEB1CBB5B82ULL, 
            0xC964DC2D4F512E58ULL, 0x1AFD45991913BA70ULL, 0xA4AD444655A615B7ULL, 0x3C29EA54A7997215ULL, 
            0xC25D48E7EBC4C82BULL, 0xD44909DEF84A5F0AULL, 0xBDC0A35A7366925EULL, 0x11A17639EAD80D22ULL, 
            0xE000E573B2FB3F11ULL, 0x4D28ED1940A8890EULL, 0xD23D2BA24DAF6ED0ULL, 0xBC053553C5019625ULL, 
            0x31070B632ABB7DE6ULL, 0xF00DD25788FE5704ULL, 0xD02177880DD8F3BDULL, 0xD895DF6954B60209ULL
        },
        {
            0x61266B5F53CA0B1FULL, 0x24B82FAD8342BA84ULL, 0xC5A57D8749911454ULL, 0x28A4BF03269E4915ULL, 
            0x31A4B4E2DB6772E2ULL, 0xFCFF1B49DD28D64EULL, 0xDDBE5AAE059128B0ULL, 0x7039FC31C1D90B52ULL, 
            0xABDB515DA6A829FFULL, 0xC6C015767D3FFB46ULL, 0x0A1B97348CD4251DULL, 0x0937FD3A2604D79AULL, 
            0x0D366972EC7DD5D5ULL, 0xF63D2D6384627C5DULL, 0xFC951816347D4932ULL, 0x5A9AC17C55E12B35ULL, 
            0xB9EDBB770AAACB29ULL, 0x4EF647902137B29CULL, 0x143A890470198B1CULL, 0x4D9A6D09EC883F4EULL, 
            0x6AF1E972B0FCD557ULL, 0x224990B0060EF44FULL, 0xADF7AF6F154A1A01ULL, 0x6906AD29F52167BFULL, 
            0xED9AF83CFB32B2C8ULL, 0xA7FDB9D90B3ED61AULL, 0xA6065557A2564525ULL, 0x62852A63EF1A14CDULL, 
            0x41C8103593A674F1ULL, 0x5A3317400773144FULL, 0x4616574FE9240FF7ULL, 0x8CFAF1226CCF3B04ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseAConstants = {
    0x1D6EA91EC70AABCBULL,
    0x14DC2E858D5189F2ULL,
    0x8CD4C688ADE78EBEULL,
    0x1D6EA91EC70AABCBULL,
    0x14DC2E858D5189F2ULL,
    0x8CD4C688ADE78EBEULL,
    0x96D51B3CFF2F5148ULL,
    0xE321C8AF537B944FULL,
    0xFC,
    0xF0,
    0xD5,
    0x71,
    0xE6,
    0x62,
    0x8C,
    0x0E
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseBSalts = {
    {
        {
            0x4CF3BA226330707FULL, 0x161E12CCFCA80245ULL, 0x0409FDC2ACEE359CULL, 0x1977C3B169BD1C63ULL, 
            0x9E271B1646C60430ULL, 0xB9C0F33A08B5CC01ULL, 0x4F312FCC5909DFFAULL, 0x4637A90656826305ULL, 
            0x02028ED80A9A15E6ULL, 0x5F04F44CAB1F04F5ULL, 0xA9E956EED835DED9ULL, 0x53AC28302120DAACULL, 
            0x336141EACFD73BE5ULL, 0x93CB979074F90D3BULL, 0xE12C26450604B526ULL, 0xF21F114B3B533177ULL, 
            0xD694C109CD9D98B0ULL, 0x7D410719489E9662ULL, 0x414FDE0D5D09C217ULL, 0x8EE6158C4CD6AAB9ULL, 
            0xF7910F526B6D6DF1ULL, 0xE10CAC97DF020337ULL, 0xC29E6A1087E56936ULL, 0x589919B0D4905B3AULL, 
            0xD14499ADA4273D04ULL, 0x86D937C839AF7A51ULL, 0xFAAC9F668C78B264ULL, 0x6D4B11329D628DF2ULL, 
            0x3084D1AE0296E22AULL, 0x918AA2FF46DF22FEULL, 0xA45F595A3429C708ULL, 0x15C5E6A43F346537ULL
        },
        {
            0xA3B8DB32F5AD686EULL, 0xCF3CED3D56F8FCABULL, 0x4A277671933C9C6FULL, 0x9F4602E89B69C161ULL, 
            0x6B21135D55E6E310ULL, 0x9986A0DC7E810077ULL, 0xAC38EC54715A930BULL, 0x61D75BDF4992B35CULL, 
            0x6520DF08E018CC73ULL, 0x7A5AFCA701CAD654ULL, 0x842C7C52DACF302FULL, 0xFCEC555C211A6823ULL, 
            0x344C95E24331D3C5ULL, 0x24ECA2E0BB31F3DEULL, 0x24D251AC6BF744E9ULL, 0xAEA9A9EBBDCA052FULL, 
            0x53839159853EDC8DULL, 0x93C62258468F883AULL, 0x3EA6B73339045695ULL, 0x1C27D371803A4580ULL, 
            0xDD280490EBE8BDF2ULL, 0x075A2C7EB68112FBULL, 0x39AED644C76E3CFAULL, 0x68FAAA8734592883ULL, 
            0x815BDEDDC24B6083ULL, 0x00FAA34FA4F1BDCEULL, 0xE570BE3013379166ULL, 0xCDCC21F822733F71ULL, 
            0x26A7643D464F3E96ULL, 0x8D12A4E90454BFC7ULL, 0x057BB7E63BA95EC9ULL, 0x8498E0D24A1C5412ULL
        },
        {
            0x2151BFD0439FC788ULL, 0x3B74A6E6823656EBULL, 0x1C8159444E7B6306ULL, 0x3BF86114E264999DULL, 
            0x784AD4C63C33EC6AULL, 0x0470EB0F8F78EE97ULL, 0x9B3713167A9DCCB8ULL, 0x945CCDD588692908ULL, 
            0x7370A4E216C473BBULL, 0x37F772F19E8EAA85ULL, 0x76E44243AEECE8B2ULL, 0x90A084E70B3C79C0ULL, 
            0x1E2DEE87B7CA0B61ULL, 0x876FF974E52DF1BCULL, 0xE7E62D58DEE8CA51ULL, 0xE7671F013ABB42A2ULL, 
            0xD1047D940F892701ULL, 0xA7BCBACDF6928DC2ULL, 0x60448A177BD501ADULL, 0x069A813B2B807D98ULL, 
            0xDB542069982D6E72ULL, 0x0C9FA67946481B2EULL, 0x2DEB0BE07437B56CULL, 0x5B3D1A91A5D9A662ULL, 
            0x92A12840AB8D0815ULL, 0xA77BC7951660E593ULL, 0x4DA5CA19A3D6B0BDULL, 0xF747CCFD46B17E85ULL, 
            0xBAC5EC8258A03867ULL, 0x0D6000C4F3E28D49ULL, 0x13997277D58067A0ULL, 0x6A52CEDEA481E7B6ULL
        },
        {
            0xFA3F2F9484587724ULL, 0xF7CB97F0902E777BULL, 0x8B720B60A5142FA6ULL, 0x32E8022CB92BBF5DULL, 
            0xEAEFC8F057717A55ULL, 0x1E102C3E02FE4AD1ULL, 0xC12546F8F854DA9AULL, 0xF879B7258624FC9DULL, 
            0x15344B7A8394F999ULL, 0xC0BD603787CEA372ULL, 0xD89E603371453F72ULL, 0x67590FEFF488F373ULL, 
            0x5677AAF9B802D21AULL, 0x0F6DA172E855DBC1ULL, 0x56F56A184FAFFAD2ULL, 0x6ACF5AD725652404ULL, 
            0xEDB4C23BD301D5D0ULL, 0x45E3E5A2825603B3ULL, 0x01638493CA333DE1ULL, 0x1F94C757806FA4C2ULL, 
            0x283D17EC13534C57ULL, 0x0B937C8E2E84FB60ULL, 0x07AAFB9CEDC28552ULL, 0x0FCDA8B95535081DULL, 
            0x99B186346D226FC6ULL, 0xC5FEC614DB624E88ULL, 0xD86FF593E1DD5651ULL, 0x9E91D3D79C280598ULL, 
            0xAF3FF529AD7900A3ULL, 0x9C0ADDB158B72A16ULL, 0x93BADDF942AEC513ULL, 0xC7A7BF213D74E8BFULL
        },
        {
            0x2AACBDA08AD6EC37ULL, 0x4D2EFD595954A8D1ULL, 0x2596407FFBD5F7EFULL, 0x869F6ED26DB017DDULL, 
            0xD3F4529F7AE8FAF8ULL, 0x04527A2004CBEB50ULL, 0x5D20F477BA8F3CC2ULL, 0xBD22CBBC82B85C50ULL, 
            0x279CF6C9463B9434ULL, 0x2EC8597F9DB29DF4ULL, 0x92BE8AEF7806769FULL, 0x8D828B389418A4E3ULL, 
            0xC174D87DE2F2AA20ULL, 0x78DA6E2C16A3DF5BULL, 0x2FB37DB6759B6828ULL, 0x7A787E170B013EF3ULL, 
            0x89F10F6928637FB8ULL, 0xBF758F575DA5B642ULL, 0x08A88FBB37FA45B8ULL, 0xA40792A757249AF2ULL, 
            0x7B2F6D123E0CCA55ULL, 0xC38C5F4ABB02CE38ULL, 0x91256E7F9765C9DFULL, 0x811E3B69E2EEF043ULL, 
            0x01D9DCA79AE42E70ULL, 0x9F7D84AEB3BDA0B8ULL, 0x27A5863DD34EE69CULL, 0xC586D48D7624077BULL, 
            0x49BAF0879D9227DEULL, 0x543F14994C99FDA6ULL, 0x1E2F3782B237258EULL, 0xB04E8790DCC600F9ULL
        },
        {
            0x7A6C0B63538C6EFBULL, 0x300F51FB34E654C9ULL, 0xCE9B7284CD8BD032ULL, 0x3F930A44967A36E9ULL, 
            0xA8EDEA71DF18BF30ULL, 0x1C93491C76DE4122ULL, 0x50CA1A359A0CCFC9ULL, 0x2891BFD95597AB76ULL, 
            0x19CD8D425830EA39ULL, 0x9C49645927117A01ULL, 0xF109920BEA97DE7EULL, 0x41B20CE74472A4E8ULL, 
            0xA524C9D1427A9B63ULL, 0x2F9782B15F4EC7FBULL, 0x6B5B4EC1ECA49D1CULL, 0xCFCDB3EC56423522ULL, 
            0x7296DE451599ADA0ULL, 0x3AFAEF9184FD6CA2ULL, 0xD3F2765F9CF94DDCULL, 0x0515D327767104A0ULL, 
            0xBD08B94198945993ULL, 0x60C402F211C01F43ULL, 0x3BDD4E6D157C1105ULL, 0x1C8587551B1D6622ULL, 
            0x005A002CFF01F88EULL, 0xCE16AEE26085A335ULL, 0x849F657755DCA2FCULL, 0x37B00EABC87378B7ULL, 
            0x1908CFCDA4BCBA2FULL, 0xF07BC5DDD8FF938EULL, 0x49BCC2E5433D7466ULL, 0x032580C657703749ULL
        }
    },
    {
        {
            0x88C9D8789DB47B41ULL, 0x5EBE8BC2F2EDF19CULL, 0x143FD62796EFA578ULL, 0x36A2BF47692665B6ULL, 
            0x14D43D570631E880ULL, 0x8705ED40B4D9C4A2ULL, 0x409D89124F270E5EULL, 0xA8D9AF3E8D6A2D5BULL, 
            0xC4CCA6DFC4F13A76ULL, 0xB5D1ED36E4BBC302ULL, 0x96EE04F2E95BAB99ULL, 0x0714554DB97F91C1ULL, 
            0x0857CB5C9BF4993BULL, 0xE4F9EA73EC35523BULL, 0xB1FE4B4EDE98C404ULL, 0x7DE9C1B168BE5445ULL, 
            0x2ADF0B453CA1D500ULL, 0x3DF25792B11B5C2EULL, 0x8B2F365987CADA94ULL, 0x057100A748A966D7ULL, 
            0x09CC3B717CD6EC1BULL, 0xC8120D57DA77CB0DULL, 0x5BA60CDA3D792F10ULL, 0x0BAE939FD333D95BULL, 
            0x3C63B05EC613C848ULL, 0xA1A3730C1D9FA46DULL, 0x3F49BFE0198EB6ACULL, 0xDAF6DAE16C114493ULL, 
            0xC44FB1783687E72CULL, 0x2D05D689B3421794ULL, 0x25307B149BACB178ULL, 0xD2EEC32E453ED80BULL
        },
        {
            0xD4213F337316B788ULL, 0xED95EDA7E4E521EAULL, 0x39FAA1CDBC9E9FF5ULL, 0x68D8C78444FAA6B4ULL, 
            0x60E392FA053D2978ULL, 0xA418F2B852382E14ULL, 0x3384EAEF5BB18DABULL, 0x7CBED7DE2494D8BCULL, 
            0xAAC5B6C5846CCFE0ULL, 0xF08C335E12665691ULL, 0x9F2A4D9F67F836A6ULL, 0xFB5C29C73B6297C5ULL, 
            0xE6AA18D11980A932ULL, 0x06CF2327A05C31CBULL, 0x679431D812092DE7ULL, 0x0BE66BD08A840856ULL, 
            0xDCD90BFAA28F7286ULL, 0x427B7480C370D78DULL, 0xC39D0F4BD1C56ED1ULL, 0xAEACD676ECF4B587ULL, 
            0x94CE50E367423848ULL, 0x2E3C177E46828902ULL, 0xA31DD566310DBB1AULL, 0x452BB83266EAEBA8ULL, 
            0x446B7EA84E5ED8A6ULL, 0x3CFE6B3DCBED5D0FULL, 0xF60EB9C379B6AFE0ULL, 0xE875964772EBB3FEULL, 
            0x6DE4F2A1EDCD1140ULL, 0x1F6017C339C6F298ULL, 0x12338BBDBFED8809ULL, 0xD918FCA44BD1C275ULL
        },
        {
            0xCB8CEFA7F13E147EULL, 0x4CF06062FEBC0A31ULL, 0xA68CEF00B0FFF50AULL, 0x6B9BBF5E0A93E919ULL, 
            0x2595DA74D3D583D4ULL, 0x756561BC2E8E390BULL, 0x3F44F8B420C264D3ULL, 0xB5987F8C8DEB861BULL, 
            0x39DD13EDDF1F64D6ULL, 0x427E6B4A95C208A8ULL, 0x457E12B1C0C73603ULL, 0xC61B4DCB69BDF9F4ULL, 
            0x1619115658F607F9ULL, 0xA67A7B902371AEE6ULL, 0x15E145CA7D3DCD68ULL, 0x3CB3D8E90EA51BC4ULL, 
            0xF684E4EBF5C4F6FFULL, 0x907F3B196A7EDB19ULL, 0xA4760EB2BAF70736ULL, 0xC7F15E8254F19014ULL, 
            0x8C5F622CA8A65916ULL, 0x55715F60745A8913ULL, 0xD76DFF8A9ED98425ULL, 0xEB853747AFBCBF28ULL, 
            0xDBF0F37487937068ULL, 0x70B49F4AE107EBAAULL, 0x56CD5E0EF8814B7BULL, 0x2EFD29DD8FA2D109ULL, 
            0xC782E73420693599ULL, 0x7AC67A2C6DC09452ULL, 0x030F30507A5ED0E5ULL, 0xBB79E2E4780D231BULL
        },
        {
            0x4E6A4EFFA96714D8ULL, 0x8B80C5EBA06CF6E9ULL, 0x4D30F21AD14DFE85ULL, 0xC852879FC0169F43ULL, 
            0x3B4927DD9B4E413FULL, 0xC5E1CF6C1B5F8F30ULL, 0x0497F3E95C3E5AC2ULL, 0xE711FE10116428F1ULL, 
            0xE1271D29BEB14247ULL, 0x2F5A229F19B97FF5ULL, 0xE69C1B215FB524D4ULL, 0x5A865540A087B1D6ULL, 
            0xA1C3F92790AC3926ULL, 0xBB1F9D4B45013E31ULL, 0xADAC2ACA0988A755ULL, 0xD280A95654E07146ULL, 
            0x08125757D989C256ULL, 0x8E22049144F08E36ULL, 0xBD0B6E09F0E7D810ULL, 0xAA65EC0F83429152ULL, 
            0x6E06416544EDFC38ULL, 0xB576A85C20B95A56ULL, 0xFEFB5100B51D8047ULL, 0x5DF1828A513FD236ULL, 
            0x44A06176A0404312ULL, 0xEC7B95B93C670BD4ULL, 0xF54923AEBA6FEDDAULL, 0xD5C42A3E7F959C40ULL, 
            0xECFD6E8310D5AE3AULL, 0x4CC5745D086302A1ULL, 0x46D49EB15CF7E5C9ULL, 0xF643686E8589FB36ULL
        },
        {
            0x3DA776679953AF54ULL, 0x8EC7A7E96DD8AA88ULL, 0xA28B159AD2CB8491ULL, 0xA458031C58078C36ULL, 
            0xBF108DB7AF6FDC89ULL, 0x3931E20F8E5D462CULL, 0x876C82198DC564C5ULL, 0x698B5CCF3AF02D81ULL, 
            0xCDBF5FFE32FC14A4ULL, 0x9D01593FC50DC41CULL, 0x35ACB75599BC3286ULL, 0x7FA26C1C0E7B495FULL, 
            0x9A6BBD8EF15471C9ULL, 0xDE36EA8887308F76ULL, 0x96619D0530A08891ULL, 0xC1FE367E66902FCEULL, 
            0x4943C6FAE0EF63C1ULL, 0x93F33FCD77325C4DULL, 0x9859C813733BB047ULL, 0xFCECC9FD88D2DD38ULL, 
            0x6612330E12501765ULL, 0x3A3429038BC88954ULL, 0x1D72CFDA354D6A7BULL, 0x0A92F9CBB5E7A028ULL, 
            0x8DF4EBB12E113335ULL, 0x29734C97BA60194BULL, 0x25F9A93C2297B6FBULL, 0xE423A27C5E89825BULL, 
            0xE1FA57A6333BF34CULL, 0x4B870DFED0597A99ULL, 0x9A15EC4115E6A5BBULL, 0x5C673DA1399A18A0ULL
        },
        {
            0x73093A63013EF3B1ULL, 0x793E5BC3E66F4CFDULL, 0x9716C49C0F1F9CE6ULL, 0xC92D29DCB72E7181ULL, 
            0x5D99078B8630398AULL, 0x66A8A7F053513D1EULL, 0xF9DD82DA953A97FAULL, 0xFC6568F7E3CB8039ULL, 
            0x9680640200D343ADULL, 0x5C4C4AA033AC1EDCULL, 0x321E6736953A27F0ULL, 0x3AC1498811DD5597ULL, 
            0x8A18F5B318D27696ULL, 0x2DCDF385156E0F99ULL, 0xFAF0501234E49C78ULL, 0x871EF0924B572C73ULL, 
            0x6B7007266DF78F23ULL, 0x1D30AC9F938A6B56ULL, 0x81CEE5077CB3E608ULL, 0x52550CEE9AFF2450ULL, 
            0xF059666B18AB1870ULL, 0xE2E8684C0B6E6D28ULL, 0xD219E8F879CDB9E5ULL, 0xDC9E943E2655FD0DULL, 
            0xE24F2190C274CE7BULL, 0x6D7BB9A0019A4935ULL, 0x722B38BC092EDCA8ULL, 0xFF40A084108B6205ULL, 
            0xFF0365BE91B370F8ULL, 0x10D66466AC590A5AULL, 0x171BA660B17ED98FULL, 0x51749146FAD65FEAULL
        }
    },
    {
        {
            0x1F99FF8E5A787125ULL, 0xD507FDBDBFFCE648ULL, 0x64815B3A8B1AF8C7ULL, 0x61871A5750198DA3ULL, 
            0x13AA9D39C2442D49ULL, 0xDF7300C42E733F1CULL, 0xFC28C9A373F37FFCULL, 0xFB15B9ED9684DAAFULL, 
            0xDDB5144FE07B8A3AULL, 0xC4D051B0DA88FDBDULL, 0x2BD83E01B30353D5ULL, 0x59FFB42D9957EF90ULL, 
            0x7734E2115AC71CC0ULL, 0xF524AE27C48FF51EULL, 0x814B5D83DACB6954ULL, 0x7B90B0EB2FFF6F72ULL, 
            0xAA7A26F89561D27BULL, 0x90768AABC6D1792FULL, 0x6DBA9188873E9AABULL, 0xA23A5860D3D92E00ULL, 
            0xDFE171795751FFB8ULL, 0x9524DE8E7A42CA8FULL, 0xF70D4DB0B9994EE0ULL, 0xCF78B7A96F74146FULL, 
            0xB796E34DEB184B57ULL, 0xD000F1D772094592ULL, 0xEE9F64482F244810ULL, 0x7FCBCF1414942F6CULL, 
            0x1D469F0882758EF4ULL, 0x0D9F0B103E385B0CULL, 0xDC5CBC7768FC9BF4ULL, 0xCCC655EBFF0CABA0ULL
        },
        {
            0x4108EBB1C8AFF9E5ULL, 0x9D959066B04DF5E4ULL, 0x9D884360B45DC0A8ULL, 0x5BCB51E98F5DF0C0ULL, 
            0xDE6631CC57E9584CULL, 0x77A8BA65803C3706ULL, 0x9A720EDA9EDDE276ULL, 0x00C13735A8E037CAULL, 
            0x373ECD227F51CB67ULL, 0xDACE80D0EA6E85FBULL, 0x1894624815F68375ULL, 0x05FDC626BC2B3426ULL, 
            0x7D5BC7E800761D56ULL, 0x8C19F885B17351C6ULL, 0x5A7215C69BA7A79AULL, 0x2DAF177EE655F392ULL, 
            0xE0EA0F44163C89D9ULL, 0x2B602980D2CB91BAULL, 0x6032AC0E5AD6EC5CULL, 0x452CF91F17F8E5C6ULL, 
            0x89175C2DFB0303D3ULL, 0x65ED494960CF6AD2ULL, 0xA52BBC9E3F18F728ULL, 0x7157C2ACD5D36D44ULL, 
            0xBF7FFC606F624E0CULL, 0x1D89CF0AE53542CAULL, 0xDBADAC4D7ADD18D4ULL, 0xA628805615F07FF7ULL, 
            0x71ADE4F663925A09ULL, 0x424B69CDA2C3C8CCULL, 0xB291C5C9B918C2CDULL, 0xF70160394BFAF8C0ULL
        },
        {
            0xD65BCD9B60AE4BE7ULL, 0xC02B648D4560D821ULL, 0xD7784118A8F40B86ULL, 0x142F279AEE06EDC3ULL, 
            0xDC7B0AD28231A8A2ULL, 0x4DFAF471D8E4CFE2ULL, 0x1F137851833AF1AFULL, 0x69A050A4FD13DDF9ULL, 
            0xA6EB442D2476F712ULL, 0x1A12B631432F48ABULL, 0x5EF3756747CC3E17ULL, 0x3BD02D9BA96A87FCULL, 
            0x9E6653907198400DULL, 0x48D7E073D1009094ULL, 0xA72EA30D57F804C3ULL, 0xAE114EA16F60D911ULL, 
            0x1239722083DBF4EBULL, 0x891CCAA685445315ULL, 0x90B5EB2CC3267DBDULL, 0x15DAEB287C891CF2ULL, 
            0xFCB15A6ABE9D33EEULL, 0x81C45556ADBE8009ULL, 0x4827BE9AACB59184ULL, 0x3273B3B548A05B04ULL, 
            0x833D52E9F395B374ULL, 0xE82DCFF92399EACDULL, 0xAC3CFB1B8013C783ULL, 0xB7E3A1E506B8746DULL, 
            0x2C43F81C6120FE90ULL, 0x4C6990EBBCE6F48DULL, 0x93381B1A77C1146FULL, 0xE7605F963DBFA15BULL
        },
        {
            0xF76CDCAB4FD37867ULL, 0x1BA897D2289E7ECAULL, 0x3B39B2723277C7BDULL, 0xE602D372C622C8A6ULL, 
            0xB29CF68CB94D0FA6ULL, 0x4B4B24FD44EE0AE4ULL, 0x6FE707BDA99CE8B9ULL, 0xCF591365F1E40C9CULL, 
            0xBD03CF676E40C41BULL, 0x64955122B6D2F38BULL, 0x4A6206081417860BULL, 0x334FD127028C5D32ULL, 
            0x2D70128F0AFA5BF7ULL, 0xF7021337A28C1E30ULL, 0xE15A2BBD3C216D4BULL, 0x2804415D9FB5653EULL, 
            0x5E718680DFB505CCULL, 0x709696E29945BDACULL, 0x26E46A8A98AF895AULL, 0xD300971EAD18F24AULL, 
            0x894F1B98684E183EULL, 0xF4080F3C484C19FBULL, 0xFF3F9F5B17ACCC4BULL, 0xED3E99DF06971C5DULL, 
            0x185CC1DEE98B70A6ULL, 0x82AD252CF3714E3EULL, 0x3A060710BC81ED28ULL, 0x1BAAD41C216825C3ULL, 
            0x0002DD2FCFA16CD2ULL, 0x9F1A93C5D2212D16ULL, 0x75F87539C8E3AF39ULL, 0x23B33F0F843D62DAULL
        },
        {
            0x1562031A9C0A28A5ULL, 0xBB57B3581529417FULL, 0x4702A64503AD0F03ULL, 0x4965B1368B1ED474ULL, 
            0xE643FBC31BACE5FCULL, 0x2CB1FC1D28EBFD82ULL, 0x78D94A64B04DBD9FULL, 0x3A91A5AB3E681268ULL, 
            0x8576FA6F7D95330FULL, 0x0F7326709BFA19F4ULL, 0xE0EB974D0FF5CF01ULL, 0x91DCE8779094D17FULL, 
            0x2BE874C45FE28C32ULL, 0xF1A8885B89AE39D7ULL, 0x3B3D24F8063DFDA8ULL, 0x69AF4E1143AF062AULL, 
            0x6DD1630A365D0134ULL, 0x25C6B4A90D1AB553ULL, 0xA9645CB1D928D092ULL, 0xB51CCE66EC1080FDULL, 
            0xEBEACA50664FCDC3ULL, 0x2B092DB5AC5B29DFULL, 0xAAF27320F9F0E0CAULL, 0xEA2DAE3BA6D6B388ULL, 
            0xED89C3908D720E5AULL, 0x28FAC19B3560BC5AULL, 0x1A70A1D147AB53CDULL, 0xB8EFB85408D76F90ULL, 
            0x5787505E593573A8ULL, 0x57204573CFBD645AULL, 0xE0A826582F75F0BAULL, 0x0FEFE4A69E1320E7ULL
        },
        {
            0xCBD6B6FC8EA459A3ULL, 0x4D91ADCFBA124D96ULL, 0x46B0C11A9187F456ULL, 0x42CA00DE8C27A41CULL, 
            0x04DDCCE9A4F9333DULL, 0x7DE00DCFED644B64ULL, 0xBB20B41E69C236F5ULL, 0x5936EAC9200453A7ULL, 
            0xFE983CC5B2842693ULL, 0xAB017882CD770B94ULL, 0x016EE54FF9F66370ULL, 0x4A55C5FDB5117F1FULL, 
            0x702E29203C8AE5D8ULL, 0x2E6B34386484D808ULL, 0xDAF246B66DCA0E59ULL, 0xD1027ED5B4249F0BULL, 
            0xE79619AA3A187E58ULL, 0x10754E4040428570ULL, 0x1F65F5C8BECEC013ULL, 0x689AD06100024327ULL, 
            0x9AB47F14DC87B8F9ULL, 0x206038B9F1DC6EEAULL, 0xEAB0846B045694FAULL, 0xF56A237200B6F727ULL, 
            0x4807D552622E4F19ULL, 0xD2BE97FE7424ADAFULL, 0xBE5519E425641D93ULL, 0x23C7814B2A30C1ADULL, 
            0x2D42E9FA7C52D169ULL, 0x8057ACFF1AA137D5ULL, 0x541DC22B4B1EB12EULL, 0x8D4F3C75DDF953A1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseBConstants = {
    0x7B3E18E6BA7B02F6ULL,
    0x760EB91A117C0992ULL,
    0x0B7FA220D5F6E070ULL,
    0x7B3E18E6BA7B02F6ULL,
    0x760EB91A117C0992ULL,
    0x0B7FA220D5F6E070ULL,
    0xF2D0EA23DDD00854ULL,
    0x5C925DB7C910014EULL,
    0x8D,
    0xA4,
    0x18,
    0x60,
    0xC1,
    0x27,
    0x7C,
    0x44
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseCSalts = {
    {
        {
            0x76E970F4D4F2A191ULL, 0xAFF06EDDD25DD4F5ULL, 0x5E928B6A7F8F48F8ULL, 0xD643DF1EE008E712ULL, 
            0x80C9DA90F0B274B6ULL, 0xFAB1D75EF464C0AEULL, 0x82DC959E0EA446E1ULL, 0x3DA49B6C6BED78AAULL, 
            0x781662683A34C63DULL, 0xDC3EF789672BACC4ULL, 0x55A15CA456D530C8ULL, 0x3C14C047F39F3292ULL, 
            0x1ED9FD129AE1B56FULL, 0x4DDCD721260572B5ULL, 0x5A5682191CB7FB30ULL, 0x8ED9686BB5713CF7ULL, 
            0x7777DA02132E9433ULL, 0xAF8E488B6653E196ULL, 0xFE20AAB7D0F6BEFCULL, 0xC2E2344746DAE07CULL, 
            0xAEB1CF6CE7C77874ULL, 0x18B4BDAA13682101ULL, 0x342D282BCB055D0AULL, 0x14422EDE19D26D5FULL, 
            0x96BED04AD7EEF31DULL, 0xA96ED2A1C60B5932ULL, 0x637BA3EADABA0C06ULL, 0x1890CDF5737F21FAULL, 
            0x25925EF8A19CF103ULL, 0xA1C4603725E09190ULL, 0xC9BCB196B9DAD55BULL, 0x1E8D1B23551739B8ULL
        },
        {
            0x8AA5636267069676ULL, 0x69E3E14106354628ULL, 0x0238E2C45F6817B4ULL, 0x047A3FE8A24BF2B2ULL, 
            0xF063EF626919F755ULL, 0x5BBB889B7A44B6ACULL, 0x42AA09652AA5D7C4ULL, 0x35995B58906999BCULL, 
            0xC4FD2BF4BE1A2B03ULL, 0x15959F9C4945D8D3ULL, 0x6804EB73C3DA5EEFULL, 0x881B8C59F981B65CULL, 
            0x75E99F4C855070A7ULL, 0x30F0B998425BBBCFULL, 0xC63852527D12309AULL, 0xDC98DD797957955FULL, 
            0x74F3138A0E74291AULL, 0x0ADFFC562BDE9367ULL, 0xDC40E3C45599B1C7ULL, 0x7ED58758F2677373ULL, 
            0x3D73A24F25110363ULL, 0x89CEDE8732022D65ULL, 0xA29C9089E76F23EEULL, 0x97D37CF7E9B6AFE8ULL, 
            0x60F40CEA8D41DB09ULL, 0xBB99DFA0F7EDEA4BULL, 0x3217606F87ED93BEULL, 0xE50D528B58E45083ULL, 
            0x4C9B588276A57E27ULL, 0xF5653A3F434C8CE1ULL, 0xEC62F7525ECAF1ECULL, 0xF6A9DB011A28A88AULL
        },
        {
            0xF4B5C59558611AB4ULL, 0x34E52A026715D0AAULL, 0x06697C23CE03838EULL, 0xBD68F911076DCE37ULL, 
            0x654A5C0D23FD0CCDULL, 0xE191311567184920ULL, 0xE4EB92E6E61B2C13ULL, 0x004D3E28127AA355ULL, 
            0xA599A6932128DEFAULL, 0x1F49E587B0739A8BULL, 0x5F60CF727CD86059ULL, 0xF01D49B1B468557AULL, 
            0x72D16FFF9EA0E2A5ULL, 0xD6C02B84D89CABD2ULL, 0x37348D28EF624D53ULL, 0xD5C9113049FD9B77ULL, 
            0xCFF664A09300512FULL, 0xC6DBCD3DD7A6A6E1ULL, 0x2C9F38B2305509CEULL, 0xC1A8D63CBC2DCBCEULL, 
            0x7BCFD8516D8A202AULL, 0x45E8830AC3433F05ULL, 0x4BE20EE05802D5E5ULL, 0xCC70300AFC0ADC75ULL, 
            0xF6E2B96AB7F8C65AULL, 0x0465B56A6AE46314ULL, 0x0EF40C491DF9A9CEULL, 0x2C37BD6BAF670B31ULL, 
            0xCA6876D7EB59421DULL, 0xC2C440C79FB57F50ULL, 0xC6A0528C8E028959ULL, 0x7EFC05818553E960ULL
        },
        {
            0x4E04D9D93E3D3187ULL, 0xC5D857114E7825FBULL, 0x31C4104269C84F99ULL, 0xE7F3ED7C378CDDADULL, 
            0xE5D92E58C7736B34ULL, 0x29232B82339D8C0AULL, 0xDDB38082AB9282DBULL, 0xC22B7A2BB2627CB0ULL, 
            0x14F22F9D2A28DE39ULL, 0x6966F93EC5FDDF84ULL, 0x54D1260D33040E5FULL, 0x672774C443092295ULL, 
            0xFA5870588AE5D09CULL, 0xC82B6079D9EAB348ULL, 0x35CF99A83D81772EULL, 0xCB7386BA523EB251ULL, 
            0xF9B14513C6895D04ULL, 0x1C937367A7322F2FULL, 0x037A7478824542AAULL, 0x770F91EEBEBBE3B3ULL, 
            0x57A50BF34F798FAFULL, 0xE402B17069726137ULL, 0x3A17F57A3FE22F0BULL, 0x713D1D10D0FB35E1ULL, 
            0x4D9FA1AF0E9C7392ULL, 0x7EA7D1E727079388ULL, 0xAF0538DEB541569CULL, 0x7C49775132752FA7ULL, 
            0x08BB77E5A4A28D8FULL, 0x7BF2B4FDA32457F0ULL, 0x25E6503DF28CD418ULL, 0x9CC7E3DE92619C2DULL
        },
        {
            0x1370FFBF633FD318ULL, 0x273DF3879CB00CFFULL, 0x171AAB1E5FCBA3ACULL, 0x35B8521EE4CDADB3ULL, 
            0x1CE6D835CFC8AF59ULL, 0x970E262FBD042686ULL, 0xE47ECBE9BD348104ULL, 0x8ABD04FAFF8F9558ULL, 
            0xEC34BA246AB02ADCULL, 0x68F55EBD3BBC4CD1ULL, 0xC0DE7A60EC7AFD8AULL, 0x8B014687A57E4E5EULL, 
            0x78C13C5867EC0B95ULL, 0x5FAAFF78E9B0968DULL, 0xE0C420E91822D690ULL, 0x1E1E01203B1C5EDAULL, 
            0xD83A6D52AAC8FDC9ULL, 0x6E62A5B46F46580EULL, 0xFEF17EFC39EBDE86ULL, 0xD97B58D91B7421BAULL, 
            0x930CC807220E28CAULL, 0x129AEB124D3BAA7CULL, 0x838904AB8C521944ULL, 0xFA661B96DC258937ULL, 
            0x05EC8A5CDD26BC24ULL, 0x57ED0AD4B5234B48ULL, 0x2D416E5B1ED46E70ULL, 0x88B18B2A46BBF709ULL, 
            0xC0EDC0A64CEC8C7DULL, 0xF3B30BE2B193E947ULL, 0x6BD21DFA1C84A22EULL, 0x1D2745B6C036D728ULL
        },
        {
            0x4536005000B77BBEULL, 0x4504DC50B71C25E8ULL, 0x9A9C927E0DAE205FULL, 0x2A8354A51CC8495DULL, 
            0xFB3D9CDB7891DE38ULL, 0x338FD61CC529832EULL, 0x8DB85051086C65EAULL, 0x304B27ACD60D8F9EULL, 
            0x21328E203BA1F64EULL, 0x80F854EFFB9E3C77ULL, 0xB4A85F5AEE1AD516ULL, 0x98FD3F4A2311164FULL, 
            0x48566EE12CFDD90FULL, 0x0133BDF45BFDEB3CULL, 0x6B96E3BE852E779CULL, 0x84E717E7F01B4C70ULL, 
            0x8FC1BF4E1271FA64ULL, 0x7B0091991B0BB1B6ULL, 0x7631D9C60E41792EULL, 0xAADDA4A7F9712269ULL, 
            0x9CB981324F9DC220ULL, 0xC60BB4812F0A045FULL, 0xC54BA632C76E1ED9ULL, 0x468042313116760EULL, 
            0x78A0039BD3560D72ULL, 0x677A2F08B0F2CE32ULL, 0x11DAB92380A80662ULL, 0x2432417343A42CA6ULL, 
            0xB6CB3205F2C16AF9ULL, 0xBB16D67855C978A0ULL, 0x90C5FE7896178738ULL, 0x90CFF105F4CC62E2ULL
        }
    },
    {
        {
            0x65D5C60F40AECACDULL, 0xA7F92DD60F39D658ULL, 0xC527BE802F2CE85FULL, 0xCDA9F5C68E3D6390ULL, 
            0xA72933628B8D2C88ULL, 0x0AB4843E0E7B1B30ULL, 0xD79D79A73FBC0BE8ULL, 0x6090F517D0D4F389ULL, 
            0xEC748E63BF135217ULL, 0xB37E567E377A78DDULL, 0x7017B79CE939E185ULL, 0x2D4472C17F4AE802ULL, 
            0x0567CC1F821A0C26ULL, 0xA1DE1D382CED5B18ULL, 0xA58452F3F816124CULL, 0x5F9BBE03C424F6DDULL, 
            0xD020C4D4315CECF7ULL, 0xEFB0A58F3DF3BB87ULL, 0xA51CEEAA1CAB31D2ULL, 0x7EC656C76B666A34ULL, 
            0xE5C2D3C451751B23ULL, 0x0E69921601F2E07CULL, 0xF7F865BF0A24ABACULL, 0xA81155BA89D16A7BULL, 
            0x34005F01524A32F8ULL, 0x1FC97650DBFDDE62ULL, 0x0E891CA2FC623818ULL, 0xA8534595B8CEFE63ULL, 
            0xD14F4BEB398D7849ULL, 0xACCA8993159D3ECCULL, 0x1549CD73502A50CCULL, 0x30E110B829C19674ULL
        },
        {
            0xC2EEBC73C9B850A1ULL, 0xA64F7070276F3EC8ULL, 0x6A618A2AB28CB76BULL, 0xD527CD40E93BB4C9ULL, 
            0xBCF0E2D5FDC78230ULL, 0x3B05B8B37B45498DULL, 0xF829F1BB79E15CE2ULL, 0x98A988A261583075ULL, 
            0x7E44CABBFEC398FCULL, 0x8D99FB4199CE80C9ULL, 0xE790975034393A7CULL, 0x4893AA8BCEC0E68AULL, 
            0xD40CF208E5F25E40ULL, 0x32C404FAA941F1CBULL, 0x5B9C573A69E48A3DULL, 0xE3DC671A2DBCEF71ULL, 
            0x3001272E4D85E9D3ULL, 0xED077DE097EC23A9ULL, 0x96C4B1B93D804CC6ULL, 0xC26A2F381384FE6EULL, 
            0xA5E4292C32780254ULL, 0x5A2895B07872A711ULL, 0x26DFF77AF3F2FCAAULL, 0xBE44D29896C56ED6ULL, 
            0x0E5E19C9DABF5DE9ULL, 0xDECC3BC7FB3D0DDAULL, 0x1C8B1DF805978B1AULL, 0xC7D4315C71D460CFULL, 
            0xA6CB5EC9B8D621D4ULL, 0x86393157C6CD77BDULL, 0xB705189797D1D42CULL, 0xDBF118BBA4A36942ULL
        },
        {
            0xF35D92E6D6B33DDDULL, 0xE384BA0F9DB196C1ULL, 0x88EC37192EDFF405ULL, 0xF5800B4909EFB223ULL, 
            0x2930C4191B729E93ULL, 0x794DEE7CBC937795ULL, 0xD4FF20A3BDB9EC6DULL, 0xBD2DD418A76D2DD4ULL, 
            0x56B775D4996E078CULL, 0xA7229074B0C51965ULL, 0x4A2B79E38EEA5489ULL, 0xBB7C0A3EE2F45ABFULL, 
            0x8F00A181B8A8A4E6ULL, 0x8BCE4D5696A1B55BULL, 0xD9088995F74B632EULL, 0x637AEA09CBF825F4ULL, 
            0x4098BA6237B71083ULL, 0xA4A27316386A284FULL, 0x05939EB0A01E139CULL, 0xA6FE03122AFA4B6EULL, 
            0x5C499A25EFF0E967ULL, 0xD9CA72537CC2BB14ULL, 0xDF0434B2C9E63B37ULL, 0x7BC9FBDE483206E0ULL, 
            0x825A3AB849507A79ULL, 0x1D57663875EB8B17ULL, 0xF73F881FDF139BB2ULL, 0xCD3C9DD572FFE3DBULL, 
            0xA484514C2F84CBE1ULL, 0xADABE8366A991D53ULL, 0xA28F9D5978013370ULL, 0x4EF42BA4C9CC73F5ULL
        },
        {
            0x5989ECFCE77D584CULL, 0xEC38C79DAAC45970ULL, 0x8B95BBD67B7C5510ULL, 0x55D8C553F39B4E49ULL, 
            0x9E1E691D52FB2A7AULL, 0xBCA92C04599E0E4DULL, 0x3F18CD8DAE6BFA7CULL, 0x599DD59E3DC509FAULL, 
            0x8F38AE8908C19BE1ULL, 0xEFB5460919D29FD9ULL, 0x9CA230C9FBCB42FFULL, 0x4AF5B32DD9EC4C98ULL, 
            0xE93E8B7AE59C4546ULL, 0x10B75D2DC947B2A3ULL, 0x3355F521185B3F7DULL, 0x6D49FD56FDE650EEULL, 
            0xD17891161A53DB78ULL, 0x324E630B446C06C4ULL, 0x38BC2C179784A618ULL, 0xB912AA8386FF017DULL, 
            0x5CCC606034A8475CULL, 0x8852F90A1AF97B07ULL, 0x3F5B9A9515CECA22ULL, 0x3506AEDD934350D5ULL, 
            0x5D84229CA907B0B3ULL, 0x183488B867E022FFULL, 0xB411879FF2B89721ULL, 0xF0D937A06A5C55DEULL, 
            0x4DF370538D5BE1DEULL, 0x7BD83EE6F9817578ULL, 0x0CD2DAE530E7C459ULL, 0x9607D27E3BC92ACBULL
        },
        {
            0x3BAC87A68DE630B3ULL, 0x57E1B594BD7B51A2ULL, 0xE52B9C529FEF5374ULL, 0xF24BB67CA47FC8CAULL, 
            0x6D6A7FE8A2A61D08ULL, 0x97F9AA98462D5DE7ULL, 0xABDC0CA0007D3A22ULL, 0x46E36315DCD11F79ULL, 
            0x6CCDFB2CABC22BF0ULL, 0x1C6CAD9429580498ULL, 0xB446CD0108261238ULL, 0x1E5846B6226939A0ULL, 
            0x472A40C657324A6DULL, 0x78355EF30F7972E9ULL, 0xE3A907B4DB7FE403ULL, 0xC40BF65D1EC9B93EULL, 
            0xC8B4389833EFB12BULL, 0x64368D481BFC1A00ULL, 0x9A8D07DBE5A83E4EULL, 0x0C7EECDA6C6DBF53ULL, 
            0x7C60868EE8A04B3EULL, 0x8FC5F99F091E490DULL, 0x3902744BBA403C20ULL, 0x97C056E20197A2BCULL, 
            0xDF50DCF8FC26BB73ULL, 0x7D626E451E8FC91AULL, 0x24179A52BDBFC591ULL, 0x26E74AE8945BFE5FULL, 
            0xAD663103C19F6C08ULL, 0x50E0E8419FE821E8ULL, 0xF312AF9D5272DE04ULL, 0xDE50EBD8FE93E2DCULL
        },
        {
            0xE4284D645F420C9DULL, 0xD9E27E4BB938DE70ULL, 0xB6C5809C91104BA5ULL, 0x8A013125FB4D5828ULL, 
            0x4303FFDDE05CC145ULL, 0xD8EFBCD3D5D30DDBULL, 0xD94DF7866E84C9FCULL, 0xACAAFE07F9387A47ULL, 
            0xB27FFFA4B65C5898ULL, 0x369A77AC1F9E35C4ULL, 0xF80A54F75BFBBDCCULL, 0x2E4AF6072670D176ULL, 
            0xDF7B464394745D00ULL, 0x4DB8A88CBE890ECCULL, 0x6B07954151534F3DULL, 0xD12966C0350B259DULL, 
            0x6DFEF5210F905F31ULL, 0x79ED66CD9372BF65ULL, 0xB503993E818C58F6ULL, 0x50B4088938DA554FULL, 
            0x64EA322B5153B346ULL, 0xDE4375C890D8D924ULL, 0x9AEE8472E5FEF116ULL, 0x58DA22A5D3ABE4A1ULL, 
            0x0FE4B62750160D4AULL, 0x6E2CA994E1C20EB5ULL, 0x6B1D0D115DCEDDC2ULL, 0x2F526D7D16F71ED9ULL, 
            0x1B8913D18F399B50ULL, 0xED67F5FA835BDFD0ULL, 0xE0EB90DF0CB7FF41ULL, 0x89A0AF6231898290ULL
        }
    },
    {
        {
            0x6BB5B262C78F98B7ULL, 0x4CAF516393A87931ULL, 0x7B39679726B2037DULL, 0xD6DCC30CFB6E05F8ULL, 
            0xE126407B7A7F56DFULL, 0x8E5AF2F845A17259ULL, 0xEAB9F8449290363BULL, 0x10A2D4B291A0E72DULL, 
            0x60A7E079B9084E1EULL, 0x8D06B72D73829B81ULL, 0x2339E60843127F07ULL, 0xB30B35EB360C017EULL, 
            0x23AF4AC15E71D6A8ULL, 0x8F23A6CC7A58F01CULL, 0xD97620FA02597FCBULL, 0x457C6061C0373F74ULL, 
            0x8846781A447B916BULL, 0x4344B8870B9CBFF3ULL, 0x4546FD7CAF8A4F76ULL, 0x473EA7834C4CBF97ULL, 
            0x3AA4F2DDFD781F62ULL, 0x6C78B59F07107A8CULL, 0xEBE86227B31A21AEULL, 0x989DDD1148FA3161ULL, 
            0xD6B51BF46480A693ULL, 0xB87952A07D603B11ULL, 0x2C74804C95A83FA9ULL, 0x9E0A398BD4689A1BULL, 
            0x32C64E6E9BC12FA5ULL, 0x023C31C2649BFA6FULL, 0x47005997A757C1A7ULL, 0x8B6F43ACEFE75C54ULL
        },
        {
            0x23E17DBCD1DD8331ULL, 0xA7F19E919D60BBC3ULL, 0xF13B77C9B04A8135ULL, 0x3437C9486260F7D7ULL, 
            0xAB1CFA6B910F8B09ULL, 0x26C201098DE3BD49ULL, 0xF6AEB0AD43C47105ULL, 0xF6419E7A39235EBCULL, 
            0xD8AC6E81F61339FDULL, 0xBA675CA5077E8DE9ULL, 0x44FD0AB2F06A81B7ULL, 0x23081683FE7D98DFULL, 
            0xD0A024BDF012E02BULL, 0xCAC545AE6B3AC858ULL, 0xD62EFF7B90446D7BULL, 0xDC9404DE63E0A5E1ULL, 
            0x2B3527D885C4B7DAULL, 0x7D6A52EC95B5654FULL, 0x99F3A396F70B68E5ULL, 0xF8C6F4E153ED78CEULL, 
            0x67EDDF2330C23760ULL, 0x8A55B1BA8AEC5F7FULL, 0xB73084A089215422ULL, 0x466A48517DB40F78ULL, 
            0xDF8DFAA589C3E925ULL, 0x0A7E0FC25CFBAD0EULL, 0xFD040D59A2C03BB4ULL, 0x623EE0D7098C5E3FULL, 
            0x3B94E610107D269EULL, 0xBE55662A5A33DEACULL, 0x5517AECB7374BE12ULL, 0xBF1B7FF035D6DA25ULL
        },
        {
            0x5D7469419DE68E4BULL, 0x1B8F6197A1CD0C32ULL, 0xBB586715E3248416ULL, 0x10B2BC1943F8EE87ULL, 
            0xFAE42ADD4ABD4CC1ULL, 0x5A015D92FAF4C315ULL, 0x54D270307001DDD0ULL, 0xD5EACC84D4884D61ULL, 
            0x9CA2E7805D52F77CULL, 0x2E127D7ACE1915BAULL, 0x30020A2A36B42A88ULL, 0xE6ADFFBFFBA7B5C3ULL, 
            0x983DE7178B529C05ULL, 0x37FA40883F3AABA3ULL, 0xB80B8AAD9DB7FBCBULL, 0x0D4868371C437624ULL, 
            0xEEA2A958CDF3EF2BULL, 0x2E5C5217516E867AULL, 0x582307ADF7DD59EDULL, 0x819D27B30D133DCFULL, 
            0x262D237987EBD4D7ULL, 0x74E2239CE858684EULL, 0xFBDD2DD9C9B0F4A5ULL, 0x82EC4A827921DBD4ULL, 
            0xAE0B322855E0BF81ULL, 0xE5539C8362C11ADAULL, 0x93792BFB96FF8E65ULL, 0x9DF41D269A24B17AULL, 
            0x099A87AB4978755CULL, 0x14F9DD91D20B54DEULL, 0xA8417F0BBA355CE6ULL, 0x652C26741300EBD4ULL
        },
        {
            0xEC87D28F542AD596ULL, 0xF6BB140903405632ULL, 0xFFA29A1F41867694ULL, 0x39AC26D6A1095830ULL, 
            0xC9B44A3354D9B730ULL, 0x203F041C63C49EABULL, 0x2C90CCDC61B657C6ULL, 0x4061F3CB8621ECC1ULL, 
            0x49BE431255DAE6EFULL, 0x42892EDF23142BC6ULL, 0xEA97406469871D46ULL, 0x06C01D00EE7501A1ULL, 
            0x2D9ED0B49AB846B5ULL, 0xB0E6009B12B5AC84ULL, 0x782D325A11D3F52AULL, 0x76C1A199518D0FC7ULL, 
            0xFB276C522848867EULL, 0x7B270300B1DB5440ULL, 0x9ECD84D7CF6F2CB9ULL, 0x2B3FD295784F0FC1ULL, 
            0xC5FB66449FD96543ULL, 0xB05C6005C55BF780ULL, 0xF67FB190B3E1CA7AULL, 0xFD88EAC38F49D213ULL, 
            0xA1A43F30FBD70250ULL, 0xC075C04BE13F33A8ULL, 0xF9CF43EE4F138199ULL, 0xA6EFBCAF7CFDCA27ULL, 
            0x55B9000C94B4074BULL, 0x55F8C87C166C157FULL, 0x9BFA7C5018494EF2ULL, 0x5B4430841BF06E7DULL
        },
        {
            0x1BDEAD0F4A9806BFULL, 0xF241F4A8B1E71997ULL, 0x48F50EA10FBAC2D2ULL, 0x18EB5CD07B05448AULL, 
            0x125E1A7FBE72AEDCULL, 0x62BDD41E572D4AA3ULL, 0xEA49EB3A35C29F55ULL, 0x427F5996194150CDULL, 
            0x24A282175DEF2E7AULL, 0xC7BF51064F4638E7ULL, 0xAE60FF763D9B018FULL, 0xC798E38019375375ULL, 
            0xA854F95332A310E8ULL, 0x321F635494C4253AULL, 0x57752E4FF3D9E036ULL, 0x22AC47A99313EA14ULL, 
            0xC036966233685643ULL, 0x2B3879E4A82D6DEDULL, 0x51F64AE5474D68DAULL, 0x3FF5CAF0CC828307ULL, 
            0x7CDF8BF13F6C569BULL, 0x8C87EC1CDF5A7538ULL, 0xFA2B885603D18A39ULL, 0x25D4CB61EDAE51DDULL, 
            0x676504B4CCF64F3AULL, 0x3A8FDEDE4534723DULL, 0xCF3F008DE0CC42B9ULL, 0x048F6C057112AA97ULL, 
            0x3EC829FA4C7AF338ULL, 0x5F0CA3195D4010A8ULL, 0x7F81CA7AC11D7CB9ULL, 0xBEC07CADAB0802A0ULL
        },
        {
            0x266FD52F36AF4EC7ULL, 0xC36AD6C059CB843FULL, 0x808501716ACB9ACFULL, 0xE6EFD9C07FE4D047ULL, 
            0x2EF176000F0F93F6ULL, 0xF6394C6F1450CF85ULL, 0xD5FC53C08BD9E637ULL, 0x5DC7FD50937E3571ULL, 
            0xC37779CBABCF7BD1ULL, 0xB0444777C4736A47ULL, 0x05749D34711C7D2EULL, 0xFDB0196711C46E8AULL, 
            0x42FEF2F0D27DFEDCULL, 0xB95A177515E9D39AULL, 0x72589F9722AE09F9ULL, 0x23AC3EF2F500C530ULL, 
            0x12DF17639CAF69B0ULL, 0xB248CDE3908FA36BULL, 0x61D0D06A3D63612BULL, 0x601916057DBFB807ULL, 
            0x671F659B8C0828A6ULL, 0xC8FC47E3E4FAD3FBULL, 0xDAE34E56ADD35911ULL, 0xDCBEF2DB5ACA6A5FULL, 
            0x8523BE6701FD8C17ULL, 0x0021FD0CF318693FULL, 0x83569EEA69231C98ULL, 0xD475DC287C66FE13ULL, 
            0x897E36A588BE5AFDULL, 0xA28E32EA302059BFULL, 0xDB449741154A5DC6ULL, 0x2FACE8E893BC86A8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseCConstants = {
    0xD088C31B36A4A03AULL,
    0x03E06DE6C0440F1EULL,
    0x3C4DF8F6685DC5E2ULL,
    0xD088C31B36A4A03AULL,
    0x03E06DE6C0440F1EULL,
    0x3C4DF8F6685DC5E2ULL,
    0xDABA4D58E39C6142ULL,
    0x746F12C77293B239ULL,
    0x20,
    0xA5,
    0x8A,
    0x96,
    0xDD,
    0xD6,
    0x8A,
    0xEF
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseDSalts = {
    {
        {
            0xA992A9EA40FA7B80ULL, 0x32276CE591E62D3EULL, 0x22EED123F90CF8A1ULL, 0x1409609C412ED981ULL, 
            0x2A18819F81B70DDAULL, 0x4E1E5B1C266502A1ULL, 0x5919DDAC4C5E168EULL, 0x417668ED6A5B54FEULL, 
            0x7D4F3C0F904B4140ULL, 0x4CB354BF5C2FCA6CULL, 0x09E9C1A4DE3CFD72ULL, 0xD12C55E6659750B0ULL, 
            0x25A5A41CE881EA1AULL, 0x79CD53B90FE95259ULL, 0xF4AB6DF94B20852AULL, 0x9C9053CAE692312EULL, 
            0xC2C51CE969471704ULL, 0x19E3F16A19560F20ULL, 0xB6103AFF9CFF02F4ULL, 0x1FD13125AC4C3266ULL, 
            0x37B81A096FED9449ULL, 0xB2862B166BDD8539ULL, 0xC20C8676921966F8ULL, 0x85D5223E33194E6FULL, 
            0x1936416979F22754ULL, 0x28E72746300C2DBEULL, 0xB6024B1B3A64079CULL, 0xB1E6B76DC50ACF6FULL, 
            0x7ED49341873D92A4ULL, 0x4C6C1DA4D3AF0272ULL, 0xADC008FDC6982270ULL, 0xC67D1719CD86AD8AULL
        },
        {
            0xB586F3CA24382877ULL, 0x77FCF7C5AEA17858ULL, 0x2724A5DA32173FABULL, 0x54FCDF4202B9F2D7ULL, 
            0x442E9134B6D316B5ULL, 0x6563A212E3B8AB0FULL, 0xAED542E5FDEA0F2CULL, 0x0354979CB9FBED70ULL, 
            0x76D58D399F101F10ULL, 0x5A80D4848EEA0A62ULL, 0xA3646E0162E74522ULL, 0x027BA4B889436B71ULL, 
            0x8A45A98F545B3781ULL, 0x619AEC7B11AA9F08ULL, 0xEC466848EE300253ULL, 0x29BA352300CE5E56ULL, 
            0x3ACCC39F5526766FULL, 0x8EDD48777B805398ULL, 0x7447EC8687B308E9ULL, 0xFD75819C9BCAC319ULL, 
            0x48C73C95EDC2E008ULL, 0x70A1D4FE05FDE975ULL, 0xFFD95E121E88B357ULL, 0x569CF77C8FAC95D0ULL, 
            0x5EA3E64A50A245FAULL, 0x90E50236F2F7A452ULL, 0x81E76FEF63741108ULL, 0x28B0440DF69D8541ULL, 
            0xA8535A1CE2D4CCBBULL, 0xEF83DA59183D1DB0ULL, 0x3EE5C57BBED8E3EEULL, 0x3779D55866CDEF65ULL
        },
        {
            0xA5E7A40208B8103DULL, 0x49161333966E203BULL, 0x82C3290570E5868CULL, 0x0A87006D29026767ULL, 
            0xE13C0BCEBBF4BBD0ULL, 0x9E3C4E46409109ECULL, 0x7E09B2DC9EE07BAEULL, 0xA5ACBB960BBDC61EULL, 
            0x40093C70B7F754BFULL, 0x7ECF92AEA7845D10ULL, 0xF0A6756C29DC5F84ULL, 0x7BB7726970F6AE64ULL, 
            0x6D609C405A36C2FFULL, 0xAF1EE2E7807DE907ULL, 0x607C64C06BF05309ULL, 0xC195310E108EC979ULL, 
            0xDAE8A61396DE2272ULL, 0x5F0012B4A379225DULL, 0xA8FB72B84B59CE63ULL, 0xBB935034AE6F253FULL, 
            0xA5F6D8078C516661ULL, 0xD7D5CF404FA87B98ULL, 0x17850FAA82D94928ULL, 0x6E3E3737932447E4ULL, 
            0x50384FB3C6428920ULL, 0x9FF44843C4A54A40ULL, 0x707A775858B76C71ULL, 0x13B82A774A656A42ULL, 
            0x1521766A0BC078FAULL, 0x9BB9744BAF61E9ADULL, 0x6F915F386C2235E5ULL, 0xACE52F2E24DE40D0ULL
        },
        {
            0xC0EF191BF163699BULL, 0x56AEBDFF16BCF89BULL, 0x60EAB80B2C1F6E9AULL, 0x27ABF852A4CB57BBULL, 
            0xA2347459834E8EF1ULL, 0x8A41A095F432DB0DULL, 0xFD7EDAE9A4C10247ULL, 0xCBB4069559AED232ULL, 
            0x7EE636C06BACC13EULL, 0xF3E1D6F870EFD8ACULL, 0xA01C9FA3B023AD2CULL, 0x48D05FDFE44A68A2ULL, 
            0xDC823995E044A012ULL, 0xC123288842471878ULL, 0x6D264528504D2A55ULL, 0xC942BC3914B7CB44ULL, 
            0x3683BC6A32EE7BAAULL, 0x0413C046F6DE17F4ULL, 0xA6E907FBB227B04FULL, 0xAA8176F5CC9490F6ULL, 
            0xAF40AA06ACFE661EULL, 0x2BA331DAA452BAB9ULL, 0x2B932FC3E2F580C6ULL, 0xA50FC9D0727A8692ULL, 
            0x4B5F430319592C4AULL, 0x0EB4BEF058214B81ULL, 0xDA39A98FED95911CULL, 0xC75E19E8EAFBABCFULL, 
            0x99FAF17541EF393CULL, 0xCE39876CC26E0AD3ULL, 0x4DC90DA4A24388BAULL, 0x9A3916A9CABBA096ULL
        },
        {
            0x79021B140BC42560ULL, 0xBCD9288EE03794DBULL, 0xC3F2A6D7E6DE7B7FULL, 0xC68B2A4BF250E25BULL, 
            0x4E9D67DE640F3993ULL, 0x1B974DAC501979C9ULL, 0xFA32B92C863A9832ULL, 0xE160C068D423389CULL, 
            0x344D0A8C2D2CA507ULL, 0x891394287FD29707ULL, 0xD9DECAD1B23327A0ULL, 0xB44C3F87B8758B3DULL, 
            0x4564015C2FE8FD94ULL, 0xBB9686B4BD51ABFCULL, 0xD07A6A9A63BE802BULL, 0x9C2DF56D285A00EDULL, 
            0xB80FDDB2ECC74346ULL, 0xFBECF6762070C95FULL, 0xE692BFD4F99AFAC1ULL, 0x6486F043F31BD31DULL, 
            0x28B10C4E955C38BFULL, 0x0C5AB2D667E55576ULL, 0xDCC2CEBF12A391D0ULL, 0x8D0A8A77D61F0F23ULL, 
            0x8B95435C529D228BULL, 0x026EA539FAD8594DULL, 0xB1CC917550A24325ULL, 0x3BFEE9FF9C22181EULL, 
            0x9C36F6B7E656808FULL, 0xF3FB7491013C1AF4ULL, 0x449764A7998FC824ULL, 0xF3D6DC60E450F1D5ULL
        },
        {
            0xAEC33CFC93DC60A3ULL, 0x0DDF73ED93B35DDCULL, 0x9C82EB4E21918E43ULL, 0x1F3CE86A26AA347FULL, 
            0x1D25A04DEFCEE8E9ULL, 0x635BB546639B0B9CULL, 0x5C13067580548BFEULL, 0x516AC912CAC5208EULL, 
            0xDA1BD17C55849942ULL, 0xFE4FCA2DDD930429ULL, 0xC680442A359B21CAULL, 0x8C3CD8A88A8DF186ULL, 
            0xA7B3617AB76010CDULL, 0xCD4E251C2B278D38ULL, 0xD7512E5A816A4662ULL, 0x5560FD3097BAEFA3ULL, 
            0x7AB47BDA82282E04ULL, 0x10B2F82C62C44A13ULL, 0xEF9CA91062FD88A3ULL, 0x6AB8E2CE91E0F65EULL, 
            0xCBF3BAA75DA32B36ULL, 0x6E023B80508E006AULL, 0x250DEAE5B1BFE6D5ULL, 0xC1CFBA389B8C8DCDULL, 
            0x3BB7EC62A3A6E2A0ULL, 0x34B48A413129BF0EULL, 0xC3ED88FADBDC5A92ULL, 0xFA80F7DFF92F5A0FULL, 
            0xBA1C3F35C4772C7EULL, 0xDC9B4672727FE436ULL, 0x489866F1D714F42DULL, 0xE68EE6BD8D59DAEEULL
        }
    },
    {
        {
            0x096A363250AB60DDULL, 0x1641EF344655FB72ULL, 0xE694A822C4D9B618ULL, 0x8647E757D594983EULL, 
            0xB277C18FC88F65A3ULL, 0xB8ED92D3A37E26E7ULL, 0x481BD8F6FD32BDE1ULL, 0x9F215567623B92AAULL, 
            0x289DA4DC2655E8C7ULL, 0x2026D88A4F8549F0ULL, 0x2E0EE79F7F895A54ULL, 0xAF264AD3EC29C726ULL, 
            0xB51256E3DE4D3D2FULL, 0x500A3B85FB269458ULL, 0xD592DF84AAEE9538ULL, 0x23B4A89C1CB9C4D4ULL, 
            0xDD47A4F757351840ULL, 0x0A0A3CC74215B4C5ULL, 0xE9AEA8A919DD22D2ULL, 0xAD4B193B215819FFULL, 
            0x1E96970992E1DE93ULL, 0xB70C80CC011F7B5FULL, 0xA3F763149D77DDF4ULL, 0x88D1CBA662C3B6EDULL, 
            0x0F7CA15EF172B949ULL, 0x63AE42947F961863ULL, 0x66C4C38BDF86440AULL, 0xD783B39D38F41BD0ULL, 
            0x9DE8B99CAB04ABAFULL, 0x0EBF5710EE50090EULL, 0xC4517B6B3E46D4EDULL, 0xD9DC6A8AA1F10031ULL
        },
        {
            0xCD2C944CF4E764EAULL, 0x002D1FF4F5E6C1A8ULL, 0x1E1E8E1754CA24A1ULL, 0x3F4FF0765542196DULL, 
            0xDBD52E3E0C51A8D8ULL, 0xE04FF3EBD04B24D8ULL, 0x44EC3E5B90876546ULL, 0x9BAAEC0423187933ULL, 
            0x2134F81FBA12D840ULL, 0x8EF96D0DB2967EFEULL, 0xD0E743B5EC5ACC75ULL, 0x5036F33257EBD2C3ULL, 
            0x4CF0D833D0455333ULL, 0xCD15867105048636ULL, 0x54E5CACC37476A89ULL, 0x37FA516263B87505ULL, 
            0x1F58A7B93217D09FULL, 0x082007C811A51B85ULL, 0x9D042E37EF2B81BCULL, 0x52AE437485E30341ULL, 
            0x91A35AFC05D525CBULL, 0x63C82DC583851B4AULL, 0xC50086137F6528AFULL, 0xED7A68BDEBFD1C08ULL, 
            0xCCB49AF3A40D0A46ULL, 0xB43A16C7A0E465DBULL, 0x5BCE17022EBA3F7CULL, 0xBA013E18D17ED5EEULL, 
            0x5AB43B90EB712689ULL, 0x554691FC36B87AE5ULL, 0xA8EECB8EC8CA5F40ULL, 0x8D177A639B43E653ULL
        },
        {
            0xC4C2DE10136D923BULL, 0x404122FE86140276ULL, 0xAFD76B46D93E0584ULL, 0x66C1323EE30EA1FCULL, 
            0x397F4AA120B77F73ULL, 0xFD7A249095DF8FF2ULL, 0x140407A4C23041AAULL, 0x9A659CAD04082134ULL, 
            0x7DA2F02F3E5D1C8FULL, 0x656AF580D4E312A1ULL, 0xE850DAA4C116779EULL, 0xDA9FD2DAE98DA1B9ULL, 
            0x09DAE83411409DB9ULL, 0xF9328F2306366F2EULL, 0x6E18B734054EC1D3ULL, 0x9793C268BACBF99FULL, 
            0xE065B480C6E3EA3FULL, 0x47006E59736DC33EULL, 0x7D0A9A00323DE056ULL, 0xBAB83F2B6361CB4BULL, 
            0xCEF027CCF74B1CEEULL, 0xA9412943983A291AULL, 0xDC228D58EEE68030ULL, 0xFBB17EF5E4E6F740ULL, 
            0xCE25E9FC17F1C3EAULL, 0x43FD2B770507BC1EULL, 0xCD11C4979454B5CEULL, 0x8B57119192E3DB47ULL, 
            0xE98B5A35C12F9097ULL, 0xB7FF5D4DAE8702EEULL, 0x95A584CF0EC8AD6FULL, 0xF458B9B06CA2C2FEULL
        },
        {
            0x544230C82919153BULL, 0x2AE0D877BE9AC916ULL, 0xADEBB85292770B07ULL, 0x409A4C8129036E9EULL, 
            0xD7805527B00925EAULL, 0x9BD2F5BE0D9332C7ULL, 0x550B4917F606754BULL, 0x153E76F316BE079EULL, 
            0x501AE67F02732B7DULL, 0x23F729D62604B786ULL, 0xBC8411392658E04EULL, 0x2EE6F19BCFABE7C9ULL, 
            0xCA00EDAE4C394240ULL, 0xE1CFA08D514B7F52ULL, 0x5A5C748722D780FDULL, 0xCD76AC45D532CF2AULL, 
            0x18B6BC4F3BBE6E76ULL, 0x37F9DD484B742E61ULL, 0xC275ABEE3A9A126BULL, 0x72612B3876ED59AEULL, 
            0x3AD06C7269A5B61BULL, 0x19F4F720F6F99724ULL, 0xDD16D4A67E4D8448ULL, 0x5240364A02D04C85ULL, 
            0xADA6F99043389E5DULL, 0xA3B1AA09BF78A189ULL, 0x4592EBEFD9B94E44ULL, 0xCD7779466A0D816BULL, 
            0x785EFF47E9A4A113ULL, 0x5415C74E129BCD4CULL, 0x51FC33FB43E31822ULL, 0x48BE6D1CE92266F6ULL
        },
        {
            0xE4048393224277B6ULL, 0x1BC50821001C0857ULL, 0xA7A4C99392EC6BD6ULL, 0x570B792BE47275CEULL, 
            0xE0028B2A42AD3E5FULL, 0x586A294261E852EAULL, 0xE6ECAB3B01C9EEE4ULL, 0x6697E1D227F39968ULL, 
            0xDDA06236951AFCDBULL, 0x827F88BBFFA95A5DULL, 0x62BF539783A70D34ULL, 0x7A845BB7549485B4ULL, 
            0xFBC96D1AD9A724B1ULL, 0xBECF1398C5D352C2ULL, 0xD98412170F681BD4ULL, 0x3A08B20B7667CE8EULL, 
            0x5A60173B92D88047ULL, 0x59ADA1161A7F1634ULL, 0xCACFA98F660C3F9BULL, 0x8CD249759FBF7CAAULL, 
            0xCB0158F7E5634217ULL, 0x5D4AF8573AAF20BCULL, 0x3761DD8568016437ULL, 0x29E30D91CE122F1CULL, 
            0x5A198F9D9180ECD9ULL, 0x11105E5E1D323CFCULL, 0x9D5B4B388E6A7673ULL, 0x20F691F4F073E9ABULL, 
            0x2A9CB6CB2F0625B3ULL, 0xBBE25FD075843950ULL, 0xF2B8346A33534898ULL, 0x739A1601BD087F97ULL
        },
        {
            0x2B52D998E730CE1FULL, 0x9191DCC3CC205ECDULL, 0x29925653EEFD0CD9ULL, 0xF409F4F3946642D1ULL, 
            0xC1A3244A079C05CBULL, 0x7092DB0BE3C4A457ULL, 0x6BA72E69CD59C613ULL, 0x4E162EE1BF9CF8A7ULL, 
            0x2F929B095681B58CULL, 0x188729F83F0EE57AULL, 0x82314F9D59294D76ULL, 0xDC27AF9F02BCF581ULL, 
            0x7F84017832771D54ULL, 0xBFA7F16A709C470AULL, 0xCA02E5F0DF98650EULL, 0xFCD2CE8A86D1910CULL, 
            0x19A5548F899D24AFULL, 0x02F881D93C54B226ULL, 0x90B95FFC4D4B360EULL, 0xFF071B0ADC4974C0ULL, 
            0xD16F6E7E834B9A9CULL, 0x9187E7276D950BC6ULL, 0xDD7872203B6B0805ULL, 0xBA2A4AA53AA5ED5CULL, 
            0xA380716224E5B34BULL, 0x313BA38105CE9857ULL, 0x959F229B53952AB8ULL, 0xC63750EECF544F03ULL, 
            0x4D6C982A3C9DCE91ULL, 0x9F095BD0935D4504ULL, 0x375C362A683C65F0ULL, 0xD953D7BA01400F6EULL
        }
    },
    {
        {
            0x820CDF73D3EB4FB6ULL, 0x44E8A8E81A48D631ULL, 0x32A5A2AC2840D725ULL, 0x175C2FF013BDDF9AULL, 
            0x1945F8524AE5D898ULL, 0x98F72BAC537E3CE6ULL, 0x7437FB5DC34DFF50ULL, 0xCE1C06EE6AA94A58ULL, 
            0x877BCE2FB222D0B3ULL, 0x5FD61EE2551E5844ULL, 0xB641926928BFC845ULL, 0x3D2BC6B2EA618054ULL, 
            0xE6ADBA70A242D53AULL, 0x2B99B94708BAED3FULL, 0xF3EC1613B101007DULL, 0x7C6836E2933E9783ULL, 
            0x169843B0100CF19BULL, 0x81698C6884180173ULL, 0xEECCDBC25CB450E6ULL, 0x7BBBA4B477D8B410ULL, 
            0x1E1F8C36A9B1B7CDULL, 0xA68E7FB1510455A9ULL, 0xED99CEA35D82EED5ULL, 0x05FF7378C26D95B9ULL, 
            0xFDFD85F7E462D9FEULL, 0x9F9DD90B1E3BA740ULL, 0xB50F3BCFB4A1A82DULL, 0x9C3BAC2BBF2468CEULL, 
            0xAE9DF9287E4E3A11ULL, 0x5A3A9464E4A1B91EULL, 0x1B676599D30C308CULL, 0x2077F5F7B69491EBULL
        },
        {
            0x4441F749E53C637DULL, 0xCCC76A409D277D22ULL, 0x219E7E2154B4D0D5ULL, 0x3F12E4E2C0160CC1ULL, 
            0x9FBB5160A0FEFE31ULL, 0xF45A3BFA7EB5B9FFULL, 0xA6FBD9EA2FD6C454ULL, 0xB4495068C077AF5CULL, 
            0xB595D7D80F1328F2ULL, 0x604B6F526F575233ULL, 0x07D32A3372CD8800ULL, 0x849828535D938FB5ULL, 
            0xC8D772551EA3F8DFULL, 0x1EECD7EAEAB6F25FULL, 0x59568A0508645D9FULL, 0xAE273834FFBC69C5ULL, 
            0x0910588CCDC2ED94ULL, 0xB2DE162C256AEFA0ULL, 0x9824CADB5ED39A44ULL, 0x6583F56F290DEBC1ULL, 
            0x8995453B0A3B75DFULL, 0x7B43725013D9A485ULL, 0x4D18BA8ABDA3296BULL, 0x7DBCA0FFAFEF8852ULL, 
            0x9E11E65173B16605ULL, 0xDD6FB052C075023CULL, 0xDDDF480D230C36E4ULL, 0x6E04BFD63FF49FAEULL, 
            0x0A680D0CDF60A892ULL, 0x101EB5C78E48849EULL, 0x703D1D2EC96B18A1ULL, 0x858700A126EEB81CULL
        },
        {
            0x9F322D016780B92FULL, 0xE4B11273E0F2463EULL, 0x3F8DDC96CA0D45A2ULL, 0x46BC4CDB2EA6E5EBULL, 
            0x86771DE91E5F38A0ULL, 0xCFFBF5817C890B1FULL, 0x16DC8EF8B7683228ULL, 0xAD79CAD6483762E1ULL, 
            0xDC1AD39F6E90D00DULL, 0x3D953891DBE676E0ULL, 0x78FCBD84EEF90E0EULL, 0xD6F86A78CA4EB3C3ULL, 
            0xBBBC73D6F8D5AF63ULL, 0xE3933A81156BCE21ULL, 0x0B70DB53B32AD4C0ULL, 0x61636F06FB230EA3ULL, 
            0xC9006D510BED92FBULL, 0xCA9F37F80A769F0BULL, 0xCDC52454D88795CCULL, 0x86BE2A79E0401FC8ULL, 
            0xCF15B08EDB66DA11ULL, 0x03E160DC77318275ULL, 0x4F800635BA6B6076ULL, 0x7DD6C37FFB050C0DULL, 
            0x64A63D8641FD474CULL, 0x7C285E10B6108E67ULL, 0xAC93616DE1E642A1ULL, 0x99129C5B45C9D0EEULL, 
            0xA85BAB8AB12DA64DULL, 0x52A968604C90806BULL, 0x8B92EEA2456338EFULL, 0xCBB67104830A5F51ULL
        },
        {
            0x817D3961E67C931BULL, 0x434C42B2990C8FE6ULL, 0x8824F9C877C1FD8FULL, 0xB3B82CCF63BC6C05ULL, 
            0x876A8DBE485EC428ULL, 0xA60AA9ED68C66B87ULL, 0x4CC2FC63CFF2A0A7ULL, 0x740ABF2994834B0DULL, 
            0x5275E79F52D5327FULL, 0xD934C5F07416FC42ULL, 0xF9F1E10E23B4C577ULL, 0x1BF21CD9595DC539ULL, 
            0xA3EC3323A7E4926FULL, 0x2FE0A9ED7DED37D6ULL, 0x024C3DEF20028577ULL, 0xC5B3F8745638776AULL, 
            0xAC12C01F26E3145EULL, 0x217673D22CD12B74ULL, 0x40C121A333505340ULL, 0xFEAB29EBC196A7DEULL, 
            0x89E198A366DC98A3ULL, 0xD60DDC8EFFFEA5DDULL, 0xC47636E01A9DFD4AULL, 0x4179A770F6DD31FAULL, 
            0x8EE60774CE3047D7ULL, 0x06B6C24AC979A462ULL, 0x3169F8EB64FA3DF9ULL, 0x42AD0DD658862841ULL, 
            0x8DCFF96700893C3CULL, 0x6407EAADF4138831ULL, 0x42B72E3C742CDF88ULL, 0x0FE2EF1F3896D48EULL
        },
        {
            0x0739B6DEDFB21024ULL, 0xA0E2FCC022F531C7ULL, 0x7B2CF9895632C82AULL, 0x524CBFE244A0EF3FULL, 
            0x5DB0D68FB923DB03ULL, 0x2C315F94DA1C14E2ULL, 0x60AEEB5736E002D3ULL, 0x0F133FF51CBE1B38ULL, 
            0xF2EF092E767837A4ULL, 0x23231D4F7FA4A1BDULL, 0x77A382FCA5D944D8ULL, 0x6C14E0FB06547F8DULL, 
            0xEA94E073C8D27CFBULL, 0xC2BAB0A8B83D8417ULL, 0xE71728BA6ED8CA84ULL, 0x27E9CA1CFA24DB63ULL, 
            0xFD15A5F654A5DDEEULL, 0x6F4AAE7F7F57281BULL, 0x6D87574FE2DC3ACBULL, 0xFEFDFA5705D6E51CULL, 
            0xD54130FF4B97D5CEULL, 0xE8F357FAFEDE3FBEULL, 0x303A0818F98A0CEFULL, 0x86DA0C29C138E6FFULL, 
            0xFBE6DDE59178D4FEULL, 0x2ED7B867246A1AD0ULL, 0xBE3F1EAB340371B2ULL, 0x7BBC5BAD39B16F3AULL, 
            0x76B086FD07C71F38ULL, 0xF49A4C2FA2D35796ULL, 0xA14507F051950AA0ULL, 0x19220A11CC7C1C00ULL
        },
        {
            0xDB0ED3602EB83D23ULL, 0x4D33F837D4C91EF0ULL, 0x4B481508C9B467BFULL, 0xA9CBA1D2A65E77BEULL, 
            0xF8E9DB094BACFB94ULL, 0x453D4BE9FD4392D6ULL, 0x49A072933904C656ULL, 0x28D22A8B8FC7D3B4ULL, 
            0x1ABCE2479847D4A4ULL, 0x70F41764A360A37BULL, 0x3318DF000A47D53FULL, 0x5306343CF5E69C7CULL, 
            0xB22D58595009BA96ULL, 0x464A2FF95A75A00CULL, 0x4485A9956C2F29E7ULL, 0xEABC4FD079388C46ULL, 
            0x3FEF23EA70A57CACULL, 0x51889CC9EB38482CULL, 0x5CF018BFD0930372ULL, 0xC7D7E0FD44EED39CULL, 
            0x583AB214030C70CBULL, 0x35C4D03E30400B6EULL, 0xFD4B76B2345AAE87ULL, 0xDCC5500E3BB14595ULL, 
            0x6A764A3A072AF57BULL, 0x3382CEC1DAC352FDULL, 0x834E8B9CE061276EULL, 0x3C16BC5906827B5FULL, 
            0xB83AACC9B241BAB7ULL, 0xB3C1047D9CB6CEB7ULL, 0x09030065CA12CFCEULL, 0xEAB85A2B6C4A6B0AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseDConstants = {
    0xD2EFD74509280969ULL,
    0x5715DD6370D9022FULL,
    0xE6E0B141D7AEC843ULL,
    0xD2EFD74509280969ULL,
    0x5715DD6370D9022FULL,
    0xE6E0B141D7AEC843ULL,
    0xA23F3BCE9B5A4387ULL,
    0xC7D24124EB0DCC33ULL,
    0x74,
    0xBF,
    0x28,
    0x0E,
    0xB8,
    0x49,
    0xA2,
    0x10
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseESalts = {
    {
        {
            0x138822E09992D490ULL, 0x12CB7F9C13D348AEULL, 0xBC967766147D5283ULL, 0x5DBE107CEA2FD164ULL, 
            0x9216598D8B7B8A56ULL, 0x2F2439C576DA5E82ULL, 0x9E9EA407E002A282ULL, 0x69F17F4B4ED7DBB0ULL, 
            0x67FA8AFF57E48784ULL, 0xF0706A1881A158AEULL, 0x3BAFD945BACFCCFEULL, 0xBA1B90E5F1CFE9A4ULL, 
            0x5B48F10BF3EA29F5ULL, 0xEB7729FF4E93BBDAULL, 0xF9F796F9DC333E2BULL, 0xAD8FCAB649FE67D3ULL, 
            0x5CA9BB9F6FC001C2ULL, 0x16A4F06F52B9C344ULL, 0x5C39A217A3A1F3E0ULL, 0x81837D4B47A5BF4AULL, 
            0xB35193EC74B37E43ULL, 0x020B9A4E1A9EF588ULL, 0xE0AA8506C38E0A87ULL, 0x7E52854F5A1FE87CULL, 
            0x58C604B5C009E25CULL, 0x3DB7121DCAA1CB9FULL, 0x83FBEA0470824D01ULL, 0xB26376D349009F56ULL, 
            0xC5598B4061457978ULL, 0x5F6827F7509EFF49ULL, 0xF0DEC2420AF46572ULL, 0x80DF33278872A8C9ULL
        },
        {
            0x6DEE3CDE68DCBED2ULL, 0x70D8018E99AAEF52ULL, 0x873C7F7E48F1BA73ULL, 0xA21D594B1E15805CULL, 
            0x68F91E5A32940B59ULL, 0x90DE09583078C8E7ULL, 0x14025C387A261383ULL, 0xDA591F1EC68E1731ULL, 
            0x22BCDBE5CDC712F3ULL, 0x33BB0AEBE9410747ULL, 0xF35B03E1EC702F47ULL, 0x3C199A950C6EAE9BULL, 
            0x3389A84B1A4F495AULL, 0x2F320DF815AB29D8ULL, 0xE44CA1B54135397BULL, 0xD5B760FF5479E7EBULL, 
            0x5777CB577FEC711FULL, 0x952C47BCBBDE430FULL, 0xA0943C0842F36DE7ULL, 0x73C35621392B2118ULL, 
            0x67208AE46F35E6E0ULL, 0xDFA01874231D6CD8ULL, 0xC236D5D4C82E4311ULL, 0xF7C802DE0F128926ULL, 
            0x86D190969EF74A98ULL, 0xE071BB1601EC61B2ULL, 0xF5224BB07815D289ULL, 0xC91F7450AD7563DCULL, 
            0x059582ECBF1E2720ULL, 0xB5B58FA01D23C9E9ULL, 0x12444C8AE14A508AULL, 0x8EBF79674ED4B62FULL
        },
        {
            0xE0CB96CDF5DC217DULL, 0xF19AF2B41D00D992ULL, 0x37F572A0847178C9ULL, 0x07BDF77521710ABFULL, 
            0x0BEB8F99F15B6A3BULL, 0xCF1677F4C1775C02ULL, 0xCA4917BECF53F14FULL, 0xEC30BAD1838AA1F4ULL, 
            0xA3EDA42B2E1039BEULL, 0x2569E0C609E53A18ULL, 0xA1E8F48C8E2A992BULL, 0x18AF7DDD92126D0DULL, 
            0x17C5C870A1610754ULL, 0x7771A3DE2390DC6EULL, 0x08D82A720C903EE7ULL, 0xDCACBACD1BC4FB57ULL, 
            0x873BFE524C0AD746ULL, 0xD03FC4096D53B031ULL, 0x2A88C69E3C6A683DULL, 0x00A960AB4AE56449ULL, 
            0x994892721657104DULL, 0x4BA9003CE7A04D9CULL, 0x23FDD8A8F40D2C5BULL, 0xE93A3A03F314091FULL, 
            0xDDC5451F2AF82005ULL, 0xEDCE9C8D78DB0637ULL, 0xF4844D924F8B2DFCULL, 0x29A1C1C5433FD8ADULL, 
            0x67A343E821DDBAFAULL, 0x10EFEBAAECAA6264ULL, 0x6FFDC0E46DD0F956ULL, 0xB64C13B80796431EULL
        },
        {
            0x9E0695910FCD0DB2ULL, 0xD591816D49D4EE9EULL, 0x9D2DE2CF940C5878ULL, 0xA7C18F15494B597BULL, 
            0x688E720C92F3C415ULL, 0x52A3628363FF9C25ULL, 0xA0AC6D9663DD19C0ULL, 0x1D430321459DAF6DULL, 
            0x0EB7D093309D5DADULL, 0x4321E463CDA9EBF4ULL, 0x8104BFC2B9146375ULL, 0x34DD4BF178E7267EULL, 
            0xA8D21E70E210385FULL, 0xA0044BA96FB995FBULL, 0xC7B9851B4FA44063ULL, 0xF41DA90AF918BEB3ULL, 
            0x21027CF1B8FF7310ULL, 0x8826155F5EE690A2ULL, 0x11C7A7491F580D5FULL, 0x939CF30332A04B4DULL, 
            0x814D439F32ECAE28ULL, 0x1F7EA7D9681CCE0AULL, 0x6B34632E54F2C5CCULL, 0x2226A0B34037C9CEULL, 
            0x868684605BE76607ULL, 0x6905EC1321265FDDULL, 0x698E3A3CEEFBF773ULL, 0x73F3D283CE4261B8ULL, 
            0xF838BEC470010816ULL, 0x777106E5EC6E71D2ULL, 0xA90B4C1B80D86782ULL, 0x9B48D08015D1325CULL
        },
        {
            0xDCDEFDCA928C5788ULL, 0xAFFC3E2479AA97F0ULL, 0xE9F6DCC0EEAF161BULL, 0x01385DDD63D95C42ULL, 
            0x65E5B8CEE4C74C96ULL, 0x2B98FDEE45DAB67AULL, 0x4AD227B3891A1011ULL, 0x526DFAC80CA1C3DEULL, 
            0x9587750A04298055ULL, 0x2588323B97F7DFC4ULL, 0x51B79B82CE38E3AAULL, 0x33DC98006BDD999AULL, 
            0x619F109567BAF56AULL, 0x5308C704EDDB7D32ULL, 0xE551ABD72A5C400FULL, 0x529FFC72CD2D6609ULL, 
            0x108CE91848A1105CULL, 0x2A351703E9BF11E7ULL, 0xDC9F5330508BCE16ULL, 0xA8C7ED1A7CB0E7FCULL, 
            0xE7EB6FA77D4516E0ULL, 0x1B31F77C8B54A549ULL, 0xDDB85B1418FB3D1AULL, 0x0F76051623193BDFULL, 
            0xC4B56F87B20A9091ULL, 0x73D3D6CC63DDA80FULL, 0x4AC346276746EF78ULL, 0x965FBCB14A75A144ULL, 
            0x403AAD769F1CDCF1ULL, 0xBE569F2EA9B19EEEULL, 0xE5A30A7AE06C3050ULL, 0x4EED616BB6D7B3E0ULL
        },
        {
            0xDCE3FD80EF0957A3ULL, 0xC977139D7AEDA63AULL, 0x788AEB4BE17B89C3ULL, 0x3DAA41DDBD797EA9ULL, 
            0x978D49FCB0E03718ULL, 0xAD333E6571BF7D3DULL, 0x513A60CADAD35734ULL, 0xC35EEC405BD9FDFEULL, 
            0xB4F3C6B32105DA2BULL, 0x19860ED08D481E5CULL, 0x6E5C22D373BAF2A4ULL, 0x9605D49484C3C438ULL, 
            0x9EE87E8C6FD70E70ULL, 0x584A85EA59C2C681ULL, 0xC518465A3E5CE10EULL, 0xE572A897136F2B91ULL, 
            0x9DEB4B58FA379291ULL, 0xA122CDE86ABD3E08ULL, 0x4EFB1433DB0133B6ULL, 0x79A4D54E326A7E99ULL, 
            0x0DF18F5776FE3367ULL, 0x1EA6A292AE2F8F2EULL, 0x6C4948D3BA20D999ULL, 0x90F2377CAB47CDEAULL, 
            0x3A224ED282FB47BEULL, 0x4F14EE34128FA48DULL, 0x8DF78DD98C65E93AULL, 0x26EABA4E0DE70A62ULL, 
            0x5003334C04CCDBFDULL, 0xB1449DD8405B5D20ULL, 0xBAD16C125B1E194CULL, 0x6FA5139D1478FDB5ULL
        }
    },
    {
        {
            0x8DAFADEF075CD20EULL, 0x4C7C7C52A4CF2657ULL, 0x47F942BAF015D9B5ULL, 0xB70CAB5F193BAE2AULL, 
            0x9666E9A329F27743ULL, 0x1D9F56A1CFB16FCBULL, 0x1ABBBE1F3F7AEA4DULL, 0xB8224DD7C49BC400ULL, 
            0x8E1E059121BEE3A1ULL, 0x056A8499E45842FDULL, 0xDEDC4EB7E3B2FE81ULL, 0x55D1F6F89BC009E3ULL, 
            0x471B13FE9EDE2A7AULL, 0x31BBF6BE8CCE45E5ULL, 0x23877BA4CB5C9BFBULL, 0x4F7829569E7390F1ULL, 
            0xAA5330B35FA51005ULL, 0x668D5C61CCFA3CC6ULL, 0x856727ED4AE4452AULL, 0x4ECDD35E8527B159ULL, 
            0xA094C53281794755ULL, 0x70F1C28E8D35C28FULL, 0xC1DB0D03108C4519ULL, 0x3F6DBFF50F25BFE7ULL, 
            0x43CC9CE6CF2244C0ULL, 0x99592F0B282E7D49ULL, 0xD5819761B73D4AFFULL, 0x7CD4179F2DAB76B4ULL, 
            0x23EB6CB50B80AC0DULL, 0xCEBC7D22BA0A1A22ULL, 0x2FC7617A9D2ECD48ULL, 0x8EC73AF0E7E7DF10ULL
        },
        {
            0x934CD04744B66DD9ULL, 0x83998F9E060A4615ULL, 0x357DF852DC6C6399ULL, 0xE0EFC02A780607ECULL, 
            0xB1385A8F05AED901ULL, 0x16C5744D8562950DULL, 0xE7FC60AD062D6563ULL, 0x606C54FEA16D29F5ULL, 
            0x183BCED75D5A5772ULL, 0xA1093948CD9C3F3DULL, 0xCC1782FCB67BEE7DULL, 0x985878C1C4303CA0ULL, 
            0x254AE43332814DB7ULL, 0x2F39B569664CD77CULL, 0x04198DDEBED00E82ULL, 0xCD2463328D4AE54DULL, 
            0x9ABE5DB35049F1AEULL, 0x1EBCE9EDA4857E42ULL, 0xCB66DB8BEBC1FD0AULL, 0x7E5B713A71CB03BBULL, 
            0x4B4597A5DDF136DEULL, 0xB938C81928FB77D8ULL, 0xC2C7B8E538EB3353ULL, 0x406A562D1CEE1E6CULL, 
            0x5D4D0D4031F34E6DULL, 0xA28B16D2D244E9C0ULL, 0x3650A3276C9D2835ULL, 0x206739A79D98A4D4ULL, 
            0xBC9E0039C5A4121AULL, 0xF9DDD00B6656635EULL, 0x0D2A464EC2D1B718ULL, 0xF03E628962D3315FULL
        },
        {
            0x80BAF0CE9E4B56C8ULL, 0x64425F0307C79F96ULL, 0x863C0A0E878CD0C7ULL, 0xE827BB34E2112DC8ULL, 
            0xCFBDEB0F2FEDEB0FULL, 0x2D48D9FABE92F3BAULL, 0x902002AED42040DCULL, 0xA2735320B785079EULL, 
            0xE02E6EED908E6755ULL, 0xBCDF8A36C30B3DC3ULL, 0x59D2E3573F0191A2ULL, 0xD6E88C82062E71EBULL, 
            0xCE12DDBC59EAE0D1ULL, 0xB62FC674D8CB5127ULL, 0xE29DF6CCCBC420CDULL, 0xCE01073164E1F9D6ULL, 
            0x71833C443DEAE1FDULL, 0x91401D9F92FFC764ULL, 0xA247A735A2D669B7ULL, 0x5E3C50734584701AULL, 
            0x1644B7EF31F66D51ULL, 0xF3B95EAC1FF3D413ULL, 0x3B1934FA6D642C3FULL, 0x819F0D5D4E323103ULL, 
            0x63D5D1C22618015BULL, 0x7B834079B19FC780ULL, 0x0D9323BBD8F9F0A2ULL, 0xC64B3FB741031846ULL, 
            0xCBB4F122625241F0ULL, 0x92813E538070E552ULL, 0xEE1D27BCA27B58CFULL, 0x4D41051EDB50CC32ULL
        },
        {
            0x965270B525297108ULL, 0xADDAF35F6CF9620FULL, 0x62396544D15B444EULL, 0xDAB45C29138AA424ULL, 
            0x832ED983AB68E3B7ULL, 0x9474242DB94DB9A4ULL, 0x5904FA49F606E4DAULL, 0x13E9C82E45CFE9A4ULL, 
            0x1E4CC1307F1D6335ULL, 0xF9C6A90BAE8556C4ULL, 0x3F206A486A62EC81ULL, 0x12878A9750476583ULL, 
            0xD78ADC8C2036C0E6ULL, 0x93B432859AEDBCF7ULL, 0x130F669424F4B02BULL, 0x5E3CCAC122C97805ULL, 
            0x36877D40CD722EDFULL, 0x1383A5A0E8C064D9ULL, 0xB1A4FE034E7B6ADEULL, 0x7E7B0285F0B3946CULL, 
            0x69CCAE9AC1372DE2ULL, 0x7EBADAAD21AE1F0BULL, 0xA25A8492F8F2101AULL, 0xA06E4A23593D1F97ULL, 
            0xDA5FF669E34BB54CULL, 0x8A9325099AD231A8ULL, 0xFFC65AA0A83FC457ULL, 0x235A461699EB4B25ULL, 
            0x5D89068AF6896F7FULL, 0xB3AAA4ECB07CF872ULL, 0x1D00E08F0654DF43ULL, 0x344EAC15F1F4830CULL
        },
        {
            0xA681119DCFA4897CULL, 0x2ACA0D214067258DULL, 0x2EA7CBD948CBC5B1ULL, 0x427D04BDFAE4814BULL, 
            0xB452274ADACFE981ULL, 0xBA06866D65D3D4AAULL, 0x6411F1B4343DD13DULL, 0xB463CB6355EECA98ULL, 
            0x36373ED7B59B6D60ULL, 0x2FE96D5F0AE87CE7ULL, 0x8E9808E55EB31C15ULL, 0xC3B61C2D49BCB6D8ULL, 
            0x312CE4CB8136D53EULL, 0x9E46B64CECF2F70FULL, 0xFB5B5FC58DC1FB42ULL, 0xF170708E59A4CF11ULL, 
            0xDB40135E24D19975ULL, 0x49D31F84C533310FULL, 0x1381D9490D4D137CULL, 0xA0CF10911F82AD4BULL, 
            0x1EC682DEC29521C9ULL, 0x9F58EF85A18D1A8BULL, 0x8E0F51DC31398D6DULL, 0x9093E032D271C307ULL, 
            0x27FEF525B15B6461ULL, 0xB3F301B2E0B67D96ULL, 0x43521F971578C4B2ULL, 0x0B5C863CE06E2CF0ULL, 
            0xE6CF39A4C6BF5AE5ULL, 0xD5B32CE970D3EF6DULL, 0x3C6DFF4936AACEE7ULL, 0x7862480CE660DE7FULL
        },
        {
            0xCD2F53DDC1863F86ULL, 0x3FECE1E16CE36D99ULL, 0x6A8E5D22729EC370ULL, 0x390B8F3CB9898723ULL, 
            0x99D2279DCBEEBD91ULL, 0x0401F4D57791A65AULL, 0x615794F0B157C3AEULL, 0x75F0CEF4B057B5D8ULL, 
            0xB26BFDF8E6E9C889ULL, 0xE374A8A541432AA4ULL, 0xD2FFD73A0A0AAC89ULL, 0x3FECA36C42B6C3E2ULL, 
            0x75E67FFE183AFE5BULL, 0x52CCD0B4105673B6ULL, 0x97067D86D1D31954ULL, 0xEDB7058CBFBF03F6ULL, 
            0xDD623C75DFE1FBC7ULL, 0x53D6A3D649CD4694ULL, 0x7176403A187BE034ULL, 0xFEDA7AF2B78F50BFULL, 
            0xF049635E14A48F8BULL, 0x56ACBD0828DDDB85ULL, 0x119CB03FD8B11415ULL, 0xDFA08DA785672B74ULL, 
            0x4887E17B6DA2EC8DULL, 0x66B2F71805EB8147ULL, 0x6A9B939A56A03504ULL, 0x9D2CC83A37B7E980ULL, 
            0x6400565478A4CEFEULL, 0xDF88D6137F8A96EBULL, 0x0D63F47D51D5B687ULL, 0x77A3473BD83FC324ULL
        }
    },
    {
        {
            0xDC0183112F5146F9ULL, 0xD6AA52334A05E7EEULL, 0x14F268650078FA60ULL, 0xC634AF9C179E8663ULL, 
            0xE574D7854E984DEAULL, 0xC22DA664B7115C1AULL, 0x03FF63E30BE18CC4ULL, 0x3EA039772C3E52F5ULL, 
            0x3F437B54584D6BC3ULL, 0xBECDC01252AD4E18ULL, 0xF574F68D662A59EBULL, 0xDA2762294D9BF9AFULL, 
            0xE8D0B5757400FE66ULL, 0x7633F0C7076B86AAULL, 0xD77CF67B7267D1BCULL, 0xD7C43B98017376F7ULL, 
            0xB47122F37C71AAF4ULL, 0xD0251712A498DBFAULL, 0x1164B7C3CED64165ULL, 0x92681D72581EBC70ULL, 
            0xF38506D3EC3957DDULL, 0xE56FEEEF7EE1F18EULL, 0x0A6D25C551105013ULL, 0xA07AFA96DF77429BULL, 
            0x22C132A62E8823B2ULL, 0x2C609674707AA88FULL, 0x9E6B83E04F341B95ULL, 0x124239168D01B0DEULL, 
            0x93DD1A94AB69BB2AULL, 0x70C2EF2B09D9FDD5ULL, 0x1241A844B5736741ULL, 0xF21E88C66B553323ULL
        },
        {
            0x73C009F7ED674678ULL, 0x711A5389EC5B7E22ULL, 0xCEAE4D2B42ACCC87ULL, 0x0224FBF82AAAEE67ULL, 
            0x20EFBD54D5884EC4ULL, 0x8BE550BD7B5CDEF0ULL, 0x57F17597B9DBA452ULL, 0xA7259D38D562459AULL, 
            0xD977B4AF9CF375AEULL, 0xD3FAE92802C3E379ULL, 0xE0A6BBC4C33F9BFBULL, 0x1F39AA4A4BDD0373ULL, 
            0x34AB79286724F43FULL, 0xC63C7735966FB8C5ULL, 0x2579F4693B563031ULL, 0x8969667B32DF5B84ULL, 
            0x797CCBC9F2C2A086ULL, 0x4CF8FA342D168427ULL, 0x5F11CD47ABCCC18BULL, 0x02977D14CA817E55ULL, 
            0xD9E23039936F0552ULL, 0x2C7D8C02B816FFDDULL, 0x1BB80FC754F69E44ULL, 0x62AA7029BB16E07FULL, 
            0x7DD6F19B0CB4EDDAULL, 0x95F2FBADB5CC850EULL, 0xA9EDE605F3E432E2ULL, 0x30F7FCC5ED33765FULL, 
            0xAD8A85AEAF52FAA4ULL, 0x6343C34D29149E46ULL, 0x80D323773BC4BB51ULL, 0x6EA99CC0E356B27CULL
        },
        {
            0xC63BD6F682E3F1E9ULL, 0x27669B418A0824E4ULL, 0x75CC8A327C1454E4ULL, 0x820CCF4542E5B782ULL, 
            0xE795ED8C761D7F54ULL, 0xD65E5593BD218ECFULL, 0xF941E795502AEC86ULL, 0x106C3C9B45C9A993ULL, 
            0xFE4FAD678C69896BULL, 0x508E369BF8352E50ULL, 0x0350FE0F741499D9ULL, 0x797B87B0D65B56DFULL, 
            0x22C329639B08893AULL, 0x355CBBD970820B82ULL, 0x2D3CC36AD2DAA757ULL, 0x20AAFE242A7F2E36ULL, 
            0xF3945B84FBB7F7DAULL, 0xB18F1F022B39B212ULL, 0x16A0489E7E54FDCCULL, 0x18AF6B12AC65D803ULL, 
            0xB5B58FFF78B9840BULL, 0x398EEAB5618D5671ULL, 0x589A8DE70AA148F0ULL, 0x7A7224E345CAF64FULL, 
            0x720626254B2D9A4AULL, 0x243DB3AF810CD467ULL, 0xBD706EF3160B0BBDULL, 0x0A8819A659ACE1F4ULL, 
            0xF28F6F813A1C55B3ULL, 0x188310FA6DAD3DCCULL, 0x2B6019C6FD3F7F6FULL, 0xC5CDF3D89BF170B7ULL
        },
        {
            0x68D8B735F0A90DBCULL, 0x38C83238F29A02A1ULL, 0xB2B083C542658A98ULL, 0xAB3D52C4FEB87AACULL, 
            0x2813DF2F4750DC2FULL, 0x46E353D0E10F0ED4ULL, 0x8AC13C1D96B343A0ULL, 0x9EFE69E088E13A8DULL, 
            0x1C72014835D292B9ULL, 0xC2CB55D2E9266720ULL, 0xDA0F906C047E473EULL, 0x2F365EFA7857110BULL, 
            0x07BE91DF11FEF9A6ULL, 0x595D3FDB263E939BULL, 0x3110866E9D6CF0BDULL, 0x862EF3636830C20FULL, 
            0x5B47F170215E04B7ULL, 0x3E9DF7CC8C4EEC1AULL, 0xAC07CDDA7ABD9368ULL, 0x11B239D8AED9CCA3ULL, 
            0x55C2538B90ACF680ULL, 0x97E1B46546CFE607ULL, 0x53EC0708E2C237A7ULL, 0x670CCC70F6F9DF33ULL, 
            0x0C6227F6030C063EULL, 0x3C2A0EA9104ED4B0ULL, 0x770E5FA9C6B94EC2ULL, 0x6FEF6969D19FD261ULL, 
            0xFFC6F0747BA37245ULL, 0x5D78EFBCC47DF6BDULL, 0xFCE4ECAD336D9D68ULL, 0xCEC545FD1D6B3EEFULL
        },
        {
            0xDF64523E7DCF6E73ULL, 0xF4B9E84F8F6E3C51ULL, 0x491B17298FF6B72BULL, 0x38699D966A7AA8AAULL, 
            0x998A20E52CA6FCCCULL, 0xDE6A8514C6F300D6ULL, 0xA24C6F8693E95406ULL, 0xF11E28A5670F04CAULL, 
            0x9B1A292E3C4F7A24ULL, 0x077EF7E8287F10C1ULL, 0x62C45BBA3B945884ULL, 0x37D2DED9D9E17CC6ULL, 
            0xDDAEEB15512CEC77ULL, 0xEB2F049FEF044372ULL, 0x1E77DE066F73E2A3ULL, 0x1073FEF1FDBBAEACULL, 
            0xD731929AFD5B2482ULL, 0xAE6FABF879D64045ULL, 0xC9C689241332DFA0ULL, 0x5B9448302A5FF7D6ULL, 
            0x8444F0CDC5FA2467ULL, 0x61F6E7C193AAD2F5ULL, 0x60A4D986F8F45153ULL, 0xF9B94CB18EC7ADB3ULL, 
            0x3EA8C89FD7756D5CULL, 0x618D19D33A0CAA86ULL, 0x7B08524DD9042342ULL, 0x7CD8177A95D9FEC1ULL, 
            0xB37346D3E938F7ADULL, 0xEBBB33214D019D5FULL, 0xA03E8FD7C52F7DB9ULL, 0x8C52D11D6FC6C325ULL
        },
        {
            0xFC4D10FF7CBC6618ULL, 0xE07F082630521EB4ULL, 0x24EBF536398AE3BCULL, 0x7D15FFCBF292C444ULL, 
            0x5075623028AE7EE1ULL, 0x2167FF8F724814A0ULL, 0xF196A51E3EC46DDAULL, 0x8E85B01CD99545F4ULL, 
            0xE7F5135287AF099EULL, 0xD8AA8011929F0D6DULL, 0xFA5C0F114FDB2460ULL, 0x85AB3104A215EF91ULL, 
            0xA9638A321E85B4FAULL, 0x312477231655EB60ULL, 0x9FB6720D89604BBAULL, 0x34B70417256BCF83ULL, 
            0xF05CD406ED59535EULL, 0x4AB447F70771CEA0ULL, 0x46FD11EB5C356E22ULL, 0x0770C4B33E57B510ULL, 
            0x320057738A6AD517ULL, 0x26A4B068FB0FF7A6ULL, 0x255FE284D7E33D93ULL, 0xDDDA3DFDAD3242F2ULL, 
            0x35E9D63FC1F4753AULL, 0xD648C2E79BD6F58EULL, 0x778D44753D7B3C88ULL, 0x01C359B861017096ULL, 
            0x3089BC96DE4A30A6ULL, 0x0973B945E07B909AULL, 0xE8FECA02D0D82676ULL, 0xBCA10B4B30F10892ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseEConstants = {
    0x87DA01D4DCF334C4ULL,
    0xBEFCC7F159B688EDULL,
    0x7E125E99319583EEULL,
    0x87DA01D4DCF334C4ULL,
    0xBEFCC7F159B688EDULL,
    0x7E125E99319583EEULL,
    0xB6DF76640B2B7649ULL,
    0x13832E50F1608728ULL,
    0x91,
    0x7F,
    0xB3,
    0x05,
    0xE5,
    0x2D,
    0x04,
    0xE8
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseFSalts = {
    {
        {
            0x6C1AFCD6142A6C21ULL, 0xC5E09A3B2831C102ULL, 0x31A0C93134E6E757ULL, 0x74D9D9292C855C6DULL, 
            0xC4398FFB755AEECBULL, 0xB4391DD7C8AD27DFULL, 0xF5B453CF10F27E2AULL, 0x8AE3BB2AB4D25B68ULL, 
            0xD485D7F5371181A2ULL, 0x953F093856A64612ULL, 0x46E5D19183B7A3D8ULL, 0xC35193EFA1748B5CULL, 
            0x7B3CCF6FA387A932ULL, 0x91F4A4F1549DEB51ULL, 0x7038D9F56A06A804ULL, 0x8E160CC3C8E75A2CULL, 
            0xF3E83CCBC8824E29ULL, 0x19E2EEF178CC6B41ULL, 0xFF7E7BFC897B6FAFULL, 0xD141D6E60ED366DFULL, 
            0x55870C5A6FC27E45ULL, 0xD33BF3C61ED12BC1ULL, 0x53BC8193EC8AC2BEULL, 0x5ADB05A339C60D22ULL, 
            0xB6B70333D9851523ULL, 0x0F75B0FE9DE382D5ULL, 0x9DF822A8842D54ACULL, 0x1F647BB9E2C2290DULL, 
            0x8265180F04A75EBEULL, 0x938647034ABAA5E7ULL, 0x3F4FECEA9E806B11ULL, 0xE4B3854CC1B85F26ULL
        },
        {
            0x60453A0745677ABEULL, 0xF400CBD274D2027AULL, 0xDD82E41A91D33F34ULL, 0xB3232A954E93F697ULL, 
            0x65D328F867296FA0ULL, 0x8D8BED4923012BBAULL, 0x7CA4755F67BE4F7DULL, 0x02FDFEAA8DED9CC8ULL, 
            0x4B530EED6D419014ULL, 0xBD3EC35B82F421B2ULL, 0x0673646EC63B1F37ULL, 0x303156E7545AA105ULL, 
            0x230DC240DF79C650ULL, 0xA6525ECA2E628DDBULL, 0x9E6A1D88E562A3E6ULL, 0xE0D19F95EA0506B5ULL, 
            0x3E52E920FEA9FB91ULL, 0xD0170C21F70BF9C0ULL, 0xF0347BB19D56439BULL, 0x61B207820FE8DFA4ULL, 
            0x6B4210B030534913ULL, 0x0B13497C26262457ULL, 0xAE4C1EBDCCF90FDAULL, 0xB5DFB7B730F6FFF3ULL, 
            0x1349EAB32AFA6017ULL, 0xF4AECD604B1FFB6EULL, 0xEBC1C791353EBEB7ULL, 0x703F4AAEE8554376ULL, 
            0x0E6EA7FF6013CCF6ULL, 0xD917CD80126D6E91ULL, 0x066B5844D5843261ULL, 0xBA2C0B55498F6BD3ULL
        },
        {
            0xAE1BCA464D3AE709ULL, 0xDD61B949BB9B9728ULL, 0xC576E94C1BE16185ULL, 0xDF8F0ED5AAB3C7DCULL, 
            0x2DC4A649A9B3B656ULL, 0x519719E845977400ULL, 0xC43A809F3603CD9FULL, 0x912BA0FFF1AAA991ULL, 
            0x35522FBB349B1A61ULL, 0x551065C8D87C6E4AULL, 0x8D323371A38B1DC9ULL, 0x17F9294705B9E9ABULL, 
            0x853C5910DCA1492EULL, 0x74D5D665104BF0EBULL, 0xD2AB4FB416491832ULL, 0xFD487E384266419CULL, 
            0x0ADDFA2714CBF2F2ULL, 0x71D85B9A819EA75CULL, 0x85B8AD799DA82CB6ULL, 0xF7EA3BA11404D353ULL, 
            0xA30EEE047604028FULL, 0x45862F2601CA25E7ULL, 0x09A9279877987714ULL, 0x6A23F6430F600FA0ULL, 
            0xBFFD4A865237F6C6ULL, 0x61A860CC9CC6E54DULL, 0x1A51029604A46B99ULL, 0x92D95933E7B079A8ULL, 
            0x645210C0358FBBC7ULL, 0xF56C12F4590D6D7FULL, 0x7486C75AF063891DULL, 0xEE788EFB3A3F6DC1ULL
        },
        {
            0x41ABEB252ABF4AD8ULL, 0x6F5D588B047E54FFULL, 0xCD18B2CFF4E2059EULL, 0xBD24B53AD94511B6ULL, 
            0xF022EA3884CE293BULL, 0x1DA3A276A42C03CDULL, 0x0028BC578302C60BULL, 0x8AA2D8F1FAEB6D44ULL, 
            0x288627EE4A5D05EFULL, 0x85398A5E8A940E38ULL, 0xBBC2F71E075F7CB2ULL, 0x2035650AF5F65699ULL, 
            0xF0C28CC3FE13B1B6ULL, 0x095422538AD69A47ULL, 0x7897D65D5E68F2F0ULL, 0x55076F29A79D720EULL, 
            0x54FFC8E5FBE92CFAULL, 0x66A171373D1472EEULL, 0x02C40094C0C9A03FULL, 0xBB69468CBF5102F8ULL, 
            0x528C520E4B865D50ULL, 0xE30103A86E357989ULL, 0xCC50B88C017A38E5ULL, 0x0F967A91378F06E5ULL, 
            0x58B978812431D6F2ULL, 0x8C2F55A9E23D9F7EULL, 0xC8FE8FF6248D516FULL, 0x0A44F630D6381E2DULL, 
            0x0EA45EC1CD216196ULL, 0xBEAA2361C886BE66ULL, 0x5901C0D33B84EA24ULL, 0xA5275A471F5C8A74ULL
        },
        {
            0xAED0A159D783CC4DULL, 0x392F233C6FF5BB8DULL, 0x68E890F7958B4E38ULL, 0x98D1A43AE4DFFEE8ULL, 
            0x1FE691871D7DC31BULL, 0x69BAB991A876C582ULL, 0x55AD6E16F7EBD60CULL, 0x96FFDA1F1709B495ULL, 
            0x7E75551E3C44389DULL, 0xCC522AD174B879A7ULL, 0x6B37602C9555E243ULL, 0xADAAD4FF7ECA6981ULL, 
            0x73BF3DAB848BA69AULL, 0x4FD20BD69486426FULL, 0x20D5E4882736A637ULL, 0x950D8E3E19950BE0ULL, 
            0x03C6C0489B54A8B4ULL, 0x2337934F58034671ULL, 0x25F0D3134DED2C53ULL, 0x1563269E208EA99BULL, 
            0x16CE44A3B3AC29CFULL, 0x2317C1A9523BCECEULL, 0xF2121F4542B02A96ULL, 0xFD7487128D77F923ULL, 
            0x247CDC34BBEC55FFULL, 0x219F219A1940B965ULL, 0xD4BC5B962FA6D90BULL, 0x10DD9ED1EB6989ECULL, 
            0x6CDA14FBCCC66743ULL, 0xC75426EC30B7B113ULL, 0x6F98967CD69F5F56ULL, 0x0CA0BE9695D409CEULL
        },
        {
            0xFF1451DF8B25AA13ULL, 0xDAF6215D4403A809ULL, 0x41FF4E9A5C68C895ULL, 0xD344777AADFBD147ULL, 
            0xAE0E51AC91E64CE6ULL, 0x944DC9FDF87F7D47ULL, 0x4E83C1F09883A4F0ULL, 0xE842C249BEE13C42ULL, 
            0xA15256D5EB98C46CULL, 0x699F89195FB56DF8ULL, 0xC3DD158AAB4448E8ULL, 0x3D1C73021F2C882AULL, 
            0xC3BFF377BDAA04C5ULL, 0x41C192C4ACA76105ULL, 0xE8B26D9CABF15F84ULL, 0xE66B888DF9B7CBAEULL, 
            0x02BD4C38D89BAD95ULL, 0xF0D67BC278A673C7ULL, 0x418D5C45104044FBULL, 0x2497CE799FA9E4ABULL, 
            0x75A57B1F411226B7ULL, 0xAA91CF30D9DF0498ULL, 0x793225A0A6BCA96CULL, 0xB365E6DAD0939224ULL, 
            0xCB348E59321A8A9FULL, 0xAAFE78EE3CAF2AEBULL, 0xFEEEDA794E97433AULL, 0x2531965AF1F26ECCULL, 
            0x5631FD8A956CE11BULL, 0xEBE30C2CB71702EBULL, 0xECE93882B9BC1CDFULL, 0x9798D7AC03837079ULL
        }
    },
    {
        {
            0x45033966C972AEBEULL, 0x56468123D21EA538ULL, 0xC3DAEB12D4328D2AULL, 0x41CF197E3375D85BULL, 
            0xE6CC73E4D30A5300ULL, 0x76DCE9E4AB882578ULL, 0x03042759DB83E588ULL, 0x852E07384BCE40FFULL, 
            0xA8467F653FFBCF5BULL, 0x61EE6912FAD85C71ULL, 0x7DE85D8581AC18DCULL, 0x7EB511095CD536B3ULL, 
            0xE8DC100B6BCACCCBULL, 0x790FD647505B967CULL, 0xB0FA612E5BA2D48BULL, 0xB6250A81D82EB002ULL, 
            0x12AFA1AF5BDF8E91ULL, 0xA075EE449D683B8CULL, 0x45B86B18142F9477ULL, 0xB89A43B0B2C9BD89ULL, 
            0xFE5E464A09EE3323ULL, 0x54C40B35258F5E88ULL, 0xF50A6FB0B4C2B628ULL, 0x8982B314C8A3575DULL, 
            0x5AC33C2BB57A3B21ULL, 0xC656B0A19DB49AE7ULL, 0x3260861963F301FDULL, 0xDFDB1E268066FB91ULL, 
            0xC1D3F67581059C8EULL, 0x9C2F16CA42934AADULL, 0x85E4370835808612ULL, 0x2338CBABDC991396ULL
        },
        {
            0xEAA11CE0E6387BB1ULL, 0xEADC69AFB7F63A77ULL, 0xC107B7A69DBD050DULL, 0xA9192C8A0EE80B74ULL, 
            0xFDB416FF1FF256C3ULL, 0x794B7C76AA043931ULL, 0x0AB34DF4C27211B7ULL, 0x5600001AFF7616C0ULL, 
            0xC221BBBAC6514978ULL, 0xAA4E38349AB87622ULL, 0x2F73B4C0224616D0ULL, 0xA4AC31C390724B17ULL, 
            0xEB7E7F9BF1D0D448ULL, 0xE310DB9613ADDFDEULL, 0x9E042225D0D8BD2DULL, 0x7047650DE3289320ULL, 
            0xA61313CE4E3E408AULL, 0x4A1D691E10860477ULL, 0xC4941482CE2B7980ULL, 0xA95F2577752BE1A8ULL, 
            0x561DB6BF3E1FE076ULL, 0x46EC905CF98FA77DULL, 0x7757F47E691D3273ULL, 0x86F282544987CE1EULL, 
            0xB439F0A9AF07BF93ULL, 0x15C646E9D692A9E6ULL, 0xA1342A2127148786ULL, 0x6564FBB92BAEC4FAULL, 
            0x3E6DA6899816B996ULL, 0xC52BB28E59BAC8C7ULL, 0x51ADB31EC5602FB5ULL, 0x9F2391DE389E579DULL
        },
        {
            0x0C22FAA367CCAD97ULL, 0x912ADC6299D7939BULL, 0x93E95E822FFDB2ACULL, 0xC9B8FC1146354283ULL, 
            0xADF2235C75358D85ULL, 0xD96FFD91BD328208ULL, 0x18DD5BE70D5367D2ULL, 0xD3B7976A607E10B6ULL, 
            0x8BBA1B9ECE5FCCC0ULL, 0xEE04D6616DC44E92ULL, 0x721833B303BC69DEULL, 0xB960FB99A2C9C7A1ULL, 
            0xE145FC5E847D65A0ULL, 0xE7B56A703554672EULL, 0x3AAD6D4536DE3CD0ULL, 0x000BF000E85A7330ULL, 
            0x656E4CC1B87ADC26ULL, 0xB80AD83C47E48B1FULL, 0x272FAC57748C893FULL, 0xCB042544A6CD4326ULL, 
            0x30E2DB982CB5AF56ULL, 0xCD0CF87F5D745AF4ULL, 0x87EC988F13A5D163ULL, 0x0FF13FE39F2BE389ULL, 
            0x0A56378669D34F34ULL, 0xE93A15923CA86E49ULL, 0xF2CF2B54774F3286ULL, 0x45E8DED9080EB5F5ULL, 
            0x5F9832E145977CFBULL, 0xB24BCEBAD0D4F2EDULL, 0xDD400058EA5DFECCULL, 0x92976921038AC774ULL
        },
        {
            0xD8C50E289486A9E9ULL, 0x81553B4CAF5453C8ULL, 0x09912DE068C56E8BULL, 0x1D322A212DC8B9BDULL, 
            0x797DF7A496F431ECULL, 0x047B1A8CEBF99A2DULL, 0xAB6D94E1B635A6DBULL, 0x5C6431553046E9C3ULL, 
            0x9B135C5D2D1171ABULL, 0xDACA7F4D9217A7EAULL, 0xCDDE35D085747FF0ULL, 0xF628895FCB4BC96AULL, 
            0x2B790EE0880636DEULL, 0x3EEEF838B6B1C88AULL, 0xC07A5B9D0581A025ULL, 0xEA3D8C509C359185ULL, 
            0xD89450E6F8911551ULL, 0x3F5ABC302E2A08E2ULL, 0x0DB67DB15311DEBAULL, 0x21331ED44E1076E2ULL, 
            0x214903B2BC27715CULL, 0x75A2DA86A826E7C5ULL, 0xBC3AE7D4033B7A16ULL, 0xD0E3AF322AEC388FULL, 
            0xE4D7A854D055B9DBULL, 0xD121C2E271A26D81ULL, 0xFE94BBB5DBA90928ULL, 0x72CC3ED52A0535BBULL, 
            0x81AD386438A918A8ULL, 0x1DE23F2D2E0E1E4CULL, 0x8D65BFB4BBFB04C7ULL, 0x2F8400EAC7EFC7EDULL
        },
        {
            0x3E2C5106156D871AULL, 0xA483F385971F9D98ULL, 0x624C802A226B1EF6ULL, 0x77757EBD1F791669ULL, 
            0x6E44775AB7D4939EULL, 0x94FE8F43630AE921ULL, 0x28D7C930EB4FC583ULL, 0xA8170ACF378FADC0ULL, 
            0xCA32AD2FB234581DULL, 0x6A0E986505C6BE9EULL, 0x0ABDB23719FD4555ULL, 0xBC06E5663E032776ULL, 
            0x78FC94CD5F58FA81ULL, 0xF0A2BE0C878F9F01ULL, 0x9C5B54B6A68B12A6ULL, 0xA8BFFEADF9481B7FULL, 
            0x0DDC999310465441ULL, 0xEE4A56745B38BA10ULL, 0xC582053EA07C049BULL, 0x25DB76716FD28A81ULL, 
            0xE7A965C8A9F2A549ULL, 0x15135DE51E42097DULL, 0xCD2241000FD78835ULL, 0x86A34BC4983B7773ULL, 
            0x24FC7CB884D854C3ULL, 0x77F5B8FA121191C9ULL, 0x13E9206B41C906D4ULL, 0x7873124FD7D4A978ULL, 
            0xCEFCA34F0E548F37ULL, 0xDD03D8CF00C74F76ULL, 0xF5FBF21BA234D070ULL, 0x37C8D503B8757ED4ULL
        },
        {
            0x6319FA6831751DF5ULL, 0xF91526D1BDF349B4ULL, 0xDCD780B66A7AAEF2ULL, 0x8AEE7611796D471FULL, 
            0x3C0DDFED5C78A75FULL, 0x937954AFA11453E2ULL, 0x973DCB6D76FF8B4CULL, 0x51BF33AD78E1BEE1ULL, 
            0x93ED5CB326459DF1ULL, 0x87B4D539060027ACULL, 0xA2C268BAA6DF115BULL, 0x17507EEC9A597D22ULL, 
            0x0A660169D5FB5B17ULL, 0xC922CEBF3B0AF35FULL, 0xA174EF8BE695CC26ULL, 0xC4A273CFC48A8916ULL, 
            0x2FADF881B23AAF71ULL, 0x70FB0113E67D331BULL, 0xE2CF1059851B5A11ULL, 0xA24B8AB3873FA397ULL, 
            0x8E600FFFA97FAAE2ULL, 0x705494C49594D24EULL, 0xFAA40701F86DEAA0ULL, 0x2A0A6653781ABF30ULL, 
            0xD25C86A10E8FB281ULL, 0x003A33C82CBC72A7ULL, 0xF376D0A491DBAE09ULL, 0x9571620ADEA2819FULL, 
            0xB5FEFD1E23623C9DULL, 0xF5FB712A7B4F6AB3ULL, 0xD265B86A5BB8CA8DULL, 0x1F2CC1620613076EULL
        }
    },
    {
        {
            0xEF9D289F0B390912ULL, 0x4CBE543F62DC3F61ULL, 0xE464B43840922984ULL, 0x60814C1BB9E6EBADULL, 
            0xAEFF4BEEB139905FULL, 0x5CF4C0234DEA9D11ULL, 0xB6AA182431B1AD72ULL, 0xEFF7A2F1EC495665ULL, 
            0x15428D40166295E1ULL, 0x7D0A063AF1DF06EEULL, 0x773A12D7340B51CBULL, 0xBF89286611309056ULL, 
            0x00D41C689D6B8FE1ULL, 0x3BFAE31E1BD77AA8ULL, 0x394EF99F217AFB5CULL, 0xE6D3A23F9773869BULL, 
            0x946EFA6C8B8A6B32ULL, 0xF0908C7F7266BD49ULL, 0x82B803D3EAC38F24ULL, 0xFEB1C2DBE18B742CULL, 
            0xD6D6208C33B451A1ULL, 0x2E2AE9BCF2ACBC6EULL, 0xC553AFE546F3D734ULL, 0x75BF1BA9441EECA6ULL, 
            0xFF4A7F64563FE222ULL, 0x9B49DFD920C5E6D1ULL, 0xB2A8B1A4CF6AD435ULL, 0x498D2A63ED8408EBULL, 
            0x88ECBD96CD256E40ULL, 0xA9213710623E1F04ULL, 0x963FC725F23C02DFULL, 0x29D3302D61ED85AFULL
        },
        {
            0x0336AE3F1E625B86ULL, 0x1E471475534036ECULL, 0x1F867270B26819E5ULL, 0x9105E401B5FC9DFDULL, 
            0x49BB50C0E13C89E7ULL, 0x6FD5F150AD8B8232ULL, 0xD2AE9C62F9EECBF6ULL, 0xA005A1D4C09CD140ULL, 
            0x58AD4D9D13984E13ULL, 0xE276237A973E7890ULL, 0x46A5B61DE067C6DEULL, 0x337AA94BB0FEC59BULL, 
            0x7193A2B5CC606C87ULL, 0x981D698C9EC59119ULL, 0x49B1F46EECD75FBEULL, 0xA9D1F36B6365F388ULL, 
            0xA417E2932E48B78FULL, 0x51EA33F2E3BD383AULL, 0x6DA34452B39CC6F6ULL, 0x1A2B1E534508A0EBULL, 
            0x2656A9DD1076B9B5ULL, 0xF0803F643A754604ULL, 0x0348D075072BCC7FULL, 0x5D147161933072BBULL, 
            0x9F703BD11C0981ECULL, 0xD6B19D8EF6C7B581ULL, 0xD161275E438649F9ULL, 0x879C58466308CF47ULL, 
            0x820A762718454200ULL, 0xCE72BFB7302D6F3FULL, 0xC41DA4CA113C1AC4ULL, 0x51A0DC444AD9421BULL
        },
        {
            0x37B5D39DCFEEBF6AULL, 0x155F3FD49A0B05A9ULL, 0x4EC9020AD3A5114CULL, 0xC98785F86350A67FULL, 
            0xF5C950EAD8F41D68ULL, 0xB07E028CFDA94592ULL, 0x0D7BF8D735E192A4ULL, 0x3F17528F9AF47933ULL, 
            0xF5DECB51A85A3B2CULL, 0xA396D2F4A76DB760ULL, 0x1115CB388D045F13ULL, 0x0E9CD23DF61F612DULL, 
            0x8A8C0524A6A7340FULL, 0xFFB0DDD10F69629CULL, 0x8EFC30DDEE06177DULL, 0xBCFCAD85339DA1E8ULL, 
            0x85E8B7814C491772ULL, 0x6BF22D2BA0DEB680ULL, 0x63A2FCDEC2DE2B14ULL, 0xDB7F3190F65E1764ULL, 
            0x9D2A4876F1AAFDD6ULL, 0xCBE92253F59E2361ULL, 0x3743E0B0CB0B7AC1ULL, 0x34AA48FF105AC10AULL, 
            0x1E98E95493E9EC8AULL, 0x75B5A10A5F62E722ULL, 0xDD5EFFE063EB239AULL, 0xBFE09DF73A3ED6C5ULL, 
            0x7BF2B87913E5C20FULL, 0xE84C2BA99A609D49ULL, 0xEDF05C0BC61851BFULL, 0xEA307F14EEDDF377ULL
        },
        {
            0x094B4F52FB00014AULL, 0x20650A00EB8EF073ULL, 0xD0C1484A28ECC5E5ULL, 0xBB1E59E921BA9E8EULL, 
            0x4B2C0ABDCBCEFDEAULL, 0x5540650837581A4DULL, 0x1C3E9BC60BB12477ULL, 0x8E12EFD596270508ULL, 
            0x015FAB7250A7C111ULL, 0x568BDDE7CE555C7CULL, 0x8ACB8FD184142111ULL, 0x0CCC4B75470A9167ULL, 
            0x98C2FC7F87C8D7A9ULL, 0xB9D4C1025AB30B11ULL, 0x076132403FB05830ULL, 0x18A0379DED96337AULL, 
            0xEB418BB5FF50A2EBULL, 0xA36302741695232CULL, 0x67ACA27BF813ABD2ULL, 0xCF3AD59A6B9B84BEULL, 
            0x3564F0F3450AD7A3ULL, 0x6FA135864613DADDULL, 0x5FC769F64E01C0F6ULL, 0x832368DB7DD81505ULL, 
            0xD181E152303E8043ULL, 0x7A177F20AC374ABFULL, 0x81E511CE1EFBDA1AULL, 0x5EC9E6CF76701812ULL, 
            0x9019CFD8B7B1F665ULL, 0x04F296866FE9883BULL, 0x02130B59E6621EBFULL, 0xCC11A6A941D91733ULL
        },
        {
            0x77D82449B1830FC4ULL, 0x35E343631B01FA06ULL, 0x1D05292E21FB6E25ULL, 0xE2631827E03A7F39ULL, 
            0xAAFFA6605E9F6A52ULL, 0x67BD8CFB55803748ULL, 0xC063FC87F6B6C24EULL, 0xA41D8F44EE043A90ULL, 
            0xA0B93A05F0EBD3F4ULL, 0x3B6FAD79526F9A7FULL, 0xEA96725C3BF858EBULL, 0xE9427BD0E3E9E834ULL, 
            0x6B6ED691A7F340F4ULL, 0x389B00EA5E695013ULL, 0xBC1C0BD1894CDD02ULL, 0x1F2F01F9CFEDF9FBULL, 
            0xC6485D62D89C992AULL, 0x7716CFFDE2D3E0EAULL, 0x2E580D9FD68B2B8FULL, 0xB0AA8D6457C32E92ULL, 
            0xFEBD5A7CE1948C05ULL, 0xE43B684F0686D413ULL, 0x7D0DD11162001482ULL, 0x46063EDAE62BAC45ULL, 
            0xA9DCB85477744A2FULL, 0xAEB5867C8EE1CE69ULL, 0x623EA0BF53B5F459ULL, 0x461C9088E3551FE9ULL, 
            0x22ED49EA4053239CULL, 0x8C5D1CC6DB9E127EULL, 0x581EDDC7E23D1CEFULL, 0xD0E7A39C5C022EE4ULL
        },
        {
            0xA9AD2CCBD0E2A62FULL, 0x73DC55C6FD0A3BC1ULL, 0xAA33AE4B7FDD7EC4ULL, 0x38345600C735EBE5ULL, 
            0x33FA092BCE512D7CULL, 0x369CEC57C2AB797AULL, 0xDDAB4F5AB17F2CDCULL, 0x3EF4F29B591B66FDULL, 
            0xC22591588733B298ULL, 0x31206FB11496C866ULL, 0x5DC82F62B7508C46ULL, 0x735A69820B74C598ULL, 
            0x91D61CD3D26B01D3ULL, 0x276CC8DFC122D9DFULL, 0x0F1E207C42E973BFULL, 0x77F8F1FBAB77A0CEULL, 
            0x1B6AA9986F0C3474ULL, 0x7B014685897241D4ULL, 0xF32EA9BE3DD7476DULL, 0x3815667BD37A14C9ULL, 
            0x838FACA20DD784CAULL, 0x2C01E671ACBFD1C7ULL, 0x1DA971003A45B750ULL, 0xDBFA89438EDE3250ULL, 
            0x47BD470BFB05A6F9ULL, 0x8EE9259D610DAFA1ULL, 0x10DC783AFC9B8ACAULL, 0xC1E83FDD7410BC34ULL, 
            0x5F1BF1CC84409559ULL, 0x9EED84C67DCB1CF9ULL, 0x8CD95AE4A434A42DULL, 0xDCAE7FB9F5521ADAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseFConstants = {
    0x94D2C14D48458246ULL,
    0x905A2D9A49639E19ULL,
    0x57315B8462389770ULL,
    0x94D2C14D48458246ULL,
    0x905A2D9A49639E19ULL,
    0x57315B8462389770ULL,
    0x829AD2D8C458F13CULL,
    0x7B695FCF1A42C536ULL,
    0x0D,
    0xC3,
    0x11,
    0x25,
    0x19,
    0x3B,
    0x6F,
    0xBD
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseGSalts = {
    {
        {
            0x710460CE4040CBCBULL, 0x639CDACF9A81B15FULL, 0x48559F0AB65D339CULL, 0x0C2628CF30C10273ULL, 
            0x6B8BE2325022E3AFULL, 0x85DA87CF371CF1A7ULL, 0x673B10BB4DB97EA6ULL, 0x36020F3667D27788ULL, 
            0x88ACD5657AE0900DULL, 0xB1A6ACD0F7502A99ULL, 0xFE4E8FAADFE214C2ULL, 0xB1B2B2D553B1034DULL, 
            0x87A33934D8D502B2ULL, 0xD3594F6913B9BCE7ULL, 0xBC91D2BCB4EB6407ULL, 0x73E60BB5910DCEE3ULL, 
            0x14A61C7B4D6864BEULL, 0x783EB73787E08E4BULL, 0x17255C5C7568A0E4ULL, 0xE55450BF6ECDF645ULL, 
            0x79A69674AEC0D66FULL, 0x982F1AAA4D7D0A51ULL, 0xACA797E13CF6BBD9ULL, 0xF1F71CA54505C480ULL, 
            0x9647A49FFFAF67C7ULL, 0x3E101EA3FBCBC62EULL, 0xE5FE9212E231D9BCULL, 0x4379CD30F5545713ULL, 
            0x8E0753D2E935DC72ULL, 0x7FF537B8BD9DC357ULL, 0xDE7638B3627D6C19ULL, 0x967024938AD0FA51ULL
        },
        {
            0x05A2618F278EC5D7ULL, 0x834685E4F425897FULL, 0xC5F6308F5CF13FB5ULL, 0x5C43C643C882702DULL, 
            0x6D2B89FAE6C0B87FULL, 0x968AB85248BF4E7BULL, 0xAC7A0D788B091034ULL, 0x43C2076127D7CDC0ULL, 
            0x8C12F9C664F64960ULL, 0x9913DA1A3DB270DAULL, 0xBB6D9915101E7433ULL, 0xE575FE6DE1FB2D2EULL, 
            0x28A88AE0FB9B6F57ULL, 0x5E130CB7AC1468CDULL, 0x15357782A2DFF6FAULL, 0x7523B2FF5E5C51EDULL, 
            0x3153F4C31912254FULL, 0x0B4117F42DC54100ULL, 0x6771DD51C81742B8ULL, 0xB6DEBAE264EF3A7FULL, 
            0x1BBDC732DFBA92B5ULL, 0xA34A9CA584641D81ULL, 0xDA06C9B3DC73F3B7ULL, 0xD57DA2D56CC68F90ULL, 
            0xD8724965522651E9ULL, 0x8BAEEE98A37A93DDULL, 0x2DA8E1C14FF467F8ULL, 0x62D4B7E4C01CA9D5ULL, 
            0xD27846EFB4E97F71ULL, 0xF49F2DBB395B6515ULL, 0xF9BEFC93A76320F2ULL, 0xC9B9622BAE627EB3ULL
        },
        {
            0x92083FC015B2309BULL, 0x55D4FD60B8CCE3C9ULL, 0xAC8D4276634B4EACULL, 0x8241DC0DA2C00BD5ULL, 
            0xE6D6289BF5DAA4D3ULL, 0xAA0031947C545A67ULL, 0x487E631568A469E4ULL, 0x63DE3B23FA5350D2ULL, 
            0x222B3A737141B980ULL, 0xDAD1A2213D0F2588ULL, 0xC8E21193195C7B14ULL, 0xE9F53FAAEE47E7F8ULL, 
            0xE7BB963A81D67CD3ULL, 0x2B1EDBF1A3434DE9ULL, 0xB5A6E4D6195C9F60ULL, 0xB1EAA85EA5CFCC21ULL, 
            0x53560447C080B2ABULL, 0x56A5495C2DF6F4F1ULL, 0x3F2A07E86B3A45C0ULL, 0x29D3B672D2E51117ULL, 
            0x5BAD5F8923CE82CCULL, 0x19B5DAE581962955ULL, 0xBB1E5B312226765FULL, 0xA268DA14B5EC1396ULL, 
            0x6D3E4EBBBFB42AFEULL, 0x27E0331201B972EDULL, 0x60AB3E44E23119E4ULL, 0x137D46BE243F35C6ULL, 
            0xB52BFF48723C2263ULL, 0x59C2310826E739DAULL, 0xFBF43FC5DE538A13ULL, 0x226E761CE591FD01ULL
        },
        {
            0x61C0B703222A5BCFULL, 0x85B310528F99689CULL, 0x569C3DBA0AF0DB55ULL, 0x0121A44657CCFB21ULL, 
            0x6A3E162AD9B13242ULL, 0x8E092DE6C1B85B19ULL, 0xB569EF063768E80CULL, 0xA684CA4708B36E73ULL, 
            0x04D29D18ED2D3B10ULL, 0x235B7A3A2DF3D1D6ULL, 0x5092A500D7823F10ULL, 0xB9B3E83136C19CA9ULL, 
            0x4C3DAD6C21996CCCULL, 0x47D75BCC3097FE1EULL, 0x361C82A4FACA8950ULL, 0xF8DFC8E35C6E532DULL, 
            0xF016579070B2AF4DULL, 0x24ECA82B1A132261ULL, 0x9A4D4D4B9AD6F9DBULL, 0x83C2DC86C8EB18D7ULL, 
            0x16699A3DD51C6E51ULL, 0x5E8EE4CFB53020C6ULL, 0xC8D556A24374C09EULL, 0xAD4FBCF057EEB5D2ULL, 
            0xF91A9377E11C3C14ULL, 0x6BF893BD97CC5579ULL, 0x63DAB78A6FF3A996ULL, 0xE7BF4968E8B2B862ULL, 
            0x24EE87D3322EF499ULL, 0x03753FF23C3DBB0AULL, 0xA225F641337D30C0ULL, 0x27AA70DB1B336C0AULL
        },
        {
            0xC4B78C50F60A5240ULL, 0xE48AFE447723F6CEULL, 0x3DA1ACF2995B7513ULL, 0x395408B6EB28FC5DULL, 
            0xBE2F8CD677983B13ULL, 0x9561761419CD0ED3ULL, 0x3B32C5AD31D0D253ULL, 0x8D191040057741F7ULL, 
            0x33EAF8A41B5518B7ULL, 0x3E0C5A7DB0436DABULL, 0x9C5AE6BB0D9365D4ULL, 0xB53A56875AA432DCULL, 
            0x0F2CFE5369E2DCFFULL, 0xFAE08ECC14608521ULL, 0xC543EFDAE45693EEULL, 0xFCF3F38951B2D098ULL, 
            0x4A793BC9FECBD932ULL, 0xB06AF179B4EB6C80ULL, 0xC11B8171F156CABFULL, 0x5ABAEA8D8933F99CULL, 
            0x28C61661A82B67F6ULL, 0x9ADF1982DB4FD85FULL, 0x02060B7E173B626EULL, 0x21609972A5491B7BULL, 
            0x8293BF0AA87E616BULL, 0x623615CC4C13A5C4ULL, 0x2C1EA2A6A91F9E6FULL, 0x6AEACA741B3B7629ULL, 
            0xB0CAA142282CDAA1ULL, 0x6363B00B4392E58EULL, 0xC43DD0E32A5A9C5BULL, 0x3AEED49C1BDD9EBDULL
        },
        {
            0x4411ACC395D303D2ULL, 0xA9E8C5EE50A5B359ULL, 0xC219F47219FCC410ULL, 0x46B0D20AC164BC42ULL, 
            0x26D3339160655C14ULL, 0xB1D5B9C46BB63024ULL, 0x1663E709A0FE2338ULL, 0x8F6243B64E497111ULL, 
            0xA554B51DD2954BD8ULL, 0x3DF3D663073BA3AFULL, 0xF2010E1A94050384ULL, 0x2017DFB5354A9543ULL, 
            0x8DBB4C734CE18948ULL, 0x3E2E524A365F453FULL, 0xA396469C67FE55B4ULL, 0xDF05FD3042A8012EULL, 
            0x52246FBFBD2E3242ULL, 0x597BCFFD9E669DCBULL, 0x6B9703EDB7A369CDULL, 0x9DF48BE35E5212BAULL, 
            0x9E42CCEBE05A330DULL, 0x7F7091DBE176CD2DULL, 0x6109059C4066198EULL, 0xD8839F975C0F674FULL, 
            0xE86E948704DB4C07ULL, 0xB20DB7A35D279B1CULL, 0x0FD9A84B11B30382ULL, 0x5E8802F5FD8F341CULL, 
            0x94640B13492C4890ULL, 0x1AC284349CD77D37ULL, 0xEC888C4C90DFA99CULL, 0xC562A584103044EBULL
        }
    },
    {
        {
            0xC2B1382D5B1EA7FBULL, 0x37BF3AA2836110AAULL, 0xAC02BC90DAA68199ULL, 0xF4B1072F52189896ULL, 
            0x537B44E658742A1AULL, 0xFCA09369732446BBULL, 0xB31066C6C01154A2ULL, 0x5FBFDBA44C93107BULL, 
            0x6A6227FDC65DB4F6ULL, 0x92A8FDBF800B0076ULL, 0xCF157E22CB574C83ULL, 0x99704A300FEB9076ULL, 
            0x6EDCF3EEF159D632ULL, 0x4AC30E900C50EA94ULL, 0x6CF62A25B92D2DE0ULL, 0x6DDA260A8B418B32ULL, 
            0x04C4C0D1E3F569C9ULL, 0x6A8F2ABB064A2E1FULL, 0x7ADCE4C7759CA6C4ULL, 0x49DA3D748138C312ULL, 
            0x8ECCA85D42455152ULL, 0x9E4CE51FC46210B3ULL, 0x60A3FDFAD3ECDAA1ULL, 0xA130D2C14D02359CULL, 
            0xB641D27338F13989ULL, 0xE2848D274CAA8E70ULL, 0xC873DB1988FD5CA5ULL, 0x9EE03A74432082DCULL, 
            0xB4E8294503548C6CULL, 0x6A2AF8BD9ECCEBD8ULL, 0x68F2C278AFDC0D43ULL, 0xB72F948E872B9C6AULL
        },
        {
            0x39E9C2E121B0A25EULL, 0xF4E4DDB07F7AEE05ULL, 0x423640A795724494ULL, 0x892408321551C616ULL, 
            0x148CCB58E66DED87ULL, 0xA97B7CFA28F16859ULL, 0x3721C692FD90CB69ULL, 0x3D147AD1134045A9ULL, 
            0x35EB8C6BECDE50EAULL, 0x95CBB4049151F019ULL, 0x0AC12AA94D16946DULL, 0xFCD979DAFFE68ECBULL, 
            0x9254FAB3212E361DULL, 0x6824AD2749DDE560ULL, 0xABD66681C7E14151ULL, 0xFED3477EADB7EA26ULL, 
            0x47E55493FAADC014ULL, 0x1DD2E7F90DFBECB8ULL, 0xC196EF494E7899F0ULL, 0x241B09A3E837C152ULL, 
            0x66EB8D059E2A64D0ULL, 0xDB462E969A2CBE37ULL, 0x020F210CE096364CULL, 0x85F475B18E6111F3ULL, 
            0xF878130AA1CDF769ULL, 0xE3367ECEF1E4D654ULL, 0x5B87BB3CCC78AC76ULL, 0x965CADC385428350ULL, 
            0x418785755DB82CA9ULL, 0x6D4DB4CA6BF9DC79ULL, 0xC383E5B18EA3E711ULL, 0xEBBE584AD9BA5F74ULL
        },
        {
            0x6C0E2D5E564237DFULL, 0x8602382F5DD44A3EULL, 0xFB40B391D1050C28ULL, 0x7170B4CF4965F811ULL, 
            0x597403AE2DED75F3ULL, 0xAE3DEA4D62E9ED20ULL, 0xB78B89E368D92B1EULL, 0xDF6630545765F87DULL, 
            0xEE87D61ED8132160ULL, 0xF5BE83E1F02EEAEAULL, 0xDCFB9DF40803F99BULL, 0x35F055248229E46EULL, 
            0x329BC7F835317AE2ULL, 0xAB66E9CD2ED27125ULL, 0xCBDFF9A851B9F8AAULL, 0xA6500DA58FE0D8B7ULL, 
            0xDB4ABA73A1B6EBEBULL, 0x0678AFE0527E863FULL, 0xE6687FDCD1890F3FULL, 0x4A3CD03FCB7D1907ULL, 
            0x418098BF360308D7ULL, 0x7B003A8DCDFB73DEULL, 0x113E3E553C597031ULL, 0x58823E72725CA3DFULL, 
            0x5255DFE8ED4CF0BBULL, 0x0722A511C334B250ULL, 0x7FD7DA68863DD911ULL, 0x25F8DDEDBAB9FFC5ULL, 
            0x64F352B5D5FF808FULL, 0x733768E18DBDA694ULL, 0x895842F22AA3B6D3ULL, 0xD055DCB5D7BBE3A2ULL
        },
        {
            0xA69B981634590733ULL, 0x4C29E0BE15BE7606ULL, 0x7019FD367F596CF5ULL, 0x6E9B2FABFFBDA78BULL, 
            0xB5B502F7D65D7B5DULL, 0x826008927B9C330DULL, 0x07DB07B1EDC5E1D4ULL, 0x92A76C607B0F987DULL, 
            0x03F3B726C707F61FULL, 0xD57041E049A27BBFULL, 0x35DF15ED5D2015F4ULL, 0x4BE9FD70CBFC5B51ULL, 
            0xB42DC5BA8D0783CFULL, 0x9189CD0D10B9ED8DULL, 0x36884DA95E10199DULL, 0xD7BE752AFFF9B07FULL, 
            0x31F7615D7AEC11DAULL, 0xFCB2DA2B569767F4ULL, 0x71B0B14C07486CA9ULL, 0xCE4760B2EE968297ULL, 
            0xF6C88E3C3C7A7523ULL, 0xFEC8CC7FE2A8BF27ULL, 0xD1034EA2836D02B4ULL, 0x12BD097282E5D0F3ULL, 
            0xF15CA84E638B5DF3ULL, 0xF910AB24143546BCULL, 0x184517003657D6DFULL, 0x766C93E0296BFDE8ULL, 
            0xEBE4591CA7974C59ULL, 0x492DCEFAF2AD6D95ULL, 0xF0ACE988E78D2ABFULL, 0x830BC4E24C8CD272ULL
        },
        {
            0x6E0E4043AD41EEC2ULL, 0xDDCAAA35FD83EC15ULL, 0x64981CB7A6EA0FE2ULL, 0x1DE65C4378B5A422ULL, 
            0x45B780B12795E310ULL, 0x8FBA0C7D6CC411FCULL, 0x3DEE7A9624B1FED5ULL, 0x37CED2EA5CDA2535ULL, 
            0x5F62C5A8DAD3A4D5ULL, 0x4D388B854BCD7655ULL, 0xF7BA871A89A6F8F4ULL, 0x3EF3699EF31390E5ULL, 
            0xA86869045A51CFC2ULL, 0x8F839EB8A9903A4FULL, 0xA7FE0E98F0C152BAULL, 0xAD886809A9405970ULL, 
            0x0C88A12FA3B8E802ULL, 0x1A1D26CA9795A54FULL, 0xB6C5F700AFD86D41ULL, 0x21DEC73089932184ULL, 
            0xE3E819CAA043A834ULL, 0xFC6BEB054EB82842ULL, 0x7F1A8E76E71DC173ULL, 0x13BA241C875876AFULL, 
            0xA7B46300C50F136FULL, 0xD3EF8217A70BBB9EULL, 0x6337A241DE0671AEULL, 0xBECEF5C8BE54801BULL, 
            0x6FF50F08D2FAF3A0ULL, 0xFA2DFFBE4F627B0FULL, 0x06F7AA86C1CE20A3ULL, 0xA40F50FCB167F434ULL
        },
        {
            0x7CA9F77DA268067DULL, 0xAD86F6F4D6D37E9BULL, 0x68063BE04E4920E1ULL, 0x226F4391F9A348FDULL, 
            0x0ABA9D846F8C73C3ULL, 0xCF0EA27D10A0DD86ULL, 0x9D257D663A3FD083ULL, 0x64470CC0462DC829ULL, 
            0x71FA745117F0D48BULL, 0xE4FA03F1E37076E0ULL, 0xD3DB59336303D3D1ULL, 0xBAB8666C1247C42BULL, 
            0xED4E947C24CD3CAEULL, 0x94FA8031B578C8FBULL, 0x0FDA0D13697A23B0ULL, 0xD98B63831AA8E337ULL, 
            0x71495C9E8D418A1AULL, 0x7A011B67691045D7ULL, 0x1C7D335CBCC7CE94ULL, 0x5597424833D4D27BULL, 
            0x29366ACEB2097BB1ULL, 0x003058C835280D4FULL, 0x926AFAF5C0526278ULL, 0xC08F648F7468C7FEULL, 
            0x16CC26015488D9BAULL, 0x39EBAA05679440CCULL, 0x01B41CF6DB63CD36ULL, 0x74A97E44BF500E5FULL, 
            0xCD8A876B68A69A88ULL, 0xC5CAFE4FE3F46274ULL, 0x7901992B4F961DF1ULL, 0xCE7E2CD0E6FBCB8CULL
        }
    },
    {
        {
            0x530E0CE16A7CC3FCULL, 0x9ABB561696B004CBULL, 0xB5BBE0041E1ADDDFULL, 0xD99A984F901D966EULL, 
            0x3B7EFD9C769CF9C9ULL, 0xA9C509ED4D19B0C8ULL, 0xB7194D8584CDEB63ULL, 0x9793C98A6DABC4DEULL, 
            0x070B5B10D3E8E53CULL, 0xD13D325791BA4C2AULL, 0x87F90D387E519FC3ULL, 0x53FD5FD1DE9F3367ULL, 
            0x154EC3BC7A1C060BULL, 0xC0856814FA388A75ULL, 0x8475343FB4CA42D1ULL, 0xADEE7DA4174B6D3BULL, 
            0xAC0E585CF7FDDA1EULL, 0x0F29C70875BE2699ULL, 0xF8D22C056F110BA7ULL, 0x868A4204E60BCBB1ULL, 
            0x378784333BB294DDULL, 0xC6A753338F086E21ULL, 0x4DBB709F19A9AB84ULL, 0x91CF0965465E6B8FULL, 
            0x18A5BA0C5B0CF547ULL, 0x6FFCED3AA0FE7AD4ULL, 0xE2EBAA929FBD507FULL, 0xB008A61B68300663ULL, 
            0x78FDE19BFE7C0609ULL, 0xC9F458CC42DEA2E2ULL, 0xC532B65AB159C1F3ULL, 0x2E86EF230B9E8AA4ULL
        },
        {
            0x75E7D75D2054628AULL, 0x247F6C644FDB7A84ULL, 0x432E8DE21BAA08BEULL, 0x208A0ECDBF48B6BDULL, 
            0xFCE1E002FAE16AF7ULL, 0xCDD3BE1FEA588D25ULL, 0x794129C40DBAB4E5ULL, 0x11090947FD7E747DULL, 
            0xCEBDE3A5ADB6AD07ULL, 0x9AB742A833CEBF9CULL, 0x835B5AA090752DFAULL, 0xCD1CD944BC3E439CULL, 
            0xDDDB4608C47F2CDAULL, 0x87E4A7D7D0BA2003ULL, 0x3F500945D62AD305ULL, 0xE79C31A24B266840ULL, 
            0x97627453330DD63FULL, 0x2D937C4447800C16ULL, 0xEAC941B3E0535FF3ULL, 0x652206C675870132ULL, 
            0x3651FC39A0B63585ULL, 0x54E404EFED7D08E5ULL, 0xF4E0E4C262BCC7DEULL, 0xF45B8C0876E2F6D8ULL, 
            0x4271075DAC9240F4ULL, 0x6F95E24040AF5EB3ULL, 0x587456BFEB007800ULL, 0x3C062F9CF238ED87ULL, 
            0x4878A88F8173490FULL, 0x2AE71AA35A486CE2ULL, 0xC8D73B3C46591288ULL, 0x19CB787185802B3AULL
        },
        {
            0xB50AC9D9A25D21E3ULL, 0x9467AB5D8986C4FEULL, 0xE8BE405684386FE9ULL, 0xD18AE4EECB6BFAC2ULL, 
            0x9C8D53BA622561C5ULL, 0x1BCE040772B58332ULL, 0x78E98378F65023F0ULL, 0x31C36F48C91F7EB2ULL, 
            0x1B630A381F95D13AULL, 0x1CED7E082A9EF5DEULL, 0x0EE8DF3CB9EF0377ULL, 0x2069A38574399037ULL, 
            0x53EF61FCEFEBBBDBULL, 0xAA3E0C19CF012A30ULL, 0x1F501BAA62BC6FD3ULL, 0x1027EC1187DD50B7ULL, 
            0x86C962F7E6386448ULL, 0x18F41B88FF837D70ULL, 0x2AA5CC92EEBAA82AULL, 0x178CD11023F5C5A8ULL, 
            0x4E27B3C688B8B07EULL, 0x921DD9FE13641BA4ULL, 0xAB2392EADB7DFCB1ULL, 0xC6191B8527617B2DULL, 
            0xC919AA7B6A9F0DE2ULL, 0x63610BA05A89FBEEULL, 0x2B4BB3BC2B51A7B9ULL, 0x7A1F67212F203AE5ULL, 
            0xDE22BE3D16E072A5ULL, 0xCF78FA25232F695DULL, 0xD661F1667EF8C6DBULL, 0x281879DEBFA32470ULL
        },
        {
            0x87A3BA1A58076C1EULL, 0xFD23D95590950D13ULL, 0xB74CD65897523516ULL, 0xCA2920669122A5C6ULL, 
            0x6ACF9B5736E43675ULL, 0x91205D0D990EBE36ULL, 0x2BF42463659AB402ULL, 0x3AC179E7A39AB778ULL, 
            0xDA6B037D4B229930ULL, 0x292F4524F9744FBEULL, 0x9F093162CAA599B2ULL, 0x51CF171A2CE85D86ULL, 
            0xF0CAFB7D63BFA792ULL, 0x1EBD57343972ECB9ULL, 0x07CAD27A3E36F737ULL, 0xD0A00DC99DDA3D74ULL, 
            0x4252CE83B19762F9ULL, 0x895DC037E2DD33D3ULL, 0x62A2917BB7DFDFD1ULL, 0x7D567F3541242F64ULL, 
            0x4573A1DFC1D8B48CULL, 0xB4904BACCCA27B72ULL, 0x1DDC3D1BB2F1BE9BULL, 0xA1969BEA1DD3064EULL, 
            0x826113A170615075ULL, 0x4151CD49C598B1D3ULL, 0xAEAE3DE1E8391369ULL, 0x9DAD61CF29513326ULL, 
            0x43EC0000822FA7E6ULL, 0x53BBCCD0ED2FFA91ULL, 0x4A5DAADBC721B001ULL, 0xFB82090F2E11C7C7ULL
        },
        {
            0x67E06093F3A118A4ULL, 0xFB3E1BEE7463E11CULL, 0x52CB8E79E063E801ULL, 0xDE654BF8E59272E5ULL, 
            0x06B675EA714E0BCDULL, 0xB873592932FBC277ULL, 0xF1A504A826631E24ULL, 0x48B689D44533F186ULL, 
            0x9ADD37A53DB0E4D5ULL, 0x3B3DFF051DD6F658ULL, 0x7F2789018D9AA2B9ULL, 0x5CFB49A4BEC2DEA9ULL, 
            0x752EFB899A878137ULL, 0x1ADAB0B94C3D468CULL, 0x2E5AA4274E5900F2ULL, 0x46852429442D80AFULL, 
            0x0F323E048E9F62CFULL, 0x7BC0201489EFE338ULL, 0x34573684763109B2ULL, 0x92307F21D9149A0DULL, 
            0xE8D78101D4557A72ULL, 0x6C4D75389E3F9DF6ULL, 0x7F70B20A3481BDC9ULL, 0x1AF0BDAA145CBE0BULL, 
            0x805C4DF492F0CE7FULL, 0x062640B87BB692C2ULL, 0x7C7BDC9158199A05ULL, 0xADACD068DD14C21FULL, 
            0x1210911258119FEEULL, 0x34EE89ED58B67B2AULL, 0x4312CAFC76213FC1ULL, 0x1D274BF7D4F678A2ULL
        },
        {
            0x3527F436BCF3D13FULL, 0x6F872CFCE3719067ULL, 0xEFE4084F0F0EEB03ULL, 0x2C43EAA36216E6F6ULL, 
            0x680BD97BA92D1821ULL, 0xFDD7331EBDE5636BULL, 0x2C02D5369ED29476ULL, 0x678A54853257CBE3ULL, 
            0x50791CAC89B05504ULL, 0x4B42071ADC93A78AULL, 0xAF29756263B47088ULL, 0x9F3FB5A2432D9D91ULL, 
            0x7F7A186627D0675BULL, 0x10C94994882BFC13ULL, 0x8787061C02710893ULL, 0xF191CBB93BFA6A3AULL, 
            0x639E07A0A2901BD5ULL, 0x6565A69CF2C4A62DULL, 0x13E44BD773EA0A9CULL, 0x28264EB9CF186E46ULL, 
            0x39984C32A4C07F34ULL, 0x24726320FFC10327ULL, 0x9AD8B0C421ECDE79ULL, 0xDD16BCD47487E81AULL, 
            0xEBF9B41D77354C85ULL, 0xE48DFD3B75528868ULL, 0xE4904B937414AD07ULL, 0x43223DF43EE66D16ULL, 
            0xC62B26B39DFC322DULL, 0x89614395A052C0F3ULL, 0x0C74C869B2DA9AA1ULL, 0x0BF3E5638A498637ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseGConstants = {
    0x4592D6A4A589CB54ULL,
    0xD530262936E469E9ULL,
    0x95667B645755D98FULL,
    0x4592D6A4A589CB54ULL,
    0xD530262936E469E9ULL,
    0x95667B645755D98FULL,
    0xE536558879D330BFULL,
    0x81BBEB9D55CB2791ULL,
    0x88,
    0x02,
    0xFF,
    0xB9,
    0x44,
    0x7F,
    0x75,
    0x5B
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseHSalts = {
    {
        {
            0x02EC49FC735C3119ULL, 0x4F459007C8E6A45BULL, 0x6E0D7B63C89FD783ULL, 0x05AAD2D42FE08C69ULL, 
            0xBE11CE83577AC383ULL, 0x870657564EA6454AULL, 0x715EDFC63EDFF124ULL, 0x7FE8A80A45032DDDULL, 
            0xA51751C4BFB78130ULL, 0xF216C53C5922A464ULL, 0x9E81B1814FC740E4ULL, 0xBD3D6F5A561B6737ULL, 
            0x3C4300FA998DF5D8ULL, 0x8A3613F264F94D63ULL, 0xB301AF4B17352B59ULL, 0xE0B9EA608A7B403DULL, 
            0x7E8B650A7661EF6CULL, 0xACD9E9DF19B41C0BULL, 0x1D1F0F401A9A12B9ULL, 0xCE8AFE656A113CDBULL, 
            0x0F1D749620D8933BULL, 0x3DB946F98808D9C1ULL, 0xE9EDEBCC43F4CC62ULL, 0x58AC9762CAB17A11ULL, 
            0xD881131EA7ACC5BBULL, 0xD387450EBC452A1AULL, 0x259F76A705DFD889ULL, 0x94CD06A859BBE0C4ULL, 
            0x1FFB7DDE27C68B02ULL, 0x2A5231F5561FAAFDULL, 0x8DB6224F7BFA6A4EULL, 0xE63521B39D1964E2ULL
        },
        {
            0xA61AA86C15FD0B46ULL, 0xAA7C125125B9D6CDULL, 0x0ADC6D67386A47DFULL, 0x16CB8596776E7726ULL, 
            0x6402C1B4B5928FAAULL, 0x8DC574270D7E99B0ULL, 0xB156300EA44FBCB5ULL, 0x155D424DF08CEFC5ULL, 
            0xA2CAAAD783BEF59BULL, 0x792D4FF2A763DB69ULL, 0xD10929E550AA59C3ULL, 0xA881329B4C9A8821ULL, 
            0x7483E2AFC2B3F41EULL, 0x960D2E803D2D812FULL, 0xB0A14368CD1F1C70ULL, 0x4630AEF6BC55E96DULL, 
            0x30A35FA3A2446B79ULL, 0x9AE72338E2C88A41ULL, 0x9B0B5EA0AC268A0AULL, 0x3580A9F38220A496ULL, 
            0x09BE77AB658B8089ULL, 0x6F6D7D057EA445CDULL, 0x74600D132F2EA5B4ULL, 0x676D2E86CD4B8096ULL, 
            0xD09EA4E6A613A154ULL, 0xBB1054E27DF74117ULL, 0x52A326CA5C730ADAULL, 0xBA2F69B42A36AF22ULL, 
            0x04111A83E03ECBE6ULL, 0x44FCF34D5A401C31ULL, 0x632CC1D5EFC35410ULL, 0x8B385E9FE7276406ULL
        },
        {
            0x85D5066F596D0F52ULL, 0x29EB16EEA26062A8ULL, 0x20241ED0091B90DCULL, 0x7D2234B256EE9D8BULL, 
            0x0F48BCA3A7748CE8ULL, 0x637E44D92135A7ADULL, 0x852E71BB4289AD1BULL, 0xB64C69CFB7766DF1ULL, 
            0x7F2EE72C2AF9F436ULL, 0x664CF87AE698F873ULL, 0xC4FA4F0761F7F35EULL, 0x03F295BBB514F95AULL, 
            0xD9173B5AC471BCDFULL, 0x58EAE628EE2EEF8CULL, 0x26CFA4BAC70A45D4ULL, 0xF601E2CB90384C93ULL, 
            0x5ED3F34A9CE008A4ULL, 0x5D3B94B77EEE69A2ULL, 0xCDAB0345FE7C8B34ULL, 0x188ED1E03DECAFAAULL, 
            0xBDE62F390CCDB604ULL, 0x3389415AF01B92D1ULL, 0x459A8C453B7BBC80ULL, 0x17FA2229EE2C5A0CULL, 
            0xC1439D0A2927A3C7ULL, 0xB6EC888E1E760DC7ULL, 0x618BBE5D441F9207ULL, 0x2E07D3F947AB132AULL, 
            0xA65D0BC8299F6FFFULL, 0x25076A617659435AULL, 0x5EB56A6B62D54DEBULL, 0x4F981D495712A2B1ULL
        },
        {
            0x91D50D502773AF41ULL, 0xB6429B7533A893E7ULL, 0xF91FC63654DA4C98ULL, 0x43D80AB18632AF75ULL, 
            0x9119003B3A427675ULL, 0x3FBA1CFE486DA669ULL, 0x7AE963006B63C378ULL, 0x7271B39EC3616B54ULL, 
            0xCE577EFC1AD91103ULL, 0xDAFD87999CDC23CAULL, 0x0D8B34580996687BULL, 0x3CFD030A54FBF447ULL, 
            0xE80CE7B0AEAE2293ULL, 0x2AC453F48066F3AAULL, 0x3B7EE4406B2132F9ULL, 0xC62B68386FBB78EAULL, 
            0x9259E42BEBE72101ULL, 0x4F3DDBA416913AA2ULL, 0x6DB8755D125A56D7ULL, 0x24771202487919D1ULL, 
            0xA1AA052144E28B63ULL, 0xA1F0ABB543C0142CULL, 0xB7BE2C7EFF64D815ULL, 0xDCAFC40E2A9BADE7ULL, 
            0x15C160B6BB789933ULL, 0x9FC85F342D74303DULL, 0xE85EAB0A3AEBBE21ULL, 0x28C28523CE897D0BULL, 
            0xE0A2AD09C16B700FULL, 0xC4AD97742FB5A1F9ULL, 0x1889EB2262306E3AULL, 0x5477AE1758FE9261ULL
        },
        {
            0xC1072AD7A747F329ULL, 0xF1740DAB44790AC7ULL, 0x4BB62003EBCA183FULL, 0x2A9DC76BEC90022AULL, 
            0x53C4D7F80B0593BCULL, 0x4AF3C9F0D8F00AA7ULL, 0xE876A41E3D425306ULL, 0x573D2802C02E8F3BULL, 
            0x17C2FA095BA69174ULL, 0x787927B0B13C8DAAULL, 0x8A776908F908FD1CULL, 0x43AB5755FBB454DAULL, 
            0x31C98696E3E3CE69ULL, 0x5FCB47EC6BA0456CULL, 0x9C01C9CA6C7F94A9ULL, 0xEE4B1795BE2395E5ULL, 
            0x043017830C5E2671ULL, 0xA5786D11E3EAB409ULL, 0xBC6EC72D5D500ECDULL, 0xF117D04EBC6D3D58ULL, 
            0x3BDC7F7F2EFB66E1ULL, 0xC5252A319207790FULL, 0xB104EF04108E56DCULL, 0x161FB6BD4020F4C4ULL, 
            0x00810C6AA1ED2955ULL, 0x2AE23AEA57A81AF2ULL, 0x3722061963256389ULL, 0x7491D05951B161D6ULL, 
            0x3BB8ABD564FDC8EDULL, 0xC5DA34CF0E6C1565ULL, 0x56A12B916F0FC124ULL, 0x62EB6ADD13E14E10ULL
        },
        {
            0x1BC6593C881F55ABULL, 0x6031F6B3A5F604B5ULL, 0x5A0F37B268169743ULL, 0xAAAE6A7DB6ED3F3EULL, 
            0xE6EB296703A8604FULL, 0x3A27BF23EC0EEBFCULL, 0x9E95E4318FC3821BULL, 0x418E9E3E5F3F675AULL, 
            0xFC0B0CD57A688DE2ULL, 0x1A43A6953D1BCF0EULL, 0xAF14E09CC21178DCULL, 0x775582F086C753E0ULL, 
            0xE20D93D31F0F3C6CULL, 0xE63CA8B4B906786DULL, 0x7F6386B884AC11AFULL, 0x1A280AD8A39114B4ULL, 
            0x29469EA6CEF30021ULL, 0x19AD6D5D954B33C1ULL, 0x62911534270B4ED1ULL, 0xA912611461BDA577ULL, 
            0x5AD191DF7F722328ULL, 0xC6C648B61ED35EEAULL, 0x2A5468ACA3EC604DULL, 0xB4D2D43B46ED649BULL, 
            0x1637B687185C6DB5ULL, 0x7C5D034C7753463AULL, 0xD5AEF9419DFCEB4EULL, 0x6114A56EFB7E725EULL, 
            0x1CC3C7716E3400F3ULL, 0x19D9F5CB91D7336EULL, 0x7ADB7965131307D0ULL, 0x40808FC4E20A7FF1ULL
        }
    },
    {
        {
            0x0A0FB03567092A23ULL, 0x92D78CEFAFBF8AD9ULL, 0x68A7E20B99B38A60ULL, 0xF36CC393ABA39FF0ULL, 
            0x77F2F738A2473651ULL, 0x9FEA431FDAC54447ULL, 0x29180DB172ACA4CBULL, 0x7A69374868A89179ULL, 
            0x918D085D7E31DDBAULL, 0x6FE281B24C764BF3ULL, 0xD5DC89777ACD9E03ULL, 0x8AC3EEB67F9060A6ULL, 
            0x8BC7195C48F80F67ULL, 0xB35A3C3B61F19F72ULL, 0x764F010F0D2EEEC5ULL, 0xFAB1446F7E8CD242ULL, 
            0xA41E1C39B8549C2FULL, 0x15126CF376173D9AULL, 0xFBE93E5FED996675ULL, 0xF2C6D57264A04332ULL, 
            0x01EF4E74E817DD8EULL, 0x669BB27C886C0950ULL, 0x2584900C4C0799C5ULL, 0x2E56A69D9D714939ULL, 
            0x24768EBC011F540BULL, 0x223349E60C4D7DEFULL, 0x18C2C83372E2633AULL, 0xCFC28C9FA8B2FF98ULL, 
            0x8B10237FC307F7E4ULL, 0x2009EB9FAC50B792ULL, 0x069F616722BB89B2ULL, 0x89C83EE6C5EE0FD8ULL
        },
        {
            0x3E0FF5CD0A976D84ULL, 0x6FD15E7D9127186AULL, 0x352A138042C40F55ULL, 0x202A80F94E9C501AULL, 
            0xFD0E846A9D3833A5ULL, 0xC9DB82E328CDF4C1ULL, 0x0DBED53DC15B1E90ULL, 0x920E6B737F3279C5ULL, 
            0x27D49B83F185FDFBULL, 0x2B55A47F10D1F79DULL, 0x01E1AA082047AB18ULL, 0x974B63DA20CC546BULL, 
            0xF31164C343C5DDDDULL, 0xF5B0E09834467E07ULL, 0x0DA9A1832FAEB9F9ULL, 0x43AE7F6FE725D1F9ULL, 
            0x0F06F53973C364A5ULL, 0x52394CEDD862EF84ULL, 0xEF7E5400FA1AA11BULL, 0x26374FCE199452F4ULL, 
            0xC9604BE7B4ED8579ULL, 0x34B5EBBA96CB95BFULL, 0xA65108354495FE6DULL, 0xEE6CAB06637EBD9CULL, 
            0x395D29E755B06E14ULL, 0x923C9411BC225317ULL, 0xB3143D660E9CE68CULL, 0xCC2005EC179AD52AULL, 
            0x8B9F6E764EC541DFULL, 0x14F1B59E8B12B42BULL, 0x91A336C87185B65CULL, 0x2D1664E035DC20ABULL
        },
        {
            0xB1686DF8045985C4ULL, 0xB914243931CC18AEULL, 0x4B7ECDEC8287379EULL, 0xCD8DAAB50EB55DBCULL, 
            0xBD02EF357DCFD211ULL, 0x9408827033CA14A7ULL, 0x4DD3AFE0BD478813ULL, 0x5F3FE4EBA50F0BDFULL, 
            0x9200ED8C3D7AA469ULL, 0x910BB6B802A86748ULL, 0x27BE5FB75B6312C6ULL, 0x73770275AD89FB14ULL, 
            0xCE6EF645BDEFEC52ULL, 0x975DB0677A65E126ULL, 0x1ECD9B65666F17C5ULL, 0x91AB077FDB2D4337ULL, 
            0xA56EDD8138F922DEULL, 0x91A10F18941E763CULL, 0x8D59209656B23B32ULL, 0x32258763D8F85C07ULL, 
            0x82E7036EAFE41636ULL, 0x0AB75DDFCE2B29BAULL, 0x892C78C3040976C0ULL, 0xCE65A9DE6D98BD25ULL, 
            0x4318F91676565515ULL, 0xAB0FBEBAD7570234ULL, 0x456F21ECDAC89563ULL, 0xB259508CC402CFB0ULL, 
            0x270F776C8E11FABCULL, 0x876C0B6C528FAA36ULL, 0xC4338FCC4F71E986ULL, 0x38B373BC8FB2CEA8ULL
        },
        {
            0x26D3376989209482ULL, 0x7F13720FB5178588ULL, 0xC7659DD28213FC0AULL, 0xF32B4C06FFE5B49AULL, 
            0xF400D304BB5EAA49ULL, 0x9815E9E4C37C9CEBULL, 0x732901AD3523EBD1ULL, 0x5113386C68A862E7ULL, 
            0xA4B6C86846D79769ULL, 0x5775951A4EB59064ULL, 0xA409951D2DD06C0CULL, 0x3D0896CB9F0B940DULL, 
            0x5C3B012B0866CF8AULL, 0x3F13FC6260B54E5BULL, 0x10DD94D110FE96FFULL, 0x7608B74E3B4BC12FULL, 
            0x2707DCC5A63B638DULL, 0x56B46BE56A872951ULL, 0xC3FDBE19CA7FBCAEULL, 0x92A4C14CFF0A21D9ULL, 
            0xE03E4F017B7D9CBAULL, 0xE6C1646E1F402EAAULL, 0x6A025B053580C65FULL, 0xA6EED6F294CEF2F3ULL, 
            0x8893198FE94E4BB2ULL, 0xB350FE1ADE914788ULL, 0x16C23F7A36F5C237ULL, 0xBC99E8C127D25C16ULL, 
            0x11971BA66366C39DULL, 0xE02ECEF8CBE37CF2ULL, 0x3457FAD4877893A9ULL, 0x9415EE1BB9EADB9BULL
        },
        {
            0xD9B6EFA5251DCBDDULL, 0x424359B0294AA711ULL, 0x37D6676773870723ULL, 0x71138F43CEC4F35FULL, 
            0x54D6F903F6315749ULL, 0x5AD25C9CF42F1485ULL, 0x326A7CDB5C08E6A3ULL, 0x6B005DB9F629EA7EULL, 
            0x90D86D3F84783939ULL, 0x5CF6052187BC4C83ULL, 0x3C766E638F06695EULL, 0xED237EB658063A33ULL, 
            0x5BD2DA61EE83F505ULL, 0x49B5F0818239ED77ULL, 0x24783D0880B6099EULL, 0xD0A8B96BC82FA3CDULL, 
            0xE9A478DFD9B0F0CEULL, 0xEB13C3AF3438798DULL, 0xE661D7BD5CED16ECULL, 0x0034FFD142B55A5FULL, 
            0x24436DFCE19E4945ULL, 0x72B6BD17F44A589DULL, 0x0D843F34BC0B58E5ULL, 0x5AF68971FD90D157ULL, 
            0xC0FFCD7826A400F8ULL, 0x622F2FA14CBEC685ULL, 0xD8BBD251B8996259ULL, 0x7C34BC96BAE0415BULL, 
            0x5F30A294873A471AULL, 0x1338AD8E451B09F7ULL, 0xC128731ED364F305ULL, 0x2A66FD2480EA7790ULL
        },
        {
            0xB39B3FB77B1F598BULL, 0x4F8AE4D40C77574BULL, 0x88219F6B3BAB5229ULL, 0xC768241B84E1F7E0ULL, 
            0xD18540D2D8C1F2C1ULL, 0xB26330022FBDB5D4ULL, 0x9C0867E112539EE4ULL, 0x868A36E655C1708FULL, 
            0xA5D229EA0BDC1E51ULL, 0x88DE8FEC8C71E996ULL, 0x67AAB0F222DD3D82ULL, 0xD42362EFA8B58270ULL, 
            0x3A5C56A8A3EE1F04ULL, 0x4B3575449D56D359ULL, 0xFA2614CCFF9FB00EULL, 0x6EF20AAD50F30397ULL, 
            0x91C9100EDA006B73ULL, 0xA5E179CB383CC688ULL, 0xAB9A5B8C6AFE7459ULL, 0x73813626061C5545ULL, 
            0x406CF2E32A51FFF7ULL, 0xBF19B84951C0138AULL, 0xF3248C6F5E279CECULL, 0x7D9EAAC005B17EECULL, 
            0x253153D3DC5E6175ULL, 0x4C39439CAC729808ULL, 0xAA744F0FC117634CULL, 0xB89F772143DFF9A0ULL, 
            0x3AEADAD292546115ULL, 0xC74E4AA1CC43581EULL, 0xE59B1B5F42CE96B7ULL, 0xAC96915FAE53CEE0ULL
        }
    },
    {
        {
            0xF248591B9F2C7478ULL, 0xAC6F4935AA0DC6E8ULL, 0x52C6FEA02E9951C1ULL, 0x517493B8AED00FB0ULL, 
            0xB84B090A5ED7F7A7ULL, 0xF73441126A069E53ULL, 0x91C88017552F6812ULL, 0x8DDA265CB26DEF03ULL, 
            0x69A6B4E1683AEE4FULL, 0x8F7933C329F0F60FULL, 0xDF0FEB677E44B71EULL, 0x4B224BE5FF4B37CAULL, 
            0xC76B80F4292D5280ULL, 0x4C71D25AAA91D904ULL, 0x0723971A8F19C47AULL, 0x7AAAAA3667698C60ULL, 
            0x22E10796F2E353A4ULL, 0xE9C1DDBA056E1DB0ULL, 0xC94245C702E06353ULL, 0xA11F317F3A82F2A2ULL, 
            0xBE6A7F4C14AEAD18ULL, 0x00969A31488A68DBULL, 0x73C27B09282F87DBULL, 0x150993B86DB33788ULL, 
            0x5A2E9B69576A11CCULL, 0x16E8B3AAFC231466ULL, 0xAE4FF39B4EA596C1ULL, 0x81FD11B973C6497FULL, 
            0x4A353EED71DBE8EBULL, 0x2875E28CEC58CD40ULL, 0x7DC7972FDF596DB7ULL, 0x4487E0C77D998A87ULL
        },
        {
            0x39BBDC7A88DAEF41ULL, 0xCF91DBF55E599E80ULL, 0x018AA1B084493241ULL, 0x440EBED45DA562FAULL, 
            0xC6BF396A0C991B3FULL, 0xB5ADA14B9D203240ULL, 0xD856C68FCB6775E7ULL, 0x1EF6B1C6225B7932ULL, 
            0x297FC7A7C1F463FFULL, 0xBDB336943A46382EULL, 0xB0CFD00E72ED2CDAULL, 0x208F50B9E4FB89C4ULL, 
            0x49F8D2619CB79314ULL, 0x30CFE4B855F7E5FFULL, 0x16D2F3ABCB103006ULL, 0x032F4D2632C87967ULL, 
            0xCFB2642F065591F1ULL, 0x23711BC0E9A7ED47ULL, 0x4F9702029613107AULL, 0x2FC0D6F493316332ULL, 
            0xF4198290D0A68CF0ULL, 0xEA53483A53DE483CULL, 0xB46EF1AE9AF1CE18ULL, 0x65AFC920A9AAA762ULL, 
            0xD608BEDFE834E7BEULL, 0x1325B573E080F91AULL, 0xBA43D15235C3371CULL, 0x36D416A9686583FCULL, 
            0x24ABCF76F18D10ACULL, 0x2DE4D67F6E647839ULL, 0x8E9EDD3A8CA76968ULL, 0x0190E7DDF460010AULL
        },
        {
            0xFD79BEF6403E4DF8ULL, 0xCBC21EDDC4151C41ULL, 0xE4AD3E33D3B5B8EAULL, 0xFC663A346D7434C2ULL, 
            0x2AFE5E797C7B264DULL, 0xD0F75FD070CF224FULL, 0xD3FFF2D966395CCFULL, 0xE3C3326B2611A58FULL, 
            0x29F3A0FE8A112C6BULL, 0x6F25CB4A89CFEC15ULL, 0x5A19EBB32C8A947AULL, 0x73CBEB20ACE5E503ULL, 
            0x415045273515D00DULL, 0xC72E4C5DD489774CULL, 0xECCCEABFE84406CCULL, 0xFA122AD63E3C7179ULL, 
            0x9BD4FA70441BE4D8ULL, 0xC505314B91A43F8FULL, 0xB3470F69A52FC5ECULL, 0xF1053BD355E0B45EULL, 
            0xCA0A90D530A537B3ULL, 0xFCE1D20FAD84AEFCULL, 0x036591D0AE0149C7ULL, 0x4E5CF0D6F0183CA2ULL, 
            0x9B5D8C2E417C2662ULL, 0x5EC51BE07C9978C0ULL, 0x690357B648238C90ULL, 0x472E2DA33C196FB8ULL, 
            0x2AE8C00C9283CDE4ULL, 0x8AA98D99875C2E09ULL, 0x988372091F7B8D86ULL, 0x82E07AB79E14D8C3ULL
        },
        {
            0xB746D2DB380A0D95ULL, 0x30D5FB0CCF4630F3ULL, 0x80C2E75A27BB5767ULL, 0xEBD2E1FE2BADB61BULL, 
            0x4DA982DC2426FD21ULL, 0x02318F49E6A750CAULL, 0x27C2ACDDC9AA2C50ULL, 0xF9DB250E7A0C2250ULL, 
            0x9C9AFA8E00F18D0BULL, 0x282C53DCB6D9A877ULL, 0xAED1D345C23E6EBBULL, 0xEEE121930E3CC669ULL, 
            0x483D92E7508ABE28ULL, 0xFCD3AA9D641491D2ULL, 0xADE32F9124724480ULL, 0x5E2AC781E1CCF983ULL, 
            0x510CD3601172E7C1ULL, 0x592E1B601A2AE00EULL, 0x38C46A34A0439C12ULL, 0x6670ADA3BDC76AD3ULL, 
            0xEA94166AF43B4915ULL, 0xB83FEAF6E2320941ULL, 0xA692E63172180A63ULL, 0xF0C9570CDFAC2A0AULL, 
            0xC0F8173947371274ULL, 0x7E656998A1CB50B8ULL, 0x04EA005D4B29432AULL, 0xBD07E6449421B3FFULL, 
            0x46CFC5387B485532ULL, 0x651CC697654CF3DDULL, 0xB7FF9BB2ECD1A6ACULL, 0xA3246E77CB291D9EULL
        },
        {
            0x1FEB36D17137AB02ULL, 0xF4E431B26631DE0DULL, 0x0F1A9E484312C64FULL, 0xD55D8E2B3A8E5BD5ULL, 
            0xF2098C18A963EBABULL, 0x202C1E66A91F2ECEULL, 0x4EEC59E1D933CFE7ULL, 0x45EF5B756186147FULL, 
            0xB6AA7310495A60D0ULL, 0xA4F9053E5C0C6CCBULL, 0x08ED5A525CF1075CULL, 0x173924B625A4A7E6ULL, 
            0xE63465351E803D99ULL, 0x7626F0CBF240188AULL, 0x96C0B21E91D6E2E2ULL, 0x28C62E1EC6FCC365ULL, 
            0xC02D8904EBD8E2E9ULL, 0xCD73EF16CABF9AE9ULL, 0x64EE659F15F56FB0ULL, 0x7D3E43D62E649E85ULL, 
            0xAAF155EB8BEDB1E7ULL, 0x79D79B16E2B1ED02ULL, 0x42EDD87538910852ULL, 0x63CF670F83B13AFEULL, 
            0xAB6BD930EEF2E06DULL, 0xF747936FD3DD2978ULL, 0xE132CE1DCD3CC7B1ULL, 0x7BB1F99CC74F38A8ULL, 
            0x60F83393C65658F7ULL, 0xE76C26F727EACCCAULL, 0xCB74EF256B236651ULL, 0xAF0B3ED6ED1CD6CEULL
        },
        {
            0xA48776C138FE2F30ULL, 0xE214E57D7420E4C2ULL, 0xEA92C7466BCE33CBULL, 0x8D4B021C43ED9C2DULL, 
            0x0E620D0709296339ULL, 0xDF120BFCE514F3CDULL, 0xA8050CB508953F77ULL, 0x70A1B211422FB59BULL, 
            0x1410F3C9DA38BA30ULL, 0x0A4B95D1CDA360DAULL, 0xF727F583958995EDULL, 0xBD491288B3E7AA72ULL, 
            0xBC5F6530B9A7D648ULL, 0x353957A3802E70E3ULL, 0x0F2143BF1407754AULL, 0xFF1D3CCBFFF8664BULL, 
            0x6191E7BC947ED331ULL, 0x133E115260DA8DACULL, 0xADAFEAC2C0B63AB6ULL, 0xD9B3168645BB0D88ULL, 
            0x0D11395C0852AF01ULL, 0x67CB5D149A2929AEULL, 0x8C6F059B26C6AB39ULL, 0xF7BD7045345886B1ULL, 
            0xC37E8919491C5B1CULL, 0x41B2CC06BFAD3107ULL, 0x9AB04B73C9E5C642ULL, 0x9DD812AE7A39E690ULL, 
            0x65EE721F1600BAF1ULL, 0x5C05F32A95017DBCULL, 0xE6FA576D12C0BE0CULL, 0xF40B9BDB5A855719ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseHConstants = {
    0x03BB29A80C074E91ULL,
    0x77D8E36A90D39D94ULL,
    0xF0AC15B462D4A2B6ULL,
    0x03BB29A80C074E91ULL,
    0x77D8E36A90D39D94ULL,
    0xF0AC15B462D4A2B6ULL,
    0x6D1FF61E9B87A3F0ULL,
    0xC1AD858FCBA288F7ULL,
    0xB5,
    0x1D,
    0xD7,
    0x5E,
    0x0C,
    0x9C,
    0x76,
    0x14
};

