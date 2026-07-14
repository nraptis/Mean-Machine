#include "TwistExpander_Menkent.hpp"
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

TwistExpander_Menkent::TwistExpander_Menkent()
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

void TwistExpander_Menkent::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9076C7ED385FA518ULL; std::uint64_t aIngress = 0xBF6A8EDC560D6A3EULL; std::uint64_t aCarry = 0xDF4CC68A05F0184DULL;

    std::uint64_t aWandererA = 0xE60D15A27E29A723ULL; std::uint64_t aWandererB = 0x8E04AF0C9ACC31BAULL; std::uint64_t aWandererC = 0xD19990DA787CA383ULL; std::uint64_t aWandererD = 0xCDF10CBE8852ADC0ULL;
    std::uint64_t aWandererE = 0xEF20C170ACBC8C75ULL; std::uint64_t aWandererF = 0xAE4564CC58F65E1EULL; std::uint64_t aWandererG = 0xC4CD04CE5730E0E6ULL; std::uint64_t aWandererH = 0xC8DA25D7B33EF081ULL;
    std::uint64_t aWandererI = 0xFC2BC36DF68AE66CULL; std::uint64_t aWandererJ = 0xFCBDDF6FC7309914ULL; std::uint64_t aWandererK = 0xE9A72E479175FFE8ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13656365349321192801U;
        aCarry = 16959790063537555017U;
        aWandererA = 13202364017062669992U;
        aWandererB = 11631379159769394127U;
        aWandererC = 18092228382381118794U;
        aWandererD = 10366382305478433319U;
        aWandererE = 12014137079085244614U;
        aWandererF = 17730040145497787169U;
        aWandererG = 12073037852181410678U;
        aWandererH = 9996071622271428230U;
        aWandererI = 13796176948003108752U;
        aWandererJ = 14563131869979311166U;
        aWandererK = 16284642987050731457U;
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
    TwistExpander_Menkent_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Menkent_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Menkent_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Menkent_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Menkent_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Menkent::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xDBECABD19539D2BAULL; std::uint64_t aIngress = 0x9901606806FA1B45ULL; std::uint64_t aCarry = 0xE9F8ED47F1B298D6ULL;

    std::uint64_t aWandererA = 0xD60271C40292176EULL; std::uint64_t aWandererB = 0xA84CC1E502883F6EULL; std::uint64_t aWandererC = 0xF90481FD754B1BE8ULL; std::uint64_t aWandererD = 0xA5921F1642CE2A37ULL;
    std::uint64_t aWandererE = 0xAA7A818C8A9AB88FULL; std::uint64_t aWandererF = 0xE05213208A33E733ULL; std::uint64_t aWandererG = 0xB70F9005F3399E95ULL; std::uint64_t aWandererH = 0xAFCD8000422025CBULL;
    std::uint64_t aWandererI = 0x85C8D4465DC359A2ULL; std::uint64_t aWandererJ = 0xAB1C348051AB5B20ULL; std::uint64_t aWandererK = 0xD513862BBDD83201ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14525567548187186278U;
        aCarry = 14327053454165095252U;
        aWandererA = 17687472846760638683U;
        aWandererB = 11225356082405199086U;
        aWandererC = 15622481136581972349U;
        aWandererD = 14357457204417055015U;
        aWandererE = 13711161246847342765U;
        aWandererF = 10550297405845928738U;
        aWandererG = 15590764359724459597U;
        aWandererH = 12857823599505470472U;
        aWandererI = 15023532747565908816U;
        aWandererJ = 13652240415747630618U;
        aWandererK = 12677735960835637188U;
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
    TwistExpander_Menkent_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Menkent_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Menkent_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Menkent_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Menkent::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xCE9FE4137816A6A4ULL;
    std::uint64_t aIngress = 0x931E615AA4A50C09ULL;
    std::uint64_t aCarry = 0xB8242FC7433AC41FULL;

    std::uint64_t aWandererA = 0x80A9202410ADC325ULL;
    std::uint64_t aWandererB = 0x94E2A30CCBFD6D0BULL;
    std::uint64_t aWandererC = 0x89ABA167C9291154ULL;
    std::uint64_t aWandererD = 0x925CD0D626ECE69BULL;
    std::uint64_t aWandererE = 0xFEF5220183554C17ULL;
    std::uint64_t aWandererF = 0xD5F33D1195FB08CAULL;
    std::uint64_t aWandererG = 0x9E32C013635C2934ULL;
    std::uint64_t aWandererH = 0xCD41553544CB2AEBULL;
    std::uint64_t aWandererI = 0x84937820EA48B16BULL;
    std::uint64_t aWandererJ = 0xC9400268CD9580F5ULL;
    std::uint64_t aWandererK = 0xF134E25DFE1DC3C0ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneB, 0);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneB, 4);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
    TwistExpander_Menkent_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Menkent_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Menkent_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 18 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1799 / 1984 (90.68%)
// Total distance from earlier candidates: 30762
void TwistExpander_Menkent::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 680U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1301U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1004U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1987U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 843U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2046U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 333U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1625U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 718U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1102U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1694U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 724U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 791U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 644U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 385U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1251U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1737U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 621U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1123U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1134U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 367U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1227U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 754U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1786U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1232U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 512U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 38U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1319U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1509U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 792U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1261U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 199U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1438U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 604U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1364U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 195U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1141U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1018U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 113U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1427U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1783U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1549U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 386U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1038U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 588U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1375U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 140U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 153U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 268U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 221U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1978U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 345U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1518U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 615U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 467U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 853U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 529U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 883U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1051U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 782U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2000U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 34U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1776U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 610U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1179U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 750U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 915U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 868U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 866U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1237U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1511U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1374U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 232U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 238U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 625U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1653U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1142U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1333U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1926U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1916U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1907U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 390U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1523U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1497U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 65U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 707U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 977U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1779U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1736U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 779U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1166U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1646U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 241U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1691U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1362U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1284U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1340U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 595U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 295U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 650U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 0U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1450U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1419U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1949U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1299U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 36U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 230U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1662U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1059U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1064U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1594U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 422U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1655U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1735U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 249U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 536U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1940U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 67U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1833U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 449U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1350U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 370U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 19U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1143U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1462U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 880U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1888U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 648U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Menkent::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xCAA8EC8BC288973CULL; std::uint64_t aIngress = 0xBE00F2A55595F01DULL; std::uint64_t aCarry = 0xC3C5E74000415300ULL;

    std::uint64_t aWandererA = 0xEB4FF1E1FE801B1FULL; std::uint64_t aWandererB = 0x8EE38077D7847842ULL; std::uint64_t aWandererC = 0x87594DF77AAD346BULL; std::uint64_t aWandererD = 0xCAE1159EA92F3A6BULL;
    std::uint64_t aWandererE = 0xBC7FA4C119137ED7ULL; std::uint64_t aWandererF = 0xA5779ECF336D75E8ULL; std::uint64_t aWandererG = 0xADBA0C18FA99BC68ULL; std::uint64_t aWandererH = 0xD047719274F88DAEULL;
    std::uint64_t aWandererI = 0xB46176BA060CD47DULL; std::uint64_t aWandererJ = 0xB4515189346EAC30ULL; std::uint64_t aWandererK = 0xD1F3223E1050BCCCULL;

    // [seed]
        aPrevious = 15440063968718878983U;
        aCarry = 9762800583984200096U;
        aWandererA = 13446397463108693491U;
        aWandererB = 13418626285653425258U;
        aWandererC = 16500439312586189905U;
        aWandererD = 11318883221193653679U;
        aWandererE = 10492924230105920837U;
        aWandererF = 14925482003540413423U;
        aWandererG = 16907792059468731674U;
        aWandererH = 17235075980217073270U;
        aWandererI = 9963720567474389246U;
        aWandererJ = 14333017527937009405U;
        aWandererK = 12304751796942988005U;
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
    TwistExpander_Menkent_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Menkent_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Menkent_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 18 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9269; nearest pair: 492 / 674
