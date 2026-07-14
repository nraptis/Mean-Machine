#include "TwistExpander_Achernar.hpp"
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

TwistExpander_Achernar::TwistExpander_Achernar()
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

void TwistExpander_Achernar::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE0CC897EB982D9DCULL; std::uint64_t aIngress = 0xDAEA491D8E9E58A4ULL; std::uint64_t aCarry = 0xE05A32425E4A9331ULL;

    std::uint64_t aWandererA = 0xD8D22F1E29989001ULL; std::uint64_t aWandererB = 0xF267E704DF241C05ULL; std::uint64_t aWandererC = 0xD895654A5CAA15EFULL; std::uint64_t aWandererD = 0xECBB6B8F606145A8ULL;
    std::uint64_t aWandererE = 0x92805B3C96A220E7ULL; std::uint64_t aWandererF = 0xF49B9BEFF519E8F8ULL; std::uint64_t aWandererG = 0xD51AF35EB35CA161ULL; std::uint64_t aWandererH = 0xCC240B2FB9BF0B71ULL;
    std::uint64_t aWandererI = 0xB314F30916B84D4EULL; std::uint64_t aWandererJ = 0x959167386F78EE2EULL; std::uint64_t aWandererK = 0x901062E6FDBAF091ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16701393898237781399U;
        aCarry = 11737542991767447422U;
        aWandererA = 14834358754274239590U;
        aWandererB = 11255556549367505165U;
        aWandererC = 10073867970021053542U;
        aWandererD = 11259824533463926158U;
        aWandererE = 16179437780400218388U;
        aWandererF = 12931644193772109227U;
        aWandererG = 11814752332204993555U;
        aWandererH = 18112660726630271215U;
        aWandererI = 12532364204421005576U;
        aWandererJ = 17424231267039947959U;
        aWandererK = 10724756051376680733U;
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
    TwistExpander_Achernar_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Achernar::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xDAA166DAABA2D84BULL; std::uint64_t aIngress = 0xDC4D9518DAA7EF64ULL; std::uint64_t aCarry = 0xAEB7AF3E41EB8F7FULL;

    std::uint64_t aWandererA = 0xD83D5BDF4F41CCE5ULL; std::uint64_t aWandererB = 0xF706BE2F680461DCULL; std::uint64_t aWandererC = 0xE2DAD0925353259FULL; std::uint64_t aWandererD = 0xEAEA86FC3FF6EA5BULL;
    std::uint64_t aWandererE = 0xB2A21930436CA15CULL; std::uint64_t aWandererF = 0xE92E83FF62D32D43ULL; std::uint64_t aWandererG = 0x88FAF671E3224535ULL; std::uint64_t aWandererH = 0xAED25D9B5AA7B564ULL;
    std::uint64_t aWandererI = 0x9A7D0F2DFD157628ULL; std::uint64_t aWandererJ = 0xE8A6ADB348A87037ULL; std::uint64_t aWandererK = 0x92BC76CADC9AA8CEULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16275176150146939896U;
        aCarry = 12206714970418774327U;
        aWandererA = 10978229549179589812U;
        aWandererB = 9774384183386233141U;
        aWandererC = 18070380538255898165U;
        aWandererD = 11632651076795632686U;
        aWandererE = 15509760299589102384U;
        aWandererF = 17843969669520551883U;
        aWandererG = 15233138766729629599U;
        aWandererH = 15875312369988347210U;
        aWandererI = 15805181188771109007U;
        aWandererJ = 16077348664712392614U;
        aWandererK = 9742494779661489950U;
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
    TwistExpander_Achernar_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Achernar::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xFB2643D696622C93ULL;
    std::uint64_t aIngress = 0xC85F8715B6F1FBD1ULL;
    std::uint64_t aCarry = 0x84F80EF47FE6012BULL;

    std::uint64_t aWandererA = 0x80DED67879D4979AULL;
    std::uint64_t aWandererB = 0xD652D08CCA5B83E5ULL;
    std::uint64_t aWandererC = 0x8E93B33648F46180ULL;
    std::uint64_t aWandererD = 0xB803C6CE416BE638ULL;
    std::uint64_t aWandererE = 0xC55A97DC1BD478A0ULL;
    std::uint64_t aWandererF = 0xA394659FD02CAC5DULL;
    std::uint64_t aWandererG = 0xC97DE0E0B3A47991ULL;
    std::uint64_t aWandererH = 0xEDEC7CBDF4B6402BULL;
    std::uint64_t aWandererI = 0xA78BF127E60873C9ULL;
    std::uint64_t aWandererJ = 0xF5FEA4DAC5009036ULL;
    std::uint64_t aWandererK = 0xD6D83730D7F6F169ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
    TwistExpander_Achernar_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Achernar_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Achernar_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 1 of 33
// Exploration cases: 50000000
// Diversity score: baseline candidate (no earlier family member)
void TwistExpander_Achernar::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 768U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 341U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 171U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 120U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 622U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 490U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 34U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1763U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 352U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 728U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1414U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1079U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1136U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 404U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 279U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1040U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 300U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 324U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1327U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 504U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1819U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 563U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 608U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1267U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1081U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 566U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1034U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 379U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 88U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1601U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 316U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 860U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1827U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1983U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1526U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 252U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 181U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 578U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1029U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1265U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 542U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1502U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 321U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 583U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 519U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1052U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1043U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1158U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 470U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 630U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 539U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1342U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 162U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 734U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1118U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1567U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1416U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 418U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1391U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 27U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1481U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1960U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 332U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 307U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1985U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 467U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1552U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 59U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1197U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 902U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1340U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 282U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1099U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1086U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1798U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1613U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 291U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 804U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 845U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1055U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1931U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 713U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 754U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1706U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 656U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 485U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 632U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1329U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1240U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 991U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1644U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1821U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 547U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1679U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1672U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1367U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 878U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1349U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 236U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 229U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 971U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1886U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 326U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 850U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1557U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1955U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 137U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 785U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1637U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1970U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 91U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1302U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1636U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 935U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1120U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1630U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1958U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1686U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 419U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 892U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 8U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 899U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 471U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 791U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1562U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 993U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1114U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 797U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Achernar::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x9CAE618991E657FCULL; std::uint64_t aIngress = 0xFF98970B63EC7C62ULL; std::uint64_t aCarry = 0xCBF8899BA6AA16F0ULL;

    std::uint64_t aWandererA = 0xFF166AEDD6223FF1ULL; std::uint64_t aWandererB = 0xADC298BB7426F49CULL; std::uint64_t aWandererC = 0xBB5B65C35D50ADD5ULL; std::uint64_t aWandererD = 0xE03FF2D69FCD7C94ULL;
    std::uint64_t aWandererE = 0xF1F0F8F730C3711AULL; std::uint64_t aWandererF = 0xA70355AC573BB750ULL; std::uint64_t aWandererG = 0xF95515BC1EB99F2DULL; std::uint64_t aWandererH = 0xD446588FAD53E3DCULL;
    std::uint64_t aWandererI = 0xFB85496903A6C44FULL; std::uint64_t aWandererJ = 0xA6238AAD04C6D7E8ULL; std::uint64_t aWandererK = 0x9AF7AF19D1598E7CULL;

    // [seed]
        aPrevious = 11216090367363025652U;
        aCarry = 15875105945668943938U;
        aWandererA = 11069072991238335442U;
        aWandererB = 12882680148218542910U;
        aWandererC = 11395504563220059065U;
        aWandererD = 13369746144020157357U;
        aWandererE = 15993761416108478260U;
        aWandererF = 11806249577364613814U;
        aWandererG = 14642280396188180654U;
        aWandererH = 14682092244114639562U;
        aWandererI = 9854595537238341015U;
        aWandererJ = 18376897429617968013U;
        aWandererK = 14618194733597703836U;
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
    TwistExpander_Achernar_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Achernar_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Achernar_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 1 of 33
// Exploration cases: 50000000
// Total structural distance: baseline candidate
void TwistExpander_Achernar::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1255U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6354U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1878U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2148U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6739U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1069U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3370U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1422U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5071U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 560U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3627U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5330U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 753U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5731U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6626U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3580U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 387U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 286U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1985U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1114U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 401U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1285U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1071U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 316U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 526U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 767U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 517U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 659U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1807U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 507U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1109U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 96U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1030U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 485U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1346U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 966U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 1 of 33
// Exploration cases: 50000000
// Total structural distance: baseline candidate
void TwistExpander_Achernar::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1199U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 704U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5970U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3590U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 63U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6818U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7190U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7332U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7148U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3049U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2557U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1609U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4023U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6964U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7875U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1082U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 757U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1378U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1274U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 383U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1568U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 884U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1857U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 429U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 300U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1763U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1137U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 504U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1868U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1046U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 448U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 480U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 667U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 947U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 250U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 345U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseASalts = {
    {
        {
            0x2AEB6972B391CF73ULL, 0x6D089B169602D7D4ULL, 0xAA0DF7076BEA953DULL, 0x6D7FB9144F7A1AEDULL, 
            0xF031E7FB6EAD970EULL, 0xDE1D09A87563B1BAULL, 0x4216A563E6C12601ULL, 0xFD5FA83372246B6EULL, 
            0x248BAE2201070E26ULL, 0xBF113D80579C19D5ULL, 0xA09BDC22D9DD343FULL, 0x3A918A2BEF72ADCFULL, 
            0xA429B7595889D671ULL, 0x842AC851068D026AULL, 0x15871CF1A18A664CULL, 0xDA4E4BD3BEA325BDULL, 
            0x0DD9AEAF6807758AULL, 0x6CC1CF7F509D90B6ULL, 0x26A8BD4570FA6B3DULL, 0x3DA73DDEBD434D73ULL, 
            0xF38F3444E01B475DULL, 0xC9C2056C053AF158ULL, 0x3C7149CB71B4B3A5ULL, 0x8E4E0A81549D4810ULL, 
            0x02E01B4E5ED00061ULL, 0x88BDB4031DC2CF34ULL, 0x488B4ED2A0F0F85CULL, 0x07211A1DFACDBFA7ULL, 
            0xA6941749181B7822ULL, 0x8390618C1D395860ULL, 0xE479A03797D0D0C2ULL, 0x28EFD6E500924E45ULL
        },
        {
            0x000A9CD62D00C999ULL, 0xCBC96FC2658FBB3AULL, 0x565E828F6A11CF97ULL, 0x283CA4931669E996ULL, 
            0x10540ECCC3623755ULL, 0xBA3F338D2D9E333CULL, 0xAD1CF74395D97958ULL, 0x7BA7BE9C994D86F1ULL, 
            0x6DB49B944445A960ULL, 0x43F11C06329F6A42ULL, 0xA6BDE136F693CCC6ULL, 0xC0F6D7B3A78CFB59ULL, 
            0xAD3948535F647BA0ULL, 0x68CD4AF435C0D9B5ULL, 0xEBDAA1CD776E128EULL, 0xC44DDD23AEF0EE84ULL, 
            0x1C3AA3A45D4DE6C6ULL, 0xBE7056F99AE168BBULL, 0x0B11F4B1573069C8ULL, 0xDAF13E615922472DULL, 
            0x1C56B5C0DCE033CDULL, 0xF9B8FC16E44F29E5ULL, 0xF02F7232EF37E2CDULL, 0xAE2287F566038EA8ULL, 
            0xDEF5488BBEC7EB1CULL, 0xDCA13986385D4A05ULL, 0x8A1E34522F489811ULL, 0x07DBF7355FF23870ULL, 
            0x9A547C08B0C95A9FULL, 0x2C8EC4908FD159B3ULL, 0x49BE04333659E479ULL, 0x59FBEB392EFEC959ULL
        },
        {
            0x4160DBB2846207D8ULL, 0x37F61AE555F347B3ULL, 0x88939BB72262850FULL, 0xD5E73E59796AA985ULL, 
            0x28A73F22B7E5006BULL, 0xDEF70ABEEAAC18F4ULL, 0xCFA5E2DB91365904ULL, 0x66FCCCC4F41B6505ULL, 
            0x054489B3DDFE00B4ULL, 0x2EF4D98713C46717ULL, 0x34F0BC9A4615CAE1ULL, 0xD2E0B773996FE915ULL, 
            0x59D26262FF84F251ULL, 0xD07F6E1C2A50B216ULL, 0xA2319098438AC4CBULL, 0x07EB8F9460EEFB80ULL, 
            0xA9BDAC99FDE17EEAULL, 0x3613E9A6211FF0ADULL, 0xF0928D8CFC6121A6ULL, 0xF1B2167DE156B57DULL, 
            0x38C70EEB44AEB4B8ULL, 0x2498ECFD296417F4ULL, 0xAD3B4B4F95FE70CDULL, 0xCE21477FF9A79A62ULL, 
            0xDA7381AE3B80C638ULL, 0x3A4573A71E896674ULL, 0x570FCCF8D7CC57EFULL, 0x89DC540A33B510E1ULL, 
            0xA559D993A58F29A0ULL, 0x73BC7F782034B37CULL, 0x514A6622DA40AB0CULL, 0x9F5E0823DF6D4C04ULL
        },
        {
            0xB4CD54E24B9BB84AULL, 0xE205D0B6F91E5401ULL, 0x8C7092D483DD0C1BULL, 0x826C969B73779904ULL, 
            0xC4A61C4111CC544DULL, 0x01AA5C24CF504F5FULL, 0xE2271E2BD2CCA02CULL, 0xBE0F69E3EE79B565ULL, 
            0x1D586ED0647D669EULL, 0x882AE64E27FEB532ULL, 0xB54AE8E7AC1A25DCULL, 0x0BF08721F31326A9ULL, 
            0x4B97E84D7322323FULL, 0xEEBE4E319E6D6A54ULL, 0xEC2A7B4504D9321BULL, 0x25907B400FD6AEE0ULL, 
            0x0B644DAA7AA25069ULL, 0x4A9A2FCE2A8F9CFBULL, 0xA9630C21048C01CBULL, 0x7146078F4673B812ULL, 
            0xB940093ABDE0A430ULL, 0x3513B730441A900CULL, 0x62B5C5E22FF5DB81ULL, 0xEB28B170AFADD3FEULL, 
            0xD438701250E2146CULL, 0xDC69CE1D10B982D0ULL, 0x34C380C80FECD2CAULL, 0xE5E142AEDDEFB21EULL, 
            0x23485EE5C414277FULL, 0x2EA5542196FE27BDULL, 0xD685D3FBCEA3DDCFULL, 0x0C82E7F7190C59BBULL
        },
        {
            0x5848C003BDDBBBABULL, 0x70ACC6CE7A005926ULL, 0xA8986D5CCB2A6532ULL, 0x3534BE06CB7E0A36ULL, 
            0xE23702CB2A81D396ULL, 0xE7F95C20A2996299ULL, 0x02566A84EC7D90DCULL, 0x8FC79EF1A9A1262BULL, 
            0x14C7F04E8C6A2C5EULL, 0x9032A10569D3FDC1ULL, 0x7D217A196E28B85BULL, 0x1B3D387011E8C663ULL, 
            0xB301B67113A44F26ULL, 0xBBBB7A8B5A965872ULL, 0xF0D91DAAA19DD3C2ULL, 0x361EA172DE547F3BULL, 
            0x78A39CDB6F5B7F78ULL, 0xC82EE5BD26DF98FBULL, 0xA7401758D46E49C8ULL, 0xC41AE766B6C32479ULL, 
            0x0B31E15573B01799ULL, 0x5C8F23CF42EFD832ULL, 0x2C51B37418C1EBACULL, 0x55DD0A8F26D9163AULL, 
            0xA34CDABA74604C76ULL, 0xF8DC30252801F224ULL, 0x149A682DE24DC318ULL, 0x4656FD77B0459BB6ULL, 
            0x5654CFDD03E18E07ULL, 0x6D398D10D22BE079ULL, 0x58329D1E704A00A8ULL, 0xC1B82EB09E847A39ULL
        },
        {
            0x09939F9A7892F224ULL, 0x18765CC040C1FAA7ULL, 0x5712ABD2A277DB8EULL, 0xDF7FEFCFF0696C19ULL, 
            0x5A36B910A2ECB365ULL, 0xFF15B103B068462BULL, 0x8F712165E3F4A530ULL, 0xA4161D4BA99FA528ULL, 
            0xB18B41F5B40AAC15ULL, 0x0A549F6F4ECAB216ULL, 0x740D8987A1ECBC45ULL, 0xEDE49103A7F2DA7EULL, 
            0xA2EC32A20156B4D5ULL, 0x548FC698DCEF8446ULL, 0x52D4783902A48C93ULL, 0x196E98A9C00D6665ULL, 
            0x98C55677919C1F41ULL, 0xC2911C6422726489ULL, 0xA955B9AC331AF591ULL, 0x3DECBD597FDCC101ULL, 
            0x0CDB4C0EA09BC238ULL, 0x60E7B2AB889EE78BULL, 0x9DC3EA71CE69D092ULL, 0xB2B3757D5A996916ULL, 
            0xCBAE3D1CB9210DF6ULL, 0xDF34F4F137834C31ULL, 0xBC7925F8852F8002ULL, 0x7F2FFF848FEFD930ULL, 
            0xA67700920635938FULL, 0x3118AD1E3DBD79EAULL, 0x10727CC091C11675ULL, 0x25087593D157C9B5ULL
        }
    },
    {
        {
            0x9792153E483B6798ULL, 0xEC2BEAFABB29652BULL, 0x859DCC88F43DADF8ULL, 0x3461AF84600E6FB6ULL, 
            0xDA9B3B46BCD3AE07ULL, 0x438ACF6C899C4FB5ULL, 0x15F2764F2F153A56ULL, 0x2EA13037D14707A3ULL, 
            0x116EBFA52FF6DB8EULL, 0x577CAAF7B1F9D558ULL, 0x69F2EDB151929D6EULL, 0x9D53DF192B62F4B0ULL, 
            0x7540F86FA2B6B12AULL, 0x61E2E87A0DE64E5DULL, 0x7580042B1FB32D0EULL, 0x09EB3D67C559C887ULL, 
            0xFB12729211EE6A51ULL, 0xBAE8785B2A8043D8ULL, 0x5777D6B0A37EEAFCULL, 0xC96E471B16884E5CULL, 
            0xA284C7C5E724C741ULL, 0x3AA8D2B04B37C6C5ULL, 0x88D2CEE05A6A28F4ULL, 0xC343DCA11E735A66ULL, 
            0xAB0AE961A59FC445ULL, 0x6CA35304B4CD425FULL, 0x21A0A52894EE9C78ULL, 0x47E2B8F7F3C0FC3BULL, 
            0xAF3D6B8ED5B44C4BULL, 0x5331C86D47ADAC7AULL, 0xA6E1EC6729AB2B33ULL, 0x9D7749384D57F911ULL
        },
        {
            0x3A8595FE3EC1CA59ULL, 0x9EEEFB5C0D085A10ULL, 0x7A50BAC2A36A9F49ULL, 0x80F18FA587D1C9DAULL, 
            0x741576ED2626354AULL, 0xDBDC3647555005E4ULL, 0xED2878F27A3FBE69ULL, 0xA78578F7DF530A2EULL, 
            0xB0A33DCA62F59FA4ULL, 0x50DF2E8DACBA4E6FULL, 0x362C68398FC95F00ULL, 0xFCF1CABC04529246ULL, 
            0x41679FAE4C6E1637ULL, 0x0984353769A8FCFBULL, 0x8704AF60D6C1763FULL, 0xAC5D568B342D56D4ULL, 
            0xDB62844F7CC66B34ULL, 0x71D082A09D25D83AULL, 0x104F4D39794750C2ULL, 0xF2E68D991DE61DC6ULL, 
            0x69195183E1D282AEULL, 0x4EEA0827613CB44CULL, 0x0396DA432F1170B1ULL, 0xE21ACC023A752EC2ULL, 
            0xB637B5A9ED4FF869ULL, 0x6DE89D019C37C03BULL, 0x47C0E6051EB8BA0DULL, 0x86CB279BEBACB08EULL, 
            0xBB7DDBB4FFB5DC61ULL, 0x64110A59A82551B9ULL, 0x39870BE82B31DB6CULL, 0xD4B2E51BB877BECCULL
        },
        {
            0x5B73F5C63A2FE341ULL, 0x3D601E08EBEEBF29ULL, 0x99603541613CE4CAULL, 0x9E4A325C93072BFAULL, 
            0x0AA00D074B9CCC10ULL, 0x159847F23685A837ULL, 0x0A974686EF3B10E9ULL, 0x16A61C47D5995E6DULL, 
            0x9E6C92FE1EADFD96ULL, 0x1ADAC8B98588E099ULL, 0x8EF96E51F7393045ULL, 0x8BF23E76F1E133CAULL, 
            0x2A7AA54359D9657DULL, 0xB86EE5DB77658692ULL, 0x261A6312DE652372ULL, 0xBA3AAAC6E32EFE14ULL, 
            0xD8FB9401760810F3ULL, 0x1827A4C93FDCE242ULL, 0xA24A48D4E25D3FE0ULL, 0xA357D1BFD07CEE36ULL, 
            0xB0DEBDD86945A559ULL, 0x7574529DF9537741ULL, 0x2AB59D20405E80F6ULL, 0xD8865362E8AF4BD9ULL, 
            0xFEEFA9E954FE806CULL, 0xE1B145A1A0E97B4EULL, 0x7B00ADA75D8F718BULL, 0xC5AF7A316A4B4811ULL, 
            0xDDBFDAFA3427A548ULL, 0xB6EBB8F1E0C00659ULL, 0xD94DF66A9ADD70BBULL, 0x85031865500549D9ULL
        },
        {
            0x0529820FB52209D1ULL, 0x07EFE76E7E13A3CBULL, 0x7004DED8192E73E1ULL, 0x38E1E18CC63CF8BCULL, 
            0xE349BD4E3D7F57C7ULL, 0xD68F1EB646E28D12ULL, 0x79825D4DFF9C66E5ULL, 0x8B65DBD8BABF0321ULL, 
            0x523BF340439D3F6CULL, 0xF7E23376ECF9D5E7ULL, 0x663C3AF03CF10D72ULL, 0xCE4AFCCB49F5B638ULL, 
            0x230B8F2D4614DC5BULL, 0x28FACF848B346AEAULL, 0xAB9D7ACB86114707ULL, 0x0EA9F5FFFA815BD9ULL, 
            0x8C87CD6EB5CD6FC3ULL, 0xCAB2187F99B69E26ULL, 0xB34F5E5378E09C53ULL, 0x4B91B435464F1211ULL, 
            0xE6F5CC29C7A94DE7ULL, 0xB7E765AC25F41BFFULL, 0x2908A807B1BFE9D2ULL, 0x573D56BF2BA9AD33ULL, 
            0xE4574FEE71F3E129ULL, 0x877EB4FEFC73A4B8ULL, 0x752F2816125A95CCULL, 0xC37A240CEEA37F3CULL, 
            0x934F148451BCEC4FULL, 0x14C9A19D2E86E2B1ULL, 0xD792B5F41CC91410ULL, 0x7FD7ED7BBC05A9DFULL
        },
        {
            0x4442EBE899D22AD0ULL, 0x440EC3CBDE39BDD3ULL, 0x17F7C71C82584500ULL, 0x8BB7C09CEDDCC694ULL, 
            0x43C18F75D6E6FBD7ULL, 0xAABB9EA5C5492BF2ULL, 0x2EA5CA54F160288EULL, 0x474217B038329699ULL, 
            0x9CCD53A5ACB30AC0ULL, 0xC032FB00D10685F8ULL, 0xEE1AE68D69601754ULL, 0x21670122A5D285F1ULL, 
            0xDA9501D4E5A2BE55ULL, 0x1EA45D90C179FBF6ULL, 0x48D5933E3B87743DULL, 0x72BAEFEA66C2AB16ULL, 
            0x1F00EE480747BE17ULL, 0xADAE54D8993B52CEULL, 0xF54208BEF1519A14ULL, 0x63B4A88BA8BDB753ULL, 
            0xF17F2C0A0C1CF345ULL, 0xC8444661EF1AEA80ULL, 0xA8492C6ACDD685F8ULL, 0x7D64B9C4E2C5E7FEULL, 
            0xAA29AFD3008A78EAULL, 0x1ADE5218C5452B9CULL, 0xF58B72C700206429ULL, 0x071CDD38421587CAULL, 
            0x310562C95EB4721BULL, 0x2F1A7D4DF4F23109ULL, 0x679583F721DC8ED1ULL, 0xFBE01AF9EAD14DB6ULL
        },
        {
            0x005FD4088831D6F2ULL, 0x59784B2BFED72351ULL, 0x7227385E890D0DDBULL, 0x5D0DD3ABAF2ECD25ULL, 
            0xE6C0FA4E9B108B90ULL, 0x0468A2CA0962C0CEULL, 0x55C1A85102E34EF9ULL, 0x65755CD64A638125ULL, 
            0x5649287C57B9FDCEULL, 0x3F4A3663770BB0F5ULL, 0xD82664886D49AA93ULL, 0x03BBB64E244EB4E6ULL, 
            0x2A4D0C62106DFA3BULL, 0x69E43BDFF7870D55ULL, 0x57571EB502FF1ACFULL, 0xFBA2CAA64F11C751ULL, 
            0x251CB4793E564A8AULL, 0xB4274D6F8A601CB9ULL, 0x520D556A4A72F112ULL, 0x4B127E789485558DULL, 
            0x87DF3806E04A4F6AULL, 0xE34298AFC787B9C8ULL, 0x6E54744B419DCE32ULL, 0xF7DD8EDE6EA2A188ULL, 
            0x3F381EDF8FA7F757ULL, 0xB57C00435755B8DAULL, 0x57525043F53AEDD1ULL, 0x2713AC6DD6819489ULL, 
            0x9D118CC15DDEF56BULL, 0x5D70F6258AE1BEC3ULL, 0x79757E7D7BDE51ADULL, 0x87D5938F6A8681CBULL
        }
    },
    {
        {
            0x92DD4981AA43F576ULL, 0x8C93B1B1913B6A71ULL, 0xAB995E77E8713D82ULL, 0xEF2A95F01847B615ULL, 
            0xCD3AC09E5C2639C8ULL, 0xEC296D3D9BAE538BULL, 0xFBD19B75AF3927D6ULL, 0xD4BC95211ADFD4B3ULL, 
            0x5111914DC21E6838ULL, 0x9786228753F25053ULL, 0xABA667F86CEFA447ULL, 0x0464D31BCCE38AF6ULL, 
            0x3D5EBB43A98043A8ULL, 0x307538CC2AAA1944ULL, 0x6E87A7EA513EA876ULL, 0x7DBF24171F4E59A1ULL, 
            0x4F962153C43F271BULL, 0xB799285D1ABF43F6ULL, 0xC4947C940B8270B2ULL, 0xFEC376142D1AEE59ULL, 
            0xCCD09B90F2B73249ULL, 0x2233C1D11BCE8C81ULL, 0x116F7D30F5296C1FULL, 0x7FB1D9B46073A0F7ULL, 
            0xCDB07C6164626791ULL, 0x5B95E8B1854C1099ULL, 0x99D9A2E96C2F941EULL, 0x10C7E078716D494EULL, 
            0x85B27358E2C13FF3ULL, 0xC0BDD188A5BE05F1ULL, 0x8488A0C2C9BCAFA6ULL, 0xC55CCFE950FB438DULL
        },
        {
            0xF0D0E6CFDF1E6BEAULL, 0x3BAEFB8A43C7A55DULL, 0x758193A3000035ACULL, 0x9970E528A6E7FAE4ULL, 
            0x6DACFB38DEF2CB74ULL, 0xD35FE68DA36B8CBDULL, 0xE76C23A533697A20ULL, 0x27B68AFFD4AB819CULL, 
            0xBEF41AA90F9DB143ULL, 0x50F8E30D11E723D5ULL, 0x7C11F157D77F182BULL, 0xD9CB659E242FF365ULL, 
            0x4F3E6B3BCBFD3D0EULL, 0xA2B058212183F0D7ULL, 0x6999E652998AAE69ULL, 0xC0330DC0905B3834ULL, 
            0x4217AA689C88284AULL, 0x768FA802410B46E6ULL, 0x0AB999965A90681DULL, 0x25B42277563E41CFULL, 
            0x465A4F2871C15E6AULL, 0xAA749DBA4D2C1669ULL, 0x14DD7B109112ACC9ULL, 0x5DD63F53E83B0D68ULL, 
            0x9F5513D6DD1DDA12ULL, 0x17DA379EAD9D60EFULL, 0x2126B6AECC1268DCULL, 0x78120971F8B3871EULL, 
            0xAB086F0B70F213F8ULL, 0x54CC685DFF5DB930ULL, 0x29BCED6C0630819BULL, 0xBD39C29BE141DDE5ULL
        },
        {
            0x7CAD84751CED239EULL, 0xC3F533ABBC296F6FULL, 0x7050B9E15B1413EAULL, 0xD3A6465B811C0A99ULL, 
            0xF712EB7AE1D0C619ULL, 0x3328F2071AE57E16ULL, 0x52954A8FD0155F11ULL, 0x317E67DDF68E78BFULL, 
            0x83177F50191A48D8ULL, 0xA514CE6A16814EC6ULL, 0xD365898E54459EC8ULL, 0xD54256D46A7F7AD0ULL, 
            0x5A10C19935A4C2C1ULL, 0xFB7F4ECA2D0E8910ULL, 0x524731DE7F13645EULL, 0xF7876E9FEC3A4DBEULL, 
            0xAC60C611A23036D4ULL, 0xB4CDC0B8F0A529FBULL, 0xF332EB6D7FD15EB6ULL, 0x332AFEDB9C39FCBDULL, 
            0xBEC4009F99F44A16ULL, 0x807183CC45AD5C9DULL, 0x8BB6897943B2062BULL, 0xE4C81D6893594967ULL, 
            0x7BE303B5184CA2D3ULL, 0xC8F8440AFDD6B23EULL, 0xEA8F4A01CDB98059ULL, 0x2A14878D7BAEEED5ULL, 
            0x7D1D45FBCCA6A588ULL, 0x1ACF80B173471073ULL, 0x945300C170C14A47ULL, 0x3CD7C57D2EA6EDA3ULL
        },
        {
            0x621A3C41F568D37AULL, 0x846F97DFE8156FE5ULL, 0x6849F1B69A1510B0ULL, 0xDBE027DF01BE8DB9ULL, 
            0x42DF07F85EC6630EULL, 0x99B6E886D55A4D4EULL, 0x283624C461D2DBACULL, 0x60F5C909EBFCCB88ULL, 
            0x8118B32B284DF69CULL, 0xD55F3299DD648B39ULL, 0xDA07FD9B5C286ACBULL, 0xDD49A0BAA1F04513ULL, 
            0x75A4DF11A04F1706ULL, 0xBB26DCF6D33C37B9ULL, 0x4DA5189B986D94CBULL, 0xDC1391D22B963BFBULL, 
            0x7253618976168A97ULL, 0x5CAF7FDE6AB3B47CULL, 0xC8F1FDFBAFC35342ULL, 0x98F3699A636EAB59ULL, 
            0x1B13308E6AA7BDD2ULL, 0xA463866ECF461D94ULL, 0x643B033A6FED5BCFULL, 0x1A0CAAE9D9DDC2B1ULL, 
            0x4DE61BA09ACE923EULL, 0xA64C6274BF79DF79ULL, 0x927B1FC0061CA235ULL, 0x78ED742FE62C5032ULL, 
            0xF063752922C386C8ULL, 0x6CBB656370FCA7EBULL, 0x921D0842C22E6441ULL, 0x943CCE1EB48B1538ULL
        },
        {
            0xF6D4933FC3BD9BC9ULL, 0x62D2A075352D51DEULL, 0x7E62EFADE776038EULL, 0xD7687AAF0131DE45ULL, 
            0x83C124D208A48EB4ULL, 0x0C4576C99CA7A3F9ULL, 0xE4348FE6F16EB8BAULL, 0xB5523A08453A30E2ULL, 
            0x613D8094443D6EC2ULL, 0x9E4BD1F471F44966ULL, 0x2A924FEFBBE24FDBULL, 0x647196FBCE43232BULL, 
            0x24C554FA32A4AF15ULL, 0xC6E55086A9FB66A7ULL, 0x836C1E14FC47BBBCULL, 0xB60B43C636625E99ULL, 
            0xA9235F0A5F20B2C1ULL, 0x029C377C58E95488ULL, 0xE3BEE14242AAEB16ULL, 0x207BD67D16A198D8ULL, 
            0x0700E9D60ADF57A6ULL, 0x66DBBD4851B92D5EULL, 0xAB086DA636078EDEULL, 0x90CAA04B5D405000ULL, 
            0x3067079DE1B3BCB9ULL, 0x1EED41AF15215DADULL, 0x020BEB6015DCF4D3ULL, 0x7AA2DD4ADE4CD773ULL, 
            0xCDE6ADCA7CCEA798ULL, 0x3056900F5ECC7306ULL, 0x6DF680CF7BCE8BA3ULL, 0x23ADAD9AD52BFF9FULL
        },
        {
            0xB6510CBC8C48EF12ULL, 0x2318D0960D257F0DULL, 0xF4D318238969BF0AULL, 0x420B8010F156D41BULL, 
            0x9A93D9DA9C629870ULL, 0xE175099C7A4E806BULL, 0xB12F5B8E524A7155ULL, 0x1CC1BF748C692090ULL, 
            0x165F5F55EF39BCF2ULL, 0x751EED08CB78C43BULL, 0x8E3A5AEBAAD59FCDULL, 0xF349659577AC7DB8ULL, 
            0x03C3238BECDD0552ULL, 0x90A760F89B9E0CF7ULL, 0x9F70E5E9736E936EULL, 0x6887E84E077CDD3EULL, 
            0x87406141919D0E26ULL, 0x10F646F35E606884ULL, 0xB85B76DDF14AB0B9ULL, 0x064ECFC5205F17CDULL, 
            0x7A2E6719F1118618ULL, 0xD86D0CF7CD7678C7ULL, 0xE0A3C0FC2BC2269FULL, 0x0D62485484847172ULL, 
            0x039886E20F321342ULL, 0x223B7D3A76B54B79ULL, 0xFA116E08CF93BD99ULL, 0x47A3C1C740B039C4ULL, 
            0x72DC76784BE81A72ULL, 0x2F40861082911715ULL, 0x025BD4F7074BA204ULL, 0xB761EC87A97BA7C8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseAConstants = {
    0x0366EB650CF7CF40ULL,
    0x05E1CC95AE0A0498ULL,
    0x4F09A1A44B7427CCULL,
    0x0366EB650CF7CF40ULL,
    0x05E1CC95AE0A0498ULL,
    0x4F09A1A44B7427CCULL,
    0xFBE710435674D2A8ULL,
    0x8AD9930E9F2DBBA7ULL,
    0xF7,
    0xF8,
    0x40,
    0x93,
    0x8F,
    0x72,
    0x57,
    0x60
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseBSalts = {
    {
        {
            0x641BC0BB8E952939ULL, 0x5318318FEB5DAF0BULL, 0xF7802EF9342B36DAULL, 0x3FD359B178C7DE8CULL, 
            0x885A54B34F1D8A67ULL, 0x69F6344E548938ACULL, 0x94C11D0A0BA28C4EULL, 0xB67105915A269704ULL, 
            0x04971D0AF9E4DFA2ULL, 0xCBA10DD8E817585AULL, 0x6DC97909B58B58A6ULL, 0x7C58E335CBD8810DULL, 
            0xDD284C1BFE96ABE6ULL, 0x6DF5E230A2536772ULL, 0x838F53FB7697B7B5ULL, 0x68D3D722849A7557ULL, 
            0x4FAE42E5E7D68226ULL, 0xDB82CC1EA71E3D5BULL, 0xF85ECE554B1663B9ULL, 0x9B6D117283D34B2CULL, 
            0x5E62D75A23E82202ULL, 0x6EBC507EB5E41224ULL, 0xF16490ED7856D505ULL, 0x20ADED4335C75A76ULL, 
            0xFDC2D0DF45BA2435ULL, 0x469CCF3C3FA64B36ULL, 0x171DF9408C8468E3ULL, 0xCA666F04EE25143BULL, 
            0x4596E5136140C330ULL, 0x024E0D736E980482ULL, 0xF22BD79702345B28ULL, 0xDACC18E6F81372C0ULL
        },
        {
            0xBBB918B0FD1373F1ULL, 0x5EBBB247513EF569ULL, 0xF8ABDF5122E0F2A9ULL, 0xA00FF98D77E458ACULL, 
            0x3F261A7B14574049ULL, 0x74CDDCB79D6734B7ULL, 0xE5E49F6271797351ULL, 0x511FDCC4744ED490ULL, 
            0xFFF30022017DAFA6ULL, 0x29893DC937D92662ULL, 0xDDB803372B864E32ULL, 0xD9B9A5550EED4019ULL, 
            0xCEBF79B25A22A7E5ULL, 0x59C0122076E0BAD8ULL, 0xB85BE9BCE55C3D55ULL, 0x62B97151E6DE5E49ULL, 
            0xBC360D4A4EB5C180ULL, 0x00236500BBC35634ULL, 0xBB8985B8C2135E9CULL, 0xBBA862F551BF9FA5ULL, 
            0x937EC6117520D833ULL, 0x70F4D7E1B4CA83BCULL, 0x764F3D57B6E486B9ULL, 0x567ECBA7108593CBULL, 
            0xCE3983A363AD034EULL, 0x58F4166D67471A7EULL, 0x01D249A8F709BB79ULL, 0xF459A7B6AEBE1182ULL, 
            0xB1BBEC7A11ADFA11ULL, 0x2E91CFF3D79DDE77ULL, 0x451A47585EB43AF1ULL, 0xD56B437851E64743ULL
        },
        {
            0x79C03A8F99652373ULL, 0x7CF364C224C499F6ULL, 0x5E4C667AC5884E9EULL, 0x8660BD9D05B94CE3ULL, 
            0x9CC88E231D748A3FULL, 0x5309A2B0BBAD0C59ULL, 0x101BB566FD6576A1ULL, 0x7C9A4E6BAEDA0826ULL, 
            0x6D110162E7A982FCULL, 0x5999BCB1C8C8EE5AULL, 0x563EFE8B7AFDFE5DULL, 0x5411AD7765564204ULL, 
            0x23A768491207D7BDULL, 0xE08032B0E2BC189EULL, 0x3103A9DB90B5DC02ULL, 0x7695E24EBEC7018DULL, 
            0xF4F8B1857072FD36ULL, 0x980E6E43AF27D6E1ULL, 0x2FD1DB7AA9F35E4DULL, 0xEBCB3D235D835CDFULL, 
            0x4FB1604D88CFC37AULL, 0x1145756701A0B6CDULL, 0x0ED8AAF8EC3D93F0ULL, 0x1170D3E4BC007BB3ULL, 
            0x7EDFEA6766990F50ULL, 0xA7321B6E744B75CEULL, 0x6343BA9896817CF3ULL, 0x6659C5C2C58FE9F2ULL, 
            0xF3AC3D7B0061C457ULL, 0x267A931FA41B3EC3ULL, 0x1BB87B2EB021B79AULL, 0x861622E51BAF80F9ULL
        },
        {
            0xB999770FAE0FCD24ULL, 0x8C6F78A5ADDF9D6DULL, 0xEF9C77F686CAC849ULL, 0x20D08586FF9470B2ULL, 
            0x089DD8F4AF63232DULL, 0x5133D0BAFE8D16A3ULL, 0xD4AC3F9654C6BBE7ULL, 0xCEE696623B483DE8ULL, 
            0x6068FC1305D4D16CULL, 0x31071F49FDDF7028ULL, 0x385FF531452DC446ULL, 0x542BC96F120AD880ULL, 
            0x82794E8974BC89B1ULL, 0xFAA68F9EFA0EF5EEULL, 0x6958EA6B84167E34ULL, 0x474129D3BDC57E96ULL, 
            0xFC6C4CC1725188FEULL, 0x4D479167D02858BFULL, 0x3AACFBB037BE043DULL, 0x1FF4F95F31F31775ULL, 
            0xE618B652AEF8AA5FULL, 0xD452A488D1E15712ULL, 0x5982449D1DC49097ULL, 0x0813DFF5EB3C05D5ULL, 
            0x67A63CBADCA0AD7CULL, 0x862C6E91D70708A0ULL, 0x8AD0175FCAD22560ULL, 0x5B03B3A366F492C5ULL, 
            0xD67226F6023E1CF7ULL, 0x0BC34EBC9104F9FCULL, 0x61624B88E00D0396ULL, 0xCA06CB616C03BF1AULL
        },
        {
            0x25FABF4AF932C8FFULL, 0xD206530A0FD578D2ULL, 0x7F6F6B8EE5C9728EULL, 0x50D4E9F2BC40A3CBULL, 
            0x794C173064793976ULL, 0xB7DDB8D3C8ECE3ECULL, 0x27A21F23B903FE95ULL, 0xBE6A6FC6973B9707ULL, 
            0x240B56C3BE966394ULL, 0x53BB6D9CD0CD2DCEULL, 0xAFE919C80D262D6EULL, 0x95C8044A6A5ADA69ULL, 
            0x5CA4C3A5AA40DF20ULL, 0xB8E70E9CE4B8DE48ULL, 0xC945A1160059D59DULL, 0x815203D264B5C7F6ULL, 
            0x64C6B2213CDF920DULL, 0x648CCF7E9C23897BULL, 0x11BA8030E9D056B3ULL, 0xE85827F2A04C52BAULL, 
            0xAAAA0A25FEF7B7D7ULL, 0x5022CF017DB173ECULL, 0x52A59F77347AA68DULL, 0x615FC19EBEB20355ULL, 
            0x72FAA9DF98BC6287ULL, 0xD9E4CBD9094419A0ULL, 0x32466A23D1F6D9A9ULL, 0xAB68642C982FA9A7ULL, 
            0x274CD6000CC95EFFULL, 0x81885DBBA4E7AA0DULL, 0x8487A354376C595FULL, 0xEC95BCA5BDEDD745ULL
        },
        {
            0xF2B330162E6D4518ULL, 0x2611224A681D205BULL, 0x437A97D4833E5E24ULL, 0x32B3D47CBF86C3FBULL, 
            0x05C562586C207296ULL, 0x8E83E2EAF9C57F4DULL, 0xB2D39DFA59EACAD3ULL, 0x0F9E97C95883BDFAULL, 
            0x45F37F2748DED188ULL, 0xCF379877702D9F02ULL, 0x6BDD960D4283E910ULL, 0xA79E6C9E491D0DDFULL, 
            0x7B07BCA55F90E4F2ULL, 0xC8277674B49D87D4ULL, 0xAA0778AD01F8382BULL, 0xE9A10B1F302F1E11ULL, 
            0x8B2006E296D109D3ULL, 0x860046820272BB70ULL, 0xD4D62C06BB36370AULL, 0x651A060218D8AC18ULL, 
            0xF0BC48B824E8116BULL, 0x806EBA7E3DED2AE9ULL, 0x9B38910564A711CDULL, 0xE29B7DD762D181D5ULL, 
            0x678E825F43033F24ULL, 0xDF8D0BE7593C8554ULL, 0x83545D93BCBB8FDCULL, 0x564867EBD779AFA9ULL, 
            0xB32178B517B345CCULL, 0x2690EE66DA0CA883ULL, 0xA077111357715850ULL, 0x801B3CC548F7A160ULL
        }
    },
    {
        {
            0xE33DB5B6F7EA257DULL, 0xD1923E1A68172BD5ULL, 0x8A2E856183636345ULL, 0xC2A1E5D0271563F6ULL, 
            0x6004029FC516214DULL, 0xA4E14DFEA1348E8EULL, 0x27AB8BE8FFC69A68ULL, 0xF30540ACBEEE9942ULL, 
            0x6391F6E9555C3A94ULL, 0x13B4B71BA42A0CDEULL, 0x43ECCC78D87C252DULL, 0x5A56C117B8EA49BEULL, 
            0xF184C7C5A4CF5AC3ULL, 0xE315771030266E26ULL, 0xA3E5862CCA2D0C98ULL, 0xE80C99FB7ADE4FC5ULL, 
            0x8AFE87D6F2D76E74ULL, 0x8E9589E522C5EA56ULL, 0x42588BCD546670B3ULL, 0x1F31BBA216BC4E7DULL, 
            0x262BDBAF73934C80ULL, 0x71FAA9E6098BF48EULL, 0x56F45F53903D40BFULL, 0xF572ADEE466CA873ULL, 
            0x8A4142373C262465ULL, 0x13F30FD0FC5A9874ULL, 0x838BC9EC0EDA1C92ULL, 0xB9C746934B5AAD3DULL, 
            0x892A0730FD1AD088ULL, 0x07DCD51A806612FEULL, 0xB44305F19DA98EC6ULL, 0x31F7DFE4255E078BULL
        },
        {
            0xFA7100A92F98F71EULL, 0x78B957B35835563CULL, 0xDE977A23485CC2C5ULL, 0xA8C08EFA4C365760ULL, 
            0x1C2D9C15A89AEEADULL, 0x9921655F23AE15B2ULL, 0x066E5DA1AF6C2B63ULL, 0x365F815F448A3D29ULL, 
            0x1B38479453A3903CULL, 0x658213A0D74D83E9ULL, 0xEF8E549854ED7C46ULL, 0x05DCD2BEAE3F0BD8ULL, 
            0x3DDBCC92B7B364E0ULL, 0xFADCE16035763C32ULL, 0xF5603BD478A60C79ULL, 0x5956AFA2955FA877ULL, 
            0xF2731CFE3A7990A4ULL, 0x88BD97D0A9F2877DULL, 0x24C9DF972CE1292AULL, 0x33ABB6FCACBBA96CULL, 
            0x64B6AA21EFBC91CBULL, 0x36CB02B26A3CDA76ULL, 0xCF9FBCE46F36FF72ULL, 0x51418BDF615B4A8FULL, 
            0xE23F2695D9D8B30CULL, 0xADFBB7C4B379F866ULL, 0xB77AC4406B06BB8EULL, 0x7F49C8BB158D36F5ULL, 
            0x61DF1A6D0F2F6099ULL, 0x747746750D9AD8E8ULL, 0x4792E4964670D949ULL, 0x52E7F3991966D9B4ULL
        },
        {
            0xFB721F9D58C1D76DULL, 0x54A4729F591AE309ULL, 0x13E24336908425C2ULL, 0xBB20813683776EADULL, 
            0x83E931067E8FC325ULL, 0x733E3181884D8754ULL, 0xF3DFE35DA9F34818ULL, 0x5CD5728008464F81ULL, 
            0xE2C36CE085830FCBULL, 0xB8B1D38CB1B2ACE9ULL, 0x01364E429EAD626FULL, 0xEE968E20FDAB380BULL, 
            0x3742C133C06797C5ULL, 0xE2274E3E38E31002ULL, 0xC315A6970C405CF0ULL, 0xDAC5BD5AD25C462AULL, 
            0xC5595BFD67964EF4ULL, 0xDE7F9B3206BCCF31ULL, 0x162D0443BB5FF80DULL, 0xE0FA7CACEB266F2AULL, 
            0x73D1B2A0655972EBULL, 0x22443DFA3868BB37ULL, 0x5338C884CB7152E4ULL, 0x83E0222C9688CF36ULL, 
            0xC3A4CFF5D723BA75ULL, 0xC0A2FE7A432D072FULL, 0x51FAB6B7DC25CE87ULL, 0xE647816A0560F1F8ULL, 
            0x565931CE04ECAF14ULL, 0x713EC2D9350DB40EULL, 0x168C9EF17F45D806ULL, 0xC91E5F0976981DC9ULL
        },
        {
            0x22948D54347D3531ULL, 0xF1C074EF6398662EULL, 0x0C679A3F67DE4090ULL, 0x775FACFF54526323ULL, 
            0xEC451DC88A7687E9ULL, 0x11D8D951DA368982ULL, 0xB0366F1D531DB407ULL, 0x7D4F7E56BB0B37A1ULL, 
            0x3A2E3183BA47CF27ULL, 0xCA1F9A8C6A624537ULL, 0x5EE99D5BCA6D24C3ULL, 0x9658B8A38C70BE03ULL, 
            0x7A01FD91F55AB7CBULL, 0x4A8CE1763CBF61CBULL, 0x4142770F5819A20BULL, 0xA0B6576A1DF8DEBCULL, 
            0x2E5BEECBA9151CB7ULL, 0x2EC73A9073461EF6ULL, 0xA74B0D2FA42796F2ULL, 0x9BDEA2370F2BB272ULL, 
            0xDE3D06CDE109745AULL, 0x0CFA85C87A105A14ULL, 0x3F78A875DA1BB956ULL, 0x3D55E49C8884F712ULL, 
            0xDBFAD19ABE2055B7ULL, 0x7710EF0BDE90B6CFULL, 0xB646E7F0F40B0FC9ULL, 0x3E9FC8EA8CF2BC0AULL, 
            0x98A19ABFB192EB5DULL, 0x8DB8C0A2365A7F83ULL, 0x4EF7039842553ECDULL, 0x76EAB9EE284DC2C6ULL
        },
        {
            0x58F1CEA60C84313EULL, 0xD4E070BED80DB9D9ULL, 0x67E64DEBD039BD3CULL, 0x5BD7800F9B8844A0ULL, 
            0x87044FCC7019010BULL, 0x3C01DDC4306AF2F3ULL, 0x57CD4D0183267AAEULL, 0xA8D44F1282A478A9ULL, 
            0xABC8FFE2BF5DFA82ULL, 0x385831266EB462F5ULL, 0x90B4F36920E6C082ULL, 0xE3509829779FA8D4ULL, 
            0xCD31531951A87FB1ULL, 0x68B6292BC88ECA90ULL, 0x26BDCE7BDE204FE7ULL, 0xCDCB7F0FF3F7D5C9ULL, 
            0x1326EE06514EE890ULL, 0x4C074962C3BB82F1ULL, 0xB566C0C1BC9A18CFULL, 0x43974EBC6795D6D9ULL, 
            0x726B6EF7D46470A7ULL, 0xD319F9C2FAEF2370ULL, 0x2C8EB4FB7FAF1354ULL, 0x4B9ADBE1730201D7ULL, 
            0x53717BFD9F0EA7D3ULL, 0x89DCC620CC297429ULL, 0x57CF8F68A781D617ULL, 0xBAE8E94DF273EC58ULL, 
            0xB86FEC79E9861156ULL, 0xDD7321DCA6A7D04DULL, 0x96DAFFBE204B4D81ULL, 0xF0CA5FE80D74EBABULL
        },
        {
            0xA9D7B1B1AB69B73CULL, 0xBC0EAE479D13F0F0ULL, 0x13A3BE7F1C6541DBULL, 0xF9FEA5DC0EDAB46CULL, 
            0x3758D9362F2FA61AULL, 0x16E54847AB1C4E5BULL, 0x7C240A17C2D1EBBDULL, 0xF36AD64BE7770BE1ULL, 
            0xDC91A49CF6ED04E9ULL, 0x39743E6AE8D9F3C4ULL, 0x8906145970761547ULL, 0xBB6DA476B3E9B701ULL, 
            0xB4E3D8FD88D851D1ULL, 0x3951244B54F5F0B7ULL, 0xBF6C0EF1ED42DA63ULL, 0xB0DA2F06BDCA495EULL, 
            0x9FC6111FF6CB1DC0ULL, 0xD22A1088FDFF18BBULL, 0x5128678BE142C7E6ULL, 0xFD9BB47236D8778DULL, 
            0x7D43AC09335910F2ULL, 0x10BEE47F5DEB9FFAULL, 0xC465052E20E0A519ULL, 0x4C6857A3F72B551DULL, 
            0xF282F829790E71B2ULL, 0x363AB7957324D070ULL, 0xDE0509769A137AC0ULL, 0x2FE8E7FA0AA35EC8ULL, 
            0x5E3ED26413E1C00EULL, 0x2E330E764593A39DULL, 0xDF17327321531F8BULL, 0xE801AE6854153651ULL
        }
    },
    {
        {
            0xD32DA7FEB1423D06ULL, 0x566BBCCCE8795DA4ULL, 0xA365227BD796C149ULL, 0xB538F9B40769C5E1ULL, 
            0xA4DC8EAEAB53566DULL, 0x0A31C1112EDCFE9DULL, 0x2824825D9C4ED264ULL, 0xE0588D97C29468C7ULL, 
            0x2BF7F89810637009ULL, 0x201B848FFFF3F495ULL, 0x853DD880715623EAULL, 0x418A1F376A5E3E72ULL, 
            0xF322C3F8CACA78D9ULL, 0x904417D52388B414ULL, 0xE7F10A0C3485195BULL, 0x87D27574207D1871ULL, 
            0xA69AFEF271845C24ULL, 0xF5C1F03A76211385ULL, 0x61E7220BC76DBBD3ULL, 0x77D0DD6A9823EACBULL, 
            0x05B1417A8363497CULL, 0x8B0212D364F047F9ULL, 0x4C646A29DE93186BULL, 0x02F46E4EEE93F0D3ULL, 
            0x8733B1BB4BC6EB29ULL, 0xB79496D8C325EDE9ULL, 0x9A9DA6EFB55A2B0CULL, 0xC675166595FC9224ULL, 
            0xC397B6E3A3CA256AULL, 0x7A38509DB4C3A919ULL, 0xAA7B308DCED6D510ULL, 0x7234077C4A1109D9ULL
        },
        {
            0xAFD7A2133B4FD1F3ULL, 0xDA72BBA6C3ADD4E7ULL, 0xE39062F110ADA448ULL, 0x03A59603EDA56A31ULL, 
            0x9B4F05CD44DA69ECULL, 0x8AFAFA99F3F80C4DULL, 0xFD6EEA75E8927BE5ULL, 0xAD215485BB85D073ULL, 
            0x36640B0B1C1A6B96ULL, 0x930D1D098E7BD006ULL, 0x2E3848EA637339FDULL, 0xB3F166F831C71444ULL, 
            0x6AC1F24B7AF74F83ULL, 0xEEF1B321F5527FF3ULL, 0x57E970C9FF370561ULL, 0x1DF215C77DDED157ULL, 
            0x76991A0696E8DF63ULL, 0x1EA5DC7D8032EF27ULL, 0x17CB5F584FEECF02ULL, 0x19ACE7B8E61C9CBAULL, 
            0xCA7924ABBEB187BFULL, 0xD98FB6BD77F780CDULL, 0x544F49E9FA60A13FULL, 0x4EC9E0E78B9178F3ULL, 
            0x8624B97C06D02E55ULL, 0x49AFF1054580288AULL, 0x5FE23DFB5382BAFDULL, 0x5332394460AEFCB4ULL, 
            0xAC89E01F26883721ULL, 0xD66497B3881295E3ULL, 0xA6B5BEF49970ED82ULL, 0xAF376B05DB4A63D5ULL
        },
        {
            0x5C677D74252FE972ULL, 0x8C74D805924936ECULL, 0xC28F4EF6964B27DAULL, 0x0DD2C2681271AD3BULL, 
            0x70B668DAFECEC2CFULL, 0xDB6636ECDEF352B5ULL, 0x9052999357530D41ULL, 0x750970BBAFC86D7AULL, 
            0xBD51BCEBA9EA1E14ULL, 0x94AA4138A5A4E1BAULL, 0x064852F14AF525F7ULL, 0x3CE4F53434233241ULL, 
            0x39B23EDAB42BCFCBULL, 0x604CE2130A0EA476ULL, 0xD10715C2D02F30CAULL, 0x6075A57790919BA6ULL, 
            0xFAAB1C8B71C4FE4EULL, 0x3B6B1F9C8AD0B95CULL, 0x127B1F9260AA755FULL, 0xCF7BADD8005B4139ULL, 
            0xAEB54E4E88EE5A30ULL, 0x28D193C609F7F905ULL, 0x28A91A2502687667ULL, 0xF5B50F3D667E8021ULL, 
            0x036F45DDC2BDD1A1ULL, 0x525EBCE58F1E580FULL, 0x657805A83661CB26ULL, 0xACF16314D672DAE5ULL, 
            0xC456C8FF176135EDULL, 0x1E31B78A03F0665EULL, 0xF0893B79CB9D057FULL, 0xFDA401662BE20E05ULL
        },
        {
            0x5A53B185D20F87ABULL, 0x2869012209C7A23AULL, 0xCEC445E8587FE161ULL, 0xE5A572AF9E030397ULL, 
            0xAC27A408F165052FULL, 0xE0CFE8CF315CCF30ULL, 0x9651C50E72969E5BULL, 0x7B211789471DA5C1ULL, 
            0xA96CAE01E8084A08ULL, 0x025D21374948F84BULL, 0xA8302D9498C48F65ULL, 0x69ABD7C6D9C28580ULL, 
            0x82F18D137E952541ULL, 0x5520CF755675489DULL, 0x08499AD9E9609DCCULL, 0x5FDE135EB64C8EF3ULL, 
            0x91BCA6F2E9D0A2B6ULL, 0x232AA36B3DA10FA4ULL, 0xC031DACE633825F4ULL, 0xE686ED50DBE5248CULL, 
            0x15C0058BE2ACE4FAULL, 0x601BC32C6BF210E9ULL, 0x5D53CC9C25C310A4ULL, 0x67CD2008858EC366ULL, 
            0xDF685A1B6CABF4AEULL, 0x0C4000892F8ABB11ULL, 0x8BEBD314D06DE8E6ULL, 0x9866855A38160CC4ULL, 
            0x312137BE3C4B1DFEULL, 0x5EB1D8C94ED82628ULL, 0x362B2A15EE099A6DULL, 0x2EEBA4DD368B1570ULL
        },
        {
            0x78D56929685693A5ULL, 0xCC86D81386ADFBE4ULL, 0x20C2C9695455F522ULL, 0x8487A52C5D163E16ULL, 
            0x9DAF0CEA76057F00ULL, 0x395F69C8BA550B59ULL, 0x5BE7F37B78514A39ULL, 0xE3065930049FEAA7ULL, 
            0x6A3284AE2C4B999DULL, 0x99774B451AA9D2FAULL, 0x644718927B47240CULL, 0x7733A63C1A348811ULL, 
            0x2B808C775EA32A95ULL, 0x2C80417960CBF1C7ULL, 0x6987C024165083F2ULL, 0x73203F7A094513D4ULL, 
            0x5151A5461F7FDD31ULL, 0x3440DCCB4AAE2520ULL, 0x8BBF90EC4FF9F245ULL, 0xED293BA4F9C09090ULL, 
            0xA5B0588B5995DC4AULL, 0x5588BE1C728A5DA2ULL, 0xC87DFC8F69F25531ULL, 0x3855BE3AD0784940ULL, 
            0x9360C048453560A4ULL, 0xE02FF129AD0FDCFBULL, 0xDEF5DED69FA4DFC2ULL, 0x1254C9072E33C3B7ULL, 
            0xDB61D2B2ACFF62C1ULL, 0x07C648026523B9EDULL, 0x724E6A2B2092A234ULL, 0x3E19E9FA6231B19FULL
        },
        {
            0xC1CA1B67737EC14FULL, 0xAC05FADE77BF8AF7ULL, 0xF7973B87BB61C570ULL, 0x88418F318A0209F9ULL, 
            0xA510A044AB1ADD87ULL, 0x644B323B87DD690BULL, 0x490E131E3AB2DD68ULL, 0x77FA4604BD118FAFULL, 
            0x02991C2D655D1154ULL, 0x59BE9DA38A2A3CD8ULL, 0x67E5F74BDA1B3EFFULL, 0xB2B8BEFC8736F576ULL, 
            0xA929ED94C5DF9E9BULL, 0x40912A7FA4EDA2ECULL, 0x1BE7E07A505FB948ULL, 0xF562FA978AB96074ULL, 
            0x1CA1F04401760D80ULL, 0x5FFD4D91785464D4ULL, 0xBB50ED7178B3AAE2ULL, 0x878A9A56A9E83579ULL, 
            0x139054C28A52FC46ULL, 0xFBFCC46520B70CADULL, 0xF6BA262ED44059E0ULL, 0x54F213B19613F0CBULL, 
            0x95641AD6B87D583EULL, 0x977F90AD6D674609ULL, 0x9ABBE2552F17D886ULL, 0x476119AC69A3D782ULL, 
            0xADDF1957B698C6D9ULL, 0x3DC23458A294688BULL, 0x1E346CAEC802486CULL, 0xA1875FE47B3346E5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseBConstants = {
    0xC8F980E6880C1A87ULL,
    0xEFE6E156E1BD7BA2ULL,
    0x77C9B380ACE4019EULL,
    0xC8F980E6880C1A87ULL,
    0xEFE6E156E1BD7BA2ULL,
    0x77C9B380ACE4019EULL,
    0x0875CB982E759123ULL,
    0xE39CE2EF2B0B7180ULL,
    0xE9,
    0x85,
    0xBC,
    0x11,
    0x9D,
    0x54,
    0x78,
    0x47
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseCSalts = {
    {
        {
            0x755C7B2075153386ULL, 0xF76192806C2142DAULL, 0x3A61F4DF80EA09ACULL, 0x344FD21200E9C47FULL, 
            0x85C9004BC3BF2FD3ULL, 0x9B43726723792178ULL, 0xCA35BBEEF2A21CE1ULL, 0x8A6F75ACA1C67067ULL, 
            0x28CFEEDB7BF607AFULL, 0x2B5F9F49841DAC88ULL, 0xE386A05E79587DF2ULL, 0x9B04967CC47F78BAULL, 
            0xDAD3173B466BEB98ULL, 0x0FDE546C4EAEF0CBULL, 0xCE07C3C217B90B17ULL, 0xCF9DCD3C671375DDULL, 
            0x958B36506BF4A668ULL, 0x9464931437903B62ULL, 0xF6B0F2378A72E05AULL, 0xDF2661C8A2A29D56ULL, 
            0x823C5B3CC57414DEULL, 0x34FBB43DA1878194ULL, 0x77C643D57F607238ULL, 0xAD865581F25310F2ULL, 
            0x64E51851A9BF37A8ULL, 0x690C58811CDDDE5BULL, 0xF8EA4DB90E6303D0ULL, 0xB33542FA5B1AF1D6ULL, 
            0x469322F95BF86658ULL, 0x371B1050DE35F016ULL, 0x480D47FDA68DBFD4ULL, 0x7CE8708700F0BDF3ULL
        },
        {
            0x3532FEE463795A03ULL, 0xB8902C21BE462F8DULL, 0x56F85ECCEC6943C7ULL, 0x55210DF65EB7668FULL, 
            0xF3B46B2EE6553D8AULL, 0xFA32BC152AE0D74CULL, 0xF338241254A808A8ULL, 0x10AFF80954F46FFEULL, 
            0xCBCBBC5E3FB4207EULL, 0x6FAB420421F70F15ULL, 0x5E5923445F61D8CBULL, 0x425B4213DA7A19E8ULL, 
            0xD443772600C97A82ULL, 0xB7E1F419F252BD99ULL, 0x8ADE650A795A0BF8ULL, 0x54567C0F183DD2D8ULL, 
            0xE5543CE6A9A47D87ULL, 0xFE578BD32E90CFE2ULL, 0x2B8F802706336C0AULL, 0xCE41A40858FC9A3FULL, 
            0xB8E419F0A84F5455ULL, 0xE20303723AF7B2DDULL, 0x3B40588CFF53587CULL, 0x275233B585E0D8FAULL, 
            0x7FB15962CC76FC9FULL, 0xBCFDECED28941DF6ULL, 0x718B1A8B590DD94FULL, 0x9BFA9105CEC9E4B7ULL, 
            0xC3B65A92532230BBULL, 0x816ED1616E21C075ULL, 0x64C97B07737B377EULL, 0x9AEEC0FFB7183397ULL
        },
        {
            0x09B0E34E76E590E1ULL, 0x23B7391CAC176AAEULL, 0x525B643A1B76ED00ULL, 0xF60A4670D7AD6C9FULL, 
            0xD7D9A28FA4E0784DULL, 0x1ACAD53CA3A5FDD7ULL, 0x5CAC82AF2E294CB0ULL, 0x108BB17C04E8E041ULL, 
            0xF731F828EB22E607ULL, 0x0E1552CCC2215534ULL, 0x325003221692339EULL, 0x209EE9A9D1A1EBCDULL, 
            0x1731A268C6034B98ULL, 0x650376A17F5FC3E4ULL, 0xCD281E624EEF179DULL, 0x1B4957350830314DULL, 
            0x9B6B1F4A877C2F54ULL, 0xB3BEED8D6D8BEC85ULL, 0x18C7F14328017204ULL, 0xF26846D1B87A83A5ULL, 
            0x27A09C5A00D9172CULL, 0x69E3F6E8CD198E6FULL, 0xD0F2D86901D1CEB5ULL, 0x4CB161E4B86E7EB1ULL, 
            0x5F63DB5C99B505CFULL, 0x1EF75EC7C209A75BULL, 0xBB085BA9D0AF6865ULL, 0xCD56E3138FE50B9CULL, 
            0x99B9B3E66A9F485BULL, 0x3E09FE0D1B563549ULL, 0x1E9CB2DC15380F19ULL, 0x51B0C79C7C6EFFB8ULL
        },
        {
            0xCB653129677CFA49ULL, 0x3FFF9629F6E437AAULL, 0x1A21905DB8A0BE25ULL, 0xA58275AB90E2ECC5ULL, 
            0x84B90D02570588E1ULL, 0xCBEF1B5CC247B603ULL, 0x584531919C7BC8CBULL, 0x7FB5124398363D1DULL, 
            0x4942CF137C62BB05ULL, 0xAD535D0F5805FB34ULL, 0xC87832AD56A36F18ULL, 0xFE357987C862B397ULL, 
            0xE840094A7F4556DBULL, 0x516959BAFD4030EFULL, 0xAC600A5546F556F5ULL, 0x3852EBAD17164277ULL, 
            0x096650FCF56348C9ULL, 0x356FCA4449097C77ULL, 0x9C3CC0F9E812978BULL, 0x0EF586A9351325C8ULL, 
            0xC4F565FB3AF097C4ULL, 0x411539DA0F4C6A26ULL, 0x3E8CD6D1260233B2ULL, 0x768E5114B456D6EDULL, 
            0x05C74E835ABBE55BULL, 0xAA6E4BA78B9133B8ULL, 0x3B43CD35B1B4CF9CULL, 0x04BC42F4E42C21DAULL, 
            0xCB855D0EB384D2EEULL, 0xF3C8FC5C91C74045ULL, 0xB769C542FE73D2D4ULL, 0x60AE0EB4CC42C805ULL
        },
        {
            0x0A68970076B263EFULL, 0xB9ADA6853FC75F21ULL, 0x9E95B0A8EE089DAFULL, 0xC19A09A46BD886E8ULL, 
            0x798D77601CA1F99FULL, 0x3D483D1718C8AEC9ULL, 0x960E46CF86DA8258ULL, 0xAE93CAF6C2EE8625ULL, 
            0x48D5276FCB7E0FF6ULL, 0x2EB76EBD9A2090D5ULL, 0x3FECC45761D5D48FULL, 0x42A4033B8FBB0316ULL, 
            0x941E60BA1B618859ULL, 0xA7803E6F0820381EULL, 0xD1075E71F6C22A4DULL, 0x2F5AA122E5AE711AULL, 
            0x699F03D942AFD04EULL, 0x433BC8C344EEACB1ULL, 0x9B008B11C7DA2764ULL, 0x3C66B5E499C3A3FDULL, 
            0xD094BC67FAA1888AULL, 0x6A91AE755E133810ULL, 0xB38B81B37004BD74ULL, 0x82D64DDE7090139AULL, 
            0x9C968DF821B43E9DULL, 0xC1A4F33E49F2BC34ULL, 0x27082C8F80842AC2ULL, 0x954C3CDE4A6D0D3CULL, 
            0x7BF00531124715E4ULL, 0x622691EDF4B377E1ULL, 0xE3DC7959EB68ECC6ULL, 0x7F6D33E9468462C2ULL
        },
        {
            0x62E38038EFDDD95EULL, 0xD8761DBA0EE92AFBULL, 0x7EC24E723CE38701ULL, 0x28C3E087BEF7E84DULL, 
            0x2D52F7A93E14C7F6ULL, 0xD5B72B4BF34173F1ULL, 0x707B127984A7D498ULL, 0x8300CE525DC89AA2ULL, 
            0xD865BF1489DF2E3CULL, 0x0A4DDE45877DCF1DULL, 0x72D035D6A008F829ULL, 0x20A91BDDF036F905ULL, 
            0x07CE83506756E3FBULL, 0x36EE0B68A74E7869ULL, 0x80CC5554E633F32BULL, 0xFF48B49E3622A98FULL, 
            0x55BBB79E2F1E5088ULL, 0x3893BBA900DD5671ULL, 0xB73ABB3E2A47D208ULL, 0xD9BD2626B10CB04CULL, 
            0x1DB6B207F79136D3ULL, 0x1275FBF1D80D622CULL, 0xFE4BFAE649A62438ULL, 0x6B46E36D47EA7454ULL, 
            0x047D672CF3A32042ULL, 0x36544B08BCCA60CFULL, 0x5C5E22ECA94CE353ULL, 0xA5BDDD321E633C80ULL, 
            0x40B62B94C8283200ULL, 0x98B6F62EB0BEE6DDULL, 0x9A803166B3CD5FC3ULL, 0xDA3C0821CAB272BEULL
        }
    },
    {
        {
            0x6B729324373E756BULL, 0x79B87E925F71195CULL, 0xA1A563EBCFBF9439ULL, 0x6EC6ADF525CD309EULL, 
            0x2FCB73AF9BA871D5ULL, 0x4E24EA6CD4824F10ULL, 0x43B02191CC652668ULL, 0x5F5BF6DCD779B911ULL, 
            0xFAE32A6FB63645F7ULL, 0xB7880789188E2E1EULL, 0x687BB6DC8CBF7CA0ULL, 0x1F65CF3FF98A3901ULL, 
            0x2EEF6D535D387741ULL, 0xF278ABD3ADC9507EULL, 0xCE968D61B559538CULL, 0x858EC6FA6123601CULL, 
            0x5DB4FA6CB0334323ULL, 0xB670DC0BFFF7A895ULL, 0x76D9FD90FEAD6EA8ULL, 0xC598E4BB90C07F69ULL, 
            0x38651031D2B0C182ULL, 0xE4A34D182BBF2C29ULL, 0x7E2A02FBBADC101EULL, 0x5393188492FD5D6CULL, 
            0x4BA710C74D5C1BCCULL, 0x6726900CC674598EULL, 0x479DEE5D6280B568ULL, 0xFE7E89440D3F38AFULL, 
            0x7ED50E6E60257B9AULL, 0x167FD818A8AB0920ULL, 0x9D6D32EF42056B53ULL, 0x70715D34FC3A0AD3ULL
        },
        {
            0x19EE5724B909B74AULL, 0xA0E44C7618BF3732ULL, 0x6494F19569AF0F45ULL, 0x007167121BEFD220ULL, 
            0xCAA372C461EBFE46ULL, 0x3629D58B880BF706ULL, 0x8A0841F0D4B15C1FULL, 0x443311DD6B79B218ULL, 
            0xAB77ED20D6225294ULL, 0x91C061CEF1D6A1DBULL, 0xBF7D6945EA422524ULL, 0x1C8FC0F4CA1C79FAULL, 
            0x9D5AF96D9C7394E6ULL, 0x4BACE7C9B8AF8F0EULL, 0x95D2930420665241ULL, 0x090D32C0390FDD21ULL, 
            0x9A68D8467A121A48ULL, 0x0B4DF33493857906ULL, 0xCBE89EBE9D9785D1ULL, 0x52A051CC0B4DF34EULL, 
            0x4F0CF286DD60AC2BULL, 0xAD6036AA3FFF05DBULL, 0xA49059B5BD46D8B8ULL, 0x3A517EBBE2BAD2DFULL, 
            0xDB8049F092314B2FULL, 0x03FB9D89A3A3E20CULL, 0x78B59F3D75A99C65ULL, 0x8FF82A5321FCA639ULL, 
            0xF9B4D0231FCFD55CULL, 0xA0EFE5F7F46AC452ULL, 0xCAE923C84F430EB4ULL, 0xCE91B7FE258EF304ULL
        },
        {
            0xD4AED5EC468D71EAULL, 0x003FEA7C4942827FULL, 0xA0C8DA5F41B97178ULL, 0x1E974801FFB5BFA5ULL, 
            0x2A4B6CC270F9A1A9ULL, 0x615CBFD2BA9B0E38ULL, 0x052FE38B4034B44CULL, 0x467ADC97BA090335ULL, 
            0x6F1BD58D47D84D76ULL, 0x35EB60A263E1E587ULL, 0x2617E3D4F3C5A842ULL, 0x418B2817162A88E4ULL, 
            0xFB09875469FACCDEULL, 0xD59778CEC0349D1AULL, 0xC8509CD653CF51E3ULL, 0xDC80B4C46134648EULL, 
            0x9937EDB43F4555E5ULL, 0x3093DBBEBDC4ACA5ULL, 0x864D851C272E915AULL, 0x1DF7113B1B4BF61BULL, 
            0xE8D6B73E26314AA1ULL, 0xD16AA19E2202F5A0ULL, 0x2396B9C10FCB43E0ULL, 0x3734B31CA8FE5774ULL, 
            0x411F7522199EF499ULL, 0x9544EF371645B0F2ULL, 0x836982BE6ABFAA13ULL, 0x0ACA1F3E7BA548F3ULL, 
            0xDC9719655C7CB099ULL, 0xD9CE3996519342D8ULL, 0x4F6697526EDEC530ULL, 0x2C0B77B56ED3FFAAULL
        },
        {
            0xC61E83975AAAB5C7ULL, 0x834B8D7ED4C1CBE4ULL, 0xAEC0F2B83AA8ACCCULL, 0x216C100E56E64A58ULL, 
            0xE8EAC942EC7EB630ULL, 0xFC59C6ED1E287774ULL, 0xBADA43B9995840FBULL, 0x876F2E6C1CD794B2ULL, 
            0x16BCB6D43DCF33E6ULL, 0xCC392809B66E00FEULL, 0x6AD0519BA05F4C60ULL, 0xB8A8566FBDCBB511ULL, 
            0x54E2541A0B915FCFULL, 0x1FEAD863FA081435ULL, 0x24BC6F0FF82A8AA0ULL, 0x1CCC9F84423AFE82ULL, 
            0x6B6DC966A8FEDF39ULL, 0x25429D54C2886F8CULL, 0x08BE117261A1ECF4ULL, 0xFCA89538A4162FE2ULL, 
            0x14815BCC56157602ULL, 0x4D110340F622ACB9ULL, 0xF67F7BBB948AC994ULL, 0x464C03504C6CEE2DULL, 
            0x7AC9003EA540B9CCULL, 0xA35F729F6A98EE04ULL, 0x669D80CA19838382ULL, 0xD223D5E45D376327ULL, 
            0x61A2E98890F3DCA7ULL, 0x69B7BD01C47EA0CCULL, 0x1B36C88D45D46280ULL, 0x3B9D3745EA62474EULL
        },
        {
            0x705C3E3B16931504ULL, 0x55A09440DF2FAFEBULL, 0x81E57AC306AEC299ULL, 0x148B27E70F0B3452ULL, 
            0xF0ABF39167D95118ULL, 0xDC8B9A0495CBB1DDULL, 0x2B2CC3B87D343958ULL, 0xEECB908AB5FF118FULL, 
            0x4864398DBFEBA37DULL, 0xC1491D47F3A0D117ULL, 0x27EEA790C7E889E6ULL, 0x665FA1CD4AA675BAULL, 
            0xD12FB697A3A816A8ULL, 0x5933A9575C88E781ULL, 0xF4C58CD104CE975CULL, 0x4AD54BF96C0E1C68ULL, 
            0x1AAB94772BF8D584ULL, 0x8934ED4F3E29D2ECULL, 0x39B216843F035893ULL, 0xE90E85C8036C55E7ULL, 
            0xE37AE2B736D093B9ULL, 0x0DA02DC567D2886BULL, 0xD0CD21A36B730CE4ULL, 0x424C6317899A8FD6ULL, 
            0x114E0AC77E2B205CULL, 0x7D22C9FC550C675EULL, 0x89C8823EDE3687F6ULL, 0x5D0D3CB9548F62BCULL, 
            0xC2014EC89AD63E38ULL, 0x115D744D003FFC0EULL, 0xAC6DBD033139B36FULL, 0x1C912B6149C5AE9DULL
        },
        {
            0x7DB34661E820B9CEULL, 0x8DFCBC4A93E9504DULL, 0xEDC6C701E3EB82E3ULL, 0x5CEB2AB31E643A5AULL, 
            0xED2318FE2F25EC2BULL, 0x1B5FA2FB42CBD8A4ULL, 0xCAB20B71216C2057ULL, 0xF103DF3FB7DFF0D1ULL, 
            0xC474760ABEFFB5B3ULL, 0xDD8F688770C616A2ULL, 0x060E28FECC317B30ULL, 0x0DEF8EF32EB67D2EULL, 
            0xA4F5A43D60B83AEFULL, 0x559678A9CF8AAFEAULL, 0x76CB3876E17A76F1ULL, 0x40789BD25F587D5CULL, 
            0x13820EDD173E7B69ULL, 0x71159C2ECB6E9724ULL, 0x682846D0C2974F5AULL, 0xF2636D3CEB092B2AULL, 
            0xCB376CCEDF7C1531ULL, 0xA0F043E464571BB4ULL, 0xB4F603FA2E9518C5ULL, 0x60B743DAF13942D0ULL, 
            0xF1EC7BF99BAA69ADULL, 0xD623AC3427448C5DULL, 0x3FB7892F73D5708DULL, 0x63458376F072F9BAULL, 
            0xF09E71A0A07D6242ULL, 0x4D3D30606555F058ULL, 0xEA0CB9B5A8F22C03ULL, 0x162A0EB7E7E0594CULL
        }
    },
    {
        {
            0x2EC03E8AE888888EULL, 0x3A1BB4A9BEF139D7ULL, 0x815BF6BA28A6D50CULL, 0x4C2AE659D10269FDULL, 
            0xA777BAD4DDC0246FULL, 0x9A9A6B143621CD1BULL, 0xDCA7515739A68B64ULL, 0xE1B91E801D07A0B3ULL, 
            0xBD2635E44B8911A7ULL, 0x7A486E70E24053E4ULL, 0x7F60BE3E7FBBDD4CULL, 0x44945C721086A9EAULL, 
            0x67ABFA9C4E61BD12ULL, 0x03CC499D9B08C7B3ULL, 0x1C5E84A19093EF69ULL, 0x88226F757A03DD54ULL, 
            0x7CC46E6DD9FAF866ULL, 0x13C9F1270EDD4241ULL, 0x106CE1578CD15963ULL, 0x2F48F93B209AA3BDULL, 
            0x89B50DFBD576B573ULL, 0x2FCC514C0D02C0A8ULL, 0x48E14153CA466D67ULL, 0x1F62AB61C5A7FE63ULL, 
            0x1A233656240EE7FAULL, 0x0CB193CE37975387ULL, 0x2C403C9B3A16EC59ULL, 0x5DB5F22742BBE271ULL, 
            0x581521777AC76092ULL, 0x13146C504D11CE30ULL, 0x07842E409ED1BB4FULL, 0xE9C048A1EA9257B7ULL
        },
        {
            0xD7D5D9118AF41759ULL, 0x6ED2FA9C472F0B29ULL, 0x1D047EB91B5DDB0CULL, 0x8455B52F1491EBD6ULL, 
            0x43B89FB1E2EA43D4ULL, 0x29A404BB5C6B467CULL, 0x61F2898531C2EF03ULL, 0x7911390897376357ULL, 
            0xDB394B1983EA713FULL, 0xCFDCDE394F7C36E0ULL, 0xCED7F9992009CB72ULL, 0x7A203DFCF4442282ULL, 
            0x53BA5F733A920EE2ULL, 0xDA42F946989ACD20ULL, 0x419C868D677A7998ULL, 0xCD3A32CDBAE4539EULL, 
            0xF994D4B5FB91095DULL, 0xC063E497C7354BDDULL, 0x7BE1EF59ED002C96ULL, 0x448007203DA26F35ULL, 
            0xBE776B605E18F5E6ULL, 0x2E6B287757A440A2ULL, 0xFFEEF690E38EC694ULL, 0x826D7D55CEE922A5ULL, 
            0xC404C5DB86B8185DULL, 0x3EA9E5C267EAECA3ULL, 0xCE5ADCF84975CBA3ULL, 0x8B9C9C1308E4D519ULL, 
            0x7D7058AA86AC6207ULL, 0x28A22C4D242E0E7CULL, 0xB3EDE329DBD1C046ULL, 0x1DF13835F9749DBAULL
        },
        {
            0x47FFEBE6F883F176ULL, 0x03EADBE2677EFA39ULL, 0x4C0C725CF85A7B51ULL, 0x89CE58CF040E91BAULL, 
            0x6A2F7052F1FEC686ULL, 0x282810FD2F14E160ULL, 0x5BA7E94330D3E7DFULL, 0xDFC448C89BF0B56DULL, 
            0xF71EE22C1240A7D2ULL, 0xAE6FBFA64695F191ULL, 0xFEEEE2B712997000ULL, 0x20BC3F74ABBB0C3CULL, 
            0xF5DBD6592DBC4318ULL, 0x881652F81A5DF653ULL, 0xBC20C4E96BE6AF70ULL, 0x57D6E2350606EF16ULL, 
            0xD67CBA884CD4520CULL, 0x0DABA56E67FD346BULL, 0x96CFFD8B8F0A6300ULL, 0x44F246E007046B59ULL, 
            0xF5F1F3449F8AEEABULL, 0x56E8C8A67580CF41ULL, 0x2DF4E94712486651ULL, 0x33DB7B92022BCC5DULL, 
            0x956220173A2290CDULL, 0xAD024CA9FC40CEF3ULL, 0x2BA717850F67CD4CULL, 0x286E44AD3B7008C2ULL, 
            0xE2B89DD88F9D0F6DULL, 0x760D9B2A0695F617ULL, 0xC68CB1E8062E5504ULL, 0x7DC3C8A7600E16AFULL
        },
        {
            0x8069358FC280D70BULL, 0x117A25D64F8338E5ULL, 0xD8B22C8B9587327DULL, 0x1BB06B072EBB773AULL, 
            0xEB9FB52DBD7CE6F7ULL, 0x2D7F044D68D17302ULL, 0x7DA1EF091C450C80ULL, 0x86F0B4BB913AA8F1ULL, 
            0xEEC1BE0571BCF184ULL, 0xCC7D69F340574C69ULL, 0x5B57EF508BB0747CULL, 0x096AAF916F32274CULL, 
            0x371B59D7D04F3A19ULL, 0x0CE68B3CAA4B678FULL, 0x69617AEC73768DCCULL, 0x90595B5B7E2380E6ULL, 
            0x56C829D37141084FULL, 0x6EDCEA79499B94F2ULL, 0xC98629ADCCB95B14ULL, 0x2639CDA96F6F9B06ULL, 
            0x4261F9A2B79980D8ULL, 0xC643DE3BAA0A1500ULL, 0x2F357685B7B05E2CULL, 0x40900CAE700C1221ULL, 
            0xDD03EC59F13D8B67ULL, 0x98E8AE406D60C63AULL, 0x3CED69E5A6750BEAULL, 0xF219ED8ABD4064C6ULL, 
            0x35E34F5343E65C9DULL, 0x0D096D6E09F618F0ULL, 0x1DB3B49047E98B07ULL, 0x311A393878E78F14ULL
        },
        {
            0x8A16F7AB7244BC81ULL, 0x013D0640175987EAULL, 0xC4320EE7D83980A1ULL, 0x77D124E2C26FD61AULL, 
            0x1E641601F341F356ULL, 0x7129B846B0E4C30CULL, 0xFB37579D46B31390ULL, 0x5203D80F02327F06ULL, 
            0xBF14083D96613A0CULL, 0x9A989B14680E0A8CULL, 0x61FA8C36E96E3677ULL, 0x6EA71D9FD4E88BC7ULL, 
            0xFC9158AD56BCB682ULL, 0x9B7C378C3EA758D3ULL, 0xA39326CBD16C34A9ULL, 0x25F65A3B84A4F6D7ULL, 
            0xD33F5A0F8FA9A3A6ULL, 0x1A32101833E40A8AULL, 0x174DD64F4165C54DULL, 0x2690141891E4CCC5ULL, 
            0x7578284FA590536EULL, 0x31BF8065CC001CD8ULL, 0xB2433494174DFE53ULL, 0x3B157F6234B4B20CULL, 
            0xE336AB03AFF9FDCCULL, 0x01E0E752F25DC481ULL, 0x0CDE945393B91D39ULL, 0xCB96C86F3C0C58F9ULL, 
            0x77991A47B45530A0ULL, 0x8C7DBAD628D79AAAULL, 0x9EC4A00DF7B35C07ULL, 0x3B470E5ADC7B5B59ULL
        },
        {
            0x2468054481D48C69ULL, 0xB27B1FA402AE24A8ULL, 0x840C68F6133CF7BCULL, 0x6E910F90B0E0F976ULL, 
            0x76CF996130BFE03FULL, 0x2DD8DDA3D7623C8FULL, 0xBF3DB8F741B27940ULL, 0x4CB365985EC125EBULL, 
            0x36E14618368F21C1ULL, 0xBE4D00AC4121D0EFULL, 0x1B6DC3729CBE33B6ULL, 0x41B7C3A6ABDCC8F0ULL, 
            0xB3130DBB36A6D001ULL, 0x97DE98470FE4B9F8ULL, 0x526DB9540314F00CULL, 0x79BC53E6FC949C15ULL, 
            0x1F41415696E55299ULL, 0x3D370CD216D22E94ULL, 0x1E074F56FC6F006FULL, 0x283229A2B8D1A3A7ULL, 
            0x04098BC9E6E57A89ULL, 0x0D86A7553144C6E9ULL, 0xB040D5A670EE3041ULL, 0xADFC23F740792106ULL, 
            0x629C47601D3E6FDAULL, 0x31D2DB6811429608ULL, 0xC1EEB154C5003B1FULL, 0x9E41BEC6D05623C4ULL, 
            0x8223254F7E0A82FEULL, 0x8AA24B22C60FE3B9ULL, 0x7A06DDA45B2424A4ULL, 0x754905DBF847052EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseCConstants = {
    0x406D4B6400D3ECF2ULL,
    0x9A1E10D6FB750F52ULL,
    0x5459736D7F5A2B9DULL,
    0x406D4B6400D3ECF2ULL,
    0x9A1E10D6FB750F52ULL,
    0x5459736D7F5A2B9DULL,
    0xF4016C3D784764E0ULL,
    0xC715CF4599834372ULL,
    0x1D,
    0x16,
    0xAE,
    0x5D,
    0x6B,
    0xC1,
    0xA0,
    0x10
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseDSalts = {
    {
        {
            0xC04218352CEE7C1EULL, 0x766909EEF36C6D5DULL, 0xE263A54CF9F59983ULL, 0x6C2F9FDCCB1BAF08ULL, 
            0x45639C3B066E1EE1ULL, 0xD9EC11C83EACBC8FULL, 0x49CD699EF337DCC3ULL, 0x8F9B8A1EF6899C52ULL, 
            0xE0AF83E73E7CF63BULL, 0x95E8CFAB796EC0E4ULL, 0xC818574AB16E4A5FULL, 0x29564BB2699CCFA5ULL, 
            0xA5A775B0B66DFDBEULL, 0x5B19EE344C20496AULL, 0xF675DE84EAAD605FULL, 0xEC75AE8FCF2E01AEULL, 
            0xEB4881B1C0539A10ULL, 0x0BD185EFE6571E06ULL, 0x145DE37EFB96D2EAULL, 0xA51E1AF9C50155D1ULL, 
            0x710C378BC6F360DDULL, 0x01CE9970322BE8D0ULL, 0x2C6467FCE3A64DC5ULL, 0x5A5FBA3FAC00D8FFULL, 
            0xFDF9EC49B32A96CDULL, 0x6DA7144332B21C7BULL, 0x5ED3EC9BE4CD05C7ULL, 0x70009D029537F4DEULL, 
            0xA157C6E2C3FA5729ULL, 0x50088ED9A3FCAF40ULL, 0x80136DB12687954AULL, 0x5973E39BFC0B74E3ULL
        },
        {
            0x8A8A68D6D4BBD11BULL, 0xBA1A9ADA7814A136ULL, 0x9BB1EBD43E20085FULL, 0x0B7D43E192F54615ULL, 
            0x877027BC75A64A57ULL, 0xC37DD3534BB79F5BULL, 0xC61831AB780B5942ULL, 0x7F3A77E2D3E4707BULL, 
            0xD1A46D28CE39E012ULL, 0x1C8C67B008D882BFULL, 0x5E9C0145A8EF3EDBULL, 0x98FBBC5C068764BDULL, 
            0x4A71EE438D2C35F1ULL, 0x60AEACC6D06F9C05ULL, 0x7F4BD2246CB9F3D7ULL, 0x37ED5A54BEEFCC7BULL, 
            0x89D9C11D754F25CDULL, 0x38E4B1CBBCDCECF4ULL, 0x1F2D71C81768D3F0ULL, 0x1FA9D072EF91C72BULL, 
            0x61DD151EE7B962A5ULL, 0x6A6A38A180BE39D6ULL, 0xAEAFA2436D6D9C7CULL, 0xE8DF02184157B124ULL, 
            0x66F849DFBB67FD72ULL, 0x0220705DC2667C30ULL, 0x3F13A4728AF1B31BULL, 0x771B0398278920E8ULL, 
            0xE96F942A6C456368ULL, 0xCECA827F32C15634ULL, 0x3945088260B393A3ULL, 0x1AD1A3DE6356C426ULL
        },
        {
            0x3F7093055E629063ULL, 0x1B8F87B43E179E7BULL, 0xB5B2737EAAB2553CULL, 0x7C586DD791E0ADC6ULL, 
            0x9DF95A5EBB2D11A8ULL, 0xF71C556BAD75A53CULL, 0x569D25AF8CB541CDULL, 0x87FA5E3D0ABFD0D8ULL, 
            0xBBC0718A833F6CD7ULL, 0xECC51F220790DE2AULL, 0x5815728CE573B5EAULL, 0x7A4CBA5624701F80ULL, 
            0x2A446D81DBB05575ULL, 0xC836DE3FB3EDB8D2ULL, 0xFB6657FDFF46AD16ULL, 0x3B92FE7325A30B53ULL, 
            0x9B1A1E1A03D6E1F9ULL, 0x77E9B12FA923933EULL, 0xDEE82CCD8DC0C1ABULL, 0x1E821D4855137093ULL, 
            0xEC71C38AE3A92FBCULL, 0x0860014DD6BA8B94ULL, 0xED4D18B19563245DULL, 0x08202969872738CCULL, 
            0xEF504B1BEB3B8C00ULL, 0xDFE5251188C718A7ULL, 0x163650D620E3D020ULL, 0x62BCFE6A0BD2BDD3ULL, 
            0xCE2B80A50218472EULL, 0x4CA47FE267E057BDULL, 0x3CD1C4A77469AD13ULL, 0xBCF01B0D68F3FDFDULL
        },
        {
            0xA9E91D09B318E514ULL, 0xCEB331AD8F19EC4FULL, 0xC3144334C993B6E1ULL, 0x70B75B5568894729ULL, 
            0xF9DDA2A2EC6C3FB0ULL, 0x786D5F75CD886F2BULL, 0x9185F273FFFE27A4ULL, 0x5DFFE1B3568B609AULL, 
            0x9EED26E03D8F23C1ULL, 0x0A9C2A7057DF352BULL, 0x46E09884F9672B5BULL, 0x93AA1D9E40D1312DULL, 
            0x17AE7D3A738B2B96ULL, 0xABBA5F0F278333E0ULL, 0xF7D24FB1FDEE5F1CULL, 0x7C702604746329D4ULL, 
            0x3E15504663B2FBF8ULL, 0xF885894EEEC40B63ULL, 0x9C3362B1406DE013ULL, 0x782915F4D531A5BFULL, 
            0xB0A72753A95555C9ULL, 0xDCF0DAE8C054C02AULL, 0xC56E73C8EC7231E6ULL, 0xE29DE9473EA9D6BAULL, 
            0x34092F0316679EA9ULL, 0x6655864B315A5679ULL, 0x73EA4E6D007BF869ULL, 0x4E1654965DF7F284ULL, 
            0x8E3E94672506FF00ULL, 0xC1DB152089997276ULL, 0x45BCABAAF65B30A4ULL, 0x7762513D78C61BF9ULL
        },
        {
            0x7341F840EDE1AD2DULL, 0x034A3B5CB260D940ULL, 0xFA236FFDB9088BCCULL, 0x3CFA59175C3255A0ULL, 
            0x7EE0C8B2DC3505CBULL, 0x42B54DDA56BC58FAULL, 0x8FDDE259F7629C3EULL, 0xCD47FD169C70E3C5ULL, 
            0x11DDED3422C2D57CULL, 0x30F566176547AA82ULL, 0xB0E73298B0142F91ULL, 0x4A5C511B8D64F7E1ULL, 
            0x78E5DCE6A668BE6AULL, 0x0ED91C05C6A7045BULL, 0x915CCB8838FAB861ULL, 0xC6861A4C2E1DCE12ULL, 
            0x7EDF8BDEE9EC334BULL, 0x461BB5DA750C6A2BULL, 0x5AE56CB090DC34E0ULL, 0xA83976B01ED7DC71ULL, 
            0x9381C9C81EECF7DBULL, 0x4145724C0736F1C4ULL, 0xA06CB78D77C5A043ULL, 0xB2BE02F5357603D9ULL, 
            0xB459F2F16F54A201ULL, 0xD4EB5E6E05754A71ULL, 0x8F88A89E42CAC4DEULL, 0x6E4B9211A5B2B325ULL, 
            0x0CDAD312A931E1F0ULL, 0x159211DB23BADA3EULL, 0xB4514EF9776E946AULL, 0x24ED7A715F0E05ADULL
        },
        {
            0xDD5479A2C9CDDBCBULL, 0x20D4627DFF028C74ULL, 0x8FA745003B683DE2ULL, 0x668B632E6B6F9D9CULL, 
            0xB950EF88B8EEA29AULL, 0x4105F640213434EEULL, 0x52EEE2E045EB6DD2ULL, 0x63798BCF73C76818ULL, 
            0x8A03D4AE8FE43293ULL, 0xF1A55C7103A20FF1ULL, 0x05EA5D376D7E2952ULL, 0x94C73F95E75AFFA8ULL, 
            0x11AAE5613BCD7A59ULL, 0x5C3E13CD1FB87461ULL, 0x690A2CBEC903558BULL, 0x6FD7D8BB07897D85ULL, 
            0xC8D3295D9DCAB54CULL, 0x94C29E36946FAA07ULL, 0xDBDB3B77A0EF721BULL, 0xE496B5431F38E32AULL, 
            0x79E7F422D2CECE31ULL, 0x29ACEB798D2C4EF9ULL, 0x1A9EFE3885410585ULL, 0x25AE221724E06380ULL, 
            0x88B836382E3DA6E0ULL, 0x41F2740A3C85A7E2ULL, 0xE2FBA997D9DBE4CFULL, 0x3F5A6D506E7D3595ULL, 
            0xAB6609FB02AC9563ULL, 0x872BA358DF604E3DULL, 0xB8FE223752592FF7ULL, 0x6ADC8AB698DBD080ULL
        }
    },
    {
        {
            0x83624FF03E106D1EULL, 0x097AE348FE4C96A8ULL, 0x4D94B1533552CFB4ULL, 0x482370AB1E64ADB9ULL, 
            0x78C56D9D75EAC74DULL, 0x58C5C69C68C1AC07ULL, 0x1F9D66ED598052F7ULL, 0x2AF28FF3FE185055ULL, 
            0xB2D3F107C64ADA6DULL, 0x0ED58934DEE6066BULL, 0xD8E10FC176A8D381ULL, 0x570EBDBAB870C198ULL, 
            0x93DA874ABCC3AB6EULL, 0xD514595FD47CC5CFULL, 0x74751DD9023707E0ULL, 0x024D7C3DCA46FAA1ULL, 
            0x46FF19A3DE8FCF0DULL, 0x629093928ABB116CULL, 0xA882F78F17D3F9AAULL, 0x022D68D98FF48B30ULL, 
            0x279651519AE6A253ULL, 0x6F0530AE71BDB230ULL, 0x99DAE1F6C9B0B878ULL, 0xF0DD211BAB702DCBULL, 
            0x06BF334AA2BBE9C2ULL, 0xB475055F8857E6B4ULL, 0x90EBCB0A20D73443ULL, 0x839A2C105F88C9A9ULL, 
            0x1298DC1A0F6C88A3ULL, 0xA97A1384A0429EEAULL, 0x9245FF374464BFC5ULL, 0x37BC09E3ED9B76F8ULL
        },
        {
            0xDFC98A994C7850F6ULL, 0xF6544039CF2E6563ULL, 0xED7D248B5906A4ADULL, 0x312FD82BC4D11CBCULL, 
            0xAE35DA2AD710C0D5ULL, 0x17A10748EF8FFAD8ULL, 0xFFBDEDF24915948FULL, 0x9A4A6425266A11D2ULL, 
            0xC6775D360B01CAC2ULL, 0xDA7AC715EC891360ULL, 0x5EE26AE49ECDE5ACULL, 0xBF1D2B223814581FULL, 
            0x4BD14C7DFC680F79ULL, 0x7CC79599E4BAC708ULL, 0x76015AB46F70B858ULL, 0xDB2E9B328C1E8455ULL, 
            0xBB7785FA866C7054ULL, 0x0A71F60E5AC9676BULL, 0xB8E8C80C4704FB01ULL, 0x2D913C6FDC0076CCULL, 
            0x4021EAB6EBA9DA06ULL, 0x49E53A6E9E9D4667ULL, 0xE410D876A99FFC5CULL, 0x29FEF55B0278B2DEULL, 
            0xFB6FBEDC20E01D13ULL, 0xE51F44733C8EA66EULL, 0xA98B1FA1BF4F9020ULL, 0x8A9712AFDD5E84A8ULL, 
            0xB4833478F0F4FDC9ULL, 0x13C3331DD2337D0DULL, 0xCB8EB52C9F38BDDCULL, 0x7B10960E0F0C132DULL
        },
        {
            0x569CCA99EF97D752ULL, 0x9F7F2164D04F1EEEULL, 0xED822675A6381200ULL, 0xC357AD1EE23E5F4CULL, 
            0xE14791F42A97C8E2ULL, 0xA2DBDD4D5AC3BE03ULL, 0x6AED71B055BE7F44ULL, 0x452FCEFE463DAF7EULL, 
            0x6268450E5A9A6997ULL, 0xA35AF2574C4A8F8DULL, 0x8A3CA2DEA29FD968ULL, 0x24DF7CD8387BE26AULL, 
            0xCB575C30C6B6F5CCULL, 0x1C0314DC9D0629FDULL, 0x7929F54B8C1BA405ULL, 0x8E89F51F20587507ULL, 
            0xBA117587C6F1B3FCULL, 0xCB74E729FD2B7207ULL, 0xE49CAF1F6DD7A060ULL, 0x68C2C04AA590EB33ULL, 
            0x2C4958F84749549DULL, 0x413C64A9B69623E7ULL, 0xB69E06CA6AC6B561ULL, 0x43A731BA5E7523F0ULL, 
            0x7AB9045E4692AABBULL, 0x5675808211E8EB1FULL, 0x7CEC64352B5582D4ULL, 0x6B1EE3C06C1D5C3DULL, 
            0xE5E490D8168871CBULL, 0x58403481E04063A4ULL, 0x3B05036B4A580F93ULL, 0xA6C68988A85CD745ULL
        },
        {
            0x73A645C4063D4D9CULL, 0x65A9749D409DEBECULL, 0xFACC0A325CA46334ULL, 0x3310A20FA765889EULL, 
            0x549EE9280E2F1E06ULL, 0xD980AF7CAD372230ULL, 0xA6CF3A01F8A74233ULL, 0x966FCA6618987877ULL, 
            0x922A684E5A8E8F28ULL, 0x4B2E46D5E27DC064ULL, 0x2F3977E760FEA0FAULL, 0xF2A5405BB5DADD8EULL, 
            0xD368EE63E79351BBULL, 0x672F4ADB0C7D0E35ULL, 0x8F703EFE404C428BULL, 0xCDF4B59B7C4E570FULL, 
            0xD26EBF2BCF8A06C3ULL, 0xB6BF015EFEC8521CULL, 0xA5AAFF5B2ACAADBBULL, 0x7D41F7960528F49AULL, 
            0x5051AA7C66C6FDD5ULL, 0x94205520E3508C30ULL, 0x2B05836F1AAC5D1AULL, 0x3CF40F1EBCB8B52EULL, 
            0x21FF57337C51EA07ULL, 0x83AF46C334B18F35ULL, 0x911931D80222C1F9ULL, 0x109B719EFA81C41AULL, 
            0xE983F87B8F7C853AULL, 0xB191E4A230888BC9ULL, 0xDFED45F2F02ED10DULL, 0xEA7F6268CA909883ULL
        },
        {
            0xE3EDAEE5C83B1571ULL, 0xC3B8AC6A87CF5472ULL, 0x888AE17227E6156CULL, 0x029BC7805A27FD4BULL, 
            0x07E06DDE57449B8EULL, 0x3A85F9D131563D70ULL, 0xE5E399A94C4B1D3CULL, 0x2DA4D97018A83A4BULL, 
            0x3DAF2BB32BC8A068ULL, 0xEE919012A87421AAULL, 0x091A6B76FD358F6BULL, 0x96C7E6BB4D102A6CULL, 
            0x17AD7791CA193379ULL, 0xB5F48DD66DBC9E46ULL, 0x1B79DB4201751FC7ULL, 0xB52DECFA81E56741ULL, 
            0x34D27F592A19EE63ULL, 0x28658CBA0EC4A674ULL, 0xB4DFA18C99D65A58ULL, 0x563F5CB3B02454D8ULL, 
            0x478E8F65C030509AULL, 0xE07AF207C109F19EULL, 0x1AA478E955A90E90ULL, 0x333E1A6C70E7F28BULL, 
            0x261047AD6A04CE27ULL, 0x35BA9617C1E2ACD8ULL, 0x7E9EA9CCE7A8C64CULL, 0xB402C87163C8AE72ULL, 
            0x680A51DB2ADDE0F0ULL, 0x8862C0CA17A70E30ULL, 0x381EA32E7D45D5BFULL, 0x1C19BBE5F7CA5680ULL
        },
        {
            0xD0FC1D99E473600FULL, 0x724EEA1203F8E61CULL, 0xD91C421B864823E5ULL, 0xF6190FF82E177DD0ULL, 
            0xC6FDE457068C379DULL, 0xC986CC85FFA10717ULL, 0xE959F98DDCD43D2FULL, 0xF270444FF9D15E63ULL, 
            0x942738CD66B02E7EULL, 0x7E4B375760922597ULL, 0xC7490674C3DA5EC2ULL, 0x8916D38B78D6B7BFULL, 
            0x53E9454B7216D792ULL, 0xBEDFC64BC3D3F00DULL, 0x7796F8A6CF310650ULL, 0xBE0DDF590001A56DULL, 
            0xBFF099EC5697FBC4ULL, 0xD093448B16DE11ABULL, 0x1DE8AAB532AA5145ULL, 0xE23261FC86BA74D0ULL, 
            0x3882D069543FD8DDULL, 0x021EC4698CB1311EULL, 0xB896A39061BC86B1ULL, 0xD2F7813E60D959AEULL, 
            0x46CED117D60EDB12ULL, 0x2AAF74AA7F654CE8ULL, 0x56AB253531A7A61CULL, 0x588F361452BF7B27ULL, 
            0x1A574605D0B752A1ULL, 0x343BAE8AF51B97DBULL, 0x4EBECE99B5B5B498ULL, 0xB548320FC9EE0BF5ULL
        }
    },
    {
        {
            0x4EC54A0B5519D3B3ULL, 0xAAE968252820E251ULL, 0xF1AAC561BB99CD4DULL, 0x1609129CADE18692ULL, 
            0x5A40EF09C65D27A5ULL, 0x57A3D47C9253D27BULL, 0x3845AF11F5DBE919ULL, 0x544562E0D3C94BF9ULL, 
            0x1757BC7F92325DE9ULL, 0x3336C318D3233715ULL, 0xF02E685861E28D8DULL, 0x033A23B0509BA009ULL, 
            0x6176DE5FE7BD4EC2ULL, 0x32F7C289AAF191A7ULL, 0x7532023ACDB2A96FULL, 0x87B1E0753BB30A65ULL, 
            0xDFFF72F9CD0F8F2DULL, 0xF1F7079F742341FAULL, 0xEE427FA462519EF2ULL, 0x2A909E60D19BF4BDULL, 
            0x89217A4BED99C9BFULL, 0x32E010035250A16EULL, 0xCB89BFDFF07334B6ULL, 0xB044BAE5BC740473ULL, 
            0xB1CE0DD06E06DE33ULL, 0x1E9F5F759C78F031ULL, 0xCE857691DBBE745EULL, 0x447C2B3289DB8A27ULL, 
            0xA4236F9EEB730414ULL, 0xE6C005D0758BF00CULL, 0xFDC618228B629A10ULL, 0x3959F59E725D9EE0ULL
        },
        {
            0xBCC1C8BD27C8856AULL, 0xB6B146FB6F6EC981ULL, 0x5597E148550DCA74ULL, 0x30272313EEFD6BDEULL, 
            0xC11D73FAB2CD2F88ULL, 0x6EF5CD3142CB68CBULL, 0xBDD064B2A1D2683FULL, 0x7FD642E14EE98C07ULL, 
            0x013E6CB80FF4C4C2ULL, 0x8B1C7F404550FC7FULL, 0xC227EB5A2F91B656ULL, 0xEFA0CC1BBBA42C71ULL, 
            0x1EC08D2E0C8FC4B9ULL, 0x03361ABC23570FB3ULL, 0x91534514AEA55256ULL, 0xDFE829065BB14D65ULL, 
            0x9FDD065FC5982D33ULL, 0xEF0B2FA13ECA0A65ULL, 0x81E8CAA26D33FE96ULL, 0x492CA86D71BB940DULL, 
            0xFB6E5ABC707E6F30ULL, 0xB993DE7C9CFC6B8FULL, 0xFD522BA6969B5027ULL, 0xA2A05EB0E1780757ULL, 
            0xFF406E37016BA3A2ULL, 0xDA71A142DFB0A4C2ULL, 0xC9680700CCD5B4DDULL, 0xD12C4EFB4CF77D35ULL, 
            0x7669D416B47F14E5ULL, 0x5F00D445B40D957CULL, 0x991DEEAD0E2BC62CULL, 0x494F2F8DF41B4A09ULL
        },
        {
            0x11438DFD958F5F5BULL, 0x8623CE2766C0BC55ULL, 0xFA325B60CF9861F5ULL, 0xD5A345A672978550ULL, 
            0x2892295DE04E9BFDULL, 0x80F60202A6DCFA35ULL, 0xD77078D74C746EB1ULL, 0xACCB2CF651C08B01ULL, 
            0x530F3E4659BFF26FULL, 0xF6C4A337DB768C36ULL, 0xCBC924A8926B9BC5ULL, 0x5E304BC134F5166BULL, 
            0x7733F31A833BAAFEULL, 0x8347A0F0020C9D05ULL, 0x18439E8933BBC35DULL, 0x51830FF34FBA6DDBULL, 
            0x9101D4DB5FA9407BULL, 0x81F585E7E395433FULL, 0xBA3ADF5AD88E81F8ULL, 0x1D5C48268B1687C7ULL, 
            0x2AB572FEC361BE8CULL, 0x121BD379D9269084ULL, 0xB3ABA4712E077FDCULL, 0x639D73216DC7569DULL, 
            0x166D50BF3B7DA933ULL, 0x3A13AEE99B42C1C1ULL, 0x995C9181B5400C9EULL, 0x120CF9ECA082117BULL, 
            0x347EDEDAE6EBE134ULL, 0x5310B4D50B30DB90ULL, 0x3E50A2C9E72883B6ULL, 0x70194E411DE90340ULL
        },
        {
            0x6841D07CE86D2DEDULL, 0xFC23501EA43EAE0CULL, 0xB09427F863C92507ULL, 0xC858803D86814EE7ULL, 
            0xDDDC38A397752520ULL, 0xDA0B310F3CBDA0ACULL, 0x32737807542D98A1ULL, 0xDEC0B434556A0A54ULL, 
            0x727CBF28C0C17263ULL, 0xF04A2308A5A18D1AULL, 0xC74EDD1D71781E18ULL, 0xFF37B0FDC49FD75EULL, 
            0x59D6B73C7D199B55ULL, 0x45417F47CC79B522ULL, 0x8F2DE3EB64377375ULL, 0x51E375AD29F99A23ULL, 
            0xFB4C8A8334610158ULL, 0xFEC90E32A28C1401ULL, 0xB9CAD6CF10CD4385ULL, 0xC6F1AA8AF35051D1ULL, 
            0xD2F8F9ED14E6140BULL, 0x8E4633E46C658128ULL, 0x196EF9F16E7E54C5ULL, 0x2FA1BDA319492EA2ULL, 
            0x50B593B226B58FD5ULL, 0xD791F2B743C6E0FDULL, 0x050D5D560227BFD2ULL, 0x900660D66EC8D1E6ULL, 
            0xFEFB9C3F5E34F984ULL, 0x0FE413508F7975C7ULL, 0x90DAE3E1FD41DDEAULL, 0x36D95FD396AD0680ULL
        },
        {
            0x9C279E77AED08F3BULL, 0x66B79123D300CED7ULL, 0x803D1255B9A02E94ULL, 0x7190864BDA5B8AD9ULL, 
            0x070A378E5F243AA1ULL, 0x0450162F4DD1D400ULL, 0xB7F63528893F961EULL, 0x947A11258A02CD9EULL, 
            0x92ACE1D5B19A4C86ULL, 0x5CA88C316D5DA191ULL, 0x2A05E54621D0D1E2ULL, 0x153DF5C23160D4FAULL, 
            0x7B617D333A3088B6ULL, 0x665DBC7ABB3825A9ULL, 0xB86AA7462020E47CULL, 0x20B9FAB68E508681ULL, 
            0xBC3790E2D654396FULL, 0x515AD670FD2063C6ULL, 0x1A9CDF93833F5E90ULL, 0xE5A8CD978102FAF4ULL, 
            0x1FE2943E8F29B326ULL, 0x40D62B6C42F7E866ULL, 0xC5CFBD9433D12402ULL, 0x78C6476E19A86B88ULL, 
            0xE896B367BAEB4CD6ULL, 0x6E52AF544DF88D51ULL, 0x0DBE7C53CDA3BC02ULL, 0x0E357FAB97DAE7D7ULL, 
            0xCA9329493B2C2BDBULL, 0xAC749F7A0D980CFEULL, 0xC167B41B1FDF6217ULL, 0xCEC57859684AEA86ULL
        },
        {
            0x7773BA84E168BC3EULL, 0x1A29B185823A6454ULL, 0x6B9316F8A4B8A3B6ULL, 0x64C920DF99869955ULL, 
            0x39A8C30C305F2A9CULL, 0xD5C4E68E3651F965ULL, 0x4BF2ABDB6BBA0249ULL, 0xDE3C164DB014807BULL, 
            0xE56B8FDBAB24E21FULL, 0x70C4518B8E333500ULL, 0x63B94CA40226DDCCULL, 0x0D2DCECB7F29A5F0ULL, 
            0x02A03126F670DAAEULL, 0x3C990F8FB2A0545FULL, 0x652E5AD6854016C6ULL, 0xF17D4C0D4E793EB1ULL, 
            0xA70C29D59A343BBCULL, 0x233ECB2368D2CBE2ULL, 0x48CC1DA0D2D88430ULL, 0x24956D77C42FDEC9ULL, 
            0xD3F20B0E232C3356ULL, 0xF881DE975D6317A8ULL, 0xB9C40F2E2A64E719ULL, 0x50A313EE48E302B2ULL, 
            0x03CEB9E913E91A9EULL, 0x0437F762422E72F3ULL, 0x024246FD6DC19CDCULL, 0x6DAC0A8163AC898FULL, 
            0xC419EAB772E45D5CULL, 0x616B0F9652604C4AULL, 0x1A24B76EB881F0A8ULL, 0x8BCE642CC6CD299FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseDConstants = {
    0x9D074EB05BDB2C78ULL,
    0x9E4CAA5802EA6985ULL,
    0x23534C12B5813426ULL,
    0x9D074EB05BDB2C78ULL,
    0x9E4CAA5802EA6985ULL,
    0x23534C12B5813426ULL,
    0x322C9ACC3E2E68F1ULL,
    0xED5997FC8E9739FBULL,
    0x3F,
    0xE3,
    0xC8,
    0xA9,
    0xB8,
    0xCE,
    0x9F,
    0x04
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseESalts = {
    {
        {
            0x3F8AFC702B717AB3ULL, 0x1B166E6988083B6CULL, 0x20C4C9D16D07F962ULL, 0x3B912FCB28432C2BULL, 
            0xDB309B556CBF6CD3ULL, 0x24D9AB7D2CCAA852ULL, 0x8A6616A51CABC133ULL, 0x14338C41D662FE22ULL, 
            0xDE9AAC7C35C4173BULL, 0x8DEEA3E1FCD8AE33ULL, 0x9B338D07454E3CB9ULL, 0xE532DC1DA078EB34ULL, 
            0x23C39B8874EC112BULL, 0x2227BE58884FF53DULL, 0xE02FA8A72E6C1E9FULL, 0x122ECEA384737CA4ULL, 
            0x6396A364892F4A1FULL, 0x30880D06A4EC80B7ULL, 0xB3E1A1FE34A1711AULL, 0x7255F6F48AD21586ULL, 
            0x80D8A8EDA810D776ULL, 0xA542ECA3B4796FC3ULL, 0xD2A7932A05494C20ULL, 0x6B75003AB6046CA0ULL, 
            0xDA8F8473CF2C06C7ULL, 0xEB8DAE1A43987DF5ULL, 0xAFB141825688E33DULL, 0x2F81CBCDB55DECE3ULL, 
            0xEFB32FEC7F945A58ULL, 0x7257020A05794C7FULL, 0x446C3DDCE07F92F3ULL, 0xE246E5D469CFB1BCULL
        },
        {
            0x1B9C463A992A6167ULL, 0x6573F839654569F8ULL, 0x4385212EFB606130ULL, 0x5A5249361474B6D4ULL, 
            0x33DE708735B55E29ULL, 0x2A689B54DB745D79ULL, 0x8E203B47F65074DBULL, 0x17E015DE83663C56ULL, 
            0x6702B33D8A40D14FULL, 0x13CA77FACC74A5D5ULL, 0x5B379FB27DC10C8FULL, 0x0D0AC3E1043848B8ULL, 
            0x80DD27F470D9C774ULL, 0x24C71425503B5F8CULL, 0xFCD49FFF8D930344ULL, 0x80323D7C71DE8AC8ULL, 
            0xAEB36F60EDEE0459ULL, 0x2CC8B73B4A758605ULL, 0xC97F3A4935E88AF8ULL, 0x64B8AEBF9D0537B4ULL, 
            0xAA28E5D164EAA57CULL, 0x8AE30775F0400180ULL, 0x90E46B4E183C2760ULL, 0x6593CC81ADACC460ULL, 
            0x48A43C0FB901E2C3ULL, 0xCF1D531AF5F257F7ULL, 0xB909371CBFAC28AFULL, 0x9F687D9A8A282918ULL, 
            0xE530EC7845FDD6A5ULL, 0x3F299A8466299810ULL, 0xA83CA4137DD44246ULL, 0xD61FF271BFF82FA3ULL
        },
        {
            0x121B8E1EDF455856ULL, 0x84B3202BD39207CCULL, 0x9E24D5923C9D1571ULL, 0xCDFDB7F8D9E5A9FDULL, 
            0x0000E327EFD1F3DBULL, 0x0B7BE05A375C1298ULL, 0x65634C346280CE56ULL, 0x718B4CBBAE6F26F3ULL, 
            0x5C06B71F777B2F5AULL, 0xE568371E8A5F1827ULL, 0x3AF05B9B779F4A40ULL, 0x73C88FE26F776160ULL, 
            0xB19478A5D8DD002EULL, 0x42D7B5708FA6590DULL, 0xF7CB52051838802CULL, 0x929D55DDA8CF67E0ULL, 
            0x353A3944C28D31FBULL, 0x2416B136DD831BA6ULL, 0x1942BF1F7092BBAFULL, 0x0E5900FEA49CCC08ULL, 
            0x36AD83401359026BULL, 0x6A9906E1AAAC984BULL, 0x0ED6B9FCCB4F7592ULL, 0xF3CCADE3C13C48D8ULL, 
            0xB6CA2B992B1F07D6ULL, 0xFCD6276F996526FFULL, 0x00800B058E8C64B8ULL, 0x696594569AE21ABAULL, 
            0x005CDBFE4EBF6A2FULL, 0x1A107B81691DFB01ULL, 0x0E2F9530D7F5DDE4ULL, 0x3F24DF98A3A598AEULL
        },
        {
            0x5EA45844ED86FA74ULL, 0xA9FAFC088ADF6CE1ULL, 0x33BC34FFBC31B928ULL, 0x7F9C0392E1A0125FULL, 
            0xC125EC3B264CE1CEULL, 0xA4BAB8302ECFDA25ULL, 0xE2ECA336CA1A1407ULL, 0xF08DBD5998720E31ULL, 
            0x2CB65C0BBC54C8F8ULL, 0xA58DF47918FFC9A5ULL, 0x3708F11D4D76C2D0ULL, 0xA4118FD17091FF10ULL, 
            0x9468246B84920C8FULL, 0x0BBC03419156F511ULL, 0x79172AFA0FFAF8B4ULL, 0x3623F6E9918EEF52ULL, 
            0x2FDEC6B0BB1DDF1EULL, 0x9B7D26B2CB09330AULL, 0x7F77B3907935232AULL, 0x2436BC4380EF4571ULL, 
            0x620C62F3337BA6B6ULL, 0xDEBB1FAA32DCA3C6ULL, 0x461B2A34EA3E206DULL, 0x64B8A2CE9C49BA76ULL, 
            0x7F4509BE25D67BEEULL, 0x7B5F59DF6B51F200ULL, 0x2D6D1ED0F7ADEA6AULL, 0x9B19F3F96A88AE25ULL, 
            0x825FF02FF9382FE9ULL, 0x6BD00E46C11DA085ULL, 0x9D5BD57D60AA365FULL, 0xC75F42FA148C8657ULL
        },
        {
            0xCC7047310522083CULL, 0xFFD3591254592734ULL, 0xEA1C09DFC9600C30ULL, 0xF065A66991142725ULL, 
            0xAA57F8C65E52B6CBULL, 0x400EB3088916B364ULL, 0x183643F7AD4EAA3DULL, 0x2786A29330C5551DULL, 
            0x236FDAFEBAC0E93CULL, 0x76A134F2E1B4838AULL, 0x00E56B2C51AB44E5ULL, 0xEFA0D7AB9CE925BDULL, 
            0xC8F023C138106AEAULL, 0x1FA3394191FAA196ULL, 0x9C1C0081AF1DCD0DULL, 0x06EBE13032838938ULL, 
            0xF6BCC585F3F8C600ULL, 0x3DC73109DEA22D1DULL, 0x040F378A733958E2ULL, 0xF1325816956544BFULL, 
            0x7F77E4A9BA4A6908ULL, 0x3D0C8E679234798DULL, 0x2E75FAEB9E558D1EULL, 0x9B5BB4DAE507F4B1ULL, 
            0x304E03513BA0E86FULL, 0xC23881A5D82F0A22ULL, 0xDA643E6E751756C8ULL, 0xB038BBAB0CEEDD6DULL, 
            0x3520646037BCD67FULL, 0x00B3AB64097D2E0CULL, 0xD48D8527D43187FEULL, 0xCFF2DB433EAA68B0ULL
        },
        {
            0xE255BF9CE35011E3ULL, 0xFF34BE57272BC23BULL, 0xB6F0741C6130AF35ULL, 0xE1FDDA0A2E9FB893ULL, 
            0xA39462AF26A6C52FULL, 0x6AD03B3A893684D6ULL, 0x560856D66579DD1AULL, 0x12F77226F196BBBAULL, 
            0x96DCF99AF8F1FBD2ULL, 0xFD42015301B5CB26ULL, 0x6F75A81EA6965017ULL, 0x82CEB31FF79E2B8FULL, 
            0x09DF03839AE81218ULL, 0xCC45149CCB3B7FACULL, 0x08D3CB49DF2C56E0ULL, 0x13EBFF8D161178B6ULL, 
            0x38FFD218C73D2BA4ULL, 0xEDE7609CF9124B3DULL, 0xD33D2A28E90349C9ULL, 0x1AC72480FE81DB28ULL, 
            0xF47698FFE2DCBCFBULL, 0x9B0A829EE59CDAE8ULL, 0xF19E74937CE618DDULL, 0xA0A9193716027DF0ULL, 
            0x06B65BABCB062E4FULL, 0x3EB94C7E11FD2287ULL, 0x52193CA86B46FE01ULL, 0x1FF78196D779912CULL, 
            0xF7578B30C0E8ECCFULL, 0x42A7C22BB9793D05ULL, 0xD7F9D3E640A7E916ULL, 0xC8A159AEC004B841ULL
        }
    },
    {
        {
            0x3CE484CEE67DF808ULL, 0x55BFA1DD8CD8B6F1ULL, 0xBAB4061831C4FAA8ULL, 0x4EF61C0A9CE08EE0ULL, 
            0xAE44F626E5A63BA5ULL, 0xEA5A39240456A2F9ULL, 0x2A79F20B5939114FULL, 0x88280D836CD3BA47ULL, 
            0x7C3A8A564CDECDBAULL, 0x2661EEF6A5CEB80DULL, 0x55EE956FD7ACEF73ULL, 0x0A9C65C7479DA016ULL, 
            0xE876A86E0900A997ULL, 0x2266409FE66036CEULL, 0x26AB18819AD9080FULL, 0xC01EEA5EB46023C1ULL, 
            0x16033DBBA23A0295ULL, 0x76873143B7FB5B32ULL, 0xBB74DB56C6FE1D8FULL, 0xC362B5D01F4353D2ULL, 
            0x1920F1C542852774ULL, 0x33D6CB1AB5AF7A4EULL, 0x7990459AEE4A88ABULL, 0x628A1064FA9ACAC6ULL, 
            0xD0EC263566756B7DULL, 0x942DD7D81DC31BE7ULL, 0x56AE1806CEBB2783ULL, 0xD1FF1B292AF10930ULL, 
            0x06691ACD63045E84ULL, 0x944F40610547A037ULL, 0x49A9566579F5D3D3ULL, 0x3C622417CB39798BULL
        },
        {
            0x010CECC4C174C5D4ULL, 0x28BEF9E61D70E05CULL, 0x022E3F71CE185498ULL, 0xDBD54E91F143A9E0ULL, 
            0xC7A370B534024D88ULL, 0x2C3DFEEC3A9CCDEDULL, 0xC9FF6049F7AD753BULL, 0x023C559E62445226ULL, 
            0xCC33B646F9307153ULL, 0x75EEE9D5D5FDAF3CULL, 0x439FD82DAA147F55ULL, 0x0A33585CE4514641ULL, 
            0x523CE3722C0F393FULL, 0xEE036B90F11788B7ULL, 0x9B60BC513C35F7D7ULL, 0xE44B6A37DBAFA4ACULL, 
            0xC70F8C8DC6BF8817ULL, 0x2A2154D2CFF5B648ULL, 0xE78CFD694E449D77ULL, 0x732BA2ACFE20B88CULL, 
            0x29A9622C7897552BULL, 0x9F15FD9A2C605598ULL, 0x6AEDED509509F53EULL, 0x0ED86AFC613006AFULL, 
            0x5D7E13808944909EULL, 0x2D16A671601CA785ULL, 0x6A811714E732981BULL, 0xCDFEFDD621064891ULL, 
            0x7732B1F4EF43676EULL, 0x1B33FBBC13949313ULL, 0xAB01EEDFCBE4C20FULL, 0x16B6AAEBF7F33F38ULL
        },
        {
            0x42710FAE4EDE8255ULL, 0xAC521C5F0F8404B9ULL, 0x9C156B4312DC2467ULL, 0xD340C7AAFA6A7604ULL, 
            0x61C2B8265574C3A7ULL, 0x33DD581AD10CAB7DULL, 0x941AC641B54FA56BULL, 0xE913AAFF797F13A5ULL, 
            0x91357DFEFDB98A0CULL, 0x5CCF202958B8C296ULL, 0x2DE579451FC8F03AULL, 0x83CAD8DDFB919294ULL, 
            0x04F64543139B0299ULL, 0x6AA08829A877824EULL, 0x2CF87885CCE0D6A8ULL, 0x8AC4B53148407397ULL, 
            0x414CD95FE587CE6FULL, 0x455173DD83FB269CULL, 0xB2C67FA7D6576A72ULL, 0x10CED0AA711A99B4ULL, 
            0x9ACB3CB226316DDFULL, 0xF3498F7D62472736ULL, 0xBC72230DAE48796DULL, 0x3C4DEACFCD847096ULL, 
            0x1189AFCCAE43875CULL, 0xD94567B17A2A82F9ULL, 0x73D30DE368AA03C7ULL, 0x263FC10F24ED5CBAULL, 
            0x24DFC36BA6C55AADULL, 0xCB9B1AF0287100BDULL, 0x34FA995AE625AAE0ULL, 0x796E7B01D062B4F0ULL
        },
        {
            0x1DACBAFB9DC9DAB9ULL, 0x40B0906B4A41B337ULL, 0x196CFBCEFF4ACA5AULL, 0x77496CA878CB8CDEULL, 
            0xA587877E9AB5A78CULL, 0xB4EAB3B06BDF8188ULL, 0xBFDD07D024634B09ULL, 0x1BAF4B26C60D8BC1ULL, 
            0x75FE465AB1697679ULL, 0xF544D026B9BD2A56ULL, 0x115A7160853C5AC8ULL, 0x896C231B05ACB2B5ULL, 
            0x0AB814B555402C44ULL, 0x75D50D7157BAA03FULL, 0xD99EB30422EF6A1EULL, 0x22D2900EE1CA4080ULL, 
            0x435F75858204680AULL, 0x198F465D202F5005ULL, 0xF661F2C12BCA66ADULL, 0xA856D35695EBBD48ULL, 
            0x11813B1F098A4254ULL, 0x607FA7ABA7E8DBF1ULL, 0x45EE243B2AA6471AULL, 0xDC7B05826661A435ULL, 
            0xB8DEF82F87C1C215ULL, 0x0D3AD1962087E4B9ULL, 0xD9B7C53A19A495C7ULL, 0xAC6D44D66C36C27AULL, 
            0xD1B4DE5C481FEF93ULL, 0x570141F7A28E0CC7ULL, 0xAE4799A9899404EDULL, 0x93C277EA4516AD72ULL
        },
        {
            0x7A59E1731252CE42ULL, 0x11F3057BBCFC5D4FULL, 0xC4B16817FECAA899ULL, 0x9A781D24A155B5F6ULL, 
            0xCE22FA5791BD292FULL, 0xB867F49CCA677861ULL, 0x522B63E00C6CA564ULL, 0x4092EC9EF56ADF1EULL, 
            0xD7C7D9544CB0058BULL, 0xFA375C247005104CULL, 0xC1DA01C6C627A645ULL, 0x6E06E8B55B84B3C4ULL, 
            0xE41EBFBE71EDA110ULL, 0x53BB9546B09B770AULL, 0xF5EAC6F224DF1A9FULL, 0x725E01929B2ECD27ULL, 
            0xA30B0850DCBED406ULL, 0x1555D580B1F358F5ULL, 0x3A6606936C46C3C9ULL, 0x1AFB93990DA66BD3ULL, 
            0x3C8557CB09CCC86FULL, 0x3F7B9092C36B0EE1ULL, 0x793C8EB24B029E9CULL, 0x30D27B57B45D3DF2ULL, 
            0xB5F37CEEB36AF7C6ULL, 0x7B425AF66D8FBDC1ULL, 0xA083EA1CA1BABF8FULL, 0x8F903D5064A044BBULL, 
            0x12E1E1A97456E1CEULL, 0xD1E91BFC97B8F3CAULL, 0x76ED9ACA7E58D30DULL, 0xBF78F7F5EFC61CB6ULL
        },
        {
            0xA76BD798CDBEE441ULL, 0x7B48BB5F4191B41FULL, 0xC0F8499FA4413EC3ULL, 0xCF6A393583B08FD3ULL, 
            0xA2C23538A835D821ULL, 0xC25BF7F64BB3ECE5ULL, 0xEF67ADEAD120D3B5ULL, 0xAB03AB1A74DE0DD7ULL, 
            0x7CE41045633C6E96ULL, 0xD381075ABF906234ULL, 0xD975C4A327BE65B0ULL, 0x911D441FE923F6B5ULL, 
            0x5E608A14E5EEE577ULL, 0x278ABE8D165865F2ULL, 0x64738C452EA10369ULL, 0x2523813B348BD871ULL, 
            0x6ABC3E6BA18A2E0CULL, 0xC0A456EB4270FC9AULL, 0x644BC88221C69EE4ULL, 0xE5DA9B3DDC60F727ULL, 
            0x26F5BC0CC1AD1644ULL, 0x294BD209DCABE341ULL, 0x622408EC9F61AC2EULL, 0x4127E65BDD7B66EAULL, 
            0x8F221C4EAC5B3A17ULL, 0x11FC0004915AC295ULL, 0x9B2ADD778B09CD05ULL, 0x4602B9F64707D3CEULL, 
            0x1E88B30EBF0C6965ULL, 0xB00C7BD46C8D8DFCULL, 0x46C38D976697CC42ULL, 0x6998E1238FFCF660ULL
        }
    },
    {
        {
            0x374C2BCEA8C7F82EULL, 0xF44A5859FBA3C1DCULL, 0x3AE1A8DDB32572D6ULL, 0x1464D16DD4708666ULL, 
            0x08F0DAFC6EC78031ULL, 0xAF9D778980BD46C9ULL, 0x70433C498DDBCBC3ULL, 0x5DB19CBBB69E3558ULL, 
            0xF7AD9E1A767F07B6ULL, 0x06655721BDD73B8DULL, 0xB85DAC91E39FFC7FULL, 0x8A1C2F42906C60BDULL, 
            0x5C6D91A33346626EULL, 0x0770C8BCD2C6598FULL, 0xC5D6A86B7ABC9F6BULL, 0x205716B6FE26F695ULL, 
            0xB7A3A928CBD3CDC3ULL, 0x1848F1F98734EDACULL, 0x691D7EE45535254EULL, 0x1CBD405780617B00ULL, 
            0xAB35D5EA09A7ECE5ULL, 0x3D78121D630F589AULL, 0x9C0C7184550E9935ULL, 0xFFFEE6B5EBF84920ULL, 
            0x26B8EBAB9C5CB4D3ULL, 0x5288457E0E9D312BULL, 0xE17A3986C32ED29FULL, 0x58C04B725DE85784ULL, 
            0x14979EA43EC75206ULL, 0xA8AABFEDE904EB42ULL, 0xC697FCCB3BB069CFULL, 0xC3AEFD46D12F05F5ULL
        },
        {
            0x6BD92BCEF72A484CULL, 0x7994E5C1B07554EEULL, 0xA0059B27347D2EB4ULL, 0x440A5D61CBB60B1AULL, 
            0xA2E3300302A5954CULL, 0xC176C580DBD5F529ULL, 0xC5C806EA7E5E2264ULL, 0xD8E9C23320065676ULL, 
            0xBDAB6E8F79ACEF44ULL, 0xE6BF96EF63BBAF82ULL, 0x36253508B7A58740ULL, 0x58225C76F1E10E8DULL, 
            0xCFF55F5A80A8CD30ULL, 0xEDA720FC6BEDF802ULL, 0x2AF27671AB8B6949ULL, 0x46AA01204B1ECE71ULL, 
            0xDF805E8EF5428E3DULL, 0x4463A85435A61C71ULL, 0x1E8E4D84245662B2ULL, 0x70174441952E5B73ULL, 
            0x4BAAC973DFBB57D3ULL, 0x7B1F40A5ACC8921EULL, 0x0CDD982D55538E3FULL, 0x56A7C53202FB4E83ULL, 
            0x0C736E0A2D359888ULL, 0xE1DB925E9AA78B40ULL, 0x2A8ACD53F8A0CBF6ULL, 0x6CA646B7D7BA0D67ULL, 
            0x8809EC914105F8FFULL, 0xFEF421B04FCD7838ULL, 0x867BC7D5588A9F22ULL, 0xE7036A9FA65111ECULL
        },
        {
            0xE929705C243ED7D5ULL, 0xCA5916E4AE167772ULL, 0xB0D0C8BE4D66001FULL, 0x53014FB293719D6EULL, 
            0x53741690066B3958ULL, 0x58D19668D8585B7FULL, 0xB1A619680AA06952ULL, 0x122DE2BBD0BA06DDULL, 
            0x720974E0A8652497ULL, 0x811A1681CC82EB72ULL, 0x99FD8CD0B1331EB7ULL, 0x95AC7610025BE301ULL, 
            0x846C705EF58155FCULL, 0x3D55A0BEB3820AD6ULL, 0x2E40FB6D88521E49ULL, 0xDD0C2620AE8EA5A7ULL, 
            0x7CB8AAA891A4FEE0ULL, 0x8DEDC9380C0DC691ULL, 0x31157071B5E84351ULL, 0x06E53D4414E84FBAULL, 
            0x720D0C7FB376BD1AULL, 0xA225FF3930036BA2ULL, 0x4DC26FF0DC93DA58ULL, 0x1C169F72A3DB68EAULL, 
            0xEDC8AD096E437612ULL, 0xA834D502DF29A4AAULL, 0x059A0AF85A889C27ULL, 0xA3562D9E98ABBB12ULL, 
            0x90C28CF23EC77DE0ULL, 0xF5CF30DE07BDA53EULL, 0xCF66B401E5389548ULL, 0xAA69D4BE955DC143ULL
        },
        {
            0x545A5647DCDFE8A2ULL, 0xA59251523B40E70DULL, 0x24D118ED1F4900ADULL, 0x1AC9F8CB27D56192ULL, 
            0xE81638B23BFB0EF8ULL, 0x7AE440F28FCDFB3BULL, 0x3156909D5BA82396ULL, 0xAB72801A07EC2AA7ULL, 
            0xC580F6388E27C80AULL, 0x59A3E6E8E339B52CULL, 0x400E3606938412B6ULL, 0xC3519BD442C4ABA4ULL, 
            0x15DD30A7C79A2EA6ULL, 0x52F55E9CAA4DD346ULL, 0x2E503CD64D0CA942ULL, 0x7056F52FB7F1A258ULL, 
            0xA0E2244F084590CDULL, 0x53C4A2C53197C811ULL, 0xF3EE72C70C692C85ULL, 0x716766FEE618BF68ULL, 
            0x67E84C6B0C30CC0EULL, 0x2019430752A8E224ULL, 0xD2EE614F378ED98DULL, 0x58E1A8FC05440040ULL, 
            0x853A5B8E7A1A941EULL, 0xE860A15B54C465C2ULL, 0x02A02AF4BB5C3B18ULL, 0x80EE3C23EF3378C8ULL, 
            0xA3E7E7E0650CA8A8ULL, 0xA13825F4FCFF3658ULL, 0x9ACED9C6323094C6ULL, 0xFB8F1EF403624902ULL
        },
        {
            0x65B1BB6E820529D6ULL, 0x45137AE98AA2FE3FULL, 0xB6A75241D2C48E7EULL, 0x0E5F9FA0E5BC9862ULL, 
            0x7A45E4C43FBD7498ULL, 0xA686F0DE7B67452BULL, 0x3165E16357162949ULL, 0xFF906622F9DB8842ULL, 
            0xECB20D27970DEEE8ULL, 0xA44C3447EBAC8E6DULL, 0xD4D634FE14CD9BCEULL, 0xC178D3DFA423C840ULL, 
            0xBD338A8F77FD2E0EULL, 0xDB5362DEB54BE8FFULL, 0xFE20605E7BA48329ULL, 0x3CE5662BF5208732ULL, 
            0xEE443584A32937DFULL, 0x1FB14457D1278248ULL, 0x0EACB710C6DE3A41ULL, 0xB00BB512DFBFC842ULL, 
            0x6C5633860BED4E6FULL, 0x7D4FF2EA46FAE852ULL, 0x65B33C18492490F0ULL, 0x1B504BC72DC2AC7AULL, 
            0xB9499260C27184B6ULL, 0xE4D3D3BAE9639AA1ULL, 0x21349AA5B0191A05ULL, 0x882C4B188DDADDFDULL, 
            0xF2275425B1395B31ULL, 0xD95E5992374052C3ULL, 0xA291DDCF5953E6C8ULL, 0xA7F1EB56BFBBF0ECULL
        },
        {
            0x8789AFB8B547CF78ULL, 0x8DF868D292236A9CULL, 0xC69938F986970099ULL, 0xE03340CD666CD433ULL, 
            0xCA5DD3DE10D1E088ULL, 0xF386054CE574A110ULL, 0x0B8BBB7DB58FE971ULL, 0xD46B46611217C4D5ULL, 
            0xDAD7B48359E8089DULL, 0xA6F7F0376141B0A7ULL, 0x713250C1C7AF51E3ULL, 0x754A376589C2247FULL, 
            0xADF11F12CDA44EAAULL, 0xEFEAC56AE128B6F6ULL, 0x5AD4571F3E2EE911ULL, 0xCDCC4FA8D21EFBD9ULL, 
            0x147EE14ED73DDD9CULL, 0x3AE8CCE70C3B7E2FULL, 0xE786AB63C3529702ULL, 0xF0F6B03C62420711ULL, 
            0x4C8A3EB277653B3EULL, 0x0D7CFB929CA6A98DULL, 0x60B9EB514ED74499ULL, 0x7F4AD661DBFC1372ULL, 
            0xED1FFD3B29577D7FULL, 0xB389B402E4076947ULL, 0xF9E6571344D749E1ULL, 0x39716581C7FD7AA2ULL, 
            0xCAD5C9F7D58508FFULL, 0xBB95A32BD02E89CDULL, 0x7794F3FB5C05BCA7ULL, 0x33942860C86B6D40ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseEConstants = {
    0x8C16855AB59C89C8ULL,
    0x9F46624EB56ED9BDULL,
    0x263826EAEAF96B4AULL,
    0x8C16855AB59C89C8ULL,
    0x9F46624EB56ED9BDULL,
    0x263826EAEAF96B4AULL,
    0xEF093C141FBDAAD1ULL,
    0x4630FF33DEDAACA3ULL,
    0xA5,
    0x18,
    0x8E,
    0x92,
    0x4E,
    0x3E,
    0xEF,
    0x27
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseFSalts = {
    {
        {
            0x0ED6F19D10C635F5ULL, 0xC464954A3D2EB77BULL, 0x76CF7DC45C841D9CULL, 0x2F87DCC525EDCBDAULL, 
            0xA6C3E182BF035415ULL, 0x823C884EB5F4B198ULL, 0x8556D98C65C27FC7ULL, 0xCF4C1EE60AA54721ULL, 
            0x1355D00A49DBDF74ULL, 0x020B0BD0B943FEA4ULL, 0xF7E4FEFE54AE037BULL, 0x540D493EBC6F8851ULL, 
            0x45C5A895A20D6175ULL, 0xDF8D0DAE4C0B0979ULL, 0xFC62FCB7F64E08E9ULL, 0x93250F2D0706610BULL, 
            0x5D85389F30248B00ULL, 0xE4A1798DD4BCE3F6ULL, 0x2A6058FF4F1B6A54ULL, 0x35C250C2F725F332ULL, 
            0x6C83B851CCE20557ULL, 0xA438343E31C5D168ULL, 0x3D14D075A914DF87ULL, 0x3B499F7129C7FBCAULL, 
            0xDECD680FEE144CC3ULL, 0xD6E25D39983CEDDDULL, 0x5AA86D5556081ADFULL, 0x44418484600B2CE1ULL, 
            0x0CB43804911D3658ULL, 0x581E92ED541EE819ULL, 0xE58E239C097A9CD3ULL, 0xFE4F162240250895ULL
        },
        {
            0xF3BA3073CE933BD0ULL, 0x5E2035C4BFC92B30ULL, 0xE897CD0F6AFA08D6ULL, 0x2330BB9EB8EBF023ULL, 
            0xD51A46FE37934BA9ULL, 0xD5D0B8BD0143E666ULL, 0x5BC1F82E1310006EULL, 0x0B7B749426BFDDD4ULL, 
            0xCBFEF806F475321FULL, 0x294F025F95F08720ULL, 0x976045366BBB6087ULL, 0x57165E0E831B13CDULL, 
            0xE619E8F37DDB9006ULL, 0xFCCF3A806F1AA170ULL, 0x4ED2DC28297DDE70ULL, 0x9E2062FA43FD63DEULL, 
            0xED952C8AB0AB8842ULL, 0x118BF3B5119EF424ULL, 0x12EDD8F48E9F4C75ULL, 0x1132F0B0389E1E20ULL, 
            0x6004B7A08378641BULL, 0x83BD37EBB3A647B7ULL, 0xFCEE21166EAE986EULL, 0xFA35DB8EA585D6D5ULL, 
            0xFBDFC21FFA345173ULL, 0xFB1A202B5A85E895ULL, 0x9C3CCAB0B2C0C380ULL, 0xADAF19BCE0035970ULL, 
            0x12AE3FA8E732B22AULL, 0x84F13CC0A6BDA45BULL, 0x194D16FCDD6055ECULL, 0x95DBE221D8E2F937ULL
        },
        {
            0x8104074E9CB53266ULL, 0x5F33FF1F0E0D6F82ULL, 0x18738D7E1DE4D9E7ULL, 0x2F4781A93B0E9B66ULL, 
            0xE4F524B4D79CCC9CULL, 0xAD825E6CE5B45CDEULL, 0x887EBB56C31F6C55ULL, 0x5F3BF394F380E382ULL, 
            0x7C7059B5F8F2D086ULL, 0x2812F6578FA8FBFEULL, 0xCBA6C95BB239413AULL, 0x133EC20D26AE3D49ULL, 
            0x7D315D1D121AD611ULL, 0x998A6BCD2C1B6F9DULL, 0x78F5D14C6C018C94ULL, 0x59B5E1AF1612C131ULL, 
            0x18D06130F752A372ULL, 0x0DF87BB044760682ULL, 0x5D6F072441153861ULL, 0x9F1659856A0E1685ULL, 
            0xD3B2F298416861FAULL, 0xF0A054D81DD7FA59ULL, 0x76F44C6A40DA65A9ULL, 0x34FC4D0A41C2C1E4ULL, 
            0xB5701480DA7878EBULL, 0x96DFBE33E3B5F159ULL, 0x91B3338B8407CFA0ULL, 0x091BAF07E8529789ULL, 
            0x5482A26DBF7727AEULL, 0x0399BA3BDF6CB1D3ULL, 0x99B534CB2F6B289CULL, 0x8D7F75920AC57396ULL
        },
        {
            0xA0057FB1BA0D3D68ULL, 0xD9C796CF8FD9D6F6ULL, 0x799821244A3787B3ULL, 0x9643104C03061C56ULL, 
            0x294ADBBA788F3C42ULL, 0x4E3F5B59287F1E06ULL, 0x52A570A8B24E9D22ULL, 0xAD25E01E1987A392ULL, 
            0x2A982E663AC41935ULL, 0x1E670507C0371AECULL, 0x0F4DAF74734AACE0ULL, 0x90BB6AAFD22C59BAULL, 
            0x0B3858809980E588ULL, 0x5C2444517C3C33E8ULL, 0x1FD10DD433A395E9ULL, 0x264800A5EB8CCE90ULL, 
            0xD1494AA95C9C7356ULL, 0xD7E327B8BEC580DCULL, 0x54B0BCBE41838BE1ULL, 0xBC5653D1461A9048ULL, 
            0xAB2EB01769902A4EULL, 0xFB9EF445D00396B5ULL, 0xBAEE9B8134FF7781ULL, 0xE7A003CEB4105535ULL, 
            0x02DD33101F7B67C5ULL, 0xBB0F81A83B5BAA72ULL, 0xDB9F6BEE98FEBC91ULL, 0x31CA78F1902B72FDULL, 
            0x90A8DDE96CFCE594ULL, 0x6A6C7EC3C8C2C98AULL, 0x992C4A3050394621ULL, 0x8FA049F07476767EULL
        },
        {
            0x69CB1E40804C83C6ULL, 0x52E473689C45FAEDULL, 0x6E13BE255FFB9F66ULL, 0x990B551C0BACC615ULL, 
            0x3E162591145E693AULL, 0xBC8B2F071CC0F49BULL, 0xB5FD54987653076DULL, 0xC2B64E9C328CBA4AULL, 
            0xBDC123C6762808D1ULL, 0x337B65EEBBB187ECULL, 0x1F747C7B8FE33032ULL, 0xFF436EA1F68801C5ULL, 
            0x33D813D871629EB0ULL, 0xDD56000D1DAF586CULL, 0x0880FCDC16A02C74ULL, 0xAB90E89F808E354AULL, 
            0x9909BBD7BDB8B843ULL, 0x0679731BC9927D2CULL, 0x1DCA08F158DB2019ULL, 0xBB34ED4D5F8793EBULL, 
            0x56B2913A160B886CULL, 0x8DD6D16B733C4796ULL, 0xB1727949DC46ACB9ULL, 0x3434324B88B09B06ULL, 
            0x9495B1D3F48165BEULL, 0x69C97199569C8484ULL, 0xA4F932BAAA12A476ULL, 0xA8161360BE14F525ULL, 
            0x3941D04D0D496D86ULL, 0x7FC0336C37B1EC7EULL, 0x2F08A3C3F3636C6BULL, 0x31F12746E3F018BEULL
        },
        {
            0xE086675332284470ULL, 0x8DEB3AB9A2FC0686ULL, 0xC97EB6EB134880D5ULL, 0xB7B56D4AAAFAE530ULL, 
            0xCA9DDD1C1B054F75ULL, 0xB8788B8979D16FE1ULL, 0x900A50D3CE7B5E89ULL, 0x2B63DCD98225667BULL, 
            0x44A25669E7BE23E8ULL, 0xFFAE27587E95478FULL, 0xF43D94C6957225F7ULL, 0xC8D0B39FC2E675E3ULL, 
            0x30A1A394D51507DAULL, 0xF7BCAE4FAD6F250DULL, 0x27A87E7CF0375C41ULL, 0xD76120886C5F7452ULL, 
            0x6C39972256BD4C71ULL, 0x78D575149A2D5744ULL, 0x97E6147D9CDEAA1FULL, 0x51DC4D2210C45E62ULL, 
            0x3757BA77E63FD00DULL, 0xC466E72F31EFF12BULL, 0xBF9A0E86BDBC8A8AULL, 0xDABC4EEAEAB3B9E4ULL, 
            0x15E7340FCD3CB8E8ULL, 0xF53D5EC32CD2B15AULL, 0xE1591A85A4567FF5ULL, 0x1CBA5FD680EFDA9BULL, 
            0x4F865A00B775E9ECULL, 0x6D0EACB9F3D66B86ULL, 0x85F3DCB77CCF67E0ULL, 0xCDC7DF4E09B34593ULL
        }
    },
    {
        {
            0xBEEA7C391C693677ULL, 0x12C4562E5E592D14ULL, 0xFCC116FB91F8CAE0ULL, 0xD707BA1514AB3E63ULL, 
            0xAA3B8A03A4E6D325ULL, 0x071D129F2AD3D8B7ULL, 0x660669EB682F2352ULL, 0x34FF80AE7FC468ADULL, 
            0x6BDC1026D88A164DULL, 0x5BF271EFB63911CCULL, 0x2D02BEEC9B6BB8BAULL, 0xDEEBFFEE3DA8A714ULL, 
            0x37EC4DF33AE1A2DBULL, 0xCA4C399A91D483C5ULL, 0xF750FC350D27F0BDULL, 0xB545394345350689ULL, 
            0x99B9A0BC79673B95ULL, 0x037DC70A7610A789ULL, 0x5DDEE955ED3814A2ULL, 0x874673BD4EC8DDA4ULL, 
            0xF028B224699D83E1ULL, 0x436E46DD07AB90EDULL, 0x4240271A07026093ULL, 0xDD1EA273C92D72ABULL, 
            0x81ADD484BB04D22BULL, 0x7F21C5A87EE28122ULL, 0x13E683C208AB558FULL, 0xC1936C9BE398BE5CULL, 
            0x605B7C306D2077EFULL, 0xE4B7D841CDDB56B3ULL, 0x66C88490C9CD70A5ULL, 0x3D4B2AF3B6D50A77ULL
        },
        {
            0x360D83ED636780D1ULL, 0x2A5ECB25E1DEB85DULL, 0x655D9EBBD324310DULL, 0x5B42F7E8CEF97363ULL, 
            0x14F1012FE2AAE198ULL, 0x003EBEE7B563DCCCULL, 0x5F870AD103F215C6ULL, 0x2B24346325750CA7ULL, 
            0x40E1AD797253671AULL, 0x7962DE968DB7218FULL, 0x2AB62F88FC4E51F4ULL, 0x49BEC956A5A80C90ULL, 
            0x6690E6F0179CD28EULL, 0xCF99D8318010A406ULL, 0x6F7AA9995271A08BULL, 0xDC68731550653970ULL, 
            0xB57EE73019D68B4AULL, 0xCE405D6D2240FBABULL, 0x15B3548766654545ULL, 0xC56EAC0101F06373ULL, 
            0xBB597EB24A680B65ULL, 0x76BC40394677D550ULL, 0xCFD202EEDB4F1508ULL, 0xB3421C1FDC9C37EFULL, 
            0x6EB920F85122AE58ULL, 0x65789B49EC6C1CFFULL, 0x00AF822AA945F85BULL, 0x9C959A2891230A31ULL, 
            0xAE2818A7620D373AULL, 0x9364D64254D20ACAULL, 0x1B9E95CB7F7A30C7ULL, 0xEB585522337464D0ULL
        },
        {
            0x22D4A429D358E8AAULL, 0x1A0613FB076CEBCCULL, 0xBA46FF54CFE7ABF3ULL, 0x5E0544AA13A670E5ULL, 
            0x534BCB78542B78EFULL, 0xF1985F5CBD71AD94ULL, 0xAF255D8DF74988AFULL, 0xEEBA2A1490D28BA1ULL, 
            0xDC3F0CE3DC3E0956ULL, 0x3B471EF48574EC46ULL, 0x1BE3101CA9B401F1ULL, 0xE2C74778C77D691EULL, 
            0x43CEDCA050D2EF7AULL, 0x253D0B2A231F09D7ULL, 0x464B2EAB8297ACD4ULL, 0x7971D21B7CF78AB2ULL, 
            0x6447B6937A9A82BCULL, 0x63F84DD64D1B830CULL, 0x265ACD05CDAA8EDAULL, 0x8AA2491F32383C7EULL, 
            0x59F721828B629645ULL, 0x4EF3A611C872DD2BULL, 0xB7202410A642A0AAULL, 0x69D8F6D82ED3E98BULL, 
            0x86E7C7C4B8E15E0EULL, 0xF73ADADDE0D697B2ULL, 0xAD7E1A4D9800E3ACULL, 0x8B15DB1D09D6F0A4ULL, 
            0x9841D48040992A51ULL, 0x2757573BFAC96641ULL, 0x1DCD0912847BD8C7ULL, 0x429F836F27984BEFULL
        },
        {
            0xA06A4DF0290DD93EULL, 0xD0D582F15A73ED14ULL, 0x98D7638F3B7E2AB4ULL, 0x068A241E86FA947BULL, 
            0xCF9D9AB01C9F9031ULL, 0xB4591C15F40C8FA3ULL, 0x6EAF214385AF6EACULL, 0x34D4263EE009C18CULL, 
            0x2EB0FC5CFB5A4E99ULL, 0xCC7438D62B4C4E89ULL, 0x1C3C4CB238C8DBECULL, 0xF44488EA1DE4DCE4ULL, 
            0xB60BE02F71A2D8F1ULL, 0x8426F8B7980F0E06ULL, 0xCE225C4D69E2788CULL, 0xBDAD2E9F60AD478BULL, 
            0xF831BF40F4255E66ULL, 0xA01EDC9988959777ULL, 0xAACEF944DEC361DEULL, 0xCDE73C2B91BD7698ULL, 
            0x2054A44D21CAF7C6ULL, 0x63FE19A023895AE3ULL, 0x205BB65DA1C567F2ULL, 0xFE58179272D4EA3DULL, 
            0x9411C63240AC2779ULL, 0x8998DF10EB78C46EULL, 0xD9182CC94D3746D0ULL, 0x71D79B9ADFC828F3ULL, 
            0xD9056038F26E7917ULL, 0xF8D08FB03B69DB01ULL, 0x9488342C209CFD9FULL, 0xC2AE4F7314C6CB62ULL
        },
        {
            0x27D67BA8F6170105ULL, 0xB7E21B5ED7E31C31ULL, 0xEB795A574A529978ULL, 0x6559E295EFE91888ULL, 
            0x85B2724268AE28FEULL, 0x2C8BAF093E387CCAULL, 0xBCFA6DF34698176EULL, 0x5C593D04DB9474C6ULL, 
            0xE2C7486730EAC4F7ULL, 0x7ABE62DB9916B3FEULL, 0xA444A60EDBB9A3AEULL, 0x1ACC49335765E17FULL, 
            0x5BE2F934384B8481ULL, 0x08FED08CEFA6F6C4ULL, 0x4A72C106C7185BA7ULL, 0xBE530AE9B249255EULL, 
            0x330A3B547A861EA0ULL, 0x6E8E1A0BBC7475F8ULL, 0xC7EE71E51BB4F097ULL, 0xCA5AA76CB55BE113ULL, 
            0x0817261D24942CA0ULL, 0x9D4CAD833D9C5FA8ULL, 0xD7B6301B57B2B522ULL, 0x0C34E9AB053F1B8BULL, 
            0xD38E3D7A8991085DULL, 0xEFFB7973183E7C13ULL, 0xB88686A1D8E8485BULL, 0xAA06316219EA0864ULL, 
            0x917E2E6C5B92EF0AULL, 0x138E46525B5C4472ULL, 0xBDC6862933880FFFULL, 0x8A11438ED2884C54ULL
        },
        {
            0x070D6D9B09E407BDULL, 0x10F384F11F98A55FULL, 0x9ACCADC718A8872EULL, 0x166838992E4D0942ULL, 
            0xEAB746BA2C60AB31ULL, 0x2A1733E93CC7EBF4ULL, 0x808DE2D77D72BACFULL, 0xF4271358628BF347ULL, 
            0x338D0128533F54BEULL, 0x7B5D5842A34DF0E1ULL, 0xA1E04BBCB886D375ULL, 0x47F436D24A9A4E01ULL, 
            0xDEBC2DB97C98EFA9ULL, 0x13D5C1697E73795AULL, 0x450FA71CE5735018ULL, 0x0BB558EE34654D61ULL, 
            0xCCA5F9FCEEDA37A0ULL, 0x151EDCCFF0E9EBF4ULL, 0xACDB284D1BA523AEULL, 0x61CC083F0DB31185ULL, 
            0x9712CA7345DD5BA4ULL, 0xFD04C93B1055CE76ULL, 0xC8D43DE83FFB1A15ULL, 0xBC053D3AE32D71CEULL, 
            0xDFF99C1B11291379ULL, 0x09420B5C2CD65522ULL, 0x74CACC1AE3F08A4CULL, 0xD73B893727AAEF52ULL, 
            0x8B81C1E0E3BCEC50ULL, 0xC01E6BCA98D1DC02ULL, 0xD9A7221EC2BF55A4ULL, 0xCAB647EC8E3EF4CCULL
        }
    },
    {
        {
            0x5F961E9EDA6C91A9ULL, 0xBF25379ADFCBC8A8ULL, 0xD966B06B082099F9ULL, 0xF0109C7FBD7D2B50ULL, 
            0x72426F9FB848C12DULL, 0x7C6464F744C6F90AULL, 0x2BC2B1EF9BDCEDF8ULL, 0x3E6D30E2A3F41D76ULL, 
            0x97359512B02DB704ULL, 0xAFC640E27546A617ULL, 0x0793D8F2A68B8750ULL, 0x2E2998719E92C94AULL, 
            0xF2CB378FAF196AFDULL, 0xE36421ED7BA7CC96ULL, 0xCD51D86E05A4CC71ULL, 0x01AD8C9376CF1EE3ULL, 
            0xC62003809106D7AFULL, 0x60C94C6FED56DE9AULL, 0xEF2DAB96D69CC3BBULL, 0x615EF3F3AEADCE04ULL, 
            0x76F09926D4A3EEFDULL, 0x7030053D3A81EB7CULL, 0x1B498A8233111AB1ULL, 0x0644CF0A67BBEB2FULL, 
            0xA4C148EAD0E821FFULL, 0x96316A9BDDB3DA21ULL, 0xDDE513381254C2F4ULL, 0x7CFB830610AD2DE8ULL, 
            0x2BD5DA1C658B1F3BULL, 0xF0B9B5CA1B300920ULL, 0x1F0FBC637A0F9BD8ULL, 0x6DC20BC18B47DE2AULL
        },
        {
            0x4BA3D50FB1458873ULL, 0x0CFBA82059338B19ULL, 0x5D6568E0B2DA6EF9ULL, 0xA1D31A4F988AD94BULL, 
            0x0A34FBBD44FABE7CULL, 0x55C0C975FF404449ULL, 0xE5C9919C8C9B4DD4ULL, 0xE0B2F46A9122CA32ULL, 
            0xCFF3189D24F5F674ULL, 0x248EE897482E9B28ULL, 0x70EF6F88387DE680ULL, 0x2EEB2B95CE63755DULL, 
            0xDC3C78A1DC86F2FFULL, 0x774ED67E12A2088AULL, 0x9DD109A4279BBF80ULL, 0x96D7F8328597739CULL, 
            0xA224FB6A786F61AFULL, 0x46CD897FA7A9FA1BULL, 0x81F26C1AFF84491FULL, 0xDCDE3C8D241DF8CAULL, 
            0xD52C9CC838EEFB13ULL, 0x5DD14CEB9F9C10ABULL, 0x9E69191D205BDC8BULL, 0xE3A11AEB9EB6DF49ULL, 
            0xC14E6FFB41824076ULL, 0x89E7F7BAA6EEAA8EULL, 0x98711F2BD7FD0DCAULL, 0xDFEFF89855066C24ULL, 
            0x4F861692F45F5FE8ULL, 0xFA8C7CDA44430AE3ULL, 0x68293BBFAD5F5B41ULL, 0x54F0A7EE0626D336ULL
        },
        {
            0xF585CAA65497F173ULL, 0x9002568EF43BFA15ULL, 0x54D49FCF22F591DEULL, 0x51268A2FC5B7B4D5ULL, 
            0x886E8804BEEA85B0ULL, 0xA1CD329FA3F69EF2ULL, 0xCBD2860C65B3ED56ULL, 0x0B891C12514F7465ULL, 
            0xD98C9FD85B25E75FULL, 0x94143BCDCFBDBE52ULL, 0x80DC6FCB27CA6EC5ULL, 0x5D561CA397A3A031ULL, 
            0xBC441D16451DE6CDULL, 0x1A91A84D83313F05ULL, 0xC14C6960F091FC4BULL, 0x1A345EDCFD661F07ULL, 
            0x7053AB7886940B04ULL, 0xA50FE448CE3C1ABDULL, 0xD3D9AF0CE56A5EE5ULL, 0x3534A72FB2091F36ULL, 
            0x26A5D1819D7FA4C9ULL, 0x78366133FD51C693ULL, 0xEE52D28D20CECA90ULL, 0x8E5EA431B42B37E1ULL, 
            0x055B4CBC4F5CF56EULL, 0x7A1FDC717FA50AACULL, 0x5D19B5A7BB66CEDDULL, 0xB8D6BE07AEBA1BB6ULL, 
            0xAC1BA49CE4A56202ULL, 0x6ED02084370D133CULL, 0x0597E53CEBEE3E0CULL, 0x47082549D2594EBAULL
        },
        {
            0x9BDD2AD6044B035EULL, 0x4FAD5786B9E2C9F6ULL, 0x9AC732C2F83E1357ULL, 0xD77DF05797A35F9FULL, 
            0x32E9B20C1555BFAEULL, 0x85F873CCD088380DULL, 0x9A59CF25C12B1155ULL, 0xE80D93438E229F5AULL, 
            0xDF5F5C461859631FULL, 0xFBD6E234EF22D9BBULL, 0x124BEFE83109DDB2ULL, 0xFEFBFEC2E9D22676ULL, 
            0xE12003395393B646ULL, 0x62B41CE1F481DEF5ULL, 0x8935C33CF81B702BULL, 0xB13ABB39F18B5111ULL, 
            0x61446DD3F2A99E81ULL, 0x9781FDF55B8835F7ULL, 0x5DC42F5CA7ADABD2ULL, 0x7FFFA8D987B7F80DULL, 
            0x3A3F6A93221F870DULL, 0x35FF1AFEEB2FEB97ULL, 0x16B52C11D6496C34ULL, 0x2A6B98546FE07EAFULL, 
            0xF07B85A8B8075787ULL, 0x3B926F425360971BULL, 0xBF3932138BE550A7ULL, 0x110BD724DADA1E40ULL, 
            0x994FCF0CD3EEC694ULL, 0x64EAA68252A66FACULL, 0x14F4EC4DCD2A906CULL, 0xF4AC88D4CDF9F2A0ULL
        },
        {
            0x25EBFDD1AA826C78ULL, 0x2D612FFAACE605B2ULL, 0x5DC58C2EC11663FFULL, 0x6A7957589DA1A405ULL, 
            0x0CCAC76ACDCE7DC1ULL, 0xE217C179D8F5034FULL, 0xBEC80B2628F9A651ULL, 0x1D1493ACF9E58744ULL, 
            0x5B3916FC0C158CDBULL, 0xCD049888BD20815AULL, 0x3260D8A70D360181ULL, 0xBEBB0F80AA5AAC3EULL, 
            0x38C19C7994B081BFULL, 0x17806C965CBB603AULL, 0x1A03DA774EE8BC45ULL, 0xAE811D0A8EA1AC25ULL, 
            0x256786913A1B7410ULL, 0xDA2CECA99C33E3B8ULL, 0x1C0E0D7E6FE613F1ULL, 0xCB79D4F6BB76B31CULL, 
            0x1584167427C2B125ULL, 0x7A1398C56E00C8D5ULL, 0x4481969DC3557DA4ULL, 0xF33E9C7EB572CB88ULL, 
            0x923603BE11295D97ULL, 0x3B45BB79004C8AC6ULL, 0xC7D43FF6FB829877ULL, 0x80DE5852A143EAE9ULL, 
            0x22B075B2F0535C78ULL, 0x2351233F3D19A5A7ULL, 0x14BC0928A3F82BDFULL, 0x8B390933E7A9EA71ULL
        },
        {
            0xFB2BF09BEBD7FA1EULL, 0x5B97A79D2D5CAC32ULL, 0xBC19A74C0F2E8CDFULL, 0xC00EF6C7591C93CDULL, 
            0x7348926A1830DF95ULL, 0x3A441EFA5A52367AULL, 0xD65E44187BBCBEB0ULL, 0x52FA493C05863CA3ULL, 
            0x51312E45AF76BAFBULL, 0xA03283C6DAE2C8BEULL, 0x5E870D2110781FEEULL, 0x87975AD299BCBC95ULL, 
            0xF1E7BFED4516AD76ULL, 0xE5FE3EA114C9C07AULL, 0x8662AD2D0CFD0945ULL, 0xAA2EAF2BF4A388C7ULL, 
            0x5C72A2B588325465ULL, 0x99D17D34F886B68DULL, 0x2343CF6C648A485CULL, 0x469B6D24D938BD8BULL, 
            0xE126B683310C411CULL, 0xDFF2B2C77ED3EEE9ULL, 0x8F274F8DABF03D93ULL, 0xB379DC649F3FCDE3ULL, 
            0x7B4BC4016D250819ULL, 0x4311AC4E9637207CULL, 0x8F04842CB99DFCA1ULL, 0xCA6A639774A97CE2ULL, 
            0xCAC3EBA4A2687FA4ULL, 0x3ED0B8B704A4AC41ULL, 0x9C5F0AA30D802ECCULL, 0xFD40BACF8FF9E22DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseFConstants = {
    0x6251C6E42246840EULL,
    0x92A2FF782A9E8312ULL,
    0xE9D7AE95179344E9ULL,
    0x6251C6E42246840EULL,
    0x92A2FF782A9E8312ULL,
    0xE9D7AE95179344E9ULL,
    0x05C0D1A2D850225AULL,
    0x1E73C1C27DE98F77ULL,
    0xDC,
    0x0D,
    0xA6,
    0xFE,
    0x4E,
    0xAD,
    0xDB,
    0x19
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseGSalts = {
    {
        {
            0x98B93A143054BD5BULL, 0x451B2D3577716758ULL, 0x487BD56B7D68FBBFULL, 0x8DEB1E26381DE33AULL, 
            0x23C9EFCBE5D5ACD1ULL, 0xB986F46DE0CBE0EAULL, 0xBDF4CB145F4AC43FULL, 0x12AD383CD541A95EULL, 
            0x13174D8AB64442DCULL, 0xA81E214088FDF6DBULL, 0xC6896FDAA748F650ULL, 0x2A83D55A0461EBACULL, 
            0xEC564FEC3385500CULL, 0x8249C2887890199BULL, 0x06DEB6A3F51B5A90ULL, 0x531B4D401D09BDF8ULL, 
            0x8B6DF0DB19C8A3BEULL, 0x6FCC6F4516AD0F1DULL, 0x3A180088814A9FE9ULL, 0x75A3B02C0E1B6F93ULL, 
            0x7A54C8B53AAA1BC4ULL, 0x4186DD1A8C9E4895ULL, 0x77E32F1EDAB7DA60ULL, 0x7CE025296AB09C8DULL, 
            0xD28F7FDAB381FB5EULL, 0x8ACF7F6A1BB82B2BULL, 0x724CE051ED4F6106ULL, 0xC6BAD96775337C6EULL, 
            0x3443B73231C2656FULL, 0x2FE286E3E63318A5ULL, 0x2BA0535BE88BCB3FULL, 0x939CF40C49C632C4ULL
        },
        {
            0x94CD1794027DD94DULL, 0xB5AFBD54780C9DC8ULL, 0xC81E3F7F0D48D1B8ULL, 0x21378E67E0E459DFULL, 
            0x48D74AABA95FF908ULL, 0xB2D984F36294C42CULL, 0x9F96AD7006E0D71CULL, 0x52FA674A81257138ULL, 
            0x2630363D6AC3947BULL, 0x1836CD663670413BULL, 0x0FA445D85C0C92CEULL, 0x8EA23D56AB6378EDULL, 
            0xE3A0B789C822E05BULL, 0x86A6758DD3053322ULL, 0x3CC51FB3599FD40EULL, 0xB3A593F5579D99B2ULL, 
            0xF466541EDFC44BE0ULL, 0xDB91306B59B89071ULL, 0x01988CA714A343A3ULL, 0x686BAAB98B5DC6D4ULL, 
            0x454B2710C5387F0FULL, 0xE845CFA4B2F661D7ULL, 0x61FDE18F4EAC19E2ULL, 0xE7D1BAED6A925C30ULL, 
            0x9F039244A13697E8ULL, 0x5D14BB97CAE47BB9ULL, 0x151EF519945CC92CULL, 0x82642A786ABE5E92ULL, 
            0x2B71C58FEB8A63C7ULL, 0x446D47C12F32F06BULL, 0x8E6388096ACF569AULL, 0x0839E243D056B6ACULL
        },
        {
            0xD11692379BCCF81EULL, 0x96E2ED87F96DD552ULL, 0xFA7C9EAC91477A2EULL, 0xC0AC7C18E6086310ULL, 
            0xF3FE80F48DF6888FULL, 0xB93ED147DB1E2E64ULL, 0x2DE21EE4E21194A4ULL, 0x89CFBE57331FE437ULL, 
            0x44AF5C9D0D3A2BB7ULL, 0xB4C44D46292A64FFULL, 0x4B7E867D0F371128ULL, 0x762C5C209BFC428AULL, 
            0x96663CCFE2D6EB06ULL, 0x454486756EDCB292ULL, 0xC46893985378CC0AULL, 0x3A60247A54B83587ULL, 
            0x1BBB46B8BA75400CULL, 0xEFD124F2DDDBCA0DULL, 0x0A1D0317F583D4EFULL, 0x87E617B51924B273ULL, 
            0x4722015FED1969F7ULL, 0x453AADF99259428AULL, 0x50ACA9684B601BC8ULL, 0xEE490147FC3CF230ULL, 
            0x2ADD8A4DACBBF24BULL, 0xCD656F88D6FFADC9ULL, 0xC718EAA049B6955EULL, 0x9DC86992744D6E28ULL, 
            0xAFF4CE1A9DB490FDULL, 0x5DE16407375DA5A9ULL, 0x2C30B9F9D24E3090ULL, 0xD66D31549DD572B7ULL
        },
        {
            0x3254883ABCF523F1ULL, 0x8DA2E61F6EEED799ULL, 0xE164A11E2677DA66ULL, 0x4B026DCF2C8641C8ULL, 
            0xF59A763A595101FAULL, 0xB9B55B1363602DA0ULL, 0x7AC31596D0F657DAULL, 0x70475C3FFDDD3E61ULL, 
            0xA9931E44C9579DCFULL, 0xC456E0E11BFAD5B0ULL, 0xD486785BA85BADD5ULL, 0x4D8B5271022BD26CULL, 
            0x4EBC3C83B707F5FCULL, 0xDA6E260262C064E0ULL, 0x47D508178AC69C99ULL, 0x54E2B65439B02A2CULL, 
            0x0BF378CEB13EF20DULL, 0x1570D536EDD47D6FULL, 0xC4F288E721E38FFEULL, 0x3091DD172151C33DULL, 
            0x9EC6480025860EBBULL, 0x2CD19D9333699964ULL, 0x2C6B1310BCB69B61ULL, 0x1C9F3D2B59C38CD9ULL, 
            0x89F8BAAB9783F75EULL, 0xABE18E0FFB8966F4ULL, 0xD9A878DF9AEBFB7CULL, 0xDA06BB8F60E6910BULL, 
            0x836509173C042A4BULL, 0x1EE6E8942551DB63ULL, 0xC27DB68B7BACDBB0ULL, 0x1526308F8DCCAC54ULL
        },
        {
            0x25D676CB1478D9AAULL, 0x00E94428980259C9ULL, 0x477F22592BD0D2A4ULL, 0xE585663DD76C3A15ULL, 
            0xF4E6D884A37CB694ULL, 0x126AD5C8511FABD4ULL, 0x8F0B445780A1F3D3ULL, 0x0D5F41C2DB75DB54ULL, 
            0xE6DDB064ECEBF56AULL, 0x424AB9ADE5356D8FULL, 0x33DCCC2A3CB93B65ULL, 0xDA6AC9AAD61924ACULL, 
            0x719A81F5137E7C37ULL, 0x655D03F7477705C8ULL, 0x8161AC6E344C31C2ULL, 0x85C03A02967EB551ULL, 
            0x8058BFEDCAEC59ADULL, 0x8E1E88DB46A844B0ULL, 0x50FA18AFA228C8EBULL, 0xB39456B883B487D4ULL, 
            0x2D6E5B8F4E456DB0ULL, 0xB1751625B3CA521BULL, 0x970E85F2902C6738ULL, 0xF1A6904498F8779FULL, 
            0xBA37A72403AAC290ULL, 0xEEE1FFFA8C27364FULL, 0x1F2CFE41CF911574ULL, 0x3D1C39D07422D933ULL, 
            0x580A78878E4432D5ULL, 0xFAE02757F3A7A8D6ULL, 0xC953BA3AD647C08BULL, 0xA492E5B377BC733FULL
        },
        {
            0x0582D34C7A49F5BBULL, 0x24494B14B11C7FBAULL, 0x3045CD429EA0ED6BULL, 0xA37E6265A06E34DAULL, 
            0x52374289C3BBE97CULL, 0x96018A7E189ED671ULL, 0xB5C3B5ADB34AD814ULL, 0xAC4C1A996C8A8C89ULL, 
            0x8B6CE8FB4D6B45D5ULL, 0x2F0499D3E7185258ULL, 0x24989B3AD348241DULL, 0x9DD83F71B062C548ULL, 
            0x07E8C5FD1FFDCBAAULL, 0x3E8599553E765190ULL, 0x300DB09DFFA72B29ULL, 0xE8682DAF63ACFC59ULL, 
            0x84E123AA407EDED9ULL, 0x46AFFD10726C5B2AULL, 0x03CBAD9C42DA3558ULL, 0x072E306D9E48C193ULL, 
            0x57129A07184F092AULL, 0x4941DB9DF5FFF10BULL, 0xE3E28CD0D47DBE2BULL, 0x93FBCB5E575DD4F1ULL, 
            0xFE2E4D8A3032B388ULL, 0x7962E2B912407B23ULL, 0xD4FB66E333857CB5ULL, 0xD7ED3DD04CC46DFDULL, 
            0x7E6C1E1347A42B39ULL, 0x55E6FD3B7703F6E1ULL, 0x5F33AB8C81E6A033ULL, 0x6301A910865C5318ULL
        }
    },
    {
        {
            0x596105C7BA13542CULL, 0xF637E1E1628432FEULL, 0xE93EB3BC26931642ULL, 0x6170AC7E5D591E1EULL, 
            0x07CD50162693B298ULL, 0x48E77BA70F21CC26ULL, 0x56A805F64C303828ULL, 0xFAEC9D198BE7C9CDULL, 
            0x8E45CFD256ACAE46ULL, 0xD708D90E5EA47232ULL, 0x8711178A74F4EEA9ULL, 0x6F5F86B51993400DULL, 
            0x8C9458203260DDC6ULL, 0xBC99F69B9DDD184EULL, 0x78D4F68C65706D59ULL, 0xFF6D660B42D6FF26ULL, 
            0xF35CA1164A3408F0ULL, 0x4AC3BF2EB3096FBAULL, 0xA63B7AB964549275ULL, 0xCDDA3818CDA64AE8ULL, 
            0x625F165A3BD142C4ULL, 0x9A23D6F88EC1C3C5ULL, 0x43CA7167F9A73F8DULL, 0x2E7D4783C564F37AULL, 
            0x312F4991C74E5382ULL, 0xE88679352096C31EULL, 0xA61C8F606B5ADCAFULL, 0x0899DBFBFF4FC41DULL, 
            0x951F82CA6352CA98ULL, 0xAB262C90E161689DULL, 0xDA32A22A0C18B83FULL, 0x758E9432D94FBEB3ULL
        },
        {
            0x2B491E5B47FE1AF1ULL, 0x1AFEC4EF0B35C234ULL, 0xF3733998CA2F4B4FULL, 0x65715AF31A286C30ULL, 
            0x3E4EBFB428202FC1ULL, 0x10A894F691389FD7ULL, 0x6DF2CA64E0A336D6ULL, 0x0BCC103138FC9457ULL, 
            0x9A0080B47CCD28C2ULL, 0x73158462AFC8291EULL, 0xC9B4B6F60DEFC44CULL, 0xFD5FF23E5393F794ULL, 
            0xBE4524708C3E2E55ULL, 0xFFAC9C1942460625ULL, 0x4555478B65EF274BULL, 0xFE8519582BB8DD5DULL, 
            0x22D4D9540A94E260ULL, 0x8606EA0B6BC94F9AULL, 0x5DE09887CA6B9E88ULL, 0x2AF2976301DC7A68ULL, 
            0x3FF13EE8596AF529ULL, 0x4F420B67E8DCD4BAULL, 0xD524AFF983DBF1AFULL, 0x43597693E2C650C1ULL, 
            0xCB954928E7C79B9BULL, 0xC1BA122E33DE42EFULL, 0x3D19A9CAC07D9C60ULL, 0x9F073C3E11A32860ULL, 
            0x26B7F2B5C212C110ULL, 0x43392BBB903F0D4CULL, 0x5C25369E01531FAAULL, 0xE62ABEB1F4E80654ULL
        },
        {
            0xE575B196F57FFEC4ULL, 0x4F840B98F98F44CFULL, 0x8692054FA9731F01ULL, 0xE258B705DBF02027ULL, 
            0x93991CF4C1CDE9FEULL, 0x39E1CE6981C98AC5ULL, 0x99429A0977FABABEULL, 0x2A567B8FBCEB1E22ULL, 
            0x3A3013183BA6FF6AULL, 0xD62B5FAECA3B8FDFULL, 0x4DBDF08396451138ULL, 0xC5079ADD2BED9623ULL, 
            0x9EDA41C3D1441A03ULL, 0x2DD2F039BFF62FD1ULL, 0xF18F47D9DEECB222ULL, 0x03748069AD204879ULL, 
            0x6A519A7517D2D505ULL, 0x42DA79D45192F676ULL, 0xD984059E8F7B89ABULL, 0xC0E0B0301E6629F1ULL, 
            0xCC070A46FDEF1526ULL, 0x4E0231B42E49A2A1ULL, 0x4E2AB94EA984A40FULL, 0x874C511CCA334E1EULL, 
            0xF3C897A693B24B81ULL, 0x01528F6A118CA2E5ULL, 0x0D983B3738BC2C64ULL, 0x52199EDFDA2F978EULL, 
            0x519C456622DEB056ULL, 0xA7FBCDF3889C0940ULL, 0x5E0980ECADA5A940ULL, 0x61AB02EB81461C70ULL
        },
        {
            0xA4AB84641E66717AULL, 0xEF07E16DD2AF9CBDULL, 0x86FFAE83662D7603ULL, 0xF32F06C33C4A75FEULL, 
            0x524E6383084ACD32ULL, 0xC7F8341608D444C0ULL, 0x38ADB5249CAE5825ULL, 0x38DF2B6C9A263B7BULL, 
            0x38640B5D16B63D07ULL, 0x0C3709AC34DC8FD8ULL, 0x1934C775AB8B6759ULL, 0xE620873AB39A8B0BULL, 
            0x07DC49BEB0261867ULL, 0x2F3CC2DAA57E7925ULL, 0xF2EDEFBF14E18DD7ULL, 0x5813A5594BC194D8ULL, 
            0x48D3F76D9BD358C0ULL, 0x7117010568360939ULL, 0x565F13135A755CD4ULL, 0x452D4C381B57BBF9ULL, 
            0xB8C452CCA81D6C9FULL, 0x3817155D02A94BF8ULL, 0x015C27FE4F6CFCFAULL, 0x6EEDA41C4E578763ULL, 
            0xFE2FC964937FF052ULL, 0xF11CE26AE43A68DCULL, 0xB065020BA5CCD452ULL, 0x5F498854E5623553ULL, 
            0xE41AA3DB7A7738D1ULL, 0x67BB88741696E042ULL, 0xEE56A4B1B9BD351DULL, 0x608A98C371667749ULL
        },
        {
            0x62C8E5EFA4119B22ULL, 0xE62B94B304261EA8ULL, 0x7ED92EFC15011942ULL, 0xABB140970F7E7B8EULL, 
            0x7F2E1BD391E9EC52ULL, 0xF07BBC4443BB7F65ULL, 0x094240242F8E9A9FULL, 0x192CE03B798155BCULL, 
            0x49AC0B55952FD840ULL, 0x4045A43C700B1908ULL, 0x2B7599E842E0C54CULL, 0x39D637CCC560736FULL, 
            0x12585F6EB17228A4ULL, 0xB299527234DC0DAEULL, 0xBF425A8567CFFED7ULL, 0x66860A38FB7898C2ULL, 
            0x1E19D359545EF216ULL, 0x2B6BB8A690DE01E8ULL, 0x3A8360DA30983E78ULL, 0xFB61CE37809A151EULL, 
            0x00BD8140DBB06677ULL, 0x0AE328A8265F2754ULL, 0xDD822B35AB817229ULL, 0x1AD5E6B731C97D76ULL, 
            0x2C956B4CB8978579ULL, 0x0054B97F51E1AEC2ULL, 0x0BB2DD0454E5A7C9ULL, 0x70A4BF7681DB651DULL, 
            0x1A1A72594FC76DCBULL, 0xF56FA3CD661FA01BULL, 0xAE6CE9D7158A1B61ULL, 0x7ECFD2B2D5B7F562ULL
        },
        {
            0xF33827C6D6E9697FULL, 0x829CE4925366EB4BULL, 0xE84B35BE37D5F53EULL, 0xF023351A2062AE83ULL, 
            0x3A8F5061B2E9581AULL, 0xAE63DA8018E1AE22ULL, 0xFAF07798AD658EB3ULL, 0x8695396A0D2F62B5ULL, 
            0xEE5AAADC67F6BB22ULL, 0x17A22BE4EFEC4A81ULL, 0xD1144414F4A86A60ULL, 0xFB2F02311A3F536AULL, 
            0x276C7EF7A908A521ULL, 0x037AE933B569B268ULL, 0x1898914F0618BAC8ULL, 0x4F79AFA1E3655479ULL, 
            0xF712DB332BAE9072ULL, 0xCD1445D5EBA7BE6FULL, 0x8674609302E091E9ULL, 0x1515494E4821F4EEULL, 
            0xCAFEF729462FCD29ULL, 0x64AA838117E18FA9ULL, 0xE099C8C26B4FD0E2ULL, 0x23C6F573F656CC85ULL, 
            0x03B58765BEC7185BULL, 0x146D4EB5864E0BE0ULL, 0x01656713761824C4ULL, 0x4E69E74B6B00C0FCULL, 
            0xE6ED2770F68334AAULL, 0x3F527369B64C04B7ULL, 0x1FC4B8284B1526BDULL, 0x15575CA4473F9453ULL
        }
    },
    {
        {
            0x8D1636FB12C872D9ULL, 0x0CE97792E14E7A20ULL, 0x3F2BEBE33F5CC9EEULL, 0xD3D5026FB0114A0AULL, 
            0xCA35418FFF6202CBULL, 0x26BA573499C0A57EULL, 0xAE09F66862E27C6FULL, 0xB992DCE7154E4C08ULL, 
            0xEB40CAF5096725A8ULL, 0x217822DACF172FB2ULL, 0xFC0C31F49B030270ULL, 0x7FBF2E6505394B9CULL, 
            0x47CC1679616BD127ULL, 0x47A84E659376AE27ULL, 0x048DE1E98DACAD12ULL, 0xBD7227FAFFC78694ULL, 
            0x3581064FB95E4EBFULL, 0x02CDF6019F16930EULL, 0xDAC030DDB983CADAULL, 0x12B6931FC31D272AULL, 
            0xFB08FF3DD0870373ULL, 0x1D9FD5367764DDEBULL, 0x25A9E9D9242725D6ULL, 0x89AC7FC428A2F884ULL, 
            0x375DF61D3F8E885AULL, 0x31105D40F495ECCBULL, 0x964829117DD1F79EULL, 0x1966C98E63EC1CF9ULL, 
            0x572A1B0FD191DF8AULL, 0x2B3025484F988D0EULL, 0x763D6F7E99C10FC7ULL, 0xD7ECDDF933C6881FULL
        },
        {
            0x99E200F7CA8A4614ULL, 0x2E1356BF205AF949ULL, 0x9EA9CD197465BBF3ULL, 0x7C8BB11DB93F3E5FULL, 
            0x2B0CFBC732A727E3ULL, 0x32969EB5F280A045ULL, 0x42A83F6BA90A2BD0ULL, 0x47BB88AC169B578BULL, 
            0x144E407CB5277652ULL, 0xA27C42F9C8E4D46FULL, 0xCD286E92412BCC89ULL, 0x48FAA0546BB988FEULL, 
            0xEE649878EAD9274AULL, 0x91FD407D445D09E0ULL, 0xB959D86F799AEFA9ULL, 0x64D8C0A3FC08FB56ULL, 
            0x3488D32FF5DE26A9ULL, 0xB06F895862A153CBULL, 0xFD83C1604387B339ULL, 0x9DF5B93269D35424ULL, 
            0x09E93C4FE992B6A4ULL, 0xF88BCCED351110CBULL, 0x2659D29DEA0E9143ULL, 0x438ADFC5E55083EEULL, 
            0x5DCC779212A8D796ULL, 0xF09C53E73A980933ULL, 0x4CDE1A34E2A31850ULL, 0x977285E01F349D40ULL, 
            0xE960B08BABAD512CULL, 0x984D328063AF5590ULL, 0x4663F25D576EC3B2ULL, 0x9289BB22C3853F67ULL
        },
        {
            0xA0B93DB08FA19034ULL, 0x5747C800FB3EA6D9ULL, 0xBE7B16B90550DA97ULL, 0xD24195DBA069C9D2ULL, 
            0xA6D40686F61D8A1CULL, 0xFC2FAE8EEAA50052ULL, 0x0A248013D422EE10ULL, 0x08457F4980CBD6A8ULL, 
            0x41659AF1199F71A8ULL, 0xAC6687E42BD1A1AFULL, 0x9A97C94E3E28371AULL, 0xAA0460A49958F55CULL, 
            0x1590ED3887680E73ULL, 0x8C90AC1151CD6E73ULL, 0xE58B950DD54A6FCEULL, 0xFB12A2F9E5D1C3AEULL, 
            0x6F462E7A7016A452ULL, 0xCC26A2CA9346A70DULL, 0xCC0B44BF05DF887CULL, 0x73F34A1471741BD0ULL, 
            0xC98555750D5E9316ULL, 0xCACCC94589FBCE9AULL, 0x916FD7CD553A89A8ULL, 0x9650D912252D7AF3ULL, 
            0x8169D43390DA8765ULL, 0xC11C5BEC4761EEF0ULL, 0x0154AE8276F89720ULL, 0xDAC6A6994DE7DC58ULL, 
            0xFE0202A833307B8BULL, 0xDDF2F05033BF6EA8ULL, 0xF38B949726F081D7ULL, 0xDE2379DA5CE30EA3ULL
        },
        {
            0xB5C3B2BF248B87F8ULL, 0x43876B026E81AB79ULL, 0xDCE268CFC1EEADC3ULL, 0xFDCBAA57BB7D3D87ULL, 
            0x63EECEE70CC36360ULL, 0x2002A22672EB95E0ULL, 0x61B27BA165EC229CULL, 0x547C18986A7CE651ULL, 
            0x8B1BFEABBC59CA09ULL, 0xCD577DE59A3CA078ULL, 0x7DEF9AFC3B80C376ULL, 0x916B98161F6B979BULL, 
            0x362F372376CCA7D8ULL, 0x7EF1B03DF06B7213ULL, 0xC9E32381470290D5ULL, 0x036CD0E0CCD5D1C3ULL, 
            0x8DA9D3D33BD04ABBULL, 0x5343EC11701EFEA6ULL, 0x8A3E4B23FAFD806BULL, 0x15AD7C360BDE824DULL, 
            0x955E502551FB3497ULL, 0xE6F686361FDBE9A1ULL, 0xA803387D5ECFBA14ULL, 0x67B872F0059DA348ULL, 
            0xBD268680011EC712ULL, 0x391E35F2DA51281CULL, 0x99B8B1AD0547D7F1ULL, 0xC95808BA95B1B454ULL, 
            0x7672F5206DF2059AULL, 0x4C6F695F5B22CA5CULL, 0x4460633329FF97C6ULL, 0xD370E35A9395199AULL
        },
        {
            0xA136C8570D97C075ULL, 0x0C73F264FDE5C348ULL, 0xE25C9E80D95766A8ULL, 0x64EF879326C9DEF1ULL, 
            0x3E4077A47F3E0D39ULL, 0x1BE8678301D9318BULL, 0xDA1BEB4BA2DE5E18ULL, 0x4B7594D0F5F3E6A1ULL, 
            0x0030B1B388CF134AULL, 0x1950F8854CD134CFULL, 0xEC1937BD3B06A69DULL, 0x52CD5D76B484A06EULL, 
            0x4F73C7155C3C2319ULL, 0x9D2CD8874D96115DULL, 0xF283775978E20917ULL, 0xCC0084C4B9554790ULL, 
            0x1332E6213D1C9960ULL, 0x219A800D33A80E42ULL, 0x6FA4D8444E08BFF7ULL, 0xA57C693E1877B7F7ULL, 
            0xAAE735BD2FA2FD8DULL, 0xF6759D59139772E2ULL, 0x0730D3BDCBB8919DULL, 0x6EE9526A15B76A63ULL, 
            0x51FBDA06269B48DBULL, 0x5B753F2285F0EAB4ULL, 0x1D5C21AE68AE4090ULL, 0x70CA06615F7D75D2ULL, 
            0x03832BEFE51AF763ULL, 0xDE6F03C194E8B90DULL, 0x836C97E9EDEA3B30ULL, 0x5F69D126710B87CEULL
        },
        {
            0x5A6E5691DB4EF0EFULL, 0x55CFD29F55D578C4ULL, 0xA3052F0DD44C2316ULL, 0x7994731838F41192ULL, 
            0xDA65DA6849BBE82DULL, 0xAA02183A090714BEULL, 0x83EA9BCFF8E34B67ULL, 0x041AE0D4A5B4A800ULL, 
            0xF855A30A3A45D4E3ULL, 0x53136C3BEB1BE2C0ULL, 0xB27EA2E45A784B70ULL, 0xF20FAE7C29CDE4ABULL, 
            0x8BF5B5DC92CD6CABULL, 0x4845EDA34AB49917ULL, 0x6685898A6310C8FDULL, 0x9D34B661E5C9DB0AULL, 
            0xE1101972BE1B3E80ULL, 0xCFE0E8C1F7261B26ULL, 0xCD4A60FE3C481639ULL, 0xC1A1B09037D17212ULL, 
            0x60B9A125C05ADCDFULL, 0x9ADD4FBDE1B3BC38ULL, 0xEC77D72656EA41D7ULL, 0x46157E2F108844ABULL, 
            0x62E9ACBA7607899AULL, 0x193B758C2237A33CULL, 0x0397197AFEB3C946ULL, 0x163E50E014B6FF79ULL, 
            0xF003DEAC251C2906ULL, 0xE3C8E74CF93E5A6AULL, 0x77AD2526BDE17712ULL, 0xEF1CB1BE3E27AF0BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseGConstants = {
    0x956E03F841EA4019ULL,
    0xFE6C27BB9E397949ULL,
    0xF4B41A324B905184ULL,
    0x956E03F841EA4019ULL,
    0xFE6C27BB9E397949ULL,
    0xF4B41A324B905184ULL,
    0x5B6755CE6D47D8E1ULL,
    0xC48AC6448A12A72EULL,
    0xBC,
    0xB1,
    0x6A,
    0xA2,
    0x6C,
    0xFA,
    0x5A,
    0x6A
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseHSalts = {
    {
        {
            0x7E0EA2B7F7E05E7AULL, 0xB539E17327499DDDULL, 0x1D277D45452850A7ULL, 0x11946B816F23D13AULL, 
            0x922C3247AACEAEEBULL, 0xB5CA0DCDEEB582D6ULL, 0x9EAE928BE2D48F53ULL, 0xF3022833C4A445D5ULL, 
            0xC7881990461EA7D1ULL, 0x09EB4BCDCCA0A70BULL, 0xC1C5E943050CF7CEULL, 0x9E6E86D47A2A871BULL, 
            0xE636325A5A1C152DULL, 0x3F1859EAA1680ECAULL, 0x5E1D2CA689E68B7DULL, 0x3F0E6D7B1CAB71B5ULL, 
            0xBF82E183C8889009ULL, 0x5FE6A85C1C85F33CULL, 0xC462901E898F5DD2ULL, 0x23A1CD84792A882FULL, 
            0x887129992F63FAE8ULL, 0xDC409D0E8F4A38CDULL, 0xB9031E3C9F4D51BFULL, 0xBD5CC198E88057F5ULL, 
            0x0D4FD3E29354641DULL, 0xAB3412A7E8FDC084ULL, 0x5EE1080ED2620B88ULL, 0x2E7561E3373D8C48ULL, 
            0xEEC8FC1C3A16B069ULL, 0x84463A466FD84A0EULL, 0x7FBFCFC8E4F5B446ULL, 0x8B0A7F99DFC634F5ULL
        },
        {
            0x530EBDBD339C2ECCULL, 0x84CD928B9361EB4FULL, 0xF65DE492E5AC6893ULL, 0x93AB6AE4C294D7DCULL, 
            0x6DE8DDE79947B627ULL, 0xED95BB62776579E1ULL, 0x0320BF39C5ED342CULL, 0x1511B0F9FB71C6FDULL, 
            0xEC2A57BBB52E433AULL, 0x76F199D536264835ULL, 0xB445FA26C39F2F3CULL, 0x9BCA6E9A7B486504ULL, 
            0x66DCF3C6BAC06D69ULL, 0xC0A88F00129395AAULL, 0x17F2437EEDBF892AULL, 0x8805F343BC53491FULL, 
            0xF203C8E2D083E4D1ULL, 0xDDF2EBEAACB2FF9CULL, 0x7F49454953FFA4D5ULL, 0xEF957D102CBEA414ULL, 
            0x5B426A91EF89236BULL, 0xA7FD716E05BAEF36ULL, 0x13A43A80EDECAFFEULL, 0xDB2BC793DCABA68CULL, 
            0x84945009E8799625ULL, 0xC749BB27BA1E0E8CULL, 0x164AAE6417795685ULL, 0xACEA02BCB7EF8F86ULL, 
            0x2EA662068985E299ULL, 0xFFCE30ED55BF2C90ULL, 0xE047C22A308C953CULL, 0xF077B8644F9585D4ULL
        },
        {
            0x9DD39196237CC0E6ULL, 0xD227F6B17F8B98D2ULL, 0xD06B3AFFD3322169ULL, 0x0AA45CC004D926E6ULL, 
            0xA1684CF0C5B8B488ULL, 0x4AC76C10C7DBCB55ULL, 0xBEDC496A25D79576ULL, 0xCE3A9A966DC8A8C1ULL, 
            0xB0043E1FAC4BFDB7ULL, 0x187DEDD7ABFCD7BBULL, 0x37CFA28022654431ULL, 0x3DF52465C87D0645ULL, 
            0xA6E5EEFCE2801318ULL, 0xA27DC8E2C1F74B2EULL, 0xE72E91D496C99549ULL, 0x5D68FE1896DA3276ULL, 
            0xAC178B9F87F3BD5FULL, 0xF5F1BD8300F80E42ULL, 0x20082A94B813ED09ULL, 0x7FBD5B8388C9A07BULL, 
            0xE0457A7E514E82B6ULL, 0x777C419C7489C725ULL, 0x6C3C0DC1AACD05F7ULL, 0xA27A4C86608A728BULL, 
            0x1BEDD7E1A370EFB6ULL, 0xF29189E28BF4953AULL, 0x7B0BF1B0515521DDULL, 0xA36A0594C131E6F0ULL, 
            0xD22B188B1F259E05ULL, 0xBE50C3C49EBBA34AULL, 0x2D8769CD8F1ADC22ULL, 0x9C2137FC45E4E3C1ULL
        },
        {
            0x06EB5C3F3680770CULL, 0xA829851C3BAEF78BULL, 0xD7D9C99557CD7914ULL, 0x6B0A4757161C9DEEULL, 
            0x2172FC8179E4A42DULL, 0x3FA3B3E9CBA6EE29ULL, 0x6C2048FD65CD8223ULL, 0x45ADA85E81626CD6ULL, 
            0x1F5715CB6FE095AFULL, 0xD55340A87C42DB50ULL, 0x6A4F4153D39F40A1ULL, 0x4385BC7BE966AE2AULL, 
            0x2B12EC61CB9CDBF7ULL, 0x5E9CB96485C1EC72ULL, 0x6DBE5F1A2FBD3311ULL, 0x040A39E192662F90ULL, 
            0x420129B1F1331704ULL, 0xE3FFA0D0AAF2C928ULL, 0x0CECF4FC39490D0EULL, 0x6D14DC26F84D0A96ULL, 
            0x0381DF2447042246ULL, 0x3041475C67ACFD9DULL, 0x2D271C9B0FD21675ULL, 0xBB64679DE083B47FULL, 
            0x7FBAF00E32DC4529ULL, 0x498FA56FF9FF572AULL, 0x68226C5C476D40B8ULL, 0x850C03AA8798CEB1ULL, 
            0x4177EBD40A8AFBDEULL, 0xD9BFC873D355B442ULL, 0xCFDCE958FDDAA094ULL, 0xB8496BF80904DA5BULL
        },
        {
            0x79B23DDA1510BDB6ULL, 0x122513D5B91050FBULL, 0x79B9A517801E6FE1ULL, 0x44B93024C81AB5C4ULL, 
            0xEEA36C3D98358EA7ULL, 0x29298EC2411B706CULL, 0x12717B5D2D00E9CCULL, 0xFFDB336A7FAF4A1CULL, 
            0x255B9C4AB085B8BDULL, 0x27D52C338963FC05ULL, 0xAF85E40127C8732BULL, 0xE705967259186A9AULL, 
            0xE4173854D622626CULL, 0x9A23999AAFDE606DULL, 0x7145471146527E5AULL, 0x1AC2748CEBD45AF0ULL, 
            0xD53893B8F10F233DULL, 0x287F2991BA431E97ULL, 0x172C9A1465E78ACBULL, 0xEE5B23B062A2C358ULL, 
            0x676C9F467C14761DULL, 0x3C68747E808C376CULL, 0x5DED7AEDCD822665ULL, 0xCAC1014E1E432A1BULL, 
            0x8B59B4C16F1575FBULL, 0xF3383279C13A43DCULL, 0xA17ACB7FE5FEDB04ULL, 0x51301802697FBC59ULL, 
            0x0B0121C73689CD67ULL, 0x45008FC5B1F7B459ULL, 0xE77C27DCBD5C47A5ULL, 0xF037BADF47C8BB93ULL
        },
        {
            0xDD027E49C3A3256AULL, 0x21C186D8827EFC47ULL, 0xEE86CDE311E6E890ULL, 0x9B7CDC616EECF57DULL, 
            0x8A5A4E512645B0B4ULL, 0xD6A74909F95C6A62ULL, 0x7E4F307C6D11FB65ULL, 0x21274B93DF70C0FBULL, 
            0xC9EE39D8E325AE7FULL, 0x672C6052E6A6D525ULL, 0x9E2EE026D008E3BBULL, 0x44707A3600651C84ULL, 
            0xD59A0C5805E177AEULL, 0x78C97D97ED4E6B8CULL, 0x95A4B12DA69E64B7ULL, 0x988E2F3BA14223F3ULL, 
            0x8BD666F8788448CAULL, 0x1475879326F115A4ULL, 0xC8E3CF76CFC019D9ULL, 0xFB152C5D4A29D92CULL, 
            0x2E13F5BA14786668ULL, 0x5DBA7EFD17F19D7DULL, 0xEA4E7F69792988D0ULL, 0xA8A2BCD3B9D906C5ULL, 
            0x87628A37E06BA96CULL, 0x3C8DF5678317F10EULL, 0xEB53CB3C8B3DA3DCULL, 0x304208F982F5F7F2ULL, 
            0x6FEBDD175A551AB1ULL, 0x21BA75CC43CB4B4EULL, 0x82F6BB8B8184E79CULL, 0x47123E1DEAA350D2ULL
        }
    },
    {
        {
            0x0512B55AEF1D7AEFULL, 0xD8F4E7BE9B2AFC0DULL, 0x40F878F238D936CBULL, 0x29E8FE435D4D52E4ULL, 
            0xC1DB4A0A54ED3B64ULL, 0x6116A4273B224A06ULL, 0x83B199D3E52542BDULL, 0x84AF9198F186D048ULL, 
            0x665CCFF2D7E57AB5ULL, 0xEF2DD2213475CDFCULL, 0xE6C778A2321BACF4ULL, 0x93699BE0D8C7255DULL, 
            0xF94D6A326AC193C4ULL, 0x5B2A8F0D7D062C7EULL, 0x8F646A30D537AA45ULL, 0x78065C4DD97D2D98ULL, 
            0xC9D68860D1CB6ADFULL, 0x66A2019EE25E222FULL, 0x3CBA9E3403D671D9ULL, 0x721C0053B5585971ULL, 
            0x2383F1862C225E44ULL, 0x6B78DEBF46A6C08BULL, 0x01D013B9E5551BAEULL, 0x62C53C6239C638FDULL, 
            0xBDE7628E22A06A90ULL, 0x3D67BE4C657CC300ULL, 0xCFEB77D98897CC62ULL, 0xBDE8A7218FFF634AULL, 
            0x73DC663CA60E4246ULL, 0x0F83B0BDA544AEB2ULL, 0xE805B5B0F6C04274ULL, 0x5DE1880FD724A4F5ULL
        },
        {
            0x5B9148B4D5B9910CULL, 0x9A3E6653D3137DE3ULL, 0xE0B418183660B4A6ULL, 0x7CA4336081ADEE00ULL, 
            0x2EA7E0D93D754AD2ULL, 0x7BCC4CA27E2E74B4ULL, 0x4E8160BEEC1615D8ULL, 0xAFDD09624990FE96ULL, 
            0xC3D27DC25312936DULL, 0xBE53367888B222F8ULL, 0x794716EAC6956FEFULL, 0x58576B45F7A070C4ULL, 
            0x7A5CF0156C10C44BULL, 0xCB64C9BDFC0CB5B2ULL, 0x02A7D65747085D6CULL, 0x5E2FDF31C7122E3CULL, 
            0x010443229AECAB92ULL, 0x0DABF1E81FA42E69ULL, 0xDCD85CD1A8F04394ULL, 0x1DC180E595282B98ULL, 
            0xD6FBA9CB7A67800BULL, 0xCD7A5B35B1E60C13ULL, 0x380C33C36A2662E7ULL, 0xD4925638CE52AF2BULL, 
            0xAAB62F17C6FF903AULL, 0x48DDD34EB1DFCA2DULL, 0x26B9C4BC01286BDBULL, 0xB0E89E1954E10B4CULL, 
            0x4570DAEA1D3D6F77ULL, 0x7CF622E66E32FF4CULL, 0x0814EBD8F446BE57ULL, 0x877C84DC9FA3AF4FULL
        },
        {
            0x0BA5C5E87C68AEB9ULL, 0xD6D9A20D102207D0ULL, 0x011CA14A6DD99117ULL, 0x7221855AF1D29027ULL, 
            0x3B2277914785B817ULL, 0x5C9ABA545BE64B75ULL, 0x3B3F49907BA5A080ULL, 0xF11DBC7978FD4CD7ULL, 
            0x081834D754F98A9CULL, 0xBC3CA76425E4BC1CULL, 0xC9CA1EF8A2502816ULL, 0xA63696C1941CEC10ULL, 
            0x5824A746108EF586ULL, 0x081CEB1BBFFFF6FEULL, 0x13C86B25025158B8ULL, 0x6BEF558D0ABE6FC1ULL, 
            0xE6A761516A060C81ULL, 0x1BD525304C4C7048ULL, 0x9F56E5944E0AC7BDULL, 0xEBAE1A2C9E05E7F5ULL, 
            0x1E4C5B1C189A42B6ULL, 0x32FB46DF2B8A22C5ULL, 0x41D33F5FEF64AC24ULL, 0xF19CD158B53FADE8ULL, 
            0xB59BE4949D2FF47CULL, 0x54742F7FEA2CFE43ULL, 0x5A24B4CCC059C860ULL, 0x33EB4EA20C2BB705ULL, 
            0xD8408E592674B688ULL, 0x8CE9964DAE771B45ULL, 0x2E90A4700F990849ULL, 0x31BCC1EF41E103AAULL
        },
        {
            0x7F5439C64B4089A9ULL, 0xC464C000CFEC9A41ULL, 0xB7C5E326B83898F1ULL, 0xBE122AB89E78A932ULL, 
            0x2DE07674A955A4A6ULL, 0x85B2BA92D908E927ULL, 0xDDF72E1E1DABB08BULL, 0xBC8370DB27A01298ULL, 
            0xE0DD7A946CDF36D8ULL, 0x75028D20143A76B1ULL, 0x56EF8E17FF7D1FEBULL, 0x175FEACAD477FF53ULL, 
            0xAEEB5AD58AAF770CULL, 0x48CF3AB9F635E84DULL, 0xDDF85679A5ABF8A4ULL, 0xCBEEF9F0DB70CB09ULL, 
            0x264D995CD7D5A1A0ULL, 0xBA6D9F855493E590ULL, 0x5D3831F8F3915F7FULL, 0x84C9B67C0BFB2297ULL, 
            0xD858FFB4CE6CB554ULL, 0x19C1689599015241ULL, 0xD0885C3CD5263896ULL, 0x3E28ED874E805FF9ULL, 
            0x38F52CBF5676D9E4ULL, 0x49D484C1E176DB5EULL, 0x15353E1D38EA7C89ULL, 0xF421EB66F14CB27AULL, 
            0xC1EA4332E0633C63ULL, 0x54AE75E40FA2A1F7ULL, 0x1710F06567971EB9ULL, 0x8871724C3FE02A50ULL
        },
        {
            0x720A2893759FC133ULL, 0x3CB9B945A78800C6ULL, 0x3D89243832EAF8C9ULL, 0x5F20D66E148B2665ULL, 
            0x5E3B4C8B3E739F33ULL, 0x91464CA7D34B7CD1ULL, 0x68CEF558913C55A0ULL, 0x7EC8D43C7920E80DULL, 
            0xF51E543C90305BC9ULL, 0x183897D060E4C87AULL, 0x879DF8748ED534D8ULL, 0x27369063D5B54125ULL, 
            0xE982CBB43A5D9C7FULL, 0x684065162196AFC1ULL, 0x072ABE455FFE0C14ULL, 0xF5C65749F42FAB41ULL, 
            0x964A2C83B7F76B9FULL, 0x9657FFC69E29F467ULL, 0x5CBECB913F08EF05ULL, 0xC75F424E25274A98ULL, 
            0x1122EFEB8B3C8DCDULL, 0xB91953983F3F264BULL, 0xE6A0D4E102B38CA9ULL, 0x5E0F72D5B5DEF65AULL, 
            0x2F5EB35504ABF17BULL, 0x81916012F8888D08ULL, 0x313D879E71F39797ULL, 0x91FBCCC434B51947ULL, 
            0x25BB9D1550F5DF73ULL, 0xCFC4072BC8138EBDULL, 0xFD75082304AED3BBULL, 0x8C174F576DCAD85DULL
        },
        {
            0x83170764AD4E54EEULL, 0xA54C434263941C2EULL, 0x7F2606E7970A3969ULL, 0xAE818DB95C6BC1B3ULL, 
            0xB0DA1A91C71B735FULL, 0x7EB3AC67A587C24EULL, 0x8BB82ADC85745348ULL, 0xE17D259B4740AF88ULL, 
            0xD1A540C3242988AAULL, 0xF6CC43D9372358F9ULL, 0x1F8CB302A3027F15ULL, 0xBDEF431FDDA51A35ULL, 
            0x8042D18B24D8E7B8ULL, 0x8D710F955CDE81D5ULL, 0x974116A37A2C1A75ULL, 0x74A74C1AB3D781ABULL, 
            0xC971382891F8A21AULL, 0x0E8DB1BA4EB43A64ULL, 0xD63E7371CA655477ULL, 0x4735F9CCE00CD10DULL, 
            0x9CFB63A509CDE7A2ULL, 0x3239390DCBD0372BULL, 0x8175C5A706BF52DFULL, 0xBEBC78B6B8AD4524ULL, 
            0x859B53F694DFD452ULL, 0x05F9E6F29413C2D6ULL, 0x1467909390E44657ULL, 0x98AD386DDD83E535ULL, 
            0xF04368A23428735CULL, 0xD5414B1785139C5AULL, 0xFF87EA7166638E5AULL, 0xD6141FD4E5968813ULL
        }
    },
    {
        {
            0x1214E031775F2209ULL, 0x59D1C2224705589EULL, 0xD348B6959834F890ULL, 0xE64C9E0E5DE85AF8ULL, 
            0x1FBFCC81E39DE022ULL, 0x995470DE34FB31B5ULL, 0x02DEDBD8C10D28D3ULL, 0xDE20F84E46FE4812ULL, 
            0x2011A3809C1126A3ULL, 0xDBDF5F549DB58B54ULL, 0x22AD247EA320DBDCULL, 0x27FBE7F1B39513C1ULL, 
            0x41BEA09721C01A03ULL, 0x33EBE10A48B1A2F7ULL, 0x76C39611B1C1EAAEULL, 0xD5C6BB4F9E6ACC64ULL, 
            0x20E7FD347F29C4B5ULL, 0x18BB62FFB002D2B6ULL, 0x9DA7037CA23D0EF6ULL, 0x8C81618ACE625E99ULL, 
            0x2FD66E8C12B65EC0ULL, 0xAC64B832EDC54402ULL, 0x8A1A0FD86FDDA422ULL, 0x4365AD8C05C5FD73ULL, 
            0x3E460F0B26498A7BULL, 0x9F768929CEE7D1F6ULL, 0xEFFEE42B99AB53CAULL, 0x7D1A56BF7CBC98AFULL, 
            0x118E4BCAB49DB8D1ULL, 0xD2F6A041EBCB116AULL, 0xA8792658B04826ABULL, 0xEEDEED7B6D7E1838ULL
        },
        {
            0x3C2D753B60560FACULL, 0x9B04B13B60BF8455ULL, 0x36509D04C97D3DB6ULL, 0x7EDBF6FCE12FE226ULL, 
            0x3288BF95D48EAC53ULL, 0x0FFCA7E5CDF58928ULL, 0x6DB40CBD3CE263CEULL, 0x7AC073D9A624FF69ULL, 
            0x5016B3584E82CDCDULL, 0x1CA37AA2393616AEULL, 0x3AA1A6E3F598A59FULL, 0xC4FF4815F09B18BCULL, 
            0x0D73CED9CDE44E04ULL, 0xA4CA23FBD3CE7F7BULL, 0x91DD7C80C092A016ULL, 0xF3869DA96F1E85F7ULL, 
            0xDF946C23BB540481ULL, 0xBED265D2E4EC5DAFULL, 0xCE82564ABE5DF7E5ULL, 0x75A668252CBBF30AULL, 
            0xA5E1EE9B69F0F318ULL, 0xA56CF16CD9839969ULL, 0xFBB6810C1D6A27CBULL, 0x4CC8603F50895890ULL, 
            0x06B3B93F905964EDULL, 0xBCF32FD3B9475223ULL, 0x2C08A9E642F47EA2ULL, 0x4195F69FAFB4E278ULL, 
            0x95593DC14A23DADBULL, 0xFED8108A8BA587C2ULL, 0xB6B94F3039957CA3ULL, 0xA3D01717D1F8D3EAULL
        },
        {
            0x789E8D8E7D1569BDULL, 0x008DCB4FC5A67BB7ULL, 0xD442F8C4A3171446ULL, 0x396A0C742A74E993ULL, 
            0x82317B2B1DD2B2C3ULL, 0x0FC82C23A38FB9F4ULL, 0x972E01A1071CB667ULL, 0x793316590C8A65D4ULL, 
            0x85D22C9F2644E9B8ULL, 0x98683770529027D5ULL, 0xFF486A15A1406A1AULL, 0x76E6283B31E5AF82ULL, 
            0x95AE802D65E2A204ULL, 0x6F2448D54689E31BULL, 0x38F57CB892A15327ULL, 0x521D33C8C31E7EF9ULL, 
            0x53A5B420AE75A50AULL, 0x5C49301349A5D653ULL, 0xA3A741CED78B0EFDULL, 0x404DCEE01D2C8B7BULL, 
            0x9485D32C04CA1804ULL, 0xF78B8BCF351234E9ULL, 0x1B98DE25B64D8798ULL, 0x0C194F9BB013FE2EULL, 
            0x69162FFFAF170621ULL, 0x0D3ECC25739FFF8CULL, 0x70BD94318C52DD13ULL, 0xAC51259E0D3E75D1ULL, 
            0xB1F58DD98F2E946AULL, 0x844CDCE6EEA1F41EULL, 0x07E49FF8A09018D1ULL, 0xC8939BA4B425BFFAULL
        },
        {
            0xE91174D88B048E59ULL, 0x495A2709A3FEDE49ULL, 0x62A227CFE12DBE2FULL, 0xEB3DCA10A62C8AB5ULL, 
            0x9210A65D237E2AECULL, 0xBCA196BF03E10712ULL, 0xFF68C8E5E7B866DBULL, 0x6A1D6A4812949043ULL, 
            0xA2B591E4D8D77D81ULL, 0xCBBAA66E76ACE364ULL, 0xA067301207A47432ULL, 0x8586658E4F0EA032ULL, 
            0xECF1681AE438BB11ULL, 0xC12DDADBA27C6FBAULL, 0x43EBE62C3E76B26FULL, 0xF28A344BAEC18BC9ULL, 
            0x690C875CFD65626AULL, 0x949A7BDE1F232785ULL, 0xDB2358E43C7EB8FFULL, 0x651C0344CA092CC3ULL, 
            0xC10D128927075777ULL, 0xA9843788A83377F7ULL, 0x80F6FE84F4C525FAULL, 0x25E7A685F25FDE8BULL, 
            0xC66D225B6A40D895ULL, 0x081827DDEA556BA7ULL, 0xC1D7CBEB6902C143ULL, 0x68A02131A7DA0AABULL, 
            0xD7D26DC0F0448101ULL, 0x7207F70391FD94A8ULL, 0xAD5DD050FB86975CULL, 0xFDB5A609ED26EEBCULL
        },
        {
            0x8BFD46E0ECA3B0F2ULL, 0x06705BF8E8A51CC1ULL, 0x086371569BA198A2ULL, 0x50100AB42B79B4C0ULL, 
            0x952EC1DB4B37829CULL, 0xBAA76D7E265B7CC6ULL, 0x4A3A43CC5AAD8568ULL, 0x6D11775037942A6CULL, 
            0xB895EB825A157B55ULL, 0xC77BA6132C1F9AA2ULL, 0xFA03C16F964D5006ULL, 0x9D99649333237909ULL, 
            0xBB82D224CE9711DFULL, 0x57C0F6C6EC5B6945ULL, 0x04AA39BC6FB227C2ULL, 0x51453696B0426972ULL, 
            0x4B0256426299A916ULL, 0x56DBFE2F4F0D9863ULL, 0x15A7DF284E42CCFBULL, 0xB9E8E6AAD973C70CULL, 
            0xECC09A90601FC343ULL, 0x42D4738318057CB1ULL, 0xCEAE77D1BF7CE16AULL, 0xD198430821123627ULL, 
            0xFC60060FDE117931ULL, 0x991FB98CEDE96C5DULL, 0x2F96F941FB899676ULL, 0x5C0A7D61A48AB67BULL, 
            0x467CE72A21B15DA4ULL, 0xDF0D5E28DD3E9E13ULL, 0x72F9EE3DF1C2722EULL, 0x11B290B611C79FDDULL
        },
        {
            0xCAA41BADFE2344FEULL, 0xF06EC185EE18C48DULL, 0xCA2C0671371DAFA0ULL, 0x6C648AE2037AA0F8ULL, 
            0xA352E81335755204ULL, 0xD8B8C083E6376C3DULL, 0xA319A885A7D78D64ULL, 0x86E5A4BAB7A36AEFULL, 
            0x16AEC02D3FE84659ULL, 0x21FD3DC7338324AAULL, 0x83252A118C32AE76ULL, 0xF8A90398D0453C83ULL, 
            0x48D9B86D9C03BA01ULL, 0x1050DE338F888D3BULL, 0x8EAA00015DD064D2ULL, 0x9669F47B6F47A36AULL, 
            0x417A56EBE57E441AULL, 0x49F41AFE671082ADULL, 0x035ED9BF173D8A81ULL, 0x75306C702A335A0BULL, 
            0x5842A404853E2192ULL, 0x69A605A5C9E4DD2EULL, 0xFF10D7308BDD0E54ULL, 0xF878F4A8809F0492ULL, 
            0x6D8DDA545DDD76E1ULL, 0xFF5F160034C3C616ULL, 0x3E4BEAE05BB9EE42ULL, 0x90299434F6D5A385ULL, 
            0x39E5AEBF6C2C540AULL, 0xABBE1A3F5F2DCA20ULL, 0x8A61B163EA485A42ULL, 0xBB7DF4A68B17B889ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseHConstants = {
    0xB43FBB03483CFCA0ULL,
    0xCF0AE4D4C9505FBCULL,
    0x09DA76C7FC92099FULL,
    0xB43FBB03483CFCA0ULL,
    0xCF0AE4D4C9505FBCULL,
    0x09DA76C7FC92099FULL,
    0x0951E024A15C7A1EULL,
    0xD0DBE2C17D0C69B9ULL,
    0xC0,
    0xC7,
    0x77,
    0x66,
    0x41,
    0xD7,
    0x2C,
    0xFB
};