void TwistExpander_Menkent::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3940U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 115U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4560U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7623U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7644U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7493U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8093U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5450U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5758U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6628U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3790U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5596U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6508U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7594U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6247U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7103U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 921U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1412U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 574U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 332U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1139U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1978U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1264U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 461U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 911U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 57U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 74U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 420U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1571U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 359U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1276U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1134U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1055U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 424U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1562U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1479U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 18 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9260; nearest pair: 472 / 674
void TwistExpander_Menkent::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3257U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8002U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4470U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7581U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7822U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1753U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 469U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4097U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7912U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3215U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5064U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2711U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7154U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3248U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2801U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6667U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 453U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 305U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 429U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 390U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 535U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1968U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 392U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 932U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1833U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 51U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 59U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 391U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2026U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 435U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 753U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1202U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 599U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1753U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1263U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1239U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseASalts = {
    {
        {
            0x8D9E880374E8E910ULL, 0x9DC2B16B84C38883ULL, 0xF7FBC979159224D5ULL, 0xFC3FD10C49D79526ULL, 
            0x9DA38D6CBFC7628AULL, 0x241F6AA5BDD5940BULL, 0x404239FFB01B0B2CULL, 0xE056B4A709956749ULL, 
            0xD2A15849619E00C1ULL, 0xEC106CACAC8AC790ULL, 0x2F7F43673CFF16EBULL, 0x4752E9F3B77537C2ULL, 
            0xD7EB0FD58E12A405ULL, 0x54DE22EEDD93826DULL, 0xD1B5C7CFB2A8AA48ULL, 0x3B9420E8A2A93986ULL, 
            0xEABB64DECF1E0D8AULL, 0x25A836140B564920ULL, 0x46DE5DFF560679C7ULL, 0x255A96975D0D24B6ULL, 
            0xFC840D25245733FAULL, 0xFF879736477F7A59ULL, 0x36D003938CE82F7FULL, 0xB3CCAA0DA7C1A3F8ULL, 
            0x3545B7FAB7A8D309ULL, 0x3FB674F57CA312BBULL, 0x20091D5E670CE059ULL, 0x47006B02747EF183ULL, 
            0xC04F4DA0567E2DF9ULL, 0x200A42D03CF67E5BULL, 0x955BEE02042EA335ULL, 0x5B835664219621ADULL
        },
        {
            0xBF4636886F4CB05CULL, 0xD908997470578E69ULL, 0x0C9B1B21622071FFULL, 0x13F18B7FD1E4202BULL, 
            0x24C306986BC7DBA0ULL, 0xF3F68BE144A52FC5ULL, 0x8782AE3C0D7BCA24ULL, 0xA899D4A06E202487ULL, 
            0xCD8D7A38BAA0469FULL, 0x8A21BE60E9304850ULL, 0x0C1E3E6877FE5F0DULL, 0xB23AC05C105771E6ULL, 
            0x8F56AC551E19351BULL, 0x387FF236EA3DBD48ULL, 0x656A4B7408D80617ULL, 0x82CF4D2458D6D13FULL, 
            0xC313DFEC46F543D8ULL, 0x7C8438B3409D71B8ULL, 0x6DE9155DC904E42AULL, 0x0CFDA440108D8FB8ULL, 
            0xF91982CE3BE72171ULL, 0xA0495E3A3E75A6E8ULL, 0x41210C9A356C9DC1ULL, 0xE20E2EE8750D1522ULL, 
            0x3FD09F53A7673D22ULL, 0x9B41C2200E12221FULL, 0x5434F47CF11F1522ULL, 0x0E06492E788DE5DBULL, 
            0xFCEA9CCCB2301E45ULL, 0x5B364EAE96570072ULL, 0x39DDF7F745E6D2C0ULL, 0xFDA9C642028CC03EULL
        },
        {
            0xDFB2980F71E14845ULL, 0x28099648C6C6F9B9ULL, 0xBE06B29DC60EBAECULL, 0x99E8915FA5A67275ULL, 
            0x736949F285C89E2BULL, 0xDEF007FDF1C0FDFAULL, 0xFF27AE29783A3E0EULL, 0x7F1643B90FAC4082ULL, 
            0xBE74952416011EFBULL, 0x916E613164B342B1ULL, 0x240B526C954C574CULL, 0x311B3FF69457CBECULL, 
            0xAAFF0351699CBDF0ULL, 0x3C68B1604E8ACCC9ULL, 0x3F735F9C8E6473BDULL, 0x6A018651413AFC8BULL, 
            0x342693834C89CF56ULL, 0x2A91A2E04CCF2F9FULL, 0xC9933F73ADFC9142ULL, 0x3F398DB27F1A8B1BULL, 
            0xAAE0DB8EF256BA4CULL, 0xB12FEC0BF84FDC00ULL, 0xBA74D32BAE2102D5ULL, 0xCC60A4F74EC2C71EULL, 
            0x48EFC2096794D1C2ULL, 0x4C3B9F9157E0EEF5ULL, 0xD8BB436ED5EFB20AULL, 0x5FF82AC5D69EC78AULL, 
            0xA82603050EE72051ULL, 0x734AFC1A8D290D63ULL, 0xCA162A01725F8DB4ULL, 0x19CB3D3E8308CF36ULL
        },
        {
            0xF69122221269F612ULL, 0xA42E4EEDFFDA849CULL, 0x999820F8216BF60FULL, 0xE9C1B396F686AE8FULL, 
            0x9B43FE185EEF760CULL, 0x081E85518250E3BEULL, 0x3A7DB0F16E7296C2ULL, 0xEBE761658281E37CULL, 
            0x73E07EC91F74F4CDULL, 0x9C71BBFEF40AEE4FULL, 0x384697059EDFB0D5ULL, 0x667B1218ACF66AE9ULL, 
            0x58527890C41B0528ULL, 0x655D88520CF4B555ULL, 0x33EF320DEFCA1CD5ULL, 0xB231A9AD80326E44ULL, 
            0x4C4AAEC348ECD923ULL, 0x231CEC352130BB11ULL, 0x87942E3DE0A35189ULL, 0x4A7004CD2D37441FULL, 
            0xE0A2F785AC59883FULL, 0x701C2542534365FEULL, 0xDA6F5BB012F99758ULL, 0x9DC1E008A080A610ULL, 
            0x3D4E90A37FB0F7BAULL, 0x641D2F67FC91DFE9ULL, 0x8F3DF0841BECFF80ULL, 0x13C9C4CB606CC865ULL, 
            0xE5ACB2CB0C06CF17ULL, 0x5E8C3B496E26D0DEULL, 0xFB0B84EBFE652298ULL, 0xADDEFA99DD8F15EDULL
        },
        {
            0x02347697CF58891DULL, 0x788A6356F9B5E6A1ULL, 0x3C3251896AC25BC4ULL, 0xEBCE33087B68AFA9ULL, 
            0xC16D19E94BBA0EE4ULL, 0x44C02978E60DC3CCULL, 0x565B5FE90C467E90ULL, 0x32BF87767D88B1C5ULL, 
            0xA537462527534107ULL, 0x6C9F4266D0BD15BBULL, 0xE5E80DAD5D012498ULL, 0xA3682DFCE19EB168ULL, 
            0xEA59417788E93B2AULL, 0x4D4C1D8438764349ULL, 0x68AC2395C7F4169AULL, 0xD3D6928DC10ECD56ULL, 
            0xDA2DD26578016A67ULL, 0xA953EB94D688BFB8ULL, 0x1CDED2877ED89223ULL, 0x2495BFD804A0EC57ULL, 
            0x534C95C47D57D63EULL, 0xC0840CE3937AD2CBULL, 0x98C1861A8B6E8954ULL, 0x4AA6D19CF981A75CULL, 
            0x9997F8D7FC633BC7ULL, 0xC3E930CEDC57B7C1ULL, 0x8EFE20324D790C0CULL, 0x4C9F2ECA1CE8AEE9ULL, 
            0x8A4E51D85195E85EULL, 0x016432EE5789CD59ULL, 0x122DCFB3D09BC79CULL, 0xC5940506E2B1F53BULL
        },
        {
            0xD23FFE9988446E3AULL, 0x6756E03F46D1E795ULL, 0x17239481332DD4D8ULL, 0x59757F5F7FE6FC01ULL, 
            0x35D6DBDA41AFB8FCULL, 0xA3CF0A794F073E3FULL, 0x98F1D67B7FF5FB54ULL, 0x1C7000F290A57636ULL, 
            0x8E6FF4FAC042BA32ULL, 0x1B1EF83569572F3CULL, 0x1FA65BDDD57767ACULL, 0x0DB3BE00E4D6A669ULL, 
            0x4F571F5B00CFC7A4ULL, 0x611E73C450484D08ULL, 0xC5C1613D60477197ULL, 0xE4B53519B1FFA55AULL, 
            0x8401E90ADB50BDFEULL, 0x61F8592FF16A572FULL, 0x3B72E8DB71E35341ULL, 0x803B8FC3B1FF1043ULL, 
            0x352D6168B7283879ULL, 0x2998A21758EA9D1FULL, 0x56DC77C317999138ULL, 0x1AF9182E3A0FF64FULL, 
            0x6CB415BBAEB35332ULL, 0xBAE840C9974A2A87ULL, 0xC300A9200E263005ULL, 0xD4DC6387EC5BA101ULL, 
            0x5452CA44C258C59EULL, 0x83B28E1BFA20967CULL, 0xF1543389F1DB58AFULL, 0x8DF1026287CFDFB3ULL
        }
    },
    {
        {
            0x8B12846D2D145464ULL, 0x0745948BC604B5A8ULL, 0x32EE80FAAB79B8D6ULL, 0x10B4B4225A0C0788ULL, 
            0x0363B9D93987EE8EULL, 0x689FD3BC9A0B89ABULL, 0x02948657306A06B7ULL, 0x9F819686433F73D9ULL, 
            0x6CABF3220A0F8348ULL, 0x2F165DF70E080C25ULL, 0x48721E7354D84C0CULL, 0xABCFB1EA800A590AULL, 
            0x4B88CA81E2158B0FULL, 0x7B4672E9D0C38C50ULL, 0x7DE83681B03B5850ULL, 0xE6B6858E5834E3D1ULL, 
            0xDE44091D3F4A2AB9ULL, 0x65A5C1A7F7A46D50ULL, 0x7D5306167441F261ULL, 0x8ADE63B958596A14ULL, 
            0x400EE12CC4534910ULL, 0xA1C48CCC2BBE8774ULL, 0x729223B19F17377CULL, 0xC015F37DA1B5792EULL, 
            0x23E37B0B1DAE2501ULL, 0x8DBC07AEE173FC64ULL, 0xAA82557FEBDD1651ULL, 0x4505F49DE6821B18ULL, 
            0xFF1033B23ED6AFD6ULL, 0xEE558DFD75989B3DULL, 0x99669A8CAF2B378EULL, 0x9C771F524E8D7E90ULL
        },
        {
            0x19868CD52C34E472ULL, 0x40DA01CCD4FF87A6ULL, 0xC39596A26ED4C2D5ULL, 0xF64BEF2900F8542CULL, 
            0x0F5E992D84FF4AE7ULL, 0xE31B075AF6849AA1ULL, 0x7EFB6B74E6A11016ULL, 0x9836041A84BB6492ULL, 
            0xC08F236BAB71BDE4ULL, 0xB0D922666D19F3EFULL, 0x3F79DB5962FBA3D6ULL, 0x53EFFE54D0125CEFULL, 
            0x6432DC06FFA07152ULL, 0xE411ECD944970908ULL, 0xAA74E24B3508FFF4ULL, 0x79E2DD3361BBC58DULL, 
            0xB5C7192A230B0E04ULL, 0xCAE5C75968815F9EULL, 0x455DD31207E99D8CULL, 0x5E52BD39E4D9EA2FULL, 
            0x8551836C5ADBDE34ULL, 0x439CA041FD732857ULL, 0x9806DB1B975A3231ULL, 0xACC89AD2A966F31DULL, 
            0xAC920B7DBB9F71C2ULL, 0x72E5547E9F4EE077ULL, 0x75EDAA2E91A13CE6ULL, 0x08B96F834DDAF697ULL, 
            0x2A9BB32CA3DC5C47ULL, 0x2D88862E2DC6716DULL, 0xBA76136448CAC65FULL, 0xAE72992518595C71ULL
        },
        {
            0x8CCA0BFAEA180CD5ULL, 0x670CF513EFDB4A5DULL, 0xC7D1DC06518E53B3ULL, 0xDF8E11F64219B493ULL, 
            0xD91141A7EC21BD96ULL, 0x5BF819565E68D351ULL, 0x997FC1FDC4777DC3ULL, 0x312979E7AF033856ULL, 
            0x4D4732CE923001CCULL, 0x6A7D4AF32C99E34DULL, 0x9A23CD87745FC92AULL, 0x0FFA24DA58660347ULL, 
            0xF40355455CD16D8DULL, 0x88DE555736F148E5ULL, 0x0586551CE8B684A6ULL, 0x6123E06B2EF2E94EULL, 
            0x3DFC5AA317F3201EULL, 0x02EEF7CD01847792ULL, 0xFF69996CD835A95EULL, 0xCAE0E70B8625BDE1ULL, 
            0xF16DF2B68D37D866ULL, 0xADD2A4DBECB7D536ULL, 0xA7934BA9355418A2ULL, 0xFC29A614AEB4A5A0ULL, 
            0x134CA52485836509ULL, 0x85958D80A6ED2D98ULL, 0xF4A4EBAB791D1D30ULL, 0x9D78AD3827C9659FULL, 
            0xBDDD3BDAA7115DC1ULL, 0x0F4581B8D8A6D6C5ULL, 0xAE81A5EAD15DD783ULL, 0xC2946DBC59030659ULL
        },
        {
            0x77AFE4712F7C2F9BULL, 0xB80A0D04AAED55B6ULL, 0x09583D44DC2C9DF2ULL, 0x2EB2B7BFFAE4729DULL, 
            0x3CF06ACD8F47E793ULL, 0xB915C16E958AD643ULL, 0x9BA62E903C58AD51ULL, 0xD6C22F66BCACFE66ULL, 
            0xA83E722BDDDB69EDULL, 0xB6C23A43CA08A1CBULL, 0x801B7FED8D10E16EULL, 0xB54E1904F519AAC1ULL, 
            0x9231683A9406463EULL, 0x5CCC5A3844804179ULL, 0x683BD6E029F8CB48ULL, 0x9627F81811D35AB2ULL, 
            0x47D95F16BE817737ULL, 0xAD395E00B1DF29FEULL, 0xA59E796E58A88305ULL, 0x882A602EFAE5E565ULL, 
            0x67A5E5968D176CBBULL, 0x1AC2659291D11028ULL, 0x61D2EAE58D738BD1ULL, 0x7826431A4A1474FAULL, 
            0xBBC4BB5584A58F19ULL, 0x1C83FD81D6574149ULL, 0x136D7E59B281DC24ULL, 0x8C56B78F391FD7B2ULL, 
            0x4B45173A7A6F8247ULL, 0xE57FFD21527A00DDULL, 0xDC572CA71C8F520AULL, 0xE36DA64187624749ULL
        },
        {
            0x0DDCC34F46D19AEAULL, 0x1DBCAB5525378FB8ULL, 0x64B7FF6B71DEA381ULL, 0x879E7884A296DDBDULL, 
            0x402446BDF0E0CC6DULL, 0x2357A3C34A3BD92CULL, 0x297E6FE36D4DD1C5ULL, 0x2D564CF8C289FD9FULL, 
            0xECF807D2FD6C880BULL, 0x2233BE897910A649ULL, 0xD82869DB46A73166ULL, 0xA9355F7533A6916AULL, 
            0x9A4D9A39B675922DULL, 0x135CE7E68DA6354FULL, 0x71343289E0AE4539ULL, 0x9BB88EB1045EA085ULL, 
            0x83B4379D42865F82ULL, 0xD121DD89AD3DBB6FULL, 0x98DADC575A0A4247ULL, 0xF0B28762A7EA3BC4ULL, 
            0x564353A63B69C5E3ULL, 0x50232614A04BE190ULL, 0x1F1C54DC19011F47ULL, 0x20339E5D002F0E8CULL, 
            0x4CCBA38CDE13A15AULL, 0x4FCF255200DFB8F5ULL, 0xC1B08AB35F1C2EEEULL, 0x3969605760CC4391ULL, 
            0x526479CCD0BD0603ULL, 0x0B6B173D2325FA2BULL, 0x8E52F696210D97EAULL, 0xE3917532EAA97C40ULL
        },
        {
            0x701E257BE9AB6BC6ULL, 0xA8E920007B599CBCULL, 0x4761ECF522700453ULL, 0x4676698E7F3F5F2EULL, 
            0xE0FC68CD192488D0ULL, 0x416CBDBF3E4DFAB5ULL, 0x06C54875CD3801BCULL, 0x8921FCE9D55F60C1ULL, 
            0x56A5853509D47374ULL, 0xB529124ECDE1371AULL, 0x62BF41FA51CB29A7ULL, 0x3C733F60E35A25ABULL, 
            0x41ED91FA3ED8A9AEULL, 0x5B4646507E49C02EULL, 0xFBDFDEBEF176D65AULL, 0x26071800B20D55FDULL, 
            0x8B77F5F1AE0BA464ULL, 0x99398B20817BEE7AULL, 0xA9AC35179C6622CEULL, 0xE3EAC3D960FD5772ULL, 
            0xFB4A23A89E87FD28ULL, 0x89321F7B52BE8871ULL, 0xBDCA6ABF713C7FB6ULL, 0xC0C74DC156B5FF09ULL, 
            0x2F7F05E30FAB1C16ULL, 0x153CEEF7955CEB48ULL, 0x69A7B3DF7C257FE1ULL, 0x9EA3B5027B1E7C90ULL, 
            0xEE5A4829AA2D9B8FULL, 0xAAA2498BDBC79546ULL, 0x75847489A01EC5E1ULL, 0x04CB768197264343ULL
        }
    },
    {
        {
            0xFBB412159A69606CULL, 0x0AEBE5DF2DA2D4E6ULL, 0x1B897413F5000E00ULL, 0xF97CFAD55B4DC273ULL, 
            0xF093AE1873C30467ULL, 0x6FAE2140FFE61946ULL, 0xFE1FE71E1BB5CDB1ULL, 0xE9C304982D68A728ULL, 
            0xAD4CCFBF3E8F4396ULL, 0x6A72C64D3C9E00F4ULL, 0xAD3D6CBF91938F82ULL, 0x4106E28A9A2514F6ULL, 
            0x5BC2978DB23EF53BULL, 0x78938A071024136EULL, 0xF9D328E6633BF3D3ULL, 0xD40F73E486658497ULL, 
            0x9B4E4E5D17D5A9A6ULL, 0x22BDA0E46CA00CE0ULL, 0x6325C5984E55F826ULL, 0x368E7DE9EC5C0423ULL, 
            0x8696AEF0F46660D6ULL, 0x60EF9E5DDEA20155ULL, 0x14824462C1C4DE48ULL, 0x0643DF9D376A3B76ULL, 
            0x2F5C17C66E79CCBFULL, 0x073B790B904F71A9ULL, 0x4F157F55A7F2A8D9ULL, 0xE8611AEBC926ABD9ULL, 
            0x319AB58546BCF6A0ULL, 0xB8DDFB679F0AE70BULL, 0xE05BAE2848116CF1ULL, 0x675CB07766DD37EEULL
        },
        {
            0xB7E1396493882733ULL, 0x76A3F110E77FDC68ULL, 0x45FA98AEC421E1E0ULL, 0xABC345FD48A7BE2DULL, 
            0xED964D4450941656ULL, 0x6E2982CC147F03EDULL, 0x7AE0ED3FCF4ACC3FULL, 0xC9E4D9B0E2AC8CB8ULL, 
            0x95F30D6AD042B0CAULL, 0x8E21B9F54459FC27ULL, 0x9FD46AF7783BBC6EULL, 0x8E9A6FC4916BFA9BULL, 
            0x37ED9DE4D469C7E0ULL, 0xF27827C2CFB8D767ULL, 0x5A28143FDC5950A4ULL, 0x9AB13FAC98470B61ULL, 
            0x62AC6705D944B59FULL, 0x0265436C2B1DE0DFULL, 0x04F7FBF3D905A2AFULL, 0xEDE579E47C1008C7ULL, 
            0xFD4828AD7F55247AULL, 0x05592C54C4E78D58ULL, 0xA53E71AD96AAA20DULL, 0x0CE398951C7BB8ACULL, 
            0x42FABF1BF6AB668AULL, 0xF43FCE121F0FDCF4ULL, 0x0C962E78B0DB1DA9ULL, 0x409516F39379F4C0ULL, 
            0x6BEF17872449EFFFULL, 0xDF03678C4D7298B1ULL, 0xBF967045C48AB5E7ULL, 0x8A007328ADB54DA2ULL
        },
        {
            0x05A54BB06594A5EBULL, 0x50C8C5AD11FB6EF8ULL, 0xCBC1328985BD364BULL, 0x6F9EC78FE913124EULL, 
            0xA1FA926C5EFD8984ULL, 0xF4FE36130A20FC48ULL, 0xD7BF9F39CA5803B4ULL, 0x804A13D8DFB9CCD5ULL, 
            0x4CC648BA45D0C33EULL, 0x9BCBC16BAC1AEE16ULL, 0x7AE4A282AD3A7575ULL, 0x483DF7F5670DE052ULL, 
            0x1296A4F6CEC239F8ULL, 0x1AB2DC3D87B4324CULL, 0x0051ECD692C06CB8ULL, 0x1999088AFC5970FBULL, 
            0x9C8C915DA8444DFAULL, 0xD0EA90CB93A1A6FDULL, 0x695690218031930EULL, 0x054984032B0D129DULL, 
            0x42D6C6BB6A55AF40ULL, 0x0CF1E1B517EA619EULL, 0x8E25CDD009EC8F7BULL, 0x1DB6704CCD401438ULL, 
            0x0B5DE89B6D709AF9ULL, 0xE37F8AEB3C31EE26ULL, 0x39D03FD704ED8948ULL, 0x3100B7C91290E24DULL, 
            0x9B89A384434F62ABULL, 0xE7965FDF40042145ULL, 0x98E139447CCC7FA3ULL, 0x622FD11E681A6472ULL
        },
        {
            0xC1402491CB716B29ULL, 0x9EF877B78A76E2FBULL, 0x70B8A673F36E15D7ULL, 0xA6F175DAC2E2F178ULL, 
            0xC01EF93DDD7901F5ULL, 0xBA6C5D988213BAE9ULL, 0xFAD36C224C6C0DDEULL, 0xC28FAA653C8D27DAULL, 
            0xF62C0E82187692D8ULL, 0xBE3221E828F1793FULL, 0x39F0BE47391EC396ULL, 0x74EE7E2E61035876ULL, 
            0xB8F3535BADA8114DULL, 0x0C9FB1526B877DB0ULL, 0x64DC36350A2E0CD2ULL, 0x9E8DCE1D06164295ULL, 
            0xCC92AE509C37D609ULL, 0x7E1D8736240BC1DEULL, 0x8621F7FCC1A3E478ULL, 0x49FF2EFB93F130F1ULL, 
            0xF7A33D69D1CB5181ULL, 0xF89ACF4B7043B226ULL, 0x8010516B69374F31ULL, 0x1C79C94C82F383C3ULL, 
            0x462E312B3CB6170FULL, 0x403BC02A83EC2A82ULL, 0x23125F2A45FFAB19ULL, 0xA5C7B2AA89FF68A1ULL, 
            0xE690700DE7A72AF3ULL, 0x5D1B32AAF5535B04ULL, 0x5499E6AF6B5CA043ULL, 0xE3AF30838881EF8EULL
        },
        {
            0xD2BB94311C53BF7EULL, 0x3448E17EFCD051F7ULL, 0x48C83AF83B90203BULL, 0xC52BD5C39DA657B4ULL, 
            0x31F1675952D7E461ULL, 0x9D64F8F6511FF69EULL, 0x7F1D29D37BFB11E4ULL, 0x81D0BFDBD9F1EB33ULL, 
            0xEF663EF67129588EULL, 0x22920B9B92A11A9FULL, 0x4B0C6BA39ED77427ULL, 0x9285D8D693303D58ULL, 
            0xCCC30D4BA179B654ULL, 0xDD07A87DDC03AE58ULL, 0x32E1AD858384E06FULL, 0xEF67069369EDC83FULL, 
            0x569A11F3447C8A92ULL, 0xC4C37D337EE2FC93ULL, 0x13776D4A6E17CE1FULL, 0xD40A7F783D28A60FULL, 
            0x07E9E02E7E6C9C7CULL, 0x0255B5CE09B4AC66ULL, 0x5921A63108ACA99DULL, 0xBEB258B6BBE33553ULL, 
            0x4E06BEB57617DEAEULL, 0xE5A9FAFE3D4B610CULL, 0xAEB2DAC8CDC7255CULL, 0xE4A107A1DEA5504AULL, 
            0xC1B5C1889F2CCBFEULL, 0x6A4F1F6BBB64C0A6ULL, 0x5913CF1C19691831ULL, 0x734E7599E2734974ULL
        },
        {
            0xB04C0C735E2D1C1AULL, 0x860989FE275E0F11ULL, 0xA607DE31081F32D4ULL, 0xE14AB80FE1B4DA3DULL, 
            0x8EFD4411E2B6C2A4ULL, 0x217D8EB319E0D9E5ULL, 0x06F6F9F067865719ULL, 0x5021DFF163EFA491ULL, 
            0xF7729CBA702E29EBULL, 0x96FE509E4579872CULL, 0xEDF6ADEE767CF2DFULL, 0xD7DB9728DFC78E05ULL, 
            0xA027B1E67E022D3AULL, 0xB75BBDFD32A027C7ULL, 0x5938E5B51C311ECBULL, 0xFDBD55B9159B15A8ULL, 
            0xDBDC6BF6EF6A6E68ULL, 0x41FFA08B1151FC08ULL, 0x55522646A463482BULL, 0xBB1DAEA55B42F5CDULL, 
            0xFCDF4CC857864E0BULL, 0xA6310F1E46FB137DULL, 0xD12B3CF5A2826591ULL, 0xBD6358897C46210CULL, 
            0xCF5F5CDE6E4D0A12ULL, 0x8705AB880C1241F6ULL, 0xE5EC61878F9DE5C8ULL, 0xA857B882055BB19BULL, 
            0xD59FC34D5C34940BULL, 0x40E52EAAC4F0A679ULL, 0xD4D66657687A6ABBULL, 0x0E4BF96341433F11ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseAConstants = {
    0xFEC0AF6E982C0573ULL,
    0x399A6F394639DA1CULL,
    0x04ECD90F2ADBA6A8ULL,
    0xFEC0AF6E982C0573ULL,
    0x399A6F394639DA1CULL,
    0x04ECD90F2ADBA6A8ULL,
    0x0F792DBE67C3FC85ULL,
    0x1C98FAF89C4C8249ULL,
    0x27,
    0xAD,
    0xC1,
    0xED,
    0x48,
    0x79,
    0xCD,
    0x98
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseBSalts = {
    {
        {
            0x747BFD3EC55652C5ULL, 0xD6094A6FDBA881AFULL, 0x081A0022E1A79A27ULL, 0xD9798F7FC34140DFULL, 
            0x5972229FDEFAD4CFULL, 0xFAFE3D4C92986E38ULL, 0x25458354972387EFULL, 0xA45E433F1B4ACAE7ULL, 
            0xCBA9FBECF06E3927ULL, 0xA9B33881841EF1B4ULL, 0xA17AB9F49E7F434DULL, 0x39880A300FEDC18FULL, 
            0x13129CC77F1E5464ULL, 0x7E9B952F502B967DULL, 0x7A5C6BD0FA43A3F4ULL, 0xB206319A2FEE55E9ULL, 
            0x451D873877DA102AULL, 0x94A0A05E6861E975ULL, 0xE08D4CD6F7D44292ULL, 0x262662340814E91AULL, 
            0x09920A2583FE63B6ULL, 0x34B4771897F9A801ULL, 0x046E29E85D5B7417ULL, 0xB229C259C17BEC50ULL, 
            0x4DB48A48975FC83DULL, 0xBC82CC2382EDDD6DULL, 0x95D3BAF001862AE7ULL, 0x66C0BD5908173458ULL, 
            0xB3F2B1E0CAE8AE30ULL, 0xEC7DAFB239BE3DC6ULL, 0xE8D9C1DAEC496D86ULL, 0xA76FC2C5A03BF0FAULL
        },
        {
            0xA490C00D182E6EDCULL, 0xB545519ED92F120EULL, 0x4111886834D09678ULL, 0xC8628A93F0223CF5ULL, 
            0x10A6BB29C434063DULL, 0xAF194FB2D59437E2ULL, 0xD0EBD8486F296222ULL, 0xB573239AB75DF65BULL, 
            0xB5D6E7A60C936EC9ULL, 0x0646D619FB46B86CULL, 0x028266D616EE0CC3ULL, 0x42DDF9F67D4B5BA9ULL, 
            0xDB85BB810C34C4CCULL, 0xA6F0A3CED8C398A7ULL, 0x3DA9AD50DE6554A6ULL, 0x2D4C32C7FC951F36ULL, 
            0xE5302746AAB63746ULL, 0xE3894DC267FDB1B2ULL, 0x2FD930A1B61D9817ULL, 0xF9BB3CE08A6559D4ULL, 
            0x1712354E33FCC01BULL, 0x85FC608A87DA4321ULL, 0x2FAE982A17D04F23ULL, 0x73DF95A6061C4AE1ULL, 
            0xEF495EA45A61CE89ULL, 0x6AAB04C8386FEA2AULL, 0xE8D458AA668AEA68ULL, 0xA595B12EA3D6C2D9ULL, 
            0xFA6341F543FC565FULL, 0x88CC58E91AEE6DAEULL, 0xFF64172085179460ULL, 0xE729FF09E0265557ULL
        },
        {
            0x19FCF73E4C7E2BAAULL, 0x0659F917212D9957ULL, 0x26C7B522BA44DC18ULL, 0xF008A8724B20B736ULL, 
            0xAC962DED5146E7A0ULL, 0xEED412D4F1988AFFULL, 0xB969DE2F0DE74D56ULL, 0xEF556446449B89D7ULL, 
            0x511E2A41C47FA937ULL, 0x7E9C07E21F93E36FULL, 0x4F4D0F358825894EULL, 0x956CEF06EBF72B27ULL, 
            0x34FD7A4557156E8EULL, 0x8AF9B1CC9047DB53ULL, 0x996AE323AA7806E7ULL, 0xD0C5F8044E8EDB8CULL, 
            0x85A1958FA72CA4AAULL, 0x1590B4B87D11C589ULL, 0xAE7571CEC079103DULL, 0xC3763B0E9A8E006FULL, 
            0xD0B042F9A4B1627BULL, 0x4ACDED8D4958E80BULL, 0xB73BAF127272F341ULL, 0x534D8DDA5EC6576AULL, 
            0x8CD4B32AF20E7FDEULL, 0xFC763E956BCE4639ULL, 0x56047A15EC1CE7CEULL, 0x94BA30D776A5F7C4ULL, 
            0xB985D7759899C5E3ULL, 0xCA11CB004FCCE69AULL, 0x2A6C0270861398DEULL, 0xFC8527F99BDF9ACDULL
        },
        {
            0x9AC100D648C31EBAULL, 0x675B4AAD9A323B06ULL, 0xD6DF86B4F6A958B0ULL, 0x0126A931B12EC309ULL, 
            0x009FB326E849A97AULL, 0xD996AB7F2B819196ULL, 0x954D54FDC512D02AULL, 0x14CF86AA486EAFEAULL, 
            0x8071062DF99ED7ACULL, 0x409DCCFB7D65769CULL, 0x74168D6AF3880818ULL, 0x92C878EC99929944ULL, 
            0xC32EA32D1B09857CULL, 0xBEF4E0119E5871F1ULL, 0x2783DEA1F60CAF23ULL, 0x409700BB665E28E0ULL, 
            0x19B73253A246FA37ULL, 0x100AA777DEA48860ULL, 0xC35C17035C90FC7DULL, 0xE8E469AA3252B086ULL, 
            0x3DD82087D3FA565BULL, 0xBF336D0D757C4A3DULL, 0xC530D8AAAD76670EULL, 0x22A2D92748D299A8ULL, 
            0x206834F29003048EULL, 0xAAD664458B87E218ULL, 0xAADD16366DE5398BULL, 0x3822482BA1928AC1ULL, 
            0x0CE18EE68490AB1EULL, 0x62CDEE83DE8C776AULL, 0x4AAA6DFA21A33CA7ULL, 0xC5725B09CC3CE933ULL
        },
        {
            0x7F58B8E02E79F364ULL, 0xBE083F36FCB2525EULL, 0x4DD56838C462349CULL, 0xD5934AFA094554E8ULL, 
            0xAC05148F7DE8247AULL, 0x1AEE5A68AD5CF0F2ULL, 0x92AD0C63F7659824ULL, 0x39842C3F0159FC66ULL, 
            0x318F5AD609711706ULL, 0x56AFD7533ECFA567ULL, 0x9862BE8117BBDE37ULL, 0x2AA74D2B26B9FF10ULL, 
            0x985D3EE97E9050ADULL, 0x34F70484DBE383C3ULL, 0xE7E55C9F0919FABDULL, 0x7273AB3E65D71B2CULL, 
            0x549A9DBE9690901BULL, 0x49717DFB64E028E7ULL, 0x8EE2A957072E6D44ULL, 0x32D9F49FAC382172ULL, 
            0xE0997CE02F6FCE35ULL, 0x17D52698E4640CE8ULL, 0x62FC0AB7038EA112ULL, 0x74AA083617E89074ULL, 
            0xE7390216F9868808ULL, 0x9C528AC2BFEA976DULL, 0x9ED3A86F16813B06ULL, 0xCA72FC32988577C6ULL, 
            0xE4E4AE1F7C0F2F8EULL, 0xE0D8E685C8C6F00DULL, 0xAE77CFCBF96F999AULL, 0xE66813DDF9E051A1ULL
        },
        {
            0x4B6C8B1A876A7085ULL, 0xA0D9B37AB02D1F66ULL, 0x512EE9D724BEBE3BULL, 0x9116793AE0635EACULL, 
            0x7AF51547A4AF1BDBULL, 0x368EAB8C7937CCCBULL, 0x33748FB569B58435ULL, 0x3C21CC58E04F30ACULL, 
            0x0120758A67F40F62ULL, 0xCF077942CCDAD77CULL, 0xDEED3048A036C15BULL, 0x760EB4A01385F8FDULL, 
            0x5871D21FE95CBAE7ULL, 0xB842254B4CF52D69ULL, 0x0B1CD65B5A9408CEULL, 0x589A0DA0C0EA9E65ULL, 
            0x5CAE168AB3A928B0ULL, 0x49AAAF7CE31D9B6EULL, 0xE82806CBD48F1963ULL, 0x95C183994C6591DFULL, 
            0x0697ED3B9D06D72FULL, 0x7C8426519CBF87FBULL, 0x3E398A3DB21246D9ULL, 0x7F8F1FF50E4B4D14ULL, 
            0xFDDD5E39CB79C222ULL, 0xC777A6B554D6EE85ULL, 0x8822483810AA7E7FULL, 0x89843E46E437D35EULL, 
            0x5EE9C4546E2BA8F7ULL, 0xCFB9C29899A1833BULL, 0x2D34ABA7AC0EAD4CULL, 0x8D8782815FF5A5A5ULL
        }
    },
    {
        {
            0x0A76237D1E2AF86EULL, 0x75D1DA0631D628E1ULL, 0x29B8BCAC51439C52ULL, 0xDD544D3AF9CF74DFULL, 
            0xBCAC4DB5CAAABB11ULL, 0xB11A8059A6FD756CULL, 0x60694B7F4AACC0F5ULL, 0xA2DD90FDBDC94633ULL, 
            0xB2B1AB2C96E1A70EULL, 0x7C00B7B9F2E9E884ULL, 0xD52F53F51DD2814FULL, 0xC6EAEA5734A179FFULL, 
            0xC336DFF59EA3CE96ULL, 0x519E3A0D330ECC17ULL, 0x7DBFB6C7F4C6D9D5ULL, 0x0EFFDDD1ABBEB3CCULL, 
            0x06CE08B63B2335C7ULL, 0x51A360A5DB88F43DULL, 0xCB2057C755633368ULL, 0x5ACDDDC6613BE721ULL, 
            0x70FA551E9ADBBAF8ULL, 0x89B98E18277BCAD7ULL, 0xED4A056805FFE7E1ULL, 0xC6B80F18135149EBULL, 
            0xF334D46CE95E9858ULL, 0xF89979331E1EA806ULL, 0x0E147C7920576DE8ULL, 0xF2F70D13C29A82D9ULL, 
            0xBDF4A562F91AB92DULL, 0x86DE8ED05CA29BEAULL, 0x1E4E218EA36122E4ULL, 0x6DF708C2BEA4F642ULL
        },
        {
            0x0E77CA5632397DA0ULL, 0x40671DCC52614060ULL, 0x23E3F0DF206962FAULL, 0xDF4F4E5866166DB4ULL, 
            0x025F255DAF5EF445ULL, 0xA1A176D9820FDD40ULL, 0x076984C462942932ULL, 0x7455CBF43A90AE53ULL, 
            0x0F15489C3DF41E99ULL, 0x77E76D91601D9BAEULL, 0x7A52B8E8D1451D2EULL, 0x4A2D5C6CBDA59F05ULL, 
            0x0C4CE50AFD441D7DULL, 0xAC4C407511399DD8ULL, 0x3420F5D9BB985797ULL, 0x56AAE3FD107FE80CULL, 
            0xDB89F9C4111FECBBULL, 0x597499B462AC7C6FULL, 0xA76E1B4A5821DF4FULL, 0x74EC6E8AEFD7804DULL, 
            0x8BCF34895DF5EA74ULL, 0x56DCC83D7D2F2B2DULL, 0x3A29F506BC6A58F8ULL, 0x4A445B68DACB075FULL, 
            0x5164C9549FABB25DULL, 0xC9276892644BBB48ULL, 0xB62FE160C96C5A07ULL, 0x5C023AC58AD10A52ULL, 
            0xCB84FF655EFFF986ULL, 0x6A5ED90D7901F779ULL, 0x394DB961E7296EB6ULL, 0x4806A41A90F67C7EULL
        },
        {
            0x543EC9ED70C223C3ULL, 0xC7FDA83FA4A1B7C6ULL, 0x2E84992F5DF17411ULL, 0xB3DAEE78E2DEA4A9ULL, 
            0x6416E91870BC27F0ULL, 0xD523824C73ADC4ECULL, 0x2C718BF3A7850464ULL, 0xBDA607D0CB7DD107ULL, 
            0x46D32204694A6714ULL, 0x4AF003D9170746A4ULL, 0xD619826B46ECDCBFULL, 0x5639B0EA063E0A0AULL, 
            0x431DA6E1898EFD12ULL, 0xBD30A095F6753372ULL, 0x41ECBC340A49C13DULL, 0x74AD1099AE361EBAULL, 
            0xB3178C303BCE146EULL, 0xC1F29EAF068AE605ULL, 0x45BB491C5881FEF1ULL, 0x45DBB2979DEB148AULL, 
            0xC4DCA8F008AB4B0BULL, 0xDAF884793C020C8FULL, 0xD1365201BEF3D4DCULL, 0x811794ECB6C04FD6ULL, 
            0x588D8FC42075020DULL, 0x61DE63F34D05E9D3ULL, 0xB62A66959A05CA8CULL, 0x42D781D936150B98ULL, 
            0xA897CDE2CA7E7387ULL, 0xF374F5307C6F3A3FULL, 0xAE23F94704F413C4ULL, 0xC8F1FEC9791018D3ULL
        },
        {
            0xE8F7F6BFF594638DULL, 0xDBB88A6DF5EB7300ULL, 0x3C4D295E8A67B78FULL, 0xB778F2487385283CULL, 
            0xCD0EC7C263148F38ULL, 0xD0A434B293E7C259ULL, 0x1E5962A9028FDBB3ULL, 0x73186D1D15064784ULL, 
            0xCC1DC06F52E1876AULL, 0x52442EEA505F6FD8ULL, 0xA77EF46E05D899D5ULL, 0x0F5788088B30EDE3ULL, 
            0x0C0CB8A594F12AE1ULL, 0xB4DE22EDCFCFC1D2ULL, 0x8FF54959EFDB85D2ULL, 0x8255BB25A02D6C78ULL, 
            0x82F2E26345337C4DULL, 0xAD425E31FA539D99ULL, 0x1DC26024FA51CA5FULL, 0x5628B243A5010B52ULL, 
            0x8F26DDFBA1E24E81ULL, 0xE2A7C7D9844A39F8ULL, 0xC5411E3F4BE3ED32ULL, 0x22EFA19752D1D247ULL, 
            0x356989D5DCF4F6FDULL, 0x24EA9CF0FBBD32D0ULL, 0xAEF559EE85036657ULL, 0x52F04421CC6A5F16ULL, 
            0x295E7175DA2E2D71ULL, 0x9214C5EA7DD0C451ULL, 0x0FF09264A555B56BULL, 0x837C20DC6C4E0EEFULL
        },
        {
            0x0389669AE4A25CD8ULL, 0x3703B49431EF77F4ULL, 0xDBFB35FA55831995ULL, 0x108EECA7597BA00BULL, 
            0x2C08B2B309F142E5ULL, 0x5B6E76764A86FC91ULL, 0xFD78867259DBD743ULL, 0x4E1DC96D13DD1347ULL, 
            0xA364E37436A99948ULL, 0xFE389B991F8A5AD0ULL, 0x943F7183992655D2ULL, 0x2BC81BA6CC2DC7A1ULL, 
            0x89566E5942B553F7ULL, 0x0C001A718A70B923ULL, 0xF53601CF7270B87BULL, 0x5BDE4F2D0AAEE400ULL, 
            0xE3A0C270DFEBDF42ULL, 0x95E2E20A0740FDAFULL, 0xFEAD66875C1B70E3ULL, 0x323F8B2B8BA91AC8ULL, 
            0xE48A34F4D1F4A18EULL, 0xB993424DF4913B78ULL, 0xB2D2754887141C52ULL, 0xED54DAD85BBAD842ULL, 
            0x4478A27C66E00504ULL, 0x1EEF6B4428BA2C92ULL, 0xAA66A710E220CAAAULL, 0x5272AE972E720F28ULL, 
            0x2D85370160B2384BULL, 0x46B9E9D49EE65C99ULL, 0x9E7297270517B22FULL, 0xA6109AD91B084F4EULL
        },
        {
            0x29BBD42285095ED7ULL, 0x312643BD4D99659BULL, 0xFACDF7F4D43C1A64ULL, 0x3D4EE66830764BC3ULL, 
            0x36DE6D79996CB4ABULL, 0xFAF205686A07AAB2ULL, 0xDCDCAC07400698E5ULL, 0xFB9AC84B75DFC6A0ULL, 
            0x66557B9AA368922BULL, 0x376A2C14511B985AULL, 0x0D84F5DAE82EFD24ULL, 0x219DF1615CD08805ULL, 
            0xF6392C2C144FDDADULL, 0x958E6FDBF5768AD0ULL, 0x4DB5612F7AFD5337ULL, 0x5A9D0957363561B9ULL, 
            0x7240652AD2383081ULL, 0xBA219B039EDC3606ULL, 0x62E4EB0F231CE7DDULL, 0xEF96630EE645064AULL, 
            0x6EF5E76DCE218D4FULL, 0x3986D268188EB18FULL, 0x73D68C7F528159A3ULL, 0x04317627FE21F713ULL, 
            0x1EAADF525F49C3A3ULL, 0x99BB7DAFC5F9B4DDULL, 0xEACFE23B97A542F5ULL, 0xD3902BFC98C4FDDAULL, 
            0x51F9F840DE4F2D0DULL, 0x438DD34B1AABD903ULL, 0x19684F6DB1D6CDEEULL, 0x63BCEF67E29EF789ULL
        }
    },
    {
        {
            0x37EC3D0F9EC9EC7CULL, 0xA3A61FB69999A41BULL, 0xF8E709B80EEAAED2ULL, 0x4EF28C63F42A0028ULL, 
            0x282FCD51A1B0CABAULL, 0x31934C7B68EFC360ULL, 0x1E56B07A6CD2478DULL, 0xC218E32C1152B421ULL, 
            0x864C7BAA247AF876ULL, 0x3C03302B2EEEFF10ULL, 0x7D962E9381BE3C53ULL, 0xAE4C5189D30BDCC2ULL, 
            0x732AAA08C0FA30C4ULL, 0x955578D5B4A5006DULL, 0x1698FDA87D25CCB9ULL, 0x7CACA9B499347FA8ULL, 
            0x57671DD101C7506BULL, 0x18BB58D6BAB5A0C2ULL, 0xD2796851F284D83CULL, 0x28B41E72087E2CB0ULL, 
            0xB49B82C2D983BC51ULL, 0x0E573E190B1A854AULL, 0x5FAED849BF8B19D4ULL, 0xE5018A4F037136C3ULL, 
            0x864063904AEA9C2DULL, 0x6537766EBD20E2B7ULL, 0xBC211C3A8FD34A68ULL, 0x582299DC50B7E784ULL, 
            0x48A15D0EA75A32DFULL, 0x98B7A93513E19E99ULL, 0x76471FFD7922A67AULL, 0x75E98A3BB79AF485ULL
        },
        {
            0xB8BA2AC5A0ED9B20ULL, 0xD9C4A79A89163361ULL, 0x143C08582F370E1AULL, 0x4DA8B98B26C4FA61ULL, 
            0xEE15EDCFDE1B3F36ULL, 0x1AFD2039F908352AULL, 0xD1B456691484B5A9ULL, 0x4E11E0828D8B9228ULL, 
            0x4A15906DC07D4A87ULL, 0xA45EAAB3976AB730ULL, 0xF3ECC4BAC7DBB6C2ULL, 0x0E99FFA0FF56A6B5ULL, 
            0x205905579D5669EFULL, 0xC74E505EBE4B4946ULL, 0xF3771E481779BBB6ULL, 0x15AEA36DE3A025B9ULL, 
            0xC74DFE68A52928DBULL, 0xA8E8AD0EADC5F6CFULL, 0x6F666C50840A7320ULL, 0xF002E6B9DF42F4EDULL, 
            0x8240D4A29B8BC27BULL, 0x2472500DCFD33B0AULL, 0x8ABC7EBF5B23CDD9ULL, 0x97B4F5B9E461F924ULL, 
            0x350F8B8322346DD6ULL, 0xB9A8C5DEB3FD48E5ULL, 0xD657C8967C26324BULL, 0x830CBD348F844A9CULL, 
            0x500405E4AB99D28AULL, 0x8446BE415FB16C2AULL, 0x2C7845935A682218ULL, 0x72A248CEAFF3B181ULL
        },
        {
            0x5CB170FB390E8B1CULL, 0x6EAE5DCD843C8E5BULL, 0xB48B8217AB360F70ULL, 0x7D6C9E5FF9B16B5AULL, 
            0xE83520D15E59FF72ULL, 0xB2C8A55C5BEDD01FULL, 0x2665959D90318630ULL, 0xFEE793ED034C4F11ULL, 
            0x7FE21B4B0C2AD24EULL, 0xBB708F2F40B4E324ULL, 0xF5F3374E9AF33CB7ULL, 0x535AEDC2DA607C6AULL, 
            0xC8AFF3EA3E28C528ULL, 0xBB61F8E596B2466FULL, 0x5B78F70638549468ULL, 0x658EDA1579C52D75ULL, 
            0x7C591706773C918EULL, 0x102EBF167D22BCAAULL, 0x0D6E2253E6F6842DULL, 0x207B1CF97D9A777EULL, 
            0xE9DCA4C1F85E30B4ULL, 0x3B7324E962B00EE1ULL, 0x5C633734B124BAFFULL, 0xC0B92A73D070708FULL, 
            0xC4ECA008EB1B7BD3ULL, 0x227155124A0CC42AULL, 0x407EA28C70277E86ULL, 0x96CB6CEE7568B490ULL, 
            0xBA53F53E24C80E0AULL, 0xE03B0BF38FD927D4ULL, 0x69CAF3CA5BB2BE87ULL, 0x94FBF7E6B518A2ECULL
        },
        {
            0x2E52C409FE06AD65ULL, 0xB543DDBB2E8716BDULL, 0x7539F9BE238228CBULL, 0xE4AD7CDAF1E044FCULL, 
            0x9ED9A51DE0A017A8ULL, 0x38D712B5C80F2DF1ULL, 0x1DB59836273A9C02ULL, 0xF19927329DB307FCULL, 
            0x9C4EA77194FCBBCDULL, 0x738CC7013D654B24ULL, 0x9B19EA64950698AEULL, 0x5B3E6EF3A05D9C3CULL, 
            0x2A91572227E91425ULL, 0xE61A9AFC1BC14549ULL, 0xD878CBCEB9F5934AULL, 0xEEE298FB0489358DULL, 
            0x04FBE65A6027349CULL, 0x266333C5B5A065B9ULL, 0xC7AFBAABC26F4FF5ULL, 0x1AEFB54B89615E37ULL, 
            0xDA9C4FD991212856ULL, 0x3342006C21F3B837ULL, 0x176F1F6083A37D18ULL, 0xEE16C9BDCE9B8597ULL, 
            0x917765E5C5B42EE3ULL, 0xEE69C7476A60F34FULL, 0x21597CCD6698390CULL, 0xEC948E4A25D911E0ULL, 
            0xD7373E2A396A2908ULL, 0x18B9CDF3A7C6240CULL, 0x23AEF90233C11279ULL, 0xAEE4C7B8250248DCULL
        },
        {
            0x4691C7B8A60E58E0ULL, 0xD13C6CDED6DCF2C9ULL, 0x28BAF86FAE8442F8ULL, 0x0594CD1733064647ULL, 
            0x4297A305FC8E41EFULL, 0x46AFF3F347946E6FULL, 0xF573AC5474F12DF4ULL, 0x5448A6A4CC2E774BULL, 
            0x7A8592ABAA563D18ULL, 0xE0415A357F475631ULL, 0x50137D2421AD2CACULL, 0x2F85AAEE2D7A4F82ULL, 
            0x4ED74418ECBEFC2DULL, 0x8E54A19D808B087DULL, 0xA0BEDC95183BEA66ULL, 0xCC40ABF233DB40F5ULL, 
            0xE1AF221951BB9578ULL, 0xA449B4BB6C0CB2C1ULL, 0x4A30D34F5DB6256AULL, 0x973675F8D68CABB4ULL, 
            0x7A5206ED3F7A040EULL, 0x49DB5AA7D98EEC54ULL, 0x3A343514B1EAE5CAULL, 0xED9D58C4F1DCC031ULL, 
            0xF65BC47B1F23E158ULL, 0x5E2FB7DF05698BE4ULL, 0x4A09362BC572BA40ULL, 0x4A0B76DE5D332739ULL, 
            0x06C7C7F6B3F05267ULL, 0x51C425DFD2328F0FULL, 0x41763EACD3AE7ECBULL, 0xAEBD121BED0752AFULL
        },
        {
            0x9CE81022BC17BED3ULL, 0x138CDF6E8BF66A6CULL, 0x7C61047FACA3B9EFULL, 0xB93B3193B83535D1ULL, 
            0x8F369CEEBB1F4BBCULL, 0xE254E7AE5ED2D2F5ULL, 0x8029EDC39D958C7DULL, 0x7998603E00E6B9F6ULL, 
            0xF76E7333DA419E82ULL, 0xF13C703702A678E6ULL, 0xD17DA38F02EAB862ULL, 0x77AE12024C8AF9B4ULL, 
            0xB95DCAC2D5E2449BULL, 0xC080A33F4B451FDDULL, 0x95AE8128A1E00335ULL, 0xF6B2AC1EFC028E57ULL, 
            0x87951492C3903CE2ULL, 0x989FAB0472E77245ULL, 0x61A3A78F7BFCF4F8ULL, 0xC4EF6DAE4EE62881ULL, 
            0x8C1E6B48F41B3C92ULL, 0x48E356E44BF779BDULL, 0x1623C2745007ACEDULL, 0x31E9390416523039ULL, 
            0x40EA8FB725F172EFULL, 0x3C05E4843ADC8771ULL, 0xB5E4D623AF289585ULL, 0x3595FEAE65B3EA6CULL, 
            0x2647DB72AAC30C0BULL, 0xE9224D3939FEA454ULL, 0xD2227E903EED78C1ULL, 0x577AF799E5581BA1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseBConstants = {
    0xF915F959CEFE9426ULL,
    0x6EA0FF0045421E08ULL,
    0x5C573D9CA63D972EULL,
    0xF915F959CEFE9426ULL,
    0x6EA0FF0045421E08ULL,
    0x5C573D9CA63D972EULL,
    0x8511FC331F09BD58ULL,
    0xCA451EDFD3AEC149ULL,
    0x9C,
    0x19,
    0x03,
    0x98,
    0xCD,
    0x22,
    0xDF,
    0x81
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseCSalts = {
    {
        {
            0x82BBA20CD6326B77ULL, 0xAA18E730F255B65AULL, 0x6FC4C8E1D496596CULL, 0x4C8FDEA2DEAA61A0ULL, 
            0x450B4DA9FA4A3FDBULL, 0x822696975069CA7BULL, 0xF2D3608CBE033B4FULL, 0x742113733845CB43ULL, 
            0xA39A06929E554CB5ULL, 0xD7AFC500E46871A3ULL, 0xD9A795192FC30073ULL, 0xC328B6BEF6647788ULL, 
            0xBC187307990355DBULL, 0xAC66C05D13A0587EULL, 0x11A6889C77141469ULL, 0xCC4713B06EFCAB97ULL, 
            0x0E800F0B968BD2D8ULL, 0xE844F1F1F31600C6ULL, 0x0E7B96CC3571AAFFULL, 0x98FADBD72AB95D4DULL, 
            0x1A2E1B201901AF3BULL, 0xA51AA5A37B7980FCULL, 0x52F1B9563ED8EA6DULL, 0xF4C849483D5977F2ULL, 
            0xDAC7AFF178930252ULL, 0x039B080651158853ULL, 0xB137028D63969A27ULL, 0x85924E3AD5FE9E88ULL, 
            0x8FD04ADDABDAE301ULL, 0xCF70026CCBDEEDD7ULL, 0x2DD17CD27BDDF3BAULL, 0x77C7BD3C159C72EFULL
        },
        {
            0x32BA469F7F541888ULL, 0x28FA977B44E28FD2ULL, 0xFA5916B77AF6D513ULL, 0x311001CC5CDE116AULL, 
            0x19906CB0E1E6F2B7ULL, 0x15C193BF4A0481B2ULL, 0x53C66AFDD0394463ULL, 0x36F17D09878B71DBULL, 
            0xD3C1184D265CEAD9ULL, 0x31DD0284C988E2DBULL, 0x8F69CE327A2AE6CBULL, 0x681C39DAAEF3A6A1ULL, 
            0xAC07CD050B79E715ULL, 0x09DA0F7CA62FC14AULL, 0xA9FFB64DA87E9313ULL, 0x7089CF57F109C40BULL, 
            0xF80B76FF9AD0FDE2ULL, 0x8F96EAAE46B4E0A4ULL, 0x84450B6EEAC23BC9ULL, 0xB46CEA142FFE5671ULL, 
            0x8AC748D0019C6673ULL, 0x5B42A28BC9C0E683ULL, 0xA27DA9F72C2B98F8ULL, 0xA3A3FC9B07F833A2ULL, 
            0x00C76A761E5872DFULL, 0x9B78F5370DFC2F8EULL, 0xEF75EAB3C1DFB593ULL, 0xF2D3A04D882040D9ULL, 
            0x51E6DAF9020D617EULL, 0x24353EF91FBE8124ULL, 0xE19578825C688BC6ULL, 0x4EE23729F413FE0CULL
        },
        {
            0x80837B96EE10D091ULL, 0x824732BC0F6E983DULL, 0xFE7565B0BF8E27D3ULL, 0x4B31340DC704BA18ULL, 
            0x76E03893CB14B2CEULL, 0x7367D2F8931DDF3DULL, 0x800403766DBA259BULL, 0xE9DCCC565E922869ULL, 
            0x609D81BA1901CC20ULL, 0xF280D2A95FE0DE0FULL, 0x30079843304587B7ULL, 0xDFABC02736334B5BULL, 
            0x1E95D23F4D95F7B6ULL, 0x956B4852A4974894ULL, 0xD674B92DB18FEC29ULL, 0xF1418D646F772EBCULL, 
            0x0ED77D47D34A637BULL, 0xA50B1F254F8BEEAFULL, 0x12283A2FEE90A07AULL, 0xB0FD27CC73D4E639ULL, 
            0x32C9320556681419ULL, 0xC6288FB5E726311FULL, 0x1F85383813532327ULL, 0x6D35B1D4EA0219EAULL, 
            0x5E37F921C8512EDDULL, 0x993A5D7A2E8A4372ULL, 0x76EF86FB8F5CE0BFULL, 0x26F71907C8B175B9ULL, 
            0x8B3489DDFA676F7CULL, 0x240AE01508A4F128ULL, 0x4385E30B5050CFE8ULL, 0x8C7A806F903EE500ULL
        },
        {
            0x86B4ED1614A1DA09ULL, 0x16385B8B0C092E31ULL, 0x6BCE3A488C0FB0D7ULL, 0x925CEE5CFFE884E0ULL, 
            0x9D62B6BFA68F5CBCULL, 0xA02E1150DDD17017ULL, 0xB7A170D6DA4A4238ULL, 0x12B8600B145665C6ULL, 
            0xBF4872208FAEDE46ULL, 0xAD7F05316E749A4CULL, 0x886DA3F206C0FCE1ULL, 0x16341546C239CCCBULL, 
            0x5E4083ED5063D7FEULL, 0x822A62A8BA878532ULL, 0x299955918E97DA82ULL, 0xEAEFC0D334DD4F06ULL, 
            0xCB2668B4AE0C3E49ULL, 0x075EF5E83ACE28ECULL, 0xFAD1C6933176C2F6ULL, 0xBAB6EB76244DEDC9ULL, 
            0x542A5EB7ACE30174ULL, 0x8A3C9447BA25BA4EULL, 0x073CA08DA386B1F8ULL, 0xB103097F1EDD8177ULL, 
            0x938C656C7769D46DULL, 0xEF9E146EC8541A07ULL, 0x1ECDA8C49468E53FULL, 0xC271A99B94C4CD73ULL, 
            0x3049CA44F2854194ULL, 0xFE6C1CE6A2245BEFULL, 0xC234AD8E5A12B5BEULL, 0xBBB5E33BDAEF72B3ULL
        },
        {
            0xC93565001BF764E8ULL, 0x1CCA323EDB719539ULL, 0xCF23F7B03FFA7DD1ULL, 0xD8B3790482DE6FFBULL, 
            0x11EC9CAEF4BDA35CULL, 0xF2A8D1962C8A1B7EULL, 0xB0BD2D72E25844C4ULL, 0x5FA51DE8B7F94F25ULL, 
            0x0606E95CC12D8FEDULL, 0xF48952243AEA004AULL, 0x3B6749986C0E051FULL, 0x6B31EDD09A146BBAULL, 
            0x6883B086D534F9B7ULL, 0xB834FD7429657C23ULL, 0x13C54202AF8CE966ULL, 0x9E047F2E6F84E162ULL, 
            0x1D9F2CDED31C7197ULL, 0xBB45B53C5725D326ULL, 0x41AA29210778B925ULL, 0xC0137993EBFD217DULL, 
            0x11F33B9F42552ED2ULL, 0xE3EEE934FA0739C2ULL, 0x6381905CBCC18C4AULL, 0xC3799500A4078A37ULL, 
            0x06BA8A0A776FC462ULL, 0x1D00669FD3B78D66ULL, 0x2A5F627773457465ULL, 0x5A98BB03772FC8DEULL, 
            0xA8FB8FE5EC60BE88ULL, 0xA50E989C54C0DBB8ULL, 0x3C4FBE24A7B49C51ULL, 0x3593A6C8048F9E3EULL
        },
        {
            0x5BEB32FCC18571C8ULL, 0xA8793854540E7217ULL, 0xC899390FB4DF0B56ULL, 0x570EB9AF5DB4ED18ULL, 
            0x103C8BEF31C86596ULL, 0x9F1935F361F93DC4ULL, 0x70220C3079D617F6ULL, 0x7684F04BEDF5E2B0ULL, 
            0x59477164D7F665E2ULL, 0xBF15939EC011C648ULL, 0xE2A0123DBD083A76ULL, 0x38BBFDD1C8162592ULL, 
            0xAE09EEE9477D112CULL, 0xD4B076D363F07504ULL, 0xC7ABC0577E5E5496ULL, 0x4968B5A1B80B69F7ULL, 
            0xC1E843C8AA03D056ULL, 0xC7A5129FD53C1DEDULL, 0x3824B38046078FF2ULL, 0x16BC8608AD262234ULL, 
            0xBD0DC7F08E99B16BULL, 0xCF9A796B44E0A52EULL, 0x879C4AC26008109AULL, 0xF5DE84DC63B39E66ULL, 
            0x498420A89AC62637ULL, 0xB2CBC33C6550677BULL, 0xFE21D944E26F3CA6ULL, 0xD78DA544643BF4EDULL, 
            0xA9E1CE5F3C2D4330ULL, 0x9BE0FDF900B33C14ULL, 0x523F21449BD53678ULL, 0x3E2C7EC864383302ULL
        }
    },
    {
        {
            0xE7492E1B78CA94F9ULL, 0x95710077B36970A4ULL, 0xF9FB60B68AEE19F1ULL, 0x0C2F7E36C9D97A6EULL, 
            0x033764467689BBB8ULL, 0x1F261F252828ECCAULL, 0x8C329DA0C159603EULL, 0xE0182B822751541DULL, 
            0x6C6FAE43C9E6CBC1ULL, 0x8852233DCD2362DEULL, 0xDFF42754E19C6EB2ULL, 0x1F4E6AF1144DC760ULL, 
            0x4ED0678AD1EA7F2DULL, 0xFFAE7BA82BDC6E7DULL, 0x551F20DA8E07E04FULL, 0x886FC64D300D2511ULL, 
            0x8C1AE0444BD05720ULL, 0xBDD58FC3134ED3ABULL, 0x0591C422044AFEF8ULL, 0x9FD3FBACAAB560F0ULL, 
            0x7ABA1FBC151A0271ULL, 0x2CFD84FE4E642544ULL, 0x3A895C45433CBA8BULL, 0x627418B0F4B1AFC4ULL, 
            0x87A1A38392DA6054ULL, 0xF77969B185E1A809ULL, 0x8A335BB950387E09ULL, 0x4C9CFB31F89BED83ULL, 
            0x6744496FEFD7E90EULL, 0x48E410E44074CB0DULL, 0x4F797A4EBF219C29ULL, 0x1977208B34B829CBULL
        },
        {
            0xFB4358B661F8EE5FULL, 0xDDD346DECD3BED97ULL, 0xEB6D24EB47FD7D74ULL, 0xA87C32916E508C79ULL, 
            0xD345F592DA4449ADULL, 0x58CDB2631CB0ABACULL, 0x086BFC86847A340BULL, 0xF463450E2D51B10FULL, 
            0xEE3348429BF51C09ULL, 0x55CED81085BE3C34ULL, 0x0B31C48586762B37ULL, 0x2930F17B31801239ULL, 
            0xB1E3E6764ADF296FULL, 0xB55F6811436ED52AULL, 0xDB46F952BEE865F3ULL, 0xEB356CE2AB7D1C69ULL, 
            0x4011E841B426FA7FULL, 0x7D04B579D44CF151ULL, 0x9C1C897DE5B3934AULL, 0x1A390767A7A3BA12ULL, 
            0x7D804CB7D66A0B41ULL, 0x966B0B5FA3A04EC5ULL, 0xF5B9BB1E1DF1285DULL, 0x56135C260C161DA7ULL, 
            0x1D3BF9A00B4D5104ULL, 0x62B72333D1E40552ULL, 0x48876EE8A52C134FULL, 0xCDCC37F0C42134C3ULL, 
            0xE97BB4E9DDABF596ULL, 0xBFF809E5497B9C6DULL, 0x79EAC883D9B03D37ULL, 0x13132F58B4E71370ULL
        },
        {
            0xBE118F6FCDFB1CE1ULL, 0xD90DCC325CF6F2A0ULL, 0x141979BEB4D90714ULL, 0x5920CB9763C8E58CULL, 
            0x9B0B245BA171B632ULL, 0x7E58D85440AB1320ULL, 0xA74EA9FF57EBD7DDULL, 0x5441DB28D842D81AULL, 
            0xDE54CB9E4E843892ULL, 0x203D9364B787B228ULL, 0xA676DE012C327193ULL, 0x130C2B9C1E412A9FULL, 
            0xB5FA35CD15CB9024ULL, 0xEBE946DB639F4C5FULL, 0x8A67F8292C706E8FULL, 0xD024D830103AD4C2ULL, 
            0x2626F0E77C4D83F4ULL, 0x7CFA0B1EC3CF78B9ULL, 0x958399FFFA76A742ULL, 0x7AE8995DE76BFE48ULL, 
            0xE7AA57F022E3535CULL, 0xD1E9005B22939C19ULL, 0xBD17A631C7DD2ED5ULL, 0xD0E0731AA07E9B9EULL, 
            0xA018C6F75E715FFCULL, 0x732FC44DAA396FE7ULL, 0xACAC9AC66D603C57ULL, 0xF971EB1598C50F7BULL, 
            0xC8B298206626B828ULL, 0x10274A236712A924ULL, 0x9F91685DCBEFA234ULL, 0x405EC71EB968D0E5ULL
        },
        {
            0xCFBD65343177B95AULL, 0x08BE47C7FC589D8AULL, 0x79FBE99A36AD23DDULL, 0xCEDDB91E43A2E24FULL, 
            0x3920CF0E2530577FULL, 0x7D6F94DBCE010E68ULL, 0x69180EDBC50F8602ULL, 0x81E3C3C55D8062B3ULL, 
            0x452B64DD54FE0490ULL, 0x7C6E531DD53AFA7BULL, 0xBFF7832BF53E4AC3ULL, 0x338D46B9D9062FFCULL, 
            0x1A9306A1FDFFC9B4ULL, 0x345E70A8015848E0ULL, 0x3664F6496421DFE0ULL, 0xC96C95AA52B2E359ULL, 
            0x26A2368433A91660ULL, 0xFA2695D5428F489AULL, 0xB5EC5ECA1ABB01EAULL, 0xA95A40C6CE95ACB8ULL, 
            0xB32C2C22DC384823ULL, 0x6FA512111FF8C3FCULL, 0x5415F22E3C6CF9E1ULL, 0xA7174B1E5D9E22AEULL, 
            0x91539EE9C50BCB53ULL, 0xE14067199AC9B1C7ULL, 0xBAE0E8A31AA2FE24ULL, 0x355B2B0DC298D9A4ULL, 
            0x42FE5748C8274EC4ULL, 0xFC8E9AB60E8FE3F8ULL, 0x5B390957EA18B52DULL, 0x366CBDAC12EA7778ULL
        },
        {
            0x625C88328D36188FULL, 0xA15DA0385946A178ULL, 0x6323428A1428F03CULL, 0x83735844B65DB6A1ULL, 
            0x16965DBADE0573F1ULL, 0xC3682DCFB86F53DDULL, 0x0716F22F1E61121EULL, 0x9BFE7F59A44AF53CULL, 
            0x1F01A39BDCB2044BULL, 0x85A4D4ACF646C517ULL, 0x0050EDF562519A5AULL, 0x456CE846950A9879ULL, 
            0x2A17CE96FB356A14ULL, 0xF965B4403163C94CULL, 0xC55A246F51C3C519ULL, 0x5EA2D1B584F3B3B8ULL, 
            0x8B23F6078CB76370ULL, 0x18243840BDB12037ULL, 0xBF9FA2292746237AULL, 0x514B00823117ED64ULL, 
            0x9618871E8C9C26F3ULL, 0xDB74EDA4BA8D93C4ULL, 0x4778291ADB7E39C9ULL, 0x8A47556F66EB9B62ULL, 
            0x0E4595070ACF253EULL, 0x1F8F3AB1D146DE95ULL, 0xF47A170A41C79A29ULL, 0x97F948D90FB29954ULL, 
            0x01F5F8683DCC14EBULL, 0xEDD0E27C4AAAB53AULL, 0xC1D3C093C2B37B3FULL, 0x355107CCDA5F76E9ULL
        },
        {
            0xC9DBCA623ADAADBDULL, 0xCEDB4CCF7107ABC9ULL, 0x8B13B6481AAD8438ULL, 0x386AF7170F2AD4E0ULL, 
            0xED15C99489548B4FULL, 0x1FA1E28505AE5C99ULL, 0x615CC335061A5DBAULL, 0xA39FBFA9840CF8A6ULL, 
            0x69E92E79F788F4FEULL, 0x7123EC659927681CULL, 0x61A65CA9D012DAF8ULL, 0x303A8D3729BE4A40ULL, 
            0xEC3B09D3E68D1FFBULL, 0xFDCC7AF6167965B7ULL, 0xC4797CF2C3B94078ULL, 0x0AEA07C794E45493ULL, 
            0x95224AA5EE064CC1ULL, 0xEB8211C8199F0698ULL, 0xCD30A7C44F8188F9ULL, 0xF3401EDA5477B7E4ULL, 
            0xDFF06E051908A335ULL, 0x931A71CEF4ED3970ULL, 0x37D4D040FCAE368AULL, 0x32C69F6813B28E85ULL, 
            0xB750383A2DCDD2E5ULL, 0x71BFF10A06948E2FULL, 0x15FC9BA261B552BBULL, 0x09E82D736AE65067ULL, 
            0x29F8E3FE93CFF9B1ULL, 0xD46702DA9EC13177ULL, 0x3A711E3086EEBE15ULL, 0x10F201E2BEBE1B60ULL
        }
    },
    {
        {
            0x918DA835A4BA21A6ULL, 0xF7790C0EC732ED7FULL, 0x01CA9CDE3E6752C8ULL, 0x0513ED2EC754E3D5ULL, 
            0x7CD28BA31A39352EULL, 0xF2E789D023E55F3AULL, 0xE9D5BED959428861ULL, 0x1481B645D8C07D6EULL, 
            0xC1434D3AFC5CA0DFULL, 0x2AAD363503DE8D68ULL, 0x42E727B53F0D6347ULL, 0x20708057A77C85D9ULL, 
            0x394B65D3F71B2D31ULL, 0xE238FF95068C418CULL, 0x04F9AF2943062258ULL, 0x457243424B474E55ULL, 
            0x3E41FAA50CEA4C39ULL, 0xA64ECA79272FAD93ULL, 0x1458A6874275EF64ULL, 0x756A1A5115017BB4ULL, 
            0xF052B56074AD4352ULL, 0x4983A201177B1246ULL, 0x2883DFA814A5F4C4ULL, 0xE8E456C666D6E945ULL, 
            0xA74A1070BF70C8A3ULL, 0x19134D85620615E3ULL, 0xAD32685A0CEE893AULL, 0x9CC2C2D4BD2C8677ULL, 
            0x4EAD240497BB2C40ULL, 0x8CBB957867B9805EULL, 0xE97FC49B700D06F8ULL, 0xE7A998122D35914BULL
        },
        {
            0x268D861E833CF7ADULL, 0xA523F6FE91A70565ULL, 0xBC287BF72807F733ULL, 0x39017D54875C7271ULL, 
            0x6BA86C2561964A57ULL, 0x9CC0CC79CF4CE85FULL, 0x17DD2D03164440A2ULL, 0xD48195609F3E2EB1ULL, 
            0x76C071D925E93FB2ULL, 0x7D2945246698EE0EULL, 0x11344DA7F30A5C2FULL, 0x4CE4687C68CBB2FAULL, 
            0xB4C22DC8C82EE2E8ULL, 0x13E89FF05E5D6E1AULL, 0x19E856650D1C2208ULL, 0xF3C3C9AC2BC22DD3ULL, 
            0xA65674B14934E230ULL, 0x6188E1678F9145ADULL, 0x60F11F4F35016C3AULL, 0x16F67A553ACE5121ULL, 
            0x5EB7F183C638E829ULL, 0xAA76CE968C717358ULL, 0x6F339D6E83D007FBULL, 0x61E115AD6ACCC43BULL, 
            0x70D0D40CFBDE47CAULL, 0x73CAD315E785E6A8ULL, 0x4DEE5B7538B43907ULL, 0xD5AD508A748EBCF1ULL, 
            0xA53C68C9C020A096ULL, 0x10D2F120E81F3A00ULL, 0xADACA98AB5E1ECE9ULL, 0xBA02BADF994D27A6ULL
        },
        {
            0x3886BAA6105F3673ULL, 0xCFD6DE0D48417AB5ULL, 0xC7705656DF3CB4A8ULL, 0x73CD2A76E6AC80C4ULL, 
            0x0157D9D834C3EC96ULL, 0xFABA4B13445CDDEDULL, 0x3247EB93B667C8E2ULL, 0x0F4D2D5B331071ABULL, 
            0x617AC290C0AD0B06ULL, 0xE6D1697BC509596BULL, 0x4A7F9B0F0DCED997ULL, 0xBB92CB995AE43038ULL, 
            0x679B579DECF7EAF6ULL, 0x9E73AF55464BEEBFULL, 0x64E5E0495270411FULL, 0x9907D0F55E4A764BULL, 
            0x4BDE2CD89D37180FULL, 0x62D1F944E42207D3ULL, 0xCE49C9960C10B5F2ULL, 0x22E3A4CE125AA678ULL, 
            0x6F53EA552CF2C35EULL, 0x71E7CD96F24C0404ULL, 0xC50A4D354F0CC7D7ULL, 0x4587D57E2DEF41E6ULL, 
            0xDBD5D330BAC64963ULL, 0xF550875B62F956DEULL, 0x13AC0C508C85EAEBULL, 0x67F3BCE9A7ABC011ULL, 
            0x5D4BFFEF169CC0C7ULL, 0x1D1FDE7625973CEFULL, 0xEBF12E94CC36B78AULL, 0x998FD7437BE7D050ULL
        },
        {
            0x7234E3CF6EFF13E7ULL, 0xC09098AE61187203ULL, 0x8B67CD63D400196CULL, 0x6486D70692EA0488ULL, 
            0x56293E76C9282812ULL, 0xA5BFE90E77C5040DULL, 0xD03D5DF31A7AD5B3ULL, 0x7C2F7EA4646D790CULL, 
            0x17C4F52F3D10FF20ULL, 0xE7ACE99F9E8DA282ULL, 0xE9B9C9D0481C3D2DULL, 0x43FBEA6EA50E12B8ULL, 
            0x8B3054776454BF01ULL, 0x44E9A9B8FD8FF4EDULL, 0xDA3B41C78D1D3EF5ULL, 0xFA5AE9F7BC698722ULL, 
            0x98BE998C5E6EC195ULL, 0x28CDC672A63D3B73ULL, 0x3C80FB2CB50A1347ULL, 0x1AB226809F27FCB7ULL, 
            0x1BE980657DF237B2ULL, 0xF1061ACE181B042DULL, 0xAE828F7DDFE788E5ULL, 0xFF760EEDC1608030ULL, 
            0x18484ECCDBDD9401ULL, 0x9C4F50EC0000DF80ULL, 0x69D362E40B323CBEULL, 0x8BE31F6AAE1780AFULL, 
            0x1E02653012CA3A6EULL, 0x9E430E97448299E8ULL, 0x067A24C566EF4052ULL, 0x8B4B81FD004138A4ULL
        },
        {
            0xC71FEAF6F60A465EULL, 0x12072B37613A467BULL, 0xFE49FF2EA59B3BEBULL, 0x63656BF8C8F56C96ULL, 
            0x4300957ED1AD5023ULL, 0x789BFCD0ADBD2629ULL, 0x6C6168A9DC0D2A13ULL, 0xF07DCE9776A147A1ULL, 
            0xAD78F5D5470E401DULL, 0x3C5B71027E1E669EULL, 0xFC8FE888671F0D43ULL, 0xA10785FBBB72410AULL, 
            0x2C8A1CC6AC26E996ULL, 0xEF5BA07CFEFE78D4ULL, 0x1849AD5D5DB96BCBULL, 0xAF5E51866D7EF65EULL, 
            0x691856057EA965F0ULL, 0x390685CFED9DE4C2ULL, 0x4F2E7C3735DD2A90ULL, 0xC8378574E57171B3ULL, 
            0xD0612493C2BFEC23ULL, 0x7D4489CDC5CA7419ULL, 0xBD2FD88010B2D3AAULL, 0xB553DE1415BA4EB0ULL, 
            0xC48477A9BED9CA07ULL, 0x268F453F1A38E88DULL, 0x39BBAC8A1BBCD41AULL, 0x07F32267B5A9244EULL, 
            0x4759F195CE941F77ULL, 0x48D5A6917917193CULL, 0xBCC441DBB6C62505ULL, 0x5228B8B03A572661ULL
        },
        {
            0x4835C1570700A5FAULL, 0x130BA7386DE9689DULL, 0x2A533971BB56967AULL, 0x2957922AD76DFC5FULL, 
            0x4B2137BD918F3C77ULL, 0x8C1EB972003D2CF9ULL, 0x113E0B69876A5DCCULL, 0x77B7F04850A35510ULL, 
            0xD874C871E74FD714ULL, 0xDD1A195EB0309E9CULL, 0x250AEEF79AA80E2BULL, 0x24202F56E8FE66FEULL, 
            0x78AFFB8BB034B9FCULL, 0xBC5D8AEB7F640E07ULL, 0x69B1E674485ADEEDULL, 0x6CC6A99C76486BC1ULL, 
            0x3E1F5F579E23367FULL, 0x669E8C0AD8F44D55ULL, 0x2E8877FBF95760AAULL, 0x2DC8542C703E162FULL, 
            0x83F22FCF4EB46386ULL, 0xB588B4A1BCA24F0AULL, 0xA75C66BCCD0775F3ULL, 0x6DB22740E10F9CE9ULL, 
            0x2A519636CCC1825EULL, 0xA8EC0F9488092B9DULL, 0x031708F5FF4513BCULL, 0x5BF59662E13F0A6FULL, 
            0x6E3A381A82F0A13EULL, 0x74020D4FAEFF3DD5ULL, 0x0FED3163EA5A5686ULL, 0x7FC62A57377AAA01ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseCConstants = {
    0xB02D983A0391D097ULL,
    0x0ADCFB109207E0E8ULL,
    0x1C71D9F9114BECA6ULL,
    0xB02D983A0391D097ULL,
    0x0ADCFB109207E0E8ULL,
    0x1C71D9F9114BECA6ULL,
    0x1578903041E96DF1ULL,
    0xE880CDD9CBE11DD7ULL,
    0xC3,
    0xBE,
    0x32,
    0x8F,
    0x32,
    0x69,
    0xD2,
    0x7D
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseDSalts = {
    {
        {
            0xEE565B9F7430C5A5ULL, 0x772FF681F22FF55BULL, 0x04D0184A9696B70BULL, 0xC98F59A36AF6BE6EULL, 
            0xF2A675867F84602FULL, 0xC7C3BED98E16013BULL, 0xF1CDE20DEEA09AEBULL, 0x5C16125B45492058ULL, 
            0x763B4D8A4A909A8AULL, 0xD58B56789B16E8E4ULL, 0xE4CF8355C837412DULL, 0x4FDE080E81EE1F66ULL, 
            0xBAE0721E6C5EC9B8ULL, 0x6B8C724AFD467726ULL, 0x6D2E0033AB20333AULL, 0xB3D26B61102EE9C1ULL, 
            0x47F2CEC09268F21DULL, 0x18575B83BD4C1B92ULL, 0x6B022CEF110A7CFDULL, 0x2DD7F58A59220625ULL, 
            0xD5B21E7B60296382ULL, 0x84B97F3CF2BA892EULL, 0x1E9102E52992FB4FULL, 0x29BB1546E854D9B0ULL, 
            0x1AFE9E7E897D2867ULL, 0x97D689A5C2F00D73ULL, 0xCED0B2A2B6BAAB3FULL, 0x70745FA48AE8E369ULL, 
            0x71E5CF6B0F6B9235ULL, 0xBF6E706FA7D62465ULL, 0x2920C3CB0847698BULL, 0x534E63A8BADBF508ULL
        },
        {
            0x21022DF710294232ULL, 0x878601A929CE3EECULL, 0xF1D1B39EFBF12226ULL, 0x6563BE5DDE7E421AULL, 
            0x6127DF652B9F57E4ULL, 0x75D1F5876497BBF8ULL, 0x9867C1428E79252FULL, 0xEA4425640B925445ULL, 
            0x1963D55E878714A4ULL, 0x3152D12218DBC6A7ULL, 0xBF602E86F1666C74ULL, 0x0E5E3AFCF9509B8EULL, 
            0xD014E48967417CE0ULL, 0xAF4291477480F5E7ULL, 0x078168594518E610ULL, 0x3CF89A2021335131ULL, 
            0xF4DAA53AB79065D1ULL, 0xD223585F6D296668ULL, 0xBF7AE2CC4CEEAF6BULL, 0x161BD34E4A56F620ULL, 
            0xC164044C314F3BA7ULL, 0xC8ED51CF539B6871ULL, 0x1FAAA2EB4F9E8BA5ULL, 0x6DE0EDEE1ED37BE1ULL, 
            0x891BC4E3778164A1ULL, 0xA1F0C8CF697EB4F6ULL, 0x50777D337F37299FULL, 0xDB14F505AE441E71ULL, 
            0x7DD75D0F2F5A66CCULL, 0x99E4565808877CF9ULL, 0x6849D2DF57D7110EULL, 0x4C7EE958EF2BC3F0ULL
        },
        {
            0xBD65AA61E9AB272AULL, 0x46E565FDB5E688C1ULL, 0xA4A8D1A276050E2AULL, 0xCC8ACE1BF43457A1ULL, 
            0xB042988A40DB2CEFULL, 0x40B0A84B403E40FBULL, 0x97909BF9ED9C790BULL, 0x11248756D9FBC6AFULL, 
            0x70FB6E112B8FDED4ULL, 0x178E078283160CE2ULL, 0x6C329FAE710B5312ULL, 0xBA85939C8008ED12ULL, 
            0xAB066E0A5A4FB6D8ULL, 0x6B6869507A5C26E9ULL, 0xD291F2950C6FCF65ULL, 0x408EE0FA16DFFF2CULL, 
            0xBB48F0F0D61C52C1ULL, 0x9865C30CC24761E0ULL, 0x3AD66C7342802913ULL, 0xABA4AC9FD5F5F01EULL, 
            0x74434DFC02585E99ULL, 0x1C1F93ABD20EFE1FULL, 0x8B27E815312C7106ULL, 0x5D78F608BF8FF868ULL, 
            0x75200118D1B1E663ULL, 0xBB4FE7323F35AE6DULL, 0x80C1377EB5612ED7ULL, 0x7042BC74C9C183FEULL, 
            0x75596EA84BE203B4ULL, 0x976FF417CD778D86ULL, 0x4CF43A3866DC0D7DULL, 0x0951BEB90B2F4E0CULL
        },
        {
            0xAD863489A93F93C4ULL, 0xB35B3A4AF8C92A83ULL, 0xC3E6CEA6D452775CULL, 0x7EAA5038F7264B08ULL, 
            0xD8F8B6E6B094EDCEULL, 0x2EB954A50C096431ULL, 0x274FC88F0583CE4BULL, 0xC748046121FB36BEULL, 
            0x372CC3C102A297DAULL, 0x1D8735A2FE2C73E9ULL, 0x0AB1DF51DCC840D2ULL, 0x982F77A533FD6052ULL, 
            0xA11A2F15B909A7E9ULL, 0xB95CB33C702AEB72ULL, 0x7774B699497158CCULL, 0x2DCBCE5E8FA4225CULL, 
            0xD39BFB3F823CE7EDULL, 0xC73C5917970FBB10ULL, 0x4FBBD0D7EC5EC607ULL, 0xC0C24A42E33C38DAULL, 
            0x6E7E47D729B0B789ULL, 0x58C9476671D7A928ULL, 0x163AC4AC3F7C53D4ULL, 0xCBF66E50FBAA6EABULL, 
            0x2D7AFD93A7B45A50ULL, 0x9D5D9AE49C449F1DULL, 0x88C760F85BB90066ULL, 0x32537230986D05D0ULL, 
            0xDEDDEAB8CEA21F5EULL, 0x7DB196B69A0C6AB3ULL, 0x8AEFC16E8674C9FEULL, 0x6C2350BEB5F9AD25ULL
        },
        {
            0x2C68A195ED1FFB81ULL, 0x1CCFA99592B42D9CULL, 0xE0525ACBDC45D268ULL, 0x4487021212AB494DULL, 
            0xA8379EE548D5ABE2ULL, 0xECE1544AA2194665ULL, 0xE01A8D89AEACAF38ULL, 0x769225F620B22899ULL, 
            0x0182BD27CE0C4184ULL, 0x7170AFAA0DE8A263ULL, 0xE93F44778FB6FA33ULL, 0x1996DE036E3ABC02ULL, 
            0x680EE09B867C05DBULL, 0x8A0CC560C0991141ULL, 0xB419600CA8A268CCULL, 0x0CBB1985B550CECAULL, 
            0xC991F657108EBAFCULL, 0x390912EA898C9C8FULL, 0xF206D2864939FE7CULL, 0x9FA7FA3613C7E294ULL, 
            0x6B9BE1E3AD2673B4ULL, 0x23F24909ED7DB985ULL, 0x7C48F651248B2342ULL, 0x2684CFFC1277F7E4ULL, 
            0xCBDF63C55BECC411ULL, 0xA4ED8B4AAAED32BFULL, 0x4423D97648535761ULL, 0x71E1112D95A906B1ULL, 
            0x39B3032B40D94AA8ULL, 0x9D1E40ACA85C460CULL, 0x2D99D044125E8207ULL, 0xAE4789B2329EC81FULL
        },
        {
            0xE760B4375EC5FE4CULL, 0x575DBB301BD6F075ULL, 0x11643F46C8E4067AULL, 0x1B6715A9B82038B9ULL, 
            0x6764B7065ECBFBB0ULL, 0x67A19AB33261679FULL, 0x3737278493CA91C4ULL, 0x29BD01AE0C171B6CULL, 
            0x23DD49483F0891D0ULL, 0xF7F3E80B59DCD220ULL, 0x78C577BECBE52DD1ULL, 0x8377983D9FFC2CCAULL, 
            0x133946C2598A7A1BULL, 0x3DF4E5A855166ED0ULL, 0x571AC8AA5F2F62C6ULL, 0x069C2C1546DD1210ULL, 
            0x19C292668683C623ULL, 0x77DC02CD29FEBBB3ULL, 0x1EC1599E867C42B1ULL, 0x54584F7F7159151DULL, 
            0xC83BC85BDE3B88E1ULL, 0x7A8D126BA6131F8BULL, 0xD3B881CA49E4C44DULL, 0x5C5E0773433982EDULL, 
            0xFD346012BB40B303ULL, 0xCDC2200BE3C19249ULL, 0xBBDE4852C83EA992ULL, 0x1B1DF707C685E7B3ULL, 
            0x5A7CA84AF49026F3ULL, 0x00F044521E2063C0ULL, 0xFC8D7F32F4CFAFF8ULL, 0x70A2745A40518CD8ULL
        }
    },
    {
        {
            0xB868CC3FB7D304BDULL, 0xBFDB8E6AA37E2FD1ULL, 0xCB60B5E142758FBDULL, 0x012D4AC71443FD62ULL, 
            0x8BB7C2A92BD8555BULL, 0x75E8FA97FC97B367ULL, 0x06259CB0595E110BULL, 0x56985FF730A3FB4BULL, 
            0xDFC9C309D7D1D8EBULL, 0x5385B7EB5A00382AULL, 0x54FE4B2F503E4672ULL, 0x1B51B908CC73A611ULL, 
            0x277E4927002931DAULL, 0x81887496F05D06D6ULL, 0x677FDC06F48145D0ULL, 0x6BF266F6F85C2E87ULL, 
            0x9F4D8549BA1B53D3ULL, 0x04DB46CBE5D763A6ULL, 0x42931EFCC0C1B692ULL, 0x45C3F3387954DDC9ULL, 
            0x7DA3D7EE70D1F2E8ULL, 0x6D8071ABE1DAF667ULL, 0xA507F557A6AB9089ULL, 0x3B857249DF23D829ULL, 
            0xE1230EF2C3E32A4AULL, 0x9CA245F7A327AB15ULL, 0x2B2C9503B29B567BULL, 0xADCC696BEF4CE6B8ULL, 
            0xE3753D983523F334ULL, 0xC63FF7EDEADC28BAULL, 0x4BBD656F788C2412ULL, 0x193A806A56E2A769ULL
        },
        {
            0x321CE4A3B017D60CULL, 0xBCB7DF3C1B8F9BD1ULL, 0xC6A784DB37F86A6CULL, 0x8A0E1FF8B7BBA36DULL, 
            0x25521B9055D74A8FULL, 0xEEF1F05AE2F25331ULL, 0xCE1A431F380DAFFFULL, 0x49B26902B53646ACULL, 
            0x9187E1BB269D6659ULL, 0xD6EF2E205372803BULL, 0x49041AD682582108ULL, 0xFD7F67E6B8F9102BULL, 
            0x52BCB48A317C1CB5ULL, 0x0755922D2D2D6226ULL, 0xB9DCA99614838EF3ULL, 0xBDF9A8A871433294ULL, 
            0xFA02BE6CD113945BULL, 0x3B9E58D55BF98EABULL, 0x7C0CE730388E4352ULL, 0x3B0C70F445852527ULL, 
            0xD51924DDDE7519E6ULL, 0xB81CF0DDAD0E2FD9ULL, 0xBB07C6E04938D8C3ULL, 0x5662F7CA6CBD0105ULL, 
            0x65F1AF680C9C008FULL, 0xE299F6223AFC848CULL, 0x1A7313D744BF4452ULL, 0x9BFAE1D895D8C871ULL, 
            0x708240554E5AF1F6ULL, 0x346FFC788DB20D5DULL, 0x70E4BCF099FA1937ULL, 0xCF922AC6DFE3CE45ULL
        },
        {
            0xF91DA8F633D90AC9ULL, 0x102895E7AD112ECCULL, 0xA23E68754208B317ULL, 0x894F2BC090E2FB7DULL, 
            0x3B653415098BA170ULL, 0x04BA7681510C5BCBULL, 0x8B892489C5CAF5F0ULL, 0x82AC22D661CF860CULL, 
            0xB318449541F286C1ULL, 0x37D0277A3406DE29ULL, 0x0D63DD856B5548BBULL, 0xFEA7D3A3DA2E9E71ULL, 
            0x8F76962652D7E466ULL, 0x49A61B7972F8586FULL, 0x704683FF3CB02A62ULL, 0x4255B254FE462017ULL, 
            0x61CFA9F4B7827EC5ULL, 0x98A914A512DB01A4ULL, 0x773BC131889F7895ULL, 0x6B889DB56C304185ULL, 
            0x9F7C1AD4B99993B7ULL, 0xB0EA77D921439898ULL, 0x19542FC69661DF4CULL, 0xD2345E0C36663A0FULL, 
            0xF6B365A601E60823ULL, 0x275D4817F4DED78EULL, 0x8A5AC3F36F87E12CULL, 0x9207320EE74FB6BBULL, 
            0x81850A59142C7C2DULL, 0x3F40B0253F7F4456ULL, 0x39EF8A51DD084DFCULL, 0x1C5C4B69F54AAAE0ULL
        },
        {
            0x2220197FCD692968ULL, 0x1920FD96C957EF1EULL, 0x6795F9635EB09206ULL, 0x9B7E327550D82D49ULL, 
            0x4DE904EF4475AC84ULL, 0x26722378A06CB3A9ULL, 0xC1FC426A5439F618ULL, 0x78C498DB29F3AF0CULL, 
            0xD7B5B4487D2D876DULL, 0x7D78A02088B6EDF0ULL, 0xD95AF3AF13EA6B7FULL, 0xE4CEEB2FEDA7F402ULL, 
            0x2076CD3875FB4114ULL, 0x7B5F27303ACACE02ULL, 0xD2DDAF6BA35F51E9ULL, 0x4745814BAC7EF82AULL, 
            0x8E94648AEDF8556EULL, 0x770AE9ECD701E010ULL, 0xC591D8F7632CD3C3ULL, 0xC64E013E993DA52EULL, 
            0xF8D5ADDE7312598FULL, 0xE98452CD18AB103EULL, 0xD5E2A467F4602AA9ULL, 0x5473DFB328B299CBULL, 
            0xCED89B7CF95E04DCULL, 0x4885792CD07445AEULL, 0x95542B502A75D3EBULL, 0xA64275A8283B0C17ULL, 
            0xD5CC4CD11E73EC6FULL, 0xACE472FEDF5DBED8ULL, 0xF927AF754B79045EULL, 0x7EA74F7A8386FF86ULL
        },
        {
            0xA1AC606EC404A2CBULL, 0x60CE61236ABCCB82ULL, 0x58F77A76FAE443A7ULL, 0x0EA3FBC9F773EBD6ULL, 
            0x3FCD201ADE929207ULL, 0xD98466141C17A273ULL, 0xCFAE64EB9024FD32ULL, 0x887D82EC6B600D95ULL, 
            0xF24CC16B04D1D590ULL, 0xB57C9A6F5D7822AAULL, 0x2DF634E5C6F00C00ULL, 0xBBB145CC7BDA9D42ULL, 
            0xC8203B809FC2A86FULL, 0x0273D8AE85B59BDEULL, 0x48BBB1EFB84F93E8ULL, 0x97DFA734E4AB5842ULL, 
            0xEF8BFE6CA25CE4E7ULL, 0x8687F0B3C2935060ULL, 0xC8F6D59CF7DE8D53ULL, 0x6D852AB085D0F7ECULL, 
            0xB21DE4D38641A882ULL, 0x57B8E011697EEC6FULL, 0x4102E149580BC572ULL, 0x6962D171586123C5ULL, 
            0x283C9784DEE95E28ULL, 0x88A5AF00C0763373ULL, 0x888FC528975AD46AULL, 0x2DDC260758B74F37ULL, 
            0xC3ECFF1C15A73119ULL, 0xBA14F0C8E0E3F8D8ULL, 0xEC845E4B3E988D6AULL, 0xF02CEE641767A0DCULL
        },
        {
            0xF6E55373F7C179B1ULL, 0x7B5D858DBABC81CEULL, 0x940A10CDFFF940B6ULL, 0x29BF9441DCAB032FULL, 
            0x97ADC45311B9D90AULL, 0xFC08A35FDEC66352ULL, 0x76910CF796F5556AULL, 0x0A8EB63A1EF18A74ULL, 
            0x666BF770785889A7ULL, 0x43121519511AA1FDULL, 0xD64863A4881D0D55ULL, 0x5BD6AC17D364F905ULL, 
            0xF5B1E38A1C3BDA66ULL, 0xE9EF702E876697D4ULL, 0xE87AFA1D5668EABDULL, 0x54FA7463C35149F3ULL, 
            0xDF7751A2CEE83402ULL, 0x444E8ACC66806B48ULL, 0xD459430C4E37C1CBULL, 0x2AE26266C18232DAULL, 
            0xFB7931B1728475C3ULL, 0x177E457812910796ULL, 0xAB854DD7977706A7ULL, 0xF67B8BB869F99FF9ULL, 
            0xE2797C035E8F8E17ULL, 0x3B3964058A0AEBAAULL, 0x554312D6EC84EA7DULL, 0xABE527207C0013E8ULL, 
            0xCF9BC69052A6B3AEULL, 0x1893FBFEDA85FEE0ULL, 0xE1B8454B5D72E0E2ULL, 0x99DD660D17AB6F24ULL
        }
    },
    {
        {
            0xAA235AD51A06152BULL, 0x504121D78DBC1869ULL, 0x2645984E42459FD2ULL, 0x65F686B741B325F2ULL, 
            0x9C68B61533AE0348ULL, 0x29B2F619B73D5386ULL, 0x52A11DFA8784F234ULL, 0xDCE0E7E8B54F887FULL, 
            0x41E0EEE4AA776FCEULL, 0x28867C776D240189ULL, 0xB7C3BA666E836DF4ULL, 0xE1E1685B4E1793C9ULL, 
            0xE71565432AD093B2ULL, 0xC1FD8A53A5692D01ULL, 0x734160989D987839ULL, 0x76DBFE5ED36A26D6ULL, 
            0x8D409E1467E7CF67ULL, 0x0E7D6F049C0394A3ULL, 0x9AEAEF41351A0100ULL, 0xA8B853C879378E87ULL, 
            0x6F536130428D173EULL, 0x124DA49B5D273CC9ULL, 0xBB0D75D30B8D90C3ULL, 0xB8846E10BE148C6BULL, 
            0x975A691ACE2EC58CULL, 0x0A7D6D24E4C566F9ULL, 0x2E7B0753FDD0384DULL, 0xAA2C6EA34B900EFAULL, 
            0x6F16381F6E7298C4ULL, 0x69257F9ADBAF6D3EULL, 0xA846851C714709C2ULL, 0x9C651C78DD1E390AULL
        },
        {
            0xD213BE8FF9AF96DFULL, 0x17A59B03393C3959ULL, 0x8E2F50A79863EC00ULL, 0x6067FFF0A448E3DEULL, 
            0xDDEAAE066097EAE2ULL, 0x7F8D5A6A86080131ULL, 0x59443E098970B4A6ULL, 0x9B28C8BBEA4E1105ULL, 
            0xD6BDB5D38F68AC35ULL, 0x3D770B14557EA2E6ULL, 0x9669CDED3927CB31ULL, 0x0085BD9206A181B5ULL, 
            0x5AC7529C68E8D3DDULL, 0xC1A5E6D4C3295CFCULL, 0x4F661631FCC45BB1ULL, 0xD6A2D9BAC77F7CD3ULL, 
            0xEA0C78A73C9517C6ULL, 0x32637060F3122583ULL, 0x2BEDA588338D4BEFULL, 0xF2242354F49D616BULL, 
            0xA65D934A8899A853ULL, 0x4788E2228EA4786DULL, 0xD3653453E3E4C1B8ULL, 0x074535C255441B94ULL, 
            0xB4E72545CC1AFA00ULL, 0x5BCDA3C0B3042170ULL, 0x2E6E2F89E1505B71ULL, 0x78F52C7EF6D70FFAULL, 
            0x4BC031E7DA9A0064ULL, 0x2CFBC312BE537EBBULL, 0x1D82443039024A54ULL, 0x79BD727783FD87C1ULL
        },
        {
            0xDD59C38F9190DADAULL, 0xE78CBFF5EE66B3EFULL, 0x6ACC916D8112EB76ULL, 0x1EFCD658D9226999ULL, 
            0xA74972CB8C716F4EULL, 0xF8A6F2D373928695ULL, 0x0C8BEEC64281944FULL, 0x3EC23BFA33911A8DULL, 
            0x52C596C1A9A502BDULL, 0x87618BB1B313CEFEULL, 0x4BB814136824F909ULL, 0x8760C71583A95FB9ULL, 
            0x0FBA4CFCDE2C2A49ULL, 0x170A95B92747D2E2ULL, 0x0672D6E18B69C0FEULL, 0xED149C2ABD215C1FULL, 
            0x62AA06AD884ADF65ULL, 0x085C4D04FEA770C2ULL, 0x23529094CED9C4F9ULL, 0x3A977CDA6AE921D0ULL, 
            0xB5B09F86711703FCULL, 0xB969D687E44F9F17ULL, 0x0B54032A08ACB38EULL, 0xF825FFBBFD5538ABULL, 
            0x420246AB807DB2AAULL, 0xB8E3432980673E00ULL, 0x6FD6FE30035C10DFULL, 0x10EC76AEC244AD71ULL, 
            0x2E1B9FD2480BFED2ULL, 0x2B6EDA99A8D7A410ULL, 0xA04B5ABCC2553E7CULL, 0x0E6D907024B5C795ULL
        },
        {
            0x5E12B4A944DFEED5ULL, 0x2BBD93552AFA0C54ULL, 0x99DA5677A9576B10ULL, 0xF0ADEFAD99F8D6B0ULL, 
            0x149C51BAEF40516CULL, 0xDBD35D3B26D3F338ULL, 0x79E3749E329D76FFULL, 0x79B3C9BDFA90A894ULL, 
            0x79DBF16CB559EFB9ULL, 0xE32A70784F2FC60BULL, 0xDEC0B18C28320D7BULL, 0x1450F73899BEC4FDULL, 
            0x97E142AC506DB72AULL, 0x2C3794C932419558ULL, 0x5B560A9EE36B00A6ULL, 0xCAA804D180239DBBULL, 
            0x52916310D1944A47ULL, 0x1837F9DC45729071ULL, 0x8D554F31C40E6165ULL, 0xB5D34FA1C158A3B7ULL, 
            0xD91F871931B6482BULL, 0x6D83065034991AEDULL, 0x444B44696BD4D47FULL, 0x30B420CC30B943DDULL, 
            0x423F3A7D1F5B038DULL, 0x560C6635223C2D28ULL, 0xDEFB92CE6CAF6862ULL, 0x2B724BE45AE8B152ULL, 
            0x5D3393A653D0ED7BULL, 0x578633E6914D9249ULL, 0x68E944BF95072CCDULL, 0xE0813C82361411CBULL
        },
        {
            0x5CE16DE6BCAA61C6ULL, 0x2CDF3A6249602E8EULL, 0x3B7F27B2C3B2A208ULL, 0xE70A7A8287E3BBADULL, 
            0x70D9FBCA61680520ULL, 0xBAC49456FCA4B631ULL, 0x57BFAB264AC42C06ULL, 0x3A924926CA80F148ULL, 
            0x3BDBCA17121B2967ULL, 0x04582A8375066246ULL, 0xFF4A49D3B2D0CA75ULL, 0x79E49730CA1090E3ULL, 
            0xDF77F4353570E5DCULL, 0x86DDF9A644F18CC4ULL, 0xC6FB31DB5840E35BULL, 0xBBC44BC785316694ULL, 
            0xD5B68E70E83A889AULL, 0x763C1A56C89F3FD1ULL, 0xEF5B25B9BCA0DB6BULL, 0x06D765EF3736211BULL, 
            0x8EA48984D87F26A3ULL, 0x81080931D35260F0ULL, 0x8D23D57C53984642ULL, 0x77672D4697F9C2EFULL, 
            0x92153E3EA2306C2BULL, 0x9C5344EA04526015ULL, 0xB8CE4F5D3575A15AULL, 0x0016185DA35295C9ULL, 
            0x2F74F6349915A451ULL, 0xEB2EDB19DE2E58CFULL, 0xAF9C8B5F93AD19FFULL, 0xA5FA5C769A1A2B6BULL
        },
        {
            0xD28CFB2E20DA12AAULL, 0xC971CAADE7B1629DULL, 0x71E198494C78C01BULL, 0x8380234951DCF023ULL, 
            0x0F4A04C99B533868ULL, 0x0DDB26C2D50FB080ULL, 0xE96425BA2DC6ACEDULL, 0xB841FBC66901A51AULL, 
            0x33BC2B84E6803AB5ULL, 0x8D679FDEC6C9AE52ULL, 0x9F739D566A7FA39AULL, 0x210B6C12E3D39AD3ULL, 
            0x8E8FF160D5CE1D93ULL, 0x3A7397E76092F2D1ULL, 0xBCC04DD052E607C2ULL, 0xEE69372939EEB31FULL, 
            0xF608ABAEC3047A1CULL, 0x21DE8F03A9DB9EB5ULL, 0x3B94FB0D3CF16E28ULL, 0x81342D333B371F03ULL, 
            0xD59B18B3A60C3F0CULL, 0x2AF2C26858DE33C4ULL, 0x299B8A5411B47654ULL, 0x777DCAE30943F0BFULL, 
            0x62ED8F571ADD6649ULL, 0x2978671476DB2E5FULL, 0x4FE70629FFE291BAULL, 0x24B4CCEA1456FA1CULL, 
            0x5F0FA92E4555BFC8ULL, 0x4D720528C08CC1B4ULL, 0x15260179CE07D7DAULL, 0xE700C06E3383EAECULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseDConstants = {
    0xD1CC06D73C21EB9CULL,
    0xC4B8D8764B45B2EFULL,
    0x6BC643F4961DC143ULL,
    0xD1CC06D73C21EB9CULL,
    0xC4B8D8764B45B2EFULL,
    0x6BC643F4961DC143ULL,
    0x99FAB80B1D7449E1ULL,
    0xA664DEC2DDF02396ULL,
    0x88,
    0x8B,
    0x94,
    0x17,
    0xF4,
    0x07,
    0xDE,
    0xB2
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseESalts = {
    {
        {
            0x8CE6A814E78DBBB5ULL, 0x9733079D05BC8BD1ULL, 0x1AD207057CDB413FULL, 0x6E874D53CB747686ULL, 
            0x83FE9EE7B11D3508ULL, 0x4C1DBB39F0F0C785ULL, 0xDF34C787248ECB56ULL, 0x4DFCEE0590421911ULL, 
            0xFC48A9F3A5E2DFC7ULL, 0xE4E9AE1EDA4F7C86ULL, 0x154DD71480BBEA07ULL, 0x737ADE78CF34D490ULL, 
            0x1A24C569DA19F4D1ULL, 0x6302AC5D9F65452CULL, 0x8643C4BD275CCEADULL, 0x3F8E755766608DC8ULL, 
            0xCAAA75E24C1BFB87ULL, 0x3575A84A571DEDC2ULL, 0x0BBCD57B870597E3ULL, 0x2EF82F51C1157DC6ULL, 
            0x908C7D59F696767DULL, 0x91E88440C3150EE0ULL, 0x0149BFCB06EF98D1ULL, 0x02919E7A4869832EULL, 
            0x8C66C9778064C488ULL, 0x6FB93BF36DA046ECULL, 0xE61D6F4FD396F81DULL, 0x578C6548B7373F7AULL, 
            0xDE11213995BC6FC8ULL, 0x702AF93B5ACD806CULL, 0x117B2ED514E45CCFULL, 0x3D9E59C00ADF82A7ULL
        },
        {
            0xB32AB6EBF5676302ULL, 0x6D712A88C152E175ULL, 0xC3B664C83F4A71C2ULL, 0x66CC8F59BF8CA4EDULL, 
            0xADD1508A42DDE8C3ULL, 0xE79D68909C76A66AULL, 0x2012083C12744925ULL, 0x38413E9C64B0B7CCULL, 
            0x6B16457044EAF299ULL, 0x73D2FC55F2F7D889ULL, 0x63FC21F49959904CULL, 0xE6812B1BFF041D3BULL, 
            0xDE2F10C00A895491ULL, 0x9B36AD6EEC3C5B05ULL, 0x9F3A33778849FE33ULL, 0x855FFC5A0AB4B8CDULL, 
            0x0E207B8EA6F34ADBULL, 0x5BDF3BEC5F3F59D6ULL, 0x903D7F34939FA295ULL, 0xCE2C2A972523040CULL, 
            0x894A129CAB2AA3DFULL, 0xF2AE647958EC2730ULL, 0x2069B2EC77171250ULL, 0x60DEFDF7E5E1C518ULL, 
            0xD3FE193B03C6AF3EULL, 0x16A8CEF1D84B4FEAULL, 0x1119FCB2B37A396BULL, 0x363265EF000DCC3BULL, 
            0x5CDE13A3365CDE0CULL, 0x697D1920037A6E1BULL, 0xA7969FD9D737E22BULL, 0x99B4B3CD080AEC46ULL
        },
        {
            0xDA53CA1F5B7BCFD2ULL, 0xE3FD1F2DDC2A7FFCULL, 0xF127E31CD13E8BF2ULL, 0x755914E8B332A37BULL, 
            0x829B0B5D37A850DAULL, 0xB17F46FEDC40DA86ULL, 0xB6AB9852EA5C9A2EULL, 0xF5631F085AD71BD1ULL, 
            0x168BCDCF477E1E6DULL, 0x8C34B0E7937040B5ULL, 0xFAB54D3ECA6E879EULL, 0xEF4431BE5B3A1DB8ULL, 
            0x3EB6A23C530A5ABEULL, 0x41DD3C575530E51BULL, 0x7A1971BBE505E35DULL, 0x084F5112620F8D37ULL, 
            0x953A620D48C8765AULL, 0x1EC62DDB942C9D84ULL, 0x343FDE4C273F87CAULL, 0x1E7351C1AC220F5AULL, 
            0xCB5AB7D463CE3E82ULL, 0xE3BFEDCAD6A45098ULL, 0xDCA2E2A9BF378FE9ULL, 0x99649362D15C8E17ULL, 
            0x803A5E827000821BULL, 0xFA1C76C43B20D74CULL, 0x26D938A47EE7F33EULL, 0xDCCD755D9997092FULL, 
            0x087FB313C8FF4EC8ULL, 0x96EA6764CC7CC8EEULL, 0x8F44C0811D7D6A91ULL, 0x4CC02F118D26A5D0ULL
        },
        {
            0x51118AFA369AF259ULL, 0x39A6544EE5477D40ULL, 0x6E1862C71CADFB27ULL, 0xA45AAED44056D9E0ULL, 
            0xD9A5AB1B0C3F7DE8ULL, 0x70B66353FD5D310FULL, 0x3061A893A3D25305ULL, 0xB209D18179BF9FFBULL, 
            0x7158F3E960393B57ULL, 0x4BB74E6F69626DECULL, 0xAC09B79D73265849ULL, 0xA3AC542597B59BFAULL, 
            0x0C7B8072B2B7E246ULL, 0xBB8ECA4C1D8C46F9ULL, 0x1A17D9F7CCEE4C6FULL, 0xFFB08A21A30B8845ULL, 
            0xF65A6B0CDD0AE999ULL, 0x9AEB201FEE14BD0BULL, 0xF3A65116F2AD69FCULL, 0x0C5A4E51B0C96479ULL, 
            0x408ACC0EE8E0457BULL, 0x2C0D5253C2DE595EULL, 0xF87D199AC5099472ULL, 0xE7CEBA82C89C7AC8ULL, 
            0x7661BB7D7126F78AULL, 0x696072BD968478CDULL, 0xE11E982FF851BB95ULL, 0x35217E43204526E8ULL, 
            0x78746A0047C5946EULL, 0x08599DCF40F81B2BULL, 0xD7F876911E3C8261ULL, 0xDB67AA455326FC1DULL
        },
        {
            0x7329186A8292F76EULL, 0x4224F17FBA538697ULL, 0xA0FED12956274DC8ULL, 0x6CD575B27447B838ULL, 
            0x49863D4BF9F775F1ULL, 0xE068F43F66398F56ULL, 0x0115941E1021AAE6ULL, 0x4974CE1DD1B3EF94ULL, 
            0xA3ACB47E83EB2AECULL, 0xB6A77D76319BAF46ULL, 0x0553D8088082D565ULL, 0x61A0926BBE8FA106ULL, 
            0xE3B7E5E1F7A8BA1CULL, 0xB9C0A36DCBE5991DULL, 0xD34850DA0A34C296ULL, 0x8F39AF567E69AA33ULL, 
            0x0150BEC94FD50B8EULL, 0x00390D353AE33510ULL, 0x29043D7B5C304162ULL, 0x93956E343CCE0F28ULL, 
            0x853CD81CF7AEFAA0ULL, 0xBD2F81A9A9E6352EULL, 0x45A40271E2D777B1ULL, 0xF6562C9BA02728AFULL, 
            0x901F0C3A87BABC0BULL, 0x866A329B3858F6C2ULL, 0xFD734700D8516BC4ULL, 0x9DBD5D4C38165EFBULL, 
            0xF845E1858FC577C0ULL, 0x45AE0B52CF1D91C1ULL, 0x625B3374B220BE15ULL, 0x0F17E5920A54A9A8ULL
        },
        {
            0xA0C43E6B58A418CCULL, 0x958DC5D54F9BED2BULL, 0x52BD8268DC5565A2ULL, 0xA9BD7CB9680507A3ULL, 
            0xB1B4ED3E90D4989AULL, 0x22E9FE337A65609EULL, 0x49A14F6F68ACB866ULL, 0xCECA657F23448D5AULL, 
            0xDDB020ACEBB9F80AULL, 0x5563A41B25C5251FULL, 0x7247A28EA8D5D78CULL, 0x5E61E36ADCC4D56EULL, 
            0x9F5F329FB927F013ULL, 0xE96D45F9DAF93AAFULL, 0x5495D236FDC019D4ULL, 0xB745A13329F0105CULL, 
            0x10AC2F0CF1A8B26EULL, 0xEF0E224E12143517ULL, 0x9D2A81748812F627ULL, 0x0D270061855BB73AULL, 
            0xD822CEAFC118F1BEULL, 0x1BCDE470A8961834ULL, 0x5EF81FE08AC1428EULL, 0xBE7951D5959702D4ULL, 
            0x7073613F99750D2DULL, 0x587DD2B46FE24851ULL, 0x5AC2E67E2B5CE25BULL, 0x2AE4AEB0FCC5E10AULL, 
            0xFB2A9EBCCA822916ULL, 0xE0DECAD744C3BC51ULL, 0x970791103601F794ULL, 0x645FA03CD54CA1C9ULL
        }
    },
    {
        {
            0xCC716DBAD0E67F86ULL, 0x0B57AD9DC612556DULL, 0x109C4FE4E64912B2ULL, 0x12089C91F537B70EULL, 
            0x87A36309773E4655ULL, 0xAC5786BE3A50A819ULL, 0xFAD046F924D011FBULL, 0xCFCD7F8D2A5D5F44ULL, 
            0x1389AA2802B48A5FULL, 0x13CAD4BAD9D4114DULL, 0xD3CA27F1E76C73CEULL, 0xD81AEE7BFC95FFE3ULL, 
            0x3C4F22DFE066E6C7ULL, 0x7868923C2719910FULL, 0x2D8B69CF8101E9D0ULL, 0x3FA1AB0954BA1220ULL, 
            0x44ADA41D3075331BULL, 0x28B066BBDEF8548DULL, 0x86E84DD25AD5804BULL, 0x7FFBD3FFC8DEA58DULL, 
            0x1A4F776A6451DB9AULL, 0xEB0E13C6B63D0F07ULL, 0xED5DE059E40F7F59ULL, 0x8189D953B0F96FC3ULL, 
            0x2C6491B10201F322ULL, 0x9FF1461C2CB10EA8ULL, 0x6C72D24944EBDEC4ULL, 0x89E4B0D875235614ULL, 
            0x3ED5495D9E3554B3ULL, 0x1706D55DF2291825ULL, 0xCAD5517316781A16ULL, 0x96BEC5A5BEFA9173ULL
        },
        {
            0x5885C458E5584E9FULL, 0xF0D125FF7607F947ULL, 0x6A75DB409BEBE375ULL, 0xCA3B47D67C90D6CEULL, 
            0x66D364610402BE1AULL, 0xD626EEB4457891F8ULL, 0xDF6A6F90296D8617ULL, 0x43A0C632CE99954FULL, 
            0x6E2388030B3DBE05ULL, 0x9E7428D432CFB6DDULL, 0xE29CF4F85C3161E7ULL, 0xBE41C22C1ADF30FDULL, 
            0x9198EF247573C3ECULL, 0x75B9AF216DFE5597ULL, 0xCAEBE838C25E6166ULL, 0x8AA9C577DABA9EEFULL, 
            0x691CDED9F03962AAULL, 0x7541C3C99AD6DFCDULL, 0x44653638C5E69392ULL, 0x7AE709C0B609598DULL, 
            0x43367C6611C7B833ULL, 0x201FEB89998F9797ULL, 0x7CCDE79FAE26CFD3ULL, 0x6F466BAC069B7784ULL, 
            0xFF7F77B0E2BC6CF5ULL, 0x729A4DAD9EB05A7DULL, 0xFA56BCFDA7DF4C33ULL, 0xF2127B07C74D068CULL, 
            0xD87E3C164263ABA6ULL, 0x9F7493A0BC75BC09ULL, 0x950899095B3D5613ULL, 0x863D87F027781767ULL
        },
        {
            0x775BF6296D982718ULL, 0x80CDD63BDD4C1220ULL, 0xD44A6D80124118D7ULL, 0xB8EEDBDE3742E200ULL, 
            0xA7899DF02AE9CD1BULL, 0x3042F2A6508D4135ULL, 0x24D26757D4B2948EULL, 0xA679600659B82B41ULL, 
            0xEBB7C8B4A353C3D5ULL, 0x1C98792C8FE0CA19ULL, 0x0E5AF8EEC297932BULL, 0xBB67932983BE1223ULL, 
            0x724A44A53EB877CDULL, 0xDAD143247B9EFC99ULL, 0x876056ADE83AC3A8ULL, 0x4DF2C07A29B4FB06ULL, 
            0x85A0DE38E1BFA4A6ULL, 0x5B41612D11DE4579ULL, 0x4956045FE4B585A5ULL, 0x557F563CB8FBED1FULL, 
            0x1AA0486057F62540ULL, 0x14659883EE6C3029ULL, 0x0FA8F973A5C0E877ULL, 0xB796A026B6503900ULL, 
            0x6531D24E4127436EULL, 0x45952B58E3FAF7D1ULL, 0x516524C92F60AF19ULL, 0x615CA0CD39296517ULL, 
            0xB71FC44D7BC1F624ULL, 0x0635367EC579B9DEULL, 0x1735AC1829F6FAB8ULL, 0x028966CEB8B0718AULL
        },
        {
            0x85D8423CE7870C2EULL, 0xBD2866AE75044196ULL, 0x433D38477B1702FFULL, 0xA0C70DD591E40992ULL, 
            0xCC6AC1E0B86CAF61ULL, 0xD41ACEADFA79AAFFULL, 0x7B963703F92CBC25ULL, 0x3C982ECB3B2322F8ULL, 
            0x13383FCC80BCBE5FULL, 0xBC940A6C959EF2DBULL, 0xCE4697DE7FBFE84BULL, 0xE0BC13B378E35DABULL, 
            0xB88EEAC99875305AULL, 0x41A436E929AAD54DULL, 0x957AA0BE70032A0EULL, 0xAF4A125E1B4F884CULL, 
            0xC0247F6653EDFA10ULL, 0x5E37095629FE1118ULL, 0x20773E5A93D0E432ULL, 0xDCD76309203E5674ULL, 
            0x63DF5F70D1F96B3EULL, 0x48389DA282E79A34ULL, 0x4A7F24268390602CULL, 0x34A79A2EB8AAB5E5ULL, 
            0xB8A78A19394003D8ULL, 0xD0DD3B1473FA62B7ULL, 0xF9B550FA242E0AC4ULL, 0xEE0FF37394C7AD64ULL, 
            0xE8152461B08534BFULL, 0x413464666F72CCF9ULL, 0x392BCC5BB51DD400ULL, 0x4D4C931FF4F69E38ULL
        },
        {
            0x8C124DE31651B965ULL, 0x55ABBCA4D443F83DULL, 0xB445228462F9BD72ULL, 0x3267D962DA8E949BULL, 
            0x866F6C41545E6B0BULL, 0x84BC48EC517E7E26ULL, 0x19C86F79720AA54FULL, 0x9461803368B06DF1ULL, 
            0xCE6D7753688BAF85ULL, 0x7808CD43DF32D569ULL, 0x34C5EEA0B1340849ULL, 0x492E913D93BF371AULL, 
            0xF156628857429195ULL, 0x0073A110D28E8CAAULL, 0x3CEADBEA2E5B04A8ULL, 0x2EA6E2315E1FA6C6ULL, 
            0x551FF4B535AEDCEBULL, 0xCE8C331BA9C0B53AULL, 0x011A20571F878EF0ULL, 0x6536FE1B9DBB7229ULL, 
            0xD9DDFB842EC9259FULL, 0x750F403A49442E54ULL, 0x8168C40DE6A4885FULL, 0xDEDBD5E86610B922ULL, 
            0xAB65E04584D85970ULL, 0xFF903ECA4BB25657ULL, 0xE01FC6C409928D27ULL, 0xE3A5B65EB3BB4587ULL, 
            0xEA7CA89FC251D7C5ULL, 0x904B1DE6C9D995DDULL, 0xF7A3B8CA729D43F2ULL, 0x01615AE7C97CF425ULL
        },
        {
            0x5F5C5F4CD78AC7B3ULL, 0x7C9CE4DD16F80DBDULL, 0x6AC548D2460214B1ULL, 0x3B0728735E98F609ULL, 
            0x03B6C033701AB0B1ULL, 0xF3B6386A1D9BDEDCULL, 0xC6C443D2DB99EABFULL, 0xCF151361559F6C27ULL, 
            0x3D60EE3C6C97E99EULL, 0xDEDD99C3A9722147ULL, 0x45752A1480D5D210ULL, 0x5C7A65EDD582D0B5ULL, 
            0x87620E9C689896D8ULL, 0x4FBE1C10D2E36B6BULL, 0x45D275036A64FED5ULL, 0x0514CEDE87CD47D3ULL, 
            0x138BEFDE9BC08099ULL, 0x5D134D2832E80064ULL, 0x257CA5E33E54BC6BULL, 0xBFD10466B7E1B32AULL, 
            0x3979A508568A392DULL, 0xF3582CE68BEF238DULL, 0xD321C269020C239FULL, 0x49CD43A48739F7C9ULL, 
            0xCC12262310780787ULL, 0x476BB510980848A8ULL, 0xE7343E83A62E2247ULL, 0x6838650DAA2AEABDULL, 
            0xBFB64D1BDF1382EFULL, 0xFBD6D2E5377499E6ULL, 0x2D72DE990B28A81CULL, 0x12AFE2DFADAB5F28ULL
        }
    },
    {
        {
            0xA29CC6B48AD5966DULL, 0xC749BA42B29AADA0ULL, 0x0F9B2509F84FCA0AULL, 0xFD86B461122C5D08ULL, 
            0x205E5997E364B43BULL, 0x98A9104E0A60873AULL, 0xE88DC47F9E550E03ULL, 0xC26B20F3C7205EF1ULL, 
            0x2D9CD5224FEBB3BEULL, 0x33B1EED9B5736E88ULL, 0xD315B3F465AE419FULL, 0xA95B8F5BABAA0B92ULL, 
            0x3FECE39C1415AAE9ULL, 0xE7C43FE0E41154ADULL, 0x44324177645EC809ULL, 0x319903ADB3C1978FULL, 
            0xC97E27290A905630ULL, 0xEB95ED902188CBC8ULL, 0x9C5369C0AA9E4B46ULL, 0x2B2B1DA307662923ULL, 
            0x6343B16F3E1DE24AULL, 0x1A6183BB6DAAADB7ULL, 0x9E26CBDFE33D11C5ULL, 0xE53557D936BF3C86ULL, 
            0x25F121FAB0F72504ULL, 0x6CE1EBC3FE3B78CCULL, 0x42F6333041D46115ULL, 0x57CCD86E05F946E9ULL, 
            0xAC82173139982E5EULL, 0xBA519C36562DF3A5ULL, 0x134ACC144CB26778ULL, 0xDCA43BAC1453257DULL
        },
        {
            0x97764BF6850BF663ULL, 0xE755C43C5545F90AULL, 0x8518168A65FA0CDFULL, 0xB7899D04D775767AULL, 
            0xB40E9159A561BA6FULL, 0xEC5DEFE7053FA436ULL, 0x523EAB6194E0B36AULL, 0x207D80323810B115ULL, 
            0x955E7D1C14A5354FULL, 0x893898A52B25EC91ULL, 0x2F04FD48DD25D38EULL, 0x7BE1AC713D5226F0ULL, 
            0xE5475F928FE7FB6FULL, 0x753A0FD08676C8F6ULL, 0x7EB6CDD48FA5FDD0ULL, 0xBCFED1439EA78C7DULL, 
            0x27EAF03FCF4EB9CBULL, 0x73D9CFA2C4E7112CULL, 0xDC4C428EB5953135ULL, 0xB779160A419B7486ULL, 
            0x92D059832AA1437DULL, 0xAD47CF3B8F7F70F6ULL, 0x00BFA9492F645CE0ULL, 0x52DBE12956D3E9BCULL, 
            0xC4F72E17DF7D5548ULL, 0x9DC2FAA340EFAD09ULL, 0xF4B87E66468B61FCULL, 0x072B216AF9E97AAFULL, 
            0x939665582A22F077ULL, 0x637BEE16BEA507DDULL, 0x05BFFD7AD5FB4EF1ULL, 0xDAA8AF86A417F300ULL
        },
        {
            0x5D57D65C9267C3B5ULL, 0xBA4931DDA0244328ULL, 0xDAA006584B12F920ULL, 0x30B0F779B2D954D8ULL, 
            0x72E298820F492018ULL, 0x83608E4164A5AFD7ULL, 0x7619B75DB704EF3AULL, 0x33E69004D3C8AFCAULL, 
            0x6543F69AE8D3AD08ULL, 0xAD130C0D4E2D3D42ULL, 0xAD5D705FD9C3BBFEULL, 0x932B7A27BFBA035AULL, 
            0xD4EE5F9BCA6104D7ULL, 0x70F82A53A555192FULL, 0xC4939DF10E19B68DULL, 0xD883080E85D16C16ULL, 
            0x9405B94AEFA350F4ULL, 0xC2953336CD12DBAEULL, 0xA7B19C0EE04E3CE5ULL, 0x99E2BAC8FA35AE45ULL, 
            0x8575806EB5EF67CDULL, 0x59CA67A6D5B86952ULL, 0xE1058E371CA1496FULL, 0x33FEC0C0910F2979ULL, 
            0xE9FE287C33408BA3ULL, 0x6554BE7A80DACEA3ULL, 0xC1BFE454A5EB791BULL, 0xBFB15C2918BD6D39ULL, 
            0x2030BA31F3C81D10ULL, 0x5D050DD8BCDDC208ULL, 0xA1150125BE4938B8ULL, 0x5DF89A42947F4958ULL
        },
        {
            0x1ABE4E6D33B43D48ULL, 0x60CE78525B101AECULL, 0x5E2A4312FFA3BEDAULL, 0xA0F5072F08505939ULL, 
            0x1F8764AAAA282B96ULL, 0x3CDB6A72546F2100ULL, 0xF46264B4A9A05465ULL, 0xA68EECF601620FAEULL, 
            0xC75BBD950EBA354BULL, 0x317031096322ECF3ULL, 0x5F7DD0CE81312C45ULL, 0x73C024C2640E5F39ULL, 
            0x2F273DE2DB97F775ULL, 0x73E7129267C3E51EULL, 0x5A30B85981D390B8ULL, 0xEB44914B9A3AE9A5ULL, 
            0x6D3E99CEB6410817ULL, 0x3FD60BAD1859AC59ULL, 0x2DA13701D46F1B39ULL, 0x3A0715BBAE6B09F1ULL, 
            0x38C27A5AA019B17AULL, 0xB0683FF9219D2876ULL, 0xD276C7B594BC91BBULL, 0x40ECB5A82B130156ULL, 
            0x3C565C78569868C3ULL, 0xE38910298E3562FEULL, 0xA2033E547A412FCBULL, 0xF7E84607DF895D4FULL, 
            0x018A6D229F9E516BULL, 0xB724651F21BD03C0ULL, 0xAAF814D09D614CA8ULL, 0xB96D2FBAB2AB2BE9ULL
        },
        {
            0x135EE748FC62A4A2ULL, 0xB4E29D46F4233F65ULL, 0x43EF2F8F332BCFA5ULL, 0x6CAC6AEB1BFB0C4AULL, 
            0x61BFBCA54AE22F7CULL, 0x9CFE4EE7C7EA770CULL, 0xE245401B7A0CDB36ULL, 0x3C4FFED77A0E6553ULL, 
            0x4479CDED935B8947ULL, 0x8BC4FD6DC993EDBAULL, 0xC4305B55BE83F523ULL, 0xAA9B518C65145DB3ULL, 
            0xDF2D220A03754631ULL, 0x57C2DEDFD209ED2BULL, 0x1745E5FA9743B9C0ULL, 0xA32DBFA81318293AULL, 
            0xAE18E28C7DC7B6EEULL, 0x3DD71B7D06BD3121ULL, 0x55716EFF95D62D5EULL, 0x9042646561F74FBBULL, 
            0x31C164457C968ABAULL, 0x3441B8467C5C32F2ULL, 0x6E841DCCCB44F7EDULL, 0x3A5B68D4B6D35BDBULL, 
            0xC2C3129CE68AFF20ULL, 0x0218FF68FB270978ULL, 0x2CEF05EF3DB1D9D9ULL, 0xFF3F9EFEF9DFAB37ULL, 
            0xFF67B14B09CCBD59ULL, 0x7C62A66FCB8D4E0FULL, 0x18E61851C71682D5ULL, 0x568D4D1F8C02205EULL
        },
        {
            0x349B66AA2CE67CDDULL, 0x8C6AF9E9E487D9BCULL, 0x75AAD3A2A9DA53FCULL, 0xFA2A31B4AC995EEEULL, 
            0xC40C19B1FB5D859DULL, 0x2106F85BCA5BC634ULL, 0x3F9E4FE73FA6E05DULL, 0x30423C2153ADAEBEULL, 
            0x66369E95076C0AB0ULL, 0x6AD7160E372F4592ULL, 0xC842728724BBB649ULL, 0xE49C2D8D1C68650CULL, 
            0x09736E40EBD01EC8ULL, 0xCBE14D925DAB077EULL, 0x17644D78189F9C7BULL, 0x8409B1DDAD70CDEAULL, 
            0xA8E4BB387B03EC26ULL, 0xED634530C872C334ULL, 0xF15249E69DFDC441ULL, 0x1B6594635FC8769DULL, 
            0xA52084C2A22EBDBBULL, 0x07D6AC4D8F15B2D3ULL, 0x66D17D42436A4F79ULL, 0x2006749AC96996E5ULL, 
            0x19F5B6EB2790CC52ULL, 0x11696D2147C62DC7ULL, 0xC198E281D59310BFULL, 0x27A432B7BB0B5478ULL, 
            0x6B3626CB4AC52BD3ULL, 0xBC528AF80C1CA1CCULL, 0x3879BB5DA2604870ULL, 0x8A6FC036539D4A5FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseEConstants = {
    0xE99CE1C9CCEF91E1ULL,
    0xAA01783B6EF5FB43ULL,
    0x297A47E4386028C4ULL,
    0xE99CE1C9CCEF91E1ULL,
    0xAA01783B6EF5FB43ULL,
    0x297A47E4386028C4ULL,
    0x4C1936BF27243ABCULL,
    0x589FD92101C9C2E2ULL,
    0x38,
    0x17,
    0x38,
    0x04,
    0x67,
    0x13,
    0x6B,
    0x73
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseFSalts = {
    {
        {
            0x763BCEE70FAF90A6ULL, 0x93E0568212D72A24ULL, 0xB5F5879B698815E3ULL, 0x94C5848E0FC6A690ULL, 
            0xE0C34A7B47154334ULL, 0x8EB11B2D82BD889BULL, 0x69F0D6D628D1304BULL, 0x322F9712B30C6C28ULL, 
            0x390049BCD6CEECBBULL, 0xEABDD4076B16D2BDULL, 0xE602974E64456A32ULL, 0xA841D2BBCE0E7548ULL, 
            0x6FD49551ECEDD6B3ULL, 0x537A22C13E82E4C6ULL, 0xCFBD120BFC75FBE5ULL, 0xE4EE7C19548036B0ULL, 
            0xDF5B36716F117D5AULL, 0x2B3BCB4C5FC0C8C8ULL, 0x88DB1BFF7E844267ULL, 0x62F52C993A50601AULL, 
            0xE465ED5EC71CAB68ULL, 0x63AF64BEB2775E7DULL, 0x0E351BD738A69692ULL, 0xFF11A3ACBBC64D13ULL, 
            0xF432AA3625627F17ULL, 0xD5F45674868FD212ULL, 0x4C1329250A3AEEA3ULL, 0x4268FB8E725A708BULL, 
            0x856D65BA337015E2ULL, 0x8C14E510AB4E03E3ULL, 0x61410199A1F6BE32ULL, 0x5A94E63E1A1247D3ULL
        },
        {
            0x70DE2C9A293074C3ULL, 0x05E6F89552642348ULL, 0xC6BD6E2FAE7E5224ULL, 0xBD410170E42D92ABULL, 
            0x3EDDBDA137B42E1BULL, 0x0CD39C136B3DCF95ULL, 0xFBF8989C0185445EULL, 0x1505AF19B668948FULL, 
            0xC92AAED2401EDD78ULL, 0xE2EF20601C134D8BULL, 0xBC1FC70A8F06364CULL, 0x7381F5A7BA37D8D8ULL, 
            0x34809165AD708BABULL, 0x84F2D4D2F9DB2B2DULL, 0xDE3DFFF1EE1F104EULL, 0x0DA3CF7813A8B7EDULL, 
            0xB43B533E8708AD46ULL, 0x3399ADF6C2458EE6ULL, 0xAC8A0A9F8D72F3ECULL, 0x6B176B6B45D84D7DULL, 
            0xDC54D5880F6BEB86ULL, 0x0BE1A2FC3370F787ULL, 0x6A16E6A6E41349B5ULL, 0x46A7019C29A32E45ULL, 
            0x2F79DD8D1603AE9AULL, 0x1296A89A6270C66FULL, 0xADE8EDA8F0FBF80CULL, 0xD75355788436921FULL, 
            0xB86E11B172F5D9BDULL, 0x564B4229B1BC9798ULL, 0x0D8E548B4A77A45CULL, 0x82AB4C3E94D43832ULL
        },
        {
            0xC52FC048815E8992ULL, 0x7E11C0E4B299EA48ULL, 0xBF1CE7883F1F3DACULL, 0x89DEF3DD765AECA6ULL, 
            0xA997BB5732B6950BULL, 0xE13C3F38F9C5FE0DULL, 0xC0E30A74BC3C0CA9ULL, 0x6BE9AA9B687A68CDULL, 
            0x02B83FDEDADDE63FULL, 0xD61F953A4A696997ULL, 0x7A8DF11A084E7964ULL, 0x5FDDE2398923708EULL, 
            0x2DC5900B70CD4ACEULL, 0xCAF9A606AE1B8D40ULL, 0x066F66F2B419666DULL, 0x62BE9C4860B64C12ULL, 
            0x15CB1BAA5B886508ULL, 0x87DC6329A3D8CE65ULL, 0xDFA6AC359979B7ADULL, 0xA59E47198C0F903AULL, 
            0x6BE45525B0195076ULL, 0xE58DF12E77156D00ULL, 0x57B6EAA90B8FB612ULL, 0x4292936E4E845E31ULL, 
            0x35C3BE4607233ECFULL, 0x97E691E7E6176F55ULL, 0x05C70FA630D4E369ULL, 0xAEF0E7DBF577BF30ULL, 
            0xE2D6B6D8CF3ECD08ULL, 0x5698C8CBE0E1D52CULL, 0x6D261FD11D1382F2ULL, 0x6B4A80F2BFB536C9ULL
        },
        {
            0x787B320C4B88BA4FULL, 0xB52A49BE3FA2954DULL, 0x789CC790568D6C10ULL, 0x4FD1CC5E1234B382ULL, 
            0xB13C67FACC5CD396ULL, 0x200100A83FF9B083ULL, 0x264760D14015A81DULL, 0xC96E50E0DEC09417ULL, 
            0xC3FCCB8EB12CCF3EULL, 0xA974926BC4B1C66FULL, 0xE764583DFD6007ECULL, 0xC736FAFCF6C2A309ULL, 
            0xDAA7A13CE0668CCCULL, 0x4E0290E85C9391E2ULL, 0x4243BE816F999BDFULL, 0x1CE5BBBC376F390DULL, 
            0x007D25D9B1248397ULL, 0xE3EDEAE11F7F8A3FULL, 0xB7A06E0192A8DCD4ULL, 0x92C9DB5A08BBF97AULL, 
            0xCF3115A589A989BBULL, 0x774E6755F75C8352ULL, 0xBD578E0B53075C0EULL, 0x8864991FFAA994A3ULL, 
            0x703776503FCF6B52ULL, 0xDD0D1582DF6D2703ULL, 0xB38EFD2F873DEC02ULL, 0xD9A2352DAE2172C0ULL, 
            0x755B60343BDDC9A9ULL, 0x3E1C8CD8968CC1ABULL, 0x757BE88FA1D296B5ULL, 0x88E14C6D0D3ED9FAULL
        },
        {
            0xC55AA67056287D2FULL, 0x7E6B44885FEADD42ULL, 0xD0DB8652BF63EA5FULL, 0xE52E779662800B1EULL, 
            0x12F4BB9016CCC2E7ULL, 0x0E0D9E7746FC17A7ULL, 0x5F8A36F6FCF28FF5ULL, 0x5922D9D78CBBE544ULL, 
            0x21FA1A4E530F3821ULL, 0x36ACDF6FAEF2B3ABULL, 0x135E66673A11948BULL, 0xC95119E1D1204594ULL, 
            0xEAFB31B16EDCD789ULL, 0xF4C4D31600AFC186ULL, 0xD263526371ACA118ULL, 0x24EE11670DE42A3DULL, 
            0x11794B90B4B050E6ULL, 0x862DC648DF7ABEC5ULL, 0xF34FCDD91AEE5357ULL, 0x51185FF68FA78508ULL, 
            0x2FBC73301AFCA5BFULL, 0x383AD8B2DE364054ULL, 0x79466E0066147F21ULL, 0x7581A7EB957F9784ULL, 
            0x1A1DD792BCD51C22ULL, 0x7519E4A6CCD5F8B5ULL, 0xD72AF8C5F806B4B7ULL, 0xBC37D819A399D081ULL, 
            0x32CF88244B07DE3EULL, 0x8D2882CA13C4B425ULL, 0x72E608A15BF40D93ULL, 0xC37008D129B89E8CULL
        },
        {
            0x67F0EB14FBBF95C7ULL, 0xA00D3E0C6D437DE7ULL, 0x6ECA746CFA3EEFC9ULL, 0x249B6F08A174CEE3ULL, 
            0xA262CBE2A1C1FAEBULL, 0xDD9CABC8F75B319AULL, 0xC15B801286A27224ULL, 0xF16523D2848C8233ULL, 
            0x5CC69D3F60126E07ULL, 0x476D51C60D1864F9ULL, 0x2BE4DB6FD8448FC8ULL, 0xE8B426DF04CE1AAAULL, 
            0xDFAB62A5CA234F37ULL, 0xC7A0748F25116917ULL, 0x2C2785846A1E1C82ULL, 0x30E1294A05AEAEB7ULL, 
            0x67FAA2565A279549ULL, 0xD5D3981045462B21ULL, 0xCEC01834EC3619E6ULL, 0xDE35333B9CCFA2D7ULL, 
            0x0C2523B98A269551ULL, 0x850023DA58562157ULL, 0xDCC98E9F335FFF16ULL, 0x5B8D4300724B77CFULL, 
            0x553AEE05821AFC0DULL, 0xA9900A0646DF4E69ULL, 0xA5A9E1290A1236E1ULL, 0xAFC4894DFFB9B0BBULL, 
            0x13C9F738A5CED859ULL, 0x5A9C6F7315EA399AULL, 0xA93DBCC4D0C197CBULL, 0x427EB5B7B9309211ULL
        }
    },
    {
        {
            0x68F4F39C5BE02500ULL, 0x8658E6554C37D05BULL, 0x7760A052623D70EFULL, 0x8C76F1B59EC758AFULL, 
            0xFC2D9B6F26CF7C09ULL, 0xD440F10C19D6767DULL, 0x6C259C0CB8FD2CA4ULL, 0xA9E7875045D1F079ULL, 
            0x2DD7D5E7771A6DEDULL, 0xAFEB3E9FFB0EDFB1ULL, 0x62E0EA7074207393ULL, 0xCCADC3AD15A29892ULL, 
            0x2ED6B751BD290F8AULL, 0x6293AA2D1416C1DBULL, 0x5AB46C5BE82DA3D8ULL, 0x24EC0FC7E4A04C50ULL, 
            0x2FAE3BEB5D679D5DULL, 0x183EA07572576D7DULL, 0x5667BA511147BF8AULL, 0x5B5CECE0D37BC440ULL, 
            0x959A445AA380A424ULL, 0xCB64736FC9D637A1ULL, 0x42C738027AD0CCA8ULL, 0x0E14D752748C74C0ULL, 
            0x4F6C97AF7389F579ULL, 0xF05D53C2E0374AB7ULL, 0xB3AFB268501B24EAULL, 0x5639C0D710D74F6EULL, 
            0x4979C780732D8EBAULL, 0xB48EBA6C7F549586ULL, 0xF4C449C472CC44F6ULL, 0x90351D2B9D2CB311ULL
        },
        {
            0x1FEE8A4F2F26EE8AULL, 0x7C7651A5184C4984ULL, 0xD7388DB37B235C33ULL, 0xF5867EA23F4093FBULL, 
            0x24A9F42DEFA54671ULL, 0xD0A016B29E630C22ULL, 0x315F877D774E5CE7ULL, 0x9F29DFA2510FBD99ULL, 
            0xAD11136AE0B64691ULL, 0xA472BA33C9B893C9ULL, 0xC26DB2584E807A4FULL, 0x36F00FB702C78451ULL, 
            0x3E730FC1143FC507ULL, 0xC98F4EF85ABEDC94ULL, 0xA7BDFF34587FCE63ULL, 0x69D41B14D8916B54ULL, 
            0x5167A00B02ADC3F3ULL, 0xD23928AF901ADE86ULL, 0xEF14E4B60C2F4AC0ULL, 0x466125734704000FULL, 
            0x9C0A4A5ABCFE57E5ULL, 0x58402CD8833F125AULL, 0xE45F09D68CDB2078ULL, 0xCDDDB38CC90DA030ULL, 
            0x379B7EA91C15B09CULL, 0x64D8A154E9359401ULL, 0x0DC82809B4FACF8CULL, 0x2832CF176AA9C573ULL, 
            0xE63484C3C37597DFULL, 0xA9CB25CAC1EEB0E4ULL, 0xF8F1B1A0DF4895B7ULL, 0x829D948F5DECB1A1ULL
        },
        {
            0x1B8095D0F5CEE1C2ULL, 0x1E2559DAFD694C5CULL, 0x6877FA590A4FD332ULL, 0x135B184940C264E9ULL, 
            0x7B799B7BAA6CABAEULL, 0x1773D05EF0DFF7E5ULL, 0xA761ED46D000A43CULL, 0xE3737CE91845C38CULL, 
            0x436EA70668E09F84ULL, 0xD8B43B0E9CE8F881ULL, 0x65DF21FF7C3F5D4FULL, 0x0D931AEDFE80B500ULL, 
            0xCC34E45222E85CE4ULL, 0xD8A7D36A7AF07088ULL, 0xF80CAD9A42391DE1ULL, 0x275377B15C4C2B98ULL, 
            0x1BEA542679DBAC92ULL, 0x6947A26D266FADFFULL, 0xEB468680EB9A9B87ULL, 0x375BF723E73751D8ULL, 
            0xD6D16A6D5D2C40C2ULL, 0x9CA7370E59D2FB7FULL, 0xA2BFFB40137988CDULL, 0xC4B31410B81ADDFFULL, 
            0x06D051C4D7D06CC1ULL, 0xED9EE24AC0A1F042ULL, 0x25396CCCA7946406ULL, 0x463F67F40D1745C9ULL, 
            0xDA006B388F8BF616ULL, 0xCC5A7F74F40BCD3FULL, 0x63EF894BB7B0722CULL, 0xD15D552055DB20A8ULL
        },
        {
            0xC0579325BFA95BCCULL, 0x2D520B8A101183BCULL, 0x2435607C6527DB4EULL, 0x07F8AC291BDC18AEULL, 
            0xB753840D577C65FFULL, 0x6D24AD2EF9D3920EULL, 0x0A0FE118BFC657BDULL, 0x762763F28FF8448FULL, 
            0x145BF5EA3A0FBF59ULL, 0x5E001CF2A78043D9ULL, 0xA369AB6B9A6D8091ULL, 0x69DA568B70629140ULL, 
            0xEEC2C6C27C5CAEE3ULL, 0x08D003E0EDE97835ULL, 0x38895E4F46201251ULL, 0x1BE37E60387C5BA5ULL, 
            0xC426BE5F76BC0C6CULL, 0xC3C476E3B77FDA1EULL, 0x266830D694DD7688ULL, 0x78F06A59D53D7D1AULL, 
            0x16C2D9287140085CULL, 0x0F76B64E12AC92EDULL, 0x3EC00B63E3639CA0ULL, 0x2C96D31B77A64FC1ULL, 
            0x5BB4918463E56A19ULL, 0xB8C4F76C14FB2209ULL, 0xDD613E16C8B39A0CULL, 0x0CE1F0A0C14E099DULL, 
            0x6ACB89815E77E7A0ULL, 0xDCCAA7A1B4CBF1B2ULL, 0x96F4376BB04DA939ULL, 0xF4A6E220D25FE101ULL
        },
        {
            0x04CCFC578809A35DULL, 0xB7DB725D464647BEULL, 0x2F310CD03B350D2FULL, 0x33792ABD17C2F92BULL, 
            0xF4210D9412F30E84ULL, 0xBA38676BAC2E97B5ULL, 0xA0A26B12E5D60F48ULL, 0xF423900A1B2671E4ULL, 
            0x7D4A802071202269ULL, 0xC056A2A65585C40EULL, 0x52B348B154AD6AADULL, 0xF1F159DD1E7EDF98ULL, 
            0xF7BDD743F430F59DULL, 0x782D104FF8A3A0AAULL, 0x0A556AAFF8E13EFFULL, 0x59A16735A2D684C2ULL, 
            0x1FE4B7A8A561BCEFULL, 0xAB7D119DFC49551AULL, 0x31A85D6D34F5EA12ULL, 0xADCDE221DCC90B79ULL, 
            0x1C424FA77AE6EA3AULL, 0x31DCCD7687B66E23ULL, 0xC9219ACA3A128517ULL, 0x3A68B5387983200AULL, 
            0x03D343FF20131A50ULL, 0x80E11734937EA0F8ULL, 0x11B775D838E57B75ULL, 0x135F738AADF746FEULL, 
            0xF15214E7DFCDB5C2ULL, 0xF232C0DBDC04F01EULL, 0x243F1DA46D9D3235ULL, 0xFA205C60B40472A9ULL
        },
        {
            0x3E64776B1642E1E4ULL, 0x6C399DFA53FF8A0BULL, 0xF24A92860D2BC7E1ULL, 0xD3D9147AD2AFDBC8ULL, 
            0xB44E20716C1BF0B3ULL, 0x8290EF3D10C3CF8CULL, 0xB8E0CE031AD70E1CULL, 0x294AC0D3F5B02BA7ULL, 
            0x20720430E522DED2ULL, 0x8CD2F1EED0CEE69EULL, 0xD45773697D2A6A8DULL, 0x56252D510ECFA15AULL, 
            0x8700A4198846A775ULL, 0xDBCB6EC886F4E855ULL, 0x9BEC5BAFDD5BEDD0ULL, 0x329853C4BACAD82EULL, 
            0x8B25D2D5143EDE60ULL, 0xDE57622ADDA1A83CULL, 0x791F5B7B7CB5DB99ULL, 0xE8CE598AA9B25C45ULL, 
            0xE81045471E297C90ULL, 0x992575689A5DFC56ULL, 0x3C80B8867718040EULL, 0x6ECF88954D860251ULL, 
            0xC740A743A228C054ULL, 0x7A418782BFCABD6DULL, 0x443BE8545CD14544ULL, 0xCEB65B7C91AEA2CAULL, 
            0x4B30A889C6C40AFCULL, 0x16F840F07B54E19EULL, 0x58D1D00BE88835D4ULL, 0x658523714F4C6131ULL
        }
    },
    {
        {
            0x715BFCA09CC1D098ULL, 0xA5CBFC8006FD81D3ULL, 0xE0B21A3009774E02ULL, 0xED5C631820C1981FULL, 
            0x6A85F49EF8553AEFULL, 0xE8014FA69807DC32ULL, 0x5C817BC2F83592E2ULL, 0xA4C0F295DB7ADD0DULL, 
            0x84EFB1CC11A0B590ULL, 0xB4FD39D27D338FE2ULL, 0x3BB0B350F82779B5ULL, 0x1DA8321A6745EE9CULL, 
            0x07C53E6297B8183BULL, 0x0456ACB9CDDF64C2ULL, 0x476FAEF8712E96B8ULL, 0x8BABAADC8AF65889ULL, 
            0xB6CBB6ACDFA86B3BULL, 0xC0CEA902CEEC8EA9ULL, 0x5CDBCD523B05109DULL, 0xCA505114A2C7982CULL, 
            0x64686EDE79B902FBULL, 0xBC64736886E0009DULL, 0x38C5DE7E819AB6E5ULL, 0xF50F07712D60EED2ULL, 
            0xDF37487D7D7F9FB5ULL, 0x80657D700EA91FD6ULL, 0xA414285FA5BF9365ULL, 0x7203DCCD0F3722EAULL, 
            0x9D4A09DB62786A9AULL, 0xD937353DDD744C1BULL, 0xD08A97F1CCA571F5ULL, 0x347A334718449317ULL
        },
        {
            0x3AAEF6F2ACC3CFDDULL, 0xD216B68E3834238EULL, 0xBC8AA5A573F03087ULL, 0xC2DEB213398C7CFDULL, 
            0x81994333AB07512CULL, 0xCA0C4AB56676E09AULL, 0xCF28D8CA5739A96DULL, 0x659C9EAB19C9FE71ULL, 
            0xFE54E040A36A7856ULL, 0x17E4930B2711F59DULL, 0x5A00A4AC1BA30F14ULL, 0x587150AC1524B44FULL, 
            0x1257F66527DB9C94ULL, 0x95C745AA955D5C7FULL, 0xD17B458A1C8F3B7DULL, 0x1F6F822DB167ABE2ULL, 
            0xAA2C349B37EF0C3AULL, 0xBB945829CBAE1880ULL, 0xDB2194BAADF7DD25ULL, 0x278E00C74862F22DULL, 
            0x000EE040EFC66BADULL, 0xA7C09729C511543AULL, 0xF25BE1C3A0ABD0C5ULL, 0x1210308E536F261EULL, 
            0x2CCED4BF6679D94DULL, 0x6C67AD2B054E85D8ULL, 0xA6A08FFDDBACD6CDULL, 0xE3B57F68702A0D2BULL, 
            0x0B54F8EDFE6D21F1ULL, 0x0137D84A54F8AB0CULL, 0x8B3F3F934A615C4BULL, 0x137D7A8E66C9E421ULL
        },
        {
            0x78C75FB19CA45675ULL, 0x80135C7C7DF9870FULL, 0xA469F44D4E0477DAULL, 0x61805195B5BF214EULL, 
            0xF2C81C45E13BA362ULL, 0xB891BC4C4B6C278CULL, 0x8280DDA6B429CD0BULL, 0x00049CC4BB008858ULL, 
            0x35F921566FCCCCE3ULL, 0xD7B42448708F8CBDULL, 0x1CBBD4C8BF078F1BULL, 0x7E1C59D830FB6C16ULL, 
            0x4F9773F185D62F7EULL, 0x2157A684F8DE14C8ULL, 0x3EE335D72D76AA54ULL, 0xE6B4A1AD38CE8615ULL, 
            0x3CC3F031FB94DCD1ULL, 0x408703E20F9D12CAULL, 0xDCDAAE77E136AAEDULL, 0x3AF84D7E94E04EFCULL, 
            0x45AA662D9777B05FULL, 0xB7428D559A961242ULL, 0xD7349134CA840D10ULL, 0x885ED778863D1839ULL, 
            0x9D14E7B58FFA0E78ULL, 0x5B50ADADF613B9F7ULL, 0x38D071883E859896ULL, 0xC64CC0DE6ACB5404ULL, 
            0xB2488FCA538FD83EULL, 0x4646DED2F58317FCULL, 0x225428B6BEB5E633ULL, 0xD6D6320B7F9D95E5ULL
        },
        {
            0xDD41EDB1B1AA17FEULL, 0xC49EB610E72E856DULL, 0xFCC8C2E65BF40AF4ULL, 0x2218BCF66E568073ULL, 
            0x073B4CF89E68ED16ULL, 0x29DD1DE118DD9E01ULL, 0x3EE0B16746EAA7F4ULL, 0x25C741A6B20B517EULL, 
            0x6B9999AED78A3A2DULL, 0xC4F613C8176F417CULL, 0xD63D899DC2A0DD9AULL, 0xA36FFFA5AE40B313ULL, 
            0x42F6A377C1A4CD18ULL, 0xEACBEDE775893B3CULL, 0xB1CDAA8BEADA2669ULL, 0x6616196F29476966ULL, 
            0xC3FB8379DA2687BFULL, 0xBE57904A172F37E9ULL, 0x0C7CA083DF2D7AF2ULL, 0x73DFBF48B5679732ULL, 
            0x46DE7BEA56201F2FULL, 0x410A2CED2051B780ULL, 0xBA0677298BCA13D7ULL, 0x76732F2C39B43BAAULL, 
            0x995A8D8EEABC9701ULL, 0x090D1C8FD5433CE9ULL, 0x2EAF5A826C824549ULL, 0x999D65E2BE6B5B2FULL, 
            0x62F36EED44034A1DULL, 0x00C7DA9EE8E4E43EULL, 0x96273B5EF9DB3A29ULL, 0x6E46F35ED5E01E34ULL
        },
        {
            0xB280B3A5D056D656ULL, 0x4505AFCDD3D9C443ULL, 0xB0E15454B56E51D0ULL, 0x8F2B9805F02F45A6ULL, 
            0xC7BB8C957A98639CULL, 0xE96F4E09CCB48364ULL, 0x690C7646BEFD9F8CULL, 0xF85A8115E376ABB6ULL, 
            0xB6D360394E85232CULL, 0x62EC8E4AB693DCA5ULL, 0x925EF988DFD5391CULL, 0x562BC9B9CEE159B9ULL, 
            0xE01D154F5BD1FC22ULL, 0x43259F168E6EC067ULL, 0xBB8B1DD76F5D1AAFULL, 0x6899F4F3A9A534A5ULL, 
            0xB30B73AE405CC2ECULL, 0x9AD5916741F83D6EULL, 0x2A06C48DEFF64DF8ULL, 0xE9F2DFB5B0BD8553ULL, 
            0x3166DD442DF5A8B3ULL, 0xB7EF4E923BBCEED3ULL, 0x507AB1E09721270BULL, 0x398EA82C6BE14040ULL, 
            0x52EDD491871F6ED7ULL, 0x71D4A1D0D7824A69ULL, 0xF48650FD72F92416ULL, 0x0DFF9276CEBA2A1EULL, 
            0x5645FD9FDC5BB0A6ULL, 0xEBA3381D5DE09E2EULL, 0x1C126524DB5099A3ULL, 0xE26DB3857608DC1BULL
        },
        {
            0xED0F0180FC775C56ULL, 0x4F1CB31C69EF1CBAULL, 0x8673DB19042505ADULL, 0x352FE343D08D1536ULL, 
            0x5BE6C1B2E6E127BDULL, 0x0C75F71929AE82ECULL, 0xC2A2FD763BE51502ULL, 0xD5D1E0C04D054323ULL, 
            0xB56E8FB0DD1BB29FULL, 0x3AEBF135E9C0EB95ULL, 0xCD3684F407EE2A64ULL, 0x49065E3EF38DF490ULL, 
            0x01953647C95AED08ULL, 0x298891C98159D891ULL, 0x1FB7C45CC5639360ULL, 0x2A18BCECE551414EULL, 
            0x7563E21F91D83333ULL, 0x8920BE5B698A7547ULL, 0xA737BA66523BC805ULL, 0x5731B9F5023638F6ULL, 
            0xA3D29FB24FE36532ULL, 0x4379CCB6C5581CB8ULL, 0xF594FEB108FF7612ULL, 0x38089D93B9E05FCBULL, 
            0x957C91483C9EAF94ULL, 0xD32EFBAA6CF95CA0ULL, 0x507A3B44679E7CC6ULL, 0x395FD8BACBF193A9ULL, 
            0xB12445D66FCD6FC8ULL, 0x648F091969A6F0FCULL, 0x979DE0C462221994ULL, 0xE5E63F347FB023E4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseFConstants = {
    0x03BC58352F2512ABULL,
    0x1F018077F166F1E2ULL,
    0x9312441C22141D97ULL,
    0x03BC58352F2512ABULL,
    0x1F018077F166F1E2ULL,
    0x9312441C22141D97ULL,
    0x0763040950BE034FULL,
    0x4D1799BA21663532ULL,
    0xB8,
    0x47,
    0x2A,
    0xD3,
    0x75,
    0x64,
    0x27,
    0xEB
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseGSalts = {
    {
        {
            0x20D74C92C1102A32ULL, 0xF3059F61D384A0AEULL, 0x70A017DEA832E804ULL, 0x09CC00066A53B3F8ULL, 
            0x987490858E2455F0ULL, 0xE4F05DDD7F766C6DULL, 0x1DCFE6BEA8F42F11ULL, 0x7597DF82443A9960ULL, 
            0xB9997D7AB2651783ULL, 0x361625BF4D7C2FA5ULL, 0xE48C28CA09BE243DULL, 0x71695725187588FCULL, 
            0x5D7AD6A1F4CC5F2FULL, 0xA8ADB5FAB688D7C3ULL, 0x6A5FE8FD24E70B1AULL, 0xEE3BBABEDD19BF83ULL, 
            0x02350562E6FDAF2EULL, 0x10C0CA4A1BB8092BULL, 0xDF86B6BDFAF4FD25ULL, 0x5CE134EEC8FF757FULL, 
            0x131B5438E05189A1ULL, 0x692F5128D9F50890ULL, 0x648CEBDF07BBD322ULL, 0x3D3F6BC94041C906ULL, 
            0x13C52419FE90FCFFULL, 0x704805055E9D5B7FULL, 0x12F3BF4B4EEE99AFULL, 0x20DCC35C7E12E3C8ULL, 
            0x4492F17AF3196633ULL, 0x7C0FEAEDAAE6C308ULL, 0x36F2658E9366C1CDULL, 0x5215BCC36297713FULL
        },
        {
            0x04E578ECB682A17BULL, 0x91B3C9FB01F1BD78ULL, 0x8F25AFC160ADA508ULL, 0x0FC2659A3097DF3CULL, 
            0x46B54A159949EEE6ULL, 0xAC913D37CAD97F02ULL, 0xF56AF2E8F25E5EF4ULL, 0x91CEC037C1B86465ULL, 
            0xC3AF46D051CBE4A2ULL, 0xFA07031B4B7DDDD1ULL, 0x468A10327ED8D356ULL, 0x20ACAD761E215462ULL, 
            0xB8701A576DC65DF8ULL, 0x5D424EE4376E3E52ULL, 0x99A64FE530B5F81DULL, 0x7094E92C7CCC214BULL, 
            0x44D13BD441F33EF2ULL, 0x587CDD5BEAC89783ULL, 0x48DA50686195490EULL, 0x28DD0DB366B1F637ULL, 
            0x60995493C9105C6DULL, 0x255ECDC873FBDE60ULL, 0xAE41130CFF16CD14ULL, 0x5098D8DAEDCEF132ULL, 
            0x6B6D027F80500556ULL, 0x5EEB131C1E9B4F69ULL, 0xCB747BC0743CC33FULL, 0x9B93B5DFD7B9931BULL, 
            0xF76D95C9FB6B433CULL, 0x99B4F238C0A503A7ULL, 0x22DFA3F8C69F1C30ULL, 0xE09CD952068A0A11ULL
        },
        {
            0x1AD9D996816EF7E0ULL, 0x8970022A84D60D8CULL, 0x54E5629615514267ULL, 0xF175DEA8E144C544ULL, 
            0x8D0547A2BB51BF68ULL, 0xC39F9B36B6B5D6BCULL, 0xDB3FF11CE643D56AULL, 0x264EF8B46E9DADA2ULL, 
            0xEEA203A19957E54FULL, 0xFD95B3A5A19F4121ULL, 0x88DD56142F55CEBBULL, 0xD8E7E9F062F7EEC9ULL, 
            0x627A40744C69A3B3ULL, 0xE41BD87D82F63D1DULL, 0x6D7592F969B68A70ULL, 0xC840DB3531413159ULL, 
            0xCF11F8CE76714E4AULL, 0x02787D82B0BD552BULL, 0x125F4F50958B4E4EULL, 0x8BB7143FC07CA81BULL, 
            0x3F96B859E3DF8AC8ULL, 0x34F4E9280BEB1E21ULL, 0x0D60A384F182C2F6ULL, 0xEBD6028954E6F32CULL, 
            0xE179DF2897572F83ULL, 0x40B3DC5BF82091A7ULL, 0x175286426B8B0A0FULL, 0xCE781EADDD3C3BE4ULL, 
            0x240A07EE4E9008A2ULL, 0xD6D180288AB0C92FULL, 0xA745A23C827108E5ULL, 0xAFE811DA33E5F4E9ULL
        },
        {
            0x369B2E2913B0A22BULL, 0xE120499FCE495BADULL, 0x3A716F265BBF0611ULL, 0x9FE3BB89CE5B25F3ULL, 
            0x3DD53DB170FC7374ULL, 0xBB94CE0E2D414EAEULL, 0x6CD31074855F8E90ULL, 0xF9624C9CC3D36CF7ULL, 
            0xC1D6A229EFC66409ULL, 0x28F201BF645D69B4ULL, 0xDD247B2BFD2A837BULL, 0x1A3AF776B71BCAD6ULL, 
            0x057C8AC8519D988FULL, 0x827D92E7F0C1046FULL, 0xB28E5FA6658F3329ULL, 0x8BB2EE75CEC73726ULL, 
            0xE0C28366C18A8D98ULL, 0xB84C279D644BAFF2ULL, 0x74406BE4A1994E6DULL, 0x1F0495D3424DFE32ULL, 
            0x4DDAAD683B30BEADULL, 0x06CBE7DAF0ECEA06ULL, 0xBB1DA8256D865A1CULL, 0xBCA565487A2F5EE0ULL, 
            0x63614C189257B3C3ULL, 0xC9EB8191E3C50FD4ULL, 0xA5D8991D186B7F3BULL, 0xF925185D68FB5F33ULL, 
            0x3771974EF58023D5ULL, 0xEA4694BA90DFEB80ULL, 0x009792AD8DFC07D6ULL, 0xEE3258E808503FEEULL
        },
        {
            0x0E63780C739056A7ULL, 0x09AD5B423F48258BULL, 0xEC767D9A0E960A05ULL, 0x76F965BEBF4CD460ULL, 
            0x2103BEB16A12B11FULL, 0x95D2A1A4EFCA9764ULL, 0xD3B9859089CD4D0FULL, 0x357D45C7B30D3EB1ULL, 
            0x4B37E60E49AF2F5BULL, 0xD735F1BD41076B4AULL, 0x1B4DA809AE7FB916ULL, 0xD84DA12600F7D314ULL, 
            0x7AE765C3876401D6ULL, 0x2801A2017DCD5649ULL, 0x280D6B4938D29034ULL, 0xBC8E35C1AE339EFFULL, 
            0x29922D619FFEFE0AULL, 0xEC9A1D7CF0592302ULL, 0x4BC1413BF3797B6BULL, 0xE19570181A059AA1ULL, 
            0x6DFE28B32E350EBFULL, 0x74C5C034E6619C2FULL, 0xFFF462E6EDDFE136ULL, 0x4787AA5C7D462C5CULL, 
            0xC598C2AE9E6BA8FAULL, 0x5982E63B228CBC2EULL, 0x5F779385F4461BA9ULL, 0x4AB94F6A26BEF33FULL, 
            0x987E2B5B01ACFFAEULL, 0xE4046F2A4B6E0A58ULL, 0xA8890B4CAD655B81ULL, 0xE6C54AF8A4CF44CAULL
        },
        {
            0xEF07A144D39DC639ULL, 0x6B45EA2AC5A7EE2AULL, 0xAFC461A1F35BB8CEULL, 0xC448926C4B0204CBULL, 
            0xE36CC56C4CD58CC0ULL, 0x52CD42540864D8AFULL, 0x0587DFA6272E7315ULL, 0xF7485577884EF926ULL, 
            0x0AAAA3D7769A65F3ULL, 0x879624BE529592DCULL, 0x8B4E82B3B098FA87ULL, 0x75A717AACFF88588ULL, 
            0x02BC0AB3AE5AE1AAULL, 0x6EC009AAB85EEDD5ULL, 0x7A08DD1CB7C14D83ULL, 0x4F6087EA6DDDA7E6ULL, 
            0x56784DE0AB5C843CULL, 0x9CCAD725F8F8FDECULL, 0x64500E2F79B5DF70ULL, 0xDFB07154F2817BEFULL, 
            0x45D1059D5669A6BAULL, 0x0811665E98EFE3A5ULL, 0x37A96A692271D1DEULL, 0x211622FF4807F4DAULL, 
            0x362417B04DC1D5DCULL, 0x31E57036636C7BD0ULL, 0xBE8C287F782A8A12ULL, 0xBE90F202FB3E971DULL, 
            0xD9600B8BFD5FE8D4ULL, 0xB1091CFAC1FC81E0ULL, 0xE3672518B949BC9BULL, 0x50534FFF5EA3FED6ULL
        }
    },
    {
        {
            0xE6E8AF8663BDC99FULL, 0xF0EE381F1FE11D0BULL, 0x7943E80CE741E8E4ULL, 0x3DF0546A7C2702B1ULL, 
            0xAB275B0AAFBFEC11ULL, 0xFA6600C8A9017237ULL, 0x11D7F3084F156464ULL, 0x1E9CBCF6FD85DFA2ULL, 
            0x457C820347DC3913ULL, 0x767489CFC1F8E6D5ULL, 0xC336F90B4203F636ULL, 0x570E694B3381CFC6ULL, 
            0xD29882304D574676ULL, 0x439B24718130CA06ULL, 0x1722F31AA126D286ULL, 0x97E322718079FD76ULL, 
            0xA5E7D36BD9C2ADBBULL, 0x3B4BF9C8BAEE2B16ULL, 0x5D9575B96359E3FDULL, 0xD5233335DDF6DE44ULL, 
            0x8564028AA5693C79ULL, 0x52FDDCEC6A9C4E38ULL, 0x4877DBC2AABC0F75ULL, 0xE0CEE27111171D75ULL, 
            0x288D9F83BC1229BFULL, 0x6B47FDC4AEE7D4A2ULL, 0x56C59D047156C6E6ULL, 0x657A019247BC0B9DULL, 
            0x6CD4B1E441FBBCE6ULL, 0x3D77ED6DC6BFD45DULL, 0x58D818DC9189F214ULL, 0x7653B684A9C39041ULL
        },
        {
            0x41E0F4F7AA3B1A99ULL, 0x1D770E7C02A20CEDULL, 0x8D43394EBF060639ULL, 0x9C0DFEB929ACCF65ULL, 
            0x2A443B29677B9AAEULL, 0xE59D9B686DC41092ULL, 0xD446CC99F207629EULL, 0x329415430D32EDDFULL, 
            0x6885EB1BCE08D273ULL, 0x0E23F5370FBAA034ULL, 0x36BC7903031C07FEULL, 0x758F64A3A1912998ULL, 
            0x10A010E57CA25F90ULL, 0x8A5EBD2574A83D8EULL, 0x3902F8915F0F6A1EULL, 0x83B6C520E03D3577ULL, 
            0x64C3E7726354EF8CULL, 0x9EFD2616AAC69802ULL, 0x90FE8B631A40D565ULL, 0xA7460BC72BCB959DULL, 
            0x3F3F72E823942AC0ULL, 0xB199DF1D940F6914ULL, 0x2B1DD2189A14654CULL, 0x2575379CEC9C23CDULL, 
            0xDDC53CEBC3ED628BULL, 0x4C70E5F360BBD83EULL, 0xD22FD0A42F901CDDULL, 0x0D554CA99429DFA9ULL, 
            0x312A3C2C1105864FULL, 0x0956FE3A503DC094ULL, 0x2D91A63B10B64309ULL, 0x9E33169BD3870375ULL
        },
        {
            0xCA7105A5F4D7028CULL, 0x4E313F9CCBA090BDULL, 0x48A0687B5EC42681ULL, 0x4294221E45430914ULL, 
            0x2C02237FBEB04CA2ULL, 0x26F6919D9267A417ULL, 0x0A589031638E3B20ULL, 0xDA1AA03094228E60ULL, 
            0x7091E3612E882586ULL, 0xC3B63B3CD5D246BCULL, 0x1525C1F12776BEEBULL, 0xBC0A8CFF6025B7A8ULL, 
            0x2CC38639F4B64E2CULL, 0xFE1591BCFD48BB51ULL, 0x6DB76281378CB22CULL, 0xE0090A67E08FD789ULL, 
            0x47CFF760D0CB846BULL, 0xE240F7E88BC295C4ULL, 0x4F45D6287F5B1F53ULL, 0x2CBCAF8016A0D5DFULL, 
            0xAFE980CB34C51823ULL, 0x9D0E0515B67DB6EBULL, 0x89E1BEFAC509665AULL, 0x8539297F05366270ULL, 
            0x7A6B883751662527ULL, 0xEB6A26AB3304E302ULL, 0xFB4FFE3880EA430BULL, 0x0571FCDE9B241EDFULL, 
            0xE8BEC1706379BD25ULL, 0xF42928B912DC3654ULL, 0x76BFF8F14759910EULL, 0x0B5DA02F7FAE2A74ULL
        },
        {
            0x2005975240189761ULL, 0xF694D24456E45FB4ULL, 0x0DE4D9E065AA975DULL, 0x49E80A58CC50188FULL, 
            0x8CC9085781A5231BULL, 0x1252A93A4CF67173ULL, 0x9E3A99F3534C8141ULL, 0xE3676C9F4FB4F8EAULL, 
            0xC52011FCFE39329AULL, 0x80C4A444074F4991ULL, 0x96226BE588C63160ULL, 0x8AB2BB8657187767ULL, 
            0x6851B764135445C8ULL, 0x79D0709F841D789AULL, 0x56DF98E5F4C79FAAULL, 0x83C86C02941A4B1FULL, 
            0x3EC5A2CF60D44426ULL, 0x750B46F732B00DCBULL, 0xACA53554AECE084DULL, 0xAF33E1308EFD0033ULL, 
            0xA80169F0838F1282ULL, 0x5C19F1F40ED0D664ULL, 0xDAE0C697AF9469BCULL, 0x1F44890D616C9BEEULL, 
            0x986CE300A904506BULL, 0x2C1198F21B593136ULL, 0x3B7D69613A0DE01FULL, 0xDD5A0DD945B457CFULL, 
            0x4632BBC16520F670ULL, 0xDA13569AB0289430ULL, 0x84EA505905AF80A9ULL, 0x33965E6A08735238ULL
        },
        {
            0xE6CD0465F79529F7ULL, 0x9BAC90D2442403A3ULL, 0x22DA08DF355D5A9BULL, 0x8155DA7538073CE2ULL, 
            0x1E2D3320DA601E0FULL, 0x135B221D1D0470C4ULL, 0xAC450F84F7B2F4A9ULL, 0x2B195009A5B84588ULL, 
            0x46613742C9D7FDF7ULL, 0xE9ED949D1E35E5EBULL, 0x34C6CC21E2802ED6ULL, 0x281A8AD8F9F4C483ULL, 
            0x03C954987C0E748EULL, 0xDA06E6469766CCE0ULL, 0x0C07BAE08DF4DEE8ULL, 0xB24820CC93197229ULL, 
            0x1D6733B794CBBD9DULL, 0x0E01FA30B9997E89ULL, 0x141EFD8B61D24B35ULL, 0xF8D9DA0B231CA69FULL, 
            0x6CD547EDFBEC5DBFULL, 0xCBE0C708EEF451D0ULL, 0x8E3F5A5EA752B325ULL, 0x5B2100BAF9EB9338ULL, 
            0xDF0149C1C4CF0CE5ULL, 0x5F274E72900BDA7DULL, 0x1C172333E74D78DEULL, 0xDB10E180CC2CA7A9ULL, 
            0xD59EF98CDE99084BULL, 0x1EEFA5E4D565BB3CULL, 0x3AE14B15950D41D2ULL, 0x43213F94DBEB07F8ULL
        },
        {
            0x7B8F39892A233DBFULL, 0x0A890323AC88AD68ULL, 0xB55C5EA92B0CFB52ULL, 0xD95DED9E08C4DF41ULL, 
            0x878D1F777E967C5BULL, 0x547DA57A49419A2AULL, 0xD296839A873D56B9ULL, 0xBAD3E0536686971BULL, 
            0xCB9D9F0629C90EB6ULL, 0x63FDC3F64D86966AULL, 0xD916463894454632ULL, 0x118ECEE4F332D973ULL, 
            0x289ADDC6D342CE5FULL, 0x2795AF0A6EE9A3F7ULL, 0x9620D97A526DCCB7ULL, 0xDE82A8688180BEF7ULL, 
            0x280AF556CE830F7EULL, 0x8BF95A550B4810DFULL, 0xF773EF98D1640C41ULL, 0xBABE1248166DCDC6ULL, 
            0x4FA5CA21D209264BULL, 0xA5DF45724B68A2A9ULL, 0x911C537C56B3B110ULL, 0x791C1E278156A8BFULL, 
            0xE346B1CCD51997BAULL, 0x748FD2E78FA5F5E5ULL, 0x8D160CF25F04A801ULL, 0x293EA047D8A47196ULL, 
            0xABD63F149AFBE9FAULL, 0x30D37F23B811BD08ULL, 0x9D928AA37A543BE3ULL, 0xB39DDB4E32810318ULL
        }
    },
    {
        {
            0x51DB80CDADD06CC8ULL, 0xA2678813A4019050ULL, 0x8A75CDB452CB35D0ULL, 0xC8DE8505651D93F2ULL, 
            0x0BD31F737099B523ULL, 0xEA53F5A95F483FF1ULL, 0x4259399C6CA1B975ULL, 0x758F80D5F2513FFEULL, 
            0xAB151F2C42AA0448ULL, 0x1597D149C653F108ULL, 0xFE02438F95A98EEDULL, 0xBB5AF8F1F30CEDCCULL, 
            0x3871EAC5FE1155E5ULL, 0xEB988D964E425F3CULL, 0xB7130DFF68440DDDULL, 0x6A0EC54E8DC1AE84ULL, 
            0x28F4C85FE05B3CF1ULL, 0x42690A4592F4F61EULL, 0x344DB7C7CE5D860AULL, 0x823BAE96CC7F60B5ULL, 
            0x6CFE27508384B27FULL, 0xBED5F8985FC53432ULL, 0xDACE68E49EAA6ACCULL, 0xB3CC67A0FC635400ULL, 
            0x44218F070DB357FBULL, 0xFEFF649D046A583FULL, 0xA5A7E3DF86755DD1ULL, 0xDE93BE360CD3B6A4ULL, 
            0x28FBEA2DCCC9DF5FULL, 0x9C528EEAF0D2F438ULL, 0x13DF7D33521CA0ADULL, 0x4B3CB1BCDC1D8B0DULL
        },
        {
            0xCE5AD6A3E1991438ULL, 0xB82DD5E897506016ULL, 0x8B75FDD8A498117CULL, 0x5B9A987150842B20ULL, 
            0xF98FC05CDCB21537ULL, 0x4EA6B80E0DDA4583ULL, 0x8C3EB2A5BFE7650AULL, 0x83A3F438FE83B882ULL, 
            0x557CAD52CE78AB7AULL, 0x947D291DBEA03A57ULL, 0x4177027192AC4953ULL, 0x591CE1E408570BF8ULL, 
            0x23DE7067C5EBA484ULL, 0x2ECEC858A59FAD68ULL, 0xA4115A31D188F73AULL, 0xBFD57041C966F14FULL, 
            0xB40C7695D30FACC7ULL, 0xEB9E4517A33FA04CULL, 0x9E34F96DE762E580ULL, 0xFD0878F2919EBC07ULL, 
            0xED5FBFC8D991570FULL, 0x40EFB2457B674D5FULL, 0x1D5A516EBA79BE02ULL, 0xCA00832C590696E0ULL, 
            0x953DFA89C1068EF7ULL, 0x1922E2E2527B88C6ULL, 0x291D6AC32AE6DC6CULL, 0xA2B2DD1CFAE57413ULL, 
            0xEC905CDABE7EB331ULL, 0x033EF99826FEDAD3ULL, 0xFE0FD59BCF2DA6D1ULL, 0x0CC04F3AAA242CA8ULL
        },
        {
            0x17A44818EEF3EBC0ULL, 0x30556A9C89940C48ULL, 0x1EF63C408DD6D8D6ULL, 0x868BCA5D5EC4B228ULL, 
            0x32518D5C27E25812ULL, 0x52DE16CDB0C1A5B6ULL, 0x786AE7E43BD071C3ULL, 0xE24359AF8E8F9B9EULL, 
            0x53F525F01902264AULL, 0x7EE733C363CD6E51ULL, 0xFC48F5DAC2FC972CULL, 0x980DD0895F3CA6A4ULL, 
            0xA5544A9E1798CB7CULL, 0xA30398FB881EB3B1ULL, 0xD81C5D53B24AA86AULL, 0xEB3425186F9856B2ULL, 
            0xDFAF8A496BD98E13ULL, 0xF76CAB4021A372B0ULL, 0x5DF451AC6F36C425ULL, 0xDA8391D14CFFAD00ULL, 
            0xB22967F0B23572C7ULL, 0x9ECBB6F9FE30DFF2ULL, 0x44C3DBE6A435DC33ULL, 0xDAD44B4B79BD3E66ULL, 
            0x07AC77A0D30A5546ULL, 0xD41FFC67C76CC481ULL, 0x9425C1F16CC6589EULL, 0xF5095723DCA1F385ULL, 
            0x47277556732B02D4ULL, 0x5A11A334CE59A33AULL, 0x12EACA32FDD1F2F1ULL, 0x1730B06AE5231392ULL
        },
        {
            0x72CDD7E393B83A1BULL, 0x862B4F36F8BF747EULL, 0x5B885585FA32A5CEULL, 0x28E2BBF1EF2158FDULL, 
            0x7715F00D9C4CE3FFULL, 0x55B38C227B6934C3ULL, 0xEDA5E744610E7F61ULL, 0xFC958241015A418DULL, 
            0xDED3E0E9539F4329ULL, 0xE88091D2A26BE7E6ULL, 0x5572015A5CDEE15DULL, 0xF3F6D780ECF7AF34ULL, 
            0xF615B28F5A3D0930ULL, 0x127301832B466172ULL, 0x6CB4E7613AEF15DEULL, 0x4325A239DB3B660EULL, 
            0xBC1EF01E0147EEB7ULL, 0xEE29BBB04D36497CULL, 0xA6A4C4EC0458A204ULL, 0xD4634F51AC8A9B60ULL, 
            0x4A18F218179DF85DULL, 0x26C5A8934FBC9A19ULL, 0x87A93127075902D8ULL, 0x8B26469AAB922F16ULL, 
            0x1A8C03FC5ECDDC15ULL, 0xA1EDA1798BD22BE8ULL, 0xF5A7859EDBB0272CULL, 0xE2B703CC42CF2697ULL, 
            0xDD61F11FB06710FAULL, 0x4323A7A8E0FED164ULL, 0x5031D2D7B0F5F8C1ULL, 0x53DBB3B953ED87F1ULL
        },
        {
            0x00105BBFA6D6BE56ULL, 0xB01379D1FE84E34FULL, 0x3767E4A809D1908AULL, 0x6BD6EE5958BA9307ULL, 
            0xCA5C4A224F8D5C03ULL, 0x0148877EF53B8630ULL, 0xAF43F8A65ACBFE1EULL, 0x37A853377D9EC3D2ULL, 
            0xFBADF1EB1B41E98AULL, 0xC99727841E6C8496ULL, 0x4998ADA3F05ED1ECULL, 0x5889B0B3CB6FC146ULL, 
            0x118261A01ABE3649ULL, 0x9B50E324BE0DCCAAULL, 0x5625BEC2AECA868CULL, 0xB4FF309E32E88417ULL, 
            0xCD177B247E0A4C3AULL, 0x7E2B9A9170521CC2ULL, 0xB9F38C666CCA3B40ULL, 0x6166421AB7048105ULL, 
            0x969BAAC9122FB5C5ULL, 0x278CA101B6025A72ULL, 0x9F7F17CC5C3A341AULL, 0x87984B09B7069AF3ULL, 
            0x0BD985EA2AC5CDFAULL, 0xDE78AE6F9D8A2DBEULL, 0xAE40E9145B77C720ULL, 0x780048CB092F826BULL, 
            0x2244F9A3FEBC0446ULL, 0x3ECD4AA934AB5B4DULL, 0xE9E504E988DF2952ULL, 0x07526D937E175AE3ULL
        },
        {
            0x12097A92F48BA571ULL, 0x700B04AB224E0B53ULL, 0x6AE5270EED7EB455ULL, 0xAC9D4B57673EF8A9ULL, 
            0xBD6D8A5ECAA08231ULL, 0x138FEF0345A19F73ULL, 0xC993292B8082E6B8ULL, 0x9A08CE8B087744CAULL, 
            0xB7FE3C3EC3A64E48ULL, 0xEEF60A0D83B4C5AFULL, 0x35A1618252EE5C79ULL, 0x4AF72CFF8A581108ULL, 
            0xC6710A17835637CCULL, 0x7ACF43F27D63FBE6ULL, 0x4AC6DC91064E8402ULL, 0xC252199F4A75B56BULL, 
            0x7638B3F3F07A1DC4ULL, 0xB6E614F909270365ULL, 0xF688EE016663C9DAULL, 0xAC5E57D182B90A2AULL, 
            0x20E31CD916167AE5ULL, 0x4CF211762152BDAAULL, 0x2E95F36A4C7A2035ULL, 0x6515E047844515B0ULL, 
            0x81F7908FFD956774ULL, 0x01747CDF180259C3ULL, 0x3A457473CEE1F1FAULL, 0xB3A039002F605BA2ULL, 
            0x5692F0E6A4CE306BULL, 0xEEDB4EC1CB62C077ULL, 0x37785B36EDB8BEB5ULL, 0xC14AAE5171D42875ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseGConstants = {
    0xA852AB33972DA118ULL,
    0xFE7BEC7CBA13483CULL,
    0xB8FC57B882C18C8DULL,
    0xA852AB33972DA118ULL,
    0xFE7BEC7CBA13483CULL,
    0xB8FC57B882C18C8DULL,
    0xF5944387E1036FDAULL,
    0xCAF8C3119937406BULL,
    0x61,
    0xB9,
    0x8C,
    0x8E,
    0xC4,
    0x21,
    0x77,
    0x91
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseHSalts = {
    {
        {
            0xD675A80B28E1E533ULL, 0xF7133D8A5086202BULL, 0x8966BCE45C8D473CULL, 0x94B3B87B5ED8C761ULL, 
            0xD968F10FD9ED0CD4ULL, 0x9111D670F11B6735ULL, 0xA8C45E7CA2373357ULL, 0xB7F3180E0CD8D30FULL, 
            0x64CDFC82905447CCULL, 0x82CEEABF8652DA3EULL, 0xD2115B7D85ADBD47ULL, 0xF6BEBC5BC3FAF889ULL, 
            0x6051F5FF1E95F8A7ULL, 0x46FE3137AFD733BFULL, 0xEE79864C15D47BADULL, 0x66D11C20BA935EDCULL, 
            0x56294FB8A899132FULL, 0x0A2BC3006930CE27ULL, 0xA939718C12C53F39ULL, 0xEE3FF4930C7DE34CULL, 
            0xECEE5962628D0F63ULL, 0x4A3093B5206D5854ULL, 0xCABF09C14DB0E771ULL, 0xDBA4A386679E7A40ULL, 
            0x5C59BD6A9299C421ULL, 0x737F44ACF8954B1DULL, 0xFBA31A583B15ED22ULL, 0x6BEE94E34AFC2E61ULL, 
            0xCC0B770A3C9D0C1FULL, 0x48BC3B1EA029EA32ULL, 0x5350315239CEFA24ULL, 0x020BD3B3257DB91EULL
        },
        {
            0x41AFAE486D3E355AULL, 0x8175793373B0173AULL, 0x056AE42BCAE2251DULL, 0x57D606D08A9ADC48ULL, 
            0x5EDEAE83B737D488ULL, 0x0207F4599D028021ULL, 0x70F3325A202F2CADULL, 0x91964F9F4FFFC080ULL, 
            0xE72EC8ACBE50B530ULL, 0x62695AD3EA94B3A6ULL, 0x9FF4A76A6D18A523ULL, 0xCF40F1BCBC987B33ULL, 
            0xBFFFB2CFD6AF8027ULL, 0xBB987A03D84E37CEULL, 0x7BBCC1A3F648BBEDULL, 0xC939843D75B89815ULL, 
            0xE1DDEA0F6555CBACULL, 0x7361E6290B3A0C9CULL, 0x585F35C599D45CDEULL, 0x913A47398B3BD71CULL, 
            0xC6EF6D7007461C56ULL, 0xB8F25C5A69DC3D59ULL, 0xF56060578DFC7EDAULL, 0xE2749F99C2699F9AULL, 
            0xDF44AABE66870F0AULL, 0xDB77EDDF896E7929ULL, 0x48589F668A9F0518ULL, 0xF993347DF4EB4390ULL, 
            0xD04BC405E7ED7A1FULL, 0x314B686B23732D9AULL, 0xABF6A3C1083EB713ULL, 0xE56C382131AF7BA1ULL
        },
        {
            0x83EE90EA3657D30BULL, 0x692751BDFFD90EF3ULL, 0x9E51BB987F756054ULL, 0x299FF938A072D49FULL, 
            0x8600FAA20B9ED942ULL, 0x9B366BA240F49852ULL, 0xB4945B16A1115F8FULL, 0xB067F70C65E22CCFULL, 
            0x599486A6E3EA6D74ULL, 0x9F6833CB1C7E5628ULL, 0x2733E343BDDAAB7CULL, 0x9C8A65EEBA03F924ULL, 
            0x5ADEC449CDA4C8B3ULL, 0x5C9AC1363C23E5DFULL, 0xF5825CF1171B9B90ULL, 0x0D36FC2D603C272AULL, 
            0xBD3FC708869430EFULL, 0x5084E7DC2EFE0C3BULL, 0x0F7FC9CA8ADF9C07ULL, 0x276F99AFFBBC7B55ULL, 
            0x2CA021833057A53DULL, 0x9391640D67F818E6ULL, 0x7D5E059F3780E826ULL, 0x69B114311B07179EULL, 
            0x9C88A8EA6BBEB547ULL, 0x4E4CAC51EC9B6ED0ULL, 0x40C180B7A541AF40ULL, 0x9DCBE4E25738F24AULL, 
            0xCD1EBB722B61AF6CULL, 0x6480026C9F293DE7ULL, 0xB12F2104FB448F24ULL, 0x2AFC2465AECB5CF3ULL
        },
        {
            0x4C62C56386118F65ULL, 0xEBB77EE36DE9E29CULL, 0x1A8008C86035AE15ULL, 0x97DFE35EE68CF6A0ULL, 
            0x1E458B1A2CBF3FD5ULL, 0xF4A10732735E6000ULL, 0x7BF817E9650DAC24ULL, 0xC88A29A4ECF38ECDULL, 
            0xE4ABEA7191A815BBULL, 0xD2F6C3AA9AF7B5E4ULL, 0x04058BEEDAE18186ULL, 0x528E734712A8F824ULL, 
            0x620686F94DB72310ULL, 0x93A91A0ECADB4762ULL, 0x0500838F274F3BF1ULL, 0x9EF4BC902603A91CULL, 
            0x066B2D0A0DC09290ULL, 0x87F1BD92A1DE47CEULL, 0xF5D2F54D59830181ULL, 0x7059EF283F976D5AULL, 
            0x5FDCD84CF0B10980ULL, 0x9668B36007AA63FEULL, 0x461001FC13AC7291ULL, 0xF43B0A775E199570ULL, 
            0x16DB573B6735BA5AULL, 0x6181ACB2CDF61D36ULL, 0x7B21272AC438EA21ULL, 0xD57E1A0B5B221123ULL, 
            0xCB962074CF1E8DCDULL, 0x181C8073AAD77987ULL, 0xE8400872481F6F37ULL, 0xE9BDD6CCBAF2DD20ULL
        },
        {
            0x8E387906341065C2ULL, 0x9C9B2785736B1B6DULL, 0x1799D3F532EEE2F2ULL, 0xBE84D45A67487C04ULL, 
            0x40995578EB97A68EULL, 0x73A181C643A2E3F3ULL, 0xC236AEBD57507DA0ULL, 0xCE4C73356E6F1458ULL, 
            0xBBF81F784CAA7E0FULL, 0x6CC7F9BC0C2BBAC6ULL, 0xBA8C5680D13A69EDULL, 0xAB0620E8592A5FE9ULL, 
            0xFA63BE5044DF7179ULL, 0xA58E6E1686F28579ULL, 0x30F92C483A993294ULL, 0x14F088CC0D930B55ULL, 
            0x6312F6278A0F487FULL, 0x33B8287DE5F1205EULL, 0x9D9D79FF5E988123ULL, 0xBEF3C40E19AFDB3CULL, 
            0x7CC8BFE130028B66ULL, 0xB9F5E7BD0DDCE6E3ULL, 0xE84BB0470337E51AULL, 0xF9CDD0E40A6420B3ULL, 
            0x8FD07D01D672E70BULL, 0xC8593C3FC3B15625ULL, 0x265E6F693253540DULL, 0x44477C9EE7B314F5ULL, 
            0x33FD5F0DBD028958ULL, 0x712C3DA687344D14ULL, 0x2DEDCBF3DD31D521ULL, 0xD80D0269BA681297ULL
        },
        {
            0x3B5E6A321043622AULL, 0x5CA0B493BFD07F69ULL, 0xB304D95D69C411E9ULL, 0x5C4B19B8D86D7B5AULL, 
            0x756BB0F865C1A2B9ULL, 0x9F77610C2413A12AULL, 0x9880EF50A77298A9ULL, 0x5A202F81E69696D1ULL, 
            0x4BD95F3BBFF412EEULL, 0xCC17E9217F760D44ULL, 0xC0FD600BDEDC38F3ULL, 0xF97CC096A43A975AULL, 
            0xC6B37A203AFAD2AEULL, 0xB37DABBF18FCFDC3ULL, 0x6648B5048F2791DBULL, 0xFCD42CFD0FB4725AULL, 
            0xEAE3BA2B51F179C9ULL, 0xAF1807CF1DCE3FFCULL, 0xD7B05F69CD0C484BULL, 0x49C1BCEE4311AEFAULL, 
            0x2FD8BAAE6393E051ULL, 0x087E40152FF8EC78ULL, 0xB50EA7D79E76AB8DULL, 0x3723ADBBA55AE71DULL, 
            0xE598C90787962358ULL, 0x2AFB7CF3B80F1679ULL, 0x5F8F71E617D908B3ULL, 0x04B1346EB3014DC8ULL, 
            0xCC032AF01CDDCCB3ULL, 0x16179912EC524825ULL, 0xD548CE37493A637CULL, 0x4CB111E7FF3D5D56ULL
        }
    },
    {
        {
            0x6A8DF247727638C6ULL, 0x5CAACB10D140FAF8ULL, 0x3630C94FD649F917ULL, 0x848E877A0DE07AFBULL, 
            0xD8DB46FEE9CCABFEULL, 0xEB1A5CA6934446E7ULL, 0x7D3009985D124E24ULL, 0x7B95C11B4A486AF6ULL, 
            0xC94900F0CDCC518EULL, 0x9CEF8DFB03493AB8ULL, 0xDFC3CD45A26D115AULL, 0x863B9A0F672A8248ULL, 
            0xDEAB6EA85C13C70CULL, 0xCE75A597DD2A1689ULL, 0xA701D6B9C9B05C6CULL, 0x574BDC702C55F4B2ULL, 
            0x405AC3F4FC28F801ULL, 0x1CEE4E0AED3998CEULL, 0xD4C88467F9D5D82AULL, 0x14DE21A08F197785ULL, 
            0x13ED56A33BC996E0ULL, 0xBA041ACE506F8848ULL, 0x8D276E4B044CFDF5ULL, 0x05E4C490ED32FCF3ULL, 
            0xA208652CB647E1B3ULL, 0x2D2D9E3CA8EA7720ULL, 0x0F182FEE49B861FCULL, 0xB045048F78758165ULL, 
            0x5F9AB48C79EA1B44ULL, 0xAF11F5D795A00C04ULL, 0x4F624159D4152507ULL, 0x42F63C63A3B5A0CAULL
        },
        {
            0x3079469AC36C0976ULL, 0xD4DDA2631515D76AULL, 0x732E58AA3E11AD90ULL, 0x573A0C0798EA58F7ULL, 
            0x8B3EBF287DAAD319ULL, 0x7517C40B9D603155ULL, 0xA7406E400DDB8945ULL, 0xE40FEB01404E98BBULL, 
            0x8CA9ACAAD0206350ULL, 0x68D2A90EDD4C495DULL, 0xEF44120A64C1DBC0ULL, 0x46EA1EB06DBA5CCEULL, 
            0xF03F2E10D04FF6ECULL, 0x637D72ED0DA648B7ULL, 0x6B681142F54F3428ULL, 0x292811F7E91A9D66ULL, 
            0xA19859DB30A8741DULL, 0x7B11EB363FB22F6BULL, 0x70E3C18FA2ED7825ULL, 0xB6B1D4DE8A6F12A7ULL, 
            0xF5D2AC16E502CEC5ULL, 0x1C55B06C452739C5ULL, 0xB482B27EE8B17721ULL, 0x48ECC00CE8C4D955ULL, 
            0xB601BB3A58C704A7ULL, 0x0BE64036A464F8DDULL, 0xD909A54BC4CA91F0ULL, 0xCA08DF290716D3B0ULL, 
            0xA0464CDE20290D14ULL, 0xCC39A7CE634DAE96ULL, 0x81998FD312344507ULL, 0xE0B88EA73A73EB8EULL
        },
        {
            0x07BCB4E53B54E2D7ULL, 0xC0316C76FFF35EE0ULL, 0xAB1E932ECB31525EULL, 0x2E0D5CE9ADE5455DULL, 
            0xEBF5D4BD9A26C5E4ULL, 0x058C6EE3E0F96CCDULL, 0x77629221998D38FFULL, 0x1B7B91D7505EE1B1ULL, 
            0xD30ACB119E62FD6DULL, 0xF90904FC715ADD0AULL, 0x72F2FA71468E8885ULL, 0x5F6DA996C81E7E01ULL, 
            0x759F0F5AEF7D8540ULL, 0xE964B57CDE78F40DULL, 0xB3E96515927DA4FAULL, 0x90AA87B53C862541ULL, 
            0x96B4A31C01857165ULL, 0xBDEC11249D0D0B7CULL, 0xDB3108153019FC3EULL, 0xA8E3CC601DE82192ULL, 
            0xC2C43F9FC8D4FA35ULL, 0x4570BEF877874F28ULL, 0xBF11546745DD0C49ULL, 0x6D7FCED710F8DB2CULL, 
            0x27744BF6890AE829ULL, 0xA7DA41ABD58D64E4ULL, 0x755F45CC86BAD549ULL, 0xD4770A48CEFD4047ULL, 
            0xB7D51FFA54F3900AULL, 0x71CC405508BCE656ULL, 0x7C22D2CABB4F9E16ULL, 0xB3011DDDE55D49BDULL
        },
        {
            0x69E742025E1A927FULL, 0xB064B74A8192CE33ULL, 0x6E76DD6CA4F16A7AULL, 0x9A06C6FA0688C297ULL, 
            0x258BBF9BBE25EDDFULL, 0x951895B6B5E6169FULL, 0x33C77FD36DBFD735ULL, 0x104C2090B231670DULL, 
            0x415A4F52234517C5ULL, 0xD3FC240B864E95B5ULL, 0x163A6AA18416A9A1ULL, 0xFBF2946485F8A721ULL, 
            0xF4A71E80F3AE1FC7ULL, 0xFCA0A82BEED57107ULL, 0x6F25EFA61A1A4C3FULL, 0xACACC2C78012E6A2ULL, 
            0x2830933FCAD999CBULL, 0x5AF56B3E415588B7ULL, 0x3744308412C133D3ULL, 0x83F23C700F8296E1ULL, 
            0x3E194AAC91DBA1A4ULL, 0x7FF7B5BD90D794C3ULL, 0xE5C453217D75152AULL, 0xD3050ED34CB56B27ULL, 
            0x9EEDF202C4137F9EULL, 0x9730399C886A5F6CULL, 0x7EABBB11E7BD01D7ULL, 0x728BB3078D67530FULL, 
            0xA0F77CEAC84E2636ULL, 0x9054AD6F6651395EULL, 0xBB04D26F39C66208ULL, 0x712C4CC71E2375A3ULL
        },
        {
            0x905264E290D75E93ULL, 0x6232C23014A0CC96ULL, 0xD68505E8F8581B53ULL, 0xDEEC1EF49BF2FEB1ULL, 
            0xADBCA147B9CE7162ULL, 0x8ECFCC0CBC2A52F8ULL, 0xC1AC672635E47D52ULL, 0xAFC3CD12A57AEE4BULL, 
            0xA20ECD87D35BEFA2ULL, 0xC0148C9A3AE3BD43ULL, 0x99E7B1FB6DA8F4D3ULL, 0x73602D2264F570ACULL, 
            0x41B66DBE554BF8B8ULL, 0x850B34112297DCBEULL, 0x2520AAB33FCF1008ULL, 0xBDCE6FA620988F5BULL, 
            0xE700B3438B1D1509ULL, 0x98C4C40937F0DE90ULL, 0x80D35068B4664826ULL, 0x2B2D18C91B6122F6ULL, 
            0xF23201873D7C9718ULL, 0xE41E44B8E01CFB5EULL, 0xD907768D170DD042ULL, 0xA0AE31B3A0753D33ULL, 
            0xE37A48072CFC7769ULL, 0x7229A91007A650CEULL, 0x4E4045935892ECE9ULL, 0xC7C9CE549C80C04CULL, 
            0x08A8C9B28EF54307ULL, 0xB0E2B8D349B7370BULL, 0x12CCDDA093AE16DDULL, 0x35ABBFCDB74F6C3DULL
        },
        {
            0x4DFEDA533A48B03DULL, 0x20AEE1AB3BB805CAULL, 0xDE85043F63447B3AULL, 0xD2FD20B9C2A0706FULL, 
            0x7CCC53C261A03B2EULL, 0xBCB3AE2FA40F9838ULL, 0x8BBFB5B163CE71D6ULL, 0x800BB4E19F3829C6ULL, 
            0xAC28A28CF698C775ULL, 0x9C4461427023D73CULL, 0xF946B5894DA8D218ULL, 0x0AF114EC4E198966ULL, 
            0x20AC6C188776D32FULL, 0x3E8A2F28AE65B3F7ULL, 0xC5597ECC8C94C265ULL, 0x4CD70002A0DA8073ULL, 
            0x9974AA17C678171AULL, 0x2440CD8093E031C6ULL, 0x0578219115016943ULL, 0x5A8D054412B5C6E4ULL, 
            0x126067494BC223EAULL, 0x1467688AAC54EF32ULL, 0x849B643A28D8AEFFULL, 0xAC07FC41BE707AE8ULL, 
            0x89A7F60829A34A23ULL, 0xD4F3A2341289325FULL, 0x5F53D5BEDE42F633ULL, 0xF69EDE2E835E4F16ULL, 
            0x1A1068D9411014AEULL, 0xC1892A4E5DFA42F0ULL, 0xC5BAA2139FC23FCFULL, 0x1A6615BB2991142CULL
        }
    },
    {
        {
            0xE89E1D42A4038A83ULL, 0xF6527F70B414A28CULL, 0x472A5BE2D48C401BULL, 0x7E59D2B21CE63734ULL, 
            0x080B1BE439691E1EULL, 0xBD7BB9FB094799E8ULL, 0x76F43D88F8B284BCULL, 0xE66891DE7F70D97EULL, 
            0x60861BB83C3265E9ULL, 0xBBAB25F64C3A665FULL, 0xD9DD93D6DBCC2F87ULL, 0x4523F6D915C0FCA0ULL, 
            0x9D70BE8B84DC8C04ULL, 0x1C6425FE82A4F847ULL, 0xDEEE29C853C59556ULL, 0x4EA3372B6DA01018ULL, 
            0x4D1C152576169BBCULL, 0xCACB6611E2AB56F4ULL, 0x520ACC9CD0D319AFULL, 0x6D3DA7CBDE34B9EBULL, 
            0x9ABE14D7B6DA8192ULL, 0xA6989DD734299B4AULL, 0xCF65CBD669138CB5ULL, 0xB27E3E9684F3B75EULL, 
            0xA2B83A079225C24BULL, 0x1EF6AB4F4C9073DDULL, 0x4359BCAA11E10D77ULL, 0xCF3D9023EA7DF142ULL, 
            0xEFC8C0EE99911FF0ULL, 0x21B848ACFB72E1E8ULL, 0x535DFD603CF603AFULL, 0xA55DE36098DCE316ULL
        },
        {
            0x70CB1BAE40A9A8DAULL, 0x882FDA3C3E73A598ULL, 0xE30369E457355F87ULL, 0x06FC28EF2474AB30ULL, 
            0x188CEFDEE17CC958ULL, 0xC3123775FAA4E2A9ULL, 0x7DBB1A5DCF047030ULL, 0x364F3E98107A83FEULL, 
            0x2BB8678EECA46D24ULL, 0xD9CC4A3B00EA4762ULL, 0x844909E11FAD64D2ULL, 0xBE695FAE7DDD06AFULL, 
            0x1F98C5E94A4786ADULL, 0xC782BB2A473D0848ULL, 0x5200803D6BFC236DULL, 0x112F2387BDE9FC83ULL, 
            0x1EE8EBFB0CA4B9C5ULL, 0xC574CA7BB393B919ULL, 0x30A2B79CAEA16AF6ULL, 0x662AE53A8CDD836EULL, 
            0xC79F3BC5486112A6ULL, 0xAD7D5B19DD6D7D72ULL, 0xE73CD415CF7FCAC0ULL, 0x722C6561F254C9A6ULL, 
            0x7D412102D085D827ULL, 0xBBA81333C26F79D4ULL, 0x23C4A26326147116ULL, 0xCEAEC56A98702D45ULL, 
            0x4C90BD8E51EDFDA3ULL, 0x22FCFC9E6D7E37B3ULL, 0x00BD16A456C6DB67ULL, 0x666BEEC30CDDB2BAULL
        },
        {
            0xE42DD33BC53E5622ULL, 0xDF4D3F5CF4872DE7ULL, 0xB6C7526B12F004C7ULL, 0x7B09C412E3D42CB9ULL, 
            0xA8BFFE051D611FEBULL, 0xF6DAF8C9007CDECAULL, 0xD9291C208BAEAFE1ULL, 0x7B652B490B467302ULL, 
            0x9FDA48B71CACA5B4ULL, 0x7A0AB1A8FEC4ED1AULL, 0x0559CE04D154A71DULL, 0x98694EEA8BFC08E9ULL, 
            0x072D15536B864790ULL, 0x2B2B7A48DD4EA384ULL, 0xD1FE3EBEF64B90BCULL, 0x7C65BD41C9F9FEF3ULL, 
            0x1ED5F46FCA171627ULL, 0x8485FD71D06392D6ULL, 0x0D5906CA8EC17B27ULL, 0x013BDDAAA302D630ULL, 
            0x3B8B0E0D9ECE102EULL, 0x1F537BAC3C637012ULL, 0xE3D8F67B804366B4ULL, 0x576031709C0DBF9BULL, 
            0xFD722437F720D28CULL, 0x63561AC9DD979E8AULL, 0xF2702457750B98BBULL, 0x56F2A631305F7C4DULL, 
            0xEEE7C9E3DC4153CCULL, 0x576625D6E083BA6FULL, 0xE08E84560635EF5CULL, 0xA02870B22A03BA9AULL
        },
        {
            0x3272E122D0FD3D2DULL, 0xD3913C80227B3019ULL, 0x56E11B8889BC0238ULL, 0x805C05517637FC62ULL, 
            0xE40E2A689CFAC881ULL, 0x24DA60522A0914C5ULL, 0xE859882830A98A0AULL, 0x5254A97A5C9DBF2FULL, 
            0xE18CD92F5AB85267ULL, 0x558E905A395EA5A4ULL, 0x65AFA01C049D7193ULL, 0x0A0683C725725525ULL, 
            0xCDDA030DEBEE7319ULL, 0xCD6D18E03E207485ULL, 0x1BB4358EE3537A78ULL, 0xAD865CB58D0DACA5ULL, 
            0x2D4C3E6C5D44143DULL, 0xCB764ADBF5E3DEA3ULL, 0x6CB36E22E54E02A1ULL, 0xD411453A47B6C91BULL, 
            0xD8567948AE8C0F48ULL, 0x76B4DE6D7D10D835ULL, 0x105E35264BBD466EULL, 0x7A0893EA8677B364ULL, 
            0xC5516C601F132FF4ULL, 0xC4BFA0962201A1FFULL, 0x5DAA80D2C356F8DFULL, 0x0B16EEE328323E3FULL, 
            0x9A9D3744EE192BF9ULL, 0xE466E900D96EE538ULL, 0x12A5C5D4ACCEB7D8ULL, 0x5996CB1AC4202D5DULL
        },
        {
            0xA862A31A40DCB78FULL, 0x4787EF732C89FBC6ULL, 0x68AE8B361A82F869ULL, 0xF0E8803383827112ULL, 
            0x79C835CBB845E734ULL, 0x420D4AA65556B424ULL, 0x1FE0E18669CAE437ULL, 0x50B504BCCA88AEBCULL, 
            0xFA4AF445A17040EEULL, 0xF2C84AA3A380B284ULL, 0x2E1034693E9C3C5DULL, 0x70FB3FE9A32F0EAFULL, 
            0x8641DC7B1B70D800ULL, 0x6D81CAC3F7C36665ULL, 0x5AD5FF2806F7D454ULL, 0xE304FF385AC7442DULL, 
            0x3640AE41E6A1C5F8ULL, 0x0DE93F922367D566ULL, 0x693EE9FD8373EC79ULL, 0xEDA18EC3C7451A24ULL, 
            0x2595B145D308472DULL, 0x76D9B8ECC1D5A6C5ULL, 0xE0267F1ABB079059ULL, 0xB2BF170CD29AB7E9ULL, 
            0x1C07916769FA7A5FULL, 0xEDB2B077A6CC234EULL, 0xF494A739A9CE8F8EULL, 0x9E70B7B9AA9DF5FEULL, 
            0x522092BBCBF0C336ULL, 0x7A089B32E5288DFAULL, 0x1A283F4A7F5C0847ULL, 0x7B9FB430A5FF181FULL
        },
        {
            0xC8DF7F992AF82AA2ULL, 0x5F855B200CB2A47CULL, 0x58D3C5FF30299705ULL, 0x72BAD92E08A70F19ULL, 
            0x6F0F282294FB7FA4ULL, 0x0A70D94B4245018FULL, 0x3D0097DDA577D134ULL, 0xA4EE037EF771FB0EULL, 
            0x874C37CC6DEA410BULL, 0x23AE208FB076677EULL, 0xA1EC3436C3CA4691ULL, 0x7F04E22BAE74FACAULL, 
            0x63456BF48F73547AULL, 0x0C5575032FC98CA8ULL, 0x0487BD94362357E0ULL, 0x1D859B84B7C9CDB8ULL, 
            0xBCF33FAC3E51EA7FULL, 0x4753C0CD4AFFFBCEULL, 0x4EDF640BFD8CCFE9ULL, 0x40733DB2CD18ED6FULL, 
            0x2F70829E220CA504ULL, 0x1245D48076B8FFEFULL, 0x8D46820695AFCC8AULL, 0x2123CC2F2B91E9AAULL, 
            0xE03ED8EBAAD63755ULL, 0xB83CB3A7472CFF67ULL, 0x8777700B7C3234EAULL, 0x01F5D52A64F7D1E6ULL, 
            0xA24A694581A3C8FCULL, 0xFBF98537897FCE4CULL, 0xF42BB2A6B69B7C4BULL, 0xEA11B9C47BC7AEA3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseHConstants = {
    0x94C024AC9B9A9319ULL,
    0x7776DD48FA7B5952ULL,
    0x062198B7566E8612ULL,
    0x94C024AC9B9A9319ULL,
    0x7776DD48FA7B5952ULL,
    0x062198B7566E8612ULL,
    0x74FC165231F21D37ULL,
    0x7A544BCD7007D69FULL,
    0x6B,
    0x01,
    0x98,
    0x9B,
    0xC9,
    0x7A,
    0x56,
    0x77
};

